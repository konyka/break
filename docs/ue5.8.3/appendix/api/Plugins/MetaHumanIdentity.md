# Plugins / MetaHumanIdentity

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentity`
- headers: 13; symbols: 586
- symbol kinds: class=22, delegate=5, enum=9, enumerator=50, function=10, macro=9, member=164, namespace=2, prototype=307, struct=6, typedef=2
- PrivateDependencyModuleNames: CameraCalibrationCore, CaptureDataCore, ControlRigDeveloper, Core, GeometryCore, ImgMedia, InterchangeDNA, JsonUtilities, MeshConversion, MeshDescription, MetaHumanCaptureDataEditor, MetaHumanConfig, MetaHumanCoreTech, MetaHumanFaceAnimationSolver, MetaHumanFaceContourTracker, MetaHumanFaceFittingSolver, MetaHumanPipeline, Projects, RigLogicModule, SkeletalMeshDescription, SkeletalMeshUtilitiesCommon, Slate, StaticMeshDescription, UnrealEd
- PublicDependencyModuleNames: CoreUObject, Engine, GeometryFramework, Json, MetaHumanCaptureData, MetaHumanCore, MetaHumanCoreTechLib, MetaHumanPipelineCore, MetaHumanSDKEditor, SlateCore

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentity/Private/MetaHumanIdentityModule.h` (Private)


#### class `FMetaHumanIdentityModule`  
`class FMetaHumanIdentityModule : public IModuleInterface`  
_L7-18_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `TSharedPtr<class FAssetTypeActions_MetaHumanIdentity> IdentityAssetActions;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentity/Public/LandmarkConfigIdentityHelper.h` (Public)


#### enum `ECurvePresetType`  
`enum class ECurvePresetType : uint8`  
_L13-20_
- L15 _public enumerator_ `Invalid = 0`
- L16 _public enumerator_ `Identity_NeutralPose`
- L17 _public enumerator_ `Identity_TeethPose`
- L18 _public enumerator_ `Performance`
- L19 _public enumerator_ `NeutralPose_NoBrowsNoIris`

#### struct `FMarkerCurveDef`  
`struct FMarkerCurveDef`  
_L23-34_
- desc: persistent data for curves, loaded from json
- L25 _public member_ `FString Name;`
- L26 _public member_ `FString StartPointName;`
- L27 _public member_ `FString EndPointName;`
- L29 _public member_ `TArray<int32> VertexIDs;`
- L30 _public member_ `TArray<FVector2D> DefaultScreenPoints;`
- L31 _public member_ `TArray<FString> GroupTagIDs;`
- L33 _public member_ `FString CurveMeshFromConfig;`

#### struct `FMarkerDefs`  
`struct FMarkerDefs`  
_L36-43_
- L38 _public member_ `TArray<FString> GroupNames;`
- L39 _public member_ `TArray<FMarkerCurveDef> CurveDefs;`
- L40 _public member_ `TMap<FString, int32> Landmarks;`
- L41 _public member_ `TMap<FString, FVector2D> DefaultScreenPoints;`
- L42 _public member_ `TMap<FString, FString> CurveMeshesForMarkers;`

#### class `FLandmarkConfigIdentityHelper`  
`class FLandmarkConfigIdentityHelper`  
_L45-97_
- L49 _public prototype_ `FLandmarkConfigIdentityHelper();`
- L50 _public prototype_ `~FLandmarkConfigIdentityHelper();`
- L53 _public prototype_ `TSharedPtr<struct FMarkerDefs> GetMarkerDefs() const;` — Returns all the marker definitions as per config
- L55 _public prototype_ `TArray<FString> GetGroupListForSelectedPreset(const ECurvePresetType& InSelectedPose) const;`
- L58 _public prototype_ `FFrameTrackingContourData ProjectPromotedFrameCurvesOnTemplateMesh(const struct FMinimalViewInfo& InViewInfo, const TMap<EIdentityPartMeshes, TArray<FVector>>& InTemplateMeshVertices, const ECurvePresetType& InSelectedPreset, const FIntRect& InViewRect) const;` — Projects the 2D points based on 3D position of vertex IDs of the archetype mesh
- L62 _public prototype_ `FFrameTrackingContourData GetDefaultContourDataFromConfig(const FVector2D& InTexResolution, const ECurvePresetType& InSelectedPreset) const;` — Uses preset values for curves in the config
- L65 _public prototype_ `ECurvePresetType GetCurvePresetFromIdentityPose(const EIdentityPoseType& InIdentityPoseType) const;` — Convert Identity Pose Type enum into a curve preset type
- L69 _private prototype_ `void GetProjectedScreenCoordinates(const TArray<FVector>& InWorldPositions, const struct FMinimalViewInfo& InViewInfo, TArray<FVector2d>& OutScreenPositions, const FIntRect& InViewRect) const;`
- L72 _private prototype_ `void PopulateMarkerDataFromConfig(const TMap<FJsonObject::FStringType, TSharedPtr<class FJsonValue>>& InConfigContourData);`
- L74 _private prototype_ `bool LoadCurvesAndLandmarksFromJson(const FString& InFileName);`
- L75 _private prototype_ `bool LoadGroupsFromJson(const FString& InFileName) const;`
- L77 _private prototype_ `TArray<struct FMarkerCurveDef> GetCurvesForPreset(const ECurvePresetType& InSelectedPose) const;`
- L79 _private prototype_ `EIdentityPartMeshes GetMeshPartFromConfigName(const FString& InMeshName) const;`
- L82 _private member_ `TSharedPtr<struct FMarkerDefs> MarkerDefs;` — A struct containing non-changing marker group and curve data
- L84 _private member_ `TSet<FString> NeutralPoseCurveExclusionList;`
- L85 _private member_ `TSet<FString> NeutralPoseGroupExclusionList;`
- L87 _private member_ `TSet<FString> TeethPoseCurveExclusionList;`
- L88 _private member_ `TSet<FString> TeethPoseGroupExclusionList;`
- L90 _private member_ `TSet<FString> PerformanceCurveList;`
- L91 _private member_ `TSet<FString> PerformanceCurveGroups;`
- L93 _private member_ `TSet<FString> NeutralNoBrowsIrisPoseCurveExclusionList;`
- L94 _private member_ `TSet<FString> NeutralNoBrowsPoseGroupExclusionList;`
- L96 _private member_ `const static FString ConfigGroupFileName;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANIDENTITY_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentity/Public/MetaHumanIdentity.h` (Public)


#### enum `EIdentityInvalidationState`  
`enum class EIdentityInvalidationState : uint8`  
_L26-29_
- reflection: `UENUM()`
- L28 _public enumerator_ `Solve`
- L28 _public enumerator_ `Solve`
- L28 _public enumerator_ `Solve`
- L28 _public enumerator_ `Solve`
- L28 _public enumerator_ `Solve`
- L28 _public enumerator_ `Solve`

