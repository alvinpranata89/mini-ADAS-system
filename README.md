#Mini ADAS System (Parking Assistance Prototype)

This project demonstrates a simplified Advanced Driver Assistance System (ADAS) for vehicle parking, featuring distance measurement and steering guidance visualized on a graphical dashboard.

Overview

The system is built using a distributed embedded architecture with multiple nodes communicating over CAN.

Key Features
Real-time distance measurement using ultrasonic sensor
Steering input simulation using IMU (DualSense controller)
CAN-based communication between ECUs
Graphical dashboard for visualization (Qt)
System Architecture
Ultrasonic Sensor (HC-SR04) → Distance measurement
STM32 → Sensor ECU (data acquisition & CAN transmission)
Raspberry Pi → Processing ECU (steering input + dashboard)
MCP2515 → CAN controller (SPI interface)
DualSense Controller → IMU-based steering input
Qt GUI → Visualization layer
Requirements
Raspberry Pi OS
Python 3
Qt (for GUI)
CAN interface (MCP2515)
Setup (Raspberry Pi)
sudo apt update
sudo apt install libsocketcan2 libsocketcan-dev
sudo apt install python3-venv python3-full -y

python3 -m venv adas-env
source adas-env/bin/activate

pip install evdev
CAN Configuration
sudo ip link set can0 up type can bitrate 500000
Run
python steering.py

