/*
 * TextToSpeechHelper.cpp
 *
 *  Created on: 4.12.2011
 *      Author: m1uan
 */

#include "TextToSpeechHelper.h"
#include <FLclLocale.h>
#include "setting/LangSetting.h"
#include "setting/CommonSetting.h"

using namespace Osp::Locales;

TextToSpeechHelper::TextToSpeechHelper() :
	__pTextToSpeech(null)
{

}

TextToSpeechHelper::~TextToSpeechHelper()
{
	if (__pTextToSpeech)
		delete __pTextToSpeech;
}

void TextToSpeechHelper::Play(String text)
{
	if (!__pTextToSpeech)
	{
		__pTextToSpeech = new TextToSpeech();
		__pTextToSpeech->Construct(*this);
	}

	//__pTextToSpeech->SetLocale()
	result res = __pTextToSpeech->Initialize();
	Locale & loc = LangSetting::GetLocaleFromCode(CommonSetting::GetInstance().lern);

	__pTextToSpeech->SetLocale(loc);

	if (IsFailed(res))
	{
		delete __pTextToSpeech;
		__pTextToSpeech = null;
	}
	else
	{
		__text = text;
	}
}

void TextToSpeechHelper::OnTextToSpeechStatusChanged(Osp::Uix::TextToSpeechStatus status)
{
	if (status == TTS_STATUS_INITIALIZED)
	{
		if (__pTextToSpeech)
			__pTextToSpeech->Speak(__text);
	}
}

void TextToSpeechHelper::OnTextToSpeechErrorOccurred(Osp::Uix::TextToSpeechError error)
{

}
