# NavXplorer

NavXplorer is a smart and automatic self-driven car designed for indoor navigation purposes. Originally conceived as a redesigned drip stand solution for elderly individuals prone to getting lost and for patients needing hands-free assistance in medical facility settings, it aims to navigate in complex indoor environments where GPS signals are ineffective.

## Introduction
[![Introduction Video](https://img.youtube.com/vi/5Z55hOexmpI/0.jpg)](https://www.youtube.com/watch?v=5Z55hOexmpI)

## Features
- **Automatic Navigation**: Navigates in indoor environments autonomously without relying on GPS.
- **Obstacle Avoidance**: Equipped with ultrasonic sensors for detecting obstacles and to ensure safety.
- **Patient Waiting**: Equipped with ultrasonic sensors for continuous monitoring of the user's presence.
- **QR Code Integration**: Utilizes QR codes for initial setup, determining location, and updating navigation directions.
- **Real-time Monitoring**: Provides a web server interface for monitoring the car's status and obstacle distances.

## Table of Contents
- Introduction
- Features
- Project Structure
- Hardware
- Software
- Installation
- How to Use
- Future Plans
- License
- References

## Project Structure

## Hardware
### Materials
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

### Circuit Diagrams

## Software
### Arduino Code
Controls various hardware modules essential for the operation of NavXplorer, including ESP32 board, power supply, ultrasonic sensors and motors. It also establishes a server for communication with code running on remote computers.<br>
<br>
Additionally, it provides a simple web server page for real-time monitoring of the car's status and display distances detected by the ultrasonic sensors.

### Python Code
Manages the navigation logic of NavXplorer in collaboration with a handheld QR code scanner.<br>
<br>
It reads QR codes during initial setup to determine the area, current position, and destination. During navigation, it continuously scans QR code inputs to update the car's current position and determine its subsequent direction.

### Installation
#### Download and Install Python
1. Visit the [Python download page](https://www.python.org/downloads/).
2. Select the appropriate version for your operating system.
3. Download and install Python by following the instructions provided on the page.
4. Make sure to check the box that says "Add Python to PATH" during the installation process.

#### Download and Install Arduino IDE
1. Visit the [Arduino IDE download page](https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE).
2. Select the appropriate version for your operating system (Windows, Mac, Linux).
3. Download and install the Arduino IDE by following the instructions provided on the page.

## How to Use

## Future Plans

## References
- Arduino Official Website<br>
  https://www.arduino.cc/
- Freenove ESP32 S3 WROOM Board <br>
  https://github.com/Freenove/Freenove_ESP32_S3_WROOM_Board
- HC-SR04 Datasheet
- L298N Datasheet
  
- **Special Thanks** <br>
  TA 仲耘 for providing the AI path planning idea <br>
  TA 致嘉 for providing the 2D Barcode Scanner idea

## License