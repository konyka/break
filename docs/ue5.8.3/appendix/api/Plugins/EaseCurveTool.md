# Plugins / EaseCurveTool

- module root: `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool`
- headers: 38; symbols: 987
- symbol kinds: class=35, delegate=17, enum=4, enumerator=15, function=95, macro=3, member=286, namespace=52, prototype=471, struct=8, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, ContentBrowser, CoreUObject, CurveEditor, DeveloperSettings, EditorSubsystem, Engine, InputCore, Json, MovieScene, MovieSceneTools, Projects, PropertyEditor, Sequencer, SequencerCore, Slate, SlateCore, ToolMenus, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/AssetDefinition/AssetDefinition_EaseCurveLibrary.h` (Private)


#### class `UAssetDefinition_EaseCurveLibrary`  
`class UAssetDefinition_EaseCurveLibrary : public UAssetDefinitionDefault`  
_L9-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurve.h` (Private)


#### class `UEaseCurve`  
`class UEaseCurve : public UCurveFloat`  
_L10-46_
- reflection: `UCLASS()`
- inherits: `UCurveFloat`
- L15 _public prototype_ `UEaseCurve();`
- L17 _public prototype_ `FKeyHandle GetStartKeyHandle() const;`
- L18 _public prototype_ `FKeyHandle GetEndKeyHandle() const;`
- L20 _public prototype_ `FRichCurveKey& GetStartKey();`
- L21 _public prototype_ `FRichCurveKey& GetEndKey();`
- L23 _public prototype_ `float GetStartKeyTime() const;`
- L24 _public prototype_ `float GetStartKeyValue() const;`
- L25 _public prototype_ `float GetEndKeyTime() const;`
- L26 _public prototype_ `float GetEndKeyValue() const;`
- L28 _public prototype_ `FEaseCurveTangents GetTangents() const;`
- L29 _public prototype_ `void SetTangents(const FEaseCurveTangents& InTangents);`
- L30 _public prototype_ `void SetStartTangent(const float InTangent, const float InTangentWeight);`
- L31 _public prototype_ `void SetEndTangent(const float InTangent, const float InTangentWeight);`
- L33 _public prototype_ `void FlattenOrStraightenTangents(const FKeyHandle InKeyHandle, const bool bInFlattenTangents);`
- L35 _public prototype_ `void SetInterpMode(const ERichCurveInterpMode InInterpMode, const ERichCurveTangentMode InTangentMode);`
- L37 _public prototype_ `void BroadcastUpdate();`
- L40 _public prototype_ `virtual void OnCurveChanged(const TArray<FRichCurveEditInfo>& InRichCurveEditInfos) override;`
- L44 _protected member_ `FKeyHandle StartKeyHandle;`
- L45 _protected member_ `FKeyHandle EndKeyHandle;`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurveEditorExtension.h` (Private)


#### class `UE::EaseCurveTool::FEaseCurveEditorExtension`  
`class FEaseCurveEditorExtension : public ICurveEditorExtension`  
_L22-50_
- inherits: `ICurveEditorExtension`
- L25 _public prototype_ `explicit FEaseCurveEditorExtension(const TWeakPtr<FCurveEditor>& InWeakCurveEditor);`
- L28 _public prototype_ `virtual void BindCommands(TSharedRef<FUICommandList> InCommandList) override;`
- L29 _public prototype_ `virtual TSharedPtr<FExtender> MakeToolbarExtender(const TSharedRef<FUICommandList>& InCommandList) override;`
- L33 _private prototype_ `void ExtendCurveEditorToolbar(FToolBarBuilder& ToolBarBuilder);`
- L35 _private prototype_ `void PopupToolbarMenu();`
- L37 _private prototype_ `TSharedRef<SWidget> GetToolbarButtonMenuContent();`
- L39 _private prototype_ `EVisibility GetToolbarButtonVisibility() const;`
- L41 _private prototype_ `TSharedPtr<FEaseCurveTool> GetToolInstance() const;`
- L43 _private prototype_ `bool IsButtonEnabled() const;`
- L45 _private prototype_ `FText GetEaseCurveTooltipText() const;`
- L47 _private member_ `TWeakPtr<FCurveEditor> WeakCurveEditor;`
- L49 _private member_ `TSharedPtr<FCurveEditorToolBarMenu> ButtonMenu;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurveKeySelection.h` (Private)


#### enum `EEaseCurveToolError`  
`enum class EEaseCurveToolError : uint8`  
_L26-36_
- reflection: `UENUM()`
- L29 _public enumerator_ `None = 0` — All selected keys are valid ease-able keys
- L31 _public enumerator_ `LastKey = 1 << 1` — All selected keys are the last key of the channel and have no next key to ease to
- L33 _public enumerator_ `SameValues = 1 << 2` — All selected keys have the same values (easing would result in no change)
- L35 _public enumerator_ `NoWeightedBrokenCubicTangents = 1 << 3` — All selected keys are not weighted, broken, cubic tangents

#### struct `UE::EaseCurveTool::FEaseCurveChannelKeyCache`  
`struct FEaseCurveChannelKeyCache`  
_L45-57_
- desc: Cached set of key handles for a channel
- L47 _public member_ `TObjectPtr<UMovieSceneSection> Section;`
- L48 _public member_ `FMovieSceneChannelHandle ChannelHandle;`
- L49 _public member_ `TMap<FKeyHandle, EEaseCurveToolError> KeyHandles;`
- L52 _public function_ `template <class InChannelHandleType, class InChannelValueType> TMovieSceneChannelData<InChannelValueType> GetChannelData()`

#### struct `UE::EaseCurveTool::FEaseCurveKeySelection`  
`struct FEaseCurveKeySelection`  
_L60-226_
- desc: Represents a key selection, either Curve Editor (prioritized) or Sequencer, that can be operated on by the Ease Curve Tool
- L63 _public function_ `FEaseCurveKeySelection()` — Constructs an empty ease curve key selection
- L65 _public prototype_ `FEaseCurveKeySelection(const TSharedPtr<ISequencer>& InSequencer);` — Constructs an ease curve key selection from a sequencer key selection
- L67 _public prototype_ `FEaseCurveTangents AverageTangents(const FFrameRate& InDisplayRate , const FFrameRate& InTickResolution , const bool bInAutoFlipTangents , const bool bInFirstOnly = false);`
- L72 _public prototype_ `void SetTangents(const FEaseCurveTangents& InTangents , const EEaseCurveToolOperation InOperation , const FFrameRate& InDisplayRate , const FFrameRate& InTickResolution , const bool bInAutoFlipTangents);`
- L78 _public function_ `bool HasCachedKeysToEase() const`
- L83 _public function_ `int32 GetTotalSelectedKeys() const`
- L88 _public function_ `bool IsCurveEditorSelection() const`
- L93 _public prototype_ `int32 GetKeyChannelCount() const;`
- L96 _public function_ `EEaseCurveToolError GetSelectionError() const` — @return Error code specifying why the key selection is not valid to be used by the Ease Curve Tool to perform operations on
- L102 _protected typedef_ `using FProcessKeySignature = TFunctionRef<bool(const FKeyHandle& , const FKeyHandle& , const FMovieSceneChannelHandle& , const TObjectPtr<UMovieSceneSection>& )>;`
- L107 _protected prototype_ `void SetSelectionError();`
- L109 _protected prototype_ `EEaseCurveToolError FindErrorForKey(const FMovieSceneChannelHandle& InChannelHandle, const FKeyHandle& InKey);`
- L112 _protected function_ `template <class InChannelType, class InValueType> static EEaseCurveToolError FindErrorForKey_Internal(const FKeyHandle& InKeyHandle, const FMovieSceneChannelHandle& InChannelHandle)`
- L155 _protected prototype_ `bool ProcessSequencerKeySelection(const TSharedPtr<Sequencer::FSequencerSelection>& InSequencerSelection, const FKeyHandle InKey);`
- L156 _protected prototype_ `bool ProcessCurveEditorKeySelection(FCurveModel& CurveModel, const FMovieSceneChannelHandle& ChannelHandle, const FKeyHandle& InKey);`
- L158 _protected prototype_ `void ForEachEaseableKey(const FProcessKeySignature& InCallable);`
- L160 _protected prototype_ `bool ForEachChannelKey(const FMovieSceneChannelHandle& InChannelHandle , const TMap<FKeyHandle, EEaseCurveToolError>& InKeyHandles , const TObjectPtr<UMovieSceneSection>& InSection , const FProcessKeySignature& InCallable);`
- L166 _protected function_ `template <class InChannelType, class InValueType> bool ForEachChannelKey_Internal(const FMovieSceneChannelHandle& InChannelHandle , const TMap<FKeyHandle, EEaseCurveToolError>& InKeyHandles , const TObjectPtr<UMovieSceneSection>& InSection , const FProcessKeySignature& InCallable)`
- L220 _protected member_ `TMap<UE::Sequencer::TViewModelPtr<UE::Sequencer::FChannelModel>, FEaseCurveChannelKeyCache> SequencerKeyData;`
- L221 _protected member_ `TMap<FCurveModelID, FEaseCurveChannelKeyCache> CurveEditorKeyData;`
- L223 _protected member_ `int32 TotalSelectedKeys = 0;`
- L225 _protected member_ `EEaseCurveToolError SelectionError = EEaseCurveToolError::None;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Sequencer` (scope `UE`)
- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurveLibraryFactory.h` (Private)


#### class `UEaseCurveLibraryFactory`  
`class UEaseCurveLibraryFactory : public UFactory`  
_L9-22_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L14 _public prototype_ `UEaseCurveLibraryFactory();`
- L17 _public prototype_ `virtual FText GetDisplayName() const override;`
- L18 _public prototype_ `virtual FText GetToolTip() const override;`
- L19 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L20 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurvePreset.h` (Private)


#### struct `FEaseCurvePresetHandle`  
`struct FEaseCurvePresetHandle`  
_L11-28_
- desc: Store category and name as a handle to pass around for preset identification
- L13 _public function_ `FEaseCurvePresetHandle()`
- L14 _public function_ `FEaseCurvePresetHandle(const FText& InCategory, const FText& InName) : Category(InCategory), Name(InName)`
- L21 _public function_ `FORCEINLINE bool operator==(const FEaseCurvePresetHandle& InRhs) const`
- L26 _public member_ `FText Category;`
- L27 _public member_ `FText Name;`

#### struct `FEaseCurvePreset`  
`struct FEaseCurvePreset`  
_L31-77_
- reflection: `USTRUCT()`
- L35 _public function_ `FEaseCurvePreset()`
- L36 _public function_ `FEaseCurvePreset(const FText& InCategory, const FText& InName, const FEaseCurveTangents& InTangents) : Category(InCategory), Name(InName), Tangents(InTangents)`
- L39 _public function_ `FEaseCurvePreset(const FEaseCurvePresetHandle& InHandle, const FEaseCurveTangents& InTangents) : Category(InHandle.Category), Name(InHandle.Name), Tangents(InTangents)`
- L43 _public function_ `FORCEINLINE bool operator==(const FEaseCurvePresetHandle& InRhs) const`
- L47 _public function_ `FORCEINLINE bool operator==(const FEaseCurvePreset& InRhs) const`
- L51 _public function_ `FORCEINLINE bool operator!=(const FEaseCurvePreset& InRhs) const`
- L56 _public function_ `FORCEINLINE bool operator<(const FEaseCurvePreset& InRhs) const`
- L64 _public function_ `FEaseCurvePresetHandle GetHandle() const`
- L70 _public member_ `FText Category;` — `UPROPERTY(Config, EditAnywhere, Category = "EaseCurvePreset")`
- L73 _public member_ `FText Name;` — `UPROPERTY(Config, EditAnywhere, Category = "EaseCurvePreset")`
- L76 _public member_ `FEaseCurveTangents Tangents;` — `UPROPERTY(Config, EditAnywhere, Category = "EaseCurvePreset")`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurvePresetDragDropOperation.h` (Private)


#### class `UE::EaseCurveTool::FEaseCurvePresetDragDropOperation`  
`class FEaseCurvePresetDragDropOperation : public FDragDropOperation`  
_L16-41_
- inherits: `FDragDropOperation`
- L19 _public function_ `DRAG_DROP_OPERATOR_TYPE(FEaseCurvePresetDragDropOperation, FDragDropOperation) FEaseCurvePresetDragDropOperation(const TSharedPtr<SEaseCurvePresetGroupItem>& InWidget, const TSharedPtr<FEaseCurvePreset>& InPreset) : WidgetWeak(InWidget), Preset(InPreset)`
- L25 _public function_ `TSharedPtr<SEaseCurvePresetGroupItem> GetWidget() const`
- L26 _public function_ `TSharedPtr<FEaseCurvePreset> GetPreset() const`
- L29 _public prototype_ `virtual FCursorReply OnCursorQuery() override;`
- L30 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L31 _public prototype_ `virtual void OnDrop(bool bInDropWasHandled, const FPointerEvent& InMouseEvent) override;`
- L34 _public prototype_ `void AddHoveredGroup(const TSharedRef<SEaseCurvePresetGroup>& InGroupWidget);`
- L37 _protected member_ `TWeakPtr<SEaseCurvePresetGroupItem> WidgetWeak;`
- L38 _protected member_ `TSharedPtr<FEaseCurvePreset> Preset;`
- L40 _protected member_ `TSet<TWeakPtr<SEaseCurvePresetGroup>> HoveredGroupWidgets;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurveStyle.h` (Private)


