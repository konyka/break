# Plugins / MetaHumanCaptureDataEditor

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureDataEditor`
- headers: 3; symbols: 21
- symbol kinds: class=2, function=1, macro=1, member=5, namespace=1, prototype=10, typedef=1
- PrivateDependencyModuleNames: CaptureDataCore, CaptureDataEditor, Core, CoreUObject, Engine, InputCore, MetaHumanCoreEditor, MetaHumanImageViewerEditor, Slate, SlateCore
- PublicDependencyModuleNames: 

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureDataEditor/Private/MetaHumanCaptureDataEditorModule.h` (Private)


#### class `FMetaHumanCaptureDataEditorModule`  
`class FMetaHumanCaptureDataEditorModule : public IModuleInterface`  
_L7-20_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private member_ `FName ClassToUnregisterOnShutdown;` — StaticClass is not safe on shutdown, so we cache the name, and use this to unregister on shut down

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureDataEditor/Public/CaptureDataUtils.h` (Public)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace MetaHumanCaptureDataUtils`
- L13 _prototype_ `USceneComponent* CreatePreviewComponent(UCaptureData* InCaptureData, UObject* InObject);` (scope `MetaHumanCaptureDataUtils`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanCaptureDataEditor/Public/SMetaHumanCameraCombo.h` (Public)


#### class `SMetaHumanCameraCombo`  
`class SMetaHumanCameraCombo : public SCompoundWidget`  
_L14-43_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanCameraCombo)`
- L22 _public typedef_ `typedef TSharedPtr<FString> FComboItemType;`
- L24 _public prototype_ `void Construct(const FArguments& InArgs, const TArray<TSharedPtr<FString>>* InOptionsSource, const FString* InCamera, TObjectPtr<UObject> InPropertyOwner, TSharedPtr<IPropertyHandle> InProperty);`
- L26 _public prototype_ `void HandleSourceDataChanged(class UFootageCaptureData* InFootageCaptureData, class USoundWave* InAudio, bool bInResetRanges);`
- L27 _public prototype_ `void HandleSourceDataChanged(bool bInResetRanges);`
- L29 _public prototype_ `TSharedRef<SWidget> MakeWidgetForOption(FComboItemType InOption);`
- L31 _public prototype_ `void OnSelectionChanged(FComboItemType InNewValue, ESelectInfo::Type);`
- L33 _public prototype_ `FText GetCurrentItemLabel() const;`
- L35 _public prototype_ `bool IsEnabled() const;`
- L39 _private member_ `const FString* Camera = nullptr;`
- L40 _private member_ `TObjectPtr<UObject> PropertyOwner;`
- L41 _private member_ `TSharedPtr<IPropertyHandle> Property;`
- L42 _private member_ `TSharedPtr<SComboBox<FComboItemType>> Combo;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCAPTUREDATAEDITOR_API`
