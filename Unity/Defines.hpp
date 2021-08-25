#pragma once
// Calling Convention
#define UNITY_CALLING_CONVENTION __fastcall*

// Component
#define UNITY_COMPONENT_CLASS										"UnityEngine.Component"
#define UNITY_COMPONENT_GETGAMEOBJECT								UNITY_COMPONENT_CLASS"::get_gameObject"
#define UNITY_COMPONENT_GETTRANSFORM								UNITY_COMPONENT_CLASS"::get_transform"

// GameObject
#define UNITY_GAMEOBJECT_CLASS										"UnityEngine.GameObject"
#define UNITY_GAMEOBJECT_CREATEPRIMITIVE 							UNITY_GAMEOBJECT_CLASS"::CreatePrimitive"
#define UNITY_GAMEOBJECT_FIND 										UNITY_GAMEOBJECT_CLASS"::Find"
#define UNITY_GAMEOBJECT_GETCOMPONENT 								UNITY_GAMEOBJECT_CLASS"::GetComponentByName"
#define UNITY_GAMEOBJECT_GETCOMPONENTS								UNITY_GAMEOBJECT_CLASS"::GetComponentsInternal"
#define UNITY_GAMEOBJECT_GETLAYER 									UNITY_GAMEOBJECT_CLASS"::get_layer"
#define UNITY_GAMEOBJECT_GETTRANSFORM 								UNITY_GAMEOBJECT_CLASS"::get_transform"
#define UNITY_GAMEOBJECT_SETLAYER 									UNITY_GAMEOBJECT_CLASS"::set_layer"

// LayerMask
#define UNITY_LAYERMASK_CLASS										"UnityEngine.LayerMask"
#define UNITY_LAYERMASK_LAYERTONAME									UNITY_LAYERMASK_CLASS"::LayerToName"
#define UNITY_LAYERMASK_NAMETOLAYER									UNITY_LAYERMASK_CLASS"::NameToLayer"

// Object
#define UNITY_OBJECT_CLASS											"UnityEngine.Object"
#define UNITY_OBJECT_DESTROY										UNITY_OBJECT_CLASS"::Destroy"
#define UNITY_OBJECT_FINDOBJECTSOFTYPE								UNITY_OBJECT_CLASS"::FindObjectsOfType"
#define UNITY_OBJECT_GETNAME										UNITY_OBJECT_CLASS"::GetName"

// Transform
#define UNITY_TRANSFORM_CLASS										"UnityEngine.Transform"
#define UNITY_TRANSFORM_GETPOSITION									UNITY_TRANSFORM_CLASS"::get_position_Injected"
#define UNITY_TRANSFORM_GETLOCALPOSITION							UNITY_TRANSFORM_CLASS"::get_localPosition_Injected"
#define UNITY_TRANSFORM_GETLOCALROTATION							UNITY_TRANSFORM_CLASS"::get_localRotation_Injected"
#define UNITY_TRANSFORM_GETLOCALSCALE								UNITY_TRANSFORM_CLASS"::get_localScale_Injected"
#define UNITY_TRANSFORM_SETPOSITION									UNITY_TRANSFORM_CLASS"::set_position_Injected"
#define UNITY_TRANSFORM_SETLOCALPOSITION							UNITY_TRANSFORM_CLASS"::set_localPosition_Injected"
#define UNITY_TRANSFORM_SETLOCALROTATION							UNITY_TRANSFORM_CLASS"::set_localRotation_Injected"
#define UNITY_TRANSFORM_SETLOCALSCALE								UNITY_TRANSFORM_CLASS"::set_localScale_Injected"