# Plugins / RemoteControlActorModifierBridge

- module root: `Plugins/Experimental/RemoteControlActorModifierBridge/Source`
- headers: 1; symbols: 4
- symbol kinds: class=1, prototype=3
- PrivateDependencyModuleNames: ActorModifierCore, Core, CoreUObject, OperatorStackEditor, PropertyAnimatorCore, PropertyEditor, RemoteControl, RemoteControlUI

### `Plugins/Experimental/RemoteControlActorModifierBridge/Source/Private/RemoteControlActorModifierBridgeModule.h` (Private)


#### class `FRemoteControlActorModifierBridgeModule`  
`class FRemoteControlActorModifierBridgeModule : public IModuleInterface`  
_L14-24_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _private prototype_ `bool ResolverActorModifierProperty(const TSharedRef<FRemoteControlProperty>& InProperty, TArray<UObject*>& InOutBoundObjects, TSharedPtr<FPropertyPath>& OutPropertyPath);`
