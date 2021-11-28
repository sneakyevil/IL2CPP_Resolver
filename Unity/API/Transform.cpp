#include "../../Includes.hpp"

namespace Unity
{
	STransformFunctions TransformFunctions;

	namespace Transform
	{
		void Initialize()
		{
			IL2CPP::SystemTypeCache::Initializer::Add(UNITY_TRANSFORM_CLASS);

			TransformFunctions.m_pGetParent				= IL2CPP::ResolveCall(UNITY_TRANSFORM_GETPARENT);
			TransformFunctions.m_pGetRoot				= IL2CPP::ResolveCall(UNITY_TRANSFORM_GETROOT);
			TransformFunctions.m_pGetChild				= IL2CPP::ResolveCall(UNITY_TRANSFORM_GETCHILD);
			TransformFunctions.m_pGetChildCount			= IL2CPP::ResolveCall(UNITY_TRANSFORM_GETCHILDCOUNT);
			TransformFunctions.m_pGetPosition			= IL2CPP::ResolveCall(UNITY_TRANSFORM_GETPOSITION);
			TransformFunctions.m_pGetLocalPosition		= IL2CPP::ResolveCall(UNITY_TRANSFORM_GETLOCALPOSITION);
			TransformFunctions.m_pGetLocalRotation		= IL2CPP::ResolveCall(UNITY_TRANSFORM_GETLOCALROTATION);
			TransformFunctions.m_pGetLocalScale			= IL2CPP::ResolveCall(UNITY_TRANSFORM_GETLOCALSCALE);
			TransformFunctions.m_pSetPosition			= IL2CPP::ResolveCall(UNITY_TRANSFORM_SETPOSITION);
			TransformFunctions.m_pSetLocalPosition		= IL2CPP::ResolveCall(UNITY_TRANSFORM_SETLOCALPOSITION);
			TransformFunctions.m_pSetLocalRotation		= IL2CPP::ResolveCall(UNITY_TRANSFORM_SETLOCALROTATION);
			TransformFunctions.m_pSetLocalScale			= IL2CPP::ResolveCall(UNITY_TRANSFORM_SETLOCALSCALE);
		}
	}
}