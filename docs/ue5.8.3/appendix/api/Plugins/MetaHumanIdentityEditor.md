# Plugins / MetaHumanIdentityEditor

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor`
- headers: 15; symbols: 526
- symbol kinds: class=22, delegate=18, enum=2, enumerator=11, function=5, macro=1, member=119, prototype=344, struct=4
- PrivateDependencyModuleNames: AdvancedPreviewScene, AnimGraph, AssetDefinition, CaptureDataCore, CaptureDataUtils, ControlRig, ControlRigDeveloper, Core, CoreUObject, DesktopPlatform, Engine, GeometryCore, GeometryFramework, ImageCore, ImgMedia, InputCore, MediaAssets, MeshConversion, MetaHumanCaptureData, MetaHumanCaptureDataEditor, MetaHumanCaptureUtils, MetaHumanCore, MetaHumanCoreEditor, MetaHumanCoreTech, MetaHumanCoreTechLib, MetaHumanFaceContourTracker, MetaHumanFaceFittingSolver, MetaHumanIdentity, MetaHumanImageViewerEditor, MetaHumanPipeline, MetaHumanPlatform, MetaHumanSDKEditor, MetaHumanSequencer, MetaHumanToolkit, MovieScene, NNE, Projects, RigLogicModule, RigVMDeveloper, Sequencer, SkeletalMeshDescription, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/AssetDefinitions/AssetDefinition_MetaHumanIdentity.h` (Private)


#### class `UAssetDefinition_MetaHumanIdentity`  
`class UAssetDefinition_MetaHumanIdentity : public UAssetDefinitionDefault`  
_L10-30_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L21 _public prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L22 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& InOpenArgs) const;`
- L27 _private prototype_ `void ResolveContourDataCompatibility(const class UMetaHumanIdentityFace* InFacePart) const;`
- L28 _private prototype_ `bool ContourDataIsCompatible(const class UMetaHumanIdentityFace* InFacePart, bool& bOutUpdateRequired) const;`
- L29 _private prototype_ `FText GetCompatibilityMessage(bool bRigCompatible, bool bContoursCompatible) const;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/Customizations/MetaHumanIdentityPoseCustomizations.h` (Private)


#### class `FMetaHumanIdentityPromotedFramePropertyCustomization`  
`class FMetaHumanIdentityPromotedFramePropertyCustomization : public IPropertyTypeCustomization`  
_L18-51_
- inherits: `IPropertyTypeCustomization`
- desc: Detail customization for a UMetaHumanIdentityPromotedFrame
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L36 _private prototype_ `TOptional<FVector::FReal> GetAxisValue(TSharedRef<IPropertyHandle> InPropertyHandle, ETransformField InField, EAxis::Type InAxis) const;` — Get the axis value of the given PropertyHandle
- L39 _private prototype_ `void SetAxisValue(FVector::FReal InNewValue, TSharedRef<IPropertyHandle> InPropertyHandle, ETransformField InField, EAxis::Type InAxis) const;` — Sets the axis value of given PropertyHandle
- L42 _private prototype_ `bool CanEditCameraTransform(TSharedRef<IPropertyHandle> InNavigationLockedHandle) const;` — Whether or not the camera transform can be edited based on the NavigationLocked property
- L50 _private prototype_ `TSharedRef<SWidget> MakeNumericVectorInputBoxWidget(TSharedRef<IPropertyHandle> InPropertyHandle, TSharedRef<IPropertyHandle> InIsEnabledProperty, ETransformField InField) const;` — Create a SNumericVectorInputBox widget for the given property handle @param InPropertyHandle The property handle to read and write values to @param InIsEnabledProperty The property handle used to enable/disable the widget @param InField If the field represents a location or rotation value

#### enum `FMetaHumanIdentityPromotedFramePropertyCustomization::ETransformField`  
`enum class ETransformField`  
_L29-33_
- L31 _public enumerator_ `Location`
- L32 _public enumerator_ `Rotation`

#### class `FMetaHumanIdentityPoseCustomization`  
`class FMetaHumanIdentityPoseCustomization : public IDetailCustomization`  
_L59-67_
- inherits: `IDetailCustomization`
- desc: Detail customization for a UMetaHumanIdentityPose
- L63 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L66 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

#### struct `FMetaHumanIdentityBodyType`  
`struct FMetaHumanIdentityBodyType`  
_L72-81_
- L74 _public member_ `int32 Index;`
- L75 _public member_ `const FSlateBrush* ThumbnailBrush;`
- L77 _public function_ `FMetaHumanIdentityBodyType(int32 InIndex, const FSlateBrush* InThumbnailBrush) : Index(InIndex) , ThumbnailBrush(InThumbnailBrush)`

#### class `FMetaHumanIdentityBodyCustomization`  
`class FMetaHumanIdentityBodyCustomization : public IDetailCustomization`  
_L86-111_
- inherits: `IDetailCustomization`
- desc: Detail customization for a UMetaHumanIdentityBody
- L91 _public prototype_ `FMetaHumanIdentityBodyCustomization();`
- L93 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L96 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L100 _private prototype_ `void SwapThumbnails(UMetaHumanIdentityBody* Body, int32 NewHeight);`
- L102 _private prototype_ `TArray<TSharedPtr<FMetaHumanIdentityBodyType>> GetBodyTypeSubRangeByHeight(TArray<TSharedPtr<FMetaHumanIdentityBodyType>>& BodyTypesFullRange, int32 Height);`
- L105 _private member_ `TArray<TSharedPtr<FMetaHumanIdentityBodyType>> BodyTypes;` — A list of all available body types
- L107 _private member_ `TArray<TSharedPtr<FMetaHumanIdentityBodyType>> BodyTypeSubRangeByHeight;` — A subset (based on the selected height) of body types shown as thumbnails that the user can select
- L109 _private member_ `TSharedPtr<STileView<TSharedPtr<FMetaHumanIdentityBodyType>>> TileWidget;` — TileView container, allowing for swapping thumbnails on height slider move after the widgets has been constructed
- L110 _private member_ `static const int32 BodyTypeSubRangeSize;`

#### class `FMetaHumanIdentityFaceCustomization`  
`class FMetaHumanIdentityFaceCustomization : public IDetailCustomization`  
_L116-129_
- inherits: `IDetailCustomization`
- desc: Detail customization for a UMetaHumanIdentityFace
- L121 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L124 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

#### class `FMetaHumanIdentityCustomization`  
`class FMetaHumanIdentityCustomization : public IDetailCustomization`  
_L135-143_
- inherits: `IDetailCustomization`
- desc: Detail customization for a UMetaHumanIdentity
- L139 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L142 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

#### class `FMetaHumanTemplateMeshCustomization`  
`class FMetaHumanTemplateMeshCustomization : public IDetailCustomization`  
_L148-156_
- inherits: `IDetailCustomization`
- desc: Detail customization for a UMetaHumanTemplateMesh
- L152 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L155 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

#### class `FMetaHumanTemplateMeshComponentCustomization`  
`class FMetaHumanTemplateMeshComponentCustomization : public IDetailCustomization`  
_L165-174_
- inherits: `IDetailCustomization`
- desc: Detail customization for a UMetaHumanTemplateMeshComponent. Used to hide all categories from the details panel that we don't want to show
- L169 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L172 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/MetaHumanIdentityAssetEditor.h` (Private)


#### class `UMetaHumanIdentityAssetEditor`  
`class UMetaHumanIdentityAssetEditor : public UAssetEditor`  
_L10-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetEditor`
- L16 _public prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& InObjectsToEdit) override;`
- L17 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L19 _public prototype_ `void SetObjectToEdit(UObject* InObject);`
- L23 _protected member_ `TObjectPtr<class UMetaHumanIdentity> ObjectToEdit;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/MetaHumanIdentityAssetEditorContext.h` (Private)


#### class `UMetaHumanIdentityAssetEditorContext`  
`class UMetaHumanIdentityAssetEditorContext : public UObject`  
_L12-19_
- reflection: `UCLASS()`
- inherits: `UObject`
- L18 _public member_ `TWeakPtr<FMetaHumanIdentityAssetEditorToolkit> MetaHumanIdentityAssetEditor;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/MetaHumanIdentityAssetEditorToolkit.h` (Private)


