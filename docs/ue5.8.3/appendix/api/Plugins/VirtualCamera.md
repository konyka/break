# Plugins / VirtualCamera

- module root: `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCamera`
- headers: 12; symbols: 222
- symbol kinds: class=11, delegate=3, enum=4, enumerator=11, function=9, member=39, namespace=6, prototype=135, struct=4
- PrivateDependencyModuleNames: AdvancedWidgets, AnimationCore, ConcertTakeRecorder, Constraints, EditorFramework, EditorScriptingUtilities, LevelEditor, MediaIOCore, MovieSceneTracks, Slate, TakeRecorderSources, TakesCore, UnrealEd, VPUtilitiesEditor
- PublicDependencyModuleNames: AssetRegistry, AugmentedReality, CinematicCamera, Core, CoreUObject, Engine, InputCore, LevelSequence, LevelSequenceEditor, LiveLinkInterface, MovieScene, RemoteSession, Sequencer, SlateCore, TakeRecorder, TimeManagement, UMG, VCamCore, VPUtilities

### `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCamera/Private/Cinematic/MovieSceneSpawnableVCamBinding.h` (Private)


#### class `UMovieSceneSpawnableVCamBinding`  
`class UMovieSceneSpawnableVCamBinding : public UMovieSceneSpawnableActorBinding`  
_L21-36_
- reflection: `UCLASS()`
- inherits: `UMovieSceneSpawnableActorBinding`
- desc: Allows the AVCamBaseActor to be recorded as ACineCameraActor instead. This allows users to record a VCam actor using Take Recorder and disable the VCam plugin afterwards while still being able to use the recorded sequences without missing classes. This class is never actually instantiated. It simply creates a UMovieSceneSpawnableActorBinding that contains a ACineCameraActor instead of a VCam. Not instantiating this class is important: otherwise the sequence referencing the binding would lose the reference when VCam plugin is disabled as the class would be missing.
- L27 _public prototype_ `virtual bool SupportsBindingCreationFromObject(const UObject* SourceObject) const override;`
- L28 _public prototype_ `virtual UMovieSceneCustomBinding* CreateNewCustomBinding(UObject* SourceObject, UMovieScene& OwnerMovieScene) override;`
- L34 _protected function_ `virtual int32 GetCustomBindingPriority() const override`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace TakeRecorderSources` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCamera/Private/VirtualCamera.h` (Private)


#### class `UE::VirtualCamera::FVirtualCameraModuleImpl`  
`class FVirtualCameraModuleImpl : public IModuleInterface`  
_L12-27_
- inherits: `IModuleInterface`
- L17 _public prototype_ `virtual void StartupModule() override;`
- L18 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _private prototype_ `void OnPostInitEngine();`
- L25 _private prototype_ `void RegisterSettings();`
- L26 _private prototype_ `void UnregisterSettings();`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVirtualCamera, Log, Log);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVirtualCamera, Log, Log);`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace VirtualCamera` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCamera/Public/Cinematic/VCamHierarchyInfo.h` (Public)


#### struct `UE::VirtualCamera::FVCamHierarchyInfo`  
`struct FVCamHierarchyInfo`  
_L13-29_
- desc: Gets components of a VCamActor for the purpose of deciding whether it should be recorded as cine camera in Sequencer.
- L15 _public member_ `const AActor* Actor;`
- L16 _public member_ `UVCamComponent* VCamComponent;`
- L18 _public member_ `USceneComponent* RootComponent;`
- L19 _public member_ `UCineCameraComponent* Camera;`
- L21 _public function_ `explicit FVCamHierarchyInfo(TNotNull<const UObject*> SourceObject) : Actor(SourceObject->IsA<AActor>() ? Cast<AActor>(SourceObject) : SourceObject->GetTypedOuter<AActor>()) , VCamComponent(Actor ? Actor->FindComponentByClass<UVCamComponent>() : nullptr) , RootComponent(Actor ? Actor->GetRootComponent() : nullptr) , Camera(VCamComponent ? VCamComponent->GetTargetCamera() : nullptr)`
- L28 _public function_ `bool ShouldRecordAsCineCamera() const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace VirtualCamera` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCamera/Public/FunctionLibraries/AssetFilteringAndSortingFunctionLibrary.h` (Public)


#### enum `ESortOrder`  
`enum class UE_DEPRECATED(5.5, "Use EEditorAssetSortOrder instead") ESortOrder : uint8`  
_L16-20_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `Ascending`
- L19 _public enumerator_ `Descending`

#### enum `EAssetTagMetaDataSortType`  
`enum class UE_DEPRECATED(5.5, "Use EEditorAssetMetaDataSortType instead") EAssetTagMetaDataSortType : uint8`  
_L23-28_
- reflection: `UENUM(BlueprintType)`
- L25 _public enumerator_ `String`
- L26 _public enumerator_ `Numeric`
- L27 _public enumerator_ `DateTime`

