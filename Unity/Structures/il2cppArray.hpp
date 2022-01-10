#pragma once

namespace Unity
{
	template<typename T>
	struct il2cppArray : il2cppObject
	{
		il2cppArrayBounds* m_pBounds = nullptr;
		uintptr_t m_uMaxLength = 0;
		T* m_pValues = nullptr;

		uintptr_t GetData()
		{
			return reinterpret_cast<uintptr_t>(m_pValues);
		}

		T& operator[](unsigned int m_uIndex)
		{
			return *reinterpret_cast<T*>(GetData() + sizeof(T) * m_uIndex);
		}

		T& At(unsigned int m_uIndex)
		{
			return operator[](m_uIndex);
		}

		void Insert(T* m_pArray, uintptr_t m_uSize, uintptr_t m_uIndex = 0)
		{
			if ((m_uSize + m_uIndex) >= m_uMaxLength)
			{
				if (m_uIndex >= m_uMaxLength)
					return;

				m_uSize = m_uMaxLength - m_uIndex;
			}

			for (uintptr_t u = 0; m_uSize > u; ++u)
				operator[](u + m_uIndex) = m_pArray[u];
		}

		void Fill(T m_tValue)
		{
			for (uintptr_t u = 0; m_uMaxLength > u; ++u)
				operator[](u) = m_tValue;
		}

		void RemoveAt(unsigned int m_uIndex)
		{
			if (m_uIndex >= m_uMaxLength)
				return;

			if (m_uMaxLength > (m_uIndex + 1))
			{
				for (unsigned int u = m_uIndex; (static_cast<unsigned int>(m_uMaxLength) - m_uIndex) > u; ++u)
					operator[](u) = operator[](u + 1);
			}

			--m_uMaxLength;
		}

		void RemoveRange(unsigned int m_uIndex, unsigned int m_uCount)
		{
			if (m_uCount == 0)
				m_uCount = 1;

			unsigned int m_uTotal = m_uIndex + m_uCount;
			if (m_uTotal >= m_uMaxLength)
				return;

			if (m_uMaxLength > (m_uTotal + 1))
			{
				for (unsigned int u = m_uIndex; (static_cast<unsigned int>(m_uMaxLength) - m_uTotal) >= u; ++u)
					operator[](u) = operator[](u + m_uCount);
			}

			m_uMaxLength -= m_uCount;
		}

		void RemoveAll()
		{
			if (m_uMaxLength > 0)
			{
				memset(GetData(), 0, sizeof(T) * m_uMaxLength);
				m_uMaxLength = 0;
			}
		}
	};

	// Defined here because its basically same shit
	template<typename T>
	struct il2cppList : il2cppObject
	{
		il2cppArray<T>* m_pListArray;

		il2cppArray<T>* ToArray() { return m_pListArray; }
	};
}