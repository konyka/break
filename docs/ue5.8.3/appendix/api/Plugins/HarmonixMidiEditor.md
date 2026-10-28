# Plugins / HarmonixMidiEditor

- module root: `Plugins/Runtime/Harmonix/Source/HarmonixMidiEditor`
- headers: 7; symbols: 89
- symbol kinds: class=8, delegate=1, function=5, member=27, namespace=1, prototype=46, struct=1
- PrivateDependencyModuleNames: AssetDefinition, AssetTools, ContentBrowser, DetailCustomizations, Engine, HarmonixMidi, InputCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: BlueprintGraph, Core, CoreUObject, EditorFramework, EditorStyle, GraphEditor, PropertyEditor, Settings, Slate, SlateCore

### `Plugins/Runtime/Harmonix/Source/HarmonixMidiEditor/Private/AssetDefinition_MidiFile.h` (Private)


#### class `UAssetDefinition_MidiFile`  
`class UAssetDefinition_MidiFile : public UAssetDefinitionDefault`  
_L14-37_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L20 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L21 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L22 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L23 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L24 _public prototype_ `virtual bool CanImport() const override;`
- L26 _public prototype_ `static void RegisterContextMenu();`
- L28 _private prototype_ `static void ExecuteExportMidiFile(const FToolMenuContext& MenuContext);`
- L29 _private prototype_ `static void ExportAllMidiToFolder(const UContentBrowserAssetContextMenuContext* Context);`
- L30 _private prototype_ `static void ExecuteCompareMidiFiles(const FToolMenuContext& MenuContext);`
- L31 _private prototype_ `static bool CanExecuteCompareMidiFiles(const FToolMenuContext& MenuContext);`
- L32 _private prototype_ `static void ExecuteOpenMidiFileInExternalEditor(const FToolMenuContext& MenuContext);`
- L33 _private prototype_ `static bool CanExecuteOpenMidiFileInExternalEditor(const FToolMenuContext& MenuContext);`
- L35 _private prototype_ `static EAppReturnType::Type AskOverwrite(FString& OutPath);`
- L36 _private member_ `static FString LastMidiExportFolder;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace EAppReturnType`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidiEditor/Private/MidiFileDetailCustomization.h` (Private)


#### class `FMidiFileDetailCustomization`  
`class FMidiFileDetailCustomization : public IDetailCustomization`  
_L23-45_
- inherits: `IDetailCustomization`
- L26 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L32 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& InDetailBuilder) override;` — Text Display for midi file length
- L33 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L36 _private member_ `TSharedPtr<IDetailLayoutBuilder> DetailBuilder;`
- L37 _private member_ `FText FileLengthText;`
- L38 _private member_ `TSharedPtr<STextBlock> FileLengthTextBlock;`
- L39 _private member_ `TSharedPtr<SHorizontalBox> LengthBox;`
- L40 _private member_ `FDetailWidgetRow* LengthRow = nullptr;`
- L42 _private member_ `TWeakObjectPtr<UObject> MidiFile;`
- L44 _private prototype_ `void BuildLengthRow(UMidiFile* TheMidiFile);`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidiEditor/Private/MidiFileFactory.h` (Private)


#### class `UMidiFileFactory`  
`class UMidiFileFactory : public UFactory, public FReimportHandler`  
_L26-63_
- reflection: `UCLASS()`
- inherits: `UFactory,FReimportHandler`
- desc: Imports a standard midi file
- L31 _private prototype_ `virtual FText GetDisplayName() const override;`
- L32 _private prototype_ `virtual FText GetToolTip() const override;`
- L33 _private prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L34 _private prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L35 _private prototype_ `virtual void CleanUp() override;`
- L39 _private prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L40 _private prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L41 _private prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L42 _private prototype_ `virtual void PostImportCleanUp() override;`
- L45 _private member_ `static constexpr int32 kMaxTickErrorForTrivialConform = 2;`
- L46 _private prototype_ `static bool LengthCanBeTriviallyConformed(UMidiFile* MidiFile);`
- L49 _private member_ `TArray<UMidiFile*> ImportedFiles;` — keep track of files that are imported for the pop-up dialog (multi batch)
- L50 _private member_ `bool bApplyGrossConformToAll = false;`
- L51 _private member_ `bool bDontApplyGrossConformToAll = false;`
- L52 _private member_ `bool bApplyOffByOneConformToAll = false;`
- L53 _private member_ `bool bDontApplyOffByOneConformToAll = false;`
- L54 _private member_ `EMidiFileQuantizeDirection ApplyGrossConformDirection = EMidiFileQuantizeDirection::Up;`
- L55 _private member_ `EMidiClockSubdivisionQuantization GrossConformSubdivision = EMidiClockSubdivisionQuantization::None;`
- L58 _private prototype_ `static void AskOrDoTrivialConform(UMidiFile* MidiFileAsset, bool bIsOneOfMany, UMidiFileFactory* CallingFactory, int32 CurrentLengthTicks, int32 QuantizedLengthTick);` — making these static means we can call them from other places in the editor UI...
- L59 _private prototype_ `static void AskOrDoGrossConform(UMidiFile* MidiFileAsset, bool bIsOneOfMany, UMidiFileFactory* CallingFactory, int32 CurrentLengthTicks, int32 QuantizedLengthTick, EMidiClockSubdivisionQuantization BestSubdivision);`
- L62 _private prototype_ `void CheckImportedFilesForValidLengths();`

#### class `SConformMidiFileLengthDialog`  
`class SConformMidiFileLengthDialog : public SCompoundWidget`  
_L71-113_
- inherits: `SCompoundWidget`
- L74 _public function_ `SLATE_BEGIN_ARGS(SConformMidiFileLengthDialog) : _ParentWindow() , _bMultipleFiles(false) , _FileDescription() , _RecommendedDirection(EMidiFileQuantizeDirection::Nearest) , _RecommendedSubdivision(EMidiClockSubdivisionQuantization::Bar)`
- L82 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(bool, bMultipleFiles) SLATE_ARGUMENT(FText, FileDescription) SLATE_ARGUMENT(EMidiFileQuantizeDirection, RecommendedDirection) SLATE_ARGUMENT(EMidiClockSubdivisionQuantization, RecommendedSubdivision) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L92 _public member_ `const FTextBlockStyle MidiFileInformationStyle = FTextBlockStyle().SetFont(FCoreStyle::GetDefaultFontStyle("Bold", 10)).SetColorAndOpacity(FLinearColor::Whi` — custom widgets
- L93 _public member_ `EMidiFileQuantizeDirection ConformDirection = EMidiFileQuantizeDirection::Up;`
- L94 _public member_ `EMidiClockSubdivisionQuantization ConformSubdivision = EMidiClockSubdivisionQuantization::Bar;`
- L95 _public member_ `bool bDoForAll = false;`
- L96 _public member_ `bool bUserTookAction = false;`
- L99 _private member_ `TArray<TSharedPtr<FString>> DirectionNames;`
- L100 _private member_ `TSharedPtr<FString> SelectedDirection;`
- L111 _private member_ `TArray<TSharedPtr<FSubdivisionEntry>> QuantizationSubdivisions;`
- L112 _private member_ `TSharedPtr<FSubdivisionEntry> SelectedQuantizationSubdivision;`

#### struct `SConformMidiFileLengthDialog::FSubdivisionEntry`  
`struct FSubdivisionEntry`  
_L102-110_
- L104 _public member_ `EMidiClockSubdivisionQuantization Value;`
- L105 _public member_ `FString DisplayString;`
- L106 _public function_ `FSubdivisionEntry(EMidiClockSubdivisionQuantization InValue, const FString& InString) : Value(InValue) , DisplayString(InString)`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidiEditor/Private/MidiNoteCustomization.h` (Private)


#### class `FMidiNoteCustomization`  
`class FMidiNoteCustomization : public IPropertyTypeCustomization`  
_L13-39_
- inherits: `IPropertyTypeCustomization`
- desc: Exposes a dropdown on FMidiNote properties in the detail panel.
- L16 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L22 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L24 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L29 _private prototype_ `void OnGetStrings(TArray< TSharedPtr<FString> >& OutStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems) const;` — Get list of all rows
- L32 _private prototype_ `FString OnGetValueString() const;` — Gets currently selected row display string
- L34 _private prototype_ `void OnValueStringSelected(const FString& SelectedString);`
- L37 _private member_ `TSharedPtr<IPropertyHandle> MidiNoteValuePropertyHandle;` — Handle to the struct properties being customized

### `Plugins/Runtime/Harmonix/Source/HarmonixMidiEditor/Private/Pins/MidiNotePin.h` (Private)


#### class `SMidiNotePin`  
`class SMidiNotePin : public SGraphPin`  
_L19-40_
- inherits: `SGraphPin`
- desc: Owner: Jake Burga Exposes a dropdown on FMidiNote pins dropdown shows midi notes from 0-127 with friendly names
- L22 _public function_ `SLATE_BEGIN_ARGS(SMidiNotePin)`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L26 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L30 _protected prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;` — this override is used to display slate widget used for customization.
- L33 _protected prototype_ `void OnGetStrings(TArray< TSharedPtr<FString> >& OutStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems) const;` — Get list of all rows
- L36 _protected prototype_ `FString OnGetValueString() const;` — Gets currently selected row display string
- L39 _protected prototype_ `void OnValueSelected(const FString& value);` — Triggers when drop down item is selected

### `Plugins/Runtime/Harmonix/Source/HarmonixMidiEditor/Private/Pins/MidiNotePinFactory.h` (Private)


#### class `FMidiNotePinFactory`  
`class FMidiNotePinFactory : public FGraphPanelPinFactory`  
_L14-17_
- inherits: `FGraphPanelPinFactory`
- desc: Factory class that creates a custom Graph Pin for FMidiNote struct pins.
- L16 _private prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;`

### `Plugins/Runtime/Harmonix/Source/HarmonixMidiEditor/Public/HarmonixMidiEditorModule.h` (Public)


#### class `FHarmonixMidiEditorModule`  
`class FHarmonixMidiEditorModule : public IModuleInterface`  
_L13-20_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual void StartupModule();`
- L17 _public prototype_ `virtual void ShutdownModule();`
- L19 _private prototype_ `void RegisterAssetContextMenus();`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixMidiEditor, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixMidiEditor, Log, All);`
