from evdev import InputDevice, ecodes
import time
import socket
import select

dev = InputDevice('/dev/input/event5')
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
target = ("127.0.0.1", 12345)

bias = None
steering = 0.0

MAX_TILT = 8000      # raw data on neutral position
DEADZONE = 30       # accelerometer noise floor 
SMOOTHING = 0.15     # 0.0 = very smooth, 1.0 = raw data

prev_steering = 0.0

while True:
    r, _, _ = select.select([dev], [], [], 0)
    if dev in r:
        for event in dev.read():
            if event.type == ecodes.EV_ABS and event.code == ecodes.ABS_X:
                raw = event.value

                # initial calibration
                if bias is None:
                    bias = raw
                    print(f"Bias set: {bias}")

                tilt = raw - bias

                # Deadzone
                if abs(tilt) < DEADZONE:
                    tilt = 0

                # Normalize 
                steering_raw = tilt / MAX_TILT
                steering_raw = max(-1.0, min(1.0, steering_raw))

                # Low-pass filter for smoothing
                prev_steering = (1 - SMOOTHING) * prev_steering + SMOOTHING * steering_raw
                steering = prev_steering * 10

    sock.sendto(str(steering).encode(), target)
    print(f"\rSTEER: {steering:+.9f}", end="")
    time.sleep(0.02) 
