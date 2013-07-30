//  rfBeeGPIO.cpp GPIO functions for rfBee
//  see www.seeedstudio.com for details and ordering rfBee hardware.

//  Copyright (c) 2013 Chris Stephens <rfbee (at) chuljin.net>
//  Author: Chris Stephens, based on the original Rfbee v1.1 firmware by Hans Klunder
//  Version: July 29, 2013
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
	setP0Mode();
	setP1Mode();
	setP2Mode();
	setP3Mode();
	setP0Duty();
	setD2Duty();
	setD3Duty();
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
int setP0Mode() { return setMode(PIN_P0,Config.get(CONFIG_P0_MODE)); }
int setP1Mode() { return setMode(PIN_P1,Config.get(CONFIG_P1_MODE)); }
int setP2Mode() { return setMode(PIN_P2,Config.get(CONFIG_P2_MODE)); }
int setP3Mode() { return setMode(PIN_P3,Config.get(CONFIG_P3_MODE)); }
int setMode(byte pin, byte mode){
	switch(mode){
		case SPECIAL:
			switch(pin){
				case PIN_D5:
				case PIN_P0:
				case PIN_P3:
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
		case ANALOG_INPUT:
			pinMode(pin,INPUT);
			break;
		case PWM_OUTPUT:
			pinMode(pin,OUTPUT);
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
	if(mode==PWM_OUTPUT){
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
int printP0Input() { return printInput(PIN_P0,Config.get(CONFIG_P0_MODE)); }
int printP1Input() { return printInput(PIN_P1,Config.get(CONFIG_P1_MODE)); }
int printP2Input() { return printInput(PIN_P2,Config.get(CONFIG_P2_MODE)); }
int printP3Input() { return printInput(PIN_P3,Config.get(CONFIG_P3_MODE)); }
int printInput(byte pin, byte mode){
	Serial.println(getInput(pin,mode));
	return OK;
}
int printAllInputs(){
	Serial.println(getAllInputs());
	return OK;
}
int getInput(byte pin, byte mode){
	int retVal=0;
	switch(mode){
		case DIGITAL_INPUT:
			retVal=digitalRead(pin);
			break;
		case DIGITAL_OUTPUT_HIGH:
			retVal=1;
			break;
		case ANALOG_INPUT:
			if(pin>=14)
				retVal=analogRead(pin-14);
			break;
		case PWM_OUTPUT:
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
	return retVal;
}
