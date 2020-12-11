
/*
 * ADC.h
 *
 *  Created on: Nov 5, 2020
 *      Author: Yaman
 */

#ifndef ADC_H_
#define ADC_H_

#include "msp.h"
#include <stdint.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *      ADC14 Analog Input
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   GPIO      :  P6.0
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define ADC14_ANALOG_INPUT_BIT  BIT0
#define ADC14_ANALOG_INPUT      INCH_0

// Prototypes
void ConfigureADC(void);
void StartSampling(void);
void ADC14_IRQHandler(void);

#endif
