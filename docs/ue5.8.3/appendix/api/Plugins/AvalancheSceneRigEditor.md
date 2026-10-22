# Plugins / AvalancheSceneRigEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheSceneRigEditor`
- headers: 6; symbols: 92
- symbol kinds: class=6, delegate=4, function=7, member=16, prototype=59
- PrivateDependencyModuleNames: AssetRegistry, AssetTools, Avalanche, AvalancheOutliner, AvalancheSceneRig, Engine, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSceneRigEditor/Private/AvaSceneRigEditorModule.h` (Private)


#### class `FAvaSceneRigEditorModule`  
`class FAvaSceneRigEditorModule : public IAvaSceneRigEditorModule`  
_L21-54_
- inherits: `IAvaSceneRigEditorModule`
- L25 _public prototype_ `virtual void CustomizeSceneRig(const TSharedRef<IPropertyHandle>& InSceneRigHandle, IDetailLayoutBuilder& DetailBuilder) override;`
- L26 _public prototype_ `virtual ULevelStreaming* SetActiveSceneRig(UWorld* const InWorld, const FSoftObjectPath& InSceneRigAssetPath) const override;`
- L27 _public prototype_ `virtual FSoftObjectPath GetActiveSceneRig(UWorld* const InWorld) const override;`
- L28 _public prototype_ `virtual bool IsActiveSceneRigActor(UWorld* const InWorld, AActor* const InActor) const override;`
- L29 _public prototype_ `virtual bool RemoveAllSceneRigs(UWorld* const InWorld) const override;`
- L30 _public prototype_ `virtual void AddActiveSceneRigActors(UWorld* const InWorld, const TArray<AActor*>& InActors) const override;`
- L31 _public prototype_ `virtual void RemoveActiveSceneRigActors(UWorld* const InWorld, const TArray<AActor*>& InActors) const override;`
- L32 _public prototype_ `virtual FSoftObjectPath CreateSceneRigAssetWithDialog() const override;`
- L33 _public function_ `virtual FOnSceneRigChanged& OnSceneRigChanged() override`
- L34 _public function_ `virtual FOnSceneRigActorsAdded& OnSceneRigActorsAdded() override`
- L35 _public function_ `virtual FOnSceneRigActorsRemoved& OnSceneRigActorsRemoved() override`
- L39 _public prototype_ `virtual void StartupModule() override;`
- L40 _public prototype_ `virtual void ShutdownModule() override;`
- L44 _private prototype_ `void RegisterOutlinerItems();`
- L45 _private prototype_ `void UnregisterOutlinerItems();`
- L47 _private prototype_ `UAvaSceneSettings* GetSceneSettings(UWorld* const InWorld) const;`
- L49 _private member_ `FDelegateHandle OutlinerProxiesExtensionDelegateHandle;`
- L51 _private member_ `FOnSceneRigChanged OnSceneRigChangedDelegate;`
- L52 _private member_ `FOnSceneRigActorsAdded OnSceneRigActorsAddedDelegate;`
- L53 _private member_ `FOnSceneRigActorsRemoved OnSceneRigActorsRemovedDelegate;`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(AvaSceneRigEditorLog, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(AvaSceneRigEditorLog, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSceneRigEditor/Private/Outliner/AvaOutlinerSceneRig.h` (Private)


