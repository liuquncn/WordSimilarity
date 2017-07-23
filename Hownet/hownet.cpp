
#include "hownet.h"

#include <fstream>
#include <list>
using namespace std;

#include "..\\BasicModule\\error.h"
#include "..\\BasicModule\\code.h"
#include "..\\BasicModule\\token.h"

bool Sememe::read(int id,fstream & file)
{
	char line[1024];
	file.getline(line,1023);

	char * p0, *p1=p0=line;
//	while (*p1 && isSpcChar(p1)) goNext(p1);  // 跳过空格
//	while (*p1 && !isSpcChar(p1)) goNext(p1); // 跳过非空格
	while (*p1 && isSpcChar(p1)) goNext(p1);  // 跳过空格
	p0=p1;
	if (*p0==0) return false;
	while (*p1 && !isSpcChar(p1)) goNext(p1); // 跳过非空格
	if (isSglByte(p1)) *p1++=0;
	else { *p1++=0; *p1++=0; }
	if (id!=atoi(p0))
		error("Sememe::read(): id mismatch.",p0);

	while (*p1 && isSpcChar(p1)) goNext(p1); // 跳过空格
	p0=p1;
	while (*p1 && *p1!='|') goNext(p1); // 走到竖杠
	*p1++=0;
	English=p0;

	p0=p1;
	while (*p1 && !isSpcChar(p1)) goNext(p1); // 跳过非空格
	if (isSglByte(p1)) *p1++=0;
	else { *p1++=0; *p1++=0; }
	Chinese=p0;

	while (*p1 && isSpcChar(p1)) goNext(p1); // 跳过空格
	p0=p1;
	while (*p1 && !isSpcChar(p1)) goNext(p1); // 跳过非空格
	if (isSglByte(p1)) *p1++=0;
	else { *p1++=0; *p1++=0; }
	IDparent=atoi(p0);
	return true;
}

string Meaning::read(fstream & file)
{
	char line[1024];
	file.getline(line,1023);

	string word;

	char * p0, * p1=p0=line;
	while (*p1 && !isSpcChar(p1)) goNext(p1); // 跳过非空格
	if (isSglByte(p1)) *p1++=0;
	else { *p1++=0; *p1++=0; }
	if (*p0==0) return word;
	word=p0;

	while (*p1 && isSpcChar(p1)) goNext(p1);  // 跳过空格
	p0=p1;
	while (*p1 && !isSpcChar(p1)) goNext(p1); // 跳过非空格
	if (isSglByte(p1)) *p1++=0;
	else { *p1++=0; *p1++=0; }
	POS=p0;

	while (*p1 && isSpcChar(p1)) goNext(p1);  // 跳过空格
	p0=p1;
	while (*p1 && !isSpcChar(p1)) goNext(p1); // 跳过非空格
	if (isSglByte(p1)) *p1++=0;
	else { *p1++=0; *p1++=0; }
	DEF=p0;
	return word;
}

float Hownet::alpha=1.6f;
float Hownet::beta1=0.5f;
float Hownet::beta2=0.2f;
float Hownet::beta3=0.17f;
float Hownet::beta4=0.13f;
float Hownet::gama=0.2f;
float Hownet::delta=0.2f;

Hownet::Hownet()
{
	fstream sememefile;
	sememefile.open("whole.dat",ios::in|ios::binary);
	if (!sememefile)
		error("Hownet::Hownet(): sememefile cannot open.","whole.dat");
	Sememe sememe;
	int id=0;
	while (!sememefile.eof())
	{
		if (sememe.read(id,sememefile)==false) break;
		SememeSet.push_back(sememe);
		SememeIndex.insert(pair<string,int>(sememe.Chinese,id));
		SememeIndex.insert(pair<string,int>(sememe.English,id));
		id++;
	}
	sememefile.close();

	fstream vocabularyfile;
	vocabularyfile.open("glossary.dat",ios::in|ios::binary);
	if (!vocabularyfile)
		error("Hownet::Hownet(): vocabularyfile cannot open.","glossary.dat");
	Meaning meaning;
	while (!vocabularyfile.eof())
	{
		string word;
		word=meaning.read(vocabularyfile);
		if (word.empty()) break;
		MeaningMap.insert(pair<string,Meaning>(word,meaning));
	}
	vocabularyfile.close();
}

