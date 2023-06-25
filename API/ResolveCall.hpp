#pragma once

namespace IL2CPP
{
	// Without this function, you're pretty much fucked up.
	void* ResolveCall(const char* m_Name)
	{
		return reinterpret_cast<void*(IL2CPP_CALLING_CONVENTION)(const char*)>(Functions.m_ResolveFunction)(m_Name);
	}
}