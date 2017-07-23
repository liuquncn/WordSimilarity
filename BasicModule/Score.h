#ifndef SCORE_H
#define SCORE_H

#include <math.h>

// 评分: 是一个小于或等于0的浮点数，其意义为可信度（取值范围(0,1]）的对数
class Score
{
	float TheScore;
public:
	Score() { TheScore=0; }
	// 取该结点的评分
	float getScore() const { return TheScore; }
	// 设置该结点的评分
	void setScore(float s) { TheScore=(s>0 ? 0 : (s<LowestScore ? LowestScore : s)); }
	// 规则可信度级别的一个等级，是一个浮点型常数数组
	static const float ScaledRuleScore[10];
	// 规则可信度级别的最小值，是一个浮点型常数数组
	static const float LowestRuleScore;
	// 最小评分值，任何评分都应大于这个值
	static const float LowestScore;
};

#endif//SCORE_H