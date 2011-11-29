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

	int nsh;
	TryReturnVoid(pReg->Get(VAL_NSM_DICTIONARY, nsh) == E_SUCCESS
			, "can not GetValue for native %s", GetErrorMessage(GetLastResult()));
	NSHDictionary = nsh == 1 ? true : false;

	TryReturnVoid(pReg->Get(VAL_NSM_INIT, nsh) == E_SUCCESS
			, "can not GetValue for native %s", GetErrorMessage(GetLastResult()));
	NSHInit = nsh == 1 ? true : false;

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