#### class `FMetaHumanIdentityAssetEditorToolkit`  
`class FMetaHumanIdentityAssetEditorToolkit : public FMetaHumanToolkitBase`  
_L17-306_
- inherits: `FMetaHumanToolkitBase`
- L21 _public prototype_ `FMetaHumanIdentityAssetEditorToolkit(UAssetEditor* InOwningAssetEditor);`
- L22 _public prototype_ `virtual ~FMetaHumanIdentityAssetEditorToolkit();`
- L26 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L27 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L28 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L29 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L30 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L31 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L32 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L33 _public prototype_ `virtual void HandleSequencerGlobalTimeChanged() override;`
- L36 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L37 _public prototype_ `virtual FString GetReferencerName() const override;`
- L40 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L44 _public prototype_ `virtual void InitToolMenuContext(struct FToolMenuContext& InMenuContext) override;`
- L45 _public prototype_ `virtual void SetEditingObject(UObject* InObject) override;`
- L49 _public prototype_ `void HandleIdentityTreeSelectionChanged(UObject* InObject, EIdentityTreeNodeIdentifier InNodeIdentifier);` — Updates which objects is being displayed in the details panel
- L52 _public prototype_ `void HandlePromotedFrameAdded(class UMetaHumanIdentityPromotedFrame* InPromotedFrame);` — Handle to a newly created promoted frame to initialize curve and group data
- L55 _public prototype_ `void HandleTrackCurrent();` — Applies tracking related viewport settings and runs tracking pipeline
- L58 _public prototype_ `FFrameTrackingContourData GetPoseSpecificContourDataForPromotedFrame(UMetaHumanIdentityPromotedFrame* InPromotedFrame, TWeakObjectPtr<class UMetaHumanIdentityPose> InPose, bool bInProjectFootage = false) const;` — Gets the default contour position for promoted frame based on what curves are available for this pose
- L61 _public prototype_ `const TSharedPtr<class SMetaHumanIdentityPartsEditor> GetIdentityPartsEditor() const;`
- L65 _protected prototype_ `virtual TSharedPtr<FEditorViewportClient> CreateEditorViewportClient() const override;`
- L66 _protected prototype_ `virtual void CreateWidgets() override;`
- L67 _protected prototype_ `virtual void PostInitAssetEditor() override;`
- L68 _protected prototype_ `virtual void BindCommands() override;`
- L69 _protected prototype_ `virtual TSharedRef<SWidget> GetViewportExtraContentWidget() override;`
- L70 _protected prototype_ `virtual void HandleGetViewABMenuContents(EABImageViewMode InViewMode, class FMenuBuilder& InMenuBuilder) override;`
- L71 _protected prototype_ `virtual void HandleSequencerMovieSceneDataChanged(EMovieSceneDataChangeType InDataChangeType) override;`
- L72 _protected prototype_ `virtual void HandleSequencerKeyAdded(struct FMovieSceneChannel* InChannel, const TArray<struct FKeyAddOrDeleteEventItem>& InItems) override;`
- L73 _protected prototype_ `virtual void HandleSequencerKeyRemoved(struct FMovieSceneChannel* InChannel, const TArray<struct FKeyAddOrDeleteEventItem>& InItems) override;`
- L74 _protected prototype_ `virtual void HandleFootageDepthDataChanged(float InNear, float InFar) override;`
- L75 _protected prototype_ `virtual void HandleUndoOrRedoTransaction(const class FTransaction* InTransaction) override;`
- L76 _protected prototype_ `virtual bool IsTimelineEnabled() const override;`
- L80 _private prototype_ `TSharedRef<SDockTab> SpawnPartsTab(const FSpawnTabArgs& InArgs);`
- L81 _private prototype_ `TSharedRef<SDockTab> SpawnOutlinerTab(const FSpawnTabArgs& InArgs);`
- L84 _private prototype_ `TSharedRef<class FMetaHumanIdentityViewportClient> GetMetaHumanIdentityViewportClient() const;` — Get the viewport client as a FMetaHumanIdentityViewportClient
- L87 _private prototype_ `void CreateSceneCaptureComponent();` — Create the scene capture component used to take screenshots for tracking
- L90 _private prototype_ `void LoadGenericFaceContourTracker();` — Load generic face contour tracker models
- L93 _private prototype_ `void ExtendMenu();` — Extend the editor's main menu with custom entries
- L96 _private prototype_ `void ExtendToolBar();` — Extend the editor's toolbar with custom entries
- L99 _private prototype_ `UMetaHumanIdentityPose::ECurrentFrameValid GetIsCurrentFrameValid() const;` — Called to retrieve if the current frame is valid (has both image and depth)
- L102 _private prototype_ `void HandlePromotedFrameTrackingModeChanged(class UMetaHumanIdentityPromotedFrame* InPromotedFrame);` — Called when the tracking mode of a promoted frame changes
- L105 _private prototype_ `void HandlePromotedFrameSelectedInPromotedFramesPanel(class UMetaHumanIdentityPromotedFrame* InPromotedFrame, bool bForceNotify);` — Handles when a Promoted Frame is selected in the Promoted Frames panel
- L108 _private prototype_ `void HandlePromotedFrameRemoved(UMetaHumanIdentityPromotedFrame* InPromotedFrame);` — Handle to a removed promoted frame to deal with removing sequencer keys
- L111 _private prototype_ `void HandleCameraStopped();` — Called when the camera in the viewport stops moving. Used for retracking in case track on change is enabled
- L113 _private prototype_ `void HandleConform();`
- L114 _private prototype_ `void HandleResetTemplateMesh();`
- L116 _private prototype_ `void HandleSubmitToAutoRigging();`
- L118 _private prototype_ `void HandlePredictiveSolverTraining();`
- L120 _private prototype_ `void HandleImportDNA();`
- L121 _private prototype_ `void HandleExportDNA();`
- L122 _private prototype_ `void HandleFitTeeth();`
- L123 _private prototype_ `void HandleExportTemplateMeshClicked();`
- L125 _private prototype_ `void HandleTogglePlayback(EABImageViewMode InViewMode);`
- L127 _private prototype_ `bool CanExportTemplateMesh() const;`
- L128 _private prototype_ `bool CanActivateMarkersForCurrent() const;`
- L129 _private prototype_ `bool CanActivateMarkersForAll() const;`
- L130 _private prototype_ `bool CanTrackCurrent() const;`
- L131 _private prototype_ `bool CanTrackAll() const;`
- L132 _private prototype_ `bool CanConform() const;`
- L133 _private prototype_ `bool CanResetTemplateMesh() const;`
- L134 _private prototype_ `bool CanSubmitToAutoRigging() const;`
- L135 _private prototype_ `bool ActiveCurvesAreValidForConforming() const;`
- L136 _private prototype_ `bool CanImportDNA() const;`
- L137 _private prototype_ `bool CanExportDNA() const;`
- L138 _private prototype_ `bool CanFitTeeth() const;`
- L139 _private prototype_ `bool CanRunSolverTraining() const;`
- L140 _private prototype_ `bool CanCreateComponents() const;`
- L141 _private prototype_ `bool CanTogglePlayback(EABImageViewMode InViewMode) const;`
- L142 _private prototype_ `bool FaceIsConformed() const;`
- L145 _private prototype_ `bool CaptureDataIsConsistentForPoses(const UCaptureData* InCaptureData) const;` — TODO: Instead of checking for consistency filter out the classes that should be selectable
- L148 _private prototype_ `void TrackPromotedFrame(UMetaHumanIdentityPromotedFrame* InPromotedFrame, const TArray<FColor>& InImageData, int32 InWidth, int32 InHeight, const FString& InDepthFramePath);` — Track the given Promoted Frame using the image data provided
- L152 _private prototype_ `bool CaptureSceneForPromotedFrame(class UMetaHumanIdentityPromotedFrame* InPromotedFrame, FIntPoint& OutImageSize, TArray<FColor>& OutLocalSamples, FString & OutDepthFramePath);` — Captures the scene using SceneCaptureComponent and the camera transform from the given Promoted Frame. For footage 2 MetaHuman this also returns the path of the depthmap used (empty if Mesh 2 MetaHuman case)
- L155 _private prototype_ `bool UpdatePromotedFrameTexture(const FFrameNumber& InFrameNumber);` — Returns true if PromotedFrameTexture has been updated with valid texture
- L158 _private prototype_ `bool PopulateImageTextureFromDisk(const FFrameNumber& InFrameNumber, FString& OutTexturePath);` — Returns true if image component of the PromotedFrameTexture has been successfully loaded
- L161 _private prototype_ `bool PopulateDepthTextureFromDisk(const FFrameNumber& InFrameNumber, FString& OutTexturePath);` — Returns true if depth component of the PromotedFrameTexture has been successfully loaded
- L164 _private prototype_ `TSharedRef<SWidget> MakeAssetPickerForCaptureDataType(UClass* InCaptureDataClass);` — Creates an Asset Picker widget based on the given CaptureData type
- L167 _private prototype_ `void MakeCreateComponentsMenu(UToolMenu* InToolMenu);` — Adds the "Create Components" menu in the toolbar
- L170 _private prototype_ `FText GetComponentsFromMeshTooltip() const;` — Get tooltip for Components from Mesh
- L173 _private prototype_ `FText GetComponentsFromFootageTooltip() const;` — Get tooltip for Components from Mesh
- L176 _private prototype_ `void MakeMeshAssetPickerMenu(UToolMenu* InToolMenu, TFunction<void(const FAssetData& InAssetData)> InCallbackFunction) const;`
- L179 _private prototype_ `void SetUpEditorForCaptureDataType();` — Setups the editor based on the current capture data type being help by the neutral pose
- L182 _private prototype_ `bool IsUsingFootageData() const;` — Check for a first valid capture data source set on the pose and return true if it's type is Footage
- L185 _private prototype_ `bool IsUsingMeshData() const;` — Check for a first valid capture data source set on the pose and return true if it's type is Mesh
- L188 _private prototype_ `UFootageCaptureData* GetFootageCaptureData() const;` — Returns first available footage data source is there is one
- L191 _private prototype_ `UCaptureData* GetAvailableCaptureDataFromExistingPoses() const;` — Returns first available capture data source if there is one
- L194 _private prototype_ `ETimecodeAlignment GetTimecodeAlignment() const;` — Returns first available timecode alignment
- L197 _private prototype_ `FString GetCamera() const;` — Returns first available camera
- L200 _private prototype_ `UMetaHumanIdentityPose* GetAvailablePoseWithCaptureData() const;` — Returns the pose with capture source, if there is one. Checks selected pose first
- L202 _private prototype_ `void UpdateTimelineTabVisibility(bool InIsCaptureFootage);`
- L203 _private prototype_ `void HandleCaptureDataChanged(class UCaptureData* InFootageCaptureData, ETimecodeAlignment InTimecodeAlignment, const FString& InCamera, bool bInResetRanges);`
- L204 _private prototype_ `void HandleIdentityPartRemoved(class UMetaHumanIdentityPart* InIdentityPart);`
- L205 _private prototype_ `void HandleIdentityPoseAdded(class UMetaHumanIdentityPose* InIdentityPose, class UMetaHumanIdentityPart* InIdentityPart);`
- L206 _private prototype_ `void HandleIdentityPoseRemoved(class UMetaHumanIdentityPose* InIdentityPose, class UMetaHumanIdentityPart* InIdentityPart);`
- L208 _private prototype_ `void UpdateKeysForSelectedPose();`
- L209 _private prototype_ `void AddSequencerKeyForFrameNumber(int32 InFrameNumber);`
- L210 _private prototype_ `void UpdateTimelineForFootage(UFootageCaptureData* InFootageCaptureData, ETimecodeAlignment InTimecodeAlignment, const FString& InCamera);`
- L211 _private prototype_ `void UpdateContourDataAfterHeadAlignment(const TWeakObjectPtr<class UMetaHumanIdentityPose> InPose);`
- L215 _private member_ `static const FName PartsTabId;`
- L216 _private member_ `static const FName OutlinerTabId;`
- L218 _private member_ `bool bDepthProcessingEnabled = false;`
- L221 _private member_ `TWeakPtr<class SNotificationItem> PredictiveSolversTaskProgressNotification;` — Predictive solver progress notification. Valid only during the identity training
- L224 _private member_ `TWeakObjectPtr<class UMetaHumanIdentityPose> SelectedIdentityPose;` — A reference to the current selected Pose
- L227 _private member_ `TSharedPtr<class SMetaHumanIdentityPartsEditor> IdentityPartsEditor;` — A reference to the Identity Parts editor Widget
- L230 _private member_ `TSharedPtr<class SMetaHumanIdentityPromotedFramesEditor> PromotedFramesEditorWidget;` — The widget used to display Promoted Frames for a Identity Pose
- L233 _private member_ `TSharedPtr<class SMetaHumanIdentityOutliner> OutlinerWidget;` — The widget used to display the Promoted Frame curves and landmarks outliner
- L236 _private member_ `TSharedPtr<class FLandmarkConfigIdentityHelper> LandmarkConfigHelper;` — A helper class for promoted frames and outliner to work with pose specific curves
- L239 _private member_ `TObjectPtr<class UMetaHumanIdentity> Identity;` — A Reference to the Identity we are editing
- L242 _private member_ `TObjectPtr<class USceneCaptureComponent2D> SceneCaptureComponent;` — A component used to capture the scene in a texture for tracking purposes
- L245 _private member_ `TPair<TObjectPtr<class UTexture2D>, TObjectPtr<UTexture2D>> PromotedFrameTexture;` — A pointer to currently loaded promoted frame texture
- L248 _private member_ `TRange<FFrameNumber> ProcessingFrameRange = TRange<FFrameNumber>(0, 0);` — The range of valid frames for processing (where both image and depth tracks are defined)
- L251 _private member_ `TMap<TWeakObjectPtr<UObject>, TRange<FFrameNumber>> MediaFrameRanges;` — The range of frames for each media track
- L256 _private prototype_ `void AddTemplateToMetaHumanToAssetMenu();` — Called to show/hide the TemplateToMetaHuman menu item in response to setting the mh.Identity.EnableTemplateToMetaHuman cvar
- L259 _private prototype_ `void UpdatedViewportForCaptureData(UCaptureData* InCaptureData, ETimecodeAlignment InTimecodeAlignment, const FString& InCamera);`
- L262 _private prototype_ `FText GetCreateComponentsToolbarComboTooltip() const;` — A delegate returning the CreateComponents toolbar combo button tooltip
- L265 _private prototype_ `FText GetPromoteFrameButtonTooltip() const;` — A delegate returning the PromoteFrame button tooltip
- L268 _private prototype_ `FText GetDemoteFrameButtonTooltip() const;` — A delegate returning the DemoteFrame button tooltip
- L271 _private prototype_ `FText GetTrackActiveFrameButtonTooltip() const;` — A delegate returning the Track Active Frame button tooltip
- L274 _private prototype_ `FText GetTrackAllFramesButtonTooltip() const;` — A delegate returning the Track All Frames button tooltip
- L277 _private prototype_ `FText GetIdentitySolveButtonTooltip() const;` — A delegate returning the IdentitySolve button tooltip
- L280 _private prototype_ `FText GetMeshToMetaHumanButtonTooltip() const;` — A delegate returning the MeshToMetaHuman button tooltip
- L283 _private prototype_ `FText GetMeshToMetaHumanButtonTooltipWithAfterProcessingInfo(FText Tooltip, bool bFullMetaHuman) const;` — A method to append after-processing info to the MeshToMetaHuman button tooltip depending on whether it's coming from mesh or footage capture data
- L286 _private prototype_ `FText GetFitTeethButtonTooltip() const;` — A delegate returning the Fit Teeth button tooltip
- L289 _private prototype_ `FText GetMeshToMetaHumanDNAOnlyButtonTooltip() const;` — A delegate returning MeshToMetaHuman (DNA Only) button tooltip
- L292 _private prototype_ `FText GetMeshToMetaHumanButtonTooltipWithEnableInstructionsAdded(FText MainTooltipText) const;` — A method to get dynamic tooltip text for MeshToMetaHuman command, with additional info how to enable the button added
- L295 _private prototype_ `FText GetPrepareForPerformanceButtonTooltip() const;` — A method to get dynamic tooltip text for Prepare for Performance
- L298 _private prototype_ `bool WarnUnknownDeviceModelDialog() const;` — Creates a dialog warning the user that the Device Model has not been set, returns whether the user agrees to continue
- L301 _private prototype_ `FText GetConfigureComponentsFromConformedTooltipText() const;` — Returns a tooltip for Configure Components from Conformed command
- L303 _private prototype_ `void HandleAutoriggingServiceFinished(bool InSuccess);`
- L305 _private prototype_ `void GetExcludedFrameInfo(FFrameRate& OutSourceRate, FFrameRangeMap& OutExcludedFramesMap, int32& OutRGBMediaStartFrame, TRange<FFrameNumber>& OutProcessingLimit) const;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/MetaHumanIdentityCommands.h` (Private)


