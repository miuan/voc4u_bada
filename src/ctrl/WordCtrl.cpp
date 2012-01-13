/*
 * WordCtrl.cpp
 *
 *  Created on: 6.11.2011
 *      Author: m1uan
 */

#include "WordCtrl.h"

using namespace Osp::Base::Collection;

WordCtrl * WordCtrl::__wc = null;

WordCtrl::WordCtrl() :
	__db(null), __lw(null), __lwLissener(null), __pFirstWords(null)
{
}

WordCtrl::~WordCtrl()
{
	if (__lw)
	{
		__lw->SetLessonWorkerLissener(null);

		while (__lw->IsRunning())
			Thread::Sleep(1000);

		delete __lw;
	}
	if (__db)
		delete __db;
}

WordCtrl * WordCtrl::GetInstance()
{
	if (!__wc)
	{
		__wc = new WordCtrl();
		__wc->Init();
	}

	return __wc;
}

int WordCtrl::GetWordCount(const WORD_TYPE type, const int lesson)
{
	String sql;
	String where;

	where = PrepareWordWhere(type, lesson);

	sql.Format(1000, WORD_COUNT, TABLE_NAME);
	if (where.GetLength() > 0)
	{
		sql.Append(" WHERE ");
		sql.Append(where);
	}

	AppLogDebug("SQL: (%S)", sql.GetPointer());
	DbEnumerator* pEnum = __db->QueryN(sql);

	int count = 0;
	if (pEnum)
	{
		while (pEnum->MoveNext() == E_SUCCESS)
		{
			pEnum->GetIntAt(0, count);
			break;
		}

		delete pEnum;
	}

	return count;
}

bool WordCtrl::GetLessonLoaded(const int lesson)
{
	return GetWordCount(WORD_TYPE_ALL, lesson) > 0;
}

result WordCtrl::PrepareDB()
{
	result r;
	String sql;
	sql.Format(1000, INSERT_TABLE, TABLE_NAME, COLUMN_ID, COLUMN_LESSON, COLUMN_LERN, COLUMN_NATIVE, COLUMN_LWEIGHT, COLUMN_NWEIGHT, COLUMN_USER_CHANGE);

	AppLogDebug("SQL: (%ls)", sql.GetPointer());
	r = __db->ExecuteSql(sql, true);

	if (IsFailed(r))
	{
		AppLog("DB not initialized (%1s)", GetErrorMessage(r));
		return r;
	}

	return r;
}

result WordCtrl::Init()
{
	result r = E_SUCCESS;
	__db = new Database();

	if (!Database::Exists(DB_NAME))
	{
		__db->Construct(DB_NAME, true);
		r = PrepareDB();
	}
	else __db->Construct(DB_NAME, false);

	return r;
}

bool WordCtrl::AddWord(Word &word)
{
	String statement;

	if (__db->BeginTransaction() != E_SUCCESS)
		return false;

	statement.Format(1000, L"INSERT INTO %S (%S, %S, %S, %S, %S, %S) VALUES (?, ?, ?, ?, ?, ?)", TABLE_NAME, COLUMN_LESSON, COLUMN_LERN, COLUMN_NATIVE, COLUMN_LWEIGHT,
			COLUMN_NWEIGHT, COLUMN_USER_CHANGE);

	DbStatement * pStmt = __db->CreateStatementN(statement);

	pStmt->BindInt(0, word.__lesson);
	pStmt->BindString(1, word.__lern);
	pStmt->BindString(2, word.__native);
	pStmt->BindInt(3, word.__lweight);
	pStmt->BindInt(4, word.__nweight);
	pStmt->BindInt(5, 0);

	DbEnumerator * pEnum = __db->ExecuteStatementN(*pStmt);

	__db->CommitTransaction();

	delete pEnum;
	delete pStmt;

	AppLogDebug("word: %S - %S", word.__lern.GetPointer(), word.__native.GetPointer());
	return true;
}

void WordCtrl::CreateLessonWorker()
{
	// delete and create new LessonWorker
	__lw = new LessonWorker();
	__lw->Construct();
	__lw->SetLessonWorkerLissener(this);
}

bool WordCtrl::LoadLesson(const int lesson, bool unload)
{
	bool createnew = false;

	if (!__lw)
	{
		CreateLessonWorker();
		createnew = true;
	}
	else
	{
		// set wait because, the __lw
		// can be on end of add/removing cycle
		// set wait on this cycle for try GetLessonFromList
		__lw->StartWait();
	}

	// the __lw is finished yet
	// you can create new therad
	// because old thread isn't abble to start again
	if (!createnew && !__lw->IsRunning())
	{
		__lw->StopWait();
		delete __lw;
		__lw = null;

		CreateLessonWorker();
		createnew = true;
	}

	// add/remove lesson at lesson
	bool result = __lw->AddLesson(lesson, unload);

	// it was create new start new thread
	// otherwise call StopWait -> continue cycle in Run
	if (createnew)
		__lw->Start();
	else __lw->StopWait();

	return result;
}

