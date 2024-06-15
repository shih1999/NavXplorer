# NavXplorer

NavXplorer is a smart and automatic self-driven car designed for indoor navigation purposes. Originally conceived as a redesigned drip stand solution for elderly individuals prone to getting lost and for patients needing hands-free assistance in medical facility settings, it aims to navigate in complex indoor environments where GPS signals are ineffective.

## Introduction

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

## Hardware
### Materials
- ESP32-S3 Development Board
- HC-SR04 Ultrasonic Distance Measurement Module x4
- L298N Motor Driver Module for DC Motors x 1
- DC3V-6V TT Gear Motor 1:48 x 2
- Wheels x 2
- W420 Ball Caster Wheel x 1
- 12V Battery Power Supply
- 2D Barcode Scanner (eg. AURORA XB-6208)

### Circuit Diagrams

## Software
### Arduino code
Controls various hardware modules essential for the operation of NavXplorer, including ESP32 board, power supply, ultrasonic sensors, and motors. It also establishes a server for communication with code running on remote computers. Additionally, it provides a simple web server page for real-time monitoring of the car's status and display distances detected by the ultrasonic sensors.

### Python Code
Manages the navigation logic of NavXplorer in collaboration with a handheld QR code scanner. It reads QR codes during initial setup to determine the area, current position, and destination. During navigation, it continuously scans QR code inputs to update the car's current position and determine its subsequent direction.

## Refernces
- Freenove ESP32 S3 WROOM Board
  https://github.com/Freenove/Freenove_ESP32_S3_WROOM_Board