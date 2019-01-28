EESchema Schematic File Version 4
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
L power:GND #PWR0101
U 1 1 5C4EE4E1
P 1850 2900
F 0 "#PWR0101" H 1850 2650 50  0001 C CNN
F 1 "GND" H 1855 2727 50  0000 C CNN
F 2 "" H 1850 2900 50  0001 C CNN
F 3 "" H 1850 2900 50  0001 C CNN
	1    1850 2900
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0102
U 1 1 5C4EE50A
P 1600 2050
F 0 "#PWR0102" H 1600 1900 50  0001 C CNN
F 1 "+3.3V" V 1615 2178 50  0000 L CNN
F 2 "" H 1600 2050 50  0001 C CNN
F 3 "" H 1600 2050 50  0001 C CNN
	1    1600 2050
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R_Oil_Temp1
U 1 1 5C4EE56E
P 1850 2200
F 0 "R_Oil_Temp1" H 1920 2246 50  0000 L CNN
F 1 "1K" H 1920 2155 50  0000 L CNN
F 2 "" V 1780 2200 50  0001 C CNN
F 3 "~" H 1850 2200 50  0001 C CNN
	1    1850 2200
	1    0    0    -1  
$EndComp
Text GLabel 2400 2400 2    50   Input ~ 0
PA3
$Comp
L Device:R_Variable ERR2081_2
U 1 1 5C4EE786
P 1850 2600
F 0 "ERR2081_2" H 1978 2646 50  0000 L CNN
F 1 "R_Variable" H 1978 2555 50  0000 L CNN
F 2 "" V 1780 2600 50  0001 C CNN
F 3 "~" H 1850 2600 50  0001 C CNN
	1    1850 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 2900 1850 2750
Wire Wire Line
	1850 2350 1850 2400
Wire Wire Line
	2400 2400 1850 2400
Connection ~ 1850 2400
Wire Wire Line
	1850 2400 1850 2450
Wire Wire Line
	1600 2050 1850 2050
$Comp
L MCU_Module:Maple_Mini A1
U 1 1 5C4EE966
P 9600 2000
F 0 "A1" H 9600 814 50  0000 C CNN
F 1 "Maple_Mini" H 9600 723 50  0000 C CNN
F 2 "Module:Maple_Mini" H 9650 950 50  0001 L CNN
F 3 "http://docs.leaflabs.com/static.leaflabs.com/pub/leaflabs/maple-docs/0.0.12/hardware/maple-mini.html" H 9650 0   50  0001 L CNN
	1    9600 2000
	1    0    0    -1  
$EndComp
Text GLabel 8600 1800 0    50   Input ~ 0
PA4
Wire Wire Line
	8800 1800 8600 1800
$Comp
L power:GND #PWR0103
U 1 1 5C4EF168
P 1850 1600
F 0 "#PWR0103" H 1850 1350 50  0001 C CNN
F 1 "GND" H 1855 1427 50  0000 C CNN
F 2 "" H 1850 1600 50  0001 C CNN
F 3 "" H 1850 1600 50  0001 C CNN
	1    1850 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0104
U 1 1 5C4EF16E
P 1600 750
F 0 "#PWR0104" H 1600 600 50  0001 C CNN
F 1 "+3.3V" V 1615 878 50  0000 L CNN
F 2 "" H 1600 750 50  0001 C CNN
F 3 "" H 1600 750 50  0001 C CNN
	1    1600 750 
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R_Coolant_Temp1
U 1 1 5C4EF174
P 1850 900
F 0 "R_Coolant_Temp1" H 1920 946 50  0000 L CNN
F 1 "1K" H 1920 855 50  0000 L CNN
F 2 "" V 1780 900 50  0001 C CNN
F 3 "~" H 1850 900 50  0001 C CNN
	1    1850 900 
	1    0    0    -1  
$EndComp
Text GLabel 2400 1100 2    50   Input ~ 0
PA4
$Comp
L Device:R_Variable ERR2081_1
U 1 1 5C4EF17C
P 1850 1300
F 0 "ERR2081_1" H 1978 1346 50  0000 L CNN
F 1 "R_Variable" H 1978 1255 50  0000 L CNN
F 2 "" V 1780 1300 50  0001 C CNN
F 3 "~" H 1850 1300 50  0001 C CNN
	1    1850 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 1600 1850 1450
