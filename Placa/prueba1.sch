EESchema Schematic File Version 2
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
LIBS:silabs
LIBS:silabs-2
LIBS:silabs-eth
LIBS:micro-silabs
LIBS:max232ti_n
LIBS:linear2
LIBS:linear-technology
LIBS:jst_eph
LIBS:basicx
LIBS:Capacitor-Wima-FKM2-100v
LIBS:Cap-Gold
LIBS:m-pad-2.1
LIBS:diy_connectors
LIBS:pinhead-1
LIBS:pinhead
LIBS:stuart
LIBS:prueba1-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "8 may 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L AGND #PWR01
U 1 1 5524219B
P 3100 5400
F 0 "#PWR01" H 3100 5400 40  0001 C CNN
F 1 "AGND" H 3100 5330 50  0000 C CNN
F 2 "" H 3100 5400 60  0000 C CNN
F 3 "" H 3100 5400 60  0000 C CNN
	1    3100 5400
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5524235B
P 1250 3100
F 0 "C3" H 1250 3200 39  0000 L CNN
F 1 "0,1micF" H 1256 3015 39  0000 L CNN
F 2 "~" H 1288 2950 30  0000 C CNN
F 3 "~" H 1250 3100 60  0000 C CNN
	1    1250 3100
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5524249A
P 1700 2900
F 0 "R3" V 1780 2900 40  0000 C CNN
F 1 "100ohm" V 1707 2901 40  0000 C CNN
F 2 "~" V 1630 2900 30  0000 C CNN
F 3 "~" H 1700 2900 30  0000 C CNN
	1    1700 2900
	0    -1   -1   0   
$EndComp
$Comp
L DGND #PWR02
U 1 1 552424EC
P 1250 3350
F 0 "#PWR02" H 1250 3350 40  0001 C CNN
F 1 "DGND" H 1250 3280 40  0000 C CNN
F 2 "" H 1250 3350 60  0000 C CNN
F 3 "" H 1250 3350 60  0000 C CNN
	1    1250 3350
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 55242560
P 1250 2250
F 0 "C2" H 1250 2350 39  0000 L CNN
F 1 "0,1micF" H 1256 2165 39  0000 L CNN
F 2 "~" H 1288 2100 30  0000 C CNN
F 3 "~" H 1250 2250 60  0000 C CNN
	1    1250 2250
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 55242566
P 1700 2050
F 0 "R2" V 1780 2050 40  0000 C CNN
F 1 "100ohm" V 1707 2051 40  0000 C CNN
F 2 "~" V 1630 2050 30  0000 C CNN
F 3 "~" H 1700 2050 30  0000 C CNN
	1    1700 2050
	0    -1   -1   0   
$EndComp
$Comp
L DGND #PWR03
U 1 1 5524256F
P 1250 2450
F 0 "#PWR03" H 1250 2450 40  0001 C CNN
F 1 "DGND" H 1250 2380 40  0000 C CNN
F 2 "" H 1250 2450 60  0000 C CNN
F 3 "" H 1250 2450 60  0000 C CNN
	1    1250 2450
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 55242576
P 1250 1500
F 0 "C1" H 1250 1600 39  0000 L CNN
F 1 "0,1micF" H 1256 1415 39  0000 L CNN
F 2 "~" H 1288 1350 30  0000 C CNN
F 3 "~" H 1250 1500 60  0000 C CNN
	1    1250 1500
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5524257C
P 1700 1300
F 0 "R1" V 1780 1300 40  0000 C CNN
F 1 "100ohm" V 1707 1301 40  0000 C CNN
F 2 "~" V 1630 1300 30  0000 C CNN
F 3 "~" H 1700 1300 30  0000 C CNN
	1    1700 1300
	0    -1   -1   0   
$EndComp
$Comp
L DGND #PWR04
U 1 1 55242585
P 1250 1700
F 0 "#PWR04" H 1250 1700 40  0001 C CNN
F 1 "DGND" H 1250 1630 40  0000 C CNN
F 2 "" H 1250 1700 60  0000 C CNN
F 3 "" H 1250 1700 60  0000 C CNN
	1    1250 1700
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5524258C
P 1250 4000
F 0 "C4" H 1250 4100 39  0000 L CNN
F 1 "0,1micF" H 1256 3915 39  0000 L CNN
F 2 "~" H 1288 3850 30  0000 C CNN
F 3 "~" H 1250 4000 60  0000 C CNN
	1    1250 4000
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 55242592
P 1700 3800
F 0 "R4" V 1780 3800 40  0000 C CNN
F 1 "100ohm" V 1707 3801 40  0000 C CNN
F 2 "~" V 1630 3800 30  0000 C CNN
F 3 "~" H 1700 3800 30  0000 C CNN
	1    1700 3800
	0    -1   -1   0   
$EndComp
$Comp
L DGND #PWR05
U 1 1 5524259B
P 1250 4350
F 0 "#PWR05" H 1250 4350 40  0001 C CNN
F 1 "DGND" H 1250 4280 40  0000 C CNN
F 2 "" H 1250 4350 60  0000 C CNN
F 3 "" H 1250 4350 60  0000 C CNN
	1    1250 4350
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 552425AE
P 1250 4950
F 0 "C5" H 1250 5050 39  0000 L CNN
F 1 "0,1micF" H 1256 4865 39  0000 L CNN
F 2 "~" H 1288 4800 30  0000 C CNN
F 3 "~" H 1250 4950 60  0000 C CNN
	1    1250 4950
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 552425B4
P 1700 4750
F 0 "R5" V 1780 4750 40  0000 C CNN
F 1 "100ohm" V 1707 4751 40  0000 C CNN
F 2 "~" V 1630 4750 30  0000 C CNN
F 3 "~" H 1700 4750 30  0000 C CNN
	1    1700 4750
	0    -1   -1   0   
