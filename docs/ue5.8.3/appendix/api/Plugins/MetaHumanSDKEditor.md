# Plugins / MetaHumanSDKEditor

- module root: `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor`
- headers: 40; symbols: 812
- symbol kinds: class=45, delegate=28, enum=14, enumerator=43, externvar=1, function=17, macro=18, member=246, namespace=58, prototype=297, struct=32, typedef=11, variable=2
- DynamicallyLoadedModuleNames: 

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/Cloud/MetaHumanCloudAuthenticationInternal.h` (Private)


#### class `UE::MetaHuman::Authentication::FClient`  
`class FClient final : public TSharedFromThis<FClient>`  
_L19-48_
- inherits: `TSharedFromThis<FClient>`
- L27 _public prototype_ `explicit FClient(FPrivateToken PrivateToken);`
- L30 _public prototype_ `static TSharedRef<FClient> CreateClient(EEosEnvironmentType EnvironmentType, void* InReserved = nullptr);` — create an instance of a MetaHuman cloud client for the given environment NOTE: if GameDev the correct reserved data needs to be passed in
- L32 _public prototype_ `void HasLoggedInUser(FOnCheckLoggedInCompletedDelegate&& OnCheckLoggedInCompletedDelegate);` — returns true if there's at least one logged in user for this client (will check auth token status)
- L34 _public prototype_ `void LoginAsync(FOnLoginCompleteDelegate&& OnLoginCompleteDelegate, FOnLoginFailedDelegate&& OnLoginFailedDelegate);` — Log in asynchronously and invoke delegate when done
- L36 _public prototype_ `void LogoutAsync(FOnLogoutCompleteDelegate&& OnLogoutCompleteDelegate);` — Log out asynchronously and invoke delegate when done
- L39 _public prototype_ `bool SetAuthHeaderForUserBlocking(TSharedRef<IHttpRequest> Request);` — Set the authorization header for this user in the given request NOTE: this might block waiting for an in-progress authentication process
- L41 _public prototype_ `FString GetLoggedInAccountId() const;` — return the currently logged in user's account id, or ""
- L43 _public prototype_ `FString GetLoggedInAccountUserName() const;` — returns the currently logged in user's user name, or ""
- L45 _public prototype_ `void Tick();` — Tick client state to allow any background tasks to be completed. Useful for blocking calls that need to wait on the authentication flow
- L47 _private member_ `TPimplPtr<FClientState> ClientState;`

#### struct `UE::MetaHuman::Authentication::FClient::FPrivateToken`  
`struct FPrivateToken`  
_L22-25_
- L24 _public prototype_ `explicit FPrivateToken() = default;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MetaHuman` (scope `UE`)
- L10 _namespace_ `namespace Authentication` (scope `UE::MetaHuman`)
- L14 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnCheckLoggedInCompletedDelegate, bool, FString, FString);`
- L14 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnCheckLoggedInCompletedDelegate, bool, FString, FString);` (scope `UE::MetaHuman::Authentication`)
- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLoginCompleteDelegate, TSharedRef<class FClient>);`
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLoginCompleteDelegate, TSharedRef<class FClient>);` (scope `UE::MetaHuman::Authentication`)
- L16 _delegate_ `DECLARE_DELEGATE(FOnLoginFailedDelegate);`
- L16 _prototype_ `DECLARE_DELEGATE(FOnLoginFailedDelegate);` (scope `UE::MetaHuman::Authentication`)
- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLogoutCompleteDelegate, TSharedRef<class FClient>);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLogoutCompleteDelegate, TSharedRef<class FClient>);` (scope `UE::MetaHuman::Authentication`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/Cloud/MetaHumanDdcUtils.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DELEGATE_OneParam(FOnFetchedCacheDataDelegate, FSharedBuffer);`
- L8 _prototype_ `DECLARE_DELEGATE_OneParam(FOnFetchedCacheDataDelegate, FSharedBuffer);`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MetaHuman` (scope `UE`)
- L13 _prototype_ `bool CacheAvailable();` (scope `UE::MetaHuman`) — returns true if at least a DDC is available
- L15 _prototype_ `[[nodiscard]] FSharedBuffer TryCacheFetch(const FString& KeyString);` (scope `UE::MetaHuman`) — tries to find the given key in the cache and returns its contents if found (blocking)
- L17 _prototype_ `void TryCacheFetchAsync(const FString& KeyString, FOnFetchedCacheDataDelegate&& OnFetchedCacheDataDelegate);` (scope `UE::MetaHuman`) — tries to find the given key in the cache asynchronously. The delegate is invoked with a valid, or empty, FSharedBuffer instance
- L19 _prototype_ `void UpdateCacheAsync(const FString& KeyString, FSharedString InRequestName, FSharedBuffer InOutSharedBuffer);` (scope `UE::MetaHuman`) — tries to update the cache entry for the given key with the given content (can silently fail)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/Cloud/MetaHumanZlib.h` (Private)


#### struct `UE::MetaHuman::FZlib`  
`struct FZlib`  
_L11-25_
- desc: Convenience wrapper around Engine/Thirdparty/zlib to provide standard deflate and inflate methods
- L21 _public prototype_ `static bool Deflate(TArray<uint8>& OutDeflated, TConstArrayView<uint8> InRaw, Format DeflatedFormat);` — Deflate the InRaw array using ZLib according to the given option
- L24 _public prototype_ `static bool Inflate(TArray<uint8>& OutInflated, TConstArrayView<uint8> InDeflated, Format DeflatedFormat);` — Inflate deflated data NOTE: The option must match the option used to deflate the data originally

#### enum `UE::MetaHuman::FZlib::Format`  
`enum class Format`  
_L13-19_
- L16 _public enumerator_ `Raw` — simply deflate; use this when creating/reading ZIP archives for example
- L18 _public enumerator_ `WithZlibHeader` — deflate and wrap with zlib header and trailer; use for deflated HTTP request content for example

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/Import/MetaHumanImportUI.h` (Private)


#### struct `UE::MetaHuman::FAssetUpdateReason`  
`struct FAssetUpdateReason`  
_L15-25_
- desc: Reason for performing an update (currently only version difference, but this could be extended).
- L17 _public member_ `FMetaHumanAssetVersion OldVersion;`
- L18 _public member_ `FMetaHumanAssetVersion NewVersion;`
- L21 _public function_ `bool IsBreakingChange() const` — Whether the update is a breaking change (change in major version number)

#### struct `UE::MetaHuman::FAssetOperationPath`  
`struct FAssetOperationPath`  
_L28-34_
- desc: Description of an asset update operation
- L30 _public member_ `FString SourceFile;`
- L31 _public member_ `FString DestinationFile;`
- L32 _public member_ `FString SourcePackage;`
- L33 _public member_ `FString DestinationPackage;`

#### struct `UE::MetaHuman::FAssetOperations`  
`struct FAssetOperations`  
_L37-44_
- desc: List of relative asset paths to be Added, Replaced etc. as part of the current import action
- L39 _public member_ `TArray<FAssetOperationPath> Add;`
- L40 _public member_ `TArray<FAssetOperationPath> Replace;`
- L41 _public member_ `TArray<FAssetOperationPath> Skip;`
- L42 _public member_ `TArray<FAssetOperationPath> Update;`
- L43 _public member_ `TArray<FAssetUpdateReason> UpdateReasons;`

#### enum `UE::MetaHuman::EImportOperationUserResponse`  
`enum class EImportOperationUserResponse: int`  
_L46-51_
- L48 _public enumerator_ `OK`
- L49 _public enumerator_ `Cancel`
- L50 _public enumerator_ `BulkImport`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MetaHuman` (scope `UE`)
- L58 _prototype_ `EImportOperationUserResponse DisplayUpgradeWarning(const FSourceMetaHuman& SourceMetaHuman, const TSet<FString>& IncompatibleCharacters, const TArray<FInstalledMetaHuman>& InstalledMetaHumans, const TSet<FString>& AvailableMetaHumans, const FAssetOperations& AssetOperations);` (scope `UE::MetaHuman`) — Display a warning dialog informing the user that upgrade may impact upon incompatible MetaHumans in the project @param SourceMetaHuman The MetaHuman being imported @param IncompatibleCharacters MetaHumans in the project that are incompatible with the proposed import @param InstalledMetaHumans All MetaHumans installed in the project
- L60 _prototype_ `bool DisplayQualityLevelChangeWarning(EMetaHumanQualityLevel Source, EMetaHumanQualityLevel Target);` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/Import/MetaHumanPackageFactory.h` (Private)


#### class `UMetaHumanPackageFactory`  
`class UMetaHumanPackageFactory : public UFactory`  
_L9-25_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: Allow import of MetaHuman asset group packages
- L14 _private prototype_ `virtual FText GetToolTip() const override;` — UFactory interface
- L15 _private prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L16 _private prototype_ `virtual UObject* ImportObject(UClass* InClass, UObject* InOuter, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Parms, bool& OutCanceled) override;`
- L17 _private prototype_ `virtual void CleanUp() override;`
- L18 _private prototype_ `virtual bool DoesSupportClass(UClass* Class);`
- L24 _private member_ `TObjectPtr<UObject> MainObject;` — `UPROPERTY()`

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/MetaHumanVersionService.h` (Private)


#### struct `UE::MetaHuman::FReleaseNoteData`  
`struct FReleaseNoteData`  
_L11-17_
- desc: Represents a Release Note
- L13 _public member_ `FText Title;` — Title for the note
- L14 _public member_ `FMetaHumanVersion Version;` — MHC release that this note relates to
- L15 _public member_ `FText Note;` — Main body of the release note
- L16 _public member_ `FText Detail;` — Further detail on the release

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MetaHuman` (scope `UE`)
- L20 _prototype_ `const FString& UEVersionFromMhVersion(const FMetaHumanVersion& Version);` (scope `UE::MetaHuman`) — Given a MHC release, give the UE version it relates to as a simple FString i.e. 1.2.0 => "5.0"
- L23 _prototype_ `TArray<TSharedRef<FReleaseNoteData>> GetReleaseNotesForVersionUpgrade(const FMetaHumanVersion& FromVersion, const FMetaHumanVersion& ToVersion);` (scope `UE::MetaHuman`) — Returns all ReleaseNotes
- L26 _prototype_ `void SetServiceUrl(const FString &ServiceUrl);` (scope `UE::MetaHuman`) — Override the URL to use to connect to the version service.
- L29 _prototype_ `void Init();` (scope `UE::MetaHuman`) — Starts asynchronous retrieval of cloud data

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/ProjectUtilities/MetaHumanDependencyWalker.h` (Private)


#### enum `UE::MetaHuman::DependencyWalker::EVisitResult`  
`enum class EVisitResult : uint8`  
_L11-15_
- L13 _public enumerator_ `Follow` — Continue BFS through this dep's own dependencies.
- L14 _public enumerator_ `Skip` — Do not descend. Dep is still marked seen and won't be revisited.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MetaHuman` (scope `UE`)
- L9 _namespace_ `namespace DependencyWalker` (scope `UE::MetaHuman`)
- L21 _typedef_ `using FVisitorFn = TFunctionRef<EVisitResult(const FName& Source, const FName& Dependency)>;` (scope `UE::MetaHuman::DependencyWalker`) — Visitor signature: (Source, Dependency) -> EVisitResult. Seed packages are never passed to the visitor — they are roots, not discovered deps.
- L28 _prototype_ `void WalkDependencies(TArrayView<const FName> Seeds, FVisitorFn Visitor);` (scope `UE::MetaHuman::DependencyWalker`) — BFS over package dependencies via IAssetRegistry::GetDependencies starting from Seeds. Each newly-discovered dep is passed once to Visitor; already-seen deps are not revisited and the visitor cannot "undo" a previous Follow.

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/ProjectUtilities/MetaHumanSkeletonDefinitions.inl` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace MetaHuman` (scope `UE`)
- L7 _variable_ `static TMap<FName, FName> MetaHumanBodyHierarchy = { {"pelvis", "root"}, {"spine_01", "pelvis"}, {"spine_02", "spine_01"}, {"spine_03", "spine_02"}, {"spine_04", "spine_03"}, {"spine_05", "spine_04"}, {"neck_01", "spine_05"}, {"neck_02", "neck_01"}, {"head", "neck_02"}, {"clavicle_l", "spine_05"}, {"upperarm_l", "clavicle_l"}, {"lowerarm_l", "upperarm_l"}, {"hand_l", "lowerarm_l"}, {"index_metacarpal_l", "hand_l"}, {"index_01_l", "index_metacarpal_l"}, {"index_02_l", "index_01_l"}, {"index_03_l", "index_02_l"}, {"middle_metacarpal_l", "hand_l"}, {"middle_01_l", "middle_metacarpal_l"}, {"middle_02_l", "middle_01_l"}, {"middle_03_l", "middle_02_l"}, {"pinky_metacarpal_l", "hand_l"}, {"pinky_01_l", "pinky_metacarpal_l"}, {"pinky_02_l", "pinky_01_l"}, {"pinky_03_l", "pinky_02_l"}, {"ring_metacarpal_l", "hand_l"}, {"ring_01_l", "ring_metacarpal_l"}, {"ring_02_l", "ring_01_l"}, {"ring_03_l", "ring_02_l"}, {"thumb_01_l", "hand_l"}, {"thumb_02_l", "thumb_01_l"}, {"thumb_03_l", "thumb_02_l"}, {"wrist_inner_l", "hand_l"}, {"wrist_outer_l", "hand_l"}, {"lowerarm_twist_02_l", "lowerarm_l"}, {"lowerarm_twist_01_l", "lowerarm_l"}, {"lowerarm_correctiveRoot_l", "lowerarm_l"}, {"lowerarm_out_l", "lowerarm_correctiveRoot_l"}, {"lowerarm_in_l", "lowerarm_correctiveRoot_l"},` (scope `UE::MetaHuman`)
- L364 _variable_ `static TMap<FName, FName> MetaHumanFacialHierarchy = { {"pelvis", "root"}, {"spine_01", "pelvis"}, {"spine_02", "spine_01"}, {"spine_03", "spine_02"}, {"spine_04", "spine_03"}, {"spine_05", "spine_04"}, {"clavicle_pec_l", "spine_05"}, {"clavicle_pec_r", "spine_05"}, {"spine_04_latissimus_l", "spine_05"}, {"spine_04_latissimus_r", "spine_05"}, {"clavicle_l", "spine_05"}, {"clavicle_out_l", "clavicle_l"}, {"clavicle_scap_l", "clavicle_l"}, {"upperarm_l", "clavicle_l"}, {"upperarm_correctiveRoot_l", "upperarm_l"}, {"upperarm_out_l", "upperarm_correctiveRoot_l"}, {"upperarm_fwd_l", "upperarm_correctiveRoot_l"}, {"upperarm_in_l", "upperarm_correctiveRoot_l"}, {"upperarm_bck_l", "upperarm_correctiveRoot_l"}, {"clavicle_r", "spine_05"}, {"clavicle_out_r", "clavicle_r"}, {"clavicle_scap_r", "clavicle_r"}, {"upperarm_r", "clavicle_r"}, {"upperarm_correctiveRoot_r", "upperarm_r"}, {"upperarm_out_r", "upperarm_correctiveRoot_r"}, {"upperarm_fwd_r", "upperarm_correctiveRoot_r"}, {"upperarm_in_r", "upperarm_correctiveRoot_r"}, {"upperarm_bck_r", "upperarm_correctiveRoot_r"}, {"neck_01", "spine_05"}, {"neck_02", "neck_01"}, {"head", "neck_02"}, {"FACIAL_C_FacialRoot", "head"}, {"FACIAL_L_ForeheadMid", "FACIAL_C_FacialRoot"}, {"FACIAL_L_12IPV_ForeheadMid15", "FACIAL_L_ForeheadMid"}, {"FACIAL_L_12IPV_ForeheadMid16", "FACIAL_L_ForeheadMid"}, {"FACIAL_L_12IPV_ForeheadMid17", "FACIAL_L_ForeheadMid"}, {"FACIAL_L_12IPV_ForeheadMid18", "FACIAL_L_ForeheadMid"}, {"FACIAL_L_12IPV_ForeheadMid19", "FAC ...` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/UI/MetaHumanManager.h` (Private)


#### class `UE::MetaHuman::FMetaHumanManager`  
`class FMetaHumanManager`  
_L15-36_
- desc: Class that handles the display of the MetaHuman Manager UI for packaging MetaHuman Assets
- L21 _public prototype_ `static void Initialize();` — Initializes the manager and registers the UI with the editor
- L22 _public prototype_ `static void Shutdown();`
- L23 _public prototype_ `static void CreateWindow();`
- L31 _public prototype_ `static void OpenAndSelectAsset(const FAssetData& Asset);` — Opens the MetaHuman Manager window and attempts to select the supplied asset in the navigation pane. If the asset cannot be matched to an item in the navigation (e.g. the asset isn't packageable, or the navigation hasn't surfaced it for any reason) the window still opens — selection just defaults to the first item as usual.
- L34 _private prototype_ `FMetaHumanManager() = default;`
- L35 _private member_ `static TUniquePtr<FMetaHumanManagerImpl> Instance;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/UI/MetaHumanStyleSet.h` (Private)


#### class `UE::MetaHuman::FMetaHumanStyleSet`  
`class FMetaHumanStyleSet : public FSlateStyleSet`  
_L11-19_
- inherits: `FSlateStyleSet`
- desc: Class to manage styles used by the MetaHuman SDK
- L15 _public prototype_ `static FMetaHumanStyleSet& Get();` — Management
- L18 _private prototype_ `FMetaHumanStyleSet();`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/UI/SAssetGroupItemView.h` (Private)


#### class `UE::MetaHuman::SAssetGroupItemView`  
`class SAssetGroupItemView final : public SCompoundWidget`  
_L18-54_
- inherits: `SCompoundWidget`
- desc: Widget to display details of an AssetGroup: name, icon, contents, verification report etc.
- L21 _public function_ `SLATE_BEGIN_ARGS(SAssetGroupItemView)`
- L24 _public prototype_ `SLATE_EVENT(FOnVerify, OnVerify) SLATE_EVENT(FOnPackage, OnPackage) SLATE_ATTRIBUTE(bool, EnablePackageButton) SLATE_ATTRIBUTE(FText, VerifyButtonText) SLATE_ATTRIBUTE(FText, PackageButtonText) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _public prototype_ `void SetItem(TSharedPtr<FMetaHumanAssetDescription> AssetDescription, int32 OtherSelectedCount = 0);` — Set the item whose details are shown in the right pane. @param AssetDescription  The item to display (may be null to clear). @param OtherSelectedCount  Number of additional items selected alongside this one (0 = only item).
- L43 _private prototype_ `FReply OnVerify() const;`
- L44 _private prototype_ `FReply OnPackage() const;`
- L46 _private prototype_ `bool EnableVerifyButton() const;`
- L49 _private member_ `TSharedPtr<SAssetGroupItemDetails> ItemDetails;` — Data
- L52 _private member_ `FOnVerify OnVerifyCallback;` — Callbacks
- L53 _private member_ `FOnPackage OnPackageCallback;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MetaHuman` (scope `UE`)
- L14 _delegate_ `DECLARE_DELEGATE(FOnVerify);`
- L14 _prototype_ `DECLARE_DELEGATE(FOnVerify);` (scope `UE::MetaHuman`)
- L15 _delegate_ `DECLARE_DELEGATE(FOnPackage);`
- L15 _prototype_ `DECLARE_DELEGATE(FOnPackage);` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/UI/SAssetGroupNavigation.h` (Private)


#### class `UE::MetaHuman::SNavigationEntry`  
`class SNavigationEntry : public STableRow<TSharedRef<FMetaHumanAssetDescription>>`  
_L19-59_
- inherits: `STableRow<TSharedRef<FMetaHumanAssetDescription>>`
- desc: A Navigation entry in the list - represents a selectable MetaHuman Asset Group
- L22 _public function_ `SLATE_BEGIN_ARGS(SNavigationEntry)`
- L25 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FMetaHumanAssetDescription>, Item) SLATE_ATTRIBUTE(bool, IsMultiSelectMode) SLATE_ATTRIBUTE(bool, IsChecked) SLATE_ATTRIBUTE(bool, IsDisabledByRule) SLATE_EVENT(FSimpleDelegate, OnCheckChanged) SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& Owner);`
- L40 _private member_ `TSharedPtr<FMetaHumanAssetDescription> RowData;`
- L41 _private prototype_ `const FSlateBrush* GetIconForItem() const;`
- L42 _private prototype_ `FMargin GetMarginForItem() const;`
- L45 _private prototype_ `EVisibility GetCheckBoxVisibility() const;` — Checkbox visibility — only shown in multi-select mode.
- L49 _private prototype_ `bool IsContentEnabled() const;` — Inverse of IsDisabledByRuleAttr — bound to the content wrapper's IsEnabled so the row's inner widgets dim and the checkbox blocks input, but plain row clicks still propagate.
- L53 _private prototype_ `FText GetItemTooltip() const;` — Returns the Assembly-restriction message when disabled, else the asset name (which also serves as the ellipsis-overflow tooltip on the text block).
- L55 _private member_ `TAttribute<bool> IsMultiSelectModeAttr;`
- L56 _private member_ `TAttribute<bool> IsCheckedAttr;`
- L57 _private member_ `TAttribute<bool> IsDisabledByRuleAttr;`
- L58 _private member_ `FSimpleDelegate OnCheckChangedCallback;`

#### class `UE::MetaHuman::FSectionItem`  
`class FSectionItem final`  
_L64-79_
- desc: Data class for each section in the navigation list. Represents a collapsible section of the navigation pane
- L67 _public prototype_ `FSectionItem() = default;`
- L68 _public prototype_ `FSectionItem(const EMetaHumanAssetType Type);`
- L69 _public prototype_ `void SetItems(const TArray<FMetaHumanAssetDescription>& SourceItems);`
- L70 _public prototype_ `const TArray<TSharedRef<FMetaHumanAssetDescription>>& GetItems() const;`
- L71 _public prototype_ `const EMetaHumanAssetType GetType() const;`
- L72 _public prototype_ `const FText& GetName() const;`
- L73 _public prototype_ `void SetOnUpdateItems(const FOnUpdateItems& Callback);`
- L76 _private member_ `EMetaHumanAssetType Type = EMetaHumanAssetType::None;`
- L77 _private member_ `TArray<TSharedRef<FMetaHumanAssetDescription>> Items;`
- L78 _private member_ `FOnUpdateItems OnUpdateItems;`

#### struct `UE::MetaHuman::FNavigatePayload`  
`struct FNavigatePayload`  
_L86-100_
- desc: Payload for FOnNavigate. Carries both the item to display in the detail pane and the full operative set (checked items) as first-class named fields, avoiding any implicit encoding conventions that would be invisible to the type system.
- L90 _public member_ `TArray<TSharedRef<FMetaHumanAssetDescription>> DetailItems;` — The single item whose details should be shown in the right pane (the last item clicked). Empty when nothing is selected.
- L95 _public member_ `TArray<TSharedRef<FMetaHumanAssetDescription>> MultiSelectItems;` — The full set of items that Verify/Package should operate on. In single-select mode this mirrors DetailItems (0 or 1 entries). In multi-select mode it contains all checked items across all sections.
- L99 _public member_ `bool bIsCtrlClick = false;` — True when the navigation event represents a multi-select toggle (Ctrl+click or checkbox change). False for plain clicks and programmatic selections.

#### class `UE::MetaHuman::SNavigationSection`  
`class SNavigationSection final : public SCompoundWidget`  
_L113-204_
- inherits: `SCompoundWidget`
- desc: Collapsible navigation section expanding to show a list of items
- L116 _public function_ `SLATE_BEGIN_ARGS(SNavigationSection)`
- L119 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FSectionItem>, SectionItem) SLATE_ARGUMENT(bool, InitiallyCollapsed) SLATE_EVENT(FOnNavigate, OnNavigate) SLATE_EVENT(FOnExpansionChanged, OnExpand) SLATE_ATTRIBUTE(bool, IsMultiSelectMode) SLATE_ARGUMENT(TSet<FName>*, CheckedItems) SLATE_EVENT(FOnIsItemDisabled, IsItemDisabledByRule) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L131 _public prototype_ `void Collapse();`
- L134 _public prototype_ `void Expand();` — Programmatically expand this section. The parent SAssetGroupNavigation collapses other sections automatically.
- L137 _public prototype_ `void RefreshList();` — Rebuild the list so checkbox widgets re-query their state.
- L144 _public prototype_ `bool SelectAsset(const FAssetData& Asset);` — If this section currently displays an item with the supplied asset data, select it on the SListView and fire the navigate callback. Returns true if a matching item was found and selected, false otherwise.
- L147 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForItem(TSharedRef<FMetaHumanAssetDescription> Item, const TSharedRef<STableViewBase>& Owner);`
- L149 _private prototype_ `void OnSelectionChanged(const TSharedPtr<FMetaHumanAssetDescription> Item, ESelectInfo::Type Type) const;`
- L150 _private prototype_ `void OnExpansionChanged(bool bIsExpanded) const;`
- L153 _private prototype_ `void ToggleChecked(TSharedRef<FMetaHumanAssetDescription> Item);` — Toggle the checked state of an item and notify the parent navigation.
- L156 _private prototype_ `int32 GetCheckedCountInSection() const;` — Returns the number of items in this section that are currently checked.
- L159 _private prototype_ `FText GetSelectionBadgeText() const;` — Builds the display text for the selection badge (e.g. "(2 selected)").
- L162 _private prototype_ `EVisibility GetSelectionBadgeVisibility() const;` — Badge is visible in multi-select mode when this section has checked items.
- L165 _private prototype_ `bool IsFolderFilterApplicable() const;` — True when this section supports the configured-folder filter (currently SkeletalClothing only).
- L168 _private prototype_ `bool IsFolderFilterPathConfigured() const;` — True when the configured Skeletal Clothing folder is non-empty — drives the filter button's enabled state.
- L171 _private prototype_ `EVisibility GetFolderFilterButtonVisibility() const;` — Folder filter button is visible only when IsFolderFilterApplicable() is true.
- L173 _private prototype_ `ECheckBoxState GetFolderFilterButtonCheckedState() const;`
- L174 _private prototype_ `void OnFolderFilterButtonCheckChanged(ECheckBoxState NewState);`
- L175 _private prototype_ `FText GetFolderFilterButtonTooltip() const;`
- L178 _private prototype_ `void RebuildDisplayedItems();` — Repopulates DisplayedItems from SectionItem according to the current filter state.
- L181 _private prototype_ `void OnSectionItemsChanged();` — Called when SectionItem's underlying item list changes.
- L183 _private member_ `TSharedPtr<FSectionItem> SectionItem;`
- L184 _private member_ `TSharedPtr<SExpandableArea> ExpandableArea;`
- L185 _private member_ `TSharedPtr<SListView<TSharedRef<FMetaHumanAssetDescription>>> ItemsList;`
- L186 _private member_ `FOnNavigate NavigateCallback;`
- L187 _private member_ `FOnExpansionChanged ExpansionCallback;`
- L189 _private member_ `TAttribute<bool> IsMultiSelectModeAttr;`
- L191 _private member_ `TSet<FName>* CheckedItems = nullptr;` — Non-owning pointer — owned by SAssetGroupNavigation.
- L193 _private member_ `FOnIsItemDisabled IsItemDisabledByRuleCallback;` — Per-row Assembly-restriction predicate, supplied by SAssetGroupNavigation.
- L200 _private member_ `TArray<TSharedRef<FMetaHumanAssetDescription>> DisplayedItems;` — Items currently presented to the SListView. Equal to SectionItem's items when no filter is active; a folder-filtered subset otherwise. The SListView binds to this array directly so filter toggles only require RebuildDisplayedItems + RebuildList.
- L203 _private member_ `bool bFolderFilterActive = false;` — Folder-filter toggle state. Transient — does not persist across window instances.

