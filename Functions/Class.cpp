#include "../Includes.hpp"

namespace IL2CPP
{
	namespace Class
	{
        Unity::il2cppFieldInfo* GetFields(Unity::il2cppClass* m_pClass, void** m_pIterator)
        {
            return reinterpret_cast<Unity::il2cppFieldInfo*(IL2CPP_CALLING_CONVENTION)(void*, void**)>(Data.Functions.m_pClassGetFields)(m_pClass, m_pIterator);
        }

        void FetchFields(Unity::il2cppClass* m_pClass, std::vector<Unity::il2cppFieldInfo*>* m_pVector, void* m_pFieldIterator)
        {
            m_pVector->clear();

            while (1)
            {
                Unity::il2cppFieldInfo* m_pField = GetFields(m_pClass, &m_pFieldIterator);
                if (!m_pField)
                    break;

                m_pVector->emplace_back(m_pField);
            }
        }

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
            else
            {
                m_pNameSpace = new char[2];
                memset(m_pNameSpace, 0, 2);
            }

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

        namespace Utils
        {
            int GetFieldOffset(Unity::il2cppClass* m_pClass, const char* m_pName)
            {
                void* m_pFieldIterator = nullptr;
                while (1)
                {
                    Unity::il2cppFieldInfo* m_pField = GetFields(m_pClass, &m_pFieldIterator);
                    if (!m_pField)
                        break;

                    if (strcmp(m_pField->m_pName, m_pName) == 0)
                        return m_pField->m_iOffset;
                }

                return 0;
            }

            int GetFieldOffset(const char* m_pClassName, const char* m_pName)
            {
                Unity::il2cppClass* m_pClass = Find(m_pClassName);
                if (m_pClass)
                    return GetFieldOffset(m_pClass, m_pName);

                return 0;
            }

            void* GetMethodPointer(Unity::il2cppClass* m_pClass, const char* m_pMethodName, int m_iArgs)
            {
                Unity::il2cppMethodInfo* pMethod = reinterpret_cast<Unity::il2cppMethodInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*, int)>(Data.Functions.m_pClassGetMethodFromName)(m_pClass, m_pMethodName, m_iArgs);
                if (!pMethod) return nullptr;

                return pMethod->m_pMethodPointer;
            }
        }
	}
}