#### class `FAvaOutlinerSceneRig`  
`class FAvaOutlinerSceneRig : public FAvaOutlinerObjectReference`  
_L21-42_
- inherits: `FAvaOutlinerObjectReference`
- desc: Item in Outliner representing a Scene Rig object. Inherits from FAvaOutlinerObjectReference as multiple objects can be in the same Scene Rig.
- L24 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerSceneRig, FAvaOutlinerObjectReference);`
- L26 _public prototype_ `FAvaOutlinerSceneRig(IAvaOutliner& InOutliner, ULevelStreaming* const InSceneRig, const FAvaOutlinerItemPtr& InReferencingItem);`
- L29 _public prototype_ `virtual FText GetDisplayName() const override;`
- L30 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L31 _public prototype_ `virtual void Select(FAvaOutlinerScopedSelection& InSelection) const override;`
- L36 _private prototype_ `virtual void SetObject_Impl(UObject* InObject) override;`
- L39 _private member_ `FSlateIcon Icon;`
- L41 _private member_ `TWeakObjectPtr<ULevelStreaming> StreamingLevelWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSceneRigEditor/Private/Outliner/AvaOutlinerSceneRigProxy.h` (Private)


#### class `FAvaOutlinerSceneRigProxy`  
`class FAvaOutlinerSceneRigProxy : public FAvaOutlinerItemProxy`  
_L13-51_
- inherits: `FAvaOutlinerItemProxy`
- L16 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerSceneRigProxy, FAvaOutlinerItemProxy);`
- L18 _public prototype_ `FAvaOutlinerSceneRigProxy(IAvaOutliner& InOutliner, const FAvaOutlinerItemPtr& InParentItem);`
- L23 _public prototype_ `virtual void OnItemRegistered() override;`
- L24 _public prototype_ `virtual void OnItemUnregistered() override;`
- L25 _public prototype_ `virtual FText GetDisplayName() const override;`
- L26 _public prototype_ `virtual FSlateIcon GetIcon() const override;`
- L27 _public prototype_ `virtual FText GetIconTooltipText() const override;`
- L31 _public prototype_ `virtual void GetProxiedItems(const TSharedRef<IAvaOutlinerItem>& InParent, TArray<FAvaOutlinerItemPtr>& OutChildren, bool bInRecursive) override;`
- L35 _private prototype_ `void BindDelegates();`
- L36 _private prototype_ `void UnbindDelegates();`
- L38 _private prototype_ `void OnSceneRigChanged(UWorld* const InWorld, ULevelStreaming* const InSceneRig);`
- L39 _private prototype_ `void OnSceneRigActorAdded(UWorld* const InWorld, const TArray<AActor*>& InActors);`
- L40 _private prototype_ `void OnSceneRigActorRemoved(UWorld* const InWorld, const TArray<AActor*>& InActors);`
- L42 _private prototype_ `ULevelStreaming* GetSceneRigAsset() const;`
- L44 _private member_ `FSlateIcon Icon;`
- L46 _private member_ `FDelegateHandle OnSceneRigChangedHandle;`
- L47 _private member_ `FDelegateHandle OnSceneRigActorAddedHandle;`
- L48 _private member_ `FDelegateHandle OnSceneRigActorRemovedHandle;`
- L50 _private member_ `TWeakObjectPtr<ULevelStreaming> StreamingLevelWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSceneRigEditor/Private/Widgets/SSceneRigPicker.h` (Private)