$EndComp
$Comp
L DGND #PWR06
U 1 1 552425BD
P 1250 5200
F 0 "#PWR06" H 1250 5200 40  0001 C CNN
F 1 "DGND" H 1250 5130 40  0000 C CNN
F 2 "" H 1250 5200 60  0000 C CNN
F 3 "" H 1250 5200 60  0000 C CNN
	1    1250 5200
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 552425C4
P 1250 5700
F 0 "C6" H 1250 5800 39  0000 L CNN
F 1 "0,1micF" H 1256 5615 39  0000 L CNN
F 2 "~" H 1288 5550 30  0000 C CNN
F 3 "~" H 1250 5700 60  0000 C CNN
	1    1250 5700
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 552425CA
P 1700 5500
F 0 "R6" V 1780 5500 40  0000 C CNN
F 1 "100ohm" V 1707 5501 40  0000 C CNN
F 2 "~" V 1630 5500 30  0000 C CNN
F 3 "~" H 1700 5500 30  0000 C CNN
	1    1700 5500
	0    -1   -1   0   
$EndComp
$Comp
L DGND #PWR07
U 1 1 552425D3
P 1250 5950
F 0 "#PWR07" H 1250 5950 40  0001 C CNN
F 1 "DGND" H 1250 5880 40  0000 C CNN
F 2 "" H 1250 5950 60  0000 C CNN
F 3 "" H 1250 5950 60  0000 C CNN
	1    1250 5950
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 552426B8
P 1250 6500
F 0 "C7" H 1250 6600 39  0000 L CNN
F 1 "0,1micF" H 1256 6415 39  0000 L CNN
F 2 "~" H 1288 6350 30  0000 C CNN
F 3 "~" H 1250 6500 60  0000 C CNN
	1    1250 6500
	1    0    0    -1  
$EndComp
$Comp
L R R7
U 1 1 552426BE
P 1700 6300
F 0 "R7" V 1780 6300 40  0000 C CNN
F 1 "100ohm" V 1707 6301 40  0000 C CNN
F 2 "~" V 1630 6300 30  0000 C CNN
F 3 "~" H 1700 6300 30  0000 C CNN
	1    1700 6300
	0    -1   -1   0   
$EndComp
$Comp
L DGND #PWR08
U 1 1 552426C6
P 1250 6750
F 0 "#PWR08" H 1250 6750 40  0001 C CNN
F 1 "DGND" H 1250 6680 40  0000 C CNN
F 2 "" H 1250 6750 60  0000 C CNN
F 3 "" H 1250 6750 60  0000 C CNN
	1    1250 6750
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 552426CD
P 1250 7200
F 0 "C8" H 1250 7300 39  0000 L CNN
F 1 "0,1micF" H 1256 7115 39  0000 L CNN
F 2 "~" H 1288 7050 30  0000 C CNN
F 3 "~" H 1250 7200 60  0000 C CNN
	1    1250 7200
	1    0    0    -1  
$EndComp
$Comp
L R R8
U 1 1 552426D3
P 1700 7000
F 0 "R8" V 1780 7000 40  0000 C CNN
F 1 "100ohm" V 1707 7001 40  0000 C CNN
F 2 "~" V 1630 7000 30  0000 C CNN
F 3 "~" H 1700 7000 30  0000 C CNN
	1    1700 7000
	0    -1   -1   0   
$EndComp
$Comp
L DGND #PWR09
U 1 1 552426DB
P 1250 7450
F 0 "#PWR09" H 1250 7450 40  0001 C CNN
F 1 "DGND" H 1250 7380 40  0000 C CNN
F 2 "" H 1250 7450 60  0000 C CNN
F 3 "" H 1250 7450 60  0000 C CNN
	1    1250 7450
	1    0    0    -1  
$EndComp
$Comp
L MAX232_TID U1
U 1 1 5524333D
P 6150 5100
F 0 "U1" H 6150 5100 60  0000 C CNN
F 1 "MAX232_TID" H 6150 5100 60  0000 C CNN
F 2 "" H 6150 5100 60  0000 C CNN
F 3 "" H 6150 5100 60  0000 C CNN
	1    6150 5100
	1    0    0    -1  
$EndComp
$Comp
L C C31
U 1 1 5526D3CB
P 4750 5200
F 0 "C31" H 4750 5300 40  0000 L CNN
F 1 "0,1mF" H 4756 5115 40  0000 L CNN
F 2 "~" H 4788 5050 30  0000 C CNN
F 3 "~" H 4750 5200 60  0000 C CNN
	1    4750 5200
	1    0    0    -1  
$EndComp
$Comp
L C C32
U 1 1 5526DBBB
P 7450 4750
F 0 "C32" H 7450 4850 40  0000 L CNN
F 1 "0,1micF" H 7456 4665 40  0000 L CNN
F 2 "~" H 7488 4600 30  0000 C CNN
F 3 "~" H 7450 4750 60  0000 C CNN
	1    7450 4750
	1    0    0    -1  
