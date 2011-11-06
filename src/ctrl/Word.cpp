/*
 * Word.cpp
 *
 *  Created on: 6.11.2011
 *      Author: m1uan
 */

#include "Word.h"

Word::Word(int id, int lesson, String native, String lern, int lw, int nw):
__id(id), __lesson(lesson), __lweight(lw), __nweight(nw)
{
	__native = native;
	__lern = lern;
}

Word::~Word()
{
	// TODO Auto-generated destructor stub
}
