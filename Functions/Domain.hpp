#pragma once

namespace IL2CPP
{
	namespace Domain
	{
		static void* Get()
		{
			return reinterpret_cast<void*(IL2CPP_CALLING_CONVENTION)()>(Data.Functions.m_pDomainGet)();
		}

		static Unity::il2cppAssembly** GetAssemblies(size_t* m_pSize)
		{
			return reinterpret_cast<Unity::il2cppAssembly**(IL2CPP_CALLING_CONVENTION)(void*, size_t*)>(Data.Functions.m_pDomainGetAssemblies)(Get(), m_pSize);
		}
	}
}