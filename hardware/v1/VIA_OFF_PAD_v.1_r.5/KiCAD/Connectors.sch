EESchema Schematic File Version 2
LIBS:power
LIBS:MYRIAD_RF-cache
EELAYER 27 0
EELAYER END
$Descr User 8266 11692
encoding utf-8
Sheet 5 7
Title "MYRIAD RF_Novena v.1"
Date "19 apr 2014"
Rev "3"
Comp ""
Comment1 "THIS WORK IS COVERED UNDER A CREATIVE COMMONS LICENSE (CC BY 3.0)"
Comment2 "Copyright 2013 AZIO Electronics Co., Ltd."
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 5500 6150 2    45   Output ~ 0
RXCLK
Text GLabel 5600 2650 2    45   Output ~ 0
TXEN
Text GLabel 4850 2550 2    45   Input ~ 0
CLK_IN
Text GLabel 1700 7450 0    45   Output ~ 0
RXEN
Text GLabel 2950 7150 0    45   Output ~ 0
SAEN(SPI_NCS0)
Text GLabel 2950 7050 0    45   Output ~ 0
SACLK(SPI_CLK)
Text GLabel 2950 6650 0    45   Output ~ 0
SADO(SPI_MISO)
Text GLabel 2950 6550 0    45   Output ~ 0
SADIO(SPI_MOSI)
Text GLabel 2450 6150 0    45   Output ~ 0
TXCLK
Text GLabel 2950 6450 0    45   Output ~ 0
RESET
$Comp
L GND #PWR067
U 1 1 4FED9BA7
P 3000 6850
F 0 "#PWR067" H 3000 6950 50  0001 C CNN
F 1 "GND" H 3000 6750 50  0000 C CNN
F 2 "" H 3000 6850 60  0001 C CNN
F 3 "" H 3000 6850 60  0001 C CNN
	1    3000 6850
	0    1    1    0   
$EndComp
$Comp
L GND #PWR068
U 1 1 4FED9BA0
P 3000 5550
F 0 "#PWR068" H 3000 5650 50  0001 C CNN
F 1 "GND" H 3000 5450 50  0000 C CNN
F 2 "" H 3000 5550 60  0001 C CNN
F 3 "" H 3000 5550 60  0001 C CNN
	1    3000 5550
	0    1    1    0   
$EndComp
$Comp
L GND #PWR069
U 1 1 4FED9B9A
P 3000 4250
F 0 "#PWR069" H 3000 4350 50  0001 C CNN
F 1 "GND" H 3000 4150 50  0000 C CNN
F 2 "" H 3000 4250 60  0001 C CNN
F 3 "" H 3000 4250 60  0001 C CNN
	1    3000 4250
	0    1    1    0   
$EndComp
$Comp
L GND #PWR070
U 1 1 4FED9B93
P 3000 2950
F 0 "#PWR070" H 3000 3050 50  0001 C CNN
F 1 "GND" H 3000 2850 50  0000 C CNN
F 2 "" H 3000 2950 60  0001 C CNN
F 3 "" H 3000 2950 60  0001 C CNN
	1    3000 2950
	0    1    1    0   
