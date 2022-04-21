#pragma once

namespace IL2CPP
{
	namespace Class
	{
		Unity::il2cppFieldInfo* GetFields(Unity::il2cppClass* m_pClass, void** m_pIterator);

		void FetchFields(Unity::il2cppClass* m_pClass, std::vector<Unity::il2cppFieldInfo*>* m_pVector, void* m_pFieldIterator = nullptr);

		Unity::il2cppMethodInfo* GetMethods(Unity::il2cppClass* m_pClass, void** m_pIterator);

		void FetchMethods(Unity::il2cppClass* m_pClass, std::vector<Unity::il2cppMethodInfo*>* m_pVector, void* m_pMethodIterator = nullptr);

		Unity::il2cppType* GetType(Unity::il2cppClass* m_pClass);

		Unity::il2cppObject* GetSystemType(Unity::il2cppClass* m_pClass);

		Unity::il2cppObject* GetSystemType(const char* m_pClassName);

		Unity::il2cppClass* GetFromName(Unity::il2cppImage* m_pImage, const char* m_pNamespace, const char* m_pName);

		Unity::il2cppClass* Find(const char* m_pName);

		/*
		*   If you wanna fetch modules with custom classes use modulename: Assembly-CSharp
		*   Nullptr namespace == pass any namespace
		*/
		void FetchClasses(std::vector<Unity::il2cppClass*>* m_pVector, const char* m_pModuleName, const char* m_pNamespace);

		namespace Utils
		{
			int GetFieldOffset(Unity::il2cppClass* m_pClass, const char* m_pName);

			int GetFieldOffset(const char* m_pClassName, const char* m_pName);

			void* GetMethodPointer(Unity::il2cppClass* m_pClass, const char* m_pMethodName, int m_iArgs = -1);

			void* GetMethodPointer(const char* m_pClassName, const char* m_pMethodName, int m_iArgs = -1);
			
			/*
			*	Usage
			*		m_pArgNames = { "arg1" , "arg2" , ... }
			*/
			void* GetMethodPointer(const char* m_pClassName, const char* m_pMethodName, std::vector<std::string> m_pArgNames);

			
			/*
			*	Name Prefixes
			*		(Field)  ~
			*		(Method) -
			*/
			Unity::il2cppClass* FilterClass(std::vector<Unity::il2cppClass*>* m_pClasses, std::initializer_list<const char*> m_vNames, int m_iFoundCount = -1);

			void* FilterClassToMethodPointer(std::vector<Unity::il2cppClass*>* m_pClasses, const char* m_pMethodName, int m_iArgs = -1);
		}
	}

	enum class m_eClassPropType : int
	{
		Unknown = 0,
		Field,			// Member of class that can be accessed directly by RVA
		Property,		// Member of class that can be accessed by calling function
		Method,			// Function of class
	};

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
			Unity::il2cppFieldInfo* pField = reinterpret_cast<Unity::il2cppFieldInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Data.Functions.m_pClassGetFieldFromName)(m_Object.m_pClass, m_pPropType);
			if (pField) 
				return m_eClassPropType::Field;

			Unity::il2cppPropertyInfo* pProperty = reinterpret_cast<Unity::il2cppPropertyInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Data.Functions.m_pClassGetPropertyFromName)(m_Object.m_pClass, m_pPropType);
			if (pProperty) 
				return m_eClassPropType::Property;

			Unity::il2cppMethodInfo* pMethod = reinterpret_cast<Unity::il2cppMethodInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*, int)>(Data.Functions.m_pClassGetMethodFromName)(m_Object.m_pClass, m_pPropType, -1);
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
			Unity::il2cppPropertyInfo* pProperty = reinterpret_cast<Unity::il2cppPropertyInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Data.Functions.m_pClassGetPropertyFromName)(m_Object.m_pClass, m_pPropertyName);
			if (pProperty && pProperty->m_pGet) 
				return reinterpret_cast<T(UNITY_CALLING_CONVENTION)(void*)>(pProperty->m_pGet->m_pMethodPointer)(this);

			T tDefault = {};
			return tDefault;
		}

		template<typename T>
		void SetPropertyValue(const char* m_pPropertyName, T m_tValue)
		{
			Unity::il2cppPropertyInfo* pProperty = reinterpret_cast<Unity::il2cppPropertyInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Data.Functions.m_pClassGetPropertyFromName)(m_Object.m_pClass, m_pPropertyName);
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
			Unity::il2cppFieldInfo* pField = reinterpret_cast<Unity::il2cppFieldInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Data.Functions.m_pClassGetFieldFromName)(m_Object.m_pClass, m_pMemberName);
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
			Unity::il2cppFieldInfo* pField = reinterpret_cast<Unity::il2cppFieldInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Data.Functions.m_pClassGetFieldFromName)(m_Object.m_pClass, m_pMemberName);
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
					case sizeof(double):
					{
						long long m_lKey = *reinterpret_cast<long long*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
						long long m_lValue = *reinterpret_cast<long long*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_lKey));

						m_lValue ^= m_lKey;
						return *reinterpret_cast<T*>(&m_lValue);
					}
					break;
					case sizeof(int):
					{
						int m_iKey = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
						int m_iValue = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_iKey));

						m_iValue ^= m_iKey;
						return *reinterpret_cast<T*>(&m_iValue);
					}
					break;
					case sizeof(bool):
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
			Unity::il2cppFieldInfo* m_pField = reinterpret_cast<Unity::il2cppFieldInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Data.Functions.m_pClassGetFieldFromName)(m_Object.m_pClass, m_pMemberName);	
			return GetObscuredViaOffset<T>(m_pField ? m_pField->m_iOffset : -1);
		}

		template<typename T>
		__inline void SetObscuredViaOffset(int m_iOffset, T m_tValue)
		{
			if (0 > m_iOffset)
				return;

			switch (sizeof(T))
			{
				case sizeof(double):
				{
					long long m_lKey = *reinterpret_cast<long long*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
					long long* m_pValue = reinterpret_cast<long long*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_lKey));

					*m_pValue = *reinterpret_cast<long long*>(&m_tValue) ^ m_lKey;
				}
				break;
				case sizeof(int):
				{
					int m_iKey = *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
					int* m_pValue = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + m_iOffset + sizeof(m_iKey));

					*m_pValue = *reinterpret_cast<int*>(&m_tValue) ^ m_iKey;
				}
				break;
				case sizeof(bool):
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
			Unity::il2cppFieldInfo* m_pField = reinterpret_cast<Unity::il2cppFieldInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Data.Functions.m_pClassGetFieldFromName)(m_Object.m_pClass, m_pMemberName);
			if (!m_pField)
				return;
			
			SetObscuredViaOffset<T>(m_pField->m_iOffset, m_tValue);
		}
	};
}
