/*
 * BaseTrainer.h
 *
 *  Created on: 4.12.2011
 *      Author: m1uan
 */

#ifndef BASETRAINER_H_
#define BASETRAINER_H_

#include "../BaseWordForm.h"
#include "LastListProvider.h"
#include "forms/dictionary/Dictionary.h"

class BaseTrainer: public BaseWordForm
{
protected:
	Word *__word;
	Label *__lblTest;
	ListView *__lastList;

public:
	bool GetFirstWord();

	virtual String GetResourceID(){return L"IDF_TRAIN";};

	BaseTrainer();
	virtual ~BaseTrainer();

	virtual LastListProvider & GetProvider() = 0;
	virtual BaseTrainer * NewThisN() = 0;
	virtual result OnInitializing(void);
};

#endif /* BASETRAINER_H_ */
