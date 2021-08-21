#pragma once
#ifndef IL2CPP_ASSERT
	#define IL2CPP_ASSERT(x) assert(x)
#endif

#ifndef IL2CPP_MAIN_MODULE
	#define IL2CPP_MAIN_MODULE "GameAssembly.dll"
#endif

#define IL2CPP_INIT_EXPORT "il2cpp_init"
#define IL2CPP_CLASS_GET_FIELD_FROM_NAME_EXPORT "il2cpp_class_get_field_from_name"
#define IL2CPP_CLASS_GET_METHOD_FROM_NAME_EXPORT "il2cpp_class_get_method_from_name"
#define IL2CPP_FREE_EXPORT "il2cpp_free"
#define IL2CPP_RESOLVE_FUNC_EXPORT "il2cpp_resolve_icall"
#define IL2CPP_STRING_NEW_EXPORT "il2cpp_string_new"

// Calling Convention
#define IL2CPP_CALLING_CONVENTION __fastcall*