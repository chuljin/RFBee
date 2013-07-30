//  rfBeeSerial.h serial interface to rfBee
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


#ifndef RFBEESERIAL_H
#define RFBEESERIAL_H 1

#include "debug.h"
#include "globals.h"
#include "Config.h"
#include "CCx.h"
#include "rfBeeCore.h"
#include "rfBeeGPIO.h"
#include <avr/pgmspace.h>

#define BUFFLEN CCx_PACKT_LEN
#define SERIALCMDMODE 1
#define SERIALDATAMODE 0
#define SERIALCMDTERMINATOR 13  // use <CR> to terminate commands

void readSerialCmd();
void readSerialData();

int setMyAddress();
int setAddressCheck();
int setPowerAmplifier();
int setCCxConfig();
int changeUartBaudRate();
int setSerialDataMode();
int setRFBeeMode();
int showFirmwareVersion();
int showHardwareVersion();
int resetConfig();
int setSleepMode();



byte serialData[BUFFLEN+1]; // 1 extra so we can easily add a /0 when doing a debug print ;-)
byte serialMode;
volatile int sleepCounter;


// RFbee AT commands

// Need to define the labels outside the struct :-(
static char DA_label[] PROGMEM="DA";
static char MA_label[] PROGMEM="MA";
static char AC_label[] PROGMEM="AC";
static char PA_label[] PROGMEM="PA";
static char TH_label[] PROGMEM="TH";
static char BD_label[] PROGMEM="BD";
static char MD_label[] PROGMEM="MD";
static char FV_label[] PROGMEM="FV";
static char HV_label[] PROGMEM="HV";
static char RS_label[] PROGMEM="RS";
static char CF_label[] PROGMEM="CF";
static char OF_label[] PROGMEM="OF";
static char O0_label[] PROGMEM="O0";
static char SL_label[] PROGMEM="SL";
static char D0_label[] PROGMEM="D0";
static char D1_label[] PROGMEM="D1";
static char D2_label[] PROGMEM="D2";
static char D3_label[] PROGMEM="D3";
static char D4_label[] PROGMEM="D4";
static char D5_label[] PROGMEM="D5";
static char D6_label[] PROGMEM="D6";
static char D7_label[] PROGMEM="D7";
static char D8_label[] PROGMEM="D8";
static char P0_label[] PROGMEM="P0";
static char P1_label[] PROGMEM="P1";
static char P2_label[] PROGMEM="P2";
static char P3_label[] PROGMEM="P3";
static char M0_label[] PROGMEM="M0";
static char M2_label[] PROGMEM="M2";
static char M3_label[] PROGMEM="M3";
static char I0_label[] PROGMEM="I0";
static char I1_label[] PROGMEM="I1";
static char I2_label[] PROGMEM="I2";
static char I3_label[] PROGMEM="I3";
static char I4_label[] PROGMEM="I4";
static char I5_label[] PROGMEM="I5";
static char I6_label[] PROGMEM="I6";
static char I7_label[] PROGMEM="I7";
static char I8_label[] PROGMEM="I8";
static char IA_label[] PROGMEM="IA";
static char IB_label[] PROGMEM="IB";
static char IC_label[] PROGMEM="IC";
static char ID_label[] PROGMEM="ID";
static char IE_label[] PROGMEM="IE";

// Supported commands, Commands and parameters in ASCII
// Example: ATDA14 means: change the RF module Destination Address to 14

typedef int (*AT_Command_Function_t)();

typedef struct
{
  const char *name;
  const byte configItem;   // the ID used in the EEPROM
  const byte paramDigits;  // how many digits for the parameter
  const byte maxValue;     // maximum value of the parameter
  const byte postProcess;  // do we need to call the function to perform extra actions on change
  AT_Command_Function_t function; // the function which does the real work on change
}  AT_Command_t;