#### class `UDEPRECATED_AssetFilteringAndSortingFunctionLibrary`  
`class UE_DEPRECATED(5.5, "Use the equivalent function in UEditorAssetSubsystem and UAssetRegistryHelpers instead") UDEPRECATED_AssetFilteringAndSortingFunctionLibrary : public UBlueprintFunctionLibrary`  
_L35-84_
- reflection: `UCLASS(BlueprintType, Deprecated)`
- inherits: `UBlueprintFunctionLibrary`
- desc: This library's purpose is to facilitate Blueprints to discover assets using some filters and sort them.
- L43 _public prototype_ `static TArray<FAssetData> GetAllAssetsByMetaDataTags(const TSet<FName>& RequiredTags, const TSet<UClass*>& AllowedClasses);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera | Clips", meta = (DeprecatedFunction, DeprecationMessage = "Use EditorAssetSubsystem's GetAllAssetsByMetaDataTags instead."))` — `UE_DEPRECATED(5.5, "Use UEditorAssetSubsystem::GetAllAssetsByMetaDataTags instead.")` — Gets all assets which have the given tags.
- L51 _public prototype_ `static void SortByCustomPredicate(UPARAM(Ref) TArray<FAssetData>& Assets, FAssetSortingPredicate SortingPredicate, ESortOrder SortOrder = ESortOrder::Ascending);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera | Clips", meta = (DeprecatedFunction, DeprecationMessage = "Use AssetRegistryHelpers's SortByCustomPredicate instead."))` — `UE_DEPRECATED(5.5, "Use UAssetRegistryHelpers::SortByCustomPredicate instead.")` — Sorts the assets based on a custom Blueprint delegate. @param SortingPredicate Implements a Left <= Right relation
- L58 _public prototype_ `static void SortByAssetName(UPARAM(Ref) TArray<FAssetData>& Assets, ESortOrder SortOrder = ESortOrder::Ascending);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera | Clips", meta = (DeprecatedFunction, DeprecationMessage = "Use AssetRegistryHelpers's SortByAssetName instead."))` — `UE_DEPRECATED(5.5, "Use UAssetRegistryHelpers::SortByAssetName instead.")` — Sorts the assets by their asset name.
- L73 _public prototype_ `static bool SortByMetaData(UPARAM(Ref) TArray<FAssetData>& Assets, FName MetaDataTag, EAssetTagMetaDataSortType MetaDataType, ESortOrder SortOrder = ESortOrder::Ascending);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera | Clips", meta = (DeprecatedFunction, DeprecationMessage = "Use EditorAssetSubsystem's SortByMetaData instead."))` — `UE_DEPRECATED(5.5, "Use UEditorAssetSubsystem::SortByMetaData instead.")` — Sorts the assets based on their meta data's type. Supported types: FString, int, float, FDateTime. @param Assets The assets to sort @param MetaDataTag The on which the sort is based @param SortOrder Whether to sort ascending or descending @return Whether it was possible to compare all the meta data successfully.
- L82 _public prototype_ `static void SortAssets(TArray<FAssetData>& Assets, TFunctionRef<bool(const FAssetData& Left, const FAssetData& Right)> Predicate, ESortOrder SortOrder);` — `UE_DEPRECATED(5.5, "This function will not be replaced. Write your own version.")` — Util that does the actual sorting @param Predicate Implements a Left <= Right relation

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FAssetSortingPredicate, const FAssetData&, Left, const FAssetData&, Right);`
- L31 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_TwoParams(bool, FAssetSortingPredicate, const FAssetData&, Left, const FAssetData&, Right);` — `UE_DEPRECATED(5.5, "Use the equivalent delegates for UEditorAssetSubsystem and UAssetRegistryHelpers instead")`

### `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCamera/Public/FunctionLibraries/GameViewFunctionLibrary.h` (Public)


#### class `UGameViewFunctionLibrary`  
`class UGameViewFunctionLibrary : public UBlueprintFunctionLibrary`  
_L13-68_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Library for changing the viewport into game view. Game view shows the scene as it appears in game.
- L25 _public prototype_ `static void ToggleGameView(EVCamTargetViewportID ViewportID);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Camera | Game View")` — Toggles the game view. Game view shows the scene as it appears in game. @note Only works in editor builds.
- L32 _public prototype_ `static bool CanToggleGameView(EVCamTargetViewportID ViewportID);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Camera | Game View")` — @return Whether we can toggle game view. @note Only works in editor builds.
- L39 _public prototype_ `static bool IsInGameView(EVCamTargetViewportID ViewportID);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Camera | Game View")` — @return Whether we are in game view. @note Only works in editor builds.
- L46 _public prototype_ `static void SetGameViewEnabled(EVCamTargetViewportID ViewportID, bool bIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Camera | Game View")` — Sets whether the specified viewport should have the game view enabled. @note Only works in editor builds.
- L53 _public prototype_ `static void SetGameViewEnabledForAllViewports(bool bIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Camera | Game View")` — Sets the game view mode for all open viewports. @note Only works in editor builds.
- L60 _public prototype_ `static TMap<EVCamTargetViewportID, bool> SnapshotGameViewStates();` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera | Game View")` — @return The state of each viewport's state. If the viewport is not currently open, then the returned map will not have any entry for it. @note Only works in editor builds.
- L67 _public prototype_ `static void RestoreGameViewStates(const TMap<EVCamTargetViewportID, bool>& Snapshot);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Camera | Game View")` — Sets the game view of the viewports as specified in the map. Util for using together with SnapshotGameViewStates. @note Only works in editor builds.

### `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCamera/Public/FunctionLibraries/LevelSequenceVCamLibrary.h` (Public)


#### struct `FPilotableSequenceCameraInfo`  
`struct FPilotableSequenceCameraInfo`  
_L16-23_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `TObjectPtr<UCameraComponent> Camera;` — `UPROPERTY(BlueprintReadOnly, Category = "Virtual Camera | Level Sequence")` — A camera from a sequencer track

#### class `ULevelSequenceVCamLibrary`  
`class ULevelSequenceVCamLibrary : public UBlueprintFunctionLibrary`  
_L29-62_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Utility functions for Level Sequences to implement VCamHUD UI.
- L41 _public prototype_ `static bool HasAnyCameraCutsInLevelSequence(ULevelSequence* Sequence);` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera | Level Sequence", meta = (WorldContext = "WorldContextObject"))` — Checks whether this sequence has any camera cuts set up. If yes, you should pilot the sequence using ULevelSequenceEditorBlueprintLibrary::SetLockCameraCutToViewport instead of directly piloting by using FindLevelSequencePilotableCamerasInActiveLevelSequence.
- L53 _public prototype_ `static int32 ClearVCamConstraintBakeTracks(ULevelSequence* Sequence, AActor* VCamActor);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Camera | Level Sequence")` — Removes baked transform keys that fight a parent constraint on a VCam binding. Sets the section's TransformMask to match the constraint's TransformFilter so only constrained axes are evaluated. Must be called again if TransformFilter changes. @param Sequence    The level sequence to operate on. @param VCamActor   The VCam actor to clean up. Pass nullptr to process all bindings with constraint channels. @return            Number of sections cleared.
- L61 _public prototype_ `static TArray<FPilotableSequenceCameraInfo> FindPilotableCamerasInActiveLevelSequence();` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera | Level Sequence")` — Gets all cameras currently spawned by the active level sequence. Note: You must have called ULevelSequenceEditorBlueprintLibrary::OpenLevelSequence before calling this function. Note: Only works in the editor.

