/*
 * Word.cpp
 *
 *  Created on: 6.11.2011
 *      Author: m1uan
 */

#include "Word.h"

Word::Word(int id, int lesson, String native, String lern, int lw, int nw) :
	__id(id), __lesson(lesson), __lweight(lw), __nweight(nw), __user(0)
{
	__native = native;
	__lern = lern;
	__type = __nweight < __lweight ? 1 : 0;
	__know = false;
}

String Word::GetTestWord()
{
	return __type ? __native : __lern;
}

void Word::SetKnow(bool know)
{
	__know = know;

	int &weight = __type ? __nweight : __lweight;
	if(weight < 1)
		weight += 1;

	if (know)
	{
		weight = weight < 10000 ? weight * 3 : weight + 30000;
	}
	else
	{
		weight = weight / 2;
		weight = weight < 1 ? 1 : weight;
	}

//	if(__type)
//		__nweight = weight;
//	else
//		__lweight = weight;
}

Word::~Word()
{
	// TODO Auto-generated destructor stub
}
