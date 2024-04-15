EESchema Schematic File Version 4
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Mobrob"
Date "2024-04-14"
Rev "1.0"
Comp "Miika & Essi"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Driver_Motor:L293D U1
U 1 1 661C2C64
P 4250 5600
F 0 "U1" H 3850 6700 50  0000 C CNN
F 1 "L293D" H 3850 6600 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 4500 4850 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/l293.pdf" H 3950 6300 50  0001 C CNN
	1    4250 5600
	-1   0    0    -1  
$EndComp
$Comp
L Device:LED D10
U 1 1 661D084E
P 8300 3250
F 0 "D10" H 8293 2995 50  0000 C CNN
F 1 "LED_STATUS" H 8293 3086 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 8300 3250 50  0001 C CNN
F 3 "~" H 8300 3250 50  0001 C CNN
	1    8300 3250
	-1   0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 661D1761
P 8700 3250
F 0 "R3" V 8493 3250 50  0000 C CNN
F 1 "R" V 8584 3250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 8630 3250 50  0001 C CNN
F 3 "~" H 8700 3250 50  0001 C CNN
	1    8700 3250
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 661DF12F
P 5150 1900
F 0 "R1" H 5220 1946 50  0000 L CNN
F 1 "R" H 5220 1855 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5080 1900 50  0001 C CNN
F 3 "~" H 5150 1900 50  0001 C CNN
	1    5150 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 661DF878
P 5150 1400
F 0 "R2" H 5220 1446 50  0000 L CNN
F 1 "R" H 5220 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5080 1400 50  0001 C CNN
F 3 "~" H 5150 1400 50  0001 C CNN
	1    5150 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D11
U 1 1 661FEBE6
P 3500 1300
F 0 "D11" H 3493 1045 50  0000 C CNN
F 1 "LED_POWER" H 3493 1136 50  0000 C CNN
F 2 "LED_SMD:LED_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3500 1300 50  0001 C CNN
F 3 "~" H 3500 1300 50  0001 C CNN
	1    3500 1300
	-1   0    0    1   
$EndComp
Wire Wire Line
	2850 1300 3150 1300
$Comp
L power:GND #PWR012
U 1 1 662093E7
P 2550 2100
F 0 "#PWR012" H 2550 1850 50  0001 C CNN
F 1 "GND" H 2555 1927 50  0000 C CNN
F 2 "" H 2550 2100 50  0001 C CNN
F 3 "" H 2550 2100 50  0001 C CNN
	1    2550 2100
	1    0    0    -1  
$EndComp
Connection ~ 3150 2000
Wire Wire Line
	3150 1300 3350 1300
Connection ~ 3150 1300
$Comp
L Device:R R4
U 1 1 66213AC9
P 3800 1650
F 0 "R4" H 3870 1696 50  0000 L CNN
F 1 "R" H 3870 1605 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3730 1650 50  0001 C CNN
F 3 "~" H 3800 1650 50  0001 C CNN
	1    3800 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 1300 3800 1300
$Comp
L power:+5V #PWR011
U 1 1 66214998
P 3150 1200
F 0 "#PWR011" H 3150 1050 50  0001 C CNN
F 1 "+5V" H 3165 1373 50  0000 C CNN
F 2 "" H 3150 1200 50  0001 C CNN
F 3 "" H 3150 1200 50  0001 C CNN
	1    3150 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 1300 3150 1200
Wire Wire Line
	3150 2000 3800 2000
Wire Wire Line
	5150 1550 5150 1650
Wire Wire Line
	5600 1650 5150 1650
Connection ~ 5150 1650
Wire Wire Line
	5150 1650 5150 1750
$Comp
L power:+5V #PWR010
U 1 1 66229590
P 5500 1150
F 0 "#PWR010" H 5500 1000 50  0001 C CNN
F 1 "+5V" H 5515 1323 50  0000 C CNN
F 2 "" H 5500 1150 50  0001 C CNN
F 3 "" H 5500 1150 50  0001 C CNN
	1    5500 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 2150 5150 2100
