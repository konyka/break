# Plugins / HarmonixDspEditor

- module root: `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor`
- headers: 18; symbols: 307
- symbol kinds: class=20, delegate=7, enum=8, enumerator=27, function=32, macro=2, member=66, namespace=3, prototype=136, struct=6
- PrivateDependencyModuleNames: AssetDefinition, AssetRegistry, AssetTools, AudioEditor, ContentBrowser, CurveEditor, DetailCustomizations, EditorScriptingUtilities, EditorWidgets, Engine, Harmonix, HarmonixDsp, HarmonixEditor, HarmonixMidi, InputCore, Json, PropertyEditor, Settings, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/AssetDefinitions/AssetDefinition_FusionPatch.h` (Private)


#### class `UAssetDefinition_FusionPatch`  
`class UAssetDefinition_FusionPatch : public UAssetDefinitionDefault`  
_L13-29_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L19 _public function_ `virtual FText GetAssetDisplayName() const override`
- L20 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L21 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L22 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L27 _public function_ `virtual bool CanImport() const`

#### class `FFusionPatchExtension`  
`class FFusionPatchExtension`  
_L31-36_
- L34 _public prototype_ `static void RegisterMenus();`
- L35 _public prototype_ `static void ExecuteCreateFusionPatch(const FToolMenuContext& MenuContext);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/Customization/AdsrSettingsDetailCustomization.h` (Private)


#### class `FAdsrSettingsDetailsCustomization`  
`class FAdsrSettingsDetailsCustomization : public IPropertyTypeCustomization`  
_L12-39_
- inherits: `IPropertyTypeCustomization`
- L15 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L23 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L27 _private prototype_ `void RefreshCurve();`
- L29 _private prototype_ `FAdsrSettings GetAdsrSettings();`
- L32 _private member_ `TSharedPtr<IPropertyHandle> MyPropertyHandle;` — Handle to the struct being customized
- L34 _private member_ `TSharedPtr<IPropertyUtilities> DetailBuilder;`
- L36 _private member_ `TSharedPtr<FCurveEditor> CurveEditor;`
- L38 _private member_ `FRichCurve RichCurve;`

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/Customization/FusionPatchDetailCustomization.h` (Private)


#### class `FFusionPatchDetailCustomization`  
`class FFusionPatchDetailCustomization : public IDetailCustomization`  
_L15-24_
- inherits: `IDetailCustomization`
- desc: Fusion Patch detail customizatiaon class
- L18 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/Customization/FusionPatchImportOptionsCustomization.h` (Private)


#### class `FFusionPatchCreateOptionsCustomization`  
`class FFusionPatchCreateOptionsCustomization : public IDetailCustomization`  
_L15-28_
- inherits: `IDetailCustomization`
- desc: Fusion Patch detail customizatiaon class
- L18 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L27 _private prototype_ `void RebuildKeyzones();`

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/Customization/FusionPatchSettingsDetailCustomization.h` (Private)


#### class `FFusionPatchSettingsDetailCustomization`  
`class FFusionPatchSettingsDetailCustomization : public IPropertyTypeCustomization`  
_L9-27_
- inherits: `IPropertyTypeCustomization`
- L12 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L24 _private prototype_ `void CustomizeArrayProperty(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& StructBuilder, uint32 MaxPreviewNum);`
- L26 _private prototype_ `TSharedRef<SWidget> CreateStructPropertiesPreviewValueWidget(TSharedRef<IPropertyHandle> PropertyHandle, uint32 MaxPreviewNum);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/Customization/PannerDetailsCustomization.h` (Private)


#### class `FPannerDetailsCustomization`  
`class FPannerDetailsCustomization : public IPropertyTypeCustomization`  
_L17-56_
- inherits: `IPropertyTypeCustomization`
- desc: Owner: Jake Burga FPannerDetails have custom serialization code, so we need to expose the porperties to blueprints this way
- L20 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L28 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L33 _private prototype_ `void OnPannerModeEnumSelectionChanged(int32 TypeIndex, ESelectInfo::Type SelectInfo);` — enum dropdown callbacks
- L34 _private prototype_ `int32 OnGetPannerModeEnumValue() const;`
- L36 _private prototype_ `void OnChannelAssignmentEnumSelectionChanged(int32 TypeIndex, ESelectInfo::Type SelectInfo);`
- L37 _private prototype_ `int32 OnGetChannelAssignmentEnumValue() const;`
- L40 _private prototype_ `TOptional<float> OnGetFloatValue(FName PropertyName) const;` — position (float) numeric entry box callbacks
- L41 _private prototype_ `void OnFloatValueChanged(float NewValue, FName PropertyName);`
- L42 _private prototype_ `void OnFloatValueCommitted(float NewValue, ETextCommit::Type CommitType, FName PropertyName);`
- L45 _private prototype_ `FPannerDetails* GetPannerDetailsPtr();` — get the underlying FPannerDetails as a ptr
- L46 _private prototype_ `const FPannerDetails* GetPannerDetailsPtr() const;`
- L49 _private member_ `TSharedPtr<IPropertyHandle> MyPropertyHandle;` — Handle to the struct being customized
- L50 _private member_ `TSharedPtr<IPropertyUtilities> MyPropertyUtils;`
- L52 _private member_ `const FName PanName = FName("Pan`
- L53 _private member_ `const FName EdgeProximityName = FName("Edg`
- L55 _private member_ `TSharedPtr<IPropertyUtilities> DetailBuilder;`

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/Customization/PitchShifterConfigCustomization.h` (Private)


#### class `FPitchShifterConfigCustomization`  
`class FPitchShifterConfigCustomization : public IDetailCustomization`  
_L17-27_
- inherits: `IDetailCustomization`
- desc: Owner: Jake Burga Exposes a dropdown on FPitchShifterConfigCustomization properties in the detail panel
- L20 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/Customization/PitchShifterNameCustomization.h` (Private)


