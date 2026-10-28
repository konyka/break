# Plugins / AudioModulationEditor

- module root: `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor`
- headers: 21; symbols: 139
- symbol kinds: class=23, delegate=1, function=30, macro=4, member=11, prototype=70
- PrivateDependencyModuleNames: AssetDefinition, AudioEditor, AudioExtensions, AudioModulation, Core, CoreUObject, CurveEditor, EditorFramework, EditorWidgets, Engine, GameProjectGeneration, InputCore, LevelSequence, MetasoundEditor, MetasoundFrontend, MetasoundGraphCore, MovieScene, MovieSceneTools, PropertyEditor, SequenceRecorder, Sequencer, SequencerCore, Slate, SlateCore, ToolWidgets, UnrealEd, WaveTable, WaveTableEditor
- PublicDependencyModuleNames: MovieSceneTools, Sequencer

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/AssetDefinition/AssetDefinition_SoundControlBus.h` (Private)


#### class `UAssetDefinition_SoundControlBus`  
`class UAssetDefinition_SoundControlBus : public UAssetDefinitionDefault_AudioDiffable`  
_L10-40_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L16 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L17 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override`
- L28 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/AssetDefinition/AssetDefinition_SoundControlBusMix.h` (Private)


#### class `UAssetDefinition_SoundControlBusMix`  
`class UAssetDefinition_SoundControlBusMix : public UAssetDefinitionDefault_AudioDiffable`  
_L10-31_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L16 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L17 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/AssetDefinition/AssetDefinition_SoundModulationGenerator.h` (Private)


#### class `UAssetDefinition_SoundModulationGenerator`  
`class UAssetDefinition_SoundModulationGenerator : public UAssetDefinitionDefault_AudioDiffable`  
_L10-31_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L16 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L17 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/AssetDefinition/AssetDefinition_SoundModulationParameter.h` (Private)


#### class `UAssetDefinition_SoundModulationParameter`  
`class UAssetDefinition_SoundModulationParameter : public UAssetDefinitionDefault_AudioDiffable`  
_L10-31_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L16 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L17 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/AssetDefinition/AssetDefinition_SoundModulationPatch.h` (Private)


#### class `UAssetDefinition_SoundModulationPatch`  
`class UAssetDefinition_SoundModulationPatch : public UAssetDefinitionDefault_AudioDiffable`  
_L10-32_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault_AudioDiffable`
- L16 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L17 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L18 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L19 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L30 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/AudioControlBusBaseTrackEditor.h` (Private)


#### class `FAudioControlBusBaseTrackEditor`  
`class FAudioControlBusBaseTrackEditor : public FMovieSceneTrackEditor`  
_L11-35_
- inherits: `FMovieSceneTrackEditor`
- L20 _public prototype_ `FAudioControlBusBaseTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L23 _public prototype_ `virtual ~FAudioControlBusBaseTrackEditor();` — Virtual destructor.
- L25 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L26 _public prototype_ `virtual bool IsResizable(UMovieSceneTrack* InTrack) const override;`
- L28 _public prototype_ `void OnAudioControlBusAssetEnterPressed(const TArray<FAssetData>& AssetData);` — Audio control bus asset enter pressed
- L32 _protected prototype_ `virtual void AddControlBusAssetTrackToSequence(const FAssetData& InAssetData);` — Add new control bus Asset track to sequence
- L34 _protected member_ `IConsoleVariable* CVarUseControlBusTracks;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOMODULATIONEDITOR_API`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/AudioControlBusMixTrackEditor.h` (Private)


#### class `FAudioControlBusMixTrackEditor`  
`class FAudioControlBusMixTrackEditor : public FAudioControlBusBaseTrackEditor`  
_L11-46_
- inherits: `FAudioControlBusBaseTrackEditor`
- L20 _public prototype_ `FAudioControlBusMixTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L23 _public prototype_ `virtual ~FAudioControlBusMixTrackEditor();` — Virtual destructor.
- L31 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L35 _public prototype_ `virtual FText GetDisplayName() const override;`
- L36 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L37 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L38 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L39 _public prototype_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override;`
- L40 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L44 _private prototype_ `void AddControlBusAssetTrackToSequence(const FAssetData& InAssetData) override;` — Add new control bus mix track to sequence

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOMODULATIONEDITOR_API`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/AudioControlBusTrackEditor.h` (Private)


#### class `FAudioControlBusTrackEditor`  
`class FAudioControlBusTrackEditor : public FAudioControlBusBaseTrackEditor`  
_L11-45_
- inherits: `FAudioControlBusBaseTrackEditor`
- L20 _public prototype_ `FAudioControlBusTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L23 _public prototype_ `virtual ~FAudioControlBusTrackEditor();` — Virtual destructor.
- L31 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L35 _public prototype_ `virtual FText GetDisplayName() const override;`
- L36 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L37 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L38 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L39 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L40 _public prototype_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override;`
- L44 _private prototype_ `void AddControlBusAssetTrackToSequence(const FAssetData& InAssetData) override;` — Add new control bus track to sequence

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AUDIOMODULATIONEDITOR_API`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/AudioModulationEditor.h` (Private)