#### class `FMetaHumanIdentityEditorCommands`  
`class FMetaHumanIdentityEditorCommands : public TCommands<FMetaHumanIdentityEditorCommands>`  
_L8-48_
- inherits: `TCommands<FMetaHumanIdentityEditorCommands>`
- L13 _public prototype_ `FMetaHumanIdentityEditorCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface
- L19 _public member_ `TSharedPtr<FUICommandInfo> ComponentsFromMesh;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> ComponentsFromFootage;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> TrackCurrent;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> TrackAll;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ActivateMarkersForCurrent;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ActivateMarkersForAll;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> ResetTemplateMesh;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> IdentitySolve;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> MeshToMetaHumanDNAOnly;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> ImportDNA;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> ExportDNA;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> FitTeeth;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> PrepareForPerformance;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> RigidFitCurrent;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> RigidFitAll;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> PromoteFrame;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> DemoteFrame;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> ToggleConformalMesh;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> ToggleRig;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> ToggleCurrentPose;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> TogglePlayback;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> ExportTemplateMesh;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/MetaHumanIdentityEditorModule.h` (Private)


#### class `FMetaHumanIdentityEditorModule`  
`class FMetaHumanIdentityEditorModule : public IModuleInterface`  
_L7-21_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private member_ `TArray<FName> ClassesToUnregisterOnShutdown;` — StaticClass is not safe on shutdown, so we cache the name, and use this to unregister on shut down
- L20 _private member_ `FName PropertyToUnregisterOnShutdown;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/MetaHumanIdentityFactoryNew.h` (Private)


#### class `UMetaHumanIdentityFactoryNew`  
`class UMetaHumanIdentityFactoryNew : public UFactory`  
_L13-25_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L19 _public prototype_ `UMetaHumanIdentityFactoryNew();`
- L22 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* Context, FFeedbackContext* Warn) override;`
- L23 _public prototype_ `virtual FText GetToolTip() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANIDENTITYEDITOR_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/MetaHumanIdentityTooltipProvider.h` (Private)


#### enum `ETrackPromotedFrameTooltipState`  
`enum class ETrackPromotedFrameTooltipState`  
_L8-11_
- L10 _public enumerator_ `Default`
- L10 _public enumerator_ `Default`
- L10 _public enumerator_ `Default`
- L10 _public enumerator_ `Default`
- L10 _public enumerator_ `Default`
- L10 _public enumerator_ `Default`
- L10 _public enumerator_ `Default`
- L10 _public enumerator_ `Default`
- L10 _public enumerator_ `Default`

#### struct `FMetaHumanIdentityTooltipProvider`  
`struct FMetaHumanIdentityTooltipProvider`  
_L13-22_
- L15 _public prototype_ `static FText GetTrackActiveFrameButtonTooltip(const TWeakObjectPtr<class UMetaHumanIdentity> InIdentity, const TWeakObjectPtr<class UMetaHumanIdentityPose> SelectedIdentityPose, const class UMetaHumanIdentityPromotedFrame* InSelectedFrame);`
- L19 _public prototype_ `static FText GetIdentitySolveButtonTooltip(const TWeakObjectPtr<class UMetaHumanIdentity> InIdentity);`
- L20 _public prototype_ `static FText GetMeshToMetaHumanButtonTooltip(const TWeakObjectPtr<class UMetaHumanIdentity> InIdentity);`
- L21 _public prototype_ `static FText GetFitTeethButtonTooltip(const TWeakObjectPtr<class UMetaHumanIdentity> InIdentity, bool bInCanFitTeeth);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/ThumbnailRendering/MetaHumanIdentityThumbnailRenderer.h` (Private)


#### class `FMetaHumanIdentityThumbnailScene`  
`class FMetaHumanIdentityThumbnailScene : public FThumbnailPreviewScene`  
_L14-38_
- inherits: `FThumbnailPreviewScene`
- L19 _public prototype_ `FMetaHumanIdentityThumbnailScene();`
- L21 _public prototype_ `void SetMetaHumanIdentity(class UMetaHumanIdentity* InIdentity);`
- L26 _protected prototype_ `virtual void GetViewMatrixParameters(const float InFOVDegrees, FVector& OutOrigin, float& OutOrbitPitch, float& OutOrbitYaw, float& OutOrbitZoom) const override;`
- L31 _private member_ `TObjectPtr<class AActor> PreviewActor;` — The actor used to preview the visual component of the Identity asset, which can be a static or skeletal mesh
- L34 _private member_ `TWeakObjectPtr<class UMetaHumanIdentity> Identity;` — A reference to the Identity asset which we need to generate the thumbnail for
- L37 _private member_ `TStrongObjectPtr<class UTexture2D> FrameTexture;` — The texture used to render the thumbnail

#### class `UMetaHumanIdentityThumbnailRenderer`  
`class UMetaHumanIdentityThumbnailRenderer : public UDefaultSizedThumbnailRenderer`  
_L44-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDefaultSizedThumbnailRenderer`
- L51 _public prototype_ `virtual bool CanVisualizeAsset(UObject* InObject) override;`
- L52 _public prototype_ `virtual void Draw(UObject* InObject, int32 InX, int32 InY, uint32 InWidth, uint32 InHeight, class FRenderTarget* InRenderTarget, class FCanvas* InCanvas, bool bInAdditionalViewFamily) override;`
- L53 _public prototype_ `virtual void BeginDestroy() override;`
- L57 _private member_ `TUniquePtr<FMetaHumanIdentityThumbnailScene> ThumbnailScene;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/UI/MetaHumanIdentityViewportClient.h` (Private)


#### class `FMetaHumanIdentityViewportClient`  
`class FMetaHumanIdentityViewportClient : public FMetaHumanEditorViewportClient`  
_L7-43_
- inherits: `FMetaHumanEditorViewportClient`
- L11 _public prototype_ `FMetaHumanIdentityViewportClient(FPreviewScene* InPreviewScene, class UMetaHumanIdentity* InIdentity);`
- L14 _public prototype_ `virtual TArray<class UPrimitiveComponent*> GetHiddenComponentsForView(EABImageViewMode InViewMode) const override;`
- L15 _public prototype_ `virtual void UpdateABVisibility(bool bInSetViewpoint = true) override;`
- L16 _public prototype_ `virtual void Tick(float InDeltaSeconds) override;`
- L17 _public prototype_ `virtual bool CanToggleShowCurves(EABImageViewMode InViewMode) const override;`
- L18 _public prototype_ `virtual bool CanToggleShowControlVertices(EABImageViewMode InViewMode) const override;`
- L19 _public prototype_ `virtual bool CanChangeViewMode(EABImageViewMode InViewMode) const override;`
- L20 _public prototype_ `virtual bool CanChangeEV100(EABImageViewMode InViewMode) const override;`
- L21 _public prototype_ `virtual UMetaHumanFootageComponent* GetActiveFootageComponent(const TArray<UPrimitiveComponent*>& InAllComponents) const override;`
- L22 _public prototype_ `virtual bool GetSetViewpoint() const override;`
- L23 _public prototype_ `virtual bool ShouldShowCurves(EABImageViewMode InViewMode) const override;`
- L24 _public prototype_ `virtual bool ShouldShowControlVertices(EABImageViewMode InViewMode) const override;`
- L25 _public prototype_ `virtual bool IsFootageVisible(EABImageViewMode InViewMode) const override;`
- L26 _public prototype_ `virtual void FocusViewportOnSelection() override;`
- L29 _public prototype_ `bool IsCurrentPoseVisible(EABImageViewMode InViewMode) const;`
- L30 _public prototype_ `bool IsTemplateMeshVisible(EABImageViewMode InViewMode) const;`
- L32 _public prototype_ `void ToggleCurrentPoseVisibility(EABImageViewMode InViewMode);`
- L33 _public prototype_ `void ToggleConformalMeshVisibility(EABImageViewMode InViewMode);`
- L35 _public prototype_ `DECLARE_DELEGATE_RetVal(class UMetaHumanIdentityPromotedFrame*, FOnGetSelectedPromotedFrame) FOnGetSelectedPromotedFrame OnGetSelectedPromotedFrameDelegate;`
- L40 _protected prototype_ `bool HasSelectedPromotedFrame() const;`
- L42 _protected member_ `TObjectPtr<class UMetaHumanIdentity> Identity;`

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_DELEGATE_RetVal(class UMetaHumanIdentityPromotedFrame*, FOnGetSelectedPromotedFrame) FOnGetSelectedPromotedFrame OnGetSelectedPromotedFrameDelegate;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/UI/SMetaHumanIdentityOutliner.h` (Private)


