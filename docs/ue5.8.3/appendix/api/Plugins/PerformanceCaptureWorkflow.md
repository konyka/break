# Plugins / PerformanceCaptureWorkflow

- module root: `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow`
- headers: 17; symbols: 401
- symbol kinds: class=32, delegate=18, enum=3, enumerator=8, function=31, macro=1, member=164, prototype=136, struct=8
- PrivateDependencyModuleNames: AnimationCore, AssetDefinition, Blutility, CinematicCamera, CoreUObject, DataTableEditor, DeveloperSettings, EditorFramework, EditorSubsystem, Engine, EngineAssetDefinitions, IKRig, InputCore, LevelSequence, LiveLink, LiveLinkAnimationCore, LiveLinkInterface, MainFrame, ModelViewViewModel, MovieScene, NamingTokens, PerformanceCaptureCore, PerformanceCaptureWorkflowRuntime, Projects, Settings, Slate, SlateCore, SubobjectDataInterface, TakeRecorderSources, TakesCore, ToolMenus, UMG, UMGEditor, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: CommonUI, Core, PlacementMode

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Private/PCapActorFactory.h` (Private)


#### class `UPCapCharacterActorFactory`  
`class UPCapCharacterActorFactory : public UActorFactory`  
_L18-32_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L22 _private member_ `FTypedElementHandle SpawnedPerformerHandle;`
- L25 _private prototype_ `virtual UClass* GetDefaultActorClass( const FAssetData& AssetData ) override;` — Initialize NewActorClass if necessary, and return that class.
- L27 _private prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`
- L29 _private prototype_ `virtual void PostSpawnActor( UObject* Asset, AActor* NewActor ) override;`
- L31 _private prototype_ `virtual TArray<FTypedElementHandle> PlaceAsset(const FAssetPlacementInfo& InPlacementInfo, const FPlacementOptions& InPlacementOptions) override;`

#### class `UPCapPerformerActorFactory`  
`class UPCapPerformerActorFactory : public UActorFactory`  
_L35-45_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L40 _private prototype_ `virtual UClass* GetDefaultActorClass( const FAssetData& AssetData ) override;` — Initialize NewActorClass if necessary, and return that class.
- L42 _private prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`
- L44 _private prototype_ `virtual void PostSpawnActor( UObject* Asset, AActor* NewActor ) override;`

#### class `UPCapPropActorFactory`  
`class UPCapPropActorFactory : public UActorFactory`  
_L49-59_
- inherits: `UActorFactory`
- L54 _private prototype_ `virtual UClass* GetDefaultActorClass(const FAssetData& AssetData) override;` — Initialize NewActorClass if necessary, and return that class.
- L56 _private prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L58 _private prototype_ `virtual void PostSpawnActor( UObject* Asset, AActor* NewActor ) override;`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Private/PCapAssetDefinition.h` (Private)


#### class `UAssetDefinition_PCapDataTable`  
`class UAssetDefinition_PCapDataTable : public UAssetDefinition_DataTable`  
_L18-38_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_DataTable`
- L23 _private function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L24 _private function_ `virtual FLinearColor GetAssetColor() const override`
- L25 _private function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L26 _private function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L37 _private function_ `virtual bool CanImport() const override`

#### class `UAssetDefinition_PCapDataAsset`  
`class UAssetDefinition_PCapDataAsset : public UAssetDefinition_DataAsset`  
_L41-62_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_DataAsset`
- L47 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Implementation
- L48 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L49 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L50 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`

#### class `UAssetDefinition_PerformerDataAsset`  
`class UAssetDefinition_PerformerDataAsset : public UAssetDefinition_PCapDataAsset`  
_L65-76_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_PCapDataAsset`
- L71 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Implementation
- L72 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L73 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L74 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

#### class `UAssetDefinition_CharacterDataAsset`  
`class UAssetDefinition_CharacterDataAsset : public UAssetDefinition_PCapDataAsset`  
_L79-90_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_PCapDataAsset`
- L85 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Implementation
- L86 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L87 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L88 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

#### class `UAssetDefinition_PropDataAsset`  
`class UAssetDefinition_PropDataAsset : public UAssetDefinition_PCapDataAsset`  
_L93-104_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_PCapDataAsset`
- L99 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Implementation
- L100 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L101 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L102 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

#### class `UAssetDefinition_SessionTemplateAsset`  
`class UAssetDefinition_SessionTemplateAsset : public UAssetDefinition_PCapDataAsset`  
_L107-118_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_PCapDataAsset`
- L113 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Implementation
- L114 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L115 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L116 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

#### class `UAssetDefinition_PCapDataWorkflowCustomization`  
`class UAssetDefinition_PCapDataWorkflowCustomization : public UAssetDefinition_DataAsset`  
_L120-132_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_DataAsset`
- L126 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Implementation
- L127 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L128 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L129 _public prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L130 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Private/PCapAssetFactory.h` (Private)


#### class `UPCapDataTableFactory`  
`class UPCapDataTableFactory : public UDataTableFactory`  
_L17-37_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDataTableFactory`
- desc: Custom PCapDataTable Factory
- L23 _public prototype_ `UPCapDataTableFactory(const FObjectInitializer& ObjectInitializer);`
- L26 _public prototype_ `virtual bool ConfigureProperties() override;`
- L27 _public prototype_ `virtual FText GetDisplayName() const override;`
- L28 _public prototype_ `virtual FText GetToolTip() const override;`
- L29 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L30 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L31 _public prototype_ `virtual FName GetNewAssetThumbnailOverride() const override;`
- L36 _protected prototype_ `virtual UDataTable* MakeNewDataTable(UObject* InParent, FName Name, EObjectFlags Flags) override;`

#### class `UPCap_DataAssetFactory`  
`class UPCap_DataAssetFactory : public UFactory`  
_L41-57_
- inherits: `UFactory`
- L46 _public prototype_ `UPCap_DataAssetFactory(const FObjectInitializer& ObjectInitializer);`
- L49 _public member_ `TSubclassOf<UPCapDataAsset> DataAssetClass;` — `UPROPERTY(EditAnywhere, Category=DataAsset)`
- L52 _public prototype_ `virtual bool ConfigureProperties() override;` — UFactory interface
- L53 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L54 _public prototype_ `virtual uint32 GetMenuCategories() const override;`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Private/PCapBPFunctionLibrary.h` (Private)


#### class `UPerformanceCaptureBPFunctionLibrary`  
`class UPerformanceCaptureBPFunctionLibrary : public UEditorFunctionLibrary`  
_L15-44_
- reflection: `UCLASS()`
- inherits: `UEditorFunctionLibrary`
- L26 _public prototype_ `static FString SanitizeFileString(FString InString);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Workflow",meta=(DisplayName="Sanitize File Name String"))` — Returns a string stripped of the following characters []<>{}1!"$£%^&*()+=;:,.?/\|'@#~ @param	InString String you wish to clean @return	Cleaned string
- L34 _public prototype_ `static FString SanitizePathString(FString InString);` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Workflow",meta=(DisplayName="Sanitize File Path String"))` — Returns a string stripped of the following characters []<>{}1!"$£%^&*()+=;:,.?\|'@#~ Note filepath delimiters are not excluded @param	InString String you wish to clean @return	Cleaned string
- L43 _public prototype_ `static void GetAllActorsWithComponent(const UObject* WorldContextObject, TSubclassOf<UActorComponent> Component, TArray<AActor*>& OutActors);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Core", meta=(WorldContext="WorldContextObject", DeterminesOutputType="Component", DynamicOutputParam="OutActors"))` — Find all Actors in the world containing at least one instance of the given component class. This is a very slow operation, as it will search over every actor in the world. @param	Component	Class of component to find. Must be specified or result array will be empty. @param	OutActors	Output array of Actors of the specified class.

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Private/PCapDataTable.h` (Private)


#### class `UPCapDataTable`  
`class UPCapDataTable : public UDataTable`  
_L13-75_
- reflection: `UCLASS()`
- inherits: `UDataTable`
- L18 _public prototype_ `UPCapDataTable();`
- L21 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDatatableModified);`
- L23 _public member_ `FOnDatatableModified OnDatatableModified;` — `UPROPERTY(BlueprintAssignable, Transient, Category="Performance Capture|Database")`
- L26 _public prototype_ `void DataTableModified() const;` — Emit a callback each time the datatable is modified
- L34 _public prototype_ `bool RemoveTableRow(FName RowName);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Database")` — Remove a given row from the datatable. @param RowName The row name to remove. @return bool Whether operation was successful.
- L43 _public prototype_ `bool DuplicateTableRow(FName SourceRow, FName NewRow);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Database")` — Duplicate a given new row to the datatable. @param SourceRow The row to duplicate. @param NewRow The unique name for the new row. @return bool Whether duplication was successful.
- L51 _public prototype_ `bool AddTableRow(FName NewRow);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Database")` — Add a given new row to the datatable. @param NewRow The unique name for the new row. @return bool Whether operation was successful.
- L61 _public prototype_ `bool InsertTableRow(FName SelectedRow, FName NewRow, bool bAbove);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Database")` — Insert a given new row in to the datatable, above or below the selected row. @param SelectedRow The row to insert at. @param NewRow The unique name for the new row. @param bAbove Insert Above or Below the SelectedRow. @return bool Whether inserting new row was successful.
- L73 _public prototype_ `bool UpdateTableRow(const FName& RowName, const FTableRowBase& RowData);` — `UFUNCTION(BlueprintCallable, CustomThunk, Category="Performance Capture|Database", meta=(AutoCreateRefTerm="RowName", CustomStructureParam="RowData"))` — Update an existing row in-place (preserving row order), or add it if it does not exist. Unlike AddDataTableRow, this does not remove and re-insert the row, so order is preserved. Only compatiable with the natively declared PCapDataTable structs. @param RowName The name of the row to update or add. @param RowData The struct data to write into the row. @return true if the operation succeeded (row was updated or created); false if there was an error.

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDatatableModified);`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Private/PCapDatabase.h` (Private)


