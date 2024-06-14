# NavXplorer

NavXplorer is a smart and automatic self-driven car designed for indoor navigation purposes. Originally conceived as a redesigned drip stand solution for elderly individuals prone to getting lost and for patients needing hands-free assistance in medical facility settings, it aims to navigate in complex indoor environments where GPS signals are ineffective.

## Introduction

This project consists of two main components:

**Arduino Code**
Controls various hardware modules essential for the operation of NavXplorer, including the battery power supply, an ESP32 board, four ultrasonic sensors for obstacle avoidance and patient following, and a motor controller for two motors. It also establishes a server for communication with Python code running on remote computers. Additionally, it provides a simple web server page for real-time monitoring of the car's status and displays obstacle distances detected by the ultrasonic sensors.

**Python Code**
Manages the navigation logic of NavXplorer in collaboration with a handheld QR code scanner. It reads QR codes during initial setup to determine the area, current position, and destination. During navigation, it continuously scans QR code inputs to update the car's current position and determine its subsequent direction

## Table of Contents
- Intoduction
- Features
- Project Structure
- Installation
- Usage
- Future Plans
- License
