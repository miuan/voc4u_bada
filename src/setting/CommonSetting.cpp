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

	Registry reg;
	r = reg.Construct(REG_NAME, false);
	TryReturnVoid(r == E_SUCCESS, "");

	TryReturnVoid(reg.GetValue(REG_SECTION, VAL_LERN, lern) == E_SUCCESS
			, "can not GetValue for lern");

	TryReturnVoid(reg.GetValue(REG_SECTION, VAL_NATIVE, native) == E_SUCCESS
				, "can not GetValue for native");

	__initialized = true;
	return;
}


bool CommonSetting::Store()
{
	Registry reg;
	//AppRegistry* pAppRegistry = Osp::App::Application::GetInstance()->GetAppRegistry();
	result r = reg.Construct(name, REG_OPEN_READ_WRITE | REG_OPEN_CREATE, true, 0);
	if(IsFailed(r))
	{
		AppLog("reg construct doesn't work (%s)", GetErrorMessage(r));
		goto CATCH;
	}
	reg.AddSection(REG_SECTION);


	r = reg.AddValue(REG_SECTION, VAL_LERN,lern);
	if(r == E_KEY_ALREADY_EXIST)
		r = reg.SetValue(REG_SECTION, VAL_LERN, lern);

	if(IsFailed(r))
		goto CATCH;

	r = reg.AddValue(REG_SECTION, VAL_NATIVE, native);
	if(r == E_KEY_ALREADY_EXIST)
		r = reg.SetValue(REG_SECTION, VAL_NATIVE, native);

	if(IsFailed(r))
		goto CATCH;

		return true;
	CATCH:
		return false;
}
