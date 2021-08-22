#pragma once
// Calling Convention
#define UNITY_CALLING_CONVENTION __fastcall*

// Component
#define UNITY_COMPONENT_GETGAMEOBJECT "UnityEngine.Component::get_gameObject"
#define UNITY_COMPONENT_GETTRANSFORM "UnityEngine.Component::get_transform"

// GameObject
#define UNITY_GAMEOBJECT_CREATEPRIMITIVE "UnityEngine.GameObject::CreatePrimitive"
#define UNITY_GAMEOBJECT_FIND "UnityEngine.GameObject::Find"
#define UNITY_GAMEOBJECT_GETCOMPONENT "UnityEngine.GameObject::GetComponentByName"
#define UNITY_GAMEOBJECT_GETTRANSFORM "UnityEngine.GameObject::get_transform"

// Object
#define UNITY_OBJECT_DESTROY "UnityEngine.Object::Destroy"
#define UNITY_OBJECT_FINDOBJECTSOFTYPE "UnityEngine.Object::FindObjectsOfType"

// Transform
#define UNITY_TRANSFORM_GETPOSITION "UnityEngine.Transform::get_position_Injected"
#define UNITY_TRANSFORM_GETLOCALPOSITION "UnityEngine.Transform::get_localPosition_Injected"
#define UNITY_TRANSFORM_SETPOSITION "UnityEngine.Transform::set_position_Injected"
#define UNITY_TRANSFORM_SETLOCALPOSITION "UnityEngine.Transform::set_localPosition_Injected"