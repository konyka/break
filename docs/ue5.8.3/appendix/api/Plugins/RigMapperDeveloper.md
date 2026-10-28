# Plugins / RigMapperDeveloper

- module root: `Plugins/Experimental/Animation/RigMapper/Source/RigMapperDeveloper`
- headers: 1; symbols: 3
- symbol kinds: class=1, prototype=2
- PrivateDependencyModuleNames: AnimationCore, ControlRig, Core, CoreUObject, Engine, Json, RigMapper
- PublicDependencyModuleNames: 

### `Plugins/Experimental/Animation/RigMapper/Source/RigMapperDeveloper/Public/RigMapperDeveloperModule.h` (Public)


#### class `FRigMapperDeveloperModule`  
`class FRigMapperDeveloperModule : public IModuleInterface`  
_L11-18_
- inherits: `IModuleInterface`
- desc: FRigMapperDeveloperModule Module for the developer only content in the RigMapper plugin
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
