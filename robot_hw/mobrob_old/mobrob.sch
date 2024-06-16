EESchema Schematic File Version 4
LIBS:mobrob-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Mobrob"
Date "2024-04-14"
Rev "1.0"
Comp "Miika & Essi (Group 32)"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R R1
U 1 1 661DF12F
P 5150 1900
F 0 "R1" H 5220 1946 50  0000 L CNN
F 1 "33k" H 5220 1855 50  0000 L CNN
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
F 1 "15k" H 5220 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5080 1400 50  0001 C CNN
F 3 "~" H 5150 1400 50  0001 C CNN
	1    5150 1400
	1    0    0    -1  
$EndComp
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
F 1 "33k" H 7070 1855 50  0000 L CNN
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
F 1 "15k" H 7070 1355 50  0000 L CNN
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
Connection ~ 950  1300
Wire Wire Line
	950  1200 950  1300
Wire Wire Line
	950  1300 950  2100
Connection ~ 1650 1300
Wire Wire Line
	1650 1300 1950 1300
$Comp
L Device:CP C2
U 1 1 66535F9A
P 2850 1650
F 0 "C2" H 2968 1696 50  0000 L CNN
F 1 "0.1uF" H 2968 1605 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 2888 1500 50  0001 C CNN
F 3 "~" H 2850 1650 50  0001 C CNN
	1    2850 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 6652FBC8
P 1650 1650
F 0 "C1" H 1768 1696 50  0000 L CNN
F 1 "0.22uF" H 1768 1605 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 1688 1500 50  0001 C CNN
F 3 "~" H 1650 1650 50  0001 C CNN
	1    1650 1650
	1    0    0    -1  
$EndComp
Connection ~ 1650 2000
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
	1050 2100 1050 2000
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
	2250 1600 2250 2000
$Comp
L Regulator_Linear:L7805 U2
U 1 1 661C7417
P 2250 1300
F 0 "U2" H 2250 1542 50  0000 C CNN
F 1 "L7805" H 2250 1451 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 2275 1150 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 2250 1250 50  0001 C CNN
	1    2250 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1500 1650 1300
Wire Wire Line
	2250 2100 2250 2000
Wire Wire Line
	2850 1500 2850 1300
Wire Wire Line
	2850 1800 2850 2000
Wire Wire Line
	3500 1500 3500 1300
Wire Wire Line
	3500 1800 3500 2000
Wire Wire Line
	2250 2000 2850 2000
Connection ~ 2250 2000
Wire Wire Line
	1650 1800 1650 2000
Wire Wire Line
	1650 2000 2250 2000
Wire Wire Line
	2850 2000 3500 2000
Wire Wire Line
	2850 1300 2850 1200
$Comp
L power:+5V #PWR011
U 1 1 66214998
P 2850 1200
F 0 "#PWR011" H 2850 1050 50  0001 C CNN
F 1 "+5V" H 2865 1373 50  0000 C CNN
F 2 "" H 2850 1200 50  0001 C CNN
F 3 "" H 2850 1200 50  0001 C CNN
	1    2850 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 1300 3500 1300
$Comp
L Device:R R4
U 1 1 66213AC9
P 3500 1650
F 0 "R4" H 3570 1696 50  0000 L CNN
F 1 "150" H 3570 1605 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3430 1650 50  0001 C CNN
F 3 "~" H 3500 1650 50  0001 C CNN
	1    3500 1650
	1    0    0    -1  
$EndComp
Connection ~ 2850 1300
Wire Wire Line
	2850 1300 3050 1300
Connection ~ 2850 2000
$Comp
L power:GND #PWR012
U 1 1 662093E7
P 2250 2100
F 0 "#PWR012" H 2250 1850 50  0001 C CNN
F 1 "GND" H 2255 1927 50  0000 C CNN
F 2 "" H 2250 2100 50  0001 C CNN
F 3 "" H 2250 2100 50  0001 C CNN
	1    2250 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1300 2850 1300
$Comp
L Device:LED D11
U 1 1 661FEBE6
P 3200 1300
F 0 "D11" H 3193 1045 50  0000 C CNN
F 1 "LED_POWER" H 3193 1136 50  0000 C CNN
F 2 "LED_SMD:LED_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3200 1300 50  0001 C CNN
F 3 "~" H 3200 1300 50  0001 C CNN
	1    3200 1300
	-1   0    0    1   
