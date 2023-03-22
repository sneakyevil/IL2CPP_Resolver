#include "../Includes.hpp"

namespace IL2CPP
{
	namespace Callback
	{
		const int ON_UPDATE_OFFSET = 0x1C * sizeof(void*);
		const int ON_FIXED_UPDATE_OFFSET = 0x1D * sizeof(void*);
		const int ON_LATE_UPDATE_OFFSET = 0x1E * sizeof(void*);
		//const int DO_GUI_OFFSET = 0x21 * sizeof(void*);

		struct _VFuncCallback
		{
			std::vector<void*> m_vFunctions;

			void** m_pVTable = nullptr;
			void* m_pOriginal = nullptr;
		};

		namespace OnUpdate
		{
			_VFuncCallback Data;

			void Add(void* m_pFunction) { Data.m_vFunctions.emplace_back(m_pFunction); }

			void __fastcall Caller(void* rcx)
			{
				for (void* m_pFunction : Data.m_vFunctions)
					reinterpret_cast<void(*)()>(m_pFunction)();

				reinterpret_cast<void(__fastcall*)(void*)>(Data.m_pOriginal)(rcx);
			}
		}

		namespace OnLateUpdate
		{
			_VFuncCallback Data;

			void Add(void* m_pFunction) { Data.m_vFunctions.emplace_back(m_pFunction); }

			void __fastcall Caller(void* rcx)
			{
				for (void* m_pFunction : Data.m_vFunctions)
					reinterpret_cast<void(*)()>(m_pFunction)();

				reinterpret_cast<void(__fastcall*)(void*)>(Data.m_pOriginal)(rcx);
			}
		}

		void Replace_VFunc(void** m_pVTableFunc, void* m_pCaller, void** m_pCallbackOriginal)
		{
			DWORD m_dOldProtection = 0x0;
			if (m_pVTableFunc && VirtualProtect(m_pVTableFunc, sizeof(void*), PAGE_READWRITE, &m_dOldProtection))
			{
				if (m_pCallbackOriginal) *m_pCallbackOriginal = *m_pVTableFunc;
				*m_pVTableFunc = m_pCaller;

				VirtualProtect(m_pVTableFunc, sizeof(void*), m_dOldProtection, &m_dOldProtection);
			}
		}

		void Initialize()
		{
			void* m_pThread = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());

			// Fetch
			{
				void* m_pMonoBehaviourVTable = *(void**)IL2CPP::Helper::GetMonoBehaviour()->m_CachedPtr;
				if (m_pMonoBehaviourVTable) // x86: welcome back my old friend :)
				{
					OnUpdate::Data.m_pVTable = (void**)((DWORD)m_pMonoBehaviourVTable + ON_UPDATE_OFFSET);
					OnLateUpdate::Data.m_pVTable = (void**)((DWORD)m_pMonoBehaviourVTable + ON_LATE_UPDATE_OFFSET);
				}
			}

			IL2CPP::Thread::Detach(m_pThread);

			// Replace
			{
				Replace_VFunc(OnUpdate::Data.m_pVTable,		OnUpdate::Caller,		&OnUpdate::Data.m_pOriginal);
				Replace_VFunc(OnLateUpdate::Data.m_pVTable,	OnLateUpdate::Caller,	&OnLateUpdate::Data.m_pOriginal);
			}
		}

		void Uninitialize()
		{
			Replace_VFunc(OnUpdate::Data.m_pVTable,		OnUpdate::Data.m_pOriginal,		nullptr);
			Replace_VFunc(OnLateUpdate::Data.m_pVTable,	OnLateUpdate::Data.m_pOriginal,	nullptr);
		}
	}
}