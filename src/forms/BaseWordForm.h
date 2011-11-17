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
#include "ctrl/WordCtrl.h"
#include "system/Utils.h"
#include "dialogs/addword/AddWord.h"

using namespace Osp::Ui::Controls;

class BaseWordForm
		: public Osp::Ui::Controls::Form,
		public Osp::Ui::IActionEventListener
{
public:
			static const int ID_ADD_WORD = 101;
protected:
		WordCtrl *__WCtrl;

		AddWord *__pAddWordDlg;
public:
	BaseWordForm();
	virtual ~BaseWordForm();


	bool Init();
	virtual String GetResourceID() = 0;
	virtual result OnInitializing();

	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

	static String GetString(Osp::Base::String ID);
};

#endif /* BASEWORDFORM_H_ */