$EndComp
$Comp
L C C34
U 1 1 5526DE58
P 6950 5150
F 0 "C34" H 6950 5250 40  0000 L CNN
F 1 "0,1micF" H 6956 5065 40  0000 L CNN
F 2 "~" H 6988 5000 30  0000 C CNN
F 3 "~" H 6950 5150 60  0000 C CNN
	1    6950 5150
	0    -1   -1   0   
$EndComp
$Comp
L C C33
U 1 1 5526E07D
P 7850 4750
F 0 "C33" H 7850 4850 40  0000 L CNN
F 1 "0,1micF" H 7856 4665 40  0000 L CNN
F 2 "~" H 7888 4600 30  0000 C CNN
F 3 "~" H 7850 4750 60  0000 C CNN
	1    7850 4750
	1    0    0    -1  
$EndComp
$Comp
L C C30
U 1 1 5526E163
P 4750 4650
F 0 "C30" H 4750 4750 40  0000 L CNN
F 1 "0,1mF" H 4756 4565 40  0000 L CNN
F 2 "~" H 4788 4500 30  0000 C CNN
F 3 "~" H 4750 4650 60  0000 C CNN
	1    4750 4650
	1    0    0    -1  
$EndComp
$Comp
L JUMPER JP1
U 1 1 5527D125
P 4350 5950
F 0 "JP1" H 4350 6100 60  0000 C CNN
F 1 "JUMPER" H 4350 5870 40  0000 C CNN
F 2 "~" H 4350 5950 60  0000 C CNN
F 3 "~" H 4350 5950 60  0000 C CNN
	1    4350 5950
	1    0    0    -1  
$EndComp
$Comp
L JUMPER JP2
U 1 1 5527D134
P 4350 6300
F 0 "JP2" H 4350 6450 60  0000 C CNN
F 1 "JUMPER" H 4350 6220 40  0000 C CNN
F 2 "~" H 4350 6300 60  0000 C CNN
F 3 "~" H 4350 6300 60  0000 C CNN
	1    4350 6300
	1    0    0    -1  
$EndComp
$Comp
L JUMPER JP3
U 1 1 5527D143
P 4350 6650
F 0 "JP3" H 4350 6800 60  0000 C CNN
F 1 "JUMPER" H 4350 6570 40  0000 C CNN
F 2 "~" H 4350 6650 60  0000 C CNN
F 3 "~" H 4350 6650 60  0000 C CNN
	1    4350 6650
	1    0    0    -1  
$EndComp
$Comp
L JUMPER JP4
U 1 1 5527D152
P 4350 7000
F 0 "JP4" H 4350 7150 60  0000 C CNN
F 1 "JUMPER" H 4350 6920 40  0000 C CNN
F 2 "~" H 4350 7000 60  0000 C CNN
F 3 "~" H 4350 7000 60  0000 C CNN
	1    4350 7000
	1    0    0    -1  
$EndComp
$Comp
L LM2937 U2
U 1 1 552C2C12
P 7000 1000
F 0 "U2" H 6700 1225 50  0000 L BNN
F 1 "LM2937" H 6700 1125 50  0000 L BNN
F 2 "linear2-TO263-3" H 7000 1150 50  0001 C CNN
F 3 "" H 7000 1000 60  0000 C CNN
	1    7000 1000
	1    0    0    -1  
$EndComp
$Comp
L JACK_2P J1
U 1 1 552C2D9E
P 10300 1150
F 0 "J1" H 9950 950 60  0000 C CNN
F 1 "JACK_2P" H 10150 1400 60  0000 C CNN
F 2 "~" H 10300 1150 60  0000 C CNN
F 3 "~" H 10300 1150 60  0000 C CNN
	1    10300 1150
	-1   0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR010
U 1 1 552C3CA0
P 9450 1750
F 0 "#PWR010" H 9450 1800 40  0001 C CNN
F 1 "GNDPWR" H 9450 1670 40  0000 C CNN
F 2 "" H 9450 1750 60  0000 C CNN
F 3 "" H 9450 1750 60  0000 C CNN
	1    9450 1750
	1    0    0    -1  
$EndComp
$Comp
L JUMPER3 JP9
U 1 1 552C4328
P 8900 1000
F 0 "JP9" H 8950 900 40  0000 L CNN
F 1 "JUMPER3" H 8900 1100 40  0000 C CNN
F 2 "~" H 8900 1000 60  0000 C CNN
F 3 "~" H 8900 1000 60  0000 C CNN
	1    8900 1000
	0    1    1    0   
$EndComp
$Comp
L C C17
U 1 1 552C4886
P 7700 1250
F 0 "C17" H 7700 1350 40  0000 L CNN
F 1 "C" H 7706 1165 40  0000 L CNN
F 2 "~" H 7738 1100 30  0000 C CNN
F 3 "~" H 7700 1250 60  0000 C CNN
	1    7700 1250
	1    0    0    -1  
$EndComp
$Comp
L C C18
U 1 1 552C4920
P 8250 1250
F 0 "C18" H 8250 1350 40  0000 L CNN
F 1 "10uF" H 8256 1165 40  0000 L CNN
F 2 "~" H 8288 1100 30  0000 C CNN
F 3 "~" H 8250 1250 60  0000 C CNN
	1    8250 1250
	1    0    0    -1  