#### class `FEaseCurveStyle`  
`class FEaseCurveStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FEaseCurveStyle& Get()`
- L16 _public prototype_ `FEaseCurveStyle();`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurveTangents.h` (Private)


#### struct `FEaseCurveTangents`  
`struct FEaseCurveTangents`  
_L17-108_
- reflection: `USTRUCT()`
- desc: Generic representation of a curve constructed of two tangents and their weights, one for each end of the curve.
- L22 _public prototype_ `static bool FromString(const FString& InString, FEaseCurveTangents& OutTangents);`
- L23 _public prototype_ `static bool CanParseString(const FString& InString);`
- L25 _public prototype_ `static FNumberFormattingOptions DefaultNumberFormattingOptions();`
- L27 _public prototype_ `static FEaseCurveTangents Average(const TArray<FEaseCurveTangents>& InTangentArray);`
- L29 _public function_ `FEaseCurveTangents()`
- L30 _public function_ `FEaseCurveTangents(const double InStart, const double InStartWeight, const double InEnd, const double InEndWeight) : Start(InStart), StartWeight(InStartWeight) , End(InEnd), EndWeight(InEndWeight)`
- L34 _public function_ `FEaseCurveTangents(const FRichCurveKey& InRichCurveKey) : Start(InRichCurveKey.LeaveTangent), StartWeight(InRichCurveKey.LeaveTangentWeight) , End(InRichCurveKey.ArriveTangent), EndWeight(InRichCurveKey.ArriveTangentWeight)`
- L38 _public function_ `FEaseCurveTangents(const FRichCurveKey& InStartRichCurveKey, const FRichCurveKey& InEndRichCurveKey) : Start(InStartRichCurveKey.LeaveTangent), StartWeight(InStartRichCurveKey.LeaveTangentWeight) , End(InEndRichCurveKey.ArriveTangent), EndWeight(InEndRichCurveKey.ArriveTangentWeight)`
- L42 _public function_ `FEaseCurveTangents(const FMovieSceneDoubleValue& InMovieSceneDoubleValue) : Start(InMovieSceneDoubleValue.Tangent.LeaveTangent), StartWeight(InMovieSceneDoubleValue.Tangent.LeaveTangentWeight) , End(InMovieSceneDoubleValue.Tangent.ArriveTangent), EndWeight(InMovieSceneDoubleValue.Tangent.ArriveTangentWeight)`
- L46 _public function_ `FEaseCurveTangents(const FMovieSceneDoubleValue& InStartMovieSceneDoubleValue, const FMovieSceneDoubleValue& InEndMovieSceneDoubleValue) : Start(InStartMovieSceneDoubleValue.Tangent.LeaveTangent), StartWeight(InStartMovieSceneDoubleValue.Tangent.LeaveTangentWeight) , End(InEndMovieSceneDoubleValue.Tangent.ArriveTangent), EndWeight(InEndMovieSceneDoubleValue.Tangent.ArriveTangentWeight)`
- L50 _public function_ `FEaseCurveTangents(const FMovieSceneFloatValue& InMovieSceneFloatValue) : Start(InMovieSceneFloatValue.Tangent.LeaveTangent), StartWeight(InMovieSceneFloatValue.Tangent.LeaveTangentWeight) , End(InMovieSceneFloatValue.Tangent.ArriveTangent), EndWeight(InMovieSceneFloatValue.Tangent.ArriveTangentWeight)`
- L54 _public function_ `FEaseCurveTangents(const FMovieSceneFloatValue& InStartMovieSceneFloatValue, const FMovieSceneFloatValue& InEndMovieSceneFloatValue) : Start(InStartMovieSceneFloatValue.Tangent.LeaveTangent), StartWeight(InStartMovieSceneFloatValue.Tangent.LeaveTangentWeight) , End(InEndMovieSceneFloatValue.Tangent.ArriveTangent), EndWeight(InEndMovieSceneFloatValue.Tangent.ArriveTangentWeight)`
- L59 _public prototype_ `explicit FEaseCurveTangents(const FString& InTangentsString);` — Constructor from string consisting of cubic bezier points. Ex. "0.45, 0.34, 0.0, 1.00"
- L61 _public function_ `FORCEINLINE bool operator==(const FEaseCurveTangents& InRhs) const`
- L65 _public function_ `FORCEINLINE bool operator!=(const FEaseCurveTangents& InRhs) const`
- L70 _public prototype_ `bool IsNearlyEqual(const FEaseCurveTangents& InOther, const double InErrorTolerance = UE_DOUBLE_SMALL_NUMBER) const;`
- L72 _public prototype_ `FText ToDisplayText() const;`
- L73 _public prototype_ `FString ToDisplayString() const;`
- L75 _public prototype_ `FString ToJson() const;`
- L77 _public prototype_ `FText GetStartTangentText() const;`
- L78 _public prototype_ `FText GetEndTangentText() const;`
- L79 _public prototype_ `FText GetCubicBezierText() const;`
- L81 _public prototype_ `static FEaseCurveTangents MakeFromCubicBezier(const TStaticArray<double, 4>& InPoints);`
- L83 _public prototype_ `bool FromCubicBezier(const TStaticArray<double, 4>& InPoints);`
- L84 _public prototype_ `bool ToCubicBezier(TStaticArray<double, 4>& OutPoints) const;`
- L86 _public prototype_ `void Normalize(const FFrameNumber& InFrameNumber, const double InValue , const FFrameNumber& InNextFrameNumber, const double InNextValue , const FFrameRate& InDisplayRate, const FFrameRate& InTickResolution);`
- L90 _public prototype_ `void ScaleUp(const FFrameNumber& InFrameNumber, const double InValue , const FFrameNumber& InNextFrameNumber, const double InNextValue , const FFrameRate& InDisplayRate, const FFrameRate& InTickResolution);`
- L95 _public prototype_ `double CalculateCurveLength(const int32 InSampleCount = 10) const;` — Calculates the length of this curve. The higher the sample count, the higher the calculation precision.
- L98 _public member_ `double Start = 0.0;` — `UPROPERTY(Config, EditAnywhere, Category = "EaseCurveTangents")`
- L101 _public member_ `double StartWeight = 0.0;` — `UPROPERTY(Config, EditAnywhere, Category = "EaseCurveTangents")`
- L104 _public member_ `double End = 0.0;` — `UPROPERTY(Config, EditAnywhere, Category = "EaseCurveTangents")`
- L107 _public member_ `double EndWeight = 0.0;` — `UPROPERTY(Config, EditAnywhere, Category = "EaseCurveTangents")`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurveTool.h` (Private)


#### enum `UE::EaseCurveTool::EEaseCurveToolMode`  
`enum class EEaseCurveToolMode : uint8`  
_L32-40_
- desc: Current default and only implemented is DualKeyEdit.
- L35 _public enumerator_ `DualKeyEdit` — Edits the selected key's leave tangent and the next key's arrive tangent in the curve editor graph.
- L39 _public enumerator_ `SingleKeyEdit` — Edits only the selected key. The leave tangent in the curve editor graph will set the sequence key arrive tangent. The arrive tangent in the curve editor graph will set the sequence key leave tangent.

#### enum `UE::EaseCurveTool::EEaseCurveToolOperation`  
`enum class EEaseCurveToolOperation : uint8`  
_L42-47_
- L44 _public enumerator_ `InOut`
- L45 _public enumerator_ `In`
- L46 _public enumerator_ `Out`

