#include "common.h"
#include "static_code.h"

void readStaticCode(byte rxSP1StaticCode[SECPLUS1_CODE_LEN], uint8_t &door, uint8_t &light){
	uint8_t obs = 0; // experiement to figure out what key 0x39 is for
	uint8_t key = 0;
	uint8_t val = 0;

	key = rxSP1StaticCode[0];
	val = rxSP1StaticCode[1];

	printStaticCode(rxSP1StaticCode);

	// door state
	if(key == 0x38){
		Serial.print("door state: ");
		if(val == 0x52){
			// door open
			door = 1;
		}else if(val == 0x55){
			// door closed
			door = 2;
		}else if(val == 0x01){
			// door opening
			door = 4;
		}else if(val == 0x04){
			// door closing
			door = 5;
		}else{
			// unknown
			door = 0;
		}
	}

	// light
	if(key == 0x3A){
		if(val == 0x5C){
			// light off
			light = 0;
		}else if(val == 0x58){
			// light on
			light = 1;
		}else{
			// light unknown
			light = 2;
		}
	}

	// obstruction?
	if(key == 0x39){
		obs = val;
	}

	Serial.print(" | STATUS:");
	Serial.print(" door:");
	Serial.print(door);
	Serial.print(" light:");
	Serial.print(light);
	Serial.print(" obs?:");
	Serial.print(obs);

	Serial.println("");
}

void getStaticCode(const char *command){
	if(strcmp(command,"door") == 0){
		txSP1StaticCode[0] = 0x30;
	}else if(strcmp(command,"light") == 0){
		txSP1StaticCode[0] = 0x32;
	}

	return;
}

void printStaticCode(byte code[SECPLUS1_CODE_LEN]){
	for(int i = 0; i < SECPLUS1_CODE_LEN; i++){
		if(code[i] <= 0x0f) Serial.print("0");
		Serial.print(code[i],HEX);
	}
}