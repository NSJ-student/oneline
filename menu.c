#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "draw.h"
#include "draw_c.h"
#include "cursor.h"
#include "dialog.h"
#include "menu.h"
#include "file.h"

static BOOL set_path = NO;
static BOOL save_to_new = NO;

int Menu_Exit(stChar ** stHead);
void Menu_New(stChar ** stHead, stChar ** stCur);
void Menu_Save(stChar ** stHead, MENU_ITEM mNow);
void Menu_Load(stChar ** stHead, stChar ** stCur);

void TextChanged()
{
	save_to_new = YES;
}

int Menu(stChar ** stHead, stChar ** stCur)
{
	char cmd = 0;
	char asc = 0;
	MENU_ITEM mNow = NEW;
	char * path;

	Draw_CursorOn	(POS_ITEM_X(mNow), POS_MENU_Y, strlen(Menu_item[mNow]));
	Move_Cursor	(POS_ITEM_X(mNow), POS_MENU_Y);

	while( (asc = getch()) != ESC )
	{
		if( asc == 0 )			// 방향키로 메뉴 선택  & ALT_X
		{
			cmd = getch();

			if( (cmd == L_ARROW)&&(mNow>NEW) )
			{
				Draw_CursorOff	(POS_ITEM_X(mNow), POS_MENU_Y, strlen(Menu_item[mNow]));
				mNow--;
				Draw_CursorOn	(POS_ITEM_X(mNow), POS_MENU_Y, strlen(Menu_item[mNow]));
				Move_Cursor	(POS_ITEM_X(mNow), POS_MENU_Y);
			}
			else if( (cmd == R_ARROW)&&(mNow<EXIT) )
			{
				Draw_CursorOff	(POS_ITEM_X(mNow), POS_MENU_Y, strlen(Menu_item[mNow]));
				mNow++;
				Draw_CursorOn	(POS_ITEM_X(mNow), POS_MENU_Y, strlen(Menu_item[mNow]));
				Move_Cursor	(POS_ITEM_X(mNow), POS_MENU_Y);
			}
			else if(cmd == ALT_X)
				return END;
		}
		else if(asc == ENTER )		// 현재 커서가 위치한 메뉴를 선택
		{
			switch(mNow)
			{
				case NEW: 		Menu_New(stHead, stCur); 	break;
				case SAVE: 		Menu_Save(stHead, SAVE);  	break;
				case LOAD: 		Menu_Load(stHead, stCur); 	break;
				case SAVEAS:	Menu_Save(stHead, SAVEAS); 	break;
				case EXIT: 	if( END == Menu_Exit(stHead))	return END;
							else									break;
			}
			Move_Cursor(POS_ITEM_X(mNow), POS_MENU_Y);
		}
	}

	Draw_CursorOff(POS_ITEM_X(mNow), POS_MENU_Y, strlen(Menu_item[mNow]));

	return GO;
}

int Menu_Exit(stChar ** stHead)
{	
	char * path;
	void * scr;
	scr = malloc(80*25*2);

	while(1)
	{	
		if(save_to_new== YES) 	// new & load & save 후 텍스트 편집
		{
			gettext(1,1,80,25,scr);
			path = Dialog_NewExit(set_path, EXIT);
			puttext(1,1,80,25,scr);

			// cancel(path = 0)이 선택됨
			if(path == 0)
			{
				free(scr);
				return GO;			// cancel =>  [menu로]
			}
			// don't save(path = -1) & save
			else				
			{
				// save가 선택됨
				if(path != -1)		
				{
					if( GOOD != Save_File(path, *stHead))
					{
						Cursor_Off();
						gettext(1,1,80,25,scr);	
						Draw_ErrorBox("Save Error!");
						while(getchar() != '\n');
						puttext(1,1,80,25,scr);
						Cursor_On();
						set_path = NO;
						continue;			// save error 
					}
					else
					{
						break;
					}
				}
				else
				{
					set_path = NO;
					break;
				}
			}
		}
		else
		{
			break;
		}
	}

	free(scr);
	return END;		// save & don't save =>  [종료]
}


void Menu_New(stChar ** stHead, stChar ** stCur)
{	
	char * path;
	void * scr;
	scr = malloc(80*25*2);

	while(1)
	{	
		if(save_to_new== YES) 
		{
			gettext(1,1,80,25,scr);
			path = Dialog_NewExit(set_path, NEW);
			puttext(1,1,80,25,scr);

			// cancel(path = 0)이 선택됨
			if(path == 0)
			{
				free(scr);
				return;			// cancel => 그냥 종료 
			}
			// don't save(path = -1) & save
			else				
			{
				// save가 선택됨
				if(path != -1)		
				{
					if( GOOD != Save_File(path, *stHead))
					{
						Cursor_Off();
						gettext(1,1,80,25,scr);	
						Draw_ErrorBox("Save Error!");
						while(getchar() != '\n');
						puttext(1,1,80,25,scr);
						Cursor_On();
						set_path = NO;
						continue;
					}
					else
					{
						break;
					}
				}
				else
				{
					set_path = NO;
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	
	// Save or Don't Save  => page & linked list RESET
	set_path = NO;				
	save_to_new = NO;
	Clr_Text();
	Free_All(stHead, stCur);

	free(scr);
	return;	
}

void Menu_Save(stChar ** stHead, MENU_ITEM mNow)
{
	char * path;
	void * scr;
	scr = malloc(80*25*2);

	while(1)
	{
		// dialog에서 경로 설정을 받는다
		if((mNow == SAVEAS)||(set_path == NO) )
		{
			gettext(1,1,80,25,scr);		
			path = Dialog_SaveLoad(SAVEAS);
			puttext(1,1,80,25,scr);
		}
		// SAVE 메뉴를 선택 & 이미 경로설정이 된 경우 경로만 받아온다
		else
			path = Dialog_SaveLoad(SAVE);

		
		if(path != 0) 		// [cancel & esc] => path = 0 
		{
			if( GOOD == Save_File(path, *stHead)) 
			{
				set_path = YES;
				save_to_new = NO;
				break;
			}
			else
			{
				Cursor_Off();
				gettext(1,1,80,25,scr);	
				Draw_ErrorBox("Save Error!");
				while(getchar() != '\n');
				puttext(1,1,80,25,scr);
				Cursor_On();
				set_path = NO;
			}
		}
		else
		{
			set_path = NO;
			break;
		}
	}
	
	free(scr);
}

void Menu_Load(stChar ** stHead, stChar ** stCur)
{			
	char * path;
	void * scr;
	scr = malloc(80*25*2);

	while(1)
	{
		gettext(1,1,80,25,scr);		
		path = Dialog_SaveLoad(LOAD);
		puttext(1,1,80,25,scr);
		
		if(path != 0)
		{
			if( GOOD == Load_File(path, stHead, stCur) )
			{
				set_path = YES;
				save_to_new = NO;
				Clr_Text();
				Draw_Text_Load(*stHead);
				break;
			}
			else
			{
				Cursor_Off();
				gettext(1,1,80,25,scr);	
				Draw_ErrorBox("Load Error!");
				while(getchar() != '\n');
				puttext(1,1,80,25,scr);
				Cursor_On();
				set_path = NO;
			}
		}
		else
		{
			set_path = NO;
			break;
		}
	}
	
	free(scr);
}
