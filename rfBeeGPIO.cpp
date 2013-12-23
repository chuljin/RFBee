//  rfBeeGPIO.cpp GPIO functions for rfBee
//  see www.seeedstudio.com for details and ordering rfBee hardware.

//  Copyright (c) 2013 Chris Stephens <rfbee (at) chuljin.net>
//  Author: Chris Stephens, based on the original Rfbee v1.1 firmware by Hans Klunder
//  Version: November 27, 2013
//
//  Copyright (c) 2010 Hans Klunder <hans.klunder (at) bigfoot.com>
//  Author: Hans Klunder, based on the original Rfbee v1.0 firmware by Seeedstudio
//  Version: August 18, 2010
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#include "rfBeeGPIO.h"
void setGPIO(){
	setD0Mode();
	setD1Mode();
	setD2Mode();
	setD3Mode();
	setD4Mode();
	setD5Mode();
	setD6Mode();
	setD7Mode();
	setD8Mode();
	setD9Mode();
	setP0Mode();
	setP1Mode();
	setP2Mode();
	setP3Mode();
	setP0Duty();
	setD2Duty();
	setD3Duty();
	setPeriodicInterval();
}

int setD0Mode() { return setMode(PIN_D0,Config.get(CONFIG_D0_MODE)); }
int setD1Mode() { return setMode(PIN_D1,Config.get(CONFIG_D1_MODE)); }
int setD2Mode() { return setMode(PIN_D2,Config.get(CONFIG_D2_MODE)); }
int setD3Mode() { return setMode(PIN_D3,Config.get(CONFIG_D3_MODE)); }
int setD4Mode() { return setMode(PIN_D4,Config.get(CONFIG_D4_MODE)); }
int setD5Mode() { return setMode(PIN_D5,Config.get(CONFIG_D5_MODE)); }
int setD6Mode() { return setMode(PIN_D6,Config.get(CONFIG_D6_MODE)); }
int setD7Mode() { return setMode(PIN_D7,Config.get(CONFIG_D7_MODE)); }
int setD8Mode() { return setMode(PIN_D8,Config.get(CONFIG_D8_MODE)); }
int setD9Mode() { return setMode(PIN_D9,Config.get(CONFIG_D9_MODE)); }
int setP0Mode() { return setMode(PIN_P0,Config.get(CONFIG_P0_MODE)); }
int setP1Mode() { return setMode(PIN_P1,Config.get(CONFIG_P1_MODE)); }
int setP2Mode() { return setMode(PIN_P2,Config.get(CONFIG_P2_MODE)); }
int setP3Mode() { return setMode(PIN_P3,Config.get(CONFIG_P3_MODE)); }
int setMode(byte pin, byte mode){
	if(pin==-1)
		return ERR;
	switch(mode){
		case SPECIAL:
			switch(pin){
				case PIN_D5:
				case PIN_P0:
				case PIN_P3:
					pinMode(pin,OUTPUT);
					break;
				default:
					pinMode(pin,INPUT);
					break;
			}
		case DIGITAL_INPUT:
			pinMode(pin,INPUT);
			break;
		case DIGITAL_OUTPUT_LOW:
			pinMode(pin,OUTPUT);
			digitalWrite(pin,LOW);
			break;
		case DIGITAL_OUTPUT_HIGH:
			pinMode(pin,OUTPUT);
			digitalWrite(pin,HIGH);
			break;
		case ANALOG_INPUT_OR_PWM_OUTPUT:
			switch(pin){
				case PIN_P0:
				case PIN_D2:
				case PIN_D3:
					pinMode(pin,OUTPUT);
					break;
				default:
					pinMode(pin,INPUT);
					break;
			}
			break;
		default: //e.g. DISABLED
			pinMode(pin,INPUT);
			break;
	}
	return OK;
}

int setP0Duty() { return setDuty(PIN_P0,Config.get(CONFIG_P0_MODE),Config.get(CONFIG_P0_DUTY)); }
int setD2Duty() { return setDuty(PIN_D2,Config.get(CONFIG_D2_MODE),Config.get(CONFIG_D2_DUTY)); }
int setD3Duty() { return setDuty(PIN_D3,Config.get(CONFIG_D3_MODE),Config.get(CONFIG_D3_DUTY)); }
int setDuty(byte pin, byte mode, byte duty){
	if(mode==ANALOG_INPUT_OR_PWM_OUTPUT){
		analogWrite(pin,duty);
		return OK;
	}
	return ERR;
}

