EESchema Schematic File Version 2  date 19/07/2014 15:49:20
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:FE
LIBS:Duet0.7-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 3 7
Title "Duet"
Date "19 jul 2014"
Rev "0.7"
Comp "Think3DPrint3D, RepRapPro"
Comment1 "CERN OSH License 1.2"
Comment2 "http://www.ohwr.org/attachments/2388/cern_ohl_v_1_2.txt"
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 2150 4250
Wire Wire Line
	2150 4600 2150 4250
Wire Wire Line
	4250 5450 2000 5450
Wire Wire Line
	4250 5450 4250 5150
Connection ~ 6000 4800
Wire Wire Line
	6000 4900 6000 4800
Connection ~ 5250 1800
Wire Wire Line
	5250 1900 5250 1800
Wire Wire Line
	4100 2100 4100 2200
Wire Wire Line
	2600 1800 2250 1800
Wire Wire Line
	6600 4450 6600 4050
Wire Wire Line
	6600 4050 6150 4050
Wire Notes Line
	7000 5800 5000 5800
Wire Notes Line
	7000 5800 7000 3650
Wire Notes Line
	5000 5800 5000 3650
Wire Notes Line
	5000 3650 7000 3650
Wire Wire Line
	6400 1800 6500 1800
Wire Wire Line
	5950 1300 5700 1300
Connection ~ 5700 1800
Wire Wire Line
	5700 1300 5700 1800
Wire Wire Line
	2000 5450 2000 5550
Wire Notes Line
	1400 3650 4850 3650
Connection ~ 3850 5450
Wire Notes Line
	7250 1100 1400 1100
Wire Notes Line
	7250 1100 7250 3550
Wire Notes Line
	7250 3550 1400 3550
Wire Notes Line
	1400 3550 1400 1100
Connection ~ 3850 4250
Connection ~ 2750 5450
Wire Wire Line
	2750 5450 2750 4750
Wire Wire Line
	3850 5450 3850 4950
Wire Notes Line
	1400 3650 1400 5800
Wire Wire Line
	3850 4250 3850 4550
Wire Notes Line
	4850 3650 4850 5800
Wire Wire Line
	1800 4250 2350 4250
Wire Notes Line
	4850 5800 1400 5800
Wire Wire Line
	3150 4350 3250 4350
Wire Wire Line
	3250 4350 3250 4250
Connection ~ 3250 4250
Wire Wire Line
	5250 2550 5250 2300
Wire Wire Line
	2150 2800 2150 3000
Wire Wire Line
	6500 2500 6500 2250
Wire Wire Line
	6500 1800 6500 1850
Wire Wire Line
	5000 1800 5800 1800
Wire Wire Line
	6600 5500 6600 5150
Wire Wire Line
	4600 1800 4500 1800
Wire Wire Line
	6150 4800 5850 4800
Wire Wire Line
	6000 5400 6600 5400
Connection ~ 6600 5400
Wire Wire Line
	5700 2700 5700 2800
Wire Wire Line
	1800 2750 1800 2800
Connection ~ 2150 2800
Wire Wire Line
	2150 5000 2150 5450
Connection ~ 2150 5450
Wire Wire Line
	3150 4250 4350 4250
Connection ~ 4250 4250
Wire Wire Line
	1800 2250 1800 2200
Wire Wire Line
	1750 1800 1850 1800
Connection ~ 1800 1800
Wire Wire Line
	1800 2800 3200 2800
Wire Wire Line
	3200 2800 3200 2200
Wire Wire Line
	3200 2200 4100 2200
Connection ~ 3550 2200
Wire Wire Line
	3700 1800 3200 1800
Connection ~ 3550 1800
$Comp
L C C95
U 1 1 53B48211
P 2150 4800
F 0 "C95" H 2200 4900 50  0000 L CNN
F 1 "1u" H 2200 4700 50  0000 L CNN
	1    2150 4800
	1    0    0    -1  
