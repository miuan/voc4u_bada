/*
 * LessonWorker.h
 *
 *  Created on: 17.11.2011
 *      Author: m1uan
 */
#ifndef LESSONWORKER_H_
#define LESSONWORKER_H_

#include <FIo.h>
#include <FBase.h>

using namespace Osp::Io;
using namespace Osp::Base;
using namespace Osp::Base::Runtime;
using namespace Osp::Base::Collection;
using namespace Osp::Base::Utility;

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
    void LessonAdd(int & lesson, void * wc);

public:
	LessonWorker();
	~LessonWorker();

public:

	int *GetLessonInProgressN(int &count);
	bool GetLessonFromList(int & lesson);
	bool AddLesson(int lesson, bool remove);

	bool IsRunning();
	Object *Run(void);

	void SetLessonWorkerLissener(ILessonWorkerLissener *lesson);

	bool IsWait();
	bool StartWait();
	void StopWait();
};

#endif /* LESSONWORKER_H_ */
