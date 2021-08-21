#pragma once
// Disable Asserts
// #define IL2CPP_ASSERT(x) ((void)(x))
#include "Defines.hpp"

#include <assert.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>

// Unity
#include "Unity/Includes.hpp"

// IL2CPP API
#include "Data.hpp" // Pointers, Variables, etc...

// IL2CPP
#include "Functions/Class.hpp"
#include "Functions/ResolveCall.hpp"
#include "Functions/String.hpp"

// Unity API - Include here so we have access to some cute IL2CPP Features
#include "Unity/API/_TEMPLATE_API.hpp"
#include "Unity/API/Object.hpp"
#include "Unity/API/Component.hpp"
#include "Unity/API/GameObject.hpp"
#include "Unity/API/Transform.hpp"