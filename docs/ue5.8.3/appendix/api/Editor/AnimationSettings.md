# Editor / AnimationSettings

- module root: `Source/Editor/AnimationSettings`
- headers: 1; symbols: 7
- symbol kinds: class=1, delegate=1, member=1, prototype=4
- PrivateDependencyModuleNames: AssetRegistry, Core, CoreUObject, Engine, SharedSettingsWidgets

### `Source/Editor/AnimationSettings/Public/AnimationSettingsModule.h` (Public)


#### class `FAnimationSettingsModule`  
`class FAnimationSettingsModule : public IModuleInterface`  
_L10-22_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private prototype_ `static void OnAssetRenamed(const FAssetData& InAssetData, const FString& InOldName);`
- L21 _private member_ `FDelegateHandle OnAssetRenamedHandle;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimationSettings, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAnimationSettings, Log, All);`