Hownet::~Hownet()
{
}

bool Hownet::getMeaningIter(string & word, multimap<string,Meaning>::const_iterator & iter) const
{
	iter=MeaningMap.find(word);
	return iter!=MeaningMap.end();
}

const Meaning & Hownet::getMeaningNext(string & word, multimap<string,Meaning>::const_iterator & iter) const
{
	static Meaning emptymeaning;
	if (iter==MeaningMap.end() || iter->first!=word) return emptymeaning;
	else return iter++->second;
}

int Hownet::getSememeDistance(int id1,int id2) const
{
	if (id1<0 || id1>=SememeSet.size())
		error("Hownet::getSememeDistance(): id1 is not a valid SememeID.");
	if (id2<0 || id2>=SememeSet.size())
		error("Hownet::getSememeDistance(): id2 is not a valid SememeID.");
	int parent1=id1,parent2=id2;
	list<int> idlist1, idlist2;
	do
	{
		idlist1.push_front(parent1);
		parent1=getSememe(parent1).getIDparent();
	} while (parent1!=*idlist1.begin());
	do
	{
		idlist2.push_front(parent2);
		parent2=getSememe(parent2).getIDparent();
	} while (parent2!=*idlist2.begin());
	list<int>::iterator iter1,iter2;
	iter1=idlist1.begin();
	iter2=idlist2.begin();
	int same=0;
	while (iter1!=idlist1.end() && iter2!=idlist2.end() && *iter1==*iter2)
	{
		same++;
		iter1++;
		iter2++;
	}
	return same==0?20:idlist1.size()+idlist2.size()-2*same;
}

float Hownet::getSememeSimilarity(int id1,int id2) const
{
	int distance=getSememeDistance(id1,id2);
	return distance==-1?0:alpha/(distance+alpha);
}

float Hownet::getSememeWordSimilarity(const SememeWord & sw1, const SememeWord & sw2) const
{
	if (sw1.Sememe==-1 && sw2.Sememe==-1)
		return sw1.Word==sw2.Word?1:0;
	else if (sw1.Sememe==-1 && sw2.Sememe!=-1 || sw1.Sememe!=-1 && sw2.Sememe==-1)
		return gama;
	else return getSememeSimilarity(sw1.Sememe,sw2.Sememe);
}

struct sememetriple
{
	int sm1;
	int sm2;
	float sim;
	bool operator == (const sememetriple & t) const { return sm1==t.sm1 && sm2==t.sm2; }
};

float Hownet::getSememeSetSimilarity(const set<int> & ss1,const set<int> & ss2) const
{
	if (ss1.size()==0 && ss2.size()==0) return 1;
	list<sememetriple> triplelist;
	set<int>::const_iterator iter1,iter2;
	for (iter1=ss1.begin();iter1!=ss1.end();iter1++)
	{
		for (iter2=ss2.begin();iter2!=ss2.end();iter2++)
		{
			sememetriple tp;
			tp.sm1=*iter1;
			tp.sm2=*iter2;
			tp.sim=getSememeSimilarity(*iter1,*iter2);
			triplelist.push_back(tp);
		}
	}
	vector<float> maxset;
	while (!triplelist.empty())
	{
		float maxsim=-1;
		sememetriple maxtriple;
		list<sememetriple>::iterator tripleiter,triplenext;
		for (tripleiter=triplelist.begin();tripleiter!=triplelist.end();tripleiter++)
		{
			if (tripleiter->sim>maxsim)
			{
				maxtriple=*tripleiter; 
				maxsim=maxtriple.sim;
			}
		}
		maxset.push_back(maxsim);
		for (tripleiter=triplelist.begin();tripleiter!=triplelist.end();tripleiter=triplenext)
		{
			triplenext=tripleiter;
			triplenext++;
			if (tripleiter->sm1==maxtriple.sm1 || tripleiter->sm2==maxtriple.sm2)
				triplelist.remove(*tripleiter);
		}
	}
	int dif=ss1.size()-ss2.size();
	if (dif<0) dif=-dif;
	float mean=0;
	vector<float>::iterator maxiter;
	for (maxiter=maxset.begin();maxiter!=maxset.end();maxiter++)
		mean+=*maxiter;
	mean+=dif*delta;
	mean/=maxset.size()+dif;
	return mean;
}

