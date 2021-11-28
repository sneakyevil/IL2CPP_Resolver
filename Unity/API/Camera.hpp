#pragma once

namespace Unity
{
	struct SCameraFunctions
	{
		void* m_pGetCurrent = nullptr;
		void* m_pGetMain = nullptr;
		void* m_pGetDepth = nullptr;
		void* m_pSetDepth = nullptr;
		void* m_pGetFieldOfView = nullptr;
		void* m_pSetFieldOfView = nullptr;
		void* m_pWorldToScreen = nullptr;
	};
	extern SCameraFunctions CameraFunctions;

	class CCamera : public IL2CPP::CClass
	{
	public:
		float GetDepth()
		{
			return reinterpret_cast<float(UNITY_CALLING_CONVENTION)(void*)>(CameraFunctions.m_pGetDepth)(this);
		}

		void SetDepth(float m_fValue)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, float)>(CameraFunctions.m_pSetDepth)(this, m_fValue);
		}

		float GetFieldOfView()
		{
			return reinterpret_cast<float(UNITY_CALLING_CONVENTION)(void*)>(CameraFunctions.m_pGetFieldOfView)(this);
		}

		void SetFieldOfView(float m_fValue)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, float)>(CameraFunctions.m_pSetFieldOfView)(this, m_fValue);
		}

		void WorldToScreen(Vector3& m_vWorld, Vector3& m_vScreen, int m_iEye = 2)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3&, int, Vector3&)>(CameraFunctions.m_pWorldToScreen)(this, m_vWorld, m_iEye, m_vScreen);
		}
	};

	namespace Camera
	{
		void Initialize();

		CCamera* GetCurrent();

		CCamera* GetMain();
	}

	enum m_eCameraType : int
	{
		m_eCameraType_Game = 1,
		m_eCameraType_SceneView = 2,
		m_eCameraType_Preview = 4,
		m_eCameraType_VR = 8,
		m_eCameraType_Reflection = 16,
	};

	enum m_eCameraEye : int
	{
		m_eCameraEye_Left = 0,
		m_eCameraEye_Right = 1,
		m_eCameraEye_Center = 2,
	};
}