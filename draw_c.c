#include "cursor.h"
#include "draw.h"
#include "draw_c.h"
	
void Draw_Text_Cursor(stChar * stCur)
{
	// 현재 위치에 맞춰서 커서 위치를 이동
	if( stCur == 0 )	Move_Cursor(POS_TEXT_X, 					POS_TEXT_Y);
	else				Move_Cursor(POS_TEXT_X+stCur->char_number, 	POS_TEXT_Y);
}

void Draw_Text_RMove(stChar * stHead, stChar ** stCur)
{
	if( 0 == stHead)				return;				// 텍스트가 없으면
	else if( 0 == (*stCur) )			*stCur = stHead;		// 커서위치가 맨 앞이면
	else if( 0 == (*stCur)->next )	return;				// 커서 위치가 맨 뒤면
	else							*stCur = (*stCur)->next;

	// 커서 위치 설정
	Move_Cursor(POS_TEXT_X+(*stCur)->char_number, POS_TEXT_Y);
}

void Draw_Text_LMove(stChar ** stCur)
{
	if( *stCur == 0 ) 		return;		// 커서 위치가 맨 앞이면 종료

	// 커서를 한 칸 앞으로이동
	*stCur = (*stCur)->prev;
	// 현재 커서 위치 설정
	if( *stCur == 0 )	Move_Cursor(POS_TEXT_X, 						POS_TEXT_Y);		// 맨 앞
	else				Move_Cursor(POS_TEXT_X+(*stCur)->char_number, 	POS_TEXT_Y);	// 맨 앞 아님
}

void Draw_Text_Input(stChar * stCur)
{
	// 현재 커서 위치 설정
	Move_Cursor(POS_TEXT_X+stCur->char_number, 	POS_TEXT_Y);
	// 입력된 문자 위치를 기준으로 문자를 한 칸 뒤로 밀어서 그린다
	for( ; stCur != 0; stCur = stCur->next )
	{
		VGA_CHAR(POS_TEXT_X+stCur->char_number-1, 	POS_TEXT_Y, stCur->character);
	}
}

void Draw_Text_Load(stChar * stHead)
{
	int x = POS_TEXT_X;
	
	for( ; stHead != 0; stHead = stHead->next, x++ )
	{
		VGA_CHAR(POS_TEXT_X+stHead->char_number-1, POS_TEXT_Y, stHead->character);
	}

	Move_Cursor(x, POS_TEXT_Y);
}

void Draw_Text_Remove(stChar * stHead, stChar * stCur)
{
	stChar * stTmp;
	int x;

	// 삭제 후 커서위치가 맨 앞이면
	if(stCur == 0)						
	{
		stTmp = stHead;							// 맨 앞 = stHead가 가리키는 위치부터 그림
		Move_Cursor(POS_TEXT_X, POS_TEXT_Y);	// 커서는 맨 앞으로
		x = POS_TEXT_X;
	}
	// 맨 앞이 아니면
	else								
	{
		stTmp = stCur;							// 현재 커서위치부터 그림
		Move_Cursor(POS_TEXT_X+stCur->char_number, POS_TEXT_Y);	// 현재 커서 위치 설정
		x = POS_TEXT_X+stCur->char_number-1;
	}

	// 삭제된 위치 다음 문자를 앞으로 1칸 당긴다
	for( ; stTmp != 0; stTmp = stTmp->next , x++ )
	{
		VGA_CHAR(POS_TEXT_X+stTmp->char_number-1, POS_TEXT_Y, stTmp->character);
	}
	// 마지막 문자를 지운다
	VGA_CHAR(x, POS_TEXT_Y, ' ');
	
}


