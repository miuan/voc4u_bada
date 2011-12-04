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
		static Bitmap *__pBGLogo;
		static Bitmap *__pICHeader;
public:
		static const int ID_ADD_WORD = 101;
		static const int ID_TRAIN = 102;
		static const int ID_MENU = 103;
		static const int ID_MENU_INFO = 104;
		static const int ID_DICTIONARY = 105;
		static const int ID_SPEAKER = 106;
		static const int ID_LISTENER = 107;


protected:
		WordCtrl *__WCtrl;
		ContextMenu *__pContextMenu;
		AddWord *__pAddWordDlg;
    void ShowDictionary();
public:
	BaseWordForm();
	virtual ~BaseWordForm();


	bool Init();
	virtual String GetResourceID() = 0;
	virtual result OnInitializing();

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
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

	virtual result OnDraw(void);
};

#endif /* BASEWORDFORM_H_ */
