# Plugins / TakesCore

- module root: `Plugins/VirtualProduction/Takes/Source/TakesCore`
- headers: 16; symbols: 388
- symbol kinds: class=14, delegate=12, enum=2, enumerator=11, function=64, macro=8, member=94, namespace=9, prototype=165, struct=8, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, NamingTokens, TakeMovieScene, UnrealEd
- PublicDependencyModuleNames: AssetRegistry, Engine, LevelSequence, LevelSequenceEditor, MovieScene, MovieSceneTools, MovieSceneTracks, SerializedRecorderInterface, SlateCore
- PublicIncludePathModuleNames: TakeRecorderNamingTokens, TakeTrackRecorders

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Private/TakeData.h` (Private)


#### class `FTakesCoreTakeData`  
`class FTakesCoreTakeData : public IMovieSceneToolsTakeData`  
_L21-132_
- inherits: `IMovieSceneToolsTakeData`
- L24 _public prototype_ `virtual ~FTakesCoreTakeData() = default;`
- L26 _public function_ `virtual bool GatherTakes(const UMovieSceneSection* Section, TArray<FAssetData>& AssetData, uint32& OutCurrentTakeNumber)`
- L63 _public function_ `virtual bool GetTakeNumber(const UMovieSceneSection* Section, FAssetData AssetData, uint32& OutTakeNumber)`
- L102 _public function_ `virtual bool SetTakeNumber(const UMovieSceneSection* Section, uint32 InTakeNumber)`

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Private/TakeRecorderSourcesManagerImpl.h` (Private)


#### class `UTakeRecorderSourcesManagerImpl`  
`class UTakeRecorderSourcesManagerImpl final : public UEngineSubsystem, public ITakeRecorderSourcesManager`  
_L19-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem,ITakeRecorderSourcesManager`
- desc: Implementation of the ITakeRecorderSourcesManager interface, implemented as an Engine subsystem. Handles Take Recorder Sources in both editor and runtime contexts. At editor time, the LevelSequence metadata is used to track and store the Take Recorder sources. At runtime, a transient map is used to store the sources per level sequence. This is designed to be transient and unserialized due to requirements of recording at runtime, and setups most likely be game based.
- L27 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L28 _public prototype_ `virtual void Deinitialize() override;`
- L32 _public prototype_ `virtual UTakeRecorderSources* CopySources(ULevelSequence* FromSequence, ULevelSequence* ToSequence) override;`
- L33 _public prototype_ `virtual UTakeRecorderSources* CopySources(UTakeRecorderSources* InSources, ULevelSequence* ToSequence) override;`
- L34 _public prototype_ `virtual UTakeRecorderSources* FindSources(const ULevelSequence* InSequence) const override;`
- L35 _public prototype_ `virtual UTakeRecorderSources* FindOrAddSources(ULevelSequence* InSequence) override;`
- L36 _public prototype_ `virtual bool HasSources(const ULevelSequence* InSequence) const override;`
- L37 _public prototype_ `virtual UTakeRecorderSource* AddSource(ULevelSequence* InSequence, const TSubclassOf<UTakeRecorderSource> InSourceClass) override;`
- L38 _public prototype_ `virtual void RemoveSource(ULevelSequence* InSequence, UTakeRecorderSource* InSource) override;`
- L39 _public prototype_ `virtual void RemoveSources(ULevelSequence* InSequence) override;`
- L49 _private member_ `TMap<TObjectPtr<ULevelSequence>, TObjectPtr<UTakeRecorderSources>> RuntimeSources;` — `UPROPERTY(Transient)` — Sources map used at runtime to store the TakeRecorderSources per LevelSequence. This map can be transient as we have no intention of ever serializing it. It is used only at runtime for adding sources to record, and does not need to be persisted out.

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/ActorSequenceInformation.h` (Public)


#### class `UE::TakesCore::FActorSequenceInformation`  
`class FActorSequenceInformation`  
_L21-81_
- desc: Resolves and caches an actor's relationship to a level sequence hierarchy at construction time. Determines whether the actor is bound as a possessable or spawnable, and which sequence and sequence ID owns that binding.
- L24 _public prototype_ `FActorSequenceInformation() = delete;`
- L27 _public prototype_ `explicit FActorSequenceInformation(ULevelSequence* InLevelSequence, AActor* InActor);` — Resolves binding information for InActor within InLevelSequence, acquiring a shared playback state automatically.
- L30 _public prototype_ `explicit FActorSequenceInformation(ULevelSequence* InLevelSequence, AActor* InActor, TSharedPtr<const UE::MovieScene::FSharedPlaybackState> InSharedPlaybackState);` — Resolves binding information for InActor within InLevelSequence using the provided shared playback state.
- L33 _public function_ `const FGuid& GetCachedObjectBindingGuid() const` — Returns the binding GUID resolved at construction. Invalid if no binding was found.
- L36 _public function_ `bool IsControlledBySequence() const` — Returns true if the actor has an active binding in the sequence hierarchy (spawnable or tracked possessable).
- L39 _public function_ `const FMovieSceneSequenceID& GetControllingSequenceID() const` — Returns the FMovieSceneSequenceID of the sequence that owns the binding.
- L42 _public function_ `TWeakObjectPtr<UMovieSceneSequence> GetControllingSequence() const` — Returns the sequence that directly owns the actor's binding.
- L45 _public function_ `bool IsPossessable() const` — Returns true if the actor is bound as a possessable with existing track data.
- L48 _public function_ `bool IsSpawnable() const` — Returns true if the actor is bound as a Sequencer-managed spawnable.
- L51 _public function_ `AActor* GetTargetActor() const` — Returns the actor passed at construction.
- L54 _public function_ `ULevelSequence* GetTargetLevelSequence() const` — Returns the root level sequence passed at construction.
- L58 _private prototype_ `void Init();` — Drives the resolution pipeline: tries the root sequence, then compiled sub-sequence data.
- L61 _private prototype_ `void InitFromCompiledData(ULevelSequence* InLevelSequence, AActor* InActor);` — Searches sub-sequences in the compiled hierarchy when the root sequence yields no binding.
- L64 _private prototype_ `bool ResolveBindingFromSequence(AActor* InActor, ULevelSequence* InLevelSequence);` — Attempts to resolve the actor's binding GUID from InLevelSequence. Returns true on success.
- L67 _private prototype_ `bool IsPossessableBinding(ULevelSequence* InLevelSequence, const FGuid& InBindingGuid) const;` — Returns true if InBindingGuid is a possessable with existing track data (not a spawnable custom binding).
- L70 _private prototype_ `bool TryFindSequenceID(ULevelSequence* ForSequence);` — Resolves SequenceID for ForSequence via playback state or compiled hierarchy. Returns true on success.
- L72 _private member_ `TWeakObjectPtr<AActor> WeakTargetActor;`
- L73 _private member_ `TWeakObjectPtr<ULevelSequence> WeakTargetLevelSequence;`
- L75 _private member_ `bool bIsControlledBySequence = false;`
- L76 _private member_ `bool bIsPossessable = false;`
- L77 _private member_ `FGuid CachedObjectBindingGuid;`
- L78 _private member_ `FMovieSceneSequenceID SequenceID;`
- L79 _private member_ `TWeakObjectPtr<UMovieSceneSequence> WeakControllingSequence;`
- L80 _private member_ `TWeakPtr<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TAKESCORE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace TakesCore` (scope `UE`)

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/ITakeRecorderSourcesManager.h` (Public)


#### class `UTakeRecorderSourcesManager`  
`class UTakeRecorderSourcesManager : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintable)`
- inherits: `UInterface`

#### class `ITakeRecorderSourcesManager`  
`class ITakeRecorderSourcesManager`  
_L27-117_
- desc: Interface for the public Take Recorder Sources manager interface. This interface allows callers to work with Take Recorder Sources uniformly at editor and runtime, with the implementation handling the differences between the two environments. At editor time, the LevelSequence metadata is used to store and track sources as is the traditional behaviour. At runtime, the sources should be stored per level sequence editor separate from the sequence, as metadata is unavailable in runtime.
- L33 _public prototype_ `static ITakeRecorderSourcesManager* Get();` — Returns a pointer to the global ITakeRecorderSourcesManager implementation, or nullptr if not available.
- L39 _public prototype_ `static ITakeRecorderSourcesManager& GetChecked();` — Returns a reference to the global ITakeRecorderSourcesManager implementation. Asserts if no implementation is available.
- L48 _public prototype_ `virtual UTakeRecorderSources* CopySources(ULevelSequence* FromSequence, ULevelSequence* ToSequence) = 0;` — Copies all recorder sources from one level sequence to another. @param FromSequence  The sequence to copy sources from. @param ToSequence    The sequence to copy sources to. @return Pointer to the newly copied Sources object, or nullptr if sources were not found in FromSequence, or nothing was copied.
- L57 _public prototype_ `virtual UTakeRecorderSources* CopySources(UTakeRecorderSources* InSources, ULevelSequence* ToSequence) = 0;` — Copies the given sources onto the given sequence. This will replace any sources already on ToSequence. @param InSources     The sources to copy. @param ToSequence    The sequence to copy sources to. @return Pointer to the newly copied Sources object, or nullptr if nothing was copied.
- L64 _public prototype_ `virtual UTakeRecorderSources* FindSources(const ULevelSequence* InSequence) const = 0;` — Returns the UTakeRecorderSources associated with the given level sequence, or nullptr if none exist. @param InSequence  The sequence to look up.
- L72 _public prototype_ `virtual UTakeRecorderSources* FindOrAddSources(ULevelSequence* InSequence) = 0;` — Returns the UTakeRecorderSources associated with the given level sequence, creating and associating a new instance if one does not already exist. @param InSequence  The sequence to look up or create sources for.
- L79 _public prototype_ `virtual bool HasSources(const ULevelSequence* InSequence) const = 0;` — Returns true if a UTakeRecorderSources object is currently associated with the given level sequence. @param InSequence  The sequence to check.
- L88 _public function_ `template <typename TSource> UTakeRecorderSource* AddSource(ULevelSequence* InSequence)` — Convenience wrapper that adds a new recorder source of type TSource to the given level sequence. @param InSequence  The sequence to add the source to. @return The newly created UTakeRecorderSource, or nullptr on failure.
- L100 _public prototype_ `virtual UTakeRecorderSource* AddSource(ULevelSequence* InSequence, const TSubclassOf<UTakeRecorderSource> InSourceClass) = 0;` — Adds a new recorder source of the specified class to the given level sequence. @param InSequence     The sequence to add the source to. @param InSourceClass  The class of source to create and add. @return The newly created UTakeRecorderSource, or nullptr on failure.
- L108 _public prototype_ `virtual void RemoveSource(ULevelSequence* InSequence, UTakeRecorderSource* InSource) = 0;` — Removes a recorder source from the given level sequence's source list. @param InSequence  The sequence whose source list to modify. @param InSource    The source to remove.
- L116 _public prototype_ `virtual void RemoveSources(ULevelSequence* InSequence) = 0;` — Removes the UTakeRecorderSources association for the given level sequence. Callers are responsible for invoking this when a sequence is no longer needed. @param InSequence  The sequence whose sources entry should be removed.

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/NamingTokens/TakeRecorderNamingTokensContext.h` (Public)