$Comp
L power:GND #PWR09
U 1 1 6622A592
P 5150 2150
F 0 "#PWR09" H 5150 1900 50  0001 C CNN
F 1 "GND" H 5155 1977 50  0000 C CNN
F 2 "" H 5150 2150 50  0001 C CNN
F 3 "" H 5150 2150 50  0001 C CNN
	1    5150 2150
	1    0    0    -1  
$EndComp
Connection ~ 5150 2100
Wire Wire Line
	5150 2100 5150 2050
Wire Wire Line
	5600 1750 5500 1750
Wire Wire Line
	5500 1750 5500 2100
Wire Wire Line
	5150 2100 5500 2100
Wire Wire Line
	5600 1550 5500 1550
Wire Wire Line
	5500 1150 5500 1550
Text GLabel 5100 1100 0    50   Input ~ 0
LHALL_IN
Wire Wire Line
	5150 1100 5150 1250
Wire Wire Line
	5100 1100 5150 1100
$Comp
L Device:R R6
U 1 1 66246416
P 7000 1900
F 0 "R6" H 7070 1946 50  0000 L CNN
F 1 "R" H 7070 1855 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 6930 1900 50  0001 C CNN
F 3 "~" H 7000 1900 50  0001 C CNN
	1    7000 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 6624641C
P 7000 1400
F 0 "R5" H 7070 1446 50  0000 L CNN
F 1 "R" H 7070 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 6930 1400 50  0001 C CNN
F 3 "~" H 7000 1400 50  0001 C CNN
	1    7000 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 1550 7000 1650
Wire Wire Line
	7450 1650 7000 1650
Connection ~ 7000 1650
Wire Wire Line
	7000 1650 7000 1750
$Comp
L power:+5V #PWR014
U 1 1 66246426
P 7350 1150
F 0 "#PWR014" H 7350 1000 50  0001 C CNN
F 1 "+5V" H 7365 1323 50  0000 C CNN
F 2 "" H 7350 1150 50  0001 C CNN
F 3 "" H 7350 1150 50  0001 C CNN
	1    7350 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 2150 7000 2100
$Comp
L power:GND #PWR013
U 1 1 6624642D
P 7000 2150
F 0 "#PWR013" H 7000 1900 50  0001 C CNN
F 1 "GND" H 7005 1977 50  0000 C CNN
F 2 "" H 7000 2150 50  0001 C CNN
F 3 "" H 7000 2150 50  0001 C CNN
	1    7000 2150
	1    0    0    -1  
$EndComp
Connection ~ 7000 2100
Wire Wire Line
	7000 2100 7000 2050
Wire Wire Line
	7450 1750 7350 1750
Wire Wire Line
	7350 1750 7350 2100
Wire Wire Line
	7000 2100 7350 2100
$Comp
L Connector_Generic:Conn_01x03 J7
U 1 1 66246438
P 7650 1650
F 0 "J7" H 7730 1692 50  0000 L CNN
F 1 "RHALL" H 7730 1601 50  0000 L CNN
F 2 "Connector_JST:JST_EH_B3B-EH-A_1x03_P2.50mm_Vertical" H 7650 1650 50  0001 C CNN
F 3 "~" H 7650 1650 50  0001 C CNN
	1    7650 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 1550 7350 1550
Wire Wire Line
	7350 1150 7350 1550
Text GLabel 6950 1100 0    50   Input ~ 0
RHALL_IN
Wire Wire Line
	7000 1100 7000 1250
Wire Wire Line
	6950 1100 7000 1100
$Comp
L power:GND #PWR07
U 1 1 66317BB9
P 4250 6550
F 0 "#PWR07" H 4250 6300 50  0001 C CNN
F 1 "GND" H 4255 6377 50  0000 C CNN
F 2 "" H 4250 6550 50  0001 C CNN
F 3 "" H 4250 6550 50  0001 C CNN
	1    4250 6550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4050 6400 4050 6500