#### class `UE::MetaHuman::SAssetGroupNavigation`  
`class SAssetGroupNavigation final : public SCompoundWidget`  
_L207-278_
- inherits: `SCompoundWidget`
- desc: Top-level navigation UI presenting a list of collapsible sections each with a tree underneath
- L210 _public function_ `SLATE_BEGIN_ARGS(SAssetGroupNavigation)`
- L213 _public prototype_ `SLATE_EVENT(FOnNavigate, OnNavigate) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L217 _public prototype_ `void OnExpansionChanged(TSharedPtr<FSectionItem> Section, bool bIsExpanded);`
- L218 _public prototype_ `void Refresh();`
- L225 _public prototype_ `void SelectAsset(const FAssetData& Asset);` — Locate the section containing the supplied asset, expand it, and select the matching item. Does nothing if no section currently lists the asset (e.g. it is not a packageable MetaHuman type, or the navigation has not been refreshed since the asset was created).
- L228 _private prototype_ `int32 UpdateSection(int32 DesiredIndex, EMetaHumanAssetType Type);`
- L235 _private prototype_ `void OnItemClicked(TSharedRef<FMetaHumanAssetDescription> Item, bool bIsCtrlHeld);` — Called by a section when a list item is clicked. Handles both normal clicks (exit multi-select, set single detail item) and Ctrl+clicks (enter/extend multi-select, toggle the clicked item's checked state).
- L238 _private prototype_ `void RefreshAllSectionLists();` — Rebuild all section lists so checkbox visibility/state is refreshed.
- L241 _private prototype_ `void FireNavigateCallback(TSharedRef<FMetaHumanAssetDescription> DetailItem);` — Build the multi-select array from CheckedItems and fire NavigateCallback.
- L252 _private prototype_ `bool IsRowDisabledByAssemblyRule(const TSharedPtr<FMetaHumanAssetDescription>& Item) const;` — Returns true if Item should be disabled because adding it to the current selection would create a multi-item set containing a MetaHuman Assembly. Rule: * Item not already in the operative set, AND * the operative set is non-empty, AND * the operative set contains a CharacterAssembly OR Item is a CharacterAssembly. The operative set is CheckedItems (resolved to descriptions) in multi-select mode, or {LastSingleClickItem} in single-select mode.
- L254 _private member_ `TArray<TSharedRef<FSectionItem>> Sections;`
- L255 _private member_ `TArray<TSharedRef<SNavigationSection>> SectionWidgets;`
- L256 _private member_ `TSharedPtr<SSplitter> SectionsSplitter;`
- L257 _private member_ `FOnNavigate NavigateCallback;`
- L260 _private member_ `bool bMultiSelectMode = false;` — Whether multi-select mode is currently active.
- L267 _private member_ `TSet<FName> CheckedItems;` — Set of asset package paths that are currently checked. Keyed by FMetaHumanAssetDescription::AssetData.PackageName. Populated only during multi-select mode.
- L270 _private member_ `TArray<TSharedRef<FMetaHumanAssetDescription>> AllItems;` — All items known across all sections — used to resolve CheckedItems to descriptions.
- L277 _private member_ `TSharedPtr<FMetaHumanAssetDescription> LastSingleClickItem;` — The item most recently selected by a plain (non-Ctrl) click. When the user Ctrl+clicks to enter multi-select mode for the first time, this item is added to CheckedItems alongside the newly clicked item so it is not silently dropped.

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MetaHuman` (scope `UE`)
- L61 _delegate_ `DECLARE_DELEGATE(FOnUpdateItems);`
- L61 _prototype_ `DECLARE_DELEGATE(FOnUpdateItems);` (scope `UE::MetaHuman`)
- L103 _delegate_ `DECLARE_DELEGATE_OneParam(FOnNavigate, const FNavigatePayload&);` — Fired by SAssetGroupNavigation whenever the user's selection changes.
- L103 _prototype_ `DECLARE_DELEGATE_OneParam(FOnNavigate, const FNavigatePayload&);` (scope `UE::MetaHuman`) — Fired by SAssetGroupNavigation whenever the user's selection changes.
- L105 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnExpansionChanged, TSharedPtr<FSectionItem>, bool);`
- L105 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnExpansionChanged, TSharedPtr<FSectionItem>, bool);` (scope `UE::MetaHuman`)
- L110 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnIsItemDisabled, const TSharedPtr<FMetaHumanAssetDescription>&);` — Returns true if the supplied row should be disabled in the navigation list because selecting it would create a multi-item set containing a MetaHuman Assembly. Bound by SAssetGroupNavigation; queried per-row at paint time.
- L110 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnIsItemDisabled, const TSharedPtr<FMetaHumanAssetDescription>&);` (scope `UE::MetaHuman`) — Returns true if the supplied row should be disabled in the navigation list because selecting it would create a multi-item set containing a MetaHuman Assembly. Bound by SAssetGroupNavigation; queried per-row at paint time.

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/UI/SImportSummary.h` (Private)


#### struct `UE::MetaHuman::FImportResult`  
`struct FImportResult`  
_L13-17_
- L15 _public member_ `TStrongObjectPtr<UMetaHumanAssetReport> Report;`
- L16 _public member_ `TStrongObjectPtr<UObject> Target;`

#### class `UE::MetaHuman::SImportSummary`  
`class SImportSummary final : public SWindow`  
_L19-34_
- inherits: `SWindow`
- L22 _public function_ `SLATE_BEGIN_ARGS(SImportSummary)`
- L25 _public prototype_ `SLATE_ARGUMENT(TArray<TSharedPtr<FImportResult>>, ImportResults) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _private prototype_ `void ChangeSelection(TSharedPtr<FImportResult> Item);`
- L32 _private member_ `TArray<TSharedPtr<FImportResult>> ImportResults;`
- L33 _private member_ `TSharedPtr<SImportItemView> ItemView;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/UI/SMetaHumanAssetReportView.h` (Private)


