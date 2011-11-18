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
	NSHDictionary = false;
	NSHInit = false;
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

	int nsh;
	TryReturnVoid(pReg->Get(VAL_NSM_DICTIONARY, nsh) == E_SUCCESS
			, "can not GetValue for native %s", GetErrorMessage(GetLastResult()));
	NSHDictionary = nsh == 1 ? true : false;

	TryReturnVoid(pReg->Get(VAL_NSM_INIT, nsh) == E_SUCCESS
			, "can not GetValue for native %s", GetErrorMessage(GetLastResult()));
	NSHInit = nsh == 1 ? true : false;

	__initialized = true;
	return;
}

result CommonSetting::StoreBool(AppRegistry * pReg, String key, bool value)
{
	result r;
	int nsh = value ? 1 : 0;
	r = pReg->Set(key, nsh);
	if (r == E_KEY_NOT_FOUND)
		r = pReg->Add(key, nsh);

	return r;
}

bool CommonSetting::Store()
{
	result r;
	AppRegistry* pReg = Osp::App::Application::GetInstance()->GetAppRegistry();

	r = pReg->Set(VAL_LERN, lern);
	if (r == E_KEY_NOT_FOUND)
		r = pReg->Add(VAL_LERN, lern);

	if (IsFailed(r))
		goto CATCH;

	r = pReg->Set(VAL_NATIVE, native);
	if (r == E_KEY_NOT_FOUND)
		r = pReg->Add(VAL_NATIVE, native);

	r = StoreBool(pReg, VAL_NSM_DICTIONARY, NSHDictionary);
	if (IsFailed(r))
		goto CATCH;

	if (IsFailed(StoreBool(pReg, VAL_NSM_INIT, NSHInit)))
		goto CATCH;

	pReg->Save();
	return true;

	CATCH: AppLog("Store error by : (%s)", GetErrorMessage(r));
	return false;
}
