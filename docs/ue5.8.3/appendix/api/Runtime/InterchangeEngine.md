# Runtime / InterchangeEngine

- module root: `Source/Runtime/Interchange/Engine`
- headers: 21; symbols: 737
- symbol kinds: class=39, delegate=17, enum=6, enumerator=31, externvar=3, function=56, macro=8, member=266, namespace=22, prototype=260, struct=22, typedef=7
- PrivateDependencyModuleNames: AssetRegistry, DeveloperSettings, Json, JsonUtilities, MeshDescription, SkeletalMeshDescription, SkeletalMeshUtilitiesCommon, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InterchangeCore

### `Source/Runtime/Interchange/Engine/Private/InterchangeEngineLogPrivate.h` (Private)


#### class `FScopeInterchangeTraceAsyncTask`  
`class FScopeInterchangeTraceAsyncTask`  
_L13-52_
- L16 _public function_ `FScopeInterchangeTraceAsyncTask(FString InTaskName) : TaskName(InTaskName)`
- L32 _public function_ `~FScopeInterchangeTraceAsyncTask()`
- L47 _private member_ `double StartTime = 0;`
- L48 _private member_ `int32 TaskID = 0;`
- L49 _private member_ `FString TaskName;`
- L50 _private member_ `const FString TraceAsyncGameThreadStr = "Ga`
- L51 _private member_ `const FString TraceAsyncBackgroundThreadStr = "Ba`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeEngine, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeEngine, Log, All);`
- L9 _macro_ `#define INTERCHANGE_TRACE_ASYNCHRONOUS_TASK_ENABLED 0`
- L54 _macro_ `#define INTERCHANGE_TRACE_ASYNCHRONOUS_TASK(TaskName) \`

### `Source/Runtime/Interchange/Engine/Private/Tasks/InterchangeTaskCompletion.h` (Private)


#### class `UE::Interchange::FTaskPreCompletion_GameThread`  
`class FTaskPreCompletion_GameThread : public FInterchangeTaskBase`  
_L15-33_
- inherits: `FInterchangeTaskBase`
- L18 _private member_ `UInterchangeManager* InterchangeManager;`
- L19 _private member_ `TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> WeakAsyncHelper;`
- L21 _public function_ `FTaskPreCompletion_GameThread(UInterchangeManager* InInterchangeManager, TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> InAsyncHelper) : InterchangeManager(InInterchangeManager) , WeakAsyncHelper(InAsyncHelper)`
- L27 _public function_ `virtual EInterchangeTaskThread GetTaskThread() const override`
- L32 _public prototype_ `virtual void Execute() override;`

#### class `UE::Interchange::FTaskCompletion_GameThread`  
`class FTaskCompletion_GameThread : public FInterchangeTaskBase`  
_L35-53_
- inherits: `FInterchangeTaskBase`
- L38 _private member_ `UInterchangeManager* InterchangeManager;`
- L39 _private member_ `TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> WeakAsyncHelper;`
- L41 _public function_ `FTaskCompletion_GameThread(UInterchangeManager* InInterchangeManager, TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> InAsyncHelper) : InterchangeManager(InInterchangeManager) , WeakAsyncHelper(InAsyncHelper)`
- L47 _public function_ `virtual EInterchangeTaskThread GetTaskThread() const override`
- L52 _public prototype_ `virtual void Execute() override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Interchange` (scope `UE`)

### `Source/Runtime/Interchange/Engine/Private/Tasks/InterchangeTaskCreateSceneObjects.h` (Private)


#### class `UE::Interchange::FTaskCreateSceneObjects_GameThread`  
`class FTaskCreateSceneObjects_GameThread : public FInterchangeTaskBase`  
_L20-38_
- inherits: `FInterchangeTaskBase`
- L23 _private member_ `FString PackageBasePath;`
- L24 _private member_ `int32 SourceIndex;`
- L25 _private member_ `TWeakPtr<FImportAsyncHelper> WeakAsyncHelper;`
- L26 _private member_ `TArray<UInterchangeFactoryBaseNode*> FactoryNodes;`
- L27 _private member_ `const UClass* FactoryClass;`
- L30 _public prototype_ `explicit FTaskCreateSceneObjects_GameThread(const FString& InPackageBasePath, const int32 InSourceIndex, TWeakPtr<FImportAsyncHelper> InAsyncHelper, TArrayView<UInterchangeFactoryBaseNode*> InNodes, const UClass* InFactoryClass);`
- L32 _public function_ `virtual EInterchangeTaskThread GetTaskThread() const override`
- L37 _public prototype_ `virtual void Execute() override;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Interchange` (scope `UE`)

### `Source/Runtime/Interchange/Engine/Private/Tasks/InterchangeTaskImportObject.h` (Private)


#### class `UE::Interchange::FTaskImportObject_GameThread`  
`class FTaskImportObject_GameThread : public FInterchangeTaskBase`  
_L18-45_
- inherits: `FInterchangeTaskBase`
- desc: This task create UPackage and UObject, Cook::PackageTracker::NotifyUObjectCreated is not thread safe, so we need to create the packages on the main thread
- L21 _private member_ `FString PackageBasePath;`
- L22 _private member_ `int32 SourceIndex;`
- L23 _private member_ `TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> WeakAsyncHelper;`
- L24 _private member_ `UInterchangeFactoryBaseNode* FactoryNode;`
- L25 _private member_ `const UClass* FactoryClass;`
- L28 _public function_ `FTaskImportObject_GameThread(const FString& InPackageBasePath, const int32 InSourceIndex, TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> InAsyncHelper, UInterchangeFactoryBaseNode* InFactoryNode, const UClass* InFactoryClass) : PackageBasePath(InPackageBasePath) , SourceIndex(InSourceIndex) , WeakAsyncHelper(InAsyncHelper) , FactoryNode(InFactoryNode) , FactoryClass(InFactoryClass)`
- L39 _public function_ `virtual EInterchangeTaskThread GetTaskThread() const override`
- L44 _public prototype_ `virtual void Execute() override;`

#### class `UE::Interchange::FTaskImportObject_Async`  
`class FTaskImportObject_Async : public FInterchangeTaskBase`  
_L47-77_
- inherits: `FInterchangeTaskBase`
- L50 _private member_ `FString PackageBasePath;`
- L51 _private member_ `int32 SourceIndex;`
- L52 _private member_ `TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> WeakAsyncHelper;`
- L53 _private member_ `UInterchangeFactoryBaseNode* FactoryNode;`
- L56 _public function_ `FTaskImportObject_Async(const FString& InPackageBasePath, const int32 InSourceIndex, TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> InAsyncHelper, UInterchangeFactoryBaseNode* InFactoryNode) : PackageBasePath(InPackageBasePath) , SourceIndex(InSourceIndex) , WeakAsyncHelper(InAsyncHelper) , FactoryNode(InFactoryNode)`
- L65 _public function_ `virtual EInterchangeTaskThread GetTaskThread() const override`
- L76 _public prototype_ `virtual void Execute() override;`

#### class `UE::Interchange::FTaskImportObjectFinalize_GameThread`  
`class FTaskImportObjectFinalize_GameThread : public FInterchangeTaskBase`  
_L82-107_
- inherits: `FInterchangeTaskBase`
- desc: This task create UPackage and UObject, Cook::PackageTracker::NotifyUObjectCreated is not thread safe, so we need to create the packages on the main thread
- L85 _private member_ `FString PackageBasePath;`
- L86 _private member_ `int32 SourceIndex;`
- L87 _private member_ `TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> WeakAsyncHelper;`
- L88 _private member_ `UInterchangeFactoryBaseNode* FactoryNode;`
- L89 _private member_ `const UClass* FactoryClass;`
- L92 _public function_ `FTaskImportObjectFinalize_GameThread(const FString& InPackageBasePath, const int32 InSourceIndex, TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> InAsyncHelper, UInterchangeFactoryBaseNode* InFactoryNode) : PackageBasePath(InPackageBasePath) , SourceIndex(InSourceIndex) , WeakAsyncHelper(InAsyncHelper) , FactoryNode(InFactoryNode)`
- L101 _public function_ `virtual EInterchangeTaskThread GetTaskThread() const override`
- L106 _public prototype_ `virtual void Execute() override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Interchange` (scope `UE`)

### `Source/Runtime/Interchange/Engine/Private/Tasks/InterchangeTaskParsing.h` (Private)


#### class `UE::Interchange::FTaskParsing`  
`class FTaskParsing : public FInterchangeTaskBase`  
_L16-36_
- inherits: `FInterchangeTaskBase`
- L19 _private member_ `UInterchangeManager* InterchangeManager;`
- L20 _private member_ `TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> WeakAsyncHelper;`
- L22 _public function_ `FTaskParsing(UInterchangeManager* InInterchangeManager, TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> InAsyncHelper) : InterchangeManager(InInterchangeManager) , WeakAsyncHelper(InAsyncHelper)`
- L29 _public function_ `virtual EInterchangeTaskThread GetTaskThread() const override`
- L35 _public prototype_ `virtual void Execute() override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Interchange` (scope `UE`)

### `Source/Runtime/Interchange/Engine/Private/Tasks/InterchangeTaskPipeline.h` (Private)


#### class `UE::Interchange::FTaskPipeline`  
`class FTaskPipeline : public FInterchangeTaskBase`  
_L17-52_
- inherits: `FInterchangeTaskBase`
- L20 _private member_ `TWeakObjectPtr<UInterchangePipelineBase> PipelineBase;`
- L21 _private member_ `TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> WeakAsyncHelper;`
- L23 _public function_ `FTaskPipeline(TWeakObjectPtr<UInterchangePipelineBase> InPipelineBase, TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> InAsyncHelper) : PipelineBase(InPipelineBase) , WeakAsyncHelper(InAsyncHelper)`
- L29 _public function_ `virtual EInterchangeTaskThread GetTaskThread() const override`
- L51 _public prototype_ `virtual void Execute() override;`

#### class `UE::Interchange::FTaskWaitAssetCompilation_GameThread`  
`class FTaskWaitAssetCompilation_GameThread : public FInterchangeTaskBase`  
_L55-75_
- inherits: `FInterchangeTaskBase`
- desc: We want to be sure any asset compilation is finish before calling subsequents tasks
- L58 _private member_ `int32 SourceIndex;`
- L59 _private member_ `TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> WeakAsyncHelper;`
- L62 _public function_ `FTaskWaitAssetCompilation_GameThread(int32 InSourceIndex, TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> InAsyncHelper) : SourceIndex(InSourceIndex) , WeakAsyncHelper(InAsyncHelper)`
- L68 _public function_ `virtual EInterchangeTaskThread GetTaskThread() const override`
- L74 _public prototype_ `virtual void Execute() override;`

#### class `UE::Interchange::FTaskPostImport_GameThread`  
`class FTaskPostImport_GameThread : public FInterchangeTaskBase`  
_L77-96_
- inherits: `FInterchangeTaskBase`
- L80 _private member_ `int32 SourceIndex;`
- L81 _private member_ `TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> WeakAsyncHelper;`
- L84 _public function_ `FTaskPostImport_GameThread(int32 InSourceIndex, TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> InAsyncHelper) : SourceIndex(InSourceIndex) , WeakAsyncHelper(InAsyncHelper)`
- L90 _public function_ `virtual EInterchangeTaskThread GetTaskThread() const override`
- L95 _public prototype_ `virtual void Execute() override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Interchange` (scope `UE`)

### `Source/Runtime/Interchange/Engine/Private/Tasks/InterchangeTaskTranslator.h` (Private)


#### class `UE::Interchange::FTaskTranslator`  
`class FTaskTranslator : public FInterchangeTaskBase`  
_L15-40_
- inherits: `FInterchangeTaskBase`
- L18 _private member_ `int32 SourceIndex = INDEX_NONE;`
- L19 _private member_ `TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> WeakAsyncHelper;`
- L22 _public function_ `FTaskTranslator(int32 InSourceIndex, TWeakPtr<FImportAsyncHelper, ESPMode::ThreadSafe> InAsyncHelper) : SourceIndex(InSourceIndex) , WeakAsyncHelper(InAsyncHelper)`
- L28 _public function_ `virtual EInterchangeTaskThread GetTaskThread() const override`
- L39 _public prototype_ `virtual void Execute();`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Interchange` (scope `UE`)

### `Source/Runtime/Interchange/Engine/Public/InterchangeAnalyticsHandlerBase.h` (Public)


#### enum `EInterchangeAnalyticsDefaultCategory`  
`enum class EInterchangeAnalyticsDefaultCategory : uint8`  
_L35-50_
- desc: If you add or remove from this enum, make sure to update the corresponding strings in UInterchangeAnalyticsHandlerBase::GetDefaultAnalyticsCategoryName.
- L37 _public enumerator_ `NotSpecified = 0`
- L38 _public enumerator_ `Models`
- L39 _public enumerator_ `Scenes`
- L40 _public enumerator_ `Materials`
- L41 _public enumerator_ `Textures`
- L42 _public enumerator_ `Sounds`
- L43 _public enumerator_ `Meshes`
- L44 _public enumerator_ `StaticMeshes`
- L45 _public enumerator_ `SkeletalMeshesAndAnimations`
- L46 _public enumerator_ `GeometryCaches`
- L47 _public enumerator_ `Grooms`
- L48 _public enumerator_ `Physics`
- L49 _public enumerator_ `InterchangeAnalyticsCategory_COUNT`

#### struct `FInterchangeImportResultAnalyticsInfo`  
`struct FInterchangeImportResultAnalyticsInfo`  
_L52-65_
- L54 _public member_ `bool bCancel;`
- L55 _public member_ `int32 UniqueId;`
- L57 _public member_ `TNotNull<const UInterchangeSourceData*> PrimarySourceData;`
- L58 _public member_ `const UInterchangeSourceNode* PrimarySourceNode;`
- L60 _public member_ `TOptional<const UInterchangeResultsContainer*> AssetImportResultsContainer;`
- L61 _public member_ `TOptional<const UInterchangeResultsContainer*> SceneImportResultsContainer;`
- L63 _public member_ `TMap<int32, TArray<TObjectPtr<UObject>>> ImportedAssetsPerSourceIndex;`
- L64 _public member_ `TMap<int32, TArray<TObjectPtr<UObject>>> ImportedSceneObjectsPerSourceIndex;`

