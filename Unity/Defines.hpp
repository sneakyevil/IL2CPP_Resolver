#pragma once
// Calling Convention
#ifdef _WIN64
    #define UNITY_CALLING_CONVENTION __fastcall*
#elif _WIN32
    #define UNITY_CALLING_CONVENTION __cdecl*
#endif

// Camera
#define UNITY_CAMERA_CLASS                                          "UnityEngine.Camera"
#define UNITY_CAMERA_GETCURRENT                                     IL2CPP_RStr(UNITY_CAMERA_CLASS"::get_current")
#define UNITY_CAMERA_GETMAIN                                        IL2CPP_RStr(UNITY_CAMERA_CLASS"::get_main")
#define UNITY_CAMERA_GETDEPTH                                       IL2CPP_RStr(UNITY_CAMERA_CLASS"::get_depth")
#define UNITY_CAMERA_SETDEPTH                                       IL2CPP_RStr(UNITY_CAMERA_CLASS"::set_depth")
#define UNITY_CAMERA_GETFIELDOFVIEW                                 IL2CPP_RStr(UNITY_CAMERA_CLASS"::get_fieldOfView")
#define UNITY_CAMERA_SETFIELDOFVIEW                                 IL2CPP_RStr(UNITY_CAMERA_CLASS"::set_fieldOfView")
#define UNITY_CAMERA_WORLDTOSCREEN                                  IL2CPP_RStr(UNITY_CAMERA_CLASS"::WorldToScreenPoint_Injected")

// Component
#define UNITY_COMPONENT_CLASS										"UnityEngine.Component"
#define UNITY_COMPONENT_GETGAMEOBJECT								IL2CPP_RStr(UNITY_COMPONENT_CLASS"::get_gameObject")
#define UNITY_COMPONENT_GETTRANSFORM								IL2CPP_RStr(UNITY_COMPONENT_CLASS"::get_transform")

// GameObject
#define UNITY_GAMEOBJECT_CLASS										"UnityEngine.GameObject"
#define UNITY_GAMEOBJECT_ADDCOMPONENT 								IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::Internal_AddComponentWithType")
#define UNITY_GAMEOBJECT_CREATEPRIMITIVE 							IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::CreatePrimitive")
#define UNITY_GAMEOBJECT_FIND 										IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::Find")
#define UNITY_GAMEOBJECT_GETCOMPONENT 								IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::GetComponentByName")
#define UNITY_GAMEOBJECT_GETCOMPONENTS								IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::GetComponentsInternal")
#define UNITY_GAMEOBJECT_GETCOMPONENTINCHILDREN 					IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::GetComponentInChildren")
#define UNITY_GAMEOBJECT_GETACTIVE 									IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::get_active")
#define UNITY_GAMEOBJECT_GETLAYER 									IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::get_layer")
#define UNITY_GAMEOBJECT_GETTRANSFORM 								IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::get_transform")
#define UNITY_GAMEOBJECT_SETACTIVE 									IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::set_active")
#define UNITY_GAMEOBJECT_SETLAYER 									IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::set_layer")
#define UNITY_GAMEOBJECT_FINDGAMEOBJECTWITHTAG					    IL2CPP_RStr(UNITY_GAMEOBJECT_CLASS"::FindGameObjectsWithTag")

// LayerMask
#define UNITY_LAYERMASK_CLASS										"UnityEngine.LayerMask"
#define UNITY_LAYERMASK_LAYERTONAME									IL2CPP_RStr(UNITY_LAYERMASK_CLASS"::LayerToName")
#define UNITY_LAYERMASK_NAMETOLAYER									IL2CPP_RStr(UNITY_LAYERMASK_CLASS"::NameToLayer")

// MonoBehaviour
#define UNITY_MONOBEHAVIOUR_CLASS                                   "UnityEngine.MonoBehaviour"

