
#pragma warning(disable : 4786)
#include <fstream>
using namespace std;
#include "function.h"

namespace trace
{
	extern fstream tracefile;
	extern fstream logfile;

	extern bool traceflag;
	extern bool trace_time_flag;
	extern bool trace_memory_flag;
	extern bool logflag;

	namespace trace_time
	{
		long gettime();
	}

	namespace trace_memory
	{ 
		extern int newnumber;
		extern int delnumber;
		extern int memrecord[1000000];
		void setrecord(int index,bool value);
		bool getrecord(int index);
		void * mynew(size_t n);
		void mydelete(void * p);
		void mymemory();
	}
}