#### class `UE::EaseCurveTool::FEaseCurveTool`  
`class FEaseCurveTool : public TSharedFromThis<FEaseCurveTool> , public FGCObject , public FSelfRegisteringEditorUndoClient , public FTickableEditorObject`  
_L52-213_
- inherits: `TSharedFromThis<FEaseCurveTool>,FGCObject,FSelfRegisteringEditorUndoClient,FTickableEditorObject`
- L59 _public prototype_ `static void ShowNotificationMessage(const FText& InMessageText);`
- L61 _public prototype_ `static void RecordPresetAnalytics(const TSharedPtr<FEaseCurvePreset>& InPreset, const FString& InLocation);`
- L64 _public prototype_ `static bool TangentsFromClipboardPaste(FEaseCurveTangents& OutTangents);` — Returns true if the clipboard paste data contains tangent information.
- L66 _public prototype_ `FEaseCurveTool(const TSharedRef<ISequencer>& InSequencer);`
- L70 _public prototype_ `TSharedPtr<ISequencer> GetSequencer() const;`
- L72 _public prototype_ `bool IsToolTabVisible() const;`
- L73 _public prototype_ `void ShowHideToolTab(const bool bInVisible);`
- L74 _public prototype_ `void ToggleToolTabVisible();`
- L76 _public prototype_ `TSharedRef<SWidget> GenerateWidget();`
- L77 _public prototype_ `TSharedPtr<SEaseCurveTool> GetToolWidget() const;`
- L79 _public prototype_ `UEaseCurveLibrary* GetPresetLibrary() const;`
- L80 _public prototype_ `void SetPresetLibrary(const TWeakObjectPtr<UEaseCurveLibrary>& InPresetLibrary);`
- L83 _public function_ `FOnEaseCurveLibraryChanged& OnPresetLibraryChanged()` — Event that broadcasts when the underlying ease curve preset library has been changed
- L85 _public prototype_ `TObjectPtr<UEaseCurve> GetToolCurve() const;`
- L86 _public prototype_ `FRichCurve* GetToolRichCurve() const;`
- L88 _public prototype_ `FEaseCurveTangents GetEaseCurveTangents() const;`
- L95 _public prototype_ `void SetEaseCurveTangents(const FEaseCurveTangents& InTangents , const EEaseCurveToolOperation InOperation , const bool bInBroadcastUpdate , const bool bInSetSequencerTangents , const FText& InTransactionText = NSLOCTEXT("EaseCurveToo` — Sets the internal ease curve tangents and optionally broadcasts a change event for the curve object. This is different from SetEaseCurveTangents_Internal in that it performs undo/redo transactions and optionally sets the selected tangents in the actual sequence.
- L101 _public prototype_ `void ResetEaseCurveTangents(const EEaseCurveToolOperation InOperation);`
- L103 _public prototype_ `void FlattenOrStraightenTangents(const EEaseCurveToolOperation InOperation, const bool bInFlattenTangents);`
- L106 _public prototype_ `UCurveBase* CreateCurveAsset() const;` — Creates a new external float curve from the internet curve editor curve.
- L108 _public prototype_ `void SetSequencerKeySelectionTangents(const FEaseCurveTangents& InTangents, const EEaseCurveToolOperation InOperation = EEaseCurveToolOperation::InOut);`
- L110 _public prototype_ `bool CanApplyQuickEaseToSequencerKeySelections() const;`
- L111 _public prototype_ `void ApplyQuickEaseToSequencerKeySelections(const EEaseCurveToolOperation InOperation = EEaseCurveToolOperation::InOut);`
- L114 _public prototype_ `void UpdateEaseCurveFromKeySelections();` — Updates the ease curve graph view based on the active sequencer or curve editor key selection.
- L116 _public prototype_ `EEaseCurveToolOperation GetToolOperation() const;`
- L117 _public prototype_ `void SetToolOperation(const EEaseCurveToolOperation InNewOperation);`
- L118 _public prototype_ `bool IsToolOperation(const EEaseCurveToolOperation InNewOperation) const;`
- L120 _public prototype_ `bool CanCopyTangentsToClipboard() const;`
- L121 _public prototype_ `void CopyTangentsToClipboard() const;`
- L122 _public prototype_ `bool CanPasteTangentsFromClipboard() const;`
- L123 _public prototype_ `void PasteTangentsFromClipboard() const;`
- L125 _public prototype_ `bool IsKeyInterpMode(const ERichCurveInterpMode InInterpMode, const ERichCurveTangentMode InTangentMode) const;`
- L126 _public prototype_ `void SetKeyInterpMode(const ERichCurveInterpMode InInterpMode, const ERichCurveTangentMode InTangentMode) const;`
- L128 _public prototype_ `void BeginTransaction(const FText& InDescription) const;`
- L129 _public prototype_ `void EndTransaction() const;`
- L131 _public prototype_ `void OpenToolSettings() const;`
- L133 _public prototype_ `FFrameRate GetTickResolution() const;`
- L134 _public prototype_ `FFrameRate GetDisplayRate() const;`
- L136 _public prototype_ `bool HasCachedKeysToEase() const;`
- L138 _public prototype_ `EEaseCurveToolError GetSelectionError() const;`
- L139 _public prototype_ `FText GetSelectionErrorText() const;`
- L142 _public prototype_ `bool IsCurveEditorSelection() const;` — @return True if the tool is operating on a curve editor key selection, False if operating on a Sequencer key selection
- L145 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L146 _public prototype_ `virtual FString GetReferencerName() const override;`
- L150 _public prototype_ `virtual void PostUndo(const bool bInSuccess) override;`
- L151 _public prototype_ `virtual void PostRedo(const bool bInSuccess) override;`
- L155 _public prototype_ `virtual bool IsTickable() const override;`
- L156 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L157 _public prototype_ `virtual TStatId GetStatId() const override;`
- L158 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L161 _public prototype_ `TSharedPtr<FUICommandList> GetCommandList() const;`
- L163 _public function_ `FEaseCurveKeySelection& GetSelectedKeyCache()`
- L165 _public prototype_ `FEaseCurveTangents GetAverageTangentsFromKeyCache();`
- L168 _protected prototype_ `void ApplyTangents();`
- L169 _protected prototype_ `void ZoomToFit() const;`
- L171 _protected prototype_ `void BindCommands();`
- L177 _protected prototype_ `void SetEaseCurveTangents_Internal(const FEaseCurveTangents& InTangents, const EEaseCurveToolOperation InOperation, const bool bInBroadcastUpdate) const;` — Sets the internal ease curve tangents and optionally broadcasts a change event for the curve object. Changing the internal ease curve tangents will be directly reflected in the ease curve editor graph.
- L179 _protected prototype_ `void UpdateEaseCurveFromKeyCache();`
- L181 _protected member_ `TWeakPtr<ISequencer> SequencerWeak;`
- L183 _protected member_ `TSharedRef<FEaseCurveToolTab> ToolTab;`
- L185 _protected member_ `TSharedPtr<FUICommandList> CommandList;`
- L187 _protected member_ `TWeakObjectPtr<UEaseCurveLibrary> WeakPresetLibrary;`
- L188 _protected member_ `FOnEaseCurveLibraryChanged PresetLibraryChangedDelegate;`
- L190 _protected member_ `TObjectPtr<UEaseCurve> EaseCurve;`
- L192 _protected member_ `TObjectPtr<UEaseCurveToolSettings> ToolSettings;`
- L194 _protected member_ `EEaseCurveToolMode ToolMode = EEaseCurveToolMode::DualKeyEdit;`
- L195 _protected member_ `EEaseCurveToolOperation OperationMode = EEaseCurveToolOperation::InOut;`
- L197 _protected member_ `TSharedPtr<SEaseCurveTool> ToolWidget;`
- L200 _protected member_ `FEaseCurveKeySelection KeyCache;` — Cached data set when a new sequencer selection is made.
- L202 _protected member_ `bool bRefreshForKeySelectionChange = false;`
- L204 _protected member_ `FCurveEditorSelection LastCurveEditorSelection;`
- L207 _private prototype_ `void OnSequencerSelectionChanged(TArray<FGuid> InObjectGuids);`
- L208 _private prototype_ `void OnMovieSceneDataChanged(const EMovieSceneDataChangeType InMetaData);`
- L210 _private prototype_ `void OnTabVisibilityChanged(const bool bInVisible);`
- L212 _private prototype_ `void OnCurveEditorSelectionChanged();`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace EaseCurveTool` (scope `UE`)
- L49 _delegate_ `DECLARE_DELEGATE_RetVal(UEaseCurveLibrary*, FOnGetEaseCurveSelectedLibrary) DECLARE_MULTICAST_DELEGATE_OneParam(FOnEaseCurveLibraryChanged, TWeakObjectPtr<UEaseCurveLibrary> ) class FEaseCurveTool : public TSharedFromThis<FEaseCurveTool> , public FGCObject , public FSelfRegisteringEditorUndoClient , public FTickableEditorObject { public: static void ShowNotificationMessage(const FText& InMessageText); static void RecordPresetAnalytics(const TSharedPtr<FEaseCurvePreset>& InPreset, const FString& InLocation); static bool TangentsFromClipboardPaste(FEaseCurveTangents& OutTangents); FEaseCurveTool(const TSharedRef<ISequencer>& InSequencer); virtual ~FEaseCurveTool() override; TSharedPtr<ISequencer> GetSequencer() const; bool IsToolTabVisible() const; void ShowHideToolTab(const bool bInVisible); void ToggleToolTabVisible(); TSharedRef<SWidget> GenerateWidget(); TSharedPtr<SEaseCurveTool> GetToolWidget() const; UEaseCurveLibrary* GetPresetLibrary() const; void SetPresetLibrary(const TWeakObjectPtr<UEaseCurveLibrary>& InPresetLibrary); FOnEaseCurveLibraryChanged& OnPresetLibraryChanged() { return PresetLibraryChangedDelegate; } TObjectPtr<UEaseCurve> GetToolCurve() const; FRichCurve* GetToolRichCurve() const; FEaseCurveTangents GetEaseCurveTangents() const;`
- L50 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnEaseCurveLibraryChanged, TWeakObjectPtr<UEaseCurveLibrary> ) class FEaseCurveTool : public TSharedFromThis<FEaseCurveTool> , public FGCObject , public FSelfRegisteringEditorUndoClient , public FTickableEditorObject { public: static void ShowNotificationMessage(const FText& InMessageText); static void RecordPresetAnalytics(const TSharedPtr<FEaseCurvePreset>& InPreset, const FString& InLocation); static bool TangentsFromClipboardPaste(FEaseCurveTangents& OutTangents); FEaseCurveTool(const TSharedRef<ISequencer>& InSequencer); virtual ~FEaseCurveTool() override; TSharedPtr<ISequencer> GetSequencer() const; bool IsToolTabVisible() const; void ShowHideToolTab(const bool bInVisible); void ToggleToolTabVisible(); TSharedRef<SWidget> GenerateWidget(); TSharedPtr<SEaseCurveTool> GetToolWidget() const; UEaseCurveLibrary* GetPresetLibrary() const; void SetPresetLibrary(const TWeakObjectPtr<UEaseCurveLibrary>& InPresetLibrary); FOnEaseCurveLibraryChanged& OnPresetLibraryChanged() { return PresetLibraryChangedDelegate; } TObjectPtr<UEaseCurve> GetToolCurve() const; FRichCurve* GetToolRichCurve() const; FEaseCurveTangents GetEaseCurveTangents() const;`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurveToolCommands.h` (Private)


#### class `FEaseCurveToolCommands`  
`class FEaseCurveToolCommands : public TCommands<FEaseCurveToolCommands>`  
_L8-70_
- inherits: `TCommands<FEaseCurveToolCommands>`
- L11 _public function_ `FEaseCurveToolCommands() : TCommands<FEaseCurveToolCommands>(TEXT("EaseCurveTool") , NSLOCTEXT("EaseCurveToolCommands", "EaseCurveToolCommands", "Ease Curve Tool Commands") , NAME_None , FAppStyle::GetAppStyleSetName())`
- L19 _public prototype_ `virtual void RegisterCommands() override;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> ToggleToolTabVisible;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> OpenToolSettings;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> Refresh;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> Apply;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> ZoomToFit;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> SetOperationToEaseOut;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> SetOperationToEaseInOut;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> SetOperationToEaseIn;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> ToggleGridSnap;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ToggleAutoFlipTangents;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> ToggleAutoZoomToFit;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> ResetTangents;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> ResetStartTangent;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> ResetEndTangent;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> FlattenTangents;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> FlattenStartTangent;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> FlattenEndTangent;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> StraightenTangents;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> StraightenStartTangent;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> StraightenEndTangent;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> CopyTangents;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> PasteTangents;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> CreateExternalCurveAsset;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> SetKeyInterpConstant;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> SetKeyInterpLinear;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> SetKeyInterpCubicAuto;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> SetKeyInterpCubicSmartAuto;`
- L61 _public member_ `TSharedPtr<FUICommandInfo> SetKeyInterpCubicUser;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> SetKeyInterpCubicBreak;`
- L63 _public member_ `TSharedPtr<FUICommandInfo> SetKeyInterpToggleWeighted;`
- L65 _public member_ `TSharedPtr<FUICommandInfo> QuickEase;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> QuickEaseIn;`
- L67 _public member_ `TSharedPtr<FUICommandInfo> QuickEaseOut;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> SaveCurveEditorSelection;`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurveToolExtender.h` (Private)


#### class `UE::EaseCurveTool::FEaseCurveToolExtender`  
`class FEaseCurveToolExtender : IModularFeature`  
_L27-89_
- inherits: `IModularFeature`
- desc: Singleton class for extending and managing tool instances.
- L30 _public prototype_ `static FEaseCurveToolExtender& Get();`
- L32 _public prototype_ `FEaseCurveToolExtender();`
- L33 _public prototype_ `virtual ~FEaseCurveToolExtender();`
- L35 _public prototype_ `static FName GetModularFeatureName();`
- L44 _public prototype_ `static FName GetToolInstanceId(const ISequencer& InSequencer);` — Retrieves the unique name for the provided Sequencer instance. The tool instance name is based on its associated sequencer settings object name. This provides a unique instance name for each Sequencer type. @param InSequencer The Sequencer instance for which the name is being retrieved. @return The name of the tool instance if available; otherwise, NAME_None.
- L45 _public prototype_ `static FName GetToolInstanceId(const FEaseCurveTool& InTool);`
- L47 _public prototype_ `static TSharedPtr<FEaseCurveTool> GetToolInstance(const FName InToolId);`
- L50 _public prototype_ `static TSharedPtr<FEaseCurveTool> FindToolInstance(const TSharedRef<ISequencer>& InSequencer);` — Find the tool instance associated with the given Sequencer instance
- L52 _public prototype_ `static TSharedPtr<FEaseCurveTool> FindToolInstanceByCurveEditor(const TSharedRef<FCurveEditor>& InCurveEditor);`
- L54 _public prototype_ `static TSharedRef<SWidget> MakeQuickPresetMenu(const FName InToolId);`
- L70 _protected prototype_ `FEaseCurveToolInstance* FindOrAddToolInstance_Internal(const TSharedRef<ISequencer>& InSequencer);`
- L72 _protected prototype_ `void OnSequencerCreated(const TSharedRef<ISequencer> InSequencer);`
- L73 _protected prototype_ `void OnSequencerClosed(const TSharedRef<ISequencer> InSequencer, const FName InToolId);`
- L75 _protected prototype_ `static void AddSidebarExtension(FEaseCurveToolInstance& InToolInstance);`
- L76 _protected prototype_ `static void RemoveSidebarExtension(FEaseCurveToolInstance& InToolInstance);`
- L78 _protected prototype_ `static void AddSidebarWidget(FMenuBuilder& MenuBuilder, const FName InToolId);`
- L80 _protected prototype_ `static EVisibility GetSidebarVisibility(const FName InToolId);`
- L83 _private member_ `static bool bFirstTimeSequencerCreated;`
- L85 _private member_ `FDelegateHandle SequencerCreatedHandle;`
- L88 _private member_ `TMap<FName, FEaseCurveToolInstance> ToolInstances;` — Registered Sequencer types to the tool instances

#### struct `UE::EaseCurveTool::FEaseCurveToolExtender::FEaseCurveToolInstance`  
`struct FEaseCurveToolInstance`  
_L57-68_
- L59 _public member_ `FName ToolId;`
- L61 _public member_ `TSharedPtr<FEaseCurveTool> Instance;`
- L63 _public member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L65 _public member_ `FDelegateHandle SequencerClosedHandle;`
- L67 _public member_ `TSharedPtr<FExtender> SidebarExtender;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API EASECURVETOOL_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurveToolModule.h` (Private)


#### class `FEaseCurveToolModule`  
`class FEaseCurveToolModule : public IModuleInterface`  
_L8-24_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private prototype_ `void RegisterContentBrowserExtender();`
- L18 _private prototype_ `void UnregisterContentBrowserExtender();`
- L20 _private prototype_ `void RegisterCurveEditorExtender();`
- L21 _private prototype_ `void UnregisterCurveEditorExtender();`
- L23 _private member_ `FDelegateHandle CurveEditorExtenderHandle;`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurveToolSettings.h` (Private)


#### class `UEaseCurveToolSettings`  
`class UEaseCurveToolSettings : public UDeveloperSettings`  
_L13-101_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, meta = (DisplayName = "Ease Curve Tool"))`
- inherits: `UDeveloperSettings`
- L18 _public prototype_ `UEaseCurveToolSettings();`
- L20 _public function_ `bool ShouldShowInSidebar() const`
- L21 _public function_ `void SetShowInSidebar(const bool bInSpawnInTabWindow)`
- L22 _public function_ `void ToggleShowInSidebar()`
- L24 _public function_ `bool IsToolVisible() const`
- L25 _public function_ `void SetToolVisible(const bool bInVisible)`
- L27 _public function_ `bool ShouldShowCurveEditorToolbar() const`
- L28 _public function_ `void SetShowCurveEditorToolbar(const bool bInShowCurveEditorToolbarButton)`
- L29 _public function_ `void ToggleShowCurveEditorToolbar()`
- L31 _public function_ `TObjectPtr<UEaseCurveLibrary> GetPresetLibrary() const`
- L32 _public function_ `void SetPresetLibrary(const TObjectPtr<UEaseCurveLibrary>& InWeakPresetLibrary)`
- L34 _public function_ `FText GetNewPresetCategory() const`
- L35 _public function_ `void SetNewPresetCategory(const FText& InNewPresetCategory)`
- L37 _public function_ `FString GetQuickEaseTangents() const`
- L38 _public function_ `void SetQuickEaseTangents(const FString& InTangents)`
- L40 _public function_ `int32 GetGraphSize() const`
- L41 _public function_ `void SetGraphSize(const int32 InSize)`
- L43 _public function_ `bool GetGridSnap() const`
- L44 _public function_ `void SetGridSnap(const bool bInGridSnap)`
- L45 _public function_ `void ToggleGridSnap()`
- L47 _public function_ `int32 GetGridSize() const`
- L48 _public function_ `void SetGridSize(const int32 InSize)`
- L50 _public function_ `bool GetAutoZoomToFit() const`
- L51 _public function_ `void SetAutoZoomToFit(const bool bInAutoZoomToFit)`
- L52 _public function_ `void ToggleAutoZoomToFit()`
- L54 _public function_ `bool GetAutoFlipTangents() const`
- L55 _public function_ `void SetAutoFlipTangents(const bool bInAutoFlipTangents)`
- L56 _public function_ `void ToggleAutoFlipTangents()`
- L61 _private member_ `bool bShowInSidebar = true;` — `UPROPERTY(Config, EditAnywhere, Category = "General")` — If true, displays the tool in the Sequencer sidebar drawer
- L65 _private member_ `bool bShowCurveEditorToolbarButton = false;` — `UPROPERTY(Config, EditAnywhere, Category = "General")` — If true, shows the ease curve combo button in the curve editor toolbar
- L68 _private member_ `bool bToolTabVisible = false;` — `UPROPERTY(Config)`
- L72 _private member_ `TSoftObjectPtr<UEaseCurveLibrary> DefaultPresetLibrary;` — `UPROPERTY(Config, EditAnywhere, Category = "General")` — The preset library to use by default and saved when a preset library is changed from a dropdown
- L76 _private member_ `FText NewPresetCategory;` — `UPROPERTY(Config, EditAnywhere, Category = "General")` — The name of the category to place newly created curve presets.
- L80 _private member_ `FString QuickEaseTangents;` — `UPROPERTY(Config, EditAnywhere, Category = "General")` — The tangents to apply for quick ease. Should be in the format of four comma-separated cubic bezier points. Ex. "0.45, 0.34, 0.0, 1.00"
- L84 _private member_ `int32 GraphSize = 140;` — `UPROPERTY(Config, EditAnywhere, Category = "Graph Editor", meta = (UIMin = 64, ClampMin = 64, UIMax = 256, ClampMax = 256, Delta = 1))` — The height of the curve ease tool in the details panel.
- L88 _private member_ `bool bGridSnap = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Graph Editor")` — If true, snaps tangents to grid.
- L92 _private member_ `int32 GridSize = 8;` — `UPROPERTY(Config, EditAnywhere, Category = "Graph Editor", meta = (UIMin = 4, ClampMin = 4, UIMax = 24, ClampMax = 24, Delta = 1))` — The height of the curve ease tool in the details panel.
- L96 _private member_ `bool bAutoZoomToFit = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Graph Editor")` — If true, will auto zoom the graph editor to fit the tangent handles after they have been changed.
- L100 _private member_ `bool bAutoFlipTangents = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Graph Editor")` — If true, auto flips tangents when sequential key frame curve values are descending.

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurveToolSidebarSection.h` (Private)


#### class `UE::EaseCurveTool::FEaseCurveToolSidebarSection`  
`class FEaseCurveToolSidebarSection : public ISidebarDrawerContent`  
_L16-34_
- inherits: `ISidebarDrawerContent`
- L19 _public member_ `static const FName UniqueId;`
- L21 _public prototype_ `FEaseCurveToolSidebarSection(const TSharedRef<ISequencer>& InSequencer);`
- L24 _public prototype_ `virtual FName GetUniqueId() const override;`
- L25 _public prototype_ `virtual FName GetSectionId() const override;`
- L26 _public prototype_ `virtual FText GetSectionDisplayText() const override;`
- L27 _public prototype_ `virtual bool ShouldShowSection() const override;`
- L28 _public prototype_ `virtual int32 GetSortOrder() const override;`
- L29 _public prototype_ `virtual TSharedRef<SWidget> CreateContentWidget() override;`
- L33 _protected member_ `TWeakPtr<ISequencer> WeakSequencer;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurveToolTab.h` (Private)


#### class `UE::EaseCurveTool::FEaseCurveToolTab`  
`class FEaseCurveToolTab : public TSharedFromThis<FEaseCurveToolTab>`  
_L19-65_
- inherits: `TSharedFromThis<FEaseCurveToolTab>`
- L22 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisibilityChanged, const bool );`
- L26 _public prototype_ `static FName StaticToolTabId(const ISequencer& InSequencer);` — @return Returns the auto generated tool tab id using the passed in ISequencer. Tool tab ids are based on the sequencer instance settings name.
- L28 _public prototype_ `FEaseCurveToolTab(FEaseCurveTool& InOwnerTool);`
- L30 _public prototype_ `void Init();`
- L31 _public prototype_ `void Shutdown();`
- L34 _public prototype_ `bool ShouldShowToolTab() const;` — @return True if the USequencerSettings setting for the tool is set to visible
- L37 _public prototype_ `bool IsToolTabVisible() const;` — @return True if the tool tab is visible
- L40 _public prototype_ `void ShowHideToolTab(const bool bInVisible);` — Shows or hides the tool tab and toggles the state in the saved settings
- L42 _public prototype_ `void ToggleToolTabVisible();`
- L44 _public function_ `FOnVisibilityChanged& OnVisibilityChanged()`
- L47 _protected prototype_ `TSharedPtr<IToolkitHost> GetToolkitHost() const;`
- L48 _protected prototype_ `TSharedPtr<FTabManager> GetTabManager() const;`
- L49 _protected prototype_ `USequencerSettings* GetSequencerSettings() const;`
- L51 _protected prototype_ `void RegisterToolTab();`
- L52 _protected prototype_ `void UnregisterToolTab();`
- L54 _protected prototype_ `TSharedRef<SDockTab> SpawnToolTab(const FSpawnTabArgs& InArgs);`
- L55 _protected prototype_ `void CloseToolTab();`
- L57 _protected member_ `FEaseCurveTool& OwnerTool;`
- L59 _protected member_ `FName ToolTabId;`
- L62 _protected member_ `bool bShuttingDown = false;` — State variable to help the dock tab know when it should save its visibility
- L64 _protected member_ `FOnVisibilityChanged VisibilityChangedDelegate;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace EaseCurveTool` (scope `UE`)
- L22 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnVisibilityChanged, const bool );`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/EaseCurveToolUtils.h` (Private)


#### class `UE::EaseCurveTool::FEaseCurveToolUtils`  
`class FEaseCurveToolUtils`  
_L19-34_
- L22 _public prototype_ `static UEaseCurveLibrary* GetToolPresetLibrary(const TWeakPtr<FEaseCurveTool>& InWeakTool);`
- L25 _public prototype_ `static bool CompareCurveEditorSelections(const FCurveEditorSelection& InSelectionA, const FCurveEditorSelection& InSelectionB);` — Returns True if the curve editor selections match
- L27 _public prototype_ `static TSharedPtr<FCurveEditor> GetCurveEditorFromSequencer(const TSharedRef<ISequencer>& InSequencer);`
- L29 _public prototype_ `static bool FindChannelHandleFromCurveModel(const FCurveModel& InCurveModel, FMovieSceneChannelHandle& OutChannelHandle);`
- L31 _public prototype_ `static bool HasWeightedBrokenTangents(const FRichCurveKey& InKey);`
- L32 _public prototype_ `static bool HasWeightedBrokenTangents(const FMovieSceneDoubleValue& InValue);`
- L33 _public prototype_ `static bool HasWeightedBrokenTangents(const FMovieSceneFloatValue& InValue);`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Menus/CurveEditorToolBarMenu.h` (Private)


#### class `UE::EaseCurveTool::FCurveEditorToolBarMenu`  
`class FCurveEditorToolBarMenu : public TSharedFromThis<FCurveEditorToolBarMenu>`  
_L19-38_
- inherits: `TSharedFromThis<FCurveEditorToolBarMenu>`
- L22 _public member_ `static const FName MenuName;`
- L24 _public prototype_ `FCurveEditorToolBarMenu(const TWeakPtr<FEaseCurveTool>& InWeakTool);`
- L26 _public prototype_ `TSharedRef<SWidget> GenerateWidget();`
- L29 _protected prototype_ `void PopulateMenu(UToolMenu* const InMenu);`
- L31 _protected prototype_ `FFrameRate GetDisplayRate() const;`
- L32 _protected prototype_ `void HandlePresetChanged(const TSharedPtr<FEaseCurvePreset>& InPreset);`
- L33 _protected prototype_ `void HandleQuickPresetChanged(const TSharedPtr<FEaseCurvePreset>& InPreset);`
- L35 _protected prototype_ `EVisibility GetVisibilityForLibrary() const;`
- L37 _protected member_ `TWeakPtr<FEaseCurveTool> WeakTool;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Menus/EaseCurveLibraryMenu.h` (Private)


#### class `UE::EaseCurveTool::FEaseCurveLibraryMenu`  
`class FEaseCurveLibraryMenu : public TSharedFromThis<FEaseCurveLibraryMenu>`  
_L19-46_
- inherits: `TSharedFromThis<FEaseCurveLibraryMenu>`
- L22 _public prototype_ `static void RegisterMenus();`
- L23 _public prototype_ `static void UnregisterMenus();`
- L26 _protected prototype_ `static void AddMenuImportExportSection(FToolMenuSection& InSection);`
- L28 _protected prototype_ `static void AddMenuEntryForNoSerializers(FMenuBuilder& InMenuBuilder);`
- L30 _protected prototype_ `static bool AddMenuEntryForSerializer(FMenuBuilder& InMenuBuilder , UEaseCurveSerializer& InSerializer , const bool bInImport , const TSet<TWeakObjectPtr<UEaseCurveLibrary>> InWeakLibraryAssets);`
- L35 _protected prototype_ `static void PopulateImportMenu(FMenuBuilder& InMenuBuilder , const TSet<TWeakObjectPtr<UEaseCurveLibrary>> InWeakLibraryAssets);`
- L37 _protected prototype_ `static void PopulateExportMenu(FMenuBuilder& InMenuBuilder , const TSet<TWeakObjectPtr<UEaseCurveLibrary>> InWeakLibraryAssets);`
- L40 _protected prototype_ `static void PromptForImport(UEaseCurveSerializer* const InSerializer , const TSet<TWeakObjectPtr<UEaseCurveLibrary>> InWeakLibraryAssets);`
- L42 _protected prototype_ `static void PromptForExport(UEaseCurveSerializer* const InSerializer , const TSet<TWeakObjectPtr<UEaseCurveLibrary>> InWeakLibraryAssets);`
- L45 _protected prototype_ `static void SetToDefaultPresets(const TSet<TWeakObjectPtr<UEaseCurveLibrary>> InWeakLibraryAssets);`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Menus/EaseCurveToolContextMenu.h` (Private)


