#pragma once

// Default Headers
#include <cstdint>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <unordered_map>
#include <Windows.h>

// Application Defines
#ifndef UNITY_VERSION_2022_3_8F1
	// If Unity version is equal or greater than 2022.3.8f1 uncomment this define.
	// #define UNITY_VERSION_2022_3_8F1
#endif

// IL2CPP Defines

// Disable Asserts
//#define IL2CPP_ASSERT(x) assert(0)
#ifndef IL2CPP_ASSERT
	#include <cassert>
	#define IL2CPP_ASSERT(x) assert(x)
#endif

#ifndef IL2CPP_RStr 
	// If you wanna forward to some string encryption just define before including this file.
	#define IL2CPP_RStr(x) x
#endif

#ifndef IL2CPP_MAIN_MODULE
	// If the game for some reason uses diff module name just define own one before including this file.
	#define IL2CPP_MAIN_MODULE IL2CPP_RStr("GameAssembly.dll")
#endif

#include "Defines.hpp"

// IL2CPP Headers
#include "Data.hpp"

// Unity Headers
#include "Unity/Obfuscators.hpp"
#include "Unity/Defines.hpp"
#include "Unity/Structures/il2cpp.hpp"
#include "Unity/Structures/il2cppArray.hpp"
#include "Unity/Structures/il2cppDictionary.hpp"
#include "Unity/Structures/Engine.hpp"
#include "Unity/Structures/System_String.hpp"

// IL2CPP Utils
#include "Utils/Hash.hpp"
#include "Utils/VTable.hpp"

// IL2CPP API Headers
#include "API/Domain.hpp"
#include "API/Class.hpp"
#include "API/ResolveCall.hpp"
#include "API/String.hpp"
#include "API/Thread.hpp"

// IL2CPP Headers before Unity API
#include "SystemTypeCache.hpp"

// Unity Class APIs - So they're accessible everywhere
namespace Unity
{
	class CCamera;
	class CComponent;
	class CGameObject;
	class CLayerMask;
	class CObject;
	class CRigidbody;
	class CTransform;
}

// Unity API
#include "Unity/API/Object.hpp"
#include "Unity/API/GameObject.hpp"
#include "Unity/API/Camera.hpp"
#include "Unity/API/Component.hpp"
#include "Unity/API/LayerMask.hpp"
#include "Unity/API/Rigidbody.hpp"
#include "Unity/API/Transform.hpp"

// IL2CPP Headers after Unity API
#include "Utils/Helper.hpp"
#include "API/Callback.hpp"

namespace IL2CPP
{
	namespace UnityAPI
	{
		enum m_eExportObfuscationType
		{
			None = 0,
			ROT = 1,
			MAX = 2,
		};
		m_eExportObfuscationType m_ExportObfuscation = m_eExportObfuscationType::None;

		int m_ROTObfuscationValue = -1;
		void* ResolveExport(const char* m_Name)
		{
			switch (m_ExportObfuscation)
			{
				case m_eExportObfuscationType::ROT:
				{
					if (m_ROTObfuscationValue == -1) // Bruteforce
					{
						for (int i = 1; 26 > i; ++i)
						{
							void* m_Return = GetProcAddress(Globals.m_GameAssembly, &Unity::Obfuscators::ROT_String(m_Name, i)[0]);
							if (m_Return)
							{
								m_ROTObfuscationValue = i;
								return m_Return;
							}
						}

						return nullptr;
					}

					return GetProcAddress(Globals.m_GameAssembly, &Unity::Obfuscators::ROT_String(m_Name, m_ROTObfuscationValue)[0]);
				}
				default: return GetProcAddress(Globals.m_GameAssembly, m_Name);
			}

			return nullptr;
		}

		bool ResolveExport_Boolean(void** m_Address, const char* m_Name)
		{
			*m_Address = ResolveExport(m_Name);
			IL2CPP_ASSERT(*m_Address != nullptr && "Couldn't resolve export!");
			return (*m_Address);
		}

