# NavXplorer
NavXplorer is a smart and automatic self-driven car designed for indoor navigation. Originally conceived as a redesigned drip stand solution, it aims to assist patients needing hands-free assistance and elderly individuals prone to getting lost in medical environments. However, it can also be applied to other complex indoor settings where GPS signals are ineffective.

## Table of Contents
0. [Introduction](#0-introduction)
1. [Features](#1-features)
2. [Project Structure](#2-project-structure)
3. [Hardware](#3-hardware) <br>
   3.1 [Materials](#31-materials) <br>
   3.2 [Circuit Diagrams](#32-circuit-diagrams)
4. [Software](#4-software) <br>
   4.1 [Arduino Code](#41-arduino-code) <br>
   4.2 [Python Code](#42-python-code) <br>
   4.3 [Code Logic and Functionality](#43-code-logic-and-functionality)
5. [Installation](#5-installation)
6. [How to Run](#6-how-to-run)
7. [References](#7-References)
8. [Future Work](#8-Future-Work)
9. [Our Team](#9-our-team)
9. [Our Team](#9-our-team)

## 0. Introduction
[![Introduction Video](https://img.youtube.com/vi/5Z55hOexmpI/0.jpg)](https://www.youtube.com/watch?v=5Z55hOexmpI)

## 1. Features
- **Automatic Navigation**:  Navigates autonomously in indoor environments.
- **Obstacle Avoidance**: Equipped with ultrasonic sensors for detecting obstacles to ensure safety.
- **User Presence Detection**: Uses ultrasonic sensors to continuously monitor the user's presence.
- **QR Code Integration**: Utilizes QR codes for initial setup, location determination, and navigation updates.
- **Real-time Monitoring**: Provides a web server interface for monitoring the car's status and obstacle distances.

## 2. Project Structure
```bash
NavXplorer/
│
├── WebServerCarControl/
│   └── WebServerCarControl.ino
├── QRcodeScanControl/
│   └── QRcodeScanControl.py
├── ModuleTest/
│   ├── MotorTest/
│   │   └── MotorTest.ino
│   ├── UltrasonicTest/
│   │   └── UltrasonicTest.ino
│   └── README.md  # This README explains the testing code
└── README.md  # This README explains the main project
```

## 3. Hardware
### 3.1 Materials
| Material | Number | Note
|:-|:-:|:-:|
| ESP32-S3 Development Board | 1 | |
| HC-SR04 Ultrasonic Distance Measurement Module | 4 | |
| L298N Motor Driver Module for DC Motors| 1 | |
| DC3V-6V TT Gear Motor 1:48 | 2 | |
| 65 * 27mm TPE Rubber Wheel | 2 | |
| W420 Ball Caster Wheel | 1 | |
| 12V Battery Power Supply | 1 | |
| 2D Bluetooth Barcode Scanner | 1 | eg. AURORA XB-6208 |

### 3.2 Circuit Diagrams

## 4. Software

### 4.1 Arduino Code
Controls essential hardware modules for the operation of NavXplorer, including the ESP32 board, power supply, ultrasonic sensors, and motors. It establishes a server for remote communication and provides a web page for real-time monitoring of the car's status and ultrasonic sensor detection results.

### 4.2 Python Code
Manages NavXplorer's navigation logic in conjunction with a handheld QR code scanner. During initial setup, it reads QR codes to determine the area, current position, and destination. Throughout navigation, it continuously scans QR code inputs to update it's position and determine the next direction.

### 4.3 Code Logic and Functionality
Still writing ...

## 5. Installation
#### Download and Install Arduino IDE
1. Visit the [Arduino IDE download page](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE)
2. Select the appropriate version for your operating system (Windows, Mac, Linux)
3. Download and install the Arduino IDE by following the instructions provided on the page
   
#### Download and Install Python
1. Visit the [Python download page](https://www.python.org/downloads/)
2. Select the appropriate version for your operating system
3. Download and install Python by following the instructions provided on the page
4. Make sure to check the box that says "Add Python to PATH" during the installation process

## 6. How to Run

### 6.1 Run Arduino Code

1. Open Arduino IDE
2. Select **Files > Open > Find WebServerCarControl.ino > Click "Open"**
3. Select **Tools > Board > ESP32 Arduino > Click "ESP32S3 Dev Module"**
4. Modify Code: Change Wi-Fi settings to your own Wi-Fi credentials <br>

   <img src="https://github.com/shih1999/NavXplorer/assets/65940533/e864bceb-431a-4aa1-a12c-3b27ecb59cf9" width=45% height=45%>
6. Connect ESP32 to your computer by USB cable
7. Click the upload (right arrow) button to upload the code <br>

   <img src="https://github.com/shih1999/NavXplorer/assets/65940533/aeebbb4c-8600-474a-a21a-1c92b6261cc5" width=45% height=45%>
9. Wait for the upload to finish
10. Open Serial Monitor (baud rate set to 115200)

### 6.2 Run Python Code

1. Open **QRcodeScanControl.py**
2. Modify Code: Change IP to the ip address obtained from the Serial Monitor

   <img src="https://github.com/shih1999/NavXplorer/assets/65940533/6a31f012-ea4a-4b93-9291-a7b80b213ab9" width=45% height=45%>

4. Navigate to the correct directory
   
   ```bash
   cd path_to_directory
   ```
5. Run
   
   ```bash
   python QRcodeScanControl.py
   ```
## 7. References
- Arduino Official Website <br>
  https://www.arduino.cc/
- Freenove ESP32 S3 WROOM Board <br>
  https://github.com/Freenove/Freenove_ESP32_S3_WROOM_Board
- HC-SR04 Datasheet <br>
  https://pdf1.alldatasheet.com/datasheet-pdf/view/1132203/ETC2/HC-SR04.html
- L298N Datasheet <br>
  https://pdf1.alldatasheet.com/datasheet-pdf/view/22440/STMICROELECTRONICS/L298N.html
- ChatGPT - OpenAI <br>
  https://chatgpt.com/

## 8. Future Work

## 9. Our Team

#### Team Members
#### Team Members
- **Yvonne Chen** (GitHub: [@yvonne-chen-0813](https://github.com/yvonne-chen-0813))
- **Shih-Jieh Chen** (GitHub: [@shih1999](https://github.com/shih1999))


#### Special Thanks
#### Special Thanks

- **TA 仲耘** for providing the AI path planning idea

- **TA 致嘉** for providing the 2D Barcode Scanner idea


