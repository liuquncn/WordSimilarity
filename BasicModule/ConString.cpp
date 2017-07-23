#include "ConString.h"
#include "string.h"
conmemory constring::g_mem;
constring operator+(constring &t,const char *s)
{
	int length=t.g_mem.Length(t.GetMi());
	char *p=new char[length+strlen(s)+1];
	memcpy(p,t.g_mem.Pointer(t.GetMi()),length);
	memcpy(&p[length],s,strlen(s)+1);
	constring temp(p);
	delete p;
	return temp;
}

constring operator+(constring &t,constring &x)
{
	return operator+(t,x.g_mem.Pointer(x.GetMi()));
}

constring operator+(constring &t,const char c)
{
	char v[2];
	v[0]=c;
	v[1]='\0';
	return operator+(t,v);
}
constring operator+(const char *s,constring &t)
{
	int length=t.g_mem.Length(t.GetMi());
	char *p=new char[length+strlen(s)+1];
	memcpy(p,s,strlen(s));
	memcpy(&p[strlen(s)],t.g_mem.Pointer(t.GetMi()),length+1);
	constring temp(p);
	delete p;
	return temp;
}
constring operator+(const char c,constring &t)
{
	char v[2];
	v[0]=c;
	v[1]='\0';
	return operator+(t,v);
}
bool operator!=(constring &t,char* s)
{
	return strcmp(t.g_mem.Pointer(t.GetMi()),s)!=0;
}
bool operator!=(char* s,constring &t)
{
	return strcmp(t.g_mem.Pointer(t.GetMi()),s)!=0;
}
bool operator!=(constring &s,constring &t)
{
	return s.GetMi()!=t.GetMi();
}
bool operator==(constring &t,char *s)
{
	return strcmp(t.g_mem.Pointer(t.GetMi()),s)==0;
}
bool operator==(constring &t,constring &s)
{
	return t.GetMi()==s.GetMi();
}
bool operator==(char *s,constring &t)
{
	return strcmp(t.g_mem.Pointer(t.GetMi()),s)==0;
}
bool operator<(const constring &t,const constring &s)
{
	if (t.GetMi()==s.GetMi()) return false;
	else return strcmp(constring::g_mem.Pointer(t.GetMi()),constring::g_mem.Pointer(s.GetMi()))<0;
}
bool operator>=(const constring &t,const constring &s)
{
	return (!(t < s));
}
bool operator>(const constring &t,const constring &s)
{
	if(t.GetMi()==s.GetMi()) return false;
	else return strcmp(constring::g_mem.Pointer(t.GetMi()),constring::g_mem.Pointer(s.GetMi()))>0;
}
bool operator<=(const constring &t,const constring &s)
{
	return (!(t>s));
}