#### class `FAudioModulationEditorModule`  
`class FAudioModulationEditorModule : public IModuleInterface`  
_L15-41_
- inherits: `IModuleInterface`
- L18 _public prototype_ `FAudioModulationEditorModule();`
- L20 _public prototype_ `TSharedPtr<FExtensibilityManager> GetModulationPatchMenuExtensibilityManager();`
- L21 _public prototype_ `TSharedPtr<FExtensibilityManager> GetModulationPatchToolbarExtensibilityManager();`
- L23 _public prototype_ `virtual void StartupModule() override;`
- L25 _public prototype_ `void RegisterCustomPropertyLayouts();`
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _private prototype_ `void SetIcon(const FString& ClassName);`
- L32 _private member_ `TArray<TSharedPtr<FAssetTypeActions_Base>> AssetActions;`
- L34 _private member_ `TSharedPtr<FExtensibilityManager> ModulationPatchMenuExtensibilityManager;`
- L35 _private member_ `TSharedPtr<FExtensibilityManager> ModulationPatchToolBarExtensibilityManager;`
- L37 _private member_ `TSharedPtr<FSlateStyleSet> StyleSet;`
- L39 _private member_ `FDelegateHandle AudioControlBusTrackCreateEditorHandle;`
- L40 _private member_ `FDelegateHandle AudioControlBusMixTrackCreateEditorHandle;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioModulationEditor, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioModulationEditor, Log, All);`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/Editors/ModulationPatchCurveEditorViewStacked.h` (Private)


#### class `SModulationPatchEditorViewStacked`  
`class SModulationPatchEditorViewStacked : public WaveTable::Editor::SViewStacked`  
_L21-30_
- inherits: `WaveTable::Editor::SViewStacked`
- L23 _private prototype_ `virtual void FormatInputLabel(const WaveTable::Editor::FWaveTableCurveModel& EditorModel, const FNumberFormattingOptions& InLabelFormat, FText& InOutLabel) const override;`
- L24 _private prototype_ `virtual void FormatOutputLabel(const WaveTable::Editor::FWaveTableCurveModel& EditorModel, const FNumberFormattingOptions& InLabelFormat, FText& InOutLabel) const override;`
- L27 _protected prototype_ `virtual FText FormatToolTipValue(const FCurveModel& CurveModel, double EvaluatedValue) const override;`
- L29 _protected member_ `static constexpr int MaximumFractionalDigits = 3;`

#### class `FModPatchCurveEditorModel`  
`class FModPatchCurveEditorModel : public WaveTable::Editor::FWaveTableCurveModel`  
_L32-55_
- inherits: `WaveTable::Editor::FWaveTableCurveModel`
- L35 _public member_ `static ECurveEditorViewID ModPatchViewId;`
- L37 _public prototype_ `FModPatchCurveEditorModel(FRichCurve& InRichCurve, UObject* InOwner, EWaveTableCurveSource InSource);`
- L39 _public prototype_ `virtual void RefreshCurveDescriptorText(const FWaveTableTransform& InTransform, FText& OutShortDisplayName, FText& OutInputAxisName, FText& OutOutputAxisName) override;`
- L41 _public function_ `virtual ECurveEditorViewID GetViewId() const override`
- L42 _public function_ `virtual FColor GetCurveColor() const override`
- L43 _public function_ `virtual bool GetPropertyEditorDisabled() const override`
- L44 _public function_ `virtual FText GetPropertyEditorDisabledText() const override`
- L46 _public prototype_ `virtual void GetValueRange(double& MinValue, double& MaxValue) const override;`
- L48 _public prototype_ `virtual bool ShowDefaultDashedLine() const override;`
- L49 _public prototype_ `virtual double GetDefaultDashedLineValue() const override;`
- L51 _public prototype_ `bool GetIsBypassed() const;`
- L53 _public prototype_ `USoundModulationPatch* GetPatch();`
- L54 _public prototype_ `const USoundModulationPatch* GetPatch() const;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define LOCTEXT_NAMESPACE "AudioModulation"`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/Editors/ModulationPatchEditor.h` (Private)