static AT_Command_t atCommands[] PROGMEM =
{
// Addressing:
  { DA_label, CONFIG_DEST_ADDR, 3 , 255, false, 0 },             // Destination address   (0~255)
  { MA_label, CONFIG_MY_ADDR, 3 , 255, true, setMyAddress },     // My address            (0~255)
  { AC_label, CONFIG_ADDR_CHECK, 1 , 2, true, setAddressCheck }, // address check option  (0: no, 1: address check , 2: address check and 0 broadcast )
// RF
  { PA_label, CONFIG_PAINDEX, 1 , 7, true, setPowerAmplifier },  // Power amplifier           (0: -30 , 1: -20 , 2: -15 , 3: -10 , 4: 0 , 5: 5 , 6: 7 , 7: 10 )
  { CF_label, CONFIG_CONFIG_ID, 1 , 5, true, setCCxConfig },     // select CCx configuration  (0: 915 Mhz - 76.8k, 1: 915 Mhz - 4.8k sensitivity, 2: 915 Mhz - 4.8k low current, 3: 868 Mhz - 76.8k, 4: 868 Mhz - 4.8k sensitivity, 5: 868 Mhz - 4.8k low current )
// Serial
  { BD_label, CONFIG_BDINDEX, 1 , 3, true, changeUartBaudRate },  // Uart baudrate                    (0: 9600 , 1:19200, 2:38400 ,3:115200)
  { TH_label, CONFIG_TX_THRESHOLD, 2 , 32, false, 0 },            // TH- threshold of transmitting    (0~32)
  { OF_label, CONFIG_OUTPUT_FORMAT, 1 , 3 , false, 0 },           // Output Format                    (0: payload only, 1: source, dest, payload ,  2: payload len, source, dest, payload, rssi, lqi, 3: same as 2, but all except for payload as decimal and separated by comma's )
// Mode
  { MD_label, CONFIG_RFBEE_MODE, 1 , 3 , true, setRFBeeMode},    // CCx Working mode                 (0:transceive , 1:transmit , 2:receive, 3:lowpower)
  { O0_label, 0, 0 , 0 , true, setSerialDataMode },              // thats o+ zero, go back to online mode
  { SL_label, 0, 0 , 0 , true, setSleepMode },                   // put the rfBee to sleep
// Diagnostics:
  { FV_label, 0, 0 , 0 , true, showFirmwareVersion },           // firmware version
  { HV_label, 0, 0 , 0 , true, showHardwareVersion },           // hardware version
// Miscelaneous
  { RS_label, 0, 0 , 0 , true, resetConfig },                    // restore default settings
// GPIO Config
  { D0_label, CONFIG_D0_MODE, 1, 5, true, setD0Mode },
  { D1_label, CONFIG_D1_MODE, 1, 5, true, setD1Mode },
  { D2_label, CONFIG_D2_MODE, 1, 6, true, setD2Mode },
  { D3_label, CONFIG_D3_MODE, 1, 6, true, setD3Mode },
  { D4_label, CONFIG_D4_MODE, 1, 5, true, setD4Mode },
  { D5_label, CONFIG_D5_MODE, 1, 5, true, setD5Mode },
  { D6_label, CONFIG_D6_MODE, 1, 5, true, setD6Mode },
  { D7_label, CONFIG_D7_MODE, 1, 5, true, setD7Mode },
  { D8_label, CONFIG_D8_MODE, 1, 4, true, setD8Mode },
  { P0_label, CONFIG_P0_MODE, 1, 6, true, setP0Mode },
  { P1_label, CONFIG_P1_MODE, 1, 4, true, setP1Mode },
  { P2_label, CONFIG_P2_MODE, 1, 4, true, setP2Mode },
  { P3_label, CONFIG_P3_MODE, 1, 5, true, setP3Mode },
// GPIO PWM Output
  { M0_label, CONFIG_P0_DUTY, 3, 255, true, setP0Duty },
  { M2_label, CONFIG_D2_DUTY, 3, 255, true, setD2Duty },
  { M3_label, CONFIG_D3_DUTY, 3, 255, true, setD3Duty },
// GPIO Input
  { I0_label, 0, 0, 0, true, printD0Input },
  { I1_label, 0, 0, 0, true, printD1Input },
  { I2_label, 0, 0, 0, true, printD2Input },
  { I3_label, 0, 0, 0, true, printD3Input },
  { I4_label, 0, 0, 0, true, printD4Input },
  { I5_label, 0, 0, 0, true, printD5Input },
  { I6_label, 0, 0, 0, true, printD6Input },
  { I7_label, 0, 0, 0, true, printD7Input },
  { I8_label, 0, 0, 0, true, printD8Input },
  { IA_label, 0, 0, 0, true, printP0Input },
  { IB_label, 0, 0, 0, true, printP1Input },
  { IC_label, 0, 0, 0, true, printP2Input },
  { ID_label, 0, 0, 0, true, printP3Input },
  { IE_label, 0, 0, 0, true, printAllInputs }
};

// error codes and labels
byte errNo;

static char error_0[] PROGMEM="no error";
static char error_1[] PROGMEM="received invalid RF data size";
static char error_2[] PROGMEM="received invalid RF data";
static char error_3[] PROGMEM="RX buffer overflow";
static char error_4[] PROGMEM="CRC check failed";

static char *error_codes[] PROGMEM={
  error_0,
  error_1,
  error_2,
  error_3,
};


long baudRateTable[] PROGMEM= {9600,19200,38400,115200};

// operating modes, used by ATMD

#define TRANSCEIVE_MODE 0
#define TRANSMIT_MODE 1
#define RECEIVE_MODE 2
#define LOWPOWER_MODE 3

#ifdef INTERRUPT_RECEIVE
volatile enum state

#endif

#endif
