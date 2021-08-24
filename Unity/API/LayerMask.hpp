#pragma once

namespace Unity
{
	struct SLayerMaskFunctions
	{
		void* m_pLayerToName = nullptr;
		void* m_pNameToLayer = nullptr;
	};
	extern SLayerMaskFunctions LayerMaskFunctions;

	namespace LayerMask
	{
		void Initialize();

		static System_String* LayerToName(unsigned int m_uLayer)
		{
			return reinterpret_cast<System_String*(UNITY_CALLING_CONVENTION)(unsigned int)>(LayerMaskFunctions.m_pLayerToName)(m_uLayer);
		}

		static unsigned int NameToLayer(System_String* m_pName)
		{
			return reinterpret_cast<unsigned int(UNITY_CALLING_CONVENTION)(void*)>(LayerMaskFunctions.m_pNameToLayer)(m_pName);
		}
	}
}