$EndComp
Text GLabel 5150 4800 2    50   Input ~ 0
1,2EN
Text GLabel 5150 5400 2    50   Input ~ 0
3,4EN
Wire Wire Line
	5150 4800 4950 4800
Wire Wire Line
	5150 5400 4950 5400
Wire Wire Line
	4450 3400 4850 3400
Connection ~ 4450 3400
Wire Wire Line
	4450 3500 4450 3400
$Comp
L power:GND #PWR06
U 1 1 6664C003
P 4450 3500
F 0 "#PWR06" H 4450 3250 50  0001 C CNN
F 1 "GND" H 4455 3327 50  0000 C CNN
F 2 "" H 4450 3500 50  0001 C CNN
F 3 "" H 4450 3500 50  0001 C CNN
	1    4450 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 3400 4450 3400
Wire Wire Line
	5150 3800 5150 3350
Wire Wire Line
	4850 3800 5150 3800
Connection ~ 4850 3800
Wire Wire Line
	4850 3700 4850 3800
Wire Wire Line
	4050 3800 4350 3800
Wire Wire Line
	4050 3700 4050 3800
Wire Wire Line
	4550 3800 4850 3800
$Comp
L Device:C C3
U 1 1 6660FD28
P 4050 3550
F 0 "C3" H 4165 3596 50  0000 L CNN
F 1 "0.1uF" H 4165 3505 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W5.0mm_P5.00mm" H 4088 3400 50  0001 C CNN
F 3 "~" H 4050 3550 50  0001 C CNN
	1    4050 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 6660E0C1
P 4850 3550
F 0 "C4" H 4965 3596 50  0000 L CNN
F 1 "0.1uF" H 4965 3505 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W5.0mm_P5.00mm" H 4888 3400 50  0001 C CNN
F 3 "~" H 4850 3550 50  0001 C CNN
	1    4850 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 3800 4550 4000
Wire Wire Line
	4350 3800 4350 4000
Wire Wire Line
	5150 4400 4950 4400
Wire Wire Line
	5150 4600 4950 4600
Wire Wire Line
	5150 5000 4950 5000
Wire Wire Line
	5150 5200 4950 5200
Text GLabel 5150 5200 2    50   Input ~ 0
4A
Text GLabel 5150 5000 2    50   Input ~ 0
3A
Text GLabel 5150 4600 2    50   Input ~ 0
2A
Text GLabel 5150 4400 2    50   Input ~ 0
1A
$Comp
L power:+5V #PWR08
U 1 1 6632B8DA
P 5150 3350
F 0 "#PWR08" H 5150 3200 50  0001 C CNN
F 1 "+5V" H 5165 3523 50  0000 C CNN
F 2 "" H 5150 3350 50  0001 C CNN
F 3 "" H 5150 3350 50  0001 C CNN
	1    5150 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 5900 4550 5900
Connection ~ 4450 5900
Wire Wire Line
	4450 5950 4450 5900
Wire Wire Line
	4350 5900 4450 5900
Connection ~ 4350 5900
Wire Wire Line
	4350 5800 4350 5900
Wire Wire Line
	4550 5900 4650 5900
Connection ~ 4550 5900
Wire Wire Line
	4550 5800 4550 5900
Wire Wire Line
	4650 5900 4650 5800
Wire Wire Line
	4250 5900 4350 5900
Wire Wire Line
	4250 5800 4250 5900
$Comp
L power:GND #PWR07
U 1 1 66317BB9
P 4450 5950
F 0 "#PWR07" H 4450 5700 50  0001 C CNN
F 1 "GND" H 4455 5777 50  0000 C CNN
F 2 "" H 4450 5950 50  0001 C CNN
F 3 "" H 4450 5950 50  0001 C CNN
	1    4450 5950
	-1   0    0    -1  
$EndComp
$Comp
L Driver_Motor:L293D U1
U 1 1 661C2C64
P 4450 5000
F 0 "U1" H 4050 6100 50  0000 C CNN
F 1 "L293D" H 4050 6000 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 4700 4250 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/l293.pdf" H 4150 5700 50  0001 C CNN
	1    4450 5000
	-1   0    0    -1  
$EndComp
$Comp
L Device:LED D10
U 1 1 661D084E
P 8300 3350
F 0 "D10" H 8293 3095 50  0000 C CNN
F 1 "LED_STATUS" H 8293 3186 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 8300 3350 50  0001 C CNN
F 3 "~" H 8300 3350 50  0001 C CNN
	1    8300 3350
	-1   0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 661D1761
