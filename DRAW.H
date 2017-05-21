#ifndef __DRAW_H__
#define __DRAW_H__

#define VGA_CHAR(x, y, ch)	(*((char far *)(0xb8000000 + (x)*2 + (y)*0xa0))) = (ch); \
							(*((char far *)(0xb8000000 + ((x)*2+1) + (y)*0xa0))) = 0x07
#define INV_CHAR(x, y)		(*((char far *)(0xb8000000 + ((x)*2+1) + (y)*0xa0))) = 0x70
#define ORG_CHAR(x, y)		(*((char far *)(0xb8000000 + ((x)*2+1) + (y)*0xa0))) = 0x07


//#define VGA_ATTR(x, y, at)	((*((char far *)(0xb8000000 + ((x)*2+1) + (y)*0xa0))) = (at))

// Extended ASCII - LINE 
#define H_LINE			196
#define V_LINE			179
#define LU_LINE			218
#define RU_LINE			191
#define LD_LINE			192
#define RD_LINE			217
#define EO_LINE			180
#define AA_LINE			195

// Extended ASCII - DOUBLE LINE 
#define H_LINE_D		205
#define V_LINE_D			186
#define LU_LINE_D		201
#define RU_LINE_D		187
#define LD_LINE_D		200
#define RD_LINE_D		188
#define EO_LINE_D		185
#define AA_LINE_D		204

// Menu component x-axis
#define POS_ITEM_X(x)	(5+12*(x))

#define POS_NEW		5+12*0
#define POS_LOAD		5+12*1
#define POS_SAVE		5+12*2
#define POS_SAVEAS		5+12*3	
#define POS_EXIT		5+12*4

#define POS_MENU_Y		1	// menu bar y-axis

// init cursor position
#define POS_TEXT_X		3	// text line initial x-axis
#define POS_TEXT_Y		6	// text line initial y-axis	

// Save&Load Dialog 관련
#define DIALOG_W			66			// dialog width
#define DIALOG_H			6			// dialog height
#define DIALOG_BTN_LEN		8			// Save&Load&Cancel button length
#define DIALOG_BTN_LEN2	12			// Don't Save button length
#define DIALOG_PATH_W		DIALOG_W-2	// path window width
#define DIALOG_PATH_H		3			// path window height

#define POS_DIALOG_X			7		// dialog left-up  x-axis
#define POS_DIALOG_Y			4		// dialog left-up y-axis
#define POS_PATH_X				9		// path window left-up y-axis
#define POS_PATH_Y				6		// path window left-up y-axis

// Error box
#define POS_ERR_X		29
#define POS_ERR_Y		4
#define ERR_MSG_W		18
#define ERR_W			20
#define ERR_H			6

// Save&Load 관련 다이얼로그 좌표
#define DIALOG_BLANK_W			((int)((DIALOG_W-2-DIALOG_BTN_LEN*2)/3))
																	// Save&Load x-axis
#define POS_OK_X				(POS_DIALOG_X -1 + DIALOG_BLANK_W)		
																	// Cancel x-axis
#define POS_CANCEL_X			(POS_OK_X +	DIALOG_BTN_LEN + DIALOG_BLANK_W)


#define POS_BTN_Y				(POS_DIALOG_Y+DIALOG_H-2)			// button y-axis	
// New 관련 다이얼로그 좌표
#define DIALOG_BLANK_W2		((int)((DIALOG_W-2-DIALOG_BTN_LEN*2-DIALOG_BTN_LEN2)/4))
																	// Save x-axis
#define POS_NEW_OK_X			(POS_DIALOG_X -1 + DIALOG_BLANK_W2)		
																	// Don't Save x-axis
#define POS_NEW_DONT_X		(POS_NEW_OK_X +	DIALOG_BTN_LEN + DIALOG_BLANK_W2)		
																	// Cancel x-axis
#define POS_NEW_CANCEL_X		(POS_NEW_DONT_X + DIALOG_BTN_LEN2 + DIALOG_BLANK_W2)

// 전체 윈도우 크기
#define WINDOW_W		80
#define WINDOW_H		14
#define TEXT_W			WINDOW_W-6
#define MAX_TEXT		TEXT_W-1

/* ASCII */
#define ESC				27
#define ENTER			13
#define BACK_SPACE		8
#define SPACE			32
#define TAB				9

/* KEY VALYE */
#define L_ARROW		75
#define R_ARROW		77
#define U_ARROW		72
#define D_ARROW		80
#define F1				59
#define F10				68
#define ALT_X			45
#define DELETE			83
#define HOME_KEY		71
#define END_KEY			79

typedef enum _act { NEW_IN, INPUT, REMOVE, CURSOR, R_MOVE, L_MOVE } ACT; 
typedef enum _item { NEW, LOAD, SAVE, SAVEAS, EXIT } MENU_ITEM;
typedef enum _save_item { S_WINDOW, S_OK, S_CANCEL } SITEM;
typedef enum _create_item { C_SAVE, C_DONT, C_CANCEL, C_WINDOW } CITEM;
typedef enum { YES, NO } BOOL;

extern const char * Menu_item[5];

// 그리기 기본 함수
void Draw_HLine(int y);
void Draw_Rect(int xi, int yi, int w, int h);
void Draw_Rect_D(int xi, int yi, int w, int h);

void Draw_CursorOn(int x, int y, int len);
void Draw_CursorOff(int x, int y, int len);

void Clr_Text();
void Clr_RestLine(int x, int y);
void Clr_Dialog();
void Clr_Line(int x, int y, int len);

// Dialog 관련
int Draw_Dialog_Save(char * path);
int Draw_Dialog_Load(char * path);
int Draw_DialogNewExit(char * path, MENU_ITEM now);
void Draw_DialogNewExit_Saved(char * path, MENU_ITEM now);
void Draw_DialogFocus(SITEM now, int cur);
void Draw_DialogFocusNewExit(CITEM now, int cur);
void Draw_ErrorBox(char * msg);


// 창 그리기
void Draw_MainWindow();

// 해당 좌표에 문자열 출력
int Put_Str(int x, int y, const char * str);
// 문자열 출력
void Print_Str(const char * str);


#endif /* __DRAW_H__ */
