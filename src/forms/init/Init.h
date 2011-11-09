#ifndef _INIT_H_
#define _INIT_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>

#include "LangSelect.h"
#include "setting/CommonSetting.h"

class Init :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
	public ILangSelectListener
{

// Construction
public:
	Init(void);
	virtual ~Init(void);
	bool Initialize(void);

// Implementation
protected:
	static const int ID_BUTTON_NATIVE = 101;
	static const int ID_BUTTON_LERN = 102;
	static const int ID_BUTTON_BEGIN = 103;
	Osp::Ui::Controls::Button *__pbtnNative;
	Osp::Ui::Controls::Button *__pbtnLern;
	Osp::Ui::Controls::Button *__pbtnBegin;

	Locale *__pLern, * __pNative;

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	virtual void onSelectLang(int type, Locale &selected);
};

#endif	//_INIT_H_