### `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCamera/Public/FunctionLibraries/MultiUserTakesVCamFunctionLibrary.h` (Public)


#### class `UMultiUserTakesVCamFunctionLibrary`  
`class UMultiUserTakesVCamFunctionLibrary : public UBlueprintFunctionLibrary`  
_L13-73_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: This library wraps UMultiUserTakesFunctionLibrary: in editor builds, the calls are forwarded and cooked builds, the calls are compiled out. This is done so that Blueprints can continue to be cooked without crashing due to missing functions.
- L23 _public prototype_ `static bool GetRecordOnClientLocal();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera | Multi User Takes")` — Gets the checkbox value in the "Record On Client" column in the settings displayed at the bottom of the "Take Recorder" tab. This is an utility for getting the local client's value; GetRecordOnClient can also be used.
- L30 _public prototype_ `static void SetRecordOnClientLocal(bool bNewValue);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera | Multi User Takes")` — Sets the checkbox value in the "Record On Client" column in the settings displayed at the bottom of the "Take Recorder" tab. This is an utility for setting the local client's value; SetRecordOnClient can also be used.
- L39 _public prototype_ `static bool GetRecordOnClient(const FGuid& ClientEndpointId);` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera | Multi User Takes")` — Gets the checkbox value in the "Record On Client" column in the settings displayed at the bottom of the "Take Recorder" tab. This function queries the state of any connected client. For the local client, you can also use GetRecordOnClientLocal. @param ClientEndpointId ID of the client. You can get this by using e.g.UMultiUserSubsystem::GetRemoteClientIds or UMultiUserSubsystem::GetLocalClientId.
- L49 _public prototype_ `static void SetRecordOnClient(const FGuid& ClientEndpointId, bool bNewValue);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera | Multi User Takes")` — Sets the checkbox value in the "Record On Client" column in the settings displayed at the bottom of the "Take Recorder" tab. This function queries the state of any connected client. For the local client, you can also use SetRecordOnClientLocal. @param ClientEndpointId ID of the client. You can get this by using e.g.UMultiUserSubsystem::GetRemoteClientIds or UMultiUserSubsystem::GetLocalClientId. @param bNewValue The new value to set
- L56 _public prototype_ `static bool GetSynchronizeTakeRecorderTransactionsLocal();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera | Multi User Takes")` — Gets the value of the "SynchronizeTakeRecorderTransactions" checkbox in the settings displayed at the bottom of the "Take Recorder" tab. This is an utility for getting the local client's value; GetSynchronizeTakeRecorderTransactions can also be used.
- L65 _public prototype_ `static bool GetSynchronizeTakeRecorderTransactions(const FGuid& ClientEndpointId);` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera | Multi User Takes")` — Gets the value of the "SynchronizeTakeRecorderTransactions" checkbox in the settings displayed at the bottom of the "Take Recorder" tab. This function queries the state of any connected client. For the local client, you can also use GetSynchronizeTakeRecorderTransactionsLocal. @param ClientEndpointId ID of the client. You can get this by using e.g.UMultiUserSubsystem::GetRemoteClientIds or UMultiUserSubsystem::GetLocalClientId.
- L72 _public prototype_ `static void SetSynchronizeTakeRecorderTransactionsLocal(bool bNewValue);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera | Multi User Takes")` — Sets the value of the "SynchronizeTakeRecorderTransactions" checkbox in the settings displayed at the bottom of the "Take Recorder" tab. @note Only the value of the local client can be set. Setting of remote clients is not implemented (no technical reason - there just never was a use-case).

### `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCamera/Public/FunctionLibraries/TakeMetaDataTagsFunctionLibrary.h` (Public)


