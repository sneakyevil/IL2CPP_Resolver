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

        Unity::il2cppMethodInfo* GetMethods(Unity::il2cppClass* m_pClass, void** m_pIterator)
        {
            return reinterpret_cast<Unity::il2cppMethodInfo*(IL2CPP_CALLING_CONVENTION)(void*, void**)>(Data.Functions.m_pClassGetMethods)(m_pClass, m_pIterator);
        }

        void FetchMethods(Unity::il2cppClass* m_pClass, std::vector<Unity::il2cppMethodInfo*>* m_pVector, void* m_pMethodIterator)
        {
            m_pVector->clear();

            while (1)
            {
                Unity::il2cppMethodInfo* m_pMethod = GetMethods(m_pClass, &m_pMethodIterator);
                if (!m_pMethod)
                    break;

                m_pVector->emplace_back(m_pMethod);
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

        Unity::il2cppObject* GetSystemType(const char* m_pClassName)
        {
            Unity::il2cppClass* m_pClass = Find(m_pClassName);
            if (!m_pClass)
                return nullptr;

            return GetSystemType(m_pClass);
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

        void FetchClasses(std::vector<Unity::il2cppClass*>* m_pVector, const char* m_pModuleName, const char* m_pNamespace)
        {
            m_pVector->clear();

            size_t m_sAssembliesCount = 0U;
            Unity::il2cppAssembly** m_pAssemblies = Domain::GetAssemblies(&m_sAssembliesCount);
            if (!m_pAssemblies || 0U >= m_sAssembliesCount) return;

            Unity::il2cppImage* m_pImage = nullptr;
            for (size_t i = 0U; m_sAssembliesCount > i; ++i)
            {
                Unity::il2cppAssembly* m_pAssembly = m_pAssemblies[i];
                if (!m_pAssembly || !m_pAssembly->m_pImage || strcmp(m_pAssembly->m_pImage->m_pNameNoExt, m_pModuleName) != 0)
                    continue;

                m_pImage = m_pAssembly->m_pImage;
                break;
            }

            if (m_pImage)
            {
                size_t m_sClassesCount = reinterpret_cast<size_t(IL2CPP_CALLING_CONVENTION)(void*)>(Data.Functions.m_pImageGetClassCount)(m_pImage);
                for (size_t i = 0U; m_sClassesCount > i; ++i)
                {
                    Unity::il2cppClass* m_pClass = reinterpret_cast<Unity::il2cppClass*(IL2CPP_CALLING_CONVENTION)(void*, size_t)>(Data.Functions.m_pImageGetClass)(m_pImage, i);
                    if (m_pNamespace)
                    {
                        if (m_pNamespace[0] == '\0')
                        {
                            if (m_pClass->m_pNamespace[0] != '\0')
                                continue;
                        }
                        else if (strcmp(m_pClass->m_pNamespace, m_pNamespace) != 0)
                            continue;
                    }

                    m_pVector->emplace_back(m_pClass);
                }
            }
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

                return -1;
            }

            int GetFieldOffset(const char* m_pClassName, const char* m_pName)
            {
                Unity::il2cppClass* m_pClass = Find(m_pClassName);
                if (m_pClass)
                    return GetFieldOffset(m_pClass, m_pName);

                return -1;
            }

            void* GetMethodPointer(Unity::il2cppClass* m_pClass, const char* m_pMethodName, int m_iArgs)
            {
                Unity::il2cppMethodInfo* pMethod = reinterpret_cast<Unity::il2cppMethodInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*, int)>(Data.Functions.m_pClassGetMethodFromName)(m_pClass, m_pMethodName, m_iArgs);
                if (!pMethod) return nullptr;

                return pMethod->m_pMethodPointer;
            }

            void* GetMethodPointer(const char* m_pClassName, const char* m_pMethodName, int m_iArgs)
            {
                Unity::il2cppClass* m_pClass = Find(m_pClassName);
                if (m_pClass)
                    return GetMethodPointer(m_pClass, m_pMethodName, m_iArgs);

                return nullptr;
            }

	        void* GetMethodPointer(const char* m_pClassName, const char* m_pMethodName, std::initializer_list<const char*> m_vNames)
            {
                Unity::il2cppClass* m_pClass = Find(m_pClassName);
                if (!m_pClass)
                    return nullptr;

                int m_iNamesCount       = static_cast<int>(m_vNames.size());
                const char** m_pNames   = const_cast<const char**>(m_vNames.begin());

                void* m_pMethodIterator = nullptr;
                while (1)
                {
                    Unity::il2cppMethodInfo* m_pMethod = GetMethods(m_pClass, &m_pMethodIterator);
                    if (!m_pMethod)
                        break;

                    if (strcmp(m_pMethod->m_pName, m_pMethodName) != 0)
                        continue;

                    Unity::il2cppParameterInfo* m_pCurrentParameters = m_pMethod->m_pParameters;
                    for (int i = 0; m_iNamesCount > i; ++i)
                    {
                        if (strcmp(m_pCurrentParameters->m_pName, m_pNames[i]) != 0)
                            break;

                        m_pCurrentParameters++; // m_pCurrentParameters += sizeof(Unity::il2cppParameterInfo);
                        if ((i + 1) == m_iNamesCount)
                            return m_pMethod->m_pMethodPointer;
                    }
                }
                return nullptr;
            }
		
            Unity::il2cppClass* FilterClass(std::vector<Unity::il2cppClass*>* m_pClasses, std::initializer_list<const char*> m_vNames, int m_iFoundCount)
            {
                int m_iNamesCount = static_cast<int>(m_vNames.size());
                const char** m_pNames = const_cast<const char**>(m_vNames.begin());

                if (0 >= m_iFoundCount || m_iFoundCount > m_iNamesCount)
                    m_iFoundCount = m_iNamesCount;

                Unity::il2cppClass* m_pReturn = nullptr;
                for (size_t c = 0; m_pClasses->size() > c; ++c)
                {
                    int m_iFoundCountNow = 0;

                    Unity::il2cppClass* m_pClass = m_pClasses->operator[](c);
                    if (!m_pClass)
                        continue;

                    for (int i = 0; m_iNamesCount > i; ++i)
                    {
                        const char* m_pNameToFind = m_pNames[i];

                        bool m_bFoundInClass = false;
                        if (m_pNameToFind[0] == '~') // Field
                            m_bFoundInClass = GetFieldOffset(m_pClass, &m_pNameToFind[1]) >= 0;
                        else if (m_pNameToFind[0] == '-') // Method
                            m_bFoundInClass = GetMethodPointer(m_pClass, &m_pNameToFind[1]) != nullptr;
                        else // Both
                        {
                            m_bFoundInClass = GetFieldOffset(m_pClass, m_pNameToFind) >= 0;
                            if (!m_bFoundInClass)
                                m_bFoundInClass = GetMethodPointer(m_pClass, m_pNameToFind) != nullptr;
                        }

                        if (m_bFoundInClass)
                            ++m_iFoundCountNow;
                    }

                    if (m_iFoundCount == m_iFoundCountNow)
                    {
                        m_pReturn = m_pClass;
                        break;
                    }
                }

                return m_pReturn;
            }

            void* FilterClassToMethodPointer(std::vector<Unity::il2cppClass*>* m_pClasses, const char* m_pMethodName, int m_iArgs)
            {
                void* m_pMethodPointer = nullptr;
                for (size_t c = 0; m_pClasses->size() > c; ++c)
                {
                    Unity::il2cppClass* m_pClass = m_pClasses->operator[](c);
                    if (!m_pClass)
                        continue;

                    m_pMethodPointer = GetMethodPointer(m_pClass, m_pMethodName, m_iArgs);
                    if (m_pMethodPointer)
                        break;
                }

                return m_pMethodPointer;
            }
        }
	}
}
