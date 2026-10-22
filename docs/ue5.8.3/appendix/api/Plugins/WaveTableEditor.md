# Plugins / WaveTableEditor

- module root: `Plugins/Runtime/WaveTable/Source/WaveTableEditor`
- headers: 7; symbols: 191
- symbol kinds: class=10, delegate=1, enum=1, enumerator=4, function=23, macro=3, member=43, namespace=13, prototype=91, struct=2
- PrivateDependencyModuleNames: AssetDefinition, AudioEditor, AudioExtensions, Core, CoreUObject, CurveEditor, EditorFramework, EditorWidgets, Engine, GameProjectGeneration, InputCore, PropertyEditor, SequenceRecorder, Slate, ToolWidgets, UnrealEd, WaveTable
- PublicDependencyModuleNames: AssetTools, SlateCore

### `Plugins/Runtime/WaveTable/Source/WaveTableEditor/Private/AssetDefinition_WaveTableBank.h` (Private)


#### class `UAssetDefinition_WaveTableBank`  
`class UAssetDefinition_WaveTableBank : public UAssetDefinitionDefault`  
_L9-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L16 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L17 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L18 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L28 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Runtime/WaveTable/Source/WaveTableEditor/Private/WaveTableBankFactory.h` (Private)


#### class `UWaveTableBankFactory`  
`class UWaveTableBankFactory : public UFactory`  
_L10-17_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI)`
- inherits: `UFactory`
- L15 _private prototype_ `virtual UObject* FactoryCreateNew(UClass* Class,UObject* InParent,FName Name,EObjectFlags Flags,UObject* Context,FFeedbackContext* Warn) override;`

### `Plugins/Runtime/WaveTable/Source/WaveTableEditor/Private/WaveTableEditorModule.h` (Private)


#### class `WaveTable::Editor::FModule`  
`class FModule : public IModuleInterface`  
_L14-26_
- inherits: `IModuleInterface`
- L17 _public prototype_ `FModule() = default;`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L21 _public prototype_ `virtual void ShutdownModule() override;`
- L24 _private member_ `TArray<TSharedPtr<FAssetTypeActions_Base>> AssetActions;`
- L25 _private member_ `TSharedPtr<FSlateStyleSet> StyleSet;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWaveTableEditor, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWaveTableEditor, Log, All);`
- L12 _namespace_ `namespace WaveTable`
- L12 _namespace_ `namespace Editor` (scope `WaveTable`)

### `Plugins/Runtime/WaveTable/Source/WaveTableEditor/Public/WaveTableBankEditor.h` (Public)


