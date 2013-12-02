/*
Test code for SD_HSMCI library

Initialises and reads the SD card properties before writing 5 files of between 5120 bytes
and 5120000 bytes to the root directory of the card. The time taken for each file write
and read is printed to the initialised Serial out. 512 is the blocksize set so this should
give optimum performance.

No checking for free space is done on the SD card.
Card detect works on the Duet, it will wait for a card to be inserted.

The SD_HSMCI library uses FatFs: see
http://elm-chan.org/fsw/ff/00index_e.html
for more info.
SD cards can be FAT or FAT32 formatted and be either SD or SDHC. exFAT and SDXC are not supported.

Tony@think3dprint3d
GPLv3

*/

#include "Arduino.h"
#include <SamNonDuePin.h>
#include <string.h>
#include <SD_HSMCI.h>

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


	// Initialize SD MMC stack
	sd_mmc_init();
	printf("Please plug in a card.\n\r");
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

