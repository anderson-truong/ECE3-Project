# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'calibration.ui'
##
## Created by: Qt User Interface Compiler version 6.0.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import *
from PySide6.QtGui import *
from PySide6.QtWidgets import *


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(568, 365)
        icon = QIcon()
        icon.addFile(u":/icon.png", QSize(), QIcon.Normal, QIcon.Off)
        MainWindow.setWindowIcon(icon)
        self.actionSave = QAction(MainWindow)
        self.actionSave.setObjectName(u"actionSave")
        self.actionSave_as = QAction(MainWindow)
        self.actionSave_as.setObjectName(u"actionSave_as")
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.tableWidget_dataTable = QTableWidget(self.centralwidget)
        if (self.tableWidget_dataTable.columnCount() < 2):
            self.tableWidget_dataTable.setColumnCount(2)
        __qtablewidgetitem = QTableWidgetItem()
        self.tableWidget_dataTable.setHorizontalHeaderItem(0, __qtablewidgetitem)
        __qtablewidgetitem1 = QTableWidgetItem()
        self.tableWidget_dataTable.setHorizontalHeaderItem(1, __qtablewidgetitem1)
        if (self.tableWidget_dataTable.rowCount() < 8):
            self.tableWidget_dataTable.setRowCount(8)
        __qtablewidgetitem2 = QTableWidgetItem()
        self.tableWidget_dataTable.setVerticalHeaderItem(0, __qtablewidgetitem2)
        __qtablewidgetitem3 = QTableWidgetItem()
        self.tableWidget_dataTable.setVerticalHeaderItem(1, __qtablewidgetitem3)
        __qtablewidgetitem4 = QTableWidgetItem()
        self.tableWidget_dataTable.setVerticalHeaderItem(2, __qtablewidgetitem4)
        __qtablewidgetitem5 = QTableWidgetItem()
        self.tableWidget_dataTable.setVerticalHeaderItem(3, __qtablewidgetitem5)
        __qtablewidgetitem6 = QTableWidgetItem()
        self.tableWidget_dataTable.setVerticalHeaderItem(4, __qtablewidgetitem6)
        __qtablewidgetitem7 = QTableWidgetItem()
        self.tableWidget_dataTable.setVerticalHeaderItem(5, __qtablewidgetitem7)
        __qtablewidgetitem8 = QTableWidgetItem()
        self.tableWidget_dataTable.setVerticalHeaderItem(6, __qtablewidgetitem8)
        __qtablewidgetitem9 = QTableWidgetItem()
        self.tableWidget_dataTable.setVerticalHeaderItem(7, __qtablewidgetitem9)
        self.tableWidget_dataTable.setObjectName(u"tableWidget_dataTable")
        self.tableWidget_dataTable.setGeometry(QRect(30, 30, 281, 271))
        self.verticalLayoutWidget = QWidget(self.centralwidget)
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(360, 80, 160, 163))
        self.verticalLayout_serial = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout_serial.setObjectName(u"verticalLayout_serial")
        self.verticalLayout_serial.setContentsMargins(0, 0, 0, 0)
        self.label_status = QLabel(self.verticalLayoutWidget)
        self.label_status.setObjectName(u"label_status")
        self.label_status.setAlignment(Qt.AlignCenter)

        self.verticalLayout_serial.addWidget(self.label_status)

        self.label_serialport = QLabel(self.verticalLayoutWidget)
        self.label_serialport.setObjectName(u"label_serialport")
        self.label_serialport.setAlignment(Qt.AlignCenter)

        self.verticalLayout_serial.addWidget(self.label_serialport)

        self.lineEdit_serialport = QLineEdit(self.verticalLayoutWidget)
        self.lineEdit_serialport.setObjectName(u"lineEdit_serialport")
        self.lineEdit_serialport.setAlignment(Qt.AlignCenter)

        self.verticalLayout_serial.addWidget(self.lineEdit_serialport)

        self.label_baudrate = QLabel(self.verticalLayoutWidget)
        self.label_baudrate.setObjectName(u"label_baudrate")
        self.label_baudrate.setAlignment(Qt.AlignCenter)

        self.verticalLayout_serial.addWidget(self.label_baudrate)

        self.lineEdit_baudrate = QLineEdit(self.verticalLayoutWidget)
        self.lineEdit_baudrate.setObjectName(u"lineEdit_baudrate")
        self.lineEdit_baudrate.setAlignment(Qt.AlignCenter)

        self.verticalLayout_serial.addWidget(self.lineEdit_baudrate)

        self.pushButton_connectSerial = QPushButton(self.verticalLayoutWidget)
        self.pushButton_connectSerial.setObjectName(u"pushButton_connectSerial")

        self.verticalLayout_serial.addWidget(self.pushButton_connectSerial)

        self.pushButton_disconnectSerial = QPushButton(self.verticalLayoutWidget)
        self.pushButton_disconnectSerial.setObjectName(u"pushButton_disconnectSerial")

        self.verticalLayout_serial.addWidget(self.pushButton_disconnectSerial)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 568, 21))
        self.menuFile = QMenu(self.menubar)
        self.menuFile.setObjectName(u"menuFile")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.menubar.addAction(self.menuFile.menuAction())
        self.menuFile.addAction(self.actionSave)
        self.menuFile.addAction(self.actionSave_as)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"ECE3 Sensor Calibration", None))
        self.actionSave.setText(QCoreApplication.translate("MainWindow", u"Save", None))
        self.actionSave_as.setText(QCoreApplication.translate("MainWindow", u"Save as", None))
        ___qtablewidgetitem = self.tableWidget_dataTable.horizontalHeaderItem(0)
        ___qtablewidgetitem.setText(QCoreApplication.translate("MainWindow", u"Min", None));
        ___qtablewidgetitem1 = self.tableWidget_dataTable.horizontalHeaderItem(1)
        ___qtablewidgetitem1.setText(QCoreApplication.translate("MainWindow", u"Max", None));
        ___qtablewidgetitem2 = self.tableWidget_dataTable.verticalHeaderItem(0)
        ___qtablewidgetitem2.setText(QCoreApplication.translate("MainWindow", u"Sensor 0", None));
        ___qtablewidgetitem3 = self.tableWidget_dataTable.verticalHeaderItem(1)
        ___qtablewidgetitem3.setText(QCoreApplication.translate("MainWindow", u"Sensor 1", None));
        ___qtablewidgetitem4 = self.tableWidget_dataTable.verticalHeaderItem(2)
        ___qtablewidgetitem4.setText(QCoreApplication.translate("MainWindow", u"Sensor 2", None));
        ___qtablewidgetitem5 = self.tableWidget_dataTable.verticalHeaderItem(3)
        ___qtablewidgetitem5.setText(QCoreApplication.translate("MainWindow", u"Sensor 3", None));
        ___qtablewidgetitem6 = self.tableWidget_dataTable.verticalHeaderItem(4)
        ___qtablewidgetitem6.setText(QCoreApplication.translate("MainWindow", u"Sensor 4", None));
        ___qtablewidgetitem7 = self.tableWidget_dataTable.verticalHeaderItem(5)
        ___qtablewidgetitem7.setText(QCoreApplication.translate("MainWindow", u"Sensor 5", None));
        ___qtablewidgetitem8 = self.tableWidget_dataTable.verticalHeaderItem(6)
        ___qtablewidgetitem8.setText(QCoreApplication.translate("MainWindow", u"Sensor 6", None));
        ___qtablewidgetitem9 = self.tableWidget_dataTable.verticalHeaderItem(7)
        ___qtablewidgetitem9.setText(QCoreApplication.translate("MainWindow", u"Sensor 7", None));
        self.label_status.setText("")
        self.label_serialport.setText(QCoreApplication.translate("MainWindow", u"Serial Port", None))
        self.lineEdit_serialport.setText("")
        self.label_baudrate.setText(QCoreApplication.translate("MainWindow", u"Baud Rate", None))
        self.lineEdit_baudrate.setText("")
        self.pushButton_connectSerial.setText(QCoreApplication.translate("MainWindow", u"Connect", None))
        self.pushButton_disconnectSerial.setText(QCoreApplication.translate("MainWindow", u"Disconnect", None))
        self.menuFile.setTitle(QCoreApplication.translate("MainWindow", u"File", None))
    # retranslateUi