#### class `FModulationPatchEditor`  
`class FModulationPatchEditor : public WaveTable::Editor::FBankEditorBase`  
_L9-22_
- inherits: `WaveTable::Editor::FBankEditorBase`
- L12 _public prototype_ `FModulationPatchEditor() = default;`
- L13 _public prototype_ `virtual ~FModulationPatchEditor() = default;`
- L16 _protected prototype_ `virtual bool GetIsBypassed() const;`
- L17 _protected prototype_ `virtual bool GetIsPropertyEditorDisabled() const override;`
- L18 _protected prototype_ `virtual FWaveTableTransform* GetTransform(int32 InIndex) const override;`
- L19 _protected prototype_ `virtual int32 GetNumTransforms() const override;`
- L21 _protected prototype_ `virtual TUniquePtr<WaveTable::Editor::FWaveTableCurveModel> ConstructCurveModel(FRichCurve& InRichCurve, UObject* InParentObject, EWaveTableCurveSource InSource) override;`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/Factories/SoundControlBusFactory.h` (Private)


#### class `USoundControlBusFactory`  
`class USoundControlBusFactory : public UFactory`  
_L16-21_
- reflection: `UCLASS(hidecategories = Object, MinimalAPI)`
- inherits: `UFactory`
- L20 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/Factories/SoundControlBusMixFactory.h` (Private)


#### class `USoundControlBusMixFactory`  
`class USoundControlBusMixFactory : public UFactory`  
_L12-17_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI)`
- inherits: `UFactory`
- L16 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/Factories/SoundModulationGeneratorFactory.h` (Private)


#### class `USoundModulationGeneratorFactory`  
`class USoundModulationGeneratorFactory : public UFactory`  
_L12-23_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI)`
- inherits: `UFactory`
- L17 _private member_ `TSubclassOf<USoundModulationGenerator> GeneratorClass;` — `UPROPERTY()`
- L20 _private prototype_ `virtual bool ConfigureProperties() override;`
- L21 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/Factories/SoundModulationParameterFactory.h` (Private)


#### class `USoundModulationParameterFactory`  
`class USoundModulationParameterFactory : public UFactory`  
_L11-20_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI)`
- inherits: `UFactory`
- L15 _private prototype_ `virtual bool ConfigureProperties() override;`
- L16 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L19 _private member_ `UClass* ParameterClass;`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/Factories/SoundModulationPatchFactory.h` (Private)


#### class `USoundModulationPatchFactory`  
`class USoundModulationPatchFactory : public UFactory`  
_L12-19_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI)`
- inherits: `UFactory`
- L17 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/Layouts/SoundControlBusMixStageLayout.h` (Private)


#### class `FSoundControlBusMixStageLayoutCustomization`  
`class FSoundControlBusMixStageLayoutCustomization : public IPropertyTypeCustomization`  
_L14-26_
- inherits: `IPropertyTypeCustomization`
- L17 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L24 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/Layouts/SoundControlModulationPatchLayout.h` (Private)


#### class `FSoundControlModulationPatchLayoutCustomization`  
`class FSoundControlModulationPatchLayoutCustomization : public IPropertyTypeCustomization`  
_L18-45_
- inherits: `IPropertyTypeCustomization`
- L21 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L28 _private function_ `template <typename T> void AddPatchProperties(TAttribute<EVisibility> VisibilityAttribute, TMap<FName, TSharedPtr<IPropertyHandle>>& PropertyHandles, IDetailChildrenBuilder& ChildBuilder)`
- L40 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L41 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L44 _private prototype_ `TAttribute<EVisibility> CustomizeControl(TMap<FName, TSharedPtr<IPropertyHandle>>& PropertyHandles, IDetailChildrenBuilder& ChildBuilder);`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/Layouts/SoundModulationParameterSettingsLayout.h` (Private)


#### class `FSoundModulationParameterSettingsLayoutCustomization`  
`class FSoundModulationParameterSettingsLayoutCustomization : public IPropertyTypeCustomization`  
_L15-27_
- inherits: `IPropertyTypeCustomization`
- L18 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L24 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L25 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Private/Layouts/SoundModulationTransformLayout.h` (Private)


#### class `FSoundModulationTransformLayoutCustomization`  
`class FSoundModulationTransformLayoutCustomization : public WaveTable::Editor::FTransformLayoutCustomizationBase`  
_L18-32_
- inherits: `WaveTable::Editor::FTransformLayoutCustomizationBase`
- L21 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L28 _protected prototype_ `virtual TSet<EWaveTableCurve> GetSupportedCurves() const override;`
- L29 _protected prototype_ `virtual FWaveTableTransform* GetTransform() const override;`
- L30 _protected prototype_ `virtual bool IsBipolar() const override;`

### `Plugins/Runtime/AudioModulation/Source/AudioModulationEditor/Public/AudioModulationClassTemplates.h` (Public)


#### class `USoundModulationClassTemplate`  
`class USoundModulationClassTemplate : public UPluginClassTemplate`  
_L13-16_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UPluginClassTemplate`

#### class `USoundModulationGeneratorClassTemplate`  
`class USoundModulationGeneratorClassTemplate : public USoundModulationClassTemplate`  
_L19-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USoundModulationClassTemplate`
