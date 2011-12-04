/*
 * Train.h
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#ifndef TRAIN_H_
#define TRAIN_H_

#include "../BaseTrainer.h"
#include "../LastListProvider.h"
#include "dialogs/information/Information.h"

class Train: public BaseTrainer
{

	static LastListProvider *__llProv;

    void UpdateWord(bool know);

public:
	static const int ID_BTN_KNOW = 5001;
	static const int ID_BTN_DONTKNOW = 5002;


public:
	Train();
	virtual ~Train();

	virtual wchar_t* GetShowInfoCode(){ return IDS_TRAIN;};
	virtual String GetResourceID(){return L"IDF_TRAIN";};
protected:
	virtual void PrepareContextMenu();
	virtual void PrepareFooter();

	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

	virtual LastListProvider & GetProvider(){ return *__llProv;};
	virtual BaseTrainer * NewThisN(){return new Train();};
};

#endif /* TRAIN_H_ */
