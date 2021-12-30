#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <signal.h>
#include <stdbool.h>
#include "sc16is750.h"

//Connect TX and RX with a wire

int main(int argc, char **argv){

	SC16IS750_t dev;
	
	if (argc < 3) {
		printf("USAGE:\n");
		printf("\t%s I2C i2c_address : For I2C\n", argv[0]);
		printf("\t%s SPI chip_select : For SPI\n", argv[0]);
		return 1;
	}
	
	if (strcmp(argv[1], "I2C") == 0) {
		long i2c_address = strtol(argv[2], NULL, 16);
		printf("i2c_addressr=%x\n", (uint8_t)i2c_address);
		SC16IS750_init(&dev, SC16IS750_PROTOCOL_I2C, (uint8_t)i2c_address);
	} else if (strcmp(argv[1], "SPI") == 0) {
		long chip_select = strtol(argv[2], NULL, 10);
		printf("chip_select=%ld\n", chip_select);
		SC16IS750_init(&dev, SC16IS750_PROTOCOL_SPI, (uint8_t)chip_select);
	} else {
		printf("USAGE:\n");
		printf("\t%s I2C i2c_address : For I2C\n", argv[0]);
		printf("\t%s SPI chip_select : For SPI\n", argv[0]);
		return 1;
	}

	// wiringPi Initialization
	if(wiringPiSetupGpio() == -1) {
		printf("wiringPiSetupGpio Fail\n");
		return 1;
	}

	// SC16IS752 Initialization
	SC16IS752_begin(&dev, SC16IS750_DEFAULT_SPEED, SC16IS750_DEFAULT_SPEED, 1843200UL); //baudrate&frequency setting
	if (SC16IS750_ping(&dev)!=1) {
		printf("device not found\n");
		return 1;
	} else {
		printf("device found\n");
	}
	printf("start serial communication\n");


	while(1) {
		SC16IS750_write(&dev, SC16IS752_CHANNEL_A, 0x55);
		while(SC16IS750_available(&dev, SC16IS752_CHANNEL_B)==0);
		if (SC16IS750_read(&dev, SC16IS752_CHANNEL_B)!=0x55) {
			printf("serial communication error\n");
			break;
		}	
		delay(200);

		SC16IS750_write(&dev, SC16IS752_CHANNEL_B, 0xAA);
		while(SC16IS750_available(&dev, SC16IS752_CHANNEL_A)==0);
		if (SC16IS750_read(&dev, SC16IS752_CHANNEL_A)!=0xAA) {
			printf("serial communication error\n");
			break;
		}	
		delay(200);
	}
	return 0;
}
