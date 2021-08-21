#include "../../Includes.hpp"

namespace Unity
{
	SGameObjectFunctions GameObjectFunctions;

	namespace GameObject
	{
		void Initialize()
		{
			GameObjectFunctions.m_pCreatePrimitive = IL2CPP::ResolveCall(UNITY_GAMEOBJECT_CREATEPRIMITIVE);
			GameObjectFunctions.m_pFind = IL2CPP::ResolveCall(UNITY_GAMEOBJECT_FIND);
			GameObjectFunctions.m_pGetComponent = IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETCOMPONENT);
			GameObjectFunctions.m_pGetTransform = IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETTRANSFORM);
		}

		CGameObject* CreatePrimitive(m_ePrimitiveType m_eType)
		{
			return reinterpret_cast<CGameObject*(UNITY_CALLING_CONVENTION)(m_ePrimitiveType)>(GameObjectFunctions.m_pCreatePrimitive)(m_eType);
		}

		CGameObject* Find(const char* m_pName)
		{
			return reinterpret_cast<CGameObject*(UNITY_CALLING_CONVENTION)(System_String*)>(GameObjectFunctions.m_pFind)(IL2CPP::String::New(m_pName));
		}
	}
}