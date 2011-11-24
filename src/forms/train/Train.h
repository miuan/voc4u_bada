/*
 * Train.h
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#ifndef TRAIN_H_
#define TRAIN_H_

#include "../BaseWordForm.h"

class Train: public BaseWordForm
{
public:
	Train();
	virtual ~Train();

	virtual String GetResourceID();
	virtual result OnInitializing(void);
protected:
	virtual void PrepareContextMenu();
	virtual void PrepareFooter();
};

#endif /* TRAIN_H_ */
