#include "cursor.h"
#include "draw.h"
#include "draw_c.h"
	
void Draw_Text_Cursor(stChar * stCur)
{
	// ���� ��ġ�� ���缭 Ŀ�� ��ġ�� �̵�
	if( stCur == 0 )	Move_Cursor(POS_TEXT_X, 					POS_TEXT_Y);
	else				Move_Cursor(POS_TEXT_X+stCur->char_number, 	POS_TEXT_Y);
}

void Draw_Text_RMove(stChar * stHead, stChar ** stCur)
{
	if( 0 == stHead)				return;				// �ؽ�Ʈ�� ������
	else if( 0 == (*stCur) )			*stCur = stHead;		// Ŀ����ġ�� �� ���̸�
	else if( 0 == (*stCur)->next )	return;				// Ŀ�� ��ġ�� �� �ڸ�
	else							*stCur = (*stCur)->next;

	// Ŀ�� ��ġ ����
	Move_Cursor(POS_TEXT_X+(*stCur)->char_number, POS_TEXT_Y);
}

void Draw_Text_LMove(stChar ** stCur)
{
	if( *stCur == 0 ) 		return;		// Ŀ�� ��ġ�� �� ���̸� ����

	// Ŀ���� �� ĭ �������̵�
	*stCur = (*stCur)->prev;
	// ���� Ŀ�� ��ġ ����
	if( *stCur == 0 )	Move_Cursor(POS_TEXT_X, 						POS_TEXT_Y);		// �� ��
	else				Move_Cursor(POS_TEXT_X+(*stCur)->char_number, 	POS_TEXT_Y);	// �� �� �ƴ�
}

void Draw_Text_Input(stChar * stCur)
{
	// ���� Ŀ�� ��ġ ����
	Move_Cursor(POS_TEXT_X+stCur->char_number, 	POS_TEXT_Y);
	// �Էµ� ���� ��ġ�� �������� ���ڸ� �� ĭ �ڷ� �о �׸���
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

	// ���� �� Ŀ����ġ�� �� ���̸�
	if(stCur == 0)						
	{
		stTmp = stHead;							// �� �� = stHead�� ����Ű�� ��ġ���� �׸�
		Move_Cursor(POS_TEXT_X, POS_TEXT_Y);	// Ŀ���� �� ������
		x = POS_TEXT_X;
	}
	// �� ���� �ƴϸ�
	else								
	{
		stTmp = stCur;							// ���� Ŀ����ġ���� �׸�
		Move_Cursor(POS_TEXT_X+stCur->char_number, POS_TEXT_Y);	// ���� Ŀ�� ��ġ ����
		x = POS_TEXT_X+stCur->char_number-1;
	}

	// ������ ��ġ ���� ���ڸ� ������ 1ĭ ����
	for( ; stTmp != 0; stTmp = stTmp->next , x++ )
	{
		VGA_CHAR(POS_TEXT_X+stTmp->char_number-1, POS_TEXT_Y, stTmp->character);
	}
	// ������ ���ڸ� �����
	VGA_CHAR(x, POS_TEXT_Y, ' ');
	
}


