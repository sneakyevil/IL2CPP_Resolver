#pragma once

namespace IL2CPP
{
	namespace String
	{
		Unity::System_String* New(const char* m_String)
		{
			return reinterpret_cast<Unity::System_String*(IL2CPP_CALLING_CONVENTION)(const char*)>(Functions.m_StringNew)(m_String);
		}

		Unity::System_String* New(std::string m_String) 
		{ 
			return New(&m_String[0]);
		}

		namespace NoGC
		{
			Unity::System_String* New(const char* m_String)
			{
				Unity::System_String* m_NewString = new Unity::System_String;
				m_NewString->m_pClass = IL2CPP::Class::Find(IL2CPP_RStr("System.String"));
				m_NewString->m_iLength = swprintf_s(m_NewString->m_wString, (sizeof(Unity::System_String::m_wString) / 4), L"%hs", m_String);

				return m_NewString;
			}

			Unity::System_String* New(std::string m_String) 
			{
				return New(&m_String[0]); 
			}
		}
	}
}