$EndComp
$Comp
L C C16
U 1 1 552C4D78
P 6400 1250
F 0 "C16" H 6400 1350 40  0000 L CNN
F 1 "15uF" H 6406 1165 40  0000 L CNN
F 2 "~" H 6438 1100 30  0000 C CNN
F 3 "~" H 6400 1250 60  0000 C CNN
	1    6400 1250
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 552C5247
P 5650 1000
F 0 "R10" V 5730 1000 40  0000 C CNN
F 1 "2.0" V 5657 1001 40  0000 C CNN
F 2 "~" V 5580 1000 30  0000 C CNN
F 3 "~" H 5650 1000 30  0000 C CNN
	1    5650 1000
	0    -1   -1   0   
$EndComp
$Comp
L R R12
U 1 1 552C5256
P 5900 900
F 0 "R12" V 5980 900 40  0000 C CNN
F 1 "2.0" V 5907 901 40  0000 C CNN
F 2 "~" V 5830 900 30  0000 C CNN
F 3 "~" H 5900 900 30  0000 C CNN
	1    5900 900 
	0    -1   -1   0   
$EndComp
$Comp
L R R11
U 1 1 552C5265
P 5900 750
F 0 "R11" V 5980 750 40  0000 C CNN
F 1 "2.0" V 5907 751 40  0000 C CNN
F 2 "~" V 5830 750 30  0000 C CNN
F 3 "~" H 5900 750 30  0000 C CNN
	1    5900 750 
	0    -1   -1   0   
$EndComp
$Comp
L C C14
U 1 1 552C560E
P 5100 1250
F 0 "C14" H 5100 1350 40  0000 L CNN
F 1 "0,1micF" H 5106 1165 40  0000 L CNN
F 2 "~" H 5138 1100 30  0000 C CNN
F 3 "~" H 5100 1250 60  0000 C CNN
	1    5100 1250
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 552C5629
P 4750 1250
F 0 "C13" H 4750 1350 40  0000 L CNN
F 1 "0,1micF" H 4756 1165 40  0000 L CNN
F 2 "~" H 4788 1100 30  0000 C CNN
F 3 "~" H 4750 1250 60  0000 C CNN
	1    4750 1250
	1    0    0    -1  
$EndComp
$Comp
L +3,3V #PWR011
U 1 1 552C5A6E
P 4500 1000
F 0 "#PWR011" H 4500 960 30  0001 C CNN
F 1 "+3,3V" H 4500 1110 30  0000 C CNN
F 2 "" H 4500 1000 60  0000 C CNN
F 3 "" H 4500 1000 60  0000 C CNN
	1    4500 1000
	0    -1   -1   0   
$EndComp
$Comp
L C C12
U 1 1 552C5E2A
P 3850 1300
F 0 "C12" H 3850 1400 40  0000 L CNN
F 1 "0,1micF" H 3856 1215 40  0000 L CNN
F 2 "~" H 3888 1150 30  0000 C CNN
F 3 "~" H 3850 1300 60  0000 C CNN
	1    3850 1300
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 552C5E39
P 3450 1300
F 0 "C11" H 3450 1400 40  0000 L CNN
F 1 "1micF" H 3456 1215 40  0000 L CNN
F 2 "~" H 3488 1150 30  0000 C CNN
F 3 "~" H 3450 1300 60  0000 C CNN
	1    3450 1300
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR012
U 1 1 552C5FBB
P 3850 1600
F 0 "#PWR012" H 3850 1650 40  0001 C CNN
F 1 "GNDPWR" H 3850 1520 40  0000 C CNN
F 2 "" H 3850 1600 60  0000 C CNN
F 3 "" H 3850 1600 60  0000 C CNN
	1    3850 1600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 552C5FCA
P 3450 1600
F 0 "#PWR013" H 3450 1600 30  0001 C CNN
F 1 "GND" H 3450 1530 30  0001 C CNN
F 2 "" H 3450 1600 60  0000 C CNN
F 3 "" H 3450 1600 60  0000 C CNN
	1    3450 1600
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 552C6235
P 3000 850
F 0 "C10" H 3000 950 40  0000 L CNN
F 1 "0,1micF" H 3006 765 40  0000 L CNN
F 2 "~" H 3038 700 30  0000 C CNN
F 3 "~" H 3000 850 60  0000 C CNN
	1    3000 850 
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 552C6244
P 2700 850
F 0 "C9" H 2700 950 40  0000 L CNN
F 1 "0,1micF" H 2706 765 40  0000 L CNN
F 2 "~" H 2738 700 30  0000 C CNN
F 3 "~" H 2700 850 60  0000 C CNN
	1    2700 850 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 552C6618
P 2700 1150
F 0 "#PWR014" H 2700 1150 30  0001 C CNN
F 1 "GND" H 2700 1080 30  0001 C CNN
F 2 "" H 2700 1150 60  0000 C CNN
F 3 "" H 2700 1150 60  0000 C CNN
	1    2700 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 2900 1450 2900
Connection ~ 1250 2900
Wire Wire Line
	1000 2050 1450 2050
Connection ~ 1250 2050
Wire Wire Line
	1250 2450 1250 2300
Wire Wire Line
	1000 1300 1450 1300
Connection ~ 1250 1300
Wire Wire Line
	1250 2250 1250 2100
Wire Wire Line
	1000 3800 1450 3800
Connection ~ 1250 3800
Wire Wire Line
	1000 4750 1450 4750
Connection ~ 1250 4750
Wire Wire Line
	1000 5500 1450 5500
Connection ~ 1250 5500
Wire Wire Line
	2150 2900 2600 2900
