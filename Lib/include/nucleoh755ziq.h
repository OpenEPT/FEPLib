/*
 * nucleoh755ziq.h
 *
 *  Created on: Nov 3, 2024
 *      Author: Dimitrije Lilic
 */

#ifndef NUCLEOH755ZIQ_H_
#define NUCLEOH755ZIQ_H_

#include "openept_ed.h"
#include "stm32h7xx_hal.h"

int OpenEPT_ED_Platform_Init();
int OpenEPT_ED_Platform_Send(char character);
int OpenEPT_ED_Platform_SyncUp();
int OpenEPT_ED_Platform_SyncDown();

#endif /* NUCLEOH755ZIQ_H_ */
