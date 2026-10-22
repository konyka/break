# Plugins / LiveLinkEditor

- module root: `Plugins/Animation/LiveLink/Source/LiveLinkEditor`
- headers: 30; symbols: 541
- symbol kinds: class=33, delegate=10, enum=2, enumerator=8, function=52, macro=8, member=148, namespace=10, prototype=250, struct=10, typedef=10
- PrivateDependencyModuleNames: AnimGraph, AssetDefinition, AssetRegistry, BlueprintGraph, ClassViewer, Core, CoreUObject, DetailCustomizations, EditorFramework, EditorStyle, EditorWidgets, Engine, EngineAssetDefinitions, GraphEditor, InputCore, KismetCompiler, LiveLinkComponents, LiveLinkDevice, LiveLinkGraphNode, LiveLinkMessageBusFramework, LiveLinkMovieScene, MessageLog, MovieScene, Persona, PlacementMode, Projects, PropertyEditor, Sequencer, Settings, Slate, TimeManagement, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: LiveLink, LiveLinkAnimationCore, LiveLinkInterface, SlateCore

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/AssetDefinition/AssetDefinition_LiveLinkBlueprintVirtualSubject.h` (Private)


#### class `UAssetDefinition_LiveLinkBlueprintVirtualSubject`  
`class UAssetDefinition_LiveLinkBlueprintVirtualSubject : public UAssetDefinition_Blueprint`  
_L9-28_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L16 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkBoneAttachmentDetailCustomization.h` (Private)


#### class `FLiveLinkBoneAttachmentDetailCustomization`  
`class FLiveLinkBoneAttachmentDetailCustomization : public IPropertyTypeCustomization`  
_L10-51_
- inherits: `IPropertyTypeCustomization`
- L14 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IDetailCustomization interface
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L23 _private prototype_ `void CustomizeSubjectRow(TSharedPtr<IPropertyHandle> SubjectPropertyHandle, TSharedPtr<IPropertyHandle> BonePropertyHandle, class IDetailPropertyRow& PropertyRow, class IPropertyTypeCustomizationUtils& StructCustomizationUtils, TSharedPtr<SLiveLinkBoneSelectionWidget>& BonePickerWidget);` — Customize a subject row to combine the subject and bone pickers.
- L25 _private prototype_ `FText GetWarningTooltip() const;` — When the warning icon is visible, returns the text that will be shown in its tooltip.
- L27 _private prototype_ `EVisibility HandleWarningVisibility() const;` — Returns whether the warning symbol should be visible according to the status of the attachment.
- L29 _private prototype_ `SLiveLinkSubjectRepresentationPicker::FLiveLinkSourceSubjectRole GetValue(TSharedPtr<IPropertyHandle> Handle) const;` — Retrieves the value of a subject property on the attachment.
- L31 _private prototype_ `void SetValue(SLiveLinkSubjectRepresentationPicker::FLiveLinkSourceSubjectRole NewValue, TSharedPtr<IPropertyHandle> Handle, TSharedPtr<SLiveLinkBoneSelectionWidget> BonePickerWidget);` — Sets the value of a subject property on the attachment.
- L33 _private prototype_ `void GetSubjectsForPicker(TArray<FLiveLinkSubjectKey>& OutSubjectKeys);` — Populate a filtered list of subjects for the subject representation.
- L35 _private prototype_ `void OnBoneSelected(FName SelectedBone, TSharedPtr<IPropertyHandle> BonePropertyHandle) const;` — Update a bone attachment after a bone is selected.
- L37 _private prototype_ `FName GetSelectedBone(TSharedPtr<IPropertyHandle> BonePropertyHandle) const;` — Returns the bone from the property handle.
- L41 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Handle to the attachment struct.
- L50 _private member_ `FBonePickerWidgets BonePickerWidgets;` — Holds the bone picker widgets for the parent and child bone.

#### struct `FLiveLinkBoneAttachmentDetailCustomization::FBonePickerWidgets`  
`struct FBonePickerWidgets`  
_L43-47_
- L45 _public member_ `TSharedPtr<SLiveLinkBoneSelectionWidget> ParentWidget;`
- L46 _public member_ `TSharedPtr<SLiveLinkBoneSelectionWidget> ChildWidget;`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkBroadcastComponentDetailCustomization.h` (Private)


#### class `FLiveLinkBroadcastComponentDetailCustomization`  
`class FLiveLinkBroadcastComponentDetailCustomization : public IDetailCustomization`  
_L12-28_
- inherits: `IDetailCustomization`
- desc: Customizes a LiveLinkBroadcastComponent details.
- L16 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L22 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L27 _protected member_ `IDetailLayoutBuilder* DetailLayout = nullptr;` — Keep a reference to force refresh the layout

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkClientCommands.h` (Private)


#### class `FLiveLinkClientCommands`  
`class FLiveLinkClientCommands : public TCommands<FLiveLinkClientCommands>`  
_L7-20_
- inherits: `TCommands<FLiveLinkClientCommands>`
- L10 _public prototype_ `FLiveLinkClientCommands();`
- L12 _public member_ `TSharedPtr<FUICommandInfo> RemoveSource;`
- L13 _public member_ `TSharedPtr<FUICommandInfo> RemoveAllSources;`
- L14 _public member_ `TSharedPtr<FUICommandInfo> RemoveSubject;`
- L15 _public member_ `TSharedPtr<FUICommandInfo> PauseSubject;`
- L16 _public member_ `TSharedPtr<FUICommandInfo> RemoveDevice;`
- L19 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkClientPanel.h` (Private)


#### class `SLiveLinkClientPanel`  
`class SLiveLinkClientPanel : public SCompoundWidget, public FGCObject, public FEditorUndoClient`  
_L29-82_
- inherits: `SCompoundWidget,FGCObject,FEditorUndoClient`
- L31 _private function_ `SLATE_BEGIN_ARGS(SLiveLinkClientPanel)`
- L34 _private prototype_ `virtual ~SLiveLinkClientPanel() override;`
- L36 _private prototype_ `void Construct(const FArguments& Args, FLiveLinkClient* InClient);`
- L39 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L40 _private function_ `virtual FString GetReferencerName() const override`
- L47 _private prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L48 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L53 _private prototype_ `EVisibility ShowEditorPerformanceThrottlingWarning() const;` — Controls whether the editor performance throttling warning should be visible
- L56 _private prototype_ `FReply DisableEditorPerformanceThrottling();` — Handle disabling of editor performance throttling
- L59 _private prototype_ `FText GetMessageCountText() const;` — Return the message count text
- L62 _private prototype_ `FText GetSelectedMessageOccurrenceText() const;` — Return the occurrence count and last time occurred text
- L65 _private prototype_ `bool IsInReadOnlyMode() const;` — Returns whether the panel is in read only mode or not.
- L68 _private prototype_ `EVisibility GetVisibilityBasedOnReadOnly() const;` — Get widget visibility according to whether the panel is in read-only mode.
- L72 _private member_ `TSharedPtr<FLiveLinkPanelController> PanelController;` — Handles callback connections between the sources, subjects and details views
- L75 _private member_ `FLiveLinkClient* Client = nullptr;` — Pointer to the livelink client
- L78 _private member_ `TMap<TObjectPtr<UClass>, TObjectPtr<UObject>> DetailsPanelEditorObjects;` — Map to cover
- L81 _private member_ `int32 DetailWidgetIndex = -1;` — Details index

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LIVELINKEDITOR_API`
- L13 _namespace_ `namespace ESelectInfo`
- L14 _namespace_ `namespace ETextCommit`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkComponentDetailCustomization.h` (Private)


#### class `FLiveLinkComponentDetailCustomization`  
`class FLiveLinkComponentDetailCustomization : public IDetailCustomization`  
_L21-50_
- inherits: `IDetailCustomization`
- desc: Customizes a ULiveLinkComponentController details
- L25 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L31 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L35 _protected prototype_ `void OnSubjectRepresentationPropertyChanged();`
- L36 _protected prototype_ `TSharedRef<SWidget> HandleControllerComboButton(TSubclassOf<ULiveLinkRole> RoleClass) const;`
- L37 _protected prototype_ `void HandleControllerSelection(TSubclassOf<ULiveLinkRole> RoleClass, TWeakObjectPtr<UClass> SelectedControllerClass) const;`
- L38 _protected prototype_ `bool IsControllerItemSelected(FName Item, TSubclassOf<ULiveLinkRole> RoleClass) const;`
- L39 _protected prototype_ `EVisibility HandleControllerWarningVisibility(TSubclassOf<ULiveLinkRole> RoleClassEntry) const;`
- L40 _protected prototype_ `TSharedRef<SWidget> BuildControllerNameWidget(TSharedPtr<IPropertyHandle> ControllersProperty, TSubclassOf<ULiveLinkRole> RoleClass) const;`
- L41 _protected prototype_ `TSharedRef<SWidget> BuildControllerValueWidget(TSubclassOf<ULiveLinkRole> RoleClass, const FText& ControllerName) const;`
- L42 _protected prototype_ `void ForceRefreshDetails();`
- L46 _protected member_ `TWeakObjectPtr<ULiveLinkComponentController> EditedObject;` — LiveLinkComponent on which we're acting
- L49 _protected member_ `IDetailLayoutBuilder* DetailLayout = nullptr;` — Keep a reference to force refresh the layout

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkControllerBaseDetailCustomization.h` (Private)


