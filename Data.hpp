#pragma once

namespace IL2CPP
{
	struct SData
	{
		HMODULE m_hGameAseembly = 0;
		
		struct SFunctions
		{
			void* m_pClassGetFieldFromName = nullptr;
			void* m_pClassGetMethodFromName = nullptr;
			void* m_pFree = nullptr;
			void* m_pResolveFunction = nullptr;
			void* m_pStringNew = nullptr;
		};
		SFunctions Functions;
	};
	extern SData Data;
}