# Editor / AssetDefinition

- module root: `Source/Editor/AssetDefinition`
- headers: 8; symbols: 245
- symbol kinds: class=5, delegate=3, enum=9, enumerator=22, function=56, macro=4, member=82, prototype=42, struct=22
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: AssetRegistry, Core, CoreUObject, EditorSubsystem, Engine, InputCore, Slate, SlateCore

### `Source/Editor/AssetDefinition/Public/AssetDefinition.h` (Public)


#### enum `EAssetActivationMethod`  
`enum class EAssetActivationMethod : uint8`  
_L28-33_
- reflection: `UENUM()`
- L30 _public enumerator_ `DoubleClicked`
- L31 _public enumerator_ `Opened`
- L32 _public enumerator_ `Previewed`

#### enum `EAssetCommandResult`  
`enum class EAssetCommandResult : uint8`  
_L36-40_
- reflection: `UENUM()`
- L38 _public enumerator_ `Handled`
- L39 _public enumerator_ `Unhandled`

#### enum `EAssetOpenMethod`  
`enum class EAssetOpenMethod : uint8`  
_L43-48_
- reflection: `UENUM()`
- L45 _public enumerator_ `Edit`
- L46 _public enumerator_ `View`

#### enum `EAssetMergeResult`  
`enum class EAssetMergeResult : uint8`  
_L50-55_
- L52 _public enumerator_ `Unknown`
- L53 _public enumerator_ `Completed`
- L54 _public enumerator_ `Cancelled`

#### enum `EPathUse`  
`enum class EPathUse : uint8`  
_L57-70_
- L64 _public enumerator_ `Display` — Present the file in a UI friendly format. Note that the path might not always be relative. It cannot be used for other purposes then presenting it to the user since the details of how to resolve that path might change based on the asset implementation.
- L69 _public enumerator_ `AbsolutePath` — Resolve the path into an absolute path.

#### struct `FAssetArgs`  
`struct FAssetArgs`  
_L72-126_
- L74 _public function_ `FAssetArgs()`
- L75 _public function_ `FAssetArgs(TConstArrayView<FAssetData> InAssets) : Assets(InAssets)`
- L77 _public member_ `TConstArrayView<FAssetData> Assets;`
- L80 _public function_ `template<typename ExpectedObjectType> TArray<ExpectedObjectType*> LoadObjects(const TSet<FName>& LoadTags = {}, TArray<FAssetData>* OutAssetsThatFailedToLoad = nullptr) const`
- L111 _public function_ `template<typename ExpectedObjectType> ExpectedObjectType* LoadFirstValid(const TSet<FName>& LoadTags = {}) const`

#### struct `FAssetOpenArgs`  
`struct FAssetOpenArgs : public FAssetArgs`  
_L128-134_
- inherits: `FAssetArgs`
- L130 _public member_ `EAssetOpenMethod OpenMethod;`
- L131 _public member_ `TSharedPtr<IToolkitHost> ToolkitHost;`
- L133 _public function_ `EToolkitMode::Type GetToolkitMode() const`

#### struct `FAssetActivateArgs`  
`struct FAssetActivateArgs : public FAssetArgs`  
_L136-139_
- inherits: `FAssetArgs`
- L138 _public member_ `EAssetActivationMethod ActivationMethod;`

#### struct `FAssetSourceFilesArgs`  
`struct FAssetSourceFilesArgs : public FAssetArgs`  
_L141-144_
- inherits: `FAssetArgs`
- L143 _public member_ `EPathUse FilePathFormat = EPathUse::AbsolutePath;`

#### struct `FAssetSourceFilesResult`  
`struct FAssetSourceFilesResult`  
_L146-159_
- L149 _public member_ `FString FilePath;` — The file path in the format requested.
- L152 _public member_ `FString DisplayLabel;` — The Label was used to display this source file in the property editor.
- L155 _public member_ `FDateTime Timestamp;` — The timestamp of the file when it was imported (as UTC). 0 when unknown.
- L158 _public member_ `FMD5Hash FileHash;` — The MD5 hash of the file when it was imported. Invalid when unknown.

#### struct `FAssetMergeResults`  
`struct FAssetMergeResults`  
_L161-165_
- L163 _public member_ `UPackage* MergedPackage = nullptr;`
- L164 _public member_ `EAssetMergeResult Result = EAssetMergeResult::Unknown;`

