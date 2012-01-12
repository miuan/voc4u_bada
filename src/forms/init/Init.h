#ifndef _INIT_H_
#define _INIT_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>

#include "LangSelect.h"
#include "setting/CommonSetting.h"
#include "forms/dashboard/Dashboard.h"
#include "forms/trainforms/train/Train.h"
#include "dialogs/information/Information.h"
#include "system/DeleteListObject.h"

class InitFrm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
	public ILangSelectListener,
	public DeleteListObject
{
		CommonSetting *__setting;

		Information __infoDlg;
// Construction
public:
	InitFrm(void);
	virtual ~InitFrm(void);
	bool Initialize(void);

// Implementation
protected:
	static const int ID_BUTTON_NATIVE = 101;
	static const int ID_BUTTON_LERN = 102;
	static const int ID_BUTTON_BEGIN = 103;
	static const int ID_BUTTON_TRAIN = 104;
	Osp::Ui::Controls::Button *__pbtnNative;
	Osp::Ui::Controls::Button *__pbtnLern;
	Osp::Ui::Controls::Button *__pbtnMenu;
	Osp::Ui::Controls::Button *__pbtnTrain;


	Locale *__pLern, * __pNative;

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	virtual void onSelectLang(int type, Locale &selected);
};

#endif	//_INIT_H_
