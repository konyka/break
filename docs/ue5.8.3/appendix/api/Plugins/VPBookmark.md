# Plugins / VPBookmark

- module root: `Plugins/Experimental/VirtualProductionUtilities/Source/VPBookmark`
- headers: 6; symbols: 51
- symbol kinds: class=5, delegate=2, function=1, member=13, prototype=27, struct=3
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPBookmark/Private/VPBookmarkModule.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVPBookmark, Log, Log);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVPBookmark, Log, Log);`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPBookmark/Public/IVPBookmarkProvider.h` (Public)


#### class `UVPBookmarkProvider`  
`class UVPBookmarkProvider : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(BlueprintType)`
- inherits: `UInterface`

#### class `IVPBookmarkProvider`  
`class IVPBookmarkProvider : public IInterface`  
_L20-39_
- inherits: `IInterface`
- L26 _public prototype_ `void OnBookmarkActivation(UVPBookmark* Bookmark, bool bActivate);` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, Category = "Bookmarks")`
- L29 _public prototype_ `void OnBookmarkChanged(UVPBookmark* Bookmark);` — `UFUNCTION(BlueprintNativeEvent, CallInEditor, Category = "Bookmarks")`
- L32 _public prototype_ `void UpdateBookmarkSplineMeshIndicator();` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, CallInEditor, Category = "Bookmarks")`
- L35 _public prototype_ `void HideBookmarkSplineMeshIndicator();` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, CallInEditor, Category = "Bookmarks")`
- L38 _public prototype_ `void GenerateBookmarkName();` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, CallInEditor, Category = "Bookmarks")`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPBookmark/Public/VPBookmark.h` (Public)


#### struct `FVPBookmarkViewportData`  
`struct FVPBookmarkViewportData`  
_L15-34_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public prototype_ `FVPBookmarkViewportData();`
- L24 _public member_ `FVector JumpToOffsetLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")`
- L27 _public member_ `FRotator LookRotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")`
- L30 _public member_ `float OrthoZoom;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")`
- L33 _public member_ `bool bFlattenRotation;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bookmarks")`

#### struct `FVPBookmarkJumpToSettings`  
`struct FVPBookmarkJumpToSettings : public FBookmarkBaseJumpToSettings`  
_L38-41_
- reflection: `USTRUCT()`
- inherits: `FBookmarkBaseJumpToSettings`

#### class `UVPBookmark`  
`class UVPBookmark : public UBookmarkBase`  
_L45-101_
- reflection: `UCLASS(BlueprintType, Category = Bookmark)`
- inherits: `UBookmarkBase`
- L51 _private member_ `bool bIsActive;` — `UPROPERTY(DuplicateTransient, Transient)`
- L55 _public member_ `TLazyObjectPtr<AActor> OwnedActor;` — `UPROPERTY()`
- L58 _public member_ `FVPBookmarkCreationContext CreationContext;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bookmarks")`
- L61 _public member_ `FVPBookmarkViewportData CachedViewportData;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bookmarks")`
- L65 _public function_ `bool IsActive() const` — `UFUNCTION(BlueprintCallable, Category = "Bookmarks")`
- L67 _public prototype_ `void SetActive(bool bInActive);`
- L70 _public prototype_ `int32 GetBookmarkIndex() const;` — `UFUNCTION(BlueprintCallable, Category = "Bookmarks")`
- L73 _public prototype_ `AActor* GetAssociatedBookmarkActor() const;` — `UFUNCTION(BlueprintCallable, Category = "Bookmarks")`
- L76 _public prototype_ `FText GetDisplayName() const;` — `UFUNCTION(BlueprintCallable, Category = "Bookmarks")`
- L81 _public prototype_ `virtual void PostInitProperties() override;`
- L82 _public prototype_ `virtual void PostLoad() override;`
- L83 _public prototype_ `virtual void BeginDestroy() override;`
- L87 _public prototype_ `virtual void OnCleared() override;`
- L91 _private prototype_ `void BookmarkChanged(AActor* OwnerPtr);`
- L92 _private prototype_ `void RemoveBookmark();`
- L94 _private prototype_ `void OnLevelActorAdded(AActor* NewActor);`
- L95 _private prototype_ `void OnLevelActorDeleted(AActor* DeletedActor);`
- L98 _private member_ `FDelegateHandle OnLevelActorAddedHandle;`
- L99 _private member_ `FDelegateHandle OnLevelActorDeletedHandle;`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPBookmark/Public/VPBookmarkBlueprintLibrary.h` (Public)


#### class `UVPBookmarkBlueprintLibrary`  
`class UVPBookmarkBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L15-31_
- reflection: `UCLASS(meta=(ScriptName="VPBookmarkLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L21 _public prototype_ `static UVPBookmark* FindVPBookmark(const AActor* Actor);` — `UFUNCTION(BlueprintCallable, Category = "Bookmarks")`
- L24 _public prototype_ `static void GetAllVPBookmarkActors(const UObject* WorldContextObject, TArray<AActor*>& OutActors);` — `UFUNCTION(BlueprintCallable, Category = "Bookmarks", meta = (WorldContext = "WorldContextObject"))`
- L27 _public prototype_ `static void GetAllVPBookmark(const UObject* WorldContextObject, TArray<UVPBookmark*>& OutBookmarks);` — `UFUNCTION(BlueprintCallable, Category = "Bookmarks", meta = (WorldContext = "WorldContextObject"))`
- L30 _public prototype_ `static bool CreateVPBookmarkName(AActor* Bookmark, const FString& FormatString, FString& GeneratedNumber, FString& GeneratedLetter);` — `UFUNCTION(BlueprintCallable, Category = "Bookmarks")`

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPBookmark/Public/VPBookmarkContext.h` (Public)


#### struct `FVPBookmarkCreationContext`  
`struct FVPBookmarkCreationContext`  
_L11-27_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public member_ `FString ConcertCreator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")` — Username of the Concert client who is creating this bookmark.
- L22 _public member_ `FName CategoryName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")` — Category of the Bookmark
- L26 _public member_ `FString DisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bookmarks")` — Name of the Bookmark

### `Plugins/Experimental/VirtualProductionUtilities/Source/VPBookmark/Public/VPBookmarkLifecycleDelegates.h` (Public)


#### class `FVPBookmarkLifecycleDelegates`  
`class FVPBookmarkLifecycleDelegates`  
_L11-19_
- L14 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FVPBookmarkLifecycleDelegate, UVPBookmark*);`
- L16 _public prototype_ `static FVPBookmarkLifecycleDelegate& GetOnBookmarkCreated();`
- L17 _public prototype_ `static FVPBookmarkLifecycleDelegate& GetOnBookmarkDestroyed();`
- L18 _public prototype_ `static FVPBookmarkLifecycleDelegate& GetOnBookmarkCleared();`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FVPBookmarkLifecycleDelegate, UVPBookmark*);`
