#include "../Includes.hpp"

namespace IL2CPP
{
	DWORD __stdcall ThreadHandler(void* pReserved)
	{
		void* m_pIL2CPPThread = Thread::Attach(Domain::Get());

		CThread* m_pThread = reinterpret_cast<CThread*>(pReserved);
		void* m_pThreadStart = m_pThread->m_pThreadOnStart;
		void* m_pThreadEnd = m_pThread->m_pThreadOnEnd;
		delete m_pThread;

		reinterpret_cast<void(*)()>(m_pThreadStart)();
		if (m_pThreadEnd)
			reinterpret_cast<void(*)()>(m_pThreadEnd)();

		Thread::Detach(m_pIL2CPPThread);
		return 0x0;
	}
}