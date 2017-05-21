#ifndef __DRAW_TEXT_H__
#define __DRAW_TEXT_H__

#include "text.h"

// 텍스트창 문자&커서
void Draw_Text_Remove(stChar * stHead, stChar * stCur);
void Draw_Text_Load(stChar * stHead);
void Draw_Text_Input(stChar * stCur);
void Draw_Text_LMove(stChar ** stCur);
void Draw_Text_RMove(stChar * stHead, stChar ** stCur);
void Draw_Text_Cursor(stChar * stCur);

#endif /* __DRAW_TEXT_H__ */
