
#include "score.h"
#include <math.h>

const float Score::ScaledRuleScore[10] =
{
	(float)log(1.0-1.0/2.0),
	(float)log(1.0-1.0/2.0/2.0),
	(float)log(1.0-1.0/2.0/2.0/2.0),
	(float)log(1.0-1.0/2.0/2.0/2.0/2.0),
	(float)log(1.0-1.0/2.0/2.0/2.0/2.0/2.0),
	(float)log(1.0-1.0/2.0/2.0/2.0/2.0/2.0/2.0),
	(float)log(1.0-1.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0),
	(float)log(1.0-1.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0),
	(float)log(1.0-1.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0),
	(float)log(1.0-1.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0)
};

const float Score::LowestRuleScore=-1000.0;

const float Score::LowestScore=-1000000000.0;
