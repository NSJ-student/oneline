#include "dialog.h"


void Draw_Array_Move_Left(char path[], int idx);
void Draw_Array_Move_Right(char path [], int idx);

static char gbDPath[DIALOG_PATH_W-2];

char * Dialog_NewExit(const BOOL set_path, MENU_ITEM mNow)
{
	int idx = 0;
	char asc = 0;
	char cmd = 0;
	CITEM cNow = C_SAVE;
	int path_length = 0;

	Get_File_Path(gbDPath);
	if(set_path == NO)
	{
		cNow = C_WINDOW;
		idx = Draw_DialogNewExit(gbDPath, mNow);
		path_length = idx;
	}
	else
	{
		Draw_DialogNewExit_Saved(gbDPath, mNow);
		Draw_DialogFocusNewExit(cNow, 0);
	}
	
	while( (asc = getch()) != ESC)
	{
		// 커서 위치 움직이기
		if( asc == 0 )
		{
			cmd = getch();

			switch(cmd)
			{
				case R_ARROW: 	if(cNow != C_WINDOW) 
								{
									if(cNow == C_SAVE) 		cNow = C_DONT;
									else if(cNow == C_DONT) 	cNow = C_CANCEL;
								}
								else if( gbDPath[idx] != 0) idx++;
								break;
								
				case L_ARROW: 	if(cNow != C_WINDOW) 
								{
									if(cNow == C_DONT) 		cNow = C_SAVE;
									else if(cNow == C_CANCEL) 	cNow = C_DONT;
								}
								else if(idx> 0)			idx--;
								break;
								
				case D_ARROW:	if(cNow == C_WINDOW) 		cNow = C_SAVE; 		break;
				
				case U_ARROW: 	if(set_path == NO) 			cNow = C_WINDOW; 	break;
				default: 			continue;
			}
			Draw_DialogFocusNewExit(cNow, idx);
		}
		else if(asc == TAB)
		{
			cNow++;
			if(cNow > C_WINDOW)
			{
				cNow = C_SAVE;
			}
			Draw_DialogFocusNewExit(cNow, idx);
		}
		// 메뉴 선택
		else if(asc == ENTER)
		{
			if((cNow == C_SAVE)||(cNow == C_WINDOW))
			{
				Cursor_On();
				return gbDPath;		// 설정한 경로 반환
			}
			if(cNow == C_DONT)
			{
				Cursor_On();
				return -1;		// -1 반환
			}
			if(cNow == C_CANCEL)
			{
				Cursor_On();
				return 0;			// 0 반환
			}
		}
		// 문자 입력 & 삭제
		else if(cNow == C_WINDOW)
		{
			if(asc == BACK_SPACE)
			{
				if(idx > 0)
				{
					path_length--;
					idx--;
					Draw_Array_Move_Left(gbDPath, idx);
					Move_Cursor(idx+POS_PATH_X, POS_PATH_Y);
				}
			}
			else
			{
				if(path_length < DIALOG_PATH_W-3)
				{
					Draw_Array_Move_Right(gbDPath, idx);
					gbDPath[idx] = asc;
					VGA_CHAR(idx+POS_PATH_X, POS_PATH_Y, asc);
					Move_Cursor(idx+POS_PATH_X+1, POS_PATH_Y);
					
					idx++;
					path_length++;
				}
			}
		}
	}

	Cursor_On();
	return 0;
}


char * Dialog_SaveLoad(MENU_ITEM mNow)
{
	int idx = 0;
	char asc = 0;
	char cmd = 0;
	SITEM sNow = S_WINDOW;
	int path_length = 0;

	Get_File_Path(gbDPath);
	if(mNow == SAVE)
		return gbDPath;

	if(mNow == SAVEAS)
		idx = Draw_Dialog_Save(gbDPath);
	if(mNow == LOAD)
		idx = Draw_Dialog_Load(gbDPath);

	path_length = idx;
	
	while( (asc = getch()) != ESC)
	{
		// 커서 위치 움직이기
		if( asc == 0 )
		{
			cmd = getch();

			switch(cmd)
			{
				case R_ARROW: 	if(sNow != S_WINDOW) 	sNow = S_CANCEL; 
								else if( gbDPath[idx] != 0)		idx++;
								break;
				case L_ARROW: 	if(sNow != S_WINDOW) 	sNow = S_OK; 
								else if(idx> 0)			idx--;
								break;
				case D_ARROW: 	if(sNow == S_WINDOW) 	sNow = S_OK; 	break;
				case U_ARROW: 	sNow = S_WINDOW; 		break;
				default: 			continue;
			}
			Draw_DialogFocus(sNow, idx);
		}
		else if(asc == TAB)
		{
			sNow++;
			if(sNow > S_CANCEL)
			{
				sNow = S_WINDOW;
			}
			Draw_DialogFocus(sNow, idx);
		}
		// 메뉴 선택
		else if(asc == ENTER)
		{
			if((sNow == S_OK)||(sNow == S_WINDOW))		// 설정한 경로 반환
			{
				Cursor_On();
				return gbDPath;			
			}
			if(sNow == S_CANCEL)	// 0 반환
			{
				Cursor_On();
				return 0;				
			}
		}
		// 문자 입력 & 삭제
		else if(sNow == S_WINDOW)
		{
			if(asc == BACK_SPACE)
			{
				if(idx > 0)
				{
					path_length--;
					idx--;
					Draw_Array_Move_Left(gbDPath, idx);
					Move_Cursor(idx+POS_PATH_X, POS_PATH_Y);
				}
			}
			else
			{
				if(path_length < DIALOG_PATH_W-3)
				{
					Draw_Array_Move_Right(gbDPath, idx);
					gbDPath[idx] = asc;
					VGA_CHAR(idx+POS_PATH_X, POS_PATH_Y, asc);
					Move_Cursor(idx+POS_PATH_X+1, POS_PATH_Y);
					
					idx++;
					path_length++;
				}
			}
		}
	}

	Cursor_On();
	return 0;
}

void Draw_Array_Move_Left(char path[], int idx)
{
	if(*(path+idx+1) == '\0') 
	{
		*(path+idx) = '\0';
		VGA_CHAR(idx+POS_PATH_X, POS_PATH_Y, 0);
		return;
	}
	
	while( *(path+idx) != '\0' )
	{
		*(path+idx) = *(path+idx+1);
		VGA_CHAR(idx+POS_PATH_X, POS_PATH_Y, *(path+idx));
		idx++;
	}
}
void Draw_Array_Move_Right(char path [ ], int idx)
{
	int iSeeker = idx;

	for(; *(path +iSeeker) != '\0'; iSeeker++);
	
	if(iSeeker == idx) 
	{
		*(path+iSeeker+1) = '\0';
		return;
	}

	*(path+iSeeker+1) = '\0';
	while(iSeeker-1 >= idx)
	{
		*(path+iSeeker) = *(path+iSeeker-1);
		VGA_CHAR(iSeeker+POS_PATH_X, POS_PATH_Y, *(path+iSeeker));
		iSeeker--;
	}
}