Wire Wire Line
	4050 6500 4150 6500
Wire Wire Line
	4450 6500 4450 6400
Wire Wire Line
	4350 6400 4350 6500
Connection ~ 4350 6500
Wire Wire Line
	4350 6500 4450 6500
Wire Wire Line
	4150 6400 4150 6500
Connection ~ 4150 6500
Wire Wire Line
	4150 6500 4250 6500
Wire Wire Line
	4250 6550 4250 6500
Connection ~ 4250 6500
Wire Wire Line
	4250 6500 4350 6500
$Comp
L power:+5V #PWR08
U 1 1 6632B8DA
P 4950 3950
F 0 "#PWR08" H 4950 3800 50  0001 C CNN
F 1 "+5V" H 4965 4123 50  0000 C CNN
F 2 "" H 4950 3950 50  0001 C CNN
F 3 "" H 4950 3950 50  0001 C CNN
	1    4950 3950
	1    0    0    -1  
$EndComp
Text GLabel 4950 5000 2    50   Input ~ 0
1A
Text GLabel 4950 5200 2    50   Input ~ 0
2A
Text GLabel 4950 5400 2    50   Input ~ 0
EN1,2
Text GLabel 4950 5600 2    50   Input ~ 0
3A
Text GLabel 4950 5800 2    50   Input ~ 0
4A
Text GLabel 4950 6000 2    50   Input ~ 0
EN3,4
Wire Wire Line
	4950 6000 4750 6000
Wire Wire Line
	4950 5800 4750 5800
Wire Wire Line
	4950 5600 4750 5600
Wire Wire Line
	4950 5400 4750 5400
Wire Wire Line
	4950 5200 4750 5200
Wire Wire Line
	4950 5000 4750 5000
Wire Wire Line
	4150 4400 4150 4600
Wire Wire Line
	4350 4400 4350 4600
Wire Wire Line
	8850 3250 9000 3250
$Comp
L power:GND #PWR015
U 1 1 6639C242
P 9000 3500
F 0 "#PWR015" H 9000 3250 50  0001 C CNN
F 1 "GND" H 9005 3327 50  0000 C CNN
F 2 "" H 9000 3500 50  0001 C CNN
F 3 "" H 9000 3500 50  0001 C CNN
	1    9000 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 3250 8550 3250
Wire Wire Line
	9000 3250 9000 3500
Text GLabel 8050 3250 0    50   Input ~ 0
LED_STATUS
Wire Wire Line
	8050 3250 8150 3250
Wire Wire Line
	1950 2000 2550 2000
Wire Wire Line
	1950 1800 1950 2000
Connection ~ 2550 2000
Wire Wire Line
	2550 2000 3150 2000
Wire Wire Line
	3800 1800 3800 2000
Wire Wire Line
	3800 1500 3800 1300
Wire Wire Line
	3150 1800 3150 2000
Wire Wire Line
	3150 1500 3150 1300
Wire Wire Line
	2550 2100 2550 2000
Wire Wire Line
	1950 1500 1950 1300
$Comp
L Regulator_Linear:L7805 U2
U 1 1 661C7417
P 2550 1300
F 0 "U2" H 2550 1542 50  0000 C CNN
F 1 "L7805" H 2550 1451 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 2575 1150 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 2550 1250 50  0001 C CNN
	1    2550 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1600 2550 2000
$Comp
L power:+12V #PWR05
U 1 1 6621BABA
P 950 1200
F 0 "#PWR05" H 950 1050 50  0001 C CNN
F 1 "+12V" H 965 1373 50  0000 C CNN
F 2 "" H 950 1200 50  0001 C CNN
F 3 "" H 950 1200 50  0001 C CNN
	1    950  1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 2100 1050 2000
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 661CE500
P 1050 2300
F 0 "J1" V 922 2380 50  0000 L CNN
F 1 "POWER" V 1013 2380 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 1050 2300 50  0001 C CNN
F 3 "~" H 1050 2300 50  0001 C CNN
	1    1050 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	1050 2000 1950 2000