#### struct `FPCapRecordBase`  
`struct FPCapRecordBase : public FTableRowBase`  
_L32-53_
- reflection: `USTRUCT()`
- inherits: `FTableRowBase`
- L36 _public prototype_ `FPCapRecordBase();`
- L41 _public prototype_ `virtual void OnDataTableChanged(const UDataTable* InDataTable, const FName InRowName) override;`
- L43 _public prototype_ `virtual void OnPostDataImport(const UDataTable* InDataTable, const FName InRowName, TArray<FString>& OutCollectedImportProblems) override;`
- L47 _public member_ `FGuid UID;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture", meta=(IgnoreForMemberInitializationTest))` — GUID of the production record struct
- L51 _public member_ `bool bIsArchived = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Performance Capture")` — Bool to control if a record should be considered archived so the UI can hide it from view.

#### struct `FPCapProductionRecord`  
`struct FPCapProductionRecord : public FPCapRecordBase`  
_L57-69_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FPCapRecordBase`
- desc: Struct to hold the record of a production.
- L64 _public member_ `FName ProductionName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Performance Capture Production")` — Name of the production.
- L68 _public member_ `FString ProductionNotes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Performance Capture Production")` — Notes on the production.

#### enum `EPCapTakeStatus`  
`enum class EPCapTakeStatus : uint8`  
_L73-78_
- reflection: `UENUM(BlueprintType)`
- desc: Take status enumerator. Thumbs Up, Down and Neutral.
- L75 _public enumerator_ `ThumbsUp`
- L76 _public enumerator_ `ThumbsDown`
- L77 _public enumerator_ `Neutral`

#### struct `FPCapTakeRecord`  
`struct FPCapTakeRecord : public FPCapRecordBase`  
_L82-154_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FPCapRecordBase`
- desc: Struct to hold the record of a recorded take.
- L90 _public member_ `bool bFlag = false;` — `UPROPERTY(Transient, BlueprintReadWrite, Category="Flag")` — Temporary Flag. Transient, so will not be saved.
- L96 _public member_ `FDateTime DateTimeCreated;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Take")` — The date and time the sequence was recorded. This is the local machine UTC at the moment recording is finalised
- L100 _public member_ `TSoftObjectPtr<ULevelSequence> RecordedTake;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Take")` — The level sequence recorded.
- L104 _public member_ `float TakeDurationSeconds = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Take")` — Seconds Duration.
- L108 _public member_ `FFrameRate Framerate = FFrameRate(30, 1);` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Take")` — Recorded Framerate.
- L112 _public member_ `FTimecode TakeDurationTimecode;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Take")` — HHMMSSFF Duration.
- L116 _public member_ `FTimecode StartTimecode;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Take")` — Start Timecode.
- L120 _public member_ `FTimecode EndTimecode;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Take")` — End Timecode.
- L124 _public member_ `FTransform MocapStageRootTransform;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Take")` — Transform of the stage root when this recording was made.
- L128 _public member_ `EPCapTakeStatus TakeStatus = EPCapTakeStatus::Neutral;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Performance Capture Take")` — Status of Take - Thumbs Up, Thumbs Down or None.
- L132 _public member_ `int32 Rating = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Performance Capture Take", meta=(ClampMin=0, ClampMax=5))` — 5-Star Rating.
- L136 _public member_ `bool bContainsLiveLinkSources = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Performance Capture Take")` — Does this recording LiveLinkSource tracks.
- L140 _public member_ `bool bLiveLinkPlotted = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Performance Capture Take")` — Has this take been processed for plotting
- L149 _public member_ `bool bExternallyReplaced = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Performance Capture Take")` — Has the animation recorded for this take been replaced with an external asset import. This option will be positive if you use the import and upgrade workflow bringing fbx recordings from your motion capture software in and replacing the live recording.
- L153 _public member_ `FGuid SessionUID;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Take")` — GUID for the session used during the recording of this take.

#### struct `FPCapSessionRecord`  
`struct FPCapSessionRecord : public FPCapRecordBase`  
_L158-259_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FPCapRecordBase`
- desc: Struct to hold a datatable record of a session.
- L166 _public member_ `FName SessionName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session")` — Name for this session
- L170 _public member_ `FDateTime SessionDateTime;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session")` — Date and time session record was created.
- L174 _public member_ `FString SessionNotes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Performance Capture Session")` — Notes for this session record.
- L178 _public member_ `FName ProductionName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session")` — Name of Production this Session belongs to.
- L182 _public member_ `FGuid ProductionUID;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session")` — GUID of the Production record associated with this session record.
- L186 _public member_ `FString SessionOutputName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session", meta = (DisplayName = "Session OutputName"))` — The token generated name of the session.
- L190 _public member_ `FString SessionPath;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session", meta = (DisplayName = "Session Folder", ContentDir))` — The content browser path to this session record's data.
- L194 _public member_ `FString PerformerPath;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite , Category="Performance Capture Session", meta = (DisplayName = "Performer Folder", ContentDir))` — The content browser path to this session record's performer data.
- L198 _public member_ `FString CharacterPath;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session", meta = (DisplayName = "Character Folder", ContentDir))` — The content browser path to this session record's character data.
- L202 _public member_ `FString IngestPath;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session", meta = (DisplayName = "Ingest Folder", ContentDir))` — The content browser path to this session record's ingest data.
- L206 _public member_ `FString TakesPath;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session", meta = (DisplayName = "Takes Folder", ContentDir))` — The content browser path to this session record's recorded takes data.
- L210 _public member_ `FString PropPath;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session", meta = (DisplayName = "Prop Folder", ContentDir))` — The content browser path to this session record's prop data.
- L214 _public member_ `FString ScenePath;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session", meta = (DisplayName = "Scene Folder", ContentDir))` — The content browser path to this session record's scene data.
- L218 _public member_ `FString CommonPath;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session", meta = (DisplayName = "Common Folder", ContentDir))` — The content browser path to this session record's common data.
- L222 _public member_ `TArray<FString> AdditionalFolders;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session", meta = (DisplayName = "Additional Folders", ContentDir))` — Array of paths to folders of additional data. These folders can be defined in by the Session Template dataasset.
- L226 _public member_ `TSoftObjectPtr<UPCapDataTable> TakesDataTable;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session")` — Reference to the Takes datatable created for and used by this session record.
- L230 _public member_ `TArray<TSoftObjectPtr<UPCapPerformerDataAsset>> Performers;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session")` — Array of soft-refs to Performers spawned during this session.
- L234 _public member_ `TArray<TSoftObjectPtr<UPCapCharacterDataAsset>> Characters;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session")` — Array of soft-refs to Characters spawned during this session.
- L238 _public member_ `TArray<TSoftObjectPtr<UPCapPropDataAsset>> Props;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session")` — Array of soft-refs to Props spawned during this session.
- L242 _public member_ `TSoftObjectPtr<UPCapSessionTemplate> SessionTemplate;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session")` — Reference to a locked Session Template. This will be generated on session creation.
- L246 _public member_ `bool bIsWorldPartition = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session")` — Bool to determine if this session record while in a level streaming or world partition level.
- L250 _public member_ `TSoftObjectPtr<UWorld> SubLevel;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session")` — Sub-level created for this session, if using a persistent level of the Level streaming type.
- L254 _public member_ `TSoftObjectPtr<UDataLayerAsset> SessionDataLayer;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Session")` — Datalayer created for this session record, if using a persistent level of the World Partition type.
- L258 _public member_ `TSoftObjectPtr<UPCapDataTable> SessionSlateTable;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Performance Capture Session", meta = (RequiredAssetDataTags = "RowStructure=/Script/PerformanceCaptureWorkflow.PCapSlateRecord"))` — The slates datatable to use in Mocap Recorder for this session.

