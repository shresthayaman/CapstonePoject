
/************************************************************************************************************************************
 * Delong's Fan Club
 *
 * Date: November 2020
 * Author(s): Yaman Shrestha, Sunny Hwang, Jack Galletta
 *
 ************************************************************************************************************************************/

#include "msp.h"
#include "ADC.h"
#include "ClockTimer.h"
#include "DAC.h"

void main(void)
{
    // Stop the watchdog timer
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
    ConfigureClock();
    InitializeSPI();
    ConfigureTimer();

    VCORE1();
    ConfigureADC();
    InitializeDACPins();


	while(1){
	    StartSampling();
//	    __sleep();
	    __no_operation();                   // For debugger

	}

	return 0;
}
