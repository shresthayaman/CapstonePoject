/*
 * ClockTimer.c
 *
 *  Created on: Nov 16, 2020
 *      Author: yamanshrestha
 */

#include <ClockTimer.h>


extern int y_scaled;
extern int y;

//https://e2e.ti.com/support/microcontrollers/msp430/f/166/t/614225?MSP432P401R-Sampling-Audio-and-Storing-with-DMA
void ConfigureClock(){

    //Set clock to 48 MHz
    CS->KEY  =   CS_KEY_VAL;             //Unlock CS registers
    CS->CTL0     =   CS_CTL0_DCOEN   |
                        CS_CTL0_DCORSEL_5;      //Choose 48 MHz MHz clock speed

    CS->CTL1     =   CS_CTL1_SELS_3  |
                        CS_CTL1_SELM_3  ;       //Use DCOCLK as source for MCLK, SMCLK + HSMCLK
    CS->KEY      =   0;                      //Re-lock CS registers
}

void ConfigureTimer(){
    TIMER_A0->CCTL[1]    =   TIMER_A_CCTLN_OUTMOD_7;

    TIMER_A0->CTL        =   TIMER_A_CTL_TASSEL_2    |   //Select SMCLK as source for timer
                                TIMER_A_CTL_ID_2        |   //Divide clock by 4 (this yields 12 MHz for the timer clock)
                                TIMER_A_CTL_MC_1        |   //Up mode
                                TIMER_A_CTL_CLR         ;   //Clear timer count

    TIMER_A0->CCR[1] = 100;
}


void VCORE1()
{
    while(PCM->CTL1 & PCM_CTL1_PMR_BUSY);
    PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR__AM_LDO_VCORE1;
    while(PCM->CTL1 & PCM_CTL1_PMR_BUSY);
}

// Timer0 CCR0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)
{
    // The scaling factor is used to adjust any discrepancies between the number of bits produced
    // by the ADC and the number of bits supported by the DAC.
    y_scaled = (y << SCALING_FACTOR);

    ENABLE_DAC_CS;
    SPISendByte((unsigned char) (WRITE_TO_AND_UPDATE_N | DAC_A));
    SPISendByte((unsigned char) (y_scaled >> 8)); // Most Significant Byte
    SPISendByte((unsigned char) (y_scaled)); // Least Significant Byte
    DISABLE_DAC_CS;
}