#### class `FLiveLinkControllerBaseDetailCustomization`  
`class FLiveLinkControllerBaseDetailCustomization : public IDetailCustomization`  
_L16-34_
- inherits: `IDetailCustomization`
- desc: Customizes ULiveLinkControllerBase details
- L20 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L26 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L30 _private prototype_ `void OnComponentChanged();`
- L33 _protected member_ `TWeakObjectPtr<ULiveLinkControllerBase> LiveLinkControllerWeak;`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkEditorPrivate.h` (Private)


#### struct `FLiveLinkEditorPrivate`  
`struct FLiveLinkEditorPrivate`  
_L12-15_
- L14 _public prototype_ `static TSharedPtr< class ISlateStyle > GetStyleSet();`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkEditor, Log, All);`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkGraphPanelPinFactory.h` (Private)


#### class `FLiveLinkGraphPanelPinFactory`  
`class FLiveLinkGraphPanelPinFactory : public FGraphPanelPinFactory`  
_L12-33_
- inherits: `FGraphPanelPinFactory`
- L14 _private function_ `virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* InPin) const override`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkHubSubjectSettingsDetailsCustomization.h` (Private)


#### class `FLiveLinkHubSubjectSettingsDetailsCustomization`  
`class FLiveLinkHubSubjectSettingsDetailsCustomization : public IDetailCustomization`  
_L13-27_
- inherits: `IDetailCustomization`
- desc: Customizes a ULiveLinkHubSubjectSettings object
- L17 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L23 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkMetaDataDetailCustomization.h` (Private)


#### class `FLiveLinkMetaDataDetailCustomization`  
`class FLiveLinkMetaDataDetailCustomization : public IPropertyTypeCustomization`  
_L10-22_
- inherits: `IPropertyTypeCustomization`
- L14 _public function_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils ) override` — IDetailCustomization interface
- L15 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L18 _private prototype_ `FText GetFrameNumber() const;`
- L19 _private prototype_ `FText GetTimecodeValue() const;`
- L20 _private prototype_ `FText GetTimecodeFrameRate() const;`
- L21 _private member_ `TSharedPtr<IPropertyHandle> SceneTimeHandle;`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkPreviewController.h` (Private)


#### class `ULiveLinkPreviewController`  
`class ULiveLinkPreviewController : public UPersonaPreviewSceneController`  
_L15-42_
- reflection: `UCLASS()`
- inherits: `UPersonaPreviewSceneController`
- L23 _public member_ `FName SubjectName_DEPRECATED;` — `UE_DEPRECATED(4.23, "FName SubjectName is deprecated. Use the SubjectName of type FLiveLinkSubjectName instead.")` — `UPROPERTY()`
- L27 _public member_ `FLiveLinkSubjectName LiveLinkSubjectName;` — `UPROPERTY(EditAnywhere, Category = "Live Link")`
- L30 _public member_ `bool bEnableCameraSync;` — `UPROPERTY(EditAnywhere, Category = "Live Link")`
- L33 _public member_ `TSubclassOf<ULiveLinkRetargetAsset> RetargetAsset;` — `UPROPERTY(EditAnywhere, NoClear, Category = "Live Link")`
- L35 _public prototype_ `virtual void InitializeView(UPersonaPreviewSceneDescription* SceneDescription, IPersonaPreviewScene* PreviewScene) const;`
- L36 _public prototype_ `virtual void UninitializeView(UPersonaPreviewSceneDescription* SceneDescription, IPersonaPreviewScene* PreviewScene) const;`
- L39 _public prototype_ `virtual void Serialize(FArchive& Ar);`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkSourceSettingsDetailCustomization.h` (Private)


#### class `FLiveLinkSourceSettingsDetailCustomization`  
`class FLiveLinkSourceSettingsDetailCustomization : public IDetailCustomization`  
_L19-51_
- inherits: `IDetailCustomization`
- desc: Customizes a FLiveLinkSourceSettingsDetailCustomization
- L23 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L29 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L33 _private prototype_ `void ForceRefresh();`
- L36 _private prototype_ `FText GetFrameRateText() const;` — Returns the current frame rate associated with this source
- L39 _private prototype_ `FSlateColor GetFrameRateColor() const;` — If all subjects from this source don't have the same timecode, FrameRate will be displayed yellow
- L42 _private prototype_ `FText GetFrameRateTooltip() const;` — Tooltip to advise the user that subjects from this source don't have same FrameRate
- L45 _private prototype_ `bool DoSubjectsHaveSameTimecode() const;` — Returns true if enabled subjects from this Source have the same FrameRate
- L47 _private member_ `IDetailLayoutBuilder* DetailBuilder = nullptr;`
- L48 _private member_ `TWeakObjectPtr<ULiveLinkSourceSettings> WeakSourceSettings;`
- L49 _private member_ `FGuid EditedSourceGuid;`
- L50 _private member_ `FLiveLinkClientReference LiveLinkClient;`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkSubjectKeyDetailCustomization.h` (Private)


#### class `FLiveLinkSubjectKeyDetailCustomization`  
`class FLiveLinkSubjectKeyDetailCustomization : public IPropertyTypeCustomization`  
_L8-25_
- inherits: `IPropertyTypeCustomization`
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IDetailCustomization interface
- L17 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L20 _private prototype_ `SLiveLinkSubjectRepresentationPicker::FLiveLinkSourceSubjectRole GetValue() const;`
- L21 _private prototype_ `void SetValue(SLiveLinkSubjectRepresentationPicker::FLiveLinkSourceSubjectRole NewValue);`
- L22 _private prototype_ `bool HasMultipleValues() const;`
- L24 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkSubjectNameDetailCustomization.h` (Private)


#### class `FLiveLinkSubjectNameDetailCustomization`  
`class FLiveLinkSubjectNameDetailCustomization : public IPropertyTypeCustomization`  
_L8-25_
- inherits: `IPropertyTypeCustomization`
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L16 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils ) override;` — IDetailCustomization interface
- L17 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override`
- L20 _private prototype_ `SLiveLinkSubjectRepresentationPicker::FLiveLinkSourceSubjectRole GetValue() const;`
- L21 _private prototype_ `void SetValue(SLiveLinkSubjectRepresentationPicker::FLiveLinkSourceSubjectRole NewValue);`
- L22 _private prototype_ `bool HasMultipleValues() const;`
- L24 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkSubjectRepresentationDetailCustomization.h` (Private)


#### class `FLiveLinkSubjectRepresentationDetailCustomization`  
`class FLiveLinkSubjectRepresentationDetailCustomization : public IPropertyTypeCustomization`  
_L8-25_
- inherits: `IPropertyTypeCustomization`
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IDetailCustomization interface
- L17 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L20 _private prototype_ `SLiveLinkSubjectRepresentationPicker::FLiveLinkSourceSubjectRole GetValue() const;`
- L21 _private prototype_ `void SetValue(SLiveLinkSubjectRepresentationPicker::FLiveLinkSourceSubjectRole NewValue);`
- L22 _private prototype_ `bool HasMultipleValues() const;`
- L24 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkTest.h` (Private)


#### struct `FLiveLinkInnerTestInternal`  
`struct FLiveLinkInnerTestInternal`  
_L11-32_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- L16 _public member_ `float InnerSingleFloat = 0.f;` — `UPROPERTY()`
- L19 _public member_ `int32 InnerSingleInt = 0;` — `UPROPERTY()`
- L22 _public member_ `FVector InnerVectorDim[2] = {FVector::ZeroVector, FVector::ZeroVector };` — `UPROPERTY()`
- L25 _public member_ `float InnerFloatDim[2] = {0.f, 0.f};` — `UPROPERTY()`
- L28 _public member_ `int32 InnerIntDim[2] = {0, 0};` — `UPROPERTY()`
- L31 _public member_ `TArray<int32> InnerIntArray;` — `UPROPERTY()`

