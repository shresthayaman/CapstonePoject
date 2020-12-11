#include "ADC.h"

#define   Num_of_Results   8

volatile uint16_t A15results[Num_of_Results];
volatile uint16_t index = 0;

#define startSampling() TIMER_A0->CCR[0] =   750 // Corresponds to 8 kHz sampling rate
#define stopSampling() TIMER_A0->CCR[0] = 0;

void ConfigureADC(void)
{
    P6->DIR &= ~(BIT0);    //Set ADC pin as input

    // GPIO Setup
    P6->SEL1 |= BIT0;                       // Configure P6.0 for ADC
    P6->SEL0 |= BIT0;

    // Enable global interrupt
    __enable_irq();

    // Enable ADC interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);

    // Sampling time, Sample&Hold=16, ADC14 on, CONSEQ_2=Repeat-single-channel, Enable ADC14 multiple sample and conversion
    ADC14->CTL0 = ADC14_CTL0_SHT0__16 | ADC14_CTL0_SHP | ADC14_CTL0_ON | ADC14_CTL0_CONSEQ_2 | ADC14_CTL0_MSC;
    ADC14->CTL1 = ADC14_CTL1_RES__14BIT;         // Use sampling timer, 14-bit conversion results

    ADC14->MCTL[0] = ADC14_MCTLN_INCH_15;   // A15 ADC input select; Vref=AVCC
    ADC14->IER0 |= ADC14_IER0_IE0;          // Enable ADC conv complete interrupt

    SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;   // Wake up on exit from ISR

    // Ensures SLEEPONEXIT takes effect immediately
    __DSB();
}

void StartSampling(void)
{
    // Start conversion-software trigger
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;


}


// ADC14 interrupt service routine
void ADC14_IRQHandler(void)
{
    //(ADC14->IFGR0 ADC14MEM0 interrupt flag. This bit is set to 1 when ADC14MEM0 is loaded with
    //a conversion result. This bit is reset to 0 when the ADC14MEM0 register is read,
    //or when the corresponding bit in the ADC14CLRIFGR0 register is set to 1.

    //
    if (ADC14->IFGR0 & ADC14_IFGR0_IFG0)
    {
        A15results[index] = ADC14->MEM[0];   // Move A15 results, IFG is cleared

        index = (index + 1) & 0x7;          // Increment results index, modulo
        __no_operation();                   // Set Breakpoint1 here

    }

    //Add effects here based on waht you want
    AddDistortion(A15results, sizeof A15results / sizeof A15results[0])
}
