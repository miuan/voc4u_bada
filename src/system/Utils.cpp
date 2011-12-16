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

Bitmap * Utils::GetBitmapN(String ID)
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
	if (parent != null)
		pFrame->RemoveControl(*parent);
}

void Utils::SplitString(Osp::Base::String &str, Osp::Base::String separator, Osp::Base::Collection::ArrayList & arrays)
{
	const int len = str.GetLength();
	const wchar_t *p = str.GetPointer();

	const int seplen = separator.GetLength();
	const wchar_t *sep = separator.GetPointer();

	String *add = new String();
	for (int i = 0; i < len; i++)
	{
		bool isSep = true;
		for (int s = 0; s != seplen && i + s < len; s++)
		{
			if (*(p + s) != *(sep + s))
			{
				isSep = false;
				break;
			}
		}

		if (!isSep)
		{
			add->Append(*p);
			p++;
		}
		else
		{
			// because was the separor,
			// move the pointer after separator
			i += seplen;
			p += seplen;

			// add to list as new word
			AppLogDebug("Add to list: %S", add->GetPointer());
			arrays.Add(*add);
			add = new String();
		}
	}

	if (add->GetLength() > 0)
	{
		// if on end store last on-working word
		AppLogDebug("Add to list: %S", add->GetPointer());
		arrays.Add(*add);
	}
}

void Utils::RemovePunctuationFromEnd(String &str)
{
	const static String strQuestionMark = "?";
	const static String strExclamationMark = "!";
	const static String srtDot = ".";

	bool remove = str.EndsWith(strQuestionMark)
					|| str.EndsWith(strExclamationMark)
					|| str.EndsWith(srtDot);
	if(remove)
	{
		str.Remove(str.GetLength()-1, 1);
		RemovePunctuationFromEnd(str);
	}
}
