#ifndef __TEXT_H__
#define __TEXT_H__

#pragma pack(1)

typedef struct _char_tag {
	char character;			// �Է� ����
	int char_number;			// ���� ��ȣ
	struct _char_tag * prev;	// ���� ���� �ּ�
	struct _char_tag * next;	// ���� ���� �ּ�
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