#### class `UInterchangeAnalyticsHandlerBase`  
`class UInterchangeAnalyticsHandlerBase : public UObject`  
_L76-144_
- reflection: `UCLASS(BlueprintType, Blueprintable, Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: This is the base class implementation for the Interchange Analytics. This will NOT collect any analytics BY DESIGN. DO NOT MAKE CHANGES TO THE IMPLEMENTATIONS OF THE FUNCTIONS FOR THIS CLASS. See UInterchangeAnalyticsHandlerDefault instead for the default implementation. Interchange Manager exposes API to set the TSoftClassPtr for a class to use to collect Analytics. By default InterchangeAnalyticsModule registers UInterchangeAnalyticsHandlerDefault as the Analytics Handler Class.
- L81 _public prototype_ `static FAnalyticsEventAttribute CreateAnalyticsIDAttribute(FGuid AnalyticsID);`
- L83 _public prototype_ `static FString GetDefaultAnalyticsCategoryName(EInterchangeAnalyticsDefaultCategory DefaultCategory);`
- L86 _protected prototype_ `static FString GetPipelineAnalyticsEventIdentifier();`
- L88 _protected prototype_ `static FString GetImportResultEventIdentifier();`
- L94 _public prototype_ `void SetGUID(const FGuid& InGUID);` — Can only be set once per instance of the Analytics Handler.
- L99 _public prototype_ `void Append(const FString& Identifier, const TArray<FAnalyticsEventAttribute>& ToAdd);` — Adds an array of attributes to the event identifier in a thread safe manner.
- L104 _public prototype_ `void Add(const FString& Identifier, const FAnalyticsEventAttribute& Entry);` — Add the analytics attribute to an event identifier in a thread safe manner.
- L109 _public prototype_ `void Clear(const FString& Identifier);` — Clears accumulated attributes for an event identifier. Useful in Translator Analytic Events context.
- L114 _public prototype_ `void Flush();` — Send Accumulated Analytics.
- L119 _public prototype_ `virtual void Send(const TArray<UInterchangePipelineBase*>& Pipelines, const int32 AsyncHelperUniqueId) PURE_VIRTUAL(UInterchangeAnalyticsHandlerBase::Send, ) virtual void Send(const FInterchangeImportResultAnalyticsInfo& ImportResultAnalyticsInfo) PURE_VIRTUAL(UInterchangeAnalyticsHandlerBase::Send, ) virtual FAnalyticsEventAttribute GetAnalyticsIDAttribute() const;` — Send Pipelines Analytics.
- L143 _private member_ `FGuid AnalyticsID;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API INTERCHANGEENGINE_API`

### `Source/Runtime/Interchange/Engine/Public/InterchangeAssetImportData.h` (Public)


#### class `UInterchangeAssetImportData`  
`class UInterchangeAssetImportData : public UAssetImportData`  
_L20-207_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UAssetImportData`
- L25 _public prototype_ `virtual void PostLoad() override;`
- L26 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L30 _public prototype_ `virtual bool ConvertAssetImportDataToNewOwner(UObject* Owner) override;`
- L37 _public function_ `FString ScriptGetFirstFilename() const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | AssetImportData")` — Return the first filename stored in this data. The resulting filename will be absolute (that is, not relative to the asset).
- L51 _public function_ `TArray<FString> ScriptExtractFilenames() const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | AssetImportData")` — Extract all the (resolved) filenames.
- L65 _public function_ `TArray<FString> ScriptExtractDisplayLabels() const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | AssetImportData")` — Extract all the filename labels.
- L78 _public function_ `virtual void AppendAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) override` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L88 _public function_ `virtual void AppendAssetRegistryTags(FAssetRegistryTagsContext Context) override` — This function adds tags to the asset registry.
- L115 _public member_ `FSoftObjectPath SceneImportAsset;` — `UPROPERTY(EditAnywhere, Category = "Interchange | AssetImportData")` — On a level import, set to the UInterchangeSceneImportAsset created during the import.
- L118 _public function_ `static UInterchangeAssetImportData* GetFromObject(UObject* Object)` — Returns a pointer to the UInterchangeAssetImportData referred to by the input object, if applicable.
- L138 _public member_ `FString NodeUniqueID;` — `UPROPERTY(VisibleAnywhere, Category = "Interchange | AssetImportData")` — The Node UID passed to the factory that existed in the graph that was used to create this asset.
- L142 _public prototype_ `UInterchangeBaseNodeContainer* GetNodeContainer() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | AssetImportData")`
- L145 _public prototype_ `void SetNodeContainer(UInterchangeBaseNodeContainer* InNodeContainer) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | AssetImportData")`
- L151 _public prototype_ `TArray<UObject*> GetPipelines() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | AssetImportData")` — Returns Array of non-null pipelines
- L154 _public prototype_ `int32 GetNumberOfPipelines() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | AssetImportData")`
- L157 _public prototype_ `void SetPipelines(const TArray<UObject*>& InPipelines);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | AssetImportData")`
- L161 _public prototype_ `const UInterchangeBaseNode* GetStoredNode(const FString& InNodeUniqueId) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | AssetImportData")`
- L164 _public prototype_ `UInterchangeFactoryBaseNode* GetStoredFactoryNode(const FString& InNodeUniqueId) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | AssetImportData")`
- L167 _public prototype_ `const UInterchangeTranslatorSettings* GetTranslatorSettings() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | AssetImportData")`
- L170 _public prototype_ `void SetTranslatorSettings(UInterchangeTranslatorSettings* TranslatorSettings) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | AssetImportData")`
- L173 _public prototype_ `void BackupSourceData() const;` — Won't overwrite an existing backup. Backup has to be cleared before a new one can be stored.
- L174 _public prototype_ `void ClearBackupSourceData() const;`
- L175 _public prototype_ `void ReinstateBackupSourceData();`
- L179 _private member_ `TObjectPtr<UInterchangeBaseNodeContainer> NodeContainer_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use GetNodeContainer/SetNodeContainer instead."))`
- L181 _private member_ `TArray<TObjectPtr<UObject>> Pipelines_DEPRECATED;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use GetPipelines/SetPipelines instead."))`
- L184 _private member_ `mutable TObjectPtr<UInterchangeBaseNodeContainer> TransientNodeContainer;` — `UPROPERTY(Transient)`
- L187 _private member_ `mutable TArray<TObjectPtr<UObject>> TransientPipelines;` — `UPROPERTY(Transient)`
- L190 _private member_ `mutable TObjectPtr<UInterchangeTranslatorSettings> TransientTranslatorSettings;` — `UPROPERTY(Transient)`
- L192 _private prototype_ `void ProcessContainerCache() const;`
- L193 _private prototype_ `void ProcessPipelinesCache() const;`
- L194 _private prototype_ `void ProcessDeprecatedData() const;`
- L195 _private prototype_ `void ProcessTranslatorCache() const;`
- L196 _private member_ `mutable TArray64<uint8> CachedNodeContainer;`
- L197 _private member_ `mutable TArray<TPair<FString, FString>> CachedPipelines;` — Class, Data(serialized JSON) pair
- L198 _private member_ `mutable FCustomVersionContainer CachedCustomVersions;` — Custom versions of the archive we deserialized from, to help us deserialize our cached data
- L199 _private member_ `mutable TPair<FString, FString> CachedTranslatorSettings;`
- L203 _private member_ `mutable FAssetImportInfo SourceDataBackup;` — Source file data describing the files that were used to import this asset. Temporary, Primary usage is for Re-import cancellations.
- L206 _private prototype_ `static TMap<FString, UClass*> GetPipelineClassPerName();` — #todo_interchange: TODO: Move to as a IntercnageManager utility method

#### class `UInterchangeAssetImportDataConverterBase`  
`class UInterchangeAssetImportDataConverterBase : public UObject`  
_L213-245_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Base class to create an asset import data converter.
- L219 _public function_ `virtual bool CanConvertClass(const UClass* SourceClass, const UClass* DestinationClass) const` — Converter must return which class they can convert to and from UInterchangeAssetImportData.
- L230 _public function_ `virtual bool ConvertImportData(UObject* Asset, const FString& TargetExtension) const` — Convert the asset import data from the one that is in the Object to one that supports the target extension (for example, legacy FBX to Interchange or vice-versa) The function should return true only if it has converted the asset import data, or false otherwise. The system will call all objects that derive from this class until one converts the data. @Param Asset - Represent an asset that have a member AssetImportData (StaticMesh, SkeletalMesh, Texture....)
- L241 _public function_ `virtual bool ConvertImportData(const UObject* SourceImportData, const UClass* DestinationClass, UObject** DestinationImportData) const` — Convert the asset import data from the source to the destination. The function should return true only if it has convert the asset import data, false otherwise. The system will call all object deriving from this class until one convert the data.

### `Source/Runtime/Interchange/Engine/Public/InterchangeBlueprintPipelineBase.h` (Public)


#### class `UInterchangeBlueprintPipelineBase`  
`class UInterchangeBlueprintPipelineBase : public UBlueprint`  
_L14-25_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UBlueprint`
- L19 _public function_ `UInterchangeBlueprintPipelineBase()`

### `Source/Runtime/Interchange/Engine/Public/InterchangeEditorUtilitiesBase.h` (Public)


#### class `UInterchangeEditorUtilitiesBase`  
`class UInterchangeEditorUtilitiesBase : public UObject`  
_L11-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L16 _public function_ `virtual bool SaveAsset(UObject* Asset) const`
- L21 _public function_ `virtual bool IsRuntimeOrPIE() const`
- L30 _public function_ `virtual bool ClearEditorSelection() const`

### `Source/Runtime/Interchange/Engine/Public/InterchangeEngineFwd.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Interchange` (scope `UE`)
- L13 _typedef_ `using FAssetImportResultRef = TSharedRef< FImportResult, ESPMode::ThreadSafe >;` (scope `UE::Interchange`)
- L14 _typedef_ `using FSceneImportResultRef = TSharedRef< FImportResult, ESPMode::ThreadSafe >;` (scope `UE::Interchange`)

### `Source/Runtime/Interchange/Engine/Public/InterchangeFilePickerBase.h` (Public)


#### struct `FInterchangeFilePickerParameters`  
`struct FInterchangeFilePickerParameters`  
_L13-36_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `bool bAllowMultipleFiles = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | File Picker")` — If true, the user will be able to select multiple files.
- L23 _public member_ `FText Title = FText();` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | File Picker")` — If not empty, this will override the default title.
- L27 _public member_ `FString DefaultPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | File Picker")` — Set the default open path that the dialog will show to the user.
- L31 _public member_ `bool bShowAllFactoriesExtension = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | File Picker")` — If true, the user will be able to select any unreal editor factory + interchange file types.
- L35 _public member_ `TArray<FString> ExtraFormats;` — `UPROPERTY(EditAnywhere, Category = "Interchange | File Picker")` — Add some extension to the picker. Format text item that way TEXT("fbx;Filmbox")

#### class `UInterchangeFilePickerBase`  
`class UInterchangeFilePickerBase : public UObject`  
_L39-90_
- reflection: `UCLASS(Abstract, BlueprintType, Blueprintable, MinimalAPI)`
- inherits: `UObject`
- L49 _public prototype_ `bool ScriptedFilePickerForTranslatorAssetType(const EInterchangeTranslatorAssetType TranslatorAssetType, const FInterchangeFilePickerParameters& Parameters, TArray<FString>& OutFilenames);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interchange | Utilities")` — Non-virtual helper that allows Blueprint to implement an event-based function to implement FilePickerForTranslatorAssetType().
- L52 _public function_ `bool ScriptedFilePickerForTranslatorAssetType_Implementation(const EInterchangeTranslatorAssetType TranslatorAssetType, const FInterchangeFilePickerParameters& Parameters, TArray<FString>& OutFilenames)` — The default implementation, which is called if the Blueprint does not have any implementation, calls the virtual FilePickerForTranslatorAssetType().
- L62 _public prototype_ `bool ScriptedFilePickerForTranslatorType(const EInterchangeTranslatorType TranslatorType, const FInterchangeFilePickerParameters& Parameters, TArray<FString>& OutFilenames);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interchange | Utilities")` — Non-virtual helper that allows Blueprint to implement an event-based function to implement FilePickerForTranslatorType().
- L65 _public function_ `bool ScriptedFilePickerForTranslatorType_Implementation(const EInterchangeTranslatorType TranslatorAssetType, const FInterchangeFilePickerParameters& Parameters, TArray<FString>& OutFilenames)` — The default implementation, which is called if the Blueprint does not have any implementation, calls the virtual FilePickerForTranslatorType().
- L80 _protected function_ `virtual bool FilePickerForTranslatorAssetType(const EInterchangeTranslatorAssetType TranslatorAssetType, const FInterchangeFilePickerParameters& Parameters, TArray<FString>& OutFilenames)` — This function must set OutFilename with a valid file that can be import to create the specified TranslatorAssetType. We expect the user to see a file picker dialog when the editor is available. @Return - true if OutFilename was set with a valid file path, or false otherwise.
- L88 _protected function_ `virtual bool FilePickerForTranslatorType(const EInterchangeTranslatorType TranslatorType, const FInterchangeFilePickerParameters& Parameters, TArray<FString>& OutFilenames)` — This function must set OutFilename with a valid file that can be import to create the specified TranslatorType. We expect the user to see a file picker dialog when the editor is available. @Return - true if OutFilename was set with a valid file path, or false otherwise.

### `Source/Runtime/Interchange/Engine/Public/InterchangeImportCommon.h` (Public)


