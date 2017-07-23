一）
whole文件中存放的是全部特征文件的义原；包括以下几个特征文件：
1)entity.txt;	  	813
2)event.txt;  	  	141
3)attribute value.txt 	433
4)syntax.txt 		41
5)quantity value.txt 	13
6)secondary feature.txt 100

其中在attribute value.txt、quantity value.txt中已经隐含着attribute.txt、quantity value.txt中的上下位关系。

hownet提供的特征文件还有converse.txt、antonym.txt、event role && features.txt，对这些文件中对义、反义、

二）
whole.dat文件根据whole生成,每一行的内容如下：
	义原的序号  义原的内容	     该义原的父节点序号
e.g 	  1  	    static|静态             0

当某个义原不存在父节点时，其父节点则为自身；

三）
syntax:
dealhownet.pl < inputfilename > outfilename
dealhownet.pl < whole > whole.dat
得到义原网络体系中上下位关系；

semidx.pl <whole.dat > semno.dat
生成semno.dat文件的格式为
whole.dat的每一行添加一个汉语义原名；
更名为whole.dat，semno.dat删除，则whole.dat文件格式为：
	义原的序号  义原的内容	     该义原的父节点序号 汉语义原名
e.g 	  1  	    static|静态             0		  静态



目的是为了当输入汉语义原时，方便查找该义原的号码。

四）
GetSemDict.pl < whole > semdict.dat
得到每个义原的解释，表示了该义原和其他义原的关系；
输入为whole文件，输出为semdict.dat;

semdict.dat文件每一项的格式如下：
	义原序号  	 该义原的定义
e.g	1506	  	[$consume|摄取]

1506可以从whole.dat文件中查到义原为1506  flesh|肉；

ProcSemdict.pl用来得到需要的文件格式
perl ProcSemdict.pl < semdict.dat > semdict
semdict文件每一项的格式如下：
	义原序号	定义项数目  	 该义原的定义
e.g	1506	  	  1		[$consume|摄取]

1506可以从whole.dat文件中查到义原为1506  flesh|肉；


五）
ProcessDict.c
功能： 把hownet.txt文件中的词典抽取出来放入一个数据文件dict.dat中;
如果只考虑汉语的话，可以从词典中只抽取三项内容
文件中每一项的存放格式如下：
	汉词	 汉语词性  	定义
	搥打       V	 	beat|打

例如对于汉词“掌握”，共有5个词条(由于英语翻译的不同），而我们得到的结果是：
W_C=掌握	G_C=V 	DEF=control|控制
W_C=掌握	G_C=V	DEF=know|知道

处理策略：抽取所有词条，然后通过delsame.exe删除完全相同的行，可以得到不同的汉词及其意义共66181行，为glossary.dat

1)ProcessDict.c编译后生成的可执行文件a.out
a.out hownet.txt dicttmp.dat
2)delsame dicttmp.dat glossary.dat
对glossary.dat进行处理，把一些定义项中的空格换成下划线以便容易处理。生成文件glossary.dic。
例如：the Ivory Coast|象牙海岸
改为：the_Ivory_Coast|象牙海岸

六）semeset.h semeset.cpp 用来对义原集合进行操作，可以得到上位和祖先节
点。

黄雄要的接口：
 1)判断义原之间的关系：
 	int SemeSet::IsAncestor(seme1,seme2);
	输入：是两个义原
	输出：一个整数
	   如果为0,则义原之间不存在上下位关系；
	   如果为正数+n,则seme1为seme2的n层祖先；
	   如果为负数-n,则seme2为seme1的n层祖先；	   
 2)从词典中得到词的各种关系
 	int Word_Relation(char *word, Set *rels)
 	
可执行程序：semeset
  输入：wordpair.inf
  输出：wp_rel.inf
  功能：计算词语相似度：输入文件中每一行两个词，输出文件中给出每一行中两个词的相似度（％）。
  

七）GetStatistics.pl用来得到统计数据，每一个汉词的DEF平均有几个定义项。
syntax:
perl GetStatistics.pl < dictnew.dat > statisdata

每一个汉词的平均定义关系项数目为 2.328221个。
每一个义原的平均定义关系项数目为 0.358858个。

八）Sem_WordIdx.pl (没做）
用来为词作索引，每一个义原对应哪些词，形成一个关联数组，
sem1->{wd1,wd2}