# Runtime / InterchangeCore

- module root: `Source/Runtime/Interchange/Core`
- headers: 20; symbols: 1083
- symbol kinds: class=36, delegate=4, enum=16, enumerator=191, function=265, macro=15, member=148, namespace=18, prototype=344, struct=22, typedef=19, variable=5
- PrivateDependencyModuleNames: Analytics, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, Json

### `Source/Runtime/Interchange/Core/Private/InterchangeLogPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeCore, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInterchangeCore, Log, All);`

### `Source/Runtime/Interchange/Core/Public/InterchangeCustomVersion.h` (Public)


#### struct `FInterchangeCustomVersion`  
`struct FInterchangeCustomVersion`  
_L8-38_
- desc: Custom serialization version for changes to variant manager objects
- L34 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L37 _private function_ `FInterchangeCustomVersion()`

#### enum `FInterchangeCustomVersion::Type`  
`enum Type`  
_L10-31_
- L13 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Roughly corresponds to 5.2
- L15 _public enumerator_ `SerializedInterchangeObjectStoring`
- L17 _public enumerator_ `MultipleAllocationsPerAttributeInStorage`
- L20 _public enumerator_ `MultipleAllocationsPerAttributeInStorageFixed` — The change that implemented the previous version had to be backed out to fix a serialization issue
- L23 _public enumerator_ `AdditionOfReuseExistingMaterialsBool` — Replaced 'DoNotSearch' Material's search location enum value with a boolean property
- L26 _public enumerator_ `SkeletalAndStaticMeshOptionsCleanUp` — Moved mesh conversion setting from UInterchangeGenericCommonSkeletalMeshesAndAnimationsProperties to UInterchangeGenericCommonMeshesProperties
- L29 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L30 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Source/Runtime/Interchange/Core/Public/InterchangeFactoryBase.h` (Public)


#### enum `EInterchangeFactoryAssetType`  
`enum class EInterchangeFactoryAssetType : uint8`  
_L23-36_
- reflection: `UENUM(BlueprintType)`
- L25 _public enumerator_ `None = 0`
- L26 _public enumerator_ `Textures`
- L27 _public enumerator_ `Materials`
- L28 _public enumerator_ `Meshes`
- L29 _public enumerator_ `Animations`
- L30 _public enumerator_ `Physics`
- L31 _public enumerator_ `Grooms`
- L32 _public enumerator_ `Sounds`
- L33 _public enumerator_ `Levels`
- L34 _public enumerator_ `Variants`
- L35 _public enumerator_ `Custom`

#### class `FInterchangePostImportTask`  
`class FInterchangePostImportTask`  
_L43-47_
- desc: Base class for post import task. Post import tasks are execute by the InterchangeManager when there is no import task to execute. See more detail in the Interchange manager header.
- L46 _public function_ `virtual void Execute()`

#### class `UInterchangeFactoryBase`  
`class UInterchangeFactoryBase : public UObject`  
_L70-472_
- reflection: `UCLASS(BlueprintType, Blueprintable, Abstract, MinimalAPI)`
- inherits: `UObject`
- L79 _public function_ `virtual UClass* GetFactoryClass() const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Factory")` — Return the UClass this factory can create.
- L88 _public function_ `virtual EInterchangeFactoryAssetType GetFactoryAssetType()` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Factory")` — Return the asset type this factory can create.
- L131 _public function_ `virtual UObject* ImportAssetObject_GameThread(const FImportAssetObjectParams& Arguments)` — `UE_DEPRECATED(5.3, "This function is replaced by BeginImportAsset_GameThread.")`
- L136 _public function_ `virtual void CreatePayloadTasks(const FImportAssetObjectParams& Arguments, bool bAsync, TArray<TSharedPtr<UE::Interchange::FInterchangeTaskBase>>& PayloadTasks)`
- L150 _public function_ `virtual FImportAssetResult BeginImportAsset_GameThread(const FImportAssetObjectParams& Arguments)` — Override this function to import/reimport source data and configure the properties synchronously. Create the asset package on the game thread because it's not thread-safe. @param Arguments - The structure that contains all necessary arguments to import the UObject and the package. See the structure definition for its documentation. @return the FImportAssetResult. See the structure to access its documentation. @Note Mandatory to override this function to create the asset UObject package. Not mandatory for level actor; use CreateSceneObject instead.
- L160 _public function_ `virtual UObject* ImportAssetObject_Async(const FImportAssetObjectParams& Arguments)` — `UE_DEPRECATED(5.3, "This function is replaced by ImportAsset_Async.")`
- L178 _public function_ `virtual FImportAssetResult ImportAsset_Async(const FImportAssetObjectParams& Arguments)` — Override this function to import/reimport the UObject source data and configure the properties asynchronously. Do not create the asset UObject asynchronously. Helpful to get all the payloads in parallel or do any long import tasks. @param Arguments - The structure that contains all necessary data to import the UObject. See the structure definition for its documentation. @return the FImportAssetResult. See the structure to access its documentation.
- L194 _public function_ `virtual FImportAssetResult EndImportAsset_GameThread(const FImportAssetObjectParams& Arguments)` — Override this function to end import/reimport on the game thread. Helpful if you need to display UI (for example, reimport material conflict resolution) or if you need to do anything not thread-safe to complete the import/reimport. @param Arguments - The structure that contains all necessary data to import the UObject. See the structure definition for its documentation. @return the FImportAssetResult. See the structure to access its documentation.
- L256 _public function_ `virtual UObject* ImportSceneObject_GameThread(const FImportSceneObjectsParams& Arguments)` — Creates the scene object from a Scene Node data. @param Arguments - The structure that contains all necessary arguments. See the structure definition for its documentation. @return The scene object, or nullptr if the operation was unsuccessful.
- L262 _public function_ `virtual void Cancel()` — Call when the user cancels the operation.
- L289 _public function_ `virtual void SetupObject_GameThread(const FSetupObjectParams& Arguments)` — Do any UObject setup required before the build and after all dependency UObjects have been imported. @note - This function is called when starting the pre-completion task (before asset build is called for the asset).
- L302 _public function_ `virtual void BuildObject_GameThread(const FSetupObjectParams& Arguments, bool& OutPostEditchangeCalled)` — Build the asset if it can be built. @Param Arguments - The setup object data. @Param OutPostEditchangeCalled - Set it to true if your implementation has called PostEditChange. Set it to false, interchange will call PostEditChange at the end of the import. @note - This function is called when starting the pre-completion task. @note - The default implementation for asset that do not have any build step is to call PostEditChange and set OutPostEditchangeCalled to true.
- L318 _public function_ `virtual void FinalizeObject_GameThread(const FSetupObjectParams& Arguments)` — Do any final UObject setup after the asset is built @note - This function is called after asset is built in FTaskWaitAssetCompilation
- L328 _public function_ `virtual bool GetSourceFilenames(const UObject* Object, TArray<FString>& OutSourceFilenames) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Factory")` — Fills the OutSourceFilenames array with the list of source files contained in the asset source data. Returns true if the operation was successful.
- L337 _public function_ `virtual bool SetSourceFilename(const UObject* Object, const FString& SourceFilename, int32 SourceIndex) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Factory")` — Sets the object's source at the specified index to the given SourceFileName.
- L345 _public function_ `virtual void BackupSourceData(const UObject* Object) const` — Backups SourceData from the AssetData.
- L352 _public function_ `virtual void ReinstateSourceData(const UObject* Object) const` — Reinstates the backedup SourceData from the Backup to the AssetData.
- L359 _public function_ `virtual void ClearBackupSourceData(const UObject* Object) const` — Clears the backedup SourceData from the Backup to the AssetData.
- L366 _public function_ `virtual bool SetReimportSourceIndex(const UObject* Object, int32 SourceIndex) const` — Set the object's reimport source at the specified index value.
- L375 _public function_ `template <typename T> T* AddMessage()` — This function is used to add the given message object directly into the results for this operation.
- L383 _public function_ `void AddMessage(UInterchangeResult* Item)`
- L390 _public function_ `void SetResultsContainer(UInterchangeResultsContainer* InResults)`
- L399 _public function_ `void PreResetObjectProperties(const UInterchangeBaseNodeContainer* BaseNodeContainer, UInterchangeFactoryBaseNode* FactoryNode, UObject* ImportedObject)` — Called before resetting object properties. Restores all the tracked custom attribute delegates.
- L411 _public function_ `void ResetObjectProperties(const UInterchangeBaseNodeContainer* BaseNodeContainer, UInterchangeFactoryBaseNode* FactoryNode, UObject* ImportedObject)` — Re-apply all the custom attributes that were set on the Factory Node to the Object. Useful when resetting the object to its original imported state, unless the factory node's attributes have been changed.
- L427 _public function_ `void PostResetObjectProperties(const UInterchangeBaseNodeContainer* BaseNodeContainer, UInterchangeFactoryBaseNode* FactoryNode, UObject* ImportedObject)` — Called after resetting object properties. Useful for doing any cleanup required.
- L439 _public function_ `virtual UObject* GetObjectToReimport(UObject* ReimportObject, const UInterchangeFactoryBaseNode& FactoryNode, const FString& PackageName, const FString& AssetName, const FString& SubPathString)` — Acquires the Object to be re-imported. Function is called from FFactoryCommon::GetObjectToReiomport. Which in turn is called from the InterchangeTask related functions to acquire the Object to be Reimported. Allows Factories to override, in order to provide the desired ReimportObject based on Factory requirements.
- L449 _protected function_ `virtual void ExecutePreResetObjectProperties(const UInterchangeBaseNodeContainer* BaseNodeContainer, UInterchangeFactoryBaseNode* FactoryNode, UObject* ImportedObject)` — Override this method in the child classes, to support custom behavior for PreResetObjectProperties
- L457 _protected function_ `virtual void ExecuteResetObjectProperties(const UInterchangeBaseNodeContainer* BaseNodeContainer, UInterchangeFactoryBaseNode* FactoryNode, UObject* ImportedObject)` — Override this method in the child classes if the Custom Attributes are not directly applied to the imported object E.g. Actor Factories need root component/other components in the hierarchy. Actor Factory overrides this method for custom behavior
- L465 _protected function_ `virtual void ExecutePostResetObjectProperties(const UInterchangeBaseNodeContainer* BaseNodeContainer, UInterchangeFactoryBaseNode* FactoryNode, UObject* ImportedObject)` — Override this method in the child classes, to support custom behavior for PostResetObjectProperties
- L471 _public member_ `TObjectPtr<UInterchangeResultsContainer> Results;` — `UPROPERTY()`

#### struct `UInterchangeFactoryBase::FImportAssetObjectParams`  
`struct FImportAssetObjectParams`  
_L93-118_
- desc: Parameters to pass to the CreateAsset function.
- L96 _public member_ `UObject* Parent = nullptr;` — The package where the asset should be created. If null, it will be put in the transient package.
- L99 _public member_ `FString AssetName = FString();` — The name to give to the created asset.
- L102 _public member_ `UInterchangeFactoryBaseNode* AssetNode = nullptr;` — The base node that describes how to create the asset.
- L105 _public member_ `const UInterchangeTranslatorBase* Translator = nullptr;` — The translator is used to retrieve the payLoad data in case the factory needs it.
- L108 _public member_ `const UInterchangeSourceData* SourceData = nullptr;` — The source data. TODO: we have to refactor UAssetImportData, the source data should be the base class for this now
- L111 _public member_ `const UInterchangeBaseNodeContainer* NodeContainer = nullptr;` — The node container associated with the current source index.
- L117 _public member_ `UObject* ReimportObject = nullptr;` — If when we try to create the package we find out the asset already exists, this field will contain the asset we want to reimport. The reimport should just change the source data and not any asset settings.

#### struct `UInterchangeFactoryBase::FImportAssetResult`  
`struct FImportAssetResult`  
_L120-128_
- L125 _public member_ `bool bIsFactorySkipAsset = false;` — If the factory sets this to true, the Interchange task import object should skip this asset. An asset can be skipped if it already exists and the factory isn't doing a reimport. For example, if we import a static mesh and we find an existing material. We don't want to override the material in this case because the UE material often contains content related to gameplay.
- L127 _public member_ `UObject* ImportedObject = nullptr;` — Return the UObject imported or reimported by the factory, or leave it set to nullptr if there was an error.

#### struct `UInterchangeFactoryBase::FImportSceneObjectsParams`  
`struct FImportSceneObjectsParams`  
_L209-248_
- desc: Parameters to pass to the SpawnActor function.
- L212 _public member_ `ULevel* Level = nullptr;` — The level in which to create the scene objects.
- L215 _public member_ `FString ObjectName;` — The name to give to the created actor.
- L218 _public member_ `UInterchangeFactoryBaseNode* FactoryNode = nullptr;` — The base node that describes how to create the asset.
- L221 _public member_ `const UInterchangeBaseNodeContainer* NodeContainer = nullptr;` — The node container associated with the current source index.
- L224 _public member_ `const UInterchangeSourceData* SourceData = nullptr;` — The source data. TODO: we have to refactor UAssetImportData, the source data should be the base class for this now
- L229 _public member_ `UObject* ReimportObject = nullptr;` — If not null, the factory must perform a reimport of the scene node.
- L234 _public member_ `const UInterchangeFactoryBaseNode* ReimportFactoryNode = nullptr;` — Factory base node associated with the reimported scene node.
- L239 _public member_ `bool bIsReimport = false;` — true if we are re-importing
- L247 _public member_ `int32 AsyncHelperUid = INDEX_NONE;` — This represent the async helper unique id in case a factory need to retrieve the asynchelper associate to the import task TODO create a base class for FAsyncHelper in Interchange/Core so we can reference it here instead of using the unique identifier. The asynchelper is currently declare in Interchange/Engine so we can't refer to it here.

#### struct `UInterchangeFactoryBase::FSetupObjectParams`  
`struct FSetupObjectParams`  
_L267-283_
- desc: Parameters to pass to the CreateAsset function.
- L270 _public member_ `const UInterchangeSourceData* SourceData = nullptr;` — The source data, mainly used to set the asset import data file. TODO: we have to refactor UAssetImportData. The source data should be the base class for this now.
- L271 _public member_ `UInterchangeFactoryBaseNode* FactoryNode = nullptr;`
- L275 _public member_ `UObject* ImportedObject = nullptr;` — The UObject we want to execute code on.
- L276 _public member_ `FString NodeUniqueID;`
- L277 _public member_ `UInterchangeBaseNodeContainer* NodeContainer = nullptr;`
- L278 _public member_ `TArray<UInterchangePipelineBase*> Pipelines;`
- L279 _public member_ `TArray<UObject*> OriginalPipelines;`
- L280 _public member_ `UInterchangeTranslatorBase* Translator;`
- L282 _public member_ `bool bIsReimport = false;`

### `Source/Runtime/Interchange/Core/Public/InterchangeHelper.h` (Public)