#### class `FPitchShifterNameCustomization`  
`class FPitchShifterNameCustomization : public IPropertyTypeCustomization`  
_L17-43_
- inherits: `IPropertyTypeCustomization`
- desc: Owner: Jake Burga Exposes a dropdown on FPitchShifterName properties in the detail panel displays a dropdown list of available Pitch Shifter names that are actively registered/loaded
- L20 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L28 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L33 _private prototype_ `void OnGetStrings(TArray< TSharedPtr<FString> >& OutStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems) const;` — Get list of all rows
- L36 _private prototype_ `FString OnGetValueString() const;` — Gets currently selected row display string
- L38 _private prototype_ `void OnValueStringSelected(const FString& SelectedString);`
- L41 _private member_ `TSharedPtr<IPropertyHandle> PitchShifterNameValuePropertyHandle;` — Handle to the struct properties being customized

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/Customization/TypedParameterCustomization.h` (Private)


#### class `FTypedParameterCustomization`  
`class FTypedParameterCustomization : public IPropertyTypeCustomization`  
_L16-105_
- inherits: `IPropertyTypeCustomization`
- L19 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L32 _private prototype_ `void OnPropertyTypeEnumSelectionChanged(int32 TypeIndex, ESelectInfo::Type SelectInfo);` — enum dropdown callbacks
- L33 _private prototype_ `int32 OnGetPropertyTypeEnumValue() const;`
- L36 _private prototype_ `TSharedRef<class SWidget> CreateTypedValueWidget(EParameterType Type);` — creates the actual value widget based on the parameter type
- L39 _private prototype_ `FTypedParameter* GetTypedParameterPtr();` — get the underlying FTypedParemeter as a ptr
- L40 _private prototype_ `const FTypedParameter* GetTypedParameterPtr() const;`
- L44 _private function_ `template<typename T> TOptional<T> OnGetNumericValue() const` — templated methods for numeric value widget callbacks
- L59 _private function_ `template<typename T> void OnNumericValueChanged(T NewValue)`
- L68 _private function_ `template<typename T> void OnNumericValueCommitted(T NewValue, ETextCommit::Type CommitType)`
- L82 _private function_ `template<typename T> TSharedRef<SWidget> CreateNumericValueWidget()` — templated method for creating a numeric value widget using the templated callback methods abov
- L91 _private prototype_ `ECheckBoxState OnGetCheckedState() const;` — check box widget callbacks
- L92 _private prototype_ `void OnCheckedStateChanged(ECheckBoxState State);`
- L95 _private prototype_ `FText OnGetTextValue() const;` — Text Box widget callbacks for FName and FString value types
- L96 _private prototype_ `void OnTextComitted(const FText& InText, ETextCommit::Type TextCommit);`
- L101 _private member_ `TSharedPtr<class SHorizontalBox> ValueContainerWidget;` — Ptr to the value container widget used to swap out the type of value widget used based on the type being editor
- L104 _private member_ `TSharedPtr<IPropertyHandle> TypedParameterHandle;` — Handle to the struct being customized

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/Dta/DtaParser.h` (Private)


#### struct `FDtaParser`  
`struct FDtaParser`  
_L13-49_
- L15 _public prototype_ `static bool DtaStringToJsonString(const FString& InDtaString, FString& OutJsonString, FString& OutErrorMessage);`
- L47 _private prototype_ `static bool Tokenize(const FString& InDtaString, TArray<FString>& OutTokens, FParseContext& OutContext);`
- L48 _private prototype_ `static bool ParseToJson(const TArray<FString>& Tokens, FString& OutString, FString& OutErrorMessage);`

#### struct `FDtaParser::FParseContext`  
`struct FParseContext`  
_L19-45_
- L29 _public member_ `int LineIdx = 0;` — line index in the dta string being read
- L32 _public member_ `int CharIdx = 0;` — character index within the line
- L35 _public member_ `TCHAR CurrentChar = '\0';` — the character being read
- L38 _public member_ `TCHAR PrevChar = '\0';` — the previous "character" read
- L40 _public member_ `EError Error = EError::None;`
- L42 _public prototype_ `void Reset();`
- L44 _public prototype_ `FString GetErrorAsString() const;`

