/**
 * @file nucleoh755ziq.c
 * @brief Platform template file.
 *
 * This file provides the STM32-specific functions to initialize UART communication and
 * GPIOs for synchronization purposes in the OpenEPT Embedded Device (ED) library.
 *
 * @date November 3, 2024
 * @author Dimitrije Lilic, Haris Turkmanovic
 */

 /*OPENEPT: Platform specific includes files should be included here */
 

 int OpenEPT_ED_Platform_Init()
 {
     /*OPENEPT: Platform initialization code is here */
     return OPEN_EPT_STATUS_OK;
 }

 int OpenEPT_ED_Platform_Send(char character)
 {
    /* OPENEPT: Code that sends one character through SERIAL interface should be implemented here */
     return OPEN_EPT_STATUS_OK;
 }

 int OpenEPT_ED_Platform_Read(char character)
 {
    /* OPENEPT: Code that read one character from SERIAL interface should be implemented here */
     return OPEN_EPT_STATUS_OK;
 }
 
 int OpenEPT_ED_Platform_SyncUp()
 {
    /* OPENEPT: Code that set SYNC pin high should be implemented here */
    return OPEN_EPT_STATUS_OK;
 }
 

 int OpenEPT_ED_Platform_SyncDown()
 {
    /* OPENEPT: Code that set SYNC pin low should be implemented here */
    return OPEN_EPT_STATUS_OK;
 }
 

 int OpenEPT_ED_Platform_SyncToogle()
 {
    /* OPENEPT: Code that set Toogle pin low should be implemented here */
    return OPEN_EPT_STATUS_OK;
 }
  