$EndComp
$Comp
L LED D16
U 1 1 53B03C27
P 4250 4450
F 0 "D16" H 4250 4550 50  0000 C CNN
F 1 "3.3V" H 4250 4350 50  0000 C CNN
	1    4250 4450
	0    1    1    0   
$EndComp
$Comp
L R R60
U 1 1 53B03C26
P 4250 4900
F 0 "R60" V 4330 4900 50  0000 C CNN
F 1 "220R" V 4250 4900 50  0000 C CNN
	1    4250 4900
	1    0    0    -1  
$EndComp
$Comp
L LED D17
U 1 1 53B03C01
P 5700 2000
F 0 "D17" H 5700 2100 50  0000 C CNN
F 1 "5V+" H 5700 1900 50  0000 C CNN
	1    5700 2000
	0    1    1    0   
$EndComp
$Comp
L R R61
U 1 1 53B03C00
P 5700 2450
F 0 "R61" V 5780 2450 50  0000 C CNN
F 1 "220R" V 5700 2450 50  0000 C CNN
	1    5700 2450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR030
U 1 1 53B03BFF
P 5700 2800
F 0 "#PWR030" H 5700 2800 30  0001 C CNN
F 1 "GND" H 5700 2730 30  0001 C CNN
	1    5700 2800
	1    0    0    -1  
$EndComp
$Comp
L R R55
U 1 1 53B03BE9
P 1800 2500
F 0 "R55" V 1880 2500 50  0000 C CNN
F 1 "2k7" V 1800 2500 50  0000 C CNN
	1    1800 2500
	1    0    0    -1  
$EndComp
$Comp
L LED D15
U 1 1 53B03BD1
P 1800 2000
F 0 "D15" H 1800 2100 50  0000 C CNN
F 1 "VIN" H 1800 1900 50  0000 C CNN
	1    1800 2000
	0    1    1    0   
$EndComp
$Comp
L R R54
U 1 1 53B03419
P 6000 5150
F 0 "R54" V 6080 5150 50  0000 C CNN
F 1 "2k7" V 6000 5150 50  0000 C CNN
	1    6000 5150
	1    0    0    -1  
$EndComp
$Comp
L CP1 C5
U 1 1 53B02FA8
P 3550 2000
F 0 "C5" H 3600 2100 50  0000 L CNN
F 1 "0u33" H 3600 1900 50  0000 L CNN
	1    3550 2000
	1    0    0    -1  
$EndComp
$Comp
L CP1 C4
U 1 1 53B02AAB
P 3850 4750
F 0 "C4" H 3900 4850 50  0000 L CNN
F 1 "10u" H 3900 4650 50  0000 L CNN
	1    3850 4750
	1    0    0    -1  
$EndComp
$Comp
L DIODESCH D2
U 1 1 53B02782
P 4800 1800
F 0 "D2" H 4800 1900 40  0000 C CNN
F 1 "SS14M" H 4800 1700 40  0000 C CNN
	1    4800 1800
	1    0    0    -1  
$EndComp
$Comp
L 7805 U3
U 1 1 53B01DB6
P 4100 1850
F 0 "U3" H 4250 1654 60  0000 C CNN
F 1 "MC7805CDTG" H 4100 2050 60  0000 C CNN
	1    4100 1850
	1    0    0    -1  
$EndComp
Text Notes 6700 2100 0    60   ~ 0
1A
$Comp
L DIODESCH D14
U 1 1 5220D356
P 6500 2050
F 0 "D14" H 6500 2150 40  0000 C CNN
F 1 "SS14M" H 6500 1950 40  0000 C CNN
	1    6500 2050
	0    -1   -1   0   
$EndComp
$Comp
L BSH105 TR7
U 1 1 5220C267
P 6450 4800
F 0 "TR7" H 6353 5050 70  0000 C CNN
F 1 "BSH105" H 6303 4503 60  0000 C CNN
	1    6450 4800
	1    0    0    -1  