#### enum `EPCapSlateStatus`  
`enum class EPCapSlateStatus : uint8`  
_L263-268_
- reflection: `UENUM(BlueprintType)`
- desc: Slate Status. Can be Incomplete, Complete, Skip.
- L265 _public enumerator_ `Incomplete UMETA(Tooltip="Slate is incomplete")`
- L266 _public enumerator_ `Complete UMETA(Tooltip="Slate is marked complete")`
- L267 _public enumerator_ `Skip UMETA(Tooltip="Slate is marked to skip")`

#### struct `FPCapSlateRecord`  
`struct FPCapSlateRecord : public FPCapRecordBase`  
_L272-291_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FPCapRecordBase`
- desc: Slate struct. A slate record is a what the user wishes call a take and provides prior to recording
- L278 _public member_ `FString Slate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Performance Capture Slate", meta=(DisplayName="Slate"))` — String to provide Name of Slate.
- L282 _public member_ `FString SlateNote;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Performance Capture Slate", meta=(DisplayName="Note", MultiLine=true))` — Note on slate. This will be passed to the Mocap Recorder when using the Mocap Manager panel.
- L286 _public member_ `EPCapSlateStatus SlateStatus = EPCapSlateStatus::Incomplete;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Performance Capture Slate", meta=(DisplayName="Status"))` — Status of Slate, defined by the status enum.
- L290 _public member_ `FGuid SessionUID;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Performance Capture Slate")` — UID of the session this Slate is used in.

#### class `UPCapDataAsset`  
`class UPCapDataAsset : public UPrimaryDataAsset`  
_L303-323_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UPrimaryDataAsset`
- desc: Performance Capture DataAsset. Contains references to assets used for Performance Capture Workflows
- L309 _public prototype_ `UPCapDataAsset();` — Constructor
- L311 _public prototype_ `void CreateGuid();`
- L313 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L316 _public function_ `FGuid GetAssetUID() const` — `UFUNCTION(BlueprintGetter, Category="Performance Capture|Admin")`
- L322 _private member_ `FGuid AssetUID;` — `UPROPERTY(BlueprintGetter="GetAssetUID", Category="Performance Capture|Admin", meta=(IgnoreForMemberInitializationTest))` — Guid for disambiguating actors spawned by the data assets. Only editable from BP.

#### class `UPCapPerformerDataAsset`  
`class UPCapPerformerDataAsset : public UPCapDataAsset`  
_L327-362_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UPCapDataAsset`
- desc: Mocap Performer DataAsset. This class is intended to track and encapsulate the properties and assets that make up a performer
- L333 _public prototype_ `UPCapPerformerDataAsset();` — Constructor
- L337 _public member_ `FName PerformerName;` — `UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Performance Capture Performer")` — LiveLink Subject for the body of this Performer
- L341 _public member_ `FLiveLinkSubjectName LiveLinkSubject;` — `UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Performance Capture Performer")` — LiveLink Subject for this Performer.
- L345 _public member_ `TSoftClassPtr<ACapturePerformer> PerformerActorClass;` — `UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, NoClear, Category="Performance Capture Performer")` — Performer Actor class to use for this performer.
- L349 _public member_ `FLinearColor PerformerColor;` — `UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Performance Capture Performer")` — Color for this performer.
- L353 _public member_ `TSoftObjectPtr<USkeletalMesh> BaseSkeletalMesh;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Performance Capture Performer")` — Performer Base Skeleton.
- L357 _public member_ `TSoftObjectPtr<USkeletalMesh> PerformerProportionedMesh;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Performance Capture Performer")` — Performer Mesh. This must be created in a T or A Pose performer from a LiveLink pose
- L361 _public member_ `TSoftObjectPtr<UIKRigDefinition> IKRig;` — `UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Performance Capture Performer")` — Performer IKRig.