Connection ~ 1950 2000
$Comp
L Device:CP C1
U 1 1 6652FBC8
P 1950 1650
F 0 "C1" H 2068 1696 50  0000 L CNN
F 1 "0.22uF" H 2068 1605 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 1988 1500 50  0001 C CNN
F 3 "~" H 1950 1650 50  0001 C CNN
	1    1950 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 66535F9A
P 3150 1650
F 0 "C2" H 3268 1696 50  0000 L CNN
F 1 "0.1uF" H 3268 1605 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 3188 1500 50  0001 C CNN
F 3 "~" H 3150 1650 50  0001 C CNN
	1    3150 1650
	1    0    0    -1  
$EndComp
Text GLabel 7700 5400 0    50   Input ~ 0
2A
Text GLabel 7700 5500 0    50   Input ~ 0
4A
Text GLabel 7700 5200 0    50   Input ~ 0
LED_STATUS
Text GLabel 7700 5000 0    50   Input ~ 0
3A
Text GLabel 7700 5100 0    50   Input ~ 0
3,4EN
$Comp
L power:+5V #PWR01
U 1 1 66558C04
P 6950 5600
F 0 "#PWR01" H 6950 5450 50  0001 C CNN
F 1 "+5V" H 6965 5773 50  0000 C CNN
F 2 "" H 6950 5600 50  0001 C CNN
F 3 "" H 6950 5600 50  0001 C CNN
	1    6950 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 5700 6950 5600
$Comp
L power:GND #PWR02
U 1 1 665630A2
P 8500 5850
F 0 "#PWR02" H 8500 5600 50  0001 C CNN
F 1 "GND" H 8505 5677 50  0000 C CNN
F 2 "" H 8500 5850 50  0001 C CNN
F 3 "" H 8500 5850 50  0001 C CNN
	1    8500 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 5500 7800 5500
Wire Wire Line
	7700 5400 7800 5400
Wire Wire Line
	7700 5200 7800 5200
Wire Wire Line
	7700 5100 7800 5100
Wire Wire Line
	7700 5000 7800 5000
Text GLabel 7700 4900 0    50   Input ~ 0
1,2EN
Text GLabel 7700 4800 0    50   Input ~ 0
1A
Wire Wire Line
	6950 5700 7800 5700
Wire Wire Line
	7700 4800 7800 4800
Wire Wire Line
	7700 4900 7800 4900
Wire Wire Line
	1950 1300 2250 1300
Wire Wire Line
	1650 1300 1950 1300
Connection ~ 1950 1300
Wire Wire Line
	1350 1300 950  1300
Wire Wire Line
	950  1300 950  2100
$Comp
L Device:D_Schottky D9
U 1 1 661FA314
P 1500 1300
F 0 "D9" H 1500 1084 50  0000 C CNN
F 1 "D_Schottky" H 1500 1175 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-2_TabPin1" H 1500 1300 50  0001 C CNN
F 3 "https://www.mouser.fi/ProductDetail/Vishay-Semiconductors/VS-3C08EV07T-M3-I?qs=1Kr7Jg1SGW9ydBYhYJ3smQ%3D%3D" H 1500 1300 50  0001 C CNN
	1    1500 1300
	-1   0    0    1   
$EndComp
Wire Wire Line
	950  1200 950  1300
Connection ~ 950  1300
$Comp
L Device:C C4
U 1 1 6660E0C1
P 4650 4150
F 0 "C4" H 4765 4196 50  0000 L CNN
F 1 "0.1uF" H 4765 4105 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W5.0mm_P5.00mm" H 4688 4000 50  0001 C CNN
F 3 "~" H 4650 4150 50  0001 C CNN
	1    4650 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 6660FD28
