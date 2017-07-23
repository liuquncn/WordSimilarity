#ifndef CONSTRING_H
#define CONSTRING_H
#include "assert.h"
#include "ConMemory.h"
class constring
{
public:
	static conmemory g_mem;
	typedef const char* iterator;
	constring(const char *s)
	{
		if (s==NULL) m_nMemoryIndex=g_mem.AllocateMem("");
		else m_nMemoryIndex=g_mem.AllocateMem(s);
	}
	constring()
	{
		m_nMemoryIndex=g_mem.AllocateMem("");
	}
	constring(const constring &t)
	{
		m_nMemoryIndex=t.GetMi();
	}
	constring(const constring& t,unsigned int _P , unsigned int _M )
	{
		if(_P>g_mem.Length(t.GetMi()))
		{
			m_nMemoryIndex=t.GetMi();
		}else
		{
			unsigned int _N=g_mem.Length(t.GetMi())-_P;
			if(_N<_M)
				_M=_N;
			char *q=new char[_M+1];
			memcpy(q,&g_mem.Pointer(t.GetMi())[_P],_M);
			q[_M]='\0';
			m_nMemoryIndex=g_mem.AllocateMem(q);
			delete q;
		}
	}


	constring& operator=(const constring& x)
	{
		m_nMemoryIndex=x.m_nMemoryIndex;
		return *this;
	}
	constring& operator=(const char *s)
	{
		if (s==NULL) m_nMemoryIndex=g_mem.AllocateMem("");
		else m_nMemoryIndex=g_mem.AllocateMem(s);
		return *this;
	}
	constring& operator=(const char c)
	{
		char p[2];
		p[0]=c;
		p[1]='\0';
		m_nMemoryIndex=g_mem.AllocateMem(p);
		return *this;
	}
	constring& operator+=(const constring& x)
	{
		return append(x);
	}
	constring& operator+=(const char *s)
	{
		return append(s);
	}
	constring& operator+=(const char c)
	{
		return append(c);
	}




	constring& append(const constring& x)
	{
		append(g_mem.Pointer(x.GetMi()));
		return *this;
	}
	constring& append(const char *s)
	{
		int length=g_mem.Length(m_nMemoryIndex);
		char *p=new char[length+strlen(s)+1];
		memcpy(p,g_mem.Pointer(m_nMemoryIndex),length);
		memcpy(&p[length],s,strlen(s)+1);
		m_nMemoryIndex=g_mem.AllocateMem(p);
		delete p;
		return *this;
	}
	constring& append(const char c)
	{
		char t[2];
		t[0]=c;
		t[1]='\0';
		append(t);
		return *this;
	}





	constring& insert(unsigned int p,constring& x)
	{
		insert(p,g_mem.Pointer(x.m_nMemoryIndex));
		return *this;
	}
	constring& insert(unsigned int p,const char *s)
	{
		assert(p<=g_mem.Length(m_nMemoryIndex));
		if(p>g_mem.Length(m_nMemoryIndex))
			return *this;
		int len1=g_mem.Length(m_nMemoryIndex);
		int len2=strlen(s);
		char *q=new char[len1+len2+1];
		memcpy(q,g_mem.Pointer(m_nMemoryIndex),p);
		memcpy(&q[p],s,len2);
		memcpy(&q[p+len2],&g_mem.Pointer(m_nMemoryIndex)[p],len1-p+1);
		m_nMemoryIndex=g_mem.AllocateMem(q);
		delete q;
		return *this;
	}
	constring& insert(unsigned int p,const char c)
	{
		char t[2];
		t[0]=c;
		t[1]='\0';
		insert(p,t);
		return *this;
	}
	iterator insert(iterator _P, char _C)
	{
		unsigned int _P0 = _Pdif(_P, begin());
		insert(_P0, _C);
		return (begin() + _P0); 
	}