#### class `UTakeRecorderNamingTokensContext`  
`class UTakeRecorderNamingTokensContext : public UObject`  
_L19-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Context object which may be passed to NamingTokens evaluations from within TakeRecorder. This is stored under TakesCore rather than the TakeRecorderNamingTokensModule for dependency management. Multiple Take modules need access to the context but don't need access to the NamingTokens themselves and would result in circular referencing.
- L26 _public member_ `TWeakObjectPtr<const UTakeMetaData> TakeMetaData;` — `UPROPERTY(Transient)` — MetaData specifically for this context. Setting this prevents having to perform a global lookup.
- L30 _public member_ `TWeakObjectPtr<const AActor> Actor;` — `UPROPERTY(Transient)` — The specific actor for this context. @todo NamingTokens - Determine if we should be retrieving the {actor} a different way.
- L34 _public member_ `int32 AudioInputDeviceChannel = 0;` — `UPROPERTY(Transient)` — The audio device channel for this context. @todo NamingTokens - Determine if we should be retrieving the {channel} a different way.

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/TakeMetaData.h` (Public)


#### class `UTakeMetaData`  
`class UTakeMetaData : public UObject, public IMovieSceneMetaDataInterface`  
_L23-344_
- reflection: `UCLASS(MinimalAPI, config=EditorSettings, PerObjectConfig, BlueprintType)`
- inherits: `UObject,IMovieSceneMetaDataInterface`
- desc: Take meta-data that is stored on ULevelSequence assets that are recorded through the Take Recorder. Meta-data is retrieved through ULevelSequence::FindMetaData<UTakeMetaData>()
- L28 _public prototype_ `UTakeMetaData(const FObjectInitializer& ObjInit);`
- L33 _public member_ `static const FName AssetRegistryTag_Slate;` — The asset registry tag that contains the slate for this meta-data
- L36 _public member_ `static const FName AssetRegistryTag_TakeNumber;` — The asset registry tag that contains the take number for this meta-data
- L39 _public member_ `static const FName AssetRegistryTag_Timestamp;` — The asset registry tag that contains the timestamp for this meta-data
- L42 _public member_ `static const FName AssetRegistryTag_TimecodeIn;` — The asset registry tag that contains the timecode in for this meta-data
- L45 _public member_ `static const FName AssetRegistryTag_TimecodeOut;` — The asset registry tag that contains the timecode out for this meta-data
- L48 _public member_ `static const FName AssetRegistryTag_Description;` — The asset registry tag that contains the user-description for this meta-data
- L51 _public member_ `static const FName AssetRegistryTag_LevelPath;` — The asset registry tag that contains the level-path for this meta-data
- L56 _public prototype_ `static UTakeMetaData* GetConfigInstance();` — Access the global config instance that houses default settings for take meta data for a given project
- L64 _public prototype_ `static UTakeMetaData* CreateFromDefaults(UObject* Outer, FName Name);` — Create a new meta-data object from the project defaults @param Outer    The object to allocate the new meta-data within @param Name     The name for the new object. Must not already exist
- L69 _public prototype_ `static UTakeMetaData* GetMostRecentMetaData();` — Retrieve the most recent or active take metadata.
- L74 _public prototype_ `static void SetMostRecentMetaData(UTakeMetaData* InMetaData);` — Update the most recent accessed metadata.
- L81 _public prototype_ `virtual void ExtendAssetRegistryTags(FAssetRegistryTagsContext Context) const override;` — Extend the default ULevelSequence asset registry tags
- L83 _public function_ `virtual void ExtendAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L89 _public prototype_ `virtual void ExtendAssetRegistryTagMetaData(TMap<FName, FAssetRegistryTagMetadata>& OutMetadata) const override;` — Extend the default ULevelSequence asset registry tag meta-data
- L98 _public prototype_ `bool IsLocked() const;` — `UFUNCTION(BlueprintCallable, Category="Take")` — Check whether this take is locked
- L105 _public prototype_ `bool Recorded() const;` — `UFUNCTION(BlueprintCallable, Category="Take")` — Check if this take was recorded (as opposed to being setup for recording)
- L111 _public prototype_ `const FString& GetSlate() const;` — `UFUNCTION(BlueprintCallable, Category="Take")` — @return The slate for this take
- L117 _public prototype_ `int32 GetTakeNumber() const;` — `UFUNCTION(BlueprintCallable, Category="Take")` — @return The take number for this take
- L123 _public prototype_ `FDateTime GetTimestamp() const;` — `UFUNCTION(BlueprintCallable, Category="Take")` — @return The timestamp for this take
- L129 _public prototype_ `FTimecode GetTimecodeIn() const;` — `UFUNCTION(BlueprintCallable, Category = "Take")` — @return The timecode in for this take
- L135 _public prototype_ `FTimecode GetTimecodeOut() const;` — `UFUNCTION(BlueprintCallable, Category = "Take")` — @return The timecode out for this take
- L141 _public prototype_ `FFrameTime GetDuration() const;` — `UFUNCTION(BlueprintCallable, Category="Take")` — @return The duration for this take
- L147 _public prototype_ `FFrameRate GetFrameRate();` — `UFUNCTION(BlueprintCallable, Category="Take")` — @return The frame-rate for this take
- L153 _public prototype_ `FString GetDescription() const;` — `UFUNCTION(BlueprintCallable, Category="Take")` — @return The user-provided description for this take
- L159 _public prototype_ `UTakePreset* GetPresetOrigin() const;` — `UFUNCTION(BlueprintCallable, Category="Take")` — @return The preset on which the take was originally based
- L165 _public prototype_ `FString GetLevelPath() const;` — `UFUNCTION(BlueprintCallable, Category="Take")` — @return The AssetPath of the Level used to create a Recorded Level Sequence
- L171 _public prototype_ `ULevel* GetLevelOrigin() const;` — `UFUNCTION(BlueprintCallable, Category="Take")` — @return The Map used to create this recording
- L177 _public prototype_ `bool GetFrameRateFromTimecode() const;` — `UFUNCTION(BlueprintCallable, Category = "Take")` — @return Get if we get frame rate from time code
- L185 _public prototype_ `void Lock();` — `UFUNCTION(BlueprintCallable, Category="Take")` — Lock this take, causing it to become read-only
- L191 _public prototype_ `void Unlock();` — `UFUNCTION(BlueprintCallable, Category="Take")` — Unlock this take if it is read-only, allowing it to be modified once again
- L197 _public prototype_ `FString GenerateAssetPath(const FString& PathFormatString, UTakeRecorderNamingTokensContext* InContext = nullptr) const;` — `UFUNCTION(BlueprintCallable, Category="Take")` — Generate the desired asset path for this take meta-data
- L203 _public prototype_ `bool TryGenerateRootAssetPath(const FString& PathFormatString, FString& OutGeneratedAssetPath, FText* OutErrorMessage = nullptr, UTakeRecorderNamingTokensContext* InContext = nullptr) const;` — Attempt to generate the root asset path. @return true if successful, false if the path couldn't be generated.
- L206 _public prototype_ `FNamingTokenResultData ProcessTokens(const FText& InText, UTakeRecorderNamingTokensContext* InContext = nullptr) const;` — Process TakeRecorder Naming Tokens.
- L214 _public prototype_ `void SetSlate(FString InSlate, bool bEmitChanged = true);` — `UFUNCTION(BlueprintCallable, Category="Take")` — Set the slate for this take and reset its take number to 1 @param bEmitChanged Whether or not to send a slate changed event @note: Only valid for takes that have not been locked
- L222 _public prototype_ `void SetTakeNumber(int32 InTakeNumber, bool bEmitChanged = true);` — `UFUNCTION(BlueprintCallable, Category="Take")` — Set this take's take number. Take numbers are always clamped to be >= 1. @param bEmitChanged Whether or not to send a take number changed event @note: Only valid for takes that have not been locked
- L229 _public prototype_ `void SetTimestamp(FDateTime InTimestamp);` — `UFUNCTION(BlueprintCallable, Category="Take")` — Set this take's timestamp @note: Only valid for takes that have not been locked
- L236 _public prototype_ `void SetTimecodeIn(FTimecode InTimecodeIn);` — `UFUNCTION(BlueprintCallable, Category = "Take")` — Set this take's timecode in @note: Only valid for takes that have not been locked
- L243 _public prototype_ `void SetTimecodeOut(FTimecode InTimecodeOut);` — `UFUNCTION(BlueprintCallable, Category = "Take")` — Set this take's timecode out @note: Only valid for takes that have not been locked
- L250 _public prototype_ `void SetDuration(FFrameTime InDuration);` — `UFUNCTION(BlueprintCallable, Category="Take")` — Set this take's duration @note: Only valid for takes that have not been locked
- L257 _public prototype_ `void SetFrameRate(FFrameRate InFrameRate);` — `UFUNCTION(BlueprintCallable, Category="Take")` — Set this take's frame-rate @note: Only valid for takes that have not been locked
- L264 _public prototype_ `void SetDescription(FString InDescription);` — `UFUNCTION(BlueprintCallable, Category="Take")` — Set this take's user-provided description @note: Only valid for takes that have not been locked
- L271 _public prototype_ `void SetPresetOrigin(UTakePreset* InPresetOrigin);` — `UFUNCTION(BlueprintCallable, Category="Take")` — Set the preset on which the take is based @note: Only valid for takes that have not been locked
- L277 _public prototype_ `void SetLevelOrigin(ULevel* InLevelOrigin);` — `UFUNCTION(BlueprintCallable, Category="Take")` — Set the map used to create this recording
- L283 _public prototype_ `void SetFrameRateFromTimecode(bool InFromTimecode);` — `UFUNCTION(BlueprintCallable, Category = "Take")` — Set if we get frame rate from time code
- L285 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTakeSlateChanged, const FString& SlateName, UTakeMetaData* TakeMetaData);`
- L287 _public prototype_ `static FOnTakeSlateChanged& OnTakeSlateChanged();` — Multicast delegate emitted when the slate is changed.
- L289 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTakeNumberChanged, int32 TakeNumber, UTakeMetaData* TakeMetaData);`
- L291 _public prototype_ `static FOnTakeNumberChanged& OnTakeNumberChanged();` — Multicast delegate emitted when take number is changed.
- L297 _private member_ `bool bIsLocked;` — `UPROPERTY()` — Whether the take is locked
- L301 _private member_ `FString Slate;` — `UPROPERTY(config)` — The user-provided slate information for the take
- L305 _private member_ `int32 TakeNumber;` — `UPROPERTY()` — The take number
- L309 _private member_ `FDateTime Timestamp;` — `UPROPERTY()` — The timestamp at which the take was initiated
- L313 _private member_ `FTimecode TimecodeIn;` — `UPROPERTY()` — The timecode at the start of recording
- L317 _private member_ `FTimecode TimecodeOut;` — `UPROPERTY()` — The timecode at the end of recording
- L321 _private member_ `FFrameTime Duration;` — `UPROPERTY(config)` — The desired duration for the take
- L325 _private member_ `FFrameRate FrameRate = FFrameRate(60, 1);` — `UPROPERTY()` — The frame rate the take was recorded at. We default to 60fps.
- L329 _private member_ `FString Description;` — `UPROPERTY(config)` — A user-provided description for the take
- L333 _private member_ `TSoftObjectPtr<UTakePreset> PresetOrigin;` — `UPROPERTY(config)` — The preset that the take was based off
- L338 _private member_ `TSoftObjectPtr<ULevel> LevelOrigin;` — `UPROPERTY()` — The level map used to create this recording
- L343 _private member_ `bool bFrameRateFromTimecode;` — `UPROPERTY()` — Whether or not we get or frame rate from Timecode, default to true

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TAKESCORE_API`
- L285 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTakeSlateChanged, const FString& SlateName, UTakeMetaData* TakeMetaData);`
- L289 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTakeNumberChanged, int32 TakeNumber, UTakeMetaData* TakeMetaData);`

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/TakePreset.h` (Public)