#### class `UE::MetaHuman::SMetaHumanAssetReportView`  
`class SMetaHumanAssetReportView final : public SCompoundWidget`  
_L14-45_
- inherits: `SCompoundWidget`
- desc: Top-level navigation UI presenting a list of collapsible sections each with a tree underneath
- L23 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanAssetReportView) : _ReportType(EReportType::Verification)`
- L27 _public prototype_ `SLATE_ARGUMENT(EReportType, ReportType) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _public prototype_ `void SetReport(UMetaHumanAssetReport* ReportToDisplay);`
- L34 _private prototype_ `void OnClickItem(TSharedPtr<SReportDataItem> Item) const;`
- L35 _private prototype_ `TSharedPtr<SWidget> OnContextMenu() const;`
- L36 _private prototype_ `EVisibility GetSaveButtonVisibility() const;`
- L37 _private prototype_ `FReply OnSaveButtonClicked();`
- L38 _private prototype_ `const FSlateBrush* GetIconForHeader() const;`
- L39 _private prototype_ `FText GetTextForHeader() const;`
- L41 _private member_ `TStrongObjectPtr<UMetaHumanAssetReport> Report;`
- L42 _private member_ `TArray<TSharedPtr<SReportDataItem>> ReportData;`
- L43 _private member_ `TSharedPtr<STreeView<TSharedPtr<SReportDataItem>>> ReportItemsTreeView;`
- L44 _private member_ `EReportType ReportType = EReportType::Verification;`

#### enum `UE::MetaHuman::SMetaHumanAssetReportView::EReportType`  
`enum class EReportType: int32`  
_L17-21_
- L19 _public enumerator_ `Verification`
- L20 _public enumerator_ `Import`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/UI/SPackageDestinationDialog.h` (Private)


#### enum `UE::MetaHuman::EPackageDestinationMode`  
`enum class EPackageDestinationMode : uint8`  
_L10-18_
- desc: Result returned by the package destination dialog.
- L13 _public enumerator_ `Cancelled` — User closed the dialog without making a choice.
- L15 _public enumerator_ `CombinedArchive` — Package all selected assets together into one .mhpkg file chosen by the user.
- L17 _public enumerator_ `SeparateArchives` — Package each selected asset into its own .mhpkg file inside a folder chosen by the user.

#### class `UE::MetaHuman::SPackageDestinationDialog`  
`class SPackageDestinationDialog final : public SCompoundWidget`  
_L26-48_
- inherits: `SCompoundWidget`
- desc: Modal dialog that asks whether the user wants to package selected assets into one combined archive or into separate per-asset archives. Shown only when two or more assets are selected.
- L29 _public function_ `SLATE_BEGIN_ARGS(SPackageDestinationDialog)`
- L33 _public prototype_ `SLATE_ARGUMENT(int32, AssetCount) SLATE_EVENT(FOnPackageDestinationModeSelected, OnModeSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Number of assets being packaged — used in the dialog title/description.
- L41 _private prototype_ `FReply OnCombinedClicked();`
- L42 _private prototype_ `FReply OnSeparateClicked();`
- L43 _private prototype_ `FReply OnCancelClicked();`
- L45 _private prototype_ `void CloseParentWindow();`
- L47 _private member_ `FOnPackageDestinationModeSelected OnModeSelectedCallback;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace MetaHuman` (scope `UE`)
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPackageDestinationModeSelected, EPackageDestinationMode);`
- L20 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPackageDestinationModeSelected, EPackageDestinationMode);` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/UI/SPackagingInstructions.h` (Private)


#### class `UE::MetaHuman::SPackagingInstructions`  
`class SPackagingInstructions final : public SCompoundWidget`  
_L11-19_
- inherits: `SCompoundWidget`
- desc: Widget to display packaging instructions when no item is selectable in MetaHuman Manager
- L13 _private function_ `SLATE_BEGIN_ARGS(SPackagingInstructions)`
- L16 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Private/Verification/MetaHumanCharacterVerification.h` (Private)


#### struct `UE::MetaHuman::FMetaHumanCharacterVerification`  
`struct FMetaHumanCharacterVerification`  
_L17-42_
- desc: Verification for more complex types used by MetaHuman. This code is designed to avoid heavyweight plugin dependencies in the MetaHumanSDK while allowing use of those types if required.
- L19 _public prototype_ `FMetaHumanCharacterVerification();`
- L22 _public prototype_ `void VerifyGroomWardrobeItem(TNotNull<const UObject*> Target, TNotNull<const UObject*> GroomBindingAsset, UMetaHumanAssetReport* Report) const;` — WardrobeItem verification
- L23 _public prototype_ `void VerifySkelMeshClothingWardrobeItem(TNotNull<const UObject*> Target, TNotNull<const UObject*> SkeletalMesh, UMetaHumanAssetReport* Report) const;`
- L24 _public prototype_ `void VerifyOutfitWardrobeItem(TNotNull<const UObject*> Target, TNotNull<const UObject*> OutfitAsset, UMetaHumanAssetReport* Report) const;`
- L27 _public prototype_ `void VerifyOutfitAsset(TNotNull<const UObject*> Target, UMetaHumanAssetReport* Report) const;` — Custom verification for individual types
- L28 _public prototype_ `void VerifyMetaHumanCharacterAsset(TNotNull<const UObject*> Target, UMetaHumanAssetReport* Report) const;`
- L31 _public prototype_ `FClothingAssetDetails GetDetailsForClothingAsset(TNotNull<const UObject*> Target) const;` — Technical details fro individual types
- L34 _public prototype_ `bool IsWardrobeItem(TNotNull<const UObject*> Target);` — Lightweight type checks
- L35 _public prototype_ `bool IsCharacterAsset(TNotNull<const UObject*> Target);`
- L36 _public prototype_ `bool IsOutfitAsset(TNotNull<const UObject*> Target);`
- L38 _public prototype_ `static FMetaHumanCharacterVerification& Get();`
- L41 _private member_ `TStrongObjectPtr<UMetaHumanCharacterTypesVerificationExtensionBase> Extension;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Cloud/MetaHumanARServiceRequest.h` (Public)


#### enum `UE::MetaHuman::ERigType`  
`enum class ERigType`  
_L10-14_
- L12 _public enumerator_ `JointsOnly`
- L13 _public enumerator_ `JointsAndBlendshapes`

#### enum `UE::MetaHuman::ERigRefinementLevel`  
`enum class ERigRefinementLevel`  
_L16-20_
- L18 _public enumerator_ `None`
- L19 _public enumerator_ `Medium`

#### enum `UE::MetaHuman::EExportLayers`  
`enum class EExportLayers`  
_L22-27_
- L24 _public enumerator_ `Default` — can be anything, down to the current service implementation. Only use if you really don't care
- L25 _public enumerator_ `None`
- L26 _public enumerator_ `Rbf`

#### struct `UE::MetaHuman::FTargetSolveParameters`  
`struct FTargetSolveParameters`  
_L29-50_
- L31 _public prototype_ `FTargetSolveParameters() = default;`
- L33 _public member_ `TArray<FVector> ConformedFaceVertices;`
- L34 _public member_ `TArray<FVector> ConformedLeftEyeVertices;`
- L35 _public member_ `TArray<FVector> ConformedRightEyeVertices;`
- L36 _public member_ `TArray<FVector> ConformedTeethVertices;`
- L37 _public member_ `TArray<FVector> ConformedCartilageVertices;`
- L38 _public member_ `TArray<FVector> ConformedEyeEdgeVertices;`
- L39 _public member_ `TArray<FVector> ConformedEyeShellVertices;`
- L40 _public member_ `TArray<FVector> ConformedEyeLashesVertices;`
- L41 _public member_ `TArray<FVector> ConformedSalivaVertices;`
- L42 _public member_ `TArray<float> BindPose;`
- L43 _public member_ `TArray<float> Coefficients;`
- L44 _public member_ `int32 HighFrequency = 0;`
- L45 _public member_ `ERigType RigType = ERigType::JointsOnly;`
- L46 _public member_ `ERigRefinementLevel RigRefinementLevel = ERigRefinementLevel::None;`
- L47 _public member_ `EExportLayers ExportLayers = EExportLayers::Rbf;`
- L48 _public member_ `float Scale = 1.0f;`
- L49 _public member_ `FString ModelIdentifier;`

#### class `UE::MetaHuman::FAutorigResponse`  
`class FAutorigResponse`  
_L53-75_
- L56 _private function_ `FAutorigResponse(const TArray<uint8>& Content) : Payload(Content)`
- L62 _public function_ `bool IsValid() const`
- L68 _public member_ `TSharedPtr<::IDNAReader> Dna;` — DNA that can be applied to skeletal mesh.
- L72 _private member_ `const TArray<uint8>& Payload;` — NOTE: this payload data's lifetime is limited by the duration of the delegate recieving the response data
- L73 _private member_ `bool bValid;`
- L74 _private prototype_ `bool ReadDna();`

#### class `UE::MetaHuman::FAutoRigServiceRequest`  
`class FAutoRigServiceRequest final : public FMetaHumanServiceRequestBase`  
_L86-105_
- inherits: `FMetaHumanServiceRequestBase`
- desc: Request to autorig service Usage * Bind to the required Delegates (in this class and in FMetaHumanServiceRequestBase as needed) * Create an instance of a request using CreateRequest * Run the request The request will return a raw DNA file (in memory)
- L90 _public prototype_ `FAutoRigServiceRequest() = default;`
- L92 _public prototype_ `DECLARE_DELEGATE_OneParam(FAutorigRequestCompleteDelegate, const FAutorigResponse& Response);`
- L93 _public member_ `FAutorigRequestCompleteDelegate AutorigRequestCompleteDelegate;`
- L96 _public prototype_ `static TSharedRef<FAutoRigServiceRequest> CreateRequest(const FTargetSolveParameters& InSolveParams);` — create a new autorig service request for a mesh
- L98 _public prototype_ `void RequestSolveAsync();` — execute the solve request asynchronously
- L101 _protected prototype_ `virtual bool DoBuildRequest(TSharedRef<IHttpRequest> HttpRequest, FRequestContextBasePtr Context) override;`
- L102 _protected prototype_ `virtual void OnRequestCompleted(const TArray<uint8>& Content, FRequestContextBasePtr Context) override;`
- L104 _private member_ `FTargetSolveParameters SolveParameters;`

#### Free symbols / members of external scopes

- L5 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MetaHuman` (scope `UE`)
- L92 _delegate_ `DECLARE_DELEGATE_OneParam(FAutorigRequestCompleteDelegate, const FAutorigResponse& Response);`

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Cloud/MetaHumanCloudAuthentication.h` (Public)