#### class `UMetaHumanIdentityThumbnailInfo`  
`class UMetaHumanIdentityThumbnailInfo : public UThumbnailInfo`  
_L34-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UThumbnailInfo`
- desc: UMetaHumanIdentityThumbnailInfo
- L40 _public prototype_ `UMetaHumanIdentityThumbnailInfo();`
- L44 _public member_ `int32 OverridePromotedFrame;` — `UPROPERTY(EditAnywhere, Category = "Thumbnail")` — Override the Promoted Frame index used to generate the MetaHuman Identity thumbnail

#### class `UMetaHumanIdentity`  
`class UMetaHumanIdentity : public UObject`  
_L66-238_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: MetaHuman Identity Asset Provides the tools to auto-generate a fully rigged Skeletal Mesh of a human face from Capture Data (Mesh or Footage) by tracking the facial features, fitting a Template Mesh having MetaHuman topology to the tracked curves, and sending the resulting mesh to MetaHuman Service, which returns an auto-rigged SkeletalMesh resembling the person from the Capture Data. The obtained Skeletal Mesh can be used by MetaHuman Performance asset to generate an Animation Sequence from video footage. MetaHuman Identity Asset Toolkit can also create a full MetaHuman in MetaHuman Creator, downloadable through Quixel Bridge.
- L73 _public prototype_ `UMetaHumanIdentity();`
- L76 _public prototype_ `virtual void PostLoad() override;`
- L77 _public prototype_ `virtual void PostInitProperties() override;`
- L78 _public prototype_ `virtual FPrimaryAssetId GetPrimaryAssetId() const override;`
- L81 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAutoRigServiceFinishedDelegate, bool);`
- L82 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAutoRigServiceFinishedDynamicDelegate, bool, bInSuccess);`
- L87 _public member_ `FOnAutoRigServiceFinishedDynamicDelegate OnAutoRigServiceFinishedDynamicDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "Processing")` — Dynamic delegate called when the pipeline finishes running
- L90 _public member_ `FOnAutoRigServiceFinishedDelegate OnAutoRigServiceFinishedDelegate;` — Delegate called when the pipeline finishes running (used by toolkit)
- L94 _public prototype_ `class UMetaHumanIdentityPart* FindPartOfClass(TSubclassOf<class UMetaHumanIdentityPart> InPartClass) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parts")` — Looks for a Part of the given class in the array of parts. Returns nullptr if no Part was found
- L98 _public prototype_ `class UMetaHumanIdentityPart* GetOrCreatePartOfClass(TSubclassOf<class UMetaHumanIdentityPart> InPartClass);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parts")` — Looks for a Part of the given class in the array of parts. Creates and return a new one if not found
- L105 _public function_ `template<typename SearchType> SearchType* FindPartOfClass() const` — Searches for a Part of the given class in the array of parts. The class being searched must be a child of UMetaHumanIdentityPart.
- L113 _public prototype_ `bool CanAddPartOfClass(TSubclassOf<class UMetaHumanIdentityPart> InPartClass) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parts")` — Returns true if the given Part class can be added to the MetaHuman Identity being edited
- L117 _public prototype_ `bool CanAddPoseOfClass(TSubclassOf<class UMetaHumanIdentityPose> InPoseClass, EIdentityPoseType InPoseType) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parts")` — Returns true if the given Pose class can be added to the MetaHuman Identity being edited
- L123 _public prototype_ `EIdentityErrorCode ImportDNAFile(const FString& InDNAFilePath, EDNADataLayer InDnaDataLayer, const FString& InBrowsFilePath);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|MetaHuman Identity Creation")` — Initialize the MetaHuman Identity from a DNA file. The MetaHuman Identity must already have a face for this to succeeded
- L127 _public prototype_ `bool ExportDNADataToFiles(const FString& InDnaPathWithName, const FString& InBrowsPathWithName);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|MetaHuman Identity Creation")` — Export DNA and brows data to files at selected location
- L130 _public prototype_ `EIdentityErrorCode ImportDNA(TSharedPtr<class IDNAReader> InDNAReader, const TArray<uint8>& InBrowsBuffer);` — Initialize the MetaHuman Identity from a DNA. The MetaHuman Identity must already have a face for this to succeeded
- L135 _public prototype_ `void StartFrameTrackingPipeline(const TArray<FColor>& InImageData, int32 InWidth, int32 InHeight, const FString& InDepthFramePath, UMetaHumanIdentityPose* InPose, UMetaHumanIdentityPromotedFrame* InPromotedFrame, bool bInShowProgress);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Processing")`
- L139 _public prototype_ `void SetBlockingProcessing(bool bInBlockingProcessing);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Processing")`
- L142 _public prototype_ `bool IsFrameTrackingPipelineProcessing() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Processing")`
- L145 _public prototype_ `void LogInToAutoRigService();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|AutoRigging")`
- L149 _public prototype_ `bool IsLoggedInToService();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|AutoRigging")` — This function checks if there's a session stored. There is NO request sent to check if the token is actually valid
- L152 _public prototype_ `bool IsAutoRiggingInProgress();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|AutoRigging")`
- L155 _public prototype_ `void CreateDNAForIdentity(bool bInLogOnly);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|AutoRigging")`
- L158 _public prototype_ `bool DiagnosticsIndicatesProcessingIssue(FText& OutDiagnosticsWarningMessage) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Diagnostics")`
- L164 _public member_ `TArray<TObjectPtr<class UMetaHumanIdentityPart>> Parts;` — `UPROPERTY(BlueprintReadOnly, Category = "Parts")` — The list of Parts the make this Identity. See UMetaHumanIdentityPart
- L168 _public member_ `TObjectPtr<class UThumbnailInfo> ThumbnailInfo;` — `UPROPERTY(VisibleAnywhere, Instanced, AdvancedDisplay, Category = "Thumbnail")` — Information for thumbnail rendering
- L172 _public member_ `TObjectPtr<class UMetaHumanIdentityViewportSettings> ViewportSettings;` — `UPROPERTY(BlueprintReadWrite, Instanced, Category = "Viewport Settings")` — Stores the viewport settings for this MetaHuman Identity
- L177 _public member_ `EIdentityInvalidationState InvalidationState_DEPRECATED = EIdentityInvalidationState::None;` — `UPROPERTY()`
- L184 _public member_ `static const TCHAR* IdentityTransactionContext;` — The transaction context identifier for transactions done in the MetaHuman Identity being edited
- L188 _public prototype_ `static bool HandleError(EIdentityErrorCode InErrorCode, bool bInLogOnly = false);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Conforming")` — Deals with error produced by the MetaHuman Identity process - logs message and optionally show user dialog; returns false if an Error and true if no errors, or just a Warning
- L190 _public member_ `static const FText AutoRigServiceTitleError;`
- L191 _public member_ `static const FText AutoRigServiceTitleSuccess;`
- L193 _public prototype_ `UCaptureData* GetPoseCaptureData(EIdentityPoseType InPoseType) const;`
- L196 _public prototype_ `FString GetHashedIdentityAssetID();` — Returns a hashed PrimaryAssetType/PrimaryAssetName identifier. Used for telemetry
- L198 _public prototype_ `bool GetMetaHumanAuthoringObjectsPresent() const;`
- L202 _private prototype_ `void StartPipeline(const TArray<FColor>& InImageData, int32 InWidth, int32 InHeight, const FString& InDepthFramePath, const TArray<FCameraCalibration>& InCalibrations, const FString& InCamera, UMetaHumanIdentityPromotedFrame* InPromotedFrame, bool bInShowProgress, bool bInSkipDiagnostics);`
- L206 _private prototype_ `void AutoRigProgressEnd(bool bSuccess) const;`
- L208 _private prototype_ `void AutoRigSolveFinished(bool bSuccess, bool bInLogOnly);`
- L210 _private prototype_ `void HandleIdentityForAutoRigValidation(EAutoRigIdentityValidationError InErrorCode, bool bInLogOnly = false);`
- L213 _private prototype_ `void HandleAutoRigServiceError(EMetaHumanServiceRequestResult InServiceError, bool bInLogOnly);`
- L216 _private prototype_ `bool IdentityIsReadyForAutoRig(TArray<FVector>& OutConformedFaceVertices, TArray<FVector>& OutConformedLeftEyeVertices, TArray<FVector>& OutConformedRightEyeVertices, bool bInLogOnly);`
- L222 _private member_ `TUniquePtr<UE::MetaHuman::Pipeline::FPipeline> TrackPipeline;` — Pipeline for tracking Promoted Frames
- L224 _private member_ `bool bBlockingProcessing = false;`
- L227 _private member_ `bool bIsAutorigging = false;` — True if the auto rigging service has been called
- L231 _private prototype_ `void SendTelemetryForIdentityAutorigRequest(bool bIsFootageData);` — Sends a telemetry event when the user invokes MeshToMetaHuman command
- L234 _private member_ `TWeakPtr<class SNotificationItem> AutoRigProgressNotification;` — A reference to the notification dialog that shows the autorigging progress
- L237 _private member_ `bool bMetaHumanAuthoringObjectsPresent = false;`

#### Free symbols / members of external scopes

- L81 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAutoRigServiceFinishedDelegate, bool);`
- L82 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAutoRigServiceFinishedDynamicDelegate, bool, bInSuccess);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentity/Public/MetaHumanIdentityLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanIdentity, Log, All);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentity/Public/MetaHumanIdentityParts.h` (Public)


#### enum `EIdentityPartMeshes`  
`enum class EIdentityPartMeshes : uint8`  
_L22-29_
- L24 _public enumerator_ `Invalid`
- L25 _public enumerator_ `Head`
- L26 _public enumerator_ `LeftEye`
- L27 _public enumerator_ `RightEye`
- L28 _public enumerator_ `Teeth`

#### enum `ETargetTemplateCompatibility`  
`enum class ETargetTemplateCompatibility : uint8`  
_L32-45_
- reflection: `UENUM()`
- L34 _public enumerator_ `Valid = 0`
- L35 _public enumerator_ `InvalidInputMesh` — Input mesh is null or of wrong type
- L36 _public enumerator_ `MissingImportModel` — Input mesh does not contain import data
- L37 _public enumerator_ `MissingLOD`
- L38 _public enumerator_ `MissingMeshInfo`
- L39 _public enumerator_ `MismatchNumVertices`
- L40 _public enumerator_ `MismatchStartImportedVertex`
- L41 _public enumerator_ `InvalidArchetype` — Status for all errors with the archetype, should never occur
- L42 _public enumerator_ `PotentialDegenerateTriangles` — Mesh has zero-area triangles which may fail to autorig (hint only)
- L44 _public enumerator_ `Count UMETA(Hidden)`

#### class `UMetaHumanIdentityPart`  
`class UMetaHumanIdentityPart : public UObject`  
_L56-81_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `UObject`
- desc: The base class for any Part that can be added to a MetaHumanIdentity
- L64 _public prototype_ `virtual void Initialize() PURE_VIRTUAL(UMetaHumanIdentityPart::Initialize,);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parts")` — Perform any initialization required after the Part is created
- L67 _public prototype_ `virtual FText GetPartName() const PURE_VIRTUAL(UMetaHumanIdentityPart::GetPartName, return {};);` — Returns the part name
- L70 _public prototype_ `virtual FText GetPartDescription() const PURE_VIRTUAL(UMetaHumanIdentityPart::GetPartDescription, return {};);` — Returns a short description of the part
- L73 _public prototype_ `virtual FSlateIcon GetPartIcon(const FName& InPropertyName = NAME_None) const PURE_VIRTUAL(UMetaHumanIdentityPart::GetPartIcon, return {};);` — Returns the icon for the part. This can optionally return an icon for the given InPropertyName
- L76 _public prototype_ `virtual FText GetPartTooltip(const FName& InPropertyName = NAME_None) const PURE_VIRTUAL(UMetaHumanIdentityPart::GetPartTooltip, return {};);` — Returns the tooltip for the part. This can optionally return a tooltip for the given InPropertyName
- L80 _public prototype_ `virtual bool DiagnosticsIndicatesProcessingIssue(FText& OutDiagnosticsWarningMessage) const PURE_VIRTUAL(UMetaHumanIdentityPart::DiagnosticsIndicatesProcessingIssue, return {};);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Diagnostics")` — Returns true if diagnostics indicates an issue processing this part, and also passes back a warning message if a diagnostic issue has been found

#### enum `EConformType`  
`enum class EConformType`  
_L92-103_
- reflection: `UENUM()`
- L95 _public enumerator_ `Solve` — Use the Face Fitting conformer, i.e. FitIdentity
- L102 _public enumerator_ `Copy` — Copy the data from the Neutral Pose face mesh to the Template Mesh. Assumes the target mesh is already conformed and in the correct topology expected by the Mesh To MetaHuman service

