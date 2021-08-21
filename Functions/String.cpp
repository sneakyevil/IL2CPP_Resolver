#include "../Includes.hpp"

namespace IL2CPP
{
	namespace String
	{
		Unity::System_String* New(const char* m_pString)
		{
			return reinterpret_cast<Unity::System_String*(IL2CPP_CALLING_CONVENTION)(const char*)>(Data.Functions.m_pStringNew)(m_pString);
		}

		Unity::System_String* New(std::string m_sString) { return New(&m_sString[0]); }
	}
}