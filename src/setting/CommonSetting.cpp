/*
 * CommonSetting.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "CommonSetting.h"

CommonSetting *CommonSetting::__this = null;

CommonSetting::CommonSetting() :
	__lesson(-1), __word(-1)
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

	TryReturnVoid(RestoreBool(*pReg, VAL_NSM_DICTIONARY, NSHDictionary)
			, "can not GetValue for native %s", GetErrorMessage(GetLastResult()));

	TryReturnVoid(RestoreBool(*pReg, VAL_NSM_INIT, NSHInit)
			, "can not GetValue for native %s", GetErrorMessage(GetLastResult()));

	TryReturnVoid(RestoreBool(*pReg, VAL_NSM_DASHBOARD, NSHDashboard)
			, "can not GetValue for native %s", GetErrorMessage(GetLastResult()));

	TryReturnVoid(RestoreBool(*pReg, VAL_NSM_TRAIN, NSHTrain)
			, "can not GetValue for native %s", GetErrorMessage(GetLastResult()));

	if (IsFailed(pReg->Get(VAL_LESSON, __lesson)))
	{
		__lesson = -1;
	}
	if (IsFailed(pReg->Get(VAL_WORD, __word)))
	{
		__word = -1;
	}

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

bool CommonSetting::RestoreBool(AppRegistry & reg, String key, bool &value)
{
	int nsh = 0;
	result r = reg.Get(key, nsh);
	if (r == E_SUCCESS)
	{
		value = nsh == 1 ? true : false;
		return true;
	}
	else
	{
		return false;
	}
}

bool CommonSetting::Store()
{
	result r;
	AppRegistry* pReg = Osp::App::Application::GetInstance()->GetAppRegistry();

	if (lern.GetLength() == 0)
	{
		r = pReg->Remove(VAL_LERN);
	}
	else
	{
		r = pReg->Set(VAL_LERN, lern);
		if (r == E_KEY_NOT_FOUND)
			r = pReg->Add(VAL_LERN, lern);
	}

	if (IsFailed(r))
		goto CATCH;

	if (native.GetLength() == 0)
	{
		r = pReg->Remove(VAL_NATIVE);
	}
	else
	{
		r = pReg->Set(VAL_NATIVE, native);
		if (r == E_KEY_NOT_FOUND)
			r = pReg->Add(VAL_NATIVE, native);
	}

	r = StoreBool(pReg, VAL_NSM_DICTIONARY, NSHDictionary);
	if (IsFailed(r))
		goto CATCH;

	if (IsFailed(StoreBool(pReg, VAL_NSM_INIT, NSHInit)))
		goto CATCH;

	if (IsFailed(StoreBool(pReg, VAL_NSM_DASHBOARD, NSHDashboard)))
		goto CATCH;

	if (IsFailed(StoreBool(pReg, VAL_NSM_TRAIN, NSHTrain)))
		goto CATCH;
	//if(__lesson > -1 && __word > -1)
	{
		if (IsFailed(pReg->Set(VAL_LESSON, __lesson)) && IsFailed(pReg->Add(VAL_LESSON, __lesson)))
		{
			AppAssertf(false, "Storing lesson isn't correct!");
		}
		if (IsFailed(pReg->Set(VAL_WORD, __word)) && IsFailed(pReg->Add(VAL_WORD, __word)))
		{
			AppAssertf(false, "Storing word isn't correct!");
		}
	}
	//	else
	//	{
	//		pReg->Remove(VAL_LESSON);
	//		pReg->Remove(VAL_WORD);
	//	}

	pReg->Save();
	return true;

	CATCH: AppLog("Store error by : (%s)", GetErrorMessage(r));
	return false;
}

bool CommonSetting::AddContinueLesson(const int lesson, const int word)
{
	__lesson = lesson;
	__word = word;

	return Store();
}

bool CommonSetting::IsContinueLesson(int &lesson, int &word, bool remove)
{
	Restore();

	lesson = __lesson;
	word = __word;

	if (remove)
	{
		__lesson = -1;
		__word = -1;

		// you can get the lesson and word
		// only one time!
		Store();
	}

	return lesson > -1 && word > -1;
}
