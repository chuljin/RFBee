//  Config.h Simple config library for RFbee

//  Copyright (c) 2013 Chris Stephens <rfbee (at) chuljin.net>
//  Author: Chris Stephens, based on the original Rfbee v1.1 firmware by Hans Klunder
//  Version: July 29, 2013
//
//  Copyright (c) 2010 Hans Klunder <hans.klunder (at) bigfoot.com>
//  Author: Hans Klunder, based on the original Rfbee v1.0 firmware by Seeedstudio
//  Version: Aug 27, 2010
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



#ifndef Config_h
#define Config_h 1

#include "Arduino.h"

// config layout
#define CONFIG_RFBEE_MARKER       0  // Marker
#define CONFIG_HW_VERSION         1  // Hardware version
#define CONFIG_FW_VERSION         2  // Firmware version
#define CONFIG_DEST_ADDR          3  // Receiver address
#define CONFIG_MY_ADDR            4  // Sender address
#define CONFIG_ADDR_CHECK         5  // Address checking
#define CONFIG_TX_THRESHOLD       6  // Transmit threshold
#define CONFIG_BDINDEX            7  // Index to baudrate
#define CONFIG_PAINDEX            8  // Index to PowerAmplifier
#define CONFIG_CONFIG_ID          9 // Selected CCx configuration
#define CONFIG_OUTPUT_FORMAT     10 // output format to use
#define CONFIG_RFBEE_MODE        11 // rfBee operating mode (e.g. transmit/receive/idle)
#define CONFIG_D0_MODE           12 // GPIO mode for D0 (XBee Pin 20)
#define CONFIG_D1_MODE           13 // GPIO mode for D1 (XBee Pin 19)
#define CONFIG_D2_MODE           14 // GPIO mode for D2 (XBee Pin 18)
#define CONFIG_D3_MODE           15 // GPIO mode for D3 (XBee Pin 17)
#define CONFIG_D4_MODE           16 // GPIO mode for D4 (XBee Pin 11)
#define CONFIG_D5_MODE           17 // GPIO mode for D5 (XBee Pin 15/Assoc)
#define CONFIG_D6_MODE           18 // GPIO mode for D6 (XBee Pin 16)
#define CONFIG_D7_MODE           19 // GPIO mode for D7 (XBee Pin 12)
#define CONFIG_D8_MODE           20 // GPIO mode for D8 (XBee Pin 4)
#define CONFIG_P0_MODE           21 // GPIO mode for P0 (XBee Pin 6/RSSI)
#define CONFIG_P1_MODE           22 // GPIO mode for P1 (XBee Pin 7)
#define CONFIG_P2_MODE           23 // GPIO mode for P2 (XBee Pin 8)
#define CONFIG_P3_MODE           24 // GPIO mode for P3 (XBee Pin 13/On/Sleep)
#define CONFIG_P0_DUTY           25 // PWM duty for P0 (XBee Pin 6/RSSI/PB1/9)
#define CONFIG_D2_DUTY           26 // PWM duty for D2 (XBee Pin 18/PD6/6)
#define CONFIG_D3_DUTY           27 // PWM duty for D3 (XBee Pin 17/PD5/5)
#define CONFIG_PERIODIC_INTERVAL 28 // Interval for periodic transmission of input values
#define CONFIG_PERIODIC_FLAGS    29 // Whether to send input values locally (bit 0), via the radio (bit 1), or both
#define CONFIG_PERIODIC_DEST     30 // What address (or 0 for broadcast) to send input values to if _FLAGS bit 1 set
// marker
#define CONFIG_RFBEE_MARKER_VALUE 0xAA

class CONFIG
{
  public:
    CONFIG(void);
    void reset(void);
    byte get(byte);
    void set(byte,byte);
    int initialized();
};

extern CONFIG Config;

#endif
