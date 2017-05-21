#include <stdio.h>
#include <string.h>
#include "draw.h"
#include "cursor.h"
#include "text.h"

const char * Menu_item[5] = {"New", "Load", "Save", "Save as", "Exit"};

int Put_Str(int x, int y, const char * str)
{
	while( *str != 0 )
	{
		VGA_CHAR(x, y, *str);
		str++;
		x++;
	}

	return x;
}

void Print_Str(const char * str)
{
	static x = 0;
	static y = WINDOW_H + 1;

	while( *str != 0 )
	{
		if( *str == '\n' )
		{
			Clr_RestLine(x,y);

			y++;
			if(y > 24)	y = WINDOW_H+1;

			x = 0;
			str++;
			continue;
		}

		VGA_CHAR(x, y, *str);
		str++;
		x++;
		
		if(x > 79)
		{
			x = 0;
			y++;
			if(y > 24)	y = WINDOW_H+1;
		}
	}
}

void Draw_DialogNewExit_Saved(char * path, MENU_ITEM now)
{
	int pos;
	
	Clr_Dialog();
	Draw_Rect_D	(POS_DIALOG_X, 		POS_DIALOG_Y, 	DIALOG_W, 		DIALOG_H);
	Draw_Rect		(POS_DIALOG_X+1, 	POS_DIALOG_Y+1, DIALOG_PATH_W, 	DIALOG_PATH_H);
	if(now == NEW)
		Put_Str		(POS_DIALOG_X+2, 	POS_DIALOG_Y, 	" Create ");
	else if(now == EXIT)
		Put_Str		(POS_DIALOG_X+2, 	POS_DIALOG_Y, 	"  Exit  ");
	Put_Str			(POS_NEW_OK_X, 		POS_BTN_Y, 		"  Save  ");
	Put_Str			(POS_NEW_DONT_X, 	POS_BTN_Y, 		" Don't Save ");
	Put_Str			(POS_NEW_CANCEL_X, 	POS_BTN_Y, 		" Cancel ");
	pos = Put_Str	(POS_PATH_X, 		POS_PATH_Y, 		" Want to save in [ ");
	pos = Put_Str	(pos, 				POS_PATH_Y, 		path);
	Put_Str			(pos, 				POS_PATH_Y, 		" ]?");
}

int Draw_DialogNewExit(char * path, MENU_ITEM now)
{
	int idx = 0;

	Clr_Dialog();
	Draw_Rect_D	(POS_DIALOG_X, 		POS_DIALOG_Y, 	DIALOG_W, 		DIALOG_H);
	Draw_Rect		(POS_DIALOG_X+1, 	POS_DIALOG_Y+1, DIALOG_PATH_W, 	DIALOG_PATH_H);
	if(now == NEW)
		Put_Str		(POS_DIALOG_X+2, 	POS_DIALOG_Y, 	" Create ");
	else if(now == EXIT)
		Put_Str		(POS_DIALOG_X+2, 	POS_DIALOG_Y, 	"  Exit  ");
	Put_Str			(POS_NEW_OK_X, 		POS_BTN_Y, 		"  Save  ");
	Put_Str			(POS_NEW_DONT_X, 	POS_BTN_Y, 		" Don't Save ");
	Put_Str			(POS_NEW_CANCEL_X, 	POS_BTN_Y, 		" Cancel ");
	idx = Put_Str		(POS_PATH_X, 		POS_PATH_Y, 		path);
	Move_Cursor		(idx, 				POS_PATH_Y); 

	return idx-POS_PATH_X;
}

