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
   4.2 [Python Code](#42-python-code)
5. [Installation](#5-installation)
6. [How to Run](#6-how-to-run)
7. [References](#7-References)
8. [Future Work](#8-Future-Work)

## 0. Introduction
[![Introduction Video](https://img.youtube.com/vi/5Z55hOexmpI/0.jpg)](https://www.youtube.com/watch?v=5Z55hOexmpI)

## 1. Features
- **Automatic Navigation**: Navigates in indoor environments autonomously without relying on GPS.
- **Obstacle Avoidance**: Equipped with ultrasonic sensors for detecting obstacles and to ensure safety.
- **Patient Waiting**: Equipped with ultrasonic sensors for continuous monitoring of the user's presence.
- **QR Code Integration**: Utilizes QR codes for initial setup, determining location, and updating navigation directions.
- **Real-time Monitoring**: Provides a web server interface for monitoring the car's status and obstacle distances.

## 2. Project Structure

## 3. Hardware
### 3.1 Materials
| Component | Quantity | Note
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
Controls various hardware modules essential for the operation of NavXplorer, including ESP32 board, power supply, ultrasonic sensors and motors. It also establishes a server for communication with code running on remote computers.
Additionally, it provides a simple web server page for real-time monitoring of the car's status and display distances detected by the ultrasonic sensors.

### 4.2 Python Code
Manages the navigation logic of NavXplorer in collaboration with a handheld QR code scanner.
It reads QR codes during initial setup to determine the area, current position, and destination. During navigation, it continuously scans QR code inputs to update the car's current position and determine its subsequent direction.

## 5. Installation
#### Download and Install Python
1. Visit the [Python download page](https://www.python.org/downloads/).
2. Select the appropriate version for your operating system.
3. Download and install Python by following the instructions provided on the page.
4. Make sure to check the box that says "Add Python to PATH" during the installation process.

#### Download and Install Arduino IDE
1. Visit the [Arduino IDE download page](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE).
2. Select the appropriate version for your operating system (Windows, Mac, Linux).
3. Download and install the Arduino IDE by following the instructions provided on the page.

## 6. How to Run

### 6.1 Run Arduino Code

1. Open Arduino IDE
2. Select **Files > Open > Find WebServerCarControl.ino > Click "Open"**
3. Select **Tools > Board > ESP32 Arduino > Click "ESP32S3 Dev Module"**
4. Modify Code: Change Wi-Fi settings to your own Wi-Fi credentials <br>

   <img src="https://github.com/shih1999/NavXplorer/assets/65940533/a382a86f-b8df-4a36-bbb0-62fbfded12da" width=40% height=40%>
6. Connect ESP32 to your computer using by USB cable.
7. Click the upload (right arrow) button to upload the code. <br>

   <img src="https://github.com/shih1999/NavXplorer/assets/65940533/aeebbb4c-8600-474a-a21a-1c92b6261cc5" width=40% height=40%>
9. Wait for the upload to finish.
10. Open Serial Monitor (baud rate set to 115200).

### 6.2 Run Python Code

1. Open **QRcodeScanControl.py**
2. Modify Code: Change IP to the IP address obtained from the Serial Monitor
3. Navigate to the correct directory
   
   ```bash
   cd path_to_directory
   ```
5. Run
   
   ```bash
   python QRcodeScanControl.py
   ```

## 7. Future Work

## 8. References
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
  
- **Special Thanks** <br>
  TA 仲耘 for providing the AI path planning idea <br>
  TA 致嘉 for providing the 2D Barcode Scanner idea
