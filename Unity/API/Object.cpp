#include "../../Includes.hpp"

namespace Unity
{
	SObjectFunctions ObjectFunctions;

	namespace Object
	{
		void Initialize()
		{
			ObjectFunctions.m_pDestroy = IL2CPP::ResolveCall(UNITY_OBJECT_DESTROY);
		}
	}
}