#### class `UE::Interchange::FFactoryCommon`  
`class FFactoryCommon`  
_L30-176_
- desc: All the code we cannot put in the base factory class because of dependencies (like Engine dep) Will be available here.
- L58 _public prototype_ `static UAssetImportData* UpdateImportAssetData(FUpdateImportAssetDataParameters& Parameters);` — Update the AssetImportData source file of the specified asset in the parameters. Also update the node container and the node unique id. If the AssetImportData is null it will create one. If the AssetImportData is not an UInterchangeAssetImportData it will create a new one. @return The source data that should be stored on the asset or nullptr if a parameter is invalid
- L66 _public prototype_ `static UAssetImportData* UpdateImportAssetData(FUpdateImportAssetDataParameters& Parameters, TFunctionRef<void(UInterchangeAssetImportData*)> CustomFileSourceUpdate);` — Update the AssetImportData of the specified asset in the parameters. Also update the node container and the node unique id. If the AssetImportData is null it will create one. If the AssetImportData is not an UInterchangeAssetImportData it will create a new one. The file source update is done by calling the function parameter CustomFileSourceUpdate, so its the client responsability to properly update the file source. @return The source data that should be stored on the asset or nullptr if a parameter is invalid
- L88 _public prototype_ `static UAssetImportData* SetImportAssetData(FSetImportAssetDataParameters& Parameters);` — Set the AssetImportData source file of the specified asset in the parameters. Also update the node container and the node unique id. If the AssetImportData is null it will create one. If the AssetImportData is not an UInterchangeAssetImportData it will create a new one. @return The source data that should be stored on the asset or nullptr if a parameter is invalid
- L94 _public prototype_ `static bool GetSourceFilenames(const UAssetImportData* AssetImportData, TArray<FString>& OutSourceFilenames);` — Fills the OutSourceFilenames array with the list of source files contained in the asset source data. Returns true if the operation was successful.
- L99 _public prototype_ `static void BackupSourceData(const UAssetImportData* AssetImportData);` — Backups the SourceData. Primary usage for re-instating SourceData on Re-Import cancellation.
- L104 _public prototype_ `static void ReinstateSourceData(UAssetImportData* AssetImportData);` — Reinstates the backedup SourceData. Primary usage for re-instating SourceData on Re-Import cancellation.
- L109 _public prototype_ `static void ClearBackupSourceData(const UAssetImportData* AssetImportData);` — Clears the backedup SourceData. Primary usage for re-instating SourceData on Re-Import cancellation.
- L114 _public prototype_ `static bool SetSourceFilename(UAssetImportData* AssetImportData, const FString& SourceFilename, int32 SourceIndex, const FString& SourceLabel = FString());` — Sets the SourceFileName value at the specified index.
- L119 _public prototype_ `static bool SetReimportSourceIndex(const UObject* Object, UAssetImportData* AssetImportData, int32 SourceIndex);` — Set the object's reimport source at the specified index value.
- L126 _public prototype_ `static void ApplyReimportStrategyToAsset(UObject* Asset , const UInterchangeFactoryBaseNode* PreviousAssetNode , const UInterchangeFactoryBaseNode* CurrentAssetNode , UInterchangeFactoryBaseNode* PipelineAssetNode);` — Apply the current strategy to the PipelineAssetNode
- L141 _public prototype_ `static UObject* GetObjectToReimport(UInterchangeFactoryBase* Factory, UObject* ReimportObject, const UInterchangeFactoryBaseNode& FactoryNode, const FString& PackageName, const FString& AssetName, const FString& SubPathString = FString());` — If the ReimportObject is a UInterchangeSceneImportAsset, returns the UObject which asset path is //PackageName.AssetName[:SubPathString]. Returns ReimportObject otherwise. @param ReimportObject: Object that a reimport has been initialized from @param FactoryNode: Factory node being reimported @param PackageName: Package path of the actual object to reimport @param AssetName: Asset name of the actual object to reimport @param SubPathString: Optional subobject name
- L152 _public prototype_ `static const UInterchangeFactoryBaseNode* GetFactoryNode(UObject* ReimportObject, const FString& PackageName, const FString& AssetName, const FString& SubPathString = FString());` — If the ReimportObject is a UInterchangeSceneImportAsset, returns the factory node associated with the asset which path is //PackageName.AssetName[:SubPathString]. Returns nullptr otherwise. @param ReimportObject: Object that a reimport has been initialized from @param PackageName: Package path of the actual object to reimport @param AssetName: Asset name of the actual object to reimport @param SubPathString: Optional subobject name
- L171 _public prototype_ `static bool CanProceedWithFactoryNode(UInterchangeFactoryBaseNode& FactoryNode, UObject* ReimportObject, UObject* ObjectToReimport, const FString& PackageName, const FString& AssetName, const FString& SubPathString = FString());` — Evaluates whether or not a factory should be called on a factory node in a given reimport context. @param FactoryNode: Factory node to evaluate @param ReimportObject: Object a reimport has been initialized from @param ObjectToReimport: Actual object to reimport @param PackageName: Package path of the object associated with the factory node to reimport @param AssetName: Asset name of the object associated with the factory node to reimport @param SubPathString: Optional subobject name Returns: - true if it is an import. ReimportObject is null. - true if, based on its path, object associated with the factory node was not part of the previous import. - true if factory node was part of the previous import and ObjectToReimport is null but FactoryNode has been flagged as required for the reimport - true ObjectToReimport is not null - false otherwise @note The path of the missing associated object will be set on the factory node if ObjectToReimport is null
- L175 _public prototype_ `static UObject* AsyncFindObject(UInterchangeFactoryBaseNode* FactoryNode, const UClass* FactoryClass, UObject* Parent, const FString& AssetName);` — Factory helper use to find the object we have create in the game thread when we do the async part of the factory import.

#### struct `UE::Interchange::FFactoryCommon::FUpdateImportAssetDataParameters`  
`struct FUpdateImportAssetDataParameters`  
_L34-51_
- L36 _public member_ `UObject* AssetImportDataOuter = nullptr;`
- L37 _public member_ `UAssetImportData* AssetImportData = nullptr;`
- L38 _public member_ `const UInterchangeSourceData* SourceData = nullptr;`
- L39 _public member_ `FString NodeUniqueID;`
- L40 _public member_ `UInterchangeBaseNodeContainer* NodeContainer;`
- L41 _public member_ `const TArray<UObject*> Pipelines;`
- L42 _public member_ `const UInterchangeTranslatorBase* Translator;`
- L44 _public prototype_ `FUpdateImportAssetDataParameters(UObject* InAssetImportDataOuter , UAssetImportData* InAssetImportData , const UInterchangeSourceData* InSourceData , FString InNodeUniqueID , UInterchangeBaseNodeContainer* InNodeContainer , const TArray<UObject*>& InPipelines , const UInterchangeTranslatorBase* InTranslator);`

#### struct `UE::Interchange::FFactoryCommon::FSetImportAssetDataParameters`  
`struct FSetImportAssetDataParameters : public FUpdateImportAssetDataParameters`  
_L69-81_
- inherits: `FUpdateImportAssetDataParameters`
- L72 _public member_ `TArray<FAssetImportInfo::FSourceFile> SourceFiles;` — Allow the factory to provide is own list of source files.
- L74 _public prototype_ `FSetImportAssetDataParameters(UObject* InAssetImportDataOuter , UAssetImportData* InAssetImportData , const UInterchangeSourceData* InSourceData , FString InNodeUniqueID , UInterchangeBaseNodeContainer* InNodeContainer , const TArray<UObject*>& InPipelines , const UInterchangeTranslatorBase* InTranslator);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API INTERCHANGEENGINE_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Interchange` (scope `UE`)

### `Source/Runtime/Interchange/Engine/Public/InterchangeImportReset.h` (Public)


#### struct `FResetPhaseDelegates`  
`struct FResetPhaseDelegates`  
_L29-34_
- L31 _public member_ `FOnFilterFactoryNodeDelegate OnNodeFilter;`
- L32 _public member_ `FOnNodeProcessedDelegate OnNodeProcessed;`
- L33 _public member_ `FOnResetPhaseCompletedDelegate OnCompleted;`

#### struct `FInterchangeResetContextData`  
`struct FInterchangeResetContextData`  
_L37-40_
- desc: Used for storing objects that might be needed to be referenced later.
- L39 _public member_ `TMap<const UInterchangeFactoryBaseNode*, TArray<TObjectPtr<UObject>>> ObjectsSpawnedDuringReset;`

#### class `FInterchangeResetParameters`  
`class FInterchangeResetParameters`  
_L42-79_
- L52 _public prototype_ `FInterchangeResetParameters(const UInterchangeSceneImportAsset* InSceneImportAsset);`
- L53 _public prototype_ `FInterchangeResetParameters(const UInterchangeSceneImportAsset* InSceneImportAsset, TUniquePtr<FInterchangeResetContextData> InResetContextData);`
- L54 _public prototype_ `~FInterchangeResetParameters();`
- L56 _public prototype_ `void AddObjectInstanceToReset(const UInterchangeFactoryBaseNode* FactoryNode, UObject* ObjectToReset);`
- L58 _public prototype_ `void SetupFactoryNode(const UInterchangeFactoryBaseNode* FactoryNode);`
- L59 _public prototype_ `TObjectPtr<UInterchangeFactoryBase> GetFactoryForNode(const UInterchangeFactoryBaseNode* FactoryNode) const;`
- L60 _public prototype_ `TArray<TObjectPtr<UObject>> GetObjectInstancesForFactoryNode(const UInterchangeFactoryBaseNode* FactoryNode);`
- L63 _public prototype_ `const UInterchangeBaseNodeContainer* GetBaseNodeContainer() const;`
- L64 _public prototype_ `const UInterchangeSceneImportAsset* GetSceneImportAsset() const;`
- L65 _public prototype_ `const UInterchangeResultsContainer* GetResultsContainer() const;`
- L67 _public member_ `FResetPhaseDelegates PreResetDelegates;`
- L68 _public member_ `FResetPhaseDelegates ResetDelegates;`
- L69 _public member_ `FResetPhaseDelegates PostResetDelegates;`
- L72 _public member_ `TUniquePtr<FInterchangeResetContextData> ResetContextData;`
- L73 _public member_ `TSet<const UInterchangeFactoryBaseNode*> FilteredNodes;`
- L75 _private member_ `TObjectPtr<const UInterchangeSceneImportAsset> SceneImportAsset;`
- L76 _private member_ `TObjectPtr<UInterchangeResultsContainer> ResultsContainer;`
- L78 _private member_ `TMap<const UInterchangeFactoryBaseNode*, FFactoryNodeData> FactoryNodeDataCache;`

#### struct `FInterchangeResetParameters::FFactoryNodeData`  
`struct FFactoryNodeData`  
_L44-49_
- L46 _public member_ `FSoftObjectPath ReferencedObjectPath;`
- L47 _public member_ `TObjectPtr<UInterchangeFactoryBase> Factory;`
- L48 _public member_ `TArray<TObjectPtr<UObject>> ObjectsToReset;`

#### class `FInterchangeReset`  
`class FInterchangeReset`  
_L82-86_
- L85 _public prototype_ `static void ExecuteReset(FInterchangeResetParameters& ResetObjectParameters);`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FOnResetPhaseCompletedDelegate, class FInterchangeResetParameters&) DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnFilterFactoryNodeDelegate, class FInterchangeResetParameters&, const UInterchangeFactoryBaseNode*) DECLARE_DELEGATE_ThreeParams(FOnNodeProcessedDelegate, class FInterchangeResetParameters&, const UInterchangeFactoryBase*, const UInterchangeFactoryBaseNode*) DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeReset, Display, All) struct FResetPhaseDelegates { FOnFilterFactoryNodeDelegate OnNodeFilter; FOnNodeProcessedDelegate OnNodeProcessed; FOnResetPhaseCompletedDelegate OnCompleted; };`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnFilterFactoryNodeDelegate, class FInterchangeResetParameters&, const UInterchangeFactoryBaseNode*) DECLARE_DELEGATE_ThreeParams(FOnNodeProcessedDelegate, class FInterchangeResetParameters&, const UInterchangeFactoryBase*, const UInterchangeFactoryBaseNode*) DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeReset, Display, All) struct FResetPhaseDelegates { FOnFilterFactoryNodeDelegate OnNodeFilter; FOnNodeProcessedDelegate OnNodeProcessed; FOnResetPhaseCompletedDelegate OnCompleted; };`
- L25 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnNodeProcessedDelegate, class FInterchangeResetParameters&, const UInterchangeFactoryBase*, const UInterchangeFactoryBaseNode*) DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeReset, Display, All) struct FResetPhaseDelegates { FOnFilterFactoryNodeDelegate OnNodeFilter; FOnNodeProcessedDelegate OnNodeProcessed; FOnResetPhaseCompletedDelegate OnCompleted; };`
- L27 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeReset, Display, All) struct FResetPhaseDelegates { FOnFilterFactoryNodeDelegate OnNodeFilter; FOnNodeProcessedDelegate OnNodeProcessed; FOnResetPhaseCompletedDelegate OnCompleted; };`
- L88 _namespace_ `namespace UE`
- L88 _namespace_ `namespace Interchange` (scope `UE`)
- L88 _namespace_ `namespace InterchangeReset` (scope `UE::Interchange`)
- L90 _externvar_ `extern FAutoConsoleVariableRef CCvarInterchangeResetFilteredNodes;` (scope `UE::Interchange::InterchangeReset`)
- L92 _namespace_ `namespace Constants` (scope `UE::Interchange::InterchangeReset`)
- L94 _externvar_ `extern const FString SceneImportAssetPathKey;` (scope `UE::Interchange::InterchangeReset::Constants`)
- L95 _externvar_ `extern const FString FactoryNodeUidPathKey;` (scope `UE::Interchange::InterchangeReset::Constants`)

### `Source/Runtime/Interchange/Engine/Public/InterchangeManager.h` (Public)


#### enum `ESanitizeNameTypeFlags`  
`enum class ESanitizeNameTypeFlags : uint8`  
_L60-67_
- L62 _public enumerator_ `None = 0x00`
- L63 _public enumerator_ `Name = 0x01`
- L64 _public enumerator_ `ObjectName = 0x02`
- L65 _public enumerator_ `ObjectPath = 0x04`
- L66 _public enumerator_ `LongPackage = 0x08`

#### class `UE::Interchange::FScopedInterchangeImportEnableState`  
`class FScopedInterchangeImportEnableState`  
_L77-84_
- L80 _public prototype_ `explicit FScopedInterchangeImportEnableState(const bool bScopeValue);`
- L81 _public prototype_ `~FScopedInterchangeImportEnableState();`
- L83 _private member_ `bool bOriginalInterchangeImportEnableState;`

#### class `UE::Interchange::FScopedSourceData`  
`class FScopedSourceData`  
_L86-94_
- L89 _public prototype_ `explicit FScopedSourceData(const FString& Filename);`
- L90 _public prototype_ `~FScopedSourceData();`
- L91 _public prototype_ `UInterchangeSourceData* GetSourceData() const;`
- L93 _private member_ `TStrongObjectPtr<UInterchangeSourceData> SourceDataPtr = nullptr;`

#### class `UE::Interchange::FScopedTranslator`  
`class FScopedTranslator`  
_L96-105_
- L99 _public prototype_ `explicit FScopedTranslator(const UInterchangeSourceData* SourceData);`
- L100 _public prototype_ `~FScopedTranslator();`
- L101 _public prototype_ `UInterchangeTranslatorBase* GetTranslator();`
- L104 _private member_ `TStrongObjectPtr<UInterchangeTranslatorBase> ScopedTranslatorPtr = nullptr;`

#### class `UE::Interchange::FScopedBaseNodeContainer`  
`class FScopedBaseNodeContainer`  
_L107-116_
- L110 _public prototype_ `FScopedBaseNodeContainer();`
- L111 _public prototype_ `~FScopedBaseNodeContainer();`
- L112 _public prototype_ `UInterchangeBaseNodeContainer* GetBaseNodeContainer();`
- L115 _private member_ `TStrongObjectPtr<UInterchangeBaseNodeContainer> ScopedBaseNodeContainerPtr = nullptr;`

#### enum `UE::Interchange::EImportType`  
`enum class EImportType : uint8`  
_L118-123_
- L120 _public enumerator_ `ImportType_None`
- L121 _public enumerator_ `ImportType_Asset`
- L122 _public enumerator_ `ImportType_Scene`

#### struct `UE::Interchange::FImportAsyncHelperData`  
`struct FImportAsyncHelperData`  
_L125-147_
- L128 _public member_ `bool bIsAutomated = false;` — True if the import process is unattended. We cannot show UI if the import is automated.
- L131 _public member_ `bool bFollowRedirectors = false;` — True if redirectors will be followed when determining what location to import an asset.
- L134 _public member_ `EImportType ImportType = EImportType::ImportType_None;` — We can import assets or full scene.
- L137 _public member_ `UObject* ReimportObject = nullptr;` — True if we are reimporting assets or a scene.
- L140 _public member_ `ULevel* ImportLevel = nullptr;` — Level to import into, if we are doing a scene import.
- L143 _public member_ `FString DestinationName;` — Optional custom name for the import.
- L146 _public member_ `bool bReplaceExisting = true;` — Whether or not to overwrite existing assets.