#### class `UE::Interchange::FScopedLambda`  
`class FScopedLambda`  
_L43-60_
- L46 _public function_ `FScopedLambda(TFunction<void(void)>&& Lambda) : _Lambda(Lambda)`
- L50 _public function_ `~FScopedLambda()`
- L59 _private member_ `TFunction<void(void)> _Lambda;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Interchange` (scope `UE`)
- L14 _prototype_ `void SanitizeName(FString& InOutName, bool bIsJoint = false);` (scope `UE::Interchange`) — Sanitize InOutName so it's both filename and FName compatible. @param InOutName The name to sanitize in place, will be replaced by "Null" if empty or invalid for FName.
- L20 _prototype_ `FString MakeSanitizedName(const FString& InName, bool bIsJoint = false);` (scope `UE::Interchange`) — Returns a sanitized copy of InName, that is both filename and FName compatible. Returns "Null" if empty or invalid for FName.
- L23 _prototype_ `FString MakeName(const FString& InName, bool bIsJoint = false);` (scope `UE::Interchange`) — `UE_DEPRECATED(5.7, "Use MakeSanitizedName instead.")`
- L32 _prototype_ `int32 GetAssetNameMaxCharCount(const FString& ParentPackage);` (scope `UE::Interchange`) — Try to compute a char budget for asset names, including FNames constraints, OS constraints, parent package, and user defined limitation. @param ParentPackage destination of the asset (Package path consume a part of the budget) @return An estimation of the budget for asset names
- L41 _prototype_ `FString GetAssetNameWBudget(const FString& ParentPackage, int32 CharBudget, TCHAR CharReplacement = TEXT('_'));` (scope `UE::Interchange`) — Generate a new name for DesiredAssetName based on a character budget. Any characters out of the budget limit will be stripped out @param DesiredAssetName - the name of the package that needs to fulfill the OS constraints @param CharBudget - characters limit for the new generated name (if 0, the string will be returned with a warning, meaning we couldn't generate a new name) @param CharReplacement - the character replacement of the trimmed substring @return The new generated name if out of budget, or just the string if it's in the budget limitation

### `Source/Runtime/Interchange/Core/Public/InterchangePipelineBase.h` (Public)


#### enum `EInterchangePipelineTask`  
`enum class EInterchangePipelineTask : uint8`  
_L37-43_
- reflection: `UENUM(BlueprintType)`
- L39 _public enumerator_ `PostTranslator`
- L40 _public enumerator_ `PostFactory`
- L41 _public enumerator_ `PostImport`
- L42 _public enumerator_ `Export`

#### enum `EInterchangePipelineContext`  
`enum class EInterchangePipelineContext : uint8`  
_L46-59_
- reflection: `UENUM()`
- L48 _public enumerator_ `None` — Default pipeline instance we refer in the project settings pipeline stack. This context should allow editing of the properties states
- L49 _public enumerator_ `AssetImport`
- L50 _public enumerator_ `AssetReimport`
- L51 _public enumerator_ `SceneImport`
- L52 _public enumerator_ `SceneReimport`
- L53 _public enumerator_ `AssetCustomLODImport`
- L54 _public enumerator_ `AssetCustomLODReimport`
- L55 _public enumerator_ `AssetAlternateSkinningImport`
- L56 _public enumerator_ `AssetAlternateSkinningReimport`
- L57 _public enumerator_ `AssetCustomMorphTargetImport` — Import the content has a combine static mesh so we can add a custom morph target to a skeletal mesh
- L58 _public enumerator_ `AssetCustomMorphTargetReImport`

#### struct `FInterchangePipelineContextParams`  
`struct FInterchangePipelineContextParams`  
_L62-79_
- reflection: `USTRUCT()`
- L67 _public member_ `EInterchangePipelineContext ContextType = EInterchangePipelineContext::None;` — `UPROPERTY()`
- L70 _public member_ `TObjectPtr<UClass> ImportObjectType = nullptr;` — `UPROPERTY()`
- L73 _public member_ `TObjectPtr<UObject> ReimportAsset = nullptr;` — `UPROPERTY()`
- L76 _public member_ `TObjectPtr<const UInterchangeBaseNodeContainer> BaseNodeContainer = nullptr;` — `UPROPERTY()`

#### struct `FInterchangePipelinePropertyStatePerContext`  
`struct FInterchangePipelinePropertyStatePerContext`  
_L82-91_
- reflection: `USTRUCT(BlueprintType)`
- L88 _public member_ `bool bVisible = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property States")` — If true, the property is visible.

#### struct `FInterchangePipelinePropertyStates`  
`struct FInterchangePipelinePropertyStates`  
_L94-174_
- reflection: `USTRUCT(BlueprintType)`
- L99 _public function_ `bool IsPropertyLocked() const` — Return true if the property is locked.
- L104 _public function_ `void SetPropertyLocked(const bool bLockValue)`
- L110 _public function_ `bool IsPropertyPreDialogReset() const` — Return true if the property is locked.
- L115 _public function_ `void SetPropertyPreDialogReset(const bool bPreDialogResetValue)`
- L122 _public function_ `bool IsPropertyVisibleInShowEssentials() const` — Return true if the property is visible for the specified context.
- L128 _public function_ `bool IsPropertyVisible(const bool bIsReimportContext, const bool bIsShowEssentials) const` — Return true if the property is visible for the specified context.
- L138 _public function_ `void SetPropertyImportVisibility(const bool bVisibleValue)`
- L143 _public function_ `void SetPropertyReimportVisibility(const bool bVisibleValue)`
- L148 _public function_ `void SetPropertyShowEssentialsVisibility(const bool bVisibleValue)`
- L155 _public member_ `bool bLocked = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property States")` — If true, the property is locked.
- L159 _public member_ `bool bPreDialogReset = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property States")` — If true, the property will be reset to default when loading the import dialog.
- L163 _public member_ `FInterchangePipelinePropertyStatePerContext BasicLayoutStates;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Context Properties States")` — The property states for the import context.
- L167 _public member_ `FInterchangePipelinePropertyStatePerContext ImportStates;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Context Properties States")` — The property states for the import context
- L171 _public member_ `FInterchangePipelinePropertyStatePerContext ReimportStates;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Context Properties States")` — The property states for the reimport context.

#### struct `FInterchangeConflictInfo`  
`struct FInterchangeConflictInfo`  
_L176-183_
- L178 _public member_ `FString DisplayName;`
- L179 _public member_ `FString Description;`
- L180 _public member_ `FGuid UniqueId;`
- L181 _public member_ `TObjectPtr<UInterchangePipelineBase> Pipeline = nullptr;`
- L182 _public member_ `TSet<UClass*> AffectedAssetClasses;`

#### class `SInterchangeBaseConflictWidget`  
`class SInterchangeBaseConflictWidget : public SCompoundWidget`  
_L185-207_
- inherits: `SCompoundWidget`
- L188 _public function_ `SLATE_BEGIN_ARGS(SInterchangeBaseConflictWidget) : _WidgetWindow(nullptr)`
- L192 _public function_ `SLATE_ARGUMENT(TSharedPtr<SWindow>, WidgetWindow) SLATE_END_ARGS() virtual void SetWidgetWindow(TSharedPtr<SWindow> InWidgetWindow)`
- L201 _public function_ `FVector2D GetMinimumSize(float ApplicationScale) const`
- L206 _protected member_ `TSharedPtr<SWindow> WidgetWindow = nullptr;`

#### class `UInterchangePipelineBase`  
`class UInterchangePipelineBase : public UObject`  
_L219-704_
- reflection: `UCLASS(BlueprintType, Blueprintable, editinlinenew, Abstract, MinimalAPI)`
- inherits: `UObject`
- L240 _public prototype_ `FString ScriptedGetPipelineDisplayName() const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interchange | Pipeline")` — This function is call when we want to list pipeline in the import dialog. If not override the default behavior of this function will search if the pipeline have a FString UPROPERTY named "PipelineDisplayName" and return the property value. If there is no FString UPROPERTY call "PipelineDisplayName" it will return the name of the pipeline asset (UObject::GetName). When creating a pipeline (c++, python or blueprint) you can simply add a UPROPERTY name "PipelineDisplayName" to your pipeline, you do not need to override the function. Use the same category has your other options and put it on the top. The meta tag StandAlonePipelineProperty will hide your PROPERTY if your pipeline is a sub object of another pipeline when showing the import dialog. The meta tag PipelineInternalEditionData make sure the property will be show only when we edit the pipeline object (hidden when showing the import dialog). UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures", meta = (StandAlonePipelineProperty = "True", PipelineInternalEditionData = "True")) FString PipelineDisplayName;
- L242 _public function_ `FString ScriptedGetPipelineDisplayName_Implementation() const` — The default implementation (call if the blueprint do not have any implementation) will call the virtual ExecutePipeline
- L255 _public prototype_ `void ScriptedExecutePipeline(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interchange | Pipeline")` — ScriptedExecutePipeline, is call after the translation and before we parse the graph to call the factory. This is where factory node should be created by the pipeline. Each factory node represent an unreal asset create that will be create by an interchange factory. @note - the FTaskPipeline is calling this function not the virtual one that is call by the default implementation.
- L257 _public function_ `void ScriptedExecutePipeline_Implementation(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath)` — The default implementation, which is called if the Blueprint does not have any implementation, calls the virtual ExecutePipeline().
- L268 _public prototype_ `void ScriptedExecutePostFactoryPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& FactoryNodeKey, UObject* CreatedAsset, bool bIsAReimport);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interchange | Pipeline")` — ScriptedExecutePostFactoryPipeline is called after the factory creates an Unreal asset, but before it calls PostEditChange. @note - The FTaskPreCompletion task calls this function, not the virtual one that is called by the default implementation.
- L270 _public function_ `void ScriptedExecutePostFactoryPipeline_Implementation(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& FactoryNodeKey, UObject* CreatedAsset, bool bIsAReimport)` — The default implementation, which is called if the Blueprint does not have any implementation, calls the virtual ExecutePostFactoryPipeline().
- L282 _public prototype_ `void ScriptedExecutePostImportPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& FactoryNodeKey, UObject* CreatedAsset, bool bIsAReimport);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interchange | Pipeline")` — ScriptedExecutePostImportPipeline is called after an asset is completely imported, after PostEditChange has already been called. This can be useful if you need build data for one asset to finish setting up another asset. @example - A PhysicsAsset needs skeletal mesh render data to be built properly. @note - the FTaskPostImport calls this function not the virtual one that is call by the default implementation.
- L284 _public function_ `void ScriptedExecutePostImportPipeline_Implementation(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& FactoryNodeKey, UObject* CreatedAsset, bool bIsAReimport)` — The default implementation, which is called if the Blueprint does not have any implementation, calls the virtual ExecutePostImportPipeline().
- L296 _public prototype_ `void ScriptedExecutePostBroadcastPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& FactoryNodeKey, UObject* CreatedAsset, bool bIsAReimport);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interchange | Pipeline")` — ScriptedExecutePostBroadcastPipeline is called after an asset is completely imported and the broadcast have been called. This can be useful if you need to unload the asset for any reason (Level reference by level instance need to be unload). @note - the FTaskCompletion_GameThread calls this function not the virtual one that is call by the default implementation.
- L298 _public function_ `void ScriptedExecutePostBroadcastPipeline_Implementation(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& FactoryNodeKey, UObject* CreatedAsset, bool bIsAReimport)` — The default implementation, which is called if the Blueprint does not have any implementation, calls the virtual ExecutePostBroadcastPipeline().
- L309 _public prototype_ `void ScriptedExecuteExportPipeline(UInterchangeBaseNodeContainer* BaseNodeContainer);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interchange | Pipeline")` — Non-virtual helper that allows Blueprint to implement an event-based function. The Interchange manager calls this function, not the virtual one that is called by the default implementation.
- L312 _public function_ `void ScriptedExecuteExportPipeline_Implementation(UInterchangeBaseNodeContainer* BaseNodeContainer)` — The default implementation, which is called if the Blueprint does not have any implementation, calls the virtual ExecuteExportPipeline().
- L318 _public function_ `bool ScriptedCanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask)` — `UE_DEPRECATED(5.4, "This function will be remove, call CanExecuteOnAnyThread function")`
- L329 _public function_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask)` — This function tells the Interchange manager if this pipeline can be executed in async mode. If it returns false, the ScriptedExecuteImportPipeline will be called on the main thread (GameThread). If it returns true, the pipeline will be run in a background thread and possibly in parallel if there are multiple import processes at the same time.
- L339 _public prototype_ `void ScriptedSetReimportSourceIndex(UClass* ReimportObjectClass, const int32 SourceFileIndex);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interchange | Pipeline")` — Non-virtual helper that allows Blueprint to implement an event-based function. the Interchange framework calls this function, not the virtual one that is called by the default implementation.
- L342 _public function_ `void ScriptedSetReimportSourceIndex_Implementation(UClass* ReimportObjectClass, const int32 SourceFileIndex)` — The default implementation, which is called if the Blueprint does not have any implementation, calls the virtual SetReimportContentFromSourceIndex().
- L354 _public function_ `virtual bool IsScripted()` — A non-scripted class should return false here. The default is set to true because scripted classes cannot override this function since it can be called in an asynchronous thread, which is not possible for Python. We cannot call ScriptedCanExecuteOnAnyThread for a scripted Python pipeline from the task parsing async thread. This function allows us to not call it and force the ScriptedExecutePostImportPipeline to execute on the game thread.
- L359 _public prototype_ `static FString GetDefaultConfigFileName();`
- L361 _public prototype_ `void LoadSettings(const FName PipelineStackName, bool bResetPreDialog = false);`
- L363 _public prototype_ `void SaveSettings(const FName PipelineStackName);`
- L372 _public prototype_ `virtual void AdjustSettingsForContext(const FInterchangePipelineContextParams& ContextParams);` — This function is called before we show the pipeline dialog. Pipelines that override it can change the existing settings according to the reimport type. The function is also called when we import or reimport custom LOD and alternate skinning. @Note - The function will set the context of the pipeline. @Param ContextParams - Give all the context information to the pipeline for the current import.
- L373 _public prototype_ `virtual void AdjustSettingsFromCache();`
- L376 _public prototype_ `void TransferAdjustSettings(const UInterchangePipelineBase* SourcePipeline);` — Transfer the source pipeline adjust settings to this pipeline.
- L378 _public function_ `void SetShowEssentialsMode(bool bShowEssentialsModeValue)`
- L386 _public function_ `void SetFromReimportOrOverride(bool bInFromReimportOrOverride)` — Set to true if this pipeline is from a re-import or an override pipelines stack
- L394 _public function_ `bool IsFromReimportOrOverride() const` — Return true if the pipeline was created for a re-import or an override pipelines stack
- L402 _public function_ `virtual void PreDialogCleanup(const FName PipelineStackName)` — This function is called before showing the import dialog. It is not called when doing a reimport.
- L408 _public function_ `virtual bool IsSettingsAreValid(TOptional<FText>& OutInvalidReason) const` — This function should return true if all the pipeline settings are in a valid state to start the import. The Interchange Pipeline Configuration Dialog will call this to know if the Import button can be enabled.
- L418 _public function_ `virtual void FilterPropertiesFromTranslatedData(UInterchangeBaseNodeContainer* InBaseNodeContainer)` — Filter the pipeline properties from the translated data. This function is called by the import dialog after having duplicated and loaded the settings of the pipeline. If some specific options change, the UI must refresh the filter. See the IsPropertyChangeNeedRefresh function.
- L427 _public function_ `virtual bool IsPropertyChangeNeedRefresh(const FPropertyChangedEvent& PropertyChangedEvent) const` — The import dialog will call this function when the user changes a specific property. Return true if the pipeline UI should be refreshed. A refresh will call the FilterPropertiesFromTranslatedData function.
- L434 _public function_ `virtual void GetSupportAssetClasses(TArray<UClass*>& PipelineSupportAssetClasses) const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline")` — Fill the list of all asset this pipeline can create
- L445 _public function_ `virtual TArray<FInterchangeConflictInfo> GetConflictInfos(UObject* ReimportObject, UInterchangeBaseNodeContainer* InBaseNodeContainer, UInterchangeSourceData* SourceData)` — Return all conflict the pipeline find in the translated data. This function is call by the import dialog. If some specific options change, the UI must refresh the conflicts, see function IsPropertyChangeNeedRefresh.
- L452 _public function_ `virtual void ShowConflictDialog(const FGuid& ConflictUniqueId)`
- L461 _public function_ `template <typename T> T* AddMessage() const` — This function is used to add the given message object directly into the results for this operation.
- L468 _public function_ `void AddMessage(UInterchangeResult* Item) const`
- L474 _public function_ `void SetResultsContainer(UInterchangeResultsContainer* InResults)`
- L482 _public prototype_ `const FInterchangePipelinePropertyStates* GetPropertyStates(const FName PropertyPath) const;` — Return a const property states pointer. Return nullptr if the property does not exist.
- L487 _public prototype_ `FInterchangePipelinePropertyStates* GetMutablePropertyStates(const FName PropertyPath);` — Return a mutable property states pointer. Return nullptr if the property does not exist.
- L493 _public prototype_ `bool DoesPropertyStatesExist(const FName PropertyPath) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline")` — Return true if the property has valid states, or false if no states were set for the property.
- L499 _public prototype_ `FInterchangePipelinePropertyStates& FindOrAddPropertyStates(const FName PropertyPath);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline")` — Return a mutable property states reference. Add the property states if it doesn't exist.
- L504 _public prototype_ `static FName GetPropertiesStatesPropertyName();` — Return the property name of the properties states map.
- L506 _public prototype_ `static FName GetResultsPropertyName();`
- L508 _public function_ `bool CanEditPropertiesStates()`
- L511 _public function_ `bool IsReimportContext()` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline")`
- L513 _public function_ `bool IsShowEssentials()`
- L521 _public function_ `virtual bool GetPropertyPossibleValues(const FName PropertyPath, TArray<FString>& PossibleValues)` — FName or FString properties can have a dynamic set of possible values. When displaying a pipeline property in the property editor, this function will be call for all FString and FName properties and will generate a combo box with the PossibleValues if the function return true.
- L533 _public function_ `bool IsStandAlonePipeline() const` — Return true if the pipeline is not a sub-pipeline. Standalone pipelines can have some extra properties. The customize detail of the pipeline will call this function to show or hide those properties. The pipeline itself can call the function to know whether a property must be used. Example: the override asset name property.
- L542 _public prototype_ `void UpdateWeakObjectPtrs();` — Update/reset the TWeakObjectPtrs to point to their original TObjectPtr. Works based on Variable naming.
- L545 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;` — Begin UObject overrides
- L546 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L555 _public function_ `virtual bool SupportReimport() const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Pipeline")` — If this returns true, this pipeline will be saved in the asset import data. We will reuse this pipeline when reimporting the asset. If false, it's probably a debug helper pipeline that we do not want to save into assets.
- L562 _public member_ `FString DestinationName;` — `UPROPERTY()` — The Unreal import system has an option to force a name if we import only one main asset (one texture, one mesh or one animation). The generic asset pipeline uses this information to behave as expected.
- L568 _public member_ `FString ContentImportPath;` — `UPROPERTY()` — The content path where asset should be created.
- L576 _public member_ `FSoftObjectPath OriginalPipelinePath;` — `UPROPERTY()` — Path of the pipeline object used to create an instance of the pipeline. Useful for creating section names for caching the properties in ini file.
- L579 _public prototype_ `UInterchangePipelineBase* GetMostPipelineOuter() const;`
- L582 _public function_ `virtual bool CanAddPropertyToAnalytics(FProperty* Property) const` — `UE_DEPRECATED(5.8, "Use the version with PropertyValueIterator instead.")`
- L587 _public prototype_ `virtual bool CanAddPropertyToAnalytics(TPropertyValueIterator<FProperty>& PropertyValueIterator) const;`
- L590 _public function_ `virtual void AddPropertyAnalytics(FProperty* Property, TArray<FAnalyticsEventAttribute>& PipelineAttributes)` — `UE_DEPRECATED(5.8, "Use the version with PropertyValueIterator instead.")`
- L594 _public prototype_ `virtual void AddPropertyAnalytics(TPropertyValueIterator<FProperty>& PropertyValueIterator, TArray<FAnalyticsEventAttribute>& PipelineAttributes);`
- L599 _protected prototype_ `virtual FString GetCategoryNameForAnalytics(const TArray<const FProperty*>& PropertyChain) const;`
- L601 _protected prototype_ `virtual FString GetPipelineDisplayName() const;`
- L603 _protected function_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath)`
- L612 _protected function_ `virtual void ExecutePostFactoryPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport)` — This function is called after the factory creates an asset, but before PostEditChange is called. It is always called on the game thread. Code inside this function should not wait on other threads. Do not stall the game thread. This is the place to make any changes to the Unreal asset before PostEditChange is called.
- L620 _protected function_ `virtual void ExecutePostImportPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport)` — This function is called after the Unreal asset is completely imported and PostEditChange was called. @Note: Some Unreal assets have asynchronous build operations. It's possible they are still compiling.
- L628 _protected function_ `virtual void ExecutePostBroadcastPipeline(const UInterchangeBaseNodeContainer* BaseNodeContainer, const FString& NodeKey, UObject* CreatedAsset, bool bIsAReimport)` — This function is called after the Unreal asset is completely imported. PostEditChange and all broadcast have been called. @Note: Some Unreal assets have asynchronous build operations. It's possible they are still compiling.
- L632 _protected function_ `virtual void SetReimportSourceIndex(UClass* ReimportObjectClass, const int32 SourceFileIndex)`
- L637 _protected function_ `virtual void ExecuteExportPipeline(UInterchangeBaseNodeContainer* BaseNodeContainer)` — This function can modify the BaseNodeContainer to create a pipeline that will set/validate the graph nodes hierarchy and options.
- L641 _protected prototype_ `void LoadSettingsInternal(const FName PipelineStackName, const FString& ConfigFilename, TMap<FName, FInterchangePipelinePropertyStates>& ParentPropertiesStates, bool bResetPreDialog, bool& bOutRequiresSaving);`
- L643 _protected prototype_ `void SaveSettingsInternal(const FName PipelineStackName, const FString& ConfigFilename);`
- L646 _protected prototype_ `static void InternalToggleVisibilityPropertiesOfMetaDataValue(UInterchangePipelineBase* OuterMostPipeline, UInterchangePipelineBase* Pipeline, bool bDoTransientSubPipeline, const FString& MetaDataKey, const FString& MetaDataValue, const bool bVisibilityState);`
- L647 _protected prototype_ `static void HidePropertiesOfCategory(UInterchangePipelineBase* OuterMostPipeline, UInterchangePipelineBase* Pipeline, const FString& HideCategoryName, bool bDoTransientSubPipeline = false);`
- L648 _protected prototype_ `static void HidePropertiesOfSubCategory(UInterchangePipelineBase* OuterMostPipeline, UInterchangePipelineBase* Pipeline, const FString& HideSubCategoryName, bool bDoTransientSubPipeline = false);`
- L649 _protected prototype_ `static void HideProperty(UInterchangePipelineBase* OuterMostPipeline, UInterchangePipelineBase* Pipeline, const FName& HidePropertyName);`
- L660 _protected member_ `bool bAllowPropertyStatesEdition = true;` — `UPROPERTY(Transient)` — If true, the property editor for this pipeline instance will allow editing property states. If false, the property editor for this pipeline instance will apply the property states. Note: If you open a pipeline asset in the Content Browser, you will be able to edit the property states. If you import a file with Interchange, the import dialog will apply property states.
- L669 _protected member_ `bool bIsReimportContext = false;` — `UPROPERTY(Transient)` — If true, this pipeline instance is used for reimport. If false, this pipeline instance is used for import. Note: This context must be set by the owner instancing this pipeline. This context will be used to determine whether to hide some properties.
- L678 _protected member_ `bool bIsShowEssentials = false;` — `UPROPERTY(Transient)` — If true, this pipeline instance is use for essentials settings layout. If false, this pipeline instance is use for normal layout. Note: This layout must be set by the owner instancing this pipeline. This layout will be use to hide or not some properties.
- L685 _protected member_ `bool bFromReimportOrOverride = false;` — `UPROPERTY()` — If true, this pipeline was create to re-import an asset or override the project settings pipelines. That kind of pipeline will not be treat like project settings pipeline in the UI. PredialogCleanup will not be called.
- L688 _protected member_ `TObjectPtr<UInterchangeResultsContainer> Results;` — `UPROPERTY()`
- L695 _protected member_ `TMap<FName, FInterchangePipelinePropertyStates> PropertiesStates;` — `UPROPERTY()` — Map of property path and lock status. Any properties that have a true lock status will be readonly when showing the import dialog. Use the API to Get and Set the properties states.
- L698 _protected member_ `mutable TMap<FName, FInterchangePipelinePropertyStates> CachePropertiesStates;` — `UPROPERTY(Transient)`
- L701 _protected member_ `mutable FInterchangePipelineContextParams CacheContextParam;` — `UPROPERTY(Transient)`
- L703 _protected member_ `TArray<FInterchangeConflictInfo> ConflictInfos;`

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API INTERCHANGECORE_API`

### `Source/Runtime/Interchange/Core/Public/InterchangeResult.h` (Public)


#### enum `EInterchangeResultType`  
`enum class EInterchangeResultType`  
_L20-25_
- reflection: `UENUM()`
- L22 _public enumerator_ `Success`
- L23 _public enumerator_ `Warning`
- L24 _public enumerator_ `Error`

#### class `UInterchangeResult`  
`class UInterchangeResult : public UObject`  
_L32-78_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UObject`
- desc: Base class for the result from an Interchange operation.
- L41 _public function_ `virtual EInterchangeResultType GetResultType() const` — Return the severity of the message: success, warning, error.
- L46 _public function_ `virtual FText GetText() const` — Return a user-readable message.
- L51 _public prototype_ `FText GetMessageLogText() const;` — Return a message to be displayed in the MessageLog window.
- L56 _public prototype_ `FString ToJson();` — Serialize this UInterchangeResult object to Json.
- L61 _public prototype_ `static UInterchangeResult* FromJson(const FString& JsonString);` — Create a new UInterchangeResult-derived object from a Json representation.
- L65 _public member_ `FString SourceAssetName;` — `UPROPERTY()`
- L68 _public member_ `FString DestinationAssetName;` — `UPROPERTY()`
- L71 _public member_ `FString AssetFriendlyName;` — `UPROPERTY()`
- L74 _public member_ `TObjectPtr<const UClass> AssetType;` — `UPROPERTY()`
- L77 _public member_ `FString InterchangeKey;` — `UPROPERTY()`

#### class `UInterchangeResultSuccess`  
`class UInterchangeResultSuccess : public UInterchangeResult`  
_L85-93_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResult`
- desc: Class representing a succesful result.
- L91 _public function_ `virtual EInterchangeResultType GetResultType() const override`
- L92 _public function_ `virtual FText GetText() const override`

#### class `UInterchangeResultWarning`  
`class UInterchangeResultWarning : public UInterchangeResult`  
_L100-107_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResult`
- desc: Base class representing a warning result.
- L106 _public function_ `virtual EInterchangeResultType GetResultType() const override`

#### class `UInterchangeResultError`  
`class UInterchangeResultError : public UInterchangeResult`  
_L114-121_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResult`
- desc: Base class representing a error result.
- L120 _public function_ `virtual EInterchangeResultType GetResultType() const override`

#### class `UInterchangeResultWarning_Generic`  
`class UInterchangeResultWarning_Generic : public UInterchangeResultWarning`  
_L125-135_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResultWarning`
- L131 _public function_ `virtual FText GetText() const override`
- L134 _public member_ `FText Text;` — `UPROPERTY()`

#### class `UInterchangeResultError_Generic`  
`class UInterchangeResultError_Generic : public UInterchangeResultError`  
_L139-149_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResultError`
- L145 _public function_ `virtual FText GetText() const override`
- L148 _public member_ `FText Text;` — `UPROPERTY()`

#### class `UInterchangeResultError_ReimportFail`  
`class UInterchangeResultError_ReimportFail : public UInterchangeResultError`  
_L152-159_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResultError`
- L158 _public function_ `virtual FText GetText() const override`

#### class `UInterchangeResultDisplay_Generic`  
`class UInterchangeResultDisplay_Generic : public UInterchangeResultSuccess`  
_L165-175_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangeResultSuccess`
- desc: Used for Successful imports with messages with lower than Warning priorities (for ep Display)
- L171 _public function_ `virtual FText GetText() const override`
- L174 _public member_ `FText Text;` — `UPROPERTY()`

### `Source/Runtime/Interchange/Core/Public/InterchangeResultsContainer.h` (Public)


