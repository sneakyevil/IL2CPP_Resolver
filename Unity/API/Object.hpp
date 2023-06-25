#pragma once

namespace Unity
{
	struct ObjectFunctions_t
	{
		void* m_Destroy = nullptr;
		void* m_FindObjectsOfType = nullptr;
		void* m_GetName = nullptr;
	};
	ObjectFunctions_t m_ObjectFunctions;

	class CObject : public IL2CPP::CClass
	{
	public:
		void Destroy(float fTimeDelay = 0.f)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, float)>(m_ObjectFunctions.m_Destroy)(this, fTimeDelay);
		}

		System_String* GetName()
		{
			return reinterpret_cast<System_String*(UNITY_CALLING_CONVENTION)(void*)>(m_ObjectFunctions.m_GetName)(this);
		}
	};

	namespace Object
	{
		void Initialize()
		{
			IL2CPP::SystemTypeCache::Initializer::Add(UNITY_OBJECT_CLASS);

			m_ObjectFunctions.m_Destroy				= IL2CPP::ResolveCall(UNITY_OBJECT_DESTROY);
			m_ObjectFunctions.m_FindObjectsOfType	= IL2CPP::ResolveCall(UNITY_OBJECT_FINDOBJECTSOFTYPE);
			m_ObjectFunctions.m_GetName				= IL2CPP::ResolveCall(UNITY_OBJECT_GETNAME);
		}

		template<typename T>
		static il2cppArray<T*>* FindObjectsOfType(il2cppObject* m_pSystemType)
		{
			return reinterpret_cast<Unity::il2cppArray<T*>*(UNITY_CALLING_CONVENTION)(void*)>(m_ObjectFunctions.m_FindObjectsOfType)(m_pSystemType);
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

			return m_pArray->m_pValues[0];
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