P 3850 4150
F 0 "C3" H 3965 4196 50  0000 L CNN
F 1 "0.1uF" H 3965 4105 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W5.0mm_P5.00mm" H 3888 4000 50  0001 C CNN
F 3 "~" H 3850 4150 50  0001 C CNN
	1    3850 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 4400 4650 4400
Wire Wire Line
	3850 4300 3850 4400
Wire Wire Line
	3850 4400 4150 4400
Wire Wire Line
	4650 4300 4650 4400
Connection ~ 4650 4400
Wire Wire Line
	4650 4400 4950 4400
Wire Wire Line
	4950 4400 4950 3950
Wire Wire Line
	3850 4000 4250 4000
$Comp
L power:GND #PWR06
U 1 1 6664C003
P 4250 4100
F 0 "#PWR06" H 4250 3850 50  0001 C CNN
F 1 "GND" H 4255 3927 50  0000 C CNN
F 2 "" H 4250 4100 50  0001 C CNN
F 3 "" H 4250 4100 50  0001 C CNN
	1    4250 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 4100 4250 4000
Connection ~ 4250 4000
Wire Wire Line
	4250 4000 4650 4000
$Comp
L Connector_Generic:Conn_01x03 J6
U 1 1 6622413A
P 5800 1650
F 0 "J6" H 5880 1692 50  0000 L CNN
F 1 "LHALL" H 5880 1601 50  0000 L CNN
F 2 "Connector_JST:JST_EH_B3B-EH-A_1x03_P2.50mm_Vertical" H 5800 1650 50  0001 C CNN
F 3 "~" H 5800 1650 50  0001 C CNN
	1    5800 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 6685307D
P 3250 4900
F 0 "#PWR016" H 3250 4650 50  0001 C CNN
F 1 "GND" H 3255 4727 50  0000 C CNN
F 2 "" H 3250 4900 50  0001 C CNN
F 3 "" H 3250 4900 50  0001 C CNN
	1    3250 4900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2350 4450 2250 4450
Wire Wire Line
	2250 4800 2350 4800
$Comp
L Diode:1N4007 D5
U 1 1 66853085
P 3000 4450
F 0 "D5" H 2950 4650 50  0000 L CNN
F 1 "1N4007" H 2850 4550 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3000 4275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3000 4450 50  0001 C CNN
	1    3000 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 4800 3150 4800
Wire Wire Line
	3250 4450 3150 4450
$Comp
L Diode:1N4007 D6
U 1 1 6685308D
P 3000 4800
F 0 "D6" H 2950 5000 50  0000 L CNN
F 1 "1N4007" H 2850 4900 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3000 4625 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3000 4800 50  0001 C CNN
	1    3000 4800
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D2
U 1 1 66853093
P 2500 4800
F 0 "D2" H 2450 5000 50  0000 L CNN
F 1 "1N4007" H 2350 4900 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2500 4625 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2500 4800 50  0001 C CNN
	1    2500 4800
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D1
U 1 1 66853099
P 2500 4450
F 0 "D1" H 2450 4650 50  0000 L CNN
F 1 "1N4007" H 2350 4550 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2500 4275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2500 4450 50  0001 C CNN
	1    2500 4450
	1    0    0    -1  
$EndComp
Text Notes 1550 4950 0    50   ~ 0
Right motor
Wire Wire Line
	3250 4900 3250 4800
$Comp
L power:+12V #PWR03
U 1 1 668530A1
P 2250 4350
F 0 "#PWR03" H 2250 4200 50  0001 C CNN
F 1 "+12V" H 2265 4523 50  0000 C CNN
F 2 "" H 2250 4350 50  0001 C CNN
F 3 "" H 2250 4350 50  0001 C CNN
	1    2250 4350
	-1   0    0    -1  
