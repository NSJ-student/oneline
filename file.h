#ifndef __FILE_H__
#define __FILE_H__

#include "text.h"

int Save_File(char * path, stChar * stHead);
int Load_File(char * path, stChar ** stHead, stChar ** stCur);
void Get_File_Path(char * caDialog_Path);
void Set_File_Path(char * caDialog_Path);

#endif /* __FILE_H__*/