	constring& replace(unsigned int p,unsigned int n,const char *q)
	{
		return replace(p,n,q,strlen(q));
	}
	constring& replace(unsigned int p,unsigned int n,const char *q,unsigned int size)
	{
		assert(p>=0&&p<=g_mem.Length(m_nMemoryIndex));
		assert(size<=strlen(q));
		unsigned int len=g_mem.Length(m_nMemoryIndex);
		char *t=g_mem.Pointer(m_nMemoryIndex);
		if(p>len)
			return *this;
		if(p==len)
			return append(q);
//		if(strlen(q)<size)
//			size=strlen(q);
		if(p+n>len)
			n=len-p;
		char *r=new char[len+size-n+1];
		memcpy(r,t,p);
		memcpy(&r[p],q,size);
		memcpy(&r[p+size],&t[p+n],len-p-n+1);
		m_nMemoryIndex=g_mem.AllocateMem(r);
		delete r;
		return *this;
	}
	constring& replace(unsigned int p,unsigned int n,constring &t)
	{
		return replace(p,n,g_mem.Pointer(t.GetMi()),g_mem.Length(t.GetMi()));
	}
	constring& replace(unsigned int p,unsigned int n,constring &t,int size)
	{
		return replace(p,n,g_mem.Pointer(t.GetMi()),size);
	}
	constring& replace(iterator _F, iterator _L, const constring& _X)
	{
		return (replace(_Pdif(_F, begin()), _Pdif(_L, _F), g_mem.Pointer(_X.m_nMemoryIndex))); 
	}
	constring& replace(iterator _F, iterator _L, const char *_S,unsigned int _M)
	{
		return (replace(_Pdif(_F, begin()), _Pdif(_L, _F), _S, _M)); 
	}
	constring& replace(iterator _F, iterator _L, const char *_S)
	{
		return (replace(_Pdif(_F, begin()), _Pdif(_L, _F), _S)); 
	}






	int find(const char c, unsigned int pos = 0) const
	{
		return find(&c,pos,1);
	}
	int find(const char *s, unsigned int pos = 0) const
	{
		return find(s,pos,strlen(s));
	}

	int find(const char *s, unsigned int pos, unsigned int n=0) const
	{
		assert(s!=NULL);
		assert(pos<=g_mem.Length(m_nMemoryIndex));
		assert(pos<g_mem.Length(m_nMemoryIndex));
		if(n==0&&pos<=g_mem.Length(m_nMemoryIndex))
		{
			return pos;
		}
		if(pos>=g_mem.Length(m_nMemoryIndex)||!s)
			return -1;
		unsigned int _Nm;
		if(pos>=g_mem.Length(m_nMemoryIndex)||n>(_Nm=g_mem.Length(m_nMemoryIndex)-pos))
			return -1;
		const char *_U,*_V;
		for(_Nm-=n-1,_V=g_mem.Pointer(m_nMemoryIndex)+pos;(_U=sfind(_V,_Nm,*s))!=0;
			_Nm-=_U-_V+1,_V=_U+1)
				if(scompare(_U,s,n)==0)
					return(_U-g_mem.Pointer(m_nMemoryIndex));
		return -1;
/*		char *q=g_mem.Pointer(m_nMemoryIndex);
		unsigned int i,j,k;
		for(i=pos;i<=g_mem.Length(m_nMemoryIndex)-n;i++)
		{
			k=i;
			for(j=0;j<=n-1;j++)
			{
				if(q[k++]!=s[j])
					break;
			}
			if(j>n-1)
				break;
		}
		if(i<=g_mem.Length(m_nMemoryIndex)-n)
			return i;
		else return -1;
*/
	}
	int find(constring& str, unsigned int pos = 0) const//???find(const constring& str,int pos=0)
	{
		return find(str.c_str(),pos,strlen(str.c_str()));
	}

    static int __cdecl scompare(const char *_U, const char *_V, unsigned int _N)
    {
		for (size_t _I = 0; _I < _N; ++_I, ++_U, ++_V)
                        if (!(*_U==*_V))
                                return ((*_U<*_V) ? -1 : +1);
                return (0); 
	}
    static const char * __cdecl sfind(const char *_U, unsigned int _N,const char& _C)
    {
		for (; 0 < _N; --_N, ++_U)
                   if ((*_U==_C))
                         return (_U);
        return (0); 
	}


	iterator begin()
	{
		return g_mem.Pointer(m_nMemoryIndex);
	}
	iterator end()
	{
		return &g_mem.Pointer(m_nMemoryIndex)[g_mem.Length(m_nMemoryIndex)];
	}