#### class `SSceneRigPicker`  
`class SSceneRigPicker : public SCompoundWidget`  
_L13-32_
- inherits: `SCompoundWidget`
- L15 _private function_ `SLATE_BEGIN_ARGS(SSceneRigPicker)`
- L16 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakObjectPtr<UObject>& InObjectBeingCustomized);`
- L21 _protected prototype_ `bool ShouldFilterAsset(const FAssetData& InAssetData) const;`
- L22 _protected prototype_ `FString GetObjectPath() const;`
- L23 _protected prototype_ `void OnObjectChanged(const FAssetData& InAssetData) const;`
- L25 _protected prototype_ `void OnAddNewSceneRigClick() const;`
- L26 _protected prototype_ `void OnRemoveSceneRigClick() const;`
- L27 _protected prototype_ `bool IsRemoveButtonEnabled() const;`
- L29 _protected prototype_ `UWorld* GetObjectWorld() const;`
- L31 _protected member_ `TWeakObjectPtr<UObject> ObjectBeingCustomized;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSceneRigEditor/Public/AvaSceneRigEditorCommands.h` (Public)


#### class `FAvaSceneRigEditorCommands`  
`class FAvaSceneRigEditorCommands : public TCommands<FAvaSceneRigEditorCommands>`  
_L8-34_
- inherits: `TCommands<FAvaSceneRigEditorCommands>`
- L11 _public prototype_ `static const FAvaSceneRigEditorCommands& GetExternal();`
- L13 _public prototype_ `static const FAvaSceneRigEditorCommands& GetInternal();`
- L15 _public function_ `FAvaSceneRigEditorCommands() : TCommands<FAvaSceneRigEditorCommands>(TEXT("AvaSceneRigCommands") , NSLOCTEXT("AvaSceneRigCommands", "AvaSceneRigCommands", "Avalanche Scene Rig Commands") , NAME_None , FAppStyle::GetAppStyleSetName())`
- L23 _public prototype_ `virtual void RegisterCommands() override;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> PromptToSaveSceneRigFromOutlinerItems;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> AddOutlinerItemsToSceneRig;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> RemoveOutlinerItemsToSceneRig;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheSceneRigEditor/Public/IAvaSceneRigEditorModule.h` (Public)


#### class `IAvaSceneRigEditorModule`  
`class IAvaSceneRigEditorModule : public IModuleInterface`  
_L24-70_
- inherits: `IModuleInterface`
- L26 _private member_ `static constexpr const TCHAR* ModuleName = TEXT("Ava`
- L29 _public function_ `static bool IsLoaded()`
- L34 _public function_ `static IAvaSceneRigEditorModule& Get()`
- L39 _public prototype_ `virtual void CustomizeSceneRig(const TSharedRef<IPropertyHandle>& InSceneRigHandle, IDetailLayoutBuilder& DetailBuilder) = 0;`
- L42 _public prototype_ `virtual ULevelStreaming* SetActiveSceneRig(UWorld* const InWorld, const FSoftObjectPath& InSceneRigAssetPath) const = 0;` — Adds a Scene Rig streaming level to the world from a path to a Scene Rig level asset.
- L45 _public prototype_ `virtual FSoftObjectPath GetActiveSceneRig(UWorld* const InWorld) const = 0;` — As opposed to UAvaSceneSubsystem::FindFirstActiveSceneRig, this returns the cached Scene State Scene Rig.
- L48 _public prototype_ `virtual bool IsActiveSceneRigActor(UWorld* const InWorld, AActor* const InActor) const = 0;` — Returns true if the specified actor is a member of the active Scene Rig.
- L51 _public prototype_ `virtual bool RemoveAllSceneRigs(UWorld* const InWorld) const = 0;` — Removes all Scene Rig objects from the persistent level.
- L54 _public prototype_ `virtual void AddActiveSceneRigActors(UWorld* const InWorld, const TArray<AActor*>& InActors) const = 0;` — Adds a list of actors from another streaming level to the specified Scene Rig.
- L57 _public prototype_ `virtual void RemoveActiveSceneRigActors(UWorld* const InWorld, const TArray<AActor*>& InActors) const = 0;` — Removes a list of actors from the active Scene Rig.
- L63 _public prototype_ `virtual FSoftObjectPath CreateSceneRigAssetWithDialog() const = 0;` — Creates a new Scene Rig level asset. Asks the user for a location to save the new asset to. Optionally adds actors to the new Scene Rig if a world and actors are specified.
- L65 _public prototype_ `virtual FOnSceneRigChanged& OnSceneRigChanged() = 0;`
- L67 _public prototype_ `virtual FOnSceneRigActorsAdded& OnSceneRigActorsAdded() = 0;`
- L69 _public prototype_ `virtual FOnSceneRigActorsRemoved& OnSceneRigActorsRemoved() = 0;`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_EVENT_TwoParams(IAvaSceneRigEditorModule, FOnSceneRigChanged, UWorld*, ULevelStreaming*);`
- L20 _prototype_ `DECLARE_EVENT_TwoParams(IAvaSceneRigEditorModule, FOnSceneRigChanged, UWorld*, ULevelStreaming*);`
- L21 _delegate_ `DECLARE_EVENT_TwoParams(IAvaSceneRigEditorModule, FOnSceneRigActorsAdded, UWorld*, const TArray<AActor*>&);`
- L21 _prototype_ `DECLARE_EVENT_TwoParams(IAvaSceneRigEditorModule, FOnSceneRigActorsAdded, UWorld*, const TArray<AActor*>&);`
- L22 _delegate_ `DECLARE_EVENT_TwoParams(IAvaSceneRigEditorModule, FOnSceneRigActorsRemoved, UWorld*, const TArray<AActor*>&);`
- L22 _prototype_ `DECLARE_EVENT_TwoParams(IAvaSceneRigEditorModule, FOnSceneRigActorsRemoved, UWorld*, const TArray<AActor*>&);`
