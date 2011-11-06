/*
 * WordCtrl.cpp
 *
 *  Created on: 6.11.2011
 *      Author: m1uan
 */

#include "WordCtrl.h"

WordCtrl * WordCtrl::__wc = null;

WordCtrl::WordCtrl()
{
	// TODO Auto-generated constructor stub

}

WordCtrl::~WordCtrl()
{
	// TODO Auto-generated destructor stub
}

WordCtrl * WordCtrl::GetInstance()
{
	if(!__wc)
		__wc = new WordCtrl();

	return __wc;
}

bool WordCtrl::AddWord(Word &word)
{
	return true;
}
