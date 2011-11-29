#include "InitData.h"

#include "lesson1/DataCS.h"
#include "lesson1/DataDE.h"
#include "lesson1/DataEN.h"
#include "lesson1/DataES.h"
#include "lesson1/DataFR.h"
#include "lesson1/DataPL.h"
#include "lesson1/DataPT.h"
#include "lesson2/DataCS.h"
#include "lesson2/DataDE.h"
#include "lesson2/DataEN.h"
#include "lesson2/DataES.h"
#include "lesson2/DataFR.h"
#include "lesson2/DataPL.h"
#include "lesson2/DataPT.h"
#include "lesson3/DataCS.h"
#include "lesson3/DataDE.h"
#include "lesson3/DataEN.h"
#include "lesson3/DataES.h"
#include "lesson3/DataFR.h"
#include "lesson3/DataPL.h"
#include "lesson3/DataPT.h"
#include "lesson4/DataCS.h"
#include "lesson4/DataDE.h"
#include "lesson4/DataEN.h"
#include "lesson4/DataES.h"
#include "lesson4/DataFR.h"
#include "lesson4/DataPL.h"
#include "lesson4/DataPT.h"
#include "lesson5/DataCS.h"
#include "lesson5/DataDE.h"
#include "lesson5/DataEN.h"
#include "lesson5/DataES.h"
#include "lesson5/DataFR.h"
#include "lesson5/DataPL.h"
#include "lesson5/DataPT.h"


wchar_t ** getInitData(String lang, const int lesson, int &count)
{
			if( lesson == 1 && lang == "CZ"){ count = DATA_CS_1::num;return (wchar_t**)DATA_CS_1::texts;}
		if( lesson == 1 && lang == "DE"){ count = DATA_DE_1::num;return (wchar_t**)DATA_DE_1::texts;}
		if( lesson == 1 && lang == "GB"){ count = DATA_EN_1::num;return (wchar_t**)DATA_EN_1::texts;}
		if( lesson == 1 && lang == "ES"){ count = DATA_ES_1::num;return (wchar_t**)DATA_ES_1::texts;}
		if( lesson == 1 && lang == "FR"){ count = DATA_FR_1::num;return (wchar_t**)DATA_FR_1::texts;}
		if( lesson == 1 && lang == "PL"){ count = DATA_PL_1::num;return (wchar_t**)DATA_PL_1::texts;}
		if( lesson == 1 && lang == "PT"){ count = DATA_PT_1::num;return (wchar_t**)DATA_PT_1::texts;}
		if( lesson == 2 && lang == "CZ"){ count = DATA_CS_2::num;return (wchar_t**)DATA_CS_2::texts;}
		if( lesson == 2 && lang == "DE"){ count = DATA_DE_2::num;return (wchar_t**)DATA_DE_2::texts;}
		if( lesson == 2 && lang == "GB"){ count = DATA_EN_2::num;return (wchar_t**)DATA_EN_2::texts;}
		if( lesson == 2 && lang == "ES"){ count = DATA_ES_2::num;return (wchar_t**)DATA_ES_2::texts;}
		if( lesson == 2 && lang == "FR"){ count = DATA_FR_2::num;return (wchar_t**)DATA_FR_2::texts;}
		if( lesson == 2 && lang == "PL"){ count = DATA_PL_2::num;return (wchar_t**)DATA_PL_2::texts;}
		if( lesson == 2 && lang == "PT"){ count = DATA_PT_2::num;return (wchar_t**)DATA_PT_2::texts;}
		if( lesson == 3 && lang == "CZ"){ count = DATA_CS_3::num;return (wchar_t**)DATA_CS_3::texts;}
		if( lesson == 3 && lang == "DE"){ count = DATA_DE_3::num;return (wchar_t**)DATA_DE_3::texts;}
		if( lesson == 3 && lang == "GB"){ count = DATA_EN_3::num;return (wchar_t**)DATA_EN_3::texts;}
		if( lesson == 3 && lang == "ES"){ count = DATA_ES_3::num;return (wchar_t**)DATA_ES_3::texts;}
		if( lesson == 3 && lang == "FR"){ count = DATA_FR_3::num;return (wchar_t**)DATA_FR_3::texts;}
		if( lesson == 3 && lang == "PL"){ count = DATA_PL_3::num;return (wchar_t**)DATA_PL_3::texts;}
		if( lesson == 3 && lang == "PT"){ count = DATA_PT_3::num;return (wchar_t**)DATA_PT_3::texts;}
		if( lesson == 4 && lang == "CZ"){ count = DATA_CS_4::num;return (wchar_t**)DATA_CS_4::texts;}
		if( lesson == 4 && lang == "DE"){ count = DATA_DE_4::num;return (wchar_t**)DATA_DE_4::texts;}
		if( lesson == 4 && lang == "GB"){ count = DATA_EN_4::num;return (wchar_t**)DATA_EN_4::texts;}
		if( lesson == 4 && lang == "ES"){ count = DATA_ES_4::num;return (wchar_t**)DATA_ES_4::texts;}
		if( lesson == 4 && lang == "FR"){ count = DATA_FR_4::num;return (wchar_t**)DATA_FR_4::texts;}
		if( lesson == 4 && lang == "PL"){ count = DATA_PL_4::num;return (wchar_t**)DATA_PL_4::texts;}
		if( lesson == 4 && lang == "PT"){ count = DATA_PT_4::num;return (wchar_t**)DATA_PT_4::texts;}
		if( lesson == 5 && lang == "CZ"){ count = DATA_CS_5::num;return (wchar_t**)DATA_CS_5::texts;}
		if( lesson == 5 && lang == "DE"){ count = DATA_DE_5::num;return (wchar_t**)DATA_DE_5::texts;}
		if( lesson == 5 && lang == "GB"){ count = DATA_EN_5::num;return (wchar_t**)DATA_EN_5::texts;}
		if( lesson == 5 && lang == "ES"){ count = DATA_ES_5::num;return (wchar_t**)DATA_ES_5::texts;}
		if( lesson == 5 && lang == "FR"){ count = DATA_FR_5::num;return (wchar_t**)DATA_FR_5::texts;}
		if( lesson == 5 && lang == "PL"){ count = DATA_PL_5::num;return (wchar_t**)DATA_PL_5::texts;}
		if( lesson == 5 && lang == "PT"){ count = DATA_PT_5::num;return (wchar_t**)DATA_PT_5::texts;}


	count = 0;
	return null;
}





