#pragma once

namespace IL2CPP
{
	class Class
	{
	public:
		Unity::il2cppObject m_Object = { 0 };
		void* m_CachedPtr = nullptr;
		
		void* GetMethodPointer(const char* m_MethodName, int iArgs = -1)
		{
			Unity::il2cppMethodInfo* pMethod = reinterpret_cast<Unity::il2cppMethodInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*, int)>(Data.Functions.m_pClassGetMethodFromName)(m_Object.m_pClass, m_MethodName, iArgs);
			if (!pMethod || !pMethod->m_pMethodPointer) return nullptr;

			return pMethod->m_pMethodPointer;
		}

		int GetFieldOffset(const char* m_pFieldName)
		{
			Unity::il2cppFieldInfo* pField = reinterpret_cast<Unity::il2cppFieldInfo*(IL2CPP_CALLING_CONVENTION)(void*, const char*)>(Data.Functions.m_pClassGetFieldFromName)(m_Object.m_pClass, m_pFieldName);
			if (!pField || 0 > pField->m_iOffset) return -1;

			return pField->m_iOffset;
		}

		std::string GetFieldString(const char* m_pFieldName)
		{
			int m_iOffset = GetFieldOffset(m_pFieldName);
			if (0 > m_iOffset) return "";

			Unity::System_String* pString = *reinterpret_cast<Unity::System_String**>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
			if (!pString) return "";

			return pString->ToString();
		}

		template<typename T>
		void SetFieldValue(T tValue, const char* m_pFieldName)
		{
			int m_iOffset = GetFieldOffset(m_pFieldName);
			if (0 > m_iOffset) return;

			*reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + m_iOffset) = tValue;
		}

		template<typename T>
		T GetFieldValue(const char* m_pFieldName)
		{
			int m_iOffset = GetFieldOffset(m_pFieldName);
			if (0 > m_iOffset)
			{
				T tDefault;
				return tDefault;
			}

			return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
		}

		template<typename T>
		T* GetFieldPointer(const char* m_pFieldName)
		{
			int m_iOffset = GetFieldOffset(m_pFieldName);
			if (0 > m_iOffset) return reinterpret_cast<T*>(nullptr);

			return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + m_iOffset);
		}
	};
}