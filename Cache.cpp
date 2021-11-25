#include "Includes.hpp"

namespace IL2CPP
{
	namespace SystemTypeCache
	{
		class CCache
		{
		public:
			const char* m_pName = nullptr;
			Unity::il2cppObject* m_pSystemType = nullptr;

			CCache() { }
			CCache(const char* m_pKey, Unity::il2cppObject* m_pValue)
			{
				m_pName = m_pKey;
				m_pSystemType = m_pValue;
			}
		};
		std::vector<CCache> m_vCache;

		void Add(const char* m_pName, Unity::il2cppObject* m_pSystemType)
		{
			if (!m_pName || !m_pSystemType)
				return;

			m_vCache.emplace_back(CCache(m_pName, m_pSystemType));
		}

		Unity::il2cppObject* Find(const char* m_pName)
		{
			size_t m_sSize = m_vCache.size();
			if (m_sSize > 0)
			{
				CCache* m_pData = m_vCache.data();
				for (size_t i = 0; m_sSize > i; ++i)
				{
					if (m_pData[i].m_pName == m_pName)
						return m_pData[i].m_pSystemType;
				}
			}

			return nullptr;
		}

		namespace Initializer
		{
			std::vector<const char*> m_vList;

			void Add(const char* m_pName) { m_vList.emplace_back(m_pName); }

			void PreCache()
			{
				for (const char* m_pName : m_vList)
					SystemTypeCache::Add(m_pName, IL2CPP::Class::GetSystemType(m_pName));

				m_vList.clear();
			}
		}
	}
}