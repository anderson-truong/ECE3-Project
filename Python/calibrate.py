import serial
from datetime import datetime

def calibrate(serial_port, baudrate = 9600):
    ser = serial.Serial()
    ser.baudrate = baudrate
    ser.port = serial_port
    # 5 rows
    data_chunk = []

    ser.open()
    for i in range(17):
        input()
        ser.write(b'1')
        for i in range(5):
            data_chunk.append(ser.readline().decode('utf-8').rstrip('\n'))
    return data_chunk
    ser.close()

if __name__ == '__main__':
    calibrate('COM7')