$EndComp
Connection ~ 3250 4800
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 668530A8
P 1750 4600
F 0 "J2" H 1830 4592 50  0000 L CNN
F 1 "RMOTOR_OUT" H 1830 4501 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 1750 4600 50  0001 C CNN
F 3 "~" H 1750 4600 50  0001 C CNN
	1    1750 4600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2100 4700 1950 4700
Wire Wire Line
	2100 4600 1950 4600
Wire Wire Line
	3250 4450 3250 4800
Wire Wire Line
	2250 4450 2250 4800
Wire Wire Line
	2100 5200 2750 5200
Wire Wire Line
	2650 4800 2750 4800
Wire Wire Line
	2100 4050 2750 4050
Wire Wire Line
	2650 4450 2750 4450
Wire Wire Line
	2100 4050 2100 4600
Wire Wire Line
	2100 4700 2100 5200
Wire Wire Line
	2750 5200 2750 4800
Connection ~ 2750 5200
Connection ~ 2750 4800
Wire Wire Line
	2750 4800 2850 4800
Wire Wire Line
	2750 4450 2750 4050
Connection ~ 2750 4450
Wire Wire Line
	2750 4450 2850 4450
Connection ~ 2750 4050
Wire Wire Line
	2750 4050 3550 4050
Wire Wire Line
	2250 4450 2250 4350
Connection ~ 2250 4450
$Comp
L power:GND #PWR017
U 1 1 66876847
P 3250 6450
F 0 "#PWR017" H 3250 6200 50  0001 C CNN
F 1 "GND" H 3255 6277 50  0000 C CNN
F 2 "" H 3250 6450 50  0001 C CNN
F 3 "" H 3250 6450 50  0001 C CNN
	1    3250 6450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2350 6000 2250 6000
Wire Wire Line
	2250 6350 2350 6350
$Comp
L Diode:1N4007 D7
U 1 1 6687684F
P 3000 6000
F 0 "D7" H 2950 6200 50  0000 L CNN
F 1 "1N4007" H 2850 6100 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3000 5825 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3000 6000 50  0001 C CNN
	1    3000 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 6350 3150 6350
Wire Wire Line
	3250 6000 3150 6000
$Comp
L Diode:1N4007 D8
U 1 1 66876857
P 3000 6350
F 0 "D8" H 2950 6550 50  0000 L CNN
F 1 "1N4007" H 2850 6450 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3000 6175 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3000 6350 50  0001 C CNN
	1    3000 6350
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D4
U 1 1 6687685D
P 2500 6350
F 0 "D4" H 2450 6550 50  0000 L CNN
F 1 "1N4007" H 2350 6450 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2500 6175 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2500 6350 50  0001 C CNN
	1    2500 6350
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D3
U 1 1 66876863
P 2500 6000
F 0 "D3" H 2450 6200 50  0000 L CNN
F 1 "1N4007" H 2350 6100 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2500 5825 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2500 6000 50  0001 C CNN
	1    2500 6000
	1    0    0    -1  
$EndComp
Text Notes 1550 6500 0    50   ~ 0
Right motor
Wire Wire Line
	3250 6450 3250 6350
$Comp
L power:+12V #PWR04
U 1 1 6687686B
P 2250 5900
F 0 "#PWR04" H 2250 5750 50  0001 C CNN
F 1 "+12V" H 2265 6073 50  0000 C CNN
F 2 "" H 2250 5900 50  0001 C CNN
F 3 "" H 2250 5900 50  0001 C CNN
	1    2250 5900
	-1   0    0    -1  
$EndComp
Connection ~ 3250 6350
$Comp
L Connector:Screw_Terminal_01x02 J4
U 1 1 66876872
P 1750 6150
F 0 "J4" H 1830 6142 50  0000 L CNN
F 1 "RMOTOR_OUT" H 1830 6051 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 1750 6150 50  0001 C CNN
F 3 "~" H 1750 6150 50  0001 C CNN
	1    1750 6150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2100 6250 1950 6250
