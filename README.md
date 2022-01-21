## IL2CPP Resolver
A run-time API resolver for IL2CPP Unity.

[![Donate](https://img.shields.io/badge/Donate-PayPal-red.svg)](https://www.paypal.com/donate/?hosted_button_id=F86FFE644E55E)

### Quick Example
```cpp
#include "Main.hpp"

void SomeFunction()
{
    IL2CPP::Initialize(); // This needs to be called once!

    Unity::CGameObject* pLocal = Unity::GameObject::Find("LocalPlayer");
    Unity::CComponent* pLocalData = pLocal->GetComponent("PlayerData");
    pLocalData->SetMemberValue<bool>("CanFly", true);
}
```

### Creating Thread
```cpp
void ThreadStart()
{ 
    // Stuff ... Loop ... Smth
}

void ThreadEnd()
{
    // Called after ThreadStart
}

IL2CPP::Thread::Create(ThreadStart, ThreadEnd);
```
