/*
 * WordCtrl.h
 *
 *  Created on: 6.11.2011
 *      Author: m1uan
 */

#ifndef WORDCTRL_H_
#define WORDCTRL_H_

#include "Word.h"
#include <FIo.h>
#include <FBase.h>

using namespace Osp::Io;
using namespace Osp::Base;
using namespace Osp::Base::Runtime;
using namespace Osp::Base::Collection;

#define DB_NAME L"/Home/testingDatabase"

#define TABLE_NAME L"t_words"
#define COLUMN_LWEIGHT L"lweight"
#define COLUMN_NWEIGHT L"nweight"
#define COLUMN_NATIVE L"native"
#define COLUMN_LERN L"lern"
#define COLUMN_USER_CHANGE L"user"
#define COLUMN_LESSON L"lesson"
#define COLUMN_ID L"id"

#define INSERT_TABLE L"CREATE TABLE IF NOT EXISTS %ls\
		(%ls INTEGER PRIMARY KEY AUTOINCREMENT,\
		%ls INTEGER,\
		%ls VCHAR(100),\
		%ls VCHAR(100),\
		%ls INTEGER,\
		%ls INTEGER,\
		%ls INTEGER)"

#define LESSON_EXISTS L"SELECT COUNT(*) FROM %S WHERE %S = %d"



class ILessonWorkerLissener
{
public:
	ILessonWorkerLissener()
	{
	}
	;
	virtual ~ILessonWorkerLissener()
	{
	}
	;
public:

	virtual void OnLessonTask(const int lesson) = 0;
};

class LessonWorker: public Osp::Base::Runtime::Thread
{
	/**
	 * mutex
	 */
	Mutex __mutex;
	Mutex __mutexWait;
	/**
	 * is now working or not
	 */
	bool __runing;

	/**
	 * can continu in Run process
	 * because user can stop the adding proces uncheck the lesson
	 */
	bool __stop;

	/**
	 * list with other works, lesson waiting to do (add, remove)
	 */
	ArrayList __list;

	/*
	 * lesson already worket on
	 */
	int __currentLesson;

	/**
	 * i can't explain it (magic variable)
	 */
	bool __wait;
	/**
	 * after every lesson done (add, remove) is called
	 * ILessonWorkerLissener::OnLessonDone
	 */
	ILessonWorkerLissener * __lwLissener;

public:
	LessonWorker()
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

	~LessonWorker()
	{

	}

public:

	bool GetLessonFromList(int & lesson)
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
		}
		__mutex.Release();

		return lesson != 0;
	}

	bool AddLesson(int lesson, bool remove)
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

	bool IsRunning()
	{
		bool isRunning;
		__mutex.Acquire();
		isRunning = __runing;
		__mutex.Release();
		return isRunning;
	}

	Object *Run(void)
	{
		int lesson = 0;

		while (IsWait())
		{
			while (GetLessonFromList(lesson))
			{
				// TODO: add lessons

				__mutex.Acquire();
				if (__lwLissener)
					__lwLissener->OnLessonTask(lesson);
				__mutex.Release();
			}
		}
		return null;
	}

	void SetLessonWorkerLissener(ILessonWorkerLissener *lesson)
	{
		__mutex.Acquire();
		__lwLissener = lesson;
		__mutex.Release();
	}

	bool IsWait()
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

	bool StartWait()
	{
		__mutexWait.Acquire();
		__wait = true;
		return true;
	}

	void StopWait()
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
};

class WordCtrl : public ILessonWorkerLissener
{
private:
	static WordCtrl *__wc;
	Database *__db;

	LessonWorker *__lw;
	ILessonWorkerLissener * __lwLissener;
private:
	result PrepareDB();
    void CreateLessonWorker();
public:
    WordCtrl();
    virtual ~WordCtrl();
    result Init();
    static WordCtrl *GetInstance();
    bool AddWord(Word & word);
    bool GetLessonEnabled(const int lesson);
    bool AddLesson(const int lesson, bool remove);
    void SetLessonWorkerListener(ILessonWorkerLissener *ilwl);
    virtual void OnLessonTask(const int lesson);
};

#endif /* WORDCTRL_H_ */