#### struct `FIdentityOutlinerTreeNode`  
`struct FIdentityOutlinerTreeNode`  
_L14-82_
- L17 _public member_ `TWeakObjectPtr<class UMetaHumanIdentityPromotedFrame> PromotedFrame;` — The promoted frame associated with this node
- L20 _public member_ `int32 FrameIndex = INDEX_NONE;` — The index of the promoted frame associated with this node
- L23 _public member_ `FText OutlinerGroupName;` — Group name as visualized by the outliner
- L26 _public member_ `FText OutlinerCurveName;` — Curve name as visualized by the outliner
- L29 _public member_ `FString InternalGroupName;` — Internal group name as specified in the group config. Internal names are used by everything outside the outliner
- L32 _public member_ `FString InternalCurveName;` — Internal curve name as specified in the curves config. Internal names are used by everything outside the outliner
- L35 _public member_ `TWeakPtr<FIdentityOutlinerTreeNode> Parent;` — The parent of this node, nullptr if this is the root
- L38 _public member_ `TArray<TSharedRef<FIdentityOutlinerTreeNode>> Children;` — The list of child nodes
- L41 _public member_ `bool bIsNodeVisible = true;` — If the node is visible in the tree view
- L43 _public prototype_ `bool IsFrameNode() const;`
- L45 _public prototype_ `bool IsGroupNode() const;`
- L47 _public prototype_ `bool IsCurveNode() const;`
- L49 _public prototype_ `const FSlateBrush* GetCurveOrGroupIcon();`
- L51 _public prototype_ `const FText GetCurveOrGroupIconTooltip();`
- L53 _public prototype_ `FText GetLabel() const;`
- L55 _public prototype_ `void GetCurveNamesRecursive(TArray<FString>& OutCurveNames);`
- L57 _public prototype_ `void OnVisibleStateChanged(ECheckBoxState InNewState);`
- L59 _public prototype_ `void VisibleStateChangedRecursive(ECheckBoxState InNewState);`
- L61 _public prototype_ `bool IsKeypointVisibleForAnyCurve(const FString& InKeypointName);`
- L63 _public prototype_ `ECheckBoxState IsVisibleCheckState() const;`
- L65 _public prototype_ `void OnActiveStateChanged(ECheckBoxState InNewState);`
- L67 _public prototype_ `void ActiveStateChangedRecursive(ECheckBoxState InNewState);`
- L69 _public prototype_ `bool IsKeypointActiveForAnyCurve(const FString& InKeypointName);`
- L71 _public prototype_ `ECheckBoxState IsActiveCheckState() const;`
- L73 _public prototype_ `bool IsSelected(bool bInRecursive = true) const;`
- L75 _public member_ `FEnableFaceRefinementWorkflowDelegate EnableFaceRefinementWorkflowDelegate;`
- L77 _public prototype_ `FText GetTooltipForVisibilityCheckBox() const;`
- L78 _public prototype_ `FText GetTooltipForUsedToSolveCheckBox() const;`
- L79 _public prototype_ `FText GetNodeTypeName() const;`
- L81 _public prototype_ `bool IsEnabled() const;`