#### enum `FDtaParser::FParseContext::EError`  
`enum EError`  
_L21-26_
- L23 _public enumerator_ `None`
- L24 _public enumerator_ `ParenthesisMismatch`
- L25 _public enumerator_ `UnexpectedEndOfFile`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDtaParser, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDtaParser, Log, All);`
- L11 _macro_ `#define UE_API HARMONIXDSPEDITOR_API`

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/FusionPatchAssetFactory.h` (Private)


#### class `UFusionPatchAssetFactory`  
`class UFusionPatchAssetFactory : public UFactory, public FReimportHandler`  
_L20-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UFactory,FReimportHandler`
- L26 _public prototype_ `UFusionPatchAssetFactory();`
- L28 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L29 _public prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L30 _public prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L31 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L32 _public prototype_ `virtual void CleanUp() override;`
- L34 _public prototype_ `virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;`
- L35 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L37 _public member_ `const UFusionPatchCreateOptions* CreateOptions = nullptr;`
- L40 _private prototype_ `static bool GetReplaceExistingSamplesResponse(const FString& InName);`
- L41 _private prototype_ `static bool GetApplyOptionsToAllImportResponse();`
- L50 _private member_ `int32 ImportCounter = 0;`
- L51 _private member_ `EApplyAllOption ApplyOptionsToAllImport = EApplyAllOption::Unset;`
- L52 _private member_ `bool ReplaceExistingSamples = false;`
- L53 _private member_ `TArray<UObject*> ImportedObjects;`
- L55 _private prototype_ `void UpdateFusionPatchImportNotificationItem(TSharedPtr<SNotificationItem> InItem, bool bImportSuccessful, FName InName);`

#### enum `UFusionPatchAssetFactory::EApplyAllOption`  
`enum class EApplyAllOption : uint8`  
_L43-48_
- L45 _public enumerator_ `Unset`
- L46 _public enumerator_ `No`
- L47 _public enumerator_ `Yes`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HARMONIXDSPEDITOR_API`
- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFusionPatchAssetFactory, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFusionPatchAssetFactory, Log, All);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/FusionPatchImportOptions.h` (Private)