#### enum `UE::MetaHuman::Authentication::EEosEnvironmentType`  
`enum class EEosEnvironmentType`  
_L8-12_
- L10 _public enumerator_ `Prod`
- L11 _public enumerator_ `GameDev`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace MetaHuman` (scope `UE`)
- L6 _namespace_ `namespace Authentication` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Cloud/MetaHumanCloudServicesSettings.h` (Public)


#### enum `EMetaHumanCloudServiceEnvironment`  
`enum class EMetaHumanCloudServiceEnvironment`  
_L7-11_
- reflection: `UENUM()`
- L9 _public enumerator_ `Production`
- L10 _public enumerator_ `GameDev`

#### struct `FEosConstantsPlatform`  
`struct FEosConstantsPlatform`  
_L14-37_
- reflection: `USTRUCT()`
- L20 _public member_ `FString ProductId;` — `UPROPERTY()` — The product id for the running application, found on the dev portal
- L24 _public member_ `FString SandboxId;` — `UPROPERTY()` — The sandbox id for the running application, found on the dev portal
- L28 _public member_ `FString DeploymentId;` — `UPROPERTY()` — The deployment id for the running application, found on the dev portal
- L32 _public member_ `FString ClientCredentialsId;` — `UPROPERTY()` — Client id of the service permissions entry, found on the dev portal
- L36 _public member_ `FString ClientCredentialsSecret;` — `UPROPERTY()` — Client secret for accessing the set of permissions, found on the dev portal

#### class `UMetaHumanCloudServicesSettings`  
`class UMetaHumanCloudServicesSettings : public UObject`  
_L43-67_
- reflection: `UCLASS(Config = MetaHumanSDK)`
- inherits: `UObject`
- desc: NOTE: Settings are in MetaHumanCharacter/Config/BaseMetaHumanCharacter.ini
- L48 _public member_ `FString TextureSynthesisServiceUrl;` — `UPROPERTY(Config)`
- L50 _public member_ `FString AutorigServiceUrl;` — `UPROPERTY(Config)`
- L52 _public member_ `float Timeout;` — `UPROPERTY(Config)`
- L54 _public member_ `float LongPollTimeout;` — `UPROPERTY(Config)`
- L56 _public member_ `float AuthTimeout;` — `UPROPERTY(Config)`
- L58 _public member_ `float AuthPollInterval;` — `UPROPERTY(Config)`
- L60 _public member_ `int32 RetryCount;` — `UPROPERTY(Config)`
- L62 _public member_ `EMetaHumanCloudServiceEnvironment ServiceEnvironment = EMetaHumanCloudServiceEnvironment::Production;` — `UPROPERTY(Config)`
- L64 _public member_ `FEosConstantsPlatform ProdEosConstants;` — `UPROPERTY(Config)`
- L66 _public member_ `FEosConstantsPlatform GameDevEosConstants;` — `UPROPERTY(Config)`

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Cloud/MetaHumanServiceRequest.h` (Public)


#### enum `EMetaHumanServiceRequestResult`  
`enum class EMetaHumanServiceRequestResult`  
_L20-31_
- reflection: `UENUM()`
- desc: service results that can be used by all services
- L22 _public enumerator_ `Ok`
- L23 _public enumerator_ `Busy`
- L24 _public enumerator_ `Unauthorized`
- L25 _public enumerator_ `EulaNotAccepted`
- L26 _public enumerator_ `InvalidArguments`
- L27 _public enumerator_ `ServerError`
- L28 _public enumerator_ `LoginFailed`
- L29 _public enumerator_ `Timeout`
- L30 _public enumerator_ `GatewayError`

#### class `UE::MetaHuman::FRequestContextBase`  
`class FRequestContextBase : public TSharedFromThis<FRequestContextBase, ESPMode::ThreadSafe>`  
_L49-60_
- inherits: `TSharedFromThis<FRequestContextBase,ESPMode::ThreadSafe>`
- desc: Subclass contexts must derive from this class for appropriate lifetimes
- L52 _public prototype_ `FRequestContextBase();`
- L53 _public prototype_ `virtual ~FRequestContextBase() = default;`
- L55 _protected prototype_ `FRequestContextBase(TSharedRef<FMetaHumanServiceRequestBase> Owner);`
- L59 _private member_ `TPimplPtr<FImpl> BaseImpl;`

#### class `UE::MetaHuman::FMetaHumanServiceRequestBase`  
`class FMetaHumanServiceRequestBase : public TSharedFromThis<FMetaHumanServiceRequestBase, ESPMode::ThreadSafe>`  
_L99-130_
- inherits: `TSharedFromThis<FMetaHumanServiceRequestBase,ESPMode::ThreadSafe>`
- desc: Base class for MH Service Clients Implements the core "message loop" and delegates to specific handlers as needed. Handles: 1. Request building (delegates to subclass for payload details) 2. Success and Error response delegation NOTE: This class is not intended to be used directly (and indeed it can't)
- L103 _public prototype_ `virtual ~FMetaHumanServiceRequestBase() = default;`
- L105 _public member_ `FSimpleDelegate OnMetaHumanServiceRequestBeginDelegate;`
- L106 _public member_ `FMetaHumanServiceRequestFailedDelegate OnMetaHumanServiceRequestFailedDelegate;`
- L107 _public member_ `FMetaHumanServiceRequestProgressDelegate MetaHumanServiceRequestProgressDelegate;`
- L110 _protected prototype_ `FMetaHumanServiceRequestBase() = default;`
- L115 _protected prototype_ `virtual bool DoBuildRequest(TSharedRef<IHttpRequest> Request, FRequestContextBasePtr MaybeContext) = 0;` — build a request packet for a particular MH service Note that this can be called multiple times during an ExecuteRequest (for the same request), if for example the user first has to accept a EULA. MaybeContext can be used to pass context specific information to the subclass' delegates
- L118 _protected prototype_ `virtual void OnRequestCompleted(const TArray<uint8>& Response, FRequestContextBasePtr MaybeContext) = 0;` — invoked when the request is complete and a response payload is available the subclass is expected to package this into a adapter and forward to a service specific user delegate
- L120 _protected prototype_ `TSharedPtr<IHttpRequest> CreateRequest(FRequestContextBasePtr Context);` — create a request, but don't start executing it
- L122 _protected prototype_ `void ExecuteRequestAsync(FRequestContextBasePtr Context);` — Create and execute a request directly
- L125 _protected function_ `virtual void OnRequestFailed(EMetaHumanServiceRequestResult Result, FRequestContextBasePtr MaybeContext)` — can be overriden in the subclass if a context is needed should always be super:: invoked

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`
- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace MetaHuman` (scope `UE`)
- L38 _delegate_ `DECLARE_DELEGATE_OneParam(FMetaHumanServiceRequestFailedDelegate, EMetaHumanServiceRequestResult RequestResult);` — service request failed
- L38 _prototype_ `DECLARE_DELEGATE_OneParam(FMetaHumanServiceRequestFailedDelegate, EMetaHumanServiceRequestResult RequestResult);` (scope `UE::MetaHuman`) — service request failed
- L40 _delegate_ `DECLARE_DELEGATE_OneParam(FMetaHumanServiceRequestProgressDelegate, float Percentage);` — service request in progress (percentage might not be accurate)
- L40 _prototype_ `DECLARE_DELEGATE_OneParam(FMetaHumanServiceRequestProgressDelegate, float Percentage);` (scope `UE::MetaHuman`) — service request in progress (percentage might not be accurate)
- L42 _delegate_ `DECLARE_DELEGATE_OneParam(FMetaHumanServiceRequestFinishedDelegate, const TArray<uint8>& ServiceResponse);` — service request succeeded, payload is available
- L42 _prototype_ `DECLARE_DELEGATE_OneParam(FMetaHumanServiceRequestFinishedDelegate, const TArray<uint8>& ServiceResponse);` (scope `UE::MetaHuman`) — service request succeeded, payload is available
- L44 _delegate_ `DECLARE_DELEGATE_OneParam(FMetaHumanServiceUserEulaAcceptedCheck, bool Accepted);`
- L44 _prototype_ `DECLARE_DELEGATE_OneParam(FMetaHumanServiceUserEulaAcceptedCheck, bool Accepted);` (scope `UE::MetaHuman`)
- L61 _typedef_ `using FRequestContextBasePtr = TSharedPtr<FRequestContextBase>;` (scope `UE::MetaHuman`)
- L63 _namespace_ `namespace ServiceAuthentication` (scope `UE::MetaHuman`)
- L65 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLoginCompleteDelegate, FString);`
- L65 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLoginCompleteDelegate, FString);` (scope `UE::MetaHuman::ServiceAuthentication`)
- L72 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnCheckHasLoggedInUserCompleteDelegate, bool, FString, FString);` — <summary> delegate invoked when CheckHasLoggedInUserAsync completes </summary> <param name="bLoggedIn">user is logged</param> <param name="AccountId">if logged in, account id of user</param> <param name="AccountUserName">if logged in, a user name or handle for the user</param>
- L72 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnCheckHasLoggedInUserCompleteDelegate, bool, FString, FString);` (scope `UE::MetaHuman::ServiceAuthentication`) — <summary> delegate invoked when CheckHasLoggedInUserAsync completes </summary> <param name="bLoggedIn">user is logged</param> <param name="AccountId">if logged in, account id of user</param> <param name="AccountUserName">if logged in, a user name or handle for the user</param>
- L73 _delegate_ `DECLARE_DELEGATE(FOnLoginFailedDelegate);`
- L73 _prototype_ `DECLARE_DELEGATE(FOnLoginFailedDelegate);` (scope `UE::MetaHuman::ServiceAuthentication`)
- L74 _delegate_ `DECLARE_DELEGATE(FOnLogoutCompleteDelegate);`
- L74 _prototype_ `DECLARE_DELEGATE(FOnLogoutCompleteDelegate);` (scope `UE::MetaHuman::ServiceAuthentication`)
- L77 _prototype_ `void InitialiseAuthEnvironment(TSharedPtr<TArray<uint8>> EnvData);` (scope `UE::MetaHuman::ServiceAuthentication`) — initialise auth services environment and (if needed) extra data
- L79 _prototype_ `void ShutdownAuthEnvironment();` (scope `UE::MetaHuman::ServiceAuthentication`) — shut down the auth environment cleanly (can only be called *once*)
- L81 _prototype_ `void CheckHasLoggedInUserAsync(FOnCheckHasLoggedInUserCompleteDelegate&& OnCheckHasLoggedInUserCompleteDelegate);` (scope `UE::MetaHuman::ServiceAuthentication`) — checks if a user is logged in
- L83 _prototype_ `void LoginToAuthEnvironment(FOnLoginCompleteDelegate&& OnLoginCompleteDelegate, FOnLoginFailedDelegate&& OnLoginFailedDelegate);` (scope `UE::MetaHuman::ServiceAuthentication`) — log in to the active service auth environment - this function is intended for test purposes
- L85 _prototype_ `void LogoutFromAuthEnvironment(FOnLogoutCompleteDelegate&& OnLogoutCompleteDelegate);` (scope `UE::MetaHuman::ServiceAuthentication`) — log out of the active service auth environment - this function is intended for test purposes
- L87 _prototype_ `void TickAuthClient();` (scope `UE::MetaHuman::ServiceAuthentication`) — tick the authentication client to ensure the login callbacks are triggered. This is only needed for blocking calls that require waiting on cloud requests

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Cloud/MetaHumanTDSUtils.h` (Public)


#### struct `UE::MetaHuman::TDSUtils::FMetaHumanTDSAcquiredAccountInfo`  
`struct FMetaHumanTDSAcquiredAccountInfo`  
_L24-29_
- desc: Information about the acquired account.
- L26 _public member_ `FString EpicAccountId;`
- L27 _public member_ `FString Email;`
- L28 _public member_ `FString Password;`

#### class `UE::MetaHuman::TDSUtils::FExchangeCodeHandler`  
`class FExchangeCodeHandler`  
_L47-72_
- desc: Utility struct to help with obtaining TDS exchange code and setting it on the MetaHumanSDK for user authentication. Runs all of the HTTP requests synchronously. Note that the exchange code only lasts for a short period of time, so be sure to trigger the authentication code within that time frame.
- L50 _public prototype_ `FExchangeCodeHandler(const FString& InTemplateHost, const FString& InTemplateName, const FString& InClientId);`
- L51 _public prototype_ `virtual ~FExchangeCodeHandler();`
- L57 _public prototype_ `void Acquire();` — Locks in the first available TDS account to use for authentication. Next, it will obtain exchange code and store it, so exchange code authentication after that point should be possible.
- L62 _public prototype_ `bool HasExchangeCode() const;` — Returns true if exchange code was set successfully, otherwise false.
- L67 _public prototype_ `void Release();` — Returns the acquired TDS account back to the pool and clears the exchange code.
- L71 _private member_ `TUniquePtr<FImpl> Impl;`

#### class `UE::MetaHuman::TDSUtils::FScopedExchangeCodeHandler`  
`class FScopedExchangeCodeHandler : public FExchangeCodeHandler`  
_L77-82_
- inherits: `FExchangeCodeHandler`
- desc: Same as FExchangeCodeHandler, just scoped (ctor - acquire account, dtor - release account).
- L80 _public prototype_ `FScopedExchangeCodeHandler(const FString& InTemplateHost, const FString& InTemplateName, const FString& InClientId);`
- L81 _public prototype_ `virtual ~FScopedExchangeCodeHandler();`