Wire Wire Line
	1850 1050 1850 1100
Wire Wire Line
	2400 1100 1850 1100
Connection ~ 1850 1100
Wire Wire Line
	1850 1100 1850 1150
Wire Wire Line
	1600 750  1850 750 
Text GLabel 8600 1900 0    50   Input ~ 0
PA3
Wire Wire Line
	8600 1900 8800 1900
$Comp
L power:GND #PWR0105
U 1 1 5C4EF45E
P 1850 4400
F 0 "#PWR0105" H 1850 4150 50  0001 C CNN
F 1 "GND" H 1855 4227 50  0000 C CNN
F 2 "" H 1850 4400 50  0001 C CNN
F 3 "" H 1850 4400 50  0001 C CNN
	1    1850 4400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 5C4EF491
P 1600 3350
F 0 "#PWR0106" H 1600 3200 50  0001 C CNN
F 1 "+5V" V 1615 3478 50  0000 L CNN
F 2 "" H 1600 3350 50  0001 C CNN
F 3 "" H 1600 3350 50  0001 C CNN
	1    1600 3350
	0    -1   -1   0   
$EndComp
$Comp
L Sensor_Pressure:40PC100G Oil_Pressure_Sensor1
U 1 1 5C4EF58E
P 1850 3800
F 0 "Oil_Pressure_Sensor1" H 1420 3846 50  0000 R CNN
F 1 "100Psi Transducer" H 1420 3755 50  0000 R CNN
F 2 "" H 1950 3800 50  0001 C CNN
F 3 "http://www.honeywellscportal.com//index.php?ci_id=138832" H 1950 3800 50  0001 C CNN
	1    1850 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 4400 1850 4100
$Comp
L Device:R R_Oil_Press_Div2
U 1 1 5C4EF7E5
P 3150 4150
F 0 "R_Oil_Press_Div2" H 3220 4196 50  0000 L CNN
F 1 "20K" H 3220 4105 50  0000 L CNN
F 2 "" V 3080 4150 50  0001 C CNN
F 3 "~" H 3150 4150 50  0001 C CNN
	1    3150 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R_Oil_Press_Div1
U 1 1 5C4EF82D
P 2650 3800
F 0 "R_Oil_Press_Div1" V 2443 3800 50  0000 C CNN
F 1 "10K" V 2534 3800 50  0000 C CNN
F 2 "" V 2580 3800 50  0001 C CNN
F 3 "~" H 2650 3800 50  0001 C CNN
	1    2650 3800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5C4EFA5F
P 3150 4400
F 0 "#PWR0107" H 3150 4150 50  0001 C CNN
F 1 "GND" H 3155 4227 50  0000 C CNN
F 2 "" H 3150 4400 50  0001 C CNN
F 3 "" H 3150 4400 50  0001 C CNN
	1    3150 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 4400 3150 4300
Wire Wire Line
	1600 3350 1850 3350
Wire Wire Line
	1850 3350 1850 3500
Text GLabel 3150 3500 2    50   Input ~ 0
PA2
Wire Wire Line
	3150 3500 3150 3800
Wire Wire Line
	2250 3800 2500 3800
Wire Wire Line
	2800 3800 3150 3800
Connection ~ 3150 3800
Wire Wire Line
	3150 3800 3150 4000
