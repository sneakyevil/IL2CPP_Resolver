#pragma once

namespace Unity
{
	struct System_String : il2cppObject
	{
		int m_iLength;
		wchar_t m_wString[1024];

		void Clear()
		{
			if (!this) return;

			memset(m_wString, 0, static_cast<size_t>(m_iLength) * 2);
			m_iLength = 0;
		}

		std::string ToString()
		{
		    if (!this) return "";

		    std::string sRet(static_cast<size_t>(m_iLength + 1) * 4, '\0');
		    WideCharToMultiByte(CP_UTF8, 0, m_wString, m_iLength, &sRet[0], static_cast<int>(sRet.size()), 0, 0);
		    return sRet;
		}
	};
}
