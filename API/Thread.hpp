#pragma once

namespace IL2CPP
{
	namespace Thread
	{
		void* Attach(void* m_Domain)
		{
			return reinterpret_cast<void* (IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ThreadAttach)(m_Domain);
		}

		void Detach(void* m_Thread)
		{
			reinterpret_cast<void(IL2CPP_CALLING_CONVENTION)(void*)>(Functions.m_ThreadDetach)(m_Thread);
		}
	}

	// Our Stuff
	class CThread
	{
	public:
		void* m_OnStart = nullptr;
		void* m_OnEnd = nullptr;

		static DWORD __stdcall Handler(void* m_Reserved)
		{
			void* m_IL2CPPThread = Thread::Attach(Domain::Get());

			CThread* m_Thread = reinterpret_cast<CThread*>(m_Reserved);
			void* m_ThreadStart = m_Thread->m_OnStart;
			void* m_ThreadEnd = m_Thread->m_OnEnd;
			delete m_Thread;

			reinterpret_cast<void(*)()>(m_ThreadStart)();
			if (m_ThreadEnd)
				reinterpret_cast<void(*)()>(m_ThreadEnd)();

			Thread::Detach(m_IL2CPPThread);
			return 0x0;
		}

		CThread() { /* Why would you even do this? */ }
		CThread(void* m_OnStartFunc, void* m_OnEndFunc)
		{
			m_OnStart	= m_OnStartFunc;
			m_OnEnd		= m_OnEndFunc;

			if (!m_OnStart)
			{
				IL2CPP_ASSERT("IL2CPP::CThread - m_OnStart is nullptr");
				return;
			}

			HANDLE m_Thread = CreateThread(0, 0, Handler, this, 0, 0);
			if (m_Thread)
				CloseHandle(m_Thread);
		}
	};

	namespace Thread
	{
		void Create(void* m_OnStartFunc, void* m_OnEndFunc = nullptr)
		{
			CThread* m_Thread = new CThread(m_OnStartFunc, m_OnEndFunc);
			IL2CPP_ASSERT(m_Thread && "IL2CPP::Thread::Create - Failed!");
		}
	}
}