// Object
#define UNITY_OBJECT_CLASS											"UnityEngine.Object"
#define UNITY_OBJECT_DESTROY										IL2CPP_RStr(UNITY_OBJECT_CLASS"::Destroy")
#define UNITY_OBJECT_FINDOBJECTSOFTYPE								IL2CPP_RStr(UNITY_OBJECT_CLASS"::FindObjectsOfType(System.Type,System.Boolean)")
#define UNITY_OBJECT_GETNAME										IL2CPP_RStr(UNITY_OBJECT_CLASS"::GetName")

// Rigidbody
#define UNITY_RIGIDBODY_CLASS										"UnityEngine.Rigidbody"
#define UNITY_RIGIDBODY_GETDETECTCOLLISIONS                         IL2CPP_RStr(UNITY_RIGIDBODY_CLASS"::get_detectCollisions")
#define UNITY_RIGIDBODY_GETVELOCITY                                 IL2CPP_RStr(UNITY_RIGIDBODY_CLASS"::get_velocity_Injected")
#define UNITY_RIGIDBODY_SETDETECTCOLLISIONS                         IL2CPP_RStr(UNITY_RIGIDBODY_CLASS"::set_detectCollisions")
#define UNITY_RIGIDBODY_SETVELOCITY                                 IL2CPP_RStr(UNITY_RIGIDBODY_CLASS"::set_velocity_Injected")

// Transform
#define UNITY_TRANSFORM_CLASS										"UnityEngine.Transform"
#define UNITY_TRANSFORM_GETPARENT                                   IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::GetParent")
#define UNITY_TRANSFORM_GETROOT                                     IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::GetRoot")
#define UNITY_TRANSFORM_GETCHILD                                    IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::GetChild")
#define UNITY_TRANSFORM_GETCHILDCOUNT                               IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::get_childCount")
#define UNITY_TRANSFORM_FINDCHILD                                   IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::FindRelativeTransformWithPath")
#define UNITY_TRANSFORM_GETPOSITION									IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::get_position_Injected")
#define UNITY_TRANSFORM_GETROTATION									IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::get_rotation_Injected")
#define UNITY_TRANSFORM_GETLOCALPOSITION							IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::get_localPosition_Injected")
#define UNITY_TRANSFORM_GETLOCALSCALE								IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::get_localScale_Injected")
#define UNITY_TRANSFORM_SETPOSITION									IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::set_position_Injected")
#define UNITY_TRANSFORM_SETROTATION									IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::set_rotation_Injected")
#define UNITY_TRANSFORM_SETLOCALPOSITION							IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::set_localPosition_Injected")
#define UNITY_TRANSFORM_SETLOCALSCALE								IL2CPP_RStr(UNITY_TRANSFORM_CLASS"::set_localScale_Injected")

namespace Unity
{
    enum m_eTypeEnum
    {
        Type_Void = 1,
        Type_Boolean = 2,
        Type_Character = 3,
        Type_Integer = 8,
        Type_Float = 12,
        Type_String = 14,
        Type_Pointer = 15,
        Type_ValueType = 17,
        Type_Class = 18,
        Type_Variable = 19,
        Type_Array = 20,
        Type_Enum = 85,
	};

    enum m_eFieldAttribute
    {
        FieldAttribute_Compiler,
        FieldAttribute_Private,
        FieldAttribute_FamilyAndAssembly,
        FieldAttribute_Assembly,
        FieldAttribute_Family,
        FieldAttribute_FamilyOrAssembly,
        FieldAttribute_Public,
        FieldAttribute_AccessMask,
        FieldAttribute_Static = 16,
        FieldAttribute_InitOnly = 32,
        FieldAttribute_Literal = 64,
        FieldAttribute_NotSerialized = 128,
        FieldAttribute_HasRVA = 256,
        FieldAttribute_SpecialName = 512,
        FieldAttribute_RTSpecialName = 1024,
        FieldAttribute_HasMarshal = 4096,
        FieldAttribute_InvokeImpl = 8192,
        FieldAttribute_Default = 32768,
        FieldAttribute_Reserved = 38144,
    };
}