$Comp
L power:GND #PWR0108
U 1 1 5C4F191A
P 1850 5700
F 0 "#PWR0108" H 1850 5450 50  0001 C CNN
F 1 "GND" H 1855 5527 50  0000 C CNN
F 2 "" H 1850 5700 50  0001 C CNN
F 3 "" H 1850 5700 50  0001 C CNN
	1    1850 5700
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0109
U 1 1 5C4F1920
P 1600 4850
F 0 "#PWR0109" H 1600 4700 50  0001 C CNN
F 1 "+3.3V" V 1615 4978 50  0000 L CNN
F 2 "" H 1600 4850 50  0001 C CNN
F 3 "" H 1600 4850 50  0001 C CNN
	1    1600 4850
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R_Transfer_Box_Temp1
U 1 1 5C4F1926
P 1850 5000
F 0 "R_Transfer_Box_Temp1" H 1920 5046 50  0000 L CNN
F 1 "1K" H 1920 4955 50  0000 L CNN
F 2 "" V 1780 5000 50  0001 C CNN
F 3 "~" H 1850 5000 50  0001 C CNN
	1    1850 5000
	1    0    0    -1  
$EndComp
Text GLabel 2400 5200 2    50   Input ~ 0
PA1
$Comp
L Device:R_Variable ERR2081
U 1 1 5C4F192E
P 1850 5400
F 0 "ERR2081" H 1978 5446 50  0000 L CNN
F 1 "R_Variable" H 1978 5355 50  0000 L CNN
F 2 "" V 1780 5400 50  0001 C CNN
F 3 "~" H 1850 5400 50  0001 C CNN
	1    1850 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 5700 1850 5550
Wire Wire Line
	1850 5150 1850 5200
Wire Wire Line
	2400 5200 1850 5200
Connection ~ 1850 5200
Wire Wire Line
	1850 5200 1850 5250
Wire Wire Line
	1600 4850 1850 4850
Text GLabel 8600 2000 0    50   Input ~ 0
PA2
Wire Wire Line
	8600 2000 8800 2000
Text GLabel 8600 2100 0    50   Input ~ 0
PA1
Wire Wire Line
	8600 2100 8800 2100
$Comp
L power:GND #PWR0110
U 1 1 5C4F339A
P 1850 7150
F 0 "#PWR0110" H 1850 6900 50  0001 C CNN
F 1 "GND" H 1855 6977 50  0000 C CNN
F 2 "" H 1850 7150 50  0001 C CNN
F 3 "" H 1850 7150 50  0001 C CNN
	1    1850 7150
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0111
U 1 1 5C4F33A0
P 1600 6100
F 0 "#PWR0111" H 1600 5950 50  0001 C CNN
F 1 "+12V" V 1615 6228 50  0000 L CNN
F 2 "" H 1600 6100 50  0001 C CNN
F 3 "" H 1600 6100 50  0001 C CNN
	1    1600 6100
	0    -1   -1   0   
$EndComp
$Comp
L Sensor_Pressure:40PC100G Boost_Sensor1
U 1 1 5C4F33A6
P 1850 6550
F 0 "Boost_Sensor1" H 1420 6596 50  0000 R CNN
F 1 "-1 to 4 Bar" H 1420 6505 50  0000 R CNN
F 2 "" H 1950 6550 50  0001 C CNN
F 3 "http://www.honeywellscportal.com//index.php?ci_id=138832" H 1950 6550 50  0001 C CNN
	1    1850 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 7150 1850 6850
$Comp
L Device:R R_Boost_Div2
U 1 1 5C4F33AE
P 3150 6900
F 0 "R_Boost_Div2" H 3220 6946 50  0000 L CNN
F 1 "20K" H 3220 6855 50  0000 L CNN
F 2 "" V 3080 6900 50  0001 C CNN
F 3 "~" H 3150 6900 50  0001 C CNN
	1    3150 6900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R_Boost_Div1
U 1 1 5C4F33B5
P 2650 6550
F 0 "R_Boost_Div1" V 2443 6550 50  0000 C CNN
F 1 "10K" V 2534 6550 50  0000 C CNN
F 2 "" V 2580 6550 50  0001 C CNN
F 3 "~" H 2650 6550 50  0001 C CNN
	1    2650 6550
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5C4F33BC
P 3150 7150
F 0 "#PWR0112" H 3150 6900 50  0001 C CNN
F 1 "GND" H 3155 6977 50  0000 C CNN
F 2 "" H 3150 7150 50  0001 C CNN
F 3 "" H 3150 7150 50  0001 C CNN
	1    3150 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 7150 3150 7050
Wire Wire Line
	1600 6100 1850 6100
