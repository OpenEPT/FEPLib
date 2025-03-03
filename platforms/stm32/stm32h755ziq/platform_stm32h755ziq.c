/**
 * @file nucleoh755ziq.c
 * @brief Platform-specific implementation for NUCLEO-H755ZI-Q UART and GPIO initialization.
 *
 * This file provides the STM32-specific functions to initialize UART communication and
 * GPIOs for synchronization purposes in the OpenEPT Embedded Device (ED) library.
 *
 * @date November 3, 2024
 * @author Dimitrije Lilic, Haris Turkmanovic
 */
#include <strings.h>
#include "../../feplib.h"
#include "stm32h7xx.h"

UART_HandleTypeDef huart2;

/**
 * @brief Initializes the platform-specific peripherals for OpenEPT ED.
 *
 * This function initializes the GPIO and UART peripherals on the NUCLEO-H755ZI-Q.
 * It configures GPIOA and GPIOD pins for UART communication and sets up GPIOA for
 * general-purpose output (used for synchronization).
 *
 * @return OPEN_EPT_STATUS_OK if initialization is successful,
 *         OPEN_EPT_STATUS_ERROR if an error occurs during UART initialization.
 */
int OpenEPT_ED_Platform_Init()
{
     __HAL_RCC_GPIOA_CLK_ENABLE(); // Enable clock for GPIOA (change as needed)
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Configure GPIO pin PA5
    GPIO_InitStruct.Pin = GPIO_PIN_5; // Set pin PA5
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Push-Pull mode
    GPIO_InitStruct.Pull = GPIO_NOPULL; // No pull-up or pull-down
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // Low speed
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // Initialize GPIOA
    memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitTypeDef));

    __HAL_RCC_USART2_CLK_ENABLE(); // Enable clock for USART2
    __HAL_RCC_GPIOA_CLK_ENABLE(); // Enable clock for GPIOA
    __HAL_RCC_GPIOD_CLK_ENABLE(); // Enable clock for GPIOD

    // Configure PD5 (TX) and PA3 (RX) for UART2
    GPIO_InitStruct.Pin = GPIO_PIN_3; // Set pin PA3
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; // Alternate function mode for TX
    GPIO_InitStruct.Pull = GPIO_NOPULL; // No pull-up or pull-down
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // Very high speed
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2; // Alternate function for USART2
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // Initialize GPIOA

    memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitTypeDef)); // Reset structure
    GPIO_InitStruct.Pin = GPIO_PIN_5; // Set pin PD5
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; // Alternate function mode
    GPIO_InitStruct.Pull = GPIO_NOPULL; // No pull-up or pull-down
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH; // Very high speed
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2; // Alternate function for USART2
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct); // Initialize GPIOD

    // UART2 configuration
    huart2.Instance = USART2; // Select USART2
    huart2.Init.BaudRate = 115200; // Baud rate
    huart2.Init.WordLength = UART_WORDLENGTH_8B; // 8 data bits
    huart2.Init.StopBits = UART_STOPBITS_1; // 1 stop bit
    huart2.Init.Parity = UART_PARITY_NONE; // No parity
    huart2.Init.Mode = UART_MODE_TX_RX; // TX and RX enabled
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE; // No hardware flow control
    huart2.Init.OverSampling = UART_OVERSAMPLING_16; // Oversampling by 16

    if (HAL_UART_Init(&huart2) != HAL_OK) {
        // Initialization error
        return OPEN_EPT_STATUS_ERROR;
    }
    return OPEN_EPT_STATUS_OK;
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
    if(HAL_UART_Transmit(&huart2, (uint8_t*)&character, 1, HAL_MAX_DELAY) != HAL_OK) return OPEN_EPT_STATUS_ERROR;
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
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
    return (state == GPIO_PIN_SET) ? OPEN_EPT_STATUS_OK : OPEN_EPT_STATUS_ERROR;
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
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
    return (state == GPIO_PIN_RESET) ? OPEN_EPT_STATUS_OK : OPEN_EPT_STATUS_ERROR;
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
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
    return (state == GPIO_PIN_RESET) ? OPEN_EPT_STATUS_OK : OPEN_EPT_STATUS_ERROR;
}

