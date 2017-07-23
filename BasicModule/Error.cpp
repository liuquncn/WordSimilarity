#include "error.h"

void error(const char * msg1, const char * msg2, const char * msg3)
{
	message(msg1,msg2,msg3);
	
	static CErrorException errorException;
	errorException.setMessage(msg1);
	throw &errorException;
}