#### struct `FLiveLinkTestFrameDataInternal`  
`struct FLiveLinkTestFrameDataInternal : public FLiveLinkBaseFrameData`  
_L35-65_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkBaseFrameData`
- L40 _public member_ `float NotInterpolated = 0.f;` — `UPROPERTY()`
- L43 _public member_ `FVector SingleVector = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadOnly, Category = "Test", Interp)`
- L46 _public member_ `FLiveLinkInnerTestInternal SingleStruct;` — `UPROPERTY(BlueprintReadOnly, Category = "Test", Interp)`
- L49 _public member_ `float SingleFloat = 0.f;` — `UPROPERTY(BlueprintReadOnly, Category = "Test", Interp)`
- L52 _public member_ `int32 SingleInt = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "Test", Interp)`
- L55 _public member_ `TArray<FVector> VectorArray;` — `UPROPERTY(BlueprintReadOnly, Category = "Test", Interp)`
- L58 _public member_ `TArray<FLiveLinkInnerTestInternal> StructArray;` — `UPROPERTY(BlueprintReadOnly, Category = "Test", Interp)`
- L61 _public member_ `TArray<float> FloatArray;` — `UPROPERTY(BlueprintReadOnly, Category = "Test", Interp)`
- L64 _public member_ `TArray<int32> IntArray;` — `UPROPERTY(BlueprintReadOnly, Category = "Test", Interp)`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/LiveLinkVirtualSubjectDetailCustomization.h` (Private)


#### class `FLiveLinkVirtualSubjectDetailCustomization`  
`class FLiveLinkVirtualSubjectDetailCustomization : public IDetailCustomization`  
_L22-89_
- inherits: `IDetailCustomization`
- desc: Customizes a ULiveLinkVirtualSubjectDetails
- L27 _public typedef_ `typedef TSharedPtr<FName> FSubjectEntryPtr;` — Data type of out subject tree UI
- L29 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L35 _public prototype_ `virtual void CustomizeDetails(class IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L40 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForSelectedSubjectItem(FSubjectEntryPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row for a selected subject.
- L43 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForSubjectItem(FSubjectEntryPtr InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Creates subject tree entry widget
- L46 _private prototype_ `FSlateColor HandleSubjectItemColor(FSubjectEntryPtr InItem) const;` — If Item doesn't exist in Client subject's list, mark it as red
- L48 _private prototype_ `FText HandleSubjectItemToolTip(FSubjectEntryPtr InItem) const;`
- L51 _private prototype_ `TSharedRef<SWidget> OnGetVirtualSubjectsMenu();` — Generate the combo box menu to display subjects to pick.
- L54 _private prototype_ `bool IsEntrySelected(FSubjectEntryPtr EntryPtr);` — Returns whether an entry is currently selected.
- L57 _private prototype_ `void UpdateSubjectList();` — Update the list of LiveLink subjects.
- L60 _private prototype_ `void UpdateSelectedSubjects();` — Update the list of selected subjects displayed above the subject picker.
- L63 _private prototype_ `void OnGetSubjects(TArray<FLiveLinkSubjectKey>& OutSubjectsList) const;` — Returns the list of subjects that constitute the virtual subject.
- L66 _private prototype_ `SLiveLinkSubjectRepresentationPicker::FLiveLinkSourceSubjectRole GetSyncSubject() const;` — Returns the subject that synchronizes the virtual subject.
- L69 _private prototype_ ``
- L72 _private member_ `TWeakObjectPtr<ULiveLinkVirtualSubject> SubjectPtr;` — The tile set being edited
- L74 _private member_ `ILiveLinkClient* Client;`
- L77 _private member_ `IDetailLayoutBuilder* MyDetailsBuilder;` — Cached reference to our details builder so we can force refresh
- L80 _private member_ `TSharedPtr<IPropertyHandle> SubjectsPropertyHandle;` — Cached property pointers
- L83 _private member_ `TArray<FSubjectEntryPtr> SubjectsListItems;` — Cached data for the subject tree UI
- L84 _private member_ `TArray<FSubjectEntryPtr> SelectedSubjectsListItems;`
- L85 _private member_ `TSharedPtr< SListView< FSubjectEntryPtr > > SelectedSubjectsListView;`
- L88 _private member_ `TSharedPtr<class SLiveLinkSubjectRepresentationPicker> SyncSubjectWidget;` — LiveLink subject picker that restricts to the subjects that make up the virtual subject.

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/SLiveLinkSubjectNameGraphPin.h` (Private)


#### class `SLiveLinkSubjectNameGraphPin`  
`class SLiveLinkSubjectNameGraphPin : public SGraphPin`  
_L8-23_
- inherits: `SGraphPin`
- L11 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkSubjectNameGraphPin)`
- L12 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L17 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L21 _private prototype_ `SLiveLinkSubjectRepresentationPicker::FLiveLinkSourceSubjectRole GetValue() const;`
- L22 _private prototype_ `void SetValue(SLiveLinkSubjectRepresentationPicker::FLiveLinkSourceSubjectRole NewValue);`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/SLiveLinkSubjectRepresentationGraphPin.h` (Private)


#### class `SLiveLinkSubjectRepresentationGraphPin`  
`class SLiveLinkSubjectRepresentationGraphPin : public SGraphPin`  
_L13-30_
- inherits: `SGraphPin`
- L16 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkSubjectRepresentationGraphPin)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj);`
- L22 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L26 _private prototype_ `SLiveLinkSubjectRepresentationPicker::FLiveLinkSourceSubjectRole GetValue() const;`
- L27 _private prototype_ `void SetValue(SLiveLinkSubjectRepresentationPicker::FLiveLinkSourceSubjectRole NewValue);`
- L29 _private member_ `FLiveLinkSubjectRepresentation SubjectRepresentation;`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Private/Sequencer/LiveLinkSequencerFilters.h` (Private)