Wire Wire Line
	1850 6100 1850 6250
Text GLabel 3150 6250 2    50   Input ~ 0
PA0
Wire Wire Line
	3150 6250 3150 6550
Wire Wire Line
	2250 6550 2500 6550
Wire Wire Line
	2800 6550 3150 6550
Connection ~ 3150 6550
Wire Wire Line
	3150 6550 3150 6750
Text GLabel 8600 2200 0    50   Input ~ 0
PA0
Wire Wire Line
	8600 2200 8800 2200
$Comp
L Connector_Generic:Conn_01x07 SSD_1306_OLED1
U 1 1 5C4F702E
P 3450 1150
F 0 "SSD_1306_OLED1" H 3370 625 50  0000 C CNN
F 1 "1" H 3370 716 50  0000 C CNN
F 2 "" H 3450 1150 50  0001 C CNN
F 3 "~" H 3450 1150 50  0001 C CNN
	1    3450 1150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 5C4F7F60
P 4400 1450
F 0 "#PWR0113" H 4400 1200 50  0001 C CNN
F 1 "GND" H 4405 1277 50  0000 C CNN
F 2 "" H 4400 1450 50  0001 C CNN
F 3 "" H 4400 1450 50  0001 C CNN
	1    4400 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0114
U 1 1 5C4F8521
P 4400 1350
F 0 "#PWR0114" H 4400 1200 50  0001 C CNN
F 1 "+3.3V" H 4415 1523 50  0000 C CNN
F 2 "" H 4400 1350 50  0001 C CNN
F 3 "" H 4400 1350 50  0001 C CNN
	1    4400 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 1350 4400 1350
Text GLabel 3750 1150 2    50   Input ~ 0
MOSI_1
Text GLabel 3750 1250 2    50   Input ~ 0
SCK_1
Text GLabel 3750 950  2    50   Input ~ 0
OLED_DC
Text GLabel 3750 1050 2    50   Input ~ 0
OLED_RESET
Text GLabel 3750 850  2    50   Input ~ 0
OLED_CS
Wire Wire Line
	3650 850  3750 850 
Wire Wire Line
	3650 950  3750 950 
Wire Wire Line
	3650 1050 3750 1050
Wire Wire Line
	3650 1150 3750 1150
Wire Wire Line
	3650 1250 3750 1250
Text GLabel 8600 1500 0    50   Input ~ 0
MOSI_1
Wire Wire Line
	8600 1500 8800 1500
Text GLabel 8600 1700 0    50   Input ~ 0
SCK_1
Wire Wire Line
	8600 1700 8800 1700
Text GLabel 10500 1600 2    50   Input ~ 0
OLED_DC
Wire Wire Line
	10400 1600 10500 1600
Text GLabel 10500 1500 2    50   Input ~ 0
OLED_RESET
Wire Wire Line
	10400 1500 10500 1500
Text GLabel 10500 1300 2    50   Input ~ 0
OLED_CS
Wire Wire Line
	10400 1300 10500 1300
$Comp
L Connector_Generic:Conn_01x06 MicroSD1
U 1 1 5C505156
P 5000 1150
F 0 "MicroSD1" H 4920 625 50  0000 C CNN
F 1 "1" H 4920 716 50  0000 C CNN
F 2 "" H 5000 1150 50  0001 C CNN
F 3 "~" H 5000 1150 50  0001 C CNN
	1    5000 1150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5C50515D
P 5950 900
F 0 "#PWR0115" H 5950 650 50  0001 C CNN
F 1 "GND" H 5955 727 50  0000 C CNN
F 2 "" H 5950 900 50  0001 C CNN
F 3 "" H 5950 900 50  0001 C CNN
	1    5950 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 850  5950 900 
$Comp
L power:+3.3V #PWR0116
U 1 1 5C505164
P 5950 1350
F 0 "#PWR0116" H 5950 1200 50  0001 C CNN
F 1 "+3.3V" H 5965 1523 50  0000 C CNN
F 2 "" H 5950 1350 50  0001 C CNN
F 3 "" H 5950 1350 50  0001 C CNN
	1    5950 1350
	-1   0    0    1   