#### class `UTakeMetaDataTagsFunctionLibrary`  
`class UTakeMetaDataTagsFunctionLibrary : public UBlueprintFunctionLibrary`  
_L10-46_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UBlueprintFunctionLibrary`
- desc: This library's purpose is to expose the names of the UTakeMetaData asset registry tag names.
- L17 _public prototype_ `static FName GetTakeMetaDataTag_Slate();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — The asset registry tag that contains the slate for this meta-data
- L21 _public prototype_ `static FName GetTakeMetaDataTag_TakeNumber();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — The asset registry tag that contains the take number for this meta-data
- L25 _public prototype_ `static FName GetTakeMetaDataTag_Timestamp();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — The asset registry tag that contains the timestamp for this meta-data
- L29 _public prototype_ `static FName GetTakeMetaDataTag_TimecodeIn();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — The asset registry tag that contains the timecode in for this meta-data
- L33 _public prototype_ `static FName GetTakeMetaDataTag_TimecodeOut();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — The asset registry tag that contains the timecode out for this meta-data
- L37 _public prototype_ `static FName GetTakeMetaDataTag_Description();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — The asset registry tag that contains the user-description for this meta-data
- L41 _public prototype_ `static FName GetTakeMetaDataTag_LevelPath();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — The asset registry tag that contains the level-path for this meta-data
- L45 _public prototype_ `static TSet<FName> GetAllTakeMetaDataTags();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Gets all tags for TakeMetaData

### `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCamera/Public/FunctionLibraries/VCamBlueprintFunctionLibrary.h` (Public)


#### struct `FVCamTraceHitProxyQueryParams`  
`struct FVCamTraceHitProxyQueryParams`  
_L28-39_
- reflection: `USTRUCT(BlueprintType)`
- L34 _public member_ `int32 HitProxySize = 5;` — `UPROPERTY(EditAnywhere, BlueprintreadWrite, Category = "VirtualCamera")` — Determine the size of the query area around the center pixel.
- L38 _public member_ `TArray<TObjectPtr<AActor>> IgnoredActors;` — `UPROPERTY(EditAnywhere, BlueprintreadWrite, Category = "VirtualCamera")` — Components on these actors should not be considered.

#### struct `FVCamTraceHitProxyResult`  
`struct FVCamTraceHitProxyResult`  
_L42-60_
- reflection: `USTRUCT(BlueprintType)`
- L47 _public member_ `TWeakObjectPtr<AActor> HitActor;` — `UPROPERTY(BlueprintReadOnly, Category = "VirtualCamera")`
- L50 _public member_ `TWeakObjectPtr<UPrimitiveComponent> HitComponent;` — `UPROPERTY(BlueprintReadOnly, Category = "VirtualCamera")`

#### class `UVCamBlueprintFunctionLibrary`  
`class UVCamBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L63-271_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UBlueprintFunctionLibrary`
- L71 _public prototype_ `static bool IsGameRunning();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Returns true if not in editor or if running the game in PIE or Simulate
- L78 _public prototype_ `static ULevelSequence* GetCurrentLevelSequence();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Get the currently opened level sequence asset @see ULevelSequenceEditorBlueprintLibrary::GetCurrentLevelSequence
- L85 _public prototype_ `static ULevelSequence* GetPendingTakeLevelSequence();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Gets the level sequence associated with the current pending take. @see ITakeRecorderModule::GetPendingTake
- L89 _public prototype_ `static bool OpenLevelSequence(ULevelSequence* LevelSequence);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Open a level sequence asset
- L93 _public prototype_ `static void PlayCurrentLevelSequence();` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Play the current level sequence
- L97 _public prototype_ `static void PauseCurrentLevelSequence();` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Pause the current level sequence
- L101 _public prototype_ `static void SetCurrentLevelSequenceCurrentFrame(int32 NewFrame);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Set playback position for the current level sequence in frames
- L105 _public prototype_ `static int32 GetCurrentLevelSequenceCurrentFrame();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Get the current playback position in frames
- L109 _public prototype_ `static int32 GetLevelSequenceLengthInFrames(const ULevelSequence* LevelSequence);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Get length in frames of a level sequence
- L113 _public prototype_ `static FTimecode GetLevelSequenceFrameAsTimecode(const ULevelSequence* LevelSequence, int32 InFrame);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Convert a frame from a level sequence to timecode
- L117 _public prototype_ `static FTimecode GetLevelSequenceFrameAsTimecodeWithoutObject(const FFrameRate DisplayRate, int32 InFrame);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Convert a frame from a level sequence to timecode using only a provided display rate
- L121 _public prototype_ `static bool IsCurrentLevelSequencePlaying();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Check whether the sequence is actively playing.
- L125 _public prototype_ `static UTexture* ImportSnapshotTexture(FString FileName, FString SubFolderName, FString AbsolutePathPackage);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Imports image as a uasset
- L129 _public prototype_ `static bool EditorSaveAsset(FString AssetPath);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera | Clips")` — Save an asset through path. Returns true on success.
- L133 _public prototype_ `static UObject* EditorLoadAsset(FString AssetPath);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera | Clips")` — Load an asset through path.
- L137 _public prototype_ `static void ModifyObjectMetadataTags(UObject* InObject, FName InTag, FString InValue);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera | Clips")` — Modifies a UObject's metadata tags, adding a tag if the tag does not exist.
- L141 _public prototype_ `static TMap<FName, FString> GetObjectMetadataTags(UObject* InObject);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera | Clips")` — Retrieves UObject's metadata tags
- L145 _public prototype_ `static TArray<FAssetData> SortAssetsByTimecodeAssetData(TArray<FAssetData> LevelSequenceAssets);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera | Clips ")` — Sort array of FAssetData by metadata timecode
- L149 _public prototype_ `static void PilotActor(AActor* SelectedActor);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera | Streaming ")` — Pilot the provided actor using editor scripting
- L153 _public prototype_ `static bool UpdatePostProcessSettingsForCapture(USceneCaptureComponent2D* CaptureComponent, float DepthOfField, float FStopValue);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Updates the provided USceneCaptureComponent2D's PostProcessingSettings. Returns true on success.
- L157 _public prototype_ `static FFrameRate GetDisplayRate(ULevelSequence* LevelSequence);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Grab the display rate from a LevelSequences' MovieScene
- L161 _public prototype_ `static FFrameRate ConvertStringToFrameRate(FString InFrameRateString);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Converts a double framerate to a FFrameRate
- L165 _public prototype_ `static bool CallFunctionByName(UObject* ObjPtr, FName FunctionName);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Returns true if the function was found & executed correctly.
- L169 _public prototype_ `static void EditorSetGameView(bool bIsToggled);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Sets the current game view
- L173 _public prototype_ `static float CalculateAutoFocusDistance(FVector2D ReticlePosition, UCineCameraComponent* CineCamera);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Calculates auto focus
- L177 _public prototype_ `static TArray<UObject*> GetBoundObjects(FMovieSceneObjectBindingID CameraBindingID);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Get UObject from Camera Object Bindings
- L181 _public prototype_ `static void EnableDebugFocusPlane(UCineCameraComponent* CineCamera, bool bEnabled);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Enable/Disable debug focus plane
- L185 _public prototype_ `static int32 TimecodeToFrameAmount(FTimecode Timecode, const FFrameRate& InFrameRate);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Convert timecode to amount of frames at a given framerate
- L189 _public prototype_ `static FString GetNextUndoDescription();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Returns the description of the undo action that will be performed next.
- L193 _public prototype_ `static bool CopyToCineCameraActor(UCineCameraComponent* SourceCameraComponent, ACineCameraActor* TargetCameraActor);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Copies all properties from a CineCameraComponent to a CineCameraActor and ensure the root actor transform is updated so the CameraComponents end up in the same World Space position
- L196 _public prototype_ `static void SetActorLabel(AActor* Actor, const FString& NewActorLabel);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")`
- L199 _public prototype_ `static bool IsTakeRecorderPanelOpen();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Take Recorder")`
- L202 _public prototype_ `static bool TryOpenTakeRecorderPanel();` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera|Take Recorder")`
- L206 _public prototype_ `static bool IsRecording();` — `UFUNCTION(BlueprintPure, Category="VirtualCamera|Take Recorder")` — Check whether a recording is currently active
- L208 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnTakeRecorderSlateChanged_VCam, const FString&, Slate);`
- L211 _public prototype_ `static void SetOnTakeRecorderSlateChanged(FOnTakeRecorderSlateChanged_VCam OnTakeRecorderSlateChanged);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera|Take Recorder")` — Called when the slate is changed.
- L215 _public prototype_ `static float GetPlaybackSpeed();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Sequencer")` — Get playback speed in Sequencer
- L219 _public prototype_ `static void SetPlaybackSpeed(float Value=1.0);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera|Sequencer")` — Set playback speed in Sequencer
- L223 _public prototype_ `static bool DeprojectScreenToWorld(const FVector2D& InScreenPosition, FVector& OutWorldPosition, FVector& OutWorldDirection);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Convert 2D screen position to World Space 3D position and direction in the active viewport. Returns false if unable to determine value.
- L227 _public prototype_ `static bool DeprojectScreenToWorldByViewport(const FVector2D& InScreenPosition, EVCamTargetViewportID TargetViewport, FVector& OutWorldPosition, FVector& OutWorldDirection);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Converts 2D screen position to World Space 3D position and direction in the specified viewport. Returns false if unable to determine value. Only works in editor builds.
- L244 _public prototype_ `static bool MultiTraceHitProxyOnViewport(const FVector2D& InScreenPosition, EVCamTargetViewportID InTargetViewport, FVCamTraceHitProxyQueryParams InQueryParams, TArray<FVCamTraceHitProxyResult>& Result);` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Traces from the viewport and returns all components that contribute to the pixels surrounding InScreenPosition. The size of the pixel area checked is controlled by InQueryParams.HitProxySize. This finds actors that have NoCollision set. The actor is found by determining which actors contribute to the specified pixel. This function is designed for Editor builds; in Runtime builds, it returns false. @param InScreenPosition The viewport position to trace @param InTargetViewport The viewport to trace in @param InQueryParams Parameters for how the actors should be queried @param Result The result, set if this function returns true. @return Whether Result was written to
- L248 _public prototype_ `static bool IsAssetDirty(const FAssetData& AssetData);` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera")` — Checks if the asset is dirty
- L259 _public prototype_ `static void SetCameraOverscan(UCineCameraComponent* InCameraComponent, const FVector4f& InAsymmetricOverscan, bool bScaleResolution = false);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Adds asymmetric overscan to the camera. @param InCameraComponent - The camera to add overscan to @param InAsymmetricOverscan - The amount of asymmetric overscan to apply, from 0.0 meaning no overscan to 1.0 meaning 100% overscan. By convention, X is the left overscan, Y is the right overscan, Z is the top overscan, and W is the bottom overscan. @param bScaleResolution - Indicates if the render resolution should be scaled up so that the original frustum of the camera remains the same resolution
- L263 _public prototype_ `static void ClearCameraOverscan(UCineCameraComponent* InCameraComponent);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")` — Clears any overscan from the camera
- L269 _private prototype_ `static TWeakPtr<ISequencer> GetSequencer();` — Returns the current sequencer.

