# NavXplorer

NavXplorer is a smart and automatic self-driven car designed for indoor navigation purposes. Originally conceived as a redesigned drip stand solution for elderly individuals prone to getting lost and for patients needing hands-free assistance in medical facility settings, it aims to navigate in complex indoor environments where GPS signals are ineffective.

## Introduction


## Features

- **Automatic Navigation**: NavXplorer navigates indoor environments autonomously without relying on GPS signals.
- **Obstacle Avoidance**: Equipped with ultrasonic sensors for detecting obstacles and ensuring safe navigation.
- **Patient Waiting**: Use ultrasonic sensors to detect whether the user is still following.
- **QR Code Integration**: Utilizes QR codes for initial setup, determining location, and updating navigation directions.
- **Real-time Monitoring**: Provides a web server interface for monitoring the car's status and obstacle distances.

## Table of Contents
- Introduction
- Introduction
- Features
- Arduino Code
- Python Code
- Project Structure
- Hardware
  - Circuit Diagrams
  - Implementation Result
- Software
  - Arduino Code
  - Python COde
- Installation
- Usage
- Future Plans
- License

## Software
### Arduino code
Controls various hardware modules essential for the operation of NavXplorer, including ESP32 board, power supply, ultrasonic sensors, and motors. It also establishes a server for communication with code running on remote computers. Additionally, it provides a simple web server page for real-time monitoring of the car's status and display distances detected by the ultrasonic sensors.

### Python Code
Manages the navigation logic of NavXplorer in collaboration with a handheld QR code scanner. It reads QR codes during initial setup to determine the area, current position, and destination. During navigation, it continuously scans QR code inputs to update the car's current position and determine its subsequent direction.