#### class `UMetaHumanIdentityFace`  
`class UMetaHumanIdentityFace : public UMetaHumanIdentityPart`  
_L106-544_
- reflection: `UCLASS(MinimalAPI, HideCategories = ("Preview"))`
- inherits: `UMetaHumanIdentityPart`
- L112 _public prototype_ `UMetaHumanIdentityFace();`
- L115 _public prototype_ `virtual void Initialize() override;`
- L116 _public prototype_ `virtual FText GetPartName() const override;`
- L117 _public prototype_ `virtual FText GetPartDescription() const override;`
- L118 _public prototype_ `virtual FSlateIcon GetPartIcon(const FName& InPropertyName = NAME_None) const override;`
- L119 _public prototype_ `virtual FText GetPartTooltip(const FName& InPropertyName = NAME_None) const override;`
- L120 _public prototype_ `virtual bool DiagnosticsIndicatesProcessingIssue(FText& OutDiagnosticsWarningMessage) const override;`
- L123 _public prototype_ `virtual void PostLoad() override;`
- L124 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L127 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L131 _public prototype_ `bool CanConform() const;` — Return true if the face has all the required information to run the MetaHuman Identity solve (conforming)
- L134 _public prototype_ `bool CanSubmitToAutorigging() const;` — Return true if the face can be submitted to the AutoRigging service, which means is already conformed and the Neutral Pose has a valid Capture Data
- L138 _public prototype_ `EIdentityErrorCode Conform(EConformType InConformType = EConformType::Solve);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Solve")` — MetaHuman Identity solve
- L142 _public prototype_ `bool IsConformalRigValid() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Rig")` — Returns true if the conformal rig component is valid and points to a valid skeletal mesh
- L145 _public prototype_ `void ExportTemplateMesh(const FString& InPath, const FString& InAssetName);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Export")`
- L150 _public prototype_ `void ResetRigComponent(bool bInCreateNewRigComponent = true);` — Resets face part to its initial state and optionally creates new rig component.
- L153 _public prototype_ `void ResetTemplateMesh();` — Reset the template mesh
- L156 _public prototype_ `void CopyMeshVerticesFromExistingMesh(class UCaptureData* CaptureData);` — TODO: Come up with good explanation
- L159 _public prototype_ `static FString TargetTemplateCompatibilityAsString(ETargetTemplateCompatibility InCompatibility);` — Converts ETargetTemplateCompatibility to a string
- L162 _public prototype_ `static ETargetTemplateCompatibility CheckTargetTemplateMesh(const UObject* InAsset);` — Helper function to evaluate the compatibility of a given mesh to be used as template
- L165 _public prototype_ `static TSharedPtr<class IDNAReader> GetPluginArchetypeDNAReader();` — Returns the DNA Reader for the plugin archetype DNA
- L171 _public prototype_ `EIdentityErrorCode ApplyDNAToRig(TSharedPtr<class IDNAReader> InDNAReader, bool bInUpdateBlendShapes = true, bool bInUpdateSkinWeights = true);` — Apply a DNA to the Rig Depending on the level of detail and usage (e.g.only LOD0 has blend shapes), these options can be turned off to save time/memory
- L177 _public prototype_ `bool GetPredictiveSolversTaskConfig(FPredictiveSolversTaskConfig& OutConfig) const;` — Populates predictive solver task config. Returns true if it was populated successfully, false otherwise.
- L184 _public prototype_ `bool RunPredictiveSolverTraining();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Face")` — Runs predictive solvers training externally (through python script or UE editor). Returns true if the process was successful, false otherwise.
- L190 _public prototype_ `bool RunAsyncPredictiveSolverTraining(FOnPredictiveSolversProgress InOnProgressCallback, FOnPredictiveSolversCompleted InOnCompletedCallback);` — Runs predictive solvers training asynchronously. Returns true if task was successfully scheduled, false otherwise.
- L195 _public prototype_ `bool IsAsyncPredictiveSolverTrainingActive() const;` — Returns true if predictive solver training is in progress, false otherwise.
- L200 _public prototype_ `bool IsAsyncPredictiveSolverTrainingCancelling() const;` — Returns true if predictive solver training is in cancelling phase, false otherwise.
- L205 _public prototype_ `void CancelAsyncPredictiveSolverTraining();` — Cancels active solver training, if any.
- L211 _public prototype_ `bool PollAsyncPredictiveSolverTrainingProgress(float& OutProgress);` — Poll active solver training progress. Output progress range is [0..1]. Returns true if successful (task is active), false otherwise.
- L216 _public prototype_ `EIdentityErrorCode ApplyCombinedDNAToRig(TSharedPtr<class IDNAReader> InDNAReader);` — Apply a combined DNA. If debugging is turned on, the DNA is saved;
- L219 _public prototype_ `bool CheckDNACompatible(class IDNAReader* InDNAReader) const;` — Returns true if provided DNA is compatible with the Face archetype, false otherwise
- L222 _public prototype_ `bool CheckDNACompatible(class IDNAReader* InDNAReader, FString& OutCompatibilityMsg) const;` — Returns true if provided DNA is compatible with the Face archetype, false otherwise. It also outputs message listing differences between DNAs
- L225 _public prototype_ `bool CheckRigCompatible() const;` — Returns true if the face rig component is compatible with the Face archetype, false otherwise
- L228 _public prototype_ `bool CheckRigCompatible(FString& OutCompatibilityMsg) const;` — Returns true if the face rig component is compatible with the Face archetype, false otherwise. It also outputs message listing differences between DNAs
- L234 _public prototype_ `UMetaHumanIdentityPose* FindPoseByType(EIdentityPoseType InPoseType) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Poses")` — Finds a Pose of given type. Returns nullptr if one is not found.
- L238 _public prototype_ `void AddPoseOfType(EIdentityPoseType InPoseType, UMetaHumanIdentityPose* InPose);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Poses")` — Adds the given pose to this face. Does nothing if a pose of the same type already exists
- L241 _public prototype_ `bool RemovePose(UMetaHumanIdentityPose* InPose);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Poses")`
- L244 _public prototype_ `const TArray<UMetaHumanIdentityPose*>& GetPoses() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Poses")`
- L247 _public prototype_ `bool HasDNABuffer() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Data")`
- L250 _public prototype_ `bool HasPredictiveSolvers() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Data")`
- L253 _public prototype_ `void ShowHeadMeshForPose(EIdentityPoseType InPoseType);` — Set the head mesh for the given pose type to be the active head mesh in the template mesh component
- L256 _public prototype_ `FTransform GetFrontalViewFrameTransform() const;` — Returns the head alignment transform for frontal promoted frame of the Neutral Pose or the MetaHuman Identity transform if there is no frontal frame
- L259 _public prototype_ `void SetTemplateMeshTransform(const FTransform& InTransform, bool bInUpdateRigTransform = false);` — Sets the transform for the conformal mesh and notifies subscribers
- L262 _public prototype_ `void ResetTemplateMeshTransform();` — Reset the transform the template mesh to its default value
- L266 _public prototype_ `void GetConformalVerticesForAutoRigging(TArray<FVector>& OutConformedFaceVertices, TArray<FVector>& OutConformedLeftEyeVertices, TArray<FVector>& OutConformedRightEyeVertices) const;` — Return the vertices of the conformed mesh transformed to the space required by the autorigging backend, for face mesh, left eye mesh and right eye mesh if eyes have been fitted. Note that teeth are not available at this stage as we have the neutral pose only and the teeth have not been fitted yet.
- L271 _public prototype_ `TMap<EIdentityPartMeshes, TArray<FVector>> GetConformalVerticesWorldPos(EIdentityPoseType InPoseType) const;` — Return world position of conformal face mesh vertices
- L274 _public prototype_ `TMap<EIdentityPartMeshes, TArray<FVector>> GetConformalVerticesForTransform(const FTransform& InMeshTransform, EIdentityPoseType InPoseType) const;` — Return conformal face mesh vertices for a given transform
- L277 _public prototype_ `bool CanFitTeeth() const;` — Returns whether or not teeth can be conformed
- L279 _public prototype_ `bool HasValidPromotedFramesForPose(EIdentityPoseType InPoseType) const;`
- L282 _public prototype_ `EIdentityErrorCode FitTeeth();` — Fit the teeth to RawCombinedDNABuffer to generate final DNABuffer
- L285 _public prototype_ `EIdentityErrorCode Finalize();` — Finalize changes after DNA has been altered (updates skelmesh and create PCA model using DNABuffer)
- L288 _public prototype_ `bool ExportDNADataToFiles(const FString& InDnaPathWithName, const FString& InBrowsPathWithName);` — Exports DNA Buffer and Brows data to specified files
- L292 _public prototype_ `void SetRawDNABuffer(TConstArrayView<uint8> InRawDNABuffer);`
- L293 _public prototype_ `TArray<uint8> GetRawDNABuffer() const;`
- L294 _public prototype_ `bool HasRawDNABuffer() const;`
- L295 _public prototype_ `void ClearRawDNABuffer();`
- L297 _public prototype_ `void SetRawDeltaDNABuffer(TConstArrayView<uint8> InRawDeltaDNABuffer);`
- L298 _public prototype_ `TArray<uint8> GetRawDeltaDNABuffer() const;`
- L299 _public prototype_ `bool HasRawDeltaDNABuffer() const;`
- L300 _public prototype_ `void ClearRawDeltaDNABuffer();`
- L302 _public prototype_ `void SetCombinedDNABuffer(TConstArrayView<uint8> InRawCombinedDNABuffer);`
- L303 _public prototype_ `TArray<uint8> GetCombinedDNABuffer() const;`
- L304 _public prototype_ `bool HasCombinedDNABuffer() const;`
- L305 _public prototype_ `void ClearCombinedDNABuffer();`
- L307 _public prototype_ `void SetDNABuffer(TConstArrayView<uint8> InDNABuffer);`
- L308 _public prototype_ `TArray<uint8> GetDNABuffer() const;`
- L309 _public prototype_ `void ClearDNABuffer();`
- L311 _public prototype_ `void SetPCARig(TConstArrayView<uint8> InPCARig);`
- L312 _public prototype_ `TArray<uint8> GetPCARig() const;`
- L313 _public prototype_ `bool HasPCARig() const;`
- L314 _public prototype_ `void ClearPCARig();`
- L316 _public prototype_ `void SetBrowsBuffer(TConstArrayView<uint8> InBrowsBuffer);`
- L317 _public prototype_ `TArray<uint8> GetBrowsBuffer() const;`
- L318 _public prototype_ `bool HasBrowsBuffer() const;`
- L319 _public prototype_ `void ClearBrowsBuffer();`
- L321 _public prototype_ `void SetPredictiveSolvers(TConstArrayView<uint8> InPredictiveSolvers);`
- L322 _public prototype_ `TArray<uint8> GetPredictiveSolvers() const;`
- L323 _public prototype_ `void ClearPredictiveSolvers();`
- L325 _public prototype_ `void SetPredictiveWithoutTeethSolver(TConstArrayView<uint8> InPredictiveWithoutTeethSolver);`
- L326 _public prototype_ `TArray<uint8> GetPredictiveWithoutTeethSolver() const;`
- L327 _public prototype_ `bool HasPredictiveWithoutTeethSolver() const;`
- L328 _public prototype_ `void ClearPredictiveWithoutTeethSolver();`
- L331 _public prototype_ `TArray<FCameraCalibration> GetCalibrationsForPoseAndFrame(UMetaHumanIdentityPose* InPose, class UMetaHumanIdentityPromotedFrame* InPromotedFrame) const;` — Get the camera calibrations associated with the provided pose and frame index, and also return the full camera name for that pose and frame
- L334 _public prototype_ `FString GetFullCameraName(UMetaHumanIdentityPose* InPose, class UMetaHumanIdentityPromotedFrame* InPromotedFrame, const FString& InBaseCameraName) const;` — Get the full camera name associated with the provided pose and frame index, given a base camera name which may be empty for M2MH, or a RGB or depth camera name for F2MH
- L340 _public member_ `TObjectPtr<class UMetaHumanFaceFittingSolver> DefaultSolver;` — `UPROPERTY(EditAnywhere, Category = "Solver")` — The default solver
- L344 _public member_ `TObjectPtr<class UMetaHumanTemplateMeshComponent> TemplateMeshComponent;` — `UPROPERTY(VisibleAnywhere, Category = "Preview", DisplayName = "Template Mesh")` — The template mesh component for the face. Manages the meshes that represent each pose as well as eyes and teeth
- L348 _public member_ `TObjectPtr<class USkeletalMeshComponent> RigComponent;` — `UPROPERTY(VisibleAnywhere, Category = "Preview", DisplayName = "Skeletal Mesh")` — The result of the auto-rigging process. This is the conformal mesh with a proper rig able to control the face
- L352 _public member_ `uint8 bIsConformed : 1;` — `UPROPERTY(VisibleAnywhere, Category = "Output", AdvancedDisplay)` — True if this face was conformed at least once
- L356 _public member_ `uint8 bIsAutoRigged : 1;` — `UPROPERTY(VisibleAnywhere, Category = "Output", AdvancedDisplay, NonTransactional)` — True if this face has autorigged DNA applied either through AutoRig Service or if it was imported manually through Import functionality
- L360 _public member_ `uint8 bHasFittedEyes : 1;` — `UPROPERTY(VisibleAnywhere, Category = "Output", AdvancedDisplay)` — True if data-driven eyes was used during mesh conformation
- L367 _public member_ `FTransform DNAToScanTransform_DEPRECATED;` — `UPROPERTY(NonTransactional, meta = (DeprecatedProperty, DeprecationMessage = "The new autorigging service doesn't provide DNAToScan transform matrix"))` — Holds the DNAToScan transform as returned from the autorigging service
- L370 _public member_ `bool bShouldUpdateRigComponent = false;` — `UPROPERTY(VisibleAnywhere, Category = "DNA", AdvancedDisplay, NonTransactional)`
- L374 _public member_ `FVector DNAPivot_DEPRECATED;` — `UPROPERTY(NonTransactional, meta = (DeprecatedProperty, DeprecationMessage = "The new autorigging service doesn't provide DNA Pivot"))` — Holds the DNA Pivot as returned from the autorigging service
- L378 _public member_ `float DNAScale_DEPRECATED = 1.0f;` — `UPROPERTY(NonTransactional, meta = (DeprecatedProperty, DeprecationMessage = "The new autorigging service doesn't provide DNATo Scale"))` — Holds the DNA Scale as returned from the autorigging service
- L382 _public member_ `bool bSkipDiagnostics = false;` — `UPROPERTY(EditAnywhere, Category = "Processing Diagnostics")` — Flag indicating whether processing diagnostics should be calculated during identity creation
- L386 _public member_ `float MaximumScaleDifferenceFromAverage = 25.0f;` — `UPROPERTY(EditAnywhere, Category = "Processing Diagnostics", meta = (UIMin = 0.0, ClampMin = 0.0, ClampMax = 200.0))` — The maximum percentage difference an autorigged face result is allowed to differ from an average MetaHuman. Above this value a diagnostic warning will be flagged.
- L390 _public member_ `float MinimumDepthMapFaceCoverage = 80.0f;` — `UPROPERTY(EditAnywhere, Category = "Processing Diagnostics", meta = (UIMin = 0.0, UIMax = 100.0, ClampMin = 0.0, ClampMax = 100.0))` — The minimum percentage of the face region which should have valid depth-map pixels. Below this value a diagnostic warning will be flagged.
- L394 _public member_ `float MinimumDepthMapFaceWidth = 120.0f;` — `UPROPERTY(EditAnywhere, Category = "Processing Diagnostics", meta = (ClampMin = 0.0, ClampMax = 10000.0))` — The minimum required width of the face region on the depth-map in pixels. Below this value a diagnostic warning will be flagged.
- L398 _public member_ `float MaximumInvalidBrowAnnotations = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Processing Diagnostics", meta = (ClampMin = 0.0, ClampMax = 100.0))` — The maximum percentage of the brow annotations which may be outside the brows region of the head mesh. Above this value a diagnostic warning will be flagged.
- L403 _private member_ `UE::Serialization::FEditorBulkData RawDNABufferBulkData;` — Holds the raw dna file as returned from the autorigging service
- L406 _private member_ `UE::Serialization::FEditorBulkData RawDeltaDNABufferBulkData;` — Holds the raw delta dna file as returned from the autorigging service
- L409 _private member_ `UE::Serialization::FEditorBulkData RawCombinedDNABufferBulkData;` — Holds the combined raw dna and delta dna file as returned from the autorigging service
- L412 _private member_ `UE::Serialization::FEditorBulkData DNABufferBulkData;` — Holds the final dna (RawCombinedDNABuffer with teeth fitting modifications). This is also stored as a DNAAsset in the SkelMesh.
- L415 _private member_ `UE::Serialization::FEditorBulkData PCARigBulkData;` — Holds the PCA model of DNABuffer
- L418 _private member_ `UE::Serialization::FEditorBulkData BrowsBufferBulkData;` — Holds the brows.json data produced by conforming and needed in animation generation
- L421 _private member_ `UE::Serialization::FEditorBulkData PredictiveSolversBulkData;` — Holds the trained predictive solvers, which are used for the preview solve
- L424 _private member_ `UE::Serialization::FEditorBulkData PredictiveWithoutTeethSolverBulkData;` — Holds the trained predictive solver without teeth,which is used for the global teeth solve
- L429 _private member_ `TArray<uint8> RawDNABuffer_DEPRECATED;` — `UPROPERTY(NonTransactional)`
- L432 _private member_ `TArray<uint8> RawDeltaDNABuffer_DEPRECATED;` — `UPROPERTY(NonTransactional)`
- L435 _private member_ `TArray<uint8> RawCombinedDNABuffer_DEPRECATED;` — `UPROPERTY(NonTransactional)`
- L438 _private member_ `TArray<uint8> DNABuffer_DEPRECATED;` — `UPROPERTY(NonTransactional)`
- L441 _private member_ `TArray<uint8> PCARig_DEPRECATED;` — `UPROPERTY(NonTransactional)`
- L444 _private member_ `TArray<uint8> BrowsBuffer_DEPRECATED;` — `UPROPERTY(NonTransactional)`
- L447 _private member_ `TArray<uint8> PredictiveSolvers_DEPRECATED;` — `UPROPERTY(NonTransactional)`
- L450 _private member_ `TArray<uint8> PredictiveWithoutTeethSolver_DEPRECATED;` — `UPROPERTY(NonTransactional)`
- L457 _private prototype_ `void ApplyDNAToRigComponent(TSharedPtr<class IDNAReader> InDNAReader, bool bInUpdateBlendShapes = false, bool bInUpdateSkinWeights = true);` — A private function uses to apply the supplied DNA to the rig component. Depending on the level of detail and usage (e.g.only LOD0 has blend shapes), these options can be turned off to save time/memory
- L460 _private prototype_ `void LoadDefaultFaceFittingSolvers();` — Loads default solvers for face fitting
- L463 _private prototype_ `void SetSkeletalMeshMaterials(const TNotNull<class USkeletalMesh*> InSkelMesh) const;` — Loads topology materials for skeletal mesh
- L466 _private prototype_ `class USkeletalMesh* CreateFaceArchetypeSkelmesh(const FString& InNewRigAssetName, const FString& InNewRigPath);` — Calls the interchange system to create skelmesh/skeleton assets from the archetype dna file in the plugin content
- L470 _private member_ `TArray<TObjectPtr<UMetaHumanIdentityPose>> Poses;` — `UPROPERTY(VisibleAnywhere, Category = "Poses")` — An array of poses that will be used to fit the conformal mesh to the input data. See UMetaHumanIdentityPose
- L473 _private member_ `TObjectPtr<class UMetaHumanTemplateMesh> ConformalMeshComponent_DEPRECATED;` — `UPROPERTY()`
- L477 _private member_ `TArray<FVector> ConformalVertsLeftEyeRigSpace_DEPRECATED;` — `UPROPERTY()` — Stored conformed left eye mesh vertices in rig coordinate space
- L481 _private member_ `TArray<FVector> ConformalVertsRightEyeRigSpace_DEPRECATED;` — `UPROPERTY()` — Stored conformed right eye mesh vertices in rig coordinate space
- L489 _private prototype_ `EIdentityErrorCode InitializeRig();` — Initializes the Rig by copying the Face Archetype provided by the plugin
- L492 _private member_ `class FPredictiveSolversTask* CurrentPredictiveSolversTask = nullptr;` — Currently active predictive solver task
- L497 _private prototype_ `FTransform GetTemplateMeshInitialTransform() const;` — Returns initial template mesh transform
- L500 _private prototype_ `FString GetDeviceDNAToPCAConfig(class UCaptureData* InCaptureData) const;` — Get the filename for the device specific DNA to PCA config
- L503 _private prototype_ `void UpdateRigTransform();` — Moves rig component to the template mesh position.
- L505 _private prototype_ `bool SetConformerCameraParameters(UMetaHumanIdentityPose* InPose, UE::Wrappers::FMetaHumanConformer& OutConformer) const;`
- L506 _private prototype_ `bool SetConformerScanInputData(const UMetaHumanIdentityPose* InPose, UE::Wrappers::FMetaHumanConformer& OutConformer, bool &bOutInvalidMeshTopology) const;`
- L507 _private prototype_ `bool SetConformerDepthInputData(const UMetaHumanIdentityPose* InPose, UE::Wrappers::FMetaHumanConformer& OutConformer) const;`
- L508 _private prototype_ `EIdentityErrorCode RunMeshConformer(UMetaHumanIdentityPose* InPose, UE::Wrappers::FMetaHumanConformer& OutConformer);`
- L510 _private prototype_ `void WriteConformalVerticesToFile(const FString& InNameSuffix = TEXT("")) const;`
- L511 _private prototype_ `void WriteTargetMeshToFile(class UStaticMesh* InTargetMesh, const FString& InNameSuffix = TEXT("")) const;`
- L513 _private prototype_ `FString GetPluginContentDir() const;`
- L516 _private prototype_ `FString GetFrameNameForConforming(class UMetaHumanIdentityPromotedFrame* InPromotedFrame, int32 InFrameIndex) const;` — Returns a name for a promoted frame suitable to be used with the conforming API
- L519 _private function_ `static FString CombineFrameNameAndCameraViewName(const FString& InFrameName, const FString& InCameraViewName)` — combine frame name and view name to give a unique identifier
- L524 _private prototype_ `bool SaveDebuggingData(UMetaHumanIdentityPose* InPose, UE::Wrappers::FMetaHumanConformer& OutConformer, const FString& InAssetSavedFolder) const;`
- L527 _private member_ `static const TArray<FString> CurveNamesForEyeFitting;` — The list of curves required to be active when eye fitting is enabled
- L530 _private prototype_ `void UpdateSourceData(class USkeletalMesh* SkelMesh, class IDNAReader* DNAReader, class FDNAToSkelMeshMap* DNAToSkelMeshMap);` — Updates ImportData structs for SkeletalMesh to preserve the mesh
- L533 _private prototype_ `void SetHeadAlignmentForPose(class UMetaHumanIdentityPose* InPose, TConstArrayView<FMatrix44f> InStackedTransforms, TConstArrayView<float> InStackedScales);` — Sets the head alignments for the given pose
- L536 _private prototype_ `void UpdateCaptureDataConfigName();` — Updates the capture data config name in each pose
- L539 _private prototype_ `TArray<FCameraCalibration> GetCalibrations(UMetaHumanIdentityPose* InPose) const;` — Get the camera calibrations associated with the provided pose
- L542 _private prototype_ `TArray<FCameraCalibration> GetCalibrations(UMetaHumanIdentityPose* InPose, class UMetaHumanIdentityPromotedFrame* InPromotedFrame, int32 InFrameIndex) const;` — Get the calibration(s) for the supplied promoted frame and frame index