#### class `UE::Interchange::FImportResult`  
`class FImportResult : protected FGCObject`  
_L149-223_
- inherits: `FGCObject`
- L152 _public prototype_ `FImportResult();`
- L154 _public prototype_ `FImportResult(FImportResult&&) = delete;`
- L155 _public prototype_ `FImportResult& operator=(FImportResult&&) = delete;`
- L157 _public prototype_ `FImportResult(const FImportResult&) = delete;`
- L158 _public prototype_ `FImportResult& operator=(const FImportResult&) = delete;`
- L160 _public prototype_ `virtual ~FImportResult() = default;`
- L170 _public prototype_ `EStatus GetStatus() const;`
- L172 _public prototype_ `bool IsValid() const;`
- L174 _public prototype_ `void SetInProgress();`
- L175 _public prototype_ `void SetDone();`
- L176 _public prototype_ `void WaitUntilDone(bool bSynchronous = false);`
- L181 _public prototype_ `const TArray< UObject* >& GetImportedObjects() const;` — Assets are only made available once they have been completely imported (passed through the entire import pipeline). While the status isn't EStatus::Done, the list can grow between subsequent calls. FAssetImportResult holds a reference to the assets so that they aren't garbage collected.
- L184 _public prototype_ `UObject* GetFirstAssetOfClass(UClass* InClass) const;` — Helper to get the first asset of a certain class. Use when expecting a single asset of that class to be imported, because the order isn't deterministic.
- L187 _public function_ `UInterchangeResultsContainer* GetResults() const` — Return the results of this asset import operation.
- L190 _public prototype_ `void AddImportedObject(UObject* ImportedObject);` — Adds an asset to the list of imported assets.
- L193 _public prototype_ `void OnDone(TFunction< void(FImportResult&) > Callback);` — Callback when the status switches to done.
- L196 _public prototype_ `void SetAsyncHelper(TWeakPtr<class FImportAsyncHelper> InAsyncHelper);` — Set the async helper that own this import result
- L199 _public member_ `FOnObjectImportDoneDynamic OnObjectDone;` — Internal delegates. To set these, use the FImportAssetParameters when calling the Interchange import functions.
- L200 _public member_ `FOnObjectImportDoneNative OnObjectDoneNative;`
- L202 _public member_ `FOnImportDoneDynamic OnImportDone;`
- L203 _public member_ `FOnImportDoneNative OnImportDoneNative;`
- L207 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L208 _protected function_ `virtual FString GetReferencerName() const override`
- L214 _private member_ `std::atomic< EStatus > ImportStatus;`
- L216 _private member_ `TArray< TObjectPtr<UObject> > ImportedObjects;`
- L217 _private member_ `mutable FRWLock ImportedObjectsRWLock;`
- L218 _private member_ `TObjectPtr<UInterchangeResultsContainer> Results;`
- L220 _private member_ `TWeakPtr<class FImportAsyncHelper> AsyncHelper = nullptr;`
- L222 _private member_ `TFunction< void(FImportResult&) > DoneCallback;`

#### enum `UE::Interchange::FImportResult::EStatus`  
`enum class EStatus`  
_L163-168_
- L165 _public enumerator_ `Invalid`
- L166 _public enumerator_ `InProgress`
- L167 _public enumerator_ `Done`

#### class `UE::Interchange::FImportAsyncHelper`  
`class FImportAsyncHelper : protected FGCObject`  
_L230-377_
- inherits: `FGCObject`
- L233 _public prototype_ `static FInterchangeImportResultAnalyticsInfo CreateImportResultAnalyticsInfo(FImportAsyncHelper& AsyncHelper);`
- L236 _public prototype_ `FImportAsyncHelper();`
- L238 _public prototype_ `~FImportAsyncHelper();`
- L241 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L242 _public function_ `virtual FString GetReferencerName() const override`
- L247 _public member_ `bool bRunSynchronous = false;`
- L248 _public member_ `bool bRuntimeOrPIE = false;`
- L251 _public member_ `int32 UniqueId;` — Unique ID for this async helper.
- L254 _public member_ `FString ContentBasePath;` — The base path to import the content.
- L257 _public member_ `TArray<TStrongObjectPtr<UInterchangeBaseNodeContainer>> BaseNodeContainers;` — The following arrays are per source data
- L258 _public member_ `TArray<TObjectPtr<UInterchangeSourceData>> SourceDatas;`
- L259 _public member_ `TArray<TObjectPtr<UInterchangeTranslatorBase>> Translators;`
- L262 _public member_ `TArray<TObjectPtr<UInterchangePipelineBase>> Pipelines;` — The pipelines array is not per source data.
- L265 _public member_ `TArray<UObject*> OriginalPipelines;` — The original pipelines asset to save in the asset reimport data. The original pipeline can restore Python class member value. Python class instanced assets cannot be saved, so we have to serialize in JSON the data to restore it when we do a reimport.
- L267 _public member_ `TArray<uint64> TranslatorTasks;`
- L268 _public member_ `TArray<uint64> PipelineTasks;`
- L269 _public member_ `TArray<uint64> WaitAssetCompilationTasks;`
- L270 _public member_ `TArray<uint64> PostImportTasks;`
- L271 _public member_ `uint64 ParsingTask;`
- L272 _public member_ `TArray<uint64> ImportObjectQueryPayloadsTasks;`
- L273 _public member_ `TArray<uint64> BeginImportObjectTasks;`
- L274 _public member_ `TArray<uint64> ImportObjectTasks;`
- L275 _public member_ `TArray<uint64> FinalizeImportObjectTasks;`
- L276 _public member_ `TArray<uint64> SceneTasks;`
- L278 _public member_ `uint64 PreCompletionTask;`
- L279 _public member_ `uint64 CompletionTask;`
- L282 _public prototype_ `bool IsClassImportAllowed(UClass* Class);` — Return true if we can import this class, or false otherwise.
- L284 _public prototype_ `UPackage* GetCreatedPackage(const FString& PackageName) const;`
- L285 _public prototype_ `void AddCreatedPackage(const FString& PackageName, UPackage* Package);`
- L287 _public prototype_ `UInterchangeFactoryBase* GetCreatedFactory(const FString& FactoryNodeUniqueId) const;`
- L288 _public prototype_ `void AddCreatedFactory(const FString& FactoryNodeUniqueId, UInterchangeFactoryBase* Factory);`
- L315 _public prototype_ `FImportedObjectInfo& AddDefaultImportedAssetGetRef(int32 SourceIndex);`
- L316 _public prototype_ `const FImportedObjectInfo* FindImportedAssets(int32 SourceIndex, TFunction< bool(const FImportedObjectInfo& ImportedObjects) > Predicate) const;`
- L317 _public prototype_ `void IterateImportedAssets(int32 SourceIndex, TFunction< void(const TArray<FImportedObjectInfo>& ImportedObjects) > Callback) const;`
- L318 _public prototype_ `void IterateImportedAssetsPerSourceIndex(TFunction< void(int32 SourceIndex, const TArray<FImportedObjectInfo>& ImportedObjects) > Callback) const;`
- L320 _public prototype_ `FImportedObjectInfo& AddDefaultImportedSceneObjectGetRef(int32 SourceIndex);`
- L321 _public prototype_ `const FImportedObjectInfo* FindImportedSceneObjects(int32 SourceIndex, TFunction< bool(const FImportedObjectInfo& ImportedObjects) > Predicate) const;`
- L322 _public prototype_ `void IterateImportedSceneObjects(int32 SourceIndex, TFunction< void(const TArray<FImportedObjectInfo>& ImportedObjects) > Callback) const;`
- L323 _public prototype_ `void IterateImportedSceneObjectsPerSourceIndex(TFunction< void(int32 SourceIndex, const TArray<FImportedObjectInfo>& ImportedObjects) > Callback) const;`
- L328 _public prototype_ `bool IsImportingObject(UObject* Object) const;` — Return true if the Object is imported by this async import, or false otherwise.
- L330 _public member_ `FImportAsyncHelperData TaskData;`
- L332 _public member_ `FAssetImportResultRef AssetImportResult;`
- L333 _public member_ `FSceneImportResultRef SceneImportResult;`
- L336 _public member_ `std::atomic<bool> bCancel;` — If we cancel the tasks, we set this Boolean to true.
- L338 _public prototype_ `void ReleaseTranslatorsSource();`
- L343 _public prototype_ `TArray<uint64> GetCompletionTaskGraphEvent();` — Wait synchronously after the graph parsing task is done, and return the GraphEventArray up to the completion TaskGraphEvent.
- L345 _public prototype_ `void InitCancel();`
- L347 _public prototype_ `void CleanUp();`
- L349 _public member_ `double TaskExecuteStarted;`
- L353 _public member_ `TStrongObjectPtr<UInterchangeAnalyticsHandlerBase> AnalyticsHandler;` — This class owns the Analytics Handler and manages its lifetime. Analytics Handler will be released at the end of import when the ImportAsyncHandler is deleted.
- L355 _private prototype_ `static TMap<int32, TArray<TObjectPtr<UObject>>> ExtractImportedObjectsPerSourceIndex(TMap<int32, TArray<FImportedObjectInfo>>& InObjectInfoPerSourceIndex);`
- L358 _private member_ `FCriticalSection ClassPermissionLock;`
- L360 _private member_ `TSet<UClass*> DeniedClasses;` — Set of classes whose creation has been denied.
- L362 _private member_ `TSet<UClass*> AllowedClasses;` — Set of classes whose creation is allowed.
- L365 _private member_ `mutable FCriticalSection CreatedPackagesLock;` — Created package map. The key is the package name. We cannot create packages asynchronously, so we have to create a game thread task to do this.
- L366 _private member_ `TMap<FString, UPackage*> CreatedPackages;`
- L369 _private member_ `mutable FCriticalSection CreatedFactoriesLock;` — Created factories map. The key is the factory node UID.
- L370 _private member_ `TMap<FString, TObjectPtr<UInterchangeFactoryBase>> CreatedFactories;`
- L372 _private member_ `mutable FCriticalSection ImportedAssetsPerSourceIndexLock;`
- L373 _private member_ `TMap<int32, TArray<FImportedObjectInfo>> ImportedAssetsPerSourceIndex;`
- L375 _private member_ `mutable FCriticalSection ImportedSceneObjectsPerSourceIndexLock;`
- L376 _private member_ `TMap<int32, TArray<FImportedObjectInfo>> ImportedSceneObjectsPerSourceIndex;`

#### struct `UE::Interchange::FImportAsyncHelper::FImportedObjectInfo`  
`struct FImportedObjectInfo`  
_L290-313_
- L293 _public member_ `FSoftObjectPath ImportedObject;` — `UE_DEPRECATED(5.8, "Direct use of this variable is deprecated, Please use GetImportedObject()/SetImportedObject() instead")` — The object that was imported.
- L295 _public function_ `UObject* GetImportedObject() const`
- L302 _public function_ `void SetImportedObject(UObject* InImportedObject)`
- L309 _public member_ `UInterchangeFactoryBase* Factory = nullptr;` — The factory that created the imported object.
- L310 _public member_ `UInterchangeFactoryBaseNode* FactoryNode = nullptr;` — The node that describes the object.
- L311 _public member_ `bool bIsReimport;`
- L312 _public member_ `mutable bool bPostEditChangeCalled = false;` — This field is set by the PreCompletionTask and need to be mutable

#### class `UInterchangePipelineStackOverride`  
`class UInterchangePipelineStackOverride : public UObject`  
_L388-404_
- reflection: `UCLASS(Transient, BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: This class is used to pass override pipelines in the ImportAssetTask Options member.
- L394 _public member_ `TArray<FSoftObjectPath> OverridePipelines;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange|ImportAsset")`
- L397 _public prototype_ `void AddPythonPipeline(UInterchangePythonPipelineBase* PipelineBase);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | PipelineStackOverride")`
- L400 _public prototype_ `void AddBlueprintPipeline(UInterchangeBlueprintPipelineBase* PipelineBase);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | PipelineStackOverride")`
- L403 _public prototype_ `void AddPipeline(UInterchangePipelineBase* PipelineBase);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | PipelineStackOverride")`

#### struct `FImportAssetParameters`  
`struct FImportAssetParameters`  
_L407-472_
- reflection: `USTRUCT(BlueprintType)`
- L413 _public member_ `TObjectPtr<UObject> ReimportAsset = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange|ImportAsset")` — If the import is a reimport for a specific asset, set the asset to reimport here.
- L417 _public member_ `int32 ReimportSourceIndex = INDEX_NONE;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange|ImportAsset")` — If we are doing a reimport, set the source index here. Some assets have more then one source file that each contains part of the asset content.
- L421 _public member_ `bool bIsAutomated = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange|ImportAsset")` — Tell Interchange that import is automated and it shouldn't present a modal window.
- L425 _public member_ `bool bFollowRedirectors = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange|ImportAsset")` — Tell Interchange to follow redirectors when determining the location an asset will be imported.
- L429 _public member_ `TArray<FSoftObjectPath> OverridePipelines;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange|ImportAsset", meta = (AllowedClasses = "/Script/InterchangeCore.InterchangePipelineBase, /Script/InterchangeEngine.InterchangeBlueprintPipelineBase, /Script/InterchangeEngine.InterchangePythonPipelineAsset"))` — Adding overrides tells Interchange to use the specific custom set of pipelines instead of letting the user or the system choose.
- L433 _public member_ `TObjectPtr<ULevel> ImportLevel = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange|ImportAsset")` — Level to import into when doing a scene import.
- L437 _public member_ `FString DestinationName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange|ImportAsset")` — Optional custom name for the import.
- L441 _public member_ `bool bReplaceExisting = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange|ImportAsset")` — Determies whether to overwrite existing assets.
- L445 _public member_ `bool bForceShowDialog = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange|ImportAsset")` — If true this import must show the import dialog and ignore the show dialog settings.
- L451 _public member_ `FOnObjectImportDoneDynamic OnAssetDone;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange|ImportAsset", meta=(PinHiddenByDefault))` — This is called each time an asset is imported or reimported from the import call.
- L452 _public member_ `FOnObjectImportDoneNative OnAssetDoneNative;`
- L456 _public member_ `FOnImportDoneDynamic OnAssetsImportDone;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange|ImportAsset", meta=(PinHiddenByDefault))` — This is called when all the assets were imported from the source data.
- L457 _public member_ `FOnImportDoneNative OnAssetsImportDoneNative;`
- L461 _public member_ `FOnObjectImportDoneDynamic OnSceneObjectDone;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange|ImportAsset", meta=(PinHiddenByDefault))` — This is called each time an object in the scene is imported or reimported from the import call.
- L462 _public member_ `FOnObjectImportDoneNative OnSceneObjectDoneNative;`
- L466 _public member_ `FOnImportDoneDynamic OnSceneImportDone;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange|ImportAsset", meta=(PinHiddenByDefault))` — This is called when all the scene objects were imported from the source data.
- L467 _public member_ `FOnImportDoneNative OnSceneImportDoneNative;`
- L471 _public member_ `mutable bool bRunSynchronous;` — Tell Interchange that import must run synchronously on the game thread. This is an internal property set by the Import API

