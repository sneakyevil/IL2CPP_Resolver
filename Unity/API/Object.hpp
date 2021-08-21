#pragma once

namespace Unity
{
	struct SObjectFunctions
	{
		void* m_pDestroy = nullptr;
	};
	extern SObjectFunctions ObjectFunctions;

	class CObject : public IL2CPP::Class
	{
	public:
		void Destroy(float fTimeDelay = 0.f)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, float)>(ObjectFunctions.m_pDestroy)(this, fTimeDelay);
		}
	};

	namespace Object
	{
		void Initialize();
	}
}