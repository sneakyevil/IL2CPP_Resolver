#pragma once

namespace Unity
{
	struct SObjectFunctions
	{
		void* m_pDestroy = nullptr;
		void* m_pFindObjectsOfType = nullptr;
		void* m_pGetName = nullptr;
	};
	extern SObjectFunctions ObjectFunctions;

	class CObject : public IL2CPP::CClass
	{
	public:
		void Destroy(float fTimeDelay = 0.f)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, float)>(ObjectFunctions.m_pDestroy)(this, fTimeDelay);
		}

		System_String* GetName()
		{
			return reinterpret_cast<System_String*(UNITY_CALLING_CONVENTION)(void*)>(ObjectFunctions.m_pGetName)(this);
		}
	};

	namespace Object
	{
		void Initialize();

		template<typename T>
		static il2cppArray<T*>* FindObjectsOfType(il2cppObject* m_pSystemType)
		{
			return reinterpret_cast<Unity::il2cppArray<T*>*(UNITY_CALLING_CONVENTION)(void*)>(ObjectFunctions.m_pFindObjectsOfType)(m_pSystemType);
		}

		template<typename T>
		static il2cppArray<T*>* FindObjectsOfType(const char* m_pSystemTypeName)
		{
			il2cppClass* m_pClass = IL2CPP::Class::Find(m_pSystemTypeName);
			if (!m_pClass) return nullptr;

			return FindObjectsOfType<T>(IL2CPP::Class::GetSystemType(m_pClass));
		}

		template<typename T>
		static T* FindObjectOfType(il2cppObject* m_pSystemType)
		{
			il2cppArray<T*>* m_pArray = FindObjectsOfType<T>(m_pSystemType);
			if (!m_pArray || m_pArray->m_uMaxLength == 0U) return nullptr;

			return m_pArray->m_tValues[0];
		}

		template<typename T>
		static T* FindObjectOfType(const char* m_pSystemTypeName)
		{
			il2cppClass* m_pClass = IL2CPP::Class::Find(m_pSystemTypeName);
			if (!m_pClass) return nullptr;

			return FindObjectOfType<T>(IL2CPP::Class::GetSystemType(m_pClass));
		}
	}
}
