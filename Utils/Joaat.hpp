#pragma once

namespace IL2CPP
{
	namespace Utils
	{
		inline unsigned int JOAAT(const char* str)
		{
			unsigned int m_uHash = 0;

			while (*str)
			{
				m_uHash += *(str++);
				m_uHash += (m_uHash << 10);
				m_uHash ^= (m_uHash >> 6);
			}

			m_uHash += (m_uHash << 3);
			m_uHash ^= (m_uHash >> 11);
			m_uHash += (m_uHash << 15);

			return m_uHash;
		}

		inline constexpr unsigned int JOAAT_CONSTEXPR(const char* str)
		{
			unsigned int m_uHash = 0;

			while (*str)
			{
				m_uHash += *(str++);
				m_uHash += (m_uHash << 10);
				m_uHash ^= (m_uHash >> 6);
			}

			m_uHash += (m_uHash << 3);
			m_uHash ^= (m_uHash >> 11);
			m_uHash += (m_uHash << 15);

			return m_uHash;
		}
	}
}