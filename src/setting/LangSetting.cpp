/*
 * LangSetting.cpp
 *
 *  Created on: 23.10.2011
 *      Author: m1uan
 */

#include "LangSetting.h"
#include "system/Utils.h"

const Locale LangSetting::CZECH(LANGUAGE_CES, COUNTRY_CZ);
const Locale LangSetting::ENGLISH(LANGUAGE_ENG, COUNTRY_US);
const Locale LangSetting::GERMANY(LANGUAGE_DEU, COUNTRY_DE);
const Locale LangSetting::SPAIN(LANGUAGE_SPA, COUNTRY_ES);
const Locale LangSetting::PORTUGAL(LANGUAGE_POR, COUNTRY_PT);
const Locale LangSetting::POLAND(LANGUAGE_POL, COUNTRY_PL);
const Locale LangSetting::FRANCE(LANGUAGE_FRA, COUNTRY_FR);
const Locale LangSetting::ITALIAN(LANGUAGE_ITA, COUNTRY_IT);

Locale LangSetting::LOCALES[] =
{ LangSetting::CZECH, LangSetting::ENGLISH, LangSetting::GERMANY, LangSetting::SPAIN, LangSetting::PORTUGAL, LangSetting::POLAND, LangSetting::FRANCE, LangSetting::ITALIAN };

const int LangSetting::NUM_LOCALES = 8;

const Color LangSetting::LESSON_COLORS[] = {Color(155,255,100), Color(155,205,100), Color(205,155,100), Color(255,155,100)};

LangSetting::LangSetting()
{
}

LangSetting::~LangSetting()
{
}

String LangSetting::GetNameOfLesson(int lesson)
{
	String name = L"IDS_LESSON_";
	name.Append(lesson);
	return Utils::GetString(name);
}

wchar_t ** LangSetting::GetInitDataN(String lang, int lesson, int &count)
{
	return getInitData(lang, lesson, count);
}