$EndComp
Wire Wire Line
	5200 1350 5950 1350
Text GLabel 5300 1150 2    50   Input ~ 0
MOSI_1
Text GLabel 5300 1050 2    50   Input ~ 0
SCK_1
Wire Wire Line
	5200 950  5300 950 
Wire Wire Line
	5200 1050 5300 1050
Wire Wire Line
	5200 1150 5300 1150
Wire Wire Line
	5200 1250 5300 1250
Text GLabel 5300 950  2    50   Input ~ 0
MISO_1
Text GLabel 8600 1600 0    50   Input ~ 0
MISO_1
Wire Wire Line
	8600 1600 8800 1600
Wire Wire Line
	5200 850  5950 850 
Wire Wire Line
	3650 1450 4400 1450
Text GLabel 5300 1250 2    50   Input ~ 0
SD_CS
Text GLabel 10500 2300 2    50   Input ~ 0
SD_CS
Wire Wire Line
	10400 2300 10500 2300
$Comp
L power:GND #PWR0117
U 1 1 5C51B3EA
P 9600 3450
F 0 "#PWR0117" H 9600 3200 50  0001 C CNN
F 1 "GND" H 9605 3277 50  0000 C CNN
F 2 "" H 9600 3450 50  0001 C CNN
F 3 "" H 9600 3450 50  0001 C CNN
	1    9600 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 3100 9600 3450
NoConn ~ 9700 900 
NoConn ~ 8800 2700
$Comp
L power:GND #PWR0118
U 1 1 5C51F680
P 8700 3050
F 0 "#PWR0118" H 8700 2800 50  0001 C CNN
F 1 "GND" H 8705 2877 50  0000 C CNN
F 2 "" H 8700 3050 50  0001 C CNN
F 3 "" H 8700 3050 50  0001 C CNN
	1    8700 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 2900 8700 2900
Wire Wire Line
	8700 2900 8700 3050
$Comp
L power:+3.3V #PWR0119
U 1 1 5C520482
P 8500 2800
F 0 "#PWR0119" H 8500 2650 50  0001 C CNN
F 1 "+3.3V" H 8515 2973 50  0000 C CNN
F 2 "" H 8500 2800 50  0001 C CNN
F 3 "" H 8500 2800 50  0001 C CNN
	1    8500 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 2800 8800 2800
$Comp
L power:+3.3V #PWR0120
U 1 1 5C521320
P 9300 750
F 0 "#PWR0120" H 9300 600 50  0001 C CNN
F 1 "+3.3V" H 9315 923 50  0000 C CNN
F 2 "" H 9300 750 50  0001 C CNN
F 3 "" H 9300 750 50  0001 C CNN
	1    9300 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 750  9500 750 
Wire Wire Line
	9500 750  9500 900 
$Comp
L power:+5V #PWR0121
U 1 1 5C52227B
P 9600 750
F 0 "#PWR0121" H 9600 600 50  0001 C CNN
F 1 "+5V" H 9615 923 50  0000 C CNN
F 2 "" H 9600 750 50  0001 C CNN
F 3 "" H 9600 750 50  0001 C CNN
	1    9600 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 750  9600 900 
NoConn ~ 10400 2800
$Comp
L Sensor_Temperature:MAX31856 U1
U 1 1 5C525536
P 5450 3050
F 0 "U1" H 5450 3828 50  0000 C CNN
F 1 "MAX31856" H 5450 3737 50  0000 C CNN
F 2 "Package_SO:TSSOP-14_4.4x5mm_P0.65mm" H 5600 2500 50  0001 L CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX31856.pdf" H 5400 3250 50  0001 C CNN
	1    5450 3050
	1    0    0    -1  
$EndComp
NoConn ~ 5950 2750
NoConn ~ 5950 2850
$Comp
L power:GND #PWR0122
U 1 1 5C527501
P 5350 3950
F 0 "#PWR0122" H 5350 3700 50  0001 C CNN
F 1 "GND" H 5355 3777 50  0000 C CNN
F 2 "" H 5350 3950 50  0001 C CNN
F 3 "" H 5350 3950 50  0001 C CNN
	1    5350 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3650 5350 3950
