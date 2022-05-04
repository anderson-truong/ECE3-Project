# UCLA ECE 3 Project - Spring 2022
## Arduino Setup
1. [Download Arduino IDE](https://www.arduino.cc/en/software)
2. Go to File > Preferences > Additional Board Manager URLs
3. Enter in the textbox: http://s3.amazonaws.com/energiaUS/packages/package_energia_index.json
4. Go to Tools > Board > Boards Manager
5. Search for "Energia MSP432" and install the library
6. After installing, select the board under Tools > Board > "Energia MSP432 Red Boards" > "Red LaunchPad MSP432P401R EMT"

## TI-RSLK IR Sensor Calibration GUI
1. Open "Calibrate.ino" under Arduino > Calibrate.

2. Upload to the TI-RSLK.

3. Check what serial port the TI-RSLK is under by going to Tools > Port and selecting a port (for example, COM3).
Go to Tools > Serial Monitor and enter in any key.
If the program prints out 5 lines of values, then the port is correct. Keep a note of this port.

4. Open "sensorcalibration.exe".

5. Enter in your serial port under Serial Port (for example, COM3). This is case-sensitive.

6. Enter in 9600 under Baud Rate.

7. Click the Connect button.

8. In between shifting your calibration paper, click the Read Sensors button to log the minimum and maximum IR readings for each sensor.

9. Copy the C code under the table to use as your minimum and maximum value arrays.

10. Go to File > Save As to save the C code in a .txt file.
