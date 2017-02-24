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
#include <nan.h>

//Below are inner functions.

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

void setOutput(uint16_t value){
	uint8_t data[2];
	data[0] = value & 0xff;
	data[1] = (value >> 8) & 0xff;
	if (write(i2cFile,data,2)!=2){
		perror("setOutput");
	}
}
//Above are inner functions

//the least significant bit(R/W) needs to be eliminated
//e.g. 0x20 would be the address in case where A2 A1 A0 are zero.
//Function need to be exposed to initialize i2c.
void i2cInit(const Nan::FunctionCallbackInfo<v8::Value>& info){
  if (info.Length() != 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  int address = info[0]->NumberValue();
	i2cOpen();
	i2cSetAddress(address);
}
void i2cClose(){
	close(i2cFile);
}

void getInput(const Nan::FunctionCallbackInfo<v8::Value>& info){
	uint8_t data[2];
	if(read(i2cFile,data,2)!=2){
		perror("getInput");
	}
	uint16_t val = data[0]|(data[1] << 8);
  info.GetReturnValue().Set(val);
}

void setLED1(const Nan::FunctionCallbackInfo<v8::Value>& info){
  Color c;
  if (info.Length() != 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  switch (info[0]->NumberValue) {
    case 0 : c = Blue; break;
    case 1 : c = Red; break;
    case 2 : c = Green; break;
    default: break;
  }
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

void setLED2(const Nan::FunctionCallbackInfo<v8::Value>& info){
  Color c;
  if (info.Length() != 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  switch (info[0]->NumberValue) {
    case 0 : c = Blue; break;
    case 1 : c = Red; break;
    case 2 : c = Green; break;
    default: break;
  }
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

void setLED3(const Nan::FunctionCallbackInfo<v8::Value>& info){
  Color c;
  if (info.Length() != 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  switch (info[0]->NumberValue) {
    case 0 : c = Blue; break;
    case 1 : c = Red; break;
    case 2 : c = Green; break;
    default: break;
  }
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


  void Init(v8::Local<v8::Object> exports) {
    exports->Set(Nan::New("i2cInit").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(i2cInit)->GetFunction());
    exports->Set(Nan::New("getInput").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(getInput)->GetFunction());
    exports->Set(Nan::New("setLED1").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(setLED1)->GetFunction());
    exports->Set(Nan::New("setLED2").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(setLED2)->GetFunction());
    exports->Set(Nan::New("setLED3").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(setLED3)->GetFunction());
    exports->Set(Nan::New("i2cClose").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(i2cClose)->GetFunction());
  }

  NODE_MODULE(pb, Init)
