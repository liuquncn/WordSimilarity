
#ifndef HOWNET_H
#define HOWNET_H

#pragma warning(disable : 4786)

#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;
#include "..\\BasicModule\\code.h"

class Sememe
{
	string Chinese;
	string English;
	int IDparent;
public:
	bool read(int id,fstream & file);
	const string & getChinese() const { return Chinese; }
	const string & getEnglish() const { return English; }
	int getIDparent() const { return IDparent; }
	friend class Hownet;
};

class Meaning
{
	string POS;
	string DEF;
public:
	Meaning() { POS=DEF=""; }
	string read(fstream & file);
	const string & getPOS() const { return POS; }
	const string & getDEF() const { return DEF; }
	bool operator == (const Meaning & mn) const { return POS==mn.POS && DEF==mn.DEF; }
	bool operator < (const Meaning & mn) const { return POS<mn.POS || DEF<mn.DEF; }
	friend class Hownet;
};

struct SememeWord
{
	int Sememe;
	string Word;
	SememeWord() { Sememe=0; Word=""; }
	SememeWord(int s,const const char * w) { Sememe=s; Word=w; }
	bool operator == (const SememeWord & sw) const { return Sememe==sw.Sememe && Word==sw.Word; }
	bool operator < (const SememeWord & sw) const { return Sememe<sw.Sememe || Word<sw.Word; }
};

class MeaningDEF
{
	bool Function;
	int PrimarySememe;
	set<SememeWord> SecondSememeSet;
	map<int,SememeWord> SememeRelationSet;
	multimap<char,SememeWord> SymbolRelationSet;
	friend class Hownet;
};

class Hownet
{
	vector<Sememe> SememeSet;
	multimap<string,Meaning> MeaningMap;
	map<string,int> SememeIndex;
public:
	Hownet();
	~Hownet();
	int getSememeID(const char * sem) const
	{
		int id;
		if (isDgtChar(sem))
		{
			id=atoi(sem);
			if (id>=SememeSet.size()) id=-1;
		}
		else
		{
			map<string,int>::const_iterator iter=SememeIndex.find(sem);
			if (iter==SememeIndex.end()) id=-1;
			else id=iter->second;
		}
		return id;
	}
	const Sememe getSememe(int id) const
	{
		if (id>=SememeSet.size()) return Sememe();
		else return SememeSet[id];
	}
	const Sememe getSememe(const char * sem) const
	{
		return getSememe(getSememeID(sem));
	}
	bool getMeaningIter(string & word, multimap<string,Meaning>::const_iterator & iter) const;
	const Meaning & getMeaningNext(string & word, multimap<string,Meaning>::const_iterator & iter) const;
	int getSememeDistance(int id1,int id2) const;
	float getSememeSimilarity(int id1,int id2) const;
	float getSememeSetSimilarity(const set<int> & ss1,const set<int> & ss2) const;
	float getMeaningSetSimilarity(const set<Meaning> & ss1,const set<Meaning> & ss2) const;
	float getSememeWordSetSimilarity(const set<SememeWord> & ss1,const set<SememeWord> & ss2) const;
	float getSememeRelationSetSimilarity(const map<int,SememeWord> & semrs1,const map<int,SememeWord> & semrs2) const;
	float getSymbolRelationSetSimilarity(const multimap<char,SememeWord> & symrs1,const multimap<char,SememeWord> & symrs2) const;
	float getSememeWordSimilarity(const SememeWord & sw1, const SememeWord & sw2) const;
	float getMeaningSimilarity(const Meaning & mn1, const Meaning & mn2) const;
	float getWordSimilarity(const char * word1, const char * word2) const;
	void readMeaning(Meaning & meaning, const char * posdef) const;
	void readMeaningDEF(MeaningDEF & meaningdef, const char * def) const;

	static float alpha;
	static float beta1;
	static float beta2;
	static float beta3;
	static float beta4;
	static float gama;
	static float delta;
};

#endif//HOWNET_H
