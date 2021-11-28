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

		namespace NoGC
		{
			Unity::System_String* New(const char* m_pString)
			{
				Unity::System_String* m_pNew = new Unity::System_String;
				m_pNew->m_pClass = IL2CPP::Class::Find("System.String");
				m_pNew->m_iLength = swprintf_s(m_pNew->m_wString, (sizeof(Unity::System_String::m_wString) / 4), L"%hs", m_pString);

				return m_pNew;
			}

			Unity::System_String* New(std::string m_sString) { return New(&m_sString[0]); }
		}
	}
}