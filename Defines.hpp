#pragma once
// Disable Asserts
//#define IL2CPP_ASSERT(x) assert(0)
#ifndef IL2CPP_ASSERT
	#define IL2CPP_ASSERT(x) assert(x)
#endif

#ifndef IL2CPP_MAIN_MODULE
	#define IL2CPP_MAIN_MODULE "GameAssembly.dll"
#endif

#define IL2CPP_INIT_EXPORT								"il2cpp_init"
#define IL2CPP_CLASS_FROM_NAME_EXPORT					"il2cpp_class_from_name"
#define IL2CPP_CLASS_GET_FIELDS							"il2cpp_class_get_fields"
#define IL2CPP_CLASS_GET_FIELD_FROM_NAME_EXPORT			"il2cpp_class_get_field_from_name"
#define IL2CPP_CLASS_GET_METHODS						"il2cpp_class_get_methods"
#define IL2CPP_CLASS_GET_METHOD_FROM_NAME_EXPORT		"il2cpp_class_get_method_from_name"
#define IL2CPP_CLASS_GET_PROPERTY_FROM_NAME_EXPORT		"il2cpp_class_get_property_from_name"
#define IL2CPP_CLASS_GET_TYPE_EXPORT					"il2cpp_class_get_type"
#define IL2CPP_DOMAIN_GET_EXPORT						"il2cpp_domain_get"
#define IL2CPP_DOMAIN_GET_ASSEMBLIES_EXPORT				"il2cpp_domain_get_assemblies"
#define IL2CPP_FREE_EXPORT								"il2cpp_free"
#define IL2CPP_IMAGE_GET_CLASS_EXPORT					"il2cpp_image_get_class"
#define IL2CPP_IMAGE_GET_CLASS_COUNT_EXPORT				"il2cpp_image_get_class_count"
#define IL2CPP_RESOLVE_FUNC_EXPORT						"il2cpp_resolve_icall"
#define IL2CPP_STRING_NEW_EXPORT						"il2cpp_string_new"
#define IL2CPP_THREAD_ATTACH_EXPORT						"il2cpp_thread_attach"
#define IL2CPP_THREAD_DETACH_EXPORT						"il2cpp_thread_detach"
#define IL2CPP_TYPE_GET_OBJECT_EXPORT					"il2cpp_type_get_object"

// Calling Convention
#define IL2CPP_CALLING_CONVENTION __fastcall*