struct meaningtriple
{
	Meaning sm1;
	Meaning sm2;
	float sim;
	bool operator == (const meaningtriple & t) const { return sm1==t.sm1 && sm2==t.sm2; }
};

float Hownet::getMeaningSetSimilarity(const set<Meaning> & ss1,const set<Meaning> & ss2) const
{
	if (ss1.size()==0 && ss2.size()==0) return 1;
	list<meaningtriple> triplelist;
	set<Meaning>::const_iterator iter1,iter2;
	for (iter1=ss1.begin();iter1!=ss1.end();iter1++)
	{
		for (iter2=ss2.begin();iter2!=ss2.end();iter2++)
		{
			meaningtriple tp;
			tp.sm1=*iter1;
			tp.sm2=*iter2;
			tp.sim=getMeaningSimilarity(*iter1,*iter2);
			triplelist.push_back(tp);
		}
	}
	/*
	vector<float> maxset;
	while (!triplelist.empty())
	{
		float maxsim=-1;
		meaningtriple maxtriple;
		list<meaningtriple>::iterator tripleiter,triplenext;
		for (tripleiter=triplelist.begin();tripleiter!=triplelist.end();tripleiter++)
		{
			if (tripleiter->sim>maxsim)
			{
				maxtriple=*tripleiter; 
				maxsim=maxtriple.sim;
			}
		}
		maxset.push_back(maxsim);
		for (tripleiter=triplelist.begin();tripleiter!=triplelist.end();tripleiter=triplenext)
		{
			triplenext=tripleiter;
			triplenext++;
			if (tripleiter->sm1==maxtriple.sm1 || tripleiter->sm2==maxtriple.sm2)
				triplelist.remove(*tripleiter);
		}
	}
	int dif=ss1.size()-ss2.size();
	if (dif<0) dif=-dif;
	float mean=0;
	vector<float>::iterator maxiter;
	for (maxiter=maxset.begin();maxiter!=maxset.end();maxiter++)
		mean+=*maxiter;
	mean+=dif*delta;
	mean/=maxset.size()+dif;
	return mean;
	*/
	float maxsim=-1;
	list<meaningtriple>::iterator tripleiter,triplenext;
	for (tripleiter=triplelist.begin();tripleiter!=triplelist.end();tripleiter++)
		if (tripleiter->sim>maxsim) maxsim=tripleiter->sim;
	return maxsim;
}

struct sememewordtriple
{
	SememeWord sm1;
	SememeWord sm2;
	float sim;
	bool operator == (const sememewordtriple & t) const
	{
		return sm1==t.sm1 && sm2==t.sm2;
	}
};