#### class `UInterchangeResultsContainer`  
`class UInterchangeResultsContainer : public UObject`  
_L20-95_
- reflection: `UCLASS(Experimental, MinimalAPI)`
- inherits: `UObject`
- L29 _public function_ `bool IsEmpty() const` — Returns whether the results container is empty or not
- L38 _public prototype_ `void Empty();` — Empties the results container
- L43 _public prototype_ `void Append(UInterchangeResultsContainer* Other);` — Appends the given results container to this one
- L49 _public function_ `template <typename T> T* Add()` — Creates a UInterchangeResult of the given type, adds it to the container and returns it.
- L60 _public function_ `void Add(UInterchangeResult* Item)` — Adds the given UInterchangeResult to the container.
- L69 _public prototype_ `void Finalize();` — Finalizes the container, prior to passing it to the UI display
- L74 _public function_ `TArray<UInterchangeResult*> GetResults() const` — Return the contained array (by value, for thread safety).
- L83 _public function_ `void RemoveResult(UInterchangeResult* Item)` — Removes the given UInterchangeResult from the container.
- L91 _private member_ `mutable FCriticalSection Lock;`
- L94 _private member_ `TArray<TObjectPtr<UInterchangeResult>> Results;` — `UPROPERTY()`

### `Source/Runtime/Interchange/Core/Public/InterchangeSourceData.h` (Public)


#### class `UInterchangeSourceData`  
`class UInterchangeSourceData : public UObject`  
_L22-112_
- reflection: `UCLASS(BlueprintType, Blueprintable, MinimalAPI)`
- inherits: `UObject`
- L27 _public prototype_ `UInterchangeSourceData();`
- L29 _public prototype_ `UInterchangeSourceData(FString InFilename);`
- L32 _public function_ `inline FString GetFilename() const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")`
- L38 _public function_ `inline TOptional<FMD5Hash> GetFileContentHash() const` — Return the hash of the content point by Filename.
- L49 _public function_ `inline bool SetFilename(const FString& InFilename)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")`
- L58 _public function_ `inline FString ToDisplayString() const` — Return a easy to read source description string, this is mainly use for logging or UI.
- L79 _public prototype_ `UObject* GetContextObjectByTag(const FString& Tag) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")`
- L82 _public prototype_ `void SetContextObjectByTag(const FString& Tag, UObject* Object) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")`
- L85 _public prototype_ `TArray<FString> GetAllContextObjectTags() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")`
- L88 _public prototype_ `void RemoveAllContextObjects() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Import Manager")`
- L91 _private prototype_ `void ComputeFileContentHashCache() const;`
- L94 _private member_ `FString Filename;` — `UPROPERTY()`
- L102 _private member_ `mutable TOptional<FMD5Hash> FileContentHashCache;` — Hash cache for the file content. We use mutable because the cache is computed when we use the get, which is a const function. The cache is computed only in the GetFileContentHash() to let the client control in which thread it will compute the cache. It also makes sure we do not waste CPU computing a cache in case no client uses GetFileContentHash().
- L111 _private member_ `mutable TMap<FString, TObjectPtr<UObject>> ContextObjectsByTag;` — `UPROPERTY()` — UObjects that are accessible by the translators, pipelines, and the caller of the Interchange import. Use this to transmit additional information that is beneficial to reuse but can't be serialized, such as external SDK memory objects, external assets, or large cached data.

### `Source/Runtime/Interchange/Core/Public/InterchangeTaskSystem.h` (Public)


#### enum `UE::Interchange::EInterchangeTaskStatus`  
`enum class EInterchangeTaskStatus : uint8`  
_L21-26_
- L23 _public enumerator_ `Waiting` — Task is queue for execution when prerequisite are terminate and resource are available
- L24 _public enumerator_ `Executing` — Task is being executing
- L25 _public enumerator_ `Done` — Task was execute and is now terminate

#### enum `UE::Interchange::EInterchangeTaskThread`  
`enum class EInterchangeTaskThread : uint8`  
_L28-32_
- L30 _public enumerator_ `GameThread` — Task will be tick in a ticker in the engine tick on the game thread. This is a safe place to manipulate UObject
- L31 _public enumerator_ `AsyncThread` — Task will be call on asynchronous thread, code running inside those task must be thread safe.

#### class `UE::Interchange::FInterchangeTaskBase`  
`class FInterchangeTaskBase`  
_L34-116_
- L37 _public function_ `FInterchangeTaskBase()`
- L40 _public function_ `virtual ~FInterchangeTaskBase()`
- L51 _public function_ `uint64 GetTaskId() const`
- L56 _public function_ `virtual EInterchangeTaskThread GetTaskThread() const`
- L61 _public function_ `const TArray<uint64>& GetPrerequisiteTasks() const`
- L66 _public function_ `EInterchangeTaskStatus GetTaskStatus() const`
- L79 _public prototype_ `virtual void Execute() = 0;` — This function must return the task id to fill the promise of the execution. If the caller want to re-enqueue the task and not run the subsequent tasks after this function, It must set the task status to Waiting and the task will be re-execute later on another tick. This is the best way to implement a async wait.
- L96 _public prototype_ `void Wait() const;` — Wait can be call only on game thread. Async thread wait can create dead lock by using all the thread resources. The caller have some restriction to follow - This must be a safe place for any game thread task that will be executing during the wait. - Wait should be call from a engine tick and no lock (like the global UObject locks) should be taken before calling wait. - Slate ui callback are safe - Engine tick is safe, use FTSTicker::GetCoreTicker() when you can - Wait should not happen from a package/asset load call stack - Wait should not happen from a save package/asset call stack - Wait should not happen from a garbage collect call stack If your system need to wait and you already have some locks or you are under a unsafe place you need to redesign your system to move the wait before you get to a unsafe call stack place to wait.
- L100 _protected prototype_ `bool SetTaskStatus(EInterchangeTaskStatus NewTaskStatus);` — Only friend FInterchangeTaskSystem can set a new status
- L102 _protected prototype_ `void SetPrerequisites(const TArray<uint64>& InPrerequisiteTasks);`
- L106 _private member_ `mutable FCriticalSection TaskStatusCriticalSection;`
- L107 _private member_ `uint64 TaskId = INTERCHANGE_INVALID_TASK_ID;`
- L108 _private member_ `EInterchangeTaskStatus TaskStatus = EInterchangeTaskStatus::Waiting;`
- L109 _private member_ `TArray<uint64> PrerequisiteTasks;`
- L113 _private member_ `TFuture<uint64> Future;` — If a task is asynchronous the future will be set. The future will contain the task id when it will be ready.

#### class `UE::Interchange::FInterchangeTaskLambda`  
`class FInterchangeTaskLambda : public FInterchangeTaskBase`  
_L121-144_
- inherits: `FInterchangeTaskBase`
- desc: This class is use to run a lambda with the interchange task system.
- L124 _private member_ `EInterchangeTaskThread TaskThread = EInterchangeTaskThread::GameThread;`
- L125 _private member_ `TFunction<void()> ExecuteLambda;`
- L129 _public function_ `FInterchangeTaskLambda(EInterchangeTaskThread InTaskThread, TFunction<void()> InExecuteLambda) : TaskThread(InTaskThread) , ExecuteLambda(MoveTemp(InExecuteLambda))`
- L135 _public function_ `virtual EInterchangeTaskThread GetTaskThread() const override`
- L140 _public function_ `virtual void Execute()`