#### class `UPCapCharacterDataAsset`  
`class UPCapCharacterDataAsset : public UPCapDataAsset`  
_L366-415_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UPCapDataAsset`
- desc: Mocap Character Data asset. This class is intended to track and encapsulate the properties and assets that make up a character
- L373 _public prototype_ `UPCapCharacterDataAsset();` — Mocap Character Data asset. This class is intended to track and encapsulate the properties and assets that make up a character UCLASS(Blueprintable, BlueprintType) class UPCapCharacterDataAsset : public UPCapDataAsset { GENERATED_BODY() public: Capture Character Constructor
- L377 _public member_ `FName CharacterName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Performance Capture Character", meta=(Tooltip="Optional Name for Character. If blank DataAsset name will be used"))` — Capture Character Name.
- L381 _public member_ `TSoftObjectPtr<UPCapPerformerDataAsset> SourcePerformerAsset;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Performance Capture Character")` — Source Performer Asset for this Character.
- L386 _public member_ `TSoftClassPtr<ASkeletalMeshActor> CaptureCharacterClass;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Performance Capture Character", meta = (GetAllowedClasses = "GetAllowedCaptureCharacterActorClasses", GetDisallowedClasses = "GetDisallowedCaptureCharacterActorClasses"))` — Character actor Class
- L392 _public member_ `TSoftObjectPtr<USkeletalMesh> SkeletalMesh;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Performance Capture Character")` — Main Skeletal Mesh Asset. This will be the root component of any characters spawned. A character will not be spawned if this asset reference is null or not valid.
- L396 _public member_ `TSoftObjectPtr<UIKRigDefinition> IKRig;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Performance Capture Character")` — IKRig Asset.
- L400 _public member_ `TSoftObjectPtr<UIKRetargeter> Retargeter;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Performance Capture Character")` — Retarget Asset.
- L406 _public member_ `TArray<TSoftObjectPtr<USkeletalMesh>> AdditionalMeshes_DEPRECATED;` — `UE_DEPRECATED(5.7, "AdditionalMeshes is no longer used. Create a SkeletalMeshActor class with the required meshes and components instead.")` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage = "Create a SkeletalMeshActor class with the required meshes and components instead."))` — Array of additional skeleltal mesh assets that will be spawned and parented to the root skeleteal mesh asset
- L411 _private prototype_ `static TArray<UClass*> GetAllowedCaptureCharacterActorClasses();` — `UFUNCTION()`
- L414 _private prototype_ `static TArray<UClass*> GetDisallowedCaptureCharacterActorClasses();` — `UFUNCTION()`

#### class `UPCapPropDataAsset`  
`class UPCapPropDataAsset : public UPCapDataAsset`  
_L419-481_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UPCapDataAsset`
- desc: Prop DataAsset
- L425 _public prototype_ `UPCapPropDataAsset();` — Prop DataAsset UCLASS(Blueprintable, BlueprintType) class UPCapPropDataAsset : public UPCapDataAsset { GENERATED_BODY() public: Prop DataAsset Constructor
- L429 _public member_ `FName PropName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Performance Capture Prop", meta=(Tooltip="Optional Name for Prop. If blank LiveLinkSubject name will be used"))` — Prop Name.
- L433 _public member_ `FLiveLinkSubjectName LiveLinkSubject;` — `UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Performance Capture Prop")` — Prop's LiveLinkSubject.
- L437 _public member_ `FTransform PropOffsetTransform;` — `UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Performance Capture Prop")` — Static Mesh Offset Transform
- L441 _public member_ `TSoftClassPtr<UPCapPropComponent> PropComponentClass;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Performance Capture Prop", meta=(DisplayName="Prop Component Class"), NoClear)` — Prop Component - select a customized prop component if required, otherwise base C++ class will be used
- L445 _public member_ `TSoftObjectPtr<UStaticMesh> PropStaticMesh;` — `UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Performance Capture Prop", meta=(DisplayName="Static Mesh", EditCondition="bCanSetStaticMesh", HideEditConditionToggle))` — Prop Static - if this is left blank the mocap static mesh will be used
- L449 _public member_ `TSoftObjectPtr<USkeletalMesh> PropSkeletalMesh;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Performance Capture Prop", meta=(DisplayName="Skeletal Mesh", EditCondition="bCanSetSkeletalMesh", HideEditConditionToggle))` — Prop SkelMesh - if this is left blank the mocap static mesh will be used
- L453 _public member_ `TSoftClassPtr<AActor> CustomPropClass;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Performance Capture Prop", meta=(DisplayName="Custom Prop Class", EditCondition="bCanSetCustomPropClass", HideEditConditionToggle))` — Custom Class - if you want your prop to be created from a custom BP actor, set the class here
- L457 _public member_ `bool bHiddenInGame = false;` — `UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Performance Capture Prop", meta=(Tooltip="Choose True for props you want to hide in 'Game' view e.g. Proxies or integrators"))` — Bool to control if this prop will be set to bHiddenInGame=True when spawned. Useful for proxy objects you don't want to see in game view.
- L461 _public member_ `bool bClearEditConditions = false;` — `UPROPERTY(EditDefaultsOnly, Transient, Category="Performance Capture Prop", AdvancedDisplay, meta=(DisplayName="Reset Read-only Options", Tooltip="Reset all mesh options (removes read-only status on fields)"))` — bool to control edit condition of the Static and Skeletal mesh properties
- L465 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L467 _public prototype_ `virtual void PostLoad() override;`
- L474 _private member_ `bool bCanSetStaticMesh = true;` — `UPROPERTY()`
- L476 _private member_ `bool bCanSetSkeletalMesh = true;` — `UPROPERTY()`
- L478 _private member_ `bool bCanSetCustomPropClass =true;` — `UPROPERTY()`
- L480 _private prototype_ `void ValidateEditConditions();`

#### class `UPerformanceCaptureDatabaseHelper`  
`class UPerformanceCaptureDatabaseHelper : public UObject`  
_L489-500_
- reflection: `UCLASS(Blueprintable, Abstract, meta = (ShowWorldContextPin))`
- inherits: `UObject`
- L496 _public prototype_ `void CreateRecord();` — `UFUNCTION(BlueprintImplementableEvent)`
- L499 _public prototype_ `void DeleteRecord();` — `UFUNCTION(BlueprintImplementableEvent)`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Private/PCapNamingTokens.h` (Private)


#### class `UPCapNamingTokens`  
`class UPCapNamingTokens : public UNamingTokens`  
_L15-41_
- reflection: `UCLASS(NotBlueprintable)`
- inherits: `UNamingTokens`
- desc: Naming tokens class for Pcap workflow
- L21 _public prototype_ `UPCapNamingTokens();`
- L24 _public function_ `static FString GetPCapNamespace()`
- L32 _protected prototype_ `virtual void OnCreateDefaultTokens(TArray<FNamingTokenData>& Tokens) override;`
- L33 _protected prototype_ `virtual void OnPreEvaluate_Implementation(const FNamingTokensEvaluationData& InEvaluationData) override;`
- L34 _protected prototype_ `virtual void OnPostEvaluate_Implementation() override;`
- L40 _private member_ `TObjectPtr<UPCapNamingTokensContext> Context;` — `UPROPERTY(Transient)`

#### class `UPCapNamingTokensContext`  
`class UPCapNamingTokensContext : public UObject`  
_L46-55_
- inherits: `UObject`
- L54 _public member_ `TObjectPtr<const UPCapSessionTemplate> SessionTemplate;` — `UPROPERTY(Transient)` — The current template in use. This is so the session template can pass a reference of itself.

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Private/PCapSessionTemplate.h` (Private)


#### struct `FPCapTokenisedString`  
`struct FPCapTokenisedString`  
_L15-27_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public prototype_ `FPCapTokenisedString() = default;`
- L22 _public member_ `FString Template;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Folder Template")`
- L25 _public member_ `FString Output;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Folder Template")`

#### struct `FPCapTokenisedFolderPath`  
`struct FPCapTokenisedFolderPath`  
_L30-42_
- reflection: `USTRUCT(BlueprintType)`
- L34 _public prototype_ `FPCapTokenisedFolderPath() = default;`
- L37 _public member_ `FString FolderPathTemplate;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Folder Template")`
- L40 _public member_ `FString FolderPathOutput;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Folder Template")`

#### class `UPCapSessionTemplate`  
`class UPCapSessionTemplate : public UPCapDataAsset`  
_L50-334_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UPCapDataAsset`
- L54 _private prototype_ `UPCapSessionTemplate(const FObjectInitializer& ObjectInitializer);`
- L63 _public member_ `FDirectoryPath TemplateRootFolder;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetRootFolder, BlueprintGetter = GetRootFolder, Category="Template", meta = (ContentDir, DisplayName = "Root Folder", EditCondition="bIsEditable"))`
- L69 _public prototype_ `virtual void PostLoad() override;`
- L73 _public member_ `FString ProductionName;` — `UPROPERTY(EditAnywhere, Category="Template", BlueprintGetter = GetProductionName, BlueprintSetter = SetProductionName, meta = (DisplayName = "Production Name", EditCondition="bIsEditable"))` — String for production name. Will be sanitized for illegal filesystem characters
- L77 _public member_ `FString SessionName;` — `UPROPERTY(EditAnywhere, Category="Template", BlueprintGetter = GetSessionName, BlueprintSetter = SetSessionName, meta = (DisplayName = "Session Name", EditCondition="bIsEditable"))` — String for session name. Will be sanitized for illegal filesystem character
- L81 _public member_ `FPCapTokenisedString SessionToken;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Template", meta = (DisplayName = "Session Token", EditCondition="bIsEditable", tooltip="The final name of our session, including any tokens you include in it's construction. You can use tokens to build this string, including the Session Name above"))` — The final name of the session, evaluated from the given tokens and static strings
- L87 _public function_ `void SetRootFolder(FDirectoryPath NewRootPath)` — `UFUNCTION(BlueprintSetter)` — Set the RootFolder.
- L98 _public function_ `FDirectoryPath GetRootFolder()` — `UFUNCTION(BlueprintGetter)` — Get the RootFolder. @return TemplateRootFolder path.
- L108 _public function_ `FString GetSessionName()` — `UFUNCTION(BlueprintGetter)` — Get the Session Name. @return SessionName string.
- L118 _public function_ `void SetSessionName(FString NewSessionName)` — `UFUNCTION(BlueprintSetter)` — Set the session name @param NewSessionName New session name string. This will be sanitized for illegal filesystem characters.
- L129 _public function_ `FString GetProductionName()` — `UFUNCTION(BlueprintGetter)` — Get the Production Name string. @return ProductionName
- L139 _public function_ `void SetProductionName(FString NewProductionName)` — `UFUNCTION(BlueprintSetter)` — Set New Production Name string. This will be sanitized for illegal filesystem characters @param NewProductionName
- L155 _public member_ `FPCapTokenisedFolderPath SessionFolder;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Folders", DisplayName = "Session Folder", meta=(EditCondition="bIsEditable"))` — Session folder template
- L159 _public member_ `FPCapTokenisedFolderPath CommonFolder;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Folders|Session Subfolders", meta = (DisplayName = "Common Folder", EditCondition="bIsEditable"))` — Common folder template
- L163 _public member_ `FPCapTokenisedFolderPath CharacterFolder;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Folders|Session Subfolders", meta = (DisplayName = "Character Folder", EditCondition="bIsEditable"))` — Character folder template
- L167 _public member_ `FPCapTokenisedFolderPath IngestFolder;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Folders|Session Subfolders", meta = (DisplayName = "Ingest Folder", EditCondition="bIsEditable"))` — Ingest data folder template
- L171 _public member_ `FPCapTokenisedFolderPath PerformerFolder;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Folders|Session Subfolders", meta = (DisplayName = "Performer Folder", EditCondition="bIsEditable"))` — Performer folder template
- L175 _public member_ `FPCapTokenisedFolderPath PropFolder;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Folders|Session Subfolders", meta = (DisplayName = "Prop Folder", EditCondition="bIsEditable"))` — Prop folder template
- L179 _public member_ `FPCapTokenisedFolderPath SceneFolder;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Folders|Session Subfolders", meta = (DisplayName = "Scene Folder", EditCondition="bIsEditable"))` — Scene data folder template
- L183 _public member_ `FPCapTokenisedFolderPath TakeFolder;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Folders|Session Subfolders", meta = (DisplayName = "Takes Folder", EditCondition="bIsEditable"))` — Take Recorder folder template
- L187 _public member_ `TMap<FName, FPCapTokenisedFolderPath> AdditionalFolders;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Folders|Session Subfolders", meta=(DisplayAfter="Additional Folders", EditCondition="bIsEditable", ToolTip="Use the additional folders for any extra data you want contain in your session - eg audio and facial capture data"))` — Additional folders. Create any additional folders you want under the session folder. You can use the Map key to label what each folder is for
- L193 _public member_ `bool bRecordTimecode = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Take Recorder", meta = (DisplayName = "Record Timecode", EditCondition="bIsEditable"))` — Bool to control if timecode is recorded or not.
- L197 _public member_ `bool bRecordPossessable = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Take Recorder", meta = (DisplayName = "Record to Possessable", EditCondition="bIsEditable"))` — Bool to control if all actors should be recorded to possessable or spawnable.
- L201 _public member_ `bool bStartAtCurrentTimecode = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Take Recorder", meta = (DisplayName = "Start at Current Timecode", EditCondition="bIsEditable"))` — Bool to control if recorded sequences should start at the current timecode value.
- L205 _public member_ `EUpdateClockSource RecordingClockSource = EUpdateClockSource::Timecode;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Take Recorder", meta = (DisplayName = "Recording Clock Source", EditCondition="bIsEditable"))` — The clock source to use with recordings. Recommended is "Timecode".
- L209 _public member_ `bool bRecordSubscenes = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Take Recorder", meta = (DisplayName = "Record to Subsequences", EditCondition="bIsEditable"))` — Bool to control if each recording source is placed into a subscene at the start of recording.
- L213 _public member_ `FPCapTokenisedString TakeSaveName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Take Recorder", DisplayName = "Take Save Name", meta=(EditCondition="bIsEditable", tooltip ="This be used by take recorder as the name of the recorded level sequence and the folder for any sub-scenes and assets"))` — Take name token.
- L217 _public member_ `FPCapTokenisedString AnimationTrackName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Take Recorder|Animation", DisplayName = "Animation Track Name", meta=(EditCondition="bIsEditable"))` — Animation track name token.
- L221 _public member_ `FPCapTokenisedString AnimationAssetName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Take Recorder|Animation", DisplayName = "Animation Asset Name", meta=(EditCondition="bIsEditable"))` — Animation Asset name token.
- L225 _public member_ `FPCapTokenisedString AnimationSubDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Take Recorder|Animation", DisplayName = "Animation Sub Directory", meta=(EditCondition="bIsEditable"))` — Animation subdirectory token.
- L229 _public member_ `FPCapTokenisedString SubsequenceDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Take Recorder|Animation", DisplayName = "Subsequence Directory", meta=(EditCondition="bIsEditable", tooltip ="This affects the directory created for subsequences. It cannot be set per actor, only globally across the whole recording."))` — Subsequence directory name token.
- L233 _public member_ `FPCapTokenisedString AudioSourceName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Take Recorder|Audio", DisplayName = "Audio Source Name", meta=(EditCondition="bIsEditable"))` — Audio source name token.
- L237 _public member_ `FPCapTokenisedString AudioTrackName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Take Recorder|Audio", DisplayName = "Audio Track Name", meta=(EditCondition="bIsEditable"))` — Audio track name token.
- L241 _public member_ `FPCapTokenisedString AudioAssetName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Take Recorder|Audio", DisplayName = "Audio Asset Name", meta=(EditCondition="bIsEditable"))` — Audio asset name token.
- L245 _public member_ `FPCapTokenisedString AudioSubDirectory;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Take Recorder|Audio", DisplayName = "Audio Sub Directory", meta=(EditCondition="bIsEditable"))` — Audio subdirectory token.
- L251 _public member_ `FString PCapTokens = "{session} - Name for your Performance Capture session\n" "{production} - Name of Performance Capture production\n" "{sessionToken} - Output value of the Session Token field\n" "{pcapRootFolder} - Root folder for all Performance Capture productions and sessions\n" "{sessionFolder} - folder path for Performance Capture session" /*"\n" "\n" "\n"*` — `UPROPERTY(VisibleAnywhere, Category="Tokens", meta= (displayname = "PCap Tokens", tooltip="Use these tokens in your template strings. The namespace for these tokens is 'pcap.'"))` — Read only fields to show the user what tokens are available to them in the pcap, global, and take recorder namespaces
- L262 _public member_ `FString GlobalTokens = "{yyyy} - Year (4 digit)\n" "{yy} - Year (2 digit)\n" "{Mmm} - 3-character Month (Pascal Case)\n" "{MMM} - 3-character Month (UPPERCASE)\n" "{mmm} - 3-character Month (lowercase)\n" "{mm} - Month (2 digit)\n" "{Ddd} - 3-character Day (Pascal Case)\n" "{DDD} - 3-character Day (UPPERCASE)\n" "{ddd} - 3-character Day (lowercase)\n" "{dd} - Day (2 digit)\n" "{ampm} - am or pm (lowercase)\n" "{AMPM} - AM or PM (UPPERCASE)\n" "{12h} - Hour (12)\n" "{24h} - Hour (24)\n" "{min} - Minute\n" "{sec} - Second\n" "{m` — `UPROPERTY(VisibleAnywhere, Category="Tokens", meta= (displayname = "Global Tokens", tooltip="Use these tokens in your template strings."))`
- L282 _public member_ `FString TakeRecorderTokens = "{day}\n" "{month}\n" "{year}\n" "{hour}\n" "{minute}\n" "{second}\n" "{take}\n" "{slate}\n" "{map}\n" "{actor}\n" "{c` — `UPROPERTY(VisibleAnywhere, Category="Tokens", meta= (displayname = "Take Recorder Tokens", tooltip="Use these tokens in your template strings. The namespace for these tokens is 'pcap.'"))`
- L304 _protected member_ `bool bIsEditable;` — `UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Admin")` — Bool to control edit condition on the members of this asset. Prevents user from editing after a session has been created.
- L307 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L314 _protected prototype_ `void UpdateAllFields();` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Session Template")` — Update all members and ensure illegal characters are removed.
- L321 _protected prototype_ `FPCapTokenisedString UpdateStringTemplate(FPCapTokenisedString& TokenisedTemplate);` — Update string token from the given template. @param TokenisedTemplate @return Updated string token struct.
- L328 _protected prototype_ `FPCapTokenisedFolderPath UpdateFolderPathTemplate(FPCapTokenisedFolderPath& FolderPathTokenisedTemplate);` — Upate a token for a folder path. @param FolderPathTokenisedTemplate @return Updated folder path struct.
- L333 _private member_ `TObjectPtr<UPCapNamingTokensContext> NamingTokensContext;` — `UPROPERTY()`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Private/PCapSettings.h` (Private)


#### class `UPerformanceCaptureSettings`  
`class UPerformanceCaptureSettings : public UObject`  
_L26-128_
- inherits: `UObject`
- L35 _public prototype_ `static UPerformanceCaptureSettings* GetPerformanceCaptureSettings();` — `UFUNCTION(BlueprintPure, Category="Performance Capture|Settings")` — Get the Performance Capture settings uobject @return Settings Object.
- L41 _public prototype_ `void ShowPerformanceCaptureProjectSettings();` — `UFUNCTION(BlueprintCallable, Category = "Performance Capture|Settings")` — Open the project settings panel and show the Performance Capture section.
- L45 _public member_ `TSoftClassPtr<APerformanceCaptureStageRoot> StageRoot;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Config, NoClear, Category="Actors", DisplayName= "Stage Root Actor Class" ,meta = (MetaClass = "/Script/PerformanceCaptureWorkflow.PerformanceCaptureStageRoot"))` — Stage Root Actor to spawn for Performance Capture. Class must derive from APerformanceCaptureStageRoot.
- L50 _public member_ `TSoftObjectPtr<USkeletalMesh> DefaultPerformerSkelMesh;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Config, NoClear, Category="Actors", DisplayName= "Default Performer Mesh")` — Base skeletal mesh for Mocap performers.
- L54 _public member_ `TArray<TSoftClassPtr<ASkeletalMeshActor>> AllowedCaptureCharacterActorClasses;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Config, NoClear, Category = "Actors")` — Skeletal Mesh Actor classes that are explicitly to be used as Characters with Mocap Manager. These skeletal mesh actors must contain a retarget component
- L58 _public member_ `TArray<TSoftClassPtr<ASkeletalMeshActor>> DisallowedCaptureCharacterActorClasses;` — `UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Config, NoClear, Category = "Actors")` — Skeletal Mesh Actor classes that are explicitly disallowed for use as Characters with Mocap Manager.
- L62 _public member_ `TSoftClassPtr<UMVVMViewModelBase> ViewModelClass;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Config, NoClear, Category="UI", meta = (MetaClass = "/Script/ModelViewViewModel.MVVMViewModelBase",ConfigRestartRequired=true))` — Blueprint Viewmodel class. If you change class you will need to restart the editor to pick up the change.
- L66 _public member_ `TSoftObjectPtr<UEditorUtilityWidgetBlueprint> MocapManagerUI;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Config, Category="UI", meta = (MetaClass = "/Script/Blutility.EditorUtilityWidgetBlueprint"))` — Editor Utility Widget class that will be used for the Mocap Manager UI
- L70 _public member_ `TSoftObjectPtr<UPCapWorkflowCustomization> MocapManagerDefaultWorkflow;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Config, Category="UI", DisplayName = "Default Workflows", meta = ( tooltip="This Data Asset defines the UI panels you wish to have available in Mocap Manager"))` — Default Workflow UI panels to use in the Mocap Manager panel.
- L77 _public member_ `TSoftClassPtr<UEditorUtilityWidget> WorkflowPhaseUIBaseClass;` — `UPROPERTY(BlueprintReadOnly, Config, NoClear, Category="UI", meta = (MetaClass = "/Script/Blutility.EditorUtilityWidgetBlueprint"))` — Editor Utility Widget class that will be used for each of the phase UI panels. Note this is not editable in the settings. It can only be modified in the DefaultPerformanceCaptureWorkflow.ini
- L81 _public member_ `TSoftObjectPtr<UPCapSessionTemplate> DefaultSessionTemplate;` — `UPROPERTY(BlueprintReadOnly, Config, EditDefaultsOnly, Category="Database", DisplayName = "Default Session Template", meta = ( tooltip="This Asset defines the folder structure and settings used in a performance capture session"))` — Default session template to use when starting the Mocap Manager panel.
- L85 _public member_ `TSoftClassPtr<UPerformanceCaptureDatabaseHelper> DatabaseHelperClass;` — `UPROPERTY(EditAnywhere, Config, NoClear, Category="Database", DisplayName = "Database Helper Class", meta=(ConfigRestartRequired=true))` — Blueprint helper class for making database calls. If you change class you will need to restart the editor to pick up the change
- L89 _public member_ `TSoftObjectPtr<UPCapDataTable> SessionTable;` — `UPROPERTY(BlueprintReadOnly, Config, EditDefaultsOnly, Category = "Database|Internal Database Tables", DisplayName = "Session DataTable", meta = (RequiredAssetDataTags = "RowStructure=/Script/PerformanceCaptureWorkflow.PCapSessionRecord"))` — Pointer to the datatable Mocap Manager will use for recording all session data.
- L93 _public member_ `TSoftObjectPtr<UPCapDataTable> ProductionTable;` — `UPROPERTY(BlueprintReadOnly, Config, EditDefaultsOnly, Category="Database|Internal Database Tables", DisplayName = "Production DataTable", meta = (RequiredAssetDataTags = "RowStructure=/Script/PerformanceCaptureWorkflow.PCapProductionRecord"))` — Pointer to the datatable Mocap Manager will use for recording production data.
- L100 _public prototype_ `void SetSessionTable(TSoftObjectPtr<UPCapDataTable> NewDataTable);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Settings")` — Set the session table in Performance Capture settings. @param NewDataTable Datatable ref. Must be of the FPCapSession struct type.
- L107 _public prototype_ `void SetProductionTable(TSoftObjectPtr<UPCapDataTable> NewDataTable);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Settings")` — Set the production table in Performance Capture Settings. @param NewDataTable Datatable ref. Must be of the FPCapProduction struct type.
- L114 _public prototype_ `void SetDefaultSessionTemplate(TSoftObjectPtr<UPCapSessionTemplate> NewSessionTemplate);` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Settings")` — Set the default session template in Performance Capture Settings. @param NewSessionTemplate Session Template data asset ref.
- L118 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPCapSettingsChanged);`
- L124 _public member_ `FOnPCapSettingsChanged OnPCapSettingsChanged;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|Settings")` — Multicast delegate called whenever the Performance Capture settings object is modified.
- L126 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### class `UPCapDialogObject`  
`class UPCapDialogObject : public UObject`  
_L134-141_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UObject`
- desc: Utility object for choosing a content browser path in a message dialog.
- L140 _public member_ `FDirectoryPath Path;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=nocategory, meta=(ContentDir, DisplayName="PCap Path", ToolTip="Choose a folder for your Performance Capture data"))`

#### Free symbols / members of external scopes

- L118 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPCapSettingsChanged);`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Private/PCapSubsystem.h` (Private)


#### class `UPerformanceCaptureSubsystem`  
`class UPerformanceCaptureSubsystem : public UEngineSubsystem`  
_L27-221_
- reflection: `UCLASS(Category="Performance Capture")`
- inherits: `UEngineSubsystem`
- L33 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L41 _public function_ `UPerformanceCaptureDatabaseHelper* GetDatabaseHelper() const` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Database")` — Get the Performance Capture Database helper. @return Databasehelper object
- L51 _public function_ `UMVVMViewModelCollectionObject* GetViewModelCollection() const` — `UFUNCTION(BlueprintCallable, Category="Performance Capture|Viewmodel")` — Get the Performance Capture Viewmodel collection. @return Performance Capture Viewmodel collection.
- L61 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapAssetRemoved, FAssetData, DeletedAsset);` — Multicast delegate that will execute when an asset is removed from the asset registry. Returns the FAssetData of the removed asset.
- L64 _public member_ `FOnPCapAssetRemoved OnPCapAssetRemoved;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|Assets")` — Editor Only
- L69 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPCapAssetRenamed, FAssetData, RenamedAsset, FString, OldName);` — Multicast delegate that will execute when an asset is renamed to the asset registry. Returns the FAssetData of the renamed asset.
- L72 _public member_ `FOnPCapAssetRenamed OnPCapAssetRenamed;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|Assets")` — Editor Only
- L77 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapAssetAdded, FAssetData, NewAsset);` — Multicast delegate that will execute when a new asset is added to the asset registry. Returns the FAssetData of new asset.
- L80 _public member_ `FOnPCapAssetAdded OnPCapAssetAdded;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|Assets")` — Editor Only
- L85 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapActorModified, AActor*, Actor);` — Multicast delegate that will execute when an actor is modified in the Level Editor. Returns the actor modified.
- L88 _public member_ `FOnPCapActorModified OnPCapActorModified;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|Workflow")` — Editor Only
- L93 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapEditorUndo, bool, bSuccess);` — Multicast delegate that will execute when the user calls Undo. Returns success boolean.
- L96 _public member_ `FOnPCapEditorUndo OnPCapEditorUndo;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|Workflow")` — Editor Only
- L101 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapEditorRedo, bool, bSuccess);` — Multicast delegate that will execute when the user calls Redo. Returns success boolean.
- L104 _public member_ `FOnPCapEditorRedo OnPCapEditorRedo;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|Workflow")` — Editor Only
- L109 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapAssetEditorOpen, UObject*, Asset);` — Multicast delegate that will execute when an asset editor is opened. Returns the asset object that is opened.
- L112 _public member_ `FOnPCapAssetEditorOpen OnPCapAssetEditorOpen;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|Assets")` — Editor Only
- L117 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapAssetEditorClose, UObject*, Asset);` — Multicast delegate that will execute when an asset editor is closed. Returns the asset object that is closed.
- L120 _public member_ `FOnPCapAssetEditorClose OnPCapAssetEditorClose;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|Assets")` — Editor Only
- L125 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPCapLiveLinkSubjectUpdate, FLiveLinkSubjectKey, Subject, ELiveLinkSubjectState, State);` — Multicast delegate that will execute when a Live Link subject's state is updated.
- L128 _public member_ `FOnPCapLiveLinkSubjectUpdate OnPCapLiveLinkSubjectUpdate;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|LiveLink")` — Editor Only
- L133 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapLiveLinkSubjectAdded, FLiveLinkSubjectKey, Subject);` — Multicast delegate that will execute when a Live Link subject is added.
- L136 _public member_ `FOnPCapLiveLinkSubjectAdded OnPCapLiveLinkSubjectAdded;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|LiveLink")` — Editor Only
- L141 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapLiveLinkSubjectRemoved, FLiveLinkSubjectKey, Subject);` — Multicast delegate that will execute when a Live Link subject is removed.
- L144 _public member_ `FOnPCapLiveLinkSubjectRemoved OnPCapLiveLinkSubjectRemoved;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|LiveLink")` — Editor Only
- L149 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPCapLiveLinkSubjectEnableChanged, FLiveLinkSubjectKey, Subject, bool, NewEnabled);` — Multicast delegate that will execute when a Live Link subject's bIsEnabled member is modified in the Live Link panel.
- L152 _public member_ `FOnPCapLiveLinkSubjectEnableChanged OnPCapLiveLinkSubjectEnableChanged;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|LiveLink")` — Editor Only
- L157 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPCapTimecodeProviderChanged);` — Multicast delegate that will execute when the engine's Timecode provider is updated.
- L160 _public member_ `FOnPCapTimecodeProviderChanged OnPCapTimecodeProviderChanged;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|LiveLink")` — Editor Only
- L165 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPCapCustomTimestepProviderChanged);` — Multicast delegate that will execute when the engine's Timestep provider is updated.
- L168 _public member_ `FOnPCapCustomTimestepProviderChanged OnPCapCustomTimestepProviderChanged;` — `UPROPERTY(BlueprintAssignable, Category="Performance Capture|LiveLink")` — Editor Only
- L174 _protected prototype_ `void OnEngineInitComplete();`
- L176 _protected prototype_ `void InitiateDatabaseHelper();`
- L178 _protected prototype_ `void InitiateViewModelCollection();`
- L181 _protected member_ `TObjectPtr<UPerformanceCaptureDatabaseHelper> DatabaseHelper;` — `UPROPERTY(Transient)`
- L184 _protected member_ `TObjectPtr<UMVVMViewModelBase> PerformanceCaptureViewModel;` — `UPROPERTY(Transient)`
- L186 _protected member_ `FDelegateHandle EngineInitCompleteDelegate;`
- L188 _protected member_ `IAssetRegistry* AssetRegistry;`
- L192 _private member_ `TObjectPtr<UMVVMViewModelCollectionObject> ViewModelCollection;` — `UPROPERTY(Transient)`
- L194 _private prototype_ `void OnAssetRemoved(const FAssetData& InAssetData) const;`
- L196 _private prototype_ `void OnAssetRenamed(const FAssetData& InAssetData, const FString& NewName) const;`
- L198 _private prototype_ `void OnAssetAdded(const FAssetData& InAssetData) const;`
- L200 _private prototype_ `void OnObjectPropertyChanged(UObject* Asset, FPropertyChangedEvent& PropertyChangedEvent);`
- L202 _private prototype_ `void OnEditorUndo(const FTransactionContext& TransactionContext, bool Succeeded) const;`
- L204 _private prototype_ `void OnEditorRedo(const FTransactionContext& TransactionContext, bool Succeeded) const;`
- L206 _private prototype_ `void OnAssetOpened(UObject* Object, IAssetEditorInstance* Instance) const;`
- L208 _private prototype_ `void OnAssetClosed(UObject* Object, IAssetEditorInstance* Instance) const;`
- L210 _private prototype_ `void OnLiveLinkSubjectUpdated(FLiveLinkSubjectKey Subject, ELiveLinkSubjectState State) const;`
- L212 _private prototype_ `void OnLiveLinkSubjectAdded(FLiveLinkSubjectKey Subject) const;`
- L214 _private prototype_ `void OnLiveLinkSubjectRemoved(FLiveLinkSubjectKey Subject) const;`
- L216 _private prototype_ `void OnLiveLinkSubjectEnableChanged(FLiveLinkSubjectKey Subject, bool NewEnabled) const;`
- L218 _private prototype_ `void OnTimecodeProviderChanged() const;`
- L220 _private prototype_ `void OnCustomTimestepProviderChanged() const;`

#### Free symbols / members of external scopes

- L61 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapAssetRemoved, FAssetData, DeletedAsset);` — Multicast delegate that will execute when an asset is removed from the asset registry. Returns the FAssetData of the removed asset.
- L69 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPCapAssetRenamed, FAssetData, RenamedAsset, FString, OldName);` — Multicast delegate that will execute when an asset is renamed to the asset registry. Returns the FAssetData of the renamed asset.
- L77 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapAssetAdded, FAssetData, NewAsset);` — Multicast delegate that will execute when a new asset is added to the asset registry. Returns the FAssetData of new asset.
- L85 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapActorModified, AActor*, Actor);` — Multicast delegate that will execute when an actor is modified in the Level Editor. Returns the actor modified.
- L93 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapEditorUndo, bool, bSuccess);` — Multicast delegate that will execute when the user calls Undo. Returns success boolean.
- L101 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapEditorRedo, bool, bSuccess);` — Multicast delegate that will execute when the user calls Redo. Returns success boolean.
- L109 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapAssetEditorOpen, UObject*, Asset);` — Multicast delegate that will execute when an asset editor is opened. Returns the asset object that is opened.
- L117 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapAssetEditorClose, UObject*, Asset);` — Multicast delegate that will execute when an asset editor is closed. Returns the asset object that is closed.
- L125 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPCapLiveLinkSubjectUpdate, FLiveLinkSubjectKey, Subject, ELiveLinkSubjectState, State);` — Multicast delegate that will execute when a Live Link subject's state is updated.
- L133 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapLiveLinkSubjectAdded, FLiveLinkSubjectKey, Subject);` — Multicast delegate that will execute when a Live Link subject is added.
- L141 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPCapLiveLinkSubjectRemoved, FLiveLinkSubjectKey, Subject);` — Multicast delegate that will execute when a Live Link subject is removed.
- L149 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPCapLiveLinkSubjectEnableChanged, FLiveLinkSubjectKey, Subject, bool, NewEnabled);` — Multicast delegate that will execute when a Live Link subject's bIsEnabled member is modified in the Live Link panel.
- L157 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPCapTimecodeProviderChanged);` — Multicast delegate that will execute when the engine's Timecode provider is updated.
- L165 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPCapCustomTimestepProviderChanged);` — Multicast delegate that will execute when the engine's Timestep provider is updated.

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Private/PCapWorkflowCustomization.h` (Private)