#### class `UTakePreset`  
`class UTakePreset : public UObject`  
_L16-85_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: Take preset that is stored as an asset comprising a ULevelSequence, and a set of actor recording sources
- L22 _public prototype_ `UTakePreset(const FObjectInitializer& ObjInit);`
- L27 _public function_ `ULevelSequence* GetLevelSequence() const` — Get this preset's level sequence that is used as a template for a new take recording
- L35 _public prototype_ `ULevelSequence* GetOrCreateLevelSequence();` — Retrieve this preset's level sequence template, creating one if necessary
- L40 _public prototype_ `void CreateLevelSequence();` — Forcibly re-create this preset's level sequence template, even if one already exists
- L45 _public prototype_ `void CopyFrom(UTakePreset* TemplatePreset);` — Copy the specified template preset into this instance. Copies the level sequence and all its recording meta-data.
- L50 _public prototype_ `void CopyFrom(ULevelSequence* TemplateLevelSequence);` — Copy the specified level-sequence into this instance. Copies the level sequence and all its recording meta-data.
- L55 _public prototype_ `FDelegateHandle AddOnLevelSequenceChanged(const FSimpleDelegate& InHandler);` — Bind onto an event that is triggered when this preset's level sequence has been changed
- L60 _public prototype_ `void RemoveOnLevelSequenceChanged(FDelegateHandle DelegateHandle);` — Remove a previously bound handler for the  event that is triggered when this preset's level sequence has been changed
- L65 _public prototype_ `static UTakePreset* AllocateTransientPreset(UTakePreset* TemplatePreset);` — Allocate the transient preset used by the take recorder.
- L70 _public prototype_ `static FSimpleMulticastDelegate& OnTakePresetAllocated();` — Static multicast delegate fired by AllocateTransientPreset when it creates a new transient pending take.
- L75 _private prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L80 _private member_ `TObjectPtr<ULevelSequence> LevelSequence;` — `UPROPERTY(Instanced)` — Instanced level sequence template that is used to define a starting point for a new take recording
- L82 _private member_ `FSimpleMulticastDelegate OnLevelSequenceChangedEvent;`
- L84 _private member_ `static FSimpleMulticastDelegate OnTakePresetAllocatedDelegate;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API TAKESCORE_API`

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/TakePresetSettings.h` (Public)


#### struct `FTakeRecorderTargetRecordClassProperty`  
`struct FTakeRecorderTargetRecordClassProperty`  
_L15-21_
- reflection: `USTRUCT()`
- desc: Wraps the class so this can be customized by a type layout.
- L20 _public member_ `TSoftClassPtr<ULevelSequence> TargetRecordClass;` — `UPROPERTY(EditAnywhere, Category = "Take Recorder")`

#### class `UTakePresetSettings`  
`class UTakePresetSettings : public UObject`  
_L30-64_
- reflection: `UCLASS(MinimalAPI, config=EditorSettings, BlueprintType, DisplayName = "Take Recorder")`
- inherits: `UObject`
- desc: Settings for how to assemble UTakePreset. These settings belong into UTakeRecorderSettings but those are in TakeRecorder, which depends on TakesCore. DisplayName is important so these settings are displayed in the same category as UTakeRecorderSettings.
- L35 _public prototype_ `UTakePresetSettings();`
- L38 _public prototype_ `static UTakePresetSettings* Get();` — @return The settings object
- L41 _public prototype_ `UClass* GetTargetRecordClass() const;` — @return The class that recorded sequences should have
- L44 _public prototype_ `void SetTargetRecordClass(const TSoftClassPtr<ULevelSequence>& InClass);` — Sets the target record class
- L46 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSettingsChanged);`
- L48 _public function_ `FOnSettingsChanged& OnSettingsChanged()` — Invoked when any settings change.
- L50 _public function_ `static FName GetTargetRecordClassMemberName()`
- L53 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L60 _private member_ `FTakeRecorderTargetRecordClassProperty TargetRecordClass;` — `UPROPERTY(config, EditAnywhere, Category = "Take Recorder")` — The class that recorded sequences should have.
- L63 _private member_ `FOnSettingsChanged OnSettingsChangedDelegate;` — Invoked when any settings change.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TAKESCORE_API`
- L46 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSettingsChanged);`

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/TakeRecorderSource.h` (Public)


#### class `UTakeRecorderSource`  
`class UTakeRecorderSource : public UObject`  
_L31-266_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, BlueprintType)`
- inherits: `UObject`
- desc: Base class for all sources that can be recorded with the Take Recorder. Custom recording sources can be created by inheriting from this class and implementing the Start/Tick/Stop recording functions. The level sequence that the recording is being placed into is provided so that the take can decide to store the data directly in the resulting level sequence, but sources are not limited to generating data in the specified Level Sequence. The source should be registered with the ITakeRecorderModule for it to show up in the Take Recorder UI. If creating a recording setup via code you can just add instances of your Source to the UTakeRecorderSources instance you're using to record and skip registering them with the module. Sources should reset their state before recording as there is not a guarantee that the object will be newly created for each recording.
- L36 _public prototype_ `UTakeRecorderSource(const FObjectInitializer& ObjInit);`
- L40 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L46 _public member_ `bool bEnabled;` — `UPROPERTY(BlueprintReadWrite, Category="Source")` — True if this source is cued for recording or not
- L49 _public member_ `int32 TakeNumber;` — `UPROPERTY(BlueprintReadWrite, Category="Source")`
- L52 _public member_ `FColor TrackTint;` — `UPROPERTY(BlueprintReadWrite, Category="Source")`
- L60 _public function_ `virtual void Initialize()` — Gives the Source object an opportunity to perform additional initialization outside of the constructor. This can be necessary when needing to perform additional initialization that should not occur if/when the object is duplicated (as is the case when all sources are duplicated prior to each record pass).
- L66 _public function_ `virtual bool IsValid() const` — If the source is Valid and ready to be recorded. Tells the Take Recorder that it's really going to record. Note that PreRecord/StartRecord may still get called on the source even if not Valid. This is used mainly so we only Start Recording if we have more than one Valid Source.
- L87 _public prototype_ `virtual TArray<UTakeRecorderSource*> PreRecording(ULevelSequence* InSequence, FMovieSceneSequenceID InSequenceID, ULevelSequence* InRootSequence, FManifestSerializer* InManifestSerializer);` — This is called on all sources before recording is started. This allows a source to return a list of new sources that should be added to the recording. This is useful for abstract sources (such as "Player" or "World Settings") which are convenience wrappers for existing sources (such as a Actor Source). In these cases, these abstract sources simply do their logic to find out which new sources need to be made and then return them. These new sources only need to exist for the lifespan of a single UTakeRecorderSources recording. Do any computationally expensive work in this function (as opposed to StartRecording) so that all sources can have StartRecording called as closely as possible to each other. See StartRecording for more details. Will not be called if this recording source is not enabled. @param InSequence - The Level Sequence the take is being recorded into @param InSequenceID - The sequence ID for InSequence, or MovieSceneSequenceID::Root where InSequence == InRootSequence (ie, not sub-sequence recording) @param InRootSequence - The Root Level Sequence that may contain the InSequence as a child or if no subsequences, is the same as InSequence. @param InManifestSerializer - Manifest Serializer that we may write into. @return An array of newly created take recorder sources. Can be an empty list if no additional sources needed to be created by this source.
- L90 _public function_ `virtual void OnAllSourcesPreRecordingFinished()` — Called after all sources have had PreRecording run.
- L104 _public function_ `virtual void StartRecording(const FTimecode& InSectionStartTimecode, const FFrameNumber& InSectionFirstFrame, class ULevelSequence* InSequence)` — This is called when the UTakeRecorderSources starts a recording, after all sources have had PreRecording called on them. Implementations should avoid blocking on this call (instead place that in PreRecording) so that the sources all get StartRecording called on them as close to possible as one another. This is useful for any source that relies on platform time (or other time sources) so that a source does not spend a long time being initialized and causing different sources to record drastically different times. @param InSectionStartTimecode - The externally provided timecode at the time of this recording starting. @param InSectionFirstFrame - The first frame of the section in tick resolution @param InSequence - The Level Sequence the take is being recorded into.
- L115 _public function_ `virtual void TickRecording(const FQualifiedFrameTime& CurrentSequenceTime)` — This is called each frame and allows the source to record any new information from the current frame. Called after all actors in the level Tick. @param - CurrentSequenceTime - The frame of the Level Sequence for this frame that the data should be stored on. Passed as a qualified time to handle any differences in sub-sequence resolutions. Will not be called if this recording source is not enabled.
- L126 _public function_ `virtual void StopRecording(class ULevelSequence* InSequence)` — This is called when the UTakeRecorderSources stops recording. This is called on all sources after recording has finished. This should avoid being a blocking call (use PostRecording instead) so that all sources can be stopped as soon as possible after the user requests the recording end. See StartRecording for more details about why having all recordings start/stop as close as possible to each other is important. Will not be called if this recording source is not enabled.
- L138 _public function_ `virtual TArray<UTakeRecorderSource*> PostRecording(class ULevelSequence* InSequence, class ULevelSequence* InRootSequence, const bool bCancelled)` — This is called on all sources after recording is stopped. By returning the same list of additional sources as provided in PreRecording the source can clean up any additional temporary sources that were created by this recording. These additional temporary sources will be properly shut down so they have a chance to store their data before being removed from the list. Will not be called if this recording source is not enabled. @return An array of take recorder sources to be removed. Likely to match the same list as PreRecording. Can be an empty list if no additional sources are required by this source.
- L143 _public function_ `virtual void FinalizeRecording()` — This is called on all sources after post recording. There should not be any dependencies between sources at this point.
- L151 _public function_ `virtual TArray<UObject*> GetAdditionalSettingsObjects() const` — This allows a Source to return an array of dynamically spawned settings objects for that source. These will be shown in the UI as a separate category when the source is Selected. @return A an array of additional objects to be shown in the UI. Can be an empty list if no additional settings objects are needed.
- L156 _public function_ `virtual bool SupportsSubscenes() const` — Supports recording into subscenes
- L161 _public function_ `virtual FString GetSubsceneTrackName(ULevelSequence* InSequence) const` — When recorded to a Subscenes track, what should the subscene track name of the Section be?
- L166 _public function_ `virtual FString GetSubsceneAssetName(ULevelSequence* InSequence) const` — When recorded to a Subscenes track, what should the sub level sequence asset name be? By default, returns the name of the track
- L173 _public function_ `virtual void AddContentsToFolder(class UMovieSceneFolder* InFolder)` — If you are not recording into a sub-sequence then this will be called after PreRecording is called and will specify the folder that this Source should add itself to. This will not be called if you are recording into a sub-sequence as recorded data should be placed in the root of the sub-sequence in that case.
- L178 _public function_ `virtual bool ShouldCreateFolderForContents() const` — Optional function to allow sources to decide if they want to create folders for their contents or not.
- L184 _public function_ `virtual bool CanAddSource(UTakeRecorderSources* InSources) const` — Whether this source can be added (some sources should only exist once)
- L191 _public prototype_ `virtual bool OverwriteExistingTrackData() const;` — Whether this source should overwrite existing track data, or leave it, or potentially create new data. This is primarily used in response to Spawnables, such as we if we want to overwrite subsequence data or clear existing data in non-subsequence tracks.
- L197 _public function_ `virtual void PreRemove()` — Called by UTakeRecorderSources right before a Source is removed from its internal map. Allows for any cleanup or logic the Source needs to do when being removed.
- L204 _public function_ `FText GetCategoryText() const` — Get the optional category text to display on the Take Recorder source list for this source
- L212 _public function_ `FText GetDisplayText() const` — Get the text to display on the Take Recorder source list for this source
- L220 _public function_ `FText GetAddSourceDisplayText() const` — Get the text to display on the add source menu for this source
- L234 _public function_ `const FSlateBrush* GetDisplayIcon() const` — Get the icon to display on the Take Recorder source list for this source
- L242 _public function_ `FText GetDescriptionText() const` — A very brief text summary of what is going to be recorded for this source
- L250 _public function_ `virtual bool SupportsTakeNumber() const` — Whether or the source can be referenced via take number
- L253 _public function_ `virtual const class IMovieSceneTrackRecorderHost* AsTrackRecorderHost() const` — If this source implements the IMovieSceneTrackRecorderHost interface. This is used to avoid RTTI.
- L256 _public function_ `virtual bool IsActorSourceForActor(const AActor* Actor) const` — If this source is an actor source for the given actor. Used for cross-module communication.
- L261 _private prototype_ `virtual const FSlateBrush* GetDisplayIconImpl() const;` — Default implementations for UI functions
- L262 _private function_ `virtual FText GetCategoryTextImpl() const`
- L263 _private function_ `virtual FText GetDisplayTextImpl() const`
- L264 _private function_ `virtual FText GetDescriptionTextImpl() const`
- L265 _private function_ `virtual FText GetAddSourceDisplayTextImpl() const`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API TAKESCORE_API`

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/TakeRecorderSourceProperty.h` (Public)