Wire Wire Line
	2150 1300 2150 2900
Wire Wire Line
	2150 1300 1950 1300
Wire Wire Line
	2100 3000 2600 3000
Wire Wire Line
	2100 2050 2100 3000
Wire Wire Line
	2100 2050 1950 2050
Wire Wire Line
	1950 3100 2600 3100
Wire Wire Line
	2600 3200 1950 3200
Wire Wire Line
	1950 3200 1950 3800
Wire Wire Line
	2600 3300 2050 3300
Wire Wire Line
	2050 3300 2050 4750
Wire Wire Line
	2050 4750 1950 4750
Wire Wire Line
	2600 3400 2100 3400
Wire Wire Line
	2100 3400 2100 5500
Wire Wire Line
	2100 5500 1950 5500
Wire Wire Line
	2600 3500 2150 3500
Wire Wire Line
	1000 6300 1450 6300
Connection ~ 1250 6300
Wire Wire Line
	1000 7000 1450 7000
Connection ~ 1250 7000
Wire Wire Line
	2150 3500 2150 6300
Wire Wire Line
	2600 3600 2200 3600
Wire Wire Line
	2200 3600 2200 7000
Wire Wire Line
	2600 2700 2600 1900
Wire Wire Line
	2600 1900 4200 1900
Wire Wire Line
	4200 1900 4200 3700
Wire Wire Line
	4200 3700 4750 3700
Wire Wire Line
	4000 3100 4100 3100
Wire Wire Line
	4100 3100 4100 5875
Wire Wire Line
	4000 3200 4050 3200
Wire Wire Line
	4050 3200 4050 5700
Wire Wire Line
	2500 4200 2600 4200
Wire Wire Line
	2500 4200 2500 5950
Wire Wire Line
	2600 4300 2600 6300
Wire Wire Line
	5150 5550 5150 5500
Wire Wire Line
	5150 5500 5450 5500
Wire Wire Line
	4750 4850 5450 4850
Wire Wire Line
	4750 4450 5150 4450
Wire Wire Line
	5150 4450 5150 4600
Wire Wire Line
	5150 4600 5450 4600
Wire Wire Line
	5450 5000 4750 5000
Wire Wire Line
	4750 5400 5150 5400
Wire Wire Line
	5150 5400 5150 5250
Wire Wire Line
	5150 5250 5450 5250
Wire Wire Line
	6750 5500 6950 5500
Wire Wire Line
	6950 5500 6950 5400
Wire Wire Line
	6950 5400 7150 5400
Wire Wire Line
	6750 5700 7150 5700
Wire Wire Line
	6750 5800 6950 5800
Wire Wire Line
	6950 5800 6950 6500
Wire Wire Line
	7150 5700 7150 6100
Wire Wire Line
	6750 4650 6750 4450
Wire Wire Line
	6750 4450 7850 4450
Wire Wire Line
	6750 5150 6750 5100
Wire Wire Line
	6750 4750 6850 4750
Wire Wire Line
	6850 4750 6850 4550
Wire Wire Line
	6850 4550 7450 4550
Wire Wire Line
	7150 5150 7150 5000
Connection ~ 7150 5000
Wire Wire Line
	6750 5000 8800 5000
Wire Wire Line
	7450 4950 7450 5000
Connection ~ 7450 5000
Wire Wire Line
	7850 4200 7850 4550
Wire Wire Line
	7850 4950 7850 5000
Connection ~ 7850 5000
Wire Wire Line
	4750 3700 4750 3900
Wire Wire Line
	4750 3900 5900 3900
Wire Wire Line
	4000 3600 5850 3600
Wire Wire Line
	2200 7000 1950 7000
Connection ~ 2200 5800
Wire Wire Line
	2150 6300 1950 6300
Wire Wire Line
	1950 3100 1950 2900
Wire Wire Line
	8800 5000 8800 5200
Wire Wire Line
	2500 5950 4050 5950
Wire Wire Line
	2600 6300 4050 6300
Wire Wire Line
	4050 5700 3850 5700
Wire Wire Line
	3850 5700 3850 6650
Wire Wire Line
	3850 6650 4050 6650
Wire Wire Line
	4100 5875 3900 5875
Wire Wire Line
	3900 5875 3900 7000
Wire Wire Line
	3900 7000 4050 7000
Wire Wire Line
	4650 5950 4650 5550
Wire Wire Line
	4650 5550 5150 5550
Wire Wire Line
	4650 6300 4925 6300
Wire Wire Line
	4925 6300 4925 5700
Wire Wire Line
	4925 5700 5450 5700
Wire Wire Line
	4650 7000 4675 7000
Wire Wire Line
	4675 7000 4675 6850
Wire Wire Line
	4675 6850 5325 6850
Wire Wire Line
	5325 6850 5325 5800
Wire Wire Line
	5325 5800 5450 5800
Wire Wire Line
	4650 6650 4850 6650
Wire Wire Line
	4850 6650 4850 5600
Wire Wire Line
	4850 5600 5450 5600
Wire Wire Line
	4000 4600 4000 4100
Wire Wire Line
	4000 4100 4350 4100
Wire Wire Line
	4000 4700 4150 4700
Wire Wire Line
	4150 4700 4150 4250
Wire Wire Line
	4150 4250 4500 4250
Wire Wire Line
	9450 1250 9850 1250
Connection ~ 9700 1250
Wire Wire Line
	9450 1150 9450 1750
