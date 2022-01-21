#pragma once

namespace IL2CPP
{
	namespace SystemTypeCache
	{
		void Add(unsigned int m_uHash, Unity::il2cppObject* m_pSystemType);

		void Add(const char* m_pName, Unity::il2cppObject* m_pSystemType);

		Unity::il2cppObject* Find(unsigned int m_uHash);

		Unity::il2cppObject* Find(const char* m_pName);

		namespace Initializer
		{
			extern std::vector<const char*> m_vList;

			/*
			* (WARNING) this needs to be called before actual IL2CPP Resolver Init, otherwise use function Add outside Initializer namespace!
			*/
			void Add(const char* m_pName);

			void PreCache();
		}
	}
}