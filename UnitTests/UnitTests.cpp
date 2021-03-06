#include "pch.h"
#include "CppUnitTest.h"

#include "../heshTab/HashTable.h"
#include "../heshTab/TrivialDictionary.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace {
	template<class TKey, class TValue>
	void CheckInsert(Dictionary<TKey, TValue>& map)
	{
		map.Set(777, 666);

		Assert::IsTrue(!map.IsSet(555));
		Assert::IsTrue(map.IsSet(777));
		Assert::AreEqual(map.Get(777), 666);
	}
	
	template<class TKey, class TValue>
	void CheckNotFoundException(Dictionary<TKey, TValue>& map)
	{
		try
		{
			map.Get(777);
			Assert::Fail(L"Ожидалось исключение");
		}
		catch (NotFoundException<int>& e)
		{
			Assert::AreEqual(e.GetKey(), 777);
		}
		catch (...)
		{
			Assert::Fail(L"Исключение не того типа");
		}

	}
};



TEST_CLASS(HashTable_IntInt)
{
public:

	using DictionaryImpl = HashTable<int, int>;
	TEST_METHOD(InsertsElement)
	{
		unique_ptr<Dictionary<int, int>> map = make_unique<DictionaryImpl>(); 

		CheckInsert(*map);
	}

	TEST_METHOD(ThrowsException_WhenNoExists)
	{
		unique_ptr<Dictionary<int, int>> map = make_unique<DictionaryImpl>();

		CheckNotFoundException(*map);
	}
};

TEST_CLASS(TrivialDictionary_IntInt)
{
public:
	using DictionaryImpl = TrivialDictionary<int, int>;
	TEST_METHOD(InsertsElement)
	{
		unique_ptr<Dictionary<int, int>> map = make_unique<DictionaryImpl>();

		CheckInsert(*map);
	}

	TEST_METHOD(ThrowsException_WhenNoExists)
	{
		unique_ptr<Dictionary<int, int>> map = make_unique<DictionaryImpl>();

		CheckNotFoundException(*map);
	}
};
