/**
 * @file nucleoh755ziq.c
 * @brief Platform-specific implementation for NUCLEO-H755ZI-Q UART and GPIO initialization.
 *
 * This file provides the STM32-specific functions to initialize UART communication and
 * GPIOs for synchronization purposes in the OpenEPT Embedded Device (ED) library.
 *
 * @date November 3, 2024
 * @author Dimitrije Lilic
 */
#include <Arduino.h>
#include <stdint.h>
#include "../../feplib/feplib.h"
#include "string.h"



#define SYNC_PIN 5

static uint8_t  OPENEPT_SYNC_PIN_VALUE;


int OpenEPT_ED_Platform_Init()
{
    pinMode(SYNC_PIN, OUTPUT);
    Serial.begin(115200);
    OPENEPT_SYNC_PIN_VALUE = 0;
    return 1;
}

/**
 * @brief Sends a single character over UART.
 *
 * This function sends one character through UART2 using the HAL library.
 *
 * @param character The character to be transmitted.
 * @return OPEN_EPT_STATUS_OK on successful transmission,
 *         OPEN_EPT_STATUS_ERROR on transmission error.
 */
int OpenEPT_ED_Platform_Send(char character)
{
    Serial.print(character);
    return OPEN_EPT_STATUS_OK;
}


/**
 * @brief Read a single character over UART.
 *
 * This function Read one character through UART2 using the HAL library.
 *
 * @param character Read character.
 * @return OPEN_EPT_STATUS_OK on successful transmission,
 *         OPEN_EPT_STATUS_ERROR on transmission error.
 */
int OpenEPT_ED_Platform_Read(char* character)
{
    int ret = 0;
    Serial.setTimeout(1000);
    ret = Serial.readBytes(character, 1);
    if(ret <= 0) return OPEN_EPT_STATUS_ERROR;
    return OPEN_EPT_STATUS_OK;
}

/**
 * @brief Synchronizes up by setting GPIOA pin 5 to HIGH.
 *
 * This function sets GPIOA pin 5 to HIGH and verifies the pin state
 * to confirm the operation.
 *
 * @return OPEN_EPT_STATUS_OK if the pin is set successfully,
 *         OPEN_EPT_STATUS_ERROR if the pin state is incorrect.
 */
int OpenEPT_ED_Platform_SyncUp()
{
    digitalWrite(SYNC_PIN, HIGH);
    return OPEN_EPT_STATUS_OK;
}

/**
 * @brief Synchronizes down by setting GPIOA pin 5 to LOW.
 *
 * This function sets GPIOA pin 5 to LOW and verifies the pin state
 * to confirm the operation.
 *
 * @return OPEN_EPT_STATUS_OK if the pin is reset successfully,
 *         OPEN_EPT_STATUS_ERROR if the pin state is incorrect.
 */
int OpenEPT_ED_Platform_SyncDown()
{
    digitalWrite(SYNC_PIN, LOW);
    return OPEN_EPT_STATUS_OK;
}

/**
 * @brief Synchronizes down by setting GPIOA pin 5 to LOW.
 *
 * This function sets GPIOA pin 5 to LOW and verifies the pin state
 * to confirm the operation.
 *
 * @return OPEN_EPT_STATUS_OK if the pin is reset successfully,
 *         OPEN_EPT_STATUS_ERROR if the pin state is incorrect.
 */
int OpenEPT_ED_Platform_SyncToogle()
{
    OPENEPT_SYNC_PIN_VALUE = OPENEPT_SYNC_PIN_VALUE == 0 ? 1 : 0;
    digitalWrite(SYNC_PIN, OPENEPT_SYNC_PIN_VALUE);
    return OPEN_EPT_STATUS_OK;
}