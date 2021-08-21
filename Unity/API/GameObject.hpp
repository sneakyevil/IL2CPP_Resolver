#pragma once

namespace Unity
{
	struct SGameObjectFunctions
	{
		void* m_pCreatePrimitive = nullptr;
		void* m_pFind = nullptr;
		void* m_pGetComponent = nullptr;
		void* m_pGetTransform = nullptr;
	};
	extern SGameObjectFunctions GameObjectFunctions;

	class CGameObject : public CObject
	{
	public:
		CComponent* GetComponent(const char* m_pName)
		{
			return reinterpret_cast<CComponent*(UNITY_CALLING_CONVENTION)(void*, System_String*)>(GameObjectFunctions.m_pGetComponent)(this, IL2CPP::String::New(m_pName));
		}

		CTransform* GetTransform()
		{
			return reinterpret_cast<CTransform*(UNITY_CALLING_CONVENTION)(void*)>(GameObjectFunctions.m_pGetTransform)(this);
		}
	};

	namespace GameObject
	{
		enum m_ePrimitiveType
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