#### class `UE::Interchange::FInterchangeTaskSystem`  
`class FInterchangeTaskSystem`  
_L146-235_
- L153 _public prototype_ `FInterchangeTaskSystem();` — The constructor should not be called directly, an ensure will be set if its the case Use the static Get function to acces the singleton.
- L156 _public prototype_ `static FInterchangeTaskSystem& Get();` — The interchange task system is a singleton
- L163 _public prototype_ `uint64 AddTask(TSharedPtr<FInterchangeTaskBase, ESPMode::ThreadSafe> Task, TArray<uint64>& TaskPrerequisites);` — Add a task with some prerequisites. Return the task id. If there is an issue the returned task id will be INTERCHANGE_INVALID_TASK_ID The task will start when all prerequisites are done and some thread resource will be available.
- L170 _public prototype_ `uint64 AddTask(TSharedPtr<FInterchangeTaskBase, ESPMode::ThreadSafe> Task);` — Add a task without prerequisite. Return the task id. If there is an issue the returned task id will be INTERCHANGE_INVALID_TASK_ID The task will start when some thread resource will be available.
- L173 _public prototype_ `EInterchangeTaskStatus GetTaskStatus(const uint64 TaskId) const;` — Return the current task status
- L179 _public prototype_ `void CancelTask(const uint64 TaskId, const bool bCancelPrerequisites);` — Cancel a task, you can control if you cancel also the prerequisites, and subsequents. Canceling a task that is waiting will simply push it state to Done which will allow subsequent to be executed.
- L196 _public prototype_ `void WaitUntilTasksComplete(const TArray<uint64>& TasksToComplete);` — Wait can be call only on game thread. Async thread wait can create dead lock by using all the thread resources. The caller have some restriction to follow - This must be a safe place for any game thread task that will be executing during the wait. - Wait should be call from a engine tick and no lock (like the global UObject locks) should be taken before calling wait. - Slate ui callback are safe - Engine tick is safe, use FTSTicker::GetCoreTicker() when you can - Wait should not happen from a package/asset load call stack - Wait should not happen from a save package/asset call stack - Wait should not happen from a garbage collect call stack If your system need to wait and you already have some locks or you are under a unsafe place you need to redesign your system to move the wait before you get to a unsafe call stack place to wait.
- L198 _public function_ `FOnInterchangeTaskSystemTick& OnTaskSystemTickDelegate()`
- L205 _private member_ `static bool bIsCreatingSingleton;`
- L207 _private member_ `FOnInterchangeTaskSystemTick OnTaskSystemTick;`
- L210 _private prototype_ `void InternalAddCancelRequestNoLock(const uint64 TaskId, bool bCancelPrerequisites);` — Internal cancel request with no lock, lock is handle by the caller (CancelTask)
- L215 _private prototype_ `void Tick();` — The tick is where we start task execution and where we update the tasks status
- L218 _private member_ `FTSTicker::FDelegateHandle TickTickerHandle;` — The ticker we use to tick in the engine tick
- L221 _private member_ `TMap<uint64, TSharedPtr<FInterchangeTaskBase, ESPMode::ThreadSafe>> TaskPerIdMap;` — Store the tasks per id
- L222 _private member_ `mutable FCriticalSection TaskPerIdMapCriticalSection;`
- L226 _private member_ `TSet<uint64> ReleaseAndDoneTasks;` — When a task is done, we add it here and release the task. Prerequisite are search in the list and here. A clean up is done when the TaskPerIdMap is empty.
- L230 _private member_ `uint64 PriorityValue = 0;` — The priority value is a counter that is increment for each task added to the system to create the task id The lower task id are execute earlier if possible.
- L231 _private member_ `FCriticalSection PriorityValueCriticalSection;`
- L233 _private member_ `TArray<uint64> CancelTaskRequests;`
- L234 _private member_ `FCriticalSection CancelTaskRequestsCriticalSection;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define INTERCHANGE_INVALID_TASK_ID 0xFFFFFFFFFFFFFFFF`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnInterchangeTaskSystemTick) namespace UE::Interchange {`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Interchange` (scope `UE`)

### `Source/Runtime/Interchange/Core/Public/InterchangeTranslatorBase.h` (Public)


#### class `UInterchangeTranslatorSettings`  
`class UInterchangeTranslatorSettings : public UObject`  
_L28-38_
- reflection: `UCLASS(BlueprintType, Blueprintable, editinlinenew, Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Base class for translator settings, the UInterchangeAssetImportData will store this data if the source translator exist
- L34 _public prototype_ `void LoadSettings();` — `UFUNCTION(BlueprintCallable, Category = "Interchange")`
- L37 _public prototype_ `void SaveSettings();` — `UFUNCTION(BlueprintCallable, Category = "Interchange")`

#### enum `EInterchangeTranslatorType`  
`enum class EInterchangeTranslatorType : uint8`  
_L41-47_
- reflection: `UENUM(BlueprintType)`
- L43 _public enumerator_ `Invalid = 0`
- L44 _public enumerator_ `Assets = 1 << 1`
- L45 _public enumerator_ `Actors = 1 << 2`
- L46 _public enumerator_ `Scenes = Assets | Actors`

#### enum `EInterchangeTranslatorAssetType`  
`enum class EInterchangeTranslatorAssetType : uint8`  
_L50-59_
- reflection: `UENUM(BlueprintType)`
- L52 _public enumerator_ `None = 0x0`
- L53 _public enumerator_ `Textures = 0x1 << 0`
- L54 _public enumerator_ `Materials = 0x1 << 1`
- L55 _public enumerator_ `Meshes = 0x1 << 2`
- L56 _public enumerator_ `Animations = 0x1 << 3`
- L57 _public enumerator_ `Sounds = 0x1 << 4`
- L58 _public enumerator_ `Grooms = 0x1 << 5`

#### class `UInterchangeTranslatorBase`  
`class UInterchangeTranslatorBase : public UObject`  
_L63-180_
- reflection: `UCLASS(BlueprintType, Blueprintable, Abstract, MinimalAPI)`
- inherits: `UObject`
- L70 _public prototype_ `virtual bool CanImportSourceData(const UInterchangeSourceData* InSourceData) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Translator")` — return true if the translator can translate the given source data.
- L77 _public function_ `virtual bool IsThreadSafe() const` — Return true if the translator can be instantiate more then one time. Some translator are not thread safe and cannot translate two files in same time. A non thread safe translator could use the InterchangeWorker program to run in a separate process and return true.
- L81 _public function_ `virtual EInterchangeTranslatorType GetTranslatorType() const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Translator")` — Specifies the capabilities of a translator.
- L83 _public function_ `bool DoesSupportAssetType(EInterchangeTranslatorAssetType AssetType) const`
- L86 _public prototype_ `virtual EInterchangeTranslatorAssetType GetSupportedAssetTypes() const PURE_VIRTUAL(UInterchangeTranslatorBase::GetSupportedAssetTypes, return EInterchangeTranslatorAssetType::None;);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Translator")`
- L90 _public prototype_ `virtual TArray<FString> GetSupportedFormats() const PURE_VIRTUAL(UInterchangeTranslatorBase::GetSupportedExtensions, return TArray<FString>(););` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Translator")` — List of formats supported by the translator. Each entry is of the form "ext;Description" where ext is the file extension.
- L98 _public function_ `virtual bool Translate(UInterchangeBaseNodeContainer& BaseNodeContainer) const` — Translate the associated source data into node(s) that are hold in the specified nodes container. @param BaseNodeContainer - The nodes container where to put the translated source data result. @return true if the translator can translate the source data, false otherwise.
- L109 _public function_ `virtual void ReleaseSource()` — Release source is called when we do not need anymore the translator source and also early in the cancel process. This is where out of process translator will send the stop command. A good example of why its useful to release the source is when the dispatcher delete the worker, the join on the thread will be very short and will not block the main thread. If the worker stop command was send before the completion task.
- L118 _public function_ `virtual void ImportFinish()` — This function is call when the import is done (FImportAsyncHelper::CleanUp) and we are cleaning the data. Use it to free resource that need to be release before the next garbage collector pass.
- L127 _public function_ `template <typename T> T* AddMessage() const` — This function is used to add the given message object directly into the results for this operation.
- L138 _public function_ `void AddMessage(UInterchangeResult* Item) const`
- L147 _public function_ `void SetResultsContainer(UInterchangeResultsContainer* InResults)`
- L156 _public function_ `const UInterchangeSourceData* GetSourceData() const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Translator")` — Get the associated source data for this translator.
- L165 _public function_ `virtual UInterchangeTranslatorSettings* GetSettings() const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Translator")` — Return this translator settings
- L171 _public function_ `virtual void SetSettings(const UInterchangeTranslatorSettings* InterchangeTranslatorSettings)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Translator")` — Reimport will set the settings if they exist in UInterchangeAssetImportData
- L174 _public member_ `TObjectPtr<UInterchangeResultsContainer> Results;` — `UPROPERTY()`
- L177 _public member_ `TObjectPtr<const UInterchangeSourceData> SourceData;` — `UPROPERTY()`
- L179 _public member_ `TObjectPtr<UInterchangeAnalyticsHandlerBase> AnalyticsHandler = nullptr;`

#### Free symbols / members of external scopes

- L60 _prototype_ `ENUM_CLASS_FLAGS(EInterchangeTranslatorAssetType);`

### `Source/Runtime/Interchange/Core/Public/InterchangeWriterBase.h` (Public)


#### class `UInterchangeWriterBase`  
`class UInterchangeWriterBase : public UObject`  
_L13-24_
- reflection: `UCLASS(BlueprintType, Blueprintable, Abstract, Experimental, MinimalAPI)`
- inherits: `UObject`
- L23 _public function_ `virtual bool Export(UInterchangeBaseNodeContainer* BaseNodeContainer) const` — Export an nodes container (graph) @param BaseNodeContainer - The container holding nodes that describe what to export @return true if the writer can export the Nodes, false otherwise.

### `Source/Runtime/Interchange/Core/Public/Nodes/InterchangeBaseNode.h` (Public)


#### struct `UE::Interchange::FBaseNodeStaticData`  
`struct FBaseNodeStaticData`  
_L156-168_
- desc: Helper struct used to declare static const data we use in the UInterchangeBaseNode. Nodes that derive from UInterchangeBaseNode can also add a struct that derives from this one to add static data. @note: The static data are mainly for holding Attribute keys. All attributes that are always available for a node should be in this class or a derived class.
- L158 _public prototype_ `static const FAttributeKey& UniqueIDKey();`
- L159 _public prototype_ `static const FAttributeKey& DisplayLabelKey();`
- L160 _public prototype_ `static const FAttributeKey& NamespaceKey();`
- L161 _public prototype_ `static const FAttributeKey& ParentIDKey();`
- L162 _public prototype_ `static const FAttributeKey& DesiredChildIndexKey();`
- L163 _public prototype_ `static const FAttributeKey& IsEnabledKey();`
- L164 _public prototype_ `static const FAttributeKey& TargetAssetIDsKey();`
- L165 _public prototype_ `static const FAttributeKey& ClassTypeAttributeKey();`
- L166 _public prototype_ `static const FAttributeKey& AssetNameKey();`
- L167 _public prototype_ `static const FAttributeKey& NodeContainerTypeKey();`

#### enum `EInterchangeNodeContainerType`  
`enum class EInterchangeNodeContainerType : uint8`  
_L173-179_
- reflection: `UENUM(BlueprintType)`
- L175 _public enumerator_ `None`
- L176 _public enumerator_ `TranslatedScene`
- L177 _public enumerator_ `TranslatedAsset`
- L178 _public enumerator_ `FactoryData`

#### enum `EInterchangeNodeUserInterfaceContext`  
`enum class EInterchangeNodeUserInterfaceContext : uint8`  
_L182-186_
- reflection: `UENUM(BlueprintType)`
- L184 _public enumerator_ `None`
- L185 _public enumerator_ `Preview` — When we want to preview the node data. A preview is normally read-only and should not show internal data.

#### class `UInterchangeBaseNode`  
`class UInterchangeBaseNode : public UObject`  
_L194-593_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: This struct is used to store and retrieve key-value attributes. The attributes are stored in a generic FAttributeStorage that serializes the values in a TArray64<uint8>. See UE::Interchange::EAttributeTypes to know the supported template types. This is an abstract class. This is the base class of the interchange node graph format; all classes in this format should derive from this class.
- L199 _public member_ `static constexpr const TCHAR* HierarchySeparator = TEXT("\\"`
- L201 _public prototype_ `UInterchangeBaseNode();`
- L211 _public prototype_ `void InitializeNode(const FString& UniqueID, const FString& DisplayLabel, const EInterchangeNodeContainerType NodeContainerType);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Initialize the base data of the node. @param UniqueID - The unique ID for this node. @param DisplayLabel - The name of the node. If the Node to initialize also will get a Parent, then the UInterchangeBaseNodeContainer's SetupNode is better suited.
- L217 _public prototype_ `virtual FString GetTypeName() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Return the node type name of the class. This is used when reporting errors.
- L223 _public prototype_ `virtual FName GetIconName() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Icon name, used to retrieve the brush when we display the node in any UI.
- L229 _public prototype_ `virtual FString GetKeyDisplayName(const UE::Interchange::FAttributeKey& NodeAttributeKey) const;` — UI that inspects node attributes calls this to give a readable name to an attribute key.
- L234 _public prototype_ `virtual bool ShouldHideAttribute(const UE::Interchange::FAttributeKey& NodeAttributeKey) const;` — UI that inspects node attributes calls this to display or hide an attribute.
- L239 _public prototype_ `virtual FString GetAttributeCategory(const UE::Interchange::FAttributeKey& NodeAttributeKey) const;` — UI that inspects node attributes calls this to display the attribute under the returned category.
- L248 _public member_ `EInterchangeNodeUserInterfaceContext UserInterfaceContext = EInterchangeNodeUserInterfaceContext::None;` — `UPROPERTY(Transient, DuplicateTransient)` — Temporary property set by UI to have the context for ShouldHideAttribute. We use this because the property editor cannot add this custom context when it calls CustomizeDetails.
- L258 _public function_ `template<typename T> UE::Interchange::FAttributeStorage::TAttributeHandle<T> RegisterAttribute(const UE::Interchange::FAttributeKey& NodeAttributeKey, const T& Value)` — Add an attribute to the node. @param NodeAttributeKey - The key of the attribute. @param Value - The attribute value.
- L275 _public prototype_ `virtual bool HasAttribute(const UE::Interchange::FAttributeKey& NodeAttributeKey) const;` — Return true if the node contains an attribute with the specified Key. @param nodeAttributeKey - The key of the searched attribute.
- L282 _public prototype_ `virtual UE::Interchange::EAttributeTypes GetAttributeType(const UE::Interchange::FAttributeKey& NodeAttributeKey) const;` — This function returns an attribute type for the specified Key. Returns type None if the key is invalid. @param NodeAttributeKey - The key of the attribute.
- L291 _public function_ `template<typename T> UE::Interchange::FAttributeStorage::TAttributeHandle<T> GetAttributeHandle(const UE::Interchange::FAttributeKey& NodeAttributeKey) const` — This function returns an attribute handle for the specified Key. If there is an issue with the KEY or storage, the method will trip a check. Always make sure you have a valid key before calling this. @param NodeAttributeKey - The key of the attribute.
- L299 _public prototype_ `void GetAttributeKeys(TArray<UE::Interchange::FAttributeKey>& AttributeKeys) const;` — Query all the node attribute keys.
- L305 _public prototype_ `bool RemoveAttribute(const FString& NodeAttributeKey);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Remove the specified attribute from this node. Returns false if it could not be removed. If the attribute does not exist, returns true.
- L311 _public prototype_ `bool AddBooleanAttribute(const FString& NodeAttributeKey, const bool& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Add a Boolean attribute to this node. Returns false if the attribute does not exist or if it cannot be added.
- L317 _public prototype_ `bool GetBooleanAttribute(const FString& NodeAttributeKey, bool& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Get a Boolean attribute from this node. Returns false if the attribute does not exist.
- L323 _public prototype_ `bool AddInt32Attribute(const FString& NodeAttributeKey, const int32& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Add a int32 attribute to this node. Returns false if the attribute does not exist or if it cannot be added.
- L329 _public prototype_ `bool GetInt32Attribute(const FString& NodeAttributeKey, int32& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Get a int32 attribute from this node. Returns false if the attribute does not exist.
- L335 _public prototype_ `bool AddFloatAttribute(const FString& NodeAttributeKey, const float& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Add a float attribute to this node. Returns false if the attribute does not exist or if it cannot be added.
- L341 _public prototype_ `bool GetFloatAttribute(const FString& NodeAttributeKey, float& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Get a float attribute from this node. Returns false if the attribute does not exist.
- L347 _public prototype_ `bool AddDoubleAttribute(const FString& NodeAttributeKey, const double& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Add a double attribute to this node. Returns false if the attribute does not exist or if it cannot be added.
- L353 _public prototype_ `bool GetDoubleAttribute(const FString& NodeAttributeKey, double& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Get a double attribute from this node. Returns false if the attribute does not exist.
- L359 _public prototype_ `bool AddStringAttribute(const FString& NodeAttributeKey, const FString& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Add a string attribute to this node. Returns false if the attribute does not exist or if it cannot be added.
- L365 _public prototype_ `bool GetStringAttribute(const FString& NodeAttributeKey, FString& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Get a string attribute from this node. Returns false if the attribute does not exist.
- L371 _public prototype_ `bool AddGuidAttribute(const FString& NodeAttributeKey, const FGuid& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Add a GUID attribute to this node. Returns false if the attribute does not exist or if it cannot be added.
- L377 _public prototype_ `bool GetGuidAttribute(const FString& NodeAttributeKey, FGuid& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Get a GUID attribute from this node. Returns false if the attribute does not exist.
- L383 _public prototype_ `bool AddLinearColorAttribute(const FString& NodeAttributeKey, const FLinearColor& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Add an FLinearColor attribute to this node. Returns false if the attribute does not exist or if it cannot be added.
- L389 _public prototype_ `bool GetLinearColorAttribute(const FString& NodeAttributeKey, FLinearColor& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Get an FLinearColor attribute from this node. Returns false if the attribute does not exist.
- L395 _public prototype_ `bool AddVector2Attribute(const FString& NodeAttributeKey, const FVector2f& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Add a Vector2 attribute to this node. Returns false if the attribute does not exist or if it cannot be added.
- L401 _public prototype_ `bool GetVector2Attribute(const FString& NodeAttributeKey, FVector2f& OutValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Get a Vector2 attribute from this node. Returns false if the attribute does not exist.
- L404 _public function_ `template<typename AttributeType> AttributeType GetAttributeChecked(const FString& NodeAttributeKey) const`
- L415 _public function_ `template<typename AttributeType> bool GetAttribute(const FString& NodeAttributeKey, AttributeType& OutValue) const`
- L420 _public function_ `template<typename AttributeType> bool SetAttribute(const FString& NodeAttributeKey, const AttributeType& Value)`
- L429 _public prototype_ `FString GetUniqueID() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Return the unique ID passed in the constructor.
- L435 _public prototype_ `FString GetDisplayLabel() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Return the display label.
- L442 _public prototype_ `bool SetDisplayLabel(const FString& InDisplayLabel);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Change the display label. @param InDisplayLabel - Desired display label text. Sanitized to "Null" if empty or if equals "None".
- L450 _public prototype_ `bool GetNamespace(FString& Namespace) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Namespace is a prefix added when calling GetUniqueId(). If the attribute exist it will fill Namespace and return true. If the attribute do not exist, it will not touch OutNamespace and return false.
- L459 _public prototype_ `FString GetParentUid() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Return the parent unique ID. If the attribute does not exist, returns InvalidNodeUid(). Use UInterchangeBaseNodeContainer::SetNodeParentUid function to create a parent hierarchy. This will ensure the container cache is always in sync It's suggested to use SetupNode (that will Iintialize, Add to container and setup the Parent hierarchy as well).
- L468 _public prototype_ `int32 GetDesiredChildIndex() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Return the desired child index. If the attribute do not exist it will return INDEX_NONE. The interchange node container will use this to re-order children if attribute are specified. Use UInterchangeBaseNodeContainer::SetNodeDesiredChildIndex function to set this node child index. This will ensure the container cache is always in sync
- L474 _public prototype_ `int32 GetTargetNodeCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Get the number of target assets relating to this object.
- L480 _public prototype_ `void GetTargetNodeUids(TArray<FString>& OutTargetAssets) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Get the target assets relating to this object.
- L486 _public prototype_ `bool AddTargetNodeUid(const FString& AssetUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Add an asset node UID relating to this object.
- L492 _public prototype_ `bool RemoveTargetNodeUid(const FString& AssetUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Remove an asset node UID relating to this object.
- L499 _public prototype_ `bool IsEnabled() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — If true, the node is imported or exported. If false, it is discarded. Returns false if the node was disabled. Returns true if the attribute is not there or if it was enabled.
- L507 _public prototype_ `bool SetEnabled(const bool bIsEnabled);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Determine whether this node should be part of the import or export process. @param bIsEnabled - If true, this node is imported or exported. If false, it is discarded. @return true if the attribute was set, or false otherwise.
- L513 _public prototype_ `EInterchangeNodeContainerType GetNodeContainerType() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Return the node container type that defines the purpose of the node (factory node, translated scene node, or translated asset node).
- L522 _public prototype_ `virtual FGuid GetHash() const;` — Return an FGuid built from the FSHA1 of all the attribute data contained in the node. @note the attribute are sorted by key when building the FSHA1 data. The hash will be deterministic for the same data whatever the order we add the attributes. This function interface is pure virtual.
- L529 _public prototype_ `virtual FString GetAssetName() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Optional. Any node that can import or export an asset should set the desired name for the asset. If the attribute was never set, returns GetDisplayLabel().
- L535 _public prototype_ `virtual bool SetAssetName(const FString& AssetName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Set the name for the imported asset this node represents. The asset factory will call GetAssetName().
- L538 _public prototype_ `static FString InvalidNodeUid();` — Return the invalid unique ID.
- L543 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Serialize the node. By default, only the attribute storage is serialized for a node.
- L545 _public prototype_ `static void CompareNodeStorage(const UInterchangeBaseNode* NodeA, const UInterchangeBaseNode* NodeB, TArray<UE::Interchange::FAttributeKey>& RemovedAttributes, TArray<UE::Interchange::FAttributeKey>& AddedAttributes, TArray<UE::Interchange::FAttributeKey>& ModifiedAttributes);`
- L547 _public prototype_ `static void CopyStorageAttributes(const UInterchangeBaseNode* SourceNode, UInterchangeBaseNode* DestinationNode, const TArray<UE::Interchange::FAttributeKey>& AttributeKeys);`
- L548 _public prototype_ `static void CopyStorageAttributes(const UInterchangeBaseNode* SourceNode, UE::Interchange::FAttributeStorage& DestinationStorage, const TArray<UE::Interchange::FAttributeKey>& AttributeKeys);`
- L549 _public prototype_ `static void CopyStorageAttributes(const UE::Interchange::FAttributeStorage& SourceStorage, UInterchangeBaseNode* DestinationNode, const TArray<UE::Interchange::FAttributeKey>& AttributeKeys);`
- L550 _public prototype_ `static void CopyStorageAttributes(const UInterchangeBaseNode* SourceNode, UE::Interchange::FAttributeStorage& DestinationStorage, const TArray<TPair<UE::Interchange::FAttributeKey, UE::Interchange::FAttributeKey>>& SrcDestAttributeKeys);`
- L552 _public prototype_ `static void CopyStorage(const UInterchangeBaseNode* SourceNode, UInterchangeBaseNode* DestinationNode);`
- L554 _public function_ `virtual void AppendAssetRegistryTags(FAssetRegistryTagsContext Context) const`
- L559 _public function_ `virtual void AppendAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const` — `UE_DEPRECATED(5.4, "Implement the version that takes FAssetRegistryTagsContext instead.")`
- L568 _protected prototype_ `bool SetNamespace(const FString& InNamespace);` — Return true if the Namespace attribute is added, false otherwise.
- L573 _protected prototype_ `bool SetDesiredChildIndex(const int32& ChildIndex);` — Set the desired child index. Only the container should set the desired child index
- L580 _protected prototype_ `bool SetParentUid(const FString& ParentUid);` — Set the parent unique ID. Use UInterchangeBaseNodeContainer::SetNodeParentUid function to create a parent hierarchy. This will ensure the container cache is always in sync It's suggested to use SetupNode (that will Iintialize, Add to container and setup the Parent hierarchy as well).
- L583 _protected member_ `TSharedPtr<UE::Interchange::FAttributeStorage, ESPMode::ThreadSafe> Attributes;` — The storage use to store the Key value attribute for this node.
- L585 _protected member_ `bool bIsInitialized = false;`
- L590 _protected member_ `mutable UE::Interchange::TArrayAttributeHelper<FString> TargetNodes;` — This tracks the IDs of asset nodes which are the target of factories

#### Free symbols / members of external scopes

- L41 _namespace_ `namespace InterchangePrivateNodeBase`
- L55 _function_ `template<typename ValueType> bool GetCustomAttribute(const UE::Interchange::FAttributeStorage& Attributes, const UE::Interchange::FAttributeKey& AttributeKey, const FString& OperationName, ValueType& OutAttributeValue)` (scope `InterchangePrivateNodeBase`) — Retrieve a custom attribute if the attribute exists. @param Attributes - The attribute storage you want to query for the custom attribute. @param AttributeKey - The storage key for the attribute. @param OperationName - The name of the operation, in case there is an error. @param OutAttributeValue - This is where we store the value we retrieve from the storage. @return - returns true if the attribute exists in the storage and was queried without error. returns false if the attribute does not exist or there is an error retrieving it from the storage.
- L84 _function_ `template<typename ValueType> bool SetCustomAttribute(UE::Interchange::FAttributeStorage& Attributes, const UE::Interchange::FAttributeKey& AttributeKey, const FString& OperationName, const ValueType& AttributeValue)` (scope `InterchangePrivateNodeBase`) — Add or update a custom attribute value in the specified storage. @param Attributes - The attribute storage in which you want to add or update the custom attribute. @param AttributeKey - The storage key for the attribute. @param OperationName - The name of the operation, in case there is an error. @param AttributeValue - The value to add or update in the storage.
- L103 _prototype_ `FProperty* FindPropertyByPathChecked(TVariant<UObject*, uint8*>& Container, UStruct* Outer, FStringView PropertyPath);` (scope `InterchangePrivateNodeBase`) — Finds a property by name in Outer and supports looking into FStructProperties (embedded structs) with a '.' separating the property names. @param Container - The container for the property values. If the final property is inside a UScriptStruct, the container will be set to the UScriptStruct instance address. @param Outer - The UStruct containing the top level property. @param PropertyPath - A dot separated chain of properties. Doesn't support going through external objects. @return The Property matching the last name in the PropertyPath.
- L120 _macro_ `#define IMPLEMENT_NODE_ATTRIBUTE_KEY(AttributeName) \` — Use these macros to create Get/Set/ApplyToAsset for an attribute you want to support in your custom UOD node that derive from UInterchangeBaseNode. The attribute key will be declared under the private access modifier, and the functions are declared under the public access modifier. The class access modifier is public after calling this macro. @note - The Get will return false if the attribute was never set. @note - The Set will add the attribute to the storage or update the value if the storage already has this attribute. @note - The Apply will set a member variable of the AssetType instance. It will apply the value only if the storage contains the attribute key @param AttributeName - The name of the Get/Set functions. For example, if you pass Foo you will end up with GetFoo and SetFoo functions. @param AttributeType - This is to specify the type of the attribute: bool, float, FString, or anything else supported by the FAttributeStorage. @param AssetType - This is the asset you want to apply the storage value. @param EnumType - Optional. Specify only if the AssetType member is an enum so we can type cast it in the apply function (we use uint8 to store the enum value).
- L124 _macro_ `#define IMPLEMENT_NODE_ATTRIBUTE_GETTER(AttributeName, AttributeType) \`
- L128 _macro_ `#define IMPLEMENT_NODE_ATTRIBUTE_SETTER_NODELEGATE(AttributeName, AttributeType) \`
- L133 _macro_ `#define INTERCHANGE_BASE_NODE_ADD_ATTRIBUTE(ValueType) \`
- L137 _macro_ `#define INTERCHANGE_BASE_NODE_GET_ATTRIBUTE(ValueType) \`
- L149 _namespace_ `namespace UE`
- L149 _namespace_ `namespace Interchange` (scope `UE`)

### `Source/Runtime/Interchange/Core/Public/Nodes/InterchangeBaseNodeContainer.h` (Public)


#### class `UInterchangeBaseNodeContainer`  
`class UInterchangeBaseNodeContainer : public UObject`  
_L38-314_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: The Interchange UInterchangeBaseNode graph is a format used to feed factories and writers when they import, reimport, and export an asset or scene. This container holds a flat list of all nodes that have been translated from the source data. Translators fill this container, and the import/export managers read it to execute the import/export process.
- L42 _public prototype_ `UInterchangeBaseNodeContainer();`
- L48 _public function_ `void Reset()` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Empty the container.
- L58 _public function_ `void RemoveNode(const FString& NodeUniqueID)` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Removes node from Nodes map with the given NodeUniqueID.
- L71 _public prototype_ `FString AddNode(UInterchangeBaseNode* Node);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Add a node to the container. The node is added into a TMap. @param Node - a pointer on the node you want to add @return: return the node unique ID of the added item. If the node already exist it will return the existing ID. Return InvalidNodeUid if the node cannot be added.
- L74 _public prototype_ `bool ReplaceFactoryNode(const FString& NodeUniqueID, UInterchangeFactoryBaseNode* NewNode);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")`
- L77 _public function_ `void ReplaceNode(const FString& NodeUniqueID, UInterchangeFactoryBaseNode* NewNode)` — `UE_DEPRECATED(5.8, "Use ReplaceFactoryNode instead.")`
- L83 _public prototype_ `bool RemoveFactoryNode(const FString& NodeUniqueID);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")`
- L87 _public prototype_ `bool IsNodeUidValid(const FString& NodeUniqueID) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Return true if the node unique ID exists in the container.
- L101 _public prototype_ `void SetNamespace(const FString& Namespace, UClass* TargetClass);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Set a namespace to all node of the target class in this container. A valid node namespace is prefix to the unique ID in UInterchangeBaseNode::GetUniqueId(). After adding the namespace this function will find any string attribute in all the node that reference the node unique ID and replace the attribute value with the new unique id. The last step is to remap the node container with the new Ids. @Param Namespace - Is the new namespace you want to set. Pass an empty string to remove an existing namespace. @Param TargetClass - Optional, this parameter represent the node class we want to apply the namespace on. If null all node will be tagged with the namespace @Note - Changing all node namespace wont work since some node class use a combination of the unique ID in there attributes and we cannot change those attribute in a generic way.
- L104 _public prototype_ `void IterateNodes(TFunctionRef<void(const FString&, UInterchangeBaseNode*)> IterationLambda) const;` — Unordered iteration of the all nodes.
- L107 _public function_ `template <typename T> void IterateNodesOfType(TFunctionRef<void(const FString&, T*)> IterationLambda) const`
- L119 _public function_ `template <typename T> void GetNodesOfType(TArray<T*>& OutNodes) const`
- L133 _public function_ `template <typename T> void GetNodeUIDsOfType(TArray<FString>& OutNodeUIDs) const`
- L148 _public function_ `void IterateNodeChildren(const FString& NodeUniqueID, TFunctionRef<void(const UInterchangeBaseNode*)> IterationLambda) const` — Recursively traverse the hierarchy starting with the specified node unique ID. If the iteration lambda returns true, the iteration will stop. If the iteration lambda returns false, the iteration will continue.
- L167 _public function_ `bool BreakableIterateNodeChildren(const FString& NodeUniqueID, TFunctionRef<bool(const UInterchangeBaseNode*)> IterationLambda) const` — Recursively traverse the hierarchy starting with the specified node unique ID. If the iteration lambda returns true, the iteration will stop. If the iteration lambda returns false, the iteration will continue. @return - Return true if the iteration was broken, or false otherwise.
- L188 _public prototype_ `void BreakableIterateNodes(TFunctionRef<bool(const FString&, UInterchangeBaseNode*)> IterationLambda) const;` — Unordered iteration of the all nodes, but can be stopped early by returning true.
- L191 _public function_ `template <typename T> void BreakableIterateNodesOfType(TFunctionRef<bool(const FString&, T*)> IterationLambda) const`
- L207 _public prototype_ `void GetRoots(TArray<FString>& RootNodes) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Return all nodes that do not have any parent.
- L211 _public prototype_ `void GetNodes(const UClass* ClassNode, TArray<FString>& OutNodes) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Return all nodes that are of the ClassNode type.
- L215 _public prototype_ `const UInterchangeBaseNode* GetNode(const FString& NodeUniqueID) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Get a node pointer. Once added to the container, nodes are considered const.
- L219 _public prototype_ `UInterchangeFactoryBaseNode* GetFactoryNode(const FString& NodeUniqueID) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Get a factory node pointer.
- L223 _public prototype_ `bool SetNodeParentUid(const FString& NodeUniqueID, const FString& NewParentNodeUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Set the ParentUid of the node.
- L227 _public prototype_ `bool ClearNodeParentUid(const FString& NodeUniqueID);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Remove the node's ParentUid, making it into a top-level node
- L231 _public prototype_ `bool SetNodeDesiredChildIndex(const FString& NodeUniqueID, const int32& NewNodeDesiredChildIndex);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Set the desired child index of the node.
- L235 _public prototype_ `int32 GetNodeChildrenCount(const FString& NodeUniqueID) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Get the number of children the node has.
- L239 _public prototype_ `TArray<FString> GetNodeChildrenUids(const FString& NodeUniqueID) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Get the UIDs of all the node's children.
- L241 _public prototype_ `TArray<FString>* GetCachedNodeChildrenUids(const FString& NodeUniqueID) const;`
- L245 _public prototype_ `UInterchangeBaseNode* GetNodeChildren(const FString& NodeUniqueID, int32 ChildIndex);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Get the nth const child of the node
- L248 _public prototype_ `const UInterchangeBaseNode* GetNodeChildren(const FString& NodeUniqueID, int32 ChildIndex) const;` — Get the nth const child of the node. Const version.
- L255 _public prototype_ `void SerializeNodeContainerData(FArchive& Ar);` — This function serializes the node container and all node sub-objects it points . Out-of-process translators like FBX will dump a file containing this data, and the editor will read the file and regenerate the container from the saved data.
- L259 _public prototype_ `void SaveToFile(const FString& Filename);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Serialize the node container into the specified file.
- L263 _public prototype_ `void LoadFromFile(const FString& Filename);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Serialize the node container from the specified file.
- L267 _public prototype_ `void ComputeChildrenCache();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Fill the cache of children UIDs to optimize the GetNodeChildrenUids call.
- L270 _public prototype_ `void SetChildrenCache(const TMap<FString, TArray<FString>>& InChildrenCache);` — Sets the children cache from an incoming data set.
- L273 _public prototype_ `TMap<FString, TArray<FString>>& GetChildrenCache();` — Gets the children cache.
- L277 _public function_ `void ResetChildrenCache()` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node Container")` — Reset the cache of children UIDs.
- L286 _public prototype_ `bool GetIsAncestor(const FString& NodeUniqueID, const FString& AncestorUID) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Checks if ParentNodeUID is an ancestor.
- L288 _public prototype_ `void SetupNode(UInterchangeBaseNode* Node, const FString& NodeUID, const FString& DisplayLabel, EInterchangeNodeContainerType ContainerType, const FString& ParentNodeUID = TEXT(""));`
- L292 _public prototype_ `void SetupAndReplaceFactoryNode(UInterchangeFactoryBaseNode* Node, const FString& NodeUID, const FString& DisplayLabel, EInterchangeNodeContainerType ContainerType, const FString& OldNodeUID, const FString& ParentNodeUID = TEXT(""));`
- L298 _public function_ `template<typename PREDICATE_CLASS> inline void SortNodes(const PREDICATE_CLASS& Predicate)`
- L305 _private prototype_ `void InternalReorderChildren(TArray<FString>& Children) const;`
- L307 _private prototype_ `UInterchangeBaseNode* GetNodeChildrenInternal(const FString& NodeUniqueID, int32 ChildIndex);`
- L311 _private member_ `TMap<FString, TObjectPtr<UInterchangeBaseNode> > Nodes;` — `UPROPERTY(VisibleAnywhere, Category = "Interchange | Node Container")` — Flat List of the nodes. Since the nodes are variable size, we store a pointer.
- L313 _private member_ `mutable TMap<FString, TArray<FString> > ChildrenCache;`

### `Source/Runtime/Interchange/Core/Public/Nodes/InterchangeBaseNodeUtilities.h` (Public)


#### class `UE::Interchange::TArrayAttributeHelper`  
`template<typename ItemType> class TArrayAttributeHelper`  
_L49-308_
- desc: Helper class to manage an array of items inside an attribute storage
- L52 _public function_ `~TArrayAttributeHelper()`
- L60 _public function_ `void Initialize(const TSharedPtr<FAttributeStorage, ESPMode::ThreadSafe>& InAttributes, const FString& BaseKeyName)`
- L69 _public function_ `int32 GetCount() const`
- L89 _public function_ `void GetItem(const int32 Index, ItemType& OutItem) const`
- L122 _public function_ `void GetItems(TArray<ItemType>& OutItems) const`
- L160 _public function_ `bool AddItem(const ItemType& Item)`
- L200 _public function_ `bool RemoveItem(const ItemType& ItemToDelete)`
- L264 _public function_ `bool RemoveAllItems()`
- L297 _private member_ `TWeakPtr<FAttributeStorage, ESPMode::ThreadSafe> Attributes = nullptr;`
- L298 _private member_ `FAttributeKey KeyCount;`
- L299 _private function_ `FAttributeKey GetKeyCount() const`
- L304 _private function_ `FAttributeKey GetIndexKey(int32 Index) const`

#### class `UE::Interchange::TMapAttributeHelper`  
`template<typename KeyType, typename ValueType> class TMapAttributeHelper`  
_L314-625_
- desc: Helper class to manage a TMap where the key and value type can be any type support by the FAttributeStorage
- L317 _private typedef_ `template<typename T> using TAttributeHandle = FAttributeStorage::TAttributeHandle<T>;`
- L320 _public function_ `void Initialize(const TSharedRef<FAttributeStorage, ESPMode::ThreadSafe>& InAttributes, const FString& BaseKeyName)`
- L340 _public prototype_ `TMapAttributeHelper() = default;`
- L341 _public prototype_ `TMapAttributeHelper(const TMapAttributeHelper&) = default;`
- L342 _public prototype_ `TMapAttributeHelper(TMapAttributeHelper&&) = default;`
- L343 _public prototype_ `TMapAttributeHelper& operator=(const TMapAttributeHelper&) = default;`
- L344 _public prototype_ `TMapAttributeHelper& operator=(TMapAttributeHelper&&) = default;`
- L346 _public function_ `~TMapAttributeHelper()`
- L351 _public function_ `bool SetKeyValue(const KeyType& InKey, const ValueType& InValue)`
- L357 _public function_ `bool GetValue(const KeyType& InKey, ValueType& OutValue) const`
- L363 _public function_ `bool RemoveKey(const KeyType& InKey)`
- L369 _public function_ `bool RemoveKeyAndGetValue(const KeyType& InKey, ValueType& OutValue)`
- L375 _public function_ `bool SetKeyValueByHash(uint32 Hash, const KeyType& InKey, const ValueType& InValue)`
- L407 _public function_ `bool GetValueByHash(uint32 Hash, const KeyType& InKey, ValueType& OutValue) const`
- L424 _public function_ `bool RemoveKeyByHash(uint32 Hash, const KeyType& InKey)`
- L440 _public function_ `bool RemoveKeyAndGetValueByHash(uint32 Hash, const KeyType& InKey, ValueType& OutValue)`
- L459 _public function_ `void Reserve(int32 Number)`
- L464 _public function_ `void Empty(int32 NumOfExpectedElements = 0)`
- L469 _public function_ `int32 GetCount() const`
- L474 _public function_ `TMapAttributeHelper& operator=(const TMap<KeyType, ValueType>& InMap)`
- L495 _public function_ `TMap<KeyType, ValueType> ToMap() const`
- L513 _public function_ `void RebuildCache()`
- L549 _private function_ `FAttributeKey GetKeyAttribute(int32 Index) const`
- L559 _private function_ `FAttributeKey GetValueAttribute(const KeyType& InKey) const`
- L570 _private function_ `TAttributeHandle<KeyType> GetLastKeyAttributeHandle() const`
- L580 _private function_ `bool RemoveBySwap(uint32 Hash, const KeyType& InKey, TPair<TAttributeHandle<KeyType>, TAttributeHandle<ValueType>>& CachedPair)`
- L602 _private function_ `void EmptyInternal(int32 NumOfExpectedElements)`
- L622 _private member_ `TMap<KeyType, TPair<TAttributeHandle<KeyType>, TAttributeHandle<ValueType>>> CachedKeysAndValues;`
- L623 _private member_ `TAttributeHandle<int32> KeyCountHandle;` — Assign in Initialize function, it will ensure if its the default value (NAME_None) when using the class
- L624 _private member_ `TWeakPtr<FAttributeStorage, ESPMode::ThreadSafe> Attributes = nullptr;`

#### class `UE::Interchange::TSetAttributeHelper`  
`template<typename ValueType> class TSetAttributeHelper`  
_L633-867_
- desc: Helper class to manage a TSet where the value type can be any type support by the FAttributeStorage This class can also load storage made for the TArrayAttributeHelper but will ignore duplicate values
- L636 _private typedef_ `template<typename T> using TAttributeHandle = FAttributeStorage::TAttributeHandle<T>;`
- L639 _public function_ `void Initialize(const TSharedPtr<FAttributeStorage, ESPMode::ThreadSafe>& InAttributes, const FString& BaseKeyName)`
- L659 _public prototype_ `TSetAttributeHelper() = default;`
- L660 _public prototype_ `TSetAttributeHelper(const TSetAttributeHelper&) = default;`
- L661 _public prototype_ `TSetAttributeHelper(TSetAttributeHelper&&) = default;`
- L662 _public prototype_ `TSetAttributeHelper& operator=(const TSetAttributeHelper&) = default;`
- L663 _public prototype_ `TSetAttributeHelper& operator=(TSetAttributeHelper&&) = default;`
- L665 _public function_ `~TSetAttributeHelper()`
- L674 _public function_ `bool AddItem(const ValueType& InValue)` — Adds an item. Returns true if the item is added successfully. Returns false if the item is already present or if Initialize was not properly called before adding an item.
- L695 _public function_ `bool HasItem(const ValueType& InValue) const`
- L709 _public function_ `bool RemoveItem(const ValueType& InValue)` — Remove an item if it exists. Will realign attributes by indices in the storage if needed (0(N)).
- L750 _public function_ `void Reserve(int32 Number)`
- L755 _public function_ `void Empty(int32 NumOfExpectedElements = 0)`
- L760 _public function_ `int32 GetCount() const`
- L767 _public function_ `TSetAttributeHelper& operator=(const TSet<ValueType>& InSet)`
- L788 _public function_ `TSet<ValueType> ToSet() const`
- L803 _public function_ `void RebuildCache()`
- L834 _private function_ `void EmptyInternal(int32 NumOfExpectedElements)`
- L852 _private member_ `TMap<ValueType, FAttributeKey> CachedValues;`
- L853 _private member_ `TAttributeHandle<int32> KeyCountHandle;`
- L854 _private member_ `TWeakPtr<FAttributeStorage, ESPMode::ThreadSafe> Attributes = nullptr;`
- L856 _private member_ `FAttributeKey KeyCount;`
- L857 _private function_ `FAttributeKey GetKeyCount() const`
- L862 _private function_ `FAttributeKey GetIndexKey(int32 Index) const`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Interchange` (scope `UE`)
- L16 _function_ `static const FString& ArrayIndexKey()` (scope `UE::Interchange`)
- L22 _function_ `static FAttributeKey BuildArrayKeyFromIndex(const FString& BaseKeyName, uint32 Index)` (scope `UE::Interchange`)
- L28 _function_ `static FString BuildDisplayNameForArrayKey(const FString& BaseDisplayName, const FString& ArrayAttributeKey)` (scope `UE::Interchange`)

### `Source/Runtime/Interchange/Core/Public/Nodes/InterchangeFactoryBaseNode.h` (Public)


#### struct `UE::Interchange::FFactoryBaseNodeStaticData`  
`struct FFactoryBaseNodeStaticData : public FBaseNodeStaticData`  
_L159-166_
- inherits: `FBaseNodeStaticData`
- L161 _public prototype_ `static const FString& FactoryDependenciesBaseKey();`
- L162 _public prototype_ `static const FString& AttributesAppliedThroughDelegatesBaseKey();`
- L163 _public prototype_ `static const FAttributeKey& ReimportStrategyFlagsKey();`
- L164 _public prototype_ `static const FAttributeKey& SkipNodeImportKey();`
- L165 _public prototype_ `static const FAttributeKey& ForceNodeReimportKey();`

#### enum `EReimportStrategyFlags`  
`enum class EReimportStrategyFlags : uint8`  
_L171-179_
- reflection: `UENUM()`
- L174 _public enumerator_ `ApplyNoProperties` — Do not apply any properties when reimporting. Simply change the source data
- L176 _public enumerator_ `ApplyPipelineProperties` — Always apply all properties specified by the pipeline.
- L178 _public enumerator_ `ApplyEditorChangedProperties UMETA(DisplayName = "Preserve Editor Changed Properties")` — Always apply all properties specified by the pipeline, but leave the properties that were modified in the editor since the last import.

#### class `UInterchangeFactoryBaseNode`  
`class UInterchangeFactoryBaseNode : public UInterchangeBaseNode`  
_L187-468_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeBaseNode`
- desc: This struct is used to store and retrieve key-value attributes. The attributes are stored in a generic FAttributeStorage that serializes the values in a TArray64<uint8>. See UE::Interchange::EAttributeTypes to know the supported template types. This is an abstract class. This is the base class of the Interchange node graph format; all classes in this format should derive from this class.
- L192 _public prototype_ `UInterchangeFactoryBaseNode();`
- L194 _public function_ `virtual void Serialize(FArchive& Ar) override`
- L205 _public prototype_ `virtual FString GetKeyDisplayName(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L206 _public prototype_ `virtual FString GetAttributeCategory(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L207 _public prototype_ `virtual bool ShouldHideAttribute(const UE::Interchange::FAttributeKey& NodeAttributeKey) const override;`
- L215 _public prototype_ `EReimportStrategyFlags GetReimportStrategyFlags() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Return the reimport strategy flags.
- L222 _public prototype_ `bool SetReimportStrategyFlags(const EReimportStrategyFlags& ReimportStrategyFlags);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Change the reimport strategy flags.
- L232 _public prototype_ `bool ShouldSkipNodeImport() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Return true if this node should skip the factory import process, or false otherwise. Nodes can be in a situation where we have to skip the import process because we cannot import the associated asset for multiple reasons. For example: - An asset can already exist and represents a different type (UClass). - An asset can already exist and is being compiled. - An asset can already exist and is being imported by another concurrent import task (such as a user importing multiple files at the same time in the same content folder).
- L238 _public prototype_ `bool SetSkipNodeImport();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Add the skip node attribute. Use this function to cancel the creation of the Unreal asset. See ShouldSkipNodeImport for more documentation.
- L244 _public prototype_ `bool UnsetSkipNodeImport();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Remove the skip node attribute. See ShouldSkipNodeImport for more documentation.
- L250 _public prototype_ `virtual class UClass* GetObjectClass() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Return the UClass of the object we represent, so we can find the factory/writer.
- L256 _public prototype_ `bool GetCustomSubPath(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Return the custom sub-path under PackageBasePath where the assets will be created.
- L262 _public prototype_ `bool SetCustomSubPath(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Set the custom sub-path under PackageBasePath where the assets will be created.
- L268 _public prototype_ `bool GetCustomLevelUid(FString& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | ActorFactory")` — If this node represent a scene asset (actor), return a specific level in which we will create this scene asset.
- L274 _public prototype_ `bool SetCustomLevelUid(const FString& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | ActorFactory")` — If this node represent a scene asset (actor), you can set a specific level in which we will create this scene asset.
- L280 _public prototype_ `int32 GetFactoryDependenciesCount() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Retrieve the number of factory dependencies for this object.
- L286 _public prototype_ `TSet<FString> GetFactoryDependencies() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Retrieve the dependencies for this object.
- L293 _public prototype_ `void GetFactoryDependency(const int32 Index, FString& OutDependency) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — `UE_DEPRECATED(5.8, "Use GetFactoryDependencies or HasFactoryDependency instead.")` — Retrieve one dependency for this object.
- L299 _public prototype_ `bool HasFactoryDependency(const FString& DependencyUid) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Returns true if this factory node has a dependency on the factory which Uid is DependencyUid.
- L305 _public prototype_ `bool AddFactoryDependencyUid(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Add one dependency to this object.
- L311 _public prototype_ `bool RemoveFactoryDependencyUid(const FString& DependencyUid);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Remove one dependency from this object.
- L317 _public prototype_ `bool GetCustomReferenceObject(FSoftObjectPath& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Return the custom ReferenceObject: the UObject this factory node has created.
- L323 _public prototype_ `bool SetCustomReferenceObject(const FSoftObjectPath& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Set the custom ReferenceObject: the UObject this factory node has created.
- L325 _public prototype_ `static FString BuildFactoryNodeUid(const FString& TranslatedNodeUid);`
- L326 _public prototype_ `static FString BuildTranslatedNodeUid(const FString& InFactoryNodeUid);`
- L335 _public prototype_ `template<typename AttributeType> inline void AddApplyAndFillDelegates(const FString& NodeAttributeKey, UClass* ObjectClass, const FName PropertyName);` — Adds the delegates that will read and write the attribute value to a UObject. @param NodeAttributeKey	The key of the attribute for which we are adding the delegates. @param ObjectClass		The class of the object that we will apply and fill on. @param PropertyName		The name of the property of the ObjectClass that we will read and write to.
- L345 _public prototype_ `template<typename AttributeType> inline bool ApplyAttributeToObject(const FString& NodeAttributeKey, UObject* Object, const FName PropertyName) const;` — Writes an attribute value to a UObject. @param NodeAttributeKey	The key for the attribute to write. @param Object			The object to write to. @param PropertyName		The name of the property to write to on the Object. @result					True if the operation succeeded.
- L355 _public prototype_ `template<typename AttributeType> inline bool FillAttributeFromObject(const FString& NodeAttributeKey, UObject* Object, const FName PropertyName);` — Reads an attribute value from a UObject. @param NodeAttributeKey	The key for the attribute to read. @param Object			The object to read from. @param PropertyName		The name of the property to read from on the Object. @result					True if the operation succeeded.
- L362 _public function_ `virtual void CopyWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object)` — Copies all the attributes from SourceNode to this node. @param SourceNode		The source factory node to copy from. @param Object			The object to build delegates on custom attributes from, if applicable.
- L373 _public prototype_ `void ApplyAllCustomAttributeToObject(UObject* Object) const;` — Each Attribute that was set and has a delegate set for the specified UObject->UClass will have the delegate executed so it applies the attribute to the UObject property. See the macros IMPLEMENT_NODE_ATTRIBUTE_SETTER at the top of the file to know how delegates are setup for properties.
- L375 _public prototype_ `void FillAllCustomAttributeFromObject(UObject* Object) const;`
- L380 _public prototype_ `void RestoreAllCustomAttributeDelegates();` — Adds apply and fill delegates for attributes again that were using custom delegates.
- L386 _public prototype_ `void RemoveCustomAttributesForClass(UClass* Class);` — Removes all custom attribute delegates registered for the provided class. @param Class				The class used to pick which delegates to remove.
- L391 _public prototype_ `void RemoveAllCustomAttributeDelegates();` — Removes all custom attribute delegates that are currently added.
- L399 _public prototype_ `static UInterchangeFactoryBaseNode* DuplicateWithObject(const UInterchangeFactoryBaseNode* SourceNode, UObject* Object);` — Copies all the custom attributes from SourceNode to this node, and gets the appropriate values from Object. @param SourceNode		The source factory node to copy from. @param Object			The object to fill custom attributes' values from, if applicable.
- L406 _public prototype_ `bool ShouldForceNodeReimport() const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Return whether or not an object should be created even if it has been deleted in the editor. Return false by default.
- L412 _public prototype_ `bool SetForceNodeReimport();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Allow the creation of the Unreal object even if it has been previously deleted in the editor.
- L418 _public prototype_ `bool UnsetForceNodeReimport();` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Disallow the creation of the Unreal object if it has been previously deleted in the editor.
- L425 _public function_ `virtual bool IsRuntimeImportAllowed() const` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node")` — Return if the import of the class is allowed at runtime.
- L434 _protected prototype_ `virtual void OnRestoreAllCustomAttributeDelegates();` — Adds apply and fill delegates for attributes again that were using custom delegates.
- L445 _protected prototype_ `template<typename PropertyType> inline bool ApplyPropertyValueToObject(const PropertyType& Value, UObject* Object, const FName PropertyName) const;` — Writes a value to an UObject's property. @param Value				The value to write. @param Object			The object to write to. @param PropertyName		The name of the property to write to on the Object. @result					True if the operation succeeded.
- L451 _protected member_ `UE::Interchange::TSetAttributeHelper<FString> FactoryDependencies;` — Those dependencies are used by the Interchange parsing task to make sure the assets are created in the correct order. Examples: The Mesh factory node will have dependencies on the material factory node, and the Material factory node will have dependencies on the texture factory node.
- L454 _protected member_ `TMap<UClass*, TArray<UE::Interchange::FApplyAttributeToAsset>> ApplyCustomAttributeDelegates;` — This array holds the delegate to apply the attribute that has to be set on an UObject.
- L456 _protected member_ `TMap<UClass*, TArray<UE::Interchange::FFillAttributeToAsset>> FillCustomAttributeDelegates;`
- L458 _protected member_ `UE::Interchange::TArrayAttributeHelper<FString> AttributesAppliedThroughDelegates;`
- L461 _protected member_ `TSet<FString> AttributesAppliedThroughDelegatesKeySet;` — `UPROPERTY(Transient)`
- L465 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomSubPathKey = UE::Interchange::FAttributeKey(TEXT("SubP`
- L466 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomLevelUidKey = UE::Interchange::FAttributeKey(TEXT("Leve`
- L467 _private member_ `const UE::Interchange::FAttributeKey Macro_CustomReferenceObjectKey = UE::Interchange::FAttributeKey(TEXT("Refe`
- L471 _function_ `template<typename AttributeType> inline void UInterchangeFactoryBaseNode::AddApplyAndFillDelegates(const FString& NodeAttributeKey, UClass* ObjectClass, const FName PropertyName)`
- L493 _function_ `template<typename AttributeType> inline bool UInterchangeFactoryBaseNode::ApplyAttributeToObject(const FString& NodeAttributeKey, UObject* Object, const FName PropertyName) const`
- L510 _function_ `template<typename AttributeType> inline bool UInterchangeFactoryBaseNode::FillAttributeFromObject(const FString& NodeAttributeKey, UObject* Object, const FName PropertyName)`
- L546 _function_ `template<> inline bool UInterchangeFactoryBaseNode::FillAttributeFromObject<FString>(const FString& NodeAttributeKey, UObject* Object, const FName PropertyName)` — Specialized version of FillAttributeFromObject for strings. If the target property is an FObjectPropertyBase, treat the string as an object path.
- L581 _function_ `template<> inline bool UInterchangeFactoryBaseNode::FillAttributeFromObject<bool>(const FString& NodeAttributeKey, UObject* Object, const FName PropertyName)` — Specialized version of FillAttributeFromObject for bools. If the target property is an FBoolProperty, treat the property as a bitfield.
- L613 _function_ `template<typename PropertyType> inline bool UInterchangeFactoryBaseNode::ApplyPropertyValueToObject(const PropertyType& Value, UObject* Object, const FName PropertyName) const`
- L647 _function_ `template<> inline bool UInterchangeFactoryBaseNode::ApplyPropertyValueToObject<FString>(const FString& Value, UObject* Object, const FName PropertyName) const` — Specialized version of ApplyPropertyValueToObject for strings. If the target property is an FObjectPropertyBase, treat the string as an object path.
- L687 _function_ `template<> inline bool UInterchangeFactoryBaseNode::ApplyPropertyValueToObject<bool>(const bool& Value, UObject* Object, const FName PropertyName) const` — Specialized version of ApplyPropertyValueToObject for bools. If the target property is an FBoolProperty, treat the property as a bitfield.

#### Free symbols / members of external scopes

- L23 _macro_ `#define IMPLEMENT_NODE_ATTRIBUTE_DELEGATE_BY_PROPERTYNAME(AttributeName, AttributeType, ObjectType, PropertyName) \`
- L34 _macro_ `#define IMPLEMENT_NODE_ATTRIBUTE_SETTER(NodeClassName, AttributeName, AttributeType, AssetType) \`
- L57 _macro_ `#define IMPLEMENT_NODE_ATTRIBUTE_SETTER_WITH_CUSTOM_DELEGATE_WITH_CUSTOM_CLASS(NodeClassName, AttributeName, AttributeType, AssetType) \` — Use this macro to implement a custom node attribute setter that will add a delegate to apply the node attribute value to any UObject derived from the specified type class. Use this macro if the type class is different from the node's GetObjectCLass(). The node should derive from UInterchangeFactoryBaseNode to apply a delegate. The node needs to implement 2 functions for the attribute: - ApplyCustom##AttributeName##ToAsset(UObject*): see the UE::Interchange::FApplyAttributeToAsset delegate signature. - FillCustom##AttributeName##FromAsset(UObject*): see the UE::Interchange::FFillAttributeToAsset delegate signature.
- L79 _macro_ `#define IMPLEMENT_NODE_ATTRIBUTE_SETTER_WITH_CUSTOM_DELEGATE(NodeClassName, AttributeName, AttributeType) \` — This macro uses the factory node GetObjectClass() to register the delegate instead of receiving a TypeClass. See the documentation of IMPLEMENT_NODE_ATTRIBUTE_SETTER_WITH_CUSTOM_DELEGATE_WITH_CUSTOM_CLASS.
- L104 _macro_ `#define COPY_NODE_DELEGATES(SourceNode, AttributeName, AttributeType, AssetType) \` — This macro forces the addition of the Fill and Apply delegates on 'this' if the designated attribute has been set on the source node. Copying the arrays of delegates from the source node to 'this' is not sufficient because the delegates of the source node have a reference on the source node not 'this'. Consequently, a call to those delegates would always use the source node.
- L116 _macro_ `#define COPY_NODE_DELEGATES_WITH_CUSTOM_DELEGATE(SourceNode, NodeClassName, AttributeName, AttributeType, AssetClass) \`
- L130 _macro_ `#define REFILL_CUSTOM_ATTRIBUTE_APPLY_DELEGATE(AttributeName, AttributeType) \`
- L141 _macro_ `#define REFILL_CUSTOM_ATTRIBUTE_APPLY_DELEGATE_EXPLICIT(AttributeKey, Getter, Setter, AttributeType) \`
- L153 _namespace_ `namespace UE`
- L153 _namespace_ `namespace Interchange` (scope `UE`)
- L156 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FApplyAttributeToAsset, UObject*);`
- L156 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FApplyAttributeToAsset, UObject*);` (scope `UE::Interchange`)
- L157 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFillAttributeToAsset, UObject*);`
- L157 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FFillAttributeToAsset, UObject*);` (scope `UE::Interchange`)
- L477 _function_ `` (scope `UInterchangeFactoryBaseNode::AddApplyAndFillDelegates`)

### `Source/Runtime/Interchange/Core/Public/Nodes/InterchangeSourceNode.h` (Public)


#### struct `UE::Interchange::FSourceNodeExtraInfoStaticData`  
`struct FSourceNodeExtraInfoStaticData`  
_L20-25_
- L22 _public prototype_ `static const FString& GetApplicationVendorExtraInfoKey();`
- L23 _public prototype_ `static const FString& GetApplicationNameExtraInfoKey();`
- L24 _public prototype_ `static const FString& GetApplicationVersionExtraInfoKey();`

#### class `UInterchangeSourceNode`  
`class UInterchangeSourceNode : public UInterchangeBaseNode`  
_L32-244_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeBaseNode`
- desc: This class allows a translator to add general source data that describes the whole source. Pipelines can use this information.
- L36 _private prototype_ `UInterchangeSourceNode();`
- L46 _public prototype_ `void InitializeSourceNode(const FString& UniqueID, const FString& DisplayLabel, UInterchangeBaseNodeContainer* NodeContainer);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | source")` — Initialize the base data of the node. Adds it to NodeContainer. @param UniqueID - The unique ID for this node. @param DisplayLabel - The name of the node.
- L51 _public prototype_ `virtual FString GetTypeName() const override;` — Return the node type name of the class. This is used when reporting errors.
- L54 _public prototype_ `static UInterchangeSourceNode* FindOrCreateUniqueInstance(UInterchangeBaseNodeContainer* NodeContainer);` — Translators that want to modify the common data should ensure they create the unique common pipeline node.
- L58 _public prototype_ `static const UInterchangeSourceNode* GetUniqueInstance(const UInterchangeBaseNodeContainer* NodeContainer);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | source")` — This function should be use by pipelines to avoid creating a node. If the unique instance doesn't exist, returns nullptr.
- L62 _public prototype_ `bool GetCustomSourceFrameRateNumerator(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Query the source frame rate numerator.
- L66 _public prototype_ `bool SetCustomSourceFrameRateNumerator(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Set the source frame rate numerator.
- L70 _public prototype_ `bool GetCustomSourceFrameRateDenominator(int32& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Query the source frame rate denominator.
- L74 _public prototype_ `bool SetCustomSourceFrameRateDenominator(const int32& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Set the source frame rate denominator.
- L79 _public prototype_ `bool GetCustomSourceTimelineStart(double& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — `UE_DEPRECATED(5.6, "Please, use UInterchangeSkeletalAnimationTrackNode::GetCustomSourceTimelineAnimationStartTime")` — Query the start of the source timeline.
- L84 _public prototype_ `bool SetCustomSourceTimelineStart(const double& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — `UE_DEPRECATED(5.6, "Please, use UInterchangeSkeletalAnimationTrackNode::SetCustomSourceTimelineAnimationStartTime")` — Set the start of the source timeline.
- L89 _public prototype_ `bool GetCustomSourceTimelineEnd(double& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — `UE_DEPRECATED(5.6, "Please, use UInterchangeSkeletalAnimationTrackNode::GetCustomSourceTimelineAnimationStopTime")` — Query the end of the source timeline.
- L94 _public prototype_ `bool SetCustomSourceTimelineEnd(const double& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — `UE_DEPRECATED(5.6, "Please, use UInterchangeSkeletalAnimationTrackNode::SetCustomSourceTimelineAnimationStopTime")` — Set the end of the source timeline.
- L99 _public prototype_ `bool GetCustomAnimatedTimeStart(double& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — `UE_DEPRECATED(5.6, "Please, use UInterchangeSkeletalAnimationTrackNode::GetCustomAnimationStartTime")` — Query the start of the source animated time.
- L104 _public prototype_ `bool SetCustomAnimatedTimeStart(const double& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — `UE_DEPRECATED(5.6, "Please, use UInterchangeSkeletalAnimationTrackNode::SetCustomAnimationStartTime")` — Set the start of the source animated time.
- L109 _public prototype_ `bool GetCustomAnimatedTimeEnd(double& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — `UE_DEPRECATED(5.6, "Please, use UInterchangeSkeletalAnimationTrackNode::GetCustomAnimationStopTime")` — Query the end of the source animated time.
- L114 _public prototype_ `bool SetCustomAnimatedTimeEnd(const double& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — `UE_DEPRECATED(5.6, "Please, use UInterchangeSkeletalAnimationTrackNode::SetCustomAnimationStopTime")` — Set the end of the source animated time.
- L118 _public prototype_ `bool GetCustomImportUnusedMaterial(bool& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Query whether to import materials that aren't used.
- L122 _public prototype_ `bool SetCustomImportUnusedMaterial(const bool& AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Set whether to import materials that aren't used.
- L127 _public prototype_ `bool SetExtraInformation(const FString& Name, const FString& Value);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Set Extra Information that we want to show in the Config Panel (such as File Information).
- L131 _public prototype_ `bool RemoveExtraInformation(const FString& Name);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Remove Extra Information that we dont want to show in the Config Panel.
- L135 _public prototype_ `void GetExtraInformation(TMap<FString, FString>& OutExtraInformation) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Get Extra Information that we want to show in the Config Panel (such as File Information).
- L140 _public prototype_ `bool GetCustomAxisConversionInverseTransform(FTransform& AxisConversionInverseTransform) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Query Axis Conversion Inverse Transform (Primarily used for Socket transform calculations.).
- L144 _public prototype_ `bool SetCustomAxisConversionInverseTransform(const FTransform& AxisConversionInverseTransform);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Set the Axis Conversion Inverse Transform (Primarily used for Socket transform calculations.).
- L152 _public prototype_ `bool GetCustomSubPathPrefix(FString& Prefix) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Gets a prefix that should be added to factory node SubPath custom attributes. For example this can contain the imported scene's name, so that we create an additional content folder named after it to contain the imported assets.
- L156 _public prototype_ `bool SetCustomSubPathPrefix(const FString& Prefix);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Sets the prefix that should be added to factory node SubPath custom attributes.
- L168 _public prototype_ `bool GetCustomUseAssetTypeSubPathSuffix(bool& Suffix) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Gets whether factory nodes for this import should have a suffix named after their asset category added to their custom sub path attribute. For example, if this is set then imported StaticMesh assets will be placed inside of an additional content folder named "StaticMeshes". Note that this is done automatically for all factory nodes created by the generic assets pipeline, but must be handled manually by calling FillSubPathFromSourceNode() from InterchangePipelineHelper.h for any factory nodes that other pipelines may create.
- L175 _public prototype_ `bool SetCustomUseAssetTypeSubPathSuffix(const bool& Suffix);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Sets whether factory nodes for this import should have a suffix named after their asset category added to their custom sub path attribute.
- L179 _public prototype_ `bool GetCustomReimportStrategyFlags(uint8& StrategyFlag) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Get the reimport strategy based on EReimportStrategyFlags
- L183 _public prototype_ `bool SetCustomReimportStrategyFlags(uint8 StrategyFlag);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Set the reimport strategy based on EReimportStrategyFlags
- L187 _public prototype_ `bool GetCustomSkeletalMeshFrontAxis(uint8& AttributeValue) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Get the value of the front axis to be used when importing skeletal meshes.
- L191 _public prototype_ `bool SetCustomSkeletalMeshFrontAxis(uint8 AttributeValue);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Set the value of the front axis to be used when importing skeletal meshes.
- L195 _public prototype_ `bool GetCustomNaniteTriangleThreshold(int64& MinNumTriangles) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Gets the minimum triangle count a mesh needs to have in order to get Nanite enabled for it when bBuildNanite is true on the static mesh pipeline.
- L199 _public prototype_ `bool SetCustomNaniteTriangleThreshold(const int64& MinNumTriangles);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Sets the minimum triangle count a mesh needs to have in order to get Nanite enabled for it when bBuildNanite is true on the static mesh pipeline.
- L203 _public prototype_ `bool GetCustomAllowSceneRootAsJoint(bool& bAllowSceneRootAsJoint) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Gets, if the skeleton processing should accept a SceneRoot as a joint (root node), for when import is forced as Skeletal.
- L207 _public prototype_ `bool SetCustomAllowSceneRootAsJoint(const bool& bAllowSceneRootAsJoint);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Sets, if the skeleton processing should accept a SceneRoot as a joint (root node), for when import is forced as Skeletal.
- L219 _public prototype_ `bool GetCustomAlignSkeletalMeshInScene(bool& AlignSkeletalMeshInScene) const;` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Gets, SkeletalMeshes requires the Scene Transforms to be aligned with the Skeleton. If false then Skeleton and SkeletalMesh should be aligned on Asset level already. (prior to the Scene Composition) For example: true:=FBX false:=glTF
- L223 _public prototype_ `bool SetCustomAlignSkeletalMeshInScene(const bool& AlignSkeletalMeshInScene);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | Source")` — Sets, if SkeletalMeshes requires the Scene Transforms to be aligned with the Skeleton.
- L226 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SourceFrameRateNumerator);`
- L227 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SourceFrameRateDenominator);`
- L228 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SourceTimelineStart);`
- L229 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SourceTimelineEnd);`
- L230 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AnimatedTimeStart);`
- L231 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AnimatedTimeEnd);`
- L232 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ImportUnusedMaterial);`
- L233 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AxisConversionInverseTransform);`
- L234 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SubPathPrefix);`
- L235 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(UseAssetTypeSubPathSuffix);`
- L236 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(ReimportStrategyFlags);`
- L237 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(SkeletalMeshFrontAxis);`
- L238 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(NaniteTriangleThreshold);`
- L239 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AllowSceneRootAsJoint);`
- L240 _private prototype_ `IMPLEMENT_NODE_ATTRIBUTE_KEY(AlignSkeletalMeshInScene);`
- L243 _private member_ `UE::Interchange::TMapAttributeHelper<FString, FString> ExtraInformation;` — Extra InformationTo show in the Config Panel.

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Interchange` (scope `UE`)

### `Source/Runtime/Interchange/Core/Public/Nodes/InterchangeUserDefinedAttribute.h` (Public)


#### struct `FInterchangeUserDefinedAttributeInfo`  
`struct FInterchangeUserDefinedAttributeInfo`  
_L24-36_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | Node | UserDefinedAttributeInfo")`
- L31 _public member_ `UE::Interchange::EAttributeTypes Type;`
- L33 _public member_ `TOptional<FString> PayloadKey;`
- L35 _public member_ `bool RequiresDelegate;`

#### class `UInterchangeUserDefinedAttributesAPI`  
`class UInterchangeUserDefinedAttributesAPI : public UObject`  
_L44-138_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UObject`
- desc: UInterchangeUserDefinedAttributesAPI is used to store and retrieve user-defined attributes such as DCC node attributes, so that pipelines have access to those attributes. Every user-defined attribute has a name, a value, and an optional AnimationPayloadKey: an FRichCurve that is a float curve. The value type must be supported by the UE::Interchange::EAttributeTypes enumeration.
- L59 _public prototype_ `template<typename ValueType> static bool CreateUserDefinedAttribute(UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName, const ValueType& Value, const TOptional<FString>& PayloadKey, bool RequiresDelegate = false);` — Create a user-defined attribute with a value and a optional payload key. param UserDefinedAttributeName - The name of the user-defined attribute. param Value - The value of the user-defined attribute. param PayloadKey - The translator payload key to retrieve the FRichCurve animation for this user-defined attribute. Note - User-defined attributes are the user custom attributes from the DCC translated node (for example, extra attributes in Maya). The payload key points to an FRichCurve payload.
- L62 _public prototype_ `static bool CreateUserDefinedAttribute_Boolean(UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName, const bool& Value, const FString& PayloadKey, bool RequiresDelegate = false);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | UserDefinedAttribute")`
- L65 _public prototype_ `static bool CreateUserDefinedAttribute_Float(UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName, const float& Value, const FString& PayloadKey, bool RequiresDelegate = false);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | UserDefinedAttribute")`
- L68 _public prototype_ `static bool CreateUserDefinedAttribute_Double(UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName, const double& Value, const FString& PayloadKey, bool RequiresDelegate = false);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | UserDefinedAttribute")`
- L71 _public prototype_ `static bool CreateUserDefinedAttribute_Int32(UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName, const int32& Value, const FString& PayloadKey, bool RequiresDelegate = false);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | UserDefinedAttribute")`
- L74 _public prototype_ `static bool CreateUserDefinedAttribute_FString(UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName, const FString& Value, const FString& PayloadKey, bool RequiresDelegate = false);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | UserDefinedAttribute")`
- L84 _public prototype_ `static bool RemoveUserDefinedAttribute(UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | UserDefinedAttribute")` — Remove the specified user-defined attribute. @param UserDefinedAttributeName - The name of the user-defined attribute to remove. @return - True if the attribute exists and was removed, or if the attribute doesn't exist. Returns false if the attribute exists but could not be removed. Note - User-defined attributes are the user custom attributes from the DCC translated node (for example, extra attributes in Maya). The payload key points to an FRichCurve payload.
- L95 _public prototype_ `template<typename ValueType> static bool GetUserDefinedAttribute(const UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName, ValueType& OutValue, TOptional<FString>& OutPayloadKey);` — Get the value of a user-defined attribute and an optional payload key. @param UserDefinedAttributeName - The name of the user-defined attribute. @param OutValue - The value of the user-defined attribute. @param OutPayloadKey - The translator payload key to retrieve the FRichCurve animation for this user-defined attribute. Note - User-defined attributes are the user custom attributes from the DCC translated node (for example, extra attributes in Maya). The payload key points to an FRichCurve payload.
- L98 _public prototype_ `static bool GetUserDefinedAttribute_Boolean(const UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName, bool& OutValue, FString& OutPayloadKey);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | UserDefinedAttribute")`
- L101 _public prototype_ `static bool GetUserDefinedAttribute_Float(const UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName, float& OutValue, FString& OutPayloadKey);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | UserDefinedAttribute")`
- L104 _public prototype_ `static bool GetUserDefinedAttribute_Double(const UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName, double& OutValue, FString& OutPayloadKey);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | UserDefinedAttribute")`
- L107 _public prototype_ `static bool GetUserDefinedAttribute_Int32(const UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName, int32& OutValue, FString& OutPayloadKey);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | UserDefinedAttribute")`
- L110 _public prototype_ `static bool GetUserDefinedAttribute_FString(const UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName, FString& OutValue, FString& OutPayloadKey);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | UserDefinedAttribute")`
- L112 _public prototype_ `static TArray<FInterchangeUserDefinedAttributeInfo> GetUserDefinedAttributeInfos(const UInterchangeBaseNode* InterchangeNode);`
- L115 _public prototype_ `static void GetUserDefinedAttributeInfos(const UInterchangeBaseNode* InterchangeNode, TArray<FInterchangeUserDefinedAttributeInfo>& UserDefinedAttributeInfos);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | UserDefinedAttribute")`
- L118 _public prototype_ `static void DuplicateAllUserDefinedAttribute(const UInterchangeBaseNode* InterchangeSourceNode, UInterchangeBaseNode* InterchangeDestinationNode, bool bAddSourceNodeName);` — `UFUNCTION(BlueprintCallable, Category = "Interchange | Node | UserDefinedAttribute")`
- L120 _public prototype_ `static void AddApplyAndFillDelegatesToFactory(UInterchangeFactoryBaseNode* InterchangeFactoryNode, UClass* ParentClass);`
- L122 _public prototype_ `static UE::Interchange::FAttributeKey MakeUserDefinedPropertyValueKey(const FStringView UserDefinedAttributeName, bool RequiresDelegate);`
- L123 _public prototype_ `static UE::Interchange::FAttributeKey MakeUserDefinedPropertyValueKey(const FString& UserDefinedAttributeName,bool RequiresDelegate);`
- L125 _public prototype_ `static UE::Interchange::FAttributeKey MakeUserDefinedPropertyPayloadKey(const FStringView UserDefinedAttributeName, bool RequiresDelegate);`
- L126 _public prototype_ `static UE::Interchange::FAttributeKey MakeUserDefinedPropertyPayloadKey(const FString& UserDefinedAttributeName, bool RequiresDelegate);`
- L129 _private prototype_ `static bool HasAttribute(const UInterchangeBaseNode* InterchangeSourceNode, const FString& InUserDefinedAttributeName, bool GeneratePayloadKey, bool& OutRequiresDelegate);`
- L130 _private prototype_ `static UE::Interchange::FAttributeKey MakeUserDefinedPropertyKey(const FStringView UserDefinedAttributeName, bool RequiresDelegate, bool GeneratePayloadKey = false);`
- L131 _private prototype_ `static UE::Interchange::FAttributeKey MakeUserDefinedPropertyKey(const FString& UserDefinedAttributeName,bool RequiresDelegate, bool GeneratePayloadKey = false);`
- L134 _private member_ `static const FString UserDefinedAttributeBaseKey;`
- L135 _private member_ `static const FString UserDefinedAttributeValuePostKey;`
- L136 _private member_ `static const FString UserDefinedAttributePayLoadPostKey;`
- L137 _private member_ `static const FString UserDefinedAttributeDelegateKey;`
- L141 _function_ `template<typename ValueType> bool UInterchangeUserDefinedAttributesAPI::CreateUserDefinedAttribute(UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName, const ValueType& Value, const TOptional<FString>& PayloadKey, bool RequiresDelegate )`
- L166 _function_ `template<typename ValueType> bool UInterchangeUserDefinedAttributesAPI::GetUserDefinedAttribute(const UInterchangeBaseNode* InterchangeNode, const FString& UserDefinedAttributeName, ValueType& OutValue, TOptional<FString>& OutPayloadKey)`

### `Source/Runtime/Interchange/Core/Public/PackageUtils/PackageUtils.h` (Public)


#### class `UE::Interchange::FPackageUtils`  
`class FPackageUtils`  
_L14-55_
- L17 _public function_ `static bool IsMapPackageAsset(const FString& ObjectPath)`
- L23 _public function_ `static bool IsMapPackageAsset(const FString& ObjectPath, FString& MapFilePath)`
- L43 _public function_ `static FString ExtractPackageName(const FString& ObjectPath)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Interchange` (scope `UE`)

### `Source/Runtime/Interchange/Core/Public/Types/AttributeStorage.h` (Public)


#### struct `UE::Interchange::Private::TUnderlyingType`  
`template <typename T, typename Enable = void> struct UE_DEPRECATED(5.7, "No longer used.") T`  
_L58-58_
- L63 _public typedef_ `using type = typename std::underlying_type<T>::type;`

#### struct `UE::Interchange::Private::TUnderlyingType`  
`template <typename T> struct UE_DEPRECATED(5.7, "No longer used.") TUnderlyingType<T, typename std::enable_if<std::is_enum<T>::value>::type>`  
_L61-64_
- L63 _public typedef_ `using type = typename std::underlying_type<T>::type;`

#### struct `UE::Interchange::FAttributeKey`  
`struct FAttributeKey`  
_L67-183_
- L69 _public member_ `FString Key;`
- L71 _public prototype_ `FAttributeKey() = default;`
- L73 _public prototype_ `FAttributeKey(const FAttributeKey& Other) = default;`
- L74 _public prototype_ `FAttributeKey(FAttributeKey&& Other) = default;`
- L75 _public prototype_ `FAttributeKey& operator=(const FAttributeKey&) = default;`
- L76 _public prototype_ `FAttributeKey& operator=(FAttributeKey&&) = default;`
- L78 _public function_ `explicit FAttributeKey(const FName& Other)`
- L83 _public function_ `explicit FAttributeKey(const FStringView& Other)`
- L88 _public function_ `explicit FAttributeKey(const FString& Other)`
- L93 _public function_ `explicit FAttributeKey(FString&& Other)`
- L98 _public function_ `explicit FAttributeKey(const FText& Other)`
- L103 _public function_ `explicit FAttributeKey(const TCHAR* Other)`
- L108 _public function_ `inline FAttributeKey& operator=(const FName& Other)`
- L114 _public function_ `inline FAttributeKey& operator=(const FString& Other)`
- L120 _public function_ `inline FAttributeKey& operator=(FString&& Other)`
- L126 _public function_ `inline FAttributeKey& operator=(const FText& Other)`
- L132 _public function_ `inline FAttributeKey& operator=(const TCHAR* Other)`
- L138 _public function_ `inline bool operator==(const FAttributeKey& Other) const`
- L143 _public function_ `inline bool operator!=(const FAttributeKey& Other) const`
- L148 _public function_ `inline bool operator<(const FAttributeKey& Other) const`
- L153 _public function_ `inline bool operator<=(const FAttributeKey& Other) const`
- L158 _public function_ `inline bool operator>(const FAttributeKey& Other) const`
- L163 _public function_ `inline bool operator>=(const FAttributeKey& Other) const`
- L174 _public function_ `inline const FString& ToString() const`
- L179 _public function_ `inline FName ToName() const`

#### enum `UE::Interchange::EAttributeTypes`  
`enum class EAttributeTypes : int32`  
_L196-318_
- desc: Enumerates the built-in types that can be stored in instances of FAttributeStorage. We cannot change the value of a type to make sure the serialization of old assets is always working.
- L198 _public enumerator_ `None = 0`
- L200 _public enumerator_ `Bool = 1`
- L201 _public enumerator_ `Color = 4`
- L202 _public enumerator_ `DateTime = 5`
- L203 _public enumerator_ `Double = 6`
- L204 _public enumerator_ `Enum = 7`
- L205 _public enumerator_ `Float = 8`
- L206 _public enumerator_ `Guid = 9`
- L207 _public enumerator_ `Int8 = 10`
- L208 _public enumerator_ `Int16 = 11`
- L209 _public enumerator_ `Int32 = 12`
- L210 _public enumerator_ `Int64 = 13`
- L211 _public enumerator_ `IntRect = 14`
- L212 _public enumerator_ `LinearColor = 15`
- L213 _public enumerator_ `Name = 16`
- L214 _public enumerator_ `RandomStream = 17`
- L215 _public enumerator_ `String = 18`
- L216 _public enumerator_ `Timespan = 19`
- L217 _public enumerator_ `TwoVectors = 20`
- L218 _public enumerator_ `UInt8 = 21`
- L219 _public enumerator_ `UInt16 = 22`
- L220 _public enumerator_ `UInt32 = 23`
- L221 _public enumerator_ `UInt64 = 24`
- L222 _public enumerator_ `Vector2d = 25`
- L223 _public enumerator_ `IntPoint = 26`
- L224 _public enumerator_ `IntVector = 27`
- L225 _public enumerator_ `Vector2DHalf = 28`
- L226 _public enumerator_ `Float16 = 29`
- L227 _public enumerator_ `OrientedBox = 30`
- L228 _public enumerator_ `FrameNumber = 31`
- L229 _public enumerator_ `FrameRate = 32`
- L230 _public enumerator_ `FrameTime = 33`
- L231 _public enumerator_ `SoftObjectPath = 34`
- L232 _public enumerator_ `Matrix44f = 35`
- L233 _public enumerator_ `Matrix44d = 36`
- L234 _public enumerator_ `Plane4f = 37`
- L235 _public enumerator_ `Plane4d = 38`
- L236 _public enumerator_ `Quat4f = 39`
- L237 _public enumerator_ `Quat4d = 40`
- L238 _public enumerator_ `Rotator3f = 41`
- L239 _public enumerator_ `Rotator3d = 42`
- L240 _public enumerator_ `Transform3f = 43`
- L241 _public enumerator_ `Transform3d = 44`
- L242 _public enumerator_ `Vector3f = 45`
- L243 _public enumerator_ `Vector3d = 46`
- L244 _public enumerator_ `Vector2f = 47`
- L245 _public enumerator_ `Vector4f = 48`
- L246 _public enumerator_ `Vector4d = 49`
- L247 _public enumerator_ `Box2f = 50`
- L248 _public enumerator_ `Box2D = 51`
- L249 _public enumerator_ `Box3f = 52`
- L250 _public enumerator_ `Box3d = 53`
- L251 _public enumerator_ `BoxSphereBounds3f = 54`
- L252 _public enumerator_ `BoxSphereBounds3d = 55`
- L253 _public enumerator_ `Sphere3f = 56`
- L254 _public enumerator_ `Sphere3d = 57`
- L256 _public enumerator_ `BoolArray = 58`
- L257 _public enumerator_ `ColorArray = 59`
- L258 _public enumerator_ `DateTimeArray = 60`
- L259 _public enumerator_ `DoubleArray = 61`
- L260 _public enumerator_ `EnumArray = 62`
- L261 _public enumerator_ `FloatArray = 63`
- L262 _public enumerator_ `GuidArray = 64`
- L263 _public enumerator_ `Int8Array = 65`
- L264 _public enumerator_ `Int16Array = 66`
- L265 _public enumerator_ `Int32Array = 67`
- L266 _public enumerator_ `Int64Array = 68`
- L267 _public enumerator_ `IntRectArray = 69`
- L268 _public enumerator_ `LinearColorArray = 70`
- L269 _public enumerator_ `NameArray = 71`
- L270 _public enumerator_ `RandomStreamArray = 72`
- L271 _public enumerator_ `StringArray = 73`
- L272 _public enumerator_ `TimespanArray = 74`
- L273 _public enumerator_ `TwoVectorsArray = 75`
- L274 _public enumerator_ `ByteArray = 2`
- L275 _public enumerator_ `ByteArray64 = 3`
- L276 _public enumerator_ `UInt16Array = 76`
- L277 _public enumerator_ `UInt32Array = 77`
- L278 _public enumerator_ `UInt64Array = 78`
- L279 _public enumerator_ `Vector2dArray = 79`
- L280 _public enumerator_ `IntPointArray = 80`
- L281 _public enumerator_ `IntVectorArray = 81`
- L282 _public enumerator_ `Vector2DHalfArray = 82`
- L283 _public enumerator_ `Float16Array = 83`
- L284 _public enumerator_ `OrientedBoxArray = 84`
- L285 _public enumerator_ `FrameNumberArray = 85`
- L286 _public enumerator_ `FrameRateArray = 86`
- L287 _public enumerator_ `FrameTimeArray = 87`
- L288 _public enumerator_ `SoftObjectPathArray = 88`
- L289 _public enumerator_ `Matrix44fArray = 89`
- L290 _public enumerator_ `Matrix44dArray = 90`
- L291 _public enumerator_ `Plane4fArray = 91`
- L292 _public enumerator_ `Plane4dArray = 92`
- L293 _public enumerator_ `Quat4fArray = 93`
- L294 _public enumerator_ `Quat4dArray = 94`
- L295 _public enumerator_ `Rotator3fArray = 95`
- L296 _public enumerator_ `Rotator3dArray = 96`
- L297 _public enumerator_ `Transform3fArray = 97`
- L298 _public enumerator_ `Transform3dArray = 98`
- L299 _public enumerator_ `Vector3fArray = 99`
- L300 _public enumerator_ `Vector3dArray = 100`
- L301 _public enumerator_ `Vector2fArray = 101`
- L302 _public enumerator_ `Vector4fArray = 102`
- L303 _public enumerator_ `Vector4dArray = 103`
- L304 _public enumerator_ `Box2fArray = 104`
- L305 _public enumerator_ `Box2DArray = 105`
- L306 _public enumerator_ `Box3fArray = 106`
- L307 _public enumerator_ `Box3dArray = 107`
- L308 _public enumerator_ `BoxSphereBounds3fArray = 108`
- L309 _public enumerator_ `BoxSphereBounds3dArray = 109`
- L310 _public enumerator_ `Sphere3fArray = 110`
- L311 _public enumerator_ `Sphere3dArray = 111`
- L313 _public enumerator_ `InterchangeLODMeshData = 112`
- L314 _public enumerator_ `InterchangeLODMeshDataArray = 113`
- L317 _public enumerator_ `Max = 114` — Max should always be updated if we add a new supported type

#### struct `UE::Interchange::TAttributeTypeTraits`  
`template<typename T, typename Enable = void> struct UE_DEPRECATED(5.7, "No longer used: The AttributeStorage handles all supported type traits internally now.") TAttributeTypeTraits`  
_L332-344_
- L334 _public function_ `static constexpr EAttributeTypes GetType()`
- L340 _public function_ `template<typename ValueType> static FString ToString(const ValueType& Value)`

#### enum `UE::Interchange::EAttributeStorageResult`  
`enum class EAttributeStorageResult : uint64`  
_L354-379_
- desc: Enum to return complete status of a storage operation. It supports success with additional information. It supports multiple errors.
- L356 _public enumerator_ `None = 0x0`
- L358 _public enumerator_ `Operation_Success = 0x1` — Success result.
- L364 _public enumerator_ `Operation_Error_WrongType = (0x1 << 20)` — The type of the value was not matching the existing type. We cannot change the type of an existing attribute.
- L366 _public enumerator_ `Operation_Error_WrongSize = (0x1 << 21)` — The size of the value is different from the existing size. We cannot have a different size.
- L368 _public enumerator_ `Operation_Error_AttributeAllocationCorrupted = (0x1 << 22)` — The AttributeAllocationTable has an attribute whose offset is not valid in the storage.
- L370 _public enumerator_ `Operation_Error_CannotFoundKey = (0x1 << 23)` — We cannot find the specified key.
- L372 _public enumerator_ `Operation_Error_CannotRemoveAttribute = (0x1 << 24)` — There was an error when removing an attribute from the AttributeAllocationTable. The TArray remove has failed.
- L374 _public enumerator_ `Operation_Error_CannotOverrideAttribute = (0x1 << 25)` — We try to override an attribute but the specified options do not allow override.
- L376 _public enumerator_ `Operation_Error_InvalidStorage = (0x1 << 26)` — The storage is invalid (nullptr).
- L378 _public enumerator_ `Operation_Error_InvalidMultiSizeValueData = (0x1 << 27)` — Cannot get a valid value data pointer.

#### enum `UE::Interchange::EAttributeStorageAddOptions`  
`enum class EAttributeStorageAddOptions : uint32`  
_L413-418_
- desc: Enum to pass options when we add an attribute.
- L415 _public enumerator_ `None = 0x0`
- L416 _public enumerator_ `Option_Override = 0x1`

#### enum `UE::Interchange::EAttributeProperty`  
`enum class EAttributeProperty : uint32`  
_L433-437_
- desc: Enumerates the attribute properties. Those properties affect how the attribute are stored or what they are used for.
- L435 _public enumerator_ `None = 0x0`
- L436 _public enumerator_ `NoHash = 0x1`

#### struct `UE::Interchange::TSpecializeType`  
`template<typename T> struct UE_DEPRECATED(5.7, "No longer used.") TSpecializeType`  
_L450-453_
- L452 _public typedef_ `typedef T Type;`

#### struct `UE::Interchange::TAttributeStorageTypeTraits`  
`template<typename T> struct TAttributeStorageTypeTraits`  
_L456-461_
- L458 _public member_ `static constexpr bool bIsArrayOfStringType = false;`
- L459 _public member_ `static constexpr bool bIsArrayOfEnumType = false;`
- L460 _public member_ `static constexpr bool bIsArrayOfEnumAsByteType = false;`
- L481 _public typedef_ `using ElementType = T;`
- L483 _public member_ `static constexpr bool bIsArrayOfStringType = TIsStringType<ElementType>;`
- L484 _public member_ `static constexpr bool bIsArrayOfEnumType = TIsEnum<ElementType>::Value;`
- L485 _public member_ `static constexpr bool bIsArrayOfEnumAsByteType = TIsTEnumAsByte<ElementType>::Value;`

#### struct `UE::Interchange::TAttributeStorageTypeTraits`  
`template<typename T> struct TAttributeStorageTypeTraits<TArray<T>>`  
_L479-486_
- L458 _public member_ `static constexpr bool bIsArrayOfStringType = false;`
- L459 _public member_ `static constexpr bool bIsArrayOfEnumType = false;`
- L460 _public member_ `static constexpr bool bIsArrayOfEnumAsByteType = false;`
- L481 _public typedef_ `using ElementType = T;`
- L483 _public member_ `static constexpr bool bIsArrayOfStringType = TIsStringType<ElementType>;`
- L484 _public member_ `static constexpr bool bIsArrayOfEnumType = TIsEnum<ElementType>::Value;`
- L485 _public member_ `static constexpr bool bIsArrayOfEnumAsByteType = TIsTEnumAsByte<ElementType>::Value;`

#### class `UE::Interchange::FAttributeStorage`  
`class FAttributeStorage`  
_L497-1060_
- desc: This class is a Key/Value storage inside a TArray64<uint8>. The keys are of type FAttributeKey, which is an FString. Each key is unique and has only one value. The value can be of any type contained in EAttributeTypes. @note The storage is multi-thread safe. It uses a mutex to lock the storage for every read/write operation. The hash of the storage is deterministic because it sorts the attributes before calculating the hash.
- L654 _public prototype_ `FAttributeStorage() = default;`
- L656 _public prototype_ `FAttributeStorage(const FAttributeStorage& Other);`
- L658 _public prototype_ `FAttributeStorage& operator=(const FAttributeStorage& Other);`
- L672 _public prototype_ `template<typename T, typename = std::enable_if_t<TIsNonEnumType<T>>> EAttributeStorageResult RegisterAttribute(const FAttributeKey& ElementAttributeKey, const T& DefaultValue, EAttributeProperty AttributeProperty = EAttributeProperty::None);` — Register an attribute in the storage. Return success if the attribute was properly added, or there is an existing attribute of the same type. Return an error otherwise. @Param ElementAttributeKey - the storage key (the path) of the attribute. @Param DefaultValue - the default value for the registered attribute. @note Possible errors: - Key exists with a different type. - Storage is corrupted.
- L676 _public function_ `template<typename E, typename = std::enable_if_t<TIsEnum<E>::Value>, int = 0> EAttributeStorageResult RegisterAttribute(const FAttributeKey& ElementAttributeKey, const E& DefaultValue, EAttributeProperty AttributeProperty = EAttributeProperty::None)` — Redirect enum instantiations to underlying type
- L684 _public function_ `template<typename B, typename = std::enable_if_t<TIsTEnumAsByte<B>::Value>, int = 0, int = 0> EAttributeStorageResult RegisterAttribute(const FAttributeKey& ElementAttributeKey, const B& DefaultValue, EAttributeProperty AttributeProperty = EAttributeProperty::None)` — Redirect TEnumAsByte instantiations to underlying type
- L692 _public function_ ``
- L715 _public prototype_ `EAttributeStorageResult UnregisterAttribute(const FAttributeKey& ElementAttributeKey);` — Remove an attribute from the storage. @param ElementAttributeKey - the storage key (the path) of the attribute to remove. @note Possible errors: - Key does not exist. - Internal storage structure removal error.
- L729 _public prototype_ `template<typename T, typename = std::enable_if_t<TIsNonEnumType<T>>> EAttributeStorageResult GetAttribute(const FAttributeKey& ElementAttributeKey, T& OutValue) const;` — Retrieve a copy of an attribute value. Return success if the attribute is added. @param ElementAttributeKey is the storage key (the path) of the attribute. @param OutValue the reference value where we copy of the attribute value. @note Possible errors - Key do not exist - Key exist with a different type - Key exist with a wrong size
- L733 _public function_ `template<typename E, typename = std::enable_if_t<TIsEnum<E>::Value>, int = 0> EAttributeStorageResult GetAttribute(const FAttributeKey& ElementAttributeKey, E& OutValue) const` — Redirect enum instantiations to underlying type
- L741 _public function_ `template<typename B, typename = std::enable_if_t<TIsTEnumAsByte<B>::Value>, int = 0, int = 0> EAttributeStorageResult GetAttribute(const FAttributeKey& ElementAttributeKey, B& OutValue) const` — Redirect TEnumAsByte instantiations to underlying type
- L749 _public function_ ``
- L770 _public prototype_ `template<typename T, typename = std::enable_if_t<TIsNonEnumType<T>>> TAttributeHandle<T> GetAttributeHandle(const FAttributeKey& ElementAttributeKey) const;` — Return an attribute handle for the specified attribute. This handle is a compile type check and is use to get and set the attribute value type. The function will assert if the key is missing or the type doesn't match the specified template type. @param ElementAttributeKey - the storage key (the path) of the attribute.
- L774 _public function_ `template<typename E, typename = std::enable_if_t<TIsEnum<E>::Value>, int = 0> TAttributeHandle<E> GetAttributeHandle(const FAttributeKey& ElementAttributeKey) const` — Redirect enum instantiations to underlying type
- L782 _public function_ `template<typename B, typename = std::enable_if_t<TIsTEnumAsByte<B>::Value>, int = 0, int = 0> TAttributeHandle<B> GetAttributeHandle(const FAttributeKey& ElementAttributeKey) const` — Redirect TEnumAsByte instantiations to underlying type
- L790 _public function_ ``
- L810 _public prototype_ `EAttributeTypes GetAttributeType(const FAttributeKey& ElementAttributeKey) const;` — Return the attribute type if the key exists, or None if the key is missing. @param ElementAttributeKey - the storage key (the path) of the attribute.
- L818 _public prototype_ `bool ContainAttribute(const FAttributeKey& ElementAttributeKey) const;` — Return true if the attribute key points to an existing attribute in the storage. Return false otherwise. @param ElementAttributeKey - the storage key (the path) of the attribute.
- L824 _public prototype_ `void GetAttributeKeys(TArray<FAttributeKey>& AttributeKeys) const;` — Retrieve the array of keys that can be used to iterate and do reflection on the storage content.
- L832 _public prototype_ `FGuid GetAttributeHash(const FAttributeKey& ElementAttributeKey) const;` — Return an FGuid built from the FSHA1 of the specified attribute data. If the attribute does not exist, return an empty FGUID. @param ElementAttributeKey - the storage key (the path) of the attribute.
- L841 _public prototype_ `bool GetAttributeHash(const FAttributeKey& ElementAttributeKey, FGuid& OutGuid) const;` — This function fills the OutGuid with the hash of the specified attribute. Return true if the attribute exists and the OutGuid was assigned, or false otherwise without touching the OutGuid. @param ElementAttributeKey - the storage key (the path) of the attribute. @param OutGuid - where we put the attribute hash.
- L850 _public prototype_ `FGuid GetStorageHash() const;` — Return an FGuid built from the FSHA1 of all the attribute data contained in the node. The data includes the UniqueID and the DisplayLabel. @note the attributes are sorted by key when building the FSHA1 data. The hash will be deterministic for the same data whatever the order we add the attributes.
- L862 _public prototype_ `static void CompareStorage(const FAttributeStorage& BaseStorage, const FAttributeStorage& VersionStorage, TArray<FAttributeKey>& RemovedAttributes, TArray<FAttributeKey>& AddedAttributes, TArray<FAttributeKey>& ModifiedAttributes);` — Compare two storage objects to know which properties were modified/added/removed. @param BaseStorage - The reference storage. @param VersionStorage - The storage with the changes. @param RemovedAttribute - All attributes that are in base storage but not in version storage. Contains keys that are only valid for the base storage. @param AddedAttributes - All attributes that are in version storage but not in base storage. Contains keys that are only valid for the version storage. @param ModifiedAttributes - All attributes that are in both storage but have a different hash (different value).
- L873 _public prototype_ `static void CopyStorageAttributes(const FAttributeStorage& SourceStorage, FAttributeStorage& DestinationStorage, const TArray<FAttributeKey>& AttributeKeys);` — Copy an array of attributes from the source storage to the destination storage. If the attribute already exists in the destination, the value will be updated. If a key does not exist in the source it will not be copied/created in the destination. @param SourceStorage - The storage source. @param DestinationStorage - The storage destination. @param AttributeKeys - All attributes that must be copied from the source to the destination.
- L884 _public prototype_ `static void CopyStorageAttributes(const FAttributeStorage& SourceStorage, FAttributeStorage& DestinationStorage, const TArray<TPair<FAttributeKey, FAttributeKey>>& SrcDestAttributeKeys);` — Copy an array of attributes from the source storage to the destination storage. If the attribute already exists in the destination, the value will be updated. If a key does not exist in the source it will not be copied/created in the destination. @param SourceStorage - The storage source. @param DestinationStorage - The storage destination. @param SrcDestAttributeKeys - All attributes that must be copied from the source to the destination, with a new key name.
- L891 _public function_ `inline float GetDefragRatio() const` — Return the defrag ratio. This ratio is used to know when we need to defrag the storage. @example - a ratio of 0.1f will defrag the storage if the memory lost is bigger then 10% of the storage allocation. Defrag is called when we remove an attribute or when we set the defrag ratio.
- L897 _public prototype_ `void SetDefragRatio(const float InDefragRatio);` — Set the defrag ratio. See GetDefragRatio() for the defrag documentation.
- L920 _public prototype_ `void Reserve(int64 NewAttributeCount, int64 NewStorageSize);` — Reserve the allocation table and the storage data. @param NewAttributeCount: The number of attributes we want to reserve. Passing a zero value does not reserve attribute count. @param NewStorageSize: The size of the storage all the new attributes will need. Passing a zero value do not reserve storage size.
- L952 _protected function_ `friend FArchive& operator<<(FArchive& Ar, FAttributeAllocationInfo& AttributeAllocationInfo)` — Serialization
- L989 _protected prototype_ `bool AreAllocationInfosEqual(const FAttributeKey& BaseKey, const FAttributeAllocationInfo& BaseInfo, const FAttributeStorage& VersionStorage, const FAttributeAllocationInfo& VersionInfo) const;` — Compare two allocation infos. Returns true if they are equal @param BaseKey - The reference key. @param BaseInfo - The reference allocation info. @param VersionStorage - The storage with the changes. @param VersionInfo - The allocation info to compare BaseInfo with.
- L1002 _protected prototype_ `template<typename T> EAttributeStorageResult SetAttribute(const FAttributeKey& ElementAttributeKey, const T& Value);` — Set an attribute value into the storage. Return success if the attribute was properly set. @param ElementAttributeKey is the storage key (the path) of the attribute @param Value is the value we want to add to the storage @note Possible errors - Key exist with a different type - Key exist with a wrong size
- L1005 _protected prototype_ `template<typename T> EAttributeStorageResult SetAttribute(FAttributeAllocationInfo* AttributeAllocationInfo, const T& Value);`
- L1008 _protected prototype_ `void DefragInternal();` — Defrag the storage by using memmove on the attribute store after a hole in the storage.
- L1012 _protected function_ `static uint64 GetValueSize(const T& Value)` — `UE_DEPRECATED(5.7, "No longer used.")`
- L1017 _protected prototype_ `const FStringView GetFStringViewAttributeFromStorage(const uint8* StorageData, const FAttributeAllocationInfo* AttributeAllocationInfo, int32 ElementIndex = 0) const;`
- L1020 _protected prototype_ `template<typename MultiSizeType> EAttributeStorageResult MultiSizeSetAttribute(FAttributeAllocationInfo* AttributeAllocationInfo, int32 TargetAllocationIndex, const MultiSizeType& Value, const void* SourceDataPtr, bool& bOutNeedsDefrag);`
- L1023 _protected prototype_ `template<typename ArrayType> EAttributeStorageResult GenericArrayGetAttribute(const FAttributeKey& ElementAttributeKey, ArrayType& OutValue) const;`
- L1028 _protected prototype_ `void UpdateAllocationInfoHash(FAttributeAllocationInfo& AllocationInfo);`
- L1030 _protected prototype_ `void UpdateAllocationCount();`
- L1033 _protected member_ `TMap<FAttributeKey, FAttributeAllocationInfo> AttributeAllocationTable;` — The attribute allocation table is use to index the attributes into the storage.
- L1036 _protected member_ `TArray64<uint8> AttributeStorage;` — The storage of the data point by the attribute allocation table
- L1042 _protected member_ `uint64 FragmentedMemoryCost = 0;` — The total size of the fragmented holes in the AttributeStorage (memory waste). A Hole is create each time we remove an attribute.
- L1048 _protected member_ `float DefragRatio = 0.1f;` — if FragmentedMemoryCost > AttributeStorage.Num*DefragRatio then defrag. This is use whenever we remove attribute or change DefragRatio value.
- L1054 _protected member_ `uint32 AllocationCount = 0;` — Used to help with the debug visualizers (on Unreal.natvis), because now that we support multiple allocations per attribute it is no longer trivial to compute the total number of allocations
- L1059 _protected member_ `mutable FCriticalSection StorageMutex;` — Mutex use when accessing or modifying the storage

#### class `UE::Interchange::FAttributeStorage::TAttributeHandle`  
`template<typename T> class TAttributeHandle<T, std::enable_if_t<TIsNonEnumType<T>>>`  
_L507-530_
- desc: Class to get/set an attribute of the storage.
- L510 _public prototype_ `TAttributeHandle();`
- L515 _public prototype_ `bool IsValid() const;` — Return true if the storage contains a valid attribute key, or false otherwise.
- L517 _public prototype_ `EAttributeStorageResult Get(T& Value) const;`
- L519 _public prototype_ `EAttributeStorageResult Set(const T& Value);`
- L521 _public prototype_ `const FAttributeKey& GetKey() const;`
- L524 _protected member_ `class FAttributeStorage* AttributeStorage;`
- L525 _protected member_ `FAttributeKey Key;`
- L527 _protected prototype_ `TAttributeHandle(const FAttributeKey& InKey, const FAttributeStorage* InAttributeStorage);`
- L538 _public typedef_ `using UnderlyingType = std::underlying_type_t<E>;`
- L539 _public typedef_ `using Base = TAttributeHandle<UnderlyingType>;`
- L543 _public function_ `explicit TAttributeHandle(const TAttributeHandle<UnderlyingType>& Other) : TAttributeHandle(Other.Key, Other.AttributeStorage)`
- L550 _public function_ `EAttributeStorageResult Get(E& Value) const` — Note: Since we derive TAttributeHandle<std::underlying_type_t<E>> we also get the base class overloads for free, and can Get()/Set() with the underlying type directly!
- L555 _public function_ `EAttributeStorageResult Set(const E& Value)`
- L570 _public typedef_ `using UnderlyingType = uint8;`
- L580 _public function_ `EAttributeStorageResult Get(B& Value) const`
- L585 _public function_ `EAttributeStorageResult Set(const B& Value)`
- L600 _public typedef_ `using UnderlyingType = std::underlying_type_t<typename T::ElementType>;`
- L601 _public typedef_ `using Base = TAttributeHandle<TArray<UnderlyingType>>;`
- L605 _public function_ `explicit TAttributeHandle(const TAttributeHandle<TArray<UnderlyingType>>& Other) : TAttributeHandle(Other.Key, Other.AttributeStorage)`
- L610 _public function_ `EAttributeStorageResult Get(T& Value) const`
- L615 _public function_ `EAttributeStorageResult Set(const T& Value)`

#### class `UE::Interchange::FAttributeStorage::TAttributeHandle`  
`template<typename E> class TAttributeHandle<E, std::enable_if_t<TIsEnum<E>::Value>> : public TAttributeHandle<std::underlying_type_t<E>>`  
_L534-562_
- inherits: `TAttributeHandle<std::underlying_type_t<E>>`
- desc: Redirect enum instantiations to underlying type
- L510 _public prototype_ `TAttributeHandle();`
- L515 _public prototype_ `bool IsValid() const;` — Return true if the storage contains a valid attribute key, or false otherwise.
- L517 _public prototype_ `EAttributeStorageResult Get(T& Value) const;`
- L519 _public prototype_ `EAttributeStorageResult Set(const T& Value);`
- L521 _public prototype_ `const FAttributeKey& GetKey() const;`
- L524 _protected member_ `class FAttributeStorage* AttributeStorage;`
- L525 _protected member_ `FAttributeKey Key;`
- L527 _protected prototype_ `TAttributeHandle(const FAttributeKey& InKey, const FAttributeStorage* InAttributeStorage);`
- L538 _public typedef_ `using UnderlyingType = std::underlying_type_t<E>;`
- L539 _public typedef_ `using Base = TAttributeHandle<UnderlyingType>;`
- L543 _public function_ `explicit TAttributeHandle(const TAttributeHandle<UnderlyingType>& Other) : TAttributeHandle(Other.Key, Other.AttributeStorage)`
- L550 _public function_ `EAttributeStorageResult Get(E& Value) const` — Note: Since we derive TAttributeHandle<std::underlying_type_t<E>> we also get the base class overloads for free, and can Get()/Set() with the underlying type directly!
- L555 _public function_ `EAttributeStorageResult Set(const E& Value)`
- L570 _public typedef_ `using UnderlyingType = uint8;`
- L580 _public function_ `EAttributeStorageResult Get(B& Value) const`
- L585 _public function_ `EAttributeStorageResult Set(const B& Value)`
- L600 _public typedef_ `using UnderlyingType = std::underlying_type_t<typename T::ElementType>;`
- L601 _public typedef_ `using Base = TAttributeHandle<TArray<UnderlyingType>>;`
- L605 _public function_ `explicit TAttributeHandle(const TAttributeHandle<TArray<UnderlyingType>>& Other) : TAttributeHandle(Other.Key, Other.AttributeStorage)`
- L610 _public function_ `EAttributeStorageResult Get(T& Value) const`
- L615 _public function_ `EAttributeStorageResult Set(const T& Value)`

#### class `UE::Interchange::FAttributeStorage::TAttributeHandle`  
`template<typename B> class TAttributeHandle<B, std::enable_if_t<TIsTEnumAsByte<B>::Value>> : public TAttributeHandle<uint8>`  
_L566-592_
- inherits: `TAttributeHandle<uint8>`
- desc: Redirect TEnumAsByte<T> instantiations to uint8
- L510 _public prototype_ `TAttributeHandle();`
- L515 _public prototype_ `bool IsValid() const;` — Return true if the storage contains a valid attribute key, or false otherwise.
- L517 _public prototype_ `EAttributeStorageResult Get(T& Value) const;`
- L519 _public prototype_ `EAttributeStorageResult Set(const T& Value);`
- L521 _public prototype_ `const FAttributeKey& GetKey() const;`
- L524 _protected member_ `class FAttributeStorage* AttributeStorage;`
- L525 _protected member_ `FAttributeKey Key;`
- L527 _protected prototype_ `TAttributeHandle(const FAttributeKey& InKey, const FAttributeStorage* InAttributeStorage);`
- L538 _public typedef_ `using UnderlyingType = std::underlying_type_t<E>;`
- L539 _public typedef_ `using Base = TAttributeHandle<UnderlyingType>;`
- L543 _public function_ `explicit TAttributeHandle(const TAttributeHandle<UnderlyingType>& Other) : TAttributeHandle(Other.Key, Other.AttributeStorage)`
- L550 _public function_ `EAttributeStorageResult Get(E& Value) const` — Note: Since we derive TAttributeHandle<std::underlying_type_t<E>> we also get the base class overloads for free, and can Get()/Set() with the underlying type directly!
- L555 _public function_ `EAttributeStorageResult Set(const E& Value)`
- L570 _public typedef_ `using UnderlyingType = uint8;`
- L580 _public function_ `EAttributeStorageResult Get(B& Value) const`
- L585 _public function_ `EAttributeStorageResult Set(const B& Value)`
- L600 _public typedef_ `using UnderlyingType = std::underlying_type_t<typename T::ElementType>;`
- L601 _public typedef_ `using Base = TAttributeHandle<TArray<UnderlyingType>>;`
- L605 _public function_ `explicit TAttributeHandle(const TAttributeHandle<TArray<UnderlyingType>>& Other) : TAttributeHandle(Other.Key, Other.AttributeStorage)`
- L610 _public function_ `EAttributeStorageResult Get(T& Value) const`
- L615 _public function_ `EAttributeStorageResult Set(const T& Value)`

#### class `UE::Interchange::FAttributeStorage::TAttributeHandle`  
``  
_L596-622_
- inherits: `TAttributeHandle<TArray<std::underlying_type_t<typenameT::ElementType>>>`
- L510 _public prototype_ `TAttributeHandle();`
- L515 _public prototype_ `bool IsValid() const;` — Return true if the storage contains a valid attribute key, or false otherwise.
- L517 _public prototype_ `EAttributeStorageResult Get(T& Value) const;`
- L519 _public prototype_ `EAttributeStorageResult Set(const T& Value);`
- L521 _public prototype_ `const FAttributeKey& GetKey() const;`
- L524 _protected member_ `class FAttributeStorage* AttributeStorage;`
- L525 _protected member_ `FAttributeKey Key;`
- L527 _protected prototype_ `TAttributeHandle(const FAttributeKey& InKey, const FAttributeStorage* InAttributeStorage);`
- L538 _public typedef_ `using UnderlyingType = std::underlying_type_t<E>;`
- L539 _public typedef_ `using Base = TAttributeHandle<UnderlyingType>;`
- L543 _public function_ `explicit TAttributeHandle(const TAttributeHandle<UnderlyingType>& Other) : TAttributeHandle(Other.Key, Other.AttributeStorage)`
- L550 _public function_ `EAttributeStorageResult Get(E& Value) const` — Note: Since we derive TAttributeHandle<std::underlying_type_t<E>> we also get the base class overloads for free, and can Get()/Set() with the underlying type directly!
- L555 _public function_ `EAttributeStorageResult Set(const E& Value)`
- L570 _public typedef_ `using UnderlyingType = uint8;`
- L580 _public function_ `EAttributeStorageResult Get(B& Value) const`
- L585 _public function_ `EAttributeStorageResult Set(const B& Value)`
- L600 _public typedef_ `using UnderlyingType = std::underlying_type_t<typename T::ElementType>;`
- L601 _public typedef_ `using Base = TAttributeHandle<TArray<UnderlyingType>>;`
- L605 _public function_ `explicit TAttributeHandle(const TAttributeHandle<TArray<UnderlyingType>>& Other) : TAttributeHandle(Other.Key, Other.AttributeStorage)`
- L610 _public function_ `EAttributeStorageResult Get(T& Value) const`
- L615 _public function_ `EAttributeStorageResult Set(const T& Value)`

#### class `UE::Interchange::FAttributeStorage::TAttributeHandle`  
``  
_L626-652_
- inherits: `TAttributeHandle<TArray<uint8>>`
- L510 _public prototype_ `TAttributeHandle();`
- L515 _public prototype_ `bool IsValid() const;` — Return true if the storage contains a valid attribute key, or false otherwise.
- L517 _public prototype_ `EAttributeStorageResult Get(T& Value) const;`
- L519 _public prototype_ `EAttributeStorageResult Set(const T& Value);`
- L521 _public prototype_ `const FAttributeKey& GetKey() const;`
- L524 _protected member_ `class FAttributeStorage* AttributeStorage;`
- L525 _protected member_ `FAttributeKey Key;`
- L527 _protected prototype_ `TAttributeHandle(const FAttributeKey& InKey, const FAttributeStorage* InAttributeStorage);`
- L538 _public typedef_ `using UnderlyingType = std::underlying_type_t<E>;`
- L539 _public typedef_ `using Base = TAttributeHandle<UnderlyingType>;`
- L543 _public function_ `explicit TAttributeHandle(const TAttributeHandle<UnderlyingType>& Other) : TAttributeHandle(Other.Key, Other.AttributeStorage)`
- L550 _public function_ `EAttributeStorageResult Get(E& Value) const` — Note: Since we derive TAttributeHandle<std::underlying_type_t<E>> we also get the base class overloads for free, and can Get()/Set() with the underlying type directly!
- L555 _public function_ `EAttributeStorageResult Set(const E& Value)`
- L570 _public typedef_ `using UnderlyingType = uint8;`
- L580 _public function_ `EAttributeStorageResult Get(B& Value) const`
- L585 _public function_ `EAttributeStorageResult Set(const B& Value)`
- L600 _public typedef_ `using UnderlyingType = std::underlying_type_t<typename T::ElementType>;`
- L601 _public typedef_ `using Base = TAttributeHandle<TArray<UnderlyingType>>;`
- L605 _public function_ `explicit TAttributeHandle(const TAttributeHandle<TArray<UnderlyingType>>& Other) : TAttributeHandle(Other.Key, Other.AttributeStorage)`
- L610 _public function_ `EAttributeStorageResult Get(T& Value) const`
- L615 _public function_ `EAttributeStorageResult Set(const T& Value)`

#### struct `UE::Interchange::FAttributeStorage::FAttributeAllocationInfo`  
`struct FAttributeAllocationInfo`  
_L924-978_
- desc: Structure used to hold the attribute information stored in the attribute allocation table.
- L928 _public function_ `FAttributeAllocationInfo()` — clang fix for std::is_default_constructible_v returning false in inlined code of outer class
- L931 _public member_ `TArray<uint64> Offsets;` — The offsets of our allocations in the storage
- L933 _public member_ `TArray<uint64> Sizes;` — The sizes of our allocations in the storage, in bytes
- L935 _public member_ `EAttributeTypes Type = EAttributeTypes::None;` — The real type of the attribute
- L937 _public member_ `EAttributeProperty Property = EAttributeProperty::None;` — The attribute properties
- L939 _public member_ `FGuid Hash = FGuid();` — 128 bit Attribute hash
- L941 _public function_ `bool operator==(const FAttributeAllocationInfo& Other) const`

#### Free symbols / members of external scopes

- L51 _namespace_ `namespace UE`
- L53 _namespace_ `namespace Interchange` (scope `UE`)
- L55 _namespace_ `namespace Private` (scope `UE::Interchange`)
- L168 _function_ `friend FArchive& operator<<(FArchive& Ar, FAttributeKey& AttributeKey)` (scope `UE::Interchange`)
- L186 _function_ `inline uint32 GetTypeHash(const FAttributeKey& AttributeKey)` (scope `UE::Interchange`)
- L323 _prototype_ `FString AttributeTypeToString(EAttributeTypes AttributeType);` (scope `UE::Interchange`) — Return the FString for the specified AttributeType.
- L329 _prototype_ `EAttributeTypes StringToAttributeType(const FString& AttributeTypeString);` (scope `UE::Interchange`) — Return the AttributeType for the specified FString, or return EAttributeTypes::None if the string does not match any supported attribute type.
- L347 _prototype_ `template<typename ValueType> FString AttributeValueToString(const ValueType& Value);` (scope `UE::Interchange`)
- L381 _function_ `ENUM_CLASS_FLAGS(EAttributeStorageResult) inline bool HasAttributeStorageResult(const EAttributeStorageResult Result, const EAttributeStorageResult RefResult)` (scope `UE::Interchange`)
- L396 _function_ `inline bool IsAttributeStorageResultSuccess(const EAttributeStorageResult Result)` (scope `UE::Interchange`) — Helper function to determine if the storage result is success. @return true if the result contains Operation_Success.
- L407 _prototype_ `void LogAttributeStorageErrors(const EAttributeStorageResult Result, const FString OperationName, const FAttributeKey AttributeKey );` (scope `UE::Interchange`) — Helper function to transform an operation result into a LOG. @param Result - The result we want to output a log for. @param OperationName - The operation name that ended up with the specified result. @param AttributeKey - The attribute we applied the operation to.
- L420 _function_ `ENUM_CLASS_FLAGS(EAttributeStorageAddOptions) inline bool HasAttributeStorageAddOption(const EAttributeStorageAddOptions Options, const EAttributeStorageAddOptions RefOptions)` (scope `UE::Interchange`)
- L439 _function_ `ENUM_CLASS_FLAGS(EAttributeProperty) inline bool HasAttributeProperty(const EAttributeProperty PropertyA, const EAttributeProperty PropertyB)` (scope `UE::Interchange`)
- L464 _variable_ `template<typename T> inline constexpr bool TIsStringType = std::is_same_v<T, FString> || std::is_same_v<T, FName> || std::is_same_v<T, FSoftObjectPath>;` (scope `UE::Interchange`)
- L467 _variable_ `template<typename T> inline constexpr bool TIsArrayOfStringType = TAttributeStorageTypeTraits<T>::bIsArrayOfStringType;` (scope `UE::Interchange`)
- L470 _variable_ `template<typename T> inline constexpr bool TIsArrayOfEnumType = TAttributeStorageTypeTraits<T>::bIsArrayOfEnumType;` (scope `UE::Interchange`)
- L473 _variable_ `template<typename T> inline constexpr bool TIsArrayOfEnumAsByteType = TAttributeStorageTypeTraits<T>::bIsArrayOfEnumAsByteType;` (scope `UE::Interchange`)
- L476 _variable_ `template<typename T> inline constexpr bool TIsNonEnumType = !TIsEnum<T>::Value && !TIsTEnumAsByte<T>::Value && !TIsArrayOfEnumType<T> && !TIsArrayOfEnumAsByteType<T>;` (scope `UE::Interchange`)
- L678 _typedef_ `using UnderlyingType = std::underlying_type_t<E>;` (scope `UE::Interchange::FAttributeStorage::RegisterAttribute`)
- L686 _typedef_ `using UnderlyingType = uint8;` (scope `UE::Interchange::FAttributeStorage::RegisterAttribute`)
- L694 _typedef_ `using UnderlyingType = std::underlying_type_t<typename T::ElementType>;` (scope `UE::Interchange::FAttributeStorage::RegisterAttribute`)
- L735 _typedef_ `using UnderlyingType = std::underlying_type_t<E>;` (scope `UE::Interchange::FAttributeStorage::GetAttribute`)
- L743 _typedef_ `using UnderlyingType = uint8;` (scope `UE::Interchange::FAttributeStorage::GetAttribute`)
- L751 _typedef_ `using UnderlyingType = std::underlying_type_t<typename ArrayOfE::ElementType>;` (scope `UE::Interchange::FAttributeStorage::GetAttribute`)
- L776 _typedef_ `using UnderlyingType = std::underlying_type_t<E>;` (scope `UE::Interchange::FAttributeStorage::GetAttributeHandle`)
- L784 _typedef_ `using UnderlyingType = uint8;` (scope `UE::Interchange::FAttributeStorage::GetAttributeHandle`)
- L792 _typedef_ `using UnderlyingType = std::underlying_type_t<typename ArrayOfE::ElementType>;` (scope `UE::Interchange::FAttributeStorage::GetAttributeHandle`)
- L899 _function_ `friend FArchive& operator<<(FArchive& Ar, FAttributeStorage& Storage)` (scope `UE::Interchange`)

### `Source/Runtime/Interchange/Core/Public/Types/InterchangeLODMeshData.h` (Public)


#### struct `FInterchangeLODMeshData`  
`struct FInterchangeLODMeshData`  
_L14-74_
- reflection: `USTRUCT(BlueprintType)`
- desc: This helper struct is placed here, so that we can implement support for it in AttributeStorage.h
- L21 _public member_ `FString MeshUid;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | LOD | MeshData")`
- L27 _public member_ `FString SceneNodeName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | LOD | MeshData")` — Used for Rigid to RiggedMesh conversions to identify the bone targeting given Mesh.
- L30 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | LOD | MeshData")`
- L37 _public member_ `FTransform GeometricTransform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interchange | LOD | MeshData")` — Specifically and only used for re-skinning meshes to T0. GeometricTransform is already part of the Transform, however we need the separated out GeometricTransform for re-skinning to T0 calculations.
- L39 _public function_ `FInterchangeLODMeshData()`
- L43 _public function_ `FInterchangeLODMeshData( const FString& InMeshUid) : MeshUid(InMeshUid)`
- L49 _public function_ `FInterchangeLODMeshData( const FString& InMeshUid, const FTransform& InTransform) : MeshUid(InMeshUid) , Transform(InTransform)`
- L57 _public function_ `FInterchangeLODMeshData( const FString& InMeshUid, const FString& InSceneNodeName, const FTransform& InTransform, const FTransform& InGeometricTransform) : MeshUid(InMeshUid) , SceneNodeName(InSceneNodeName) , Transform(InTransform) , GeometricTransform(InGeometricTransform)`
- L67 _public function_ `FString ToString() const`
- L73 _public function_ `static constexpr int32 NumberOfAttributes()` — 2 FString, 2 FTransform
