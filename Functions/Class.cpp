#include "../Includes.hpp"

namespace IL2CPP
{
	namespace Class
	{
        Unity::il2cppType* GetType(Unity::il2cppClass* m_pClass)
        {
            return reinterpret_cast<Unity::il2cppType*(IL2CPP_CALLING_CONVENTION)(void*)>(Data.Functions.m_pClassGetType)(m_pClass);
        }

        Unity::il2cppObject* GetSystemType(Unity::il2cppClass* m_pClass)
        {
            return reinterpret_cast<Unity::il2cppObject*(IL2CPP_CALLING_CONVENTION)(void*)>(Data.Functions.m_pTypeGetObject)(GetType(m_pClass));
        }

        Unity::il2cppClass* GetFromName(Unity::il2cppImage* m_pImage, const char* m_pNamespace, const char* m_pName)
        {
            return reinterpret_cast<Unity::il2cppClass*(IL2CPP_CALLING_CONVENTION)(void*, const char*, const char*)>(Data.Functions.m_pClassFromName)(m_pImage, m_pNamespace, m_pName);
        }

		Unity::il2cppClass* Find(const char* m_pName)
		{
            size_t m_sAssembliesCount = 0U;
            Unity::il2cppAssembly** m_pAssemblies = Domain::GetAssemblies(&m_sAssembliesCount);
            if (!m_pAssemblies || 0U >= m_sAssembliesCount) return nullptr;

            const char* m_pNameSpaceEnd = strrchr(m_pName, '.');
            char* m_pNameSpace = nullptr;
            if (m_pNameSpaceEnd)
            {
                uintptr_t m_uNamespaceSize = static_cast<uintptr_t>(m_pNameSpaceEnd - m_pName);
                m_pNameSpace = new char[m_uNamespaceSize + 1];
                memcpy(m_pNameSpace, m_pName, m_uNamespaceSize);
                m_pNameSpace[m_uNamespaceSize] = '\0';

                m_pName = m_pNameSpaceEnd + 1;
            }
            else m_pNameSpace = new char[2];

            Unity::il2cppClass* m_pClassReturn = nullptr;
            for (size_t i = 0U; m_sAssembliesCount > i; ++i)
            {
                Unity::il2cppAssembly* m_pAssembly = m_pAssemblies[i];
                if (!m_pAssembly || !m_pAssembly->m_pImage) continue;

                m_pClassReturn = GetFromName(m_pAssembly->m_pImage, m_pNameSpace, m_pName);
                if (m_pClassReturn) break;
            }

            delete[] m_pNameSpace;
            return m_pClassReturn;
		}
	}
}