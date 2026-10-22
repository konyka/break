# Plugins / GameplayInsightsEditor

- module root: `Plugins/Animation/GameplayInsights/Source/GameplayInsightsEditor`
- headers: 1; symbols: 4
- symbol kinds: class=1, macro=1, prototype=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine
- PrivateIncludePathModuleNames: GameplayInsights

### `Plugins/Animation/GameplayInsights/Source/GameplayInsightsEditor/Public/InsightsSkeletalMeshComponent.h` (Public)


#### class `UInsightsSkeletalMeshComponent`  
`class UInsightsSkeletalMeshComponent : public USkeletalMeshComponent`  
_L16-26_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `USkeletalMeshComponent`
- L22 _public prototype_ `void SetPoseFromProvider(const IAnimationProvider& InProvider, const FSkeletalMeshPoseMessage& InMessage, const FSkeletalMeshInfo& SkeletalMeshInfo);` — Set this component up from a provider & message
- L25 _public prototype_ `virtual void InitAnim(bool bForceReInit) override;` — USkeletalMeshComponent interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYINSIGHTSEDITOR_API`
