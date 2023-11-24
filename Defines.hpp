#pragma once

#define IL2CPP_INIT_EXPORT								IL2CPP_RStr("il2cpp_init")
#define IL2CPP_CLASS_FROM_NAME_EXPORT					IL2CPP_RStr("il2cpp_class_from_name")
#define IL2CPP_CLASS_GET_FIELDS							IL2CPP_RStr("il2cpp_class_get_fields")
#define IL2CPP_CLASS_GET_FIELD_FROM_NAME_EXPORT			IL2CPP_RStr("il2cpp_class_get_field_from_name")
#define IL2CPP_CLASS_GET_METHODS						IL2CPP_RStr("il2cpp_class_get_methods")
#define IL2CPP_CLASS_GET_METHOD_FROM_NAME_EXPORT		IL2CPP_RStr("il2cpp_class_get_method_from_name")
#define IL2CPP_CLASS_GET_PROPERTY_FROM_NAME_EXPORT		IL2CPP_RStr("il2cpp_class_get_property_from_name")
#define IL2CPP_CLASS_GET_TYPE_EXPORT					IL2CPP_RStr("il2cpp_class_get_type")
#define IL2CPP_DOMAIN_GET_EXPORT						IL2CPP_RStr("il2cpp_domain_get")
#define IL2CPP_DOMAIN_GET_ASSEMBLIES_EXPORT				IL2CPP_RStr("il2cpp_domain_get_assemblies")
#define IL2CPP_FREE_EXPORT								IL2CPP_RStr("il2cpp_free")
#define IL2CPP_IMAGE_GET_CLASS_EXPORT					IL2CPP_RStr("il2cpp_image_get_class")
#define IL2CPP_IMAGE_GET_CLASS_COUNT_EXPORT				IL2CPP_RStr("il2cpp_image_get_class_count")
#define IL2CPP_RESOLVE_FUNC_EXPORT						IL2CPP_RStr("il2cpp_resolve_icall")
#define IL2CPP_STRING_NEW_EXPORT						IL2CPP_RStr("il2cpp_string_new")
#define IL2CPP_THREAD_ATTACH_EXPORT						IL2CPP_RStr("il2cpp_thread_attach")
#define IL2CPP_THREAD_DETACH_EXPORT						IL2CPP_RStr("il2cpp_thread_detach")
#define IL2CPP_TYPE_GET_OBJECT_EXPORT					IL2CPP_RStr("il2cpp_type_get_object")
#define IL2CPP_OBJECT_NEW								IL2CPP_RStr("il2cpp_object_new")
#define IL2CPP_METHOD_GET_PARAM_NAME					IL2CPP_RStr("il2cpp_method_get_param_name")
#define IL2CPP_METHOD_GET_PARAM							IL2CPP_RStr("il2cpp_method_get_param")
#define IL2CPP_CLASS_FROM_IL2CPP_TYPE					IL2CPP_RStr("il2cpp_class_from_il2cpp_type")

// Calling Convention
#ifdef _WIN64
	#define IL2CPP_CALLING_CONVENTION __fastcall*
#elif _WIN32
	#define IL2CPP_CALLING_CONVENTION __cdecl*
#endif
