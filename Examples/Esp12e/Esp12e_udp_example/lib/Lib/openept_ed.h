/**
 * @file openept_ed.h
 * @brief Implementation of the OpenEPT Embedded Device (ED) library.
 *
 * This library provides functions for initializing and setting up communication
 * for embedded devices, with platform-specific function calls for
 * initialization, synchronization, and data transmission.
 *
 * @date November 3, 2024
 * @author Dimitrije Lilic
 */

#ifndef OPENEPT_ED_H_
#define OPENEPT_ED_H_

#include "./Platform/platform.h"
#include <stdint.h>

int OpenEPT_ED_Init();
int OpenEPT_ED_SetEPSlow(uint8_t* epName, uint32_t epNameSize);
int OpenEPT_ED_SetEPFast(uint8_t* epName, uint32_t epNameSize);
int OpenEPT_ED_SyncUp();
int OpenEPT_ED_SyncDown ();
int OpenEPT_ED_SyncToogle();

#endif /* OPENEPT_ED_H_ */