#### class `UMetaHumanIdentityBody`  
`class UMetaHumanIdentityBody : public UMetaHumanIdentityPart`  
_L550-579_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetaHumanIdentityPart`
- L556 _public prototype_ `UMetaHumanIdentityBody();`
- L559 _public function_ `virtual void Initialize() override`
- L560 _public prototype_ `virtual FText GetPartName() const override;`
- L561 _public prototype_ `virtual FText GetPartDescription() const override;`
- L562 _public prototype_ `virtual FSlateIcon GetPartIcon(const FName& InPropertyName = NAME_None) const override;`
- L563 _public prototype_ `virtual FText GetPartTooltip(const FName& InPropertyName = NAME_None) const override;`
- L564 _public prototype_ `virtual bool DiagnosticsIndicatesProcessingIssue(FText& OutDiagnosticsWarningMessage) const override;`
- L567 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L573 _public member_ `int32 Height;` — `UPROPERTY(BlueprintReadWrite, Category = "Body")`
- L576 _public member_ `int32 BodyTypeIndex;` — `UPROPERTY(BlueprintReadWrite, Category = "Body")`
- L578 _public member_ `FSimpleMulticastDelegate OnMetaHumanIdentityBodyChangedDelegate;`

#### class `UMetaHumanIdentityHands`  
`class UMetaHumanIdentityHands : public UMetaHumanIdentityPart`  
_L585-601_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetaHumanIdentityPart`
- L591 _public prototype_ `UMetaHumanIdentityHands();`
- L594 _public function_ `virtual void Initialize() override`
- L595 _public prototype_ `virtual FText GetPartName() const override;`
- L596 _public prototype_ `virtual FText GetPartDescription() const override;`
- L597 _public prototype_ `virtual FSlateIcon GetPartIcon(const FName& InPropertyName = NAME_None) const override;`
- L598 _public prototype_ `virtual FText GetPartTooltip(const FName& InPropertyName = NAME_None) const override;`
- L599 _public prototype_ `virtual bool DiagnosticsIndicatesProcessingIssue(FText& OutDiagnosticsWarningMessage) const override;`

