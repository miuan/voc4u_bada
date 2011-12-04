/*
 * Speaker.h
 *
 *  Created on: 3.12.2011
 *      Author: m1uan
 */

#ifndef SPEAKER_H_
#define SPEAKER_H_

#include "../BaseWordForm.h"

class Speaker : public BaseWordForm
{
public:
	Speaker();
	virtual String GetResourceID(){return L"IDF_TRAIN";};
	virtual ~Speaker();
};

#endif /* SPEAKER_H_ */