Connection ~ 9450 1250
Wire Wire Line
	4750 1500 9450 1500
Connection ~ 9450 1500
Connection ~ 9450 1150
Wire Wire Line
	9850 1150 9450 1150
Wire Wire Line
	9850 1000 9150 1000
Wire Wire Line
	9150 1000 9150 1250
Wire Wire Line
	9150 1250 8900 1250
Wire Wire Line
	7400 1000 8800 1000
Connection ~ 8550 1000
Wire Wire Line
	8250 1000 8250 1050
Wire Wire Line
	8250 1500 8250 1450
Wire Wire Line
	7700 1500 7700 1450
Connection ~ 8250 1500
Wire Wire Line
	7700 1000 7700 1050
Connection ~ 8250 1000
Connection ~ 7700 1000
Wire Wire Line
	7000 1500 7000 1300
Connection ~ 7700 1500
Connection ~ 7000 1500
Wire Wire Line
	5900 1000 6600 1000
Wire Wire Line
	6400 600  6400 1050
Wire Wire Line
	6400 1500 6400 1450
Connection ~ 6400 1000
Wire Wire Line
	6400 750  6150 750 
Connection ~ 6400 750 
Wire Wire Line
	6400 900  6150 900 
Connection ~ 6400 900 
Connection ~ 6400 1500
Wire Wire Line
	4500 1000 5400 1000
Wire Wire Line
	3850 900  5650 900 
Wire Wire Line
	5650 750  3900 750 
Wire Wire Line
	3900 750  3900 650 
Wire Wire Line
	5100 1000 5100 1050
Wire Wire Line
	5100 1500 5100 1450
Wire Wire Line
	4750 1500 4750 1450
Connection ~ 5100 1500
Wire Wire Line
	4750 1050 4750 1000
Connection ~ 5100 1000
Wire Wire Line
	3850 1100 3850 900 
Connection ~ 3850 1100
Wire Wire Line
	3850 1500 3450 1500
Wire Wire Line
	3450 1500 3450 1600
Wire Wire Line
	3850 1500 3850 1600
Wire Wire Line
	3900 650  2450 650 
Connection ~ 3000 650 
Connection ~ 2700 650 
Wire Wire Line
	2700 1050 3000 1050
Wire Wire Line
	2700 1050 2700 1150
Wire Wire Line
	3300 1100 3850 1100
Wire Wire Line
	3200 1300 2450 1300
Wire Wire Line
	2450 1300 2450 650 
Wire Wire Line
	5400 2700 4500 2700
Wire Wire Line
	4500 2700 4500 4250
Wire Wire Line
	5400 2400 4350 2400
Wire Wire Line
	4350 2400 4350 4100
Wire Wire Line
	8900 650  8900 750 
Wire Wire Line
	8650 650  8900 650 
Wire Wire Line
	3300 5100 3500 5100
Wire Wire Line
	3500 5100 3500 5400
$Comp
L GNDPWR #PWR015
U 1 1 552C76EE
P 3500 5400
F 0 "#PWR015" H 3500 5450 40  0001 C CNN
F 1 "GNDPWR" H 3500 5320 40  0000 C CNN
F 2 "" H 3500 5400 60  0000 C CNN
F 3 "" H 3500 5400 60  0000 C CNN
	1    3500 5400
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR016
U 1 1 552C76FD
P 8800 5200
F 0 "#PWR016" H 8800 5250 40  0001 C CNN
F 1 "GNDPWR" H 8800 5120 40  0000 C CNN
F 2 "" H 8800 5200 60  0000 C CNN
F 3 "" H 8800 5200 60  0000 C CNN
	1    8800 5200
	1    0    0    -1  
$EndComp
$Comp
L +3,3V #PWR017
U 1 1 552C770C
P 7850 4200
F 0 "#PWR017" H 7850 4160 30  0001 C CNN
F 1 "+3,3V" H 7850 4310 30  0000 C CNN
F 2 "" H 7850 4200 60  0000 C CNN
F 3 "" H 7850 4200 60  0000 C CNN
	1    7850 4200
	1    0    0    -1  
$EndComp
Connection ~ 7850 4450
$Comp
L R R9
U 1 1 552D4B36
P 5050 1850
F 0 "R9" V 5130 1850 40  0000 C CNN
F 1 "470" V 5057 1851 40  0000 C CNN
F 2 "~" V 4980 1850 30  0000 C CNN
F 3 "~" H 5050 1850 30  0000 C CNN
	1    5050 1850
	0    -1   -1   0   
$EndComp
$Comp
L LED PWR1
U 1 1 552D4B5B
P 5700 1850
F 0 "PWR1" H 5700 1950 50  0000 C CNN
F 1 "LED" H 5700 1750 50  0000 C CNN
F 2 "~" H 5700 1850 60  0000 C CNN
F 3 "~" H 5700 1850 60  0000 C CNN
	1    5700 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 1850 5500 1850
$Comp
L R R13
U 1 1 552D4E68
P 7400 3300
F 0 "R13" V 7480 3300 40  0000 C CNN
F 1 "470" V 7407 3301 40  0000 C CNN
F 2 "~" V 7330 3300 30  0000 C CNN
F 3 "~" H 7400 3300 30  0000 C CNN
	1    7400 3300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7650 3300 7800 3300
