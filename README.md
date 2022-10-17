## IL2CPP Resolver
A run-time API resolver for IL2CPP Unity.

[External Version](https://github.com/extremeblackliu/IL2CPP_Resolver_External)

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

### Registering OnUpdate Callback
```cpp
void OurUpdateFunction()
{
    // Your special code...
}

void OnLoad()
{
    IL2CPP::Initialize();

    IL2CPP::Callback::Initialize();
    IL2CPP::Callback::OnUpdate::Add(OurUpdateFunction);
}
```

More: https://sneakyevil.gitbook.io/il2cpp-resolver/
