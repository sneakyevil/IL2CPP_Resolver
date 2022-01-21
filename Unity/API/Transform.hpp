#pragma once

namespace Unity
{
	struct STransformFunctions
	{
		void* m_pGetParent = nullptr;
		void* m_pGetRoot = nullptr;
		void* m_pGetChild = nullptr;
		void* m_pGetChildCount = nullptr;
		void* m_pGetPosition = nullptr;
		void* m_pGetRotation = nullptr;
		void* m_pGetLocalPosition = nullptr;
		void* m_pGetLocalScale = nullptr;
		void* m_pSetPosition = nullptr;
		void* m_pSetRotation = nullptr;
		void* m_pSetLocalPosition = nullptr;
		void* m_pSetLocalScale = nullptr;
	};
	extern STransformFunctions TransformFunctions;

	class CTransform : public IL2CPP::CClass
	{
	public:
		CTransform* GetParent()
		{
			return reinterpret_cast<CTransform*(UNITY_CALLING_CONVENTION)(void*)>(TransformFunctions.m_pGetParent)(this);
		}

		CTransform* GetRoot()
		{
			return reinterpret_cast<CTransform*(UNITY_CALLING_CONVENTION)(void*)>(TransformFunctions.m_pGetRoot)(this);
		}

		CTransform* GetChild(int m_iIndex)
		{
			return reinterpret_cast<CTransform*(UNITY_CALLING_CONVENTION)(void*, int)>(TransformFunctions.m_pGetChild)(this, m_iIndex);
		}

		int GetChildCount()
		{
			return reinterpret_cast<int(UNITY_CALLING_CONVENTION)(void*)>(TransformFunctions.m_pGetChildCount)(this);
		}

		Vector3 GetPosition()
		{
			Vector3 vRet;
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3&)>(TransformFunctions.m_pGetPosition)(this, vRet);
			return vRet;
		}

		Quaternion GetRotation()
		{
			Quaternion m_qRet;
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Quaternion&)>(TransformFunctions.m_pGetRotation)(this, m_qRet);
			return m_qRet;
		}

		Vector3 GetLocalPosition()
		{
			Vector3 vRet;
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3&)>(TransformFunctions.m_pGetLocalPosition)(this, vRet);
			return vRet;
		}

		Vector3 GetLocalScale()
		{
			Vector3 vRet;
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3&)>(TransformFunctions.m_pGetLocalScale)(this, vRet);
			return vRet;
		}

		void SetPosition(Vector3 m_vVector)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3)>(TransformFunctions.m_pSetPosition)(this, m_vVector);
		}

		void SetRotation(Quaternion m_qQuat)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Quaternion)>(TransformFunctions.m_pSetRotation)(this, m_qQuat);
		}

		void SetLocalPosition(Vector3 m_vVector)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3)>(TransformFunctions.m_pSetLocalPosition)(this, m_vVector);
		}

		void SetLocalScale(Vector3 m_vVector)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3)>(TransformFunctions.m_pSetLocalScale)(this, m_vVector);
		}
	};

	namespace Transform
	{
		void Initialize();
	}
}