#### struct `FActorRecordedProperty`  
`struct FActorRecordedProperty`  
_L12-38_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public function_ `FActorRecordedProperty() : PropertyName(NAME_None) , bEnabled(false) , RecorderName()`
- L23 _public function_ `FActorRecordedProperty(const FName& InName, const bool bInEnabled, const FText& InRecorderName)`
- L31 _public member_ `FName PropertyName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property")`
- L34 _public member_ `bool bEnabled;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Property")`
- L37 _public member_ `FText RecorderName;` — `UPROPERTY(VisibleAnywhere, Category = "Property")`

#### class `UActorRecorderPropertyMap`  
`class UActorRecorderPropertyMap : public UObject`  
_L47-100_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: This represents a list of all possible properties and components on an actor which can be recorded by the Actor Recorder and whether or not the user wishes to record them. If you wish to expose a property to be recorded it needs to be marked as "Interp" (C++) or "Expose to Cinematics" in Blueprints.
- L53 _public prototype_ `virtual void PostEditUndo() override;`
- L54 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L58 _public member_ `TSoftObjectPtr<UObject> RecordedObject;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Property")`
- L62 _public member_ `TArray<FActorRecordedProperty> Properties;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")` — Represents properties exposed to Cinematics that can possibly be recorded.
- L65 _public member_ `TArray<TObjectPtr<UActorRecorderPropertyMap>> Children;` — `UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, meta=(ShowInnerProperties, EditFixedOrder), Category = "Property")`
- L83 _public function_ `Cache CachedPropertyComponentCount() const` — Return the number of properties and components participating in recording.
- L89 _public prototype_ `void UpdateCachedValues();` — Visit all properties recursively and cache the record state.
- L91 _private prototype_ `int32 NumberOfPropertiesRecordedOnThis() const;`
- L92 _private prototype_ `int32 NumberOfComponentsRecordedOnThis() const;`
- L95 _private prototype_ `void ChildChanged();` — This is called by the children to let the parent know that the number of recorded properties has changed
- L97 _private member_ `TWeakObjectPtr<UActorRecorderPropertyMap> Parent;`
- L99 _private member_ `Cache RecordingInfo;`

