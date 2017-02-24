#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

//I2C Linux device hanlde
int i2cFile;
uint16_t value = 0xEE07;
typedef int Color;
enum{Blue,Red,Green};


//open the Linux device
void i2cOpen(){
	int adapter_nr = 2;
	char filename[20];

	snprintf(filename,19,"/dev/i2c-%d", adapter_nr);
	i2cFile = open(filename, O_RDWR);
	if(i2cFile < 0){
		perror("i2cOpen");
		exit(1);
	}
}

void i2cClose(){
	close(i2cFile);
}

void i2cSetAddress(int address){
	if(ioctl(i2cFile, I2C_SLAVE, address) < 0){
		perror("i2cSetAddress");
		exit(1);
	}
}
//the least significant bit(R/W) needs to be eliminated
//e.g. 0x20 would be the address in case where A2 A1 A0 are zero.
void i2cInit(int address){
	i2cOpen();
	i2cSetAddress(address);
}

void setOutput(uint16_t value){
	uint8_t data[2];
	data[0] = value & 0xff;
	data[1] = (value >> 8) & 0xff;
	if (write(i2cFile,data,2)!=2){
		perror("setOutput");
	}
}
void setLED1(Color c){
	if (c == Blue){
		value |= 0x0001;
		value &= ~(0x0001 << 3);
		value &= ~(0x0001 << 6);
	}
	else if(c == Red){
		value |= (0x0001 << 3);
		value &= ~(0x0001 << 6);
		value &= ~(0x0001);
	}
	else if(c == Green){
		value |= (0x0001 << 6);
		value &= ~(0x0001 << 3);
		value &= ~(0x0001);
	}
}
void setLED2(Color c){
	if (c == Blue){
		value |= 0x0002;
		value &= ~(0x0002 << 3);
		value &= ~(0x0002 << 6);
	}
	else if(c == Red){
		value |= (0x0002 << 3);
		value &= ~(0x0002 << 6);
		value &= ~(0x0002);
	}
	else if(c == Green){
		value |= (0x0002 << 6);
		value &= ~(0x0002 << 3);
		value &= ~(0x0002);
	}
}
void setLED3(Color c){
	if (c == Blue){
		value |= 0x0004;
		value &= ~(0x0004 << 3);
		value &= ~(0x0004 << 6);
	}
	else if(c == Red){
		value |= (0x0004 << 3);
		value &= ~(0x0004 << 6);
		value &= ~(0x0004);
	}
	else if(c == Green){
		value |= (0x0004 << 6);
		value &= ~(0x0004 << 3);
		value &= ~(0x0004);
	}
}
uint16_t getInput(){
	uint8_t data[2];
	if(read(i2cFile,data,2)!=2){
		perror("getInput");
	}
	return data[0]|(data[1] << 8);
}

int main(int argc, char **argv)
{
	uint16_t mask = 0x8000;
	int addr = 0x20;
	i2cInit(addr);
	setLED1(Red);
	setLED2(Red);
	setLED3(Red);
	setOutput(value);
	int out = 0;
	while(1){
		out = getInput();
		if((out & mask) == mask){
			setLED3(Blue);
		}else{
			setLED3(Red);
		}
		if((out & (mask >> 1)) == (mask >> 1)){
			setLED2(Blue);
		}else{
			setLED2(Red);
		}
		if((out & (mask >> 2)) == (mask >> 2)){
			setLED1(Blue);
			setOutput(value);
		}else{
			setLED1(Red);
		}
		setOutput(value);
		sleep(0.5);
	}
	i2cClose();
}
