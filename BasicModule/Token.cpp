#include "token.h"

char ** Token::DelimList;

int delimcompare(const void * delim1,const void * delim2)
 	{ return strcmp(*(const char **)delim2,*(const char **)delim1); }

void Token::initDelimList(char ** delimlist)
{
	if (DelimList)
		error("Token::initDelimList(): initialize DelimList twice.");
	char ** delim=delimlist;
	while (**delim)
	{
		if (!isPctChar(*delim))
			error("Token::initDelimList(): illegal Delim.","Delim: ",*delim);
		delim++;
	}
	int delimnumber=delim-delimlist;
	if (delimnumber>=DELIMNUMBER)
		error("Token::initDelimList(): Too many delimiters.");
	qsort(delimlist,delimnumber,sizeof(char *),delimcompare);
	DelimList=delimlist;
}

int IToken::input()
{
	InPntr=ForeInPntr;
	if (!ForeInPntr)
		error("IToken::input(): input from NULL. ");
	else if (!*ForeInPntr) { *Buffer=0; return 0; }
	else if (isLtnChar(ForeInPntr)||isChnChar(ForeInPntr)||
			 *ForeInPntr=='_'||*ForeInPntr=='"')
	{
		char * b=Buffer;
		if (*ForeInPntr=='"')
		{
			ForeInPntr++;
			while (1)
			{
				if (!*ForeInPntr)
					error("IToken::input(): quato mismatch.",ForeInPntr-1);
				else if (*ForeInPntr!='"') *b++=*ForeInPntr++;
				else if (*(ForeInPntr+1)=='"')
					{ *b++=*ForeInPntr++; ForeInPntr++; }
				else { ForeInPntr++; break; }
			}
		}
		else while(isChnChar(ForeInPntr)||isLtnChar(ForeInPntr)||
				  isDgtChar(ForeInPntr)||*ForeInPntr=='_')
				setCharNext(b,ForeInPntr);
		*b=0;
		if (b-Buffer>TOKENLENGTH)
			error("IToken::inputIdent(): Token too long.","Buffer: ",Buffer);
		Type=IDENT;
	}
	else if (isDgtChar(ForeInPntr))
	{
		char * b=Buffer;
		while(isDgtChar(ForeInPntr)) setCharNext(b,ForeInPntr);
		*b=0;
		if (b-Buffer>TOKENLENGTH)
			error("IToken::inputIdent(): Token too long.","Buffer: ",Buffer);
		Type=INTEG;
	}
	else // if (isPctChar(ForeInPntr) || isOthChar(ForeInPntr))
	{
		char * b=Buffer;
		int i=setChar(b,ForeInPntr);
		b+=i;
		*b++=0;
		ForeInPntr+=i;
		if (DelimList)
		{
			char **delim=DelimList;
			//if (!(delim=DelimList))
			//	error("IToken::inputDelim(): DelimList does not initialized.");
			while (**delim)
			{
				b=Buffer;
				const char *d=*delim;
				while (*d && *b && *d==*b) { d++; b++; }
				if (*d < *b) break;
				if (!*b && *d)
				{
					const char *p=ForeInPntr;
					const char *e=d;
					while (*e && *e==*p) { e++; p++; }
					if (!*e) { while (*d++) { *b++=*ForeInPntr++; } *b=0; }
				}
				delim++;
			}
		}
		Type=DELIM;
	}
	// else error("IToken::input(): illegal token.");
	int length=ForeInPntr-InPntr;
	while (isSpcChar(ForeInPntr)) ForeInPntr++;
	if (length>TOKENLENGTH)
		error("IToken::input(): input Token to long.","InPntr: ",InPntr);
	return length;
}

void IToken::goupto(const char * str1, const char * str2 )
{
	if (InPntr==ForeInPntr) input();
	while (!isEqualTo(str1) && !isEqualTo(str2) && input());
}

void IToken::goover(const char * str1, const char * str2)
{
	if (InPntr==ForeInPntr) input();
	while (!isEqualTo(str1) && !isEqualTo(str2) && input());
	input();
}