void WordCtrl::SetLessonWorkerListener(ILessonWorkerLissener *ilwl)
{
	__lwLissener = ilwl;

}

void WordCtrl::OnLessonTask(const int lesson)
{
	if (__lwLissener)
		__lwLissener->OnLessonTask(lesson);
}

int * WordCtrl::GetWorkerTaskLessonInProgressN(int &count)
{
	if (__lw && __lw->IsRunning())
		return __lw->GetLessonInProgressN(count);
	else
	{
		count = 0;
		return null;
	}
}
//#define SELECT_WORD L"SELECT %S %S, %S, %S, %S, %S, %S FROM %S ORDER BY DESC %S, %S"
String WordCtrl::SQLSelectWord(String where = L"", String limit = L"")
{
	String sql;
	String table = TABLE_NAME;
	String orderby = COLUMN_NWEIGHT;

	if (where.GetLength() > 0)
	{
		table.Append(" WHERE ");
		table.Append(where);
	}

	sql.Format(1000, SELECT_WORD, COLUMN_ID, COLUMN_LESSON, COLUMN_LERN, COLUMN_NATIVE, COLUMN_LWEIGHT, COLUMN_NWEIGHT, COLUMN_USER_CHANGE, table.GetPointer(), COLUMN_LWEIGHT,
			COLUMN_NWEIGHT, limit.GetPointer());
	return sql;
}

Word * WordCtrl::CreateWordFromDbEnumeratorN(DbEnumerator & pEnum)
{
	int id, lesson, lweight, nweight, userchanged;
	String native, lern;

	pEnum.GetIntAt(0, id);
	pEnum.GetIntAt(1, lesson);
	pEnum.GetStringAt(2, lern);
	pEnum.GetStringAt(3, native);
	pEnum.GetIntAt(4, lweight);
	pEnum.GetIntAt(5, nweight);
	pEnum.GetIntAt(6, userchanged);

	return new Word(id, lesson, lern, native, lweight, nweight);
}

String WordCtrl::PrepareWordWhere(const WORD_TYPE type, const int lesson)
{
	String where = L"";
	if (type == WORD_TYPE_ENABLED)
	{
		where.Format(1000, L"%S > 0 AND %S > 0", COLUMN_LWEIGHT, COLUMN_NWEIGHT);
		if (lesson != -1)
			where.Append(" ");
	}
	else if (type == WORD_TYPE_ENABLED_DONTKNOW)
	{
		where.Format(1000, L"%S = 1 OR %S = 1", COLUMN_LWEIGHT, COLUMN_NWEIGHT);
		if (lesson != -1)
			where.Append(" ");
	}
	else if (type == WORD_TYPE_DISABLED)
	{
		where.Format(1000, L"%S = 0 AND %S = 0", COLUMN_LWEIGHT, COLUMN_NWEIGHT);
		if (lesson != -1)
			where.Append(" ");
	}

	if (lesson != -1)
	{
		where.Append(COLUMN_LESSON);
		where.Append("= ");
		where.Append(lesson);
	}

	return where;
}

ArrayList * WordCtrl::GetWordsN(const int lesson, const int limit, const WORD_TYPE type, ArrayList * withoutWords)
{
	result r;
	int withoutCount = withoutWords ? withoutWords->GetCount() : 0;
	ArrayList *result = null;
	String where = L"";
	String sqllimit = L"";

	where = PrepareWordWhere(type, lesson);

	// prepare where for
	if (withoutCount)
	{
		if (where.GetLength() > 0)
			where.Append(" AND ");

		for (int i = 0; i < withoutCount; i++)
		{
			String condition;
			Word *word = static_cast<Word *> (withoutWords->GetAt(i));
			condition.Format(1000, L"%S <> %d AND ", COLUMN_ID, word->__id);
			where.Append(condition);
		}
		// remove last AND
		where.Remove(where.GetLength() - 4, 4);
	}

	if (limit)
	{
		sqllimit.Append("LIMIT ");
		sqllimit.Append(limit);
	}
	//where.Append(lesson);
	String sql = SQLSelectWord(where, sqllimit);

	AppLogDebug("SQL: (%S)", sql.GetPointer());
	DbStatement * pStmt = __db->CreateStatementN(sql);

	//if (lesson != -1)
	//	pStmt->BindInt(0, lesson);

	DbEnumerator* pEnum = __db->ExecuteStatementN(*pStmt);

	// pEnum = __db->QueryN(sql);
	if (!pEnum)
	{
		AppLog("QueryN not initialized (%1s)", GetErrorMessage(GetLastResult()));
	}

	int count = 0;
	if (pEnum)
	{
		while (pEnum->MoveNext() == E_SUCCESS)
		{
			Word * w;

			w = CreateWordFromDbEnumeratorN(*pEnum);

			if (!result)
			{
				result = new ArrayList();
				result->Construct();
			}

			result->Add(*w);
		}

		delete pEnum;
	}

	delete pStmt;

	return result;
}

