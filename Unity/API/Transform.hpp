#pragma once

namespace Unity
{
	struct STransformFunctions
	{
		void* m_pGetPosition = nullptr;
		void* m_pGetLocalPosition = nullptr;
		void* m_pSetPosition = nullptr;
		void* m_pSetLocalPosition = nullptr;
	};
	extern STransformFunctions TransformFunctions;

	class CTransform : public IL2CPP::Class
	{
	public:
		Vector3 GetPosition()
		{
			Vector3 vRet;
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3&)>(TransformFunctions.m_pGetPosition)(this, vRet);
			return vRet;
		}

		Vector3 GetLocalPosition()
		{
			Vector3 vRet;
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3&)>(TransformFunctions.m_pGetLocalPosition)(this, vRet);
			return vRet;
		}

		void SetPosition(Vector3 m_vVector)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3)>(TransformFunctions.m_pSetPosition)(this, m_vVector);
		}

		void SetLocalPosition(Vector3 m_vVector)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3)>(TransformFunctions.m_pSetLocalPosition)(this, m_vVector);
		}
	};

	namespace Transform
	{
		void Initialize();
	}
}