#pragma once

namespace IL2CPP
{
	namespace String
	{
		Unity::System_String* New(const char* m_pString);

		Unity::System_String* New(std::string m_sString);

		// Make sure to delete it after you done using it.
		namespace NoGC
		{ 
			Unity::System_String* New(const char* m_pString);

			Unity::System_String* New(std::string m_sString);
		}
	}
}