#### struct `FMocapManagerPhase`  
`struct FMocapManagerPhase`  
_L14-42_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `FName PhaseName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MocapManager")` — Name to use for this phase. It should be unique among all the other phase names
- L28 _public member_ `TSoftObjectPtr<UTexture2D> Icon;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MocapManager")` — Icon to use on the phase button on the Mocap Manager UI
- L34 _public member_ `bool bIsEnabled = true;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MocapManager")` — Bool to determine if Mocap Manager should use this phase
- L40 _public member_ `TSoftClassPtr<UEditorUtilityWidget> WorkflowPhaseUIPanelClass;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MocapManager", meta = (GetAllowedClasses = "/Script/PerformanceCaptureWorkflow.PCapWorkflowCustomization:GetAllowedPanelWidgetClasses"))` — UI Panel to use for this phase. Must be of class defined by WorkflowPhaseUIBaseClass in DefaultPerformanceCaptureWorkflow.ini

#### class `UPCapWorkflowCustomization`  
`class UPCapWorkflowCustomization : public UPCapDataAsset`  
_L48-73_
- reflection: `UCLASS(Blueprintable, BlueprintType)`
- inherits: `UPCapDataAsset`
- desc: Data asset class to let users build a series of phases in Mocap Manager
- L54 _public member_ `TArray<FMocapManagerPhase> WorkflowPhases;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MocapManager")`
- L56 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPCapCustomizationModified);`
- L58 _public member_ `FOnPCapCustomizationModified OnPCapCustomizationModified;` — `UPROPERTY(BlueprintAssignable, Transient, Category="Performance Capture|Customization")`
- L62 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L69 _private prototype_ `static TArray<UClass*> GetAllowedPanelWidgetClasses();` — `UFUNCTION()`

#### Free symbols / members of external scopes

- L56 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPCapCustomizationModified);`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Private/Visualizers/PCapBoneVisualizer.h` (Private)


#### enum `EBoneVisualType`  
`enum class EBoneVisualType : uint8`  
_L13-17_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `Joint UMETA(DisplayName = "Joint")`
- L16 _public enumerator_ `Bone UMETA(DisplayName = "Bone")`

#### class `UPCapBoneVisualiser`  
`class UPCapBoneVisualiser : public UInstancedStaticMeshComponent`  
_L21-70_
- reflection: `UCLASS(ClassGroup=(PerformanceCapture), meta=(BlueprintSpawnableComponent), Transient, DisplayName = "PerformanceCaptureVisualizer")`
- inherits: `UInstancedStaticMeshComponent`
- desc: Instanced Static Mesh Component for drawing bones and joints on a Skinned Mesh component. Only usable with Actors that contain at least one Skinned Mesh component
- L27 _public prototype_ `UPCapBoneVisualiser(const FObjectInitializer& ObjectInitializer);` — Sets default values for this component's properties
- L30 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;` — Called every frame
- L33 _public prototype_ `TArray<FTransform> GetJointTransforms(USkinnedMeshComponent* InSkinnedMeshComponent) const;` — Get all the transforms from the Skinned Mesh component.
- L36 _public prototype_ `TArray<FTransform> GetBoneTransforms(USkinnedMeshComponent* InSkinnedMeshComponent) const;` — Get all the bones' transforms for drawing a joint (point to point mesh).
- L40 _public member_ `EBoneVisualType VisualizationType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PerformanceCapture|Visualization")` — Whether to draw joints along the length of the bone, or just at the pivot or scaled by the distance to the parent bone.
- L44 _public member_ `FLinearColor Color;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter="UpdateColor", Category="PerformanceCapture|Visualization")` — Color to use on the instanced static meshes. Can only be set during construction.
- L48 _public member_ `TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="PerformanceCapture|Visualization")` — Dynamic Material to use on the instanced static meshes.
- L55 _public prototype_ `void UpdateColor(FLinearColor NewColor);` — `UFUNCTION(BlueprintCallable, Category="PerformanceCapture|Visualization")` — Update the color for this bone visaulizer. @param NewColor New color to apply in the material.
- L59 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L64 _protected prototype_ `virtual void OnRegister() override;`
- L65 _protected prototype_ `virtual void OnUnregister() override;`
- L69 _private member_ `TObjectPtr<USkinnedMeshComponent> SkinnedMeshComponent;` — `UPROPERTY()`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Public/PCapMVVMResolver.h` (Public)


#### class `UPCapMVVMResolver`  
`class UPCapMVVMResolver : public UMVVMViewModelContextResolver`  
_L14-23_
- reflection: `UCLASS()`
- inherits: `UMVVMViewModelContextResolver`
- desc: Editor-only resolver class
- L20 _private prototype_ `virtual UObject* CreateInstance(const UClass* ExpectedType, const UUserWidget* UserWidget, const UMVVMView* View) const override;`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Public/PCapViewmodel.h` (Public)