#### class `UMetaHumanIdentityOutfit`  
`class UMetaHumanIdentityOutfit : public UMetaHumanIdentityPart`  
_L607-622_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetaHumanIdentityPart`
- L613 _public prototype_ `UMetaHumanIdentityOutfit();`
- L616 _public function_ `virtual void Initialize() override`
- L617 _public prototype_ `virtual FText GetPartName() const override;`
- L618 _public prototype_ `virtual FText GetPartDescription() const override;`
- L619 _public prototype_ `virtual FSlateIcon GetPartIcon(const FName& InPropertyName = NAME_None) const override;`
- L620 _public prototype_ `virtual FText GetPartTooltip(const FName& InPropertyName = NAME_None) const override;`
- L621 _public prototype_ `virtual bool DiagnosticsIndicatesProcessingIssue(FText& OutDiagnosticsWarningMessage) const override;`

#### class `UMetaHumanIdentityProp`  
`class UMetaHumanIdentityProp : public UMetaHumanIdentityPart`  
_L628-643_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetaHumanIdentityPart`
- L634 _public prototype_ `UMetaHumanIdentityProp();`
- L637 _public function_ `virtual void Initialize() override`
- L638 _public prototype_ `virtual FText GetPartName() const override;`
- L639 _public prototype_ `virtual FText GetPartDescription() const override;`
- L640 _public prototype_ `virtual FSlateIcon GetPartIcon(const FName& InPropertyName = NAME_None) const override;`
- L641 _public prototype_ `virtual FText GetPartTooltip(const FName& InPropertyName = NAME_None) const override;`
- L642 _public prototype_ `virtual bool DiagnosticsIndicatesProcessingIssue(FText& OutDiagnosticsWarningMessage) const override;`

#### class `UMetaHumanTemplateMesh`  
`class UMetaHumanTemplateMesh : public UDynamicMeshComponent`  
_L649-658_
- reflection: `UCLASS(MinimalAPI, HideCategories = (DynamicMeshComponent, Physics, Collision, HLOD, Navigation, VirtualTexture, Tags, ComponentReplication, Activation, Variable, Cooking, MaterialParameters, TextureStreaming, Mobile, AssetUserData))`
- inherits: `UDynamicMeshComponent`
- L657 _public member_ `int32 MaskPreset = 0;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API METAHUMANIDENTITY_API`
- L47 _prototype_ `ENUM_RANGE_BY_COUNT(ETargetTemplateCompatibility, ETargetTemplateCompatibility::Count);`
- L86 _namespace_ `namespace UE`
- L86 _namespace_ `namespace Wrappers` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentity/Public/MetaHumanIdentityPose.h` (Public)


#### enum `EIdentityPoseType`  
`enum class EIdentityPoseType : uint8`  
_L20-27_
- reflection: `UENUM()`
- L22 _public enumerator_ `Invalid = 0`
- L23 _public enumerator_ `Neutral`
- L24 _public enumerator_ `Teeth`
- L25 _public enumerator_ `Custom`
- L26 _public enumerator_ `Count UMETA(Hidden)`

#### class `UMetaHumanIdentityPose`  
`class UMetaHumanIdentityPose : public UObject`  
_L38-230_
- reflection: `UCLASS(MinimalAPI, BlueprintType, HideCategories = ("Preview"))`
- inherits: `UObject`
- desc: A Pose describes the appearance of the MetaHuman Identity in some way. It could be a mesh or footage showing the Identity's teeth or its neutral expression.
- L45 _public prototype_ `static FString PoseTypeAsString(EIdentityPoseType InPoseType);` — Utility function to convert the EIdentityPoseType to a FString
- L47 _public prototype_ `UMetaHumanIdentityPose();`
- L50 _public prototype_ `FSlateIcon GetPoseIcon() const;` — Returns an icon that represents this pose
- L53 _public prototype_ `FText GetPoseTooltip() const;` — Returns an tooltip for this pose
- L56 _public prototype_ `void SetCaptureData(class UCaptureData* InCaptureData);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Target")`
- L59 _public prototype_ `class UCaptureData* GetCaptureData() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Target")`
- L63 _public prototype_ `bool IsCaptureDataValid() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Target")` — Returns true if the capture is initialized
- L74 _public prototype_ `UMetaHumanIdentityPromotedFrame* AddNewPromotedFrame(int32& OutPromotedFrameIndex);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Frame Promotion")` — @brief Creates a new promoted frame suitable for this pose. The type of the promoted frame will be based on PromotedFrameClass. It also sets the default tracker for the frame to be the same as DefaultTracker. @param OutPromotedFrameIndex The index of the newly created promoted frame in the internal array @return A new UMetaHumanIdentityPromotedFrame based on PromotedFrameClass
- L78 _public prototype_ `void RemovePromotedFrame(UMetaHumanIdentityPromotedFrame* InPromotedFrame);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Frame Promotion")` — Removes the given promoted frame from this pose
- L80 _public function_ `FOnCaptureDataChanged& OnCaptureDataChanged()`
- L86 _public prototype_ `bool IsDefaultTrackerValid() const;` — Returns true iff the default tracker is a valid object that is ready to track
- L89 _public prototype_ `TArray<class UMetaHumanIdentityPromotedFrame*> GetAllPromotedFramesWithValidContourData() const;` — Returns all Promoted Frames that contain contour data
- L92 _public prototype_ `TArray<class UMetaHumanIdentityPromotedFrame*> GetValidContourDataFramesFrontFirst() const;` — If front view is set, returns promoted frames with valid contours with front view as first entry
- L95 _public prototype_ `UMetaHumanIdentityPromotedFrame* GetFrontalViewPromotedFrame() const;` — Returns the promoted frame tagged as front view
- L98 _public prototype_ `const FTransform& GetHeadAlignment(int32 InFrameIndex = 0);` — Returns the head alignment transform for a given promoted frame
- L104 _public prototype_ `void SetHeadAlignment(const FTransform& InTransform, int32 InFrameIndex = INDEX_NONE);` — Sets the head alignment transform for a promoted frame. If InFrameIndex is not specified, sets the same transform to all promoted frames
- L108 _public prototype_ `void LoadDefaultTracker();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Trackers")` — Sets the default tracker based on the PoseType. Only changes it DefaultTracker is not currently set
- L111 _public prototype_ `void UpdateCaptureDataSceneComponent();` — Adds or destroys the capture data scene component depending if it has valid capture data
- L114 _public prototype_ `void UpdateCaptureDataConfigName();` — Update the capture data config name
- L117 _public member_ `TArray<TSharedPtr<FString>> CameraNames;` — List of all RGB cameras (views) in the footage capture data
- L121 _public prototype_ `virtual void PostLoad() override;` — UObject Interface
- L122 _public prototype_ `virtual void PostInitProperties() override;`
- L125 _public prototype_ `virtual void PreEditChange(FEditPropertyChain& InPropertyAboutToChange) override;`
- L126 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L127 _public prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L133 _public member_ `FText PoseName;` — `UPROPERTY(EditAnywhere, Category = "Pose", meta = (EditCondition = "PoseType == EIdentityPoseType::Custom"))` — The display name of the pose. This can be edited for custom poses
- L137 _public member_ `EIdentityPoseType PoseType;` — `UPROPERTY(BlueprintReadWrite, Category = "Pose")` — The type this pose represents
- L141 _public member_ `bool bFitEyes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pose", DisplayName = "Use Data Driven Eyes", meta = (EditCondition = "PoseType == EIdentityPoseType::Neutral"))` — Whether or not to use the data driven approach to fit the eyes in the template mesh
- L145 _public member_ `FTransform PoseTransform;` — `UPROPERTY(EditAnywhere, Category = "Pose")` — The transform for the pose if changed in the viewport
- L149 _public member_ `TObjectPtr<class UMetaHumanFaceContourTrackerAsset> DefaultTracker;` — `UPROPERTY(EditAnywhere, Category = "Trackers")` — The default tracker that should be used for tracking a Promoted Frame of this pose. This can still be customized in a per-frame basis
- L153 _public member_ `TSubclassOf<class UMetaHumanIdentityPromotedFrame> PromotedFrameClass;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Frame Promotion")` — The class the defines the Promoted Frame type for this pose
- L157 _public member_ `TArray<TObjectPtr<class UMetaHumanIdentityPromotedFrame>> PromotedFrames;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = "Frame Promotion", meta = (EditFixedOrder))` — The array of Promoted Frames for this pose
- L161 _public member_ `TObjectPtr<class USceneComponent> CaptureDataSceneComponent;` — `UPROPERTY(VisibleAnywhere, Category = "Preview")` — The scene component that represents the capture data for this pose
- L168 _public member_ `float ManualTeethDepthOffset;` — `UPROPERTY(EditAnywhere, Category = "Pose", DisplayName = "Manual Teeth Depth Offset", meta = (EditCondition = "PoseType == EIdentityPoseType::Teeth", ToolTip = "Unit: cm", ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))` — Additional offset depth translation for the teeth
- L171 _private prototype_ `void NotifyCaptureDataChanged(bool bInResetRanges);`
- L172 _private prototype_ `void NotifyPoseTransformChanged();`
- L174 _private prototype_ `void HandleCaptureDataChanged(bool bInResetRanges);`
- L175 _private prototype_ `void HandleCaptureDataSceneComponentTransformChanged();`
- L177 _private prototype_ `void RegisterCaptureDataInternalsChangedDelegate();`
- L178 _private prototype_ `void RegisterCaptureDataSceneComponentTransformChanged();`
- L180 _private prototype_ `void UpdateRateMatchingDropFrames();`
- L182 _private member_ `TArray<FFrameRange> RateMatchingDropFrameRanges;`
- L187 _private member_ `FOnCaptureDataChanged OnCaptureDataChangedDelegate;` — Delegated called when the capture data associated with the Pose changes
- L191 _private member_ `TObjectPtr<class UCaptureData> CaptureData;` — `UPROPERTY(EditAnywhere, Category = "Target")` — Source data for this pose, this could be a mesh or footage
- L194 _private member_ `bool bIsCaptureDataValid = false;` — A cached check on if capture data is valid
- L198 _private member_ `FString CaptureDataConfig;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "Target")` — Display name of the config to use with the capture data
- L201 _private member_ `ETimecodeAlignment PreviousTimecodeAlignment = ETimecodeAlignment::None;` — The value of timecode alignment used previously (used to detect when timecode alignment changes between particular modes)
- L204 _private member_ `FString PreviousCamera;` — The value of camera used previously (used to detect when camera changes)
- L210 _public member_ `FString Camera;` — `UPROPERTY(EditAnywhere, Category = "Target")` — Name of camera (view) in the footage capture data to use for display and processing
- L214 _public member_ `ETimecodeAlignment TimecodeAlignment = ETimecodeAlignment::Relative;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")` — Controls alignment of media tracks via their timecode
- L226 _public prototype_ `ECurrentFrameValid GetIsFrameValid(int32 InFrameNumber) const;`
- L227 _public prototype_ `ECurrentFrameValid GetIsFrameValid(int32 InFrameNumber, const TRange<FFrameNumber>& InProcessingFrameRange, const TMap<TWeakObjectPtr<UObject>, TRange<FFrameNumber>>& InMediaFrameRanges) const;`
- L229 _public prototype_ `TArray<FFrameRange> GetRateMatchingExcludedFrameRanges() const;`