Wire Wire Line
	5550 3650 5550 3950
Wire Wire Line
	5550 3950 5350 3950
Connection ~ 5350 3950
$Comp
L power:+3.3V #PWR0123
U 1 1 5C5295D3
P 6350 2100
F 0 "#PWR0123" H 6350 1950 50  0001 C CNN
F 1 "+3.3V" H 6365 2273 50  0000 C CNN
F 2 "" H 6350 2100 50  0001 C CNN
F 3 "" H 6350 2100 50  0001 C CNN
	1    6350 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 2450 5550 2100
Wire Wire Line
	5550 2100 6350 2100
Wire Wire Line
	5350 2450 5350 2100
Wire Wire Line
	5350 2100 5550 2100
Connection ~ 5550 2100
Text GLabel 6050 3050 2    50   Input ~ 0
MAX_CS
Wire Wire Line
	5950 3050 6050 3050
Text GLabel 10500 2700 2    50   Input ~ 0
MAX_CS
Wire Wire Line
	10400 2700 10500 2700
Text GLabel 6050 3150 2    50   Input ~ 0
SCK_2
Wire Wire Line
	5950 3150 6050 3150
Text GLabel 10500 2600 2    50   Input ~ 0
SCK_2
Wire Wire Line
	10400 2600 10500 2600
Text GLabel 6050 3350 2    50   Input ~ 0
MOSI_2
Wire Wire Line
	5950 3350 6050 3350
Text GLabel 10500 2400 2    50   Input ~ 0
MOSI_2
Wire Wire Line
	10400 2400 10500 2400
Text GLabel 6050 3250 2    50   Input ~ 0
MISO_2
Wire Wire Line
	5950 3250 6050 3250
Text GLabel 10500 2500 2    50   Input ~ 0
MISO_2
Wire Wire Line
	10400 2500 10500 2500
$Comp
L Device:C C1
U 1 1 5C53BFC4
P 4250 2950
F 0 "C1" H 4365 2996 50  0000 L CNN
F 1 "0.1uF" H 4365 2905 50  0000 L CNN
F 2 "" H 4288 2800 50  0001 C CNN
F 3 "~" H 4250 2950 50  0001 C CNN
	1    4250 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 3050 4650 3050
Wire Wire Line
	4650 3050 4650 3150
Wire Wire Line
	4650 3300 4250 3300
Wire Wire Line
	4250 3300 4250 3100
Wire Wire Line
	4950 2950 4650 2950
Wire Wire Line
	4650 2950 4650 2600
Wire Wire Line
	4650 2600 4250 2600
Wire Wire Line
	4250 2600 4250 2800
$Comp
L Device:Thermocouple TC1
U 1 1 5C53FBE5
P 3600 2900
F 0 "TC1" H 3571 3225 50  0000 C CNN
F 1 "Thermocouple" H 3571 3134 50  0000 C CNN
F 2 "" H 3025 2950 50  0001 C CNN
F 3 "~" H 3025 2950 50  0001 C CNN
	1    3600 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 2800 3900 2800
Wire Wire Line
	3900 2800 3900 2600
Wire Wire Line
	3900 2600 4250 2600
Connection ~ 4250 2600
Wire Wire Line
	3700 3000 3900 3000
Wire Wire Line
	3900 3000 3900 3300
Wire Wire Line
	3900 3300 4250 3300
Connection ~ 4250 3300
$Comp
L Device:C C2
U 1 1 5C54408B
P 5050 2100
F 0 "C2" V 4798 2100 50  0000 C CNN
F 1 "0.1uF" V 4889 2100 50  0000 C CNN
F 2 "" H 5088 1950 50  0001 C CNN
F 3 "~" H 5050 2100 50  0001 C CNN
	1    5050 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	5350 2100 5200 2100
Connection ~ 5350 2100
$Comp
L Device:C C3
U 1 1 5C548C47
P 4650 2450
F 0 "C3" H 4765 2496 50  0000 L CNN
F 1 "0.01uF" H 4765 2405 50  0000 L CNN
F 2 "" H 4688 2300 50  0001 C CNN
F 3 "~" H 4650 2450 50  0001 C CNN
	1    4650 2450
	1    0    0    -1  