#### class `SMetaHumanIdentityOutliner`  
`class SMetaHumanIdentityOutliner : public SCompoundWidget`  
_L91-198_
- inherits: `SCompoundWidget`
- L95 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanIdentityOutliner)`
- L97 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<class FLandmarkConfigIdentityHelper>, LandmarkConfigHelper) SLATE_ARGUMENT(TSharedPtr<class FMetaHumanEditorViewportClient>, ViewportClient) SLATE_EVENT(FOnOutlinerSelectionChanged, OnSelectionChanged) SLATE_EVENT(FSimpleDelegate, OnResetImageViewerPoints) SLATE_ATTRIBUTE(bool, FaceIsConformed) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L112 _public prototype_ `void SetPromotedFrame(class UMetaHumanIdentityPromotedFrame* InPromotedFrame, int32 InFrameIndex, const EIdentityPoseType& InSelectedPose);`
- L117 _private prototype_ `TSharedRef<SHeaderRow> MakeHeaderRow() const;` — Create the Header Row for the outliner tree view
- L120 _private prototype_ `TSharedRef<ITableRow> HandleGenerateOutlinerTreeRow(TSharedRef<FIdentityOutlinerTreeNode> InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L123 _private prototype_ `void HandleOutlinerTreeGetChildren(TSharedRef<FIdentityOutlinerTreeNode> InItem, TArray<TSharedRef<FIdentityOutlinerTreeNode>>& OutChildren);`
- L126 _private prototype_ `void HandleOutlinerTreeSelectionChanged(TSharedPtr<FIdentityOutlinerTreeNode> InItem, ESelectInfo::Type InSelectInfo);`
- L129 _private prototype_ `void HandleOutlinerTreeSetExpansionRecursive(TSharedRef<FIdentityOutlinerTreeNode> InItem, bool bInShouldExpand);` — Enable recursive expansion using Shift + click to expand a node
- L132 _private prototype_ `void CreateCurveNameMappingFromFile();` — Populate the name mapping from specified config path. Returns true if parsing was successful
- L135 _private prototype_ `void RefreshSelectedNodeExpansion(const TArray<TSharedRef<FIdentityOutlinerTreeNode>>& InSelectedNodes);` — Update the node expansion for selected nodes
- L138 _private prototype_ `void RefreshTreeSelectionFromContourData(bool bClearPointSelection = false);` — Checks selection from contour data and updates selection for tree
- L141 _private prototype_ `TSharedRef<FIdentityOutlinerTreeNode> MakeOutlinerTreeNodeForPromotedFrame(class UMetaHumanIdentityPromotedFrame* InPromotedFrame, int32 InFrameIndex, const EIdentityPoseType& InSelectedPose);`
- L144 _private prototype_ `void FindSelectedItemsRecursive(TSharedRef<FIdentityOutlinerTreeNode> InItem, TArray<TSharedRef<FIdentityOutlinerTreeNode>>& OutSelectedItems) const;`
- L147 _private prototype_ `void FindSelectionFromContourDataRecursive(TSharedRef<FIdentityOutlinerTreeNode> InItem, TArray<TSharedRef<FIdentityOutlinerTreeNode>>& OutSelectedItems) const;` — Looks up Contour Data to determine which curves are selected
- L150 _private prototype_ `void FindItemsWithCurveNamesRecursive(TSharedRef<FIdentityOutlinerTreeNode> InItem, const TSet<FString>& InNames, TArray<TSharedRef<FIdentityOutlinerTreeNode>>& OutItems) const;` — populates a list of tree nodes that have a matching curve name
- L153 _private prototype_ `void FindAllCurveNodesRecursive(TSharedRef<FIdentityOutlinerTreeNode> InItem, TArray<TSharedRef<FIdentityOutlinerTreeNode>>& OutItems) const;` — populates the list of curve nodes from the input node node recursively
- L156 _private prototype_ `TSet<FString> FindSelectedCurveNamesFromContourData() const;` — Returns a list of curves that have been selected from contour data state
- L159 _private prototype_ `TSet<FString> FindSelectedCurveNamesFromNodeSelection() const;` — Returns a list of curves that have been selected from contour data state
- L162 _private prototype_ `bool IsFaceRefinementWorkflowEnabled();` — Returns true if face has been conformed or user manually sets it
- L165 _private prototype_ `bool EnableCurveEditingForUnconformedFaceDialog() const;` — Creates suppressible dialog checking if the user wants to manually place curves
- L170 _private member_ `TWeakObjectPtr<class UMetaHumanIdentityPromotedFrame> PromotedFrame;` — Reference to the Promoted Frame we are editing
- L173 _private member_ `TSharedPtr<class FLandmarkConfigIdentityHelper> LandmarkConfigHelper;`
- L176 _private member_ `TSharedPtr<class FUICommandList> CommandList;` — Command list for handling actions in the tree view
- L179 _private member_ `TSharedPtr<FMetaHumanEditorViewportClient> ViewportClient;` — Hold a shared pointer to viewport client
- L182 _private member_ `TSharedPtr<STreeView<TSharedRef<FIdentityOutlinerTreeNode>>> OutlinerTreeWidget;` — A pointer to the Identity tree view
- L185 _private member_ `TArray<TSharedRef<FIdentityOutlinerTreeNode>> RootNodes;` — List of root nodes of the Outliner tree
- L188 _private member_ `TMap<FString, FText> InternalToOutlinerNamingMap;` — Mapping for Outliner curve names
- L191 _private member_ `FEnableFaceRefinementWorkflowDelegate EnableFaceRefinementWorkflowDelegate;` — A delegate that returns the state for improved face conformation flow
- L194 _private member_ `TAttribute<bool> bFaceIsConformed;` — An attribute to check if the face has been conformed
- L197 _private member_ `bool bManualCurveInteraction = false;` — True if the user selected manual curve interaction before solve took place

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FEnableFaceRefinementWorkflowDelegate)`
- L89 _delegate_ `DECLARE_DELEGATE_OneParam(FOnOutlinerSelectionChanged, const TArray<FString>& SelectedCurves) class SMetaHumanIdentityOutliner : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityOutliner) {} SLATE_ARGUMENT(TSharedPtr<class FLandmarkConfigIdentityHelper>, LandmarkConfigHelper) SLATE_ARGUMENT(TSharedPtr<class FMetaHumanEditorViewportClient>, ViewportClient) SLATE_EVENT(FOnOutlinerSelectionChanged, OnSelectionChanged) SLATE_EVENT(FSimpleDelegate, OnResetImageViewerPoints) SLATE_ATTRIBUTE(bool, FaceIsConformed) SLATE_END_ARGS() void Construct(const FArguments& InArgs); void SetPromotedFrame(class UMetaHumanIdentityPromotedFrame* InPromotedFrame, int32 InFrameIndex, const EIdentityPoseType& InSelectedPose); private: TSharedRef<SHeaderRow> MakeHeaderRow() const; TSharedRef<ITableRow> HandleGenerateOutlinerTreeRow(TSharedRef<FIdentityOutlinerTreeNode> InItem, const TSharedRef<STableViewBase>& InOwnerTable); void HandleOutlinerTreeGetChildren(TSharedRef<FIdentityOutlinerTreeNode> InItem, TArray<TSharedRef<FIdentityOutlinerTreeNode>>& OutChildren); void HandleOutlinerTreeSelectionChanged(TSharedPtr<FIdentityOutlinerTreeNode> InItem, ESelectInfo::Type InSelectInfo);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/UI/SMetaHumanIdentityPartsClassCombo.h` (Private)


#### class `SMetaHumanIdentityPartsClassCombo`  
`class SMetaHumanIdentityPartsClassCombo : public SCompoundWidget`  
_L17-56_
- inherits: `SCompoundWidget`
- desc: A combo button that shows Identity Parts and Poses and emits the appropriate event when one is selected selected
- L21 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanIdentityPartsClassCombo)`
- L22 _public prototype_ `SLATE_ARGUMENT(TWeakObjectPtr<class UMetaHumanIdentity>, Identity) SLATE_EVENT(FIdentityPartClassSelected, OnIdentityPartClassSelected) SLATE_EVENT(FIdentityPoseClassSelected, OnIdentityPoseClassSelected) SLATE_EVENT(FIsIdentityPartClassEnabled, OnIsIdentityPartClassEnabled) SLATE_EVENT(FIsIdentityPoseClassEnabled, OnIsIdentityPoseClassEnabled) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L33 _private prototype_ `TSharedRef<SWidget> MakeAddPartMenuWidget() const;` — Creates the widget that will be displayed as the combo menu
- L35 _private prototype_ `void MakeAddPartSubMenu(class FMenuBuilder& InMenuBuilder) const;`
- L36 _private prototype_ `void MakeAddPoseSubMenu(class FMenuBuilder& InMenuBuilder) const;`
- L37 _private prototype_ `void MakeAddPoseGroupSubMenu(class FMenuBuilder& InMenuBuilder) const;`
- L39 _private prototype_ `FText GetAddPartTooltip(TSubclassOf<class UMetaHumanIdentityPart> InPart) const;`
- L40 _private prototype_ `FText GetAddNeutralTooltip() const;`
- L41 _private prototype_ `FText GetAddTeethTooltip() const;`
- L44 _private member_ `FIdentityPartClassSelected OnIdentityPartClassSelectedDelegate;` — Delegate called when a Identity Part class is selected from the combo menu
- L47 _private member_ `FIdentityPoseClassSelected OnIdentityPoseClassSelectedDelegate;` — Delegate called when a Identity Pose class is selected from the combo menu
- L50 _private member_ `FIsIdentityPartClassEnabled OnIsIdentityPartClassEnabledDelegate;` — Delegate called to query if a Part class should be enabled in the menu
- L53 _private member_ `FIsIdentityPoseClassEnabled OnIsIdentityPoseClassEnabledDelegate;` — Delegate called to query if a Pose class should be enabled in the menu
- L55 _private member_ `TWeakObjectPtr<UMetaHumanIdentity> Identity;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_DELEGATE_OneParam(FIdentityPartClassSelected, TSubclassOf<class UMetaHumanIdentityPart> InPartClass) DECLARE_DELEGATE_TwoParams(FIdentityPoseClassSelected, TSubclassOf<class UMetaHumanIdentityPose> InPoseClass, EIdentityPoseType InPoseType) DECLARE_DELEGATE_RetVal_OneParam(bool, FIsIdentityPartClassEnabled, TSubclassOf<class UMetaHumanIdentityPart> InPartClass) DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsIdentityPoseClassEnabled, TSubclassOf<class UMetaHumanIdentityPose> InPoseClass, EIdentityPoseType InPoseType) class SMetaHumanIdentityPartsClassCombo : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPartsClassCombo) {} SLATE_ARGUMENT(TWeakObjectPtr<class UMetaHumanIdentity>, Identity) SLATE_EVENT(FIdentityPartClassSelected, OnIdentityPartClassSelected) SLATE_EVENT(FIdentityPoseClassSelected, OnIdentityPoseClassSelected) SLATE_EVENT(FIsIdentityPartClassEnabled, OnIsIdentityPartClassEnabled) SLATE_EVENT(FIsIdentityPoseClassEnabled, OnIsIdentityPoseClassEnabled) SLATE_END_ARGS() void Construct(const FArguments& InArgs); private: TSharedRef<SWidget> MakeAddPartMenuWidget() const; void MakeAddPartSubMenu(class FMenuBuilder& InMenuBuilder) const; void MakeAddPoseSubMenu(class FMenuBuilder& InMenuBuilder) const; void MakeAddPoseGroupSubMenu(class FMenuBuilder& InMenuBuilder) const; FText GetAddPartTooltip(TSubclassOf<class UMetaHumanIdentityPart> InPart) const; FText GetAddNeutralTooltip() const; FText GetAddTeethTooltip() const; FIdentityPartClassSelect`
- L12 _delegate_ `DECLARE_DELEGATE_TwoParams(FIdentityPoseClassSelected, TSubclassOf<class UMetaHumanIdentityPose> InPoseClass, EIdentityPoseType InPoseType) DECLARE_DELEGATE_RetVal_OneParam(bool, FIsIdentityPartClassEnabled, TSubclassOf<class UMetaHumanIdentityPart> InPartClass) DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsIdentityPoseClassEnabled, TSubclassOf<class UMetaHumanIdentityPose> InPoseClass, EIdentityPoseType InPoseType) class SMetaHumanIdentityPartsClassCombo : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPartsClassCombo) {} SLATE_ARGUMENT(TWeakObjectPtr<class UMetaHumanIdentity>, Identity) SLATE_EVENT(FIdentityPartClassSelected, OnIdentityPartClassSelected) SLATE_EVENT(FIdentityPoseClassSelected, OnIdentityPoseClassSelected) SLATE_EVENT(FIsIdentityPartClassEnabled, OnIsIdentityPartClassEnabled) SLATE_EVENT(FIsIdentityPoseClassEnabled, OnIsIdentityPoseClassEnabled) SLATE_END_ARGS() void Construct(const FArguments& InArgs); private: TSharedRef<SWidget> MakeAddPartMenuWidget() const; void MakeAddPartSubMenu(class FMenuBuilder& InMenuBuilder) const; void MakeAddPoseSubMenu(class FMenuBuilder& InMenuBuilder) const; void MakeAddPoseGroupSubMenu(class FMenuBuilder& InMenuBuilder) const; FText GetAddPartTooltip(TSubclassOf<class UMetaHumanIdentityPart> InPart) const; FText GetAddNeutralTooltip() const; FText GetAddTeethTooltip() const; FIdentityPartClassSelected OnIdentityPartClassSelectedDelegate; FIdentityPoseClassSelected OnIdentityPoseClassSelectedDelegate; FIsId`
- L13 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsIdentityPartClassEnabled, TSubclassOf<class UMetaHumanIdentityPart> InPartClass) DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsIdentityPoseClassEnabled, TSubclassOf<class UMetaHumanIdentityPose> InPoseClass, EIdentityPoseType InPoseType) class SMetaHumanIdentityPartsClassCombo : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPartsClassCombo) {} SLATE_ARGUMENT(TWeakObjectPtr<class UMetaHumanIdentity>, Identity) SLATE_EVENT(FIdentityPartClassSelected, OnIdentityPartClassSelected) SLATE_EVENT(FIdentityPoseClassSelected, OnIdentityPoseClassSelected) SLATE_EVENT(FIsIdentityPartClassEnabled, OnIsIdentityPartClassEnabled) SLATE_EVENT(FIsIdentityPoseClassEnabled, OnIsIdentityPoseClassEnabled) SLATE_END_ARGS() void Construct(const FArguments& InArgs); private: TSharedRef<SWidget> MakeAddPartMenuWidget() const; void MakeAddPartSubMenu(class FMenuBuilder& InMenuBuilder) const; void MakeAddPoseSubMenu(class FMenuBuilder& InMenuBuilder) const; void MakeAddPoseGroupSubMenu(class FMenuBuilder& InMenuBuilder) const; FText GetAddPartTooltip(TSubclassOf<class UMetaHumanIdentityPart> InPart) const; FText GetAddNeutralTooltip() const; FText GetAddTeethTooltip() const; FIdentityPartClassSelected OnIdentityPartClassSelectedDelegate; FIdentityPoseClassSelected OnIdentityPoseClassSelectedDelegate; FIsIdentityPartClassEnabled OnIsIdentityPartClassEnabledDelegate;`
- L14 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FIsIdentityPoseClassEnabled, TSubclassOf<class UMetaHumanIdentityPose> InPoseClass, EIdentityPoseType InPoseType) class SMetaHumanIdentityPartsClassCombo : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPartsClassCombo) {} SLATE_ARGUMENT(TWeakObjectPtr<class UMetaHumanIdentity>, Identity) SLATE_EVENT(FIdentityPartClassSelected, OnIdentityPartClassSelected) SLATE_EVENT(FIdentityPoseClassSelected, OnIdentityPoseClassSelected) SLATE_EVENT(FIsIdentityPartClassEnabled, OnIsIdentityPartClassEnabled) SLATE_EVENT(FIsIdentityPoseClassEnabled, OnIsIdentityPoseClassEnabled) SLATE_END_ARGS() void Construct(const FArguments& InArgs); private: TSharedRef<SWidget> MakeAddPartMenuWidget() const; void MakeAddPartSubMenu(class FMenuBuilder& InMenuBuilder) const; void MakeAddPoseSubMenu(class FMenuBuilder& InMenuBuilder) const; void MakeAddPoseGroupSubMenu(class FMenuBuilder& InMenuBuilder) const; FText GetAddPartTooltip(TSubclassOf<class UMetaHumanIdentityPart> InPart) const; FText GetAddNeutralTooltip() const; FText GetAddTeethTooltip() const; FIdentityPartClassSelected OnIdentityPartClassSelectedDelegate; FIdentityPoseClassSelected OnIdentityPoseClassSelectedDelegate; FIsIdentityPartClassEnabled OnIsIdentityPartClassEnabledDelegate; FIsIdentityPoseClassEnabled OnIsIdentityPoseClassEnabledDelegate;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/UI/SMetaHumanIdentityPartsEditor.h` (Private)


#### struct `FIdentityTreeNode`  
`struct FIdentityTreeNode`  
_L17-87_
- desc: A node in the Identity Parts tree
- L20 _public prototype_ `FIdentityTreeNode(class UMetaHumanIdentityPart* InIdentityPart, class AActor* InIdentityActor, FName InPropertyName = NAME_None, class UPrimitiveComponent* InPreviewComponent = nullptr, EIdentityTreeNodeIdentifier InIdentifier = EIdentityTreeNodeIdentifier::None);` — Builds a node from a Part
- L23 _public prototype_ `FIdentityTreeNode(class UMetaHumanIdentityPose* InIdentityPose, class AActor* InIdentityActor);` — Builds a node from a Pose
- L26 _public prototype_ `FIdentityTreeNode(class UMetaHumanIdentity* InIdentity, class AActor* InIdentityActor);` — Builds the node hierarchy for a given Identity
- L29 _public prototype_ `FIdentityTreeNode(EIdentityTreeNodeIdentifier InIdentifier);` — Builds an empty node that can act as container for child nodes
- L32 _public prototype_ `static EIdentityTreeNodeIdentifier GetTreeNodeIdentifierForPart(class UMetaHumanIdentityPart* InIdentityPart);` — Return the Tree Node Identifier for a given part type
- L35 _public prototype_ `static EIdentityTreeNodeIdentifier GetTreeNodeIdentifierForPose(const EIdentityPoseType InPoseType);` — Return Tree Node Identifier for a given pose type
- L38 _public prototype_ `void SetupPreviewSceneComponentInstance(class AActor* InIdentityActor);` — Creates the PreviewSceneComponentInstance which will be displayed in the viewport
- L41 _public prototype_ `void UpdateSceneComponentInstanceProperty(class FProperty* InProperty);` — Updates the value of the given property in the PreviewSceneComponentInstance
- L44 _public prototype_ `bool CanDelete() const;` — Returns true if this node can be deleted from the tree
- L47 _public prototype_ `FText GetDisplayText() const;` — Returns the display text for this node based on the data it is holding
- L50 _public prototype_ `const FSlateBrush* GetDisplayIconBrush() const;` — Returns the display icon for this node based on the data it is holding
- L53 _public prototype_ `FText GetTooltip() const;` — Returns the tooltip for this node based on the data it is holding
- L56 _public prototype_ `UObject* GetObject() const;` — Returns a pointer to the valid object associated with this node. It can return nullptr if not directly associated with one
- L59 _public prototype_ `class FObjectProperty* GetObjectProperty() const;` — Returns the FObjectProperty associated with this node. Only valid if this node points to a property of a Part, i.e, IdentityPartPropertyName is not none
- L62 _public member_ `TWeakObjectPtr<class UMetaHumanIdentity> Identity;` — A weak pointer to the Identity object associated with this node. This is valid iff this is the root node of the hierarchy
- L65 _public member_ `TWeakObjectPtr<class UMetaHumanIdentityPart> IdentityPart;` — A weak pointer to the Identity Part associated with this node, if there is one
- L68 _public member_ `FName IdentityPartPropertyName = NAME_None;` — The name of the Part property associated with this node, if there is one
- L71 _public member_ `TWeakObjectPtr<class UMetaHumanIdentityPose> IdentityPose;` — A weak pointer to the Identity pose associated with this node, if there is one
- L74 _public member_ `TArray<TSharedRef<FIdentityTreeNode>> Children;` — The children nodes
- L77 _public member_ `TWeakObjectPtr<UPrimitiveComponent> PreviewSceneComponent;` — The preview component associated with this node, if there is one
- L80 _public member_ `TWeakObjectPtr<UPrimitiveComponent> PreviewSceneComponentInstance;` — The instance of the preview scene component that is actually displayed in the viewport
- L83 _public member_ `EIdentityTreeNodeIdentifier TreeNodeIdentifier;` — An identifier for scene components for relevant tree nodes
- L86 _public member_ `bool bVisible = true;` — If this node is visible in the tree. Note that an invisible node hides all its children even if they are tagged as visible

#### class `SMetaHumanIdentityPartsEditor`  
`class SMetaHumanIdentityPartsEditor : public SCompoundWidget`  
_L103-331_
- inherits: `SCompoundWidget`
- desc: A widget that allows editing the Parts of a Identity. It displays a button to add new Parts and a tree view with the hierarchy of Parts and Poses that form a Identity
- L107 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanIdentityPartsEditor)`
- L110 _public prototype_ `SLATE_ARGUMENT(class UMetaHumanIdentity*, Identity)` — The Identity we are editing
- L116 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<class FMetaHumanIdentityViewportClient>, ViewportClient)` — A reference to the viewport client where scene components can be displayed
- L140 _public prototype_ `~SMetaHumanIdentityPartsEditor();`
- L147 _public prototype_ `void AddPartsFromAsset(class UObject* InAsset, bool bInIsInputConformed = false);` — Create all the components from a given asset. If the asset is a Static Or Skeletal Mesh it creates a CaptureData, Face and Neutral pose directly from the given mesh. If the asset is a Footage Capture Data is creates a Face and Neutral Pose with the footage attached to it.
- L150 _public prototype_ `class UPrimitiveComponent* GetSceneComponentOfType(EIdentityTreeNodeIdentifier InComponentIdentifier, bool bInInstance) const;` — Returns the scene component of the given identifier or nullptr if there isn't one
- L153 _public prototype_ `class UPrimitiveComponent* GetPrimitiveComponent(class UPrimitiveComponent* InComponent, bool bInInstance) const;`
- L156 _public prototype_ `TArray<class UPrimitiveComponent*> GetAllPrimitiveComponents() const;`
- L159 _public prototype_ `TArray<class UPrimitiveComponent*> GetSelectedComponents() const;`
- L162 _public prototype_ `EIdentityPoseType GetSelectedPoseType() const;` — Returns the pose type that has been selected in the tree view. Invalid if no pose is selected
- L165 _public prototype_ `void SelectNode(EIdentityTreeNodeIdentifier InNodeIdentifier);`
- L168 _public prototype_ `void UpdateCurrentPoseForViewportSelection();` — Update the current pose for viewport if pose is selected in tree view
- L171 _public prototype_ `void UpdateViewportSelectionOutlines(bool bShowSelectionOutlines = true);` — Update the selection highlights in the viewport.
- L174 _public prototype_ `void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged);` — Called whenever a property is edited in the details panel
- L177 _public prototype_ `bool HandleUndoOrRedoTransaction(const class FTransaction* InTransaction);` — Handles an undo/redo transaction. Returns true if the editor was modified as a result.
- L181 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget Interface
- L185 _private prototype_ `void BindCommands();` — Creates and binds the list of commands used in this widget
- L195 _private prototype_ `void FindAllPreviewSceneComponents(const TSharedRef<FIdentityTreeNode>& InNode, TArray<UPrimitiveComponent*>& OutPreviewComponents, bool bInInstances, bool bInOnlyVisible) const;` — Recursively gets all preview scene components currently store in a node and its descendants with the option to only returns the ones that are visible @param InNode The node to start the search from @param OutPreviewComponents The list of components matching the search criteria @param bInInstances Return the instances of the the scene components that are actually displayed in the viewport @param bInOnlyVisible Return only the components that are currently set to be visible
- L198 _private prototype_ `void AddAllPreviewSceneComponentInstances(const TSharedRef<FIdentityTreeNode>& InNode);` — Adds all preview scene components from the given node and all its children
- L201 _private prototype_ `void RemoveAllPreviewSceneComponents(const TSharedRef<FIdentityTreeNode>& InNode);` — Removes all preview scene components from the viewport
- L204 _private prototype_ `void RefreshWidget();` — Rebuilds the tree view and updates the viewport accordingly
- L207 _private prototype_ `void RefreshIdentityTree();` — Recreates the Identity hierarchy tree, useful when handling undo operations
- L210 _private prototype_ `void HandleAddIdentityPartOfClass(TSubclassOf<class UMetaHumanIdentityPart> InIdentityPartClass);` — Handles the addition of a new Identity Part of the specified class
- L213 _private prototype_ `void HandleAddIdentityPoseOfClass(TSubclassOf<class UMetaHumanIdentityPose> InIdentityPoseClass, EIdentityPoseType InPoseType);` — Handles the addition of a new Identity Pose of the specified class
- L216 _private prototype_ `TSharedRef<class ITableRow> HandleIdentityTreeGenerateRow(TSharedRef<FIdentityTreeNode> InNode, const TSharedRef<class STableViewBase>& InOwnerTable);` — Handles the generation of a row in the tree view
- L219 _private prototype_ `void HandleIdentityTreeGetChildren(TSharedRef<FIdentityTreeNode> InItem, TArray<TSharedRef<FIdentityTreeNode>>& OutChildren);` — Returns the children of a given node in the three
- L222 _private prototype_ `void HandleIdentityTreeSelectionChanged(TSharedPtr<FIdentityTreeNode> InItem, ESelectInfo::Type InSelectInfo);` — Handles selection events in the tree view
- L225 _private prototype_ `void HandleIdentityTreeExpansionRecursive(TSharedRef<FIdentityTreeNode> InItem, bool bInShouldExpand);` — Handles recursive expansion on the tree widget when Shift + Click in a node
- L228 _private prototype_ `void HandleIdentityFilterTextChanged(const FText& InFilterText);` — Handles a change in the text used to filter the tree view
- L231 _private prototype_ `void HandleIdentityTreeDeleteSelectedNode();` — Handles deleting the selected node in the Identity tree view
- L234 _private prototype_ `void HandleIdentityPoseCaptureDataChanged(bool bInResetRanges, class UMetaHumanIdentityPose* InIdentityPose);` — Handles a change in the capture data used for the given pose
- L237 _private prototype_ `void HandleFocusToSelection();` — Handles focusing on the current selected item in the tree view
- L240 _private prototype_ `TSharedPtr<SWidget> HandleIdentityTreeContextMenu();` — Creates the context menu for a node in the Identity tree view
- L243 _private prototype_ `void HandleSceneComponentClicked(const class UPrimitiveComponent* InSceneComponent);` — Handles a click in a scene component in the viewport
- L246 _private prototype_ `void ClearIdentityTreeFilter(TSharedRef<FIdentityTreeNode> InNode);` — Recursively set all nodes to be visible in the tree view.
- L249 _private prototype_ `bool FilterIdentityTree(TSharedRef<FIdentityTreeNode> InNode, const FString& InFilterString);` — Recursively filter nodes from the tree view based on the given filter string
- L252 _private prototype_ `void SelectAndExpandIdentityTreeNode(TSharedRef<FIdentityTreeNode> InNode);` — Select and expand to the given node in the tree view
- L255 _private prototype_ `bool IdentityPartOfClassExists(TSubclassOf<class UMetaHumanIdentityPart> InIdentityPartClass) const;` — Returns true if a part of the given class exists in the treeview
- L258 _private prototype_ `bool CanAddIdentityPartOfClass(TSubclassOf<class UMetaHumanIdentityPart> InIdentityPartClass) const;` — Returns true if a part of the given class can be added to the Identity being edited
- L261 _private prototype_ `bool CanAddIdentityPoseOfClass(TSubclassOf<class UMetaHumanIdentityPose> InIdentityPoseClass, EIdentityPoseType InPoseType) const;` — Returns true if a pose of the given class and type can be added to the Identity being edited
- L264 _private prototype_ `bool CanDeleteSelectedIdentityTreeNode() const;` — Returns true if the selected node in the Identity tree view can be deleted
- L267 _private prototype_ `bool CanFocusToSelection() const;` — Returns true if the current selected node in the tree view can focus on the viewport, i.e., if it has a scene component
- L270 _private prototype_ `bool IsIdentityTreeValid() const;` — Returns true if the Identity tree has its root node created
- L273 _private prototype_ `TSharedRef<FIdentityTreeNode> GetIdentityRootNode() const;` — Returns the root node of in the tree view
- L276 _private prototype_ `class UMetaHumanIdentity* GetIdentity() const;` — Returns a pointer to the Identity we are editing which is stored in the root node of the tree
- L279 _private prototype_ `class FPreviewScene* GetPreviewScene() const;` — Returns a pointer to the preview scene where scene components are being displayed
- L282 _private prototype_ `TSharedPtr<FIdentityTreeNode> FindIdentityPartNodeByClass(TSubclassOf<class UMetaHumanIdentityPart> InIdentityPart, const TSharedRef<FIdentityTreeNode>& InNode) const;` — Recursively looks for a Identity Part of the given class
- L285 _private prototype_ `TSharedPtr<FIdentityTreeNode> FindIdentityTreeNode(const UObject* InObject, const TSharedRef<FIdentityTreeNode>& InNode) const;` — Recursively looks for a node that holds the given UObject
- L288 _private prototype_ `TSharedPtr<FIdentityTreeNode> FindIdentityNodeByComponentId(EIdentityTreeNodeIdentifier InComponenetIdentifier, const TSharedRef<FIdentityTreeNode>& InNode) const;` — Recursively looks for a node holding the given component identifier
- L291 _private prototype_ `void UpdateSceneComponentVisiblity();` — Update the scene component visibility for identity. Triggers an update on the viewport client
- L295 _private member_ `TWeakObjectPtr<class AActor> IdentityPreviewActorInstance;` — The actor representing the identity in the viewport. Used to attach components for rendering Identity Parts and Poses
- L298 _private member_ `TWeakObjectPtr<class UMetaHumanIdentity> IdentityPtr;` — Reference to the Identity object we are editing
- L301 _private member_ `TSharedPtr<class FMetaHumanIdentityViewportClient> ViewportClient;` — The viewport client of the preview scene
- L304 _private member_ `TSharedPtr<class FUICommandList> CommandList;` — Command list for handling actions in the tree view
- L307 _private member_ `TSharedPtr<STreeView<TSharedRef<FIdentityTreeNode>>> IdentityTreeWidget;` — A pointer to the Identity tree view
- L310 _private member_ `TArray<TSharedRef<FIdentityTreeNode>> RootNodes;` — List of root nodes of the Identity tree. This will have a single element but an array is required for the tree view
- L313 _private member_ `EIdentityPoseType CurrentPoseForViewport;` — Variable that holds the last selected pose to be displayed as current pose in the viewport
- L316 _private member_ `FIdentityPartAdded OnIdentityPartAddedDelegate;` — Delegate called when a new Identity Part was added to the Identity
- L319 _private member_ `FIdentityPartRemoved OnIdentityPartRemovedDelegate;` — Delegate called when a Identity Part was removed from the Identity in a given Part
- L322 _private member_ `FIdentityPoseAdded OnIdentityPoseAddedDelegate;` — Delegate called when a new Identity Pose was added to the Identity
- L325 _private member_ `FIdentityPoseRemoved OnIdentityPoseRemovedDelegate;` — Delegate called when a Identity pose was removed from the Identity in a given Part
- L328 _private member_ `FIdentityTreeSelectionChanged OnIdentityTreeSelectionChangedDelegate;` — Delegated called when a new node in the tree view is selected
- L330 _private member_ `FCaptureDataChanged OnCaptureSourceSelectionChangedDelegate;`

#### Free symbols / members of external scopes

- L92 _delegate_ `DECLARE_DELEGATE_OneParam(FIdentityPartAdded, class UMetaHumanIdentityPart* InIdentityPart) DECLARE_DELEGATE_OneParam(FIdentityPartRemoved, class UMetaHumanIdentityPart* InIdentityPart) DECLARE_DELEGATE_TwoParams(FIdentityPoseAdded, class UMetaHumanIdentityPose* InIdentityPose, class UMetaHumanIdentityPart* InIdentityPart) DECLARE_DELEGATE_TwoParams(FIdentityPoseRemoved, class UMetaHumanIdentityPose* InIdentityPose, class UMetaHumanIdentityPart* InIdentityPart) DECLARE_DELEGATE_TwoParams(FIdentityTreeSelectionChanged, class UObject* InObject, EIdentityTreeNodeIdentifier InNodeIdentifier) DECLARE_DELEGATE_FourParams(FCaptureDataChanged, class UCaptureData* InCaptureData, ETimecodeAlignment InTimecodeAlignment, const FString& InCamera, bool bInResetRanges) class SMetaHumanIdentityPartsEditor : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPartsEditor) {}`
- L93 _delegate_ `DECLARE_DELEGATE_OneParam(FIdentityPartRemoved, class UMetaHumanIdentityPart* InIdentityPart) DECLARE_DELEGATE_TwoParams(FIdentityPoseAdded, class UMetaHumanIdentityPose* InIdentityPose, class UMetaHumanIdentityPart* InIdentityPart) DECLARE_DELEGATE_TwoParams(FIdentityPoseRemoved, class UMetaHumanIdentityPose* InIdentityPose, class UMetaHumanIdentityPart* InIdentityPart) DECLARE_DELEGATE_TwoParams(FIdentityTreeSelectionChanged, class UObject* InObject, EIdentityTreeNodeIdentifier InNodeIdentifier) DECLARE_DELEGATE_FourParams(FCaptureDataChanged, class UCaptureData* InCaptureData, ETimecodeAlignment InTimecodeAlignment, const FString& InCamera, bool bInResetRanges) class SMetaHumanIdentityPartsEditor : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPartsEditor) {}`
- L94 _delegate_ `DECLARE_DELEGATE_TwoParams(FIdentityPoseAdded, class UMetaHumanIdentityPose* InIdentityPose, class UMetaHumanIdentityPart* InIdentityPart) DECLARE_DELEGATE_TwoParams(FIdentityPoseRemoved, class UMetaHumanIdentityPose* InIdentityPose, class UMetaHumanIdentityPart* InIdentityPart) DECLARE_DELEGATE_TwoParams(FIdentityTreeSelectionChanged, class UObject* InObject, EIdentityTreeNodeIdentifier InNodeIdentifier) DECLARE_DELEGATE_FourParams(FCaptureDataChanged, class UCaptureData* InCaptureData, ETimecodeAlignment InTimecodeAlignment, const FString& InCamera, bool bInResetRanges) class SMetaHumanIdentityPartsEditor : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPartsEditor) {}`
- L95 _delegate_ `DECLARE_DELEGATE_TwoParams(FIdentityPoseRemoved, class UMetaHumanIdentityPose* InIdentityPose, class UMetaHumanIdentityPart* InIdentityPart) DECLARE_DELEGATE_TwoParams(FIdentityTreeSelectionChanged, class UObject* InObject, EIdentityTreeNodeIdentifier InNodeIdentifier) DECLARE_DELEGATE_FourParams(FCaptureDataChanged, class UCaptureData* InCaptureData, ETimecodeAlignment InTimecodeAlignment, const FString& InCamera, bool bInResetRanges) class SMetaHumanIdentityPartsEditor : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPartsEditor) {}`
- L96 _delegate_ `DECLARE_DELEGATE_TwoParams(FIdentityTreeSelectionChanged, class UObject* InObject, EIdentityTreeNodeIdentifier InNodeIdentifier) DECLARE_DELEGATE_FourParams(FCaptureDataChanged, class UCaptureData* InCaptureData, ETimecodeAlignment InTimecodeAlignment, const FString& InCamera, bool bInResetRanges) class SMetaHumanIdentityPartsEditor : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPartsEditor) {}`
- L97 _delegate_ `DECLARE_DELEGATE_FourParams(FCaptureDataChanged, class UCaptureData* InCaptureData, ETimecodeAlignment InTimecodeAlignment, const FString& InCamera, bool bInResetRanges) class SMetaHumanIdentityPartsEditor : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPartsEditor) {}`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentityEditor/Private/UI/SMetaHumanIdentityPromotedFramesEditor.h` (Private)


