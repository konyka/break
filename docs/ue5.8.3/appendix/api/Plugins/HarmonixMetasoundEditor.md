# Plugins / HarmonixMetasoundEditor

- module root: `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundEditor`
- headers: 10; symbols: 74
- symbol kinds: class=11, delegate=1, function=1, macro=3, member=7, namespace=1, prototype=50
- PrivateDependencyModuleNames: AssetDefinition, DetailCustomizations, Engine, HarmonixMetasound, HarmonixMidi, MetasoundEditor, MetasoundFrontend, MetasoundGraphCore, Projects, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, PropertyEditor, Slate, SlateCore

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundEditor/Private/AssetDefinition_MidiStepSequence.h` (Private)


#### class `UAssetDefinition_MidiStepSequence`  
`class UAssetDefinition_MidiStepSequence : public UAssetDefinitionDefault`  
_L13-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L19 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L20 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L22 _public prototype_ `virtual bool CanImport() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define ASSET_MENU_ITEM_GROUPING_CHEKED_IN 0`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundEditor/Private/AssetDefinition_MidiStutterSequence.h` (Private)


#### class `UAssetDefinition_MidiStutterSequence`  
`class UAssetDefinition_MidiStutterSequence : public UAssetDefinitionDefault`  
_L13-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L19 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L20 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L22 _public prototype_ `virtual bool CanImport() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define ASSET_MENU_ITEM_GROUPING_CHEKED_IN 0`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundEditor/Private/AssetDefinition_MusicAssets.h` (Private)


#### class `UAssetDefinition_MetasoundMusic`  
`class UAssetDefinition_MetasoundMusic : public UAssetDefinitionDefault`  
_L13-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L19 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L20 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L22 _public prototype_ `virtual bool CanImport() const override;`
- L23 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L24 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`

#### class `UAssetDefinition_WaveMusic`  
`class UAssetDefinition_WaveMusic : public UAssetDefinitionDefault`  
_L28-40_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L33 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L34 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L35 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L36 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L37 _public prototype_ `virtual bool CanImport() const override;`
- L38 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L39 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define ASSET_MENU_ITEM_GROUPING_CHEKED_IN 0`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundEditor/Private/HarmonixMetasoundMusicFactory.h` (Private)


#### class `UHarmonixMetasoundMusicFactory`  
`class UHarmonixMetasoundMusicFactory : public UFactory`  
_L9-18_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L13 _public prototype_ `UHarmonixMetasoundMusicFactory();`
- L15 _public prototype_ `virtual FText GetDisplayName() const override;`
- L16 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundEditor/Private/HarmonixMetasoundSlateStyle.h` (Private)


#### class `HarmonixMetasoundEditor::FSlateStyle`  
`class FSlateStyle final : public FSlateStyleSet`  
_L8-22_
- inherits: `FSlateStyleSet`
- L12 _public prototype_ `FSlateStyle();`
- L13 _public prototype_ `static const FSlateStyle& Get();`
- L15 _public prototype_ `void SetCustomPinStyle(const FName PinType, const FLinearColor& PinColor, FSlateBrush* ConnectedIcon, FSlateBrush* DisconnectedIcon);`
- L17 _public prototype_ `const FLinearColor& GetPinColor(FName PinType) const;`
- L18 _public prototype_ `const FSlateBrush* GetConnectedIcon(FName PinType) const;`
- L19 _public prototype_ `const FSlateBrush* GetDisconnectedIcon(FName PinType) const;`
- L21 _public prototype_ `~FSlateStyle();`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace HarmonixMetasoundEditor`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundEditor/Private/HarmonixWaveMusicFactory.h` (Private)


#### class `UHarmonixWaveMusicFactory`  
`class UHarmonixWaveMusicFactory : public UFactory`  
_L10-19_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L14 _public prototype_ `UHarmonixWaveMusicFactory();`
- L16 _public prototype_ `virtual FText GetDisplayName() const override;`
- L17 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundEditor/Private/MidiStepSequenceDetailCustomization.h` (Private)


#### class `FMidiStepSequenceDetailCustomization`  
`class FMidiStepSequenceDetailCustomization : public IDetailCustomization`  
_L21-49_
- inherits: `IDetailCustomization`
- L24 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L29 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L31 _private member_ `TWeakObjectPtr<UObject> MidiStepSequence;`
- L32 _private member_ `TArray<TSharedPtr<SScrollBox>> CellWidgetContainerScrollBoxes;`
- L33 _private member_ `int32 CurrentPageNumber = 1;`
- L34 _private member_ `int32 NumPages = 1;`
- L37 _private member_ `FSlateColor CellDisabledColor = FSlateColor(FLinearColor(0.5f, 0.5f, 0.5f));` — cell button colors for disabled, enabled, and continuation-enabled cells
- L38 _private member_ `FSlateColor CellEnabledColor = FSlateColor(FLinearColor(124 / 255.f, 252 / 255.f, 0.f));` — green
- L39 _private member_ `FSlateColor CellContinuationColor = FSlateColor(FLinearColor(1.0, 1.0, 0.f));` — yellow
- L41 _private prototype_ `void DrawCurrentPage(TSharedPtr<IPropertyHandle> StepTableHandle, IDetailCategoryBuilder& MidiStepSequenceCategory);`
- L46 _private prototype_ `void HandleContinuationChange(bool bEnabling, TSharedPtr<IPropertyHandle> EnabledHandle, TSharedPtr<IPropertyHandle> ContinuationHandle, TSharedPtr<IPropertyHandleArray> CellsHandle, int32 NumCells, int32 CellIndex);` — this handles the change in continuation of each cell upon a click on the cell button
- L48 _private prototype_ `bool IsCellContinuable(TSharedPtr<IPropertyHandle> EnabledHandle, TSharedPtr<IPropertyHandle> ContinuationHandle, TSharedPtr<IPropertyHandleArray> CellsHandle, int32 NumCells, int32 CellIndex);`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundEditor/Private/MidiStepSequenceFactory.h` (Private)


#### class `UMidiStepSequenceFactory`  
`class UMidiStepSequenceFactory : public UFactory`  
_L9-18_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L13 _public prototype_ `UMidiStepSequenceFactory();`
- L15 _public prototype_ `virtual FText GetDisplayName() const override;`
- L16 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundEditor/Private/MidiStutterSequenceFactory.h` (Private)


#### class `UMidiStutterSequenceFactory`  
`class UMidiStutterSequenceFactory : public UFactory`  
_L9-18_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L13 _public prototype_ `UMidiStutterSequenceFactory();`
- L15 _public prototype_ `virtual FText GetDisplayName() const override;`
- L16 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/Harmonix/Source/HarmonixMetasoundEditor/Public/HarmonixMetasoundEditorModule.h` (Public)


#### class `FHarmonixMetasoundEditorModule`  
`class FHarmonixMetasoundEditorModule : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixMetasoundEditor, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixMetasoundEditor, Log, All);`