$EndComp
$Comp
L GND #PWR071
U 1 1 4FED9B83
P 4900 2950
F 0 "#PWR071" H 4900 3050 50  0001 C CNN
F 1 "GND" H 4900 2850 50  0000 C CNN
F 2 "" H 4900 2950 60  0001 C CNN
F 3 "" H 4900 2950 60  0001 C CNN
	1    4900 2950
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR072
U 1 1 4FED9B7C
P 4900 4250
F 0 "#PWR072" H 4900 4350 50  0001 C CNN
F 1 "GND" H 4900 4150 50  0000 C CNN
F 2 "" H 4900 4250 60  0001 C CNN
F 3 "" H 4900 4250 60  0001 C CNN
	1    4900 4250
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR073
U 1 1 4FED9B72
P 4900 5550
F 0 "#PWR073" H 4900 5650 50  0001 C CNN
F 1 "GND" H 4900 5450 50  0000 C CNN
F 2 "" H 4900 5550 60  0001 C CNN
F 3 "" H 4900 5550 60  0001 C CNN
	1    4900 5550
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR074
U 1 1 4FED9B6D
P 4900 6850
F 0 "#PWR074" H 4900 6950 50  0001 C CNN
F 1 "GND" H 4900 6750 50  0000 C CNN
F 2 "" H 4900 6850 60  0001 C CNN
F 3 "" H 4900 6850 60  0001 C CNN
	1    4900 6850
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR075
U 1 1 4FED9B66
P 2200 9125
F 0 "#PWR075" H 2200 9225 50  0001 C CNN
F 1 "GND" H 2200 9025 50  0000 C CNN
F 2 "" H 2200 9125 60  0001 C CNN
F 3 "" H 2200 9125 60  0001 C CNN
	1    2200 9125
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR076
U 1 1 4FED9B61
P 3550 9125
F 0 "#PWR076" H 3550 9225 50  0001 C CNN
F 1 "GND" H 3550 9025 50  0000 C CNN
F 2 "" H 3550 9125 60  0001 C CNN
F 3 "" H 3550 9125 60  0001 C CNN
	1    3550 9125
	0    -1   -1   0   
$EndComp
$Comp
L CONN_5 X5
U 1 1 4FEB431B
P 2600 9125
F 0 "X5" H 2600 9445 50  0000 C CNN
F 1 "5-104348-3" H 2600 8785 50  0001 C CNN
F 2 "VR_pinhead5" H 2600 9125 60  0001 C CNN
F 3 "" H 2600 9125 60  0001 C CNN
F 4 ".100 inch AMPMODU Headers; RIGHT ANGLE; 5WAY;" H 2600 9125 60  0001 C CNN "Description"
F 5 "5-104348-3" H 2600 9125 60  0001 C CNN "Manufacturer Part Number"
F 6 "TE Connectivity" H 2600 9125 60  0001 C CNN "Manufacturer"
F 7 "TTI" H 2600 9125 60  0001 C CNN "Vendor"
F 8 "5-104348-3" H 2600 9125 60  0001 C CNN "Vendor Part Number"
	1    2600 9125
	-1   0    0    -1  
$EndComp
$Comp
L CONN_5 X4
U 1 1 4FEB4303
P 1350 9125
F 0 "X4" H 1350 9445 50  0000 C CNN
F 1 "5-104348-3" H 1350 8785 50  0001 C CNN
F 2 "VR_pinhead5" H 1350 9125 60  0001 C CNN
F 3 "" H 1350 9125 60  0001 C CNN
F 4 ".100 inch AMPMODU Headers; RIGHT ANGLE; 5WAY;" H 1350 9125 60  0001 C CNN "Description"
F 5 "5-104348-3" H 1350 9125 60  0001 C CNN "Manufacturer Part Number"
F 6 "TE Connectivity" H 1350 9125 60  0001 C CNN "Manufacturer"
F 7 "TTI" H 1350 9125 60  0001 C CNN "Vendor"
F 8 "5-104348-3" H 1350 9125 60  0001 C CNN "Vendor Part Number"
	1    1350 9125
	-1   0    0    -1  
