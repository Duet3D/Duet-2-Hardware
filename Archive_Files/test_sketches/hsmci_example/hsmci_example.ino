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
			SerialUSB.println("File write check START");
			//start time
			time_ms = millis();
			for(uint32_t i = 0; i <TEST_FILE_LOOP; i++){
                                res = f_write(&file_object, WBuff, btw, &bw);
				if (res != FR_OK) {
                                        SerialUSB.print("File write error: ");
                                        SerialUSB.println(res);
					break;
				}
			}
			//Stop time
			time_ms = millis()-time_ms;
			SerialUSB.print("File write check FINISHED. Time  ");
                        SerialUSB.print(time_ms);
                        SerialUSB.println(" ms");
			f_close(&file_object);
			if (f_open(&file_object, (char *) testfile, FA_OPEN_EXISTING | FA_READ) == FR_OK){
				SerialUSB.print("File read check STARTED ");
                                SerialUSB.println((char *) testfile);
				//start time
				time_ms = millis();
				for (;;) {
					res = f_read(&file_object, RBuff, btw, &br);	// Read a chunk of file
				        if (res != FR_OK) {
                                            SerialUSB.print("File read error: ");
                                            SerialUSB.println(res);
					    break;
				        }
					if (!br) break;			//end of file
				}
				//Stop time
				time_ms = millis()-time_ms;
			        SerialUSB.print("File read check FINISHED. Time ");
                                SerialUSB.print(time_ms);
                                SerialUSB.print(" ms, Size ");
                                SerialUSB.println(file_object.fsize);
				f_close(&file_object);
			}
	    }
	}
        else
          SerialUSB.println("mounting failed");
}

/**
 * \brief Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
void setup (void)
{
	SerialUSB.begin(115200);
        while(!SerialUSB){}
        
	SerialUSB.println("-- SD/MMC/SDIO Card Example on FatFs --");
         
         /* Configure HSMCI pins */
	hsmciPinsinit();

	// Initialize SD MMC stack
	sd_mmc_init();
	SerialUSB.println("Please plug in a card");
	while (CTRL_NO_PRESENT == sd_mmc_check(0)) {
	}
	//print card info
	SerialUSB.print("sd_mmc_card->capacity: "); SerialUSB.print(sd_mmc_get_capacity(0)); SerialUSB.println(" bytes");
	SerialUSB.print("sd_mmc_card->clock "); SerialUSB.print(sd_mmc_get_bus_clock(0)); SerialUSB.println(" Hz");
	SerialUSB.print("sd_mmc_card->bus_width: "); SerialUSB.println(sd_mmc_get_bus_width(0));

}

void loop(void){
 
  	//performance check
	uint32_t buffer_size = 512;
	SerialUSB.println("Performance Checking, don't eject card");
	char file[] ="0:test.txt";
	performanceCheck((char const *)file,1000,buffer_size); //500Kb fle
	SerialUSB.println("Performance Check complete");
        delay(10000);
}

