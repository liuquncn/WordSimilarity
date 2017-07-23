/* Constant.h */

#ifndef CONSTANT_H
#define CONSTANT_H

const int LANGNUM=5;
enum LangCode
{
		CHINESE,
		ENGLISH,
		MONGOLIAN,
		TIBETAN,
		JAPANESE,
		SEMANTIC=-1
};

const char * const LANGSTRING[] =
{
	"CHINESE",
	"ENGLISH",
	"MONGOLIAN",
	"TIBETAN",
	"JAPANESE"
};

const int FILENAMELENGTH=120;
const int COMMANDLENGTH=250;
const int WORDLENGTH=32;
const int TEXTLENGTH=1024;
const int SENTLENGTH=1024;
const int LINELENGTH=1024;
const int TREELENGTH=32*SENTLENGTH;

const int WRONG=-1;
/*
const bool SUCC=true;
const bool FAIL=false;

const bool YES=true;
const bool NO=false;

#ifndef TRUE
const bool TRUE=true;
const bool FALSE=false;
#endif//TRUE
*/
#endif // CONSTANT_H