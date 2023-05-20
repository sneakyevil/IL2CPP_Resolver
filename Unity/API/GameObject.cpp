#include "../../Includes.hpp"

namespace Unity
{
	SGameObjectFunctions GameObjectFunctions;

	namespace GameObject
	{
		void Initialize()
		{
			IL2CPP::SystemTypeCache::Initializer::Add(UNITY_GAMEOBJECT_CLASS);

			GameObjectFunctions.m_pAddComponent				= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_ADDCOMPONENT);
			GameObjectFunctions.m_pCreatePrimitive			= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_CREATEPRIMITIVE);
			GameObjectFunctions.m_pFind						= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_FIND);
			GameObjectFunctions.m_pFindGameObjectsWithTag	= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_FINDGAMEOBJECTWITHTAG);
			GameObjectFunctions.m_pGetComponent				= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETCOMPONENT);
			GameObjectFunctions.m_pGetComponents			= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETCOMPONENTS);
			GameObjectFunctions.m_pGetComponentInChildren	= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETCOMPONENTINCHILDREN);
			GameObjectFunctions.m_pGetActive				= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETACTIVE);
			GameObjectFunctions.m_pGetLayer					= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETLAYER);
			GameObjectFunctions.m_pGetTransform				= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETTRANSFORM);
			GameObjectFunctions.m_pSetActive				= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_SETACTIVE);
			GameObjectFunctions.m_pSetLayer					= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_SETLAYER);
		}

		CGameObject* CreatePrimitive(m_ePrimitiveType m_eType)
		{
			return reinterpret_cast<CGameObject*(UNITY_CALLING_CONVENTION)(m_ePrimitiveType)>(GameObjectFunctions.m_pCreatePrimitive)(m_eType);
		}

		CGameObject* Find(const char* m_pName)
		{
			return reinterpret_cast<CGameObject*(UNITY_CALLING_CONVENTION)(System_String*)>(GameObjectFunctions.m_pFind)(IL2CPP::String::New(m_pName));
		}
		
		il2cppArray<CGameObject*>* FindWithTag(const char* m_pTag)
		{
			return reinterpret_cast<il2cppArray<CGameObject*>*(UNITY_CALLING_CONVENTION)(void*)>(GameObjectFunctions.m_pFindGameObjectsWithTag)(IL2CPP::String::New(m_pTag));
		}
	}
}
