#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>
#include <HTTPSRedirect.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//---------------------------------------------------------------------------------------------------------
const char *GScriptId = "AKfycbwo6aRauABndpqA81XQ3Su1uNhpfqc0pKd1CI1KmK6SPimJ6oQWRoQkC18vQUS1gLrF";
//---------------------------------------------------------------------------------------------------------
const char* ssid     = "YOUSSEF-EHAB 5504";
const char* password = "q89{N118";
//---------------------------------------------------------------------------------------------------------
String payload_base = "{\"command\": \"insert_row\", \"sheet_name\": \"Sheet1\", \"values\": ";
String payload = "";
//---------------------------------------------------------------------------------------------------------
const char* host = "script.google.com";
const int httpsPort = 443;

String url = String("/macros/s/") + GScriptId + "/exec";
HTTPSRedirect* client = nullptr;
//------------------------------------------------------------
String student_Rollno;
//------------------------------------------------------------
int blocks[] = {4,5,6,8,9};
#define total_blocks  (sizeof(blocks) / sizeof(blocks[0]))
//------------------------------------------------------------
#define RST_PIN  0  //D3
#define SS_PIN   2  //D4
#define BUZZER   4  //D2
//------------------------------------------------------------
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;
//------------------------------------------------------------
byte bufferLen = 18;
byte readBlockData[18];
//------------------------------------------------------------

// متغيرات منع تكرار التسجيل
String lastUID = "";
unsigned long lastScanTime = 0;

/****************************************************************************************************/
void setup() {
  pinMode(D8, OUTPUT);
  Serial.begin(9600);
  delay(10);
  Serial.println('\n');

  SPI.begin();

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting to");
  lcd.setCursor(0,1);
  lcd.print("WiFi...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Connecting to");
  lcd.setCursor(0,1);
  lcd.print("Google");

  for(int i=0; i<5; i++){
    if(client->connect(host, httpsPort)){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Connected ✓");
      delay(2000);
      break;
    }
  }
  delete client;
  client = nullptr;
}

/****************************************************************************************************/
void loop() {
  static bool flag = false;
  if (!flag){
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();
    flag = true;
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");
  }
  if (client != nullptr){
    if (!client->connected()){
      client->connect(host, httpsPort);
    }
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scan your Tag");

  mfrc522.PCD_Init();
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  // الحصول على UID
  String currentUID = "";
  for(byte i=0; i<mfrc522.uid.size; i++){
    currentUID += String(mfrc522.uid.uidByte[i], HEX);
  }

  // منع التكرار فقط لو الكارت لسه على الريدر
  if (currentUID == lastUID) {
    if (millis() - lastScanTime < 1000) return;
  }
  lastUID = currentUID;
  lastScanTime = millis();

  String values = "", data;

  for (byte i = 0; i < total_blocks; i++) {
    ReadDataFromBlock(blocks[i], readBlockData);
    data = String((char*)readBlockData);
    data.trim();

    if(i == 0){
      student_Rollno = data;
      values = "\"" + data + ",";
    }
    else if(i == total_blocks-1){
      values += data + "\"}";
    } else {
      values += data + ",";
    }
  }

  payload = payload_base + values;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Publishing Data");

  if(client->POST(url, host, payload)){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Roll No: "+student_Rollno);
    lcd.setCursor(0,1);
    lcd.print("Present ✓");
    digitalWrite(D8, HIGH);
    delay(1500);
    digitalWrite(D8, LOW);
  } else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Failed!");
    lcd.setCursor(0,1);
    lcd.print("Try Again");
  }

  delay(1000);
}

/****************************************************************************************************/
void ReadDataFromBlock(int blockNum, byte readBlockData[])
{
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK){
    Serial.print("Auth failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Reading failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  readBlockData[16] = ' ';
  readBlockData[17] = ' ';
}