#### class `UMetaHumanTDSUtils`  
`class UMetaHumanTDSUtils : public UBlueprintFunctionLibrary`  
_L89-114_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Utility class for acquiring and releasing TDS accounts.
- L103 _public prototype_ `static FString AcquireTdsAccount(const FString& InTemplateHost, const FString& InTemplateName, const FString& InClientId = FString(TEXT("")));` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|TDS")` — Acquires a TDS account and sets the exchange code to be used for authentication. @param InTemplateHost	Address of the TDS service @param InTemplateName	Template name of the TDS account @param InClientId	Service application ID to target. Set to empty to use the default @return	Accound ID of acquired TDS account.
- L113 _public prototype_ `static bool ReleaseTdsAccount(const FString& InTemplateHost, const FString& InAccountId);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|TDS")` — Releases the account back to the pool. @param InTemplateHost	Address of the TDS service @param InAccountId	Account ID to release @return True if account was released, false otherwise

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanTDSUtils, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanTDSUtils, Log, All);`
- L14 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace MetaHuman` (scope `UE`)
- L19 _namespace_ `namespace TDSUtils` (scope `UE::MetaHuman`)
- L31 _typedef_ `using FTdsAcquireAccountResult = TValueOrError<FMetaHumanTDSAcquiredAccountInfo, FString>;` (scope `UE::MetaHuman::TDSUtils`)
- L32 _prototype_ `TFuture<FTdsAcquireAccountResult> AcquireAccount(const FString& InTemplateHost, const FString& InTemplateName);` (scope `UE::MetaHuman::TDSUtils`)
- L34 _typedef_ `using FTdsGetExchangeCodeResult = TValueOrError<FString, FString>;` (scope `UE::MetaHuman::TDSUtils`)
- L35 _prototype_ `TFuture<FTdsGetExchangeCodeResult> GetExchangeCode(const FString& InTemplateHost, const FString& InAccountId, const FString& InClientId);` (scope `UE::MetaHuman::TDSUtils`)
- L37 _typedef_ `using FTdsReleaseAccountResult = TValueOrError<void, FString>;` (scope `UE::MetaHuman::TDSUtils`)
- L38 _prototype_ `TFuture<FTdsReleaseAccountResult> ReleaseAccount(const FString& InTemplateHost, const FString& InAccountId);` (scope `UE::MetaHuman::TDSUtils`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Cloud/MetaHumanTextureSynthesisServiceRequest.h` (Public)


#### class `UE::MetaHuman::THighFrequencyData`  
`template<typename EnumType UE_REQUIRES(TIsEnumClass<EnumType>::Value)> class THighFrequencyData : public TSharedFromThis<THighFrequencyData<EnumType>, ESPMode::ThreadSafe>`  
_L18-37_
- inherits: `TSharedFromThis<THighFrequencyData<EnumType>,ESPMode::ThreadSafe>`
- L21 _public function_ `THighFrequencyData()`
- L25 _public function_ `TConstArrayView<uint8> operator[](EnumType Type) const`
- L30 _public function_ `TArray<uint8>& GetMutable(EnumType Type)`
- L35 _private typedef_ `using FHighFrequencyDataArray = TStaticArray<TArray<uint8>, static_cast<uint32>(EnumType::Count)>;`
- L36 _private member_ `FHighFrequencyDataArray HighFrequencyDataArray;`

#### struct `UE::MetaHuman::TTextureRequestParams`  
`template<typename EnumType UE_REQUIRES(TIsEnumClass<EnumType>::Value)> struct TTextureRequestParams`  
_L40-44_
- L42 _public member_ `EnumType Type;`
- L43 _public member_ `int32 Resolution;`

#### struct `UE::MetaHuman::FFaceTextureRequestCreateParams`  
`struct FFaceTextureRequestCreateParams`  
_L50-54_
- desc: creation parameters for a request for (potentially) multiple face textures for a given high frequency ID
- L53 _public member_ `int32 HighFrequency;` — must be in the range [0, FMetaHumanFaceTextureSynthesizer::GetMaxHighFrequencyIndex() - 1]

#### struct `UE::MetaHuman::FBodyTextureRequestCreateParams`  
`struct FBodyTextureRequestCreateParams`  
_L56-60_
- desc: creation parameters for a request for (potentially) multiple body textures
- L58 _public member_ `int32 SurfaceMap;`
- L59 _public member_ `int32 Tone;`

#### class `UE::MetaHuman::detail::FTextureSynthesisServiceRequestBase`  
`class FTextureSynthesisServiceRequestBase : public FMetaHumanServiceRequestBase`  
_L68-86_
- inherits: `FMetaHumanServiceRequestBase`
- desc: base class for texture face, body, and chest synthesis request types
- L73 _public prototype_ `static TSharedRef<FFaceTextureSynthesisServiceRequest> CreateRequest(const FFaceTextureRequestCreateParams& Params);` — create a request instance that can live for long enough
- L75 _public prototype_ `static TSharedRef<FBodyTextureSynthesisServiceRequest> CreateRequest(const FBodyTextureRequestCreateParams& Params);` — create a request instance that can live for long enough
- L77 _protected prototype_ `FTextureSynthesisServiceRequestBase() = default;`
- L79 _protected member_ `TPimplPtr<FImpl> Impl;`
- L81 _protected prototype_ `bool CheckCanRequest();`
- L83 _protected prototype_ `virtual bool DoBuildRequest(TSharedRef<IHttpRequest> HttpRequest, FRequestContextBasePtr Context) override;`
- L84 _protected prototype_ `virtual bool DoBuildRequestImpl(FString& InOutRequestUrl, TSharedRef<IHttpRequest> HttpRequest, FRequestContextBasePtr Context) = 0;`
- L85 _protected prototype_ `virtual void OnRequestFailed(EMetaHumanServiceRequestResult Result, FRequestContextBasePtr MaybeContext) override;`

#### class `UE::MetaHuman::FFaceTextureSynthesisServiceRequest`  
`class FFaceTextureSynthesisServiceRequest final : public detail::FTextureSynthesisServiceRequestBase`  
_L92-111_
- inherits: `detail::FTextureSynthesisServiceRequestBase`
- desc: A face texture synthesis service request
- L96 _public prototype_ `FFaceTextureSynthesisServiceRequest() = default;`
- L99 _public prototype_ `DECLARE_DELEGATE_OneParam(FFaceTextureSynthesisRequestCompleteDelegate, TSharedPtr<FFaceHighFrequencyData> FaceHighFrequencyData);` — this delegate is invoked for each completed synthesis request
- L100 _public member_ `FFaceTextureSynthesisRequestCompleteDelegate FaceTextureSynthesisRequestCompleteDelegate;`
- L104 _public prototype_ `void RequestTexturesAsync(TConstArrayView<FFaceTextureRequestParams> TexturesToRequestParams);` — Issue requests for the given list of texture types NOTE that only ONE success OR ONE failure callback will be invoked
- L107 _protected prototype_ `virtual void OnRequestCompleted(const TArray<uint8>& Response, FRequestContextBasePtr Context) override;`
- L108 _protected prototype_ `virtual bool DoBuildRequestImpl(FString& InOutRequestUrl, TSharedRef<IHttpRequest> HttpRequest, FRequestContextBasePtr Context) override;`
- L110 _private prototype_ `void UpdateHighFrequencyFaceTextureCacheAsync(FRequestContextBasePtr Context);`

#### class `UE::MetaHuman::FBodyTextureSynthesisServiceRequest`  
`class FBodyTextureSynthesisServiceRequest final : public detail::FTextureSynthesisServiceRequestBase`  
_L116-135_
- inherits: `detail::FTextureSynthesisServiceRequestBase`
- desc: A body texture synthesis service request
- L120 _public prototype_ `FBodyTextureSynthesisServiceRequest() = default;`
- L123 _public prototype_ `DECLARE_DELEGATE_OneParam(FBodyTextureSynthesisRequestCompleteDelegate, TSharedPtr<FBodyHighFrequencyData> BodyHighFrequencyData);` — this delegate is invoked for each completed synthesis request
- L124 _public member_ `FBodyTextureSynthesisRequestCompleteDelegate BodyTextureSynthesisRequestCompleteDelegate;`
- L128 _public prototype_ `void RequestTexturesAsync(TConstArrayView<FBodyTextureRequestParams> TexturesToRequestParams);` — Issue requests for the given list of texture types NOTE that only ONE success OR ONE failure callback will be invoked
- L131 _protected prototype_ `virtual void OnRequestCompleted(const TArray<uint8>& Response, FRequestContextBasePtr Context) override;`
- L132 _protected prototype_ `virtual bool DoBuildRequestImpl(FString& InOutRequestUrl, TSharedRef<IHttpRequest> HttpRequest, FRequestContextBasePtr Context) override;`
- L134 _private prototype_ `void UpdateHighFrequencyBodyTextureCacheAsync(FRequestContextBasePtr Context);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace MetaHuman` (scope `UE`)
- L46 _typedef_ `using FFaceHighFrequencyData = THighFrequencyData<EFaceTextureType>;` (scope `UE::MetaHuman`)
- L47 _typedef_ `using FBodyHighFrequencyData = THighFrequencyData<EBodyTextureType>;` (scope `UE::MetaHuman`)
- L62 _typedef_ `using FFaceTextureRequestParams = TTextureRequestParams<EFaceTextureType>;` (scope `UE::MetaHuman`)
- L63 _typedef_ `using FBodyTextureRequestParams = TTextureRequestParams<EBodyTextureType>;` (scope `UE::MetaHuman`)
- L65 _namespace_ `namespace detail` (scope `UE::MetaHuman`)
- L99 _delegate_ `DECLARE_DELEGATE_OneParam(FFaceTextureSynthesisRequestCompleteDelegate, TSharedPtr<FFaceHighFrequencyData> FaceHighFrequencyData);` — this delegate is invoked for each completed synthesis request
- L123 _delegate_ `DECLARE_DELEGATE_OneParam(FBodyTextureSynthesisRequestCompleteDelegate, TSharedPtr<FBodyHighFrequencyData> BodyHighFrequencyData);` — this delegate is invoked for each completed synthesis request

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Import/MetaHumanAssetUpdateHandler.h` (Public)


#### class `UE::MetaHuman::FMetaHumanAssetUpdateHandler`  
`class FMetaHumanAssetUpdateHandler`  
_L18-36_
- desc: Class that handles the actual import and update of assets asynchronously on the correct thread and in the correct tick phase.
- L26 _public prototype_ `static TFuture<bool> Enqueue(const FMetaHumanImportDescription& ImportDescription);` — Enqueues an import operation to occur on the main game thread during the correct tick phase @param ImportDescription The parameters for the import operation @param Report The Asset Report to use for this operation. Lifetime must be handled by the caller
- L31 _public prototype_ `static void Shutdown();` — Shuts down the queue cancelling any in-flight requests
- L34 _private prototype_ `FMetaHumanAssetUpdateHandler() = default;`
- L35 _private member_ `static TUniquePtr<FMetaHumanAssetUpdateHandlerImpl> Instance;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Import/MetaHumanImport.h` (Public)


#### class `UE::MetaHuman::IMetaHumanImportAutomationHandler`  
`class IMetaHumanImportAutomationHandler`  
_L27-39_
- desc: Interface for classes handling automation of the MetaHuman import process for e.g. scripting and tests
- L30 _public prototype_ `virtual ~IMetaHumanImportAutomationHandler() = default;`
- L38 _public prototype_ `virtual bool ShouldContinueWithBreakingMetaHumans(const TArray<FString>& IncompatibleMetaHumans, const TArray<FString>& UpdatedFiles) = 0;` — @param IncompatibleMetaHumans Array of names of MetaHumans in project that are not compatible with the requested import @param UpdatedFiles Array of filenames of the assets that would be updated by the requested import @return Whether to continue with the import process

#### class `UE::MetaHuman::IMetaHumanBulkImportHandler`  
`class IMetaHumanBulkImportHandler`  
_L45-56_
- desc: Interface for classes handling the processing of bulk import operations. The only supported implementation is for Quixel Bridge to handle the "re-import all MetaHumans" operation.
- L48 _public prototype_ `virtual ~IMetaHumanBulkImportHandler() = default;`
- L55 _public prototype_ `virtual void DoBulkImport(const TArray<FString>& MetaHumanIds) = 0;` — This is an asynchronous operation. This function must return immediately and the import operation that called it will then immediately terminate. @param MetaHumanIds A list of the Quixel IDs of the MetaHumans to be imported

#### struct `UE::MetaHuman::FQuixelAccountMetaHumanEntry`  
`struct FQuixelAccountMetaHumanEntry`  
_L61-67_
- desc: Struct describing a MetaHuman item in QuixelBridge
- L63 _public member_ `FString Name;` — MetaHuman name
- L64 _public member_ `FString Id;` — Quixel ID
- L65 _public member_ `bool bIsLegacy;` — Does this MetaHuman require an Upgrade before it can be used
- L66 _public member_ `FString Version;` — The version of MHC used to create this character

#### struct `UE::MetaHuman::FMetaHumanImportDescription`  
`struct FMetaHumanImportDescription`  
_L72-89_
- desc: Struct giving parameters for an import operation for a MetaHuman character
- L74 _public member_ `inline static const FString DefaultDestinationPath = TEXT("/Ga`
- L76 _public member_ `FString CharacterPath;` — The file path to the source unique assets for this import operation
- L77 _public member_ `FString CommonPath;` — The file path to the source common assets for this import operation
- L78 _public member_ `FString CharacterName;` — The name of the MetaHuman to import (expected to match the final part of CharacterPath)
- L79 _public member_ `FString QuixelId;` — The ID of the character being imported
- L80 _public member_ `bool bIsBatchImport;` — If this is part of a batch import
- L81 _public member_ `FString SourcePath = DefaultDestinationPath;` — The asset path that the exporter has written the assets out to
- L82 _public member_ `FString DestinationPath = DefaultDestinationPath;` — The asset path to install the MetaHuman to in the project
- L83 _public member_ `TArray<FQuixelAccountMetaHumanEntry> AccountMetaHumans;` — All the MetaHumans that are included in the user's account. Used to show which MetaHumans can be upgraded
- L84 _public member_ `bool bForceUpdate = false;` — Ignore asset version metadata and update all assets
- L85 _public member_ `bool bWarnOnQualityChange = false;` — Warn if the user is importing a MetaHuman at a different quality level to the existing MetaHuman in the scene.
- L86 _public member_ `TSharedPtr<FZipArchiveReader> Archive = nullptr;` — If present, import from this archive rather than the CharacterPath
- L87 _public member_ `UMetaHumanAssetReport* Report = nullptr;` — If present, log messages to this report
- L88 _public member_ `TMap<FString, FString> PackageRedirects;` — Archive-relative package path -> original source package path. Used to fix up references for remapped external dependencies.

#### struct `UE::MetaHuman::FFileSource`  
`struct FFileSource`  
_L94-133_
- desc: Struct describing the source of a set of files to import as a MetaHuman Asset Group
- L107 _public prototype_ `FFileSource(const FString& FilePath);` — Constructs a FileSource that is a local folder on disk @param FilePath The file path to use to resolve relative paths to source files
- L113 _public prototype_ `FFileSource(const TSharedPtr<FZipArchiveReader>& Archive, const FString& FilePath=TEXT(""));` — Constructs a FileSource that is a zip file @param Archive The zip archive containing files
- L120 _public prototype_ `ECopyResult CopySingleFile(const FString& SourceFilePath, const FString& DestinationFilePath) const;` — @param SourceFilePath The relative path to the source file @param DestinationFilePath The absolute path to copy the source file to @return The status of the copy operation
- L127 _public prototype_ `TSharedPtr<FJsonObject> ReadJson(const FString& SourceFilePath) const;` — @param SourceFilePath The relative path to the JSON file @return The JsonObject if loaded correctly, nullptr otherwise
- L130 _private member_ `TVariant<FString, TSharedPtr<FZipArchiveReader>> Root;`
- L132 _private member_ `FString SubFolder;`

#### enum `UE::MetaHuman::FFileSource::ECopyResult`  
`enum class ECopyResult: uint32`  
_L96-101_
- L98 _public enumerator_ `Success`
- L99 _public enumerator_ `MissingSource`
- L100 _public enumerator_ `Failure`

#### struct `UE::MetaHuman::FAssetGroupImportDescription`  
`struct FAssetGroupImportDescription`  
_L138-146_
- desc: Struct giving parameters for an import operation for an Asset Group
- L140 _public member_ `FString Name;` — The Name of the AssetGroup
- L141 _public member_ `FString TargetRootAssetPath;` — The target asset path to import to. e.g. /Game/Folder/MyGrooms
- L142 _public member_ `FString SourceRootAssetPath;` — The path to the assets in their source project
- L143 _public member_ `FFileSource FileSource;` — The FileSource containing the asset group
- L144 _public member_ `UMetaHumanAssetReport* Report;` — The Report to populate with the results of the import operation
- L145 _public member_ `TMap<FString, FString> PackageRedirects;` — Archive-relative package path -> original source package path. Used to fix up references for remapped external dependencies.

#### class `UE::MetaHuman::FMetaHumanImport`  
`class FMetaHumanImport`  
_L151-208_
- desc: Utility class handling the import or MetaHumans into a project.
- L155 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnImportStarted, const FSourceMetaHuman& InSourceMetaHuman);` — Delegate called when a MetaHuman starts being imported into the project. If this delegate is bound and returns false it will skip the import process
- L156 _public member_ `FOnImportStarted OnImportStartedDelegate;`
- L159 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnShouldImportAssetOrFile, const FSourceMetaHuman& InSourceMetaHuman, const FString& InDestPath, bool bInIsFile);` — Delegate called to check if given asset or file should be imported. This can be used to import a subset of assets of files into the project
- L160 _public member_ `FOnShouldImportAssetOrFile OnShouldImportAssetOrFileDelegate;`
- L163 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnImportEnded, const FSourceMetaHuman& InSourceMetaHuman, const FInstalledMetaHuman& InTargetMetaHuman);` — Delegate called at the end of the import process. It can be used to perform extra processing on the assets and files that were imported
- L164 _public member_ `FOnImportEnded OnImportEndedDelegate;`
- L173 _public prototype_ `TOptional<UObject*> ImportMetaHuman(const FMetaHumanImportDescription& ImportDescription) const;` — This method imports a MetaHuman into a project, handling asset unloading and re-loading and warning the user of any asset-version mismatches for assets shared by multiple MetaHumans in the project. @param ImportDescription the parameters for the import @return The main asset for the imported item
- L182 _public prototype_ `TOptional<UObject*> ImportAssetGroup(const FAssetGroupImportDescription ImportDescription) const;` — This method imports an AssetGroup into a project, handling asset unloading and re-loading. @param ImportDescription the parameters for the import @return The main asset for the imported item
- L188 _public prototype_ `void SetAutomationHandler(IMetaHumanImportAutomationHandler* Handler);` — @param Handler the automation handler to be used for subsequent calls to ImportMetaHuman
- L195 _public prototype_ `void SetBulkImportHandler(IMetaHumanBulkImportHandler* Handler);` — @param Handler bulk import handler to be used if a version conflict requiring the bulk import of multiple MetaHumans is required.
- L201 _public prototype_ `static TSharedPtr<FMetaHumanImport> Get();` — @return Get the singleton instance of this class
- L204 _private prototype_ `FMetaHumanImport() = default;`
- L205 _private member_ `IMetaHumanImportAutomationHandler* AutomationHandler{nullptr};`
- L206 _private member_ `IMetaHumanBulkImportHandler* BulkImportHandler{nullptr};`
- L207 _private member_ `static TSharedPtr<FMetaHumanImport> MetaHumanImportInst;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace MetaHuman` (scope `UE`)
- L155 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnImportStarted, const FSourceMetaHuman& InSourceMetaHuman);` — Delegate called when a MetaHuman starts being imported into the project. If this delegate is bound and returns false it will skip the import process
- L159 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnShouldImportAssetOrFile, const FSourceMetaHuman& InSourceMetaHuman, const FString& InDestPath, bool bInIsFile);` — Delegate called to check if given asset or file should be imported. This can be used to import a subset of assets of files into the project
- L163 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnImportEnded, const FSourceMetaHuman& InSourceMetaHuman, const FInstalledMetaHuman& InTargetMetaHuman);` — Delegate called at the end of the import process. It can be used to perform extra processing on the assets and files that were imported

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/MetaHumanAssetReport.h` (Public)


#### enum `EMetaHumanOperationResult`  
`enum class EMetaHumanOperationResult : uint8`  
_L12-16_
- reflection: `UENUM(BlueprintType)`
- desc: The status of an operation represented by a report
- L14 _public enumerator_ `Success`
- L15 _public enumerator_ `Failure`

#### struct `FMetaHumanAssetReportItem`  
`struct FMetaHumanAssetReportItem`  
_L20-35_
- reflection: `USTRUCT(BlueprintType)`
- desc: A line in a report representing some Info, a Warning or an Error. Can optionally reference a specific item or file.
- L26 _public member_ `FText Message;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " MetaHuman SDK | Reports ")` — The message to display to the user
- L30 _public member_ `TObjectPtr<const UObject> ProjectItem = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " MetaHuman SDK | Reports ")` — The relevant object (if any) in the project to which this message relates
- L34 _public member_ `FString SourceItem;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " MetaHuman SDK | Reports ")` — The file path (if any) to which this message relates

#### class `UMetaHumanAssetReport`  
`class UMetaHumanAssetReport : public UObject`  
_L40-162_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: A report generated when an asset is imported or tested for MetaHuman compatibility
- L51 _public prototype_ `void SetSubject(const FString& InSubject);` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Reports ")` — Set the subject for the report, typically the name of the asset being tested or imported @param InSubject The Name to appear in the title of the report
- L60 _public prototype_ `void AddVerbose(const FMetaHumanAssetReportItem& Message);` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Reports ")` — Adds a user-facing message to appear in the report. This will not flag the report as containing warnings or as having failed and will be discarded if SetVerbose is not called with a value of true @param Message The localized informational message
- L69 _public prototype_ `void AddInfo(const FMetaHumanAssetReportItem& Message);` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Reports ")` — Adds a user-facing message to appear in the report. This will not flag the report as containing warnings or as having failed. @param Message The localized informational message
- L78 _public prototype_ `void AddWarning(const FMetaHumanAssetReportItem& Message);` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Reports ")` — Adds a user-facing message to appear in the report. This will flag the report as containing warnings but will not flag it as having failed. @param Message The localized warning message
- L87 _public prototype_ `void AddError(const FMetaHumanAssetReportItem& Message);` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Reports ")` — Adds a user-facing message to appear in the report. This will flag the report as containing warnings and as having failed. @param Message The localized error message
- L91 _public prototype_ `FString GenerateHtmlReport() const;` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Reports ")` — Generates an HTML representation of the report
- L95 _public prototype_ `FString GenerateJsonReport() const;` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Reports ")` — Generates a JSON representation of the report
- L99 _public prototype_ `FString GenerateRawReport() const;` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Reports ")` — Generates a plain text representation of the report
- L103 _public prototype_ `FText GenerateRichTextReport() const;` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Reports ")` — Generates a representation of the report suitable for use in an SRichText control
- L106 _public prototype_ `TArray<TSharedRef<class FTokenizedMessage>> GenerateTokenizedMessageReport() const;` — Generates a representation of the report suitable for use with the MessageLog
- L110 _public prototype_ `EMetaHumanOperationResult GetReportResult() const;` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Reports ")` — Determine whether the report represents a successful operation or not
- L114 _public prototype_ `bool HasWarnings() const;` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Reports ")` — Determine whether the report contains non-informational messages
- L120 _public prototype_ `void SetWarningsAsErrors(const bool Value);` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Reports ")` — Set whether warnings should be reported as errors
- L126 _public prototype_ `void SetVerbose(const bool Value);` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Reports ")` — Set whether to include verbose items in the report
- L132 _public prototype_ `void SetSilent(const bool Value);` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Reports ")` — Suppress logging of messages from the report
- L138 _public member_ `FString Subject;` — `UPROPERTY()` — The Subject of the Report
- L144 _public member_ `TArray<FMetaHumanAssetReportItem> Infos;` — `UPROPERTY()` — The Info Items in the Report
- L150 _public member_ `TArray<FMetaHumanAssetReportItem> Warnings;` — `UPROPERTY()` — The Warnings in the Report
- L156 _public member_ `TArray<FMetaHumanAssetReportItem> Errors;` — `UPROPERTY()` — The Errors in the Report
- L159 _private member_ `bool bWarningsAsErrors = false;`
- L160 _private member_ `bool bVerbose = false;`
- L161 _private member_ `bool bSilent = false;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/MetaHumanSDKEditor.h` (Public)