float Hownet::getSememeWordSetSimilarity(const set<SememeWord> & ss1,const set<SememeWord> & ss2) const
{
	if (ss1.size()==0 && ss2.size()==0) return 1;
	list<sememewordtriple> triplelist;
	set<SememeWord>::const_iterator iter1,iter2;
	for (iter1=ss1.begin();iter1!=ss1.end();iter1++)
	{
		for (iter2=ss2.begin();iter2!=ss2.end();iter2++)
		{
			sememewordtriple tp;
			tp.sm1=*iter1;
			tp.sm2=*iter2;
			tp.sim=getSememeWordSimilarity(*iter1,*iter2);
			triplelist.push_back(tp);
		}
	}
	vector<float> maxset;
	while (!triplelist.empty())
	{
		float maxsim=-1;
		sememewordtriple maxtriple;
		list<sememewordtriple>::iterator tripleiter,triplenext;
		for (tripleiter=triplelist.begin();tripleiter!=triplelist.end();tripleiter++)
		{
			if (tripleiter->sim>maxsim)
			{
				maxtriple=*tripleiter; 
				maxsim=maxtriple.sim;
			}
		}
		maxset.push_back(maxsim);
		for (tripleiter=triplelist.begin();tripleiter!=triplelist.end();tripleiter=triplenext)
		{
			triplenext=tripleiter;
			triplenext++;
			if (tripleiter->sm1==maxtriple.sm1 || tripleiter->sm2==maxtriple.sm2)
				triplelist.remove(*tripleiter);
		}
	}
	int dif=ss1.size()-ss2.size();
	if (dif<0) dif=-dif;
	float mean=0;
	vector<float>::iterator maxiter;
	for (maxiter=maxset.begin();maxiter!=maxset.end();maxiter++)
		mean+=*maxiter;
	mean+=dif*delta;
	mean/=maxset.size()+dif;
	return mean;
}

float Hownet::getSememeRelationSetSimilarity(const map<int,SememeWord> & semrs1,const map<int,SememeWord> & semrs2) const
{
	map<int,SememeWord>::const_iterator iter1,iter2;
	iter1=semrs1.begin();
	iter2=semrs2.begin();
	float sim=1;
	while (iter1!=semrs1.end() && iter2!=semrs2.end())
	{
		if (iter1->first==iter2->first)
		{
			sim*=getSememeWordSimilarity(iter1->second,iter2->second);
			iter1++;
			iter2++;
		}
		else
		{
			sim*=delta;
			if (iter1->first > iter2->first) iter1++;
			else iter2++;
		}
	}
	if (iter1!=semrs1.end()) while (iter2!=semrs2.end()) { sim*=delta; iter2++; }
	if (iter2!=semrs2.end()) while (iter1!=semrs1.end()) { sim*=delta; iter1++; }
	return sim;
}

float Hownet::getSymbolRelationSetSimilarity(const multimap<char,SememeWord> & symrs1,const multimap<char,SememeWord> & symrs2) const
{
	multimap<char,SememeWord>::const_iterator iter1,iter2;
	iter1=symrs1.begin();
	iter2=symrs2.begin();
	float sim=1;
	while (iter1!=symrs1.end() && iter2!=symrs2.end())
	{
		if (iter1->first==iter2->first)
		{
			set<SememeWord> value1,value2;
			char symbol=iter1->first;
			while (iter1!=symrs1.end() && iter1->first==symbol)
			{
				value1.insert(iter1->second);
				iter1++;
			}
			while (iter2!=symrs2.end() && iter2->first==symbol)
			{
				value2.insert(iter2->second);
				iter2++;
			}
			sim*=getSememeWordSetSimilarity(value1,value2);
		}
		else
		{
			sim*=delta;
			if (iter1->first > iter2->first) iter1++;
			else iter2++;
		}
	}
	if (iter1!=symrs1.end()) while (iter2!=symrs2.end()) { sim*=delta; iter2++; }
	if (iter2!=symrs2.end()) while (iter1!=symrs1.end()) { sim*=delta; iter1++; }
	return sim;
}

float Hownet::getMeaningSimilarity(const Meaning & mn1, const Meaning & mn2) const
{
	MeaningDEF meaningdef1,meaningdef2;
	readMeaningDEF(meaningdef1,mn1.getDEF().data());
	readMeaningDEF(meaningdef2,mn2.getDEF().data());
	float sim1,sim2,sim3,sim4;
	sim1=getSememeSimilarity(meaningdef1.PrimarySememe,meaningdef2.PrimarySememe);
	sim2=getSememeWordSetSimilarity(meaningdef1.SecondSememeSet,meaningdef2.SecondSememeSet);
	sim3=getSememeRelationSetSimilarity(meaningdef1.SememeRelationSet,meaningdef2.SememeRelationSet);
	sim4=getSymbolRelationSetSimilarity(meaningdef1.SymbolRelationSet,meaningdef2.SymbolRelationSet);
	sim2*=sim1;
	sim3*=sim2;
	sim4*=sim3;
	return beta1*sim1+beta2*sim2+beta3*sim3+beta4*sim4;
}

