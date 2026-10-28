# Plugins / TrajectoryTools

- module root: `Plugins/Experimental/Animation/TrajectoryTools/Source/TrajectoryTools`
- headers: 4; symbols: 183
- symbol kinds: class=6, enum=1, enumerator=6, function=17, macro=2, member=73, prototype=63, struct=15
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, EditorWidgets, Engine, GameplayInsights, InputCore, PropertyEditor, RewindDebugger, RewindDebuggerInterface, Slate, SlateCore, ToolMenus, ToolWidgets, TraceAnalysis, TraceInsights, TraceLog, TraceServices, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Animation/TrajectoryTools/Source/TrajectoryTools/Public/SExportTrajectoriesWindow.h` (Public)


#### class `UTrajectoryExportDetails`  
`class UTrajectoryExportDetails : public UObject`  
_L32-69_
- reflection: `UCLASS()`
- inherits: `UObject`
- L40 _public member_ `FTrajectoryExportSettings ExportSettings;` — `UPROPERTY(EditAnywhere, Category = "Export Settings", meta=(ShowOnlyInnerProperties))` — Used to determine how the trajectory will be transformed into a animation sequence
- L44 _public member_ `int NumberOfKeyFrames = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Information")` — Number of key frames the animation sequence will have
- L48 _public member_ `double PlayLength = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Information")` — Play length of the sequence obtained after backing trajectory
- L52 _public member_ `FTrajectoryExportAssetInfo ExportAssetInfo;` — `UPROPERTY(EditAnywhere, Category = "Output Asset", meta=(ShowOnlyInnerProperties))` — Used to create an asset for the trajectory to export its data on to.
- L55 _public function_ `void Reset()` — Reset all properties back to default values

#### struct `FPreviewData`  
`struct FPreviewData`  
_L72-98_
- desc: Holds all the information needed to display a trajectory in the preview viewport
- L75 _public member_ `int SourceIndex = INDEX_NONE;` — Index to access all the information related to the currently selected trajectory
- L81 _public member_ `} Viewport;`
- L84 _public member_ `TConstArrayView<FGameplayTrajectory> SourceTrajectories;` — Raw trajectories available
- L87 _public member_ `FGameplayTrajectory OutputTrajectory;` — Preview trajectory which is affected by the export settings
- L90 _public member_ `TObjectPtr<UTrajectoryExportDetails> Details = nullptr;` — We need to hold a pointer to be able to query the export settings and accurately display a preview trajectory
- L97 _public member_ `} Timeline;`

#### struct `FPreviewData::FViewportInfo`  
`struct FViewportInfo`  
_L77-81_
- L79 _public member_ `uint64 SourceSkeletalMeshComponentId = 0;`
- L80 _public member_ `FSkeletalMeshInfo SourceSkeletalMeshInfo;`

#### struct `FPreviewData::FTimelineInfo`  
`struct FTimelineInfo`  
_L93-97_
- desc: Holds stateful data used to draw timeline
- L95 _public member_ `bool bShouldDrawScrubber = false;`
- L96 _public member_ `double ScrubTime = 0;`

#### class `SPreviewTrajectoryViewport`  
`class SPreviewTrajectoryViewport : public SEditorViewport`  
_L101-138_
- inherits: `SEditorViewport`
- desc: Used to preview the trajectory to export given its settings (ExportRange,ExportFrameRage, etc).
- L106 _public function_ `SLATE_BEGIN_ARGS(SPreviewTrajectoryViewport)`
- L107 _public function_ `SLATE_ARGUMENT(TSharedPtr<FPreviewData>, PreviewData) SLATE_END_ARGS() SPreviewTrajectoryViewport() : PreviewScene(FPreviewScene::ConstructionValues()), PreviewData(nullptr)`
- L112 _public prototype_ `void Construct(const FArguments& InArgs);`
- L115 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — End SWidget
- L118 _public prototype_ `void ResetPreviewSkeletalMesh() const;`
- L119 _public prototype_ `void UpdatePreviewPoseFromScrubTime(double InTraceStartTime, double InTraceEndTime) const;`
- L121 _public function_ `TSharedPtr<FPreviewData> GetPreviewData() const`
- L125 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — Begin SEditorViewport interface
- L131 _private member_ `FPreviewScene PreviewScene;` — Scene to preview trajectory on
- L134 _private member_ `TSharedPtr<FPreviewData> PreviewData;` — Used to draw the trajectory
- L137 _private member_ `TObjectPtr<UDebugSkelMeshComponent> PreviewComponent;` — Used to display the pose of the scrub time

