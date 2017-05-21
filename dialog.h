#ifndef __DIALOG_H__
#define __DIALOG_H__

#include "draw.h"
#define DEFAULT_PATH	".\\"


char * Dialog_SaveLoad(MENU_ITEM aNow);
char * Dialog_NewExit(const BOOL set_path, MENU_ITEM aNow);

#endif /* __DIALOG_H__ */