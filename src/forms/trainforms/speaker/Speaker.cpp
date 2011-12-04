/*
 * Speaker.cpp
 *
 *  Created on: 3.12.2011
 *      Author: m1uan
 */

#include "Speaker.h"

LastListProvider *Speaker::__llProv = null;

Speaker::Speaker()
{
	if (!__llProv)
		__llProv = new LastListProvider();
}

Speaker::~Speaker()
{
	// TODO Auto-generated destructor stub
}

result Speaker::OnInitializing(void)
{
	BaseTrainer::OnInitializing();
	return E_SUCCESS;
}