#### Free symbols / members of external scopes

- L5 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanSDK, Log, All);`
- L5 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanSDK, Log, All);`
- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MetaHuman` (scope `UE`)
- L10 _externvar_ `extern const FName MessageLogName;` (scope `UE::MetaHuman`)
- L12 _prototype_ `void AnalyticsEvent(FString&& EventName, const TArray<FAnalyticsEventAttribute>& Attributes = {});` (scope `UE::MetaHuman`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/MetaHumanSDKSettings.h` (Public)


#### class `UMetaHumanSDKSettings`  
`class UMetaHumanSDKSettings : public UObject`  
_L13-53_
- reflection: `UCLASS(MinimalAPI, defaultconfig, config = MetaHumanSDK, meta = (DisplayName = "MetaHuman SDK"))`
- inherits: `UObject`
- desc: Project Settings for the MetaHuman SDK
- L20 _public member_ `FString VersionServiceBaseUrl;` — `UPROPERTY(Config)` — The URL for fetching version information and release notes
- L24 _public member_ `FSoftObjectPath DefaultDNAPipelinePath{ TEXT("/Meta` — `UPROPERTY(EditAnywhere, Config, Category = "DNA Interchange", meta = (AllowedClasses = "/Script/InterchangePipelines.InterchangeGenericAssetsPipeline", DisplayName = "Default DNA Pipeline"))` — The Interchange pipeline asset used when generating Skeletal Meshes from DNA assets
- L28 _public member_ `FDirectoryPath CinematicImportPath{TEXT("/Gam` — `UPROPERTY(EditAnywhere, Config, Category = "MetaHuman Import Paths", meta = (ContentDir, DisplayName = "Cinematic Characters"))` — The asset path for importing Cinematic MetaHumans.
- L32 _public member_ `FDirectoryPath OptimizedImportPath{TEXT("/Gam` — `UPROPERTY(EditAnywhere, Config, Category = "MetaHuman Import Paths", meta = (ContentDir, DisplayName = "Optimized Characters"))` — The asset path for importing Optimized MetaHumans.
- L36 _public member_ `FDirectoryPath CharacterAssetPackagingPath{TEXT("/Gam` — `UPROPERTY(Config, meta = (DeprecatedProperty, DeprecationMessage = "Per-type packaging paths are no longer honored; packageable assets are discovered across all of /Game/."))` — The asset path for finding Editable MetaHuman Character Assets for Packaging.
- L40 _public member_ `FDirectoryPath CharacterAssemblyPackagingPath{TEXT("/Gam` — `UPROPERTY(Config, meta = (DeprecatedProperty, DeprecationMessage = "Per-type packaging paths are no longer honored; packageable assets are discovered across all of /Game/."))` — The asset path for finding MetaHuman Character Assemblies for Packaging.
- L44 _public member_ `FDirectoryPath SkeletalClothingPackagingPath{TEXT("/Gam` — `UPROPERTY(EditAnywhere, Config, Category = "MetaHuman Packaging Paths", meta = (ContentDir, DisplayName = "Skeletal Clothing"))` — The asset path for finding MetaHuman Skeletal Clothing Assets for Packaging.
- L48 _public member_ `FDirectoryPath OutfitPackagingPath{TEXT("/Gam` — `UPROPERTY(Config, meta = (DeprecatedProperty, DeprecationMessage = "Per-type packaging paths are no longer honored; packageable assets are discovered across all of /Game/."))` — The asset path for finding MetaHuman Outfit-based Clothing Assets for Packaging.
- L52 _public member_ `FDirectoryPath GroomPackagingPath{TEXT("/Gam` — `UPROPERTY(Config, meta = (DeprecatedProperty, DeprecationMessage = "Per-type packaging paths are no longer honored; packageable assets are discovered across all of /Game/."))` — The asset path for finding MetaHuman Groom Assets for Packaging.

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/MetaHumanTypesEditor.h` (Public)


#### struct `UE::MetaHuman::FImportPaths`  
`struct FImportPaths`  
_L16-79_
- desc: Helper structure describing the normal file and asset structure for Legacy MetaHumans. Used during the import of a MetaHuman to a project
- L18 _public member_ `inline static const FString MetaHumansFolderName = TEXT("Met`
- L19 _public member_ `inline static const FString CommonFolderName = TEXT("Com`
- L22 _public prototype_ `explicit FImportPaths(const FString& InSourceRootFilePath, const FString& InSourceAssetPath, const FString& InDestinationCommonAssetPath, const FString& InDestinationCharacterAssetPath);` — Construction
- L28 _public prototype_ `static FString FilenameToAssetName(const FString& Filename);` — @param Filename The name of a file containing an asset that is part of a MetaHuman asset group @return The default name of the asset contained in that file
- L34 _public prototype_ `static FString AssetNameToFilename(const FString& AssetName);` — @param AssetName The name an asset that is part of a MetaHuman asset group @return The default name of the file containing that asset
- L41 _public prototype_ `FString CharacterNameToBlueprintAssetPath(const FString& CharacterName) const;` — Convert from the name of the MetaHuman to the default name for the main Blueprint Asset @param CharacterName The MetaHuman Name to convert @return The name of the default blueprint asset
- L48 _public prototype_ `FString GetSourceFile(const FString& RelativeFilePath) const;` — Given a relative path from the manifest, calculate the full path to the corresponding source file. @param RelativeFilePath The path relative to the root @return The full path to the source file
- L55 _public prototype_ `FString GetDestinationFile(const FString& RelativeFilePath) const;` — Given a relative path from the manifest, calculate the full path to the corresponding destination file. @param RelativeFilePath The path relative to the root @return The full path to the destination file
- L62 _public prototype_ `FString GetDestinationPackage(const FString& RelativeFilePath) const;` — Given a relative path from the manifest, calculate the full asset path to the corresponding destination package. @param RelativeFilePath The path relative to the root @return The full asset path to the destination package
- L69 _public prototype_ `FString GetSourcePackage(const FString& RelativeFilePath) const;` — Given a relative path from the manifest, calculate the full asset path to the corresponding source package. @param RelativeFilePath The path relative to the root @return The full asset path to the source package
- L71 _public member_ `FString SourceRootFilePath;`
- L72 _public member_ `FString SourceRootAssetPath;`
- L74 _public member_ `FString DestinationCharacterRootFilePath;`
- L75 _public member_ `FString DestinationCharacterFilePath;`
- L76 _public member_ `FString DestinationCommonFilePath;`
- L77 _public member_ `FString DestinationCharacterAssetPath;`
- L78 _public member_ `FString DestinationCommonAssetPath;`

#### struct `UE::MetaHuman::FMetaHumanVersion`  
`struct FMetaHumanVersion`  
_L83-132_
- desc: Representation of a MetaHuman Version. This is a simple semantic-versioning style version number that is stored in a Json file at a specific location in the directory structure that MetaHumans use.
- L86 _public prototype_ `FMetaHumanVersion() = default;` — Currently default initialisation == 0.0.0 which is not a valid version.
- L89 _public prototype_ `explicit FMetaHumanVersion(const FString& VersionString);` — Construction
- L90 _public prototype_ `explicit FMetaHumanVersion(const int InMajor, const int InMinor, const int InRevision);`
- L107 _public prototype_ `bool IsCompatible(const FMetaHumanVersion& Other) const;` — Check for asset compatibility (major version matches) between two MetaHumans @param Other The other MetaHuman to compare against
- L113 _public prototype_ `FString AsString() const;` — Converts the Version to a string. @return The canonical string representation of the MetaHuman version.
- L120 _public prototype_ `static FMetaHumanVersion ReadFromFile(const FString& VersionFilePath);` — Reads the MetaHuman Version from the file that comes with an exported MetaHuman @param VersionFilePath Path to the VersionInfo.txt file that is part of an exported MetaHuman @return The MetaHumanVersion contained in the file
- L127 _public prototype_ `static FMetaHumanVersion ReadFromArchive(const FString& VersionFilePath, FZipArchiveReader* Archive);` — Reads the MetaHuman Version from the file that comes with a MetaHuman that is packaged in a MetaHuman archive @param VersionFilePath Path to the VersionInfo.txt file that is part of a MetaHuman package @return The MetaHumanVersion contained in the file
- L129 _public member_ `int32 Major = 0;`
- L130 _public member_ `int32 Minor = 0;`
- L131 _public member_ `int32 Revision = 0;`

#### struct `UE::MetaHuman::FMetaHumanAssetVersion`  
`struct FMetaHumanAssetVersion`  
_L137-162_
- desc: Represents the Asset Version stored in MetaData on MetaHuman assets. Major version changes imply breaking changes.
- L140 _public prototype_ `explicit FMetaHumanAssetVersion(const FString& VersionString);` — Construction
- L141 _public prototype_ `explicit FMetaHumanAssetVersion(const int InMajor, const int InMinor);`
- L158 _public prototype_ `FString AsString() const;` — Converts the Version to a string. @return The canonical string representation of the MetaHuman Asset version.
- L160 _public member_ `int32 Major = 0;`
- L161 _public member_ `int32 Minor = 0;`

#### class `UE::MetaHuman::FSourceMetaHuman`  
`class FSourceMetaHuman`  
_L166-204_
- desc: Class that handles the layout on-disk of a MetaHuman being used as the source of an Import operation Gives us a single place to handle simple path operations, filenames etc.
- L169 _public prototype_ `FSourceMetaHuman(const FString& InCharacterPath, const FString& InCommonPath, const FString& InName);`
- L170 _public prototype_ `FSourceMetaHuman(FZipArchiveReader* Reader);`
- L175 _public prototype_ `const FString GetSourceAssetsPath() const;` — @return The path to the source assets (i.e. DNA files) for this MetaHuman
- L180 _public prototype_ `const FString& GetName() const;` — @return The name of the MetaHuman
- L185 _public prototype_ `const FMetaHumanVersion& GetVersion() const;` — @return The MetaHuman version of this MetaHuman
- L190 _public prototype_ `bool IsUEFN() const;` — @return Is this MetaHuman exported for use in UEFN
- L195 _public prototype_ `EMetaHumanQualityLevel GetQualityLevel() const;` — @return The MetaHuman quality level that this MetaHuman was generated at
- L198 _private member_ `FString CharacterPath;`
- L199 _private member_ `FString CommonPath;`
- L200 _private member_ `FString Name;`
- L201 _private member_ `FMetaHumanVersion Version;`
- L202 _private member_ `bool bIsUEFN = false;`
- L203 _private member_ `EMetaHumanQualityLevel QualityLevel = EMetaHumanQualityLevel::Cinematic;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/ProjectUtilities/MetaHumanAssetManager.h` (Public)


#### struct `FMetaHumanImportOptions`  
`struct FMetaHumanImportOptions`  
_L22-34_
- reflection: `USTRUCT(BlueprintType)`
- desc: Options to apply during the import of a MetaHuman Asset Archive
- L27 _public member_ `bool bVerbose = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ImportOptions")`
- L33 _public member_ `bool bForceUpdate = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ImportOptions")` — Ignores version information and always replaces files in the project with files in the imported archive

#### enum `EMetaHumanAssetType`  
`enum class EMetaHumanAssetType : uint8`  
_L41-49_
- reflection: `UENUM(BlueprintType)`
- desc: Describes the types of MetaHuman Assets that can be managed and packaged
- L43 _public enumerator_ `Character`
- L44 _public enumerator_ `CharacterAssembly`
- L45 _public enumerator_ `SkeletalClothing`
- L46 _public enumerator_ `OutfitClothing`
- L47 _public enumerator_ `Groom`
- L48 _public enumerator_ `None`

#### struct `FMetaHumanAggregateDetails`  
`struct FMetaHumanAggregateDetails`  
_L56-214_
- reflection: `USTRUCT(BlueprintType)`
- desc: Details about the assets contained in a MetaHuman Package
- L66 _public member_ `bool bResizesWithBlendableBodies = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Clothing will resize to blendable bodies in UEMHC
- L72 _public member_ `bool bHasClothingMask = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Clothing has a mask for hidden face removal in UEMHC
- L78 _public member_ `int32 IncludedLods = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Which LODs are included for this item
- L84 _public member_ `int32 Lod0VertCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Vert Count for LOD0 (if single item in listing)
- L90 _public member_ `int32 NumUniqueClothingItems = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Number of clothing items
- L98 _public member_ `bool bContainsGrooms = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Does this character contain one or more grooms
- L104 _public member_ `bool bContainsClothing = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Does this character come with clothing
- L110 _public member_ `bool bIsEditableCharacter = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Is this a character a user can open up in UEMHC and edit?
- L116 _public member_ `TArray<EMetaHumanQualityLevel> PlatformsIncluded;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Cinematic and/or Optimized
- L122 _public member_ `int32 NumUniqueCharacters = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — How many Characters are included in this listing
- L128 _public member_ `int32 NumVirtualTextures = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Number of Virtual Textures in this package
- L134 _public member_ `int32 NumSubstrateMaterials = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Number of Substrate-only materials in this package
- L141 _public member_ `int32 NumUniqueGrooms = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Number of grooms
- L147 _public member_ `bool bPhysics = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Simulation enabled
- L153 _public member_ `int32 StrandsCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Number of curves
- L159 _public member_ `int32 StrandsPointCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Number of CVs
- L165 _public member_ `bool bHasLods = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — LODs available
- L171 _public member_ `int32 CardMeshCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Number of card assets
- L177 _public member_ `int32 CardMeshVertices = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Number of verts
- L183 _public member_ `FIntVector2 CardMeshTextureResolution = FIntVector2::ZeroValue;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Texture Atlas resolution
- L189 _public member_ `int32 VolumeMeshCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Number of meshes
- L195 _public member_ `int32 VolumeMeshVertices = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Number of verts
- L201 _public member_ `FIntVector2 VolumeMeshTextureResolution = FIntVector2::ZeroValue;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Textures resolution
- L207 _public member_ `int32 NumMaterials = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Number of material or material instances
- L213 _public member_ `FString EngineVersion;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — UE Version asset was packaged with

#### struct `FMetaHumanAssetDescription`  
`struct FMetaHumanAssetDescription`  
_L220-281_
- reflection: `USTRUCT(BlueprintType)`
- desc: Description of a MetaHuman asset including verification status
- L224 _public prototype_ `FMetaHumanAssetDescription() = default;`
- L225 _public prototype_ `FMetaHumanAssetDescription(const FAssetData& InAssetData, EMetaHumanAssetType InAssetType, const FName& DisplayName = FName());`
- L231 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — The display name for the Asset. Normally the name of the Root Asset.
- L237 _public member_ `FAssetData AssetData;` — `UPROPERTY(SkipSerialization, EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — The FAssetData describing the Root Asset
- L243 _public member_ `TArray<FName> DependentPackages;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — A list of all the packages included in the asset
- L249 _public member_ `EMetaHumanAssetType AssetType = EMetaHumanAssetType::CharacterAssembly;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — The asset type, i.e. Groom, Clothing, etc.
- L253 _public member_ `FMetaHumanAggregateDetails Details;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")`
- L259 _public member_ `int32 TotalSize = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — The total size of all assets
- L265 _public member_ `TObjectPtr<UMetaHumanAssetReport> VerificationReport;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Verification")` — If present, the verification report for this Asset
- L271 _public member_ `TSet<FName> ExcludedSubAssetRoots;` — Root packages of sub-assets excluded by the user (e.g. specific Grooms or Clothing). These are skipped during dependency walking for both verification and packaging.
- L280 _public member_ `TMap<FString, FString> PackageRedirects;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AssetDescription")` — Package path redirects for assets that were remapped into the archive. Key: archive-relative package path (e.g. "Ada/CaptainOutfit/OA_CaptainOutfit") Value: original source package path (e.g. "/Game/Outfits/CaptainOutfit/OA_CaptainOutfit") On import, these are registered as scoped FCoreRedirects so existing references resolve correctly.

#### struct `FMetaHumanMultiArchiveDescription`  
`struct FMetaHumanMultiArchiveDescription`  
_L287-296_
- reflection: `USTRUCT(BlueprintType)`
- desc: Description of the contents of a multi-item archive
- L295 _public member_ `TArray<FString> ContainedArchives;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ArchiveDescription")` — A list of all the sub-archives included in the archive

#### struct `FMetaHumanArchiveEntry`  
`struct FMetaHumanArchiveEntry`  
_L302-317_
- reflection: `USTRUCT(BlueprintType)`
- desc: A single item in a MetaHuman Archive
- L310 _public member_ `FString Path;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ArchiveContents")` — The path to this file relative to the root of the archive
- L316 _public member_ `FString Version;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ArchiveContents")` — The version of the file in format Major.Minor. If no version is available the version should be 0.0

#### struct `FMetaHumanArchiveContents`  
`struct FMetaHumanArchiveContents`  
_L323-329_
- reflection: `USTRUCT(BlueprintType)`
- desc: Description of the contents of a MetaHuman Archive
- L328 _public member_ `TArray<FMetaHumanArchiveEntry> Files;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ArchiveContents")`

#### struct `FMetaHumanExcludableSubAsset`  
`struct FMetaHumanExcludableSubAsset`  
_L335-348_
- desc: Describes an excludable sub-asset (e.g. a Groom or Clothing item) discovered within the dependency tree of a parent asset.
- L338 _public member_ `FName Name;` — Display name for UI presentation.
- L341 _public member_ `EMetaHumanAssetType AssetType = EMetaHumanAssetType::None;` — The asset type of this sub-asset.
- L344 _public member_ `FName RootPackage;` — The root package of this sub-asset.
- L347 _public member_ `bool bIncluded = true;` — Whether this sub-asset should be included in the package (default true).

#### class `UMetaHumanAssetManager`  
`class UMetaHumanAssetManager : public UBlueprintFunctionLibrary`  
_L354-468_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Manages MetaHuman characters and compatible assets in the project
- L366 _public prototype_ `static TArray<FMetaHumanAssetDescription> FindAssetsForPackaging(EMetaHumanAssetType AssetType);` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman | AssetManager ")` — Finds all assets in the project that ore of the correct type and in the correct location to be packaged @param AssetType The type of asset to find @return The found assets
- L377 _public prototype_ `static bool IsAssetOfType(const FName& RootPackage, EMetaHumanAssetType AssetType);` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman | AssetManager ")` — Performs some simple tests to see if an asset is of the correct type and in the correct location to be a Root Asset of the given type of MetaHuman Asset. @param RootPackage The Root Package of the asset to be tested @param AssetType The type of asset to be tested against @return Whether the asset is a packageable asset of the given type
- L386 _public prototype_ `static bool IsMetaHumanBodyCompatibleSkeleton(const USkeleton* ToTest);` — Tests whether the joint names and hierarchy in a skeleton match with those in the standard MetaHuman body skeleton @param ToTest The Skeleton to test @return whether ToTest is MetaHuman compatible
- L394 _public prototype_ `static bool IsMetaHumanFaceCompatibleSkeleton(const USkeleton* ToTest);` — Tests whether the joint names and hierarchy in a skeleton match with those in the standard MetaHuman face skeleton @param ToTest The Skeleton to test @return whether ToTest is MetaHuman compatible
- L404 _public prototype_ `static bool CreateArchive(const TArray<FMetaHumanAssetDescription>& Assets, const FString& ArchivePath);` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman | AssetManager ")` — Packages up the described MetaHuman Asset (including dependencies) into a zip file @param Assets The MetaHuman Assets to be packaged @param ArchivePath The file to package up to @return Whether the archive was successfully created
- L413 _public prototype_ `static FMetaHumanAssetDescription& UpdateAssetDependencies(UPARAM(ref) FMetaHumanAssetDescription& Asset);` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman | AssetManager ")` — Updates the stored package dependencies for a MetaHuman Asset @param Asset The MetaHuman Asset to update
- L423 _public prototype_ `static FMetaHumanAssetDescription& UpdateAssetDetails(UPARAM(ref) FMetaHumanAssetDescription& Asset);` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman | AssetManager ")` — Updates the stored asset details for a MetaHuman Asset @param Asset The MetaHuman Asset to update
- L434 _public prototype_ `static TFuture<bool> ImportArchive(const FString& ArchivePath, const FMetaHumanImportOptions& ImportOptions, UMetaHumanAssetReport* Report);` — Asynchronously imports a MetaHuman Asset in to a project @param ArchivePath The file to import @param ImportOptions Options such as whether to ignore version information @param Report A report to fill out with the information about the import operation @return a Future which will complete with the import status when the import is completed
- L442 _public prototype_ `static FString GetPackagingFolderForAssetType(const EMetaHumanAssetType AssetType);` — `UE_DEPRECATED(5.8, "Per-type packaging folders are no longer honored; packageable assets are discovered across all of /Game/.")` — Gives the root folder to use for discovering packageable Asset Groups @param AssetType The type of asset to get the folder for @return The root folder to use for discovering packageable Asset Groups of this type
- L449 _public prototype_ `static FTopLevelAssetPath GetMainAssetClassPathForAssetType(const EMetaHumanAssetType AssetType);` — Gives the UCLass corresponding to the main asset for an AssetGroup @param AssetType The type of asset to get the Class for @return The UCLass corresponding to the main asset for an AssetGroup of this type
- L457 _public prototype_ `static FName GetWardrobeItemPackage(FName MainAssetPackage);` — Given a main asset from an Asset Group, find the package containing the relevant Wardrobe Item if it exists @param MainAssetPackage The main asset to use to look for a wardrobe item @return The package containing the wardrobe Item or FName::None
- L466 _public prototype_ `static TArray<FMetaHumanExcludableSubAsset> FindExcludableSubAssets(const FMetaHumanAssetDescription& Asset);` — Identifies excludable sub-assets (Grooms, Clothing) within the dependency tree of a parent asset. Must be called after UpdateAssetDependencies. @param Asset The parent asset whose dependencies have been computed @return Array of excludable sub-assets found in the dependency tree

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/ProjectUtilities/MetaHumanProjectUtilities.h` (Public)


#### class `UE::MetaHuman::FInstalledMetaHuman`  
`class FInstalledMetaHuman`  
_L22-51_
- desc: Class that handles the layout and filenames of a MetaHuman that has been added to a project.
- L25 _public prototype_ `FInstalledMetaHuman(const FString& InName, const FString& InCharacterFilePath, const FString& InCommonFilePath);`
- L27 _public function_ `const FString& GetName() const`
- L32 _public prototype_ `FString GetRootAsset() const;`
- L34 _public prototype_ `FName GetRootPackage() const;`
- L36 _public prototype_ `FMetaHumanVersion GetVersion() const;`
- L38 _public prototype_ `EMetaHumanQualityLevel GetQualityLevel() const;`
- L40 _public prototype_ `FString GetCommonAssetPath() const;`
- L43 _public prototype_ `static TArray<FInstalledMetaHuman> GetInstalledMetaHumans(const FString& CharactersFolder, const FString& CommonAssetsFolder);` — Finds MetaHumans in the destination of a given import
- L46 _private member_ `FString Name;`
- L47 _private member_ `FString CharacterFilePath;`
- L48 _private member_ `FString CommonFilePath;`
- L49 _private member_ `FString CharacterAssetPath;`
- L50 _private member_ `FString CommonAssetPath;`

#### class `UE::MetaHuman::FMetaHumanProjectUtilities`  
`class FMetaHumanProjectUtilities`  
_L53-73_
- L57 _public prototype_ `static void EnableAutomation(IMetaHumanImportAutomationHandler* Handler);` — Disable UI and enable automation of user input for headless testing
- L60 _public prototype_ `static void SetBulkImportHandler(IMetaHumanBulkImportHandler* Handler);` — Disable UI and enable automation of user input for headless testing
- L63 _public prototype_ `static void ImportMetaHuman(const FMetaHumanImportDescription& AssetImportDescription);` — Main entry-point used by Quixel Bridge
- L66 _public prototype_ `static void OverrideVersionServiceUrl(const FString& BaseUrl);` — Provide the Url for the versioning service to use
- L69 _public prototype_ `static TArray<FInstalledMetaHuman> GetInstalledMetaHumans();` — Returns a list of all MetaHumans in the project
- L72 _public prototype_ `static void CopyVersionMetadata(TNotNull<class UObject*> InSourceObject, TNotNull<class UObject*> InDestObject);` — Copy the MetaHuman version metadata from the Source Object to the Destination Object

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/UI/SMetaHumanAuthenticationMenuButton.h` (Public)


#### class `SMetaHumanAuthenticationMenuButton`  
`class SMetaHumanAuthenticationMenuButton : public SCompoundWidget`  
_L8-40_
- inherits: `SCompoundWidget`
- desc: Widget used to display a combo button that displays MetaHuman authentication menu options.
- L11 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanAuthenticationMenuButton)`
- L14 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L21 _private prototype_ `TSharedRef<SWidget> MakeAuthenticationMenuOptionsWidget();` — Makes the authentication menu options widget.
- L24 _private prototype_ `TSharedRef<SWidget> MakeAccountUsernameTextWidget() const;` — Makes the account username text label widget. .
- L27 _private prototype_ `TSharedRef<SWidget> MakeAccountIDTextWidget() const;` — Makes the account id text label widget. .
- L30 _private prototype_ `TSharedRef<SWidget> MakeSignOutButtonWidget() const;` — Makes the sign out button widget.
- L33 _private prototype_ `FReply OnSignOutButtonClicked() const;` — Called when the sign out but is clicked.
- L36 _private prototype_ `bool IsSignOutButtonEnabled() const;` — True if the sign out but is enabled.
- L39 _private member_ `static const FName AuthenticationMenuName;` — The name identifier of the authentication menu.

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Verification/MetaHumanCharacterTypesVerificationExtensionBase.h` (Public)


#### struct `FClothingAssetDetails`  
`struct FClothingAssetDetails`  
_L13-17_
- L15 _public member_ `bool bResizesWithBlendableBodies = false;`
- L16 _public member_ `bool bHasClothingMask = false;`

#### class `UMetaHumanCharacterTypesVerificationExtensionBase`  
`class UMetaHumanCharacterTypesVerificationExtensionBase : public UObject`  
_L24-40_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Interface class to allow verification rule implementations to live inside the MetaHumanCharacter plugin for access to types defined in plugins that we can not reference from the MetaHumanSDK
- L30 _public prototype_ `virtual void VerifyGroomWardrobeItem(TNotNull<const UObject*> Target, TNotNull<const UObject*> GroomBindingAsset, UMetaHumanAssetReport* Report) PURE_VIRTUAL(UMetaHumanCharacterTypesVerificationExtensionBase::VerifyGroomWardrobeItem_Implementation,);` — WardrobeItem verification
- L31 _public prototype_ `virtual void VerifySkelMeshClothingWardrobeItem(TNotNull<const UObject*> Target, TNotNull<const UObject*> SkeletalMesh, UMetaHumanAssetReport* Report) PURE_VIRTUAL(UMetaHumanCharacterTypesVerificationExtensionBase::VerifySkelMeshClothingWardrobeItem_Implementation,);`
- L32 _public prototype_ `virtual void VerifyOutfitWardrobeItem(TNotNull<const UObject*> Target, TNotNull<const UObject*> OutfitAsset, UMetaHumanAssetReport* Report) PURE_VIRTUAL(UMetaHumanCharacterTypesVerificationExtensionBase::VerifyOutfitWardrobeItem_Implementation,);`
- L35 _public prototype_ `virtual void VerifyOutfitAsset(TNotNull<const UObject*> Target, UMetaHumanAssetReport* Report) PURE_VIRTUAL(UMetaHumanCharacterTypesVerificationExtensionBase::VerifyOutfitAsset_Implementation,);` — Custom verification for individual types
- L36 _public prototype_ `virtual void VerifyMetaHumanCharacterAsset(TNotNull<const UObject*> Target, UMetaHumanAssetReport* Report) PURE_VIRTUAL(UMetaHumanCharacterTypesVerificationExtensionBase::VerifyMetaHumanCharacterAsset_Implementation,);`
- L39 _public prototype_ `virtual FClothingAssetDetails GetDetailsForClothingAsset(TNotNull<const UObject*> Target) PURE_VIRTUAL(UMetaHumanCharacterTypesVerificationExtensionBase::GetDetailsForClothingAsset_Implementation, return {};);` — Technical details for individual types

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Verification/MetaHumanVerificationRuleCollection.h` (Public)


#### struct `FMetaHumanVerificationOptions`  
`struct FMetaHumanVerificationOptions`  
_L16-28_
- reflection: `USTRUCT(BlueprintType)`
- desc: Options for the Verification process
- L21 _public member_ `bool bVerbose = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " MetaHuman SDK | Verification ")`
- L24 _public member_ `bool bTreatWarningsAsErrors = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " MetaHuman SDK | Verification ")`
- L27 _public member_ `bool bVerifyPackagingRules = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " MetaHuman SDK | Verification ")`

#### class `UMetaHumanVerificationRuleBase`  
`class UMetaHumanVerificationRuleBase : public UObject`  
_L36-52_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable)`
- inherits: `UObject`
- desc: A Rule which can be part of a MetaHuman verification test suite
- L49 _public prototype_ `void Verify(const UObject* ToVerify, UMetaHumanAssetReport* Report, const FMetaHumanVerificationOptions& Options);` — `UFUNCTION(BlueprintNativeEvent, Category = " MetaHuman SDK | Verification ")` — Applies the rule to the asset and updates the verification report @param ToVerify The root UObject of the asset that is being verified @param Report The report which should be updated with the results of the test @param Options Verification option flags to use when generating the report
- L51 _public prototype_ `virtual void Verify_Implementation(const UObject* ToVerify, UMetaHumanAssetReport* Report, const FMetaHumanVerificationOptions& Options) const PURE_VIRTUAL(UMetaHumanVerificationRuleBase::Verify_Implementation,);`