#### struct `UActorRecorderPropertyMap::Cache`  
`struct Cache`  
_L68-80_
- L70 _public function_ `Cache& operator+=(const Cache& InOther)`
- L77 _public member_ `int32 Properties = 0;` — The number of properties (both on actor + components) that we are recording. This includes child maps.
- L79 _public member_ `int32 Components = 0;` — The number of components that belong to the target actor that we are recording. This include child maps.

#### struct `FAudioInputDeviceInfoProperty`  
`struct FAudioInputDeviceInfoProperty`  
_L106-140_
- reflection: `USTRUCT(BlueprintType)`
- desc: Encapsulates audio device properties which are utilized by UI facing classes such as FAudioInputDeviceProperty.
- L110 _public prototype_ `FAudioInputDeviceInfoProperty() = default;`
- L112 _public function_ `FAudioInputDeviceInfoProperty(const FString& InDeviceName, const FString& InDeviceId, int32 InChannelCount, int32 InSampleRate, bool bInIsDefaultDevice) : DeviceName(InDeviceName) , DeviceId(InDeviceId) , InputChannels(InChannelCount) , PreferredSampleRate(InSampleRate) , bIsDefaultDevice(bInIsDefaultDevice)`
- L123 _public member_ `FString DeviceName;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Property")` — User friendly name of the audio device
- L127 _public member_ `FString DeviceId;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Property")` — The unique id used to identify the device
- L131 _public member_ `int32 InputChannels = 0;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Property")` — The number input channels this device supports
- L135 _public member_ `int32 PreferredSampleRate = 0;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Property")` — The preferred sample rate for this audio device
- L139 _public member_ `bool bIsDefaultDevice = false;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Property")` — Boolean indicating if this device is the currently the system selected input device

#### struct `FAudioInputDeviceProperty`  
`struct FAudioInputDeviceProperty`  
_L147-169_
- reflection: `USTRUCT(BlueprintType)`
- desc: Encapsulates the array of audio input devices which is populated by UTakeRecorderMicrophoneAudioManager and utilized by the audio input device list in FAudioInputDevicePropertyCustomization.
- L152 _public member_ `constexpr static int32 MaxInputChannelCount = 8;` — The maximum number input channels currently supported
- L156 _public member_ `bool bUseSystemDefaultAudioDevice = true;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Property")` — Boolean indicating if the system selects audio device should be used or to use the selected device from the details panel
- L160 _public member_ `TArray<FAudioInputDeviceInfoProperty> DeviceInfoArray;` — `UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "Property")` — Holds device information for each of the audio devices available on this system.
- L164 _public member_ `FString DeviceId;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Property", meta = (DisplayName = "Audio Input Device"))` — The unique id of the currently selected audio device
- L168 _public member_ `int32 AudioInputBufferSize = 1024;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Property", meta = (ClampMin = "256", UIMin = "256", ClampMax = "8192", UIMax = "8192"))` — The desired buffer size used for audio callbacks during record