#### class `UInterchangeManager`  
`class UInterchangeManager : public UObject`  
_L475-1064_
- reflection: `UCLASS(Transient, BlueprintType, CustomConstructor, MinimalAPI)`
- inherits: `UObject`
- L480 _public prototype_ `UInterchangeManager(const FObjectInitializer& ObjectInitializer);`
- L488 _public function_ `static UInterchangeManager* GetInterchangeManagerScripted()` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Return the pointer to the Interchange Manager singleton. @note - We need to return a pointer to have a valid Blueprint-callable function.
- L494 _public prototype_ `static UInterchangeManager& GetInterchangeManager();` — Return the Interchange Manager singleton.
- L497 _public prototype_ `static bool IsInterchangeImportEnabled();` — Return the CVar that enables or disables Interchange.
- L499 _public prototype_ `static void SetInterchangeImportEnabled(bool bEnabled);` — Set the CVar that enables or disables Interchange.
- L502 _public prototype_ `static bool IsImporting();` — Checks if there are any imports in progress.
- L505 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInterchangeOnAssetPostImport, UObject*);` — Delegate type that is fired when new assets have been imported. Note: InCreatedObject can be NULL if the import failed. Params: UFactory* InFactory, UObject* InCreatedObject.
- L507 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInterchangeOnAssetPostReimport, UObject*);` — Delegate type that is fired when new assets have been reimported. Note: InCreatedObject can be NULL if the import failed. Params: UObject* InCreatedObject.
- L509 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInterchangeOnBatchImportComplete, TStrongObjectPtr<UInterchangeResultsContainer>);` — Delegate type that is fired when the import results in an error.
- L511 _public typedef_ `using FSourceIndexObjectsMap = TMap<int32, TArray<TObjectPtr<UObject>>>;` — Delegate type that is fired when the import is completed and results are available to iterate on.
- L512 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FInterchangeOnImportedObjectsAvailable, FSourceIndexObjectsMap, FSourceIndexObjectsMap);`
- L516 _public member_ `FInterchangeOnAssetPostImport OnAssetPostImport;`
- L517 _public member_ `FInterchangeOnAssetPostReimport OnAssetPostReimport;`
- L518 _public member_ `FInterchangeOnBatchImportComplete OnBatchImportComplete;`
- L521 _public member_ `FOnImportStarted OnImportStarted;` — Fires when the first import process starts.
- L524 _public member_ `FInterchangeOnImportedObjectsAvailable OnImportedObjectsAvailable;` — Fires when the imported assets and scene actors are available.
- L527 _public member_ `FOnImportFinished OnImportFinished;` — Fires when the last import process finishes.
- L530 _public member_ `FOnSanitizeName OnSanitizeName;` — Fire when we need to sanitize a name, make sure your delegate code is thread safe, since it will be broadcast in any thread.
- L533 _public member_ `FSimpleMulticastDelegate OnPreDestroyInterchangeManager;` — Called when before the application is exiting.
- L535 _public prototype_ `void SanitizeNameInline(FString& NameToSanitize, const ESanitizeNameTypeFlags NameType);`
- L544 _public prototype_ `bool RegisterTranslator(const UClass* TranslatorClass);` — All translators must be registered with the manager. @Param Translator - The UClass of the translator you want to register. @return true if the translator class can be registered, or false otherwise. @Note If you register the same class multiple times, this returns true for every call. @Note The order in which the translators are registered will be the same as the order used to select a translator to import a file.
- L553 _public prototype_ `bool RegisterFactory(const UClass* Factory);` — All factories must be registered with the manager. @Param Factory - The UClass of the factory you want to register. @return true if the factory class can be registered, or false otherwise. @Note If you register the same class multiple time, this returns true for every call.
- L562 _public prototype_ `bool RegisterWriter(const UClass* Writer);` — All writers must be registered with the manager, @Param Writer - The UClass of the writer you want to register, @return true if the writer class can be registered, or false otherwise. @Note If you register the same class multiple time, this returns true for every call.
- L571 _public prototype_ `bool RegisterImportDataConverter(const UClass* Converter);` — All converters must be registered with the manager. @Param Converter - The UClass of the converter you want to register. @return true if the converter class can be registered, or false otherwise. @Note If you register the same class multiple time, this returns true for every call.
- L579 _public prototype_ `bool ConvertImportData(UObject* Asset, const FString& Extension) const;` — Call all the registered converters to see if any converter can convert the data. @Param Asset - The asset we want to convert the import data. @Param Extension - The file extension we want to import. @return true if one of the converter has converted the data, or false otherwise.
- L587 _public prototype_ `bool ConvertImportData(const UObject* SourceImportData, FImportAssetParameters& ImportAssetParameters) const;` — Call all the registered converter, until one can convert the source import data to UInterchangeAssetImportData @Param SourceImportData - The source import data options. @Param ImportAssetParameters - The interchange import asset parameters. @return true if one of the converter has convert the data. False otherwise.
- L596 _public prototype_ `bool ConvertImportData(const UObject* SourceImportData, const UClass* DestinationClass, UObject** DestinationImportData) const;` — Call all the registered converter, until one can convert the source data to the destination @Param SourceImportData - The source import data options. @Param DestinationImportData - The destination import data options we have to create and fill. @Param DestinationClass - The class representing the DestinationImportData @return true if one of the converter has convert the data. False otherwise.
- L602 _public prototype_ `TArray<FString> GetSupportedFormats(const EInterchangeTranslatorType ForTranslatorType) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Returns the list of supported formats for a given translator type.
- L608 _public prototype_ `TArray<FString> GetSupportedAssetTypeFormats(const EInterchangeTranslatorAssetType ForTranslatorAssetType, const EInterchangeTranslatorType ForTranslatorType = EInterchangeTranslatorType::Invalid, bool bStrictMatchTranslatorType = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Returns the list of formats supporting the specified translator asset type.
- L615 _public prototype_ `TArray<FString> GetSupportedFormatsForObject(const UObject* Object, int32 SourceFileIndex) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Returns the list of supported formats for a given Object.
- L626 _public prototype_ `bool CanTranslateSourceData(const UInterchangeSourceData* SourceData, bool bSceneImportOnly = false) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Check whether there is a registered translator for this source data. This allows us to bypass the original asset tools system to import supported assets. @Param SourceData - The source data input we want to translate to Uod. @return True if there is a registered translator that can handle handle this source data, or false otherwise, when bSceneImportOnly is false. Otherwise, returns true only if the translator supports level import @Note: Temporary until FBX level import is production ready
- L634 _public prototype_ `bool CanReimport(const UObject* Object, TArray<FString>& OutFilenames) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Returns true if Interchange can create this type of asset and is able to translate its source files. @Param Object - The object we want to reimport. @Param OutFilenames - An array that is filled with the object's source filenames if the operation is successful.
- L648 _public prototype_ `bool ImportAsset(const FString& ContentPath, const UInterchangeSourceData* SourceData, const FImportAssetParameters& ImportAssetParameters, TArray<UObject*>& OutImportedObjects);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Call this to start a synchronous asset import process. This process can import many different assets into the game content. @Param ContentPath - The path where the imported assets will be created. @Param SourceData - The source data input to translate. @param ImportAssetParameters - All parameters that need to be passed to the import asset function. @return true if the import succeeds, or false otherwise. @Note - In blueprint depending on the event you use to start the import its possible to have a deadlock, use the async function if its what you are experimenting
- L660 _public prototype_ `bool ImportAsset(const FString& ContentPath, const UInterchangeSourceData* SourceData, const FImportAssetParameters& ImportAssetParameters);` — Call this to start a synchronous asset import process. This process can import many different assets into the game content. @Param ContentPath - The path where the imported assets will be created. @Param SourceData - The source data input to translate. @param ImportAssetParameters - All parameters that need to be passed to the import asset function. @return true if the import succeeds, or false otherwise.
- L671 _public prototype_ `UE::Interchange::FAssetImportResultRef ImportAssetWithResult(const FString& ContentPath, const UInterchangeSourceData* SourceData, const FImportAssetParameters& ImportAssetParameters);` — Call this to start a synchronous asset import process. This process can import many different assets into the game content. @Param ContentPath - The path where the imported assets will be created. @Param SourceData - The source data input to translate. @param ImportAssetParameters - All parameters that need to be passed to the import asset function. @return return an import result which can be use to know when the asynchronous import is terminate.
- L682 _public prototype_ `UE::Interchange::FAssetImportResultRef ImportAssetAsync(const FString& ContentPath, const UInterchangeSourceData* SourceData, const FImportAssetParameters& ImportAssetParameters);` — Call this to start an asynchronous asset import process. This process can import many different assets into the game content. @Param ContentPath - The path where the imported assets will be created. @Param SourceData - The source data input to translate. @param ImportAssetParameters - All parameters that need to be passed to the import asset function. @return return an import result which can be use to know when the asynchronous import is terminate.
- L694 _public prototype_ `bool ScriptedImportAssetAsync(const FString& ContentPath, const UInterchangeSourceData* SourceData, const FImportAssetParameters& ImportAssetParameters);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Call this from blueprint or python to start an asynchronous asset import process. This process can import many different assets into the game content. @Param ContentPath - The path where the imported assets will be created. @Param SourceData - The source data input to translate. @param ImportAssetParameters - All parameters that need to be passed to the import asset function. @return true if the import was started, or false otherwise.
- L711 _public prototype_ `bool ReimportAsset(UObject* ObjectToReimport, const FImportAssetParameters& ImportAssetParameters, TArray<UObject*>& OutImportedObjects);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Call this to start a synchronous asset re-import process. This process can re-import many different assets into the game content. @Param ObjectToReimport - The object to re-import. @param ImportAssetParameters - All parameters that need to be passed to the import asset function. @return true if the import succeeds, or false otherwise. @Note - The interchange manager will by default use the last file use to re-import the ObjectToReimport. If the file doesn't exist and the bAutomated flag is: - true, the function will return false and log a warning - false, a dialog will ask @Note - In blueprint depending on the event you use to start the import its possible to have a deadlock, use the async function if its what you are experimenting
- L722 _public prototype_ `UE::Interchange::FAssetImportResultRef ReimportAssetAsync(UObject* ObjectToReimport, const FImportAssetParameters& ImportAssetParameters);` — Call this to start an asynchronous asset import process. This process can import many different assets into the game content. @Param ContentPath - The path where the imported assets will be created. @Param SourceData - The source data input to translate. @param ImportAssetParameters - All parameters that need to be passed to the import asset function. @return return an import result which can be use to know when the asynchronous import is terminate.
- L739 _public prototype_ `bool ScriptedReimportAssetAsync(UObject* ObjectToReimport, const FImportAssetParameters& ImportAssetParameters);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Call this from blueprint or python to start an asynchronous asset import process. This process can import many different assets into the game content. @Param ObjectToReimport - The object to re-import. @param ImportAssetParameters - All parameters that need to be passed to the import asset function. @return true if the import was started, or false otherwise. @Note - The interchange manager will by default use the last file use to re-import the ObjectToReimport. If the file doesn't exist and the bAutomated flag is: - true, the function will return false and log a warning - false, a dialog will ask @Note - If you need an event for when the import is done use the ImportAssetParameters events.
- L753 _public prototype_ `bool ImportScene(const FString& ContentPath, const UInterchangeSourceData* SourceData, const FImportAssetParameters& ImportAssetParameters);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Call this to start a synchronous scene import process. This process can import many different assets and their transforms (USceneComponent). @Param ContentPath - The path where the imported assets will be created. @Param SourceData - The source data input to translate. This object will be duplicated to allow thread-safe operations. @param ImportAssetParameters - All parameters that need to be passed to the import asset function. @return true if the import succeeds, or false otherwise. @Note - In blueprint depending on the event you use to start the import its possible to have a deadlock, use the async function if its what you are experimenting
- L765 _public prototype_ `bool ScriptedImportSceneAsync(const FString& ContentPath, const UInterchangeSourceData* SourceData, const FImportAssetParameters& ImportAssetParameters);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Call this to start a asynchronous scene import process. This process can import many different assets and their transforms (USceneComponent). @Param ContentPath - The path where the imported assets will be created. @Param SourceData - The source data input to translate. This object will be duplicated to allow thread-safe operations. @param ImportAssetParameters - All parameters that need to be passed to the import asset function. @return true if the import was started, or false otherwise.
- L777 _public prototype_ `ImportSceneAsync(const FString& ContentPath, const UInterchangeSourceData* SourceData, const FImportAssetParameters& ImportAssetParameters);`
- L787 _public prototype_ `bool ExportAsset(const UObject* Asset, bool bIsAutomated = false);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Export Manager")` — Call this to start an asset export process. The caller must specify a source data. @Param Asset - The asset to export. @Param bIsAutomated - If true, the exporter will not show any UI or dialogs. @return true if the export succeeds, or false otherwise.
- L796 _public prototype_ `bool ExportScene(const UObject* World, bool bIsAutomated = false);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Export Manager")` — Call this to start a scene export process. The caller must specify a source data. @Param World - The scene to export. @Param bIsAutomated - If true, the import process will not show any UI or dialogs. @return true if the export succeeds, or false otherwise.
- L804 _public prototype_ `static UInterchangeSourceData* CreateSourceData(const FString& InFileName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Script helper to create a source data object that points to a file on disk. @Param InFilename: Specify a file on disk. @return: A new UInterchangeSourceData.
- L812 _public prototype_ `const UClass* GetRegisteredFactoryClass(const UClass* ClassToMake) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Script helper to get a registered factory for a specified class. @Param FactoryClass: The class whose registered factory you want to find. @return: The registered factory class if found, or NULL if no registered factory was found.
- L818 _public prototype_ `void InitAsyncHelper(TSharedRef<UE::Interchange::FImportAsyncHelper, ESPMode::ThreadSafe>& AsyncHelper, const UE::Interchange::FImportAsyncHelperData& Data, const FImportAssetParameters& ImportAssetParameters);` — Initializes an FImportAsyncHelper with correct task data and import asset parameters. The Async Helper is deleted when ReleaseAsyncHelper is called. @param Data - The data to pass to the different import tasks.
- L821 _public prototype_ `void ReleaseAsyncHelper(TWeakPtr<UE::Interchange::FImportAsyncHelper, ESPMode::ThreadSafe> AsyncHelper);` — Delete the specified AsyncHelper and remove it from the array that was holding it.
- L827 _public prototype_ `TSharedPtr<UE::Interchange::FImportAsyncHelper, ESPMode::ThreadSafe> GetAsyncHelper(int32 UniqueId);` — Return a pointer to an FImportAsyncHelper that is the specified UniqueId. Return an empty shared pointer if the unique id is not matching any async helper The return asynchelper should be release before the end of the import process to make sure all resource are release when the import is completed.
- L835 _public prototype_ `UInterchangeTranslatorBase* GetTranslatorForSourceData(const UInterchangeSourceData* SourceData) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Return the first translator that can translate the source data. @Param SourceData - The source data that you want a translator for. @return return a matching translator, or nullptr if no translators exist for the source data.
- L841 _public prototype_ `bool IsInterchangeActive();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Return true if Interchange is actively importing or exporting, or false otherwise.
- L849 _public prototype_ `bool WarnIfInterchangeIsActive();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Return false if Interchange is not actively importing or exporting. If Interchange is active, it will display a notification to let the user know they can cancel the asynchronous import/export to be able to complete the operation they requested. (This is called by the exit editor operation.)
- L855 _public prototype_ `UInterchangeAssetImportData* GetAssetImportData(UObject* Asset) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Returns the list of supported formats for a given translator type.
- L862 _public prototype_ `bool CanTranslateSourceDataWithPayloadInterface(const UInterchangeSourceData* SourceData, const UClass* PayloadInterfaceClass) const;` — Check whether there is a translator registered that can translate the source data with the specified PayloadInterface. @Param SourceData - The source data input you want to translate to Uod. @return true if the source data can be translated using the specified PayloadInterface, or false otherwise.
- L870 _public prototype_ `UInterchangeTranslatorBase* GetTranslatorSupportingPayloadInterfaceForSourceData(const UInterchangeSourceData* SourceData, const UClass* PayloadInterfaceClass) const;` — Return the first translator that can translate the source data with the specified PayloadInterface. @Param SourceData - The source data that you want a translator for. @Param PayloadInterfaceClass - The PayloadInterface that the translator must implement. @return return a matching translator that implements the specified PayloadInterface, or nullptr if none exists.
- L877 _public prototype_ `bool IsObjectBeingImported(UObject* Object) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Return true if the object is being imported, or false otherwise. If the user imports multiple file in the same folder, it's possible to have the same asset name in two different files.
- L884 _public prototype_ `bool EnqueuePostImportTask(TSharedPtr<FInterchangePostImportTask> PostImportTask);` — Queue task that are not directly a import or re-import of assets. The post import tasks are execute only when the QueuedTasks is empty (no more import task running) Example: if a skeletal mesh re-import cannot apply the existing alternate skinning data, it will enqueue a post import task to re-import those alternate skinning files.
- L891 _public prototype_ `static void SetReplaceExistingAlldialogAnswer(bool bReplaceExistingAllDialogAnswer);` — Sets the bReplaceExistingAllDialogAnswer which is responsible for: if the Import process will override or not all existing assets this Import stack tries to override.
- L896 _public prototype_ `static void ResetReplaceExistingAlldialogAnswerSet();` — Checks if the bReplaceExistingAllDialogAnswer.
- L901 _public prototype_ `static TOptional<bool> GetReplaceExistingAlldialogAnswer();` — Gets the bReplaceExistingAllDialogAnswer.
- L906 _public prototype_ `void SetEditorUtilities(UClass* EditorUtilitiesClass);` — Set the editor utilities, those are use for editor operation like saving an asset.
- L911 _public prototype_ `UInterchangeEditorUtilitiesBase* GetEditorUtilities() const;` — Get the editor utilities, those are use for editor operation like saving an asset.
- L916 _public prototype_ `bool CanUseTranslator(UInterchangeTranslatorBase* Translator) const;` — Check if a non-parallel translator is unlocked for using.
- L921 _public prototype_ `void SetAnalyticsHandlerClass(const TSoftClassPtr<UInterchangeAnalyticsHandlerBase>& InAnalyticsHandlerClass);` — Sets class to use for analytics. This will create a new object during import and use for the Analytics.
- L926 _protected prototype_ `static bool IsAttended();` — Return true if Interchange can show UI.
- L933 _protected prototype_ `void FindPipelineCandidate(TArray<UClass*>& PipelineCandidates);` — Find all pipeline candidates (C++, Blueprint, and Python). @Param SourceData - The source data you need a translator for. @return return a matching translator, or nullptr if there is no match.
- L941 _protected prototype_ `void CancelAllTasks();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — This function cancels all tasks and finishes them as fast as possible. We use this if the user cancels the work or if the editor exits. @note - This is a asynchronous call. Tasks will be completed (canceled) soon.
- L947 _protected prototype_ `void WaitUntilAllTasksDone(bool bCancel);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")` — Wait synchronously until all tasks are done.
- L954 _protected prototype_ `void SetActiveMode(bool IsActive);` — If we set the mode to active, we will setup the timer and add the thread that will block the GC. If the we set the mode to inactive, we will remove the timer and finish the thread that blocks the GC.
- L960 _protected prototype_ `void StartQueuedTasks(bool bCancelAllTasks = false);` — Start tasks until we reach the taskgraph worker number. @param bCancelAllTasks - If true, we will start all tasks but with the cancel state set, so tasks will complete fast and call the completion task.
- L966 _protected prototype_ `ImportInternal(const FString& ContentPath, const UInterchangeSourceData* SourceData, const FImportAssetParameters& ImportAssetParameters, const UE::Interchange::EImportType ImportType);`
- L968 _protected prototype_ `TOptional<FString> ValidateReimportParameter(UObject* ObjectToReimport, const FImportAssetParameters& ImportAssetParameters, bool bRunSynchronous);`
- L970 _protected prototype_ `int32 GetImportTaskCount() const;`
- L971 _protected prototype_ `TSharedPtr<UE::Interchange::FImportAsyncHelper, ESPMode::ThreadSafe> GetImportTaskForIndex(int32 Index) const;`
- L972 _protected prototype_ `TSharedPtr<UE::Interchange::FImportAsyncHelper, ESPMode::ThreadSafe> GetImportTaskForAsyncHelperUniqueId(int32 AsyncHelperUniqueId) const;`
- L974 _protected prototype_ `int32 AddImportTask(TSharedPtr<UE::Interchange::FImportAsyncHelper, ESPMode::ThreadSafe> ImportTask);` — Return the index in the ImportTasks array
- L975 _protected prototype_ `void RemoveImportTask(TSharedPtr<UE::Interchange::FImportAsyncHelper, ESPMode::ThreadSafe> ImportTask);`
- L976 _protected prototype_ `void RemoveImportTask(int32 AsyncHelperUniqueId);`
- L979 _private prototype_ `TStrongObjectPtr<UInterchangeAnalyticsHandlerBase> CreateAnalyticsHandler(const FString& ImportFilePath);`
- L983 _private member_ `static bool bIsCreatingSingleton;`
- L991 _private member_ `TSoftClassPtr<UInterchangeAnalyticsHandlerBase> AnalyticsHandlerClass;`
- L993 _private member_ `TMap<UClass*, bool> NonParallelTranslatorLocks;`
- L994 _private member_ `TMap<UClass*, TArray<FQueuedTaskData>> NonParallelTranslatorQueueTasks;`
- L997 _private member_ `TQueue<FQueuedTaskData> QueuedTasks;` — Queue all incoming tasks if there are more started task then we have cores.
- L998 _private member_ `int32 QueueTaskCount = 0;`
- L1003 _private member_ `TQueue<TSharedPtr<FInterchangePostImportTask>> QueuedPostImportTasks;` — Queue all incoming tasks that are not directly import or re-import of assets. The post import tasks are executed only when all the QueuedTasks are completed and empty. Those tasks can start an import task (QueuedTasks), one example is the skeletal mesh alternate skinning which requires to import several files for each profile.
- L1006 _private member_ `FTSTicker::FDelegateHandle QueuedPostImportTasksTickerHandle;` — Ticker which is on only if we have some QueuedPostImportTasks
- L1009 _private member_ `mutable FCriticalSection ImportTasksLock;` — Critical section to make the import tasks array thread safe
- L1012 _private member_ `TArray<TSharedPtr<UE::Interchange::FImportAsyncHelper, ESPMode::ThreadSafe> > ImportTasks;` — `UE_DEPRECATED(5.6, "Use the provided API to manipulate the Import tasks array. This array need to be thread safe")` — By using pointer, there is no issue if the array get resized.
- L1014 _private member_ `TSharedPtr<FAsyncTaskNotification> Notification = nullptr;`
- L1015 _private member_ `FTSTicker::FDelegateHandle NotificationTickHandle;`
- L1019 _private member_ `TSet<TObjectPtr<const UClass>> RegisteredTranslatorsClass;` — `UPROPERTY()` — Caching the registered translator classes to avoid double registration.
- L1032 _private member_ `TMap<TObjectPtr<const UClass>, TObjectPtr<const UClass> > RegisteredFactoryClasses;` — `UPROPERTY()` — The manager will create only one factory per type.
- L1036 _private member_ `TMap<TObjectPtr<const UClass>, TObjectPtr<UInterchangeWriterBase> > RegisteredWriters;` — `UPROPERTY()` — The manager will create only one writer per type.
- L1040 _private member_ `TMap<TObjectPtr<const UClass>, TObjectPtr<UInterchangeAssetImportDataConverterBase> > RegisteredConverters;` — `UPROPERTY()` — The manager will create only one converter per type.
- L1043 _private member_ `TStrongObjectPtr<UInterchangeEditorUtilitiesBase> EditorUtilities = nullptr;` — We support one editor utilities class
- L1046 _private member_ `FThreadSafeBool bIsActive = false;` — If interchange is currently importing, we have a timer to watch the cancel and we block GC.
- L1050 _private member_ `TMap<UClass*, TArray<UInterchangePipelineBase*>> ImportAllWithSamePipelines;` — If the user wants to use the same import pipeline stack for all queued tasks. This map is reset when the ImportTasks array is empty.
- L1054 _private member_ `bool bImportCanceled = false;` — Indicates that the import process was canceled by the user. This Boolean is reset to false when the ImportTasks array is empty.
- L1057 _private member_ `FDelegateHandle GCEndDelegate;` — We want to avoid starting an import task during a GC.
- L1058 _private member_ `FDelegateHandle GCPreDelegate;`
- L1059 _private member_ `bool bGCEndDelegateCancellAllTask = false;`

#### struct `UInterchangeManager::FQueuedTaskData`  
`struct FQueuedTaskData`  
_L985-989_
- L987 _public member_ `TSharedPtr<UE::Interchange::FImportAsyncHelper, ESPMode::ThreadSafe> AsyncHelper;`
- L988 _public member_ `UClass* TranslatorClass = nullptr;`

#### Free symbols / members of external scopes

- L37 _macro_ `#define UE_API INTERCHANGEENGINE_API`
- L49 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnObjectImportDoneDynamic, UObject*, Object);` — Some utility delegates for automating Interchange.
- L49 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnObjectImportDoneDynamic, UObject*, Object);` — Some utility delegates for automating Interchange.
- L50 _delegate_ `DECLARE_DELEGATE_OneParam(FOnObjectImportDoneNative, UObject*);`
- L50 _prototype_ `DECLARE_DELEGATE_OneParam(FOnObjectImportDoneNative, UObject*);`
- L52 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnImportDoneDynamic, const TArray<UObject*>&, Objects);`
- L52 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnImportDoneDynamic, const TArray<UObject*>&, Objects);`
- L53 _delegate_ `DECLARE_DELEGATE_OneParam(FOnImportDoneNative, const TArray<UObject*>&);`
- L53 _prototype_ `DECLARE_DELEGATE_OneParam(FOnImportDoneNative, const TArray<UObject*>&);`
- L56 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnImportStarted);` — Delegate Type that is fired when Interchange starts importing. Won't fire when a new import process starts while one is already in progress. Primarily Used for AutoSave setting.
- L56 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnImportStarted);` — Delegate Type that is fired when Interchange starts importing. Won't fire when a new import process starts while one is already in progress. Primarily Used for AutoSave setting.
- L58 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnImportFinished);` — Delegate Type that is fired when Interchange finished importing. Won't fire when an import process finishes while one is still in progress. Primarily Used for AutoSave setting.
- L58 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnImportFinished);` — Delegate Type that is fired when Interchange finished importing. Won't fire when an import process finishes while one is still in progress. Primarily Used for AutoSave setting.
- L71 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnSanitizeName, FString& , const ESanitizeNameTypeFlags );` — Thread safe delegate since this can be broadcast in any thread
- L71 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnSanitizeName, FString& , const ESanitizeNameTypeFlags );` — Thread safe delegate since this can be broadcast in any thread
- L73 _namespace_ `namespace UE`
- L75 _namespace_ `namespace Interchange` (scope `UE`)
- L225 _typedef_ `using FAssetImportResultRef = TSharedRef< FImportResult, ESPMode::ThreadSafe >;` (scope `UE::Interchange`)
- L226 _typedef_ `using FSceneImportResultRef = TSharedRef< FImportResult, ESPMode::ThreadSafe >;` (scope `UE::Interchange`)
- L227 _typedef_ `using FAssetImportResultPtr = TSharedPtr< FImportResult, ESPMode::ThreadSafe >;` (scope `UE::Interchange`)
- L228 _typedef_ `using FSceneImportResultPtr = TSharedPtr< FImportResult, ESPMode::ThreadSafe >;` (scope `UE::Interchange`)
- L380 _prototype_ `UInterchangePipelineBase* GeneratePipelineInstance(const FSoftObjectPath& PipelineInstance);` (scope `UE::Interchange`) — This function takes an asset that represents a pipeline and generates a UInterchangePipelineBase asset.
- L505 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInterchangeOnAssetPostImport, UObject*);` — Delegate type that is fired when new assets have been imported. Note: InCreatedObject can be NULL if the import failed. Params: UFactory* InFactory, UObject* InCreatedObject.
- L507 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInterchangeOnAssetPostReimport, UObject*);` — Delegate type that is fired when new assets have been reimported. Note: InCreatedObject can be NULL if the import failed. Params: UObject* InCreatedObject.
- L509 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FInterchangeOnBatchImportComplete, TStrongObjectPtr<UInterchangeResultsContainer>);` — Delegate type that is fired when the import results in an error.
- L512 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FInterchangeOnImportedObjectsAvailable, FSourceIndexObjectsMap, FSourceIndexObjectsMap);`

