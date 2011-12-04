/*
 * Speaker.cpp
 *
 *  Created on: 3.12.2011
 *      Author: m1uan
 */

#include "Listener.h"

LastListProvider *Listener::__llProv = null;

Listener::Listener()
{
	if (!__llProv)
		__llProv = new LastListProvider();
}

Listener::~Listener()
{
	// TODO Auto-generated destructor stub
}
