#pragma once

namespace Unity
{
	struct LayerMaskFunctions_t
	{
		void* m_LayerToName = nullptr;
		void* m_NameToLayer = nullptr;
	};
	LayerMaskFunctions_t m_LayerMaskFunctions;

	namespace LayerMask
	{
		void Initialize()
		{
			IL2CPP::SystemTypeCache::Initializer::Add(UNITY_LAYERMASK_CLASS);

			m_LayerMaskFunctions.m_LayerToName = IL2CPP::ResolveCall(UNITY_LAYERMASK_LAYERTONAME);
			m_LayerMaskFunctions.m_NameToLayer = IL2CPP::ResolveCall(UNITY_LAYERMASK_NAMETOLAYER);
		}

		System_String* LayerToName(unsigned int m_uLayer)
		{
			return reinterpret_cast<System_String*(UNITY_CALLING_CONVENTION)(unsigned int)>(m_LayerMaskFunctions.m_LayerToName)(m_uLayer);
		}

		uint32_t NameToLayer(const char* m_pName)
		{
			return reinterpret_cast<uint32_t(UNITY_CALLING_CONVENTION)(void*)>(m_LayerMaskFunctions.m_NameToLayer)(IL2CPP::String::New(m_pName));
		}
	}
}