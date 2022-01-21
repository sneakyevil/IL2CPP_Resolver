#include "../../Includes.hpp"

namespace Unity
{
	SCameraFunctions CameraFunctions;

	namespace Camera
	{
		void Initialize()
		{
			IL2CPP::SystemTypeCache::Initializer::Add(UNITY_CAMERA_CLASS);

			CameraFunctions.m_pGetCurrent			= IL2CPP::ResolveCall(UNITY_CAMERA_GETCURRENT);
			CameraFunctions.m_pGetMain				= IL2CPP::ResolveCall(UNITY_CAMERA_GETMAIN);
			CameraFunctions.m_pGetDepth				= IL2CPP::ResolveCall(UNITY_CAMERA_GETDEPTH);
			CameraFunctions.m_pSetDepth				= IL2CPP::ResolveCall(UNITY_CAMERA_SETDEPTH);
			CameraFunctions.m_pGetFieldOfView		= IL2CPP::ResolveCall(UNITY_CAMERA_GETFIELDOFVIEW);
			CameraFunctions.m_pSetFieldOfView		= IL2CPP::ResolveCall(UNITY_CAMERA_SETFIELDOFVIEW);
			CameraFunctions.m_pWorldToScreen		= IL2CPP::ResolveCall(UNITY_CAMERA_WORLDTOSCREEN);
		}

		CCamera* GetCurrent()
		{
			return reinterpret_cast<CCamera*(UNITY_CALLING_CONVENTION)()>(CameraFunctions.m_pGetCurrent)();
		}

		CCamera* GetMain()
		{
			return reinterpret_cast<CCamera*(UNITY_CALLING_CONVENTION)()>(CameraFunctions.m_pGetMain)();
		}
	}
}