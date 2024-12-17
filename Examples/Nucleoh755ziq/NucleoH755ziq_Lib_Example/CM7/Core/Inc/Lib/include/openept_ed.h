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

#include "platform.h"
#include <stdint.h>

typedef enum
{
	OPEN_EPT_STATUS_OK,
	OPEN_EPT_STATUS_ERROR
}open_ept_status_t;

int OpenEPT_ED_Init();
int OpenEPT_ED_SetEP(uint8_t* epName, uint32_t epNameSize);
int OpenEPT_ED_SyncUp();
int OpenEPT_ED_SyncDown ();

#endif /* OPENEPT_ED_H_ */