Wire Wire Line
	2100 6150 1950 6150
Wire Wire Line
	3250 6000 3250 6350
Wire Wire Line
	2250 6000 2250 6350
Wire Wire Line
	2100 6750 2750 6750
Wire Wire Line
	2650 6350 2750 6350
Wire Wire Line
	2100 5600 2750 5600
Wire Wire Line
	2650 6000 2750 6000
Wire Wire Line
	2100 5600 2100 6150
Wire Wire Line
	2100 6250 2100 6750
Wire Wire Line
	2750 6750 2750 6350
Connection ~ 2750 6750
Wire Wire Line
	2750 6750 3550 6750
Connection ~ 2750 6350
Wire Wire Line
	2750 6350 2850 6350
Wire Wire Line
	2750 6000 2750 5600
Connection ~ 2750 6000
Wire Wire Line
	2750 6000 2850 6000
Connection ~ 2750 5600
Wire Wire Line
	2250 6000 2250 5900
Connection ~ 2250 6000
Wire Wire Line
	3750 5800 3550 5800
Wire Wire Line
	3550 5800 3550 6750
Wire Wire Line
	2750 5600 3750 5600
Wire Wire Line
	2750 5200 3750 5200
Wire Wire Line
	3750 5000 3550 5000
Wire Wire Line
	3550 5000 3550 4050
$Comp
L Connector:Conn_01x15_Female J5
U 1 1 668ED08B
P 9000 5000
F 0 "J5" H 9028 5026 50  0000 L CNN
F 1 "MCU_ROW2" H 9028 4935 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x15_P2.54mm_Vertical" H 9000 5000 50  0001 C CNN
F 3 "~" H 9000 5000 50  0001 C CNN
	1    9000 5000
	-1   0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR018
U 1 1 66905759
P 10000 5600
F 0 "#PWR018" H 10000 5450 50  0001 C CNN
F 1 "+3.3V" H 10015 5773 50  0000 C CNN
F 2 "" H 10000 5600 50  0001 C CNN
F 3 "" H 10000 5600 50  0001 C CNN
	1    10000 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 5700 10000 5600
Wire Wire Line
	9300 5600 9200 5600
Wire Wire Line
	8500 5800 8500 5850
Wire Wire Line
	8500 5800 9300 5800
Text GLabel 9300 5300 2    50   Input ~ 0
UT_TRIG
Text GLabel 9300 4300 2    50   Input ~ 0
UT_ECHO
Wire Wire Line
	9200 4300 9300 4300
Wire Wire Line
	9200 5300 9300 5300
Wire Wire Line
	9200 5700 10000 5700
Wire Wire Line
	9300 5600 9300 5800
Text GLabel 7700 4500 0    50   Input ~ 0
LHALL_IN
Text GLabel 7700 4400 0    50   Input ~ 0
RHALL_IN
Wire Wire Line
	7700 4400 7800 4400
Wire Wire Line
	7700 4500 7800 4500
Wire Wire Line
	7800 5600 7700 5600
Wire Wire Line
	7700 5600 7700 5800
Wire Wire Line
	7700 5800 8500 5800
Connection ~ 8500 5800
$Comp
L Connector:Conn_01x15_Female J3
U 1 1 6653A81B
P 8000 5000
F 0 "J3" H 8028 5026 50  0000 L CNN
F 1 "MCU_ROW1" H 8028 4935 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x15_P2.54mm_Vertical" H 8000 5000 50  0001 C CNN
F 3 "~" H 8000 5000 50  0001 C CNN
	1    8000 5000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J9
U 1 1 6699FE23
P 10600 1550
F 0 "J9" H 10680 1542 50  0000 L CNN
F 1 "UT" H 10680 1451 50  0000 L CNN
F 2 "Connector_JST:JST_EH_B4B-EH-A_1x04_P2.50mm_Vertical" H 10600 1550 50  0001 C CNN
F 3 "~" H 10600 1550 50  0001 C CNN
	1    10600 1550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR021
