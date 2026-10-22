# Plugins / NaniteDisplacedMeshEditor

- module root: `Plugins/Experimental/NaniteDisplacedMesh/Source/NaniteDisplacedMeshEditor`
- headers: 6; symbols: 131
- symbol kinds: class=6, delegate=2, enum=1, enumerator=4, externvar=1, macro=3, member=41, prototype=69, struct=3, typedef=1
- PrivateDependencyModuleNames: AssetRegistry, AssetTools, Core, CoreUObject, DeveloperToolSettings, EditorFramework, EditorStyle, Engine, Json, Projects, PropertyEditor, RHI, Slate, SlateCore, SourceControl, TargetPlatform, UnrealEd
- PrivateIncludePathModuleNames: DerivedDataCache
- PublicDependencyModuleNames: EditorSubsystem, NaniteDisplacedMesh

### `Plugins/Experimental/NaniteDisplacedMesh/Source/NaniteDisplacedMeshEditor/Private/GenerateNaniteDisplacedMeshCommandlet.h` (Private)


#### class `UGenerateNaniteDisplacedMeshCommandlet`  
`class UGenerateNaniteDisplacedMeshCommandlet : public UCommandlet`  
_L25-63_
- reflection: `UCLASS()`
- inherits: `UCommandlet`
- desc: Commandlet to help keeping up to date generated nanite displacement mesh assets Iterate all the levels and keep track of the linked mesh used.
- L31 _public prototype_ `static bool IsRunning();`
- L34 _public prototype_ `virtual int32 Main(const FString& CmdLineParams) override;`
- L39 _private prototype_ `UNaniteDisplacedMesh* OnLinkDisplacedMesh(UNaniteDisplacedMesh* ExistingDisplacedMesh, FValidatedNaniteDisplacedMeshParams&& InParameters, const FNaniteDisplacedMeshLinkParameters& InLinkParameters);`
- L40 _private prototype_ `void LoadLevel(const FAssetData& AssetData);`
- L41 _private prototype_ `void SavePackages();`
- L42 _private prototype_ `void FreeMemoryIfNeeded();`
- L43 _private prototype_ `bool ShouldFreeMemory() const;`
- L44 _private prototype_ `static TSet<FString> GetPackagesInFolders(const TSet<FString>& Folders, const FString& NamePrefix);`
- L46 _private member_ `TSet<FString> LinkedPackageNames;`
- L47 _private member_ `TSet<FString> LinkedPackageFolders;`
- L48 _private member_ `TSet<FString> AddedPackageNames;`
- L49 _private member_ `TSet<FString> AddedOtherPackages;`
- L50 _private member_ `bool bSaveModifiedActor = false;`
- L52 _private member_ `TSet<UPackage*> PackagesToSave;`
- L54 _private member_ `FARCompiledFilter PreCompiledActorsFilter;`
- L57 _private member_ `uint64 MemoryMinFreeVirtual = 8192;` — Soft limit for when the garbage collector should be kicked (it use the same settings as the cook and will load these if found)
- L58 _private member_ `uint64 MemoryMaxUsedVirtual= 98304;`
- L59 _private member_ `uint64 MemoryMinFreePhysical= 8192;`
- L60 _private member_ `uint64 MemoryMaxUsedPhysical= 0;`
- L62 _private member_ `TSharedPtr<class FPathPermissionList> WritableFoldersPermission;`

### `Plugins/Experimental/NaniteDisplacedMesh/Source/NaniteDisplacedMeshEditor/Private/NaniteDisplacedMeshEditorModule.h` (Private)


#### class `FNaniteDisplacedMeshEditorModule`  
`class FNaniteDisplacedMeshEditorModule : public IModuleInterface`  
_L20-45_
- inherits: `IModuleInterface`
- L24 _public prototype_ `virtual void StartupModule() override;`
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L27 _public prototype_ `static FNaniteDisplacedMeshEditorModule& GetModule();`
- L29 _public prototype_ `UPackage* GetNaniteDisplacementMeshTransientPackage() const;`
- L32 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(UNaniteDisplacedMesh*, FOnLinkDisplacedMesh, const FNaniteDisplacedMeshParams& , const FString& , const ELinkDisplacedMeshAssetSetting& );` — `UE_DEPRECATED(5.6, "Use FOnOverrideNaniteDisplacedMeshLink Instead")`
- L35 _public member_ `FOnLinkDisplacedMesh OnLinkDisplacedMeshOverride;` — `UE_DEPRECATED(5.6, "Use OverrideNaniteDisplacedMeshLink Instead")`
- L39 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(UNaniteDisplacedMesh*, FOOnOverideDisplacedMeshLink, UNaniteDisplacedMesh* , FValidatedNaniteDisplacedMeshParams&& , const FNaniteDisplacedMeshLinkParameters& );` — Invoked when a nanite displaced mesh is linked
- L40 _public member_ `FOOnOverideDisplacedMeshLink OverrideNaniteDisplacedMeshLink;`
- L43 _private member_ `FAssetTypeActions_NaniteDisplacedMesh* NaniteDisplacedMeshAssetActions;`
- L44 _private member_ `TStrongObjectPtr<UPackage> NaniteDisplacedMeshTransientPackage;`

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(UNaniteDisplacedMesh*, FOnLinkDisplacedMesh, const FNaniteDisplacedMeshParams& , const FString& , const ELinkDisplacedMeshAssetSetting& );`
- L39 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(UNaniteDisplacedMesh*, FOOnOverideDisplacedMeshLink, UNaniteDisplacedMesh* , FValidatedNaniteDisplacedMeshParams&& , const FNaniteDisplacedMeshLinkParameters& );` — Invoked when a nanite displaced mesh is linked