$Comp
L LED Prueba1
U 1 1 552D503B
P 8000 3300
F 0 "Prueba1" H 8000 3400 50  0000 C CNN
F 1 "LED" H 8000 3200 50  0000 C CNN
F 2 "~" H 8000 3300 60  0000 C CNN
F 3 "~" H 8000 3300 60  0000 C CNN
	1    8000 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 4200 1250 4350
$Comp
L +3,3V #PWR018
U 1 1 55313060
P 4700 1800
F 0 "#PWR018" H 4700 1760 30  0001 C CNN
F 1 "+3,3V" H 4700 1910 30  0000 C CNN
F 2 "" H 4700 1800 60  0000 C CNN
F 3 "" H 4700 1800 60  0000 C CNN
	1    4700 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 1850 4700 1850
Wire Wire Line
	4700 1850 4700 1800
$Comp
L PINHD-1X1 Vref+1
U 1 1 553FBF3A
P 5950 3600
F 0 "Vref+1" H 5700 3725 50  0000 L BNN
F 1 "PINHD-1X1" H 5700 3400 50  0000 L BNN
F 2 "pinhead-1X01" H 5950 3750 50  0001 C CNN
F 3 "" H 5950 3600 60  0000 C CNN
	1    5950 3600
	1    0    0    -1  
$EndComp
$Comp
L PINHD-1X1 Vref-1
U 1 1 553FC02E
P 6000 3900
F 0 "Vref-1" H 5750 4025 50  0000 L BNN
F 1 "PINHD-1X1" H 5750 3700 50  0000 L BNN
F 2 "pinhead-1X01" H 6000 4050 50  0001 C CNN
F 3 "" H 6000 3900 60  0000 C CNN
	1    6000 3900
	1    0    0    -1  
$EndComp
$Comp
L PINHD-1X1 PIN1
U 1 1 553FC122
P 8550 650
F 0 "PIN1" H 8300 775 50  0000 L BNN
F 1 "PINHD-1X1" H 8300 450 50  0000 L BNN
F 2 "pinhead-1X01" H 8550 800 50  0001 C CNN
F 3 "" H 8550 650 60  0000 C CNN
	1    8550 650 
	-1   0    0    -1  
$EndComp
$Comp
L PINHD-1X1 XRX1
U 1 1 553FC5D5
P 8550 5300
F 0 "XRX1" H 8300 5425 50  0000 L BNN
F 1 "PINHD-1X1" H 8300 5100 50  0000 L BNN
F 2 "pinhead-1X01" H 8550 5450 50  0001 C CNN
F 3 "" H 8550 5300 60  0000 C CNN
	1    8550 5300
	1    0    0    -1  
$EndComp
$Comp
L PINHD-1X1 XCTS1
U 1 1 553FC5E4
P 8550 5700
F 0 "XCTS1" H 8300 5825 50  0000 L BNN
F 1 "PINHD-1X1" H 8300 5500 50  0000 L BNN
F 2 "pinhead-1X01" H 8550 5850 50  0001 C CNN
F 3 "" H 8550 5700 60  0000 C CNN
	1    8550 5700
	1    0    0    -1  
$EndComp
$Comp
L PINHD-1X1 XTX1
U 1 1 553FC5F3
P 8550 6100
F 0 "XTX1" H 8300 6225 50  0000 L BNN
F 1 "PINHD-1X1" H 8300 5900 50  0000 L BNN
F 2 "pinhead-1X01" H 8550 6250 50  0001 C CNN
F 3 "" H 8550 6100 60  0000 C CNN
	1    8550 6100
	1    0    0    -1  
$EndComp
$Comp
L PINHD-1X1 XRTS1
U 1 1 553FC602
P 8550 6500
F 0 "XRTS1" H 8300 6625 50  0000 L BNN
F 1 "PINHD-1X1" H 8300 6300 50  0000 L BNN
F 2 "pinhead-1X01" H 8550 6650 50  0001 C CNN
F 3 "" H 8550 6500 60  0000 C CNN
	1    8550 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 5400 7150 5300
Wire Wire Line
	7150 5300 8450 5300
Wire Wire Line
	8450 5700 7750 5700
Wire Wire Line
	7750 5700 7750 5600
Wire Wire Line
	7750 5600 6750 5600
Wire Wire Line
	7150 6100 8450 6100
Wire Wire Line
	6950 6500 8450 6500
NoConn ~ 2600 4400
NoConn ~ 2600 4500
NoConn ~ 4000 3400
Connection ~ 1250 4350
Connection ~ 1250 4200
Wire Wire Line
	1250 6750 1250 6700
Wire Wire Line
	1250 5950 1250 5900
Connection ~ 1250 5950
Wire Wire Line
	3100 5400 3100 5100
$Comp
L GND #PWR019
U 1 1 553FFE63
P 6050 1900
F 0 "#PWR019" H 6050 1900 30  0001 C CNN
F 1 "GND" H 6050 1830 30  0001 C CNN
F 2 "" H 6050 1900 60  0000 C CNN
F 3 "" H 6050 1900 60  0000 C CNN
	1    6050 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 1850 6050 1850
Wire Wire Line
	6050 1850 6050 1900
$Comp
L GND #PWR020
U 1 1 553FFF60
P 8400 3350
F 0 "#PWR020" H 8400 3350 30  0001 C CNN
F 1 "GND" H 8400 3280 30  0001 C CNN
F 2 "" H 8400 3350 60  0000 C CNN
F 3 "" H 8400 3350 60  0000 C CNN
	1    8400 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 3300 8400 3300