### `Source/Runtime/Interchange/Engine/Public/InterchangeMeshUtilities.h` (Public)


#### class `FInterchangeSkeletalMeshAlternateSkinWeightPostImportTask`  
`class FInterchangeSkeletalMeshAlternateSkinWeightPostImportTask : public FInterchangePostImportTask`  
_L17-38_
- inherits: `FInterchangePostImportTask`
- L20 _public prototype_ `FInterchangeSkeletalMeshAlternateSkinWeightPostImportTask(USkeletalMesh* InSkeletalMesh);`
- L22 _public prototype_ `virtual ~FInterchangeSkeletalMeshAlternateSkinWeightPostImportTask() = default;`
- L24 _public prototype_ `virtual void Execute() override;`
- L28 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FInterchangeReimportAlternateSkinWeight, USkeletalMesh*, int32 LodIndex);` — This delegate should execute the following editor function (since we are a runtime module we need this delegate to call the editor function) FSkinWeightsUtilities::ReimportAlternateSkinWeight(SkeletalMesh, LodIndex);
- L29 _public member_ `FInterchangeReimportAlternateSkinWeight ReimportAlternateSkinWeightDelegate;`
- L31 _public prototype_ `bool AddLodToReimportAlternate(int32 LodToAdd);`
- L34 _private member_ `TObjectPtr<USkeletalMesh> SkeletalMesh;`
- L37 _private member_ `TArray<int32> ReImportAlternateSkinWeightsLods;` — Alternate skin weights reimport

#### class `UInterchangeMeshUtilities`  
`class UInterchangeMeshUtilities : public UObject`  
_L41-102_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UObject`
- L54 _public prototype_ `static bool ShowMeshFilePicker(FString& OutFilename, const FText& Title);` — This function pop a file picker with all meshes supported format. @param OutFilename - The filename the user pick. #param Title - The picker dialog title. @Return - return true if the users successfully pick a file, false if something went wrong or the user cancel.
- L66 _public prototype_ `static TFuture<bool> ImportCustomLod(UObject* MeshObject, const int32 LodIndex, const UInterchangeSourceData* SourceData, bool bAsync);` — This function import a mesh from the source data and add/replace the MeshObject LOD (at LodIndex) with the imported mesh LOD data. @Param MeshObject - The Mesh we want to add the lod @Param LodIndex - The index of the LOD we want to replace or add @Param SourceData - The source to import the custom LOD @param bAsync - If true the future will not be set when the function return and the import will be asynchronous. @Return - return future boolean which will be true if it successfully add or replace the MeshObject LOD at LodIndex with the imported data.
- L79 _public prototype_ `static TFuture<bool> ImportMorphTarget(USkeletalMesh* SkeletalMesh, const int32 LodIndex, const UInterchangeSourceData* SourceData, bool bAsync, const FString& MorphTargetName);` — This function import a morph target from the source data and add/replace the skeletal mesh morph target. @Param SkeletalMesh - The target skeletal mesh we want to add the morph targets @Param LodIndex - The index of the LOD we want to replace or add the morph targets @Param SourceData - The source to import the morph targets @Param bAsync - If true the future will not be set when the function return and the import will be asynchronous. @Param MorphTargetName - If not empty we will use this name to create the morph target, if there is already an existing morph target it will be re-import @Return - return future boolean which will be true if it successfully add or replace the skeletal mesh morph target at LodIndex with the imported data.
- L92 _public function_ `bool ScriptedImportMorphTarget(USkeletalMesh* SkeletalMesh, const int32 LodIndex, const UInterchangeSourceData* SourceData, const FString& MorphTargetName) const` — `UFUNCTION(BlueprintCallable, Category = "SkeletalMesh | MorphTarget")` — This function import a morph target from the source data and add/replace the skeletal mesh morph target. @Param SkeletalMesh - The target skeletal mesh we want to add the morph targets @Param LodIndex - The index of the LOD we want to replace or add the morph targets @Param SourceData - The source to import the morph targets @Param MorphTargetName - If not empty we will use this name to create the morph target, if there is already an existing morph target it will be re-import @Return - return true if it successfully add or replace the skeletal mesh morph target at LodIndex, flase otherwise.
- L101 _private prototype_ `static TFuture<bool> InternalImportCustomLod(TSharedPtr<TPromise<bool>> Promise, UObject* MeshObject, const int32 LodIndex, const UInterchangeSourceData* SourceData, bool bAsync);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API INTERCHANGEENGINE_API`
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FInterchangeReimportAlternateSkinWeight, USkeletalMesh*, int32 LodIndex);` — This delegate should execute the following editor function (since we are a runtime module we need this delegate to call the editor function) FSkinWeightsUtilities::ReimportAlternateSkinWeight(SkeletalMesh, LodIndex);

### `Source/Runtime/Interchange/Engine/Public/InterchangePipelineConfigurationBase.h` (Public)


#### enum `EInterchangePipelineConfigurationDialogResult`  
`enum class EInterchangePipelineConfigurationDialogResult : uint8`  
_L16-22_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `Cancel UMETA(DisplayName = "Cancel")`
- L19 _public enumerator_ `Import UMETA(DisplayName = "Import")`
- L20 _public enumerator_ `ImportAll UMETA(DisplayName = "Import All")`
- L21 _public enumerator_ `SaveConfig UMETA(DisplayName = "Save Config")`

#### struct `FInterchangeStackInfo`  
`struct FInterchangeStackInfo`  
_L25-34_
- reflection: `USTRUCT(BlueprintType)`
- L30 _public member_ `FName StackName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Translator")`
- L33 _public member_ `TArray<TObjectPtr<UInterchangePipelineBase>> Pipelines;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Translator")`

