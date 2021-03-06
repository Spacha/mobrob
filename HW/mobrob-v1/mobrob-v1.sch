EESchema Schematic File Version 4
EELAYER 29 0
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
L Regulator_Linear:LM7805_TO220 U?
U 1 1 62472A6C
P 1950 1350
F 0 "U?" H 1950 1592 50  0000 C CNN
F 1 "LM7805_TO220" H 1950 1501 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 1950 1575 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7805.pdf" H 1950 1300 50  0001 C CNN
	1    1950 1350
	1    0    0    -1  
$EndComp
$Comp
L Driver_Motor:L293D U?
U 1 1 62473727
P 8500 1900
F 0 "U?" H 8500 3081 50  0000 C CNN
F 1 "L293D" H 8500 2990 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 8750 1150 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/l293.pdf" H 8200 2600 50  0001 C CNN
	1    8500 1900
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 62476F99
P 6900 1550
F 0 "J?" H 6980 1542 50  0000 L CNN
F 1 "Conn_01x02" H 6980 1451 50  0000 L CNN
F 2 "" H 6900 1550 50  0001 C CNN
F 3 "~" H 6900 1550 50  0001 C CNN
	1    6900 1550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 624780E0
P 6900 2050
F 0 "J?" H 6980 2042 50  0000 L CNN
F 1 "Conn_01x02" H 6980 1951 50  0000 L CNN
F 2 "" H 6900 2050 50  0001 C CNN
F 3 "~" H 6900 2050 50  0001 C CNN
	1    6900 2050
	1    0    0    -1  
$EndComp
Text Notes 6300 2450 0    50   ~ 0
Two 2-pin connectors for the motors
$Comp
L RF_Module:ESP32-WROOM-32D U?
U 1 1 62481721
P 3900 3500
F 0 "U?" H 3900 5081 50  0000 C CNN
F 1 "ESP32-WROOM-32D" H 3900 4990 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 3900 2000 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf" H 3600 3550 50  0001 C CNN
	1    3900 3500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_ARM_JTAG_SWD_20 J?
U 1 1 624835EF
P 8500 4400
F 0 "J?" H 7971 4446 50  0000 R CNN
F 1 "Conn_ARM_JTAG_SWD_20" H 7971 4355 50  0000 R CNN
F 2 "" H 8950 3350 50  0001 L TNN
F 3 "http://infocenter.arm.com/help/topic/com.arm.doc.dui0499b/DUI0499B_system_design_reference.pdf" V 8150 3150 50  0001 C CNN
	1    8500 4400
	1    0    0    -1  
$EndComp
Text Notes 8100 5450 0    50   ~ 0
JTAG 20-pin connector
Text Notes 7950 2900 0    50   ~ 0
Dual H-bridge motor driver
$Comp
L Device:R R?
U 1 1 6248DD9B
P 6750 4150
F 0 "R?" V 6543 4150 50  0000 C CNN
F 1 "R" V 6634 4150 50  0000 C CNN
F 2 "" V 6680 4150 50  0001 C CNN
F 3 "~" H 6750 4150 50  0001 C CNN
	1    6750 4150
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 6248FA67
P 6750 4750
F 0 "R?" V 6543 4750 50  0000 C CNN
F 1 "R" V 6634 4750 50  0000 C CNN
F 2 "" V 6680 4750 50  0001 C CNN
F 3 "~" H 6750 4750 50  0001 C CNN
	1    6750 4750
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 6248EAB5
P 6750 4550
F 0 "R?" V 6543 4550 50  0000 C CNN
F 1 "R" V 6634 4550 50  0000 C CNN
F 2 "" V 6680 4550 50  0001 C CNN
F 3 "~" H 6750 4550 50  0001 C CNN
	1    6750 4550
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 6248E36F
P 6750 4350
F 0 "R?" V 6543 4350 50  0000 C CNN
F 1 "R" V 6634 4350 50  0000 C CNN
F 2 "" V 6680 4350 50  0001 C CNN
F 3 "~" H 6750 4350 50  0001 C CNN
	1    6750 4350
	0    1    1    0   
$EndComp
Text Notes 7150 3500 0    50   ~ 0
MTDI should be kept at a low electric level when powering up the module.
$Comp
L Regulator_Switching:LM2596S-5 U?
U 1 1 62498CAB
P 2450 6150
F 0 "U?" H 2450 6517 50  0000 C CNN
F 1 "LM2596S-5" H 2450 6426 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-263-5_TabPin3" H 2500 5900 50  0001 L CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm2596.pdf" H 2450 6150 50  0001 C CNN
	1    2450 6150
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:AMS1117-3.3 U?
U 1 1 6249A219
P 4500 6000
F 0 "U?" H 4500 6242 50  0000 C CNN
F 1 "AMS1117-3.3" H 4500 6151 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 4500 6200 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 4600 5750 50  0001 C CNN
	1    4500 6000
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C?
U 1 1 6249B82E
P 5150 6150
F 0 "C?" H 5265 6196 50  0000 L CNN
F 1 "10u" H 5265 6105 50  0000 L CNN
F 2 "" H 5150 6150 50  0001 C CNN
F 3 "~" H 5150 6150 50  0001 C CNN
	1    5150 6150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6249CDF7
P 3850 6150
F 0 "C?" H 3965 6196 50  0000 L CNN
F 1 "100n" H 3965 6105 50  0000 L CNN
F 2 "" H 3888 6000 50  0001 C CNN
F 3 "~" H 3850 6150 50  0001 C CNN
	1    3850 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 6300 4500 6300
Wire Wire Line
	5150 6300 4500 6300
Connection ~ 4500 6300
Wire Wire Line
	4800 6000 5150 6000
Wire Wire Line
	3850 6000 4200 6000
$EndSCHEMATC