int printD0Input() { return printInput(PIN_D0,Config.get(CONFIG_D0_MODE)); }
int printD1Input() { return printInput(PIN_D1,Config.get(CONFIG_D1_MODE)); }
int printD2Input() { return printInput(PIN_D2,Config.get(CONFIG_D2_MODE)); }
int printD3Input() { return printInput(PIN_D3,Config.get(CONFIG_D3_MODE)); }
int printD4Input() { return printInput(PIN_D4,Config.get(CONFIG_D4_MODE)); }
int printD5Input() { return printInput(PIN_D5,Config.get(CONFIG_D5_MODE)); }
int printD6Input() { return printInput(PIN_D6,Config.get(CONFIG_D6_MODE)); }
int printD7Input() { return printInput(PIN_D7,Config.get(CONFIG_D7_MODE)); }
int printD8Input() { return printInput(PIN_D8,Config.get(CONFIG_D8_MODE)); }
int printD9Input() { return printInput(PIN_D9,Config.get(CONFIG_D9_MODE)); }
int printP0Input() { return printInput(PIN_P0,Config.get(CONFIG_P0_MODE)); }
int printP1Input() { return printInput(PIN_P1,Config.get(CONFIG_P1_MODE)); }
int printP2Input() { return printInput(PIN_P2,Config.get(CONFIG_P2_MODE)); }
int printP3Input() { return printInput(PIN_P3,Config.get(CONFIG_P3_MODE)); }
int printInput(byte pin, byte mode){
	int input=getInput(pin,mode);
	char msb=input>>8;
	char lsb=input&0xff;
	Serial.print(msb);
	Serial.println(lsb);
	return OK;
}
int getInput(byte pin, byte mode){
	int retVal=0;
	if(pin==-1)
		return 0;
	switch(mode){
		case DIGITAL_INPUT:
			retVal=digitalRead(pin);
			break;
		case DIGITAL_OUTPUT_HIGH:
			retVal=1;
			break;
		case ANALOG_INPUT_OR_PWM_OUTPUT:
			if(pin>=14)
				retVal=analogRead(pin-14);
			else{
				switch(pin){
					case PIN_P0:
						retVal=Config.get(CONFIG_P0_DUTY);
						break;
					case PIN_D2:
						retVal=Config.get(CONFIG_D2_DUTY);
						break;
					case PIN_D3:
						retVal=Config.get(CONFIG_D3_DUTY);
						break;
				}
			}
			break;
	}
	return retVal;
}
int printAllInputs(){
	int buffer[14];
	getAllInputs(buffer);
	for(int pin=0;pin<=12;pin++){
		Serial.print(buffer[pin],DEC);
		Serial.print(",");
	}
	Serial.println(buffer[13]);
	return OK;
}
void getAllInputs(int* buffer){
	buffer[0]=getInput(PIN_D0,Config.get(CONFIG_D0_MODE));
	buffer[1]=getInput(PIN_D1,Config.get(CONFIG_D1_MODE));
	buffer[2]=getInput(PIN_D2,Config.get(CONFIG_D2_MODE));
	buffer[3]=getInput(PIN_D3,Config.get(CONFIG_D3_MODE));
	buffer[4]=getInput(PIN_D4,Config.get(CONFIG_D4_MODE));
	buffer[5]=getInput(PIN_D5,Config.get(CONFIG_D5_MODE));
	buffer[6]=getInput(PIN_D6,Config.get(CONFIG_D6_MODE));
	buffer[7]=getInput(PIN_D7,Config.get(CONFIG_D7_MODE));
	buffer[8]=getInput(PIN_D8,Config.get(CONFIG_D8_MODE));
	buffer[9]=getInput(PIN_D9,Config.get(CONFIG_D9_MODE));
	buffer[10]=getInput(PIN_P0,Config.get(CONFIG_P0_MODE));
	buffer[11]=getInput(PIN_P1,Config.get(CONFIG_P1_MODE));
	buffer[12]=getInput(PIN_P2,Config.get(CONFIG_P2_MODE));
	buffer[13]=getInput(PIN_P3,Config.get(CONFIG_P3_MODE));
}

void setRSSIOutput(byte rssi){
	if(Config.get(CONFIG_P0_MODE)==RSSI_PWM)
		analogWrite(PIN_P0,rssi+128);
}

unsigned long nextInputTransmission;
int setPeriodicInterval(){
	nextInputTransmission=millis()+(unsigned long)(Config.get(CONFIG_PERIODIC_INTERVAL)*1000);
	return OK;
}
bool checkPeriodicInterval(byte* buffer,byte serialMode){
	bool retVal=false;
	if(Config.get(CONFIG_PERIODIC_INTERVAL)>0){
		if(millis()>=nextInputTransmission){
			int ibuffer[14];
			getAllInputs(ibuffer);
			for (int i=0;i<=13;i++){
				buffer[i*2]=ibuffer[i]>>8;
				buffer[i*2+1]=ibuffer[i]&0xff;
			}
			byte flags=Config.get(CONFIG_PERIODIC_FLAGS);
			if(flags&1)
				if(serialMode==0){
					for(int i=0;i<=27;i++){
						Serial.write(buffer[i]);
					}
					Serial.println();
				}
			if(flags&2){
				retVal=true;
			}
			setPeriodicInterval();
		}
	}
	return retVal;
}
