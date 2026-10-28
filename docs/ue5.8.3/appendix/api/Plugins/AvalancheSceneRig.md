# Plugins / AvalancheSceneRig

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheSceneRig`
- headers: 2; symbols: 32
- symbol kinds: class=1, delegate=1, member=2, namespace=4, prototype=22, variable=2
- PrivateDependencyModuleNames: AssetRegistry, Engine
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSceneRig/Public/AvaSceneRigAssetTags.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace AvaSceneRig` (scope `UE`)
- L7 _namespace_ `namespace AssetTags` (scope `UE::AvaSceneRig`)
- L9 _variable_ `constexpr const TCHAR* SceneRig = TEXT("Ava` (scope `UE::AvaSceneRig::AssetTags`)
- L11 _namespace_ `namespace Values` (scope `UE::AvaSceneRig::AssetTags`)
- L13 _variable_ `constexpr const TCHAR* Enabled = TEXT("Ena` (scope `UE::AvaSceneRig::AssetTags::Values`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSceneRig/Public/AvaSceneRigSubsystem.h` (Public)


#### class `UAvaSceneRigSubsystem`  
`class UAvaSceneRigSubsystem : public UWorldSubsystem`  
_L26-100_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- L32 _public prototype_ `static UAvaSceneRigSubsystem* ForWorld(const UWorld* const InWorld);` — Returns the Scene Rig Subsystem for a world.
- L35 _public prototype_ `static bool IsSceneRigAssetData(const FAssetData& InAssetData);` — Returns true if the asset data is for a Scene Rig level.
- L38 _public prototype_ `static bool IsSceneRigAsset(UObject* const InObject);` — Returns true if the asset object is Scene Rig level.
- L41 _public prototype_ `static FString GetSceneRigAssetSuffix();` — Returns the Scene Rig level suffix string. Recommended to append to level asset name to differentiate them from other levels.
- L44 _public prototype_ `static void RegisterSupportedActorClasses(const TSet<TSubclassOf<AActor>>& InClasses);` — Registers actor classes that are allowed to be added to a Scene Rig.
- L47 _public prototype_ `static void UnregisterSupportedActorClasses(const TSet<TSubclassOf<AActor>>& InClasses);` — Unregisters actor classes that are allowed to be added to a Scene Rig.
- L50 _public prototype_ `static const TSet<TSubclassOf<AActor>>& GetSupportedActorClasses();` — Returns the list of supported object classes that are allowed to be added to a scene rig level.
- L53 _public prototype_ `static bool IsSupportedActorClass(TSubclassOf<AActor> InClass);` — Returns true if the class is a supported Scene Rig class.
- L56 _public prototype_ `static bool AreActorsSupported(const TArray<AActor*>& InActors);` — Returns true if the list of actors are supported Scene Rig classes.
- L59 _public prototype_ `static ULevelStreaming* SceneRigFromActor(AActor* const InActor);` — Returns the active Scene Rig that an actor belongs to.
- L62 _public prototype_ `static bool AreAllActorsInLevel(ULevel* const InLevel, const TArray<AActor*>& InActors);` — Returns true if all actors exist in the level.
- L65 _public prototype_ `static bool AreSomeActorsInLevel(ULevel* const InLevel, const TArray<AActor*>& InActors);` — Returns true if at least one actor exists in the level.
- L68 _public prototype_ `TArray<ULevelStreaming*> FindAllSceneRigs() const;` — Find all scene rig streaming levels in the current persistent level.
- L71 _public prototype_ `ULevelStreaming* FindFirstActiveSceneRig() const;` — Returns the first active Scene Rig object in the persistent level. NOTE: There should only be one Scene Rig in a world at any time.
- L74 _public prototype_ `UWorld* FindFirstActiveSceneRigAsset() const;` — Returns all Scene Rig asset level paths that exist in the persistent level. NOTE: There should only be one Scene Rig in a world at any time.
- L77 _public prototype_ `bool IsActiveSceneRigActor(AActor* const InActor) const;` — Removes a list of actors from the active Scene Rig.
- L79 _public prototype_ `void ForEachActiveSceneRigActor(TFunction<void(AActor* const InActor)> InFunction) const;`
- L82 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& InOutCollection) override;`
- L83 _public prototype_ `virtual void Deinitialize() override;`
- L88 _private prototype_ `void OnGetWorldTags(FAssetRegistryTagsContext InContext) const;`
- L92 _private prototype_ `virtual bool ShouldCreateSubsystem(UObject* const InOuter) const override;`
- L96 _private member_ `FDelegateHandle WorldTagGetterDelegate;`
- L99 _private member_ `static TSet<TSubclassOf<AActor>> SupportedActorClasses;`

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(AvaSceneRigSubsystemLog, Log, All);`
- L23 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(AvaSceneRigSubsystemLog, Log, All);`