#### class `UFusionPatchImportOptions`  
`class UFusionPatchImportOptions : public UObject`  
_L14-46_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L25 _public prototype_ `static const UFusionPatchImportOptions* GetWithDialog(FArgs&& Args, bool& OutWasOkayPressed);`
- L29 _public member_ `FDirectoryPath SamplesImportDir;` — `UPROPERTY(EditAnywhere, Category = "Import Options", Meta = (DisplayName = "Sound Waves Import Folder", ContentDir))` — The directory to save samples to
- L33 _public member_ `ESoundWaveLoadingBehavior SampleLoadingBehavior = ESoundWaveLoadingBehavior::RetainOnLoad;` — `UPROPERTY(EditAnywhere, Category = "Import Options", Meta = (DisplayName = "Sound Wave Loading Behavior"))` — The loading behavior to apply to the imported samples
- L37 _public member_ `ESoundAssetCompressionType SampleCompressionType = ESoundAssetCompressionType::BinkAudio;` — `UPROPERTY(EditAnywhere, Category = "Import Options", Meta = (DisplayName = "Sound Wave Compression Type"))` — The compression type to apply to the imported samples
- L41 _public function_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override` — UObject interface

#### struct `UFusionPatchImportOptions::FArgs`  
`struct FArgs`  
_L19-23_
- L21 _public member_ `FName PatchName;`
- L22 _public member_ `FString Directory;`

#### enum `ELockedNoteFlag`  
`enum class ELockedNoteFlag : uint8`  
_L49-57_
- reflection: `UENUM()`
- L51 _public enumerator_ `None = 0b000`
- L52 _public enumerator_ `Min = 0b001`
- L53 _public enumerator_ `Root = 0b010`
- L54 _public enumerator_ `Max = 0b100`
- L55 _public enumerator_ `MinMax = Min | Max`
- L56 _public enumerator_ `MinRootMax = Min | Root | Max`

#### enum `EFusionPatchKeyzoneSortOption`  
`enum class EFusionPatchKeyzoneSortOption : uint8`  
_L61-67_
- reflection: `UENUM()`
- L63 _public enumerator_ `Lexical UMETA(DisplayName="Alphabetical", ToolTip="Alphabetical order.")`
- L64 _public enumerator_ `Index UMETA(DisplayName="Index Order", ToolTip="Sample name contains index, ordering the samples alphabetically then from lowest to highest index (snare_0, snare_1, tom_0)")`
- L65 _public enumerator_ `NoteNumber UMETA(DisplayName="Note Number", ToolTip="Sample names contain note numbers with one of the acceptable formats: (name_[Min]_[Root]_[Max], name_[Min]_[Max], name_[Root])")`
- L66 _public enumerator_ `NoteName UMETA(DisplayName="Note Name", ToolTip="Sample names contain note names: (eg. 'Eb1', 'G#3', 'B2')")`

#### enum `EFusionPatchKeyzoneNoteLayoutOption`  
`enum class EFusionPatchKeyzoneNoteLayoutOption : uint8`  
_L70-75_
- reflection: `UENUM()`
- L72 _public enumerator_ `SingleNote UMETA(DisplayName="Single Note", ToolTip="Assign each zone to a single note, 'root' note if parsed by note number or note name, otherwise each note from the selected 'min - max' range")`
- L73 _public enumerator_ `Distribute UMETA(DisplayName="Distribute", ToolTip="Evenly distribute all zones, using the values parsed by the note number or note name, otherwise uses 'min-max' note range")`
- L74 _public enumerator_ `Layer UMETA(DisplayName="Layer", ToolTip="Every zone will span 'min-max' note range.")`

#### enum `EFusionPatchKeyzoneNoteScaleOption`  
`enum class EFusionPatchKeyzoneNoteScaleOption : uint8`  
_L78-82_
- reflection: `UENUM()`
- L80 _public enumerator_ `None UMETA(DisplayName="No Scale (Equal Distance)", ToolTip="Distributes the notes evenly based on the selected layout")`
- L81 _public enumerator_ `MajorScale UMETA(DisplayName="Major Scale", ToolTip="Distributes the notes across a major scale, starting with the Min Note")`

#### enum `EFusionPatchKeyzoneRootNoteOption`  
`enum class EFusionPatchKeyzoneRootNoteOption : uint8`  
_L85-90_
- reflection: `UENUM()`
- L87 _public enumerator_ `Min UMETA(DisplayName="Align Min", ToolTip="Adjusts the range so that the Root note is the same as the Min note of the zone")`
- L88 _public enumerator_ `Max UMETA(DisplayName="Align Max", ToolTip="Adjusts the range so that the Root note is the same as the Max note of the zone")`
- L89 _public enumerator_ `Centered UMETA(DisplayName="Align Center", ToolTip="Adjusts the range so that the Root note of each keyzone is between its min and max note (Root = (Max + Min) / 2)")`

#### class `UFusionPatchCreateOptions`  
`class UFusionPatchCreateOptions : public UObject`  
_L93-177_
- reflection: `UCLASS(config = Editor)`
- inherits: `UObject`
- L105 _public prototype_ `static const UFusionPatchCreateOptions* GetWithDialog(FArgs&& Args, bool& OutWasOkayPressed);`
- L109 _public member_ `FDirectoryPath FusionPatchDir;` — `UPROPERTY(config, EditAnywhere, Category = "Create Patch", Meta=(DisplayName = "Destination", ContentDir))` — Which directory the FusionPatch should be created in
- L113 _public member_ `FString AssetName;` — `UPROPERTY(EditAnywhere, Category = "Create Patch", Meta=(DisplayName = ""))` — The Name of the new fusion patch
- L117 _public member_ `EFusionPatchKeyzoneSortOption SortOption = EFusionPatchKeyzoneSortOption::NoteNumber;` — `UPROPERTY(config, EditAnywhere, Category = "Create Patch", meta=(DisplayName="Assign Notes By"))` — how to parse and sort the names of the samples, extract the note numbers (if applicable) and assigning root, min, max notes
- L121 _public member_ `EFusionPatchKeyzoneNoteLayoutOption LayoutOption = EFusionPatchKeyzoneNoteLayoutOption::Distribute;` — `UPROPERTY(config, EditAnywhere, Category = "Create Patch", meta=(DisplayName="Keyzone Layout", EditConditionHides, EditCondition="LockedNotesMask != ELockedNoteFlag::MinRootMax"))` — how to assign the min and max notes for each keyzone based on ordering and note mapping
- L125 _public member_ `EFusionPatchKeyzoneNoteScaleOption ScaleOption = EFusionPatchKeyzoneNoteScaleOption::None;` — `UPROPERTY(Config, EditAnywhere, Category = "Create Patch", meta=(DisplayName="Scale Mapping", EditConditionHides, EditCondition="SortOption == EFusionPatchKeyzoneSortOption::Lexical || SortOption == EFusionPatchKeyzoneSortOption::Index"))` — whether to assign the notes along a scale, or evenly spaced
- L129 _public member_ `EFusionPatchKeyzoneRootNoteOption RootNoteOption = EFusionPatchKeyzoneRootNoteOption::Min;` — `UPROPERTY(config, EditAnywhere, Category = "Create Patch", meta=(DisplayName="Note Alignment", EditConditionHides, EditCondition="LockedNotesMask != ELockedNoteFlag::MinRootMax"))` — how to assign the root note based on the min and max notes
- L132 _public member_ `int8 MinNote = 0;` — `UPROPERTY(config, EditAnywhere, Category = "Create Patch", meta=(ClampMin = 0, ClampMax = 127, UIMin = 0, UIMax = 127))`
- L135 _public member_ `int8 MaxNote = 127;` — `UPROPERTY(config, EditAnywhere, Category = "Create Patch", meta=(ClampMin = 0, ClampMax = 127, UIMin = 0, UIMax = 127))`
- L141 _public member_ `int32 OctaveAdjust = 0;` — `UPROPERTY(Config, EditAnywhere, Category = "Create Patch")` — Apply an additional octave, positive or negative, to the note values. This can be used to adjust the note values parsed from the sample file names or similarly adjust the octave when setting the notes by scale
- L144 _public member_ `TArray<FKeyzoneSettings> Keyzones;` — `UPROPERTY(EditAnywhere, Category = "Create Patch")`
- L147 _public member_ `FFusionPatchSettings FusionPatchSettings;` — `UPROPERTY()`
- L149 _public member_ `TArray<TWeakObjectPtr<USoundWave>> StagedSoundWaves;`
- L152 _public member_ `ELockedNoteFlag LockedNotesMask = ELockedNoteFlag::None;` — `UPROPERTY()`
- L157 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject interface
- L159 _public prototype_ `void SortLexical();`
- L161 _public prototype_ `void SortNoteNumber();`
- L163 _public prototype_ `void SortNoteName();`
- L165 _public prototype_ `void SortIndex();`
- L167 _public prototype_ `void LayoutSingleNote();`
- L169 _public prototype_ `void LayoutDistribute();`
- L171 _public prototype_ `void LayoutLayer();`
- L173 _public prototype_ `void UpdateKeyzonesWithSettings();`

#### struct `UFusionPatchCreateOptions::FArgs`  
`struct FArgs`  
_L98-103_
- L100 _public member_ `FString Directory;`
- L101 _public member_ `FString AssetName;`
- L102 _public member_ `TArray<TWeakObjectPtr<USoundWave>> StagedSoundWaves;`

#### class `FKeyzoneNoteParser`  
`class FKeyzoneNoteParser`  
_L179-206_
- L197 _public prototype_ `static bool ParseMinRootMax(const FString& Input, FParseResult& Output);`
- L199 _public prototype_ `static bool ParseMinMax(const FString& Input, FParseResult& Output);`
- L201 _public prototype_ `static bool ParseRoot(const FString& Input, FParseResult& Output);`
- L203 _public prototype_ `static bool ParseNoteName(const FString& Input, FParseResult& Output);`
- L205 _public prototype_ `static bool ParseIndex(const FString& Input, FParseResult& Output);`

#### struct `FKeyzoneNoteParser::FParseResult`  
`struct FParseResult`  
_L183-195_
- L185 _public member_ `int32 MinNote = -1;`
- L186 _public member_ `int32 RootNote = -1;`
- L187 _public member_ `int32 MaxNote = -1;`
- L189 _public function_ `void Reset()`

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/FusionPatchJsonImporter.h` (Private)


