/*
 * WordCtrl.h
 *
 *  Created on: 6.11.2011
 *      Author: m1uan
 */

#ifndef WORDCTRL_H_
#define WORDCTRL_H_

#include "Word.h"

class WordCtrl
{
private:
	static WordCtrl *__wc;

public:
	WordCtrl();
	virtual ~WordCtrl();

	static WordCtrl * GetInstance();
	bool AddWord(Word &word);
};

#endif /* WORDCTRL_H_ */
