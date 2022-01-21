#pragma once

namespace Unity
{
	// Don't use! Untested
	template<typename T>
	struct il2cppDictionary : il2cppObject
	{
		il2cppArray<int>* m_pBuckets;
		il2cppArray<T>* m_pEntries;
		int m_iCount;
		int m_iVersion;
		int m_iFreeList;
		int m_iFreeCount;
		void* m_pComparer;
		void* m_pKeys;
		void* m_pValues;
	};
}