$EndComp
Connection ~ 4650 2600
$Comp
L Device:C C4
U 1 1 5C548CBD
P 4650 3450
F 0 "C4" H 4765 3496 50  0000 L CNN
F 1 "0.01uF" H 4765 3405 50  0000 L CNN
F 2 "" H 4688 3300 50  0001 C CNN
F 3 "~" H 4650 3450 50  0001 C CNN
	1    4650 3450
	1    0    0    -1  
$EndComp
Connection ~ 4650 3300
$Comp
L power:GND #PWR0124
U 1 1 5C548DB2
P 4650 3600
F 0 "#PWR0124" H 4650 3350 50  0001 C CNN
F 1 "GND" H 4655 3427 50  0000 C CNN
F 2 "" H 4650 3600 50  0001 C CNN
F 3 "" H 4650 3600 50  0001 C CNN
	1    4650 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0125
U 1 1 5C54D81C
P 4500 2100
F 0 "#PWR0125" H 4500 1850 50  0001 C CNN
F 1 "GND" V 4505 1972 50  0000 R CNN
F 2 "" H 4500 2100 50  0001 C CNN
F 3 "" H 4500 2100 50  0001 C CNN
	1    4500 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	4650 2300 4650 2100
Wire Wire Line
	4650 2100 4900 2100
Wire Wire Line
	4500 2100 4650 2100
Connection ~ 4650 2100
$Comp
L Switch:SW_Push LEFTBUT1
U 1 1 5C55514E
P 4600 5100
F 0 "LEFTBUT1" H 4600 5385 50  0000 C CNN
F 1 "SW_Push" H 4600 5294 50  0000 C CNN
F 2 "" H 4600 5300 50  0001 C CNN
F 3 "" H 4600 5300 50  0001 C CNN
	1    4600 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0126
U 1 1 5C55537A
P 4400 5100
F 0 "#PWR0126" H 4400 4850 50  0001 C CNN
F 1 "GND" H 4405 4927 50  0000 C CNN
F 2 "" H 4400 5100 50  0001 C CNN
F 3 "" H 4400 5100 50  0001 C CNN
	1    4400 5100
	1    0    0    -1  
$EndComp
Text GLabel 4800 5100 2    50   Input ~ 0
PC15
Text GLabel 8600 2300 0    50   Input ~ 0
PC15
Wire Wire Line
	8800 2300 8600 2300
$Comp
L Switch:SW_Push SELBUT1
U 1 1 5C55CD0A
P 5400 5100
F 0 "SELBUT1" H 5400 5385 50  0000 C CNN
F 1 "SW_Push" H 5400 5294 50  0000 C CNN
F 2 "" H 5400 5300 50  0001 C CNN
F 3 "" H 5400 5300 50  0001 C CNN
	1    5400 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0127
U 1 1 5C55CD11
P 5200 5100
F 0 "#PWR0127" H 5200 4850 50  0001 C CNN
F 1 "GND" H 5205 4927 50  0000 C CNN
F 2 "" H 5200 5100 50  0001 C CNN
F 3 "" H 5200 5100 50  0001 C CNN
	1    5200 5100
	1    0    0    -1  
$EndComp
Text GLabel 5600 5100 2    50   Input ~ 0
PC13
Text GLabel 8600 2500 0    50   Input ~ 0
PC13
Wire Wire Line
	8600 2500 8800 2500
$Comp
L Switch:SW_Push RIGHTBUT1
U 1 1 5C569789
P 6200 5100
F 0 "RIGHTBUT1" H 6200 5385 50  0000 C CNN
F 1 "SW_Push" H 6200 5294 50  0000 C CNN
F 2 "" H 6200 5300 50  0001 C CNN
F 3 "" H 6200 5300 50  0001 C CNN
	1    6200 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0128