#### class `ULiveLinkSequencerTrackFilter`  
`class ULiveLinkSequencerTrackFilter : public USequencerTrackFilterExtension`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `USequencerTrackFilterExtension`
- L15 _public prototype_ `virtual void AddTrackFilterExtensions(ISequencerTrackFilters& InFilterInterface , const TSharedRef<FFilterCategory>& InPreferredCategory , TArray<TSharedRef<FSequencerTrackFilter>>& InOutFilterList) const override;`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Public/LiveLinkClientPanelToolbar.h` (Public)


#### class `SLiveLinkClientPanelToolbar`  
`class SLiveLinkClientPanelToolbar : public SCompoundWidget`  
_L24-78_
- inherits: `SCompoundWidget`
- L26 _private function_ `SLATE_BEGIN_ARGS(SLiveLinkClientPanelToolbar) : _SourceButtonAlignment(HAlign_Fill) , _ShowPresetPicker(true) , _ShowSettings(true)`
- L33 _private prototype_ `SLATE_ARGUMENT(EHorizontalAlignment, SourceButtonAlignment) SLATE_ARGUMENT(TSharedPtr<SWindow>, ParentWindow) SLATE_ARGUMENT(TSharedPtr<SWidget>, CustomHeader) SLATE_ARGUMENT(bool, ShowPresetPicker) SLATE_ARGUMENT(bool, ShowSettings) SLATE_END_ARGS() void Construct(const FArguments& Args, FLiveLinkClient* InClient);` — Horizontal alignment of the add source button.
- L54 _private prototype_ `TSharedRef<SWidget> OnPresetGeneratePresetsMenu();` — Generates the preset combo button content.
- L57 _private prototype_ `void OnSaveAsPreset();` — Handles saving a preset to disk.
- L60 _private prototype_ `FReply OnSavePreset();` — Saves the current preset, or falls back to Save As if none has been loaded.
- L63 _private prototype_ `void OnImportPreset(const FAssetData& InPreset);` — Handles importing a preset from disk.
- L66 _private prototype_ `FReply OnRevertChanges();` — Handles reverting changes to a preset.
- L69 _private prototype_ `bool HasLoadedLiveLinkPreset() const;` — Indicates if a preset has been loaded, used to check if we can revert a preset to its original state.
- L74 _private member_ `FLiveLinkClient* Client;` — Cached livelink client.
- L77 _private member_ `TSharedPtr<SWindow> ParentWindowOverride;` — Parent window override used for creating asset dialogs when running in LiveLinkHub.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LIVELINKEDITOR_API`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Public/LiveLinkClientPanelViews.h` (Public)


#### enum `ELiveLinkEntryType`  
`enum class ELiveLinkEntryType : uint8`  
_L55-62_
- desc: Type of the subject entry in the list.
- L57 _public enumerator_ `Source`
- L58 _public enumerator_ `Subject`
- L59 _public enumerator_ `Device`
- L60 _public enumerator_ `DevicesHeader`
- L61 _public enumerator_ `SourcesHeader`

#### struct `FLiveLinkSubjectUIEntry`  
`struct FLiveLinkSubjectUIEntry`  
_L65-125_
- desc: Structure that defines a single entry in the subject UI
- L67 _public prototype_ `FLiveLinkSubjectUIEntry(const FLiveLinkSubjectKey& InSubjectKey, FLiveLinkClient* InClient, bool bIsSource = false);`
- L68 _public prototype_ `FLiveLinkSubjectUIEntry(FLiveLinkClient* InClient, ELiveLinkEntryType InType);`
- L71 _public member_ `FLiveLinkSubjectKey SubjectKey;` — Subject key
- L73 _public member_ `FLiveLinkClient* Client;` — LiveLink Client
- L75 _public member_ `TWeakObjectPtr<class ULiveLinkDevice> WeakDevice;` — Weak pointer to the device represented by this row.
- L77 _public member_ `ELiveLinkEntryType Type = ELiveLinkEntryType::Subject;` — What type of item this row represents.
- L80 _public member_ `TArray<TSharedPtr<FLiveLinkSubjectUIEntry>> Children;` — Children (if this entry represents a source instead of a specific subject
- L83 _public member_ `bool bFilteredOut = false;` — Whether the item should be hidden since it's been filtered out.
- L86 _public prototype_ `bool IsSubject() const;` — Whether the subject entry is a subject
- L88 _public prototype_ `bool IsSource() const;` — Whether the subject entry is a source
- L90 _public prototype_ `bool IsDevice() const;` — Whether this entry is a device.
- L92 _public prototype_ `bool IsVirtualSubject() const;` — Whether the subject is virtual
- L94 _public prototype_ `UObject* GetSettings() const;` — Get the subject or source settings
- L96 _public prototype_ `bool IsSubjectEnabled() const;` — Whether the subject is enabled
- L98 _public prototype_ `bool IsSubjectValid() const;` — Whether the subject is valid
- L100 _public prototype_ `bool IsPlaybackSource() const;` — Whether the entry is a playback source.
- L102 _public prototype_ `void SetSubjectEnabled(bool bIsEnabled);` — Enable or disable a subject
- L104 _public prototype_ `FText GetItemText() const;` — Get a textual representation of the ui entry
- L106 _public prototype_ `FText GetMachineName() const;` — Get the name of the machine that hosts this source or device.
- L108 _public prototype_ `TSubclassOf<ULiveLinkRole> GetItemRole() const;` — Get the livelink role of this entry
- L110 _public prototype_ `TSubclassOf<ULiveLinkRole> GetItemTranslatedRole() const;` — Get the translated role for this subject (if translating rebroadcast subjects).
- L112 _public prototype_ `void RemoveFromClient() const;` — Remove the subject or source from the livelink client
- L114 _public prototype_ `void PauseSubject();` — Pause or unpause a subject if it's already paused
- L116 _public prototype_ `bool IsPaused() const;` — Returns whether a subject is currently paused.
- L118 _public prototype_ `void GetFilterText(TArray<FString>& OutStrings) const;` — Get item string representation for filtering.
- L122 _private member_ `bool bIsVirtualSubject = false;` — Whether the subject is virtual
- L124 _private member_ `bool bIsPlaybackSource = false;` — Whether this is a playback source, used to display a different icon when the source is in playback.

#### struct `FLiveLinkSourceUIEntry`  
`struct FLiveLinkSourceUIEntry`  
_L128-168_
- desc: Structure that defines a single entry in the source UI
- L131 _public function_ `FLiveLinkSourceUIEntry(FGuid InEntryGuid, FLiveLinkClient* InClient) : EntryGuid(InEntryGuid) , Client(InClient)`
- L137 _public prototype_ `FGuid GetGuid() const;` — Get the guid of the source
- L139 _public prototype_ `FText GetSourceType() const;` — Get the type of the source
- L141 _public prototype_ `FText GetMachineName() const;` — Get the machine name of the source
- L143 _public prototype_ `FText GetStatus() const;` — Get the source's status
- L145 _public prototype_ `ULiveLinkSourceSettings* GetSourceSettings() const;` — Get the source's settings
- L147 _public prototype_ `void RemoveFromClient() const;` — Remove the source from the client
- L149 _public prototype_ `FText GetDisplayName() const;` — Get the display name of the source
- L151 _public prototype_ `FText GetToolTip() const;` — Get the tooltip of the source
- L153 _public function_ `void GetFilterText(TArray<FString>& OutStrings) const` — Get item string representation for filtering.
- L160 _public member_ `bool bFilteredOut = false;` — Whether the item should be hidden since it's been filtered out.
- L164 _private member_ `FGuid EntryGuid;` — GUID of the source
- L166 _private member_ `FLiveLinkClient* Client = nullptr;` — Pointer to the livelink client

#### class `UE::LiveLink::SLiveLinkListView`  
`template <typename ListType, typename ListElementType> class SLiveLinkListView : public ListType`  
_L174-213_
- inherits: `ListType`
- desc: Base class for live link list/tree views, handles removing list element by pressing delete.
- L177 _public function_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override`
- L212 _public member_ `TAttribute<bool> bReadOnly;` — Whether the panel is in read-only mode or not.

#### class `SLiveLinkSourceListView`  
`class SLiveLinkSourceListView : public UE::LiveLink::SLiveLinkListView<SListView<FLiveLinkSourceUIEntryPtr>, FLiveLinkSourceUIEntryPtr>`  
_L216-225_
- inherits: `UE::LiveLink::SLiveLinkListView<SListView<FLiveLinkSourceUIEntryPtr>,FLiveLinkSourceUIEntryPtr>`
- L219 _public function_ `void Construct(const FArguments& InArgs, TAttribute<bool> bInReadOnly)`

#### class `SLiveLinkSubjectsTreeView`  
`class SLiveLinkSubjectsTreeView : public UE::LiveLink::SLiveLinkListView<STreeView<FLiveLinkSubjectUIEntryPtr>, FLiveLinkSubjectUIEntryPtr>`  
_L227-235_
- inherits: `UE::LiveLink::SLiveLinkListView<STreeView<FLiveLinkSubjectUIEntryPtr>,FLiveLinkSubjectUIEntryPtr>`
- L230 _public function_ `void Construct(const FArguments& InArgs, TAttribute<bool> bInReadOnly)`