#### struct `FAudioInputDeviceChannelProperty`  
`struct FAudioInputDeviceChannelProperty`  
_L176-185_
- reflection: `USTRUCT(BlueprintType)`
- desc: This class is used by Microphone sources to track the currently selected channel. It aslo contains a local cache of the max channel count for the currently selected audio device.
- L184 _public member_ `int32 AudioInputDeviceChannel = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")` — The currently selected channel from the details panel for this source

#### class `UTakeRecorderAudioInputSettings`  
`class UTakeRecorderAudioInputSettings : public UObject`  
_L193-212_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, BlueprintType)`
- inherits: `UObject`
- desc: Provides access to the UI code for registering OnAudioInputDeviceChanged delegates.
- L200 _public function_ `virtual void EnumerateAudioDevices(bool InForceRefresh = false)` — Subclasses can override this to enumerate audio devices
- L203 _public function_ `virtual int32 GetDeviceChannelCount()` — Returns the channel count for the currently selected audio device
- L206 _public function_ `FOnAudioInputDeviceChanged& GetOnAudioInputDeviceChanged()` — Accessor for the OnAudioInputDeviceChanged delegate list
- L211 _private member_ `FOnAudioInputDeviceChanged OnAudioInputDeviceChanged;` — Multicast notification when the user selects a new audio device

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TAKESCORE_API`
- L187 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAudioInputDeviceChanged);`
- L187 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAudioInputDeviceChanged);`

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/TakeRecorderSources.h` (Public)


#### struct `FTakeRecorderSourcesSettings`  
`struct FTakeRecorderSourcesSettings`  
_L23-34_
- L25 _public member_ `bool bStartAtCurrentTimecode;`
- L26 _public member_ `bool bRecordSourcesIntoSubSequences;`
- L27 _public member_ `bool bRecordToPossessable;`
- L28 _public member_ `ETakeRecorderSpawnableOverwriteBehavior SpawnableOverwriteBehavior;`
- L29 _public member_ `bool bSaveRecordedAssets;`
- L30 _public member_ `bool bAutoLock;`
- L31 _public member_ `bool bRemoveRedundantTracks;`
- L32 _public member_ `FTransform TransformOrigin;`
- L33 _public member_ `FString SubSequenceDirectory;`

#### class `UTakeRecorderSources`  
`class UTakeRecorderSources : public UObject`  
_L54-318_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UObject`
- desc: A list of sources to record for any given take. Is stored and looked up against a level sequence using the ITakeRecorderSourcesManager. Note that within an editor environment, ITakeRecorderSourcesManager will store the sources object as meta-data on ULevelSequence through ULevelSequence::FindMetaData<UTakeRecorderSources>.
- L59 _public prototype_ `UTakeRecorderSources(const FObjectInitializer& ObjInit);`
- L67 _public function_ `template<typename SourceType> SourceType* AddSource()` — Add a new source to this source list of the templated type @return An instance of the templated type
- L80 _public prototype_ `UTakeRecorderSource* AddSource(TSubclassOf<UTakeRecorderSource> InSourceType);` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder", meta = (DeterminesOutputType = "InSourceType"))` — Add a new source to this source list of the templated type @param InSourceType    The class type of the source to add @return An instance of the specified source type
- L88 _public prototype_ `void RemoveSource(UTakeRecorderSource* InSource);` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder")` — Remove the specified source from this list @param InSource        The source to remove
- L94 _public function_ `TArrayView<UTakeRecorderSource* const> GetSources() const` — Access all the sources stored in this list
- L105 _public function_ `TArray<UTakeRecorderSource*> GetSourcesCopy() const` — `UFUNCTION(BlueprintPure, DisplayName = "Get Sources (Copy)", Category = "Take Recorder")` — Retrieves a copy of the list of sources that are being recorded. This is intended for Blueprint usages which cannot use TArrayView. DO NOT MODIFY THIS ARRAY, modifications will be lost.
- L113 _public function_ `uint32 GetSourcesSerialNumber() const` — Retrieve the serial number that is incremented when a source is added or removed from this list. @note: This field is not serialized, and not copied along with UObject duplication.
- L119 _public function_ `FTakeRecorderSourcesSettings GetSettings() const` — Sources settings from the user and project parameters
- L120 _public function_ `void SetSettings(FTakeRecorderSourcesSettings& InSettings)`
- L124 _public prototype_ `void StartRecordingSource(TArray<UTakeRecorderSource*> InSources, const FQualifiedFrameTime& CurrentFrameTime);` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder")` — Calls the recording initialization flows on each of the specified sources.
- L134 _public prototype_ `FDelegateHandle BindSourcesChanged(const FSimpleDelegate& Handler);` — Bind a callback for when this source list changes @param Handler         The delegate to call when the list changes @return A handle to this specific binding that should be passed to UnbindSourcesChanged
- L141 _public prototype_ `void UnbindSourcesChanged(FDelegateHandle Handle);` — Unbind a previously bound handler for when this source list changes @param Handle          The handle returned from BindSourcesChanged for the handler to remove
- L143 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSourceAdded, UTakeRecorderSource* Source);`
- L144 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSourceRemoved, UTakeRecorderSource* Source);`
- L145 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSourceModified, UTakeRecorderSource* Source);`
- L148 _public prototype_ `static FOnSourceAdded& OnSourceAdded();` — Multicast delegate for when any source is added.
- L151 _public prototype_ `static FOnSourceRemoved& OnSourceRemoved();` — Multicast delegate for when any source is removed.
- L154 _public prototype_ `static FOnSourceModified& OnSourceModified();` — Multicast delegate for when any source is modified.
- L159 _private prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(UTakeRecorderSource*, FOnActorBindingAdded, AActor*, ULevelSequence*);`
- L161 _private prototype_ `static FOnActorBindingAdded& OnAddSourceForActorBinding();` — Delegate for when a source is being added for an actor binding. This is for our Sources Module, so it can properly add an actor source.
- L170 _public prototype_ `ULevelSequence* AddSourceForActorBinding(AActor* InActor, ULevelSequence* InLevelSequence);` — Notifies sources that a new actor binding has been added. @param InActor The actor the binding was added for. @param InLevelSequence The level sequence of the binding.
- L173 _public prototype_ `bool IsActorPossessable(const AActor* InActor) const;` — Checks if a given actor is possessable given source configuration.
- L180 _public prototype_ `void SetCachedAssets(class ULevelSequence* InSequence, FManifestSerializer* InManifestSerializer);` — Cache assets needed for sequencer.
- L186 _public prototype_ `void PreRecording(class ULevelSequence* InSequence, const FQualifiedFrameTime& InCurrentFrameTime, FManifestSerializer* InManifestSerializer);` — Pre recording pass
- L192 _public prototype_ `void StartRecording(class ULevelSequence* InSequence, const FQualifiedFrameTime& InCurrentFrameTime, FManifestSerializer* InManifestSerializer);` — Start recording pass
- L199 _public prototype_ `FFrameTime AdvanceTime(const FQualifiedFrameTime& CurrentFrameTime, float DeltaTime);` — Moves time forward by given DeltaTime @return Current Frame Number
- L205 _public prototype_ `FFrameTime TickRecording(class ULevelSequence* InSequence, const FQualifiedFrameTime& CurrentFrameTime, float DeltaTime);` — Tick recording pass @return Current Frame Number we are recording at.
- L211 _public prototype_ `void StopRecording(class ULevelSequence* InSequence, const bool bCancelled);` — Stop recording pass
- L219 _public prototype_ `static ULevelSequence* CreateSubSequenceForSource(ULevelSequence* InRootSequence, const FString& SubSequenceTrackName, const FString& SubSequenceAssetName, const FTakeRecorderSourcesSettings& InSettings = FTakeRecorderSourcesSettings());` — Creates a sub-sequence asset for the specified sub sequence name based on the given root sequence.
- L225 _public member_ `static TArray<TPair<FQualifiedFrameTime, FQualifiedFrameTime> > RecordedTimes;` — Array of pairs - key time and the corresponding timecode
- L227 _public function_ `FQualifiedFrameTime GetCachedFrameTime() const`
- L230 _private prototype_ `static ULevelSequence* FindExistingSubSequence(const ULevelSequence* InRootSequence, const FString& InSubSequenceAssetName);`
- L236 _private prototype_ `int32 RenderStatTakeSources(UWorld* World, FViewport* Viewport, FCanvas* Canvas, int32 X, int32 Y, const FVector* ViewLocation, const FRotator* ViewRotation);` — Renders stat text that displays the current list of active take recorder sources.  The take recorder can now operate without a panel and this gives users a way to view the current sources list outside of the panel.
- L239 _private function_ `virtual void Tick(float DeltaTime)` — Called at the end of each frame in both the Editor and in Game to update all Sources.
- L243 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Called whenever a property is changed on this class
- L247 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSourcesChanged);` — A list of handlers to invoke when the sources list changes
- L248 _private member_ `FOnSourcesChanged OnSourcesChangedEvent;`
- L251 _private prototype_ `void StartPreRecordingRecursive(const TArray<UTakeRecorderSource*>& InSources, ULevelSequence* InRootSequence, TArray<UTakeRecorderSource*>& NewSourcesOut, FManifestSerializer* InManifestSerializer);` — Calls PreRecording on sources recursively allowing them to create other sources which properly get PreRecording called on them as well.
- L255 _private prototype_ `void PreRecordingRecursive(TArray<UTakeRecorderSource*> InSources, ULevelSequence* InRootSequence, TArray<UTakeRecorderSource*>& NewSourcesOut, FManifestSerializer* InManifestSerializer, TSet<FString>& UsedTrackNames);` — Calls PreRecording on sources recursively allowing them to create other sources which properly get PreRecording called on them as well.
- L259 _private prototype_ `class UMovieSceneFolder* AddFolderForSource(const UTakeRecorderSource* InSource, class UMovieScene* InMovieScene);` — Finds the folder that the given Source should be created in, creating it if necessary.
- L262 _private prototype_ `void RemoveRedundantTracks();` — Remove object bindings that don't have any tracks and are not bindings for attach/path tracks
- L264 _private prototype_ `void StartRecordingPreRecordedSources(const FQualifiedFrameTime& CurrentFrameTime);`
- L266 _private prototype_ `void PreRecordSources(TArray<UTakeRecorderSource *> InSources);`
- L268 _private prototype_ `void StartRecordingTheseSources(const TArray<UTakeRecorderSource *>& InSources, const FQualifiedFrameTime& CurrentFrameTime);`
- L270 _private prototype_ `void SetSectionStartTimecode(UMovieSceneSubSection* SubSection, const FTimecode& Timecode, const FQualifiedFrameTime& CurrentFrameTime);`
- L276 _private member_ `TArray<TObjectPtr<UTakeRecorderSource>> Sources;` — `UPROPERTY(Instanced)` — The array of all sources contained within this list
- L280 _private member_ `TMap<TObjectPtr<UTakeRecorderSource>, TObjectPtr<ULevelSequence>> SourceSubSequenceMap;` — `UPROPERTY(Transient)` — Maps each source to the level sequence that was created for that source, or to the root source if a subsequence was not created.
- L284 _private member_ `TArray<TObjectPtr<class UMovieSceneSubSection>> ActiveSubSections;` — `UPROPERTY(Transient)` — List of sub-sections that we're recording into. Needed to ensure they're all the right size at the end without re-adjusting every sub-section in a sequence.
- L287 _private member_ `TMap<TWeakObjectPtr<AActor>, bool> AddedActorPossessableBindings;` — Bindings added for an actor mapped to whether it is possessable or not. Reset on PreRecord.
- L290 _private member_ `bool bIsRecording;` — Are we currently in a recording pass and should be ticking our Sources?
- L293 _private member_ `FFrameRate TargetLevelSequenceTickResolution;` — What Tick Resolution is the target level sequence we're recording into? Used to convert seconds into FrameNumbers.
- L296 _private member_ `FFrameRate TargetLevelSequenceDisplayRate;` — What Display Rate is the target level sequence we're recording into? Used to convert seconds into FrameNumbers.
- L299 _private member_ `uint32 SourcesSerialNumber;` — Non-serialized serial number that is used for updating UI when the source list changes
- L302 _private member_ `FTakeRecorderSourcesSettings Settings;` — Sources settings
- L305 _private member_ `FManifestSerializer* CachedManifestSerializer;` — Manifest Serializer that we are recording into.
- L308 _private member_ `ULevelSequence* CachedLevelSequence;` — Level Sequence that we are recording into. Cached so that new sources added mid-recording get placed in the right sequence.
- L311 _private member_ `TArray<TSharedPtr<FManifestSerializer>> CreatedManifestSerializers;` — Array of Allocated Serializers created for each sub sequence.  Deleted at the end of the recording so memory is freed.
- L314 _private member_ `TArray<UTakeRecorderSource *> PreRecordedSources;` — All sources after PreRecord
- L317 _private member_ `FQualifiedFrameTime CachedFrameTime;` — The last frame time during tick recording

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API TAKESCORE_API`
- L21 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(SubSequenceSerialization, Verbose, All);`
- L21 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(SubSequenceSerialization, Verbose, All);`
- L41 _namespace_ `namespace UE`
- L41 _namespace_ `namespace TakeRecorderSources` (scope `UE`)
- L143 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSourceAdded, UTakeRecorderSource* Source);`
- L144 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSourceRemoved, UTakeRecorderSource* Source);`
- L145 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSourceModified, UTakeRecorderSource* Source);`
- L159 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(UTakeRecorderSource*, FOnActorBindingAdded, AActor*, ULevelSequence*);`
- L247 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSourcesChanged);` — A list of handlers to invoke when the sources list changes

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/TakeRecorderSpawnableBehavior.h` (Public)


