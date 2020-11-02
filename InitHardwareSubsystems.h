/*
 * InitHardwareSubsystems.h
 *
 *  Created on: Sep 24, 2020
 *      Author: harry
 */

#ifndef INITHARDWARESUBSYSTEMS_H_
#define INITHARDWARESUBSYSTEMS_H_

Init_Timers{

}
InitADC{

}
InitAll{
	InitADC();
	Init_Timers();
//DO NOT ENABLE Interrupts
}

#endif /* INITHARDWARESUBSYSTEMS_H_ */
