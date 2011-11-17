/*
 * LangSelect.h
 *
 *  Created on: 23.10.2011
 *      Author: m1uan
 */

#ifndef INFORMATION_H_
#define INFORMATION_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FMedia.h>
#include <FLclLocale.h>
#include <FApp.h>

#include "system/Utils.h"

using namespace Osp::App;
using namespace Osp::Locales;
using namespace Osp::Base;
using namespace Osp::Graphics;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Media;

#define IDS_DICTIONARY L"DICTIONARY"

class Information: public Popup, public IActionEventListener
{
private:
	Form *__pParentForm;

	String __type;

	CheckButton *__chkNoShowMore;
    void SetupCheckbox(bool & checked);
    void SetupCommonSetting(bool checked);

public:
	static const int ID_BTN_CANCEL = 1;
	static const int ID_BTN_NOSHOWMORE = 2;
public:
	Information();
	Information(String type);
	bool ShowPopup(Form * parent);
	virtual ~Information();
	 void SetType(String type);
	virtual void OnActionPerformed(const Osp::Ui::Control & source, int actionId);
};

#endif /* INFORMATION_H_ */
