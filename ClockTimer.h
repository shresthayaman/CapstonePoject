/*
 * ClockTimer.h
 *
 *  Created on: Nov 16, 2020
 *      Author: yamanshrestha
 */

#ifndef CLOCKTIMER_H_
#define CLOCKTIMER_H_



#include "msp.h"
#include <stdint.h>

#define TACCR0_VALUE (3125-1)
#define SCALING_FACTOR 6

// Prototypes
void VCORE1(void);
void ConfigureClock(void);
void ConfigureTimer(void);


#endif /* CLOCKTIMER_H_ */
