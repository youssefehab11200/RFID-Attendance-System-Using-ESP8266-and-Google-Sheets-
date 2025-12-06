# RFID Attendance System Using ESP8266 and Google Sheets

## University Information

**Zagazig National University**
Faculty of Engineering
Department of Mechatronics Engineering

---

## Project Title

**RFID Attendance System Using ESP8266 and Google Sheets**

---

## Prepared By

1. Youssef Ehab Taha El-Morsi
2. Ali Waleed Ali Zied
3. Momen Ali Fekry
4. Hadi Ibrahim Alhadi
5. Basmala Hsony Farouk Ibrahim
6. Malak Mohamed Abdelhakam
7. Yasmin Jaser Mohamed


## Supervised By

**Dr. Ahmed Osman**

## Date

December 2025

---

## Project Overview

This project presents an electronic attendance system based on **RFID technology** and **IoT**. The system uses an **RC522 RFID reader** connected to an **ESP8266 (NodeMCU)** to identify users through RFID cards. Attendance records are automatically sent over Wi-Fi to **Google Sheets** using a **Google Apps Script WebApp**.

A **16×2 I2C LCD** is used to display system messages and student information, while a **buzzer or LED** provides feedback for successful scans. The entire setup is mounted on a wooden board for stability and demonstration purposes.

---

## System Features

* Contactless RFID-based attendance
* Wi-Fi connectivity using ESP8266
* Real-time data logging to Google Sheets
* Visual feedback via LCD display
* Sound or LED feedback on successful scan
* Duplicate scan prevention
* Simple and low-cost implementation

---

## Hardware Components (BOM)

* ESP8266 NodeMCU (or compatible board)
* RC522 / MFRC522 RFID Reader
* MIFARE 1K RFID Cards or Tags
* 16×2 I2C LCD Display
* Buzzer or LED indicator
* Jumper wires
* 5V USB power supply
* Screws and plastic spacers
* Wooden board for mounting

---

## Software Components

* Arduino IDE
* ESP8266 Board Package
* MFRC522 Library
* ESP8266WiFi Library
* HTTPSRedirect Library
* Google Apps Script (WebApp)
* Google Sheets

---

## System Operation

1. Student data is first written to the RFID card using a dedicated **RFID write program**.
2. The attendance system reads the card data when placed near the RC522 reader.
3. Student information is displayed on the LCD.
4. Attendance data is sent as an HTTPS POST request to Google Apps Script.
5. Google Apps Script logs the data into Google Sheets with date and time.

---

## RFID Memory Usage

The system uses **MIFARE Classic 1K** RFID cards. The following memory blocks are used:

* Block 4: Roll Number
* Block 5: Student Name
* Block 6: Department / Program
* Block 8: Level / Group
* Block 9: Additional Information

Each block stores **16 bytes** of data.

---

## Duplicate Scan Prevention

To avoid repeated attendance records:

* The last scanned card UID is stored.
* The time of the last scan is recorded.
* A new attendance entry is accepted only if the UID changes or after a predefined time delay.

---

## Installation & Setup

1. Connect the hardware components according to the wiring configuration.
2. Upload the RFID write program to store data on the cards.
3. Upload the attendance system code to the ESP8266.
4. Configure Wi-Fi credentials inside the code.
5. Update the Google Apps Script ID and Spreadsheet ID.
6. Deploy the Apps Script as a WebApp.

---

## Hardware Assembly

* Mount all components securely on a wooden board.
* Ensure the RFID antenna area is not blocked.
* Organize wiring neatly for safety and reliability.
* Label the card scanning area for user guidance.

---

## Testing

* Verify Wi-Fi connection through Serial Monitor.
* Check RFID read/write functionality.
* Confirm LCD display output.
* Ensure attendance records appear correctly in Google Sheets.

---

## Troubleshooting

* No LCD display: Check I2C address and wiring.
* RFID not detected: Verify 3.3V supply and SPI connections.
* Wi-Fi issues: Recheck SSID and password.
* Google Sheets not updating: Confirm WebApp deployment and permissions.

---

## Future Improvements

* Add RTC or NTP for more accurate time tracking
* Offline data storage when Wi-Fi is unavailable
* Secure authentication for Google Script
* Web dashboard instead of Google Sheets
* Integration with Firebase or database systems

---

## Source Code

GitHub Repository:
[https://github.com/youssefehab11200/RFID-Attendance-System-Using-ESP8266-and-Google-Sheets-.git](https://github.com/youssefehab11200/RFID-Attendance-System-Using-ESP8266-and-Google-Sheets-.git)

---

## Security Notes

* MIFARE 1K cards are not encrypted by default.
* Avoid storing sensitive personal information on the cards.
* Restrict access to the Google Apps Script endpoint when possible.

---

**End of README**