#### class `UE::EaseCurveTool::FEaseCurveToolContextMenu`  
`class FEaseCurveToolContextMenu : public TSharedFromThis<FEaseCurveToolContextMenu>`  
_L17-32_
- inherits: `TSharedFromThis<FEaseCurveToolContextMenu>`
- L20 _public prototype_ `FEaseCurveToolContextMenu(const TWeakPtr<FUICommandList>& InCommandListWeak, const FEaseCurveToolOnGraphSizeChanged& InOnGraphSizeChanged);`
- L22 _public prototype_ `TSharedRef<SWidget> GenerateWidget();`
- L25 _protected prototype_ `void PopulateContextMenuSettings(UToolMenu* const InToolMenu);`
- L27 _protected member_ `TWeakPtr<FUICommandList> CommandListWeak;`
- L29 _protected member_ `FEaseCurveToolOnGraphSizeChanged OnGraphSizeChanged;`
- L31 _protected member_ `int32 GraphSize;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace EaseCurveTool` (scope `UE`)
- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FEaseCurveToolOnGraphSizeChanged, const int32 ) class FEaseCurveToolContextMenu : public TSharedFromThis<FEaseCurveToolContextMenu> { public: FEaseCurveToolContextMenu(const TWeakPtr<FUICommandList>& InCommandListWeak, const FEaseCurveToolOnGraphSizeChanged& InOnGraphSizeChanged); TSharedRef<SWidget> GenerateWidget(); protected: void PopulateContextMenuSettings(UToolMenu* const InToolMenu); TWeakPtr<FUICommandList> CommandListWeak; FEaseCurveToolOnGraphSizeChanged OnGraphSizeChanged; int32 GraphSize; };`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Menus/EaseCurveToolMenuContext.h` (Private)


#### class `UEaseCurveToolMenuContext`  
`class UEaseCurveToolMenuContext : public UObject`  
_L12-32_
- reflection: `UCLASS()`
- inherits: `UObject`
- L17 _public function_ `void Init(const TWeakPtr<UE::EaseCurveTool::FEaseCurveTool>& InWeakTool)`
- L22 _public function_ `TSharedPtr<UE::EaseCurveTool::FEaseCurveTool> GetTool() const`
- L27 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPopulateMenu, UToolMenu*);`
- L28 _public member_ `FOnPopulateMenu OnPopulateMenu;`
- L31 _protected member_ `TWeakPtr<UE::EaseCurveTool::FEaseCurveTool> WeakTool;`

#### Free symbols / members of external scopes

- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPopulateMenu, UToolMenu*);`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Serializers/CubicBezierCurveSerializer.h` (Private)


#### class `UCubicBezierCurveSerializer`  
`class UCubicBezierCurveSerializer : public UEaseCurveSerializer`  
_L17-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEaseCurveSerializer`
- desc: Serializes cubic bezier coordinates to cubic hermite
- L24 _public prototype_ `virtual FText GetDisplayName() const override;`
- L25 _public prototype_ `virtual FText GetDisplayTooltip() const override;`
- L27 _public prototype_ `virtual bool IsFileExport() const override;`
- L28 _public prototype_ `virtual bool SupportsExport() const override;`
- L29 _public prototype_ `virtual bool Export(const FString& InFilePath, TSet<TWeakObjectPtr<UEaseCurveLibrary>> InWeakLibraries) override;`
- L31 _public prototype_ `virtual bool IsFileImport() const override;`
- L32 _public prototype_ `virtual bool SupportsImport() const override;`
- L33 _public prototype_ `virtual bool Import(const FString& InFilePath, TSet<TWeakObjectPtr<UEaseCurveLibrary>> InWeakLibraries) override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API EASECURVETOOL_API`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Serializers/CubicBezierPointEntryDialog.h` (Private)


#### class `UE::EaseCurveTool::FCubicBezierPointEntryDialog`  
`class FCubicBezierPointEntryDialog : public TSharedFromThis<FCubicBezierPointEntryDialog>`  
_L22-63_
- inherits: `TSharedFromThis<FCubicBezierPointEntryDialog>`
- L25 _public prototype_ `static bool Prompt(const TSet<TWeakObjectPtr<UEaseCurveLibrary>>& InWeakLibraries);`
- L28 _protected prototype_ `TSharedRef<SWidget> ConstructLabel(const FText& InLabel);`
- L29 _protected prototype_ `TSharedRef<SWidget> BuildContent();`
- L31 _protected prototype_ `bool CanAdd() const;`
- L33 _protected prototype_ `FReply HandleAddButtonClick();`
- L34 _protected prototype_ `FReply HandleCloseButtonClick();`
- L36 _protected prototype_ `void ForEachLibrary(const TFunction<bool(UEaseCurveLibrary*)> InFunctor) const;`
- L38 _protected prototype_ `void SetStatus(const FSlateColor& InColor = FStyleColors::Foreground, const FText& InText = FText::GetEmpty()) const;`
- L40 _protected prototype_ `FText GetDefaultCategoryName() const;`
- L44 _protected prototype_ `FText GetNewCategoryName() const;` — @return The current selected category name. If the category dropdown is set to "(Default)", this will return the default category from the tool settings.
- L46 _protected prototype_ `void ResetDialog();`
- L48 _protected member_ `TSet<TWeakObjectPtr<UEaseCurveLibrary>> WeakLibraries;`
- L50 _protected member_ `TSharedPtr<SWindow> Window;`
- L52 _protected member_ `bool bHasAdded = false;`
- L54 _protected member_ `FText NewCategoryName;`
- L55 _protected member_ `FText NewPresetName;`
- L57 _protected member_ `FVector2d Point1 = FVector2d::ZeroVector;`
- L58 _protected member_ `FVector2d Point2 = FVector2d::ZeroVector;`
- L60 _protected member_ `mutable FSlateColor StatusColor;`
- L61 _protected member_ `mutable FText StatusText;`
- L62 _protected member_ `bool bLastAddedSuccessfully = false;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Widgets/SEaseCurveAddNew.h` (Private)


#### class `UE::EaseCurveTool::SEaseCurveAddNew`  
`class SEaseCurveAddNew : public SCompoundWidget`  
_L16-41_
- inherits: `SCompoundWidget`
- L19 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnGetNewPresetTangents, FEaseCurveTangents& ) SLATE_BEGIN_ARGS(SEaseCurveAddNew)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FEaseCurveTool>& InTool);`
- L27 _protected prototype_ `bool IsButtonEnabled() const;`
- L29 _protected prototype_ `FReply OnCreateNewPresetClick();`
- L30 _protected prototype_ `FReply OnCancelNewPresetClick();`
- L32 _protected prototype_ `FReply OnNewPresetKeyDownHandler(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);`
- L33 _protected prototype_ `void OnNewPresetTextCommitted(const FText& InNewText, ETextCommit::Type InCommitType);`
- L35 _protected member_ `TWeakPtr<FEaseCurveTool> WeakTool;`
- L37 _protected member_ `TSharedPtr<SButton> NewPresetButton;`
- L38 _protected member_ `TSharedPtr<SEditableTextBox> NewPresetNameTextBox;`
- L40 _protected member_ `bool bIsCreatingNewPreset = false;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace EaseCurveTool` (scope `UE`)
- L19 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnGetNewPresetTangents, FEaseCurveTangents& ) SLATE_BEGIN_ARGS(SEaseCurveAddNew) {} SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FEaseCurveTool>& InTool);`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Widgets/SEaseCurveCategoryComboBox.h` (Private)


