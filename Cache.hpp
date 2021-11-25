#pragma once

namespace IL2CPP
{
	namespace SystemTypeCache
	{
		void Add(const char* m_pName, Unity::il2cppObject* m_pSystemType);

		Unity::il2cppObject* Find(const char* m_pName);

		namespace Initializer
		{
			extern std::vector<const char*> m_vList;

			void Add(const char* m_pName);

			void PreCache();
		}
	}
}