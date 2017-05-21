#include <stdio.h>
#include <conio.h>
#include "draw.h"
#include "draw_c.h"
#include "cursor.h"
#include "text.h"
#include "menu.h"

int main(void)
{
	stChar * Head = 0;			// 문자가 저장된 공간 맨 앞을 가리키는 포인터
	stChar * Cur = 0;				// 현재 커서가 위치한 공간을 가리키는 포인터
	char ch = 0;					// 입력받은 문자
	char key = 0;					// 특수키 입력

	Set_File_Path(".\\save\\");
	clrscr();
	Draw_MainWindow();						// 메인 윈도우 그리기
	Move_Cursor(POS_TEXT_X, POS_TEXT_Y);		// 커서를 기본위치로

	while(ALT_X != key)			// ALT_X 입력이면 종료
	{
		ch = getch();				// 키 입력받음
		if( ch == 0 )				// 특수 키가 입력됨
		{
			key = getch();			// 특수키 입력받음
			switch(key)
			{
/////////// 메뉴로 포커스를 이동
				case F10: 		if( END == Menu(&Head, &Cur)) {	
									Free_All(&Head, &Cur);
									return 0;			// EXIT선택 & ALT_X 입력이면 종료
								}
								Draw_Text_Cursor(Cur);
								break;

////////// 커서 이동
				case HOME_KEY: 	Cur = 0;
								Draw_Text_Cursor(Cur); 			break;
				case END_KEY:	if(Cur == 0) 				Cur = Head;
								while( Cur->next != 0)  	Cur = Cur->next;
								Draw_Text_Cursor(Cur); 			break;
				case R_ARROW :  Draw_Text_RMove(Head, &Cur); 	break;
				case L_ARROW :	Draw_Text_LMove(&Cur); 			break;
				case U_ARROW : 	break;
				case D_ARROW : 	break;

////////// DEL 키로 삭제
				case DELETE : 	if( Head == 0) 		continue;	// 문자가 없으면 입력
								if( Cur->next == 0) 	continue;	// 커서가 맨 뒤면 다시 입력
								
								if(Cur == 0) 	Cur = Head;			// 커서가 맨 앞
								else			Cur = Cur->next;		// 커서가 맨 앞은 아님
								
								if( GOOD == BackSpace(&Cur, &Head) )
								{
									TextChanged();
									Draw_Text_Remove(Head, Cur);
								}break;
				case F1 : 		break;
				default: 			break;
			}
		}
		else		// 텍스트 문자가 입력됨
		{
			if(ch == BACK_SPACE)
			{
				if(Cur == 0) continue;	// 커서가 맨 앞이면 다시 입력 받음
				
				if( GOOD == BackSpace(&Cur, &Head) )
				{
					TextChanged();
					Draw_Text_Remove(Head, Cur);
				}
			}
			else if(ch >= SPACE)
			{
				if( GOOD ==Insert(ch, &Cur, &Head) )
				{
					TextChanged();
					Draw_Text_Input(Cur);
				}
			}
		}	
	}
	
	Free_All(&Head, &Cur);
	return 0;
}

/*
else
{
	VGA_CHAR(1, 15, '0'+ch/100);
	VGA_CHAR(2, 15, '0'+(ch%100)/10);
	VGA_CHAR(3, 15, '0'+ch%10);
}
*/