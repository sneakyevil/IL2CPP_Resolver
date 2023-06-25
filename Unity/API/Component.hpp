#pragma once

namespace Unity
{
	struct ComponentFunctions_t
	{
		void* m_GetGameObject = nullptr;
		void* m_GetTransform = nullptr;
	};
	ComponentFunctions_t m_ComponentFunctions;

	class CComponent : public CObject
	{
	public:
		CGameObject* GetGameObject()
		{
			return reinterpret_cast<CGameObject*(UNITY_CALLING_CONVENTION)(void*)>(m_ComponentFunctions.m_GetGameObject)(this);
		}

		CTransform* GetTransform()
		{
			return reinterpret_cast<CTransform*(UNITY_CALLING_CONVENTION)(void*)>(m_ComponentFunctions.m_GetTransform)(this);
		}
	};

	namespace Component
	{
		void Initialize()
		{
			IL2CPP::SystemTypeCache::Initializer::Add(UNITY_COMPONENT_CLASS);

			m_ComponentFunctions.m_GetGameObject	= IL2CPP::ResolveCall(UNITY_COMPONENT_GETGAMEOBJECT);
			m_ComponentFunctions.m_GetTransform		= IL2CPP::ResolveCall(UNITY_COMPONENT_GETTRANSFORM);
		}
	}
}