#### class `UMetaHumanVerificationRuleCollection`  
`class UMetaHumanVerificationRuleCollection : public UObject`  
_L59-81_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- desc: A collection of Rules which make up a verification test for a class of MetaHuman asset compatibility, for example groom compatibility, clothing compatibility, animation compatibility etc.
- L66 _public prototype_ `void AddVerificationRule(UMetaHumanVerificationRuleBase* Rule);` — `UFUNCTION(BlueprintCallable, Category = " MetaHuman SDK | Verification ")` — Adds a rule to this collection
- L76 _public prototype_ `UMetaHumanAssetReport* ApplyAllRules(const UObject* Target, UMetaHumanAssetReport* Report, const FMetaHumanVerificationOptions& Options) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = " MetaHuman SDK | Verification ")` — Runs all registered rules against the Target. Compiles the results in OutReport. @param Target The root UObject of the asset that is being verified @param Report The report which should be updated with the results of the tests @param Options The options struct which may contain relevant options for the verification rule
- L80 _private member_ `TArray<TObjectPtr<UMetaHumanVerificationRuleBase>> Rules;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`
- L30 _typedef_ `using FMetaHumansVerificationOptions UE_DEPRECATED(5.7, "Use FMetaHumanVerificationOptions i`

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Verification/VerifyMetaHumanCharacter.h` (Public)


#### class `UVerifyMetaHumanCharacter`  
`class UVerifyMetaHumanCharacter : public UMetaHumanVerificationRuleBase`  
_L14-21_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetaHumanVerificationRuleBase`
- desc: A verification rule that tests that a MetaHuman character is valid. Currently only handles "Legacy" MetaHuman Characters.
- L20 _public prototype_ `virtual void Verify_Implementation(const UObject* ToVerify, UMetaHumanAssetReport* Report, const FMetaHumanVerificationOptions& Options) const override;` — UMetaHumanVerificationRuleBase overrides

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Verification/VerifyMetaHumanGroom.h` (Public)


#### class `UVerifyMetaHumanGroom`  
`class UVerifyMetaHumanGroom : public UMetaHumanVerificationRuleBase`  
_L14-54_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMetaHumanVerificationRuleBase`
- desc: A rule to test if a UObject complies with the MetaHuman Groom standard
- L20 _public prototype_ `virtual void Verify_Implementation(const UObject* ToVerify, UMetaHumanAssetReport* Report, const FMetaHumanVerificationOptions& Options) const override;` — UMetaHumanVerificationRuleBase overrides
- L29 _public member_ `bool bDetailedGroomingMeshVerification = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Verification")` — If true, detailed grooming mesh verification is performed. In addition to the basic checks (source/target mesh presence and spatial bounds overlap), the source skeletal mesh geometry is compared against the template MetaHuman head topology in UV space. This is expensive, so disable it when the caller only needs the basic grooming mesh checks.
- L37 _public member_ `bool bVerifyGroomToMeshAlignment = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Verification")` — If true, per-group groom-to-mesh alignment is validated. This builds a dynamic mesh AABB tree from the source skeletal mesh and tests every strand root against it; it is expensive. Other per-group strands checks (bounds intersect, vertex/curve counts) always run regardless of this flag.
- L45 _public member_ `bool bVerifyCardsStrandsAlignment = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Verification")` — If true, per-group hair cards will be checked for alignment against the groom's combined strands bounding box. This requires iterating every hair group to compute the strands bounds and is expensive. Other card checks (e.g. UVs) always run regardless of this flag.
- L53 _public member_ `bool bVerifyMeshesStrandsAlignment = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Verification")` — If true, per-group hair meshes (e.g. helmets) will be checked for alignment against the groom's combined strands bounding box. This requires iterating every hair group to compute the strands bounds and is expensive. Other hair mesh checks (e.g. UVs) always run regardless of this flag.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Verification/VerifyMetaHumanOutfitClothing.h` (Public)


