EESchema Schematic File Version 4
EELAYER 30 0
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
L ESP8266:NodeMCU1.0(ESP-12E) U1
U 1 1 606B3892
P 5450 3900
F 0 "U1" H 5450 5093 60  0000 C CNN
F 1 "NodeMCU1.0(ESP-12E)" H 5450 4987 60  0000 C CNN
F 2 "ESP8266:ESP12F-Devkit-V3" H 5450 4881 60  0000 C CNN
F 3 "" H 4850 3050 60  0000 C CNN
	1    5450 3900
	1    0    0    -1  
$EndComp
Text Label 7250 4200 2    50   ~ 0
V_in
Text Label 7250 4300 2    50   ~ 0
RX_Trig
Text Label 7250 4400 2    50   ~ 0
TX_Echo
Text Label 7250 4500 2    50   ~ 0
GND
Text Label 7550 3300 2    50   ~ 0
GND
Text Label 7550 3400 2    50   ~ 0
DQ
Text Label 7550 3500 2    50   ~ 0
VDD
Wire Wire Line
	6750 4200 7250 4200
$Comp
L Device:R R1
U 1 1 6069D019
P 6750 3550
F 0 "R1" V 6543 3550 50  0000 C CNN
F 1 "4.7k" V 6634 3550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 6680 3550 50  0001 C CNN
F 3 "~" H 6750 3550 50  0001 C CNN
	1    6750 3550
	-1   0    0    1   
$EndComp
Connection ~ 6750 3700
Wire Wire Line
	6750 3400 7550 3400
Wire Wire Line
	6250 3400 6750 3400
Connection ~ 6750 3400
Wire Wire Line
	6750 3700 7150 3700
Wire Wire Line
	6250 3700 6750 3700
Wire Wire Line
	6750 3700 6750 4200
Wire Wire Line
	6250 3800 7350 3800
$Comp
L Connector:Conn_01x05_Female J1
U 1 1 606E4F3A
P 7450 4400
F 0 "J1" H 7478 4426 50  0000 L CNN
F 1 "Conn_01x05_Female" H 7478 4335 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 7450 4400 50  0001 C CNN
F 3 "~" H 7450 4400 50  0001 C CNN
	1    7450 4400
	1    0    0    -1  
$EndComp
NoConn ~ 4650 3200
NoConn ~ 4650 3300
NoConn ~ 4650 3400
NoConn ~ 4650 3600
NoConn ~ 4650 3700
NoConn ~ 4650 3800
NoConn ~ 4650 4000
NoConn ~ 4650 4100
NoConn ~ 4650 4200
NoConn ~ 4650 4300
NoConn ~ 4650 4400
NoConn ~ 4650 4500
NoConn ~ 4650 4600
NoConn ~ 6250 4600
NoConn ~ 7250 4600
NoConn ~ 6250 4400
NoConn ~ 6250 4300
NoConn ~ 6250 4200
NoConn ~ 6250 3500
NoConn ~ 6250 3300
NoConn ~ 6250 3200
NoConn ~ 4650 3900
NoConn ~ 6250 3600
NoConn ~ 4650 3500
Wire Wire Line
	7250 4300 6650 4300
Wire Wire Line
	7250 4400 6550 4400
Wire Wire Line
	6250 3900 6650 3900
Wire Wire Line
	6650 3900 6650 4300
Wire Wire Line
	6550 4000 6250 4000
Wire Wire Line
	6550 4000 6550 4400
NoConn ~ 6250 4100
$Comp
L LakeLevel-rescue:TBL003-254-03GR-2OR-TBL003-254-03GR-2OR DS18B20
U 1 1 606E0C3C
P 7950 3400
F 0 "DS18B20" H 8180 3446 50  0000 L CNN
F 1 "TBL003-254-03GR-2OR" H 8180 3355 50  0000 L CNN
F 2 "TBL003-254-03GR-2OR:CUI_TBL003-254-03GR-2OR" H 7950 3400 50  0001 L BNN
F 3 "" H 7950 3400 50  0001 L BNN
F 4 "CUI" H 7950 3400 50  0001 L BNN "MANUFACTURER"
F 5 "Manufacturer Recommendations" H 7950 3400 50  0001 L BNN "STANDARD"
	1    7950 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 3500 7150 3500
Wire Wire Line
	7150 3500 7150 3700
Wire Wire Line
	7550 3300 7350 3300
Wire Wire Line
	7350 3300 7350 3800
Wire Wire Line
	6250 4500 7250 4500
$EndSCHEMATC