#### class `UE::EaseCurveTool::SEaseCurveCategoryComboBox`  
`class SEaseCurveCategoryComboBox : public SCompoundWidget`  
_L14-41_
- inherits: `SCompoundWidget`
- desc: A combo box widget to display and select a category from a list of all categories that exist inside a library
- L17 _public function_ `DECLARE_DELEGATE_TwoParams(FOnCategoryChanged, const FText& , const ESelectInfo::Type ) SLATE_BEGIN_ARGS(SEaseCurveCategoryComboBox)`
- L20 _public prototype_ `SLATE_ARGUMENT(bool, UseDefault) SLATE_EVENT(FOnCategoryChanged, OnChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakObjectPtr<UEaseCurveLibrary>& InWeakLibrary);`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, const TSet<TWeakObjectPtr<UEaseCurveLibrary>>& InWeakLibraries);`
- L27 _public prototype_ `FText GetSelectedCategory() const;`
- L30 _protected prototype_ `TSharedPtr<FText> GetSelectedCategoryItem() const;`
- L31 _protected prototype_ `void HandleCategoryChanged(const TSharedPtr<FText> InNewCategory, const ESelectInfo::Type InSelectInfo);`
- L33 _protected member_ `TSet<TWeakObjectPtr<UEaseCurveLibrary>> WeakLibraries;`
- L35 _protected member_ `FOnCategoryChanged OnCategoryChanged;`
- L37 _protected member_ `TArray<TSharedPtr<FText>> AllCategories;`
- L39 _protected member_ `TSharedPtr<FText> DefaultCategory;`
- L40 _protected member_ `TSharedPtr<FText> SelectedCategory;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace EaseCurveTool` (scope `UE`)
- L17 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnCategoryChanged, const FText& , const ESelectInfo::Type ) SLATE_BEGIN_ARGS(SEaseCurveCategoryComboBox) {} SLATE_ARGUMENT(bool, UseDefault) SLATE_EVENT(FOnCategoryChanged, OnChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakObjectPtr<UEaseCurveLibrary>& InWeakLibrary);`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Widgets/SEaseCurveEditor.h` (Private)


#### class `UE::EaseCurveTool::SEaseCurveEditor`  
`class SEaseCurveEditor : public SCompoundWidget, public FGCObject, public FEditorUndoClient`  
_L27-333_
- inherits: `SCompoundWidget,FGCObject,FEditorUndoClient`
- L33 _public function_ `SLATE_BEGIN_ARGS(SEaseCurveEditor) : _DisplayRate(FFrameRate(30, 1)) , _ShowInputGridNumbers(true) , _ShowOutputGridNumbers(true) , _NormalAreaColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.05f)) , _NormalBoundsColor(FLinearColor(0.4f, 0.4f, 0.4f, 1.0f)) , _GridSnap(false) , _GridColor(FLinearColor(0.1f, 0.1f, 0.1f, 0.1f)) , _ExtendedGridColor(FLinearColor(0.02f, 0.02f, 0.02f, 0.5f)) , _CurveThickness(2.5f) , _CurveColor(FLinearColor::White)`
- L47 _public prototype_ `SLATE_ATTRIBUTE(TOptional<float>, DataMinInput) SLATE_ATTRIBUTE(TOptional<float>, DataMaxInput) SLATE_ATTRIBUTE(TOptional<FVector2D>, DesiredSize) SLATE_ATTRIBUTE(FFrameRate, DisplayRate) SLATE_ARGUMENT(bool, ShowInputGridNumbers) SLATE_ARGUMENT(bool, ShowOutputGridNumbers) SLATE_ARGUMENT(FLinearColor, NormalAreaColor) SLATE_ARGUMENT(FLinearColor, NormalBoundsColor) SLATE_ATTRIBUTE(bool, GridSnap) SLATE_ATTRIBUTE(int32, GridSize) SLATE_ARGUMENT(FLinearColor, GridColor) SLATE_ARGUMENT(FLinearColor, ExtendedGridColor) SLATE_ARGUMENT(float, CurveThickness) SLATE_ARGUMENT(FLinearColor, CurveColor) SLATE_ATTRIBUTE(EEaseCurveToolOperation, Operation) SLATE_ATTRIBUTE(bool, CanEditCurve) SLATE_ATTRIBUTE(TOptional<FText>, ErrorMessage) SLATE_ATTRIBUTE(FText, StartText) SLATE_ATTRIBUTE(FText, StartTooltipText) SLATE_ATTRIBUTE(FText, EndText) SLATE_ATTRIBUTE(FText, EndTooltipText) SLATE_EVENT(FOnEaseCurveChanged, OnTangentsChanged) SLATE_EVENT(FOnGetContent, GetContextMenuContent) SLATE_EVENT(FOnKeyDown, OnKeyDown) SLATE_EVENT(FSimpleDelegate, OnDragStart) SLATE_EVENT(FSimpleDelegate, OnDragEnd) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FEaseCurveTool>& InTool);`
- L85 _public prototype_ `static FVector2d CalcTangentDir(const double InTangent);`
- L86 _public prototype_ `static float CalcTangent(const FVector2d& InHandleDelta);`
- L88 _public prototype_ `void ZoomToFit();`
- L91 _public prototype_ `void SetRequireFocusToZoom(const bool bInRequireFocusToZoom);` — Set flag that allows scrolling up/down over the widget from the outside without it handling the scroll wheel event.
- L93 _public function_ `FKeyHandle GetSelectedKeyHandle() const`
- L95 _public prototype_ `bool HasDrawErrorMessage() const;`
- L96 _public prototype_ `bool CanEditCurve() const;`
- L141 _protected prototype_ `FVector2d GetArriveTangentScreenLocation(const FTrackScaleInfo& InScaleInfo, const FKeyHandle& InKeyHandle) const;`
- L142 _protected prototype_ `FVector2d GetArriveTangentScreenLocation(const FTrackScaleInfo& InScaleInfo , const FVector2d& InKeyPosition, const float InTangent, const float InWeight) const;`
- L145 _protected prototype_ `FVector2d GetLeaveTangentScreenLocation(const FTrackScaleInfo& InScaleInfo, const FKeyHandle& InKeyHandle) const;`
- L146 _protected prototype_ `FVector2d GetLeaveTangentScreenLocation(const FTrackScaleInfo& InScaleInfo , const FVector2d& InKeyPosition, const float InTangent, const float InWeight) const;`
- L149 _protected prototype_ `void ClearSelection();`
- L151 _protected prototype_ `int32 PaintGrid(const FTrackScaleInfo& InScaleInfo , const FGeometry& InGeometry , FSlateWindowElementList& OutDrawElements , int32 InLayerId , const FSlateRect& InMyCullingRect , const ESlateDrawEffect InDrawEffects) const;`
- L158 _protected prototype_ `void PaintNormalBounds(const FTrackScaleInfo& InScaleInfo , const FGeometry& InGeometry , FSlateWindowElementList& OutDrawElements , int32 InLayerId , const FSlateRect& InMyCullingRect , const ESlateDrawEffect InDrawEffects , const FWidgetStyle& InWidgetStyle) const;`
- L166 _protected prototype_ `void PaintCurve(const FTrackScaleInfo& InScaleInfo , const FGeometry& InGeometry , FSlateWindowElementList& OutDrawElements , int32 LayerId , const FSlateRect& MyCullingRect , const ESlateDrawEffect DrawEffects , const FWidgetStyle& InWidgetStyle) const;`
- L174 _protected prototype_ `int32 PaintKeys(const FTrackScaleInfo& InScaleInfo , const FGeometry& InGeometry , FSlateWindowElementList& OutDrawElements , int32 InLayerId , const ESlateDrawEffect InDrawEffects , const FWidgetStyle& InWidgetStyle) const;`
- L181 _protected prototype_ `int32 PaintTangentHandle(const FGeometry& InGeometry , FSlateWindowElementList& OutDrawElements , int32 InLayerId , const ESlateDrawEffect InDrawEffects , const FWidgetStyle& InWidgetStyle , const FVector2D& InKeyLocation , const FVector2D& InTangentLocation , const bool bInSelected) const;`
- L190 _protected prototype_ `int32 PaintSelectionText(const FTrackScaleInfo& InScaleInfo , const FGeometry& InGeometry , FSlateWindowElementList& OutDrawElements , int32 InLayerId , const ESlateDrawEffect InDrawEffects) const;`
- L197 _protected prototype_ `virtual void PostUndo(const bool bInSuccess) override;`
- L198 _protected prototype_ `virtual void PostRedo(const bool bInSuccess) override;`
- L202 _protected prototype_ `virtual FString GetReferencerName() const override;`
- L203 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L207 _protected function_ `virtual bool SupportsKeyboardFocus() const override`
- L208 _protected prototype_ `virtual FVector2D ComputeDesiredSize(const float InLayoutScaleMultiplier) const override;`
- L210 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L211 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L212 _protected prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L213 _protected prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L214 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L215 _protected prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L217 _protected prototype_ `virtual TOptional<bool> OnQueryShowFocus(const EFocusCause InFocusCause) const override;`
- L219 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs , const FGeometry& InGeometry , const FSlateRect& InCullingRect , FSlateWindowElementList& OutDrawElements , int32 InLayerId , const FWidgetStyle& InWidgetStyle , const bool bInParentEnabled) const override;`
- L228 _protected prototype_ `void TryStartDrag(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L229 _protected prototype_ `void ProcessDrag(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L230 _protected prototype_ `void EndDrag(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L232 _protected prototype_ `void ProcessClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L234 _protected prototype_ `void ZoomView(const FVector2D& InDelta);`
- L237 _protected prototype_ `void CreateLinesForSegment(const ERichCurveInterpMode InInterpMode , const ERichCurveTangentMode InTangentMode , const TPair<float, float>& InStartKeyTimeValue, const TPair<float, float>& InEndKeyTimeValue , TArray<FVector2D>& OutLinePoints, TArray<FLinearColor>& OutLineColors , const FTrackScaleInfo& InScaleInfo) const;` — Generates the line(s) for rendering between KeyIndex and the following key.
- L243 _protected prototype_ `void MoveSelectedTangent(const FTrackScaleInfo& InScaleInfo, const FVector2D& InScreenDelta);`
- L245 _protected prototype_ `FVector2D SnapLocation(const FVector2D& InLocation) const;`
- L247 _protected prototype_ `FText GetCurveToolTipInputText() const;`
- L248 _protected prototype_ `FText GetCurveToolTipOutputText() const;`
- L250 _protected prototype_ `TSharedRef<IToolTip> CreateCurveToolTip();`
- L251 _protected prototype_ `void UpdateCurveToolTip(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L253 _protected prototype_ `void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);`
- L256 _protected prototype_ `virtual void SetDefaultOutput(const float InMinZoomRange);` — Set Default output values when range is too small
- L258 _protected prototype_ `void SetInputMinMax(const float InNewMin, const float InNewMax);`
- L259 _protected prototype_ `void SetOutputMinMax(const float InNewMin, const float InNewMax);`
- L261 _protected prototype_ `bool HitTestCurves(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) const;`
- L262 _protected prototype_ `FSelectedTangent HitTestTangentHandles(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) const;`
- L263 _protected prototype_ `bool HitTestKey(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent, const FVector2D& InInputPosition) const;`
- L265 _protected member_ `TSharedPtr<FEaseCurveTool> Tool;`
- L266 _protected member_ `TObjectPtr<UEaseCurve> EaseCurve;`
- L269 _protected member_ `TAttribute<TOptional<float>> DataMinInput;` — Minimum/Maximum input of data range
- L270 _protected member_ `TAttribute<TOptional<float>> DataMaxInput;`
- L272 _protected member_ `TAttribute<TOptional<FVector2D>> DesiredSize;`
- L273 _protected member_ `TAttribute<FFrameRate> DisplayRate;`
- L275 _protected member_ `bool bShowInputGridNumbers = false;`
- L276 _protected member_ `bool bShowOutputGridNumbers = false;`
- L278 _protected member_ `FLinearColor NormalAreaColor = FLinearColor::White;`
- L279 _protected member_ `FLinearColor NormalBoundsColor = FLinearColor::White;`
- L280 _protected member_ `TAttribute<bool> bGridSnap;`
- L281 _protected member_ `TAttribute<int32> GridSize;`
- L282 _protected member_ `FLinearColor GridColor = FLinearColor::White;`
- L283 _protected member_ `FLinearColor ExtendedGridColor = FLinearColor::White;`
- L284 _protected member_ `float CurveThickness = 1.f;`
- L285 _protected member_ `FLinearColor CurveColor = FLinearColor::White;`
- L286 _protected member_ `TAttribute<EEaseCurveToolOperation> Operation;`
- L288 _protected member_ `TAttribute<bool> bCanEditCurve;`
- L289 _protected member_ `TAttribute<TOptional<FText>> ErrorMessage;`
- L291 _protected member_ `TAttribute<FText> StartText;`
- L292 _protected member_ `TAttribute<FText> StartTooltipText;`
- L293 _protected member_ `TAttribute<FText> EndText;`
- L294 _protected member_ `TAttribute<FText> EndTooltipText;`
- L296 _protected member_ `FOnEaseCurveChanged OnTangentsChanged;`
- L297 _protected member_ `FOnGetContent GetContextMenuContent;`
- L298 _protected member_ `FOnKeyDown OnKeyDownEvent;`
- L299 _protected member_ `FSimpleDelegate OnDragStart;`
- L300 _protected member_ `FSimpleDelegate OnDragEnd;`
- L302 _protected member_ `float ViewMinInput = 0.f;`
- L303 _protected member_ `float ViewMaxInput = 1.f;`
- L304 _protected member_ `float ViewMinOutput = 0.f;`
- L305 _protected member_ `float ViewMaxOutput = 1.f;`
- L307 _protected member_ `FVector2D MouseDownLocation = FVector2D::ZeroVector;`
- L308 _protected member_ `FVector2D MouseMoveLocation = FVector2D::ZeroVector;`
- L310 _protected member_ `EDragState DragState = EDragState::None;`
- L312 _protected member_ `float DragThreshold = 4.f;` — The number of pixels which the mouse must move before a drag operation starts.
- L314 _protected member_ `FKeyHandle DraggedKeyHandle;` — A handle to the key which was clicked to start a key drag operation.
- L317 _protected member_ `FEaseCurveTangents PreDragTangents;` — Tangent values at the beginning of a drag operation.
- L319 _protected member_ `TSharedPtr<IToolTip> CurveToolTip;`
- L320 _protected member_ `int8 ToolTipIndex = INDEX_NONE;`
- L322 _protected member_ `FText CurveToolTipInputText;`
- L323 _protected member_ `FText CurveToolTipOutputText;`
- L325 _protected member_ `FEaseCurveTangents MovingTangents;`
- L326 _protected member_ `FEaseCurveTangents LockTangents;`
- L328 _protected member_ `bool bDraggingToolSizeValue = false;`
- L330 _protected member_ `FSelectedTangent SelectedTangent;`
- L332 _protected member_ `bool bRequireFocusToZoom = false;`

#### enum `UE::EaseCurveTool::SEaseCurveEditor::EDragState`  
`enum class EDragState`  
_L100-114_
- desc: Represents the different states of a drag operation
- L103 _public enumerator_ `None` — There is no active drag operation.
- L105 _public enumerator_ `PreDrag` — The user has clicked a mouse button, but has not moved more then the drag threshold.
- L107 _public enumerator_ `DragTangent` — The user is dragging a selected tangent handle.
- L109 _public enumerator_ `MarqueeSelect` — The user is performing a marquee selection of keys.
- L111 _public enumerator_ `Pan` — The user is panning the curve view.
- L113 _public enumerator_ `Zoom` — The user is zooming the curve view.

#### struct `UE::EaseCurveTool::SEaseCurveEditor::FSelectedTangent`  
`struct FSelectedTangent`  
_L116-139_
- L118 _public function_ `FSelectedTangent() : KeyHandle(FKeyHandle::Invalid()), bIsArrival(false)`
- L121 _public function_ `FSelectedTangent(const FKeyHandle InKey, const bool bInIsArrival) : KeyHandle(InKey), bIsArrival(bInIsArrival)`
- L125 _public function_ `bool operator == (const FSelectedTangent& InOther) const`
- L130 _public function_ `bool IsValid() const`
- L135 _public member_ `FKeyHandle KeyHandle;`
- L138 _public member_ `bool bIsArrival;` — Indicates if it is the arrival tangent, or the leave tangent

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace EaseCurveTool` (scope `UE`)
- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnEaseCurveChanged, const FEaseCurveTangents& ) class SEaseCurveEditor : public SCompoundWidget, public FGCObject, public FEditorUndoClient { public: SLATE_BEGIN_ARGS(SEaseCurveEditor) : _DisplayRate(FFrameRate(30, 1)) , _ShowInputGridNumbers(true) , _ShowOutputGridNumbers(true) , _NormalAreaColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.05f)) , _NormalBoundsColor(FLinearColor(0.4f, 0.4f, 0.4f, 1.0f)) , _GridSnap(false) , _GridColor(FLinearColor(0.1f, 0.1f, 0.1f, 0.1f)) , _ExtendedGridColor(FLinearColor(0.02f, 0.02f, 0.02f, 0.5f)) , _CurveThickness(2.5f) , _CurveColor(FLinearColor::White) { _Clipping = EWidgetClipping::ClipToBounds; } SLATE_ATTRIBUTE(TOptional<float>, DataMinInput) SLATE_ATTRIBUTE(TOptional<float>, DataMaxInput) SLATE_ATTRIBUTE(TOptional<FVector2D>, DesiredSize) SLATE_ATTRIBUTE(FFrameRate, DisplayRate) SLATE_ARGUMENT(bool, ShowInputGridNumbers) SLATE_ARGUMENT(bool, ShowOutputGridNumbers) SLATE_ARGUMENT(FLinearColor, NormalAreaColor) SLATE_ARGUMENT(FLinearColor, NormalBoundsColor) SLATE_ATTRIBUTE(bool, GridSnap) SLATE_ATTRIBUTE(int32, GridSize) SLATE_ARGUMENT(FLinearColor, GridColor) SLATE_ARGUMENT(FLinearColor, ExtendedGridColor) SLATE_ARGUMENT(float, CurveThickness) SLATE_ARGUMENT(FLinearColor, CurveColor) SLATE_ATTRIBUTE(EEaseCurveToolOperation, Operation)`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Widgets/SEaseCurveLibraryComboBox.h` (Private)


#### class `UE::EaseCurveTool::SEaseCurveLibraryComboBox`  
`class SEaseCurveLibraryComboBox : public SCompoundWidget`  
_L14-33_
- inherits: `SCompoundWidget`
- desc: A combo box widget for editing the preset library of an Ease Curve Tool instance
- L17 _public function_ `SLATE_BEGIN_ARGS(SEaseCurveLibraryComboBox)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FEaseCurveTool>& InTool);`
- L24 _protected prototype_ `FString GetSelectedPath() const;`
- L25 _protected prototype_ `void HandleLibrarySelected(const FAssetData& InAssetData);`
- L27 _protected prototype_ `EVisibility GetOpenTabButtonVisibility() const;`
- L28 _protected prototype_ `FReply OpenEaseCurveToolTab();`
- L30 _protected member_ `TWeakPtr<FEaseCurveTool> WeakTool;`
- L32 _protected member_ `TStrongObjectPtr<UEaseCurveLibraryFactory> PresetLibraryFactory;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Widgets/SEaseCurvePreset.h` (Private)


#### class `UE::EaseCurveTool::SEaseCurvePreset`  
`class SEaseCurvePreset : public SCompoundWidget`  
_L19-67_
- inherits: `SCompoundWidget`
- L22 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnGetNewPresetTangents, FEaseCurveTangents& ) SLATE_BEGIN_ARGS(SEaseCurvePreset) : _DisplayRate(FFrameRate(30, 1))`
- L28 _public prototype_ `SLATE_ATTRIBUTE(FFrameRate, DisplayRate) SLATE_EVENT(FOnPresetChanged, OnPresetChanged) SLATE_EVENT(FOnPresetChanged, OnQuickPresetChanged) SLATE_EVENT(FOnGetNewPresetTangents, OnGetNewPresetTangents) SLATE_END_ARGS() virtual ~SEaseCurvePreset() override;` — Display rate used to draw the ease curve preview.
- L36 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FEaseCurveTool>& InTool);`
- L38 _public prototype_ `void ClearSelection();`
- L40 _public prototype_ `bool SetSelectedItem(const FEaseCurvePresetHandle& InPresetHandle);`
- L41 _public prototype_ `bool SetSelectedItem(const FEaseCurveTangents& InTangents);`
- L44 _protected prototype_ `void HandleLibraryChanged(const TWeakObjectPtr<UEaseCurveLibrary> InWeakLibrary);`
- L46 _protected prototype_ `void HandlePresetChanged();`
- L48 _protected prototype_ `FReply OnCreateNewPresetClick();`
- L49 _protected prototype_ `FReply OnCancelNewPresetClick();`
- L51 _protected prototype_ `FReply OnNewPresetKeyDownHandler(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);`
- L52 _protected prototype_ `void OnNewPresetTextCommitted(const FText& InNewText, ETextCommit::Type InCommitType);`
- L54 _protected member_ `TWeakPtr<FEaseCurveTool> WeakTool;`
- L56 _protected member_ `TAttribute<FFrameRate> DisplayRate;`
- L57 _protected member_ `FOnPresetChanged OnPresetChanged;`
- L58 _protected member_ `FOnPresetChanged OnQuickPresetChanged;`
- L59 _protected member_ `FOnGetNewPresetTangents OnGetNewPresetTangents;`
- L61 _protected member_ `TSharedPtr<SEaseCurvePresetComboBox> PresetComboBox;`
- L62 _protected member_ `TSharedPtr<SEditableTextBox> NewPresetNameTextBox;`
- L64 _protected member_ `bool bIsCreatingNewPreset = false;`
- L66 _protected member_ `TWeakObjectPtr<UEaseCurveLibrary> WeakCurrentLibrary;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace EaseCurveTool` (scope `UE`)
- L22 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnGetNewPresetTangents, FEaseCurveTangents& ) SLATE_BEGIN_ARGS(SEaseCurvePreset) : _DisplayRate(FFrameRate(30, 1)) {} SLATE_ATTRIBUTE(FFrameRate, DisplayRate) SLATE_EVENT(FOnPresetChanged, OnPresetChanged) SLATE_EVENT(FOnPresetChanged, OnQuickPresetChanged) SLATE_EVENT(FOnGetNewPresetTangents, OnGetNewPresetTangents) SLATE_END_ARGS() virtual ~SEaseCurvePreset() override;`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Widgets/SEaseCurvePresetComboBox.h` (Private)