#### class `WaveTable::Editor::FBankEditorBase`  
`class FBankEditorBase : public FAssetEditorToolkit, public FNotifyHook, public FEditorUndoClient`  
_L30-140_
- inherits: `FAssetEditorToolkit,FNotifyHook,FEditorUndoClient`
- L33 _public prototype_ `FBankEditorBase();`
- L34 _public prototype_ `virtual ~FBankEditorBase() = default;`
- L36 _public prototype_ `void Init(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InParentObject);`
- L39 _public prototype_ `virtual FName GetToolkitFName() const override;` — FAssetEditorToolkit interface
- L40 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L41 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L42 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L43 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L44 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L47 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;` — FNotifyHook interface
- L50 _public prototype_ `void RegenerateFileCurves();` — Regenerates curves set to "file" without refreshing whole stack view
- L53 _public prototype_ `void RefreshCurves();` — Updates & redraws curves.
- L70 _protected prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L71 _protected prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L73 _protected function_ `virtual bool GetIsPropertyEditorDisabled() const`
- L77 _protected function_ `virtual EWaveTableResolution GetBankResolution() const` — Returns resolution of bank being edited. By default, bank does not support WaveTable generation by being set to no resolution.
- L80 _protected function_ `virtual EWaveTableSamplingMode GetBankSamplingMode() const` — Returns sampling mode of bank being edited.
- L83 _protected function_ `virtual int32 GetBankSampleRate() const` — Returns sample rate to use if BankSamplingMode is set to 'SampleRate'.
- L87 _protected function_ `virtual bool GetBankIsBipolar() const` — Returns whether or not bank is bipolar.  By default, returns false (bank is unipolar), functionally operating as a unipolar envelope editor.
- L90 _protected prototype_ `virtual TUniquePtr<FWaveTableCurveModel> ConstructCurveModel(FRichCurve& InRichCurve, UObject* InParentObject, EWaveTableCurveSource InSource) = 0;` — Construct a new curve model for the given FRichCurve.  Allows for editor implementation to construct custom curve model types.
- L93 _protected prototype_ `virtual FWaveTableTransform* GetTransform (int32 InIndex) const = 0;` — Returns the transform associated with the given index
- L96 _protected prototype_ `virtual int32 GetNumTransforms() const = 0;` — Returns the number of transforms associated with the given bank.
- L98 _protected prototype_ `void SetCurve(int32 InTransformIndex, FRichCurve& InRichCurve, EWaveTableCurveSource InSource);`
- L103 _private prototype_ `void GenerateExpressionCurve(FCurveData& OutCurveData, int32 InTransformIndex, bool bInIsUnset = false);` — Regenerates expression curve at the given index. If curve is a 'File' and source PCM data in Transform is too long, inline edits are not included in recalculation for better interact performance.
- L105 _private prototype_ `void InitCurves();`
- L107 _private prototype_ `void ResetCurves();`
- L110 _private prototype_ `TSharedRef<SDockTab> SpawnTab_OutputCurve(const FSpawnTabArgs& Args);` — Spawns the tab allowing for editing/viewing the output curve(s)
- L113 _private prototype_ `TSharedRef<SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);` — Spawns the tab allowing for editing/viewing the output curve(s)
- L116 _private prototype_ `EOrientation GetSnapLabelOrientation() const;` — Get the orientation for the snap value controls.
- L119 _private prototype_ `static void TrimKeys(FRichCurve& OutCurve);` — Trims keys out-of-bounds in provided curve
- L122 _private prototype_ `void ClearExpressionCurve(int32 InTransformIndex);` — Clears the expression curve at the given input index
- L124 _private prototype_ `bool RequiresNewCurve(int32 InTransformIndex, const FRichCurve& InRichCurve) const;`
- L126 _private member_ `TSharedPtr<FUICommandList> ToolbarCurveTargetCommands;`
- L128 _private member_ `TSharedPtr<FCurveEditor> CurveEditor;`
- L129 _private member_ `TSharedPtr<SCurveEditorPanel> CurvePanel;`
- L131 _private member_ `TArray<FCurveData> CurveData;`
- L134 _private member_ `TSharedPtr<IDetailsView> PropertiesView;` — Properties tab
- L137 _private member_ `static const FName AppIdentifier;` — Settings Editor App Identifier
- L138 _private member_ `static const FName CurveTabId;`
- L139 _private member_ `static const FName PropertiesTabId;`

#### struct `WaveTable::Editor::FBankEditorBase::FCurveData`  
`struct FCurveData`  
_L56-68_
- L58 _public member_ `FCurveModelID ModelID;`
- L62 _public member_ `TSharedPtr<FRichCurve> ExpressionCurve;` — Curve used purely for display.  May be down-sampled from asset's curve for performance while editing
- L64 _public function_ `FCurveData() : ModelID(FCurveModelID::Unique())`

#### class `WaveTable::Editor::FBankEditor`  
`class FBankEditor : public FBankEditorBase`  
_L142-157_
- inherits: `FBankEditorBase`
- L145 _public prototype_ `FBankEditor() = default;`
- L146 _public prototype_ `virtual ~FBankEditor() = default;`
- L149 _protected prototype_ `virtual EWaveTableResolution GetBankResolution() const override;`
- L150 _protected prototype_ `virtual EWaveTableSamplingMode GetBankSamplingMode() const override;`
- L151 _protected prototype_ `virtual int32 GetBankSampleRate() const override;`
- L152 _protected prototype_ `virtual bool GetBankIsBipolar() const override;`
- L153 _protected prototype_ `virtual int32 GetNumTransforms() const override;`
- L154 _protected prototype_ `virtual FWaveTableTransform* GetTransform(int32 InIndex) const override;`
- L156 _protected prototype_ `virtual TUniquePtr<FWaveTableCurveModel> ConstructCurveModel(FRichCurve& InRichCurve, UObject* InParentObject, EWaveTableCurveSource InSource) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API WAVETABLEEDITOR_API`
- L15 _namespace_ `namespace WaveTable`
- L15 _namespace_ `namespace Editor` (scope `WaveTable`)
- L26 _namespace_ `namespace WaveTable`
- L28 _namespace_ `namespace Editor` (scope `WaveTable`)

### `Plugins/Runtime/WaveTable/Source/WaveTableEditor/Public/WaveTableCurveEditorViewStacked.h` (Public)


#### enum `EWaveTableCurveSource`  
`enum class EWaveTableCurveSource : uint8`  
_L22-28_
- reflection: `UENUM()`
- L24 _public enumerator_ `Custom`
- L25 _public enumerator_ `Expression`
- L26 _public enumerator_ `Shared`
- L27 _public enumerator_ `Unset`

#### class `WaveTable::Editor::FWaveTableCurveModel`  
`class FWaveTableCurveModel : public FRichCurveEditorModelRaw`  
_L35-86_
- inherits: `FRichCurveEditorModelRaw`
- L38 _public member_ `static ECurveEditorViewID WaveTableViewId;`
- L40 _public prototype_ `FWaveTableCurveModel(FRichCurve& InRichCurve, UObject* InOwner, EWaveTableCurveSource InSource);`
- L42 _public prototype_ `const FText& GetAxesDescriptor() const;`
- L43 _public prototype_ `const UObject* GetParentObject() const;`
- L44 _public prototype_ `EWaveTableCurveSource GetSource() const;`
- L45 _public prototype_ `void Refresh(const FWaveTableTransform& InTransform, int32 InCurveIndex, bool bInIsBipolar, EWaveTableSamplingMode InSamplingMode = EWaveTableSamplingMode::FixedResolution);`
- L47 _public function_ `virtual ECurveEditorViewID GetViewId() const`
- L48 _public prototype_ `virtual bool IsReadOnly() const override;`
- L49 _public prototype_ `virtual FLinearColor GetColor() const override;`
- L50 _public prototype_ `virtual void GetTimeRange(double& MinValue, double& MaxValue) const override;`
- L51 _public prototype_ `virtual void GetValueRange(double& MinValue, double& MaxValue) const override;`
- L53 _public function_ `virtual bool ShowDefaultDashedLine() const`
- L54 _public function_ `virtual double GetDefaultDashedLineValue() const`
- L56 _public function_ `float GetCurveDuration() const`
- L57 _public function_ `int32 GetCurveIndex() const`
- L58 _public function_ `bool GetIsBipolar() const`
- L59 _public function_ `float GetFadeInRatio() const`
- L60 _public function_ `float GetFadeOutRatio() const`
- L61 _public function_ `int32 GetNumSamples() const`
- L62 _public function_ `EWaveTableSamplingMode GetSamplingMode() const`
- L64 _protected prototype_ `virtual void RefreshCurveDescriptorText(const FWaveTableTransform& InTransform, FText& OutShortDisplayName, FText& OutInputAxisName, FText& OutOutputAxisName);`
- L65 _protected prototype_ `virtual FColor GetCurveColor() const;`
- L66 _protected prototype_ `virtual bool GetPropertyEditorDisabled() const;`
- L67 _protected prototype_ `virtual FText GetPropertyEditorDisabledText() const;`
- L69 _protected member_ `TWeakObjectPtr<UObject> ParentObject;`
- L72 _private member_ `int32 CurveIndex = INDEX_NONE;`
- L73 _private member_ `int32 NumSamples = 0;`
- L75 _private member_ `EWaveTableCurveSource Source = EWaveTableCurveSource::Unset;`
- L76 _private member_ `EWaveTableSamplingMode SamplingMode = EWaveTableSamplingMode::FixedResolution;`
- L78 _private member_ `bool bIsBipolar = false;`
- L80 _private member_ `float FadeInRatio = 0.0f;`
- L81 _private member_ `float FadeOutRatio = 0.0f;`
- L82 _private member_ `float CurveDuration = 1.0f;`
- L84 _private member_ `FText InputAxisName;`
- L85 _private member_ `FText AxesDescriptor;`

#### class `WaveTable::Editor::SViewStacked`  
`class SViewStacked : public SCurveEditorViewStacked`  
_L88-153_
- inherits: `SCurveEditorViewStacked`
- L91 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FCurveEditor> InCurveEditor);`
- L94 _protected prototype_ `virtual void PaintView( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L103 _protected prototype_ `virtual void DrawViewGrids(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, ESlateDrawEffect DrawEffects) const override;`
- L104 _protected prototype_ `virtual void DrawLabels(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, ESlateDrawEffect DrawEffects) const override;`
- L106 _protected prototype_ `virtual void FormatInputLabel(const FWaveTableCurveModel& EditorModel, const FNumberFormattingOptions& InLabelFormat, FText& InOutLabel) const;`
- L107 _protected function_ `virtual void FormatOutputLabel(const FWaveTableCurveModel& EditorModel, const FNumberFormattingOptions& InLabelFormat, FText& InOutLabel) const`
- L108 _protected prototype_ `virtual FText FormatToolTipTime(const FCurveModel& CurveModel, double EvaluatedTime) const override;`
- L151 _private prototype_ `void DrawViewGridLineX(FSlateWindowElementList& OutDrawElements, FGridDrawInfo& DrawInfo, ESlateDrawEffect DrawEffect, double OffsetAlpha, bool bIsMajor, bool bDashedLine = false) const;`
- L152 _private prototype_ `void DrawViewGridLineY(const float VerticalLine, FSlateWindowElementList& OutDrawElements, FGridDrawInfo &DrawInfo, ESlateDrawEffect DrawEffects, const FText* Label, bool bIsMajor) const;`

#### struct `WaveTable::Editor::SViewStacked::FGridDrawInfo`  
`struct FGridDrawInfo`  
_L111-149_
- L113 _public member_ `const FGeometry* AllottedGeometry = nullptr;`
- L115 _public member_ `FPaintGeometry PaintGeometry;`
- L117 _public member_ `ESlateDrawEffect DrawEffects;`
- L118 _public member_ `FNumberFormattingOptions LabelFormat;`
- L120 _public member_ `TArray<FVector2D> LinePoints;`
- L122 _public member_ `FCurveEditorScreenSpace ScreenSpace;`
- L125 _private member_ `FLinearColor MajorGridColor;`
- L126 _private member_ `FLinearColor MinorGridColor;`
- L128 _private member_ `int32 BaseLayerId = INDEX_NONE;`
- L130 _private member_ `const FCurveModel* CurveModel = nullptr;`
- L132 _private member_ `double LowerValue = 0.0;`
- L133 _private member_ `double PixelBottom = 0.0;`
- L134 _private member_ `double PixelTop = 0.0;`
- L137 _public prototype_ `FGridDrawInfo(const FGeometry* InAllottedGeometry, const FCurveEditorScreenSpace& InScreenSpace, FLinearColor InGridColor, int32 InBaseLayerId);`
- L139 _public prototype_ `void SetCurveModel(const FCurveModel* InCurveModel);`
- L140 _public prototype_ `const FCurveModel* GetCurveModel() const;`
- L141 _public prototype_ `void SetLowerValue(double InLowerValue);`
- L142 _public prototype_ `int32 GetBaseLayerId() const;`
- L143 _public prototype_ `FLinearColor GetLabelColor() const;`
- L144 _public prototype_ `double GetLowerValue() const;`
- L145 _public prototype_ `FLinearColor GetMajorGridColor() const;`
- L146 _public prototype_ `FLinearColor GetMinorGridColor() const;`
- L147 _public prototype_ `double GetPixelBottom() const;`
- L148 _public prototype_ `double GetPixelTop() const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API WAVETABLEEDITOR_API`
- L31 _namespace_ `namespace WaveTable`
- L33 _namespace_ `namespace Editor` (scope `WaveTable`)

### `Plugins/Runtime/WaveTable/Source/WaveTableEditor/Public/WaveTableFileUtilities.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace WaveTable`
- L8 _namespace_ `namespace Editor` (scope `WaveTable`)
- L10 _namespace_ `namespace FileUtilities` (scope `WaveTable::Editor`)
- L12 _prototype_ `void LoadPCMChannel(const FString& InFilePath, int32 InChannelIndex, FWaveTableData& OutData, int32& OutSampleRate);` (scope `WaveTable::Editor::FileUtilities`)
- L15 _prototype_ `void LoadPCMChannel(const FString& InFilePath, int32 InChannelIndex, TArray<float>& OutPCMData);` (scope `WaveTable::Editor::FileUtilities`) — `UE_DEPRECATED(5.3, "Use version of 'LoadPCMChannel' that takes in WaveTableData to support sample rate & bit depth conversion")`

### `Plugins/Runtime/WaveTable/Source/WaveTableEditor/Public/WaveTableTransformLayout.h` (Public)


#### class `WaveTable::Editor::FWaveTableDataLayoutCustomization`  
`class FWaveTableDataLayoutCustomization : public IPropertyTypeCustomization`  
_L17-27_
- inherits: `IPropertyTypeCustomization`
- L20 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `WaveTable::Editor::FTransformLayoutCustomizationBase`  
`class FTransformLayoutCustomizationBase : public IPropertyTypeCustomization`  
_L29-58_
- inherits: `IPropertyTypeCustomization`
- L33 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L34 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L38 _protected prototype_ `virtual TSet<EWaveTableCurve> GetSupportedCurves() const;`
- L39 _protected prototype_ `virtual FWaveTableTransform* GetTransform() const = 0;`
- L40 _protected prototype_ `virtual bool IsBipolar() const = 0;`
- L41 _protected prototype_ `virtual EWaveTableSamplingMode GetSamplingMode() const;`
- L43 _protected prototype_ `void CachePCMFromFile();`
- L44 _protected prototype_ `EWaveTableCurve GetCurve() const;`
- L45 _protected prototype_ `int32 GetOwningArrayIndex() const;`
- L46 _protected prototype_ `bool IsScaleableCurve() const;`
- L48 _protected member_ `TSharedPtr<IPropertyHandle> CurveHandle;`
- L49 _protected member_ `TSharedPtr<IPropertyHandle> ChannelIndexHandle;`
- L50 _protected member_ `TSharedPtr<IPropertyHandle> FilePathHandle;`
- L51 _protected member_ `TSharedPtr<IPropertyHandle> SourceDataHandle;`
- L52 _protected member_ `TSharedPtr<IPropertyHandle> WaveTableOptionsHandle;`
- L55 _private prototype_ `void CustomizeCurveSelector(IDetailChildrenBuilder& ChildBuilder);`
- L57 _private member_ `TMap<FString, FName> CurveDisplayStringToNameMap;`

#### class `WaveTable::Editor::FTransformLayoutCustomization`  
`class FTransformLayoutCustomization : public FTransformLayoutCustomizationBase`  
_L60-70_
- inherits: `FTransformLayoutCustomizationBase`
- L63 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L68 _public prototype_ `virtual bool IsBipolar() const override;`
- L69 _public prototype_ `virtual FWaveTableTransform* GetTransform() const override;`

#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API WAVETABLEEDITOR_API`
- L15 _namespace_ `namespace WaveTable`
- L15 _namespace_ `namespace Editor` (scope `WaveTable`)