#### enum `UMetaHumanIdentityPose::ECurrentFrameValid`  
`enum class ECurrentFrameValid : uint8`  
_L217-224_
- desc: Determine if specified frame is valid, ie has RGB and depth data, not excluded etc
- L219 _public enumerator_ `Valid = 0`
- L220 _public enumerator_ `Invalid_NoCaptureData`
- L221 _public enumerator_ `Invalid_NoFootage`
- L222 _public enumerator_ `Invalid_NoRGBOrDepth`
- L223 _public enumerator_ `Invalid_Excluded`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API METAHUMANIDENTITY_API`
- L29 _prototype_ `ENUM_RANGE_BY_COUNT(EIdentityPoseType, EIdentityPoseType::Count);`
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCaptureDataChanged, bool bInResetRanges) UCLASS(MinimalAPI, BlueprintType, HideCategories = ("Preview")) class UMetaHumanIdentityPose : public UObject { GENERATED_BODY() public: static FString PoseTypeAsString(EIdentityPoseType InPoseType); UMetaHumanIdentityPose(); FSlateIcon GetPoseIcon() const; FText GetPoseTooltip() const; UFUNCTION(BlueprintCallable, Category = "MetaHuman|Target") void SetCaptureData(class UCaptureData* InCaptureData); UFUNCTION(BlueprintCallable, Category = "MetaHuman|Target") class UCaptureData* GetCaptureData() const; UFUNCTION(BlueprintCallable, Category = "MetaHuman|Target") bool IsCaptureDataValid() const; /** * @brief Creates a new promoted frame suitable for this pose. * The type of the promoted frame will be based on PromotedFrameClass. * It also sets the default tracker for the frame to be the same as DefaultTracker. * * @param OutPromotedFrameIndex The index of the newly created promoted frame in the internal array`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentity/Public/MetaHumanIdentityPromotedFrames.h` (Public)


#### class `UMetaHumanIdentityPromotedFrame`  
`class UMetaHumanIdentityPromotedFrame : public UObject`  
_L18-126_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `UObject`
- L26 _public member_ `static const FIntPoint DefaultTrackerImageSize;` — The default size to be used when capturing a promoted frame for tracking
- L28 _public prototype_ `UMetaHumanIdentityPromotedFrame();`
- L33 _public prototype_ `virtual void PostLoad() override;`
- L37 _public prototype_ `void InitializeMarkersFromParsedConfig(const FFrameTrackingContourData& InContourData, const FString& InConfigVersion);` — Initialize the contour data for this frame with curves, specified in the config
- L40 _public prototype_ `void UpdateContourDataFromFrameTrackingContours(const FFrameTrackingContourData& InContourData, bool bUpdateCurveStates = false) const;` — Updates the ContourData for curves initialized from the config. Bool controls if visibility and "curveModified" status should be updated
- L43 _public prototype_ `void UpdateContourDataForIndividualCurves(const FFrameTrackingContourData& InContourData) const;` — Updates the individual curves in contour data
- L46 _public prototype_ `bool AreActiveCurvesValidForConforming(const FBox2D& InTexCanvas) const;` — Returns true if all active curves are inside the viewport
- L48 _public prototype_ `const FFrameTrackingContourData* GetFrameTrackingContourData() const;`
- L51 _public prototype_ `TSharedPtr<class FMetaHumanCurveDataController> GetCurveDataController() const;` — Return the Curve Data Controller for this frame
- L55 _public prototype_ `bool FrameContoursContainActiveData() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Tracking")` — Returns true if ContourData in ShapeAnnotation contains any curves that are active
- L59 _public prototype_ `bool CanTrack() const;` — `UFUNCTION(BlueprintPure, Category = "MetaHuman|Tracking")` — Returns true if this Promoted Frame has all the required information to track
- L62 _public prototype_ `bool IsTrackingOnChange() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Tracking")`
- L65 _public prototype_ `bool IsTrackingManually() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Tracking")`
- L68 _public prototype_ `bool IsNavigationLocked() const;` — `UFUNCTION(BlueprintPure, Category = "MetaHuman|Navigation")`
- L71 _public prototype_ `void SetNavigationLocked(bool bIsLocked);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Navigation")`
- L74 _public prototype_ `void ToggleNavigationLocked();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Navigation")`
- L79 _public prototype_ `bool DiagnosticsIndicatesProcessingIssue(float InMinimumDepthMapFaceCoverage, float InMinimumDepthMapFaceWidth, FText& OutDiagnosticsWarningMessage) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Diagnostics")` — Returns true if the diagnostics associated with the promoted frame indicate a potential issue, and returns a warning message if so. Note that the thresholds supplied for checking whether an issue exists are properties of UMetaHumanIdentityFace and can be obtained from there
- L85 _public member_ `FTransform HeadAlignment;` — `UPROPERTY(VisibleAnywhere, Category = "Annotations")` — The alignment of the conformal mesh associated with this promoted frame
- L89 _public member_ `FText FrameName;` — `UPROPERTY(EditAnywhere, Category = "Frame")` — The name of frame as given by the user
- L93 _public member_ `uint8 bIsHeadAlignmentSet : 1;` — `UPROPERTY(VisibleAnywhere, Category = "Annotations")` — Do we have a valid alignment of the conformal mesh associated with this promoted frame
- L97 _public member_ `uint8 bUseToSolve : 1;` — `UPROPERTY(EditAnywhere, Category = "Frame")` — Whether or not the markers (landmarks) of this Promoted Frame are active
- L101 _public member_ `uint8 bIsNavigationLocked : 1;` — `UPROPERTY(EditAnywhere, Category = "Frame")` — Whether or not the navigation is locked for this Promoted frame
- L105 _public member_ `uint8 bTrackOnChange : 1;` — `UPROPERTY(Transient)` — Whether or not track on change is enabled
- L109 _public member_ `uint8 bIsFrontView : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Frame")` — Whether this promoted frame is front view
- L113 _public member_ `TObjectPtr<class UMetaHumanFaceContourTrackerAsset> ContourTracker;` — `UPROPERTY(EditAnywhere, Category = "Trackers")` — The tracker that can be used to track landmarks on the data represented by this Promoted Frame
- L117 _public member_ `TObjectPtr<class UMetaHumanContourData> ContourData;` — `UPROPERTY(EditAnywhere, Category = "Annotations")` — Contour data class that holds all the data for curves and control vertices
- L120 _public member_ `TSharedPtr<class FMetaHumanCurveDataController> CurveDataController;` — Data controller for MetaHumanContourData. Any data manipulation is done in the controller
- L124 _public member_ `FDepthMapDiagnosticsResult DepthMapDiagnostics;` — `UPROPERTY(VisibleAnywhere, Category = "Diagnostics")` — The depth-map diagnostics result for the frame

