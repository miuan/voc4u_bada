/*
 * LangSelect.h
 *
 *  Created on: 23.10.2011
 *      Author: m1uan
 */

#ifndef ADD_WORD_H_
#define ADD_WORD_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FMedia.h>
#include <FLclLocale.h>
#include <FApp.h>

using namespace Osp::App;
using namespace Osp::Locales;
using namespace Osp::Base;
using namespace Osp::Graphics;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Media;

class AddWord: public Popup, public IActionEventListener
{
private:
	Form *__pParentForm;
	EditField *__pNative;
	EditField *__pLern;
    void showErrorMessageBox();


public:
	static const int ID_BTN_CANCEL = 1;
	static const int ID_BTN_ADD = 2;

public:
	AddWord();
	bool ShowPopup(Form * parent);
	virtual ~AddWord();

	virtual void OnActionPerformed(const Osp::Ui::Control & source, int actionId);
};

#endif /* ADD_WORD_H_ */
