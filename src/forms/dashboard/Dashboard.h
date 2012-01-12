/*
 * Dashboard.h
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#ifndef DASHBOARD_H_
#define DASHBOARD_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FApp.h>

#include "dialogs/addword/AddWord.h"
#include "forms/BaseWordForm.h"
#include "dialogs/information/Information.h"

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::App;
using namespace Osp::Graphics;

class Dashboard :
	public BaseWordForm
{
private:
		Information __info;
public:

public:
	Dashboard();
	virtual ~Dashboard();
	virtual String GetResourceID(){return L"IDF_DASHBOARD";};
	result OnInitializing(void);
	virtual wchar_t* GetShowInfoCode(){ return IDS_DASHBOARD;};
protected:
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

};

#endif /* DASHBOARD_H_ */
