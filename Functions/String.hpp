#pragma once

namespace IL2CPP
{
	namespace String
	{
		Unity::System_String* New(const char* m_pString);

		Unity::System_String* New(std::string m_sString);
	}
}