#### class `FPreviewTrajectoryViewportClient`  
`class FPreviewTrajectoryViewportClient : public FEditorViewportClient`  
_L141-156_
- inherits: `FEditorViewportClient`
- desc: Client for SPreviewTrajectoryViewport
- L146 _public prototype_ `FPreviewTrajectoryViewportClient(FPreviewScene& InPreviewScene, const TSharedRef<SPreviewTrajectoryViewport>& InPreviewTrajectoryViewport);`
- L149 _public prototype_ `virtual void Tick(float DeltaTime) override;` — Begin FEditorViewportClient interface
- L150 _public function_ `virtual FSceneInterface* GetScene() const override`
- L151 _public function_ `virtual FLinearColor GetBackgroundColor() const override`
- L152 _public function_ `virtual void SetViewMode(EViewModeIndex Index) override final`
- L153 _public prototype_ `virtual void Draw(const FSceneView* InView, FPrimitiveDrawInterface* InPDI) override;`
- L154 _public prototype_ `virtual void DrawCanvas(FViewport& InViewport, FSceneView& InView, FCanvas& InCanvas) override;`

#### class `SExportTrajectoriesWindow`  
`class SExportTrajectoriesWindow : public SCompoundWidget, FGCObject`  
_L159-244_
- inherits: `SCompoundWidget,FGCObject`
- desc: Widget that configures and export a trajectory(s) into an animation asset / sequence
- L163 _public function_ `SLATE_BEGIN_ARGS(SExportTrajectoriesWindow)`
- L164 _public function_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, WidgetWindow) SLATE_ARGUMENT(TArrayView<FName>, OwnerNames) SLATE_ARGUMENT(TArrayView<FRewindDebuggerTrajectory::FExtensionState::FDebugInfo>, DebugInfos) SLATE_ARGUMENT(TArrayView<FGameplayTrajectory>, Trajectories) SLATE_ARGUMENT(TArrayView<FSkeletalMeshInfo>, SkelMeshInfos) SLATE_END_ARGS() SExportTrajectoriesWindow()`
- L174 _public prototype_ `void Construct(const FArguments& InArgs);` — Usual Construct method of SWidgets. Constructs the slate UI and assigns the UI delegates.
- L177 _public function_ `virtual FString GetReferencerName() const override` — Begin FGCObject
- L178 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L195 _private prototype_ `TSharedRef<SWidget> OnGetTrajectoryPickerMenuContent();`
- L196 _private prototype_ `void OnTrajectoryPickerMenuOpened(bool bIsOpen);`
- L197 _private prototype_ `void OnFinishedChangingExportSettingsSelectionProperties(const FPropertyChangedEvent& PropertyChangedEvent);`
- L201 _private prototype_ `FText GetWarningMessage() const;`
- L202 _private prototype_ `EExportValidation GetExportValidation() const;`
- L203 _private prototype_ `void UpdateAssetInfo(FSoftObjectPath& OutSkeletonPath, FSoftObjectPath & OutSkeletalMeshPath) const;`
- L204 _private prototype_ `void UpdateViewportAfterTrajectorySelection();`
- L207 _private member_ `TWeakPtr<SWindow> WidgetWindow;` — Window owning this widget
- L217 _private member_ `} ImmutableState;` — TArrayView<FName> OwnerNames;
- L220 _private member_ `TArray<FGameplayTrajectory> Trajectories;` — Trajectories that are available for export
- L223 _private member_ `TArray<FName> TrajectoryOwnerNames;` — Names of the trajectories' associated objects
- L228 _private member_ `int SelectedTrajectoryIndex = INDEX_NONE;` — Index of trajectory to be exported
- L231 _private member_ `TObjectPtr<UTrajectoryExportDetails> ExportDetails;` — Used to determine how the trajectory should be exported / baked out
- L235 _private member_ `TSharedPtr<FPreviewData> PreviewData;`
- L239 _private member_ `TSharedPtr<IDetailsView> ExportDetailsView;`
- L240 _private member_ `TSharedPtr<SPreviewTrajectoryViewport> Viewport;`
- L241 _private member_ `TSharedPtr<SMenuAnchor> TrajectoryPickerComboButton;`
- L242 _private member_ `TSharedPtr<SWidget> ExportButton;`
- L243 _private member_ `TSharedPtr<SWidget> ViewportTimeline;`

#### enum `SExportTrajectoriesWindow::EExportValidation`  
`enum class EExportValidation`  
_L183-191_
- L185 _public enumerator_ `MultipleTraceRanges`
- L186 _public enumerator_ `NoTrajectorySelected`
- L187 _public enumerator_ `MissingAssetInfo`
- L188 _public enumerator_ `ExportPathIsInvalid`
- L189 _public enumerator_ `AssetAlreadyExists`
- L190 _public enumerator_ `Valid`

#### struct `SExportTrajectoriesWindow::ImmutableState`  
`struct ImmutableState`  
_L211-217_
- L214 _public member_ `TArrayView<FRewindDebuggerTrajectory::FExtensionState::FDebugInfo> DebugInfos;` — TArrayView<FGameplayTrajectory> Trajectories;
- L215 _public member_ `TArrayView<FSkeletalMeshInfo> SkeletalMeshInfos;`

### `Plugins/Experimental/Animation/TrajectoryTools/Source/TrajectoryTools/Public/TrajectoryExportOperation.h` (Public)


#### struct `FTrajectoryExportSettings`  
`struct FTrajectoryExportSettings`  
_L17-55_
- reflection: `USTRUCT()`
- L21 _public prototype_ `FTrajectoryExportSettings();`
- L25 _public member_ `FFrameRate FrameRate;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Frame rate for the exported asset
- L29 _public member_ `FFloatInterval Range;` — `UPROPERTY(EditAnywhere, meta=(Units="s"), Category = "Settings")` — Range of the trajectory to export. Note that the entire trajectory will be exported if the range is empty (Min == Max).
- L33 _public member_ `bool bShouldForceOrigin = false;` — `UPROPERTY(EditAnywhere, meta=(DisplayName="Force Origin"), Category = "Settings")` — Flag to determine if all trajectory samples should be relative to the frame given by ForceOriginAtTime
- L37 _public member_ `double OriginTime = 0;` — `UPROPERTY(EditAnywhere, meta=(EditCondition="bShouldForceOrigin", EditConditionHides, Units="s"), Category = "Settings")` — Specific which trajectory sample's position will be position at the origin given by the desired time. Note that if time for origin is less than 0 no origin will be enforced.
- L44 _public member_ `bool bShouldOverwriteExistingFiles = false;` — `UPROPERTY(EditAnywhere, meta=(DisplayName="Overwrite Existing Files"), Category = "Settings")` — Any files with the same name will be overwritten instead of creating a new file with a numeric suffix. This is useful when iterating on a batch process.
- L48 _public member_ `bool bShouldExportOnlyAnimatedBones = true;` — `UPROPERTY(EditAnywhere, meta=(DisplayName="Export Only Animated Bones"), Category = "Settings")` — Will not produce keys on bones that are not animated, reducing size on disk of the resulting files.
- L51 _public prototype_ `bool IsValid() const;` — All export settings are valid and trajectory can be generated without issues from them
- L54 _public prototype_ `void Reset();` — Reset trajectory to default values

