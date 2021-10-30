#pragma once

namespace IL2CPP
{
	DWORD __stdcall ThreadHandler(void* pReserved);

	class CThread
	{
	public:
		void* m_pThreadOnStart = nullptr;
		void* m_pThreadOnEnd = nullptr;

		CThread() { /* Why would you even do this? */ }
		CThread(void* m_pOnStart, void* m_pOnEnd)
		{
			m_pThreadOnStart = m_pOnStart;
			m_pThreadOnEnd = m_pOnEnd;

			if (!m_pThreadOnStart)
			{
				IL2CPP_ASSERT("IL2CPP::CThread - m_pThreadOnStart is nullptr");
				return;
			}

			CreateThread(0, 0, ThreadHandler, this, 0, 0);
		}
	};

	namespace Thread
	{
		static void Create(void* m_pOnStart, void* m_pOnEnd = nullptr)
		{
			CThread* pThread = new CThread(m_pOnStart, m_pOnEnd);
			IL2CPP_ASSERT(pThread && "IL2CPP::Thread::Create - Failed!");
		}

		static void* Attach(void* m_pDomain)
		{
			return reinterpret_cast<void*(IL2CPP_CALLING_CONVENTION)(void*)>(IL2CPP::Data.Functions.m_pThreadAttach)(m_pDomain);
		}

		static void Detach(void* m_pThread)
		{
			reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void*)>(IL2CPP::Data.Functions.m_pThreadDetach)(m_pThread);
		}
	}
}