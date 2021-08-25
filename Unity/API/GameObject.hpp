#pragma once

namespace Unity
{
	struct SGameObjectFunctions
	{
		void* m_pCreatePrimitive = nullptr;
		void* m_pFind = nullptr;
		void* m_pGetComponent = nullptr;
		void* m_pGetComponents = nullptr;
		void* m_pGetLayer = nullptr;
		void* m_pGetTransform = nullptr;
		void* m_pSetLayer = nullptr;
	};
	extern SGameObjectFunctions GameObjectFunctions;

	class CGameObject : public CObject
	{
	public:
		CComponent* GetComponent(const char* m_pName)
		{
			return reinterpret_cast<CComponent*(UNITY_CALLING_CONVENTION)(void*, System_String*)>(GameObjectFunctions.m_pGetComponent)(this, IL2CPP::String::New(m_pName));
		}

		il2cppArray<CComponent>* GetComponents(il2cppObject* m_pSystemType)
		{
			return reinterpret_cast<Unity::il2cppArray<CComponent>*(UNITY_CALLING_CONVENTION)(void*, void*, bool, bool, bool, bool, void*)>(GameObjectFunctions.m_pGetComponents)(this, m_pSystemType, false, false, true, false, nullptr);
		}

		il2cppArray<CComponent>* GetComponents(const char* m_pSystemTypeName)
		{
			il2cppClass* pClass = IL2CPP::Class::Find(m_pSystemTypeName);
			if (!pClass) return nullptr;

			return GetComponents(IL2CPP::Class::GetSystemType(pClass));
		}

		CTransform* GetTransform()
		{
			return reinterpret_cast<CTransform*(UNITY_CALLING_CONVENTION)(void*)>(GameObjectFunctions.m_pGetTransform)(this);
		}

		unsigned int GetLayer()
		{
			return reinterpret_cast<unsigned int(UNITY_CALLING_CONVENTION)(void*)>(GameObjectFunctions.m_pGetLayer)(this);
		}

		void SetLayer(unsigned int m_uLayer)
		{
			return reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, unsigned int)>(GameObjectFunctions.m_pSetLayer)(this, m_uLayer);
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

		void Initialize();
		
		CGameObject* CreatePrimitive(m_ePrimitiveType m_eType);

		CGameObject* Find(const char* m_pName);
	}
}