#include "../../Includes.hpp"

namespace Unity
{
	SObjectFunctions ObjectFunctions;

	namespace Object
	{
		void Initialize()
		{
			IL2CPP::SystemTypeCache::Initializer::Add(UNITY_OBJECT_CLASS);

			ObjectFunctions.m_pDestroy				= IL2CPP::ResolveCall(UNITY_OBJECT_DESTROY);
			ObjectFunctions.m_pFindObjectsOfType	= IL2CPP::ResolveCall(UNITY_OBJECT_FINDOBJECTSOFTYPE);
			ObjectFunctions.m_pGetName				= IL2CPP::ResolveCall(UNITY_OBJECT_GETNAME);
		}
	}
}