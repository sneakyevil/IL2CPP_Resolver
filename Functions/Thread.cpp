#include "../Includes.hpp"

namespace IL2CPP
{
	DWORD ThreadHandler(void* pReserved)
	{
		void* m_pIL2CPPThread = Thread::Attach(Domain::Get());

		CThread* m_pThread = reinterpret_cast<CThread*>(pReserved);
		void* m_pThreadStart = m_pThread->m_pThreadOnStart;
		void* m_pThreadEnd = m_pThread->m_pThreadOnEnd;
		delete m_pThread;

		reinterpret_cast<void(*)()>(m_pThreadStart)();
		Thread::Detach(m_pIL2CPPThread);
		reinterpret_cast<void(*)()>(m_pThreadEnd)();

		return 0x0;
	}
}