#### class `UE::EaseCurveTool::SEaseCurvePresetComboBox`  
`class SEaseCurvePresetComboBox : public SCompoundWidget`  
_L20-70_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS(SEaseCurvePresetComboBox) : _DisplayRate(FFrameRate(30, 1)) , _AllowEditMode(true)`
- L27 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<UEaseCurveLibrary>, Library) SLATE_ATTRIBUTE(FFrameRate, DisplayRate) SLATE_ARGUMENT(bool, AllowEditMode) SLATE_EVENT(FOnPresetChanged, OnPresetChanged) SLATE_EVENT(FOnPresetChanged, OnQuickPresetChanged) SLATE_END_ARGS() virtual ~SEaseCurvePresetComboBox() override;`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FEaseCurveTool>& InTool);`
- L39 _public prototype_ `bool HasSelection() const;`
- L41 _public prototype_ `void ClearSelection();`
- L43 _public prototype_ `bool GetSelectedItem(FEaseCurvePreset& OutPreset) const;`
- L45 _public prototype_ `bool SetSelectedItem(const FEaseCurvePresetHandle& InPresetHandle);`
- L46 _public prototype_ `bool SetSelectedItem(const FEaseCurveTangents& InTangents);`
- L48 _public prototype_ `void Reload();`
- L51 _protected prototype_ `void HandlePresetLibraryChanged(const TWeakObjectPtr<UEaseCurveLibrary> InLibrary);`
- L53 _protected prototype_ `TSharedRef<SWidget> GeneratePresetDropdown();`
- L55 _protected prototype_ `void HandlePresetChanged(const TSharedPtr<FEaseCurvePreset>& InPreset);`
- L57 _protected prototype_ `void GenerateSelectedRowWidget();`
- L59 _protected member_ `TWeakPtr<FEaseCurveTool> WeakTool;`
- L61 _protected member_ `TAttribute<FFrameRate> DisplayRate;`
- L62 _protected member_ `bool bAllowEditMode = false;`
- L63 _protected member_ `FOnPresetChanged OnPresetChanged;`
- L64 _protected member_ `FOnPresetChanged OnQuickPresetChanged;`
- L66 _protected member_ `TSharedPtr<SEaseCurvePresetList> PresetList;`
- L67 _protected member_ `TSharedPtr<SBox> SelectedRowContainer;`
- L69 _protected member_ `TSharedPtr<FEaseCurvePreset> SelectedItem;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Widgets/SEaseCurvePresetGroup.h` (Private)


#### class `UE::EaseCurveTool::SEaseCurvePresetGroup`  
`class SEaseCurvePresetGroup : public SCompoundWidget`  
_L19-107_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SEaseCurvePresetGroup) : _DisplayRate(FFrameRate(30, 1))`
- L25 _public prototype_ `SLATE_ARGUMENT(FText, CategoryName) SLATE_ARGUMENT(TArray<TSharedPtr<FEaseCurvePreset>>, Presets) SLATE_ATTRIBUTE(TSharedPtr<FEaseCurvePreset>, SelectedPreset) SLATE_ARGUMENT(FText, SearchText) SLATE_ATTRIBUTE(bool, IsEditMode) SLATE_ARGUMENT(FFrameRate, DisplayRate) SLATE_EVENT(FEaseCurveCategoryDeleteDelegate, OnCategoryDelete) SLATE_EVENT(FEaseCurveCategoryRenameDelegate, OnCategoryRename) SLATE_EVENT(FEaseCurvePresetDelegate, OnPresetDelete) SLATE_EVENT(FEaseCurvePresetRenameDelegate, OnPresetRename) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnBeginPresetMove) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnEndPresetMove) SLATE_EVENT(FEaseCurvePresetClickDelegate, OnPresetClick) SLATE_EVENT(FEaseCurvePresetDelegate, OnSetQuickEase) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L43 _public prototype_ `void SetSearchText(const FText& InText);`
- L45 _public prototype_ `int32 GetVisiblePresetCount() const;`
- L47 _public prototype_ `bool IsEditMode() const;`
- L49 _public prototype_ `void ResetDragBorder();`
- L51 _public function_ `void NotifyCanDrop(const bool bInCanDrop)`
- L53 _public function_ `FText GetCategoryName() const`
- L55 _public prototype_ `bool IsSelected(const TSharedPtr<FEaseCurvePreset> InPreset) const;`
- L58 _protected prototype_ `TSharedRef<SWidget> ConstructHeader();`
- L60 _protected prototype_ `TSharedRef<ITableRow> GeneratePresetWidget(const TSharedPtr<FEaseCurvePreset> InPreset, const TSharedRef<STableViewBase>& InOwnerTable);`
- L62 _protected prototype_ `EVisibility GetEditModeVisibility() const;`
- L64 _protected prototype_ `const FSlateBrush* GetBorderImage() const;`
- L66 _protected prototype_ `FText GetPresetNameTooltipText() const;`
- L68 _protected prototype_ `void HandleCategoryRenameCommitted(const FText& InNewText, ETextCommit::Type InCommitType);`
- L69 _protected prototype_ `FReply HandleCategoryDelete() const;`
- L71 _protected prototype_ `bool HandlePresetDelete(const TSharedPtr<FEaseCurvePreset>& InPreset);`
- L72 _protected prototype_ `bool HandlePresetRename(const TSharedPtr<FEaseCurvePreset>& InPreset, const FText& InNewName);`
- L73 _protected prototype_ `bool HandlePresetBeginMove(const TSharedPtr<FEaseCurvePreset>& InPreset, const FText& InNewCategoryName) const;`
- L74 _protected prototype_ `bool HandlePresetEndMove(const TSharedPtr<FEaseCurvePreset>& InPreset, const FText& InNewCategoryName) const;`
- L75 _protected prototype_ `bool HandlePresetClick(const TSharedPtr<FEaseCurvePreset>& InPreset) const;`
- L76 _protected prototype_ `bool HandleSetQuickEase(const TSharedPtr<FEaseCurvePreset>& InPreset) const;`
- L79 _protected prototype_ `virtual void OnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L80 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& InDragDropEvent) override;`
- L81 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L82 _protected prototype_ `virtual FReply OnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L85 _protected member_ `FText CategoryName;`
- L86 _protected member_ `TArray<TSharedPtr<FEaseCurvePreset>> Presets;`
- L87 _protected member_ `FText SearchText;`
- L88 _protected member_ `TAttribute<bool> bIsEditMode;`
- L89 _protected member_ `FFrameRate DisplayRate;`
- L90 _protected member_ `TAttribute<TSharedPtr<FEaseCurvePreset>> SelectedPreset;`
- L91 _protected member_ `FEaseCurveCategoryDeleteDelegate OnCategoryDelete;`
- L92 _protected member_ `FEaseCurveCategoryRenameDelegate OnCategoryRename;`
- L93 _protected member_ `FEaseCurvePresetDelegate OnPresetDelete;`
- L94 _protected member_ `FEaseCurvePresetRenameDelegate OnPresetRename;`
- L95 _protected member_ `FEaseCurvePresetMoveDelegate OnBeginPresetMove;`
- L96 _protected member_ `FEaseCurvePresetMoveDelegate OnEndPresetMove;`
- L97 _protected member_ `FEaseCurvePresetClickDelegate OnPresetClick;`
- L98 _protected member_ `FEaseCurvePresetDelegate OnSetQuickEase;`
- L100 _protected member_ `TArray<TSharedPtr<FEaseCurvePreset>> VisiblePresets;`
- L102 _protected member_ `TSharedPtr<SEditableTextBox> RenameCategoryNameTextBox;`
- L103 _protected member_ `TMap<TSharedPtr<FEaseCurvePreset>, TSharedPtr<SEaseCurvePresetGroupItem>> PresetWidgetsMap;`
- L105 _protected member_ `bool bCanBeDroppedOn = false;`
- L106 _protected member_ `bool bIsOverDifferentCategory = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace EaseCurveTool` (scope `UE`)
- L16 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FEaseCurveCategoryDeleteDelegate, const FText& ) DECLARE_DELEGATE_RetVal_TwoParams(bool, FEaseCurveCategoryRenameDelegate, const FText& , const FText& ) class SEaseCurvePresetGroup : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SEaseCurvePresetGroup) : _DisplayRate(FFrameRate(30, 1)) {} SLATE_ARGUMENT(FText, CategoryName) SLATE_ARGUMENT(TArray<TSharedPtr<FEaseCurvePreset>>, Presets) SLATE_ATTRIBUTE(TSharedPtr<FEaseCurvePreset>, SelectedPreset) SLATE_ARGUMENT(FText, SearchText) SLATE_ATTRIBUTE(bool, IsEditMode) SLATE_ARGUMENT(FFrameRate, DisplayRate) SLATE_EVENT(FEaseCurveCategoryDeleteDelegate, OnCategoryDelete) SLATE_EVENT(FEaseCurveCategoryRenameDelegate, OnCategoryRename) SLATE_EVENT(FEaseCurvePresetDelegate, OnPresetDelete) SLATE_EVENT(FEaseCurvePresetRenameDelegate, OnPresetRename) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnBeginPresetMove) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnEndPresetMove) SLATE_EVENT(FEaseCurvePresetClickDelegate, OnPresetClick) SLATE_EVENT(FEaseCurvePresetDelegate, OnSetQuickEase) SLATE_END_ARGS() void Construct(const FArguments& InArgs); void SetSearchText(const FText& InText); int32 GetVisiblePresetCount() const; bool IsEditMode() const; void ResetDragBorder(); void NotifyCanDrop(const bool bInCanDrop) { bCanBeDroppedOn = bInCanDrop; } FText GetCategoryName() const { return CategoryName; } bool IsSelected(const TSharedPtr<FEaseCurvePreset> InPreset) const;`
- L17 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FEaseCurveCategoryRenameDelegate, const FText& , const FText& ) class SEaseCurvePresetGroup : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SEaseCurvePresetGroup) : _DisplayRate(FFrameRate(30, 1)) {} SLATE_ARGUMENT(FText, CategoryName) SLATE_ARGUMENT(TArray<TSharedPtr<FEaseCurvePreset>>, Presets) SLATE_ATTRIBUTE(TSharedPtr<FEaseCurvePreset>, SelectedPreset) SLATE_ARGUMENT(FText, SearchText) SLATE_ATTRIBUTE(bool, IsEditMode) SLATE_ARGUMENT(FFrameRate, DisplayRate) SLATE_EVENT(FEaseCurveCategoryDeleteDelegate, OnCategoryDelete) SLATE_EVENT(FEaseCurveCategoryRenameDelegate, OnCategoryRename) SLATE_EVENT(FEaseCurvePresetDelegate, OnPresetDelete) SLATE_EVENT(FEaseCurvePresetRenameDelegate, OnPresetRename) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnBeginPresetMove) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnEndPresetMove) SLATE_EVENT(FEaseCurvePresetClickDelegate, OnPresetClick) SLATE_EVENT(FEaseCurvePresetDelegate, OnSetQuickEase) SLATE_END_ARGS() void Construct(const FArguments& InArgs); void SetSearchText(const FText& InText); int32 GetVisiblePresetCount() const; bool IsEditMode() const; void ResetDragBorder(); void NotifyCanDrop(const bool bInCanDrop) { bCanBeDroppedOn = bInCanDrop; } FText GetCategoryName() const { return CategoryName; } bool IsSelected(const TSharedPtr<FEaseCurvePreset> InPreset) const;`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Widgets/SEaseCurvePresetGroupItem.h` (Private)


#### class `UE::EaseCurveTool::SEaseCurvePresetGroupItem`  
`class SEaseCurvePresetGroupItem : public STableRow<TSharedPtr<FEaseCurvePreset>>`  
_L23-90_
- inherits: `STableRow<TSharedPtr<FEaseCurvePreset>>`
- L26 _public function_ `SLATE_BEGIN_ARGS(SEaseCurvePresetGroupItem) : _DisplayRate(FFrameRate(30, 1))`
- L29 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FEaseCurvePreset>, Preset) SLATE_ATTRIBUTE(bool, IsEditMode) SLATE_ARGUMENT(FFrameRate, DisplayRate) SLATE_ATTRIBUTE(bool, IsSelected) SLATE_EVENT(FEaseCurvePresetClickDelegate, OnClick) SLATE_EVENT(FEaseCurvePresetDelegate, OnDelete) SLATE_EVENT(FEaseCurvePresetRenameDelegate, OnRename) SLATE_EVENT(FEaseCurvePresetDelegate, OnSetQuickEase) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnBeginMove) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnEndMove) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<STableViewBase>& InOwnerTableView);`
- L43 _public prototype_ `void SetPreset(const TSharedPtr<FEaseCurvePreset>& InPreset);`
- L45 _public prototype_ `bool IsEditMode() const;`
- L47 _public prototype_ `void TriggerBeginMove();`
- L48 _public prototype_ `void TriggerEndMove();`
- L51 _protected prototype_ `void HandleRenameTextCommitted(const FText& InNewText, ETextCommit::Type InCommitType) const;`
- L53 _protected prototype_ `FReply HandleDeleteClick() const;`
- L55 _protected prototype_ `EVisibility GetEditModeVisibility() const;`
- L57 _protected prototype_ `EVisibility GetBorderVisibility() const;`
- L58 _protected prototype_ `const FSlateBrush* GetBackgroundImage() const;`
- L60 _protected prototype_ `FSlateColor GetQuickPresetIconColor() const;`
- L61 _protected prototype_ `EVisibility GetQuickPresetIconVisibility() const;`
- L62 _protected prototype_ `FText GetQuickPresetIconToolTip() const;`
- L64 _protected prototype_ `bool IsQuickEasePreset() const;`
- L66 _protected prototype_ `FReply HandleSetQuickEase();`
- L69 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L70 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L71 _protected prototype_ `virtual FReply OnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L72 _protected prototype_ `virtual FReply OnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) override;`
- L75 _protected member_ `TSharedPtr<FEaseCurvePreset> Preset;`
- L76 _protected member_ `TAttribute<bool> bIsEditMode;`
- L77 _protected member_ `TAttribute<bool> IsSelected;`
- L79 _protected member_ `FEaseCurvePresetClickDelegate OnClick;`
- L80 _protected member_ `FEaseCurvePresetDelegate OnDelete;`
- L81 _protected member_ `FEaseCurvePresetRenameDelegate OnRename;`
- L82 _protected member_ `FEaseCurvePresetDelegate OnSetQuickEase;`
- L84 _protected member_ `FEaseCurvePresetMoveDelegate OnBeginMove;`
- L85 _protected member_ `FEaseCurvePresetMoveDelegate OnEndMove;`
- L87 _protected member_ `TSharedPtr<SEditableTextBox> RenameTextBox;`
- L89 _protected member_ `bool bIsDragging = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace EaseCurveTool` (scope `UE`)
- L18 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FEaseCurvePresetDelegate, const TSharedPtr<FEaseCurvePreset>& ) DECLARE_DELEGATE_RetVal_OneParam(bool, FEaseCurvePresetClickDelegate, const TSharedPtr<FEaseCurvePreset>& ) DECLARE_DELEGATE_RetVal_TwoParams(bool, FEaseCurvePresetRenameDelegate, const TSharedPtr<FEaseCurvePreset>& , const FText& ) DECLARE_DELEGATE_RetVal_TwoParams(bool, FEaseCurvePresetMoveDelegate, const TSharedPtr<FEaseCurvePreset>& , const FText& ) class SEaseCurvePresetGroupItem : public STableRow<TSharedPtr<FEaseCurvePreset>> { public: SLATE_BEGIN_ARGS(SEaseCurvePresetGroupItem) : _DisplayRate(FFrameRate(30, 1)) {} SLATE_ARGUMENT(TSharedPtr<FEaseCurvePreset>, Preset) SLATE_ATTRIBUTE(bool, IsEditMode) SLATE_ARGUMENT(FFrameRate, DisplayRate) SLATE_ATTRIBUTE(bool, IsSelected) SLATE_EVENT(FEaseCurvePresetClickDelegate, OnClick) SLATE_EVENT(FEaseCurvePresetDelegate, OnDelete) SLATE_EVENT(FEaseCurvePresetRenameDelegate, OnRename) SLATE_EVENT(FEaseCurvePresetDelegate, OnSetQuickEase) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnBeginMove) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnEndMove) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<STableViewBase>& InOwnerTableView); void SetPreset(const TSharedPtr<FEaseCurvePreset>& InPreset); bool IsEditMode() const; void TriggerBeginMove(); void TriggerEndMove(); protected: void HandleRenameTextCommitted(const FText& InNewText, ETextCommit::Type InCommitType) const; FReply HandleDeleteClick() const; EVisibi`
- L19 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FEaseCurvePresetClickDelegate, const TSharedPtr<FEaseCurvePreset>& ) DECLARE_DELEGATE_RetVal_TwoParams(bool, FEaseCurvePresetRenameDelegate, const TSharedPtr<FEaseCurvePreset>& , const FText& ) DECLARE_DELEGATE_RetVal_TwoParams(bool, FEaseCurvePresetMoveDelegate, const TSharedPtr<FEaseCurvePreset>& , const FText& ) class SEaseCurvePresetGroupItem : public STableRow<TSharedPtr<FEaseCurvePreset>> { public: SLATE_BEGIN_ARGS(SEaseCurvePresetGroupItem) : _DisplayRate(FFrameRate(30, 1)) {} SLATE_ARGUMENT(TSharedPtr<FEaseCurvePreset>, Preset) SLATE_ATTRIBUTE(bool, IsEditMode) SLATE_ARGUMENT(FFrameRate, DisplayRate) SLATE_ATTRIBUTE(bool, IsSelected) SLATE_EVENT(FEaseCurvePresetClickDelegate, OnClick) SLATE_EVENT(FEaseCurvePresetDelegate, OnDelete) SLATE_EVENT(FEaseCurvePresetRenameDelegate, OnRename) SLATE_EVENT(FEaseCurvePresetDelegate, OnSetQuickEase) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnBeginMove) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnEndMove) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<STableViewBase>& InOwnerTableView); void SetPreset(const TSharedPtr<FEaseCurvePreset>& InPreset); bool IsEditMode() const; void TriggerBeginMove(); void TriggerEndMove(); protected: void HandleRenameTextCommitted(const FText& InNewText, ETextCommit::Type InCommitType) const; FReply HandleDeleteClick() const; EVisibility GetEditModeVisibility() const; EVisibility GetBorderVisibility() const; const FSlateBrush* GetBack`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FEaseCurvePresetRenameDelegate, const TSharedPtr<FEaseCurvePreset>& , const FText& ) DECLARE_DELEGATE_RetVal_TwoParams(bool, FEaseCurvePresetMoveDelegate, const TSharedPtr<FEaseCurvePreset>& , const FText& ) class SEaseCurvePresetGroupItem : public STableRow<TSharedPtr<FEaseCurvePreset>> { public: SLATE_BEGIN_ARGS(SEaseCurvePresetGroupItem) : _DisplayRate(FFrameRate(30, 1)) {} SLATE_ARGUMENT(TSharedPtr<FEaseCurvePreset>, Preset) SLATE_ATTRIBUTE(bool, IsEditMode) SLATE_ARGUMENT(FFrameRate, DisplayRate) SLATE_ATTRIBUTE(bool, IsSelected) SLATE_EVENT(FEaseCurvePresetClickDelegate, OnClick) SLATE_EVENT(FEaseCurvePresetDelegate, OnDelete) SLATE_EVENT(FEaseCurvePresetRenameDelegate, OnRename) SLATE_EVENT(FEaseCurvePresetDelegate, OnSetQuickEase) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnBeginMove) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnEndMove) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<STableViewBase>& InOwnerTableView); void SetPreset(const TSharedPtr<FEaseCurvePreset>& InPreset); bool IsEditMode() const; void TriggerBeginMove(); void TriggerEndMove(); protected: void HandleRenameTextCommitted(const FText& InNewText, ETextCommit::Type InCommitType) const; FReply HandleDeleteClick() const; EVisibility GetEditModeVisibility() const; EVisibility GetBorderVisibility() const; const FSlateBrush* GetBackgroundImage() const;`
- L21 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FEaseCurvePresetMoveDelegate, const TSharedPtr<FEaseCurvePreset>& , const FText& ) class SEaseCurvePresetGroupItem : public STableRow<TSharedPtr<FEaseCurvePreset>> { public: SLATE_BEGIN_ARGS(SEaseCurvePresetGroupItem) : _DisplayRate(FFrameRate(30, 1)) {} SLATE_ARGUMENT(TSharedPtr<FEaseCurvePreset>, Preset) SLATE_ATTRIBUTE(bool, IsEditMode) SLATE_ARGUMENT(FFrameRate, DisplayRate) SLATE_ATTRIBUTE(bool, IsSelected) SLATE_EVENT(FEaseCurvePresetClickDelegate, OnClick) SLATE_EVENT(FEaseCurvePresetDelegate, OnDelete) SLATE_EVENT(FEaseCurvePresetRenameDelegate, OnRename) SLATE_EVENT(FEaseCurvePresetDelegate, OnSetQuickEase) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnBeginMove) SLATE_EVENT(FEaseCurvePresetMoveDelegate, OnEndMove) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<STableViewBase>& InOwnerTableView); void SetPreset(const TSharedPtr<FEaseCurvePreset>& InPreset); bool IsEditMode() const; void TriggerBeginMove(); void TriggerEndMove(); protected: void HandleRenameTextCommitted(const FText& InNewText, ETextCommit::Type InCommitType) const; FReply HandleDeleteClick() const; EVisibility GetEditModeVisibility() const; EVisibility GetBorderVisibility() const; const FSlateBrush* GetBackgroundImage() const; FSlateColor GetQuickPresetIconColor() const;`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Widgets/SEaseCurvePresetList.h` (Private)


