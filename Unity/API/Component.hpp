#pragma once

namespace Unity
{
	struct SComponentFunctions
	{
		void* m_pGetGameObject = nullptr;
		void* m_pGetTransform = nullptr;
	};
	extern SComponentFunctions ComponentFunctions;

	class CComponent : public CObject
	{
	public:
		CGameObject* GetGameObject()
		{
			return reinterpret_cast<CGameObject*(UNITY_CALLING_CONVENTION)(void*)>(ComponentFunctions.m_pGetGameObject)(this);
		}

		CTransform* GetTransform()
		{
			return reinterpret_cast<CTransform*(UNITY_CALLING_CONVENTION)(void*)>(ComponentFunctions.m_pGetTransform)(this);
		}
	};

	namespace Component
	{
		void Initialize();
	}
}