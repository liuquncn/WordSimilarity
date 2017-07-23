
#ifndef TOKEN_H

#define TOKEN_H
#include <string.h>
#include "code.h"

static const int TOKENLENGTH=32;
static const int DELIMNUMBER=256;

enum { IDENT=1, INTEG=2, DELIM=3 };

class Token
{

 protected:
	static char * * DelimList;
	
	int Type;
	char Buffer [TOKENLENGTH];

  public:

	Token() { Type=NULL; *Buffer=0; }
	Token(const Token &token)
		{ Type=token.Type; strcpyn(Buffer,token.Buffer,TOKENLENGTH); }

	static char * * getDelimList() { return DelimList; }
	static void initDelimList(char ** delimlist);

	int getType() const { return Type; }
	const char * getBuffer() const { return Buffer; }
	void setType(int t) { Type=t; }
	void setBuffer(const char *s) { strcpy(Buffer,s); }

	bool isIdent() { return Type==IDENT; }
	bool isIdent(const char *s) { return (Type==IDENT) && (!strcmp(s,Buffer)); }
	bool isInteg() { return Type==INTEG; }
	bool isInteg(int n) { return (Type==INTEG) && (atoi(Buffer)==n); }
	bool isInteg(const char *s){return (Type==INTEG) && (atoi(Buffer)==atoi(s)); }
	bool isDelim() { return Type==DELIM; }
	bool isDelim(const char *s) { return (Type==DELIM) && (!strcmp(s,Buffer)); }
	bool isEmpty() { return !*Buffer; }

	bool isEqualTo(Token &t)
	{
		if (Type!=t.Type) return false;
		else if (Type==INTEG) return atoi(Buffer)==atoi(t.Buffer);
		else return !strcmp(Buffer,t.Buffer);
	}
	bool isEqualTo(const char *s)
	{
		if (!s || !*s) return (!*Buffer);
		else if (isLtnChar(s) || isChnChar(s) || *s=='_' ) return isIdent(s);
		else if (isDgtChar(s)) return isInteg(s);
		else if (isPctChar(s)) return isDelim(s);
		error("Token::isEqualTo(): illegal token.","String: ",s);return 1;
	}
	bool isEqualTo(int n) { return isInteg(n); }

	bool operator == ( Token &t ) { return isEqualTo(t); }
	bool operator == ( const char *s) { return isEqualTo(s); }
	bool operator == ( int n) { return isInteg(n); }
	bool operator != ( Token &t ) { return (!isEqualTo(t)); }
	bool operator != ( const char *s) { return (!isEqualTo(s)); }
	bool operator != ( int n) { return (!isInteg(n)); }

	operator const char * () { return Buffer; }
};

class IToken: virtual public Token
{
protected:

	const char * InPntr;
	const char * ForeInPntr;

  public:

	IToken() { InPntr=ForeInPntr=NULL; }
	IToken(const char *s) { while (isSpcChar(s)) s++; InPntr=ForeInPntr=s; }
	IToken(const IToken & itoken) : Token(itoken)
		{ InPntr=itoken.InPntr; ForeInPntr=itoken.ForeInPntr; }

	const char * getInPntr() { return InPntr; }
	const char * getForeInPntr() { return ForeInPntr; }
	int getInPace() { return ForeInPntr-InPntr; }

	void setInPntr(const char *s) { while (isSpcChar(s)) s++; InPntr=ForeInPntr=s; }
	void redrawin()
	{
		if (InPntr==ForeInPntr)
			error("IToken::redrawin(): redrawin twice.","InPntr: ",InPntr);
		ForeInPntr=InPntr;
	}

	int input();

	void goupto(const char * s1, const char * s2=NULL );
	void goover(const char * s1, const char * s2=NULL );
	void gouptomatch();
	void goovermatch();

	friend void goupto( const char * &pntr, const char * s1, const char * s2=NULL );
	friend void goover( const char * &pntr, const char * s1, const char * s2=NULL );
	friend void gouptomatch( const char * &pntr );
	friend void goovermatch( const char * &pntr );

};

inline void goupto( const char * &pntr, const char * s1, const char * s2 )
{
	IToken token(pntr);
	token.goupto(s1,s2);
	pntr=token.getInPntr();
}
inline void goover( const char * &pntr, const char * s1, const char * s2 )
{
	IToken token(pntr);
	token.goover(s1,s2);
	pntr=token.getInPntr();
}
inline void gouptomatch( const char * &pntr )
{
	IToken token(pntr);
	token.gouptomatch();
	pntr=token.getInPntr();
}
inline void goovermatch( const char * &pntr )
{
	IToken token(pntr);
	token.goovermatch();
	pntr=token.getInPntr();
}

class OToken: virtual public Token
{
protected:

	char * OutPntr;
	char * BackOutPntr;

public:

	OToken() { OutPntr=BackOutPntr=NULL; }
	OToken(char *s) { OutPntr=BackOutPntr=s; }
	OToken(const OToken & otoken) : Token(otoken)
		{ OutPntr=otoken.OutPntr; BackOutPntr=otoken.BackOutPntr; }

	char * getOutPntr() { return OutPntr; }
	char * getBackOutPntr() { return BackOutPntr; }
	int getOutPace() { return OutPntr-BackOutPntr; }

	void setOutPntr(char *s) { OutPntr=BackOutPntr=s; }
	void redrawout()
	{
		if (BackOutPntr==OutPntr)
			error("OToken::redrawout(): redrawout twice.","OutPntr: ",OutPntr);
		OutPntr=BackOutPntr;
	}

	int output();
	int output(const Token & t);
	int output(const char c);
	int output(const Code c);
	int output(const char *s);
	int outputIdent(const char *s);
	int outputNewLine();
	int outputNull();
};

class IOToken: public IToken, public OToken
{

  public:

	IOToken(){}
	IOToken(const char *in,char *out):IToken(in),OToken(out){}
	IOToken(const IOToken & iotoken) : Token(iotoken)
	{
		OutPntr=iotoken.OutPntr; BackOutPntr=iotoken.BackOutPntr;
		InPntr=iotoken.InPntr; ForeInPntr=iotoken.ForeInPntr;
	}
	operator const char * () { return Token::operator const char * (); }

};

#endif

