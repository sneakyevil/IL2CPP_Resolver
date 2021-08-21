#include "../../Includes.hpp"

namespace Unity
{
	STransformFunctions TransformFunctions;

	namespace Transform
	{
		void Initialize()
		{
			TransformFunctions.m_pGetPosition = IL2CPP::ResolveCall(UNITY_TRANSFORM_GETPOSITION);
			TransformFunctions.m_pGetLocalPosition = IL2CPP::ResolveCall(UNITY_TRANSFORM_GETLOCALPOSITION);
			TransformFunctions.m_pSetPosition = IL2CPP::ResolveCall(UNITY_TRANSFORM_SETPOSITION);
			TransformFunctions.m_pSetLocalPosition = IL2CPP::ResolveCall(UNITY_TRANSFORM_SETLOCALPOSITION);
		}
	}
}