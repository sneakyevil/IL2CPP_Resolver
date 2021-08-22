#pragma once
#include "Includes.hpp"

namespace IL2CPP
{
	/* Must be called once before using any other functions!
	* Args:
	* bWaitForModule: (Wait for GameAssembly - can result in infinite loop!) 
	*/
	bool Initialize(bool m_bWaitForModule = false);

	namespace UnityAPI
	{
		enum m_eExportObfuscationType
		{
			None = 0,
			ROT = 1,
			MAX = 2,
		};

		extern m_eExportObfuscationType m_ExportObfuscation;

		void* ResolveExport(const char* m_pName);

		bool Initialize();
	}
}