#include <stdlib.h>
#include "text.h"

static unsigned int cNum = 0;		// character number 입력문자수 세기
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
	if( 0 == *stHead )	return FAIL;	// 텍스트가 없으면 동작 중지
	if( 0 == *pCur )	return FAIL;	// 커서가 맨 앞이면 동작 중지

	///////////////////////////////////////// 연결 리스트 연결 상태 조절

// 앞 문자를 뒷 문자랑 연결	
	if( 0 == (*pCur)->prev )	*stHead = (*pCur)->next;
	else 					(*pCur)->prev->next = (*pCur)->next;	

	if( 0 != (*pCur)->next)	(*pCur)->next->prev = (*pCur)->prev;	// 뒷 문자를 앞 문자랑 연결
	
	*pCur = (*pCur)->prev;

	//////////////////////////////////////////////	문자 삭제

	free(stCur);		// 현재 위치의 삭제
	cNum--;			// 라인의 문자 수 1 감소

	////////////////////////////////////////////// 	char_number 수정

	if( (*pCur) == 0)	stTmp = (*stHead);				// 삭제 후 커서가 맨 앞이면
	else				stTmp = (*pCur)->next;
	
	// 삭제한 글자 뒤의 char_number를 수정
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

// 맨 앞에 삽입
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
	stTmp = stTmp->next;		// 다음 문자의 char_number를 증가기키기위해 옮김
	
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
