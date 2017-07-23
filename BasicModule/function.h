
#ifndef COMMON_H
#define COMMON_H

#include "constant.h"
#include <string.h>
#include <ctype.h>
#ifdef _DEBUG
#include "stdlib.h"
#endif

#ifdef WIN32
#define F_OK 00
#define X_OK 01
#define R_OK 02
#define W_OK 04
#define S_ISDIR(x) ((x)&(_S_IFDIR))
#endif

inline unsigned int strcpyn(char * s1,const char * s2,unsigned int l2)
{
	const char * b2=s2, * e2=s2+l2-1;
	while ((s2<e2) && (*s1=*s2)) { s1++; s2++; }
	if (s2==e2) *s1=0;
	return s2-b2;
}

inline int stricmp(const char * s1, const char * s2)
{
	while (*s1 && *s2 && tolower(*s1)==tolower(*s2)) { s1++; s2++; }
	return tolower(*s1)-tolower(*s2);
}

inline int stragree(const char * s1, const char * s2)
{
	while (*s1 && *s2 && *s1==*s2) { s1++; s2++; }
	if (*s1 && *s2)
	{
		if (*s1>*s2) return 2;
		else return -2;
	}
	else if (*s1) return 1;
	else if (*s2) return -1;
	else return 0;
}

void message(const char * msg1=NULL,
		     const char * msg2=NULL, const char * msg3=NULL);

int yesno(const char * msg,bool def=true);

void FileTouch(const char * lpszFile);
void FileCopyTo(const char * lpszSrcFile,const char * lpszDestFile);
void FileAppendTo(const char * lpszSrcFile,const char * lpszDestFile);
void FileAppendStringTo(const char * string,const char * lpszDestFile);

void FileLock(const char * filename,const char * msg);
void FileUnlock(const char * filename);

unsigned long FileGetTime(const char * filename);

void DirMake(const char * dirname);
bool DirSelect(char * dirname,const char * title="Please Select Directory:");

int ShellOpen(const char * file,const char * dir=NULL);
int ShellTextOpen(const char * file,const char * dir=NULL);

int getDstgVal(const char *word);
int getHashVal(const char *word,int Len);

#endif //COMMON_H