		bool Initialize()
		{
			bool m_InitExportResolved = false;
			for (int i = 0; m_eExportObfuscationType::MAX > i; ++i)
			{
				m_ExportObfuscation = static_cast<m_eExportObfuscationType>(i);
				if (ResolveExport(IL2CPP_INIT_EXPORT))
				{
					m_InitExportResolved = true;
					break;
				}
			}

			IL2CPP_ASSERT(m_InitExportResolved && "Couldn't resolve il2cpp_init!");
			if (!m_InitExportResolved) 
				return false;

			std::unordered_map<std::string, void**> m_ExportMap =
			{
				{ IL2CPP_CLASS_FROM_NAME_EXPORT,					&Functions.m_ClassFromName },
				{ IL2CPP_CLASS_GET_FIELDS,							&Functions.m_ClassGetFields },
				{ IL2CPP_CLASS_GET_FIELD_FROM_NAME_EXPORT,			&Functions.m_ClassGetFieldFromName },
				{ IL2CPP_CLASS_GET_METHODS,							&Functions.m_ClassGetMethods },
				{ IL2CPP_CLASS_GET_METHOD_FROM_NAME_EXPORT,			&Functions.m_ClassGetMethodFromName },
				{ IL2CPP_CLASS_GET_PROPERTY_FROM_NAME_EXPORT,		&Functions.m_ClassGetPropertyFromName },
				{ IL2CPP_CLASS_GET_TYPE_EXPORT,						&Functions.m_ClassGetType },
				{ IL2CPP_DOMAIN_GET_EXPORT,							&Functions.m_DomainGet },
				{ IL2CPP_DOMAIN_GET_ASSEMBLIES_EXPORT,				&Functions.m_DomainGetAssemblies },
				{ IL2CPP_FREE_EXPORT,								&Functions.m_Free },
				{ IL2CPP_IMAGE_GET_CLASS_EXPORT,					&Functions.m_ImageGetClass },
				{ IL2CPP_IMAGE_GET_CLASS_COUNT_EXPORT,				&Functions.m_ImageGetClassCount },
				{ IL2CPP_RESOLVE_FUNC_EXPORT,						&Functions.m_ResolveFunction },
				{ IL2CPP_STRING_NEW_EXPORT,							&Functions.m_StringNew },
				{ IL2CPP_THREAD_ATTACH_EXPORT,						&Functions.m_ThreadAttach },
				{ IL2CPP_THREAD_DETACH_EXPORT,						&Functions.m_ThreadDetach },
				{ IL2CPP_TYPE_GET_OBJECT_EXPORT,					&Functions.m_TypeGetObject },
				{ IL2CPP_OBJECT_NEW,								&Functions.m_pObjectNew },
				{ IL2CPP_METHOD_GET_PARAM_NAME,						&Functions.m_MethodGetParamName },
				{ IL2CPP_METHOD_GET_PARAM,							&Functions.m_MethodGetParam },
				{ IL2CPP_CLASS_FROM_IL2CPP_TYPE,					&Functions.m_ClassFromIl2cppType },
				{ IL2CPP_FIELD_STATIC_GET_VALUE,					&Functions.m_FieldStaticGetValue },
				{ IL2CPP_FIELD_STATIC_SET_VALUE,					&Functions.m_FieldStaticSetValue },
			};

			for (auto& m_ExportPair : m_ExportMap)
			{
				if (!ResolveExport_Boolean(m_ExportPair.second, &m_ExportPair.first[0]))
					return false;
			}

			// Unity APIs
			Unity::Camera::Initialize();
			Unity::Component::Initialize();
			Unity::GameObject::Initialize();
			Unity::LayerMask::Initialize();
			Unity::Object::Initialize();
			Unity::RigidBody::Initialize();
			Unity::Transform::Initialize();

			// Caches
			IL2CPP::SystemTypeCache::Initializer::PreCache();

			return true;
		}
	}

	/* 
	*	You need to call this, before using any IL2CPP/Unity Functions!
	*	Args:
	*		m_WaitForModule - Will wait for main module if you're loading your dll earlier than the main module.
	*		m_MaxSecondsWait - Max seconds it will wait for main module to load otherwise will return false to prevent infinite loop.
	*/
	bool Initialize(bool m_WaitForModule = false, int m_MaxSecondsWait = 60)
	{
		Globals.m_GameAssembly = GetModuleHandleA(IL2CPP_MAIN_MODULE);

		if (m_WaitForModule)
		{
			int m_SecondsWaited = 0;
			while (!Globals.m_GameAssembly)
			{
				if (m_SecondsWaited >= m_MaxSecondsWait)
					return false;

				Globals.m_GameAssembly = GetModuleHandleA(IL2CPP_MAIN_MODULE);
				++m_SecondsWaited;
				Sleep(1000);
			}
		}

		if (!UnityAPI::Initialize())
			return false;

		return true;
	}
}
