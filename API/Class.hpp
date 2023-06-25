#pragma once

namespace IL2CPP
{
    namespace Class
    {
        Unity::il2cppFieldInfo* GetFields(Unity::il2cppClass* m_pClass, void** m_pIterator)
        {
            return reinterpret_cast<Unity::il2cppFieldInfo * (IL2CPP_CALLING_CONVENTION)(void*, void**)>(Functions.m_ClassGetFields)(m_pClass, m_pIterator);
        }

        void FetchFields(Unity::il2cppClass* m_pClass, std::vector<Unity::il2cppFieldInfo*>* m_pVector, void* m_pFieldIterator = nullptr)
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
            return reinterpret_cast<Unity::il2cppMethodInfo * (IL2CPP_CALLING_CONVENTION)(void*, void**)>(Functions.m_ClassGetMethods)(m_pClass, m_pIterator);
        }

        void FetchMethods(Unity::il2cppClass* m_pClass, std::vector<Unity::il2cppMethodInfo*>* m_pVector, void* m_pMethodIterator = nullptr)
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
            return reinterpret_cast<Unity::il2cppType * (IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ClassGetType)(m_pClass);
        }

        Unity::il2cppObject* GetSystemType(Unity::il2cppClass* m_pClass)
        {
            return reinterpret_cast<Unity::il2cppObject * (IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_TypeGetObject)(GetType(m_pClass));
        }

        Unity::il2cppClass* GetFromName(Unity::il2cppImage* m_pImage, const char* m_pNamespace, const char* m_pName)
        {
            return reinterpret_cast<Unity::il2cppClass * (IL2CPP_CALLING_CONVENTION)(void*, const char*, const char*)>(Functions.m_ClassFromName)(m_pImage, m_pNamespace, m_pName);
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

        Unity::il2cppObject* GetSystemType(const char* m_pClassName)
        {
            Unity::il2cppClass* m_pClass = Find(m_pClassName);
            if (!m_pClass)
                return nullptr;

            return GetSystemType(m_pClass);
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
                size_t m_sClassesCount = reinterpret_cast<size_t(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ImageGetClassCount)(m_pImage);
                for (size_t i = 0U; m_sClassesCount > i; ++i)
                {
                    Unity::il2cppClass* m_pClass = reinterpret_cast<Unity::il2cppClass * (IL2CPP_CALLING_CONVENTION)(void*, size_t)>(Functions.m_ImageGetClass)(m_pImage, i);
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

            void* GetMethodPointer(Unity::il2cppClass* m_pClass, const char* m_pMethodName, int m_iArgs = -1)
            {
                Unity::il2cppMethodInfo* pMethod = reinterpret_cast<Unity::il2cppMethodInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*, int)>(Functions.m_ClassGetMethodFromName)(m_pClass, m_pMethodName, m_iArgs);
                if (!pMethod) return nullptr;

                return pMethod->m_pMethodPointer;
            }

            void* GetMethodPointer(const char* m_pClassName, const char* m_pMethodName, int m_iArgs = -1)
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

                int m_iNamesCount = static_cast<int>(m_vNames.size());
                const char** m_pNames = const_cast<const char**>(m_vNames.begin());

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

            Unity::il2cppClass* FilterClass(std::vector<Unity::il2cppClass*>* m_pClasses, std::initializer_list<const char*> m_vNames, int m_iFoundCount = -1)
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

            void* FilterClassToMethodPointer(std::vector<Unity::il2cppClass*>* m_pClasses, const char* m_pMethodName, int m_iArgs = -1)
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

    enum class m_eClassPropType : int
    {
        Unknown = 0,
        Field,			// Member of class that can be accessed directly by RVA
        Property,		// Member of class that can be accessed by calling function
        Method,			// Function of class
    };

    // Main Class
    class CClass
    {
    public:
        Unity::il2cppObject m_Object = { 0 };
        void* m_CachedPtr = nullptr;

        // Wrappers for namespace, ah...
        Unity::il2cppFieldInfo* GetFields(void** m_pIterator)
        {
            return Class::GetFields(m_Object.m_pClass, m_pIterator);
        }

        void FetchFields(std::vector<Unity::il2cppFieldInfo*>* m_pVector, void* m_pFieldIterator = nullptr)
        {
            Class::FetchFields(m_Object.m_pClass, m_pVector, m_pFieldIterator);
        }

        Unity::il2cppMethodInfo* GetMethods(void** m_pIterator)
        {
            return Class::GetMethods(m_Object.m_pClass, m_pIterator);
        }

        void FetchMethods(std::vector<Unity::il2cppMethodInfo*>* m_pVector, void* m_pMethodIterator = nullptr)
        {
            Class::FetchMethods(m_Object.m_pClass, m_pVector, m_pMethodIterator);
        }

        void* GetMethodPointer(const char* m_pMethodName, int m_iArgs = -1)
        {
            return Class::Utils::GetMethodPointer(m_Object.m_pClass, m_pMethodName, m_iArgs);
        }

        m_eClassPropType GetPropType(const char* m_pPropType)
        {
            Unity::il2cppFieldInfo* pField = reinterpret_cast<Unity::il2cppFieldInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetFieldFromName)(m_Object.m_pClass, m_pPropType);
            if (pField)
                return m_eClassPropType::Field;

            Unity::il2cppPropertyInfo* pProperty = reinterpret_cast<Unity::il2cppPropertyInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetPropertyFromName)(m_Object.m_pClass, m_pPropType);
            if (pProperty)
                return m_eClassPropType::Property;

            Unity::il2cppMethodInfo* pMethod = reinterpret_cast<Unity::il2cppMethodInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*, int)>(Functions.m_ClassGetMethodFromName)(m_Object.m_pClass, m_pPropType, -1);
            if (pMethod)
                return m_eClassPropType::Method;

            return m_eClassPropType::Unknown;
        }

        // Call Method
        template<typename TReturn, typename... TArgs>
        TReturn CallMethod(void* m_pMethod, TArgs... tArgs) { return reinterpret_cast<TReturn(UNITY_CALLING_CONVENTION)(void*, TArgs...)>(m_pMethod)(this, tArgs...); }

        template<typename TReturn, typename... TArgs>
        TReturn CallMethod(const char* m_pMethodName, TArgs... tArgs) { return CallMethod<TReturn>(GetMethodPointer(m_pMethodName), tArgs...); }

        template<typename TReturn, typename... TArgs>
        TReturn CallMethodSafe(void* m_pMethod, TArgs... tArgs)
        {
            if (!m_pMethod)
            {
#ifdef _DEBUG 
                __debugbreak(); // remove it when you wanna step through your code and be like why the fuck it doesn't do anything.
#endif

                TReturn m_tDefault = {}; // void goes like illegal use of type. (use void* and fuck them)
                return m_tDefault;
            }

            return CallMethod<TReturn>(m_pMethod, tArgs...);
        }

        template<typename TReturn, typename... TArgs>
        TReturn CallMethodSafe(const char* m_pMethodName, TArgs... tArgs) { return CallMethodSafe<TReturn>(GetMethodPointer(m_pMethodName), tArgs...); }

        // Properties/Fields

        template<typename T>
        T GetPropertyValue(const char* m_pPropertyName)
        {
            Unity::il2cppPropertyInfo* pProperty = reinterpret_cast<Unity::il2cppPropertyInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetPropertyFromName)(m_Object.m_pClass, m_pPropertyName);
            if (pProperty && pProperty->m_pGet)
                return reinterpret_cast<T(UNITY_CALLING_CONVENTION)(void*)>(pProperty->m_pGet->m_pMethodPointer)(this);

            T tDefault = {};
            return tDefault;
        }

        template<typename T>
        void SetPropertyValue(const char* m_pPropertyName, T m_tValue)
        {
            Unity::il2cppPropertyInfo* pProperty = reinterpret_cast<Unity::il2cppPropertyInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetPropertyFromName)(m_Object.m_pClass, m_pPropertyName);
            if (pProperty && pProperty->m_pSet)
                return reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, T)>(pProperty->m_pSet->m_pMethodPointer)(this, m_tValue);
        }

        template<typename T>
        __inline T GetMemberValue(int m_iOffset)
        {
            return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
        }

        template<typename T>
        __inline void SetMemberValue(int m_iOffset, T m_tValue)
        {
            *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + m_iOffset) = m_tValue;
        }

        template<typename T>
        __inline T GetMemberValue(Unity::il2cppFieldInfo* m_pField)
        {
            if (!m_pField || 0 > m_pField->m_iOffset)
            {
                T m_tDefault = {};
                return m_tDefault;
            }

            return GetMemberValue<T>(m_pField->m_iOffset);
        }

        template<typename T>
        __inline void SetMemberValue(Unity::il2cppFieldInfo* m_pField, T m_tValue)
        {
            if (!m_pField || 0 > m_pField->m_iOffset)
                return;

            SetMemberValue<T>(m_pField->m_iOffset, m_tValue);
        }

        template<typename T>
        T GetMemberValue(const char* m_pMemberName)
        {
            Unity::il2cppFieldInfo* pField = reinterpret_cast<Unity::il2cppFieldInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetFieldFromName)(m_Object.m_pClass, m_pMemberName);
            if (pField)
            {
                if (pField->m_iOffset >= 0) return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + pField->m_iOffset);
            }
            else
                return GetPropertyValue<T>(m_pMemberName);

            T tDefault = {};
            return tDefault;
        }

        template<typename T>
        void SetMemberValue(const char* m_pMemberName, T m_tValue)
        {
            Unity::il2cppFieldInfo* pField = reinterpret_cast<Unity::il2cppFieldInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetFieldFromName)(m_Object.m_pClass, m_pMemberName);
            if (pField)
            {
                if (pField->m_iOffset >= 0) *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + pField->m_iOffset) = m_tValue;
                return;
            }

            SetPropertyValue<T>(m_pMemberName, m_tValue);
        }

        template<typename T>
        __inline T GetObscuredViaOffset(int m_iOffset)
        {
            if (m_iOffset >= 0)
            {
                switch (sizeof(T))
                {
                    case sizeof(double) :
                    {
                        long long m_lKey = *reinterpret_cast<long long*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
                        long long m_lValue = *reinterpret_cast<long long*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_lKey));

                        m_lValue ^= m_lKey;
                        return *reinterpret_cast<T*>(&m_lValue);
                    }
                    break;
                    case sizeof(int) :
                    {
                        int m_iKey = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
                        int m_iValue = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_iKey));

                        m_iValue ^= m_iKey;
                        return *reinterpret_cast<T*>(&m_iValue);
                    }
                    break;
                    case sizeof(bool) :
                    {
                        unsigned char m_uKey = *reinterpret_cast<unsigned char*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
                        int m_iValue = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_uKey));

                        m_iValue ^= m_uKey;
                        return *reinterpret_cast<T*>(&m_iValue);
                    }
                    break;
                }
            }

            T m_tDefault = { 0 };
            return m_tDefault;
        }

        template<typename T>
        T GetObscuredValue(const char* m_pMemberName)
        {
            Unity::il2cppFieldInfo* m_pField = reinterpret_cast<Unity::il2cppFieldInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetFieldFromName)(m_Object.m_pClass, m_pMemberName);
            return GetObscuredViaOffset<T>(m_pField ? m_pField->m_iOffset : -1);
        }

        template<typename T>
        __inline void SetObscuredViaOffset(int m_iOffset, T m_tValue)
        {
            if (0 > m_iOffset)
                return;

            switch (sizeof(T))
            {
                case sizeof(double) :
                {
                    long long m_lKey = *reinterpret_cast<long long*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
                    long long* m_pValue = reinterpret_cast<long long*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_lKey));

                    *m_pValue = *reinterpret_cast<long long*>(&m_tValue) ^ m_lKey;
                }
                break;
                case sizeof(int) :
                {
                    int m_iKey = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
                    int* m_pValue = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_iKey));

                    *m_pValue = *reinterpret_cast<int*>(&m_tValue) ^ m_iKey;
                }
                break;
                case sizeof(bool) :
                {
                    unsigned char m_uKey = *reinterpret_cast<unsigned char*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
                    int* m_pValue = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_uKey));

                    *m_pValue = *reinterpret_cast<int*>(&m_tValue) ^ m_uKey;
                }
                break;
            }
        }

        template<typename T>
        void SetObscuredValue(const char* m_pMemberName, T m_tValue)
        {
            Unity::il2cppFieldInfo* m_pField = reinterpret_cast<Unity::il2cppFieldInfo * (IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Functions.m_ClassGetFieldFromName)(m_Object.m_pClass, m_pMemberName);
            if (!m_pField)
                return;

            SetObscuredViaOffset<T>(m_pField->m_iOffset, m_tValue);
        }
    };
}