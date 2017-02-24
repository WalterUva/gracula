#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <nan.h>

#define IN 0
#define OUT 1

#define LOW 0
#define HIGH 1
#define BUFFER_MAX 3

//Export one pin at one time.
void GPIOExport(const Nan::FunctionCallbackInfo<v8::Value>& info){
  //argument checks
  if(info.Length() < 1){
    Nan::ThrowTypeError("Missing arguments");
    return;
  }
  if(!info[0] -> IsNumber()){
    Nan::ThrowTypeError("Invalid arguments");
    return;
  }
  int pin = info[0]->NumberValue();
  char buffer[BUFFER_MAX];
  ssize_t bytes_written;
	int fd;
	fd = open("/sys/class/gpio/export", O_WRONLY);
	if(-1 == fd){
		fprintf(stderr, "Failed to open export for writing!\n");
    Nan::ThrowError("Failed to open export for writing!\n");
		return;
	}
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d",pin);
	write(fd, buffer, bytes_written);
	close(fd);
}

void GPIOUnexport(const Nan::FunctionCallbackInfo<v8::Value>& info){
  if(info.Length() < 1){
    Nan::ThrowTypeError("Missing arguments");
    return;
  }
  if(!info[0] -> IsNumber()){
    Nan::ThrowTypeError("Invalid arguments");
    return;
  }
  char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;
	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if(-1 == fd){
		fprintf(stderr, "Failed to open unexport for writing!\n");
    Nan::ThrowError("Failed to open unexport for writing!\n");
		return;
	}
  int pin = info[0]->NumberValue();
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
}

void GPIODirection(const Nan::FunctionCallbackInfo<v8::Value>& info){

  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }
  int pin = info[0]->NumberValue();
  int dir = info[1]->NumberValue();
	static const char s_directions_str[] = "in\0out";
  #define DIRECTION_MAX 35
	char path[DIRECTION_MAX];
	int fd;

	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction",pin);
	fd = open(path, O_WRONLY);
	if(-1 == fd){
		fprintf(stderr, "Failed to open gpio direction for writing!\n");
	}
	if(-1 == write(fd, &s_directions_str[IN == dir ? 0:3], IN == dir?2:3)){
		fprintf(stderr,"Failed to set Direction!\n");
	}
	close(fd);
	return;
}

void GPIORead(const Nan::FunctionCallbackInfo<v8::Value>& info){

  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }
  int pin = info[0]->NumberValue();
  #define VALUE_MAX 30
	char path[VALUE_MAX];
	char value_str[3];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value",pin);
	fd = open(path, O_RDONLY);
	if(-1 == fd){
		fprintf(stderr, "Failed to open gpio value for reading!\n");
    Nan::ThrowError("Failed to open gpio value for reading!\n");
		return;
	}
	if(-1 == read(fd, value_str, 3)){
		fprintf(stderr, "Falied to read value!\n");
    Nan::ThrowError("Failed to read value!\n");
		return;
	}
	close(fd);
	int value = atoi(value_str);
  info.GetReturnValue().Set(value);
}
void GPIOWrite(const Nan::FunctionCallbackInfo<v8::Value>& info){
  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }
  int pin = info[0]->NumberValue();
  int value = info[1]->NumberValue();
	static const char s_values_str[] = "01";
	char path[VALUE_MAX];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value",pin);
	fd = open(path,O_WRONLY);
	if(-1 == fd){
		fprintf(stderr, "Failed to open gpio value for writing!\n");
    Nan::ThrowError("Failed to open gpio value for writing!\n");
		return;
	}
	if(1 != write(fd, &s_values_str[LOW == value ? 0:1], 1)){
		fprintf(stderr, "Failed to write value!\n");
    Nan::ThrowError("Failed to write value!\n");
		return;
	}
	close(fd);
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("GPIOExport").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GPIOExport)->GetFunction());
  exports->Set(Nan::New("GPIOUnexport").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GPIOUnexport)->GetFunction());
  exports->Set(Nan::New("GPIODirection").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GPIODirection)->GetFunction());
  exports->Set(Nan::New("GPIORead").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GPIORead)->GetFunction());
  exports->Set(Nan::New("GPIOWrite").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(GPIOWrite)->GetFunction());
}

NODE_MODULE(gpio, Init)
