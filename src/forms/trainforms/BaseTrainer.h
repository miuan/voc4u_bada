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
#include "TextToSpeechHelper.h"

class BaseTrainer: public BaseWordForm
{
private:
	static TextToSpeechHelper * __pTTSH;
protected:
	Word *__word;
	Label *__lblTest;
	ListView *__lastList;


	TextToSpeechHelper * GetTextToSpeechHelper();
public:
	bool GetFirstWord();

	virtual String GetResourceID(){return L"IDF_TRAIN";};

	BaseTrainer();
	virtual ~BaseTrainer();

	virtual LastListProvider & GetProvider() = 0;
	virtual BaseTrainer * NewThisN() = 0;
	virtual result OnInitializing(void);

protected:
	void UpdateListWithWord();
	virtual String GetTextForTestLabel();
};

#endif /* BASETRAINER_H_ */
