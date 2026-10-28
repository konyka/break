# Editor / DetailCustomizations

- module root: `Source/Editor/DetailCustomizations`
- headers: 164; symbols: 3048
- symbol kinds: class=215, delegate=13, enum=9, enumerator=36, externvar=1, function=184, macro=14, member=758, namespace=6, prototype=1787, struct=17, typedef=5, variable=3
- DynamicallyLoadedModuleNames: GameProjectGeneration, GeometryProcessingInterfaces, Layers, MeshMergeUtilities, MeshReductionInterface
- PrivateDependencyModuleNames: AIModule, AdvancedPreviewScene, AdvancedWidgets, AnimGraph, AppFramework, ApplicationCore, AudioEditor, AudioSettingsEditor, BlueprintGraph, CinematicCamera, ClassViewer, ComponentVisualizers, ConfigEditor, ContentBrowser, Core, CoreUObject, DataTableEditor, DesktopPlatform, DesktopWidgets, EditorFramework, EditorWidgets, Engine, ExternalImagePicker, GraphEditor, HardwareTargeting, HeadMountedDisplay, InputCore, InternationalizationSettings, Json, JsonUtilities, Kismet, KismetWidgets, Landscape, LevelEditor, LevelSequence, MaterialEditor, MoviePlayer, MovieScene, MovieSceneCapture, MovieSceneTools, MovieSceneTracks, NavigationSystem, PhysicsCore, PropertyEditor, RHI, RenderCore, Sequencer, SettingsEditor, ShaderPlatformConfigEditor, SharedSettingsWidgets, SkeletonEditor, Slate, SlateCore, SourceCodeAccess, SourceControl, TargetPlatform, TimeManagement, ToolMenus, ToolWidgets, UnrealEd, VirtualTexturingEditor
- PrivateIncludePathModuleNames: GameProjectGeneration, GeometryProcessingInterfaces, LandscapeEditor, Layers, Media, MeshMergeUtilities, MeshReductionInterface
- PublicDependencyModuleNames: PropertyEditor, Slate

### `Source/Editor/DetailCustomizations/Private/AIDataProviderValueDetails.h` (Private)


#### class `FAIDataProviderValueDetails`  
`class FAIDataProviderValueDetails : public IPropertyTypeCustomization`  
_L17-44_
- inherits: `IPropertyTypeCustomization`
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L24 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L25 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L29 _private member_ `TSharedPtr<IPropertyHandle> DataBindingProperty;`
- L30 _private member_ `TSharedPtr<IPropertyHandle> DataFieldProperty;`
- L31 _private member_ `TSharedPtr<IPropertyHandle> DefaultValueProperty;`
- L32 _private member_ `FAIDataProviderValue* DataPtr;`
- L34 _private member_ `TArray<FName> MatchingProperties;`
- L36 _private prototype_ `void OnBindingChanged();`
- L37 _private prototype_ `TSharedRef<SWidget> OnGetDataFieldContent();`
- L38 _private prototype_ `void OnDataFieldNameChange(int32 Index);`
- L39 _private prototype_ `FText GetDataFieldDesc() const;`
- L40 _private prototype_ `FText GetValueDesc() const;`
- L41 _private prototype_ `EVisibility GetBindingDescVisibility() const;`
- L42 _private prototype_ `EVisibility GetDataFieldVisibility() const;`
- L43 _private prototype_ `EVisibility GetDefaultValueVisibility() const;`

### `Source/Editor/DetailCustomizations/Private/ActorComponentDetails.h` (Private)


#### class `FActorComponentDetails`  
`class FActorComponentDetails : public IDetailCustomization`  
_L10-18_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

### `Source/Editor/DetailCustomizations/Private/ActorDetails.h` (Private)


#### class `FActorDetails`  
`class FActorDetails : public IDetailCustomization`  
_L27-118_
- inherits: `IDetailCustomization`
- L30 _public prototype_ `virtual ~FActorDetails();`
- L33 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L36 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L39 _private prototype_ `DECLARE_DELEGATE_RetVal(const FSlateBrush*, FGetBrushImage);` — Delegate that returns an icon
- L42 _private prototype_ `DECLARE_DELEGATE_RetVal(FText, FGetText);` — Delegate that returns a tooltip or other text field
- L51 _private prototype_ `UClass* GetConversionRoot( UClass* InCurrentClass ) const;` — Returns the conversion root class of the passed in class @param InCurrentClass		The class to find the conversion root of @return						Going up the class hierarchy, the first class found to have "IsConversionRoot" metadata (NULL if none is found)
- L58 _private prototype_ `void OnConvertActor(UClass* ChosenClass);` — Callback from the Class Picker when a class is picked. @param ChosenClass		The class chosen to convert to
- L66 _private prototype_ `void CreateClassPickerConvertActorFilter(const TWeakObjectPtr<AActor> ConvertActor, class FClassViewerInitializationOptions* ClassPickerOptions);` — Creates the filters for displaying valid classes to convert to @param ConvertActor			The actor being converted @param ClassPickerOptions	Options for the Class Picker being generated, to be given a newly created filter
- L69 _private prototype_ `TSharedRef<SWidget> OnGetConvertContent();` — Retrieves the content for the Convert combo button
- L72 _private prototype_ `EVisibility GetConvertMenuVisibility() const;` — Returns the visibility of the Convert menu
- L75 _private prototype_ `TSharedRef<SWidget> MakeConvertMenu( const FSelectedActorInfo& SelectedActorInfo );` — Create the Convert combo button
- L77 _private prototype_ `void OnNarrowSelectionSetToSpecificLevel( TWeakObjectPtr<ULevel> LevelToNarrowInto );`
- L79 _private prototype_ `bool IsActorValidForLevelScript() const;`
- L81 _private prototype_ `FReply FindSelectedActorsInLevelScript();`
- L83 _private prototype_ `bool AreAnySelectedActorsInLevelScript() const;`
- L86 _private prototype_ `TSharedRef<SWidget> MakeEventOptionsWidgetFromSelection();` — Util to create a menu for events we can add for the selected actor
- L88 _private prototype_ `void AddActorCategory( IDetailLayoutBuilder& DetailBuilder, const TMap<ULevel*, int32>& ActorsPerLevelCount );`
- L90 _private prototype_ `void AddBlueprintCategory( IDetailLayoutBuilder& DetailBuilder, const TMap<UBlueprint*, UObject*>& UniqueBlueprints );`
- L92 _private prototype_ `void AddLayersCategory( IDetailLayoutBuilder& DetailBuilder );`
- L94 _private prototype_ `void AddTransformCategory( IDetailLayoutBuilder& DetailBuilder );`
- L97 _private prototype_ `void AddEventsCategory(IDetailLayoutBuilder& DetailBuilder);` — Display a category with all dynamic delegates on a CDO
- L100 _private prototype_ `FReply HandleAddOrViewEventForVariable(UBlueprint* BP, class FMulticastDelegateProperty* Property);` — Handle the creation of a bound event from a dynamic delegate on a CDO
- L102 _private prototype_ `const TArray< TWeakObjectPtr<AActor> >& GetSelectedActors() const;`
- L108 _private prototype_ `FReply OnPickBlueprintPathClicked(bool bHavest);` — Bring up the menu for user to select the path to create blueprint at
- L111 _private prototype_ `void OnSelectBlueprintPath(const FString& );` — Bring up the menu for user to select the path to create blueprint at
- L114 _private member_ `FString PathForActorBlueprint;` — The path the user has selected to create a blueprint at
- L117 _private member_ `TArray< TWeakObjectPtr<AActor> > SelectedActors;` — List of currently selected actors

#### Free symbols / members of external scopes

- L39 _delegate_ `DECLARE_DELEGATE_RetVal(const FSlateBrush*, FGetBrushImage);` — Delegate that returns an icon
- L42 _delegate_ `DECLARE_DELEGATE_RetVal(FText, FGetText);` — Delegate that returns a tooltip or other text field

### `Source/Editor/DetailCustomizations/Private/AmbientSoundDetails.h` (Private)


#### class `FAmbientSoundDetails`  
`class FAmbientSoundDetails : public IDetailCustomization`  
_L14-43_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L30 _private prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L32 _private prototype_ `bool IsEditSoundCueEnabled() const;`
- L34 _private prototype_ `FReply OnEditSoundCueClicked();`
- L35 _private prototype_ `FReply OnPlaySoundClicked();`
- L36 _private prototype_ `FReply OnStopSoundClicked();`
- L38 _private prototype_ `TSharedRef<SWidget> OnGetSoundCueTemplates();`
- L40 _private prototype_ `void CreateNewSoundCue( ESoundCueLayouts Layout );`
- L42 _private member_ `TWeakObjectPtr<class AAmbientSound> AmbientSound;`

#### enum `FAmbientSoundDetails::ESoundCueLayouts`  
`enum ESoundCueLayouts`  
_L21-27_
- L23 _public enumerator_ `SOUNDCUE_LAYOUT_EMPTY`
- L24 _public enumerator_ `SOUNDCUE_LAYOUT_MIXER`
- L25 _public enumerator_ `SOUNDCUE_LAYOUT_RANDOM_LOOP`
- L26 _public enumerator_ `SOUNDCUE_LAYOUT_RANDOM_LOOP_WITH_DELAY`

### `Source/Editor/DetailCustomizations/Private/AnimMontageSegmentDetails.h` (Private)


#### class `FAnimMontageSegmentDetails`  
`class FAnimMontageSegmentDetails : public IDetailCustomization`  
_L37-66_
- inherits: `IDetailCustomization`
- L41 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L44 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L46 _protected prototype_ `bool OnShouldFilterAnimAsset(const FAssetData& AssetData) const;`
- L48 _protected prototype_ `const UAnimSequenceBase* GetAnimationAsset() const;`
- L49 _protected prototype_ `FAnimSegment* GetAnimationSegment() const;`
- L50 _protected prototype_ `bool CanEditSegmentProperties() const;`
- L52 _protected prototype_ `void SetAnimationAsset(const FAssetData& InAssetData);`
- L53 _protected prototype_ `void OnStartTimeChanged(float InValue, ETextCommit::Type InCommitType, bool bInteractive = false);`
- L54 _protected prototype_ `void OnEndTimeChanged(float InValue, ETextCommit::Type InCommitType, bool bInteractive = false);`
- L56 _protected prototype_ `TOptional<float> GetStartTime() const;`
- L57 _protected prototype_ `TOptional<float> GetEndTime() const;`
- L58 _protected prototype_ `TOptional<float> GetAnimationAssetPlayLength() const;`
- L59 _protected prototype_ `TOptional<float> GetPlayRate() const;`
- L62 _protected member_ `TSharedPtr<IPropertyHandle> AnimSegmentHandle;`
- L63 _protected member_ `TSharedPtr<IPropertyHandle> AnimationAssetHandle;`
- L64 _protected member_ `TSharedPtr<IPropertyHandle> AnimStartTimeProperty;`
- L65 _protected member_ `TSharedPtr<IPropertyHandle> AnimEndTimeProperty;`

#### class `SAnimationSegmentViewport`  
`class SAnimationSegmentViewport : public SCompoundWidget`  
_L70-134_
- inherits: `SCompoundWidget`
- L73 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnValueChanged, float, bool);`
- L75 _public function_ `SLATE_BEGIN_ARGS( SAnimationSegmentViewport )`
- L86 _public prototype_ `SAnimationSegmentViewport();`
- L87 _public prototype_ `virtual ~SAnimationSegmentViewport();`
- L89 _public prototype_ `void Construct(const FArguments& InArgs);`
- L91 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L92 _public prototype_ `void RefreshViewport();`
- L95 _private prototype_ `void InitSkeleton();`
- L97 _private member_ `TSharedPtr<FEditorViewportClient> LevelViewportClient;`
- L99 _private member_ `TAttribute<const UAnimSequenceBase*> AnimationRefAttribute;`
- L100 _private member_ `TAttribute<TOptional<float>> StartTimeAttribute;`
- L101 _private member_ `TAttribute<TOptional<float>> EndTimeAttribute;`
- L102 _private member_ `TAttribute<TOptional<float>> PlayRateAttribute;`
- L103 _private member_ `FOnValueChanged OnStartTimeChanged;`
- L104 _private member_ `FOnValueChanged OnEndTimeChanged;`
- L108 _private member_ `TSharedPtr<SViewport> ViewportWidget;` — TSharedPtr<class FSceneViewport> Viewport;
- L110 _private member_ `TSharedPtr<class FSceneViewport> SceneViewport;`
- L112 _private member_ `TObjectPtr<UAnimSequenceBase> CurrentAnimSequenceBase;`
- L113 _private member_ `FAdvancedPreviewScene AdvancedPreviewScene;`
- L114 _private member_ `class UDebugSkelMeshComponent* PreviewComponent;`
- L116 _private member_ `TSharedPtr<STextBlock> Description;`
- L118 _private prototype_ `void CleanupComponent(USceneComponent* Component);`
- L119 _private prototype_ `bool IsVisible() const;`
- L124 _public prototype_ `float GetViewMinInput() const;` — Get Min/Max Input of value
- L125 _public prototype_ `float GetViewMaxInput() const;`
- L127 _public prototype_ `class UAnimSingleNodeInstance* GetPreviewInstance() const;`
- L130 _public prototype_ `TArray<float> GetBars() const;` — Optional, additional values to draw on the timeline
- L131 _public prototype_ `void OnBarDrag(int32 index, float newPos, bool bInteractive);`

#### class `SAnimationSegmentScrubPanel`  
`class SAnimationSegmentScrubPanel : public SCompoundWidget`  
_L140-193_
- inherits: `SCompoundWidget`
- desc: This is a slimmed down version of SAnimationScrubPanel and has no ties to persona. It would be best to have these inherit from a more generic base class so some functionality could be shared.
- L144 _public function_ `SLATE_BEGIN_ARGS(SAnimationSegmentScrubPanel) : _LockedSequence()`
- L148 _public prototype_ `SLATE_ARGUMENT(UAnimSequenceBase*, LockedSequence) SLATE_ATTRIBUTE(class UAnimSingleNodeInstance*, PreviewInstance) SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax ) SLATE_ARGUMENT( bool, bAllowZoom ) SLATE_ATTRIBUTE( TArray<float>, DraggableBars ) SLATE_EVENT( FOnScrubBarDrag, OnBarDrag ) SLATE_EVENT( FOnScrubBarCommit, OnBarCommit ) SLATE_EVENT( FOnTickPlayback, OnTickPlayback ) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — If you'd like to lock to one asset for this scrub control, give this
- L161 _public prototype_ `virtual ~SAnimationSegmentScrubPanel();`
- L163 _public prototype_ `void ReplaceLockedSequence(class UAnimSequenceBase * NewLockedSequence);`
- L166 _protected member_ `bool bSliderBeingDragged;`
- L167 _protected prototype_ `FReply OnClick_Forward();`
- L170 _protected member_ `TAttribute<class UAnimSingleNodeInstance*> PreviewInstance;`
- L172 _protected prototype_ `void AnimChanged(UAnimationAsset * AnimAsset);`
- L174 _protected prototype_ `void OnValueChanged(float NewValue);`
- L176 _protected prototype_ `void OnBeginSliderMovement();` — make sure viewport is freshes
- L177 _protected prototype_ `void OnEndSliderMovement(float NewValue);`
- L180 _protected prototype_ `EPlaybackMode::Type GetPlaybackMode() const;`
- L181 _protected prototype_ `bool IsRealtimeStreamingMode() const;`
- L183 _protected prototype_ `float GetScrubValue() const;`
- L184 _protected prototype_ `class UAnimSingleNodeInstance* GetPreviewInstance() const;`
- L186 _protected member_ `TSharedPtr<class SScrubControlPanel> ScrubControlPanel;`
- L187 _protected member_ `class UAnimSequenceBase* LockedSequence;`
- L190 _protected prototype_ `bool DoesSyncViewport() const;` — Do I need to sync with viewport?
- L191 _protected prototype_ `uint32 GetNumOfFrames() const;`
- L192 _protected prototype_ `float GetSequenceLength() const;`

#### class `FAnimationSegmentViewportClient`  
`class FAnimationSegmentViewportClient : public FEditorViewportClient`  
_L196-208_
- inherits: `FEditorViewportClient`
- desc: FAnimationSegmentViewportClient
- L199 _public prototype_ `FAnimationSegmentViewportClient(FAdvancedPreviewScene& InPreviewScene, const TWeakPtr<SEditorViewport>& InEditorViewportWidget = nullptr);`
- L202 _public prototype_ `virtual FSceneInterface* GetScene() const override;` — FlEditorViewportClient interface
- L203 _public function_ `virtual FLinearColor GetBackgroundColor() const override`
- L204 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L207 _public prototype_ `void UpdateLighting();`

#### Free symbols / members of external scopes

- L73 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnValueChanged, float, bool);`

### `Source/Editor/DetailCustomizations/Private/AnimSequenceDetails.h` (Private)


#### class `FAnimSequenceDetails`  
`class FAnimSequenceDetails : public IDetailCustomization`  
_L36-95_
- inherits: `IDetailCustomization`
- L40 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L43 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L46 _public prototype_ `void CreateOverridenProperty(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& AdditiveSettingsCategory, TSharedPtr<IPropertyHandle> PropertyHandle, TAttribute<EVisibility> VisibilityAttribute);` — Create an override for the supplide Property
- L49 _public prototype_ `EVisibility ShouldShowRefPoseType() const;` — Functions to control property visibility
- L50 _public prototype_ `EVisibility ShouldShowRefAnimInfo() const;`
- L51 _public prototype_ `EVisibility ShouldShowRefFrameIndex() const;`
- L53 _public prototype_ `virtual ~FAnimSequenceDetails();`
- L57 _private member_ `TWeakObjectPtr<USkeleton> TargetSkeleton;`
- L60 _private member_ `TSharedPtr<IPropertyHandle> AdditiveAnimTypeHandle;` — additive setting handler
- L61 _private member_ `TSharedPtr<IPropertyHandle> RefPoseTypeHandle;`
- L62 _private member_ `TSharedPtr<IPropertyHandle> RefPoseSeqHandle;`
- L63 _private member_ `TSharedPtr<IPropertyHandle> RefFrameIndexHandle;`
- L66 _private member_ `TSharedPtr<IPropertyHandle> RetargetSourceNameHandler;` — retarget source handler
- L67 _private member_ `TSharedPtr<IPropertyHandle> RetargetSourceAssetHandle;`
- L69 _private member_ `TSharedPtr<class SSearchableComboBox> RetargetSourceComboBox;`
- L70 _private member_ `TArray< TSharedPtr< FString > > RetargetSourceComboList;`
- L72 _private prototype_ `TSharedRef<SWidget> MakeRetargetSourceComboWidget( TSharedPtr<FString> InItem );`
- L73 _private prototype_ `void OnRetargetSourceChanged( TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo );`
- L74 _private prototype_ `FText GetRetargetSourceComboBoxContent() const;`
- L75 _private prototype_ `FText GetRetargetSourceComboBoxToolTip() const;`
- L76 _private prototype_ `void OnRetargetSourceComboOpening();`
- L77 _private prototype_ `TSharedPtr<FString> GetRetargetSourceString(FName RetargetSourceName) const;`
- L78 _private prototype_ `EVisibility UpdateRetargetSourceAssetDataVisibility() const;`
- L79 _private prototype_ `FReply UpdateRetargetSourceAssetData();`
- L81 _private member_ `USkeleton::FOnRetargetSourceChanged OnDelegateRetargetSourceChanged;`
- L82 _private member_ `FDelegateHandle OnDelegateRetargetSourceChangedDelegateHandle;`
- L83 _private prototype_ `void RegisterRetargetSourceChanged();`
- L84 _private prototype_ `void DelegateRetargetSourceChanged();`
- L87 _private member_ `TSharedPtr<IPropertyHandle> AnimationTrackNamesHandle;` — *** Animation Track Names ***
- L88 _private member_ `TArray<FName> AnimationTrackNamesList;`
- L89 _private prototype_ `void GenerateAnimationTrackNameArrayElementWidget(TSharedRef<IPropertyHandle> PropertyHandle, int32 ArrayIndex, IDetailChildrenBuilder& ChildrenBuilder, IDetailLayoutBuilder* DetailLayout);`
- L94 _private member_ `TArray< TWeakObjectPtr<UAnimSequence> > SelectedAnimSequences;` — button handler for Apply Compression cache all anim sequences that are selected but I need to know them before compress

#### class `SAnimationRefPoseViewport`  
`class SAnimationRefPoseViewport : public SCompoundWidget`  
_L98-163_
- inherits: `SCompoundWidget`
- L101 _public function_ `SLATE_BEGIN_ARGS( SAnimationRefPoseViewport )`
- L112 _public prototype_ `SAnimationRefPoseViewport();`
- L113 _public prototype_ `virtual ~SAnimationRefPoseViewport();`
- L115 _public prototype_ `void Construct(const FArguments& InArgs);`
- L117 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L118 _public prototype_ `void RefreshViewport();`
- L123 _private prototype_ `void OnTickPreview( double InCurrentTime, float InDeltaTime );` — Called to tick the preview during playback
- L125 _private prototype_ `void InitSkeleton();`
- L127 _private member_ `TSharedPtr<FEditorViewportClient> LevelViewportClient;`
- L129 _private member_ `TSharedPtr<IPropertyHandle> AnimRefPropertyHandle;`
- L130 _private member_ `TSharedPtr<IPropertyHandle> RefPoseTypeHandle;`
- L131 _private member_ `TSharedPtr<IPropertyHandle> RefFrameIndexPropertyHandle;`
- L135 _private member_ `TSharedPtr<SViewport> ViewportWidget;` — TSharedPtr<class FSceneViewport> Viewport;
- L137 _private member_ `TSharedPtr<class FSceneViewport> SceneViewport;`
- L140 _private member_ `USkeleton* TargetSkeleton;` — Skeleton
- L141 _private member_ `UAnimSequence* PreviewAnimationSequence;`
- L143 _private member_ `FAdvancedPreviewScene PreviewScene;`
- L144 _private member_ `class FFXSystemInterface* FXSystem;`
- L146 _private member_ `TSharedPtr<STextBlock> Description;`
- L148 _private member_ `class UDebugSkelMeshComponent* PreviewComponent;`
- L150 _private prototype_ `void CleanupComponent(USceneComponent* Component);`
- L151 _private prototype_ `bool IsVisible() const;`
- L155 _public prototype_ `float GetViewMinInput() const;` — Get Min/Max Input of value
- L156 _public prototype_ `float GetViewMaxInput() const;`
- L158 _public prototype_ `class UAnimSingleNodeInstance* GetPreviewInstance() const;`
- L161 _public prototype_ `TArray<float> GetBars() const;` — Optional, additional values to draw on the timeline
- L162 _public prototype_ `void OnBarDrag(int32 index, float newPos);`

### `Source/Editor/DetailCustomizations/Private/AnimStateAliasNodeDetails.h` (Private)


#### class `FAnimStateAliasNodeDetails`  
`class FAnimStateAliasNodeDetails : public IDetailCustomization`  
_L16-39_
- inherits: `IDetailCustomization`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L27 _private prototype_ `void GetReferenceableStates(const UAnimStateAliasNode& OwningNode, TSet<TWeakObjectPtr<UAnimStateNodeBase>>& OutStates) const;`
- L29 _private prototype_ `bool IsGlobalAlias() const;`
- L30 _private prototype_ `void OnPropertyAliasAllStatesCheckboxChanged(ECheckBoxState NewState);`
- L31 _private prototype_ `ECheckBoxState AreAllStatesAliased() const;`
- L32 _private prototype_ `void OnPropertyIsStateAliasedCheckboxChanged(ECheckBoxState NewState, const TWeakObjectPtr<UAnimStateNodeBase> StateNodeWeak);`
- L33 _private prototype_ `ECheckBoxState IsStateAliased(const TWeakObjectPtr<UAnimStateNodeBase> StateNodeWeak) const;`
- L35 _private prototype_ `void GenerateStatePickerDetails(UAnimStateAliasNode& AliasNode, IDetailLayoutBuilder& DetailBuilder);`
- L37 _private member_ `TWeakObjectPtr<UAnimStateAliasNode> StateAliasNodeWeak;`
- L38 _private member_ `TSet<TWeakObjectPtr<UAnimStateNodeBase>> ReferenceableStates;`

### `Source/Editor/DetailCustomizations/Private/AnimStateNodeDetails.h` (Private)


#### class `FAnimStateNodeDetails`  
`class FAnimStateNodeDetails : public FAnimTransitionNodeDetails`  
_L13-24_
- inherits: `FAnimTransitionNodeDetails`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L23 _private prototype_ `static void AddAnimationStateEventField(const IDetailCategoryBuilder& AnimationStateCategory, IDetailGroup& AnimationStateGroup, const FString& TransitionName);`

### `Source/Editor/DetailCustomizations/Private/AnimTrailNodeDetails.h` (Private)


#### class `FAnimTrailNodeDetails`  
`class FAnimTrailNodeDetails : public IDetailCustomization`  
_L16-48_
- inherits: `IDetailCustomization`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L24 _public prototype_ `virtual void PendingDelete() override;`
- L44 _public member_ `} TrailRelaxCurveEditor;`
- L47 _private member_ `TSharedPtr<class SCurveEditor> TrailRelaxCurveWidget;`

#### struct `FAnimTrailNodeDetails::FTrailRelaxCurveEditor`  
`struct FTrailRelaxCurveEditor: public FCurveOwnerInterface`  
_L26-44_
- inherits: `FCurveOwnerInterface`
- L28 _public prototype_ `FTrailRelaxCurveEditor(UAnimGraphNode_Trail* InGraphNode = nullptr, TSharedPtr<IPropertyHandle> InTrailRelaxCurveHandle = TSharedPtr<IPropertyHandle>());`
- L31 _public prototype_ `virtual TArray<FRichCurveEditInfoConst> GetCurves() const override;` — `UE_DEPRECATED(5.6, "Use version taking a TAdderReserverRef")` — FCurveOwnerInterface interface
- L32 _public prototype_ `virtual void GetCurves(TAdderReserverRef<FRichCurveEditInfoConst> Curves) const override;`
- L33 _public prototype_ `virtual TArray<FRichCurveEditInfo> GetCurves() override;`
- L34 _public prototype_ `virtual void ModifyOwner() override;`
- L35 _public prototype_ `virtual TArray<const UObject*> GetOwners() const override;`
- L36 _public prototype_ `virtual void MakeTransactional() override;`
- L37 _public function_ `virtual void OnCurveChanged(const TArray<FRichCurveEditInfo>& ChangedCurveEditInfos) override`
- L38 _public prototype_ `virtual bool IsValidCurve(FRichCurveEditInfo CurveInfo) override;`
- L41 _private member_ `UAnimGraphNode_Trail* GraphNodeOwner;`
- L42 _private member_ `TSharedPtr<IPropertyHandle> TrailRelaxCurveHandle;`

### `Source/Editor/DetailCustomizations/Private/AnimTransitionNodeDetails.h` (Private)


#### class `FAnimTransitionNodeDetails`  
`class FAnimTransitionNodeDetails : public IDetailCustomization`  
_L27-58_
- inherits: `IDetailCustomization`
- L31 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L34 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L37 _protected prototype_ `static TSharedPtr<IPropertyHandle> GetTransitionEventProperty(const IDetailCategoryBuilder& TransitionCategory, const FString& TransitionName);`
- L38 _protected prototype_ `static void AddTransitionEventField(IDetailCategoryBuilder& TransitionCategory, const FString& TransitionName);`
- L39 _protected prototype_ `static void BuildTransitionEventRow(IDetailPropertyRow& Row, const TSharedPtr<IPropertyHandle>& NameProperty, const FText& InfoText = FText::GetEmpty());`
- L41 _protected prototype_ `FReply OnClickEditBlendGraph();`
- L42 _protected prototype_ `EVisibility GetBlendGraphButtonVisibility(bool bMultiSelect) const;`
- L44 _protected prototype_ `TSharedRef<SWidget> GetWidgetForInlineShareMenu(const TAttribute<FText>& InSharedNameText, const TAttribute<bool>& bInIsCurrentlyShared, FOnClicked PromoteClick, FOnClicked DemoteClick, FOnGetContent GetContentMenu);`
- L46 _protected prototype_ `FReply OnPromoteToSharedClick(bool RuleShare);`
- L47 _protected prototype_ `void PromoteToShared(const FText& NewTransitionName, ETextCommit::Type CommitInfo, bool bRuleShare);`
- L48 _protected prototype_ `FReply OnUnshareClick(bool bUnshareRule);`
- L49 _protected prototype_ `TSharedRef<SWidget> OnGetShareableNodesMenu(bool bShareRules);`
- L50 _protected prototype_ `void BecomeSharedWith(UAnimStateTransitionNode* NewNode, bool bShareRules);`
- L51 _protected prototype_ `void AssignUniqueColorsToAllSharedNodes(UEdGraph* CurrentGraph);`
- L53 _protected prototype_ `void OnBlendProfileChanged(UBlendProfile* NewProfile, TSharedPtr<IPropertyHandle> ProfileProperty);`
- L56 _private member_ `TWeakObjectPtr<UAnimStateTransitionNode> TransitionNode;`
- L57 _private member_ `TSharedPtr<STextEntryPopup> TextEntryWidget;`

### `Source/Editor/DetailCustomizations/Private/AnimationAssetDetails.h` (Private)


#### class `FAnimationAssetDetails`  
`class FAnimationAssetDetails : public IDetailCustomization`  
_L14-31_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L23 _private member_ `TWeakObjectPtr<USkeleton> TargetSkeleton;`
- L26 _private member_ `TSharedPtr<IPropertyHandle> PreviewPoseAssetHandler;` — property handler
- L29 _private prototype_ `void OnPreviewPoseAssetChanged(const FAssetData& AssetData);` — replacing source animation
- L30 _private prototype_ `bool ShouldFilterAsset(const FAssetData& AssetData);`

### `Source/Editor/DetailCustomizations/Private/AssetImportDataCustomization.h` (Private)


#### class `FAssetImportDataCustomization`  
`class FAssetImportDataCustomization : public IPropertyTypeCustomization`  
_L18-66_
- inherits: `IPropertyTypeCustomization`
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L25 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;` — IDetailCustomization interface
- L26 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;`
- L31 _private prototype_ `FReply OnChangePathClicked(int32 Index) const;` — Handle the user wanting to change a specific source path
- L34 _private prototype_ `FReply OnClearPathClicked(int32 Index) const;` — Handle the user requesting that the specified index be cleared
- L36 _private prototype_ `FReply OnClearAllPathsClicked() const;`
- L39 _private prototype_ `FReply OnPropagateFromAbovePathClicked(int32 Index) const;` — Handle the user requesting that the Path use at Index - 1 will be replace the path at Index
- L40 _private prototype_ `bool IsPropagateFromAbovePathEnable(int32 Index) const;`
- L43 _private prototype_ `FReply OnPropagateFromBelowPathClicked(int32 Index) const;` — Handle the user requesting that the Path use at Index + 1 will be replace the path at Index
- L44 _private prototype_ `bool IsPropagateFromBelowPathEnable(int32 Index) const;`
- L47 _private prototype_ `FAssetImportInfo* GetEditStruct() const;` — Access the struct we are editing - returns null if we have more than one.
- L50 _private prototype_ `TArray<FAssetImportInfo*> GetEditStructs() const;` — Access all the structs we are editing
- L53 _private prototype_ `UAssetImportData* GetOuterClass() const;` — Access the outer class that contains this struct
- L55 _private prototype_ `TArray<UAssetImportData*> GetAllAssetImportData() const;`
- L58 _private prototype_ `FText GetFilenameText(int32 Index) const;` — Get text for the UI
- L59 _private prototype_ `FText GetTimestampText(int32 Index) const;`
- L63 _private prototype_ `void PropagatePath(int32 SrcIndex, int32 DstIndex) const;`
- L65 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Property handle of the property we're editing

### `Source/Editor/DetailCustomizations/Private/AssetViewerSettingsCustomization.h` (Private)


#### class `FAssetViewerSettingsCustomization`  
`class FAssetViewerSettingsCustomization : public IDetailCustomization`  
_L19-50_
- inherits: `IDetailCustomization`
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L30 _protected prototype_ `FText OnGetProfileName() const;` — Callbacks for customized SEditableTextBox
- L31 _protected prototype_ `void OnProfileNameChanged(const FText& InNewText);`
- L32 _protected prototype_ `void OnProfileNameCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);`
- L35 _protected prototype_ `const bool IsProfileNameValid(const FString& NewName);` — Check whether or not the given profile name is valid by cross-referencing it with existing names
- L36 _protected prototype_ `bool CanSetSharedProfile() const;`
- L37 _protected prototype_ `EVisibility ShowFileWatcherWidget() const;`
- L38 _protected prototype_ `FString SharedProfileConfigFilePath() const;`
- L41 _private member_ `TSharedPtr<SEditableTextBox> NameEditTextBox;` — Customized name edit text box used for the profile name
- L43 _private member_ `TSharedPtr<IPropertyHandle> NameProperty;` — Cached data
- L45 _private member_ `TSharedPtr<SSettingsEditorCheckoutNotice> FileWatcherWidget;` — Watcher widget for the default config file (checks file status / SCC state).
- L47 _private member_ `int32 ProfileIndex;`
- L48 _private member_ `UAssetViewerSettings* ViewerSettings;`
- L49 _private member_ `bool bValidProfileName;`

### `Source/Editor/DetailCustomizations/Private/AttenuationSettingsCustomizations.h` (Private)


#### class `FBaseAttenuationSettingsCustomization`  
`class FBaseAttenuationSettingsCustomization : public IPropertyTypeCustomization`  
_L12-41_
- inherits: `IPropertyTypeCustomization`
- L16 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L17 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L20 _public prototype_ `TAttribute<bool> IsAttenuationOverriddenAttribute() const;`
- L21 _public prototype_ `TAttribute<EVisibility> IsAttenuationOverriddenVisibleAttribute() const;`
- L25 _protected prototype_ `EVisibility IsSphereSelected() const;`
- L26 _protected prototype_ `EVisibility IsBoxSelected() const;`
- L27 _protected prototype_ `EVisibility IsCapsuleSelected() const;`
- L28 _protected prototype_ `EVisibility IsConeSelected() const;`
- L29 _protected prototype_ `EVisibility IsNaturalSoundSelected() const;`
- L30 _protected prototype_ `EVisibility IsCustomCurveSelected() const;`
- L32 _protected prototype_ `TAttribute<bool> GetIsAttenuationEnabledAttribute() const;`
- L33 _protected prototype_ `TAttribute<bool> GetIsFalloffModeEnabledAttribute() const;`
- L34 _protected prototype_ `TSharedPtr<IPropertyHandle> GetOverrideAttenuationHandle(TSharedRef<IPropertyHandle> StructPropertyHandle);`
- L36 _protected member_ `TSharedPtr<IPropertyHandle> bIsAttenuatedHandle;`
- L37 _protected member_ `TSharedPtr<IPropertyHandle> AttenuationShapeHandle;`
- L38 _protected member_ `TSharedPtr<IPropertyHandle> DistanceAlgorithmHandle;`
- L39 _protected member_ `TSharedPtr<IPropertyHandle> DbAttenuationAtMaxHandle;`
- L40 _protected member_ `TSharedPtr<IPropertyHandle> bOverrideAttenuationHandle;`

#### class `FSoundAttenuationSettingsCustomization`  
`class FSoundAttenuationSettingsCustomization : public FBaseAttenuationSettingsCustomization`  
_L43-88_
- inherits: `FBaseAttenuationSettingsCustomization`
- L46 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L49 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L50 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L55 _protected member_ `TSharedPtr<IPropertyHandle> bIsSpatializedHandle;`
- L56 _protected member_ `TSharedPtr<IPropertyHandle> bIsAirAbsorptionEnabledHandle;`
- L57 _protected member_ `TSharedPtr<IPropertyHandle> bIsFocusedHandle;`
- L58 _protected member_ `TSharedPtr<IPropertyHandle> bIsOcclusionEnabledHandle;`
- L59 _protected member_ `TSharedPtr<IPropertyHandle> bIsReverbSendEnabledHandle;`
- L60 _protected member_ `TSharedPtr<IPropertyHandle> bIsPriorityAttenuationEnabledHandle;`
- L61 _protected member_ `TSharedPtr<IPropertyHandle> bIsSubmixSendAttenuationEnabledHandle;`
- L62 _protected member_ `TSharedPtr<IPropertyHandle> bIsSourceDataOverrideEnabledHandle;`
- L63 _protected member_ `TSharedPtr<IPropertyHandle> bIsSendToAudioLinkEnabledHandle;`
- L64 _protected member_ `TSharedPtr<IPropertyHandle> bEnableSourceDataOverrideHandle;`
- L65 _protected member_ `TSharedPtr<IPropertyHandle> ReverbSendMethodHandle;`
- L66 _protected member_ `TSharedPtr<IPropertyHandle> PriorityAttenuationMethodHandle;`
- L67 _protected member_ `TSharedPtr<IPropertyHandle> AbsorptionMethodHandle;`
- L69 _protected member_ `TAttribute<bool> IsFocusEnabledAttribute;`
- L71 _protected prototype_ `TAttribute<bool> GetIsFocusEnabledAttribute() const;`
- L72 _protected prototype_ `TAttribute<bool> GetIsOcclusionEnabledAttribute() const;`
- L73 _protected prototype_ `TAttribute<bool> GetIsSpatializationEnabledAttribute() const;`
- L74 _protected prototype_ `TAttribute<bool> GetIsAirAbsorptionEnabledAttribute() const;`
- L75 _protected prototype_ `TAttribute<bool> GetIsReverbSendEnabledAttribute() const;`
- L76 _protected prototype_ `TAttribute<bool> GetIsPriorityAttenuationEnabledAttribute() const;`
- L77 _protected prototype_ `TAttribute<bool> GetIsSubmixSendAttenuationEnabledAttribute() const;`
- L79 _protected prototype_ `EVisibility IsLinearMethodSelected() const;`
- L80 _protected prototype_ `EVisibility IsCustomReverbSendCurveSelected() const;`
- L81 _protected prototype_ `EVisibility IsLinearOrCustomReverbMethodSelected() const;`
- L82 _protected prototype_ `EVisibility IsManualReverbSendSelected() const;`
- L83 _protected prototype_ `EVisibility IsCustomAirAbsorptionCurveSelected() const;`
- L84 _protected prototype_ `EVisibility IsPriorityAttenuationLinearMethodSelected() const;`
- L85 _protected prototype_ `EVisibility IsCustomPriorityAttenuationCurveSelected() const;`
- L86 _protected prototype_ `EVisibility IsLinearOrCustomPriorityAttenuationSelected() const;`
- L87 _protected prototype_ `EVisibility IsManualPriorityAttenuationSelected() const;`

#### class `FForceFeedbackAttenuationSettingsCustomization`  
`class FForceFeedbackAttenuationSettingsCustomization : public FBaseAttenuationSettingsCustomization`  
_L90-99_
- inherits: `FBaseAttenuationSettingsCustomization`
- L93 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L96 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L97 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Source/Editor/DetailCustomizations/Private/AudioSettingsDetails.h` (Private)


#### class `FAudioSettingsDetails`  
`class FAudioSettingsDetails : public IDetailCustomization`  
_L12-25_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L22 _private prototype_ `FText GetExampleDialogueFilename() const;`
- L24 _private member_ `TSharedPtr<IPropertyHandle> DialogueFilenameFormatProperty;`

### `Source/Editor/DetailCustomizations/Private/AutoReimportDirectoryCustomization.h` (Private)


#### class `FAutoReimportWildcardCustomization`  
`class FAutoReimportWildcardCustomization : public IPropertyTypeCustomization`  
_L21-48_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details view customization for the FAutoReimportDirectoryConfig struct.
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;`
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;`
- L31 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()` — Creates an instance of this class.
- L38 _private prototype_ `FText GetWildcardText() const;`
- L39 _private prototype_ `void OnWildcardCommitted(const FText& InValue, ETextCommit::Type CommitType);`
- L40 _private prototype_ `void OnWildcardChanged(const FText& InValue);`
- L42 _private prototype_ `void OnCheckStateChanged(ECheckBoxState InState);`
- L43 _private prototype_ `ECheckBoxState GetCheckState() const;`
- L45 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L46 _private member_ `TSharedPtr<IPropertyHandle> WildcardProperty;`
- L47 _private member_ `TSharedPtr<IPropertyHandle> IncludeProperty;`

#### class `FAutoReimportDirectoryCustomization`  
`class FAutoReimportDirectoryCustomization : public IPropertyTypeCustomization`  
_L53-91_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details view customization for the FAutoReimportDirectoryConfig struct.
- L57 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;`
- L58 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;`
- L63 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()` — Creates an instance of this class.
- L71 _private prototype_ `EVisibility GetMountPathVisibility() const;`
- L73 _private prototype_ `FText GetDirectoryText() const;`
- L74 _private prototype_ `void OnDirectoryCommitted(const FText& InValue, ETextCommit::Type CommitType);`
- L75 _private prototype_ `void OnDirectoryChanged(const FText& InValue);`
- L77 _private prototype_ `FText GetMountPointText() const;`
- L79 _private prototype_ `void SetSourcePath(const FString& InSourceDir);`
- L80 _private prototype_ `FReply BrowseForFolder();`
- L82 _private prototype_ `TSharedRef<class SWidget> GetPathPickerContent();`
- L83 _private prototype_ `void PathPickerPathSelected(const FString& FolderPath);`
- L85 _private member_ `EVisibility MountPathVisibility;`
- L86 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L87 _private member_ `TSharedPtr<IPropertyHandle> SourceDirProperty;`
- L88 _private member_ `TSharedPtr<IPropertyHandle> MountPointProperty;`
- L89 _private member_ `TSharedPtr<IPropertyHandle> WildcardsProperty;`
- L90 _private member_ `TSharedPtr<class SComboButton> PathPickerButton;`

### `Source/Editor/DetailCustomizations/Private/BlackboardEntryDetails.h` (Private)


#### class `FBlackboardEntryDetails`  
`class FBlackboardEntryDetails : public IPropertyTypeCustomization`  
_L10-25_
- inherits: `IPropertyTypeCustomization`
- L14 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L18 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L22 _private member_ `TSharedPtr<IPropertyHandle> MyNameProperty;`
- L23 _private member_ `TSharedPtr<IPropertyHandle> MyDescriptionProperty;`
- L24 _private member_ `TSharedPtr<IPropertyHandle> MyValueProperty;`

### `Source/Editor/DetailCustomizations/Private/BodyInstanceCustomization.h` (Private)


#### struct `FCollisionChannelInfo`  
`struct FCollisionChannelInfo`  
_L42-47_
- L44 _public member_ `FString DisplayName;`
- L45 _public member_ `ECollisionChannel CollisionChannel;`
- L46 _public member_ `bool TraceType;`

#### class `FBodyInstanceCustomization`  
`class FBodyInstanceCustomization : public IPropertyTypeCustomization`  
_L52-155_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes a DataTable asset to use a dropdown
- L55 _public prototype_ `FBodyInstanceCustomization();`
- L57 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L63 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L64 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L69 _private prototype_ `void OnSimulatePhysicsChanged();` — Simulate physics toggle
- L72 _private prototype_ `TSharedRef<SWidget> MakeCollisionProfileComboWidget( TSharedPtr<FString> InItem );` — Profile combo related
- L73 _private prototype_ `void OnCollisionProfileChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L74 _private prototype_ `FText GetCollisionProfileComboBoxContent() const;`
- L75 _private prototype_ `FText GetCollisionProfileComboBoxToolTip() const;`
- L76 _private prototype_ `void OnCollisionProfileComboOpening();`
- L79 _private prototype_ `TSharedRef<SWidget> MakeObjectTypeComboWidget(TSharedPtr<FString> InItem);` — Movement channel related
- L80 _private prototype_ `void OnObjectTypeChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L81 _private prototype_ `FText GetObjectTypeComboBoxContent() const;`
- L82 _private prototype_ `int32 InitializeObjectTypeComboList();`
- L85 _private prototype_ `void SetToDefaultProfile();` — set to default for profile setting
- L86 _private prototype_ `bool ShouldShowResetToDefaultProfile() const;`
- L88 _private prototype_ `void SetToDefaultResponse(int32 ValidIndex);`
- L89 _private prototype_ `bool ShouldShowResetToDefaultResponse(int32 ValidIndex) const;`
- L92 _private prototype_ `void OnCollisionChannelChanged(ECheckBoxState InNewValue, int32 ValidIndex, ECollisionResponse InCollisionResponse);` — collision channel check boxes
- L93 _private prototype_ `ECheckBoxState IsCollisionChannelChecked( int32 ValidIndex, ECollisionResponse InCollisionResponse) const;`
- L95 _private prototype_ `void OnAllCollisionChannelChanged(ECheckBoxState InNewValue, ECollisionResponse InCollisionResponse);` — all collision channel check boxes
- L96 _private prototype_ `ECheckBoxState IsAllCollisionChannelChecked(ECollisionResponse InCollisionResponse) const;`
- L99 _private prototype_ `bool ShouldEnableCustomCollisionSetup() const;` — should show custom prop
- L100 _private prototype_ `EVisibility ShouldShowCustomCollisionSetup() const;`
- L102 _private prototype_ `bool IsCollisionEnabled() const;`
- L105 _private prototype_ `bool AreAllCollisionUsingDefault() const;` — whether we can edit collision or if we're getting it from a default
- L108 _private prototype_ `void CreateCustomCollisionSetup(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder);` — utility functions between property and struct
- L109 _private prototype_ `void SetCollisionResponseContainer(const FCollisionResponseContainer& ResponseContainer);`
- L110 _private prototype_ `void SetResponse(int32 ValidIndex, ECollisionResponse InCollisionResponse);`
- L111 _private prototype_ `void UpdateCollisionProfile();`
- L112 _private prototype_ `TSharedPtr<FString> GetProfileString(FName ProfileName) const;`
- L114 _private prototype_ `void UpdateValidCollisionChannels();`
- L116 _private prototype_ `void RefreshCollisionProfiles();`
- L118 _private prototype_ `UStaticMeshComponent* GetDefaultCollisionProvider(const FBodyInstance* BI) const;`
- L119 _private prototype_ `void MarkAllBodiesDefaultCollision(bool bUseDefaultCollision);`
- L120 _private prototype_ `bool CanUseDefaultCollision() const;`
- L121 _private prototype_ `bool CanShowDefaultCollision() const;`
- L122 _private prototype_ `int32 GetNumberOfSpecialProfiles() const;`
- L123 _private prototype_ `int32 GetCustomIndex() const;`
- L124 _private prototype_ `int32 GetDefaultIndex() const;`
- L128 _private member_ `TSharedPtr<IPropertyHandle> BodyInstanceHandle;` — property handles
- L129 _private member_ `TSharedPtr<IPropertyHandle> CollisionProfileNameHandle;`
- L130 _private member_ `TSharedPtr<IPropertyHandle> CollisionEnabledHandle;`
- L131 _private member_ `TSharedPtr<IPropertyHandle> ObjectTypeHandle;`
- L132 _private member_ `TSharedPtr<IPropertyHandle> CollisionResponsesHandle;`
- L133 _private member_ `TSharedPtr<IPropertyHandle> UseDefaultCollisionHandle;`
- L134 _private member_ `TSharedPtr<IPropertyHandle> StaticMeshHandle;`
- L137 _private member_ `TSharedPtr<class SComboBox<TSharedPtr<FString>>> CollisionProfileComboBox;` — widget related variables
- L138 _private member_ `TArray<TSharedPtr<FString>> CollisionProfileComboList;`
- L141 _private member_ `TSharedPtr<class SComboBox<TSharedPtr<FString>>> ObjectTypeComboBox;` — movement channel related options
- L142 _private member_ `TArray<TSharedPtr<FString>> ObjectTypeComboList;`
- L144 _private member_ `TArray<ECollisionChannel> ObjectTypeValues;` — matching ObjectType value to ComboList, technically you can search DisplayName all the time, but this seems just easier
- L147 _private member_ `UCollisionProfile* CollisionProfile;` — default collision profile object
- L149 _private member_ `TArray<FBodyInstance*> BodyInstances;`
- L150 _private member_ `TArray<UPrimitiveComponent*> PrimComponents;`
- L151 _private member_ `TMap<FBodyInstance*, TWeakObjectPtr<UPrimitiveComponent>> BodyInstanceToPrimComponent;`
- L153 _private member_ `TArray<FCollisionChannelInfo> ValidCollisionChannels;`
- L154 _private member_ `IDetailLayoutBuilder* DetailBuilder = nullptr;`

#### class `FBodyInstanceCustomizationHelper`  
`class FBodyInstanceCustomizationHelper : public TSharedFromThis<FBodyInstanceCustomizationHelper>`  
_L157-205_
- inherits: `TSharedFromThis<FBodyInstanceCustomizationHelper>`
- L160 _public prototype_ `FBodyInstanceCustomizationHelper(const TArray<TWeakObjectPtr<UObject>>& InObjectsCustomized);`
- L161 _public prototype_ `void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder, TSharedRef<IPropertyHandle> BodyInstanceHandler);`
- L162 _public prototype_ `void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder, TSharedRef<IPropertyHandle> BodyInstanceHandler, TFunction<void(TSharedRef<IPropertyHandle>)> CustomizeCoMNudge);`
- L165 _private prototype_ `void UpdateFilters();`
- L166 _private prototype_ `bool IsSimulatePhysicsEditable() const;`
- L168 _private prototype_ `TOptional<float> OnGetBodyMass() const;`
- L169 _private prototype_ `void OnSetBodyMass(float InBodyMass, ETextCommit::Type Commit);`
- L170 _private prototype_ `bool IsBodyMassReadOnly() const;`
- L171 _private prototype_ `EVisibility IsMassVisible(bool bOverrideMass) const;`
- L172 _private function_ `bool IsBodyMassEnabled() const`
- L173 _private prototype_ `void AddMassInKg(IDetailCategoryBuilder& PhysicsCategory, TSharedRef<IPropertyHandle> BodyInstanceHandler);`
- L174 _private prototype_ `void AddBodyConstraint(IDetailCategoryBuilder& PhysicsCategory, TSharedRef<IPropertyHandle> BodyInstanceHandler);`
- L175 _private prototype_ `void AddMaxAngularVelocity(IDetailCategoryBuilder& PhysicsCategory, TSharedRef<IPropertyHandle> BodyInstanceHandler);`
- L177 _private prototype_ `EVisibility IsAutoWeldVisible() const;`
- L179 _private prototype_ `EVisibility IsMaxAngularVelocityVisible(bool bOverrideMaxAngularVelocity) const;`
- L180 _private prototype_ `TOptional<float> OnGetBodyMaxAngularVelocity() const;`
- L182 _private prototype_ `bool IsMaxAngularVelocityReadOnly() const;`
- L183 _private prototype_ `EVisibility IsDOFMode(EDOFMode::Type Mode) const;`
- L186 _private member_ `bool bDisplayMass;`
- L187 _private member_ `bool bDisplayConstraints;`
- L188 _private member_ `bool bDisplayEnablePhysics;`
- L189 _private member_ `bool bDisplayAsyncScene;`
- L190 _private member_ `bool bDisplayLinearDamping;`
- L191 _private member_ `bool bDisplayAngularDamping;`
- L192 _private member_ `bool bDisplayEnableGravity;`
- L193 _private member_ `bool bDisplayInertiaConditioning;`
- L194 _private member_ `bool bDisplayInitialOverlapDepenetration;`
- L195 _private member_ `bool bDisplayWalkableSlopeOverride;`
- L196 _private member_ `bool bDisplayAutoWeld;`
- L197 _private member_ `bool bDisplayStartAwake;`
- L198 _private member_ `bool bDisplayCOMNudge;`
- L199 _private member_ `bool bDisplayMassScale;`
- L200 _private member_ `bool bDisplayMaxAngularVelocity;`
- L202 _private member_ `TSharedPtr<IPropertyHandle> MassInKgOverrideHandle;`
- L203 _private member_ `TSharedPtr<IPropertyHandle> DOFModeProperty;`
- L204 _private member_ `TArray<TWeakObjectPtr<UObject>> ObjectsCustomized;`

### `Source/Editor/DetailCustomizations/Private/BodySetupDetails.h` (Private)


#### class `FBodySetupDetails`  
`class FBodySetupDetails : public IDetailCustomization`  
_L17-35_
- inherits: `IDetailCustomization`
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L24 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L26 _public function_ `virtual void CustomizeCoMNudge(IDetailLayoutBuilder& DetailBuilder, TSharedRef<IPropertyHandle> BodyInstanceHandler)`
- L29 _private prototype_ `void AddPhysicalAnimation(IDetailLayoutBuilder& DetailBuilder);`
- L32 _private member_ `TSharedPtr<class FBodyInstanceCustomizationHelper> BodyInstanceCustomizationHelper;`
- L33 _private member_ `TArray< TWeakObjectPtr<UObject> > ObjectsCustomized;`
- L34 _private member_ `TSharedPtr<IPropertyHandle> CollisionReponseHandle;`

#### class `FSkeletalBodySetupDetails`  
`class FSkeletalBodySetupDetails : public IDetailCustomization`  
_L39-50_
- inherits: `IDetailCustomization`
- L43 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L46 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L49 _private member_ `TArray< TWeakObjectPtr<UObject> > ObjectsCustomized;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DETAILCUSTOMIZATIONS_API`

### `Source/Editor/DetailCustomizations/Private/BoundsCopyComponentDetails.h` (Private)


#### class `FBoundsCopyComponentDetailsCustomization`  
`class FBoundsCopyComponentDetailsCustomization : public IDetailCustomization`  
_L18-46_
- inherits: `IDetailCustomization`
- desc: UI customization for UBoundsCopyComponent
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L24 _protected prototype_ `FBoundsCopyComponentDetailsCustomization();`
- L27 _protected prototype_ `FReply SetRotation();` — Callback for Copy Rotation button
- L29 _protected prototype_ `FReply SetTransformToBounds();` — Callback for Copy Bounds button
- L32 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L36 _private prototype_ `void OnBoundsComponentsXChanged(ECheckBoxState NewState);`
- L37 _private prototype_ `void OnBoundsComponentsYChanged(ECheckBoxState NewState);`
- L38 _private prototype_ `void OnBoundsComponentsZChanged(ECheckBoxState NewState);`
- L39 _private prototype_ `ECheckBoxState IsBoundsComponentsXChecked() const;`
- L40 _private prototype_ `ECheckBoxState IsBoundsComponentsYChecked() const;`
- L41 _private prototype_ `ECheckBoxState IsBoundsComponentsZChecked() const;`
- L42 _private prototype_ `bool IsCopyEnabled() const;`
- L45 _private member_ `TWeakObjectPtr<UBoundsCopyComponent> BoundsCopyComponent;`

### `Source/Editor/DetailCustomizations/Private/BrushDetails.h` (Private)


#### class `FBrushDetails`  
`class FBrushDetails : public IDetailCustomization`  
_L21-54_
- inherits: `IDetailCustomization`
- L25 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L27 _public prototype_ `~FBrushDetails();`
- L30 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& InDetailLayout ) override;` — IDetailCustomization interface
- L34 _private prototype_ `FReply OnCreateStaticMesh();` — Callback for creating a static mesh from valid selected brushes.
- L36 _private prototype_ `FReply ExecuteExecCommand(FString InCommand);`
- L38 _private prototype_ `TSharedRef<SWidget> GenerateBuildMenuContent();`
- L40 _private prototype_ `void OnClassPicked(UClass* InChosenClass);`
- L42 _private prototype_ `FText GetBuilderText() const;`
- L45 _private member_ `TSharedPtr<IPropertyHandle> BrushBuilderHandle;`
- L48 _private member_ `TArray< TWeakObjectPtr<ABrush> > SelectedBrushes;` — Holds a list of BSP brushes or volumes, used for converting to static meshes
- L51 _private member_ `TSharedPtr< SHorizontalBox > GeometryToolsContainer;` — Container widget for the geometry mode tools
- L53 _private member_ `TWeakPtr<IPropertyUtilities> PropertyUtils;`

### `Source/Editor/DetailCustomizations/Private/CameraCropSettingsCustomization.h` (Private)


#### class `FCameraCropSettingsCustomization`  
`class FCameraCropSettingsCustomization : public IPropertyTypeCustomization`  
_L13-39_
- inherits: `IPropertyTypeCustomization`
- L16 _public prototype_ `FCameraCropSettingsCustomization();`
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization instance
- L22 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L26 _protected member_ `TSharedPtr<IPropertyHandle> AspectRatioHandle;`
- L28 _protected member_ `TSharedPtr<class SComboBox< TSharedPtr<FString> > > PresetComboBox;`
- L29 _protected member_ `TArray< TSharedPtr< FString > > PresetComboList;`
- L31 _protected prototype_ `bool IsPresetEnabled() const;`
- L32 _protected prototype_ `void OnPresetChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L33 _protected prototype_ `TSharedRef<SWidget> MakePresetComboWidget(TSharedPtr<FString> InItem);`
- L35 _protected prototype_ `FText GetPresetComboBoxContent() const;`
- L36 _protected prototype_ `TSharedPtr<FString> GetPresetString() const;`

### `Source/Editor/DetailCustomizations/Private/CameraDetails.h` (Private)


#### class `FCameraDetails`  
`class FCameraDetails : public IDetailCustomization`  
_L18-46_
- inherits: `IDetailCustomization`
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L25 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L28 _private prototype_ `void OnAspectRatioChanged();`
- L29 _private prototype_ `TOptional<float> GetAspectRatio() const;`
- L30 _private prototype_ `void OnAspectRatioSpinnerChanged(float InValue);`
- L31 _private prototype_ `void UpdateAspectTextFromProperty();`
- L32 _private prototype_ `TSharedRef<SWidget> OnGetComboContent() const;`
- L33 _private prototype_ `void CommitAspectRatioText(FText ItemText);`
- L34 _private prototype_ `void OnCommitAspectRatioText(const FText& ItemFText, ETextCommit::Type CommitInfo);`
- L36 _private prototype_ `EVisibility ProjectionModeMatches(TSharedPtr<IPropertyHandle> Property, ECameraProjectionMode::Type DesiredMode) const;`
- L38 _private member_ `TSharedPtr<IPropertyHandle> AspectRatioProperty;`
- L39 _private member_ `TSharedPtr<SEditableTextBox> AspectTextBox;`
- L40 _private member_ `float LastParsedAspectRatioValue;`
- L42 _private member_ `static const float MinAspectRatio;`
- L43 _private member_ `static const float MaxAspectRatio;`
- L44 _private member_ `static const float LowestCommonAspectRatio;`
- L45 _private member_ `static const float HighestCommonAspectRatio;`

### `Source/Editor/DetailCustomizations/Private/CameraFilmbackSettingsCustomization.h` (Private)


#### class `FCameraFilmbackSettingsCustomization`  
`class FCameraFilmbackSettingsCustomization : public IPropertyTypeCustomization`  
_L26-55_
- inherits: `IPropertyTypeCustomization`
- L29 _public prototype_ `FCameraFilmbackSettingsCustomization();`
- L31 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L34 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization instance
- L35 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L39 _protected member_ `TSharedPtr<IPropertyHandle> SensorWidthHandle;`
- L40 _protected member_ `TSharedPtr<IPropertyHandle> SensorHeightHandle;`
- L41 _protected member_ `TSharedPtr<IPropertyHandle> SensorHorizontalOffsetHandle;`
- L42 _protected member_ `TSharedPtr<IPropertyHandle> SensorVerticalOffsetHandle;`
- L44 _protected member_ `TSharedPtr<class SComboBox< TSharedPtr<FString> > > PresetComboBox;`
- L45 _protected member_ `TArray< TSharedPtr< FString > > PresetComboList;`
- L47 _protected prototype_ `void BuildPresetComboList();`
- L49 _protected prototype_ `bool IsPresetEnabled() const;`
- L50 _protected prototype_ `void OnPresetChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L51 _protected prototype_ `TSharedRef<SWidget> MakePresetComboWidget(TSharedPtr<FString> InItem);`
- L53 _protected prototype_ `FText GetPresetComboBoxContent() const;`
- L54 _protected prototype_ `TSharedPtr<FString> GetPresetString() const;`

### `Source/Editor/DetailCustomizations/Private/CameraFocusSettingsCustomization.h` (Private)


#### class `FCameraFocusSettingsCustomization`  
`class FCameraFocusSettingsCustomization : public IPropertyTypeCustomization`  
_L13-33_
- inherits: `IPropertyTypeCustomization`
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization instance
- L20 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L23 _protected member_ `TSharedPtr<IPropertyHandle> FocusMethodHandle;`
- L24 _protected member_ `TSharedPtr<IPropertyHandle> ManualFocusDistanceHandle;`
- L27 _private prototype_ `EVisibility IsManualSettingGroupVisible() const;`
- L28 _private prototype_ `EVisibility IsSpotSettingGroupVisible() const;`
- L29 _private prototype_ `EVisibility IsTrackingSettingGroupVisible() const;`
- L30 _private prototype_ `EVisibility IsGeneralSettingGroupVisible() const;`
- L32 _private prototype_ `void OnSceneDepthLocationSelected(FVector PickedSceneLoc);`

### `Source/Editor/DetailCustomizations/Private/CameraLensSettingsCustomization.h` (Private)


#### class `FCameraLensSettingsCustomization`  
`class FCameraLensSettingsCustomization : public IPropertyTypeCustomization`  
_L26-60_
- inherits: `IPropertyTypeCustomization`
- L29 _public prototype_ `FCameraLensSettingsCustomization();`
- L31 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L34 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization instance
- L35 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L39 _protected member_ `TSharedPtr<IPropertyHandle> MinFocalLengthHandle;`
- L40 _protected member_ `TSharedPtr<IPropertyHandle> MaxFocalLengthHandle;`
- L41 _protected member_ `TSharedPtr<IPropertyHandle> MinFStopHandle;`
- L42 _protected member_ `TSharedPtr<IPropertyHandle> MaxFStopHandle;`
- L43 _protected member_ `TSharedPtr<IPropertyHandle> MinFocusDistanceHandle;`
- L44 _protected member_ `TSharedPtr<IPropertyHandle> SqueezeFactorHandle;`
- L45 _protected member_ `TSharedPtr<IPropertyHandle> DiaphragmBladeCountHandle;`
- L47 _protected member_ `TSharedPtr<class SComboBox< TSharedPtr<FString> > > PresetComboBox;`
- L48 _protected member_ `TArray< TSharedPtr< FString > > PresetComboList;`
- L50 _protected prototype_ `void BuildPresetComboList();`
- L52 _protected prototype_ `bool IsPresetEnabled() const;`
- L53 _protected prototype_ `void OnPresetChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L54 _protected prototype_ `TSharedRef<SWidget> MakePresetComboWidget(TSharedPtr<FString> InItem);`
- L56 _protected prototype_ `FText GetPresetComboBoxContent() const;`
- L57 _protected prototype_ `TSharedPtr<FString> GetPresetString() const;`

### `Source/Editor/DetailCustomizations/Private/CaptureResolutionCustomization.h` (Private)


#### class `FCaptureResolutionCustomization`  
`class FCaptureResolutionCustomization : public IPropertyTypeCustomization`  
_L18-53_
- inherits: `IPropertyTypeCustomization`
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L25 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;` — IDetailCustomization interface
- L26 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;`
- L31 _private prototype_ `void UpdateProperty();` — Respond to a selection change event from the combo box
- L41 _private member_ `TArray<TSharedPtr<FPredefinedResolution>> Resolutions;`
- L44 _private member_ `int32 CurrentIndex;` — The index of the resolution we're currently displaying
- L46 _private member_ `TSharedPtr<STextBlock> CurrentText;` — The text of the current selection
- L48 _private member_ `TSharedPtr<SWidget> CustomSliders;` — The custom sliders to be hidden and shown based on combo box selection
- L51 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Property handles of the properties we're editing
- L52 _private member_ `TSharedPtr<IPropertyHandle> ResXHandle, ResYHandle;`
- L52 _private member_ `TSharedPtr<IPropertyHandle> ResXHandle, ResYHandle;`

#### struct `FCaptureResolutionCustomization::FPredefinedResolution`  
`struct FPredefinedResolution`  
_L36-40_
- desc: Array of predefined resolutions
- L38 _public member_ `FText DisplayName;`
- L39 _public member_ `uint32 ResX, ResY;`
- L39 _public member_ `uint32 ResX, ResY;`

### `Source/Editor/DetailCustomizations/Private/CollectionReferenceStructCustomization.h` (Private)


#### class `FCollectionReferenceStructCustomization`  
`class FCollectionReferenceStructCustomization: public IPropertyTypeCustomization`  
_L15-41_
- inherits: `IPropertyTypeCustomization`
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L21 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L23 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L28 _private prototype_ `FText GetDisplayedText(TSharedRef<IPropertyHandle> PropertyHandle) const;` — Delegate for displaying text value of path
- L31 _private prototype_ `FReply OnPickContent(TSharedRef<IPropertyHandle> PropertyHandle) ;` — Delegate used to display a directory picker
- L34 _private prototype_ `void OnCollectionPicked(const FCollectionNameType& CollectionType, TSharedRef<IPropertyHandle> PropertyHandle);` — Called when a path is picked from the path picker
- L37 _private member_ `TSharedPtr<SButton> PickerButton;` — The pick button widget
- L40 _private member_ `TSharedPtr<IMenu> PickerMenu;` — The pick button popup menu

### `Source/Editor/DetailCustomizations/Private/CollisionProfileDetails.h` (Private)


#### class `FChannelListItem`  
`class FChannelListItem`  
_L32-44_
- desc: Class containing the friend information - used to build the list view
- L39 _public function_ `FChannelListItem(TSharedPtr<FCustomChannelSetup> InChannelSetup) : ChannelSetup(InChannelSetup)` — Constructor takes the required details
- L43 _public member_ `TSharedPtr<FCustomChannelSetup> ChannelSetup;`

#### class `SChannelListItem`  
`class SChannelListItem : public SMultiColumnTableRow< TSharedPtr<class FChannelListItem> >`  
_L49-75_
- inherits: `SMultiColumnTableRow<TSharedPtr<classFChannelListItem>>`
- desc: Implements the FriendsList
- L54 _public function_ `SLATE_BEGIN_ARGS(SChannelListItem)`
- L67 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);` — Constructs the application. @param InArgs - The Slate argument list.
- L68 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L72 _private prototype_ `FText GetDefaultResponse() const;`
- L74 _private member_ `TSharedPtr<FCustomChannelSetup> ChannelSetup;`

#### class `FProfileListItem`  
`class FProfileListItem`  
_L79-91_
- desc: Class containing the friend information - used to build the list view
- L86 _public function_ `FProfileListItem(TSharedPtr<FCollisionResponseTemplate> InProfileTemplate) : ProfileTemplate(InProfileTemplate)` — Constructor takes the required details
- L90 _public member_ `TSharedPtr<FCollisionResponseTemplate> ProfileTemplate;`

#### class `SProfileListItem`  
`class SProfileListItem : public SMultiColumnTableRow< TSharedPtr<class FProfileListItem> >`  
_L96-122_
- inherits: `SMultiColumnTableRow<TSharedPtr<classFProfileListItem>>`
- desc: Implements the FriendsList
- L101 _public function_ `SLATE_BEGIN_ARGS(SProfileListItem)`
- L114 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);` — Constructs the application. @param InArgs - The Slate argument list.
- L115 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L119 _private prototype_ `FText GetObjectType() const;`
- L120 _private prototype_ `FText GetCollsionEnabled() const;`
- L121 _private member_ `TSharedPtr<FCollisionResponseTemplate> ProfileTemplate;`

#### class `FCollisionProfileDetails`  
`class FCollisionProfileDetails : public IDetailCustomization`  
_L127-202_
- inherits: `IDetailCustomization`
- L131 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L134 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L144 _private prototype_ `TSharedRef<ITableRow> HandleGenerateChannelWidget(TSharedPtr< FChannelListItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a widget for a channel item. @param InItem - the ChannelListItem @param OwnerTable - the owning table @return The table row widget
- L146 _private prototype_ `TSharedRef<ITableRow> HandleGenerateProfileWidget(TSharedPtr< FProfileListItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L149 _private prototype_ `FReply OnNewChannel(bool bTraceType);` — button handlers
- L150 _private prototype_ `bool IsNewChannelAvailable() const;`
- L151 _private prototype_ `FReply OnEditChannel(bool bTraceType);`
- L152 _private prototype_ `bool IsAnyChannelSelected(bool bTraceType) const;`
- L153 _private prototype_ `FReply OnDeleteChannel(bool bTraceType);`
- L154 _private prototype_ `bool IsValidChannelSetup(const FCustomChannelSetup* Channel) const;`
- L156 _private prototype_ `FReply OnNewProfile();`
- L157 _private prototype_ `FReply OnEditProfile();`
- L158 _private prototype_ `FReply OnDeleteProfile();`
- L159 _private prototype_ `bool IsAnyProfileSelected() const;`
- L160 _private prototype_ `bool IsValidProfileSetup(const FCollisionResponseTemplate* Template, int32 ProfileIndex) const;`
- L163 _private member_ `TSharedPtr<SChannelListView> ObjectChannelListView;`
- L164 _private member_ `TArray< TSharedPtr< FChannelListItem > > ObjectChannelList;`
- L166 _private member_ `TSharedPtr<SChannelListView> TraceChannelListView;`
- L167 _private member_ `TArray< TSharedPtr< FChannelListItem > > TraceChannelList;`
- L169 _private member_ `TSharedPtr<SProfileListView> ProfileListView;`
- L170 _private member_ `TArray< TSharedPtr< FProfileListItem > > ProfileList;`
- L172 _private member_ `UCollisionProfile * CollisionProfile;`
- L175 _private prototype_ `ECollisionChannel FindAvailableChannel() const;` — functions
- L176 _private prototype_ `void UpdateChannel(bool bTraceType);`
- L177 _private prototype_ `void UpdateProfile();`
- L178 _private prototype_ `void CommitProfileChange(int32 ProfileIndex, FCollisionResponseTemplate & NewProfile);`
- L179 _private prototype_ `void RefreshChannelList(bool bTraceType);`
- L180 _private prototype_ `void RefreshProfileList();`
- L181 _private prototype_ `FCustomChannelSetup * FindFromChannel(ECollisionChannel CollisionChannel) const;`
- L182 _private prototype_ `void RemoveChannel(ECollisionChannel CollisionChannel) const;`
- L184 _private prototype_ `int32 FindProfileIndexFromName(FName Name) const;`
- L186 _private prototype_ `void OnObjectChannelListItemDoubleClicked(TSharedPtr< FChannelListItem >);`
- L187 _private prototype_ `void OnTraceChannelListItemDoubleClicked(TSharedPtr< FChannelListItem >);`
- L188 _private prototype_ `void OnProfileListItemDoubleClicked(TSharedPtr< FProfileListItem >);`
- L201 _private member_ `FCollisionProfileData SavedData;`

#### struct `FCollisionProfileDetails::FCollisionProfileData`  
`struct FCollisionProfileData`  
_L192-199_
- desc: this is the data that saves before starting, and creates the EditProfiles based on that. this is needed if we do EditProfiles
- L194 _public member_ `TArray<FCollisionResponseTemplate> Profiles;`
- L195 _public member_ `TArray<FCustomChannelSetup> DefaultChannelResponses;`
- L196 _public member_ `TArray<FCustomProfile> EditProfiles;`
- L198 _public prototype_ `void Save(UCollisionProfile * Profile);`

#### Free symbols / members of external scopes

- L124 _typedef_ `typedef SListView< TSharedPtr< FChannelListItem > > SChannelListView;`
- L125 _typedef_ `typedef SListView< TSharedPtr< FProfileListItem > > SProfileListView;`

### `Source/Editor/DetailCustomizations/Private/CollisionProfileNameCustomization.h` (Private)


#### class `FCollisionProfileNameCustomization`  
`class FCollisionProfileNameCustomization : public IPropertyTypeCustomization`  
_L29-61_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes a CollisionProfileName property to use a dropdown
- L33 _public prototype_ `FCollisionProfileNameCustomization();`
- L35 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L38 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L39 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L43 _protected prototype_ `TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<FName> InItem);`
- L45 _protected prototype_ `void OnSelectionChanged(TSharedPtr<FName> NameItem, ESelectInfo::Type SelectInfo, IDetailGroup* CollisionGroup);`
- L46 _protected prototype_ `void OnComboBoxOpening();`
- L48 _protected prototype_ `TSharedPtr<FName> GetSelectedName() const;`
- L50 _protected prototype_ `void SetPropertyWithName(const FName& Name);`
- L51 _protected prototype_ `void GetPropertyAsName(FName& OutName) const;`
- L53 _protected prototype_ `FText GetProfileComboBoxContent() const;`
- L54 _protected prototype_ `FText GetProfileComboBoxToolTip() const;`
- L58 _protected member_ `TSharedPtr<IPropertyHandle> NameHandle;`
- L59 _protected member_ `TArray<TSharedPtr<FName>> NameList;`
- L60 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<FName>>> NameComboBox;`

### `Source/Editor/DetailCustomizations/Private/ColorGradingSettingsCustomization.h` (Private)


#### class `FColorGradingSettingsCustomization`  
`class FColorGradingSettingsCustomization : public IPropertyTypeCustomization`  
_L12-45_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details view customization for the FColorGradingSettings structure.
- L15 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L22 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L23 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L32 _private prototype_ `void GetPropertyGroups(TSharedRef<IPropertyHandle> PropertyHandle, TMap<FName, FString>& OutPropertyGroupMap, TSet<FString>& OutGroupSet);` — Iterates the property's children and finds all child properties that have a subcategory and need a group made for them @param PropertyHandle The property handle being customized @param OutPropertyGroupMap A map of properties and the group they want to be in @param OutGroupSet The set of all groups that need to be explicitly added
- L41 _private prototype_ `void AddPropertyChildrenExplicitly(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder);` — Adds the specified property's children explicitly to the details panel under a custom group that matches the property's name. Used in case a group is needed to embed additional properties that don't live in the specified property @param PropertyHandle The property handle whose children are added explicitly @param ChildBuilder The detail children builder
- L44 _private prototype_ `IDetailGroup& GetOrAddGroup(IDetailChildrenBuilder& ChildBuilder, const FName& GroupName, const FText& GroupDisplayName);` — Gets an existing group, or adds one if not found

### `Source/Editor/DetailCustomizations/Private/ColorGradingVectorCustomization.h` (Private)


#### struct `FColorGradingMinMaxSliderValue`  
`struct FColorGradingMinMaxSliderValue`  
_L37-43_
- L39 _public member_ `TOptional<float> CurrentMaxSliderValue;`
- L40 _public member_ `TOptional<float> CurrentMinSliderValue;`
- L41 _public member_ `TOptional<float> DefaultMaxSliderValue;`
- L42 _public member_ `TOptional<float> DefaultMinSliderValue;`

#### class `FColorGradingVectorCustomizationBase`  
`class FColorGradingVectorCustomizationBase : public TSharedFromThis<FColorGradingVectorCustomizationBase>, public FEditorUndoClient`  
_L45-146_
- inherits: `TSharedFromThis<FColorGradingVectorCustomizationBase>,FEditorUndoClient`
- L49 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnNumericEntryBoxDynamicSliderMinMaxValueChanged, float, TWeakPtr<SWidget>, bool, bool);` — Notification when the max/min slider values are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L52 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCurrentHSVColorChanged, FLinearColor, bool);` — Notification the current HSV color was changed
- L54 _public prototype_ `FColorGradingVectorCustomizationBase(const FTrackedVector4PropertyHandle& InColorGradingPropertyHandle, const TArray<TWeakPtr<IPropertyHandle>>& InSortedChildArray);`
- L57 _public function_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged& GetOnNumericEntryBoxDynamicSliderMaxValueChangedDelegate()` — Return max/min slider value changed delegate (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L58 _public function_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged& GetOnNumericEntryBoxDynamicSliderMinValueChangedDelegate()`
- L61 _public function_ `FOnCurrentHSVColorChanged& GetOnCurrentHSVColorChangedDelegate()` — Return the current HSV color was changed delegate
- L64 _public prototype_ `void OnDynamicSliderMaxValueChanged(float NewMaxSliderValue, TWeakPtr<SWidget> InValueChangedSourceWidget, bool IsOriginator, bool UpdateOnlyIfHigher);` — Callback when the max/min slider value are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L65 _public prototype_ `void OnDynamicSliderMinValueChanged(float NewMinSliderValue, TWeakPtr<SWidget> InValueChangedSourceWidget, bool IsOriginator, bool UpdateOnlyIfLower);`
- L68 _public prototype_ `TOptional<float> OnSliderGetValue(int32 ColorIndex) const;` — Callback returning the current slider value for a specified color index
- L71 _public prototype_ `void OnCurrentHSVColorChangedDelegate(FLinearColor NewHSVColor, bool Originator);` — Callback handling HSV color changed
- L74 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L75 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L79 _protected prototype_ `bool IsInRGBMode() const;`
- L80 _protected prototype_ `UE::ColorGrading::EColorGradingModes GetColorGradingMode() const;`
- L82 _protected prototype_ `TSharedRef<UE::ColorGrading::SColorGradingComponentViewer> MakeComponentViewer(int32 ColorIndex, TOptional<float>& MinValue, TOptional<float>& MaxValue, TOptional<float>& SliderMinValue, TOptional<float>& SliderMaxValue, float& SliderExponent, float& Delta, float& ShiftMultiplier, float &CtrlMultiplier, bool& SupportDynamicSliderMaxValue, bool& SupportDynamicSliderMinValue, bool UseCompactDisplay);`
- L85 _protected prototype_ `UE::ColorGrading::EColorGradingComponent OnGetColorComponent(int32 ColorIndex) const;` — Callback returning the component associated with a specified color index
- L88 _protected prototype_ `bool GetCurrentColorGradingValue(FVector4& OutCurrentValue);` — Get the current color value being edited/displayed by this widget
- L91 _protected prototype_ `TOptional<float> OnGetMaxSliderValue(TOptional<float> DefaultMaxSliderValue, int32 ColorIndex) const;` — Callback returning the min/max slider value for a specified color index
- L92 _protected prototype_ `TOptional<float> OnGetMinSliderValue(TOptional<float> DefaultMinSliderValue, int32 ColorIndex) const;`
- L95 _protected prototype_ `float OnGetSliderDeltaValue(float DefaultValue, int32 ColorIndex) const;` — Callback returning the delta slider value for a specified color index
- L98 _protected prototype_ `TOptional<float> OnGetMaxValue(TOptional<float> DefaultValue, int32 ColorIndex) const;` — Callback returning the max value for a specified color index
- L100 _protected prototype_ `void OnBeginSliderMovement();`
- L101 _protected prototype_ `void OnEndSliderMovement(float NewValue, int32 ColorIndex);`
- L104 _protected prototype_ `void OnValueChanged(float NewValue, int32 ColorIndex);` — Callback called when a slider value changed or the user typed into the text box
- L107 _protected prototype_ `bool GetSupportDynamicSliderMaxValue(bool DefaultValue, int32 ColorIndex) const;` — Callback returning if we support dynamic max/min slider value
- L108 _protected prototype_ `bool GetSupportDynamicSliderMinValue(bool DefaultValue, int32 ColorIndex) const;`
- L111 _protected prototype_ `bool IsEntryBoxEnabled(int32 ColorIndex) const;` — Callback returning if an entry box should be enabled
- L115 _protected member_ `FColorGradingMinMaxSliderValue SpinBoxMinMaxSliderValues;` — Min/Max slider value that can change dynamically
- L118 _protected member_ `TArray<TWeakPtr<UE::ColorGrading::SColorGradingComponentViewer>> ComponentViewers;` — List of registered color component viewers
- L121 _protected member_ `FTrackedVector4PropertyHandle ColorGradingPropertyHandle;` — The color grading property we're editing
- L124 _protected member_ `TArray<TWeakPtr<IPropertyHandle>> SortedChildArray;` — Property for each color value (RGBY)
- L127 _protected member_ `bool IsRGBMode;` — Tell us if we are in RGB mode or HSV
- L132 _protected member_ `FLinearColor CurrentHSVColor;` — Represent the current HSV color. This is seperate as we store the value in FVector4 RGB format so during conversion value can be lost, so during editing we always use this variable in HSV mode
- L135 _protected member_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged OnNumericEntryBoxDynamicSliderMaxValueChanged;` — Callback when the max/min slider value are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L136 _protected member_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged OnNumericEntryBoxDynamicSliderMinValueChanged;`
- L139 _protected member_ `FOnCurrentHSVColorChanged OnCurrentHSVColorChanged;` — Return the current HSV color was changed delegate
- L142 _protected member_ `IDetailGroup* ParentGroup;` — Parent group in the property panel
- L145 _protected member_ `bool bIsUsingSlider;` — Whether or not the slider is actively being used

#### class `FColorGradingVectorCustomization`  
`class FColorGradingVectorCustomization : public FColorGradingVectorCustomizationBase`  
_L148-168_
- inherits: `FColorGradingVectorCustomizationBase`
- L151 _public prototype_ `FColorGradingVectorCustomization(TWeakPtr<IPropertyHandle> InColorGradingPropertyHandle, const TArray<TWeakPtr<IPropertyHandle>>& InSortedChildArray);`
- L152 _public prototype_ `virtual ~FColorGradingVectorCustomization();`
- L154 _public prototype_ `void MakeHeaderRow(FDetailWidgetRow& Row, TSharedRef<FVector4StructCustomization> InVector4Customization);`
- L155 _public prototype_ `void CustomizeChildren(IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils);`
- L158 _public prototype_ `void OnColorModeChanged(bool InIsRGBMode);` — Callback when the ColorMode changed
- L162 _private prototype_ `FLinearColor OnGetColorForHeaderColorBlock() const;` — Will return the color of the color block displayed in the header
- L164 _private prototype_ `EVisibility GetMultipleValuesTextVisibility() const;`
- L167 _private member_ `TSharedPtr<class FColorGradingCustomBuilder> CustomColorGradingBuilder;` — Represent the custom builder associated with the color grading property

#### class `FColorGradingCustomBuilder`  
`class FColorGradingCustomBuilder : public IDetailCustomNodeBuilder, public FColorGradingVectorCustomizationBase`  
_L170-242_
- inherits: `IDetailCustomNodeBuilder,FColorGradingVectorCustomizationBase`
- L174 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnColorModeChanged, bool);` — Notification when we change color mode (RGB <-> HSV)
- L176 _public prototype_ `FColorGradingCustomBuilder(const FTrackedVector4PropertyHandle& InColorGradingPropertyHandle, const TArray<TWeakPtr<IPropertyHandle>>& InSortedChildArray, TSharedRef<FColorGradingVectorCustomization> InColorGradingCustomization, IDetailGroup* InParentGroup);`
- L178 _public prototype_ `virtual ~FColorGradingCustomBuilder();`
- L181 _public function_ `FOnColorModeChanged& GetOnColorModeChanged()` — Delegate to register for notification when we change color mode (RGB <-> HSV)
- L184 _public prototype_ `void ResetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle);` — Callback when user click the reset button of the color grading property
- L185 _public prototype_ `bool CanResetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle);`
- L190 _private function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRebuildChildren) override` — IDetailCustomNodeBuilder interface
- L191 _private function_ `virtual bool RequiresTick() const override`
- L192 _private prototype_ `virtual void Tick(float DeltaTime) override;`
- L193 _private prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L194 _private prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L195 _private function_ `virtual FName GetName() const override`
- L196 _private function_ `virtual bool InitiallyCollapsed() const override`
- L199 _private prototype_ `void OnColorGradingPickerChanged(FVector4 &NewValue, bool ShouldCommitValueChanges);` — Local UI Handlers
- L201 _private prototype_ `void OnBeginMainValueSliderMovement();`
- L202 _private prototype_ `void OnEndMainValueSliderMovement();`
- L204 _private prototype_ `void OnBeginMouseCapture();`
- L205 _private prototype_ `void OnEndMouseCapture();`
- L208 _private prototype_ `void OnPropertyValueChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);` — Called when any property changes
- L211 _private prototype_ `void OnDetailGroupReset();` — Callback when user click the Group reset button
- L214 _private prototype_ `FText OnChangeColorModeText(UE::ColorGrading::EColorGradingColorDisplayMode ModeType) const;` — Callback returning which color mode text we should display
- L217 _private prototype_ `FText OnChangeColorModeToolTipText(UE::ColorGrading::EColorGradingColorDisplayMode ModeType) const;` — Callback returning which color mode text tooltip we should display
- L220 _private prototype_ `UE::ColorGrading::EColorGradingColorDisplayMode OnGetChangeColorMode() const;` — Callback returning which color mode is checked
- L223 _private prototype_ `EVisibility OnGetRGBHSVButtonVisibility(UE::ColorGrading::EColorGradingColorDisplayMode ModeType) const;` — Callback returning if the RGB/HSV button should be visible
- L226 _private prototype_ `EVisibility OnGetGradientVisibility() const;` — Callback returning if the Gradient should be visible
- L229 _private prototype_ `void OnChangeColorModeClicked(UE::ColorGrading::EColorGradingColorDisplayMode ModeType);` — Callback Called when user click a color mode change checkbox
- L232 _private member_ `FSimpleDelegate OnRebuildChildren;` — Called to rebuild the children of the detail tree
- L235 _private member_ `TWeakPtr<UE::ColorGrading::SColorGradingPicker> ColorGradingPickerWidget;` — Color Picker widget
- L238 _private member_ `TSharedPtr<FColorGradingVectorCustomization> ColorGradingCustomization;` — Parent of this custom builder (required to communicate with FColorGradingVectorCustomization)
- L241 _private member_ `FOnColorModeChanged OnColorModeChanged;` — Delegate to register for notification when we change color mode (RGB <-> HSV)

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace ColorGrading` (scope `UE`)
- L49 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnNumericEntryBoxDynamicSliderMinMaxValueChanged, float, TWeakPtr<SWidget>, bool, bool);` — Notification when the max/min slider values are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L52 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCurrentHSVColorChanged, FLinearColor, bool);` — Notification the current HSV color was changed
- L174 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnColorModeChanged, bool);` — Notification when we change color mode (RGB <-> HSV)

### `Source/Editor/DetailCustomizations/Private/ComponentMaterialCategory.h` (Private)


#### class `FComponentMaterialCategory`  
`class FComponentMaterialCategory : public TSharedFromThis<FComponentMaterialCategory>`  
_L21-96_
- inherits: `TSharedFromThis<FComponentMaterialCategory>`
- desc: Encapsulates functionality for the ActorDetails material category
- L27 _public prototype_ `FComponentMaterialCategory( TArray< TWeakObjectPtr<USceneComponent> >& InSelectedComponents );` — Constructs a category in the details panel for displaying used materials
- L32 _public prototype_ `void Create( IDetailLayoutBuilder& DetailBuilder );` — Creates the category
- L39 _private prototype_ `void OnGetMaterialsForView( class IMaterialListBuilder& OutMaterials );` — Called by the material list widget when we need to get new materials for the list @param OutMaterials	Handle to a material list builder that materials should be added to
- L49 _private prototype_ `void OnMaterialChanged( UMaterialInterface* NewMaterial, UMaterialInterface* PrevMaterial, int32 SlotIndex, bool bReplaceAll );` — Called when a user drags a new material over a list item to replace it @param NewMaterial	The material that should replace the existing material @param PrevMaterial	The material that should be replaced @param SlotIndex		The index of the slot on the component where materials should be replaces @param bReplaceAll	If true all materials in the slot should be replaced not just ones using PrevMaterial
- L56 _private prototype_ `void OnCopyMaterialItem(int32 CurrentSlot);` — Called when a user executes the copy command on a material list item @param CurrentSlot	The slot index that was copied
- L64 _private prototype_ `bool OnCanCopyMaterialItem(int32 CurrentSlot) const;` — Called to determine if the copy command should be enabled for a particular a material list item @param CurrentSlot	The slot index that was copied @return	whether this slot index can be copied
- L71 _private prototype_ `void OnPasteMaterialItem(int32 CurrentSlot);` — Called when a user executes the paste command on a material list item @param CurrentSlot	The slot index that was pasted on
- L79 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetsForMaterial(UMaterialInterface* Material, int32 SlotIndex);` — Called by the material list widget to customize the material slot widget @param Material	The material for the slot widget to be customized @param SlotIndex The slot index for the slot widget to be customized
- L84 _private prototype_ `bool IsComponentEditable( UActorComponent* InComponent ) const;` — @return true if a component is editable (and visible in the view)
- L88 _private member_ `TArray< TWeakObjectPtr<USceneComponent> > SelectedComponents;` — Reference to the list of selected actors
- L91 _private member_ `FNotifyHook* NotifyHook;` — Notify hook to use
- L93 _private member_ `IDetailCategoryBuilder* MaterialCategory;`
- L95 _private prototype_ `FText GetMaterialNameText(int32 MaterialIndex) const;`

### `Source/Editor/DetailCustomizations/Private/ComponentReferenceCustomization.h` (Private)


#### class `FComponentReferenceCustomization`  
`class FComponentReferenceCustomization : public IPropertyTypeCustomization`  
_L25-154_
- inherits: `IPropertyTypeCustomization`
- L29 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this customization for a specific detail view requesting it
- L32 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L33 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;`
- L37 _private prototype_ `void BuildClassFilters();` — From the property metadata, build the list of allowed and disallowed class.
- L40 _private prototype_ `void BuildComboBox();` — Build the combobox widget.
- L46 _private prototype_ `AActor* GetFirstOuterActor() const;` — From the Detail panel outer hierarchy, find the first actor or component owner we find. This is use in case we want only component on the Self actor and to check if we did a cross-level reference.
- L52 _private prototype_ `void SetValue(const FComponentReference& Value);` — Set the value of the asset referenced by this property editor. Will set the underlying property handle if there is one.
- L55 _private prototype_ `FPropertyAccess::Result GetValue(FComponentReference& OutValue) const;` — Get the value referenced by this widget.
- L58 _private prototype_ `bool IsComponentReferenceValid(const FComponentReference& Value) const;` — Is the Value valid
- L61 _private prototype_ `void OnPropertyValueChanged();` — Callback when the property value changed.
- L68 _private prototype_ `int32 OnGetComboContentWidgetIndex() const;` — Return 0, if we have multiple values to edit. Return 1, if we display the widget normally.
- L70 _private prototype_ `bool CanEdit() const;`
- L71 _private prototype_ `bool CanEditChildren() const;`
- L73 _private prototype_ `const FSlateBrush* GetActorIcon() const;`
- L74 _private prototype_ `FText OnGetActorName() const;`
- L75 _private prototype_ `const FSlateBrush* GetComponentIcon() const;`
- L76 _private prototype_ `FText OnGetComponentName() const;`
- L77 _private prototype_ `const FSlateBrush* GetStatusIcon() const;`
- L83 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();` — Get the content to be displayed in the asset/actor picker menu @returns the widget for the menu content
- L89 _private prototype_ `void OnMenuOpenChanged(bool bOpen);` — Called when the asset menu is closed, we handle this to force the destruction of the asset menu to ensure any settings the user set are saved.
- L94 _private prototype_ `bool IsFilteredActor(const AActor* const Actor) const;` — Returns whether the actor/component should be filtered out from selection.
- L95 _private prototype_ `bool IsFilteredComponent(const UActorComponent* const Component) const;`
- L96 _private prototype_ `static bool IsFilteredObject(const UObject* const Object, const TArray<const UClass*>& AllowedFilters, const TArray<const UClass*>& DisallowedFilters);`
- L102 _private prototype_ `void OnComponentSelected(const UActorComponent* InComponent);` — Delegate for handling selection in the scene outliner. @param	InActor	The chosen component
- L107 _private prototype_ `void CloseComboButton();` — Closes the combo button.
- L114 _private prototype_ `void UpdateCachedValues(bool bResetValueIfInvalid);` — Updates CachedFirstOuterActor, CachedComponent, and CachedPropertyAccess @param bResetValueIfInvalid If true and the resulting component doesn't match the filters, do a SetValue call to reset the reference to null.
- L117 _private prototype_ `bool RedirectActorToBPPreviewActor(TWeakObjectPtr<AActor>& InOutActor, UWorld*& OutWorld) const;` — Redirects the found actor to a BP preview actor to be able to choose components in a BP editor context
- L120 _private prototype_ `UActorComponent* GetCachedComponent() const;` — Gets (or updates) the cached component
- L124 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — The property handle we are customizing
- L127 _private member_ `TSharedPtr<SComboButton> ComponentComboButton;` — Main combo button
- L130 _private member_ `TArray<const UClass*> AllowedActorClassFilters;` — Classes that can be used with this property
- L131 _private member_ `TArray<const UClass*> AllowedComponentClassFilters;`
- L134 _private member_ `TArray<const UClass*> DisallowedActorClassFilters;` — Classes that can NOT be used with this property
- L135 _private member_ `TArray<const UClass*> DisallowedComponentClassFilters;`
- L138 _private member_ `bool bAllowClear;` — Whether the asset can be 'None' in this case
- L141 _private member_ `bool bAllowAnyActor;` — Can the actor be different/selected
- L144 _private member_ `bool bUseComponentPicker;` — Do it has the UseComponentPicker metadata
- L147 _private member_ `bool bIsSoftReference;` — Whether or not the component reference is a FSoftComponentReference
- L150 _private member_ `TWeakObjectPtr<AActor> CachedFirstOuterActor;` — Cached ComponentReference
- L151 _private member_ `TWeakObjectPtr<AActor> CachedFilterActor;`
- L152 _private member_ `TWeakObjectPtr<UActorComponent> CachedComponent;`
- L153 _private member_ `FPropertyAccess::Result CachedPropertyAccess;`

### `Source/Editor/DetailCustomizations/Private/ComponentTransformDetails.h` (Private)


#### enum `ETransformField::Type`  
`enum Type`  
_L38-43_
- L40 _public enumerator_ `Location`
- L41 _public enumerator_ `Rotation`
- L42 _public enumerator_ `Scale`

#### class `FComponentTransformDetails`  
`class FComponentTransformDetails : public TSharedFromThis<FComponentTransformDetails>, public IDetailCustomNodeBuilder, public TNumericUnitTypeInterface<FVector::FReal>`  
_L48-364_
- inherits: `TSharedFromThis<FComponentTransformDetails>,IDetailCustomNodeBuilder,TNumericUnitTypeInterface<FVector::FReal>`
- desc: Manages the Transform section of a details view
- L51 _public prototype_ `FComponentTransformDetails( const TArray< TWeakObjectPtr<UObject> >& InSelectedObjects, const FSelectedActorInfo& InSelectedActorInfo, IDetailLayoutBuilder& DetailBuilder );`
- L52 _public prototype_ `~FComponentTransformDetails();`
- L54 _public function_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override`
- L55 _public prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L56 _public function_ `virtual bool RequiresTick() const override`
- L57 _public function_ `virtual FName GetName() const override`
- L58 _public function_ `virtual bool InitiallyCollapsed() const override`
- L59 _public prototype_ `virtual void Tick( float DeltaTime ) override;`
- L60 _public function_ `virtual void SetOnRebuildChildren( FSimpleDelegate OnRebuildChildren ) override`
- L62 _public function_ `void HideTransformField(const ETransformField::Type InTransformField)`
- L69 _private prototype_ `void CacheDetails();` — Caches some information of the actor (transform, locked location) for the user input boxes
- L72 _private prototype_ `bool GetIsEnabled() const;` — @return Whether the transform details panel should be enabled (editable) or not (read-only / greyed out)
- L73 _private prototype_ `bool GetIsLocationEnabled() const;`
- L74 _private prototype_ `bool GetIsRotationEnabled() const;`
- L75 _private prototype_ `bool GetIsScaleEnabled() const;`
- L76 _private prototype_ `bool GetIsTransformComponentEnabled(FName ComponentName) const;`
- L79 _private prototype_ `FVector GetAxisFilteredVector(EAxisList::Type Axis, const FVector& NewValue, const FVector& OldValue);` — Sets a vector based on two source vectors and an axis list
- L90 _private prototype_ `void OnSetTransform(ETransformField::Type TransformField, EAxisList::Type Axis, FVector NewValue, bool bMirror, bool bCommitted);` — Sets the selected object(s) axis to passed in value @param TransformField	The field (location/rotation/scale) to modify @param Axis				Bitfield of which axis to set, can be multiple @param NewValue			The new vector values, it only uses the ones with specified axis @param bMirror			If true, set the value to it's inverse instead of using NewValue @param bCommittted		True if the value was committed, false is the value comes from the slider
- L101 _private prototype_ `void OnSetTransformAxis(FVector::FReal NewValue, ETextCommit::Type CommitInfo, ETransformField::Type TransformField, EAxisList::Type Axis, bool bCommitted);` — Sets a single axis value, called from UI @param TransformField	The field (location/rotation/scale) to modify @param NewValue			The new translation value @param CommitInfo		Whether or not this was committed from pressing enter or losing focus @param Axis				Bitfield of which axis to set, can be multiple @param bCommittted		true if the value was committed, false is the value comes from the slider
- L108 _private prototype_ `void BeginSliderTransaction(FText ActorTransaction, FText ComponentTransaction) const;` — Helper to begin a new transaction for a slider interaction. @param ActorTransaction		The name to give the transaction when changing an actor transform. @param ComponentTransaction	The name to give the transaction when directly editing a component transform.
- L111 _private prototype_ `void OnBeginRotationSlider();` — Called when the one of the axis sliders for object rotation begins to change for the first time
- L114 _private prototype_ `void OnEndRotationSlider(FRotator::FReal NewValue);` — Called when the one of the axis sliders for object rotation is released
- L117 _private prototype_ `void OnBeginLocationSlider();` — Called when one of the axis sliders for object location begins to change
- L120 _private prototype_ `void OnEndLocationSlider(FVector::FReal NewValue);` — Called when one of the axis sliders for object location is released
- L123 _private prototype_ `void OnBeginScaleSlider();` — Called when one of the axis sliders for object scale begins to change
- L126 _private prototype_ `void OnEndScaleSlider(FVector::FReal NewValue);` — Called when one of the axis sliders for object scale is released
- L129 _private prototype_ `const FSlateBrush* GetPreserveScaleRatioImage() const;` — @return Icon to use in the preserve scale ratio check box
- L132 _private prototype_ `ECheckBoxState IsPreserveScaleRatioChecked() const;` — @return The state of the preserve scale ratio checkbox
- L137 _private prototype_ `void OnPreserveScaleRatioToggled( ECheckBoxState NewState );` — Called when the preserve scale ratio checkbox is toggled
- L145 _private prototype_ `TSharedRef<SWidget> BuildTransformFieldLabel( ETransformField::Type TransformField );` — Builds a transform field label @param TransformField The field to build the label for @return The label widget
- L153 _private prototype_ `FText GetTransformFieldText( ETransformField::Type TransformField ) const;` — Gets display text for a transform field @param TransformField	The field to get the text for @return The text label for TransformField
- L158 _private prototype_ `FText GetLocationText() const;` — @return the text to display for translation
- L163 _private prototype_ `FText GetRotationText() const;` — @return the text to display for rotation
- L168 _private prototype_ `FText GetScaleText() const;` — @return the text to display for scale
- L175 _private prototype_ `void OnSetAbsoluteTransform( ETransformField::Type TransformField, bool bAbsoluteEnabled);` — Sets relative transform on the specified field @param The field that should be set to relative
- L178 _private prototype_ `bool IsAbsoluteTransformChecked( ETransformField::Type TransformField, bool bAbsoluteEnabled=true) const;` — @return true if Absolute flag of transform type matches passed in bCheckAbsolute
- L181 _private prototype_ `bool CanChangeAbsoluteFlag(ETransformField::Type TransformField) const;` — @return true if Absolute flag of transform can be changed
- L184 _private prototype_ `bool OnCanCopy( ETransformField::Type TransformField ) const;` — @return true of copy is enabled for the specified field
- L189 _private prototype_ `void OnCopy( ETransformField::Type TransformField );` — Copies the specified transform field to the clipboard
- L191 _private prototype_ `void OnCopyToText(TSharedPtr<IPropertyHandle> PropertyHandle, FString& Text, const TOptional<FGuid>& InOperationId, ETransformField::Type InTransformField);`
- L193 _private prototype_ `void CopyToText(FString& Text, ETransformField::Type InTransformField);`
- L199 _private prototype_ `void OnPaste( ETransformField::Type TransformField );` — Pastes the specified transform field from the clipboard
- L201 _private prototype_ `void OnPasteFromText(const FString& InTag, const FString& InText, const TOptional<FGuid>& InOperationId, ETransformField::Type InTransformField);`
- L203 _private prototype_ `void PasteFromText(const FString& InTag, const FString& InText, ETransformField::Type InTransformField);`
- L208 _private prototype_ `FUIAction CreateCopyAction( ETransformField::Type TransformField ) const;` — Creates a UI action for copying a specified transform field
- L213 _private prototype_ `FUIAction CreatePasteAction( ETransformField::Type TransformField ) const;` — Creates a UI action for pasting a specified transform field
- L216 _private prototype_ `void OnLocationResetClicked();` — Called when the "Reset to Default" button for the location has been clicked
- L219 _private prototype_ `void OnRotationResetClicked();` — Called when the "Reset to Default" button for the rotation has been clicked
- L222 _private prototype_ `void OnScaleResetClicked();` — Called when the "Reset to Default" button for the scale has been clicked
- L225 _private prototype_ `void ExtendXScaleContextMenu( FMenuBuilder& MenuBuilder );` — Extend the context menu for the X component
- L227 _private prototype_ `void ExtendYScaleContextMenu( FMenuBuilder& MenuBuilder );` — Extend the context menu for the Y component
- L229 _private prototype_ `void ExtendZScaleContextMenu( FMenuBuilder& MenuBuilder );` — Extend the context menu for the Z component
- L232 _private prototype_ `void OnXScaleMirrored();` — Called when the X axis scale is mirrored
- L234 _private prototype_ `void OnYScaleMirrored();` — Called when the Y axis scale is mirrored
- L236 _private prototype_ `void OnZScaleMirrored();` — Called when the Z axis scale is mirrored
- L239 _private prototype_ `TOptional<FVector::FReal> GetLocationX() const;` — @return The X component of location
- L241 _private prototype_ `TOptional<FVector::FReal> GetLocationY() const;` — @return The Y component of location
- L243 _private prototype_ `TOptional<FVector::FReal> GetLocationZ() const;` — @return The Z component of location
- L245 _private prototype_ `bool GetLocationResetVisibility() const;` — @return The visibility of the "Reset to Default" button for the location component
- L248 _private prototype_ `TOptional<FRotator::FReal> GetRotationX() const;` — @return The X component of rotation
- L250 _private prototype_ `TOptional<FRotator::FReal> GetRotationY() const;` — @return The Y component of rotation
- L252 _private prototype_ `TOptional<FRotator::FReal> GetRotationZ() const;` — @return The Z component of rotation
- L254 _private prototype_ `bool GetRotationResetVisibility() const;` — @return The visibility of the "Reset to Default" button for the rotation component
- L257 _private prototype_ `TOptional<FVector::FReal> GetScaleX() const;` — @return The X component of scale
- L259 _private prototype_ `TOptional<FVector::FReal> GetScaleY() const;` — @return The Y component of scale
- L261 _private prototype_ `TOptional<FVector::FReal> GetScaleZ() const;` — @return The Z component of scale
- L263 _private prototype_ `bool GetScaleResetVisibility() const;` — @return The visibility of the "Reset to Default" button for the scale component
- L266 _private prototype_ `void CacheCommonLocationUnits();` — Cache a single unit to display all location components in
- L269 _private prototype_ `TSharedPtr<IPropertyHandle> FindOrCreatePropertyHandle(FName PropertyName, IDetailChildrenBuilder& ChildrenBuilder);` — Get a property handle from a property name.
- L271 _private prototype_ `void UpdatePropertyHandlesObjects(const TArray<UObject*> NewSceneComponents);` — Update the outer objects of the property handles generated from this transform.
- L274 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);` — Delegate called when the OnObjectsReplaced is broadcast by the engine.
- L279 _private prototype_ `FVector ConvertFromUnrealSpace_EulerDeg(const FRotator& Rotator) const;` — Gets Euler angles from Unreal's Rotator space and converts to the display/edit space If display space is the Rotator space, then just Euler() Otherwise performs handedness and rotation order calculations
- L282 _private prototype_ `FRotator ConvertToUnrealSpace_EulerDeg(const FVector& Rotation) const;` — Converts back to Unreal's Rotator if display space is different than Rotator's space Assumes that the Rotation provided is in degrees
- L327 _private member_ `FSelectedActorInfo SelectedActorInfo;`
- L329 _private member_ `TArray< TWeakObjectPtr<UObject> > SelectedObjects;` — Copy of selected actor references in the details view
- L331 _private member_ `FOptionalVector<FVector::FReal> CachedLocation;` — Cache translation value of the selected set
- L333 _private member_ `FOptionalVector<FRotator::FReal> CachedRotation;` — Cache rotation value of the selected set
- L335 _private member_ `FOptionalVector<FVector::FReal> CachedScale;` — Cache scale value of the selected set
- L337 _private member_ `FNotifyHook* NotifyHook;` — Notify hook to use
- L339 _private member_ `TMap< UObject*, FRotator > ObjectToRelativeRotationMap;` — Mapping from object to relative rotation values which are not affected by Quat->Rotator conversions during transform calculations
- L341 _private member_ `bool bAbsoluteLocation;` — Whether or not we are in absolute translation mode
- L343 _private member_ `bool bAbsoluteRotation;` — Whether or not we are in absolute rotation mode
- L345 _private member_ `bool bAbsoluteScale;` — Whether or not we are in absolute scale mode
- L347 _private member_ `bool bPreserveScaleRatio;` — Whether or not to preserve scale ratios
- L349 _private member_ `FVector SliderScaleRatio;` — Scale ratio to use when we are using the sliders with bPreserveScaleRatio set.
- L351 _private member_ `bool bEditingRotationInUI;` — Flag to indicate we are currently editing the rotation in the UI, so we should rely on the cached value in objectToRelativeRotationMap, not the value from the object
- L353 _private member_ `bool bIsSliderTransaction;` — Flag to indicate we are currently performing a slider transaction
- L355 _private member_ `uint8 HiddenFieldMask;` — Bitmask to indicate which fields should be hidden (if any)
- L357 _private member_ `TMap<FName, TSharedPtr< IPropertyHandle> > PropertyHandles;` — Holds this transform's property handles.
- L359 _private member_ `TArray< TWeakObjectPtr<UObject> > CachedHandlesObjects;` — Holds the property handles' outer objects. Used to update the handles' objects when the actor construction script runs.
- L361 _private member_ `bool bIsEnabledCache;` — Cached enabled value of the selected set
- L363 _private member_ `bool bIsAxisDisplayLeftUpForward;` — Whether or not the axis display coordinate system is LeftUpForward

#### struct `FComponentTransformDetails::FOptionalVector`  
`template <typename NumericType> struct FOptionalVector`  
_L287-325_
- desc: A vector where it may optionally be unset
- L292 _public function_ `void Set( const FVector& InVec )` — Sets the value from an FVector
- L302 _public function_ `void Set(const FRotator& InRot)` — Sets the value from an FRotator
- L310 _public function_ `bool IsSet() const` — @return Whether or not the value is set
- L316 _public function_ `FVector ToVector() const`
- L322 _public member_ `TOptional<NumericType> X;`
- L323 _public member_ `TOptional<NumericType> Y;`
- L324 _public member_ `TOptional<NumericType> Z;`

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace ETransformField`

### `Source/Editor/DetailCustomizations/Private/CompositeRerouteCustomization.h` (Private)


#### class `FCompositeRerouteCustomization`  
`class FCompositeRerouteCustomization : public IPropertyTypeCustomization`  
_L8-17_
- inherits: `IPropertyTypeCustomization`
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this property customization
- L15 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Source/Editor/DetailCustomizations/Private/CompressedAnimationDataNodeBuilder.h` (Private)


#### class `FCompressedAnimationDataNodeBuilder`  
`class FCompressedAnimationDataNodeBuilder : public IDetailCustomNodeBuilder`  
_L11-41_
- inherits: `IDetailCustomNodeBuilder`
- L14 _public prototype_ `FCompressedAnimationDataNodeBuilder(UAnimSequence* InAnimSequence);`
- L16 _public function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override`
- L17 _public function_ `virtual void SetOnToggleExpansion(FOnToggleNodeExpansion InOnToggleExpansion) override`
- L18 _public prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L19 _public prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L20 _public function_ `virtual FName GetName() const override`
- L22 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L23 _public function_ `virtual bool RequiresTick() const override`
- L25 _protected prototype_ `EVisibility GetCompressionIndicatorVisibility() const;`
- L26 _protected prototype_ `const FSlateBrush* GetSelectedPlatformBrush() const;`
- L27 _protected prototype_ `static TSharedRef<SWidget> OnGeneratePlatformListWidget(TSharedPtr<FString> Platform);`
- L28 _protected prototype_ `void OnPlatformSelectionChanged( TSharedPtr<FString> Platform, ESelectInfo::Type InSelectInfo );`
- L29 _protected prototype_ `FText GetSelectedPlatformName() const;`
- L31 _protected member_ `TWeakObjectPtr<UAnimSequence> WeakAnimSequence;`
- L32 _protected member_ `FOnToggleNodeExpansion OnToggleExpansion;`
- L33 _protected member_ `FSimpleDelegate OnRegenerateChildren;`
- L34 _protected member_ `const ITargetPlatform* CurrentTargetPlatform = nullptr;`
- L35 _protected member_ `TArray<TSharedPtr<FString>> PlatformsList;`
- L36 _protected member_ `bool bExpanded = false;`
- L38 _protected member_ `bool bCachedHasCompressionData = false;`
- L40 _protected member_ `FString SelectedPlatformName;`

### `Source/Editor/DetailCustomizations/Private/ConfigEditorPropertyDetails.h` (Private)


#### class `FConfigPropertyHelperDetails`  
`class FConfigPropertyHelperDetails : public IDetailCustomization`  
_L22-105_
- inherits: `IDetailCustomization`
- desc: Implements details panel customizations for UConfigPropertyHelper fields.
- L34 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Makes a new instance of this config editor detail layout class. @return The created instance.
- L40 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& InDetailBuilder ) override;` — IDetailCustomization interface
- L52 _private prototype_ `TSharedRef<SWidget> ConstructPropertyTable(IDetailLayoutBuilder& DetailBuilder);` — Create a property table of the Config Files vs Property we are editing @return The created instance of the property table.
- L57 _private prototype_ `void RepopulatePropertyTable(IDetailLayoutBuilder& DetailBuilder);` — Populate the Property table with entries for the provided config files.
- L65 _private prototype_ `void OnPropertyValueChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);` — Event which is triggered through changes in our editor. @param Object				- The object whose property has changed. @param PropertyChangedEvent	- The event information of the change.
- L70 _private member_ `TSharedPtr<IPropertyTable> PropertyTable;` — The table which holds our editable properties.
- L76 _private prototype_ `void AddEditablePropertyForConfig(IDetailLayoutBuilder& DetailBuilder, class UPropertyConfigFileDisplayRow* ConfigFileProperty);`
- L84 _private member_ `TSharedPtr<IPropertyHandle> ConfigFilesHandle;` — Keep track of the property handle for the config files.
- L87 _private member_ `FProperty* ConfigEditorCopyOfEditProperty;` — A copy of the edit property we use with our helper class to update values on a per-config basis.
- L90 _private member_ `FProperty* OriginalProperty;` — The original property from the Project settings, that we have chosen to edit.
- L94 _private member_ `UClass* ConfigEditorPropertyViewClass;` — A runtime class generated with the Original property as a member. This allows us to edit a property on a per config basis.
- L98 _private member_ `UObject* ConfigEditorPropertyViewCDO;` — The 'Class Default Object' of the runtime class we generate. We duplicate this for each config file instance.
- L101 _private member_ `TMap<FString, UObject*> AssociatedConfigFileAndObjectPairings;` — Coupling of Config files and their editable objects.
- L104 _private member_ `TMap<FString, UObject*> ConfigFileAndPropertySourcePairings;` — Mapping of Config Files and ConfigEditorPropertyViewClass objects.

### `Source/Editor/DetailCustomizations/Private/CurveColorCustomization.h` (Private)


#### class `FCurveColorCustomization`  
`class FCurveColorCustomization : public IPropertyTypeCustomization, public FCurveOwnerInterface`  
_L27-148_
- inherits: `IPropertyTypeCustomization,FCurveOwnerInterface`
- desc: Customizes a RuntimeCurveLinearColor struct to display a Curve Editor
- L30 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L35 _public prototype_ `virtual ~FCurveColorCustomization();` — Destructor
- L38 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L39 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L43 _public prototype_ `virtual TArray<FRichCurveEditInfoConst> GetCurves() const override;` — `UE_DEPRECATED(5.6, "Use version taking a TAdderReserverRef")` — FCurveOwnerInterface interface
- L44 _public prototype_ `virtual void GetCurves(TAdderReserverRef<FRichCurveEditInfoConst> Curves) const override;`
- L45 _public prototype_ `virtual TArray<FRichCurveEditInfo> GetCurves() override;`
- L46 _public prototype_ `virtual void ModifyOwner() override;`
- L47 _public prototype_ `virtual TArray<const UObject*> GetOwners() const override;`
- L48 _public prototype_ `virtual void MakeTransactional() override;`
- L49 _public prototype_ `virtual void OnCurveChanged(const TArray<FRichCurveEditInfo>& ChangedCurveEditInfos) override;`
- L50 _public function_ `virtual bool IsLinearColorCurve() const override`
- L51 _public prototype_ `virtual FLinearColor GetLinearColorValue(float InTime) const override;`
- L52 _public prototype_ `virtual bool HasAnyAlphaKeys() const override;`
- L53 _public prototype_ `virtual bool IsValidCurve( FRichCurveEditInfo CurveInfo ) override;`
- L59 _private prototype_ `FCurveColorCustomization();` — Constructor
- L64 _private function_ `float GetViewMinInput() const` — Get View Min Input for the Curve Editor
- L69 _private function_ `float GetViewMaxInput() const` — Get View Min Input for the Curve Editor
- L74 _private prototype_ `float GetTimelineLength() const;` — Get Timeline Length for the Curve Editor
- L79 _private prototype_ `void SetInputViewRange(float InViewMinInput, float InViewMaxInput);` — Set View Min and Max Inputs for the Curve Editor
- L84 _private prototype_ `void OnExternalCurveChanged(TSharedRef<IPropertyHandle> CurvePropertyHandle);` — Called when RuntimeCurveLinearColor's External Curve is changed
- L89 _private prototype_ `FReply OnCreateButtonClicked();` — Called when button clicked to create an External Colour Curve
- L94 _private prototype_ `bool IsCreateButtonEnabled() const;` — Whether Create button is enabled
- L99 _private prototype_ `FReply OnConvertButtonClicked();` — Called when button clicked to convert External Curve to internal curve
- L104 _private prototype_ `bool IsConvertButtonEnabled() const;` — Whether Convert button is enabled
- L109 _private prototype_ `FReply OnCurvePreviewDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent );` — Called when user double clicks on the curve preview to open a full size editor
- L114 _private prototype_ `static void CopyCurveData( const FRichCurve* SrcCurve, FRichCurve* DestCurve );` — Copies data from one Rich Curve to another
- L119 _private prototype_ `void DestroyPopOutWindow();` — Destroys the pop out window used for editing internal curves.
- L123 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Cached RuntimeCurveLinearColor struct handle
- L126 _private member_ `TSharedPtr<IPropertyHandle> ExternalCurveHandle;` — Cached External Curve handle
- L129 _private member_ `TSharedPtr<SCurveEditor> CurveWidget;` — Small preview Curve Editor
- L132 _private member_ `TWeakPtr<SWindow> CurveEditorWindow;` — Window for pop out Curve Editor
- L135 _private member_ `FRuntimeCurveLinearColor* RuntimeCurve;` — Cached pointer to the actual RuntimeCurveLinearColor struct
- L138 _private member_ `UObject* Owner;` — Object that owns the RuntimeFloatCurve
- L141 _private member_ `float ViewMinInput;` — View Min Input for the Curve Editor
- L144 _private member_ `float ViewMaxInput;` — View Max Input for the Curve Editor
- L147 _private member_ `static const FVector2D DEFAULT_WINDOW_SIZE;` — Size of the pop out Curve Editor window

### `Source/Editor/DetailCustomizations/Private/CurveStructCustomization.h` (Private)


#### class `FCurveStructCustomization`  
`class FCurveStructCustomization : public IPropertyTypeCustomization, public FCurveOwnerInterface, public FEditorUndoClient`  
_L27-149_
- inherits: `IPropertyTypeCustomization,FCurveOwnerInterface,FEditorUndoClient`
- desc: Customizes a RuntimeFloatCurve struct to display a Curve Editor
- L30 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L35 _public prototype_ `virtual ~FCurveStructCustomization();` — Destructor
- L38 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L39 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L43 _public prototype_ `virtual TArray<FRichCurveEditInfoConst> GetCurves() const override;` — `UE_DEPRECATED(5.6, "Use version taking a TAdderReserverRef")` — FCurveOwnerInterface interface
- L44 _public prototype_ `virtual void GetCurves(TAdderReserverRef<FRichCurveEditInfoConst> Curves) const override;`
- L45 _public prototype_ `virtual TArray<FRichCurveEditInfo> GetCurves() override;`
- L46 _public prototype_ `virtual void ModifyOwner() override;`
- L47 _public prototype_ `virtual TArray<const UObject*> GetOwners() const override;`
- L48 _public prototype_ `virtual void MakeTransactional() override;`
- L49 _public prototype_ `virtual void OnCurveChanged(const TArray<FRichCurveEditInfo>& ChangedCurveEditInfos) override;`
- L50 _public prototype_ `virtual bool IsValidCurve( FRichCurveEditInfo CurveInfo ) override;`
- L53 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L54 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L60 _private prototype_ `FCurveStructCustomization();` — Constructor
- L65 _private function_ `float GetViewMinInput() const` — Get View Min Input for the Curve Editor
- L70 _private function_ `float GetViewMaxInput() const` — Get View Min Input for the Curve Editor
- L75 _private prototype_ `float GetTimelineLength() const;` — Get Timeline Length for the Curve Editor
- L80 _private prototype_ `void SetInputViewRange(float InViewMinInput, float InViewMaxInput);` — Set View Min and Max Inputs for the Curve Editor
- L85 _private prototype_ `void OnExternalCurveChanged(TSharedRef<IPropertyHandle> CurvePropertyHandle);` — Called when RuntimeFloatCurve's External Curve is changed
- L90 _private prototype_ `FReply OnCreateButtonClicked();` — Called when button clicked to create an External Curve
- L95 _private prototype_ `bool IsCreateButtonEnabled() const;` — Whether Create button is enabled
- L100 _private prototype_ `FReply OnConvertButtonClicked();` — Called when button clicked to convert External Curve to internal curve
- L105 _private prototype_ `bool IsConvertButtonEnabled() const;` — Whether Convert button is enabled
- L110 _private prototype_ `FReply OnCurvePreviewDoubleClick( const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent );` — Called when user double clicks on the curve preview to open a full size editor
- L115 _private prototype_ `static void CopyCurveData( const FRichCurve* SrcCurve, FRichCurve* DestCurve );` — Copies data from one Rich Curve to another
- L120 _private prototype_ `void DestroyPopOutWindow();` — Destroys the pop out window used for editing internal curves.
- L124 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Cached RuntimeFloatCurve struct handle
- L127 _private member_ `TSharedPtr<IPropertyHandle> ExternalCurveHandle;` — Cached External Curve handle
- L130 _private member_ `TSharedPtr<SCurveEditor> CurveWidget;` — Small preview Curve Editor
- L133 _private member_ `TWeakPtr<SWindow> CurveEditorWindow;` — Window for pop out Curve Editor
- L136 _private member_ `FRuntimeFloatCurve* RuntimeCurve;` — Cached pointer to the actual RuntimeFloatCurve struct
- L139 _private member_ `UObject* Owner;` — Object that owns the RuntimeFloatCurve
- L142 _private member_ `float ViewMinInput;` — View Min Input for the Curve Editor
- L145 _private member_ `float ViewMaxInput;` — View Max Input for the Curve Editor
- L148 _private member_ `static const FVector2D DEFAULT_WINDOW_SIZE;` — Size of the pop out Curve Editor window

### `Source/Editor/DetailCustomizations/Private/CurveVectorCustomization.h` (Private)


#### class `FCurveVectorCustomization`  
`class FCurveVectorCustomization : public IPropertyTypeCustomization, public FCurveOwnerInterface`  
_L26-141_
- inherits: `IPropertyTypeCustomization,FCurveOwnerInterface`
- desc: Customizes a RuntimeVectorCurve struct to display a Curve Editor
- L29 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L31 _public prototype_ `virtual ~FCurveVectorCustomization();`
- L34 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L35 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L39 _public prototype_ `virtual TArray<FRichCurveEditInfoConst> GetCurves() const override;` — `UE_DEPRECATED(5.6, "Use version taking a TAdderReserverRef")` — FCurveOwnerInterface interface
- L40 _public prototype_ `virtual void GetCurves(TAdderReserverRef<FRichCurveEditInfoConst> Curves) const override;`
- L41 _public prototype_ `virtual TArray<FRichCurveEditInfo> GetCurves() override;`
- L42 _public prototype_ `virtual void ModifyOwner() override;`
- L43 _public prototype_ `virtual TArray<const UObject*> GetOwners() const override;`
- L44 _public prototype_ `virtual void MakeTransactional() override;`
- L45 _public prototype_ `virtual void OnCurveChanged(const TArray<FRichCurveEditInfo>& ChangedCurveEditInfos) override;`
- L46 _public prototype_ `virtual bool IsValidCurve( FRichCurveEditInfo CurveInfo ) override;`
- L52 _private prototype_ `FCurveVectorCustomization();` — Constructor
- L57 _private function_ `float GetViewMinInput() const` — Get View Min Input for the Curve Editor
- L62 _private function_ `float GetViewMaxInput() const` — Get View Min Input for the Curve Editor
- L67 _private prototype_ `float GetTimelineLength() const;` — Get Timeline Length for the Curve Editor
- L72 _private prototype_ `void SetInputViewRange(float InViewMinInput, float InViewMaxInput);` — Set View Min and Max Inputs for the Curve Editor
- L77 _private prototype_ `void OnExternalCurveChanged(TSharedRef<IPropertyHandle> CurvePropertyHandle);` — Called when RuntimeVectorCurve's External Curve is changed
- L82 _private prototype_ `FReply OnCreateButtonClicked();` — Called when button clicked to create an External Vector Curve
- L87 _private prototype_ `bool IsCreateButtonEnabled() const;` — Whether Create button is enabled
- L92 _private prototype_ `FReply OnConvertButtonClicked();` — Called when button clicked to convert External Curve to internal curve
- L97 _private prototype_ `bool IsConvertButtonEnabled() const;` — Whether Convert button is enabled
- L102 _private prototype_ `FReply OnCurvePreviewDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);` — Called when user double clicks on the curve preview to open a full size editor
- L107 _private prototype_ `static void CopyCurveData(const FRichCurve* SrcCurve, FRichCurve* DestCurve);` — Copies data from one Rich Curve to another
- L112 _private prototype_ `void DestroyPopOutWindow();` — Destroys the pop out window used for editing internal curves.
- L116 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Cached RuntimeCurveLinearColor struct handle
- L119 _private member_ `TSharedPtr<IPropertyHandle> ExternalCurveHandle;` — Cached External Curve handle
- L122 _private member_ `TSharedPtr<SCurveEditor> CurveWidget;` — Small preview Curve Editor
- L125 _private member_ `TWeakPtr<SWindow> CurveEditorWindow;` — Window for pop out Curve Editor
- L128 _private member_ `FRuntimeVectorCurve* RuntimeCurve;` — Cached pointer to the actual RuntimeVectorCurve struct
- L131 _private member_ `UObject* Owner;` — Object that owns the RuntimeFloatCurve
- L134 _private member_ `float ViewMinInput;` — View Min Input for the Curve Editor
- L137 _private member_ `float ViewMaxInput;` — View Max Input for the Curve Editor
- L140 _private member_ `static const FVector2D DEFAULT_WINDOW_SIZE;` — Size of the pop out Curve Editor window

### `Source/Editor/DetailCustomizations/Private/CustomPrimitiveDataCustomization.h` (Private)


#### class `FCustomPrimitiveDataCustomization`  
`class FCustomPrimitiveDataCustomization : public IPropertyTypeCustomization`  
_L38-131_
- inherits: `IPropertyTypeCustomization`
- L41 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L43 _public prototype_ `FCustomPrimitiveDataCustomization();`
- L44 _public prototype_ `~FCustomPrimitiveDataCustomization();`
- L47 _public prototype_ `void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L48 _public prototype_ `void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L52 _private member_ `bool bDeferringRefresh = false;` — TODO [jonathan.bard] Remove on non-release branch
- L54 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtils;`
- L55 _private member_ `TSharedPtr<IPropertyHandle> DataHandle;`
- L56 _private member_ `TSharedPtr<IPropertyHandleArray> DataArrayHandle;`
- L58 _private member_ `TMap<TWeakObjectPtr<UPrimitiveComponent>, TSet<TSoftObjectPtr<UMaterial>>> ComponentsToWatch;`
- L59 _private member_ `TMap<TWeakObjectPtr<UPrimitiveComponent>, uint32> ComponentMaterialCounts;`
- L60 _private member_ `TSet<TSoftObjectPtr<UMaterialInterface>> MaterialsToWatch;`
- L62 _private member_ `TMap<uint8, TArray<FCustomPrimitiveDataParameter>> VectorParameterData;`
- L63 _private member_ `TMap<uint8, TArray<FCustomPrimitiveDataParameter>> ScalarParameterData;`
- L64 _private member_ `TMap<uint8, TSharedPtr<SColorBlock>> ColorBlocks;`
- L71 _private prototype_ `IDetailGroup* CreateVectorGroup(IDetailChildrenBuilder& ChildBuilder, uint8 PrimIdx, bool bDataEditable, int32 NumElements, IPropertyTypeCustomizationUtils& CustomizationUtils);` — Creates a group for the specified vector parameter, with a header that contains the vector parameter name and a color block that opens a color picker when clicked. Also contains add, delete and reset to default buttons to quickly populate a vector parameter
- L80 _private prototype_ `void CreateParameterRow(IDetailChildrenBuilder& ChildBuilder, uint8 PrimIdx, TSharedPtr<IPropertyHandle> ElementHandle, bool bDataEditable, IDetailGroup* VectorGroup, IPropertyTypeCustomizationUtils& CustomizationUtils);` — Creates a row for the specified primitive index. Will create hyperlinks for each parameter, to take the user to the parameter's node. If there are multiple unique parameters for the one row, it will fill the name content with each individual parameter name, or mention that the row is undefined for a component. If the parameter doesn't have an element yet, provides an add button for the user to quickly add elements up until that parameter.
- L83 _private prototype_ `template<typename Predicate> void ForEachSelectedComponent(Predicate Pred);`
- L84 _private prototype_ `bool IsSelected(UPrimitiveComponent* Component) const;`
- L86 _private prototype_ `void Cleanup();`
- L89 _private prototype_ `void PopulateParameterData(UPrimitiveComponent* PrimitiveComponent, int32& MaxPrimitiveDataIndex);` — Populates our parameter data for scalar and vector parameters. Updates the max primitive index if necessary.
- L91 _private prototype_ `void RequestRefresh();`
- L92 _private prototype_ `void OnElementsModified(const enum FPropertyAccess::Result OldAccessResult, const uint32 OldNumElements);`
- L93 _private prototype_ `void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);`
- L94 _private prototype_ `void OnMaterialCompiled(UMaterialInterface* Material);`
- L97 _private prototype_ `void OnNavigate(TWeakObjectPtr<UMaterialInterface> Material, FGuid ExpressionID);` — Will open the material editor to the specified parameter expression when a user clicks a hyperlink
- L100 _private prototype_ `void OnAddedDesiredPrimitiveData(uint8 PrimIdx);` — Adds elements to the primitive data array up until and including the specified PrimIdx. Also initializes elements with defaults from material interface
- L103 _private prototype_ `void OnRemovedPrimitiveData(uint8 PrimIdx);` — Remove all elements up until and including this primitive index
- L105 _private prototype_ `FLinearColor GetVectorColor( uint8 PrimIdx) const;`
- L106 _private prototype_ `void SetVectorColor(FLinearColor NewColor, uint8 PrimIdx);`
- L109 _private prototype_ `void SetDefaultValue(uint8 PrimIdx);` — Iterates through each parameter, and sets their values to the material interface's defaults on a per-component basis
- L112 _private prototype_ `void SetDefaultVectorValue(uint8 PrimIdx);` — Helper method to SetDefaultValue for vectors, but makes one transaction for all edits
- L114 _private prototype_ `FReply OnMouseButtonDownColorBlock(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, uint8 PrimIdx);`
- L115 _private prototype_ `void OnColorPickerCancelled(FLinearColor OriginalColor, uint8 PrimIdx);`
- L116 _private prototype_ `void OnColorPickerWindowClosed(const TSharedRef<SWindow>& Window);`
- L118 _private prototype_ `TSharedRef<SWidget> CreateNameWidget(int32 PrimIdx, TSharedRef<SWidget> ParameterName, IPropertyTypeCustomizationUtils& CustomizationUtils) const;`
- L121 _private prototype_ `TSharedRef<class SHyperlink> CreateHyperlink(FText Text, TWeakObjectPtr<UMaterialInterface> Material, const FGuid& ExpressionId);` — Hyperlink that's used for navigating to parameters
- L124 _private prototype_ `TSharedRef<SWidget> GetUndeclaredParameterWidget(int32 PrimIdx, IPropertyTypeCustomizationUtils& CustomizationUtils) const;` — Default widget that's used when a component is missing declared parameters for the specified primitive index
- L127 _private prototype_ `TSharedRef<SWidget> CreateWarningWidget(TSharedRef<SWidget> Content, FText WarningText) const;` — Creates a widget wraps content with a warning icon, border and tooltip text
- L130 _private prototype_ `enum FPropertyAccess::Result GetNumElements(uint32& NumElements) const;` — Get the number of elements and the access result of our primitive data array

### `Source/Editor/DetailCustomizations/Private/DataTableCategoryCustomization.h` (Private)


#### class `FDataTableCategoryCustomizationLayout`  
`class FDataTableCategoryCustomizationLayout : public IPropertyTypeCustomization`  
_L21-370_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes a DataTable asset to use a dropdown
- L24 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L30 _public function_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override` — IPropertyTypeCustomization interface
- L48 _public function_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L131 _private function_ `TSharedPtr<FString> InitRowWidgetContent()` — Init the contents the combobox sources its data off
- L194 _private function_ `TSharedPtr<FString> InitColumnWidgetContent()` — Init the contents the combobox sources its data off
- L239 _private function_ `TSharedRef<SWidget> HandleColumnNameComboBoxGenarateWidget(TSharedPtr<FString> Item)` — Return the representation of the the column names to display
- L246 _private function_ `TSharedRef<SWidget> HandleRowContentsComboBoxGenarateWidget(TSharedPtr<FString> Item)` — Return the representation of the the row names to display
- L253 _private function_ `FText GetColumnNameComboBoxContentText() const` — Display the current column selection
- L273 _private function_ `FText GetRowContentsComboBoxContentText() const` — Display the current row selection
- L293 _private function_ `void OnDataTableChanged()` — Delegate to refresh the drop down when the datatable changes
- L305 _private function_ `void OnColumnSelectionChanged(TSharedPtr<FString> SelectedItem, ESelectInfo::Type SelectInfo)` — Update the root data on a change of selection
- L319 _private function_ `void OnRowSelectionChanged(TSharedPtr<FString> SelectedItem, ESelectInfo::Type SelectInfo)` — Update the root data on a change of selection
- L329 _private function_ `bool ShouldFilterAsset(const FAssetData& AssetData)` — Returns true if we should hide asset due to wrong type
- L355 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString> > > ColumnNameComboBox;` — The column combobox object
- L357 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString> > > RowContentsComboBox;` — The row combobox object
- L359 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle to the struct properties being customized
- L360 _private member_ `TSharedPtr<IPropertyHandle> DataTablePropertyHandle;`
- L361 _private member_ `TSharedPtr<IPropertyHandle> RowContentsPropertyHandle;`
- L362 _private member_ `TSharedPtr<IPropertyHandle> ColumnNamePropertyHandle;`
- L364 _private member_ `TArray<TSharedPtr<FString> > RowContents;` — A cached copy of strings to populate the combo box
- L366 _private member_ `TArray<TSharedPtr<FString> > ColumnNames;` — A cached copy of strings to populate the column combo box
- L368 _private member_ `FName RowTypeFilter;` — The MetaData derived filter for the row type
- L369 _private member_ `UScriptStruct* RowFilterStruct = nullptr;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define LOCTEXT_NAMESPACE "FDataTableCategoryCustomizationLayout"`

### `Source/Editor/DetailCustomizations/Private/DataTableCustomization.h` (Private)


#### class `FDataTableCustomizationLayout`  
`class FDataTableCustomizationLayout : public IPropertyTypeCustomization`  
_L20-64_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes a DataTable asset to use a dropdown
- L23 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L29 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L31 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L35 _private prototype_ `bool GetCurrentValue(UDataTable*& OutDataTable, FName& OutName) const;` — Reads current value of handles
- L38 _private prototype_ `bool ShouldFilterAsset(const FAssetData& AssetData);` — Returns true if we should hide asset due to wrong type
- L41 _private prototype_ `void OnDataTableChanged();` — Delegate to refresh the drop down when the datatable changes
- L44 _private prototype_ `void OnSearchForReferences();` — Open reference viewer
- L47 _private prototype_ `void OnGetRowStrings(TArray< TSharedPtr<FString> >& OutStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems) const;` — Get list of all rows
- L50 _private prototype_ `FString OnGetRowValueString() const;` — Gets currently selected row display string
- L53 _private prototype_ `FText GetPreviewText() const;` — Enables previewing of a selected row value
- L56 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle to the struct properties being customized
- L57 _private member_ `TSharedPtr<IPropertyHandle> DataTablePropertyHandle;`
- L58 _private member_ `TSharedPtr<IPropertyHandle> RowNamePropertyHandle;`
- L60 _private member_ `FName RowTypeFilter;` — The MetaData derived filter for the row type
- L61 _private member_ `FName RowPreviewPropertyName;`
- L62 _private member_ `UScriptStruct* RowFilterStruct;`
- L63 _private member_ `bool bShowOnlyInnerProperties = false;`

### `Source/Editor/DetailCustomizations/Private/DateTimeStructCustomization.h` (Private)


#### class `FDateTimeStructCustomization`  
`class FDateTimeStructCustomization : public IPropertyTypeCustomization`  
_L20-88_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details view customization for the FDateTime structure.
- L30 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()` — Creates an instance of this class. @return The new instance.
- L39 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L40 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L43 _protected prototype_ `FDateTimeStructCustomization();`
- L48 _private prototype_ `FSlateColor HandleTextBoxForegroundColor() const;` — Handles getting the text color of the editable text box.
- L51 _private prototype_ `FText HandleTextBoxText() const;` — Handles getting the text to be displayed in the editable text box.
- L54 _private prototype_ `void HandleTextBoxTextChanged(const FText& NewText);` — Handles changing the value in the editable text box.
- L57 _private prototype_ `void HandleTextBoxTextCommited(const FText& NewText, ETextCommit::Type CommitInfo);` — Handles committing the text in the editable text box.
- L61 _private member_ `static const int32 TIMEZONE_UTC = 0;` — UTC constant
- L64 _private prototype_ `static int32 GetLocalTimezone();` — Get our local timezone based on user settings
- L67 _private prototype_ `static bool ParseDateTimeZone(const FString& DateTimeZoneString, FDateTime& OutDateTime);` — Parse a DateTime string for timezone information and then convert that time into UTC
- L70 _private prototype_ `static FDateTime ConvertTime(const FDateTime& InDate, int32 InTimezone, int32 OutTimezone);` — Convert a time to another timezone
- L73 _private prototype_ `static FString ToDateTimeZoneString(const FDateTime& UTCDate);` — Convert a Date to a string with the users preferred local timezone
- L76 _private prototype_ `static FORCEINLINE int32 ConvertShortTimezone(int32 ShortTimezone);` — Convert a short timezone to a longer timezone
- L81 _private member_ `bool InputValid;` — Holds a flag indicating whether the current input is a valid GUID.
- L84 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Holds a handle to the property being edited.
- L87 _private member_ `TSharedPtr<SEditableTextBox> TextBox;` — Holds the text box for editing the Guid.

### `Source/Editor/DetailCustomizations/Private/DebugCameraControllerSettingsCustomization.h` (Private)


#### class `FDebugCameraControllerSettingsViewModeIndexCustomization`  
`class FDebugCameraControllerSettingsViewModeIndexCustomization : public IPropertyTypeCustomization`  
_L11-22_
- inherits: `IPropertyTypeCustomization`
- L14 _public prototype_ `FDebugCameraControllerSettingsViewModeIndexCustomization();`
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L20 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`

### `Source/Editor/DetailCustomizations/Private/DecalComponentDetails.h` (Private)


#### class `FDecalComponentDetails`  
`class FDecalComponentDetails : public IDetailCustomization`  
_L10-24_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L21 _private prototype_ `static bool ShouldFilterDecalMaterialAsset(FAssetData const& AssetData);` — Returns false if asset should appear in filtered list.
- L23 _private prototype_ `static bool IsDecalMaterialAssetRecursive(FAssetData const& AssetData, IAssetRegistry const& AssetRegistry);` — Returns true if this asset is a decal material, or child of a decal material.

### `Source/Editor/DetailCustomizations/Private/DeviceProfileDetails.h` (Private)


#### class `FDeviceProfileParentPropertyDetails`  
`class FDeviceProfileParentPropertyDetails : public TSharedFromThis<FDeviceProfileParentPropertyDetails>`  
_L28-83_
- inherits: `TSharedFromThis<FDeviceProfileParentPropertyDetails>`
- desc: Helper which implements details panel customizations for a device profiles parent property
- L39 _public prototype_ `FDeviceProfileParentPropertyDetails(IDetailLayoutBuilder* InDetailBuilder);` — Constructor for the parent property details view @param InDetailsBuilder Where we are adding our property view to
- L45 _public prototype_ `void CreateParentPropertyView();` — Create the parent property view for the device profile
- L55 _private prototype_ `TSharedRef<SWidget> HandleDeviceProfileParentComboBoxGenarateWidget(TSharedPtr<FString> InItem);` — Select a parent Combo-box listings @param InItem The prospective parent profile name we are creating a listing for @return The slate widget with the listed profile name
- L63 _private prototype_ `void HandleDeviceProfileParentSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);` — Handle a new parent profile being selected for the active device profile @param NewSelection The name of the selected parent profile @param SelectionInfo	The selection type information
- L68 _private prototype_ `void OnParentPropertyChanged();` — Delegate used when the device profiles parent is updated from any source.
- L73 _private member_ `IDetailLayoutBuilder* DetailBuilder;` — A handle to the detail view builder
- L76 _private member_ `TSharedPtr<IPropertyHandle> ParentPropertyNameHandle;` — Access to the Parent Property
- L79 _private member_ `TArray<TSharedPtr<FString>> AvailableParentProfiles;` — Collection of possible Device Profiles we can use as a parent for this profile
- L82 _private member_ `class UDeviceProfile* ActiveDeviceProfile;` — A reference to the object we are showing these properties for

#### class `FDeviceProfileConsoleVariablesPropertyDetails`  
`class FDeviceProfileConsoleVariablesPropertyDetails : public TSharedFromThis<FDeviceProfileConsoleVariablesPropertyDetails>`  
_L92-173_
- inherits: `TSharedFromThis<FDeviceProfileConsoleVariablesPropertyDetails>`
- desc: Helper which implements details panel customizations for a device profiles console variables property
- L103 _public prototype_ `FDeviceProfileConsoleVariablesPropertyDetails(IDetailLayoutBuilder* InDetailBuilder);` — Constructor for the active profiles' console variables property details view @param InDetailsBuilder Where we are adding our property view to
- L109 _public prototype_ `void CreateConsoleVariablesPropertyView();` — Create the Console Variables property view for the device profile
- L118 _private prototype_ `void HandleCVarAdded(const FString& SelectedCVar);` — Action when a CVar has been selected for add to the device profile @param SelectedCVar The CVar added
- L127 _private prototype_ `void CreateRowWidgetForCVarProperty(TSharedPtr<IPropertyHandle> InProperty, IDetailGroup& InGroup) const;` — Action when a CVar has been selected for add to the device profile @param InProperty The property handle of which we are creating a row for. @param InGroup The group the property is to be listed under.
- L137 _private prototype_ `void OnCVarValueCommited(const FText& NewValue, ETextCommit::Type CommitInfo, TSharedPtr<IPropertyHandle> CVarPropertyHandle);` — Action when a CVar has been updated on the device profile @param NewValue The New value for the given CVar @param CommitInfo Details of how the action was committed @param CVarPropertyHandle The CVar property which has been updated
- L146 _private prototype_ `FReply OnRemoveCVarProperty(TSharedPtr<IPropertyHandle> InProperty);` — Action when a CVar has removed from the device profile @param InProperty The property which has been removed from the profile @return Whether the event was handled
- L155 _private prototype_ `FReply OnRemoveAllFromGroup(int32 CVarCategory);` — Action when a group of CVars have been removed from the device profile @param CVarCategory - The category of the group all CVars have been removed for (@see ECVarGroup). @return Whether the event was handled
- L161 _private prototype_ `void OnCVarPropertyChanged();` — Delegate used when the console variables are updated from any source.
- L166 _private member_ `IDetailLayoutBuilder* DetailBuilder;` — A handle to the detail view builder
- L169 _private member_ `TSharedPtr<IPropertyHandle> CVarsHandle;` — A handle to the CVars array where the entire CVar collection is
- L172 _private member_ `TMap<FString, IDetailGroup*> CVarDetailGroups;` — The collection of console variable property groups and their id's

#### class `FDeviceProfileDetails`  
`class FDeviceProfileDetails : public IDetailCustomization`  
_L182-213_
- inherits: `IDetailCustomization`
- desc: Implements details panel customizations for UDeviceProfile fields.
- L192 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()` — Makes a new instance of this device profile detail layout class. @return The created instance.
- L201 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& InDetailBuilder ) override;`
- L206 _private member_ `TSharedPtr<FDeviceProfileParentPropertyDetails> ParentProfileDetails;` — Reference to the parent profile property view
- L209 _private member_ `TSharedPtr<FDeviceProfileConsoleVariablesPropertyDetails> ConsoleVariablesDetails;` — Reference to the console variables property view
- L212 _private member_ `TSharedPtr<FDeviceProfileTextureLODSettingsDetails> TextureLODSettingsDetails;` — Reference to the console variables property view

### `Source/Editor/DetailCustomizations/Private/DialogueStructsCustomizations.h` (Private)


#### class `FDialogueContextStructCustomization`  
`class FDialogueContextStructCustomization : public IPropertyTypeCustomization`  
_L10-20_
- inherits: `IPropertyTypeCustomization`
- L14 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — @return A new instance of this class
- L17 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface begin
- L18 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`

#### class `FDialogueWaveParameterStructCustomization`  
`class FDialogueWaveParameterStructCustomization : public IPropertyTypeCustomization`  
_L22-32_
- inherits: `IPropertyTypeCustomization`
- L26 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — @return A new instance of this class
- L29 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface begin
- L30 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`

### `Source/Editor/DetailCustomizations/Private/DialogueWaveDetails.h` (Private)


#### class `FDialogueContextMappingNodeBuilder`  
`class FDialogueContextMappingNodeBuilder : public IDetailCustomNodeBuilder, public TSharedFromThis<FDialogueContextMappingNodeBuilder>`  
_L21-66_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FDialogueContextMappingNodeBuilder>`
- L24 _public prototype_ `FDialogueContextMappingNodeBuilder(IDetailLayoutBuilder* InDetailLayoutBuilder, const TSharedPtr<IPropertyHandle>& InPropertyHandle);`
- L27 _public function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRebuildChildren) override` — IDetailCustomNodeBuilder interface
- L28 _public function_ `virtual bool RequiresTick() const override`
- L29 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L30 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L31 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L32 _public function_ `virtual bool InitiallyCollapsed() const override`
- L33 _public function_ `virtual FName GetName() const override`
- L36 _private prototype_ `void RemoveContextButton_OnClick();`
- L38 _private prototype_ `FText LocalizationKeyFormatEditableText_GetText() const;`
- L39 _private prototype_ `void LocalizationKeyFormatEditableText_OnTextCommitted(const FText& InNewText, ETextCommit::Type InCommitType);`
- L40 _private prototype_ `bool LocalizationKeyFormatEditableText_IsReadyOnly() const;`
- L41 _private prototype_ `void LocalizationKeyFormatEditableText_UpdateErrorText();`
- L43 _private prototype_ `FText LocalizationKey_GetText() const;`
- L47 _private member_ `FSimpleDelegate OnRebuildChildren;` — Called to rebuild the children of the detail tree
- L50 _private member_ `IDetailLayoutBuilder* DetailLayoutBuilder;` — Associated detail layout builder
- L53 _private member_ `TSharedPtr<IPropertyHandle> ContextMappingPropertyHandle;` — Property handle to associated context mapping
- L56 _private member_ `TSharedPtr<IPropertyHandle> LocalizationKeyFormatPropertyHandle;` — Property handle to the localization key format property within this context mapping
- L59 _private member_ `TSharedPtr<SEditableTextBox> LocalizationKeyFormatEditableText;` — Pointer to the editable text box used to edit the localization key format string
- L62 _private member_ `double LastLocalizationKeyErrorUpdateTimestamp;` — Timestamp the last time the error information for the localization key was updated
- L65 _private member_ `FText LocalizationKeyErrorMsg;` — The error message that the localized key is currently showing

#### class `FDialogueWaveDetails`  
`class FDialogueWaveDetails : public IDetailCustomization`  
_L68-83_
- inherits: `IDetailCustomization`
- L72 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L75 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails interface
- L78 _private prototype_ `FReply AddDialogueContextMapping_OnClicked();`
- L82 _private member_ `IDetailLayoutBuilder* DetailLayoutBuilder;` — Associated detail layout builder

### `Source/Editor/DetailCustomizations/Private/DialogueWaveWidgets.h` (Private)


#### class `SDialogueVoicePropertyEditor`  
`class SDialogueVoicePropertyEditor : public SCompoundWidget`  
_L29-100_
- inherits: `SCompoundWidget`
- L32 _public function_ `SLATE_BEGIN_ARGS( SDialogueVoicePropertyEditor ) : _IsEditable(true) , _ShouldCenterThumbnail(false)`
- L36 _public prototype_ `SLATE_ARGUMENT( bool, IsEditable ) SLATE_ARGUMENT( bool, ShouldCenterThumbnail ) SLATE_EVENT( FOnShouldFilterAsset, OnShouldFilterAsset ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InPropertyHandle, const TSharedRef<FAssetThumbnailPool>& InAssetThumbnailPool );`
- L43 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L45 _public prototype_ `FText GetDialogueVoiceDescription() const;`
- L48 _private prototype_ `FText OnGetToolTip() const;`
- L49 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();`
- L50 _private prototype_ `void CloseMenu();`
- L57 _private prototype_ `bool OnIsAssetAcceptableForDrop( TArrayView<FAssetData> InAssets ) const;` — Called when an asset is being dragged over this item @param InObject	The asset being dragged over
- L64 _private prototype_ `void OnAssetDropped( const FDragDropEvent&, TArrayView<FAssetData> InAssets );` — Called when an asset dropped onto the list item @param InObject	The asset being dropped
- L66 _private prototype_ `bool CanUseSelectedAsset();`
- L67 _private prototype_ `void OnUseSelectedDialogueVoice();`
- L69 _private prototype_ `void ReplaceDialogueVoice( const UDialogueVoice* const NewDialogueVoice );`
- L71 _private prototype_ `bool CanBrowseToAsset();`
- L72 _private prototype_ `void OnBrowseToDialogueVoice();`
- L74 _private prototype_ `void OnGetAllowedClassesForAssetPicker( TArray<const UClass*>& OutClasses );`
- L76 _private prototype_ `void OnAssetSelectedFromPicker( const FAssetData& InAssetData );`
- L81 _private prototype_ `FText GetDialogueVoicePath() const;` — Called to get the dialogue voice path that should be displayed
- L86 _private prototype_ `void OnDialogueVoicePathChanged( const FText& NewText, ETextCommit::Type TextCommitType );` — Called when the dialogue voice path is changed by a user
- L91 _private prototype_ `void GoToAssetInContentBrowser( TWeakObjectPtr<UObject> Object );` — Finds the asset in the content browser
- L94 _protected member_ `TSharedPtr<IPropertyHandle> DialogueVoicePropertyHandle;`
- L95 _protected member_ `bool IsEditable;`
- L96 _protected member_ `TSharedPtr<FAssetThumbnail> AssetThumbnail;`
- L97 _protected member_ `TSharedPtr<FAssetThumbnailPool> AssetThumbnailPool;`
- L98 _protected member_ `TSharedPtr<SComboButton> ComboButton;`
- L99 _protected member_ `FOnShouldFilterAsset OnShouldFilterAsset;`

#### class `STargetsSummaryWidget`  
`class STargetsSummaryWidget : public SCompoundWidget`  
_L102-130_
- inherits: `SCompoundWidget`
- L105 _public function_ `SLATE_BEGIN_ARGS( STargetsSummaryWidget ) : _IsEditable(true) , _WrapWidth(0.0f)`
- L109 _public prototype_ `SLATE_ARGUMENT( bool, IsEditable ) SLATE_ATTRIBUTE( float, WrapWidth ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InPropertyHandle, const TSharedRef<FAssetThumbnailPool>& InAssetThumbnailPool );`
- L114 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L116 _public prototype_ `FText GetDialogueVoiceDescription() const;`
- L119 _private prototype_ `float GetPreferredWidthForWrapping() const;`
- L120 _private prototype_ `bool FilterTargets( const struct FAssetData& InAssetData );`
- L121 _private prototype_ `void GenerateContent();`
- L124 _private member_ `TSharedPtr<IPropertyHandle> TargetsPropertyHandle;`
- L125 _private member_ `bool IsEditable;`
- L126 _private member_ `TAttribute<float> WrapWidth;`
- L127 _private member_ `TSharedPtr<FAssetThumbnailPool> AssetThumbnailPool;`
- L128 _private member_ `TArray<const UDialogueVoice*> DisplayedTargets;`
- L129 _private member_ `float AllottedWidth;`

#### class `SDialogueContextHeaderWidget`  
`class SDialogueContextHeaderWidget : public SCompoundWidget`  
_L132-153_
- inherits: `SCompoundWidget`
- L135 _public function_ `SLATE_BEGIN_ARGS( SDialogueContextHeaderWidget )`
- L136 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InPropertyHandle, const TSharedRef<FAssetThumbnailPool>& InAssetThumbnailPool );`
- L139 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L142 _private prototype_ `bool IsSpeakerValid() const;`
- L143 _private prototype_ `bool IsTargetSetValid() const;`
- L144 _private prototype_ `void AddTargetButton_OnClick();`
- L145 _private prototype_ `void RemoveTargetButton_OnClick();`
- L146 _private prototype_ `void EmptyTargetsButton_OnClick();`
- L149 _private member_ `TSharedPtr<IPropertyHandle> ContextPropertyHandle;`
- L151 _private member_ `TSharedPtr<SErrorHint> SpeakerErrorHint;`
- L152 _private member_ `TSharedPtr<SErrorHint> TargetsErrorHint;`

### `Source/Editor/DetailCustomizations/Private/DirectionalLightComponentDetails.h` (Private)


#### class `FDirectionalLightComponentDetails`  
`class FDirectionalLightComponentDetails : public IDetailCustomization`  
_L11-19_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L18 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

### `Source/Editor/DetailCustomizations/Private/DirectoryPathStructCustomization.h` (Private)


#### class `FDirectoryPathStructCustomization`  
`class FDirectoryPathStructCustomization : public IPropertyTypeCustomization`  
_L15-55_
- inherits: `IPropertyTypeCustomization`
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L21 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L23 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L28 _private prototype_ `FReply OnPickContent(TSharedRef<IPropertyHandle> PropertyHandle, const bool bForceShowPluginContent, const bool bForceShowEngineContent);` — Delegate used to display a directory picker
- L31 _private prototype_ `FReply OnPickDirectory(TSharedRef<IPropertyHandle> PropertyHandle, const bool bRelativeToGameContentDir, const bool bUseRelativePaths) const;` — Delegate used to display a directory picker
- L34 _private prototype_ `bool IsValidPath(const FString& AbsolutePath, const bool bRelativeToGameContentDir, FText* const OutReason = nullptr) const;` — Check whether that the chosen path is valid
- L37 _private prototype_ `void OnPathPicked(const FString& Path, TSharedRef<IPropertyHandle> PropertyHandle);` — Called when a path is picked from the path picker
- L40 _private prototype_ `bool IsBrowseEnabled(TSharedRef<IPropertyHandle> PropertyHandle) const;` — Delegate to determine whether the browse button should be enabled
- L45 _private member_ `TSharedPtr<SButton> BrowseButton;` — The browse button widget
- L48 _private member_ `TSharedPtr<SButton> PickerButton;` — The pick button widget
- L51 _private member_ `TSharedPtr<IMenu> PickerMenu;` — The pick button popup menu
- L54 _private member_ `FString AbsoluteGameContentDir;` — Absolute path to the game content directory

### `Source/Editor/DetailCustomizations/Private/DistanceDatumStructCustomization.h` (Private)


#### class `FDistanceDatumStructCustomization`  
`class FDistanceDatumStructCustomization : public IPropertyTypeCustomization`  
_L16-37_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes a Distance Datum struct to improve naming when used as a parameter
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L27 _public prototype_ `virtual ~FDistanceDatumStructCustomization();` — Destructor
- L30 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L31 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L36 _public prototype_ `explicit FDistanceDatumStructCustomization(FPrivateToken);` — Constructor

#### struct `FDistanceDatumStructCustomization::FPrivateToken`  
`struct FPrivateToken`  
_L19-19_
- L19 _public prototype_ `struct FPrivateToken`

#### class `FCrossFadeCustomization`  
`class FCrossFadeCustomization : public IDetailCustomization`  
_L39-47_
- inherits: `IDetailCustomization`
- L43 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L46 _public prototype_ `static TSharedRef< IDetailCustomization > MakeInstance();`

### `Source/Editor/DetailCustomizations/Private/DocumentationActorDetails.h` (Private)


#### class `FDocumentationActorDetails`  
`class FDocumentationActorDetails : public IDetailCustomization`  
_L16-43_
- inherits: `IDetailCustomization`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L26 _public prototype_ `FReply OnHelpButtonClicked();` — Handler for clicking the help button
- L29 _public prototype_ `FText OnGetButtonText() const;` — Handler to get the text for the button
- L32 _public prototype_ `FText OnGetButtonTooltipText() const;` — Handler to get the text for the button tooltip
- L35 _public prototype_ `bool IsButtonEnabled() const;` — Handler to determine if the button is enabled (link is valid)
- L39 _private member_ `TWeakObjectPtr<ADocumentationActor> SelectedDocumentationActor;` — The first documentation actor that we are showing in the details panel
- L42 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Handle to the string property

### `Source/Editor/DetailCustomizations/Private/EnvQueryParamInstanceCustomization.h` (Private)


#### class `FEnvQueryParamInstanceCustomization`  
`class FEnvQueryParamInstanceCustomization : public IPropertyTypeCustomization`  
_L17-52_
- inherits: `IPropertyTypeCustomization`
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance( );`
- L27 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L28 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L32 _protected member_ `TSharedPtr<IPropertyHandle> NameProp;`
- L33 _protected member_ `TSharedPtr<IPropertyHandle> ValueProp;`
- L34 _protected member_ `TSharedPtr<IPropertyHandle> TypeProp;`
- L36 _protected prototype_ `TOptional<float> GetParamNumValue() const;`
- L37 _protected prototype_ `void OnParamNumValueChanged(float FloatValue) const;`
- L38 _protected prototype_ `EVisibility GetParamNumValueVisibility() const;`
- L40 _protected prototype_ `ECheckBoxState GetParamBoolValue() const;`
- L41 _protected prototype_ `void OnParamBoolValueChanged(ECheckBoxState BoolValue) const;`
- L42 _protected prototype_ `EVisibility GetParamBoolValueVisibility() const;`
- L44 _protected prototype_ `FText GetHeaderDesc() const;`
- L45 _protected prototype_ `void OnTypeChanged();`
- L46 _protected prototype_ `void InitCachedTypes();`
- L48 _protected member_ `EAIParamType ParamType;`
- L49 _protected member_ `mutable uint8 CachedBool : 1;`
- L50 _protected member_ `mutable float CachedFloat;`
- L51 _protected member_ `mutable int32 CachedInt;`

### `Source/Editor/DetailCustomizations/Private/FbxImportUIDetails.h` (Private)


#### enum `EConflictDialogType`  
`enum EConflictDialogType`  
_L26-30_
- L28 _public enumerator_ `Conflict_Material`
- L29 _public enumerator_ `Conflict_Skeleton`

#### enum `EMaterialImportMethod`  
`enum class EMaterialImportMethod : int32`  
_L33-38_
- reflection: `UENUM()`
- L35 _public enumerator_ `CreateNewMaterials UMETA(DisplayName = "Create New Materials", ToolTip = "A new material will be created from the imported data.")`
- L36 _public enumerator_ `CreateNewInstancedMaterials UMETA(DisplayName = "Create New Instanced Materials", Tooltip = "A new material instance of the specified base material will be created and set with the imported material data.")`
- L37 _public enumerator_ `DoNotCreateMaterialString UMETA(DisplayName = "Do Not Create Material", Tooltip = "No materials will be created from the import data.")`

#### class `FFbxImportUIDetails`  
`class FFbxImportUIDetails : public IDetailCustomization, public FEditorUndoClient`  
_L40-141_
- inherits: `IDetailCustomization,FEditorUndoClient`
- L43 _public prototype_ `~FFbxImportUIDetails();`
- L46 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L49 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L52 _public prototype_ `void AddSubCategory(IDetailLayoutBuilder& DetailBuilder, FName MainCategoryName, TMap<FString, TArray<TSharedPtr<IPropertyHandle>>>& SubCategoriesProperties, TMap<FString, bool >& SubCategoriesAdvanced, TMap<FString, FText >& SubCategoriesTooltip);`
- L54 _public prototype_ `void RefreshCustomDetail();`
- L57 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L58 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L61 _public prototype_ `void CollectChildPropertiesRecursive(TSharedPtr<IPropertyHandle> Node, TArray<TSharedPtr<IPropertyHandle>>& OutProperties);`
- L63 _public prototype_ `void ConstructMaterialImportMethod(TSharedPtr<IPropertyHandle> ImportMaterialPropHandle, class IDetailCategoryBuilder& MaterialCategory);`
- L65 _public prototype_ `void ConstructBaseMaterialUI(TSharedPtr<IPropertyHandle> Handle, class IDetailCategoryBuilder& MaterialCategory);`
- L71 _public prototype_ `bool IsImportTypeMetaDataValid(EFBXImportType& ImportType, FString& MetaData);` — Checks whether a metadata string is valid for a given import type @param ImportType the type of mesh being imported @param MetaData the metadata string to validate
- L74 _public prototype_ `void ImportAutoComputeLodDistancesChanged();` — Called if the bAutoComputeLodDistances changes
- L77 _public prototype_ `void ValidateLodSettingsChanged(int32 MemberID);` — Called when the LODSettings changes
- L80 _public prototype_ `void ImportMaterialsChanged();` — Called if the bImportMaterials changes
- L83 _public prototype_ `void MeshImportModeChanged();` — Called if the mesh mode (static / skeletal) changes
- L86 _public prototype_ `void ImportMeshToggleChanged();` — Called if the import mesh option for skeletal meshes is changed
- L89 _public prototype_ `void BaseMaterialChanged();` — Called when the base material is changed
- L92 _public prototype_ `void OnBaseColor(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);` — Called user chooses base material properties
- L93 _public prototype_ `void OnDiffuseTextureColor(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);`
- L94 _public prototype_ `void OnNormalTextureColor(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);`
- L95 _public prototype_ `void OnEmmisiveTextureColor(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);`
- L96 _public prototype_ `void OnEmissiveColor(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);`
- L97 _public prototype_ `void OnSpecularTextureColor(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);`
- L98 _public prototype_ `void OnOpacityTextureColor(TSharedPtr<FString> Selection, ESelectInfo::Type SelectInfo);`
- L99 _public prototype_ `FReply MaterialBaseParamClearAllProperties();`
- L101 _public prototype_ `int32 GetMaterialImportMethodValue() const;`
- L102 _public prototype_ `void OnMaterialImportMethodChanged(int32 Value, ESelectInfo::Type SelectInfo);`
- L104 _public member_ `TWeakObjectPtr<UFbxImportUI> ImportUI;` — The UI data object being customised
- L105 _public member_ `IDetailLayoutBuilder* CachedDetailBuilder;` — The detail builder for this cusomtomisation
- L110 _private prototype_ `FFbxImportUIDetails();` — Use MakeInstance to create an instance of this class
- L113 _private prototype_ `void SetStaticMeshLODGroupWidget(IDetailPropertyRow& PropertyRow, const TSharedPtr<IPropertyHandle>& Handle);` — Sets a custom widget for the StaticMeshLODGroup property
- L116 _private prototype_ `void OnLODGroupChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo, TWeakPtr<IPropertyHandle> HandlePtr);` — Called when the StaticMeshLODGroup spinbox is changed
- L119 _private prototype_ `bool GetVertexOverrideColorEnabledState() const;` — Called to determine the visibility of the VertexOverrideColor property
- L120 _private prototype_ `bool GetSkeletalMeshVertexOverrideColorEnabledState() const;`
- L122 _private prototype_ `FReply ShowConflictDialog(EConflictDialogType DialogType);`
- L123 _private prototype_ `bool ShowCompareResult();`
- L126 _private member_ `TArray<FName> LODGroupNames;` — LOD group options.
- L127 _private member_ `TArray<TSharedPtr<FString>> LODGroupOptions;`
- L130 _private member_ `TSharedPtr<IPropertyHandle> StaticMeshLODGroupPropertyHandle;` — Cached StaticMeshLODGroup property handle
- L133 _private member_ `TSharedPtr<IPropertyHandle> VertexColorImportOptionHandle;` — Cached VertexColorImportOption property handle
- L134 _private member_ `TSharedPtr<IPropertyHandle> SkeletalMeshVertexColorImportOptionHandle;`
- L136 _private member_ `EMaterialImportMethod SelectedMaterialImportMethod;`
- L137 _private member_ `bool bShowBaseMaterialUI;`
- L139 _private member_ `TArray< TSharedPtr< FString > > BaseColorNames;`
- L140 _private member_ `TArray< TSharedPtr< FString > > BaseTextureNames;`

### `Source/Editor/DetailCustomizations/Private/FbxSceneImportDataDetails.h` (Private)


#### class `FFbxSceneImportDataDetails`  
`class FFbxSceneImportDataDetails : public IDetailCustomization`  
_L15-39_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L26 _public member_ `TWeakObjectPtr<UFbxSceneImportData> ImportData;` — The UI data object being customised
- L30 _private prototype_ `FReply OnBrowseClicked();`
- L33 _private prototype_ `FFbxSceneImportDataDetails();` — Use MakeInstance to create an instance of this class
- L36 _private member_ `TSharedPtr<IPropertyHandle> SourceFileFbxHandle;` — The path we want to change
- L38 _private member_ `TSharedPtr<SWidget> SourceFileValueWidget;` — The value widget for the source path

### `Source/Editor/DetailCustomizations/Private/FilePathStructCustomization.h` (Private)


#### class `FFilePathStructCustomization`  
`class FFilePathStructCustomization : public IPropertyTypeCustomization`  
_L14-51_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details view customization for the FFilePath structure.
- L24 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance( )` — Creates an instance of this class. @return The new instance.
- L33 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L34 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L39 _private prototype_ `FString HandleFilePathPickerFilePath( ) const;` — Callback for getting the selected path in the picker widget.
- L42 _private prototype_ `void HandleFilePathPickerPathPicked( const FString& PickedPath );` — Callback for picking a file in the file path picker.
- L46 _private member_ `TSharedPtr<IPropertyHandle> PathStringProperty;` — Pointer to the string that will be seet when changing the path
- L47 _private member_ `bool bLongPackageName;`
- L50 _private member_ `bool bRelativeToGameDir;` — Whether the output file path tries to be relative to the project directory

### `Source/Editor/DetailCustomizations/Private/FrameRateCustomization.h` (Private)


#### class `FFrameRateCustomization`  
`class FFrameRateCustomization : public IPropertyTypeCustomization`  
_L13-35_
- inherits: `IPropertyTypeCustomization`
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L24 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;`
- L25 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;`
- L30 _private prototype_ `FFrameRate GetFirstFrameRate() const;`
- L31 _private prototype_ `void SetFrameRate(FFrameRate NewFrameRate);`
- L32 _private prototype_ `bool HasMultipleValues() const;`
- L34 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`

### `Source/Editor/DetailCustomizations/Private/GeneralProjectSettingsDetails.h` (Private)


#### class `FGeneralProjectSettingsDetails`  
`class FGeneralProjectSettingsDetails : public IDetailCustomization`  
_L10-19_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Source/Editor/DetailCustomizations/Private/HardwareTargetingSettingsDetails.h` (Private)


#### class `FHardwareTargetingSettingsDetails`  
`class FHardwareTargetingSettingsDetails : public IDetailCustomization`  
_L10-19_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Source/Editor/DetailCustomizations/Private/HierarchicalSimplificationCustomizations.h` (Private)


#### class `FHierarchicalSimplificationCustomizations`  
`class FHierarchicalSimplificationCustomizations : public IPropertyTypeCustomization, public TOverrideResetToDefaultWithStaticUStruct<FHierarchicalSimplification>`  
_L14-31_
- inherits: `IPropertyTypeCustomization,TOverrideResetToDefaultWithStaticUStruct<FHierarchicalSimplification>`
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization instance
- L21 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L24 _protected prototype_ `EHierarchicalSimplificationMethod GetSelectedSimplificationMethod() const;`
- L26 _protected prototype_ `EVisibility IsProxyMeshSettingVisible() const;`
- L27 _protected prototype_ `EVisibility IsMergeMeshSettingVisible() const;`
- L28 _protected prototype_ `EVisibility IsApproximateMeshSettingVisible() const;`
- L30 _protected member_ `TSharedPtr< IPropertyHandle > SimplificationMethodPropertyHandle;`

### `Source/Editor/DetailCustomizations/Private/ImportantToggleSettingCustomization.h` (Private)


#### class `FImportantToggleSettingCustomization`  
`class FImportantToggleSettingCustomization : public IDetailCustomization`  
_L29-51_
- inherits: `IDetailCustomization`
- L33 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L36 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L43 _private prototype_ `bool IsToggleValue(bool bValue) const;`
- L44 _private prototype_ `void OnToggledTo(bool bSetTo);`
- L45 _private prototype_ `void OnNavigateHyperlink(FString Url);`
- L46 _private prototype_ `FText GetDescriptionText() const;`
- L49 _private member_ `TSharedPtr<IPropertyHandle> TogglePropertyHandle;`
- L50 _private member_ `TWeakObjectPtr<UObject> ToggleSettingObject;`

### `Source/Editor/DetailCustomizations/Private/InputSettingsDetails.h` (Private)


#### struct `InputSettingsDetails::FMappingSet`  
`struct FMappingSet`  
_L34-41_
- L36 _public member_ `FName SharedName;`
- L37 _public member_ `IDetailGroup* DetailGroup;`
- L38 _public member_ `TArray<TSharedRef<IPropertyHandle>> Mappings;`
- L39 _public prototype_ `FName GetActionMappingName() const;`
- L40 _public prototype_ `FName GetAxisMappingName() const;`

#### class `FActionMappingsNodeBuilder`  
`class FActionMappingsNodeBuilder : public IDetailCustomNodeBuilder, public TSharedFromThis<FActionMappingsNodeBuilder>`  
_L44-92_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FActionMappingsNodeBuilder>`
- L47 _public prototype_ `FActionMappingsNodeBuilder( IDetailLayoutBuilder* InDetailLayoutBuilder, const TSharedPtr<IPropertyHandle>& InPropertyHandle );`
- L50 _public function_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRebuildChildren ) override` — IDetailCustomNodeBuilder interface
- L51 _public function_ `virtual bool RequiresTick() const override`
- L52 _public prototype_ `virtual void Tick( float DeltaTime ) override;`
- L53 _public prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L54 _public prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L55 _public function_ `virtual bool InitiallyCollapsed() const override`
- L56 _public function_ `virtual FName GetName() const override`
- L59 _private prototype_ `void AddActionMappingButton_OnClick();`
- L60 _private prototype_ `void ClearActionMappingButton_OnClick();`
- L61 _private prototype_ `void OnActionMappingNameCommitted(const FText& InName, ETextCommit::Type CommitInfo, const InputSettingsDetails::FMappingSet MappingSet);`
- L62 _private prototype_ `void AddActionMappingToGroupButton_OnClick(const InputSettingsDetails::FMappingSet MappingSet);`
- L63 _private prototype_ `void RemoveActionMappingGroupButton_OnClick(const InputSettingsDetails::FMappingSet MappingSet);`
- L65 _private prototype_ `void OnDeprecationCheckboxChanged(ECheckBoxState NewState, const FName MappingName);`
- L66 _private prototype_ `ECheckBoxState GetActionMappingCheckBoxState(const FName MappingName) const;`
- L67 _private prototype_ `class UInputSettings* GetInputSettings() const;`
- L70 _private prototype_ `bool GroupsRequireRebuild() const;`
- L71 _private prototype_ `void RebuildGroupedMappings();`
- L72 _private function_ `void RebuildChildren()`
- L77 _private prototype_ `void HandleDelayedGroupExpansion();` — Makes sure that groups have their expansion set after any rebuilding
- L81 _private member_ `FSimpleDelegate OnRebuildChildren;` — Called to rebuild the children of the detail tree
- L84 _private member_ `IDetailLayoutBuilder* DetailLayoutBuilder;` — Associated detail layout builder
- L87 _private member_ `TSharedPtr<IPropertyHandle> ActionMappingsPropertyHandle;` — Property handle to associated action mappings
- L89 _private member_ `TArray<InputSettingsDetails::FMappingSet> GroupedMappings;`
- L91 _private member_ `TArray<TPair<FName, bool>> DelayedGroupExpansionStates;`

#### class `FAxisMappingsNodeBuilder`  
`class FAxisMappingsNodeBuilder : public IDetailCustomNodeBuilder, public TSharedFromThis<FAxisMappingsNodeBuilder>`  
_L94-141_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FAxisMappingsNodeBuilder>`
- L97 _public prototype_ `FAxisMappingsNodeBuilder( IDetailLayoutBuilder* InDetailLayoutBuilder, const TSharedPtr<IPropertyHandle>& InPropertyHandle );`
- L100 _public function_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRebuildChildren ) override` — IDetailCustomNodeBuilder interface
- L101 _public function_ `virtual bool RequiresTick() const override`
- L102 _public prototype_ `virtual void Tick( float DeltaTime ) override;`
- L103 _public prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L104 _public prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L105 _public function_ `virtual bool InitiallyCollapsed() const override`
- L106 _public function_ `virtual FName GetName() const override`
- L109 _private prototype_ `void AddAxisMappingButton_OnClick();`
- L110 _private prototype_ `void ClearAxisMappingButton_OnClick();`
- L111 _private prototype_ `void OnAxisMappingNameCommitted(const FText& InName, ETextCommit::Type CommitInfo, const InputSettingsDetails::FMappingSet MappingSet);`
- L112 _private prototype_ `void AddAxisMappingToGroupButton_OnClick(const InputSettingsDetails::FMappingSet MappingSet);`
- L113 _private prototype_ `void RemoveAxisMappingGroupButton_OnClick(const InputSettingsDetails::FMappingSet MappingSet);`
- L115 _private prototype_ `void OnDeprecationCheckboxChanged(ECheckBoxState NewState, const FName MappingName);`
- L116 _private prototype_ `ECheckBoxState GetAxisMappingCheckBoxState(const FName MappingName) const;`
- L117 _private prototype_ `class UInputSettings* GetInputSettings() const;`
- L119 _private prototype_ `bool GroupsRequireRebuild() const;`
- L120 _private prototype_ `void RebuildGroupedMappings();`
- L121 _private function_ `void RebuildChildren()`
- L126 _private prototype_ `void HandleDelayedGroupExpansion();` — Makes sure that groups have their expansion set after any rebuilding
- L130 _private member_ `FSimpleDelegate OnRebuildChildren;` — Called to rebuild the children of the detail tree
- L133 _private member_ `IDetailLayoutBuilder* DetailLayoutBuilder;` — Associated detail layout builder
- L136 _private member_ `TSharedPtr<IPropertyHandle> AxisMappingsPropertyHandle;` — Property handle to associated axis mappings
- L138 _private member_ `TArray<InputSettingsDetails::FMappingSet> GroupedMappings;`
- L140 _private member_ `TArray<TPair<FName, bool>> DelayedGroupExpansionStates;`

#### class `FInputSettingsDetails`  
`class FInputSettingsDetails : public IDetailCustomization`  
_L143-159_
- inherits: `IDetailCustomization`
- L147 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L150 _public prototype_ `virtual void CustomizeDetails( class IDetailLayoutBuilder& DetailBuilder ) override;` — ILayoutDetails interface
- L158 _private prototype_ `EVisibility GetLegacyWarningVisibility() const;` — If true, then we should display some warning text about the Axis/Action mappings being legacy in favor of Enhanced Input

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace InputSettingsDetails`
- L27 _namespace_ `namespace InputConstants` (scope `InputSettingsDetails`)
- L29 _variable_ `const FMargin PropertyPadding(2.0f, 0.0f, 2.0f, 0.0f);` (scope `InputSettingsDetails::InputConstants`)
- L30 _variable_ `const float TextBoxWidth = 250.0f;` (scope `InputSettingsDetails::InputConstants`)
- L31 _variable_ `const float ScaleBoxWidth = 50.0f;` (scope `InputSettingsDetails::InputConstants`)

### `Source/Editor/DetailCustomizations/Private/InputStructCustomization.h` (Private)


#### class `FInputAxisConfigCustomization`  
`class FInputAxisConfigCustomization : public IPropertyTypeCustomization`  
_L11-19_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes an InputAxisConfigEntry struct to display it more simply
- L14 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L18 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`

#### class `FInputActionMappingCustomization`  
`class FInputActionMappingCustomization : public IPropertyTypeCustomization`  
_L24-38_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes an InputActionKeyMapping struct to display it more simply
- L27 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L30 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L31 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L34 _private prototype_ `void RemoveActionMappingButton_OnClick();`
- L37 _private member_ `TSharedPtr<class IPropertyHandle> ActionMappingHandle;`

#### class `FInputAxisMappingCustomization`  
`class FInputAxisMappingCustomization : public IPropertyTypeCustomization`  
_L43-57_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes an InputAxisKeyMapping struct to display it more simply
- L46 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L49 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L50 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L53 _private prototype_ `void RemoveAxisMappingButton_OnClick();`
- L56 _private member_ `TSharedPtr<class IPropertyHandle> AxisMappingHandle;`

### `Source/Editor/DetailCustomizations/Private/InstancedStaticMeshComponentDetails.h` (Private)


#### class `FInstancedStaticMeshComponentDetails`  
`class FInstancedStaticMeshComponentDetails : public IDetailCustomization`  
_L16-40_
- inherits: `IDetailCustomization`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L24 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L27 _private prototype_ `FReply OnShowHideAllInstancesClicked();`
- L28 _private prototype_ `bool IsShowHideAllInstancesEnabled() const;`
- L29 _private prototype_ `FText GetShowHideAllInstancesText() const;`
- L33 _private member_ `bool bForceShowAllInstances = false;` — Indicate whether we're currently forcing the display of the instance list or not
- L35 _private member_ `TWeakObjectPtr<UInstancedStaticMeshComponent> ComponentBeingCustomized;` — Component being edited
- L37 _private member_ `int32 NumInstances = 0;` — Current number of instances to show in the display panel
- L39 _private member_ `TWeakPtr<IDetailLayoutBuilder> CachedDetailBuilder;` — The detail builder for this customization

### `Source/Editor/DetailCustomizations/Private/IntervalStructCustomization.h` (Private)


#### enum `EIntervalField`  
`enum class EIntervalField`  
_L14-18_
- L16 _public enumerator_ `Min`
- L17 _public enumerator_ `Max`

#### class `FIntervalStructCustomization`  
`template <typename NumericType> class FIntervalStructCustomization : public IPropertyTypeCustomization`  
_L24-151_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details panel customization for numeric TInterval structures.
- L28 _public function_ `FIntervalStructCustomization() : bIsUsingSlider(false)`
- L35 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L36 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L45 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates a new instance. @return A new struct customization for Guids.
- L55 _protected prototype_ `TOptional<NumericType> OnGetValue(EIntervalField Field) const;` — Gets the value for the provided interval field @param	Field	Which FInterval field to get @return	The value or unset if it could not be accessed
- L62 _protected prototype_ `TOptional<NumericType> OnGetMinValue() const;` — Gets the minimum allowed value @return	The value or unset if it could not be accessed
- L69 _protected prototype_ `TOptional<NumericType> OnGetMinSliderValue() const;` — Gets the minimum slider allowed value @return	The value or unset if it could not be accessed
- L76 _protected prototype_ `TOptional<NumericType> OnGetMaxValue() const;` — Gets the maximum allowed value @return	The value or unset if it could not be accessed
- L83 _protected prototype_ `TOptional<NumericType> OnGetMaxSliderValue() const;` — Gets the maximum slider allowed value @return	The value or unset if it could not be accessed
- L92 _protected prototype_ `void OnValueCommitted(NumericType NewValue, ETextCommit::Type CommitType, EIntervalField Field);` — Called when the value is committed from the property editor @param	NewValue		The new value of the property @param	CommitType		How the value was committed (unused) @param	Field			Which TInterval field is being committed to
- L100 _protected prototype_ `void OnValueChanged(NumericType NewValue, EIntervalField Field);` — Called when the value is changed in the property editor @param	NewValue		The new value of the property @param	Field			Which TInterval field is being committed to
- L105 _protected prototype_ `void OnBeginSliderMovement();` — Called when a value starts to be changed by a slider
- L112 _protected prototype_ `void OnEndSliderMovement(NumericType NewValue);` — Called when a value stops being changed by a slider @param	NewValue		The new value of the property
- L121 _protected prototype_ `void SetValue(NumericType NewValue, EIntervalField Field, EPropertyValueSetFlags::Type Flags = EPropertyValueSetFlags::DefaultFlags);` — Sets the interval field specified to a new value @param	NewValue		The new value of the property @param	Field			Which TInterval field is being set @param	Flags			Flags specifying how the property should be set
- L128 _protected prototype_ `bool ShouldAllowSpin() const;` — Determines if the spin box is enabled on a numeric value widget @return Whether the spin box should be enabled.
- L131 _protected prototype_ `bool IsPropertyEnabled(EIntervalField Field) const;` — If the property is disable we must disable the editing
- L134 _protected member_ `TSharedPtr<IPropertyHandle> MinValueHandle;` — Cached shared pointers to properties that we are managing
- L135 _protected member_ `TSharedPtr<IPropertyHandle> MaxValueHandle;`
- L138 _protected member_ `TOptional<NumericType> MinAllowedValue;` — Min and max allowed values from the metadata
- L139 _protected member_ `TOptional<NumericType> MaxAllowedValue;`
- L140 _protected member_ `TOptional<NumericType> MinAllowedSliderValue;`
- L141 _protected member_ `TOptional<NumericType> MaxAllowedSliderValue;`
- L144 _protected member_ `bool bIsUsingSlider;` — Flags whether the slider is being moved at the moment on any of our widgets
- L147 _protected member_ `bool bAllowInvertedInterval;` — Specifies that the Min value may be set greater than the Max value
- L150 _protected member_ `bool bClampToMinMaxLimits;` — Specifies that the Min value imposes a minimum limit on the Max value, and vice versa

### `Source/Editor/DetailCustomizations/Private/LevelSequenceActorDetails.h` (Private)


#### class `FLevelSequenceActorDetails`  
`class FLevelSequenceActorDetails : public IDetailCustomization`  
_L14-29_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _private prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L23 _private prototype_ `bool CanOpenLevelSequenceForActor() const;`
- L24 _private prototype_ `FReply OnOpenLevelSequenceForActor();`
- L28 _private member_ `TWeakObjectPtr<ALevelSequenceActor> LevelSequenceActor;` — The selected level sequence actor

### `Source/Editor/DetailCustomizations/Private/LevelSequenceBurnInOptionsCustomization.h` (Private)


#### class `FLevelSequenceBurnInOptionsCustomization`  
`class FLevelSequenceBurnInOptionsCustomization : public IPropertyTypeCustomization`  
_L11-18_
- inherits: `IPropertyTypeCustomization`
- L14 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L17 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `FLevelSequenceBurnInInitSettingsCustomization`  
`class FLevelSequenceBurnInInitSettingsCustomization : public IPropertyTypeCustomization`  
_L21-28_
- inherits: `IPropertyTypeCustomization`
- L24 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Source/Editor/DetailCustomizations/Private/LightComponentDetails.h` (Private)


#### class `FLightComponentDetails`  
`class FLightComponentDetails : public IDetailCustomization`  
_L14-55_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L22 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L24 _public prototype_ `static void SetComponentIntensity(ULightComponent* Component, float InIntensity);`
- L29 _private prototype_ `bool IsLightBrightnessEnabled() const;` — Helper functions which tell whether the various custom controls are enabled or not
- L30 _private prototype_ `bool IsUseIESBrightnessEnabled() const;`
- L31 _private prototype_ `bool IsIESBrightnessScaleEnabled() const;`
- L33 _private prototype_ `void ResetIntensityToDefault(TSharedPtr<IPropertyHandle> PropertyHandle, TWeakObjectPtr<ULightComponent> Component);`
- L34 _private prototype_ `bool IsIntensityResetToDefaultVisible(TSharedPtr<IPropertyHandle> PropertyHandle, TWeakObjectPtr<ULightComponent> Component) const;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> IESBrightnessTextureProperty;`
- L38 _private member_ `TSharedPtr<IPropertyHandle> IESBrightnessEnabledProperty;`
- L39 _private member_ `TSharedPtr<IPropertyHandle> IESBrightnessScaleProperty;`
- L40 _private member_ `TSharedPtr<IPropertyHandle> LightIntensityProperty;`
- L41 _private member_ `TSharedPtr<IPropertyHandle> IntensityUnitsProperty;`
- L43 _private member_ `TWeakPtr<IDetailLayoutBuilder> CachedDetailBuilder;`
- L44 _private prototype_ `void ResetIntensityUnitsToDefault(TSharedPtr<IPropertyHandle> PropertyHandle, ULocalLightComponent* Component);`
- L45 _private prototype_ `bool IsIntensityUnitsResetToDefaultVisible(TSharedPtr<IPropertyHandle> PropertyHandle, ULocalLightComponent* Component) const;`
- L48 _private prototype_ `void OnIntensityUnitsPreChange(ULocalLightComponent* Component);` — Called when the intensity units are changed
- L49 _private prototype_ `void OnIntensityUnitsChanged(ULocalLightComponent* Component);`
- L52 _private prototype_ `void AddLocalLightIntensityWithUnit(IDetailLayoutBuilder& DetailBuilder, ULocalLightComponent* Component);` — Add local light intensity with unit
- L54 _private member_ `float LastLightBrigtness = 0;`

### `Source/Editor/DetailCustomizations/Private/LightingChannelsCustomization.h` (Private)


#### class `FLightingChannelsCustomization`  
`class FLightingChannelsCustomization : public IPropertyTypeCustomization`  
_L13-35_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes Lighting Channels as a horizontal row of buttons.
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _public function_ `FLightingChannelsCustomization()`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L26 _private prototype_ `FText GetStructPropertyNameText() const;`
- L27 _private prototype_ `FText GetStructPropertyTooltipText() const;`
- L29 _private prototype_ `bool IsLightingChannelButtonEditable(uint32 ChildIndex) const;`
- L30 _private prototype_ `void OnButtonCheckedStateChanged(ECheckBoxState NewState, uint32 ChildIndex) const;`
- L31 _private prototype_ `ECheckBoxState GetButtonCheckedState(uint32 ChildIndex) const;`
- L33 _private member_ `TSharedPtr<IPropertyHandle> LightingChannelsHandle;`
- L34 _private member_ `FCheckBoxStyle Style;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DETAILCUSTOMIZATIONS_API`

### `Source/Editor/DetailCustomizations/Private/LinuxTargetSettingsDetails.h` (Private)


#### class `FLinuxTargetSettingsDetails`  
`class FLinuxTargetSettingsDetails : public IDetailCustomization`  
_L24-72_
- inherits: `IDetailCustomization`
- desc: Manages the Transform section of a details view
- L28 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L31 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L35 _private prototype_ `bool HandlePreExternalIconCopy(const FString& InChosenImage);` — Delegate handler for before an icon is copied
- L38 _private prototype_ `FString GetPickerPath();` — Delegate handler to get the path to start picking from
- L41 _private prototype_ `bool HandlePostExternalIconCopy(const FString& InChosenImage);` — Delegate handler to set the path to start picking from
- L44 _private prototype_ `void HandleAudioDeviceSelected(FString AudioDeviceName, TSharedPtr<IPropertyHandle> PropertyHandle);` — Handles when a new audio device is selected from list of available audio devices.
- L47 _private prototype_ `FSlateColor HandleAudioDeviceBoxForegroundColor(TSharedPtr<IPropertyHandle> PropertyHandle) const;` — Handles changing the foreground color of the audio device box.
- L50 _private prototype_ `FText HandleAudioDeviceTextBoxText(TSharedPtr<IPropertyHandle> PropertyHandle) const;` — Handles getting text of the audio device list text block.
- L53 _private prototype_ `void HandleAudioDeviceTextBoxTextChanged(const FText& InText, TSharedPtr<IPropertyHandle> PropertyHandle);` — Handles text changes in the audio device list text block.
- L56 _private prototype_ `void HandleAudioDeviceTextBoxTextComitted(const FText& InText, ETextCommit::Type CommitType, TSharedPtr<IPropertyHandle> PropertyHandle);` — Handles committing changes in the audio list text block.
- L61 _protected prototype_ `bool IsValidAudioDeviceName(const FString& InDeviceName) const;` — Checks if the device name is valid.
- L64 _protected prototype_ `TSharedRef<SWidget> MakeAudioDeviceMenu(const TSharedPtr<IPropertyHandle>& PropertyHandle);` — Creates a widget for the audio device picker.
- L68 _private member_ `TSharedPtr<FShaderFormatsPropertyDetails> TargetShaderFormatsDetails;` — Reference to the target shader formats property view
- L71 _private member_ `FAudioPluginWidgetManager AudioPluginWidgetManager;` — Manager for Audio Plugin widget.

### `Source/Editor/DetailCustomizations/Private/LocalLightComponentDetails.h` (Private)


#### class `FLocalLightComponentDetails`  
`class FLocalLightComponentDetails : public IDetailCustomization`  
_L12-20_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

### `Source/Editor/DetailCustomizations/Private/MarginCustomization.h` (Private)


#### class `FMarginStructCustomization`  
`class FMarginStructCustomization : public IPropertyTypeCustomization`  
_L19-114_
- inherits: `IPropertyTypeCustomization`
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L24 _public function_ `FMarginStructCustomization() : bIsUsingSlider( false )`
- L29 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L31 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L38 _private prototype_ `TSharedRef<SEditableTextBox> MakePropertyWidget();` — Make the margin property widget
- L45 _private prototype_ `TSharedRef<SWidget> MakeChildPropertyWidget( int32 PropertyIndex) const;` — Make the widget for the specified property @param PropertyIndex	The index of the child property to the make the widget for
- L50 _private prototype_ `FText GetMarginText() const;` — Get the margin property value as text
- L55 _private prototype_ `void OnMarginTextCommitted( const FText& InText, ETextCommit::Type InCommitType );` — Delegate to commit margin text
- L60 _private prototype_ `FString GetMarginTextFromProperties() const;` — Update the margin text from the margin property values
- L68 _private prototype_ `virtual TOptional<float> OnGetValue( int32 PropertyIndex ) const;` — Gets the value as a float for the provided property handle @param PropertyIndex	The index of the child property to get the value from @return The value or unset if it could not be accessed
- L77 _private prototype_ `virtual void OnValueCommitted( float NewValue, ETextCommit::Type CommitType, int32 PropertyIndex );` — Called when the value is committed from the property editor @param NewValue		The new value of the property as a float @param CommitType	How the value was committed (unused) @param PropertyIndex	The index of the child property that the new value is for
- L85 _private prototype_ `virtual void OnValueChanged( float NewValue, int32 PropertyIndex );` — Called when the value is changed in the property editor @param NewValue		The new value of the property as a float @param PropertyIndex	The index of the child property that the new value is for
- L90 _private prototype_ `void OnBeginSliderMovement();` — Called when a value starts to be changed by a slider
- L95 _private prototype_ `void OnEndSliderMovement( float NewValue );` — Called when a value stops being changed by a slider
- L98 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle to the margin being customized
- L101 _private member_ `TArray< TSharedRef<IPropertyHandle> > ChildPropertyHandles;` — Child property handles
- L104 _private member_ `bool bIsMarginUsingUVSpace;` — True if this margin value working in uv space
- L107 _private member_ `bool bIsUsingSlider;` — True if a value is being changed by dragging a slider
- L110 _private member_ `TSharedPtr<SEditableTextBox> MarginEditableTextBox;` — Margin text editable text box
- L113 _private member_ `TSharedPtr< INumericTypeInterface<float> > NumericInterface;` — Used to evaluate margin strings as mathematical expressions

### `Source/Editor/DetailCustomizations/Private/MaterialAttributePropertyDetails.h` (Private)


#### class `FMaterialAttributePropertyDetails`  
`class FMaterialAttributePropertyDetails : public IDetailCustomization`  
_L20-30_
- inherits: `IDetailCustomization`
- desc: Customization for material attribute get/set nodes to handle GUID-Name conversions.
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`
- L25 _public prototype_ `void OnBuildChild(TSharedRef<IPropertyHandle> ChildHandle, int32 ElementIndex, IDetailChildrenBuilder& ChildrenBuilder);`
- L28 _private member_ `TArray<TPair<FString, FGuid>> AttributeNameToIDList;`
- L29 _private member_ `TArray<TSharedPtr<FString>> AttributeDisplayNameList;`

### `Source/Editor/DetailCustomizations/Private/MaterialExpressionTextureBaseDetails.h` (Private)


#### class `FMaterialExpressionTextureBaseDetails`  
`class FMaterialExpressionTextureBaseDetails : public IDetailCustomization`  
_L17-34_
- inherits: `IDetailCustomization`
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual ~FMaterialExpressionTextureBaseDetails();`
- L26 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L28 _public member_ `TSharedPtr<FPropertyRestriction> EnumRestriction;`
- L29 _public member_ `TWeakObjectPtr<UMaterialExpressionTextureBase> Expression;`
- L30 _public member_ `FDelegateHandle DelegateHandle;`
- L32 _public prototype_ `void OnTextureChanged();`
- L33 _public prototype_ `void OnPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);`

### `Source/Editor/DetailCustomizations/Private/MaterialInstanceDynamicDetails.h` (Private)


#### class `FMaterialInstanceDynamicDetails`  
`class FMaterialInstanceDynamicDetails : public IDetailCustomization`  
_L10-15_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;`

### `Source/Editor/DetailCustomizations/Private/MaterialParameterCollectionDetails.h` (Private)


#### class `FMaterialParameterCollectionDetails`  
`class FMaterialParameterCollectionDetails : public IDetailCustomization`  
_L24-66_
- inherits: `IDetailCustomization`
- L28 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L33 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L36 _private prototype_ `FMaterialParameterCollectionDetails() = default;`
- L38 _private prototype_ `FMaterialParameterCollectionDetails(const FMaterialParameterCollectionDetails&) = delete;`
- L39 _private prototype_ `FMaterialParameterCollectionDetails& operator =(const FMaterialParameterCollectionDetails&) = delete;`
- L44 _private prototype_ `static FBaseOverridesSelector GetBaseOverridesMap(UMaterialParameterCollection* OverrideCollection);`
- L45 _private prototype_ `static FBaseOverridesSelectorConst GetBaseOverridesMap(const UMaterialParameterCollection* OverrideCollection);`
- L47 _private prototype_ `static FProperty* GetBaseOverridesMapProperty(const FCollectionScalarParameter&);`
- L48 _private prototype_ `static FProperty* GetBaseOverridesMapProperty(const FCollectionVectorParameter&);`
- L51 _private prototype_ `template<class FCollectionParameterType> static auto GetParameterValue(const UMaterialParameterCollection* Collection, const FCollectionParameterType& CollectionParameter, const UMaterialParameterCollection* BaseCollection = nullptr);`
- L54 _private prototype_ `template<class FCollectionParameterType> void AddParameter(IDetailGroup& DetailGroup, TSharedPtr<IPropertyHandle> PropertyHandle, UMaterialParameterCollection* Collection, const FCollectionParameterType& CollectionParameter, const UMaterialParameterCollection* BaseCollection);`
- L57 _private prototype_ `template<class FCollectionParameterType> void AddParameters(IDetailCategoryBuilder& DetailCategory, FName PropertyName, UMaterialParameterCollection* Collection, const TArray<FCollectionParameterType>& CollectionParameters, UMaterialParameterCollection* BaseCollection);`
- L59 _private prototype_ `void CustomizeCollectionDetails(UMaterialParameterCollection* Collection);`
- L61 _private prototype_ `void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);`
- L63 _private prototype_ `void UnbindDelegates();`
- L65 _private member_ `IDetailLayoutBuilder* DetailLayout = nullptr;`

### `Source/Editor/DetailCustomizations/Private/MaterialProxySettingsCustomizations.h` (Private)


#### class `FMaterialProxySettingsCustomizations`  
`class FMaterialProxySettingsCustomizations : public IPropertyTypeCustomization`  
_L13-42_
- inherits: `IPropertyTypeCustomization`
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization instance
- L20 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L22 _protected prototype_ `void AddTextureSizeClamping(TSharedPtr<IPropertyHandle> TextureSizeProperty);`
- L23 _protected prototype_ `bool UseNativeProxyLODTool() const;`
- L26 _protected prototype_ `EVisibility AreManualOverrideTextureSizesEnabled() const;`
- L27 _protected prototype_ `EVisibility IsTextureSizeEnabled() const;`
- L29 _protected prototype_ `EVisibility IsSimplygonMaterialMergingVisible() const;`
- L31 _protected prototype_ `EVisibility IsMeshMinDrawDistanceVisible() const;`
- L33 _protected member_ `TSharedPtr< IPropertyHandle > TextureSizingTypeHandle;`
- L35 _protected member_ `TSharedPtr< IPropertyHandle > TextureSizeHandle;`
- L36 _protected member_ `TArray<TSharedPtr<IPropertyHandle>> PropertyTextureSizeHandles;`
- L38 _protected member_ `TSharedPtr< IPropertyHandle > MergeTypeHandle;`
- L39 _protected member_ `TSharedPtr< IPropertyHandle > GutterSpaceHandle;`
- L41 _protected member_ `TSharedPtr< IPropertyHandle > MeshMinDrawDistanceHandle;`

### `Source/Editor/DetailCustomizations/Private/MaterialShadingModelCustomization.h` (Private)


#### class `FMaterialShadingModelCustomization`  
`class FMaterialShadingModelCustomization : public IPropertyTypeCustomization`  
_L10-19_
- inherits: `IPropertyTypeCustomization`
- L13 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L17 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`

### `Source/Editor/DetailCustomizations/Private/MeshComponentDetails.h` (Private)


#### class `FMeshComponentDetails`  
`class FMeshComponentDetails : public IDetailCustomization`  
_L11-24_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L18 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L22 _private member_ `IDetailCategoryBuilder* RenderingCategory;`

### `Source/Editor/DetailCustomizations/Private/MeshDeformerCustomizations.h` (Private)


#### class `FMeshDeformerCustomization`  
`class FMeshDeformerCustomization : public IPropertyTypeCustomization`  
_L7-22_
- inherits: `IPropertyTypeCustomization`
- L10 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L13 _public prototype_ `void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization overrides
- L18 _public function_ `void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`

### `Source/Editor/DetailCustomizations/Private/MeshMergingSettingsCustomization.h` (Private)


#### class `FMeshMergingSettingsObjectCustomization`  
`class FMeshMergingSettingsObjectCustomization : public IDetailCustomization`  
_L17-33_
- inherits: `IDetailCustomization`
- L20 _public prototype_ `~FMeshMergingSettingsObjectCustomization();`
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& LayoutBuilder) override;` — Begin IDetailCustomization interface
- L27 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L29 _protected prototype_ `EVisibility ArePropertiesVisible(const int32 VisibleType) const;`
- L30 _protected prototype_ `bool AreMaterialPropertiesEnabled() const;`
- L31 _protected member_ `TSharedPtr<IPropertyHandle> EnumProperty;`

#### class `FMeshMergingSettingsCustomization`  
`class FMeshMergingSettingsCustomization : public IPropertyTypeCustomization, public TOverrideResetToDefaultWithStaticUStruct<FMeshMergingSettings>`  
_L36-44_
- inherits: `IPropertyTypeCustomization,TOverrideResetToDefaultWithStaticUStruct<FMeshMergingSettings>`
- L39 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L42 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization instance
- L43 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Source/Editor/DetailCustomizations/Private/MeshProxySettingsCustomizations.h` (Private)


#### class `FMeshProxySettingsCustomizations`  
`class FMeshProxySettingsCustomizations : public IPropertyTypeCustomization, public TOverrideResetToDefaultWithStaticUStruct<FMeshProxySettings>`  
_L14-41_
- inherits: `IPropertyTypeCustomization,TOverrideResetToDefaultWithStaticUStruct<FMeshProxySettings>`
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization instance
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L25 _protected prototype_ `EVisibility IsHardAngleThresholdVisible() const;`
- L26 _protected prototype_ `EVisibility IsRecalculateNormalsVisible() const;`
- L27 _protected prototype_ `EVisibility IsUseLandscapeCullingVisible() const;`
- L28 _protected prototype_ `EVisibility IsUseLandscapeCullingPrecisionVisible() const;`
- L29 _protected prototype_ `EVisibility IsMergeDistanceVisible() const;`
- L30 _protected prototype_ `EVisibility IsUnresolvedGeometryColorVisible() const;`
- L31 _protected prototype_ `EVisibility IsVoxelSizeVisible() const;`
- L32 _protected prototype_ `EVisibility IsScreenSizeVisible() const;`
- L33 _protected prototype_ `EVisibility IsNormalCalcMethodVisible() const;`
- L34 _protected prototype_ `EVisibility IsSearchDistanceVisible() const;`
- L36 _protected prototype_ `EVisibility IsThirdPartySpecificVisible() const;`
- L37 _protected prototype_ `EVisibility IsProxyLODSpecificVisible() const;`
- L38 _protected prototype_ `bool UseNativeProxyLODTool() const;`
- L40 _protected member_ `bool bIsEditingHLODLayer;`

### `Source/Editor/DetailCustomizations/Private/MotionControllerDetails.h` (Private)


#### class `FMotionControllerDetails`  
`class FMotionControllerDetails : public IDetailCustomization`  
_L12-30_
- inherits: `IDetailCustomization`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L23 _private member_ `TSharedPtr<IPropertyHandle> MotionSourceProperty;`
- L26 _private prototype_ `void OnMotionSourceChanged(FName NewMotionSource);` — Delegate handler for when UI changes motion source
- L29 _private prototype_ `FText GetMotionSourceValueText() const;` — Return text for motion source combo box

### `Source/Editor/DetailCustomizations/Private/MotionControllerPinFactory.h` (Private)


#### class `FMotionControllerPinFactory`  
`class FMotionControllerPinFactory : public FGraphPanelPinFactory`  
_L8-11_
- inherits: `FGraphPanelPinFactory`
- L10 _private prototype_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override;`

### `Source/Editor/DetailCustomizations/Private/MotionControllerSourceCustomization.h` (Private)


#### class `SMotionSourceWidget`  
`class SMotionSourceWidget : public SCompoundWidget`  
_L18-46_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SMotionSourceWidget)`
- L29 _public prototype_ `void Construct(const FArguments& InArgs);`
- L34 _private prototype_ `TSharedRef<SWidget> BuildMotionSourceMenu();` — Generate the motion source combo box popup menu
- L37 _private prototype_ `FText GetMotionSourceText() const;` — Handler for setting combo box text
- L40 _private prototype_ `void OnMotionSourceValueTextComitted(const FText& InNewText, ETextCommit::Type InTextCommit);` — Handler new values from the motion source combo box
- L41 _private prototype_ `void OnMotionSourceComboValueCommited(FName InMotionSource);`
- L44 _private member_ `FOnGetMotionSourceText OnGetMotionSourceText;` — Delegates for interaction with source
- L45 _private member_ `FOnMotionSourceChanged OnMotionSourceChanged;`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_RetVal(FText, FOnGetMotionSourceText) DECLARE_DELEGATE_OneParam(FOnMotionSourceChanged, FName) class SMotionSourceWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMotionSourceWidget) {} SLATE_EVENT(FOnGetMotionSourceText, OnGetMotionSourceText) SLATE_EVENT(FOnMotionSourceChanged, OnMotionSourceChanged) SLATE_END_ARGS() public: void Construct(const FArguments& InArgs); private:`
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMotionSourceChanged, FName) class SMotionSourceWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMotionSourceWidget) {} SLATE_EVENT(FOnGetMotionSourceText, OnGetMotionSourceText) SLATE_EVENT(FOnMotionSourceChanged, OnMotionSourceChanged) SLATE_END_ARGS() public: void Construct(const FArguments& InArgs); private:`

### `Source/Editor/DetailCustomizations/Private/MoviePlayerSettingsDetails.h` (Private)


#### class `FMoviePlayerSettingsDetails`  
`class FMoviePlayerSettingsDetails : public IDetailCustomization`  
_L14-39_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `~FMoviePlayerSettingsDetails();`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L28 _private prototype_ `void GenerateArrayElementWidget(TSharedRef<IPropertyHandle> PropertyHandle, int32 ArrayIndex, IDetailChildrenBuilder& ChildrenBuilder);` — Generate a widget for a movie array element
- L31 _private prototype_ `FString HandleFilePathPickerFilePath( TSharedRef<IPropertyHandle> Property ) const;` — Callback for getting the selected path in the picker widget.
- L34 _private prototype_ `void HandleFilePathPickerPathPicked( const FString& InOutPath, TSharedRef<IPropertyHandle> Property );` — Delegate handler for when a new movie path is picked
- L38 _private member_ `TSharedPtr<IPropertyHandle> StartupMoviesPropertyHandle;` — Handle to the movies array property

### `Source/Editor/DetailCustomizations/Private/MovieSceneBindingOverrideDataCustomization.h` (Private)


#### class `FMovieSceneBindingOverrideDataCustomization`  
`class FMovieSceneBindingOverrideDataCustomization : public IPropertyTypeCustomization`  
_L15-33_
- inherits: `IPropertyTypeCustomization`
- L18 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L25 _private prototype_ `void OnGetObjectFromProxy();`
- L27 _private prototype_ `IMovieSceneBindingOwnerInterface* GetInterface() const;`
- L28 _private prototype_ `UMovieSceneSequence* GetSequence() const;`
- L30 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L31 _private member_ `TSharedPtr<IPropertyHandle> ObjectProperty;`
- L32 _private member_ `TSharedPtr<FStructOnScope> ObjectPickerProxy;`

### `Source/Editor/DetailCustomizations/Private/MovieSceneCaptureCustomization.h` (Private)


#### class `FMovieSceneCaptureCustomization`  
`class FMovieSceneCaptureCustomization : public IDetailCustomization`  
_L17-36_
- inherits: `IDetailCustomization`
- L20 _public prototype_ `FMovieSceneCaptureCustomization();`
- L21 _public prototype_ `~FMovieSceneCaptureCustomization();`
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L28 _private prototype_ `void OnObjectPostEditChange( UObject* Object, FPropertyChangedEvent& PropertyChangedEvent );`
- L29 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& OldToNewInstanceMap);`
- L31 _private member_ `TArray<TWeakObjectPtr<>> ObjectsBeingCustomized;`
- L32 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`
- L34 _private member_ `FDelegateHandle PropertyChangedHandle;`
- L35 _private member_ `FDelegateHandle ObjectsReplacedHandle;`

### `Source/Editor/DetailCustomizations/Private/MovieSceneEvalOptionsCustomization.h` (Private)


#### class `FMovieSceneSectionEvalOptionsCustomization`  
`class FMovieSceneSectionEvalOptionsCustomization : public IPropertyTypeCustomization`  
_L12-19_
- inherits: `IPropertyTypeCustomization`
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L17 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;`
- L18 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;`

### `Source/Editor/DetailCustomizations/Private/MovieSceneEventParametersCustomization.h` (Private)


#### class `FMovieSceneEventParametersCustomization`  
`class FMovieSceneEventParametersCustomization : public IPropertyTypeCustomization`  
_L16-33_
- inherits: `IPropertyTypeCustomization`
- L19 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L21 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;`
- L22 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;`
- L25 _private prototype_ `void OnStructChanged(const FAssetData& AssetData);`
- L26 _private prototype_ `void OnEditStructChildContentsChanged();`
- L28 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`
- L29 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L31 _private member_ `TSharedPtr<IStructureDetailsView> EventPayloadDetails;`
- L32 _private member_ `TSharedPtr<FStructOnScope> EditStructData;`

### `Source/Editor/DetailCustomizations/Private/MovieSceneSequenceLoopCountCustomization.h` (Private)


#### class `FMovieSceneSequenceLoopCountCustomization`  
`class FMovieSceneSequenceLoopCountCustomization : public IPropertyTypeCustomization`  
_L23-72_
- inherits: `IPropertyTypeCustomization`
- desc: Details view customization for the FMovieSceneSequencePlaybackSettings struct.
- L29 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L35 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;`
- L36 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;`
- L41 _protected prototype_ `void UpdateProperty();` — Respond to a selection change event from the combo box.
- L46 _private prototype_ `FText GetCustomSuffix() const;` — Get the suffix to display after the custom entry box.
- L49 _private prototype_ `EVisibility GetLoopResetVisibility() const;` — Get whether the loop reset button should be visible.
- L52 _private prototype_ `FReply OnLoopResetClicked();` — Called when the "Reset to Default" button for the loop mode has been clicked.
- L61 _private member_ `TArray<TSharedPtr<FLoopMode>> LoopModes;`
- L64 _private member_ `TSharedPtr<FLoopMode> CurrentMode;` — The loop mode we're currently displaying.
- L66 _private member_ `TSharedPtr<STextBlock> CurrentText;` — The text of the current selection.
- L68 _private member_ `TSharedPtr<SWidget> LoopEntry;` — The loop number entry to be hidden and shown based on combo box selection.
- L71 _private member_ `TSharedPtr<IPropertyHandle> LoopCountProperty;` — Property handles of the properties we're editing

#### struct `FMovieSceneSequenceLoopCountCustomization::FLoopMode`  
`struct FLoopMode`  
_L55-59_
- desc: Array of loop modes.
- L57 _public member_ `FText DisplayName;`
- L58 _public member_ `int32 Value;`

### `Source/Editor/DetailCustomizations/Private/NavAgentSelectorCustomization.h` (Private)


#### class `FNavAgentSelectorCustomization`  
`class FNavAgentSelectorCustomization : public IPropertyTypeCustomization`  
_L13-38_
- inherits: `IPropertyTypeCustomization`
- L19 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L20 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L27 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates a new instance. @return A new struct customization for Keys.
- L30 _protected prototype_ `void OnAgentStateChanged();`
- L31 _protected prototype_ `FText GetSupportedDesc() const;`
- L32 _protected prototype_ `void OnHeaderCheckStateChanged(ECheckBoxState InNewState);`
- L33 _protected prototype_ `ECheckBoxState IsHeaderChecked() const;`
- L34 _protected prototype_ `bool ComputeSupportedAgentCount(const UNavigationSystemV1* NavSysCDO, int32& OutNumAgents, int32& OutNumSupported, int32& OutFirstSupportedIdx) const;`
- L36 _protected member_ `TSharedPtr<IPropertyHandle> StructHandle;`
- L37 _protected member_ `FText SupportedDesc;`

### `Source/Editor/DetailCustomizations/Private/NavLinkStructCustomization.h` (Private)


#### class `FNavLinkStructCustomization`  
`class FNavLinkStructCustomization : public IPropertyTypeCustomization`  
_L10-27_
- inherits: `IPropertyTypeCustomization`
- L16 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L17 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L26 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates a new instance. @return A new struct customization for Keys.

### `Source/Editor/DetailCustomizations/Private/ObjectDetails.h` (Private)


#### class `FObjectDetails`  
`class FObjectDetails : public IDetailCustomization`  
_L16-38_
- inherits: `IDetailCustomization`
- L20 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates an instance of FObjectDetails
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L28 _private prototype_ `void AddExperimentalWarningCategory(IDetailLayoutBuilder& DetailBuilder);` — Adds a warning banner if the class is marked as Experimental or EarlyAccessPreview
- L31 _private prototype_ `void AddCallInEditorMethods(IDetailLayoutBuilder& DetailBuilder);` — Creates a button strip in each category that contains reflected functions marked as CallInEditor
- L33 _private prototype_ `TArray<TWeakObjectPtr<UObject>> GetFunctionCallExecutionContext(TWeakObjectPtr<UFunction> InWeakFunction) const;`
- L37 _private member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjectsList;` — The list of selected objects, used when invoking a CallInEditor method

### `Source/Editor/DetailCustomizations/Private/OverrideResetToDefault.h` (Private)


#### class `TOverrideResetToDefaultWithStaticUStruct`  
`template<typename UStructType> class TOverrideResetToDefaultWithStaticUStruct`  
_L21-42_
- desc: Class template aiming to override ResetToDefault methods by comparing properties with an internal static DefaultObject. This behavior was originally written for settings UI and does not properly support inheritance (resetting a parent class's struct member to default and have it propagate to loaded children). If a struct wants to override ResetToDefault behavior using this class and must support the outer-object being a parent class, OnResetToDefault should be revisited to properly reset archetype instances as well.
- L25 _public prototype_ `static bool IsResetToDefaultVisible(TSharedPtr<IPropertyHandle> InPropertyHandle);` — Called by the UI to show/hide the reset widgets
- L28 _public prototype_ `static void OnResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);` — Reset to default triggered in UI
- L32 _protected prototype_ `static void AddResetToDefaultOverrides(IDetailPropertyRow& InDetailPropertyRow);` — Adds callbacks used by the UI to determine if a property can be reset and reset it.
- L39 _private prototype_ `static const void* ResolveDefaultValuePtr(TSharedPtr<IPropertyHandle> InPropertyHandle);` — Resolves the correct default value pointer for a property that may be nested within UStructType. Walks the property handle parent chain to figure out the correct offset from DefaultObject.
- L41 _private member_ `static const UStructType DefaultObject;`
- L48 _function_ `template<typename UStructType> const void* TOverrideResetToDefaultWithStaticUStruct<UStructType>::ResolveDefaultValuePtr(TSharedPtr<IPropertyHandle> InPropertyHandle)`
- L79 _function_ `template<typename UStructType> bool TOverrideResetToDefaultWithStaticUStruct<UStructType>::IsResetToDefaultVisible(TSharedPtr<IPropertyHandle> InPropertyHandle)`
- L99 _function_ `template<typename UStructType> void TOverrideResetToDefaultWithStaticUStruct<UStructType>::OnResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle)`
- L117 _function_ `template<typename UStructType> void TOverrideResetToDefaultWithStaticUStruct<UStructType>::AddResetToDefaultOverrides(IDetailPropertyRow& InDetailPropertyRow)`

#### Free symbols / members of external scopes

- L45 _member_ `template<typename UStructType> const UStructType TOverrideResetToDefaultWithStaticUStruct<UStructType>::DefaultObject;` (scope `TOverrideResetToDefaultWithStaticUStruct<UStructType>`)

### `Source/Editor/DetailCustomizations/Private/ParticleModuleDetails.h` (Private)


#### class `FParticleModuleDetailsBase`  
`class FParticleModuleDetailsBase : public IDetailCustomization`  
_L16-22_
- inherits: `IDetailCustomization`
- L19 _protected prototype_ `void RestrictPropertiesOnGPUEmitter( IDetailLayoutBuilder& DetailBuilder, TArray<FString>& PropertyNames, TRestrictionList& Restrictions );`
- L21 _protected prototype_ `TSharedRef<const FPropertyRestriction> GetDistributionsForGPURestriction();`

#### class `FParticleModuleRequiredDetails`  
`class FParticleModuleRequiredDetails: public FParticleModuleDetailsBase`  
_L24-32_
- inherits: `FParticleModuleDetailsBase`
- L28 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L31 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

#### class `FParticleModuleSubUVDetails`  
`class FParticleModuleSubUVDetails : public FParticleModuleDetailsBase`  
_L34-42_
- inherits: `FParticleModuleDetailsBase`
- L38 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L41 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

#### class `FParticleModuleAccelerationDetails`  
`class FParticleModuleAccelerationDetails : public FParticleModuleDetailsBase`  
_L44-52_
- inherits: `FParticleModuleDetailsBase`
- L48 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L51 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

#### class `FParticleModuleAccelerationDragDetails`  
`class FParticleModuleAccelerationDragDetails : public FParticleModuleDetailsBase`  
_L54-62_
- inherits: `FParticleModuleDetailsBase`
- L58 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L61 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

#### class `FParticleModuleAccelerationDragScaleOverLifeDetails`  
`class FParticleModuleAccelerationDragScaleOverLifeDetails : public FParticleModuleDetailsBase`  
_L64-72_
- inherits: `FParticleModuleDetailsBase`
- L68 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L71 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

#### class `FParticleModuleCollisionGPUDetails`  
`class FParticleModuleCollisionGPUDetails : public FParticleModuleDetailsBase`  
_L74-82_
- inherits: `FParticleModuleDetailsBase`
- L78 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L81 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

#### class `FParticleModuleOrbitDetails`  
`class FParticleModuleOrbitDetails : public FParticleModuleDetailsBase`  
_L84-92_
- inherits: `FParticleModuleDetailsBase`
- L88 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L91 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

#### class `FParticleModuleSizeMultiplyLifeDetails`  
`class FParticleModuleSizeMultiplyLifeDetails : public FParticleModuleDetailsBase`  
_L94-102_
- inherits: `FParticleModuleDetailsBase`
- L98 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L101 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

#### class `FParticleModuleSizeScaleDetails`  
`class FParticleModuleSizeScaleDetails : public FParticleModuleDetailsBase`  
_L104-112_
- inherits: `FParticleModuleDetailsBase`
- L108 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L111 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

#### class `FParticleModuleVectorFieldScaleDetails`  
`class FParticleModuleVectorFieldScaleDetails : public FParticleModuleDetailsBase`  
_L114-122_
- inherits: `FParticleModuleDetailsBase`
- L118 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L121 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

#### class `FParticleModuleVectorFieldScaleOverLifeDetails`  
`class FParticleModuleVectorFieldScaleOverLifeDetails : public FParticleModuleDetailsBase`  
_L124-132_
- inherits: `FParticleModuleDetailsBase`
- L128 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L131 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef TArray<TSharedRef<const class FPropertyRestriction>> TRestrictionList;`

### `Source/Editor/DetailCustomizations/Private/ParticleSysParamStructCustomization.h` (Private)


#### class `FParticleSysParamStructCustomization`  
`class FParticleSysParamStructCustomization : public IPropertyTypeCustomization`  
_L23-67_
- inherits: `IPropertyTypeCustomization`
- desc: Class for FParticleSysParam struct customization
- L26 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L28 _public prototype_ `FParticleSysParamStructCustomization();`
- L31 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization instance
- L32 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L37 _protected prototype_ `TSharedRef<SWidget> OnGenerateComboWidget(TSharedPtr<FString> InComboString);` — Called by the combo box to generate each row of the widget
- L40 _protected prototype_ `void OnComboSelectionChanged(TSharedPtr<FString> InSelectedItem, ESelectInfo::Type SelectInfo);` — Called when the combo box selection changes, when a new parameter type is selected
- L43 _protected prototype_ `FText GetParameterTypeName() const;` — Called to obtain an FText representing the current combo box selection
- L48 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Cached handle to the struct property
- L51 _private member_ `int32 ParameterType;` — Current parameter type
- L54 _private member_ `TArray<TSharedPtr<FString>> ParameterTypeNames;` — A list of parameter type names
- L57 _private member_ `TArray<FText> ParameterTypeToolTips;` — A list of parameter type tooltips
- L60 _private prototype_ `EVisibility GetScalarVisibility() const;` — Delegates called by each property widget to determine their visibility
- L61 _private prototype_ `EVisibility GetScalarLowVisibility() const;`
- L62 _private prototype_ `EVisibility GetVectorVisibility() const;`
- L63 _private prototype_ `EVisibility GetVectorLowVisibility() const;`
- L64 _private prototype_ `EVisibility GetColorVisibility() const;`
- L65 _private prototype_ `EVisibility GetActorVisibility() const;`
- L66 _private prototype_ `EVisibility GetMaterialVisibility() const;`

### `Source/Editor/DetailCustomizations/Private/ParticleSystemComponentDetails.h` (Private)


#### class `FParticleSystemComponentDetails`  
`class FParticleSystemComponentDetails : public IDetailCustomization`  
_L11-30_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L18 _private prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& InDetailLayout ) override;` — IDetailCustomization interface
- L21 _private prototype_ `FReply OnAutoPopulateClicked();` — Handles the Auto-Populate button's on click event
- L24 _private prototype_ `FReply OnResetEmitter();` — Handles the Emitter Reset button's on click event
- L29 _private member_ `IDetailLayoutBuilder* DetailLayout;` — Cached off reference to the layout builder

### `Source/Editor/DetailCustomizations/Private/PerQualityLevelPropertyCustomization.h` (Private)


#### class `FPerQualityLevelPropertyCustomization`  
`template<typename OverrideType> class FPerQualityLevelPropertyCustomization : public IPropertyTypeCustomization`  
_L19-46_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details panel customization for the FPerQualityLevel structures.
- L22 _public function_ `FPerQualityLevelPropertyCustomization()`
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L27 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L34 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates a new instance. @return A new customization for FPerQualityLevel structs.
- L37 _protected prototype_ `TSharedRef<SWidget> GetWidget(FName InQualityLevelName, TSharedRef<IPropertyHandle> StructPropertyHandle) const;`
- L38 _protected prototype_ `TArray<FName> GetOverrideNames(TSharedRef<IPropertyHandle> StructPropertyHandle) const;`
- L39 _protected prototype_ `bool AddOverride(FName InQualityLevelName, TSharedRef<IPropertyHandle> StructPropertyHandle);`
- L40 _protected prototype_ `bool RemoveOverride(FName InQualityLevelName, TSharedRef<IPropertyHandle> StructPropertyHandle);`
- L41 _protected prototype_ `float CalcDesiredWidth(TSharedRef<IPropertyHandle> StructPropertyHandle);`
- L45 _private member_ `TWeakPtr<IPropertyUtilities> PropertyUtilities;` — Cached utils used for resetting customization when layout changes

### `Source/Editor/DetailCustomizations/Private/PhysicsConstraintComponentDetails.h` (Private)


#### class `FConstraintTransformCustomization`  
`class FConstraintTransformCustomization : public FMathStructCustomization`  
_L46-130_
- inherits: `FMathStructCustomization`
- desc: Proxy class customization that displays a constraint transform in a user friendly way. Constraint transforms are described by a position vector and a pair of orthonormal vectors representing the orientation. This class displays the transform as a position vector and a rotator in the UI details panel in a way that can be easily read and safely edited by users.
- L50 _public prototype_ `FConstraintTransformCustomization();`
- L52 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L54 _public prototype_ `void MakeRotationRow(TSharedRef<IPropertyHandle>& InPriAxisPropertyHandle, TSharedRef<IPropertyHandle>& InSecAxisPropertyHandle, FDetailWidgetRow& Row, TSharedRef<SWidget> EditSpaceToggleButtonWidget);`
- L55 _public prototype_ `void MakePositionRow(TSharedRef<IPropertyHandle>& InPositionPropertyHandle, FDetailWidgetRow& Row, TSharedRef<SWidget> EditSpaceToggleButtonWidget);`
- L57 _public prototype_ `template<typename ProxyType, typename NumericType> TSharedRef<SWidget> MakeNumericProxyWidget(TSharedRef<IPropertyHandle>& PriAxisPropertyHandle, TSharedRef<IPropertyHandle>& SecAxisPropertyHandle, TSharedRef< TProxyProperty<ProxyType, NumericType> >& ProxyValue, const FText& Label, bool bRotationInDegrees, const FLinearColor& LabelBackgroundColor);`
- L60 _public prototype_ `void OnCopy(TWeakPtr<IPropertyHandle> PositionPropertyHandlePtr, TWeakPtr<IPropertyHandle> PriAxisPropertyHandlePtr, TWeakPtr<IPropertyHandle> SecAxisPropertyHandlePtr);`
- L61 _public prototype_ `void OnCopyPosition(TWeakPtr<IPropertyHandle> PositionPropertyHandlePtr);`
- L62 _public prototype_ `void OnCopyRotation(TWeakPtr<IPropertyHandle> PriAxisPropertyHandlePtr, TWeakPtr<IPropertyHandle> SecAxisPropertyHandlePtr);`
- L63 _public prototype_ `void OnPaste(TWeakPtr<IPropertyHandle> PositionPropertyHandlePtr, TWeakPtr<IPropertyHandle> PriAxisPropertyHandlePtr, TWeakPtr<IPropertyHandle> SecAxisPropertyHandlePtr);`
- L64 _public prototype_ `void OnPastePosition(TWeakPtr<IPropertyHandle> PositionPropertyHandlePtr);`
- L65 _public prototype_ `void OnPasteRotation(TWeakPtr<IPropertyHandle> PriAxisPropertyHandlePtr, TWeakPtr<IPropertyHandle> SecAxisPropertyHandlePtr);`
- L67 _public prototype_ `void OnPasteFromText(const FString& InTag, const FString& InText, const TOptional<FGuid>& InOperationId, TWeakPtr<IPropertyHandle> PositionPropertyHandlePtr, TWeakPtr<IPropertyHandle> PriAxisPropertyHandlePtr, TWeakPtr<IPropertyHandle> SecAxisPropertyHandlePtr);`
- L70 _public prototype_ `bool IsRotationValueEnabled(TWeakPtr<IPropertyHandle> PriAxisPropertyHandlePtr, TWeakPtr<IPropertyHandle> SecAxisPropertyHandlePtr) const;`
- L71 _public prototype_ `template<typename ProxyType, typename NumericType> TOptional<NumericType> OnGetRotationValue(TWeakPtr<IPropertyHandle> PriAxisPropertyHandlePtr, TWeakPtr<IPropertyHandle> SecAxisPropertyHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue) const;`
- L72 _public prototype_ `template<typename ProxyType, typename NumericType> TOptional<NumericType> OnGetRotationValue(TWeakPtr<IPropertyHandle> PriAxisPropertyHandlePtr, TWeakPtr<IPropertyHandle> SecAxisPropertyHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue) const;`
- L73 _public prototype_ `template<typename ProxyType, typename NumericType> TOptional<NumericType> OnGetRotationValue(TWeakPtr<IPropertyHandle> PriAxisPropertyHandlePtr, TWeakPtr<IPropertyHandle> SecAxisPropertyHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue) const;`
- L75 _public prototype_ `bool IsPositionValueEnabled(TWeakPtr<IPropertyHandle> PositionWeakHandlePtr) const;`
- L76 _public prototype_ `template<typename ProxyType, typename NumericType> TOptional<NumericType> OnGetPositionValue(TWeakPtr<IPropertyHandle> PositionWeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue) const;`
- L77 _public prototype_ `template<typename ProxyType, typename NumericType> TOptional<NumericType> OnGetPositionValue(TWeakPtr<IPropertyHandle> PositionWeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue) const;`
- L78 _public prototype_ `template<typename ProxyType, typename NumericType> TOptional<NumericType> OnGetPositionValue(TWeakPtr<IPropertyHandle> PositionWeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue) const;`
- L80 _public prototype_ `void SetFrameLabelText(const FText InText);`
- L81 _public prototype_ `FText& GetFrameLabelText();`
- L83 _public prototype_ `void GetPositionAsFormattedString(FString& OutString);`
- L84 _public prototype_ `void GetRotationAsFormattedString(FString& OutString);`
- L85 _public prototype_ `void GetValueAsFormattedString(FString& OutString);`
- L86 _public prototype_ `bool SetPositionFromFormattedString(const FString& InString);`
- L87 _public prototype_ `bool SetRotationFromFormattedString(const FString& InString);`
- L88 _public prototype_ `bool SetValueFromFormattedString(const FString& InString);`
- L90 _public prototype_ `virtual bool CacheValues(TWeakPtr<IPropertyHandle> PositionPropertyHandlePtr) const;`
- L91 _public prototype_ `virtual bool CacheValues(TWeakPtr<IPropertyHandle> PriAxisPropertyHandlePtr, TWeakPtr<IPropertyHandle> SecAxisPropertyHandlePtr) const;`
- L92 _public prototype_ `virtual bool FlushValues(TWeakPtr<IPropertyHandle> PositionPropertyHandlePtr) const;`
- L93 _public prototype_ `virtual bool FlushValues(TWeakPtr<IPropertyHandle> PriAxisPropertyHandlePtr, TWeakPtr<IPropertyHandle> SecAxisPropertyHandlePtr) const;`
- L95 _public function_ `const FTransform& GetDefaultTransform() const`
- L97 _public prototype_ `void SetDefaultTransform(const FTransform& InTransform, TWeakPtr<IPropertyHandle> PositionPropertyHandlePtr, TWeakPtr<IPropertyHandle> PriAxisPropertyHandlePtr, TWeakPtr<IPropertyHandle> SecAxisPropertyHandlePtr);`
- L98 _public function_ `void SetPositionDisplayRelativeToDefault(const bool bValue)`
- L99 _public function_ `void SetRotationDisplayRelativeToDefault(const bool bValue)`
- L102 _protected prototype_ `void OrthonormalVectorPairToDisplayedRotator(const FVector& PriAxis, const FVector& SecAxis, FRotator& OutRotator) const;`
- L103 _protected prototype_ `void DisplayedRotatorToOrthonormalVectorPair(const FRotator& InRotator, FVector& OutPriAxis, FVector& OutSecAxis) const;`
- L105 _protected prototype_ `void OnPastePositionFromText(const FString& InTag, const FString& InText, const TOptional<FGuid>& InOperationId, TWeakPtr<IPropertyHandle> PositionPropertyHandlePtr);`
- L106 _protected prototype_ `void PastePositionFromText(const FString& InTag, const FString& InText, TWeakPtr<IPropertyHandle> PositionPropertyHandlePtr);`
- L108 _protected prototype_ `void OnPasteRotationFromText(const FString& InTag, const FString& InText, const TOptional<FGuid>& InOperationId, TWeakPtr<IPropertyHandle> PriAxisPropertyHandlePtr, TWeakPtr<IPropertyHandle> SecAxisPropertyHandlePtr);`
- L109 _protected prototype_ `void PasteRotationFromText(const FString& InTag, const FString& InText, TWeakPtr<IPropertyHandle> PriAxisPropertyHandlePtr, TWeakPtr<IPropertyHandle> SecAxisPropertyHandlePtr);`
- L111 _protected member_ `mutable TSharedRef< TProxyValue<FRotator> > CachedRotation;`
- L112 _protected member_ `mutable TSharedRef< TProxyProperty<FRotator, FRotator::FReal> > CachedRotationYaw;`
- L113 _protected member_ `mutable TSharedRef< TProxyProperty<FRotator, FRotator::FReal> > CachedRotationPitch;`
- L114 _protected member_ `mutable TSharedRef< TProxyProperty<FRotator, FRotator::FReal> > CachedRotationRoll;`
- L116 _protected member_ `mutable TSharedRef< TProxyValue<FVector> > CachedPosition;`
- L117 _protected member_ `mutable TSharedRef< TProxyProperty<FVector, FRotator::FReal> > CachedPositionX;`
- L118 _protected member_ `mutable TSharedRef< TProxyProperty<FVector, FRotator::FReal> > CachedPositionY;`
- L119 _protected member_ `mutable TSharedRef< TProxyProperty<FVector, FRotator::FReal> > CachedPositionZ;`
- L122 _protected member_ `FTransform DefaultTransform;` — Constraint transforms are displayed relative to this default transform when the associated ...DisplayRelativeToDefault flag is true. Otherwise they are displayed in the frame of the associated bone.
- L123 _protected member_ `FTransform InverseDefaultTransform;`
- L126 _protected member_ `bool bPositionDisplayRelativeToDefault;` — When true, the Position/Rotation components are displayed as offsets from the default transforms.
- L127 _protected member_ `bool bRotationDisplayRelativeToDefault;`
- L129 _protected member_ `FText FrameLabelText;`

#### class `FPhysicsConstraintComponentDetails`  
`class FPhysicsConstraintComponentDetails : public IDetailCustomization`  
_L135-243_
- inherits: `IDetailCustomization`
- desc: Detail customizer for PhysicsConstraintComponent and PhysicsConstraintTemplate
- L138 _public prototype_ `FPhysicsConstraintComponentDetails();`
- L141 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L144 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L169 _private prototype_ `bool IsPropertyEnabled(EPropertyType::Type Type) const;`
- L171 _private prototype_ `ECheckBoxState IsLimitRadioChecked(TSharedPtr<IPropertyHandle> Property, uint8 Value) const ;`
- L172 _private prototype_ `void OnLimitRadioChanged(ECheckBoxState CheckType, TSharedPtr<IPropertyHandle> Property, uint8 Value);`
- L174 _private prototype_ `void AddConstraintProperties(IDetailLayoutBuilder& DetailBuilder, TSharedPtr<IPropertyHandle> ConstraintInstancePropertyHandle, TArray<TWeakObjectPtr<UObject>>& Objects);`
- L175 _private prototype_ `void AddConstraintFrameTransform(const EConstraintFrame::Type ConstraintFrameType, IDetailCategoryBuilder& ConstraintCat, TSharedPtr<IPropertyHandle> ConstraintInstancePropertyHandle);`
- L176 _private prototype_ `void AddConstraintBehaviorProperties(IDetailLayoutBuilder& DetailBuilder, TSharedPtr<IPropertyHandle> ConstraintInstancePropertyHandle, TSharedPtr<IPropertyHandle> ProfileInstance);`
- L177 _private prototype_ `void AddLinearLimits(IDetailLayoutBuilder& DetailBuilder, TSharedPtr<IPropertyHandle> ConstraintInstancePropertyHandle, TSharedPtr<IPropertyHandle> ProfileInstance);`
- L178 _private prototype_ `void AddAngularLimits(IDetailLayoutBuilder& DetailBuilder, TSharedPtr<IPropertyHandle> ConstraintInstancePropertyHandle, TSharedPtr<IPropertyHandle> ProfileInstance);`
- L179 _private prototype_ `void AddLinearDrive(IDetailLayoutBuilder& DetailBuilder, TSharedPtr<IPropertyHandle> ConstraintInstancePropertyHandle, TSharedPtr<IPropertyHandle> ProfileInstance);`
- L180 _private prototype_ `void AddAngularDrive(IDetailLayoutBuilder& DetailBuilder, TSharedPtr<IPropertyHandle> ConstraintInstancePropertyHandle, TSharedPtr<IPropertyHandle> ProfileInstance);`
- L182 _private prototype_ `void OnCopyConstraintTransform(TSharedPtr<IPropertyHandle> PositionPropertyHandle, TSharedPtr<IPropertyHandle> PriAxisPropertyHandle, TSharedPtr<IPropertyHandle> SecAxisPropertyHandle, TSharedPtr<FConstraintTransformCustomization> RotationProxy);`
- L183 _private prototype_ `void OnPasteConstraintTransform(TSharedPtr<IPropertyHandle> PositionPropertyHandle, TSharedPtr<IPropertyHandle> PriAxisPropertyHandle, TSharedPtr<IPropertyHandle> SecAxisPropertyHandle, TSharedPtr<FConstraintTransformCustomization> RotationProxy);`
- L185 _private prototype_ `bool IsSnapConstraintTransformComponentVisible(TSharedPtr<IPropertyHandle> ConstraintInstancePropertyHandle, const EConstraintTransformComponentFlags SnapFlags);`
- L186 _private prototype_ `void ToggleDisplayConstraintTransformComponentRelativeToDefault(TSharedPtr<IPropertyHandle> ConstraintInstance, const EConstraintTransformComponentFlags ComponentFlags);`
- L187 _private prototype_ `bool IsDisplayingConstraintTransformComponentRelativeToDefault(const EConstraintTransformComponentFlags ComponentFlags);`
- L188 _private prototype_ `bool IsConstraintTransformComponentEnabled(const EConstraintTransformComponentFlags ComponentFlags) const;`
- L189 _private prototype_ `FSlateColor GetConstraintTransformColorAndOpacity(const EConstraintTransformComponentFlags ComponentFlags) const;`
- L192 _private prototype_ `void OnPasteConstraintTransformFromText( const FString& InTag, const FString& InText, const TOptional<FGuid>& InOperationId, TSharedPtr<IPropertyHandle> PositionPropertyHandle, TSharedPtr<IPropertyHandle> PriAxisPropertyHandle, TSharedPtr<IPropertyHandle> SecAxisPropertyHandle, TSharedPtr<FConstraintTransformCustomization> TransformProxy);`
- L201 _private prototype_ `void PasteConstraintTransformFromText( const FString& InTag, const FString& InText, TSharedPtr<IPropertyHandle> PositionPropertyHandle, TSharedPtr<IPropertyHandle> PriAxisPropertyHandle, TSharedPtr<IPropertyHandle> SecAxisPropertyHandle, TSharedPtr<FConstraintTransformCustomization> TransformProxy);`
- L209 _private prototype_ `TSharedRef<SWidget> MakeEditSpaceToggleButtonWidget(TSharedPtr<IPropertyHandle> ConstraintInstancePropertyHandle, const EConstraintTransformComponentFlags ComponentFlags);` — TODO - get this in the right place in src
- L210 _private prototype_ `void SnapConstraintTransformComponentsToDefault(TSharedPtr<IPropertyHandle> ConstraintInstancePropertyHandle, const EConstraintTransformComponentFlags SnapFlags);`
- L211 _private prototype_ `void UpdateTransformProxyDisplayRelativeToDefault(TSharedPtr<IPropertyHandle> ConstraintInstancePropertyHandle);`
- L212 _private prototype_ `FConstraintInstance* GetConstraintInstance();`
- L214 _private member_ `TSharedRef<FConstraintTransformCustomization> ChildTransformProxy;` — Creates a user friendly representation of the constraint's transform in the frame of the child bone in the UI details panel.
- L215 _private member_ `TSharedRef<FConstraintTransformCustomization> ParentTransformProxy;` — Creates a user friendly representation of the constraint's transform in the frame of the parent bone in the UI details panel.
- L217 _private member_ `TSharedPtr<IPropertyHandle> LinearXPositionDriveProperty;`
- L218 _private member_ `TSharedPtr<IPropertyHandle> LinearYPositionDriveProperty;`
- L219 _private member_ `TSharedPtr<IPropertyHandle> LinearZPositionDriveProperty;`
- L221 _private member_ `TSharedPtr<IPropertyHandle> LinearXVelocityDriveProperty;`
- L222 _private member_ `TSharedPtr<IPropertyHandle> LinearYVelocityDriveProperty;`
- L223 _private member_ `TSharedPtr<IPropertyHandle> LinearZVelocityDriveProperty;`
- L225 _private member_ `TSharedPtr<IPropertyHandle> AngularSwing1MotionProperty;`
- L226 _private member_ `TSharedPtr<IPropertyHandle> AngularSwing2MotionProperty;`
- L227 _private member_ `TSharedPtr<IPropertyHandle> AngularTwistMotionProperty;`
- L229 _private member_ `TSharedPtr<IPropertyHandle> ChildPositionPropertyHandle;`
- L230 _private member_ `TSharedPtr<IPropertyHandle> ChildPriAxisPropertyHandle;`
- L231 _private member_ `TSharedPtr<IPropertyHandle> ChildSecAxisPropertyHandle;`
- L233 _private member_ `TSharedPtr<IPropertyHandle> ParentPositionPropertyHandle;`
- L234 _private member_ `TSharedPtr<IPropertyHandle> ParentPriAxisPropertyHandle;`
- L235 _private member_ `TSharedPtr<IPropertyHandle> ParentSecAxisPropertyHandle;`
- L237 _private member_ `UPhysicsConstraintComponent* ConstraintComp;`
- L238 _private member_ `UPhysicsConstraintTemplate* ConstraintTemplate;`
- L240 _private member_ `UPhysicsAsset* ParentPhysicsAsset;`
- L242 _private member_ `bool bInPhat;`

#### struct `FPhysicsConstraintComponentDetails::EPropertyType`  
`struct EPropertyType`  
_L147-167_

#### enum `FPhysicsConstraintComponentDetails::EPropertyType::Type`  
`enum Type`  
_L149-166_
- L151 _public enumerator_ `LinearXPositionDrive`
- L152 _public enumerator_ `LinearYPositionDrive`
- L153 _public enumerator_ `LinearZPositionDrive`
- L154 _public enumerator_ `LinearPositionDrive`
- L155 _public enumerator_ `LinearXVelocityDrive`
- L156 _public enumerator_ `LinearYVelocityDrive`
- L157 _public enumerator_ `LinearZVelocityDrive`
- L158 _public enumerator_ `LinearVelocityDrive`
- L159 _public enumerator_ `LinearDrive`
- L161 _public enumerator_ `AngularSwingLimit`
- L162 _public enumerator_ `AngularSwing1Limit`
- L163 _public enumerator_ `AngularSwing2Limit`
- L164 _public enumerator_ `AngularTwistLimit`
- L165 _public enumerator_ `AngularAnyLimit`

### `Source/Editor/DetailCustomizations/Private/PhysicsSettingsDetails.h` (Private)


#### class `FPhysicalSurfaceListItem`  
`class FPhysicalSurfaceListItem`  
_L27-39_
- desc: Class containing the friend information - used to build the list view
- L34 _public function_ `FPhysicalSurfaceListItem(TSharedPtr<FPhysicalSurfaceName> InPhysicalSurface) : PhysicalSurface(InPhysicalSurface)` — Constructor takes the required details
- L38 _public member_ `TSharedPtr<FPhysicalSurfaceName> PhysicalSurface;`

#### class `SPhysicalSurfaceEditBox`  
`class SPhysicalSurfaceEditBox : public SCompoundWidget`  
_L44-74_
- inherits: `SCompoundWidget`
- desc: Implements the FriendsList
- L48 _public function_ `SLATE_BEGIN_ARGS(SPhysicalSurfaceEditBox)`
- L61 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the application. @param InArgs - The Slate argument list.
- L63 _public prototype_ `FString GetTypeString() const;`
- L65 _public prototype_ `FText GetName() const;`
- L66 _public prototype_ `void NewNameEntered(const FText& NewText, ETextCommit::Type CommitInfo);`
- L67 _public prototype_ `void OnTextChanged(const FText& NewText);`
- L70 _private member_ `TSharedPtr<FPhysicalSurfaceName> PhysicalSurface;`
- L71 _private member_ `UEnum * PhysicalSurfaceEnum;`
- L72 _private member_ `FOnCommitChange OnCommitChange;`
- L73 _private member_ `TSharedPtr<SEditableTextBox> NameEditBox;`

#### class `FPhysicsSettingsDetails`  
`class FPhysicsSettingsDetails : public IDetailCustomization`  
_L78-105_
- inherits: `IDetailCustomization`
- L82 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L85 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L95 _private prototype_ `TSharedRef<ITableRow> HandleGenerateListWidget(TSharedPtr< FPhysicalSurfaceListItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a widget for a channel item. @param InItem - the ChannelListItem @param OwnerTable - the owning table @return The table row widget
- L99 _private member_ `TArray< TSharedPtr< FPhysicalSurfaceListItem > > PhysicalSurfaceList;`
- L101 _private member_ `UPhysicsSettings * PhysicsSettings;`
- L102 _private member_ `UEnum* PhysicalSurfaceEnum;`
- L104 _private prototype_ `void OnCommitChange();` — functions

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_DELEGATE(FOnCommitChange)`
- L76 _typedef_ `typedef SListView< TSharedPtr< FPhysicalSurfaceListItem > > SPhysicalSurfaceListView;`

### `Source/Editor/DetailCustomizations/Private/PoseAssetDetails.h` (Private)


#### class `FPoseAssetDetails`  
`class FPoseAssetDetails : public IDetailCustomization`  
_L28-101_
- inherits: `IDetailCustomization`
- L32 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L35 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L37 _public prototype_ `virtual ~FPoseAssetDetails();`
- L40 _private member_ `TWeakObjectPtr<UPoseAsset> PoseAsset;`
- L41 _private member_ `TWeakObjectPtr<USkeleton> TargetSkeleton;`
- L44 _private member_ `TSharedPtr<IPropertyHandle> RetargetSourceNameHandler;` — property handler
- L45 _private member_ `TSharedPtr<IPropertyHandle> RetargetSourceAssetHandle;`
- L48 _private member_ `TSharedPtr< SSearchableComboBox > RetargetSourceComboBox;` — retarget source related
- L49 _private member_ `TArray< TSharedPtr< FString > > RetargetSourceComboList;`
- L51 _private prototype_ `TSharedRef<SWidget> MakeRetargetSourceComboWidget( TSharedPtr<FString> InItem );`
- L52 _private prototype_ `void OnRetargetSourceChanged( TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo );`
- L53 _private prototype_ `FText GetRetargetSourceComboBoxContent() const;`
- L54 _private prototype_ `FText GetRetargetSourceComboBoxToolTip() const;`
- L55 _private prototype_ `void OnRetargetSourceComboOpening();`
- L56 _private prototype_ `TSharedPtr<FString> GetRetargetSourceString(FName RetargetSourceName) const;`
- L57 _private prototype_ `EVisibility UpdateRetargetSourceAssetDataVisibility() const;`
- L58 _private prototype_ `FReply UpdateRetargetSourceAssetData();`
- L60 _private member_ `USkeleton::FOnRetargetSourceChanged OnDelegateRetargetSourceChanged;`
- L61 _private member_ `FDelegateHandle OnDelegateRetargetSourceChangedDelegateHandle;`
- L62 _private prototype_ `void RegisterRetargetSourceChanged();`
- L63 _private prototype_ `void DelegateRetargetSourceChanged();`
- L66 _private prototype_ `void OnAdditiveToggled(ECheckBoxState NewCheckedState);` — additive setting
- L67 _private prototype_ `ECheckBoxState IsAdditiveChecked() const;`
- L70 _private member_ `TSharedPtr< SSearchableComboBox > BasePoseComboBox;` — base pose
- L71 _private member_ `TArray< TSharedPtr< FString > > BasePoseComboList;`
- L73 _private prototype_ `TSharedRef<SWidget> MakeBasePoseComboWidget(TSharedPtr<FString> InItem);`
- L74 _private prototype_ `void OnBasePoseChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L75 _private prototype_ `FText GetBasePoseComboBoxContent() const;`
- L76 _private prototype_ `FText GetBasePoseComboBoxToolTip() const;`
- L77 _private prototype_ `void OnBasePoseComboOpening();`
- L78 _private prototype_ `TSharedPtr<FString> GetBasePoseString(int32 InBasePoseIndex) const;`
- L79 _private prototype_ `bool CanSelectBasePose() const;`
- L80 _private member_ `UPoseAsset::FOnPoseListChanged OnDelegatePoseListChanged;`
- L81 _private member_ `FDelegateHandle OnDelegatePoseListChangedDelegateHandle;`
- L82 _private prototype_ `void RegisterBasePoseChanged();`
- L83 _private prototype_ `void RefreshBasePoseChanged();`
- L85 _private member_ `bool bCachedAdditive;`
- L86 _private member_ `int32 CachedBasePoseIndex;`
- L87 _private prototype_ `void CachePoseAssetData();`
- L89 _private prototype_ `EVisibility CanApplySettings() const;`
- L90 _private prototype_ `FReply OnApplyAdditiveSettings();`
- L92 _private member_ `TSharedPtr<IPropertyHandle> SourceAnimationPropertyHandle;`
- L94 _private prototype_ `void OnSourceAnimationChanged(const FAssetData& AssetData);` — replacing source animation
- L95 _private prototype_ `bool ShouldFilterAsset(const FAssetData& AssetData);`
- L96 _private prototype_ `FReply OnUpdatePoseSourceAnimation();`
- L97 _private prototype_ `bool IsUpdateSourceEnabled() const;`
- L98 _private prototype_ `FText GetAnimationUpdateButtonText() const;`
- L100 _private prototype_ `FText GetButtonText() const;`

### `Source/Editor/DetailCustomizations/Private/PostProcessSettingsCustomization.h` (Private)


#### class `FPostProcessSettingsCustomization`  
`class FPostProcessSettingsCustomization : public IPropertyTypeCustomization`  
_L20-41_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details view customization for the FPostProcessSettings structure.
- L30 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance( )` — Creates an instance of this class. @return The new instance.
- L39 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L40 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`

#### class `FWeightedBlendableCustomization`  
`class FWeightedBlendableCustomization : public IPropertyTypeCustomization`  
_L47-87_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details view customization for the FBlendablesWrapper structure.
- L57 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance( )` — Creates an instance of this class. @return The new instance.
- L66 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L67 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L69 _public prototype_ `TSharedRef<SWidget> GenerateContentWidget(TSharedRef<IPropertyHandle> StructPropertyHandle, UPackage* Package, TSharedPtr<IPropertyHandle> Weight, TSharedPtr<IPropertyHandle> Value);`
- L72 _public prototype_ `void AddDirectAsset(TSharedRef<IPropertyHandle> StructPropertyHandle, TSharedPtr<IPropertyHandle> Weight, TSharedPtr<IPropertyHandle> Value, UClass* Class);` — "Outer" is the object that has the blendables container
- L74 _public prototype_ `void AddIndirectAsset(TSharedPtr<IPropertyHandle> Weight);` — "Outer" is a package
- L77 _public prototype_ `FReply JumpToDirectAsset(TSharedPtr<IPropertyHandle> Value);` — open the details panel for this object
- L80 _public prototype_ `FText GetDirectAssetName(TSharedPtr<IPropertyHandle> Value) const;` — to get the blendable type as string
- L83 _public prototype_ `int32 ComputeSwitcherIndex(TSharedRef<IPropertyHandle> StructPropertyHandle, UPackage* Package, TSharedPtr<IPropertyHandle> Weight, TSharedPtr<IPropertyHandle> Value) const;` — @return 0:choose 1:direct, 2:indirect
- L86 _public prototype_ `EVisibility IsWeightVisible(TSharedPtr<IPropertyHandle> Weight) const;` — the weight is only visible if the user choose the type (or the reference)

### `Source/Editor/DetailCustomizations/Private/PrimitiveComponentDetails.h` (Private)


#### class `FPrimitiveComponentDetails`  
`class FPrimitiveComponentDetails : public IDetailCustomization`  
_L21-58_
- inherits: `IDetailCustomization`
- L25 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L28 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L31 _private prototype_ `void AddMaterialCategory( IDetailLayoutBuilder& DetailBuilder);`
- L32 _private prototype_ `void AddLightingCategory(IDetailLayoutBuilder& DetailBuilder);`
- L33 _private prototype_ `void AddPhysicsCategory(IDetailLayoutBuilder& DetailBuilder);`
- L34 _private prototype_ `void AddCollisionCategory(IDetailLayoutBuilder& DetailBuilder);`
- L36 _private prototype_ `void AddAdvancedSubCategory(IDetailLayoutBuilder& DetailBuilder, FName MainCategory, FName SubCategory);`
- L38 _private prototype_ `FReply OnMobilityResetClicked(TSharedRef<IPropertyHandle> MobilityHandle);`
- L40 _private prototype_ `EVisibility GetMobilityResetVisibility(TSharedRef<IPropertyHandle> MobilityHandle) const;`
- L43 _private prototype_ `bool IsSimulatePhysicsEditable() const;` — Returns whether to enable editing the 'Simulate Physics' checkbox based on the selected objects physics geometry
- L45 _private prototype_ `bool IsUseAsyncEditable() const;` — Returns whether to enable editing the 'Use Async Scene' checkbox based on the selected objects' mobility and if the project uses an AsyncScene
- L47 _private prototype_ `TOptional<float> OnGetBodyMass() const;`
- L48 _private prototype_ `bool IsBodyMassReadOnly() const;`
- L49 _private function_ `bool IsBodyMassEnabled() const`
- L53 _private member_ `TArray< TWeakObjectPtr<UObject> > ObjectsCustomized;` — Objects being customized so we can update the 'Simulate Physics' state if physics geometry is added/removed
- L55 _private member_ `TSharedPtr<class FComponentMaterialCategory> MaterialCategory;`
- L56 _private member_ `TSharedPtr<class FBodyInstanceCustomizationHelper> BodyInstanceCustomizationHelper;`

### `Source/Editor/DetailCustomizations/Private/RangeStructCustomization.h` (Private)


#### class `FRangeStructCustomization`  
`template <typename NumericType> class FRangeStructCustomization : public IPropertyTypeCustomization`  
_L23-136_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details panel customization for FFloatRange structures.
- L27 _public function_ `FRangeStructCustomization() : bIsUsingSlider(false)`
- L34 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L35 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L44 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates a new instance. @return A new struct customization for Guids.
- L55 _protected prototype_ `TOptional<NumericType> OnGetValue(TWeakPtr<IPropertyHandle> ValueWeakPtr, TWeakPtr<IPropertyHandle> TypeWeakPtr) const;` — Gets the value for the provided property handle @param	ValueWeakPtr	Handle to the property to get the value from @param	TypeWeakPtr		Handle to the property to get the type from @return	The value or unset if it could not be accessed
- L64 _protected prototype_ `void OnValueCommitted(NumericType NewValue, ETextCommit::Type CommitType, TWeakPtr<IPropertyHandle> HandleWeakPtr);` — Called when the value is committed from the property editor @param	NewValue		The new value of the property @param	CommitType		How the value was committed (unused) @param	HandleWeakPtr	Handle to the property that the new value is for
- L72 _protected prototype_ `void OnValueChanged(NumericType NewValue, TWeakPtr<IPropertyHandle> HandleWeakPtr);` — Called when the value is changed in the property editor @param	NewValue		The new value of the property @param	HandleWeakPtr	Handle to the property that the new value is for
- L77 _protected prototype_ `void OnBeginSliderMovement();` — Called when a value starts to be changed by a slider
- L84 _protected prototype_ `void OnEndSliderMovement(NumericType NewValue);` — Called when a value stops being changed by a slider @param	NewValue		The new value of the property
- L92 _protected prototype_ `bool OnQueryIfEnabled(TWeakPtr<IPropertyHandle> HandleWeakPtr) const;` — Determines if the value is valid from the handle of the range type passed in @param	HandleWeakPtr	Handle to the property to get the type from @return	Whether the value is valid or not.
- L99 _protected prototype_ `bool ShouldAllowSpin() const;` — Determines if the spin box is enabled on a numeric value widget @return Whether the spin box should be enabled.
- L107 _protected prototype_ `TSharedRef<SWidget> OnGenerateComboWidget(TSharedPtr<FString> InComboString);` — Generates a row of the combo widget @param	InComboString	Item string to be displayed in the combo item @return	An SWidget representing the combo row.
- L116 _protected prototype_ `void OnComboSelectionChanged(TSharedPtr<FString> InSelectedItem, ESelectInfo::Type SelectInfo, TWeakPtr<IPropertyHandle> HandleWeakPtr);` — Called when an item is selected in the combo box @param	InSelectedItem	String of the item selected @param	SelectInfo		Type of selection @param	HandleWeakPtr	Handle to the type property which will be changed by the combo selection
- L119 _protected member_ `TSharedPtr<IPropertyHandle> LowerBoundStructHandle;` — Cached shared pointers to properties that we are managing
- L120 _protected member_ `TSharedPtr<IPropertyHandle> UpperBoundStructHandle;`
- L121 _protected member_ `TSharedPtr<IPropertyHandle> LowerBoundValueHandle;`
- L122 _protected member_ `TSharedPtr<IPropertyHandle> LowerBoundTypeHandle;`
- L123 _protected member_ `TSharedPtr<IPropertyHandle> UpperBoundValueHandle;`
- L124 _protected member_ `TSharedPtr<IPropertyHandle> UpperBoundTypeHandle;`
- L127 _protected member_ `TOptional<NumericType> MinAllowedValue;` — Min and max allowed values from the metadata
- L128 _protected member_ `TOptional<NumericType> MaxAllowedValue;`
- L131 _protected member_ `TArray< TSharedPtr<FString> > ComboBoxList;` — Arrays of combo box data: list items, and tooltips
- L132 _protected member_ `TArray< FText > ComboBoxToolTips;`
- L135 _protected member_ `bool bIsUsingSlider;` — Flags whether the slider is being moved at the moment on any of our widgets

### `Source/Editor/DetailCustomizations/Private/RawDistributionVectorStructCustomization.h` (Private)


#### class `FRawDistributionVectorStructCustomization`  
`class FRawDistributionVectorStructCustomization : public IPropertyTypeCustomization`  
_L15-23_
- inherits: `IPropertyTypeCustomization`
- desc: Class for FRawDistributionVector struct customization
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization instance
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Source/Editor/DetailCustomizations/Private/ReflectionCaptureDetails.h` (Private)


#### class `FReflectionCaptureDetails`  
`class FReflectionCaptureDetails : public IDetailCustomization`  
_L10-20_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _private prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface

### `Source/Editor/DetailCustomizations/Private/RenderPassesCustomization.h` (Private)


#### class `FRenderPassesCustomization`  
`class FRenderPassesCustomization : public IPropertyTypeCustomization`  
_L12-21_
- inherits: `IPropertyTypeCustomization`
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;` — IDetailCustomization interface
- L20 _public function_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils ) override`

### `Source/Editor/DetailCustomizations/Private/RotatorStructCustomization.h` (Private)


#### class `FRotatorStructCustomization`  
`class FRotatorStructCustomization : public FMathStructCustomization`  
_L15-30_
- inherits: `FMathStructCustomization`
- desc: Customizes FRotator structs.
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — @return A new instance of this class
- L26 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L29 _private prototype_ `virtual void GetSortedChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, TArray<TSharedRef<IPropertyHandle>>& OutChildren) override;` — FMathStructCustomization interface

### `Source/Editor/DetailCustomizations/Private/SPerPlatformPropertiesWidget.h` (Private)


#### class `SPerPlatformPropertiesRow`  
`class SPerPlatformPropertiesRow : public SCompoundWidget`  
_L24-57_
- inherits: `SCompoundWidget`
- desc: SPerPlatformPropertiesWidget
- L28 _public function_ `SLATE_BEGIN_ARGS(SPerPlatformPropertiesRow)`
- L31 _public prototype_ `SLATE_EVENT(FOnGenerateWidget, OnGenerateWidget) SLATE_EVENT(FOnPlatformOverrideAction, OnRemovePlatform) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FName PlatformName);`
- L44 _protected prototype_ `TSharedRef<SWidget> MakePerPlatformWidget(FName InName);`
- L46 _protected prototype_ `FReply RemovePlatform(FName PlatformName);`
- L48 _protected prototype_ `EActiveTimerReturnType CheckPlatformCount(double InCurrentTime, float InDeltaSeconds);`
- L50 _protected prototype_ `void AddPlatformToMenu(const FName& PlatformName, const FTextFormat Format, FMenuBuilder& AddPlatformMenuBuilder);`
- L52 _protected member_ `FOnGenerateWidget OnGenerateWidget;`
- L53 _protected member_ `FOnPlatformOverrideAction OnRemovePlatform;`
- L54 _protected member_ `TAttribute<TArray<FName>> PlatformOverrideNames;`
- L55 _protected member_ `int32 LastPlatformOverrideNames;`
- L56 _protected member_ `bool bAddedMenuItem;`

### `Source/Editor/DetailCustomizations/Private/SceneCaptureDetails.h` (Private)


#### class `FSceneCaptureDetails`  
`class FSceneCaptureDetails : public IDetailCustomization`  
_L15-44_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _private prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L26 _private member_ `TSharedPtr<IPropertyHandle> ShowFlagSettingsProperty;` — The show flags property on the SceneCaptureComponent
- L34 _private prototype_ `ECheckBoxState OnGetDisplayCheckState(FString ShowFlagName) const;` — Gets the display state to send to a display filter check box @param The type of checkbox. @return The desired checkbox state.
- L37 _private prototype_ `void OnShowFlagCheckStateChanged(ECheckBoxState InNewRadioState, FString FlagName);` — Show flag settings changed, so update the scene capture
- L40 _private prototype_ `bool GetShowFlagResetVisibility(FString ShowFlagName) const;` — Gets the visibility of the reset to default property detail.
- L43 _private prototype_ `void OnResetShowFlag(FString ShowFlagName);` — Reset the specified show flag to its (archetype) default.

### `Source/Editor/DetailCustomizations/Private/SceneComponentDetails.h` (Private)


#### class `FSceneComponentDetails`  
`class FSceneComponentDetails : public IDetailCustomization`  
_L10-21_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L20 _private prototype_ `void MakeTransformDetails( IDetailLayoutBuilder& DetailBuilder );`

### `Source/Editor/DetailCustomizations/Private/SkeletalControlNodeDetails.h` (Private)


#### class `FSkeletalControlNodeDetails`  
`class FSkeletalControlNodeDetails : public IDetailCustomization`  
_L22-47_
- inherits: `IDetailCustomization`
- L25 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L28 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L32 _protected prototype_ `void OnGenerateElementForPropertyPin(TSharedRef<IPropertyHandle> ElementProperty, int32 ElementIndex, IDetailChildrenBuilder& ChildrenBuilder, FName CategoryName);`
- L35 _protected prototype_ `ECheckBoxState GetShowPinValueForProperty(TSharedRef<IPropertyHandle> InElementProperty) const;` — Returns the current value of the checkbox being displayed for the bShowPin property
- L38 _protected prototype_ `void OnShowPinChanged(ECheckBoxState InNewState, TSharedRef<IPropertyHandle> InElementProperty);` — Helper function for changing the value of the bShowPin checkbox to update the property
- L41 _protected prototype_ `FReply HideAllUnconnectedPins(const bool bHideInputPins);` — Handler to hide all unconnected pins on a BreakStruct node
- L44 _private member_ `IDetailCategoryBuilder* DetailCategory;`
- L45 _private member_ `TWeakObjectPtr<class UK2Node> HideUnconnectedPinsNode;`
- L46 _private member_ `TSharedPtr<class IPropertyHandleArray> ArrayProperty;`

### `Source/Editor/DetailCustomizations/Private/SkeletalMeshComponentDetails.h` (Private)


#### class `FSkeletalMeshComponentDetails`  
`class FSkeletalMeshComponentDetails : public IDetailCustomization`  
_L28-127_
- inherits: `IDetailCustomization`
- L31 _public prototype_ `FSkeletalMeshComponentDetails();`
- L32 _public prototype_ `~FSkeletalMeshComponentDetails();`
- L35 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L38 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L40 _public prototype_ `static TSharedRef<SWidget> CreateAsyncSceneValueWidgetWithWarning(const TSharedPtr<IPropertyHandle>& AsyncScenePropertyHandle);`
- L43 _private prototype_ `void UpdateAnimationCategory(IDetailLayoutBuilder& DetailBuilder);`
- L44 _private prototype_ `void UpdatePhysicsCategory(IDetailLayoutBuilder& DetailBuilder);`
- L47 _private prototype_ `EVisibility VisibilityForAnimationMode(EAnimationMode::Type AnimationMode) const;` — Function that returns whether the specified animation mode should be visible
- L50 _private prototype_ `EVisibility VisibilityForBlueprintMode() const;` — Helper wrapper functions for VisibilityForAnimationMode
- L51 _private function_ `EVisibility VisibilityForSingleAnimMode() const`
- L52 _private prototype_ `bool AnimPickerIsEnabled() const;`
- L54 _private prototype_ `EVisibility VisibilityForAnimModeProperty() const;`
- L57 _private prototype_ `bool OnShouldFilterAnimAsset(const FAssetData& AssetData);` — Handler for filtering animation assets in the UI picker when asset mode is selected
- L60 _private member_ `USkeletalMeshComponent::FOnSkeletalMeshPropertyChanged OnSkeletalMeshPropertyChanged;` — Delegate called when a skeletal mesh property is changed on a selected object
- L63 _private prototype_ `void PerformInitialRegistrationOfSkeletalMeshes(IDetailLayoutBuilder& DetailBuilder);` — Register/Unregister the mesh changed delegate to TargetComponent
- L64 _private prototype_ `void RegisterSkeletalMeshPropertyChanged(TWeakObjectPtr<USkeletalMeshComponent> Mesh);`
- L65 _private prototype_ `void UnregisterSkeletalMeshPropertyChanged(TWeakObjectPtr<USkeletalMeshComponent> Mesh);`
- L66 _private prototype_ `void UnregisterAllMeshPropertyChangedCallers();`
- L72 _private prototype_ `USkeleton* GetValidSkeletonFromRegisteredMeshes() const;` — Iterates over registered meshes and returns a pointer to the common skeleton used by all of them. If the meshes use more than one different skeleton, NULL is returned.
- L75 _private prototype_ `void SkeletalMeshPropertyChanged();` — Bound to the delegate used to detect changes in skeletal mesh properties
- L78 _private prototype_ `TSharedRef<SWidget> GetClassPickerMenuContent();` — Generates menu content for the class picker when it is clicked
- L81 _private prototype_ `FText GetSelectedAnimBlueprintName() const;` — Gets the currently selected blueprint name to display on the class picker combo button
- L84 _private prototype_ `void OnClassPicked(UClass* PickedClass);` — Callback from the class picker when the user selects a class
- L87 _private prototype_ `void OnBrowseToAnimBlueprint();` — Callback from the detail panel to browse to the selected anim asset
- L90 _private prototype_ `void UseSelectedAnimBlueprint();` — Callback from the details panel to use the currently selected asset in the content browser
- L93 _private prototype_ `void UpdateSkeletonNameAndPickerVisibility();` — Called when a skeletal mesh property changes.
- L96 _private member_ `IDetailLayoutBuilder* CurrentDetailBuilder;` — Cached layout builder for use after customization
- L99 _private member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjects;` — Cached selected objects to use when the skeletal mesh property changes
- L102 _private member_ `TArray<TWeakObjectPtr<USkeletalMeshComponent>> SelectedSkeletalMeshComponents;` — Cache of mesh components in the current selection
- L105 _private member_ `TSharedPtr<IPropertyHandle> AnimationModeHandle;` — Caches the AnimationMode Handle so we can look up its value after customization has finished
- L108 _private member_ `TSharedPtr<IPropertyHandle> AnimationBlueprintHandle;` — Caches the AnimationBlueprintGeneratedClass Handle so we can look up its value after customization has finished
- L111 _private member_ `TSharedPtr<IPropertyHandle> AsyncSceneHandle;` — Caches the AsyncScene handle so we can look up its value after customization has finished.
- L114 _private member_ `FString SelectedSkeletonName;` — Full name of the currently selected skeleton to use for filtering animation assets
- L117 _private member_ `USkeleton* Skeleton;` — The skeleton that we grab the name from for filtering.
- L120 _private member_ `bool bAnimPickerEnabled;` — Current enabled state of the animation asset picker in the details panel
- L123 _private member_ `TSharedPtr<SComboButton> ClassPickerComboButton;` — The combo button for the class picker, Cached so we can close it when the user picks something
- L126 _private member_ `TMap<USkeletalMeshComponent*, FDelegateHandle> OnSkeletalMeshPropertyChangedDelegateHandles;` — Per-mesh handles to registered OnSkeletalMeshPropertyChanged delegates

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API DETAILCUSTOMIZATIONS_API`

### `Source/Editor/DetailCustomizations/Private/SkeletalMeshDetails.h` (Private)


#### class `FSkeletalMeshDetails`  
`class FSkeletalMeshDetails : public IDetailCustomization`  
_L10-19_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& LayoutBuilder) override;` — Begin IDetailCustomization interface
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it

### `Source/Editor/DetailCustomizations/Private/SkeletalMeshLODSettingsDetails.h` (Private)


#### class `FSkeletalMeshLODSettingsDetails`  
`class FSkeletalMeshLODSettingsDetails : public IDetailCustomization`  
_L10-20_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& LayoutBuilder) override;` — Begin IDetailCustomization interface
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it

### `Source/Editor/DetailCustomizations/Private/SkeletalMeshReductionSettingsDetails.h` (Private)


#### class `FSkeletalMeshReductionSettingsDetails`  
`class FSkeletalMeshReductionSettingsDetails : public IPropertyTypeCustomization`  
_L15-55_
- inherits: `IPropertyTypeCustomization`
- L19 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L23 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L26 _private prototype_ `float ConvertToPercentage(float Input) const;`
- L27 _private prototype_ `float ConvertToDecimal(float Input) const;`
- L29 _private member_ `TSharedPtr<IPropertyHandle> TerminationCriterionPropertyHandle;`
- L30 _private member_ `TSharedPtr<IPropertyHandle> ReductionMethodPropertyHandle;`
- L31 _private member_ `TSharedPtr<IPropertyHandle> NumTrianglesPercentagePropertyHandle;`
- L32 _private member_ `TSharedPtr<IPropertyHandle> MaxDeviationPercentagePropertyHandle;`
- L34 _private prototype_ `float GetNumTrianglesPercentage() const;`
- L35 _private prototype_ `void SetNumTrianglesPercentage(float Value);`
- L37 _private prototype_ `float GetAccuracyPercentage() const;`
- L38 _private prototype_ `void SetAccuracyPercentage(float Value);`
- L41 _private prototype_ `EVisibility GetVisibiltyIfCurrentReductionMethodIsNot(SkeletalMeshOptimizationType ReductionType) const;` — Used the the thrid-party UI.
- L44 _private prototype_ `EVisibility ShowIfCurrentCriterionIs(TArray<SkeletalMeshTerminationCriterion> TerminationCriterionArray) const;` — Used by the native tool UI.
- L47 _private prototype_ `bool UseNativeLODTool() const;` — Detect usage of thirdparty vs native tool
- L48 _private prototype_ `bool UseNativeReductionTool() const;`
- L54 _private prototype_ `EVisibility GetVisibilityForThirdPartyTool() const;` — Used to hide parameters that only make sense for the third party tool. @return EVisibility::Visible if we are using the simplygon tool, otherwise EVisibility::Hidden

### `Source/Editor/DetailCustomizations/Private/SkeletonDetails.h` (Private)


#### class `FSkeletonDetails`  
`class FSkeletonDetails : public IDetailCustomization`  
_L10-18_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Source/Editor/DetailCustomizations/Private/SkinnedMeshComponentDetails.h` (Private)


#### class `FSkinnedMeshComponentDetails`  
`class FSkinnedMeshComponentDetails : public IDetailCustomization`  
_L21-48_
- inherits: `IDetailCustomization`
- L25 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L28 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L31 _private prototype_ `void CreateActuallyUsedPhysicsAssetWidget(FDetailWidgetRow& OutWidgetRow, IDetailLayoutBuilder* DetailBuilder) const;`
- L33 _private prototype_ `FText GetUsedPhysicsAssetAsText(IDetailLayoutBuilder* DetailBuilder) const;`
- L34 _private prototype_ `void BrowseUsedPhysicsAsset(IDetailLayoutBuilder* DetailBuilder) const;`
- L36 _private prototype_ `bool FindUniqueUsedPhysicsAsset(IDetailLayoutBuilder* DetailBuilder, UPhysicsAsset*& OutFoundPhysicsAsset) const;`
- L38 _private prototype_ `void CreateSkinWeightProfileSelectionWidget(IDetailCategoryBuilder& SkinWeightCategory);`
- L39 _private prototype_ `void PopulateSkinWeightProfileNames();`
- L42 _private member_ `TSharedPtr<SNameComboBox> SkinWeightCombo;` — Skin Weight Profile Selector
- L43 _private member_ `TArray<TSharedPtr<FName>> SkinWeightProfileNames;`
- L44 _private member_ `TSharedPtr<IPropertyHandle> SkeletalMeshHandle;`
- L46 _private member_ `TWeakObjectPtr<USkinnedMeshComponent> WeakSkinnedMeshComponent;`

### `Source/Editor/DetailCustomizations/Private/SkyLightComponentDetails.h` (Private)


#### class `FSkyLightComponentDetails`  
`class FSkyLightComponentDetails : public IDetailCustomization`  
_L14-36_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _private prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L23 _private prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder) override;`
- L25 _private prototype_ `FReply OnUpdateSkyCapture();`
- L27 _private prototype_ `void OnSourceTypeChanged();`
- L32 _private member_ `TWeakPtr<IDetailLayoutBuilder> CachedDetailBuilder;` — The detail builder for this cusomtomisation
- L35 _private member_ `TWeakObjectPtr<ASkyLight> SkyLight;` — The selected sky light

### `Source/Editor/DetailCustomizations/Private/SlateColorCustomization.h` (Private)


#### class `FSlateColorCustomization`  
`class FSlateColorCustomization : public FColorStructCustomization`  
_L14-44_
- inherits: `FColorStructCustomization`
- L19 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L25 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L26 _public prototype_ `virtual void MakeHeaderRow(TSharedRef<class IPropertyHandle>& InStructPropertyHandle, FDetailWidgetRow& Row) override;`
- L31 _private prototype_ `virtual void OnValueChanged();` — Called when the value is changed in the property editor.
- L33 _private prototype_ `ECheckBoxState GetForegroundCheckState() const;`
- L35 _private prototype_ `void HandleForegroundChanged(ECheckBoxState CheckedState);`
- L40 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — slate color struct handle
- L42 _private member_ `TSharedPtr<IPropertyHandle> ColorRuleHandle;`
- L43 _private member_ `TSharedPtr<IPropertyHandle> SpecifiedColorHandle;`

### `Source/Editor/DetailCustomizations/Private/SlateSoundCustomization.h` (Private)


#### class `FSlateSoundStructCustomization`  
`class FSlateSoundStructCustomization : public IPropertyTypeCustomization`  
_L13-28_
- inherits: `IPropertyTypeCustomization`
- desc: Customize the appearance of an FSlateSound
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L24 _protected prototype_ `void OnObjectChanged(const FAssetData&);` — Called when the resource object used by this FSlateSound has been changed
- L27 _protected member_ `TArray<FSlateSound*> SlateSoundStructs;` — Array of FSlateSound instances this customization is currently editing

### `Source/Editor/DetailCustomizations/Private/SoftClassPathCustomization.h` (Private)


#### class `FSoftClassPathCustomization`  
`class FSoftClassPathCustomization : public IPropertyTypeCustomization`  
_L17-42_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes a string class reference to look like a UClass property
- L20 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L31 _private prototype_ `const UClass* OnGetClass() const;` — @return The class currently set on this reference
- L33 _private prototype_ `void OnSetClass(const UClass* NewClass);` — Set the class used by this reference
- L36 _private prototype_ `static const UClass* StringToClass(const FString& ClassName);` — Find or load the class associated with the given string
- L39 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Handle to the property being customized
- L41 _private member_ `mutable TWeakObjectPtr<UClass> CachedClassPtr;` — A cache of the currently resolved value for the class name

### `Source/Editor/DetailCustomizations/Private/SoftObjectPathCustomization.h` (Private)


#### class `FSoftObjectPathCustomization`  
`class FSoftObjectPathCustomization : public IPropertyTypeCustomization`  
_L13-28_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes a soft object path to look like a UObject property
- L16 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L22 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L23 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L27 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle to the struct property being customized

### `Source/Editor/DetailCustomizations/Private/SoundBaseDetailsUtils.h` (Private)


#### class `FSoundBaseDetailsUtils`  
`class FSoundBaseDetailsUtils`  
_L7-12_
- L10 _public prototype_ `static void SortSoundCategories(const TMap<FName, IDetailCategoryBuilder*>& AllCategoryMap);`
- L11 _public prototype_ `static void SortSoundCategories(const TMap<FName, IDetailCategoryBuilder*>& AllCategoryMap, const TArray<FName> CategoryOrder);`

### `Source/Editor/DetailCustomizations/Private/SoundCueDetails.h` (Private)


#### class `FSoundCueDetails`  
`class FSoundCueDetails : public IDetailCustomization`  
_L10-20_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L18 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — Makes a new instance of this detail layout class for a specific detail view requesting it static TSharedRef<IDetailCustomization> MakeInstance(); private: ~ Begin IDetailCustomization interface

### `Source/Editor/DetailCustomizations/Private/SoundSourceBusDetails.h` (Private)


#### class `FSoundSourceBusDetails`  
`class FSoundSourceBusDetails : public IDetailCustomization`  
_L10-22_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L18 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — Makes a new instance of this detail layout class for a specific detail view requesting it static TSharedRef<IDetailCustomization> MakeInstance(); private: ~ Begin IDetailCustomization interface
- L21 _private prototype_ `void CustomizeCurveDetails(IDetailLayoutBuilder& DetailBuilder);`

### `Source/Editor/DetailCustomizations/Private/SoundSubmixSendFilterCustomization.h` (Private)


#### class `FSoundSubmixSendFilterCustomization`  
`class FSoundSubmixSendFilterCustomization : public IPropertyTypeCustomization`  
_L13-22_
- inherits: `IPropertyTypeCustomization`
- desc: Custom LPF/HPF cutoff spinbox with MaxFractionalDigits(1); SSpinBox::Construct clobbers the meta-path value.
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& Utils) override;`
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& Utils) override;`

### `Source/Editor/DetailCustomizations/Private/SoundWaveDetails.h` (Private)


#### class `FSoundWaveDetails`  
`class FSoundWaveDetails : public IDetailCustomization`  
_L14-35_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L24 _private prototype_ `void CustomizeCurveDetails(IDetailLayoutBuilder& DetailBuilder);`
- L26 _private prototype_ `void CustomizeCloudStreamingPlatformDetails(IDetailLayoutBuilder& DetailBuilder);`
- L28 _private prototype_ `EVisibility GetMakeInternalCurvesVisibility(USoundWave* SoundWave, TSharedRef<IPropertyHandle> CurvePropertyHandle) const;`
- L30 _private prototype_ `EVisibility GetUseInternalCurvesVisibility(USoundWave* SoundWave, TSharedRef<IPropertyHandle> CurvePropertyHandle) const;`
- L32 _private prototype_ `FReply HandleMakeInternalCurves(USoundWave* SoundWave);`
- L34 _private prototype_ `FReply HandleUseInternalCurves(USoundWave* SoundWave, TSharedRef<IPropertyHandle> CurvePropertyHandle);`

### `Source/Editor/DetailCustomizations/Private/SourceCodeAccessSettingsDetails.h` (Private)


#### struct `FAccessorItem`  
`struct FAccessorItem`  
_L17-30_
- L19 _public function_ `FAccessorItem(const FText& InText, const FName& InName) : Text(InText) , Name(InName)`
- L26 _public member_ `FText Text;` — Text to display
- L29 _public member_ `FName Name;` — Name of the accessor

#### class `FSourceCodeAccessSettingsDetails`  
`class FSourceCodeAccessSettingsDetails : public IDetailCustomization`  
_L32-54_
- inherits: `IDetailCustomization`
- L36 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L39 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L43 _private prototype_ `TSharedRef<SWidget> OnGenerateWidget( TSharedPtr<FAccessorItem> InItem );` — Generate a row widget for display in the list view
- L46 _private prototype_ `void OnSelectionChanged(TSharedPtr<FAccessorItem> InItem, ESelectInfo::Type InSeletionInfo, TSharedRef<IPropertyHandle> PreferredProviderPropertyHandle);` — Set the accessor when we change selection
- L49 _private prototype_ `FText GetAccessorText() const;` — Get the text to display on the accessor drop-down
- L53 _private member_ `TArray<TSharedPtr<FAccessorItem>> Accessors;` — Accessor names to display in a drop-down list

### `Source/Editor/DetailCustomizations/Private/SplineComponentDetails.h` (Private)


#### class `FSplineComponentDetails`  
`class FSplineComponentDetails : public IDetailCustomization`  
_L10-18_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Source/Editor/DetailCustomizations/Private/StaticMeshActorDetails.h` (Private)


#### class `FStaticMeshActorDetails`  
`class FStaticMeshActorDetails : public IDetailCustomization`  
_L10-18_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface

### `Source/Editor/DetailCustomizations/Private/StaticMeshComponentDetails.h` (Private)


#### class `FStaticMeshComponentDetails`  
`class FStaticMeshComponentDetails : public IDetailCustomization`  
_L17-40_
- inherits: `IDetailCustomization`
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L24 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L30 _private prototype_ `int HandleNoticeSwitcherWidgetIndex() const;` — @return Which UI to show whether or not override lightmap res is enabled
- L35 _private prototype_ `TOptional<int32> GetStaticMeshLightResValue() const;` — @return Accessor for the static mesh's light resolution value.
- L37 _private member_ `TArray<TWeakObjectPtr<UObject>> ObjectsCustomized;`
- L38 _private member_ `TSharedPtr<IPropertyHandle> OverrideLightResProperty;`
- L39 _private member_ `TSharedPtr<IPropertyHandle> StaticMeshProperty;`

### `Source/Editor/DetailCustomizations/Private/StereoLayerComponentCustomization.h` (Private)


#### class `FStereoLayerComponentCustomization`  
`class FStereoLayerComponentCustomization : public IDetailCustomization`  
_L11-24_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L21 _private prototype_ `[[nodiscard]] bool ShouldEnableDepthSupport() const;`
- L23 _private member_ `TWeakObjectPtr<const UStereoLayerComponent> WeakComponent;`

### `Source/Editor/DetailCustomizations/Private/SubScriptStructOfCustomization.h` (Private)


#### class `FSubScriptStructOfCustomization`  
`class FSubScriptStructOfCustomization : public IPropertyTypeCustomization`  
_L17-37_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes a SubScriptStructOf reference to look like a UScriptStruct* property
- L20 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L31 _private prototype_ `const UScriptStruct* HandleGetScriptStruct() const;` — @return The struct currently set on this reference
- L33 _private prototype_ `void HandleSetScriptStruct(const UScriptStruct* newStruct);` — Set the struct used by this reference
- L36 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Handle to the property being customized

### `Source/Editor/DetailCustomizations/Private/TemplateStringStructCustomization.h` (Private)


#### class `FTemplateStringStructCustomization`  
`class FTemplateStringStructCustomization : public IPropertyTypeCustomization`  
_L16-65_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details view customization for the FTemplateString structure.
- L25 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance( )` — Creates an instance of this class. @return The new instance.
- L31 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L32 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L36 _private prototype_ `FText GetText() const;` — Get the property string value (as FText).
- L39 _private prototype_ `FText GetResolvedText() const;` — Get the property string value (as FText).
- L42 _private prototype_ `void SetText(const FText& InNewText) const;` — Set the property string value (from FText).
- L45 _private prototype_ `FText GetToolTip() const;` — Get/Create tooltip, with list of valid arguments.
- L48 _private prototype_ `const TArray<FString>& GetValidArguments() const;` — Get the list of valid arguments.
- L51 _private prototype_ `void OnResetToDefault();` — Custom behavior that clears both the Template and Resolved strings.
- L55 _private member_ `TSharedPtr<IPropertyHandle> TemplateStringProperty;` — Pointer to the string that will be set when changing the path.
- L58 _private member_ `TSharedPtr<IPropertyHandle> ResolvedStringProperty;` — Pointer to the stored result of the template string after it's resolved and all args are replaced.
- L61 _private member_ `mutable FText CachedTooltip;` — Cached tooltip, created by GetToolTip().
- L64 _private member_ `mutable TArray<FString> ValidArguments;` — Store the valid arguments for this property.

### `Source/Editor/DetailCustomizations/Private/TextCustomization.h` (Private)


#### class `FTextCustomization`  
`class FTextCustomization : public IPropertyTypeCustomization`  
_L7-18_
- inherits: `IPropertyTypeCustomization`
- L10 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L16 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> InPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L17 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> InPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils ) override;`

### `Source/Editor/DetailCustomizations/Private/TextureCubeArrayDetails.h` (Private)


#### class `FTextureCubeArrayDetails`  
`class FTextureCubeArrayDetails : public IDetailCustomization`  
_L15-36_
- inherits: `IDetailCustomization`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L24 _private prototype_ `bool ShouldFilterCubeAsset(const FAssetData& AssetData, int32 ElementIndex) const;` — Filter for array element asset pickers - blocks cubemaps that don't match the first entry's size/format.
- L27 _private prototype_ `void OnGenerateArrayElementWidget(TSharedRef<IPropertyHandle> ElementHandle, int32 ElementIndex, IDetailChildrenBuilder& ChildrenBuilder);` — Generates custom widget per array element with the filtered asset picker.
- L30 _private prototype_ `FText GetErrorText() const;` — Dynamic error text describing which textures mismatch.
- L33 _private prototype_ `EVisibility GetErrorVisibility() const;` — Visible only when there's a size/format mismatch in the array.
- L35 _private member_ `TWeakObjectPtr<UTextureCubeArray> TextureCubeArrayPtr;`

### `Source/Editor/DetailCustomizations/Private/TextureLODSettingsDetails.h` (Private)


#### class `FTextureLODGroupLayout`  
`class FTextureLODGroupLayout : public IDetailCustomNodeBuilder, public TSharedFromThis < FTextureLODGroupLayout >`  
_L28-103_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FTextureLODGroupLayout>`
- desc: Texture Group layout for property editor views.
- L31 _public prototype_ `FTextureLODGroupLayout(const class UDeviceProfile* InDeviceProfile, TextureGroup GroupId);`
- L32 _public prototype_ `virtual ~FTextureLODGroupLayout();`
- L35 _private function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override` — Begin IDetailCustomNodeBuilder Interface
- L36 _private prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L37 _private prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L38 _private function_ `virtual void Tick(float DeltaTime) override`
- L39 _private function_ `virtual bool RequiresTick() const override`
- L40 _private function_ `virtual FName GetName() const override`
- L41 _private function_ `virtual bool InitiallyCollapsed() const override`
- L47 _private prototype_ `uint32 GetMinLODSize() const;` — Controls for the Min LOD Size property editing
- L48 _private prototype_ `void OnMinLODSizeChanged(uint32 NewValue);`
- L49 _private prototype_ `void OnMinLODSizeCommitted(uint32 NewValue, ETextCommit::Type TextCommitType);`
- L52 _private prototype_ `uint32 GetMaxLODSize() const;` — Controls for the Max LOD Size property editing
- L53 _private prototype_ `void OnMaxLODSizeChanged(uint32 NewValue);`
- L54 _private prototype_ `void OnMaxLODSizeCommitted(uint32 NewValue, ETextCommit::Type TextCommitType);`
- L57 _private prototype_ `uint32 GetMaxLODSizeVT() const;` — Controls for the Max LOD Size VT property editing
- L58 _private prototype_ `void OnMaxLODSizeVTChanged(uint32 NewValue);`
- L59 _private prototype_ `void OnMaxLODSizeVTCommitted(uint32 NewValue, ETextCommit::Type TextCommitType);`
- L62 _private prototype_ `int32 GetLODBias() const;` — Controls for the LOD Bias property editing
- L63 _private prototype_ `void OnLODBiasChanged(int32 NewValue);`
- L64 _private prototype_ `void OnLODBiasCommitted(int32 NewValue, ETextCommit::Type TextCommitType);`
- L67 _private prototype_ `int32 GetLODBiasVT() const;` — Controls for the LOD Bias VT property editing
- L68 _private prototype_ `void OnLODBiasVTChanged(int32 NewValue);`
- L69 _private prototype_ `void OnLODBiasVTCommitted(int32 NewValue, ETextCommit::Type TextCommitType);`
- L72 _private prototype_ `TSharedRef<SWidget> MakeMinMagFilterComboWidget(TSharedPtr<FName> InItem);` — Controls for the MinMag Filter property editing
- L73 _private prototype_ `void OnMinMagFilterChanged(TSharedPtr<FName> NewSelection, ESelectInfo::Type SelectInfo);`
- L74 _private prototype_ `FText GetMinMagFilterComboBoxContent() const;`
- L75 _private prototype_ `FText GetMinMagFilterComboBoxToolTip() const;`
- L78 _private prototype_ `TSharedRef<SWidget> MakeMipFilterComboWidget(TSharedPtr<FName> InItem);` — Controls for the Mip Filter property editing
- L79 _private prototype_ `void OnMipFilterChanged(TSharedPtr<FName> NewSelection, ESelectInfo::Type SelectInfo);`
- L80 _private prototype_ `FText GetMipFilterComboBoxContent() const;`
- L81 _private prototype_ `FText GetMipFilterComboBoxToolTip() const;`
- L84 _private prototype_ `TSharedRef<SWidget> MakeMipGenSettingsComboWidget(TSharedPtr<TextureMipGenSettings> InItem);` — Controls for the MipGenSettings property editing
- L85 _private prototype_ `void OnMipGenSettingsChanged(TSharedPtr<TextureMipGenSettings> NewSelection, ESelectInfo::Type SelectInfo);`
- L86 _private prototype_ `FText GetMipGenSettingsComboBoxContent() const;`
- L87 _private prototype_ `FText GetMipGenSettingsComboBoxToolTip() const;`
- L91 _private member_ `FTextureLODGroup* LodGroup;` — The LOD group we are creating an editor for.
- L94 _private member_ `TArray<TSharedPtr<FName>> FilterComboList;` — The available filter names for the MinMag and Mip Filter selection
- L99 _private prototype_ `void AddToAvailableMipGenSettings(TextureMipGenSettings MipGenSettingsId);` — Populate the Mip Gen Settings Combo Options
- L102 _private member_ `TArray<TSharedPtr<TextureMipGenSettings>> MipGenSettingsComboList;` — The available MipGenSettingsavailable for selection

#### class `FDeviceProfileTextureLODSettingsDetails`  
`class FDeviceProfileTextureLODSettingsDetails : public TSharedFromThis<FDeviceProfileTextureLODSettingsDetails>`  
_L108-152_
- inherits: `TSharedFromThis<FDeviceProfileTextureLODSettingsDetails>`
- desc: Details panel for Texture LOD Settings
- L119 _public prototype_ `FDeviceProfileTextureLODSettingsDetails(IDetailLayoutBuilder* InDetailBuilder);` — Constructor for the parent property details view @param InDetailsBuilder Where we are adding our property view to
- L125 _public prototype_ `void CreateTextureLODSettingsPropertyView();` — Create the parent property view for the device profile
- L130 _public prototype_ `void CreateTextureGroupEntryRow(int32 GroupId, IDetailCategoryBuilder& DetailGroup);` — Create an editor for the provided LOD Group
- L137 _private prototype_ `void OnTextureLODSettingsPropertyChanged();` — Delegate used when the device profiles parent is updated from any source.
- L142 _private member_ `IDetailLayoutBuilder* DetailBuilder;` — A handle to the detail view builder
- L145 _private member_ `TSharedPtr<IPropertyHandle> TextureLODSettingsPropertyNameHandle;` — Access to the Parent Property
- L148 _private member_ `TSharedPtr<IPropertyHandleArray> LODGroupsArrayHandle;` — Access to the LOD Groups array
- L151 _private member_ `class UDeviceProfile* DeviceProfile;` — A reference to the object we are showing these properties for

### `Source/Editor/DetailCustomizations/Private/TimecodeDetailsCustomization.h` (Private)


#### class `FTimecodeDetailsCustomization`  
`class FTimecodeDetailsCustomization : public IPropertyTypeCustomization`  
_L17-39_
- inherits: `IPropertyTypeCustomization`
- desc: Customize the FTimecode.
- L20 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L25 _public function_ `FTimecodeDetailsCustomization()`
- L30 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override` — IPropertyTypeCustomization interface
- L31 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L34 _private prototype_ `FText OnGetTimecodeText() const;`
- L35 _private prototype_ `void OnTimecodeTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);`
- L38 _private member_ `TSharedPtr<IPropertyHandle> TimecodeProperty;` — Store the property handle to the Timecode field so we can get/set the value on the object via text box callbacks.

### `Source/Editor/DetailCustomizations/Private/TimespanStructCustomization.h` (Private)


#### class `FTimespanStructCustomization`  
`class FTimespanStructCustomization : public IPropertyTypeCustomization`  
_L17-63_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details view customization for the FTimespan structure.
- L27 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()` — Creates an instance of this class. @return The new instance.
- L36 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L37 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L42 _private prototype_ `FSlateColor HandleTextBoxForegroundColor() const;` — Handles getting the text color of the editable text box.
- L45 _private prototype_ `FText HandleTextBoxText() const;` — Handles getting the text to be displayed in the editable text box.
- L48 _private prototype_ `void HandleTextBoxTextChanged(const FText& NewText);` — Handles changing the value in the editable text box.
- L51 _private prototype_ `void HandleTextBoxTextCommited(const FText& NewText, ETextCommit::Type CommitInfo);` — Handles committing the text in the editable text box.
- L56 _private member_ `bool InputValid;` — Holds a flag indicating whether the current input is a valid GUID.
- L59 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Holds a handle to the property being edited.
- L62 _private member_ `TSharedPtr<SEditableTextBox> TextBox;` — Holds the text box for editing the Guid.

### `Source/Editor/DetailCustomizations/Private/Vector4StructCustomization.h` (Private)


#### class `FVector4StructCustomization`  
`class FVector4StructCustomization : public FMathStructCustomization`  
_L19-39_
- inherits: `FMathStructCustomization`
- desc: Customizes FVector4 structs. We override Vector4 because the color grading controls are made with vector4
- L23 _public prototype_ `FVector4StructCustomization();`
- L24 _public prototype_ `~FVector4StructCustomization();`
- L26 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — @return A new instance of this class
- L31 _public prototype_ `virtual void MakeHeaderRow(TSharedRef<IPropertyHandle>& StructPropertyHandle, FDetailWidgetRow& Row) override;`
- L32 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L36 _private prototype_ `TSharedPtr<FColorGradingVectorCustomization> GetOrCreateColorGradingVectorCustomization(TSharedRef<IPropertyHandle>& StructPropertyHandle);` — We specialize the detail display of color grading vector property. The color grading mode is specified inside the metadata of the FProperty
- L38 _private member_ `TSharedPtr<FColorGradingVectorCustomization> ColorGradingVectorCustomization;`

### `Source/Editor/DetailCustomizations/Private/WindowsTargetSettingsDetails.h` (Private)


#### class `FWindowsTargetSettingsDetails`  
`class FWindowsTargetSettingsDetails : public IDetailCustomization`  
_L20-52_
- inherits: `IDetailCustomization`
- desc: Manages the Transform section of a details view
- L24 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L27 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L31 _private prototype_ `bool HandlePreExternalIconCopy(const FString& InChosenImage);` — Delegate handler for before an icon is copied
- L34 _private prototype_ `FString GetPickerPath();` — Delegate handler to get the path to start picking from
- L37 _private prototype_ `bool HandlePostExternalIconCopy(const FString& InChosenImage);` — Delegate handler to set the path to start picking from
- L40 _private prototype_ `void HandleAudioStreamCachingToggled(ECheckBoxState bEnableStreamCaching, TSharedPtr<IPropertyHandle> PropertyHandle);` — Handles when Stream Caching is toggled.
- L43 _private prototype_ `ECheckBoxState GetAudioStreamCachingToggled(TSharedPtr<IPropertyHandle> PropertyHandle) const;` — This gets the current value of the audio stream caching bool property.
- L47 _private member_ `TSharedPtr<FShaderFormatsPropertyDetails> D3D12TargetShaderFormatsDetails;` — Reference to the target shader formats property view
- L48 _private member_ `TSharedPtr<FShaderFormatsPropertyDetails> D3D11TargetShaderFormatsDetails;`
- L49 _private member_ `TSharedPtr<FShaderFormatsPropertyDetails> VulkanTargetShaderFormatsDetails;`
- L51 _private member_ `FAudioPluginWidgetManager AudioPluginWidgetManager;`

### `Source/Editor/DetailCustomizations/Private/WorldSettingsDetails.h` (Private)


#### class `FWorldSettingsDetails`  
`class FWorldSettingsDetails : public IDetailCustomization`  
_L35-114_
- inherits: `IDetailCustomization`
- desc: Implements details panel customizations for AWorldSettings fields.
- L40 _public prototype_ `virtual ~FWorldSettingsDetails();`
- L44 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;`
- L53 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance( )` — Makes a new instance of this detail layout class. @return The created instance.
- L67 _protected prototype_ `void CustomizeGameInfoProperty( const FName& PropertyName, IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& CategoryBuilder );` — Customizes an AGameInfo property with the given name. @param PropertyName The property to customize. @param DetailBuilder The detail builder. @param CategoryBuilder The category builder
- L74 _protected prototype_ `void AddLightmapCustomization( IDetailLayoutBuilder& DetailBuilder );` — Adds the lightmap customization to the Lightmass section @param DetailBuilder The detail builder.
- L80 _protected prototype_ `void AddWorldCustomization(IDetailLayoutBuilder& DetailBuilder);` — Add customization to the World section @param DetailBuilder the detail builder.
- L84 _private prototype_ `bool IsPartitionedWorld(ULevel* Level) const;` — return true if level's owning world is partitioned.
- L87 _private prototype_ `void OnUseExternalActorsChanged(ECheckBoxState State, ULevel* Level);` — Called when `ULevel::bUseExternalActors` changes.
- L90 _private prototype_ `ECheckBoxState IsUseExternalActorsChecked(ULevel* Level) const;` — return the state of `ULevel::bUseExternalActors`.
- L93 _private prototype_ `bool IsUseExternalActorsEnabled(ULevel* Level) const;` — return true if the state of 'ULevel::bUseExternalActors' can be changed.
- L96 _private prototype_ `void OnUseActorFoldersChanged(ECheckBoxState BoxState, ULevel* Level);` — Called when `ULevel::bUseActorFolders` changes.
- L99 _private prototype_ `ECheckBoxState IsUsingActorFoldersChecked(ULevel* Level) const;` — return the state of `ULevel::bUseActorFolders`.
- L102 _private prototype_ `bool IsUsingActorFoldersEnabled(ULevel* Level) const;` — return true if the state of 'ULevel::bUseActorFolders' can be changed.
- L105 _private prototype_ `bool HandleAssetDropTargetIsAssetAcceptableForDrop( const UObject* InObject ) const;` — Handles checking whether a given asset is acceptable for drag-and-drop.
- L108 _private prototype_ `void HandleAssetDropped( UObject* Object, TSharedRef<IPropertyHandle> GameInfoProperty );` — Handles dropping an asset.
- L111 _private member_ `TSharedPtr<FGameModeInfoCustomizer> GameInfoModeCustomizer;` — Helper class to customizer GameMode property
- L113 _private member_ `TWeakObjectPtr<class AWorldSettings> SelectedWorldSettings;`

#### class `FLightmapCustomNodeBuilder`  
`class FLightmapCustomNodeBuilder : public IDetailCustomNodeBuilder, public TSharedFromThis<FLightmapCustomNodeBuilder>`  
_L118-183_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FLightmapCustomNodeBuilder>`
- desc: Custom struct for each group of arguments in the function editing details
- L121 _public prototype_ `FLightmapCustomNodeBuilder(const TSharedPtr<FAssetThumbnailPool>& InThumbnailPool);`
- L122 _public prototype_ `~FLightmapCustomNodeBuilder();`
- L127 _protected prototype_ `virtual void SetOnRebuildChildren( FSimpleDelegate InOnRegenerateChildren ) override;` — IDetailCustomNodeBuilder interface
- L128 _protected prototype_ `virtual void GenerateHeaderRowContent( FDetailWidgetRow& NodeRow ) override;`
- L129 _protected prototype_ `virtual void GenerateChildContent( IDetailChildrenBuilder& ChildrenBuilder ) override;`
- L130 _protected function_ `virtual void Tick( float DeltaTime ) override`
- L131 _protected function_ `virtual bool RequiresTick() const override`
- L132 _protected function_ `virtual FName GetName() const override`
- L133 _protected function_ `virtual bool InitiallyCollapsed() const override`
- L149 _private prototype_ `FText GetLightmapCountText() const;` — Handler for the lightmap count text in the right hand column
- L152 _private prototype_ `void HandleLightingBuildKept();` — Handler for when lighting has been rebuilt and kept
- L155 _private prototype_ `void HandleNewCurrentLevel();` — Handler for when the current level changes
- L158 _private prototype_ `TSharedRef<SWidget> MakeLightMapList(TSharedPtr<FLightmapItem> AssetItem);` — Handler for light map list view widget creation
- L161 _private prototype_ `TSharedPtr<SWidget> OnGetLightMapContextMenuContent(TSharedPtr<FLightmapItem> Lightmap);` — Handler for context menus
- L164 _private prototype_ `FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, TWeakPtr<FLightmapItem> Lightmap);` — Handler for right clicking an item
- L167 _private prototype_ `FReply OnLightMapListMouseButtonDoubleClick(const FGeometry& MyGeom, const FPointerEvent& PointerEvent, TWeakPtr<FLightmapItem> SelectedLightmap);` — Handler for double clicking an item
- L170 _private prototype_ `void ExecuteViewLightmap(FString SelectedLightmapPath);` — Handler for when "View" is selected in the light map list
- L173 _private prototype_ `void RefreshLightmapItems();` — Refreshes the list of lightmaps to display
- L178 _private member_ `FSimpleDelegate OnRegenerateChildren;` — Delegate to handle refreshing this group
- L181 _private member_ `TArray<TSharedPtr<FLightmapItem>> LightmapItems;` — The list view showing light maps in this world
- L182 _private member_ `TSharedPtr<class FAssetThumbnailPool> ThumbnailPool;`

#### struct `FLightmapCustomNodeBuilder::FLightmapItem`  
`struct FLightmapItem`  
_L137-146_
- L139 _public member_ `FString ObjectPath;`
- L140 _public member_ `TSharedPtr<class FAssetThumbnail> Thumbnail;`
- L142 _public function_ `FLightmapItem(const FString& InObjectPath, const TSharedPtr<class FAssetThumbnail>& InThumbnail) : ObjectPath(InObjectPath) , Thumbnail(InThumbnail)`

### `Source/Editor/DetailCustomizations/Public/ActorDetailsDelegates.h` (Public)


#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_DELEGATE_RetVal( const TArray< TWeakObjectPtr<AActor> >&, FGetSelectedActors );` — Delegate that returns a const& to an array of actors this view is inspecting
- L10 _prototype_ `DECLARE_DELEGATE_RetVal( const TArray< TWeakObjectPtr<AActor> >&, FGetSelectedActors );` — Delegate that returns a const& to an array of actors this view is inspecting
- L12 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FExtendActorDetails, class IDetailLayoutBuilder&, const FGetSelectedActors&);`
- L12 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FExtendActorDetails, class IDetailLayoutBuilder&, const FGetSelectedActors&);`
- L15 _externvar_ `extern FExtendActorDetails OnExtendActorDetails;` — Delegate that is invoked to extend the actor details view

### `Source/Editor/DetailCustomizations/Public/Customizations/ColorStructCustomization.h` (Public)


#### class `FColorStructCustomization`  
`class FColorStructCustomization : public FMathStructCustomization`  
_L36-233_
- inherits: `FMathStructCustomization`
- desc: Base class for color struct customization (FColor,FLinearColor).
- L41 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L46 _protected function_ `FColorStructCustomization() : bIsLinearColor(false) , bIgnoreAlpha(false) , bIsInlineColorPickerVisible(false) , bIsInteractive(false) , bIsInBlueprint(false) , bDontUpdateWhileEditing(false)`
- L65 _protected prototype_ `virtual FPropertyAccess::Result GetColorAsLinear(FLinearColor& InColor) const;` — Get the color used by this struct as a linear color value @param InColor To be filled with the color value used by this struct, or white if this struct is being used to edit multiple values @return The result of trying to get the color value
- L71 _protected function_ `virtual bool TypeSupportsAlpha() const` — Does the type have Alpha Support @return true if it does
- L76 _protected prototype_ `virtual void GatherSavedPreColorPickerColors();` — Stores the colors from the property into SavedPreColorPickerColors
- L81 _protected prototype_ `virtual void SetLastPickerColorString(const FLinearColor NewColor);` — Stores the color as a string in LastPickerColorString
- L88 _protected prototype_ `virtual TArray<FString> ConvertToPerObjectColors(const TArray<FLinearOrSrgbColor>& Colors) const;` — Converts Colors into strings @param Colors Array of colors to convert @return Array of colors converted to string
- L93 _protected prototype_ `TSharedRef<SWidget> CreateColorWidget(TWeakPtr<IPropertyHandle>);` — Creates the color widget that when clicked spawns the color picker window.
- L99 _protected prototype_ `EVisibility GetMultipleValuesTextVisibility() const;` — Does this struct have multiple values? @return EVisibility::Visible if it does, EVisibility::Collapsed otherwise
- L107 _protected prototype_ `void CreateColorPicker(bool bUseAlpha);` — Creates a new color picker for interactively selecting the color @param bUseAlpha If true alpha will be displayed, otherwise it is ignored @param bOnlyRefreshOnOk If true the value of the property will only be refreshed when the user clicks OK in the color picker
- L110 _protected prototype_ `TSharedRef<SColorPicker> CreateInlineColorPicker(TWeakPtr<IPropertyHandle>);` — Creates a new color picker for interactively selecting color
- L117 _protected prototype_ `void OnSetColorFromColorPicker(FLinearColor NewColor);` — Called when the property is set from the color picker @param NewColor The new color value
- L122 _protected prototype_ `void ResetColors();` — Called to reset all colors to before the color picker spawned
- L130 _protected prototype_ `void OnColorPickerCancelled(FLinearColor OriginalColor);` — Called when the user clicks cancel in the color picker The values are reset to their original state when this happens @param OriginalColor Original color of the property
- L135 _protected prototype_ `void OnColorPickerWindowClosed(const TSharedRef<SWindow>& Window);` — Called when the color picker window is clsoed
- L140 _protected prototype_ `void OnColorPickerInteractiveBegin();` — Called when the user enters an interactive color change (dragging something in the picker)
- L145 _protected prototype_ `void OnColorPickerInteractiveEnd();` — Called when the user completes an interactive color change (dragging something in the picker)
- L150 _protected prototype_ `FLinearColor OnGetColorForColorBlock() const;` — @return The color that should be displayed in the color block
- L155 _protected prototype_ `FSlateColor OnGetSlateColorForBlock() const;` — @return The color that should be displayed in the color block in slate color format
- L160 _protected prototype_ `FSlateColor GetColorWidgetBorderColor() const;` — @return The border color encompassing the entire color block
- L164 _protected prototype_ `FReply OnMouseButtonDownColorBlock(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Called when the user clicks in the color block (opens inline color picker)
- L167 _protected prototype_ `FReply OnOpenFullColorPickerClicked();` — Called when the user clicks on the the button to get the full color picker
- L173 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L174 _protected prototype_ `virtual void MakeHeaderRow(TSharedRef<IPropertyHandle>& InStructPropertyHandle, FDetailWidgetRow& Row) override;`
- L175 _protected prototype_ `virtual void GetSortedChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, TArray< TSharedRef<IPropertyHandle> >& OutChildren) override;`
- L197 _protected member_ `TArray<FLinearOrSrgbColor> SavedPreColorPickerColors;` — Saved per struct colors in case the user clicks cancel in the color picker
- L200 _protected member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Color struct handle
- L203 _protected member_ `TSharedPtr<SWidget> ColorPickerParentWidget;` — Cached widget for the color picker to use as a parent
- L205 _protected member_ `TSharedPtr<SWidget > ColorWidgetBackgroundBorder;`
- L208 _protected member_ `TOptional<bool> sRGBOverride;` — Overrides the default state of the sRGB check box
- L211 _protected member_ `bool bIsLinearColor;` — True if the property is a linear color property
- L214 _protected member_ `bool bIgnoreAlpha;` — True if the property wants to ignore the alpha component
- L217 _protected member_ `bool bIsInlineColorPickerVisible;` — True if the inline color picker is visible
- L220 _protected member_ `bool bIsInteractive;` — True if the user is performing an interactive color change
- L223 _protected member_ `bool bIsInBlueprint;` — True if the property we are editing is contained within a blueprint
- L226 _protected member_ `FString LastPickerColorString;` — Last color set from color picker as string
- L230 _protected member_ `bool bDontUpdateWhileEditing;` — The value won;t be updated while editing
- L232 _protected member_ `TOptional<int32> TransactionIndex;`

#### struct `FColorStructCustomization::FLinearOrSrgbColor`  
`struct FLinearOrSrgbColor`  
_L179-194_
- desc: Stores a linear or srb color without converting between the two. Only one is valid at a time
- L181 _public function_ `FLinearOrSrgbColor(const FLinearColor& InLinearColor) : LinearColor(InLinearColor)`
- L185 _public function_ `FLinearOrSrgbColor(const FColor& InSrgbColor) : SrgbColor(InSrgbColor)`
- L189 _public function_ `FLinearColor GetLinear() const`
- L190 _public function_ `FColor GetSrgb() const`
- L192 _private member_ `FLinearColor LinearColor;`
- L193 _private member_ `FColor SrgbColor;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API DETAILCUSTOMIZATIONS_API`

### `Source/Editor/DetailCustomizations/Public/Customizations/CurveTableCustomization.h` (Public)


#### class `FCurveTableCustomizationLayout`  
`class FCurveTableCustomizationLayout : public IPropertyTypeCustomization`  
_L54-286_
- inherits: `IPropertyTypeCustomization`
- desc: Customizes a DataTable asset to use a dropdown
- L57 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L63 _public function_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override` — IPropertyTypeCustomization interface
- L74 _public function_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override`
- L113 _public function_ `virtual void CreateCurveTableChildProperty(IDetailChildrenBuilder& StructBuilder)`
- L121 _protected function_ `TSharedPtr<FString> InitWidgetContent(bool bShouldModifyData)` — Init the contents the combobox sources its data off
- L178 _protected prototype_ `TSharedRef<SWidget> GetListContent();` — Returns the ListView for the ComboButton
- L181 _protected function_ `void OnInitialRefresh()` — Initial refresh, will not modify data
- L192 _protected function_ `void OnCurveTableChanged()` — Delegate to refresh the drop down when the datatable changes
- L203 _protected function_ `TSharedRef<ITableRow> HandleRowNameComboBoxGenarateWidget( TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable )` — Return the representation of the the row names to display
- L213 _protected function_ `FText GetRowNameComboBoxContentText( ) const` — Display the current selection
- L233 _protected function_ `void OnSelectionChanged( TSharedPtr<FString> SelectedItem, ESelectInfo::Type SelectInfo )` — Update the root data on a change of selection
- L247 _protected function_ `void OnFilterTextChanged( const FText& InFilterText )` — Called by Slate when the filter box changes text.
- L277 _protected member_ `TSharedPtr<SComboButton> RowNameComboButton;` — The comboButton objects
- L278 _protected member_ `TSharedPtr<SListView<TSharedPtr<FString> > > RowNameComboListView;`
- L279 _protected member_ `TSharedPtr<FString> CurrentSelectedItem;`
- L281 _protected member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle to the struct properties being customized
- L282 _protected member_ `TSharedPtr<IPropertyHandle> CurveTablePropertyHandle;`
- L283 _protected member_ `TSharedPtr<IPropertyHandle> RowNamePropertyHandle;`
- L285 _protected member_ `TArray<TSharedPtr<FString> > RowNames;` — A cached copy of strings to populate the combo box

#### Free symbols / members of external scopes

- L43 _macro_ `#define UE_API DETAILCUSTOMIZATIONS_API`

### `Source/Editor/DetailCustomizations/Public/Customizations/LinearColorRampCustomization.h` (Public)


#### struct `FLinearColorRampCustomizationArgs`  
`struct FLinearColorRampCustomizationArgs`  
_L8-12_
- desc: Arguments for the linear color ramp customization
- L11 _public member_ `bool bWithAlphaChannel = true;` — When true, the alpha channel is displayed and editable

#### class `FLinearColorRampCustomization`  
`class FLinearColorRampCustomization : public IPropertyTypeCustomization`  
_L14-34_
- inherits: `IPropertyTypeCustomization`
- L17 _public prototype_ `FLinearColorRampCustomization() = default;`
- L18 _public prototype_ `FLinearColorRampCustomization(const FLinearColorRampCustomizationArgs InArgs);`
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L24 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(const FLinearColorRampCustomizationArgs InArgs);` — Makes a new instance of this detail layout class for a specific detail view requesting it, with arguments
- L27 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L28 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> , IDetailChildrenBuilder& , IPropertyTypeCustomizationUtils& ) override`
- L33 _private member_ `const FLinearColorRampCustomizationArgs Args;` — Arguments for this customization

### `Source/Editor/DetailCustomizations/Public/Customizations/MathStructCustomizations.h` (Public)


#### class `FMathStructCustomization`  
`class FMathStructCustomization : public IPropertyTypeCustomization`  
_L30-217_
- inherits: `IPropertyTypeCustomization`
- desc: Base class for math struct customization (e.g, vector, rotator, color)
- L34 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L37 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnNumericEntryBoxDynamicSliderMinMaxValueChanged, float, TWeakPtr<SWidget>, bool, bool);` — Notification when the max/min slider values are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L39 _public function_ `FMathStructCustomization() : bIsUsingSlider(false) , bPreserveScaleRatio(false)`
- L44 _public prototype_ `virtual ~FMathStructCustomization() = default;`
- L47 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization instance
- L48 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L51 _public function_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged& GetOnNumericEntryBoxDynamicSliderMaxValueChangedDelegate()` — Return max/min slider value changed delegate (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L52 _public function_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged& GetOnNumericEntryBoxDynamicSliderMinValueChangedDelegate()`
- L56 _public prototype_ `template <typename NumericType> void OnDynamicSliderMaxValueChanged(NumericType NewMaxSliderValue, TWeakPtr<SWidget> InValueChangedSourceWidget, bool IsOriginator, bool UpdateOnlyIfHigher);` — Callback when the max/min spinner value are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)
- L59 _public prototype_ `template <typename NumericType> void OnDynamicSliderMinValueChanged(NumericType NewMinSliderValue, TWeakPtr<SWidget> InValueChangedSourceWidget, bool IsOriginator, bool UpdateOnlyIfLower);`
- L66 _public prototype_ `bool IsValueEnabled(TWeakPtr<IPropertyHandle> WeakHandlePtr) const;` — Called to see if the value is enabled for editing @param WeakHandlePtr	Handle to the property that the new value is for
- L89 _public prototype_ `template <typename NumericType> static void ExtractNumericMetadata(TSharedRef<IPropertyHandle>& PropertyHandle, FNumericMetadata<NumericType>& MetadataOut);` — Utility function that will extract common Math related numeric metadata
- L93 _public prototype_ `static void ExtractNumericMetadata(TSharedRef<IPropertyHandle>& PropertyHandle, TOptional<NumericType>& MinValue, TOptional<NumericType>& MaxValue, TOptional<NumericType>& SliderMinValue, TOptional<NumericType>& SliderMaxValue, NumericType& SliderExponent, NumericType& Delta, int32& ShiftMouseMovePixelPerDelta, bool& bSupportDynamicSliderMaxValue, bool& bSupportDynamicSliderMinValue);` — `UE_DEPRECATED(5.0, "Use ExtractNumericMetadata overload with struct argument instead.")`
- L106 _protected prototype_ `virtual void MakeHeaderRow(TSharedRef<IPropertyHandle>& StructPropertyHandle, FDetailWidgetRow& Row);` — Makes the header row for the customization @param StructPropertyHandle	Handle to the struct property @param Row	The header row to add widgets to
- L114 _protected prototype_ `virtual void GetSortedChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, TArray< TSharedRef<IPropertyHandle> >& OutChildren);` — Gets the sorted children for the struct @param StructPropertyHandle	The handle to the struct property @param OutChildren			The child array that should be populated in the order that children should be displayed
- L122 _protected prototype_ `virtual TSharedRef<SWidget> MakeChildWidget( TSharedRef<IPropertyHandle>& StructurePropertyHandle, TSharedRef<IPropertyHandle>& PropertyHandle);` — Constructs a widget for the property handle @param StructurePropertyHandle	handle of the struct property @param PropertyHandle	Child handle of the struct property
- L133 _protected prototype_ `template<typename NumericType> TOptional<NumericType> OnGetValue(TWeakPtr<IPropertyHandle> WeakHandlePtr) const;` — Gets the value as a float for the provided property handle @param WeakHandlePtr	Handle to the property to get the value from @return The value or unset if it could not be accessed
- L143 _protected prototype_ `template<typename NumericType> void OnValueCommitted(NumericType NewValue, ETextCommit::Type CommitType, TWeakPtr<IPropertyHandle> WeakHandlePtr);` — Called when the value is committed from the property editor @param NewValue		The new value of the property as a float @param CommitType	How the value was committed (unused) @param WeakHandlePtr	Handle to the property that the new value is for
- L153 _protected prototype_ `template<typename NumericType> void OnValueChanged(NumericType NewValue, TWeakPtr<IPropertyHandle> WeakHandlePtr);` — Called when the value is changed in the property editor @param NewValue		The new value of the property as a float @param WeakHandlePtr	Handle to the property that the new value is for
- L163 _protected prototype_ `template<typename NumericType> void SetValue(NumericType NewValue, EPropertyValueSetFlags::Type Flags, TWeakPtr<IPropertyHandle> WeakHandlePtr);` — Called to set the value of the property handle. @param NewValue		The new value of the property as a float @param Flags         The flags to pass when setting the value on the property handle. @param WeakHandlePtr	Handle to the property that the new value is for
- L172 _protected prototype_ `FText OnGetValueToolTip(TWeakPtr<IPropertyHandle> WeakHandlePtr) const;` — `UE_DEPRECATED(5.6, "OnGetValueToolTip is deprecated and no longer called.")`
- L176 _private prototype_ `TOptional<FTextFormat> OnGetValueToolTipTextFormat(TWeakPtr<IPropertyHandle> WeakHandlePtr) const;`
- L179 _private prototype_ `const FSlateBrush* GetPreserveScaleRatioImage() const;` — Gets the brush to use for the lock icon.
- L182 _private prototype_ `ECheckBoxState IsPreserveScaleRatioChecked() const;` — Gets the checked value of the preserve scale ratio option
- L185 _private prototype_ `void OnPreserveScaleRatioToggled(ECheckBoxState NewState, TWeakPtr<IPropertyHandle> PropertyHandle);` — Called when the user toggles preserve ratio.
- L187 _private prototype_ `FReply OnNormalizeClicked(TWeakPtr<IPropertyHandle> PropertyHandle);`
- L192 _private prototype_ `void OnBeginSliderMovement();` — Called when a value starts to be changed by a slider
- L196 _private prototype_ `template<typename NumericType> void OnEndSliderMovement(NumericType NewValue);` — Called when a value stops being changed by a slider
- L199 _private prototype_ `template<typename NumericType> TSharedRef<SWidget> MakeNumericWidget(TSharedRef<IPropertyHandle>& StructurePropertyHandle, TSharedRef<IPropertyHandle>& PropertyHandle);`
- L203 _protected member_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged OnNumericEntryBoxDynamicSliderMaxValueChanged;`
- L204 _protected member_ `FOnNumericEntryBoxDynamicSliderMinMaxValueChanged OnNumericEntryBoxDynamicSliderMinValueChanged;`
- L207 _protected member_ `TArray< TSharedRef<IPropertyHandle> > SortedChildHandles;` — All the sorted children of the struct that should be displayed
- L210 _protected member_ `TArray<TWeakPtr<SWidget>> NumericEntryBoxWidgetList;` — All created numeric entry box widget for this customization
- L213 _protected member_ `bool bIsUsingSlider;` — True if a value is being changed by dragging a slider
- L216 _protected member_ `bool bPreserveScaleRatio;` — True if the ratio is locked when scaling occurs (uniform scaling)

#### struct `FMathStructCustomization::FNumericMetadata`  
`template <typename NumericType> struct FNumericMetadata`  
_L70-85_
- desc: Argument struct for ExtractNumericMetadata, to make it easier to add new metadata to extract.
- L72 _public member_ `TOptional<NumericType> MinValue;`
- L73 _public member_ `TOptional<NumericType> MaxValue;`
- L74 _public member_ `TOptional<NumericType> SliderMinValue;`
- L75 _public member_ `TOptional<NumericType> SliderMaxValue;`
- L76 _public member_ `TSharedPtr<INumericTypeInterface<NumericType>> TypeInterface;`
- L77 _public member_ `NumericType SliderExponent;`
- L78 _public member_ `NumericType Delta;`
- L79 _public member_ `int32 LinearDeltaSensitivity;`
- L80 _public member_ `float ShiftMultiplier;`
- L81 _public member_ `float CtrlMultiplier;`
- L82 _public member_ `bool bSupportDynamicSliderMaxValue;`
- L83 _public member_ `bool bSupportDynamicSliderMinValue;`
- L84 _public member_ `bool bAllowSpinBox;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API DETAILCUSTOMIZATIONS_API`
- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnNumericEntryBoxDynamicSliderMinMaxValueChanged, float, TWeakPtr<SWidget>, bool, bool);` — Notification when the max/min slider values are changed (only apply if SupportDynamicSliderMaxValue or SupportDynamicSliderMinValue are true)

### `Source/Editor/DetailCustomizations/Public/Customizations/MathStructProxyCustomizations.h` (Public)


#### class `TProxyValue`  
`template< typename ObjectType > class TProxyValue`  
_L40-106_
- desc: Helper class used to track the dirty state of a proxy value
- L43 _public function_ `TProxyValue() : Value() , bIsSet(false)`
- L49 _public function_ `TProxyValue(const ObjectType& InValue) : Value(InValue) , bIsSet(false)`
- L59 _public function_ `void Set(const ObjectType& InValue)` — Set the wrapped value @param	InValue	The value to set.
- L69 _public function_ `const ObjectType& Get() const` — Get the wrapped value @return the wrapped value
- L78 _public function_ `ObjectType& Get()` — Get the wrapped value @return the wrapped value
- L87 _public function_ `bool IsSet() const` — Check to see if the value is set. @return whether the value is set.
- L95 _public function_ `void MarkAsSet()` — Mark the value as if it was set.
- L102 _private member_ `ObjectType Value;` — The value we are tracking
- L105 _private member_ `bool bIsSet;` — Whether the value is set

#### class `TProxyProperty`  
`template< typename ObjectType, typename PropertyType > class TProxyProperty`  
_L112-160_
- desc: Helper class used to track the state of properties of proxy values.
- L115 _public function_ `TProxyProperty(const TSharedRef< TProxyValue<ObjectType> >& InValue, PropertyType& InPropertyValue) : Value(InValue) , Property(InPropertyValue) , bIsSet(false)`
- L126 _public function_ `void Set(const PropertyType& InPropertyValue)` — Set the value of this property @param	InPropertyValue		The value of the property to set
- L137 _public function_ `const PropertyType& Get() const` — Get the value of this property @return The value of the property
- L146 _public function_ `bool IsSet() const` — Check to see if the value is set. @return whether the value is set.
- L153 _private member_ `TSharedRef< TProxyValue<ObjectType> > Value;` — The proxy value we are tracking
- L156 _private member_ `PropertyType& Property;` — The property of the value we are tracking
- L159 _private member_ `bool bIsSet;` — Whether the value is set

#### class `FMathStructProxyCustomization`  
`class FMathStructProxyCustomization : public FMathStructCustomization`  
_L166-249_
- inherits: `FMathStructCustomization`
- desc: Helper class to aid representing math structs to the user in an editable form e.g. representing a quaternion as a set of euler angles
- L170 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L173 _public prototype_ `virtual void MakeHeaderRow( TSharedRef<class IPropertyHandle>& InStructPropertyHandle, FDetailWidgetRow& Row ) override;` — FMathStructCustomization interface
- L182 _protected prototype_ `virtual bool CacheValues( TWeakPtr<IPropertyHandle> WeakHandlePtr ) const = 0;` — Cache the values from the property to the proxy. @param	WeakHandlePtr	The property handle to get values from. @return true if values(s) were successfully cached
- L189 _protected prototype_ `virtual bool FlushValues( TWeakPtr<IPropertyHandle> WeakHandlePtr ) const = 0;` — Flush the values from the proxy to the property. @param	WeakHandlePtr	The property handle to set values to. @return true if values(s) were successfully flushed
- L200 _protected prototype_ `template<typename ProxyType, typename NumericType> TSharedRef<SWidget> MakeNumericProxyWidget(TSharedRef<IPropertyHandle>& StructPropertyHandle, TSharedRef< TProxyProperty<ProxyType, NumericType> >& ProxyValue, const FText& Label, bool bRotationInDegrees = false, const FLinearColor& LabelColor = FCoreStyle::Get().GetColor("Defa` — Helper function to make a numeric property widget to edit a proxy value. @param	StructPropertyHandle	Property handle to the containing struct @param	ProxyValue				The value we will be editing in the proxy data. @param	Label					A label to use for this value. @param	bRotationInDegrees		Whether this is to be used for a rotation value (configures sliders appropriately). @return the newly created widget.
- L204 _protected prototype_ `FText OnGetValueToolTip(TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef<TProxyProperty<ProxyType, NumericType>> ProxyValue, FText Label) const;` — `UE_DEPRECATED(5.6, "OnGetValueToolTip is deprecated and no longer called. Please use the Label in MakeNumericProxyWidget to customize the display name portion of the ToolTip.")`
- L206 _protected prototype_ `TOptional<FTextFormat> OnGetValueToolTipTextFormat(FText Label) const;`
- L218 _private prototype_ `template<typename ProxyType, typename NumericType> TOptional<NumericType> OnGetValue( TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue ) const;` — Gets the value as a float for the provided property handle @param WeakHandlePtr	Handle to the property to get the value from @param ProxyValue	Proxy value to get value from. @return The value or unset if it could not be accessed
- L228 _private prototype_ `template<typename ProxyType, typename NumericType> void OnValueCommitted( NumericType NewValue, ETextCommit::Type CommitType, TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue );` — Called when the value is committed from the property editor @param NewValue		The new value of the property as a float @param CommitType	How the value was committed (unused) @param WeakHandlePtr	Handle to the property that the new value is for
- L237 _private prototype_ `template<typename ProxyType, typename NumericType> void OnValueChanged( NumericType NewValue, TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue );` — Called when the value is changed in the property editor @param NewValue		The new value of the property as a float @param WeakHandlePtr	Handle to the property that the new value is for
- L240 _private prototype_ `void OnBeginSliderMovement();` — Called when a value starts to be changed by a slider
- L244 _private prototype_ `template<typename ProxyType, typename NumericType> void OnEndSliderMovement( NumericType NewValue, TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue );` — Called when a value stops being changed by a slider
- L248 _protected member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Cached property utilities
- L252 _function_ `template<typename ProxyType, typename NumericType> inline TSharedRef<SWidget> FMathStructProxyCustomization::MakeNumericProxyWidget( TSharedRef<IPropertyHandle>& StructPropertyHandle, TSharedRef< TProxyProperty<ProxyType, NumericType> >& ProxyValue, const FText& Label, bool bRotationInDegrees, const FLinearColor& LabelBackgroundColor)`
- L294 _function_ `template<typename ProxyType, typename NumericType> inline void FMathStructProxyCustomization::OnEndSliderMovement( NumericType NewValue, TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue )`
- L303 _function_ `template<typename ProxyType, typename NumericType> inline TOptional<NumericType> FMathStructProxyCustomization::OnGetValue( TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue ) const`
- L313 _function_ `template<typename ProxyType, typename NumericType> inline void FMathStructProxyCustomization::OnValueCommitted( NumericType NewValue, ETextCommit::Type CommitType, TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue )`
- L323 _function_ `template<typename ProxyType, typename NumericType> inline void FMathStructProxyCustomization::OnValueChanged( NumericType NewValue, TWeakPtr<IPropertyHandle> WeakHandlePtr, TSharedRef< TProxyProperty<ProxyType, NumericType> > ProxyValue )`

#### struct `FTransformField`  
`struct FTransformField`  
_L332-340_

#### enum `FTransformField::Type`  
`enum Type`  
_L334-339_
- L336 _public enumerator_ `Location`
- L337 _public enumerator_ `Rotation`
- L338 _public enumerator_ `Scale`

#### class `FMatrixStructCustomization`  
`template<typename T> class FMatrixStructCustomization : public FMathStructProxyCustomization`  
_L346-423_
- inherits: `FMathStructProxyCustomization`
- desc: Proxy struct customization that displays a matrix as a position, rotation & scale.
- L349 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L352 _public function_ `FMatrixStructCustomization() : CachedRotation(MakeShareable( new TProxyValue<UE::Math::TRotator<T>>(UE::Math::TRotator<T>::ZeroRotator))) , CachedRotationYaw(MakeShareable( new TProxyProperty<UE::Math::TRotator<T>, T>(CachedRotation, CachedRotation->Get().Yaw))) , CachedRotationPitch(MakeShareable( new TProxyProperty<UE::Math::TRotator<T>, T>(CachedRotation, CachedRotation->Get().Pitch))) , CachedRotationRoll(MakeShareable( new TProxyProperty<UE::Math::TRotator<T>, T>(CachedRotation, CachedRotation->Get().Roll))) , CachedTranslation(MakeShareable( new TProxyValue<UE::Math::TVector<T>>(UE::Math::TVector<T>::ZeroVector))) , CachedTranslationX(MakeShareable( new TProxyProperty<UE::Math::TVector<T>, T>(CachedTranslation, CachedTranslation->Get().X))) , CachedTranslationY(MakeShareable( new TProxyProperty<UE::Math::TVector<T>, T>(CachedTranslation, CachedTranslation->Get().Y))) , CachedTranslationZ(MakeShareable( new TProxyProperty<UE::Math::TVector<T>, T>(CachedTranslation, CachedTranslation->Get().Z))) , CachedScale(MakeShareable( new TProxyValue<UE::Math::TVector<T>>(UE::Math::TVector<T>::ZeroVector))) , CachedScaleX(MakeShareable( new TProxyProperty<UE::Math::TVector<T>, T>(CachedScale, CachedScale->Get().X))) , CachedScaleY(MakeShareable( new TProxyProperty<UE::Math::TVector<T>, T>(CachedScale, CachedScale->Get().Y))) , CachedScaleZ(MakeShareable( new TProxyProperty<UE::Math::TVector<T>, T>(CachedScale, CachedScale->Get().Z))) , bUseLeftUpForwardAxisDisplayCoordinateSystem( f ...`
- L370 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L374 _protected prototype_ `void CustomizeLocation(TSharedRef<class IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& Row);` — Customization utility functions
- L375 _protected prototype_ `void CustomizeRotation(TSharedRef<class IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& Row, TOptional<FText> OverrideName = TOptional<FText>{});`
- L376 _protected prototype_ `void CustomizeScale(TSharedRef<class IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& Row);`
- L379 _protected prototype_ `virtual void MakeHeaderRow(TSharedRef<class IPropertyHandle>& InStructPropertyHandle, FDetailWidgetRow& Row) override;` — FMathStructCustomization interface
- L382 _protected prototype_ `virtual bool CacheValues(TWeakPtr<IPropertyHandle> PropertyHandlePtr) const override;` — FMathStructProxyCustomization interface
- L383 _protected prototype_ `virtual bool FlushValues(TWeakPtr<IPropertyHandle> PropertyHandlePtr) const override;`
- L384 _protected prototype_ `virtual FIntVector4 GetSwizzle() const;`
- L386 _protected prototype_ `void OnCopy(FTransformField::Type Type, TWeakPtr<IPropertyHandle> PropertyHandlePtr);`
- L387 _protected prototype_ `void OnPaste(FTransformField::Type Type, TWeakPtr<IPropertyHandle> PropertyHandlePtr);`
- L389 _protected prototype_ `void PasteFromText( const FString& InTag, const FString& InText, FTransformField::Type Type, TWeakPtr<IPropertyHandle> PropertyHandlePtr);`
- L395 _protected prototype_ `void OnPasteFromText( const FString& InTag, const FString& InText, const TOptional<FGuid>& InOperationId, FTransformField::Type Type, TWeakPtr<IPropertyHandle> PropertyHandlePtr);`
- L404 _protected member_ `mutable TSharedRef< TProxyValue<UE::Math::TRotator<T>> > CachedRotation;` — Cached rotation values
- L405 _protected member_ `mutable TSharedRef< TProxyProperty<UE::Math::TRotator<T>, T> > CachedRotationYaw;`
- L406 _protected member_ `mutable TSharedRef< TProxyProperty<UE::Math::TRotator<T>, T> > CachedRotationPitch;`
- L407 _protected member_ `mutable TSharedRef< TProxyProperty<UE::Math::TRotator<T>, T> > CachedRotationRoll;`
- L410 _protected member_ `mutable TSharedRef< TProxyValue<UE::Math::TVector<T>> > CachedTranslation;` — Cached translation values
- L411 _protected member_ `mutable TSharedRef< TProxyProperty<UE::Math::TVector<T>, T > > CachedTranslationX;`
- L412 _protected member_ `mutable TSharedRef< TProxyProperty<UE::Math::TVector<T>, T > > CachedTranslationY;`
- L413 _protected member_ `mutable TSharedRef< TProxyProperty<UE::Math::TVector<T>, T> > CachedTranslationZ;`
- L416 _protected member_ `mutable TSharedRef< TProxyValue<UE::Math::TVector<T>> > CachedScale;` — Cached scale values
- L417 _protected member_ `mutable TSharedRef< TProxyProperty<UE::Math::TVector<T>, T> > CachedScaleX;`
- L418 _protected member_ `mutable TSharedRef< TProxyProperty<UE::Math::TVector<T>, T> > CachedScaleY;`
- L419 _protected member_ `mutable TSharedRef< TProxyProperty<UE::Math::TVector<T>, T> > CachedScaleZ;`
- L422 _protected member_ `bool bUseLeftUpForwardAxisDisplayCoordinateSystem;` — Whether or not this customization is using the LeftUpForward axis display coordinate system

#### class `FTransformStructCustomization`  
`template<typename T> class FTransformStructCustomization : public FMatrixStructCustomization<T>`  
_L429-439_
- inherits: `FMatrixStructCustomization<T>`
- desc: Proxy struct customization that displays an FTransform as a position, euler rotation & scale.
- L432 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L436 _protected prototype_ `virtual bool CacheValues(TWeakPtr<IPropertyHandle> PropertyHandlePtr) const override;` — FMathStructProxyCustomization interface
- L437 _protected prototype_ `virtual bool FlushValues(TWeakPtr<IPropertyHandle> PropertyHandlePtr) const override;`
- L438 _protected prototype_ `virtual FIntVector4 GetSwizzle() const override;`

#### class `FQuatStructCustomization`  
`template<typename T> class FQuatStructCustomization : public FMatrixStructCustomization<T>`  
_L445-460_
- inherits: `FMatrixStructCustomization<T>`
- desc: Proxy struct customization that displays an FQuat as an euler rotation
- L448 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L451 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L454 _public prototype_ `virtual void MakeHeaderRow(TSharedRef<class IPropertyHandle>& InStructPropertyHandle, FDetailWidgetRow& Row) override;` — FMathStructCustomization interface
- L458 _protected prototype_ `virtual bool CacheValues(TWeakPtr<IPropertyHandle> PropertyHandlePtr) const override;` — FMathStructProxyCustomization interface
- L459 _protected prototype_ `virtual bool FlushValues(TWeakPtr<IPropertyHandle> PropertyHandlePtr) const override;`

#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_API DETAILCUSTOMIZATIONS_API`

### `Source/Editor/DetailCustomizations/Public/Customizations/MobilityCustomization.h` (Public)


#### class `FMobilityCustomization`  
`class FMobilityCustomization : public IDetailCustomNodeBuilder, public TSharedFromThis<FMobilityCustomization>`  
_L22-48_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FMobilityCustomization>`
- desc: Helper class to create a Mobility customization for the specified Property in the specified CategoryBuilder.
- L32 _public prototype_ `FMobilityCustomization(TSharedPtr<IPropertyHandle> InMobilityHandle, uint8 InRestrictedMobilityBits, bool InForLight);`
- L34 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& WidgetRow) override;`
- L35 _public prototype_ `virtual FName GetName() const override;`
- L36 _public function_ `virtual TSharedPtr<IPropertyHandle> GetPropertyHandle() const override`
- L40 _private prototype_ `EComponentMobility::Type GetActiveMobility() const;`
- L41 _private prototype_ `FSlateColor GetMobilityTextColor(EComponentMobility::Type InMobility) const;`
- L42 _private prototype_ `void OnMobilityChanged(EComponentMobility::Type InMobility);`
- L43 _private prototype_ `FText GetMobilityToolTip() const;`
- L45 _private member_ `TSharedPtr<IPropertyHandle> MobilityHandle;`
- L46 _private member_ `bool bForLight;`
- L47 _private member_ `uint8 RestrictedMobilityBits;`

#### enum `FMobilityCustomization::(anonymous)`  
``  
_L26-30_

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DETAILCUSTOMIZATIONS_API`
- L27 _enumerator_ `StaticMobilityBitMask = (1u << EComponentMobility::Static)` (scope `FMobilityCustomization::__anone5efec1b0103`)
- L28 _enumerator_ `StationaryMobilityBitMask = (1u << EComponentMobility::Stationary)` (scope `FMobilityCustomization::__anone5efec1b0103`)
- L29 _enumerator_ `MovableMobilityBitMask = (1u << EComponentMobility::Movable)` (scope `FMobilityCustomization::__anone5efec1b0103`)

### `Source/Editor/DetailCustomizations/Public/Customizations/SlateBrushCustomization.h` (Public)


#### class `FSlateBrushStructCustomization`  
`class FSlateBrushStructCustomization : public IPropertyTypeCustomization`  
_L17-74_
- inherits: `IPropertyTypeCustomization`
- L20 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(bool bIncludePreview);`
- L22 _public prototype_ `FSlateBrushStructCustomization(bool bIncludePreview);`
- L25 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;` — IPropertyTypeCustomization interface
- L27 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L33 _private prototype_ `EVisibility GetOutlineSettingsPropertyVisibility() const;` — Get the Slate Brush outline settings property row visibility
- L38 _private prototype_ `EVisibility GetTilingPropertyVisibility() const;` — Get the Slate Brush tiling property row visibility
- L43 _private prototype_ `EVisibility GetMarginPropertyVisibility() const;` — Get the Slate Brush margin property row visibility
- L46 _private prototype_ `bool IsImageSizeResetToDefaultVisible(TSharedPtr<IPropertyHandle> PropertyHandle) const;` — Callback for determining image size reset button visibility
- L49 _private prototype_ `void OnImageSizeResetToDefault(TSharedPtr<IPropertyHandle> PropertyHandle) const;` — Callback for clicking the image size reset button
- L52 _private prototype_ `FVector2f GetDefaultImageSize() const;` — Gets the current default image size based on the current texture resource
- L55 _private member_ `TSharedPtr<IPropertyHandle> DrawAsProperty;` — Slate Brush DrawAs property
- L58 _private member_ `TSharedPtr<IPropertyHandle> ImageSizeProperty;` — Slate Brush Image Size property
- L61 _private member_ `TSharedPtr<IPropertyHandle> ResourceObjectProperty;` — Slate Brush Resource Object property
- L64 _private member_ `TSharedPtr<IPropertyHandle> ResourceNameProperty;` — Slate Brush Resource Name property
- L67 _private member_ `TSharedPtr<IPropertyHandle> ImageTypeProperty;` — Slate Brush Image Type property
- L70 _private member_ `TSharedPtr<SErrorText> ResourceErrorText;` — Error text to display if the resource object is not valid
- L73 _private member_ `bool bIncludePreview;` — Should we show the preview portion of the customization?

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DETAILCUSTOMIZATIONS_API`

### `Source/Editor/DetailCustomizations/Public/Customizations/SlateFontInfoCustomization.h` (Public)


#### class `FSlateFontInfoStructCustomization`  
`class FSlateFontInfoStructCustomization : public IPropertyTypeCustomization`  
_L32-118_
- inherits: `IPropertyTypeCustomization`
- desc: Customize the appearance of an FSlateFontInfo
- L35 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L38 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L39 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& InStructBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override;`
- L42 _protected prototype_ `void AddFontSizeProperty(IDetailChildrenBuilder& InStructBuilder);`
- L43 _protected prototype_ `bool IsFontSizeEnabled() const;`
- L46 _protected prototype_ `TOptional<float> OnFontSizeGetValue() const;` — @return The value or unset if properties with multiple values are viewed
- L47 _protected prototype_ `void OnFontSizeValueChanged(float NewDisplayValue);`
- L48 _protected prototype_ `void OnFontSizeValueCommitted(float NewDisplayValue, ETextCommit::Type CommitInfo);`
- L53 _protected prototype_ `void OnFontSizeBeginSliderMovement();` — Called when the slider begins to move.  We create a transaction here to undo the property
- L58 _protected prototype_ `void OnFontSizeEndSliderMovement(float NewDisplayValue);` — Called when the slider stops moving.  We end the previously created transaction
- L61 _protected prototype_ `FText GetFontSizeTooltipText() const;` — @return a dynamic text explaining what the size does and showing the current Font DPI setting
- L63 _protected prototype_ `static float ConvertFontSizeFromNativeToDisplay(float FontSize);`
- L64 _protected prototype_ `static float ConvertFontSizeFromDisplayToNative(float FontSize);`
- L67 _protected prototype_ `static bool OnFilterFontAsset(const FAssetData& InAssetData);` — Called to filter out invalid font assets
- L70 _protected prototype_ `void OnFontChanged(const FAssetData& InAssetData);` — Called when the font object used by this FSlateFontInfo has been changed
- L73 _protected prototype_ `bool IsFontEntryComboEnabled() const;` — Called to see whether the font entry combo should be enabled
- L76 _protected prototype_ `void OnFontEntryComboOpening();` — Called before the font entry combo is opened - used to update the list of available font entries
- L79 _protected prototype_ `void OnFontEntrySelectionChanged(TSharedPtr<FName> InNewSelection, ESelectInfo::Type);` — Called when the selection of the font entry combo is changed
- L82 _protected prototype_ `TSharedRef<SWidget> MakeFontEntryWidget(TSharedPtr<FName> InFontEntry);` — Make the widget for an entry in the font entry combo
- L85 _protected prototype_ `FText GetFontEntryComboText() const;` — Get the text to use for the font entry combo button
- L88 _protected prototype_ `FName GetActiveFontEntry() const;` — Get the name of the currently active font entry (may not be the selected entry if the entry is set to use "None")
- L91 _protected prototype_ `TArray<FSlateFontInfo*> GetFontInfoBeingEdited();` — Get the array of FSlateFontInfo instances this customization is currently editing
- L92 _protected prototype_ `TArray<const FSlateFontInfo*> GetFontInfoBeingEdited() const;`
- L95 _protected member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle to the struct property being edited
- L98 _protected member_ `TSharedPtr<IPropertyHandle> FontObjectProperty;` — Handle to the "FontObject" property being edited
- L101 _protected member_ `TSharedPtr<IPropertyHandle> TypefaceFontNameProperty;` — Handle to the "TypefaceFontName" property being edited
- L104 _protected member_ `TSharedPtr<IPropertyHandle> FontSizeProperty;` — Handle to the "Size" property being edited
- L107 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<FName>>> FontEntryCombo;` — Font entry combo box widget
- L110 _protected member_ `TArray<TSharedPtr<FName>> FontEntryComboData;` — Source data for the font entry combo widget
- L113 _protected member_ `bool bIsUsingSlider = false;` — True if the slider is being used to change the value of the property
- L116 _protected member_ `float LastSliderFontSizeCommittedValue = 0.0f;` — When using the slider, what was the last committed value

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API DETAILCUSTOMIZATIONS_API`

### `Source/Editor/DetailCustomizations/Public/Customizations/VectorStructCustomization.h` (Public)


#### class `FVectorStructCustomization`  
`class FVectorStructCustomization : public FMathStructCustomization`  
_L17-32_
- inherits: `FMathStructCustomization`
- desc: Customizes FVector structs.
- L23 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — @return A new instance of this class
- L28 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L31 _private prototype_ `virtual void GetSortedChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, TArray<TSharedRef<IPropertyHandle>>& OutChildren) override;` — FMathStructCustomization interface

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DETAILCUSTOMIZATIONS_API`

### `Source/Editor/DetailCustomizations/Public/DetailCustomizations.h` (Public)


#### class `FDetailCustomizationsModule`  
`class FDetailCustomizationsModule : public IModuleInterface`  
_L11-70_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created
- L22 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed.
- L29 _public function_ `virtual bool SupportsDynamicReloading() override` — Override this to set whether your module is allowed to be unloaded on the fly @return	Whether the module supports shutdown separate from the rest of the engine.
- L37 _public prototype_ `void RegisterDevelopmentStatusWarningSuppression(FName ClassName);` — Suppresses the DevelopmentStatus warnings for the given class or any derived versions of this class
- L41 _public prototype_ `void UnregisterDevelopmentStatusWarningSuppression(FName ClassName);` — Removes suppression of DevelopmentStatus warnings for the given class or any derived versions of this class
- L43 _public prototype_ `bool IsDevelopmentStatusWarningSuppressed(const UClass* Class) const;`
- L46 _private prototype_ `void RegisterPropertyTypeCustomizations();`
- L47 _private prototype_ `void RegisterObjectCustomizations();`
- L48 _private prototype_ `void RegisterSectionMappings();`
- L56 _private prototype_ `void RegisterCustomClassLayout(FName ClassName, FOnGetDetailCustomizationInstance DetailLayoutDelegate );` — Registers a custom class @param ClassName				The class name to register for property customization @param DetailLayoutDelegate	The delegate to call to get the custom detail layout instance
- L64 _private prototype_ `void RegisterCustomPropertyTypeLayout(FName PropertyTypeName, FOnGetPropertyTypeCustomizationInstance PropertyTypeLayoutDelegate );` — Registers a custom struct @param StructName				The name of the struct to register for property customization @param StructLayoutDelegate	The delegate to call to get the custom detail layout instance
- L67 _private member_ `TSet< FName > RegisteredClassNames;` — List of registered class that we must unregister when the module shuts down
- L68 _private member_ `TSet< FName > RegisteredPropertyTypes;`
- L69 _private member_ `TSet< FName > SuppressedDevelopmentStatusWarnings;`

### `Source/Editor/DetailCustomizations/Public/DetailsViewCategoryHiderCustomization.h` (Public)


#### class `FDetailsViewCategoryHiderCustomization`  
`class FDetailsViewCategoryHiderCustomization : public IDetailCustomization`  
_L5-22_
- inherits: `IDetailCustomization`
- desc: Used to hide categories in a Details View
- L8 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TArray<FName>&& InCategoriesToHide);`
- L9 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(const TArrayView<FName>& InCategoriesToHide);`
- L12 _private prototype_ `FDetailsViewCategoryHiderCustomization(TArray<FName>&& InCategoriesToHide);`
- L13 _private prototype_ `FDetailsViewCategoryHiderCustomization(const TArrayView<FName>& InCategoriesToHide);`
- L15 _private prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailLayoutBuilder) override;`
- L18 _private member_ `TArray<FName> CategoriesToHide;`

### `Source/Editor/DetailCustomizations/Public/DetailsViewWarningOrErrorCustomization.h` (Public)


#### class `FDetailsViewWarningOrErrorCustomization`  
`class FDetailsViewWarningOrErrorCustomization : public IDetailCustomization`  
_L7-36_
- inherits: `IDetailCustomization`
- desc: Used to insert an SWarningOrErrorBox into a Details View at the top of a specified category
- L10 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance( const FName& InCategoryForInsertion, const FName& InRowTag, const FText& InWarningOrErrorLabel, const EMessageStyle InMessageStyle = EMessageStyle::Warning, ECategoryPriority::Type InCategoryPriority = ECategoryPriority::Uncommon);`
- L18 _private prototype_ `FDetailsViewWarningOrErrorCustomization( const FName& InCategoryForInsertion, const FName& InRowTag, const FText& InWarningOrErrorLabel, const EMessageStyle InMessageStyle, const ECategoryPriority::Type InCategoryPriority);`
- L25 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayoutBuilder) override;`
- L28 _private member_ `FName CategoryForInsertion;`
- L29 _private member_ `FName RowTag;`
- L30 _private member_ `FText WarningOrErrorLabel;`
- L31 _private member_ `EMessageStyle MessageStyle;`
- L32 _private member_ `ECategoryPriority::Type CategoryPriority;`

### `Source/Editor/DetailCustomizations/Public/GuidStructCustomization.h` (Public)


#### enum `EPropertyEditorGuidActions::Type`  
`enum Type`  
_L21-28_
- desc: Enumerates quick-set action types.
- L24 _public enumerator_ `Generate` — Generate a new GUID.
- L27 _public enumerator_ `Invalidate` — Set a null GUID.

#### class `FGuidStructCustomization`  
`class FGuidStructCustomization : public IPropertyTypeCustomization`  
_L37-95_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details panel customization for FGuid structures.
- L47 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance( )` — Creates a new instance. @return A new struct customization for Guids.
- L56 _public prototype_ `virtual void CustomizeHeader( TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L57 _public prototype_ `virtual void CustomizeChildren( TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils ) override;`
- L66 _protected prototype_ `void SetGuidValue( const FGuid& Guid );` — Sets the property's value. @param Guid The value to set.
- L71 _private prototype_ `void HandleGuidActionClicked( EPropertyEditorGuidActions::Type Action );` — Callback for clicking an item in the quick-set menu.
- L74 _private prototype_ `FSlateColor HandleTextBoxForegroundColor() const;` — Handles getting the text color of the editable text box.
- L77 _private prototype_ `FText HandleTextBoxText( ) const;` — Handles getting the text to be displayed in the editable text box.
- L80 _private prototype_ `void HandleTextBoxTextChanged( const FText& NewText );` — Handles changing the value in the editable text box.
- L83 _private prototype_ `void HandleTextBoxTextCommited( const FText& NewText, ETextCommit::Type CommitInfo );` — Handles committing the text in the editable text box.
- L88 _private member_ `bool InputValid;` — Holds a flag indicating whether the current input is a valid GUID.
- L91 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Holds a handle to the property being edited.
- L94 _private member_ `TSharedPtr<SEditableTextBox> TextBox;` — Holds the text box for editing the Guid.

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace EPropertyEditorGuidActions`
- L32 _prototype_ `void WriteGuidToProperty(TSharedPtr<IPropertyHandle> GuidPropertyHandle, const FGuid& Guid);` — Writes the supplied GUID to the supplied property handle as one undoable transaction

### `Source/Editor/DetailCustomizations/Public/KeyStructCustomization.h` (Public)


#### class `FKeyStructCustomization`  
`class FKeyStructCustomization : public IPropertyTypeCustomization`  
_L23-127_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details panel customization for FKey structures. As  "Key"				<SKeySelector>
- L27 _public prototype_ `FKeyStructCustomization();`
- L33 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L34 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L35 _public function_ `virtual bool ShouldInlineKey() const override`
- L39 _public prototype_ `void CustomizeHeaderOnlyWithButton(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils, TSharedRef<SWidget> Button);` — Helper variant that generates the key struct in the header and appends a single button at the end TODO: Is there a better way?
- L44 _public function_ `void SetDisplayIcon(bool bShouldDisplayIcon)` — `UE_DEPRECATED(5.2, "SetDisplayIcon(bShouldDisplayIcon) is deprecated and the icon referenced has been removed")` — Sets a bool for whether the information Icon for a combo trigger is displayed or not
- L51 _public function_ `bool GetDisplayIcon() const` — `UE_DEPRECATED(5.2, "GetDisplayIcon() is deprecated and the icon referenced has been removed")` — Gets bDisplayIcon bool
- L58 _public prototype_ `void SetEnableKeySelector(bool bKeySelectorEnabled);` — Sets a bool for whether the key selector should be enabled or not
- L62 _public function_ `bool GetEnableKeySelector() const` — Gets bEnableKeySelector bool
- L68 _public function_ `void SetDefaultKeyName(FString KeyName)` — Sets default key name - what key selector will default to if it is disabled
- L74 _public function_ `FString GetDefaultKeyName() const` — Gets default key name - what key selector will default to if it is disabled
- L80 _public function_ `void SetDisabledKeySelectorToolTip(const FText& InToolTip)` — Sets tooltip on the KeySelector when it is disabled
- L86 _public function_ `FText GetDisabledKeySelectorToolTip() const` — Gets tooltip on the KeySelector when it is disabled
- L91 _public prototype_ `void SetKey(const FString& KeyName);`
- L100 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance( );` — Creates a new instance. @return A new struct customization for Keys.
- L105 _protected member_ `bool bDisplayIcon = false;` — `UE_DEPRECATED(5.2, "bDisplayIcon is deprecated and the icon has been removed")` — Whether the information icon for combo triggers is displayed or not
- L108 _protected member_ `bool bEnableKeySelector = true;` — Whether the key selector should be enabled or not
- L111 _protected member_ `FText DisabledKeySelectorToolTip = FText::FromString(TEXT("Key` — Tooltip to display on the actual KeySelector
- L114 _protected member_ `FString DefaultKeyName = TEXT("Non` — Default Key to assign the KeySelector when it is disabled
- L117 _protected prototype_ `TOptional<FKey> GetCurrentKey() const;` — Gets the current Key being edited.
- L120 _protected prototype_ `void OnKeyChanged(TSharedPtr<FKey> SelectedKey);` — Updates the property when a new key is selected.
- L123 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Holds a handle to the property being edited.
- L126 _protected member_ `TSharedPtr<SKeySelector> KeySelector = nullptr;` — shared pointer to the Key Selector.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DETAILCUSTOMIZATIONS_API`

### `Source/Editor/DetailCustomizations/Public/PerPlatformPropertyCustomization.h` (Public)


#### struct `FPerPlatformPropertyCustomNodeBuilderArgs`  
`struct FPerPlatformPropertyCustomNodeBuilderArgs`  
_L32-55_
- L35 _public member_ `FOnGetContent OnGenerateNameWidget;` — Callback to generate the name widget.
- L38 _public member_ `TAttribute<TArray<FName>> PlatformOverrideNames;` — List of platforms that can override the default value
- L41 _public member_ `TAttribute<bool> IsEnabled = true;` — Is overriding per-property enabled
- L44 _public member_ `FOnGenerateWidget OnGenerateWidgetForPlatformRow;` — Callback to generate a widget for a specific platform row
- L46 _public member_ `FOnPlatformOverrideAction OnAddPlatformOverride;`
- L48 _public member_ `FOnPlatformOverrideAction OnRemovePlatformOverride;`
- L51 _public member_ `FText FilterText;` — Used for search box queries
- L54 _public member_ `FName Name;` — Used to identify the builder through GetName()

#### class `FPerPlatformPropertyCustomNodeBuilder`  
`class FPerPlatformPropertyCustomNodeBuilder : public IDetailCustomNodeBuilder, public TSharedFromThis<FPerPlatformPropertyCustomNodeBuilder>`  
_L57-82_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FPerPlatformPropertyCustomNodeBuilder>`
- L60 _public function_ `FPerPlatformPropertyCustomNodeBuilder(const FPerPlatformPropertyCustomNodeBuilderArgs& InArgs) : Args(InArgs)`
- L64 _public function_ `virtual void Tick(float DeltaTime) override`
- L65 _public function_ `virtual bool RequiresTick() const override`
- L67 _public prototype_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override;`
- L68 _public prototype_ `virtual void SetOnToggleExpansion(FOnToggleNodeExpansion InOnRegenerateChildren) override;`
- L69 _public prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& HeaderRow);`
- L70 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L71 _public function_ `virtual bool InitiallyCollapsed() const override`
- L72 _public prototype_ `virtual FName GetName() const override;`
- L74 _private prototype_ `void OnAddPlatformOverride(FName PlatformName);`
- L75 _private prototype_ `bool OnRemovePlatformOverride(FName PlatformName);`
- L76 _private prototype_ `void AddPlatformToMenu(const FName PlatformName, const FTextFormat Format, FMenuBuilder& AddPlatformMenuBuilder);`
- L79 _private member_ `FPerPlatformPropertyCustomNodeBuilderArgs Args;` — Handle to the default value
- L80 _private member_ `FSimpleDelegate OnRebuildChildren;`
- L81 _private member_ `FOnToggleNodeExpansion OnToggleExpansion;`

#### class `FPerPlatformPropertyCustomization`  
`template<typename PerPlatformType> class FPerPlatformPropertyCustomization : public IPropertyTypeCustomization`  
_L87-113_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details panel customization for the FPerPlatform structures.
- L90 _public function_ `FPerPlatformPropertyCustomization()`
- L94 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override` — IPropertyTypeCustomization interface
- L95 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L102 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates a new instance. @return A new customization for FPerPlatform structs.
- L105 _protected prototype_ `TSharedRef<SWidget> GetWidget(FName PlatformGroupName, TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder) const;`
- L106 _protected prototype_ `TArray<FName> GetPlatformOverrideNames(TSharedRef<IPropertyHandle> StructPropertyHandle) const;`
- L107 _protected prototype_ `bool AddPlatformOverride(FName PlatformGroupName, TSharedRef<IPropertyHandle> StructPropertyHandle);`
- L108 _protected prototype_ `bool RemovePlatformOverride(FName PlatformGroupName, TSharedRef<IPropertyHandle> StructPropertyHandle);`
- L112 _private member_ `TWeakPtr<IPropertyUtilities> PropertyUtilities;` — Cached utils used for resetting customization when layout changes

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API DETAILCUSTOMIZATIONS_API`
- L28 _typedef_ `typedef typename TSlateDelegates<FName>::FOnGenerateWidget FOnGenerateWidget;`
- L30 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnPlatformOverrideAction, FName);`
- L30 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnPlatformOverrideAction, FName);`

### `Source/Editor/DetailCustomizations/Public/SplineMetadataDetailsFactory.h` (Public)


#### class `ISplineMetadataDetails`  
`class ISplineMetadataDetails`  
_L12-19_
- L15 _public prototype_ `virtual FName GetName() const = 0;`
- L16 _public prototype_ `virtual FText GetDisplayName() const = 0;`
- L17 _public prototype_ `virtual void Update(USplineComponent* InSplineComponent, const TSet<int32>& InSelectedKeys) = 0;`
- L18 _public prototype_ `virtual void GenerateChildContent(IDetailGroup& InGroup) = 0;`

#### class `USplineMetadataDetailsFactoryBase`  
`class USplineMetadataDetailsFactoryBase : public UObject`  
_L22-29_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- L27 _public prototype_ `virtual TSharedPtr<ISplineMetadataDetails> Create() PURE_VIRTUAL(USplineMetadataDetailsFactoryBase::Create, return nullptr;);`
- L28 _public prototype_ `virtual UClass* GetMetadataClass() const PURE_VIRTUAL(USplineMetadataDetailsFactoryBase::GetMetadataClass, return nullptr;);`
