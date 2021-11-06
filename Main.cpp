#include "Main.hpp"

namespace IL2CPP
{
	bool Initialize(bool m_bWaitForModule)
	{
		if (m_bWaitForModule)
		{
			while (!Data.m_hGameAseembly)
			{
				Data.m_hGameAseembly = GetModuleHandleA(IL2CPP_MAIN_MODULE);
				Sleep(1000); // Prevent high CPU usage!
			}
		}
		else
		{
			Data.m_hGameAseembly = GetModuleHandleA(IL2CPP_MAIN_MODULE);
			if (!Data.m_hGameAseembly) return false;
		}

		if (!UnityAPI::Initialize()) return false;

		return true;
	}

	namespace UnityAPI
	{
		m_eExportObfuscationType m_ExportObfuscation = m_eExportObfuscationType::None;
		int m_iROTObfuscationValue = -1;

		void* ResolveExport(const char* m_pName)
		{
			switch (m_ExportObfuscation)
			{
				case m_eExportObfuscationType::ROT:
				{
					if (m_iROTObfuscationValue == -1) // Bruteforce
					{
						for (int i = 1; 26 > i; ++i)
						{
							void* pReturn = GetProcAddress(Data.m_hGameAseembly, &Unity::Obfuscators::ROT_String(m_pName, i)[0]);
							if (pReturn)
							{
								m_iROTObfuscationValue = i;
								return pReturn;
							}
						}

						return nullptr;
					}
					
					return GetProcAddress(Data.m_hGameAseembly, &Unity::Obfuscators::ROT_String(m_pName, m_iROTObfuscationValue)[0]);
				}
				default: return GetProcAddress(Data.m_hGameAseembly, m_pName);
			}

			return nullptr;
		}

		bool ResolveExport_Boolean(void** m_pAddress, const char* m_pName)
		{
			*m_pAddress = ResolveExport(m_pName);
			IL2CPP_ASSERT(*m_pAddress != nullptr && "Couldn't resolve export!");
			return *m_pAddress != nullptr;
		}

		bool Initialize()
		{
			bool m_bInitExportResolved = false;
			for (int i = 0; m_eExportObfuscationType::MAX > i; ++i)
			{
				m_ExportObfuscation = static_cast<m_eExportObfuscationType>(i);
				if (ResolveExport(IL2CPP_INIT_EXPORT))
				{
					m_bInitExportResolved = true;
					break;
				}
			}

			IL2CPP_ASSERT(m_bInitExportResolved && "Couldn't resolve il2cpp_init!");
			if (!m_bInitExportResolved) return false;

			std::unordered_map<const char*, void**> m_uExports =
			{
				{ IL2CPP_CLASS_FROM_NAME_EXPORT,				&Data.Functions.m_pClassFromName },
				{ IL2CPP_CLASS_GET_FIELD_FROM_NAME_EXPORT,		&Data.Functions.m_pClassGetFieldFromName },
				{ IL2CPP_CLASS_GET_METHOD_FROM_NAME_EXPORT,		&Data.Functions.m_pClassGetMethodFromName },
				{ IL2CPP_CLASS_GET_PROPERTY_FROM_NAME_EXPORT,	&Data.Functions.m_pClassGetPropertyFromName },
				{ IL2CPP_CLASS_GET_TYPE_EXPORT,					&Data.Functions.m_pClassGetType },
				{ IL2CPP_DOMAIN_GET_EXPORT,						&Data.Functions.m_pDomainGet },
				{ IL2CPP_DOMAIN_GET_ASSEMBLIES_EXPORT,			&Data.Functions.m_pDomainGetAssemblies },
				{ IL2CPP_FREE_EXPORT,							&Data.Functions.m_pFree },
				{ IL2CPP_RESOLVE_FUNC_EXPORT,					&Data.Functions.m_pResolveFunction },
				{ IL2CPP_STRING_NEW_EXPORT,						&Data.Functions.m_pStringNew },
				{ IL2CPP_THREAD_ATTACH_EXPORT,					&Data.Functions.m_pThreadAttach },
				{ IL2CPP_THREAD_DETACH_EXPORT,					&Data.Functions.m_pThreadDetach },
				{ IL2CPP_TYPE_GET_OBJECT_EXPORT,				&Data.Functions.m_pTypeGetObject },
			};

			for (std::pair<const char*, void**> m_pExport : m_uExports)
			{
				if (!ResolveExport_Boolean(m_pExport.second, m_pExport.first))
					return false;
			}

			// Unity APIs
			Unity::Component::Initialize();
			Unity::GameObject::Initialize();
			Unity::LayerMask::Initialize();
			Unity::Object::Initialize();
			Unity::Transform::Initialize();

			return true;
		}
	}
}