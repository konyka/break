# Plugins / AudioGameplayVolumeEditor

- module root: `Plugins/AudioGameplayVolume/Source/AudioGameplayVolumeEditor`
- headers: 3; symbols: 18
- symbol kinds: class=3, function=1, member=2, prototype=12
- PrivateDependencyModuleNames: AudioGameplay, CoreUObject, Engine, PropertyEditor, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: AudioGameplayVolume, Core, ToolMenus

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolumeEditor/Private/DetailCustomizations/ReverbVolumeComponentDetail.h` (Private)


#### class `FReverbVolumeComponentDetail`  
`class FReverbVolumeComponentDetail : public IDetailCustomization`  
_L12-26_
- inherits: `IDetailCustomization`
- L16 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L22 _private prototype_ `static void SortCategories(const TMap<FName, IDetailCategoryBuilder*>& AllCategories);`
- L23 _private prototype_ `bool ShouldFilterAsset(const FAssetData& AssetData);`
- L25 _private member_ `TObjectPtr<UReverbVolumeComponent> ComponentToModify = nullptr;`

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolumeEditor/Public/AudioGameplayVolumeComponentVisualizers.h` (Public)


#### class `FAudioGameplayVolumeComponentVisualizer`  
`class FAudioGameplayVolumeComponentVisualizer : public FComponentVisualizer`  
_L12-22_
- inherits: `FComponentVisualizer`
- L16 _public prototype_ `FAudioGameplayVolumeComponentVisualizer() = default;`
- L17 _public prototype_ `virtual ~FAudioGameplayVolumeComponentVisualizer() = default;`
- L20 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`

### `Plugins/AudioGameplayVolume/Source/AudioGameplayVolumeEditor/Public/AudioGameplayVolumeEditorModule.h` (Public)


#### class `FAudioGameplayVolumeEditorModule`  
`class FAudioGameplayVolumeEditorModule : public IModuleInterface`  
_L14-29_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _protected prototype_ `void HandleCustomPropertyLayouts(bool bRegister);`
- L24 _protected prototype_ `void HandleComponentVisualizers(bool bRegister);`
- L26 _protected prototype_ `void RegisterComponentVisualizer(FName ComponentClassName, TSharedPtr<FComponentVisualizer> Visualizer);`
- L28 _protected member_ `TArray<FName> RegisteredComponentVisualizers;`

#### Free symbols / members of external scopes

- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(AudioGameplayVolumeEditor, Log, All);`
