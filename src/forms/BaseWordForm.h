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
		public Osp::Ui::IActionEventListener,
		public IFormBackEventListener
{
private:
		ArrayList __destructList;
		Form * __pBackForm;

public:
		static const int ID_ADD_WORD = 101;
		static const int ID_TRAIN = 102;
		static const int ID_MENU = 103;
		static const int ID_MENU_INFO = 104;

protected:
		WordCtrl *__WCtrl;
		ContextMenu *__pContextMenu;
		AddWord *__pAddWordDlg;
public:
	BaseWordForm();
	virtual ~BaseWordForm();


	bool Init();
	virtual String GetResourceID() = 0;
	virtual result OnInitializing();

	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

	static String GetString(Osp::Base::String ID);
	void SetBackForm(Form &frm);
protected:
	void AddToDestructList(Object *obj);
	virtual void PrepareHeader();
	virtual void PrepareFooter();
	virtual void PrepareContextMenu();

	void ShowInfoDlg();

	virtual  wchar_t* GetShowInfoCode();
	virtual void OnFormBackRequested (Osp::Ui::Controls::Form &source);
};

#endif /* BASEWORDFORM_H_ */
