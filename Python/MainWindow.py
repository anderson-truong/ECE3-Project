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
        MainWindow.resize(591, 438)
        icon = QIcon()
        icon.addFile(u"icon.ico", QSize(), QIcon.Normal, QIcon.Off)
        MainWindow.setWindowIcon(icon)
        MainWindow.setStyleSheet(u"background-color: rgb(23, 23, 23);")
        MainWindow.setIconSize(QSize(24, 24))
        MainWindow.setTabShape(QTabWidget.Rounded)
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
        brush = QBrush(QColor(255, 255, 255, 255))
        brush.setStyle(Qt.NoBrush)
        __qtablewidgetitem10 = QTableWidgetItem()
        __qtablewidgetitem10.setBackground(brush);
        self.tableWidget_dataTable.setItem(0, 0, __qtablewidgetitem10)
        self.tableWidget_dataTable.setObjectName(u"tableWidget_dataTable")
        self.tableWidget_dataTable.setGeometry(QRect(50, 20, 280, 267))
        self.tableWidget_dataTable.setAutoFillBackground(False)
        self.tableWidget_dataTable.setStyleSheet(u"QHeaderView::section\n"
"{\n"
"	background-color: rgb(244, 243, 243);\n"
"	border: 2px outset rgb(203, 203, 203);\n"
"}\n"
"\n"
"QTableWidget::item\n"
"{\n"
"	background-color: rgb(255, 255, 255);\n"
"    color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QTableWidget::item:selected\n"
"{\n"
"    background-color: rgb(244, 243, 243);\n"
"	 color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"QTableWidget\n"
"{\n"
"border: none;\n"
"\n"
"}")
        self.tableWidget_dataTable.setAlternatingRowColors(False)
        self.tableWidget_dataTable.setShowGrid(False)
        self.tableWidget_dataTable.setGridStyle(Qt.NoPen)
        self.tableWidget_dataTable.setCornerButtonEnabled(True)
        self.tableWidget_dataTable.horizontalHeader().setVisible(True)
        self.tableWidget_dataTable.horizontalHeader().setDefaultSectionSize(110)
        self.tableWidget_dataTable.horizontalHeader().setHighlightSections(False)
        self.tableWidget_dataTable.verticalHeader().setCascadingSectionResizes(False)
        self.tableWidget_dataTable.verticalHeader().setDefaultSectionSize(30)
        self.tableWidget_dataTable.verticalHeader().setHighlightSections(False)
        self.tableWidget_dataTable.verticalHeader().setProperty("showSortIndicator", False)
        self.tableWidget_dataTable.verticalHeader().setStretchLastSection(False)
        self.verticalLayoutWidget = QWidget(self.centralwidget)
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(380, 30, 160, 171))
        self.verticalLayout_serial = QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout_serial.setObjectName(u"verticalLayout_serial")
        self.verticalLayout_serial.setContentsMargins(0, 0, 0, 0)
        self.label_status = QLabel(self.verticalLayoutWidget)
        self.label_status.setObjectName(u"label_status")
        self.label_status.setStyleSheet(u"color: rgb(255, 255, 255);")
        self.label_status.setAlignment(Qt.AlignCenter)

        self.verticalLayout_serial.addWidget(self.label_status)

        self.label_serialport = QLabel(self.verticalLayoutWidget)
        self.label_serialport.setObjectName(u"label_serialport")
        self.label_serialport.setStyleSheet(u"color: rgb(255, 255, 255);")
        self.label_serialport.setAlignment(Qt.AlignCenter)

        self.verticalLayout_serial.addWidget(self.label_serialport)

        self.lineEdit_serialport = QLineEdit(self.verticalLayoutWidget)
        self.lineEdit_serialport.setObjectName(u"lineEdit_serialport")
        self.lineEdit_serialport.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.lineEdit_serialport.setAlignment(Qt.AlignCenter)

        self.verticalLayout_serial.addWidget(self.lineEdit_serialport)

        self.label_baudrate = QLabel(self.verticalLayoutWidget)
        self.label_baudrate.setObjectName(u"label_baudrate")
        self.label_baudrate.setStyleSheet(u"color: rgb(255, 255, 255);")
        self.label_baudrate.setAlignment(Qt.AlignCenter)

        self.verticalLayout_serial.addWidget(self.label_baudrate)

        self.lineEdit_baudrate = QLineEdit(self.verticalLayoutWidget)
        self.lineEdit_baudrate.setObjectName(u"lineEdit_baudrate")
        self.lineEdit_baudrate.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.lineEdit_baudrate.setAlignment(Qt.AlignCenter)

        self.verticalLayout_serial.addWidget(self.lineEdit_baudrate)

        self.pushButton_connectSerial = QPushButton(self.verticalLayoutWidget)
        self.pushButton_connectSerial.setObjectName(u"pushButton_connectSerial")
        self.pushButton_connectSerial.setStyleSheet(u"background-color: rgb(163, 247, 191);\n"
"border-color: rgb(0, 0, 0);")

        self.verticalLayout_serial.addWidget(self.pushButton_connectSerial)

        self.pushButton_disconnectSerial = QPushButton(self.verticalLayoutWidget)
        self.pushButton_disconnectSerial.setObjectName(u"pushButton_disconnectSerial")
        self.pushButton_disconnectSerial.setStyleSheet(u"background-color: rgb(255, 133, 133);\n"
"border-color: rgb(0, 0, 0);")

        self.verticalLayout_serial.addWidget(self.pushButton_disconnectSerial)

        self.verticalLayoutWidget_2 = QWidget(self.centralwidget)
        self.verticalLayoutWidget_2.setObjectName(u"verticalLayoutWidget_2")
        self.verticalLayoutWidget_2.setGeometry(QRect(380, 220, 161, 51))
        self.verticalLayout_sensor = QVBoxLayout(self.verticalLayoutWidget_2)
        self.verticalLayout_sensor.setObjectName(u"verticalLayout_sensor")
        self.verticalLayout_sensor.setContentsMargins(0, 0, 0, 0)
        self.pushButton_readSensors = QPushButton(self.verticalLayoutWidget_2)
        self.pushButton_readSensors.setObjectName(u"pushButton_readSensors")
        self.pushButton_readSensors.setAutoFillBackground(False)
        self.pushButton_readSensors.setStyleSheet(u"color: rgb(0, 0, 0);\n"
"background-color: rgb(255, 221, 98);")

        self.verticalLayout_sensor.addWidget(self.pushButton_readSensors)

        self.pushButton_resetValues = QPushButton(self.verticalLayoutWidget_2)
        self.pushButton_resetValues.setObjectName(u"pushButton_resetValues")
        self.pushButton_resetValues.setStyleSheet(u"background-color: rgb(255, 181, 89);")

        self.verticalLayout_sensor.addWidget(self.pushButton_resetValues)

        self.verticalLayoutWidget_3 = QWidget(self.centralwidget)
        self.verticalLayoutWidget_3.setObjectName(u"verticalLayoutWidget_3")
        self.verticalLayoutWidget_3.setGeometry(QRect(30, 310, 531, 80))
        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget_3)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.textBrowser_sensorCode = QTextBrowser(self.verticalLayoutWidget_3)
        self.textBrowser_sensorCode.setObjectName(u"textBrowser_sensorCode")
        self.textBrowser_sensorCode.setStyleSheet(u"color: rgb(255, 255, 255);\n"
"background-color: rgb(23, 23, 23);")

        self.verticalLayout.addWidget(self.textBrowser_sensorCode)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 591, 21))
        self.menubar.setStyleSheet(u"QMenuBar::item\n"
"{\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QMenuBar::item:selected {\n"
"	\n"
"	background-color: rgb(65, 65, 65);\n"
"}\n"
"\n"
"QMenuBar::item:pressed {\n"
"	background-color: rgb(83, 83, 83);\n"
"}")
        self.menuFile = QMenu(self.menubar)
        self.menuFile.setObjectName(u"menuFile")
        self.menuFile.setStyleSheet(u"QMenu::item\n"
"{\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QMenu::item:selected\n"
"{\n"
"	background-color: rgb(65, 65, 65);\n"
"}\n"
"\n"
"QMenu::item:pressed\n"
"{\n"
"	\n"
"	background-color: rgb(83, 83, 83);\n"
"}")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.menubar.addAction(self.menuFile.menuAction())
        self.menuFile.addAction(self.actionSave_as)

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"TI-RSLK IR Sensor Calibration", None))
        self.actionSave.setText(QCoreApplication.translate("MainWindow", u"Save", None))
        self.actionSave_as.setText(QCoreApplication.translate("MainWindow", u"Save  As", None))
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

        __sortingEnabled = self.tableWidget_dataTable.isSortingEnabled()
        self.tableWidget_dataTable.setSortingEnabled(False)
        self.tableWidget_dataTable.setSortingEnabled(__sortingEnabled)

        self.label_status.setText(QCoreApplication.translate("MainWindow", u"Connect to a port.", None))
        self.label_serialport.setText(QCoreApplication.translate("MainWindow", u"Serial Port", None))
        self.lineEdit_serialport.setText("")
        self.label_baudrate.setText(QCoreApplication.translate("MainWindow", u"Baud Rate", None))
        self.lineEdit_baudrate.setText("")
        self.pushButton_connectSerial.setText(QCoreApplication.translate("MainWindow", u"Connect", None))
        self.pushButton_disconnectSerial.setText(QCoreApplication.translate("MainWindow", u"Disconnect", None))
        self.pushButton_readSensors.setText(QCoreApplication.translate("MainWindow", u"Read Sensors", None))
        self.pushButton_resetValues.setText(QCoreApplication.translate("MainWindow", u"Reset Values", None))
        self.textBrowser_sensorCode.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">int16_t sensorMin[8] { 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500 };</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">int16_t sensorMax[8] { 0, 0, 0, 0, 0, 0, 0, 0 };</span></p></body></html>", None))
        self.menuFile.setTitle(QCoreApplication.translate("MainWindow", u"File", None))
    # retranslateUi