$EndComp
Text GLabel 3150 9325 2    45   Output ~ 0
RXOUTQP
Text GLabel 3150 9225 2    45   Output ~ 0
RXOUTQN
Text GLabel 3150 9025 2    45   Output ~ 0
RXOUTIP
Text GLabel 3150 8925 2    45   Output ~ 0
RXOUTIN
Text GLabel 1900 9325 2    45   Input ~ 0
TXINQN
Text GLabel 1900 9225 2    45   Input ~ 0
TXINQP
Text GLabel 1900 9025 2    45   Input ~ 0
TXINIP
Text GLabel 1900 8925 2    45   Input ~ 0
TXININ
Text GLabel 4950 6650 2    45   Output ~ 0
GPIO2
Text GLabel 4950 6550 2    45   Output ~ 0
GPIO1
Text GLabel 4950 6450 2    45   Output ~ 0
GPIO0
Text GLabel 4950 5950 2    45   Input ~ 0
RXD10
Text GLabel 4950 5850 2    45   Input ~ 0
RXD8
Text GLabel 4950 5750 2    45   Input ~ 0
RXD6
Text GLabel 4950 5250 2    45   Input ~ 0
RXD4
Text GLabel 4950 5150 2    45   Input ~ 0
RXD2
Text GLabel 4950 5050 2    45   Input ~ 0
RXD0
Text GLabel 4950 4850 2    45   Input ~ 0
RXIQSEL
Text GLabel 4950 4650 2    45   Input ~ 0
TXD10
Text GLabel 4950 4550 2    45   Input ~ 0
TXD8
Text GLabel 4950 4450 2    45   Input ~ 0
TXD6
Text GLabel 4950 4050 2    45   Output ~ 0
TXD4
Text GLabel 4950 3950 2    45   Output ~ 0
TXD2
Text GLabel 4950 3850 2    45   Output ~ 0
TXD0
Text GLabel 4950 3550 2    45   Output ~ 0
TXIQSEL
Text GLabel 2950 5950 0    45   Input ~ 0
RXD11
Text GLabel 2950 5850 0    45   Input ~ 0
RXD9
Text GLabel 2950 5750 0    45   Input ~ 0
RXD7
Text GLabel 2950 5350 0    45   Input ~ 0
RXD5
Text GLabel 2950 5150 0    45   Input ~ 0
RXD3
Text GLabel 2950 5050 0    45   Input ~ 0
RXD1
Text GLabel 2950 4750 0    45   Output ~ 0
TXD11
Text GLabel 2950 4650 0    45   Output ~ 0
TXD9
Text GLabel 2950 4550 0    45   Output ~ 0
TXD7
Text GLabel 2950 4050 0    45   Output ~ 0
TXD5
Text GLabel 2950 3850 0    45   Output ~ 0
TXD3
Text GLabel 2950 3750 0    45   Output ~ 0
TXD1
$Comp
L FX10A-80P8 X3
U 1 1 4FEB249B
P 3950 4850
F 0 "X3" H 3900 7750 50  0000 C CNN
F 1 "CONN_HROSE_FX10A-80P8" H 3900 7650 50  0000 C CNN
F 2 "FX10A-80P8" H 3950 4850 60  0001 C CNN
F 3 "" H 3950 4850 60  0001 C CNN
F 4 "CONN HEADER 80POS W/O POST SMD" H 3950 4850 60  0001 C CNN "Description"
F 5 "FX10B-80P/8-SV1(71)" H 3950 4850 60  0001 C CNN "Manufacturer Part Number"
F 6 "Hirose Electric" H 3950 4850 60  0001 C CNN "Manufacturer"
F 7 "Digi-Key" H 3950 4850 60  0001 C CNN "Vendor"
F 8 "H11228-ND" H 3950 4850 60  0001 C CNN "Vendor Part Number"
	1    3950 4850
	1    0    0    -1  
$EndComp
NoConn ~ 3150 3250
NoConn ~ 3150 3350
NoConn ~ 3150 3550
NoConn ~ 3150 3650
NoConn ~ 3150 4950
NoConn ~ 3150 4850
NoConn ~ 3150 6250
NoConn ~ 4750 6250
NoConn ~ 4750 4950
NoConn ~ 4750 3650
NoConn ~ 4750 3350
NoConn ~ 4750 3250
$Comp
L VCC #PWR077
U 1 1 4FEB2007
P 5350 7000
F 0 "#PWR077" H 5350 7120 20  0001 C CNN
F 1 "VCC" H 5350 7160 50  0000 C CNN
F 2 "" H 5350 7000 60  0001 C CNN
F 3 "" H 5350 7000 60  0001 C CNN
F 4 "+5V" H 5336 7094 39  0000 C CNN "Voltage"
	1    5350 7000
	1    0    0    -1  
