#ifndef __TEXT_H__
#define __TEXT_H__

#pragma pack(1)

typedef struct _char_tag {
	char character;			// 입력 문자
	int char_number;			// 문자 번호
	struct _char_tag * prev;	// 이전 문자 주소
	struct _char_tag * next;	// 다음 문자 주소
} stChar;

#pragma pack(4)

#define FAIL		-1
#define GOOD	0

#ifndef __DRAW_H__
#define WINDOW_W		80
#define TEXT_W			WINDOW_W-6
#define MAX_TEXT		TEXT_W-1
#endif

unsigned int Get_TxtNumber();
int Insert(char, stChar **, stChar **);
int BackSpace(stChar **, stChar **);
void Free_All(stChar **, stChar **);
void Clr_Save_cNum();
void Recover_cNum();

#endif /* __TEXT_H__ */