P 8700 3350
F 0 "R3" V 8493 3350 50  0000 C CNN
F 1 "150" V 8584 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 8630 3350 50  0001 C CNN
F 3 "~" H 8700 3350 50  0001 C CNN
	1    8700 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	8850 3350 9000 3350
$Comp
L power:GND #PWR015
U 1 1 6639C242
P 9000 3600
F 0 "#PWR015" H 9000 3350 50  0001 C CNN
F 1 "GND" H 9005 3427 50  0000 C CNN
F 2 "" H 9000 3600 50  0001 C CNN
F 3 "" H 9000 3600 50  0001 C CNN
	1    9000 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 3350 8550 3350
Wire Wire Line
	9000 3350 9000 3600
Text GLabel 8050 3350 0    50   Input ~ 0
LED_STATUS
Wire Wire Line
	8050 3350 8150 3350
Text GLabel 7700 5500 0    50   Input ~ 0
2A
Text GLabel 7700 5600 0    50   Input ~ 0
4A
Text GLabel 7700 5300 0    50   Input ~ 0
LED_STATUS
Text GLabel 7700 5100 0    50   Input ~ 0
3A
Text GLabel 7700 5200 0    50   Input ~ 0
3,4EN
$Comp
L power:+5V #PWR01
U 1 1 66558C04
P 6950 5700
F 0 "#PWR01" H 6950 5550 50  0001 C CNN
F 1 "+5V" H 6965 5873 50  0000 C CNN
F 2 "" H 6950 5700 50  0001 C CNN
F 3 "" H 6950 5700 50  0001 C CNN
	1    6950 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 5800 6950 5700
$Comp
L power:GND #PWR02
U 1 1 665630A2
P 8500 5950
F 0 "#PWR02" H 8500 5700 50  0001 C CNN
F 1 "GND" H 8505 5777 50  0000 C CNN
F 2 "" H 8500 5950 50  0001 C CNN
F 3 "" H 8500 5950 50  0001 C CNN
	1    8500 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 5600 7800 5600
Wire Wire Line
	7700 5500 7800 5500
Wire Wire Line
	7700 5300 7800 5300
Wire Wire Line
	7700 5200 7800 5200
Wire Wire Line
	7700 5100 7800 5100
Text GLabel 7700 5000 0    50   Input ~ 0
1,2EN
Text GLabel 7700 4900 0    50   Input ~ 0
1A
Wire Wire Line
	6950 5800 7800 5800
Wire Wire Line
	7700 4900 7800 4900
Wire Wire Line
	7700 5000 7800 5000
$Comp
L Connector:Conn_01x15_Female J5
U 1 1 668ED08B
P 9000 5100
F 0 "J5" H 9028 5126 50  0000 L CNN
F 1 "MCU_ROW2" H 9028 5035 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x15_P2.54mm_Vertical" H 9000 5100 50  0001 C CNN
F 3 "~" H 9000 5100 50  0001 C CNN
	1    9000 5100
	-1   0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR018
U 1 1 66905759
P 10000 5700
F 0 "#PWR018" H 10000 5550 50  0001 C CNN
F 1 "+3.3V" H 10015 5873 50  0000 C CNN
F 2 "" H 10000 5700 50  0001 C CNN
F 3 "" H 10000 5700 50  0001 C CNN
	1    10000 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 5800 10000 5700
Wire Wire Line
	9300 5700 9200 5700
Wire Wire Line
	8500 5900 8500 5950
Wire Wire Line
	8500 5900 9300 5900
Text GLabel 9300 5400 2    50   Input ~ 0
UT_TRIG
Text GLabel 9300 4400 2    50   Input ~ 0
UT_ECHO
Wire Wire Line
	9200 4400 9300 4400
Wire Wire Line
	9200 5400 9300 5400
Wire Wire Line
	9200 5800 10000 5800
Wire Wire Line
	9300 5700 9300 5900
Text GLabel 7700 4600 0    50   Input ~ 0
LHALL_IN
Text GLabel 7700 4500 0    50   Input ~ 0
RHALL_IN
Wire Wire Line
	7700 4500 7800 4500
Wire Wire Line
	7700 4600 7800 4600
Wire Wire Line
	7800 5700 7700 5700
Wire Wire Line
	7700 5700 7700 5900
Wire Wire Line
	7700 5900 8500 5900
