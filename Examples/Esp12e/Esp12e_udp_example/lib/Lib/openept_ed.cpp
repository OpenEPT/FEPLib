/**
 * @file openept_ed.c
 * @brief Implementation of the OpenEPT Embedded Device (ED) library.
 *
 * This library provides functions for initializing and setting up communication
 * for embedded devices, with platform-specific function calls for
 * initialization, synchronization, and data transmission.
 *
 * @date November 3, 2024
 * @author Dimitrije Lilic
 */

#include "openept_ed.h"
#include "Platform/esp12e.h"
#include <string.h>
/**
 * @brief Initializes the OpenEPT Embedded Device.
 *
 * This function initializes the OpenEPT ED platform by calling the platform-specific
 * initialization function.
 *
 * @return OPEN_EPT_STATUS_OK on successful initialization,
 *         OPEN_EPT_STATUS_ERROR on failure.
 */
int OpenEPT_ED_Init()
{
    if(OpenEPT_ED_Platform_Init() != 0) return OPEN_EPT_STATUS_ERROR;
    return OPEN_EPT_STATUS_OK;
}

/**
 * @brief Sets up a communication energy point.
 *
 * This function configures a communication energy point by sending its name character by
 * character to the platform. It adds a carriage return ('\r') after the energy point
 * name and performs synchronization before and after sending the data.
 *
 * @param epName Pointer to the name of the energy point.
 * @param epNameSize Size of the energy point name in bytes.
 * @return OPEN_EPT_STATUS_OK on successful setup,
 *         OPEN_EPT_STATUS_ERROR on failure.
 */
int OpenEPT_ED_SetEPSlow(uint8_t* epName, uint32_t epNameSize)
{
    if(OpenEPT_ED_Platform_SyncUp() != 0) return OPEN_EPT_STATUS_ERROR;
    uint32_t cnt = 0;
    while(cnt < epNameSize)
    {
        if(OpenEPT_ED_Platform_Send((char)epName[cnt]) != 0) return OPEN_EPT_STATUS_ERROR;
        cnt++;
    }
    if(OpenEPT_ED_Platform_Send('\r') != 0) return OPEN_EPT_STATUS_ERROR;
    if(OpenEPT_ED_Platform_SyncDown() != 0) return OPEN_EPT_STATUS_ERROR;
    return OPEN_EPT_STATUS_OK;
}


int OpenEPT_ED_SetEPFast(uint8_t* epName, uint32_t epNameSize)
{
    if(OpenEPT_ED_Platform_SyncToogle() != 0) return OPEN_EPT_STATUS_ERROR;
    uint32_t cnt = 0;
    while(cnt < epNameSize)
    {
        if(OpenEPT_ED_Platform_Send((char)epName[cnt]) != 0) return OPEN_EPT_STATUS_ERROR;
        cnt++;
    }
    if(OpenEPT_ED_Platform_Send('\r') != 0) return OPEN_EPT_STATUS_ERROR;
    return OPEN_EPT_STATUS_OK;

}

/**
 * @brief Performs synchronization before starting communication.
 *
 * This function calls the platform-specific synchronization-up function to
 * prepare the device for data transmission.
 *
 * @return Platform-specific return code indicating synchronization success or failure.
 */
int OpenEPT_ED_SyncUp()
{
    return OpenEPT_ED_Platform_SyncUp();
}

/**
 * @brief Performs synchronization after completing communication.
 *
 * This function calls the platform-specific synchronization-down function to
 * finalize data transmission and ensure the device is in a stable state.
 *
 * @return Platform-specific return code indicating synchronization success or failure.
 */
int OpenEPT_ED_SyncDown()
{
    return OpenEPT_ED_Platform_SyncDown();
}


int OpenEPT_ED_SyncToogle()
{
    return OpenEPT_ED_Platform_SyncToogle();
}