#### Free symbols / members of external scopes

- L52 _function_ `friend bool operator==(const FVCamTraceHitProxyResult& Left, const FVCamTraceHitProxyResult& Right)`
- L56 _function_ `friend bool operator!=(const FVCamTraceHitProxyResult& Left, const FVCamTraceHitProxyResult& Right)`
- L208 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnTakeRecorderSlateChanged_VCam, const FString&, Slate);`

### `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCamera/Public/LevelSequence/VCamTakesMetaDataMigration.h` (Public)


#### class `UVCamTakesMetaDataMigration`  
`class UVCamTakesMetaDataMigration : public UBlueprintFunctionLibrary`  
_L13-88_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Helps VCam Blueprints migrate. UVirtualCameraClipsMetaData
- L24 _public prototype_ `static bool GetIsNoGood(ULevelSequence* InLevelSequence, bool& bOutNoGood);` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera", meta = (DisplayName = "Get Is No Good (Migration)"))` — Gets whether the user has marked this take as no good. Does no migration. Looks for new data source first and falls back to legacy data. @return Whether there is any data (legacy or new) stored.
- L31 _public prototype_ `static bool GetIsFlagged(ULevelSequence* InLevelSequence, bool& bOutIsFlagged);` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera", meta = (DisplayName = "Get Is Flagged (Migration)"))` — Gets whether this was flagged by a user. Does no migration. Looks for new data source first and falls back to legacy data. @return Whether there is any data (legacy or new) stored.
- L38 _public prototype_ `static bool GetFavoriteLevel(ULevelSequence* InLevelSequence, int32& OutFavoriteLevel);` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera", meta = (DisplayName = "Get Favorite Level (Migration)"))` — Gets the favorite rating. The favorite rating is like a star rating, usually 1-3 if it was rated. Does no migration. Looks for new data source first and falls back to legacy data. @return Whether there is any data (legacy or new) stored.
- L46 _public prototype_ `static bool GetIsNoGoodByAssetData(const FAssetData& InAssetData, bool& bOutNoGood);` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera", meta = (DisplayName = "Get Is No Good By Asset Data (Migration)"))` — Gets whether the user has marked this take as no good. Does no migration. Looks for new data source first and falls back to legacy data. @return Whether there is any data (legacy or new) stored.
- L53 _public prototype_ `static bool GetIsFlaggedByAssetData(const FAssetData& InAssetData, bool& bOutIsFlagged);` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera", meta = (DisplayName = "Get Is Flagged By Asset Data (Migration)"))` — Gets whether this was flagged by a user. Does no migration. Looks for new data source first and falls back to legacy data. @return Whether there is any data (legacy or new) stored.
- L60 _public prototype_ `static bool GetFavoriteLevelByAssetData(const FAssetData& InAssetData, int32& OutFavoriteLevel);` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera", meta = (DisplayName = "Get Favorite Level By Asset Data (Migration)"))` — Gets the favorite rating. The favorite rating is like a star rating, usually 1-3 if it was rated. Does no migration. Looks for new data source first and falls back to legacy data. @return Whether there is any data (legacy or new) stored.
- L64 _public prototype_ `static void SetIsNoGood(ULevelSequence* InLevelSequence, bool bInIsNoGood);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", meta = (DisplayName = "Set Is No Good (Migration)"))` — Sets whether the user has marked this take as no good. Always writes the data to the new data source.
- L67 _public prototype_ `static void SetIsFlagged(ULevelSequence* InLevelSequence, bool bInIsFlagged);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", meta = (DisplayName = "Set Is Flagged (Migration)"))` — Sets whether this was flagged by a user. Always writes the data to the new data source.
- L70 _public prototype_ `static void SetFavoriteLevel(ULevelSequence* InLevelSequence, int32 InFavoriteLevel);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", meta = (DisplayName = "Set Favorite Level (Migration)"))` — Sets the favorite rating. The favorite rating is like a star rating, usually 1-3 if it was rated. Always writes the data to the new data source.
- L74 _public prototype_ `static bool NeedsToMigrateVCamMetaData(ULevelSequence* InLevelSequence);` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera", meta = (DisplayName = "Needs Migration For VCam TakesMeta Data (Migration)"))` — @return Whether the passed in level sequence contains the legacy UVirtualCameraClipsMetaData
- L77 _public prototype_ `static bool NeedsToMigrateVCamMetaDataByAssetData(const FAssetData& InAssetData);` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera", meta = (DisplayName = "Needs Migration For VCam TakesMeta Data By Asset Data (Migration)"))` — @return Whether the passed in level sequence contains the legacy UVirtualCameraClipsMetaData
- L81 _public prototype_ `static void MigrateVCamTakesMetaData(ULevelSequence* InLevelSequence);` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera", meta = (DisplayName = "Migrate VCam Takes Meta Data (Migration)"))` — Migrates UVirtualCameraClipsMetaData to UMovieSceneShotMetaData.
- L84 _public prototype_ `static bool GetAutoMigrateAccessedLevelSequencesCVar();` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")`
- L87 _public prototype_ `static void SLOW_MigrateAllVCamTakesMetaDataInProject();` — `UFUNCTION(BlueprintCallable, Category = "VirtualCamera")`

