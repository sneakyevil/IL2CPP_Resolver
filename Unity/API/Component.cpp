#include "../../Includes.hpp"

namespace Unity
{
	SComponentFunctions ComponentFunctions;

	namespace Component
	{
		void Initialize()
		{
			IL2CPP::SystemTypeCache::Initializer::Add(UNITY_COMPONENT_CLASS);

			ComponentFunctions.m_pGetGameObject		= IL2CPP::ResolveCall(UNITY_COMPONENT_GETGAMEOBJECT);
			ComponentFunctions.m_pGetTransform		= IL2CPP::ResolveCall(UNITY_COMPONENT_GETTRANSFORM);
		}
	}
}