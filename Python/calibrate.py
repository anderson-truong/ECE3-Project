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

        # Defaults
        self.data_mins = [2500 for i in range(8)]
        self.data_maxs = [0 for i in range(8)]

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
            self.label_status.setText('Invalid baud rate!')
            return

        self.ser.port = self.lineEdit_serialport.text()

        # If new Serial Port not open
        if not self.ser.is_open:
            try:
                self.ser.open()
                self.label_status.setText(f'Connected to {self.ser.port}')
            except serial.SerialException:
                self.label_status.setText(f'Invalid serial port!')
                return
        else:
            self.label_status.setText('Serial port closed!')
            return

    def disconnect_serial(self):
        if self.ser.is_open:
            self.ser.close()
            self.label_status.setText(f'Disconnected from {self.ser.port}')
        else:
            self.label_status.setText(f'{self.ser.port} not open!')

    def readSensors(self):
        if not self.ser_isopen:
            self.label_status.setText(f'No serial connection!')
            return
        data_chunk = []
        data_means = [0 for i in range(8)]

        for i in range(17):
            input()
            try:
                self.ser.write(b'1')
                for j in range(5):
                    line = self.ser.readline().decode('utf-8').rstrip(',\n').split(',')
                    line = [int(item) for item in line]
                    for idx, item in enumerate(line):
                        data_means[idx] += item
                data_means = [item/5. for item in data_means]
                for idx in range(8):
                    if data_means[idx] < self.data_mins[idx]:
                        self.data_mins[idx] = data_means[idx]
                    if data_means[idx] > self.data_maxs[idx]:
                        self.data_maxs[idx] = data_means[idx]
                for idx, item in self.data_mins:
                    self.tableWidget_dataTable.setItem(idx, 0, item)
                for idx, item in self.data_maxs:
                    self.tableWidget_dataTable.setItem(idx, 1, item)

            except serial.SerialException:
                self.label_status.setText(f'No serial connection!')



if __name__ == '__main__':
    #calibrate('COM7')
    app = QtWidgets.QApplication()
    window = MainWindow()
    window.show()
    app.exec_()