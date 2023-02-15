#include<stdio.h>
#include<iostream>
#include<vector>
#include "TrameInterpret.h"
#define MAX_PAYLOAD_SIZE 64
typedef struct tagMessage {
	uint8_t id;
	uint8_t rw;
	uint8_t isQueued;
	uint8_t paramsLen;
	uint8_t params[MAX_PAYLOAD_SIZE - 2];
}Message;


int main() {
	Message a = { 87, 0, 0, 30, {0x11,0x22,0x33,0x44} };

	TrameInterpret trame(a);

	return 0;
}
