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

#include <stdint.h>
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif


#define OPEN_EPT_STATUS_OK                  0
#define OPEN_EPT_STATUS_ERROR               1


/* Size of the buffer used within OpenEPT EP Library to receive messages from Acquistion device */
#define OPENEPT_CONF_RECEIVE_BUFFER_SIZE    OPENEPT_ED_CONF_RECEIVE_BUFFER_SIZE

/**
 * @brief Initializes the OpenEPT Embedded Device.
 *
 * This function initializes the OpenEPT EP on DUT by calling the platform-specific initialization 
 * function.
 *
 * @return OPEN_EPT_STATUS_OK on successful initialization,
 *         OPEN_EPT_STATUS_ERROR on failure.
 */
int OpenEPT_ED_Init();

/**
 * @brief Start EP link for communication with Acqusition Device.
 *
 * Initiates communication with the OpenEPT Acquisition device by sending a "START" command.
 * This function waits for a response from the acquisition device to confirm the connection.
 *
 * @return OPEN_EPT_STATUS_OK if communication is successful established,
 *         OPEN_EPT_STATUS_ERROR if there is no response from Acquistion device.
 */
int OpenEPT_ED_Start();

/**
 * @brief Stop EP link.
 *
 * Stop communication with the OpenEPT Acquisition device by sending a "STOP" command.
 * This function waits for a response from the acquisition device to confirm the Acqusition
 * device successsfully receive this command.
 *
 * @return OPEN_EPT_STATUS_OK if communication is successful established,
 *         OPEN_EPT_STATUS_ERROR if there is no response from Acquistion device.
 */
int OpenEPT_ED_Stop();

/**
 * @brief Sets up a communication energy point.
 *
 * This function configures a communication energy point by sending its name character by
 * character to the platform. It adds a carriage return ('\r') after the energy point
 * name and performs synchronization before sending the data (SYNC  is toggled before 
 * energy point name is transmited over serial interface)
 *
 * @param epName Pointer to the name of the energy point.
 * @param epNameSize Size of the energy point name in bytes.
 * @return OPEN_EPT_STATUS_OK on successful setup,
 *         OPEN_EPT_STATUS_ERROR on failure.
 */
int OpenEPT_ED_SetEPFast(uint8_t* epName, uint32_t epNameSize);

/**
 * @brief Send info message to OpenEPT device.
 *
 * Send info message to OpenEPT Device over serial interface
 *
 * @param message Information message.
 * @return OPEN_EPT_STATUS_OK on successful setup,
 *         OPEN_EPT_STATUS_ERROR on failure.
 */
int OpenEPT_ED_SendInfo(const char* message);

/**
 * @brief Sets up a communication energy point.
 *
 * This function will send ENergy Request without name. It is expected that energy request 
 * name will be sent later
 * 
 * @return OPEN_EPT_STATUS_OK on successful setup,
 *         OPEN_EPT_STATUS_ERROR on failure.
 */
int OpenEPT_ED_Record();

/**
 * @brief 
 *
 * This function will send EP Name only. 
 *
 * @param epName Pointer to the name of the energy point.
 * @param epNameSize Size of the energy point name in bytes.
 * @return OPEN_EPT_STATUS_OK on successful setup,
 *         OPEN_EPT_STATUS_ERROR on failure.
 */
int OpenEPT_ED_SendEPName(uint8_t* epName, uint32_t epNameSize);

#ifdef __cplusplus
}
#endif
 
 #endif /* OPENEPT_ED_H_ */