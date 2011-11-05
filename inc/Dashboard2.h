
#ifndef _DASHBOARD2_H_
#define _DASHBOARD2_H_

#include <FBase.h>
#include <FUi.h>



class Dashboard2 :
	public Osp::Ui::Controls::Form,
 	public Osp::Ui::IActionEventListener
{

// Construction
public:
	Dashboard2(void);
	virtual ~Dashboard2(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:

// Generated call-back functions
public:


	virtual void OnActionPerformed(const Osp::Ui::Control &source, int actionId);
};

#endif
