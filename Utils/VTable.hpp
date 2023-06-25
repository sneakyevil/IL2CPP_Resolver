#pragma once

namespace IL2CPP
{
    namespace Utils
    {
        namespace VTable
        {
            void ReplaceFunction(void** m_VTableFunc, void* m_NewFunc, void** m_Original = nullptr)
            {
                if (!m_VTableFunc)
                    return;

                DWORD m_OldProtection = 0x0;
                if (!VirtualProtect(m_VTableFunc, sizeof(void*), PAGE_READWRITE, &m_OldProtection))
                    return;
             
                if (m_Original) 
                    *m_Original = *m_VTableFunc;

                *m_VTableFunc = m_NewFunc;
                VirtualProtect(m_VTableFunc, sizeof(void*), m_OldProtection, &m_OldProtection);
            }

            void** FindFunction(void** m_VTable, int m_Count, std::initializer_list<unsigned char> m_Opcodes)
            {
                size_t m_OpcodeSize = m_Opcodes.size();
                const void* m_OpcodesPtr = m_Opcodes.begin();

                for (int i = 0; m_Count > i; ++i)
                {
                    if (memcmp(m_VTable[i], m_OpcodesPtr, m_OpcodeSize) == 0)
                        return &m_VTable[i];
                }

                return 0;
            }
        }
    }
}