float Hownet::getWordSimilarity(const char * word1, const char * word2) const
{
	multimap<string,Meaning>::const_iterator iter1,iter2;
	set<Meaning> meaningset1,meaningset2;
	if (getMeaningIter(string(word1),iter1)==false)
	{
		message("Hownet::getWordSimilarity(): word not found.",word1);
		return 0;
	}
	else
	{
		Meaning meaning;
		while (true)
		{
			meaning=getMeaningNext(string(word1),iter1);
			if (meaning.getPOS().empty()) break;
			meaningset1.insert(meaning);
		}
	}
	if (getMeaningIter(string(word2),iter2)==false)
	{
		message("Hownet::getWordSimilarity(): word not found.",word2);
		return 0;
	}
	else
	{
		Meaning meaning;
		while (true)
		{
			meaning=getMeaningNext(string(word2),iter2);
			if (meaning.getPOS().empty()) break;
			meaningset2.insert(meaning);
		}
	}
	return getMeaningSetSimilarity(meaningset1,meaningset2);
}

void Hownet::readMeaning(Meaning & meaning, const char * posdef) const
{
	if (posdef==0 || *posdef==0)
	{
		meaning.DEF=meaning.POS="";
	}
	else
	{
		char newposdef[1000];
		strcpy(newposdef,posdef);
		char * p=newposdef;
		while (*p && *p!=' ') p++;
		if (*p!=0) *p++=0;
		meaning.DEF=p;
		meaning.POS=newposdef;
	}
}

void Hownet::readMeaningDEF(MeaningDEF & mndef, const char * def) const
{
	IToken token(def);
	token.input(); // read Chinese Sememe or "{"
	if (token=="{") // function word
	{
		mndef.Function=true;
		token.input(); // read Chinese Sememe
		mndef.PrimarySememe=getSememeID(token);
		token.input(); // read "|"
		if (token=="|") { token.input(); token.input(); }// read English Sememe
		token.input(); // read "}"
	}
	else // content word
	{
		mndef.Function=false;
		mndef.PrimarySememe=getSememeID(token);
		token.input(); // read "|"
		if (token=="|") { token.input(); token.input(); }// read English Sememe
		while (*token && token==",")
		{
			bool isword=false;
			token.input();
			if (token=="(")
			{
				token.input();
				isword=true;
			}
			if (token.isDelim()) // Symbol Relation
			{
				char symbol=*token;
				SememeWord semword;
				token.input();  // read Sememe or "("
				if (token=="(")
				{
					isword=true;
					token.input();
				}
				if (isword)
				{
					semword.Sememe=-1;
					semword.Word=token;
					token.input();
				}
				else semword.Sememe=getSememeID(token);
				mndef.SymbolRelationSet.insert(pair<char,SememeWord>(symbol,semword));
				token.input();
				if (token=="|") { token.input(); token.input(); }
			}
			else // Sememe or Sememe Relation
			{
				int seme=getSememeID(token);
				token.input();
				if (token=="|") { token.input(); token.input(); }
				if (token=="=")
				{
					token.input();
					SememeWord value;
					if (token=="(")
					{
						isword=true;
						token.input();
					}
					if (isword)
					{
						value.Sememe=-1;
						value.Word=token;
						token.input(); // read ")"
					}
					else value.Sememe=getSememeID(token);
					mndef.SememeRelationSet.insert(pair<int,SememeWord>(seme,value));
					token.input();
				}
				else
				{
					if (isword)
					{
						mndef.SecondSememeSet.insert(SememeWord(-1,token));
					}
					else
					{
						mndef.SecondSememeSet.insert(SememeWord(seme,""));
					}
				}
			}
		}
	}
}