int Draw_Dialog_Save(char * path)
{
	int idx = 0;

	Clr_Dialog();
	Draw_Rect_D	(POS_DIALOG_X, 		POS_DIALOG_Y, 	DIALOG_W, 		DIALOG_H);
	Draw_Rect		(POS_DIALOG_X+1, 	POS_DIALOG_Y+1, DIALOG_PATH_W, 	DIALOG_PATH_H);
	Put_Str			(POS_DIALOG_X+2, 	POS_DIALOG_Y, 	" File ");
	Put_Str			(POS_OK_X, 			POS_BTN_Y, 		"  Save  ");
	Put_Str			(POS_CANCEL_X, 		POS_BTN_Y, 		" Cancel ");
	idx = Put_Str		(POS_PATH_X, 		POS_PATH_Y, 		path);
	Move_Cursor		(idx, 				POS_PATH_Y); 

	return idx-POS_PATH_X;
}
int Draw_Dialog_Load(char * path)
{
	int idx = 0;

	Clr_Dialog();
	Draw_Rect_D	(POS_DIALOG_X, 		POS_DIALOG_Y, 	DIALOG_W, 		DIALOG_H);
	Draw_Rect		(POS_DIALOG_X+1, 	POS_DIALOG_Y+1, DIALOG_PATH_W, DIALOG_PATH_H);
	Put_Str			(POS_DIALOG_X+2, 	POS_DIALOG_Y, 	" File ");
	Put_Str			(POS_OK_X, 			POS_BTN_Y, 		"  Load  ");
	Put_Str			(POS_CANCEL_X, 		POS_BTN_Y, 		" Cancel ");
	idx = Put_Str		(POS_PATH_X, 		POS_PATH_Y, 		path);
	Move_Cursor		(idx, 				POS_PATH_Y); 

	return idx-POS_PATH_X;
}
void Draw_DialogFocusNewExit(CITEM now, int cur)
{
	if(now == C_SAVE)
	{
		Cursor_Off();		
		Draw_CursorOff	(POS_NEW_DONT_X, 	POS_BTN_Y, 	DIALOG_BTN_LEN2);
		Draw_CursorOff	(POS_NEW_CANCEL_X, 	POS_BTN_Y, 	DIALOG_BTN_LEN);
		Draw_CursorOn	(POS_NEW_OK_X, 		POS_BTN_Y, 	DIALOG_BTN_LEN);
	}
	if(now == C_CANCEL)
	{	
		Cursor_Off();	
		Draw_CursorOff	(POS_NEW_DONT_X, 	POS_BTN_Y, 	DIALOG_BTN_LEN2);
		Draw_CursorOff	(POS_NEW_OK_X, 		POS_BTN_Y,	DIALOG_BTN_LEN);
		Draw_CursorOn	(POS_NEW_CANCEL_X, 	POS_BTN_Y, 	DIALOG_BTN_LEN);
	}	
	if(now == C_DONT)
	{	
		Cursor_Off();	
		Draw_CursorOn	(POS_NEW_DONT_X, 	POS_BTN_Y, 	DIALOG_BTN_LEN2);
		Draw_CursorOff	(POS_NEW_OK_X, 		POS_BTN_Y,	DIALOG_BTN_LEN);
		Draw_CursorOff	(POS_NEW_CANCEL_X, 	POS_BTN_Y, 	DIALOG_BTN_LEN);
	}	
	if(now == C_WINDOW)
	{		
		Cursor_On();
		Draw_CursorOff	(POS_NEW_DONT_X, 	POS_BTN_Y, 	DIALOG_BTN_LEN2);
		Draw_CursorOff	(POS_NEW_CANCEL_X, 	POS_BTN_Y, 	DIALOG_BTN_LEN);
		Draw_CursorOff	(POS_NEW_OK_X, 		POS_BTN_Y,	DIALOG_BTN_LEN);
		Move_Cursor		(POS_PATH_X+cur, 	POS_PATH_Y);
	}
}

void Draw_DialogFocus(SITEM now, int cur)
{
	if(now == S_OK)
	{
		Cursor_Off();		
		Draw_CursorOff	(POS_CANCEL_X, 	POS_BTN_Y, 	DIALOG_BTN_LEN);
		Draw_CursorOn	(POS_OK_X, 		POS_BTN_Y, 	DIALOG_BTN_LEN);
	}
	if(now == S_CANCEL)
	{	
		Cursor_Off();	
		Draw_CursorOff	(POS_OK_X, 		POS_BTN_Y,	DIALOG_BTN_LEN);
		Draw_CursorOn	(POS_CANCEL_X, 	POS_BTN_Y, 	DIALOG_BTN_LEN);
	}	
	if(now == S_WINDOW)
	{		
		Cursor_On();
		Draw_CursorOff	(POS_CANCEL_X, 	POS_BTN_Y, 	DIALOG_BTN_LEN);
		Draw_CursorOff	(POS_OK_X, 		POS_BTN_Y,	DIALOG_BTN_LEN);
		Move_Cursor		(POS_PATH_X+cur, POS_PATH_Y);
	}
}