Connection ~ 8500 5900
$Comp
L Connector:Conn_01x15_Female J3
U 1 1 6653A81B
P 8000 5100
F 0 "J3" H 8028 5126 50  0000 L CNN
F 1 "MCU_ROW1" H 8028 5035 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x15_P2.54mm_Vertical" H 8000 5100 50  0001 C CNN
F 3 "~" H 8000 5100 50  0001 C CNN
	1    8000 5100
	1    0    0    -1  
$EndComp
Text GLabel 9300 4500 2    50   Input ~ 0
IMU_SCL
Text GLabel 9300 4800 2    50   Input ~ 0
IMU_SDA
Wire Wire Line
	9200 4800 9300 4800
Wire Wire Line
	9200 4500 9300 4500
Wire Wire Line
	1050 2000 1650 2000
Wire Wire Line
	950  1300 1650 1300
Wire Wire Line
	3550 4400 3550 3450
Wire Wire Line
	3550 5200 3550 6150
Connection ~ 2250 5400
Wire Wire Line
	2250 5400 2250 5300
Connection ~ 2750 5000
Wire Wire Line
	2750 5400 2850 5400
Connection ~ 2750 5400
Wire Wire Line
	2750 5400 2750 5000
Wire Wire Line
	2750 5750 2850 5750
Connection ~ 2750 5750
Wire Wire Line
	2750 6150 3550 6150
Connection ~ 2750 6150
Wire Wire Line
	2750 6150 2750 5750
Wire Wire Line
	2100 5650 2100 6150
Wire Wire Line
	2100 5000 2100 5550
Wire Wire Line
	2650 5400 2750 5400
Wire Wire Line
	2100 5000 2750 5000
Wire Wire Line
	2650 5750 2750 5750
Wire Wire Line
	2100 6150 2750 6150
Wire Wire Line
	2250 5400 2250 5750
Wire Wire Line
	3250 5400 3250 5750
Wire Wire Line
	2100 5550 1950 5550
Wire Wire Line
	2100 5650 1950 5650
$Comp
L Connector:Screw_Terminal_01x02 J4
U 1 1 66876872
P 1750 5550
F 0 "J4" H 1830 5542 50  0000 L CNN
F 1 "LMOTOR_OUT" H 1830 5451 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 1750 5550 50  0001 C CNN
F 3 "~" H 1750 5550 50  0001 C CNN
	1    1750 5550
	-1   0    0    -1  
$EndComp
Connection ~ 3250 5750
$Comp
L power:+12V #PWR04
U 1 1 6687686B
P 2250 5300
F 0 "#PWR04" H 2250 5150 50  0001 C CNN
F 1 "+12V" H 2265 5473 50  0000 C CNN
F 2 "" H 2250 5300 50  0001 C CNN
F 3 "" H 2250 5300 50  0001 C CNN
	1    2250 5300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3250 5850 3250 5750
Text Notes 1550 5900 0    50   ~ 0
Left motor
$Comp
L Diode:1N4007 D3
U 1 1 66876863
P 2500 5400
F 0 "D3" H 2450 5600 50  0000 L CNN
F 1 "1N4007" H 2350 5500 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2500 5225 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2500 5400 50  0001 C CNN
	1    2500 5400
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D4
U 1 1 6687685D
P 2500 5750
F 0 "D4" H 2450 5950 50  0000 L CNN
F 1 "1N4007" H 2350 5850 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2500 5575 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2500 5750 50  0001 C CNN
	1    2500 5750
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D8
U 1 1 66876857
P 3000 5750
F 0 "D8" H 2950 5950 50  0000 L CNN
F 1 "1N4007" H 2850 5850 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3000 5575 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3000 5750 50  0001 C CNN
	1    3000 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 5400 3150 5400
Wire Wire Line
	3250 5750 3150 5750
$Comp
L Diode:1N4007 D7
U 1 1 6687684F
P 3000 5400
F 0 "D7" H 2950 5600 50  0000 L CNN
F 1 "1N4007" H 2850 5500 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3000 5225 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3000 5400 50  0001 C CNN
	1    3000 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 5750 2350 5750
Wire Wire Line
	2350 5400 2250 5400
$Comp
L power:GND #PWR017
U 1 1 66876847
P 3250 5850
F 0 "#PWR017" H 3250 5600 50  0001 C CNN
F 1 "GND" H 3255 5677 50  0000 C CNN
F 2 "" H 3250 5850 50  0001 C CNN
F 3 "" H 3250 5850 50  0001 C CNN
	1    3250 5850
	-1   0    0    -1  