#### enum `EMergeFlags`  
`enum EMergeFlags : uint8`  
_L169-174_
- L171 _public enumerator_ `MF_NONE = 0x00`
- L172 _public enumerator_ `MF_NO_GUI = 0x01`
- L173 _public enumerator_ `MF_HANDLE_SOURCE_CONTROL = 0x02`

#### struct `FAssetAutomaticMergeArgs`  
`struct FAssetAutomaticMergeArgs`  
_L176-181_
- L178 _public member_ `UObject* LocalAsset = nullptr;`
- L179 _public member_ `FOnAssetMergeResolved ResolutionCallback;`
- L180 _public member_ `EMergeFlags Flags = MF_HANDLE_SOURCE_CONTROL;`

#### struct `FAssetManualMergeArgs`  
`struct FAssetManualMergeArgs`  
_L183-190_
- L185 _public member_ `UObject* LocalAsset = nullptr;`
- L186 _public member_ `UObject* BaseAsset = nullptr;`
- L187 _public member_ `UObject* RemoteAsset = nullptr;`
- L188 _public member_ `FOnAssetMergeResolved ResolutionCallback;`
- L189 _public member_ `EMergeFlags Flags = MF_HANDLE_SOURCE_CONTROL;`

#### struct `FAssetSupportResponse`  
`struct FAssetSupportResponse`  
_L192-223_
- L195 _public function_ `static FAssetSupportResponse Supported()`
- L200 _public function_ `static FAssetSupportResponse NotSupported()`
- L205 _public function_ `static FAssetSupportResponse Error(const FText& ErrorText)`
- L210 _public function_ `bool IsSupported() const`
- L211 _public function_ `const FText& GetErrorText() const`
- L214 _private function_ `FAssetSupportResponse(bool InSupported, const FText InError) : bSupported(InSupported) , ErrorText(InError)`
- L221 _private member_ `bool bSupported;`
- L222 _private member_ `FText ErrorText;`

#### struct `FRevisionInfo`  
`struct FRevisionInfo`  
_L227-245_
- reflection: `USTRUCT(BlueprintType)`
- desc: Revision information for a single revision of a file in source control
- L232 _public member_ `FString Revision;` — `UPROPERTY(BlueprintReadWrite, Category="Asset Revision")`
- L235 _public member_ `int32 Changelist = -1;` — `UPROPERTY(BlueprintReadWrite, Category="Asset Revision")`
- L238 _public member_ `FDateTime Date;` — `UPROPERTY(BlueprintReadWrite, Category="Asset Revision")`
- L240 _public function_ `static inline FRevisionInfo InvalidRevision()`

#### struct `FAssetDiffArgs`  
`struct FAssetDiffArgs`  
_L247-254_
- L249 _public member_ `UObject* OldAsset = nullptr;`
- L250 _public member_ `FRevisionInfo OldRevision;`
- L252 _public member_ `UObject* NewAsset = nullptr;`
- L253 _public member_ `FRevisionInfo NewRevision;`

#### struct `FAssetOpenSupportArgs`  
`struct FAssetOpenSupportArgs`  
_L256-265_
- L258 _public function_ `FAssetOpenSupportArgs(EAssetOpenMethod InOpenMethod = EAssetOpenMethod::Edit) : OpenMethod(InOpenMethod)`
- L264 _public member_ `EAssetOpenMethod OpenMethod;`

#### struct `EAssetCategoryPaths`  
`struct EAssetCategoryPaths`  
_L272-296_
- desc: These are just some common asset categories.  You're not at all limited to these, and can register an "Advanced" category with the IAssetTools::RegisterAdvancedAssetCategory.
- L277 _public member_ `static FAssetCategoryPath Basic;` — This category is special, "Basic" assets appear at the very top level and are not placed into any submenu. Arguably the basic category should not exist and should instead be user configurable on what they feel should be top level assets.
- L279 _public member_ `static FAssetCategoryPath Animation;`
- L280 _public member_ `static FAssetCategoryPath Audio;`
- L281 _public member_ `static FAssetCategoryPath Blueprint;`
- L282 _public member_ `static FAssetCategoryPath Cinematics;`
- L283 _public member_ `static FAssetCategoryPath Data;`
- L284 _public member_ `static FAssetCategoryPath Foliage;`
- L285 _public member_ `static FAssetCategoryPath FX;`
- L286 _public member_ `static FAssetCategoryPath Gameplay;`
- L287 _public member_ `static FAssetCategoryPath AI;`
- L288 _public member_ `static FAssetCategoryPath Input;`
- L289 _public member_ `static FAssetCategoryPath Material;`
- L290 _public member_ `static FAssetCategoryPath Media;`
- L291 _public member_ `static FAssetCategoryPath Misc;`
- L292 _public member_ `static FAssetCategoryPath Physics;`
- L293 _public member_ `static FAssetCategoryPath Texture;`
- L294 _public member_ `static FAssetCategoryPath UI;`
- L295 _public member_ `static FAssetCategoryPath World;`