### `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCamera/Public/LevelSequence/VirtualCameraClipsMetaData.h` (Public)


#### class `UVirtualCameraClipsMetaData`  
`class UVirtualCameraClipsMetaData : public UObject , public IMovieSceneMetaDataInterface`  
_L15-348_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject,IMovieSceneMetaDataInterface`
- desc: Clips meta-data that is stored on ULevelSequence assets that are recorded through the virtual camera. Meta-data is retrieved through ULevelSequence::FindMetaData<UVirtualCameraClipsMetaData>().
- L22 _public prototype_ `UVirtualCameraClipsMetaData(const FObjectInitializer& ObjInit);`
- L28 _public member_ `static const FName AssetRegistryTag_FocalLength;` — `UE_DEPRECATED(5.6, "Data was removed.")` — The asset registry tag that contains the focal length for this meta-data
- L32 _public member_ `static const FName AssetRegistryTag_bIsSelected;` — `UE_DEPRECATED(5.6, "Data was removed.")` — The asset registry tag that contains if the selected state for this meta-data
- L36 _public member_ `static const FName AssetRegistryTag_RecordedLevelName;` — `UE_DEPRECATED(5.6, "Data was removed.")` — The asset registry tag that contains the recorded level name for this meta-data
- L40 _public member_ `static const FName AssetRegistryTag_FrameCountStart;` — `UE_DEPRECATED(5.6, "Data was removed.")` — The asset registry tag that contains the FrameCountStart in for this meta-data
- L44 _public member_ `static const FName AssetRegistryTag_FrameCountEnd;` — `UE_DEPRECATED(5.6, "Data was removed.")` — The asset registry tag that contains the FrameCountEnd out for this meta-data
- L48 _public member_ `static const FName AssetRegistryTag_LengthInFrames;` — `UE_DEPRECATED(5.6, "Data was removed.")` — The asset registry tag that contains the LengthInFrames out for this meta-data
- L52 _public member_ `static const FName AssetRegistryTag_DisplayRate;` — `UE_DEPRECATED(5.6, "Data was removed.")` — The asset registry tag that contains the FrameCountEnd out for this meta-data
- L56 _public member_ `static const FName AssetRegistryTag_bIsACineCameraRecording;` — `UE_DEPRECATED(5.6, "Data was removed.")` — The asset registry tag that contains whether the clip was recorded with a CineCamera for this meta-data
- L60 _public member_ `static const FName AssetRegistryTag_bIsNoGood;` — `UE_DEPRECATED(5.6, "Use ULevelSequenceShotMetaDataLibrary::GetIsNoGoodAssetTag instead.")` — The asset registry tag that contains whether this take is good or not
- L64 _public member_ `static const FName AssetRegistryTag_bIsFlagged;` — `UE_DEPRECATED(5.6, "Use ULevelSequenceShotMetaDataLibrary::GetIsFlaggedAssetTag instead.")` — The asset registry tag that contains whether this was flagged by a user
- L68 _public member_ `static const FName AssetRegistryTag_FavoriteLevel;` — `UE_DEPRECATED(5.6, "Use ULevelSequenceShotMetaDataLibrary::GetFavoriteRatingAssetTag instead.")` — The asset registry tag that contains its favorite status
- L72 _public member_ `static const FName AssetRegistryTag_bIsCreatedFromVCam;` — `UE_DEPRECATED(5.6, "Data was removed.")` — The asset registry tag that contains whether it was created from a VCam
- L75 _public member_ `static const FName AssetRegistryTag_PostSmoothLevel;` — The asset registry tag that contains the post smooth level
- L82 _public prototype_ `static FName GetClipsMetaDataTag_FocalLength();` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — The asset registry tag that contains the focal length for this meta-data
- L87 _public prototype_ `static FName GetClipsMetaDataTag_IsSelected();` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — The asset registry tag that contains if the selected state for this meta-data
- L92 _public prototype_ `static FName GetClipsMetaDataTag_RecordedLevel();` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — The asset registry tag that contains the recorded level name for this meta-data
- L97 _public prototype_ `static FName GetClipsMetaDataTag_FrameCountStart();` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — The asset registry tag that contains the FrameCountStart in for this meta-data
- L102 _public prototype_ `static FName GetClipsMetaDataTag_FrameCountEnd();` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — The asset registry tag that contains the FrameCountEnd out for this meta-data
- L107 _public prototype_ `static FName GetClipsMetaDataTag_LengthInFrames();` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — The asset registry tag that contains the LengthInFrames out for this meta-data
- L112 _public prototype_ `static FName GetClipsMetaDataTag_DisplayRate();` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — The asset registry tag that contains the FrameCountEnd out for this meta-data
- L117 _public prototype_ `static FName GetClipsMetaDataTag_IsCineACineCameraRecording();` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera|Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — The asset registry tag that contains whether the clip was recorded with a CineCamera for this meta-data
- L122 _public prototype_ `static FName GetClipsMetaDataTag_IsNoGood();` — `UE_DEPRECATED(5.6, "Use ULevelSequenceShotMetaDataLibrary::GetIsNoGoodAssetTag instead.")` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Clips", meta=(DeprecatedFunction, DeprecationMessage="Use ULevelSequenceShotMetaDataLibrary::GetIsNoGoodAssetTag instead."))` — The asset registry tag that contains whether this take is good or not
- L127 _public prototype_ `static FName GetClipsMetaDataTag_IsFlagged();` — `UE_DEPRECATED(5.6, "Use ULevelSequenceShotMetaDataLibrary::GetIsFlaggedAssetTag instead.")` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Clips", meta=(DeprecatedFunction, DeprecationMessage="Use ULevelSequenceShotMetaDataLibrary::GetIsFlaggedAssetTag instead."))` — The asset registry tag that contains whether this was flagged by a user
- L132 _public prototype_ `static FName GetClipsMetaDataTag_FavoriteLevel();` — `UE_DEPRECATED(5.6, "Use ULevelSequenceShotMetaDataLibrary::GetFavoriteRatingAssetTag instead.")` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Clips", meta=(DeprecatedFunction, DeprecationMessage="Use ULevelSequenceShotMetaDataLibrary::GetFavoriteRatingAssetTag instead."))` — The asset registry tag that contains its favorite status
- L137 _public prototype_ `static FName GetClipsMetaDataTag_IsCreatedFromVCam();` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — The asset registry tag that contains whether it was created from a VCam
- L141 _public prototype_ `static FName GetClipsMetaDataTag_PostSmoothLevel();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Clips")` — The asset registry tag that contains post smooth level
- L145 _public prototype_ `static TSet<FName> GetAllClipsMetaDataTags();` — `UFUNCTION(BlueprintPure, Category = "VirtualCamera|Clips")` — Gets all asset registry tags
- L152 _public prototype_ `virtual void ExtendAssetRegistryTags(FAssetRegistryTagsContext Context) const override;` — Extend the default ULevelSequence asset registry tags
- L154 _public function_ `virtual void ExtendAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L156 _public prototype_ `virtual void ExtendAssetRegistryTagMetaData(TMap<FName, FAssetRegistryTagMetadata>& OutMetadata) const override;`
- L165 _public prototype_ `float GetFocalLength() const;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — @return The focal length for this clip
- L172 _public prototype_ `bool GetSelected() const;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — @return Whether or not the clip is selected.
- L179 _public prototype_ `FString GetRecordedLevelName() const;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — @return The name of the clip's recorded level.
- L186 _public prototype_ `int GetFrameCountStart() const;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — @return The initial frame of the clip
- L193 _public prototype_ `int GetFrameCountEnd() const;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — @return The final frame of the clip
- L200 _public prototype_ `int GetLengthInFrames();` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — @return The length in frames of the clip.
- L207 _public prototype_ `FFrameRate GetDisplayRate();` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — @return The display rate of the clip.
- L214 _public prototype_ `bool GetIsACineCameraRecording() const;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — @return Whether the clip was recorded by a CineCameraActor
- L217 _public prototype_ `bool GetIsNoGood() const;` — `UE_DEPRECATED(5.6, "Use ULevelSequenceShotMetaDataLibrary::GetIsNoGood or UVCamTakesMetaDataMigration instead")`
- L219 _public prototype_ `bool GetIsFlagged() const;` — `UE_DEPRECATED(5.6, "Use ULevelSequenceShotMetaDataLibrary::GetIsFlagged or UVCamTakesMetaDataMigration instead")`
- L221 _public prototype_ `int32 GetFavoriteLevel() const;` — `UE_DEPRECATED(5.6, "Use ULevelSequenceShotMetaDataLibrary::GetFavoriteRank or UVCamTakesMetaDataMigration instead")`
- L230 _public prototype_ `void SetFocalLength(float InFocalLength);` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — Set the focal length associated with this clip. @note: Used for tracking. Does not update the StreamedCameraComponent.
- L237 _public prototype_ `void SetSelected(bool bInSelected);` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — Set if this clip is 'selected'
- L244 _public prototype_ `void SetRecordedLevelName(FString InLevelName);` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — Set the name of the level that the clip was recorded in.
- L251 _public prototype_ `void SetFrameCountStart(int InFrame);` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — Set the initial frame of the clip used for calculating duration.
- L258 _public prototype_ `void SetFrameCountEnd(int InFrame);` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — Set the final frame of the clip used for calculating duration.
- L265 _public prototype_ `void SetLengthInFrames(int InLength);` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — Set the length in frames of the clip used for AssetData calculations.
- L272 _public prototype_ `void SetDisplayRate(FFrameRate InDisplayRate);` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — Set the DisplayRate of the clip used for AssetData calculations.
- L279 _public prototype_ `void SetIsACineCameraRecording(bool bInIsACineCameraRecording);` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UFUNCTION(BlueprintCallable, Category = "Clips", meta=(DeprecatedFunction, DeprecationMessage="Data was removed."))` — Set if the clip was recorded by a CineCameraActor
- L287 _private member_ `float FocalLength = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Clips", BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DeprecatedProperty, DeprecationMessage = "Data was removed."))` — The focal length of the streamed camera used to record the take
- L292 _private member_ `bool bIsSelected = false;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UPROPERTY(EditAnywhere, Category = "Clips", BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DeprecatedProperty, DeprecationMessage = "Data was removed."))` — Whether or not the take was marked as 'selected'
- L297 _private member_ `FString RecordedLevelName;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UPROPERTY(EditAnywhere, Category = "Clips", BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DeprecatedProperty, DeprecationMessage = "Data was removed."))` — The name of the level that the clip was recorded in
- L302 _private member_ `int FrameCountStart = 0;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UPROPERTY(EditAnywhere, Category = "Clips", BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DeprecatedProperty, DeprecationMessage = "Data was removed."))` — The initial frame of the clip used for calculating duration.
- L307 _private member_ `int FrameCountEnd = 0;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UPROPERTY(EditAnywhere, Category = "Clips", BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DeprecatedProperty, DeprecationMessage = "Data was removed."))` — The last frame of the clip used for calculating duration.
- L312 _private member_ `int LengthInFrames = 0;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UPROPERTY(EditAnywhere, Category = "Clips", BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DeprecatedProperty, DeprecationMessage = "Data was removed."))` — The level sequence length in frames calculated from VirtualCameraSubsystem used for AssetData calculations
- L317 _private member_ `FFrameRate DisplayRate;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UPROPERTY(EditAnywhere, Category = "Clips", BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DeprecatedProperty, DeprecationMessage = "Data was removed."))` — The display rate of the level sequence used for AssetData calculations.
- L322 _private member_ `bool bIsACineCameraRecording = false;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UPROPERTY(EditAnywhere, Category = "Clips", BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DeprecatedProperty, DeprecationMessage = "Data was removed."))` — If the LevelSequence was recorded with a CineCameraActor, rather than a VirtualCameraActor
- L327 _private member_ `bool bIsNoGood = false;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UPROPERTY(EditAnywhere, Category = "Clips", BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DeprecatedProperty, DeprecationMessage = "Use ULevelSequenceShotMetaDataLibrary or UVCamTakesMetaDataMigration instead"))` — Whether this take is marked as good
- L332 _private member_ `bool bIsFlagged = false;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UPROPERTY(EditAnywhere, Category = "Clips", BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DeprecatedProperty, DeprecationMessage = "Use ULevelSequenceShotMetaDataLibrary or UVCamTakesMetaDataMigration instead"))` — The asset registry tag that contains whether this was flagged by a user
- L337 _private member_ `int32 FavoriteLevel = 0;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UPROPERTY(EditAnywhere, Category = "Clips", BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DeprecatedProperty, DeprecationMessage = "Use ULevelSequenceShotMetaDataLibrary or UVCamTakesMetaDataMigration instead"))` — The asset registry tag that contains its favorite status
- L342 _private member_ `bool bIsCreatedFromVCam = true;` — `UE_DEPRECATED(5.6, "Data was removed.")` — `UPROPERTY(EditAnywhere, Category = "Clips", BlueprintReadWrite, meta = (AllowPrivateAccess = "true", DeprecatedProperty, DeprecationMessage = "Data was removed."))` — Whether the sequence was created from a VCam
- L347 _private member_ `int32 PostSmoothLevel = 0;` — `UPROPERTY(EditAnywhere, Category = "Clips", BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))` — The asset registry tag that contains the post smooth level

