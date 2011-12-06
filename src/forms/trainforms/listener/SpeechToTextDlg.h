/*
 * LangSelect.h
 *
 *  Created on: 23.10.2011
 *      Author: m1uan
 */

#ifndef _SPEECH_TO_TEXT_DLG_H_
#define _SPEECH_TO_TEXT_DLG_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FMedia.h>
#include <FLclLocale.h>
#include <FApp.h>

#include "ctrl/WordCtrl.h"

using namespace Osp::App;
using namespace Osp::Locales;
using namespace Osp::Base;
using namespace Osp::Graphics;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Media;

class SpeechToTextDlg: public Popup, public IActionEventListener
{
private:
	Form *__pParentForm;
	EditField *__pNative;
	EditField *__pLern;
    void showErrorMessageBox();


    IActionEventListener * __resultListener;
    int __resultActionCode;

public:
	static const int ID_BTN_CANCEL = 1;
	static const int ID_BTN_STOP_SPEAKING = 2;

public:
	SpeechToTextDlg();
	bool ShowPopup(Form * parent, String title);
	virtual ~SpeechToTextDlg();

	virtual void OnActionPerformed(const Osp::Ui::Control & source, int actionId);

	/**
	 * set ActionEventListener when success add new custom button
	 * see to dictionary
	 */
	void SetResultListener(IActionEventListener * rl, int actionCode)
	{
		__resultListener = rl;
		__resultActionCode = actionCode;
	}
};

#endif /* _SPEECH_TO_TEXT_DLG_H_ */
