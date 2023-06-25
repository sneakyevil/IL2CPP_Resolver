#pragma once

namespace Unity
{
	struct GameObjectFunctions_t
	{
		void* m_AddComponent = nullptr;
		void* m_CreatePrimitive = nullptr;
		void* m_Find = nullptr;
		void* m_FindGameObjectsWithTag = nullptr;
		void* m_GetComponent = nullptr;
		void* m_GetComponents = nullptr;
		void* m_GetComponentInChildren = nullptr;
		void* m_GetActive = nullptr;
		void* m_GetLayer = nullptr;
		void* m_GetTransform = nullptr;
		void* m_SetActive = nullptr;
		void* m_SetLayer = nullptr;
	};
	GameObjectFunctions_t m_GameObjectFunctions;

	class CGameObject : public CObject
	{
	public:
		void AddComponent(il2cppObject* m_pSystemType)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, void*)>(m_GameObjectFunctions.m_AddComponent)(this, m_pSystemType);
		}

		CComponent* GetComponent(const char* m_pName)
		{
			return reinterpret_cast<CComponent*(UNITY_CALLING_CONVENTION)(void*, System_String*)>(m_GameObjectFunctions.m_GetComponent)(this, IL2CPP::String::New(m_pName));
		}

		CComponent* GetComponentInChildren(il2cppObject* m_pSystemType, bool includeInactive)
		{
			return reinterpret_cast<CComponent*(UNITY_CALLING_CONVENTION)(void*, void*, bool)>(m_GameObjectFunctions.m_GetComponentInChildren)(this, m_pSystemType, includeInactive);
		}

		// e.g CGameObject->GetComponentInChildren("Namespace.Component");
		CComponent* GetComponentInChildren(const char* type)
		{
			il2cppClass* m_pClass = IL2CPP::Class::Find(type);
			if (!m_pClass) return nullptr;

			return GetComponentInChildren(IL2CPP::Class::GetSystemType(m_pClass), true);
		}

		il2cppArray<CComponent*>* GetComponents(il2cppObject* m_pSystemType)
		{
			/* 
			0 - Object
			1 - Type
			2 - Use search type as array return type
			3 - Recursive
			4 - Include inactive
			5 - Reverse
			6 - Result list
			*/
			return reinterpret_cast<Unity::il2cppArray<CComponent*>*(UNITY_CALLING_CONVENTION)(void*, void*, bool, bool, bool, bool, void*)>(m_GameObjectFunctions.m_GetComponents)(this, m_pSystemType, false, false, true, false, nullptr);
		}

		il2cppArray<CComponent*>* GetComponents(const char* m_pSystemTypeName)
		{
			il2cppClass* m_pClass = IL2CPP::Class::Find(m_pSystemTypeName);
			if (!m_pClass) return nullptr;

			return GetComponents(IL2CPP::Class::GetSystemType(m_pClass));
		}

		CComponent* GetComponentByIndex(il2cppObject* m_pSystemType, unsigned int m_uIndex = 0U)
		{
			il2cppArray<CComponent*>* m_pComponents = GetComponents(m_pSystemType);
			if (!m_pComponents || m_uIndex >= m_pComponents->m_uMaxLength) return nullptr;

			return m_pComponents->operator[](m_uIndex);
		}

		CComponent* GetComponentByIndex(const char* m_pSystemTypeName, unsigned int m_uIndex = 0U)
		{
			il2cppClass* m_pClass = IL2CPP::Class::Find(m_pSystemTypeName);
			if (!m_pClass) return nullptr;

			return GetComponentByIndex(IL2CPP::Class::GetSystemType(m_pClass), m_uIndex);
		}

		CTransform* GetTransform()
		{
			return reinterpret_cast<CTransform*(UNITY_CALLING_CONVENTION)(void*)>(m_GameObjectFunctions.m_GetTransform)(this);
		}

		bool GetActive()
		{
			return reinterpret_cast<bool(UNITY_CALLING_CONVENTION)(void*)>(m_GameObjectFunctions.m_GetActive)(this);
		}

		unsigned int GetLayer()
		{
			return reinterpret_cast<unsigned int(UNITY_CALLING_CONVENTION)(void*)>(m_GameObjectFunctions.m_GetLayer)(this);
		}

		/*
		* (WARNING) when you use GameObject::Find and you set the object to unactive, you won't find it anymore with that slow function.
		*/
		void SetActive(bool m_bActive)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, bool)>(m_GameObjectFunctions.m_SetActive)(this, m_bActive);
		}

		void SetLayer(unsigned int m_uLayer)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, unsigned int)>(m_GameObjectFunctions.m_SetLayer)(this, m_uLayer);
		}
	};

	namespace GameObject
	{
		enum class m_ePrimitiveType : int
		{
			Default = 0,
			Sphere = 0,
			Capsule,
			Cylinder,
			Cube,
			Plane,
			Quad,
		};

		void Initialize()
		{
			IL2CPP::SystemTypeCache::Initializer::Add(UNITY_GAMEOBJECT_CLASS);

			m_GameObjectFunctions.m_AddComponent			= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_ADDCOMPONENT);
			m_GameObjectFunctions.m_CreatePrimitive			= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_CREATEPRIMITIVE);
			m_GameObjectFunctions.m_Find					= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_FIND);
			m_GameObjectFunctions.m_FindGameObjectsWithTag	= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_FINDGAMEOBJECTWITHTAG);
			m_GameObjectFunctions.m_GetComponent			= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETCOMPONENT);
			m_GameObjectFunctions.m_GetComponents			= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETCOMPONENTS);
			m_GameObjectFunctions.m_GetComponentInChildren	= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETCOMPONENTINCHILDREN);
			m_GameObjectFunctions.m_GetActive				= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETACTIVE);
			m_GameObjectFunctions.m_GetLayer				= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETLAYER);
			m_GameObjectFunctions.m_GetTransform			= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETTRANSFORM);
			m_GameObjectFunctions.m_SetActive				= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_SETACTIVE);
			m_GameObjectFunctions.m_SetLayer				= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_SETLAYER);
		}

		CGameObject* CreatePrimitive(m_ePrimitiveType m_Type)
		{
			return reinterpret_cast<CGameObject*(UNITY_CALLING_CONVENTION)(m_ePrimitiveType)>(m_GameObjectFunctions.m_CreatePrimitive)(m_Type);
		}

		CGameObject* Find(const char* m_Name)
		{
			return reinterpret_cast<CGameObject*(UNITY_CALLING_CONVENTION)(System_String*)>(m_GameObjectFunctions.m_Find)(IL2CPP::String::New(m_Name));
		}

		il2cppArray<CGameObject*>* FindWithTag(const char* m_Tag)
		{
			return reinterpret_cast<il2cppArray<CGameObject*>*(UNITY_CALLING_CONVENTION)(void*)>(m_GameObjectFunctions.m_FindGameObjectsWithTag)(IL2CPP::String::New(m_Tag));
		}
	}
}
