#include "Includes.hpp"

namespace IL2CPP
{
	namespace SystemTypeCache
	{
		class CCache
		{
		public:
			unsigned int m_uHash = 0U;
			Unity::il2cppObject* m_pSystemType = nullptr;

			CCache() { }
			CCache(unsigned int m_uKey, Unity::il2cppObject* m_pValue)
			{
				m_uHash = m_uKey;
				m_pSystemType = m_pValue;
			}
		};
		std::vector<CCache> m_vCache;

		void Add(unsigned int m_uHash, Unity::il2cppObject* m_pSystemType)
		{
			if (!m_pSystemType)
				return;

			m_vCache.emplace_back(CCache(m_uHash, m_pSystemType));
		}

		void Add(const char* m_pName, Unity::il2cppObject* m_pSystemType)
		{
			if (!m_pName)
				return;

			Add(Utils::JOAAT(m_pName), m_pSystemType);
		}

		Unity::il2cppObject* Find(unsigned int m_uHash)
		{
			size_t m_sSize = m_vCache.size();
			if (m_sSize > 0)
			{
				CCache* m_pData = m_vCache.data();
				for (size_t i = 0; m_sSize > i; ++i)
				{
					if (m_pData[i].m_uHash == m_uHash)
						return m_pData[i].m_pSystemType;
				}
			}

			return nullptr;
		}

		Unity::il2cppObject* Find(const char* m_pName)
		{
			return Find(Utils::JOAAT(m_pName));
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