Wire Wire Line
	8400 3300 8400 3350
Wire Wire Line
	1250 5200 1250 5150
Wire Wire Line
	3400 2300 3400 1750
Wire Wire Line
	3400 1750 3300 1750
Wire Wire Line
	3300 1750 3300 1100
Connection ~ 3450 1100
Connection ~ 4750 1000
Connection ~ 4050 900 
Wire Wire Line
	4050 1000 4050 900 
$Comp
L C8051F352 +1
U 1 1 5524216A
P 3300 2700
F 0 "+1" H 3300 2700 60  0000 C CNN
F 1 "C8051F352" H 3300 2700 60  0000 C CNN
F 2 "" H 3300 2700 60  0000 C CNN
F 3 "" H 3300 2700 60  0000 C CNN
	1    3300 2700
	1    0    0    -1  
$EndComp
$Comp
L VDD #PWR021
U 1 1 552C5BF6
P 4050 1000
F 0 "#PWR021" H 4050 1100 30  0001 C CNN
F 1 "VDD" H 4050 1110 30  0000 C CNN
F 2 "" H 4050 1000 60  0000 C CNN
F 3 "" H 4050 1000 60  0000 C CNN
	1    4050 1000
	1    0    0    1   
$EndComp
Connection ~ 3500 5400
Connection ~ 3100 5100
Wire Wire Line
	3200 2300 3200 1300
Wire Wire Line
	1250 7400 1250 7450
Wire Wire Line
	1250 3300 1250 3350
$Comp
L PINHD-1X1 JP5
U 1 1 5547CCBB
P 5500 2400
F 0 "JP5" H 5250 2525 50  0000 L BNN
F 1 "PINHD-1X1" H 5250 2200 50  0000 L BNN
F 2 "pinhead-1X01" H 5500 2550 50  0001 C CNN
F 3 "" H 5500 2400 60  0000 C CNN
	1    5500 2400
	1    0    0    -1  
$EndComp
$Comp
L PINHD-1X1 JP6
U 1 1 5547CCCA
P 5500 2700
F 0 "JP6" H 5250 2825 50  0000 L BNN
F 1 "PINHD-1X1" H 5250 2500 50  0000 L BNN
F 2 "pinhead-1X01" H 5500 2850 50  0001 C CNN
F 3 "" H 5500 2700 60  0000 C CNN
	1    5500 2700
	1    0    0    -1  
$EndComp
$Comp
L PINHD-1X1 JP8
U 1 1 554D2DF9
P 8000 2250
F 0 "JP8" H 7750 2375 50  0000 L BNN
F 1 "PINHD-1X1" H 7750 2050 50  0000 L BNN
F 2 "pinhead-1X01" H 8000 2400 50  0001 C CNN
F 3 "" H 8000 2250 60  0000 C CNN
	1    8000 2250
	1    0    0    -1  
$EndComp
$Comp
L PINHD-1X1 JP10
U 1 1 554D2E08
P 8000 2650
F 0 "JP10" H 7750 2775 50  0000 L BNN
F 1 "PINHD-1X1" H 7750 2450 50  0000 L BNN
F 2 "pinhead-1X01" H 8000 2800 50  0001 C CNN
F 3 "" H 8000 2650 60  0000 C CNN
	1    8000 2650
	1    0    0    -1  
$EndComp
$Comp
L PINHD-1X1 JP7
U 1 1 554D2E17
P 8000 1850
F 0 "JP7" H 7750 1975 50  0000 L BNN
F 1 "PINHD-1X1" H 7750 1650 50  0000 L BNN
F 2 "pinhead-1X01" H 8000 2000 50  0001 C CNN
F 3 "" H 8000 1850 60  0000 C CNN
	1    8000 1850
	1    0    0    -1  
$EndComp
$Comp
L PINHD-1X1 JP11
U 1 1 554D2E26
P 8950 3000
F 0 "JP11" H 8700 3125 50  0000 L BNN
F 1 "PINHD-1X1" H 8700 2800 50  0000 L BNN
F 2 "pinhead-1X01" H 8950 3150 50  0001 C CNN
F 3 "" H 8950 3000 60  0000 C CNN
	1    8950 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 1850 7000 2100
Wire Wire Line
	7000 1850 7900 1850
Wire Wire Line
	2600 3800 2450 3800
Wire Wire Line
	2450 3800 2450 2100
Wire Wire Line
	2450 2100 7000 2100
Wire Wire Line
	7900 2250 2350 2250
Wire Wire Line
	2350 2250 2350 3900
Wire Wire Line
	2350 3900 2600 3900
Wire Wire Line
	2600 4000 2250 4000
Wire Wire Line
	2250 4000 2250 2000
Wire Wire Line
	2250 2000 6750 2000
Wire Wire Line
	6750 2000 6750 2650
Wire Wire Line
	6750 2650 7900 2650
Wire Wire Line
	8850 3000 8850 4550
Wire Wire Line
	8850 4550 9050 4550
Wire Wire Line
	9050 4550 9050 7050
Wire Wire Line
	9050 7050 4550 7050
Wire Wire Line
	4550 7050 4550 7200
Wire Wire Line
	4550 7200 2400 7200
Wire Wire Line
	2400 7200 2400 4100
Wire Wire Line
	2400 4100 2600 4100
NoConn ~ 4000 2700
NoConn ~ 4000 2800
NoConn ~ 4000 2900
NoConn ~ 4000 3000
$EndSCHEMATC
