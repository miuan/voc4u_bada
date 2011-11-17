/*
 * LessonWorker.cpp
 *
 *  Created on: 17.11.2011
 *      Author: m1uan
 */

#include "LessonWorker.h"

#include "WordCtrl.h"
#include "Setting/LangSetting.h"
#include "Setting/CommonSetting.h"

LessonWorker::LessonWorker()
{
	__mutex.Create();
	__mutexWait.Create();
	__list.Construct(10);
	__runing = false;
	__currentLesson = 0;
	__stop = false;
	__lwLissener = null;
	// must be set true
	// because firt in Run is first call
	// to IsWait
	__wait = true;
}

LessonWorker::~LessonWorker()
{

}

bool LessonWorker::GetLessonFromList(int & lesson)
{
	__mutex.Acquire();

	// reset values to stop
	lesson = 0;
	__currentLesson = 0;

	// is something for do in list?
	__runing = __list.GetCount() > 0;
	if (__runing)
	{
		Integer *pInt = static_cast<Integer*> (__list.GetAt(0));
		lesson = pInt->ToInt();
		__list.RemoveAt(0, true);
		__currentLesson = lesson;
		__stop = false;
	}
	__mutex.Release();

	return lesson != 0;
}

bool LessonWorker::AddLesson(int lesson, bool remove)
{
	AppAssert(lesson != 0);
	if (lesson == 0)
		return false;

	bool result = true;

	// negative lesson is remove lesson with the id
	lesson = !remove ? lesson : lesson * -1;

	__mutex.Acquire();

	int inversion = lesson * (-1);

	// try add lesson which actualy in work process
	if (lesson == __currentLesson)
	{
		result = false;
		goto RELEASE;
	}

	// try add lesson which is inversion of lesson already in work process
	if (inversion == __currentLesson)
	{
		// hope that isn't in list other inversion
		// because will be catched here
		// on previosly attempt
		result = __list.InsertAt(*(new Integer(lesson)), 0) == E_SUCCESS;
		__stop = true;

		goto RELEASE;
	}

	// get inversion in list
	// when somebody check lesson and after that uncheck

	for (int i = 0; i != __list.GetCount(); i++)
	{
		Integer *pInt = static_cast<Integer*> (__list.GetAt(0));
		if (inversion == pInt->ToInt())
		{
			__list.RemoveAt(i, true);
			result = true;
			goto RELEASE;
		}
	}

	// get exist in list
	for (int i = 0; i != __list.GetCount(); i++)
	{
		Integer *pInt = static_cast<Integer*> (__list.GetAt(0));
		if (pInt->ToInt() == lesson)
		{
			result = false;
			break;
		}
	}

	// add to list if not exist in list
	if (result)
		result = __list.Add(*(new Integer(lesson))) == E_SUCCESS;
	RELEASE: __mutex.Release();

	return result;
}

bool LessonWorker::IsRunning()
{
	bool isRunning;
	__mutex.Acquire();
	isRunning = __runing;
	__mutex.Release();
	return isRunning;
}

void LessonWorker::LessonAdd(int & lesson, void * vwc)
{
	CommonSetting cs = CommonSetting::GetInstance();
	int ncount, lcount, count;
	wchar_t ** native = LangSetting::GetInitDataN(cs.native, lesson, ncount);
	wchar_t ** lern = LangSetting::GetInitDataN(cs.lern, lesson, lcount);

	count = ncount > lcount ? lcount : ncount;


	WordCtrl * wc = static_cast<WordCtrl*>(vwc);

	for(int i = 0;i < count; i++)
	{
		String n = String(native[i]);
		String l = String(lern[i]);
		Word word(-1, lesson, n, l, 0, 0);
		wc->AddWord(word);
		//Thread::Sleep(1000);
		__mutex.Acquire();

		if(__stop)
		{
			// break
			count = 0;
		}
		__mutex.Release();
	}
}

Object *LessonWorker::Run(void)
{
	int lesson = 0;

	WordCtrl *wc = WordCtrl::GetInstance();

	while (IsWait())
	{
		while (GetLessonFromList(lesson))
		{
			if(lesson > 0)
			{
			    LessonAdd(lesson, wc);
			}
			else
			{
				wc->DeleteLesson(Math::Abs(lesson));
			}

			__mutex.Acquire();
			if (__lwLissener)
				__lwLissener->OnLessonTask(lesson);
			__mutex.Release();
		}
	}
	return null;
}

void LessonWorker::SetLessonWorkerLissener(ILessonWorkerLissener *lesson)
{
	__mutex.Acquire();
	__lwLissener = lesson;
	__mutex.Release();
}

bool LessonWorker::IsWait()
{
	bool wait;
	__mutexWait.Acquire();
	wait = __wait;

	// wait is can set only one time
	// because other will be the cycle in Run
	// will not over
	if(__wait)
		__wait = false;

	__mutexWait.Release();
	return wait;
}

bool LessonWorker::StartWait()
{
	__mutexWait.Acquire();
	__wait = true;
	return true;
}

void LessonWorker::StopWait()
{
	__mutex.Acquire();

	// the running status is will be changed
	// on GetLessonFromList when if still true
	// it means the thread is not checking items in __list
	// ( it is middle on process adding/deleting some lesson )
	// and claimly can be wait removed
	if (__runing && __wait)
		__wait = false;

	// release from StartWait
	__mutexWait.Release();
	__mutex.Release();
}