#### class `FFusionPatchJsonImporter`  
`class FFusionPatchJsonImporter : public FJsonImporter`  
_L20-58_
- inherits: `FJsonImporter`
- L55 _public prototype_ `static TArray<UObject*> ImportAudioSamples(const TArray<FString>& Files, const FString& DestinationPath, bool ReplaceExisting);`
- L57 _public prototype_ `static bool TryParseJson(TSharedPtr<FJsonObject> JsonObj, UFusionPatch* FusionPatch, TArray<UObject*>& OutAdditionalImportedObjects, const FImportArgs& ImportArgs, TArray<FString>& OutErrors);`

#### struct `FFusionPatchJsonImporter::FImportArgs`  
`struct FImportArgs`  
_L24-53_
- L26 _public function_ `FImportArgs()`
- L29 _public function_ `FImportArgs(FName InName, const FString& InSourcePath, const FString& InDestPath, const FString& InSamplesDestPath, bool InReplaceExistingSamples = false, ESoundWaveLoadingBehavior SampleLoadingBehavior = ESoundWaveLoadingBehavior::Inherited, ESoundAssetCompressionType SampleCompressionType = ESoundAssetCompressionType::BinkAudio) : Name(InName) , SourcePath(InSourcePath) , DestPath(InDestPath) , SamplesDestPath(InSamplesDestPath) , ReplaceExistingSamples(InReplaceExistingSamples) , SampleLoadingBehavior(SampleLoadingBehavior) , SampleCompressionType(SampleCompressionType)`
- L45 _public member_ `FName Name;`
- L46 _public member_ `FString SourcePath;`
- L47 _public member_ `FString DestPath;`
- L48 _public member_ `FString SamplesDestPath;`
- L49 _public member_ `bool ReplaceExistingSamples;`
- L50 _public member_ `ESoundWaveLoadingBehavior SampleLoadingBehavior;`
- L51 _public member_ `ESoundAssetCompressionType SampleCompressionType;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFusionPatchJsonImporter, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFusionPatchJsonImporter, Log, All);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/JsonImporterHelper.h` (Private)


