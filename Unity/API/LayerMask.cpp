#include "../../Includes.hpp"

namespace Unity
{
	SLayerMaskFunctions LayerMaskFunctions;

	namespace LayerMask
	{
		void Initialize()
		{
			LayerMaskFunctions.m_pLayerToName = IL2CPP::ResolveCall(UNITY_LAYERMASK_LAYERTONAME);
			LayerMaskFunctions.m_pNameToLayer = IL2CPP::ResolveCall(UNITY_LAYERMASK_NAMETOLAYER);
		}
	}
}