#### class `UVerifyMetaHumanOutfitClothing`  
`class UVerifyMetaHumanOutfitClothing : public UMetaHumanVerificationRuleBase`  
_L14-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetaHumanVerificationRuleBase`
- desc: Verifies that a piece of clothing conforms to the standard for outfit-based clothing packages
- L17 _private prototype_ `virtual void Verify_Implementation(const UObject* ToVerify, UMetaHumanAssetReport* Report, const FMetaHumanVerificationOptions& Options) const override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Verification/VerifyMetaHumanPackageSource.h` (Public)


#### class `UVerifyMetaHumanPackageSource`  
`class UVerifyMetaHumanPackageSource : public UMetaHumanVerificationRuleBase`  
_L15-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetaHumanVerificationRuleBase`
- desc: A generic rule for MetaHuman Asset Groups that tests that they are valid for the generation of a MetaHuman Package. Only works for "normal" Asset Groups like grooms and clothing, not legacy characters.
- L21 _public prototype_ `virtual void Verify_Implementation(const UObject* ToVerify, UMetaHumanAssetReport* Report, const FMetaHumanVerificationOptions& Options) const override;` — UMetaHumanVerificationRuleBase overrides

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Verification/VerifyMetaHumanSkeletalClothing.h` (Public)


#### class `UVerifyMetaHumanSkeletalClothing`  
`class UVerifyMetaHumanSkeletalClothing : public UMetaHumanVerificationRuleBase`  
_L14-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMetaHumanVerificationRuleBase`
- desc: Verifies that a piece of clothing conforms to the standard for skeletal mesh-based clothing packages
- L19 _public prototype_ `virtual void Verify_Implementation(const UObject* ToVerify, UMetaHumanAssetReport* Report, const FMetaHumanVerificationOptions& Options) const override;`
- L21 _public prototype_ `static void VerifyClothingCompatibleAssets(const UObject* ToVerify, UMetaHumanAssetReport* Report);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`

### `Plugins/MetaHuman/MetaHumanSDK/Source/MetaHumanSDKEditor/Public/Verification/VerifyObjectValid.h` (Public)


#### class `UVerifyObjectValid`  
`class UVerifyObjectValid : public UMetaHumanVerificationRuleBase`  
_L14-21_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMetaHumanVerificationRuleBase`
- desc: A simple rule to test if a UObject is a valid asset
- L20 _public prototype_ `virtual void Verify_Implementation(const UObject* ToVerify, UMetaHumanAssetReport* Report, const FMetaHumanVerificationOptions& Options) const override;` — UMetaHumanVerificationRuleBase overrides

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANSDKEDITOR_API`