$EndComp
$Comp
L R R44
U 1 1 4FEB1F3B
P 2750 6150
F 0 "R44" V 2840 6150 50  0000 C CNN
F 1 "0" V 2660 6150 50  0000 C CNN
F 2 "R_SM0402" H 2750 6150 60  0001 C CNN
F 3 "" H 2750 6150 60  0001 C CNN
F 4 "RESISTOR; 0402; 0R; REEL 10000;" H 2750 6150 60  0001 C CNN "Description"
F 5 "RC0402JR-070RL" H 2750 6150 60  0001 C CNN "Manufacturer Part Number"
F 6 "YAGEO (PHYCOMP)" H 2750 6150 60  0001 C CNN "Manufacturer"
F 7 "Farnell" H 2750 6150 60  0001 C CNN "Vendor"
F 8 "1117280" H 2750 6150 60  0001 C CNN "Vendor Part Number"
F 9 "NF" V 2750 6150 60  0000 C CNN "Install"
F 10 "NOFIT" V 2750 6150 60  0001 C CNN "Assemble"
	1    2750 6150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3000 8925 3150 8925
Wire Wire Line
	3000 9325 3150 9325
Wire Wire Line
	3000 9025 3150 9025
Wire Wire Line
	1750 9325 1900 9325
Wire Wire Line
	1750 9125 2200 9125
Wire Wire Line
	1750 8925 1900 8925
Wire Wire Line
	2950 3750 3150 3750
Wire Wire Line
	2950 4050 3150 4050
Wire Wire Line
	2950 4650 3150 4650
Wire Wire Line
	3150 5050 2950 5050
Wire Wire Line
	3150 5350 2950 5350
Wire Wire Line
	3150 5850 2950 5850
Wire Wire Line
	2950 5950 3150 5950
Wire Wire Line
	3150 6450 2950 6450
Wire Wire Line
	3150 6650 2950 6650
Wire Wire Line
	3150 7150 2950 7150
Wire Wire Line
	5350 7250 4750 7250
Wire Wire Line
	4750 6650 4950 6650
Wire Wire Line
	4750 5850 4950 5850
Wire Wire Line
	4750 5050 4950 5050
Wire Wire Line
	4750 4650 4950 4650
Wire Wire Line
	4750 4450 4950 4450
Wire Wire Line
	4750 3850 4950 3850
Wire Wire Line
	4750 4050 4950 4050
Wire Wire Line
	5350 7150 4750 7150
Wire Wire Line
	5350 7350 4750 7350
Wire Wire Line
	4750 5250 4950 5250
Wire Wire Line
	4750 3950 4950 3950
Wire Wire Line
	4750 3550 4950 3550
Wire Wire Line
	4750 4550 4950 4550
Wire Wire Line
	4750 4850 4950 4850
Wire Wire Line
	4750 5150 4950 5150
Wire Wire Line
	4750 5750 4950 5750
Wire Wire Line
	4750 5950 4950 5950
Wire Wire Line
	4750 6450 4950 6450
Wire Wire Line
	4750 6550 4950 6550
Wire Wire Line
	3150 7050 2950 7050
Wire Wire Line
	2950 6550 3150 6550
Wire Wire Line
	3150 5750 2950 5750
Wire Wire Line
	3150 5150 2950 5150
Wire Wire Line
	3150 4750 2950 4750
Wire Wire Line
	3150 4550 2950 4550
Wire Wire Line
	3150 3850 2950 3850
Wire Wire Line
	1750 9025 1900 9025
Wire Wire Line
	1750 9225 1900 9225
Wire Wire Line
	3000 9125 3550 9125
Wire Wire Line
	3000 9225 3150 9225
