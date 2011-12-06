/*
 * Word.h
 *
 *  Created on: 6.11.2011
 *      Author: m1uan
 */

#ifndef WORD_H_
#define WORD_H_

#include <FBase.h>

using namespace Osp::Base;

class Word : public Object
{
public:
	String __native;
	String __lern;
	const int __id;
	int __nweight;
	int __lweight;
	const int __lesson;
	const int __user;

	int __type;
	bool __know;

public:
	Word(int id, int lesson, String lern, String native, int lw, int nw);
	String GetTestWord();
	String GetLern(){return __lern;};
	String GetNative(){return __native;};
	void SetKnow(bool know);
	virtual ~Word();
};

#endif /* WORD_H_ */