#### struct `FTrajectoryExportAssetInfo`  
`struct FTrajectoryExportAssetInfo`  
_L59-86_
- reflection: `USTRUCT()`
- desc: All information needed to create an asset for a trajectory
- L65 _public member_ `FString AssetName;` — `UPROPERTY(EditAnywhere, Category = "Asset")` — Name of asset to be created during export. Defaulted to the name of the selected trajectory in UI.
- L69 _public member_ `FDirectoryPath FolderPath;` — `UPROPERTY(EditAnywhere, Category = "Asset", meta=(ContentDir))` — Directory path where to export asset to
- L73 _public member_ `FSoftObjectPath Skeleton;` — `UPROPERTY(VisibleAnywhere, Category = "Information")` — Path to skeleton to be used and assigned to the exported asset.
- L77 _public member_ `FSoftObjectPath SkeletalMesh;` — `UPROPERTY(VisibleAnywhere, Category = "Information")` — Path to skeletal mesh to be used and assigned to the exported asset.
- L79 _public prototype_ `bool IsExportPathValid() const;`
- L80 _public prototype_ `bool DoesAssetExistAtPath() const;`
- L81 _public prototype_ `bool CanCreateAsset() const;`
- L83 _public prototype_ `void Reset();`
- L85 _public prototype_ `bool IsValid() const;`

