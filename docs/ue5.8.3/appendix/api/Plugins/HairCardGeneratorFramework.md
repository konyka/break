# Plugins / HairCardGeneratorFramework

- module root: `Plugins/Runtime/HairStrands/Source/HairCardGeneratorFramework`
- headers: 1; symbols: 8
- symbol kinds: class=1, function=2, macro=1, member=1, namespace=1, prototype=2
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Runtime/HairStrands/Source/HairCardGeneratorFramework/Public/IHairCardGenerator.h` (Public)


#### class `IHairCardGenerator`  
`class IHairCardGenerator : public IModularFeature`  
_L14-22_
- inherits: `IModularFeature`
- L17 _public member_ `static const FName ModularFeatureName;` — "HairCardGenerator"
- L19 _public prototype_ `virtual bool GenerateHairCardsForLOD(UGroomAsset* Groom, FHairGroupsCardsSourceDescription& CardsDesc) = 0;`
- L21 _public prototype_ `virtual bool IsCompatibleSettings(UHairCardGenerationSettings* OldSettings) = 0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HAIRCARDGENERATORFRAMEWORK_API`
- L24 _namespace_ `namespace HairCardGenerator_Utils`
- L26 _function_ `inline void RegisterModularHairCardGenerator(IHairCardGenerator* Generator)` (scope `HairCardGenerator_Utils`)
- L31 _function_ `inline void UnregisterModularHairCardGenerator(IHairCardGenerator* Generator)` (scope `HairCardGenerator_Utils`)
