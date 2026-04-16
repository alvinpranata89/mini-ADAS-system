# Mini ADAS System (Parking Assistance Prototype)

This project demonstrates a simplified Advanced Driver Assistance System (ADAS) for vehicle parking, featuring distance measurement and steering trajectory visualized on a graphical dashboard.

## Overview

The system is built using a distributed embedded architecture with multiple nodes communicating over CAN.

### Key Features

* Real-time distance measurement using ultrasonic sensor
* Steering input simulation using IMU (DualSense controller)
* CAN-based communication between ECUs
* Graphical dashboard for visualization (Qt)

---

## System Architecture

* **Ultrasonic Sensor (HC-SR04)** → Distance measurement
* **STM32** → Sensor ECU (data acquisition and CAN transmission)
* **Raspberry Pi** → Processing ECU (steering input and dashboard)
* **MCP2515** → CAN controller (SPI interface)
* **DualSense Controller** → IMU-based steering input
* **Qt GUI** → Visualization layer

---

## Requirements

* Raspberry Pi OS
* Python 3
* Qt (for GUI)
* CAN interface (MCP2515)

---
## STM32 Firmware

The STM32 firmware was generated using STM32CubeMX and implements:

- Ultrasonic sensor data acquisition
- CAN message transmission via MCP2515

Key logic can be found in:
- Core/Src/main.c

## Setup (Raspberry Pi)

```bash
sudo apt update
sudo apt install libsocketcan2 libsocketcan-dev
sudo apt install python3-venv python3-full -y

python3 -m venv adas-env
source adas-env/bin/activate

pip install evdev
```

## GUI (Qt)

The dashboard is implemented using Qt on Raspberry Pi.  
Open the project using Qt Creator and build normally.


## CAN Configuration

```bash
sudo ip link set can0 up type can bitrate 500000
```

---

## Run
Run the DS python script together with the compiled Qt dashboard
```bash
python DS.py
```

---

## Notes

* Steering input is derived from IMU gyro data (DualSense controller)
* Includes filtering, deadzone, and drift compensation
* CAN protocol is used to simulate communication between automotive ECUs

---

https://github.com/user-attachments/assets/3e7f92fb-65e7-405c-b2f5-7b87920ac040

https://github.com/user-attachments/assets/1310b057-ce1c-4888-b549-76da096c774f

## Future Improvements

* Integration with real automotive steering angle sensor
* Adding more distance sensor or using real vehicle distance sensor
* Advanced ADAS logic (lane detection, camera integration)