#### enum `ETakeRecorderSpawnableOverwriteBehavior`  
`enum class ETakeRecorderSpawnableOverwriteBehavior : uint8`  
_L10-18_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `ProjectDefault` — Use the project default to determine if spawnables are overwritten
- L15 _public enumerator_ `OverwriteLegacy UMETA(DisplayName = "Overwrite (Legacy)")` — Overwrite one existing spawnable similar to behavior in UE 5.7 and below
- L17 _public enumerator_ `CreateNew` — Creates a new spawnable

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/TakeRecorderTimeProcessing.h` (Public)


#### enum `UE::TakesCore::ETimecodeExtractionFlags`  
`enum class ETimecodeExtractionFlags : uint8`  
_L25-38_
- L27 _public enumerator_ `None`
- L29 _public enumerator_ `Hours = 1 << 0`
- L30 _public enumerator_ `Minutes = 1 << 1`
- L31 _public enumerator_ `Seconds = 1 << 2`
- L32 _public enumerator_ `Frames = 1 << 3`
- L33 _public enumerator_ `Subframes = 1 << 4`
- L35 _public enumerator_ `Times = 1 << 5`
- L37 _public enumerator_ `All = Hours | Minutes | Seconds | Frames | Subframes | Times`

#### struct `UE::TakesCore::FTimecodeExtractionData`  
`struct FTimecodeExtractionData`  
_L42-51_
- desc: All arrays, except those excluded by the ETimecodeExtractionFlags flags, are equal length.
- L44 _public member_ `TArray<int32> Hours;`
- L45 _public member_ `TArray<int32> Minutes;`
- L46 _public member_ `TArray<int32> Seconds;`
- L47 _public member_ `TArray<int32> Frames;`
- L48 _public member_ `TArray<FMovieSceneFloatValue> SubFrames;`
- L49 _public member_ `TArray<FFrameNumber> Times;`
- L50 _public member_ `FFrameRate TCRate;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace TakesCore` (scope `UE`)
- L17 _typedef_ `using FArrayOfRecordedTimePairs = TArray<TPair<FQualifiedFrameTime, FQualifiedFrameTime>>;` (scope `UE::TakesCore`) — Key: Recorded frame (to which to apply the timecode). Value: The timecode the recorded frame has.
- L20 _prototype_ `void ProcessRecordedTimes( ULevelSequence* InSequence, UMovieSceneTakeTrack* TakeTrack, const TOptional<TRange<FFrameNumber>>& FrameRange, const FArrayOfRecordedTimePairs& RecordedTimes );` (scope `UE::TakesCore`) — Creates a takes track to store timecode data on a take recorder source.
- L39 _prototype_ `ENUM_CLASS_FLAGS(ETimecodeExtractionFlags);` (scope `UE::TakesCore`)
- L54 _prototype_ `[[nodiscard]] FTimecodeExtractionData ExtractIntoTimecodeArrays( UMovieScene* InMovieScene, const TRange<FFrameNumber>& InRange, const FArrayOfRecordedTimePairs& InRecordedTimes, ETimecodeExtractionFlags InFlags = ETimecodeExtractionFlags::All );` (scope `UE::TakesCore`) — Splits recorded InRecordedTimes up into arrays, one for each component.

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/TakesCoreBlueprintLibrary.h` (Public)