U 1 1 5C569790
P 6000 5100
F 0 "#PWR0128" H 6000 4850 50  0001 C CNN
F 1 "GND" H 6005 4927 50  0000 C CNN
F 2 "" H 6000 5100 50  0001 C CNN
F 3 "" H 6000 5100 50  0001 C CNN
	1    6000 5100
	1    0    0    -1  
$EndComp
Text GLabel 6400 5100 2    50   Input ~ 0
PB7
Text GLabel 10500 1100 2    50   Input ~ 0
PB7
Wire Wire Line
	10500 1100 10400 1100
$Comp
L Switch:SW_Push UPBUT1
U 1 1 5C57263C
P 7000 4750
F 0 "UPBUT1" H 7000 5035 50  0000 C CNN
F 1 "SW_Push" H 7000 4944 50  0000 C CNN
F 2 "" H 7000 4950 50  0001 C CNN
F 3 "" H 7000 4950 50  0001 C CNN
	1    7000 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0129
U 1 1 5C572643
P 6800 4750
F 0 "#PWR0129" H 6800 4500 50  0001 C CNN
F 1 "GND" H 6805 4577 50  0000 C CNN
F 2 "" H 6800 4750 50  0001 C CNN
F 3 "" H 6800 4750 50  0001 C CNN
	1    6800 4750
	1    0    0    -1  
$EndComp
Text GLabel 7200 4750 2    50   Input ~ 0
PC14
Text GLabel 8600 2400 0    50   Input ~ 0
PC14
Wire Wire Line
	8600 2400 8800 2400
$Comp
L Switch:SW_Push DOWNBUT1
U 1 1 5C57D8A1
P 7000 5400
F 0 "DOWNBUT1" H 7000 5685 50  0000 C CNN
F 1 "SW_Push" H 7000 5594 50  0000 C CNN
F 2 "" H 7000 5600 50  0001 C CNN
F 3 "" H 7000 5600 50  0001 C CNN
	1    7000 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0130
U 1 1 5C57D8A8
P 6800 5400
F 0 "#PWR0130" H 6800 5150 50  0001 C CNN
F 1 "GND" H 6805 5227 50  0000 C CNN
F 2 "" H 6800 5400 50  0001 C CNN
F 3 "" H 6800 5400 50  0001 C CNN
	1    6800 5400
	1    0    0    -1  
$EndComp
Text GLabel 7200 5400 2    50   Input ~ 0
PB6
Text GLabel 10500 1200 2    50   Input ~ 0
PB6
Wire Wire Line
	10500 1200 10400 1200
NoConn ~ 10400 1700
NoConn ~ 10400 1800
Text Label 10400 1700 0    50   ~ 0
SWCLK
Text Label 10400 1800 0    50   ~ 0
SWDIO
NoConn ~ 10400 1900
NoConn ~ 10400 2000
Text Label 10400 1900 0    50   ~ 0
USB_DP
NoConn ~ 10400 2100
NoConn ~ 10400 2200
NoConn ~ 8800 1100
Text Label 8550 1100 0    50   ~ 0
K_IN
Text Label 8550 1200 0    50   ~ 0
K_OUT
Wire Wire Line
	8550 1100 8800 1100
NoConn ~ 8800 1200
Wire Wire Line
	8550 1200 8800 1200
NoConn ~ 8800 1300
Text Label 8550 1300 0    50   ~ 0
BOOT1
Wire Wire Line
	8800 1300 8550 1300
NoConn ~ 10400 1400
NoConn ~ 8800 1400
Text Label 10400 2000 0    50   ~ 0
USB_DM
Text Notes 8150 7650 0    50   ~ 0
28/1/2019
Text Notes 10600 7650 0    50   ~ 0
1
Text Notes 7500 7500 0    50   ~ 0
Maple Mini - LRDuinoTD5
Text Notes 7300 7250 0    50   ~ 0
1
Text Notes 7400 7250 0    50   ~ 0
1
Text Notes 7150 6750 0    50   ~ 0
https://github.com/BennehBoy/LRDuinoTD5
Wire Wire Line
	4950 3150 4650 3150
Connection ~ 4650 3150
Wire Wire Line
	4650 3150 4650 3300
$EndSCHEMATC