#### class `UE::EaseCurveTool::SEaseCurvePresetList`  
`class SEaseCurvePresetList : public SCompoundWidget`  
_L26-106_
- inherits: `SCompoundWidget`
- L29 _public function_ `SLATE_BEGIN_ARGS(SEaseCurvePresetList) : _DisplayRate(FFrameRate(30, 1)) , _AllowEditMode(true)`
- L34 _public prototype_ `SLATE_ATTRIBUTE(FFrameRate, DisplayRate) SLATE_ARGUMENT(bool, AllowEditMode) SLATE_EVENT(FOnPresetChanged, OnPresetChanged) SLATE_EVENT(FOnPresetChanged, OnQuickPresetChanged) SLATE_END_ARGS() virtual ~SEaseCurvePresetList() override;` — Display rate used to draw the ease curve preview.
- L42 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FEaseCurveTool>& InTool);`
- L44 _public prototype_ `bool HasSelection() const;`
- L46 _public prototype_ `bool GetSelectedItem(FEaseCurvePreset& OutPreset) const;`
- L48 _public prototype_ `void ClearSelection();`
- L50 _public prototype_ `bool SetSelectedItem(const FEaseCurvePresetHandle& InPresetHandle);`
- L51 _public prototype_ `bool SetSelectedItem(const FEaseCurveTangents& InTangents);`
- L53 _public prototype_ `TSharedPtr<FEaseCurvePreset> FindItem(const FEaseCurvePresetHandle& InPresetHandle) const;`
- L54 _public prototype_ `TSharedPtr<FEaseCurvePreset> FindItemByTangents(const FEaseCurveTangents& InTangents, const double InErrorTolerance = 0.01) const;`
- L56 _public prototype_ `bool IsInEditMode() const;`
- L57 _public prototype_ `void EnableEditMode(const bool bInEnable);`
- L59 _public prototype_ `void Reload();`
- L62 _protected prototype_ `TSharedRef<SWidget> GenerateSearchRowWidget();`
- L64 _protected prototype_ `void ReloadPresetItems();`
- L66 _protected prototype_ `void RegenerateGroupWrapBox();`
- L67 _protected prototype_ `void UpdateGroupsContent();`
- L69 _protected prototype_ `void HandlePresetLibraryChanged(const TWeakObjectPtr<UEaseCurveLibrary> InLibrary);`
- L73 _protected prototype_ `FReply OnDeletePresetClick();`
- L74 _protected prototype_ `FReply CreateNewCategory();`
- L76 _protected prototype_ `void ToggleEditMode(const ECheckBoxState bInNewState);`
- L78 _protected prototype_ `void HandleSearchTextChanged(const FText& InSearchText);`
- L80 _protected prototype_ `bool HandleCategoryDelete(const FText& InCategory);`
- L81 _protected prototype_ `bool HandleCategoryRename(const FText& InCategory, const FText& InNewName);`
- L82 _protected prototype_ `bool HandlePresetDelete(const TSharedPtr<FEaseCurvePreset>& InPreset);`
- L83 _protected prototype_ `bool HandlePresetRename(const TSharedPtr<FEaseCurvePreset>& InPreset, const FText& InNewName);`
- L84 _protected prototype_ `bool HandleBeginPresetMove(const TSharedPtr<FEaseCurvePreset>& InPreset, const FText& InNewCategory);`
- L85 _protected prototype_ `bool HandleEndPresetMove(const TSharedPtr<FEaseCurvePreset>& InPreset, const FText& InNewCategory);`
- L86 _protected prototype_ `bool HandlePresetClick(const TSharedPtr<FEaseCurvePreset>& InPreset);`
- L87 _protected prototype_ `bool HandleSetQuickEase(const TSharedPtr<FEaseCurvePreset>& InPreset);`
- L89 _protected member_ `TWeakPtr<FEaseCurveTool> WeakTool;`
- L91 _protected member_ `TAttribute<FFrameRate> DisplayRate;`
- L92 _protected member_ `bool bAllowEditMode = false;`
- L93 _protected member_ `FOnPresetChanged OnPresetChanged;`
- L94 _protected member_ `FOnPresetChanged OnQuickPresetChanged;`
- L96 _protected member_ `TSharedPtr<SBox> GroupWidgetsParent;`
- L97 _protected member_ `TSharedPtr<SUniformWrapPanel> GroupWrapBox;`
- L98 _protected member_ `TArray<TSharedPtr<SEaseCurvePresetGroup>> GroupWidgets;`
- L100 _protected member_ `TArray<TSharedPtr<FEaseCurvePreset>> PresetItems;`
- L101 _protected member_ `TSharedPtr<FEaseCurvePreset> SelectedItem;`
- L103 _protected member_ `FText SearchText;`
- L105 _protected member_ `TAttribute<bool> bEditMode;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace EaseCurveTool` (scope `UE`)
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPresetChanged, const TSharedPtr<FEaseCurvePreset>&) class SEaseCurvePresetList : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SEaseCurvePresetList) : _DisplayRate(FFrameRate(30, 1)) , _AllowEditMode(true) {} SLATE_ATTRIBUTE(FFrameRate, DisplayRate) SLATE_ARGUMENT(bool, AllowEditMode) SLATE_EVENT(FOnPresetChanged, OnPresetChanged) SLATE_EVENT(FOnPresetChanged, OnQuickPresetChanged) SLATE_END_ARGS() virtual ~SEaseCurvePresetList() override; void Construct(const FArguments& InArgs, const TSharedRef<FEaseCurveTool>& InTool); bool HasSelection() const; bool GetSelectedItem(FEaseCurvePreset& OutPreset) const; void ClearSelection(); bool SetSelectedItem(const FEaseCurvePresetHandle& InPresetHandle); bool SetSelectedItem(const FEaseCurveTangents& InTangents); TSharedPtr<FEaseCurvePreset> FindItem(const FEaseCurvePresetHandle& InPresetHandle) const; TSharedPtr<FEaseCurvePreset> FindItemByTangents(const FEaseCurveTangents& InTangents, const double InErrorTolerance = 0.01) const; bool IsInEditMode() const; void EnableEditMode(const bool bInEnable); void Reload(); protected: TSharedRef<SWidget> GenerateSearchRowWidget();`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Widgets/SEaseCurvePreview.h` (Private)


#### class `UE::EaseCurveTool::SEaseCurvePreview`  
`class SEaseCurvePreview : public SLeafWidget`  
_L22-139_
- inherits: `SLeafWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS(SEaseCurvePreview) : _Tangents() , _PreviewSize(32.f) , _CanExpandPreview(false) , _CurveThickness(2.f) , _CurveColor(FLinearColor::White) , _StraightColor(FStyleColors::AccentBlue.GetSpecifiedColor()) , _CustomToolTip(false) , _Animate(false) , _IdleAnimationLength(1.f) , _DisplayRate(FFrameRate(30, 1)) , _AnimationColor(FLinearColor::White) , _AnimationSize(12.f) , _DrawMotionTrails(false) , _MotionTrailColor(FLinearColor(0.5f, 0.5f, 0.5f, 1.f)) , _MotionTrailColorFade(FLinearColor(0.15f, 0.15f, 0.15f, 1.f)) , _MotionTrailSize(10.f) , _MotionTrailFadeLength(0.2f) , _MotionTrailOffset(FVector2D(0.f, 10.f))`
- L45 _public prototype_ `SLATE_ATTRIBUTE(FEaseCurveTangents, Tangents) SLATE_ARGUMENT(float, PreviewSize) SLATE_ARGUMENT(bool, CanExpandPreview) SLATE_ARGUMENT(float, CurveThickness) SLATE_ARGUMENT(TOptional<FLinearColor>, BackgroundColor) SLATE_ARGUMENT(FLinearColor, CurveColor) SLATE_ARGUMENT(FLinearColor, StraightColor) SLATE_ARGUMENT(TOptional<FLinearColor>, UnderCurveColor) SLATE_ARGUMENT(bool, CustomToolTip) SLATE_ARGUMENT(bool, Animate) SLATE_ARGUMENT(bool, FlatAnimation) SLATE_ARGUMENT(float, IdleAnimationLength) SLATE_ARGUMENT(FFrameRate, DisplayRate) SLATE_ARGUMENT(FLinearColor, AnimationColor) SLATE_ARGUMENT(float, AnimationSize) SLATE_ARGUMENT(bool, DrawMotionTrails) SLATE_ARGUMENT(FLinearColor, MotionTrailColor) SLATE_ARGUMENT(FLinearColor, MotionTrailColorFade) SLATE_ARGUMENT(float, MotionTrailSize) SLATE_ARGUMENT(float, MotionTrailFadeLength) SLATE_ARGUMENT(FVector2D, MotionTrailOffset) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L75 _public prototype_ `FEaseCurveTangents GetTangents() const;`
- L76 _public prototype_ `void SetTangents(const TAttribute<FEaseCurveTangents>& InTangents);`
- L80 _public prototype_ `virtual TSharedRef<FSlateAccessibleWidget> CreateAccessibleWidget() override;`
- L82 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InMyCullingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool bInParentEnabled) const override;`
- L86 _protected prototype_ `void MakeCurveData(const FGeometry& InGeometry, TArray<FVector2D>& OutCurvePoints, TArray<FLinearColor>& OutCurveColors) const;`
- L88 _protected prototype_ `float WeightedEvalForTwoKeys(const FEaseCurveTangents& InTangents, const float InTime) const;`
- L91 _protected prototype_ `virtual FVector2D ComputeDesiredSize(const float InLayoutScaleMultiplier) const override;`
- L92 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L93 _protected prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L96 _protected member_ `TAttribute<FEaseCurveTangents> Tangents;`
- L97 _protected member_ `float PreviewSize = 0.f;`
- L98 _protected member_ `bool CanExpandPreview = false;`
- L99 _protected member_ `float CurveThickness = 1.f;`
- L101 _protected member_ `TOptional<FLinearColor> BackgroundColor;`
- L102 _protected member_ `FLinearColor CurveColor = FLinearColor::White;`
- L103 _protected member_ `FLinearColor StraightColor = FLinearColor::White;`
- L104 _protected member_ `TOptional<FLinearColor> UnderCurveColor;`
- L106 _protected member_ `bool bAnimate = false;`
- L107 _protected member_ `float IdleAnimationLength = 0.f;`
- L108 _protected member_ `FFrameRate DisplayRate;`
- L109 _protected member_ `FLinearColor AnimationColor = FLinearColor::White;`
- L110 _protected member_ `float AnimationSize = 0.f;`
- L111 _protected member_ `bool bDrawMotionTrails = false;`
- L112 _protected member_ `FLinearColor MotionTrailColor = FLinearColor::White;`
- L113 _protected member_ `FLinearColor MotionTrailColorFade = FLinearColor::White;`
- L114 _protected member_ `float MotionTrailSize = 0.f;`
- L115 _protected member_ `float MotionTrailFadeLength = 0.f;`
- L116 _protected member_ `FVector2D MotionTrailOffset = FVector2D::ZeroVector;`
- L118 _protected member_ `TSharedPtr<SEaseCurvePreviewToolTip> ToolTipWidget;`
- L121 _protected member_ `float BelowZeroValue = 0.f;` — The amount the curve is below value 0 in curve space.
- L123 _protected member_ `float AboveOneValue = 0.f;` — The amount the curve is above value 1 in curve space.
- L125 _protected member_ `TSharedPtr<FActiveTimerHandle> IdleTimerHandle;`
- L127 _protected member_ `double CurrentAnimateTime = 0.f;`
- L128 _protected member_ `FVector2D CurrentAnimateLocation = FVector2D::ZeroVector;`
- L136 _protected member_ `TArray<FMotionTrail> MotionTrails;`
- L138 _protected member_ `double MotionTrailFadeStartTime = 0.f;`

#### struct `UE::EaseCurveTool::SEaseCurvePreview::FMotionTrail`  
`struct FMotionTrail`  
_L130-135_
- L132 _public member_ `FVector2D Location = FVector2D::ZeroVector;`
- L133 _public member_ `float Time = 0.f;`
- L134 _public member_ `FLinearColor Color = FLinearColor(1.f, 1.f, 1.f, 1.f);`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Widgets/SEaseCurvePreviewToolTip.h` (Private)