#### class `UPCapViewmodel`  
`class UPCapViewmodel : public UMVVMViewModelBase`  
_L13-21_
- reflection: `UCLASS(Blueprintable, Abstract, DisplayName="PCap Viewmodel",meta = (ShowWorldContextPin))`
- inherits: `UMVVMViewModelBase`
- L20 _public prototype_ `void Initialize();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Performance Capture|Viewmodel")` — Initialise the viewmodel. Implemented in Blueprint.

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Public/PerformanceCapture.h` (Public)


#### class `FPerformanceCaptureModule`  
`class FPerformanceCaptureModule : public IModuleInterface`  
_L14-36_
- inherits: `IModuleInterface`
- L19 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _public prototype_ `void PluginButtonClicked();` — This function will be bound to Command (by default it will bring up plugin window)
- L26 _public member_ `static const FLazyName MessageLogName;` — Message Log Name for the PerformanceCapture module.
- L29 _private prototype_ `TSharedRef<class SDockTab> OnSpawnMocapManager(const class FSpawnTabArgs& SpawnTabArgs);`
- L31 _private prototype_ `void OnMainFrameCreationFinished(TSharedPtr<class SWindow> InRootWindow, bool bIsNewProjectWindow);`
- L33 _private member_ `TSharedPtr<class FUICommandList> PluginCommands;`
- L35 _private member_ `bool bEditorStartupInProgress = true;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PERFORMANCECAPTUREWORKFLOW_API`
- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCap, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCap, Log, All);`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Public/PerformanceCaptureCommands.h` (Public)


#### class `FPerformanceCaptureCommands`  
`class FPerformanceCaptureCommands : public TCommands<FPerformanceCaptureCommands>`  
_L9-23_
- inherits: `TCommands<FPerformanceCaptureCommands>`
- L13 _public function_ `FPerformanceCaptureCommands() : TCommands<FPerformanceCaptureCommands>(TEXT("PerformanceCapture"), NSLOCTEXT("Contexts", "PerformanceCapture", "PerformanceCaptureWorkflow Plugin"), NAME_None, FPerformanceCaptureStyle::GetStyleSetName())`
- L19 _public prototype_ `virtual void RegisterCommands() override;` — TCommands<> interface
- L22 _public member_ `TSharedPtr< FUICommandInfo > OpenPluginWindow;`

### `Plugins/VirtualProduction/PerformanceCaptureWorkflow/Source/PerformanceCaptureWorkflow/Public/PerformanceCaptureStyle.h` (Public)


#### class `FPerformanceCaptureStyle`  
`class FPerformanceCaptureStyle`  
_L12-36_
- L16 _public prototype_ `static void Initialize();`
- L18 _public prototype_ `static void Shutdown();`
- L21 _public prototype_ `static void ReloadTextures();` — reloads textures used by slate renderer
- L24 _public prototype_ `static const ISlateStyle& Get();` — @return The Slate style set for the editor
- L26 _public prototype_ `static FName GetStyleSetName();`
- L28 _public member_ `static FColor TypeColor;`
- L33 _private prototype_ `static TSharedRef< class FSlateStyleSet > Create();`
- L35 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleInstance;`
