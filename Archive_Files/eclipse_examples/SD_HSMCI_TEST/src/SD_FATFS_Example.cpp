/*
Test code for FET outputs on DUET 0.3
Note on 0.3 the FETS come on automatically when 12V is applied (the driver fets invert
the logic)

Uses the Undefined Arduino Due Pins Library "UdefDuePin.h" to demonstrate PWM on
pins that are not defined as PWM within the DUE software but are on the SAM3X8E

Note no setup of the pins is required as this is carried out within the analogWriteUndefined()
function in the same way as it is done within the normal analogWrite() function in arduino.

On the Duet 0.3 the following pins are connected:
E0_PWM    PIO_PC8B_PWML3   // Undefined pin 5
FAN0_PWM  PIO_PC9B_PWMH3   // Undefined pin 6
BED_PWM   PIO_PB14B_PWMH2  // Undefined pin 7

E0_PWM and FAN0_PWM are connected to the same channel and are the compliment of each other
(when E0_PWM is set to 254 it is on, when FAN0_PWM is fet to 254 it is off)

Duet 0.4 will use only PWMLX pins and not connect the same channel to two pins!

Finally I am using the option of defining the Arduino Undef pins with a X in front of them,
this allows for easy distinguishing of them but is not required.
*/

#include "Arduino.h"
#include "SamNonDuePin.h"
#include <string.h>
#include "SD_HSMCI.h"

void performanceCheck(char const *testfile, uint32_t loop_counter,uint32_t buff_size)
{
	char const * test_file_name = testfile;
	FRESULT res;
	FATFS fs;
	FIL file_object;
	UINT br,bw, btw;
	btw = buff_size;
	BYTE RBuff[btw];		/* File read buffer */
	BYTE WBuff[btw];		/* File write buffer */
	uint32_t TEST_FILE_LOOP = loop_counter;
	uint32_t time_ms = 0;
	//fill the write buffer
	for (UINT i =0 ; i < btw; i++)
	{
		WBuff[i]=(BYTE)i;
	}
	memset(&fs, 0, sizeof(FATFS));
	//u_mount SD card
	f_mount (LUN_ID_SD_MMC_0_MEM, NULL);
	//mount SD card
	if (f_mount(LUN_ID_SD_MMC_0_MEM, &fs) != FR_INVALID_DRIVE) {
		//test_file_name[0] = LUN_ID_SD_MMC_0_MEM + '0'; //confirm the file is written to the mounted drive
		if (f_open(&file_object,
				(char const *)test_file_name,
				FA_CREATE_ALWAYS | FA_WRITE) == FR_OK){
			printf("File write check START\n");
			//start time
			time_ms = millis();
			for(uint32_t i = 0; i <TEST_FILE_LOOP; i++){
				if (f_write(&file_object, WBuff, btw, &bw) != FR_OK) {
					break;
				}
			}
			//Stop time
			time_ms = millis()-time_ms;
			printf("File write check FINISHED. Time %u ms\n",time_ms);
			f_close(&file_object);
			if (f_open(&file_object, (char *) testfile, FA_OPEN_EXISTING | FA_READ) == FR_OK){
				printf("File read check STARTED %s\n",(char *) testfile);
				//start time
				time_ms = millis();
				for (;;) {
					res = f_read(&file_object, RBuff, btw, &br);	// Read a chunk of file
					if (res || !br) break;			//Error or end of file
				}
				//Stop time
				time_ms = millis()-time_ms;
			    printf("File read check FINISHED. Time %u ms, Size %u bytes\n",time_ms, file_object.fsize);
				f_close(&file_object);
			}
	    }
	}
}

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
void setup (void)
{
	 Serial.begin(115200);
	 /* Configure HSMCI pins */
	hsmciPinsinit();

	printf("\n\r-- SD/MMC/SDIO Card Example on FatFs --\n\r");
	printf("-- Compiled: %s %s --\n\r",__DATE__,__TIME__);
	printf("Please plug in a card.\n\r");

	// Initialize SD MMC stack
	sd_mmc_init();

	while (CTRL_NO_PRESENT == sd_mmc_check(0)) {
	}
	//print card info
	printf("sd_mmc_card->capacity: %u bytes\n", sd_mmc_get_capacity(0));
	printf("sd_mmc_card->clock %u Hz\n",	sd_mmc_get_bus_clock(0));
	printf("sd_mmc_card->bus_width: %u \n", sd_mmc_get_bus_width(0));
	//performance check
	uint32_t buffer_size = 512;
	printf("Performance Check\r\n");
	char file1[] ="0:test1.txt";
	printf("Write/Read: %s \n",file1);
	performanceCheck((char const *)file1,10,buffer_size);
	char file2[] ="0:test2.txt";
	printf("Write/Read: %s \n",file2);
	performanceCheck((char const *)file2,100,buffer_size);
	char file3[] ="0:test3.txt";
	printf("Write/Read: %s \n",file3);
	performanceCheck((char const *)file3,1000,buffer_size);
	char file4[] ="0:test4.txt";
	printf("Write/Read: %s \n",file4);
	performanceCheck((char const *)file4,10000,buffer_size);
	char file5[] ="0:test5.txt";
	printf("Write/Read: %s \n",file5);
	performanceCheck((char const *)file5,100000,buffer_size);
	printf("Performance Check complete\r\n");
}

void loop(void){
}
