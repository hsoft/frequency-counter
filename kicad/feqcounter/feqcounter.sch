EESchema Schematic File Version 4
LIBS:feqcounter-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+5V #PWR?
U 1 1 5BBD1769
P 1250 2150
F 0 "#PWR?" H 1250 2000 50  0001 C CNN
F 1 "+5V" H 1265 2323 50  0000 C CNN
F 2 "" H 1250 2150 50  0001 C CNN
F 3 "" H 1250 2150 50  0001 C CNN
	1    1250 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BBD17B5
P 1250 2600
F 0 "#PWR?" H 1250 2350 50  0001 C CNN
F 1 "GND" H 1255 2427 50  0000 C CNN
F 2 "" H 1250 2600 50  0001 C CNN
F 3 "" H 1250 2600 50  0001 C CNN
	1    1250 2600
	1    0    0    -1  
$EndComp
$Comp
L local:SN74HC161 U?
U 1 1 5BBD1AFD
P 3050 3400
F 0 "U?" H 3050 3975 50  0000 C CNN
F 1 "SN74HC161" H 3050 3884 50  0000 C CNN
F 2 "" H 3050 3400 50  0000 C CNN
F 3 "" H 3050 3400 50  0000 C CNN
	1    3050 3400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J?
U 1 1 5BBD1BBF
P 1150 3500
F 0 "J?" H 1044 3275 50  0000 C CNN
F 1 "FREQ SOURCE" H 1044 3366 50  0000 C CNN
F 2 "" H 1150 3500 50  0001 C CNN
F 3 "~" H 1150 3500 50  0001 C CNN
	1    1150 3500
	-1   0    0    1   
$EndComp
Wire Wire Line
	2350 3350 2350 3250
Connection ~ 2350 3150
Wire Wire Line
	2350 3150 2350 3050
Connection ~ 2350 3250
Wire Wire Line
	2350 3250 2350 3150
Wire Wire Line
	2350 3050 2150 3050
Connection ~ 2350 3050
Text Label 2150 3050 0    50   ~ 0
GND
Text Label 1250 2600 0    50   ~ 0
GND
Text Label 1250 2250 0    50   ~ 0
VCC
Wire Wire Line
	1250 2150 1250 2250
Text Label 2200 3550 0    50   ~ 0
VCC
Wire Wire Line
	2200 3550 2350 3550
Wire Wire Line
	1350 3500 1350 3650
Wire Wire Line
	1350 3650 2350 3650
Wire Wire Line
	3750 3650 3750 3550
Text Label 2200 3750 0    50   ~ 0
VCC
Text Label 3750 3550 0    50   ~ 0
VCC
Wire Wire Line
	2200 3750 2350 3750
NoConn ~ 3750 3150
NoConn ~ 3750 3250
NoConn ~ 3750 3350
NoConn ~ 3750 3450
$Comp
L MCU_Microchip_ATtiny:ATtiny45-20PU U?
U 1 1 5BBD227B
P 5350 1900
F 0 "U?" H 4820 1946 50  0000 R CNN
F 1 "ATtiny45-20PU" H 4820 1855 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5350 1900 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 5350 1900 50  0001 C CNN
	1    5350 1900
	-1   0    0    -1  
$EndComp
Text Label 5350 1300 0    50   ~ 0
VCC
Text Label 5350 2500 0    50   ~ 0
GND
NoConn ~ 4750 2100
Text Label 3750 3050 0    50   ~ 0
FREQ16
Text Label 2200 2400 0    50   ~ 0
FREQ16
Wire Wire Line
	3800 1800 4750 1800
$Comp
L local:SN74HC161 U?
U 1 1 5BBD1A3D
P 3100 2150
F 0 "U?" H 3100 2725 50  0000 C CNN
F 1 "SN74HC161" H 3100 2634 50  0000 C CNN
F 2 "" H 3100 2150 50  0000 C CNN
F 3 "" H 3100 2150 50  0000 C CNN
	1    3100 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2100 2400 2000
Connection ~ 2400 1900
Wire Wire Line
	2400 1900 2400 1800
Connection ~ 2400 2000
Wire Wire Line
	2400 2000 2400 1900
Text Label 2250 1800 0    50   ~ 0
GND
Wire Wire Line
	2250 1800 2400 1800
Connection ~ 2400 1800
Text Label 2200 2300 0    50   ~ 0
VCC
Text Label 2200 2500 0    50   ~ 0
VCC
Wire Wire Line
	2400 2300 2200 2300
Wire Wire Line
	2400 2500 2200 2500
NoConn ~ 3800 1900
NoConn ~ 3800 2000
NoConn ~ 3800 2100
NoConn ~ 3800 2200
Text Label 3800 2300 0    50   ~ 0
VCC
Wire Wire Line
	3800 2400 3800 2300
Wire Wire Line
	2400 2400 2200 2400
Text Label 4100 1800 0    50   ~ 0
FREQ256
NoConn ~ 4750 2000
NoConn ~ 4750 1900
$Comp
L Connector:USB_A J?
U 1 1 5BBD427B
P 3950 1050
F 0 "J?" H 4005 1517 50  0000 C CNN
F 1 "USB_A" H 4005 1426 50  0000 C CNN
F 2 "" H 4100 1000 50  0001 C CNN
F 3 " ~" H 4100 1000 50  0001 C CNN
	1    3950 1050
	1    0    0    -1  
$EndComp
NoConn ~ 3850 1450
Text Label 3950 1450 0    50   ~ 0
GND
Text Label 4250 850  0    50   ~ 0
VCC
Wire Wire Line
	4750 1600 4750 1050
Wire Wire Line
	4750 1050 4250 1050
Wire Wire Line
	4250 1150 4650 1150
Wire Wire Line
	4650 1150 4650 1700
Wire Wire Line
	4650 1700 4750 1700
Text Label 4300 1050 0    50   ~ 0
OUTCLK
Text Label 4300 1150 0    50   ~ 0
OUTSER
$EndSCHEMATC
