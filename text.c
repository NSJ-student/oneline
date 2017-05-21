#include <stdlib.h>
#include "text.h"

static unsigned int cNum = 0;		// character number �Է¹��ڼ� ����
static unsigned int tmp_cNum = 0;

void Clr_Save_cNum()
{
	tmp_cNum = cNum;
	cNum = 0;
}

void Recover_cNum()
{
	cNum = tmp_cNum;
}

unsigned int Get_TxtNumber()
{
	return cNum;
}

int BackSpace(stChar ** pCur, stChar ** stHead)
{
	const stChar * stCur = *pCur;
	stChar * stTmp;

	if( 0 == stHead)	return FAIL;
	if( 0 == pCur )	return FAIL;
	if( 0 == *stHead )	return FAIL;	// �ؽ�Ʈ�� ������ ���� ����
	if( 0 == *pCur )	return FAIL;	// Ŀ���� �� ���̸� ���� ����

	///////////////////////////////////////// ���� ����Ʈ ���� ���� ����

// �� ���ڸ� �� ���ڶ� ����	
	if( 0 == (*pCur)->prev )	*stHead = (*pCur)->next;
	else 					(*pCur)->prev->next = (*pCur)->next;	

	if( 0 != (*pCur)->next)	(*pCur)->next->prev = (*pCur)->prev;	// �� ���ڸ� �� ���ڶ� ����
	
	*pCur = (*pCur)->prev;

	//////////////////////////////////////////////	���� ����

	free(stCur);		// ���� ��ġ�� ����
	cNum--;			// ������ ���� �� 1 ����

	////////////////////////////////////////////// 	char_number ����

	if( (*pCur) == 0)	stTmp = (*stHead);				// ���� �� Ŀ���� �� ���̸�
	else				stTmp = (*pCur)->next;
	
	// ������ ���� ���� char_number�� ����
	while( 0 != stTmp )
	{
		stTmp->char_number--;
		stTmp = stTmp->next;
	}

	return GOOD;
}

int Insert(char ch, stChar ** pCur, stChar ** stHead)
{
	stChar * stTmp;
	
	if( 0 == stHead)			return FAIL;
	if(cNum >= MAX_TEXT)		return FAIL;
	
	stTmp = (stChar *)malloc(sizeof(stChar));
	if( 0 == stTmp )			return FAIL;
	
	stTmp->character = ch;
	
	cNum++;

// �� �տ� ����
	if( 0 == *pCur)
	{
		if( 0 != *stHead )			(*stHead)->prev = stTmp;
		
		stTmp->next = *stHead;
		stTmp->prev = 0;
		stTmp->char_number = 1;
		*stHead = stTmp;
	}
	else
	{
		if( 0 != (*pCur)->next )	(*pCur)->next->prev = stTmp;
		
		stTmp->next = (*pCur)->next;
		stTmp->prev = *pCur;
		stTmp->char_number = (*pCur)->char_number + 1;
		(*pCur)->next = stTmp;
	}
	*pCur = stTmp;
	stTmp = stTmp->next;		// ���� ������ char_number�� ������Ű������ �ű�
	
	while( 0 != stTmp )
	{
		stTmp->char_number++;
		stTmp = stTmp->next;
	}
	
	return GOOD;
}

void Free_All(stChar ** stHead, stChar ** stCur)
{
	stChar * stTmp = *stHead;

	while( 0 != *stHead)
	{
		stTmp = *stHead;
		*stHead = (*stHead)->next;
		free(stTmp);
	}

	cNum = 0;
	*stCur = 0;	
}