Wire Wire Line
	3000 6150 3150 6150
Wire Wire Line
	2500 6150 2450 6150
Wire Wire Line
	1800 7450 1700 7450
Wire Wire Line
	2300 7450 3150 7450
Wire Wire Line
	4900 6150 4750 6150
Wire Wire Line
	5400 6150 5500 6150
Wire Wire Line
	5550 2650 5600 2650
$Comp
L R R23
U 1 1 5048E6C1
P 2050 7450
F 0 "R23" V 2140 7450 50  0000 C CNN
F 1 "0" V 1960 7450 50  0000 C CNN
F 2 "R_SM0402" H 2050 7450 60  0001 C CNN
F 3 "" H 2050 7450 60  0001 C CNN
F 4 "RESISTOR; 0402; 0R; REEL 10000;" H 2050 7450 60  0001 C CNN "Description"
F 5 "RC0402JR-070RL" H 2050 7450 60  0001 C CNN "Manufacturer Part Number"
F 6 "YAGEO (PHYCOMP)" H 2050 7450 60  0001 C CNN "Manufacturer"
F 7 "Farnell" H 2050 7450 60  0001 C CNN "Vendor"
F 8 "1117280" H 2050 7450 60  0001 C CNN "Vendor Part Number"
	1    2050 7450
	0    -1   -1   0   
$EndComp
$Comp
L R R24
U 1 1 5048E6F4
P 5300 2650
F 0 "R24" V 5400 2650 50  0000 C CNN
F 1 "0" V 5210 2650 50  0000 C CNN
F 2 "R_SM0402" H 5300 2650 60  0001 C CNN
F 3 "" H 5300 2650 60  0001 C CNN
F 4 "RESISTOR; 0402; 0R; REEL 10000;" H 5300 2650 60  0001 C CNN "Description"
F 5 "RC0402JR-070RL" H 5300 2650 60  0001 C CNN "Manufacturer Part Number"
F 6 "YAGEO (PHYCOMP)" H 5300 2650 60  0001 C CNN "Manufacturer"
F 7 "Farnell" H 5300 2650 60  0001 C CNN "Vendor"
F 8 "1117280" H 5300 2650 60  0001 C CNN "Vendor Part Number"
	1    5300 2650
	0    -1   -1   0   
$EndComp
$Comp
L R R46
U 1 1 5048E6FF
P 5150 6150
F 0 "R46" V 5240 6150 50  0000 C CNN
F 1 "0" V 5060 6150 50  0000 C CNN
F 2 "R_SM0402" H 5150 6150 60  0001 C CNN
F 3 "" H 5150 6150 60  0001 C CNN
F 4 "RESISTOR; 0402; 0R; REEL 10000;" H 5150 6150 60  0001 C CNN "Description"
F 5 "RC0402JR-070RL" H 5150 6150 60  0001 C CNN "Manufacturer Part Number"
F 6 "YAGEO (PHYCOMP)" H 5150 6150 60  0001 C CNN "Manufacturer"
F 7 "Farnell" H 5150 6150 60  0001 C CNN "Vendor"
F 8 "1117280" H 5150 6150 60  0001 C CNN "Vendor Part Number"
F 9 "NF" V 5150 6150 60  0000 C CNN "Install"
F 10 "NOFIT" V 5150 6150 60  0001 C CNN "Assemble"
	1    5150 6150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4850 2550 4750 2550
Wire Wire Line
	5050 2650 4750 2650
Wire Wire Line
	4750 2950 4900 2950
Wire Wire Line
	4750 4250 4900 4250
Wire Wire Line
	4750 5550 4900 5550
Wire Wire Line
	4750 6850 4900 6850
Wire Wire Line
	5350 7000 5350 7350
Wire Wire Line
	5350 7050 4750 7050