#### class `UE::EaseCurveTool::SEaseCurvePreviewToolTip`  
`class SEaseCurvePreviewToolTip : public IToolTip`  
_L15-44_
- inherits: `IToolTip`
- L18 _public prototype_ `static FText GetToolTipText(const FEaseCurveTangents& InTangents);`
- L20 _public prototype_ `static TSharedRef<SToolTip> CreateDefaultToolTip(const SEaseCurvePreview::FArguments& InPreviewArgs, const TSharedPtr<SWidget>& InAdditionalContent = nullptr);`
- L22 _public prototype_ `SEaseCurvePreviewToolTip(const SEaseCurvePreview::FArguments& InPreviewArgs, const TSharedPtr<SWidget>& InAdditionalContent = nullptr);`
- L23 _public prototype_ `virtual ~SEaseCurvePreviewToolTip() override = default;`
- L26 _protected prototype_ `void CreateToolTipWidget();`
- L28 _protected prototype_ `void InvalidateWidget();`
- L31 _protected prototype_ `virtual TSharedRef<SWidget> AsWidget() override;`
- L32 _protected prototype_ `virtual TSharedRef<SWidget> GetContentWidget() override;`
- L33 _protected prototype_ `virtual void SetContentWidget(const TSharedRef<SWidget>& InContentWidget) override;`
- L34 _protected function_ `virtual bool IsEmpty() const override`
- L35 _protected function_ `virtual bool IsInteractive() const override`
- L36 _protected function_ `virtual void OnOpening() override`
- L37 _protected function_ `virtual void OnClosed() override`
- L40 _protected member_ `SEaseCurvePreview::FArguments PreviewArgs;`
- L41 _protected member_ `TSharedPtr<SWidget> AdditionalContent;`
- L43 _protected member_ `TSharedPtr<SToolTip> ToolTipWidget;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Widgets/SEaseCurveTangents.h` (Private)


#### class `UE::EaseCurveTool::SEaseCurveTangents`  
`class SEaseCurveTangents : public SCompoundWidget`  
_L11-56_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SEaseCurveTangents)`
- L16 _public prototype_ `SLATE_ARGUMENT(FEaseCurveTangents, InitialTangents) SLATE_EVENT(SNumericEntryBox<double>::FOnValueChanged, OnStartTangentChanged) SLATE_EVENT(SNumericEntryBox<double>::FOnValueChanged, OnStartWeightChanged) SLATE_EVENT(SNumericEntryBox<double>::FOnValueChanged, OnEndTangentChanged) SLATE_EVENT(SNumericEntryBox<double>::FOnValueChanged, OnEndWeightChanged) SLATE_EVENT(FSimpleDelegate, OnBeginSliderMovement) SLATE_EVENT(SNumericEntryBox<double>::FOnValueChanged, OnEndSliderMovement) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _public prototype_ `double GetStartTangent() const;`
- L28 _public prototype_ `double GetStartTangentWeight() const;`
- L29 _public prototype_ `double GetEndTangent() const;`
- L30 _public prototype_ `double GetEndTangentWeight() const;`
- L32 _public prototype_ `void SetTangents(const FEaseCurveTangents& InTangents);`
- L35 _protected prototype_ `TSharedRef<SWidget> ConstructTangentNumBox(const FText& InLabel , const FText& InToolTip , const TAttribute<double>& InValue , const SNumericEntryBox<double>::FOnValueChanged& InOnValueChanged , const TOptional<double>& InMinSliderValue , const TOptional<double>& InMaxSliderValue) const;`
- L42 _protected prototype_ `void OnStartTangentSpinBoxChanged(const double InNewValue);`
- L43 _protected prototype_ `void OnStartTangentWeightSpinBoxChanged(const double InNewValue);`
- L44 _protected prototype_ `void OnEndTangentSpinBoxChanged(const double InNewValue);`
- L45 _protected prototype_ `void OnEndTangentWeightSpinBoxChanged(const double InNewValue);`
- L47 _protected member_ `FEaseCurveTangents Tangents;`
- L49 _protected member_ `SNumericEntryBox<double>::FOnValueChanged OnStartTangentChanged;`
- L50 _protected member_ `SNumericEntryBox<double>::FOnValueChanged OnStartWeightChanged;`
- L51 _protected member_ `SNumericEntryBox<double>::FOnValueChanged OnEndTangentChanged;`
- L52 _protected member_ `SNumericEntryBox<double>::FOnValueChanged OnEndWeightChanged;`
- L54 _protected member_ `FSimpleDelegate OnBeginSliderMovement;`
- L55 _protected member_ `SNumericEntryBox<double>::FOnValueChanged OnEndSliderMovement;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Private/Widgets/SEaseCurveTool.h` (Private)


#### class `UE::EaseCurveTool::SEaseCurveTool`  
`class SEaseCurveTool : public SCompoundWidget , public FEditorUndoClient`  
_L22-110_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L27 _public member_ `static constexpr int32 DefaultGraphSize = 200;`
- L29 _public function_ `SLATE_BEGIN_ARGS(SEaseCurveTool) : _ToolMode(EEaseCurveToolMode::DualKeyEdit) , _ToolOperation(EEaseCurveToolOperation::InOut)`
- L33 _public prototype_ `SLATE_ATTRIBUTE(EEaseCurveToolMode, ToolMode) SLATE_ATTRIBUTE(EEaseCurveToolOperation, ToolOperation) SLATE_ARGUMENT(FEaseCurveTangents, InitialTangents) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FEaseCurveTool>& InTool);`
- L40 _public prototype_ `void SetTangents(const FEaseCurveTangents& InTangents, EEaseCurveToolOperation InOperation, const bool bInSetEaseCurve, const bool bInBroadcastUpdate, const bool bInSetSequencerTangents) const;`
- L43 _public prototype_ `FEaseCurveTangents GetTangents() const;`
- L45 _public prototype_ `FKeyHandle GetSelectedKeyHandle() const;`
- L47 _public prototype_ `void ZoomToFit() const;`
- L49 _public prototype_ `void ResetTangentsAndNotify() const;`
- L53 _protected prototype_ `virtual FVector2D ComputeDesiredSize(const float InScaleMultiplier) const override;`
- L56 _protected prototype_ `TSharedRef<SWidget> ConstructCurveEditorPanel();`
- L58 _protected prototype_ `FFrameRate GetDisplayRate() const;`
- L59 _protected prototype_ `EEaseCurveToolOperation GetToolOperation() const;`
- L60 _protected prototype_ `TOptional<FVector2D> GetEditorSize() const;`
- L62 _protected prototype_ `bool CanEditCurve() const;`
- L63 _protected prototype_ `TOptional<FText> GetErrorMessage() const;`
- L65 _protected prototype_ `void HandleLibraryChanged(const TWeakObjectPtr<UEaseCurveLibrary> InWeakLibrary);`
- L67 _protected prototype_ `void HandleEditorTangentsChanged(const FEaseCurveTangents& InTangents) const;`
- L69 _protected prototype_ `void OnStartTangentSpinBoxChanged(const double InNewValue) const;`
- L70 _protected prototype_ `void OnStartTangentWeightSpinBoxChanged(const double InNewValue) const;`
- L71 _protected prototype_ `void OnEndTangentSpinBoxChanged(const double InNewValue) const;`
- L72 _protected prototype_ `void OnEndTangentWeightSpinBoxChanged(const double InNewValue) const;`
- L73 _protected prototype_ `void OnBeginSliderMovement();`
- L74 _protected prototype_ `void OnEndSliderMovement(const double InNewValue);`
- L76 _protected prototype_ `void OnPresetChanged(const TSharedPtr<FEaseCurvePreset>& InPreset) const;`
- L77 _protected prototype_ `void OnQuickPresetChanged(const TSharedPtr<FEaseCurvePreset>& InPreset) const;`
- L78 _protected prototype_ `bool OnGetNewPresetTangents(FEaseCurveTangents& OutTangents) const;`
- L80 _protected prototype_ `void UndoAction();`
- L81 _protected prototype_ `void RedoAction();`
- L83 _protected prototype_ `void OnEditorDragStart() const;`
- L84 _protected prototype_ `void OnEditorDragEnd() const;`
- L86 _protected prototype_ `FText GetStartText() const;`
- L87 _protected prototype_ `FText GetStartTooltipText() const;`
- L88 _protected prototype_ `FText GetEndText() const;`
- L89 _protected prototype_ `FText GetEndTooltipText() const;`
- L92 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L95 _protected member_ `TWeakPtr<FEaseCurveTool> WeakTool;`
- L97 _protected member_ `TAttribute<EEaseCurveToolMode> ToolMode;`
- L98 _protected member_ `TAttribute<EEaseCurveToolOperation> ToolOperation;`
- L100 _protected member_ `TSharedPtr<SEaseCurvePreset> CurvePresetWidget;`
- L101 _protected member_ `TSharedPtr<SEaseCurveEditor> CurveEaseEditorWidget;`
- L102 _protected member_ `TSharedPtr<SEaseCurveTangents> CurveTangentsWidget;`
- L104 _protected member_ `int32 CurrentGraphSize = DefaultGraphSize;`
- L106 _protected member_ `TSharedPtr<FEaseCurveToolContextMenu> ContextMenu;`
- L108 _protected member_ `SVerticalBox::FSlot* ToolWidgetSlot = nullptr;`
- L109 _protected member_ `SVerticalBox::FSlot* GraphEditorSlot = nullptr;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace EaseCurveTool` (scope `UE`)

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Public/EaseCurveLibrary.h` (Public)


#### class `UEaseCurveLibrary`  
`class UEaseCurveLibrary : public UDataAsset`  
_L14-68_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataAsset`
- desc: Data asset that holds category and tangent data for ease curve presets
- L18 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPresetChangedDelegate, const FEaseCurvePreset&);`
- L25 _public prototype_ `static TArray<FEaseCurvePreset> GetDefaultPresets();` — Mainly used to compare clicked presets names for engine analytics, thus returns static category and preset names of the default presets instead of looking on disk for the actual default names.
- L27 _public function_ `FSimpleMulticastDelegate& OnPresetChanged()`
- L29 _public prototype_ `bool DoesPresetExist(const FEaseCurvePresetHandle& InPresetHandle) const;`
- L31 _public prototype_ `const TArray<FEaseCurvePreset>& GetPresets() const;`
- L33 _public prototype_ `TArray<FText> GetCategories() const;`
- L35 _public prototype_ `TArray<FEaseCurvePreset> GetCategoryPresets(const FText& InCategory) const;`
- L37 _public prototype_ `bool AddPreset(const FEaseCurvePreset& InPreset);`
- L38 _public prototype_ `bool AddPresetToNewCategory(const FText& InName, const FEaseCurveTangents& InTangents, FEaseCurvePreset& OutNewPreset);`
- L40 _public prototype_ `bool RemovePreset(const FEaseCurvePresetHandle& InPresetHandle);`
- L42 _public prototype_ `bool ChangePresetCategory(const FEaseCurvePreset& InPreset, const FText& InNewCategory);`
- L44 _public prototype_ `bool FindPreset(const FEaseCurvePresetHandle& InPresetHandle, FEaseCurvePreset& OutPreset);`
- L45 _public prototype_ `bool FindPresetByTangents(const FEaseCurveTangents& InTangents , FEaseCurvePreset& OutPreset, const double InErrorTolerance = 0.01);`
- L48 _public prototype_ `bool DoesPresetCategoryExist(const FText& InCategory) const;`
- L49 _public prototype_ `bool RenamePresetCategory(const FText& InCategory, const FText& InNewCategory);`
- L50 _public prototype_ `bool RemovePresetCategory(const FText& InCategory);`
- L52 _public prototype_ `bool RenamePreset(const FEaseCurvePresetHandle& InPresetHandle, const FText& InNewPresetName);`
- L54 _public prototype_ `void SetToDefaultPresets();`
- L56 _public prototype_ `FText GenerateNewEmptyCategory();`
- L58 _public prototype_ `void Sort();`
- L62 _protected member_ `TArray<FEaseCurvePreset> Presets;` — `UPROPERTY(EditAnywhere, Category = "Ease Curve Library")`
- L65 _protected member_ `TArray<FText> EmptyCategories;` — `UPROPERTY()`
- L67 _protected member_ `FSimpleMulticastDelegate PresetChangedDelegate;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPresetChangedDelegate, const FEaseCurvePreset&);`

### `Plugins/Animation/EaseCurveTool/Source/EaseCurveTool/Public/EaseCurveSerializer.h` (Public)


#### class `UEaseCurveSerializer`  
`class UEaseCurveSerializer : public UObject`  
_L20-66_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Derive from this class to make additional ease curve serializers capable of custom saving and loading of presets.
- L25 _public prototype_ `static bool PromptUserForFilePath(FString& OutFilePath, const bool bInImport);`
- L28 _public prototype_ `virtual FText GetDisplayName() const;` — The display name text to show for menu entries
- L31 _public prototype_ `virtual FText GetDisplayTooltip() const;` — The display tooltip text to show for menu entries
- L34 _public prototype_ `virtual bool IsFileExport() const;` — @return True if the export operation should prompt for a file location
- L37 _public prototype_ `virtual bool SupportsExport() const;` — @return True if this serializer supports export of ease curve presets
- L48 _public prototype_ `virtual bool Export(const FString& InFilePath, TSet<TWeakObjectPtr<UEaseCurveLibrary>> InWeakLibraries);` — Exports an Ease Curve Library asset to an external file. Override to implement custom export logic (for a specific file type for example) @param InFilePath The path to the file where the library will be exported @param InWeakLibraries The Ease Curve Library assets to export @return True if the export operation was successful, false otherwise
- L51 _public prototype_ `virtual bool IsFileImport() const;` — @return True if the import operation should prompt for a file location
- L54 _public prototype_ `virtual bool SupportsImport() const;` — @return True if this serializer supports import of ease curve presets
- L65 _public prototype_ `virtual bool Import(const FString& InFilePath, TSet<TWeakObjectPtr<UEaseCurveLibrary>> InWeakLibraries);` — Imports an Ease Curve Library asset from an external file. Override to implement custom import logic (for a specific file type for example) @param InFilePath The path to the file where the library will be exported @param InWeakLibraries The Ease Curve Library assets to import @return True if the import operation was successful, false otherwise

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API EASECURVETOOL_API`
