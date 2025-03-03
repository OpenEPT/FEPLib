#ifndef PLATFOM_H_
#define PLATFOM_H_


#define OPEN_EPT_STATUS_OK                  0
#define OPEN_EPT_STATUS_ERROR               1


#ifdef __cplusplus
extern "C" {
#endif
int OpenEPT_ED_Platform_Init();
int OpenEPT_ED_Platform_Send(char character);
int OpenEPT_ED_Platform_Read(char* character);
int OpenEPT_ED_Platform_SyncUp();
int OpenEPT_ED_Platform_SyncDown();
int OpenEPT_ED_Platform_SyncToogle();
#ifdef __cplusplus
}
#endif

#endif