#### class `UInterchangePipelineConfigurationBase`  
`class UInterchangePipelineConfigurationBase : public UObject`  
_L37-205_
- reflection: `UCLASS(BlueprintType, Blueprintable, MinimalAPI)`
- inherits: `UObject`
- L47 _public prototype_ `EInterchangePipelineConfigurationDialogResult ScriptedShowPipelineConfigurationDialog(TArray<FInterchangeStackInfo>& PipelineStacks , TArray<UInterchangePipelineBase*>& OutPipelines , UInterchangeSourceData* SourceData , UInterchangeTranslatorBase* Translator , UInterchangeBaseNodeContainer* BaseNodeContainer);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interchange | Translator")` — Non-virtual helper that allows Blueprint to implement an event-based function to implement ShowPipelineConfigurationDialog().
- L54 _public function_ `EInterchangePipelineConfigurationDialogResult ScriptedShowPipelineConfigurationDialog_Implementation(TArray<FInterchangeStackInfo>& PipelineStacks , TArray<UInterchangePipelineBase*>& OutPipelines , UInterchangeSourceData* SourceData , UInterchangeTranslatorBase* Translator , UInterchangeBaseNodeContainer* BaseNodeContainer)` — The default implementation, which is called if the Blueprint does not have any implementation, calls the virtual ShowPipelineConfigurationDialog().
- L79 _public prototype_ `EInterchangePipelineConfigurationDialogResult ScriptedShowScenePipelineConfigurationDialog(TArray<FInterchangeStackInfo>& PipelineStacks , TArray<UInterchangePipelineBase*>& OutPipelines , UInterchangeSourceData* SourceData , UInterchangeTranslatorBase* Translator , UInterchangeBaseNodeContainer* BaseNodeContainer);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interchange | Translator")` — Non-virtual helper that allows Blueprint to implement an event-based function to implement ShowScenePipelineConfigurationDialog().
- L86 _public function_ `EInterchangePipelineConfigurationDialogResult ScriptedShowScenePipelineConfigurationDialog_Implementation(TArray<FInterchangeStackInfo>& PipelineStacks , TArray<UInterchangePipelineBase*>& OutPipelines , UInterchangeSourceData* SourceData , UInterchangeTranslatorBase* Translator , UInterchangeBaseNodeContainer* BaseNodeContainer)` — The default implementation, which is called if the Blueprint does not have any implementation, calls the virtual ShowScenePipelineConfigurationDialog().
- L112 _public prototype_ `EInterchangePipelineConfigurationDialogResult ScriptedShowReimportPipelineConfigurationDialog(TArray<FInterchangeStackInfo>& PipelineStacks , TArray<UInterchangePipelineBase*>& OutPipelines , UInterchangeSourceData* SourceData , UInterchangeTranslatorBase* Translator , UInterchangeBaseNodeContainer* BaseNodeContainer , UObject* ReimportAsset , bool bSceneImport = false);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interchange | Translator")` — Non-virtual helper that allows Blueprint to implement an event-based function to implement ShowReimportPipelineConfigurationDialog().
- L121 _public function_ `EInterchangePipelineConfigurationDialogResult ScriptedShowReimportPipelineConfigurationDialog_Implementation(TArray<FInterchangeStackInfo>& PipelineStacks , TArray<UInterchangePipelineBase*>& OutPipelines , UInterchangeSourceData* SourceData , UInterchangeTranslatorBase* Translator , UInterchangeBaseNodeContainer* BaseNodeContainer , UObject* ReimportAsset , bool bSceneImport = false)` — The default implementation, which is called if the Blueprint does not have any implementation, calls the virtual ShowReimportPipelineConfigurationDialog().
- L149 _public prototype_ `EInterchangePipelineConfigurationDialogResult ScriptedShowTestPlanConfigurationDialog(TArray<FInterchangeStackInfo>& PipelineStacks , TArray<UInterchangePipelineBase*>& OutPipelines , UInterchangeSourceData* SourceData , UInterchangeTranslatorBase* Translator , UInterchangeBaseNodeContainer* BaseNodeContainer , UObject* ReimportAsset , bool bSceneImport = false , bool bReimport = false);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interchange | Translator")` — Non-virtual helper that allows Blueprint to implement an event-based function to implement ShowTestPlanPipelineConfigurationDialog().
- L159 _public function_ `EInterchangePipelineConfigurationDialogResult ScriptedShowTestPlanConfigurationDialog_Implementation(TArray<FInterchangeStackInfo>& PipelineStacks , TArray<UInterchangePipelineBase*>& OutPipelines , UInterchangeSourceData* SourceData , UInterchangeTranslatorBase* Translator , UInterchangeBaseNodeContainer* BaseNodeContainer , UObject* ReimportAsset , bool bSceneImport = false , bool bReimport = false)` — The default implementation, which is called if the Blueprint does not have any implementation, calls the virtual ShowTestPlanAssetPipelineConfigurationDialog().
- L200 _protected function_ `virtual EInterchangePipelineConfigurationDialogResult ShowPipelineDialog_Internal(FPipelineConfigurationDialogParams& InParams)`

#### struct `UInterchangePipelineConfigurationBase::FPipelineConfigurationDialogParams`  
`struct FPipelineConfigurationDialogParams`  
_L185-198_
- L187 _public member_ `TArray<FInterchangeStackInfo>& PipelineStacks;`
- L188 _public member_ `TArray<UInterchangePipelineBase*>& OutPipelines;`
- L189 _public member_ `TWeakObjectPtr<UInterchangeSourceData> SourceData;`
- L190 _public member_ `TWeakObjectPtr <UInterchangeTranslatorBase> Translator;`
- L191 _public member_ `TWeakObjectPtr <UInterchangeBaseNodeContainer> BaseNodeContainer;`
- L192 _public member_ `TWeakObjectPtr <UObject> ReimportAsset;`
- L193 _public member_ `bool bReimport;`
- L194 _public member_ `bool bSceneImport;`
- L195 _public member_ `bool bInvokedThroughTestPlan;`
- L196 _public member_ `TOptional<bool> bOverrideDefaultShowEssentials;`
- L197 _public member_ `TOptional<bool> bOverrideDefaultFilterOnContent;`

### `Source/Runtime/Interchange/Engine/Public/InterchangeProjectSettings.h` (Public)


#### struct `FInterchangeTranslatorPipelines`  
`struct FInterchangeTranslatorPipelines`  
_L19-28_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public member_ `TSoftClassPtr<UInterchangeTranslatorBase> Translator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TranslatorPipelines", meta = (AllowedClasses = "/Script/InterchangeCore.InterchangeTranslatorBase"))`
- L27 _public member_ `TArray<FSoftObjectPath> Pipelines;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TranslatorPipelines", meta = (AllowedClasses = "/Script/InterchangeCore.InterchangePipelineBase, /Script/InterchangeEngine.InterchangeBlueprintPipelineBase, /Script/InterchangeEngine.InterchangePythonPipelineAsset"))`

#### struct `FInterchangePipelineStack`  
`struct FInterchangePipelineStack`  
_L31-42_
- reflection: `USTRUCT(BlueprintType)`
- L37 _public member_ `TArray<FSoftObjectPath> Pipelines;` — `UPROPERTY(EditAnywhere, Category = "Pipelines", meta = (AllowedClasses = "/Script/InterchangeCore.InterchangePipelineBase, /Script/InterchangeEngine.InterchangeBlueprintPipelineBase, /Script/InterchangeEngine.InterchangePythonPipelineAsset"))` — The list of pipelines in this stack. The pipelines are executed in fixed order, from top to bottom.
- L41 _public member_ `TArray<FInterchangeTranslatorPipelines> PerTranslatorPipelines;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TranslatorPipelines")` — Specifies a different list of pipelines for this stack to use when importing data from specific translators.

#### struct `FInterchangePerTranslatorDialogOverride`  
`struct FInterchangePerTranslatorDialogOverride`  
_L45-59_
- reflection: `USTRUCT(BlueprintType)`
- L50 _public member_ `TSoftClassPtr<UInterchangeTranslatorBase> Translator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogOverride", meta = (AllowedClasses = "/Script/InterchangeCore.InterchangeTranslatorBase"))`
- L54 _public member_ `bool bShowImportDialog = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogOverride")` — Show the options dialog when Interchange imports.
- L58 _public member_ `bool bShowReimportDialog = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogOverride")` — Show the options dialog when Interchange reimports.

#### struct `FInterchangeDialogOverride`  
`struct FInterchangeDialogOverride`  
_L62-76_
- reflection: `USTRUCT(BlueprintType)`
- L68 _public member_ `bool bShowImportDialog = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogOverride")` — Show the options dialog when Interchange imports.
- L72 _public member_ `bool bShowReimportDialog = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogOverride")` — Show the options dialog when Interchange reimports.
- L75 _public member_ `TArray<FInterchangePerTranslatorDialogOverride> PerTranslatorImportDialogOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogOverride")`

#### struct `FInterchangeImportSettings`  
`struct FInterchangeImportSettings`  
_L79-102_
- reflection: `USTRUCT(BlueprintType)`
- L85 _public member_ `TMap<FName, FInterchangePipelineStack> PipelineStacks;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipeline")` — Configures the pipeline stacks that are available when importing assets with Interchange.
- L89 _public member_ `FName DefaultPipelineStack = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipeline")` — Specifies which pipeline stack Interchange should use by default.
- L93 _public member_ `TSoftClassPtr <UInterchangePipelineConfigurationBase> ImportDialogClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipeline")` — Specifies the class that should be used to define the configuration dialog that Interchange shows on import.
- L97 _public member_ `bool bShowImportDialog = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogOverride")` — Show the options dialog when Interchange imports.
- L101 _public member_ `bool bShowReimportDialog = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogOverride")` — Show the options dialog when Interchange reimports.

#### struct `FInterchangeSceneImportSettings`  
`struct FInterchangeSceneImportSettings : public FInterchangeImportSettings`  
_L105-111_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FInterchangeImportSettings`
- L110 _public member_ `TArray<FInterchangePerTranslatorDialogOverride> PerTranslatorDialogOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogOverride", Meta=(DisplayAfter="bShowReimportDialog"))`

#### struct `FInterchangeContentImportSettings`  
`struct FInterchangeContentImportSettings : public FInterchangeImportSettings`  
_L114-124_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FInterchangeImportSettings`
- L120 _public member_ `TMap<EInterchangeTranslatorAssetType, FName> DefaultPipelineStackOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipeline", Meta=(DisplayAfter="DefaultPipelineStack"))` — Specifies a different pipeline stack for Interchange to use by default when importing specific types of assets.
- L123 _public member_ `TMap<EInterchangeTranslatorAssetType, FInterchangeDialogOverride> ShowImportDialogOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogOverride", Meta=(DisplayAfter="bShowReimportDialog"))`