### `Plugins/Experimental/NaniteDisplacedMesh/Source/NaniteDisplacedMeshEditor/Public/AssetTypeActions_NaniteDisplacedMesh.h` (Public)


#### class `FAssetTypeActions_NaniteDisplacedMesh`  
`class FAssetTypeActions_NaniteDisplacedMesh : public FAssetTypeActions_Base`  
_L7-17_
- inherits: `FAssetTypeActions_Base`
- L10 _public prototype_ `virtual FText GetName() const override;`
- L11 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L12 _public prototype_ `virtual FColor GetTypeColor() const override;`
- L13 _public prototype_ `virtual void GetActions(const TArray<UObject*>& InObjects, class FMenuBuilder& MenuBuilder) override;`
- L14 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L15 _public prototype_ `virtual uint32 GetCategories() override;`
- L16 _public prototype_ `virtual FText GetAssetDescription(const struct FAssetData& AssetData) const override;`

### `Plugins/Experimental/NaniteDisplacedMesh/Source/NaniteDisplacedMeshEditor/Public/GeneratedNaniteDisplacedMeshEditorSubsystem.h` (Public)


#### class `UGeneratedNaniteDisplacedMeshEditorSubsystem`  
`class UGeneratedNaniteDisplacedMeshEditorSubsystem : public UEditorSubsystem, public FUObjectArray::FUObjectDeleteListener`  
_L24-131_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem,FUObjectArray::FUObjectDeleteListener`
- L32 _public typedef_ `using FOnActorDependencyChanged = TUniqueFunction<void (AActor* , UObject* , FPropertyChangedEvent& )>;`
- L45 _public prototype_ `void RegisterClassHandler(const TSubclassOf<AActor>& ActorClass, FActorClassHandler&& ActorClassHandler);` — Tell the system what to callback when a dependency was changed for an actor the specified type.
- L46 _public prototype_ `void UnregisterClassHandler(const TSubclassOf<AActor>& ActorClass);`
- L52 _public prototype_ `void UpdateActorDependencies(AActor* Actor, TArray<TObjectKey<UObject>>&& Dependencies);` — Tell the system to track for change to the dependencies of the actor. The system will invoke a callback after a change to any asset that this actor has a dependency.
- L57 _public prototype_ `void RemoveActor(const AActor* ActorToRemove);` — Tell the system to stop tracking stuff for this actor.
- L60 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L61 _public prototype_ `virtual void Deinitialize() override;`
- L64 _private prototype_ `void OnObjectPreEditChange(UObject* Object, const class FEditPropertyChain& EditPropertyChain);`
- L65 _private prototype_ `void OnObjectPostEditChange(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);`
- L66 _private prototype_ `void OnObjectsReplaced(const TMap<UObject*, UObject*>& ReplacementMap);`
- L67 _private prototype_ `void OnLevelActorDeleted(AActor* Actor);`
- L69 _private prototype_ `void OnAssetPreImport(UFactory* InFactory, UClass* InClass, UObject* InParent, const FName& Name, const TCHAR* Type);`
- L70 _private prototype_ `void OnAssetPostImport(UFactory* InFactory, UObject* InCreatedObject);`
- L72 _private prototype_ `bool CanObjectBeTracked(UObject* InObject);`
- L73 _private prototype_ `bool RemoveActor(TObjectKey<AActor> InActorToRemove, uint32 InWeakActorHash);`
- L75 _private prototype_ `FActorClassHandler* FindClassHandler(UClass* Class);`
- L76 _private prototype_ `bool ShouldCallback(UClass* AssetClass, const FActorClassHandler& ClassHandler, const FPropertyChangedEvent& PropertyChangedEvent);`
- L78 _private prototype_ `void UpdateDisplacedMeshesDueToAssetChanges(UObject* Asset);`
- L79 _private prototype_ `void UpdateDisplacementMeshToAssets(UNaniteDisplacedMesh* DisplacementMesh);`
- L80 _private prototype_ `void WaitForDependentDisplacedMeshesToFinishTheirCompilation(UObject* AssetAboutToChange);`
- L84 _private member_ `TMap<UClass*, FActorClassHandler> ActorClassHandlers;` — Track the change to asset for actors
- L85 _private member_ `TMap<TObjectKey<AActor>, TArray<TObjectKey<UObject>>> ActorsToDependencies;`
- L86 _private member_ `TMap<TObjectKey<UObject>, TSet<TObjectKey<AActor>>> DependenciesToActors;`
- L108 _private member_ `FBidirectionalAssetsAndDisplacementMeshMap MeshesAndAssetsReimportTracking;`
- L110 _private member_ `bool bIsEngineCollectingGarbage = false;`
- L112 _private member_ `FDelegateHandle OnPreEditChangeHandle;`
- L113 _private member_ `FDelegateHandle OnPostEditChangeHandle;`
- L114 _private member_ `FDelegateHandle OnObjectsReplacedHandle;`
- L115 _private member_ `FDelegateHandle OnLevelActorDeletedHandle;`
- L116 _private member_ `FDelegateHandle OnAssetReimportHandle;`
- L117 _private member_ `FDelegateHandle OnAssetPostImportHandle;`
- L118 _private member_ `FDelegateHandle OnAssetPreImportHandle;`
- L119 _private member_ `FDelegateHandle OnInMemoryAssetDeletedHandle;`
- L120 _private member_ `FDelegateHandle OnPreGarbageCollectHandle;`
- L121 _private member_ `FDelegateHandle OnPostGarbageCollectHandle;`
- L125 _private prototype_ `virtual void NotifyUObjectDeleted(const UObjectBase *Object, int32 Index) override;`
- L126 _private prototype_ `virtual void OnUObjectArrayShutdown() override;`
- L127 _private prototype_ `virtual SIZE_T GetAllocatedSize() const override;`
- L130 _private prototype_ `void UpdateIsEngineCollectingGarbage(bool bIsCollectingGarbage);`

#### struct `UGeneratedNaniteDisplacedMeshEditorSubsystem::FActorClassHandler`  
`struct FActorClassHandler`  
_L34-40_
- L36 _public member_ `FOnActorDependencyChanged Callback;`
- L39 _public member_ `TMap<UClass*, TSet<FProperty*>> PropertiesToWatchPerAssetType;` — If empty it will accept any change

#### struct `UGeneratedNaniteDisplacedMeshEditorSubsystem::FBidirectionalAssetsAndDisplacementMeshMap`  
`struct FBidirectionalAssetsAndDisplacementMeshMap`  
_L89-106_
- desc: Track re import of asset for the displaced meshes
- L91 _public prototype_ `void RemoveDisplacedMesh(UNaniteDisplacedMesh* DisplacedMesh);`
- L92 _public prototype_ `void RemoveAssetForReimportTracking(UObject* Object);`
- L94 _public prototype_ `void AddDisplacedMesh(UNaniteDisplacedMesh* Mesh, TSet<UObject*>&& AssetsToTrack);`
- L96 _public prototype_ `const TArray<TObjectKey<UNaniteDisplacedMesh>> GetMeshesThatUseAsset(UObject* Object);`
- L97 _public prototype_ `const TArray<TObjectKey<UNaniteDisplacedMesh>> GetMeshesThatUseAsset(UObject* Object, uint32 Hash);`
- L99 _public prototype_ `void ReplaceObject(UObject* OldObject, UObject* NewObject);`
- L101 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L104 _private member_ `TMap<UNaniteDisplacedMesh*, TSet<UObject*>> MeshToAssets;`
- L105 _private member_ `TMap<UObject*, TSet<UNaniteDisplacedMesh*>> AssetToMeshes;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API NANITEDISPLACEDMESHEDITOR_API`

### `Plugins/Experimental/NaniteDisplacedMesh/Source/NaniteDisplacedMeshEditor/Public/NaniteDisplacedMeshCustomization.h` (Public)


#### class `FNaniteDisplacedMeshDetails`  
`class FNaniteDisplacedMeshDetails : public IDetailCustomization`  
_L19-41_
- inherits: `IDetailCustomization`
- desc: Customization of the details view for the NaniteDisplacedMesh
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L29 _private prototype_ `FReply ApplyNaniteDisplacedMeshParams();`
- L31 _private prototype_ `bool IsApplyNaniteDisplacedMeshParamsNeeded() const;`
- L33 _private prototype_ `bool DoesParamDifferFromOriginalValue(TSharedPtr<IPropertyHandle> Handle, int32 ObjectIndex);`
- L35 _private prototype_ `void ResetParamToOriginalValue(TSharedPtr<IPropertyHandle> Handle, int32 ObjectIndex);`
- L37 _private prototype_ `TAttribute<bool> GetCanEditAttribute(int32 ObjectIndex);`
- L40 _private member_ `TArray<TPair<TWeakObjectPtr<UNaniteDisplacedMesh>, FNaniteDisplacedMeshParams>> CustomizedPairs;`

### `Plugins/Experimental/NaniteDisplacedMesh/Source/NaniteDisplacedMeshEditor/Public/NaniteDisplacedMeshFactory.h` (Public)


#### class `UNaniteDisplacedMeshFactory`  
`class UNaniteDisplacedMeshFactory : public UFactory`  
_L17-29_
- reflection: `UCLASS(MinimalAPI, hidecategories = Object)`
- inherits: `UFactory`
- L22 _public prototype_ `UNaniteDisplacedMeshFactory();`
- L25 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L26 _public prototype_ `static UNaniteDisplacedMesh* StaticFactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn);`
- L28 _public member_ `bool bCreateReadOnlyAsset = false;`

#### enum `ELinkDisplacedMeshAssetSetting`  
`enum class ELinkDisplacedMeshAssetSetting : uint8`  
_L31-37_
- L33 _public enumerator_ `LinkAgainstPersistentAsset`
- L34 _public enumerator_ `CanLinkAgainstPersistentAndTransientAsset`
- L35 _public enumerator_ `LinkAgainstTransientAsset`
- L36 _public enumerator_ `LinkAgainstExistingPersistentAsset`

#### struct `FNaniteDisplacedMeshLinkParameters`  
`struct FNaniteDisplacedMeshLinkParameters`  
_L39-45_
- L41 _public member_ `FStringView DisplacedMeshFolder;`
- L42 _public member_ `ELinkDisplacedMeshAssetSetting LinkDisplacedMeshAssetSetting = ELinkDisplacedMeshAssetSetting::LinkAgainstPersistentAsset;`
- L43 _public member_ `bool* bOutCreatedNewMesh = nullptr;`
- L44 _public member_ `bool bForcePackageToBePublic = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API NANITEDISPLACEDMESHEDITOR_API`
- L14 _macro_ `#define NANITE_DISPLACED_MESH_ID_VERSION 3`
- L48 _prototype_ `UNaniteDisplacedMesh* LinkDisplacedMeshAsset( UNaniteDisplacedMesh* ExistingDisplacedMesh, const FNaniteDisplacedMeshParams& InParameters, const FString& DisplacedMeshFolder, ELinkDisplacedMeshAssetSetting LinkDisplacedMeshAssetSetting = ELinkDisplacedMeshAssetSetting::LinkAgainstPersistentAsset, bool* bOutCreatedNewMesh = nullptr );` — `UE_DEPRECATED(5.6, "Use the other override with the FValidatedNaniteDisplacedMeshParams as second the argument type instead")`
- L56 _prototype_ `UNaniteDisplacedMesh* LinkDisplacedMeshAsset( UNaniteDisplacedMesh* ExistingDisplacedMesh, FValidatedNaniteDisplacedMeshParams&& InParameters, const FNaniteDisplacedMeshLinkParameters& InLinkParameters );`
- L66 _prototype_ `FString GetSuggestedDisplacedMeshFolder(const FStringView& InSubPathForDisplacedMesh, const FValidatedNaniteDisplacedMeshParams& InParameters);` — Suggest a path to store the displaced base on if the asset used to generate the mesh all live in the same plugin. @return A non empty string if it has a folder suggestion for the displaced mesh
- L68 _externvar_ `extern const TCHAR* LinkedDisplacedMeshAssetNamePrefix;`
- L70 _prototype_ `FString GenerateLinkedDisplacedMeshAssetName(const FNaniteDisplacedMeshParams& InParameters);`
- L72 _prototype_ `FGuid GetAggregatedId(const FNaniteDisplacedMeshParams& DisplacedMeshParams);`
- L73 _prototype_ `FGuid GetAggregatedId(const UNaniteDisplacedMesh& DisplacedMesh);`
- L75 _prototype_ `FString GetAggregatedIdString(const FNaniteDisplacedMeshParams& DisplacedMeshParams);`
- L76 _prototype_ `FString GetAggregatedIdString(const UNaniteDisplacedMesh& DisplacedMesh);`
