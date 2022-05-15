#include "../Includes.hpp"

namespace IL2CPP
{
	namespace Helper
	{
		Unity::CComponent* GetMonoBehaviour()
		{
			Unity::il2cppArray<Unity::CGameObject*>* m_pObjects = Unity::Object::FindObjectsOfType<Unity::CGameObject>(UNITY_GAMEOBJECT_CLASS);
			for (uintptr_t u = 0U; m_pObjects->m_uMaxLength > u; ++u)
			{
				Unity::CGameObject* m_pObject = m_pObjects->operator[](static_cast<unsigned int>(u));
				if (!m_pObject) continue;

				Unity::CComponent* m_pMonoBehaviour = m_pObject->GetComponentByIndex(UNITY_MONOBEHAVIOUR_CLASS);
				if (m_pMonoBehaviour)
					return m_pMonoBehaviour;
			}

			return nullptr;
		}
	}
}