#### class `FJsonImporter`  
`class FJsonImporter`  
_L18-92_
- L43 _public member_ `static const FString kEmptyString;`
- L45 _public prototype_ `static bool CanImportJson(const FString& JsonString);`
- L47 _public prototype_ `static TSharedPtr<FJsonObject> ParseJsonString(const FString& JsonString, FString& ErrorMessage);`
- L50 _public prototype_ `static TValueIterator IterValue(TSharedPtr<FJsonValue> Field);` — helpful way to iterate a vaule or field if you're not sure if it's an array or a single value
- L51 _public prototype_ `static TValueIterator IterField(TSharedPtr<FJsonObject> Object, const FString& FieldName);`
- L53 _public prototype_ `static bool TryGetObjectField(TSharedPtr<FJsonObject> Object, const FString& FieldName, TSharedPtr<FJsonObject>& OutObject);`
- L56 _public prototype_ `static bool TryGetBoolField(TSharedPtr<FJsonObject> Object, const FString& FieldName, bool& OutBool, bool Default = false);` — shortcut to reading a number as a bool
- L58 _public prototype_ `static bool TryGetStringField(TSharedPtr<FJsonObject> Object, const FString& FieldName, FString& OutString, const FString& Default = kEmptyString);`
- L60 _public prototype_ `static bool TryGetNameField(TSharedPtr<FJsonObject> Object, const FString& FildName, FName& OutName, const FName& Default = NAME_None);`
- L63 _public prototype_ `template<typename T> static bool TryGetNumberField(TSharedPtr<FJsonObject> Object, const FString& FieldName, T& OutNumber, T Default = static_cast<T>(0));`
- L66 _public prototype_ `template<typename T> static bool TryGetNumberField(TSharedPtr<FJsonObject> Object, const FString& FieldName, T& OutNumber, TFunction<T(T)> Conversion, T Default = static_cast<T>(0));`
- L69 _public prototype_ `template<typename T> static bool TryGetEnumField(TSharedPtr<FJsonObject> Object, const FString& FieldName, T& OutEnum, T Default);`
- L71 _public prototype_ `static bool TryGetObject(TSharedPtr<FJsonValue> Field, TSharedPtr<FJsonObject>& OutObject);`
- L74 _public prototype_ `static bool TryGetBool(TSharedPtr<FJsonValue> Field, bool& OutBool, bool Default = false);` — shortcut to reading a number as a bool
- L76 _public prototype_ `static bool TryGetString(TSharedPtr<FJsonValue> Field, FString& OutString, const FString& Default = kEmptyString);`
- L79 _public prototype_ `template<typename T> static bool TryGetNumber(TSharedPtr<FJsonValue> Field, T& OutNumber, T Default = static_cast<T>(0));`
- L82 _public prototype_ `template<typename T> static bool TryGetNumber(TSharedPtr<FJsonValue> Field, T& OutNumber, TFunction<T(T)> Conversion, T Default = static_cast<T>(0));`
- L85 _public prototype_ `template<typename T> static bool TryGetEnum(TSharedPtr<FJsonValue> Field, T& OutEnum, T Default);`
- L88 _public prototype_ `template<typename T> static bool ParseEnum(const FString& JsonString, T& OutEnum);`
- L91 _public prototype_ `template<typename T> static bool EnumToJsonString(const T InEnum, FString& OutJsonString);`
- L95 _function_ `template<typename T> bool FJsonImporter::TryGetNumberField(TSharedPtr<FJsonObject> Object, const FString& FieldName, T& OutNumber, T Default )`
- L111 _function_ `template<typename T> bool FJsonImporter::TryGetNumberField(TSharedPtr<FJsonObject> Object, const FString& FieldName, T& OutNumber, TFunction<T(T)> Conversion, T Default)`
- L124 _function_ `template<typename T> bool FJsonImporter::TryGetEnumField(TSharedPtr<FJsonObject> Object, const FString& FieldName, T& OutEnum, T Default)`
- L146 _function_ `template<typename T> bool FJsonImporter::TryGetNumber(TSharedPtr<FJsonValue> Field, T& OutNumber, T Default )`
- L162 _function_ `template<typename T> bool FJsonImporter::TryGetNumber(TSharedPtr<FJsonValue> Field, T& OutNumber, TFunction<T(T)> Conversion, T Default)`
- L175 _function_ `template<typename T> bool FJsonImporter::TryGetEnum(TSharedPtr<FJsonValue> Field, T& OutEnum, T Default)`
- L194 _function_ `template<typename T> bool FJsonImporter::ParseEnum(const FString& JsonString, T& OutEnum)`
- L226 _function_ `template<typename T> bool FJsonImporter::EnumToJsonString(const T InEnum, FString& OutJsonString)`

#### class `FJsonImporter::TValueIterator`  
`class TValueIterator`  
_L22-41_
- L25 _public prototype_ `TValueIterator(TSharedPtr<FJsonValue> Field);`
- L26 _public prototype_ `TValueIterator(TSharedPtr<FJsonObject> Object, const FString& FieldName);`
- L27 _public prototype_ `const TSharedPtr<FJsonValue>& operator*() const;`
- L28 _public prototype_ `const TSharedPtr<FJsonValue>* operator->() ;`
- L29 _public prototype_ `bool operator==(const TValueIterator& Other) const;`
- L30 _public prototype_ `bool operator!=(const TValueIterator& Other) const;`
- L31 _public function_ `bool operator==(int Index) const`
- L32 _public function_ `bool operator!=(int Index) const`
- L33 _public prototype_ `TValueIterator& operator++();`
- L34 _public prototype_ `TValueIterator operator++(int);`
- L35 _public prototype_ `TValueIterator begin();`
- L36 _public prototype_ `int end();`
- L38 _private member_ `int IterIndex = -1;`
- L39 _private member_ `TSharedPtr<FJsonValue> SingleValue;`
- L40 _private member_ `const TArray<TSharedPtr<FJsonValue>>* ArrayPtr = nullptr;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixJsonImporter, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixJsonImporter, Log, All);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/SettingsJsonImporter.h` (Private)


