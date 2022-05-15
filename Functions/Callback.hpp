#pragma once

namespace IL2CPP
{
	namespace Callback
	{
		namespace OnUpdate
		{
			void Add(void* m_pFunction);
		}

		namespace OnLateUpdate
		{
			void Add(void* m_pFunction);
		}

		void Initialize();

		void Uninitialize();
	}
}