$EndComp
Connection ~ 2250 3850
Wire Wire Line
	2250 3850 2250 3750
Wire Wire Line
	2750 3450 3550 3450
Connection ~ 2750 3450
Wire Wire Line
	2750 3850 2850 3850
Connection ~ 2750 3850
Wire Wire Line
	2750 3850 2750 3450
Wire Wire Line
	2750 4200 2850 4200
Connection ~ 2750 4200
Connection ~ 2750 4600
Wire Wire Line
	2750 4600 2750 4200
Wire Wire Line
	2100 4100 2100 4600
Wire Wire Line
	2100 3450 2100 4000
Wire Wire Line
	2650 3850 2750 3850
Wire Wire Line
	2100 3450 2750 3450
Wire Wire Line
	2650 4200 2750 4200
Wire Wire Line
	2100 4600 2750 4600
Wire Wire Line
	2250 3850 2250 4200
Wire Wire Line
	3250 3850 3250 4200
Wire Wire Line
	2100 4000 1950 4000
Wire Wire Line
	2100 4100 1950 4100
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 668530A8
P 1750 4000
F 0 "J2" H 1830 3992 50  0000 L CNN
F 1 "RMOTOR_OUT" H 1830 3901 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 1750 4000 50  0001 C CNN
F 3 "~" H 1750 4000 50  0001 C CNN
	1    1750 4000
	-1   0    0    -1  
$EndComp
Connection ~ 3250 4200
$Comp
L power:+12V #PWR03
U 1 1 668530A1
P 2250 3750
F 0 "#PWR03" H 2250 3600 50  0001 C CNN
F 1 "+12V" H 2265 3923 50  0000 C CNN
F 2 "" H 2250 3750 50  0001 C CNN
F 3 "" H 2250 3750 50  0001 C CNN
	1    2250 3750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3250 4300 3250 4200
Text Notes 1550 4350 0    50   ~ 0
Right motor
$Comp
L Diode:1N4007 D1
U 1 1 66853099
P 2500 3850
F 0 "D1" H 2450 4050 50  0000 L CNN
F 1 "1N4007" H 2350 3950 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2500 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2500 3850 50  0001 C CNN
	1    2500 3850
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D2
U 1 1 66853093
P 2500 4200
F 0 "D2" H 2450 4400 50  0000 L CNN
F 1 "1N4007" H 2350 4300 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 2500 4025 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2500 4200 50  0001 C CNN
	1    2500 4200
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D6
U 1 1 6685308D
P 3000 4200
F 0 "D6" H 2950 4400 50  0000 L CNN
F 1 "1N4007" H 2850 4300 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3000 4025 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3000 4200 50  0001 C CNN
	1    3000 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3850 3150 3850
Wire Wire Line
	3250 4200 3150 4200
$Comp
L Diode:1N4007 D5
U 1 1 66853085
P 3000 3850
F 0 "D5" H 2950 4050 50  0000 L CNN
F 1 "1N4007" H 2850 3950 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3000 3675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3000 3850 50  0001 C CNN
	1    3000 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 4200 2350 4200
Wire Wire Line
	2350 3850 2250 3850
$Comp
L power:GND #PWR016
U 1 1 6685307D
P 3250 4300
F 0 "#PWR016" H 3250 4050 50  0001 C CNN
F 1 "GND" H 3255 4127 50  0000 C CNN
F 2 "" H 3250 4300 50  0001 C CNN
F 3 "" H 3250 4300 50  0001 C CNN
	1    3250 4300
	-1   0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0101
U 1 1 663774DA
P 3750 3350
F 0 "#PWR0101" H 3750 3200 50  0001 C CNN
F 1 "+12V" H 3765 3523 50  0000 C CNN
F 2 "" H 3750 3350 50  0001 C CNN
F 3 "" H 3750 3350 50  0001 C CNN
	1    3750 3350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3750 3350 3750 3800
Wire Wire Line
	3750 3800 4050 3800
Connection ~ 4050 3800
Wire Wire Line
	3550 4400 3950 4400
Wire Wire Line
	2750 4600 3950 4600
Wire Wire Line
	2750 5000 3950 5000
Wire Wire Line
	3550 5200 3950 5200
$EndSCHEMATC