#### class `FLiveLinkSubjectsView`  
`class FLiveLinkSubjectsView : public TSharedFromThis<FLiveLinkSubjectsView>`  
_L237-336_
- inherits: `TSharedFromThis<FLiveLinkSubjectsView>`
- L240 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnSubjectSelectionChanged, FLiveLinkSubjectUIEntryPtr, ESelectInfo::Type);`
- L242 _public typedef_ `using FFilterType = FLiveLinkSubjectUIEntryPtr;`
- L243 _public typedef_ `using FMediaTreeFilter = TTextFilter<FFilterType>;`
- L251 _public prototype_ `FLiveLinkSubjectsView(FOnSubjectSelectionChanged InOnSubjectSelectionChanged, const TSharedPtr<FUICommandList>& InCommandList, TAttribute<bool> bInReadOnly);`
- L253 _public prototype_ `FLiveLinkSubjectsView(FOnSubjectSelectionChanged InOnSubjectSelectionChanged, const TSharedPtr<FUICommandList>& InCommandList, const FSubjectsViewArgs& InArgs);`
- L256 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(FLiveLinkSubjectUIEntryPtr InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Helper functions for building the subject tree UI
- L258 _public prototype_ `void GetChildrenForInfo(FLiveLinkSubjectUIEntryPtr InInfo, TArray< FLiveLinkSubjectUIEntryPtr >& OutChildren);` — Get a subjectsview's children
- L260 _public prototype_ `void OnSubjectSelectionChanged(FLiveLinkSubjectUIEntryPtr SubjectEntry, ESelectInfo::Type SelectInfo);` — Handle subject selection changed
- L262 _public prototype_ `TSharedPtr<SWidget> OnOpenVirtualSubjectContextMenu(TSharedPtr<FUICommandList> InCommandList);` — Handler for the subject tree context menu opening
- L264 _public prototype_ `bool CanRemoveSubject() const;` — Return whether a subject can be removed
- L266 _public prototype_ `void RefreshSubjects();` — Refresh the list of subjects using the livelink client.
- L268 _public prototype_ `bool CanPauseSubject() const;` — Return whether a subject can be paused
- L270 _public prototype_ `void HandlePauseSubject();` — Pauses/Unpauses a subject
- L272 _public prototype_ `TSharedRef<SWidget> GetWidget();` — Get the subjects list widget
- L287 _private prototype_ `void SaveSelection(TArray<FSavedSelection>& OutSavedSelection) const;` — Saves the current tree view selection into OutSavedSelection.
- L289 _private prototype_ `void RestoreSelection(const TArray<FSavedSelection>& InSavedSelection);` — Restores a previously saved selection by matching entries in the rebuilt tree.
- L291 _private prototype_ `void RestoreSelectionForItem(const FLiveLinkSubjectUIEntryPtr& Item, const TArray<FSavedSelection>& InSavedSelection);` — Selects Item if it matches any entry in InSavedSelection.
- L293 _private prototype_ `void CreateCombinedTreeView(const TSharedPtr<FUICommandList>& InCommandList);`
- L295 _private prototype_ `FText GetPauseSubjectLabel() const;` — Get the label for the pause subject context menu entry.
- L297 _private prototype_ `FText GetPauseSubjectToolTip() const;` — Get the tooltip for the pause subject context menu entry.
- L299 _private prototype_ `bool IsSelectedSubjectPaused() const;` — Returns whether the selected subject is paused.
- L301 _private prototype_ `bool CanRemoveDevice() const;` — Returns whether a device can be removed.
- L303 _private prototype_ `bool CanRemoveSource() const;` — Returns whether a source can be removed.
- L305 _private prototype_ `bool HasAnySources() const;` — Returns whether there are any sources in the list.
- L307 _private prototype_ `TSharedPtr<SWidget> OnCombinedListOpenContextMenu(TSharedPtr<FUICommandList> InCommandList);` — Opens a context menu with options relevant to the selected items.
- L309 _private prototype_ `TSharedRef<SWidget> OnGenerateAddMenuEntries();` — Populates entries for the Add combo button.
- L311 _private prototype_ `void InitializeFilters();` — Initialize default filters for the list view.
- L313 _private prototype_ `void OnFilterChanged();` — Triggers a refresh of the filtered elements when the filter changes.
- L315 _private member_ `TArray<TSharedRef<FFilterBase<FFilterType>>> CustomFilters;` — Sources, Subjects and Devices filters.
- L317 _private member_ `TSharedPtr<SLiveLinkFilterBar<FFilterType>> FilterBar;` — Filter bar widget. Necessary to create the Add filter button, but it's not actually displayed in the LiveLink UI.
- L321 _public member_ `TSharedPtr<class SLiveLinkSubjectsTreeView> SubjectsTreeView;` — Subject tree widget
- L323 _public member_ `TArray<FLiveLinkSubjectUIEntryPtr> SubjectData;` — Subject tree items
- L325 _public member_ `TArray<FLiveLinkSubjectUIEntryPtr> FilteredList;` — Filtered subject tree items
- L327 _public member_ `FOnSubjectSelectionChanged SubjectSelectionChangedDelegate;` — Subject Selection Changed delegate
- L329 _public member_ `TAttribute<bool> bReadOnly;` — Returns whether the panel is in read-only mode.
- L331 _public member_ `TSharedPtr<SLiveLinkFilterSearchBox<FLiveLinkSubjectUIEntryPtr>> FilterSearchBox;` — Filter search box.
- L335 _private member_ `bool bShowDevices = false;` — Whether to show devices in the menu. (Disabled by default in editor)

#### struct `FLiveLinkSubjectsView::FSubjectsViewArgs`  
`struct FSubjectsViewArgs`  
_L245-249_
- L247 _public member_ `TAttribute<bool> bInReadOnly;`
- L248 _public member_ `bool bInShowDevices = false;`

#### struct `FLiveLinkSubjectsView::FSavedSelection`  
`struct FSavedSelection`  
_L276-284_
- desc: Captures the identity of a selected item so it can be matched after the list is rebuilt.
- L279 _public member_ `FLiveLinkSubjectKey SubjectKey;` — Full subject key (used for subject and source matching).
- L281 _public member_ `ELiveLinkEntryType Type;` — Type of the entry.
- L283 _public member_ `TWeakObjectPtr<class ULiveLinkDevice> WeakDevice;` — Weak reference to the device, used to match device entries.

#### class `FLiveLinkSourcesView`  
`class FLiveLinkSourcesView : public TSharedFromThis<FLiveLinkSourcesView>, public FGCObject`  
_L338-403_
- inherits: `TSharedFromThis<FLiveLinkSourcesView>,FGCObject`
- L341 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnSourceSelectionChanged, FLiveLinkSourceUIEntryPtr, ESelectInfo::Type);`
- L343 _public prototype_ `FLiveLinkSourcesView(FLiveLinkClient* InLiveLinkClient, TSharedPtr<FUICommandList> InCommandList, TAttribute<bool> bInReadOnly, FOnSourceSelectionChanged InOnSourceSelectionChanged);`
- L344 _public prototype_ `~FLiveLinkSourcesView();`
- L347 _public function_ `virtual FString GetReferencerName() const override`
- L352 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L359 _public prototype_ `TSharedRef<SWidget> GetWidget();` — Get list view widget
- L361 _public prototype_ `void RefreshSourceData(bool bRefreshUI);` — Gather information about all sources and update the list view
- L363 _public prototype_ `TSharedRef<ITableRow> MakeSourceListViewWidget(FLiveLinkSourceUIEntryPtr Entry, const TSharedRef<STableViewBase>& OwnerTable) const;` — Handler that creates a widget row for a given ui entry
- L365 _public prototype_ `TSharedPtr<SWidget> OnSourceConstructContextMenu(TSharedPtr<FUICommandList> InCommandList);` — Handles constructing a context menu for the sources
- L367 _public prototype_ `bool CanRemoveSource();` — Return whether a source can be removed
- L369 _public prototype_ `void HandleRemoveSource();` — Removes a livelink source from the livelink client
- L371 _public prototype_ `void OnPropertyChanged(const FPropertyChangedEvent& InEvent);` — Callback when property changes on source settings
- L373 _public prototype_ `void OnSourceListSelectionChanged(FLiveLinkSourceUIEntryPtr Entry, ESelectInfo::Type SelectionType) const;` — Handle selection change, triggering the OnSourceSelectionChangedDelegate delegate.
- L376 _private prototype_ `void CreateSourcesListView(const TSharedPtr<FUICommandList>& InCommandList);` — Create the sources list view
- L378 _private prototype_ `TSharedRef<SWidget> OnGenerateSourceMenu();` — Populates the source combo menu widget content.
- L382 _public member_ `TArray<FLiveLinkSourceUIEntryPtr> SourceData;` — Holds the data that will be displayed in the list view
- L384 _public member_ `TSharedPtr<SLiveLinkSourceListView> SourcesListView;` — Holds the sources list view widget
- L386 _public member_ `FLiveLinkClient* Client;` — LiveLink Client
- L388 _public member_ `FOnSourceSelectionChanged OnSourceSelectionChangedDelegate;` — Source selection changed delegate
- L390 _public member_ `TAttribute<bool> bReadOnly;` — Returns whether the panel is in read-only mode.
- L394 _private member_ `TArray<FLiveLinkSourceUIEntryPtr> FilteredList;` — Filtered list resulting from applying the text filter.
- L396 _private member_ `TSharedPtr<SWidget> HostWidget;` — Holds the searchbox widget and the source list.
- L398 _private member_ `FTSTicker::FDelegateHandle TickHandle;` — Handle to the tick delegate.
- L400 _private member_ `TArray<TObjectPtr<ULiveLinkSourceFactory>> Factories;` — Holds all the LiveLink souce factories.
- L402 _private member_ `TSharedPtr<SLiveLinkFilterSearchBox<FLiveLinkSourceUIEntryPtr>> FilterSearchBox;` — Filter search box.

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API LIVELINKEDITOR_API`
- L42 _typedef_ `typedef TSharedPtr<FLiveLinkSourceUIEntry> FLiveLinkSourceUIEntryPtr;`
- L43 _typedef_ `typedef TSharedPtr<FLiveLinkSubjectUIEntry> FLiveLinkSubjectUIEntryPtr;`
- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace LiveLink` (scope `UE`)
- L48 _prototype_ `TSharedPtr<IDetailsView> CreateSourcesDetailsView(const TSharedPtr<FLiveLinkSourcesView>& InSourcesView, const TAttribute<bool>& bInReadOnly);` (scope `UE::LiveLink`) — `UE_DEPRECATED(5.8, "Use the other CreateSourcesDetailsView method")`
- L49 _prototype_ `TSharedPtr<IDetailsView> CreateSourcesDetailsView(FOnFinishedChangingProperties InChangedPropertiesDelegate, const TAttribute<bool>& bInReadOnly);` (scope `UE::LiveLink`)
- L50 _prototype_ `TSharedPtr<SLiveLinkDataView> CreateSubjectsDetailsView(FLiveLinkClient* InLiveLinkClient, const TAttribute<bool>& bInReadOnly);` (scope `UE::LiveLink`)
- L51 _prototype_ `TSharedPtr<IDetailsView> CreateDevicesDetailsView(FOnFinishedChangingProperties OnFinishedChangingProperties, const TAttribute<bool>& bInReadOnly);` (scope `UE::LiveLink`)
- L170 _namespace_ `namespace UE`
- L170 _namespace_ `namespace LiveLink` (scope `UE`)
- L240 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSubjectSelectionChanged, FLiveLinkSubjectUIEntryPtr, ESelectInfo::Type);`
- L341 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSourceSelectionChanged, FLiveLinkSourceUIEntryPtr, ESelectInfo::Type);`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Public/LiveLinkEditorSettings.h` (Public)


#### class `ULiveLinkEditorSettings`  
`class ULiveLinkEditorSettings : public UObject`  
_L13-21_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Editor preferences settings for LiveLink.
- L20 _public member_ `bool bReadOnly = false;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink")` — Whether the livelink panel should be in read-only mode.

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Public/LiveLinkPanelController.h` (Public)


#### class `FLiveLinkPanelController`  
`class FLiveLinkPanelController : public TSharedFromThis<FLiveLinkPanelController>`  
_L31-115_
- inherits: `TSharedFromThis<FLiveLinkPanelController>`
- desc: Handles callback connections between the sources, subjects and details views.
- L34 _public prototype_ `FLiveLinkPanelController(TAttribute<bool> bInReadOnly = false);`
- L35 _public prototype_ `~FLiveLinkPanelController();`
- L37 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSubjectSelectionChanged, const FLiveLinkSubjectKey&);`
- L39 _public function_ `FOnSubjectSelectionChanged& OnSubjectSelectionChanged()` — Subject Selection changed callback.
- L45 _public prototype_ `TSharedRef<SWidget> GetCombinedDetailsWidget();` — Get the widget displaying details for the selected item, whether it's a Source, Subject or Device.
- L49 _private prototype_ `void BindCommands();` — Bind live link commands
- L51 _private prototype_ `void OnSourcesChangedHandler();` — Handles the source collection changing.
- L53 _private prototype_ `void OnSubjectsChangedHandler();` — Handles the subject collection changing.
- L55 _private prototype_ `bool HasSource() const;` — Returns whether there is a source in the list.
- L57 _private prototype_ `void HandleRemoveSource();` — Handles the remove source command.
- L59 _private prototype_ `void HandleRemoveAllSources();` — Handles the remove all sources command.
- L61 _private prototype_ `bool CanRemoveSource() const;` — Returns whether a source could be removed.
- L63 _private prototype_ `bool CanRemoveSubject() const;` — Returns whether a subject can be removed.
- L65 _private prototype_ `bool CanRemoveDevice() const;` — Returns whether a device can be removed.
- L67 _private prototype_ `bool CanPauseSubject() const;` — Returns whethera subject can be paused
- L69 _private prototype_ `void HandlePauseSubject();` — Pauses/Unpauses a subject.
- L71 _private prototype_ `void HandleRemoveSubject();` — Handles the remove subject command.
- L73 _private prototype_ `void HandleRemoveDevice();` — Handles the remove device command.
- L75 _private prototype_ `void RebuildSubjectList();` — Recreates the subject list data behind the tree view.
- L77 _private prototype_ `void OnSubjectSelectionChangedHandler(FLiveLinkSubjectUIEntryPtr SubjectEntry, ESelectInfo::Type SelectInfo);` — Hadnles subject selection changing.
- L79 _private prototype_ `void OnFinishedChangingDeviceProperties(const FPropertyChangedEvent& InPropertyChangedEvent);` — Handles triggering the modified device's OnSettingChanged method.
- L81 _private prototype_ `void OnFinishedChangingSourceProperties(const FPropertyChangedEvent& InPropertyChangedEvent);` — Handles triggering LiveLinkClient's OnPropertyChanged method for the modified source.
- L83 _private prototype_ `int32 GetCombinedDetailWidgetIndex() const;` — Returns the index of the details widget that should be shown, according to the current selection.
- L88 _public member_ `TSharedPtr<class FLiveLinkSourcesView> SourcesView;` — `UE_DEPRECATED(5.8, "Use the subjects view instead.")` — Sources view
- L90 _public member_ `TSharedPtr<FLiveLinkSubjectsView> SubjectsView;` — Subjects view
- L92 _public member_ `TSharedPtr<IDetailsView> SourcesDetailsView;` — Reference to connection settings struct details panel
- L94 _public member_ `TSharedPtr<SLiveLinkDataView> SubjectsDetailsView;` — Reference to the data value struct details panel
- L96 _public member_ `TSharedPtr<IDetailsView> DevicesDetailsView;` — Reference to device settings details panel
- L98 _public member_ `FLiveLinkClient* Client;` — LiveLink Client
- L100 _public member_ `FDelegateHandle OnSourcesChangedHandle;` — Handle to delegate when client sources list has changed
- L102 _public member_ `FDelegateHandle OnSubjectsChangedHandle;` — Handle to delegate when a client subjects list has changed
- L104 _public member_ `mutable bool bSelectionChangedGuard = false;` — Guard from reentrant selection
- L106 _public member_ `TSharedPtr<FUICommandList> CommandList;` — Command list
- L108 _public member_ `FOnSubjectSelectionChanged SubjectSelectionChangedDelegate;` — Delegate called when the subject selection changes
- L112 _private member_ `FDelegateHandle DeviceAddedHandle;` — Delegate called when a device is added.
- L114 _private member_ `FDelegateHandle DeviceRemovedHandle;` — Delegate called when a device is removed.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LIVELINKEDITOR_API`
- L25 _namespace_ `namespace ESelectInfo`
- L26 _typedef_ `typedef TSharedPtr<FLiveLinkSourceUIEntry> FLiveLinkSourceUIEntryPtr;`
- L27 _typedef_ `typedef TSharedPtr<FLiveLinkSubjectUIEntry> FLiveLinkSubjectUIEntryPtr;`
- L37 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSubjectSelectionChanged, const FLiveLinkSubjectKey&);`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Public/SLiveLinkBoneSelectionWidget.h` (Public)


#### class `SLiveLinkBoneTreeMenu`  
`class SLiveLinkBoneTreeMenu : public SCompoundWidget`  
_L24-96_
- inherits: `SCompoundWidget`
- L36 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkBoneTreeMenu) : _OnBoneSelectionChanged()`
- L40 _public prototype_ `SLATE_ARGUMENT(FText, Title) SLATE_ARGUMENT(FName, SelectedBone) SLATE_EVENT(FOnBoneSelectionChanged, OnBoneSelectionChanged) SLATE_END_ARGS();`
- L50 _public prototype_ `void Construct(const FArguments& InArgs, TOptional<FLiveLinkSkeletonStaticData> SkeletonStaticData);` — Construct this widget @param	InArgs	The declaration data for this widget
- L53 _public prototype_ `TSharedPtr<SWidget> GetFilterTextWidget();` — Get the filter text widget, e.g. for focus
- L57 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget interface
- L60 _private prototype_ `void RebuildBoneList(const FName& SelectedBone);` — Using the current filter, repopulate the tree view
- L63 _private prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(TSharedPtr<FBoneNameInfo> InInfo, const TSharedRef<STableViewBase>& OwnerTable);` — Make a single tree row widget
- L66 _private prototype_ `void GetChildrenForInfo(TSharedPtr<FBoneNameInfo> InInfo, TArray< TSharedPtr<FBoneNameInfo> >& OutChildren);` — Get the children for the provided bone info
- L69 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);` — Called when the user changes the search filter
- L72 _private prototype_ `void OnSelectionChanged(TSharedPtr<SLiveLinkBoneTreeMenu::FBoneNameInfo> BoneInfo, ESelectInfo::Type SelectInfo);` — Handle the tree view selection changing
- L75 _private prototype_ `void SelectBone(TSharedPtr<SLiveLinkBoneTreeMenu::FBoneNameInfo> BoneInfo);` — Select a specific bone, helper for UI handler functions
- L78 _private member_ `TArray<TSharedPtr<FBoneNameInfo>> SkeletonTreeInfo;` — Tree info entries for bone picker
- L80 _private member_ `TArray<TSharedPtr<FBoneNameInfo>> SkeletonTreeInfoFlat;` — Mirror of SkeletonTreeInfo but flattened for searching
- L83 _private member_ `FText FilterText;` — Text to filter bone tree with
- L86 _private member_ `TSharedPtr<STreeView<TSharedPtr<FBoneNameInfo>>> TreeView;` — Tree view used in the button menu
- L89 _private member_ `TSharedPtr<SSearchBox> FilterTextWidget;` — Filter text widget
- L92 _private member_ `FOnBoneSelectionChanged OnSelectionChangedDelegate;` — Delegate called when a bone is selected.
- L95 _private member_ `FLiveLinkSkeletonStaticData SkeletonStaticData;` — Static data used to populate the bone list.

