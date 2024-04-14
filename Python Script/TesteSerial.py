import serial
import time

arduino = serial.Serial(
    port='/dev/cu.usbserial-A50285BI',
    baudrate=115200,
    )

message = ''

while (True):
    while (arduino.inWaiting() > 0):
        message += arduino.readline(1).decode()

    print(message)
    message = ''
    time.sleep(1)
