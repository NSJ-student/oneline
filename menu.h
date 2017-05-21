#ifndef __MENU_H__
#define __MENU_H__

#include "text.h"

#define GO		0
#define END		-1

void TextChanged();
int Menu(stChar ** stHead, stChar ** stCur);

#endif /* __MENU_H__ */