$EndComp
Text GLabel 5850 4800 0    60   Input ~ 0
PS_ON_CONTROL
Text Notes 5200 3850 0    60   ~ 0
PS_ON Control
$Comp
L GND #PWR031
U 1 1 5220BA8F
P 6600 5500
F 0 "#PWR031" H 6600 5500 30  0001 C CNN
F 1 "GND" H 6600 5430 30  0001 C CNN
	1    6600 5500
	1    0    0    -1  
$EndComp
Text GLabel 6150 4050 0    60   Input ~ 0
PS_ON_IN
$Comp
L JUMPER JP10
U 1 1 5220B966
P 6100 1800
F 0 "JP10" H 6100 1950 60  0000 C CNN
F 1 "ATX_5V_EN" H 6100 1720 40  0000 C CNN
	1    6100 1800
	1    0    0    -1  
$EndComp
Text Notes 5400 2150 0    60   ~ 0
1A
Text Notes 6000 3250 0    60   ~ 0
up to 1A
Text Notes 6000 3150 0    60   ~ 0
this design allows 
Text Notes 6000 3050 0    60   ~ 0
at least 780mA
Text Notes 6000 2950 0    60   ~ 0
ATX Spec advises
Text GLabel 6500 2500 3    60   Input ~ 0
5V_IN
Text Notes 4850 3050 0    60   ~ 0
by the USB specification
Text Notes 4850 2950 0    60   ~ 0
VBUS limited to 500mA 
$Comp
L JUMPER JP9
U 1 1 52209EAB
P 2900 1800
F 0 "JP9" H 2900 1950 60  0000 C CNN
F 1 "5V_EN" H 2900 1720 40  0000 C CNN
	1    2900 1800
	1    0    0    -1  
$EndComp
$Comp
L SS3P4 D1
U 1 1 5116BBAA
P 2050 1800
F 0 "D1" H 2050 1900 40  0000 C CNN
F 1 "SS3P4" H 2050 1700 40  0000 C CNN
	1    2050 1800
	1    0    0    -1  
$EndComp
$Comp
L DIODESCH D13
U 1 1 50F99BAC
P 5250 2100
F 0 "D13" H 5250 2200 40  0000 C CNN
F 1 "SS14M" H 5250 2000 40  0000 C CNN
	1    5250 2100
	0    -1   -1   0   
$EndComp
Text GLabel 5250 2550 3    60   Input ~ 0
VBUS
$Comp
L LM1117MP-3.3 U2
U 1 1 506B578D
P 2750 4400
F 0 "U2" H 2750 4700 60  0000 C CNN
F 1 "TC2117-3.3VDBTR" H 2800 4150 60  0000 L CNN
	1    2750 4400
	1    0    0    -1  
$EndComp
Text Notes 1500 3850 0    60   ~ 0
5V Input, 3.3V 500mA Output\nLow Drop-Out Linear Regulator
Text Notes 1500 1300 0    60   ~ 0
12-24V Input, 5V 1A Output 7805 regulator\n
Text GLabel 4350 4250 2    60   Input ~ 0
+3.3V
Text GLabel 1800 4250 0    60   Input ~ 0
+5V
Text GLabel 1750 1800 0    60   Input ~ 0
V_IN
Text GLabel 5950 1300 2    60   Input ~ 0
+5V
$Comp
L GND #PWR032
U 1 1 50522574
P 2000 5550
F 0 "#PWR032" H 2000 5550 30  0001 C CNN
F 1 "GND" H 2000 5480 30  0001 C CNN
	1    2000 5550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR033
U 1 1 50522566
P 2150 3000
F 0 "#PWR033" H 2150 3000 30  0001 C CNN
F 1 "GND" H 2150 2930 30  0001 C CNN
	1    2150 3000
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 50522565
P 3200 2000
F 0 "C3" H 3250 2100 50  0000 L CNN
F 1 "100u" H 3250 1900 50  0000 L CNN
F 4 "35V" H 3250 1830 50  0000 L CNN "Voltage"
	1    3200 2000
	1    0    0    -1  
$EndComp
$EndSCHEMATC
