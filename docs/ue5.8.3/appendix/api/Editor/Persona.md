# Editor / Persona

- module root: `Source/Editor/Persona`
- headers: 182; symbols: 6389
- symbol kinds: class=244, delegate=166, enum=41, enumerator=155, externvar=2, function=669, macro=35, member=1715, namespace=28, prototype=3202, struct=93, typedef=38, variable=1
- DynamicallyLoadedModuleNames: AnimationEditor, AssetTools, DesktopPlatform, Documentation, MainFrame, MeshReductionInterface, SequenceRecorder, SkeletonEditor
- PrivateDependencyModuleNames: AnimGraph, AnimGraphRuntime, AnimationBlueprintLibrary, AnimationModifiers, AppFramework, ApplicationCore, AudioEditor, BlueprintGraph, ClothingSystemEditorInterface, ClothingSystemRuntimeCommon, ClothingSystemRuntimeInterface, CommonMenuExtensions, ContentBrowser, ContentBrowserData, Core, CoreUObject, CurveEditor, DesktopWidgets, EditorFramework, EditorStyle, EditorWidgets, Engine, GraphEditor, InputCore, InteractiveToolsFramework, InterchangeEngine, Json, JsonUtilities, Kismet, KismetWidgets, MirrorDataTableEditor, NaniteUtilities, PinnedCommandList, PropertyEditor, RHI, RenderCore, Sequencer, SequencerWidgets, SkeletalMeshDescription, SkeletalMeshUtilitiesCommon, Slate, SlateCore, StatusBar, TimeManagement, ToolMenus, ToolWidgets, TypedElementRuntime, UnrealEd
- PrivateIncludePathModuleNames: AnimationBlueprintEditor, AssetRegistry, AssetTools, DesktopPlatform, EditorInteractiveToolsFramework, MainFrame, MeshReductionInterface, SequenceRecorder
- PublicDependencyModuleNames: AdvancedPreviewScene, AnimationEditMode, EditorInteractiveToolsFramework
- PublicIncludePathModuleNames: AdvancedPreviewScene, AnimationEditor, Engine, SkeletonEditor

### `Source/Editor/Persona/Private/AnimGraphNodeDetails.h` (Private)


#### class `FAnimGraphNodeBindingExtension`  
`class FAnimGraphNodeBindingExtension : public IDetailPropertyExtensionHandler`  
_L28-38_
- inherits: `IDetailPropertyExtensionHandler`
- L32 _public prototype_ `virtual bool IsPropertyExtendable(const UClass* InObjectClass, const IPropertyHandle& PropertyHandle) const override;` — IDetailPropertyExtensionHandler interface
- L33 _public prototype_ `virtual void ExtendWidgetRow(FDetailWidgetRow& InWidgetRow, const IDetailLayoutBuilder& InDetailBuilder, const UClass* InObjectClass, TSharedPtr<IPropertyHandle> PropertyHandle) override;`
- L37 _private prototype_ `void GetOptionalPinData(const IPropertyHandle& PropertyHandle, int32& OutOptionalPinIndex, UAnimGraphNode_Base*& OutAnimGraphNode) const;` — Helper function

#### class `FAnimGraphNodeDetails`  
`class FAnimGraphNodeDetails : public IDetailCustomization`  
_L43-81_
- inherits: `IDetailCustomization`
- L46 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L49 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L54 _protected prototype_ `TSharedRef<SWidget> CreatePropertyWidget(FProperty* TargetProperty, TSharedRef<IPropertyHandle> TargetPropertyHandle, UClass* NodeClass);` — Creates a widget for the supplied property
- L57 _protected prototype_ `TSharedRef<SWidget> CreateAsPinWidget(TSharedRef<IPropertyHandle> InPropertyHandle);` — Creates the 'as pin' toggle widget for a property
- L59 _protected prototype_ `EVisibility GetVisibilityOfProperty(TSharedRef<IPropertyHandle> Handle) const;`
- L62 _protected prototype_ `bool OnShouldFilterAnimAsset( const FAssetData& AssetData, UClass* NodeToFilterFor ) const;` — Delegate to handle filtering of asset pickers
- L65 _protected prototype_ `void OnBlendProfileChanged(UBlendProfile* NewProfile, TSharedPtr<IPropertyHandle> PropertyHandle);` — Called when a blend profile is selected
- L68 _protected prototype_ `void OnPinVisibilityChanged(bool bInIsVisible, int32 InOptionalPinIndex);` — Called when pin visibility changes
- L71 _protected member_ `USkeleton* TargetSkeleton = nullptr;` — The skeleton we're operating on
- L74 _protected member_ `FString TargetSkeletonName;` — Path to the current blueprints skeleton to allow us to filter asset pickers
- L77 _protected member_ `IDetailLayoutBuilder* DetailLayoutBuilder = nullptr;` — Builder that built this customization (used for refresh)
- L80 _protected member_ `bool bIsAnimBPTemplate = false;` — Whether or not the anim blueprint is a template

#### class `FInputScaleBiasCustomization`  
`class FInputScaleBiasCustomization : public IPropertyTypeCustomization`  
_L86-100_
- inherits: `IPropertyTypeCustomization`
- L89 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L92 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L93 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L96 _public prototype_ `FText GetMinValue(TSharedRef<class IPropertyHandle> StructPropertyHandle) const;`
- L97 _public prototype_ `FText GetMaxValue(TSharedRef<class IPropertyHandle> StructPropertyHandle) const;`
- L98 _public prototype_ `void OnMinValueCommitted(const FText& NewText, ETextCommit::Type CommitInfo, TSharedRef<class IPropertyHandle> StructPropertyHandle);`
- L99 _public prototype_ `void OnMaxValueCommitted(const FText& NewText, ETextCommit::Type CommitInfo, TSharedRef<class IPropertyHandle> StructPropertyHandle);`

#### class `FBoneReferenceCustomization`  
`class FBoneReferenceCustomization : public IPropertyTypeCustomization`  
_L105-132_
- inherits: `IPropertyTypeCustomization`
- L108 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L111 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L112 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L113 _public prototype_ `const struct FReferenceSkeleton& GetReferenceSkeleton() const;`
- L116 _protected prototype_ `USkeleton* GetSkeleton() const;`
- L118 _protected prototype_ `static TSharedPtr<IPropertyHandle> FindStructMemberProperty(TSharedPtr<IPropertyHandle> PropertyHandle, const FName& PropertyName);`
- L120 _protected member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L123 _protected member_ `TSharedPtr<IPropertyHandle> BoneNameProperty;` — Property to change after bone has been picked
- L125 _protected member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjects;`
- L130 _private prototype_ `virtual void OnBoneSelectionChanged(FName Name);` — Bone tree widget delegates
- L131 _private prototype_ `virtual FName GetSelectedBone(bool& bMultipleValues) const;`

#### class `FBoneSocketTargetCustomization`  
`class FBoneSocketTargetCustomization : public FBoneReferenceCustomization`  
_L137-157_
- inherits: `FBoneReferenceCustomization`
- L140 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L142 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L145 _private prototype_ `void ResolveChildProperties();`
- L148 _private member_ `TSharedPtr<IPropertyHandle> SocketNameProperty;` — Property to change after bone has been picked
- L149 _private member_ `TSharedPtr<IPropertyHandle> UseSocketProperty;`
- L152 _private prototype_ `virtual void OnBoneSelectionChanged(FName Name) override;` — Bone tree widget delegates
- L153 _private prototype_ `virtual FName GetSelectedBone(bool& bMultipleValues) const override;`
- L154 _private prototype_ `const TArray<class USkeletalMeshSocket*>& GetSocketList() const;`
- L156 _private prototype_ `TSharedPtr<IPropertyHandle> GetNameProperty() const;`

#### enum `EPlayerTreeViewEntryType::Type`  
`enum Type`  
_L165-170_
- L167 _public enumerator_ `Blueprint`
- L168 _public enumerator_ `Graph`
- L169 _public enumerator_ `Node`

#### struct `FPlayerTreeViewEntry`  
`struct FPlayerTreeViewEntry : public TSharedFromThis<FPlayerTreeViewEntry>`  
_L174-197_
- inherits: `TSharedFromThis<FPlayerTreeViewEntry>`
- desc: Describes a single row entry in a player tree view
- L176 _public function_ `FPlayerTreeViewEntry(FString Name, EPlayerTreeViewEntryType::Type InEntryType, FAnimParentNodeAssetOverride* InOverride = NULL) : EntryName(Name) , EntryType(InEntryType) , Override(InOverride)`
- L182 _public prototype_ `FORCENOINLINE bool operator==(const FPlayerTreeViewEntry& Other);`
- L184 _public prototype_ `void GenerateNameWidget(TSharedPtr<SHorizontalBox> Box);`
- L187 _public member_ `FString EntryName;` — Name for the row
- L190 _public member_ `EPlayerTreeViewEntryType::Type EntryType;` — What the row represents
- L193 _public member_ `FAnimParentNodeAssetOverride* Override;` — Node asset override for rows that represent nodes
- L196 _public member_ `TArray<TSharedPtr<FPlayerTreeViewEntry>> Children;` — Children array for rows that represent blueprints and graphs.

#### class `FAnimGraphParentPlayerDetails`  
`class FAnimGraphParentPlayerDetails : public IDetailCustomization`  
_L199-222_
- inherits: `IDetailCustomization`
- L202 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TSharedRef<class FBlueprintEditor> InBlueprintEditor);`
- L204 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder);`
- L208 _private function_ `FAnimGraphParentPlayerDetails(const TSharedRef<class FBlueprintEditor>& InBlueprintEditor) : BlueprintEditorPtr(InBlueprintEditor)`
- L211 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FPlayerTreeViewEntry> EventPtr, const TSharedRef< STableViewBase >& OwnerTable);`
- L212 _private prototype_ `void OnGetChildren(TSharedPtr<FPlayerTreeViewEntry> InParent, TArray< TSharedPtr<FPlayerTreeViewEntry> >& OutChildren);`
- L215 _private member_ `TArray<TSharedPtr<FPlayerTreeViewEntry>> ListEntries;` — Entries in the tree view
- L218 _private member_ `TWeakPtr<class FBlueprintEditor> BlueprintEditorPtr;` — Hosting Blueprint Editor instance
- L221 _private member_ `UEditorParentPlayerListObj* EditorObject;` — Editor meta-object containing override information

#### class `SParentPlayerTreeRow`  
`class SParentPlayerTreeRow : public SMultiColumnTableRow<TSharedPtr<FAnimGraphParentPlayerDetails>>`  
_L224-274_
- inherits: `SMultiColumnTableRow<TSharedPtr<FAnimGraphParentPlayerDetails>>`
- L227 _public function_ `SLATE_BEGIN_ARGS(SParentPlayerTreeRow)`
- L228 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FPlayerTreeViewEntry>, Item);`
- L229 _public prototype_ `SLATE_ARGUMENT(UEditorParentPlayerListObj*, OverrideObject);`
- L230 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<class FBlueprintEditor>, BlueprintEditor);`
- L231 _public prototype_ `SLATE_END_ARGS();`
- L233 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L235 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName);`
- L240 _private prototype_ `bool OnShouldFilterAsset(const FAssetData& AssetData);` — Should an asset be filtered, ensures we only approve assets with matching skeletons
- L243 _private prototype_ `void OnAssetSelected(const FAssetData& AssetData);` — Sets the override asset when selected from the asset picker
- L245 _private function_ `void OnCloseMenu()`
- L249 _private prototype_ `FReply OnFocusNodeButtonClicked();` — Called when the user clicks the focus button, opens a graph panel if necessary in read only mode and focusses on the node.
- L252 _private prototype_ `const UAnimationAsset* GetCurrentAssetToUse() const;` — Gets the current asset, either an override if one is selected or the original from the node.
- L255 _private prototype_ `EVisibility GetResetToDefaultVisibility() const;` — Whether or not we should show the reset to default button next to the asset picker
- L258 _private prototype_ `FReply OnResetButtonClicked();` — Resets the selected asset override back to the original node's asset
- L261 _private prototype_ `FString GetCurrentAssetPath() const;` — Gets the full path to the current asset
- L264 _private member_ `UEditorParentPlayerListObj* EditorObject;` — Editor object containing all possible overrides
- L267 _private member_ `TSharedPtr<FPlayerTreeViewEntry> Item;` — Tree item we are representing
- L270 _private member_ `UAnimGraphNode_Base* GraphNode;` — Graphnode this row represents, if any
- L273 _private member_ `TWeakPtr<FBlueprintEditor> BlueprintEditor;` — Blueprint editor pointer

#### Free symbols / members of external scopes

- L163 _namespace_ `namespace EPlayerTreeViewEntryType`

### `Source/Editor/Persona/Private/AnimInstanceDetails.h` (Private)


#### class `FAnimInstanceDetails`  
`class FAnimInstanceDetails : public IDetailCustomization`  
_L16-32_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L22 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L28 _protected prototype_ `TSharedRef<SWidget> CreateFilteredObjectPropertyWidget(FProperty* TargetProperty, TSharedRef<IPropertyHandle> TargetPropertyHandle, const USkeleton* TargetSkeleton);` — Creates a filtered object widget if the supplied property is an object property
- L31 _protected prototype_ `bool OnShouldFilterAnimAsset(const FAssetData& AssetData, const USkeleton* TargetSkeleton) const;` — Delegate to handle filtering of asset pickers

### `Source/Editor/Persona/Private/AnimNotifyDetails.h` (Private)


#### class `FAnimNotifyDetails`  
`class FAnimNotifyDetails : public IDetailCustomization`  
_L15-96_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L27 _private member_ `TArray<TSharedPtr<IPropertyHandle>> NameProperties;` — Array of pointers to the name properties
- L29 _private member_ `TArray<TSharedPtr<FString>> SlotNameItems;` — List of slot names for selection dropdown, in same order as slots in the montage
- L36 _private prototype_ `bool CustomizeProperty(IDetailCategoryBuilder& CategoryBuilder, UObject* Notify, TSharedPtr<IPropertyHandle> Property);` — Customize a notify property that is inside an instanced property @param CategoryBuilder The category to place the property into @param Notify the UAnimNotify or UAnimNotifyState object for the property @param Property Handle to the property to customize
- L43 _private prototype_ `void AddBoneNameProperty(IDetailCategoryBuilder& CategoryBuilder, UObject* Notify, TSharedPtr<IPropertyHandle> Property);` — Adds a Bone Name property to the details layout @param CategoryBuilder The category to add the property to @param Notify the UAnimNotify or UAnimNotifyState object for the property @param Property Handle to the property to customize
- L50 _private prototype_ `void AddCurveNameProperty(IDetailCategoryBuilder& CategoryBuilder, UObject* Notify, TSharedPtr<IPropertyHandle> Property);` — Adds a Curve Name property to the details layout @param CategoryBuilder The category to add the property to @param Notify the UAnimNotify or UAnimNotifyState object for the property @param Property Handle to the property to customize
- L57 _private prototype_ `void OnSearchBoxCommitted(const FText& InSearchText, ETextCommit::Type CommitInfo, int32 PropertyIndex);` — Handles search box commit for name properties @param InSearchText Text that was committed @param CommitInfo Commit method @param PropertyIndex Index of the name properties in internal array
- L60 _private prototype_ `TArray<FString> GetSearchSuggestions() const;` — Get the search suggestions
- L67 _private prototype_ `void ClearInstancedSelectionDropDown(IDetailCategoryBuilder& CategoryBuilder, TSharedRef<IPropertyHandle> PropHandle, bool bShowChildren = true);` — Removes the dropdown selection of instanced objects from the header for the property @param CategoryBuilder The category builder for the property @param PropHandle Handle to the property to modify @param bShowChildren Whether or not to show the instanced object children
- L73 _private prototype_ `void CustomizeLinkProperties(IDetailLayoutBuilder& Builder, TSharedRef<IPropertyHandle> NotifyProperty, UAnimSequenceBase* AnimSequenceBase);` — Move properties representing notify linking information into their own category @param Builder Layout builder for this object @param NotifyProperty The property that contains the linking properties
- L79 _private prototype_ `void HideLinkProperties(IDetailLayoutBuilder& Builder, TSharedRef<IPropertyHandle> NotifyProperty);` — Hide any properties relating to notify linking @param Builder Layout builder for this object @param NotifyProperty The notify property that contains the linking properties
- L84 _private prototype_ `void UpdateSlotNames(UAnimSequenceBase* AnimObject);` — Updates the list of slot names used for combo box @param AnimObject Object being edited, where we will search for slots
- L89 _private prototype_ `void OnSlotSelected(TSharedPtr<FString> SlotName, ESelectInfo::Type SelectInfo, TSharedPtr<IPropertyHandle> Property);` — Called when the user selects a slot @param Index Index of the new slot
- L92 _private prototype_ `EVisibility VisibilityForLODFilterMode() const;` — Return whether or not the LOD filter mode should be visible
- L95 _private member_ `TSharedPtr<IPropertyHandle> TriggerFilterModeHandle;` — Caches the Filter Mode handle so we can look up its value after customization has finished

### `Source/Editor/Persona/Private/AnimNotifyPanelContextMenuContext.h` (Private)


#### class `UAnimNotifyPanelContextMenuContext`  
`class UAnimNotifyPanelContextMenuContext : public UObject`  
_L14-25_
- reflection: `UCLASS()`
- inherits: `UObject`
- L19 _public member_ `TWeakPtr<SAnimNotifyTrack> NotifyTrack = nullptr;`
- L20 _public member_ `INotifyNodeObjectInterface* NodeObject = nullptr;`
- L21 _public member_ `FAnimNotifyEvent* NotifyEvent = nullptr;`
- L22 _public member_ `int32 NotifyIndex = INDEX_NONE;`
- L23 _public member_ `int32 NodeIndex = INDEX_NONE;`
- L24 _public member_ `FPointerEvent MouseEvent;`

### `Source/Editor/Persona/Private/AnimSequenceCurveEditorCommands.h` (Private)


#### class `FAnimSequenceCurveEditorCommands`  
`class FAnimSequenceCurveEditorCommands : public TCommands<FAnimSequenceCurveEditorCommands>`  
_L18-36_
- inherits: `TCommands<FAnimSequenceCurveEditorCommands>`
- desc: Defines commands for the anim sequence curve editor
- L21 _public function_ `FAnimSequenceCurveEditorCommands() : TCommands<FAnimSequenceCurveEditorCommands> ( TEXT("AnimSequenceCurveEditor"), NSLOCTEXT("Contexts", "AnimSequenceCurveEditor", "Anim Sequence Curve Editor"), NAME_None, FAppStyle::GetAppStyleSetName() )`
- L32 _public member_ `TSharedPtr<FUICommandInfo> EditSelectedCurves;`
- L35 _public prototype_ `virtual void RegisterCommands() override;`

### `Source/Editor/Persona/Private/AnimSequenceTimelineCommands.h` (Private)


#### class `FAnimSequenceTimelineCommands`  
`class FAnimSequenceTimelineCommands : public TCommands<FAnimSequenceTimelineCommands>`  
_L18-81_
- inherits: `TCommands<FAnimSequenceTimelineCommands>`
- desc: Defines commands for the anim sequence timeline editor
- L21 _public function_ `FAnimSequenceTimelineCommands() : TCommands<FAnimSequenceTimelineCommands> ( TEXT("AnimSequenceCurveEditor"), NSLOCTEXT("Contexts", "AnimSequenceTimelineEditor", "Anim Sequence Timeline Editor"), NAME_None, FAppStyle::GetAppStyleSetName() )`
- L32 _public member_ `TSharedPtr<FUICommandInfo> EditSelectedCurves;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> AddNotifyTrack;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> PasteDataIntoCurve;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> InsertNotifyTrack;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> RemoveNotifyTrack;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> AddCurve;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> EditCurve;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> ShowCurveKeys;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> UseTreeView;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> AddMetadata;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> ConvertCurveToMetaData;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> ConvertMetaDataToCurve;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> RemoveCurve;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> RemoveAllCurves;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> CopySelectedCurveNames;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> DisplaySeconds;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> DisplayFrames;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> DisplayPercentage;`
- L68 _public member_ `TSharedPtr<FUICommandInfo> DisplaySecondaryFormat;`
- L70 _public member_ `TSharedPtr<FUICommandInfo> SnapToFrames;`
- L72 _public member_ `TSharedPtr<FUICommandInfo> SnapToNotifies;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> SnapToMontageSections;`
- L76 _public member_ `TSharedPtr<FUICommandInfo> SnapToCompositeSegments;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> AddComment;`
- L80 _public prototype_ `virtual void RegisterCommands() override;`

### `Source/Editor/Persona/Private/AnimTimeline/AnimModel.h` (Private)


#### class `FAnimModel`  
`class FAnimModel : public TSharedFromThis<FAnimModel>, public FGCObject`  
_L22-284_
- inherits: `TSharedFromThis<FAnimModel>,FGCObject`
- desc: Model of the anim timeline's data
- L25 _public prototype_ `FAnimModel(const TSharedRef<IPersonaPreviewScene>& InPreviewScene, const TSharedRef<IEditableSkeleton>& InEditableSkeleton, const TSharedRef<FUICommandList>& InCommandList);`
- L28 _public prototype_ `virtual ~FAnimModel() = default;`
- L32 _public prototype_ `virtual void Initialize();` — Bind commands and perform any one-time initialization
- L36 _public function_ `const TArray<TSharedRef<FAnimTimelineTrack>>& GetRootTracks() const` — `UE_DEPRECATED(5.8, "Please use GetAllRootTracks instead.")` — Get the root tracks representing the tree
- L42 _public function_ `const TArray<TSharedRef<FAnimTimelineTrack>>& GetAllRootTracks() const` — Get the root tracks representing the tree - alias to aid deprecation
- L48 _public prototype_ `FAnimatedRange GetViewRange() const;` — Get the current view range
- L51 _public prototype_ `void SetViewRange(TRange<double> InRange);` — Set the current view range
- L54 _public prototype_ `FAnimatedRange GetWorkingRange() const;` — Get the working range of the model's data
- L57 _public prototype_ `TRange<FFrameNumber> GetPlaybackRange() const;` — Get the playback range of the model's data
- L60 _public prototype_ `FFrameNumber GetScrubPosition() const;` — Get the current scrub position
- L63 _public prototype_ `float GetScrubTime() const;` — Get the current scrub time
- L66 _public prototype_ `void SetScrubPosition(FFrameTime NewScrubPostion) const;` — Set the current scrub position
- L69 _public prototype_ `void HandleViewRangeChanged(TRange<double> InRange, EViewRangeInterpolation InInterpolation);` — Handle the view range being changed
- L72 _public prototype_ `void HandleWorkingRangeChanged(TRange<double> InRange);` — Handle the working range being changed
- L75 _public function_ `DECLARE_EVENT(FAnimModel, FOnTracksChanged) FOnTracksChanged& OnTracksChanged()` — Delegate fired when tracks have changed
- L79 _public function_ `DECLARE_EVENT_OneParam(FAnimModel, FOnHandleObjectsSelected, const TArray<UObject*>& ) FOnHandleObjectsSelected& OnHandleObjectsSelected()` — Delegate fired when objects have been selected
- L83 _public prototype_ `virtual void RefreshTracks() = 0;` — Refresh the tracks we have using our underlying asset
- L86 _public prototype_ `virtual void UpdateRange() = 0;` — Update the displayed range if the length of the sequence could have changed
- L89 _public prototype_ `virtual UAnimSequenceBase* GetAnimSequenceBase() const = 0;` — Get the underlying anim sequence
- L93 _public function_ `template<typename AssetType> AssetType* GetAsset() const` — Get the underlying anim sequence, cast to the specified type
- L99 _public function_ `TSharedRef<IPersonaPreviewScene> GetPreviewScene() const` — Get the preview scene
- L102 _public function_ `TSharedRef<IEditableSkeleton> GetEditableSkeleton() const` — Get the editable skeleton
- L105 _public function_ `TSharedRef<FUICommandList> GetCommandList() const` — Get the command list
- L108 _public prototype_ `bool IsTrackSelected(const TSharedRef<const FAnimTimelineTrack>& InTrack) const;` — Get whether a track is selected
- L111 _public prototype_ `void ClearTrackSelection();` — Clear all track selection
- L114 _public prototype_ `void SetTrackSelected(const TSharedRef<FAnimTimelineTrack>& InTrack, bool bIsSelected);` — Set whether a track is selected
- L117 _public prototype_ `UObject* ShowInDetailsView(UClass* EdClass);` — Creates an editor object from the given type to be used in a details panel
- L120 _public prototype_ `void SelectObjects(const TArray<UObject*>& Objects);` — 'Selects' objects and shows them in the details view
- L123 _public prototype_ `void ClearDetailsView();` — Clears the detail view of whatever we displayed last
- L126 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L127 _public function_ `virtual FString GetReferencerName() const override`
- L133 _public prototype_ `virtual void RecalculateSequenceLength();` — Recalculate sequence length after modifying
- L139 _public prototype_ `virtual float CalculateSequenceLengthOfEditorObject() const;` — Calculates the sequence length of the object @return		New sequence length
- L142 _public function_ `virtual void InitDetailsViewEditorObject(UEditorAnimBaseObj* EdObj)` — Allows derived classes to init newly created editor objects
- L145 _public function_ `const TArray<double>& GetEditableTimes() const` — Access editable times
- L146 _public function_ `void SetEditableTimes(const TArray<double>& InTimes)`
- L149 _public prototype_ `void SetEditableTime(int32 TimeIndex, double Time, bool bIsDragging);` — Set an editable time
- L152 _public function_ `virtual void OnSetEditableTime(int32 TimeIndex, double Time, bool bIsDragging)` — Override point for derived types to handle setting a time
- L155 _public prototype_ `FFrameRate GetFrameRate() const;` — Get the framerate specified by the anim sequence
- L158 _public prototype_ `int32 GetTickResolution() const;` — Get the tick resolution we are displaying at
- L161 _public member_ `FOnObjectsSelected OnSelectObjects;` — Delegate used to edit object details
- L164 _public member_ `FOnInvokeTab OnInvokeTab;` — Delegate used to invoke a tab in a Persona asset editor
- L174 _public prototype_ `bool Snap(float& InOutTime, float InSnapMargin, TArrayView<const FName> InSkippedSnapTypes, FName& OutSnapType) const;` — Snaps a time to the currently set snap times @param	InOutTime				The time to snap @param	InSnapMargin			The margin (in seconds) to limit the snap to @param	InSkippedSnapTypes		Array of snap types that should be ignored when checking for snap @param	OutSnapType				The type of snap that was snapped to @return true if a snap occurred
- L175 _public prototype_ `bool Snap(double& InOutTime, double InSnapMargin, TArrayView<const FName> InSkippedSnapTypes, FName& OutSnapType) const;`
- L178 _public prototype_ `void ToggleSnap(FName InSnapName);` — Toggle the specified snap type
- L181 _public prototype_ `bool IsSnapChecked(FName InSnapName) const;` — Check whether the specified snap is enabled
- L184 _public prototype_ `bool IsSnapAvailable(FName InSnapName) const;` — Check whether the specified snap is available
- L187 _public prototype_ `virtual void BuildContextMenu(FMenuBuilder& InMenuBuilder);` — Build a context menu for selected items
- L190 _public prototype_ `void ForEachRootTrack(TFunctionRef<void(FAnimTimelineTrack&)> InFunction);` — Run a predicate for each root track
- L194 _protected prototype_ `void AddRootTrack(TSharedRef<FAnimTimelineTrack> InTrack);` — Adds a track to the root tracks collection
- L197 _protected prototype_ `void ClearRootTracks();` — Clears all root tracks
- L201 _protected member_ `TArray<TSharedRef<FAnimTimelineTrack>> RootTracks;` — Tracks used to generate a tree
- L204 _protected member_ `TSet<TSharedRef<FAnimTimelineTrack>> SelectedTracks;` — Tracks that are selected
- L207 _protected member_ `FAnimatedRange ViewRange;` — The range we are currently viewing
- L210 _protected member_ `FAnimatedRange WorkingRange;` — The working range of this model, encompassing the view range
- L213 _protected member_ `FAnimatedRange PlaybackRange;` — The playback range of this model for each timeframe
- L216 _protected member_ `FOnTracksChanged OnTracksChangedDelegate;` — Delegate fired when tracks change
- L219 _protected member_ `FOnHandleObjectsSelected OnHandleObjectsSelectedDelegate;` — Delegate fired when selection changes
- L222 _protected member_ `TWeakPtr<IPersonaPreviewScene> WeakPreviewScene;` — The preview scene that this model is linked to
- L225 _protected member_ `TWeakPtr<IEditableSkeleton> WeakEditableSkeleton;` — The editable skeleton that this model is linked to
- L228 _protected member_ `TWeakPtr<FUICommandList> WeakCommandList;` — The command list we bind to
- L231 _protected member_ `FEditorObjectTracker EditorObjectTracker;` — Tracks objects created for the details panel
- L234 _protected member_ `TArray<double> EditableTimes;` — Times that can be edited by dragging bars in the UI
- L277 _protected member_ `TMap<FName, FSnapType> SnapTypes;` — Snap types for this model
- L280 _protected member_ `TArray<FSnapTime> SnapTimes;` — Times that can be snapped to when dragging
- L283 _protected member_ `bool bIsSelecting;` — Recursion guard for selection

#### struct `FAnimModel::FSnapType`  
`struct FSnapType`  
_L237-259_
- desc: Struct describing the type of a snap
- L239 _public function_ `FSnapType(const FName& InType, const FText& InDisplayName, TFunction<double(const FAnimModel&, double)> InSnapFunction = nullptr) : Type(InType) , DisplayName(InDisplayName) , SnapFunction(InSnapFunction)`
- L246 _public member_ `FName Type;` — Identifier for this snap type
- L249 _public member_ `FText DisplayName;` — Display name for this snap type
- L252 _public member_ `TFunction<double(const FAnimModel&, double)> SnapFunction;` — Optional function to snap with
- L255 _public member_ `static const FSnapType Frames;` — Built-in snap types
- L256 _public member_ `static const FSnapType Notifies;`
- L257 _public member_ `static const FSnapType CompositeSegment;`
- L258 _public member_ `static const FSnapType MontageSection;`

#### struct `FAnimModel::FSnapTime`  
`struct FSnapTime`  
_L262-274_
- desc: Struct describing a time that can be snapped to
- L264 _public function_ `FSnapTime(const FName& InType, double InTime) : Type(InType) , Time(InTime)`
- L270 _public member_ `FName Type;` — Type corresponding to a FSnapType
- L273 _public member_ `double Time;` — The time to snap to

#### Free symbols / members of external scopes

- L75 _delegate_ `DECLARE_EVENT(FAnimModel, FOnTracksChanged) FOnTracksChanged& OnTracksChanged() { return OnTracksChangedDelegate; } DECLARE_EVENT_OneParam(FAnimModel, FOnHandleObjectsSelected, const TArray<UObject*>& ) FOnHandleObjectsSelected& OnHandleObjectsSelected() { return OnHandleObjectsSelectedDelegate; } virtual void RefreshTracks() = 0;` — Delegate fired when tracks have changed
- L79 _delegate_ `DECLARE_EVENT_OneParam(FAnimModel, FOnHandleObjectsSelected, const TArray<UObject*>& ) FOnHandleObjectsSelected& OnHandleObjectsSelected() { return OnHandleObjectsSelectedDelegate; } virtual void RefreshTracks() = 0;` — Delegate fired when objects have been selected

### `Source/Editor/Persona/Private/AnimTimeline/AnimModel_AnimComposite.h` (Private)


#### class `FAnimModel_AnimComposite`  
`class FAnimModel_AnimComposite : public FAnimModel_AnimSequenceBase`  
_L10-28_
- inherits: `FAnimModel_AnimSequenceBase`
- desc: Anim model for an anim composite
- L13 _public prototype_ `FAnimModel_AnimComposite(const TSharedRef<IPersonaPreviewScene>& InPreviewScene, const TSharedRef<IEditableSkeleton>& InEditableSkeleton, const TSharedRef<FUICommandList>& InCommandList, UAnimComposite* InAnimComposite);`
- L16 _public prototype_ `virtual void RefreshTracks() override;` — FAnimModel interface
- L17 _public prototype_ `virtual UAnimSequenceBase* GetAnimSequenceBase() const override;`
- L18 _public prototype_ `virtual void RecalculateSequenceLength() override;`
- L19 _public prototype_ `virtual float CalculateSequenceLengthOfEditorObject() const override;`
- L20 _public prototype_ `virtual void RefreshSnapTimes() override;`
- L24 _private member_ `UAnimComposite* AnimComposite;` — The anim composite we wrap
- L27 _private member_ `TSharedPtr<FAnimTimelineTrack> CompositeRoot;` — Root track for the composite

### `Source/Editor/Persona/Private/AnimTimeline/AnimModel_AnimMontage.h` (Private)


#### class `FAnimModel_AnimMontage`  
`class FAnimModel_AnimMontage : public FAnimModel_AnimSequenceBase`  
_L17-85_
- inherits: `FAnimModel_AnimSequenceBase`
- desc: Anim model for an anim montage
- L20 _public prototype_ `FAnimModel_AnimMontage(const TSharedRef<IPersonaPreviewScene>& InPreviewScene, const TSharedRef<IEditableSkeleton>& InEditableSkeleton, const TSharedRef<FUICommandList>& InCommandList, UAnimMontage* InAnimMontage);`
- L23 _public prototype_ `virtual void Initialize() override;` — FAnimModel interface
- L24 _public prototype_ `virtual void RefreshTracks() override;`
- L25 _public prototype_ `virtual UAnimSequenceBase* GetAnimSequenceBase() const override;`
- L26 _public prototype_ `virtual float CalculateSequenceLengthOfEditorObject() const override;`
- L27 _public prototype_ `virtual void RecalculateSequenceLength() override;`
- L28 _public prototype_ `virtual void OnSetEditableTime(int32 TimeIndex, double Time, bool bIsDragging) override;`
- L29 _public prototype_ `virtual bool ClampToEndTime(float NewEndTime) override;`
- L30 _public prototype_ `virtual void RefreshSnapTimes() override;`
- L33 _public prototype_ `void RefreshSectionTimes();` — Refresh the UI representation of the sections
- L35 _public prototype_ `void OnMontageModified();`
- L37 _public prototype_ `void SortSections();`
- L39 _public prototype_ `void EnsureStartingSection();`
- L41 _public prototype_ `void RefreshNotifyTriggerOffsets();`
- L43 _public prototype_ `void ShowSectionInDetailsView(int32 SectionIndex);`
- L45 _public prototype_ `void RestartPreviewFromSection(int32 FromSectionIdx);`
- L48 _public member_ `FSimpleDelegate OnSectionsChanged;` — Delegate fired when montage sections have changed
- L51 _public member_ `FOnSectionTimeDragged OnSectionTimeDragged;` — Delegate fired when a section is dragged/dropped (only on drop does the time actually get set)
- L54 _public function_ `TSharedPtr<FAnimTimelineTrack_MontagePanel> GetMontagePanel() const` — Access the montage panel track
- L57 _public prototype_ `bool IsTimingElementDisplayEnabled(ENotifyTimingElementType::Type ElementType) const;` — Timing panel display options
- L58 _public prototype_ `void ToggleTimingElementDisplayEnabled(ENotifyTimingElementType::Type ElementType);`
- L61 _public prototype_ `bool IsSectionTimingDisplayEnabled() const;` — Montage section track timing options
- L62 _public prototype_ `void ToggleSectionTimingDisplay();`
- L65 _protected prototype_ `virtual void OnDataModelChanged(const EAnimDataModelNotifyType& NotifyType, IAnimationDataModel* Model, const FAnimDataModelNotifPayload& PayLoad) override;`
- L69 _private member_ `UAnimMontage* AnimMontage;` — The anim montage we wrap
- L72 _private member_ `TSharedPtr<FAnimTimelineTrack_Montage> MontageRoot;` — Root track for the montage
- L75 _private member_ `TSharedPtr<FAnimTimelineTrack_MontagePanel> MontagePanel;` — Montage panel
- L78 _private member_ `TSharedPtr<FAnimTimelineTrack_TimingPanel> TimingPanel;` — Timing panel
- L81 _private member_ `bool TimingElementNodeDisplayFlags[ENotifyTimingElementType::Max];` — Display flags for timing panel
- L84 _private member_ `bool bSectionTimingEnabled;` — Whether montage section timing is enabled on the section track

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnSectionTimeDragged, int32 , float , bool );` — Delegate fired when a section is dragged/dropped (only on drop does the time actually get set)
- L14 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnSectionTimeDragged, int32 , float , bool );` — Delegate fired when a section is dragged/dropped (only on drop does the time actually get set)

### `Source/Editor/Persona/Private/AnimTimeline/AnimModel_AnimSequenceBase.h` (Private)


#### class `FAnimModel_AnimSequenceBase`  
`class FAnimModel_AnimSequenceBase : public FAnimModel`  
_L21-118_
- inherits: `FAnimModel`
- desc: Anim model for an anim sequence base
- L24 _public prototype_ `FAnimModel_AnimSequenceBase(const TSharedRef<IPersonaPreviewScene>& InPreviewScene, const TSharedRef<IEditableSkeleton>& InEditableSkeleton, const TSharedRef<FUICommandList>& InCommandList, UAnimSequenceBase* InAnimSequenceBase);`
- L26 _public prototype_ `~FAnimModel_AnimSequenceBase();`
- L29 _public prototype_ `virtual void RefreshTracks() override;` — FAnimModel interface
- L30 _public prototype_ `virtual UAnimSequenceBase* GetAnimSequenceBase() const override;`
- L31 _public prototype_ `virtual void Initialize() override;`
- L32 _public prototype_ `virtual void UpdateRange() override;`
- L34 _public function_ `const TSharedPtr<FAnimTimelineTrack_Notifies>& GetNotifyRoot() const`
- L37 _public member_ `FOnEditCurves OnEditCurves;` — Delegate used to edit curves
- L40 _public prototype_ `bool IsNotifiesTimingElementDisplayEnabled(ENotifyTimingElementType::Type ElementType) const;` — Notify track timing options
- L41 _public prototype_ `void ToggleNotifiesTimingElementDisplayEnabled(ENotifyTimingElementType::Type ElementType);`
- L47 _public prototype_ `virtual bool ClampToEndTime(float NewEndTime);` — Clamps the sequence to the specified length @return		Whether clamping was/is necessary
- L50 _public prototype_ `virtual void RefreshSnapTimes();` — Refresh any simple snap times
- L54 _protected prototype_ `void RefreshNotifyTracks();` — Refresh notify tracks
- L57 _protected prototype_ `void RefreshCurveTracks();` — Refresh curve tracks
- L60 _protected prototype_ `void RefreshAttributeTracks();` — Refresh attribute tracks
- L63 _protected prototype_ `virtual void OnDataModelChanged(const EAnimDataModelNotifyType& NotifyType, IAnimationDataModel* Model, const FAnimDataModelNotifPayload& PayLoad);` — Callback for any change made to the IAnimationDataModel embedded in the AnimSequenceBase instance this represents
- L67 _private prototype_ `void EditSelectedCurves();` — UI handlers
- L68 _private prototype_ `bool CanEditSelectedCurves() const;`
- L69 _private prototype_ `void RemoveSelectedCurves();`
- L70 _private prototype_ `void CopySelectedCurveNamesToClipboard();`
- L71 _private prototype_ `void SetDisplayFormat(EFrameNumberDisplayFormats InFormat);`
- L72 _private prototype_ `bool IsDisplayFormatChecked(EFrameNumberDisplayFormats InFormat) const;`
- L73 _private prototype_ `void ToggleDisplayPercentage();`
- L74 _private prototype_ `bool IsDisplayPercentageChecked() const;`
- L75 _private prototype_ `void ToggleDisplaySecondary();`
- L76 _private prototype_ `bool IsDisplaySecondaryChecked() const;`
- L77 _private prototype_ `bool AreAnyCurvesSelected() const;`
- L80 _private prototype_ `void CopyToClipboard() const;` — Copy selected curves to clipboard
- L81 _private prototype_ `bool CanCopyToClipboard();`
- L84 _private prototype_ `void PasteDataFromClipboardToSelectedCurve();` — Paste curve data into selected curve. Only modifies curves, does not add any new curves.
- L85 _private prototype_ `bool CanPasteDataFromClipboardToSelectedCurve();`
- L88 _private prototype_ `void PasteFromClipboard();` — Paste curves from clipboard. Adds or overwrites curves (if identifiers collide)
- L89 _private prototype_ `bool CanPasteFromClipboard();`
- L92 _private prototype_ `void CutToClipboard();` — Cut selected curves to clipboard
- L93 _private prototype_ `bool CanCutToClipboard();`
- L97 _private member_ `UAnimSequenceBase* AnimSequenceBase;` — The anim sequence base we wrap
- L100 _private member_ `TSharedPtr<FAnimTimelineTrack_Notifies> NotifyRoot;` — Root track for notifies
- L103 _private member_ `TSharedPtr<FAnimTimelineTrack_NotifiesPanel> NotifyPanel;` — Legacy notify panel track
- L106 _private member_ `TSharedPtr<FAnimTimelineTrack_Curves> CurveRoot;` — Root track for curves
- L109 _private member_ `TSharedPtr<FAnimTimelineTrack> AdditiveRoot;` — Root track for additive layers
- L112 _private member_ `TSharedPtr<FAnimTimelineTrack_Attributes> AttributesRoot;` — Root track for custom attributes
- L115 _private member_ `bool NotifiesTimingElementNodeDisplayFlags[ENotifyTimingElementType::Max];` — Display flags for notifies track
- L117 _protected member_ `UE::Anim::FAnimDataModelNotifyCollector NotifyCollector;`

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimeSliderController.h` (Private)


#### struct `FPaintSectionAreaViewArgs`  
`struct FPaintSectionAreaViewArgs`  
_L18-30_
- L20 _public function_ `FPaintSectionAreaViewArgs() : bDisplayTickLines(false), bDisplayScrubPosition(false)`
- L25 _public member_ `bool bDisplayTickLines;` — Whether to display tick lines
- L27 _public member_ `bool bDisplayScrubPosition;` — Whether to display the scrub position
- L29 _public member_ `TOptional<FPaintPlaybackRangeArgs> PlaybackRangeArgs;` — Optional Paint args for the playback range

#### class `FAnimTimeSliderController`  
`class FAnimTimeSliderController : public ITimeSliderController`  
_L35-252_
- inherits: `ITimeSliderController`
- desc: A time slider controller for the anim timeline
- L38 _public prototype_ `FAnimTimeSliderController( const FTimeSliderArgs& InArgs, TWeakPtr<FAnimModel> InWeakModel, TWeakPtr<SAnimTimeline> InWeakTimeline, TSharedPtr<INumericTypeInterface<double>> InSecondaryNumericTypeInterface );`
- L49 _public prototype_ `float DetermineOptimalSpacing(float InPixelsPerInput, uint32 MinTick, float MinTickSpacing) const;` — Determines the optimal spacing between tick marks in the slider for a given pixel density Increments until a minimum amount of slate units specified by MinTick is reached @param InPixelsPerInput	The density of pixels between each input @param MinTick			The minimum slate units per tick allowed @param MinTickSpacing	The minimum tick spacing in time units allowed @return the optimal spacing in time units
- L52 _public prototype_ `virtual int32 OnPaintTimeSlider( bool bMirrorLabels, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;` — ITimeSliderController Interface
- L53 _public prototype_ `virtual int32 OnPaintViewArea( const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, bool bEnabled, const FPaintViewAreaArgs& Args ) const override;`
- L54 _public prototype_ `virtual FReply OnMouseButtonDown( SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L55 _public prototype_ `virtual FReply OnTimeSliderMouseButtonDown( SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L56 _public prototype_ `virtual FReply OnMouseButtonUp( SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L57 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L58 _public prototype_ `virtual FReply OnMouseMove( SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L59 _public prototype_ `virtual FReply OnMouseWheel( SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L60 _public prototype_ `virtual FCursorReply OnCursorQuery( const SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;`
- L61 _public prototype_ `virtual void SetViewRange( double NewRangeMin, double NewRangeMax, EViewRangeInterpolation Interpolation ) override;`
- L62 _public prototype_ `virtual void SetClampRange( double NewRangeMin, double NewRangeMax ) override;`
- L63 _public prototype_ `virtual void SetPlayRange( FFrameNumber RangeStart, int32 RangeDuration ) override;`
- L64 _public function_ `virtual FFrameRate GetDisplayRate() const override`
- L65 _public function_ `virtual FFrameRate GetTickResolution() const override`
- L66 _public function_ `virtual FAnimatedRange GetViewRange() const override`
- L67 _public function_ `virtual FAnimatedRange GetClampRange() const override`
- L68 _public function_ `virtual TRange<FFrameNumber> GetPlayRange() const override`
- L69 _public function_ `virtual FFrameTime GetScrubPosition() const`
- L70 _public function_ `virtual void SetScrubPosition(FFrameTime InTime, bool bEvaluate)`
- L79 _public prototype_ `void ClampViewRange(double& NewRangeMin, double& NewRangeMax);` — Clamp the given range to the clamp range @param NewRangeMin		The new lower bound of the range @param NewRangeMax		The new upper bound of the range
- L87 _public prototype_ `bool ZoomByDelta( float InDelta, float ZoomBias = 0.5f );` — Zoom the range by a given delta. @param InDelta		The total amount to zoom by (+ve = zoom out, -ve = zoom in) @param ZoomBias		Bias to apply to lower/upper extents of the range. (0 = lower, 0.5 = equal, 1 = upper)
- L94 _public prototype_ `void PanByDelta( float InDelta );` — Pan the range by a given delta @param InDelta		The total amount to pan by (+ve = pan forwards in time, -ve = pan backwards in time)
- L97 _public prototype_ `FFrameTime GetFrameTimeFromMouse(const FGeometry& Geometry, FVector2D ScreenSpacePosition) const;` — Determine frame time from a mouse position
- L110 _private prototype_ `void CommitScrubPosition( FFrameTime NewValue, bool bIsScrubbing );` — Call this method when the user's interaction has changed the scrub position @param NewValue				Value resulting from the user's interaction @param bIsScrubbing			True if done via scrubbing, false if just releasing scrubbing
- L120 _private prototype_ `void DrawTicks( FSlateWindowElementList& OutDrawElements, const TRange<double>& ViewRange, const FScrubRangeToScreen& RangeToScreen, FDrawTickArgs& InArgs ) const;` — Draw time tick marks @param OutDrawElements	List to add draw elements to @param ViewRange			The currently visible time range in seconds @param RangeToScreen		Time range to screen space converter @param InArgs			Parameters for drawing the tick lines
- L127 _private prototype_ `int32 DrawSelectionRange(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FScrubRangeToScreen& RangeToScreen, const FPaintPlaybackRangeArgs& Args) const;` — Draw the selection range. @return The new layer ID.
- L134 _private prototype_ `int32 DrawPlaybackRange(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FScrubRangeToScreen& RangeToScreen, const FPaintPlaybackRangeArgs& Args) const;` — Draw the playback range. @return the new layer ID
- L141 _private prototype_ `bool HitTestRangeStart(const FScrubRangeToScreen& RangeToScreen, const TRange<double>& Range, float HitPixel) const;` — Hit test the lower bound of a range
- L146 _private prototype_ `bool HitTestRangeEnd(const FScrubRangeToScreen& RangeToScreen, const TRange<double>& Range, float HitPixel) const;` — Hit test the upper bound of a range
- L151 _private prototype_ `bool HitTestTime(const FScrubRangeToScreen& RangeToScreen, double Time, float HitPixel) const;` — Hit test a time
- L157 _private prototype_ `int32 HitTestTimes(const FScrubRangeToScreen& RangeToScreen, float HitPixel) const;` — Hit test draggable times @return the index of the hit time, or INDEX_NONE if not hit
- L159 _private prototype_ `void SetPlaybackRangeStart(FFrameNumber NewStart);`
- L160 _private prototype_ `void SetPlaybackRangeEnd(FFrameNumber NewEnd);`
- L162 _private prototype_ `void SetSelectionRangeStart(FFrameNumber NewStart);`
- L163 _private prototype_ `void SetSelectionRangeEnd(FFrameNumber NewEnd);`
- L165 _private prototype_ `TSharedRef<SWidget> OpenSetPlaybackRangeMenu(FFrameNumber FrameNumber);`
- L166 _private prototype_ `FFrameTime ComputeFrameTimeFromMouse(const FGeometry& Geometry, FVector2D ScreenSpacePosition, FScrubRangeToScreen RangeToScreen, bool CheckSnapping = true) const;`
- L169 _private prototype_ `void ResetMouseDown(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent);` — Cache the state a mouse interaction starts from, shared by all mouse down entry points
- L180 _private prototype_ `FScrubPixelRange GetHitTestScrubberPixelRange(FFrameTime ScrubTime, const FScrubRangeToScreen& RangeToScreen) const;`
- L182 _private prototype_ `FScrubPixelRange GetScrubberPixelRange(FFrameTime ScrubTime, const FScrubRangeToScreen& RangeToScreen) const;`
- L183 _private prototype_ `FScrubPixelRange GetScrubberPixelRange(FFrameTime ScrubTime, FFrameRate Resolution, FFrameRate PlayRate, const FScrubRangeToScreen& RangeToScreen, float DilationPixels = 0.f) const;`
- L185 _private prototype_ `void SetEditableTime(int32 TimeIndex, float Time, bool bIsDragging);`
- L187 _private prototype_ `int32 DrawEditableTimes(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FScrubRangeToScreen& RangeToScreen) const;`
- L192 _private member_ `TWeakPtr<FAnimModel> WeakModel;` — Pointer back to the model object
- L195 _private member_ `TWeakPtr<SAnimTimeline> WeakTimeline;` — Pointer back to the timeline
- L197 _private member_ `FTimeSliderArgs TimeSliderArgs;`
- L200 _private member_ `const FSlateBrush* ScrubFillBrush;` — Brush for drawing the fill area on the scrubber
- L203 _private member_ `const FSlateBrush* ScrubHandleUpBrush;` — Brush for drawing an upwards facing scrub handles
- L206 _private member_ `const FSlateBrush* ScrubHandleDownBrush;` — Brush for drawing a downwards facing scrub handle
- L209 _private member_ `const FSlateBrush* EditableTimeBrush;` — Brush for drawing an editable time
- L212 _private member_ `float DistanceDragged;` — Total mouse delta during dragging
- L227 _private member_ `DragType MouseDragType;`
- L233 _private member_ `bool bMouseDownInTimeSlider;` — Whether the current mouse interaction started in the time slider. Only allow a click to set the time when it did - mouse events forwarded from the track area must leave the play head alone.
- L236 _private member_ `bool bPanning;` — If we are currently panning the panel
- L239 _private member_ `int32 DraggedTimeIndex;` — Index of the current dragged time
- L242 _private member_ `FVector2D MouseDownPosition[2];` — Mouse down position range
- L245 _private member_ `FGeometry MouseDownGeometry;` — Geometry on mouse down
- L248 _private member_ `TArray<TRange<double>> ViewRangeStack;` — Range stack
- L251 _private member_ `TSharedPtr<INumericTypeInterface<double>> SecondaryNumericTypeInterface;` — Secondary numeric type interface for displaying 'other' numeric types

#### struct `FAnimTimeSliderController::FScrubPixelRange`  
`struct FScrubPixelRange`  
_L173-178_
- L175 _public member_ `TRange<float> Range;`
- L176 _public member_ `TRange<float> HandleRange;`
- L177 _public member_ `bool bClamped;`

#### enum `FAnimTimeSliderController::DragType`  
`enum DragType`  
_L215-225_
- desc: If we are dragging a scrubber or dragging to set the time range
- L217 _public enumerator_ `DRAG_SCRUBBING_TIME`
- L218 _public enumerator_ `DRAG_SETTING_RANGE`
- L219 _public enumerator_ `DRAG_PLAYBACK_START`
- L220 _public enumerator_ `DRAG_PLAYBACK_END`
- L221 _public enumerator_ `DRAG_SELECTION_START`
- L222 _public enumerator_ `DRAG_SELECTION_END`
- L223 _public enumerator_ `DRAG_TIME`
- L224 _public enumerator_ `DRAG_NONE`

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineClipboard.h` (Private)


#### class `UAnimCurveBaseCopyObject`  
`class UAnimCurveBaseCopyObject : public UObject`  
_L20-63_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Object used to export AnimCurves to clipboard
- L26 _public prototype_ `UAnimCurveBaseCopyObject();`
- L31 _public member_ `FName CurveName;` — `UPROPERTY()`
- L34 _public member_ `ERawCurveTrackTypes CurveType;` — `UPROPERTY()`
- L37 _public member_ `ETransformCurveChannel Channel;` — `UPROPERTY()`
- L40 _public member_ `EVectorCurveChannel Axis;` — `UPROPERTY()`
- L46 _public member_ `FName OriginName;` — `UPROPERTY()` — This curve's data owner name (ex. UAnimSequenceBase Name), if any. Used internally to check if the user is attempting to paste curve data into source curve.
- L51 _public prototype_ `FAnimationCurveIdentifier GetAnimationCurveIdentifier() const;` — Get the information that identifies this curve
- L59 _public function_ `template<typename T> static T* Create()` — Create a copy object used to export  to clipboard @tparam T Curve copy object type to create @return Copy object for curve

#### class `UFloatCurveCopyObject`  
`class UFloatCurveCopyObject : public UAnimCurveBaseCopyObject`  
_L66-74_
- reflection: `UCLASS(Transient)`
- inherits: `UAnimCurveBaseCopyObject`
- L73 _public member_ `FFloatCurve Curve;` — `UPROPERTY()`

#### class `UTransformCurveCopyObject`  
`class UTransformCurveCopyObject : public UAnimCurveBaseCopyObject`  
_L77-85_
- reflection: `UCLASS(Transient)`
- inherits: `UAnimCurveBaseCopyObject`
- L84 _public member_ `FTransformCurve Curve;` — `UPROPERTY()`

#### class `UVectorCurveCopyObject`  
`class UVectorCurveCopyObject : public UAnimCurveBaseCopyObject`  
_L88-96_
- reflection: `UCLASS(Transient)`
- inherits: `UAnimCurveBaseCopyObject`
- L95 _public member_ `FVectorCurve Curve;` — `UPROPERTY()`

#### class `UAnimTimelineClipboardContent`  
`class UAnimTimelineClipboardContent : public UObject`  
_L103-122_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- L110 _public member_ `TArray<TObjectPtr<UAnimCurveBaseCopyObject>> Curves;` — `UPROPERTY(Export)` — Animation Timeline Editor Curves
- L115 _public prototype_ `bool AreAllCurvesOfTrackType(ERawCurveTrackTypes Type) const;` — Determine if all curve store in clipboard match the given Curve Track Type.
- L118 _public prototype_ `bool IsEmpty() const;` — Determine if clipboard content is empty.
- L121 _public prototype_ `static UAnimTimelineClipboardContent* Create();` — Create new clipboard content object

#### struct `FAnimTimelineClipboardUtilities`  
`struct FAnimTimelineClipboardUtilities`  
_L124-170_
- L129 _public prototype_ `static void CopyContentToClipboard(UAnimTimelineClipboardContent* Content);` — Copy anim timeline clipboard content to system's clipboard
- L132 _public prototype_ `static bool CanPasteContentToClipboard(const FString& TextToImport);` — Determine if a anim timeline clipboard content can be constructed from system's clipboard
- L135 _public prototype_ `static const UAnimTimelineClipboardContent* GetContentFromClipboard();` — Attempt to get the anim timeline clipboard content from system's clipboard.
- L145 _public prototype_ `static bool CopySelectedTracksToClipboard(const TSet<TSharedRef<FAnimTimelineTrack>>& CurveTracks, UAnimTimelineClipboardContent* ClipboardContent);` — Copy all the selected tracks into clipboard content. @param CurveTracks Selected Tracks in the Animation Timeline Editor @param ClipboardContent Clipboard object where data will be copied to @return True if any data was copied
- L154 _public prototype_ `static bool CanOverwriteSelectedCurveDataFromClipboard(const TSet<TSharedRef<FAnimTimelineTrack>>& SelectedTracks);` — Determine if curve data can be pasted into selected curve track data. @param SelectedTracks Selected Tracks in the Animation Timeline Editor @return Whether pasting is possible
- L162 _public prototype_ `static void OverwriteSelectedCurveDataFromClipboard(const UAnimTimelineClipboardContent* ClipboardContent, const TSet<TSharedRef<FAnimTimelineTrack>>& CurveTracks, UAnimSequenceBase* InTargetSequence);` — Overwrite curve data of the selected curve track with data from the clipboard without changing selected curve identifier. @param ClipboardContent Clipboard containing the curve(s) to be pasted @param CurveTracks Selected Tracks in the Animation Timeline Editor @param InTargetSequence Base Animation Sequence that will be modified
- L169 _public prototype_ `static void OverwriteOrAddCurvesFromClipboardContent(const UAnimTimelineClipboardContent* ClipboardContent, UAnimSequenceBase* InTargetSequence);` — Add or overwrite, if identifiers collide, all the curves from the clipboard object to the given Skeleton's and Controller's UAnimSequenceBase. @param ClipboardContent Clipboard containing the curves to be pasted @param InTargetSequence Base Animation Sequence that will be modified

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack.h` (Private)


#### struct `FAnimTrackPadding`  
`struct FAnimTrackPadding`  
_L21-42_
- desc: Structure used to define padding for a track
- L23 _public function_ `FAnimTrackPadding(float InUniform) : Top(InUniform) , Bottom(InUniform)`
- L27 _public function_ `FAnimTrackPadding(float InTop, float InBottom) : Top(InTop) , Bottom(InBottom)`
- L32 _public function_ `float Combined() const` — @return The sum total of the separate padding values
- L38 _public member_ `float Top;` — Padding to be applied to the top of the track
- L41 _public member_ `float Bottom;` — Padding to be applied to the bottom of the track

#### class `FAnimTimelineTrack`  
`class FAnimTimelineTrack : public TSharedFromThis<FAnimTimelineTrack>`  
_L69-242_
- inherits: `TSharedFromThis<FAnimTimelineTrack>`
- desc: Track to be displayed by the anim timeline
- L71 _private prototype_ `ANIMTIMELINE_DECLARE_BASE_TRACK(FAnimTimelineTrack);`
- L74 _public member_ `static const float OutlinerRightPadding;`
- L76 _public function_ `FAnimTimelineTrack(const FText& InDisplayName, const FText& InToolTipText, const TSharedPtr<FAnimModel>& InModel, bool bInIsHeaderTrack = false) : Model(InModel) , DisplayName(InDisplayName) , ToolTipText(InToolTipText) , Padding(0.0f) , Height(24.0f) , bIsHovered(false) , bIsVisible(true) , bIsExpanded(true) , bIsHeaderTrack(bInIsHeaderTrack)`
- L89 _public prototype_ `virtual ~FAnimTimelineTrack() = default;`
- L92 _public function_ `const TArray<TSharedRef<FAnimTimelineTrack>>& GetChildren()` — Get the children of this object
- L95 _public prototype_ `void AddChild(const TSharedRef<FAnimTimelineTrack>& InChild);` — Add a child track
- L98 _public function_ `void ClearChildren()` — Clear all child tracks
- L101 _public prototype_ `virtual FText GetLabel() const;` — Get the label to display
- L104 _public prototype_ `virtual FText GetToolTipText() const;` — Get the details text to display
- L107 _public function_ `TSharedRef<FAnimModel> GetModel() const` — Get the parent data model for this track
- L116 _public prototype_ `bool Traverse_ChildFirst(const TFunctionRef<bool(FAnimTimelineTrack&)>& InPredicate, bool bIncludeThisTrack = true);` — Iterate this entire track tree, child first. @param 	InPredicate			Predicate to call for each track, returning whether to continue iteration or not @param 	bIncludeThisTrack	Whether to include this track in the iteration, or just children @return  true where the client prematurely exited the iteration, false otherwise
- L125 _public prototype_ `bool Traverse_ParentFirst(const TFunctionRef<bool(FAnimTimelineTrack&)>& InPredicate, bool bIncludeThisTrack = true);` — Iterate this entire track tree, parent first. @param 	InPredicate			Predicate to call for each track, returning whether to continue iteration or not @param 	bIncludeThisTrack	Whether to include this track in the iteration, or just children @return  true where the client prematurely exited the iteration, false otherwise
- L134 _public prototype_ `bool TraverseVisible_ChildFirst(const TFunctionRef<bool(FAnimTimelineTrack&)>& InPredicate, bool bIncludeThisTrack = true);` — Iterate any visible portions of this track's sub-tree, child first. @param 	InPredicate			Predicate to call for each track, returning whether to continue iteration or not @param 	bIncludeThisTrack	Whether to include this track in the iteration, or just children @return  true where the client prematurely exited the iteration, false otherwise
- L143 _public prototype_ `bool TraverseVisible_ParentFirst(const TFunctionRef<bool(FAnimTimelineTrack&)>& InPredicate, bool bIncludeThisTrack = true);` — Iterate any visible portions of this track's sub-tree, parent first. @param 	InPredicate			Predicate to call for each track, returning whether to continue iteration or not @param 	bIncludeThisTrack	Whether to include this track in the iteration, or just children @return  true where the client prematurely exited the iteration, false otherwise
- L146 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForOutliner(const TSharedRef<SAnimOutlinerItem>& InRow);` — Generate a widget for the outliner for this track
- L149 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForTimeline();` — Generate a widget for the outliner for this track
- L152 _public prototype_ `virtual void AddToContextMenu(FMenuBuilder& InMenuBuilder, TSet<FName>& InOutExistingMenuTypes) const;` — Add items to the context menu
- L155 _public function_ `virtual float GetHeight() const` — Get the height of this track
- L158 _public function_ `void SetHeight(float InHeight)` — Set the height of this track
- L161 _public function_ `const FAnimTrackPadding& GetPadding() const` — Get the padding of this track
- L164 _public function_ `bool IsHovered() const` — Get whether this track is hovered
- L167 _public function_ `void SetHovered(bool bInIsHovered)` — Set whether this track is hovered
- L170 _public function_ `bool IsVisible() const` — Get whether this track is visible
- L173 _public function_ `void SetVisible(bool bInIsVisible)` — Set whether this track is visible
- L176 _public function_ `bool IsExpanded() const` — Get whether this track is expanded
- L179 _public function_ `void SetExpanded(bool bInIsExpanded)` — Set whether this track is expanded
- L182 _public function_ `virtual bool SupportsSelection() const` — Get whether this track supports selection in the outliner
- L185 _public function_ `virtual bool SupportsFiltering() const` — Get whether this track supports filtering in the outliner
- L188 _public function_ `virtual bool SupportsCopy() const` — Get whether this track supports copying to the clipboard
- L191 _public function_ `virtual void Copy(UAnimTimelineClipboardContent* InOutClipboard) const` — Copy track information to clipboard
- L194 _public function_ `virtual bool CanRename() const` — Get whether this track can be renamed
- L197 _public function_ `virtual void RequestRename()` — Request this track be renamed
- L201 _protected prototype_ `TSharedRef<SWidget> GenerateStandardOutlinerWidget(const TSharedRef<SAnimOutlinerItem>& InRow, bool bWithLabelText, TSharedPtr<SBorder>& OutOuterBorder, TSharedPtr<SHorizontalBox>& OutInnerHorizontalBox);` — Generate an outliner widget
- L204 _protected function_ `float GetMinInput() const`
- L205 _protected prototype_ `float GetMaxInput() const;`
- L206 _protected prototype_ `float GetViewMinInput() const;`
- L207 _protected prototype_ `float GetViewMaxInput() const;`
- L208 _protected prototype_ `float GetScrubValue() const;`
- L209 _protected prototype_ `void SelectObjects(const TArray<UObject*>& SelectedItems);`
- L210 _protected prototype_ `void OnSetInputViewRange(float ViewMin, float ViewMax);`
- L214 _protected member_ `TArray<TSharedRef<FAnimTimelineTrack>> Children;` — Child objects
- L217 _protected member_ `TWeakPtr<FAnimModel> Model;` — The parent model
- L220 _protected member_ `FText DisplayName;` — Display name to use
- L223 _protected member_ `FText ToolTipText;` — Tooltip text to use
- L226 _protected member_ `FAnimTrackPadding Padding;` — The padding of the track
- L229 _protected member_ `float Height;` — The height of the track
- L232 _protected member_ `bool bIsHovered : 1;` — Whether this track is hovered
- L235 _protected member_ `bool bIsVisible : 1;` — Whether this track is visible
- L238 _protected member_ `bool bIsExpanded : 1;` — Whether this track is expanded
- L241 _protected member_ `bool bIsHeaderTrack : 1;` — Whether this is a header track

#### Free symbols / members of external scopes

- L45 _macro_ `#define ANIMTIMELINE_DECLARE_BASE_TRACK(BaseClassName) \` — Simple RTTI implementation for tracks
- L56 _macro_ `#define ANIMTIMELINE_DECLARE_TRACK(ClassName, BaseClassName) \`
- L65 _macro_ `#define ANIMTIMELINE_IMPLEMENT_TRACK(ClassName) \`

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_Attribute.h` (Private)


#### class `FAnimTimelineTrack_Attribute`  
`class FAnimTimelineTrack_Attribute : public FAnimTimelineTrack`  
_L10-25_
- inherits: `FAnimTimelineTrack`
- desc: Animation timeline track inserted for each animated attribute (inserted as child of FAnimTimelineTrack_PerBoneAttributes)
- L12 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_Attribute, FAnimTimelineTrack);`
- L15 _public prototype_ `FAnimTimelineTrack_Attribute(const FAnimatedBoneAttribute& InAttribute, const TSharedRef<FAnimModel>& InModel);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForOutliner(const TSharedRef<SAnimOutlinerItem>& InRow) override;` — FAnimTimelineTrack interface
- L19 _public prototype_ `virtual FText GetLabel() const override;`
- L20 _public prototype_ `virtual FText GetToolTipText() const override;`
- L23 _private member_ `const FAnimatedBoneAttribute& Attribute;`
- L24 _private member_ `TSharedPtr<SWidget> OutlinerWidget;`

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_Attributes.h` (Private)


#### class `FAnimTimelineTrack_Attributes`  
`class FAnimTimelineTrack_Attributes : public FAnimTimelineTrack`  
_L8-20_
- inherits: `FAnimTimelineTrack`
- desc: Root-level animation timeline track under which per-bone animated attributes are inserted
- L10 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_Attributes, FAnimTimelineTrack);`
- L13 _public prototype_ `FAnimTimelineTrack_Attributes(const TSharedRef<FAnimModel>& InModel);`
- L16 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForOutliner(const TSharedRef<SAnimOutlinerItem>& InRow) override;` — FAnimTimelineTrack interface
- L19 _private member_ `TSharedPtr<SWidget> OutlinerWidget;`

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_CompositePanel.h` (Private)


#### class `FAnimTimelineTrack_CompositeRoot`  
`class FAnimTimelineTrack_CompositeRoot : public FAnimTimelineTrack`  
_L10-16_
- inherits: `FAnimTimelineTrack`
- L12 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_CompositeRoot, FAnimTimelineTrack);`
- L15 _public prototype_ `FAnimTimelineTrack_CompositeRoot(const TSharedPtr<FAnimModel>& InModel);`

#### class `FAnimTimelineTrack_CompositePanel`  
`class FAnimTimelineTrack_CompositePanel : public FAnimTimelineTrack`  
_L19-35_
- inherits: `FAnimTimelineTrack`
- desc: A timeline track that re-uses the legacy panel widget to display anim composite sections
- L21 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_CompositePanel, FAnimTimelineTrack);`
- L24 _public prototype_ `FAnimTimelineTrack_CompositePanel(const TSharedRef<FAnimModel>& InModel);`
- L27 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForTimeline() override;` — FAnimTimelineTrack interface
- L28 _public function_ `virtual bool SupportsFiltering() const override`
- L30 _public function_ `TSharedPtr<SAnimCompositePanel> GetAnimCompositePanel()`
- L34 _private member_ `TSharedPtr<SAnimCompositePanel> AnimCompositePanel;` — The legacy composite panel

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_CompoundCurve.h` (Private)


#### class `FAnimTimelineTrack_CompoundCurve`  
`class FAnimTimelineTrack_CompoundCurve : public FAnimTimelineTrack_Curve`  
_L12-40_
- inherits: `FAnimTimelineTrack_Curve`
- desc: \brief Tree view of a group of float curves, use AddGroupedCurveTracks(FloatCurves, ...) to create a tree view for curves
- L14 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_CompoundCurve, FAnimTimelineTrack_Curve);`
- L17 _public prototype_ `FAnimTimelineTrack_CompoundCurve(TArray<const FFloatCurve*> InCurves, const FText& InCurveName, const FText& InFullCurveName, const FLinearColor& InBackgroundColor, const TSharedRef<FAnimModel>& InModel);`
- L20 _public prototype_ `virtual FLinearColor GetCurveColor(int32 InCurveIndex) const override;` — FAnimTimelineTrack_Curve interface
- L21 _public prototype_ `virtual FText GetFullCurveName(int32 InCurveIndex) const override;`
- L22 _public prototype_ `virtual bool CanEditCurve(int32 InCurveIndex) const override;`
- L23 _public prototype_ `virtual void GetCurveEditInfo(int32 InCurveIndex, FName& OutName, ERawCurveTrackTypes& OutType, int32& OutCurveIndex) const override;`
- L26 _public member_ `static constexpr auto DefaultDelimiters = TEXT("._/`
- L31 _public prototype_ `static void AddGroupedCurveTracks(TArrayView<const FFloatCurve> FloatCurves, FAnimTimelineTrack& ParentTrack, const TSharedRef<FAnimModel>& InModel, FStringView Delimiters = DefaultDelimiters);` — \brief Add grouped view curve tracks for a list of curves named like 'A.B.C' \param[in] FloatCurves The curves to display \param[inout] ParentTrack The parent track to add the curves, typically a FAnimTimelineTrack_Curve \param[in] InModel FAnimModel to display the track
- L33 _public function_ `const TArray<FName>& GetCurveNames() const`
- L35 _private member_ `TArray<const FFloatCurve*> Curves;`
- L36 _private member_ `TArray<FName> CurveNames;` — Curve names used when removing curves (in case the FFloatCurve was removed)
- L38 _private prototype_ `static TArray<const FRichCurve*> ToRichCurves(TArrayView<FFloatCurve const* const> InCurves);`

#### class `FAnimTimelineTrack_FloatCurveWithDisplayName`  
`class FAnimTimelineTrack_FloatCurveWithDisplayName : public FAnimTimelineTrack_FloatCurve`  
_L43-51_
- inherits: `FAnimTimelineTrack_FloatCurve`
- desc: FloatCurve with customizable display name, e.g. showing "C" for curve "A.B.C"
- L45 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_FloatCurveWithDisplayName, FAnimTimelineTrack_FloatCurve);`
- L48 _public prototype_ `FAnimTimelineTrack_FloatCurveWithDisplayName(const FFloatCurve* InCurve, FText InDisplayName, const TSharedRef<FAnimModel>& InModel);`
- L49 _public prototype_ `virtual FText GetLabel() const override;`
- L50 _public prototype_ `virtual bool ShowCurves() const override;`

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_Curve.h` (Private)


#### class `FAnimTimelineTrack_Curve`  
`class FAnimTimelineTrack_Curve : public FAnimTimelineTrack, public FSelfRegisteringEditorUndoClient`  
_L17-122_
- inherits: `FAnimTimelineTrack,FSelfRegisteringEditorUndoClient`
- L19 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_Curve, FAnimTimelineTrack);`
- L22 _public prototype_ `FAnimTimelineTrack_Curve(const FText& InCurveName, const FText& InFullCurveName, const FLinearColor& InColor, const FLinearColor& InBackgroundColor, const TSharedRef<FAnimModel>& InModel);`
- L23 _public prototype_ `FAnimTimelineTrack_Curve(const FRichCurve* InCurve, const FName& InName, int32 InCurveIndex, ERawCurveTrackTypes InType, const FText& InCurveName, const FText& InFullCurveName, const FLinearColor& InColor, const FLinearColor& InBackgroundColor, const TSharedRef<FAnimModel>& InModel);`
- L24 _public prototype_ `FAnimTimelineTrack_Curve(const TArray<const FRichCurve*>& InCurves, const FText& InCurveName, const FText& InFullCurveName, const FLinearColor& InColor, const FLinearColor& InBackgroundColor, const TSharedRef<FAnimModel>& InModel);`
- L27 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForTimeline() override;` — FAnimTimelineTrack interface
- L28 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForOutliner(const TSharedRef<SAnimOutlinerItem>& InRow) override;`
- L29 _public function_ `virtual bool SupportsSelection() const override`
- L30 _public prototype_ `virtual void AddToContextMenu(FMenuBuilder& InMenuBuilder, TSet<FName>& InOutExistingMenuTypes) const override;`
- L31 _public function_ `virtual bool SupportsCopy() const override`
- L32 _public prototype_ `virtual void Copy(UAnimTimelineClipboardContent* InOutClipboard) const override;`
- L35 _public function_ `virtual void PostUndo(bool bSuccess) override` — FEditorUndoClient interface
- L36 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L39 _public function_ `const TArray<const FRichCurve*>& GetCurves() const` — Access the curve we are editing
- L42 _public prototype_ `virtual FLinearColor GetCurveColor(int32 InCurveIndex) const;` — Get a color for the curve widget (and edited curves)
- L45 _public function_ `virtual bool CanEditCurve(int32 InCurveIndex) const` — Get whether a specified curve can be edited
- L48 _public function_ `virtual FText GetFullCurveName(int32 InCurveIndex) const` — Get the name of the curve when edited (includes path, e.g. BoneName.Translation.X)
- L51 _public prototype_ `virtual void GetCurveEditInfo(int32 InCurveIndex, FName& OutName, ERawCurveTrackTypes& OutType, int32& OutCurveIndex) const;` — Get the information needed to reference this curve for editing
- L55 _public function_ `virtual void GetCurveEditInfo(int32 InCurveIndex, FSmartName& OutName, ERawCurveTrackTypes& OutType, int32& OutCurveIndex) const` — `UE_DEPRECATED(5.3, "Please use GetCurveEditInfo that takes a FName.")`
- L59 _public prototype_ `void HandleCurveChanged();` — Delegate handing curve changing externally
- L63 _protected prototype_ `virtual TSharedRef<SWidget> MakeTimelineWidgetContainer();` — Make the container (border) widget for the curve timeline
- L66 _protected prototype_ `virtual TSharedRef<SWidget> MakeCurveWidget();` — Make the curve widget itself
- L69 _protected prototype_ `virtual TSharedRef<SWidget> BuildCurveTrackMenu();` — Build the track menu for this curve
- L72 _protected prototype_ `virtual void AddCurveTrackButton(TSharedPtr<SHorizontalBox> InnerHorizontalBox);` — Helper function for building outliner widget
- L75 _protected prototype_ `virtual bool ShowCurves() const;` — Should this track draw its curves, by default, hide curves in parent tracks when children are expanded.
- L78 _protected prototype_ `FReply HandleDoubleClicked(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent);` — Edit this curve when double clicked
- L81 _protected prototype_ `FReply HandleMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent);` — Push a popup menu when we right-click
- L84 _protected prototype_ `void HendleEditCurve();` — Edit this curve in the curve editor
- L87 _protected prototype_ `void PostUndoRedo();` — Handle undo/redo
- L90 _protected prototype_ `void ZoomToFit();` — Zoom the view to fit the bounds of the curve
- L94 _protected member_ `TArray<const FRichCurve*> Curves;` — The curve we are editing
- L97 _protected member_ `FLinearColor Color;` — The color of the curve
- L100 _protected member_ `FLinearColor BackgroundColor;` — The color of the curve background
- L103 _protected member_ `FText FullCurveName;` — Name of the curve when edited (includes path, e.g. BoneName.Translation.X)
- L106 _protected member_ `FName OuterCurveName;` — The name of the outer curve
- L109 _protected member_ `int32 OuterCurveIndex;` — The index into the outer curve
- L112 _protected member_ `ERawCurveTrackTypes OuterType;` — The type of this curves outer (currently always RCT_Transform)
- L115 _protected member_ `TSharedPtr<SBorder> TimelineWidgetContainer;` — Container widget for timeline
- L118 _protected member_ `TSharedPtr<FCurveEditor> CurveEditor;` — Curve editor
- L121 _protected member_ `TSharedPtr<SCurveBoundsOverlay> CurveOverlay;` — Overlay widget used to display bounds

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_Curves.h` (Private)


#### class `FAnimTimelineTrack_Curves`  
`class FAnimTimelineTrack_Curves : public FAnimTimelineTrack`  
_L10-47_
- inherits: `FAnimTimelineTrack`
- L12 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_Curves, FAnimTimelineTrack);`
- L15 _public prototype_ `FAnimTimelineTrack_Curves(const TSharedRef<FAnimModel>& InModel);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForOutliner(const TSharedRef<SAnimOutlinerItem>& InRow) override;` — FAnimTimelineTrack interface
- L21 _private prototype_ `TSharedRef<SWidget> BuildCurvesSubMenu();`
- L22 _private prototype_ `void FillMetadataEntryMenu(FMenuBuilder& Builder);`
- L23 _private prototype_ `void FillVariableCurveMenu(FMenuBuilder& Builder);`
- L24 _private prototype_ `void AddMetadataEntry(const FName& InCurveName);`
- L25 _private prototype_ `void CreateNewMetadataEntryClicked();`
- L26 _private prototype_ `void CreateNewMetadataEntry(const FText& CommittedText, ETextCommit::Type CommitType);`
- L27 _private prototype_ `void CreateNewCurveClicked();`
- L28 _private prototype_ `void CreateTrack(const FText& ComittedText, ETextCommit::Type CommitInfo);`
- L29 _private prototype_ `void AddVariableCurve(const FName& InCurveName);`
- L30 _private prototype_ `void DeleteAllCurves();`
- L33 _private prototype_ `void HandleShowCurvePoints();` — Handlers for showing curve points
- L34 _private prototype_ `bool IsShowCurvePointsEnabled() const;`
- L37 _private prototype_ `void HandleUseTreeView();` — Handlers for switching to and from tree view
- L38 _private prototype_ `bool IsUseTreeViewEnabled() const;`
- L41 _private prototype_ `void OnMetadataCurveNamePicked(const FName& InCurveName);` — Curve Picker Callbacks
- L42 _private prototype_ `void OnVariableCurveNamePicked(const FName& InCurveName);`
- L43 _private prototype_ `bool IsCurveMarkedForExclusion(const FName& InCurveName);`
- L46 _private member_ `TSharedPtr<SWidget> OutlinerWidget;`

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_FloatCurve.h` (Private)


#### class `FAnimTimelineTrack_FloatCurve`  
`class FAnimTimelineTrack_FloatCurve : public FAnimTimelineTrack_Curve`  
_L11-75_
- inherits: `FAnimTimelineTrack_Curve`
- L13 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_FloatCurve, FAnimTimelineTrack_Curve);`
- L16 _public prototype_ `FAnimTimelineTrack_FloatCurve(const FFloatCurve* InCurve, const TSharedRef<FAnimModel>& InModel);`
- L19 _public prototype_ `virtual TSharedRef<SWidget> MakeTimelineWidgetContainer() override;` — FAnimTimelineTrack_Curve interface
- L20 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForOutliner(const TSharedRef<SAnimOutlinerItem>& InRow) override;`
- L21 _public prototype_ `virtual TSharedRef<SWidget> BuildCurveTrackMenu() override;`
- L22 _public prototype_ `virtual FText GetLabel() const override;`
- L23 _public prototype_ `virtual bool CanEditCurve(int32 InCurveIndex) const override;`
- L24 _public function_ `virtual bool CanRename() const override`
- L25 _public prototype_ `virtual void RequestRename() override;`
- L26 _public prototype_ `virtual void AddCurveTrackButton(TSharedPtr<SHorizontalBox> InnerHorizontalBox) override;`
- L27 _public prototype_ `virtual FLinearColor GetCurveColor(int32 InCurveIndex) const override;`
- L28 _public prototype_ `virtual void GetCurveEditInfo(int32 InCurveIndex, FName& OutName, ERawCurveTrackTypes& OutType, int32& OutCurveIndex) const override;`
- L29 _public function_ `virtual bool SupportsCopy() const override`
- L30 _public prototype_ `virtual void Copy(UAnimTimelineClipboardContent* InOutClipboard) const override;`
- L31 _public prototype_ `virtual float GetHeight() const override;`
- L34 _public function_ `const FFloatCurve* GetFloatCurve()` — Access the curve we are editing
- L37 _public function_ `FName GetFName() const` — Get this curves name
- L40 _private prototype_ `void ConvertCurveToMetaData();`
- L41 _private prototype_ `void ConvertMetaDataToCurve();`
- L42 _private prototype_ `void RemoveCurve();`
- L43 _private prototype_ `void OnCommitCurveName(const FText& InText, ETextCommit::Type CommitInfo);`
- L44 _private prototype_ `float GetCommentHeight() const;`
- L45 _private prototype_ `FOptionalSize GetCommentSize() const;`
- L46 _private prototype_ `void HandleAddComment();`
- L47 _private prototype_ `void OnCommitCurveComment(const FText& InText, ETextCommit::Type CommitInfo);`
- L48 _private prototype_ `FText GetCommentText() const;`
- L49 _private prototype_ `EVisibility GetCommentVisibility() const;`
- L50 _private prototype_ `bool IsSelected() const;`
- L51 _private prototype_ `FSlateColor GetTrackColor(bool bForComment) const;`
- L55 _private member_ `const FFloatCurve* FloatCurve;` — The curve we are editing
- L58 _private member_ `FName CurveName;` — The curve name and identifier
- L59 _private member_ `FAnimationCurveIdentifier CurveId;`
- L62 _private member_ `FLinearColor Color;` — Cached color
- L65 _private member_ `FString Comment;` — Cached comment
- L68 _private member_ `bool bIsMetadata = false;` — Cached metadata flag
- L71 _private member_ `TSharedPtr<SInlineEditableTextBlock> EditableTextLabel;` — Label we can edit
- L74 _private member_ `TSharedPtr<SInlineEditableTextBlock> EditableTextComment;` — Comment we can edit

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_Montage.h` (Private)


#### class `FAnimTimelineTrack_Montage`  
`class FAnimTimelineTrack_Montage : public FAnimTimelineTrack`  
_L12-40_
- inherits: `FAnimTimelineTrack`
- desc: Header track for montage information
- L14 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_Montage, FAnimTimelineTrack);`
- L17 _public prototype_ `FAnimTimelineTrack_Montage(const TSharedRef<FAnimModel_AnimMontage>& InModel);`
- L20 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForOutliner(const TSharedRef<SAnimOutlinerItem>& InRow) override;` — FAnimTimelineTrack interface
- L21 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForTimeline() override;`
- L22 _public prototype_ `virtual FText GetLabel() const override;`
- L23 _public prototype_ `virtual FText GetToolTipText() const override;`
- L24 _public function_ `virtual bool SupportsFiltering() const override`
- L26 _public prototype_ `TSharedRef<SWidget> BuildMontageSubMenu();`
- L28 _public prototype_ `void OnFindParentClassInContentBrowserClicked();`
- L30 _public prototype_ `void OnEditParentClassClicked();`
- L32 _public function_ `void SetMontagePanel(const TSharedRef<FAnimTimelineTrack_MontagePanel>& InMontagePanel)`
- L35 _private prototype_ `void OnShowSectionTiming();`
- L36 _private prototype_ `bool IsShowSectionTimingEnabled() const;`
- L39 _private member_ `TWeakPtr<FAnimTimelineTrack_MontagePanel> MontagePanel;`

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_MontagePanel.h` (Private)


#### class `FAnimTimelineTrack_MontagePanel`  
`class FAnimTimelineTrack_MontagePanel : public FAnimTimelineTrack`  
_L12-58_
- inherits: `FAnimTimelineTrack`
- desc: A timeline track that re-uses the legacy panel widget to display anim montages
- L14 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_MontagePanel, FAnimTimelineTrack);`
- L17 _public prototype_ `FAnimTimelineTrack_MontagePanel(const TSharedRef<FAnimModel>& InModel);`
- L20 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForTimeline() override;` — FAnimTimelineTrack interface
- L21 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForOutliner(const TSharedRef<SAnimOutlinerItem>& InRow) override;`
- L22 _public function_ `virtual bool SupportsFiltering() const override`
- L24 _public prototype_ `TSharedRef<SAnimMontagePanel> GetAnimMontagePanel();`
- L26 _public prototype_ `TSharedRef<SWidget> BuildMontageSlotSubMenu(int32 InSlotIndex);`
- L28 _public prototype_ `void BuildSlotNameMenu(FMenuBuilder& InMenuBuilder, int32 InSlotIndex);`
- L30 _public prototype_ `void RefreshOutlinerWidget();`
- L32 _public prototype_ `void OnSetSlotName(FName InName, int32 InSlotIndex);`
- L34 _public prototype_ `bool IsSlotNameSet(FName InName, int32 InSlotIndex);`
- L36 _public prototype_ `EVisibility GetSlotWarningVisibility(int32 InSlotIndex) const;`
- L38 _public prototype_ `FText GetSlotWarningText(int32 InSlotIndex) const;`
- L40 _public prototype_ `void UpdateSlotGroupWarning();`
- L44 _private member_ `TSharedPtr<SAnimMontagePanel> AnimMontagePanel;` — The legacy montage panel
- L47 _private member_ `TSharedPtr<SVerticalBox> OutlinerWidget;` — The outliner widget to allow for dynamic refresh
- L57 _private member_ `TArray<FSlotWarningInfo> WarningInfo;` — Cached warning info for all slots

#### struct `FAnimTimelineTrack_MontagePanel::FSlotWarningInfo`  
`struct FSlotWarningInfo`  
_L50-54_
- desc: Cached info about a slot warning
- L52 _public member_ `FText WarningText;`
- L53 _public member_ `bool bWarning;`

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_Notifies.h` (Private)


#### class `FAnimTimelineTrack_Notifies`  
`class FAnimTimelineTrack_Notifies : public FAnimTimelineTrack`  
_L10-37_
- inherits: `FAnimTimelineTrack`
- L12 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_Notifies, FAnimTimelineTrack);`
- L15 _public prototype_ `FAnimTimelineTrack_Notifies(const TSharedRef<FAnimModel>& InModel);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForOutliner(const TSharedRef<SAnimOutlinerItem>& InRow) override;` — FAnimTimelineTrack interface
- L21 _public prototype_ `static FName GetNewTrackName(UAnimSequenceBase* InAnimSequenceBase);` — Get a new, unused track name using the specified anim sequence
- L23 _public function_ `void SetAnimNotifyPanel(const TSharedRef<FAnimTimelineTrack_NotifiesPanel>& InNotifiesPanel)`
- L26 _public prototype_ `EVisibility OnGetTimingNodeVisibility(ENotifyTimingElementType::Type InType) const;` — Controls timing visibility for notify tracks
- L30 _private prototype_ `TSharedRef<SWidget> BuildNotifiesSubMenu();` — Populate the track menu
- L33 _private prototype_ `void AddTrack();` — Add a new track
- L36 _private member_ `TWeakPtr<FAnimTimelineTrack_NotifiesPanel> NotifiesPanel;` — The legacy notifies panel we are linked to

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_NotifiesPanel.h` (Private)


#### class `FAnimTimelineTrack_NotifiesPanel`  
`class FAnimTimelineTrack_NotifiesPanel : public FAnimTimelineTrack`  
_L14-57_
- inherits: `FAnimTimelineTrack`
- desc: A timeline track that re-uses the legacy panel widget to display notifies
- L16 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_NotifiesPanel, FAnimTimelineTrack);`
- L19 _public member_ `static const float NotificationTrackHeight;`
- L20 _public member_ `static const FName AnimationEditorStatusBarName;`
- L22 _public prototype_ `FAnimTimelineTrack_NotifiesPanel(const TSharedRef<FAnimModel>& InModel);`
- L25 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForTimeline() override;` — FAnimTimelineTrack interface
- L26 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForOutliner(const TSharedRef<SAnimOutlinerItem>& InRow) override;`
- L27 _public function_ `virtual bool SupportsFiltering() const override`
- L29 _public prototype_ `TSharedRef<SAnimNotifyPanel> GetAnimNotifyPanel();`
- L31 _public prototype_ `void Update();`
- L34 _public function_ `void RequestTrackRename(int32 InTrackIndex)` — Request a rename next update
- L37 _private prototype_ `TSharedRef<SWidget> BuildNotifiesPanelSubMenu(int32 InTrackIndex);`
- L38 _private prototype_ `void InsertTrack(int32 InTrackIndexToInsert);`
- L39 _private prototype_ `void RemoveTrack(int32 InTrackIndexToRemove);`
- L40 _private prototype_ `void RefreshOutlinerWidget();`
- L41 _private prototype_ `void OnCommitTrackName(const FText& InText, ETextCommit::Type CommitInfo, int32 TrackIndexToName);`
- L42 _private prototype_ `EVisibility OnGetTimingNodeVisibility(ENotifyTimingElementType::Type ElementType) const;`
- L43 _private prototype_ `EActiveTimerReturnType HandlePendingRenameTimer(double InCurrentTime, float InDeltaTime, TWeakPtr<SInlineEditableTextBlock> InInlineEditableTextBlock);`
- L44 _private prototype_ `void HandleNotifyChanged();`
- L47 _private member_ `TSharedPtr<SAnimNotifyPanel> AnimNotifyPanel;` — The legacy notify panel
- L50 _private member_ `TSharedPtr<SVerticalBox> OutlinerWidget;` — The outliner widget to allow for dynamic refresh
- L53 _private member_ `int32 PendingRenameTrackIndex;` — Track index we want to trigger a rename for
- L56 _private member_ `FStatusBarMessageHandle StatusBarMessageHandle;` — Handle to status bar message

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_PerBoneAttributes.h` (Private)


#### class `FAnimTimelineTrack_PerBoneAttributes`  
`class FAnimTimelineTrack_PerBoneAttributes : public FAnimTimelineTrack`  
_L8-23_
- inherits: `FAnimTimelineTrack`
- desc: Animation timeline track inserted for each unique bone containing animated attributes (inserted as child of FAnimTimelineTrack_Attributes)
- L10 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_PerBoneAttributes, FAnimTimelineTrack);`
- L13 _public prototype_ `FAnimTimelineTrack_PerBoneAttributes(const FName& InBoneName, const TSharedRef<FAnimModel>& InModel);`
- L16 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForOutliner(const TSharedRef<SAnimOutlinerItem>& InRow) override;` — FAnimTimelineTrack interface
- L17 _public prototype_ `virtual FText GetLabel() const override;`
- L18 _public prototype_ `virtual FText GetToolTipText() const override;`
- L21 _private member_ `FName BoneName;`
- L22 _private member_ `TSharedPtr<SWidget> OutlinerWidget;`

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_TimingPanel.h` (Private)


#### class `FAnimTimelineTrack_TimingPanel`  
`class FAnimTimelineTrack_TimingPanel : public FAnimTimelineTrack`  
_L12-31_
- inherits: `FAnimTimelineTrack`
- desc: A timeline track that re-uses the legacy panel widget to display anim timing panel
- L14 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_TimingPanel, FAnimTimelineTrack);`
- L17 _public prototype_ `FAnimTimelineTrack_TimingPanel(const TSharedRef<FAnimModel_AnimMontage>& InModel);`
- L20 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForTimeline() override;` — FAnimTimelineTrack interface
- L21 _public prototype_ `virtual TSharedRef<SWidget> GenerateContainerWidgetForOutliner(const TSharedRef<SAnimOutlinerItem>& InRow) override;`
- L22 _public function_ `virtual bool SupportsFiltering() const override`
- L24 _public function_ `TSharedPtr<SAnimTimingPanel> GetAnimTimingPanel()`
- L27 _private prototype_ `TSharedRef<SWidget> BuildTimingSubMenu();`
- L30 _private member_ `TSharedPtr<SAnimTimingPanel> AnimTimingPanel;` — The legacy timing panel

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_TransformCurve.h` (Private)


#### class `FAnimTimelineTrack_TransformCurve`  
`class FAnimTimelineTrack_TransformCurve : public FAnimTimelineTrack_Curve`  
_L11-49_
- inherits: `FAnimTimelineTrack_Curve`
- L13 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_TransformCurve, FAnimTimelineTrack_Curve);`
- L16 _public prototype_ `FAnimTimelineTrack_TransformCurve(const FTransformCurve* InCurve, const TSharedRef<FAnimModel>& InModel);`
- L19 _public prototype_ `virtual FLinearColor GetCurveColor(int32 InCurveIndex) const override;` — FAnimTimelineTrack_Curve interface
- L20 _public prototype_ `virtual FText GetFullCurveName(int32 InCurveIndex) const override;`
- L21 _public prototype_ `virtual TSharedRef<SWidget> BuildCurveTrackMenu() override;`
- L22 _public function_ `virtual bool CanEditCurve(int32 InCurveIndex) const override`
- L23 _public prototype_ `virtual void GetCurveEditInfo(int32 InCurveIndex, FName& OutName, ERawCurveTrackTypes& OutType, int32& OutCurveIndex) const override;`
- L24 _public function_ `virtual bool SupportsCopy() const override`
- L25 _public prototype_ `virtual void Copy(UAnimTimelineClipboardContent* InOutClipboard) const override;`
- L28 _public function_ `const FTransformCurve& GetTransformCurve()` — Access the curve we are editing
- L30 _public function_ `FName GetFName() const`
- L34 _private prototype_ `void DeleteTrack();` — Delete this track via the track menu
- L37 _private prototype_ `bool IsEnabled() const;` — Show enabled state in the menu
- L40 _private prototype_ `void ToggleEnabled();` — Toggle enabled state via the menu
- L44 _private member_ `const FTransformCurve* TransformCurve;` — The curve we are editing
- L47 _private member_ `FName CurveName;` — The curve name and identifier
- L48 _private member_ `FAnimationCurveIdentifier CurveId;`

### `Source/Editor/Persona/Private/AnimTimeline/AnimTimelineTrack_VectorCurve.h` (Private)


#### class `FAnimTimelineTrack_VectorCurve`  
`class FAnimTimelineTrack_VectorCurve : public FAnimTimelineTrack_Curve`  
_L11-30_
- inherits: `FAnimTimelineTrack_Curve`
- L13 _private prototype_ `ANIMTIMELINE_DECLARE_TRACK(FAnimTimelineTrack_VectorCurve, FAnimTimelineTrack_Curve);`
- L16 _public prototype_ `FAnimTimelineTrack_VectorCurve(const FVectorCurve* InCurve, const FName& InName, int32 InCurveIndex, ERawCurveTrackTypes InType, const FText& InCurveName, const FText& InFullCurveName, const FLinearColor& InColor, const TSharedRef<FAnimModel>& InModel);`
- L19 _public prototype_ `virtual FLinearColor GetCurveColor(int32 InCurveIndex) const override;` — FAnimTimelineTrack_Curve interface
- L20 _public prototype_ `virtual FText GetFullCurveName(int32 InCurveIndex) const override;`
- L21 _public function_ `virtual bool CanEditCurve(int32 InCurveIndex) const override`
- L22 _public prototype_ `virtual void GetCurveEditInfo(int32 InCurveIndex, FName& OutName, ERawCurveTrackTypes& OutType, int32& OutCurveIndex) const override;`
- L25 _public function_ `const FVectorCurve& GetVectorCurve()` — Access the curve we are editing
- L29 _private member_ `const FVectorCurve* VectorCurve;` — The curve we are editing

### `Source/Editor/Persona/Private/AnimTimeline/SAnimOutliner.h` (Private)


#### class `SAnimOutliner`  
`class SAnimOutliner : public STreeView<TSharedRef<FAnimTimelineTrack>>`  
_L23-130_
- inherits: `STreeView<TSharedRef<FAnimTimelineTrack>>`
- L26 _public function_ `SLATE_BEGIN_ARGS(SAnimOutliner)`
- L29 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SScrollBar>, ExternalScrollbar) SLATE_EVENT(FOnGetContextMenuContent, OnGetContextMenuContent) SLATE_ATTRIBUTE(FText, FilterText) SLATE_END_ARGS() ~SAnimOutliner();` — Externally supplied scroll bar
- L41 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FAnimModel>& InAnimModel, const TSharedRef<SAnimTrackArea>& InTrackArea);`
- L44 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);` — SWidget interface
- L45 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const;`
- L48 _public prototype_ `virtual void Private_SetItemSelection( TSharedRef<FAnimTimelineTrack> TheItem, bool bShouldBeSelected, bool bWasUserDirected = false ) override;` — STreeView interface
- L49 _public prototype_ `virtual void Private_ClearSelection() override;`
- L50 _public prototype_ `virtual void Private_SelectRangeFromCurrentTo( TSharedRef<FAnimTimelineTrack> InRangeSelectionEnd ) override;`
- L67 _public prototype_ `TOptional<FCachedGeometry> GetCachedGeometryForTrack(const TSharedRef<FAnimTimelineTrack>& InTrack) const;` — Get the cached geometry for the specified track
- L70 _public prototype_ `TOptional<float> ComputeTrackPosition(const TSharedRef<FAnimTimelineTrack>& InTrack) const;` — Compute the position of the specified track using its cached geometry
- L73 _public prototype_ `void ReportChildRowGeometry(const TSharedRef<FAnimTimelineTrack>& InTrack, const FGeometry& InGeometry);` — Report geometry for a child row
- L76 _public prototype_ `void OnChildRowRemoved(const TSharedRef<FAnimTimelineTrack>& InTrack);` — Called when a child row widget has been added/removed
- L79 _public prototype_ `void ScrollByDelta(float DeltaInSlateUnits);` — Scroll this tree view by the specified number of slate units
- L82 _public prototype_ `void RefreshFilter();` — Apply any changed filter
- L86 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(TSharedRef<FAnimTimelineTrack> Item, const TSharedRef<STableViewBase>& OwnerTable);` — Generate a row for the outliner
- L89 _private prototype_ `void HandleGetChildren(TSharedRef<FAnimTimelineTrack> Item, TArray<TSharedRef<FAnimTimelineTrack>>& OutChildren);` — Get the children of an outliner item
- L92 _private prototype_ `void HandleExpansionChanged(TSharedRef<FAnimTimelineTrack> InItem, bool bIsExpanded);` — Record the expansion state when it changes
- L95 _private prototype_ `TSharedPtr<SWidget> HandleContextMenuOpening();` — Handle context menu
- L98 _private prototype_ `void HandleTracksChanged();` — Handle tracks changing
- L101 _private prototype_ `TSharedRef<SWidget> GenerateWidgetForColumn(const TSharedRef<FAnimTimelineTrack>& InTrack, const FName& ColumnId, const TSharedRef<SAnimOutlinerItem>& Row) const;` — Generate a widget for the specified column
- L105 _private member_ `TWeakPtr<FAnimModel> AnimModel;` — The anim timeline model
- L108 _private member_ `TSharedPtr<SAnimTrackArea> TrackArea;` — The track area
- L111 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;` — The header row
- L114 _private member_ `FDelegateHandle TracksChangedDelegateHandle;` — Delegate handle for track changes
- L117 _private member_ `TMap<TSharedRef<FAnimTimelineTrack>, FCachedGeometry> CachedTrackGeometry;` — Map of cached geometries for visible tracks
- L120 _private member_ `mutable TArray<FCachedGeometry> PhysicalTracks;` — Linear, sorted array of tracks that we currently have generated widgets for
- L123 _private member_ `mutable bool bPhysicalTracksNeedUpdate;` — A flag indicating that the physical tracks need to be updated.
- L126 _private member_ `TAttribute<FText> FilterText;` — The filter text used when we are searching the tree
- L129 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> TextFilter;` — Compiled filter search terms.

#### struct `SAnimOutliner::FCachedGeometry`  
`struct FCachedGeometry`  
_L53-64_
- desc: Structure used to cache physical geometry for a particular track
- L55 _public function_ `FCachedGeometry(TSharedRef<FAnimTimelineTrack> InTrack, float InTop, float InHeight) : Track(MoveTemp(InTrack)) , Top(InTop) , Height(InHeight)`
- L61 _public member_ `TSharedRef<FAnimTimelineTrack> Track;`
- L62 _public member_ `float Top;`
- L63 _public member_ `float Height;`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetContextMenuContent, FMenuBuilder& );` — A delegate that is executed when adding menu content.
- L21 _prototype_ `DECLARE_DELEGATE_OneParam(FOnGetContextMenuContent, FMenuBuilder& );` — A delegate that is executed when adding menu content.

### `Source/Editor/Persona/Private/AnimTimeline/SAnimOutlinerItem.h` (Private)


#### class `SAnimOutlinerItem`  
`class SAnimOutlinerItem : public SMultiColumnTableRow<TSharedRef<FAnimTimelineTrack>>`  
_L14-74_
- inherits: `SMultiColumnTableRow<TSharedRef<FAnimTimelineTrack>>`
- L18 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedRef<SWidget>, FOnGenerateWidgetForColumn, const TSharedRef<FAnimTimelineTrack>&, const FName&, const TSharedRef<SAnimOutlinerItem>&);` — Delegate to invoke to create a new column for this row
- L20 _public function_ `SLATE_BEGIN_ARGS(SAnimOutlinerItem)`
- L23 _public prototype_ `SLATE_EVENT(FOnGenerateWidgetForColumn, OnGenerateWidgetForColumn) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_END_ARGS() ~SAnimOutlinerItem();` — Delegate to invoke to create a new column for this row
- L32 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<FAnimTimelineTrack>& InTrack);`
- L35 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L36 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L37 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L38 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L41 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnId) override;` — SMultiColumnTableRow interface
- L44 _public function_ `TSharedRef<FAnimTimelineTrack> GetTrack() const` — Get the track this item represents
- L47 _public prototype_ `void AddTrackAreaReference(const TSharedPtr<SAnimTrack>& InTrackWidget);` — Add a reference to the specified track, keeping it alive until this row is destroyed
- L50 _public function_ `TAttribute<FText> GetHighlightText() const` — Get the text to highlight when searching
- L54 _private prototype_ `FText GetLabelText() const;` — Get the label text for this item
- L57 _private prototype_ `bool ShouldAppearHovered() const;` — Get the hover state for this item
- L61 _private member_ `TWeakPtr<FAnimTimelineTrack> Track;` — The track that we represent
- L64 _private member_ `TSharedPtr<SAnimTrack> TrackWidget;` — Cached reference to a track lane that we relate to. This keeps the track lane alive (it's a weak widget) as long as we are in view.
- L67 _private member_ `FOnGenerateWidgetForColumn OnGenerateWidgetForColumn;` — Delegate to invoke to create a new column for this row
- L70 _private member_ `TAttribute<FText> HighlightText;` — Text to highlight when searching
- L73 _private member_ `bool bHovered;` — Keep an internal IsHovered flag

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(TSharedRef<SWidget>, FOnGenerateWidgetForColumn, const TSharedRef<FAnimTimelineTrack>&, const FName&, const TSharedRef<SAnimOutlinerItem>&);` — Delegate to invoke to create a new column for this row

### `Source/Editor/Persona/Private/AnimTimeline/SAnimTimeline.h` (Private)


#### class `SAnimTimeline`  
`class SAnimTimeline : public SCompoundWidget`  
_L25-139_
- inherits: `SCompoundWidget`
- desc: Implements the anim timeline widget.
- L28 _public function_ `SLATE_BEGIN_ARGS(SAnimTimeline)`
- L46 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FAnimModel>& InModel);` — Construct this widget. @param InArgs The declaration data for this widget. @param InModel The model for the anim timeline
- L49 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L52 _public prototype_ `bool GetGridMetrics(float PhysicalWidth, double& OutMajorInterval, int32& OutMinorDivisions) const;` — Compute a major grid interval and number of minor divisions to display
- L55 _public prototype_ `TSharedPtr<ITimeSliderController> GetTimeSliderController() const;` — Get the time slider controller
- L61 _private function_ `float GetColumnFillCoefficient(int32 ColumnIndex) const` — @return The fill percentage of the animation outliner
- L67 _private prototype_ `TSharedRef<INumericTypeInterface<double>> GetNumericTypeInterface() const;` — Get numeric Type interface for converting between frame numbers and display formats.
- L70 _private prototype_ `void OnOutlinerSearchChanged(const FText& Filter);` — Called when the outliner search terms change
- L73 _private prototype_ `void OnColumnFillCoefficientChanged(float FillCoefficient, int32 ColumnIndex);` — Called when a column fill percentage is changed by a splitter slot.
- L76 _private prototype_ `void HandleKeyComplete();` — Handles an additive layer key being set
- L78 _private prototype_ `UAnimSingleNodeInstance* GetPreviewInstance() const;`
- L82 _private prototype_ `void HandleScrubPositionChanged(FFrameTime NewScrubPosition, bool bIsScrubbing, bool bEvaluate) const;`
- L84 _private prototype_ `void OnCropAnimSequence(bool bFromStart, FFrameNumber StartFrame);`
- L86 _private prototype_ `void OnAppendAnimSequence(bool bFromStart, int32 NumOfFrames);`
- L88 _private prototype_ `void OnInsertAnimSequence(bool bBefore, int32 CurrentFrame, int32 NumFrames);`
- L90 _private prototype_ `void OnReZeroAnimSequence(int32 FrameIndex);`
- L92 _private prototype_ `void OnPromptUserForNumberOfFrames(FWidgetPath WidgetPath, TFunction<void(const int32 NumFrames)> Callback);`
- L93 _private prototype_ `double GetSpinboxDelta() const;`
- L95 _private prototype_ `void SetPlayTime(double InFrameTime);`
- L99 _private member_ `TWeakPtr<FAnimModel> Model;` — Anim timeline model
- L102 _private member_ `TSharedPtr<SAnimOutliner> Outliner;` — Outliner widget
- L105 _private member_ `TSharedPtr<SAnimTrackArea> TrackArea;` — Track area widget
- L108 _private member_ `TSharedPtr<FAnimTimeSliderController> TimeSliderController;` — The time slider controller
- L111 _private member_ `TSharedPtr<ITimeSlider> TopTimeSlider;` — The top time slider widget
- L114 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The search box for filtering tracks.
- L117 _private member_ `float ColumnFillCoefficients[2];` — The fill coefficients of each column in the grid.
- L120 _private member_ `FSimpleDelegate OnSelectionRangeBeginDrag;` — Called when the user has begun dragging the selection selection range
- L123 _private member_ `FSimpleDelegate OnSelectionRangeEndDrag;` — Called when the user has finished dragging the selection selection range
- L126 _private member_ `FSimpleDelegate OnReceivedFocus;` — Called when any widget contained within the anim timeline has received focus
- L129 _private member_ `TSharedPtr<INumericTypeInterface<double>> NumericTypeInterface;` — Numeric Type interface for converting between frame numbers and display formats.
- L132 _private member_ `TSharedPtr<INumericTypeInterface<double>> SecondaryNumericTypeInterface;` — Secondary numeric Type interface for converting between frame numbers and display formats.
- L135 _private member_ `TAttribute<FAnimatedRange> ViewRange;` — The view range
- L138 _private member_ `FText FilterText;` — Filter text used to search the tree

### `Source/Editor/Persona/Private/AnimTimeline/SAnimTimelineOverlay.h` (Private)


#### class `SAnimTimelineOverlay`  
`class SAnimTimelineOverlay : public SCompoundWidget`  
_L22-58_
- inherits: `SCompoundWidget`
- desc: An overlay that displays global information in the track area
- L25 _public function_ `SLATE_BEGIN_ARGS( SAnimTimelineOverlay ) : _DisplayTickLines( true ) , _DisplayScrubPosition( false )`
- L30 _public function_ `SLATE_ATTRIBUTE( bool, DisplayTickLines ) SLATE_ATTRIBUTE( bool, DisplayScrubPosition ) SLATE_ATTRIBUTE( FPaintPlaybackRangeArgs, PaintPlaybackRangeArgs ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TSharedRef<FAnimTimeSliderController> InTimeSliderController )`
- L46 _private prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;` — SWidget Interface
- L50 _private member_ `TSharedPtr<FAnimTimeSliderController> TimeSliderController;` — Controller for manipulating time
- L52 _private member_ `TAttribute<bool> bDisplayScrubPosition;` — Whether or not to display the scrub position
- L54 _private member_ `TAttribute<bool> bDisplayTickLines;` — Whether or not to display tick lines
- L56 _private member_ `TAttribute<FPaintPlaybackRangeArgs> PaintPlaybackRangeArgs;` — User-supplied options for drawing playback range

### `Source/Editor/Persona/Private/AnimTimeline/SAnimTimelineSplitterOverlay.h` (Private)


#### class `SAnimTimelineSplitterOverlay`  
`class SAnimTimelineSplitterOverlay : public SOverlay`  
_L20-41_
- inherits: `SOverlay`
- desc: Splitter used on the anim timeline as an overlay. Input is disabled on all areas except the draggable positions
- L23 _public typedef_ `typedef SSplitter::FArguments FArguments;`
- L25 _public prototype_ `void Construct( const FArguments& InArgs );`
- L28 _public prototype_ `virtual void OnArrangeChildren( const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren ) const override;` — SwWidget interface
- L29 _public prototype_ `virtual FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;`
- L30 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L31 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L32 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L33 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L34 _public prototype_ `virtual void OnMouseLeave( const FPointerEvent& MouseEvent ) override;`
- L37 _private prototype_ `FMargin GetSplitterHandlePadding(int32 Index) const;`
- L39 _private member_ `TSharedPtr<SSplitter> Splitter;`
- L40 _private member_ `mutable TArray<FMargin> SlotPadding;`

### `Source/Editor/Persona/Private/AnimTimeline/SAnimTimelineTransportControls.h` (Private)


#### class `SAnimTimelineTransportControls`  
`class SAnimTimelineTransportControls : public SCompoundWidget`  
_L15-55_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SAnimTimelineTransportControls)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPersonaPreviewScene>& InPreviewScene, UAnimSequenceBase* InAnimSequenceBase);`
- L25 _private prototype_ `UAnimSingleNodeInstance* GetPreviewInstance() const;`
- L27 _private function_ `TSharedRef<IPersonaPreviewScene> GetPreviewScene() const`
- L29 _private prototype_ `FReply OnClick_Forward_Step();`
- L31 _private prototype_ `FReply OnClick_Forward_End();`
- L33 _private prototype_ `FReply OnClick_Backward_Step();`
- L35 _private prototype_ `FReply OnClick_Backward_End();`
- L37 _private prototype_ `FReply OnClick_Forward();`
- L39 _private prototype_ `FReply OnClick_Backward();`
- L41 _private prototype_ `FReply OnClick_ToggleLoop();`
- L43 _private prototype_ `FReply OnClick_Record();`
- L45 _private prototype_ `bool IsLoopStatusOn() const;`
- L47 _private prototype_ `EPlaybackMode::Type GetPlaybackMode() const;`
- L49 _private prototype_ `bool IsRecording() const;`
- L52 _private member_ `TWeakPtr<IPersonaPreviewScene> WeakPreviewScene;`
- L54 _private member_ `UAnimSequenceBase* AnimSequenceBase;`

### `Source/Editor/Persona/Private/AnimTimeline/SAnimTrack.h` (Private)


#### class `SAnimTrack`  
`class SAnimTrack : public SCompoundWidget`  
_L18-60_
- inherits: `SCompoundWidget`
- desc: A wrapper widget responsible for positioning a track within the track area
- L21 _public function_ `SLATE_BEGIN_ARGS(SAnimTrack)`
- L23 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ATTRIBUTE(FAnimatedRange, ViewRange) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAnimTimelineTrack>& InTrack, const TSharedRef<SAnimOutliner>& InOutliner);`
- L33 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — Paint this widget
- L34 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L35 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L36 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L37 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L40 _public prototype_ `float GetPhysicalPosition() const;` — Get the desired physical vertical position of this track
- L43 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScale) const override;`
- L47 _private member_ `TWeakPtr<FAnimTimelineTrack> WeakTrack;` — The track that we represent
- L50 _private member_ `TWeakPtr<SAnimOutliner> WeakOutliner;` — Outliner that we are associated with
- L53 _private member_ `TOptional<FVector2D> LastDesiredSize;` — Our desired size last frame
- L56 _private member_ `TAttribute<FAnimatedRange> ViewRange;` — The range our track should display
- L59 _private member_ `TAttribute<FInt32Interval> ViewIndices;` — The range of indices our track should display

### `Source/Editor/Persona/Private/AnimTimeline/SAnimTrackArea.h` (Private)


#### class `FAnimTrackAreaSlot`  
`class FAnimTrackAreaSlot : public TSlotBase<FAnimTrackAreaSlot>, public TAlignmentWidgetSlotMixin<FAnimTrackAreaSlot>`  
_L26-38_
- inherits: `TSlotBase<FAnimTrackAreaSlot>,TAlignmentWidgetSlotMixin<FAnimTrackAreaSlot>`
- desc: Structure representing a slot in the track area.
- L31 _public prototype_ `FAnimTrackAreaSlot(const TSharedPtr<SAnimTrack>& InSlotContent);` — Construction from a track lane
- L34 _public prototype_ `float GetVerticalOffset() const;` — Get the vertical position of this slot inside its parent.
- L37 _public member_ `TWeakPtr<SAnimTrack> TrackWidget;` — The track that we represent.

#### class `SAnimTrackArea`  
`class SAnimTrackArea : public SPanel`  
_L44-122_
- inherits: `SPanel`
- desc: The area where tracks are displayed.
- L48 _public function_ `SLATE_BEGIN_ARGS(SAnimTrackArea)`
- L54 _public function_ `SAnimTrackArea() : Children(this)`
- L59 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FAnimModel>& InAnimModel, const TSharedRef<FAnimTimeSliderController>& InTimeSliderController);` — Construct this widget
- L64 _public prototype_ `void Empty();` — Empty the track area
- L67 _public prototype_ `void AddTrackSlot(const TSharedRef<FAnimTimelineTrack>& InTrack, const TSharedPtr<SAnimTrack>& InTrackWidget);` — Add a new track slot to this area for the given node. The slot will be automatically cleaned up when all external references to the supplied slot are removed.
- L70 _public prototype_ `TSharedPtr<SAnimTrack> FindTrackSlot(const TSharedRef<FAnimTimelineTrack>& InTrack);` — Attempt to find an existing slot relating to the given node
- L73 _public function_ `const FGeometry& GetCachedGeometry() const` — Access the cached geometry for this track area
- L79 _public prototype_ `void SetOutliner(const TSharedPtr<SAnimOutliner>& InOutliner);` — Assign an outliner to this track area.
- L84 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;` — SWidget interface
- L85 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L86 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L87 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L88 _public prototype_ `virtual FReply OnMouseWheel( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L89 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L90 _public prototype_ `virtual FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;`
- L91 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L92 _public prototype_ `virtual void OnArrangeChildren( const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren ) const override;`
- L93 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L94 _public prototype_ `virtual FChildren* GetChildren() override;`
- L99 _protected prototype_ `void UpdateHoverStates(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Update any hover state required for the track area
- L104 _private member_ `TPanelChildren<FAnimTrackAreaSlot> Children;` — The track area's children.
- L109 _private member_ `FGeometry CachedGeometry;` — Cached geometry.
- L112 _private member_ `TMap<TWeakPtr<FAnimTimelineTrack>, TWeakPtr<SAnimTrack>> TrackSlots;` — A map of child slot content that exists in our view.
- L115 _private member_ `TWeakPtr<FAnimModel> WeakModel;` — Weak pointer to the model.
- L118 _private member_ `TWeakPtr<FAnimTimeSliderController> WeakTimeSliderController;` — Weak pointer to the time slider.
- L121 _private member_ `TWeakPtr<SAnimOutliner> WeakOutliner;` — Weak pointer to the outliner (used for scrolling interactions).

### `Source/Editor/Persona/Private/AnimTimeline/SAnimTrackResizeArea.h` (Private)


#### class `SAnimTrackResizeArea`  
`class SAnimTrackResizeArea : public SCompoundWidget`  
_L12-42_
- inherits: `SCompoundWidget`
- desc: Area at the bottom of a track used to resize it
- L15 _public function_ `SLATE_BEGIN_ARGS(SAnimTrackResizeArea)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakPtr<FAnimTimelineTrack> InTrack);`
- L21 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L22 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L23 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L24 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L39 _private member_ `TOptional<FDragParameters> DragParameters;`
- L41 _private member_ `TWeakPtr<FAnimTimelineTrack> Track;`

#### struct `SAnimTrackResizeArea::FDragParameters`  
`struct FDragParameters`  
_L28-37_
- L30 _public function_ `FDragParameters(float InOriginalHeight, float InDragStartY) : OriginalHeight(InOriginalHeight) , DragStartY(InDragStartY)`
- L35 _public member_ `float OriginalHeight;`
- L36 _public member_ `float DragStartY;`

### `Source/Editor/Persona/Private/AnimViewportLODCommands.h` (Private)


#### class `FAnimViewportLODCommands`  
`class FAnimViewportLODCommands : public TCommands<FAnimViewportLODCommands>`  
_L18-44_
- inherits: `TCommands<FAnimViewportLODCommands>`
- desc: Class containing commands for persona viewport LOD actions
- L21 _public function_ `FAnimViewportLODCommands() : TCommands<FAnimViewportLODCommands> ( TEXT("AnimViewportLODCmd"),`
- L33 _public member_ `TSharedPtr< FUICommandInfo > LODDebug;` — LOD Debug
- L36 _public member_ `TSharedPtr< FUICommandInfo > LODAuto;` — LOD Auto
- L39 _public member_ `TSharedPtr< FUICommandInfo > LOD0;` — LOD 0
- L43 _public prototype_ `virtual void RegisterCommands() override;` — Registers our commands with the binding system

### `Source/Editor/Persona/Private/AnimViewportMenuCommands.h` (Private)


#### class `FAnimViewportMenuCommands`  
`class FAnimViewportMenuCommands : public TCommands<FAnimViewportMenuCommands>`  
_L18-77_
- inherits: `TCommands<FAnimViewportMenuCommands>`
- desc: Class containing commands for viewport menu actions
- L21 _public function_ `FAnimViewportMenuCommands() : TCommands<FAnimViewportMenuCommands> ( TEXT("AnimViewportMenu"),`
- L33 _public member_ `TSharedPtr< FUICommandInfo > PreviewSceneSettings;` — Open settings for the preview scene
- L36 _public member_ `TSharedPtr< FUICommandInfo > CameraFollowNone;` — Select camera follow mode off
- L39 _public member_ `TSharedPtr< FUICommandInfo > CameraFollowBounds;` — Select camera follow mode to follow bounds
- L42 _public member_ `TSharedPtr< FUICommandInfo > CameraFollowBone;` — Select camera follow mode to follow a named bone
- L45 _public member_ `TSharedPtr< FUICommandInfo > CameraFollowRoot;` — Select camera follow mode to orbit the root bone while keeping the mesh vertically centered.
- L48 _public member_ `TSharedPtr< FUICommandInfo > TogglePauseAnimationOnCameraMove;` — Toggle whether or not to pause the preview animation when moving the camera
- L51 _public member_ `TSharedPtr< FUICommandInfo > SetCPUSkinning;` — Show vertex normals
- L54 _public member_ `TSharedPtr< FUICommandInfo > SetShowNormals;` — Show vertex normals
- L57 _public member_ `TSharedPtr< FUICommandInfo > SetShowTangents;` — Show vertex tangents
- L60 _public member_ `TSharedPtr< FUICommandInfo > SetShowBinormals;` — Show vertex binormals
- L63 _public member_ `TSharedPtr< FUICommandInfo > AnimSetDrawUVs;` — Draw UV mapping to viewport
- L66 _public member_ `TSharedPtr< FUICommandInfo > SaveCameraAsDefault;` — Save current camera as default
- L69 _public member_ `TSharedPtr< FUICommandInfo > ClearDefaultCamera;` — Clear default camera
- L72 _public member_ `TSharedPtr< FUICommandInfo > JumpToDefaultCamera;` — Jump to default camera
- L76 _public prototype_ `virtual void RegisterCommands() override;` — Registers our commands with the binding system

### `Source/Editor/Persona/Private/AnimViewportPlaybackCommands.h` (Private)


#### class `FAnimViewportPlaybackCommands`  
`class FAnimViewportPlaybackCommands : public TCommands<FAnimViewportPlaybackCommands>`  
_L11-28_
- inherits: `TCommands<FAnimViewportPlaybackCommands>`
- desc: Class containing commands for viewport playback actions
- L14 _public prototype_ `FAnimViewportPlaybackCommands();`
- L17 _public member_ `TArray<TSharedPtr< FUICommandInfo >> PlaybackSpeedCommands;` — Command list for playback speed, indexed by EPlaybackSpeeds
- L20 _public member_ `TArray<TSharedPtr< FUICommandInfo >> TurnTableSpeeds;` — Command list for turn table speed, indexed by EPlaybackSpeeds
- L21 _public member_ `TSharedPtr<FUICommandInfo> PersonaTurnTablePlay;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> PersonaTurnTablePause;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> PersonaTurnTableStop;`
- L27 _public prototype_ `virtual void RegisterCommands() override;` — Registers our commands with the binding system

### `Source/Editor/Persona/Private/AnimViewportShowCommands.h` (Private)


#### class `FAnimViewportShowCommands`  
`class FAnimViewportShowCommands : public TCommands<FAnimViewportShowCommands>`  
_L20-191_
- inherits: `TCommands<FAnimViewportShowCommands>`
- desc: Class containing commands for persona viewport show actions
- L23 _public function_ `FAnimViewportShowCommands() : TCommands<FAnimViewportShowCommands> ( TEXT("AnimViewportShowCmd"),`
- L36 _public prototype_ `~FAnimViewportShowCommands() = default;` — Silence clang deprecation warnings for implicit default copy operator and constructor
- L37 _public prototype_ `FAnimViewportShowCommands(const FAnimViewportShowCommands&) = delete;`
- L38 _public prototype_ `FAnimViewportShowCommands& operator=(const FAnimViewportShowCommands&) = delete;`
- L39 _public prototype_ `FAnimViewportShowCommands(FAnimViewportShowCommands&&) = delete;`
- L40 _public prototype_ `FAnimViewportShowCommands& operator=(FAnimViewportShowCommands&&) = delete;`
- L44 _public member_ `TSharedPtr< FUICommandInfo > AutoAlignFloorToMesh;` — Option to align floor to Mesh
- L47 _public member_ `TSharedPtr< FUICommandInfo > MuteAudio;` — Option to mute audio in the viewport
- L50 _public member_ `TSharedPtr< FUICommandInfo > UseAudioAttenuation;` — Option to use audio attenuation in the viewport
- L53 _public member_ `TSharedPtr< FUICommandInfo > DoNotProcessRootMotion;` — Option to set ProcessRootMotionMode to Ignore (Preview mesh will not consume root motion)
- L56 _public member_ `TSharedPtr< FUICommandInfo > ProcessRootMotionLoopAndReset;` — Option to set ProcessRootMotionMode to LoopAndReset (Preview mesh will consume root motion resetting the position back to the origin every time the animation loops)
- L59 _public member_ `TSharedPtr< FUICommandInfo > ProcessRootMotionLoop;` — Option to set ProcessRootMotionMode to Loop (Preview mesh will consume root motion continually)
- L62 _public member_ `TSharedPtr< FUICommandInfo > DoNotVisualizeRootMotion;` — Visualize root motion mode
- L63 _public member_ `TSharedPtr< FUICommandInfo > VisualizeRootMotionTrajectory;`
- L64 _public member_ `TSharedPtr< FUICommandInfo > VisualizeRootMotionTrajectoryAndOrientation;`
- L67 _public member_ `TSharedPtr< FUICommandInfo > DisablePostProcessBlueprint;` — Option to enable/disable post process anim blueprint evaluation
- L70 _public member_ `TSharedPtr< FUICommandInfo > ShowBound;` — Show Bound of preview mesh
- L73 _public member_ `TSharedPtr< FUICommandInfo > UseInGameBound;` — Use in-game Bound of preview mesh
- L76 _public member_ `TSharedPtr< FUICommandInfo > UseFixedBounds;` — Use in-game Bound of preview mesh
- L79 _public member_ `TSharedPtr< FUICommandInfo > UsePreSkinnedBounds;` — Use pre-skinned Bound of preview mesh
- L82 _public member_ `TSharedPtr< FUICommandInfo > ShowPreviewMesh;` — Show/hide the preview mesh
- L85 _public member_ `TSharedPtr< FUICommandInfo > ShowNaniteFallback;` — Show/hide the preview mesh
- L88 _public member_ `TSharedPtr< FUICommandInfo > ShowMorphTargets;` — Show Morphtarget
- L91 _public member_ `TSharedPtr< FUICommandInfo > ShowBoneDrawNone;` — Hide all bones
- L94 _public member_ `TSharedPtr< FUICommandInfo > ShowBoneDrawSelected;` — Show only selected bones
- L97 _public member_ `TSharedPtr< FUICommandInfo > ShowBoneDrawSelectedAndParents;` — Show only selected bones and their parents
- L100 _public member_ `TSharedPtr< FUICommandInfo > ShowBoneDrawSelectedAndChildren;` — Show only selected bones and their children
- L103 _public member_ `TSharedPtr< FUICommandInfo > ShowBoneDrawSelectedAndParentsAndChildren;` — Show only selected bones and their parents and children
- L106 _public member_ `TSharedPtr< FUICommandInfo > ToggleShowBoneDrawAll;` — Toggles showing all bones
- L109 _public member_ `TSharedPtr< FUICommandInfo > ShowBoneDrawAll;` — Show all bones
- L112 _public member_ `TSharedPtr< FUICommandInfo > ShowRawAnimation;` — Show raw animation (vs compressed)
- L115 _public member_ `TSharedPtr< FUICommandInfo > ShowNonRetargetedAnimation;` — Show non retargeted animation.
- L118 _public member_ `TSharedPtr< FUICommandInfo > ShowAdditiveBaseBones;` — Show additive base pose
- L121 _public member_ `TSharedPtr< FUICommandInfo > ShowSourceRawAnimation;` — Show non retargeted animation.
- L124 _public member_ `TSharedPtr< FUICommandInfo > ShowBakedAnimation;` — Show non retargeted animation.
- L127 _public member_ `TSharedPtr< FUICommandInfo > ShowBoneNames;` — Show skeletal mesh bone names
- L130 _public member_ `TSharedPtr< FUICommandInfo > ShowBoneColors;` — Show skeletal mesh bone names
- L133 _public member_ `TSharedPtr< FUICommandInfo > ShowDisplayInfoBasic;` — Show skeletal mesh info
- L134 _public member_ `TSharedPtr< FUICommandInfo > ShowDisplayInfoDetailed;`
- L135 _public member_ `TSharedPtr< FUICommandInfo > ShowDisplayInfoSkelControls;`
- L136 _public member_ `TSharedPtr< FUICommandInfo > HideDisplayInfo;`
- L139 _public member_ `TSharedPtr< FUICommandInfo > ShowOverlayNone;` — Show overlay material option
- L140 _public member_ `TSharedPtr< FUICommandInfo > ShowBoneWeight;`
- L141 _public member_ `TSharedPtr< FUICommandInfo > ShowMorphTargetVerts;`
- L144 _public member_ `TSharedPtr< FUICommandInfo > ShowSockets;` — Show socket hit point diamonds
- L147 _public member_ `TSharedPtr< FUICommandInfo > ShowAttributes;` — Show transform attributes
- L150 _public member_ `TSharedPtr< FUICommandInfo > ShowLocalAxesNone;` — Hide all local axes
- L153 _public member_ `TSharedPtr< FUICommandInfo > ShowLocalAxesSelected;` — Show only selected axes
- L156 _public member_ `TSharedPtr< FUICommandInfo > ShowLocalAxesAll;` — Show all local axes
- L159 _public member_ `TSharedPtr< FUICommandInfo > EnableClothSimulation;` — Enable cloth simulation
- L162 _public member_ `TSharedPtr< FUICommandInfo > ResetClothSimulation;` — Reset cloth simulation
- L168 _public member_ `TSharedPtr< FUICommandInfo > EnableCollisionWithAttachedClothChildren;` — `UE_DEPRECATED(5.8, "This functionality has been deprecated")` — Enables collision detection between collision primitives in the base mesh and clothing on any attachments in the preview scene.
- L171 _public member_ `TSharedPtr< FUICommandInfo > ShowAllSections;` — Show all sections which means the original state
- L173 _public member_ `TSharedPtr< FUICommandInfo > ShowOnlyClothSections;` — Show only clothing mapped sections
- L175 _public member_ `TSharedPtr< FUICommandInfo > HideOnlyClothSections;` — Show all except clothing mapped sections
- L177 _public member_ `TSharedPtr< FUICommandInfo > PauseClothWithAnim;`
- L180 _public member_ `TSharedPtr< FUICommandInfo > ShowNotificationVisualizations;` — Show Notification Visualizations
- L183 _public member_ `TSharedPtr< FUICommandInfo > ShowAssetUserDataVisualizations;` — Show AssetUserData Visualizations
- L186 _public member_ `TSharedPtr< FUICommandInfo > ShowTimecode;` — Show Animation Timecode Values
- L190 _public prototype_ `virtual void RegisterCommands() override;` — Registers our commands with the binding system

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API PERSONA_API`

### `Source/Editor/Persona/Private/AnimViewportToolBarToolMenuContext.h` (Private)


#### class `UAnimViewportToolBarToolMenuContext`  
`class UAnimViewportToolBarToolMenuContext : public UObject`  
_L11-17_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public member_ `TWeakPtr<const SAnimViewportToolBar> AnimViewportToolBar;`

### `Source/Editor/Persona/Private/AnimationEditorPreviewScene.h` (Private)


#### class `FAnimationEditorPreviewScene`  
`class FAnimationEditorPreviewScene : public IPersonaPreviewScene, public FEditorUndoClient`  
_L20-549_
- inherits: `IPersonaPreviewScene,FEditorUndoClient`
- L23 _public prototype_ `FAnimationEditorPreviewScene(const ConstructionValues& CVS, const TSharedPtr<class IEditableSkeleton>& InEditableSkeleton, const TSharedRef<class IPersonaToolkit>& InPersonaToolkit);`
- L25 _public prototype_ `~FAnimationEditorPreviewScene();`
- L28 _public prototype_ `virtual void UnregisterForUndo() override;` — IPersonaPreviewScene interface
- L29 _public function_ `virtual TSharedRef<class IPersonaToolkit> GetPersonaToolkit() const override`
- L30 _public prototype_ `virtual void SetPreviewAnimationAsset(UAnimationAsset* AnimAsset, bool bEnablePreview = true) override;`
- L31 _public prototype_ `virtual UAnimationAsset* GetPreviewAnimationAsset() const override;`
- L32 _public prototype_ `virtual void SetPreviewMesh(USkeletalMesh* NewPreviewMesh, bool bAllowOverrideBaseMesh = true) override;`
- L33 _public prototype_ `virtual USkeletalMesh* GetPreviewMesh() const override;`
- L34 _public prototype_ `virtual void SetPreviewAnimationBlueprint(UAnimBlueprint* InAnimBlueprint, UAnimBlueprint* InOverlayOrSubAnimBlueprint) override;`
- L35 _public prototype_ `virtual bool AttachObjectToPreviewComponent(UObject* Object, FName AttachTo) override;`
- L36 _public prototype_ `virtual void RemoveAttachedObjectFromPreviewComponent(UObject* Object, FName AttachedTo) override;`
- L37 _public prototype_ `virtual void InvalidateViews() override;`
- L38 _public prototype_ `virtual void FocusViews() override;`
- L39 _public function_ `virtual UDebugSkelMeshComponent* GetPreviewMeshComponent() const override`
- L40 _public prototype_ `virtual TArray<UDebugSkelMeshComponent*> GetAllPreviewMeshComponents() const override;`
- L41 _public prototype_ `virtual void ForEachPreviewMesh(TFunction<void (UDebugSkelMeshComponent*)> PerMeshFunction) override;`
- L42 _public prototype_ `virtual void SetPreviewMeshComponent(UDebugSkelMeshComponent* InSkeletalMeshComponent) override;`
- L43 _public prototype_ `virtual void SetAdditionalMeshes(class UDataAsset* InAdditionalMeshes) override;`
- L44 _public prototype_ `virtual void SetAdditionalMeshesSelectable(bool bSelectable) override;`
- L45 _public prototype_ `virtual void RefreshAdditionalMeshes(bool bAllowOverrideBaseMesh) override;`
- L46 _public prototype_ `virtual void ShowReferencePose(bool bShowRefPose, bool bResetBoneTransforms = false) override;`
- L47 _public prototype_ `virtual bool IsShowReferencePoseEnabled() const override;`
- L48 _public prototype_ `virtual void SetSelectedBone(const FName& BoneName, ESelectInfo::Type InSelectInfo) override;`
- L49 _public prototype_ `virtual void SetSelectedBones(const TArray<FName>& InBoneNames, ESelectInfo::Type InSelectInfo) override;`
- L50 _public prototype_ `virtual void ClearSelectedBone() override;`
- L51 _public prototype_ `virtual void SetSelectedSocket(const FSelectedSocketInfo& SocketInfo) override;`
- L52 _public prototype_ `virtual void ClearSelectedSocket() override;`
- L53 _public prototype_ `virtual void SetSelectedActor(AActor* InActor) override;`
- L54 _public prototype_ `virtual void ClearSelectedActor() override;`
- L55 _public prototype_ `virtual void DeselectAll() override;`
- L57 _public function_ `virtual void RegisterOnAnimChanged(const FOnAnimChanged& Delegate) override`
- L62 _public function_ `virtual void UnregisterOnAnimChanged(FDelegateUserObject Thing) override`
- L67 _public function_ `virtual void RegisterOnPreviewMeshChanged(const FOnPreviewMeshChanged& Delegate) override`
- L72 _public function_ `virtual void UnregisterOnPreviewMeshChanged(FDelegateUserObject Thing) override`
- L77 _public function_ `virtual void RegisterOnLODChanged(const FSimpleDelegate& Delegate) override`
- L82 _public function_ `virtual void UnregisterOnLODChanged(FDelegateUserObject Thing) override`
- L87 _public function_ `virtual void BroadcastOnLODChanged() override`
- L95 _public function_ `virtual void RegisterOnMorphTargetsChanged(const FSimpleDelegate& Delegate) override`
- L100 _public function_ `virtual void UnregisterOnMorphTargetsChanged(FDelegateUserObject Thing) override`
- L105 _public function_ `virtual void BroadcastOnMorphTargetsChanged() override`
- L113 _public function_ `virtual void RegisterOnInvalidateViews(const FSimpleDelegate& Delegate) override`
- L118 _public function_ `virtual void UnregisterOnInvalidateViews(FDelegateUserObject Thing) override`
- L123 _public function_ `virtual void RegisterOnFocusViews(const FSimpleDelegate& Delegate) override`
- L128 _public function_ `virtual void UnregisterOnFocusViews(FDelegateUserObject Thing) override`
- L133 _public function_ `virtual void RegisterOnMeshClick(const FOnMeshClick& Delegate) override`
- L138 _public function_ `virtual void UnregisterOnMeshClick(FDelegateUserObject Thing) override`
- L143 _public function_ `virtual FDelegateHandle RegisterOnSelectedBonesChanged(const FOnSelectedBonesChanged& InDelegate) override`
- L148 _public function_ `virtual void UnregisterOnSelectedBonesChanged(FDelegateHandle InHandle) override`
- L153 _public function_ `virtual FDelegateHandle RegisterOnSelectedSocketChanged(const FOnSelectedSocketChanged& Delegate) override`
- L158 _public function_ `virtual void UnregisterOnSelectedSocketChanged(FDelegateHandle InHandle) override`
- L163 _public function_ `virtual FDelegateHandle RegisterOnDeselectAll(const FSimpleDelegate& Delegate) override`
- L168 _public function_ `virtual void UnregisterOnDeselectAll(FDelegateHandle InHandle) override`
- L173 _public prototype_ `virtual void SetDefaultAnimationMode(EPreviewSceneDefaultAnimationMode Mode, bool bShowNow) override;`
- L174 _public prototype_ `virtual void ShowDefaultMode() override;`
- L175 _public prototype_ `virtual void EnableWind(bool bEnableWind) override;`
- L176 _public prototype_ `virtual bool IsWindEnabled() const override;`
- L177 _public prototype_ `virtual void SetWindStrength(float InWindStrength) override;`
- L178 _public prototype_ `virtual float GetWindStrength() const override;`
- L179 _public prototype_ `virtual void SetGravityScale(float InGravityScale) override;`
- L180 _public prototype_ `virtual float GetGravityScale() const override;`
- L181 _public prototype_ `virtual AActor* GetSelectedActor() const override;`
- L182 _public prototype_ `virtual FSelectedSocketInfo GetSelectedSocket() const override;`
- L183 _public prototype_ `virtual int32 GetSelectedBoneIndex() const override;`
- L184 _public prototype_ `virtual void TogglePlayback() override;`
- L185 _public prototype_ `virtual AActor* GetActor() const override;`
- L186 _public prototype_ `virtual void SetActor(AActor* InActor) override;`
- L187 _public prototype_ `virtual bool AllowMeshHitProxies() const override;`
- L188 _public prototype_ `virtual void SetAllowMeshHitProxies(bool bState) override;`
- L190 _public function_ `virtual void RegisterOnSelectedLODChanged(const FOnSelectedLODChanged &Delegate) override`
- L195 _public function_ `virtual void UnRegisterOnSelectedLODChanged(FDelegateUserObject Thing) override`
- L200 _public function_ `virtual void BroadcastOnSelectedLODChanged() override`
- L208 _public function_ `virtual void RegisterOnCameraOverrideChanged(const FSimpleDelegate& Delegate) override`
- L213 _public function_ `virtual void UnregisterOnCameraOverrideChanged(FDelegateUserObject Thing) override`
- L218 _public function_ `virtual void RegisterOnPreTick(const FSimpleDelegate& Delegate) override`
- L223 _public function_ `virtual void UnregisterOnPreTick(FDelegateUserObject Thing) override`
- L228 _public function_ `virtual void RegisterOnPostTick(const FSimpleDelegate& Delegate) override`
- L233 _public function_ `virtual void UnregisterOnPostTick(FDelegateUserObject Thing) override`
- L238 _public prototype_ `virtual void FlagTickable() override;`
- L240 _public function_ `void SetCameraOverride(TSharedPtr<class FEditorCameraController> NewCamera)`
- L246 _public function_ `TSharedPtr<FEditorCameraController> GetCurrentCameraOverride() const`
- L251 _public prototype_ `virtual void HandleSkeletonTreeSelectionChanged(const TArrayView<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems, ESelectInfo::Type InSelectInfo) override;`
- L253 _public prototype_ `virtual void Tick(float InDeltaTime) override;` — FPreviewScene interface
- L254 _public prototype_ `virtual bool IsTickable() const override;`
- L255 _public function_ `virtual ETickableTickType GetTickableTickType() const`
- L256 _public prototype_ `virtual void AddComponent(class UActorComponent* Component, const FTransform& LocalToWorld, bool bAttachToRoot = false) override;`
- L257 _public prototype_ `virtual void RemoveComponent(class UActorComponent* Component) override;`
- L260 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L261 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L264 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface
- L267 _public prototype_ `void ValidatePreviewAttachedAssets(USkeletalMesh* PreviewSkeletalMesh);` — Validate preview attached assets on skeleton and supplied skeletal mesh, notifying user if any are removed
- L270 _public function_ `const FBoxSphereBounds& GetFloorBounds() const` — Get the bounds of the floor
- L273 _public prototype_ `void SetFloorLocation(const FVector& InPosition);` — Set the floor location
- L276 _public prototype_ `FText GetPreviewAssetTooltip(bool bEditingAnimBlueprint) const;` — Get tooltip text for the preview asset button
- L279 _public function_ `class UPersonaPreviewSceneDescription* GetPreviewSceneDescription() const` — Get the preview scene description
- L282 _public prototype_ `void RecordAnimation();` — Begin recording animation form the preview component
- L285 _public prototype_ `bool IsRecordAvailable() const;` — Check whether recording of the preview component is available
- L288 _public prototype_ `FSlateIcon GetRecordStatusImage() const;` — Get a status image to display for recording in progress
- L291 _public prototype_ `FText GetRecordStatusTooltip() const;` — Get a tooltip to display while recording
- L294 _public prototype_ `FText GetRecordStatusLabel() const;` — Get a the label to display while recording
- L297 _public prototype_ `FText GetRecordMenuLabel() const;` — Get a the menu label to display while recording
- L300 _public prototype_ `bool IsRecording() const;` — Check whether this Persona instance is recording
- L303 _public prototype_ `void StopRecording();` — Stop recording in this Persona instance
- L306 _public function_ `FSimpleMulticastDelegate& OnRecordingStateChanged()` — Delegate fired when recording state changes
- L309 _public prototype_ `UAnimSequence* GetCurrentRecording() const;` — Get the currently recording animation
- L312 _public prototype_ `float GetCurrentRecordingTime() const;` — Get the currently recording animation time
- L315 _public function_ `AActor* GetSelectedActor()` — Get the currently selected actor
- L318 _public function_ `FSelectedSocketInfo GetSelectedSocket()` — Get the currently selected socket
- L321 _public function_ `int32 GetSelectedBoneIndex()` — Get the currently bone index
- L324 _public function_ `virtual bool BroadcastMeshClick(HActor* HitProxy, const FViewportClick& Click)` — Broadcasts that a mesh viewport click occurred
- L328 _public prototype_ `bool PreviewComponentSelectionOverride(const UPrimitiveComponent* InComponent) const;` — Override for preview component selection to inform the editor we consider it selected
- L330 _public function_ `virtual void SetAllowAdditionalMeshes(bool bAllow)`
- L335 _public function_ `virtual void SetEditableSkeleton(TSharedPtr<IEditableSkeleton> InEditableSkeleton) override`
- L340 _public function_ `void SetIsBeingConstructed(bool bInIsBeingConstructed)`
- L345 _public function_ `bool IsBeingConstructed() const`
- L351 _public function_ `void ToggleShowTimecode()` — Toggles state on showing Timecode value in the viewport
- L357 _public function_ `bool IsShowTimecode() const` — Should we show the timecode in the viewport.
- L363 _public prototype_ `TOptional<float> GetCurrentTime() const;` — Get the current time of the preview instance for the current animation sequence.
- L366 _public prototype_ `virtual void SetCustomAnimationSpeed(float InAnimationSpeed) override;` — Set the current custom animation playback speed
- L369 _public prototype_ `virtual float GetCustomAnimationSpeed() const override;` — Get the current custom animation playback speed
- L372 _public prototype_ `virtual EAnimationPlaybackSpeeds::Type GetAnimationPlaybackSpeedMode() const override;` — Retrieve the current animation playback speed mode
- L375 _public prototype_ `virtual void SetAnimationPlaybackSpeedMode(EAnimationPlaybackSpeeds::Type InMode) override;` — Set the playback speed mode
- L378 _public prototype_ `virtual bool IsPlaybackSpeedSelected(int32 InPlaybackSpeedMode) const override;` — Function to return whether the supplied playback speed is the current active one
- L381 _public prototype_ `TSharedPtr<FUICommandList_Pinnable> GetPinnedCommandList() const;` — Return the list of commands of the preview scene which are bound to delegates
- L384 _protected prototype_ `virtual void BindCommands() override;`
- L385 _protected prototype_ `virtual TSharedRef<FUICommandList> CreateCommandList() override;`
- L389 _private prototype_ `void SetPreviewMeshInternal(USkeletalMesh* NewPreviewMesh);` — Set preview mesh internal use only. The mesh should be verified by now.
- L392 _private prototype_ `void AddPreviewAttachedObjects();` — Adds to the viewport all the attached preview objects that the current skeleton and mesh contains
- L395 _private prototype_ `void CleanupComponent(USceneComponent* Component);` — Destroy the supplied component (and its children)
- L404 _private prototype_ `void RemoveAttachedComponent(bool bRemovePreviewAttached = true);` — Removes attached components from the preview component. (WARNING: There is a possibility that this function will remove the wrong component if 2 of the same type (same UObject) are attached at the same location! @param bRemovePreviewAttached	Specifies whether all attached components are removed or just the ones that haven't come from the target skeleton.
- L407 _private prototype_ `TWeakObjectPtr<class AWindDirectionalSource> CreateWindActor(UWorld* World);` — Create an actor used to simulate wind (useful for cloth)
- L409 _private function_ `TSharedPtr<class IEditableSkeleton> GetEditableSkeleton() const`
- L412 _private function_ `virtual void SetRemoveAttachedComponentFilter(const FOnRemoveAttachedComponentFilter& Delegate) override` — setter/getter for can remove attach component
- L416 _private function_ `virtual void ClearRemoveAttachedComponentFilter() override`
- L424 _private prototype_ `void OnSetPlaybackSpeed(int32 InPlaybackSpeedMode);`
- L428 _private member_ `TObjectPtr<AActor> Actor;` — The one and only actor we have
- L431 _private member_ `TObjectPtr<UDebugSkelMeshComponent> SkeletalMeshComponent;` — The main preview skeletal mesh component
- L434 _private member_ `TArray<TObjectPtr<USkeletalMeshComponent>> AdditionalMeshes;` — Array of loaded additional meshes
- L437 _private member_ `TWeakPtr<class IEditableSkeleton> EditableSkeletonPtr;` — The editable skeleton we are viewing/editing
- L440 _private member_ `TWeakPtr<class IPersonaToolkit> PersonaToolkit;` — The persona toolkit we are embedded in
- L443 _private member_ `FBoxSphereBounds FloorBounds;` — Cached bounds of the floor mesh
- L446 _private member_ `FOnAnimChangedMulticaster OnAnimChanged;` — Delegate to be called after the preview animation has been changed
- L449 _private member_ `FOnPreviewMeshChangedMulticaster OnPreviewMeshChanged;` — Broadcasts whenever the preview mesh changes
- L452 _private member_ `EPreviewSceneDefaultAnimationMode DefaultMode;` — Mode that the preview scene defaults to (usually depending on asset editor context)
- L455 _private member_ `FOnMeshClickMulticaster OnMeshClick;` — Broadcasts whenever the preview mesh is clicked
- L458 _private member_ `TObjectPtr<class UPersonaPreviewSceneDescription> PreviewSceneDescription;` — Configuration object for editing in details panels
- L461 _private member_ `FVector PrevWindLocation;` — Previous information of a wind actor
- L462 _private member_ `FRotator PrevWindRotation;`
- L463 _private member_ `float PrevWindStrength;`
- L466 _private member_ `TWeakObjectPtr<AWindDirectionalSource> WindSourceActor;` — Reference to the wind actor
- L469 _private member_ `float GravityScale;` — The gravity scale
- L472 _private member_ `TWeakObjectPtr<AActor> SelectedActor;` — The selected actor
- L475 _private member_ `int32 SelectedBoneIndex;` — Selected bone
- L478 _private member_ `FSelectedSocketInfo SelectedSocket;` — Selected socket
- L481 _private member_ `int32 LastCachedLODForPreviewComponent;` — LOD index cached & used to check for broadcasting OnLODChanged delegate
- L484 _private member_ `FSimpleMulticastDelegate OnLODChanged;` — LOD changed delegate
- L487 _private member_ `FSimpleMulticastDelegate OnMorphTargetsChanged;` — Morph target changed delegate
- L490 _private member_ `FSimpleMulticastDelegate OnInvalidateViews;` — View invalidation delegate
- L493 _private member_ `FSimpleMulticastDelegate OnFocusViews;` — View focus delegate
- L496 _private member_ `bool bEnableMeshHitProxies;` — Whether or not mesh section hit proxies should be enabled or not
- L499 _private member_ `FOnSelectedLODChangedMulticaster OnSelectedLODChanged;` — Selected LOD changed delegate
- L502 _private member_ `FSimpleMulticastDelegate OnCameraOverrideChanged;` — Camera override delegate
- L505 _private member_ `TSharedPtr<FEditorCameraController> CameraOverride;` — Currently specified camera override
- L508 _private member_ `FSimpleMulticastDelegate OnPreTickDelegate;` — Delegates fired on pre/post tick of this preview scene
- L509 _private member_ `FSimpleMulticastDelegate OnPostTickDelegate;`
- L512 _private member_ `FSimpleMulticastDelegate OnRecordingStateChangedDelegate;` — Delegate fired when recording state changes
- L515 _private member_ `double LastTickTime;` — The last time we were flagged for ticking
- L518 _private member_ `FOnSelectedBonesChangedMulticaster OnSelectedBonesChanged;` — Bone selection changed delegate
- L521 _private member_ `FOnSelectedSocketChangedMulticaster OnSelectedSocketChanged;` — Socket selection changed delegate
- L524 _private member_ `FSimpleMulticastDelegate OnDeselectAll;` — Deselect all delegate
- L527 _private member_ `bool bSelecting;` — Selection recursion guard
- L530 _private member_ `bool bAllowAdditionalMeshes;` — Allow additional meshes to be attached
- L533 _private member_ `bool bAdditionalMeshesSelectable;` — Allow additional meshes to be selectable
- L536 _private member_ `FOnRemoveAttachedComponentFilter OnRemoveAttachedComponentFilter;` — Delegate Remove attach component
- L539 _private member_ `bool bIsBeingConstructed = false;` — True during initial creation, so some code can be skipped
- L542 _private member_ `bool bShowTimecode = true;` — Should we display timecode in the preview viewport.
- L545 _private member_ `float CustomAnimationSpeed = 1.0f;` — Custom Animation speed in the viewport. Transient setting.
- L548 _private member_ `EAnimationPlaybackSpeeds::Type AnimationPlaybackSpeedMode = EAnimationPlaybackSpeeds::Normal;` — Selected playback speed mode, used for deciding scale

### `Source/Editor/Persona/Private/ApexClothingOptionWindow.h` (Private)


#### class `SApexClothingOptionWindow`  
`class SApexClothingOptionWindow : public SCompoundWidget`  
_L15-83_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS( SApexClothingOptionWindow ) : _WidgetWindow() , _NumLODs() , _ApexDetails()`
- L30 _public prototype_ `void Construct(const FArguments& InArgs);`
- L32 _public function_ `FReply OnImport()`
- L42 _public function_ `FReply OnCancel()`
- L52 _public function_ `ECheckBoxState IsCheckedLOD() const`
- L57 _public function_ `void OnUseLOD(ECheckBoxState CheckState)`
- L62 _public function_ `bool CanImport() const`
- L67 _public function_ `bool IsUsingLOD()`
- L72 _public function_ `SApexClothingOptionWindow() : bCanImport(false) , bUseLOD(true)`
- L78 _private member_ `bool bCanImport;`
- L79 _private member_ `bool bReimport;`
- L80 _private member_ `bool bUseLOD;`
- L82 _private member_ `TWeakPtr< SWindow > WidgetWindow;`

### `Source/Editor/Persona/Private/AssetSearchBoxUtilPersona.h` (Private)


#### class `SAssetSearchBoxForBones`  
`class SAssetSearchBoxForBones : public SCompoundWidget, public FEditorUndoClient`  
_L15-60_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L18 _public function_ `SLATE_BEGIN_ARGS(SAssetSearchBoxForBones) : _OnTextCommitted() , _HintText() , _MustMatchPossibleSuggestions( false ) , _IncludeSocketsForSuggestions( false )`
- L26 _public prototype_ `SLATE_ARGUMENT( EMenuPlacement, SuggestionListPlacement ) SLATE_EVENT( FOnTextCommitted, OnTextCommitted ) SLATE_ATTRIBUTE( FText, HintText ) SLATE_ATTRIBUTE( bool, MustMatchPossibleSuggestions ) SLATE_ATTRIBUTE( bool, IncludeSocketsForSuggestions ) SLATE_END_ARGS() SAssetSearchBoxForBones();` — Where to place the suggestion list
- L43 _public prototype_ `~SAssetSearchBoxForBones();`
- L46 _public prototype_ `void Construct( const FArguments& InArgs, const class UObject* Outer, TSharedPtr<class IPropertyHandle> ParentBoneProperty );` — Constructs this widget with InArgs
- L49 _public prototype_ `void RefreshName();` — Refresh bone name
- L51 _public function_ `virtual void PostUndo( bool bSuccess )`
- L52 _public function_ `virtual void PostRedo( bool bSuccess )`
- L55 _private member_ `TSharedPtr<IPropertyHandle> BonePropertyHandle;`
- L56 _private member_ `TSharedPtr<SAssetSearchBox> SearchBox;`
- L59 _private prototype_ `FText GetBoneName() const;` — Get the bone name to display

#### class `SAssetSearchBoxForCurves`  
`class SAssetSearchBoxForCurves : public SCompoundWidget, public FEditorUndoClient`  
_L63-112_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L66 _public function_ `SLATE_BEGIN_ARGS(SAssetSearchBoxForCurves) : _OnTextCommitted() , _HintText() , _MustMatchPossibleSuggestions(false) , _IncludeSocketsForSuggestions(false)`
- L74 _public prototype_ `SLATE_ARGUMENT(EMenuPlacement, SuggestionListPlacement) SLATE_EVENT(FOnTextCommitted, OnTextCommitted) SLATE_ATTRIBUTE(FText, HintText) SLATE_ATTRIBUTE(bool, MustMatchPossibleSuggestions) SLATE_ATTRIBUTE(bool, IncludeSocketsForSuggestions) SLATE_END_ARGS() SAssetSearchBoxForCurves();` — Where to place the suggestion list
- L91 _public prototype_ `~SAssetSearchBoxForCurves();`
- L94 _public prototype_ `void Construct(const FArguments& InArgs, const class USkeleton* InSkeleton, TSharedPtr<class IPropertyHandle> ParentCurveProperty);` — Constructs this widget with InArgs
- L97 _public prototype_ `void RefreshName();` — Refresh curve name
- L99 _public function_ `virtual void PostUndo( bool bSuccess )`
- L100 _public function_ `virtual void PostRedo( bool bSuccess )`
- L103 _private member_ `TSharedPtr<IPropertyHandle> CurveNamePropertyHandle;`
- L104 _private member_ `TWeakObjectPtr<USkeleton> Skeleton;`
- L105 _private member_ `TSharedPtr<SAssetSearchBox> SearchBox;`
- L108 _private prototype_ `TArray<FAssetSearchBoxSuggestion> GetCurveSearchSuggestions() const;` — Get the search suggestions
- L111 _private prototype_ `FText GetCurveName() const;` — Get the curve name to display

### `Source/Editor/Persona/Private/BlendProfileCustomization.h` (Private)


#### class `FBlendProfileCustomization`  
`class FBlendProfileCustomization : public IPropertyTypeCustomization`  
_L10-24_
- inherits: `IPropertyTypeCustomization`
- L13 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L18 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override` — Override to do nothing
- L22 _private prototype_ `void OnBlendProfileChanged(class UBlendProfile* NewProfile, TWeakPtr<IPropertyHandle> WeakPropertyHandle);`
- L23 _private prototype_ `class USkeleton* GetSkeletonFromOuter(const UObject* Outer);`

### `Source/Editor/Persona/Private/BlendProfileInterfaceWrapperDetailsCustomization.h` (Private)


#### class `FBlendProfileInterfaceWrapperCustomization`  
`class FBlendProfileInterfaceWrapperCustomization : public IPropertyTypeCustomization`  
_L11-26_
- inherits: `IPropertyTypeCustomization`
- L14 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L18 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L21 _private prototype_ `void OnBlendProfileChanged(UBlendProfile* NewProfile, TWeakPtr<IPropertyHandle> WeakPropertyHandle, UObject* Outer);`
- L23 _private prototype_ `void OnBlendProfileProviderChanged(TObjectPtr<UObject> NewProfile, IBlendProfileProviderInterface* Interface, TWeakPtr<IPropertyHandle> WeakPropertyHandle, UObject* Outer);`
- L25 _private prototype_ `class USkeleton* GetSkeletonFromOuter(const UObject* Outer);`

### `Source/Editor/Persona/Private/CurveViewerCommands.h` (Private)


#### class `FCurveViewerCommands`  
`class FCurveViewerCommands : public TCommands<FCurveViewerCommands>`  
_L18-39_
- inherits: `TCommands<FCurveViewerCommands>`
- desc: Class containing commands for curve viewer actions
- L21 _public function_ `FCurveViewerCommands() : TCommands<FCurveViewerCommands> ( TEXT("CurveViewer"),`
- L32 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L35 _public member_ `TSharedPtr< FUICommandInfo > AddCurve;` — Add curve
- L38 _public member_ `TSharedPtr< FUICommandInfo > FindCurveUses;` — Fund curve uses

### `Source/Editor/Persona/Private/Customization/AnimGraphNodeSlotDetails.h` (Private)


#### class `FAnimGraphNodeSlotDetails`  
`class FAnimGraphNodeSlotDetails : public IDetailCustomization`  
_L17-52_
- inherits: `IDetailCustomization`
- desc: Customizes a DataTable asset to use a dropdown
- L20 _public prototype_ `FAnimGraphNodeSlotDetails(FOnInvokeTab InOnInvokeTab);`
- L22 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance(FOnInvokeTab InOnInvokeTab)`
- L28 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L32 _private member_ `FOnInvokeTab OnInvokeTab;` — delegate used to invoke a tab in the containing editor
- L35 _private member_ `TSharedPtr<IPropertyHandle> SlotNodeNamePropertyHandle;` — property of the two
- L38 _private member_ `TSharedPtr<class STextComboBox> SlotNameComboBox;` — slot node names
- L39 _private member_ `TArray< TSharedPtr< FString > > SlotNameComboListItems;`
- L40 _private member_ `TArray< FName > SlotNameList;`
- L41 _private member_ `FName SlotNameComboSelectedName;`
- L43 _private prototype_ `void OnSlotNameChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L44 _private prototype_ `void OnSlotListOpening();`
- L47 _private prototype_ `FReply OnOpenAnimSlotManager();` — slot node names buttons
- L49 _private prototype_ `void RefreshComboLists(bool bOnlyRefreshIfDifferent = false);`
- L51 _private member_ `USkeleton* Skeleton;`

### `Source/Editor/Persona/Private/Customization/BlendParameterDetails.h` (Private)


#### class `FBlendParameterDetails`  
`class FBlendParameterDetails : public IPropertyTypeCustomization`  
_L11-35_
- inherits: `IPropertyTypeCustomization`
- L14 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L20 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override` — IDetailCustomization interface
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L24 _private prototype_ `TOptional<float> GetRangeValue(const int32 RangeValueIndex) const;`
- L25 _private prototype_ `void OnRangeNumValueChanged(float FloatValue, const int32 RangeValueIndex);`
- L26 _private prototype_ `void OnRangeNumValueCommitted(float FloatValue, ETextCommit::Type CommitType, const int32 RangeValueIndex) const;`
- L29 _private member_ `static const int32 NumRangeValues = 2;`
- L30 _private member_ `bool bValidRangeValue[NumRangeValues];`
- L32 _private member_ `TSharedPtr<SNumericEntryBox<float>> RangeBoxes[NumRangeValues];`
- L34 _private member_ `TSharedPtr<IPropertyHandle> RangeProperties[NumRangeValues];`

### `Source/Editor/Persona/Private/Customization/BlendSampleDetails.h` (Private)


#### class `FBlendSampleDetails`  
`class FBlendSampleDetails : public IDetailCustomization`  
_L17-58_
- inherits: `IDetailCustomization`
- L20 _public prototype_ `FBlendSampleDetails(const class UBlendSpace* InBlendSpace, class SBlendSpaceGridWidget* InGridWidget, int32 InSampleIndex);`
- L22 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance(const class UBlendSpace* InBlendSpace, class SBlendSpaceGridWidget* InGridWidget, int32 InSampleIndex)`
- L28 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;`
- L31 _public prototype_ `static void GenerateBlendSampleWidget(TFunction<IDetailPropertyRow& (void)>InFunctor, FOnSampleMoved OnSampleMoved, const class UBlendSpace* BlendSpace, const int32 SampleIndex, bool bShowLabel);`
- L33 _public prototype_ `static void GenerateAnimationWidget(IDetailPropertyRow& PropertyRow, const UBlendSpace* BlendSpace, TSharedPtr<IPropertyHandle> AnimationProperty);`
- L35 _public prototype_ `static void GenerateSingleFrameBlendingWidget(IDetailPropertyRow& PropertyRow, TSharedPtr<IPropertyHandle> SingleFrameIndexProperty, TSharedPtr<IPropertyHandle> AnimationProperty);`
- L37 _public prototype_ `static void GenerateSampleGraphWidget(FDetailWidgetRow& Row, UAnimGraphNode_BlendSpaceGraphBase* BlendSpaceNode, int32 SampleIndex);`
- L39 _public prototype_ `static bool ShouldFilterAssetStatic(const FAssetData& AssetData, const UBlendSpace* BlendSpaceBase);`
- L43 _protected prototype_ `bool ShouldFilterAsset(const FAssetData& AssetData) const;` — Checks whether or not the specified asset should not be shown in the mini content browser when changing the animation
- L45 _protected prototype_ `FReply HandleAnalyzeAndDuplicateSample();`
- L46 _protected prototype_ `FReply HandleAnalyzeAndMoveSample();`
- L47 _protected prototype_ `FReply HandleAnalyzeAndMoveSampleX();`
- L48 _protected prototype_ `FReply HandleAnalyzeAndMoveSampleY();`
- L51 _private member_ `const class UBlendSpace* BlendSpace;` — Pointer to the current parent blend space for the customized blend sample
- L53 _private member_ `SBlendSpaceGridWidget* GridWidget;` — Parent grid widget object
- L55 _private member_ `int32 SampleIndex;` — Current sample index
- L57 _private member_ `TMap<FString, bool> bValidAdditiveTypes;` — Cached flags to check whether or not an additive animation type is compatible with the blend space

### `Source/Editor/Persona/Private/Customization/BlendSpaceDetails.h` (Private)


#### class `FBlendSpaceDetails`  
`class FBlendSpaceDetails : public IDetailCustomization, public FEditorUndoClient`  
_L16-45_
- inherits: `IDetailCustomization,FEditorUndoClient`
- L19 _public prototype_ `FBlendSpaceDetails();`
- L20 _public prototype_ `~FBlendSpaceDetails();`
- L22 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L28 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L31 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L32 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L36 _private prototype_ `FReply HandleClearSamples();`
- L37 _private prototype_ `FReply HandleAnalyzeSamples();`
- L38 _private prototype_ `void HandleAnalysisFunctionChanged(int32 AxisIndex, TSharedPtr<FString> NewItem);`
- L39 _private prototype_ `void RefreshDetails() const;`
- L41 _private member_ `IDetailLayoutBuilder* Builder;`
- L42 _private member_ `UBlendSpace* BlendSpace;`
- L43 _private member_ `TWeakObjectPtr<UAnimGraphNode_BlendSpaceGraphBase> BlendSpaceNode;`
- L44 _private member_ `TArray<TSharedPtr<FString>> AnalysisFunctionNames[3];`

### `Source/Editor/Persona/Private/Customization/InterpolationParameterDetails.h` (Private)


#### class `FInterpolationParameterDetails`  
`class FInterpolationParameterDetails : public IPropertyTypeCustomization`  
_L10-21_
- inherits: `IPropertyTypeCustomization`
- L13 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L19 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override` — IDetailCustomization interface
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Source/Editor/Persona/Private/Customization/SkeletalMeshRegionCustomization.h` (Private)


#### class `FNiagaraSkeletalMeshRegionBoneFilterDetails`  
`class FNiagaraSkeletalMeshRegionBoneFilterDetails : public IPropertyTypeCustomization`  
_L16-41_
- inherits: `IPropertyTypeCustomization`
- L19 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IDetailCustomization interface
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L29 _private prototype_ `FText HandleBoneNameComboBoxContentText() const;`
- L30 _private prototype_ `TSharedRef<SWidget> HandleBoneNameComboBoxGenerateWidget(FName StringItem);`
- L31 _private prototype_ `void HandleBoneNameComboBoxSelectionChanged(FName StringItem, ESelectInfo::Type SelectInfo);`
- L33 _private prototype_ `void OnComboOpening();`
- L36 _private member_ `USkeletalMesh* MeshObject;` — The mesh object whose details we're customizing.
- L38 _private member_ `TArray<FName> PossibleBoneNames;`
- L40 _private member_ `TSharedPtr<IPropertyHandle> BoneNameHandle;`

#### class `FNiagaraSkeletalMeshRegionMaterialFilterDetails`  
`class FNiagaraSkeletalMeshRegionMaterialFilterDetails : public IPropertyTypeCustomization`  
_L43-68_
- inherits: `IPropertyTypeCustomization`
- L46 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L52 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IDetailCustomization interface
- L53 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L56 _private prototype_ `FText HandleMaterialNameComboBoxContentText() const;`
- L57 _private prototype_ `TSharedRef<SWidget> HandleMaterialNameComboBoxGenerateWidget(TSharedPtr<FName> StringItem);`
- L58 _private prototype_ `void HandleMaterialNameComboBoxSelectionChanged(TSharedPtr<FName> StringItem, ESelectInfo::Type SelectInfo);`
- L60 _private prototype_ `void OnComboOpening();`
- L63 _private member_ `USkeletalMesh * MeshObject;` — The mesh object whose details we're customizing.
- L65 _private member_ `TArray<TSharedPtr<FName>> PossibleMaterialNames;`
- L67 _private member_ `TSharedPtr<IPropertyHandle> MaterialNameHandle;`

### `Source/Editor/Persona/Private/EditorObjectsTracker.h` (Private)


#### class `FEditorObjectTracker`  
`class FEditorObjectTracker : public FGCObject`  
_L18-51_
- inherits: `FGCObject`
- L21 _public function_ `FEditorObjectTracker(bool bInAllowOnePerClass = true) : bAllowOnePerClass(bInAllowOnePerClass)`
- L26 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface
- L27 _public function_ `virtual FString GetReferencerName() const override`
- L35 _public prototype_ `UObject* GetEditorObjectForClass( UClass* EdClass );` — Returns an existing editor object for the specified class or creates one if none exist
- L37 _public function_ `void SetAllowOnePerClass(bool bInAllowOnePerClass)`
- L44 _private member_ `bool bAllowOnePerClass;` — If true, it uses TMap, otherwise, it just uses TArray
- L47 _private member_ `TMap< TObjectPtr<UClass>, TObjectPtr<UObject> > EditorObjMap;` — Tracks editor objects created for details panel
- L50 _private member_ `TArray<TObjectPtr<UObject>> EditorObjectArray;` — Tracks editor objects created for detail panel

### `Source/Editor/Persona/Private/IPoseWatchManager.h` (Private)


#### class `IPoseWatchManager`  
`class IPoseWatchManager : public SCompoundWidget`  
_L20-60_
- inherits: `SCompoundWidget`
- desc: The public interface for the Pose Watch Manager widget
- L25 _public prototype_ `virtual void Refresh() = 0;` — Sends a requests to refresh itself the next chance it gets
- L28 _public prototype_ `virtual void FullRefresh() = 0;` — Sends a request to clear the entire tree and rebuild it from scratch
- L31 _public prototype_ `virtual TAttribute<FText> GetFilterHighlightText() const = 0;` — @return Returns a string to use for highlighting results in the outliner list
- L34 _public prototype_ `virtual const STreeView<FPoseWatchManagerTreeItemPtr>& GetTree() const = 0;` — Get a const reference to the actual tree hierarchy
- L37 _public prototype_ `virtual void SetKeyboardFocus() = 0;` — Set the keyboard focus to the outliner
- L40 _public prototype_ `virtual EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const = 0;` — Return the sorting mode for the specified ColumnId
- L42 _public prototype_ `virtual uint32 GetTypeSortPriority(const IPoseWatchManagerTreeItem& Item) const = 0;`
- L45 _public prototype_ `virtual void RequestSort() = 0;` — Request that the tree be sorted at a convenient time
- L48 _public prototype_ `virtual void Rename_Execute() = 0;` — Executes rename.
- L51 _public prototype_ `virtual void SetSelection(const TFunctionRef<bool(IPoseWatchManagerTreeItem&)> Selector) = 0;` — Set the item selection of the outliner based on a selector function. Any items which return true will be added
- L53 _public member_ `UAnimBlueprint* AnimBlueprint;`
- L56 _public function_ `const TSharedPtr<FPoseWatchManagerDefaultMode> GetMode() const` — Get the active PoseWatchManagerMode
- L59 _protected member_ `TSharedPtr<FPoseWatchManagerDefaultMode> Mode;`

### `Source/Editor/Persona/Private/IPoseWatchManagerColumn.h` (Private)


#### class `IPoseWatchManagerColumn`  
`class IPoseWatchManagerColumn : public TSharedFromThis<IPoseWatchManagerColumn>`  
_L13-29_
- inherits: `TSharedFromThis<IPoseWatchManagerColumn>`
- L16 _public prototype_ `virtual ~IPoseWatchManagerColumn() = default;`
- L18 _public prototype_ `virtual FName GetColumnID() = 0;`
- L20 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() = 0;`
- L22 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FPoseWatchManagerTreeItemRef TreeItem, const STableRow<FPoseWatchManagerTreeItemPtr>& Row) = 0;`
- L24 _public function_ `virtual void PopulateSearchStrings(const IPoseWatchManagerTreeItem& Item, TArray<FString>& OutSearchStrings) const`
- L26 _public function_ `virtual bool SupportsSorting() const`
- L28 _public function_ `virtual void SortItems(TArray<FPoseWatchManagerTreeItemPtr>& OutItems, const EColumnSortMode::Type SortMode) const`

### `Source/Editor/Persona/Private/IPoseWatchManagerTreeItem.h` (Private)


#### struct `IPoseWatchManagerTreeItem`  
`struct IPoseWatchManagerTreeItem : TSharedFromThis<IPoseWatchManagerTreeItem>`  
_L15-127_
- inherits: `TSharedFromThis<IPoseWatchManagerTreeItem>`
- L21 _public prototype_ `DECLARE_DELEGATE(FOnRenameRequest);` — Delegate for hooking up an inline editable text block to be notified that a rename is requested.
- L22 _public member_ `FOnRenameRequest RenameRequestEvent;`
- L26 _protected function_ `IPoseWatchManagerTreeItem(EPoseWatchTreeItemType InType) : Parent(nullptr), TreeType(InType)` — Default constructor
- L27 _protected prototype_ `virtual ~IPoseWatchManagerTreeItem() = default;`
- L31 _public function_ `FPoseWatchManagerTreeItemPtr GetParent() const` — Get this item's parent. If nullptr then belongs to the root of the tree
- L37 _public prototype_ `virtual bool IsAssignedFolder() const = 0;` — Returns true if this tree item is inside a folder
- L40 _public prototype_ `virtual void SetIsVisible(const bool bVisible) = 0;` — Sets this tree item's visibility
- L43 _public function_ `virtual void SetIsExpanded(const bool bIsExpanded)` — Sets whether or not this tree item is expanded
- L46 _public function_ `void AddChild(FPoseWatchManagerTreeItemRef Child)` — Add a child to this tree item
- L54 _public function_ `FORCEINLINE const TSet<TWeakPtr<IPoseWatchManagerTreeItem>>& GetChildren() const` — Get this item's children, if any.
- L61 _public function_ `template <typename T> T* CastTo()` — Attempt to cast this item to another type if it is of that type. Returns nullptr if it fails
- L67 _public function_ `template <typename T> const T* CastTo() const` — Attempt to cast this item to another type if it is of that type. Returns nullptr if it fails
- L73 _public function_ `template <typename T> bool IsA() const` — Returns true if this item is of the specified type
- L79 _public prototype_ `virtual bool IsValid() const = 0;` — Returns true if the data the item references is valid
- L82 _public prototype_ `virtual FObjectKey GetID() const = 0;` — Get the ID that represents this tree item. Used to reference this item in a map
- L85 _public prototype_ `virtual FString GetDisplayString() const = 0;` — Get the raw string to display for this tree item - used for sorting
- L88 _public function_ `virtual TSharedRef<SWidget> GenerateLabelWidget(IPoseWatchManager& Outliner, const STableRow<FPoseWatchManagerTreeItemPtr>& InRow)` — Generate the label widget for this item
- L91 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenu() = 0;` — Generate a context menu for this item. Only called if *only* this item is selected.
- L94 _public prototype_ `virtual bool GetVisibility() const = 0;` — Query this items visibility state. Only called if the item type has visibility info
- L97 _public function_ `virtual bool HasChildren() const` — Returns true if this tree item has at least one child
- L100 _public function_ `virtual bool IsExpanded() const` — Returns true if this tree item is expanded
- L102 _public function_ `virtual bool IsEnabled() const`
- L104 _public prototype_ `virtual void OnRemoved() = 0;`
- L107 _public function_ `virtual FColor GetColor() const` — Returns the view port render color
- L110 _public function_ `virtual void SetColor(const FColor& InColor)` — Sets the view port render color
- L113 _public function_ `virtual bool ShouldDisplayColorPicker() const` — Returns true if the view port render color for this item can be changed
- L117 _protected member_ `TWeakPtr<IPoseWatchManagerTreeItem> Parent;` — This item's parent tree item
- L120 _protected member_ `TSet<TWeakPtr<IPoseWatchManagerTreeItem>> Children;` — Array of children contained underneath this item
- L123 _protected member_ `static const EPoseWatchTreeItemType Type;` — Static type identifier for the base class tree item
- L126 _protected member_ `EPoseWatchTreeItemType TreeType;` — Tree item type identifier
- L129 _function_ `template <> inline const IPoseWatchManagerTreeItem* IPoseWatchManagerTreeItem::CastTo<IPoseWatchManagerTreeItem>() const`
- L134 _function_ `template <> inline IPoseWatchManagerTreeItem* IPoseWatchManagerTreeItem::CastTo<IPoseWatchManagerTreeItem>()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PERSONA_API`
- L21 _delegate_ `DECLARE_DELEGATE(FOnRenameRequest);` — Delegate for hooking up an inline editable text block to be notified that a rename is requested.

### `Source/Editor/Persona/Private/LODInfoUILayout.h` (Private)


#### class `ULODInfoUILayout`  
`class ULODInfoUILayout : public UObject`  
_L18-43_
- reflection: `UCLASS(HideCategories=Object, MinimalAPI)`
- inherits: `UObject`
- L23 _public prototype_ `void SetReferenceLODInfo(TWeakPtr<IPersonaToolkit> InPersonaToolkit, int32 InLODIndex);`
- L24 _public prototype_ `void RefreshReferenceLODInfo();`
- L26 _public function_ `TSharedPtr<IPersonaToolkit> GetPersonaToolkit() const`
- L32 _public function_ `int32 GetLODIndex() const`
- L34 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L38 _public member_ `struct FSkeletalMeshLODInfo LODInfo;` — `UPROPERTY(EditAnywhere, Category = LevelOfDetail)` — Struct containing information for a LOD level, such as materials to use, and when use the LOD.
- L41 _private member_ `TWeakPtr<IPersonaToolkit> PersonaToolkit;`
- L42 _private member_ `int32 LODIndex;`

### `Source/Editor/Persona/Private/PersonaAssetFamily.h` (Private)


#### class `UAnimationEditorsAssetFamilyExtension_SkeletonAsset`  
`class UAnimationEditorsAssetFamilyExtension_SkeletonAsset : public UAnimationEditorsAssetFamilyExtension`  
_L21-34_
- reflection: `UCLASS()`
- inherits: `UAnimationEditorsAssetFamilyExtension`
- L27 _public prototype_ `virtual TObjectPtr<UClass> GetAssetClass() const override;` — UAnimationEditorsAssetFamilyExtension
- L28 _public prototype_ `virtual FText GetAssetTypeDisplayName() const override;`
- L29 _public prototype_ `virtual const FSlateBrush* GetAssetTypeDisplayIcon() const override;`
- L30 _public prototype_ `virtual void FindAssetsOfType(TArray<FAssetData>& OutAssets, const IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) const override;`
- L31 _public prototype_ `virtual bool IsAssetCompatible(const FAssetData& InAssetData, const IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) const override;`
- L32 _public prototype_ `virtual void FindCounterpartAssets(const UObject* InAsset, IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) override;`
- L33 _public prototype_ `virtual void GetPosition(FName& OutBeforeClass, FName& OutAfterClass) const override;`

#### class `UAnimationEditorsAssetFamilyExtension_SkeletalMeshAsset`  
`class UAnimationEditorsAssetFamilyExtension_SkeletalMeshAsset : public UAnimationEditorsAssetFamilyExtension`  
_L37-50_
- reflection: `UCLASS()`
- inherits: `UAnimationEditorsAssetFamilyExtension`
- L43 _public prototype_ `virtual TObjectPtr<UClass> GetAssetClass() const override;` — UAnimationEditorsAssetFamilyExtension
- L44 _public prototype_ `virtual FText GetAssetTypeDisplayName() const override;`
- L45 _public prototype_ `virtual const FSlateBrush* GetAssetTypeDisplayIcon() const override;`
- L46 _public prototype_ `virtual void FindAssetsOfType(TArray<FAssetData>& OutAssets, const IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) const override;`
- L47 _public prototype_ `virtual bool IsAssetCompatible(const FAssetData& InAssetData, const IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) const override;`
- L48 _public prototype_ `virtual void FindCounterpartAssets(const UObject* InAsset, IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) override;`
- L49 _public prototype_ `virtual void GetPosition(FName& OutBeforeClass, FName& OutAfterClass) const override;`

#### class `UAnimationEditorsAssetFamilyExtension_AnimationAsset`  
`class UAnimationEditorsAssetFamilyExtension_AnimationAsset : public UAnimationEditorsAssetFamilyExtension`  
_L53-66_
- reflection: `UCLASS()`
- inherits: `UAnimationEditorsAssetFamilyExtension`
- L59 _public prototype_ `virtual TObjectPtr<UClass> GetAssetClass() const override;` — UAnimationEditorsAssetFamilyExtension
- L60 _public prototype_ `virtual FText GetAssetTypeDisplayName() const override;`
- L61 _public prototype_ `virtual const FSlateBrush* GetAssetTypeDisplayIcon() const override;`
- L62 _public prototype_ `virtual void FindAssetsOfType(TArray<FAssetData>& OutAssets, const IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) const override;`
- L63 _public prototype_ `virtual bool IsAssetCompatible(const FAssetData& InAssetData, const IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) const override;`
- L64 _public prototype_ `virtual void FindCounterpartAssets(const UObject* InAsset, IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) override;`
- L65 _public prototype_ `virtual void GetPosition(FName& OutBeforeClass, FName& OutAfterClass) const override;`

#### class `UAnimationEditorsAssetFamilyExtension_AnimBlueprintAsset`  
`class UAnimationEditorsAssetFamilyExtension_AnimBlueprintAsset : public UAnimationEditorsAssetFamilyExtension`  
_L69-82_
- reflection: `UCLASS()`
- inherits: `UAnimationEditorsAssetFamilyExtension`
- L75 _public prototype_ `virtual TObjectPtr<UClass> GetAssetClass() const override;` — UAnimationEditorsAssetFamilyExtension
- L76 _public prototype_ `virtual FText GetAssetTypeDisplayName() const override;`
- L77 _public prototype_ `virtual const FSlateBrush* GetAssetTypeDisplayIcon() const override;`
- L78 _public prototype_ `virtual void FindAssetsOfType(TArray<FAssetData>& OutAssets, const IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) const override;`
- L79 _public prototype_ `virtual bool IsAssetCompatible(const FAssetData& InAssetData, const IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) const override;`
- L80 _public prototype_ `virtual void FindCounterpartAssets(const UObject* InAsset, IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) override;`
- L81 _public prototype_ `virtual void GetPosition(FName& OutBeforeClass, FName& OutAfterClass) const override;`

#### class `UAnimationEditorsAssetFamilyExtension_PhysicsAsset`  
`class UAnimationEditorsAssetFamilyExtension_PhysicsAsset : public UAnimationEditorsAssetFamilyExtension`  
_L85-98_
- reflection: `UCLASS()`
- inherits: `UAnimationEditorsAssetFamilyExtension`
- L91 _public prototype_ `virtual TObjectPtr<UClass> GetAssetClass() const override;` — UAnimationEditorsAssetFamilyExtension
- L92 _public prototype_ `virtual FText GetAssetTypeDisplayName() const override;`
- L93 _public prototype_ `virtual const FSlateBrush* GetAssetTypeDisplayIcon() const override;`
- L94 _public prototype_ `virtual void FindAssetsOfType(TArray<FAssetData>& OutAssets, const IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) const override;`
- L95 _public prototype_ `virtual bool IsAssetCompatible(const FAssetData& InAssetData, const IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) const override;`
- L96 _public prototype_ `virtual void FindCounterpartAssets(const UObject* InAsset, IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) override;`
- L97 _public prototype_ `virtual void GetPosition(FName& OutBeforeClass, FName& OutAfterClass) const override;`

#### class `FPersonaAssetFamily`  
`class FPersonaAssetFamily : public IAssetFamily, public TSharedFromThis<FPersonaAssetFamily>, public IAnimationEditorsAssetFamilyInterface, public FGCObject`  
_L100-166_
- inherits: `IAssetFamily,TSharedFromThis<FPersonaAssetFamily>,IAnimationEditorsAssetFamilyInterface,FGCObject`
- L111 _public prototype_ `FPersonaAssetFamily(const UObject* InFromObject);`
- L112 _public prototype_ `FPersonaAssetFamily(const UObject* InFromObject, const TSharedRef<FPersonaAssetFamily> InFromFamily);`
- L114 _public prototype_ `virtual ~FPersonaAssetFamily() = default;`
- L117 _public prototype_ `virtual void GetAssetTypes(TArray<UClass*>& OutAssetTypes) const override;` — IAssetFamily interface
- L118 _public prototype_ `virtual FAssetData FindAssetOfType(UClass* InAssetClass) const override;`
- L119 _public prototype_ `virtual void FindAssetsOfType(UClass* InAssetClass, TArray<FAssetData>& OutAssets) const override;`
- L120 _public prototype_ `virtual FText GetAssetTypeDisplayName(UClass* InAssetClass) const override;`
- L121 _public prototype_ `virtual const FSlateBrush* GetAssetTypeDisplayIcon(UClass* InAssetClass) const override;`
- L122 _public prototype_ `virtual FSlateColor GetAssetTypeDisplayTint(UClass* InAssetClass) const override;`
- L123 _public prototype_ `virtual bool IsAssetCompatible(const FAssetData& InAssetData) const override;`
- L124 _public prototype_ `virtual UClass* GetAssetFamilyClass(UClass* InClass) const override;`
- L125 _public prototype_ `void RecordAssetOpened(const FAssetData& InAssetData);`
- L126 _public function_ `DECLARE_DERIVED_EVENT(FPersonaAssetFamily, IAssetFamily::FOnAssetOpened, FOnAssetOpened) virtual FOnAssetOpened& GetOnAssetOpened() override`
- L128 _public function_ `DECLARE_DERIVED_EVENT(FPersonaAssetFamily, IAssetFamily::FOnAssetFamilyChanged, FOnAssetFamilyChanged) virtual FOnAssetFamilyChanged& GetOnAssetFamilyChanged() override`
- L132 _public prototype_ `virtual bool IsAssetTypeInFamily(const TObjectPtr<UClass> InClass) const override;` — IAnimationEditorsAssetFamilyInterface
- L133 _public prototype_ `virtual TWeakObjectPtr<const UObject> GetAssetOfType(const TObjectPtr<UClass> InClass) const override;`
- L134 _public prototype_ `virtual bool SetAssetOfType(const TObjectPtr<UClass> InClass, TWeakObjectPtr<const UObject> InObject) override;`
- L137 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject
- L138 _public prototype_ `virtual FString GetReferencerName() const override;`
- L141 _public function_ `template <typename T> TObjectPtr<const T> GetAssetOfType() const`
- L147 _private prototype_ `FExtenderObjects* GetExtensionForClass(const TObjectPtr<const UClass> InClass);`
- L148 _private prototype_ `const FExtenderObjects* const GetExtensionForClass(const TObjectPtr<const UClass> InClass) const;`
- L151 _private prototype_ `void Initialize();` — Initialization to avoid shared ptr access in constructor
- L154 _private prototype_ `void OnSettingsChange(const UPersonaOptions* InOptions, EPropertyChangeType::Type InChangeType);` — Hande key persona settings changes (e.g. skeleton compatibilty)
- L159 _private member_ `TArray<FExtenderObjects> Extenders;`
- L162 _private member_ `FOnAssetOpened OnAssetOpened;` — Event fired when an asset is opened
- L165 _private member_ `FOnAssetFamilyChanged OnAssetFamilyChanged;` — Event fired when an asset family changes (e.g. relationships are altered)

#### struct `FPersonaAssetFamily::FExtenderObjects`  
`struct FExtenderObjects`  
_L103-108_
- L105 _public member_ `TObjectPtr<UAnimationEditorsAssetFamilyExtension> Extension;`
- L107 _public member_ `TWeakObjectPtr<const UObject> Asset;`

#### Free symbols / members of external scopes

- L126 _delegate_ `DECLARE_DERIVED_EVENT(FPersonaAssetFamily, IAssetFamily::FOnAssetOpened, FOnAssetOpened) virtual FOnAssetOpened& GetOnAssetOpened() override { return OnAssetOpened; } DECLARE_DERIVED_EVENT(FPersonaAssetFamily, IAssetFamily::FOnAssetFamilyChanged, FOnAssetFamilyChanged) virtual FOnAssetFamilyChanged& GetOnAssetFamilyChanged() override { return OnAssetFamilyChanged; } virtual bool IsAssetTypeInFamily(const TObjectPtr<UClass> InClass) const override;`
- L128 _delegate_ `DECLARE_DERIVED_EVENT(FPersonaAssetFamily, IAssetFamily::FOnAssetFamilyChanged, FOnAssetFamilyChanged) virtual FOnAssetFamilyChanged& GetOnAssetFamilyChanged() override { return OnAssetFamilyChanged; } virtual bool IsAssetTypeInFamily(const TObjectPtr<UClass> InClass) const override;`

### `Source/Editor/Persona/Private/PersonaAssetFamilyManager.h` (Private)


#### class `FPersonaAssetFamilyManager`  
`class FPersonaAssetFamilyManager`  
_L12-34_
- desc: Central registry of persona asset families
- L16 _public prototype_ `static FPersonaAssetFamilyManager& Get();` — Singleton access
- L19 _public prototype_ `TSharedRef<IAssetFamily> CreatePersonaAssetFamily(const UObject* InAsset);` — Create an asset family using the supplied asset
- L22 _public prototype_ `void BroadcastAssetFamilyChange();` — All asset families have changed (e.g. universal compatibility)
- L25 _public prototype_ `void RecordAssetOpened(const FAssetData& InAssetData) const;` — Record an asset being opened - forward to all compatible asset families
- L29 _private function_ `FPersonaAssetFamilyManager()` — Hidden constructor
- L33 _private member_ `TArray<TWeakPtr<FPersonaAssetFamily>> AssetFamilies;` — All current asset families

### `Source/Editor/Persona/Private/PersonaBlendSpaceAnalysis.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace BlendSpaceAnalysis`
- L13 _prototype_ `FVector CalculateSampleValue(const UBlendSpace& BlendSpace, const UAnimSequence& Animation, const float RateScale, const FVector& OriginalPosition, bool bAnalyzed[3]);` (scope `BlendSpaceAnalysis`) — Calculates the sample value/position and indicates if it needed to be analyzed. Note that the original position is passed in, and its elements will be used in the output where analysis doesn't need to be done.
- L24 _prototype_ `UAnalysisProperties* MakeAnalysisProperties(UObject* Outer, const FString& FunctionName);` (scope `BlendSpaceAnalysis`) — This will return an instance derived from UAnalysisProperties that is suitable for the Function. The caller will pass in a suitable owning object, outer, that the implementation should assign as owner of the newly created object.
- L29 _prototype_ `TArray<FString> GetAnalysisFunctions();` (scope `BlendSpaceAnalysis`) — This will return the names of the functions handled

### `Source/Editor/Persona/Private/PersonaEditorModeManager.h` (Private)


#### class `FPersonaEditorModeManager`  
`class FPersonaEditorModeManager : public IPersonaEditorModeManager`  
_L9-18_
- inherits: `IPersonaEditorModeManager`
- desc: Persona-specific extensions to the asset editor mode manager
- L13 _public prototype_ `virtual bool GetCameraTarget(FSphere& OutTarget) const override;` — IPersonaEditorModeManager interface
- L14 _public prototype_ `virtual void GetOnScreenDebugInfo(TArray<FText>& OutDebugText) const override;`
- L17 _public prototype_ `virtual void SetPreviewScene(FPreviewScene* NewPreviewScene) override;` — FAssetEditorModeManager overrides

### `Source/Editor/Persona/Private/PersonaMeshDetails.h` (Private)


#### struct `FClothAssetSubmeshIndex`  
`struct FClothAssetSubmeshIndex`  
_L41-57_
- desc: Struct to uniquely identify clothing applied to a material section Contains index into the ClothingAssets array and the submesh index.
- L43 _public function_ `FClothAssetSubmeshIndex(int32 InAssetIndex, int32 InSubmeshIndex) : AssetIndex(InAssetIndex) , SubmeshIndex(InSubmeshIndex)`
- L48 _public member_ `int32 AssetIndex;`
- L49 _public member_ `int32 SubmeshIndex;`
- L51 _public function_ `bool operator==(const FClothAssetSubmeshIndex& Other) const`

#### struct `FClothingComboInfo`  
`struct FClothingComboInfo`  
_L59-69_
- L62 _public member_ `TArray<TSharedPtr< class STextComboBox >> ClothingComboBoxes;` — Per-material clothing combo boxes, array size must be same to # of sections
- L64 _public member_ `TArray<TSharedPtr<FString> > ClothingComboStrings;` — Clothing combo box strings
- L66 _public member_ `TMap<FString, FClothAssetSubmeshIndex> ClothingComboStringReverseLookup;` — Mapping from a combo box string to the asset and submesh it was generated from
- L68 _public member_ `TArray<int32> ClothingComboSelectedIndices;` — The currently-selected index from each clothing combo box

#### struct `FSectionLocalizer`  
`struct FSectionLocalizer`  
_L71-90_
- L73 _public function_ `FSectionLocalizer(int32 InLODIndex, int32 InSectionIndex) : LODIndex(InLODIndex) , SectionIndex(InSectionIndex)`
- L78 _public function_ `bool operator==(const FSectionLocalizer& Other) const`
- L83 _public function_ `bool operator!=(const FSectionLocalizer& Other) const`
- L88 _public member_ `int32 LODIndex;`
- L89 _public member_ `int32 SectionIndex;`

#### class `FSkeletalMeshReductionSettingsLayout`  
`class FSkeletalMeshReductionSettingsLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FSkeletalMeshReductionSettingsLayout>`  
_L92-251_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FSkeletalMeshReductionSettingsLayout>`
- L95 _public prototype_ `FSkeletalMeshReductionSettingsLayout(FSkeletalMeshOptimizationSettings& InReductionettings, bool InbIsLODModelbuildDataAvailable, int32 InLODIndex, FIsLODSettingsEnabledDelegate InIsLODSettingsEnabledDelegate, FModifyMeshLODSettingsDelegate InModifyMeshLODSettingsDelegate);`
- L96 _public prototype_ `virtual ~FSkeletalMeshReductionSettingsLayout() = default;`
- L106 _public prototype_ `DECLARE_DELEGATE_RetVal(float, FGetFloatDelegate);`
- L107 _public prototype_ `DECLARE_DELEGATE_OneParam(FSetFloatDelegate, float);`
- L109 _public prototype_ `DECLARE_DELEGATE_RetVal(int32, FGetIntegerDelegate);`
- L110 _public prototype_ `DECLARE_DELEGATE_OneParam(FSetIntegerDelegate, int32);`
- L112 _public prototype_ `DECLARE_DELEGATE_RetVal(uint32, FGetUnsignedIntegerDelegate);`
- L113 _public prototype_ `DECLARE_DELEGATE_OneParam(FSetUnsignedIntegerDelegate, uint32);`
- L115 _public prototype_ `DECLARE_DELEGATE_RetVal(ECheckBoxState, FGetCheckBoxStateDelegate);`
- L116 _public prototype_ `DECLARE_DELEGATE_OneParam(FSetCheckBoxStateDelegate, ECheckBoxState);`
- L118 _public function_ `void UnbindReductionSettings()`
- L124 _private function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override` — IDetailCustomNodeBuilder Interface
- L125 _private prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L126 _private prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L127 _private function_ `virtual void Tick(float DeltaTime) override`
- L128 _private function_ `virtual bool RequiresTick() const override`
- L129 _private function_ `virtual FName GetName() const override`
- L130 _private function_ `virtual bool InitiallyCollapsed() const override`
- L132 _private prototype_ `bool IsReductionEnabled() const;`
- L135 _private prototype_ `FDetailWidgetRow& AddFloatRow(IDetailChildrenBuilder& ChildrenBuilder, const FText RowTitleText, const FText RowNameContentText, const FText RowNameContentTootlipText, FName RowTag, const float MinSliderValue, const float MaxSliderValue, FGetFloatDelegate GetterDelegate, FSetFloatDelegate SetterDelegate);` — Custom Row Add utilities
- L136 _private prototype_ `FDetailWidgetRow& AddBoolRow(IDetailChildrenBuilder& ChildrenBuilder, const FText RowTitleText, const FText RowNameContentText, const FText RowNameContentToolitipText, FName RowTag, FGetCheckBoxStateDelegate GetterDelegate, FSetCheckBoxStateDelegate SetterDelegate);`
- L137 _private prototype_ `FDetailWidgetRow& AddIntegerRow(IDetailChildrenBuilder& ChildrenBuilder, const FText RowTitleText, const FText RowNameContentText, const FText RowNameContentTootlipText, FName RowTag, const int32 MinSliderValue, const int32 MaxSliderValue, FGetIntegerDelegate GetterDelegate, FSetIntegerDelegate SetterDelegate);`
- L138 _private prototype_ `FDetailWidgetRow& AddUnsignedIntegerRow(IDetailChildrenBuilder& ChildrenBuilder, const FText RowTitleText, const FText RowNameContentText, const FText RowNameContentTootlipText, FName RowTag, const uint32 MinSliderValue, const uint32 MaxSliderValue, FGetUnsignedIntegerDelegate GetterDelegate, FSetUnsignedIntegerDelegate SetterDelegate);`
- L139 _private prototype_ `void AddBaseLODRow(IDetailChildrenBuilder& ChildrenBuilder);`
- L141 _private prototype_ `void SetPercentAndAbsoluteVisibility(FDetailWidgetRow& Row, SkeletalMeshTerminationCriterion FirstCriterion, SkeletalMeshTerminationCriterion SecondCriterion);`
- L143 _private function_ `int32 GetBaseLODValue() const`
- L147 _private function_ `void SetBaseLODValue(int32 Value)`
- L151 _private prototype_ `TSharedRef<class SWidget> FillReductionMethodMenu();`
- L152 _private prototype_ `FText GetReductionMethodText() const;`
- L154 _private prototype_ `TSharedRef<class SWidget> FillReductionImportanceMenu(const EImportanceType Importance);`
- L155 _private prototype_ `FText GetReductionImportanceText(const EImportanceType Importance) const;`
- L157 _private prototype_ `TSharedRef<class SWidget> FillReductionTerminationCriterionMenu();`
- L158 _private prototype_ `FText GetReductionTerminationCriterionText() const;`
- L160 _private prototype_ `float GetNumTrianglesPercentage() const;`
- L161 _private prototype_ `void SetNumTrianglesPercentage(float Value);`
- L163 _private prototype_ `float GetNumVerticesPercentage() const;`
- L164 _private prototype_ `void SetNumVerticesPercentage(float Value);`
- L166 _private prototype_ `int32 GetNumMaxTrianglesCount() const;`
- L167 _private prototype_ `void SetNumMaxTrianglesCount(int32 Value);`
- L169 _private prototype_ `int32 GetNumMaxVerticesCount() const;`
- L170 _private prototype_ `void SetNumMaxVerticesCount(int32 Value);`
- L172 _private prototype_ `uint32 GetNumMaxTrianglesPercentageCount() const;`
- L173 _private prototype_ `void SetNumMaxTrianglesPercentageCount(uint32 Value);`
- L175 _private prototype_ `uint32 GetNumMaxVerticesPercentageCount() const;`
- L176 _private prototype_ `void SetNumMaxVerticesPercentageCount(uint32 Value);`
- L178 _private prototype_ `float GetAccuracyPercentage() const;`
- L179 _private prototype_ `void SetAccuracyPercentage(float Value);`
- L181 _private prototype_ `ECheckBoxState ShouldRecomputeNormals() const;`
- L182 _private prototype_ `void OnRecomputeNormalsChanged(ECheckBoxState NewState);`
- L184 _private prototype_ `float GetNormalsThreshold() const;`
- L185 _private prototype_ `void SetNormalsThreshold(float Value);`
- L187 _private prototype_ `float GetWeldingThreshold() const;`
- L188 _private prototype_ `void SetWeldingThreshold(float Value);`
- L190 _private prototype_ `ECheckBoxState GetLockEdges() const;`
- L191 _private prototype_ `void SetLockEdges(ECheckBoxState NewState);`
- L193 _private prototype_ `ECheckBoxState GetLockColorBounaries() const;`
- L194 _private prototype_ `void SetLockColorBounaries(ECheckBoxState NewState);`
- L196 _private prototype_ `ECheckBoxState GetImproveTrianglesForCloth() const;`
- L197 _private prototype_ `void SetImproveTrianglesForCloth(ECheckBoxState NewState);`
- L199 _private prototype_ `ECheckBoxState GetEnforceBoneBoundaries() const;`
- L200 _private prototype_ `void SetEnforceBoneBoundaries(ECheckBoxState NewState);`
- L202 _private prototype_ `ECheckBoxState GetMergeCoincidentVertBones() const;`
- L203 _private prototype_ `void SetMergeCoincidentVertBones(ECheckBoxState NewState);`
- L205 _private prototype_ `float GetVolumeImportance() const;`
- L206 _private prototype_ `void SetVolumeImportance(float Value);`
- L208 _private prototype_ `ECheckBoxState GetRemapMorphTargets() const;`
- L209 _private prototype_ `void SetRemapMorphTargets(ECheckBoxState NewState);`
- L211 _private prototype_ `int32 GetMaxBonesPerVertex() const;`
- L212 _private prototype_ `void SetMaxBonesPerVertex(int32 Value);`
- L215 _private prototype_ `EVisibility GetVisibiltyIfCurrentReductionMethodIsNot(SkeletalMeshOptimizationType ReductionType) const;` — Used the the thrid-party UI.
- L218 _private prototype_ `EVisibility ShowIfCurrentCriterionIs(TArray<SkeletalMeshTerminationCriterion> TerminationCriterionArray) const;` — Used by the native tool UI.
- L221 _private prototype_ `bool UseNativeLODTool() const;` — Detect usage of thirdparty vs native tool
- L222 _private prototype_ `bool UseNativeReductionTool() const;`
- L228 _private prototype_ `EVisibility GetVisibilityForThirdPartyTool() const;` — Used to hide parameters that only make sense for the third party tool. @return EVisibility::Visible if we are using the simplygon tool, otherwise EVisibility::Hidden
- L231 _private member_ `FSkeletalMeshOptimizationSettings& ReductionSettings;`
- L232 _private member_ `bool bIsLODModelbuildDataAvailable;`
- L233 _private member_ `int32 LODIndex;`
- L234 _private member_ `FIsLODSettingsEnabledDelegate IsLODSettingsEnabledDelegate;`
- L235 _private member_ `FModifyMeshLODSettingsDelegate ModifyMeshLODSettingsDelegate;`
- L237 _private member_ `UEnum* EnumReductionMethod;`
- L238 _private member_ `UEnum* EnumImportance;`
- L239 _private member_ `UEnum* EnumTerminationCriterion;`
- L250 _private member_ `TArray<FSliderStateData> SliderStateDataArray;`

#### enum `FSkeletalMeshReductionSettingsLayout::EImportanceType`  
`enum EImportanceType`  
_L98-104_
- L100 _public enumerator_ `ID_Silhouette`
- L101 _public enumerator_ `ID_Texture`
- L102 _public enumerator_ `ID_Shading`
- L103 _public enumerator_ `ID_Skinning`

#### struct `FSkeletalMeshReductionSettingsLayout::FSliderStateData`  
`struct FSliderStateData`  
_L243-249_
- desc: Use this data to keep a valid reference so the helper lambda can have persistent data Helper lambda are use with spinner to not do a transaction when spinning with mouse movement
- L245 _public member_ `float MovementValueFloat = 0.0f;`
- L246 _public member_ `int32 MovementValueInt = 0;`
- L247 _public member_ `uint32 MovementValueUnsignedInt = 0;`
- L248 _public member_ `bool bSliderActiveMode = false;`

#### class `FSkeletalMeshBuildSettingsLayout`  
`class FSkeletalMeshBuildSettingsLayout : public IDetailCustomNodeBuilder, public TSharedFromThis<FSkeletalMeshBuildSettingsLayout>`  
_L253-348_
- inherits: `IDetailCustomNodeBuilder,TSharedFromThis<FSkeletalMeshBuildSettingsLayout>`
- L256 _public prototype_ `FSkeletalMeshBuildSettingsLayout(FSkeletalMeshBuildSettings& InBuildSettings, int32 InLODIndex, FIsLODSettingsEnabledDelegate InIsBuildSettingsEnabledDelegate, FModifyMeshLODSettingsDelegate InModifyMeshLODSettingsDelegate);`
- L257 _public prototype_ `virtual ~FSkeletalMeshBuildSettingsLayout() = default;`
- L260 _public prototype_ `DECLARE_DELEGATE_RetVal(float, FGetFloatDelegate);`
- L261 _public prototype_ `DECLARE_DELEGATE_OneParam(FSetFloatDelegate, float);`
- L263 _public prototype_ `DECLARE_DELEGATE_RetVal(int32, FGetIntegerDelegate);`
- L264 _public prototype_ `DECLARE_DELEGATE_OneParam(FSetIntegerDelegate, int32);`
- L266 _public function_ `void UnbindBuildSettings()`
- L273 _private function_ `virtual void SetOnRebuildChildren(FSimpleDelegate InOnRegenerateChildren) override` — IDetailCustomNodeBuilder Interface
- L274 _private prototype_ `virtual void GenerateHeaderRowContent(FDetailWidgetRow& NodeRow) override;`
- L275 _private prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& ChildrenBuilder) override;`
- L276 _private function_ `virtual void Tick(float DeltaTime) override`
- L277 _private function_ `virtual bool RequiresTick() const override`
- L278 _private function_ `virtual FName GetName() const override`
- L279 _private function_ `virtual bool InitiallyCollapsed() const override`
- L281 _private prototype_ `bool IsBuildEnabled() const;`
- L284 _private prototype_ `FDetailWidgetRow& AddFloatRow(IDetailChildrenBuilder& ChildrenBuilder, const FText RowTitleText, const FText RowNameContentText, const FText RowNameContentTootlipText, const float MinSliderValue, const float MaxSliderValue, FGetFloatDelegate GetterDelegate, FSetFloatDelegate SetterDelegate);` — Custom Row Add utilities
- L285 _private prototype_ `FDetailWidgetRow& AddIntegerRow( IDetailChildrenBuilder& ChildrenBuilder, const FText& RowTitleText, const FText& RowNameContentText, const FText& RowNameContentTooltipText, FName RowTag, const int32 MinSliderValue, const int32 MaxSliderValue, const FGetIntegerDelegate& GetterDelegate, const FSetIntegerDelegate& SetterDelegate);`
- L296 _private prototype_ `float GetThresholdPosition() const;`
- L297 _private prototype_ `void SetThresholdPosition(float Value);`
- L299 _private prototype_ `float GetThresholdTangentNormal() const;`
- L300 _private prototype_ `void SetThresholdTangentNormal(float Value);`
- L302 _private prototype_ `float GetThresholdUV() const;`
- L303 _private prototype_ `void SetThresholdUV(float Value);`
- L305 _private prototype_ `float GetMorphThresholdPosition() const;`
- L306 _private prototype_ `void SetMorphThresholdPosition(float Value);`
- L308 _private prototype_ `int32 GetBoneInfluenceLimit() const;`
- L309 _private prototype_ `void SetBoneInfluenceLimit(int32 Value);`
- L311 _private prototype_ `ECheckBoxState ShouldRecomputeNormals() const;`
- L312 _private prototype_ `ECheckBoxState ShouldRecomputeTangents() const;`
- L313 _private prototype_ `ECheckBoxState ShouldUseMikkTSpace() const;`
- L314 _private prototype_ `ECheckBoxState ShouldComputeWeightedNormals() const;`
- L315 _private prototype_ `ECheckBoxState ShouldRemoveDegenerates() const;`
- L316 _private prototype_ `ECheckBoxState ShouldUseHighPrecisionTangentBasis() const;`
- L317 _private prototype_ `ECheckBoxState ShouldUseHighPrecisionSkinWeights() const;`
- L318 _private prototype_ `ECheckBoxState ShouldUseFullPrecisionUVs() const;`
- L319 _private prototype_ `ECheckBoxState ShouldUseBackwardsCompatibleF16TruncUVs() const;`
- L320 _private prototype_ `ECheckBoxState ShouldOptimizeForInstancing() const;`
- L322 _private prototype_ `void OnRecomputeNormalsChanged(ECheckBoxState NewState);`
- L323 _private prototype_ `void OnRecomputeTangentsChanged(ECheckBoxState NewState);`
- L324 _private prototype_ `void OnUseMikkTSpaceChanged(ECheckBoxState NewState);`
- L325 _private prototype_ `void OnComputeWeightedNormalsChanged(ECheckBoxState NewState);`
- L326 _private prototype_ `void OnRemoveDegeneratesChanged(ECheckBoxState NewState);`
- L327 _private prototype_ `void OnUseHighPrecisionTangentBasisChanged(ECheckBoxState NewState);`
- L328 _private prototype_ `void OnUseHighPrecisionSkinWeightsChanged(ECheckBoxState NewState);`
- L329 _private prototype_ `void OnUseFullPrecisionUVsChanged(ECheckBoxState NewState);`
- L330 _private prototype_ `void OnUseBackwardsCompatibleF16TruncUVsChanged(ECheckBoxState NewState);`
- L331 _private prototype_ `void OnOptimizeForInstancingChanged(ECheckBoxState NewState);`
- L334 _private member_ `FSkeletalMeshBuildSettings& BuildSettings;`
- L335 _private member_ `int32 LODIndex;`
- L336 _private member_ `FIsLODSettingsEnabledDelegate IsBuildSettingsEnabledDelegate;`
- L337 _private member_ `FModifyMeshLODSettingsDelegate ModifyMeshLODSettingsDelegate;`
- L347 _private member_ `TArray<FSliderStateData> SliderStateDataArray;`

#### struct `FSkeletalMeshBuildSettingsLayout::FSliderStateData`  
`struct FSliderStateData`  
_L341-346_
- desc: Use this data to keep a valid reference so the helper lambda can have persistent data Helper lambda are use with spinner to not do a transaction when spinning with mouse movement
- L343 _public member_ `float MovementValueFloat = 0.0f;`
- L344 _public member_ `int32 MovementValueInt = 0;`
- L345 _public member_ `bool bSliderActiveMode = false;`

#### class `FPersonaMeshDetails`  
`class FPersonaMeshDetails : public IDetailCustomization`  
_L351-869_
- inherits: `IDetailCustomization`
- L354 _public prototype_ `FPersonaMeshDetails(TSharedRef<class IPersonaToolkit> InPersonaToolkit);`
- L355 _public prototype_ `~FPersonaMeshDetails();`
- L358 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TWeakPtr<class IPersonaToolkit> InPersonaToolkit);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L361 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L364 _public prototype_ `void ForceLayoutRebuild();`
- L365 _public prototype_ `void RequestLayoutUpdate();`
- L369 _private prototype_ `void OnAttributePreChangePreventPostEditChange(int32 LODIndex, FName LODInfoPropertyName);` — Prevent attribute change calling post edit change
- L370 _private prototype_ `void OnAttributeChangedPreventPostEditChange(const int32 LODIndex, const FName LODInfoPropertyName, const bool bForceComponentRefresh);`
- L371 _private prototype_ `void PreventAttributePostEditChange(TSharedPtr<IPropertyHandle> AttributeHandle, const int32 LODIndex, const FName PropertyName, const bool bForceComponentRefresh);`
- L374 _private prototype_ `void CustomizeLODInfoSetingsDetails(IDetailLayoutBuilder& DetailLayout, class ULODInfoUILayout* LODInfoUILayout, TSharedRef<IPropertyHandle> LODInfoProperty, IDetailCategoryBuilder& LODCategory);` — This function customize the LODInfo temporary object
- L376 _private prototype_ `FReply AddMaterialSlot();`
- L378 _private prototype_ `FText GetMaterialArrayText() const;`
- L385 _private prototype_ `void OnGetSectionsForView( class ISectionListBuilder& OutSections, int32 LODIndex );` — Called by the material list widget when we need to get new materials for the list @param OutMaterials	Handle to a material list builder that materials should be added to
- L395 _private prototype_ `void OnSectionChanged(int32 LODIndex, int32 SectionIndex, int32 NewMaterialSlotIndex, FName NewMaterialSlotName);` — Called when a user drags a new material over a list item to replace it @param NewMaterial	The material that should replace the existing material @param PrevMaterial	The material that should be replaced @param SlotIndex		The index of the slot on the component where materials should be replaces @param bReplaceAll	If true all materials in the slot should be replaced not just ones using PrevMaterial
- L402 _private prototype_ `void OnGetMaterialsForArray(class IMaterialListBuilder& OutMaterials, int32 LODIndex);` — Called by the material list widget when we need to get new materials for the list @param OutMaterials	Handle to a material list builder that materials should be added to
- L412 _private prototype_ `void OnMaterialArrayChanged(UMaterialInterface* NewMaterial, UMaterialInterface* PrevMaterial, int32 SlotIndex, bool bReplaceAll, int32 LODIndex);` — Called when a user drags a new material over a list item to replace it @param NewMaterial	The material that should replace the existing material @param PrevMaterial	The material that should be replaced @param SlotIndex		The index of the slot on the component where materials should be replaces @param bReplaceAll	If true all materials in the slot should be replaced not just ones using PrevMaterial
- L421 _private prototype_ `TSharedRef<SWidget> OnGenerateCustomNameWidgetsForSection(int32 LodIndex, int32 SectionIndex);` — Called by the material list widget on generating each name widget @param Material		The material that is being displayed @param SlotIndex		The index of the material slot
- L429 _private prototype_ `TSharedRef<SWidget> OnGenerateCustomSectionWidgetsForSection(int32 LODIndex, int32 SectionIndex);` — Called by the material list widget on generating each thumbnail widget @param Material		The material that is being displayed @param SlotIndex		The index of the material slot
- L431 _private prototype_ `bool IsSectionEnabled(int32 LodIndex, int32 SectionIndex) const;`
- L432 _private prototype_ `EVisibility ShowEnabledSectionDetail(int32 LodIndex, int32 SectionIndex) const;`
- L433 _private prototype_ `EVisibility ShowDisabledSectionDetail(int32 LodIndex, int32 SectionIndex) const;`
- L434 _private prototype_ `void OnSectionEnabledChanged(int32 LodIndex, int32 SectionIndex, bool bEnable);`
- L436 _private prototype_ `TOptional<int8> GetSectionGenerateUpToValue(int32 LodIndex, int32 SectionIndex) const;`
- L437 _private prototype_ `void SetSectionGenerateUpToValue(int8 Value, int32 LodIndex, int32 SectionIndex);`
- L438 _private prototype_ `void SetSectionGenerateUpToValueCommitted(int8 Value, ETextCommit::Type CommitInfo, int32 LodIndex, int32 SectionIndex);`
- L439 _private prototype_ `EVisibility ShowSectionGenerateUpToSlider(int32 LodIndex, int32 SectionIndex) const;`
- L440 _private prototype_ `ECheckBoxState IsGenerateUpToSectionEnabled(int32 LodIndex, int32 SectionIndex) const;`
- L441 _private prototype_ `void OnSectionGenerateUpToChanged(ECheckBoxState NewState, int32 LodIndex, int32 SectionIndex);`
- L443 _private prototype_ `TSharedRef<SWidget> OnGenerateLodComboBoxForLodPicker();`
- L444 _private prototype_ `EVisibility LodComboBoxVisibilityForLodPicker() const;`
- L445 _private prototype_ `bool IsLodComboBoxEnabledForLodPicker() const;`
- L450 _private prototype_ `TSharedRef<SWidget> OnGenerateLodMenuForLodPicker();` — Generate the context menu to choose the LOD we will display the picker list
- L451 _private prototype_ `FText GetCurrentLodName() const;`
- L452 _private prototype_ `FText GetCurrentLodTooltip() const;`
- L453 _private prototype_ `static bool GetAutoLod(USkeletalMeshComponent* InMeshComponent);`
- L454 _private prototype_ `static int32 GetCurrentDisplayLODIndex(USkeletalMeshComponent* InMeshComponent);`
- L456 _private prototype_ `void SetCurrentLOD(int32 NewLodIndex);`
- L458 _private prototype_ `void UpdateLODCategoryVisibility() const;`
- L460 _private prototype_ `FText GetMaterialNameText(int32 MaterialIndex)const ;`
- L461 _private prototype_ `void OnMaterialNameCommitted(const FText& InValue, ETextCommit::Type CommitType, int32 MaterialIndex);`
- L463 _private prototype_ `FText GetOriginalImportMaterialNameText(int32 MaterialIndex)const;`
- L471 _private prototype_ `TSharedRef<SWidget> OnGenerateCustomNameWidgetsForMaterialArray(UMaterialInterface* Material, int32 MaterialIndex);` — Called by the material list widget on generating name side content @param Material		The material that is being displayed @param MaterialIndex	The index of the material slot
- L479 _private prototype_ `TSharedRef<SWidget> OnGenerateCustomMaterialWidgetsForMaterialArray(UMaterialInterface* Material, int32 MaterialIndex, int32 LODIndex);` — Called by the material list widget on generating each thumbnail widget @param Material		The material that is being displayed @param MaterialIndex	The index of the material slot
- L488 _private prototype_ `TSharedRef<SWidget> OnGenerateMaterialListExtraBottomWidget(UMaterialInterface* Material, int32 MaterialIndex, int32 LODIndex);` — Called by the material list widget on generating each thumbnail widget Those generated widget will be stack under the material list row @param Material		The material that is being displayed @param MaterialIndex	The index of the material slot
- L491 _private prototype_ `bool OnMaterialListDirty();` — If the material list is dirty this function will return true
- L493 _private prototype_ `bool CanDeleteMaterialSlot(int32 MaterialIndex) const;`
- L495 _private prototype_ `void OnDeleteMaterialSlot(int32 MaterialIndex);`
- L498 _private prototype_ `void OnMaterialSlotOverlayMaterialChanged(UMaterialInterface* NewOverlayMaterial, int32 MaterialIndex);` — Call when user change the material slot overlay material.
- L505 _private prototype_ `ECheckBoxState IsMaterialSelected(int32 MaterialIndex) const;` — Handler for check box display based on whether the material is highlighted @param MaterialIndex	The material index that is being selected
- L512 _private prototype_ `void OnMaterialSelectedChanged(ECheckBoxState NewState, int32 MaterialIndex);` — Handler for changing highlight status on a material @param MaterialIndex	The material index that is being selected
- L519 _private prototype_ `ECheckBoxState IsIsolateMaterialEnabled(int32 MaterialIndex) const;` — Handler for check box display based on whether the material is isolated @param MaterialIndex	The material index that is being isolate
- L526 _private prototype_ `void OnMaterialIsolatedChanged(ECheckBoxState NewState, int32 MaterialIndex);` — Handler for changing isolated status on a material @param MaterialIndex	The material index that is being isolate
- L534 _private prototype_ `ECheckBoxState IsSectionSelected(int32 SectionIndex) const;` — Handler for check box display based on whether the material is highlighted @param SectionIndex	The material section that is being tested
- L541 _private prototype_ `void OnSectionSelectedChanged(ECheckBoxState NewState, int32 SectionIndex);` — Handler for changing highlight status on a material @param SectionIndex	The material section that is being tested
- L548 _private prototype_ `ECheckBoxState IsIsolateSectionEnabled(int32 SectionIndex) const;` — Handler for check box display based on whether the material is isolated @param SectionIndex	The material section that is being tested
- L555 _private prototype_ `void OnSectionIsolatedChanged(ECheckBoxState NewState, int32 SectionIndex);` — Handler for changing isolated status on a material @param SectionIndex	The material section that is being tested
- L563 _private prototype_ `ECheckBoxState IsSectionShadowCastingEnabled(int32 LODIndex, int32 SectionIndex) const;` — Handler for check box display based on whether the material has shadow casting enabled @param LODIndex	The LODIndex we want to change @param SectionIndex	The SectionIndex we change the ShadowCasting flag
- L571 _private prototype_ `void OnSectionShadowCastingChanged(ECheckBoxState NewState, int32 LODIndex, int32 SectionIndex);` — Handler for changing shadow casting status on a section @param LODIndex	The LODIndex we want to change @param SectionIndex	The SectionIndex we change the ShadowCasting flag
- L579 _private prototype_ `ECheckBoxState IsSectionVisibleInRayTracingEnabled(int32 LODIndex, int32 SectionIndex) const;` — Handler for check box display based on whether the material has VisibleInRayTracing enabled @param LODIndex	The LODIndex we want to change @param SectionIndex	The SectionIndex we change the VisibleInRayTracing flag
- L587 _private prototype_ `void OnSectionVisibleInRayTracingChanged(ECheckBoxState NewState, int32 LODIndex, int32 SectionIndex);` — Handler for changing VisibleInRayTracing status on a section @param LODIndex	The LODIndex we want to change @param SectionIndex	The SectionIndex we change the VisibleInRayTracing flag
- L595 _private prototype_ `TSharedRef<class SWidget> OnGenerateRecomputeTangentsSetting(int32 LODIndex, int32 SectionIndex);` — Handler for selecting which vertex color to mask the blending of recomputing tangents @param LODIndex	The LODIndex we want to change @param SectionIndex	The SectionIndex we change the RecomputeTangent
- L596 _private prototype_ `FText GetCurrentRecomputeTangentsSetting(int32 LODIndex, int32 SectionIndex) const;`
- L597 _private prototype_ `void SetCurrentRecomputeTangentsSetting(int32 LODIndex, int32 SectionIndex, int32 Index);`
- L604 _private prototype_ `bool CanDeleteMaterialElement(int32 LODIndex, int32 SectionIndex) const;` — Handler for enabling delete button on materials @param SectionIndex - index of the section to check
- L607 _private prototype_ `void AddLODLevelCategories(IDetailLayoutBuilder& DetailLayout);` — Creates the UI for Current LOD panel
- L610 _private prototype_ `int32 GetMaterialIndex(int32 LODIndex, int32 SectionIndex) const;` — Get a material index from LOD index and section index
- L613 _private prototype_ `void CustomizeLODSettingsCategories(IDetailLayoutBuilder& DetailLayout);` — for LOD settings category
- L616 _private prototype_ `void OnAssetPostLODImported(UObject* InObject, int32 InLODIndex);` — Called when a LOD is imported. Refreshes the UI.
- L617 _private prototype_ `void OnAssetReimport(UObject* InObject);`
- L619 _private prototype_ `void OnImportLOD(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo, IDetailLayoutBuilder* DetailLayout);` — Called from the PersonalMeshDetails UI to import a LOD.
- L620 _private prototype_ `void UpdateLODNames();`
- L621 _private prototype_ `int32 GetLODCount() const;`
- L622 _private prototype_ `void OnLODCountChanged(int32 NewValue);`
- L623 _private prototype_ `void OnLODCountCommitted(int32 InValue, ETextCommit::Type CommitInfo);`
- L624 _private prototype_ `FText GetLODCountTooltip() const;`
- L625 _private prototype_ `FText GetLODImportedText(int32 LODIndex) const;`
- L627 _private prototype_ `FText GetMaterialSlotNameText(int32 MaterialIndex) const;`
- L629 _private prototype_ `void OnNoRefStreamingLODBiasChanged(int32 NewValue, FName QualityLevel);`
- L630 _private prototype_ `void OnNoRefStreamingLODBiasCommitted(int32 InValue, ETextCommit::Type CommitInfo, FName QualityLevel);`
- L631 _private prototype_ `int32 GetNoRefStreamingLODBias(FName QualityLevel) const;`
- L632 _private prototype_ `TSharedRef<SWidget> GetNoRefStreamingLODBiasWidget(FName QualityLevelName) const;`
- L633 _private prototype_ `bool AddNoRefStreamingLODBiasOverride(FName QualityLevelName);`
- L634 _private prototype_ `bool RemoveNoRefStreamingLODBiasOverride(FName QualityLevelName);`
- L635 _private prototype_ `TArray<FName> GetNoRefStreamingLODBiasOverrideNames() const;`
- L636 _private prototype_ `FText GetNoRefStreamingLODBiasTooltip() const;`
- L638 _private prototype_ `void OnMinQualityLevelLodChanged(int32 NewValue, FName QualityLevel);`
- L639 _private prototype_ `void OnMinQualityLevelLodCommitted(int32 InValue, ETextCommit::Type CommitInfo, FName QualityLevel);`
- L640 _private prototype_ `int32 GetMinQualityLevelLod(FName QualityLevel) const;`
- L641 _private prototype_ `TSharedRef<SWidget> GetMinQualityLevelLodWidget(FName QualityLevelName) const;`
- L642 _private prototype_ `bool AddMinLodQualityLevelOverride(FName QualityLevelName);`
- L643 _private prototype_ `bool RemoveMinLodQualityLevelOverride(FName QualityLevelName);`
- L644 _private prototype_ `TArray<FName> GetMinQualityLevelLodOverrideNames() const;`
- L645 _private prototype_ `FReply ResetToDefault();`
- L646 _private prototype_ `FPerPlatformInt GetMinLod();`
- L649 _private prototype_ `FReply OnApplyChanges();` — apply LOD changes if the user modified LOD reduction settings
- L651 _private prototype_ `void RegenerateOneLOD(int32 LODIndex);` — regenerate one specific LOD Index no dependencies
- L653 _private prototype_ `void RegenerateDependentLODs(int32 LODIndex);` — regenerate the specific all LODs dependent of InLODIndex. This is not regenerating the InLODIndex
- L655 _private prototype_ `FReply ApplyLODChanges(int32 LODIndex);` — Apply specified LOD Index
- L657 _private prototype_ `FReply RegenerateLOD(int32 LODIndex);` — Apply specified LOD Index
- L659 _private prototype_ `FReply RemoveOneLOD(int32 LODIndex);` — Removes the specified lod from the skeletal mesh
- L661 _private prototype_ `FReply RemoveGeometryFromLOD(int32 LODIndex);` — Removes any editable geometry from the given LOD, making it auto-generated
- L663 _private prototype_ `void RestoreNonReducedLOD(int32 LODIndex);` — Restore the LOD imported data if the LOD is no longer reduced
- L665 _private prototype_ `void HideUnnecessaryProperties(IDetailLayoutBuilder& DetailLayout);` — hide properties which don't need to be showed to end users
- L668 _private prototype_ `void OnPostProcessBlueprintChanged(IDetailLayoutBuilder* DetailBuilder);` — Handling functions for post process blueprint selection combo box
- L669 _private prototype_ `FString GetCurrentPostProcessBlueprintPath() const;`
- L670 _private prototype_ `bool OnShouldFilterPostProcessBlueprint(const FAssetData& AssetData) const;`
- L671 _private prototype_ `void OnSetPostProcessBlueprint(const FAssetData& AssetData, TSharedRef<IPropertyHandle> BlueprintProperty);`
- L674 _private function_ `TSharedRef<IPersonaToolkit> GetPersonaToolkit() const` — Access the persona toolkit ptr. It should always be valid in the lifetime of this customization
- L675 _private function_ `bool HasValidPersonaToolkit() const`
- L677 _private prototype_ `EVisibility GetOverrideUVDensityVisibililty() const;`
- L678 _private prototype_ `ECheckBoxState IsUVDensityOverridden(int32 MaterialIndex) const;`
- L679 _private prototype_ `void OnOverrideUVDensityChanged(ECheckBoxState NewState, int32 MaterialIndex);`
- L681 _private prototype_ `EVisibility GetUVDensityVisibility(int32 MaterialIndex, int32 UVChannelIndex) const;`
- L682 _private prototype_ `TOptional<float> GetUVDensityValue(int32 MaterialIndex, int32 UVChannelIndex) const;`
- L683 _private prototype_ `void SetUVDensityValue(float InDensity, ETextCommit::Type CommitType, int32 MaterialIndex, int32 UVChannelIndex);`
- L685 _private prototype_ `SVerticalBox::FSlot& GetUVDensitySlot(int32 MaterialIndex, int32 UVChannelIndex) const;`
- L695 _private prototype_ `FReply OnReimportLodClicked(EReimportButtonType InReimportType, int32 InLODIndex);` — Handler for reimport buttons in LOD details
- L697 _private prototype_ `void OnCopySectionList(int32 LODIndex);`
- L698 _private prototype_ `bool OnCanCopySectionList(int32 LODIndex) const;`
- L699 _private prototype_ `void OnPasteSectionList(int32 LODIndex);`
- L701 _private prototype_ `void OnCopySectionItem(int32 LODIndex, int32 SectionIndex);`
- L702 _private prototype_ `bool OnCanCopySectionItem(int32 LODIndex, int32 SectionIndex) const;`
- L703 _private prototype_ `void OnPasteSectionItem(int32 LODIndex, int32 SectionIndex);`
- L705 _private prototype_ `void OnCopyMaterialList();`
- L706 _private prototype_ `bool OnCanCopyMaterialList() const;`
- L707 _private prototype_ `void OnPasteMaterialList();`
- L709 _private prototype_ `void OnCopyMaterialItem(int32 CurrentSlot);`
- L710 _private prototype_ `bool OnCanCopyMaterialItem(int32 CurrentSlot) const;`
- L711 _private prototype_ `void OnPasteMaterialItem(int32 CurrentSlot);`
- L713 _private prototype_ `void OnPreviewMeshChanged(USkeletalMesh* OldSkeletalMesh, USkeletalMesh* NewMesh);`
- L715 _private prototype_ `bool FilterOutBakePose(const struct FAssetData& AssetData, USkeleton* Skeleton) const;`
- L716 _private function_ `bool FilterOutBakePose(const struct FAssetData& AssetData, TObjectPtr<USkeleton> Skeleton) const`
- L718 _private prototype_ `FText GetLODCustomModeNameContent(int32 LODIndex) const;`
- L719 _private prototype_ `ECheckBoxState IsLODCustomModeCheck(int32 LODIndex) const;`
- L720 _private prototype_ `void SetLODCustomModeCheck(ECheckBoxState NewState, int32 LODIndex);`
- L721 _private prototype_ `bool IsLODCustomModeEnable(int32 LODIndex) const;`
- L724 _private prototype_ `TOptional<int32> GetLodSliderMaxValue() const;` — Gets the max LOD that can be set from the lod count slider (current num plus an interval)
- L726 _private prototype_ `void CustomizeSkinWeightProfiles(IDetailLayoutBuilder& DetailLayout);`
- L727 _private prototype_ `TSharedRef<SWidget> CreateSkinWeightProfileMenuContent();`
- L730 _public prototype_ `bool IsApplyNeeded() const;`
- L731 _public prototype_ `bool IsGenerateAvailable() const;`
- L732 _public prototype_ `void ApplyChanges();`
- L733 _public prototype_ `FText GetApplyButtonText() const;`
- L737 _private member_ `TWeakObjectPtr<USkeletalMesh> SkeletalMeshPtr;` — Container for the objects to display
- L740 _private member_ `TWeakPtr<class IPersonaToolkit> PersonaToolkitPtr;` — Reference the persona toolkit
- L743 _private member_ `TSharedPtr<FNaniteSkeletalMeshLayout> NaniteSettings;` — Nanite settings for the details panel.
- L745 _private member_ `IDetailLayoutBuilder* MeshDetailLayout;`
- L748 _private member_ `TArray<class ULODInfoUILayout*> LODInfoUILayouts;` — This is the mockup UObjects to modify a copy of the LODInfo
- L749 _private member_ `TArray<TSharedRef<IDetailsView>> LODInfoUILayoutDetailsViews;`
- L752 _private member_ `TArray<TSharedPtr<FString> > LODNames;` — LOD import options
- L754 _private member_ `int32 LODCount;` — Helper value that corresponds to the 'Number of LODs' spinbox.
- L757 _private member_ `TMap<int32, TArray<FSectionLocalizer>> MaterialUsedMap;` — This is to know if material are used by any LODs sections.
- L759 _private member_ `TArray<class IDetailCategoryBuilder*> LodCategories;`
- L760 _private member_ `IDetailCategoryBuilder* LodCustomCategory;`
- L762 _private member_ `bool CustomLODEditMode;`
- L763 _private member_ `TArray<bool> DetailDisplayLODs;`
- L769 _private member_ `TMap<int64, int8> OldGenerateUpToSliderValues;` — Helper to keep the old GenerateUpTo slider value to register transaction correctly. The key is the union of LOD index and section index.
- L774 _private member_ `bool bDeleteWarningConsumed;` — This prevent showing the delete material slot warning dialog more then once per editor session
- L777 _private member_ `TArray<TUniquePtr<FScopedSkeletalMeshPostEditChange>> ChangeScopes;`
- L780 _private member_ `TArray<FClothingComboInfo> ClothingComboLODInfos;` — info about clothing combo boxes for multiple LOD
- L781 _private member_ `TArray<int32> ClothingSelectedSubmeshIndices;`
- L797 _private typedef_ `typedef SComboBox<TSharedPtr<FClothingEntry>> SClothComboBox;` — Cloth combo box tracking for refreshes post-import/creation
- L798 _private typedef_ `typedef TSharedPtr<SClothComboBox> SClothComboBoxPtr;`
- L799 _private member_ `TArray<SClothComboBoxPtr> ClothComboBoxes;`
- L802 _private member_ `TArray<TSharedPtr<FClothingEntry>> NewClothingAssetEntries;` — Clothing entries available to bind to the mesh
- L805 _private member_ `TSharedPtr<FClothingEntry> ClothingNoneEntry;` — Cached item in above array that is used as the "None" entry in the list
- L808 _private prototype_ `void UpdateClothingEntries();` — Update the list of valid entries
- L811 _private prototype_ `void RefreshClothingComboBoxes();` — Refreshes clothing combo boxes that are currently active
- L814 _private prototype_ `void OnClothingComboBoxOpening();` — Called as clothing combo boxes open to validate option entries
- L817 _private prototype_ `TSharedRef<SWidget> OnGenerateWidgetForClothingEntry(TSharedPtr<FClothingEntry> InEntry);` — Generate a widget for the clothing details panel
- L820 _private prototype_ `FText OnGetClothingComboText(int32 InLodIdx, int32 InSectionIdx) const;` — Get the current text for the clothing selection combo box for the specified LOD and section
- L823 _private prototype_ `void OnClothingSelectionChanged(TSharedPtr<FClothingEntry> InNewEntry, ESelectInfo::Type InSelectType, int32 BoxIndex, int32 InLodIdx, int32 InSectionIdx);` — Callback when the clothing asset is changed
- L826 _private prototype_ `bool IsClothingPanelEnabled() const;` — If the clothing details widget is editable
- L829 _private prototype_ `void CustomizeClothingProperties(class IDetailLayoutBuilder& DetailLayout, class IDetailCategoryBuilder& ClothingFilesCategory);` — Generate slate UI for Clothing category
- L832 _private prototype_ `void OnGenerateElementForClothingAsset( TSharedRef<IPropertyHandle> ElementProperty, int32 ElementIndex, IDetailChildrenBuilder& ChildrenBuilder, IDetailLayoutBuilder* DetailLayout );` — Generate each ClothingAsset array entry
- L835 _private prototype_ `TSharedRef<SUniformGridPanel> MakeClothingDetailsWidget(int32 AssetIndex) const;` — Make uniform grid widget for Apex details
- L838 _private prototype_ `FReply OnRemoveClothingAssetClicked(int32 AssetIndex, IDetailLayoutBuilder* DetailLayout);` — Removes a clothing asset
- L841 _private prototype_ `FReply OnSaveLODSettings();` — Create LOD setting assets from current setting
- L844 _private prototype_ `void OnLODSettingsSelected(const FAssetData& AssetData);` — LOD Settings Selected
- L847 _private prototype_ `bool IsLODInfoEditingEnabled(int32 LODIndex) const;` — LOD Info editing is enabled? LODIndex == -1, then it just verifies if the asset exists
- L848 _private prototype_ `bool IsMinLodEnable() const;`
- L849 _private prototype_ `bool IsQualityLevelMinLodEnable() const;`
- L850 _private prototype_ `void ModifyMeshLODSettings(int32 LODIndex);`
- L852 _private member_ `TMap<int32, TSharedPtr<FSkeletalMeshBuildSettingsLayout>> BuildSettingsWidgetsPerLOD;`
- L853 _private member_ `TMap<int32, TSharedPtr<FSkeletalMeshReductionSettingsLayout>> ReductionSettingsWidgetsPerLOD;`
- L856 _private member_ `TSharedPtr<IPropertyHandle> VertexColorImportOptionHandle;` — Property handle used to determine if the VertexColorImportOverride property should be enabled.
- L859 _private member_ `TSharedPtr<IPropertyHandle> VertexColorImportOverrideHandle;` — Property handle used during UI construction
- L862 _private prototype_ `void OnInstancedFbxSkeletalMeshImportDataPropertyIteration(IDetailCategoryBuilder& BaseCategory, IDetailGroup* PropertyGroup, TSharedRef<IPropertyHandle>& Property) const;` — Delegate implementation of FOnInstancedPropertyIteration used during DataImport UI construction
- L865 _private prototype_ `bool GetVertexOverrideColorEnabledState() const;` — Delegate used at runtime to determine the state of the VertexOverrideColor property
- L868 _private prototype_ `void OnMeshRebuildCompleted(USkeletalMesh* InMesh);` — Called when the skeletal mesh has finished rebuilding. This may affect some settings, such as vertex attributes.

#### enum `FPersonaMeshDetails::EReimportButtonType`  
`enum class EReimportButtonType : uint8`  
_L688-692_
- desc: Used to control the type of reimport to do with a named parameter
- L690 _public enumerator_ `Reimport`
- L691 _public enumerator_ `ReimportWithNewFile`

#### struct `FPersonaMeshDetails::FClothingEntry`  
`struct FClothingEntry`  
_L784-794_
- desc: Menu entry for clothing dropdown
- L787 _public member_ `int32 AssetIndex;` — Asset index inside the mesh
- L790 _public member_ `int32 AssetLodIndex;` — LOD index inside the clothing asset
- L793 _public member_ `TWeakObjectPtr<UClothingAssetBase> Asset;` — Pointer back to the asset for this clothing entry

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalMeshPersonaMeshDetail, Log, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalMeshPersonaMeshDetail, Log, All);`
- L34 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsLODSettingsEnabledDelegate, int32) DECLARE_DELEGATE_OneParam(FModifyMeshLODSettingsDelegate, int32) struct FClothAssetSubmeshIndex { FClothAssetSubmeshIndex(int32 InAssetIndex, int32 InSubmeshIndex) : AssetIndex(InAssetIndex) , SubmeshIndex(InSubmeshIndex) {} int32 AssetIndex; int32 SubmeshIndex; bool operator==(const FClothAssetSubmeshIndex& Other) const { return (AssetIndex == Other.AssetIndex && SubmeshIndex == Other.SubmeshIndex ); } };` — The parameter is the LOD index so we know which LOD need to be rebuild
- L35 _delegate_ `DECLARE_DELEGATE_OneParam(FModifyMeshLODSettingsDelegate, int32) struct FClothAssetSubmeshIndex { FClothAssetSubmeshIndex(int32 InAssetIndex, int32 InSubmeshIndex) : AssetIndex(InAssetIndex) , SubmeshIndex(InSubmeshIndex) {} int32 AssetIndex; int32 SubmeshIndex; bool operator==(const FClothAssetSubmeshIndex& Other) const { return (AssetIndex == Other.AssetIndex && SubmeshIndex == Other.SubmeshIndex ); } };`
- L106 _delegate_ `DECLARE_DELEGATE_RetVal(float, FGetFloatDelegate);`
- L107 _delegate_ `DECLARE_DELEGATE_OneParam(FSetFloatDelegate, float);`
- L109 _delegate_ `DECLARE_DELEGATE_RetVal(int32, FGetIntegerDelegate);`
- L110 _delegate_ `DECLARE_DELEGATE_OneParam(FSetIntegerDelegate, int32);`
- L112 _delegate_ `DECLARE_DELEGATE_RetVal(uint32, FGetUnsignedIntegerDelegate);`
- L113 _delegate_ `DECLARE_DELEGATE_OneParam(FSetUnsignedIntegerDelegate, uint32);`
- L115 _delegate_ `DECLARE_DELEGATE_RetVal(ECheckBoxState, FGetCheckBoxStateDelegate);`
- L116 _delegate_ `DECLARE_DELEGATE_OneParam(FSetCheckBoxStateDelegate, ECheckBoxState);`
- L260 _delegate_ `DECLARE_DELEGATE_RetVal(float, FGetFloatDelegate);`
- L261 _delegate_ `DECLARE_DELEGATE_OneParam(FSetFloatDelegate, float);`
- L263 _delegate_ `DECLARE_DELEGATE_RetVal(int32, FGetIntegerDelegate);`
- L264 _delegate_ `DECLARE_DELEGATE_OneParam(FSetIntegerDelegate, int32);`

### `Source/Editor/Persona/Private/PersonaPreviewSceneAnimationController.h` (Private)


#### class `UPersonaPreviewSceneAnimationController`  
`class UPersonaPreviewSceneAnimationController : public UPersonaPreviewSceneController`  
_L13-28_
- reflection: `UCLASS(DisplayName="Use Specific Animation")`
- inherits: `UPersonaPreviewSceneController`
- L20 _public member_ `TSoftObjectPtr<UAnimationAsset> Animation;` — `UPROPERTY(EditAnywhere, Category = "Animation", meta = (DisplayThumbnail = true))` — The preview animation to use
- L22 _public prototype_ `virtual void InitializeView(UPersonaPreviewSceneDescription* SceneDescription, IPersonaPreviewScene* PreviewScene) const;`
- L23 _public prototype_ `virtual void UninitializeView(UPersonaPreviewSceneDescription* SceneDescription, IPersonaPreviewScene* PreviewScene) const;`
- L25 _public prototype_ `virtual IDetailPropertyRow* AddPreviewControllerPropertyToDetails(const TSharedRef<IPersonaToolkit>& PersonaToolkit, IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category, const FProperty* Property, const EPropertyLocation::Type PropertyLocation);`
- L27 _public prototype_ `bool HandleShouldFilterAsset(const FAssetData& InAssetData, const USkeleton* InSkeleton) const;`

### `Source/Editor/Persona/Private/PersonaPreviewSceneDefaultController.h` (Private)


#### class `UPersonaPreviewSceneDefaultController`  
`class UPersonaPreviewSceneDefaultController : public UPersonaPreviewSceneController`  
_L9-16_
- reflection: `UCLASS(DisplayName = "Default")`
- inherits: `UPersonaPreviewSceneController`
- L14 _public prototype_ `virtual void InitializeView(UPersonaPreviewSceneDescription* SceneDescription, IPersonaPreviewScene* PreviewScene) const;`
- L15 _public prototype_ `virtual void UninitializeView(UPersonaPreviewSceneDescription* SceneDescription, IPersonaPreviewScene* PreviewScene) const;`

### `Source/Editor/Persona/Private/PersonaPreviewSceneDescription.h` (Private)


#### class `UPersonaPreviewSceneDescription`  
`class UPersonaPreviewSceneDescription : public UObject`  
_L23-95_
- reflection: `UCLASS()`
- inherits: `UObject`
- L30 _public member_ `class TSubclassOf<UPersonaPreviewSceneController> PreviewController;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, NoClear, Category = "Animation")` — The method by which the preview is animated
- L33 _public member_ `TObjectPtr<UPersonaPreviewSceneController> PreviewControllerInstance;` — `UPROPERTY()`
- L36 _public member_ `TArray<TObjectPtr<UPersonaPreviewSceneController>> PreviewControllerInstances;` — `UPROPERTY()`
- L40 _public member_ `TSoftObjectPtr<USkeletalMesh> PreviewMesh;` — `UPROPERTY(EditAnywhere, Category = "Mesh", meta=(DisplayThumbnail=true))` — The preview mesh to use
- L44 _public member_ `TSoftObjectPtr<UAnimBlueprint> PreviewAnimationBlueprint;` — `UPROPERTY(EditAnywhere, Category = "Animation Blueprint", meta=(DisplayThumbnail=true))` — The preview anim blueprint to use
- L48 _public member_ `EPreviewAnimationBlueprintApplicationMethod ApplicationMethod;` — `UPROPERTY(EditAnywhere, Category = "Animation Blueprint")` — The method by which a preview animation blueprint is applied, either as an overlay layer, or as a linked instance
- L52 _public member_ `FName LinkedAnimGraphTag;` — `UPROPERTY(EditAnywhere, Category = "Animation Blueprint")` — The tag to use when applying a preview animation blueprint via LinkAnimGraphByTag
- L55 _public member_ `TSoftObjectPtr<UDataAsset> AdditionalMeshes;` — `UPROPERTY(EditAnywhere, Category = "Additional Meshes")`
- L58 _public member_ `TObjectPtr<UPreviewMeshCollection> DefaultAdditionalMeshes;` — `UPROPERTY()`
- L61 _public function_ `bool SetPreviewController(UClass* PreviewControllerClass, class IPersonaPreviewScene* PreviewScene)` — Sets the current preview controller for the scene (handles uninitializing and initializing controllers)
- L81 _private function_ `UPersonaPreviewSceneController* GetControllerForClass(UClass* PreviewControllerClass)` — Gets created controller for the requested class (or creates one if none exists)

### `Source/Editor/Persona/Private/PersonaPreviewSceneRefPoseController.h` (Private)


#### class `UPersonaPreviewSceneRefPoseController`  
`class UPersonaPreviewSceneRefPoseController : public UPersonaPreviewSceneController`  
_L9-24_
- reflection: `UCLASS(DisplayName = "Reference Pose")`
- inherits: `UPersonaPreviewSceneController`
- L14 _public function_ `UPersonaPreviewSceneRefPoseController() : bResetBoneTransforms(false)`
- L20 _public member_ `bool bResetBoneTransforms;` — `UPROPERTY()` — Whether to reset bone transforms when the refpose is set
- L22 _public prototype_ `virtual void InitializeView(UPersonaPreviewSceneDescription* SceneDescription, IPersonaPreviewScene* PreviewScene) const;`
- L23 _public prototype_ `virtual void UninitializeView(UPersonaPreviewSceneDescription* SceneDescription, IPersonaPreviewScene* PreviewScene) const;`

### `Source/Editor/Persona/Private/PersonaPreviewSceneSkelMeshInstanceController.h` (Private)


#### struct `FSkeletalMeshDebugInstance`  
`struct FSkeletalMeshDebugInstance`  
_L9-20_
- L11 _public prototype_ `FSkeletalMeshDebugInstance() = default;`
- L12 _public prototype_ `AActor* GetActor() const;`
- L15 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent = nullptr;`
- L17 _public member_ `bool bIsSelected = false;` — true if the actor is selected in the level editor (used to color UI to help user find intended instance)
- L19 _public member_ `FText DisplayName;` — the display name

#### class `SSkeletalMeshDebugSelectionWidget`  
`class SSkeletalMeshDebugSelectionWidget : public SCompoundWidget`  
_L22-51_
- inherits: `SCompoundWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS(SSkeletalMeshDebugSelectionWidget)`
- L26 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<IPersonaPreviewScene>, PreviewScene) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _private prototype_ `void Refresh();` — gathers all skel mesh instances in all UWorlds and refresh the UI options
- L37 _private prototype_ `TSharedRef<SWidget> OnGenerateComboBoxItemWidget(TSharedPtr<FSkeletalMeshDebugInstance> Item);` — UI
- L38 _private prototype_ `IDetailPropertyRow* GenerateInstancesCombobox(IDetailCategoryBuilder& Category);`
- L39 _private prototype_ `void OnSelectionChanged(TSharedPtr<FSkeletalMeshDebugInstance> Item, ESelectInfo::Type SelectInfo);`
- L42 _private member_ `TSharedPtr<IPersonaPreviewScene> PreviewScenePtr;` — store the preview scene for callbacks to use
- L44 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FSkeletalMeshDebugInstance>>> InstanceComboBox;` — the combobox that contains the instance names
- L46 _private member_ `TArray<TSharedPtr<FSkeletalMeshDebugInstance>> AllMeshInstances;` — all the instances of skeletal mesh components using the target skeletal mesh
- L48 _private member_ `TSharedPtr<FSkeletalMeshDebugInstance> ActiveInstance;` — the currently active component to copy the pose from
- L50 _private member_ `FText NameOfLastSelectedInstance;` — the display name of the last instance selected by the user, used to restore their selection between PIE sessions

#### class `UPersonaPreviewSceneSkelMeshInstanceController`  
`class UPersonaPreviewSceneSkelMeshInstanceController : public UPersonaPreviewSceneController`  
_L54-75_
- reflection: `UCLASS(DisplayName = "Running Instance")`
- inherits: `UPersonaPreviewSceneController`
- L59 _public function_ `UPersonaPreviewSceneSkelMeshInstanceController() : ActivePreviewInstance(nullptr)`
- L63 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> ActivePreviewInstance;` — `UPROPERTY(EditAnywhere, Category = "Animation")` — The instance to preview.
- L66 _public prototype_ `virtual void InitializeView(UPersonaPreviewSceneDescription* SceneDescription, IPersonaPreviewScene* PreviewScene) const override;` — BEGIN UPersonaPreviewSceneController interface
- L67 _public prototype_ `virtual void UninitializeView(UPersonaPreviewSceneDescription* SceneDescription, IPersonaPreviewScene* PreviewScene) const override;`
- L68 _public prototype_ `virtual IDetailPropertyRow* AddPreviewControllerPropertyToDetails( const TSharedRef<IPersonaToolkit>& PersonaToolkit, IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category, const FProperty* Property, const EPropertyLocation::Type PropertyLocation) override;`

### `Source/Editor/Persona/Private/PersonaToolkit.h` (Private)


#### class `FPersonaToolkit`  
`class FPersonaToolkit : public IPersonaToolkit, public TSharedFromThis<FPersonaToolkit>`  
_L18-97_
- inherits: `IPersonaToolkit,TSharedFromThis<FPersonaToolkit>`
- L21 _public prototype_ `FPersonaToolkit();`
- L22 _public prototype_ `virtual ~FPersonaToolkit();`
- L25 _public prototype_ `void Initialize(UObject* InAsset, const FPersonaToolkitArgs& PersonaToolkitArgs, USkeleton* InSkeleton = nullptr);` — Initialize from various sources
- L26 _public prototype_ `void Initialize(USkeleton* InSkeleton, const FPersonaToolkitArgs& PersonaToolkitArgs);`
- L27 _public prototype_ `void Initialize(UAnimationAsset* InAnimationAsset, const FPersonaToolkitArgs& PersonaToolkitArgs);`
- L28 _public prototype_ `void Initialize(USkeletalMesh* InSkeletalMesh, const FPersonaToolkitArgs& PersonaToolkitArgs);`
- L29 _public prototype_ `void Initialize(UAnimBlueprint* InAnimBlueprint, const FPersonaToolkitArgs& PersonaToolkitArgs);`
- L30 _public prototype_ `void Initialize(UPhysicsAsset* InPhysicsAsset, const FPersonaToolkitArgs& PersonaToolkitArgs);`
- L33 _public prototype_ `void CreatePreviewScene(const FPersonaToolkitArgs& PersonaToolkitArgs);` — Optionally create a preview scene - note: creates an editable skeleton
- L36 _public prototype_ `void SetPreviewSceneDetailsOptions(const FPersonaPreviewSceneDetailsOptions& Options);` — Store the options for the Preview Scene Settings details panel layout.
- L39 _public prototype_ `virtual class USkeleton* GetSkeleton() const override;` — IPersonaToolkit interface
- L40 _public prototype_ `virtual TSharedPtr<class IEditableSkeleton> GetEditableSkeleton() const override;`
- L41 _public prototype_ `virtual class UDebugSkelMeshComponent* GetPreviewMeshComponent() const override;`
- L42 _public prototype_ `virtual class USkeletalMesh* GetMesh() const override;`
- L43 _public prototype_ `virtual void SetMesh(class USkeletalMesh* InSkeletalMesh) override;`
- L44 _public prototype_ `virtual class UAnimBlueprint* GetAnimBlueprint() const override;`
- L45 _public prototype_ `virtual class UAnimationAsset* GetAnimationAsset() const override;`
- L46 _public prototype_ `virtual void SetAnimationAsset(class UAnimationAsset* InAnimationAsset) override;`
- L47 _public prototype_ `virtual class TSharedRef<IPersonaPreviewScene> GetPreviewScene() const override;`
- L48 _public prototype_ `virtual class USkeletalMesh* GetPreviewMesh() const override;`
- L49 _public prototype_ `virtual void SetPreviewMesh(class USkeletalMesh* InSkeletalMesh, bool bSetPreviewMeshInAsset = true) override;`
- L50 _public prototype_ `virtual void SetPreviewAnimationBlueprint(UAnimBlueprint* InAnimBlueprint) override;`
- L51 _public prototype_ `virtual UAnimBlueprint* GetPreviewAnimationBlueprint() const override;`
- L52 _public prototype_ `virtual int32 GetCustomData(const int32 Key) const override;`
- L53 _public prototype_ `virtual void SetCustomData(const int32 Key, const int32 CustomData) override;`
- L54 _public prototype_ `virtual void CustomizeSceneSettings(IDetailLayoutBuilder& DetailBuilder) override;`
- L55 _public prototype_ `virtual FName GetContext() const override;`
- L56 _public prototype_ `virtual bool CanPreviewMeshUseDifferentSkeleton() const override;`
- L60 _private prototype_ `void CommonInitialSetup(const FPersonaToolkitArgs& PersonaToolkitArgs);` — Common initialization
- L63 _private member_ `TWeakObjectPtr<USkeleton> Skeleton;` — The skeleton we are editing
- L66 _private member_ `TSharedPtr<IEditableSkeleton> EditableSkeleton;` — Editable skeleton
- L69 _private member_ `TWeakObjectPtr <USkeletalMesh> Mesh;` — The mesh we are editing
- L72 _private member_ `TWeakObjectPtr<UAnimBlueprint> AnimBlueprint;` — The anim blueprint we are editing
- L75 _private member_ `TWeakObjectPtr<UAnimationAsset> AnimationAsset;` — the animation asset we are editing
- L78 _private member_ `TWeakObjectPtr<UPhysicsAsset> PhysicsAsset;` — the physics asset we are editing
- L81 _private member_ `TWeakObjectPtr<UObject> Asset;` — The generic asset we are editing
- L84 _private member_ `TMap<int32, int32> CustomEditorData;` — Allow custom data for this editor
- L87 _private member_ `TSharedPtr<FAnimationEditorPreviewScene> PreviewScene;` — Preview scene for the editor
- L90 _private member_ `FOnPreviewSceneSettingsCustomized::FDelegate OnPreviewSceneSettingsCustomized;` — Callback to customize details tab of Preview Scene Settings
- L93 _private member_ `UClass* InitialAssetClass;` — The class of the initial asset we were created with
- L96 _private member_ `bool bPreviewMeshCanUseDifferentSkeleton = false;` — A flag to indicate whether the preview mesh's skeleton can be incompatible with the editing skeleton

### `Source/Editor/Persona/Private/PoseEditorCommands.h` (Private)


#### class `FPoseEditorCommands`  
`class FPoseEditorCommands : public TCommands<FPoseEditorCommands>`  
_L18-42_
- inherits: `TCommands<FPoseEditorCommands>`
- desc: Class containing commands for pose editor
- L21 _public function_ `FPoseEditorCommands() : TCommands<FPoseEditorCommands> ( TEXT("PoseEditor"),`
- L32 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L35 _public member_ `TSharedPtr< FUICommandInfo > PasteAllNames;` — Paste all names
- L38 _public member_ `TSharedPtr< FUICommandInfo > UpdatePoseToCurrent;` — Update selected pose to match viewport
- L40 _public member_ `TSharedPtr< FUICommandInfo > AddPoseFromCurrent;`
- L41 _public member_ `TSharedPtr< FUICommandInfo > AddPoseFromReference;`

### `Source/Editor/Persona/Private/PoseWatchManagerColumnColor.h` (Private)


#### class `FPoseWatchManagerColumnColor`  
`class FPoseWatchManagerColumnColor : public IPoseWatchManagerColumn`  
_L17-31_
- inherits: `IPoseWatchManagerColumn`
- desc: A PoseWatchManager column which handles setting and visualizing a pose watch's color
- L20 _public function_ `FPoseWatchManagerColumnColor()`
- L21 _public prototype_ `virtual ~FPoseWatchManagerColumnColor() = default;`
- L23 _public function_ `static FName GetID()`
- L26 _public function_ `virtual FName GetColumnID() override`
- L27 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L28 _public prototype_ `virtual const TSharedRef<SWidget> ConstructRowWidget(FPoseWatchManagerTreeItemRef TreeItem, const STableRow<FPoseWatchManagerTreeItemPtr>& Row) override;`
- L29 _public function_ `virtual bool SupportsSorting() const override`

### `Source/Editor/Persona/Private/PoseWatchManagerColumnLabel.h` (Private)


#### class `FPoseWatchManagerItemLabelColumn`  
`class FPoseWatchManagerItemLabelColumn : public IPoseWatchManagerColumn`  
_L16-35_
- inherits: `IPoseWatchManagerColumn`
- desc: A column for the PoseWatchManager that displays the item label
- L20 _public function_ `FPoseWatchManagerItemLabelColumn(IPoseWatchManager& PoseWatchManager) : WeakPoseWatchManager(StaticCastSharedRef<IPoseWatchManager>(PoseWatchManager.AsShared()))`
- L24 _public function_ `static FName GetID()`
- L27 _public function_ `virtual FName GetColumnID() override`
- L28 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L29 _public prototype_ `virtual const TSharedRef< SWidget > ConstructRowWidget(FPoseWatchManagerTreeItemRef TreeItem, const STableRow<FPoseWatchManagerTreeItemPtr>& Row) override;`
- L30 _public prototype_ `virtual void PopulateSearchStrings(const IPoseWatchManagerTreeItem& Item, TArray< FString >& OutSearchStrings) const override;`
- L34 _private member_ `TWeakPtr<IPoseWatchManager> WeakPoseWatchManager;`

### `Source/Editor/Persona/Private/PoseWatchManagerColumnVisibility.h` (Private)


#### class `FPoseWatchManagerColumnVisibility`  
`class FPoseWatchManagerColumnVisibility : public IPoseWatchManagerColumn`  
_L17-33_
- inherits: `IPoseWatchManagerColumn`
- desc: A PoseWatchManager column which handles setting and visualizing a pose watch's visibility
- L20 _public function_ `FPoseWatchManagerColumnVisibility(IPoseWatchManager& PoseWatchManager) : WeakPoseWatchManager(StaticCastSharedRef<IPoseWatchManager>(PoseWatchManager.AsShared()))`
- L25 _public function_ `static FName GetID()`
- L26 _public function_ `virtual FName GetColumnID() override`
- L27 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L28 _public prototype_ `virtual const TSharedRef< SWidget > ConstructRowWidget(FPoseWatchManagerTreeItemRef TreeItem, const STableRow<FPoseWatchManagerTreeItemPtr>& Row) override;`
- L32 _private member_ `TWeakPtr<IPoseWatchManager> WeakPoseWatchManager;`

### `Source/Editor/Persona/Private/PoseWatchManagerDefaultHierarchy.h` (Private)


#### class `FPoseWatchManagerDefaultHierarchy`  
`class FPoseWatchManagerDefaultHierarchy`  
_L11-21_
- L14 _public prototype_ `FPoseWatchManagerDefaultHierarchy(FPoseWatchManagerDefaultMode* InMode);`
- L16 _public prototype_ `FPoseWatchManagerTreeItemPtr FindParent(const IPoseWatchManagerTreeItem& Item, const TMap<FObjectKey, FPoseWatchManagerTreeItemPtr>& Items) const;`
- L18 _public prototype_ `void CreateItems(TArray<FPoseWatchManagerTreeItemPtr>& OutItems) const;`
- L20 _public member_ `FPoseWatchManagerDefaultMode* Mode;`

### `Source/Editor/Persona/Private/PoseWatchManagerDefaultMode.h` (Private)


#### class `FPoseWatchManagerDefaultMode`  
`class FPoseWatchManagerDefaultMode`  
_L11-34_
- L14 _public prototype_ `FPoseWatchManagerDefaultMode(SPoseWatchManager* InPoseWatchManager);`
- L16 _public prototype_ `void Rebuild();`
- L18 _public prototype_ `bool ParseDragDrop(FPoseWatchManagerDragDropPayload& OutPayload, const FDragDropOperation& Operation) const;`
- L20 _public prototype_ `FPoseWatchManagerDragValidationInfo ValidateDrop(const IPoseWatchManagerTreeItem& DropTarget, const FPoseWatchManagerDragDropPayload& Payload) const;`
- L22 _public prototype_ `void OnDrop(IPoseWatchManagerTreeItem& DropTarget, const FPoseWatchManagerDragDropPayload& Payload, const FPoseWatchManagerDragValidationInfo& ValidationInfo) const;`
- L24 _public prototype_ `TSharedPtr<FDragDropOperation> CreateDragDropOperation(const TArray<FPoseWatchManagerTreeItemPtr>& InTreeItems) const;`
- L26 _public prototype_ `FReply OnDragOverItem(const FDragDropEvent& Event, const IPoseWatchManagerTreeItem& Item) const;`
- L28 _public function_ `int32 GetTypeSortPriority(const IPoseWatchManagerTreeItem& Item) const`
- L31 _public member_ `SPoseWatchManager* PoseWatchManager;`
- L33 _public member_ `TUniquePtr<FPoseWatchManagerDefaultHierarchy> Hierarchy;`

### `Source/Editor/Persona/Private/PoseWatchManagerDragDrop.h` (Private)


#### enum `EPoseWatchManagerDropCompatibility`  
`enum class EPoseWatchManagerDropCompatibility : uint8`  
_L28-32_
- desc: Enum to describe the compatibility of a drag drop operation
- L30 _public enumerator_ `Compatible`
- L31 _public enumerator_ `Incompatible`

#### struct `FPoseWatchManagerDragDropPayload`  
`struct FPoseWatchManagerDragDropPayload`  
_L34-51_
- L36 _public function_ `FPoseWatchManagerDragDropPayload(const FDragDropOperation& InOperation = FDragDropOperation()) : SourceOperation(InOperation)`
- L41 _public function_ `template<typename TreeType> FPoseWatchManagerDragDropPayload(const TreeType& InDraggedItem, const FDragDropOperation& InOperation = FDragDropOperation()) : SourceOperation(InOperation)`
- L47 _public member_ `TWeakPtr<IPoseWatchManagerTreeItem> DraggedItem;`
- L50 _public member_ `const FDragDropOperation& SourceOperation;` — The source FDragDropOperation

#### struct `FPoseWatchManagerDragValidationInfo`  
`struct FPoseWatchManagerDragValidationInfo`  
_L54-79_
- desc: Struct used for validation of a drag/drop operation in the pose watch manager
- L57 _public member_ `EPoseWatchManagerDropCompatibility CompatibilityType;` — The tooltip type to display on the operation
- L60 _public member_ `FText ValidationText;` — The tooltip text to display on the operation
- L63 _public function_ `FPoseWatchManagerDragValidationInfo(const EPoseWatchManagerDropCompatibility InCompatibilityType, const FText InValidationText) : CompatibilityType(InCompatibilityType) , ValidationText(InValidationText)` — Construct this validation information out of a tooltip type and some text
- L69 _public function_ `static FPoseWatchManagerDragValidationInfo Invalid()` — Return a generic invalid result
- L75 _public function_ `bool IsValid() const` — @return true if this operation is valid, false otherwise

#### struct `FPoseWatchManagerDragDropOp`  
`struct FPoseWatchManagerDragDropOp : public FCompositeDragDropOp`  
_L82-114_
- inherits: `FCompositeDragDropOp`
- desc: A drag/drop operation that was started from the pose watch manager
- L84 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FPoseWatchManagerDragDropOp, FCompositeDragDropOp);`
- L86 _public prototype_ `FPoseWatchManagerDragDropOp();`
- L90 _public function_ `void ResetTooltip()`
- L96 _public function_ `void SetTooltip(FText InOverrideText, const FSlateBrush* InOverrideIcon)`
- L102 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L106 _private prototype_ `EVisibility GetOverrideVisibility() const;`
- L107 _private prototype_ `EVisibility GetDefaultVisibility() const;`
- L109 _private member_ `FText OverrideText;`
- L110 _private function_ `FText GetOverrideText() const`
- L112 _private member_ `const FSlateBrush* OverrideIcon;`
- L113 _private function_ `const FSlateBrush* GetOverrideIcon() const`

#### class `FPoseWatchDragDropOp`  
`class FPoseWatchDragDropOp : public FDecoratedDragDropOp`  
_L117-136_
- inherits: `FDecoratedDragDropOp`
- L120 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FPoseWatchDragDropOp, FDecoratedDragDropOp) TWeakObjectPtr<UPoseWatch> PoseWatch;`
- L125 _public function_ `void Init(const TWeakObjectPtr<UPoseWatch>& InPoseWatch)`

#### class `FPoseWatchFolderDragDropOp`  
`class FPoseWatchFolderDragDropOp : public FDecoratedDragDropOp`  
_L138-156_
- inherits: `FDecoratedDragDropOp`
- L141 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FPoseWatchFolderDragDropOp, FDecoratedDragDropOp) TWeakObjectPtr<UPoseWatchFolder> PoseWatchFolder;`
- L146 _public function_ `void Init(const TWeakObjectPtr<UPoseWatchFolder>& InPoseWatchFolder)`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API PERSONA_API`

### `Source/Editor/Persona/Private/PoseWatchManagerElementTreeItem.h` (Private)


#### struct `FPoseWatchManagerElementTreeItem`  
`struct FPoseWatchManagerElementTreeItem : IPoseWatchManagerTreeItem`  
_L11-41_
- inherits: `IPoseWatchManagerTreeItem`
- L14 _public prototype_ `FPoseWatchManagerElementTreeItem(TWeakObjectPtr<UPoseWatchElement> InPoseWatchElement);`
- L17 _public member_ `const FObjectKey ID;` — Constant identifier for this tree item
- L20 _public member_ `TWeakObjectPtr<UPoseWatchElement> PoseWatchElement;` — The node watch component this item is describing
- L23 _public member_ `static const EPoseWatchTreeItemType Type;` — Static type identifier for this tree item class
- L25 _public function_ `bool IsValid() const override`
- L28 _public prototype_ `virtual FObjectKey GetID() const override;` — Begin IPoseWatchManagerTreeItem Implementation
- L29 _public prototype_ `virtual FString GetDisplayString() const override;`
- L30 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(IPoseWatchManager& Outliner, const STableRow<FPoseWatchManagerTreeItemPtr>& InRow) override;`
- L31 _public prototype_ `virtual bool GetVisibility() const override;`
- L32 _public prototype_ `virtual bool IsAssignedFolder() const;`
- L33 _public prototype_ `virtual void SetIsVisible(const bool bVisible) override;`
- L34 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenu() override;`
- L35 _public prototype_ `virtual void OnRemoved() override;`
- L36 _public prototype_ `virtual bool IsEnabled() const override;`
- L37 _public prototype_ `virtual FColor GetColor() const override;`
- L38 _public prototype_ `virtual void SetColor(const FColor& InColor) override;`
- L39 _public prototype_ `virtual bool ShouldDisplayColorPicker() const override;`

### `Source/Editor/Persona/Private/PoseWatchManagerFolderTreeItem.h` (Private)


#### struct `FPoseWatchManagerFolderTreeItem`  
`struct FPoseWatchManagerFolderTreeItem : IPoseWatchManagerTreeItem`  
_L12-41_
- inherits: `IPoseWatchManagerTreeItem`
- L15 _public prototype_ `FPoseWatchManagerFolderTreeItem(UPoseWatchFolder* InPoseWatchFolder);`
- L18 _public member_ `const FObjectKey ID;` — Constant identifier for this tree item
- L21 _public member_ `TWeakObjectPtr<UPoseWatchFolder> PoseWatchFolder;` — The pose watch folder this item is describing
- L24 _public member_ `static const EPoseWatchTreeItemType Type;` — Static type identifier for this tree item class
- L26 _public function_ `bool IsValid() const override`
- L29 _public prototype_ `virtual FObjectKey GetID() const override;` — Begin IPoseWatchManagerTreeItem Implementation
- L30 _public prototype_ `virtual FString GetDisplayString() const override;`
- L31 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(IPoseWatchManager& Outliner, const STableRow<FPoseWatchManagerTreeItemPtr>& InRow) override;`
- L32 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenu() override;`
- L33 _public prototype_ `virtual bool GetVisibility() const override;`
- L34 _public prototype_ `virtual bool IsAssignedFolder() const override;`
- L35 _public prototype_ `virtual void SetIsVisible(const bool bVisible) override;`
- L36 _public prototype_ `virtual bool HasChildren() const override;`
- L37 _public prototype_ `virtual void OnRemoved() override;`
- L38 _public prototype_ `virtual void SetIsExpanded(const bool bIsExpanded) override;`
- L39 _public prototype_ `virtual bool IsExpanded() const override;`

### `Source/Editor/Persona/Private/PoseWatchManagerFwd.h` (Private)
_(no declarations extracted)_

### `Source/Editor/Persona/Private/PoseWatchManagerPoseWatchTreeItem.h` (Private)


#### struct `FPoseWatchManagerPoseWatchTreeItem`  
`struct FPoseWatchManagerPoseWatchTreeItem : IPoseWatchManagerTreeItem`  
_L11-40_
- inherits: `IPoseWatchManagerTreeItem`
- L14 _public prototype_ `FPoseWatchManagerPoseWatchTreeItem(UPoseWatch* InPoseWatch);`
- L17 _public member_ `const FObjectKey ID;` — Constant identifier for this tree item
- L20 _public member_ `TWeakObjectPtr<UPoseWatch> PoseWatch;` — The pose watch this item is describing
- L23 _public member_ `static const EPoseWatchTreeItemType Type;` — Static type identifier for this tree item class
- L25 _public function_ `bool IsValid() const override`
- L28 _public prototype_ `virtual FObjectKey GetID() const override;` — Begin IPoseWatchManagerTreeItem Implementation
- L29 _public prototype_ `virtual FString GetDisplayString() const override;`
- L30 _public prototype_ `virtual TSharedRef<SWidget> GenerateLabelWidget(IPoseWatchManager& Outliner, const STableRow<FPoseWatchManagerTreeItemPtr>& InRow) override;`
- L31 _public prototype_ `virtual bool GetVisibility() const override;`
- L32 _public prototype_ `virtual bool IsAssignedFolder() const;`
- L33 _public prototype_ `virtual void SetIsVisible(const bool bVisible) override;`
- L34 _public prototype_ `virtual TSharedPtr<SWidget> CreateContextMenu() override;`
- L35 _public prototype_ `virtual void OnRemoved() override;`
- L36 _public prototype_ `virtual bool IsEnabled() const override;`
- L37 _public prototype_ `virtual void SetIsExpanded(const bool bIsExpanded) override;`
- L38 _public prototype_ `virtual bool IsExpanded() const override;`

### `Source/Editor/Persona/Private/PoseWatchManagerPublicTypes.h` (Private)


#### struct `FPoseWatchManagerBuiltInColumnTypes`  
`struct FPoseWatchManagerBuiltInColumnTypes`  
_L9-28_
- desc: Container for built in column types. Function-static so they are available without linking
- L11 _public function_ `static const FName& Visibility()`
- L17 _public function_ `static const FName& Label()`
- L23 _public function_ `static FName& Color()`

#### enum `EPoseWatchManagerColumnVisibility`  
`enum class EPoseWatchManagerColumnVisibility : uint8`  
_L30-34_
- L32 _public enumerator_ `Visible`
- L33 _public enumerator_ `Invisible`

#### struct `FPoseWatchManagerInitializationOptions`  
`struct FPoseWatchManagerInitializationOptions`  
_L36-42_
- L39 _public member_ `TWeakPtr<class FBlueprintEditor> BlueprintEditor;` — The blueprint editor this pose watch manager is reflecting
- L41 _public function_ `FPoseWatchManagerInitializationOptions()`

#### struct `FPoseWatchManagerDefaultTreeItemMetrics`  
`struct FPoseWatchManagerDefaultTreeItemMetrics`  
_L44-49_
- L46 _public function_ `static float RowHeight()`
- L47 _public function_ `static float IconSize()`
- L48 _public function_ `static FMargin IconPadding()`

### `Source/Editor/Persona/Private/PoseWatchManagerStandaloneTypes.h` (Private)


#### enum `EPoseWatchTreeItemType`  
`enum EPoseWatchTreeItemType`  
_L20-25_
- L22 _public enumerator_ `PoseWatch`
- L23 _public enumerator_ `Folder`
- L24 _public enumerator_ `Element`

#### struct `FPoseWatchManagerCommonLabelData`  
`struct FPoseWatchManagerCommonLabelData`  
_L27-35_
- L29 _public member_ `TWeakPtr<IPoseWatchManager> WeakPoseWatchManager;`
- L30 _public member_ `static const FLinearColor DisabledColor;`
- L32 _public prototype_ `TOptional<FLinearColor> GetForegroundColor(const IPoseWatchManagerTreeItem& TreeItem) const;`
- L34 _public prototype_ `bool CanExecuteRenameRequest(const IPoseWatchManagerTreeItem& Item) const;`

#### struct `FPoseWatchManagerHierarchyChangedData`  
`struct FPoseWatchManagerHierarchyChangedData`  
_L38-51_
- L44 _public member_ `} Type;`
- L47 _public member_ `TArray<FPoseWatchManagerTreeItemPtr> Items;` — This event may pass one of two kinds of data, depending on the type of event
- L50 _public member_ `uint8 ItemActions = 0;` — Actions to apply to items

#### enum `FPoseWatchManagerHierarchyChangedData::(anonymous)`  
``  
_L41-44_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PERSONA_API`
- L15 _typedef_ `typedef TSharedPtr<IPoseWatchManagerTreeItem> FPoseWatchManagerTreeItemPtr;`
- L16 _typedef_ `typedef TSharedRef<IPoseWatchManagerTreeItem> FPoseWatchManagerTreeItemRef;`
- L18 _typedef_ `typedef TMap<FObjectKey, FPoseWatchManagerTreeItemPtr> FPoseWatchManagerTreeItemMap;`
- L42 _enumerator_ `Added` (scope `FPoseWatchManagerHierarchyChangedData::__anon62fa715a0103`)
- L43 _enumerator_ `FullRefresh` (scope `FPoseWatchManagerHierarchyChangedData::__anon62fa715a0103`)

### `Source/Editor/Persona/Private/PreviewSceneCustomizations.h` (Private)


#### struct `FPersonaModeComboEntry`  
`struct FPersonaModeComboEntry`  
_L24-36_
- desc: An entry in the preview mode choice box
- L27 _public member_ `UClass* Class;` — The preview controller class for this entry
- L30 _public member_ `FText Text;` — The localized label for this entry to show in the combo box
- L32 _public function_ `FPersonaModeComboEntry(UClass* InClass) : Class(InClass) , Text(InClass->GetDisplayNameText())`

#### class `FPreviewSceneDescriptionCustomization`  
`class FPreviewSceneDescriptionCustomization : public IDetailCustomization`  
_L38-129_
- inherits: `IDetailCustomization`
- L41 _public prototype_ `FPreviewSceneDescriptionCustomization(const FString& InSkeletonName, const TSharedRef<class IPersonaToolkit>& InPersonaToolkit);`
- L42 _public prototype_ `FPreviewSceneDescriptionCustomization(const FString& InSkeletonName, const TSharedRef<class IPersonaToolkit>& InPersonaToolkit, const FPersonaAdvancedPreviewSceneTabSettings& InDetailCustomizationSettings);`
- L44 _public prototype_ `~FPreviewSceneDescriptionCustomization();`
- L46 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L49 _private prototype_ `EVisibility GetSaveButtonVisibility(TSharedRef<IPropertyHandle> InAdditionalMeshesProperty) const;`
- L51 _private prototype_ `FReply OnSaveCollectionClicked(TSharedRef<IPropertyHandle> InAdditionalMeshesProperty, IDetailLayoutBuilder* DetailLayoutBuilder);`
- L53 _private prototype_ `bool HandleShouldFilterAsset(const FAssetData& InAssetData, FName InTag, bool bCanUseDifferentSkeleton);`
- L55 _private prototype_ `bool HandleShouldFilterAdditionalMesh(const FAssetData& InAssetData, bool bCanUseDifferentSkeleton);`
- L58 _private prototype_ `TSharedRef<SWidget> MakeControllerComboEntryWidget(TSharedPtr<FPersonaModeComboEntry> InItem) const;` — Helper function for making the widgets of each item in the preview controller combo box
- L61 _private prototype_ `FText GetCurrentPreviewControllerText() const;` — Delegate for getting the current preview controller text
- L64 _private prototype_ `void OnComboSelectionChanged(TSharedPtr<FPersonaModeComboEntry> InSelectedItem, ESelectInfo::Type SelectInfo);` — Called when the combo box selection changes, when a new parameter type is selected
- L67 _private prototype_ `void HandlePreviewControllerPropertyChanged();` — Called when user changes the preview controller type
- L69 _private prototype_ `void HandleMeshChanged(const FAssetData& InAssetData);`
- L71 _private prototype_ `void HandlePreviewAnimBlueprintChanged(const FAssetData& InAssetData);`
- L74 _private prototype_ `void HandleAnimBlueprintCompiled(UBlueprint* Blueprint);` — Called when the anim blueprint being edited is compiled.
- L76 _private prototype_ `void HandleAdditionalMeshesChanged(const FAssetData& InAssetData, IDetailLayoutBuilder* DetailLayoutBuilder);`
- L78 _private prototype_ `void HandleAllowDifferentSkeletonsCheckedStateChanged(ECheckBoxState CheckState);`
- L80 _private prototype_ `ECheckBoxState HandleAllowDifferentSkeletonsIsChecked() const;`
- L82 _private prototype_ `void HandleUseCustomAnimBPCheckedStateChanged(ECheckBoxState CheckState);`
- L84 _private prototype_ `ECheckBoxState HandleUseCustomAnimBPIsChecked() const;`
- L87 _private prototype_ `void ReinitializePreviewController();` — Reinitialize the preview controller in the preview scene.
- L91 _private member_ `FString SkeletonName;` — Cached skeleton name to check for asset registry tags
- L94 _private member_ `TWeakPtr<class IPersonaToolkit> PersonaToolkit;` — The persona toolkit we are associated with
- L97 _private member_ `TWeakPtr<class FAnimationEditorPreviewScene> PreviewScene;` — Preview scene we will be editing
- L100 _private member_ `TWeakPtr<class IEditableSkeleton> EditableSkeleton;` — Editable Skeleton scene we will be editing
- L103 _private member_ `UPreviewMeshCollectionFactory* FactoryToUse;` — Factory to use when creating mesh collections
- L106 _private member_ `TArray<TSharedPtr<FPersonaModeComboEntry>> ControllerItems;` — Names of all preview controllers for choice UI
- L109 _private member_ `static TArray<FTopLevelAssetPath> AvailableClassNameList;` — This is list of class available to filter asset by. This list doesn't change once loaded, so only collect once
- L112 _private member_ `IDetailLayoutBuilder* MyDetailLayout;` — Our layout builder (cached so we can refresh)
- L114 _private member_ `TWeakObjectPtr<UDataAsset> DataAssetToDisplay;`
- L116 _private member_ `FPersonaAdvancedPreviewSceneTabSettings DetailCustomizationSettings;`
- L121 _private prototype_ `bool GetReplaceVisibility(TSharedPtr<IPropertyHandle> PropertyHandle) const;` — Called to get the visibility of the replace button
- L125 _private prototype_ `void OnResetToBaseClicked(TSharedPtr<IPropertyHandle> PropertyHandle);` — Called when reset to base is clicked
- L126 _private prototype_ `void OnResetAdditionalMeshes();`
- L128 _private member_ `TSharedPtr<IPropertyHandle> AdditionalMeshesProperty;`

#### class `FPreviewMeshCollectionEntryCustomization`  
`class FPreviewMeshCollectionEntryCustomization : public IPropertyTypeCustomization`  
_L131-156_
- inherits: `IPropertyTypeCustomization`
- L134 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L139 _public function_ `FPreviewMeshCollectionEntryCustomization(const TSharedPtr<IPersonaPreviewScene>& InPreviewScene) : PreviewScene(InPreviewScene)`
- L143 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L144 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L147 _private prototype_ `bool HandleShouldFilterAsset(const FAssetData& InAssetData, FString SkeletonName, USkeleton* Skeleton);`
- L149 _private prototype_ `void HandleMeshChanged(const FAssetData& InAssetData);`
- L151 _private prototype_ `void HandleMeshesArrayChanged(TSharedPtr<IPropertyUtilities> PropertyUtilities);`
- L155 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScene;` — Preview scene we will be editing

### `Source/Editor/Persona/Private/SAnimAssetFindReplace.h` (Private)


#### struct `FAnimAssetFindReplaceSummoner`  
`struct FAnimAssetFindReplaceSummoner : public FWorkflowTabFactory`  
_L22-32_
- inherits: `FWorkflowTabFactory`
- L25 _public prototype_ `FAnimAssetFindReplaceSummoner(TSharedPtr<FAssetEditorToolkit> InHostingApp, const FAnimAssetFindReplaceConfig& InConfig);`
- L27 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L28 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L31 _private member_ `FAnimAssetFindReplaceConfig Config;`

#### class `SAnimAssetFindReplace`  
`class SAnimAssetFindReplace : public IAnimAssetFindReplace, public FGCObject`  
_L34-124_
- inherits: `IAnimAssetFindReplace,FGCObject`
- L39 _public function_ `SLATE_BEGIN_ARGS(SAnimAssetFindReplace)`
- L41 _public prototype_ `SLATE_ARGUMENT(FAnimAssetFindReplaceConfig, Config) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L48 _public prototype_ `virtual void SetCurrentProcessor(TSubclassOf<UAnimAssetFindReplaceProcessor> InProcessor) override;` — IAnimAssetFindReplace interface
- L49 _public function_ `virtual UAnimAssetFindReplaceProcessor* GetCurrentProcessor() const override`
- L50 _public prototype_ `virtual UAnimAssetFindReplaceProcessor* GetProcessor(TSubclassOf<UAnimAssetFindReplaceProcessor> InProcessor) const override;`
- L54 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L55 _private prototype_ `virtual FString GetReferencerName() const override;`
- L57 _private prototype_ `void RefreshSearchResults();`
- L59 _private prototype_ `bool HandleFilterAsset(const FAssetData& InAssetData);`
- L61 _private prototype_ `FReply HandleReplace();`
- L63 _private prototype_ `FReply HandleReplaceAll();`
- L65 _private prototype_ `void ReplaceInAssets(const TArray<FAssetData>& InAssetDatas);`
- L67 _private prototype_ `void ReplaceInAsset(const FAssetData& InAssetData) const;`
- L69 _private prototype_ `FReply HandleRemove();`
- L71 _private prototype_ `FReply HandleRemoveAll();`
- L73 _private prototype_ `void RemoveInAssets(const TArray<FAssetData>& InAssetDatas);`
- L75 _private prototype_ `void RemoveInAsset(const FAssetData& InAssetData) const;`
- L77 _private prototype_ `bool ShouldFilterOutAsset(const FAssetData& InAssetData, bool& bOutIsOldAsset) const;`
- L80 _private function_ `void RequestRefreshUI()` — Request a 'full' refresh. Rebuilds find/replace widgets and also falls through to bRefreshRequested
- L83 _private function_ `void RequestRefreshCachedData()` — Request a refresh of cached data and search results. Re-caches data also falls through to bRefreshSearchResultsRequested
- L86 _private function_ `void RequestRefreshSearchResults()` — Refresh search results
- L88 _private prototype_ `FARFilter MakeARFilter() const;`
- L91 _private member_ `FAnimAssetFindReplaceConfig Config;`
- L93 _private member_ `FAssetPickerConfig AssetPickerConfig;`
- L95 _private member_ `EAnimAssetFindReplaceMode Mode = EAnimAssetFindReplaceMode::Find;`
- L97 _private member_ `TMap<TSubclassOf<UAnimAssetFindReplaceProcessor>, TObjectPtr<UAnimAssetFindReplaceProcessor>> Processors;`
- L99 _private member_ `UAnimAssetFindReplaceProcessor* CurrentProcessor = nullptr;`
- L101 _private member_ `FRefreshAssetViewDelegate RefreshAssetViewDelegate;`
- L103 _private member_ `FGetCurrentSelectionDelegate GetCurrentSelectionDelegate;`
- L105 _private member_ `FSetARFilterDelegate SetARFilterDelegate;`
- L107 _private member_ `bool bAssetsSelected = false;`
- L109 _private member_ `bool bFoundAssets = false;`
- L111 _private member_ `bool bRefreshCachedDataRequested = false;`
- L113 _private member_ `bool bRefreshUIRequested = false;`
- L115 _private member_ `bool bRefreshSearchResultsRequested = false;`
- L117 _private member_ `TArray<FAssetData> OldAssets;`
- L119 _private member_ `TObjectPtr<UAnimAssetFindReplaceContext> ToolbarContext;`
- L121 _private member_ `TSharedPtr<SBox> ToolbarContainer;`
- L123 _private member_ `TSharedPtr<SBox> FindReplaceWidgetContainer;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace AnimAssetFindReplacePrivate`
- L19 _prototype_ `extern TSharedPtr<SAnimAssetFindReplace> GetWidgetFromContext(const FToolMenuContext& InContext);` (scope `AnimAssetFindReplacePrivate`)

### `Source/Editor/Persona/Private/SAnimAttributePicker.h` (Private)


#### class `SAnimAttributePicker`  
`class SAnimAttributePicker : public SCompoundWidget`  
_L13-107_
- inherits: `SCompoundWidget`
- L24 _public prototype_ `virtual ~SAnimAttributePicker() override = default;` — Virtual destructor.
- L26 _public function_ `SLATE_BEGIN_ARGS(SAnimAttributePicker) : _bEnableMultiSelect(false) , _bCanShowOtherSkeletonAttributes(false)`
- L31 _public prototype_ `SLATE_EVENT(FOnAttributesPicked, OnAttributesPicked) SLATE_ARGUMENT(bool, bEnableMultiSelect) SLATE_ARGUMENT(bool, bCanShowOtherSkeletonAttributes) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TObjectPtr<const USkeleton> InSkeleton);`
- L42 _private prototype_ `void RefreshListItems();`
- L44 _private prototype_ `void FilterAvailableAttributes();`
- L70 _public function_ `inline friend uint32 GetTypeHash(const FAttributeData& Attribute)`
- L77 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(TSharedPtr<FAttributeData> InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L79 _private prototype_ `void HandleFilterTextChanged(const FText& InFilterText);`
- L81 _private prototype_ `EColumnSortMode::Type GetColumnSortMode(FName ColumnId) const;`
- L83 _private prototype_ `void OnSortModeChanged(EColumnSortPriority::Type Priority, const FName& ColumnId, EColumnSortMode::Type NewSortMode);`
- L86 _private member_ `FOnAttributesPicked OnAttributesPicked;`
- L88 _private member_ `TWeakObjectPtr<const USkeleton> Skeleton;`
- L90 _private member_ `TArray<TSharedPtr<FAttributeData>> ShownAttributes;`
- L92 _private member_ `TSet<FAttributeData> FoundUniqueAttributes;`
- L94 _private member_ `FString FilterText;`
- L96 _private member_ `TSharedPtr<SListView<TSharedPtr<FAttributeData>>> NameListView;`
- L98 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L100 _private member_ `bool bShowOtherSkeletonAttributes = false;`
- L102 _private member_ `TArray<FAssetData> OldAssets;`
- L104 _private member_ `FName SortColumn;`
- L106 _private member_ `EColumnSortMode::Type SortMode = EColumnSortMode::None;`

#### struct `SAnimAttributePicker::FColumnIds`  
`struct FColumnIds`  
_L16-21_
- L18 _public member_ `static const FName AttributeName;`
- L19 _public member_ `static const FName BoneName;`
- L20 _public member_ `static const FName AttributeType;`

#### struct `SAnimAttributePicker::FAttributeData`  
`struct FAttributeData`  
_L47-74_
- L49 _public member_ `FName AttributeName;`
- L51 _public member_ `FName BoneName;`
- L53 _public member_ `int32 BoneIndex;`
- L55 _public member_ `FName AttributeType;`
- L57 _public function_ `FAttributeData(const FAnimationAttributeIdentifier& InAttributeId) : AttributeName(InAttributeId.GetName()) , BoneName(InAttributeId.GetBoneName()) , BoneIndex(InAttributeId.GetBoneIndex()) , AttributeType(FName(InAttributeId.GetScriptStructPath().ToString()))`
- L65 _public function_ `bool operator==(const FAttributeData& Other) const`

### `Source/Editor/Persona/Private/SAnimBlueprintParentPlayerList.h` (Private)


#### class `SAnimBlueprintParentPlayerList`  
`class SAnimBlueprintParentPlayerList : public SCompoundWidget`  
_L16-61_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SAnimBlueprintParentPlayerList)`
- L24 _public prototype_ `SAnimBlueprintParentPlayerList();`
- L25 _public prototype_ `~SAnimBlueprintParentPlayerList();`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FBlueprintEditor>& InBlueprintEditor, FSimpleMulticastDelegate& InOnPostUndo);`
- L34 _private prototype_ `void OnRootBlueprintChanged(UBlueprint* InBlueprint);` — Called when the root blueprint is changed. depending on the action we need to refresh the list of available overrides incase we need to remove or add some
- L38 _private prototype_ `void OnCurrentBlueprintChanged(UBlueprint* InBlueprint);` — Called when the current blueprint changes. Used to detect reparenting So the data and UI can be updated accordingly
- L43 _private prototype_ `void OnHierarchyOverrideChanged(FGuid NodeGuid, UAnimationAsset* NewAsset);` — Called when an override is changed on a less derived blueprint in the current blueprint's hierarchy so we can copy them if we haven't overridden the same asset
- L45 _private prototype_ `void RefreshDetailView();`
- L48 _private member_ `FEditorObjectTracker ObjectTracker;` — Object tracker to maintain single instance of editor objects
- L51 _private member_ `UAnimBlueprint* CurrentBlueprint;` — The blueprint currently in use
- L54 _private member_ `UClass* CurrentParentClass;` — Parent class of the current blueprint, used to detect reparenting
- L57 _private member_ `UAnimBlueprint* RootBlueprint;` — Root blueprint if one exists
- L60 _private member_ `TSharedPtr<IDetailsView> DetailView;` — The details view for the list

### `Source/Editor/Persona/Private/SAnimCompositeEditor.h` (Private)


#### class `SAnimCompositeEditor`  
`class SAnimCompositeEditor : public SAnimEditorBase, public FEditorUndoClient`  
_L25-66_
- inherits: `SAnimEditorBase,FEditorUndoClient`
- desc: Overall animation composite editing widget. This mostly contains functions for editing the UAnimComposite. SAnimCompositeEditor will create the SAnimCompositePanel which is mostly responsible for setting up the UI portion of the composite tool and registering callbacks to the SAnimCompositeEditor to do the actual editing.
- L28 _public function_ `SLATE_BEGIN_ARGS( SAnimCompositeEditor ) : _Composite(NULL)`
- L40 _private member_ `TSharedPtr<FAnimModel_AnimComposite> AnimModel;`
- L43 _public prototype_ `~SAnimCompositeEditor();`
- L45 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene, const TSharedRef<class IEditableSkeleton>& InEditableSkeleton, const TSharedRef<FUICommandList>& InCommandList);`
- L48 _public function_ `UAnimComposite* GetCompositeObj() const` — Return the animation composite being edited
- L49 _public function_ `virtual UAnimationAsset* GetEditorObject() const override`
- L53 _private member_ `UAnimComposite* CompositeObj;` — Pointer to the animation composite being edited
- L57 _public prototype_ `virtual TSharedRef<SWidget> CreateDocumentAnchor() override;`
- L61 _public prototype_ `virtual void PostUndo( bool bSuccess ) override;` — FEditorUndoClient interface
- L62 _public prototype_ `virtual void PostRedo( bool bSuccess ) override;`
- L65 _public prototype_ `void PostUndoRedo();` — Post undo

### `Source/Editor/Persona/Private/SAnimCompositePanel.h` (Private)


#### class `SAnimCompositePanel`  
`class SAnimCompositePanel : public SAnimTrackPanel, public FEditorUndoClient`  
_L25-104_
- inherits: `SAnimTrackPanel,FEditorUndoClient`
- L28 _public function_ `SLATE_BEGIN_ARGS( SAnimCompositePanel ) : _Composite() , _ViewInputMin() , _ViewInputMax() , _InputMin() , _InputMax() , _OnSetInputViewRange()`
- L37 _public prototype_ `SLATE_ARGUMENT( class UAnimComposite*, Composite) SLATE_ARGUMENT( float, WidgetWidth ) SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax ) SLATE_ATTRIBUTE( float, InputMin ) SLATE_ATTRIBUTE( float, InputMax ) SLATE_EVENT( FOnSetInputViewRange, OnSetInputViewRange ) SLATE_END_ARGS() ~SAnimCompositePanel();`
- L48 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FAnimModel>& InModel);`
- L51 _public prototype_ `void Update();` — Recreates the editor panel to reflect changes to the composite
- L54 _public prototype_ `void ClearSelected();` — Clears the selected segment from the details panel
- L57 _public prototype_ `void ShowSegmentInDetailsView(int32 SegmentIndex);` — Handlers for when the user clicks on a anim sequence node
- L60 _public prototype_ `void PreAnimUpdate();` — Delegate handlers for when the composite is being edited
- L61 _public prototype_ `void PostAnimUpdate();`
- L64 _public prototype_ `void SortAndUpdateComposite();` — This will sort all components of the composite and update (recreate) the UI
- L67 _public prototype_ `void OnCompositeChange(class UObject *EditorAnimBaseObj, bool bRebuild);` — Handler for when composite is edited in details view
- L70 _public prototype_ `EActiveTimerReturnType TriggerRebuildPanel(double InCurrentTime, float InDeltaTime);` — One-off active timer to trigger a panel rebuild
- L73 _public prototype_ `virtual void PostUndo( bool bSuccess ) override;` — FEditorUndoClient interface
- L74 _public prototype_ `virtual void PostRedo( bool bSuccess ) override;`
- L75 _public prototype_ `void PostUndoRedo();`
- L77 _public prototype_ `void CollapseComposite();`
- L80 _public prototype_ `FLinearColor HandleGetNodeColor(const FAnimSegment& InSegment) const;` — Get a color for an anim segment
- L82 _public prototype_ `void HandleObjectsSelected(const TArray<UObject*>& InObjects);`
- L84 _public prototype_ `bool OnIsAnimAssetValid(const UAnimSequenceBase* AnimSequenceBase, FText* OutReason);`
- L88 _private member_ `TWeakPtr<FAnimModel> WeakModel;` — Reference to our editor model
- L91 _private member_ `class UAnimComposite* Composite;` — The composite we are currently editing
- L94 _private member_ `TSharedPtr<SBorder> PanelArea;` — Is populated by the Update method with the panels UI
- L97 _private member_ `STrackNodeSelectionSet SelectionSet;` — Passed to the anim segments panel to handle selection
- L100 _private member_ `bool bIsActiveTimerRegistered;` — Whether the active timer to trigger a panel rebuild is currently registered
- L103 _private member_ `bool bIsSelecting;` — Recursion guard for selection

### `Source/Editor/Persona/Private/SAnimCurveEd.h` (Private)


#### class `SAnimCurveEd`  
`class SAnimCurveEd: public SCurveEditor`  
_L32-76_
- inherits: `SCurveEditor`
- L35 _public function_ `SLATE_BEGIN_ARGS(SAnimCurveEd) : _ViewMinInput(0.0f) , _ViewMaxInput(10.0f) , _TimelineLength(5.0f) , _DrawCurve(true) , _HideUI(true) , _OnGetScrubValue()`
- L44 _public prototype_ `SLATE_ATTRIBUTE(float, ViewMinInput) SLATE_ATTRIBUTE(float, ViewMaxInput) SLATE_ATTRIBUTE(TOptional<float>, DataMinInput) SLATE_ATTRIBUTE(TOptional<float>, DataMaxInput) SLATE_ATTRIBUTE(float, TimelineLength) SLATE_ATTRIBUTE(int32, NumberOfKeys) SLATE_ATTRIBUTE(FVector2D, DesiredSize) SLATE_ARGUMENT(bool, DrawCurve) SLATE_ARGUMENT(bool, HideUI) SLATE_EVENT(FOnGetScrubValue, OnGetScrubValue) SLATE_EVENT(FOnSetInputViewRange, OnSetInputViewRange) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L61 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget interface
- L62 _protected prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L63 _protected prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L67 _protected prototype_ `virtual void SetDefaultOutput(const float MinZoomRange) override;` — SCurveEditor interface
- L68 _protected prototype_ `virtual float GetTimeStep(FTrackScaleInfo &ScaleInfo) const override;`
- L73 _private member_ `FOnGetScrubValue OnGetScrubValue;` — scrub value grabber
- L75 _private member_ `TAttribute<int32> NumberOfKeys;` — @todo redo this code, all mess and dangerous

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSelectionChanged, const TArray<UObject*>&) DECLARE_DELEGATE(FOnUpdatePanel) DECLARE_DELEGATE_RetVal(float, FOnGetScrubValue)`
- L26 _delegate_ `DECLARE_DELEGATE(FOnUpdatePanel) DECLARE_DELEGATE_RetVal(float, FOnGetScrubValue)`
- L27 _delegate_ `DECLARE_DELEGATE_RetVal(float, FOnGetScrubValue)`

### `Source/Editor/Persona/Private/SAnimCurveMetadataEditor.h` (Private)


#### struct `FAnimCurveMetadataEditorClipboardEntry`  
`struct FAnimCurveMetadataEditorClipboardEntry`  
_L35-44_
- reflection: `USTRUCT()`
- desc: Clipboard contents for anim curves
- L40 _public member_ `FName CurveName;` — `UPROPERTY()`
- L43 _public member_ `FCurveMetaData MetaData;` — `UPROPERTY()`

#### struct `FAnimCurveMetadataEditorClipboard`  
`struct FAnimCurveMetadataEditorClipboard`  
_L47-53_
- reflection: `USTRUCT()`
- L52 _public member_ `TArray<FAnimCurveMetadataEditorClipboardEntry> Entries;` — `UPROPERTY()`

#### class `FAnimCurveMetadataEditorItem`  
`class FAnimCurveMetadataEditorItem`  
_L58-83_
- L61 _public member_ `FName CurveName;`
- L62 _public member_ `TWeakObjectPtr<UAnimCurveMetaData> AnimCurveMetaData;` — The asset user data we are associated with
- L63 _public member_ `TSharedPtr<SInlineEditableTextBlock> EditableText;` — The editable text box in the list, used to focus from the context menu
- L64 _public member_ `UEditorAnimCurveBoneLinks* EditorMirrorObject;`
- L65 _public member_ `EAnimCurveMetadataEditorFilterFlags Flags;`
- L66 _public member_ `bool bShown;`
- L69 _public function_ `static TSharedRef<FAnimCurveMetadataEditorItem> Make(UAnimCurveMetaData* InAnimCurveMetaData, const FName& InCurveName, EAnimCurveMetadataEditorFilterFlags InFlags, UEditorAnimCurveBoneLinks* InEditorMirrorObject)` — Static function for creating a new item, but ensures that you can only have a TSharedRef to one
- L76 _protected function_ `FAnimCurveMetadataEditorItem(UAnimCurveMetaData* InAnimCurveMetaData, const FName& InCurveName, EAnimCurveMetadataEditorFilterFlags InFlags, UEditorAnimCurveBoneLinks* InEditorMirrorObject) : CurveName(InCurveName) , AnimCurveMetaData(InAnimCurveMetaData) , EditorMirrorObject(InEditorMirrorObject) , Flags(InFlags) , bShown(false)` — Hidden constructor, always use Make above

#### class `SAnimCurveMetadataEditorRow`  
`class SAnimCurveMetadataEditorRow : public SMultiColumnTableRow< TSharedPtr<FAnimCurveMetadataEditorItem> >`  
_L88-133_
- inherits: `SMultiColumnTableRow<TSharedPtr<FAnimCurveMetadataEditorItem>>`
- L92 _public function_ `SLATE_BEGIN_ARGS(SAnimCurveMetadataEditorRow)`
- L95 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FAnimCurveMetadataEditorItem>, Item) SLATE_ARGUMENT(class TWeakPtr<SAnimCurveMetadataEditor>, AnimCurveViewerPtr) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene);` — The item for this row
- L105 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L109 _private prototype_ `void OnAnimCurveTypeBoxChecked(ECheckBoxState InState, bool bMorphTarget);` — Curve Flag checks for morphtarget or material
- L110 _private prototype_ `ECheckBoxState IsAnimCurveTypeBoxChangedChecked(bool bMorphTarget) const;`
- L113 _private prototype_ `FText GetItemName() const;` — Returns name of this curve
- L115 _private prototype_ `FText GetFilterText() const;` — Get text we are filtering for
- L118 _private member_ `TWeakPtr<SAnimCurveMetadataEditor> AnimCurveViewerPtr;` — The SAnimCurveMetadataEditor that we push the morph target weights into
- L121 _private member_ `TSharedPtr<FAnimCurveMetadataEditorItem> Item;` — The name and weight of the morph target
- L124 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScenePtr;` — Preview scene used to update on scrub
- L126 _private prototype_ `TSharedRef<SWidget> GetCurveTypeWidget();` — Returns curve type widget constructed
- L129 _private prototype_ `FText GetNumConnectedBones() const;` — returns display text for number of connected joint setting
- L132 _private prototype_ `FText GetMaxLOD() const;` — returns display text for max LOD setting

#### class `SAnimCurveMetadataEditor`  
`class SAnimCurveMetadataEditor : public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L138-328_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- L141 _public function_ `SLATE_BEGIN_ARGS( SAnimCurveMetadataEditor )`
- L144 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, UObject* InAnimCurveMetaDataHost, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene, FOnObjectsSelected InOnObjectsSelected);`
- L158 _public prototype_ `virtual ~SAnimCurveMetadataEditor();` — Destructor - resets the animation curve
- L161 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — SWidget interface
- L169 _public prototype_ `void OnPreviewMeshChanged(class USkeletalMesh* OldPreviewMesh, class USkeletalMesh* NewPreviewMesh);` — Is registered with Persona to handle when its preview mesh is changed. @param NewPreviewMesh - The new preview mesh being used by Persona
- L176 _public prototype_ `void OnPreviewAssetChanged(class UAnimationAsset* NewPreviewAsset);` — Is registered with Persona to handle when its preview asset is changed. Pose Asset will have to add curve manually
- L179 _public prototype_ `void OnCurvesChanged();` — Is registered with Persona to handle when curves change.
- L187 _public prototype_ `void OnFilterTextChanged( const FText& SearchText );` — Filters the SListView when the user changes the search text box (NameFilterBox) @param SearchText - The text the user has typed
- L197 _public prototype_ `void OnFilterTextCommitted( const FText& SearchText, ETextCommit::Type CommitInfo );` — Filters the SListView when the user hits enter or clears the search box Simply calls OnFilterTextChanged @param SearchText - The text the user has typed @param CommitInfo - Not used
- L207 _public prototype_ `TSharedRef<ITableRow> GenerateAnimCurveRow(TSharedPtr<FAnimCurveMetadataEditorItem> InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Create a widget for an entry in the tree from an info @param InInfo - Shared pointer to the morph target we're generating a row for @param OwnerTable - The table that owns this row @return A new Slate widget, containing the UI for this row
- L213 _public function_ `FText& GetFilterText()` — Accessor so our rows can grab the filtertext for highlighting
- L216 _public function_ `virtual void PostUndo(bool bSuccess) override` — FSelfRegisteringEditorUndoClient interface
- L217 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L222 _public prototype_ `void PostUndoRedo();` — Refreshes the morph target list after an undo
- L224 _public prototype_ `void RefreshCurveList(bool bInFullRefresh);`
- L227 _public prototype_ `virtual void OnNameCommitted(const FText& NewName, ETextCommit::Type CommitType, TSharedPtr<FAnimCurveMetadataEditorItem> Item);` — When a name is committed after being edited in the list
- L231 _private prototype_ `void BindCommands();`
- L234 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuContent() const;` — Handler for context menus
- L235 _private prototype_ `void OnSelectionChanged(TSharedPtr<FAnimCurveMetadataEditorItem> InItem, ESelectInfo::Type SelectInfo);`
- L243 _private prototype_ `void CreateAnimCurveList( const FString& SearchText = FString(), bool bInFullRefresh = false );` — Clears and rebuilds the table, according to an optional search string @param SearchText - Optional search string
- L245 _private prototype_ `void OnDeleteNameClicked();`
- L246 _private prototype_ `bool CanDelete();`
- L248 _private prototype_ `void OnRenameClicked();`
- L249 _private prototype_ `bool CanRename();`
- L251 _private prototype_ `void OnCopyClicked();`
- L252 _private prototype_ `bool CanCopy() const;`
- L254 _private prototype_ `void OnPasteClicked();`
- L255 _private prototype_ `bool CanPaste() const;`
- L257 _private prototype_ `void OnAddClicked();`
- L259 _private prototype_ `void OnFindCurveUsesClicked();`
- L260 _private prototype_ `bool CanFindCurveUses();`
- L263 _private prototype_ `void CreateNewNameEntry(const FText& CommittedText, ETextCommit::Type CommitType);` — Adds a new curve metadata name entry to the skeleton
- L266 _private prototype_ `void HandleCurveMetaDataChange();` — Handle curve meta data removal
- L269 _private prototype_ `UAnimCurveMetaData* GetAnimCurveMetaData() const;` — Get the metadata to edit
- L272 _private prototype_ `USkeleton* GetSkeleton() const;` — Get the skeleton associated with any bone references
- L275 _private prototype_ `UAnimInstance* GetAnimInstance() const;` — Get the anim instance we are viewing
- L278 _private prototype_ `void FindReplaceCurves();` — Open the find/replace tab to process curves. Automatically supplies the name of the selected curve, if any
- L281 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScenePtr;` — Pointer to the preview scene we are bound to
- L284 _private member_ `TWeakInterfacePtr<IInterface_AssetUserData> AnimCurveMetaDataHost;` — Pointer to the metada interface
- L287 _private member_ `TSharedPtr<SSearchBox> NameFilterBox;` — Box to filter to a specific morph target name
- L290 _private member_ `TArray< TSharedPtr<FAnimCurveMetadataEditorItem> > AnimCurveList;` — A list of animation curve. Used by the AnimCurveListView.
- L293 _private member_ `TMap< FName, TSharedPtr<FAnimCurveMetadataEditorItem> > AllSeenAnimCurvesMap;` — Tracking map of anim curves
- L296 _private member_ `UAnimInstance* CachedPreviewInstance;` — The skeletal mesh that we grab the animation curve from
- L299 _private member_ `TSharedPtr<SListView< TSharedPtr<FAnimCurveMetadataEditorItem> >> AnimCurveListView;` — Widget used to display the list of animation curve
- L302 _private member_ `FText FilterText;` — Current text typed into NameFilterBox
- L304 _private member_ `EAnimCurveMetadataEditorFilterFlags CurrentCurveFlag;`
- L306 _private member_ `TMap<FName, float> OverrideCurves;`
- L309 _private member_ `TSharedPtr<FUICommandList> UICommandList;` — Commands that are bound to delegates
- L315 _private member_ `FEditorObjectTracker EditorObjectTracker;` — Tracks objects created for the details panel
- L318 _private member_ `FOnObjectsSelected OnObjectsSelected;` — Delegate called to select objects
- L321 _private prototype_ `void ApplyCurveBoneLinks(class UEditorAnimCurveBoneLinks* EditorObj);` — apply curve bone links from editor mirror object to skeleton
- L324 _private member_ `FDelegateHandle CurveMetaDataChangedHandle;` — Delegate handle for HandleCurveMetaDataChange callback
- L327 _private member_ `TArray<TSharedRef<FFilterBase<EAnimCurveMetadataEditorFilterFlags>>> Filters;` — All filters that can be applied to the widget's display

### `Source/Editor/Persona/Private/SAnimCurvePicker.h` (Private)


#### class `SAnimCurvePicker`  
`class SAnimCurvePicker : public SCompoundWidget`  
_L15-90_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SAnimCurvePicker) : _bEnableMultiselect(false)`
- L26 _public function_ `FOnCurvesPicked ConvertOnCurvePickedFn(const FOnCurvePicked& LegacyDelegate)`
- L37 _public prototype_ `SLATE_EVENT(FOnCurvesPicked, OnCurvesPicked) SLATE_EVENT(FIsCurveNameMarkedForExclusion, IsCurveNameMarkedForExclusion) SLATE_ARGUMENT(bool, bEnableMultiselect) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const USkeleton* InSkeleton);`
- L54 _private prototype_ `void RefreshListItems();` — Refresh the list of available curves
- L57 _private prototype_ `void FilterAvailableCurves();` — Filter available curves
- L60 _private prototype_ `TSharedRef<ITableRow> HandleGenerateRow(TSharedPtr<FName> InItem, const TSharedRef<STableViewBase>& InOwnerTable);` — UI handlers
- L61 _private prototype_ `void HandleFilterTextChanged(const FText& InFilterText);`
- L65 _private member_ `FOnCurvesPicked OnCurvesPicked;` — Delegate fired when the curves selection is confirmed
- L68 _private member_ `FIsCurveNameMarkedForExclusion IsCurveNameMarkedForExclusion;` — Filter predicate to determine if curve should be excluded from the picker's curve list
- L71 _private member_ `TWeakObjectPtr<const USkeleton> Skeleton;` — The editable skeleton we use to grab curves from
- L74 _private member_ `TArray<TSharedPtr<FName>> CurveNames;` — The names of the curves we are displaying
- L77 _private member_ `TSet<FName> UniqueCurveNames;` — All the unique curve names we can find
- L80 _private member_ `FString FilterText;` — The string we use to filter curve names
- L83 _private member_ `TSharedPtr<SListView<TSharedPtr<FName>>> NameListView;` — The list view used to display names
- L86 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — The search box used to filter curves
- L89 _private member_ `bool bShowOtherSkeletonCurves;` — Whether we should show other skeleton's curves

#### Free symbols / members of external scopes

- L29 _function_ `` (scope `SAnimCurvePicker::ConvertOnCurvePickedFn`)

### `Source/Editor/Persona/Private/SAnimCurveViewer.h` (Private)


#### class `FDisplayedAnimCurveInfo`  
`class FDisplayedAnimCurveInfo`  
_L43-72_
- L46 _public member_ `FName CurveName;`
- L47 _public member_ `float Weight;`
- L48 _public member_ `bool bOverrideData;`
- L49 _public member_ `bool bShown;`
- L50 _public member_ `bool bMorphTarget;`
- L51 _public member_ `bool bMaterial;`
- L54 _public function_ `static TSharedRef<FDisplayedAnimCurveInfo> Make(const FName& InCurveName)` — Static function for creating a new item, but ensures that you can only have a TSharedRef to one
- L60 _public prototype_ `bool GetActiveFlag(const TSharedPtr<SAnimCurveViewer>& InAnimCurveViewer, bool bMorphTarget) const;` — Get the active morph/material flag for this curve
- L64 _protected function_ `FDisplayedAnimCurveInfo(const FName& InCurveName) : CurveName(InCurveName) , Weight(0.0f) , bOverrideData(false) , bShown(false) , bMorphTarget(false) , bMaterial(false)` — Hidden constructor, always use Make above

#### class `SAnimCurveListRow`  
`class SAnimCurveListRow : public SMultiColumnTableRow< TSharedPtr<FDisplayedAnimCurveInfo> >`  
_L79-161_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDisplayedAnimCurveInfo>>`
- L83 _public function_ `SLATE_BEGIN_ARGS(SAnimCurveListRow)`
- L86 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FDisplayedAnimCurveInfo>, Item) SLATE_ARGUMENT(class TWeakPtr<SAnimCurveViewer>, AnimCurveViewerPtr) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene);` — The item for this row
- L96 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L106 _private prototype_ `void OnAnimCurveWeightChanged(float NewWeight);` — Called when the user changes the value of the SSpinBox @param NewWeight - The new number the SSpinBox is set to
- L113 _private prototype_ `void OnAnimCurveWeightValueCommitted(float NewWeight, ETextCommit::Type CommitType);` — Called when the user types the value and enters @param NewWeight - The new number the SSpinBox is set to
- L116 _private prototype_ `void OnAnimCurveOverrideChecked(ECheckBoxState InState);` — Override check call back functions
- L117 _private prototype_ `ECheckBoxState IsAnimCurveOverrideChecked() const;`
- L120 _private prototype_ `bool GetActiveFlag(bool bMorphTarget) const;` — Check for an active morph target or material flag
- L123 _private prototype_ `ECheckBoxState IsAnimCurveTypeBoxChangedChecked(bool bMorphTarget) const;` — Curve Flag checks for morphtarget or material
- L126 _private prototype_ `float GetWeight() const;` — Returns the weight of this curve
- L128 _private prototype_ `TOptional<float> GetMinWeight() const;` — Returns the min seen weight of this curve
- L130 _private prototype_ `TOptional<float> GetMaxWeight() const;` — Returns the max seen weight of this curve
- L132 _private prototype_ `FText GetItemName() const;` — Returns name of this curve
- L134 _private prototype_ `FText GetFilterText() const;` — Get text we are filtering for
- L136 _private prototype_ `FSlateFontInfo GetItemFont() const;` — Return font for text of item
- L139 _private prototype_ `bool GetActiveWeight(float& OutWeight) const;` — Get current active weight. Returns false if not currently active
- L142 _private prototype_ `bool CanBeEdited() const;` — If the values of the curve represented by this row can be edited
- L145 _private member_ `TWeakPtr<SAnimCurveViewer> AnimCurveViewerPtr;` — The SAnimCurveViewer that we push the morph target weights into
- L148 _private member_ `TSharedPtr<FDisplayedAnimCurveInfo> Item;` — The name and weight of the morph target
- L151 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScenePtr;` — Preview scene used to update on scrub
- L154 _private member_ `mutable float MinWeight = -1.0f;` — The min weight we have seen
- L157 _private member_ `mutable float MaxWeight = 1.0f;` — The max weight we have seen
- L160 _private prototype_ `TSharedRef<SWidget> GetCurveTypeWidget();` — Returns curve type widget constructed

#### class `SAnimCurveViewer`  
`class SAnimCurveViewer : public SCompoundWidget, public FSelfRegisteringEditorUndoClient`  
_L166-345_
- inherits: `SCompoundWidget,FSelfRegisteringEditorUndoClient`
- L169 _public function_ `SLATE_BEGIN_ARGS( SAnimCurveViewer )`
- L171 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<IEditableSkeleton>, EditableSkeleton) SLATE_ARGUMENT(bool, bIsReadOnly) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene, FOnObjectsSelected InOnObjectsSelected);`
- L187 _public prototype_ `virtual ~SAnimCurveViewer();` — Destructor - resets the animation curve
- L195 _public prototype_ `void OnPreviewMeshChanged(class USkeletalMesh* OldPreviewMesh, class USkeletalMesh* NewPreviewMesh);` — Is registered with Persona to handle when its preview mesh is changed. @param NewPreviewMesh - The new preview mesh being used by Persona
- L202 _public prototype_ `void OnPreviewAssetChanged(class UAnimationAsset* NewPreviewAsset);` — Is registered with Persona to handle when its preview asset is changed. Pose Asset will have to add curve manually
- L210 _public prototype_ `void OnFilterTextChanged( const FText& SearchText );` — Filters the SListView when the user changes the search text box (NameFilterBox) @param SearchText - The text the user has typed
- L220 _public prototype_ `void OnFilterTextCommitted( const FText& SearchText, ETextCommit::Type CommitInfo );` — Filters the SListView when the user hits enter or clears the search box Simply calls OnFilterTextChanged @param SearchText - The text the user has typed @param CommitInfo - Not used
- L230 _public prototype_ `TSharedRef<ITableRow> GenerateAnimCurveRow(TSharedPtr<FDisplayedAnimCurveInfo> InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Create a widget for an entry in the tree from an info @param InInfo - Shared pointer to the morph target we're generating a row for @param OwnerTable - The table that owns this row @return A new Slate widget, containing the UI for this row
- L239 _public prototype_ `void AddAnimCurveOverride( FName& Name, float Weight);` — Adds a curve override or updates the weight for an existing one @param Name - Name of the curve we want to override @param Weight - How much of this curve to apply (0.0 - 1.0)
- L242 _public prototype_ `void RemoveAnimCurveOverride(FName& Name);` — Removes an existing curve override
- L245 _public prototype_ `bool GetAnimCurveOverride(FName& Name, float& Weight);` — Is there currently an override for this curve, and if so, what is its weight
- L251 _public function_ `FText& GetFilterText()` — Accessor so our rows can grab the filtertext for highlighting
- L254 _public function_ `virtual void PostUndo(bool bSuccess) override` — FSelfRegisteringEditorUndoClient interface
- L255 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L260 _public prototype_ `void PostUndoRedo();` — Refreshes the morph target list after an undo
- L263 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L264 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L266 _public prototype_ `void RefreshCurveList(bool bInFullRefresh);`
- L276 _private prototype_ `void CreateAnimCurveList( const FString& SearchText = FString(), bool bInFullRefresh = false );` — Clears and rebuilds the table, according to an optional search string @param SearchText - Optional search string
- L278 _private prototype_ `void ApplyCustomCurveOverride(UAnimInstance* AnimInstance) const;`
- L281 _private prototype_ `void HandleCurveMetaDataChange();` — Handle curve meta data removal
- L284 _private prototype_ `UAnimInstance* GetAnimInstance() const;` — Get the anim instance we are viewing
- L286 _private prototype_ `TSharedRef<SWidget> CreateCurveSourceSelector();`
- L288 _private prototype_ `void BindCommands();`
- L291 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuContent() const;` — Build context menu
- L293 _private prototype_ `void OnFindCurveUsesClicked();`
- L294 _private prototype_ `bool CanFindCurveUses();`
- L295 _private prototype_ `void FindReplaceCurves();`
- L298 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScenePtr;` — Pointer to the preview scene we are bound to
- L301 _private member_ `TWeakPtr<class IEditableSkeleton> EditableSkeletonPtr;` — Pointer to the editable skeleton
- L304 _private member_ `TSharedPtr<SSearchBox> NameFilterBox;` — Box to filter to a specific morph target name
- L307 _private member_ `TArray< TSharedPtr<FDisplayedAnimCurveInfo> > AnimCurveList;` — A list of animation curve. Used by the AnimCurveListView.
- L310 _private member_ `TMap< FName, TSharedPtr<FDisplayedAnimCurveInfo> > AllSeenAnimCurvesMap;` — Tracking map of anim curves
- L313 _private member_ `TSharedPtr<SAnimCurveListType> AnimCurveListView;` — Widget used to display the list of animation curve
- L316 _private member_ `FText FilterText;` — Current text typed into NameFilterBox
- L318 _private member_ `EAnimCurveViewerFilterFlags CurrentCurveFlag;`
- L321 _private member_ `bool bIsReadOnlyViewer = false;` — Whatever this viewer is read only or allows editing of its values
- L323 _private member_ `TMap<FName, float> OverrideCurves;`
- L326 _private member_ `TSharedPtr<FUICommandList> UICommandList;` — Commands that are bound to delegates
- L333 _private member_ `FOnObjectsSelected OnObjectsSelected;` — Delegate called to select objects
- L336 _private member_ `TArray<TSharedPtr<TWeakObjectPtr<UPoseWatchPoseElement>>> PoseWatches;` — Names of each pose watch that can be selected
- L339 _private member_ `TSharedPtr<SComboBox<TSharedPtr<TWeakObjectPtr<UPoseWatchPoseElement>>>> PoseWatchCombo;` — Combobox used to select pose watch
- L341 _private member_ `TSharedPtr<SPoseWatchPicker> PoseWatchPicker;`
- L344 _private member_ `TArray<TSharedRef<FFilterBase<EAnimCurveViewerFilterFlags>>> Filters;` — All filters that can be applied to the widget's display

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Anim` (scope `UE`)
- L74 _typedef_ `typedef SListView< TSharedPtr<FDisplayedAnimCurveInfo> > SAnimCurveListType;`

### `Source/Editor/Persona/Private/SAnimEditorBase.h` (Private)


#### class `FTrackMarkerBar`  
`class FTrackMarkerBar`  
_L23-28_
- desc: Simple collection class to store data about a track marker (section, branch point etc)
- L26 _public member_ `float Time;`
- L27 _public member_ `FLinearColor DrawColour;`

#### class `SAnimEditorBase`  
`class SAnimEditorBase : public SCompoundWidget, public FGCObject`  
_L34-140_
- inherits: `SCompoundWidget,FGCObject`
- desc: Common functionality for all anim editor widgets
- L37 _public function_ `SLATE_BEGIN_ARGS(SAnimEditorBase) : _DisplayAnimTimeline(true) , _DisplayAnimScrubBar(false)`
- L42 _public prototype_ `SLATE_EVENT(FOnObjectsSelected, OnObjectsSelected) SLATE_ARGUMENT( bool, DisplayAnimTimeline ) SLATE_ARGUMENT( bool, DisplayAnimScrubBar ) SLATE_ARGUMENT( bool, DisplayAnimScrubBarEditing ) SLATE_ARGUMENT( TSharedPtr<FAnimModel>, AnimModel ) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<class IPersonaPreviewScene>& InPreviewScene);`
- L57 _public function_ `float GetViewMinInput() const` — Accessors to the current viewed Min/Max input range of the editor
- L58 _public function_ `float GetViewMaxInput() const`
- L61 _public function_ `float GetMinInput() const` — Accessors to the total Min/Max input range of the current object being edited
- L62 _public function_ `float GetMaxInput() const`
- L64 _public prototype_ `void SetInputViewRange(float InViewMinInput, float InViewMaxInput);`
- L67 _public prototype_ `void ScrollInputViewRange(float ScreenDelta, FVector2D ScreenViewSize);` — Scrolls the input view based on the supplied ScreenDelta
- L70 _public prototype_ `void OnSelectionChanged(const TArray<UObject*>& SelectedItems);` — Delegate when selection changed
- L73 _public prototype_ `float GetScrubValue() const;` — Get Current Scrub Value
- L76 _public prototype_ `UObject* ShowInDetailsView( UClass* EdClass );` — Creates an editor object from the given type to be used in a details panel
- L79 _public prototype_ `void ClearDetailsView();` — Clears the detail view of whatever we displayed last
- L82 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface start
- L83 _public function_ `virtual FString GetReferencerName() const override`
- L90 _public prototype_ `virtual TSharedRef<SWidget> CreateDocumentAnchor();` — Creates a anchor widget for each animation editor type
- L94 _protected member_ `TWeakPtr<IPersonaPreviewScene> PreviewScenePtr;` — Preview scene reference
- L96 _protected function_ `TSharedRef<IPersonaPreviewScene> GetPreviewScene() const`
- L99 _protected prototype_ `virtual TSharedRef<SWidget> ConstructAnimScrubPanel(bool bDisplayAnimScrubBarEditing);` — Allows derived classes to create different animation scrub panel
- L102 _protected function_ `virtual void InitDetailsViewEditorObject(class UEditorAnimBaseObj* EdObj)` — Allows derived classes to init newly created editor objects
- L105 _protected prototype_ `float GetSequenceLength() const;` — Get the length of the current sequence
- L108 _protected prototype_ `virtual UAnimationAsset* GetEditorObject() const = 0;` — Get the sequence that is currently being edited
- L111 _protected prototype_ `FText GetEditorObjectName() const;` — Get Name of Object being edited
- L114 _protected member_ `float ViewMinInput;` — Get Min/Max Input of value
- L115 _protected member_ `float ViewMaxInput;`
- L118 _protected prototype_ `class UAnimSingleNodeInstance* GetPreviewInstance() const;` — To get scrub value, get preview instance
- L121 _protected member_ `TSharedPtr<SVerticalBox> EditorPanels;` — The slate container that the editor panels are placed in
- L124 _protected member_ `TSharedPtr<SVerticalBox> NonScrollEditorPanels;` — Slate container used to add controls that are not embedded in a scroll box
- L127 _protected member_ `TSharedPtr<class SAnimationScrubPanel> AnimScrubPanel;` — The editors Animation Scrub Panel
- L130 _protected member_ `FEditorObjectTracker EditorObjectTracker;` — Tracks objects created for the details panel
- L133 _protected member_ `FOnObjectsSelected OnObjectsSelected;` — Delegate called to select objects
- L136 _protected member_ `TSharedPtr<SAnimTimeline> TimelineWidget;` — The timeline widget
- L139 _private prototype_ `float GetPercentageInternal() const;`

### `Source/Editor/Persona/Private/SAnimMontagePanel.h` (Private)


#### class `SAnimMontagePanel`  
`class SAnimMontagePanel : public SAnimTrackPanel, public FEditorUndoClient`  
_L40-293_
- inherits: `SAnimTrackPanel,FEditorUndoClient`
- L43 _public function_ `SLATE_BEGIN_ARGS( SAnimMontagePanel ) : _Montage() , _CurrentPosition() , _ViewInputMin() , _ViewInputMax() , _InputMin() , _InputMax() , _OnSetInputViewRange() , _OnGetScrubValue() , _OnMontageChange() , _OnInvokeTab() , _bChildAnimMontage(false)`
- L57 _public prototype_ `SLATE_ARGUMENT( class UAnimMontage*, Montage) SLATE_ARGUMENT( float, WidgetWidth ) SLATE_ATTRIBUTE( float, CurrentPosition ) SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax ) SLATE_ATTRIBUTE( float, InputMin ) SLATE_ATTRIBUTE( float, InputMax ) SLATE_ATTRIBUTE(EVisibility, SectionTimingNodeVisibility) SLATE_EVENT( FOnSetInputViewRange, OnSetInputViewRange ) SLATE_EVENT( FOnGetScrubValue, OnGetScrubValue ) SLATE_EVENT( FOnAnimObjectChange, OnMontageChange ) SLATE_EVENT( FOnInvokeTab, OnInvokeTab ) SLATE_EVENT(FOnMontageSetPreviewSlot, OnSetMontagePreviewSlot) SLATE_ARGUMENT(bool, bChildAnimMontage) SLATE_END_ARGS() ~SAnimMontagePanel();`
- L75 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FAnimModel_AnimMontage>& InModel);`
- L78 _public prototype_ `void OnSetMontagePreviewSlot(int32 SlotIndex);` — Handler for when the preview slot is changed
- L81 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;` — SWidget interface
- L83 _public prototype_ `void RestartPreview();`
- L84 _public prototype_ `void RestartPreviewFromSection(int32 FromSectionIdx = INDEX_NONE);`
- L85 _public prototype_ `void RestartPreviewPlayAllSections();`
- L88 _public prototype_ `void Update();` — This is the main function that creates the UI widgets for the montage tool.
- L91 _public prototype_ `void SummonTrackContextMenu( FMenuBuilder& MenuBuilder, float DataPosX, int32 SectionIndex, int32 AnimSlotIndex );` — Functions used as delegates that build the context menus for the montage tracks
- L92 _public prototype_ `void SummonSectionContextMenu( FMenuBuilder& MenuBuilder, int32 SectionIndex );`
- L93 _public prototype_ `void FillElementSubMenuForTimes( FMenuBuilder& MenuBuilder );`
- L94 _public prototype_ `void FillSlotSubMenu( FMenuBuilder& Menubuilder );`
- L96 _public prototype_ `void BuildNewSlotMenu(FMenuBuilder& InMenuBuilder);`
- L97 _public prototype_ `void CreateNewSlot(FName InName);`
- L98 _public prototype_ `bool CanCreateNewSlot(FName InName) const;`
- L100 _public prototype_ `void OnNewSectionClicked(float DataPosX);`
- L101 _public prototype_ `bool CanAddNewSection();`
- L103 _public prototype_ `void ShowSegmentInDetailsView(int32 AnimSegmentIndex, int32 AnimSlotIndex);`
- L104 _public prototype_ `void ShowSectionInDetailsView(int32 SectionIndex);`
- L106 _public prototype_ `void ClearSelected();`
- L109 _public prototype_ `void CheckSlotName(const FText& SlotName, int32 SlotNodeIndex, bool bShouldCheckCollapsed = false) const;` — helper method to check whether the slot name is empty or not. If empty, shows an error message to provide a valid name
- L112 _public prototype_ `void OnSlotNameChanged(const FText& NewText, int32 SlotNodeIndex);` — check the slot name whether valid or not while the user is typing
- L115 _public prototype_ `FText GetMontageSlotName(int32 SlotIndex) const;` — get slot name from a montage editor and check the slot name whether valid or not
- L118 _public prototype_ `bool IsSlotPreviewed(int32 SlotIndex) const;` — Handlers for preview slot checkbox UI
- L119 _public prototype_ `void OnSlotPreviewedChanged(int32 SlotIndex);`
- L122 _public prototype_ `void OnSetElementsToLinkMode(EAnimLinkMethod::Type NewLinkMethod);` — Context menu callback to set all elements in the montage to a given link method
- L125 _public prototype_ `void CollectLinkableElements(TArray<FAnimLinkableElement*>& Elements);` — Fills the given array with all linkable elements in the montage
- L128 _public prototype_ `void OnSetElementsToSlot(int32 SlotIndex);` — Context menu callback to set all elements in the montage to a given slot
- L131 _public prototype_ `void RefreshTimingNodes();` — Clears the name track of timing nodes and rebuilds them
- L134 _public prototype_ `void SortSections();` — Sort Composite Sections by Start Time
- L137 _public prototype_ `void EnsureStartingSection();` — Ensure there is at least one section in the montage and that the first section starts at T=0.f
- L140 _public prototype_ `void EnsureSlotNode();` — Ensure there is at least one slot node track
- L143 _public prototype_ `void SortAnimSegments();` — Sort Segments by starting time
- L145 _public prototype_ `void SortAndUpdateMontage();`
- L146 _public prototype_ `void CollapseMontage();`
- L148 _public prototype_ `bool ClampToEndTime(float NewEndTime);`
- L151 _public prototype_ `virtual void PostUndo( bool bSuccess ) override;` — FEditorUndoClient interface
- L152 _public prototype_ `virtual void PostRedo( bool bSuccess ) override;`
- L154 _public prototype_ `void PostRedoUndo();`
- L156 _public prototype_ `bool GetSectionTime( int32 SectionIndex, float &OutTime ) const;`
- L158 _public prototype_ `bool ValidIndexes(int32 AnimSlotIndex, int32 AnimSegmentIndex) const;`
- L159 _public prototype_ `bool ValidSection(int32 SectionIndex) const;`
- L162 _public prototype_ `void RefreshNotifyTriggerOffsets();` — Updates Notify trigger offsets to take into account current montage state
- L165 _public prototype_ `void HandleNotifiesChanged();` — Handle notifies changing, so we rebuild timing
- L168 _public prototype_ `EActiveTimerReturnType TriggerRebuildMontagePanel(double InCurrentTime, float InDeltaTime);` — One-off active timer to trigger a montage panel rebuild
- L171 _public prototype_ `void RebuildMontagePanel(bool bNotifyAsset=true);` — Rebuilds the montage panel
- L173 _public prototype_ `UAnimPreviewInstance* GetPreviewInstance() const;`
- L175 _public prototype_ `bool OnIsAnimAssetValid(const UAnimSequenceBase* AnimSequenceBase, FText* OutReason);`
- L179 _public prototype_ `void OnMontageChange(class UObject *EditorAnimBaseObj, bool Rebuild);` — These are meant to be callbacks used by the montage editing UI widgets
- L181 _public prototype_ `void SetSectionTime(int32 SectionIndex, float NewTime);`
- L183 _public prototype_ `TArray<float> GetSectionStartTimes() const;`
- L184 _public prototype_ `TArray<FTrackMarkerBar> GetMarkerBarInformation() const;`
- L185 _public prototype_ `TArray<FString> GetSectionNames() const;`
- L186 _public prototype_ `TArray<float> GetAnimSegmentStartTimes() const;`
- L188 _public prototype_ `void AddNewSection(float StartTime, FString SectionName);`
- L189 _public prototype_ `void RemoveSection(int32 SectionIndex);`
- L190 _public prototype_ `FString GetSectionName(int32 SectionIndex) const;`
- L192 _public prototype_ `void RenameSlotNode(int32 SlotIndex, FString NewSlotName);`
- L195 _public prototype_ `void AddNewMontageSlot(FName NewSlotName);` — UI Slot Action handlers
- L196 _public prototype_ `void RemoveMontageSlot(int32 AnimSlotIndex);`
- L197 _public prototype_ `bool CanRemoveMontageSlot(int32 AnimSlotIndex);`
- L198 _public prototype_ `void DuplicateMontageSlot(int32 AnimSlotIndex);`
- L200 _public prototype_ `void MakeDefaultSequentialSections();`
- L201 _public prototype_ `void ClearSquenceOrdering();`
- L204 _public prototype_ `void PreAnimUpdate();` — Delegete handlers for when the editor UI is changing the montage
- L205 _public prototype_ `void PostAnimUpdate();`
- L206 _public prototype_ `void OnMontageModified();`
- L207 _public prototype_ `void ReplaceAnimationMapping(FName SlotName, int32 SegmentIdx, UAnimSequenceBase* OldSequenceBase, UAnimSequenceBase* NewSequenceBase);`
- L208 _public prototype_ `bool IsDiffererentFromParent(FName SlotName, int32 SegmentIdx, const FAnimSegment& Segment);`
- L211 _public member_ `FSimpleDelegate OnSectionsChanged;` — Delegate fired when montage sections have changed
- L213 _public prototype_ `FReply OnFindParentClassInContentBrowserClicked();`
- L214 _public prototype_ `FReply OnEditParentClassClicked();`
- L216 _public prototype_ `void HandleObjectsSelected(const TArray<UObject*>& InObjects);`
- L218 _public prototype_ `void OnOpenAnimSlotManager();`
- L221 _private member_ `TWeakPtr<FAnimModel_AnimMontage> WeakModel;`
- L222 _private member_ `TSharedPtr<SBorder> PanelArea;`
- L223 _private member_ `class UAnimMontage* Montage;`
- L224 _private member_ `TAttribute<float> CurrentPosition;`
- L226 _private member_ `TArray<TSharedPtr<class SMontageEdTrack>> TrackList;`
- L228 _private member_ `FString LastContextHeading;`
- L230 _private member_ `STrackNodeSelectionSet SelectionSet;`
- L232 _private member_ `TArray< TSharedPtr< class STextComboBox> > SlotNameComboBoxes;`
- L233 _private member_ `TArray< FName > SlotNameComboSelectedNames;`
- L235 _private member_ `TArray< TSharedPtr< FString > > SlotNameComboListItems;`
- L236 _private member_ `TArray< FName > SlotNameList;`
- L238 _private member_ `TArray< TSharedPtr<SImage> > SlotWarningImages;`
- L240 _private member_ `TSharedPtr<STrack> SectionNameTrack;`
- L241 _private member_ `TAttribute<EVisibility> SectionTimingNodeVisibility;`
- L244 _private member_ `int32 CurrentPreviewSlot;` — Member data to allow use to set preview slot from editor
- L247 _private member_ `int32 PreviewingStartSectionIdx;` — If previewing section, it is section used to restart previewing when play button is pushed
- L250 _private member_ `bool bIsSelecting;` — Recursion guard for selection
- L253 _private member_ `bool bPreviewingAllSections : 1;` — If currently previewing all or selected section
- L256 _private member_ `bool bPreviewingTracks : 1;` — If currently previewing tracks instead of sections
- L259 _private member_ `bool bIsActiveTimerRegistered : 1;` — If the active timer to trigger a montage panel rebuild is currently registered
- L266 _private member_ `bool bChildAnimMontage : 1;` — Child Anim Montage: Child Anim Montage only can replace name of animations, and no other meaningful edits as it will derive every data from Parent. There might be some other data that will allow to be replaced, but for now, it is not.
- L271 _private member_ `TSharedPtr<STextBlock> StatusBarTextBlock;` — /
- L272 _private member_ `TSharedPtr<SImage> StatusBarWarningImage;`
- L274 _private prototype_ `void OnSlotNameChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, int32 AnimSlotIndex);`
- L275 _private prototype_ `void OnSlotListOpening(int32 AnimSlotIndex);`
- L277 _private prototype_ `void RefreshComboLists(bool bOnlyRefreshIfDifferent = false);`
- L279 _private prototype_ `void CreateNewSlot(const FText& NewSlotName, ETextCommit::Type CommitInfo);`
- L280 _private prototype_ `void CreateNewSection(const FText& NewSectionName, ETextCommit::Type CommitInfo, float StartTime);`
- L285 _private prototype_ `void OnAnimSegmentRemoved(int32 SegmentIndex, int32 SlotIndex);` — Called when a segment is removed from a track, so we can adjust the indices in linkable elements @param SegmentIndex - Index of the removed segment
- L289 _private prototype_ `virtual float GetSequenceLength() const override;` — Gets the length of the montage we are currently editing
- L292 _private member_ `FOnInvokeTab OnInvokeTab;` — Delegate used to invoke a tab in the containing editor

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DELEGATE( FOnMontageLengthChange ) DECLARE_DELEGATE( FOnMontagePropertyChanged ) DECLARE_DELEGATE_OneParam( FOnMontageSetPreviewSlot, int32)`
- L27 _delegate_ `DECLARE_DELEGATE( FOnMontagePropertyChanged ) DECLARE_DELEGATE_OneParam( FOnMontageSetPreviewSlot, int32)`
- L28 _delegate_ `DECLARE_DELEGATE_OneParam( FOnMontageSetPreviewSlot, int32)`

### `Source/Editor/Persona/Private/SAnimMontageScrubPanel.h` (Private)


#### class `SAnimMontageScrubPanel`  
`class SAnimMontageScrubPanel : public SAnimationScrubPanel`  
_L12-57_
- inherits: `SAnimationScrubPanel`
- L16 _public function_ `SLATE_BEGIN_ARGS(SAnimMontageScrubPanel) : _MontageEditor() , _LockedSequence()`
- L20 _public prototype_ `SLATE_ARGUMENT( TWeakPtr<class SMontageEditor>, MontageEditor) SLATE_ARGUMENT(UAnimSequenceBase*, LockedSequence) SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax ) SLATE_EVENT( FOnSetInputViewRange, OnSetInputViewRange ) SLATE_EVENT( FOnCropAnimSequence, OnCropAnimSequence ) SLATE_EVENT( FSimpleDelegate, OnReZeroAnimSequence ) SLATE_ARGUMENT( bool, bAllowZoom ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<IPersonaPreviewScene>& InPreviewScene );`
- L42 _protected prototype_ `virtual FReply OnClick_Backward_End() override;` — notifiers
- L43 _protected prototype_ `virtual FReply OnClick_Forward_End() override;`
- L45 _protected prototype_ `virtual FReply OnClick_Backward_Step() override;`
- L46 _protected prototype_ `virtual FReply OnClick_Forward_Step() override;`
- L48 _protected prototype_ `virtual FReply OnClick_Forward() override;`
- L49 _protected prototype_ `virtual FReply OnClick_Backward() override;`
- L51 _protected prototype_ `virtual FReply OnClick_ToggleLoop() override;`
- L53 _protected prototype_ `virtual void OnValueChanged(float NewValue, bool bFireNotifies = true) override;`
- L56 _private member_ `TWeakPtr<SMontageEditor> MontageEditor;`

### `Source/Editor/Persona/Private/SAnimMontageSectionsPanel.h` (Private)


#### struct `FAnimMontageSectionsSummoner`  
`struct FAnimMontageSectionsSummoner : public FWorkflowTabFactory`  
_L24-35_
- inherits: `FWorkflowTabFactory`
- L27 _public prototype_ `FAnimMontageSectionsSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, const TSharedRef<class IPersonaToolkit>& InPersonaToolkit, FSimpleMulticastDelegate& InOnSectionsChanged);`
- L29 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L30 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L33 _public member_ `TWeakPtr<class IPersonaToolkit> PersonaToolkit;`
- L34 _public member_ `FSimpleMulticastDelegate& OnSectionsChanged;`

#### class `SAnimMontageSectionsPanel`  
`class SAnimMontageSectionsPanel : public SCompoundWidget, public FEditorUndoClient`  
_L37-106_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L40 _public function_ `SLATE_BEGIN_ARGS( SAnimMontageSectionsPanel )`
- L45 _public prototype_ `~SAnimMontageSectionsPanel();`
- L48 _public function_ `virtual void PostUndo(bool bSuccess)` — FEditorUndoClient interface
- L49 _public function_ `virtual void PostRedo(bool bSuccess)`
- L51 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<IPersonaToolkit>& InPersonaToolkit, FSimpleMulticastDelegate& InOnSectionsChanged);`
- L54 _public prototype_ `void Update();` — Rebuild panel widgets
- L59 _public prototype_ `void SetNextSectionIndex(int32 SectionIdx, int32 NextSecitonIdx);` — Callback when a section in the upper display is clicked @param SectionIdx - Section that was clicked @param NextSecitonIdx - Section to set as the next section
- L63 _public prototype_ `void RemoveLink(int32 SectionIndex);` — Unlinks the requested section @param SectionIndex - Section to unlink
- L67 _public prototype_ `FReply MakeDefaultSequence();` — Set section to play sequentially (default behavior)
- L69 _public prototype_ `FReply ClearSequence();` — Completely remove section sequence data
- L72 _public prototype_ `FReply PreviewAllSectionsClicked();` — Starts playing from the first section
- L75 _public prototype_ `FReply PreviewSectionClicked(int32 SectionIndex);` — Plays the clicked section @param SectionIndex - Section to play
- L80 _private prototype_ `TSharedRef<SWidget> OnGetSectionMenuContent(int32 SectionIdx);` — Shows the context menu for a section
- L83 _private prototype_ `void RestartPreview();` — Restarts the preview animation
- L86 _private prototype_ `void RestartPreviewPlayAllSections();` — Restarts the preview animation playing all sections
- L89 _private prototype_ `void RestartPreviewFromSection(int32 FromSectionIdx);` — Restarts the preview animation from the specified sections
- L91 _private prototype_ `void SortSections();`
- L93 _private prototype_ `void MakeDefaultSequentialSections();`
- L95 _private prototype_ `void ClearSequenceOrdering();`
- L99 _private prototype_ `bool IsLoop(int32 SectionIdx);` — Returns whether or not the provided section is part of a loop @param SectionIdx - Section to check
- L102 _private member_ `TSharedPtr<SBorder> PanelArea;` — Main panel area widget
- L105 _private member_ `TWeakPtr<IPersonaToolkit> WeakPersonaToolkit;` — Persona toolkit we are hosted in

### `Source/Editor/Persona/Private/SAnimNotifyPanel.h` (Private)


#### enum `ENotifyPasteMode::Type`  
`enum Type`  
_L53-57_
- L55 _public enumerator_ `MousePosition`
- L56 _public enumerator_ `OriginalTime`

#### enum `ENotifyPasteMultipleMode::Type`  
`enum Type`  
_L62-66_
- L64 _public enumerator_ `Relative`
- L65 _public enumerator_ `Absolute`

#### struct `FNotifyMarqueeOperation`  
`struct FNotifyMarqueeOperation`  
_L69-131_
- L71 _public function_ `FNotifyMarqueeOperation() : Operation(Add) , bActive(false)`
- L85 _public member_ `} Operation;`
- L87 _public function_ `bool IsValid() const`
- L92 _public function_ `void Start(const FVector2D& InStartLocation, FNotifyMarqueeOperation::Type InOperationType, TArray<TSharedPtr<SAnimNotifyNode>>& InOriginalSelection)`
- L99 _public function_ `void End()`
- L106 _public function_ `static FNotifyMarqueeOperation::Type OperationTypeFromMouseEvent(const FPointerEvent& MouseEvent)` — Given a mouse event, figure out what the marquee selection should do based on the state of Shift and Ctrl keys
- L124 _public member_ `FMarqueeRect Rect;` — The marquee rectangle being dragged by the user
- L127 _public member_ `bool bActive;` — Whether the marquee has been activated, usually by a drag
- L130 _public member_ `TArray<TSharedPtr<SAnimNotifyNode>> OriginalSelection;` — The original selection state before the marquee selection

#### enum `FNotifyMarqueeOperation::Type`  
`enum Type`  
_L77-85_
- L80 _public enumerator_ `Remove` — Holding down Ctrl removes nodes
- L82 _public enumerator_ `Add` — Holding down Shift adds to the selection
- L84 _public enumerator_ `Replace` — When nothing is pressed, marquee replaces selection

#### class `FAnimNotifyPanelCommands`  
`class FAnimNotifyPanelCommands : public TCommands<FAnimNotifyPanelCommands>`  
_L139-157_
- inherits: `TCommands<FAnimNotifyPanelCommands>`
- L142 _public function_ `FAnimNotifyPanelCommands() : TCommands<FAnimNotifyPanelCommands>("AnimNotifyPanel", NSLOCTEXT("Contexts", "AnimNotifyPanel", "Anim Notify Panel"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L148 _public member_ `TSharedPtr<FUICommandInfo> DeleteNotify;`
- L150 _public member_ `TSharedPtr<FUICommandInfo> CopyNotifies;`
- L152 _public member_ `TSharedPtr<FUICommandInfo> CutNotifies;`
- L154 _public member_ `TSharedPtr<FUICommandInfo> PasteNotifies;`
- L156 _public prototype_ `virtual void RegisterCommands() override;`

#### class `SAnimNotifyPanel`  
`class SAnimNotifyPanel: public SAnimTrackPanel, public FEditorUndoClient`  
_L161-382_
- inherits: `SAnimTrackPanel,FEditorUndoClient`
- desc: @todo anim : register when it's opened for the animsequence broadcast when animsequence changed, so that we refresh for multiple window
- L164 _public function_ `SLATE_BEGIN_ARGS( SAnimNotifyPanel ) : _Sequence() , _CurrentPosition() , _ViewInputMin() , _ViewInputMax() , _InputMin() , _InputMax() , _OnSetInputViewRange() , _OnSelectionChanged() , _OnGetScrubValue() , _OnRequestRefreshOffsets()`
- L177 _public prototype_ `SLATE_ARGUMENT( class UAnimSequenceBase*, Sequence) SLATE_ARGUMENT( float, WidgetWidth ) SLATE_ATTRIBUTE( float, CurrentPosition ) SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax ) SLATE_ATTRIBUTE( float, InputMin ) SLATE_ATTRIBUTE( float, InputMax ) SLATE_EVENT( FOnSetInputViewRange, OnSetInputViewRange ) SLATE_EVENT( FOnSelectionChanged, OnSelectionChanged ) SLATE_EVENT( FOnGetScrubValue, OnGetScrubValue ) SLATE_EVENT( FRefreshOffsetsRequest, OnRequestRefreshOffsets ) SLATE_EVENT( FOnGetTimingNodeVisibility, OnGetTimingNodeVisibility ) SLATE_EVENT( FOnInvokeTab, OnInvokeTab ) SLATE_EVENT( FSimpleDelegate, OnNotifiesChanged ) SLATE_EVENT( FOnSnapPosition, OnSnapPosition ) SLATE_EVENT( FOnNotifyStateHandleBeingDragged, OnNotifyStateHandleBeingDragged) SLATE_EVENT( FOnNotifyNodesBeingDragged, OnNotifyNodesBeingDragged) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FAnimModel>& InModel);`
- L198 _public prototype_ `virtual ~SAnimNotifyPanel();`
- L200 _public prototype_ `void SetSequence(class UAnimSequenceBase * InSequence);`
- L203 _public prototype_ `FName GetNewTrackName() const;` — Generate a new track name (smallest integer number that isn't currently used)
- L205 _public prototype_ `FReply AddTrack();`
- L206 _public prototype_ `FReply InsertTrack(int32 TrackIndexToInsert);`
- L207 _public prototype_ `FReply DeleteTrack(int32 TrackIndexToDelete);`
- L208 _public prototype_ `bool CanDeleteTrack(int32 TrackIndexToDelete);`
- L211 _public prototype_ `void OnCommitTrackName(const FText& InText, ETextCommit::Type CommitInfo, int32 TrackIndexToName);` — Handler function for renaming a notify track
- L214 _public prototype_ `void RequestUpdate();` — Request a deferred Update call
- L216 _public prototype_ `void Update();`
- L219 _public prototype_ `float CalculateDraggedNodePos() const;` — Returns the position of the notify node currently being dragged. Returns -1 if no node is being dragged
- L222 _public prototype_ `FReply OnNotifyNodeDragStarted(TArray<TSharedPtr<SAnimNotifyNode>> NotifyNodes, TSharedRef<SWidget> Decorator, const FVector2D& ScreenCursorPos, const FVector2D& ScreenNodePosition, const bool bDragOnMarker);` — Handler for when a notify node drag has been initiated
- L224 _public prototype_ `virtual float GetSequenceLength() const override;`
- L226 _public prototype_ `void CutSelectedNodesToClipboard();`
- L228 _public prototype_ `void CopySelectedNodesToClipboard() const;`
- L229 _public prototype_ `void OnPasteNodes(SAnimNotifyTrack* RequestTrack, float ClickTime, ENotifyPasteMode::Type PasteMode, ENotifyPasteMultipleMode::Type MultiplePasteType);`
- L232 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget Interface
- L233 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L234 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L235 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L236 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L237 _public prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L238 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L239 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L242 _public prototype_ `void RefreshMarqueeSelectedNodes(const FGeometry& PanelGeo);`
- L244 _public prototype_ `void OnNotifyObjectChanged(UObject* EditorBaseObj, bool bRebuild);`
- L247 _public prototype_ `bool IsNotifySelectionValidForReplacement();` — Check to make sure the current AnimNotify selection is a valid selection for replacing (i.e., AnimNotifies and AnimNotifyStates aren't mixed together in the selection)
- L250 _public prototype_ `void OnReplaceSelectedWithNotify(FString NewNotifyName, UClass* NewNotifyClass);` — Handler for replacing with notify
- L253 _public prototype_ `void OnReplaceSelectedWithNotifyBlueprint(FString NewBlueprintNotifyName, FString NewBlueprintNotifyClass);` — Handler for replacing with notify blueprint
- L256 _public prototype_ `void OnReplaceSelectedWithSyncMarker(FString NewBlueprintNotifyName);` — Handler for replacing with sync marker
- L258 _public prototype_ `void HandleObjectsSelected(const TArray<UObject*>& InObjects);`
- L260 _public function_ `TSharedRef<FUICommandList> GetCommandList() const`
- L265 _private member_ `TWeakPtr<FAnimModel> WeakModel;`
- L266 _private member_ `TSharedPtr<SBorder> PanelArea;`
- L267 _private member_ `TSharedPtr<SScrollBar> NotifyTrackScrollBar;`
- L268 _private member_ `class UAnimSequenceBase* Sequence;`
- L269 _private member_ `float WidgetWidth;`
- L270 _private member_ `TAttribute<float> CurrentPosition;`
- L271 _private member_ `FOnSelectionChanged OnSelectionChanged;`
- L272 _private member_ `FOnGetScrubValue OnGetScrubValue;`
- L273 _private member_ `FOnGetTimingNodeVisibility OnGetTimingNodeVisibility;`
- L276 _private member_ `FNotifyMarqueeOperation Marquee;` — Manager for mouse controlled marquee selection
- L279 _private member_ `FRefreshOffsetsRequest OnRequestRefreshOffsets;` — Delegate to request a refresh of the offsets calculated for notifies
- L282 _private member_ `float CurrentDragXPosition;` — Store the position of a currently dragged node for display across tracks
- L285 _private member_ `TArray<TSharedPtr<SAnimNotifyTrack>> NotifyAnimTracks;` — Cached list of anim tracks for notify node drag drop
- L288 _private member_ `TArray<TSharedPtr<SNotifyEdTrack>> NotifyEditorTracks;` — Cached list of Notify editor tracks
- L291 _private prototype_ `void RequestRefresh();` — Request a deferred RefreshNotifyTracks call
- L295 _private prototype_ `void RefreshNotifyTracks();` — this just refresh notify tracks - UI purpose only do not call this from here. This gets called by asset.
- L298 _private prototype_ `virtual void PostUndo( bool bSuccess ) override;` — FEditorUndoClient interface
- L299 _private prototype_ `virtual void PostRedo( bool bSuccess ) override;`
- L302 _private prototype_ `void OnDeletePressed();` — Handler for delete command
- L305 _private prototype_ `void DeleteSelectedNodeObjects();` — Deletes all currently selected notifies in the panel
- L308 _private function_ `virtual bool SupportsKeyboardFocus() const override` — We support keyboard focus to detect when we should process key commands like delete
- L314 _private prototype_ `void OnTrackSelectionChanged();` — Called when a track changes it's selection; iterates all tracks collecting selected items
- L317 _private prototype_ `void DeselectAllNotifies();` — Called to deselect all notifies across all tracks
- L320 _private prototype_ `void BindCommands();` — Binds the UI commands for this widget to delegates
- L326 _private prototype_ `void PopulateNotifyBlueprintClasses(TArray<FString>& InOutAllowedClasses);` — Populates the given class array with all classes deriving from those originally present @param InAssetsToSearch Assets to search to detect child classes @param InOutAllowedClassNames Classes to allow, this will be expanded to cover all derived classes of those originally present
- L332 _private prototype_ `void OnGetNotifyBlueprintData(TArray<FAssetData>& OutNotifyData, TArray<FString>* InOutAllowedClassNames);` — Find blueprints matching allowed classes and all derived blueprints @param OutNotifyData Asset data matching allowed classes and their children @param InOutAllowedClassNames Classes to allow, this will be expanded to cover all derived classes of those originally present
- L340 _private prototype_ `void OnGetNativeNotifyData(TArray<UClass*>& OutClasses, UClass* NotifyOutermost, TArray<FString>* OutAllowedBlueprintClassNames);` — Find classes that inherit from NotifyOutermost and add correctly formatted class name to OutAllowedBlueprintClassNames to allow us to find blueprints inherited from those types without loading the blueprints. @param OutClasses Array of classes that inherit from NotifyOutermost @param NotifyOutermost Outermost notify class to detect children of @param OutAllowedBlueprintClassNames list of class names to add the native class names to
- L342 _private prototype_ `void OnNotifyTrackScrolled(float InScrollOffsetFraction);`
- L344 _private prototype_ `virtual void InputViewRangeChanged(float ViewMin, float ViewMax) override;`
- L347 _private member_ `FOnSnapPosition OnSnapPosition;` — Delegate used to snap when dragging
- L350 _private member_ `TSharedPtr<FUICommandList> CommandList;` — UI commands for this widget
- L353 _private member_ `TArray<FString> NotifyClassNames;` — Classes that are known to be derived from blueprint notifies
- L356 _private member_ `TArray<FString> NotifyStateClassNames;` — Classes that are known to be derived from blueprint state notifies
- L359 _private member_ `FDelegateHandle OnPropertyChangedHandleDelegateHandle;` — Handle to the registered OnPropertyChangedHandle delegate
- L362 _private member_ `FOnInvokeTab OnInvokeTab;` — Delegate used to invoke a tab
- L365 _private member_ `FSimpleDelegate OnNotifiesChanged;` — Delegate used to inform others that notifies have changed (for timing)
- L368 _private member_ `FOnNotifyStateHandleBeingDragged OnNotifyStateHandleBeingDragged;` — Delegate used to inform others that a notify state handle is being dragged
- L371 _private member_ `FOnNotifyNodesBeingDragged OnNotifyNodesBeingDragged;` — Delegate used to inform others that one or more notifies nodes are being dragged
- L374 _private member_ `bool bIsSelecting;` — Recursion guard for selection
- L377 _private member_ `bool bIsUpdating;` — Recursion guard for updating
- L380 _private member_ `bool bUpdateRequested;` — Flags to handle deferred updates
- L381 _private member_ `bool bRefreshRequested;`

#### Free symbols / members of external scopes

- L33 _delegate_ `DECLARE_DELEGATE_OneParam( FOnSelectionChanged, const TArray<UObject*>& ) DECLARE_DELEGATE_RetVal( float, FOnGetScrubValue ) DECLARE_DELEGATE( FRefreshOffsetsRequest ) DECLARE_DELEGATE( FDeleteNotify ) DECLARE_DELEGATE_RetVal( bool, FOnGetIsAnimNotifySelectionValidForReplacement ) DECLARE_DELEGATE_TwoParams( FReplaceWithNotify, FString, UClass* ) DECLARE_DELEGATE_TwoParams( FReplaceWithBlueprintNotify, FString, FString ) DECLARE_DELEGATE_OneParam( FReplaceWithSyncMarker, FString ) DECLARE_DELEGATE( FDeselectAllNotifies ) DECLARE_DELEGATE_OneParam( FOnGetBlueprintNotifyData, TArray<FAssetData>& ) DECLARE_DELEGATE_OneParam( FOnGetNativeNotifyClasses, TArray<UClass*>&) class SAnimNotifyNode;`
- L34 _delegate_ `DECLARE_DELEGATE_RetVal( float, FOnGetScrubValue ) DECLARE_DELEGATE( FRefreshOffsetsRequest ) DECLARE_DELEGATE( FDeleteNotify ) DECLARE_DELEGATE_RetVal( bool, FOnGetIsAnimNotifySelectionValidForReplacement ) DECLARE_DELEGATE_TwoParams( FReplaceWithNotify, FString, UClass* ) DECLARE_DELEGATE_TwoParams( FReplaceWithBlueprintNotify, FString, FString ) DECLARE_DELEGATE_OneParam( FReplaceWithSyncMarker, FString ) DECLARE_DELEGATE( FDeselectAllNotifies ) DECLARE_DELEGATE_OneParam( FOnGetBlueprintNotifyData, TArray<FAssetData>& ) DECLARE_DELEGATE_OneParam( FOnGetNativeNotifyClasses, TArray<UClass*>&) class SAnimNotifyNode;`
- L35 _delegate_ `DECLARE_DELEGATE( FRefreshOffsetsRequest ) DECLARE_DELEGATE( FDeleteNotify ) DECLARE_DELEGATE_RetVal( bool, FOnGetIsAnimNotifySelectionValidForReplacement ) DECLARE_DELEGATE_TwoParams( FReplaceWithNotify, FString, UClass* ) DECLARE_DELEGATE_TwoParams( FReplaceWithBlueprintNotify, FString, FString ) DECLARE_DELEGATE_OneParam( FReplaceWithSyncMarker, FString ) DECLARE_DELEGATE( FDeselectAllNotifies ) DECLARE_DELEGATE_OneParam( FOnGetBlueprintNotifyData, TArray<FAssetData>& ) DECLARE_DELEGATE_OneParam( FOnGetNativeNotifyClasses, TArray<UClass*>&) class SAnimNotifyNode;`
- L36 _delegate_ `DECLARE_DELEGATE( FDeleteNotify ) DECLARE_DELEGATE_RetVal( bool, FOnGetIsAnimNotifySelectionValidForReplacement ) DECLARE_DELEGATE_TwoParams( FReplaceWithNotify, FString, UClass* ) DECLARE_DELEGATE_TwoParams( FReplaceWithBlueprintNotify, FString, FString ) DECLARE_DELEGATE_OneParam( FReplaceWithSyncMarker, FString ) DECLARE_DELEGATE( FDeselectAllNotifies ) DECLARE_DELEGATE_OneParam( FOnGetBlueprintNotifyData, TArray<FAssetData>& ) DECLARE_DELEGATE_OneParam( FOnGetNativeNotifyClasses, TArray<UClass*>&) class SAnimNotifyNode;`
- L37 _delegate_ `DECLARE_DELEGATE_RetVal( bool, FOnGetIsAnimNotifySelectionValidForReplacement ) DECLARE_DELEGATE_TwoParams( FReplaceWithNotify, FString, UClass* ) DECLARE_DELEGATE_TwoParams( FReplaceWithBlueprintNotify, FString, FString ) DECLARE_DELEGATE_OneParam( FReplaceWithSyncMarker, FString ) DECLARE_DELEGATE( FDeselectAllNotifies ) DECLARE_DELEGATE_OneParam( FOnGetBlueprintNotifyData, TArray<FAssetData>& ) DECLARE_DELEGATE_OneParam( FOnGetNativeNotifyClasses, TArray<UClass*>&) class SAnimNotifyNode;`
- L38 _delegate_ `DECLARE_DELEGATE_TwoParams( FReplaceWithNotify, FString, UClass* ) DECLARE_DELEGATE_TwoParams( FReplaceWithBlueprintNotify, FString, FString ) DECLARE_DELEGATE_OneParam( FReplaceWithSyncMarker, FString ) DECLARE_DELEGATE( FDeselectAllNotifies ) DECLARE_DELEGATE_OneParam( FOnGetBlueprintNotifyData, TArray<FAssetData>& ) DECLARE_DELEGATE_OneParam( FOnGetNativeNotifyClasses, TArray<UClass*>&) class SAnimNotifyNode;`
- L39 _delegate_ `DECLARE_DELEGATE_TwoParams( FReplaceWithBlueprintNotify, FString, FString ) DECLARE_DELEGATE_OneParam( FReplaceWithSyncMarker, FString ) DECLARE_DELEGATE( FDeselectAllNotifies ) DECLARE_DELEGATE_OneParam( FOnGetBlueprintNotifyData, TArray<FAssetData>& ) DECLARE_DELEGATE_OneParam( FOnGetNativeNotifyClasses, TArray<UClass*>&) class SAnimNotifyNode;`
- L40 _delegate_ `DECLARE_DELEGATE_OneParam( FReplaceWithSyncMarker, FString ) DECLARE_DELEGATE( FDeselectAllNotifies ) DECLARE_DELEGATE_OneParam( FOnGetBlueprintNotifyData, TArray<FAssetData>& ) DECLARE_DELEGATE_OneParam( FOnGetNativeNotifyClasses, TArray<UClass*>&) class SAnimNotifyNode;`
- L41 _delegate_ `DECLARE_DELEGATE( FDeselectAllNotifies ) DECLARE_DELEGATE_OneParam( FOnGetBlueprintNotifyData, TArray<FAssetData>& ) DECLARE_DELEGATE_OneParam( FOnGetNativeNotifyClasses, TArray<UClass*>&) class SAnimNotifyNode;`
- L42 _delegate_ `DECLARE_DELEGATE_OneParam( FOnGetBlueprintNotifyData, TArray<FAssetData>& ) DECLARE_DELEGATE_OneParam( FOnGetNativeNotifyClasses, TArray<UClass*>&) class SAnimNotifyNode;`
- L43 _delegate_ `DECLARE_DELEGATE_OneParam( FOnGetNativeNotifyClasses, TArray<UClass*>&) class SAnimNotifyNode;`
- L51 _namespace_ `namespace ENotifyPasteMode`
- L60 _namespace_ `namespace ENotifyPasteMultipleMode`

### `Source/Editor/Persona/Private/SAnimPlusMinusSlider.h` (Private)


#### class `SAnimPlusMinusSlider`  
`class SAnimPlusMinusSlider : public SCompoundWidget`  
_L16-122_
- inherits: `SCompoundWidget`
- desc: Utility widget to set-up a common style for -/+ sliders in Persona
- L21 _public function_ `SLATE_BEGIN_ARGS(SAnimPlusMinusSlider) : _ExtraWidget()`
- L26 _public function_ `SLATE_ARGUMENT (FText, Label) SLATE_EVENT( FOnClicked, OnMinusClicked ) SLATE_ARGUMENT( FText, MinusTooltip) SLATE_ATTRIBUTE( float, SliderValue ) SLATE_EVENT( FOnFloatValueChanged, OnSliderValueChanged ) SLATE_ARGUMENT( FText, SliderTooltip ) SLATE_EVENT( FOnClicked, OnPlusClicked ) SLATE_ARGUMENT( FText, PlusTooltip) SLATE_ARGUMENT( TSharedPtr<SWidget>, ExtraWidget ) SLATE_END_ARGS() void Construct(const FArguments& InArgs )` — The label to use on the widget

### `Source/Editor/Persona/Private/SAnimSegmentsPanel.h` (Private)


#### class `FAnimSegmentsPanelCommands`  
`class FAnimSegmentsPanelCommands : public TCommands < FAnimSegmentsPanelCommands >`  
_L36-48_
- inherits: `TCommands<FAnimSegmentsPanelCommands>`
- desc: UI Commands
- L39 _public function_ `FAnimSegmentsPanelCommands() : TCommands<FAnimSegmentsPanelCommands>("AnimMontagePanel", NSLOCTEXT("Contexts", "AnimMontagePanel", "Anim Montage Panel"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L45 _public member_ `TSharedPtr<FUICommandInfo> DeleteSegment;`
- L47 _public prototype_ `virtual void RegisterCommands() override;`

#### class `SAnimSegmentsPanel`  
`class SAnimSegmentsPanel: public SCompoundWidget`  
_L51-187_
- inherits: `SCompoundWidget`
- desc: TODO: comment about segment panel
- L54 _public function_ `SLATE_BEGIN_ARGS( SAnimSegmentsPanel ) : _AnimTrack(NULL) , _ViewInputMin() , _ViewInputMax() , _bChildAnimMontage(false)`
- L61 _public prototype_ `SLATE_ARGUMENT(struct FAnimTrack*, AnimTrack) SLATE_ARGUMENT(FName, SlotName) SLATE_ARGUMENT(STrackNodeSelectionSet *, NodeSelectionSet) SLATE_ARGUMENT(TSharedPtr<FTrackColorTracker>, ColorTracker) SLATE_ATTRIBUTE(float, ViewInputMin) SLATE_ATTRIBUTE(float, ViewInputMax) SLATE_EVENT(FOnGetNodeColor, OnGetNodeColor) SLATE_ATTRIBUTE(TArray<float>, DraggableBars) SLATE_ATTRIBUTE(TArray<float>, DraggableBarSnapPositions) SLATE_ATTRIBUTE(float, ScrubPosition) SLATE_ATTRIBUTE(float, TrackMaxValue) SLATE_ATTRIBUTE(int32, TrackNumDiscreteValues) SLATE_EVENT(FOnAnimSegmentNodeClicked, OnAnimSegmentNodeClicked) SLATE_EVENT(FOnAnimSegmentNodeDoubleClicked, OnAnimSegmentNodeDoubleClicked) SLATE_EVENT(FOnPreAnimUpdate, OnPreAnimUpdate) SLATE_EVENT(FOnPostAnimUpdate, OnPostAnimUpdate) SLATE_EVENT(FOnAnimSegmentRemoved, OnAnimSegmentRemoved) SLATE_EVENT(FOnAnimReplaceMapping, OnAnimReplaceMapping) SLATE_EVENT(FOnDiffFromParentAsset, OnDiffFromParentAsset) SLATE_EVENT(FIsAnimAssetValid, OnIsAnimAssetValid) SLATE_EVENT( FOnBarDrag, OnBarDrag) SLATE_EVENT( FOnBarDrop, OnBarDrop) SLATE_EVENT( FOnBarClicked, OnBarClicked) SLATE_EVENT( FOnTrackRightClickContextMenu, OnTrackRightClickContextMenu) SLATE_ARGUMENT(bool, bChildAnimMontage) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L97 _public function_ `bool SupportsKeyboardFocus() const override` — We support keyboard focus to receive UI key events
- L100 _public prototype_ `FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — Key handler
- L104 _private member_ `FOnPreAnimUpdate OnPreAnimUpdateDelegate;`
- L105 _private member_ `FOnPostAnimUpdate OnPostAnimUpdateDelegate;`
- L106 _private member_ `FOnAnimSegmentNodeClicked OnAnimSegmentNodeClickedDelegate;`
- L107 _private member_ `FOnAnimSegmentNodeDoubleClicked OnAnimSegmentNodeDoubleClickedDelegate;`
- L108 _private member_ `FOnAnimSegmentRemoved OnAnimSegmentRemovedDelegate;`
- L109 _private member_ `FOnAnimReplaceMapping OnAnimReplaceMapping;`
- L110 _private member_ `FOnDiffFromParentAsset OnDiffFromParentAsset;`
- L111 _private member_ `FOnGetNodeColor OnGetNodeColor;`
- L120 _private prototype_ `bool ValidIndex(int32 AnimSegmentIndex) const;`
- L121 _private prototype_ `FLinearColor GetNodeColor(int32 AnimSegmentIndex) const;`
- L122 _private prototype_ `float GetSegmentLength(int32 AnimSegmentIndex) const;`
- L123 _private prototype_ `float GetSegmentStartPos(int32 AnimSegmentIndex) const;`
- L124 _private prototype_ `FString GetAnimSegmentName(int32 AnimSegmentIndex) const;`
- L125 _private prototype_ `FText GetAnimSegmentDetailedInfo(int32 AnimSegmentIndex) const;`
- L127 _private prototype_ `void SetSegmentStartPos(float NewStartPos, int32 AnimSegmentIndex);`
- L128 _private prototype_ `void OnSegmentDropped(int32 AnimSegmentIndex);`
- L130 _private prototype_ `void ShowSegmentInDetailsView(int32 AnimSlotIndex, int32 AnimSegmentIndex);`
- L132 _private prototype_ `void SummonSegmentNodeContextMenu( FMenuBuilder& MenuBuilder, int32 AnimSegmentIndex );`
- L134 _private prototype_ `void AddAnimSegment(UAnimSequenceBase *NewSequenceBase, float NewStartPos );`
- L135 _private prototype_ `bool IsValidToAdd(UAnimSequenceBase* NewSequenceBase, FText* OutReason = nullptr) const;`
- L136 _private prototype_ `void OnTrackDragDrop( TSharedPtr<FDragDropOperation> DragDropOp, float DataPos );`
- L137 _private prototype_ `bool OnAssetDragDrop(TSharedPtr<FAssetDragDropOp> AssetDragDropOp);`
- L138 _private prototype_ `void OnAnimSegmentNodeClicked(int32 SegmentIdx);`
- L139 _private prototype_ `void OnAnimSegmentNodeDoubleClicked(int32 SegmentIdx);`
- L142 _private prototype_ `void ReplaceAnimSegment(UAnimSequenceBase* NewSequenceBase, float NewStartPos);` — child anim montage
- L143 _private prototype_ `void ReplaceAnimSegment(int32 AnimSegmentIndex, UAnimSequenceBase* NewSequenceBase);`
- L144 _private prototype_ `void ReplaceAnimSegment(const FAssetData& NewSequenceData, int32 AnimSegmentIndex);`
- L145 _private prototype_ `bool ShouldFilter(const FAssetData& DataToDisplay, USkeleton* InSkeleton, bool bInFilterAdditive, TEnumAsByte<EAdditiveAnimationType> InAdditiveType);`
- L148 _private prototype_ `void RemoveSelectedAnimSegments();` — Remove all selected anim segments in all segment tracks
- L151 _private prototype_ `void RemoveAnimSegment(int32 AnimSegmentIndex);` — Remove the specified anim segment
- L152 _private prototype_ `void RevertToParent(int32 AnimSegmentIndex);`
- L153 _private prototype_ `void OpenAsset(int32 AnimSegmentIndex);`
- L154 _private prototype_ `void ResetSegmentLength(int32 AnimSegmentIndex);`
- L155 _private prototype_ `void FillSubMenu(FMenuBuilder& MenuBuilder, int32 AnimSegmentIndex);`
- L158 _private prototype_ `void BindCommands();` — Bind UI commands for this widget
- L160 _private member_ `ETrackViewStyle TrackStyle;`
- L162 _private member_ `TAttribute<float> ViewInputMin;`
- L163 _private member_ `TAttribute<float> ViewInputMax;`
- L166 _private member_ `struct FAnimTrack* AnimTrack;` — Anim Track
- L168 _private member_ `FName SlotName;` — Slot name, used when bChildAnimMontage == true
- L170 _private member_ `bool bDragging;`
- L173 _private member_ `TSharedPtr<FUICommandList> UICommandList;` — List of UI commands for this widget
- L176 _private member_ `TArray<TSharedPtr<STrack>> TrackWidgets;` — List of widgets representing tracks
- L178 _private member_ `TAttribute<FLinearColor> DefaultNodeColor;`
- L180 _private member_ `FIsAnimAssetValid OnIsAnimAssetValid;`
- L186 _private member_ `bool bChildAnimMontage;` — Child Anim Montage: Child Anim Montage only can replace name of animations, and no other meaningful edits as it will derive every data from Parent. There might be some other data that will allow to be replaced, but for now, it is not.

#### enum `SAnimSegmentsPanel::ETrackViewStyle`  
`enum ETrackViewStyle`  
_L113-118_
- L115 _public enumerator_ `TRACK_Single`
- L116 _public enumerator_ `TRACK_Double`
- L117 _public enumerator_ `TRACK_ExpandAll`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE( FOnPreAnimUpdate ) DECLARE_DELEGATE( FOnPostAnimUpdate ) DECLARE_DELEGATE_OneParam( FOnAnimSegmentNodeClicked, int32 ) DECLARE_DELEGATE_OneParam( FOnAnimSegmentNodeDoubleClicked, int32) DECLARE_DELEGATE_OneParam( FOnAnimSegmentRemoved, int32 ) DECLARE_DELEGATE_FourParams( FOnAnimReplaceMapping, FName, int32, UAnimSequenceBase*, UAnimSequenceBase*) DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnDiffFromParentAsset, FName, int32, const FAnimSegment& ) DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FOnGetNodeColor, const FAnimSegment&)`
- L24 _delegate_ `DECLARE_DELEGATE( FOnPostAnimUpdate ) DECLARE_DELEGATE_OneParam( FOnAnimSegmentNodeClicked, int32 ) DECLARE_DELEGATE_OneParam( FOnAnimSegmentNodeDoubleClicked, int32) DECLARE_DELEGATE_OneParam( FOnAnimSegmentRemoved, int32 ) DECLARE_DELEGATE_FourParams( FOnAnimReplaceMapping, FName, int32, UAnimSequenceBase*, UAnimSequenceBase*) DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnDiffFromParentAsset, FName, int32, const FAnimSegment& ) DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FOnGetNodeColor, const FAnimSegment&)`
- L25 _delegate_ `DECLARE_DELEGATE_OneParam( FOnAnimSegmentNodeClicked, int32 ) DECLARE_DELEGATE_OneParam( FOnAnimSegmentNodeDoubleClicked, int32) DECLARE_DELEGATE_OneParam( FOnAnimSegmentRemoved, int32 ) DECLARE_DELEGATE_FourParams( FOnAnimReplaceMapping, FName, int32, UAnimSequenceBase*, UAnimSequenceBase*) DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnDiffFromParentAsset, FName, int32, const FAnimSegment& ) DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FOnGetNodeColor, const FAnimSegment&)`
- L26 _delegate_ `DECLARE_DELEGATE_OneParam( FOnAnimSegmentNodeDoubleClicked, int32) DECLARE_DELEGATE_OneParam( FOnAnimSegmentRemoved, int32 ) DECLARE_DELEGATE_FourParams( FOnAnimReplaceMapping, FName, int32, UAnimSequenceBase*, UAnimSequenceBase*) DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnDiffFromParentAsset, FName, int32, const FAnimSegment& ) DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FOnGetNodeColor, const FAnimSegment&)`
- L27 _delegate_ `DECLARE_DELEGATE_OneParam( FOnAnimSegmentRemoved, int32 ) DECLARE_DELEGATE_FourParams( FOnAnimReplaceMapping, FName, int32, UAnimSequenceBase*, UAnimSequenceBase*) DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnDiffFromParentAsset, FName, int32, const FAnimSegment& ) DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FOnGetNodeColor, const FAnimSegment&)`
- L28 _delegate_ `DECLARE_DELEGATE_FourParams( FOnAnimReplaceMapping, FName, int32, UAnimSequenceBase*, UAnimSequenceBase*) DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnDiffFromParentAsset, FName, int32, const FAnimSegment& ) DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FOnGetNodeColor, const FAnimSegment&)`
- L29 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnDiffFromParentAsset, FName, int32, const FAnimSegment& ) DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FOnGetNodeColor, const FAnimSegment&)`
- L30 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FLinearColor, FOnGetNodeColor, const FAnimSegment&)`

### `Source/Editor/Persona/Private/SAnimSequenceCurveEditor.h` (Private)


#### class `FRichCurveEditorModelNamed`  
`class FRichCurveEditorModelNamed : public FRichCurveEditorModel`  
_L23-54_
- inherits: `FRichCurveEditorModel`
- desc: Model that references a named curve, rather than a raw pointer, so we avoid issues with reallocation of the curves arrays under the UI
- L26 _public prototype_ `FRichCurveEditorModelNamed(const FName& InName, ERawCurveTrackTypes InType, int32 InCurveIndex, UAnimSequenceBase* InAnimSequence, FCurveEditorTreeItemID InTreeId = FCurveEditorTreeItemID());`
- L28 _public prototype_ `virtual ~FRichCurveEditorModelNamed();`
- L30 _public prototype_ `virtual bool IsValid() const override;`
- L31 _public prototype_ `virtual FRichCurve& GetRichCurve() override;`
- L32 _public prototype_ `virtual const FRichCurve& GetReadOnlyRichCurve() const override;`
- L34 _public prototype_ `virtual void SetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions, EPropertyChangeType::Type ChangeType) override;`
- L35 _public prototype_ `virtual void SetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyAttributes> InAttributes, EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified) override;`
- L36 _public prototype_ `virtual void SetCurveAttributes(const FCurveAttributes& InCurveAttributes) override;`
- L38 _public prototype_ `void CurveHasChanged();`
- L39 _public prototype_ `void OnModelHasChanged(const EAnimDataModelNotifyType& NotifyType, IAnimationDataModel* Model, const FAnimDataModelNotifPayload& Payload);`
- L40 _public prototype_ `void UpdateCachedCurve();`
- L42 _public member_ `FName CurveName;`
- L43 _public member_ `TWeakObjectPtr<UAnimSequenceBase> AnimSequence;`
- L44 _public member_ `int32 CurveIndex;`
- L45 _public member_ `ERawCurveTrackTypes Type;`
- L46 _public member_ `FCurveEditorTreeItemID TreeId;`
- L48 _public member_ `FAnimationCurveIdentifier CurveId;`
- L49 _public member_ `UE::Anim::FAnimDataModelNotifyCollector NotifyCollector;`
- L50 _public member_ `FRichCurve CachedCurve;`
- L51 _public member_ `bool bCurveRemoved;`
- L53 _public member_ `TUniquePtr<IAnimationDataController::FScopedBracket> InteractiveBracket;`

#### class `SAnimSequenceCurveEditor`  
`class SAnimSequenceCurveEditor : public IAnimSequenceCurveEditor`  
_L56-98_
- inherits: `IAnimSequenceCurveEditor`
- L58 _private function_ `SLATE_BEGIN_ARGS(SAnimSequenceCurveEditor)`
- L60 _private prototype_ `SLATE_ARGUMENT(TSharedPtr<ITimeSliderController>, ExternalTimeSliderController) SLATE_ARGUMENT(TSharedPtr<FTabManager>, TabManager) SLATE_END_ARGS() ~SAnimSequenceCurveEditor();`
- L68 _private prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<IPersonaPreviewScene>& InPreviewScene, UAnimSequenceBase* InAnimSequence);`
- L71 _private prototype_ `virtual void ResetCurves() override;` — IAnimSequenceCurveEditor interface
- L72 _private prototype_ `virtual void AddCurve(const FText& InCurveDisplayName, const FLinearColor& InCurveColor, const FName& InName, ERawCurveTrackTypes InType, int32 InCurveIndex, FSimpleDelegate InOnCurveModified) override;`
- L73 _private prototype_ `virtual void RemoveCurve(const FName& InName, ERawCurveTrackTypes InType, int32 InCurveIndex) override;`
- L74 _private prototype_ `virtual void ZoomToFit() override;`
- L75 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L77 _private prototype_ `void OnModelHasChanged(const EAnimDataModelNotifyType& NotifyType, IAnimationDataModel* Model, const FAnimDataModelNotifPayload& Payload);`
- L80 _private prototype_ `TSharedRef<SWidget> MakeToolbar(TSharedRef<SCurveEditorPanel> InEditorPanel);` — Build the toolbar for this curve editor
- L81 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L85 _private member_ `TSharedPtr<FCurveEditor> CurveEditor;` — The actual curve editor
- L88 _private member_ `TSharedPtr<SWidget> CurveEditorSearchBox;` — The search widget for filtering curves in the Curve Editor tree.
- L91 _private member_ `UAnimSequenceBase* AnimSequence;` — The anim sequence we are editing
- L94 _private member_ `TSharedPtr<SCurveEditorTree> CurveEditorTree;` — The tree widget in the curve editor
- L97 _private member_ `TArray<FAnimationCurveIdentifier> CurvesToRemove;` — Curves to be removed from editing on the next ::Tick

### `Source/Editor/Persona/Private/SAnimStreamableEditor.h` (Private)


#### class `SAnimStreamableEditor`  
`class SAnimStreamableEditor : public SAnimEditorBase, public FEditorUndoClient`  
_L19-60_
- inherits: `SAnimEditorBase,FEditorUndoClient`
- desc: Overall streamable animation editing widget. This mostly contains functions for editing the UAnimStreamable.
- L22 _public function_ `SLATE_BEGIN_ARGS( SAnimStreamableEditor ) : _StreamableAnim(nullptr)`
- L34 _private member_ `TSharedPtr<FAnimModel_AnimSequenceBase> AnimModel;`
- L37 _public prototype_ `~SAnimStreamableEditor();`
- L39 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene, const TSharedRef<class IEditableSkeleton>& InEditableSkeleton, const TSharedRef<FUICommandList>& InCommandList);`
- L42 _public function_ `UAnimStreamable* GetStreamableAnim() const` — Return the streamable animation being edited
- L43 _public function_ `virtual UAnimationAsset* GetEditorObject() const override`
- L47 _private member_ `UAnimStreamable* StreamableAnim;` — Pointer to the streamable animation being edited
- L51 _public prototype_ `virtual TSharedRef<SWidget> CreateDocumentAnchor() override;`
- L55 _public prototype_ `virtual void PostUndo( bool bSuccess ) override;` — FEditorUndoClient interface
- L56 _public prototype_ `virtual void PostRedo( bool bSuccess ) override;`
- L59 _public prototype_ `void PostUndoRedo();` — Post undo

### `Source/Editor/Persona/Private/SAnimTimingPanel.h` (Private)


#### struct `FTimingRelevantElement_Notify`  
`struct FTimingRelevantElement_Notify : public FTimingRelevantElementBase`  
_L24-34_
- inherits: `FTimingRelevantElementBase`
- desc: Small helper to store information about timing relevant elements (notifies, branch points, sections etc.)
- L26 _public member_ `UAnimSequenceBase* Sequence;` — The sequence the notify exists within
- L27 _public member_ `int32 NotifyIndex;` — The index of the notify in the sequence
- L29 _public prototype_ `virtual FName GetTypeName() override;`
- L30 _public prototype_ `virtual float GetElementTime() const override;`
- L31 _public prototype_ `virtual int32 GetElementSortPriority() const override;`
- L32 _public prototype_ `virtual ENotifyTimingElementType::Type GetType() override;`
- L33 _public prototype_ `virtual void GetDescriptionItems(TMap<FString, FText>& Items) override;`

#### struct `FTimingRelevantElement_NotifyStateEnd`  
`struct FTimingRelevantElement_NotifyStateEnd : public FTimingRelevantElement_Notify`  
_L37-42_
- inherits: `FTimingRelevantElement_Notify`
- desc: Small helper to store information about timing relevant elements (notifies, branch points, sections etc.)
- L39 _public prototype_ `virtual FName GetTypeName() override;`
- L40 _public prototype_ `virtual float GetElementTime() const override;`
- L41 _public prototype_ `virtual ENotifyTimingElementType::Type GetType() override;`

#### struct `FTimingRelevantElement_Section`  
`struct FTimingRelevantElement_Section : public FTimingRelevantElementBase`  
_L44-53_
- inherits: `FTimingRelevantElementBase`
- L46 _public member_ `UAnimMontage* Montage;` — The montage the section exists within
- L47 _public member_ `int32 SectionIdx;` — The index of the section in the montage
- L49 _public prototype_ `virtual FName GetTypeName() override;`
- L50 _public prototype_ `virtual float GetElementTime() const override;`
- L51 _public prototype_ `virtual ENotifyTimingElementType::Type GetType() override;`
- L52 _public prototype_ `virtual void GetDescriptionItems(TMap<FString, FText>& Items) override;`

#### class `SAnimTimingTrackNode`  
`class SAnimTimingTrackNode : public STrackNode`  
_L63-82_
- inherits: `STrackNode`
- L66 _public function_ `SLATE_BEGIN_ARGS(SAnimTimingTrackNode) : _bUseTooltip(true)`
- L70 _public prototype_ `SLATE_ATTRIBUTE(float, ViewInputMin) SLATE_ATTRIBUTE(float, ViewInputMax) SLATE_ATTRIBUTE(float, DataStartPos) SLATE_ATTRIBUTE(FString, NodeName) SLATE_ATTRIBUTE(FLinearColor, NodeColor) SLATE_ARGUMENT(TSharedPtr<FTimingRelevantElementBase>, Element) SLATE_ARGUMENT(bool, bUseTooltip) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

#### class `SAnimTimingPanel`  
`class SAnimTimingPanel : public SAnimTrackPanel`  
_L88-154_
- inherits: `SAnimTrackPanel`
- L92 _public function_ `SLATE_BEGIN_ARGS(SAnimTimingPanel) : _InSequence(nullptr) , _WidgetWidth(0) , _CurrentPosition(0) , _ViewInputMin(0) , _ViewInputMax(0) , _InputMin(0) , _InputMax(0) , _OnSetInputViewRange()`
- L103 _public prototype_ `SLATE_ARGUMENT(UAnimSequenceBase*, InSequence) SLATE_ARGUMENT(float, WidgetWidth) SLATE_ATTRIBUTE(float, CurrentPosition) SLATE_ATTRIBUTE(float, ViewInputMin) SLATE_ATTRIBUTE(float, ViewInputMax) SLATE_ATTRIBUTE(float, InputMin) SLATE_ATTRIBUTE(float, InputMax) SLATE_EVENT(FOnSetInputViewRange, OnSetInputViewRange) SLATE_END_ARGS()`
- L119 _public prototype_ `void Update();` — Updates panel widgets
- L123 _public prototype_ `bool IsElementDisplayEnabled(ENotifyTimingElementType::Type ElementType) const;` — Access to display enabled flags in multiple forms
- L124 _public prototype_ `ECheckBoxState IsElementDisplayChecked(ENotifyTimingElementType::Type ElementType) const;`
- L125 _public prototype_ `EVisibility IsElementDisplayVisible(ENotifyTimingElementType::Type ElementType) const;`
- L129 _public prototype_ `void OnElementDisplayEnabledChanged(ENotifyTimingElementType::Type ElementType);` — Callback from slate when element display flag changes @param ElementType - Flag to set
- L134 _public prototype_ `static void GetTimingRelevantElements(UAnimSequenceBase* Sequence, TArray<TSharedPtr<FTimingRelevantElementBase>>& Elements);` — Inspects the provided sequence, collect and sorts the requested elements @param Sequence - Sequence to inspect @param Elements - Out array of elements
- L139 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Tick the panel state
- L142 _protected prototype_ `void RefreshTrackNodes();` — Clears the timing track and rebuilds the nodes
- L145 _protected member_ `TWeakPtr<FAnimModel_AnimMontage> WeakModel;` — The model for our data
- L147 _protected member_ `TArray<TSharedPtr<FTimingRelevantElementBase>> Elements;` — Observed timing elements
- L149 _protected member_ `UAnimSequenceBase* AnimSequence;` — Anim sequence that contains the timing elements we are observing
- L151 _protected member_ `TSharedPtr<SBorder> PanelArea;` — Main panel widget
- L153 _protected member_ `TSharedPtr<STrack> Track;` — The track to place timing nodes on

#### Free symbols / members of external scopes

- L56 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(EVisibility, FOnGetTimingNodeVisibility, ENotifyTimingElementType::Type)` — Delegate to get the visibility of a type of timing node on an external panel (not the timing track)

### `Source/Editor/Persona/Private/SAnimTrackPanel.h` (Private)


#### class `FTrackColorTracker`  
`class FTrackColorTracker`  
_L22-48_
- L25 _public function_ `FTrackColorTracker() : CurrentColor(0)`
- L31 _public function_ `void AddColor(FLinearColor NewColor)` — Add a colour to our list of colour options
- L37 _public function_ `FLinearColor GetNextColor()` — return the next track colour to use from our list, looping if necessary
- L46 _private member_ `TArray<FLinearColor> Colors;`
- L47 _private member_ `int32 CurrentColor;`

#### class `S2ColumnWidget`  
`class S2ColumnWidget : public SCompoundWidget`  
_L54-70_
- inherits: `SCompoundWidget`
- desc: S2ColumnWidget Widget for drawing any number of widgets in 2 columns, useful for track layout
- L61 _public member_ `TSharedPtr<SVerticalBox> LeftColumn;`
- L62 _public member_ `TSharedPtr<SVerticalBox> RightColumn;`
- L64 _public function_ `SLATE_BEGIN_ARGS( S2ColumnWidget )`
- L66 _public prototype_ `SLATE_ARGUMENT( float, WidgetWidth ) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

#### enum `S2ColumnWidget::EDefaultColumnWidth`  
`enum EDefaultColumnWidth`  
_L57-60_
- L59 _public enumerator_ `DEFAULT_RIGHT_COLUMN_WIDTH = 176`

#### class `SAnimTrackPanel`  
`class SAnimTrackPanel: public SCompoundWidget`  
_L75-119_
- inherits: `SCompoundWidget`
- L78 _public function_ `SLATE_BEGIN_ARGS( SAnimTrackPanel ) : _ViewInputMin() , _ViewInputMax() , _InputMin() , _InputMax() , _OnSetInputViewRange()`
- L86 _public prototype_ `SLATE_ARGUMENT( float, WidgetWidth ) SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax ) SLATE_ATTRIBUTE( float, InputMin ) SLATE_ATTRIBUTE( float, InputMax ) SLATE_EVENT( FOnSetInputViewRange, OnSetInputViewRange ) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L97 _public prototype_ `void PanInputViewRange(int32 ScreenDelta, FVector2D ScreenViewSize);` — `UE_DEPRECATED(5.6, "Use the helper function accepting FVector2f instead of FVector2D")`
- L98 _public prototype_ `void PanInputViewRange(int32 ScreenDelta, FVector2f ScreenViewSize);`
- L100 _public function_ `virtual float GetSequenceLength() const`
- L106 _protected prototype_ `virtual void InputViewRangeChanged(float ViewMin, float ViewMax);` — Calls out to notify of a range change, can be overridden by derived classes to respond but they must call this version too after processing range changes
- L109 _protected prototype_ `TSharedRef<class S2ColumnWidget> Create2ColumnWidget( TSharedRef<SVerticalBox> Parent );` — Create a 2 column widget
- L111 _protected member_ `TAttribute<float> ViewInputMin;`
- L112 _protected member_ `TAttribute<float> ViewInputMax;`
- L113 _protected member_ `TAttribute<float> InputMin;`
- L114 _protected member_ `TAttribute<float> InputMax;`
- L115 _protected member_ `FOnSetInputViewRange OnSetInputViewRange;`
- L118 _protected member_ `float WidgetWidth;` — Controls the width of the tracks column

### `Source/Editor/Persona/Private/SAnimationBlendSpace.h` (Private)


#### class `SBlendSpaceEditor`  
`class SBlendSpaceEditor : public SAnimEditorBase, public FNotifyHook, public FSelfRegisteringEditorUndoClient`  
_L20-129_
- inherits: `SAnimEditorBase,FNotifyHook,FSelfRegisteringEditorUndoClient`
- L23 _public function_ `SLATE_BEGIN_ARGS(SBlendSpaceEditor) : _BlendSpace(nullptr) , _DisplayScrubBar(true) , _StatusBarName(TEXT("AssetEditor.AnimationEditor.MainMenu"))`
- L28 _public prototype_ `SLATE_ARGUMENT(UBlendSpace*, BlendSpace) SLATE_ARGUMENT(bool, DisplayScrubBar) SLATE_EVENT(FOnBlendSpaceNavigateUp, OnBlendSpaceNavigateUp) SLATE_EVENT(FOnBlendSpaceNavigateDown, OnBlendSpaceNavigateDown) SLATE_EVENT(FOnBlendSpaceCanvasDoubleClicked, OnBlendSpaceCanvasDoubleClicked) SLATE_EVENT(FOnBlendSpaceSampleDoubleClicked, OnBlendSpaceSampleDoubleClicked) SLATE_EVENT(FOnBlendSpaceSampleAdded, OnBlendSpaceSampleAdded) SLATE_EVENT(FOnBlendSpaceSampleDuplicated, OnBlendSpaceSampleDuplicated) SLATE_EVENT(FOnBlendSpaceSampleRemoved, OnBlendSpaceSampleRemoved) SLATE_EVENT(FOnBlendSpaceSampleReplaced, OnBlendSpaceSampleReplaced) SLATE_EVENT(FOnGetBlendSpaceSampleName, OnGetBlendSpaceSampleName) SLATE_EVENT(FOnExtendBlendSpaceSampleTooltip, OnExtendSampleTooltip) SLATE_EVENT(FOnSetBlendSpacePreviewPosition, OnSetPreviewPosition) SLATE_ATTRIBUTE(FVector, PreviewPosition) SLATE_ATTRIBUTE(FVector, PreviewFilteredPosition) SLATE_ARGUMENT(FName, StatusBarName) SLATE_END_ARGS() ~SBlendSpaceEditor();`
- L48 _public prototype_ `void Construct(const FArguments& InArgs);`
- L50 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene);`
- L53 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L57 _public prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L58 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`
- L62 _protected prototype_ `void OnSampleMoved(const int32 SampleIndex, const FVector& NewValue, bool bIsInteractive);`
- L63 _protected prototype_ `void OnSampleRemoved(const int32 SampleIndex);`
- L64 _protected prototype_ `int32 OnSampleAdded(UAnimSequence* Animation, const FVector& Value, bool bRunAnalysis);`
- L65 _protected prototype_ `void OnSampleDuplicated(const int32 SampleIndex, const FVector& NewValue, bool bRunAnalysis);`
- L66 _protected prototype_ `void OnSampleReplaced(const int32 SampleIndex, UAnimSequence* Animation);`
- L69 _protected function_ `virtual UAnimationAsset* GetEditorObject() const override`
- L73 _protected function_ `virtual void PostUndo(bool bSuccess) override` — FSelfRegisteringEditorUndoClient interface
- L74 _protected function_ `virtual void PostRedo(bool bSuccess) override`
- L77 _protected prototype_ `void PostUndoRedo();` — Delegate which is called when the Editor has performed an undo operation
- L80 _protected prototype_ `void UpdatePreviewParameter() const;` — Updates Persona's preview window
- L83 _protected prototype_ `void UpdateFromBlendSpaceState() const;` — Updates Persona's preview window with additional data that should always be shown.
- L86 _protected prototype_ `TSharedPtr<class IPersonaPreviewScene> GetPreviewScene() const;` — Retrieves the preview scene shown by Persona
- L89 _protected prototype_ `void OnPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);` — Global callback to anticipate on changes to the blend space
- L91 _protected prototype_ `void ResampleData();`
- L95 _protected member_ `UBlendSpace* BlendSpace;` — The blend space being edited
- L98 _protected member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScenePtr;` — The preview scene we are viewing
- L101 _protected member_ `TSharedPtr<class SBlendSpaceGridWidget> BlendSpaceGridWidget;` — Pointer to the grid widget which displays the blendspace visualization
- L104 _protected member_ `FCoreUObjectDelegates::FOnObjectPropertyChanged::FDelegate OnPropertyChangedHandle;` — Property changed delegate
- L107 _protected member_ `FDelegateHandle OnPropertyChangedHandleDelegateHandle;` — Handle to the registered OnPropertyChangedHandle delegate
- L110 _protected member_ `FOnBlendSpaceSampleAdded OnBlendSpaceSampleAdded;` — Delegate called when a sample is added
- L113 _protected member_ `FOnBlendSpaceSampleDuplicated OnBlendSpaceSampleDuplicated;` — Delegate called when a sample is duplicated
- L116 _protected member_ `FOnBlendSpaceSampleRemoved OnBlendSpaceSampleRemoved;` — Delegate called when a sample is removed
- L119 _protected member_ `FOnBlendSpaceSampleReplaced OnBlendSpaceSampleReplaced;` — Delegate called when a sample is replaced
- L122 _protected member_ `FOnSetBlendSpacePreviewPosition OnSetPreviewPosition;` — Delegate called to externally control the preview position
- L125 _protected member_ `bool bShouldSetPreviewPosition = true;` — Flag to check whether or not the preview value should be (re-)set on the next tick
- L128 _protected member_ `TUniquePtr<FScopedTransaction> SampleMoveTransaction;` — Cross-framed boundary scoped transaction, used for sticking to single transaction for interactive operations (dragging sample or spinbox)

### `Source/Editor/Persona/Private/SAnimationBlendSpaceGridWidget.h` (Private)


#### class `SBlendSpaceGridWidget`  
`class SBlendSpaceGridWidget : public SCompoundWidget, public FNotifyHook`  
_L29-406_
- inherits: `SCompoundWidget,FNotifyHook`
- L34 _public function_ `SLATE_BEGIN_ARGS(SBlendSpaceGridWidget) : _BlendSpaceBase(nullptr) , _NotifyHook(nullptr) , _ReadOnly(false) , _ShowAxisLabels(true) , _ShowSettingsButtons(true) , _StatusBarName(TEXT("AssetEditor.AnimationEditor.MainMenu"))`
- L91 _public prototype_ `~SBlendSpaceGridWidget();`
- L98 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget @param	InArgs	The declaration data for this widget
- L101 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget Interface
- L102 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L103 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L104 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L105 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L106 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L107 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L108 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L109 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L110 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L111 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L112 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L113 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L114 _public prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L115 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L116 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L120 _public prototype_ `const FVector GetPreviewPosition() const;` — Returns the sample value for previewing the blend space
- L123 _public prototype_ `void SetPreviewingState(const FVector& InPosition, const FVector& InFilteredPosition);` — Records the state of the blend space being used for previewing so it can be displayed
- L126 _public prototype_ `const bool IsPreviewing() const;` — Flag whether or not the user is actively previewing the blend space (moving the sample value)
- L128 _public function_ `int32 GetSelectedSampleIndex() const`
- L130 _public prototype_ `void InvalidateCachedData();`
- L131 _public prototype_ `void InvalidateState();`
- L134 _protected prototype_ `void PaintBackgroundAndGrid(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32& DrawLayerId) const;` — Drawing functionality for grid, legend, key and triangulation
- L135 _protected prototype_ `void PaintSampleKeys(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32& DrawLayerId) const;`
- L136 _protected prototype_ `void PaintAxisText(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32& DrawLayerId) const;`
- L137 _protected prototype_ `void PaintTriangulation(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32& DrawLayerId) const;`
- L138 _protected prototype_ `void PaintAnimationNames(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32& DrawLayerId) const;`
- L139 _protected prototype_ `void PaintGridSampleWeights(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32& DrawLayerId) const;`
- L142 _protected prototype_ `const bool IsValidDragDropOperation(const FDragDropEvent& DragDropEvent, FText& InvalidOperationText);` — Validation for drag and drop operation, will populate InvalidOperationText and return false in case it is invalid
- L145 _protected prototype_ `bool ValidateAnimationSequence(const UAnimSequence* AnimationSequence, FText& InvalidOperationText) const;` — Validation functionality for the given animation sequence, will populate InvalidOperationText and return false in case it is invalid
- L148 _protected prototype_ `void StartPreviewing();` — Preview toggling
- L149 _protected prototype_ `void StopPreviewing();`
- L152 _protected prototype_ `void MakeViewContextMenuEntries(FMenuBuilder& InMenuBuilder);` — Common view options for the context menus
- L155 _protected prototype_ `TSharedPtr<SWidget> CreateBlendSampleContextMenu();` — Blend sample context menu creation
- L158 _protected prototype_ `TSharedPtr<SWidget> CreateNewBlendSampleContextMenu(const FVector2D& InMousePosition);` — Create a new blend sample via the context menu
- L161 _protected prototype_ `TSharedPtr<SWidget> CreateGridEntryBox(const int32 BoxIndex, const bool bShowLabel);` — Construct the grid widget to change the grid position for the selected sample
- L164 _protected prototype_ `FReply ProcessClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Handles a mouse click operation on mouse up
- L166 _protected prototype_ `FReply ToggleTriangulationVisibility();` — Toggle for drawing the triangulation (only available for 2D blendspace)
- L168 _protected prototype_ `EVisibility GetTriangulationButtonVisibility() const;` — Returns whether or not the triangulation button should be visible, see above
- L170 _protected prototype_ `EVisibility GetAnimationNamesButtonVisibility() const;` — Returns whether or not the animation names button should be visible
- L172 _protected prototype_ `FReply ToggleFittingType();` — Toggle for how the grid area is determined (only available for 2D blendspace)
- L174 _protected prototype_ `EVisibility GetFittingButtonVisibility() const;` — Returns whether or not the fitting button should be visible
- L176 _protected prototype_ `void UpdateGridRatioMargin(const FVector2D& GeometrySize);` — Calculates a margin offset according to whether or not we should take into account the largest axis when creating the grid area
- L177 _protected prototype_ `FText GetFittingTypeButtonToolTipText() const;`
- L179 _protected prototype_ `FReply ToggleShowAnimationNames();` — Toggles the animation labels being shown
- L182 _protected prototype_ `void CalculateGridPoints();` — Calculates the screen space grid points
- L184 _protected prototype_ `const FVector2D SnapScreenPositionToGrid(const FVector2D& InPosition, bool ForceSnap) const;` — Snaps the given screen position to the closest grid point
- L186 _protected prototype_ `const FVector ScreenPositionToSampleValueWithSnapping(const FVector2D& InPosition, bool bForceSnap) const;` — Snaps the given screen position to the sample value on the grid
- L188 _protected prototype_ `int32 FindClosestGridPointIndexFromScreenPosition(const FVector2D& InPosition) const;` — Returns the index of the closest grid point to the given mouse position
- L190 _protected prototype_ `const FVector2D SampleValueToScreenPosition(const FVector& SampleValue) const;` — Converts the given sample value to a screen space position
- L192 _protected prototype_ `const FVector2D SampleValueToNormalizedPosition(const FVector& SampleValue) const;` — Converts the given sample value to a normalized position (between 0 and 1)
- L194 _protected prototype_ `const FVector ScreenPositionToSampleValue(const FVector2D& GridPosition, bool bClamp) const;` — Converts a screen space (grid) position to a sample value, with optional clamping
- L196 _protected prototype_ `const FSlateRect GetGridRectangleFromGeometry(const FGeometry& MyGeometry);` — Returns the (calculated) grid rectangle given the supplied geometry, and calls UpdateGridRatioMargin
- L198 _protected prototype_ `bool IsSampleValueWithinMouseRange(const FVector& SampleValue, float& OutDistance) const;` — Checks whether or not the blendspace sample value is within the range of the mouse position
- L200 _protected prototype_ `int32 GetClosestSamplePointIndexToMouse() const;` — Get the sample index that most closely corresponds to the mouse position
- L203 _protected prototype_ `void ShowToolTip();` — Sets the tooltip instance on the underlying widget instance
- L205 _protected prototype_ `void ResetToolTip();` — Resets the tooltip instance on the underlying widget instance to nullptr
- L207 _protected prototype_ `FText GetToolTipAnimationName() const;` — Tool tip text content getters
- L208 _protected prototype_ `FText GetToolTipSampleValue() const;`
- L209 _protected prototype_ `FText GetToolTipSampleValidity() const;`
- L210 _protected prototype_ `FText GetSampleErrorMessage(const struct FBlendSample& BlendSample) const;`
- L213 _protected prototype_ `EVisibility GetInputBoxVisibility(const int32 ParameterIndex) const;` — Functionality for the grid input box widgets (also used by FBlendSampleDetails)
- L214 _protected prototype_ `TOptional<float> GetInputBoxValue(const int32 ParameterIndex) const;`
- L215 _protected prototype_ `TOptional<float> GetInputBoxMinValue(const int32 ParameterIndex) const;`
- L216 _protected prototype_ `TOptional<float> GetInputBoxMaxValue(const int32 ParameterIndex) const;`
- L217 _protected prototype_ `float GetInputBoxDelta(const int32 ParameterIndex) const;`
- L218 _protected prototype_ `void OnInputBoxValueCommited(const float NewValue, ETextCommit::Type CommitType, const int32 ParameterIndex);`
- L219 _protected prototype_ `void OnInputBoxValueChanged(const float NewValue, const int32 ParameterIndex, bool bIsInteractive);`
- L220 _protected prototype_ `void OnInputSliderBegin(const int32 ParameterIndex);`
- L221 _protected prototype_ `void OnInputSliderEnd(const float NewValue, const int32 ParameterIndex);`
- L224 _protected prototype_ `void BindCommands();` — Binds commands to functions in this class
- L227 _protected prototype_ `void OnBlendSampleCut();` — Handlers for blend sample actions
- L228 _protected prototype_ `void OnBlendSampleCopy();`
- L229 _protected prototype_ `void OnBlendSamplePaste();`
- L230 _protected prototype_ `void OnBlendSampleDelete();`
- L233 _protected prototype_ `bool CanBlendSampleCutCopy();` — Returns whether or not the action is possible
- L234 _protected prototype_ `bool CanBlendSamplePaste();`
- L235 _protected prototype_ `bool CanBlendSampleDelete();`
- L238 _protected prototype_ `EVisibility GetSampleToolTipVisibility() const;` — Returns whether or not the sample tool tips should be visible
- L239 _protected prototype_ `EVisibility GetPreviewToolTipVisibility() const;`
- L242 _protected prototype_ `void UpdateCachedBlendParameterData();` — Updates the cached blend parameter data
- L245 _protected prototype_ `FText GetSampleName(const FBlendSample& InBlendSample, int32 InSampleIndex) const;` — Gets the name to display for a sample
- L248 _protected prototype_ `void EnableStatusBarMessage(bool bEnable);` — Enable/disable the status bar message
- L254 _protected prototype_ `float GetSampleLookupWeight(int32 SampleIndex) const;` — This returns the weight for this sample if a lookup was made on its position. Ideally this would be 1 (and will be for triangulation). It will not always be so when using the grid.
- L257 _private member_ `TAttribute<const UBlendSpace*> BlendSpaceBase;` — Currently visualized blendspace (const to ensure changes to it are only made within SAnimationBlendSpace
- L259 _private member_ `TWeakObjectPtr<const UBlendSpace> PreviousBlendSpaceBase;` — Previous blendspace, cached here to allow us to update cached data when it changes.
- L261 _private member_ `TAttribute<FVector> TargetPosition;` — Current BlendSpace params (driven from outside the widget)
- L263 _private member_ `TAttribute<FVector> FilteredPosition;` — Current BlendSpace state - filtered version of Position (driven from outside the widget)
- L265 _private member_ `FNotifyHook* NotifyHook;` — Notify hook (ptr to SAnimationBlendSpace instance), which is required for transacting FBlendSample object when edited using the context-menu/structure details panel
- L267 _private member_ `uint32 BlendParametersToDraw;` — Number of Blend Parameters to draw
- L269 _private member_ `EGridType GridType;` — Grid type (either 1D or 2D)
- L272 _private member_ `FVector2D LastMousePosition;` — Cached mouse interaction data
- L273 _private member_ `FVector2D LocalMousePosition;`
- L274 _private member_ `FVector2D MouseDownPosition;`
- L275 _private member_ `bool bMouseIsOverGeometry;`
- L278 _private member_ `int32 SelectedSampleIndex;` — Selection and highlight sample index/state
- L279 _private member_ `int32 HighlightedSampleIndex;`
- L280 _private member_ `int32 ToolTipSampleIndex;`
- L281 _private member_ `bool bHighlightPreviewPin;`
- L284 _private member_ `EDragState DragState;` — Drag state and data (not drag/drop)
- L285 _private member_ `int32 DraggedSampleIndex;`
- L286 _private member_ `FVector LastDragPosition;`
- L289 _private member_ `bool bSamplePreviewing;` — Currently set preview blend sample value and state data
- L290 _private member_ `FVector2D LastPreviewingMousePosition;`
- L291 _private member_ `FVector PreviewPosition;`
- L292 _private member_ `bool bAdvancedPreview;`
- L293 _private member_ `TArray<FBlendSampleData> PreviewedSamples;`
- L295 _private member_ `int32 CachedTriangulationIndex = -1;` — Previous position in the triangulation/segmentation
- L298 _private member_ `FVector PreviewFilteredPosition;` — Preview state that may have been returned
- L301 _private member_ `TSharedPtr<SToolTip> ToolTip;` — Tooltip ptr which is shown when hovering/dropping/dragging a sample
- L304 _private member_ `TSharedPtr<SBox> ToolTipExtensionContainer;` — Container box used to extend a tooltip
- L307 _private member_ `FText InvalidDragDropText;` — Drag and drop data
- L308 _private member_ `FText InvalidSamplePositionDragDropText;`
- L309 _private member_ `FText DragDropAnimationName;`
- L310 _private member_ `FText HoveredAnimationName;`
- L311 _private member_ `UAnimSequence* DragDropAnimationSequence;`
- L314 _private member_ `float CachedInputBoxValues[2];` — Cached values for the grid input boxes
- L315 _private member_ `bool bSliderMovement[2] = {false, false};`
- L318 _private member_ `FSlateRect CachedGridRectangle;` — Cached grid data (derived from the blend space)
- L319 _private member_ `FVector2D SampleValueMin;`
- L320 _private member_ `FVector2D SampleValueMax;`
- L321 _private member_ `FVector2D SampleValueRange;`
- L322 _private member_ `FVector2D SampleGridDelta;`
- L323 _private member_ `bool bSampleSnapToGrid[2];`
- L324 _private member_ `FIntPoint SampleGridDivisions;`
- L325 _private member_ `FText ParameterXName;`
- L326 _private member_ `FText ParameterYName;`
- L327 _private member_ `TArray<FVector2D> CachedGridPoints;`
- L328 _private member_ `TArray<FVector> CachedSamplePoints;`
- L331 _private member_ `TSharedPtr<class FUICommandList> UICommandList;` — Commands that are bound to delegates
- L334 _private member_ `bool bRefreshCachedData;` — Whether or not the cached data should be refreshed on the next tick
- L337 _private member_ `FVector2D XAxisTextSize;` — Cached draw-able axis information
- L338 _private member_ `float MaxVerticalAxisTextWidth;`
- L339 _private member_ `float MaxHorizontalAxisTextHeight;`
- L340 _private member_ `float HorizontalAxisMaxTextWidth;`
- L341 _private member_ `FVector2D YAxisTextSize;`
- L344 _private member_ `FOnBlendSpaceSampleAdded OnSampleAdded;` — Delegates populated from SAnimationBlendSpace and used as callbacks
- L345 _private member_ `FOnBlendSpaceSampleDuplicated OnSampleDuplicated;`
- L346 _private member_ `FOnSampleMoved OnSampleMoved;`
- L347 _private member_ `FOnBlendSpaceSampleRemoved OnSampleRemoved;`
- L348 _private member_ `FOnBlendSpaceSampleReplaced OnSampleReplaced;`
- L349 _private member_ `FOnBlendSpaceNavigateUp OnNavigateUp;`
- L350 _private member_ `FOnBlendSpaceNavigateDown OnNavigateDown;`
- L351 _private member_ `FOnBlendSpaceCanvasDoubleClicked OnCanvasDoubleClicked;`
- L352 _private member_ `FOnBlendSpaceSampleDoubleClicked OnSampleDoubleClicked;`
- L353 _private member_ `FOnGetBlendSpaceSampleName OnGetBlendSpaceSampleName;`
- L354 _private member_ `FOnExtendBlendSpaceSampleTooltip OnExtendSampleTooltip;`
- L357 _private member_ `float DragThreshold;` — Threshold values for hovering, click and dragging samples
- L358 _private member_ `float ClickAndHighlightThreshold;`
- L361 _private member_ `FVector2D KeySize;` — Sample drawing data
- L362 _private member_ `FVector2D PreviewSize;`
- L363 _private member_ `const FSlateBrush* KeyBrush;`
- L364 _private member_ `const FSlateBrush* PreviewBrush;`
- L365 _private member_ `const FSlateBrush* BackgroundImage;`
- L366 _private member_ `const FSlateBrush* LabelBrush;`
- L375 _private member_ `const FSlateBrush* ArrowBrushes[(int32)EArrowDirection::Max];`
- L378 _private member_ `FSlateColor HighlightKeyColor;` — Individual sample state colours
- L379 _private member_ `FSlateColor KeyColor;`
- L380 _private member_ `FSlateColor SelectKeyColor;`
- L381 _private member_ `FSlateColor PreDragKeyColor;`
- L382 _private member_ `FSlateColor DragKeyColor;`
- L383 _private member_ `FSlateColor InvalidColor;`
- L384 _private member_ `FSlateColor DropKeyColor;`
- L385 _private member_ `FSlateColor PreviewKeyColor;`
- L388 _private member_ `FMargin GridMargin;` — Grid drawing and layout data
- L389 _private member_ `FLinearColor GridLinesColor;`
- L390 _private member_ `FLinearColor GridOutlineColor;`
- L391 _private member_ `FSlateColor TriangulationColor;`
- L392 _private member_ `FSlateColor TriangulationCurrentColor;`
- L393 _private member_ `FSlateFontInfo FontInfo;`
- L394 _private member_ `float TextMargin;`
- L395 _private member_ `bool bShowTriangulation;`
- L396 _private member_ `bool bShowAnimationNames;`
- L397 _private member_ `bool bStretchToFit;`
- L398 _private member_ `FMargin GridRatioMargin;`
- L399 _private member_ `bool bReadOnly;`
- L400 _private member_ `bool bShowAxisLabels;`
- L401 _private member_ `bool bShowSettingsButtons;`
- L403 _private member_ `FStatusBarMessageHandle StatusBarMessageHandle;`
- L405 _private member_ `FName StatusBarName;`

#### enum `SBlendSpaceGridWidget::EGridType`  
`enum class EGridType`  
_L64-68_
- L66 _public enumerator_ `SingleAxis`
- L67 _public enumerator_ `TwoAxis`

#### enum `SBlendSpaceGridWidget::EDragState`  
`enum class EDragState`  
_L71-87_
- desc: Represents the different states of a drag operation
- L74 _public enumerator_ `PreDrag` — The user has clicked a mouse button, but hasn't moved more then the drag threshold.
- L76 _public enumerator_ `DragSample` — The user is dragging the selected sample.
- L78 _public enumerator_ `Preview` — The user is setting the preview value
- L80 _public enumerator_ `DragDrop` — The user is dropping a new sample onto the grid
- L82 _public enumerator_ `DragDropOverride` — The user is dropping a new animation to an existing sample on the grid
- L84 _public enumerator_ `InvalidDragDrop` — The user is dropping an invalid animation sequence onto the grid
- L86 _public enumerator_ `None` — There is no active drag operation.

#### enum `SBlendSpaceGridWidget::EArrowDirection`  
`enum class EArrowDirection : uint8`  
_L367-374_
- L369 _public enumerator_ `Left`
- L370 _public enumerator_ `Right`
- L371 _public enumerator_ `Up`
- L372 _public enumerator_ `Down`
- L373 _public enumerator_ `Max`

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnSampleMoved, const int32 , const FVector& , bool );`
- L26 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnSampleMoved, const int32 , const FVector& , bool );`
- L27 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSampleAnimationChanged, UAnimSequence*, const FVector&);`
- L27 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSampleAnimationChanged, UAnimSequence*, const FVector&);`

### `Source/Editor/Persona/Private/SAnimationDlgs.h` (Private)


#### class `SImportPathDialog`  
`class SImportPathDialog: public SWindow`  
_L10-44_
- inherits: `SWindow`
- L13 _public function_ `SLATE_BEGIN_ARGS(SImportPathDialog)`
- L17 _public function_ `SLATE_ARGUMENT(FText, DefaultAssetPath) SLATE_END_ARGS() SImportPathDialog() : UserResponse(EAppReturnType::Cancel)`
- L25 _public prototype_ `void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `EAppReturnType::Type ShowModal();` — Displays the dialog in a blocking fashion
- L32 _public prototype_ `FString GetAssetPath();` — Gets the resulting asset path
- L35 _protected prototype_ `void OnPathChange(const FString& NewPath);`
- L36 _protected prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`
- L37 _protected prototype_ `bool IsOkButtonEnabled() const;`
- L38 _protected member_ `EAppReturnType::Type UserResponse;`
- L39 _protected member_ `FText AssetPath;`
- L40 _protected member_ `FText AssetName;`
- L41 _protected member_ `FText Duration;`
- L43 _protected member_ `static FText LastUsedAssetPath;`

### `Source/Editor/Persona/Private/SAnimationEditorViewport.h` (Private)


#### struct `FAnimationEditorViewportRequiredArgs`  
`struct FAnimationEditorViewportRequiredArgs`  
_L26-42_
- L28 _public function_ `FAnimationEditorViewportRequiredArgs(const TSharedRef<class IPersonaPreviewScene>& InPreviewScene, TSharedRef<class SAnimationEditorViewportTabBody> InTabBody, TSharedRef<class FAssetEditorToolkit> InAssetEditorToolkit, int32 InViewportIndex) : PreviewScene(InPreviewScene) , TabBody(InTabBody) , AssetEditorToolkit(InAssetEditorToolkit) , ViewportIndex(InViewportIndex)`
- L35 _public member_ `TSharedRef<class IPersonaPreviewScene> PreviewScene;`
- L37 _public member_ `TSharedRef<class SAnimationEditorViewportTabBody> TabBody;`
- L39 _public member_ `TSharedRef<class FAssetEditorToolkit> AssetEditorToolkit;`
- L41 _public member_ `int32 ViewportIndex;`

#### enum `ESectionDisplayMode`  
`enum class ESectionDisplayMode`  
_L47-54_
- L49 _public enumerator_ `None = -1`
- L50 _public enumerator_ `ShowAll`
- L51 _public enumerator_ `ShowOnlyClothSections`
- L52 _public enumerator_ `HideOnlyClothSections`
- L53 _public enumerator_ `NumSectionDisplayMode`

#### class `SAnimationEditorViewport`  
`class SAnimationEditorViewport : public SEditorViewport, public FEditorUndoClient`  
_L56-165_
- inherits: `SEditorViewport,FEditorUndoClient`
- L59 _public function_ `SLATE_BEGIN_ARGS(SAnimationEditorViewport) : _ContextName(NAME_None) , _ShowShowMenu(true) , _ShowLODMenu(true) , _ShowPlaySpeedMenu(true) , _ShowStats(true) , _ShowFloorOptions(true) , _ShowTurnTable(true) , _ShowPhysicsMenu(false)`
- L70 _public prototype_ `SLATE_ARGUMENT(TArray<TSharedPtr<FExtender>>, Extenders) SLATE_ARGUMENT(FName, ContextName) SLATE_ARGUMENT(bool, ShowShowMenu) SLATE_ARGUMENT(bool, ShowLODMenu) SLATE_ARGUMENT(bool, ShowPlaySpeedMenu) SLATE_ARGUMENT(bool, ShowStats) SLATE_ARGUMENT(bool, ShowFloorOptions) SLATE_ARGUMENT(bool, ShowTurnTable) SLATE_ARGUMENT(bool, ShowPhysicsMenu) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FAnimationEditorViewportRequiredArgs& InRequiredArgs);`
- L91 _public prototype_ `virtual ~SAnimationEditorViewport();`
- L94 _public function_ `TSharedPtr<SAnimViewportToolBar> GetViewportToolbar() const` — Get the viewport toolbar widget
- L96 _public function_ `bool IsPhysicsEditor() const`
- L99 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface
- L100 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L101 _protected prototype_ `virtual TSharedPtr<IPreviewProfileController> CreatePreviewProfileController() override;`
- L102 _protected prototype_ `virtual void OnFocusViewportToSelection() override;`
- L103 _protected prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L107 _protected prototype_ `virtual void PostUndo( bool bSuccess );` — Handle undo/redo by refreshing the viewport
- L108 _protected prototype_ `virtual void PostRedo( bool bSuccess );`
- L110 _protected prototype_ `virtual void BindCommands() override;`
- L111 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L112 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L113 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L117 _protected member_ `TSharedPtr<class FAnimationViewportClient> LevelViewportClient;` — Viewport client
- L120 _protected member_ `TWeakPtr<class SAnimationEditorViewportTabBody> TabBodyPtr;` — Pointer to the compound widget that owns this viewport widget
- L123 _protected member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScenePtr;` — The preview scene that we are viewing
- L126 _protected member_ `FDelegateHandle PreviewFeatureLevelChangedHandle;` — Handle to the registered OnPreviewFeatureLevelChanged delegate.
- L129 _protected member_ `TWeakPtr<class FAssetEditorToolkit> AssetEditorToolkitPtr;` — The asset editor we are embedded in
- L132 _protected member_ `TSharedPtr<SAnimViewportToolBar> ViewportToolbar;` — The viewport toolbar
- L135 _protected member_ `TArray<TSharedPtr<FExtender>> Extenders;` — Menu extenders
- L138 _protected member_ `FName ContextName;` — Context used for persisting settings
- L141 _protected member_ `int32 ViewportIndex;` — Viewport index (0-3)
- L144 _protected member_ `bool bShowShowMenu;` — Whether to show the 'Show' menu
- L147 _protected member_ `bool bShowLODMenu;` — Whether to show the 'LOD' menu
- L150 _protected member_ `bool bShowPlaySpeedMenu;` — Whether to show the 'Play Speed' menu
- L153 _protected member_ `bool bShowStats;` — Whether we should show stats for this viewport
- L156 _protected member_ `bool bShowFloorOptions;` — Whether to show options relating to floor height
- L159 _protected member_ `bool bShowTurnTable;` — Whether to show options relating to turntable
- L162 _protected member_ `bool bShowPhysicsMenu;` — Whether to show options relating to physics

#### class `SAnimationEditorViewportTabBody`  
`class SAnimationEditorViewportTabBody : public IPersonaViewport`  
_L170-697_
- inherits: `IPersonaViewport`
- L173 _public function_ `SLATE_BEGIN_ARGS( SAnimationEditorViewportTabBody ) : _BlueprintEditor() , _ContextName(NAME_None) , _ShowShowMenu(true) , _ShowLODMenu(true) , _ShowPlaySpeedMenu(true) , _ShowTimeline(true) , _ShowStats(true) , _AlwaysShowTransformToolbar(false) , _ShowFloorOptions(true) , _ShowTurnTable(true) , _ShowPhysicsMenu(false)`
- L219 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene, const TSharedRef<class FAssetEditorToolkit>& InAssetEditorToolkit, int32 InViewportIndex);`
- L220 _public prototype_ `SAnimationEditorViewportTabBody();`
- L223 _public prototype_ `virtual TSharedRef<IPersonaViewportState> SaveState() const override;` — IPersonaViewport interface
- L224 _public prototype_ `virtual void RestoreState(TSharedRef<IPersonaViewportState> InState) override;`
- L225 _public prototype_ `virtual FEditorViewportClient& GetViewportClient() const override;`
- L226 _public prototype_ `virtual TSharedRef<IPinnedCommandList> GetPinnedCommandList() const override;`
- L227 _public prototype_ `virtual TWeakPtr<SWidget> AddNotification(TAttribute<EMessageSeverity::Type> InSeverity, TAttribute<bool> InCanBeDismissed, const TSharedRef<SWidget>& InNotificationWidget, FPersonaViewportNotificationOptions InOptions) override;`
- L228 _public prototype_ `virtual void RemoveNotification(const TWeakPtr<SWidget>& InContainingWidget) override;`
- L229 _public function_ `virtual FPersonaViewportKeyDownDelegate& GetKeyDownDelegate() override`
- L230 _public prototype_ `virtual void AddOverlayWidget( TSharedRef<SWidget> InOverlaidWidget, int32 ZOrder = INDEX_NONE ) override;`
- L231 _public prototype_ `virtual void RemoveOverlayWidget( TSharedRef<SWidget> InOverlaidWidget ) override;`
- L235 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget interface
- L237 _public prototype_ `void RefreshViewport();`
- L242 _public function_ `const TSharedPtr<FUICommandList_Pinnable>& GetCommandList() const` — @return The list of commands on the viewport that are bound to delegates
- L245 _public prototype_ `void HandlePreviewMeshChanged(class USkeletalMesh* OldSkeletalMesh, class USkeletalMesh* NewSkeletalMesh);` — Handle the skeletal mesh changing
- L248 _public prototype_ `int32 GetLODModelCount() const;` — Function to get the number of LOD models associated with the preview skeletal mesh
- L251 _public prototype_ `bool IsLODModelSelected( int32 LODSelectionType ) const;` — LOD model selection checking function
- L252 _public prototype_ `bool IsTrackingAttachedMeshLOD() const;`
- L253 _public prototype_ `int32 GetLODSelection() const;`
- L256 _public function_ `TSharedPtr<class SEditorViewport> GetViewportWidget() const` — Function to get anim viewport widget
- L259 _public function_ `FEditorViewportClient& GetLevelViewportClient()` — Gets the editor client for this viewport
- L265 _public prototype_ `TSharedPtr<class FAnimationViewportClient> GetAnimationViewportClient() const;` — Gets the animation viewport client
- L268 _public prototype_ `FText GetDisplayString() const;` — Returns Detail description of what's going with viewport
- L271 _public prototype_ `bool CanUseGizmos() const;` — Can we use gizmos?
- L274 _public prototype_ `bool IsAutoAlignFloor() const;` — Function to check whether floor is auto aligned or not
- L276 _public prototype_ `void SetWindStrength( float SliderPos );`
- L279 _public prototype_ `TOptional<float> GetWindStrengthSliderValue() const;` — Function to get slider value which represents wind strength (0 - 1)
- L281 _public prototype_ `bool IsApplyingClothWind() const;`
- L284 _public prototype_ `void SetGravityScale( float SliderPos );` — Show gravity scale
- L285 _public prototype_ `float GetGravityScaleSliderValue() const;`
- L288 _public prototype_ `void SetBoneDrawSize(float BoneDrawSize);` — Adjustable bone draw size
- L289 _public prototype_ `float GetBoneDrawSize() const;`
- L291 _public prototype_ `void SetCustomTurnTableSpeed(float InCustomTurnTableSpeed);`
- L292 _public prototype_ `float GetCustomTurnTableSpeed() const;`
- L295 _public prototype_ `void OnSetLODModel(int32 LODSelectionType);` — Function to set LOD model selection
- L296 _public prototype_ `void OnSetLODTrackDebuggedInstance();`
- L297 _public prototype_ `void OnLODModelChanged();`
- L298 _public prototype_ `void OnDebugForcedLODChanged();`
- L300 _public prototype_ `void OnSetSkinWeightProfile(FName InProfileName, ESkinWeightProfileLayer InLayer);`
- L301 _public prototype_ `bool IsSkinWeightProfileSelected(FName InProfileName, ESkinWeightProfileLayer InLayer) const;`
- L302 _public prototype_ `TArray<FName> GetSelectedProfileNames() const;`
- L304 _public prototype_ `void OnBeginSliderMovementFloorOffset();`
- L305 _public prototype_ `void OnFloorOffsetChanged(float InNewValue);`
- L306 _public prototype_ `void OnFloorOffsetCommitted(float InNewValue, ETextCommit::Type InCommitType);`
- L308 _public prototype_ `const TSharedPtr<IPinnedCommandList>& GetPinnedCommands();`
- L311 _public function_ `TSharedRef<class FAnimationEditorPreviewScene> GetPreviewScene() const` — Get the preview scene we are viewing
- L314 _public prototype_ `TSharedPtr<class FAssetEditorToolkit> GetAssetEditorToolkit() const;` — Get the asset editor toolkit we are embedded in
- L317 _private prototype_ `bool IsVisible() const;`
- L322 _private prototype_ `void BindCommands();` — Binds our UI commands to delegates
- L325 _private prototype_ `void OnShowMorphTargets();` — Show Morphtarget of SkeletalMesh
- L327 _private prototype_ `bool IsShowingMorphTargets() const;`
- L330 _private prototype_ `void OnShowRawAnimation();` — Show Raw Animation on top of Compressed Animation
- L332 _private prototype_ `bool IsShowingRawAnimation() const;`
- L335 _private prototype_ `void OnToggleDisablePostProcess();` — Handlers for the disable post process flag
- L336 _private prototype_ `bool CanDisablePostProcess() const;`
- L337 _private prototype_ `bool IsDisablePostProcessChecked();`
- L340 _private prototype_ `void OnShowNonRetargetedAnimation();` — Show non retargeted animation.
- L342 _private prototype_ `bool IsShowingNonRetargetedPose() const;`
- L345 _private prototype_ `void OnShowSourceRawAnimation();` — Show non retargeted animation.
- L347 _private prototype_ `bool IsShowingSourceRawAnimation() const;`
- L350 _private prototype_ `void OnShowBakedAnimation();` — Show non retargeted animation.
- L352 _private prototype_ `bool IsShowingBakedAnimation() const;`
- L356 _private prototype_ `void OnShowAdditiveBase();` — Additive Base Pose on top of full animation
- L358 _private prototype_ `bool IsShowingAdditiveBase() const;`
- L360 _private prototype_ `bool IsPreviewingAnimation() const;`
- L363 _private prototype_ `void OnShowBoneNames();` — Function to show/hide bone names
- L366 _private prototype_ `bool IsShowingBoneNames() const;` — Function to check whether bone names are displayed or not
- L369 _private prototype_ `void OnShowBoneColors();` — Function to show/hide bone colors
- L372 _private prototype_ `bool IsShowingBoneColors() const;` — Function to check whether bone's are using multiple colors
- L375 _private prototype_ `void OnShowOverlayNone();` — Function to show/hide selected bone weight
- L378 _private prototype_ `bool IsShowingOverlayNone() const;` — Function to check whether bone weights are displayed or not
- L381 _private prototype_ `void OnShowOverlayBoneWeight();` — Function to show/hide selected bone weight
- L384 _private prototype_ `bool IsShowingOverlayBoneWeight() const;` — Function to check whether bone weights are displayed or not
- L387 _private prototype_ `void OnShowOverlayMorphTargetVert();` — Function to show/hide selected morphtarget overlay
- L390 _private prototype_ `bool IsShowingOverlayMorphTargetVerts() const;` — Function to check whether morphtarget overlay is displayed or not
- L393 _private prototype_ `void OnSetBoneDrawMode(int32 BoneDrawMode);` — Function to set Local axes mode of the specificed type
- L396 _private prototype_ `bool IsBoneDrawModeSet(int32 BoneDrawMode) const;` — Local axes mode checking function for the specificed type
- L399 _private prototype_ `void ToggleShowAllBones();` — Toggles showing all bones when not all bones are shown, none otherwise
- L402 _private prototype_ `void OnSetLocalAxesMode( int32 LocalAxesMode );` — Function to set Local axes mode of the specificed type
- L405 _private prototype_ `bool IsLocalAxesModeSet( int32 LocalAxesMode ) const;` — Local axes mode checking function for the specificed type
- L408 _private prototype_ `void OnShowSockets();` — Function to show/hide socket hit points
- L411 _private prototype_ `bool IsShowingSockets() const;` — Function to check whether socket hit points are displayed or not
- L414 _private prototype_ `void OnShowAttributes();` — Function to show/hide extracted transform attributes
- L417 _private prototype_ `bool IsShowingAttributes() const;` — Function to check whether extracted transform attributes are displayed or not
- L420 _private prototype_ `void OnShowDisplayInfo(int32 DisplayInfoMode);` — Function to show/hide mesh info
- L423 _private prototype_ `bool IsShowingMeshInfo(int32 DisplayInfoMode) const;` — Function to check whether mesh info is displayed or not
- L426 _private prototype_ `void OnToggleShowTimecode();` — Function to show/hide timecode display.
- L429 _private prototype_ `bool IsShowTimecode() const;` — Function to check whether timecode is displayed or not
- L432 _private prototype_ `void OnToggleAutoAlignFloor();` — Toggles floor alignment in the preview scene
- L435 _private prototype_ `void ShowBound();` — Called to toggle showing of the bounds of the current preview mesh
- L436 _private prototype_ `bool CanShowBound() const;`
- L437 _private prototype_ `bool IsShowBoundEnabled() const;`
- L440 _private prototype_ `void ToggleShowPreviewMesh();` — Called to toggle showing of the current preview mesh
- L441 _private prototype_ `bool CanShowPreviewMesh() const;`
- L442 _private prototype_ `bool IsShowPreviewMeshEnabled() const;`
- L445 _private prototype_ `void ToggleShowNaniteFallback();` — Called to toggle showing the Nanite fallback of the current preview mesh
- L446 _private prototype_ `bool CanShowNaniteFallback() const;`
- L447 _private prototype_ `bool IsShowNaniteFallbackEnabled() const;`
- L450 _private function_ `FORCEINLINE_DEBUGGABLE void ForEachDebugMesh(TFunction<void (UDebugSkelMeshComponent*)> PerMeshFunction)` — Run a lambda function on each preview mesh in the scene
- L461 _private prototype_ `void UseInGameBound();` — Called to toggle using in-game bound on current preview mesh
- L462 _private prototype_ `bool CanUseInGameBound() const;`
- L463 _private prototype_ `bool IsUsingInGameBound() const;`
- L466 _private prototype_ `void UseFixedBounds();` — Called to toggle 'fixed bounds' option to preview
- L467 _private prototype_ `bool CanUseFixedBounds() const;`
- L468 _private prototype_ `bool IsUsingFixedBounds() const;`
- L471 _private prototype_ `void UsePreSkinnedBounds();` — Called to toggle 'pre-skinned' option to preview
- L472 _private prototype_ `bool CanUsePreSkinnedBounds() const;`
- L473 _private prototype_ `bool IsUsingPreSkinnedBounds() const;`
- L476 _private prototype_ `void ComboBoxSelectionChanged( TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo );` — Called by UV channel combo box on selection change
- L479 _private prototype_ `void PopulateNumUVChannels();` — Populates choices for UV Channel combo box for each lod based on current preview asset
- L482 _private prototype_ `void PopulateUVChoices();` — Populates choices for UV Channel combo box
- L484 _private prototype_ `void AnimChanged(UAnimationAsset* AnimAsset);`
- L487 _private prototype_ `void OpenPreviewSceneSettings();` — Open the preview scene settings
- L489 _private prototype_ `void SaveCameraAsDefault();`
- L490 _private prototype_ `void ClearDefaultCamera();`
- L491 _private prototype_ `void JumpToDefaultCamera();`
- L492 _private prototype_ `bool HasDefaultCameraSet() const;`
- L493 _private prototype_ `bool CanSaveCameraAsDefault() const;`
- L496 _private prototype_ `void HandleFocusCamera();` — Focus the viewport on the preview mesh
- L498 _private prototype_ `void CreatePinnedCommands();`
- L502 _public prototype_ `bool CanChangeCameraMode() const;` — Called to determine whether the camera mode menu options should be enabled
- L506 _private prototype_ `void OnToggleMuteAudio();` — Function to mute/unmute viewport audio
- L509 _private prototype_ `bool IsAudioMuted() const;` — Whether audio from the viewport is muted
- L512 _private prototype_ `void OnToggleUseAudioAttenuation();` — Function to enable/disable viewport audio attenuation
- L515 _private prototype_ `bool IsAudioAttenuationEnabled() const;` — Whether audio from the viewport is attenuated
- L518 _private prototype_ `void SetProcessRootMotionMode(EProcessRootMotionMode Mode);` — Sets process root motion mode on the debug mesh
- L521 _private prototype_ `bool IsProcessRootMotionModeSet(EProcessRootMotionMode Mode) const;` — Checks whether the supplied mode is set on the debug mesh
- L524 _private prototype_ `bool CanUseProcessRootMotionMode(EProcessRootMotionMode Mode) const;` — Whether the supplied mode can be used
- L526 _private prototype_ `void SetVisualizeRootMotionMode(EVisualizeRootMotionMode Mode);`
- L527 _private prototype_ `bool IsVisualizeRootMotionModeSet(EVisualizeRootMotionMode Mode) const;`
- L528 _private prototype_ `bool CanVisualizeRootMotion() const;`
- L530 _private prototype_ `void ToggleNotificationVisualizations();`
- L531 _private prototype_ `bool IsNotificationVisualizationsEnabled() const;`
- L533 _private prototype_ `void ToggleAssetUserDataVisualizations();`
- L534 _private prototype_ `bool IsAssetUserDataVisualizationsEnabled() const;`
- L538 _private member_ `EAnimationPlaybackSpeeds::Type SelectedTurnTableSpeed;` — Selected Turn Table speed
- L540 _private member_ `EPersonaTurnTableMode::Type SelectedTurnTableMode;` — Selected turn table mode
- L542 _private member_ `float CustomTurnTableSpeed = 1.0f;` — Custom Animation speed in the viewport. Transient setting.
- L544 _private prototype_ `void OnSetTurnTableSpeed(int32 SpeedIndex);`
- L545 _private prototype_ `void OnSetTurnTableMode(int32 ModeIndex);`
- L546 _private prototype_ `bool IsTurnTableModeSelected(int32 ModeIndex) const;`
- L548 _private member_ `FPersonaViewportKeyDownDelegate OnKeyDownDelegate;`
- L552 _public prototype_ `void SetCameraFollowMode(EAnimationViewportCameraFollowMode InCameraFollowMode, FName InBoneName);` — Setup the camera follow mode
- L553 _public prototype_ `bool IsCameraFollowEnabled(EAnimationViewportCameraFollowMode InCameraFollowMode) const;`
- L554 _public prototype_ `FName GetCameraFollowBoneName() const;`
- L555 _public prototype_ `void ToggleRotateCameraToFollowBone();`
- L558 _public prototype_ `EAxis::Type GetBoneAsCameraAxis(FAnimationViewportClient::EDirection Direction) const;` — Gets the axis for a direction when using the Bone As Camera follow mode
- L561 _public prototype_ `void SetBoneAsCameraAxis(FAnimationViewportClient::EDirection Direction, EAxis::Type Axis);` — Sets the axis for a direction when using the Bone As Camera follow mode
- L564 _public prototype_ `UE::Math::TVector<double> GetBoneAsCameraPositionOffset() const;` — Gets the position offset from the bone origin in world coordiantes for the Bone As Camera follow mode
- L567 _public prototype_ `FRotator GetBoneAsCameraRotationOffset() const;` — Gets the rotation offset from the bone in world coordiantes for the Bone As Camera follow mode
- L571 _public prototype_ `void SetBoneAsCameraPositionOffset(UE::Math::TVector<double> Offset);` — Sets the position offset from the bone origin in world coordiantes for the Bone As Camera follow mode
- L574 _public prototype_ `void SetBoneAsCameraRotationOffset(const FRotator& Offset);` — Sets the rotation offset from the bone in world coordiantes for the Bone As Camera follow mode
- L576 _public prototype_ `bool GetShouldRotateCameraToFollowBone() const;`
- L577 _public prototype_ `void TogglePauseAnimationOnCameraMove();`
- L578 _public prototype_ `bool GetShouldPauseAnimationOnCameraMove() const;`
- L579 _public prototype_ `bool IsTurnTableSpeedSelected(int32 SpeedIndex) const;`
- L586 _private prototype_ `void OnEnableClothSimulation();` — Enable cloth simulation
- L587 _private prototype_ `bool IsClothSimulationEnabled() const;`
- L590 _private prototype_ `void OnResetClothSimulation();` — Reset clothing simulation
- L592 _private prototype_ `void OnPauseClothingSimWithAnim();`
- L593 _private prototype_ `bool IsPausingClothingSimWithAnim();`
- L596 _private prototype_ `void OnSetSectionsDisplayMode(ESectionDisplayMode DisplayMode);` — Show all sections which means the original state
- L597 _private prototype_ `bool IsSectionsDisplayMode(ESectionDisplayMode DisplayMode) const;`
- L601 _private member_ `TWeakPtr<class FAnimationEditorPreviewScene> PreviewScenePtr;` — Weak pointer back to the preview scene we are viewing
- L604 _private member_ `TWeakPtr<class FAssetEditorToolkit> AssetEditorToolkitPtr;` — Weak pointer back to asset editor we are embedded in
- L607 _private member_ `TWeakPtr<class FBlueprintEditor> BlueprintEditorPtr;` — Weak pointer to the blueprint editor we are optionally embedded in
- L610 _private member_ `bool bShowTimeline;` — Whether to show the timeline
- L613 _private member_ `bool bAlwaysShowTransformToolbar;` — Whether we should always show the transform toolbar for this viewport
- L616 _private member_ `bool bCameraFollowLockRotation;` — Whether to align the camera's rotation to the bone's orientation
- L619 _private member_ `TSharedPtr<FEditorViewportClient> LevelViewportClient;` — Level viewport client
- L622 _private member_ `TSharedPtr<class SAnimationEditorViewport> ViewportWidget;` — Viewport widget
- L625 _private member_ `TSharedPtr<SHorizontalBox> ToolbarBox;` — Toolbar widget
- L628 _private member_ `TSharedPtr<FUICommandList_Pinnable> UICommandList;` — Commands that are bound to delegates
- L631 _private member_ `FOnInvokeTab OnInvokeTab;` — Delegate used to invoke tabs in the containing asset editor
- L634 _private member_ `TSharedPtr<IPinnedCommandList> PinnedCommands;` — Pinned commands widget
- L637 _private member_ `TUniquePtr<FScopedTransaction> PendingTransaction;` — Transaction to handle scoping updates for sliders we own that transact objects (i.e. floor mesh)
- L639 _private member_ `FName ContextName;`
- L641 _private member_ `FAnimationScrubPanelDelegates TimelineDelegates;`
- L645 _public member_ `TSharedPtr< class STextComboBox > UVChannelCombo;` — UV Channel Selector
- L649 _private member_ `TArray< TSharedPtr< FString > > UVChannels;` — Choices for UVChannelCombo
- L652 _private member_ `TArray<int32> NumUVChannels;` — Num UV Channels at each LOD of Preview Mesh
- L656 _public member_ `TSharedPtr<SVerticalBox> ScrubPanelContainer;` — Box that contains scrub panel
- L659 _public member_ `TSharedPtr<SVerticalBox> ViewportNotificationsContainer;` — Box that contains notifications
- L662 _public member_ `TWeakPtr<SWidget> WeakPostProcessNotification;` — Post process notification
- L665 _public member_ `TWeakPtr<SWidget> WeakRecordingNotification;` — Recording notification
- L668 _public member_ `TWeakPtr<SWidget> WeakMinLODNotification;` — Min LOD notification
- L671 _public member_ `int32 LODSelection;` — Current LOD selection
- L674 _public member_ `ESectionDisplayMode SectionsDisplayMode;` — Draw All/ Draw only clothing sections/ Hide only clothing sections
- L677 _public member_ `FOnGetViewportText OnGetViewportText;` — Delegate used to get custom viewport text
- L680 _public prototype_ `float GetViewMinInput() const;` — Get Min/Max Input of value
- L681 _public prototype_ `float GetViewMaxInput() const;`
- L684 _public prototype_ `void UpdateShowFlagForMeshEdges();` — Sets The EngineShowFlags.MeshEdges flag on the viewport based on current state
- L687 _public prototype_ `void UpdateScrubPanel(UAnimationAsset* AnimAsset);` — Update scrub panel to reflect viewed animation asset
- L690 _public prototype_ `void AddRecordingNotification();` — Adds a persistent notification to display recording state when recording
- L693 _public prototype_ `void AddPostProcessNotification();` — Adds a persistent notification to display post process graph state
- L696 _public prototype_ `void AddMinLODNotification();` — Add a notification to tell the user a min LOD is being applied

### `Source/Editor/Persona/Private/SAnimationScrubPanel.h` (Private)


#### class `SAnimationScrubPanel`  
`class SAnimationScrubPanel : public SCompoundWidget`  
_L20-126_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SAnimationScrubPanel) : _LockedSequence()`
- L28 _public prototype_ `SLATE_ARGUMENT(UAnimSequenceBase*, LockedSequence) SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax ) SLATE_ARGUMENT( bool, bDisplayAnimScrubBarEditing) SLATE_EVENT( FOnSetInputViewRange, OnSetInputViewRange ) SLATE_EVENT( FOnCropAnimSequence, OnCropAnimSequence ) SLATE_EVENT( FSimpleDelegate, OnReZeroAnimSequence ) SLATE_ARGUMENT( bool, bAllowZoom ) SLATE_ARGUMENT( FAnimationScrubPanelDelegates, TimelineDelegates ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<IPersonaPreviewScene>& InPreviewScene );` — If you'd like to lock to one asset for this scrub control, give this
- L50 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L53 _public prototype_ `void ReplaceLockedSequence(class UAnimSequenceBase * NewLockedSequence);`
- L55 _protected member_ `TWeakPtr<IPersonaPreviewScene> PreviewScenePtr;`
- L56 _protected member_ `FOnSetInputViewRange OnSetInputViewRange;`
- L58 _protected member_ `bool bSliderBeingDragged;`
- L61 _protected prototype_ `virtual FReply OnClick_Forward_Step();` — notifiers
- L62 _protected prototype_ `virtual FReply OnClick_Forward_End();`
- L63 _protected prototype_ `virtual FReply OnClick_Backward_Step();`
- L64 _protected prototype_ `virtual FReply OnClick_Backward_End();`
- L66 _protected prototype_ `virtual FReply OnClick_Forward();`
- L67 _protected prototype_ `virtual FReply OnClick_Backward();`
- L69 _protected prototype_ `virtual FReply OnClick_ToggleLoop();`
- L71 _protected prototype_ `virtual FReply OnClick_Record();`
- L73 _protected prototype_ `virtual EVisibility OnGetRecordVisibility() const;`
- L75 _protected prototype_ `void AnimChanged(UAnimationAsset * AnimAsset);`
- L77 _protected prototype_ `virtual void OnValueChanged(float NewValue, bool bFireNotifies);`
- L80 _protected prototype_ `void OnCropAnimSequence( bool bFromStart, float CurrentTime );` — Function to crop animation sequence before/after selected frame
- L81 _protected prototype_ `void OnAppendAnimSequence( bool bFromStart, int32 NumOfFrames );`
- L82 _protected prototype_ `void OnInsertAnimSequence( bool bBefore, int32 CurrentFrame );`
- L88 _protected prototype_ `void OnReZeroAnimSequence(int32 FrameIndex);` — Sets the root bone to be at the origin at the specified frame. If FrameIndex is INDEX_NONE then the current frame is used.
- L91 _protected prototype_ `void OnBeginSliderMovement();` — make sure viewport is freshes
- L92 _protected prototype_ `void OnEndSliderMovement(float NewValue);`
- L94 _protected prototype_ `EPlaybackMode::Type GetPlaybackMode() const;`
- L95 _protected prototype_ `bool IsRecording() const;`
- L96 _protected prototype_ `bool IsLoopStatusOn() const;`
- L97 _protected prototype_ `bool IsRealtimeStreamingMode() const;`
- L98 _protected prototype_ `float GetViewInputMin() const;`
- L99 _protected prototype_ `float GetViewInputMax() const;`
- L101 _protected prototype_ `float GetScrubValue() const;`
- L102 _protected prototype_ `class UAnimSingleNodeInstance* GetPreviewInstance() const;`
- L104 _protected member_ `TSharedPtr<class SScrubControlPanel> ScrubControlPanel;`
- L105 _protected member_ `class UAnimSequenceBase* LockedSequence;`
- L106 _protected member_ `FAnimationScrubPanelDelegates TimelineDelegates;`
- L107 _protected member_ `TAttribute<float> ViewInputMinAttribute;`
- L108 _protected member_ `TAttribute<float> ViewInputMaxAttribute;`
- L111 _protected prototype_ `bool DoesSyncViewport() const;` — Do I need to sync with viewport?
- L112 _protected prototype_ `uint32 GetNumberOfKeys() const;`
- L113 _protected prototype_ `float GetSequenceLength() const;`
- L116 _protected prototype_ `UAnimInstance* GetAnimInstanceWithBlueprint() const;` — Returns a UAnimInstance that came from a blueprint, or NULL (even if the UAnimInstance is not null, but it didn't come from a blueprint)
- L119 _protected prototype_ `bool GetAnimBlueprintDebugData(UAnimInstance*& Instance, FAnimBlueprintDebugData*& DebugInfo) const;` — Returns the debug data if the current preview is of an anim blueprint that is the selected debug object, or NULL
- L121 _protected function_ `TSharedRef<IPersonaPreviewScene> GetPreviewScene() const`
- L123 _protected prototype_ `bool GetDisplayDrag() const;`
- L125 _protected prototype_ `void SetPlaybackMode(EPlaybackMode::Type InMode);`

### `Source/Editor/Persona/Private/SAnimationSequenceBrowser.h` (Private)


#### enum `EAdditiveTypeFilterMode`  
`enum class EAdditiveTypeFilterMode : uint8`  
_L35-41_
- reflection: `UENUM()`
- L37 _public enumerator_ `NonAdditive UMETA(DisplayName = "Non-Additive")`
- L38 _public enumerator_ `AnyAdditive UMETA(DisplayName = "Any Additive")`
- L39 _public enumerator_ `LocalSpaceBase UMETA(DisplayName = "Local Space")`
- L40 _public enumerator_ `RotationOffsetMeshSpace UMETA(DisplayName = "Mesh Space")`

#### class `FAnimationAssetViewportClient`  
`class FAnimationAssetViewportClient : public FEditorViewportClient`  
_L45-54_
- inherits: `FEditorViewportClient`
- desc: FAnimationAssetViewportClient
- L48 _public prototype_ `FAnimationAssetViewportClient(FPreviewScene& InPreviewScene);`
- L51 _public prototype_ `virtual FSceneInterface* GetScene() const override;` — FEditorViewportClient interface
- L52 _public prototype_ `virtual FLinearColor GetBackgroundColor() const override;`

#### class `SAnimationSequenceBrowser`  
`class SAnimationSequenceBrowser : public IAnimationSequenceBrowser`  
_L59-294_
- inherits: `IAnimationSequenceBrowser`
- L62 _public function_ `SLATE_BEGIN_ARGS(SAnimationSequenceBrowser) : _ShowHistory(false)`
- L72 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<class IPersonaToolkit>& InPersonaToolkit);`
- L74 _public prototype_ `void OnRequestOpenAssets(const TArray<FAssetData>& SelectedAssets, bool bFromHistory);`
- L76 _public prototype_ `void OnRequestOpenAsset(const FAssetData& AssetData, bool bFromHistory);`
- L78 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L80 _public prototype_ `virtual ~SAnimationSequenceBrowser();`
- L83 _public prototype_ `virtual void SelectAsset(UAnimationAsset * AnimAsset) override;` — IAnimationSequenceBrowser interface
- L84 _public prototype_ `virtual void AddToHistory(UAnimationAsset* AnimAsset) override;`
- L85 _public prototype_ `virtual void FilterBySkeletonNotify(const FName& InNotifyName) override;`
- L88 _public prototype_ `TSharedPtr<SWidget> OnGetAssetContextMenu(const TArray<FAssetData>& SelectedAssets);` — Delegate that handles creation of context menu
- L91 _public prototype_ `void OpenInNewWindow(TArray<FAssetData> AnimationAssets);` — Delegate to open animation assets each in a new window
- L94 _public prototype_ `void FindInContentBrowser();` — Delegate to handle "Find in Content Browser" context menu option
- L97 _public prototype_ `bool CanFindInContentBrowser() const;` — Delegate to handle enabling the "Find in Content Browser" context menu option
- L100 _public prototype_ `void SaveSelectedAssets(TArray<FAssetData> ObjectsToSave) const;` — Delegate to handle "Save" context menu option
- L103 _public prototype_ `bool CanSaveSelectedAssets(TArray<FAssetData> ObjectsToSave) const;` — Delegate to handle enabling the "Save" context menu option
- L107 _public prototype_ `void OnApplyCompression(TArray<FAssetData> SelectedAssets);` — Delegate to handle compression context menu option Applies a chosen compression method to the selected assets
- L110 _public prototype_ `void OnExportToFBX(TArray<FAssetData> SelectedAssets);` — Delegate to handle Export FBX context menu option
- L113 _public prototype_ `void OnAddLoopingInterpolation(TArray<FAssetData> SelectedAssets);` — Delegate to handle Add looping interpolation context menu option
- L116 _public prototype_ `void OnSetCurrentPreviewMesh(TArray<FAssetData> SelectedAssets);` — Delegate to handle set current preview mesh context menu option
- L119 _public prototype_ `void OnReimportAnimation(TArray<FAssetData> SelectedAssets);` — Delegate to handle reimport selected animations
- L124 _public prototype_ `void OnCreateCopy(TArray<FAssetData> Selected);` — This will allow duplicate the current object, and remap to new skeleton Only allowed for AnimSequence
- L127 _protected prototype_ `bool CanShowColumnForAssetRegistryTag(FName AssetType, FName TagName) const;`
- L130 _protected prototype_ `void GetSelectedPackages(const TArray<FAssetData>& Assets, TArray<UPackage*>& OutPackages) const;` — Populate supplied OutPackages with the packages for the supplied Assets array
- L133 _protected prototype_ `void AddAssetToHistory(const FAssetData& AssetData);` — Adds the supplied asset to the asset history
- L135 _protected prototype_ `void CacheOriginalAnimAssetHistory();`
- L138 _protected prototype_ `FReply OnGoForwardInHistory();` — Single step forward in history
- L141 _protected prototype_ `FReply OnGoBackInHistory();` — Single step back in history
- L144 _protected prototype_ `void GoToHistoryIndex(int32 InHistoryIdx);` — Jumps immediately to an index in the history if valid
- L147 _protected prototype_ `bool CanStepBackwardInHistory() const;` — Returns TRUE if stepping backward in history is allowed
- L150 _protected prototype_ `bool CanStepForwardInHistory() const;` — Returns TRUE if stepping forward in history is allowed
- L157 _protected prototype_ `FReply OnMouseDownHistory( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent, TWeakPtr< SMenuAnchor > InMenuAnchor );` — Mouse down callback to display a history menu @param InMenuAnchor		This is the anchor the menu will use for positioning
- L166 _protected prototype_ `TSharedRef<SWidget> CreateHistoryMenu(bool bInBackHistory) const;` — Callback to create the history menu. @param bInBackHistory		TRUE if the back history is requested, FALSE if the forward history is @return						The menu widget displaying all available history
- L171 _protected prototype_ `void CreateAssetTooltipResources();` — Create the viewport and required objects to control the viewport used in tooltips
- L176 _protected prototype_ `TSharedRef<SToolTip> CreateCustomAssetToolTip(FAssetData& AssetData);` — Create a custom asset view tooltip for the provided asset
- L181 _protected prototype_ `bool OnVisualizeAssetToolTip(const TSharedPtr<SWidget>& TooltipContent, FAssetData& AssetData);` — Called as a tooltip is about to show;
- L186 _protected prototype_ `void OnAssetToolTipClosing();` — Called as a tooltip is closing
- L191 _protected prototype_ `void CleanupPreviewSceneComponent(USceneComponent* Component);` — Cleaup a component from the preview scene along with any attached children
- L196 _protected prototype_ `bool IsToolTipPreviewVisible();` — Has the animation asset preview tool tip been visualized
- L199 _protected prototype_ `EVisibility GetHistoryVisibility() const;` — Returns visible when not in a Blueprint mode (anim mode, etc...)
- L202 _protected prototype_ `bool HandleFilterAsset(const FAssetData& InAssetData) const;` — Perform additional filtering
- L205 _protected prototype_ `void HandlePlayAudio(FAssetData InAssetData);` — Handle playing audio from the right-click menu
- L208 _protected prototype_ `void HandleStopAudio();` — Handle stopping audio from the right-click menu
- L211 _protected prototype_ `void PlayPreviewAudio(USoundWave* InSoundWave);` — Play the specified sound on the preview audio component
- L217 _protected member_ `TSharedPtr<SViewport> ViewportWidget;` — The actual viewport widget
- L222 _protected member_ `TSharedPtr<FSceneViewport> SceneViewport;` — The scene viewport data
- L227 _protected member_ `TSharedPtr<FAnimationAssetViewportClient> ViewportClient;` — Custom viewport client used for tooltip previews
- L232 _protected member_ `UDebugSkelMeshComponent* PreviewComponent;` — Skeletal component to preview the animation asset on
- L237 _protected member_ `FPreviewScene PreviewScene;` — The scene to show in the asset previews
- L242 _protected member_ `TSharedPtr<FUICommandList> Commands;` — Commands handled by this widget
- L245 _protected member_ `TWeakPtr<class IPersonaToolkit> PersonaToolkitPtr;` — The persona toolkit we are using
- L248 _protected member_ `TSet<FName> AssetRegistryTagsToIgnore;` — Set of tags to prevent creating details view columns for (infrequently used)
- L251 _protected member_ `TArray<FAssetData> AssetHistory;` — List of recently opened assets
- L254 _protected member_ `int32 CurrentAssetHistoryIndex;` — Current position in the asset history
- L257 _protected member_ `static const int32 MaxAssetsHistory;` — Max assets to save in history
- L260 _protected member_ `bool bTriedToCacheOrginalAsset;` — Track if we have tried to cache the first asset we were playing
- L263 _protected member_ `bool bShowHistory;` — Whether to show the history widgets
- L266 _protected member_ `FOnOpenNewAsset OnOpenNewAsset;` — Delegate called to open a new asset for editing
- L269 _protected member_ `FSyncToAssetsDelegate SyncToAssetsDelegate;` — delegate to sync the asset picker to selected assets
- L270 _protected member_ `FGetCurrentSelectionDelegate GetCurrentSelectionDelegate;`
- L273 _protected member_ `FSetARFilterDelegate SetFilterDelegate;` — Delegate used to set the AR filter after the fact
- L276 _protected member_ `FARFilter Filter;` — Keep the AR filter around so we can modify it
- L279 _protected member_ `TArray<TSharedPtr<FFrontendFilter_Folder>> FolderFilters;` — All the folder filters we have
- L282 _protected member_ `TSharedPtr<FFrontendFilter_SkeletonNotify> SkeletonNotifyFilter;` — The skeleton notify filter
- L286 _private prototype_ `EActiveTimerReturnType UpdateTootipPreview( double InCurrentTime, float InDeltaTime );` — Updates the animation preview in the tooltip
- L289 _private member_ `uint8 bIsActiveTimerRegistered : 1;` — Whether the active timer is currently registered
- L293 _public member_ `static const FString SettingsIniSection;` — The section of EditorPerProjectUserSettings in which to save settings

### `Source/Editor/Persona/Private/SAssetFamilyShortcutBar.h` (Private)


#### class `SAssetFamilyShortcutBar`  
`class SAssetFamilyShortcutBar : public SCompoundWidget`  
_L13-39_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SAssetFamilyShortcutBar)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TSharedRef<class IAssetFamily>& InAssetFamily);`
- L24 _private prototype_ `void BuildShortcuts();`
- L26 _private prototype_ `void OnAssetFamilyChanged();`
- L29 _private member_ `TSharedPtr<class FAssetThumbnailPool> ThumbnailPool;` — The thumbnail pool for displaying asset shortcuts
- L32 _private member_ `TSharedPtr<SHorizontalBox> HorizontalBox;` — Container widget for shortcuts
- L35 _private member_ `TSharedPtr<IAssetFamily> AssetFamily;` — Asset family we represent
- L38 _private member_ `TWeakPtr<FWorkflowCentricApplication> WeakHostingApp;` — App we are embedded in

### `Source/Editor/Persona/Private/SMontageEditor.h` (Private)


#### struct `FMontageEditorRequiredArgs`  
`struct FMontageEditorRequiredArgs`  
_L20-33_
- L22 _public function_ `FMontageEditorRequiredArgs(const TSharedRef<class IPersonaPreviewScene>& InPreviewScene, const TSharedRef<class IEditableSkeleton>& InEditableSkeleton, FSimpleMulticastDelegate& InOnSectionsChanged, const TSharedRef<FUICommandList>& InCommandList) : PreviewScene(InPreviewScene) , EditableSkeleton(InEditableSkeleton) , OnSectionsChanged(InOnSectionsChanged) , CommandList(InCommandList)`
- L29 _public member_ `TSharedRef<class IPersonaPreviewScene> PreviewScene;`
- L30 _public member_ `TSharedRef<class IEditableSkeleton> EditableSkeleton;`
- L31 _public member_ `FSimpleMulticastDelegate& OnSectionsChanged;`
- L32 _public member_ `TSharedRef<FUICommandList> CommandList;`

#### class `SMontageEditor`  
`class SMontageEditor : public SAnimEditorBase`  
_L44-83_
- inherits: `SAnimEditorBase`
- desc: Overall animation montage editing widget. This mostly contains functions for editing the UAnimMontage. SMontageEditor will create the SAnimMontagePanel which is mostly responsible for setting up the UI portion of the Montage tool and registering callbacks to the SMontageEditor to do the actual editing.
- L47 _public function_ `SLATE_BEGIN_ARGS( SMontageEditor ) : _Montage(NULL)`
- L61 _private member_ `TSharedPtr<FAnimModel_AnimMontage> AnimModel;`
- L64 _public prototype_ `~SMontageEditor();`
- L66 _public prototype_ `void Construct(const FArguments& InArgs, const FMontageEditorRequiredArgs& InRequiredArgs);`
- L68 _public prototype_ `void SetMontageObj(UAnimMontage * NewMontage);`
- L69 _public function_ `UAnimMontage * GetMontageObj() const`
- L71 _public function_ `virtual UAnimationAsset* GetEditorObject() const override`
- L76 _private member_ `UAnimMontage* MontageObj;` — @todo fix this
- L81 _protected prototype_ `virtual TSharedRef<SWidget> CreateDocumentAnchor() override;`

### `Source/Editor/Persona/Private/SMorphTargetViewer.h` (Private)


#### class `FDisplayedMorphTargetInfo`  
`class FDisplayedMorphTargetInfo`  
_L21-55_
- L24 _public member_ `FName Name;`
- L25 _public member_ `float Weight;`
- L26 _public member_ `bool bAutoFillData;`
- L27 _public member_ `int32 NumberOfVerts;`
- L35 _public member_ `TArray<FMorphLodInfo> MorphLodInfos;`
- L38 _public function_ `static TSharedRef<FDisplayedMorphTargetInfo> Make(const FName& Source, int32 InNumberOfVerts, const TArray<FMorphLodInfo>& InMorphLodInfos)` — Static function for creating a new item, but ensures that you can only have a TSharedRef to one
- L45 _protected function_ `FDisplayedMorphTargetInfo(const FName& InSource, int32 InNumberOfVerts, const TArray<FMorphLodInfo>& InMorphLodInfos) : Name( InSource ) , Weight( 0 ) , bAutoFillData(true) , NumberOfVerts(InNumberOfVerts) , MorphLodInfos(InMorphLodInfos)` — Hidden constructor, always use Make above
- L54 _protected function_ `FDisplayedMorphTargetInfo()` — Hidden constructor, always use Make above

#### struct `FDisplayedMorphTargetInfo::FMorphLodInfo`  
`struct FMorphLodInfo`  
_L28-34_
- L30 _public member_ `FString SourceFilename;`
- L31 _public member_ `bool bIsGeneratedByEngine = false;`
- L32 _public member_ `int32 GeneratedFromLodIndex = INDEX_NONE;`
- L33 _public member_ `bool bIsValidLodMorph = false;`

#### class `SMorphTargetViewer`  
`class SMorphTargetViewer : public SCompoundWidget, public IMorphTargetViewer`  
_L62-227_
- inherits: `SCompoundWidget,IMorphTargetViewer`
- L65 _public function_ `SLATE_BEGIN_ARGS( SMorphTargetViewer )`
- L68 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene, FSimpleMulticastDelegate& OnPostUndo );`
- L79 _public prototype_ `virtual TArray<FName> GetSelectedMorphTargetNames() const override;` — IMorphTargetViewer overrides
- L80 _public prototype_ `virtual TSharedRef<SWidget> AsWidget() override;`
- L86 _public prototype_ `virtual ~SMorphTargetViewer();` — Destructor - resets the morph targets
- L94 _public prototype_ `void OnPreviewMeshChanged(class USkeletalMesh* OldPreviewMesh, class USkeletalMesh* NewPreviewMesh);` — Is registered with Persona to handle when its preview mesh is changed. @param NewPreviewMesh - The new preview mesh being used by Persona
- L99 _public prototype_ `void OnMorphTargetsChanged();` — Is registered with Persona to handle when its preview mesh morph targets has changed.
- L107 _public prototype_ `void OnFilterTextChanged( const FText& SearchText );` — Filters the SListView when the user changes the search text box (NameFilterBox) @param SearchText - The text the user has typed
- L117 _public prototype_ `void OnFilterTextCommitted( const FText& SearchText, ETextCommit::Type CommitInfo );` — Filters the SListView when the user hits enter or clears the search box Simply calls OnFilterTextChanged @param SearchText - The text the user has typed @param CommitInfo - Not used
- L127 _public prototype_ `TSharedRef<ITableRow> GenerateMorphTargetRow(TSharedPtr<FDisplayedMorphTargetInfo> InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Create a widget for an entry in the tree from an info @param InInfo - Shared pointer to the morph target we're generating a row for @param OwnerTable - The table that owns this row @return A new Slate widget, containing the UI for this row
- L136 _public prototype_ `void AddMorphTargetOverride( FName& Name, float Weight, bool bRemoveZeroWeight );` — Adds a morph target override or updates the weight for an existing one @param Name - Name of the morph target we want to override @param Weight - How much of this morph target to apply (0.0 - 1.0)
- L142 _public prototype_ `void ResetMorphTargets();` — Tells the AnimInstance to reset all of its morph target curves
- L148 _public prototype_ `bool CanPerformDelete() const;` — Provides state to the IsEnabled property of the delete morph targets button
- L153 _public prototype_ `void OnRenameMorphTargets();` — Handler for the rename morph targets button
- L158 _public prototype_ `void OnDeleteMorphTargets();` — Handler for the delete morph targets button
- L161 _public prototype_ `void OnCopyMorphTargetNames();` — Handler for copying morph taret names
- L164 _public prototype_ `FReply OnImportMorphTargetButton();` — Handler for importing a new morph target
- L165 _public prototype_ `void OnReimportMorphTargets(int32 LodIndex);`
- L166 _public prototype_ `void OnReimportMorphTargetsWithNewFile(int32 LodIndex);`
- L168 _public prototype_ `void InternalImportMorphTarget(int32 LodIndex, bool bWithNewFile, UMorphTarget* ReimportMorphTarget, bool bRecreateMorphTargetList);`
- L176 _public function_ `FText& GetFilterText()` — Accessor so our rows can grab the filtertext for highlighting
- L181 _public prototype_ `void OnPostUndo();` — Refreshes the morph target list after an undo
- L186 _public prototype_ `void OnMeshChanged();` — Refreshes the morph target list after a mesh changed
- L191 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuContent() const;` — Handler for context menus
- L194 _private prototype_ `void OnRowsSelectedChanged(TSharedPtr<FDisplayedMorphTargetInfo> Item, ESelectInfo::Type SelectInfo);` — Handler for row selection change
- L202 _private prototype_ `void CreateMorphTargetList( const FString& SearchText = FString() );` — Clears and rebuilds the table, according to an optional search string @param SearchText - Optional search string
- L205 _private prototype_ `void PreviewMorphTargets(const TArray<FName>& SelectedMorphTargetNames) const;` — Sets the selected morph target
- L208 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScenePtr;` — Pointer back to the Persona that owns us
- L211 _private member_ `TSharedPtr<SSearchBox> NameFilterBox;` — Box to filter to a specific morph target name
- L214 _private member_ `TSharedPtr<SMorphTargetListType> MorphTargetListView;` — Widget used to display the list of morph targets
- L217 _private member_ `TArray< TSharedPtr<FDisplayedMorphTargetInfo> > MorphTargetList;` — A list of morph targets. Used by the MorphTargetListView.
- L220 _private member_ `USkeletalMesh* SkeletalMesh;` — The skeletal mesh that we grab the morph targets from
- L223 _private member_ `FText FilterText;` — Current text typed into NameFilterBox
- L226 _private prototype_ `void NotifySelectionChange() const;` — notify selection change to Persona

#### Free symbols / members of external scopes

- L57 _typedef_ `typedef SListView< TSharedPtr<FDisplayedMorphTargetInfo> > SMorphTargetListType;`

### `Source/Editor/Persona/Private/SPersonaDetails.h` (Private)


#### class `SPersonaDetails`  
`class SPersonaDetails : public SCompoundWidget`  
_L11-27_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SPersonaDetails)`
- L17 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SWidget>, TopContent) SLATE_ARGUMENT(TSharedPtr<SWidget>, BottomContent) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Optional content to display above the details panel
- L26 _public member_ `TSharedPtr<class IDetailsView> DetailsView;`

### `Source/Editor/Persona/Private/SPoseEditor.h` (Private)


#### class `FDisplayedPoseInfo`  
`class FDisplayedPoseInfo`  
_L28-53_
- L31 _public member_ `FName Name;`
- L32 _public member_ `float Weight;`
- L35 _public function_ `static TSharedRef<FDisplayedPoseInfo> Make(const FName& Source)` — Static function for creating a new item, but ensures that you can only have a TSharedRef to one
- L41 _public prototype_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename
- L42 _public member_ `FOnRenameRequested OnRenameRequested;`
- L46 _protected function_ `FDisplayedPoseInfo(const FName& InSource) : Name(InSource) , Weight(0)` — Hidden constructor, always use Make above
- L52 _protected function_ `FDisplayedPoseInfo()` — Hidden constructor, always use Make above

#### class `SPoseListRow`  
`class SPoseListRow : public SMultiColumnTableRow< TSharedPtr<FDisplayedPoseInfo> >`  
_L60-129_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDisplayedPoseInfo>>`
- L64 _public function_ `SLATE_BEGIN_ARGS(SPoseListRow)`
- L67 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FDisplayedPoseInfo>, Item) SLATE_ARGUMENT(TWeakPtr<SPoseViewer>, PoseViewer) SLATE_ARGUMENT(FText, FilterText);` — The item for this row
- L75 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedRef<IPersonaPreviewScene>& InPreviewScene);`
- L80 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L90 _private prototype_ `void OnPoseWeightChanged(float NewWeight);` — Called when the user changes the value of the SSpinBox @param NewWeight - The new number the SSpinBox is set to
- L97 _private prototype_ `void OnPoseWeightValueCommitted(float NewWeight, ETextCommit::Type CommitType);` — Called when the user types the value and enters @param NewWeight - The new number the SSpinBox is set to
- L100 _private prototype_ `FText GetName() const;` — Delegate to get labels root text from settings
- L103 _private prototype_ `void OnNameCommitted(const FText& InText, ETextCommit::Type InCommitType) const;` — Delegate to commit labels root text to settings
- L105 _private prototype_ `bool OnVerifyNameChanged(const FText& InText, FText& OutErrorMessage);`
- L114 _private prototype_ `float GetWeight() const;` — Returns the weight of this morph target @return SearchText - The new number the SSpinBox is set to
- L116 _private prototype_ `bool CanChangeWeight() const;`
- L119 _private member_ `TWeakPtr<SPoseViewer> PoseViewerPtr;` — The SPoseViewer that we push the pose weights into
- L122 _private member_ `TSharedPtr<FDisplayedPoseInfo> Item;` — The name and weight of the morph target
- L125 _private member_ `FText FilterText;` — Text the user typed into the search box - used for text highlighting
- L128 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScenePtr;` — The preview scene we are viewing

#### class `FDisplayedCurveInfo`  
`class FDisplayedCurveInfo`  
_L134-153_
- L137 _public member_ `FName Name;`
- L140 _public function_ `static TSharedRef<FDisplayedCurveInfo> Make(const FName& Source)` — Static function for creating a new item, but ensures that you can only have a TSharedRef to one
- L147 _protected function_ `FDisplayedCurveInfo(const FName& InSource) : Name(InSource)` — Hidden constructor, always use Make above
- L152 _protected function_ `FDisplayedCurveInfo()` — Hidden constructor, always use Make above

#### class `SCurveListRow`  
`class SCurveListRow : public SMultiColumnTableRow< TSharedPtr<FDisplayedCurveInfo> >`  
_L161-193_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDisplayedCurveInfo>>`
- L165 _public function_ `SLATE_BEGIN_ARGS(SCurveListRow)`
- L168 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FDisplayedCurveInfo>, Item) SLATE_ARGUMENT(TWeakPtr<SPoseViewer>, PoseViewer) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);` — The item for this row
- L178 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L183 _private prototype_ `FText GetName() const;` — Delegate to get labels root text from settings
- L186 _private prototype_ `FText GetValue() const;` — Delegate to get weight of curve in selected pose
- L189 _private member_ `TSharedPtr<FDisplayedCurveInfo> Item;` — The name and weight of the morph target
- L192 _private member_ `TWeakPtr<SPoseViewer> PoseViewerPtr;` — The SPoseViewer that we push the morph target weights into

#### class `SPoseViewer`  
`class SPoseViewer : public SCompoundWidget`  
_L199-377_
- inherits: `SCompoundWidget`
- L202 _public function_ `SLATE_BEGIN_ARGS(SPoseViewer)`
- L205 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr< UPoseAsset >, PoseAsset) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<class IPersonaToolkit>& InPersonaToolkit, const TSharedRef<IEditableSkeleton>& InEditableSkeleton, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene);`
- L221 _public prototype_ `virtual ~SPoseViewer();` — Destructor - resets the animation curve
- L224 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — SWidget interface
- L232 _public prototype_ `void OnPreviewMeshChanged(class USkeletalMesh* OldPreviewMesh, class USkeletalMesh* NewPreviewMesh);` — Is registered with Persona to handle when its preview mesh is changed. @param NewPreviewMesh - The new preview mesh being used by Persona
- L240 _public prototype_ `void OnFilterTextChanged(const FText& SearchText);` — Filters the SListView when the user changes the search text box (NameFilterBox) @param SearchText - The text the user has typed
- L250 _public prototype_ `void OnFilterTextCommitted(const FText& SearchText, ETextCommit::Type CommitInfo);` — Filters the SListView when the user hits enter or clears the search box Simply calls OnFilterTextChanged @param SearchText - The text the user has typed @param CommitInfo - Not used
- L260 _public prototype_ `TSharedRef<ITableRow> GeneratePoseRow(TSharedPtr<FDisplayedPoseInfo> InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Create a widget for an entry in the tree from an info @param InInfo - Shared pointer to the morph target we're generating a row for @param OwnerTable - The table that owns this row @return A new Slate widget, containing the UI for this row
- L261 _public prototype_ `TSharedRef<ITableRow> GenerateCurveRow(TSharedPtr<FDisplayedCurveInfo> InInfo, const TSharedRef<STableViewBase>& OwnerTable);`
- L263 _public prototype_ `bool IsPoseSelected() const;`
- L264 _public prototype_ `bool IsSinglePoseSelected() const;`
- L265 _public prototype_ `bool IsCurveSelected() const;`
- L268 _public prototype_ `void OnDeletePoses();` — Handler for the delete poses option
- L271 _public prototype_ `void OnRenamePose();` — Handler for rename pose option
- L274 _public prototype_ `void OnDeleteCurves();` — Handler for delete curves option
- L277 _public prototype_ `void OnPastePoseNamesFromClipBoard(bool bSelectedOnly);` — Handler for pasting names from clipboard
- L285 _public prototype_ `void AddCurveOverride(const FName& Name, float Weight);` — Adds a morph target override or updates the weight for an existing one @param Name - Name of the morph target we want to override @param Weight - How much of this morph target to apply (0.0 - 1.0)
- L288 _public prototype_ `void RemoveCurveOverride(FName& Name);` — Remove a named curve override
- L294 _public function_ `FText& GetFilterText()` — Accessor so our rows can grab the filtertext for highlighting
- L299 _public prototype_ `void OnPoseAssetModified();` — Update pose asset changes - including list of poses or names or deletions
- L301 _public prototype_ `bool ModifyName(FName OldName, FName NewName, bool bSilence = false);`
- L302 _public prototype_ `bool IsBasePose(FName PoseName) const;`
- L305 _private prototype_ `void UpdateSelectedPoseWithCurrent();`
- L307 _private prototype_ `void AddPoseWithCurrent();`
- L308 _private prototype_ `void AddPoseWithReference();`
- L310 _private prototype_ `void BindCommands();`
- L311 _private prototype_ `void RestartPreviewComponent();`
- L314 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuContent();` — Handler for context menus
- L316 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuContentForCurveList() const;` — Handler for curve list context menu
- L318 _private prototype_ `void OnListDoubleClick(TSharedPtr<FDisplayedPoseInfo> InItem);` — Called when list double-clicked
- L319 _private prototype_ `bool IsNewPoseNameValid(FText& OutReason) const;`
- L326 _private prototype_ `void CreatePoseList(const FString& SearchText = FString());` — Clears and rebuilds the table, according to an optional search string @param SearchText - Optional search string
- L327 _private prototype_ `void CreateCurveList(const FString& SearchText = FString());`
- L329 _private prototype_ `void ApplyCustomCurveOverride(UAnimInstance* AnimInstance) const;`
- L332 _private prototype_ `UAnimInstance* GetAnimInstance() const;` — Get the anim instance we are viewing
- L335 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScenePtr;` — Pointer to the preview scene we are viewing
- L338 _private member_ `TWeakPtr<class IPersonaToolkit> PersonaToolkitPtr;` — Pointer to the persona toolkit we are embedded in
- L341 _private member_ `TWeakPtr<class IEditableSkeleton> EditableSkeletonPtr;` — Pointer to the editable skeleton we will need to modify
- L344 _private member_ `TWeakObjectPtr<UPoseAsset> PoseAssetPtr;` — Pointer to the pose asset
- L347 _private member_ `TSharedPtr<SSearchBox> NameFilterBox;` — Box to filter to a specific morph target name
- L350 _private member_ `TSharedPtr<SPoseListType> PoseListView;` — Widget used to display the list of animation curve
- L353 _private member_ `TArray< TSharedPtr<FDisplayedPoseInfo> > PoseList;` — A list of animation curve. Used by the PoseListView.
- L356 _private member_ `TSharedPtr<SCurveListType> CurveListView;` — Widget used to display the list of animation curve
- L359 _private member_ `TArray< TSharedPtr<FDisplayedCurveInfo> > CurveList;` — A list of animation curve. Used by the PoseListView.
- L361 _private member_ `FName NewPoseName;`
- L364 _private member_ `FText FilterText;` — Current text typed into NameFilterBox
- L367 _private member_ `TSharedPtr<FUICommandList> UICommandList;` — Commands that are bound to delegates
- L369 _private member_ `TMap<FName, float> OverrideCurves;`
- L372 _private member_ `FOnAddCustomAnimationCurves OnAddAnimationCurveDelegate;` — Add curve delegate
- L373 _private member_ `FDelegateHandle OnDelegatePoseListChangedDelegateHandle;`

#### class `SPoseEditor`  
`class SPoseEditor : public SAnimEditorBase`  
_L383-401_
- inherits: `SAnimEditorBase`
- desc: Overall animation sequence editing widget
- L386 _public function_ `SLATE_BEGIN_ARGS( SPoseEditor ) : _PoseAsset(NULL)`
- L394 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<class IPersonaToolkit>& InPersonaToolkit, const TSharedRef<IEditableSkeleton>& InEditableSkeleton, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene);`
- L396 _public function_ `virtual UAnimationAsset* GetEditorObject() const override`
- L400 _private member_ `UPoseAsset* PoseAssetObj;` — Pointer to the animation sequence being edited

#### Free symbols / members of external scopes

- L41 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename
- L55 _typedef_ `typedef SListView< TSharedPtr<FDisplayedPoseInfo> > SPoseListType;`
- L158 _typedef_ `typedef SListView< TSharedPtr<FDisplayedCurveInfo> > SCurveListType;`

### `Source/Editor/Persona/Private/SPoseWatchManager.h` (Private)


#### struct `PoseWatchManager::FPendingTreeOperation`  
`struct FPendingTreeOperation`  
_L56-66_
- desc: Structure that defines an operation that should be applied to the tree
- L59 _public function_ `FPendingTreeOperation(EType InType, TSharedRef<IPoseWatchManagerTreeItem> InItem) : Type(InType), Item(InItem)`
- L62 _public member_ `EType Type;` — The type of operation that is to be applied
- L65 _public member_ `FPoseWatchManagerTreeItemRef Item;` — The tree item to which this operation relates

#### enum `PoseWatchManager::FPendingTreeOperation::EType`  
`enum EType`  
_L58-58_
- L58 _public enumerator_ `enum EType { Added, Removed, Moved }; FPendingTreeOperation(EType InType, TSharedRef<IPoseWatchManagerTreeItem> InItem) : Type(InType)`
- L58 _public enumerator_ `enum EType { Added, Removed, Moved }; FPendingTreeOperation(EType InType, TSharedRef<IPoseWatchManagerTreeItem> InItem) : Type(InType)`
- L58 _public enumerator_ `enum EType { Added, Removed, Moved }; FPendingTreeOperation(EType InType, TSharedRef<IPoseWatchManagerTreeItem> InItem) : Type(InType)`

#### enum `PoseWatchManager::ENewItemAction::Type`  
`enum Type`  
_L71-81_
- L74 _public enumerator_ `None = 0` — Do nothing when it is created
- L76 _public enumerator_ `Select = 1 << 0` — Select the item when it is created
- L78 _public enumerator_ `ScrollIntoView = 1 << 1` — Scroll the item into view when it is created
- L80 _public enumerator_ `Rename = 1 << 2` — Interactively rename the item when it is created (implies the above)

#### class `SPoseWatchManager`  
`class SPoseWatchManager : public IPoseWatchManager, public FGCObject`  
_L85-415_
- inherits: `IPoseWatchManager,FGCObject`
- L88 _public function_ `SLATE_BEGIN_ARGS(SPoseWatchManager)`
- L90 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FPoseWatchManagerInitializationOptions& InitOptions);`
- L94 _public prototype_ `SPoseWatchManager();`
- L95 _public prototype_ `virtual ~SPoseWatchManager();`
- L98 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L99 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L100 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L103 _public prototype_ `virtual void Refresh() override;` — Sends a requests to refresh the next chance it gets
- L105 _public prototype_ `void RefreshSelection();`
- L108 _public function_ `virtual const STreeView<FPoseWatchManagerTreeItemPtr>& GetTree() const override` — Get a const reference to the actual tree hierarchy
- L113 _public function_ `virtual const TSharedPtr<SPoseWatchManagerTreeView>& GetTreeView() const`
- L119 _public prototype_ `virtual TAttribute<FText> GetFilterHighlightText() const;` — @return Returns a string to use for highlighting results in the list
- L122 _public prototype_ `virtual void SetKeyboardFocus() override;` — Set the keyboard focus to the manager
- L124 _public prototype_ `void SetColumnVisibility(FName ColumnId, bool bIsVisible);`
- L127 _public prototype_ `virtual EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;` — Returns the current sort mode of the specified column
- L130 _public prototype_ `virtual void RequestSort();` — Request that the tree be sorted at a convenient time
- L133 _public prototype_ `virtual void FullRefresh() override;` — Requests a full refresh, which will clear the entire tree and rebuild it from scratch
- L137 _public function_ `PoseWatchManager::FTreeItemPtrEvent& GetDoubleClickEvent()` — Event to react to a user double click on a item
- L139 _public function_ `PoseWatchManager::FOnItemSelectionChanged& GetOnItemSelectionChanged()`
- L142 _public prototype_ `virtual void SetSelection(const TFunctionRef<bool(IPoseWatchManagerTreeItem&)> Selector) override;` — Set the item selection of the manager based on a selector function. Any items which return true will be added
- L145 _public prototype_ `void SetItemSelection(const TArray<FPoseWatchManagerTreeItemPtr>& InItems, bool bSelected, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Set the selection status of a set of items in the scene manager
- L148 _public prototype_ `void SetItemSelection(const FPoseWatchManagerTreeItemPtr& InItem, bool bSelected, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);` — Set the selection status of a single item in the scene manager
- L151 _public function_ `virtual FPoseWatchManagerTreeItemPtr GetSelection() const`
- L153 _public prototype_ `FPoseWatchManagerTreeItemPtr FindParent(const IPoseWatchManagerTreeItem& InItem) const;`
- L156 _public prototype_ `void ClearSelection();` — Deselect all selected items
- L159 _public function_ `void SetPendingRenameItem(const FPoseWatchManagerTreeItemPtr& InItem)` — Sets the next item to rename
- L162 _public prototype_ `FPoseWatchManagerTreeItemPtr GetTreeItem(FObjectKey, bool bIncludePending = false);` — Retrieve an IPoseWatchManagerTreeItem by its ID if it exists in the tree
- L165 _public prototype_ `TSharedPtr<FDragDropOperation> CreateDragDropOperation(const TArray<FPoseWatchManagerTreeItemPtr>& InTreeItems) const;` — Create a drag drop operation
- L168 _public prototype_ `bool ParseDragDrop(FPoseWatchManagerDragDropPayload& OutPayload, const FDragDropOperation& Operation) const;` — Parse a drag drop operation into a payload
- L171 _public prototype_ `FPoseWatchManagerDragValidationInfo ValidateDrop(const IPoseWatchManagerTreeItem& DropTarget, const FPoseWatchManagerDragDropPayload& Payload) const;` — Validate a drag drop operation on a drop target
- L174 _public prototype_ `void OnDropPayload(IPoseWatchManagerTreeItem& DropTarget, const FPoseWatchManagerDragDropPayload& Payload, const FPoseWatchManagerDragValidationInfo& ValidationInfo) const;` — Called when a payload is dropped onto a target
- L177 _public prototype_ `FReply OnDragOverItem(const FDragDropEvent& Event, const IPoseWatchManagerTreeItem& Item) const;` — Called when a payload is dragged over an item
- L179 _public prototype_ `virtual uint32 GetTypeSortPriority(const IPoseWatchManagerTreeItem& Item) const;`
- L183 _public function_ `bool GetIsReentrant() const` — Used to test if manager related selection changes have already been handled
- L187 _private prototype_ `void EmptyTreeItems();` — Empty all the tree item containers maintained by this manager
- L190 _private prototype_ `void Populate();` — Apply incremental changes to, or a complete repopulation of the tree
- L193 _private prototype_ `void RepopulateEntireTree();` — Repopulates the entire tree
- L196 _private prototype_ `void AddPendingItem(FPoseWatchManagerTreeItemPtr Item);` — Adds a single new item to the pending map and creates an add operation for it
- L199 _private prototype_ `void AddPendingItemAndChildren(FPoseWatchManagerTreeItemPtr Item);` — Adds a new item and all of its children to the pending items.
- L202 _private prototype_ `bool AddItemToTree(FPoseWatchManagerTreeItemRef InItem);` — Attempts to add a pending item to the current tree. Will add any parents if required.
- L205 _private prototype_ `void AddUnfilteredItemToTree(FPoseWatchManagerTreeItemRef Item);` — Add an item to the tree, even if it doesn't match the filter terms. Used to add parent's that would otherwise be filtered out
- L208 _private prototype_ `FPoseWatchManagerTreeItemPtr EnsureParentForItem(FPoseWatchManagerTreeItemRef Item);` — Ensure that the specified item's parent is added to the tree, if applicable
- L213 _public function_ `template <typename TreeItemType, typename TreeItemData> FPoseWatchManagerTreeItemPtr CreateItemFor(const TreeItemData& Data, bool bForce = false)` — Test the filters using stack-allocated data to prevent unnecessary heap allocations
- L227 _public prototype_ `void OnItemAdded(const FObjectKey& ItemID, uint8 ActionMask);` — Instruct the manager to perform an action on the specified item when it is created
- L229 _public prototype_ `void OnPoseWatchesChanged(UAnimBlueprint* InAnimBlueprint, UEdGraphNode* InNode);`
- L231 _public prototype_ `virtual void Rename_Execute() override;`
- L233 _public prototype_ `virtual void Delete_Execute();`
- L236 _public function_ `const TMap<FName, TSharedPtr<IPoseWatchManagerColumn>>& GetColumns() const` — Get the columns to be displayed in this manager
- L242 _public prototype_ `bool IsTextFilterActive() const;` — @return	Returns true if the text filter is currently active
- L244 _public function_ `bool PassesTextFilter(const FPoseWatchManagerTreeItemPtr& Item) const`
- L249 _public function_ `bool HasSelectorFocus(FPoseWatchManagerTreeItemPtr Item) const`
- L256 _private member_ `TMap<FName, TSharedPtr<IPoseWatchManagerColumn>> Columns;` — Map of columns that are shown on this manager.
- L259 _private prototype_ `void SetupColumns(SHeaderRow& HeaderRow);` — Set up the columns required for this manager
- L262 _private prototype_ `void RefreshColumns();` — Refresh the scene manager for when a column was added or removed
- L265 _private prototype_ `void PopulateSearchStrings(const IPoseWatchManagerTreeItem& Item, TArray< FString >& OutSearchStrings) const;` — Populates OutSearchStrings with the strings associated with TreeItem that should be used in searching
- L269 _public prototype_ `void ScrollItemIntoView(const FPoseWatchManagerTreeItemPtr& Item);` — Scroll the specified item into view
- L273 _private prototype_ `TSharedRef< ITableRow > OnGenerateRowForManagerTree(FPoseWatchManagerTreeItemPtr Item, const TSharedRef< STableViewBase >& OwnerTable);` — Called by STreeView to generate a table row for the specified item
- L276 _private prototype_ `void OnGetChildrenForManagerTree(FPoseWatchManagerTreeItemPtr InParent, TArray< FPoseWatchManagerTreeItemPtr >& OutChildren);` — Called by STreeView to get child items for the specified parent item
- L279 _private prototype_ `void OnManagerTreeSelectionChanged(FPoseWatchManagerTreeItemPtr TreeItem, ESelectInfo::Type SelectInfo);` — Called by STreeView when the tree's selection has changed
- L282 _private prototype_ `void OnManagerTreeItemScrolledIntoView(FPoseWatchManagerTreeItemPtr TreeItem, const TSharedPtr<ITableRow>& Widget);` — Called by STreeView when an item is scrolled into view
- L284 _private prototype_ `void OnManagerTreeDoubleClick(FPoseWatchManagerTreeItemPtr TreeItem);`
- L287 _private prototype_ `void OnItemExpansionChanged(FPoseWatchManagerTreeItemPtr TreeItem, bool bIsExpanded) const;` — Called when an item in the tree has been collapsed or expanded
- L291 _private prototype_ `void OnHierarchyChangedEvent(FPoseWatchManagerHierarchyChangedData Event);` — Event required to keep the pose watch manager up to date
- L295 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);` — Called by the editable text control when the filter text is changed by the user
- L298 _private prototype_ `const FSlateBrush* GetFilterButtonGlyph() const;` — Called by the filter button to get the image to display in the button
- L301 _private prototype_ `FString GetFilterButtonToolTip() const;` — @return	The filter button tool-tip text
- L304 _private prototype_ `EVisibility GetFilterStatusVisibility() const;` — @return	Returns whether the filter status line should be drawn
- L307 _private prototype_ `EVisibility GetEmptyLabelVisibility() const;` — Returns the current visibility of the Empty label
- L310 _private prototype_ `ESelectionMode::Type GetSelectionMode() const;` — Returns the selection mode
- L314 _private prototype_ `TSharedPtr<SWidget> OnOpenContextMenu();` — Called when the user right clicks in the tree view
- L317 _private prototype_ `FReply OnCreateFolderClicked();` — Called when the user has clicked the button to add a new folder
- L320 _private prototype_ `void CreateFolder();` — Requests a new folder be created, confirmation received with OnHierarchyChangedEvent
- L323 _private prototype_ `void BindCommands();` — Binds our UI commands to delegates.
- L327 _private member_ `FOnContextMenuOpening OnContextMenuOpening;` — Context menu opening delegate provided by the client
- L330 _private member_ `TArray<PoseWatchManager::FPendingTreeOperation> PendingOperations;` — List of pending operations to be applied to the tree
- L333 _private member_ `TMap<FObjectKey, uint8> NewItemActions;` — Map of actions to apply to new tree items
- L336 _private member_ `TSharedPtr< SPoseWatchManagerTreeView > PoseWatchManagerTreeView;` — Our tree view
- L339 _private member_ `FPoseWatchManagerTreeItemMap TreeItemMap;` — A map of all items we have in the tree
- L342 _private member_ `FPoseWatchManagerTreeItemMap PendingTreeItemMap;` — Pending tree items that are yet to be added the tree
- L345 _private member_ `TArray<FPoseWatchManagerTreeItemPtr> RootTreeItems;` — Root level tree items
- L347 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L350 _private member_ `uint8 bNeedsRefresh : 1;` — true if the manager  needs to be repopulated at the next appropriate opportunity
- L353 _private member_ `uint8 bProcessingFullRefresh : 1;` — Processing a full refresh until pending items are processed
- L356 _private member_ `uint8 bFullRefresh : 1;` — true if should do a full refresh
- L359 _private member_ `uint8 bSelectionDirty : 1;` — true if should refresh selection
- L361 _private member_ `uint8 bNeedsColumnRefresh : 1;`
- L364 _private member_ `bool bIsReentrant;` — Reentrancy guard
- L367 _private member_ `TSharedPtr< SSearchBox > FilterTextBoxWidget;` — Widget containing the filtering text box
- L370 _private member_ `TSharedPtr< SHeaderRow > HeaderRowWidget;` — The header row of the manager
- L373 _private member_ `TSharedPtr< PoseWatchManager::TreeItemTextFilter > SearchBoxFilter;` — The TextFilter attached to the SearchBox widget
- L376 _private member_ `bool bPendingFocusNextFrame;` — True if the search box will take keyboard focus next frame
- L379 _private member_ `TWeakPtr<IPoseWatchManagerTreeItem> PendingRenameItem;` — The tree item that is currently pending a rename
- L381 _private member_ `TUniquePtr<FPoseWatchManagerDefaultHierarchy> Hierarchy;`
- L383 _private member_ `PoseWatchManager::FTreeItemPtrEvent OnDoubleClickOnTreeEvent;`
- L385 _private member_ `PoseWatchManager::FOnItemSelectionChanged OnItemSelectionChanged;`
- L388 _private function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L389 _private function_ `virtual FString GetReferencerName() const override`
- L394 _private member_ `bool bDisableIntermediateSorting;`
- L397 _private member_ `bool bSortDirty;` — true if currently needs to be sorted
- L400 _private member_ `FName SortByColumn;` — Specify which column to sort with
- L403 _private member_ `EColumnSortMode::Type SortMode;` — Currently selected sorting mode
- L405 _private member_ `FBlueprintEditor* BlueprintEditor;`
- L408 _private prototype_ `void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);` — Handles column sorting mode change
- L411 _private prototype_ `void SortItems(TArray<FPoseWatchManagerTreeItemPtr>& Items) const;` — Sort the specified array of items based on the current sort column
- L414 _private prototype_ `void SetItemExpansionRecursive(FPoseWatchManagerTreeItemPtr Model, bool bInExpansionState);` — Handler for recursively expanding/collapsing items

#### Free symbols / members of external scopes

- L47 _namespace_ `namespace PoseWatchManager`
- L49 _delegate_ `DECLARE_EVENT_OneParam(SPoseWatchManager, FTreeItemPtrEvent, FPoseWatchManagerTreeItemPtr);`
- L49 _prototype_ `DECLARE_EVENT_OneParam(SPoseWatchManager, FTreeItemPtrEvent, FPoseWatchManagerTreeItemPtr);` (scope `PoseWatchManager`)
- L51 _delegate_ `DECLARE_EVENT_TwoParams(SPoseWatchManager, FOnItemSelectionChanged, FPoseWatchManagerTreeItemPtr, ESelectInfo::Type);`
- L51 _prototype_ `DECLARE_EVENT_TwoParams(SPoseWatchManager, FOnItemSelectionChanged, FPoseWatchManagerTreeItemPtr, ESelectInfo::Type);` (scope `PoseWatchManager`)
- L53 _typedef_ `typedef TTextFilter<const IPoseWatchManagerTreeItem&> TreeItemTextFilter;` (scope `PoseWatchManager`)
- L69 _namespace_ `namespace ENewItemAction` (scope `PoseWatchManager`)

### `Source/Editor/Persona/Private/SPoseWatchManagerTreeView.h` (Private)


#### class `SPoseWatchManagerTreeView`  
`class SPoseWatchManagerTreeView : public STreeView< FPoseWatchManagerTreeItemPtr >`  
_L16-35_
- inherits: `STreeView<FPoseWatchManagerTreeItemPtr>`
- L19 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<SPoseWatchManager> Owner);`
- L21 _public prototype_ `void FlashHighlightOnItem(FPoseWatchManagerTreeItemPtr FlashHighlightOnItem);`
- L23 _public function_ `const TWeakPtr<SPoseWatchManager>& GetPoseWatchManagerPtr()`
- L28 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L30 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L32 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L34 _protected member_ `TWeakPtr<SPoseWatchManager> PoseWatchManagerWeak;`

#### class `SPoseWatchManagerTreeRow`  
`class SPoseWatchManagerTreeRow : public SMultiColumnTableRow< FPoseWatchManagerTreeItemPtr >`  
_L37-107_
- inherits: `SMultiColumnTableRow<FPoseWatchManagerTreeItemPtr>`
- L41 _public function_ `SLATE_BEGIN_ARGS(SPoseWatchManagerTreeRow)`
- L42 _public prototype_ `SLATE_ARGUMENT(FPoseWatchManagerTreeItemPtr, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SPoseWatchManagerTreeView>& PoseWatchManagerTreeView, TSharedRef<SPoseWatchManager> PoseWatchManager);`
- L49 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L51 _public prototype_ `void FlashHighlight();`
- L54 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L56 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L58 _protected prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L60 _protected prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L62 _protected prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L64 _protected prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L69 _private member_ `TWeakPtr< SPoseWatchManager > PoseWatchManagerWeak;` — Weak reference to the outliner widget that owns our list
- L72 _private member_ `TWeakPtr<IPoseWatchManagerTreeItem> Item;` — The item associated with this row of data
- L76 _protected prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L78 _protected prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L82 _private member_ `static const float HighlightRectLeftOffset;` — How many pixels to extend the highlight rectangle's left side horizontally
- L85 _private member_ `static const float HighlightRectRightOffset;` — How many pixels to extend the highlight rectangle's right side horizontally
- L88 _private member_ `static const float HighlightTargetSpringConstant;` — How quickly the highlight 'targeting' rectangle will slide around.  Larger is faster.
- L91 _private member_ `static const float HighlightTargetEffectDuration;` — Duration of animation highlight target effects
- L94 _private member_ `static const float HighlightTargetOpacity;` — Opacity of the highlight target effect overlay
- L97 _private member_ `static const float LabelChangedAnimOffsetPercent;` — How large the highlight target effect will be when highlighting, as a scalar percentage of font height
- L100 _private member_ `FFloatSpring1D HighlightTargetLeftSpring;` — Highlight "targeting" visual effect left position
- L103 _private member_ `FFloatSpring1D HighlightTargetRightSpring;` — Highlight "targeting" visual effect right position
- L106 _private member_ `double LastHighlightInteractionTime;` — Last time that the user had a major interaction with the highlight

### `Source/Editor/Persona/Private/SPoseWatchPicker.h` (Private)


#### class `SPoseWatchPicker`  
`class SPoseWatchPicker : public SCompoundWidget`  
_L11-31_
- inherits: `SCompoundWidget`
- L13 _private function_ `SLATE_BEGIN_ARGS(SPoseWatchPicker) : _AnimBlueprintGeneratedClass(nullptr)`
- L14 _private prototype_ `SLATE_ATTRIBUTE(const UAnimBlueprintGeneratedClass*, AnimBlueprintGeneratedClass) SLATE_ARGUMENT(FText, DefaultEntryDisplayText) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L20 _private prototype_ `UPoseWatchPoseElement* GetCurrentPoseWatch() const;`
- L23 _protected prototype_ `void OnPoseWatchesChanged(UAnimBlueprint* InAnimBlueprint, UEdGraphNode* );`
- L24 _protected prototype_ `void RebuildPoseWatches();`
- L27 _protected member_ `TSharedPtr<SComboBox<TSharedPtr<TWeakObjectPtr<UPoseWatchPoseElement>>>> PoseWatchComboBox;`
- L28 _protected member_ `TArray<TSharedPtr<TWeakObjectPtr<UPoseWatchPoseElement>>> CachedPoseWatches;`
- L29 _protected member_ `TAttribute<const UAnimBlueprintGeneratedClass*> AnimBlueprintAttribute;`
- L30 _protected member_ `TWeakObjectPtr<UPoseWatchPoseElement> SelectedPoseWatch = nullptr;`

### `Source/Editor/Persona/Private/SRenameMorphTargetDialog.h` (Private)


#### class `SRenameMorphTargetDialog`  
`class SRenameMorphTargetDialog : public SCompoundWidget`  
_L14-57_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SRenameMorphTargetDialog) : _SkeletalMesh(nullptr) , _MorphTarget(nullptr) , _Padding(FMargin(15))`
- L24 _public prototype_ `SLATE_ARGUMENT(TObjectPtr<USkeletalMesh>, SkeletalMesh) SLATE_ARGUMENT(TObjectPtr<UMorphTarget>, MorphTarget) SLATE_ARGUMENT(FMargin, Padding) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _private prototype_ `FReply OnRenameClicked();` — Renames the morph target based on dialog parameters
- L37 _private prototype_ `FReply OnCancelClicked();` — Callback for when Cancel is clicked
- L40 _private prototype_ `bool OnVerifyNameChanged(const FText& InText, FText& OutErrorMessage);` — Callback to verify the rename is good
- L43 _private prototype_ `void RenameAndClose();` — Renames the morph target and attempts to close the active window
- L46 _private prototype_ `void OnRenameTextCommitted(const FText& InText, ETextCommit::Type InCommitType);` — Attempts to rename the morph target if enter is pressed while editing the morph target name
- L49 _private prototype_ `void CloseContainingWindow();` — Closes the window that contains this widget
- L52 _private member_ `TObjectPtr<USkeletalMesh> SkeletalMesh = nullptr;`
- L54 _private member_ `TObjectPtr<UMorphTarget> MorphTarget = nullptr;`
- L56 _private member_ `TSharedPtr<SEditableTextBox> NewMorphTargetNameTextBox;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ETextCommit`

### `Source/Editor/Persona/Private/SRetargetSourceWindow.h` (Private)


#### class `FDisplayedRetargetSourceInfo`  
`class FDisplayedRetargetSourceInfo`  
_L21-74_
- L24 _public member_ `FName Name;`
- L25 _public member_ `TSoftObjectPtr<USkeletalMesh> ReferenceMesh;`
- L28 _public function_ `static TSharedRef<FDisplayedRetargetSourceInfo> Make(const FName& SourcePose, TSoftObjectPtr<USkeletalMesh> InReferenceMesh, bool bInDirtyFlag)` — Static function for creating a new item, but ensures that you can only have a TSharedRef to one
- L33 _public function_ `FString GetDisplayName()`
- L42 _public function_ `FString GetReferenceMeshName()`
- L51 _public function_ `void RequestRename()` — Requests a rename on the socket item
- L57 _public prototype_ `DECLARE_DELEGATE(FOnEnterEditingMode);` — Delegate for when the context menu requests a rename
- L58 _public member_ `FOnEnterEditingMode OnEnterEditingMode;`
- L62 _protected function_ `FDisplayedRetargetSourceInfo(const FName& InSource, TSoftObjectPtr<USkeletalMesh> InRefMesh, bool InDirtyFlag) : Name( InSource ) , ReferenceMesh( InRefMesh ) , bRenamePending( false ) , bDirtyFlag(InDirtyFlag)` — Hidden constructor, always use Make above
- L70 _protected function_ `FDisplayedRetargetSourceInfo()` — Hidden constructor, always use Make above
- L72 _protected member_ `bool bRenamePending;`
- L73 _protected member_ `bool bDirtyFlag;`

#### class `SRetargetSourceWindow`  
`class SRetargetSourceWindow : public SCompoundWidget`  
_L81-228_
- inherits: `SCompoundWidget`
- L84 _public function_ `SLATE_BEGIN_ARGS( SRetargetSourceWindow )`
- L87 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<class IEditableSkeleton>& InEditableSkeleton, FSimpleMulticastDelegate& InOnPostUndo);`
- L103 _public prototype_ `void OnFilterTextChanged( const FText& SearchText );` — Filters the SListView when the user changes the search text box (NameFilterBox) @param SearchText - The text the user has typed
- L113 _public prototype_ `void OnFilterTextCommitted( const FText& SearchText, ETextCommit::Type CommitInfo );` — Filters the SListView when the user hits enter or clears the search box Simply calls OnFilterTextChanged @param SearchText - The text the user has typed @param CommitInfo - Not used
- L123 _public prototype_ `TSharedRef<ITableRow> GenerateRetargetSourceRow(TSharedPtr<FDisplayedRetargetSourceInfo> InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Create a widget for an entry in the tree from an info @param InInfo - Shared pointer to the morph target we're generating a row for @param OwnerTable - The table that owns this row @return A new Slate widget, containing the UI for this row
- L128 _public prototype_ `void OnAddRetargetSource();` — Handler for adding new retarget source. It displays the asset picker
- L133 _public prototype_ `void OnAssetSelectedFromMeshPicker(const FAssetData& AssetData);` — Callback for asset picker
- L142 _public prototype_ `void AddRetargetSource( const FName Name, USkeletalMesh * ReferenceMesh );` — Adds a new retarget source with given name @param Name - Name of retarget source @param ReferenceMesh	- Reference Mesh this pose is based on
- L148 _public prototype_ `bool CanPerformDelete() const;` — Return true if it can delete
- L153 _public prototype_ `void OnDeleteRetargetSource();` — Handler for the delete of retarget source
- L159 _public prototype_ `bool CanPerformRename() const;` — Return true if it can perform rename
- L164 _public prototype_ `void OnRenameRetargetSource();` — Handler for the rename of retarget source
- L170 _public prototype_ `bool CanPerformRefresh() const;` — Return true if it can delete
- L175 _public prototype_ `void OnRefreshRetargetSource(bool bAll = false);` — Handler for the delete of retarget source
- L181 _public function_ `FText& GetFilterText()` — Accessor so our rows can grab the filtertext for highlighting
- L184 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;` — SWidget interface
- L189 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuContent() const;` — Handler for context menus
- L197 _private prototype_ `void CreateRetargetSourceList( const FString& SearchText = FString(""), const FName NewName = NAME_None );` — Clears and rebuilds the table, according to an optional search string @param SearchText - Optional search string
- L200 _private member_ `TWeakPtr<class IEditableSkeleton> EditableSkeletonPtr;` — The editable skeleton
- L203 _private member_ `TSharedPtr<SSearchBox> NameFilterBox;` — Box to filter to a specific morph target name
- L206 _private member_ `TSharedPtr<SRetargetSourceListType> RetargetSourceListView;` — Widget used to display the list of retarget sources
- L209 _private member_ `TArray< TSharedPtr<FDisplayedRetargetSourceInfo> > RetargetSourceList;` — A list of retarget sources. Used by the RetargetSourceListView.
- L212 _private member_ `FText FilterText;` — Current text typed into NameFilterBox
- L215 _private member_ `mutable TSharedPtr<FDisplayedRetargetSourceInfo> ItemToRename;` — Item to rename. Only valid for adding
- L218 _private prototype_ `void OnRenameCommit(const FName& InOldName, const FString& InNewName);` — Rename committed. Called by Inline Widget
- L220 _private prototype_ `bool OnVerifyRenameCommit( const FName& OldName, const FString& NewName, FText& OutErrorMessage);` — Verify Rename is legit or not
- L223 _private prototype_ `void PostUndo();` — Delegate for undo/redo transaction
- L226 _private prototype_ `FReply OnAddRetargetSourceButtonClicked();` — Button handler
- L227 _private prototype_ `FReply OnUpdateAllRetargetSourceButtonClicked();`

#### class `SCompatibleSkeletons`  
`class SCompatibleSkeletons : public SCompoundWidget`  
_L230-254_
- inherits: `SCompoundWidget`
- L233 _public function_ `SLATE_BEGIN_ARGS( SCompatibleSkeletons )`
- L234 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<class IEditableSkeleton>& InEditableSkeleton, FSimpleMulticastDelegate& InOnPostUndo);`
- L238 _public prototype_ `FReply OnAddSkeletonClicked();`
- L240 _public prototype_ `FReply OnRemoveSkeletonClicked();`
- L242 _public prototype_ `TSharedRef<ITableRow> GenerateRowForItem(TSharedRef<FSoftObjectPath> Item, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L244 _public prototype_ `void OnAssetSelectedFromSkeletonPicker(const FAssetData& AssetData);`
- L247 _private prototype_ `void UpdateCompatibleSkeletonAssets(const USkeleton& Skeleton);`
- L249 _private member_ `TArray<TSharedRef<FSoftObjectPath>> CompatibleSkeletonAssets;`
- L251 _private member_ `TSharedPtr<SListView<TSharedRef<FSoftObjectPath>>> CompatibleSkeletonListView;`
- L253 _private member_ `TWeakPtr<IEditableSkeleton> EditableSkeletonPtr;`

#### Free symbols / members of external scopes

- L57 _delegate_ `DECLARE_DELEGATE(FOnEnterEditingMode);` — Delegate for when the context menu requests a rename
- L76 _typedef_ `typedef SListView< TSharedPtr<FDisplayedRetargetSourceInfo> > SRetargetSourceListType;`

### `Source/Editor/Persona/Private/SRetargetSources.h` (Private)


#### class `SRetargetSources`  
`class SRetargetSources : public SCompoundWidget`  
_L14-29_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS( SRetargetSources )`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<class IEditableSkeleton>& InEditableSkeleton, FSimpleMulticastDelegate& InOnPostUndo);`
- L28 _private member_ `TWeakPtr<class IEditableSkeleton> EditableSkeletonWeakPtr;`

### `Source/Editor/Persona/Private/SSequenceEditor.h` (Private)


#### class `SSequenceEditor`  
`class SSequenceEditor : public SAnimEditorBase, public FEditorUndoClient`  
_L21-55_
- inherits: `SAnimEditorBase,FEditorUndoClient`
- desc: Overall animation sequence editing widget
- L24 _public function_ `SLATE_BEGIN_ARGS( SSequenceEditor ) : _Sequence(NULL)`
- L36 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScenePtr;`
- L37 _private member_ `TSharedPtr<FAnimModel_AnimSequenceBase> AnimModel;`
- L39 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<class IPersonaPreviewScene> InPreviewScene, TSharedRef<class IEditableSkeleton> InEditableSkeleton, const TSharedRef<FUICommandList>& InCommandList);`
- L41 _public prototype_ `~SSequenceEditor();`
- L43 _public function_ `virtual UAnimationAsset* GetEditorObject() const override`
- L47 _private member_ `UAnimSequenceBase* SequenceObj;` — Pointer to the animation sequence being edited
- L50 _private prototype_ `virtual void PostUndo( bool bSuccess ) override;` — FEditorUndoClient interface
- L51 _private prototype_ `virtual void PostRedo( bool bSuccess ) override;`
- L54 _private prototype_ `void PostUndoRedo();` — Post undo

### `Source/Editor/Persona/Private/SSkeletonAnimNotifies.h` (Private)


#### struct `FSkeletonAnimNotifiesSummoner`  
`struct FSkeletonAnimNotifiesSummoner : public FWorkflowTabFactory`  
_L29-45_
- inherits: `FWorkflowTabFactory`
- desc: FSkeletonAnimNotifiesSummoner
- L32 _public prototype_ `FSkeletonAnimNotifiesSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, const TSharedRef<class IEditableSkeleton>& InEditableSkeleton, FOnObjectsSelected InOnObjectsSelected);`
- L34 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L37 _public function_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override` — Create a tooltip widget for the tab
- L43 _private member_ `TWeakPtr<class IEditableSkeleton> EditableSkeleton;`
- L44 _private member_ `FOnObjectsSelected OnObjectsSelected;`

#### enum `EAnimNotifyFilterFlags`  
`enum class EAnimNotifyFilterFlags : uint8`  
_L48-62_
- desc: This is a flag that is used to filter UI part
- L51 _public enumerator_ `None = 0` — Show none
- L53 _public enumerator_ `Notifies = 0x01` — Show notifies
- L55 _public enumerator_ `SyncMarkers = 0x02` — Show sync markers
- L57 _public enumerator_ `CurrentSkeleton = 0x04` — Show the current skeleton's items
- L59 _public enumerator_ `CompatibleAssets = 0x08` — Show other compatible asset's items
- L61 _public enumerator_ `OtherAssets = 0x10` — Show other asset's items

#### class `FDisplayedAnimNotifyInfo`  
`class FDisplayedAnimNotifyInfo`  
_L69-103_
- L72 _public member_ `FName Name;`
- L75 _public member_ `TSharedPtr<SInlineEditableTextBlock> InlineEditableText;` — Handle to editable text block for rename
- L78 _public member_ `bool bIsNew;` — Flag to say whether this is a new item we are creating
- L81 _public member_ `bool bIsSyncMarker;` — Identifies sync markers vs notifies
- L84 _public member_ `EAnimNotifyFilterFlags ItemFlags;` — Flags for this item
- L87 _public function_ `static TSharedRef<FDisplayedAnimNotifyInfo> Make(const FName& NotifyName, bool bInIsSyncMarker, EAnimNotifyFilterFlags InItemFlags)` — Static function for creating a new item, but ensures that you can only have a TSharedRef to one
- L94 _protected function_ `FDisplayedAnimNotifyInfo(const FName& InNotifyName, bool bInIsSyncMarker, EAnimNotifyFilterFlags InItemFlags) : Name( InNotifyName ) , bIsNew(false) , bIsSyncMarker(bInIsSyncMarker) , ItemFlags(InItemFlags)` — Hidden constructor, always use Make above
- L102 _protected function_ `FDisplayedAnimNotifyInfo()` — Hidden constructor, always use Make above

#### class `SSkeletonAnimNotifies`  
`class SSkeletonAnimNotifies : public SCompoundWidget, public FGCObject, public FEditorUndoClient`  
_L108-299_
- inherits: `SCompoundWidget,FGCObject,FEditorUndoClient`
- L111 _public function_ `SLATE_BEGIN_ARGS( SSkeletonAnimNotifies ) : _IsPicker(false) , _ShowSyncMarkers(true) , _ShowNotifies(true) , _ShowCompatibleSkeletonAssets(false) , _ShowOtherAssets(false)`
- L148 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedPtr<class FAssetEditorToolkit>& InHostingApp = nullptr);`
- L150 _public prototype_ `~SSkeletonAnimNotifies();`
- L156 _public function_ `FText& GetFilterText()` — Accessor so our rows can grab the filter text for highlighting
- L159 _public prototype_ `UObject* ShowInDetailsView( UClass* EdClass );` — Creates an editor object from the given type to be used in a details panel
- L162 _public prototype_ `void ClearDetailsView();` — Clears the detail view of whatever we displayed last
- L165 _public prototype_ `virtual void PostUndo( bool bSuccess ) override;` — FEditorUndoClient interface
- L166 _public prototype_ `virtual void PostRedo( bool bSuccess ) override;`
- L169 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface start
- L170 _public function_ `virtual FString GetReferencerName() const override`
- L177 _public prototype_ `bool OnVerifyNotifyNameCommit( const FText& NewName, FText& OutErrorMessage, TSharedPtr<FDisplayedAnimNotifyInfo> Item );` — When user attempts to commit the name of a track
- L180 _public prototype_ `void OnNotifyNameCommitted( const FText& NewName, ETextCommit::Type, TSharedPtr<FDisplayedAnimNotifyInfo> Item );` — When user commits the name of a track
- L183 _public function_ `bool IsSelected()` — Dummy handler to stop editable text boxes swallowing our list selected events
- L187 _private prototype_ `void OnFilterTextChanged( const FText& SearchText );` — Called when the user changes the contents of the search box
- L190 _private prototype_ `void OnFilterTextCommitted( const FText& SearchText, ETextCommit::Type CommitInfo );` — Called when the user changes the contents of the search box
- L193 _private prototype_ `TSharedRef<ITableRow> GenerateNotifyRow( TSharedPtr<FDisplayedAnimNotifyInfo> InInfo, const TSharedRef<STableViewBase>& OwnerTable );` — Delegate handler for generating rows in NotifiesListView
- L196 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuContent() const;` — Delegate handler called when the user right clicks in NotifiesListView
- L199 _private prototype_ `void OnNotifySelectionChanged( TSharedPtr<FDisplayedAnimNotifyInfo> Selection, ESelectInfo::Type SelectInfo );` — Delegate handler for when the user selects something in NotifiesListView
- L202 _private prototype_ `bool CanPerformDelete() const;` — Delegate handler for determining whether we can show the delete menu options
- L205 _private prototype_ `bool CanPerformFindReferences() const;` — Delegate handler for determining whether we can show the find references menu option
- L208 _private prototype_ `void OnDeleteItems();` — Delegate handler for deleting items
- L211 _private prototype_ `bool CanPerformRename() const;` — Delegate handler for determining whether we can show the rename menu options
- L214 _private prototype_ `void OnAddItem(bool bIsSyncMarker);` — Delegate handler for adding anim notifies & sync markers
- L217 _private prototype_ `void OnRenameItem();` — Delegate handler for renaming items
- L220 _private prototype_ `void RefreshNotifiesListWithFilter();` — Wrapper that populates NotifiesListView using current filter text
- L223 _private prototype_ `void CreateNotifiesList();` — Populates NotifyList based on the project's notifies
- L226 _private prototype_ `void FilterNotifiesList(const FString& InSearchText);` — Populates FilteredNotifyList based on the project's notifies and the supplied filter text
- L229 _private prototype_ `void ShowNotifyInDetailsView( FName NotifyName );` — handler for user selecting a Notify in NotifiesListView - populates the details panel
- L232 _private prototype_ `void NotifyUser( FNotificationInfo& NotificationInfo );` — Utility function to display notifications to the user
- L235 _private prototype_ `void OnNotifiesChanged();` — Handler function for when notifies are modified on the skeleton
- L238 _private prototype_ `void OnItemScrolledIntoView(TSharedPtr<FDisplayedAnimNotifyInfo> InItem, const TSharedPtr<ITableRow>& InTableRow);` — Handle when an item is scrolled into view, triggers a rename for new items
- L241 _private prototype_ `void OnFindReferences();` — Handle find references from the context menu
- L244 _private member_ `TSharedPtr<class IEditableSkeleton> EditableSkeleton;` — The skeleton we are currently editing
- L247 _private member_ `TSharedPtr<SSearchBox> NameFilterBox;` — SSearchBox to filter the notify list
- L250 _private member_ `TSharedPtr<SAnimNotifyListType> NotifiesListView;` — Widget used to display the list of notifies
- L253 _private member_ `TArray< TSharedPtr<FDisplayedAnimNotifyInfo> > NotifyList;` — A list of all notifies and sync markers.
- L256 _private member_ `TArray< TSharedPtr<FDisplayedAnimNotifyInfo> > FilteredNotifyList;` — Filtered list of notifies. Used by the NotifiesListView.
- L259 _private member_ `FText FilterText;` — Current text typed into NameFilterBox
- L262 _private member_ `FEditorObjectTracker EditorObjectTracker;` — Tracks objects created for displaying in the details panel
- L265 _private member_ `FOnObjectsSelected OnObjectsSelected;` — Delegate called to select an object in the details panel
- L268 _private member_ `FOnNotifyPicked OnItemSelected;` — Delegate fired when a notify is selected
- L271 _private member_ `TWeakPtr<class FAssetEditorToolkit> WeakHostingApp;` — The app we are embedded in
- L274 _private member_ `bool bIsPicker = false;` — Whether we should use this dialog as a picker or an editor. In picker mode we cant add, remove or rename notifies.
- L277 _private member_ `bool bShowSyncMarkers = false;` — Whether we should display markers
- L280 _private member_ `bool bShowNotifies = false;` — Whether we should display notifies
- L283 _private member_ `bool bShowOtherSkeletonItems = false;` — Whether we should display notifies or sync markers from other skeletons
- L286 _private member_ `bool bShowOtherAssets = false;` — Whether we notifies and sync markers from assets other than the current skeleton
- L289 _private member_ `bool bShowCompatibleSkeletonAssets = false;` — Whether we notifies and sync markers from assets compatible with the current skeleton
- L292 _private member_ `bool bAllowRefreshFilter = true;` — Whether to suspend refreshing the UI when filtering
- L295 _private member_ `TArray<TSharedRef<FFilterBase<EAnimNotifyFilterFlags>>> Filters;` — All filters that can be applied to the widget's display
- L298 _private member_ `EAnimNotifyFilterFlags CurrentFilterFlags = EAnimNotifyFilterFlags::None;` — Current filter flags

#### Free symbols / members of external scopes

- L21 _macro_ `#define LOCTEXT_NAMESPACE "SkeletonAnimnotifies"`
- L64 _prototype_ `ENUM_CLASS_FLAGS(EAnimNotifyFilterFlags);`
- L106 _typedef_ `typedef SListView< TSharedPtr<FDisplayedAnimNotifyInfo> > SAnimNotifyListType;` — Widgets list type

### `Source/Editor/Persona/Private/SSkeletonSlotNames.h` (Private)


#### struct `FSkeletonSlotNamesSummoner`  
`struct FSkeletonSlotNamesSummoner : public FWorkflowTabFactory`  
_L33-48_
- inherits: `FWorkflowTabFactory`
- desc: FSkeletonSlotNamesSummoner
- L36 _public prototype_ `FSkeletonSlotNamesSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, const TSharedRef<class IEditableSkeleton>& InEditableSkeleton, FOnObjectSelected InOnObjectSelected);`
- L38 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L41 _public function_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override` — Create a tooltip widget for the tab
- L46 _public member_ `TWeakPtr<class IEditableSkeleton> EditableSkeleton;`
- L47 _public member_ `FOnObjectSelected OnObjectSelected;`

#### class `FDisplayedSlotNameInfo`  
`class FDisplayedSlotNameInfo`  
_L53-80_
- L56 _public member_ `FName Name;`
- L58 _public member_ `bool bIsGroupItem;`
- L60 _public member_ `TArray< TSharedPtr<FDisplayedSlotNameInfo> > Children;`
- L63 _public member_ `TSharedPtr<SInlineEditableTextBlock> InlineEditableText;` — Handle to editable text block for rename
- L66 _public function_ `static TSharedRef<FDisplayedSlotNameInfo> Make(const FName& InItemName, bool InbIsGroupItem)` — Static function for creating a new item, but ensures that you can only have a TSharedRef to one
- L73 _protected function_ `FDisplayedSlotNameInfo(const FName& InItemName, bool InbIsGroupItem) : Name(InItemName) , bIsGroupItem(InbIsGroupItem)` — Hidden constructor, always use Make above
- L79 _protected function_ `FDisplayedSlotNameInfo()` — Hidden constructor, always use Make above

#### class `SSkeletonSlotNames`  
`class SSkeletonSlotNames : public SCompoundWidget, public FGCObject, public FSelfRegisteringEditorUndoClient`  
_L85-243_
- inherits: `SCompoundWidget,FGCObject,FSelfRegisteringEditorUndoClient`
- L88 _public function_ `SLATE_BEGIN_ARGS( SSkeletonSlotNames )`
- L95 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<IEditableSkeleton>& InEditableSkeleton);`
- L101 _public function_ `FText& GetFilterText()` — Accessor so our rows can grab the filter text for highlighting
- L104 _public prototype_ `UObject* ShowInDetailsView( UClass* EdClass );` — Creates an editor object from the given type to be used in a details panel
- L107 _public prototype_ `void ClearDetailsView();` — Clears the detail view of whatever we displayed last
- L110 _public function_ `virtual void PostUndo(bool bSuccess) override` — FSelfRegisteringEditorUndoClient interface
- L111 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L114 _public prototype_ `void PostUndoRedo();` — This triggers a UI repopulation after undo has been called
- L117 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface start
- L118 _public function_ `virtual FString GetReferencerName() const override`
- L127 _private prototype_ `void OnFilterTextChanged( const FText& SearchText );` — Called when the user changes the contents of the search box
- L130 _private prototype_ `void OnFilterTextCommitted( const FText& SearchText, ETextCommit::Type CommitInfo );` — Called when the user changes the contents of the search box
- L133 _private prototype_ `TSharedRef<ITableRow> GenerateNotifyRow( TSharedPtr<FDisplayedSlotNameInfo> InInfo, const TSharedRef<STableViewBase>& OwnerTable );` — Delegate handler for generating rows in SlotNameListView
- L136 _private prototype_ `void GetChildrenForInfo(TSharedPtr<FDisplayedSlotNameInfo> InInfo, TArray< TSharedPtr<FDisplayedSlotNameInfo> >& OutChildren);` — Get all children for a given entry in the list
- L139 _private prototype_ `TSharedPtr<SWidget> OnGetContextMenuContent() const;` — Delegate handler called when the user right clicks in SlotNameListView
- L142 _private prototype_ `void OnNotifySelectionChanged( TSharedPtr<FDisplayedSlotNameInfo> Selection, ESelectInfo::Type SelectInfo );` — Delegate handler for when the user selects something in SlotNameListView
- L145 _private prototype_ `void OnSaveSkeleton();` — Save Skeleton
- L148 _private prototype_ `void OnAddSlot();` — Add a new Slot
- L149 _private prototype_ `void AddSlotPopUpOnCommit(const FText& InNewSlotName, ETextCommit::Type CommitInfo);`
- L152 _private prototype_ `void OnAddGroup();` — Add a new Group
- L153 _private prototype_ `void AddGroupPopUpOnCommit(const FText& InNewGroupName, ETextCommit::Type CommitInfo);`
- L156 _private prototype_ `void OnDeleteSlot(FName SlotName);` — Delete a slot after checking slot name references and prompting the user to resolve
- L159 _private prototype_ `void DeleteSlot(const FName& SlotName);` — Delete a slot immediately without checking references. Call only if sure the name is unreferenced as it will be re-added on next load if it is.
- L161 _private prototype_ `void RetryDeleteSlot(FName SlotName);` — Retry the validation for deleting a slot
- L164 _private prototype_ `void OnDeleteSlotGroup(FName GroupName);` — Delete a slot group after checking slot name references and prompting the user to resolve
- L166 _private prototype_ `void DeleteSlotGroup(const FName& GroupName);` — Delete a slot group immediately without checking references.
- L168 _private prototype_ `void RetryDeleteSlotGroup(FName GroupName);` — Retry the validation for deleting a slot group
- L170 _private prototype_ `bool CanDeleteSlotGroup(FName GroupName);` — Context menu hook for checking whether delete group is enabled
- L173 _private prototype_ `void OnRenameSlotPopupCommitted(const FText& InNewSlotText, ETextCommit::Type CommitInfo, FName OldName);` — Attempt to rename a slot after a name has been given - validating the new name and old references first
- L175 _private prototype_ `void OnRenameSlot(FName CurrentName);` — Spawn popup text box for user to enter name
- L177 _private prototype_ `void RenameSlot(FName CurrentName, FName NewName);` — Rename a slot immediately without checking references
- L179 _private prototype_ `void RetryRenameSlot(FName CurrentName, FName NewName);` — Retry the validation for renaming a slot
- L182 _private prototype_ `void FillSetSlotGroupSubMenu(FMenuBuilder& MenuBuilder);` — Set Slot Group
- L183 _private prototype_ `void ContextMenuOnSetSlot(FName InNewGroupName);`
- L186 _private prototype_ `void RefreshSlotNameListWithFilter();` — Wrapper that populates SlotNameListView using current filter test
- L188 _private prototype_ `TSharedPtr< FDisplayedSlotNameInfo > FindItemNamed(FName ItemName) const;`
- L191 _private prototype_ `void CreateSlotNameList( const FString& SearchText = FString("") );` — Populates SlotNameListView based on the skeletons SlotName and the supplied filter text
- L194 _private prototype_ `void ShowNotifyInDetailsView( FName NotifyName );` — handler for user selecting a Notify in SlotNameListView - populates the details panel
- L197 _private prototype_ `void GetCompatibleAnimMontages( TArray<struct FAssetData>& OutAssets );` — Populates OutAssets with the AnimSequences that match Personas current skeleton
- L199 _private prototype_ `void GetCompatibleAnimBlueprints( TArray<FAssetData>& OutAssets );` — Populates OutAssets with the Anim Blueprints that match Personas current skeleton
- L202 _private prototype_ `void GetAnimMontagesUsingSlot(FName SlotName, TArray<FAssetData>& OutMontages);` — Get all montages that have an anim track using the given slot
- L204 _private prototype_ `void GetAnimMontagesUsingSlotGroup(FName SlotGroupName, TArray<FAssetData>& OutMontages);` — Get all montages that have an anim track using the given slot group
- L207 _private prototype_ `void GetMontagesAndNodesUsingSlot(const FName& SlotName, TArray<FAssetData>& CompatibleMontages, TMultiMap<UAnimBlueprint*, UAnimGraphNode_Slot*>& CompatibleSlotNodes);` — Get all montages using the given slot name and a map of all blueprints/nodes also using the slot name
- L209 _private prototype_ `void GetMontagesAndNodesUsingSlotGroup(const FName& SlotGroupName, TArray<FAssetData>& OutMontages, TMultiMap<UAnimBlueprint*, UAnimGraphNode_Slot*> &OutBlueprintSlotMap);` — Get all montages using the given slot group and a map of all blueprints/nodes also using the slot group
- L212 _private prototype_ `void NotifyUser( FNotificationInfo& NotificationInfo );` — Utility function to display notifications to the user
- L215 _private prototype_ `void ReferenceWindowClosed(const TSharedRef<SWindow>& Window);` — Callback for popup reference window closing
- L218 _private member_ `TSharedPtr<class IEditableSkeleton> EditableSkeleton;` — The skeleton we are currently editing
- L221 _private member_ `FOnObjectSelected OnObjectSelected;` — Delegate call to select an object & display its details
- L224 _private member_ `TSharedPtr<SSearchBox> NameFilterBox;` — SSearchBox to filter the notify list
- L227 _private member_ `TSharedPtr<SSlotNameListType> SlotNameListView;` — Widget used to display the list of SlotName
- L230 _private member_ `TArray< TSharedPtr<FDisplayedSlotNameInfo> > NotifyList;` — A list of SlotName. Used by the SlotNameListView.
- L233 _private member_ `FText FilterText;` — Current text typed into NameFilterBox
- L236 _private member_ `FEditorObjectTracker EditorObjectTracker;` — Tracks objects created for displaying in the details panel
- L239 _private member_ `TSharedPtr<SWindow> ReferenceWindow;` — Stores the window we spawn to notify the user that references exist on deletion
- L242 _private member_ `TWeakPtr<SSlotNameReferenceWindow> ReferenceWidget;` — The actual custom widget inside ReferenceWindow

#### Free symbols / members of external scopes

- L30 _macro_ `#define LOCTEXT_NAMESPACE "SkeletonSlotNames"`
- L83 _typedef_ `typedef STreeView< TSharedPtr<FDisplayedSlotNameInfo> > SSlotNameListType;` — Widgets list type

### `Source/Editor/Persona/Private/SSlotNameReferenceWindow.h` (Private)


#### class `FDisplayedMontageReferenceInfo`  
`class FDisplayedMontageReferenceInfo`  
_L27-43_
- desc: List display helper for montage references
- L30 _public member_ `FAssetData AssetData;`
- L32 _public prototype_ `static TSharedRef<FDisplayedMontageReferenceInfo> Make(const FAssetData& AssetData);`
- L36 _protected function_ `FDisplayedMontageReferenceInfo(const FAssetData& InData) : AssetData(InData)` — Hidden constructor, always use Make above
- L41 _protected function_ `FDisplayedMontageReferenceInfo()` — Hidden constructor, always use Make above

#### class `FDisplayedBlueprintReferenceInfo`  
`class FDisplayedBlueprintReferenceInfo`  
_L46-65_
- desc: List display helper for blueprint references
- L49 _public member_ `FString BlueprintName;`
- L50 _public member_ `FString GraphName;`
- L51 _public member_ `FString NodeName;`
- L52 _public member_ `UAnimBlueprint* AnimBlueprint;`
- L53 _public member_ `UEdGraph* NodeGraph;`
- L54 _public member_ `UAnimGraphNode_Base* Node;`
- L56 _public prototype_ `static TSharedRef<FDisplayedBlueprintReferenceInfo> Make(UAnimBlueprint* Blueprint, UAnimGraphNode_Slot* SlotNode);`
- L60 _protected prototype_ `FDisplayedBlueprintReferenceInfo(UAnimBlueprint* Blueprint, UAnimGraphNode_Slot* SlotNode);` — Hidden constructor, always use Make above
- L63 _protected function_ `FDisplayedBlueprintReferenceInfo()` — Hidden constructor, always use Make above

#### class `SMontageReferenceListRow`  
`class SMontageReferenceListRow : public SMultiColumnTableRow < TSharedPtr<FDisplayedMontageReferenceInfo> >`  
_L70-90_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDisplayedMontageReferenceInfo>>`
- L73 _public function_ `SLATE_BEGIN_ARGS(SMontageReferenceListRow)`
- L79 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L81 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L86 _protected prototype_ `FReply OnViewInContentBrowserClicked();` — Handlers for asset interaction buttons
- L87 _protected prototype_ `FReply OnOpenAssetClicked();`
- L89 _protected member_ `TSharedPtr<FDisplayedMontageReferenceInfo> ReferenceInfo;`

#### class `SBlueprintReferenceListRow`  
`class SBlueprintReferenceListRow : public SMultiColumnTableRow<TSharedPtr<FDisplayedBlueprintReferenceInfo>>`  
_L92-111_
- inherits: `SMultiColumnTableRow<TSharedPtr<FDisplayedBlueprintReferenceInfo>>`
- L95 _public function_ `SLATE_BEGIN_ARGS(SBlueprintReferenceListRow)`
- L100 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);`
- L102 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L107 _protected prototype_ `FReply OnViewInContentBrowserClicked();` — Handlers for asset interaction buttons
- L108 _protected prototype_ `FReply OnOpenAssetClicked();`
- L110 _protected member_ `TSharedPtr<FDisplayedBlueprintReferenceInfo> ReferenceInfo;`

#### struct `FReferenceWindowInfo`  
`struct FReferenceWindowInfo`  
_L115-131_
- desc: Required information to update a reference window widget, used in conjunction with SSlotNameReferenceWindow::UpdateInfo any fields that do not get set by the caller will not be updated and will keep its previous value
- L117 _public function_ `FReferenceWindowInfo() : ReferencingMontages(nullptr) , ReferencingNodes(nullptr) , bRefresh(true)`
- L125 _public member_ `TArray<FAssetData>* ReferencingMontages;`
- L126 _public member_ `NodeMapPtr ReferencingNodes;`
- L127 _public member_ `FText OperationText;`
- L128 _public member_ `FText ItemText;`
- L129 _public member_ `FSimpleDelegate RetryDelegate;`
- L130 _public member_ `bool bRefresh;`

#### class `SSlotNameReferenceWindow`  
`class SSlotNameReferenceWindow : public SCompoundWidget`  
_L134-183_
- inherits: `SCompoundWidget`
- desc: Widget used to slot name references that are blocking an edit operation
- L137 _public function_ `SLATE_BEGIN_ARGS(SSlotNameReferenceWindow)`
- L147 _public prototype_ `void Construct(const FArguments& InArgs);`
- L150 _public prototype_ `void RefreshContent();` — Refresh the child content of this widget
- L153 _public prototype_ `void UpdateInfo(FReferenceWindowInfo& UpdatedInfo);` — Update the reference arrays and optionally rebuild the widget
- L156 _public member_ `FString SlotName;` — The name of the slot we're referencing
- L161 _protected prototype_ `TSharedRef<SWidget> GetContent();` — Rebuild the internal content of the widget
- L164 _protected prototype_ `TSharedRef<ITableRow> HandleGenerateMontageReferenceRow( TSharedPtr<FDisplayedMontageReferenceInfo> Item, const TSharedRef<STableViewBase>& OwnerTable );` — Row generators for montage and blueprint/node data views
- L165 _protected prototype_ `TSharedRef<ITableRow> HandleGenerateBlueprintReferenceRow( TSharedPtr<FDisplayedBlueprintReferenceInfo> Item, const TSharedRef<STableViewBase>& OwnerTable );`
- L168 _protected prototype_ `FReply OnRetryClicked();` — Button handlers
- L169 _protected prototype_ `FReply OnCloseClicked();`
- L172 _protected member_ `FText OperationText;` — Operation type to display
- L175 _protected member_ `TArray<TSharedPtr<FDisplayedMontageReferenceInfo>> ReferencingMontages;` — Objects referencing the given slot name
- L176 _protected member_ `TArray<TSharedPtr<FDisplayedBlueprintReferenceInfo>> ReferencingNodes;`
- L179 _protected member_ `TSharedPtr<SWindow> ContainingWindow;` — Ptr to the window this widget resides in
- L182 _protected member_ `FSimpleDelegate OnRetry;` — Called when the retry button is clicked. User code determines retry behaviour

#### Free symbols / members of external scopes

- L15 _macro_ `#define LOCTEXT_NAMESPACE "SlotRefWindow"`
- L24 _typedef_ `typedef TMultiMap<UAnimBlueprint*, UAnimGraphNode_Slot*>* NodeMapPtr;` — This type can't exist in a SLATE_ARGUMENT macro so typedef away the template
- L67 _typedef_ `typedef SListView<TSharedPtr<FDisplayedMontageReferenceInfo>> SMontageReferenceList;`
- L68 _typedef_ `typedef SListView<TSharedPtr<FDisplayedBlueprintReferenceInfo>> SBlueprintReferenceList;`

### `Source/Editor/Persona/Private/STimingTrack.h` (Private)


#### class `STimingTrack`  
`class STimingTrack : public STrack`  
_L15-35_
- inherits: `STrack`
- desc: Specialised anim track which arranges overlapping nodes into groups
- L19 _public function_ `SLATE_BEGIN_ARGS(STimingTrack)`
- L22 _public prototype_ `SLATE_ATTRIBUTE(float, ViewInputMin) SLATE_ATTRIBUTE(float, ViewInputMax) SLATE_ATTRIBUTE(float, TrackMaxValue) SLATE_ATTRIBUTE(float, TrackMinValue) SLATE_ATTRIBUTE(int32, TrackNumDiscreteValues) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L32 _public prototype_ `virtual void OnArrangeChildren( const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren ) const override;`

### `Source/Editor/Persona/Private/STrack.h` (Private)


#### class `FTrackNodeDragDropOp`  
`class FTrackNodeDragDropOp : public FDragDropOperation`  
_L68-97_
- inherits: `FDragDropOperation`
- L71 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FTrackNodeDragDropOp, FDragDropOperation) virtual void OnDrop( bool bDropWasHandled, const FPointerEvent& MouseEvent ) override;`
- L75 _public prototype_ `virtual void OnDragged( const class FDragDropEvent& DragDropEvent ) override;`
- L77 _public prototype_ `static TSharedRef<FTrackNodeDragDropOp> New(TSharedRef<STrackNode> TrackNode, const FVector2D &CursorPosition, const FVector2D &ScreenPositionOfNode);`
- L80 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;` — Gets the widget that will serve as the decorator unless overridden. If you do not override, you will have no decorator
- L84 _protected member_ `FVector2D Offset;` — The window that shows hover text
- L85 _protected member_ `FVector2D StartingScreenPos;`
- L86 _protected member_ `TWeakPtr<class STrackNode> OriginalTrackNode;`
- L87 _protected member_ `TWeakPtr<class STrack> OriginalTrack;`
- L89 _protected function_ `FString GetHoverText() const`

#### class `STrackNode`  
`class STrackNode : public SCompoundWidget`  
_L102-237_
- inherits: `SCompoundWidget`
- desc: class STrackNode for STrack. This is Children for STrack
- L105 _public function_ `SLATE_BEGIN_ARGS( STrackNode ) : _ViewInputMin() , _ViewInputMax() , _DataLength() , _DataStartPos() , _NodeName() , _NodeColor() , _SelectedNodeColor() , _NodeSelectionSet(NULL) , _AllowDrag(true) , _OnTrackNodeDragged() , _OnTrackNodeDropped() , _OnSelectionChanged() , _OnNodeRightClickContextMenu() , _OnTrackNodeClicked() , _OnTrackNodeDoubleClicked() , _CenterOnPosition(false)`
- L126 _public prototype_ `SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax ) SLATE_ATTRIBUTE( float, DataLength ) SLATE_ATTRIBUTE( float, DataStartPos ) SLATE_ATTRIBUTE( FString, NodeName ) SLATE_ATTRIBUTE( FLinearColor, NodeColor ) SLATE_ATTRIBUTE( FLinearColor, SelectedNodeColor ) SLATE_ARGUMENT( STrackNodeSelectionSet *, NodeSelectionSet ) SLATE_ARGUMENT( bool, AllowDrag ) SLATE_EVENT( FOnTrackNodeDragged, OnTrackNodeDragged ) SLATE_EVENT( FOnTrackNodeDropped, OnTrackNodeDropped ) SLATE_EVENT( FOnNodeSelectionChanged, OnSelectionChanged ) SLATE_EVENT( FOnNodeRightClickContextMenu, OnNodeRightClickContextMenu ) SLATE_EVENT( FOnTrackNodeClicked, OnTrackNodeClicked ) SLATE_EVENT( FOnTrackNodeDoubleClicked, OnTrackNodeDoubleClicked) SLATE_ARGUMENT( bool, CenterOnPosition ) SLATE_NAMED_SLOT(FArguments, OverrideContent) SLATE_END_ARGS() void Construct(const FArguments& Declaration);` — have delegates for update functions
- L149 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;` — mouse interface for tooltip/selection
- L150 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L151 _public prototype_ `virtual void OnMouseEnter( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L152 _public prototype_ `virtual void OnMouseLeave( const FPointerEvent& MouseEvent ) override;`
- L153 _public prototype_ `virtual void OnDragged(const class FDragDropEvent& DragDropEvent );`
- L154 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L157 _public prototype_ `virtual FVector2D GetOffsetRelativeToParent(const FGeometry& ParentAllottedGeometry) const;` — virtual draw related functions
- L158 _public prototype_ `virtual FVector2D GetSizeRelativeToParent(const FGeometry& ParentAllottedGeometry) const;`
- L161 _public prototype_ `virtual FReply OnDragDetected( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;` — drag drop relationship
- L162 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L164 _public prototype_ `void OnDropCancelled(const FPointerEvent& MouseEvent);`
- L166 _public prototype_ `virtual FReply BeginDrag( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent );`
- L168 _public prototype_ `virtual FVector2D GetDragDropScreenSpacePosition(const FGeometry& ParentAllottedGeometry, const FDragDropEvent& DragDropEvent) const;`
- L170 _public prototype_ `bool HitTest(const FGeometry& AllottedGeometry, FVector2D MouseLocalPose) const;`
- L172 _public prototype_ `virtual FVector2D GetSize() const;`
- L174 _public prototype_ `float GetDataStartPos() const;`
- L177 _public function_ `virtual bool SnapToDragBars() const` — Return whether this node should snap to the tracks draggable bars when being dragged
- L180 _public function_ `virtual void OnSnapNodeDataPosition(float OriginalX, float SnappedX)` — Called when the nodes position has been 'snapped' to something
- L183 _public function_ `void CacheTrackGeometry(const FGeometry& TrackGeometry)` — Cache the supplied geometry as our track geometry
- L185 _public function_ `const FGeometry& GetTrackGeometry() const`
- L187 _public function_ `bool IsBeingDragged() const`
- L191 _protected prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L194 _protected prototype_ `FSlateColor GetNodeColor() const;`
- L196 _protected prototype_ `FText GetNodeText() const;` — Temp, remove and replace with correct attribute
- L198 _protected prototype_ `void ToggleSelect();`
- L199 _protected prototype_ `void Select();`
- L200 _protected prototype_ `void Deselect();`
- L201 _protected prototype_ `bool IsSelected() const;`
- L204 _protected member_ `bool bSelectedFallback;` — only use this if the selection set isnt set
- L205 _protected member_ `STrackNodeSelectionSet * NodeSelectionSet;`
- L207 _protected member_ `TAttribute<FString> NodeName;`
- L208 _protected member_ `TAttribute<float> DataStartPos;`
- L209 _protected member_ `TAttribute<float> DataLength;`
- L211 _protected member_ `TAttribute<float> ViewInputMin;`
- L212 _protected member_ `TAttribute<float> ViewInputMax;`
- L213 _protected member_ `FOnNodeSelectionChanged OnNodeSelectionChanged;`
- L215 _protected member_ `TAttribute<FLinearColor> NodeColor;`
- L216 _protected member_ `TAttribute<FLinearColor> SelectedNodeColor;`
- L218 _protected member_ `FOnTrackNodeDragged OnTrackNodeDragged;`
- L219 _protected member_ `FOnTrackNodeDropped OnTrackNodeDropped;`
- L221 _protected member_ `FOnTrackNodeClicked OnTrackNodeClicked;`
- L222 _protected member_ `FOnTrackNodeDoubleClicked OnTrackNodeDoubleClicked;`
- L223 _protected member_ `FOnNodeRightClickContextMenu OnNodeRightClickContextMenu;`
- L225 _protected member_ `FSlateFontInfo Font;`
- L227 _protected member_ `mutable FVector2D LastSize;` — HACK Fixme: Need to update in OnPaint in case we are drag/dropped
- L228 _protected member_ `FGeometry CachedTrackGeometry;` — Our parent tracks geometry, so we can calculate scale/position
- L230 _protected member_ `float DistanceDragged;`
- L231 _protected member_ `bool bBeingDragged;`
- L232 _protected member_ `bool bCenterOnPosition;`
- L233 _protected member_ `bool bAllowDrag;`
- L234 _protected member_ `bool bContentOverriden;`

#### class `STrack`  
`class STrack : public SPanel`  
_L242-355_
- inherits: `SPanel`
- L246 _public function_ `SLATE_BEGIN_ARGS( STrack ) : _ViewInputMin() , _ViewInputMax() , _TrackMaxValue() , _TrackMinValue() , _TrackNumDiscreteValues() , _TrackColor(FLinearColor::White) , _OnSelectionChanged() , _DraggableBars() , _DraggableBarSnapPositions() , _DraggableBarLabels() , _OnBarDrag() , _OnTrackDragDrop() , _OnSummonContextMenu() , _OnTrackRightClickContextMenu() , _StyleInfo(FAppStyle::GetBrush( TEXT( "Persona.NotifyEditor.NotifyTrackBackground" )))`
- L264 _public prototype_ `SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax ) SLATE_ATTRIBUTE( float, TrackMaxValue ) SLATE_ATTRIBUTE( float, TrackMinValue ) SLATE_ATTRIBUTE( int32, TrackNumDiscreteValues ) SLATE_ARGUMENT( FLinearColor, TrackColor ) SLATE_EVENT( FOnNodeSelectionChanged, OnSelectionChanged ) SLATE_ATTRIBUTE( TArray<float>, DraggableBars ) SLATE_ATTRIBUTE( TArray<float>, DraggableBarSnapPositions ) SLATE_ATTRIBUTE( TArray<FString>, DraggableBarLabels ) SLATE_EVENT( FOnBarDrag, OnBarDrag) SLATE_EVENT( FOnBarClicked, OnBarClicked) SLATE_EVENT( FOnTrackDragDop, OnTrackDragDrop ) SLATE_EVENT( FOnAssetDragDrop, OnAssetDragDrop ) SLATE_EVENT( FOnBarDrop, OnBarDrop ) SLATE_EVENT( FOnSummonContextMenu, OnSummonContextMenu ) SLATE_EVENT( FOnTrackRightClickContextMenu, OnTrackRightClickContextMenu ) SLATE_ARGUMENT( const FSlateBrush*, StyleInfo ) SLATE_END_ARGS() STrack();`
- L286 _public prototype_ `void Construct( const FArguments& InArgs );`
- L288 _public prototype_ `virtual void OnArrangeChildren( const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren ) const override;`
- L289 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L291 _public prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L292 _public prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L293 _public prototype_ `virtual FReply OnDragDetected( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L294 _public prototype_ `virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L295 _public prototype_ `virtual void OnDragLeave(const FDragDropEvent& DragDropEvent) override;`
- L297 _public prototype_ `int32 GetHitNode(const FGeometry& MyGeometry, const FVector2D& CursorPosition);`
- L299 _public prototype_ `FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L300 _public prototype_ `FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L301 _public prototype_ `FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L303 _public prototype_ `virtual void OnMouseLeave( const FPointerEvent& MouseEvent ) override;`
- L304 _public prototype_ `virtual void OnMouseEnter( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L305 _public prototype_ `virtual FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;`
- L307 _public prototype_ `void AddTrackNode( TSharedRef<STrackNode> Node );`
- L308 _public prototype_ `void ClearTrack();`
- L309 _public prototype_ `FVector2D ComputeDesiredSize(float) const override;`
- L310 _public prototype_ `virtual FChildren* GetChildren() override;`
- L312 _public prototype_ `void GetSelectedNodeIndices(TArray<int32>& OutIndices);`
- L316 _protected prototype_ `bool GetDraggableBarSnapPosition(const FGeometry& MyGeometry, float &OutPosition) const;`
- L317 _protected prototype_ `virtual TSharedPtr<SWidget> SummonContextMenu(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L318 _protected prototype_ `float GetNodeDragDropDataPos( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) const;`
- L319 _protected prototype_ `float GetSnappedPosForLocalPos( const FGeometry& MyGeometry, float TrackPos) const;`
- L320 _protected prototype_ `void UpdateDraggableBarIndex( const FGeometry& MyGeometry, FVector2D CursorScreenPos );`
- L321 _protected prototype_ `float DataToLocalX( float Data, const FGeometry& MyGeometry ) const;`
- L322 _protected prototype_ `float LocalToDataX( float Input, const FGeometry& MyGeometry ) const;`
- L324 _protected member_ `TSlotlessChildren< STrackNode > TrackNodes;`
- L326 _protected member_ `TAttribute<TArray<float>> DraggableBars;`
- L327 _protected member_ `TAttribute<TArray<float>> DraggableBarSnapPositions;`
- L328 _protected member_ `TAttribute<TArray<FString>> DraggableBarLabels;`
- L329 _protected member_ `FOnBarDrag OnBarDrag;`
- L330 _protected member_ `FOnBarDrop OnBarDrop;`
- L331 _protected member_ `FOnBarClicked OnBarClicked;`
- L332 _protected member_ `TAttribute<FLinearColor> DraggableBarColor;`
- L333 _protected member_ `int32 DraggableBarIndex;`
- L334 _protected member_ `bool bDraggingBar;`
- L336 _protected member_ `TAttribute<float> TrackMaxValue;`
- L337 _protected member_ `TAttribute<float> TrackMinValue;`
- L338 _protected member_ `TAttribute<int32> TrackNumDiscreteValues;` — Discrete values (such as "number of frames in animation" used for accurate grid lines)
- L340 _protected member_ `TAttribute<float> ViewInputMin;`
- L341 _protected member_ `TAttribute<float> ViewInputMax;`
- L342 _protected member_ `TAttribute<FLinearColor> TrackColor;`
- L343 _protected member_ `FOnNodeSelectionChanged OnSelectionChanged;`
- L345 _protected member_ `FOnGetBarPos OnGetDraggableBarPos;`
- L346 _protected member_ `FOnTrackDragDop OnTrackDragDrop;`
- L347 _protected member_ `FOnAssetDragDrop OnAssetDragDrop;`
- L349 _protected member_ `TAttribute<const FSlateBrush*> StyleInfo;`
- L350 _protected member_ `FOnSummonContextMenu OnSummonContextMenu;`
- L351 _protected member_ `FOnTrackRightClickContextMenu OnTrackRightClickContextMenu;`
- L353 _protected member_ `TSharedPtr<FUICommandList> EditorActions;`
- L354 _protected member_ `FSlateFontInfo Font;`

#### Free symbols / members of external scopes

- L43 _delegate_ `DECLARE_DELEGATE_OneParam( FOnSelectionChanged, const TArray<UObject*>& ) DECLARE_DELEGATE( FOnNodeSelectionChanged ) DECLARE_DELEGATE( FOnUpdatePanel ) DECLARE_DELEGATE_RetVal_TwoParams( bool, FOnGetBarPos, int32, float& ) DECLARE_DELEGATE_OneParam( FOnBarClicked, int32) DECLARE_DELEGATE_TwoParams( FOnBarDrag, int32, float) DECLARE_DELEGATE_OneParam( FOnBarDrop, int32 ) DECLARE_DELEGATE_TwoParams( FOnTrackDragDop, TSharedPtr<FDragDropOperation>, float ) DECLARE_DELEGATE_RetVal_OneParam( bool, FOnAssetDragDrop, TSharedPtr<FAssetDragDropOp>) DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsAnimAssetValid, const UAnimSequenceBase*, FText* OutReason) DECLARE_DELEGATE_RetVal( FString, FOnGetNodeName ) DECLARE_DELEGATE_OneParam( FOnTrackNodeDragged, float ) DECLARE_DELEGATE( FOnTrackNodeDropped ) DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L43 _prototype_ `DECLARE_DELEGATE_OneParam( FOnSelectionChanged, const TArray<UObject*>& ) DECLARE_DELEGATE( FOnNodeSelectionChanged ) DECLARE_DELEGATE( FOnUpdatePanel ) DECLARE_DELEGATE_RetVal_TwoParams( bool, FOnGetBarPos, int32, float& ) DECLARE_DELEGATE_OneParam( FOnBarClicked, int32) DECLARE_DELEGATE_TwoParams( FOnBarDrag, int32, float) DECLARE_DELEGATE_OneParam( FOnBarDrop, int32 ) DECLARE_DELEGATE_TwoParams( FOnTrackDragDop, TSharedPtr<FDragDropOperation>, float ) DECLARE_DELEGATE_RetVal_OneParam( bool, FOnAssetDragDrop, TSharedPtr<FAssetDragDropOp>) DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsAnimAssetValid, const UAnimSequenceBase*, FText* OutReason) DECLARE_DELEGATE_RetVal( FString, FOnGetNodeName ) DECLARE_DELEGATE_OneParam( FOnTrackNodeDragged, float ) DECLARE_DELEGATE( FOnTrackNodeDropped ) DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L44 _delegate_ `DECLARE_DELEGATE( FOnNodeSelectionChanged ) DECLARE_DELEGATE( FOnUpdatePanel ) DECLARE_DELEGATE_RetVal_TwoParams( bool, FOnGetBarPos, int32, float& ) DECLARE_DELEGATE_OneParam( FOnBarClicked, int32) DECLARE_DELEGATE_TwoParams( FOnBarDrag, int32, float) DECLARE_DELEGATE_OneParam( FOnBarDrop, int32 ) DECLARE_DELEGATE_TwoParams( FOnTrackDragDop, TSharedPtr<FDragDropOperation>, float ) DECLARE_DELEGATE_RetVal_OneParam( bool, FOnAssetDragDrop, TSharedPtr<FAssetDragDropOp>) DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsAnimAssetValid, const UAnimSequenceBase*, FText* OutReason) DECLARE_DELEGATE_RetVal( FString, FOnGetNodeName ) DECLARE_DELEGATE_OneParam( FOnTrackNodeDragged, float ) DECLARE_DELEGATE( FOnTrackNodeDropped ) DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L45 _delegate_ `DECLARE_DELEGATE( FOnUpdatePanel ) DECLARE_DELEGATE_RetVal_TwoParams( bool, FOnGetBarPos, int32, float& ) DECLARE_DELEGATE_OneParam( FOnBarClicked, int32) DECLARE_DELEGATE_TwoParams( FOnBarDrag, int32, float) DECLARE_DELEGATE_OneParam( FOnBarDrop, int32 ) DECLARE_DELEGATE_TwoParams( FOnTrackDragDop, TSharedPtr<FDragDropOperation>, float ) DECLARE_DELEGATE_RetVal_OneParam( bool, FOnAssetDragDrop, TSharedPtr<FAssetDragDropOp>) DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsAnimAssetValid, const UAnimSequenceBase*, FText* OutReason) DECLARE_DELEGATE_RetVal( FString, FOnGetNodeName ) DECLARE_DELEGATE_OneParam( FOnTrackNodeDragged, float ) DECLARE_DELEGATE( FOnTrackNodeDropped ) DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L47 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams( bool, FOnGetBarPos, int32, float& ) DECLARE_DELEGATE_OneParam( FOnBarClicked, int32) DECLARE_DELEGATE_TwoParams( FOnBarDrag, int32, float) DECLARE_DELEGATE_OneParam( FOnBarDrop, int32 ) DECLARE_DELEGATE_TwoParams( FOnTrackDragDop, TSharedPtr<FDragDropOperation>, float ) DECLARE_DELEGATE_RetVal_OneParam( bool, FOnAssetDragDrop, TSharedPtr<FAssetDragDropOp>) DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsAnimAssetValid, const UAnimSequenceBase*, FText* OutReason) DECLARE_DELEGATE_RetVal( FString, FOnGetNodeName ) DECLARE_DELEGATE_OneParam( FOnTrackNodeDragged, float ) DECLARE_DELEGATE( FOnTrackNodeDropped ) DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L48 _delegate_ `DECLARE_DELEGATE_OneParam( FOnBarClicked, int32) DECLARE_DELEGATE_TwoParams( FOnBarDrag, int32, float) DECLARE_DELEGATE_OneParam( FOnBarDrop, int32 ) DECLARE_DELEGATE_TwoParams( FOnTrackDragDop, TSharedPtr<FDragDropOperation>, float ) DECLARE_DELEGATE_RetVal_OneParam( bool, FOnAssetDragDrop, TSharedPtr<FAssetDragDropOp>) DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsAnimAssetValid, const UAnimSequenceBase*, FText* OutReason) DECLARE_DELEGATE_RetVal( FString, FOnGetNodeName ) DECLARE_DELEGATE_OneParam( FOnTrackNodeDragged, float ) DECLARE_DELEGATE( FOnTrackNodeDropped ) DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L49 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnBarDrag, int32, float) DECLARE_DELEGATE_OneParam( FOnBarDrop, int32 ) DECLARE_DELEGATE_TwoParams( FOnTrackDragDop, TSharedPtr<FDragDropOperation>, float ) DECLARE_DELEGATE_RetVal_OneParam( bool, FOnAssetDragDrop, TSharedPtr<FAssetDragDropOp>) DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsAnimAssetValid, const UAnimSequenceBase*, FText* OutReason) DECLARE_DELEGATE_RetVal( FString, FOnGetNodeName ) DECLARE_DELEGATE_OneParam( FOnTrackNodeDragged, float ) DECLARE_DELEGATE( FOnTrackNodeDropped ) DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L50 _delegate_ `DECLARE_DELEGATE_OneParam( FOnBarDrop, int32 ) DECLARE_DELEGATE_TwoParams( FOnTrackDragDop, TSharedPtr<FDragDropOperation>, float ) DECLARE_DELEGATE_RetVal_OneParam( bool, FOnAssetDragDrop, TSharedPtr<FAssetDragDropOp>) DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsAnimAssetValid, const UAnimSequenceBase*, FText* OutReason) DECLARE_DELEGATE_RetVal( FString, FOnGetNodeName ) DECLARE_DELEGATE_OneParam( FOnTrackNodeDragged, float ) DECLARE_DELEGATE( FOnTrackNodeDropped ) DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L51 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnTrackDragDop, TSharedPtr<FDragDropOperation>, float ) DECLARE_DELEGATE_RetVal_OneParam( bool, FOnAssetDragDrop, TSharedPtr<FAssetDragDropOp>) DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsAnimAssetValid, const UAnimSequenceBase*, FText* OutReason) DECLARE_DELEGATE_RetVal( FString, FOnGetNodeName ) DECLARE_DELEGATE_OneParam( FOnTrackNodeDragged, float ) DECLARE_DELEGATE( FOnTrackNodeDropped ) DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L52 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( bool, FOnAssetDragDrop, TSharedPtr<FAssetDragDropOp>) DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsAnimAssetValid, const UAnimSequenceBase*, FText* OutReason) DECLARE_DELEGATE_RetVal( FString, FOnGetNodeName ) DECLARE_DELEGATE_OneParam( FOnTrackNodeDragged, float ) DECLARE_DELEGATE( FOnTrackNodeDropped ) DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L53 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsAnimAssetValid, const UAnimSequenceBase*, FText* OutReason) DECLARE_DELEGATE_RetVal( FString, FOnGetNodeName ) DECLARE_DELEGATE_OneParam( FOnTrackNodeDragged, float ) DECLARE_DELEGATE( FOnTrackNodeDropped ) DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L55 _delegate_ `DECLARE_DELEGATE_RetVal( FString, FOnGetNodeName ) DECLARE_DELEGATE_OneParam( FOnTrackNodeDragged, float ) DECLARE_DELEGATE( FOnTrackNodeDropped ) DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L56 _delegate_ `DECLARE_DELEGATE_OneParam( FOnTrackNodeDragged, float ) DECLARE_DELEGATE( FOnTrackNodeDropped ) DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L57 _delegate_ `DECLARE_DELEGATE( FOnTrackNodeDropped ) DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L58 _delegate_ `DECLARE_DELEGATE( FOnTrackNodeClicked ) DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L59 _delegate_ `DECLARE_DELEGATE( FOnTrackNodeDoubleClicked ) DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L61 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams( TSharedPtr<SWidget>, FOnSummonContextMenu, const FGeometry&, const FPointerEvent& );`
- L62 _delegate_ `DECLARE_DELEGATE_ThreeParams( FOnTrackRightClickContextMenu, FMenuBuilder&, float, int32 ) DECLARE_DELEGATE_OneParam( FOnNodeRightClickContextMenu, FMenuBuilder& ) typedef TSet<const class STrackNode*> STrackNodeSelectionSet;`
- L63 _delegate_ `DECLARE_DELEGATE_OneParam( FOnNodeRightClickContextMenu, FMenuBuilder& ) typedef TSet<const class STrackNode*> STrackNodeSelectionSet;`
- L65 _typedef_ `typedef TSet<const class STrackNode*> STrackNodeSelectionSet;`

### `Source/Editor/Persona/Private/SkeletalMeshReferenceSectionDetails.h` (Private)


#### class `FSectionReferenceCustomization`  
`class FSectionReferenceCustomization : public IPropertyTypeCustomization`  
_L16-48_
- inherits: `IPropertyTypeCustomization`
- L19 _public function_ `virtual ~FSectionReferenceCustomization()`
- L25 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L28 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L29 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L30 _public prototype_ `const FSkeletalMeshLODModel& GetLodModel() const;`
- L33 _protected prototype_ `void SetEditableLodModel(TSharedRef<IPropertyHandle> StructPropertyHandle);`
- L34 _protected prototype_ `virtual void SetPropertyHandle(TSharedRef<IPropertyHandle> StructPropertyHandle);`
- L35 _protected prototype_ `TSharedPtr<IPropertyHandle> FindStructMemberProperty(TSharedRef<IPropertyHandle> PropertyHandle, const FName& PropertyName);`
- L37 _protected member_ `TSharedPtr<IPropertyHandle> SectionIndexProperty;` — Property to change after section index has been picked
- L40 _protected member_ `USkeletalMesh* TargetSkeletalMesh = nullptr;` — Target LodModel this widget is referencing
- L41 _protected member_ `int32 TargetLodIndex = INDEX_NONE;`
- L46 _private prototype_ `virtual void OnSectionSelectionChanged(int32 SectionIndex);` — Section widget delegates
- L47 _private prototype_ `virtual int32 GetSelectedSection(bool& bMultipleValues) const;`

### `Source/Editor/Persona/Private/SkeletalMeshSocketDetails.h` (Private)


#### class `FSkeletalMeshSocketDetails`  
`class FSkeletalMeshSocketDetails : public IDetailCustomization`  
_L15-55_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L27 _private prototype_ `void OnParentBoneNameCommitted(const FText& InSearchText, ETextCommit::Type CommitInfo);` — Handle the committed text for the parent bone
- L30 _private prototype_ `void OnSocketNameChanged(const FText& InSearchText);` — Handle the changed text for the socket name
- L33 _private prototype_ `void OnSocketNameCommitted(const FText& InSearchText, ETextCommit::Type CommitInfo);` — Handle the committed text for the socket name
- L36 _private prototype_ `bool VerifySocketName(TSharedRef<class IEditableSkeleton> EditableSkeleton, const USkeletalMeshSocket* Socket, const FText& InText, USkeletalMesh* InSkeletalMesh, FText& OutErrorMessage ) const;` — Verifies the socket name and supplies and error message if it's invalid
- L39 _private prototype_ `TArray<FString> GetSearchSuggestions() const;` — Get the search suggestions
- L42 _private member_ `USkeletalMeshSocket* TargetSocket;` — The skeletal mesh socket associated with the socket
- L45 _private member_ `TSharedPtr<IPropertyHandle> SocketNameProperty;` — The handle to the socket name property
- L48 _private member_ `TSharedPtr<IPropertyHandle> ParentBoneProperty;` — The handle to the socket name property
- L51 _private member_ `TSharedPtr<SEditableTextBox> SocketNameTextBox;` — The ptr to the socket name text box
- L54 _private member_ `FText PreEditSocketName;` — The socket name prior to editing

### `Source/Editor/Persona/Private/SkinWeightProfileCustomization.h` (Private)


#### struct `FSkinWeightProfileCustomization`  
`struct FSkinWeightProfileCustomization : public IPropertyTypeCustomization`  
_L14-61_
- inherits: `IPropertyTypeCustomization`
- desc: Details customization for FSkinWeightProfileInfo
- L18 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — Begin IPropertyTypeCustomization overrides
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L27 _protected prototype_ `void UpdateNameRestriction();` — Check whether or not the currently inputted profile name is not used by any other profile in the mesh
- L29 _protected prototype_ `void RenameProfile();` — Renaming any profile data stored on a per-lod basis
- L32 _protected member_ `FName LastKnownProfileName;` — Name of the currently customization profile, last time it was retrieved
- L35 _protected prototype_ `FText OnGetProfileName() const;` — Callbacks used by NameEditTextBox widget
- L36 _protected prototype_ `void OnProfileNameChanged(const FText& InNewText);`
- L37 _protected prototype_ `void OnProfileNameCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);`
- L38 _protected prototype_ `const bool IsProfileNameValid(const FString& NewName);`
- L41 _protected member_ `TSharedPtr<SEditableTextBox> NameEditTextBox;` — Widgets used for customizing the Profile.Name property
- L42 _protected member_ `TSharedPtr<IPropertyHandle> NameProperty;`
- L44 _protected member_ `TArray<FString> RestrictedNames;` — Set of names that are currently used by other profiles in this profile's outer Skeletal Mesh
- L47 _protected prototype_ `TSharedRef<class SWidget> GenerateReimportMenu();` — Generates the sub menu used for reimporting (per-lod) profile data
- L49 _protected prototype_ `TSharedRef<class SWidget> GenerateRemoveMenu();` — Generates the sub menu used for removing (per-lod) profile data
- L52 _protected prototype_ `bool CheckAnyOtherProfileMarkedAsDefault() const;` — Checks to see if any other profile in the skeletal mesh is currently marked to be loaded by default
- L55 _protected prototype_ `bool IsProfileMarkedAsDefault() const;` — Checks to see if this profile in the skeletal mesh is currently marked to be loaded by default
- L58 _protected member_ `TWeakObjectPtr<USkeletalMesh> WeakSkeletalMesh;` — Weak-ptr to the currently customized profile's outer Skeletal Mesh
- L60 _protected member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`

### `Source/Editor/Persona/Private/TabSpawners.h` (Private)


#### struct `FPersonaModes`  
`struct FPersonaModes`  
_L34-62_
- desc: This is the list of IDs for persona modes
- L37 _public member_ `static const FName SkeletonDisplayMode;` — Mode constants
- L38 _public member_ `static const FName MeshEditMode;`
- L39 _public member_ `static const FName PhysicsEditMode;`
- L40 _public member_ `static const FName AnimationEditMode;`
- L41 _public member_ `static const FName AnimBlueprintEditMode;`
- L42 _public function_ `static FText GetLocalizedMode( const FName InMode )`
- L61 _private function_ `FPersonaModes()`

#### struct `FPersonaModeSharedData`  
`struct FPersonaModeSharedData : public IPersonaViewportState`  
_L67-97_
- inherits: `IPersonaViewportState`
- L69 _public prototype_ `FPersonaModeSharedData();`
- L71 _public prototype_ `void Save(const TSharedRef<FAnimationViewportClient>& InFromViewport);`
- L72 _public prototype_ `void Restore(const TSharedRef<FAnimationViewportClient>& InToViewport);`
- L75 _public member_ `FVector ViewLocation;` — camera setup
- L76 _public member_ `FRotator ViewRotation;`
- L77 _public member_ `float OrthoZoom;`
- L80 _public member_ `FVector OrbitZoom;` — orbit setup
- L81 _public member_ `FVector LookAtLocation;`
- L82 _public member_ `bool bCameraLock;`
- L83 _public member_ `EAnimationViewportCameraFollowMode CameraFollowMode;`
- L84 _public member_ `FName CameraFollowBoneName;`
- L87 _public member_ `bool bShowReferencePose;` — show flags
- L88 _public member_ `bool bShowBones;`
- L89 _public member_ `bool bShowBoneNames;`
- L90 _public member_ `bool bShowSockets;`
- L91 _public member_ `bool bShowBound;`
- L94 _public member_ `int32 ViewportType;` — viewport setup
- L95 _public member_ `EAnimationPlaybackSpeeds::Type PlaybackSpeedMode;`
- L96 _public member_ `int32 LocalAxesMode;`

#### class `FPersonaAppMode`  
`class FPersonaAppMode : public FApplicationMode`  
_L102-118_
- inherits: `FApplicationMode`
- L105 _protected prototype_ `FPersonaAppMode(TSharedPtr<class FPersona> InPersona, FName InModeName);`
- L109 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L110 _public prototype_ `virtual void PostActivateMode() override;`
- L114 _protected member_ `TWeakPtr<class FPersona> MyPersona;`
- L117 _protected member_ `FWorkflowAllowedTabSet PersonaTabFactories;` — Set of spawnable tabs in persona mode (@TODO: Multiple lists!)

#### struct `FMorphTargetTabSummoner`  
`struct FMorphTargetTabSummoner : public FWorkflowTabFactory`  
_L123-138_
- inherits: `FWorkflowTabFactory`
- L126 _public prototype_ `FMorphTargetTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, TSharedRef<IMorphTargetViewer> InViewerWidget);`
- L128 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L131 _public function_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override` — Create a tooltip widget for the tab
- L137 _private member_ `TSharedRef<IMorphTargetViewer> ViewerWidget;`

#### struct `FAnimCurveViewerTabSummoner`  
`struct FAnimCurveViewerTabSummoner : public FWorkflowTabFactory`  
_L143-161_
- inherits: `FWorkflowTabFactory`
- L146 _public prototype_ `FAnimCurveViewerTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, const TSharedPtr<IEditableSkeleton>& InEditableSkeleton, const TSharedRef<IPersonaPreviewScene>& InPreviewScene, FOnObjectsSelected InOnObjectsSelected, bool bInSetCurveViewerReadOnly = true);`
- L148 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L151 _public function_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override` — Create a tooltip widget for the tab
- L157 _private member_ `TWeakPtr<class IEditableSkeleton> EditableSkeleton;`
- L158 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScene;`
- L159 _private member_ `FOnObjectsSelected OnObjectsSelected;`
- L160 _private member_ `bool bSetCurveViewerReadOnly;`

#### struct `FAnimCurveMetadataEditorTabSummoner`  
`struct FAnimCurveMetadataEditorTabSummoner : public FWorkflowTabFactory`  
_L166-187_
- inherits: `FWorkflowTabFactory`
- L169 _public prototype_ `FAnimCurveMetadataEditorTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, UObject* InMetadataHost, const TSharedRef<IPersonaPreviewScene>& InPreviewScene, FOnObjectsSelected InOnObjectsSelected);`
- L171 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L173 _public function_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override`
- L178 _public function_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const`
- L184 _private member_ `TWeakObjectPtr<UObject> MetadataHost;`
- L185 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScene;`
- L186 _private member_ `FOnObjectsSelected OnObjectsSelected;`

#### struct `FAnimationAssetBrowserSummoner`  
`struct FAnimationAssetBrowserSummoner : public FWorkflowTabFactory`  
_L192-209_
- inherits: `FWorkflowTabFactory`
- L194 _public prototype_ `FAnimationAssetBrowserSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, const TSharedRef<IPersonaToolkit>& InPersonaToolkit, FOnOpenNewAsset InOnOpenNewAsset, FOnAnimationSequenceBrowserCreated InOnAnimationSequenceBrowserCreated, bool bInShowHistory);`
- L196 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L199 _public function_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override` — Create a tooltip widget for the tab
- L205 _private member_ `TWeakPtr<class IPersonaToolkit> PersonaToolkit;`
- L206 _private member_ `FOnOpenNewAsset OnOpenNewAsset;`
- L207 _private member_ `FOnAnimationSequenceBrowserCreated OnAnimationSequenceBrowserCreated;`
- L208 _private member_ `bool bShowHistory;`

#### struct `FPreviewViewportSummoner`  
`struct FPreviewViewportSummoner : public FWorkflowTabFactory`  
_L214-239_
- inherits: `FWorkflowTabFactory`
- L216 _public prototype_ `FPreviewViewportSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, const FPersonaViewportArgs& InArgs, int32 InViewportIndex);`
- L218 _public prototype_ `virtual FTabSpawnerEntry& RegisterTabSpawner(TSharedRef<FTabManager> TabManager, const FApplicationMode* CurrentApplicationMode) const;`
- L219 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L221 _public member_ `TWeakPtr<ISkeletonTree> SkeletonTree;`
- L222 _public member_ `TWeakPtr<IPersonaPreviewScene> PreviewScene;`
- L223 _public member_ `TWeakPtr<FBlueprintEditor> BlueprintEditor;`
- L224 _public member_ `FOnViewportCreated OnViewportCreated;`
- L225 _public member_ `FOnGetViewportText OnGetViewportText;`
- L226 _public member_ `TArray<TSharedPtr<FExtender>> Extenders;`
- L227 _public member_ `FName ContextName;`
- L228 _public member_ `int32 ViewportIndex;`
- L229 _public member_ `bool bShowShowMenu;`
- L230 _public member_ `bool bShowLODMenu;`
- L231 _public member_ `bool bShowPlaySpeedMenu;`
- L232 _public member_ `bool bShowTimeline;`
- L233 _public member_ `bool bShowStats;`
- L234 _public member_ `bool bAlwaysShowTransformToolbar;`
- L235 _public member_ `bool bShowFloorOptions;`
- L236 _public member_ `bool bShowTurnTable;`
- L237 _public member_ `bool bShowPhysicsMenu;`
- L238 _public member_ `FAnimationScrubPanelDelegates TimelineDelegates;`

#### struct `FRetargetSourcesTabSummoner`  
`struct FRetargetSourcesTabSummoner : public FWorkflowTabFactory`  
_L244-263_
- inherits: `FWorkflowTabFactory`
- L247 _public prototype_ `FRetargetSourcesTabSummoner( TSharedPtr<class FAssetEditorToolkit> InHostingApp, const TSharedRef<IEditableSkeleton>& InEditableSkeleton, FSimpleMulticastDelegate& InOnPostUndo);`
- L252 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L255 _public function_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override` — Create a tooltip widget for the tab
- L261 _private member_ `TWeakPtr<class IEditableSkeleton> EditableSkeleton;`
- L262 _private member_ `FSimpleMulticastDelegate& OnPostUndo;`

#### class `SPersonaPreviewPropertyEditor`  
`class SPersonaPreviewPropertyEditor : public SSingleObjectDetailsPanel`  
_L268-294_
- inherits: `SSingleObjectDetailsPanel`
- L271 _public function_ `SLATE_BEGIN_ARGS(SPersonaPreviewPropertyEditor)`
- L276 _private member_ `TWeakPtr<IPersonaPreviewScene> PreviewScene;` — Pointer to preview scene
- L277 _private member_ `TWeakPtr<FBlueprintEditor> BPEditor;`
- L281 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<IPersonaPreviewScene> InPreviewScene, TSharedRef<FBlueprintEditor> InBPEditor);`
- L284 _public prototype_ `virtual UObject* GetObjectToObserve() const override;` — SSingleObjectDetailsPanel interface
- L285 _public prototype_ `virtual TSharedRef<SWidget> PopulateSlot(TSharedRef<SWidget> PropertyEditorWidget) override;`
- L289 _private prototype_ `void HandlePropertyChanged(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L290 _private prototype_ `FReply HandleApplyChanges();`
- L293 _private member_ `bool bPropertyEdited;`

#### enum `EAnimBlueprintEditorMode::Type`  
`enum Type`  
_L301-305_
- L303 _public enumerator_ `PreviewMode`
- L304 _public enumerator_ `DefaultsMode`

#### struct `FAnimBlueprintPreviewEditorSummoner`  
`struct FAnimBlueprintPreviewEditorSummoner : public FWorkflowTabFactory`  
_L308-328_
- inherits: `FWorkflowTabFactory`
- L311 _public prototype_ `FAnimBlueprintPreviewEditorSummoner(TSharedPtr<class FBlueprintEditor> InBlueprintEditor, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene);`
- L313 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L315 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L319 _private prototype_ `EVisibility IsEditorVisible(EAnimBlueprintEditorMode::Type Mode) const;` — Delegates to customize tab look based on selected mode
- L320 _private prototype_ `ECheckBoxState IsChecked(EAnimBlueprintEditorMode::Type Mode) const;`
- L323 _private prototype_ `void OnCheckedChanged(ECheckBoxState NewType, EAnimBlueprintEditorMode::Type Mode);` — Handle changing of editor mode
- L324 _private member_ `EAnimBlueprintEditorMode::Type CurrentMode;`
- L326 _private member_ `TWeakPtr<class FBlueprintEditor> BlueprintEditor;`
- L327 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScene;`

#### class `FAnimBlueprintParentPlayerEditorSummoner`  
`class FAnimBlueprintParentPlayerEditorSummoner : public FWorkflowTabFactory`  
_L332-343_
- inherits: `FWorkflowTabFactory`
- desc: FAnimBlueprintParentPlayerEditorSummoner
- L335 _public prototype_ `FAnimBlueprintParentPlayerEditorSummoner(TSharedPtr<class FBlueprintEditor> InBlueprintEditor, FSimpleMulticastDelegate& InOnPostUndo);`
- L337 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L338 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L341 _private member_ `TWeakPtr<class FBlueprintEditor> BlueprintEditor;`
- L342 _private member_ `FSimpleMulticastDelegate& OnPostUndo;`

#### class `FPoseWatchManagerSummoner`  
`class FPoseWatchManagerSummoner : public FWorkflowTabFactory`  
_L347-357_
- inherits: `FWorkflowTabFactory`
- desc: FPoseWatchManagerSummoner
- L350 _public prototype_ `FPoseWatchManagerSummoner(TSharedPtr<class FBlueprintEditor> InBlueprintEditor);`
- L352 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L353 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L356 _private member_ `TWeakPtr<class FBlueprintEditor> BlueprintEditor;`

#### struct `FAdvancedPreviewSceneTabSummoner`  
`struct FAdvancedPreviewSceneTabSummoner : public FWorkflowTabFactory`  
_L363-382_
- inherits: `FWorkflowTabFactory`
- L366 _public prototype_ `FAdvancedPreviewSceneTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene);`
- L367 _public prototype_ `FAdvancedPreviewSceneTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene, const FPersonaAdvancedPreviewSceneTabSettings& InDetailCustomizationSettings);`
- L369 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L370 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L374 _private prototype_ `TSharedRef<class IDetailCustomization> CustomizePreviewSceneDescription();` — Customize the details of the scene setup object
- L377 _private prototype_ `TSharedRef<class IPropertyTypeCustomization> CustomizePreviewMeshCollectionEntry();` — Customize a preview mesh collection entry
- L380 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScene;`
- L381 _private member_ `FPersonaAdvancedPreviewSceneTabSettings DetailCustomizationSettings;`

#### struct `FPersonaDetailsTabSummoner`  
`struct FPersonaDetailsTabSummoner : public FWorkflowTabFactory`  
_L387-397_
- inherits: `FWorkflowTabFactory`
- L390 _public prototype_ `FPersonaDetailsTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, FOnDetailsCreated InOnDetailsCreated);`
- L391 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L392 _public prototype_ `virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;`
- L395 _private member_ `FOnDetailsCreated OnDetailsCreated;`
- L396 _private member_ `TSharedPtr<class SPersonaDetails> PersonaDetails;`

#### struct `FAssetPropertiesSummoner`  
`struct FAssetPropertiesSummoner : public FWorkflowTabFactory`  
_L402-414_
- inherits: `FWorkflowTabFactory`
- L404 _public prototype_ `FAssetPropertiesSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, FOnGetAsset InOnGetAsset, FOnDetailsCreated InOnDetailsCreated);`
- L407 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L408 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L412 _private member_ `FOnGetAsset OnGetAsset;`
- L413 _private member_ `FOnDetailsCreated OnDetailsCreated;`

#### struct `FAnimAttributeViewerTabSummoner`  
`struct FAnimAttributeViewerTabSummoner : public FWorkflowTabFactory`  
_L419-435_
- inherits: `FWorkflowTabFactory`
- L422 _public prototype_ `FAnimAttributeViewerTabSummoner(TSharedPtr<class FAssetEditorToolkit> InHostingApp, const TSharedRef<IPersonaPreviewScene>& InPreviewScene);`
- L424 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L427 _public function_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override` — Create a tooltip widget for the tab
- L433 _private member_ `TWeakPtr<class IEditableSkeleton> EditableSkeleton;`
- L434 _private member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScene;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define LOCTEXT_NAMESPACE "PersonaMode"`
- L299 _namespace_ `namespace EAnimBlueprintEditorMode`

### `Source/Editor/Persona/Private/ViewportToolbar/AnimViewportContext.h` (Private)


#### class `UAnimViewportContext`  
`class UAnimViewportContext : public UObject`  
_L9-16_
- reflection: `UCLASS()`
- inherits: `UObject`
- L14 _public member_ `TWeakPtr<SAnimationEditorViewportTabBody> ViewportTabBody;`
- L15 _public member_ `TWeakPtr<IPersonaPreviewScene> PersonaPreviewScene;`

### `Source/Editor/Persona/Private/ViewportToolbar/AnimationEditorMakeShowBonesMenuSection.h` (Private)


#### enum `UE::Persona::ViewportToolbar::EShowBonesMenuEntryFlags`  
`enum class EShowBonesMenuEntryFlags : uint8`  
_L13-24_
- L15 _public enumerator_ `BoneSize = 1 << 0`
- L16 _public enumerator_ `DrawAll = 1 << 1`
- L17 _public enumerator_ `DrawSelected = 1 << 2`
- L18 _public enumerator_ `DrawSelectedAndParents = 1 << 3`
- L19 _public enumerator_ `DrawSelectedAndChildren = 1 << 4`
- L20 _public enumerator_ `DrawSelectedAndParentsAndChildren = 1 << 5`
- L21 _public enumerator_ `DrawNone = 1 << 6`
- L23 _public enumerator_ `AllFlags = 0xFF`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PERSONA_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Persona` (scope `UE`)
- L11 _namespace_ `namespace ViewportToolbar` (scope `UE::Persona`)
- L25 _prototype_ `ENUM_CLASS_FLAGS(EShowBonesMenuEntryFlags);` (scope `UE::Persona::ViewportToolbar`)
- L28 _prototype_ `void MakeShowBonesMenuSection(UToolMenu* ToolMenu, const EShowBonesMenuEntryFlags Flags = EShowBonesMenuEntryFlags::AllFlags);` (scope `UE::Persona::ViewportToolbar`) — Creates the Show Bones section in a tool menu, optionally with flags what to show

### `Source/Editor/Persona/Private/ViewportToolbar/AnimationEditorMenus.h` (Private)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace AnimationEditor` (scope `UE`)
- L20 _prototype_ `void ExtendCameraMenu(FName InCameraOptionsMenuName);` (scope `UE::AnimationEditor`)
- L22 _prototype_ `void FillFollowModeSubmenu(UToolMenu* InMenu);` (scope `UE::AnimationEditor`)
- L23 _prototype_ `TSharedRef<SWidget> CreateFollowModeMenuWidget(const TWeakPtr<SAnimationEditorViewportTabBody>& InAnimEditorViewportTab);` (scope `UE::AnimationEditor`)
- L25 _prototype_ `TSharedRef<SWidget> MakeFollowBoneWidget( const TWeakPtr<SAnimationEditorViewportTabBody>& InViewport, const TWeakPtr<SComboButton>& InWeakComboButton );` (scope `UE::AnimationEditor`)
- L29 _prototype_ `FToolMenuEntry CreateShowSubmenu();` (scope `UE::AnimationEditor`)
- L30 _prototype_ `void FillShowSubmenu(UToolMenu* InMenu, bool bInShowViewportStatsToggle = true);` (scope `UE::AnimationEditor`)
- L31 _prototype_ `TSharedRef<SWidget> CreateShowMenuWidget( const TSharedRef<SEditorViewport>& InViewport, const TArray<TSharedPtr<FExtender>>& InExtenders, bool bInShowViewportStatsToggle );` (scope `UE::AnimationEditor`)
- L35 _prototype_ `FToolMenuEntry CreateTurnTableMenu();` (scope `UE::AnimationEditor`)
- L36 _prototype_ `void FillTurnTableSubmenu(UToolMenu* InMenu);` (scope `UE::AnimationEditor`)
- L37 _prototype_ `TSharedRef<SWidget> GenerateTurnTableMenu(const TWeakPtr<SAnimationEditorViewportTabBody>& InAnimEditorViewportTab);` (scope `UE::AnimationEditor`)
- L39 _prototype_ `void AddSceneElementsSection(UToolMenu* InMenu);` (scope `UE::AnimationEditor`)
- L41 _prototype_ `FToolMenuEntry CreateLODSubmenu();` (scope `UE::AnimationEditor`)
- L42 _prototype_ `FText GetLODMenuLabel(const TWeakPtr<SAnimationEditorViewportTabBody>& InAnimEditorViewportTab);` (scope `UE::AnimationEditor`)
- L43 _prototype_ `TSharedRef<SWidget> GenerateLODMenuWidget(const TWeakPtr<SAnimationEditorViewportTabBody>& InAnimEditorViewportTab);` (scope `UE::AnimationEditor`)
- L46 _prototype_ `FToolMenuEntry CreateSkinWeightProfileMenu();` (scope `UE::AnimationEditor`)
- L47 _prototype_ `FText GetSkinWeightProfileMenuLabel(const TWeakPtr<SAnimationEditorViewportTabBody>& InAnimEditorViewportTab);` (scope `UE::AnimationEditor`)
- L49 _prototype_ `TSharedRef<SWidget> MakeFloorOffsetWidget(const TWeakPtr<SAnimationEditorViewportTabBody>& InAnimEditorViewportTabWeak);` (scope `UE::AnimationEditor`)
- L51 _prototype_ `void ExtendViewModesSubmenu(FName InViewModesSubmenuName);` (scope `UE::AnimationEditor`)
- L52 _prototype_ `TSharedRef<FExtender> GetViewModesLegacyExtenders(const TWeakPtr<SAnimationEditorViewportTabBody>& InViewport);` (scope `UE::AnimationEditor`)
- L54 _prototype_ `void AddPhysicsMenu(FName InPhysicsSubmenuName, FToolMenuInsert InInsertPosition);` (scope `UE::AnimationEditor`)
- L55 _prototype_ `void FillPhysicsSubmenu(UToolMenu* InMenu);` (scope `UE::AnimationEditor`)
- L56 _prototype_ `TSharedRef<SWidget> GeneratePhysicsMenuWidget(const TWeakPtr<SAnimationEditorViewportTabBody>& InAnimEditorViewportTab, const TSharedPtr<FExtender>& MenuExtender);` (scope `UE::AnimationEditor`)
- L58 _prototype_ `void ExtendPreviewSceneSettingsSubmenu(FName InSubmenuName);` (scope `UE::AnimationEditor`)
- L60 _prototype_ `FToolMenuEntry CreatePlaybackSubmenu();` (scope `UE::AnimationEditor`)
- L61 _prototype_ `TSharedRef<SWidget> GeneratePlaybackMenu(const TWeakPtr<FAnimationEditorPreviewScene>& InAnimationEditorPreviewScene, const TArray<TSharedPtr<FExtender>>& InExtenders);` (scope `UE::AnimationEditor`)
- L62 _prototype_ `FText GetPlaybackMenuLabel(const TWeakPtr<IPersonaPreviewScene>& InPersonaPreviewScene);` (scope `UE::AnimationEditor`)

### `Source/Editor/Persona/Private/ViewportToolbar/AnimationEditorWidgets.h` (Private)


#### class `UE::AnimationEditor::SCustomAnimationSpeedSetting`  
`class SCustomAnimationSpeedSetting : public SCompoundWidget`  
_L12-30_
- inherits: `SCompoundWidget`
- desc: Class definition which represents widget to modify animation speed settings
- L16 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnCustomSpeedChanged, float);` — Notification for numeric value change
- L18 _public function_ `SLATE_BEGIN_ARGS(SCustomAnimationSpeedSetting)`
- L21 _public prototype_ `SLATE_ATTRIBUTE(float, CustomSpeed) SLATE_EVENT(FOnCustomSpeedChanged, OnCustomSpeedChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L28 _protected member_ `TAttribute<float> CustomSpeed = 1.0f;`
- L29 _protected member_ `FOnCustomSpeedChanged OnCustomSpeedChanged;`

#### class `UE::AnimationEditor::SBoneDrawSizeSetting`  
`class SBoneDrawSizeSetting : public SCompoundWidget`  
_L33-47_
- inherits: `SCompoundWidget`
- desc: Class definition which represents widget to modify Bone Draw Size in viewport
- L37 _public function_ `SLATE_BEGIN_ARGS(SBoneDrawSizeSetting)`
- L40 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SAnimationEditorViewportTabBody>, AnimEditorViewport) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L46 _protected member_ `TWeakPtr<SAnimationEditorViewportTabBody> AnimViewportPtr;`

#### class `UE::AnimationEditor::SClothWindSettings`  
`class SClothWindSettings : public SCompoundWidget`  
_L51-71_
- inherits: `SCompoundWidget`
- desc: Class definition which represents widget to modify strength of wind for clothing
- L54 _public function_ `SLATE_BEGIN_ARGS(SClothWindSettings)`
- L58 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SAnimationEditorViewportTabBody>, AnimEditorViewport) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L66 _protected prototype_ `bool IsWindEnabled() const;` — Callback function which determines whether this widget is enabled
- L70 _protected member_ `TWeakPtr<SAnimationEditorViewportTabBody> AnimViewportPtr;` — The viewport hosting this widget

#### class `UE::AnimationEditor::SGravitySettings`  
`class SGravitySettings : public SCompoundWidget`  
_L74-93_
- inherits: `SCompoundWidget`
- desc: Class definition which represents widget to modify gravity for preview
- L77 _public function_ `SLATE_BEGIN_ARGS(SGravitySettings)`
- L81 _public prototype_ `SLATE_ARGUMENT(TWeakPtr<SAnimationEditorViewportTabBody>, AnimEditorViewport) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L87 _protected prototype_ `FReply OnDecreaseGravityScale() const;`
- L89 _protected prototype_ `FReply OnIncreaseGravityScale() const;`
- L92 _protected member_ `TWeakPtr<SAnimationEditorViewportTabBody> AnimViewportPtr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace AnimationEditor` (scope `UE`)
- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCustomSpeedChanged, float);` — Notification for numeric value change

### `Source/Editor/Persona/Public/AnimAssetFindReplace.h` (Public)


#### class `UAnimAssetFindReplaceContext`  
`class UAnimAssetFindReplaceContext : public UObject`  
_L20-27_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Context for toolbar
- L26 _public member_ `TWeakPtr<SAnimAssetFindReplace> Widget;` — Weak ptr to the find/replace widget

#### enum `EAnimAssetFindReplaceMode`  
`enum class EAnimAssetFindReplaceMode : int32`  
_L30-34_
- desc: The mode configuration that the dialog can take
- L32 _public enumerator_ `Find`
- L33 _public enumerator_ `Replace`

#### class `UAnimAssetFindReplaceProcessor`  
`class UAnimAssetFindReplaceProcessor : public UObject`  
_L38-104_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Processor base class to allow systems to add their own find/replace functionality
- L46 _private prototype_ `void Initialize(TSharedRef<SAnimAssetFindReplace> InWidget);` — Initially setup the processor, binding it to the specified widget
- L50 _public prototype_ `virtual bool SupportsMode(EAnimAssetFindReplaceMode InMode) const PURE_VIRTUAL(UAnimAssetFindReplaceProcessor::SupportsMode, return false;);` — Whether this processor supports the specified mode
- L53 _public prototype_ `virtual FString GetFindResultStringFromAssetData(const FAssetData& InAssetData) const PURE_VIRTUAL(UAnimAssetFindReplaceProcessor::GetFindResultStringFromAssetData, return FString(););` — Builds results string to display from the supplied asset data
- L56 _public prototype_ `virtual TConstArrayView<UClass*> GetSupportedAssetTypes() const PURE_VIRTUAL(UAnimAssetFindReplaceProcessor::GetSupportedAssetTypes, return TConstArrayView<UClass*>(););` — Get all the asset types that are supported by this processor
- L65 _public prototype_ `virtual bool ShouldFilterOutAsset(const FAssetData& InAssetData, bool& bOutIsOldAsset) const PURE_VIRTUAL(UAnimAssetFindReplaceProcessor::ShouldFilterOutAsset, return false;);` — Whether the asset in question is a valid search result or not @param InAssetData		The asset in question @param bOutIsOldAsset	Whether the asset is 'old', i.e. it needs to be fully loaded to determine whether it is filtered, as relevant data is not saved in the asset registry for it
- L68 _public prototype_ `virtual void ReplaceInAsset(const FAssetData& InAssetData) const PURE_VIRTUAL(UAnimAssetFindReplaceProcessor::ReplaceInAsset, );` — Perform a replace operation on the specified asset
- L71 _public prototype_ `virtual void RemoveInAsset(const FAssetData& InAssetData) const PURE_VIRTUAL(UAnimAssetFindReplaceProcessor::RemoveInAsset, );` — Perform a remove operation on the specified asset
- L74 _public function_ `virtual void ExtendToolbar(FToolMenuSection& InSection)` — Optional override to extend the toolbar when this processor is selected
- L77 _public prototype_ `virtual TSharedRef<SWidget> MakeFindReplaceWidget() PURE_VIRTUAL(UAnimAssetFindReplaceProcessor::MakeFindReplaceWidget, return SNullWidget::NullWidget;);` — Make or return the widget used to edit find/replace parameters
- L80 _public function_ `virtual void FocusInitialWidget()` — Optional override allowing a widget to be focused when the find/replace widget is initially displayed
- L83 _public prototype_ `virtual bool CanCurrentlyReplace() const PURE_VIRTUAL(UAnimAssetFindReplaceProcessor::CanCurrentlyReplace, return false;);` — Allows control over when the replace option is available to users
- L86 _public prototype_ `virtual bool CanCurrentlyRemove() const PURE_VIRTUAL(UAnimAssetFindReplaceProcessor::CanCurrentlyRemove, return false;);` — Allows control over when the remove option is available to users
- L89 _public function_ `virtual void RefreshCachedData()` — Called by the UI to deferred-refresh any cached data that this processor holds after asset operations have completed
- L93 _protected prototype_ `void RequestRefreshUI();` — Requests the entire find UI to be refreshed
- L96 _protected prototype_ `void RequestRefreshCachedData();` — Requests cached data and search results
- L99 _protected prototype_ `void RequestRefreshSearchResults();` — Requests search results to be refreshed
- L103 _private member_ `TWeakPtr<SAnimAssetFindReplace> Widget;` — Weak ptr to the find/replace widget

#### class `UAnimAssetFindReplaceProcessor_StringBase`  
`class UAnimAssetFindReplaceProcessor_StringBase : public UAnimAssetFindReplaceProcessor`  
_L108-197_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAnimAssetFindReplaceProcessor`
- desc: Processor for string-based animation asset operations
- L113 _public function_ `UAnimAssetFindReplaceProcessor_StringBase() : AutoCompleteItems(MakeShared<TArray<TSharedPtr<FString>>>())`
- L118 _public prototype_ `void SetFindString(const FString& InString);` — Set the current find string
- L121 _public function_ `FStringView GetFindString() const` — Get the current find string
- L124 _public function_ `const FString& GetFindStringRef() const` — Get the current find string
- L127 _public prototype_ `void SetReplaceString(const FString& InString);` — Set the current replace string
- L130 _public function_ `FStringView GetReplaceString() const` — Get the current replace string
- L133 _public function_ `const FString& GetReplaceStringRef() const` — Get the current replace string
- L136 _public prototype_ `void SetSkeletonFilter(const FAssetData& InSkeletonFilter);` — Set the current skeleton filter
- L139 _public function_ `const FAssetData& GetSkeletonFilter() const` — Get the current skeleton filter
- L142 _public prototype_ `void SetFindWholeWord(bool bInFindWholeWord);` — Sets whether to match whole words when searching strings
- L145 _public function_ `bool GetFindWholeWord() const` — Gets whether to match whole words when searching strings
- L148 _public prototype_ `void SetSearchCase(ESearchCase::Type InSearchCase);` — Sets case comparison to use when searching
- L151 _public function_ `ESearchCase::Type GetSearchCase() const` — Gets case comparison to use when searching
- L154 _public function_ `virtual void GetAutoCompleteNames(TArrayView<FAssetData> InAssetDatas, TSet<FString>& OutUniqueNames) const` — Optional override point for derived classes to supply auto complete names to display in the UI
- L158 _protected function_ `virtual bool SupportsMode(EAnimAssetFindReplaceMode InMode) const override` — UAnimAssetFindReplaceProcessor interface
- L159 _protected prototype_ `virtual void ExtendToolbar(FToolMenuSection& InSection) override;`
- L160 _protected prototype_ `virtual TSharedRef<SWidget> MakeFindReplaceWidget() override;`
- L161 _protected prototype_ `virtual void FocusInitialWidget() override;`
- L162 _protected prototype_ `virtual bool CanCurrentlyReplace() const override;`
- L163 _protected prototype_ `virtual bool CanCurrentlyRemove() const override;`
- L164 _protected prototype_ `virtual void RefreshCachedData() override;`
- L168 _protected prototype_ `bool NameMatches(FStringView InNameStringView) const;` — Check if the supplied string matches the find parameters
- L172 _private member_ `FString FindString;` — The find string
- L175 _private member_ `FString ReplaceString;` — The replace string
- L178 _private member_ `FAssetData SkeletonFilter;` — The skeleton to filter by
- L181 _private member_ `bool bFindWholeWord = false;` — Whether to match whole words when searching strings
- L184 _private member_ `ESearchCase::Type SearchCase = ESearchCase::IgnoreCase;` — Case comparison to use when searching
- L187 _private member_ `TSharedPtr<TArray<TSharedPtr<FString>>> AutoCompleteItems;` — Cached auto-complete items
- L190 _private member_ `TWeakPtr<SWidget> FindReplaceWidget;` — Cached find/replace widget
- L193 _private member_ `TWeakPtr<SAutoCompleteSearchBox> FindSearchBox;` — Search box widget for 'find'
- L196 _private member_ `TWeakPtr<SAutoCompleteSearchBox> ReplaceSearchBox;` — Search box widget for 'replace'

#### struct `FAnimAssetFindReplaceConfig`  
`struct FAnimAssetFindReplaceConfig`  
_L200-204_
- desc: Configuration for the find/replace tab
- L203 _public member_ `TSubclassOf<UAnimAssetFindReplaceProcessor> InitialProcessorClass = nullptr;` — The initial processor class to use

#### class `IAnimAssetFindReplace`  
`class IAnimAssetFindReplace : public SCompoundWidget`  
_L207-225_
- inherits: `SCompoundWidget`
- desc: Public interface to the find/replace widget
- L211 _public prototype_ `virtual void SetCurrentProcessor(TSubclassOf<UAnimAssetFindReplaceProcessor> InProcessorClass) = 0;` — Sets the type of the current processor we are using to find/replace with
- L214 _public prototype_ `virtual UAnimAssetFindReplaceProcessor* GetCurrentProcessor() const = 0;` — Gets the current processor instance
- L217 _public prototype_ `virtual UAnimAssetFindReplaceProcessor* GetProcessor(TSubclassOf<UAnimAssetFindReplaceProcessor> InProcessorClass) const = 0;` — Gets the processor instance of the specified type
- L221 _public function_ `template <typename ProcessorType> ProcessorType* GetProcessor() const` — Gets the processor instance of the specified type

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PERSONA_API`

### `Source/Editor/Persona/Public/AnimAssetFindReplaceCurves.h` (Public)


#### class `UAnimAssetFindReplaceCurves`  
`class UAnimAssetFindReplaceCurves : public UAnimAssetFindReplaceProcessor_StringBase`  
_L11-45_
- reflection: `UCLASS(MinimalAPI, DisplayName="Curves")`
- inherits: `UAnimAssetFindReplaceProcessor_StringBase`
- desc: Find, replace and remove curves across assets
- L16 _private prototype_ `virtual FString GetFindResultStringFromAssetData(const FAssetData& InAssetData) const override;` — UAnimAssetFindReplaceProcessor interface
- L17 _private prototype_ `virtual TConstArrayView<UClass*> GetSupportedAssetTypes() const override;`
- L18 _private prototype_ `virtual bool ShouldFilterOutAsset(const FAssetData& InAssetData, bool& bOutIsOldAsset) const override;`
- L19 _private prototype_ `virtual void ReplaceInAsset(const FAssetData& InAssetData) const override;`
- L20 _private prototype_ `virtual void RemoveInAsset(const FAssetData& InAssetData) const override;`
- L21 _private prototype_ `virtual void ExtendToolbar(FToolMenuSection& InSection) override;`
- L24 _private prototype_ `virtual void GetAutoCompleteNames(TArrayView<FAssetData> InAssetDatas, TSet<FString>& OutUniqueNames) const override;` — UAnimAssetFindReplaceProcessor_StringBase interface
- L28 _public prototype_ `void SetSearchMorphTargets(bool bInSearchMorphTargets);` — Set whether to search morph targets when searching for curves
- L31 _public function_ `bool GetSearchMorphTargets() const` — Get whether to search morph targets when searching for curves
- L34 _public prototype_ `void SetSearchMaterials(bool bInSearchMaterials);` — Set whether to search material parameters when searching for curves
- L37 _public function_ `bool GetSearchMaterials() const` — Get whether to search material parameters when searching for curves
- L41 _private member_ `bool bSearchMorphTargets = false;` — Whether to search morph targets when searching for curves
- L44 _private member_ `bool bSearchMaterials = false;` — Whether to search materials when searching for curves

### `Source/Editor/Persona/Public/AnimAssetFindReplaceNotifies.h` (Public)


#### class `UAnimAssetFindReplaceNotifies`  
`class UAnimAssetFindReplaceNotifies : public UAnimAssetFindReplaceProcessor_StringBase`  
_L11-24_
- reflection: `UCLASS(MinimalAPI, DisplayName="Notifies")`
- inherits: `UAnimAssetFindReplaceProcessor_StringBase`
- desc: Find, replace and remove notifies across assets
- L16 _private prototype_ `virtual FString GetFindResultStringFromAssetData(const FAssetData& InAssetData) const override;` — UAnimAssetFindReplaceProcessor interface
- L17 _private prototype_ `virtual TConstArrayView<UClass*> GetSupportedAssetTypes() const override;`
- L18 _private prototype_ `virtual bool ShouldFilterOutAsset(const FAssetData& InAssetData, bool& bOutIsOldAsset) const override;`
- L19 _private prototype_ `virtual void ReplaceInAsset(const FAssetData& InAssetData) const override;`
- L20 _private prototype_ `virtual void RemoveInAsset(const FAssetData& InAssetData) const override;`
- L23 _private prototype_ `virtual void GetAutoCompleteNames(TArrayView<FAssetData> InAssetDatas, TSet<FString>& OutUniqueNames) const override;` — UAnimAssetFindReplaceProcessor_StringBase interface

### `Source/Editor/Persona/Public/AnimAssetFindReplaceSyncMarkers.h` (Public)


#### class `UAnimAssetFindReplaceSyncMarkers`  
`class UAnimAssetFindReplaceSyncMarkers : public UAnimAssetFindReplaceProcessor_StringBase`  
_L11-24_
- reflection: `UCLASS(MinimalAPI, DisplayName="Sync Markers")`
- inherits: `UAnimAssetFindReplaceProcessor_StringBase`
- desc: Find, replace and remove sync markers across assets
- L16 _private prototype_ `virtual FString GetFindResultStringFromAssetData(const FAssetData& InAssetData) const override;` — UAnimAssetFindReplaceProcessor interface
- L17 _private prototype_ `virtual TConstArrayView<UClass*> GetSupportedAssetTypes() const override;`
- L18 _private prototype_ `virtual bool ShouldFilterOutAsset(const FAssetData& InAssetData, bool& bOutIsOldAsset) const override;`
- L19 _private prototype_ `virtual void ReplaceInAsset(const FAssetData& InAssetData) const override;`
- L20 _private prototype_ `virtual void RemoveInAsset(const FAssetData& InAssetData) const override;`
- L23 _private prototype_ `virtual void GetAutoCompleteNames(TArrayView<FAssetData> InAssetDatas, TSet<FString>& OutUniqueNames) const override;` — UAnimAssetFindReplaceProcessor_StringBase interface

### `Source/Editor/Persona/Public/AnimNotifyNodeFactory.h` (Public)


#### struct `FAnimNotifyNodeFactory`  
`struct FAnimNotifyNodeFactory`  
_L19-35_
- L23 _public prototype_ `static FDelegateHandle RegisterFactory(FAnimNotifyNodeFactoryFunction InFactory);` — Allow others to register custom node types for custom notifies.
- L26 _public prototype_ `static void UnregisterFactory(FDelegateHandle InHandle);` — Unregister the Factory
- L29 _public function_ `static const TArray<FAnimNotifyNodeFactoryFunction>& GetRegisteredFactories()` — Get registered factories.
- L33 _private member_ `static TArray<FAnimNotifyNodeFactoryFunction> RegisteredFactories;`
- L34 _private member_ `static TArray<FDelegateHandle> RegisteredFactoryHandles;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PERSONA_API`
- L14 _typedef_ `typedef TFunction<TSharedPtr<class SAnimNotifyNode>(struct FAnimNotifyEvent*)> FAnimNotifyNodeFactoryFunction;`

### `Source/Editor/Persona/Public/AnimationEditorPreviewActor.h` (Public)


#### class `AAnimationEditorPreviewActor`  
`class AAnimationEditorPreviewActor : public AActor`  
_L11-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- L17 _public prototype_ `virtual void K2_DestroyActor() override;` — AActor interface

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PERSONA_API`

### `Source/Editor/Persona/Public/AnimationEditorTypes.h` (Public)


#### enum `ELocalAxesMode::Type`  
`enum Type`  
_L10-16_
- L12 _public enumerator_ `None`
- L13 _public enumerator_ `Selected`
- L14 _public enumerator_ `All`
- L15 _public enumerator_ `NumAxesModes`

#### enum `EDisplayInfoMode::Type`  
`enum Type`  
_L24-31_
- L26 _public enumerator_ `None`
- L27 _public enumerator_ `Basic`
- L28 _public enumerator_ `Detailed`
- L29 _public enumerator_ `SkeletalControls`
- L30 _public enumerator_ `NumInfoModes`

#### enum `EAnimationPlaybackSpeeds::Type`  
`enum Type`  
_L36-48_
- L38 _public enumerator_ `OneTenth = 0`
- L39 _public enumerator_ `Quarter`
- L40 _public enumerator_ `Half`
- L41 _public enumerator_ `ThreeQuarters`
- L42 _public enumerator_ `Normal`
- L43 _public enumerator_ `Double`
- L44 _public enumerator_ `FiveTimes`
- L45 _public enumerator_ `TenTimes`
- L46 _public enumerator_ `Custom`
- L47 _public enumerator_ `NumPlaybackSpeeds`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ELocalAxesMode`
- L22 _namespace_ `namespace EDisplayInfoMode`
- L34 _namespace_ `namespace EAnimationPlaybackSpeeds`
- L50 _externvar_ `extern float Values[NumPlaybackSpeeds];` (scope `EAnimationPlaybackSpeeds`)

### `Source/Editor/Persona/Public/AnimationEditorViewportClient.h` (Public)


#### class `FAnimationViewportClient`  
`class FAnimationViewportClient : public FEditorViewportClient, public TSharedFromThis<FAnimationViewportClient>`  
_L33-524_
- inherits: `FEditorViewportClient,TSharedFromThis<FAnimationViewportClient>`
- L38 _protected prototype_ `void ShowBoneNames(FCanvas* Canvas, FSceneView* View, UDebugSkelMeshComponent* MeshComponent);` — Function to display bone names
- L41 _protected prototype_ `void ShowAttributeNames(FCanvas* Canvas, FSceneView* View, UDebugSkelMeshComponent* MeshComponent) const;` — Function to display transform attribute names
- L44 _protected prototype_ `void DrawNodeDebugLines(TArray<FText>& Lines, FCanvas* Canvas, FSceneView* View);` — Function to display debug lines generated from skeletal controls in animBP mode
- L47 _public prototype_ `FAnimationViewportClient(const TSharedRef<class IPersonaPreviewScene>& InPreviewScene, const TSharedRef<class SAnimationEditorViewport>& InAnimationEditorViewport, const TSharedRef<class FAssetEditorToolkit>& InAssetEditorToolkit, int32 InViewportIndex, bool bInShowStats);`
- L50 _public prototype_ `void Initialize();`
- L53 _public prototype_ `virtual void Tick(float DeltaSeconds) override;` — FEditorViewportClient interface
- L54 _public prototype_ `virtual void Draw(const FSceneView* View,FPrimitiveDrawInterface* PDI) override;`
- L55 _public prototype_ `virtual void DrawCanvas( FViewport& InViewport, FSceneView& View, FCanvas& Canvas ) override;`
- L56 _public prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L57 _public prototype_ `virtual bool InputAxis(const FInputKeyEventArgs& EventArgs) override;`
- L58 _public prototype_ `virtual void ReceivedFocus(FViewport* InViewport) override;`
- L59 _public prototype_ `virtual void LostFocus(FViewport* InViewport) override;`
- L60 _public prototype_ `virtual void SetCameraSpeedSettings(const FEditorViewportCameraSpeedSettings& InCameraSpeedSettings) override;`
- L63 _public prototype_ `virtual void UpdateBonesToDraw();` — Sets what bones are drawn by DrawMeshBones and ShowBoneNames
- L67 _public prototype_ `virtual void TrackingStarted( const struct FInputEventState& InInputState, bool bIsDragging, bool bNudge ) override;` — virtual void ProcessClick(class FSceneView& View, class HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override; virtual bool InputWidgetDelta( FViewport* Viewport, EAxisList::Type CurrentAxis, FVector& Drag, FRotator& Rot, FVector& Scale ) override;
- L68 _public prototype_ `virtual void TrackingStopped() override;`
- L72 _public prototype_ `virtual FVector GetWidgetLocation() const override;` — virtual UE::Widget::EWidgetMode GetWidgetMode() const override; virtual void SetWidgetMode(UE::Widget::EWidgetMode InWidgetMode) override; virtual bool CanSetWidgetMode(UE::Widget::EWidgetMode NewMode) const override;
- L73 _public prototype_ `virtual FMatrix GetWidgetCoordSystem() const override;`
- L74 _public prototype_ `virtual ECoordSystem GetWidgetCoordSystemSpace() const override;`
- L75 _public prototype_ `virtual void SetWidgetCoordSystemSpace(ECoordSystem NewCoordSystem) override;`
- L76 _public prototype_ `virtual void SetViewMode(EViewModeIndex InViewModeIndex) override;`
- L77 _public prototype_ `virtual void SetViewportType(ELevelViewportType InViewportType) override;`
- L78 _public prototype_ `virtual void RotateViewportType() override;`
- L79 _public prototype_ `virtual bool CanCycleWidgetMode() const override;`
- L80 _public prototype_ `virtual void SetupViewForRendering( FSceneViewFamily& ViewFamily, FSceneView& View ) override;`
- L81 _public prototype_ `virtual void HandleToggleShowFlag(FEngineShowFlags::EShowFlag EngineShowFlagIndex) override;`
- L82 _public prototype_ `virtual FMatrix CalcViewRotationMatrix(const FRotator& InViewRotation) const override;`
- L86 _public prototype_ `void DrawUVsForMesh(FViewport* InViewport, FCanvas* InCanvas, int32 InTextYPos, UDebugSkelMeshComponent* MeshComponent);` — Draw call to render UV overlay
- L89 _public prototype_ `void SetCameraFollowMode(EAnimationViewportCameraFollowMode Mode, FName InBoneName = NAME_None);` — Set the camera follow mode
- L92 _public prototype_ `void OnFocusViewportToSelection();` — Called when viewport focuses on a selection
- L95 _public prototype_ `EAnimationViewportCameraFollowMode GetCameraFollowMode() const;` — Get the camera follow mode
- L98 _public prototype_ `FName GetCameraFollowBoneName() const;` — Get the bone name to use when CameraFollowMode is EAnimationViewportCameraFollowMode::Bone
- L108 _public prototype_ `EAxis::Type GetBoneAsCameraAxis(EDirection Direction) const;` — Gets the axis for a direction when using the Bone As Camera follow mode
- L111 _public prototype_ `UE::Math::TVector<double> GetBoneAsCameraPositionOffset() const;` — Gets the position offset from the bone origin in world coordiantes for the Bone As Camera follow mode
- L114 _public prototype_ `FRotator GetBoneAsCameraRotationOffset() const;` — Gets the rotation offset from the bone in world coordiantes for the Bone As Camera follow mode
- L117 _public prototype_ `void SetBoneAsCameraAxis(EDirection Direction, EAxis::Type Axis);` — Sets the axis for a direction when using the Bone As Camera follow mode
- L120 _public prototype_ `void SetBoneAsCameraPositionOffset(UE::Math::TVector<double> Offset);` — Sets the position offset from the bone origin in world coordiantes for the Bone As Camera follow mode
- L123 _public prototype_ `void SetBoneAsCameraRotationOffset(const FRotator& Offset);` — Sets the rotation offset from the bone in world coordiantes for the Bone As Camera follow mode
- L126 _public prototype_ `void JumpToDefaultCamera();` — Jump to the meshes default camera
- L129 _public prototype_ `void SaveCameraAsDefault();` — Save current camera as default for mesh
- L132 _public prototype_ `bool CanSaveCameraAsDefault() const;` — Check whether we can save this camera as default
- L135 _public prototype_ `void ClearDefaultCamera();` — Clear any default camera for mesh
- L138 _public prototype_ `bool HasDefaultCameraSet() const;` — Returns whether we have a default camera set for this mesh
- L141 _public prototype_ `void HandleSkeletalMeshChanged(class USkeletalMesh* OldSkeletalMesh, class USkeletalMesh* NewSkeletalMesh);` — Handle the skeletal mesh mesh component being used for preview changing
- L144 _public prototype_ `void HandleOnMeshChanged();` — Handle a change in the skeletal mesh mesh component being used for preview changing
- L147 _public prototype_ `void HandleOnSkelMeshPhysicsCreated();` — Handle a change in the skeletal mesh phusics component being used for preview changing
- L150 _public prototype_ `void ShowBoneNames(FViewport* Viewport, FCanvas* Canvas, UDebugSkelMeshComponent* MeshComponent);` — Function to display bone names
- L153 _public prototype_ `void OnToggleAutoAlignFloor();` — Function to enable/disable floor auto align
- L156 _public prototype_ `bool IsAutoAlignFloor() const;` — Function to check whether floor is auto align or not
- L159 _public prototype_ `void OnToggleMuteAudio();` — Function to mute/unmute audio in the viewport
- L162 _public prototype_ `bool IsAudioMuted() const;` — Function to check whether audio is muted or not
- L165 _public prototype_ `void OnToggleUseAudioAttenuation();` — Set whether to use audio attenuation
- L168 _public prototype_ `bool IsUsingAudioAttenuation() const;` — Check whether we are using audio attenuation
- L171 _public prototype_ `void SetBackgroundColor(FLinearColor InColor);` — Function to set background color
- L174 _public prototype_ `float GetBrightnessValue() const;` — Function to get current brightness value
- L177 _public prototype_ `void SetBrightnessValue(float Value);` — Function to set brightness value
- L180 _public prototype_ `void SetLocalAxesMode(ELocalAxesMode::Type AxesMode);` — Function to set Local axes mode for the ELocalAxesType
- L183 _public prototype_ `bool IsLocalAxesModeSet(ELocalAxesMode::Type AxesMode) const;` — Local axes mode checking function for the ELocalAxesType
- L186 _public prototype_ `ELocalAxesMode::Type GetLocalAxesMode() const;` — Get the Bone local axis mode
- L189 _public prototype_ `void SetBoneDrawSize(const float InBoneDrawSize);` — Access Bone Draw size config option
- L190 _public prototype_ `float GetBoneDrawSize() const;`
- L193 _public prototype_ `void SetBoneDrawMode(EBoneDrawMode::Type AxesMode);` — Function to set Bone Draw  mode for the EBoneDrawType
- L196 _public prototype_ `bool IsBoneDrawModeSet(EBoneDrawMode::Type AxesMode) const;` — Bone Draw  mode checking function for the EBoneDrawType
- L199 _public prototype_ `EBoneDrawMode::Type GetBoneDrawMode() const;` — Get the Bone local axis mode
- L202 _public prototype_ `FSphere GetCameraTarget();` — Returns the desired target of the camera
- L205 _public prototype_ `void UpdateCameraSetup();` — Sets up the viewports camera (look-at etc) based on the current preview target
- L208 _public prototype_ `void FocusViewportOnSphere( FSphere& Sphere, bool bInstant = true );` — Places the viewport camera at a good location to view the supplied sphere
- L211 _public prototype_ `void FocusViewportOnPreviewMesh(bool bUseCustomCamera);` — Places the viewport camera at a good location to view the preview target
- L214 _public prototype_ `void ToggleCPUSkinning();` — Callback for toggling the normals show flag.
- L217 _public prototype_ `bool IsSetCPUSkinningChecked() const;` — Callback for checking the normals show flag.
- L220 _public prototype_ `void ToggleRotateCameraToFollowBone();` — Toggles whether to lock the camera's rotation to a specified bone's orientation
- L223 _public prototype_ `bool GetShouldRotateCameraToFollowBone() const;` — Whether or not to lock the camera's rotation to a specified bone's orientation
- L226 _public prototype_ `void ToggleShowNormals();` — Callback for toggling the normals show flag.
- L229 _public prototype_ `bool IsSetShowNormalsChecked() const;` — Callback for checking the normals show flag.
- L232 _public prototype_ `void ToggleShowTangents();` — Callback for toggling the tangents show flag.
- L235 _public prototype_ `bool IsSetShowTangentsChecked() const;` — Callback for checking the tangents show flag.
- L238 _public prototype_ `void ToggleShowBinormals();` — Callback for toggling the binormals show flag.
- L241 _public prototype_ `bool IsSetShowBinormalsChecked() const;` — Callback for checking the binormals show flag.
- L244 _public prototype_ `void SetDrawUVOverlay(bool bInDrawUVs);` — Callback for toggling UV drawing in the viewport
- L247 _public prototype_ `bool IsSetDrawUVOverlayChecked() const;` — Callback for checking whether the UV drawing is switched on.
- L250 _public function_ `int32 GetUVChannelToDraw() const` — Returns the UV Channel that will be drawn when Draw UV Overlay is turned on
- L253 _public function_ `void SetUVChannelToDraw(int32 UVChannel)` — Sets the UV Channel that will be drawn when Draw UV Overlay is turned on
- L256 _public prototype_ `float GetFloorOffset() const;` — Returns the floor height offset
- L259 _public prototype_ `void SetFloorOffset(float NewValue);` — Sets the floor height offset, saves it to config and invalidates the viewport so it shows up immediately
- L262 _public prototype_ `void OnSetShowMeshStats(int32 ShowMode);` — Function to set mesh stat drawing state
- L264 _public prototype_ `bool IsShowingMeshStats() const;` — Whether or not mesh stats are being displayed
- L266 _public prototype_ `bool IsShowingSelectedNodeStats() const;` — Whether or not selected node stats are being displayed
- L268 _public prototype_ `bool IsDetailedMeshStats() const;` — Whether detailed mesh stats are being displayed or basic mesh stats
- L270 _public prototype_ `int32 GetShowMeshStats() const;`
- L273 _public function_ `TSharedRef<class IPersonaPreviewScene> GetPreviewScene() const` — Get the preview scene we are viewing
- L276 _public function_ `TSharedRef<class FAssetEditorToolkit> GetAssetEditorToolkit() const` — Get the asset editor we are embedded in
- L279 _public prototype_ `bool ShouldDisplayAdditiveScaleErrorMessage() const;` — Handle error checking for additive base pose
- L282 _public prototype_ `static void DrawSockets(const UDebugSkelMeshComponent* InPreviewMeshComponent, TArray<USkeletalMeshSocket*>& InSockets, FSelectedSocketInfo InSelectedSocket, FPrimitiveDrawInterface* PDI, bool bUseSkeletonSocketColor);` — Draws Mesh Sockets in foreground - bUseSkeletonSocketColor = true for grey (skeleton), false for red (mesh)
- L285 _public prototype_ `static void RenderGizmo(const FTransform& Transform, FPrimitiveDrawInterface* PDI);` — Draws Gizmo for the Transform in foreground
- L288 _public prototype_ `FText GetDisplayInfo( bool bDisplayAllInfo ) const;` — Function to display warning and info text on the viewport when outside of animBP mode
- L291 _public function_ `int32 GetViewportIndex() const` — Get the viewport index (0-3) for this client
- L294 _protected prototype_ `virtual void PerspectiveCameraMoved() override;`
- L302 _private prototype_ `void UpdateAudioListener(const FSceneView& View);` — Updates the audio listener for this viewport @param View	The scene view to use when calculate the listener position
- L307 _private prototype_ `void UpdateAudioListener() const;` — Updates the audio listener for this viewport
- L312 _public member_ `UPersonaOptions* ConfigOption;` — persona config options
- L315 _public member_ `FOnBoneSizeSet OnSetBoneSize;` — allow client code to store/serialize bone size if desired
- L316 _public member_ `FOnGetBoneSize OnGetBoneSize;`
- L325 _private member_ `TSharedPtr<class IPersonaPreviewScene> PreviewScenePtr;` — Shared pointer back to the preview scene we are viewing Workaround fix for FORT-495476, UE-159733, UE-160424, UE-145060 We hold a shared because if the PreviewScene gets destroyed before we reach this class destructor, we can not unregister the callbacks from this class and we get crashes when any of the callbacks is triggered afterwards
- L328 _private member_ `TWeakPtr<class FAssetEditorToolkit> AssetEditorToolkitPtr;` — Weak pointer back to asset editor we are embedded in
- L331 _private member_ `UE::Widget::EWidgetMode WidgetMode;` — Current widget mode
- L334 _private member_ `EAnimationViewportCameraFollowMode CameraFollowMode;` — The current camera follow mode
- L337 _private member_ `FName CameraFollowBoneName;` — The bone we will follow when in EAnimationViewportCameraFollowMode::Bone
- L340 _private member_ `EAxis::Type BoneAsCameraForward = EAxis::Type::X;` — The forward axis to use when in EAnimationViewportCameraFollowMode::BoneAsCamera
- L343 _private member_ `EAxis::Type BoneAsCameraRight = EAxis::Type::Y;` — The right axis to use when in EAnimationViewportCameraFollowMode::BoneAsCamera
- L346 _private member_ `EAxis::Type BoneAsCameraUp = EAxis::Type::Z;` — The up axis to use when in EAnimationViewportCameraFollowMode::BoneAsCamera
- L349 _private member_ `UE::Math::TVector<double> BoneAsCameraPositionOffset = UE::Math::TVector<double>::ZeroVector;` — The position offset from the bone origin in world space to use when in EAnimationViewportCameraFollowMode::BoneAsCamera
- L352 _private member_ `FRotator BoneAsCameraRotationOffset = FRotator::ZeroRotator;` — The rotation offset from the bone origin in world space to use when in EAnimationViewportCameraFollowMode::BoneAsCamera
- L355 _private member_ `bool bAutoAlignFloor;` — Should we auto align floor to mesh bounds
- L358 _private member_ `bool bRotateCameraToFollowBone;` — Whether to lock the camera's rotation to a specified bone's orientation
- L361 _private member_ `FLinearColor SelectedHSVColor;` — User selected color using color picker
- L364 _private member_ `bool bDrawUVs;` — Flag for displaying the UV data in the viewport
- L367 _private member_ `int32 UVChannelToDraw;` — Which UV channel to draw
- L377 _private member_ `bool bFocusOnDraw;` — Focus on the preview component the next time we draw the viewport
- L378 _private member_ `bool bFocusUsingCustomCamera;`
- L381 _private member_ `mutable bool bDoesAdditiveRefPoseHaveZeroScale;` — Handle additive anim scale validation
- L382 _private member_ `mutable FGuid RefPoseGuid;`
- L385 _private member_ `float CachedScreenSize;` — Screen size cached when we draw
- L388 _private member_ `FDelegateHandle OnPhysicsCreatedDelegateHandle;` — Member use to unregister OnPhysicsCreatedDelegate
- L391 _private member_ `FDelegateHandle OnMeshChangedDelegateHandle;` — Member use to unregister OnMeshChanged for our preview skeletal mesh
- L394 _private member_ `TBitArray<> BonesToDraw;` — Bit field indexed on bone index that stores what bones are visible in the viewport, updated with UpdateBonesToDraw
- L396 _private member_ `FDelegateHandle OnSelectedBonesChangedHandle;`
- L400 _private prototype_ `void SetCameraTargetLocation(const FSphere &BoundSphere, float DeltaSeconds);`
- L403 _private prototype_ `void DrawMeshBones(UDebugSkelMeshComponent * MeshComponent, FPrimitiveDrawInterface* PDI) const;` — Draws Mesh Bones in foreground
- L405 _private prototype_ `void DrawBonesFromTransforms(TArray<FTransform>& Transforms, UDebugSkelMeshComponent * MeshComponent, FPrimitiveDrawInterface* PDI, FLinearColor BoneColour, FLinearColor RootBoneColour) const;` — Draws the given array of transforms as bones
- L407 _private prototype_ `void DrawBonesFromCompactPose(const FCompactHeapPose& Pose, UDebugSkelMeshComponent * MeshComponent, FPrimitiveDrawInterface* PDI, const FLinearColor& DrawColor) const;` — Draws Bones for a compact pose
- L409 _private prototype_ `void DrawMeshBonesUncompressedAnimation(UDebugSkelMeshComponent * MeshComponent, FPrimitiveDrawInterface* PDI) const;` — Draws Bones for uncompressed animation
- L411 _private prototype_ `void DrawMeshBonesNonRetargetedAnimation(UDebugSkelMeshComponent * MeshComponent, FPrimitiveDrawInterface* PDI) const;` — Draw Bones for non retargeted animation.
- L413 _private prototype_ `void DrawMeshBonesAdditiveBasePose(UDebugSkelMeshComponent * MeshComponent, FPrimitiveDrawInterface* PDI) const;` — Draws Bones for Additive Base Pose
- L415 _private prototype_ `void DrawMeshBonesSourceRawAnimation(UDebugSkelMeshComponent * MeshComponent, FPrimitiveDrawInterface* PDI) const;` — Draw Bones for non retargeted animation.
- L417 _private prototype_ `void DrawMeshBonesBakedAnimation(UDebugSkelMeshComponent * MeshComponent, FPrimitiveDrawInterface* PDI) const;` — Draw Bones for non retargeted animation.
- L419 _private prototype_ `void DrawBonesFromSkeleton(UDebugSkelMeshComponent * MeshComponent, const USkeleton* Skeleton, const TArray<int32>& InSelectedBones, FPrimitiveDrawInterface* PDI) const;` — Draw Bones from skeleton reference pose.
- L421 _private prototype_ `void DrawBones( const FVector& ComponentOrigin, const TArray<FBoneIndexType>& RequiredBones, const FReferenceSkeleton& RefSkeleton, const TArray<FTransform>& WorldTransforms, const TArray<int32>& InSelectedBones, const TArray<FLinearColor>& BoneColors, FPrimitiveDrawInterface* PDI, bool bForceDraw, bool bAddHitProxy, bool bUseMultiColors) const;` — Draws Bones for RequiredBones with WorldTransform
- L434 _private prototype_ `void DrawAttributes(UDebugSkelMeshComponent* MeshComponent, FPrimitiveDrawInterface* PDI) const;` — Draws active transform attributes
- L437 _private prototype_ `void DrawNotifies(UDebugSkelMeshComponent* MeshComponent, FPrimitiveDrawInterface* PDI) const;` — Draws visualization from animation notifies into viewport.
- L440 _private prototype_ `void DrawCanvasNotifies(UDebugSkelMeshComponent* MeshComponent, FCanvas& Canvas, FSceneView& View) const;` — Draws visualization from animation notifies into canvas.
- L443 _private prototype_ `void DrawAssetUserData(FPrimitiveDrawInterface* PDI) const;` — Draws visualization from Asset User Data into viewport.
- L446 _private prototype_ `void DrawCanvasAssetUserData(FCanvas& Canvas, FSceneView& View) const;` — Draws visualization from Asset User Data into canvas.
- L449 _private prototype_ `void DrawRootMotionTrajectory(UDebugSkelMeshComponent* MeshComponent, FPrimitiveDrawInterface* PDI) const;` — Draws root motion trajectory
- L452 _private prototype_ `void DrawWatchedPoses(UDebugSkelMeshComponent * MeshComponent, FPrimitiveDrawInterface* PDI);` — Draws bones from watched poses
- L455 _private prototype_ `TSharedPtr<class FAnimationEditorPreviewScene> GetAnimPreviewScenePtr() const;` — Get the typed anim preview scene shared ptr
- L458 _private prototype_ `TSharedRef<class FAnimationEditorPreviewScene> GetAnimPreviewScene() const;` — Get the typed anim preview scene
- L461 _private prototype_ `void HandleInvalidateViews();` — Invalidate this view in response to a preview scene change
- L464 _private prototype_ `void HandleFocusViews();` — Handle the view being focused from the preview scene
- L468 _private prototype_ `FBox ComputeBoundingBoxForSelectedEditorSection() const;` — Computes a bounding box for the selected section of the preview mesh component. If there is no selected section, returns an empty box.
- L471 _private prototype_ `void TransformVertexPositionsToWorld(TArray<FFinalSkinVertex>& LocalVertices) const;` — Converts all local vertex positions to world positions.
- L474 _private prototype_ `void GetAllVertexIndicesUsedInSection(const FRawStaticIndexBuffer16or32Interface& IndexBuffer, const FSkelMeshRenderSection& SkelMeshSection, TArray<int32>& OutIndices) const;` — Gets all vertex indices that the given section references.
- L479 _private prototype_ `void HandlePreviewScenePreTick();` — Used for camera tracking - store data about the scene pre-tick
- L482 _private prototype_ `void HandlePreviewScenePostTick();` — Used for camera tracking - use stored data about the scene post-tick
- L492 _private prototype_ `TArray<IInterface_AssetUserData*> GetEditedObjectsWithAssetUserData() const;` — @return array of AssetUserData interfaces from editable objects on associated asset toolkit.
- L495 _private member_ `float BoneDrawSize=1.0f;` — Size to draw bones in the viewport. Transient setting.
- L498 _private member_ `bool bShowMeshStats;` — Allow mesh stats to be disabled for specific viewport instances
- L501 _private member_ `bool bInitiallyFocused;` — Whether we have initially focused on the preview mesh
- L504 _private member_ `FQuat OrbitRotation;` — When orbiting, the base rotation of the camera, allowing orbiting around different axes to Z
- L507 _private member_ `FEditorCameraController* CachedDefaultCameraController;` — We allow for replacing this in the underlying client so we cache it here
- L510 _private member_ `int32 ViewportIndex;` — Index (0-3) of this viewport
- L513 _private member_ `FVector LastLookAtLocation;` — The last location the camera was told to look at
- L516 _private prototype_ `void OnCameraControllerChanged();` — Delegate Handler to allow changing of camera controller
- L520 _private member_ `bool bResumeAfterTracking;` — True when the preview animation should resume playing upon finishing tracking
- L523 _private member_ `TOptional<FTimecodeDisplayInfo> TimecodeDisplay;` — Timecode/slate information from current animation sequence.

#### enum `FAnimationViewportClient::EDirection`  
`enum class EDirection`  
_L100-105_
- L102 _public enumerator_ `Forward`
- L103 _public enumerator_ `Right`
- L104 _public enumerator_ `Up`

#### enum `FAnimationViewportClient::GridParam`  
`enum GridParam`  
_L369-374_
- L371 _public enumerator_ `MinCellCount = 64`
- L372 _public enumerator_ `MinGridSize = 2`
- L373 _public enumerator_ `MaxGridSize = 50`

#### struct `FAnimationViewportClient::FTimecodeDisplayInfo`  
`struct FTimecodeDisplayInfo`  
_L485-489_
- L487 _public member_ `FQualifiedFrameTime QualifiedTime;`
- L488 _public member_ `FString Slate;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API PERSONA_API`
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBoneSizeSet, float);`
- L27 _prototype_ `DECLARE_DELEGATE_OneParam(FOnBoneSizeSet, float);`
- L28 _delegate_ `DECLARE_DELEGATE_RetVal(float, FOnGetBoneSize)`

### `Source/Editor/Persona/Public/AnimationEditorsAssetFamilyExtension.h` (Public)


#### struct `IAnimationEditorsAssetFamilyInterface`  
`struct IAnimationEditorsAssetFamilyInterface`  
_L13-58_
- L15 _public prototype_ `virtual bool IsAssetTypeInFamily(const TObjectPtr<UClass> InClass) const = 0;`
- L18 _public function_ `template <typename T> bool IsAssetTypeInFamily() const`
- L23 _public prototype_ `virtual TWeakObjectPtr<const UObject> GetAssetOfType(const TObjectPtr<UClass> InClass) const = 0;`
- L26 _public function_ `template <typename T> TObjectPtr<const T> GetAssetOfType() const`
- L36 _public function_ `bool IsAssetTypeInFamilyAndUnassigned(const TObjectPtr<UClass> InClass) const`
- L46 _public function_ `template <typename T> bool IsAssetTypeInFamilyAndUnassigned() const`
- L51 _public prototype_ `virtual bool SetAssetOfType(const TObjectPtr<UClass> InClass, TWeakObjectPtr<const UObject> InObject) = 0;`
- L54 _public function_ `template <typename T> bool SetAssetOfType(TWeakObjectPtr<const UObject> InObject)`

#### class `UAnimationEditorsAssetFamilyExtension`  
`class UAnimationEditorsAssetFamilyExtension : public UObject`  
_L61-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L67 _public function_ `virtual TObjectPtr<UClass> GetAssetClass() const` — The asset class that this extension is describing
- L70 _public function_ `virtual FText GetAssetTypeDisplayName() const` — Returns the display name to show for this asset class
- L73 _public function_ `virtual const FSlateBrush* GetAssetTypeDisplayIcon() const` — Returns the display icon to show for this asset class
- L76 _public function_ `virtual void FindAssetsOfType(TArray<FAssetData>& OutAssets, const IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) const` — Fills OutAssets with the assets of this type that exist
- L79 _public function_ `virtual bool IsAssetCompatible(const FAssetData& InAssetData, const IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface) const` — Returns whether or now the provided asset is compatible
- L82 _public function_ `virtual void FindCounterpartAssets(const UObject* InAsset, IAnimationEditorsAssetFamilyInterface& AssetFamilyInterface)` — Sets the rest of the assets in the family
- L85 _public function_ `virtual void GetPosition(FName& OutBeforeClass, FName& OutAfterClass) const` — Gets the horizontal position of this asset

### `Source/Editor/Persona/Public/AnimationSequenceBrowserMenuContexts.h` (Public)


#### class `UAnimationSequenceBrowserContextMenuContext`  
`class UAnimationSequenceBrowserContextMenuContext : public UObject`  
_L14-35_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L19 _public member_ `TWeakPtr<SAnimationSequenceBrowser> OwningAnimSequenceBrowser;`
- L22 _public member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjects;` — `UPROPERTY()`
- L25 _public function_ `TArray<UObject*> GetSelectedObjects() const` — `UFUNCTION(BlueprintCallable, Category = AnimationEditorExtensions)`

### `Source/Editor/Persona/Public/BlendSpaceAnalysis.h` (Public)


#### class `IBlendSpaceAnalysisFeature`  
`class IBlendSpaceAnalysisFeature : public IModularFeature`  
_L26-45_
- inherits: `IModularFeature`
- desc: Users wishing to add their own analysis functions and structures should inherit from this, implement the virtual functions, and register an instance with IModularFeatures. It may help to look at the implementation of FCoreBlendSpaceAnalysisFeature when doing this.
- L29 _public function_ `static FName GetModuleFeatureName()`
- L32 _public prototype_ `virtual bool CalculateSampleValue(float& Result, const UBlendSpace& BlendSpace, const UAnalysisProperties* AnalysisProperties, const UAnimSequence& Animation, const float RateScale) const = 0;` — This should process the animation according to the analysis properties, or return false if that is not possible.
- L41 _public prototype_ `virtual UAnalysisProperties* MakeAnalysisProperties(UObject* Outer, const FString& FunctionName) const = 0;` — This should return an instance derived from UAnalysisProperties that is suitable for the Function. The caller will pass in a suitable owning object, outer, that the implementation should assign as owner of the newly created object.
- L44 _public prototype_ `virtual TArray<FString> GetAnalysisFunctions() const = 0;` — This should return the names of the functions handled

#### enum `EAnalysisSpace`  
`enum class EAnalysisSpace : uint8`  
_L48-54_
- reflection: `UENUM()`
- L50 _public enumerator_ `World UMETA(ToolTip = "Analysis is done in world space (relative to the root of the character)")`
- L51 _public enumerator_ `Fixed UMETA(ToolTip = "Analysis is done in the space of the specified bone or socket based on the first frame of the animation used")`
- L52 _public enumerator_ `Changing UMETA(ToolTip = "Analysis is done in the space of the specified bone or socket based, but velocities are calculated as if this space is not moving")`
- L53 _public enumerator_ `Moving UMETA(ToolTip = "Analysis is done in the space of the specified bone or socket")`

#### enum `EAnalysisLinearAxis`  
`enum class EAnalysisLinearAxis : uint8`  
_L57-65_
- reflection: `UENUM()`
- L59 _public enumerator_ `PlusX UMETA(DisplayName = "+X", ToolTip = "The axis points in the positive X direction")`
- L60 _public enumerator_ `PlusY UMETA(DisplayName = "+Y", ToolTip = "The axis points in the positive Y direction")`
- L61 _public enumerator_ `PlusZ UMETA(DisplayName = "+Z", ToolTip = "The axis points in the positive Z direction")`
- L62 _public enumerator_ `MinusX UMETA(DisplayName = "-X", ToolTip = "The axis points in the negative X direction")`
- L63 _public enumerator_ `MinusY UMETA(DisplayName = "-Y", ToolTip = "The axis points in the negative Y direction")`
- L64 _public enumerator_ `MinusZ UMETA(DisplayName = "-Z", ToolTip = "The axis points in the negative Z direction")`

#### enum `EEulerCalculationMethod`  
`enum class EEulerCalculationMethod : uint8`  
_L68-72_
- reflection: `UENUM()`
- L70 _public enumerator_ `AimDirection UMETA(ToolTip = "Calculates the yaw by looking at the BoneRightAxis. This can provide better yaw values, especially when aiming (e.g. with a weapon that has minimal rotation around its pointing axis) and covering extreme angles up and down, but only if this rightwards facing axis is reliable. It won't work well if the bone is also rolling around its axis.")`
- L71 _public enumerator_ `PointDirection UMETA(ToolTip = "Calculates the yaw based only on the BoneFacingAxis. This will work when you're most interested in the yaw and pitch from a pointing direction, but can produce undesirable results when pointing almost directly up or down.")`

#### enum `EAnalysisEulerAxis`  
`enum class EAnalysisEulerAxis : uint8`  
_L75-80_
- reflection: `UENUM()`
- L77 _public enumerator_ `Roll`
- L78 _public enumerator_ `Pitch`
- L79 _public enumerator_ `Yaw`

#### class `UCachedAnalysisProperties`  
`class UCachedAnalysisProperties : public UObject`  
_L89-106_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: This will be used to preserve values as far as possible when switching between analysis functions, so it contains all the parameters used by the engine functions. User defined can inherit from this and add their own - then the user-defined MakeCache function should replace any base class cache that is passed in with their own.
- L93 _public prototype_ `void CopyFrom(const UCachedAnalysisProperties& Other);`
- L94 _public member_ `EAnalysisLinearAxis LinearFunctionAxis = EAnalysisLinearAxis::PlusX;`
- L95 _public member_ `EAnalysisEulerAxis EulerFunctionAxis = EAnalysisEulerAxis::Pitch;`
- L96 _public member_ `FBoneSocketTarget BoneSocket1;`
- L97 _public member_ `FBoneSocketTarget BoneSocket2;`
- L98 _public member_ `EAnalysisLinearAxis BoneFacingAxis = EAnalysisLinearAxis::PlusX;`
- L99 _public member_ `EAnalysisLinearAxis BoneRightAxis = EAnalysisLinearAxis::PlusY;`
- L100 _public member_ `EAnalysisSpace Space = EAnalysisSpace::World;`
- L101 _public member_ `FBoneSocketTarget SpaceBoneSocket;`
- L102 _public member_ `EAnalysisLinearAxis CharacterFacingAxis = EAnalysisLinearAxis::PlusY;`
- L103 _public member_ `EAnalysisLinearAxis CharacterUpAxis = EAnalysisLinearAxis::PlusZ;`
- L104 _public member_ `float StartTimeFraction = 0.0f;`
- L105 _public member_ `float EndTimeFraction = 1.0f;`

#### class `ULinearAnalysisPropertiesBase`  
`class ULinearAnalysisPropertiesBase : public UAnalysisProperties`  
_L109-138_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAnalysisProperties`
- L116 _public member_ `FBoneSocketTarget BoneSocket;` — `UPROPERTY(EditAnywhere, DisplayName = "Bone/Socket", Category = AnalysisProperties)` — The bone or socket used for analysis
- L125 _public member_ `EAnalysisSpace Space = EAnalysisSpace::World;` — `UPROPERTY(EditAnywhere, Category = AnalysisProperties)` — The space in which to perform the analysis. Fixed will use the analysis bone/socket at the first frame of the analysis time range. Changing will use the analysis bone/socket at the relevant frame during the analysis, but calculate velocities assuming that frame isn't moving. Moving will do the same but velocities as well as positions/rotations will be relative to this moving frame.
- L129 _public member_ `FBoneSocketTarget SpaceBoneSocket;` — `UPROPERTY(EditAnywhere, DisplayName = "Analysis Space Bone/Socket", Category = AnalysisProperties, meta = (EditCondition = "Space != EAnalysisSpace::World"))` — Bone or socket that defines the analysis space (when it isn't World)
- L133 _public member_ `float StartTimeFraction = 0.0f;` — `UPROPERTY(EditAnywhere, DisplayName = "Start time fraction", Category = AnalysisProperties, meta = (ClampMin = "0", ClampMax = "1"))` — Fraction through each animation at which analysis starts
- L137 _public member_ `float EndTimeFraction = 1.0f;` — `UPROPERTY(EditAnywhere, DisplayName = "End time fraction", Category = AnalysisProperties, meta = (ClampMin = "0", ClampMax = "1"))` — Fraction through each animation at which analysis ends

#### class `ULinearAnalysisProperties`  
`class ULinearAnalysisProperties : public ULinearAnalysisPropertiesBase`  
_L141-151_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ULinearAnalysisPropertiesBase`
- L145 _public prototype_ `void InitializeFromCache(TObjectPtr<UCachedAnalysisProperties> Cache) override;`
- L146 _public prototype_ `void MakeCache(TObjectPtr<UCachedAnalysisProperties>& Cache, UBlendSpace* BlendSpace) override;`
- L150 _public member_ `EAnalysisLinearAxis FunctionAxis = EAnalysisLinearAxis::PlusX;` — `UPROPERTY(EditAnywhere, DisplayName = "Axis", Category = AnalysisProperties)` — Axis for the analysis function

#### class `UEulerAnalysisProperties`  
`class UEulerAnalysisProperties : public UAnalysisProperties`  
_L155-210_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnalysisProperties`
- L159 _public prototype_ `void InitializeFromCache(TObjectPtr<UCachedAnalysisProperties> Cache) override;`
- L160 _public prototype_ `void MakeCache(TObjectPtr<UCachedAnalysisProperties>& Cache, UBlendSpace* BlendSpace) override;`
- L164 _public member_ `EAnalysisEulerAxis FunctionAxis = EAnalysisEulerAxis::Pitch;` — `UPROPERTY(EditAnywhere, DisplayName = "Axis", Category = AnalysisProperties)` — Axis for the analysis function
- L168 _public member_ `FBoneSocketTarget BoneSocket;` — `UPROPERTY(EditAnywhere, DisplayName = "Bone/Socket", Category = AnalysisProperties)` — The bone or socket used for analysis
- L172 _public member_ `EAnalysisLinearAxis BoneFacingAxis = EAnalysisLinearAxis::PlusX;` — `UPROPERTY(EditAnywhere, Category = AnalysisProperties)` — Used for some analysis functions - specifies the bone/socket axis that points in the facing/forwards direction
- L176 _public member_ `EAnalysisLinearAxis BoneRightAxis = EAnalysisLinearAxis::PlusY;` — `UPROPERTY(EditAnywhere, Category = AnalysisProperties)` — Used for some analysis functions - specifies the bone/socket axis that points to the "right"
- L180 _public member_ `EEulerCalculationMethod EulerCalculationMethod = EEulerCalculationMethod::AimDirection;` — `UPROPERTY(EditAnywhere, Category = AnalysisProperties)` — Used for some analysis functions - specifies how yaw should be calculated from the bone axes
- L189 _public member_ `EAnalysisSpace Space = EAnalysisSpace::World;` — `UPROPERTY(EditAnywhere, Category = AnalysisProperties)` — The space in which to perform the analysis. Fixed will use the analysis bone/socket at the first frame of the analysis time range. Changing will use the analysis bone/socket at the relevant frame during the analysis, but calculate velocities assuming that frame isn't moving. Moving will do the same but velocities as well as positions/rotations will be relative to this moving frame.
- L193 _public member_ `FBoneSocketTarget SpaceBoneSocket;` — `UPROPERTY(EditAnywhere, DisplayName = "Analysis Space Bone/Socket", Category = AnalysisProperties, meta = (EditCondition = "Space != EAnalysisSpace::World"))` — Bone or socket that defines the analysis space (when it isn't World)
- L197 _public member_ `EAnalysisLinearAxis CharacterFacingAxis = EAnalysisLinearAxis::PlusY;` — `UPROPERTY(EditAnywhere, Category = AnalysisProperties)` — World or bone/socket axis that specifies the character's facing direction
- L201 _public member_ `EAnalysisLinearAxis CharacterUpAxis = EAnalysisLinearAxis::PlusZ;` — `UPROPERTY(EditAnywhere, Category = AnalysisProperties)` — World or bone/socket axis that specifies the character's up direction
- L205 _public member_ `float StartTimeFraction = 0.0f;` — `UPROPERTY(EditAnywhere, DisplayName = "Start time fraction", Category = AnalysisProperties, meta = (ClampMin = "0", ClampMax = "1"))` — Fraction through each animation at which analysis starts
- L209 _public member_ `float EndTimeFraction = 1.0f;` — `UPROPERTY(EditAnywhere, DisplayName = "End time fraction", Category = AnalysisProperties, meta = (ClampMin = "0", ClampMax = "1"))`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API PERSONA_API`
- L15 _macro_ `#define LOCTEXT_NAMESPACE "BlendSpaceAnalysis"`
- L216 _namespace_ `namespace BlendSpaceAnalysis`
- L221 _prototype_ `bool GetBoneInfo(const UAnimSequence& Animation, const FBoneSocketTarget& BoneSocket, FTransform& BoneOffset, FName& BoneName);` (scope `BlendSpaceAnalysis`) — Retrieves the bone index and transform offset given the BoneSocketTarget. Returns true if found
- L227 _prototype_ `FTransform GetBoneTransform(const UAnimSequence& Animation, int32 Key, const FName& BoneName);` (scope `BlendSpaceAnalysis`)
- L231 _function_ `template<typename T> void CalculateFrameTM( bool& bNeedToUpdateFrameTM, FTransform& FrameTM, const int32 SampleKey, const T& AnalysisProperties, const UAnimSequence& Animation)` (scope `BlendSpaceAnalysis`)
- L256 _prototype_ `FVector GetAxisFromTM(const FTransform& TM, EAnalysisLinearAxis Axis);` (scope `BlendSpaceAnalysis`)
- L260 _function_ `template<typename T> void GetFrameDirs( FVector& FrameFacingDir, FVector& FrameUpDir, FVector& FrameRightDir, const FTransform& FrameTM, const T& AnalysisProperties)` (scope `BlendSpaceAnalysis`)
- L274 _function_ `template<typename FunctionType> static bool CalculateComponentSampleValue( double& Result, const FunctionType& Fn, const UBlendSpace& BlendSpace, const ULinearAnalysisProperties* AnalysisProperties, const UAnimSequence& Animation, const float RateScale)` (scope `BlendSpaceAnalysis`) — Helper to extract the component from the FVector functions
- L297 _function_ `template<typename FunctionType> static bool CalculateComponentSampleValue( double& Result, const FunctionType& Fn, const UBlendSpace& BlendSpace, const UEulerAnalysisProperties* AnalysisProperties, const UAnimSequence& Animation, const float RateScale)` (scope `BlendSpaceAnalysis`) — Helper to extract the component from the FVector functions
- L320 _function_ `template<typename FunctionType> static bool CalculateComponentSampleValue( float& Result, const FunctionType& Fn, const UBlendSpace& BlendSpace, const ULinearAnalysisProperties* AnalysisProperties, const UAnimSequence& Animation, const float RateScale)` (scope `BlendSpaceAnalysis`) — Helper to extract the component from the FVector functions as a float (pass through to double version)
- L339 _function_ `template<typename FunctionType> static bool CalculateComponentSampleValue( float& Result, const FunctionType& Fn, const UBlendSpace& BlendSpace, const UEulerAnalysisProperties* AnalysisProperties, const UAnimSequence& Animation, const float RateScale)` (scope `BlendSpaceAnalysis`) — Helper to extract the component from the FVector functions as a float (pass through to double version)
- L354 _prototype_ `extern bool CalculatePosition( FVector& Result, const UBlendSpace& BlendSpace, const ULinearAnalysisProperties* AnalysisProperties, const UAnimSequence& Animation, const float RateScale);` (scope `BlendSpaceAnalysis`)
- L362 _prototype_ `extern bool CalculateDeltaPosition( FVector& Result, const UBlendSpace& BlendSpace, const ULinearAnalysisProperties* AnalysisProperties, const UAnimSequence& Animation, const float RateScale);` (scope `BlendSpaceAnalysis`)
- L370 _prototype_ `extern bool CalculateVelocity( FVector& Result, const UBlendSpace& BlendSpace, const ULinearAnalysisPropertiesBase* AnalysisProperties, const UAnimSequence& Animation, const float RateScale);` (scope `BlendSpaceAnalysis`)
- L378 _prototype_ `extern void CalculateBoneOrientation( FVector& RollPitchYaw, const UAnimSequence& Animation, const int32 Key, const FName BoneName, const FTransform& BoneOffset, const UEulerAnalysisProperties* AnalysisProperties, const FVector& FrameFacingDir, const FVector& FrameRightDir, const FVector& FrameUpDir);` (scope `BlendSpaceAnalysis`)
- L392 _prototype_ `extern bool CalculateOrientation( FVector& Result, const UBlendSpace& BlendSpace, const UEulerAnalysisProperties* AnalysisProperties, const UAnimSequence& Animation, const float RateScale);` (scope `BlendSpaceAnalysis`) — Note that if a looping animation has 56 keys, then its first key is 0 and last is 55, but these will be identical poses. Thus it has one fewer intervals/unique keys
- L402 _prototype_ `extern bool CalculateDeltaOrientation( FVector& Result, const UBlendSpace& BlendSpace, const UEulerAnalysisProperties* AnalysisProperties, const UAnimSequence& Animation, const float RateScale);` (scope `BlendSpaceAnalysis`) — Note that if a looping animation has 56 keys, then its first key is 0 and last is 55, but these will be identical poses. Thus it has one fewer intervals/unique keys
- L410 _prototype_ `extern bool CalculateAngularVelocity( FVector& Result, const UBlendSpace& BlendSpace, const ULinearAnalysisProperties* AnalysisProperties, const UAnimSequence& Animation, const float RateScale);` (scope `BlendSpaceAnalysis`)
- L418 _prototype_ `extern bool CalculateOrientationRate( FVector& Result, const UBlendSpace& BlendSpace, const UEulerAnalysisProperties* AnalysisProperties, const UAnimSequence& Animation, const float RateScale);` (scope `BlendSpaceAnalysis`)

### `Source/Editor/Persona/Public/BoneDragDropOp.h` (Public)


#### class `FBoneDragDropOp`  
`class FBoneDragDropOp : public FDragDropOperation`  
_L17-76_
- inherits: `FDragDropOperation`
- desc: FBoneDragDropOp
- L20 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FBoneDragDropOp, FDragDropOperation) TWeakPtr<class IEditableSkeleton> EditableSkeleton;`
- L23 _public member_ `FName BoneName;`
- L26 _public function_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override` — The widget decorator to use
- L49 _public function_ `FText GetHoverText() const`
- L54 _public function_ `const FSlateBrush* GetIcon( ) const`
- L59 _public function_ `void SetIcon(const FSlateBrush* InIcon)`
- L64 _public function_ `static TSharedRef<FBoneDragDropOp> New(TSharedRef<class IEditableSkeleton> EditableSkeleton, const FName& InBoneName)`
- L75 _private member_ `const FSlateBrush* CurrentIconBrush;`

### `Source/Editor/Persona/Public/BoneSelectionWidget.h` (Public)


#### class `SBoneTreeMenu`  
`class SBoneTreeMenu : public SCompoundWidget`  
_L24-109_
- inherits: `SCompoundWidget`
- L36 _public function_ `SLATE_BEGIN_ARGS(SBoneTreeMenu) : _bShowVirtualBones(true) , _bShowSocket(false) , _bShowNone(false) , _OnGetReferenceSkeleton() , _OnBoneSelectionChanged() , _OnGetSocketList()`
- L45 _public prototype_ `SLATE_ARGUMENT(FText, Title) SLATE_ARGUMENT(bool, bShowVirtualBones) SLATE_ARGUMENT(bool, bShowSocket) SLATE_ARGUMENT(bool, bShowNone) SLATE_ARGUMENT(FName, SelectedBone) SLATE_EVENT(FGetReferenceSkeleton, OnGetReferenceSkeleton) SLATE_EVENT(FOnBoneSelectionChanged, OnBoneSelectionChanged) SLATE_EVENT(FGetSocketList, OnGetSocketList) SLATE_END_ARGS();`
- L61 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget @param	InArgs	The declaration data for this widget
- L64 _public prototype_ `TSharedPtr<SWidget> GetFilterTextWidget();` — Get the filter text widget, e.g. for focus
- L68 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget interface
- L71 _private prototype_ `void RebuildBoneList(const FName& SelectedBone);` — Using the current filter, repopulate the tree view
- L74 _private prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(TSharedPtr<FBoneNameInfo> InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Make a single tree row widget
- L77 _private prototype_ `void GetChildrenForInfo(TSharedPtr<FBoneNameInfo> InInfo, TArray< TSharedPtr<FBoneNameInfo> >& OutChildren);` — Get the children for the provided bone info
- L80 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);` — Called when the user changes the search filter
- L83 _private prototype_ `void OnSelectionChanged(TSharedPtr<SBoneTreeMenu::FBoneNameInfo> BoneInfo, ESelectInfo::Type SelectInfo);` — Handle the tree view selection changing
- L86 _private prototype_ `void SelectBone(TSharedPtr<SBoneTreeMenu::FBoneNameInfo> BoneInfo);` — Select a specific bone, helper for UI handler functions
- L89 _private member_ `TArray<TSharedPtr<FBoneNameInfo>> SkeletonTreeInfo;` — Tree info entries for bone picker
- L91 _private member_ `TArray<TSharedPtr<FBoneNameInfo>> SkeletonTreeInfoFlat;` — Mirror of SkeletonTreeInfo but flattened for searching
- L94 _private member_ `FText FilterText;` — Text to filter bone tree with
- L97 _private member_ `TSharedPtr<STreeView<TSharedPtr<FBoneNameInfo>>> TreeView;` — Tree view used in the button menu
- L100 _private member_ `TSharedPtr<SSearchBox> FilterTextWidget;` — Filter text widget
- L102 _private member_ `FOnBoneSelectionChanged OnSelectionChangedDelegate;`
- L103 _private member_ `FGetReferenceSkeleton OnGetReferenceSkeletonDelegate;`
- L104 _private member_ `FGetSocketList OnGetSocketListDelegate;`
- L106 _private member_ `bool bShowVirtualBones;`
- L107 _private member_ `bool bShowSocket;`
- L108 _private member_ `bool bShowNone;`

#### struct `SBoneTreeMenu::FBoneNameInfo`  
`struct FBoneNameInfo`  
_L28-34_
- desc: Storage object for bone hierarchy
- L30 _public function_ `FBoneNameInfo(FName Name) : BoneName(Name)`
- L32 _public member_ `FName BoneName;`
- L33 _public member_ `TArray<TSharedPtr<FBoneNameInfo>> Children;`

#### class `SBoneSelectionWidget`  
`class SBoneSelectionWidget : public SCompoundWidget`  
_L111-180_
- inherits: `SCompoundWidget`
- L115 _public function_ `SLATE_BEGIN_ARGS( SBoneSelectionWidget ) : _bShowSocket(false) , _bShowVirtualBones(true) , _bShowNone(false) , _OnBoneSelectionChanged() , _OnGetSelectedBone() , _OnGetReferenceSkeleton() , _OnGetSocketList()`
- L125 _public prototype_ `SLATE_ARGUMENT(bool, bShowSocket) SLATE_ARGUMENT(bool, bShowVirtualBones) SLATE_ARGUMENT(bool, bShowNone) SLATE_EVENT(FOnBoneSelectionChanged, OnBoneSelectionChanged);`
- L137 _public prototype_ `SLATE_EVENT(FGetSelectedBone, OnGetSelectedBone);` — get selected bone name
- L140 _public prototype_ `SLATE_EVENT(FGetReferenceSkeleton, OnGetReferenceSkeleton) SLATE_EVENT(FGetSocketList, OnGetSocketList) SLATE_END_ARGS();` — Get Reference skeleton
- L152 _public prototype_ `void Construct( const FArguments& InArgs );` — Construct this widget @param	InArgs	The declaration data for this widget
- L157 _private prototype_ `TSharedRef<SWidget> CreateSkeletonWidgetMenu();` — Creates the combo button menu when clicked
- L159 _private prototype_ `void OnSelectionChanged(FName BoneName);` — Called when the user selects a bone name
- L162 _private prototype_ `FText GetCurrentBoneName() const;` — Gets the current bone name, used to get the right name for the combo button
- L164 _private prototype_ `FText GetFinalToolTip() const;`
- L167 _private member_ `TSharedPtr<SComboButton> BonePickerButton;` — Base combo button
- L170 _private member_ `FOnBoneSelectionChanged OnBoneSelectionChanged;` — delegates
- L171 _private member_ `FGetSelectedBone OnGetSelectedBone;`
- L172 _private member_ `FGetReferenceSkeleton OnGetReferenceSkeleton;`
- L173 _private member_ `FGetSocketList OnGetSocketList;`
- L174 _private member_ `bool bShowSocket;`
- L175 _private member_ `bool bShowVirtualBones;`
- L176 _private member_ `bool bShowNone;`
- L179 _private member_ `FText SuppliedToolTip;` — Cache supplied tooltip

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API PERSONA_API`
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBoneSelectionChanged, FName);`
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FOnBoneSelectionChanged, FName);`
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FName, FGetSelectedBone, bool& );`
- L20 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FName, FGetSelectedBone, bool& );`
- L21 _delegate_ `DECLARE_DELEGATE_RetVal(const struct FReferenceSkeleton&, FGetReferenceSkeleton);`
- L21 _prototype_ `DECLARE_DELEGATE_RetVal(const struct FReferenceSkeleton&, FGetReferenceSkeleton);`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal(const TArray<class USkeletalMeshSocket*>&, FGetSocketList);`
- L22 _prototype_ `DECLARE_DELEGATE_RetVal(const TArray<class USkeletalMeshSocket*>&, FGetSocketList);`

### `Source/Editor/Persona/Public/IAnimSequenceCurveEditor.h` (Public)


#### class `IAnimSequenceCurveEditor`  
`class IAnimSequenceCurveEditor : public SCompoundWidget`  
_L12-26_
- inherits: `SCompoundWidget`
- desc: Interface to the curve editor tab in the anim sequence editor
- L16 _public prototype_ `virtual void ResetCurves() = 0;` — Reset the curves that are edited by this widget
- L19 _public prototype_ `virtual void AddCurve(const FText& InCurveDisplayName, const FLinearColor& InCurveColor, const FName& InName, ERawCurveTrackTypes InType, int32 InCurveIndex, FSimpleDelegate InOnCurveModified) = 0;` — Add a curve for editing
- L22 _public prototype_ `virtual void RemoveCurve(const FName& InName, ERawCurveTrackTypes InType, int32 InCurveIndex) = 0;` — Remove a curve for editing
- L25 _public prototype_ `virtual void ZoomToFit() = 0;` — Zoom to fit all the curves

### `Source/Editor/Persona/Public/IAnimationSequenceBrowser.h` (Public)


#### class `IAnimationSequenceBrowser`  
`class IAnimationSequenceBrowser : public SCompoundWidget`  
_L10-21_
- inherits: `SCompoundWidget`
- L14 _public prototype_ `virtual void SelectAsset(UAnimationAsset* InAsset) = 0;` — Select the specified asset
- L17 _public prototype_ `virtual void AddToHistory(UAnimationAsset* AnimAsset) = 0;` — Add to navigation history
- L20 _public prototype_ `virtual void FilterBySkeletonNotify(const FName& InNotifyName) = 0;` — Add filter by skeleton notify name

### `Source/Editor/Persona/Public/IAssetFamily.h` (Public)


#### class `IAssetFamily`  
`class IAssetFamily`  
_L12-63_
- desc: Represents a group of related assets, e.g. a skeleton, its animations and skeletal meshes
- L16 _public prototype_ `virtual ~IAssetFamily() = default;` — Virtual destructor
- L19 _public prototype_ `virtual void GetAssetTypes(TArray<UClass*>& OutAssetTypes) const = 0;` — Get all the asset classes this family supports (doesnt need to include derived classes)
- L22 _public prototype_ `virtual FAssetData FindAssetOfType(UClass* AssetType) const = 0;` — Find the most relevant asset of a specified type
- L26 _public function_ `template<typename AssetType> FAssetData GetAsset()` — Find the most relevant asset of a specified type
- L32 _public prototype_ `virtual void FindAssetsOfType(UClass* AssetType, TArray<FAssetData>& OutAssets) const = 0;` — Find all assets of a specified type
- L36 _public function_ `template<typename AssetType> void GetAssets(TArray<FAssetData>& OutAssets)` — Find all assets of a specified type
- L42 _public prototype_ `virtual FText GetAssetTypeDisplayName(UClass* InAssetClass) const = 0;` — Gets the name of an asset that will be displayed to a user
- L45 _public prototype_ `virtual const FSlateBrush* GetAssetTypeDisplayIcon(UClass* InAssetClass) const = 0;` — Gets the slate brush that represents this asset family
- L48 _public prototype_ `virtual FSlateColor GetAssetTypeDisplayTint(UClass* InAssetClass) const = 0;` — Gets the color to tint the asset display icon
- L51 _public prototype_ `virtual bool IsAssetCompatible(const FAssetData& InAssetData) const = 0;` — Check whether an asset is compatible with this family
- L54 _public prototype_ `virtual UClass* GetAssetFamilyClass(UClass* InClass) const = 0;` — @return the outermost superclass of the passed-in class for this asset family
- L57 _public prototype_ `DECLARE_EVENT_OneParam(IAssetFamily, FOnAssetOpened, UObject*) virtual FOnAssetOpened& GetOnAssetOpened() = 0;` — Event fired when an asset is opened
- L61 _public prototype_ `DECLARE_EVENT(IAssetFamily, FOnAssetFamilyChanged) virtual FOnAssetFamilyChanged& GetOnAssetFamilyChanged() = 0;` — Event fired when an asset family changes (e.g. relationships are altered)

#### Free symbols / members of external scopes

- L57 _delegate_ `DECLARE_EVENT_OneParam(IAssetFamily, FOnAssetOpened, UObject*) virtual FOnAssetOpened& GetOnAssetOpened() = 0;` — Event fired when an asset is opened
- L61 _delegate_ `DECLARE_EVENT(IAssetFamily, FOnAssetFamilyChanged) virtual FOnAssetFamilyChanged& GetOnAssetFamilyChanged() = 0;` — Event fired when an asset family changes (e.g. relationships are altered)

### `Source/Editor/Persona/Public/IBlendProfilePickerExtender.h` (Public)


#### class `IBlendProfilePickerExtender`  
`class IBlendProfilePickerExtender`  
_L14-54_
- L44 _public prototype_ `virtual FName GetId() const = 0;` — Returns an identifier to match extender instances
- L47 _public prototype_ `virtual FText GetDisplayName() const = 0;` — Text to display in the details panel when choosing blend profiles of this type
- L50 _public prototype_ `virtual TSharedRef<SWidget> ConstructPickerWidget(const FPickerWidgetArgs& InWidgetArgs) const = 0;` — Construct the picker widget for choosing blend profiles of this type
- L53 _public prototype_ `virtual bool OwnsBlendProfileProvider(const TObjectPtr<const UObject> InProviderObject) const = 0;` — Return true if the provided object is the matching type for this extender

#### struct `IBlendProfilePickerExtender::FPickerWidgetArgs`  
`struct FPickerWidgetArgs`  
_L17-41_
- L19 _public function_ `FPickerWidgetArgs() : Outer(nullptr) , SupportedBlendProfileModes(EBlendProfilePickerMode::AllModes)`
- L25 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnBlendProfileProviderChanged, TObjectPtr<UObject> , IBlendProfileProviderInterface*);`
- L28 _public member_ `FOnBlendProfileProviderChanged OnProviderChanged;` — Should be fired when the blend profile provider object has changed
- L31 _public member_ `TObjectPtr<UObject> InitialSelection;` — The initially selected provider object
- L34 _public member_ `TObjectPtr<UObject> Outer;` — The outer to use for constructing new provider objects
- L37 _public member_ `EBlendProfilePickerMode SupportedBlendProfileModes;` — Restrict which types of blend profiles are displayed in the picker
- L40 _public member_ `TObjectPtr<USkeleton> Skeleton;` — Optional skeleton to restrict shown blend profiles relating to a particular skeleton

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnBlendProfileProviderChanged, TObjectPtr<UObject> , IBlendProfileProviderInterface*);`

### `Source/Editor/Persona/Public/IHasPersonaToolkit.h` (Public)


#### class `IHasPersonaToolkit`  
`class IHasPersonaToolkit`  
_L8-13_
- desc: Interface implemented by objects that hold a persona toolkit
- L12 _public prototype_ `virtual TSharedRef<class IPersonaToolkit> GetPersonaToolkit() const = 0;` — Get the toolkit held by this object

### `Source/Editor/Persona/Public/IMorphTargetViewer.h` (Public)


#### class `IMorphTargetViewer`  
`class IMorphTargetViewer`  
_L9-17_
- desc: Interface to the morph target viewer in the skeletal mesh editor
- L13 _public prototype_ `virtual TArray<FName> GetSelectedMorphTargetNames() const = 0;`
- L14 _public prototype_ `virtual TSharedRef<SWidget> AsWidget() = 0;`
- L16 _public prototype_ `virtual ~IMorphTargetViewer() = default;`

### `Source/Editor/Persona/Public/IPersonaEditMode.h` (Public)


#### class `IPersonaEditMode`  
`class IPersonaEditMode : public FAnimationEditMode`  
_L9-19_
- inherits: `FAnimationEditMode`
- L14 _public prototype_ `IPersonaEditMode();`
- L16 _public prototype_ `virtual void Enter() override;`
- L17 _public prototype_ `virtual void Exit() override;`
- L18 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PERSONA_API`

### `Source/Editor/Persona/Public/IPersonaEditorModeManager.h` (Public)


#### class `UPersonaManagerContext`  
`class UPersonaManagerContext : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPersonaManagerContext`  
`class IPersonaManagerContext`  
_L19-35_
- desc: Persona-specific extensions to the asset editor mode manager
- L28 _public prototype_ `virtual bool GetCameraTarget(FSphere& OutTarget) const = 0;` — Get a camera target for when the user focuses the viewport @param OutTarget		The target object bounds @return true if the location is valid
- L34 _public prototype_ `virtual void GetOnScreenDebugInfo(TArray<FText>& OutDebugText) const = 0;` — Get debug info for any editor modes that are active @param	OutDebugText	The text to draw

#### class `UPersonaEditorModeManagerContext`  
`class UPersonaEditorModeManagerContext : public UObject, public IPersonaManagerContext`  
_L40-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IPersonaManagerContext`
- L45 _public prototype_ `IPersonaEditorModeManager* GetPersonaEditorModeManager() const;` — Only for use by FAnimationViewportClient::GetPersonaModeManager for compatibility
- L46 _public prototype_ `virtual bool GetCameraTarget(FSphere& OutTarget) const override;`
- L47 _public prototype_ `virtual void GetOnScreenDebugInfo(TArray<FText>& OutDebugText) const override;`
- L48 _public prototype_ `virtual void SetFocusInViewport();`
- L50 _private member_ `IPersonaEditorModeManager* ModeManager = nullptr;`
- L51 _private function_ `static UPersonaEditorModeManagerContext* CreateFor(IPersonaEditorModeManager* InModeManager)`

#### class `IPersonaEditorModeManager`  
`class IPersonaEditorModeManager : public FAssetEditorModeManager, public IPersonaManagerContext`  
_L60-71_
- inherits: `FAssetEditorModeManager,IPersonaManagerContext`
- L63 _public prototype_ `IPersonaEditorModeManager();`
- L65 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L66 _public prototype_ `virtual UTypedElementSelectionSet* GetEditorSelectionSet() const override;`
- L69 _private member_ `TObjectPtr<UPersonaEditorModeManagerContext> PersonaModeManagerContext{UPersonaEditorModeManagerContext::CreateFor(this)};`
- L70 _private member_ `TObjectPtr<UTypedElementSelectionSet> SelectionSet;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PERSONA_API`

### `Source/Editor/Persona/Public/IPersonaPreviewScene.h` (Public)


#### enum `EPreviewSceneDefaultAnimationMode`  
`enum class EPreviewSceneDefaultAnimationMode : int32`  
_L59-69_
- desc: Modes that the preview scene defaults to (usually depending on asset editor context)
- L61 _public enumerator_ `ReferencePose`
- L63 _public enumerator_ `Animation`
- L65 _public enumerator_ `AnimationBlueprint`
- L68 _public enumerator_ `Custom` — each mesh component defines their custom pose

#### class `IPersonaPreviewScene`  
`class IPersonaPreviewScene : public FAdvancedPreviewScene`  
_L71-343_
- inherits: `FAdvancedPreviewScene`
- L75 _public function_ `IPersonaPreviewScene(ConstructionValues CVS) : FAdvancedPreviewScene(CVS)` — Constructor only here to pass ConstructionValues to base constructor
- L80 _public prototype_ `virtual void UnregisterForUndo() = 0;` — Unregister this scene from the Undo chain. Necessary for certain editor windows.
- L83 _public prototype_ `virtual TSharedRef<class IPersonaToolkit> GetPersonaToolkit() const = 0;` — Get the persona toolkit we are associated with
- L86 _public prototype_ `virtual void InvalidateViews() = 0;` — Flag that we want our views to be updated
- L89 _public prototype_ `virtual void FocusViews() = 0;` — Request our views to focus on the current item
- L92 _public prototype_ `virtual UDebugSkelMeshComponent* GetPreviewMeshComponent() const = 0;` — Get the skeletal mesh component we are using for preview, if any.
- L95 _public prototype_ `virtual TArray<UDebugSkelMeshComponent*> GetAllPreviewMeshComponents() const = 0;` — Get array of all skeletal mesh components in the preview scene.
- L98 _public prototype_ `virtual void ForEachPreviewMesh(TFunction<void (UDebugSkelMeshComponent*)> PerMeshFunction) = 0;` — Run a lambda function on each preview mesh in the scene
- L101 _public prototype_ `virtual void SetPreviewMeshComponent(UDebugSkelMeshComponent* InSkeletalMeshComponent) = 0;` — Set the skeletal mesh component we are going to preview.
- L104 _public prototype_ `virtual void SetAdditionalMeshes(class UDataAsset* InAdditionalMeshes) = 0;` — Set the additional meshes used by this preview scene (sets the additional meshes on the skeleton)
- L107 _public prototype_ `virtual void SetAdditionalMeshesSelectable(bool bSelectable) = 0;` — Set whether additional meshes are selectable
- L110 _public prototype_ `virtual void RefreshAdditionalMeshes(bool bAllowOverrideBaseMesh) = 0;` — Refreshes the additional meshes displayed in this preview scene
- L113 _public prototype_ `virtual void SetPreviewAnimationAsset(UAnimationAsset* AnimAsset, bool bEnablePreview = true) = 0;` — Set the animation asset to preview
- L116 _public prototype_ `virtual UAnimationAsset* GetPreviewAnimationAsset() const = 0;` — Get the animation asset we are previewing
- L119 _public prototype_ `virtual void SetPreviewMesh(USkeletalMesh* NewPreviewMesh, bool bAllowOverrideBaseMesh = true) = 0;` — Set the preview mesh for this scene (does not set the preview mesh on the skeleton/asset)
- L122 _public prototype_ `virtual USkeletalMesh* GetPreviewMesh() const = 0;` — Get the preview mesh for this scene (does go via skeleton/asset)
- L125 _public prototype_ `virtual void SetPreviewAnimationBlueprint(UAnimBlueprint* InAnimBlueprint, UAnimBlueprint* InOverlayOrSubAnimBlueprint) = 0;` — Set the preview animation blueprint and an optional overlay (for sub-layers)
- L128 _public prototype_ `virtual void ShowReferencePose(bool bShowRefPose, bool bResetBoneTransforms = false) = 0;` — Show the reference pose of the displayed skeletal mesh. Otherwise display the default. Optionally reset bone transforms, if any.
- L131 _public prototype_ `virtual bool IsShowReferencePoseEnabled() const = 0;` — Are we currently displaying the ref pose
- L134 _public prototype_ `virtual bool AttachObjectToPreviewComponent(UObject* Object, FName AttachTo) = 0;` — Attaches an object to the preview component using the supplied attach name, returning whether it was successfully attached or not
- L137 _public prototype_ `virtual void RemoveAttachedObjectFromPreviewComponent(UObject* Object, FName AttachedTo) = 0;` — Removes a currently attached object from the preview component
- L141 _public function_ `virtual void SetSelectedBone(const FName& BoneName) final` — `UE_DEPRECATED(4.26, "Please call/implement SetSelectedBone with ESelectInfo")` — Sets the selected bone on the preview component
- L144 _public prototype_ `virtual void SetSelectedBone(const FName& BoneName, ESelectInfo::Type InSelectInfo) = 0;` — Sets the selected bone on the preview component
- L147 _public prototype_ `virtual void SetSelectedBones(const TArray<FName>& InBoneNames, ESelectInfo::Type InSelectInfo) = 0;` — Sets the selected bones on the preview component
- L150 _public prototype_ `virtual void ClearSelectedBone() = 0;` — Clears the selected bone on the preview component
- L153 _public prototype_ `virtual void SetSelectedSocket(const FSelectedSocketInfo& SocketInfo) = 0;` — Sets the selected socket on the preview component
- L156 _public prototype_ `virtual void ClearSelectedSocket() = 0;` — Clears the selected socket on the preview component
- L159 _public prototype_ `virtual void SetSelectedActor(AActor* InActor) = 0;` — Sets the selected actor
- L162 _public prototype_ `virtual void ClearSelectedActor() = 0;` — Clears the selected actor
- L165 _public prototype_ `virtual void DeselectAll() = 0;` — Clears all selection on the preview component
- L168 _public prototype_ `virtual void RegisterOnAnimChanged(const FOnAnimChanged& Delegate) = 0;` — Registers a delegate to be called after the preview animation has been changed
- L171 _public prototype_ `virtual void UnregisterOnAnimChanged(FDelegateUserObject Thing) = 0;` — Unregisters a delegate to be called after the preview animation has been changed
- L174 _public prototype_ `virtual void RegisterOnPreviewMeshChanged(const FOnPreviewMeshChanged& Delegate) = 0;` — Registers a delegate to be called when the preview mesh is changed
- L177 _public prototype_ `virtual void UnregisterOnPreviewMeshChanged(FDelegateUserObject Thing) = 0;` — Unregisters a delegate to be called when the preview mesh is changed
- L180 _public prototype_ `virtual void RegisterOnLODChanged(const FSimpleDelegate& Delegate) = 0;` — Registers a delegate to be called when the preview mesh's LOD has changed
- L183 _public prototype_ `virtual void UnregisterOnLODChanged(FDelegateUserObject Thing) = 0;` — Unregisters a delegate to be called when the preview mesh's LOD has changed
- L186 _public prototype_ `virtual void BroadcastOnLODChanged() = 0;` — Broadcasts that we want to force an update, after preview mesh's LOD has changed
- L189 _public prototype_ `virtual void RegisterOnMorphTargetsChanged(const FSimpleDelegate& Delegate) = 0;` — Registers a delegate to be called when the preview mesh's morph targets has changed
- L192 _public prototype_ `virtual void UnregisterOnMorphTargetsChanged(FDelegateUserObject Thing) = 0;` — Unregisters a delegate to be called when the preview mesh's morph targets has changed
- L195 _public prototype_ `virtual void BroadcastOnMorphTargetsChanged() = 0;` — Broadcasts that the preview mesh morph targets has changed
- L198 _public prototype_ `virtual void RegisterOnInvalidateViews(const FSimpleDelegate& Delegate) = 0;` — Registers a delegate to be called when the view is invalidated
- L201 _public prototype_ `virtual void UnregisterOnInvalidateViews(FDelegateUserObject Thing) = 0;` — Unregisters a delegate to be called when the view is invalidated
- L204 _public prototype_ `virtual void RegisterOnFocusViews(const FSimpleDelegate& Delegate) = 0;` — Registers a delegate to be called when the view should be focused
- L207 _public prototype_ `virtual void UnregisterOnFocusViews(FDelegateUserObject Thing) = 0;` — Unregisters a delegate to be called when the view should be focused
- L210 _public prototype_ `virtual void RegisterOnMeshClick(const FOnMeshClick& Delegate) = 0;` — Registers a delegate to be called when the preview mesh is clicked
- L213 _public prototype_ `virtual void UnregisterOnMeshClick(FDelegateUserObject Thing) = 0;` — Unregisters a delegate to be called when the preview mesh is clicked
- L216 _public prototype_ `virtual FDelegateHandle RegisterOnSelectedBonesChanged(const FOnSelectedBonesChanged& InDelegate) = 0;` — Registers a delegate called when the bones selection has changed
- L219 _public prototype_ `virtual void UnregisterOnSelectedBonesChanged(FDelegateHandle InHandle) = 0;` — Unregisters a delegate called when the bones selection has changed
- L222 _public prototype_ `virtual FDelegateHandle RegisterOnSelectedSocketChanged(const FOnSelectedSocketChanged& Delegate) = 0;` — Registers a delegate to be called when the currently selected socket has changed
- L225 _public prototype_ `virtual void UnregisterOnSelectedSocketChanged(FDelegateHandle InHandle) = 0;` — Unregisters a delegate called when the currently selected socket has changed
- L228 _public prototype_ `virtual FDelegateHandle RegisterOnDeselectAll(const FSimpleDelegate& Delegate) = 0;` — Registers a delegate to be called when all sockets/bones are deselected
- L231 _public prototype_ `virtual void UnregisterOnDeselectAll(FDelegateHandle InHandle) = 0;` — unregisters a delegate called when all sockets/bones are deselected
- L234 _public prototype_ `virtual bool BroadcastMeshClick(HActor* HitProxy, const FViewportClick& Click) = 0;` — Broadcasts that the preview mesh was clicked
- L237 _public prototype_ `virtual void SetDefaultAnimationMode(EPreviewSceneDefaultAnimationMode Mode, bool bShowNow = true) = 0;` — Set the default mode this preview scene appears in. Optionally show the default mode.
- L240 _public prototype_ `virtual void ShowDefaultMode() = 0;` — Show the mode specifed by SetDefaultAnimationMode()
- L243 _public prototype_ `virtual void EnableWind(bool bEnableWind) = 0;` — Enable wind. Useful when simulating cloth.
- L246 _public prototype_ `virtual bool IsWindEnabled() const = 0;` — Check whether wind is enabled
- L249 _public prototype_ `virtual void SetWindStrength(float InWindStrength) = 0;` — Set the wind strength
- L252 _public prototype_ `virtual float GetWindStrength() const = 0;` — Get the wind strength
- L255 _public prototype_ `virtual void SetGravityScale(float InGravityScale) = 0;` — Set the gravity scale
- L258 _public prototype_ `virtual float GetGravityScale() const = 0;` — Get the gravity scale
- L261 _public prototype_ `virtual AActor* GetSelectedActor() const = 0;` — Get the currently selected actor
- L264 _public prototype_ `virtual FSelectedSocketInfo GetSelectedSocket() const = 0;` — Get the currently selected socket
- L267 _public prototype_ `virtual int32 GetSelectedBoneIndex() const = 0;` — Get the currently selected bone index
- L270 _public prototype_ `virtual void TogglePlayback() = 0;` — Toggle the playback of animation, if any
- L273 _public prototype_ `virtual AActor* GetActor() const = 0;` — Get the main actor
- L276 _public prototype_ `virtual void SetActor(AActor* InActor) = 0;` — Set the main actor
- L279 _public prototype_ `virtual bool AllowMeshHitProxies() const = 0;` — Get whether or not to ignore mesh hit proxies
- L282 _public prototype_ `virtual void SetAllowMeshHitProxies(bool bState) = 0;` — Set whether or not to ignore mesh hit proxies
- L285 _public prototype_ `virtual void RegisterOnSelectedLODChanged(const FOnSelectedLODChanged &Delegate) = 0;` — Register callback to be able to be notify when the select LOD is change
- L287 _public prototype_ `virtual void UnRegisterOnSelectedLODChanged(FDelegateUserObject Thing) = 0;` — Unregister callback to free up the ressources
- L289 _public prototype_ `virtual void BroadcastOnSelectedLODChanged() = 0;` — Broadcast select LOD changed
- L292 _public prototype_ `virtual void RegisterOnCameraOverrideChanged(const FSimpleDelegate& Delegate) = 0;` — Register callback for when the camera override is changed
- L295 _public prototype_ `virtual void UnregisterOnCameraOverrideChanged(FDelegateUserObject Thing) = 0;` — Unregister callback for when the camera override is changed
- L298 _public prototype_ `virtual void SetCameraOverride(TSharedPtr<FEditorCameraController> NewCamera) = 0;` — Function to override the editor camera for this scene
- L301 _public prototype_ `virtual TSharedPtr<FEditorCameraController> GetCurrentCameraOverride() const = 0;` — Get the current camera override
- L304 _public prototype_ `virtual void RegisterOnPreTick(const FSimpleDelegate& Delegate) = 0;` — Register a callback for just before the preview scene is ticked
- L307 _public prototype_ `virtual void UnregisterOnPreTick(FDelegateUserObject Thing) = 0;` — Unregister a callback for just before the preview scene is ticked
- L310 _public prototype_ `virtual void RegisterOnPostTick(const FSimpleDelegate& Delegate) = 0;` — Register a callback for just after the preview scene is ticked
- L313 _public prototype_ `virtual void UnregisterOnPostTick(FDelegateUserObject Thing) = 0;` — Unregister a callback for just after the preview scene is ticked
- L316 _public prototype_ `virtual void SetRemoveAttachedComponentFilter(const FOnRemoveAttachedComponentFilter& Delegate) = 0;` — setter/getter for can remove attach component
- L317 _public prototype_ `virtual void ClearRemoveAttachedComponentFilter() = 0;`
- L320 _public prototype_ `virtual void FlagTickable() = 0;` — Let the preview scene know that it should tick (because it is visible)
- L322 _public prototype_ `virtual void HandleSkeletonTreeSelectionChanged(const TArrayView<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems, ESelectInfo::Type InSelectInfo) = 0;` — Handle syncing selection with the skeleton tree
- L327 _public prototype_ `virtual void SetEditableSkeleton(TSharedPtr<IEditableSkeleton> InEditableSkeleton) = 0;` — Replaces the current editable skeleton. This is not a safe operation unless you're working detached from other Persona components (eg. skeleton list).
- L330 _public prototype_ `virtual void SetCustomAnimationSpeed(float InAnimationSpeed) = 0;` — Set the current custom animation playback speed
- L333 _public prototype_ `virtual float GetCustomAnimationSpeed() const = 0;` — Get the current custom animation playback speed
- L336 _public prototype_ `virtual EAnimationPlaybackSpeeds::Type GetAnimationPlaybackSpeedMode() const = 0;` — Retrieve the current animation playback speed mode
- L339 _public prototype_ `virtual void SetAnimationPlaybackSpeedMode(EAnimationPlaybackSpeeds::Type InMode) = 0;` — Set the playback speed mode
- L342 _public prototype_ `virtual bool IsPlaybackSpeedSelected(int32 InPlaybackSpeedMode) const = 0;` — Function to return whether the supplied playback speed is the current active one

#### Free symbols / members of external scopes

- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnimChangedMulticaster, UAnimationAsset*);` — called when animation asset has been changed
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnimChangedMulticaster, UAnimationAsset*);` — called when animation asset has been changed
- L27 _typedef_ `typedef FOnAnimChangedMulticaster::FDelegate FOnAnimChanged;` — anim changed
- L30 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreviewMeshChangedMulticaster, USkeletalMesh* , USkeletalMesh* );` — Called when the preview mesh has been changed;
- L30 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreviewMeshChangedMulticaster, USkeletalMesh* , USkeletalMesh* );` — Called when the preview mesh has been changed;
- L33 _typedef_ `typedef FOnPreviewMeshChangedMulticaster::FDelegate FOnPreviewMeshChanged;` — preview mesh changed
- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMeshClickMulticaster, HActor*, const FViewportClick&);`
- L35 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMeshClickMulticaster, HActor*, const FViewportClick&);`
- L37 _typedef_ `typedef FOnMeshClickMulticaster::FDelegate FOnMeshClick;`
- L40 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSelectedLODChangedMulticaster);` — The selected LOD changed
- L40 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSelectedLODChangedMulticaster);` — The selected LOD changed
- L41 _typedef_ `typedef FOnSelectedLODChangedMulticaster::FDelegate FOnSelectedLODChanged;`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectedBoneChangedMulticaster, const FName& , ESelectInfo::Type );` — The selected bone changed
- L44 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectedBoneChangedMulticaster, const FName& , ESelectInfo::Type );` — The selected bone changed
- L45 _typedef_ `typedef FOnSelectedBoneChangedMulticaster::FDelegate FOnSelectedBoneChanged;`
- L48 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectedBonesChangedMulticaster, const TArray<FName>& , ESelectInfo::Type );` — The bones selection changed
- L48 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectedBonesChangedMulticaster, const TArray<FName>& , ESelectInfo::Type );` — The bones selection changed
- L49 _typedef_ `typedef FOnSelectedBonesChangedMulticaster::FDelegate FOnSelectedBonesChanged;`
- L52 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectedSocketChangedMulticaster, const FSelectedSocketInfo& );` — The selected socket changed
- L52 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectedSocketChangedMulticaster, const FSelectedSocketInfo& );` — The selected socket changed
- L53 _typedef_ `typedef FOnSelectedSocketChangedMulticaster::FDelegate FOnSelectedSocketChanged;`
- L56 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnRemoveAttachedComponentFilter, const USceneComponent* );` — The delegate to check if the attach component can be removed
- L56 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnRemoveAttachedComponentFilter, const USceneComponent* );` — The delegate to check if the attach component can be removed

### `Source/Editor/Persona/Public/IPersonaToolkit.h` (Public)


#### class `IPersonaToolkit`  
`class IPersonaToolkit`  
_L20-94_
- desc: Reusable 'Persona' features for asset editors concerned with USkeleton-related assets
- L24 _public prototype_ `virtual ~IPersonaToolkit() = default;` — Virtual destructor
- L27 _public prototype_ `virtual USkeleton* GetSkeleton() const = 0;` — Get the skeleton that we are editing
- L30 _public prototype_ `virtual TSharedPtr<IEditableSkeleton> GetEditableSkeleton() const = 0;` — Get the editable skeleton that we are editing
- L33 _public prototype_ `virtual UDebugSkelMeshComponent* GetPreviewMeshComponent() const = 0;` — Get the preview component that we are using
- L36 _public prototype_ `virtual USkeletalMesh* GetMesh() const = 0;` — Get the skeletal mesh that we are editing
- L39 _public prototype_ `virtual void SetMesh(USkeletalMesh* InSkeletalMesh) = 0;` — Set the skeletal mesh we are editing
- L42 _public prototype_ `virtual UAnimBlueprint* GetAnimBlueprint() const = 0;` — Get the anim blueprint that we are editing
- L45 _public prototype_ `virtual UAnimationAsset* GetAnimationAsset() const = 0;` — Get the animation asset that we are editing
- L48 _public prototype_ `virtual void SetAnimationAsset(UAnimationAsset* InAnimationAsset) = 0;` — Set the animation asset we are editing
- L51 _public prototype_ `virtual TSharedRef<IPersonaPreviewScene> GetPreviewScene() const = 0;` — Get the preview scene that we are using
- L58 _public prototype_ `virtual USkeletalMesh* GetPreviewMesh() const = 0;` — Get the preview mesh, according to context (mesh, skeleton or animation etc.). Note that this returns the preview mesh that is set for the asset currently being edited, which may be different from the one displayed in the viewport.
- L67 _public prototype_ `virtual void SetPreviewMesh(USkeletalMesh* InSkeletalMesh, bool bSetPreviewMeshInAsset = true) = 0;` — Set the preview mesh, according to context (mesh, skeleton or animation etc.) Note that this sets the mesh in the asset and in the viewport (and may re-open the asset editor to apply this). @param	InSkeletalMesh			The mesh to set @param	bSetPreviewMeshInAsset	If true, the mesh will be written to the asset so it can be permanently saved. Otherwise the change is merely transient and will reset next time the editor is opened.
- L70 _public prototype_ `virtual void SetPreviewAnimationBlueprint(UAnimBlueprint* InAnimBlueprint) = 0;` — Set the preview anim blueprint, used to preview sub layers in context.
- L73 _public prototype_ `virtual UAnimBlueprint* GetPreviewAnimationBlueprint() const = 0;` — Get the preview anim blueprint, used to preview sub layers in context.
- L76 _public function_ `virtual int32 GetCustomData(const int32 Key) const` — Retrieve editor custom data. Return INDEX_NONE if the key is invalid
- L84 _public function_ `virtual void SetCustomData(const int32 Key, const int32 CustomData)` — Store the custom data using the key. Remark: The custom data memory should be clear when the editor is close by the user, this is not persistent data. Currently we use it to store the state of the editor UI to restore it properly when a refresh happen.
- L87 _public function_ `virtual void CustomizeSceneSettings(IDetailLayoutBuilder& DetailBuilder)` — Callback to customize the Preview Scene Settings details tab. Different asset types require unique options.
- L90 _public prototype_ `virtual FName GetContext() const = 0;` — Get the context in which this toolkit is being used (usually the class name of the asset)
- L93 _public prototype_ `virtual bool CanPreviewMeshUseDifferentSkeleton() const = 0;` — Returns true if the preview mesh can use skeletal meshes that don't share the same skeleton as the one being edited.

### `Source/Editor/Persona/Public/IPersonaViewport.h` (Public)


#### struct `IPersonaViewportState`  
`struct IPersonaViewportState`  
_L16-18_
- desc: Opaque state interface for saving and restoring viewport state

#### struct `FPersonaViewportNotificationOptions`  
`struct FPersonaViewportNotificationOptions`  
_L20-30_
- L22 _public prototype_ `FPersonaViewportNotificationOptions() = default;`
- L25 _public function_ `explicit FPersonaViewportNotificationOptions(const TAttribute<EVisibility> InOnGetVisibility) :OnGetVisibility(InOnGetVisibility)` — in general on GetVisibility should always be provided
- L28 _public member_ `TAttribute<EVisibility> OnGetVisibility;`
- L29 _public member_ `TAttribute<const FSlateBrush*> OnGetBrushOverride;`

#### class `IPersonaViewport`  
`class IPersonaViewport : public SCompoundWidget`  
_L33-82_
- inherits: `SCompoundWidget`
- desc: Abstract viewport that can save and restore state
- L37 _public prototype_ `virtual TSharedRef<IPersonaViewportState> SaveState() const = 0;` — Save the viewport state
- L40 _public prototype_ `virtual void RestoreState(TSharedRef<IPersonaViewportState> InState) = 0;` — Restore the viewport state
- L43 _public prototype_ `virtual FEditorViewportClient& GetViewportClient() const = 0;` — Get the viewport client contained within this viewport
- L46 _public prototype_ `virtual TSharedRef<IPinnedCommandList> GetPinnedCommandList() const = 0;` — Get the pinned commands list for this viewport
- L56 _public prototype_ `virtual TWeakPtr<SWidget> AddNotification(TAttribute<EMessageSeverity::Type> InSeverity, TAttribute<bool> InCanBeDismissed, const TSharedRef<SWidget>& InNotificationWidget, FPersonaViewportNotificationOptions InOptions) = 0;` — Add a notification widget @param	InSeverity				The severity of the message @param	InCanBeDismissed		Whether the message can be manually dismissed @param	InNotificationWidget	The widget showing the notification @param	InOptions				Specify GetVisibility callback and other optional callback overrides @return the widget containing the notification
- L62 _public prototype_ `virtual void RemoveNotification(const TWeakPtr<SWidget>& InContainingWidget) = 0;` — Remove a notification widget @param	InContainingWidget		The containing widget returned from AddNotification()
- L70 _public function_ `virtual void AddToolbarExtender(FName MenuToExtend, FMenuExtensionDelegate MenuBuilderDelegate)` — `UE_DEPRECATED(5.7, "Please extend the menu using UToolMenus instead.")` — Adds an extender to the viewport's toolbar @param MenuToExtend        The name of the toolbar menu to extend @param MenuBuilderDelegate The delegate to use when filling the menu
- L75 _public prototype_ `virtual FPersonaViewportKeyDownDelegate& GetKeyDownDelegate() = 0;` — Returns the delegate broadcasted two in case we have an unhandled key
- L78 _public prototype_ `virtual void AddOverlayWidget( TSharedRef<SWidget> InOverlaidWidget, int32 ZOrder=INDEX_NONE ) = 0;` — Overlay a widget over the whole viewport
- L81 _public prototype_ `virtual void RemoveOverlayWidget( TSharedRef<SWidget> InOverlaidWidget ) = 0;` — Remove an overlay widget from the viewport

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FPersonaViewportKeyDownDelegate, const FGeometry&, const FKeyEvent&);`
- L13 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FReply, FPersonaViewportKeyDownDelegate, const FGeometry&, const FKeyEvent&);`

### `Source/Editor/Persona/Public/IPhysicsAssetRenderInterface.h` (Public)


#### class `IPhysicsAssetRenderInterface`  
`class IPhysicsAssetRenderInterface : public IModuleInterface, public IModularFeature`  
_L11-36_
- inherits: `IModuleInterface,IModularFeature`
- L16 _public function_ `static FName GetModularFeatureName()`
- L22 _public prototype_ `virtual void DebugDraw(class USkeletalMeshComponent* const SkeletalMeshComponent, class UPhysicsAsset* const PhysicsAsset, class FPrimitiveDrawInterface* PDI) = 0;`
- L23 _public prototype_ `virtual void DebugDrawBodies(class USkeletalMeshComponent* const SkeletalMeshComponent, class UPhysicsAsset* const PhysicsAsset, FPrimitiveDrawInterface* PDI, const FColor& PrimitiveColorOverride) = 0;`
- L24 _public prototype_ `virtual void DebugDrawConstraints(class USkeletalMeshComponent* const SkeletalMeshComponent, class UPhysicsAsset* const PhysicsAsset, FPrimitiveDrawInterface* PDI) = 0;`
- L26 _public prototype_ `virtual void SaveConfig() = 0;`
- L28 _public prototype_ `virtual void ToggleShowAllBodies(class UPhysicsAsset* const PhysicsAsset) = 0;`
- L29 _public prototype_ `virtual void ToggleShowAllConstraints(class UPhysicsAsset* const PhysicsAsset) = 0;`
- L30 _public prototype_ `virtual bool AreAnyBodiesHidden(class UPhysicsAsset* const PhysicsAsset) = 0;`
- L31 _public prototype_ `virtual bool AreAnyConstraintsHidden(class UPhysicsAsset* const PhysicsAsset) = 0;`
- L33 _public prototype_ `virtual EConstraintTransformComponentFlags GetConstraintViewportManipulationFlags(class UPhysicsAsset* const PhysicsAsset) = 0;`
- L34 _public prototype_ `virtual bool IsDisplayingConstraintTransformComponentRelativeToDefault(class UPhysicsAsset* const PhysicsAsset, const EConstraintTransformComponentFlags ComponentFlags) = 0;`
- L35 _public prototype_ `virtual void SetDisplayConstraintTransformComponentRelativeToDefault(class UPhysicsAsset* const PhysicsAsset, const EConstraintTransformComponentFlags ComponentFlags, const bool bShouldDisplayRelativeToDefault) = 0;`

### `Source/Editor/Persona/Public/PersonaAssetEditorToolkit.h` (Public)


#### class `FPersonaAssetEditorToolkit`  
`class FPersonaAssetEditorToolkit : public FWorkflowCentricApplication`  
_L17-54_
- inherits: `FWorkflowCentricApplication`
- desc: Persona asset editor toolkit wrapper, used to auto inject the persona editor mode manager
- L21 _public prototype_ `virtual void CreateEditorModeManager() override;` — FAssetEditorToolkit interface
- L24 _public prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit) override;` — IToolkitHost Interface
- L25 _public prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit) override;`
- L28 _public function_ `TSharedPtr<IToolkit> GetHostedToolkit() const` — Returns the currently hosted toolkit. Can be invalid if no toolkit is being hosted.
- L29 _public function_ `FOnAttachToolkit& GetOnAttachToolkit()`
- L30 _public function_ `FOnDetachToolkit& GetOnDetachToolkit()`
- L32 _public prototype_ `virtual void OnClose() override;`
- L35 _protected prototype_ `virtual void OnEditorModeIdChanged(const FEditorModeID& ModeChangedID, bool bIsEnteringMode);`
- L37 _protected prototype_ `virtual void RouteTreeSelectionToModeManager(const TConstArrayView<TSharedPtr<ISkeletonTreeItem>>& InItems);`
- L40 _protected prototype_ `virtual void OnSelectionSetChanged(const UTypedElementSelectionSet* InSelectionSet);` — Called when the editor's TypedElementSelectionSet changes. Override to update details views, etc.
- L43 _protected member_ `FOnAttachToolkit OnAttachToolkit;`
- L44 _protected member_ `FOnDetachToolkit OnDetachToolkit;`
- L47 _protected member_ `TSharedPtr<IToolkit> HostedToolkit;` — The toolkit we're currently hosting.
- L50 _private member_ `FDelegateHandle SelectionSetChangedHandle;`
- L53 _private member_ `TArray<FTypedElementHandle> RoutedSelectionHandles;` — Element handles routed by the last call to RouteTreeSelectionToModeManager, so we only deselect our own elements.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API PERSONA_API`
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAttachToolkit, const TSharedRef<IToolkit>&);`
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAttachToolkit, const TSharedRef<IToolkit>&);`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDetachToolkit, const TSharedRef<IToolkit>&);`
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDetachToolkit, const TSharedRef<IToolkit>&);`

### `Source/Editor/Persona/Public/PersonaCommonCommands.h` (Public)


#### class `FPersonaCommonCommands`  
`class FPersonaCommonCommands : public TCommands<FPersonaCommonCommands>`  
_L16-30_
- inherits: `TCommands<FPersonaCommonCommands>`
- L19 _public function_ `FPersonaCommonCommands() : TCommands<FPersonaCommonCommands>(TEXT("PersonaCommon"), NSLOCTEXT("Contexts", "PersonaCommon", "Persona Common"), NAME_None, FAppStyle::GetAppStyleSetName())`
- L24 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public prototype_ `FORCENOINLINE static const FPersonaCommonCommands& Get();`
- L29 _public member_ `TSharedPtr<FUICommandInfo> TogglePlay;` — Toggle playback

### `Source/Editor/Persona/Public/PersonaDelegates.h` (Public)


#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectBlendProfile, class UBlendProfile*);` — Called when a blend profile is selected in the blend profile tab
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectBlendProfile, class UBlendProfile*);` — Called when a blend profile is selected in the blend profile tab
- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateViewport, TWeakPtr<class SAnimationEditorViewportTabBody>);` — Called when the preview viewport is created
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCreateViewport, TWeakPtr<class SAnimationEditorViewportTabBody>);` — Called when the preview viewport is created
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnInvokeTab, const FTabId&);` — Called to invoke a specified tab
- L21 _prototype_ `DECLARE_DELEGATE_OneParam(FOnInvokeTab, const FTabId&);` — Called to invoke a specified tab
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnObjectsSelected, const TArray<UObject*>& );` — Called to display a selected object in a details panel
- L24 _prototype_ `DECLARE_DELEGATE_OneParam(FOnObjectsSelected, const TArray<UObject*>& );` — Called to display a selected object in a details panel
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnObjectSelected, UObject* );` — Called to display a selected object in a details panel
- L27 _prototype_ `DECLARE_DELEGATE_OneParam(FOnObjectSelected, UObject* );` — Called to display a selected object in a details panel
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOpenNewAsset, UObject* );` — Called to replace the currently edited asset or open it (depending on context)
- L30 _prototype_ `DECLARE_DELEGATE_OneParam(FOnOpenNewAsset, UObject* );` — Called to replace the currently edited asset or open it (depending on context)
- L33 _delegate_ `DECLARE_DELEGATE_RetVal(UObject*, FOnGetAsset);` — Called to get an object (used by the asset details panel)
- L33 _prototype_ `DECLARE_DELEGATE_RetVal(UObject*, FOnGetAsset);` — Called to get an object (used by the asset details panel)
- L36 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnEditCurves, UAnimSequenceBase* , const TArray<IAnimationEditor::FCurveEditInfo>& , const TSharedPtr<ITimeSliderController>& );` — Called to invoke the curve editor
- L36 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnEditCurves, UAnimSequenceBase* , const TArray<IAnimationEditor::FCurveEditInfo>& , const TSharedPtr<ITimeSliderController>& );` — Called to invoke the curve editor
- L39 _delegate_ `DECLARE_DELEGATE(FOnBlendSpaceNavigateUp);` — Called when the user navigates with pageup
- L39 _prototype_ `DECLARE_DELEGATE(FOnBlendSpaceNavigateUp);` — Called when the user navigates with pageup
- L42 _delegate_ `DECLARE_DELEGATE(FOnBlendSpaceNavigateDown);` — Called when the user navigates with pagedown
- L42 _prototype_ `DECLARE_DELEGATE(FOnBlendSpaceNavigateDown);` — Called when the user navigates with pagedown
- L45 _delegate_ `DECLARE_DELEGATE(FOnBlendSpaceCanvasDoubleClicked);` — Called when the blendspace canvas is double clicked
- L45 _prototype_ `DECLARE_DELEGATE(FOnBlendSpaceCanvasDoubleClicked);` — Called when the blendspace canvas is double clicked
- L48 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBlendSpaceSampleDoubleClicked, int32 );` — Called when a blendspace sample point is double clicked
- L48 _prototype_ `DECLARE_DELEGATE_OneParam(FOnBlendSpaceSampleDoubleClicked, int32 );` — Called when a blendspace sample point is double clicked
- L51 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBlendSpaceSampleRemoved, const int32 );` — Called when a blendspace sample point is removed
- L51 _prototype_ `DECLARE_DELEGATE_OneParam(FOnBlendSpaceSampleRemoved, const int32 );` — Called when a blendspace sample point is removed
- L54 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(int32, FOnBlendSpaceSampleAdded, UAnimSequence* , const FVector& , bool );` — Called when a blendspace sample point is added. Returns the new SampleIndex
- L54 _prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(int32, FOnBlendSpaceSampleAdded, UAnimSequence* , const FVector& , bool );` — Called when a blendspace sample point is added. Returns the new SampleIndex
- L57 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnBlendSpaceSampleDuplicated, int32 , const FVector& , bool );` — Called when a blendspace sample point is added
- L57 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnBlendSpaceSampleDuplicated, int32 , const FVector& , bool );` — Called when a blendspace sample point is added
- L60 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnBlendSpaceSampleReplaced, const int32 , UAnimSequence* );` — Called when a blendspace sample point is replaced
- L60 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnBlendSpaceSampleReplaced, const int32 , UAnimSequence* );` — Called when a blendspace sample point is replaced
- L63 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FName, FOnGetBlendSpaceSampleName, int32 );` — Called to get the overridden name of a blend sample
- L63 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FName, FOnGetBlendSpaceSampleName, int32 );` — Called to get the overridden name of a blend sample
- L66 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnExtendBlendSpaceSampleTooltip, int32 );` — Called to extend a sample's tooltip
- L66 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedRef<SWidget>, FOnExtendBlendSpaceSampleTooltip, int32 );` — Called to extend a sample's tooltip
- L69 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSetBlendSpacePreviewPosition, FVector );` — Called to let the blendspace editor UI set the preview position of an external blendspace node
- L69 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSetBlendSpacePreviewPosition, FVector );` — Called to let the blendspace editor UI set the preview position of an external blendspace node
- L72 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCurvePicked, const FName& );` — Called by the curve picker to indicate that a curve was chosen by the user
- L72 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCurvePicked, const FName& );` — Called by the curve picker to indicate that a curve was chosen by the user
- L75 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsCurveNameMarkedForExclusion, const FName& );` — Called by the curve picker to filter out curve names that are displayed to the user
- L75 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsCurveNameMarkedForExclusion, const FName& );` — Called by the curve picker to filter out curve names that are displayed to the user
- L78 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNotifyPicked, const FName& );` — Called by the notify picker to indicate that a notify was chosen by the user
- L78 _prototype_ `DECLARE_DELEGATE_OneParam(FOnNotifyPicked, const FName& );` — Called by the notify picker to indicate that a notify was chosen by the user
- L81 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCurvesPicked, const TConstArrayView<FName> );` — Called by the curve picker to indicate the curves chosen by the user
- L81 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCurvesPicked, const TConstArrayView<FName> );` — Called by the curve picker to indicate the curves chosen by the user
- L84 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAttributesPicked, const TConstArrayView<FAnimationAttributeIdentifier>);` — Called by the attribute picker to indicate the attributes chosen by the user
- L84 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAttributesPicked, const TConstArrayView<FAnimationAttributeIdentifier>);` — Called by the attribute picker to indicate the attributes chosen by the user

### `Source/Editor/Persona/Public/PersonaModule.h` (Public)


#### struct `FPersonaEditModes`  
`struct FPersonaEditModes`  
_L41-45_
- desc: Editor mode constants
- L44 _public member_ `const static FEditorModeID SkeletonSelection;` — Selection/manipulation of bones & sockets

#### struct `FPersonaToolkitArgs`  
`struct FPersonaToolkitArgs`  
_L76-99_
- desc: Initialization parameters for persona toolkits
- L82 _public member_ `FOnPreviewSceneCreated::FDelegate OnPreviewSceneCreated;` — Delegate called when the preview scene is created, used to setup the scene If this is not set, then a default scene will be set up.
- L85 _public member_ `bool bCreatePreviewScene = true;` — Whether to create a preview scene
- L90 _public member_ `FOnPreviewSceneSettingsCustomized::FDelegate OnPreviewSceneSettingsCustomized;` — Delegate called when the preview scene settings are being customized, supplies the IDetailLayoutBuilder for the user to customize the layout however they wish.
- L96 _public member_ `bool bPreviewMeshCanUseDifferentSkeleton = false;` — Set to true if the preview mesh can be associated with a skeleton different from the one being inspected by Persona. Used for editors that are mostly skeleton agnostic.
- L98 _public prototype_ `FPersonaToolkitArgs() = default;`

#### struct `FAnimDocumentArgs`  
`struct FAnimDocumentArgs`  
_L101-120_
- L103 _public function_ `FAnimDocumentArgs(const TSharedRef<class IPersonaPreviewScene>& InPreviewScene, const TSharedRef<class IPersonaToolkit>& InPersonaToolkit, const TSharedRef<class IEditableSkeleton>& InEditableSkeleton, FSimpleMulticastDelegate& InOnSectionsChanged) : PreviewScene(InPreviewScene) , PersonaToolkit(InPersonaToolkit) , EditableSkeleton(InEditableSkeleton) , OnSectionsChanged(InOnSectionsChanged)`
- L111 _public member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScene;` — Required args
- L112 _public member_ `TWeakPtr<class IPersonaToolkit> PersonaToolkit;`
- L113 _public member_ `TWeakPtr<class IEditableSkeleton> EditableSkeleton;`
- L114 _public member_ `FSimpleMulticastDelegate& OnSectionsChanged;`
- L117 _public member_ `FOnObjectsSelected OnDespatchObjectsSelected;` — Optional args
- L118 _public member_ `FOnInvokeTab OnDespatchInvokeTab;`
- L119 _public member_ `FSimpleDelegate OnDespatchSectionsChanged;`

#### struct `FBlendSpaceEditorArgs`  
`struct FBlendSpaceEditorArgs`  
_L122-162_
- L125 _public member_ `FOnBlendSpaceSampleRemoved OnBlendSpaceSampleRemoved;` — Called when a blendspace sample point is removed
- L128 _public member_ `FOnBlendSpaceSampleAdded OnBlendSpaceSampleAdded;` — Called when a blendspace sample point is added
- L131 _public member_ `FOnBlendSpaceSampleReplaced OnBlendSpaceSampleReplaced;` — Called when a blendspace sample point is replaced
- L134 _public member_ `FOnBlendSpaceNavigateUp OnBlendSpaceNavigateUp;` — Called when the blendspace canvas is double clicked
- L137 _public member_ `FOnBlendSpaceNavigateDown OnBlendSpaceNavigateDown;` — Called when the blendspace canvas is double clicked
- L140 _public member_ `FOnBlendSpaceCanvasDoubleClicked OnBlendSpaceCanvasDoubleClicked;` — Called when the blendspace canvas is double clicked
- L143 _public member_ `FOnBlendSpaceSampleDoubleClicked OnBlendSpaceSampleDoubleClicked;` — Called when a blendspace sample point is double clicked
- L146 _public member_ `FOnGetBlendSpaceSampleName OnGetBlendSpaceSampleName;` — Called to get the overridden name of a blend sample
- L149 _public member_ `TAttribute<FVector> PreviewPosition;` — Allows the target preview position to be programmatically driven
- L152 _public member_ `TAttribute<FVector> PreviewFilteredPosition;` — Allows the current position to be programmatically driven
- L155 _public member_ `FOnExtendBlendSpaceSampleTooltip OnExtendSampleTooltip;` — Allows an external widget to be inserted into a sample's tooltip
- L158 _public member_ `FOnSetBlendSpacePreviewPosition OnSetPreviewPosition;` — Allows preview position to drive external node
- L161 _public member_ `FName StatusBarName = TEXT("Ass` — Status bar to display hint messages in

#### struct `FBlendSpacePreviewArgs`  
`struct FBlendSpacePreviewArgs`  
_L164-176_
- L166 _public member_ `TAttribute<const UBlendSpace*> PreviewBlendSpace;`
- L169 _public member_ `TAttribute<FVector> PreviewPosition;` — Allows the target preview position to be programmatically driven
- L172 _public member_ `TAttribute<FVector> PreviewFilteredPosition;` — Allows the current preview position to be programmatically driven
- L175 _public member_ `FOnGetBlendSpaceSampleName OnGetBlendSpaceSampleName;` — Called to get the overridden name of a blend sample

#### enum `EViewportCorner`  
`enum class EViewportCorner : uint8`  
_L179-185_
- desc: Places that viewport text can be placed
- L181 _public enumerator_ `TopLeft`
- L182 _public enumerator_ `TopRight`
- L183 _public enumerator_ `BottomLeft`
- L184 _public enumerator_ `BottomRight`

#### struct `FAnimationScrubPanelDelegates`  
`struct FAnimationScrubPanelDelegates`  
_L206-249_
- desc: Struct to provide delegates to change the timeline behavior for certain clients
- L209 _public member_ `FAnimationScrubPanel_IsRecordingActive IsRecordingActiveDelegate;` — Determines if recording is currently active
- L212 _public member_ `FAnimationScrubPanel_GetRecordingVisibility GetRecordingVisibilityDelegate;` — Determines if the recording button should be visible
- L215 _public member_ `FAnimationScrubPanel_StartRecording StartRecordingDelegate;` — Starts the recording
- L218 _public member_ `FAnimationScrubPanel_StopRecording StopRecordingDelegate;` — Stops the recording
- L221 _public member_ `FAnimationScrubPanel_GetPlaybackMode GetPlaybackModeDelegate;` — Determines if the playback is currently active
- L224 _public member_ `FAnimationScrubPanel_SetPlaybackMode SetPlaybackModeDelegate;` — Sets the playback mode
- L227 _public member_ `FAnimationScrubPanel_GetPlaybackTime GetPlaybackTimeDelegate;` — Returns the current playback time
- L230 _public member_ `FAnimationScrubPanel_SetPlaybackTime SetPlaybackTimeDelegate;` — Seeks to a given time
- L233 _public member_ `FAnimationScrubPanel_StepForward StepForwardDelegate;` — steps on frame / key forward
- L236 _public member_ `FAnimationScrubPanel_StepBackward StepBackwardDelegate;` — steps on frame / key backward
- L239 _public member_ `FAnimationScrubPanel_GetIsLooping GetIsLoopingDelegate;` — Returns the current playback looping flag
- L242 _public member_ `FAnimationScrubPanel_SetIsLooping SetIsLoopingDelegate;` — Sets the playback looping flag
- L245 _public member_ `FAnimationScrubPanel_GetPlaybackTimeRange GetPlaybackTimeRangeDelegate;` — Returns the playback time range
- L248 _public member_ `FAnimationScrubPanel_GetNumberOfKeys GetNumberOfKeysDelegate;` — Returns the number of keys for this playback

#### struct `FPersonaViewportArgs`  
`struct FPersonaViewportArgs`  
_L252-315_
- desc: Arguments used to create a persona viewport tab
- L254 _public function_ `FPersonaViewportArgs(const TSharedRef<class IPersonaPreviewScene>& InPreviewScene) : PreviewScene(InPreviewScene) , ContextName(NAME_None) , bShowShowMenu(true) , bShowLODMenu(true) , bShowPlaySpeedMenu(true) , bShowTimeline(true) , bShowStats(true) , bAlwaysShowTransformToolbar(false) , bShowFloorOptions(true) , bShowTurnTable(true) , bShowPhysicsMenu(false)`
- L269 _public member_ `TSharedRef<class IPersonaPreviewScene> PreviewScene;` — Required args
- L272 _public member_ `TSharedPtr<class FBlueprintEditor> BlueprintEditor;` — Optional blueprint editor that we can be embedded in
- L275 _public member_ `FOnViewportCreated OnViewportCreated;` — Delegate fired when the viewport is created
- L278 _public member_ `TArray<TSharedPtr<FExtender>> Extenders;` — Menu extenders
- L281 _public member_ `FOnGetViewportText OnGetViewportText;` — Delegate used to customize viewport corner text
- L284 _public member_ `FName ContextName;` — The context in which we are constructed. Used to persist various settings.
- L287 _public member_ `bool bShowShowMenu;` — Whether to show the 'Show' menu
- L290 _public member_ `bool bShowLODMenu;` — Whether to show the 'LOD' menu
- L293 _public member_ `bool bShowPlaySpeedMenu;` — Whether to show the 'Play Speed' menu
- L296 _public member_ `bool bShowTimeline;` — Whether to show the animation timeline
- L299 _public member_ `bool bShowStats;` — Whether to show in-viewport stats
- L302 _public member_ `bool bAlwaysShowTransformToolbar;` — Whether we should always show the transform toolbar for this viewport
- L305 _public member_ `bool bShowFloorOptions;` — Whether to show options relating to floor height
- L308 _public member_ `bool bShowTurnTable;` — Whether to show options relating to turntable
- L311 _public member_ `bool bShowPhysicsMenu;` — Whether to show options relating to physics
- L314 _public member_ `FAnimationScrubPanelDelegates TimelineDelegates;` — A structure providing delegates to change the timeline behavior

#### struct `FPersonaAdvancedPreviewSceneTabSettings`  
`struct FPersonaAdvancedPreviewSceneTabSettings`  
_L321-328_
- desc: Some settings for the detail customization inside the advanced preview scene settings tab. This allows you to hide specific categories.
- L323 _public member_ `bool bHideAnimationCategory = false;`
- L324 _public member_ `bool bHideAnimationBlueprintCategory = false;`
- L325 _public member_ `bool bHideMeshCategory = false;`
- L326 _public member_ `bool bHidePhysicsCategory = false;`
- L327 _public member_ `bool bHideAdditionalMeshesCategory = false;`

#### class `FPersonaModule`  
`class FPersonaModule : public IModuleInterface, public IHasMenuExtensibility`  
_L333-665_
- inherits: `IModuleInterface,IHasMenuExtensibility`
- desc: Persona module manages the lifetime of all instances of Persona editors.
- L340 _public prototype_ `virtual void StartupModule();` — Called right after the module's DLL has been loaded and the module object has been created
- L345 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L348 _public prototype_ `virtual TSharedRef<IPersonaToolkit> CreatePersonaToolkit(UObject* InAsset, const FPersonaToolkitArgs& PersonaToolkitArgs, USkeleton* InSkeleton = nullptr) const;` — Create a re-usable toolkit that multiple asset editors that are concerned with USkeleton-related data can use
- L349 _public prototype_ `virtual TSharedRef<IPersonaToolkit> CreatePersonaToolkit(USkeleton* InSkeleton, const FPersonaToolkitArgs& PersonaToolkitArgs) const;`
- L350 _public prototype_ `virtual TSharedRef<IPersonaToolkit> CreatePersonaToolkit(UAnimationAsset* InAnimationAsset, const FPersonaToolkitArgs& PersonaToolkitArgs) const;`
- L351 _public prototype_ `virtual TSharedRef<IPersonaToolkit> CreatePersonaToolkit(USkeletalMesh* InSkeletalMesh, const FPersonaToolkitArgs& PersonaToolkitArgs) const;`
- L352 _public prototype_ `virtual TSharedRef<IPersonaToolkit> CreatePersonaToolkit(UAnimBlueprint* InAnimBlueprint, const FPersonaToolkitArgs& PersonaToolkitArgs) const;`
- L353 _public prototype_ `virtual TSharedRef<IPersonaToolkit> CreatePersonaToolkit(UPhysicsAsset* InPhysicsAsset, const FPersonaToolkitArgs& PersonaToolkitArgs) const;`
- L356 _public prototype_ `virtual TSharedRef<IAssetFamily> CreatePersonaAssetFamily(const UObject* InAsset) const;` — Create an asset family for the supplied persona asset
- L359 _public prototype_ `virtual void BroadcastAssetFamilyChange() const;` — Broadcast event that all asset families need to change
- L362 _public prototype_ `virtual void RecordAssetOpened(const FAssetData& InAssetData) const;` — Record that an asset was opened (forward to relevant asset families)
- L365 _public prototype_ `virtual TSharedRef<SWidget> CreateAssetFamilyShortcutWidget(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TSharedRef<class IAssetFamily>& InAssetFamily) const;` — Create a shortcut widget for an asset family
- L368 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateDetailsTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, FOnDetailsCreated InOnDetailsCreated) const;` — Create a details panel tab factory
- L371 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreatePersonaViewportTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const FPersonaViewportArgs& InArgs) const;` — Create a persona viewport tab factory
- L374 _public prototype_ `virtual void RegisterPersonaViewportTabFactories(FWorkflowAllowedTabSet& TabSet, const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const FPersonaViewportArgs& InArgs) const;` — Register 4 Persona viewport tab factories
- L377 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateAnimNotifiesTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TSharedRef<class IEditableSkeleton>& InEditableSkeleton, FOnObjectsSelected InOnObjectsSelected) const;` — Create an anim notifies tab factory
- L380 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateCurveViewerTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TSharedPtr<class IEditableSkeleton>& InEditableSkeleton, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene, FOnObjectsSelected InOnObjectsSelected, bool bInReadOnlyCurveViewer = true) const;` — Create a skeleton curve viewer tab factory
- L383 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateCurveMetadataEditorTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, UObject* InMetadataHost, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene, FOnObjectsSelected InOnObjectsSelected) const;` — Create a skeleton curve metadata editor tab factory
- L386 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateRetargetSourcesTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TSharedRef<class IEditableSkeleton>& InEditableSkeleton, FSimpleMulticastDelegate& InOnPostUndo) const;` — Create a retarget sources tab factory
- L389 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateAdvancedPreviewSceneTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TSharedRef<IPersonaPreviewScene>& InPreviewScene) const;` — Create a tab factory used to configure preview scene settings
- L390 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateAdvancedPreviewSceneTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TSharedRef<IPersonaPreviewScene>& InPreviewScene, const FPersonaAdvancedPreviewSceneTabSettings& DetailCustomizationSettings) const;`
- L393 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateAnimationAssetBrowserTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TSharedRef<IPersonaToolkit>& InPersonaToolkit, FOnOpenNewAsset InOnOpenNewAsset, FOnAnimationSequenceBrowserCreated InOnAnimationSequenceBrowserCreated, bool bInShowHistory) const;` — Create a tab factory for the animation asset browser
- L396 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateAssetDetailsTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, FOnGetAsset InOnGetAsset, FOnDetailsCreated InOnDetailsCreated) const;` — Create a tab factory for editing a single object (like an animation asset)
- L399 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateMorphTargetTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TSharedRef<IPersonaPreviewScene>& InPreviewScene, FSimpleMulticastDelegate& OnPostUndo) const;` — Create a tab factory for previewing morph targets
- L402 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateMorphTargetTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, TSharedRef<IMorphTargetViewer> InViewerWidget) const;` — Create a tab factory for previewing morph targets
- L405 _public prototype_ `virtual TSharedRef<IMorphTargetViewer> CreateDefaultMorphTargetViewerWidget(const TSharedRef<IPersonaPreviewScene>& InPreviewScene, FSimpleMulticastDelegate& OnPostUndo) const;` — Create the default morph target viewer widget
- L408 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateAnimBlueprintPreviewTabFactory(const TSharedRef<class FBlueprintEditor>& InBlueprintEditor, const TSharedRef<IPersonaPreviewScene>& InPreviewScene) const;` — Create a tab factory for editing anim blueprint preview & defaults
- L411 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreatePoseWatchTabFactory(const TSharedRef<class FBlueprintEditor>& InBlueprintEditor) const;` — Create a tab factory for the pose watch manager
- L414 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateAnimBlueprintAssetOverridesTabFactory(const TSharedRef<class FBlueprintEditor>& InBlueprintEditor, UAnimBlueprint* InAnimBlueprint, FSimpleMulticastDelegate& InOnPostUndo) const;` — Create a tab factory for editing anim blueprint parent overrides
- L417 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateSkeletonSlotNamesTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TSharedRef<class IEditableSkeleton>& InEditableSkeleton, FOnObjectSelected InOnObjectSelected) const;` — Create a tab factory for editing slot names and groups
- L420 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreatePersonaToolboxTabFactory(const TSharedRef<class FPersonaAssetEditorToolkit>& InHostingApp) const;` — Create a toolbox tab factory
- L423 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateAttributeViewerTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene) const;` — Create a attributes viewer tab factory
- L426 _public prototype_ `virtual TSharedRef<SWidget> CreateBlendSpacePreviewWidget(const FBlendSpacePreviewArgs& InArgs) const;` — Create a widget to preview a blendspace
- L429 _public prototype_ `virtual TSharedRef<SWidget> CreateBlendSpaceEditWidget(UBlendSpace* InBlendSpace, const FBlendSpaceEditorArgs& InArgs) const;` — Create a widget to edit a blendspace
- L432 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateAnimMontageSectionsTabFactory(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TSharedRef<IPersonaToolkit>& InPersonaToolkit, FSimpleMulticastDelegate& InOnSectionsChanged) const;` — Create a tab factory for editing montage sections
- L435 _public prototype_ `virtual TSharedRef<FWorkflowTabFactory> CreateAnimAssetFindReplaceTabFactory(const TSharedRef<FWorkflowCentricApplication>& InHostingApp, const FAnimAssetFindReplaceConfig& InConfig) const;` — Create a tab factory for finding and replacing in anim data
- L438 _public prototype_ `virtual TSharedRef<SWidget> CreateFindReplaceWidget(const FAnimAssetFindReplaceConfig& InConfig) const;` — Create a widget for finding and replacing in anim data
- L441 _public prototype_ `virtual TSharedRef<SWidget> CreateEditorWidgetForAnimDocument(const TSharedRef<IAnimationEditor>& InHostingApp, UObject* InAnimAsset, const FAnimDocumentArgs& InArgs, FString& OutDocumentLink);` — Create a widget that acts as a document for an animation asset
- L444 _public prototype_ `virtual TSharedRef<IAnimSequenceCurveEditor> CreateCurveWidgetForAnimDocument(const TSharedRef<class FWorkflowCentricApplication>& InHostingApp, const TSharedRef<IPersonaPreviewScene>& InPreviewScene, UAnimSequenceBase* InAnimSequence, const TSharedPtr<ITimeSliderController>& InExternalTimeSliderController, const TSharedPtr<FTabManager>& InTabManager);` — Create a widget that acts as a curve document for an animation asset
- L447 _public prototype_ `virtual void CustomizeMeshDetails(const TSharedRef<IDetailsView>& InDetailsView, const TSharedRef<IPersonaToolkit>& InPersonaToolkit);` — Customize a skeletal mesh details panel
- L450 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager()` — Gets the extensibility managers for outside entities to extend persona editor's menus and toolbars
- L451 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager()`
- L454 _public prototype_ `virtual void ImportNewAsset(USkeleton* InSkeleton, EFBXImportType DefaultImportType);` — Import a new asset using the supplied skeleton
- L457 _public prototype_ `virtual void TestSkeletonCurveMetaDataForUse(const TSharedRef<IEditableSkeleton>& InEditableSkeleton) const;` — Check all animations & skeletal meshes for curve metadata usage
- L460 _public prototype_ `virtual void ApplyCompression(TArray<TWeakObjectPtr<class UAnimSequence>>& AnimSequences, bool bPickBoneSettingsOverride);` — Apply Compression to list of animations and optionally asks to pick an overrides to the bone compression settings
- L463 _public prototype_ `virtual bool ExportToFBX(TArray<TWeakObjectPtr<class UAnimSequence>>& AnimSequences, USkeletalMesh* SkeletalMesh);` — Export to FBX files of the list of animations
- L466 _public prototype_ `virtual void AddLoopingInterpolation(TArray<TWeakObjectPtr<class UAnimSequence>>& AnimSequences);` — Add looping interpolation to the list of animations
- L469 _public function_ `virtual void CustomizeSlotNodeDetails(const TSharedRef<class IDetailsView>& InDetailsView, FOnInvokeTab InOnInvokeTab)` — `UE_DEPRECATED(4.24, "Function renamed, please use CustomizeBlueprintEditorDetails")`
- L472 _public prototype_ `virtual void CustomizeBlueprintEditorDetails(const TSharedRef<class IDetailsView>& InDetailsView, FOnInvokeTab InOnInvokeTab);` — Customize the details of a slot node for the specified details view
- L475 _public prototype_ `virtual class IPersonaEditorModeManager* CreatePersonaEditorModeManager();` — Create a Persona editor mode manager. Should be destroyed using plain ol' delete. Note: Only FPersonaEditMode-derived modes should be used with this manager!
- L478 _public function_ `virtual FIsRecordingActive& OnIsRecordingActive()` — Delegate used to query whether recording is active
- L481 _public function_ `virtual FRecord& OnRecord()` — Delegate used to start recording animation
- L484 _public function_ `virtual FStopRecording& OnStopRecording()` — Delegate used to stop recording animation
- L487 _public function_ `virtual FGetCurrentRecording& OnGetCurrentRecording()` — Delegate used to get the currently recording animation
- L490 _public function_ `virtual FGetCurrentRecordingTime& OnGetCurrentRecordingTime()` — Delegate used to get the currently recording animation time
- L493 _public function_ `virtual FOnPreviewSceneCreated& OnPreviewSceneCreated()` — Delegate broadcast when a preview scene is created
- L496 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnCustomizeMeshDetails, IDetailLayoutBuilder& DetailLayout, TWeakObjectPtr<USkeletalMesh> SkeletalMesh);` — Delegates that allow customizing the mesh details layout and are called from within PersonaMeshDetails' CustomizeDetails().
- L497 _public function_ `virtual TArray<FOnCustomizeMeshDetails>& GetCustomizeMeshDetailsDelegates()`
- L522 _public typedef_ `typedef FCommonToolMenuExtensionArgs FCommonToolbarExtensionArgs;`
- L525 _public prototype_ `virtual void AddCommonMenuExtensions(UToolMenu* InToolMenu, const FCommonToolMenuExtensionArgs& InArgs = FCommonToolMenuExtensionArgs());` — Add common menu extensions
- L528 _public prototype_ `virtual void AddCommonToolbarExtensions(UToolMenu* InToolMenu, const FCommonToolMenuExtensionArgs& InArgs = FCommonToolMenuExtensionArgs());` — Add common toolbar extensions
- L531 _public prototype_ `virtual void AddCommonToolbarExtensions(FToolBarBuilder& InToolbarBuilder, TSharedRef<IPersonaToolkit> PersonaToolkit, const FCommonToolbarExtensionArgs& InArgs = FCommonToolbarExtensionArgs());` — Add common toobar extensions (legacy support) - DEPRECATED
- L534 _public function_ `virtual FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions()` — Register common layout extensions
- L537 _public function_ `virtual FOnRegisterTabs& OnRegisterTabs()` — Register common tabs
- L540 _public prototype_ `virtual TSharedRef<SWidget> CreateMultiCurvePicker(const USkeleton* InSkeleton, FOnCurvesPicked InOnCurvesPicked, FIsCurveNameMarkedForExclusion InIsCurveNameMarkedForExclusion = FIsCurveNameMarkedForExclusion());` — Create a widget that can choose multiple curve names. Derives available names from the asset registry list of assets that use the specified skeleton.
- L543 _public prototype_ `virtual TSharedRef<SWidget> CreateCurvePicker(const USkeleton* InSkeleton, FOnCurvePicked InOnCurvePicked, FIsCurveNameMarkedForExclusion InIsCurveNameMarkedForExclusion = FIsCurveNameMarkedForExclusion());` — Create a widget that can choose a curve name. Derives available names from the asset registry list of assets that use the specified skeleton.
- L546 _public prototype_ `virtual TSharedRef<SWidget> CreateAttributePicker( const TObjectPtr<const USkeleton> InSkeleton, FOnAttributesPicked InOnAttributesPicked, const bool bEnableMultiSelect, const bool bCanShowOtherSkeletonAttributes);` — Create a widget that can choose an attribute. Derives available attributes from the asset registry list of assets that use the specified skeleton.
- L553 _public prototype_ `virtual TSharedRef<SWidget> CreateSkeletonNotifyPicker(FOnNotifyPicked InOnNotifyPicked, TSharedPtr<IEditableSkeleton> InEditableSkeleton = nullptr, TSharedPtr<FAssetEditorToolkit> InHostingApp = nullptr, bool bInShowSyncMarkers = false, bool bInShowNotifies = true, bool bInShowCompatibleSkeletonAssets = true, bool bInShowOtherAssets = true);` — Create a widget that can choose a notify name. @see SSkeletonAnimNotifies.
- L568 _public prototype_ `virtual void RegisterNotifyHostAsset(const FTopLevelAssetPath& InAssetClassPath, const FNotifyHostAssetParameters& InParameters);` — Register an asset type that can contain named anim notifies
- L571 _public prototype_ `virtual void UnregisterNotifyHostAsset(const FTopLevelAssetPath& InAssetClassPath);` — Unregister an asset type that can contain named anim notifies
- L574 _public prototype_ `virtual const FNotifyHostAssetParameters* FindNotifyHostAsset(UObject* InAsset);` — Find registered notify host parameters by asset class
- L577 _public prototype_ `virtual TArray<FTopLevelAssetPath> GetAllNotifyHostAssetClassPaths() const;` — Get all the registered notify host class paths
- L580 _public prototype_ `virtual uint32 GetNotifyHostAssetVersion() const;` — Get the version information for the notify host asset registry
- L584 _public prototype_ `void RegisterBlendProfilePickerExtender(TSharedPtr<IBlendProfilePickerExtender> Extender);` — Register a new blend provider in the editor picker for FBlendProfileInterfaceWrapper
- L586 _public prototype_ `void UnregisterBlendProfilePickerExtender(const FName ExtenderId);`
- L588 _public prototype_ `const TArray<TSharedPtr<IBlendProfilePickerExtender>>& GetCustomBlendProfiles() const;`
- L591 _private member_ `TArray<TSharedPtr<IBlendProfilePickerExtender>> CustomBlendProfiles;`
- L594 _private prototype_ `void HandleNewAnimNotifyBlueprintCreated(UBlueprint* InBlueprint);` — When a new anim notify blueprint is created, this will handle post creation work such as adding non-event default nodes
- L597 _private prototype_ `void HandleNewAnimNotifyStateBlueprintCreated(UBlueprint* InBlueprint);` — When a new anim notify state blueprint is created, this will handle post creation work such as adding non-event default nodes
- L609 _private prototype_ `static TSharedRef< SWidget > GenerateCreateAssetMenu(TWeakPtr<IPersonaToolkit> InWeakPersonaToolkit);`
- L611 _private prototype_ `static void FillCreateAnimationMenu(FMenuBuilder& MenuBuilder, TWeakPtr<IPersonaToolkit> InWeakPersonaToolkit);`
- L613 _private prototype_ `static void FillCreateAnimationFromCurrentAnimationMenu(FMenuBuilder& MenuBuilder, TWeakPtr<IPersonaToolkit> InWeakPersonaToolkit);`
- L615 _private prototype_ `static void FillCreatePoseAssetMenu(FMenuBuilder& MenuBuilder, TWeakPtr<IPersonaToolkit> InWeakPersonaToolkit);`
- L617 _private prototype_ `static void FillInsertPoseMenu(FMenuBuilder& MenuBuilder, TWeakPtr<IPersonaToolkit> InWeakPersonaToolkit);`
- L619 _private prototype_ `static void InsertCurrentPoseToAsset(const FAssetData& NewPoseAssetData, TWeakPtr<IPersonaToolkit> InWeakPersonaToolkit);`
- L621 _private prototype_ `static bool CreateAnimation(const TArray<UObject*> NewAssets, const EPoseSourceOption Option, TWeakPtr<IPersonaToolkit> InWeakPersonaToolkit);`
- L623 _private prototype_ `static bool CreatePoseAsset(const TArray<UObject*> NewAssets, const EPoseSourceOption Option, TWeakPtr<IPersonaToolkit> InWeakPersonaToolkit);`
- L625 _private prototype_ `static bool HandleAssetCreated(const TArray<UObject*> NewAssets);`
- L627 _private prototype_ `void RegisterToolMenuExtensions();`
- L629 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L630 _private member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L631 _private member_ `TArray<FOnCustomizeMeshDetails> CustomizeMeshDetailLayoutDelegates;`
- L634 _private member_ `FIsRecordingActive IsRecordingActiveDelegate;` — Delegate used to query whether recording is active
- L637 _private member_ `FRecord RecordDelegate;` — Delegate used to start recording animation
- L640 _private member_ `FStopRecording StopRecordingDelegate;` — Delegate used to stop recording animation
- L643 _private member_ `FGetCurrentRecording GetCurrentRecordingDelegate;` — Delegate used to get the currently recording animation
- L646 _private member_ `FGetCurrentRecordingTime GetCurrentRecordingTimeDelegate;` — Delegate used to get the currently recording animation time
- L649 _private member_ `FTickRecording TickRecordingDelegate;` — Delegate used to tick the skelmesh component recording
- L652 _private member_ `FOnPreviewSceneCreated OnPreviewSceneCreatedDelegate;` — Delegate broadcast when a preview scene is created
- L655 _private member_ `FOnRegisterLayoutExtensions OnRegisterLayoutExtensionsDelegate;` — Delegate broadcast to register common layout extensions
- L658 _private member_ `FOnRegisterTabs OnRegisterTabsDelegate;` — Delegate broadcast to register common tabs
- L661 _private member_ `TMap<FTopLevelAssetPath, FNotifyHostAssetParameters> NotifyHostParameters;` — Parameters for notify hosts
- L664 _private member_ `uint32 NotifyHostAssetVersion = 0;` — Version counter for NotifyHostParameters

#### struct `FPersonaModule::FCommonToolMenuExtensionArgs`  
`struct FCommonToolMenuExtensionArgs`  
_L500-520_
- desc: Settings for AddCommonToolbarExtensions
- L502 _public function_ `FCommonToolMenuExtensionArgs() : bPreviewMesh(true) , bPreviewAnimation(true) , bReferencePose(false) , bCreateAsset(true)`
- L510 _public member_ `bool bPreviewMesh;` — Adds a shortcut to setup a preview mesh to override the current display
- L513 _public member_ `bool bPreviewAnimation;` — Adds a shortcut to setup a preview animation to override the current display
- L516 _public member_ `bool bReferencePose;` — Adds a shortcut to set the character back to reference pose (also clears all bone modifications)
- L519 _public member_ `bool bCreateAsset;` — Adds a combo menu to allow other anim assets to be created

#### struct `FPersonaModule::FNotifyHostAssetParameters`  
`struct FNotifyHostAssetParameters`  
_L556-565_
- desc: Struct allowing the anim notify system to interact with an asset type
- L559 _public typedef_ `using FOnReplaceNotify = TDelegate<void(UObject* InAsset, const FString& InFindString, const FString& InReplaceString, bool bFindWholeWord, ESearchCase::Type InSearchCase)>;` — Delegate called to replace a notify event with another
- L560 _public member_ `FOnReplaceNotify OnReplaceNotify;`
- L563 _public typedef_ `using FOnRemoveNotify = TDelegate<void(UObject* InAsset, const FString& InFindString, bool bFindWholeWord, ESearchCase::Type InSearchCase)>;` — Delegate called to remove a notify event
- L564 _public member_ `FOnRemoveNotify OnRemoveNotify;`

#### enum `FPersonaModule::EPoseSourceOption`  
`enum class EPoseSourceOption : uint8`  
_L600-607_
- desc: Options for asset creation
- L602 _public enumerator_ `ReferencePose`
- L603 _public enumerator_ `CurrentPose`
- L604 _public enumerator_ `CurrentAnimation_AnimData`
- L605 _public enumerator_ `CurrentAnimation_PreviewMesh`
- L606 _public enumerator_ `Max`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API PERSONA_API`
- L38 _externvar_ `extern const FName PersonaAppName;`
- L47 _delegate_ `DECLARE_DELEGATE_TwoParams(FIsRecordingActive, USkeletalMeshComponent* , bool& );`
- L47 _prototype_ `DECLARE_DELEGATE_TwoParams(FIsRecordingActive, USkeletalMeshComponent* , bool& );`
- L48 _delegate_ `DECLARE_DELEGATE_OneParam(FRecord, USkeletalMeshComponent* );`
- L48 _prototype_ `DECLARE_DELEGATE_OneParam(FRecord, USkeletalMeshComponent* );`
- L49 _delegate_ `DECLARE_DELEGATE_OneParam(FStopRecording, USkeletalMeshComponent* );`
- L49 _prototype_ `DECLARE_DELEGATE_OneParam(FStopRecording, USkeletalMeshComponent* );`
- L50 _delegate_ `DECLARE_DELEGATE_TwoParams(FGetCurrentRecording, USkeletalMeshComponent* , class UAnimSequence*& );`
- L50 _prototype_ `DECLARE_DELEGATE_TwoParams(FGetCurrentRecording, USkeletalMeshComponent* , class UAnimSequence*& );`
- L51 _delegate_ `DECLARE_DELEGATE_TwoParams(FGetCurrentRecordingTime, USkeletalMeshComponent* , float& );`
- L51 _prototype_ `DECLARE_DELEGATE_TwoParams(FGetCurrentRecordingTime, USkeletalMeshComponent* , float& );`
- L52 _delegate_ `DECLARE_DELEGATE_TwoParams(FTickRecording, USkeletalMeshComponent* , float );`
- L52 _prototype_ `DECLARE_DELEGATE_TwoParams(FTickRecording, USkeletalMeshComponent* , float );`
- L55 _delegate_ `DECLARE_DELEGATE_OneParam(FOnViewportCreated, const TSharedRef<class IPersonaViewport>&);` — Called back when a viewport is created
- L55 _prototype_ `DECLARE_DELEGATE_OneParam(FOnViewportCreated, const TSharedRef<class IPersonaViewport>&);` — Called back when a viewport is created
- L58 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDetailsCreated, const TSharedRef<IDetailsView>&);` — Called back when a details panel is created
- L58 _prototype_ `DECLARE_DELEGATE_OneParam(FOnDetailsCreated, const TSharedRef<IDetailsView>&);` — Called back when a details panel is created
- L61 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAnimationSequenceBrowserCreated, const TSharedRef<IAnimationSequenceBrowser>&);` — Called back when an anim sequence browser is created
- L61 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAnimationSequenceBrowserCreated, const TSharedRef<IAnimationSequenceBrowser>&);` — Called back when an anim sequence browser is created
- L64 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreviewSceneCreated, const TSharedRef<IPersonaPreviewScene>&);` — Called back when a Persona preview scene is created
- L64 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreviewSceneCreated, const TSharedRef<IPersonaPreviewScene>&);` — Called back when a Persona preview scene is created
- L67 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreviewSceneSettingsCustomized, IDetailLayoutBuilder& DetailBuilder);` — Called back when a Persona preview scene settings are customized
- L67 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreviewSceneSettingsCustomized, IDetailLayoutBuilder& DetailBuilder);` — Called back when a Persona preview scene settings are customized
- L70 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRegisterTabs, FWorkflowAllowedTabSet&, TSharedPtr<FAssetEditorToolkit>);` — Called back to register tabs
- L70 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRegisterTabs, FWorkflowAllowedTabSet&, TSharedPtr<FAssetEditorToolkit>);` — Called back to register tabs
- L73 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRegisterLayoutExtensions, FLayoutExtender&);` — Called back to register common layout extensions
- L73 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRegisterLayoutExtensions, FLayoutExtender&);` — Called back to register common layout extensions
- L188 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FOnGetViewportText, EViewportCorner );` — Delegate used to provide custom text for the viewport corners
- L188 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FOnGetViewportText, EViewportCorner );` — Delegate used to provide custom text for the viewport corners
- L190 _delegate_ `DECLARE_DELEGATE_RetVal(TOptional<bool>, FAnimationScrubPanel_IsRecordingActive);`
- L190 _prototype_ `DECLARE_DELEGATE_RetVal(TOptional<bool>, FAnimationScrubPanel_IsRecordingActive);`
- L191 _delegate_ `DECLARE_DELEGATE_RetVal(TOptional<EVisibility>, FAnimationScrubPanel_GetRecordingVisibility);`
- L191 _prototype_ `DECLARE_DELEGATE_RetVal(TOptional<EVisibility>, FAnimationScrubPanel_GetRecordingVisibility);`
- L192 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FAnimationScrubPanel_StartRecording) DECLARE_DELEGATE_RetVal(bool, FAnimationScrubPanel_StopRecording);`
- L192 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FAnimationScrubPanel_StartRecording) DECLARE_DELEGATE_RetVal(bool, FAnimationScrubPanel_StopRecording);`
- L193 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FAnimationScrubPanel_StopRecording);`
- L194 _delegate_ `DECLARE_DELEGATE_RetVal(TOptional<int32>, FAnimationScrubPanel_GetPlaybackMode);`
- L194 _prototype_ `DECLARE_DELEGATE_RetVal(TOptional<int32>, FAnimationScrubPanel_GetPlaybackMode);`
- L195 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FAnimationScrubPanel_SetPlaybackMode, int32 );`
- L195 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FAnimationScrubPanel_SetPlaybackMode, int32 );`
- L196 _delegate_ `DECLARE_DELEGATE_RetVal(TOptional<float>, FAnimationScrubPanel_GetPlaybackTime);`
- L196 _prototype_ `DECLARE_DELEGATE_RetVal(TOptional<float>, FAnimationScrubPanel_GetPlaybackTime);`
- L197 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FAnimationScrubPanel_SetPlaybackTime, float , bool );`
- L197 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FAnimationScrubPanel_SetPlaybackTime, float , bool );`
- L198 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FAnimationScrubPanel_StepForward);`
- L198 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FAnimationScrubPanel_StepForward);`
- L199 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FAnimationScrubPanel_StepBackward);`
- L199 _prototype_ `DECLARE_DELEGATE_RetVal(bool, FAnimationScrubPanel_StepBackward);`
- L200 _delegate_ `DECLARE_DELEGATE_RetVal(TOptional<bool>, FAnimationScrubPanel_GetIsLooping);`
- L200 _prototype_ `DECLARE_DELEGATE_RetVal(TOptional<bool>, FAnimationScrubPanel_GetIsLooping);`
- L201 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FAnimationScrubPanel_SetIsLooping, bool );`
- L201 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FAnimationScrubPanel_SetIsLooping, bool );`
- L202 _delegate_ `DECLARE_DELEGATE_RetVal(TOptional<FVector2f>, FAnimationScrubPanel_GetPlaybackTimeRange);`
- L202 _prototype_ `DECLARE_DELEGATE_RetVal(TOptional<FVector2f>, FAnimationScrubPanel_GetPlaybackTimeRange);`
- L203 _delegate_ `DECLARE_DELEGATE_RetVal(TOptional<uint32>, FAnimationScrubPanel_GetNumberOfKeys);`
- L203 _prototype_ `DECLARE_DELEGATE_RetVal(TOptional<uint32>, FAnimationScrubPanel_GetNumberOfKeys);`
- L496 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnCustomizeMeshDetails, IDetailLayoutBuilder& DetailLayout, TWeakObjectPtr<USkeletalMesh> SkeletalMesh);` — Delegates that allow customizing the mesh details layout and are called from within PersonaMeshDetails' CustomizeDetails().

### `Source/Editor/Persona/Public/PersonaPreviewSceneController.h` (Public)


#### class `UPersonaPreviewSceneController`  
`class UPersonaPreviewSceneController : public UObject`  
_L19-31_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Base class for preview scene controller (controls what the preview scene in persona does)
- L25 _public prototype_ `virtual void InitializeView(UPersonaPreviewSceneDescription* SceneDescription, IPersonaPreviewScene* PreviewScene) const PURE_VIRTUAL( UPersonaPreviewSceneController::InitializeView, );` — Called when this preview controller is activated
- L27 _public prototype_ `virtual void UninitializeView(UPersonaPreviewSceneDescription* SceneDescription, IPersonaPreviewScene* PreviewScene) const PURE_VIRTUAL(UPersonaPreviewSceneController::UninitializeView, );` — Called when this preview controller is deactivated
- L30 _public prototype_ `virtual IDetailPropertyRow* AddPreviewControllerPropertyToDetails(const TSharedRef<class IPersonaToolkit>& PersonaToolkit, IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& Category, const FProperty* Property, const EPropertyLocation::Type PropertyLocation);` — Called when populating the preview scene settings details panel to allow customization of the controllers properties

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API PERSONA_API`

### `Source/Editor/Persona/Public/PersonaSelectionProxies.h` (Public)


#### struct `HPersonaBoneHitProxy`  
`struct HPersonaBoneHitProxy : public HHitProxy`  
_L15-31_
- inherits: `HHitProxy`
- L17 _public prototype_ `DECLARE_HIT_PROXY( ) int32 BoneIndex;`
- L20 _public member_ `FName BoneName;`
- L22 _public function_ `HPersonaBoneHitProxy(int32 InBoneIndex, FName InBoneName) : HHitProxy(HPP_Foreground) , BoneIndex(InBoneIndex) , BoneName(InBoneName)`
- L29 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override` — HHitProxy interface

#### struct `HPersonaSocketHitProxy`  
`struct HPersonaSocketHitProxy : public HHitProxy`  
_L33-48_
- inherits: `HHitProxy`
- L35 _public prototype_ `DECLARE_HIT_PROXY( ) USkeletalMeshSocket* Socket;`
- L39 _public function_ `HPersonaSocketHitProxy(USkeletalMeshSocket* InSocket) : HHitProxy(HPP_Foreground)`
- L46 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override` — HHitProxy interface

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API PERSONA_API`

### `Source/Editor/Persona/Public/PersonaTabs.h` (Public)


#### struct `FPersonaTabs`  
`struct FPersonaTabs`  
_L10-57_
- desc: Tab constants
- L13 _public member_ `static const FName MorphTargetsID;` — Selection Details
- L14 _public member_ `static const FName AnimCurveViewID;`
- L15 _public member_ `static const FName AnimCurveMetadataEditorID;`
- L16 _public member_ `static const FName SkeletonTreeViewID;`
- L18 _public member_ `static const FName RetargetManagerID;` — Skeleton Pose manager
- L19 _public member_ `static const FName RigManagerID;`
- L24 _public member_ `static const FName AnimBlueprintPreviewEditorID;` — Skeleton/Sockets Anim Blueprint Params Explorer Class Defaults
- L25 _public member_ `static const FName AnimBlueprintParentPlayerEditorID;`
- L27 _public member_ `static const FName ScrubberID;` — Anim Document
- L29 _public member_ `static const FName PreviewViewportID;` — Toolbar
- L30 _public member_ `static const FName PreviewViewport1ID;`
- L31 _public member_ `static const FName PreviewViewport2ID;`
- L32 _public member_ `static const FName PreviewViewport3ID;`
- L33 _public member_ `static const FName AssetBrowserID;`
- L34 _public member_ `static const FName MirrorSetupID;`
- L35 _public member_ `static const FName AnimBlueprintDebugHistoryID;`
- L36 _public member_ `static const FName AnimAssetPropertiesID;`
- L37 _public member_ `static const FName MeshAssetPropertiesID;`
- L38 _public member_ `static const FName PreviewManagerID;`
- L39 _public member_ `static const FName SkeletonAnimNotifiesID;`
- L40 _public member_ `static const FName SkeletonSlotNamesID;`
- L41 _public member_ `static const FName SkeletonSlotGroupNamesID;`
- L42 _public member_ `static const FName CurveNameManagerID;`
- L43 _public member_ `static const FName BlendProfileManagerID;`
- L44 _public member_ `static const FName AnimMontageSectionsID;`
- L45 _public member_ `static const FName PoseWatchManagerID;`
- L48 _public member_ `static const FName AdvancedPreviewSceneSettingsID;` — Advanced Preview Scene
- L49 _public member_ `static const FName DetailsID;`
- L50 _public member_ `static const FName FindReplaceID;`
- L52 _public member_ `static const FName ToolboxID;`
- L54 _public member_ `static const FName AnimAttributeViewID;`
- L56 _private function_ `FPersonaTabs()`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API PERSONA_API`

### `Source/Editor/Persona/Public/PersonaToolMenuContext.h` (Public)


#### class `UPersonaToolMenuContext`  
`class UPersonaToolMenuContext : public UObject`  
_L25-60_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L32 _public prototype_ `USkeleton* GetSkeleton() const;` — `UFUNCTION(BlueprintCallable, Category = PersonaEditorExtensions)` — Get the skeleton that we are editing
- L36 _public prototype_ `UDebugSkelMeshComponent* GetPreviewMeshComponent() const;` — `UFUNCTION(BlueprintCallable, Category = PersonaEditorExtensions)` — Get the preview component that we are using
- L40 _public prototype_ `USkeletalMesh* GetMesh() const;` — `UFUNCTION(BlueprintCallable, Category = PersonaEditorExtensions)` — Get the skeletal mesh that we are editing
- L44 _public prototype_ `UAnimBlueprint* GetAnimBlueprint() const;` — `UFUNCTION(BlueprintCallable, Category = PersonaEditorExtensions)` — Get the anim blueprint that we are editing
- L48 _public prototype_ `UAnimationAsset* GetAnimationAsset() const;` — `UFUNCTION(BlueprintCallable, Category = PersonaEditorExtensions)` — Get the animation asset that we are editing
- L51 _public prototype_ `void SetToolkit(TSharedRef<IPersonaToolkit> InToolkit);` — Get the persona toolkit
- L54 _public function_ `TWeakPtr<IPersonaToolkit> GetToolkit() const` — Get a weak ptr to the persona toolkit
- L57 _protected prototype_ `bool HasValidToolkit() const;`
- L59 _private member_ `TWeakPtr<IPersonaToolkit> WeakToolkit;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API PERSONA_API`

### `Source/Editor/Persona/Public/PersonaUtils.h` (Public)


#### enum `PersonaUtils::ECopyOptions`  
`enum ECopyOptions : int32`  
_L22-38_
- desc: Options for CopyPropertiesToCDO
- L25 _public enumerator_ `Default = 0` — Default copy options
- L28 _public enumerator_ `PreviewOnly = 1 << 0` — Set this option to preview the changes and not actually copy anything.  This will count the number of properties that would be copied.
- L31 _public enumerator_ `CallPostEditChangeProperty = 1 << 1` — Call PostEditChangeProperty for each modified property
- L34 _public enumerator_ `OnlyCopyEditOrInterpProperties = 1 << 2` — Copy only Edit and Interp properties.  Otherwise we copy all properties by default
- L37 _public enumerator_ `FilterBlueprintReadOnly = 1 << 3` — Filters out Blueprint Read-only properties

#### struct `PersonaUtils::FCopyOptions`  
`struct FCopyOptions`  
_L41-57_
- desc: Copy options structure for CopyPropertiesToCDO
- L44 _public function_ `FCopyOptions(const ECopyOptions InFlags) : Flags(InFlags)` — Implicit construction for an options enumeration
- L47 _public function_ `bool CanCopyProperty(FProperty& Property, UObject& Object) const` — Check whether we can copy the specified property
- L53 _public member_ `ECopyOptions Flags;` — User-specified flags for the copy
- L56 _public member_ `TFunction<bool(FProperty&, UObject&)> PropertyFilter;` — User-specified custom property filter predicate

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace PersonaUtils`
- L19 _prototype_ `USceneComponent* GetComponentForAttachedObject(USceneComponent* PreviewComponent, class UObject* Object, const FName& AttachedTo);` (scope `PersonaUtils`) — Get the viewport scene component for the specified attached asset
- L60 _prototype_ `int32 CopyPropertiesToCDO(UAnimInstance* InAnimInstance, const FCopyOptions& Options = FCopyOptions(ECopyOptions::Default));` (scope `PersonaUtils`) — Copy modified properties from the specified anim instance back to its CDO
- L63 _prototype_ `void SetObjectBeingDebugged(UAnimBlueprint* InAnimBlueprint, UAnimInstance* InAnimInstance);` (scope `PersonaUtils`) — Set the correct object to debug depending on whether we are running a sub-layer etc.
- L66 _prototype_ `TSharedRef<SWidget> MakeTrackButton(FText HoverText, FOnGetContent MenuContent, const TAttribute<bool>& HoverState);` (scope `PersonaUtils`) — Make an add button widget, as seen in the animation timeline
- L69 _prototype_ `TSharedRef<SWidget> MakeAnimNotifyPicker(UAnimSequenceBase* Sequence, const FOnClassPicked& OnClassPicked);` (scope `PersonaUtils`) — Make AnimNotify class picker widget
- L72 _prototype_ `TSharedRef<SWidget> MakeAnimNotifyStatePicker(UAnimSequenceBase* Sequence, const FOnClassPicked& OnClassPicked);` (scope `PersonaUtils`) — Make AnimNotifyState class picker widget

### `Source/Editor/Persona/Public/PhysicsAssetRenderUtils.h` (Public)


#### struct `FPhysicsAssetRenderSettings`  
`struct FPhysicsAssetRenderSettings`  
_L36-165_
- reflection: `USTRUCT()`
- desc: Per Physics Asset parameters that determine how debug draw functions should render that asset in an editor viewport. These parameters are used across different editor modes to ensure the debug draw is consistent. This makes it easier to create or debug physics assets whilst switching between editor modes.
- L42 _public prototype_ `FPhysicsAssetRenderSettings();`
- L43 _public prototype_ `void InitPhysicsAssetRenderSettings(class UMaterialInterface* InBoneUnselectedMaterial, class UMaterialInterface* InBoneNoCollisionMaterial);`
- L46 _public prototype_ `bool IsBodyHidden(const int32 BodyIndex) const;` — Accessors/helper methods
- L47 _public prototype_ `bool IsConstraintHidden(const int32 ConstraintIndex) const;`
- L48 _public prototype_ `bool AreAnyBodiesHidden() const;`
- L49 _public prototype_ `bool AreAnyConstraintsHidden() const;`
- L50 _public prototype_ `void HideBody(const int32 BodyIndex);`
- L51 _public prototype_ `void ShowBody(const int32 BodyIndex);`
- L52 _public prototype_ `void HideConstraint(const int32 ConstraintIndex);`
- L53 _public prototype_ `void ShowConstraint(const int32 ConstraintIndex);`
- L54 _public prototype_ `void ShowAllBodies();`
- L55 _public prototype_ `void ShowAllConstraints();`
- L56 _public prototype_ `void ShowAll();`
- L57 _public prototype_ `void HideAllBodies(const UPhysicsAsset* const PhysicsAsset);`
- L58 _public prototype_ `void HideAllConstraints(const UPhysicsAsset* const PhysicsAsset);`
- L59 _public prototype_ `void HideAll(const UPhysicsAsset* const PhysicsAsset);`
- L60 _public prototype_ `void ToggleShowBody(const int32 BodyIndex);`
- L61 _public prototype_ `void ToggleShowConstraint(const int32 ConstraintIndex);`
- L62 _public prototype_ `void ToggleShowAllBodies(const UPhysicsAsset* const PhysicsAsset);`
- L63 _public prototype_ `void ToggleShowAllConstraints(const UPhysicsAsset* const PhysicsAsset);`
- L65 _public prototype_ `void SetHiddenBodies(const TArray<int32>& InHiddenBodies);`
- L66 _public prototype_ `void SetHiddenConstraints(const TArray<int32>& InHiddenConstraints);`
- L69 _public prototype_ `EConstraintTransformComponentFlags GetConstraintViewportManipulationFlags() const;` — Returns a set of flags describing which components of the selected constraint's transforms are being manipulated in the view port.
- L72 _public prototype_ `bool IsDisplayingConstraintTransformComponentRelativeToDefault(const EConstraintTransformComponentFlags ComponentFlags) const;` — Returns true if all the constraint transform components specified by the flags should be displayed as an offset from the default (snapped) transforms.
- L75 _public prototype_ `void SetDisplayConstraintTransformComponentRelativeToDefault(const EConstraintTransformComponentFlags ComponentFlags, const bool bShouldDisplayRelativeToDefault);` — Set how the constraint transform components specified by the flags should be displayed, in the frame of their associated physics body (false) or as an offset from the default (snapped) transforms (true).
- L77 _public prototype_ `void ResetEditorViewportOptions();`
- L81 _public member_ `EPhysicsAssetEditorCenterOfMassViewMode CenterOfMassViewMode;` — `UPROPERTY()` — Physics Asset Editor Viewport Options
- L84 _public member_ `EPhysicsAssetEditorCollisionViewMode CollisionViewMode;` — `UPROPERTY()`
- L87 _public member_ `EPhysicsAssetEditorConstraintViewMode ConstraintViewMode;` — `UPROPERTY()`
- L91 _public member_ `EConstraintTransformComponentFlags ConstraintViewportManipulationFlags;` — `UPROPERTY(Transient)` — Flags that determine which parts of the constraints transforms (parent frame, child frame, position and rotation) are currently begin manipulated in the viewport.
- L95 _public member_ `EConstraintTransformComponentFlags ConstraintTransformComponentDisplayRelativeToDefaultFlags;` — `UPROPERTY()` — Flags that determine which parts of the constraints transforms (parent/child position/rotation) should be displayed as an offset from the default (snapped) transforms.
- L98 _public member_ `float ConstraintDrawSize;` — `UPROPERTY()`
- L101 _public member_ `float PhysicsBlend;` — `UPROPERTY()`
- L104 _public member_ `bool bHideKinematicBodies;` — `UPROPERTY()`
- L107 _public member_ `bool bHideSimulatedBodies;` — `UPROPERTY()`
- L110 _public member_ `bool bHideBodyMass;` — `UPROPERTY()`
- L113 _public member_ `bool bRenderOnlySelectedConstraints;` — `UPROPERTY()`
- L116 _public member_ `bool bShowCOM_DEPRECATED;` — `UPROPERTY()`
- L119 _public member_ `bool bShowConstraintsAsPoints;` — `UPROPERTY()`
- L122 _public member_ `bool bHighlightOverlapingBodies;` — `UPROPERTY()`
- L125 _public member_ `bool bDrawViolatedLimits;` — `UPROPERTY()`
- L128 _public member_ `bool bHideCenterOfMassForKinematicBodies;` — `UPROPERTY()`
- L132 _public member_ `FColor BoneUnselectedColor;` — `UPROPERTY()` — Draw colors
- L135 _public member_ `FColor NoCollisionColor;` — `UPROPERTY()`
- L138 _public member_ `FColor COMRenderColor;` — `UPROPERTY()`
- L141 _public member_ `float COMRenderSize;` — `UPROPERTY()`
- L144 _public member_ `float COMRenderLineThickness;` — `UPROPERTY()`
- L147 _public member_ `float COMRenderMassTextOffsetScreenspace;` — `UPROPERTY()`
- L150 _public member_ `float InfluenceLineLength;` — `UPROPERTY()`
- L154 _public member_ `TObjectPtr<class UMaterialInterface> BoneUnselectedMaterial;` — `UPROPERTY()` — Materials
- L157 _public member_ `TObjectPtr<class UMaterialInterface> BoneNoCollisionMaterial;` — `UPROPERTY()`
- L160 _public member_ `TArray<int32> HiddenBodies;` — `UPROPERTY()`
- L163 _public member_ `TArray<int32> HiddenConstraints;` — `UPROPERTY()`

#### class `UPhysicsAssetRenderUtilities`  
`class UPhysicsAssetRenderUtilities : public UObject`  
_L172-209_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Factory class for FPhysicsAssetRenderSettings.
- L178 _public prototype_ `UPhysicsAssetRenderUtilities();`
- L179 _public prototype_ `virtual ~UPhysicsAssetRenderUtilities();`
- L181 _public prototype_ `static void Initialise();`
- L184 _public prototype_ `static FPhysicsAssetRenderSettings* GetSettings(const UPhysicsAsset* InPhysicsAsset);` — Returns an existing render settings object or creates and returns a new one if none exists.
- L185 _public prototype_ `static FPhysicsAssetRenderSettings* GetSettings(const FString& InPhysicsAssetPathName);`
- L186 _public prototype_ `static FPhysicsAssetRenderSettings* GetSettings(const uint32 InPhysicsAssetPathNameHash);`
- L188 _public prototype_ `static uint32 GetPathNameHash(const UPhysicsAsset* InPhysicsAsset);`
- L189 _public prototype_ `static uint32 GetPathNameHash(const FString& InPhysicsAssetPathName);`
- L191 _public prototype_ `void OnAssetRenamed(FAssetData const& AssetInfo, const FString& InOldPhysicsAssetPathName);`
- L192 _public prototype_ `void OnAssetRemoved(UObject* Object);`
- L196 _private prototype_ `void InitialiseImpl();`
- L197 _private prototype_ `FPhysicsAssetRenderSettings* GetSettingsImpl(const uint32 InPhysicsAssetPathNameHash);`
- L200 _private member_ `TMap< uint32, FPhysicsAssetRenderSettings > IdToSettingsMap;` — `UPROPERTY()`
- L203 _private member_ `TObjectPtr<class UMaterialInterface> BoneUnselectedMaterial;` — `UPROPERTY(transient)`
- L206 _private member_ `TObjectPtr<class UMaterialInterface> BoneNoCollisionMaterial;` — `UPROPERTY(transient)`
- L208 _private member_ `IPhysicsAssetRenderInterface* PhysicsAssetRenderInterface;`

#### class `FPhysicsAssetRenderInterface`  
`class FPhysicsAssetRenderInterface : public IPhysicsAssetRenderInterface`  
_L245-267_
- inherits: `IPhysicsAssetRenderInterface`
- L248 _public prototype_ `virtual void DebugDraw(USkeletalMeshComponent* const SkeletalMeshComponent, UPhysicsAsset* const PhysicsAsset, FPrimitiveDrawInterface* PDI) override;`
- L249 _public prototype_ `virtual void DebugDrawBodies(USkeletalMeshComponent* const SkeletalMeshComponent, UPhysicsAsset* const PhysicsAsset, FPrimitiveDrawInterface* PDI, const FColor& PrimitiveColorOverride) override;`
- L250 _public prototype_ `virtual void DebugDrawConstraints(USkeletalMeshComponent* const SkeletalMeshComponent, UPhysicsAsset* const PhysicsAsset, FPrimitiveDrawInterface* PDI) override;`
- L252 _public prototype_ `virtual void SaveConfig() override;`
- L254 _public prototype_ `virtual void ToggleShowAllBodies(UPhysicsAsset* const PhysicsAsset) override;`
- L255 _public prototype_ `virtual void ToggleShowAllConstraints(UPhysicsAsset* const PhysicsAsset) override;`
- L256 _public prototype_ `virtual bool AreAnyBodiesHidden(UPhysicsAsset* const PhysicsAsset) override;`
- L257 _public prototype_ `virtual bool AreAnyConstraintsHidden(UPhysicsAsset* const PhysicsAsset) override;`
- L260 _public prototype_ `virtual EConstraintTransformComponentFlags GetConstraintViewportManipulationFlags(class UPhysicsAsset* const PhysicsAsset) override;` — Returns a set of flags describing which components of the selected constraint's transforms are being manipulated in the viewport.
- L263 _public prototype_ `virtual bool IsDisplayingConstraintTransformComponentRelativeToDefault(class UPhysicsAsset* const PhysicsAsset, const EConstraintTransformComponentFlags ComponentFlags) override;` — Returns true if the constraint transform component specified by the flags should be displayed as an offset from the default (snapped) transforms.
- L266 _public prototype_ `virtual void SetDisplayConstraintTransformComponentRelativeToDefault(class UPhysicsAsset* const PhysicsAsset, const EConstraintTransformComponentFlags ComponentFlags, const bool bShouldDisplayRelativeToDefault) override;` — Change how the constraint transform component specified by the flags should be displayed, in the frame of their associated physics body or as an offset from the default (snapped) transforms.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API PERSONA_API`
- L217 _namespace_ `namespace PhysicsAssetRender`
- L219 _typedef_ `template< typename TReturnType > using GetPrimitiveRef = TFunctionRef< TReturnType (const int32 BodyIndex, const EAggCollisionShape::Type PrimitiveType, const int32 PrimitiveIndex, const FPhysicsAssetRenderSettings& Settings) >;` (scope `PhysicsAssetRender`)
- L220 _typedef_ `template< typename TReturnType > using GetPrimitiveRef = TFunctionRef< TReturnType (const int32 BodyIndex, const EAggCollisionShape::Type PrimitiveType, const int32 PrimitiveIndex, const FPhysicsAssetRenderSettings& Settings) >;` (scope `PhysicsAssetRender`)
- L221 _typedef_ `using CreateBodyHitProxyFn = TFunctionRef< HHitProxy* (const int32 BodyIndex, const EAggCollisionShape::Type PrimitiveType, const int32 PrimitiveIndex) >;` (scope `PhysicsAssetRender`)
- L222 _typedef_ `using CreateConstraintHitProxyFn = TFunctionRef< HHitProxy* (const int32 InConstraintIndex) >;` (scope `PhysicsAssetRender`)
- L223 _typedef_ `using CreateCoMHitProxyFn = TFunctionRef< HHitProxy* (const int32 InBodyIndex) >;` (scope `PhysicsAssetRender`)
- L224 _typedef_ `using COMAccessorFunctionFn = TFunctionRef< TPair< bool, FVector >(const int32) >;` (scope `PhysicsAssetRender`)
- L225 _typedef_ `using IsSelectedFn = TFunction< bool(const uint32) >;` (scope `PhysicsAssetRender`)
- L228 _prototype_ `void DebugDraw(class USkeletalMeshComponent* const SkeletalMeshComponent, class UPhysicsAsset* const PhysicsAsset, FPrimitiveDrawInterface* PDI);` (scope `PhysicsAssetRender`) — Debug draw Physics Asset bodies and constraints using the default callbacks
- L231 _prototype_ `void DebugDrawBodies(class USkeletalMeshComponent* const SkeletalMeshComponent, class UPhysicsAsset* const PhysicsAsset, FPrimitiveDrawInterface* PDI, GetPrimitiveRef< FColor > GetPrimitiveColor, GetPrimitiveRef< class UMaterialInterface* > GetPrimitiveMaterial, GetPrimitiveTransformRef GetPrimitiveTransform, CreateBodyHitProxyFn CreateHitProxy);` (scope `PhysicsAssetRender`) — Debug draw Physics Asset bodies using the supplied custom callbacks
- L234 _prototype_ `void DebugDrawCenterOfMass(USkeletalMeshComponent* const SkeletalMeshComponent, class UPhysicsAsset* const PhysicsAsset, FPrimitiveDrawInterface* PDI, TFunctionRef< FVector(const uint32) > GetCoMPosition, TFunctionRef< bool(const uint32) > IsSelected, TFunctionRef< bool(const uint32) > IsHidden, CreateCoMHitProxyFn CreateHitProxy);` (scope `PhysicsAssetRender`) — Debug draw the Center of Masses for all bodies in the supplied Skeletal Mesh
- L237 _prototype_ `void DebugDrawConstraints(class USkeletalMeshComponent* const SkeletalMeshComponent, class UPhysicsAsset* const PhysicsAsset, FPrimitiveDrawInterface* PDI, IsSelectedFn IsSelected, const bool bRunningSimulation, CreateConstraintHitProxyFn CreateHitProxy);` (scope `PhysicsAssetRender`) — Debug draw Physics Asset constraints using the supplied custom callbacks
- L240 _prototype_ `FTransform GetPrimitiveTransform(const UPhysicsAsset* PhysicsAsset, const FTransform& BoneTM, const int32 BodyIndex, const EAggCollisionShape::Type PrimType, const int32 PrimIndex, const float Scale);` (scope `PhysicsAssetRender`) — Default callbacks used by DebugDraw
- L241 _prototype_ `FColor GetPrimitiveColor(const int32 BodyIndex, const EAggCollisionShape::Type PrimitiveType, const int32 PrimitiveIndex, const FPhysicsAssetRenderSettings& Settings);` (scope `PhysicsAssetRender`)
- L242 _prototype_ `class UMaterialInterface* GetPrimitiveMaterial(const int32 BodyIndex, const EAggCollisionShape::Type PrimitiveType, const int32 PrimitiveIndex, const FPhysicsAssetRenderSettings& Settings);` (scope `PhysicsAssetRender`)
- L269 _prototype_ `bool IsBodyKinematic(const UPhysicsAsset* const PhysicsAsset, const int32 BodyIndex);` — TODO - where is the best place for this fn to live ?

### `Source/Editor/Persona/Public/ReferenceSectionSelectionWidget.h` (Public)


#### class `SReferenceSectionSelectionWidget`  
`class SReferenceSectionSelectionWidget : public SCompoundWidget`  
_L26-80_
- inherits: `SCompoundWidget`
- L30 _public function_ `SLATE_BEGIN_ARGS(SReferenceSectionSelectionWidget) : _OnSectionSelectionChanged() , _OnGetSelectedSection() , _OnGetLodModel()`
- L37 _public prototype_ `SLATE_ARGUMENT(bool, bHideChunkedSections) SLATE_EVENT(FOnSectionSelectionChanged, OnSectionSelectionChanged);` — Should we hide chunked sections when showing the sections list we can select
- L43 _public prototype_ `SLATE_EVENT(FGetSelectedSection, OnGetSelectedSection);` — get selected section index
- L45 _public prototype_ `SLATE_EVENT(FGetLodModel, OnGetLodModel) SLATE_END_ARGS();`
- L54 _public prototype_ `void Construct( const FArguments& InArgs );` — Construct this widget @param	InArgs	The declaration data for this widget
- L59 _private prototype_ `TSharedRef<SWidget> CreateSectionListWidgetMenu();` — Creates the combo button menu when clicked
- L60 _private prototype_ `TSharedRef<ITableRow> MakeIntegerDisplayWidget(const TSharedPtr<int32> SectionIndex, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L62 _private member_ `TSharedPtr<SListView<TSharedPtr<int32>>> SectionListView;`
- L64 _private prototype_ `void OnSelectionChanged(TSharedPtr<int32> NewSectionIndex, ESelectInfo::Type SelectInfo);` — Called when the user selects a bone name
- L66 _private prototype_ `const TArray<TSharedPtr<int32>>* GetSections() const;`
- L68 _private prototype_ `FText GetCurrentSectionIndex() const;`
- L71 _private member_ `TSharedPtr<SComboButton> SectionPickerButton;` — Base combo button
- L74 _private member_ `FOnSectionSelectionChanged OnSectionSelectionChanged;` — delegates
- L75 _private member_ `FGetSelectedSection OnGetSelectedSection;`
- L76 _private member_ `FGetLodModel OnGetLodModel;`
- L78 _private member_ `bool bHideChunkedSections = false;`
- L79 _private member_ `mutable TArray<TSharedPtr<int32>> CacheSectionList;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API PERSONA_API`
- L22 _delegate_ `DECLARE_DELEGATE_OneParam(FOnSectionSelectionChanged, int32);`
- L22 _prototype_ `DECLARE_DELEGATE_OneParam(FOnSectionSelectionChanged, int32);`
- L23 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(int32, FGetSelectedSection, bool& );`
- L23 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(int32, FGetSelectedSection, bool& );`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal(const FSkeletalMeshLODModel&, FGetLodModel);`
- L24 _prototype_ `DECLARE_DELEGATE_RetVal(const FSkeletalMeshLODModel&, FGetLodModel);`

### `Source/Editor/Persona/Public/SAnimAttributeView.h` (Public)


#### class `FAnimAttributeEntry`  
`class FAnimAttributeEntry : public TSharedFromThis<FAnimAttributeEntry>`  
_L32-78_
- inherits: `TSharedFromThis<FAnimAttributeEntry>`
- L35 _public prototype_ `static TSharedRef<FAnimAttributeEntry> MakeEntry(const FAnimationAttributeIdentifier& InIdentifier, const FName& InSnapshotDisplayName);`
- L37 _public prototype_ `FAnimAttributeEntry() = default;`
- L38 _public prototype_ `FAnimAttributeEntry(const FAnimationAttributeIdentifier& InIdentifier, const FName& InSnapshotDisplayName);`
- L40 _public prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(const TSharedRef<STableViewBase>& InOwnerTable);`
- L42 _public function_ `FName GetName() const`
- L43 _public function_ `FName GetBoneName() const`
- L44 _public function_ `int32 GetBoneIndex() const`
- L45 _public function_ `FName GetTypeName() const`
- L46 _public function_ `UScriptStruct* GetScriptStruct() const`
- L47 _public function_ `FName GetSnapshotDisplayName() const`
- L49 _public prototype_ `FName GetDisplayName() const;`
- L51 _public function_ `UE::Anim::FAttributeId GetAttributeId() const`
- L56 _public function_ `const FAnimationAttributeIdentifier& GetAnimationAttributeIdentifier() const`
- L61 _public function_ `bool operator==(const FAnimAttributeEntry& InOther) const`
- L66 _public function_ `bool operator!=(const FAnimAttributeEntry& InOther) const`
- L73 _private member_ `FAnimationAttributeIdentifier Identifier;`
- L75 _private member_ `FName SnapshotDisplayName;`
- L77 _private member_ `FName CachedTypeName;`

#### class `SAnimAttributeEntry`  
`class SAnimAttributeEntry : public SMultiColumnTableRow<TSharedPtr<FAnimAttributeEntry>>`  
_L80-98_
- inherits: `SMultiColumnTableRow<TSharedPtr<FAnimAttributeEntry>>`
- L82 _private function_ `SLATE_BEGIN_ARGS( SAnimAttributeEntry )`
- L85 _private prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FAnimAttributeEntry> InEntry);`
- L90 _private prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L92 _private prototype_ `FText GetEntryName()const ;`
- L93 _private prototype_ `FText GetEntryBoneName() const;`
- L94 _private prototype_ `FText GetEntryTypeName() const;`
- L95 _private prototype_ `FText GetEntrySnapshotDisplayName() const;`
- L97 _private member_ `TWeakPtr<FAnimAttributeEntry> Entry;`

#### class `SAnimAttributeView`  
`class SAnimAttributeView : public SCompoundWidget`  
_L100-367_
- inherits: `SCompoundWidget`
- L103 _private prototype_ `static TSharedRef<IStructureDetailsView> CreateValueViewWidget();`
- L105 _private prototype_ `static TSharedRef<ITableRow> MakeTableRowWidget( TSharedPtr<FAnimAttributeEntry> InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L109 _private prototype_ `static FName GetSnapshotColumnDisplayName(const TArray<FName>& InSnapshotNames);`
- L112 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(FName, FOnGetAttributeSnapshotColumnDisplayName, const TArray<FName>& ) SLATE_BEGIN_ARGS( SAnimAttributeView ) : _SnapshotColumnLabelOverride(FText::FromString(TEXT("Direction")))`
- L118 _public prototype_ `SLATE_EVENT(FOnGetAttributeSnapshotColumnDisplayName, OnGetAttributeSnapshotColumnDisplayName)` — override what is displayed in the snapshot column, given a set of snapshots that contains the attribute
- L126 _public prototype_ `void Construct(const FArguments& InArgs);`
- L128 _public function_ `void DisplayNewAttributeContainerSnapshots( const TArray<TTuple<FName, const UE::Anim::FMeshAttributeContainer&>>& InSnapshots, const USkeletalMeshComponent* InOwningComponent)`
- L217 _public prototype_ `void ClearListView();`
- L219 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L224 _private function_ `template <typename ContainerType> bool ShouldInvalidateListViewCache( const TArray<TTuple<FName, const ContainerType&>>& InSnapshots, const USkeletalMeshComponent* InOwningComponent)`
- L290 _private prototype_ `void OnSelectionChanged(TSharedPtr<FAnimAttributeEntry> InEntry, ESelectInfo::Type InSelectType);`
- L292 _private prototype_ `void OnFilterTextChanged(const FText& InText);`
- L294 _private prototype_ `EColumnSortMode::Type GetSortModeForColumn(FName InColumnId) const;`
- L296 _private prototype_ `void OnSortAttributeEntries( EColumnSortPriority::Type InPriority, const FName& InColumnId, EColumnSortMode::Type InSortMode);`
- L301 _private prototype_ `void ExecuteSort();`
- L303 _private prototype_ `void RefreshFilteredAttributeEntries();`
- L305 _private prototype_ `void RefreshValueView();`
- L309 _private member_ `TSharedPtr<SListView<TSharedPtr<FAnimAttributeEntry>>> AttributeListView;` — list view
- L310 _private member_ `bool bShouldRefreshListView;`
- L312 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L314 _private member_ `FName ColumnIdToSort;`
- L315 _private member_ `EColumnSortMode::Type ActiveSortMode;`
- L316 _private member_ `FOnGetAttributeSnapshotColumnDisplayName OnGetAttributeSnapshotColumnDisplayName;`
- L317 _private member_ `TAttribute<FText> SnapshotColumnLabelOverride;`
- L319 _private member_ `int32 CachedNumSnapshots;`
- L323 _private member_ `TArray<TTuple<FName, TArray<FAnimationAttributeIdentifier>>> CachedAttributeIdentifierLists;` — cache all attributes in the attribute container that the list view is observing such that we can use it to detect if a change to the attribute container occured and refresh the list accordingly
- L326 _private member_ `TMap<FAnimationAttributeIdentifier, TArray<FName>> CachedAttributeSnapshotMap;` — for each attribute, save the name of the attribute container snapshot that contains it
- L328 _private member_ `TMap<FName, int32> CachedSnapshotNameIndexMap;`
- L331 _private member_ `TArray<TSharedPtr<FAnimAttributeEntry>> FilteredAttributeEntries;` — attributes to be displayed
- L333 _private member_ `FString FilterText;`
- L337 _private member_ `TSharedPtr<SScrollBox> ValueViewBox;` — value view
- L338 _private member_ `bool bShouldRefreshValueView;`
- L339 _private member_ `TOptional<FAnimAttributeEntry> SelectedAttribute;`
- L366 _private member_ `TArray<FAttributeValueView> SelectedAttributeSnapshotValueViews;`
- L370 _function_ `inline void SAnimAttributeView::ClearListView()`

#### struct `SAnimAttributeView::FAttributeValueView`  
`struct FAttributeValueView`  
_L341-364_
- L343 _public prototype_ `FAttributeValueView(FName InSnapshotName, const FAnimAttributeEntry& InSelectedAttribute);`
- L346 _public function_ `template<typename ContainerType> void UpdateValue(const ContainerType& InAttributeContainer) const`
- L360 _public member_ `FAnimAttributeEntry SubjectAttribute;`
- L361 _public member_ `FName SnapshotName;`
- L362 _public member_ `TSharedPtr<FStructOnScope> StructData;`
- L363 _public member_ `TSharedPtr<IStructureDetailsView> ViewWidget;`

#### class `SAnimAttributeViewer`  
`class SAnimAttributeViewer : public SCompoundWidget`  
_L381-398_
- inherits: `SCompoundWidget`
- L383 _private function_ `SLATE_BEGIN_ARGS( SAnimAttributeViewer )`
- L384 _private prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs, const TSharedRef<class IPersonaPreviewScene>& InPreviewScene);`
- L387 _private prototype_ `virtual ~SAnimAttributeViewer() override = default;`
- L388 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L391 _protected prototype_ `UAnimInstance* GetAnimInstance() const;`
- L394 _protected member_ `TWeakPtr<class IPersonaPreviewScene> PreviewScenePtr;` — Pointer to the preview scene we are bound to
- L396 _protected member_ `TSharedPtr<SAnimAttributeView> AttributeView;`
- L397 _protected member_ `TSharedPtr<SPoseWatchPicker> PoseWatchPicker;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API PERSONA_API`
- L26 _namespace_ `namespace EColumnSortMode`
- L112 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FName, FOnGetAttributeSnapshotColumnDisplayName, const TArray<FName>& ) SLATE_BEGIN_ARGS( SAnimAttributeView ) : _SnapshotColumnLabelOverride(FText::FromString(TEXT("Direction"))) {}`

### `Source/Editor/Persona/Public/SAnimNotifyNode.h` (Public)


#### class `SAnimNotifyNode`  
`class SAnimNotifyNode : public SLeafWidget`  
_L36-229_
- inherits: `SLeafWidget`
- L39 _public function_ `SLATE_BEGIN_ARGS(SAnimNotifyNode)`
- L40 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Declaration);`
- L45 _public prototype_ `void SetSequence(class UAnimSequenceBase* InSequence);` — Set the owning Sequence
- L48 _public prototype_ `void SetAnimNotify(FAnimNotifyEvent* InAnimNotifyEvent);` — Set the owning Anim Notify Event
- L51 _public prototype_ `void SetAnimSyncMarker(FAnimSyncMarker* InMarker);` — Set the AnimSyncMarker
- L54 _public prototype_ `void SetOnNotifyNodeDragStarted(FOnNotifyNodeDragStarted InDragStarted);` — Set event when Drag Started
- L57 _public prototype_ `void SetOnNotifyStateHandleBeingDragged(FOnNotifyStateHandleBeingDragged InHandleBeingDragged);` — Set event when notify state handle being dragged
- L60 _public prototype_ `void SetOnUpdatePanel(FOnUpdatePanel InOnUpdatePanel);` — Set event when update panel
- L63 _public prototype_ `void SetPanTrackRequest(FPanTrackRequest InPanTrackRequest);` — Set event when pan track request
- L66 _public prototype_ `void SetOnTrackSelectionChanged(FOnTrackSelectionChanged InOnTrackSelectionChanged);` — Set event when track selection changes
- L69 _public prototype_ `void SetViewInputMin(TAttribute<float> InViewInputMin);` — Set the view input min
- L72 _public prototype_ `void SetViewInputMax(TAttribute<float> InViewInputMax);` — Set the view input max
- L75 _public prototype_ `void SetStateEndTimingNode(TSharedPtr<SAnimTimingNode> InStateEndTimingNode);` — Set the state end timing node
- L78 _public prototype_ `void SetOnSnapPosition(FOnSnapPosition InOnSnapPosition);` — Set event when snapping position
- L81 _public prototype_ `virtual FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — SWidget interface
- L82 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L83 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L84 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L85 _public prototype_ `virtual void OnFocusLost(const FFocusEvent& InFocusEvent) override;`
- L86 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L87 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L91 _public prototype_ `void UpdateSizeAndPosition(const FGeometry& AllottedGeometry);` — SNodePanel::SNode interface
- L92 _public prototype_ `FVector2D GetWidgetPosition() const;`
- L93 _public prototype_ `FVector2D GetNotifyPosition() const;`
- L94 _public prototype_ `FVector2D GetNotifyPositionOffset() const;`
- L95 _public prototype_ `FVector2D GetSize() const;`
- L96 _public prototype_ `bool HitTest(const FGeometry& AllottedGeometry, FVector2D MouseLocalPose) const;`
- L99 _public prototype_ `ENotifyStateHandleHit::Type DurationHandleHitTest(const FVector2D& CursorScreenPosition) const;` — Extra hit testing to decide whether or not the duration handles were hit on a state node
- L101 _public prototype_ `UObject* GetObjectBeingDisplayed() const;`
- L104 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L105 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const ;`
- L108 _public prototype_ `void DrawHandleOffset(const float& Offset, const float& HandleCentre, FSlateWindowElementList& OutDrawElements, int32 MarkerLayer, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FLinearColor NodeColour) const;` — Helpers to draw scrub handles and snap offsets
- L109 _public prototype_ `void DrawScrubHandle(float ScrubHandleCentre, FSlateWindowElementList& OutDrawElements, int32 ScrubHandleID, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FLinearColor NodeColour) const;`
- L111 _public prototype_ `FLinearColor GetNotifyColor() const;`
- L112 _public prototype_ `FText GetNotifyText() const;`
- L115 _public member_ `INotifyNodeObjectInterface* NodeObjectInterface;` — Node object interface
- L118 _public member_ `uint8 NodeObjectInterfaceStorage[MAX_NOTIFY_NODE_OBJECT_INTERFACE_SIZE];` — In object storage for our interface struct, saves us having to dynamically allocate what will be a very small struct
- L122 _public function_ `template<typename InterfaceType, typename ParamType> void MakeNodeInterface(ParamType& InParam)` — Helper function to create our node interface object
- L128 _public prototype_ `void DropCancelled();`
- L131 _public function_ `float GetDurationSize() const` — Returns the size of this notifies duration in screen space
- L134 _public function_ `void SetLastMouseDownPosition(const FVector2D& CursorPosition)` — Sets the position the mouse was at when this node was last hit
- L137 _public member_ `static const float MinimumStateDuration;` — The minimum possible duration that a notify state can have
- L139 _public function_ `const FVector2D& GetScreenPosition() const`
- L144 _public function_ `const float GetLastSnappedTime() const`
- L149 _public function_ `void ClearLastSnappedTime()`
- L154 _public function_ `void SetLastSnappedTime(float NewSnapTime)`
- L160 _private prototype_ `FText GetNodeTooltip() const;`
- L163 _private prototype_ `float HandleOverflowPan(const FVector2D& ScreenCursorPos, float TrackScreenSpaceXPosition, float TrackScreenSpaceMin, float TrackScreenSpaceMax);` — Detects any overflow on the anim notify track and requests a track pan
- L166 _private prototype_ `float GetScrubHandleSnapPosition(float NotifyInputX, ENotifyStateHandleHit::Type HandleToCheck, TOptional<EAnimEventTriggerOffsets::Type>& OffsetForSnap);` — Finds a snap position if possible for the provided scrub handle, if it is not possible, returns -1.0f
- L168 _private prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L172 _protected member_ `UAnimSequenceBase* Sequence;` — The sequence that the AnimNotifyEvent for Notify lives in
- L173 _protected member_ `FSlateFontInfo Font;`
- L175 _protected member_ `TAttribute<float> ViewInputMin;`
- L176 _protected member_ `TAttribute<float> ViewInputMax;`
- L177 _protected member_ `FVector2f CachedAllotedGeometrySize;`
- L178 _protected member_ `FVector2D ScreenPosition;`
- L179 _protected member_ `float LastSnappedTime;`
- L181 _protected member_ `bool bDrawTooltipToRight;`
- L182 _protected member_ `bool bBeingDragged;`
- L183 _protected member_ `bool bSelected;`
- L186 _protected member_ `int32 DragMarkerTransactionIdx;` — Index for undo transactions for dragging, as a check to make sure it's active
- L189 _protected member_ `ENotifyStateHandleHit::Type CurrentDragHandle;` — The scrub handle currently being dragged, if any
- L191 _protected member_ `float NotifyTimePositionX;`
- L192 _protected member_ `float NotifyDurationSizeX;`
- L193 _protected member_ `float NotifyScrubHandleCentre;`
- L195 _protected member_ `float WidgetX;`
- L196 _protected member_ `FVector2D WidgetSize;`
- L198 _protected member_ `FVector2D TextSize;`
- L199 _protected member_ `float LabelWidth;`
- L200 _protected member_ `FVector2D BranchingPointIconSize;`
- L203 _protected member_ `FVector2D LastMouseDownPosition;` — Last position the user clicked in the widget
- L206 _protected member_ `FOnNotifyNodeDragStarted OnNodeDragStarted;` — Delegate that is called when the user initiates dragging
- L209 _protected member_ `FOnNotifyStateHandleBeingDragged OnNotifyStateHandleBeingDragged;` — Delegate that is called when a notify state handle is being dragged
- L212 _protected member_ `FPanTrackRequest PanTrackRequest;` — Delegate to pan the track, needed if the markers are dragged out of the track
- L215 _protected member_ `FOnSnapPosition OnSnapPosition;` — Delegate used to snap positions
- L218 _protected member_ `FOnTrackSelectionChanged OnSelectionChanged;` — Delegate to signal selection changing
- L221 _protected member_ `FOnUpdatePanel OnUpdatePanel;` — Delegate to redraw the notify panel
- L224 _protected member_ `FGeometry CachedTrackGeometry;` — Cached owning track geometry
- L226 _protected member_ `TSharedPtr<SOverlay> EndMarkerNodeOverlay;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API PERSONA_API`
- L28 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDeleteNotify, struct FAnimNotifyEvent*) DECLARE_DELEGATE_RetVal_FourParams(FReply, FOnNotifyNodeDragStarted, TSharedRef<SAnimNotifyNode>, const FPointerEvent&, const FVector2D&, const bool) DECLARE_DELEGATE_RetVal_FiveParams(FReply, FOnNotifyNodesDragStarted, TArray<TSharedPtr<SAnimNotifyNode>>, TSharedRef<SWidget>, const FVector2D&, const FVector2D&, const bool) DECLARE_DELEGATE_RetVal(float, FOnGetDraggedNodePos)`
- L29 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(FReply, FOnNotifyNodeDragStarted, TSharedRef<SAnimNotifyNode>, const FPointerEvent&, const FVector2D&, const bool) DECLARE_DELEGATE_RetVal_FiveParams(FReply, FOnNotifyNodesDragStarted, TArray<TSharedPtr<SAnimNotifyNode>>, TSharedRef<SWidget>, const FVector2D&, const FVector2D&, const bool) DECLARE_DELEGATE_RetVal(float, FOnGetDraggedNodePos)`
- L30 _delegate_ `DECLARE_DELEGATE_RetVal_FiveParams(FReply, FOnNotifyNodesDragStarted, TArray<TSharedPtr<SAnimNotifyNode>>, TSharedRef<SWidget>, const FVector2D&, const FVector2D&, const bool) DECLARE_DELEGATE_RetVal(float, FOnGetDraggedNodePos)`
- L31 _delegate_ `DECLARE_DELEGATE_RetVal(float, FOnGetDraggedNodePos)`

### `Source/Editor/Persona/Public/SAnimNotifyShared.h` (Public)


#### enum `ENotifyStateHandleHit::Type`  
`enum Type`  
_L18-23_
- L20 _public enumerator_ `Start`
- L21 _public enumerator_ `End`
- L22 _public enumerator_ `None`

#### enum `ENotifyNodeObjectTypes::Type`  
`enum Type`  
_L35-39_
- L37 _public enumerator_ `NOTIFY`
- L38 _public enumerator_ `SYNC_MARKER`

#### struct `INotifyNodeObjectInterface`  
`struct INotifyNodeObjectInterface`  
_L42-84_
- L44 _public function_ `static FText MakeTooltipFromTime(const UAnimSequenceBase* InSequence, float InSeconds, float InDuration)`
- L60 _public prototype_ `virtual ENotifyNodeObjectTypes::Type GetType() const = 0;`
- L61 _public prototype_ `virtual FAnimNotifyEvent* GetNotifyEvent() = 0;`
- L62 _public prototype_ `virtual int GetTrackIndex() const = 0;`
- L63 _public prototype_ `virtual float GetTime(EAnimLinkMethod::Type ReferenceFrame = EAnimLinkMethod::Absolute) const = 0;`
- L64 _public prototype_ `virtual float GetDuration() = 0;`
- L65 _public prototype_ `virtual FName GetName() = 0;`
- L66 _public prototype_ `virtual TOptional<FLinearColor> GetEditorColor() = 0;`
- L67 _public prototype_ `virtual FText GetNodeTooltip(const UAnimSequenceBase* Sequence) = 0;`
- L68 _public prototype_ `virtual TOptional<UObject*> GetObjectBeingDisplayed() = 0;`
- L69 _public prototype_ `virtual bool IsBranchingPoint() = 0;`
- L70 _public function_ `bool operator<(const INotifyNodeObjectInterface& Rhs) const`
- L72 _public prototype_ `virtual void SetTime(float Time, EAnimLinkMethod::Type ReferenceFrame = EAnimLinkMethod::Absolute) = 0;`
- L73 _public prototype_ `virtual void SetDuration(float Duration) = 0;`
- L75 _public prototype_ `virtual void HandleDrop(class UAnimSequenceBase* Sequence, float Time, int32 TrackIndex) = 0;`
- L76 _public prototype_ `virtual void CacheName() = 0;`
- L78 _public prototype_ `virtual void Delete(UAnimSequenceBase* Seq) = 0;`
- L79 _public prototype_ `virtual void MarkForDelete(UAnimSequenceBase* Seq) = 0;`
- L81 _public prototype_ `virtual void ExportForCopy(UAnimSequenceBase* Seq, FString& StrValue) const = 0;`
- L83 _public prototype_ `virtual FGuid GetGuid() const = 0;`

#### struct `FNotifyNodeInterface`  
`struct FNotifyNodeInterface : public INotifyNodeObjectInterface`  
_L86-254_
- inherits: `INotifyNodeObjectInterface`
- L88 _public member_ `FAnimNotifyEvent* NotifyEvent;`
- L91 _public member_ `FName CachedNotifyName;` — Cached notify name (can be generated by blueprints so want to cache this instead of hitting VM)
- L94 _public member_ `FGuid Guid;` — Stable Guid that allows us to refer to notify event
- L96 _public function_ `FNotifyNodeInterface(FAnimNotifyEvent* InAnimNotifyEvent) : NotifyEvent(InAnimNotifyEvent), Guid(NotifyEvent->Guid)`
- L97 _public function_ `virtual ENotifyNodeObjectTypes::Type GetType() const override`
- L98 _public function_ `virtual FAnimNotifyEvent* GetNotifyEvent() override`
- L99 _public function_ `virtual int GetTrackIndex() const override`
- L100 _public function_ `virtual float GetTime(EAnimLinkMethod::Type ReferenceFrame = EAnimLinkMethod::Absolute) const override`
- L101 _public function_ `virtual float GetDuration() override`
- L102 _public function_ `virtual FName GetName() override`
- L103 _public function_ `virtual bool IsBranchingPoint() override`
- L104 _public function_ `virtual TOptional<FLinearColor> GetEditorColor() override`
- L118 _public function_ `virtual FText GetNodeTooltip(const UAnimSequenceBase* Sequence) override`
- L141 _public function_ `virtual TOptional<UObject*> GetObjectBeingDisplayed() override`
- L155 _public function_ `virtual void SetTime(float Time, EAnimLinkMethod::Type ReferenceFrame = EAnimLinkMethod::Absolute) override`
- L156 _public function_ `virtual void SetDuration(float Duration) override`
- L158 _public function_ `virtual void HandleDrop(class UAnimSequenceBase* Sequence, float Time, int32 TrackIndex) override`
- L178 _public function_ `virtual void CacheName() override`
- L194 _public function_ `virtual void Delete(UAnimSequenceBase* Seq) override`
- L209 _public function_ `virtual void MarkForDelete(UAnimSequenceBase* Seq) override`
- L221 _public function_ `virtual void ExportForCopy(UAnimSequenceBase* Seq, FString& StrValue) const override`
- L243 _public function_ `virtual FGuid GetGuid() const override`
- L248 _public function_ `static void RemoveInvalidNotifies(UAnimSequenceBase* SeqBase)`

#### struct `FSyncMarkerNodeInterface`  
`struct FSyncMarkerNodeInterface : public INotifyNodeObjectInterface`  
_L256-375_
- inherits: `INotifyNodeObjectInterface`
- L258 _public member_ `FAnimSyncMarker* SyncMarker;`
- L261 _public member_ `FGuid Guid;` — Stable Guid that allows us to refer to sync marker event
- L263 _public function_ `FSyncMarkerNodeInterface(FAnimSyncMarker* InSyncMarker) : SyncMarker(InSyncMarker), Guid(SyncMarker->Guid)`
- L264 _public function_ `virtual ENotifyNodeObjectTypes::Type GetType() const override`
- L265 _public function_ `virtual FAnimNotifyEvent* GetNotifyEvent() override`
- L266 _public function_ `virtual int GetTrackIndex() const override`
- L267 _public function_ `virtual float GetTime(EAnimLinkMethod::Type ReferenceFrame = EAnimLinkMethod::Absolute) const override`
- L268 _public function_ `virtual float GetDuration() override`
- L269 _public function_ `virtual FName GetName() override`
- L270 _public function_ `virtual bool IsBranchingPoint() override`
- L271 _public function_ `virtual TOptional<FLinearColor> GetEditorColor() override`
- L283 _public function_ `virtual FText GetNodeTooltip(const UAnimSequenceBase* Sequence) override`
- L288 _public function_ `virtual TOptional<UObject*> GetObjectBeingDisplayed() override`
- L293 _public function_ `virtual void SetTime(float Time, EAnimLinkMethod::Type ReferenceFrame = EAnimLinkMethod::Absolute) override`
- L294 _public function_ `virtual void SetDuration(float Duration) override`
- L296 _public function_ `virtual void HandleDrop(class UAnimSequenceBase* Sequence, float Time, int32 TrackIndex) override`
- L302 _public function_ `virtual void CacheName() override`
- L304 _public function_ `virtual void Delete(UAnimSequenceBase* SeqBase) override`
- L321 _public function_ `virtual void MarkForDelete(UAnimSequenceBase* SeqBase) override`
- L336 _public function_ `virtual void ExportForCopy(UAnimSequenceBase* SeqBase, FString& StrValue) const override`
- L361 _public function_ `virtual FGuid GetGuid() const override`
- L366 _public function_ `static void RemoveInvalidSyncMarkers(UAnimSequenceBase* SeqBase)`

#### struct `NotifyCompileTimeMax`  
`template<int32 A, int32 B> struct NotifyCompileTimeMax`  
_L379-382_
- desc: Struct that allows us to get the max value of 2 numbers at compile time

#### enum `NotifyCompileTimeMax::Max`  
`enum Max`  
_L381-381_
- L381 _public enumerator_ `enum Max { VALUE = (A > B) ? A : B };`

#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "AnimNotifyPanel"`
- L16 _namespace_ `namespace ENotifyStateHandleHit`
- L26 _delegate_ `DECLARE_DELEGATE_FourParams(FOnNotifyStateHandleBeingDragged, TSharedPtr<SAnimNotifyNode> , const FPointerEvent& , ENotifyStateHandleHit::Type , float ) DECLARE_DELEGATE_FourParams(FOnNotifyNodesBeingDragged, const TArray<TSharedPtr<SAnimNotifyNode>>& , const class FDragDropEvent& , float , float ) DECLARE_DELEGATE_TwoParams(FPanTrackRequest, int32, FVector2f) DECLARE_DELEGATE(FOnTrackSelectionChanged) DECLARE_DELEGATE(FOnUpdatePanel) DECLARE_DELEGATE_RetVal_FourParams(bool, FOnSnapPosition, float& , float , TArrayView<const FName> , FName& ) namespace ENotifyNodeObjectTypes { enum Type { NOTIFY, SYNC_MARKER }; };`
- L27 _delegate_ `DECLARE_DELEGATE_FourParams(FOnNotifyNodesBeingDragged, const TArray<TSharedPtr<SAnimNotifyNode>>& , const class FDragDropEvent& , float , float ) DECLARE_DELEGATE_TwoParams(FPanTrackRequest, int32, FVector2f) DECLARE_DELEGATE(FOnTrackSelectionChanged) DECLARE_DELEGATE(FOnUpdatePanel) DECLARE_DELEGATE_RetVal_FourParams(bool, FOnSnapPosition, float& , float , TArrayView<const FName> , FName& ) namespace ENotifyNodeObjectTypes { enum Type { NOTIFY, SYNC_MARKER }; };`
- L28 _delegate_ `DECLARE_DELEGATE_TwoParams(FPanTrackRequest, int32, FVector2f) DECLARE_DELEGATE(FOnTrackSelectionChanged) DECLARE_DELEGATE(FOnUpdatePanel) DECLARE_DELEGATE_RetVal_FourParams(bool, FOnSnapPosition, float& , float , TArrayView<const FName> , FName& ) namespace ENotifyNodeObjectTypes { enum Type { NOTIFY, SYNC_MARKER }; };`
- L29 _delegate_ `DECLARE_DELEGATE(FOnTrackSelectionChanged) DECLARE_DELEGATE(FOnUpdatePanel) DECLARE_DELEGATE_RetVal_FourParams(bool, FOnSnapPosition, float& , float , TArrayView<const FName> , FName& ) namespace ENotifyNodeObjectTypes { enum Type { NOTIFY, SYNC_MARKER }; };`
- L30 _delegate_ `DECLARE_DELEGATE(FOnUpdatePanel) DECLARE_DELEGATE_RetVal_FourParams(bool, FOnSnapPosition, float& , float , TArrayView<const FName> , FName& ) namespace ENotifyNodeObjectTypes { enum Type { NOTIFY, SYNC_MARKER }; };`
- L31 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FOnSnapPosition, float& , float , TArrayView<const FName> , FName& ) namespace ENotifyNodeObjectTypes { enum Type { NOTIFY, SYNC_MARKER }; };`
- L33 _namespace_ `namespace ENotifyNodeObjectTypes`
- L250 _function_ `SeqBase->Notifies.RemoveAll([](const FAnimNotifyEvent& InNotifyEvent) { return !InNotifyEvent.Guid.IsValid(); });` (scope `FNotifyNodeInterface::RemoveInvalidNotifies`)
- L370 _function_ `Seq->AuthoredSyncMarkers.RemoveAll([](const FAnimSyncMarker& InSyncMarker) { return !InSyncMarker.Guid.IsValid(); });` (scope `FSyncMarkerNodeInterface::RemoveInvalidSyncMarkers`)
- L385 _variable_ `const int32 MAX_NOTIFY_NODE_OBJECT_INTERFACE_SIZE = NotifyCompileTimeMax<sizeof(FNotifyNodeInterface), sizeof(FSyncMarkerNodeInterface)>::VALUE;` — Size of biggest object that we can store in our node, if new node interfaces are added they should be part of this calculation

### `Source/Editor/Persona/Public/SAnimTimingPanelShared.h` (Public)


#### enum `ENotifyTimingElementType::Type`  
`enum Type`  
_L10-18_
- L12 _public enumerator_ `QueuedNotify`
- L13 _public enumerator_ `BranchPointNotify`
- L14 _public enumerator_ `NotifyStateBegin`
- L15 _public enumerator_ `NotifyStateEnd`
- L16 _public enumerator_ `Section`
- L17 _public enumerator_ `Max`

#### struct `FTimingRelevantElementBase`  
`struct FTimingRelevantElementBase`  
_L21-65_
- L23 _public prototype_ `virtual ~FTimingRelevantElementBase() = default;`
- L25 _public function_ `virtual FName GetTypeName()`
- L30 _public function_ `virtual float GetElementTime() const`
- L35 _public function_ `virtual int32 GetElementSortPriority() const`
- L40 _public function_ `virtual ENotifyTimingElementType::Type GetType()`
- L47 _public function_ `virtual void GetDescriptionItems(TMap<FString, FText>& Items)` — Get a list of descriptions key/values to describe the element. Intended for UI/Tooltip use
- L53 _public function_ `virtual bool Compare(const FTimingRelevantElementBase& Other)` — Comparison for sorting lists of elements
- L64 _public member_ `int32 TriggerIdx;` — Where in the order for the sequence this element will trigger

#### class `SAnimTimingNode`  
`class SAnimTimingNode : public SCompoundWidget`  
_L70-91_
- inherits: `SCompoundWidget`
- L73 _public function_ `SLATE_BEGIN_ARGS(SAnimTimingNode) : _InElement() , _bUseTooltip(true)`
- L79 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FTimingRelevantElementBase>, InElement) SLATE_ARGUMENT(bool, bUseTooltip) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L85 _public prototype_ `virtual FVector2D ComputeDesiredSize(float) const override;`
- L90 _protected member_ `TSharedPtr<FTimingRelevantElementBase> Element;` — The observed element

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ENotifyTimingElementType`

### `Source/Editor/Persona/Public/SBoneMappingBase.h` (Public)


#### class `FDisplayedBoneMappingInfo`  
`class FDisplayedBoneMappingInfo`  
_L26-57_
- L29 _public member_ `FName Name;`
- L30 _public member_ `FString DisplayName;`
- L33 _public function_ `static TSharedRef<FDisplayedBoneMappingInfo> Make(const FName NodeName, const FString DisplayName)` — Static function for creating a new item, but ensures that you can only have a TSharedRef to one
- L38 _public function_ `FName GetNodeName() const`
- L43 _public function_ `FString GetDisplayName() const`
- L50 _protected function_ `FDisplayedBoneMappingInfo(const FName InNodeName, const FString InDisplayName) : Name( InNodeName ) , DisplayName( InDisplayName )` — Hidden constructor, always use Make above
- L56 _protected function_ `FDisplayedBoneMappingInfo()` — Hidden constructor, always use Make above

#### class `SBoneMappingListRow`  
`class SBoneMappingListRow : public SMultiColumnTableRow< FDisplayedBoneMappingInfoPtr >`  
_L71-117_
- inherits: `SMultiColumnTableRow<FDisplayedBoneMappingInfoPtr>`
- L76 _public function_ `SLATE_BEGIN_ARGS(SBoneMappingListRow)`
- L79 _public prototype_ `SLATE_ARGUMENT(FDisplayedBoneMappingInfoPtr, Item) SLATE_ARGUMENT(TSharedPtr<SBoneMappingListType>, BoneMappingListView) SLATE_EVENT(FOnBoneMappingChanged, OnBoneMappingChanged) SLATE_EVENT(FOnGetBoneMapping, OnGetBoneMapping) SLATE_EVENT(FGetReferenceSkeleton, OnGetReferenceSkeleton) SLATE_EVENT(FOnGetFilteredText, OnGetFilteredText) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);` — The item for this row
- L97 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L102 _private member_ `TSharedPtr<SBoneMappingListType> BoneMappingListView;` — Widget used to display the list of retarget sources
- L105 _private member_ `FDisplayedBoneMappingInfoPtr Item;` — The name and weight of the retarget source
- L108 _private prototype_ `void OnBoneSelectionChanged(FName Name);` — Bone tree widget delegates
- L109 _private prototype_ `FReply OnClearButtonClicked();`
- L110 _private prototype_ `FName GetSelectedBone(bool& bMultipleValues) const;`
- L111 _private prototype_ `FText GetFilterText() const;`
- L113 _private member_ `FOnBoneMappingChanged OnBoneMappingChanged;`
- L114 _private member_ `FOnGetBoneMapping OnGetBoneMapping;`
- L115 _private member_ `FGetReferenceSkeleton OnGetReferenceSkeleton;`
- L116 _private member_ `FOnGetFilteredText OnGetFilteredText;`

#### class `SBoneMappingBase`  
`class SBoneMappingBase : public SCompoundWidget`  
_L122-205_
- inherits: `SCompoundWidget`
- L125 _public function_ `SLATE_BEGIN_ARGS( SBoneMappingBase )`
- L128 _public prototype_ `SLATE_EVENT(FOnBoneMappingChanged, OnBoneMappingChanged) SLATE_EVENT(FOnGetBoneMapping, OnGetBoneMapping) SLATE_EVENT(FGetReferenceSkeleton, OnGetReferenceSkeleton) SLATE_EVENT(FOnCreateBoneMapping, OnCreateBoneMapping) SLATE_END_ARGS() void Construct( const FArguments& InArgs, FSimpleMulticastDelegate& InOnPostUndo );`
- L149 _public prototype_ `void OnFilterTextChanged( const FText& SearchText );` — Filters the SListView when the user changes the search text box (NameFilterBox) @param SearchText - The text the user has typed
- L159 _public prototype_ `void OnFilterTextCommitted( const FText& SearchText, ETextCommit::Type CommitInfo );` — Filters the SListView when the user hits enter or clears the search box Simply calls OnFilterTextChanged @param SearchText - The text the user has typed @param CommitInfo - Not used
- L169 _public prototype_ `TSharedRef<ITableRow> GenerateBoneMappingRow(TSharedPtr<FDisplayedBoneMappingInfo> InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Create a widget for an entry in the tree from an info @param InInfo - Shared pointer to the morph target we're generating a row for @param OwnerTable - The table that owns this row @return A new Slate widget, containing the UI for this row
- L174 _public prototype_ `void RefreshBoneMappingList();` — Handler for the delete of retarget source
- L181 _private function_ `FText& GetFilterText()` — Accessor so our rows can grab the filtertext for highlighting
- L184 _private member_ `TSharedPtr<SSearchBox> NameFilterBox;` — Box to filter to a specific morph target name
- L187 _private member_ `TSharedPtr<SBoneMappingListType> BoneMappingListView;` — Widget used to display the list of retarget sources
- L190 _private member_ `TArray< TSharedPtr<FDisplayedBoneMappingInfo> > BoneMappingList;` — A list of retarget sources. Used by the BoneMappingListView.
- L193 _private member_ `FText FilterText;` — Current text typed into NameFilterBox
- L196 _private prototype_ `void PostUndo();` — Delegate for undo/redo transaction
- L198 _private prototype_ `void OnBoneMappingChanged( FName NodeName, FName BoneName );`
- L199 _private prototype_ `FName GetBoneMapping( FName NodeName );`
- L201 _private member_ `FGetReferenceSkeleton OnGetReferenceSkeletonDelegate;`
- L202 _private member_ `FOnBoneMappingChanged OnBoneMappingChangedDelegate;`
- L203 _private member_ `FOnGetBoneMapping OnGetBoneMappingDelegate;`
- L204 _private member_ `FOnCreateBoneMapping OnCreateBoneMappingDelegate;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API PERSONA_API`
- L59 _typedef_ `typedef SListView< TSharedPtr<FDisplayedBoneMappingInfo> > SBoneMappingListType;`
- L64 _typedef_ `typedef TSharedPtr< FDisplayedBoneMappingInfo > FDisplayedBoneMappingInfoPtr;`
- L66 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnBoneMappingChanged, FName , FName );`
- L66 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnBoneMappingChanged, FName , FName );`
- L67 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FName, FOnGetBoneMapping, FName );`
- L67 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FName, FOnGetBoneMapping, FName );`
- L68 _delegate_ `DECLARE_DELEGATE_RetVal(FText&, FOnGetFilteredText) DECLARE_DELEGATE_TwoParams(FOnCreateBoneMapping, const FString&, TArray< TSharedPtr<FDisplayedBoneMappingInfo> >&) class SBoneMappingListRow : public SMultiColumnTableRow< FDisplayedBoneMappingInfoPtr > { public: SLATE_BEGIN_ARGS(SBoneMappingListRow) {} SLATE_ARGUMENT(FDisplayedBoneMappingInfoPtr, Item) SLATE_ARGUMENT(TSharedPtr<SBoneMappingListType>, BoneMappingListView) SLATE_EVENT(FOnBoneMappingChanged, OnBoneMappingChanged) SLATE_EVENT(FOnGetBoneMapping, OnGetBoneMapping) SLATE_EVENT(FGetReferenceSkeleton, OnGetReferenceSkeleton) SLATE_EVENT(FOnGetFilteredText, OnGetFilteredText) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView); virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override; private: TSharedPtr<SBoneMappingListType> BoneMappingListView; FDisplayedBoneMappingInfoPtr Item;`
- L69 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnCreateBoneMapping, const FString&, TArray< TSharedPtr<FDisplayedBoneMappingInfo> >&) class SBoneMappingListRow : public SMultiColumnTableRow< FDisplayedBoneMappingInfoPtr > { public: SLATE_BEGIN_ARGS(SBoneMappingListRow) {} SLATE_ARGUMENT(FDisplayedBoneMappingInfoPtr, Item) SLATE_ARGUMENT(TSharedPtr<SBoneMappingListType>, BoneMappingListView) SLATE_EVENT(FOnBoneMappingChanged, OnBoneMappingChanged) SLATE_EVENT(FOnGetBoneMapping, OnGetBoneMapping) SLATE_EVENT(FGetReferenceSkeleton, OnGetReferenceSkeleton) SLATE_EVENT(FOnGetFilteredText, OnGetFilteredText) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView); virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override; private: TSharedPtr<SBoneMappingListType> BoneMappingListView; FDisplayedBoneMappingInfoPtr Item;`

### `Source/Editor/Persona/Public/SCreateClothingSettingsPanel.h` (Public)


#### class `FClothCreateSettingsCustomization`  
`class FClothCreateSettingsCustomization : public IDetailCustomization`  
_L15-46_
- inherits: `IDetailCustomization`
- L19 _public function_ `FClothCreateSettingsCustomization(TWeakObjectPtr<USkeletalMesh> InMeshPtr, bool bInIsSubImport) : bIsSubImport(bInIsSubImport) , MeshPtr(InMeshPtr) , ParamsStruct(nullptr)`
- L25 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance(TWeakObjectPtr<USkeletalMesh> MeshPtr, bool bIsSubImport)`
- L30 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L34 _protected prototype_ `TSharedRef<SWidget> OnGetTargetAssetMenu();`
- L35 _protected prototype_ `FText GetTargetAssetText() const;`
- L36 _protected prototype_ `void OnAssetSelected(int32 InMeshClothingIndex);`
- L38 _protected prototype_ `TSharedRef<SWidget> OnGetTargetLodMenu();`
- L39 _protected prototype_ `FText GetTargetLodText() const;`
- L40 _protected prototype_ `void OnLodSelected(int32 InLodIndex);`
- L41 _protected prototype_ `bool CanSelectLod() const;`
- L43 _protected member_ `bool bIsSubImport;`
- L44 _protected member_ `TWeakObjectPtr<USkeletalMesh> MeshPtr;`
- L45 _protected member_ `FSkeletalMeshClothBuildParams* ParamsStruct;`

#### class `SCreateClothingSettingsPanel`  
`class SCreateClothingSettingsPanel : public SCompoundWidget`  
_L48-92_
- inherits: `SCompoundWidget`
- L51 _public function_ `SLATE_BEGIN_ARGS(SCreateClothingSettingsPanel) : _LodIndex(INDEX_NONE) , _SectionIndex(INDEX_NONE) , _bIsSubImport(false)`
- L58 _public prototype_ `SLATE_ARGUMENT(FString, MeshName)` — Name of the mesh we're operating on
- L77 _private member_ `FSkeletalMeshClothBuildParams BuildParams;` — Params struct to hold request data
- L80 _private member_ `bool bIsSubImport;` — Whether or not to show sub params (lod imports)
- L83 _private prototype_ `FText GetCreateButtonTooltip() const;` — Create button functionality
- L84 _private prototype_ `bool CanCreateClothing() const;`
- L87 _private prototype_ `FReply OnCreateClicked();` — Handlers for panel buttons
- L90 _private member_ `FOnCreateClothingRequested OnCreateDelegate;` — Called when the create button is clicked, so external caller can handle the request

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API PERSONA_API`
- L13 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCreateClothingRequested, FSkeletalMeshClothBuildParams&);`
- L13 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCreateClothingRequested, FSkeletalMeshClothBuildParams&);`

### `Source/Editor/Persona/Public/SPersonaToolBox.h` (Public)


#### struct `FToolBoxSummoner`  
`struct FToolBoxSummoner : public FWorkflowTabFactory`  
_L26-37_
- inherits: `FWorkflowTabFactory`
- L29 _public prototype_ `FToolBoxSummoner(TSharedPtr<FPersonaAssetEditorToolkit> InPersonaEditorToolkit);`
- L31 _public prototype_ `virtual TSharedRef<SDockTab> SpawnTab(const FWorkflowTabSpawnInfo& Info) const override;`
- L32 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;`
- L33 _public prototype_ `virtual bool CanSpawnTab(const FSpawnTabArgs& SpawnArgs, TWeakPtr<FTabManager> WeakTabManager) const override;`
- L36 _protected member_ `TWeakPtr<FPersonaAssetEditorToolkit> PersonaAssetEditorToolkit;`

#### class `SPersonaToolbox`  
`class SPersonaToolbox : public SCompoundWidget`  
_L40-84_
- inherits: `SCompoundWidget`
- desc: Widget to surface an Edit Mode its widget, similar to LevelEditor approach
- L43 _public function_ `SLATE_BEGIN_ARGS( SPersonaToolbox )`
- L46 _public prototype_ `~SPersonaToolbox();`
- L48 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FPersonaAssetEditorToolkit>& InOwningEditor);`
- L51 _public prototype_ `void AttachToolkit(const TSharedRef<IToolkit>& InToolkit);` — Called to attach a toolkit to this toolbox widget (e.g. when the mode changes).
- L54 _public prototype_ `void DetachToolkit(const TSharedRef<IToolkit>& InToolkit);` — Called to detach a toolkit from this toolbox widget (e.g. when the mode changes).
- L57 _public prototype_ `void SetOwningTab(const TSharedRef<SDockTab>& InOwningTab);` — Sets the owning tab so that we can update the tab icon based on what the toolkit provides.
- L60 _private prototype_ `void UpdateInlineContent(const TSharedPtr<IToolkit>& Toolkit, TSharedPtr<SWidget> InlineContent);`
- L62 _private prototype_ `void UpdatePalette(const TWeakPtr<FModeToolkit>& InWeakToolkit) const;`
- L65 _private prototype_ `EVisibility GetInlineContentHolderVisibility() const;` — Whether to show the inline content or not.
- L69 _private member_ `TWeakPtr<SDockTab> OwningTab;` — The owning tab where the toolkit's interface is hosted. We need this to update the icons and title as the toolkit changes.
- L71 _private member_ `TWeakPtr<FPersonaAssetEditorToolkit> PersonaEditor;`
- L74 _private member_ `TSharedPtr<SBorder> InlineContentHolder;` — Inline content area for editor modes
- L77 _private member_ `TSharedPtr<SBorder> ModeToolBarContainer;` — The container holding the mode toolbar
- L80 _private member_ `TSharedPtr<SBorder> ModeToolHeader;` — The active tool header area
- L83 _private member_ `FStatusBarMessageHandle StatusBarMessageHandle;` — The global status bar to show the name of the active tool.

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API PERSONA_API`

### `Source/Editor/Persona/Public/SSkinWeightProfileImportOptions.h` (Public)


#### class `USkinWeightImportOptions`  
`class USkinWeightImportOptions : public UObject`  
_L26-42_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L33 _public member_ `FString ProfileName;` — `UPROPERTY(EditAnywhere, Category=SkinWeights, Config)` — Name of the to-be-imported Skin Weights Profile
- L37 _public member_ `FString FilePath;` — `UPROPERTY(VisibleAnywhere, Category = SkinWeights)` — File path to FBX file containing Mesh with alternative set of Skin Weights
- L41 _public member_ `int32 LODIndex;` — `UPROPERTY(EditAnywhere, Category = SkinWeights, meta=(DisplayName="LOD Index"))` — Target LOD index this file corresponds to

#### class `FSkinWeightImportOptionsCustomization`  
`class FSkinWeightImportOptionsCustomization : public IDetailCustomization`  
_L45-64_
- inherits: `IDetailCustomization`
- desc: Details customization for the import object, used to hide certain properties when needed and ensure we do not get duplicate profile names
- L48 _public function_ `FSkinWeightImportOptionsCustomization(USkeletalMesh* InSkeletalMesh) : WeakSkeletalMesh(InSkeletalMesh)`
- L49 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance(USkeletalMesh* InSkeletalMesh)`
- L50 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L52 _public prototype_ `FText OnGetProfileName() const;`
- L53 _public prototype_ `const bool IsProfileNameValid(const FString& NewName) const;`
- L55 _protected member_ `TSharedPtr<SEditableTextBox> NameEditTextBox;`
- L56 _protected member_ `TSharedPtr<IPropertyHandle> ProfileNameHandle;`
- L57 _protected member_ `TWeakObjectPtr<USkeletalMesh> WeakSkeletalMesh;`
- L58 _protected member_ `TArray<FString> RestrictedNames;`
- L60 _protected prototype_ `void UpdateNameRestriction();`
- L62 _protected prototype_ `void OnProfileNameChanged(const FText& InNewText);`
- L63 _protected prototype_ `void OnProfileNameCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);`

#### class `SSkinWeightProfileImportOptions`  
`class SSkinWeightProfileImportOptions : public SCompoundWidget`  
_L66-132_
- inherits: `SCompoundWidget`
- L69 _public function_ `SLATE_BEGIN_ARGS(SSkinWeightProfileImportOptions) : _ImportSettings(nullptr) , _WidgetWindow() , _SkeletalMesh()`
- L80 _public prototype_ `void Construct(const FArguments& InArgs);`
- L81 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L83 _public function_ `FReply OnImport()`
- L93 _public function_ `FReply OnCancel()`
- L103 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L113 _public function_ `bool ShouldImport() const`
- L119 _public function_ `SSkinWeightProfileImportOptions() : ImportSettings(nullptr) , bShouldImport(false)`
- L125 _private member_ `USkinWeightImportOptions* ImportSettings;`
- L126 _private member_ `USkeletalMesh* SkeletalMesh;`
- L127 _private member_ `TWeakPtr<SWindow> WidgetWindow;`
- L128 _private member_ `TSharedPtr<SButton> ImportButton;`
- L129 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L130 _private member_ `TSharedPtr<FSkinWeightImportOptionsCustomization> DetailsCustomization;`
- L131 _private member_ `bool bShouldImport;`

### `Source/Editor/Persona/Public/SkeletonSelectionEditMode.h` (Public)


#### class `FSkeletonSelectionEditMode`  
`class FSkeletonSelectionEditMode : public IPersonaEditMode`  
_L23-77_
- inherits: `IPersonaEditMode`
- L26 _public prototype_ `FSkeletonSelectionEditMode();`
- L29 _public prototype_ `virtual bool GetCameraTarget(FSphere& OutTarget) const override;` — IPersonaEditMode interface
- L30 _public prototype_ `virtual class IPersonaPreviewScene& GetAnimPreviewScene() const override;`
- L31 _public prototype_ `virtual void GetOnScreenDebugInfo(TArray<FText>& OutDebugInfo) const override;`
- L34 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;` — FEdMode interface
- L35 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L36 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L37 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L38 _public prototype_ `virtual bool AllowWidgetMove() override;`
- L39 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L40 _public prototype_ `virtual bool UsesTransformWidget() const override;`
- L41 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode CheckMode) const override;`
- L42 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L43 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L44 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L45 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click) override;`
- L46 _public prototype_ `virtual bool CanCycleWidgetMode() const override;`
- L47 _public prototype_ `virtual bool FrustumSelect(const FConvexVolume& InFrustum, FEditorViewportClient* InViewportClient, bool InSelect = true) override;`
- L49 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;`
- L50 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L53 _protected prototype_ `FTransform GetBoneTransform(const int32 BoneIndex) const;`
- L54 _protected prototype_ `FTransform GetSocketTransform(const USkeletalMeshSocket* Socket) const;`
- L55 _protected prototype_ `FTransform GetWorldSpaceBoneTransform(const FReferenceSkeleton& ReferenceSkeleton, const int32 BoneIndex) const;`
- L56 _protected prototype_ `const FReferenceSkeleton& GetReferenceSkeletonForComponent(const USkeletalMeshComponent* Component) const;`
- L60 _private prototype_ `FSelectedSocketInfo DuplicateAndSelectSocket(const FSelectedSocketInfo& SocketInfoToDuplicate);` — Duplicates and selects a socket when we alt-drag
- L63 _private prototype_ `bool IsSelectedBoneRequired() const;` — Check whether the currently selected bone is in the required bones list
- L66 _private prototype_ `static FIntPoint GetDPIUnscaledSize(FViewport* Viewport, FViewportClient* Client);` — Unscale a viewport's size by its DPI factor
- L70 _private member_ `bool bManipulating;` — Whether we are currently in a manipulation
- L73 _private member_ `bool bResumeAfterManipulating;` — Whether the preview animation should resume after the manipulating has ended
- L76 _private member_ `bool bInTransaction;` — Whether we are currently in a transaction

### `Source/Editor/Persona/Public/SkinWeightProfileHelpers.h` (Public)


#### struct `FSkinWeightProfileHelpers`  
`struct FSkinWeightProfileHelpers`  
_L11-34_
- desc: Set of editor-only helper functions used by various bits of UI related to Skin Weight profiles
- L14 _public prototype_ `static void ImportSkinWeightProfile(USkeletalMesh* InSkeletalMesh);` — Tries to import a new set of Skin Weights for the given Skeletal Mesh from an FBX file
- L17 _public prototype_ `static void ImportSkinWeightProfileLOD(USkeletalMesh* InSkeletalMesh, FName ProfileName, int32 LODIndex);` — Tries to import a new set of Skin Weights for the given Skeletal Mesh at the given LOD index from an FBX file
- L20 _public prototype_ `static void ReimportSkinWeightProfileLOD(USkeletalMesh* InSkeletalMesh, const FName& InProfileName, const int32 LODIndex);` — Tries to re import the previously imported skin weights for the given Skeletal Mesh, Profile name and LOD Index
- L23 _public prototype_ `static void RemoveSkinWeightProfile(USkeletalMesh* InSkeletalMesh, const FName& InProfileName);` — Tries to remove the previously imported skin weights for all LODs from the given Skeletal Mesh and Profile name
- L26 _public prototype_ `static void RemoveSkinWeightProfileLOD(USkeletalMesh* InSkeletalMesh, const FName& InProfileName, const int32 LODIndex);` — Tries to remove the previously imported skin weights for all LODs from the given Skeletal Mesh, Profile name and LOD index
- L29 _public prototype_ `static void ClearSkinWeightProfileInstanceOverrides(USkeletalMesh* InSkeletalMesh, FName InProfileName);` — Goes through every component using the given Skeletal Mesh and checks whether or not it currently has the Skin Weight Profile set (for either preview or at runtime)
- L33 _protected prototype_ `static bool CopySkinWeightsToProfile(USkeletalMesh* SourceMesh, USkeletalMesh* TargetMesh, const int32 LODIndex, const FName ProfileName);` — Creates a copy of the skin weights from SourceMesh into a Skin Weight profile as part of TargetMesh

### `Source/Editor/Persona/Public/SocketDragDropOp.h` (Public)


#### class `FSocketDragDropOp`  
`class FSocketDragDropOp : public FDragDropOperation`  
_L17-95_
- inherits: `FDragDropOperation`
- desc: FSocketDragDropOp
- L21 _public function_ `DRAG_DROP_OPERATOR_TYPE(FSocketDragDropOp, FDragDropOperation) virtual TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L48 _public function_ `FText GetHoverText() const` — Passed into STextBlock so Slate can grab the current text for display
- L54 _public function_ `const FSlateBrush* GetIcon( ) const` — Passed into SImage so Slate can grab the current icon for display
- L60 _public function_ `void SetIcon(const FSlateBrush* InIcon)` — Sets the icon to be displayed
- L66 _public function_ `FSelectedSocketInfo& GetSocketInfo()` — Accessor for the socket info
- L69 _public function_ `bool IsAltDrag() const` — Is this an alt-drag operation?
- L72 _public function_ `bool IsShiftDrag() const` — Is this an shift-drag operation?
- L75 _public function_ `static TSharedRef<FSocketDragDropOp> New( FSelectedSocketInfo InSocketInfo, FModifierKeysState InModifierKeysState )` — Use this function to create a new one of me
- L88 _private member_ `const FSlateBrush* CurrentIconBrush = nullptr;` — The icon to display before the text
- L91 _private member_ `FSelectedSocketInfo SocketInfo;` — The socket that we're dragging
- L94 _private member_ `FModifierKeysState ModifierKeysState;` — What was the modifier state at the start of the drag?