#### struct `FTrajectoryExportContext`  
`struct FTrajectoryExportContext`  
_L89-106_
- desc: Data needed to run an "export" operation on a trajectory.
- L92 _public member_ `FTrajectoryExportSettings Settings;` — Used when transforming trajectory data before saving/exporting it to an asset.
- L95 _public member_ `FTrajectoryExportAssetInfo AssetInfo;` — Used when creating the asset to hold the trajectory data.
- L98 _public member_ `FGameplayTrajectory* Data;` — Raw trajectory data that will be export after operation is complete.
- L101 _public member_ `FString SourceObjectName;` — Name of the object that we sourced the trajectory data from
- L103 _public prototype_ `void Reset();`
- L105 _public prototype_ `bool IsValid() const;`

#### class `UTrajectoryExportOperation`  
`class UTrajectoryExportOperation : public UObject`  
_L110-143_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Encapsulate ability to export a trajectory to the specified asset.
- L117 _public prototype_ `static void ExportTrajectory(FGameplayTrajectory* InTrajectory, const FTrajectoryExportSettings& InSettings, const FTrajectoryExportAssetInfo& InAssetInfo, const FString& InSourceObjectName);` — @todo: After having a general trajectory type, expose this to blueprint to allow for editor scripts, bp, etc to use this.
- L120 _public prototype_ `void Run(const FTrajectoryExportContext& Context);` — Actually run the process to export the trajectory for the given context.
- L125 _private prototype_ `void Reset();` — Clear any generated/saved info.
- L128 _private prototype_ `void GenerateAssets(const FTrajectoryExportContext& Context, FScopedSlowTask& Progress);` — Create assets to export the trajectory data to.
- L131 _private prototype_ `void ExportDataToAssets(const FTrajectoryExportContext& Context, FScopedSlowTask& Progress) const;` — Output trajectory data to their respective assets.
- L134 _private prototype_ `void NotifyUserOfResults(const FTrajectoryExportContext& Context, FScopedSlowTask& Progress) const;` — Output notifications of results.
- L137 _private prototype_ `void CleanupIfCancelled(const FScopedSlowTask& Progress) const;` — If user cancelled half way, cleanup all created asset(s).
- L139 _private member_ `TWeakObjectPtr<UAnimSequence> GeneratedAsset = nullptr;`
- L140 _private member_ `TWeakObjectPtr<UAnimSequence> AssetToProcess = nullptr;`
- L142 _private member_ `TUniquePtr<FScopedTransaction> ActiveTransaction = nullptr;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TRAJECTORYTOOLS_API`

### `Plugins/Experimental/Animation/TrajectoryTools/Source/TrajectoryTools/Public/TrajectoryLibrary.h` (Public)


#### struct `FGameplayTrajectory`  
`struct FGameplayTrajectory`  
_L18-68_
- reflection: `USTRUCT()`
- desc: @todo: Temp. This will be swapped for general purpose trajectory struct + poses array.
- L29 _public member_ `TArray<FSample> Samples;`
- L30 _public member_ `TArray<TArray<FTransform>> Poses;`
- L54 _public member_ `} TraceInfo;`
- L56 _public function_ `void Reset()`
- L64 _public function_ `bool IsValid() const`

