/*! \file low power functions

  \brief Allow user to turn off the LEDs when not in use to save battery. Time should be maintained
  and displayed correctly when back in time mode (mode 0).
*/

#include <msp430.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "led.h"
#include "button.h"

static unsigned enabled = 1;
static unsigned timeout;
extern unsigned watch_mode;


// called every 16ms by the RTC interrupt
void lowpwr_draw()
{
	if (button_short)
	{
		timeout = 0;

		if (enabled)
		{
			// toggle mode
			enabled = 0;
		} else {
			// toggle mode
			enabled = 1;
		}
	}

	if (button_long)
	{
		// we have just entered this mode
		enabled = 0;
		timeout = 0;
	}

	if (!enabled)
	{
	    // low power mode selected but not enabled so display the mode (led hr=4) until user short presses button or timeout
		timeout++;
        led_on(64);
        delay(8);
        led_off();
	}

	if (timeout > 15 * 60)
	    // if we are displaying the mode (led hr=4) then we should timeout and go back to displaying the time.
		watch_mode = 0;

 led_off();
}