### `Plugins/VirtualProduction/VirtualCamera/Source/VirtualCamera/Public/VCamUserSettings.h` (Public)


#### enum `EVCamTutorialCompletionState`  
`enum class EVCamTutorialCompletionState : uint8`  
_L10-16_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `Pending` — Tutorial not completed
- L15 _public enumerator_ `Completed` — Tutorial was completed

#### enum `EVCamPhotoSaveMode`  
`enum class EVCamPhotoSaveMode : uint8`  
_L19-25_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `Off`
- L22 _public enumerator_ `PNG`
- L23 _public enumerator_ `Texture`
- L24 _public enumerator_ `Both`

#### class `UVirtualCameraUserSettings`  
`class UVirtualCameraUserSettings : public UObject`  
_L28-73_
- reflection: `UCLASS(BlueprintType, Config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L35 _public function_ `static UVirtualCameraUserSettings* GetSettings()` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera", meta = (Keywords = "Get Settings Virtual Camera VCam"))`
- L37 _public prototype_ `UVirtualCameraUserSettings();`
- L45 _public member_ `EVCamTutorialCompletionState VCamTutorialCompletionState = EVCamTutorialCompletionState::Pending;` — `UPROPERTY(Config, BlueprintReadWrite, EditAnywhere, BlueprintSetter = "SetTutorialCompletionState", Category = "Virtual Camera")` — Indicates whether the VCam tutorial is completed. You can manually reset this to Pending if you want to retake the tutorial. The tutorial shown in the default VCamHUD, e.g. to teach gestures.
- L49 _public function_ `bool IsTutorialCompleted() const` — `UFUNCTION(BlueprintPure, Category = "Virtual Camera")` — @return Whether the VCam tutorial has been completed.
- L53 _public function_ `void SetTutorialCompletionState(EVCamTutorialCompletionState NewState)` — `UFUNCTION(BlueprintCallable, Category = "Virtual Camera")` — Sets the tutorial completion state and saves it to the config file if it has changed.
- L64 _public member_ `EVCamPhotoSaveMode PhotoSaveMode;` — `UPROPERTY(Config, BlueprintReadWrite, EditAnywhere, Category = "VCam Photo")` — VCam photo save mode
- L68 _public member_ `FDirectoryPath PhotoSaveLocation;` — `UPROPERTY(Config, BlueprintReadWrite, EditAnywhere, Category = "VCam Photo", meta = (EditCondition="PhotoSaveMode==EVCamPhotoSaveMode::PNG || PhotoSaveMode==EVCamPhotoSaveMode::Both"))` — Directory path to store vcam photos
- L72 _public member_ `FDirectoryPath TextureSaveLocation;` — `UPROPERTY(Config, BlueprintReadWrite, EditAnywhere, Category = "VCam Photo", meta = (ContentDir, EditCondition="PhotoSaveMode==EVCamPhotoSaveMode::Texture || PhotoSaveMode==EVCamPhotoSaveMode::Both"))` — Directory path to store vcam photo texture assets
