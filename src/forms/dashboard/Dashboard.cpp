/*
 * Dashboard.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "Dashboard.h"

Dashboard::Dashboard()
{
	// TODO Auto-generated constructor stub

}

Dashboard::~Dashboard()
{
	// TODO Auto-generated destructor stub
}

result
Dashboard::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	Button *pBtn_train = static_cast<Button *>(GetControl("IDC_BTN_TRAIN"));
	if (pBtn_train)
	{
		pBtn_train->SetActionId(101);
		pBtn_train->AddActionEventListener(*this);
	}

	return r;
}


bool Dashboard::Initialize()
{
	Construct(L"IDF_DASHBOARD");
	return true;
}

#include "../init/Init.h"
void Dashboard::OnActionPerformed(const Osp::Ui::Control& source, int actionId)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

	Init * init = new Init();
	init->Initialize();
	pFrame->RemoveControl(*init);
	pFrame->AddControl(*init);
	pFrame->SetCurrentForm(*init);
	init->RequestRedraw(true);



}
