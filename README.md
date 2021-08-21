## IL2CPP Resolver
A run-time API resolver for IL2CPP Unity.

# Quick Example
```cpp
#include "IL2CPP_API/Main.hpp"

void SomeFunction()
{
    IL2CPP::Initialize(); // This needs to be called once!

    Unity::CGameObject* pLocal = Unity::GameObject::Find("LocalPlayer");
    Unity::CComponent* pLocalData = pLocal->GetComponent("PlayerData");
    pLocalData->SetFieldValue<bool>(true, "CanFly");
}
```