#### struct `FAssetOpenSupport`  
`struct FAssetOpenSupport`  
_L298-317_
- L301 _public function_ `FAssetOpenSupport(EAssetOpenMethod InOpenMethod, bool bInSupported) : OpenMethod(InOpenMethod) , IsSupported(bInSupported)`
- L307 _public function_ `FAssetOpenSupport(EAssetOpenMethod InOpenMethod, bool bInSupported, EToolkitMode::Type InRequiredToolkitMode) : OpenMethod(InOpenMethod) , IsSupported(bInSupported) , RequiredToolkitMode(InRequiredToolkitMode)`
- L314 _public member_ `EAssetOpenMethod OpenMethod;`
- L315 _public member_ `bool IsSupported;`
- L316 _public member_ `TOptional<EToolkitMode::Type> RequiredToolkitMode;`

#### enum `EIncludeClassInFilter`  
`enum class EIncludeClassInFilter : uint8`  
_L322-326_
- L324 _public enumerator_ `IfClassIsNotAbstract`
- L325 _public enumerator_ `Always`

#### struct `FAssetFilterDataCache`  
`struct FAssetFilterDataCache`  
_L329-333_
- L332 _public member_ `TArray<FAssetFilterData> Filters;`

#### struct `FAssetActionThumbnailOverlayInfo`  
`struct FAssetActionThumbnailOverlayInfo`  
_L336-348_
- L341 _public member_ `TSharedPtr<SWidget> ActionImageWidget;` — Image widget displayed in the top left border
- L344 _public member_ `FIsActionPlaying IsActionPlayingDelegate;` — Attach your IsPlaying action to this delegate that will be used to decide on the action image to use
- L347 _public member_ `SButton::FArguments ActionButtonArgs;` — Button Args used to construct the Action Button

#### struct `FAssetButtonActionExtension`  
`struct FAssetButtonActionExtension`  
_L350-356_
- L353 _public member_ `TAttribute<FText> PickTooltipAttribute;`
- L354 _public member_ `TAttribute<const FSlateBrush*> PickBrushAttribute;`
- L355 _public member_ `FOnClicked OnClicked;`