#### struct `SLiveLinkBoneTreeMenu::FBoneNameInfo`  
`struct FBoneNameInfo`  
_L28-34_
- desc: Storage object for bone hierarchy
- L30 _public function_ `FBoneNameInfo(FName Name) : BoneName(Name)`
- L32 _public member_ `FName BoneName;`
- L33 _public member_ `TArray<TSharedPtr<FBoneNameInfo>> Children;`

#### class `SLiveLinkBoneSelectionWidget`  
`class SLiveLinkBoneSelectionWidget : public SCompoundWidget`  
_L98-146_
- inherits: `SCompoundWidget`
- L102 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkBoneSelectionWidget) : _OnBoneSelectionChanged() , _OnGetSelectedBone()`
- L108 _public prototype_ `SLATE_EVENT(FOnBoneSelectionChanged, OnBoneSelectionChanged);` — set selected bone name
- L111 _public prototype_ `SLATE_EVENT(FGetSelectedBone, OnGetSelectedBone);` — get selected bone name
- L112 _public prototype_ `SLATE_END_ARGS();`
- L119 _public prototype_ `void Construct(const FArguments& InArgs, const FLiveLinkSubjectKey& InSubjectKey);` — Construct this widget @param	InArgs	The declaration data for this widget
- L122 _public prototype_ `void SetSubject(const FLiveLinkSubjectKey& InSubjectKey);` — Set the subject for which we will list the bones.
- L125 _public prototype_ `FLiveLinkSkeletonStaticData MakeStaticDataFromTranslator(const FLiveLinkSubjectKey& SubjectKey) const;` — Utility method to create fake static data from a frame translator.
- L130 _private prototype_ `TSharedRef<SWidget> CreateSkeletonWidgetMenu();` — Creates the combo button menu when clicked
- L132 _private prototype_ `void OnSelectionChanged(FName BoneName);` — Called when the user selects a bone name
- L135 _private prototype_ `FText GetCurrentBoneName() const;` — Gets the current bone name, used to get the right name for the combo button
- L138 _private member_ `TSharedPtr<SComboButton> BonePickerButton;` — Base combo button
- L141 _private member_ `FLiveLinkSubjectKey SubjectKey;` — Subject that for which we are selecting a bone.
- L144 _private member_ `FOnBoneSelectionChanged OnBoneSelectionChanged;` — Delegates
- L145 _private member_ `FGetSelectedBone OnGetSelectedBone;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API LIVELINKEDITOR_API`
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBoneSelectionChanged, FName);`
- L21 _prototype_ `DECLARE_DELEGATE_OneParam(FOnBoneSelectionChanged, FName);`
- L22 _delegate_ `DECLARE_DELEGATE_RetVal(FName, FGetSelectedBone);`
- L22 _prototype_ `DECLARE_DELEGATE_RetVal(FName, FGetSelectedBone);`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Public/SLiveLinkDataView.h` (Public)


#### class `SLiveLinkDataView`  
`class SLiveLinkDataView : public SCompoundWidget`  
_L18-64_
- inherits: `SCompoundWidget`
- L21 _private typedef_ `using Super = SCompoundWidget;`
- L24 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkDataView) : _ReadOnly(false)`
- L27 _public prototype_ `SLATE_ATTRIBUTE(bool, ReadOnly) SLATE_END_ARGS() void Construct(const FArguments& Args, FLiveLinkClient* InClient);`
- L32 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L34 _public prototype_ `void SetSubjectKey(FLiveLinkSubjectKey InSubjectKey);`
- L35 _public function_ `FLiveLinkSubjectKey GetSubjectKey() const`
- L37 _public function_ `void SetRefreshDelay(double DelaySeconds)`
- L38 _public function_ `double GetRefreshDelay() const`
- L48 _private prototype_ `void OnPropertyChanged(const FPropertyChangedEvent& InEvent);`
- L49 _private prototype_ `int32 GetDetailWidgetIndex() const;`
- L50 _private prototype_ `void OnSelectDetailWidget(EDetailType InDetailType);`
- L51 _private function_ `bool IsSelectedDetailWidget(EDetailType InDetailType) const`
- L52 _private function_ `bool CanEditRefreshDelay() const`
- L53 _private function_ `void SetRefreshDelayInternal(double InDelaySeconds, ETextCommit::Type)`
- L56 _private member_ `FLiveLinkClient* Client;`
- L57 _private member_ `FLiveLinkSubjectKey SubjectKey;`
- L58 _private member_ `double LastUpdateSeconds;`
- L59 _private member_ `double UpdateDelay;`
- L60 _private member_ `EDetailType DetailType;`
- L62 _private member_ `TSharedPtr<IStructureDetailsView> StructureDetailsView;`
- L63 _private member_ `TSharedPtr<IDetailsView> SettingsDetailsView;`

