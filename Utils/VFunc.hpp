#pragma once

namespace VFunc
{
    static void** Find_ASM(void** m_pVTable, int m_iCount, std::initializer_list<unsigned char> m_lASM)
    {
        int m_iASMSize          = static_cast<int>(m_lASM.size());
        unsigned char* m_pBytes = const_cast<unsigned char*>(m_lASM.begin());

        for (int i = 0; m_iCount > i; ++i)
        {
            void* m_pVFunc                  = m_pVTable[i];
            unsigned char* m_pVFuncBytes    = reinterpret_cast<unsigned char*>(m_pVFunc);

            bool m_bAllMatch = true;
            for (int b = 0; m_iASMSize > b; ++b)
            {
                if (m_pBytes[b] != m_pVFuncBytes[b])
                {
                    m_bAllMatch = false;
                    break;
                }
            }

            if (m_bAllMatch)
                return &m_pVTable[i];
        }

        return 0;
    }
}