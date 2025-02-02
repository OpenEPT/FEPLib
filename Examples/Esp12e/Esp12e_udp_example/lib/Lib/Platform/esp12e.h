/*
 * nucleoh755ziq.h
 *
 *  Created on: Nov 3, 2024
 *      Author: Dimitrije Lilic
 */

#pragma once

int OpenEPT_ED_Platform_Init();
int OpenEPT_ED_Platform_Send(char character);
int OpenEPT_ED_Platform_Read(char* character);
int OpenEPT_ED_Platform_SyncUp();
int OpenEPT_ED_Platform_SyncDown();
int OpenEPT_ED_Platform_SyncToogle();