#### enum `SLiveLinkDataView::EDetailType`  
`enum class EDetailType : uint32`  
_L41-46_
- L43 _public enumerator_ `Property`
- L44 _public enumerator_ `StaticData`
- L45 _public enumerator_ `FrameData`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINKEDITOR_API`
- L11 _namespace_ `namespace ETextCommit`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Public/SLiveLinkFilterSearchBox.h` (Public)


#### class `SLiveLinkFilterSearchBox`  
`template <typename ItemType> class SLiveLinkFilterSearchBox : public SCompoundWidget`  
_L28-187_
- inherits: `SCompoundWidget`
- desc: Wrapper around a SSearchBox that provides utility to filter items in a list or tree view.
- L31 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnGatherItems, TArray<ItemType>& );`
- L32 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnUpdateFilteredList, const TArray<ItemType>& );`
- L34 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkFilterSearchBox)`
- L36 _public prototype_ `SLATE_ARGUMENT(TArray<ItemType>*, ItemSource);` — The list item for this row
- L37 _public prototype_ `SLATE_EVENT(FOnGatherItems, OnGatherItems);`
- L38 _public prototype_ `SLATE_EVENT(FOnUpdateFilteredList, OnUpdateFilteredList);`
- L39 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SBasicFilterBar<ItemType>> InFilterBar = nullptr)`
- L62 _public function_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)`
- L72 _public function_ `void Update()` — Trigger a deferred update of the filtered items.
- L79 _private function_ `void OnSearchTextChanged(const FText& InFilterText)` — Handle search text being changed by the user, triggers a deferred update.
- L88 _private function_ `bool PassesAnyFilterBarFilter(const ItemType& InItem)` — Returns whether an item passes any filter bar filter.
- L109 _private function_ `bool UpdateVisibleChildren(ItemType& Item)` — Updates the bFilteredOut field on the item and its children, then returns if the item or any of its child is visible.
- L127 _private function_ `void UpdateFilteredItemSource()` — Updates the filtered item source to match the SearchBox filter.
- L163 _private function_ `void GetItemString(const ItemType InItem, TArray<FString>& OutStrings)` — Get string representation from a subject UI entry.
- L170 _private member_ `TArray<ItemType>* ItemSource = nullptr;` — Ptr to the unfiltered item source. Used to update the filtered item list when no filtering is applied.
- L172 _private member_ `TArray<ItemType> FilteredItemSource;` — Internal filtered item source.
- L174 _private member_ `bool bUpdateFilteredItems = true;` — Handles deferred updates to the list filter.
- L176 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — Holds the search box widget.
- L178 _private typedef_ `using FEntryTextFilter = TTextFilter<ItemType>;`
- L180 _private member_ `TSharedPtr<FEntryTextFilter> SearchTextFilter;` — Text filter used for the subject list.
- L183 _private member_ `TSharedPtr<SBasicFilterBar<ItemType>> FilterBar;` — Optional filter bar used to filter items according to a predefined list of filters.
- L186 _private member_ `FOnUpdateFilteredList OnUpdateFilteredList;` — Delegate called to the owner of this widget to inform them that the filtered list has been updated.

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGatherItems, TArray<ItemType>& );`
- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FOnUpdateFilteredList, const TArray<ItemType>& );`
- L148 _function_ `` (scope `SLiveLinkFilterSearchBox::UpdateFilteredItemSource`)
- L151 _function_ `}, [](const ItemType& Item)` (scope `SLiveLinkFilterSearchBox::UpdateFilteredItemSource`)

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Public/SLiveLinkSubjectRepresentationPicker.h` (Public)


