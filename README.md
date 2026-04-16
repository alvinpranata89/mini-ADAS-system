# mini-ADAS-system

This is an ADAS system dashboard for vehicle parking including distance measurement and steering guidance on GUI.
The system involves:
1. distance measurement using HC-SR04 ultrasonic sensor module
2. STM32 acting as the 1st ECU
3. Raspberry pi acting as the 2nd ECU
4. MCP2515 CAN controller module to provide CAN protocol communication between ECUs
5. DualSense controller for steering guidance as simulated steering wheel

The GUI was developed using Qt creator

Raspberry pi's side:
1. sudo apt install libsocketcan2 libsocketcan-dev 
2. source adas-env/bin/activate
3. sudo ip link set can0 up type can bitrate 500000


