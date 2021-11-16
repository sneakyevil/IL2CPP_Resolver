#pragma once

namespace IL2CPP
{
	struct SData
	{
		HMODULE m_hGameAseembly = 0;
		
		struct SFunctions
		{
			void* m_pClassFromName = nullptr;
			void* m_pClassGetFields = nullptr;
			void* m_pClassGetFieldFromName = nullptr;
			void* m_pClassGetMethods = nullptr;
			void* m_pClassGetMethodFromName = nullptr;
			void* m_pClassGetPropertyFromName = nullptr;
			void* m_pClassGetType = nullptr;
			void* m_pDomainGet = nullptr;
			void* m_pDomainGetAssemblies = nullptr;
			void* m_pFree = nullptr;
			void* m_pImageGetClass = nullptr;
			void* m_pImageGetClassCount = nullptr;
			void* m_pResolveFunction = nullptr;
			void* m_pStringNew = nullptr;
			void* m_pThreadAttach = nullptr;
			void* m_pThreadDetach = nullptr;
			void* m_pTypeGetObject = nullptr;
		};
		SFunctions Functions;
	};
	extern SData Data;
}