#### struct `FInterchangeGroup`  
`struct FInterchangeGroup`  
_L127-165_
- reflection: `USTRUCT(BlueprintType)`
- L140 _public member_ `FName DisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InterchangeGroup")` — Specifies a different pipeline stack for Interchange to use by default when importing specific types of assets.
- L144 _public member_ `FGuid UniqueID = FGuid::NewGuid();` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InterchangeGroup", meta = (IgnoreForMemberInitializationTest, EditCondition = "false", EditConditionHides))` — This tell interchange if the import dialog should show or not when importing a particular type of asset.
- L148 _public member_ `FName DefaultPipelineStack = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipeline")` — Specifies which pipeline stack Interchange should use by default.
- L152 _public member_ `TMap<EInterchangeTranslatorAssetType, FName> DefaultPipelineStackOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipeline", Meta = (DisplayAfter = "DefaultPipelineStack"))` — Specifies a different pipeline stack for Interchange to use by default when importing specific types of assets.
- L156 _public member_ `bool bShowImportDialog = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogOverride")` — Show the options dialog when Interchange imports.
- L160 _public member_ `bool bShowReimportDialog = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogOverride")` — Show the options dialog when Interchange reimports.
- L164 _public member_ `TMap<EInterchangeTranslatorAssetType, FInterchangeDialogOverride> ShowImportDialogOverride;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DialogOverride")` — This tell interchange if the import dialog should show or not when importing a particular type of asset.

#### enum `FInterchangeGroup::EUsedGroupStatus`  
`enum EUsedGroupStatus : uint8`  
_L131-136_
- L133 _public enumerator_ `NotSet`
- L134 _public enumerator_ `SetAndValid`
- L135 _public enumerator_ `SetAndInvalid`

#### class `UInterchangeProjectSettings`  
`class UInterchangeProjectSettings : public UDeveloperSettings`  
_L168-220_
- reflection: `UCLASS(config=Engine, BlueprintType, meta=(DisplayName=Interchange), MinimalAPI)`
- inherits: `UDeveloperSettings`
- L177 _public member_ `FInterchangeContentImportSettings ContentImportSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "ImportContent")` — Settings used when importing into the Content Browser.
- L183 _public member_ `FInterchangeSceneImportSettings SceneImportSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "ImportIntoLevel")` — Settings used when importing into a level.
- L187 _public member_ `TSoftClassPtr <UInterchangeFilePickerBase> FilePickerClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "EditorInterface")` — This tells Interchange which file picker class to construct when we need to choose a file for a source.
- L194 _public member_ `bool bStaticMeshUseSmoothEdgesIfSmoothingInformationIsMissing = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Generic|ImportSettings")` — If enabled, both Interchange translators and the legacy import process smooth the edges of static meshes that don't contain smoothing information. If you have an older project that relies on leaving hard edges by default, you can disable this setting to preserve consistency with older assets.
- L201 _public member_ `TSoftClassPtr <UInterchangePipelineBase> GenericPipelineClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Editor Generic Pipeline Class")` — Specifies which pipeline class Interchange should use when editor tools import or reimport an asset with base settings. Unreal Editor depends on this class to be set. You can only edit this property in the .ini file.
- L208 _public member_ `FSoftObjectPath ConverterDefaultPipeline;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Converters", meta = (AllowedClasses = "/Script/InterchangeCore.InterchangePipelineBase, /Script/InterchangeEngine.InterchangeBlueprintPipelineBase, /Script/InterchangeEngine.InterchangePythonPipelineAsset"))` — Optional, the pipeline asset converters will duplicate to create interchange import data pipeline. If not set, converters will duplicate a pipeline class CDO of there choice.
- L214 _public member_ `TArray<FInterchangeGroup> InterchangeGroups;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Groups", meta = (NoElementDuplicate))` — Groups that define PerTransalatorPipelines that user can select to use.
- L218 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### class `FInterchangeProjectSettingsUtils`  
`class FInterchangeProjectSettingsUtils`  
_L222-238_
- L225 _public prototype_ `static const FInterchangeImportSettings& GetImportSettings(const UInterchangeProjectSettings& InterchangeProjectSettings, const bool bIsSceneImport);`
- L226 _public prototype_ `static FInterchangeImportSettings& GetMutableImportSettings(UInterchangeProjectSettings& InterchangeProjectSettings, const bool bIsSceneImport);`
- L227 _public prototype_ `static const FInterchangeImportSettings& GetDefaultImportSettings(const bool bIsSceneImport);`
- L228 _public prototype_ `static FInterchangeImportSettings& GetMutableDefaultImportSettings(const bool bIsSceneImport);`
- L230 _public prototype_ `static FName GetDefaultPipelineStackName(const bool bIsSceneImport, const UInterchangeSourceData& SourceData);`
- L231 _public prototype_ `static void SetDefaultPipelineStackName(const bool bIsSceneImport, const UInterchangeSourceData& SourceData, const FName StackName);`
- L233 _public prototype_ `static bool ShouldShowPipelineStacksConfigurationDialog(const bool bIsSceneImport, const bool bReImport, const UInterchangeSourceData& SourceData);`
- L235 _public prototype_ `static const FInterchangeGroup& GetUsedGroup(FInterchangeGroup::EUsedGroupStatus& UsedGroupStatus);`
- L237 _public prototype_ `static TArray<FName> GetGroupNames();`

#### class `UInterchangeProjectSettingsScript`  
`class UInterchangeProjectSettingsScript : public UObject`  
_L241-268_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L251 _public prototype_ `static TArray<UInterchangePipelineBase*> GetPipelineArrayFromPipelineStack(const FInterchangePipelineStack& InterchangePipelineStack);` — `UFUNCTION(BlueprintCallable, Category = "Interchange Settings")` — Pipeline stack store SoftObjectPath which are not supported in python, you can use this function to retrieve the object from FInterchangePipelineStack. @note: It return duplicated pipeline objects
- L259 _public prototype_ `static TArray<UInterchangePipelineBase*> GetPipelineArrayFromTranslatorPipelines(const FInterchangeTranslatorPipelines& InterchangeTranslatorPipeline);` — `UFUNCTION(BlueprintCallable, Category = "Interchange Settings")` — Pipeline stack store SoftObjectPath which are not supported in python, you can use this function to retrieve the object from FInterchangeTranslatorPipelines. @note: It return duplicated pipeline objects
- L267 _public prototype_ `static TArray<UInterchangePipelineBase*> GetPipelineStackFromSourceData(const bool bIsSceneImport, const UInterchangeSourceData* SourceData);` — `UFUNCTION(BlueprintCallable, Category = "Interchange Settings")` — Return the default settings pipeline stack for the specified source data. @note: It return duplicated pipeline objects

#### class `UInterchangeEditorSettings`  
`class UInterchangeEditorSettings : public UDeveloperSettings`  
_L271-306_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, BlueprintType, meta = (DisplayName = Interchange), MinimalAPI)`
- inherits: `UDeveloperSettings`
- L278 _public member_ `bool bShowImportDialogAtReimport = false;` — `UE_DEPRECATED(5.6, "Use the dialog overrides on the Interchange category of the Project Settings if you want to control when the Interchange reimport dialog is shown")` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "Show Dialog", meta=(EditCondition = "false", ToolTip="Use the dialog overrides on the Interchange category of the Project Settings if you want to control when the Interchange reimport dialog is shown"))`
- L280 _public function_ `const FGuid& GetUsedGroupUID() const`
- L283 _public function_ `const FName& GetUsedGroupName() const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Groups")`
- L286 _public prototype_ `void SetUsedGroupName(const FName& InUsedGroupName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Groups")`
- L288 _public prototype_ `void UpdateUsedGroupName();`
- L292 _private member_ `FName UsedGroupName;` — `UPROPERTY(EditAnywhere, Transient, Category = "Group Used", meta = (GetOptions = "GetSelectableItems", AllowPrivateAccess = "true"))`
- L295 _private member_ `FGuid UsedGroupUID;` — `UPROPERTY(EditAnywhere, Category = "Group Used", config, meta = (IgnoreForMemberInitializationTest, EditCondition = "false", EditConditionHides))`
- L298 _private prototype_ `TArray<FName> GetSelectableItems() const;` — `UFUNCTION()`
- L300 _private prototype_ `void UpdateUsedGroupUIDFromGroupName();`
- L303 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L304 _private prototype_ `virtual void PostInitProperties() override;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API INTERCHANGEENGINE_API`

### `Source/Runtime/Interchange/Engine/Public/InterchangePythonPipelineBase.h` (Public)


#### class `UInterchangePythonPipelineBase`  
`class UInterchangePythonPipelineBase : public UInterchangePipelineBase`  
_L17-25_
- reflection: `UCLASS(BlueprintType, Abstract, MinimalAPI)`
- inherits: `UInterchangePipelineBase`
- desc: This class represents a Python pipeline. It is used by the TSoftClassPtr of the PythonPipeline asset.
- L23 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### struct `FPropertyData`  
`struct FPropertyData`  
_L29-35_
- reflection: `USTRUCT()`
- L33 _public member_ `FString DefaultValue;`
- L34 _public member_ `bool bLocked = false;`

#### class `UInterchangePythonPipelineAsset`  
`class UInterchangePythonPipelineAsset : public UObject`  
_L47-71_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: This class is a helper class for Python pipelines. It allows the class picker to filter the Content Browser instance we want to support in the pipeline stack. Use this class factory to be able to create an instance of a Python pipeline in the Content Browser. A Python pipeline does not have any locked properties, and all default values must be set in the Python script. This restriction exists because Python classes are transient, so any assets created from a Python class cannot be saved.
- L52 _public prototype_ `virtual void PostLoad() override;`
- L54 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L57 _public prototype_ `void GeneratePipeline();`
- L59 _public prototype_ `void SetupFromPipeline(const UInterchangePythonPipelineBase* PythonPipeline, const bool bRegeneratePipeline = true);`
- L63 _public member_ `TSoftClassPtr<UInterchangePythonPipelineBase> PythonClass;` — `UPROPERTY(EditAnywhere, Category = "Interchange|Python")` — The Python class we want to use as a pipeline.
- L67 _public member_ `TObjectPtr<UInterchangePythonPipelineBase> GeneratedPipeline;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "Interchange|Python")` — The transient pipeline we generate when we load the Python pipeline.
- L70 _public member_ `FString JsonDefaultProperties;` — `UPROPERTY(VisibleAnywhere, Category = "Interchange|Python")`

### `Source/Runtime/Interchange/Engine/Public/InterchangeSceneImportAsset.h` (Public)


#### class `UInterchangeSceneImportAsset`  
`class UInterchangeSceneImportAsset : public UObject, public IInterface_AssetUserData`  
_L21-134_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IInterface_AssetUserData`
- desc: Class to hold all the data required to properly re-import a level
- L25 _private prototype_ `virtual ~UInterchangeSceneImportAsset();`
- L31 _public member_ `TObjectPtr<UInterchangeAssetImportData> AssetImportData;` — `UPROPERTY(EditAnywhere, Instanced, Category=ImportSettings)` — Importing data and options used for this scene
- L35 _public member_ `TArray< TObjectPtr<UAssetUserData> > AssetUserData;` — `UPROPERTY()` — Array of user data stored with the asset
- L39 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L41 _public prototype_ `virtual void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const override;` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L42 _public prototype_ `virtual void PostLoad() override;`
- L46 _public prototype_ `virtual void AddAssetUserData( UAssetUserData* InUserData ) override;`
- L47 _public prototype_ `virtual void RemoveUserDataOfClass( TSubclassOf<UAssetUserData> InUserDataClass ) override;`
- L48 _public prototype_ `virtual UAssetUserData* GetAssetUserDataOfClass( TSubclassOf<UAssetUserData> InUserDataClass ) override;`
- L49 _public prototype_ `virtual const TArray<UAssetUserData*>* GetAssetUserDataArray() const override;`
- L53 _public prototype_ `void RegisterWorldRenameCallbacks();`
- L57 _public prototype_ `void UpdateSceneObjects();` — Updates the SceneObjects cache based on the node container stored in AssetImportData
- L67 _public prototype_ `UObject* GetSceneObject(const FString& PackageName, const FString& AssetName, const FString& SubPathString = FString()) const;` — Returns the UObject which asset path is '//PackageName.AssetName[:SubPathString]'. Returns nullptr if the asset which path is '//PackageName.AssetName[:SubPathString]' was not part of the level import cached in this UInterchangeSceneImportAsset. @param PackageName: Package path of the actual object to reimport @param AssetName: Asset name of the actual object to reimport @param SubPathString: Optional subobject name
- L70 _public function_ `const UInterchangeFactoryBaseNode* GetFactoryNode(const FString& PackageName, const FString& AssetName, const FString& SubPathString = FString()) const` — `UE_DEPRECATED(5.8, "This function is deprecated. Use the GetFactoryNodeFromPath() instead.")`
- L76 _public function_ `const UInterchangeFactoryBaseNode* GetFactoryNode(const FSoftObjectPath& ObjectPath) const` — `UE_DEPRECATED(5.8, "This function is deprecated. Use the GetFactoryNodeFromPath() instead.")`
- L89 _public prototype_ `const UInterchangeFactoryBaseNode* GetFactoryNodeFromPath(const FString& PackageName, const FString& AssetName, const FString& SubPathString = FString()) const;` — Returns the factory node associated with the asset which path is '//PackageName.AssetName[:SubPathString]'. Returns nullptr if the asset which path is '//PackageName.AssetName[:SubPathString]' was not part of the level import cached in this UInterchangeSceneImportAsset. @param PackageName: Package path of the actual object to reimport @param AssetName: Asset name of the actual object to reimport @param SubPathString: Optional subobject name
- L91 _public prototype_ `const UInterchangeFactoryBaseNode* GetFactoryNodeFromPath(const FSoftObjectPath& ObjectPath) const;`
- L98 _public prototype_ `const UInterchangeFactoryBaseNode* GetFactoryNodeFromUniqueID(const FString& InNodeUniqueId) const;` — Returns the factory node associated with a Node UID. @param InNodeUniqueId: Unique ID of the Node @return Factory Node if available or nullptr.
- L104 _public prototype_ `TArray<const UInterchangeFactoryBaseNode*> GetFactoryNodesOfClass(const UClass* Class) const;` — Returns the array of factory nodes corresponding to the given class. @param Class: Class to be looked for
- L106 _public prototype_ `void GetSceneSoftObjectPaths(TArray<FSoftObjectPath>& SoftObjectPaths) const;`
- L108 _public prototype_ `bool ContainsObject(const FSoftObjectPath& SoftObjectPath) const;`
- L114 _private prototype_ `void OnPreWorldRename(UWorld* World, const TCHAR* InName, UObject* NewOuter, ERenameFlags Flags, bool& bShouldFailRename);` — Called before a world is renamed
- L117 _private prototype_ `void OnPostWorldRename(UWorld* World);` — Invoked when a world is successfully renamed. Used to track when a temporary 'Untitled' unsaved map is saved with a new name.
- L120 _private member_ `bool bWorldRenameCallbacksRegistered = false;` — Members used to cache the path and names related to the world to be renamed
- L121 _private member_ `FString PreviousWorldPath;`
- L122 _private member_ `FString PreviousWorldName;`
- L123 _private member_ `FString PreviousLevelName;`
- L132 _private member_ `TMap< FSoftObjectPath, FString > SceneObjects;` — Cache to easily retrieve a factory node from an asset's/actor's path FSoftObjectPath stores the path of an imported object FString stores the unique id of the factory node associated with the imported object

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API INTERCHANGEENGINE_API`