#### class `FSettingsJsonImporter`  
`class FSettingsJsonImporter : public FJsonImporter`  
_L9-30_
- inherits: `FJsonImporter`
- L13 _public prototype_ `static bool TryParseJson(TSharedPtr<FJsonObject> JsonObj, struct FKeyzoneSettings& OutSettings);`
- L15 _public prototype_ `static bool TryParseJson(TSharedPtr<FJsonObject> JsonObj, struct FPannerDetails& OutPanDetails);`
- L17 _public prototype_ `static bool TryParseJson(TSharedPtr<FJsonObject> JsonObj, struct FTimeStretchConfig& TimeStretchConfig);`
- L19 _public prototype_ `static bool TryParseJson(TSharedPtr<FJsonObject> JsonObj, struct FFusionPatchSettings& PatchSettings);`
- L21 _public prototype_ `static bool TryParseJson(TSharedPtr<FJsonObject> JsonObj, struct FAdsrSettings& AdsrSettings);`
- L23 _public prototype_ `static bool TryParseJson(TSharedPtr<FJsonObject> JsonObj, struct FLfoSettings& LfoSettings);`
- L25 _public prototype_ `static bool TryParseJson(TSharedPtr<FJsonObject> JsonObj, struct FBiquadFilterSettings& FilterSettings);`
- L27 _public prototype_ `static bool TryParseJson(TSharedPtr<FJsonObject> JsonObj, struct FModulatorSettings& ModulatorSettings);`
- L29 _public prototype_ `static bool TryParseJson(TSharedPtr<FJsonObject> JsonObj, struct FPortamentoSettings& PortamentoSettings);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Private/Widgets/SMinMaxSlider.h` (Private)


#### class `SMinMaxSlider`  
`class SMinMaxSlider : public SSlider`  
_L13-76_
- inherits: `SSlider`
- desc: A custom range slider class inherited from SSlider for customizing FusionPatch's min and max note/velocity properties 2 non-overlapped thumb handles controlling a lower value and a higher value
- L16 _public function_ `SLATE_BEGIN_ARGS(SMinMaxSlider) :_LowerHandleValue(0.0f) , _UpperHandleValue(1.0f) , _IndentHandle(true) , _SliderBarColor(FLinearColor::White) , _SliderLowerHandleColor(FLinearColor::White) , _SliderUpperHandleColor(FLinearColor::White) , _MinValue(0.0f) , _MaxValue(1.0f)`
- L26 _public prototype_ `SLATE_ATTRIBUTE(float, LowerHandleValue) SLATE_ATTRIBUTE(float, UpperHandleValue) SLATE_ATTRIBUTE(bool, IndentHandle) SLATE_ATTRIBUTE(FSlateColor, SliderBarColor) SLATE_ATTRIBUTE(FSlateColor, SliderLowerHandleColor) SLATE_ATTRIBUTE(FSlateColor, SliderUpperHandleColor) SLATE_EVENT(FOnLowerValueChanged, OnLowerHandleValueChanged) SLATE_EVENT(FOnUpperValueChanged, OnUpperHandleValueChanged) SLATE_ARGUMENT(float, MinValue) SLATE_ARGUMENT(float, MaxValue) SLATE_END_ARGS() void Construct(const FArguments& InDeclaration);`
- L41 _public prototype_ `float GetLowerNormalizedValue() const;`
- L42 _public prototype_ `float GetUpperNormalizedValue() const;`
- L43 _public prototype_ `void SetLowerValue(TAttribute<float> InValueAttribute);`
- L44 _public prototype_ `void SetUpperValue(TAttribute<float> InValueAttribute);`
- L45 _public prototype_ `void OnSliderValueChanged(float NewValue);`
- L55 _protected prototype_ `FVector2D CalculateLowerHandlePosition(const FGeometry& HandleGeometry, float Value) const;`
- L56 _protected prototype_ `FVector2D CalculateUpperHandlePosition(const FGeometry& HandleGeometry, float Value) const;`
- L57 _protected prototype_ `ESliderHandle DetermineClickedHandle(const FGeometry& HandleGeometry, const FVector2D& LocalMousePosition) const;`
- L58 _protected prototype_ `float PositionToValue(const FGeometry& MyGeometry, const UE::Slate::FDeprecateVector2DParameter& AbsolutePosition);`
- L60 _protected prototype_ `virtual void CommitValue(float NewValue) override;`
- L61 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L62 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L63 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L66 _private member_ `TAttribute<float> LowerHandleValue;`
- L67 _private member_ `TAttribute<float> UpperHandleValue;`
- L68 _private member_ `FOnLowerValueChanged OnLowerHandleValueChanged;`
- L69 _private member_ `FOnUpperValueChanged OnUpperHandleValueChanged;`
- L70 _private member_ `TAttribute<bool> IndentHandleAttribute;`
- L71 _private member_ `TAttribute<FSlateColor> SliderBarColorAttribute;`
- L72 _private member_ `TAttribute<FSlateColor> SliderLowerHandleColorAttribute;`
- L73 _private member_ `TAttribute<FSlateColor> SliderUpperHandleColorAttribute;`
- L74 _private member_ `ESliderHandle CurrentHandle = ESliderHandle::None;`

