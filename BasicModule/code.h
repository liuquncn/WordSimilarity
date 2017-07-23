
#ifndef CODE_H

#define CODE_H

#include "error.h"
#include "constant.h"
#include <stdlib.h>
#include <ctype.h>

inline unsigned char getNrByte(const char * pntr) // get Near Byte
	{ return (unsigned char)(*pntr); }
inline unsigned char getFrByte(const char * pntr) // get Far Byte
	{ return (unsigned char)(*(pntr+1)); }
inline bool isDblByte( const char * pntr )
{
	int val=(getNrByte(pntr)&0x80)?
				(getFrByte(pntr)&0xc0)?
					1:
					-1:
				0;
	if (val==-1) error("isDblByte(char *): Half Chinese character.");
	return val!=0;
}
inline bool isSglByte( const char * pntr )
{
	int val=(getNrByte(pntr)&0x80)?
				(getFrByte(pntr)&0xc0)?
					0:
					-1:
				1;
	if (val==-1) error("isSglByte(char *): Half Chinese character.");
	return val!=0;
}

struct Code
{
	unsigned char HiByte;  // High Byte
	unsigned char LoByte;  // Low Byte
	Code() { HiByte=0; LoByte=0; }
	Code(const unsigned char hi,const unsigned char lo)
		{ HiByte=hi; LoByte=lo; }
	Code(const char * pntr)
		{ if (isDblByte(pntr)) { HiByte=*pntr++; LoByte=*pntr; } else {HiByte=0; LoByte=*pntr; } }
	int operator == (const Code & code)
		{ return HiByte==code.HiByte && LoByte==code.LoByte; }
	int operator != (const Code & code)
		{ return HiByte!=code.HiByte || LoByte!=code.LoByte; }
};
inline unsigned char getHiByte(Code code) // get High Byte
	{ return code.HiByte; }
inline unsigned char getLoByte(Code code) // get Low Byte
	{ return code.LoByte; }

inline bool isDblByte( const Code code )
{
	int val=((getHiByte(code)&0x80) && (getLoByte(code)&0xc0))?
				1:
				((getHiByte(code)==0) && !(getLoByte(code)&0x80))?
					0:
					-1;
	if (val==-1) error("isDblByte(Code): illegal GB Code.");
	return val!=0;
}
inline bool isSglByte( const Code code )
{
	int val=((getHiByte(code)&0x80) && (getLoByte(code)&0xc0))?
				0:
				((getHiByte(code)==0) && !(getLoByte(code)&0x80))?
					1:
					-1;
	if (val==-1) error("isSglByte(Code): illegal GB Code.");
	return val!=0;
}

inline unsigned int getValue(const char * pntr)
{
	return isSglByte(pntr)?getNrByte(pntr):(getNrByte(pntr)<<8)+getFrByte(pntr);
}
inline unsigned int getValue(const Code code)
{
	return isSglByte(code)?getLoByte(code):(getHiByte(code)<<8)+getLoByte(code);
}

inline bool isEqual(const char *pntr1,const char *pntr2)
{
	return  (getNrByte(pntr1)!=getNrByte(pntr2))?false:
			isSglByte(pntr1)?true:getFrByte(pntr1)==getFrByte(pntr2);
}
inline bool isEqual(const char *pntr,const Code code)
{
	return  (isSglByte(pntr))?(getNrByte(pntr)==getLoByte(code)):
		(getNrByte(pntr)==getHiByte(code))&&(getFrByte(pntr)==getLoByte(code));
}
inline Code getCode(const char *pntr)
{
	Code code;
	if (isSglByte(pntr)) { code.HiByte=0; code.LoByte=getNrByte(pntr); }
	else { code.HiByte=getNrByte(pntr); code.LoByte=getFrByte(pntr); }
	return code;
}
inline Code getCodeNext(const char *&pntr)
{
	Code code;
	if (isSglByte(pntr)) { code.HiByte=0; code.LoByte=getNrByte(pntr); pntr++; }
	else { code.HiByte=getNrByte(pntr); code.LoByte=getFrByte(pntr); pntr++; pntr++; }
	return code;
}
inline int setChar(char *pntr1,const char *pntr2)
{
	if(isDblByte(pntr2)) { *pntr1=*pntr2; *(pntr1+1)=*(pntr2+1); return 2; }
	else { *pntr1=*pntr2; return 1; }
}
inline void setCharNext(char *&pntr1,const char *&pntr2)
{
	if(isDblByte(pntr2)) { *pntr1++=*pntr2++; *pntr1++=*pntr2++; }
	else { *pntr1++=*pntr2++; }
}
inline int setChar(char *pntr, const Code code)
{
	if(isSglByte(code)) { *pntr=(char)getLoByte(code); return 1; }
	else{ *pntr++=(char)getHiByte(code); *pntr=(char)getLoByte(code); return 2; }
}
inline void setCharNext(char *&pntr, const Code code)
{
	if(isSglByte(code)) { *pntr++=(char)getLoByte(code); }
	else { *pntr++=(char)getHiByte(code); *pntr++=(char)getLoByte(code); }
}

