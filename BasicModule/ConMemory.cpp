#include "assert.h"
#include "process.h"
#include "ConMemory.h"
#include "iostream.h"
#include "fstream.h"

conmemory::conmemory()
{
	max_allocation_mem=1000000;
	index_size=FindNearestPrime(2*max_allocation_mem);
//	max_allocation_mem=1000;
//	index_size=_FindNearestPrime(500);
	pMemory=new char[max_allocation_mem];
	pindex=new base_hash_elem[index_size];
	iAllocPos=0;
//	pMemory[0]='\0';
//	pindex[0].p=pMemory;
//	pindex[0].length=0;
}

conmemory::~conmemory()
{
	
	delete pMemory;
	delete pindex;
}

int conmemory::AllocateMem(const char *q)
{
	bool repeat;
	int n,length;
	length=strlen(q);
	if(iAllocPos+length+1>max_allocation_mem)
	{
		cout<<"out of";
		//out of bounderies
		if(!Regeneration())
			return 0;
	}
	n=GetHashIndex(q,repeat);
	if(!repeat)
	{
		pindex[n].length=length;
		pindex[n].p=&pMemory[iAllocPos];
		memcpy(pindex[n].p,q,length+1);
		iAllocPos+=length+1;
	}

	return n;
}

int conmemory::GetHashIndex(const char *q,bool &repeat)
{
//	static int i=0;
//	return ++i;
	repeat=false;
	unsigned int hash_val=0;
	const char *i=q;
	while(*i)
	{
		hash_val=hash_val*257+(*i);
		hash_val%=index_size;
		i++;
	}
	unsigned int orin=hash_val;
	while(pindex[hash_val].p!=NULL&&strcmp(q,pindex[hash_val].p)!=0)
	{
		hash_val+=3;
		hash_val%=index_size;
		if(hash_val==orin)
		{
			cout<<"Severe Errors,hash table has overflowed!Programme terminated"<<endl;
			exit(0);
		}
	}
	if(pindex[hash_val].p!=NULL)
		repeat=true;
	return hash_val;
}

int conmemory::FindNearestPrime(int num)
{
	int div;
	int num_has_divisor = 1;
	if ( num / 2 * 2 == num ) num++; 
	for (; num_has_divisor; num += 2 ) 
	{
		num_has_divisor=0;
		for ( div = 3; div <= num / 3; div++ ) 
		{
			if ( ( num / div) * div == num ) 
			{
				num_has_divisor = 1;
				break;
			}
		}
	}
	num -= 2;
	return( num );
}

bool conmemory::Regeneration()
{
	int m=max_allocation_mem*2;

	char *p=new char[m];
	assert(p);
	if(!p)
		return false;
	memcpy(p,pMemory,iAllocPos);
	for(int i=0;i<index_size;i++)
	{
		if(pindex[i].p!=NULL)
		{
			pindex[i].p+=p-pMemory;
		}
	}
	delete pMemory;
	pMemory=p;
	max_allocation_mem=m;
	return true;
}


void conmemory::dispm()
{
/*
	for(int i=0;i<max_allocation_mem;i++)
	{
		if(pMemory[i]!='\0')
			cout<<pMemory[i];
		else
			cout<<'X';
	}
	cout<<endl;
*/
	int kk=0;
	fstream o("conmemory.txt",ios::out);
	for(int i=0;i<max_allocation_mem;i++)
	{
		if(pMemory[i]!='\0')
			o<<pMemory[i];
		else
		{
			o<<'X';
			kk++;
		}
	}
	o<<endl;
	o<<kk;


}

void conmemory::dispi()
{
	int kk=0;
	fstream oo("index.txt",ios::out);
	for(int i=0;i<index_size;i++)
	{
		if(pindex[i].p!=NULL)
		{
			oo<<pindex[i].p<<"|";
			kk++;
		}
	}
	oo<<endl;
	oo<<kk;
}