void IToken::gouptomatch()
{
	char *left,*right;
	if (isDelim("(")) { left="("; right=")"; }
	else if (isDelim("{")) { left="{"; right="}"; }
	else if (isDelim("[")) { left="["; right="]"; }
	else if (isDelim("<")) { left="<"; right=">"; }
	else error("IToken::gouptomatch(): Nothing to match.","Buffer: ",Buffer);
	int i=1;
	while (i && input()) { if (isDelim(right)) i--; if (isDelim(left)) i++; }
}

void IToken::goovermatch()
{
	char *left,*right;
	if (isDelim("(")) { left="("; right=")"; }
	else if (isDelim("{")) { left="{"; right="}"; }
	else if (isDelim("[")) { left="["; right="]"; }
	else if (isDelim("<")) { left="<"; right=">"; }
	else error("IToken::goovermatch(): Nothing to match.","Buffer: ",Buffer);
	int i=1;
	while (i && input()) { if (isDelim(right)) i--; if (isDelim(left)) i++; }
	input();
}

int OToken::output()
{
	BackOutPntr=OutPntr;
	char * b=Buffer;
	int quato=0;
	if (Type==IDENT && !isChnChar(b) && !isLtnChar(b) && *b!='_')
		quato=1;
	while (*b)
	{
		if (Type==IDENT && !quato && !isChnChar(b) && !isLtnChar(b)
			&& !isDgtChar(b) && *b!='_') quato=1;
		if (Type==IDENT && *b=='"') *OutPntr++=*b;
		setCharNext(OutPntr,b);
	}
	if (quato)
	{
		OutPntr++; OutPntr++;
		char * pntr=OutPntr;
		pntr--; *pntr='"'; pntr--;
		while (pntr!=BackOutPntr) { *pntr=*(pntr-1); pntr--; }
		*pntr='"';
	}
	return OutPntr-BackOutPntr;
}

int OToken::output(const Token & t)
{
	BackOutPntr=OutPntr;
	const char * b=t.getBuffer();
	int quato=0;
	if (t.getType()==IDENT && !isChnChar(b) && !isLtnChar(b) && *b!='_')
		quato=1;
	while (*b)
	{
		if (t.getType()==IDENT && !quato && !isChnChar(b) && !isLtnChar(b)
			&& !isDgtChar(b) && *b!='_') quato=1;
		if (t.getType()==IDENT && *b=='"') *OutPntr++=*b;
		setCharNext(OutPntr,b);
	}
	if (quato)
	{
		OutPntr++; OutPntr++;
		char * pntr=OutPntr;
		pntr--; *pntr='"'; pntr--;
		while (pntr!=BackOutPntr) { *pntr=*(pntr-1); pntr--; }
		*pntr='"';
	}
	return OutPntr-BackOutPntr;
}

int OToken::output(const char c)
{
	BackOutPntr=OutPntr;
	*OutPntr++=c;
	return 1;
}

int OToken::output(const Code c)
{
	BackOutPntr=OutPntr;
	int pace=setChar(OutPntr,c);
	OutPntr+=pace;
	return pace;
}

int OToken::output(const char *s)
{
	if (s==NULL) return 0;
	BackOutPntr=OutPntr;
	while (*s) *OutPntr++=*s++;
	return OutPntr-BackOutPntr;
}

int OToken::outputIdent(const char *s)
{
	if (s==NULL) return 0;
	BackOutPntr=OutPntr;
	const char * b=s;
	int quato=0;
	if (!isChnChar(b) && !isLtnChar(b) && *b!='_') quato=1;
	while (*b)
	{
		if (!quato && !isChnChar(b) && !isLtnChar(b)
			&& !isDgtChar(b) && *b!='_') quato=1;
		if (*b=='"') *OutPntr++=*b;
		setCharNext(OutPntr,b);
	}
	if (quato)
	{
		OutPntr++; OutPntr++;
		char * pntr=OutPntr;
		pntr--; *pntr='"'; pntr--;
		while (pntr!=BackOutPntr) { *pntr=*(pntr-1); pntr--; }
		*pntr='"';
	}
	return OutPntr-BackOutPntr;
}

int OToken::outputNewLine()
{
	BackOutPntr = OutPntr;
#ifdef WIN32
	*OutPntr++='\r';
#endif
	*OutPntr++='\n';
	return 1;
}

int OToken::outputNull()
{
	BackOutPntr=OutPntr;
	*OutPntr++=0;
	return 1;
}