#### class `UTakesCoreBlueprintLibrary`  
`class UTakesCoreBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L13-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L23 _public prototype_ `static int32 ComputeNextTakeNumber(const FString& Slate);` — `UFUNCTION(BlueprintCallable, Category="Take Recorder")` — Compute the next unused sequential take number for the specified slate
- L33 _public prototype_ `static TArray<FAssetData> FindTakes(const FString& Slate, int32 TakeNumber = 0);` — `UFUNCTION(BlueprintCallable, Category="Take Recorder")` — Find all the existing takes that were recorded with the specified slate @param Slate        The slate to filter by @param TakeNumber   The take number to filter by. <=0 denotes all takes
- L37 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnTakeRecorderSlateChanged, const FString&, Slate);`
- L38 _public prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnTakeRecorderTakeNumberChanged, int32, TakeNumber);`
- L42 _public prototype_ `static void SetOnTakeRecorderSlateChanged(FOnTakeRecorderSlateChanged OnTakeRecorderSlateChanged);` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder")` — Called when the slate is changed.
- L46 _public prototype_ `static void SetOnTakeRecorderTakeNumberChanged(FOnTakeRecorderTakeNumberChanged OnTakeRecorderTakeNumberChanged);` — `UFUNCTION(BlueprintCallable, Category = "Take Recorder")` — Called when the take number is changed.
- L48 _public prototype_ `static void OnTakeRecorderSlateChanged(const FString& InSlate);`
- L49 _public prototype_ `static void OnTakeRecorderTakeNumberChanged(int32 InTakeNumber);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API TAKESCORE_API`
- L37 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnTakeRecorderSlateChanged, const FString&, Slate);`
- L38 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnTakeRecorderTakeNumberChanged, int32, TakeNumber);`

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/TakesCoreLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTakesCore, Log, All);`

### `Plugins/VirtualProduction/Takes/Source/TakesCore/Public/TakesUtils.h` (Public)


#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace MovieScene` (scope `UE`)
- L30 _namespace_ `namespace TakesUtils`
- L38 _prototype_ `FString SanitizeInvalidChars(const FString& InText, const TCHAR* InvalidChars);` (scope `TakesUtils`) — Converts all invalid object name characters to _. Taken from ObjectTools and moved a small subset here to remove the need to call into ObjectTools and allow the same functionality in a non-Editor environment.
- L46 _prototype_ `FString SanitizeObjectName(const FString& InObjectName);` (scope `TakesUtils`) — Converts all invalid object name characters to _. Taken from ObjectTools and moved a small subset here to remove the need to call into ObjectTools and allow the same functionality in a non-Editor environment.
- L54 _prototype_ `FString SanitizePackageName(const FString& InPackageName);` (scope `TakesUtils`) — Replaces all invalid package name characters with _. Taken from PackageTools and moved a small subset here to remove the need to call into PackageTools and allow the same functionality in a non-Editor environment.
- L60 _prototype_ `UWorld* GetFirstPIEWorld();` (scope `TakesUtils`)
- L62 _prototype_ `void ClampPlaybackRangeToEncompassAllSections(UMovieScene* InMovieScene, bool bUpperBoundOnly);` (scope `TakesUtils`)
- L64 _prototype_ `void ResetViewAndWorkRange(UMovieScene* InMovieScene);` (scope `TakesUtils`)
- L66 _prototype_ `void CleanupExternalReferences(UObject* InObject);` (scope `TakesUtils`)
- L74 _prototype_ `void SaveAsset(UObject* InObject, bool bAlwaysKeepExternalReferences = true);` (scope `TakesUtils`) — Save an object to disk. @param InObject The object to save. @param bAlwaysKeepExternalReferences If we should always keep external references. When false, we clear them. When false and the InObject is a Level Sequence, we perform fine-grained cleanup.
- L76 _prototype_ `void CreateCameraCutTrack(ULevelSequence* LevelSequence, const FGuid& RecordedCameraGuid, const FMovieSceneSequenceID& SequenceID, const TRange<FFrameNumber>& InRange);` (scope `TakesUtils`)
- L93 _function_ `template<typename AssetType> static bool CreateNewAssetPackage(FString &InPackageName, AssetType*& OutAsset, FText* OutError, AssetType* OptionalBase = nullptr, UClass* OptionalClass = nullptr)` (scope `TakesUtils`) — Creates a new Package with the given Package Name (ie: /Game/Test/Foo) of the specified AssetType. If a package already exists at that name the package name will have a number appended and iterated on until an unused package name is found. InPackageName will be modified in this case and will return the package name that the asset was actually created at. You should consider calling MarkPackageDirty() on the returned asset if you further modify it, and you shouldstill notify the FAssetRegistryModule that the asset was created after this by calling FAssetRegistryModule::AssetCreated @param InPackageName	- The desired package name (path and asset name) for the new asset. May be mutated by this function if that package name is already taken. @param OutAsset		- The resulting asset if we were able to successfully create an asset. @param OutError		- Human readable error string to describe what went wrong (if anything). Can be nullptr if you don't care about the error message. @param OptionalBase	- Optional asset reference to duplicate the new asset from. If nullptr a brand new asset will be created. @return True if the asset was created successfully, false if there was an error.
- L150 _function_ `template<typename AssetType> static bool CreateNewAssetPackage(FString& InPackageName, TObjectPtr<AssetType>& OutAsset, FText* OutError, AssetType* OptionalBase = nullptr, UClass* OptionalClass = nullptr)` (scope `TakesUtils`)
- L167 _function_ `template<typename AssetType> static AssetType* MakeNewAsset(const FString& BaseAssetPath, const FString& BaseAssetName)` (scope `TakesUtils`) — Utility function that creates an asset with the specified asset path and name. If the asset cannot be created (as one already exists), we try to postfix the asset name until we can successfully create the asset.
- L170 _function_ `` (scope `TakesUtils::MakeNewAsset`)
- L210 _prototype_ `UWorld* DiscoverSourceWorld();` (scope `TakesUtils`)
- L213 _prototype_ `TSharedPtr<ISequencer> OpenSequencer(ULevelSequence* LevelSequence, FText* OutError);` (scope `TakesUtils`)
- L216 _prototype_ `FQualifiedFrameTime GetRecordTime(TSharedPtr<ISequencer> Sequencer, ULevelSequence* SequenceAsset, const FTimecode& TimecodeAtStart, bool bStartAtCurrentTimecode, float TimeDilation = 1.f);` (scope `TakesUtils`) — The time at which to record. Taken from the Sequencer global time, otherwise based on timecode
- L220 _prototype_ `TSharedPtr<const UE::MovieScene::FSharedPlaybackState> FindSequencerSharedPlaybackState(ULevelSequence* LevelSequence);` (scope `TakesUtils`) — Find the shared playback state from the current Sequencer. This can return nullptr.
- L225 _prototype_ `FQualifiedFrameTime GetRecordTime(ULevelSequence* SequenceAsset, const FTimecode& TimecodeAtStart, bool bStartAtCurrentTimecode, float TimeDilation = 1.f);` (scope `TakesUtils`) — The time at which to record, based on timecode
- L229 _prototype_ `FGuid ResolveActorFromSequence(const AActor* InActor, const ULevelSequence* CurrentSequence);` (scope `TakesUtils`) — Retrieve an actor guid for moviescene.
- L232 _prototype_ `FGuid ResolveActorFromSequence(const AActor* InActor, const ULevelSequence* CurrentSequence, TSharedPtr<const UE::MovieScene::FSharedPlaybackState> SharedPlaybackState);` (scope `TakesUtils`) — Retrieve an actor guid for the given sequence, providing a shared playback state. This uses the shared playback state as the lookup context for the binding.
- L235 _prototype_ `bool IsSourcePossessable(const UTakeRecorderSource* InSource);` (scope `TakesUtils`) — Checks if a source is considered possessable.
- L240 _prototype_ `bool DoesTrackHaveAnyKeys(UMovieSceneTrack& Track);` (scope `TakesUtils`) — Returns true if the track has any keys across all of its sections and channels.
