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
using namespace Osp::Graphics;

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

Bitmap * Utils::GetBitmap(String ID)
{
	AppLogDebug("load icons: %S", ID.GetPointer());
	Application* pApp = Application::GetInstance();

	// TODO: handling the resource (store in list and remove on end)
	return pApp->GetAppResource()->GetBitmapN(ID, BITMAP_PIXEL_FORMAT_ARGB8888);
}

void Utils::ShowFront(Osp::Ui::Controls::Form *form, Osp::Ui::Controls::Form *parent)
{
	Osp::Ui::Controls::Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	pFrame->AddControl(*form);
	pFrame->SetCurrentForm(*form);
	form->RequestRedraw(true);
	if(parent != null)
		pFrame->RemoveControl(*parent);
}
