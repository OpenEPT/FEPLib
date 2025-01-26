/**
 * @file platform.h
 * @brief Platform file to include appropriate header files.
 *
 * This file is used for user specific platforms code that will be
 * used in openept lib function calls.
 *
 * @date November 8, 2024
 * @author Dimitrije Lilic
 */

#ifndef PLATFORM_PLATFORM_H_
#define PLATFORM_PLATFORM_H_

/* Uncomment or define the target platform before compilation */

#define PLATFORM_NUCLEO_H755ZIQ
//#define PLATFORM_NUCLEO_F4
//#define PLATFORM_ESP32
//#define PLATFORM_ARDUINO

// Include the appropriate header file based on platform
#if defined(PLATFORM_NUCLEO_H755ZIQ)
    #include "nucleoh755ziq.h"
#elif defined(PLATFORM_ESP32)
    #include "TODO"
#elif defined(PLATFORM_ARDUINO)
    #include "TODO.c"
#else
    #error "No platform selected or unsupported platform. Please define a platform in platform.h."
#endif

#endif /* PLATFORM_PLATFORM_H_ */
