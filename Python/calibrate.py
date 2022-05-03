import serial
from PySide6 import QtWidgets
from MainWindow import Ui_MainWindow

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
    ser.close()
    return data_chunk

class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.setupUi(self)

        # Serial object
        self.ser = serial.Serial()

        self.pushButton_connectSerial.clicked.connect(self.connect_serial)
        self.pushButton_disconnectSerial.clicked.connect(self.disconnect_serial)

    def connect_serial(self):
        # Check if Serial Port has already been opened
        if self.ser.is_open:
            self.label_status.setText(f'{self.ser.port} still open!')
            return

        if self.lineEdit_baudrate.text().isnumeric():
            self.ser.baudrate = int(self.lineEdit_baudrate.text())
        else:
            self.label_status.setText('Invalid Baud Rate!')
            return

        self.ser.port = self.lineEdit_serialport.text()

        # If new Serial Port not open
        if not self.ser.is_open:
            try:
                self.ser.open()
                self.label_status.setText(f'Connected to {self.ser.port}')
            except serial.SerialException:
                self.label_status.setText(f'Invalid Serial Port!')
                return
        else:
            self.label_status.setText('Serial Port Closed!')
            return

    def disconnect_serial(self):
        if self.ser.is_open:
            self.ser.close()
            self.label_status.setText(f'Disconnected from {self.ser.port}')
        else:
            self.label_status.setText(f'{self.ser.port} not open!')


if __name__ == '__main__':
    #calibrate('COM7')
    app = QtWidgets.QApplication()
    window = MainWindow()
    window.show()
    app.exec_()