#### class `UAssetDefinition`  
`class UAssetDefinition : public UObject`  
_L455-657_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Asset Definitions represent top level assets that are known to the editor. -- Conversion Guide -- Asset Definitions (UAssetDefinitionDefault) are a replacement to the Asset Actions (FAssetTypeActions_Base) system. The reasons for the replacement are multitude, but the highlights are, Asset Definitions no longer do things like provide a GetActions function, the replacement for this is you using the new UToolMenu extension system to register actions for the assets, an example is in this document.  A lot of the APIs have been tweaked and cleaned up to make them easier to upgrade in the future, a lot of the original API for Asset Actions were added one at a time, and several of them could be combined in simpler ways.  Another benefit is soon we might be able to make the AssetTools module no longer a circular dependency. All of this is in service to what was previously impossible.  To be able to right click on assets in the Content Browser and NOT have the asset and every asset it knew about load on right click, this previous impossible to escape byproduct slowed down working in the editor constantly because things that didn’t require opening the asset became necessary, and some assets could load *A LOT* of other content. Unfortunately I can’t prevent people from backsliding, at least for now.  Even after fixing the APIs to not require loading, people need to be cleverer (Use Asset Tag Data) in how they provide right click options for assets.  But to help, you can run the editor w
- L460 _public prototype_ `UAssetDefinition();`
- L463 _public prototype_ `virtual void PostCDOContruct() override;`
- L469 _public prototype_ `virtual FText GetAssetDisplayName() const PURE_VIRTUAL(UAssetDefinition::GetAssetDisplayName, (void)ensureMsgf(false && "NotImplemented", TEXT("NotImplem` — Returns the name of this type
- L477 _public function_ `virtual FText GetAssetDisplayName(const FAssetData& AssetData) const` — Returns the name of this type, but allows overriding the default on a specific instance of the asset.  This is handy for cases like UAssetData which are of course all UAssetData, but a given instance of the asset is really a specific instance of some UAssetData class, and being able to override that on the instance is handy for readability at the Content Browser level.
- L480 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const PURE_VIRTUAL(UAssetDefinition::GetAssetClass, (void)ensureMsgf(false && "NotImplemented", TEXT("NotImplemented")); return` — Get the supported class of this type.
- L483 _public prototype_ `virtual FLinearColor GetAssetColor() const PURE_VIRTUAL(UAssetDefinition::GetAssetColor, (void)ensureMsgf(false && "NotImplemented", TEXT("NotImplemente` — Returns the color associated with this type
- L486 _public function_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const` — Returns additional tooltip information for the specified asset, if it has any.
- L489 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const;` — Gets a list of categories this asset is in, these categories are used to help organize
- L493 _public function_ `virtual TArray<FAssetData> PrepareToActivateAssets(const FAssetActivateArgs& ActivateArgs) const` — Common Operations
- L498 _public function_ `virtual bool ShouldFindEditorForAsset() const`
- L504 _public function_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const` — Get open support for the method.  Includes required information before we call OpenAsset.
- L509 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const PURE_VIRTUAL(UAssetDefinition::OpenAsset, (void)ensureMsgf(false && "NotImplemented", TEXT("NotImplemented")); return EAsset`
- L511 _public function_ `virtual EAssetCommandResult ActivateAssets(const FAssetActivateArgs& ActivateArgs) const`
- L518 _public function_ `virtual FAssetSupportResponse CanRename(const FAssetData& InAsset) const` — Common Queries
- L523 _public function_ `virtual FAssetSupportResponse CanDuplicate(const FAssetData& InAsset) const`
- L528 _public function_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const`
- L535 _public function_ `virtual bool CanImport() const` — Importing
- L539 _public function_ `virtual bool CanMerge() const` — Merging
- L540 _public function_ `virtual EAssetCommandResult Merge(const FAssetAutomaticMergeArgs& MergeArgs) const`
- L541 _public function_ `virtual EAssetCommandResult Merge(const FAssetManualMergeArgs& MergeArgs) const`
- L545 _public function_ `virtual TSharedRef<FAssetFilterDataCache> GetFilters() const` — Filtering
- L557 _protected prototype_ `virtual void BuildFilters(TArray<FAssetFilterData>& OutFilters) const;`
- L561 _public function_ `virtual FText GetObjectDisplayNameText(UObject* Object) const` — Extras
- L573 _public prototype_ `virtual EAssetCommandResult GetSourceFiles(const FAssetSourceFilesArgs& InArgs, TFunctionRef<bool(const FAssetSourceFilesResult& InSourceFile)> SourceFileFunc) const;` — Return the source files that was used to generate/import the asset @param InArgs The asset data of the assets we want the source files from and in which format we want the file path to be. @param SourceFileFunc A function that is called for each source file found. The call back must return true to continue the enumeration.
- L576 _public prototype_ `virtual EAssetCommandResult GetSourceFiles(const FAssetData& InAsset, TFunctionRef<void(const FAssetImportInfo& AssetImportData)> SourceFileFunc) const;` — `UE_DEPRECATED(5.3, "This override will be removed because it doesn't account that the resolution of a relative path to its absolute path may varies based on the asset implementation.")`
- L579 _public function_ `virtual EAssetCommandResult PerformAssetDiff(const FAssetDiffArgs& DiffArgs) const` — Diffing Assets
- L587 _public function_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const` — Returns the thumbnail info for the specified asset, if it has one. This typically requires loading the asset.
- L593 _public function_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const` — Returns thumbnail brush unique for the given asset data.  Returning null falls back to class thumbnail brush.
- L599 _public function_ `virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const` — Returns icon brush unique for the given asset data.  Returning null falls back to class icon brush.
- L606 _public function_ `virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& InAssetData) const` — Optionally returns a custom widget to overlay on top of this assets' thumbnail
- L611 _public function_ `virtual bool GetThumbnailActionOverlay(const FAssetData& InAssetData, FAssetActionThumbnailOverlayInfo& OutActionOverlayInfo) const`
- L617 _public prototype_ `virtual void GetAssetStatusInfo(const TSharedPtr<IAssetStatusInfoProvider>& InAssetStatusInfoProvider, TArray<FAssetDisplayInfo>& OutStatusInfo) const;` — Get the basic status info on assets like the Dirty and SourceControl one
- L620 _public function_ `virtual void GetAssetActionButtonExtensions(const FAssetData& InAssetData, TArray<FAssetButtonActionExtension>& OutExtensions) const` — Optionally adds custom Asset Picker buttons to the Property Editor for the selected AssetDefinition, using the provided extension data this function returns.
- L623 _public function_ `virtual bool ShouldSaveExternalPackages() const` — Whether this asset has external packages associated with it (impacts saving and dirty-state behavior)
- L648 _public prototype_ `virtual bool CanRegisterStatically() const;`
- L651 _protected member_ `EIncludeClassInFilter IncludeClassInFilter = EIncludeClassInFilter::IfClassIsNotAbstract;`
- L654 _private member_ `mutable TSharedPtr<FAssetFilterDataCache> FilterCache;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API ASSETDEFINITION_API`
- L167 _delegate_ `DECLARE_DELEGATE_OneParam(FOnAssetMergeResolved, const FAssetMergeResults& Results);`
- L167 _prototype_ `DECLARE_DELEGATE_OneParam(FOnAssetMergeResolved, const FAssetMergeResults& Results);`
- L335 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FIsActionPlaying) struct FAssetActionThumbnailOverlayInfo { public: UE_DEPRECATED(5.8, "Please use the IsActionPlayingDelegate instead.") TSharedPtr<SWidget> ActionImageWidget; FIsActionPlaying IsActionPlayingDelegate; SButton::FArguments ActionButtonArgs; };`

### `Source/Editor/AssetDefinition/Public/AssetDefinitionAssetInfo.h` (Public)


#### enum `EStatusSeverity`  
`enum class EStatusSeverity`  
_L11-16_
- L13 _public enumerator_ `Info`
- L14 _public enumerator_ `Warning`
- L15 _public enumerator_ `Error`

#### struct `FAssetStatusPriority`  
`struct FAssetStatusPriority`  
_L19-70_
- L21 _public function_ `FAssetStatusPriority() : Severity(EStatusSeverity::Info) , SeverityPriority(0)`
- L26 _public function_ `FAssetStatusPriority(const TAttribute<EStatusSeverity>& InSeverity) : Severity(InSeverity) , SeverityPriority(0)`
- L31 _public function_ `FAssetStatusPriority(const TAttribute<EStatusSeverity>& InSeverity, int32 InSeverityPriority) : Severity(InSeverity) , SeverityPriority(InSeverityPriority)`
- L37 _public function_ `bool operator==(const FAssetStatusPriority& InOtherStatusPriority) const`
- L47 _public function_ `bool operator<(const FAssetStatusPriority& InOtherStatusPriority) const`
- L68 _public member_ `TAttribute<EStatusSeverity> Severity;`
- L69 _public member_ `int32 SeverityPriority;`

#### struct `FAssetDisplayInfo`  
`struct FAssetDisplayInfo`  
_L72-81_
- L75 _public member_ `TAttribute<const FSlateBrush*> StatusIcon;`
- L76 _public member_ `TAttribute<const FSlateBrush*> StatusIconOverlay;`
- L77 _public member_ `TAttribute<FText> StatusTitle;`
- L78 _public member_ `TAttribute<FText> StatusDescription;`
- L79 _public member_ `TAttribute<EVisibility> IsVisible;`
- L80 _public member_ `TAttribute<FAssetStatusPriority> Priority;`

### `Source/Editor/AssetDefinition/Public/AssetDefinitionRegistry.h` (Public)


#### class `UAssetDefinitionRegistry`  
`class UAssetDefinitionRegistry : public UObject`  
_L18-67_
- reflection: `UCLASS(MinimalAPI, config=Editor)`
- inherits: `UObject`
- L23 _public prototype_ `static UAssetDefinitionRegistry* Get();`
- L25 _public prototype_ `UAssetDefinitionRegistry();`
- L27 _public prototype_ `virtual void BeginDestroy() override;`
- L29 _public prototype_ `const UAssetDefinition* GetAssetDefinitionForAsset(const FAssetData& Asset) const;`
- L30 _public prototype_ `const UAssetDefinition* GetAssetDefinitionForClass(const UClass* Class) const;`
- L33 _public prototype_ `uint64 GetAssetDefinitionVersion() const;` — Gets the current version of the AssetDefinitions.   Version is updated whenever an AssetDefinition is Registered/Unregistered
- L34 _public prototype_ `TArray<TObjectPtr<UAssetDefinition>> GetAllAssetDefinitions() const;`
- L35 _public prototype_ `TArray<TSoftClassPtr<UObject>> GetAllRegisteredAssetClasses() const;`
- L43 _public prototype_ `void RegisterAssetDefinition(UAssetDefinition* AssetDefinition);` — Normally UAssetDefinitionRegistry are registered automatically by their CDO.  The only reason you need to do this is if you're forced to dynamically create the UAssetDefinition at runtime.  The original reason for this function was to be able to create wrappers for the to be replaced IAssetTypeActions, that you can access AssetDefinition versions of any IAssetType making the upgrade easier.
- L45 _public prototype_ `void UnregisterAssetDefinition(UAssetDefinition* AssetDefinition);`
- L50 _public prototype_ `FOnAssetDefinitionRegistryVersionChange& OnAssetDefinitionRegistryVersionChange();` — Called when the AssetDefinitionRegistry's version has changed.
- L53 _private prototype_ `void RegisterTickerForVersionNotification();`
- L54 _private prototype_ `bool TickVersionNotification(float);`
- L56 _private member_ `static UAssetDefinitionRegistry* Singleton;`
- L57 _private member_ `static bool bHasShutDown;`
- L60 _private member_ `TMap<TSoftClassPtr<UObject>, TObjectPtr<UAssetDefinition>> AssetDefinitions;` — `UPROPERTY()`
- L62 _private member_ `uint64 Version;`
- L64 _private member_ `FTickerDelegate TickerDelegate;`
- L65 _private member_ `FTSTicker::FDelegateHandle TickerDelegateHandle;`
- L66 _private member_ `FOnAssetDefinitionRegistryVersionChange OnAssetDefinitionRegistryVersionChangeDelegate;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ASSETDEFINITION_API`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAssetDefinitionRegistryVersionChange, UAssetDefinitionRegistry*);`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAssetDefinitionRegistryVersionChange, UAssetDefinitionRegistry*);`

### `Source/Editor/AssetDefinition/Public/AssetStatusAssetDataInfoProvider.h` (Public)


#### class `FAssetStatusAssetDataInfoProvider`  
`class FAssetStatusAssetDataInfoProvider : public IAssetStatusInfoProvider`  
_L10-25_
- inherits: `IAssetStatusInfoProvider`
- L13 _public function_ `FAssetStatusAssetDataInfoProvider(FAssetData InAssetData) : AssetData(InAssetData)`
- L17 _public prototype_ `virtual UPackage* FindPackage() const override;`
- L19 _public prototype_ `virtual FString TryGetFilename() const override;`
- L21 _public prototype_ `virtual FAssetData TryGetAssetData() const override;`
- L24 _private member_ `FAssetData AssetData;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ASSETDEFINITION_API`

### `Source/Editor/AssetDefinition/Public/IAssetStatusInfoProvider.h` (Public)


#### class `IAssetStatusInfoProvider`  
`class IAssetStatusInfoProvider`  
_L10-23_
- L13 _public prototype_ `virtual ~IAssetStatusInfoProvider() = default;`
- L16 _public prototype_ `virtual UPackage* FindPackage() const = 0;` — Try to find the Package without loading it, if the package is not loaded it will return nullptr
- L19 _public prototype_ `virtual FString TryGetFilename() const = 0;` — Try to get the filename, return empty otherwise
- L22 _public prototype_ `virtual FAssetData TryGetAssetData() const = 0;` — Try to get the AssetData, return an empty FAssetData otherwise

### `Source/Editor/AssetDefinition/Public/IAssetSystemInfoProvider.h` (Public)


#### class `IAssetSystemInfoProvider`  
`class IAssetSystemInfoProvider`  
_L9-16_
- L12 _public prototype_ `virtual ~IAssetSystemInfoProvider() = default;`
- L15 _public prototype_ `virtual void PopulateAssetInfo(TArray<FAssetDisplayInfo>& OutAssetDisplayInfo) const = 0;` — Populate the OutAssetDisplayInfo with the information of the Asset like the Path/Size etc...

### `Source/Editor/AssetDefinition/Public/Misc/AssetCategoryPath.h` (Public)


#### enum `ECategoryMenuType`  
`enum class ECategoryMenuType : uint8`  
_L12-16_
- desc: Whether the SubCategory should be a menu or just a section
- L14 _public enumerator_ `Menu = 0`
- L15 _public enumerator_ `Section = 1 << 0`

#### struct `FCategoryPath`  
`struct FCategoryPath`  
_L21-37_
- desc: Contains the sub menu name and the type of the sub menu, either a menu or a section, section should be the last in the chain
- L23 _public function_ `FCategoryPath(const FText& InSubMenuName, const ECategoryMenuType InCategoryMenuType = ECategoryMenuType::Menu) : SubMenuName(InSubMenuName) , CategoryMenuType(InCategoryMenuType)`
- L29 _public function_ `FText GetSubMenuName() const` — Get the name of the sub menu, could be a sub category based on the position inside the FAssetCategoryPath
- L32 _public function_ `ECategoryMenuType GetCategoryMenuType() const` — Either Menu or Section, based on if you want a menu or a section for your entry
- L35 _private member_ `FText SubMenuName;`
- L36 _private member_ `ECategoryMenuType CategoryMenuType;`

#### struct `FAssetCategoryPath`  
`struct FAssetCategoryPath`  
_L46-92_
- desc: The asset category path is how we know how to build menus around assets.\n  For example, Basic is generally the ones we expose at the top level, where as everything else is a category with a pull out menu, and the subcategory would be where it gets placed in a submenu inside of there.\n\n Currently, the system supports chaining menus and as the last entry you can have a custom section.\n You can't have a menu inside a section so the section should be the last in case you want one.
- L48 _public prototype_ `FAssetCategoryPath(const FText& InCategory);`
- L49 _public prototype_ `FAssetCategoryPath(TConstArrayView<FText> InCategoryPath);`
- L59 _public function_ `template <typename... TInSubMenus> requires (std::is_constructible_v<FCategoryPath, TInSubMenus> && ...) FAssetCategoryPath(const FAssetCategoryPath& InCategory, TInSubMenus&&... InSubMenus)` — Constructs from a root FAssetCategoryPath followed by any number of FCategoryPath.\n By default, every FText given is treated like a menu.\n If the last entry is a section you should still explicitly add it like so:\n FAssetCategoryPath(FAssetCategoryPath or (FText), FCategoryPath or (FText)..., FCategoryPath(FText, ECategoryMenuType::Section))
- L69 _public function_ `FAssetCategoryPath(const FAssetCategoryPath& InCategory, const FText& InSubMenuName, ECategoryMenuType InMenuType = ECategoryMenuType::Menu) : FAssetCategoryPath(InCategory, FCategoryPath(InSubMenuName, InMenuType))` — Constructor helper to avoid explicit wrapping when a specific menu type is needed
- L73 _public function_ `FName GetCategory() const`
- L74 _public function_ `FText GetCategoryText() const`
- L76 _public function_ `bool HasSubCategory() const`
- L77 _public function_ `int32 NumSubCategories() const`
- L78 _public function_ `FName GetSubCategory() const`
- L79 _public function_ `FText GetSubCategoryText() const`
- L81 _public prototype_ `void GetSubCategories(TArray<FName>& SubCategories) const;`
- L82 _public prototype_ `void GetSubCategoriesText(TArray<FText>& SubCategories) const;`
- L83 _public prototype_ `void GetSubCategoriesInfo(TArray<FCategoryPath>& SubCategories) const;`
- L85 _public function_ `FAssetCategoryPath operator / (const FText& SubCategory) const`
- L88 _private prototype_ `void AppendSubMenu(const FCategoryPath& InSubMenu);`
- L91 _private member_ `TArray<TPair<FName, FCategoryPath>> CategoryPath;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API ASSETDEFINITION_API`

### `Source/Editor/AssetDefinition/Public/Misc/AssetFilterData.h` (Public)


#### struct `FAssetFilterData`  
`struct FAssetFilterData`  
_L12-24_
- reflection: `USTRUCT()`
- L17 _public member_ `FString Name;`
- L19 _public member_ `FText DisplayText;`
- L21 _public member_ `TArray<FAssetCategoryPath> FilterCategories;`
- L23 _public member_ `FARFilter Filter;`
