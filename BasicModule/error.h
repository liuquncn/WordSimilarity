
#ifndef ERROR_H

#define ERROR_H

#include "constant.h"
#include "function.h"
#include <string.h>

class CErrorException {
protected:
	char m_Message[512];
public:
	const char * getMessage() { return m_Message; }
	void setMessage(const char * msg) { strcpyn(m_Message,msg,512); }
};

void error(const char * msg1=NULL,
		   const char * msg2=NULL, const char * msg3=NULL);

#endif