	constring& erase(unsigned int _P0 = 0, unsigned int _M = 0)
	{
		assert(_P0<=g_mem.Length(m_nMemoryIndex));
		if(_P0>=g_mem.Length(m_nMemoryIndex)||_M==0)
			return *this;
		if(_P0+_M>g_mem.Length(m_nMemoryIndex))
			_M=g_mem.Length(m_nMemoryIndex)-_P0;
		char *q=new char [g_mem.Length(m_nMemoryIndex)+1];
		memcpy(q,g_mem.Pointer(m_nMemoryIndex),_P0);
		memcpy(&q[_P0],&g_mem.Pointer(m_nMemoryIndex)[_P0+_M],g_mem.Length(m_nMemoryIndex)-_M-_P0+1);
//		if(strlen(q)==0)
//				m_nMemoryIndex=0;
//			else
//				m_nMemoryIndex=g_mem.AllocateMem(q);
		m_nMemoryIndex=g_mem.AllocateMem(q);
		delete q;
		return *this;
	}
	iterator erase(iterator _P)
	{
		int _M = _Pdif(_P, begin());
		erase(_M, 1);
		return (_Psum(g_mem.Pointer(m_nMemoryIndex), _M));
	}
	iterator erase(iterator _F, iterator _L)
	{
		int _M = _Pdif(_F, begin());
		erase(_M, _Pdif(_L, _F));
		return (_Psum(g_mem.Pointer(m_nMemoryIndex), _M)); 
	}


	static int _Pdif(iterator _P2, iterator _P1)
		{return (_P2 == 0 ? 0 : _P2 - _P1); }

	static iterator _Psum(iterator _P, int _N)
		{return (_P == 0 ? 0 : _P + _N); }

	static char* _Psum(char* _P, int _N)
		{return (_P == 0 ? 0 : _P + _N); }	

	const char& at(unsigned int _P0)
	{
		if ( g_mem.Length(m_nMemoryIndex)< _P0)
			_P0=g_mem.Length(m_nMemoryIndex);
		return (g_mem.Pointer(m_nMemoryIndex)[_P0]); 
	}
	const char& operator[](unsigned int _P0)
	{
		if (_P0>g_mem.Length(m_nMemoryIndex))
			_P0=g_mem.Length(m_nMemoryIndex);
		return (g_mem.Pointer(m_nMemoryIndex)[_P0]); 
	}


	int length() const
	{
		assert(m_nMemoryIndex>=0&&m_nMemoryIndex<g_mem.index_size);
		return g_mem.Length(m_nMemoryIndex);
	}
	bool empty() const
	{
		assert(m_nMemoryIndex>=0&&m_nMemoryIndex<g_mem.index_size);
		return (*g_mem.Pointer(m_nMemoryIndex))==0;
	}
	
	static const char * __cdecl _Nullstr()
	{
		static const char _C = char(0);
		return (&_C); 
	}

	const char *c_str() const
	{
		assert(m_nMemoryIndex>=0&&m_nMemoryIndex<g_mem.index_size);	
		return g_mem.Pointer(m_nMemoryIndex);
	}
	const int GetMi() const
	{
		return m_nMemoryIndex;
	}

	constring substr(unsigned int _P = 0, unsigned int _M = -1)
	{
		return (constring(*this, _P, _M)); 
	}

	const char *data() const
	{
		return (c_str()); 
	}
private:	
	int m_nMemoryIndex;
};

constring operator+(constring &t,const char *s);
constring operator+(constring &t,constring &x);
constring operator+(constring &t,const char c);
constring operator+(const char *s,constring &t);
constring operator+(const char c,constring &t);
bool operator!=(constring &t,char* s);
bool operator!=(char* s,constring &t);
bool operator!=(constring &s,constring &t);
bool operator==(constring &t,char *s);
bool operator==(constring &t,constring &s);
bool operator==(char *s,constring &t);
bool operator<(const constring &t,const constring &s);
bool operator>=(const constring &t,const constring &s);
bool operator>(const constring &t,const constring &s);
bool operator<=(const constring &t,const constring &s);


#endif