/*
 * BaseWordForm.h
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#ifndef BASEWORDFORM_H_
#define BASEWORDFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>

#include "setting/CommonSetting.h"

class BaseWordForm
		: public Osp::Ui::Controls::Form
{
public:
	BaseWordForm();
	virtual ~BaseWordForm();


	bool Initialize();


};

#endif /* BASEWORDFORM_H_ */
