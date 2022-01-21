#include "../../Includes.hpp"

namespace Unity
{
	SLayerMaskFunctions LayerMaskFunctions;

	namespace LayerMask
	{
		void Initialize()
		{
			IL2CPP::SystemTypeCache::Initializer::Add(UNITY_LAYERMASK_CLASS);

			LayerMaskFunctions.m_pLayerToName	= IL2CPP::ResolveCall(UNITY_LAYERMASK_LAYERTONAME);
			LayerMaskFunctions.m_pNameToLayer	= IL2CPP::ResolveCall(UNITY_LAYERMASK_NAMETOLAYER);
		}
	}
}