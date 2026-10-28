# Plugins / CommonUIEditor

- module root: `Plugins/Runtime/CommonUI/Source/CommonUIEditor`
- headers: 4; symbols: 29
- symbol kinds: class=4, function=4, member=1, prototype=20
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetRegistry, CommonUI, Core, CoreUObject, EditorWidgets, Engine, EngineAssetDefinitions, GameplayTags, GameplayTagsEditor, InputCore, PropertyEditor, Slate, SlateCore, ToolMenus, UMG, UnrealEd
- PrivateIncludePathModuleNames: DataTableEditor

### `Plugins/Runtime/CommonUI/Source/CommonUIEditor/Private/AssetDefinition_CommonGenericInputActionDataTable.h` (Private)


#### class `UAssetDefinition_CommonGenericInputActionDataTable`  
`class UAssetDefinition_CommonGenericInputActionDataTable : public UAssetDefinition_DataTable`  
_L9-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_DataTable`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/CommonUI/Source/CommonUIEditor/Private/CommonVideoPlayerCustomization.h` (Private)


#### class `FCommonVideoPlayerCustomization`  
`class FCommonVideoPlayerCustomization : public IDetailCustomization`  
_L13-40_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L21 _private prototype_ `FReply HandlePlayClicked();`
- L22 _private prototype_ `FReply HandleGoToStartClicked();`
- L23 _private prototype_ `FReply HandleBackwardStep();`
- L24 _private prototype_ `FReply HandleForwardStep();`
- L25 _private prototype_ `FReply HandleGoToEndClicked();`
- L26 _private prototype_ `FReply HandlePauseClicked();`
- L27 _private prototype_ `FReply HandleReverseClicked();`
- L28 _private prototype_ `EPlaybackMode::Type GetPlaybackMode() const;`
- L30 _private prototype_ `TOptional<float> GetMaxPlaybackTimeValue() const;`
- L31 _private prototype_ `TOptional<float> GetPlaybackTimeValue() const;`
- L32 _private prototype_ `void HandlePlaybackTimeCommitted(float NewTime, ETextCommit::Type);`
- L33 _private prototype_ `FText GetMaxPlaybackTimeText() const;`
- L35 _private prototype_ `TSharedRef<SWidget> HandleCreateMuteToggleWidget() const;`
- L36 _private prototype_ `const FSlateBrush* GetMuteToggleIcon() const;`
- L37 _private prototype_ `FReply HandleToggleMuteClicked() const;`
- L39 _private member_ `TWeakObjectPtr<UCommonVideoPlayer> VideoPlayer;`

### `Plugins/Runtime/CommonUI/Source/CommonUIEditor/Public/CommonGenericInputActionDataTableFactory.h` (Public)


#### class `UCommonGenericInputActionDataTableFactory`  
`class UCommonGenericInputActionDataTableFactory : public UFactory`  
_L9-17_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L14 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory interface

### `Plugins/Runtime/CommonUI/Source/CommonUIEditor/Public/CommonUIEditorModule.h` (Public)


#### class `FCommonUIEditorModule`  
`class FCommonUIEditorModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L12 _public prototype_ `virtual void ShutdownModule() override;`
