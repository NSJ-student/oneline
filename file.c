#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <sys\stat.h>
#include <sys\types.h>
#include "draw.h"
#include "file.h"

static char gbPath[DIALOG_PATH_W-2];

void Get_File_Path(char * caDialog_Path)
{
	unsigned int uiCnt = 0;
	
	for(uiCnt = 0; gbPath[uiCnt] != 0; uiCnt++)
	{
		caDialog_Path[uiCnt] = gbPath[uiCnt];
	}
	caDialog_Path[uiCnt] = 0;

	return;
}
void Set_File_Path(char * caDialog_Path)
{
	unsigned int uiCnt = 0;
	
	for(uiCnt = 0; caDialog_Path[uiCnt] != 0; uiCnt++)
	{
		gbPath[uiCnt] = caDialog_Path[uiCnt];
	}
	gbPath[uiCnt] = 0;

	return;
}

void Test_Ext(char * path)
{
	unsigned int uiCnt;
	unsigned int uiExt;
	char cExt[] = ".txt";
	
	for(uiCnt = 1; path[uiCnt] != 0; uiCnt++)
	{
		if(path[uiCnt] == '.')
		{
			break;
		}
	}
	
	for(uiExt = 0; cExt[uiExt] != 0; uiExt++)
	{
		path[uiCnt+uiExt] = cExt[uiExt];
	}
	path[uiCnt+uiExt] = 0;

	return;
}

int Save_File(char * path, stChar * stHead)
{
	int fd;

	Test_Ext(path);
	fd = creat(path, S_IREAD|S_IWRITE);
	if(fd == -1)
	{/*
		Print_Str("Error Save_File:: Can't Open => ");
		Print_Str(path);
		Print_Str("\n");
		*/
		return FAIL;
	}

	while( 0 != stHead )
	{
		write(fd, &(stHead->character), 1);
		if(stHead->char_number >= MAX_TEXT) 	break;
		stHead = stHead->next;
	}
	
	Set_File_Path(path);
	close(fd);
	return GOOD;
}

int Load_File(char * path, stChar ** stHead, stChar ** stCur)
{
	int fd;
	char ch;
	int ret = 1;
	stChar *  preHead;
	stChar * preCur;

	fd = open(path, O_RDWR|O_TEXT);
	if(fd == -1)
	{
	/*
		Print_Str("Error Load_File:: Can't Open => ");
		Print_Str(path);
		Print_Str("\n");
		*/
		return FAIL;
	}

	lseek(fd, 0, SEEK_SET);

	preHead = *stHead;
	preCur = *stCur;
	*stHead = 0;
	*stCur = 0;
	Clr_Save_cNum();
	
	while( ret != 0)
	{
		ret = read(fd, &ch, 1);

		if(ret == 0) break;
		
		if( FAIL == Insert(ch, stCur, stHead))
		{
			//Print_Str("Error Load_File:: Too Large File => "); Print_Str(path); Print_Str("\n");
			
			Free_All(stHead, stCur);
			
			*stHead = preHead;
			*stCur = preCur;
			Recover_cNum();

			close(fd);
			return FAIL;
		}
	}
	
	Set_File_Path(path);
	Clr_Save_cNum();
	Free_All(&preHead, &preCur);
	Recover_cNum();

	close(fd);
	return GOOD;
}
