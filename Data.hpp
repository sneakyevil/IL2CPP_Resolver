#pragma once

namespace IL2CPP
{
	struct Globals_t
	{
		HMODULE m_GameAssembly = nullptr;
	};
	Globals_t Globals;

	struct Functions_t
	{
		void* m_ClassFromName = nullptr;
		void* m_ClassGetFields = nullptr;
		void* m_ClassGetFieldFromName = nullptr;
		void* m_ClassGetMethods = nullptr;
		void* m_ClassGetMethodFromName = nullptr;
		void* m_ClassGetPropertyFromName = nullptr;
		void* m_ClassGetType = nullptr;

		void* m_DomainGet = nullptr;
		void* m_DomainGetAssemblies = nullptr;

		void* m_Free = nullptr;

		void* m_ImageGetClass = nullptr;
		void* m_ImageGetClassCount = nullptr;

		void* m_ResolveFunction = nullptr;

		void* m_StringNew = nullptr;

		void* m_ThreadAttach = nullptr;
		void* m_ThreadDetach = nullptr;

		void* m_TypeGetObject = nullptr;

		void* m_pObjectNew = nullptr;
		void* m_MethodGetParamName = nullptr;
		void* m_MethodGetParam = nullptr;
		void* m_ClassFromIl2cppType = nullptr;

		void* m_FieldStaticGetValue = nullptr;
		void* m_FieldStaticSetValue = nullptr;
	};
	Functions_t Functions;
}