void Draw_MainWindow(void)
{
	Draw_Rect	(0, 	0, 	WINDOW_W, 		WINDOW_H);
	Draw_Rect	(1, 	4, 	WINDOW_W-2, 	5);
	Draw_Rect	(2, 	5, 	WINDOW_W-4, 	3);
	Draw_Rect	(1, 	10, 	WINDOW_W-2, 	3);

	Draw_HLine(2);

	Put_Str(POS_NEW, 	POS_MENU_Y, 	Menu_item[NEW]);
	Put_Str(POS_LOAD, 	POS_MENU_Y, 	Menu_item[LOAD]);
	Put_Str(POS_SAVE, 	POS_MENU_Y, 	Menu_item[SAVE]);
	Put_Str(POS_SAVEAS, 	POS_MENU_Y, 	Menu_item[SAVEAS]);
	Put_Str(POS_EXIT, 	POS_MENU_Y, 	Menu_item[EXIT]);

	Put_Str(7, 	11, 	"F10 - Menu");
	Put_Str(25, 	11, 	"Alt + x - Exit");
	Put_Str(47, 	11, 	"F1 - Help");
}
void Draw_ErrorBox(char * msg)
{
	int len;
	
	Draw_Rect_D(POS_ERR_X, POS_ERR_Y, ERR_W, ERR_H);
	
	Clr_Line(POS_ERR_X+1, POS_ERR_Y+1, ERR_MSG_W);
	Clr_Line(POS_ERR_X+1, POS_ERR_Y+2, ERR_MSG_W);
	Clr_Line(POS_ERR_X+1, POS_ERR_Y+3, ERR_MSG_W);
	Clr_Line(POS_ERR_X+1, POS_ERR_Y+4, ERR_MSG_W);

	len = strlen(msg);
	Put_Str(POS_ERR_X+1+(int)((ERR_W-len)/2), POS_ERR_Y+2, msg);
	
	Put_Str(POS_ERR_X+2, POS_ERR_Y, " Error ");
	Put_Str(POS_ERR_X+((ERR_W-6)/2), 			POS_ERR_Y+ERR_H-2, "  OK  ");
	Draw_CursorOn(POS_ERR_X+((ERR_W-6)/2), 	POS_ERR_Y+ERR_H-2, 6);
}
void Draw_HLine(int y)
{
	int x = 0;

	VGA_CHAR(x, y, AA_LINE);
	for(x++; x<79; x++)
	{
		VGA_CHAR(x, y, H_LINE);
	}
	VGA_CHAR(x, y, EO_LINE);
}

void Clr_Text()
{
	int i;
	for(i = 0; i<TEXT_W; i++)
	{
		VGA_CHAR(POS_TEXT_X+i, POS_TEXT_Y, ' ');
	}
}
void Clr_RestLine(int x, int y)
{
	int i;
	
	for(i = x; i<WINDOW_W; i++)
	{
		VGA_CHAR(i, y, ' ');
	}
}
void Clr_Line(int x, int y, int len)
{
	int i;
	
	for(i = x; i<x+len; i++)
	{
		VGA_CHAR(i, y, 0);
	}
}

void Clr_Dialog()
{
	int i, j;
	for(j = 0; j<DIALOG_H-2; j++)
	{
		for(i = 0; i<DIALOG_W-2; i++)
		{
			VGA_CHAR(POS_PATH_X-1+i, POS_PATH_Y+j, ' ');
		}
	}
}

void Draw_CursorOff(int x, int y, int len)
{
	for(; len>0; len--, x++)
	{
		ORG_CHAR(x, y);
	}
}

void Draw_CursorOn(int x, int y, int len)
{
	for(; len>0; len--, x++)
	{
		INV_CHAR(x, y);
	}
}

void Draw_Rect(int xi, int yi, int w, int h)
{
	int x = xi;
	int y = yi;

	VGA_CHAR(x, y, LU_LINE);
	
	for(x++; x<w-1+xi; x++)
	{
		VGA_CHAR(x, y, H_LINE);
	}

	VGA_CHAR(x, y, RU_LINE);

	for(y++; y<h-1+yi; y++)
	{
		VGA_CHAR(x, y, V_LINE);
	}

	VGA_CHAR(x, y, RD_LINE);

	for(x--; x>xi; x--)
	{
		VGA_CHAR(x, y, H_LINE);
	}

	VGA_CHAR(x, y, LD_LINE);

	for(y--; y>yi; y--) 
	{
		VGA_CHAR(x, y, V_LINE);
	}



}

void Draw_Rect_D(int xi, int yi, int w, int h)
{
	int x = xi;
	int y = yi;

	VGA_CHAR(x, y, LU_LINE_D);
	
	for(x++; x<w-1+xi; x++)
	{
		VGA_CHAR(x, y, H_LINE_D);
	}

	VGA_CHAR(x, y, RU_LINE_D);

	for(y++; y<h-1+yi; y++)
	{
		VGA_CHAR(x, y, V_LINE_D);
	}

	VGA_CHAR(x, y, RD_LINE_D);

	for(x--; x>xi; x--)
	{
		VGA_CHAR(x, y, H_LINE_D);
	}

	VGA_CHAR(x, y, LD_LINE_D);

	for(y--; y>yi; y--) 
	{
		VGA_CHAR(x, y, V_LINE_D);
	}



}
