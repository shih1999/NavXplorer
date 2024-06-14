# NavXplorer

NavXplorer is a smart and automatic self-driven car designed for indoor navigation purposes. Originally conceived as a redesigned drip stand solution for elderly individuals prone to getting lost and for patients needing hands-free assistance in medical facility settings, it aims to navigate in complex indoor environments where GPS signals are ineffective.

## Introduction

## Features

- **Automatic Navigation**: NavXplorer navigates indoor environments autonomously without relying on GPS signals.
- **Obstacle Avoidance**: Equipped with four ultrasonic sensors for detecting obstacles and ensuring safe navigation.
- **QR Code Integration**: Uses QR codes for initial setup, determining location, and updating navigation directions.
- **Real-time Monitoring**: Provides a web server interface for monitoring the car's status and obstacle distances.

## Arduino Code

Controls various hardware modules essential for the operation of NavXplorer, including the battery power supply, an ESP32 board, four ultrasonic sensors for obstacle avoidance and patient following, and a motor controller for two motors. It also establishes a server for communication with Python code running on remote computers. Additionally, it provides a simple web server page for real-time monitoring of the car's status and displays obstacle distances detected by the ultrasonic sensors.

## Python Code

Manages the navigation logic of NavXplorer in collaboration with a handheld QR code scanner. It reads QR codes during initial setup to determine the area, current position, and destination. During navigation, it continuously scans QR code inputs to update the car's current position and determine its subsequent direction.

## Table of Contents
- Introduction
- Features
- Arduino Code
- Python Code
- Project Structure
- Hardware
  - Circuit Diagrams
  - Implementation Result
- Installation
- Usage
- Future Plans
- License