#### class `USelectedPromotedFrameIndexHolder`  
`class USelectedPromotedFrameIndexHolder : public UObject`  
_L18-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: An object used to store selected promoted frame as UPROPERTY
- L25 _public member_ `TWeakPtr<class SMetaHumanIdentityPromotedFramesEditor> PromotedFramesEditor;` — A reference to the Promoted Frames Editor widget
- L29 _public member_ `int32 PromotedFrameIndex = INDEX_NONE;` — `UPROPERTY()` — The index of the promoted frame we are creating the context menu for

#### class `SMetaHumanIdentityPromotedFramesEditor`  
`class SMetaHumanIdentityPromotedFramesEditor : public SCompoundWidget`  
_L44-287_
- inherits: `SCompoundWidget`
- desc: The Promoted Frames editor is responsible for creating new Promoted Frames and displaying a UI that allows the user to select it. Each Promoted Frame is displayed as a custom SButton that can be selected by clicking. There are also buttons to promote a new frame and remove the selected one. The Promoted Frames editor also handles undo/redo events and updates the UI accordingly.
- L48 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanIdentityPromotedFramesEditor)`
- L51 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<class FMetaHumanIdentityViewportClient>, ViewportClient)` — A reference to the viewport client used to read the camera transform for a given promoted frame
- L87 _public prototype_ `void Construct(const FArguments& InArgs);`
- L90 _public prototype_ `void SetIdentityPose(class UMetaHumanIdentityPose* InPose);` — Sets a Identity Pose to be edited by this widget
- L93 _public prototype_ `void HandlePromotedFrameRemovedFromSequencer(int32 InFrameNumber);` — Called when removing the keys from sequencer
- L96 _public prototype_ `class UMetaHumanIdentityPose* GetIdentityPose() const;` — Returns the current pose being edited
- L99 _public prototype_ `class UMetaHumanIdentityPromotedFrame* GetSelectedPromotedFrame() const;` — Returns the current selected Promoted Frame or nullptr if there isn't one selected
- L103 _public prototype_ `void SetSelection(int32 InIndex, bool bInForceNotify = false);` — Set the current selection to the the one pointed by the InIndex called by Outliner when selecting a frame in the Outliner's Frames Panel
- L106 _public prototype_ `void RecreateAllPromotedFramesButtons();` — Removes and creates all promoted frames buttons
- L111 _public prototype_ `void HandleUndoOrRedoTransaction(const class FTransaction* InTransaction);` — Handles an undo/redo transaction
- L114 _public prototype_ `void HandleOnAddPromotedFrameClicked();` — Called when the promote button is clicked
- L117 _public prototype_ `bool CanAddPromotedFrame() const;` — Returns true if a new Promoted Frame can be added for the Pose being edited
- L120 _public prototype_ `bool CanSetViewAsFront() const;` — Returns true if the option to select front frame should be visible
- L122 _public prototype_ `void RecreatePromotedFrameButtonsForUndoRedo(const UMetaHumanIdentityPromotedFrame* InSelectedPromotedFrame);`
- L125 _public prototype_ `void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged);` — Called whenever a property is edited in the details panel
- L128 _public prototype_ `FText GetPromotedFramesContainerTooltip() const;` — Returns a dynamic tooltip for Promoted Frames Container depending on whether a Pose is selected
- L131 _public prototype_ `FText GetPromoteFrameButtonTooltip() const;` — Returns a dynamic tooltip for Promote a Frame button
- L134 _public prototype_ `FText GetDemoteFrameButtonTooltip() const;` — Returns a dynamic tooltip for Demote a Frame button
- L138 _private prototype_ `void BindCommands();` — Bind commands to actions that are specific for handling promoted frames
- L141 _private prototype_ `bool IsSelectionValid() const;` — Returns true if the current selection is a valid index
- L144 _private prototype_ `void AddPromotedFrameButton(class UMetaHumanIdentityPromotedFrame* InPromotedFrame, int32 InIndex);` — Adds a Promoted Frame button at the given index
- L147 _private prototype_ `void RemovePromotedFrameButton(int32 InIndex);` — Removes an Promoted Frame button at the given index. Does nothing if the index is not in valid
- L150 _private prototype_ `void AddAllPromotedFrameButtons();` — Adds Promoted Frame buttons to the UI with playback restriction added where applicable
- L153 _private prototype_ `void AddButtonsForPromotedFrames(const TArray<UMetaHumanIdentityPromotedFrame*>& InPromotedFrames);` — Adds Promoted Frame buttons for the list provided
- L156 _private prototype_ `void RemoveAllPromotedFrameButtons();` — Remove all Promoted Frame buttons from the UI. This will also clear the current selection, if there is one
- L159 _private prototype_ `void ClearSelection();` — Clears the selection
- L162 _private prototype_ `bool IsPoseValid() const;` — Returns true if we are currently editing a valid Identity Pose with a valid Promoted Frame Class that can be instantiated
- L165 _private prototype_ `bool IsPromotedFrameNumberBelowLimit() const;` — Returns true if maximum number of promoted frames
- L168 _private prototype_ `bool UndoControlVertexManipulation(const class FTransaction* InTransaction, const UMetaHumanIdentityPromotedFrame* InSelectedPromotedFrame, bool InIsRedo) const;` — Returns true if undo operation involved reverting control vertex manipulation only
- L171 _private prototype_ `bool SetFrontFrameFromDialog();` — Creates a dialog prompting user to set first promoted frame as front
- L174 _private prototype_ `TSharedRef<class SPromotedFrameButton> GetPromotedFrameButton(int32 InIndex) const;` — Returns a reference to the Promoted Frame button at the given index
- L177 _private prototype_ `TSharedRef<SWidget> GetPromotedFrameContextMenu(int32 InPromotedFrameIndex);` — Creates the context menu for the promoted frame of the given index
- L180 _private prototype_ `void HandleOnRemovePromotedFrameClicked(int32 InPromotedFrameIndex = INDEX_NONE, bool bInBroadcast = true);` — Called when the unpromote button is clicked
- L183 _private prototype_ `void HandlePromotedFrameButtonClicked(class UMetaHumanIdentityPromotedFrame* InPromotedFrame, int32 InIndex);` — Called when one Promoted Frame button is clicked in the UI
- L186 _private prototype_ `void HandleIdentityPoseCaptureDataChanged(bool bInResetRanges);` — Called when the capture source of the pose changes externally
- L189 _private prototype_ `void HandleViewportCameraMoved();` — Called when the camera in the viewport moves. Used to update the camera transform of the selected promoted frame
- L192 _private prototype_ `void HandleViewportCameraStopped();` — Called when the camera in the viewport stops moving. Used to commit the transaction holding camera transformation changes
- L195 _private prototype_ `void HandleViewportSettingsChanged();` — Called when the viewport settings has changed. Used to store any relevant changes into the select promoted frame
- L198 _private prototype_ `bool HandleShouldUnlockNavigation() const;`
- L201 _private prototype_ `void HandlePromotedFrameTrackingModeChanged(class UMetaHumanIdentityPromotedFrame* InPromotedFrame, bool bInTrackOnChange) const;` — Handles a change in the tracking mode of a Promoted Frame
- L204 _private prototype_ `void HandlePromotedFrameCameraTransformChanged(class UMetaHumanIdentityPromotedFrame* InPromotedFrame) const;` — Updates the viewport camera when the Promoted Frame camera transform changes and this is the currently selected Promoted Frame
- L207 _private prototype_ `void HandlePromotedFrameToggleNavigationLocked(class UMetaHumanIdentityPromotedFrame* InPromotedFrame) const;` — Handles changes in the navigation locked state of the given Promoted Frame
- L210 _private prototype_ `void HandleFrontViewToggled(UMetaHumanIdentityPromotedFrame* InPromotedFrame);` — Handles changes in the front view selection for promoted frames. Only 1 promoted frame can be labeled as front
- L213 _private prototype_ `void RegisterPromotedFrameCameraTransformChange(class UMetaHumanIdentityPromotedFrame* InPromotedFrame) const;` — Registers the HandlePromotedFrameCameraTransformChanged as a delegate called when the camera transform changes in the Promoted Frame
- L216 _private prototype_ `void StoreRenderingState(class UMetaHumanIdentityPromotedFrame* InPromotedFrame) const;` — Stores the current rendering state in the given Promoted Frame
- L219 _private prototype_ `void LoadRenderingState(class UMetaHumanIdentityPromotedFrame* InPromotedFrame) const;` — Loads the rendering state stored in the Promoted Frame and sets it in the viewport
- L223 _private member_ `static const TCHAR* PromotedFramesTransactionContext;` — The transaction context identifier for transactions done in the Identity Pose being edited
- L226 _private member_ `TUniquePtr<class FScopedTransaction> ScopedTransaction;` — The transaction used to track changes in the camera transform for a given promoted frame
- L229 _private member_ `FOnPromotedFrameSelectionChanged OnPromotedFrameSelectionChangedDelegate;` — Delegate called when the selection state of a Promoted Frame changes
- L232 _private member_ `FOnPromotedFrameAdded OnPromotedFrameAddedDelegate;` — Delegate called when the add promoted frame button is clicked
- L235 _private member_ `FOnPromotedFrameRemoved OnPromotedFrameRemovedDelegate;` — Delegate called when a promoted frame is removed from the pose
- L238 _private member_ `FOnPromotedFrameNavigationLockedChanged OnPromotedFrameNavigationLockedChangedDelegate;` — Delegate called when the navigation locked state of a Promoted Frame changes
- L241 _private member_ `FOnPromotedFrameTrackingModeChanged OnPromotedFrameTrackingModeChangedDelegate;` — Delegate called when the tracking mode for a promoted frame changes
- L244 _private member_ `TWeakObjectPtr<class UMetaHumanIdentityPose> IdentityPose;` — A reference to the pose being edited
- L247 _private member_ `TWeakObjectPtr<class UMetaHumanIdentity> Identity;` — A reference to the identity the pose belongs to
- L250 _private member_ `TSharedPtr<class FMetaHumanIdentityViewportClient> ViewportClient;` — A reference to the viewport client where the pose components are being displayed
- L253 _private member_ `TSharedPtr<class SHorizontalBox> PromotedFramesContainer;` — A container for adding new Promoted Frames
- L256 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The command list with actions associated with this editor
- L259 _private member_ `TObjectPtr<USelectedPromotedFrameIndexHolder> IndexHolder;` — An object that holds frame index as UPROPERTY to store promoted frame change in undo stack
- L262 _private member_ `TAttribute<TRange<int32>> FrameRange;` — An attribute to retrieve the Playback range from the sequencer
- L265 _private member_ `TAttribute<bool> IsTrackingCurrentFrame;` — Attribute used to query if the current promoted frame is being tracked and prevent new ones from being added
- L268 _private member_ `TAttribute<UMetaHumanIdentityPose::ECurrentFrameValid> IsCurrentFrameValid;` — An attribute to retrieve if the current frame is valid
- L271 _private prototype_ `ECheckBoxState IsFreeRoamingCameraButtonCheckedHandler() const;` — A delegate that returns the checked state of the Free Roam camera mode button
- L274 _private prototype_ `void OnFreeRoamingCameraCheckStateChangedHandler(ECheckBoxState InCheckState);` — A delegate to call when the check state of Free Roaming camera toggle is changed
- L277 _private prototype_ `void OnCheckStateChangedHandler(enum ECheckBoxState InCheckState);` — A delegate to call when the check state of any button in the Promoted Frames Timeline is checked (clears out the selection)
- L280 _private member_ `static const FSlateColorBrush PromotedFramesTimelineBackgroundBrush;` — A brush to use for Promoted Frames Timeline background
- L283 _private member_ `static const int32 NeutralPoseFrameLimit;` — Maximum number of promoted frames for neutral pose
- L286 _private member_ `static const int32 TeethPoseFrameLimit;` — Maximum number of promoted frames for teeth pose

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnPromotedFrameSelectionChanged, class UMetaHumanIdentityPromotedFrame* InPromotedFrame, bool bForceNotify) DECLARE_DELEGATE_OneParam(FOnPromotedFrameTrackingModeChanged, class UMetaHumanIdentityPromotedFrame* InPromotedFrame) DECLARE_DELEGATE_OneParam(FOnPromotedFrameNavigationLockedChanged, class UMetaHumanIdentityPromotedFrame* InPromotedFrame) DECLARE_DELEGATE_OneParam(FOnPromotedFrameAdded, class UMetaHumanIdentityPromotedFrame*) DECLARE_DELEGATE_OneParam(FOnPromotedFrameRemoved, class UMetaHumanIdentityPromotedFrame* InPromotedFrame) class SMetaHumanIdentityPromotedFramesEditor : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPromotedFramesEditor) {}`
- L33 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPromotedFrameTrackingModeChanged, class UMetaHumanIdentityPromotedFrame* InPromotedFrame) DECLARE_DELEGATE_OneParam(FOnPromotedFrameNavigationLockedChanged, class UMetaHumanIdentityPromotedFrame* InPromotedFrame) DECLARE_DELEGATE_OneParam(FOnPromotedFrameAdded, class UMetaHumanIdentityPromotedFrame*) DECLARE_DELEGATE_OneParam(FOnPromotedFrameRemoved, class UMetaHumanIdentityPromotedFrame* InPromotedFrame) class SMetaHumanIdentityPromotedFramesEditor : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPromotedFramesEditor) {}`
- L34 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPromotedFrameNavigationLockedChanged, class UMetaHumanIdentityPromotedFrame* InPromotedFrame) DECLARE_DELEGATE_OneParam(FOnPromotedFrameAdded, class UMetaHumanIdentityPromotedFrame*) DECLARE_DELEGATE_OneParam(FOnPromotedFrameRemoved, class UMetaHumanIdentityPromotedFrame* InPromotedFrame) class SMetaHumanIdentityPromotedFramesEditor : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPromotedFramesEditor) {}`
- L35 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPromotedFrameAdded, class UMetaHumanIdentityPromotedFrame*) DECLARE_DELEGATE_OneParam(FOnPromotedFrameRemoved, class UMetaHumanIdentityPromotedFrame* InPromotedFrame) class SMetaHumanIdentityPromotedFramesEditor : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPromotedFramesEditor) {}`
- L36 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPromotedFrameRemoved, class UMetaHumanIdentityPromotedFrame* InPromotedFrame) class SMetaHumanIdentityPromotedFramesEditor : public SCompoundWidget { public: SLATE_BEGIN_ARGS(SMetaHumanIdentityPromotedFramesEditor) {}`
