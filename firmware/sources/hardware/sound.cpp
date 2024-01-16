// ***************************************************************************************
// ***************************************************************************************
//
//      Name :      sound.cpp
//      Authors :   Paul Robson (paul@robsons.org.uk)
//					Harry Fairhead
//      Date :      21st November 2023
//      Reviewed :  No
//      Purpose :   Audio support for Neo6502
//
// ***************************************************************************************
// ***************************************************************************************

#include "common.h"
#include "stdlib.h"
#include "hardware/pwm.h"
#include "dvi.h"
#include "system/dvi_video.h"

#define SOUND_PIN 	(20) 					// Beeper pin.

static uint sliceNumber,channel;

// ***************************************************************************************
//
//						Set up code, borrowed from Harry Fairhead
//
// ***************************************************************************************

static int32_t SNDSetPWMFrequencyDuty(uint slice_num,uint chan,uint32_t f, int d)
{
	uint32_t clock = DVI_TIMING.bit_clk_khz * 1024;
	uint32_t divider16 = clock / f / 4096 + (clock % (f * 4096) != 0);
	if (divider16 / 16 == 0) divider16 = 16;
	uint32_t wrap = clock * 16 / divider16 / f - 1;
	pwm_set_clkdiv_int_frac(slice_num, divider16/16,divider16 & 0xF);
	pwm_set_wrap(slice_num, wrap);
	pwm_set_chan_level(slice_num, chan, wrap * d / 100);
	return wrap;
}



// ***************************************************************************************
//
//				Initialise sound channel, return # of supported channels
//
// ***************************************************************************************

void SNDInitialise(void) {
	gpio_set_function(SOUND_PIN, GPIO_FUNC_PWM);
	sliceNumber = pwm_gpio_to_slice_num(SOUND_PIN);
	channel = pwm_gpio_to_channel(SOUND_PIN);
	SNDSetFrequency(0,0,false);
}

// ***************************************************************************************
//
//									Play note on channel
//
// ***************************************************************************************

void SNDSetFrequency(uint8_t channel,uint16_t frequency,bool isNoise) {
	if (channel < SOUND_CHANNELS) {
		SNDSetPWMFrequencyDuty(sliceNumber,channel, frequency, 50);
		pwm_set_enabled(sliceNumber,(frequency != 0));
	}
}

// ***************************************************************************************
//
//		Date 		Revision
//		==== 		========
//		16-01-24	Moved tick callback stuff to tick source for generalised usage
//
// ***************************************************************************************