#### struct `FGameplayTrajectory::FSample`  
`struct FSample`  
_L22-27_
- L24 _public member_ `double Time = 0;`
- L25 _public member_ `FVector Position = FVector::ZeroVector;`
- L26 _public member_ `FQuat Orientation = FQuat::Identity;`

#### struct `FGameplayTrajectory::FTraceRangedBuffers`  
`struct FTraceRangedBuffers`  
_L32-54_
- L34 _public member_ `TArray<TRange<int32>> Ranges;`
- L35 _public member_ `TArray<FSkeletalMeshInfo> SkeletalMeshInfos;`
- L37 _public function_ `int Num() const`
- L43 _public function_ `bool IsEmpty() const`
- L48 _public function_ `void Reset(int NewSize = 0)`

#### struct `FTrajectoryToolsLibrary`  
`struct FTrajectoryToolsLibrary`  
_L70-89_
- L78 _public prototype_ `static void GetRangeOverlaps(const FGameplayTrajectory& InTrajectory, const TRange<int32>& InSampleRange, FRangeOverlapTestResult& InOutOverlapResult);`
- L80 _public prototype_ `static void GetSampleIndicesForMatchedSampleTime(const FGameplayTrajectory& InTrajectory, double InRequestedSampleTime, TPair<int32, int32>& OutMatchedSampleIndicesRange);`
- L82 _public prototype_ `static bool GetTransformAtTimeInTrajectory(const FGameplayTrajectory& InTrajectory, double InRequestedTime, FTransform& OuTransform);`
- L84 _public prototype_ `static bool GetPoseAtTimeInTrajectory(const FGameplayTrajectory& InTrajectory, double InRequestedTime, TArray<FTransform>& OutCSPose);`
- L86 _public prototype_ `static void TransformTrajectoryToMatchFrameRate(const FGameplayTrajectory& InTrajectory, FFrameRate InFrameRate, FGameplayTrajectory& OutFrameMatchedTrajectory);`
- L88 _public prototype_ `static void TransformTrajectoryToMatchExportSettings(const FGameplayTrajectory& InTrajectory, const FTrajectoryExportSettings& InExportSettings, FGameplayTrajectory& OutTransformedTrajectory);`

#### struct `FTrajectoryToolsLibrary::FRangeOverlapTestResult`  
`struct FRangeOverlapTestResult`  
_L72-76_
- L74 _public member_ `bool bOverlaps = false;`
- L75 _public member_ `TArray<int> Ranges;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TRAJECTORYTOOLS_API`

### `Plugins/Experimental/Animation/TrajectoryTools/Source/TrajectoryTools/Public/TrajectoryRewindDebuggerExtension.h` (Public)