Connection ~ 5350 7050
Connection ~ 5350 7150
Connection ~ 5350 7250
$Comp
L GND #PWR078
U 1 1 534411A0
P 4900 7450
F 0 "#PWR078" H 4900 7550 50  0001 C CNN
F 1 "GND" H 4900 7350 50  0000 C CNN
F 2 "" H 4900 7450 60  0001 C CNN
F 3 "" H 4900 7450 60  0001 C CNN
	1    4900 7450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4750 7450 4900 7450
Wire Wire Line
	3150 6850 3000 6850
Wire Wire Line
	3150 5550 3000 5550
Wire Wire Line
	3150 4250 3000 4250
Wire Wire Line
	3150 2950 3000 2950
NoConn ~ 3150 2350
NoConn ~ 3150 2450
NoConn ~ 3150 2550
NoConn ~ 3150 2650
NoConn ~ 3150 2750
NoConn ~ 4750 2450
NoConn ~ 4750 2750
NoConn ~ 3150 3150
NoConn ~ 4750 3150
NoConn ~ 4750 3750
NoConn ~ 3150 3950
NoConn ~ 3150 4450
NoConn ~ 4750 4750
NoConn ~ 4750 5350
NoConn ~ 3150 5250
NoConn ~ 4750 6350
NoConn ~ 4750 6050
NoConn ~ 3150 6050
NoConn ~ 3150 6350
NoConn ~ 4750 3450
NoConn ~ 3150 3450
NoConn ~ 3150 7250
NoConn ~ 4750 2350
Text Notes 2750 1650 0    79   ~ 0
"Myriad RF" and "Novena" connector
Text GLabel 2900 7350 0    45   Output ~ 0
VCT
Wire Wire Line
	3150 7350 2900 7350
Text Notes 1850 8525 0    79   ~ 0
Analong signals
$Comp
L CONN_6 X9
U 1 1 53518ABA
P 4300 9100
F 0 "X9" H 4300 9450 60  0000 C CNN
F 1 "CONN_6" V 4350 9100 60  0001 C CNN
F 2 "pinhead6" H 4300 9100 60  0001 C CNN
F 3 "" H 4300 9100 60  0001 C CNN
F 4 "Headers & Wire Housings 06; MODII; HDR SRST; B/A; W/HD;" H 4300 9100 60  0001 C CNN "Description"
F 5 "104345-4" H 4300 9100 60  0001 C CNN "Manufacturer Part Number"
F 6 "TE Connectivity" H 4300 9100 60  0001 C CNN "Manufacturer"
F 7 "TTI" H 4300 9100 60  0001 C CNN "Vendor"
F 8 "104345-4" H 4300 9100 60  0001 C CNN "Vendor Part Number"
F 9 "NF" H 4300 9100 60  0000 C CNN "Install"
F 10 "NOFIT" H 4300 9100 60  0001 C CNN "Assemble"
	1    4300 9100
	-1   0    0    -1  
$EndComp
Text GLabel 4750 9050 2    45   Output ~ 0
SAEN(SPI_NCS0)
Text GLabel 4750 8950 2    45   Output ~ 0
RESET
Text GLabel 4750 9250 2    45   Output ~ 0
SADIO(SPI_MOSI)
Text GLabel 4750 9150 2    45   Output ~ 0
SACLK(SPI_CLK)
Text GLabel 4750 9350 2    45   Output ~ 0
SADO(SPI_MISO)
$Comp
L GND #PWR079
U 1 1 53518AF6
P 5200 8850
F 0 "#PWR079" H 5200 8950 50  0001 C CNN
F 1 "GND" H 5200 8750 50  0000 C CNN
F 2 "" H 5200 8850 60  0001 C CNN
F 3 "" H 5200 8850 60  0001 C CNN
	1    5200 8850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 8850 5200 8850
Wire Wire Line
	4650 8950 4750 8950
Wire Wire Line
	4650 9050 4750 9050
Wire Wire Line
	4650 9150 4750 9150
Wire Wire Line
	4650 9250 4750 9250
Wire Wire Line
	4650 9350 4750 9350
$EndSCHEMATC