U 1 1 669A1046
P 10300 1100
F 0 "#PWR021" H 10300 950 50  0001 C CNN
F 1 "+5V" H 10315 1273 50  0000 C CNN
F 2 "" H 10300 1100 50  0001 C CNN
F 3 "" H 10300 1100 50  0001 C CNN
	1    10300 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 1450 10300 1450
Wire Wire Line
	10300 1450 10300 1100
$Comp
L power:GND #PWR022
U 1 1 669B654A
P 10300 2100
F 0 "#PWR022" H 10300 1850 50  0001 C CNN
F 1 "GND" H 10305 1927 50  0000 C CNN
F 2 "" H 10300 2100 50  0001 C CNN
F 3 "" H 10300 2100 50  0001 C CNN
	1    10300 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 2100 10300 1750
Wire Wire Line
	10300 1750 10400 1750
Text GLabel 10300 1550 0    50   Input ~ 0
UT_TRIG
Text GLabel 10300 1650 0    50   Input ~ 0
UT_ECHO
Wire Wire Line
	10300 1650 10400 1650
Wire Wire Line
	10300 1550 10400 1550
$Comp
L Mechanical:MountingHole H3
U 1 1 669D9DF1
P 6050 7400
F 0 "H3" H 6150 7446 50  0000 L CNN
F 1 "MountingHole" H 6150 7355 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 6050 7400 50  0001 C CNN
F 3 "~" H 6050 7400 50  0001 C CNN
	1    6050 7400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 669E2136
P 6050 7150
F 0 "H2" H 6150 7196 50  0000 L CNN
F 1 "MountingHole" H 6150 7105 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 6050 7150 50  0001 C CNN
F 3 "~" H 6050 7150 50  0001 C CNN
	1    6050 7150
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 669E9112
P 6050 6900
F 0 "H1" H 6150 6946 50  0000 L CNN
F 1 "MountingHole" H 6150 6855 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 6050 6900 50  0001 C CNN
F 3 "~" H 6050 6900 50  0001 C CNN
	1    6050 6900
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J8
U 1 1 66B062F4
P 9200 1600
F 0 "J8" H 9280 1592 50  0000 L CNN
F 1 "IMU" H 9280 1501 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 9200 1600 50  0001 C CNN
F 3 "~" H 9200 1600 50  0001 C CNN
	1    9200 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR020
U 1 1 66B1BD5D
P 8900 1100
F 0 "#PWR020" H 8900 950 50  0001 C CNN
F 1 "+5V" H 8915 1273 50  0000 C CNN
F 2 "" H 8900 1100 50  0001 C CNN
F 3 "" H 8900 1100 50  0001 C CNN
	1    8900 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 1300 8900 1300
Wire Wire Line
	8900 1300 8900 1100
$Comp
L power:GND #PWR019
U 1 1 66B2AC15
P 8450 2150
F 0 "#PWR019" H 8450 1900 50  0001 C CNN
F 1 "GND" H 8455 1977 50  0000 C CNN
F 2 "" H 8450 2150 50  0001 C CNN
F 3 "" H 8450 2150 50  0001 C CNN
	1    8450 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 1400 8450 2150
Text GLabel 8900 1500 0    50   Input ~ 0
IMU_SCL
Text GLabel 8900 1600 0    50   Input ~ 0
IMU_SDA
Wire Wire Line
	8900 1500 9000 1500
Wire Wire Line
	8900 1600 9000 1600
Wire Wire Line
	8450 1400 9000 1400
Text GLabel 9300 4400 2    50   Input ~ 0
IMU_SCL
Text GLabel 9300 4700 2    50   Input ~ 0
IMU_SDA
Wire Wire Line
	9200 4700 9300 4700
Wire Wire Line
	9200 4400 9300 4400
$EndSCHEMATC
