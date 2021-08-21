#pragma once

namespace IL2CPP
{
	// Without this function, you're pretty much fucked up.
	static void* ResolveCall(const char* m_pName)
	{
		return reinterpret_cast<void*(IL2CPP_CALLING_CONVENTION)(const char*)>(Data.Functions.m_pResolveFunction)(m_pName);
	}
}