void WordCtrl::FillFirstWordsArray(ArrayList *lastList)
{
	ArrayList *list;
	//ArrayList *words = null;
	EnableNextWords();
	// if in the DB fewer word or the same as in Lastlist
	// make new last list with DB maximum -1
	// the last list is countet from end because
	// last word was showed recently
	int count = GetWordCount(WORD_TYPE_ENABLED);
	if (lastList && count <= lastList->GetCount())
	{
		int countLL = lastList->GetCount();
		ArrayList array;
		array.Construct(count);
		int min = countLL - count;
		for (int i = countLL - 1; i > min; i--)
		{
			Word *word = static_cast<Word*> (lastList->GetAt(i));
			array.Add(*word);
		}
		// get word from any lessons (-1) and set limit to only one (1)
		list = GetWordsN(-1, 15, WORD_TYPE_ENABLED, &array);
	}
	else
	{
		// get word from any lessons (-1) and set limit to only one (1)
		list = GetWordsN(-1, 15, WORD_TYPE_ENABLED, lastList);
	}

	if (list)
	{
		if (list->GetCount() > 0)
		{
			if (__pFirstWords == null)
				__pFirstWords = new ArrayList();

			IEnumerator * enumlist = list->GetEnumeratorN();
			while (enumlist->MoveNext() == E_SUCCESS)
			{
				__pFirstWords->Add(*(enumlist->GetCurrent()));
			}
		}

		list->RemoveAll(false);
		delete list;
	}
}

Word * WordCtrl::GetFirstWordN(ArrayList *lastList)
{
	Word *word = null;

	if (!__pFirstWords || __pFirstWords->GetCount() < 1)
		FillFirstWordsArray(lastList);

	if (__pFirstWords && __pFirstWords->GetCount() > 0)
	{
		int rand = Osp::Base::Utility::Math::Rand() % __pFirstWords->GetCount();
		word = (Word*) (__pFirstWords->GetAt(rand));
		__pFirstWords->RemoveAt(rand, false);
	}

	return word;
}

String WordCtrl::SQLUpdateWord()
{
	String update;
	update.Format(2000, UPDATE_TABLE, TABLE_NAME, COLUMN_LERN, COLUMN_NATIVE, COLUMN_LWEIGHT, COLUMN_NWEIGHT, COLUMN_USER_CHANGE, COLUMN_ID);
	return update;
}

bool WordCtrl::UpdateWord(Word & word)
{
	String update = SQLUpdateWord();

	__db->BeginTransaction();

	AppLogDebug("update sql : (%S)", update.GetPointer());
	DbStatement * pStmt = __db->CreateStatementN(update);
	result r = GetLastResult();
	if (IsFailed(r))
	{
		AppLog("statement failed with: %s", GetErrorMessage(r));
	}

	if (pStmt)
	{
		pStmt->BindString(0, word.__lern);
		pStmt->BindString(1, word.__native);
		pStmt->BindInt(2, word.__lweight);
		pStmt->BindInt(3, word.__nweight);
		pStmt->BindInt(4, word.__user);
		pStmt->BindInt(5, word.__id);

		DbEnumerator * pEnum = __db->ExecuteStatementN(*pStmt);
		__db->CommitTransaction();

		delete pEnum;
		delete pStmt;
	}
	else
	{
		__db->RollbackTransaction();
	}
	return true;
}

bool WordCtrl::DeleteLesson(const int lesson)
{
	String statement;

	if (__db->BeginTransaction() != E_SUCCESS)
		return false;

	if (lesson > 0)
		statement.Format(1000, L"DELETE FROM %S WHERE %S = ?", TABLE_NAME, COLUMN_LESSON);
	else statement.Format(1000, L"DELETE FROM %S", TABLE_NAME);

	DbStatement * pStmt = __db->CreateStatementN(statement);

	if (lesson > 0)
		pStmt->BindInt(0, lesson);

	DbEnumerator * pEnum = __db->ExecuteStatementN(*pStmt);

	__db->CommitTransaction();

	delete pEnum;
	delete pStmt;

	AppLog("Delete lesson: %d", lesson);
	return true;
}

bool WordCtrl::EnableNextWords()
{
	int countDK = GetWordCount(WORD_TYPE_ENABLED_DONTKNOW);

	// experiment
	// when have 3 word which youd dont know absolutly
	if (countDK > 2)
		return false;

	AppLog("enable next 5 words!!!");

	// experiment
	// enable 7 new words
	ArrayList *list = GetWordsN(-1, 7, WORD_TYPE_DISABLED);
	if (list)
	{
		for (int i = 0; i < list->GetCount(); i++)
		{
			Word * word = (Word*) list->GetAt(i);
			word->__lweight = 1;
			word->__nweight = 1;
			UpdateWord(*word);
		}

		list->RemoveAll(true);
		delete list;
	}
	return true;
}
