#ifndef PLATFOM_H_
#define PLATFOM_H_

int OpenEPT_ED_Platform_Init();
int OpenEPT_ED_Platform_Send(char character);
int OpenEPT_ED_Platform_Read(char* character);
int OpenEPT_ED_Platform_SyncUp();
int OpenEPT_ED_Platform_SyncDown();
int OpenEPT_ED_Platform_SyncToogle();

#endif