inline int getQu( const char * pntr ) { return (getNrByte(pntr)&0x7f)-32; }
inline int getWei( const char *pntr ){ return (getFrByte(pntr)&0x7f)-32;}

inline int getQu( const Code code ) { return (getHiByte(code)&0x7f)-32; }
inline int getWei( const Code code ){ return (getLoByte(code)&0x7f)-32;}

inline bool isChnChar( const char *pntr )
{
	return  (isDblByte(pntr) && getQu(pntr)>=16 && getQu(pntr)<=94) ||
			(getNrByte(pntr)==0xA1 && getFrByte(pntr)==0xF0); /* 汉字“○”*/
}
inline bool isLtnChar( const char *pntr )
{
	if(isSglByte(pntr)) return isalpha(getNrByte(pntr))!=0;
	else return(getQu(pntr)==3 && isalpha(getFrByte(pntr)&0x7F));
}
//	inline bool isRsnChar( const char * );
//	inline bool isJpnChar( const char * );
//	inline bool isGrkChar( const char * );
inline bool isPctChar( const char * pntr )
{
	if(isSglByte(pntr)) return ispunct(getNrByte(pntr))!=0;
	else return ( (getQu(pntr)==3 && ispunct(getFrByte(pntr)&0x7F)) ||
				  (getQu(pntr)==1));
}
inline bool isDgtChar( const char * pntr )
{
	if(isSglByte(pntr)) return isdigit(getNrByte(pntr))!=0;
	else return(getQu(pntr)==3 && isdigit(getFrByte(pntr)&0x7F));
}
inline bool isSpcChar( const char * pntr )
{
	if(isSglByte(pntr)) return isspace(getNrByte(pntr))!=0;
	else return(getQu(pntr)==3 && isspace(getFrByte(pntr)&0x7F) ||
				getNrByte(pntr)==0xA1 && getFrByte(pntr)==0xA1); /* 内码A1A1也是全角空格 */
}

inline bool isChnChar( const Code code )
{
	return  (isDblByte(code) && getQu(code)>=16 && getWei(code)<=94) ||
			(getHiByte(code)==0xA1 && getLoByte(code)==0xF0); /* 汉字“○”*/
}
inline bool isLtnChar( const Code code )
{
	if(isSglByte(code)) return isalpha(getLoByte(code))!=0;
	else return(getQu(code)==3 && isalpha(getLoByte(code)&0x7F));
}

//	inline bool isRsnChar( const Code );
//	inline bool isJpnChar( const Code );
//	inline bool isGrkChar( const Code );

inline bool isPctChar( const Code  code )
{
	if(isSglByte(code)) return ispunct(getLoByte(code))!=0;
	else return ( (getQu(code)==3 && ispunct(getLoByte(code)&0x7F)) ||
				  (getQu(code)==1));
}
inline bool isDgtChar( const Code  code )
{
	if(isSglByte(code)) return isdigit(getLoByte(code))!=0;
	else return(getQu(code)==3 && isdigit(getLoByte(code)&0x7F));
}
inline bool isSpcChar( const Code  code )
{
	if(isSglByte(code)) return isspace(getLoByte(code))!=0;
	else return(getQu(code)==3 && isspace(getLoByte(code)&0x7F) ||
				getHiByte(code)==0xA1 && getLoByte(code)==0xA1); /* 内码A1A1也是全角空格 */
}

inline const char * goNext ( const char *& pntr )
{
	if(isDblByte(pntr)) { pntr++; pntr++; }
	else pntr++;
	return pntr;
}

inline const char * getNext ( const char * pntr )
{
	if(isDblByte(pntr)) { pntr++; pntr++; }
	else pntr++;
	return pntr;
}
	
#endif

