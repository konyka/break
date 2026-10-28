# Plugins / VPBookmarkEditor

- module root: `Plugins/Experimental/VirtualProductionUtilities/Source/VPBookmarkEditor`
- headers: 4; symbols: 42
- symbol kinds: class=4, delegate=3, function=1, member=9, namespace=1, prototype=23, typedef=1
- PrivateDependencyModuleNames: EditorFramework, HeadMountedDisplay, InputCore, LevelEditor, Slate, UnrealEd, VREditor, ViewportInteraction
- PublicDependencyModuleNames: Core, CoreUObject, Engine, SlateCore, VPBookmark

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPBookmarkEditor/Private/VPBookmarkEditorModule.h` (Private)


#### class `FVPBookmarkEditorModule`  
`class FVPBookmarkEditorModule : public IModuleInterface`  
_L14-21_
- inherits: `IModuleInterface`
- L17 _public member_ `TSharedPtr<FVPBookmarkTypeActions> BookmarkTypeActions;`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVPBookmarkEditor, Log, Log);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVPBookmarkEditor, Log, Log);`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPBookmarkEditor/Private/VPBookmarkTypeActions.h` (Private)


#### class `FVPBookmarkTypeActions`  
`class FVPBookmarkTypeActions : public IBookmarkTypeActions`  
_L18-37_
- inherits: `IBookmarkTypeActions`
- L21 _private member_ `TWeakObjectPtr<UVPBookmark> LastActiveBookmark;`
- L24 _public member_ `FVPBookmarkActivated OnBookmarkActivated;`
- L25 _public member_ `FVPBookmarkDeactivated OnBookmarkDeactivated;`
- L28 _private prototype_ `void ActivateBookmark(UVPBookmark* Bookmark, FEditorViewportClient& Client);`
- L29 _private prototype_ `void DeactivateBookmark(UVPBookmark* Bookmark, FEditorViewportClient& Client);`
- L32 _public prototype_ `virtual TSubclassOf<UBookmarkBase> GetBookmarkClass() override;`
- L33 _public prototype_ `virtual void InitFromViewport(UBookmarkBase* InBookmark, FEditorViewportClient& InViewportClient) override;`
- L34 _public prototype_ `virtual void JumpToBookmark(UBookmarkBase* Bookmark, const TSharedPtr<FBookmarkBaseJumpToSettings> InSettings, FEditorViewportClient& InViewportClient) override;`
- L36 _public prototype_ `static AActor* SpawnBookmark(FEditorViewportClient& InViewportClient, const TSubclassOf<AActor> InActorClass, const FVPBookmarkCreationContext& InCreationContext, const FVector& InOffset, const bool bInFlattenRotation);`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FVPBookmarkActivated, UVPBookmark*);`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FVPBookmarkActivated, UVPBookmark*);`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FVPBookmarkDeactivated, UVPBookmark*);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FVPBookmarkDeactivated, UVPBookmark*);`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPBookmarkEditor/Public/SVPBookmarkListView.h` (Public)


#### class `SVPBookmarkListView`  
`class SVPBookmarkListView : public SCompoundWidget`  
_L23-53_
- inherits: `SCompoundWidget`
- desc: SVPBookmarkListView
- L26 _private typedef_ `using Super = SCompoundWidget;`
- L30 _public function_ `SLATE_BEGIN_ARGS(SVPBookmarkListView)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L34 _public prototype_ `~SVPBookmarkListView();`
- L37 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L39 _private prototype_ `void OnMapChanged(uint32 MapChangeFlags);`
- L40 _private prototype_ `void PopulateBookmarks();`
- L42 _private prototype_ `void OnBookmarkListModified(UVPBookmark* Bookmark);`
- L43 _private prototype_ `void OnBookmarkSelected(TSharedPtr<VPBookmarkList::SVPBookmarkCategoryListView> BookmarkCategory, TWeakObjectPtr<UVPBookmark> Selected, ESelectInfo::Type SelectionType);`
- L45 _private prototype_ `TWeakObjectPtr<UVPBookmark> GetSelectedBookmark();`
- L48 _private member_ `bool bBookmarkListViewDirty;`
- L49 _private member_ `bool bInSelection;`
- L50 _private member_ `TArray<TSharedPtr<VPBookmarkList::SVPBookmarkCategoryListView>> BookmarkCategories;`
- L51 _private member_ `TSharedPtr<SScrollBox> BookmarkCategoryContainer;`
- L52 _private member_ `TWeakObjectPtr<UVPBookmark> SelectedBookmark;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace VPBookmarkList`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPBookmarkEditor/Public/VPBookmarkEditorBlueprintLibrary.h` (Public)


#### class `UVPBookmarkEditorBlueprintLibrary`  
`class UVPBookmarkEditorBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L16-32_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L22 _public prototype_ `static bool JumpToBookmarkInLevelEditor(const UVPBookmark* Bookmark);` — `UFUNCTION(BlueprintCallable, Category = "Bookmarks")`
- L25 _public prototype_ `static bool JumpToBookmarkInLevelEditorByIndex(const int32 BookmarkIndex);` — `UFUNCTION(BlueprintCallable, Category = "Bookmarks")`
- L28 _public prototype_ `static AActor* AddBookmarkAtCurrentLevelEditorPosition(const TSubclassOf<AActor> ActorClass, const FVPBookmarkCreationContext CreationContext, const FVector Offset, const bool bFlattenRotation = true);` — `UFUNCTION(BlueprintCallable, Category = "Bookmarks")`
- L31 _public prototype_ `static void GetAllActorsClassThamImplementsVPBookmarkInterface(TArray<TSubclassOf<AActor>>& OutActorClasses);` — `UFUNCTION(BlueprintCallable, Category = "Bookmarks")`