#### class `FRewindDebuggerTrajectory`  
`class FRewindDebuggerTrajectory : public IRewindDebuggerExtension`  
_L21-106_
- inherits: `IRewindDebuggerExtension`
- desc: A Rewind Debugger extension that allows user to visualize trajectories and export them from the current trace session.
- L25 _public prototype_ `FRewindDebuggerTrajectory();`
- L26 _public prototype_ `virtual ~FRewindDebuggerTrajectory();`
- L28 _public prototype_ `void Initialize();`
- L29 _public prototype_ `void Shutdown();`
- L30 _public prototype_ `void Reset();`
- L33 _public prototype_ `virtual void Update(float DeltaTime, IRewindDebugger* RewindDebugger) override;` — Begin IRewindDebuggerExtension implementation
- L34 _public prototype_ `virtual void AnalysisSessionOpened(IRewindDebugger* RewindDebugger) override;`
- L35 _public prototype_ `virtual void AnalysisSessionClosed(IRewindDebugger* RewindDebugger) override;`
- L36 _public prototype_ `virtual void Clear(IRewindDebugger* RewindDebugger) override;`
- L37 _public function_ `virtual FString GetName()`
- L42 _private prototype_ `void UpdateState(IRewindDebugger* RewindDebugger);`
- L46 _private prototype_ `void GenerateMenu();`
- L47 _private prototype_ `void MakeTrajectoriesMenu(FToolMenuSection& InSection);`
- L48 _private prototype_ `void MakeToggleDebugDrawMenu(UToolMenu* InMenu);`
- L52 _private prototype_ `void EnsureDebugDrawDelegateExists();`
- L53 _private prototype_ `void DebugDraw(UCanvas* InCanvas, APlayerController* InController);`
- L89 _private member_ `} State;`
- L91 _private member_ `TArray<FColor> DebugDrawColors;`
- L92 _private member_ `FDelegateHandle DebugDrawDelegateHandle;`
- L93 _private member_ `TWeakObjectPtr<UWorld> WorldToVisualize;`
- L94 _private member_ `TSharedPtr<SWindow> BakeOutWindow;`
- L96 _private prototype_ `void ShowBakeOutTrajectoryWindow();`
- L98 _private prototype_ `static void BuildTrajectoryOwnersList(const IRewindDebugger* InRewindDebugger, const IGameplayProvider* InGameplayProvider, double InTraceStartTime, double InTraceEndTime, TArray<FObjectInfo> & OutObjectInfos);`
- L99 _private prototype_ `static void BuildTrajectorySkeletalMeshInfoList(const IGameplayProvider* InGameplayProvider, const IAnimationProvider* InAnimationProvider, double InTraceStartTime, double InTraceEndTime, const TArray<FObjectInfo>& InSkeletalMeshComponentObjectInfos, TArray<FSkeletalMeshInfo>& OutSkeletalMeshInfos);`
- L100 _private prototype_ `static void BuildTrajectories(const IGameplayProvider* InGameplayProvider, const IAnimationProvider* InAnimationProvider, double InTraceStartTime, double InTraceEndTime, const TArray<FObjectInfo>& InObjectInfos, TArray<FGameplayTrajectory>& OutTrajectories);`
- L101 _private prototype_ `static void UpdateDebugInfos(const IGameplayProvider* InGameplayProvider, const TArray<FObjectInfo>& InObjectInfos, TArray<FExtensionState::FDebugInfo>& InOutDebugInfos);`
- L102 _private prototype_ `static FName GetFullNameForDebugInfoOwner(const IGameplayProvider* InGameplayProvider, uint64 InOwnerObjectId);`
- L103 _private prototype_ `static FText GetDebugInfoOwnerWorldPostFix(const FWorldInfo& InWorldInfo);`

#### struct `FRewindDebuggerTrajectory::FExtensionState`  
`struct FExtensionState`  
_L56-89_
- desc: Holds information from each extension's update
- L71 _public member_ `} Extract;`
- L73 _public member_ `TArray<FGameplayTrajectory> Trajectories;` — Trajectories extracted from trace session
- L74 _public member_ `TArray<FObjectInfo> ObjectInfos;` — Associated object's information for the extracted trajectories
- L75 _public member_ `TArray<FSkeletalMeshInfo> SkelMeshInfos;` — Associated object's skeletal mesh info for the extracted trajectories.
- L76 _public member_ `TArray<FDebugInfo> DebugInfos;` — Associated debug information for extracted trajectories
- L79 _public function_ `void Reset()` — Reset extension's state

#### struct `FRewindDebuggerTrajectory::FExtensionState::FDebugInfo`  
`struct FDebugInfo`  
_L59-64_
- desc: Information for UI / debug drawing
- L61 _public member_ `uint64 OwnerId = 0;`
- L62 _public member_ `FName Name = NAME_None;`
- L63 _public member_ `bool bShouldDraw = false;`

#### struct `FRewindDebuggerTrajectory::FExtensionState::FExtract`  
`struct FExtract`  
_L67-71_
- desc: Information to extract a trajectory/clip from a trace file
- L69 _public member_ `double TraceStarTime = 0;`
- L70 _public member_ `double TraceEndTime = 0;`
