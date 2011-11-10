/*
 * Utils.cpp
 *
 *  Created on: 10.11.2011
 *      Author: m1uan
 */

#include "Utils.h"

#include <FApp.h>
using namespace Osp::Base;
using namespace Osp::App;

Utils::Utils()
{
	// TODO Auto-generated constructor stub

}

Utils::~Utils()
{
	// TODO Auto-generated destructor stub
}

String Utils::GetString(String ID)
{
	String out = "";
	Application* pApp = Application::GetInstance();
	pApp->GetAppResource()->GetString(ID, out);
	return out;
}