#### class `SLiveLinkSubjectRepresentationPicker`  
`class SLiveLinkSubjectRepresentationPicker : public SCompoundWidget`  
_L36-156_
- inherits: `SCompoundWidget`
- desc: A widget which allows the user to enter a subject name or discover it from a drop menu.
- L60 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, FLiveLinkSourceSubjectRole);`
- L62 _public function_ `SLATE_BEGIN_ARGS(SLiveLinkSubjectRepresentationPicker) : _ComboButtonStyle(&FCoreStyle::Get().GetWidgetStyle< FComboButtonStyle >("ComboButton")) , _ButtonStyle(nullptr) , _ForegroundColor(FCoreStyle::Get().GetSlateColor("InvertedForeground")) , _ContentPadding(FMargin(2.f, 0.f)) , _HasMultipleValues(false) , _ShowSource(false) , _ShowRole(false) , _Font()`
- L74 _public prototype_ `SLATE_STYLE_ARGUMENT(FComboButtonStyle, ComboButtonStyle) SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle) SLATE_ATTRIBUTE(FSlateColor, ForegroundColor) SLATE_ATTRIBUTE(FMargin, ContentPadding) SLATE_ATTRIBUTE(FLiveLinkSourceSubjectRole, Value) SLATE_EVENT(FOnValueChanged, OnValueChanged) SLATE_ATTRIBUTE(bool, HasMultipleValues) SLATE_ARGUMENT(bool, ShowSource) SLATE_ARGUMENT(bool, ShowRole) SLATE_ATTRIBUTE(FSlateFontInfo, Font) SLATE_EVENT(FOnGetSubjects, OnGetSubjects);` — The visual style of the combo button
- L106 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L116 _public prototype_ `FLiveLinkSourceSubjectRole GetCurrentValue() const;` — Access the current value of this picker
- L119 _private prototype_ `FText GetSourceNameValueText() const;`
- L120 _private prototype_ `FText GetSubjectNameValueText() const;`
- L121 _private prototype_ `const FSlateBrush* GetRoleIcon() const;`
- L122 _private prototype_ `FText GetRoleText() const;`
- L124 _private prototype_ `TSharedRef<SWidget> BuildMenu();`
- L125 _private prototype_ `FText GetPresetSelectedText() const;`
- L126 _private prototype_ `FSlateColor GetSelectPresetForegroundColor() const;`
- L127 _private prototype_ `FReply ClearCurrentPreset();`
- L128 _private prototype_ `bool HasCurrentPreset() const;`
- L130 _private prototype_ `TSharedRef<ITableRow> MakeSubjectRepListViewWidget(FLiveLinkSubjectRepresentationPickerEntryPtr Entry, const TSharedRef<STableViewBase>& OwnerTable) const;`
- L131 _private prototype_ `void OnSubjectRepListSelectionChanged(FLiveLinkSubjectRepresentationPickerEntryPtr Entry, ESelectInfo::Type SelectionType);`
- L133 _private prototype_ `TSharedRef<SWidget> BuildPresetSubMenu();`
- L134 _private prototype_ `void NewPresetSelected(const FAssetData& AssetData);`
- L135 _private prototype_ `void OnComboTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit);`
- L136 _private prototype_ `void SetValue(const FLiveLinkSourceSubjectRole& InValue);`
- L138 _private prototype_ `void BuildSubjectRepDataList();`
- L141 _private member_ `TWeakObjectPtr<ULiveLinkPreset> SelectedLiveLinkPreset;`
- L142 _private member_ `TWeakPtr<SComboButton> PickerComboButton;`
- L143 _private member_ `TWeakPtr<SComboButton> SelectPresetComboButton;`
- L144 _private member_ `TWeakPtr<SListView<FLiveLinkSubjectRepresentationPickerEntryPtr>> SubjectListView;`
- L145 _private member_ `TArray<FLiveLinkSubjectRepresentationPickerEntryPtr> SubjectRepData;`
- L147 _private member_ `FText CachedSourceType;`
- L148 _private member_ `TAttribute<FLiveLinkSourceSubjectRole> ValueAttribute;`
- L149 _private member_ `FOnValueChanged OnValueChangedDelegate;`
- L150 _private member_ `TAttribute<bool> HasMultipleValuesAttribute;`
- L151 _private member_ `bool bShowSource;`
- L152 _private member_ `bool bShowRole;`
- L155 _private member_ `FOnGetSubjects GetSubjectsDelegate;` — Delegate used to retrieve a custom list of subjects.

#### struct `SLiveLinkSubjectRepresentationPicker::FLiveLinkSourceSubjectRole`  
`struct FLiveLinkSourceSubjectRole`  
_L39-58_
- L41 _public prototype_ `FLiveLinkSourceSubjectRole() = default;`
- L42 _public function_ `explicit FLiveLinkSourceSubjectRole(FLiveLinkSubjectRepresentation InSubjectRepresentation) : Subject(InSubjectRepresentation.Subject), Role(InSubjectRepresentation.Role)`
- L45 _public function_ `explicit FLiveLinkSourceSubjectRole(FLiveLinkSubjectKey InSubjectKey) : Source(InSubjectKey.Source), Subject(InSubjectKey.SubjectName)`
- L48 _public function_ `FLiveLinkSourceSubjectRole(FGuid InSource, FLiveLinkSubjectName InSubject, TSubclassOf<ULiveLinkRole> InRole) : Source(InSource), Subject(InSubject), Role(InRole)`
- L52 _public function_ `FLiveLinkSubjectRepresentation ToSubjectRepresentation() const`
- L53 _public function_ `FLiveLinkSubjectKey ToSubjectKey() const`
- L55 _public member_ `FGuid Source;`
- L56 _public member_ `FLiveLinkSubjectName Subject;`
- L57 _public member_ `TSubclassOf<ULiveLinkRole> Role;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LIVELINKEDITOR_API`
- L15 _namespace_ `namespace ESelectInfo`
- L16 _namespace_ `namespace ETextCommit`
- L28 _typedef_ `typedef TSharedPtr<FLiveLinkSubjectRepresentationPickerEntry> FLiveLinkSubjectRepresentationPickerEntryPtr;`
- L30 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGetSubjects, TArray<FLiveLinkSubjectKey>& );`
- L30 _prototype_ `DECLARE_DELEGATE_OneParam(FOnGetSubjects, TArray<FLiveLinkSubjectKey>& );`
- L60 _delegate_ `DECLARE_DELEGATE_OneParam(FOnValueChanged, FLiveLinkSourceSubjectRole);`

### `Plugins/Animation/LiveLink/Source/LiveLinkEditor/Public/VirtualSubjects/LiveLinkBlueprintVirtualSubjectFactory.h` (Public)


#### class `ULiveLinkBlueprintVirtualSubjectFactory`  
`class ULiveLinkBlueprintVirtualSubjectFactory : public UBlueprintFactory`  
_L14-32_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UBlueprintFactory`
- L19 _public prototype_ `ULiveLinkBlueprintVirtualSubjectFactory();`
- L22 _public member_ `TSubclassOf<ULiveLinkRole> Role;` — `UPROPERTY(BlueprintReadWrite, Category = "Live Link Blueprint Virtual Subject Factory")`
- L25 _public prototype_ `virtual FText GetDisplayName() const override;`
- L26 _public prototype_ `virtual bool ConfigureProperties() override;`
- L27 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L28 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L29 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L30 _public prototype_ `virtual TArray<FAssetCategoryPath> GetAssetMenuPathsForCategory(FName InCategory) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINKEDITOR_API`
