/*
 * CommonSetting.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "CommonSetting.h"

CommonSetting CommonSetting::__this = CommonSetting();

CommonSetting::CommonSetting()
{
	__initialized = false;
}

CommonSetting::~CommonSetting()
{

}

void CommonSetting::Restore()
{
	result r;

	AppRegistry* pReg = Osp::App::Application::GetInstance()->GetAppRegistry();

	TryReturnVoid(pReg->Get(VAL_LERN, lern) == E_SUCCESS
			, "can not GetValue for lern %s", GetErrorMessage(GetLastResult()));

	TryReturnVoid(pReg->Get(VAL_NATIVE, native) == E_SUCCESS
				, "can not GetValue for native %s", GetErrorMessage(GetLastResult()));

	__initialized = true;
	return;
}


bool CommonSetting::Store()
{
	result r;
	AppRegistry* pReg = Osp::App::Application::GetInstance()->GetAppRegistry();

	r = pReg->Add(VAL_LERN, lern);
	if(IsFailed(r))
		goto CATCH;

	r = pReg->Add(VAL_NATIVE, native);
	if(IsFailed(r))
		goto CATCH;

		return true;
	CATCH:
		AppLog("Store error by : (%s)", GetErrorMessage(r));
		return false;
}
