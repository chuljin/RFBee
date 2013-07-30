//  rfBeeGPIO.h GPIO functions for rfBee
//  see www.seeedstudio.com for details and ordering rfBee hardware.

//  Copyright (c) 2013 Chris Stephens <rfbee (at) chuljin.net>
//  Author: Chris Stephens, based on the original Rfbee v1.1 firmware by Hans Klunder
//  Version: July 29, 2013
//
//  Copyright (c) 2010 Hans Klunder <hans.klunder (at) bigfoot.com>
//  Author: Hans Klunder, based on the original Rfbee v1.0 firmware by Seeedstudio
//  Version: July 16, 2010
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


#ifndef RFBEEGPIO_H
#define RFBEEGPIO_H 1

#include "debug.h"
#include "globals.h"
#include "Config.h"

#define DISABLED 0
#define SPECIAL 1
#define ASSOC 1
#define RSSI_PWM 1
#define STATUS 1
#define DIGITAL_INPUT 2
#define DIGITAL_OUTPUT_LOW 3
#define DIGITAL_OUTPUT_HIGH 4
#define ANALOG_INPUT 5
#define PWM_OUTPUT 6

#define PIN_D0 18
#define PIN_D1 19
#define PIN_D2 6
#define PIN_D3 5
#define PIN_D4 17
#define PIN_D5 14
#define PIN_D6 21
#define PIN_D7 16
#define PIN_D8 4
#define PIN_P0 9
#define PIN_P1 8
#define PIN_P2 7
#define PIN_P3 15

void setGPIO();

int setD0Mode();
int setD1Mode();
int setD2Mode();
int setD3Mode();
int setD4Mode();
int setD5Mode();
int setD6Mode();
int setD7Mode();
int setD8Mode();
int setP0Mode();
int setP1Mode();
int setP2Mode();
int setP3Mode();
int setMode(byte,byte);
int setP0Duty();
int setD2Duty();
int setD3Duty();
int setDuty(byte,byte,byte);
int printD0Input();
int printD1Input();
int printD2Input();
int printD3Input();
int printD4Input();
int printD5Input();
int printD6Input();
int printD7Input();
int printD8Input();
int printP0Input();
int printP1Input();
int printP2Input();
int printP3Input();
int printInput(byte,byte);
int getInput(byte,byte);
#endif
