/**
 * SSD1306xLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x64 displays
 *
 * @created: 2014-08-08
 * @author: Neven Boyanov
 *
 * This is part of the Tinusaur/SSD1306xLED project.
 *
 * Copyright (c) 2016 Neven Boyanov, Tinusaur Team. All Rights Reserved.
 * Distributed as open source software under MIT License, see LICENSE.txt file.
 * Please, as a favor, retain the link http://tinusaur.org to The Tinusaur Project.
 *
 * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled
 *
 */

// ============================================================================

// #define F_CPU 1000000UL
// NOTE: The F_CPU (CPU frequency) should not be defined in the source code.
//       It should be defined in either (1) Makefile; or (2) in the IDE. 

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                ATtiny
//               25/45/85
//              +----------+   (-)-------
//      (RST)---+ PB5  Vcc +---(+)-------
// --[OWOWOD]---+ PB3  PB2 +---[TWI/SCL]-
//           ---+ PB4  PB1 +---
// -------(-)---+ GND  PB0 +---[TWI/SDA]-
//              +----------+
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// -----(+)--------------->	// Vcc,	Pin 1 on SSD1306 Board
// -----(-)--------------->	// GND,	Pin 2 on SSD1306 Board
#define SSD1306_SCL		PB2	// SCL,	Pin 3 on SSD1306 Board
#define SSD1306_SDA		PB0	// SDA,	Pin 4 on SSD1306 Board

#define SSD1306_SA		0x78	// Slave address

// ----------------------------------------------------------------------------

#include "cpufreq.h"

#include "ssd1306xled.h"
#include "ssd1306xled8x16.h"

// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------


int main(void) {
	// ---- Initialization ----
	
	// ---- CPU Frequency Setup ----
#if F_CPU == 1000000UL
#pragma message "F_CPU=1MHZ"
	CLKPR_SET(CLKPR_1MHZ);
#elif F_CPU == 8000000UL
#pragma message "F_CPU=8MHZ"
	CLKPR_SET(CLKPR_8MHZ);
#else
#pragma message "F_CPU=????"
#error "CPU frequency should be either 1 MHz or 8 MHz"
#endif

	// Small delay is necessary if ssd1306_init is the first operation in the application.
	_delay_ms(40);
	ssd1306_init();

	// ---- Main Loop ----
  ssd1306_clear(); _delay_ms(200);
  uint8_t count = 0;

	ssd1306_setpos(44, 0);  
  ssd1306_string("hello");

	for (;;) {
    //
    // // ssd1306_drawBox();
    //
    // ssd1306_draw_bmp2(0, 0, 24, 6, bpm);
    //
    // count = (int)((double)rand() / ((double)RAND_MAX + 1) * 9);
    // drawNumber(0, count);
    //
    // _delay_ms(1000);
    // ssd1306_send_command(0xA7);
    // _delay_ms(500);
    // ssd1306_send_command(0xA6);
    // _delay_ms(500);
    // ssd1306_send_command(0xA7);
    // _delay_ms(500);
    // ssd1306_send_command(0xA6);
    //
		_delay_ms(1000);
	}
	
	return 0;
}

// ============================================================================
