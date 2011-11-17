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

// No Show More Dictionary
#define VAL_NSM_DICTIONARY String(L"NSM_DICTIONARY")


class CommonSetting
{
private:
	bool __initialized;
public:
	static CommonSetting __this;

	String lern;
	String native;

	// No Show More
	bool NSHDictionary;



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
		if(!__this.IsInitialized())
			__this.Restore();
		return __this;
	}


};

#endif /* COMMONSETTING_H_ */