#### enum `SMinMaxSlider::ESliderHandle`  
`enum class ESliderHandle`  
_L48-53_
- L50 _public enumerator_ `None`
- L51 _public enumerator_ `LowerHandle`
- L52 _public enumerator_ `UpperHandle`

#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLowerValueChanged, float) DECLARE_DELEGATE_OneParam(FOnUpperValueChanged, float) class SMinMaxSlider : public SSlider { public: SLATE_BEGIN_ARGS(SMinMaxSlider) :_LowerHandleValue(0.0f) , _UpperHandleValue(1.0f) , _IndentHandle(true) , _SliderBarColor(FLinearColor::White) , _SliderLowerHandleColor(FLinearColor::White) , _SliderUpperHandleColor(FLinearColor::White) , _MinValue(0.0f) , _MaxValue(1.0f) {} SLATE_ATTRIBUTE(float, LowerHandleValue) SLATE_ATTRIBUTE(float, UpperHandleValue) SLATE_ATTRIBUTE(bool, IndentHandle) SLATE_ATTRIBUTE(FSlateColor, SliderBarColor) SLATE_ATTRIBUTE(FSlateColor, SliderLowerHandleColor) SLATE_ATTRIBUTE(FSlateColor, SliderUpperHandleColor) SLATE_EVENT(FOnLowerValueChanged, OnLowerHandleValueChanged) SLATE_EVENT(FOnUpperValueChanged, OnUpperHandleValueChanged) SLATE_ARGUMENT(float, MinValue) SLATE_ARGUMENT(float, MaxValue) SLATE_END_ARGS() void Construct(const FArguments& InDeclaration); float GetLowerNormalizedValue() const; float GetUpperNormalizedValue() const; void SetLowerValue(TAttribute<float> InValueAttribute); void SetUpperValue(TAttribute<float> InValueAttribute); void OnSliderValueChanged(float NewValue);`
- L7 _delegate_ `DECLARE_DELEGATE_OneParam(FOnUpperValueChanged, float) class SMinMaxSlider : public SSlider { public: SLATE_BEGIN_ARGS(SMinMaxSlider) :_LowerHandleValue(0.0f) , _UpperHandleValue(1.0f) , _IndentHandle(true) , _SliderBarColor(FLinearColor::White) , _SliderLowerHandleColor(FLinearColor::White) , _SliderUpperHandleColor(FLinearColor::White) , _MinValue(0.0f) , _MaxValue(1.0f) {} SLATE_ATTRIBUTE(float, LowerHandleValue) SLATE_ATTRIBUTE(float, UpperHandleValue) SLATE_ATTRIBUTE(bool, IndentHandle) SLATE_ATTRIBUTE(FSlateColor, SliderBarColor) SLATE_ATTRIBUTE(FSlateColor, SliderLowerHandleColor) SLATE_ATTRIBUTE(FSlateColor, SliderUpperHandleColor) SLATE_EVENT(FOnLowerValueChanged, OnLowerHandleValueChanged) SLATE_EVENT(FOnUpperValueChanged, OnUpperHandleValueChanged) SLATE_ARGUMENT(float, MinValue) SLATE_ARGUMENT(float, MaxValue) SLATE_END_ARGS() void Construct(const FArguments& InDeclaration); float GetLowerNormalizedValue() const; float GetUpperNormalizedValue() const; void SetLowerValue(TAttribute<float> InValueAttribute); void SetUpperValue(TAttribute<float> InValueAttribute); void OnSliderValueChanged(float NewValue);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Public/HarmonixDspEditorModule.h` (Public)


#### class `FHarmonixDspEditorModule`  
`class FHarmonixDspEditorModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule();`
- L14 _public prototype_ `virtual void ShutdownModule();`
- L17 _private prototype_ `void RegisterMenus();`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixDspEditor, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHarmonixDspEditor, Log, All);`

### `Plugins/Runtime/Harmonix/Source/HarmonixDspEditor/Public/HarmonixDspEditorUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Harmonix`
- L8 _namespace_ `namespace Dsp` (scope `Harmonix`)
- L8 _namespace_ `namespace Editor` (scope `Harmonix::Dsp`)
- L10 _prototype_ `void GenerateAdsrEnvelope(const FAdsrSettings& InAdsrSettings, float SustainTime, float SampleRate, Audio::FAlignedFloatBuffer& OutBuffer);` (scope `Harmonix::Dsp::Editor`)
