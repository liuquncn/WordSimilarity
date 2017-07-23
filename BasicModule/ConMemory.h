#ifndef CONMEMORY_H
#define CONMEMORY_H
#include <string.h>

// memory management for class constring
class conmemory
{
public:

	conmemory();
	~conmemory();

	int ii;
	struct base_hash_elem
	{
		char *p;
		unsigned int length;
		base_hash_elem():p(NULL),length(0){}
	};


	int AllocateMem(const char *q);
	int GetHashIndex(const char *q,bool &repeat);
	int FindNearestPrime(int n);
	bool Regeneration();                //enlarge the memory to 2 times as the old
	unsigned int Length(int n)
	{
		return (n<index_size&&n>=0)?pindex[n].length:0;
	}
	char* Pointer(int n)
	{
		return (n<index_size&&n>=0)?pindex[n].p:0;
	}
	//for debug, display the memory and the index;
	void dispm();              //display memory
	void dispi();				//display index

	int index_size;
private:
	char *pMemory;
	base_hash_elem *pindex;
	int max_allocation_mem;
//	int index_size;
	int iAllocPos;        //the position where it is the first unallocated block	
};

#endif