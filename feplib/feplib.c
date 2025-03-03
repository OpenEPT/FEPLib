/**
 * @file feplib.c
 * @brief Implementation of the OpenEPT Embedded Device (ED) library.
 *
 * This library provides functions for initializing and setting up communication
 * for embedded devices, with platform-specific function calls for
 * initialization, synchronization, and data transmission.
 *
 * @date November 3, 2024
 * @author Dimitrije Lilic, Haris Turkmanovic
 */

 #include <stdio.h>
 #include <string.h> 
 #include "feplib.h"
 #include "platform.h"
 

 static uint8_t OPENEPT_START_MSG[]           = "START\r";
 static uint8_t OPENEPT_START_MSG_SIZE        = 6;
 static uint8_t OPENEPT_STOP_MSG[]            = "STOP\r";
 static uint8_t OPENEPT_STOP_MSG_SIZE         = 5;
 static uint8_t OPENEPT_RECEIVE_BUFFER[OPENEPT_CONF_RECEIVE_BUFFER_SIZE];
 
 
 
 int OpenEPT_ED_Init()
 {
     if(OpenEPT_ED_Platform_Init() != 0) return OPEN_EPT_STATUS_ERROR;
     memset(OPENEPT_RECEIVE_BUFFER, 0, OPENEPT_CONF_RECEIVE_BUFFER_SIZE);
     return OPEN_EPT_STATUS_OK;
 }
 
 int OpenEPT_ED_Start()
 {
     uint32_t cntSend;
     uint32_t cntRec;
     char data = 0;
     uint8_t pingResend = 1;
     do
     {
         //Send ping message
         cntSend = 0;
         cntRec = 0;
 
         //Send Config message header
         if(OpenEPT_ED_Platform_Send('0') != 0) return OPEN_EPT_STATUS_ERROR;
         if(OpenEPT_ED_Platform_Send(':') != 0) return OPEN_EPT_STATUS_ERROR;
         
         //Send Config message content
         while(cntSend < OPENEPT_START_MSG_SIZE)
         {
             if(OpenEPT_ED_Platform_Send((char)OPENEPT_START_MSG[cntSend]) != 0) return OPEN_EPT_STATUS_ERROR;
             cntSend += 1;
         }
         
         //Wait for response
         do
         {
             if(OpenEPT_ED_Platform_Read(&data) != OPEN_EPT_STATUS_OK) break;
             OPENEPT_RECEIVE_BUFFER[cntRec] = data;
             cntRec += 1;
         }while(data != '\r');
 
         if(data == '\r')
         {
             //Check is received response OK\r 
             if(strncmp((const char*)OPENEPT_RECEIVE_BUFFER, "OK\r", 3) != 0)
             {
                 memset(OPENEPT_RECEIVE_BUFFER, 0, OPENEPT_CONF_RECEIVE_BUFFER_SIZE);
                 pingResend = 0;
             }
             else
             {
                 memset(OPENEPT_RECEIVE_BUFFER, 0, OPENEPT_CONF_RECEIVE_BUFFER_SIZE);
                 return OPEN_EPT_STATUS_OK;
             }
         }
 
     }while(pingResend == 1);
        
     return OPEN_EPT_STATUS_ERROR;
 }
 
 
 int OpenEPT_ED_Stop()
 {
     uint32_t cntSend;
     uint32_t cntRec;
     char data = 0;
     uint8_t pingResend = 1;
     do
     {
         //Send ping message
         cntSend = 0;
         cntRec = 0;
 
         //Send Config message header
         if(OpenEPT_ED_Platform_Send('0') != 0) return OPEN_EPT_STATUS_ERROR;
         if(OpenEPT_ED_Platform_Send(':') != 0) return OPEN_EPT_STATUS_ERROR;
         
         //Send Config message content
         while(cntSend < OPENEPT_STOP_MSG_SIZE)
         {
             if(OpenEPT_ED_Platform_Send((char)OPENEPT_STOP_MSG[cntSend]) != 0) return OPEN_EPT_STATUS_ERROR;
             cntSend += 1;
         }
         
         //Wait for response
         do
         {
             if(OpenEPT_ED_Platform_Read(&data) != OPEN_EPT_STATUS_OK) break;
             OPENEPT_RECEIVE_BUFFER[cntRec] = data;
             cntRec += 1;
         }while(data != '\r');
 
         if(data == '\r')
         {
             //Check is received response OK\r 
             if(strncmp((const char*)OPENEPT_RECEIVE_BUFFER, "OK\r", 3) != 0)
             {
                 memset(OPENEPT_RECEIVE_BUFFER, 0, OPENEPT_CONF_RECEIVE_BUFFER_SIZE);
                 pingResend = 0;
             }
             else
             {
                 memset(OPENEPT_RECEIVE_BUFFER, 0, OPENEPT_CONF_RECEIVE_BUFFER_SIZE);
                 return OPEN_EPT_STATUS_OK;
             }
         }
 
     }while(pingResend == 1);
        
     return OPEN_EPT_STATUS_ERROR;
 }
 
 
 int OpenEPT_ED_SetEPFast(uint8_t* epName, uint32_t epNameSize)
 {
     if(OpenEPT_ED_Platform_SyncToogle() != 0) return OPEN_EPT_STATUS_ERROR;
     uint32_t cnt = 0;
     //Send EP message header
     if(OpenEPT_ED_Platform_Send('1') != 0) return OPEN_EPT_STATUS_ERROR;
     if(OpenEPT_ED_Platform_Send(':') != 0) return OPEN_EPT_STATUS_ERROR;
     
     //Send EP message content
     while(cnt < epNameSize)
     {
         if(OpenEPT_ED_Platform_Send((char)epName[cnt]) != 0) return OPEN_EPT_STATUS_ERROR;
         cnt++;
     }
     if(OpenEPT_ED_Platform_Send('\r') != 0) return OPEN_EPT_STATUS_ERROR;
     return OPEN_EPT_STATUS_OK;
 
 }
 
 
 int OpenEPT_ED_SendInfo(const char* message)
 {    
     uint32_t cnt = 0;
     int msgLen = strlen(message);
     //Send EP message header
     if(OpenEPT_ED_Platform_Send('2') != 0) return OPEN_EPT_STATUS_ERROR;
     if(OpenEPT_ED_Platform_Send(':') != 0) return OPEN_EPT_STATUS_ERROR;
     
     //Send EP message content
     while(cnt < msgLen)
     {
         if(OpenEPT_ED_Platform_Send((char)message[cnt]) != 0) return OPEN_EPT_STATUS_ERROR;
         cnt++;
     }
     if(OpenEPT_ED_Platform_Send('\r') != 0) return OPEN_EPT_STATUS_ERROR;
     return OPEN_EPT_STATUS_OK;
 }

 
 
 