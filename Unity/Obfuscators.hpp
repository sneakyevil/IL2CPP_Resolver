#pragma once

namespace Unity
{
	namespace Obfuscators
	{
        // Should do the basic work
        std::string ROT_String(const char* pString, int iValue)
        {
            std::string sRet;
            size_t sSize = strlen(pString);
            for (size_t i = 0; sSize > i; ++i)
            {
                bool bIsUppercase = pString[i] >= 'A' && 'Z' >= pString[i];
                bool bIsLowercase = !bIsUppercase && pString[i] >= 'a' && 'z' >= pString[i];
                if (!bIsUppercase && !bIsLowercase)
                {
                    sRet += pString[i];
                    continue;
                }

                int iNewValue = static_cast<int>(pString[i]) + iValue;
                if (bIsUppercase)
                {
                    int iMaxValue = static_cast<int>('Z');
                    while (iNewValue > iMaxValue) iNewValue = static_cast<int>('A') + (iNewValue - iMaxValue);
                }
                else
                {
                    int iMaxValue = static_cast<int>('z');
                    while (iNewValue > iMaxValue) iNewValue = static_cast<int>('a') + (iNewValue - iMaxValue);
                }

                sRet += static_cast<char>(iNewValue);
            }

            sRet += '\0';
            return sRet;
        }
	}
}