#### class `UMetaHumanIdentityCameraFrame`  
`class UMetaHumanIdentityCameraFrame : public UMetaHumanIdentityPromotedFrame`  
_L134-191_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetaHumanIdentityPromotedFrame`
- L141 _public prototype_ `UMetaHumanIdentityCameraFrame();`
- L145 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L151 _public prototype_ `FTransform GetCameraTransform() const;` — Returns the viewport transform as a FTransform object
- L153 _public function_ `FSimpleDelegate& OnCameraTransformChanged()`
- L159 _public prototype_ `FMinimalViewInfo GetMinimalViewInfo() const;` — Returns the minimal view info for this camera frame
- L165 _public member_ `FVector ViewLocation;` — `UPROPERTY(EditAnywhere, Category = "Camera", meta = (EditCondition = "!bIsNavigationLocked"))` — The current camera location for this Promoted Frame
- L169 _public member_ `FRotator ViewRotation;` — `UPROPERTY(EditAnywhere, Category = "Camera", meta = (EditCondition = "!bIsNavigationLocked"))` — The current camera rotation for this Promoted Frame
- L173 _public member_ `FVector LookAtLocation;` — `UPROPERTY(EditAnywhere, Category = "Camera", meta = (EditCondition = "!bIsNavigationLocked"))` — The current camera LookAt position for this Promoted Frame
- L177 _public member_ `float CameraViewFOV;` — `UPROPERTY(EditAnywhere, Category = "Camera", DisplayName = "Field Of View", meta = (ClampMin = "0", ClampMax = "170", EditCondition = "!bIsNavigationLocked"))` — The Camera FoV from when the view was promoted
- L181 _public member_ `TEnumAsByte<EViewModeIndex> ViewMode;` — `UPROPERTY(EditAnywhere, Category = "Rendering", DisplayName = "Lighting Mode", meta = (EditCondition = "!bIsNavigationLocked"))` — The View Mode from when the frame was promoted
- L185 _public member_ `float FixedEV100;` — `UPROPERTY(EditAnywhere, Category = "Rendering", DisplayName = "EV100", meta = (EditCondition = "!bIsNavigationLocked", UIMin=-10, UIMax=20))` — The EV100 value to used for this promoted frame
- L190 _private member_ `FSimpleDelegate OnCameraTransformChangedDelegate;` — Delegate called when one of the camera transform parameters changes

#### class `UMetaHumanIdentityFootageFrame`  
`class UMetaHumanIdentityFootageFrame : public UMetaHumanIdentityPromotedFrame`  
_L197-205_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetaHumanIdentityPromotedFrame`
- L204 _public member_ `int32 FrameNumber;` — `UPROPERTY(BlueprintReadWrite, Category = "Frame")`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METAHUMANIDENTITY_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentity/Public/MetaHumanIdentityStyle.h` (Public)


#### class `FMetaHumanIdentityStyle`  
`class FMetaHumanIdentityStyle : public FSlateStyleSet`  
_L9-20_
- inherits: `FSlateStyleSet`
- L13 _public prototype_ `static FMetaHumanIdentityStyle& Get();`
- L15 _public prototype_ `static void Register();`
- L16 _public prototype_ `static void Unregister();`
- L19 _private prototype_ `FMetaHumanIdentityStyle();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANIDENTITY_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentity/Public/MetaHumanIdentityViewportSettings.h` (Public)


#### struct `FMetaHumanIdentityABViewportState`  
`struct FMetaHumanIdentityABViewportState`  
_L19-33_
- reflection: `USTRUCT()`
- L23 _public function_ `FMetaHumanIdentityABViewportState() : bShowCurrentPose(true) , bShowTemplateMesh(false)`
- L29 _public member_ `uint8 bShowCurrentPose : 1;` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`
- L32 _public member_ `uint8 bShowTemplateMesh : 1;` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`

#### struct `FMetaHumanIdentityPoseState`  
`struct FMetaHumanIdentityPoseState`  
_L36-45_
- reflection: `USTRUCT()`
- L41 _public member_ `int32 SelectedFrame = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`
- L44 _public member_ `FFrameTime CurrentFrameTime;` — `UPROPERTY(EditAnywhere, Category = "Viewport Settings")`

#### enum `EIdentityTreeNodeIdentifier`  
`enum class EIdentityTreeNodeIdentifier`  
_L48-59_
- reflection: `UENUM()`
- L50 _public enumerator_ `None`
- L51 _public enumerator_ `IdentityRoot`
- L52 _public enumerator_ `TemplateMesh`
- L53 _public enumerator_ `SkeletalMesh`
- L54 _public enumerator_ `FaceNode`
- L55 _public enumerator_ `BodyNode`
- L56 _public enumerator_ `FacePoseList`
- L57 _public enumerator_ `FaceNeutralPose`
- L58 _public enumerator_ `FaceTeethPose`

#### class `UMetaHumanIdentityViewportSettings`  
`class UMetaHumanIdentityViewportSettings : public UMetaHumanViewportSettings`  
_L62-107_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetaHumanViewportSettings`
- L69 _public prototype_ `UMetaHumanIdentityViewportSettings();`
- L72 _public prototype_ `void ToggleCurrentPoseVisibility(EABImageViewMode InView);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L75 _public prototype_ `bool IsCurrentPoseVisible(EABImageViewMode InView) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L78 _public prototype_ `void ToggleTemplateMeshVisibility(EABImageViewMode InView);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L81 _public prototype_ `bool IsTemplateMeshVisible(EABImageViewMode InView) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L84 _public prototype_ `void SetSelectedPromotedFrame(EIdentityPoseType InPoseType, int32 InPromotedFrameIndex);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L87 _public prototype_ `int32 GetSelectedPromotedFrame(EIdentityPoseType InPoseType) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L90 _public prototype_ `void SetFrameTimeForPose(EIdentityPoseType InPoseType, const FFrameTime& InFrameTime);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L93 _public prototype_ `FFrameTime GetFrameTimeForPose(EIdentityPoseType InPoseType) const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Viewport Settings")`
- L98 _public member_ `EIdentityTreeNodeIdentifier SelectedTreeNode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewport Settings")`
- L103 _private member_ `TMap<EIdentityPoseType, FMetaHumanIdentityPoseState> IdentityPosesState;` — `UPROPERTY(VisibleAnywhere, Category = "Viewport Settings")`
- L106 _private member_ `TMap<EABImageViewMode, FMetaHumanIdentityABViewportState> IdentityViewportState;` — `UPROPERTY(VisibleAnywhere, Category = "Viewport Settings")`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANIDENTITY_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentity/Public/MetaHumanPredictiveSolversTask.h` (Public)


#### struct `FPredictiveSolversTaskConfig`  
`struct FPredictiveSolversTaskConfig`  
_L15-25_
- desc: Predictive solvers configuration.
- L17 _public member_ `FString TemplateDescriptionJson;`
- L18 _public member_ `FString ConfigurationJson;`
- L19 _public member_ `TSharedPtr<class IDNAReader> DNAReader;`
- L21 _public member_ `TWeakObjectPtr<class UDNAAsset> DNAAsset;` — `UE_DEPRECATED(5.8, "Use DNA Reader instead, this is old DNA Asset User data which has been deprecated in favor of DNA asset.")`
- L22 _public member_ `TArray<uint8> PredictiveSolverGlobalTeethTrainingData;`
- L23 _public member_ `TArray<uint8> PredictiveSolverTrainingData;`
- L24 _public member_ `bool bTrainPreviewSolvers = true;`

#### struct `FPredictiveSolversResult`  
`struct FPredictiveSolversResult`  
_L30-35_
- desc: Predictive solvers training result.
- L32 _public member_ `TArray<uint8> PredictiveWithoutTeethSolver;`
- L33 _public member_ `TArray<uint8> PredictiveSolvers;`
- L34 _public member_ `bool bSuccess = false;`

#### class `FPredictiveSolversWorker`  
`class FPredictiveSolversWorker : public FNonAbandonableTask`  
_L40-68_
- inherits: `FNonAbandonableTask`
- desc: Predictive solvers worker that actually does calculations.
- L43 _public typedef_ `using SolverProgressFunc = TFunction<void(float)>;`
- L44 _public typedef_ `using SolverCompletedFunc = TFunction<void(void)>;`
- L46 _public prototype_ `FPredictiveSolversWorker(bool bInIsAsync, const FPredictiveSolversTaskConfig& InConfig, SolverProgressFunc InOnProgress, SolverCompletedFunc InOnCompleted, std::atomic<bool>& bInIsCancelled, std::atomic<float>& InProgress);`
- L48 _public function_ `inline TStatId GetStatId() const`
- L53 _public prototype_ `void DoWork();`
- L57 _private prototype_ `void RunTraining();`
- L59 _private member_ `bool bIsAsync = true;`
- L60 _private member_ `FPredictiveSolversTaskConfig Config;`
- L61 _private member_ `SolverProgressFunc OnProgress;`
- L62 _private member_ `SolverCompletedFunc OnCompleted;`
- L63 _private member_ `std::atomic<bool>& bIsCancelled;`
- L64 _private member_ `std::atomic<float>& Progress;`
- L65 _private member_ `float LastProgress = 0.0f;`
- L66 _private member_ `std::atomic<bool> bIsDone = false;`
- L67 _private member_ `FPredictiveSolversResult Result;`

#### class `FPredictiveSolversTask`  
`class FPredictiveSolversTask`  
_L76-108_
- desc: Predictive solver task that creates new worker for predictive solver calculations.
- L79 _public prototype_ `FPredictiveSolversTask(const FPredictiveSolversTaskConfig& InConfig);`
- L81 _public prototype_ `FPredictiveSolversResult StartSync();`
- L82 _public prototype_ `void StartAsync();`
- L85 _public prototype_ `FOnPredictiveSolversCompleted& OnCompletedCallback();` — Only triggered when task is executed asynchronously
- L86 _public prototype_ `FOnPredictiveSolversProgress& OnProgressCallback();`
- L88 _public prototype_ `bool IsDone() const;`
- L89 _public prototype_ `bool WasCancelled() const;`
- L91 _public prototype_ `void Cancel();`
- L92 _public prototype_ `void Stop();`
- L95 _public prototype_ `bool PollProgress(float& OutProgress) const;` — Obtains current training progress in range [0..1]. Return true if it was successful (task is still active), false otherwise
- L98 _private member_ `FPredictiveSolversTaskConfig Config;`
- L99 _private member_ `TUniquePtr<FAsyncTask<class FPredictiveSolversWorker>> Task;`
- L100 _private member_ `std::atomic<bool> bCancelled = false;`
- L101 _private member_ `std::atomic<float> Progress = 0.0f;`
- L102 _private member_ `std::atomic<bool> bSkipCallback = false;`
- L103 _private member_ `FOnPredictiveSolversCompleted OnCompletedDelegate;`
- L104 _private member_ `FOnPredictiveSolversProgress OnProgressDelegate;`
- L106 _private prototype_ `void OnProgress_Thread(float InProgress);`
- L107 _private prototype_ `void OnCompleted_Thread();`

#### class `FPredictiveSolversTaskManager`  
`class FPredictiveSolversTaskManager`  
_L113-135_
- desc: Singleton responsible for managing and owning predictive solver tasks.
- L116 _public prototype_ `static FPredictiveSolversTaskManager& Get();`
- L118 _public prototype_ `FPredictiveSolversTaskManager() = default;`
- L119 _public prototype_ `~FPredictiveSolversTaskManager() = default;`
- L121 _public prototype_ `FPredictiveSolversTaskManager(FPredictiveSolversTaskManager const&) = delete;`
- L122 _public prototype_ `FPredictiveSolversTaskManager& operator=(const FPredictiveSolversTaskManager&) = delete;`
- L125 _public prototype_ `FPredictiveSolversTask* New(const FPredictiveSolversTaskConfig& InConfig);` — Creates new solver tasks and adds to the list of active tasks
- L128 _public prototype_ `bool Remove(FPredictiveSolversTask*& InOutTask);` — Removes given task from the list and nullifies the reference
- L131 _public prototype_ `void StopAll();` — Stops all active tasks
- L134 _private member_ `TArray<TUniquePtr<FPredictiveSolversTask>> Tasks;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANIDENTITY_API`
- L70 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPredictiveSolversCompleted, const FPredictiveSolversResult&);`
- L70 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPredictiveSolversCompleted, const FPredictiveSolversResult&);`
- L71 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPredictiveSolversProgress, float);`
- L71 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPredictiveSolversProgress, float);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentity/Public/MetaHumanTemplateMeshComponent.h` (Public)


#### enum `ETemplateVertexConversion`  
`enum class ETemplateVertexConversion : uint8`  
_L14-19_
- L16 _public enumerator_ `ConformerToUE`
- L17 _public enumerator_ `UEToConformer`
- L18 _public enumerator_ `None`

#### class `UMetaHumanTemplateMeshComponent`  
`class UMetaHumanTemplateMeshComponent : public UPrimitiveComponent`  
_L28-150_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPrimitiveComponent`
- desc: Component to manages different aspects of the MetaHuman Identity Template Mesh. This component makes use of Dynamic Meshes to store and display data. It can be used to store one mesh for each supported pose type, currently these are Neutral and Teeth. ShowHeadMeshForPose can be used to change which is currently active Head Mesh being displayed
- L35 _public prototype_ `UMetaHumanTemplateMeshComponent();`
- L38 _public prototype_ `virtual void OnRegister() override;`
- L39 _public prototype_ `virtual void OnUnregister() override;`
- L40 _public prototype_ `virtual void OnVisibilityChanged() override;`
- L44 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L49 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& InLocalToWorld) const override;`
- L54 _public prototype_ `void LoadMeshAssets();` — Load the mesh assets used by the template
- L57 _public prototype_ `void LoadMaterialsForMeshes();` — Set the override materials for template component meshes. Only needs to happen once
- L60 _public prototype_ `class UDynamicMesh* GetPoseHeadMesh(EIdentityPoseType InPoseType) const;` — Returns the dynamic mesh object for the given pose type
- L63 _public prototype_ `void ShowHeadMeshForPose(EIdentityPoseType InPoseType) const;` — Set the currently active head pose mesh
- L66 _public prototype_ `void SetPoseHeadMeshVertices(EIdentityPoseType InPoseType, TConstArrayView<FVector3f> InNewVertices, ETemplateVertexConversion InConversionType) const;` — Set the pose head mesh from the given array of vertices. The conversion type is used to perform conversions between the different spaces MetaHuman Identity operates in
- L69 _public prototype_ `void GetPoseHeadMeshVertices(EIdentityPoseType InPoseType, const FTransform& InTransform, ETemplateVertexConversion InConversionType, TArray<FVector>& OutPoseHeadVertices) const;` — Returns the vertices for the head mesh of the given pose type. The conversion type can be used to convert from UE space to rig space, which is the space expected by the autorigging service for example
- L72 _public prototype_ `void GetEyeMeshesVertices(const FTransform& InTransform, ETemplateVertexConversion InConversionType, TArray<FVector>& OutLeftEyeVertices, TArray<FVector>& OutRightEyeVertices) const;` — Returns the vertices for both left and right eyes. A transform can be passed in to be baked in the vertices before doing the conversion to the requested space
- L75 _public prototype_ `void GetTeethMeshVertices(const FTransform& InTransform, ETemplateVertexConversion InConversionType, TArray<FVector>& OutTeethVertices) const;` — Returns the vertices for teeth mesh. A transform can be passed in to be baked in the vertices before doing the conversion to the requested space
- L78 _public prototype_ `void SetEyeMeshesVertices(TConstArrayView<FVector3f> InLeftEyeVertices, TConstArrayView<FVector3f> InRightEyeVertices, ETemplateVertexConversion InConversionType);` — Set the vertices for both left and right eyes. The conversion type can be used to convert from rig to UE space or vice versa
- L81 _public prototype_ `void SetEyeMeshesVisibility(bool bInVisible);` — Updates the eye meshes visibility
- L84 _public prototype_ `void SetTeethMeshVisibility(bool bInVisible);` — Updates the teeth mesh visibility
- L87 _public prototype_ `void BakeEyeMeshesTransform(const FTransform& InTransform);` — Bake a transform into the vertices of the eye meshes
- L90 _public prototype_ `void SetTeethMeshVertices(TConstArrayView<FVector3f> InNewVertices, ETemplateVertexConversion InConversionType) const;` — Set the vertices of the teeth mesh
- L93 _public prototype_ `void BakeTeethMeshTransform(const FTransform& InTransform);` — Bake a transform into the vertices of the teeth meshes
- L96 _public prototype_ `void ResetMeshes();` — Resets the template mesh
- L99 _public prototype_ `static FVector ConvertVertex(const FVector& InVertex, ETemplateVertexConversion InConversionType);` — Convert a vector from one coordinate system to another
- L104 _public member_ `static FTransform UEToRigSpaceTransform;` — Transform that can be used with the Bake functions to align the meshes with conformed data
- L110 _public member_ `uint8 bShowFittedTeeth : 1;` — `UPROPERTY(EditAnywhere, Category = "Preview")` — Whether or not the fitted teeth mesh is active
- L114 _public member_ `uint8 bShowEyes : 1;` — `UPROPERTY(EditAnywhere, Category = "Preview")` — Whether or not to show the eye meshes
- L118 _public member_ `uint8 bShowTeethMesh : 1;` — `UPROPERTY(EditAnywhere, Category = "Preview")` — Whether or not to show the teeth mesh
- L122 _public member_ `TObjectPtr<class UDynamicMeshComponent> HeadMeshComponent;` — `UPROPERTY()` — The component that displays the currently active head mesh
- L126 _public member_ `TMap<EIdentityPoseType, TObjectPtr<class UDynamicMesh>> PoseHeadMeshes;` — `UPROPERTY()` — Stores the dynamic meshes for each support pose. ShowHeadMeshForPose will select a mesh from this map
- L130 _public member_ `TObjectPtr<class UDynamicMeshComponent> TeethMeshComponent;` — `UPROPERTY()` — The component that displays the currently active teeth mesh
- L134 _public member_ `TObjectPtr<class UDynamicMeshComponent> LeftEyeComponent;` — `UPROPERTY()` — The component that displays the left eye mesh
- L138 _public member_ `TObjectPtr<class UDynamicMeshComponent> RightEyeComponent;` — `UPROPERTY()` — The component that displays the right eye mesh
- L142 _public member_ `TObjectPtr<class UDynamicMesh> OriginalTeethMesh;` — `UPROPERTY()` — Keeps the teeth mesh before fitting. Changing bShowFittedTeeth will toggle between this and FittedTeethMesh
- L146 _public member_ `TObjectPtr<class UDynamicMesh> FittedTeethMesh;` — `UPROPERTY()` — Stores the fitted teeth mesh. Changing bShowFittedTeeth will toggle between this and OriginalTeethMesh
- L149 _public member_ `FSimpleMulticastDelegate OnTemplateMeshChanged;` — Delegate called any time one of the mesh components is modified. This is mainly used to update component instances

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANIDENTITY_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentity/Public/PredictiveSolverInterface.h` (Public)
_(no declarations extracted)_

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanIdentity/Public/PromotedFrameUtils.h` (Public)


#### class `UPromotedFrameUtils`  
`class UPromotedFrameUtils : public UObject`  
_L22-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L31 _public prototype_ `static bool InitializeContourDataForFootageFrame(class UMetaHumanIdentityPose* InPose, class UMetaHumanIdentityFootageFrame* InFootageFrame);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Frame Initialization")` — Initialization function exposed for scripting - parses contour data config & updates footage frame
- L35 _public prototype_ `static bool GetPromotedFrameAsPixelArrayFromDisk(const FString& InImagePath, FIntPoint& OutImageSize, TArray<FColor>& OutLocalSamples);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Texture Retrieval")` — Assigns loaded texture from specified path to TArray of BGRA colors. Returns true if successfully read and assigned data
- L38 _public prototype_ `static class UTexture2D* GetBGRATextureFromFile(const FString& InFilePath);` — Uses image wrapper to determine image format and returns BGRA texture
- L41 _public prototype_ `static class UTexture2D* GetDepthTextureFromFile(const FString& InFilePath);` — Returns a depth texture, loaded from a file on disk specified in the path
- L45 _public prototype_ `static FString GetImagePathForFrame(const class UFootageCaptureData* InFootageCaptureData, const FString& InCamera, const int32 InFrameId, bool bInIsImageSequence, ETimecodeAlignment InAlignment);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Texture Retrieval")` — A helper function to determine the full path to a frame, taking into account timecode alignment
- L50 _public prototype_ `static int32 IdentityFrameNumberToImageSequenceFrameNumber(const class UFootageCaptureData* InFootageCaptureData, const FString& InCamera, const int32 InFrameId, bool bInIsImageSequence, ETimecodeAlignment InAlignment);` — Converts a frame number used by identity into the corresponding frame number in the underlying image sequence. Accounts for the case where the media track in sequencer does not start at zero. @param InFrameId  Must be in the sequencer display rate.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METAHUMANIDENTITY_API`
