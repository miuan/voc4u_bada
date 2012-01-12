/*
 * CommonSetting.h
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#ifndef COMMONSETTING_H_
#define COMMONSETTING_H_

#include <FBase.h>
#include <FIo.h>
#include <FApp.h>
#include <FAppAppRegistry.h>
using namespace Osp::Base;
using namespace Osp::Io;
using namespace Osp::App;

#define REG_NAME String(L"voc4u_reg.ini")
#define REG_SECTION String(L"SECTION")

#define VAL_LERN String(L"lern")
#define VAL_NATIVE String(L"native")

#define VAL_LESSON String(L"lesson_not_complete")
#define VAL_WORD String(L"word_from_non_complete_lesson")

// No Show More Dictionary
#define VAL_NSM_DICTIONARY String(L"NSM_DICTIONARY")
#define VAL_NSM_INIT String(L"NSM_INIT")
#define VAL_NSM_TRAIN String(L"NSM_TRAIN")
#define VAL_NSM_DASHBOARD String(L"NSM_DASHBOARD")

class CommonSetting
{
private:
	bool __initialized;
public:
	static CommonSetting *__this;

	String lern;
	String native;

	// No Show More
	bool NSHDictionary;
	bool NSHInit;
	bool NSHTrain;
	bool NSHDashboard;

private:
	int __lesson;
	int __word;

public:
	CommonSetting();
	virtual ~CommonSetting();

	void Restore();
	bool Store();

	bool IsInitialized()
	{
		return __initialized;
	}

	static CommonSetting & GetInstance()
	{
		if (__this == null)
		{
			__this = new CommonSetting();
		}

		if (!__this->IsInitialized())
		{
			__this->Restore();
		}

		return *__this;
	}

	bool AddContinueLesson(const int lesson, const int word);
	bool IsContinueLesson(int &lesson, int &word, bool remove = false);
private:

	result StoreBool(AppRegistry * pReg, String key, bool value);
	bool RestoreBool(AppRegistry & reg, String key, bool &value);
};

#endif /* COMMONSETTING_H_ */
