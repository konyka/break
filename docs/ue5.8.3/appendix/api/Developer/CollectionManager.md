# Developer / CollectionManager

- module root: `Source/Developer/CollectionManager`
- headers: 12; symbols: 603
- symbol kinds: class=12, delegate=33, enum=6, enumerator=27, function=62, macro=1, member=77, namespace=1, prototype=367, struct=10, typedef=7
- PrivateDependencyModuleNames: Analytics, Core, CoreUObject, DeveloperSettings, DirectoryWatcher, SourceControl

### `Source/Developer/CollectionManager/Private/Collection.h` (Private)


#### struct `ECollectionVersion`  
`struct ECollectionVersion`  
_L14-33_

#### enum `ECollectionVersion::Type`  
`enum Type`  
_L16-32_
- L18 _public enumerator_ `_ZeroVersion = 0`
- L21 _public enumerator_ `Initial` — The initial version for collection files
- L27 _public enumerator_ `AddedCollectionGuid` — Added GUIDs to collections to allow them to be used as a parent of another collection without relying on their name/share-type combo Collections that are older than this version must be re-saved before they can be used as a parent for another collection
- L30 _public enumerator_ `_AutomaticVersionPlusOne` — -----<new versions can be added before this line>-------------------------------------------------
- L31 _public enumerator_ `CurrentVersion = _AutomaticVersionPlusOne - 1`

#### enum `ECollectionCloneMode`  
`enum class ECollectionCloneMode : uint8`  
_L35-41_
- L38 _public enumerator_ `Exact` — Clone this collection exactly as it is now, preserving its existing GUID data
- L40 _public enumerator_ `Unique` — Clone this collection, but make sure it gets unique GUIDs

#### class `FCollection`  
`class FCollection`  
_L47-243_
- desc: A class to represent a collection of assets. Collections are held privately by the collection manager and most thread safety is dealt with by locking at the collection manager level.
- L50 _public prototype_ `FCollection(const FString& InFilename, bool InUseSCC, ECollectionStorageMode::Type InStorageMode);`
- L53 _public prototype_ `TSharedRef<FCollection> Clone(const FString& InFilename, bool InUseSCC, ECollectionCloneMode InCloneMode) const;` — Clone this collection to a new location
- L56 _public prototype_ `bool Load(FText& OutError);` — Loads content from the SourceFilename into this collection. If false, OutError is a human readable warning depicting the error.
- L58 _public prototype_ `bool Save(const TArray<FText>& AdditionalChangelistText, FText& OutError, bool bForceCommitToRevisionControl);` — Saves this collection to SourceFilename. If submitting to source control, AdditionalChangelistText will be added to the changelist description. If false, OutError is a human readable warning depicting the error.
- L60 _public prototype_ `bool Update(FText& OutError);` — Updates this collection to ensure it's the latest version from source control. If false, OutError is a human readable warning depicting the error.
- L62 _public prototype_ `bool Merge(const FCollection& NewCollection);` — Merge the contents of NewCollection into this collection. Returns true if there were changes to merge, or false if the collections were identical.
- L64 _public prototype_ `bool DeleteSourceFile(FText& OutError);` — Deletes the source file for this collection. If false, OutError is a human readable warning depicting the error.
- L66 _public prototype_ `void Empty();` — Empty this collection
- L69 _public prototype_ `bool AddObjectToCollection(const FSoftObjectPath& ObjectPath);` — Adds a single object to the collection. Static collections only.
- L71 _public prototype_ `bool RemoveObjectFromCollection(const FSoftObjectPath& ObjectPath);` — Removes a single object from the collection. Static collections only.
- L73 _public prototype_ `void GetAssetsInCollection(TArray<FSoftObjectPath>& Assets) const;` — Gets a list of assets in the collection. Static collections only.
- L75 _public prototype_ `void GetClassesInCollection(TArray<FTopLevelAssetPath>& Classes) const;` — Gets a list of native classes in the collection. Static collections only.
- L77 _public prototype_ `void GetObjectsInCollection(TArray<FSoftObjectPath>& Objects) const;` — Gets a list of objects in the collection. Static collections only.
- L79 _public prototype_ `bool IsObjectInCollection(const FSoftObjectPath& ObjectPath) const;` — Returns true when the specified object is in the collection. Static collections only.
- L81 _public prototype_ `bool IsRedirectorInCollection(const FSoftObjectPath& ObjectPath) const;` — Returns true when the specified redirector is in the collection. Static collections only.
- L84 _public prototype_ `bool SetDynamicQueryText(const FString& InQueryText);` — Set the dynamic query text for this collection. Dynamic collections only.
- L86 _public prototype_ `FString GetDynamicQueryText() const;` — Get the dynamic query text for this collection. Dynamic collections only.
- L92 _public prototype_ `void PrepareDynamicQuery();` — Prepares an expression evaluator for TestDynamicQuery if it has not yet been created or is out of date. The collection manager must prevent SetDynamicQueryText from being called between PrepareDynamicQuery and TestDynamicQuery. Internally locks against concurrent calls to PrepareDynamicQuery from under a shared read lock.
- L94 _public prototype_ `bool TestDynamicQuery(const ITextFilterExpressionContext& InContext) const;` — Tests the dynamic query for against the context provided. Dynamic collections only. Must call PrepareDynamicQuery first.
- L97 _public prototype_ `FCollectionStatusInfo GetStatusInfo(bool bIsReadOnly) const;` — Get the status info for this collection
- L100 _public prototype_ `bool IsDirty() const;` — Does this collection contain unsaved changes?
- L103 _public prototype_ `bool IsEmpty() const;` — Whether the collection has any contents
- L106 _public prototype_ `bool IsUsingSourceControl() const;` — Whether the Collection uses Source Control
- L109 _public prototype_ `void PrintCollection() const;` — Logs the contents of the collection
- L112 _public function_ `FORCEINLINE const FName& GetCollectionName() const` — Returns the name of the collection
- L115 _public function_ `FORCEINLINE const FGuid& GetCollectionGuid() const` — Returns the GUID of the collection
- L118 _public function_ `FORCEINLINE const FGuid& GetParentCollectionGuid() const` — Returns the GUID of the collection we are parented under
- L121 _public function_ `FORCEINLINE void SetParentCollectionGuid(const FGuid& NewGuid)` — Set the GUID of the collection we are parented under
- L124 _public function_ `FORCEINLINE bool IsAutoGenerated() const` — Get whether this collection is auto-generated by something external instead of maintained by users
- L127 _public function_ `FORCEINLINE TOptional<FLinearColor> GetCollectionColor() const` — Get the color of the collection (if any)
- L130 _public function_ `FORCEINLINE void SetCollectionColor(const TOptional<FLinearColor>& NewColor)` — Set the color of the collection (if any)
- L133 _public function_ `FORCEINLINE ECollectionVersion::Type GetCollectionVersion() const` — Returns the file version of the collection
- L136 _public function_ `ECollectionStorageMode::Type GetStorageMode() const` — Get whether this collection is static or dynamic
- L139 _public function_ `FORCEINLINE const FString& GetSourceFilename() const` — Get the source filename of this collection
- L142 _public function_ `FORCEINLINE const TSet<FSoftObjectPath>& GetObjectSet() const` — Gets set of all objects for fast iteration
- L146 _private prototype_ `void SaveHeaderPairs(TMap<FString,FString>& OutHeaderPairs) const;` — Generates the header pairs for the collection file.
- L154 _private prototype_ `bool LoadHeaderPairs(const TMap<FString,FString>& InHeaderPairs);` — Processes header pairs from the top of a collection file. @param InHeaderPairs The header pairs found at the start of a collection file @return true if the header was valid and loaded properly
- L157 _private prototype_ `template <typename CharType> bool ParseCollection(TStringView<CharType> FullFileContentsString, FText& OutError);`
- L160 _private prototype_ `bool MergeWithCollection(const FCollection& Other);` — Merges the assets from the specified collection with this collection
- L162 _private prototype_ `static void GetObjectDifferences(const TSet<FSoftObjectPath>& BaseSet, const TSet<FSoftObjectPath>& NewSet, TArray<FSoftObjectPath>& ObjectsAdded, TArray<FSoftObjectPath>& ObjectsRemoved);` — Gets the object differences between object set A (base) and B (new)
- L164 _private prototype_ `void GetObjectDifferencesFromDisk(TArray<FSoftObjectPath>& ObjectsAdded, TArray<FSoftObjectPath>& ObjectsRemoved) const;` — Gets the object differences between what we have in memory, and what we loaded from disk. Static collections only.
- L166 _private prototype_ `bool CheckoutCollection(FText& OutError);` — Checks the shared collection out from source control so it may be saved. If false, OutError is a human readable warning depicting the error.
- L168 _private prototype_ `bool CheckinCollection(const TArray<FText>& AdditionalChangelistText, FText& OutError);` — Checks the shared collection in to source control after it is saved. In addition to the normal text, AdditionalChangelistText will be added to the checkin description. If false, OutError is a human readable warning depicting the error.
- L170 _private prototype_ `bool RevertCollection(FText& OutError);` — Reverts the collection in the event that the save was not successful. If false, OutError is a human readable warning depicting the error.
- L172 _private prototype_ `bool DeleteFromSourceControl(FText& OutError);` — Marks the source file for delete in source control. If false, OutError is a human readable warning depicting the error.
- L200 _private member_ `FName CollectionName;` — The name of the collection
- L203 _private member_ `FGuid CollectionGuid;` — The GUID of the collection
- L206 _private member_ `FGuid ParentCollectionGuid;` — The GUID of the collection we are parented under
- L209 _private member_ `TOptional<FLinearColor> CollectionColor;` — The color of the collection (if any)
- L212 _private member_ `bool bUseSCC;` — Source control is used if true
- L215 _private member_ `bool bChangedSinceLastDiskSnapshot = false;` — Indicates if the collection has changes in memory that weren't saved to disk.
- L218 _private member_ `bool bIsAutoGenerated = false;` — Indicates if the collection is auto-generated by something external instead of maintained by users
- L221 _private member_ `FString SourceFilename;` — The filename used to load this collection. Empty if it is new or never loaded from disk.
- L224 _private member_ `TSet<FSoftObjectPath> ObjectSet;` — The set of objects in the collection. Takes the form PackageName.AssetName.Static collections only.
- L227 _private member_ `FString DynamicQueryText;` — The dynamic query string for this collection. Dynamic collections only.
- L230 _private member_ `TDontCopy<UE::FMutex> DynamicQueryExpressionEvaluatorLock;` — Lock preventing concurrent instantiation of DynamicQueryExpressionEvaluatorPtr
- L233 _private member_ `TSharedPtr<FTextFilterExpressionEvaluator> DynamicQueryExpressionEvaluatorPtr;` — Expression evaluator that can be used test against the compiled DynamicQueryText
- L236 _private member_ `ECollectionVersion::Type FileVersion;` — The file version for this collection
- L239 _private member_ `ECollectionStorageMode::Type StorageMode;` — How does this collection store its objects? (static or dynamic)
- L242 _private member_ `FCollectionSnapshot DiskSnapshot;` — The state of the collection the last time it was loaded from or saved to disk.
- L245 _function_ `inline bool FCollection::IsUsingSourceControl() const`

#### struct `FCollection::FCollectionSnapshot`  
`struct FCollectionSnapshot`  
_L176-197_
- desc: Snapshot data for a collection. Used to take snapshots and provide a diff message
- L178 _public function_ `void TakeSnapshot(const FCollection& InCollection)`
- L187 _public member_ `FGuid ParentCollectionGuid;` — The GUID of the collection we are parented under
- L190 _public member_ `TOptional<FLinearColor> CollectionColor;` — The color of the collection (if set)
- L193 _public member_ `TSet<FSoftObjectPath> ObjectSet;` — The set of objects in the collection. Takes the form PackageName.AssetName. Static collections only.
- L196 _public member_ `FString DynamicQueryText;` — The dynamic query string for this collection. Dynamic collections only.

### `Source/Developer/CollectionManager/Private/CollectionContainer.h` (Private)


#### class `FCollectionRecursiveRwLock`  
`UE_INTERNAL class FCollectionRecursiveRwLock`  
_L19-51_
- L34 _public prototype_ `FCollectionRecursiveRwLock();`
- L35 _public prototype_ `~FCollectionRecursiveRwLock();`
- L37 _public prototype_ `void ReadLock();`
- L38 _public prototype_ `void WriteLock();`
- L40 _public prototype_ `void ReadUnlock();`
- L41 _public prototype_ `void WriteUnlock();`
- L46 _public prototype_ `[[nodiscard]] bool PromoteInterruptible();` — Promote the lock from read to write, possibly being interrupted by another writer in between. Returns false if the lock cannot be promoted, which can happen if the thread already holds a read lock then reenters and tries to promote to a write lock.
- L49 _private member_ `FRWLock RwLock;`
- L50 _private member_ `uint32 TlsSlot;`

#### struct `FCollectionRecursiveRwLock::FThreadLockDepths`  
`struct FThreadLockDepths`  
_L21-31_
- L23 _public prototype_ `FThreadLockDepths(void* TlsSlotValue);`
- L25 _public prototype_ `void* GetTlsSlotValue();`
- L27 _public typedef_ `using HalfUPtrInt = uint32;`
- L29 _public member_ `HalfUPtrInt ThreadReadDepth = 0;`
- L30 _public member_ `HalfUPtrInt ThreadWriteDepth = 0;`

#### class `FCollectionContainer`  
`class FCollectionContainer final : public ICollectionContainer`  
_L64-272_
- inherits: `ICollectionContainer`
- L67 _public prototype_ `FCollectionContainer(FCollectionManager& InCollectionManager, const TSharedRef<ICollectionSource>& InCollectionSource);`
- L68 _public prototype_ `~FCollectionContainer();`
- L70 _public function_ `virtual const TSharedRef<ICollectionSource>& GetCollectionSource() const override`
- L75 _public prototype_ `virtual bool IsReadOnly(ECollectionShareType::Type ShareType) const override;`
- L76 _public prototype_ `virtual void SetReadOnly(ECollectionShareType::Type ShareType, bool bReadOnly) override;`
- L77 _public prototype_ `virtual bool IsHidden() const override;`
- L78 _public prototype_ `virtual void SetHidden(bool bHidden) override;`
- L79 _public prototype_ `virtual bool HasCollections() const override;`
- L80 _public prototype_ `virtual void GetCollections(TArray<FCollectionNameType>& OutCollections) const override;`
- L81 _public prototype_ `virtual void GetCollections(FName CollectionName, TArray<FCollectionNameType>& OutCollections) const override;`
- L82 _public prototype_ `virtual void GetCollectionNames(ECollectionShareType::Type ShareType, TArray<FName>& CollectionNames) const override;`
- L83 _public prototype_ `virtual void GetRootCollections(TArray<FCollectionNameType>& OutCollections) const override;`
- L84 _public prototype_ `virtual void GetRootCollectionNames(ECollectionShareType::Type ShareType, TArray<FName>& CollectionNames) const override;`
- L85 _public prototype_ `virtual void GetChildCollections(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FCollectionNameType>& OutCollections) const override;`
- L86 _public prototype_ `virtual void GetChildCollectionNames(FName CollectionName, ECollectionShareType::Type ShareType, ECollectionShareType::Type ChildShareType, TArray<FName>& CollectionNames) const override;`
- L87 _public prototype_ `virtual TOptional<FCollectionNameType> GetParentCollection(FName CollectionName, ECollectionShareType::Type ShareType) const override;`
- L88 _public prototype_ `virtual bool CollectionExists(FName CollectionName, ECollectionShareType::Type ShareType) const override;`
- L89 _public prototype_ `virtual bool GetAssetsInCollection(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FSoftObjectPath>& AssetPaths, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const override;`
- L90 _public prototype_ `virtual bool GetObjectsInCollection(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FSoftObjectPath>& ObjectPaths, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const override;`
- L91 _public prototype_ `virtual bool GetClassesInCollection(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FTopLevelAssetPath>& ClassPaths, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const override;`
- L92 _public prototype_ `virtual void GetCollectionsContainingObject(const FSoftObjectPath& ObjectPath, ECollectionShareType::Type ShareType, TArray<FName>& OutCollectionNames, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const override;`
- L93 _public prototype_ `virtual void GetCollectionsContainingObject(const FSoftObjectPath& ObjectPath, TArray<FCollectionNameType>& OutCollections, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const override;`
- L94 _public prototype_ `virtual void GetCollectionsContainingObjects(const TArray<FSoftObjectPath>& ObjectPaths, TMap<FCollectionNameType, TArray<FSoftObjectPath>>& OutCollectionsAndMatchedObjects, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const override;`
- L95 _public prototype_ `virtual FString GetCollectionsStringForObject(const FSoftObjectPath& ObjectPath, ECollectionShareType::Type ShareType, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self, bool bFullPaths = true) const override;`
- L96 _public prototype_ `virtual FString MakeCollectionPath(FName CollectionName, ECollectionShareType::Type ShareType) const override;`
- L97 _public prototype_ `virtual void CreateUniqueCollectionName(FName BaseName, ECollectionShareType::Type ShareType, FName& OutCollectionName) const override;`
- L98 _public prototype_ `virtual bool IsValidCollectionName(const FString& CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) const override;`
- L99 _public prototype_ `virtual bool CreateCollection(FName CollectionName, ECollectionShareType::Type ShareType, ECollectionStorageMode::Type StorageMode, FText* OutError = nullptr) override;`
- L100 _public prototype_ `virtual bool RenameCollection(FName CurrentCollectionName, ECollectionShareType::Type CurrentShareType, FName NewCollectionName, ECollectionShareType::Type NewShareType, FText* OutError = nullptr) override;`
- L101 _public prototype_ `virtual bool ReparentCollection(FName CollectionName, ECollectionShareType::Type ShareType, FName ParentCollectionName, ECollectionShareType::Type ParentShareType, FText* OutError = nullptr) override;`
- L102 _public prototype_ `virtual bool DestroyCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) override;`
- L103 _public prototype_ `virtual bool AddToCollection(FName CollectionName, ECollectionShareType::Type ShareType, const FSoftObjectPath& ObjectPath, FText* OutError = nullptr) override;`
- L104 _public prototype_ `virtual bool AddToCollection(FName CollectionName, ECollectionShareType::Type ShareType, TConstArrayView<FSoftObjectPath> ObjectPaths, int32* OutNumAdded = nullptr, FText* OutError = nullptr) override;`
- L105 _public prototype_ `virtual bool RemoveFromCollection(FName CollectionName, ECollectionShareType::Type ShareType, const FSoftObjectPath& ObjectPath, FText* OutError = nullptr) override;`
- L106 _public prototype_ `virtual bool RemoveFromCollection(FName CollectionName, ECollectionShareType::Type ShareType, TConstArrayView<FSoftObjectPath> ObjectPaths, int32* OutNumRemoved = nullptr, FText* OutError = nullptr) override;`
- L107 _public prototype_ `virtual bool SetDynamicQueryText(FName CollectionName, ECollectionShareType::Type ShareType, const FString& InQueryText, FText* OutError = nullptr) override;`
- L108 _public prototype_ `virtual bool GetDynamicQueryText(FName CollectionName, ECollectionShareType::Type ShareType, FString& OutQueryText, FText* OutError = nullptr) const override;`
- L109 _public prototype_ `virtual bool TestDynamicQuery(FName CollectionName, ECollectionShareType::Type ShareType, const ITextFilterExpressionContext& InContext, bool& OutResult, FText* OutError = nullptr) const override;`
- L110 _public prototype_ `virtual bool EmptyCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) override;`
- L111 _public prototype_ `virtual bool SaveCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) override;`
- L112 _public prototype_ `virtual bool UpdateCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) override;`
- L113 _public prototype_ `virtual bool GetCollectionStatusInfo(FName CollectionName, ECollectionShareType::Type ShareType, FCollectionStatusInfo& OutStatusInfo, FText* OutError = nullptr) const override;`
- L114 _public prototype_ `virtual bool HasCollectionColors(TArray<FLinearColor>* OutColors = nullptr) const override;`
- L115 _public prototype_ `virtual bool GetCollectionColor(FName CollectionName, ECollectionShareType::Type ShareType, TOptional<FLinearColor>& OutColor, FText* OutError = nullptr) const override;`
- L116 _public prototype_ `virtual bool SetCollectionColor(FName CollectionName, ECollectionShareType::Type ShareType, const TOptional<FLinearColor>& NewColor, FText* OutError = nullptr) override;`
- L117 _public prototype_ `virtual bool GetCollectionStorageMode(FName CollectionName, ECollectionShareType::Type ShareType, ECollectionStorageMode::Type& OutStorageMode, FText* OutError = nullptr) const override;`
- L118 _public prototype_ `virtual bool IsObjectInCollection(const FSoftObjectPath& ObjectPath, FName CollectionName, ECollectionShareType::Type ShareType, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self, FText* OutError = nullptr) const override;`
- L119 _public prototype_ `virtual bool IsValidParentCollection(FName CollectionName, ECollectionShareType::Type ShareType, FName ParentCollectionName, ECollectionShareType::Type ParentShareType, FText* OutError) const override;`
- L125 _public prototype_ `bool UpdateCaches(ECollectionCacheFlags ToUpdate);` — Returns false if the collection container's internal lock cannot be promoted preventing the cache from updating, which can happen if the thread already holds a read lock then reenters and tries to promote to a write lock.
- L127 _public prototype_ `void HandleFixupRedirectors(ICollectionRedirectorFollower& InRedirectorFollower);`
- L128 _public prototype_ `bool HandleRedirectorsDeleted(TConstArrayView<FSoftObjectPath> ObjectPaths, FText* OutError);`
- L129 _public prototype_ `void HandleObjectRenamed(const FSoftObjectPath& OldObjectPath, const FSoftObjectPath& NewObjectPath);`
- L130 _public prototype_ `void HandleObjectsDeleted(TConstArrayView<FSoftObjectPath> ObjectPaths);`
- L133 _public prototype_ `DECLARE_DERIVED_EVENT(FCollectionContainer, ICollectionContainer::FIsHiddenChangedEvent, FIsHiddenChangedEvent);` — Event for when the collection container's hidden state changes
- L134 _public function_ `virtual FIsHiddenChangedEvent& OnIsHiddenChanged() override`
- L137 _public prototype_ `DECLARE_DERIVED_EVENT(FCollectionContainer, ICollectionContainer::FCollectionCreatedEvent, FCollectionCreatedEvent);` — Event for when collections are created
- L138 _public function_ `virtual FCollectionCreatedEvent& OnCollectionCreated() override`
- L141 _public prototype_ `DECLARE_DERIVED_EVENT(FCollectionContainer, ICollectionContainer::FCollectionDestroyedEvent, FCollectionDestroyedEvent);` — Event for when collections are destroyed
- L142 _public function_ `virtual FCollectionDestroyedEvent& OnCollectionDestroyed() override`
- L145 _public function_ `virtual FOnAssetsAddedToCollection& OnAssetsAddedToCollection() override` — Event for when assets are added to a collection
- L148 _public function_ `virtual FOnAssetsRemovedFromCollection& OnAssetsRemovedFromCollection() override` — Event for when assets are removed from a collection
- L151 _public prototype_ `DECLARE_DERIVED_EVENT(FCollectionContainer, ICollectionContainer::FCollectionRenamedEvent, FCollectionRenamedEvent);` — Event for when collections are renamed
- L152 _public function_ `virtual FCollectionRenamedEvent& OnCollectionRenamed() override`
- L155 _public prototype_ `DECLARE_DERIVED_EVENT(FCollectionContainer, ICollectionContainer::FCollectionReparentedEvent, FCollectionReparentedEvent);` — Event for when collections are re-parented
- L156 _public function_ `virtual FCollectionReparentedEvent& OnCollectionReparented() override`
- L159 _public prototype_ `DECLARE_DERIVED_EVENT(FCollectionContainer, ICollectionContainer::FCollectionUpdatedEvent, FCollectionUpdatedEvent);` — Event for when collections is updated, or otherwise changed and we can't tell exactly how (eg, after updating from source control and merging)
- L160 _public function_ `virtual FCollectionUpdatedEvent& OnCollectionUpdated() override`
- L162 _public prototype_ `void OnRemovedFromCollectionManager();`
- L165 _public prototype_ `void TickFileCache();` — Tick this collection container so it can process any file cache events
- L169 _private prototype_ `void LoadCollections();` — Loads all collection files from disk. Must only be called from constructor as it does not lock for the full duration.
- L172 _private prototype_ `bool ShouldUseSCC(ECollectionShareType::Type ShareType) const;` — Returns true if the specified share type requires source control
- L175 _private prototype_ `FString GetCollectionFilename(const FName& InCollectionName, const ECollectionShareType::Type InCollectionShareType) const;` — Given a collection name and share type, work out the full filename for the collection to use on disk
- L178 _private prototype_ `static uint8 GetReadOnlyMask(ECollectionShareType::Type ShareType);` — Returns the read-only bit mask for the specified share type.
- L180 _private prototype_ `bool IsReadOnly(FCollectionScopeLock& InGuard, ECollectionShareType::Type ShareType) const;`
- L183 _private prototype_ `bool ValidateWritable(FCollectionScopeLock& InGuard, ECollectionShareType::Type ShareType, FText* OutError) const;` — Returns whether the collection container is in a valid state for writing
- L186 _private prototype_ `bool AddCollection(FCollectionScopeLock_Write& InGuard, const TSharedRef<FCollection>& CollectionRef, ECollectionShareType::Type ShareType);` — Adds a collection to the lookup maps
- L189 _private prototype_ `bool RemoveCollection(FCollectionScopeLock_Write& InGuard, const TSharedRef<FCollection>& CollectionRef, ECollectionShareType::Type ShareType);` — Removes a collection from the lookup maps
- L192 _private prototype_ `void RemoveObjectFromCollections(FCollectionScopeLock_Write& InGuard, const FSoftObjectPath& ObjectPath, TArray<FCollectionNameType>& OutUpdatedCollections);` — Removes an object from any collections that contain it
- L195 _private prototype_ `void ReplaceObjectInCollections( FCollectionScopeLock_Write& InGuard, const FSoftObjectPath& OldObjectPath, const FSoftObjectPath& NewObjectPath, TArray<FCollectionNameType>& OutUpdatedCollections);` — Replaces an object with another in any collections that contain it
- L204 _private prototype_ `bool InternalSaveCollection(FCollectionScopeLock_Write&, const TSharedRef<FCollection>& CollectionRef, FText* OutError, bool bForceCommitToRevisionControl);` — Internal common functionality for saving a collection bForceCommitToRevisionControl - If the collection's storage mode will save it to source control, then bForceCommitToRevisionControl will ensure that it is committed after save.  If this is false, then the collection will be left as a modified file which can be advantageous for slow source control servers.
- L210 _private prototype_ `bool IsValidParentCollection_Locked(FCollectionScopeLock& InGuard, FName CollectionName, ECollectionShareType::Type ShareType, FName ParentCollectionName, ECollectionShareType::Type ParentShareType, FText* OutError) const;` — Internal version of IsValidParentCollection to avoid taking lock recursively. Cache must be updated for recursion before calling.
- L216 _private prototype_ `bool CollectionExists_Locked(FCollectionScopeLock& InGuard, FName CollectionName, ECollectionShareType::Type ShareType) const;` — Check if the given collection exists. Using the public API function risks acquiring the lock recursively.
- L220 _private member_ `static FStringView CollectionExtension;` — The extension used for collection files
- L223 _private member_ `mutable FCollectionRecursiveRwLock Lock;` — Required for updating caches as well as write operations to collections
- L228 _private member_ `FCollectionManager* CollectionManager;` — The collection managed that is managing this collection container. Null if this collection container has been removed from the collection manager.
- L231 _private member_ `TSharedRef<ICollectionSource> CollectionSource;` — The folders that contain collections
- L235 _private member_ `uint8 ReadOnlyFlags;`
- L238 _private member_ `bool bIsHidden;` — True if the collection container is hidden in the Editor's UI
- L241 _private member_ `TSharedPtr<DirectoryWatcher::FFileCache> CollectionFileCaches[ECollectionShareType::CST_All];` — Array of file cache instances that are watching for the collection files changing on disk
- L244 _private member_ `TMap<FCollectionNameType, TSharedRef<FCollection>> AvailableCollections;` — A map of collection names to FCollection objects
- L247 _private member_ `TPimplPtr<FCollectionContainerCache> CollectionCache;` — Cache of collection hierarchy, identity, etc
- L250 _private member_ `FIsHiddenChangedEvent IsHiddenChangedEvent;` — Event for when the collection container's hidden state changes
- L253 _private member_ `FOnAssetsAddedToCollection AssetsAddedToCollectionDelegate;` — Event for when assets are added to a collection
- L256 _private member_ `FOnAssetsRemovedFromCollection AssetsRemovedFromCollectionDelegate;` — Event for when assets are removed from a collection
- L259 _private member_ `FCollectionRenamedEvent CollectionRenamedEvent;` — Event for when collections are renamed
- L262 _private member_ `FCollectionReparentedEvent CollectionReparentedEvent;` — Event for when collections are re-parented
- L265 _private member_ `FCollectionUpdatedEvent CollectionUpdatedEvent;` — Event for when collections are updated, or otherwise changed and we can't tell exactly how (eg, after updating from source control and merging)
- L268 _private member_ `FCollectionCreatedEvent CollectionCreatedEvent;` — Event for when collections are created
- L271 _private member_ `FCollectionDestroyedEvent CollectionDestroyedEvent;` — Event for when collections are destroyed

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace DirectoryWatcher`
- L133 _delegate_ `DECLARE_DERIVED_EVENT(FCollectionContainer, ICollectionContainer::FIsHiddenChangedEvent, FIsHiddenChangedEvent);` — Event for when the collection container's hidden state changes
- L137 _delegate_ `DECLARE_DERIVED_EVENT(FCollectionContainer, ICollectionContainer::FCollectionCreatedEvent, FCollectionCreatedEvent);` — Event for when collections are created
- L141 _delegate_ `DECLARE_DERIVED_EVENT(FCollectionContainer, ICollectionContainer::FCollectionDestroyedEvent, FCollectionDestroyedEvent);` — Event for when collections are destroyed
- L151 _delegate_ `DECLARE_DERIVED_EVENT(FCollectionContainer, ICollectionContainer::FCollectionRenamedEvent, FCollectionRenamedEvent);` — Event for when collections are renamed
- L155 _delegate_ `DECLARE_DERIVED_EVENT(FCollectionContainer, ICollectionContainer::FCollectionReparentedEvent, FCollectionReparentedEvent);` — Event for when collections are re-parented
- L159 _delegate_ `DECLARE_DERIVED_EVENT(FCollectionContainer, ICollectionContainer::FCollectionUpdatedEvent, FCollectionUpdatedEvent);` — Event for when collections is updated, or otherwise changed and we can't tell exactly how (eg, after updating from source control and merging)

### `Source/Developer/CollectionManager/Private/CollectionManager.h` (Private)


#### struct `FObjectCollectionInfo`  
`struct FObjectCollectionInfo`  
_L17-35_
- desc: Collection info for a given object - gives the collection name, as well as the reason this object is considered to be part of this collection
- L19 _public function_ `explicit FObjectCollectionInfo(const FCollectionNameType& InCollectionKey) : CollectionKey(InCollectionKey) , Reason(0)`
- L25 _public function_ `FObjectCollectionInfo(const FCollectionNameType& InCollectionKey, const ECollectionRecursionFlags::Flags InReason) : CollectionKey(InCollectionKey) , Reason(InReason)`
- L32 _public member_ `FCollectionNameType CollectionKey;` — The key identifying the collection that contains this object
- L34 _public member_ `ECollectionRecursionFlags::Flags Reason;` — The reason(s) why this collection contains this object - this can be tested against the recursion mode when getting the collections for an object

#### enum `ECollectionCacheFlags`  
`enum class ECollectionCacheFlags`  
_L37-48_
- L39 _public enumerator_ `None = 0`
- L40 _public enumerator_ `Names = 1<<0`
- L41 _public enumerator_ `Objects = 1<<1`
- L42 _public enumerator_ `Hierarchy = 1<<2`
- L43 _public enumerator_ `Colors = 1 <<3`
- L46 _public enumerator_ `RecursionWorker = Names | Hierarchy` — Necessary cache updates for calling collection recursion worker
- L47 _public enumerator_ `All = Names | Objects | Hierarchy | Colors`

#### class `FCollectionManager`  
`class FCollectionManager final : public ICollectionManager`  
_L63-230_
- inherits: `ICollectionManager`
- L66 _public prototype_ `FCollectionManager();`
- L67 _public prototype_ `virtual ~FCollectionManager();`
- L69 _public prototype_ `virtual const TSharedRef<ICollectionContainer>& GetProjectCollectionContainer() const override;`
- L70 _public prototype_ `virtual TSharedPtr<ICollectionContainer> AddCollectionContainer(const TSharedRef<ICollectionSource>& CollectionSource) override;`
- L71 _public prototype_ `virtual bool RemoveCollectionContainer(const TSharedRef<ICollectionContainer>& CollectionContainer) override;`
- L72 _public prototype_ `virtual bool HasCollectionContainer(const TSharedRef<ICollectionContainer>& CollectionContainer) const override;`
- L73 _public prototype_ `virtual TSharedPtr<ICollectionContainer> FindCollectionContainer(FName CollectionSourceName) const override;`
- L74 _public prototype_ `virtual TSharedPtr<ICollectionContainer> FindCollectionContainer(const TSharedRef<ICollectionSource>& CollectionSource) const override;`
- L75 _public prototype_ `virtual void GetCollectionContainers(TArray<TSharedPtr<ICollectionContainer>>& OutCollectionContainers) const override;`
- L76 _public prototype_ `virtual void GetVisibleCollectionContainers(TArray<TSharedPtr<ICollectionContainer>>& OutCollectionContainers) const override;`
- L77 _public prototype_ `virtual bool TryParseCollectionPath(const FString& CollectionPath, TSharedPtr<ICollectionContainer>* OutCollectionContainer, FName* OutCollectionName, ECollectionShareType::Type* OutShareType) const override;`
- L79 _public prototype_ `virtual bool HasCollections() const override;`
- L80 _public prototype_ `virtual void GetCollections(TArray<FCollectionNameType>& OutCollections) const override;`
- L81 _public prototype_ `virtual void GetCollections(FName CollectionName, TArray<FCollectionNameType>& OutCollections) const override;`
- L82 _public prototype_ `virtual void GetCollectionNames(ECollectionShareType::Type ShareType, TArray<FName>& CollectionNames) const override;`
- L83 _public prototype_ `virtual void GetRootCollections(TArray<FCollectionNameType>& OutCollections) const override;`
- L84 _public prototype_ `virtual void GetRootCollectionNames(ECollectionShareType::Type ShareType, TArray<FName>& CollectionNames) const override;`
- L85 _public prototype_ `virtual void GetChildCollections(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FCollectionNameType>& OutCollections) const override;`
- L86 _public prototype_ `virtual void GetChildCollectionNames(FName CollectionName, ECollectionShareType::Type ShareType, ECollectionShareType::Type ChildShareType, TArray<FName>& CollectionNames) const override;`
- L87 _public prototype_ `virtual TOptional<FCollectionNameType> GetParentCollection(FName CollectionName, ECollectionShareType::Type ShareType) const override;`
- L88 _public prototype_ `virtual bool CollectionExists(FName CollectionName, ECollectionShareType::Type ShareType) const override;`
- L89 _public prototype_ `virtual bool GetAssetsInCollection(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FSoftObjectPath>& AssetPaths, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const override;`
- L90 _public prototype_ `virtual bool GetObjectsInCollection(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FSoftObjectPath>& ObjectPaths, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const override;`
- L91 _public prototype_ `virtual bool GetClassesInCollection(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FTopLevelAssetPath>& ClassPaths, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const override;`
- L92 _public prototype_ `virtual void GetCollectionsContainingObject(const FSoftObjectPath& ObjectPath, ECollectionShareType::Type ShareType, TArray<FName>& OutCollectionNames, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const override;`
- L93 _public prototype_ `virtual void GetCollectionsContainingObject(const FSoftObjectPath& ObjectPath, TArray<FCollectionNameType>& OutCollections, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const override;`
- L94 _public prototype_ `virtual void GetCollectionsContainingObjects(const TArray<FSoftObjectPath>& ObjectPaths, TMap<FCollectionNameType, TArray<FSoftObjectPath>>& OutCollectionsAndMatchedObjects, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const override;`
- L95 _public prototype_ `virtual FString GetCollectionsStringForObject(const FSoftObjectPath& ObjectPath, ECollectionShareType::Type ShareType, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self, bool bFullPaths = true) const override;`
- L96 _public prototype_ `virtual void CreateUniqueCollectionName(FName BaseName, ECollectionShareType::Type ShareType, FName& OutCollectionName) const override;`
- L97 _public prototype_ `virtual bool IsValidCollectionName(const FString& CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) const override;`
- L98 _public prototype_ `virtual bool CreateCollection(FName CollectionName, ECollectionShareType::Type ShareType, ECollectionStorageMode::Type StorageMode, FText* OutError = nullptr) override;`
- L99 _public prototype_ `virtual bool RenameCollection(FName CurrentCollectionName, ECollectionShareType::Type CurrentShareType, FName NewCollectionName, ECollectionShareType::Type NewShareType, FText* OutError = nullptr) override;`
- L100 _public prototype_ `virtual bool ReparentCollection(FName CollectionName, ECollectionShareType::Type ShareType, FName ParentCollectionName, ECollectionShareType::Type ParentShareType, FText* OutError = nullptr) override;`
- L101 _public prototype_ `virtual bool DestroyCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) override;`
- L102 _public prototype_ `virtual bool AddToCollection(FName CollectionName, ECollectionShareType::Type ShareType, const FSoftObjectPath& ObjectPath, FText* OutError = nullptr) override;`
- L103 _public prototype_ `virtual bool AddToCollection(FName CollectionName, ECollectionShareType::Type ShareType, TConstArrayView<FSoftObjectPath> ObjectPaths, int32* OutNumAdded = nullptr, FText* OutError = nullptr) override;`
- L104 _public prototype_ `virtual bool RemoveFromCollection(FName CollectionName, ECollectionShareType::Type ShareType, const FSoftObjectPath& ObjectPath, FText* OutError = nullptr) override;`
- L105 _public prototype_ `virtual bool RemoveFromCollection(FName CollectionName, ECollectionShareType::Type ShareType, TConstArrayView<FSoftObjectPath> ObjectPaths, int32* OutNumRemoved = nullptr, FText* OutError = nullptr) override;`
- L106 _public prototype_ `virtual bool SetDynamicQueryText(FName CollectionName, ECollectionShareType::Type ShareType, const FString& InQueryText, FText* OutError = nullptr) override;`
- L107 _public prototype_ `virtual bool GetDynamicQueryText(FName CollectionName, ECollectionShareType::Type ShareType, FString& OutQueryText, FText* OutError = nullptr) const override;`
- L108 _public prototype_ `virtual bool TestDynamicQuery(FName CollectionName, ECollectionShareType::Type ShareType, const ITextFilterExpressionContext& InContext, bool& OutResult, FText* OutError = nullptr) const override;`
- L109 _public prototype_ `virtual bool EmptyCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) override;`
- L110 _public prototype_ `virtual bool SaveCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) override;`
- L111 _public prototype_ `virtual bool UpdateCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) override;`
- L112 _public prototype_ `virtual bool GetCollectionStatusInfo(FName CollectionName, ECollectionShareType::Type ShareType, FCollectionStatusInfo& OutStatusInfo, FText* OutError = nullptr) const override;`
- L113 _public prototype_ `virtual bool HasCollectionColors(TArray<FLinearColor>* OutColors = nullptr) const override;`
- L114 _public prototype_ `virtual bool GetCollectionColor(FName CollectionName, ECollectionShareType::Type ShareType, TOptional<FLinearColor>& OutColor, FText* OutError = nullptr) const override;`
- L115 _public prototype_ `virtual bool SetCollectionColor(FName CollectionName, ECollectionShareType::Type ShareType, const TOptional<FLinearColor>& NewColor, FText* OutError = nullptr) override;`
- L116 _public prototype_ `virtual bool GetCollectionStorageMode(FName CollectionName, ECollectionShareType::Type ShareType, ECollectionStorageMode::Type& OutStorageMode, FText* OutError = nullptr) const override;`
- L117 _public prototype_ `virtual bool IsObjectInCollection(const FSoftObjectPath& ObjectPath, FName CollectionName, ECollectionShareType::Type ShareType, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self, FText* OutError = nullptr) const override;`
- L118 _public prototype_ `virtual bool IsValidParentCollection(FName CollectionName, ECollectionShareType::Type ShareType, FName ParentCollectionName, ECollectionShareType::Type ParentShareType, FText* OutError) const override;`
- L120 _public function_ `virtual FText GetLastError() const override` — `UE_DEPRECATED(5.5, "Deprecated for thread safety reasons.")`
- L121 _public prototype_ `virtual void HandleFixupRedirectors(ICollectionRedirectorFollower& InRedirectorFollower) override;`
- L122 _public prototype_ `virtual bool HandleRedirectorDeleted(const FSoftObjectPath& ObjectPath, FText* OutError = nullptr) override;`
- L123 _public prototype_ `virtual bool HandleRedirectorsDeleted(TConstArrayView<FSoftObjectPath> ObjectPaths, FText* OutError = nullptr) override;`
- L124 _public prototype_ `virtual void HandleObjectRenamed(const FSoftObjectPath& OldObjectPath, const FSoftObjectPath& NewObjectPath) override;`
- L125 _public prototype_ `virtual void HandleObjectDeleted(const FSoftObjectPath& ObjectPath) override;`
- L126 _public prototype_ `virtual void HandleObjectsDeleted(TConstArrayView<FSoftObjectPath> ObjectPaths) override;`
- L128 _public prototype_ `virtual void SuppressObjectDeletionHandling() override;`
- L129 _public prototype_ `virtual void ResumeObjectDeletionHandling() override;`
- L132 _public prototype_ `DECLARE_DERIVED_EVENT(FCollectionManager, ICollectionManager::FCollectionContainerCreatedEvent, FCollectionContainerCreatedEvent);` — Event for when collection containers are created
- L133 _public function_ `virtual FCollectionContainerCreatedEvent& OnCollectionContainerCreated() override`
- L136 _public prototype_ `DECLARE_DERIVED_EVENT(FCollectionManager, ICollectionManager::FCollectionContainerDestroyedEvent, FCollectionContainerDestroyedEvent);` — Event for when collection containers are destroyed
- L137 _public function_ `virtual FCollectionContainerDestroyedEvent& OnCollectionContainerDestroyed() override`
- L140 _public prototype_ `DECLARE_DERIVED_EVENT( FCollectionManager, ICollectionManager::FCollectionCreatedEvent, FCollectionCreatedEvent );` — Event for when collections are created
- L141 _public function_ `virtual FCollectionCreatedEvent& OnCollectionCreated() override`
- L144 _public prototype_ `DECLARE_DERIVED_EVENT( FCollectionManager, ICollectionManager::FCollectionDestroyedEvent, FCollectionDestroyedEvent );` — Event for when collections are destroyed
- L145 _public function_ `virtual FCollectionDestroyedEvent& OnCollectionDestroyed() override`
- L148 _public function_ `virtual FOnAssetsAddedToCollection& OnAssetsAddedToCollection() override` — Event for when assets are added to a collection
- L151 _public function_ `virtual FOnAssetsRemovedFromCollection& OnAssetsRemovedFromCollection() override` — Event for when assets are removed from a collection
- L154 _public prototype_ `DECLARE_DERIVED_EVENT( FCollectionManager, ICollectionManager::FCollectionRenamedEvent, FCollectionRenamedEvent );` — Event for when collections are renamed
- L155 _public function_ `virtual FCollectionRenamedEvent& OnCollectionRenamed() override`
- L158 _public prototype_ `DECLARE_DERIVED_EVENT( FCollectionManager, ICollectionManager::FCollectionReparentedEvent, FCollectionReparentedEvent );` — Event for when collections are re-parented
- L159 _public function_ `virtual FCollectionReparentedEvent& OnCollectionReparented() override`
- L162 _public prototype_ `DECLARE_DERIVED_EVENT( FCollectionManager, ICollectionManager::FCollectionUpdatedEvent, FCollectionUpdatedEvent );` — Event for when collections is updated, or otherwise changed and we can't tell exactly how (eg, after updating from source control and merging)
- L163 _public function_ `virtual FCollectionUpdatedEvent& OnCollectionUpdated() override`
- L166 _public prototype_ `DECLARE_DERIVED_EVENT( FCollectionManager, ICollectionManager::FAddToCollectionCheckinDescriptionEvent, FAddToCollectionCheckinDescriptionEvent);` — Event for when collections is updated, or otherwise changed and we can't tell exactly how (eg, after updating from source control and merging)
- L167 _public function_ `virtual FAddToCollectionCheckinDescriptionEvent& OnAddToCollectionCheckinDescriptionEvent() override`
- L170 _private prototype_ `static void InitializeCollectionContainer(const TSharedRef<class FCollectionContainer>& CollectionContainer);`
- L173 _private prototype_ `bool TickFileCache(float InDeltaTime);` — Tick this collection manager so it can process any file cache events
- L175 _private prototype_ `void CollectionCreated(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection);`
- L176 _private prototype_ `void CollectionDestroyed(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection);`
- L177 _private prototype_ `void AssetsAddedToCollection(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection, TConstArrayView<FSoftObjectPath> AssetsAdded);`
- L178 _private prototype_ `void AssetsRemovedFromCollection(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection, TConstArrayView<FSoftObjectPath> AssetsRemoved);`
- L179 _private prototype_ `void CollectionRenamed(ICollectionContainer& CollectionContainer, const FCollectionNameType& OriginalCollection, const FCollectionNameType& NewCollection);`
- L180 _private prototype_ `void CollectionReparented(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection, const TOptional<FCollectionNameType>& OldParent, const TOptional<FCollectionNameType>& NewParent);`
- L181 _private prototype_ `void CollectionUpdated(ICollectionContainer& CollectionContainer, const FCollectionNameType& Collection);`
- L185 _private member_ `FTSTicker::FDelegateHandle TickFileCacheDelegateHandle;` — Delegate handle for the TickFileCache function
- L188 _private member_ `TSharedRef<ICollectionContainer> ProjectCollectionContainer;` — The collection container for the current uproject
- L191 _private member_ `TArray<TSharedPtr<FCollectionContainer>> CollectionContainers;` — All collection containers
- L193 _private member_ `TArray<FSoftObjectPath> DeferredDeletedObjects;`
- L196 _private member_ `FCollectionContainerCreatedEvent CollectionContainerCreatedEvent;` — Event for when collection containers are created
- L199 _private member_ `FCollectionContainerDestroyedEvent CollectionContainerDestroyedEvent;` — Event for when collection containers are destroyed
- L202 _private member_ `FOnAssetsAddedToCollection AssetsAddedToCollectionDelegate;` — Event for when assets are added to a collection
- L205 _private member_ `FOnAssetsRemovedFromCollection AssetsRemovedFromCollectionDelegate;` — Event for when assets are removed from a collection
- L208 _private member_ `FCollectionRenamedEvent CollectionRenamedEvent;` — Event for when collections are renamed
- L211 _private member_ `FCollectionReparentedEvent CollectionReparentedEvent;` — Event for when collections are re-parented
- L214 _private member_ `FCollectionUpdatedEvent CollectionUpdatedEvent;` — Event for when collections are updated, or otherwise changed and we can't tell exactly how (eg, after updating from source control and merging)
- L217 _private member_ `FCollectionCreatedEvent CollectionCreatedEvent;` — Event for when collections are created
- L220 _private member_ `FCollectionDestroyedEvent CollectionDestroyedEvent;` — Event for when collections are destroyed
- L223 _private member_ `FAddToCollectionCheckinDescriptionEvent AddToCollectionCheckinDescriptionEvent;` — When a collection checkin happens, use this event to add additional text to the changelist description
- L226 _private member_ `int32 SuppressObjectDeletionRefCount = 0;` — Ref count for deferring calls to HandleObjectsDeleted. When the ref count reaches 0 we flush all deferred notifications
- L229 _private member_ `bool bNoFixupRedirectors;` — When true, redirectors will not be automatically followed in collections during startup

#### Free symbols / members of external scopes

- L49 _prototype_ `ENUM_CLASS_FLAGS(ECollectionCacheFlags);`
- L53 _typedef_ `typedef TMap<FCollectionNameType, TSharedRef<FCollection>> FAvailableCollectionsMap;` — `UE_DEPRECATED(5.5, "These typedefs have been deprecated. Replace them with their concrete types.")`
- L55 _typedef_ `typedef TMap<FGuid, FCollectionNameType> FGuidToCollectionNamesMap;` — `UE_DEPRECATED(5.5, "These typedefs have been deprecated. Replace them with their concrete types.")`
- L57 _typedef_ `typedef TMap<FSoftObjectPath, TArray<FObjectCollectionInfo>> FCollectionObjectsMap;` — `UE_DEPRECATED(5.5, "These typedefs have been deprecated. Replace them with their concrete types.")`
- L59 _typedef_ `typedef TMap<FGuid, TArray<FGuid>> FCollectionHierarchyMap;` — `UE_DEPRECATED(5.5, "These typedefs have been deprecated. Replace them with their concrete types.")`
- L61 _typedef_ `typedef TArray<FLinearColor> FCollectionColorArray;` — `UE_DEPRECATED(5.5, "These typedefs have been deprecated. Replace them with their concrete types.")`
- L132 _delegate_ `DECLARE_DERIVED_EVENT(FCollectionManager, ICollectionManager::FCollectionContainerCreatedEvent, FCollectionContainerCreatedEvent);` — Event for when collection containers are created
- L136 _delegate_ `DECLARE_DERIVED_EVENT(FCollectionManager, ICollectionManager::FCollectionContainerDestroyedEvent, FCollectionContainerDestroyedEvent);` — Event for when collection containers are destroyed
- L140 _delegate_ `DECLARE_DERIVED_EVENT( FCollectionManager, ICollectionManager::FCollectionCreatedEvent, FCollectionCreatedEvent );` — Event for when collections are created
- L144 _delegate_ `DECLARE_DERIVED_EVENT( FCollectionManager, ICollectionManager::FCollectionDestroyedEvent, FCollectionDestroyedEvent );` — Event for when collections are destroyed
- L154 _delegate_ `DECLARE_DERIVED_EVENT( FCollectionManager, ICollectionManager::FCollectionRenamedEvent, FCollectionRenamedEvent );` — Event for when collections are renamed
- L158 _delegate_ `DECLARE_DERIVED_EVENT( FCollectionManager, ICollectionManager::FCollectionReparentedEvent, FCollectionReparentedEvent );` — Event for when collections are re-parented
- L162 _delegate_ `DECLARE_DERIVED_EVENT( FCollectionManager, ICollectionManager::FCollectionUpdatedEvent, FCollectionUpdatedEvent );` — Event for when collections is updated, or otherwise changed and we can't tell exactly how (eg, after updating from source control and merging)
- L166 _delegate_ `DECLARE_DERIVED_EVENT( FCollectionManager, ICollectionManager::FAddToCollectionCheckinDescriptionEvent, FAddToCollectionCheckinDescriptionEvent);` — Event for when collections is updated, or otherwise changed and we can't tell exactly how (eg, after updating from source control and merging)

### `Source/Developer/CollectionManager/Private/CollectionManagerConsoleCommands.h` (Private)


#### class `FCollectionManagerConsoleCommands`  
`class FCollectionManagerConsoleCommands`  
_L15-299_
- L18 _public member_ `const FCollectionManagerModule& Module;`
- L20 _public member_ `FAutoConsoleCommand CreateCommand;`
- L21 _public member_ `FAutoConsoleCommand DestroyCommand;`
- L22 _public member_ `FAutoConsoleCommand AddCommand;`
- L23 _public member_ `FAutoConsoleCommand RemoveCommand;`
- L25 _public function_ `FCollectionManagerConsoleCommands(const FCollectionManagerModule& InModule) : Module(InModule) , CreateCommand( TEXT( "CollectionManager.Create" ), *LOCTEXT("CommandText_Create", "Creates a collection of the specified name and type").ToString(), FConsoleCommandWithArgsDelegate::CreateRaw( this, &FCollectionManagerConsoleCommands::Create ) ) , DestroyCommand( TEXT( "CollectionManager.Destroy" ), *LOCTEXT("CommandText_Destroy", "Deletes a collection of the specified name and type").ToString(), FConsoleCommandWithArgsDelegate::CreateRaw( this, &FCollectionManagerConsoleCommands::Destroy ) ) , AddCommand( TEXT( "CollectionManager.Add" ), *LOCTEXT("CommandText_Add", "Adds the specified object path to the specified collection").ToString(), FConsoleCommandWithArgsDelegate::CreateRaw( this, &FCollectionManagerConsoleCommands::Add ) ) , RemoveCommand( TEXT( "CollectionManager.Remove" ), *LOCTEXT("CommandText_Remove", "Removes the specified object path from the specified collection").ToString(), FConsoleCommandWithArgsDelegate::CreateRaw( this, &FCollectionManagerConsoleCommands::Remove ) )`
- L45 _public function_ `void Create(const TArray<FString>& Args)`
- L126 _public function_ `void Destroy(const TArray<FString>& Args)`
- L183 _public function_ `void Add(const TArray<FString>& Args)`
- L241 _public function_ `void Remove(const TArray<FString>& Args)`

#### Free symbols / members of external scopes

- L13 _macro_ `#define LOCTEXT_NAMESPACE "CollectionManager"`

### `Source/Developer/CollectionManager/Private/CollectionManagerLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCollectionManager, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCollectionManager, Log, All);`

### `Source/Developer/CollectionManager/Private/ProjectCollectionSource.h` (Private)


#### class `FProjectCollectionSource`  
`class FProjectCollectionSource : public ICollectionSource`  
_L7-26_
- inherits: `ICollectionSource`
- L10 _public prototype_ `FProjectCollectionSource();`
- L12 _public prototype_ `FName GetName() const override;`
- L14 _public prototype_ `FText GetTitle() const override;`
- L16 _public prototype_ `const FString& GetCollectionFolder(const ECollectionShareType::Type InCollectionShareType) const override;`
- L18 _public prototype_ `FString GetEditorPerProjectIni() const override;`
- L20 _public prototype_ `FString GetSourceControlStatusHintFilename() const override;`
- L22 _public prototype_ `TArray<FText> GetSourceControlCheckInDescription(FName CollectionName) const override;`
- L25 _private member_ `FString CollectionFolders[ECollectionShareType::CST_All];`

### `Source/Developer/CollectionManager/Public/CollectionManagerModule.h` (Public)


#### class `FCollectionManagerModule`  
`class FCollectionManagerModule : public IModuleInterface`  
_L12-54_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule();`
- L16 _public prototype_ `virtual void ShutdownModule();`
- L18 _public prototype_ `virtual ICollectionManager& Get() const;`
- L26 _public function_ `static inline FCollectionManagerModule& GetModule()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L45 _public function_ `static inline bool IsModuleAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L52 _private member_ `ICollectionManager* CollectionManager;`
- L53 _private member_ `class FCollectionManagerConsoleCommands* ConsoleCommands;`

### `Source/Developer/CollectionManager/Public/CollectionManagerTypes.h` (Public)


#### struct `ECollectionStorageMode`  
`struct ECollectionStorageMode`  
_L12-70_
- L22 _public function_ `static Type FromString(const TCHAR* InString, const Type ReturnIfConversionFails = Static)`
- L29 _public function_ `static const TCHAR* ToString(const Type InType)`
- L43 _public function_ `static FText ToText(const Type InType)`
- L57 _public function_ `static FText GetDescription(const Type InType)`

#### enum `ECollectionStorageMode::Type`  
`enum Type`  
_L14-20_
- L17 _public enumerator_ `Static` — This collection stores a list of contained objects.
- L19 _public enumerator_ `Dynamic` — This collection stores a query that can be run against the Content Browser. This type of collection never directly knows what objects it contains.

#### struct `ECollectionShareType`  
`struct ECollectionShareType`  
_L72-192_
- L84 _public function_ `static Type FromString(const TCHAR* InString, const Type ReturnIfConversionFails = CST_All)`
- L94 _public function_ `static const TCHAR* ToString(const Type InType)`
- L114 _public function_ `static FText ToText(const Type InType)`
- L134 _public function_ `static FText GetDescription(const Type InType)`
- L152 _public function_ `static FName GetIconStyleName(const Type InType, const TCHAR* InSizeSuffix = TEXT(".Small"))`
- L170 _public function_ `static bool IsValidChildType(const Type InParentType, const Type InChildType)`

#### enum `ECollectionShareType::Type`  
`enum Type`  
_L74-82_
- L76 _public enumerator_ `CST_System`
- L77 _public enumerator_ `CST_Local`
- L78 _public enumerator_ `CST_Private`
- L79 _public enumerator_ `CST_Shared`
- L81 _public enumerator_ `CST_All`

#### struct `ECollectionRecursionFlags`  
`struct ECollectionRecursionFlags`  
_L197-216_
- desc: Controls how the collections manager will recurse when performing work against a given collection
- L199 _public typedef_ `typedef uint32 Flags;`

#### enum `ECollectionRecursionFlags::Flag`  
`enum Flag`  
_L200-215_
- L203 _public enumerator_ `Self = 1<<0` — Include the current collection when performing work
- L205 _public enumerator_ `Parents = 1<<1` — Include the parent collections when performing work
- L207 _public enumerator_ `Children = 1<<2` — Include the child collections when performing work
- L210 _public enumerator_ `SelfAndParents = Self | Parents` — Include parent collections in addition to the current collection
- L212 _public enumerator_ `SelfAndChildren = Self | Children` — Include child collections in addition to the current collection
- L214 _public enumerator_ `All = Self | Parents | Children` — Include parent and child collections in addition to the current collection

#### struct `FCollectionNameType`  
`struct FCollectionNameType`  
_L219-246_
- desc: A name/type pair to uniquely identify a collection in a collection container
- L221 _public function_ `FCollectionNameType(FName InName, ECollectionShareType::Type InType) : Name(InName) , Type(InType)`
- L226 _public function_ `bool operator==(const FCollectionNameType& Other) const`
- L231 _public function_ `bool operator!=(const FCollectionNameType& Other) const`
- L244 _public member_ `FName Name;`
- L245 _public member_ `ECollectionShareType::Type Type;`

#### struct `FCollectionRef`  
`struct FCollectionRef`  
_L249-292_
- desc: A struct to uniquely identify a collection
- L251 _public function_ `FCollectionRef(const TSharedPtr<ICollectionContainer>& InContainer, const FCollectionNameType& InCollection) : Container(InContainer) , Name(InCollection.Name) , Type(InCollection.Type)`
- L258 _public function_ `FCollectionRef(const TSharedPtr<ICollectionContainer>& InContainer, FName InName, ECollectionShareType::Type InType) : Container(InContainer) , Name(InName) , Type(InType)`
- L265 _public function_ `bool operator==(const FCollectionRef& Other) const`
- L270 _public function_ `bool operator!=(const FCollectionRef& Other) const`
- L284 _public function_ `bool IsValid() const`
- L289 _public member_ `TSharedPtr<ICollectionContainer> Container;`
- L290 _public member_ `FName Name;`
- L291 _public member_ `ECollectionShareType::Type Type;`

#### struct `FCollectionStatusInfo`  
`struct FCollectionStatusInfo`  
_L295-311_
- desc: The status information for a collection
- L298 _public member_ `bool bIsDirty;` — True if the collection has unsaved changes
- L301 _public member_ `bool bIsEmpty;` — True if the collection is empty
- L304 _public member_ `bool bUseSCC;` — True if the collection uses SCC
- L307 _public member_ `int32 NumObjects;` — Number of objects within the collection (static collections only)
- L310 _public member_ `FSourceControlStatePtr SCCState;` — The current source control state of the collection. Only filled in for those collections that are under source control, but may also be empty if the SCC is unavailable (see bUseSCC)

#### class `ICollectionRedirectorFollower`  
`class ICollectionRedirectorFollower`  
_L313-320_
- L316 _public prototype_ `virtual ~ICollectionRedirectorFollower() = default;`
- L319 _public prototype_ `virtual bool FixupObject(const FSoftObjectPath& InObjectPath, FSoftObjectPath& OutNewObjectPath) = 0;` — Given an object path, will see if it needs to follow any redirectors, and if so, will populate OutNewObjectPath with the new name and return true

#### Free symbols / members of external scopes

- L194 _prototype_ `ENUM_RANGE_BY_COUNT(ECollectionShareType::Type, ECollectionShareType::CST_All);`
- L236 _function_ `friend inline uint32 GetTypeHash( const FCollectionNameType& Key )`
- L275 _function_ `friend inline uint32 GetTypeHash(const FCollectionRef& Key)`

### `Source/Developer/CollectionManager/Public/CollectionSettings.h` (Public)


#### class `UCollectionSettings`  
`class UCollectionSettings : public UDeveloperSettings`  
_L9-22_
- reflection: `UCLASS(minimalapi, config=EditorSettings)`
- inherits: `UDeveloperSettings`
- L15 _public prototype_ `FText GetSectionText() const override;`
- L16 _public prototype_ `FText GetSectionDescription() const override;`
- L21 _public member_ `bool bAutoCommitOnSave = true;` — `UPROPERTY(config, EditAnywhere, Category=Collections, meta = (DisplayName="Auto-Commit to SourceControl on Save"))` — When enabled, Shared and Private collections will automatically commit their changes to source control

### `Source/Developer/CollectionManager/Public/ICollectionContainer.h` (Public)


#### class `ICollectionContainer`  
`class ICollectionContainer : public TSharedFromThis<ICollectionContainer>`  
_L11-405_
- inherits: `TSharedFromThis<ICollectionContainer>`
- L14 _public prototype_ `ICollectionContainer() = default;`
- L15 _public prototype_ `ICollectionContainer(const ICollectionContainer&) = delete;`
- L16 _public prototype_ `virtual ~ICollectionContainer() = default;`
- L18 _public prototype_ `ICollectionContainer& operator=(const ICollectionContainer&) = delete;`
- L21 _public prototype_ `virtual const TSharedRef<ICollectionSource>& GetCollectionSource() const = 0;` — Returns the source of the collections in this container
- L24 _public prototype_ `virtual bool IsReadOnly(ECollectionShareType::Type ShareType) const = 0;` — Returns whether or not the collection container is read-only for the specified share type
- L27 _public prototype_ `virtual void SetReadOnly(ECollectionShareType::Type ShareType, bool bReadOnly) = 0;` — Sets whether or not the collection container is read-only for the specified share type
- L30 _public prototype_ `virtual bool IsHidden() const = 0;` — Returns whether or not the collection container should be hidden in the Editor's UI
- L33 _public prototype_ `virtual void SetHidden(bool bHidden) = 0;` — Sets whether or not the collection container should be hidden in the Editor's UI
- L36 _public prototype_ `virtual bool HasCollections() const = 0;` — Returns whether or not the collection container contains any collections
- L39 _public prototype_ `virtual void GetCollections(TArray<FCollectionNameType>& OutCollections) const = 0;` — Returns the list of collections
- L42 _public prototype_ `virtual void GetCollections(FName CollectionName, TArray<FCollectionNameType>& OutCollections) const = 0;` — Returns the list of collections with the given name
- L45 _public prototype_ `virtual void GetCollectionNames(ECollectionShareType::Type ShareType, TArray<FName>& CollectionNames) const = 0;` — Returns the list of collection names of the specified share type
- L48 _public prototype_ `virtual void GetRootCollections(TArray<FCollectionNameType>& OutCollections) const = 0;` — Returns the list of root-level collections
- L51 _public prototype_ `virtual void GetRootCollectionNames(ECollectionShareType::Type ShareType, TArray<FName>& CollectionNames) const = 0;` — Returns the list of root-level collection names of the specified share type
- L54 _public prototype_ `virtual void GetChildCollections(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FCollectionNameType>& OutCollections) const = 0;` — Returns the list of child collections of the given collection
- L57 _public prototype_ `virtual void GetChildCollectionNames(FName CollectionName, ECollectionShareType::Type ShareType, ECollectionShareType::Type ChildShareType, TArray<FName>& CollectionNames) const = 0;` — Returns the list of child collections of the given collection that are also of the specified share type
- L60 _public prototype_ `virtual TOptional<FCollectionNameType> GetParentCollection(FName CollectionName, ECollectionShareType::Type ShareType) const = 0;` — Returns the parent collection of the given collection, or an unset value if there is no parent set
- L63 _public prototype_ `virtual bool CollectionExists(FName CollectionName, ECollectionShareType::Type ShareType) const = 0;` — Returns true if the collection exists
- L70 _public prototype_ `virtual bool GetAssetsInCollection(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FSoftObjectPath>& OutAssetPaths, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const = 0;` — Gets a list of assets in the given collection @return true if any objects were found
- L77 _public prototype_ `virtual bool GetClassesInCollection(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FTopLevelAssetPath>& ClassPaths, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const = 0;` — Gets a list of class paths in the given collection @return true if any objects were found
- L84 _public prototype_ `virtual bool GetObjectsInCollection(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FSoftObjectPath>& ObjectPaths, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const = 0;` — Gets a list of objects in the given collection @return true if any objects were found
- L87 _public prototype_ `virtual void GetCollectionsContainingObject(const FSoftObjectPath& ObjectPath, ECollectionShareType::Type ShareType, TArray<FName>& OutCollectionNames, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const = 0;` — Returns a list of collections in which the specified object exists of the specified share type
- L90 _public prototype_ `virtual void GetCollectionsContainingObject(const FSoftObjectPath& ObjectPath, TArray<FCollectionNameType>& OutCollections, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const = 0;` — Returns a list of collections in which the specified object exists
- L93 _public prototype_ `virtual void GetCollectionsContainingObjects(const TArray<FSoftObjectPath>& ObjectPaths, TMap<FCollectionNameType, TArray<FSoftObjectPath>>& OutCollectionsAndMatchedObjects, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const = 0;` — Returns a list of collections in which any of the specified objects exist
- L96 _public prototype_ `virtual FString GetCollectionsStringForObject(const FSoftObjectPath& ObjectPath, ECollectionShareType::Type ShareType, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self, bool bFullPaths = true) const = 0;` — Returns a string containing a comma separated list of collections in which the specified object exists of the specified share type
- L99 _public prototype_ `virtual FString MakeCollectionPath(FName CollectionName, ECollectionShareType::Type ShareType) const = 0;` — Returns a path that uniquely identifies a collection
- L106 _public prototype_ `virtual void CreateUniqueCollectionName(FName BaseName, ECollectionShareType::Type ShareType, FName& OutCollectionName) const = 0;` — Creates a unique collection name for the given type taking the form BaseName+(unique number) @warning This function is threadsafe but it does not secure the name from another thread creating the collection in between calls to the ICollectionContainer API.
- L117 _public prototype_ `virtual bool IsValidCollectionName( const FString& CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) const = 0;` — Check whether the given name is valid for a new collection. @param CollectionName Potential collection name @param ShareType Type of collection to check for conflicts against. CST_All checks against all collcetion types. @param OutError Optional human readable explanation of why the operation failed @return true If a collection can be created with the name. @return false If the name contains invalid characters or conflicts with an existing collection of the same type.
- L129 _public prototype_ `virtual bool CreateCollection( FName CollectionName, ECollectionShareType::Type ShareType, ECollectionStorageMode::Type StorageMode, FText* OutError = nullptr) = 0;` — Creates a new collection. A .collection file will be added to disk. @param CollectionName The name of the new collection @param ShareType The way the collection is shared. @param StorageMode How does this collection store its objects? (static or dynamic) @param OutError Optional human readable explanation of why the operation failed @return true if the add was successful.
- L143 _public prototype_ `virtual bool RenameCollection( FName CurrentCollectionName, ECollectionShareType::Type CurrentShareType, FName NewCollectionName, ECollectionShareType::Type NewShareType, FText* OutError = nullptr) = 0;` — Renames a collection. A .collection file will be added to disk and a .collection file will be removed. @param CurrentCollectionName The current name of the collection. @param CurrentShareType The current way the collection is shared. @param NewCollectionName The new name of the collection. @param NewShareType The new way the collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the rename was successful.
- L158 _public prototype_ `virtual bool ReparentCollection( FName CollectionName, ECollectionShareType::Type ShareType, FName ParentCollectionName, ECollectionShareType::Type ParentShareType, FText* OutError = nullptr) = 0;` — Re-parents a collection. The parent collection may be re-saved if it's too old to have a stable GUID. @param CollectionName The name of the collection to set the parent of. @param ShareType The way the collection is shared. @param ParentCollectionName The new parent of the collection, or None to have the collection become a root collection. @param ParentShareType The way the new parent collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the re-parent was successful.
- L170 _public prototype_ `virtual bool DestroyCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) = 0;` — Removes a collection to the asset registry. A .collection file will be deleted from disk. @param CollectionName The name of the collection to remove. @param ShareType The way the collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the remove was successful
- L182 _public prototype_ `virtual bool AddToCollection( FName CollectionName, ECollectionShareType::Type ShareType, const FSoftObjectPath& ObjectPath, FText* OutError = nullptr) = 0;` — Adds an asset to the specified collection. @param CollectionName The collection in which to add the asset @param ShareType The way the collection is shared. @param ObjectPath the ObjectPath of the asset to add. @param OutNumAdded if non-NULL, the number of objects successfully added to the collection @param OutError Optional human readable explanation of why the operation failed @return true if the add was successful.
- L185 _public prototype_ `virtual bool AddToCollection( FName CollectionName, ECollectionShareType::Type ShareType, TConstArrayView<FSoftObjectPath> ObjectPaths, int32* OutNumAdded = nullptr, FText* OutError = nullptr) = 0;`
- L199 _public prototype_ `virtual bool RemoveFromCollection( FName CollectionName, ECollectionShareType::Type ShareType, const FSoftObjectPath& ObjectPath, FText* OutError = nullptr) = 0;` — Removes the asset from the specified collection. @param CollectionName The collection from which to remove the asset @param ShareType The way the collection is shared. @param ObjectPath the ObjectPath of the asset to remove. @param OutNumRemoved if non-NULL, the number of objects successfully removed from the collection @param OutError Optional human readable explanation of why the operation failed @return true if the remove was successful.
- L202 _public prototype_ `virtual bool RemoveFromCollection( FName CollectionName, ECollectionShareType::Type ShareType, TConstArrayView<FSoftObjectPath> ObjectPaths, int32* OutNumRemoved = nullptr, FText* OutError = nullptr) = 0;`
- L215 _public prototype_ `virtual bool SetDynamicQueryText( FName CollectionName, ECollectionShareType::Type ShareType, const FString& InQueryText, FText* OutError = nullptr) = 0;` — Sets the dynamic query text for the specified collection. @param CollectionName The collection to set the query on. @param ShareType The way the collection is shared. @param InQueryText The new query to set. @param OutError Optional human readable explanation of why the operation failed @return true if the set was successful.
- L228 _public prototype_ `virtual bool GetDynamicQueryText( FName CollectionName, ECollectionShareType::Type ShareType, FString& OutQueryText, FText* OutError = nullptr) const = 0;` — Gets the dynamic query text for the specified collection. @param CollectionName The collection to get the query from. @param ShareType The way the collection is shared. @param OutQueryText Filled with the query text. @param OutError Optional human readable explanation of why the operation failed @return true if the get was successful.
- L242 _public prototype_ `virtual bool TestDynamicQuery( FName CollectionName, ECollectionShareType::Type ShareType, const ITextFilterExpressionContext& InContext, bool& OutResult, FText* OutError = nullptr) const = 0;` — Tests the dynamic query for the specified collection against the context provided. @param CollectionName The collection to get the query from. @param ShareType The way the collection is shared. @param InContext The context to test against. @param OutResult Filled with the result of the query. @param OutError Optional human readable explanation of why the operation failed @return true if the get was successful.
- L254 _public prototype_ `virtual bool EmptyCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) = 0;` — Removes all assets from the specified collection. @param CollectionName The collection to empty @param ShareType The way the collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the clear was successful.
- L269 _public prototype_ `virtual bool SaveCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) = 0;` — Save the collection (if dirty) and check it into source control (if under SCC control) Note: Generally you won't need to save collections manually as the collection container takes care of that as objects and added/removed, etc. however, you may want to manually save a collection if a previous save attempt failed (and you've since corrected the issue), or if the collection contains redirected object references that you'd like to save to disk. @param CollectionName The collection to save @param ShareType The way the collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the save was successful.
- L283 _public prototype_ `virtual bool UpdateCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) = 0;` — Update the collection to make sure it's using the latest version from source control (if under SCC control) Note: Generally you won't need to update collections manually as the collection container takes care of that as collections are saved to disk. @param CollectionName The collection to update @param ShareType The way the collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the update was successful.
- L294 _public prototype_ `virtual bool GetCollectionStatusInfo( FName CollectionName, ECollectionShareType::Type ShareType, FCollectionStatusInfo& OutStatusInfo, FText* OutError = nullptr) const = 0;` — Gets the status info for the specified collection @param CollectionName The collection to get the status info for @param ShareType The way the collection is shared. @param OutStatusInfo The status info to populate. @param OutError Optional human readable explanation of why the operation failed @return true if the status info was filled in.
- L304 _public prototype_ `virtual bool HasCollectionColors(TArray<FLinearColor>* OutColors = nullptr) const = 0;` — Checks whether any collections have a custom color set, optionally retrieving the list of in-use colors @param OutColors The optional color array to populate. @return true if there are any custom colors in use, false otherwise.
- L315 _public prototype_ `virtual bool GetCollectionColor( FName CollectionName, ECollectionShareType::Type ShareType, TOptional<FLinearColor>& OutColor, FText* OutError = nullptr) const = 0;` — Gets the optional color for the specified collection @param CollectionName The collection to get the color for @param ShareType The way the collection is shared. @param OutColor The optional color to populate. @param OutError Optional human readable explanation of why the operation failed @return true if the collection was found, and the color was optionally filled in.
- L328 _public prototype_ `virtual bool SetCollectionColor( FName CollectionName, ECollectionShareType::Type ShareType, const TOptional<FLinearColor>& NewColor, FText* OutError = nullptr) = 0;` — Sets the optional color for the specified collection @param CollectionName The collection to set the color for @param ShareType The way the collection is shared. @param NewColor The optional color to set. @param OutError Optional human readable explanation of why the operation failed @return true if the collection was found, and the color was set.
- L341 _public prototype_ `virtual bool GetCollectionStorageMode( FName CollectionName, ECollectionShareType::Type ShareType, ECollectionStorageMode::Type& OutStorageMode, FText* OutError = nullptr) const = 0;` — Gets the method by which the specified collection stores its objects (static or dynamic) @param CollectionName The collection to get the storage mode for @param ShareType The way the collection is shared. @param OutStorageMode The variable to populate. @param OutError Optional human readable explanation of why the operation failed @return true if the status info was filled in.
- L354 _public prototype_ `virtual bool IsObjectInCollection( const FSoftObjectPath& ObjectPath, FName CollectionName, ECollectionShareType::Type ShareType, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self, FText* OutError = nullptr) const = 0;` — Check to see if the given object exists in the given collection @param ObjectPath The object to test for its existence in the collection. @param CollectionName The collection to test. @param ShareType The way the collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the object is in the collection.
- L370 _public prototype_ `virtual bool IsValidParentCollection( FName CollectionName, ECollectionShareType::Type ShareType, FName ParentCollectionName, ECollectionShareType::Type ParentShareType, FText* OutError = nullptr) const = 0;` — Check to see if the given collection is valid to be used as the parent of another collection. A collection may not be parented to itself, nor any of its current children. @param CollectionName The name of the collection to check the parent of. @param ShareType The way the collection is shared. @param ParentCollectionName The name of the parent collection to test against. @param ParentShareType The way the new parent collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the parent is considered valid for this collection.
- L375 _public prototype_ `DECLARE_EVENT_TwoParams(ICollectionContainer, FIsHiddenChangedEvent, ICollectionContainer&, bool);` — Event for when the collection container's hidden state changes
- L376 _public prototype_ `virtual FIsHiddenChangedEvent& OnIsHiddenChanged() = 0;`
- L379 _public prototype_ `DECLARE_EVENT_TwoParams(ICollectionContainer, FCollectionCreatedEvent, ICollectionContainer&, const FCollectionNameType&);` — Event for when collections are created
- L380 _public prototype_ `virtual FCollectionCreatedEvent& OnCollectionCreated() = 0;`
- L383 _public prototype_ `DECLARE_EVENT_TwoParams(ICollectionContainer, FCollectionDestroyedEvent, ICollectionContainer&, const FCollectionNameType&);` — Event for when collections are destroyed
- L384 _public prototype_ `virtual FCollectionDestroyedEvent& OnCollectionDestroyed() = 0;`
- L387 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAssetsAddedToCollection, ICollectionContainer&, const FCollectionNameType&, TConstArrayView<FSoftObjectPath>);` — Event for when assets are added to a collection
- L388 _public prototype_ `virtual FOnAssetsAddedToCollection& OnAssetsAddedToCollection() = 0;`
- L391 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAssetsRemovedFromCollection, ICollectionContainer&, const FCollectionNameType&, TConstArrayView<FSoftObjectPath>);` — Event for when assets are removed from a collection
- L392 _public prototype_ `virtual FOnAssetsRemovedFromCollection& OnAssetsRemovedFromCollection() = 0;`
- L395 _public prototype_ `DECLARE_EVENT_ThreeParams(ICollectionContainer, FCollectionRenamedEvent, ICollectionContainer&, const FCollectionNameType&, const FCollectionNameType&);` — Event for when collections are renamed
- L396 _public prototype_ `virtual FCollectionRenamedEvent& OnCollectionRenamed() = 0;`
- L399 _public prototype_ `DECLARE_EVENT_FourParams(ICollectionContainer, FCollectionReparentedEvent, ICollectionContainer&, const FCollectionNameType&, const TOptional<FCollectionNameType>&, const TOptional<FCollectionNameType>&);` — Event for when collections are re-parented (params: Collection, OldParent, NewParent)
- L400 _public prototype_ `virtual FCollectionReparentedEvent& OnCollectionReparented() = 0;`
- L403 _public prototype_ `DECLARE_EVENT_TwoParams(ICollectionContainer, FCollectionUpdatedEvent, ICollectionContainer&, const FCollectionNameType&);` — Event for when collections is updated, or otherwise changed and we can't tell exactly how (eg, after updating from source control and merging)
- L404 _public prototype_ `virtual FCollectionUpdatedEvent& OnCollectionUpdated() = 0;`

#### Free symbols / members of external scopes

- L375 _delegate_ `DECLARE_EVENT_TwoParams(ICollectionContainer, FIsHiddenChangedEvent, ICollectionContainer&, bool);` — Event for when the collection container's hidden state changes
- L379 _delegate_ `DECLARE_EVENT_TwoParams(ICollectionContainer, FCollectionCreatedEvent, ICollectionContainer&, const FCollectionNameType&);` — Event for when collections are created
- L383 _delegate_ `DECLARE_EVENT_TwoParams(ICollectionContainer, FCollectionDestroyedEvent, ICollectionContainer&, const FCollectionNameType&);` — Event for when collections are destroyed
- L387 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAssetsAddedToCollection, ICollectionContainer&, const FCollectionNameType&, TConstArrayView<FSoftObjectPath>);` — Event for when assets are added to a collection
- L391 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAssetsRemovedFromCollection, ICollectionContainer&, const FCollectionNameType&, TConstArrayView<FSoftObjectPath>);` — Event for when assets are removed from a collection
- L395 _delegate_ `DECLARE_EVENT_ThreeParams(ICollectionContainer, FCollectionRenamedEvent, ICollectionContainer&, const FCollectionNameType&, const FCollectionNameType&);` — Event for when collections are renamed
- L399 _delegate_ `DECLARE_EVENT_FourParams(ICollectionContainer, FCollectionReparentedEvent, ICollectionContainer&, const FCollectionNameType&, const TOptional<FCollectionNameType>&, const TOptional<FCollectionNameType>&);` — Event for when collections are re-parented (params: Collection, OldParent, NewParent)
- L403 _delegate_ `DECLARE_EVENT_TwoParams(ICollectionContainer, FCollectionUpdatedEvent, ICollectionContainer&, const FCollectionNameType&);` — Event for when collections is updated, or otherwise changed and we can't tell exactly how (eg, after updating from source control and merging)

### `Source/Developer/CollectionManager/Public/ICollectionManager.h` (Public)


#### class `ICollectionManager`  
`class ICollectionManager`  
_L12-508_
- L15 _public prototype_ `ICollectionManager() = default;`
- L16 _public prototype_ `ICollectionManager(const ICollectionManager&) = delete;`
- L17 _public prototype_ `virtual ~ICollectionManager() = default;`
- L19 _public prototype_ `ICollectionManager& operator=(const ICollectionManager&) = delete;`
- L22 _public prototype_ `virtual const TSharedRef<ICollectionContainer>& GetProjectCollectionContainer() const = 0;` — Returns the collection container for the current uproject
- L25 _public prototype_ `virtual TSharedPtr<ICollectionContainer> AddCollectionContainer(const TSharedRef<ICollectionSource>& CollectionSource) = 0;` — Creates and returns a new collection container for the specified collection source
- L28 _public prototype_ `virtual bool RemoveCollectionContainer(const TSharedRef<ICollectionContainer>& CollectionContainer) = 0;` — Removes the specified collection container
- L31 _public prototype_ `virtual bool HasCollectionContainer(const TSharedRef<ICollectionContainer>& CollectionContainer) const = 0;` — Returns true if this collection manager contains the specified collection container
- L34 _public prototype_ `virtual TSharedPtr<ICollectionContainer> FindCollectionContainer(FName CollectionSourceName) const = 0;` — Returns the collection container that matches the specified collection source name, if any
- L37 _public prototype_ `virtual TSharedPtr<ICollectionContainer> FindCollectionContainer(const TSharedRef<ICollectionSource>& CollectionSource) const = 0;` — Returns the collection container that matches the specified collection source, if any
- L40 _public prototype_ `virtual void GetCollectionContainers(TArray<TSharedPtr<ICollectionContainer>>& OutCollectionContainers) const = 0;` — Gets all collection containers
- L43 _public prototype_ `virtual void GetVisibleCollectionContainers(TArray<TSharedPtr<ICollectionContainer>>& OutCollectionContainers) const = 0;` — Gets all collection containers that aren't hidden
- L46 _public prototype_ `virtual bool TryParseCollectionPath(const FString& CollectionPath, TSharedPtr<ICollectionContainer>* OutCollectionContainer, FName* OutCollectionName, ECollectionShareType::Type* OutShareType) const = 0;` — Returns true if the collection path could be parsed into its constituent parts, and the collection container exists (if an out parameter for it was passed in)
- L50 _public prototype_ `virtual bool HasCollections() const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->HasCollections() to disambiguate which collection container to use.")` — Returns whether or not the collection manager contains any collections
- L54 _public prototype_ `virtual void GetCollections(TArray<FCollectionNameType>& OutCollections) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetCollections(...) to disambiguate which collection container to use.")` — Returns the list of collections
- L58 _public prototype_ `virtual void GetCollections(FName CollectionName, TArray<FCollectionNameType>& OutCollections) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetCollections(...) to disambiguate which collection container to use.")` — Returns the list of collections with the given name
- L62 _public prototype_ `virtual void GetCollectionNames(ECollectionShareType::Type ShareType, TArray<FName>& CollectionNames) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetCollectionNames(...) to disambiguate which collection container to use.")` — Returns the list of collection names of the specified share type
- L66 _public prototype_ `virtual void GetRootCollections(TArray<FCollectionNameType>& OutCollections) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetRootCollections(...) to disambiguate which collection container to use.")` — Returns the list of root-level collections
- L70 _public prototype_ `virtual void GetRootCollectionNames(ECollectionShareType::Type ShareType, TArray<FName>& CollectionNames) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetRootCollectionNames(...) to disambiguate which collection container to use.")` — Returns the list of root-level collection names of the specified share type
- L74 _public prototype_ `virtual void GetChildCollections(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FCollectionNameType>& OutCollections) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetChildCollections(...) to disambiguate which collection container to use.")` — Returns the list of child collections of the given collection
- L78 _public prototype_ `virtual void GetChildCollectionNames(FName CollectionName, ECollectionShareType::Type ShareType, ECollectionShareType::Type ChildShareType, TArray<FName>& CollectionNames) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetChildCollectionNames(...) to disambiguate which collection container to use.")` — Returns the list of child collections of the given collection that are also of the specified share type
- L82 _public prototype_ `virtual TOptional<FCollectionNameType> GetParentCollection(FName CollectionName, ECollectionShareType::Type ShareType) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetParentCollection(...) to disambiguate which collection container to use.")` — Returns the parent collection of the given collection, or an unset value if there is no parent set
- L86 _public prototype_ `virtual bool CollectionExists(FName CollectionName, ECollectionShareType::Type ShareType) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->CollectionExists(...) to disambiguate which collection container to use.")` — Returns true if the collection exists
- L94 _public prototype_ `virtual bool GetAssetsInCollection(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FSoftObjectPath>& OutAssetPaths, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetAssetsInCollection(...) to disambiguate which collection container to use.")` — Gets a list of assets in the given collection @return true if any objects were found
- L102 _public prototype_ `virtual bool GetClassesInCollection(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FTopLevelAssetPath>& ClassPaths, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetClassesInCollection(...) to disambiguate which collection container to use.")` — Gets a list of class paths in the given collection @return true if any objects were found
- L110 _public prototype_ `virtual bool GetObjectsInCollection(FName CollectionName, ECollectionShareType::Type ShareType, TArray<FSoftObjectPath>& ObjectPaths, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetObjectsInCollection(...) to disambiguate which collection container to use.")` — Gets a list of objects in the given collection @return true if any objects were found
- L114 _public prototype_ `virtual void GetCollectionsContainingObject(const FSoftObjectPath& ObjectPath, ECollectionShareType::Type ShareType, TArray<FName>& OutCollectionNames, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetCollectionsContainingObject(...) to disambiguate which collection container to use.")` — Returns a list of collections in which the specified object exists of the specified share type
- L118 _public prototype_ `virtual void GetCollectionsContainingObject(const FSoftObjectPath& ObjectPath, TArray<FCollectionNameType>& OutCollections, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetCollectionsContainingObject(...) to disambiguate which collection container to use.")` — Returns a list of collections in which the specified object exists
- L122 _public prototype_ `virtual void GetCollectionsContainingObjects(const TArray<FSoftObjectPath>& ObjectPaths, TMap<FCollectionNameType, TArray<FSoftObjectPath>>& OutCollectionsAndMatchedObjects, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetCollectionsContainingObjects(...) to disambiguate which collection container to use.")` — Returns a list of collections in which any of the specified objects exist
- L126 _public prototype_ `virtual FString GetCollectionsStringForObject(const FSoftObjectPath& ObjectPath, ECollectionShareType::Type ShareType, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self, bool bFullPaths = true) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetCollectionsStringForObject(...) to disambiguate which collection container to use.")` — Returns a string containing a comma separated list of collections in which the specified object exists of the specified share type
- L134 _public prototype_ `virtual void CreateUniqueCollectionName(FName BaseName, ECollectionShareType::Type ShareType, FName& OutCollectionName) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->CreateUniqueCollectionName(...) to disambiguate which collection container to use.")` — Creates a unique collection name for the given type taking the form BaseName+(unique number) @warning This function is threadsafe but it does not secure the name from another thread creating the collection in between calls to the ICollectionManager API.
- L146 _public prototype_ `virtual bool IsValidCollectionName( const FString& CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->IsValidCollectionName(...) to disambiguate which collection container to use.")` — Check whether the given name is valid for a new collection. @param CollectionName Potential collection name @param ShareType Type of collection to check for conflicts against. CST_All checks against all collcetion types. @param OutError Optional human readable explanation of why the operation failed @return true If a collection can be created with the name. @return false If the name contains invalid characters or conflicts with an existing collection of the same type.
- L159 _public prototype_ `virtual bool CreateCollection( FName CollectionName, ECollectionShareType::Type ShareType, ECollectionStorageMode::Type StorageMode, FText* OutError = nullptr) = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->CreateCollection(...) to disambiguate which collection container to use.")` — Creates a new collection. A .collection file will be added to disk. @param CollectionName The name of the new collection @param ShareType The way the collection is shared. @param StorageMode How does this collection store its objects? (static or dynamic) @param OutError Optional human readable explanation of why the operation failed @return true if the add was successful.
- L174 _public prototype_ `virtual bool RenameCollection( FName CurrentCollectionName, ECollectionShareType::Type CurrentShareType, FName NewCollectionName, ECollectionShareType::Type NewShareType, FText* OutError = nullptr) = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->RenameCollection(...) to disambiguate which collection container to use.")` — Renames a collection. A .collection file will be added to disk and a .collection file will be removed. @param CurrentCollectionName The current name of the collection. @param CurrentShareType The current way the collection is shared. @param NewCollectionName The new name of the collection. @param NewShareType The new way the collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the rename was successful.
- L190 _public prototype_ `virtual bool ReparentCollection( FName CollectionName, ECollectionShareType::Type ShareType, FName ParentCollectionName, ECollectionShareType::Type ParentShareType, FText* OutError = nullptr) = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->ReparentCollection(...) to disambiguate which collection container to use.")` — Re-parents a collection. The parent collection may be re-saved if it's too old to have a stable GUID. @param CollectionName The name of the collection to set the parent of. @param ShareType The way the collection is shared. @param ParentCollectionName The new parent of the collection, or None to have the collection become a root collection. @param ParentShareType The way the new parent collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the re-parent was successful.
- L203 _public prototype_ `virtual bool DestroyCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->DestroyCollection(...) to disambiguate which collection container to use.")` — Removes a collection to the asset registry. A .collection file will be deleted from disk. @param CollectionName The name of the collection to remove. @param ShareType The way the collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the remove was successful
- L216 _public prototype_ `virtual bool AddToCollection( FName CollectionName, ECollectionShareType::Type ShareType, const FSoftObjectPath& ObjectPath, FText* OutError = nullptr) = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->AddToCollection(...) to disambiguate which collection container to use.")` — Adds an asset to the specified collection. @param CollectionName The collection in which to add the asset @param ShareType The way the collection is shared. @param ObjectPath the ObjectPath of the asset to add. @param OutNumAdded if non-NULL, the number of objects successfully added to the collection @param OutError Optional human readable explanation of why the operation failed @return true if the add was successful.
- L220 _public prototype_ `virtual bool AddToCollection( FName CollectionName, ECollectionShareType::Type ShareType, TConstArrayView<FSoftObjectPath> ObjectPaths, int32* OutNumAdded = nullptr, FText* OutError = nullptr) = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->AddToCollection(...) to disambiguate which collection container to use.")`
- L235 _public prototype_ `virtual bool RemoveFromCollection( FName CollectionName, ECollectionShareType::Type ShareType, const FSoftObjectPath& ObjectPath, FText* OutError = nullptr) = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->RemoveFromCollection(...) to disambiguate which collection container to use.")` — Removes the asset from the specified collection. @param CollectionName The collection from which to remove the asset @param ShareType The way the collection is shared. @param ObjectPath the ObjectPath of the asset to remove. @param OutNumRemoved if non-NULL, the number of objects successfully removed from the collection @param OutError Optional human readable explanation of why the operation failed @return true if the remove was successful.
- L239 _public prototype_ `virtual bool RemoveFromCollection( FName CollectionName, ECollectionShareType::Type ShareType, TConstArrayView<FSoftObjectPath> ObjectPaths, int32* OutNumRemoved = nullptr, FText* OutError = nullptr) = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->RemoveFromCollection(...) to disambiguate which collection container to use.")`
- L253 _public prototype_ `virtual bool SetDynamicQueryText( FName CollectionName, ECollectionShareType::Type ShareType, const FString& InQueryText, FText* OutError = nullptr) = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->SetDynamicQueryText(...) to disambiguate which collection container to use.")` — Sets the dynamic query text for the specified collection. @param CollectionName The collection to set the query on. @param ShareType The way the collection is shared. @param InQueryText The new query to set. @param OutError Optional human readable explanation of why the operation failed @return true if the set was successful.
- L267 _public prototype_ `virtual bool GetDynamicQueryText( FName CollectionName, ECollectionShareType::Type ShareType, FString& OutQueryText, FText* OutError = nullptr) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetDynamicQueryText(...) to disambiguate which collection container to use.")` — Gets the dynamic query text for the specified collection. @param CollectionName The collection to get the query from. @param ShareType The way the collection is shared. @param OutQueryText Filled with the query text. @param OutError Optional human readable explanation of why the operation failed @return true if the get was successful.
- L282 _public prototype_ `virtual bool TestDynamicQuery( FName CollectionName, ECollectionShareType::Type ShareType, const ITextFilterExpressionContext& InContext, bool& OutResult, FText* OutError = nullptr) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->TestDynamicQuery(...) to disambiguate which collection container to use.")` — Tests the dynamic query for the specified collection against the context provided. @param CollectionName The collection to get the query from. @param ShareType The way the collection is shared. @param InContext The context to test against. @param OutResult Filled with the result of the query. @param OutError Optional human readable explanation of why the operation failed @return true if the get was successful.
- L295 _public prototype_ `virtual bool EmptyCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->EmptyCollection(...) to disambiguate which collection container to use.")` — Removes all assets from the specified collection. @param CollectionName The collection to empty @param ShareType The way the collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the clear was successful.
- L311 _public prototype_ `virtual bool SaveCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->SaveCollection(...) to disambiguate which collection container to use.")` — Save the collection (if dirty) and check it into source control (if under SCC control) Note: Generally you won't need to save collections manually as the collection manager takes care of that as objects and added/removed, etc. however, you may want to manually save a collection if a previous save attempt failed (and you've since corrected the issue), or if the collection contains redirected object references that you'd like to save to disk. @param CollectionName The collection to save @param ShareType The way the collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the save was successful.
- L326 _public prototype_ `virtual bool UpdateCollection(FName CollectionName, ECollectionShareType::Type ShareType, FText* OutError = nullptr) = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->UpdateCollection(...) to disambiguate which collection container to use.")` — Update the collection to make sure it's using the latest version from source control (if under SCC control) Note: Generally you won't need to update collections manually as the collection manager takes care of that as collections are saved to disk. @param CollectionName The collection to update @param ShareType The way the collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the update was successful.
- L338 _public prototype_ `virtual bool GetCollectionStatusInfo( FName CollectionName, ECollectionShareType::Type ShareType, FCollectionStatusInfo& OutStatusInfo, FText* OutError = nullptr) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetCollectionStatusInfo(...) to disambiguate which collection container to use.")` — Gets the status info for the specified collection @param CollectionName The collection to get the status info for @param ShareType The way the collection is shared. @param OutStatusInfo The status info to populate. @param OutError Optional human readable explanation of why the operation failed @return true if the status info was filled in.
- L349 _public prototype_ `virtual bool HasCollectionColors(TArray<FLinearColor>* OutColors = nullptr) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->HasCollectionColors(...) to disambiguate which collection container to use.")` — Checks whether any collections have a custom color set, optionally retrieving the list of in-use colors @param OutColors The optional color array to populate. @return true if there are any custom colors in use, false otherwise.
- L361 _public prototype_ `virtual bool GetCollectionColor( FName CollectionName, ECollectionShareType::Type ShareType, TOptional<FLinearColor>& OutColor, FText* OutError = nullptr) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetCollectionColor(...) to disambiguate which collection container to use.")` — Gets the optional color for the specified collection @param CollectionName The collection to get the color for @param ShareType The way the collection is shared. @param OutColor The optional color to populate. @param OutError Optional human readable explanation of why the operation failed @return true if the collection was found, and the color was optionally filled in.
- L375 _public prototype_ `virtual bool SetCollectionColor( FName CollectionName, ECollectionShareType::Type ShareType, const TOptional<FLinearColor>& NewColor, FText* OutError = nullptr) = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->SetCollectionColor(...) to disambiguate which collection container to use.")` — Sets the optional color for the specified collection @param CollectionName The collection to set the color for @param ShareType The way the collection is shared. @param NewColor The optional color to set. @param OutError Optional human readable explanation of why the operation failed @return true if the collection was found, and the color was set.
- L389 _public prototype_ `virtual bool GetCollectionStorageMode( FName CollectionName, ECollectionShareType::Type ShareType, ECollectionStorageMode::Type& OutStorageMode, FText* OutError = nullptr) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->GetCollectionStorageMode(...) to disambiguate which collection container to use.")` — Gets the method by which the specified collection stores its objects (static or dynamic) @param CollectionName The collection to get the storage mode for @param ShareType The way the collection is shared. @param OutStorageMode The variable to populate. @param OutError Optional human readable explanation of why the operation failed @return true if the status info was filled in.
- L403 _public prototype_ `virtual bool IsObjectInCollection( const FSoftObjectPath& ObjectPath, FName CollectionName, ECollectionShareType::Type ShareType, ECollectionRecursionFlags::Flags RecursionMode = ECollectionRecursionFlags::Self, FText* OutError = nullptr) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->IsObjectInCollection(...) to disambiguate which collection container to use.")` — Check to see if the given object exists in the given collection @param ObjectPath The object to test for its existence in the collection. @param CollectionName The collection to test. @param ShareType The way the collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the object is in the collection.
- L420 _public prototype_ `virtual bool IsValidParentCollection( FName CollectionName, ECollectionShareType::Type ShareType, FName ParentCollectionName, ECollectionShareType::Type ParentShareType, FText* OutError = nullptr) const = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->IsValidParentCollection(...) to disambiguate which collection container to use.")` — Check to see if the given collection is valid to be used as the parent of another collection. A collection may not be parented to itself, nor any of its current children. @param CollectionName The name of the collection to check the parent of. @param ShareType The way the collection is shared. @param ParentCollectionName The name of the parent collection to test against. @param ParentShareType The way the new parent collection is shared. @param OutError Optional human readable explanation of why the operation failed @return true if the parent is considered valid for this collection.
- L426 _public prototype_ `virtual FText GetLastError() const = 0;` — `UE_DEPRECATED(5.5, "Deprecated for thread safety reasons. Functions which populated this value now take an optional FText* out parameter.")` — Returns the most recent error.
- L432 _public prototype_ `virtual void HandleFixupRedirectors(ICollectionRedirectorFollower& InRedirectorFollower) = 0;` — Called to notify the collections that they should fix-up their object references so that they no longer contain any redirectors References are only updated in-memory, and won't be saved to disk until a redirector is deleted (which forces our hand), or the collection is saved for any other reason
- L438 _public prototype_ `virtual bool HandleRedirectorDeleted(const FSoftObjectPath& ObjectPath, FText* OutError = nullptr) = 0;` — Called to notify the collections that a redirector has been deleted and that they should ensure their on-disk representation is re-saved with the fixed up in-memory version @return true if all of the collections that were referencing this redirector could be re-saved, false otherwise
- L444 _public prototype_ `virtual bool HandleRedirectorsDeleted(TConstArrayView<FSoftObjectPath> ObjectPaths, FText* OutError = nullptr) = 0;` — Called to notify the collections that redirectors have been deleted and that they should ensure their on-disk representation is re-saved with the fixed up in-memory version @return true if all of the collections that were referencing these redirectors could be re-saved, false otherwise
- L447 _public prototype_ `virtual void HandleObjectRenamed(const FSoftObjectPath& OldObjectPath, const FSoftObjectPath& NewObjectPath) = 0;` — Called to notify the collections that an object has been renamed or moved
- L450 _public prototype_ `virtual void HandleObjectDeleted(const FSoftObjectPath& ObjectPath) = 0;` — Called to notify the collections that an object has been deleted
- L453 _public prototype_ `virtual void HandleObjectsDeleted(TConstArrayView<FSoftObjectPath> ObjectPaths) = 0;` — Called to notify the collections that objects have been deleted
- L456 _public prototype_ `DECLARE_EVENT_OneParam(ICollectionManager, FCollectionContainerCreatedEvent, const TSharedRef<ICollectionContainer>&);` — Event for when collection containers are created
- L457 _public prototype_ `virtual FCollectionContainerCreatedEvent& OnCollectionContainerCreated() = 0;`
- L460 _public prototype_ `DECLARE_EVENT_OneParam(ICollectionManager, FCollectionContainerDestroyedEvent, const TSharedRef<ICollectionContainer>&);` — Event for when collection containers are destroyed
- L461 _public prototype_ `virtual FCollectionContainerDestroyedEvent& OnCollectionContainerDestroyed() = 0;`
- L464 _public prototype_ `DECLARE_EVENT_OneParam( ICollectionManager, FCollectionCreatedEvent, const FCollectionNameType& );` — Event for when collections are created
- L466 _public prototype_ `virtual FCollectionCreatedEvent& OnCollectionCreated() = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->OnCollectionCreated() to disambiguate which collection container to use.")`
- L469 _public prototype_ `DECLARE_EVENT_OneParam( ICollectionManager, FCollectionDestroyedEvent, const FCollectionNameType& );` — Event for when collections are destroyed
- L471 _public prototype_ `virtual FCollectionDestroyedEvent& OnCollectionDestroyed() = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->OnCollectionDestroyed() to disambiguate which collection container to use.")`
- L474 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAssetsAddedToCollection, const FCollectionNameType&, TConstArrayView<FSoftObjectPath> );` — Event for when assets are added to a collection
- L476 _public prototype_ `virtual FOnAssetsAddedToCollection& OnAssetsAddedToCollection() = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->OnAssetsAddedToCollection() to disambiguate which collection container to use.")`
- L479 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams( FOnAssetsRemovedFromCollection, const FCollectionNameType&, TConstArrayView<FSoftObjectPath> );` — Event for when assets are removed from a collection
- L481 _public prototype_ `virtual FOnAssetsRemovedFromCollection& OnAssetsRemovedFromCollection() = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->OnAssetsRemovedFromCollection() to disambiguate which collection container to use.")`
- L484 _public prototype_ `DECLARE_EVENT_TwoParams( ICollectionManager, FCollectionRenamedEvent, const FCollectionNameType&, const FCollectionNameType& );` — Event for when collections are renamed
- L486 _public prototype_ `virtual FCollectionRenamedEvent& OnCollectionRenamed() = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->OnCollectionRenamed() to disambiguate which collection container to use.")`
- L489 _public prototype_ `DECLARE_EVENT_ThreeParams( ICollectionManager, FCollectionReparentedEvent, const FCollectionNameType&, const TOptional<FCollectionNameType>&, const TOptional<FCollectionNameType>& );` — Event for when collections are re-parented (params: Collection, OldParent, NewParent)
- L491 _public prototype_ `virtual FCollectionReparentedEvent& OnCollectionReparented() = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->OnCollectionReparented() to disambiguate which collection container to use.")`
- L494 _public prototype_ `DECLARE_EVENT_OneParam( ICollectionManager, FCollectionUpdatedEvent, const FCollectionNameType& );` — Event for when collections is updated, or otherwise changed and we can't tell exactly how (eg, after updating from source control and merging)
- L496 _public prototype_ `virtual FCollectionUpdatedEvent& OnCollectionUpdated() = 0;` — `UE_DEPRECATED(5.6, "ICollectionContainer has been introduced as a new top level object for housing collections, substitute wtih GetProjectCollectionContainer()->OnCollectionUpdated() to disambiguate which collection container to use.")`
- L502 _public prototype_ `DECLARE_EVENT_TwoParams( ICollectionManager, FAddToCollectionCheckinDescriptionEvent, const FName& , TArray<FText>& );` — When a collection checkin happens, use this event to add additional text to the changelist description. Delegates bound to this event must be safe to call on any thread.
- L503 _public prototype_ `virtual FAddToCollectionCheckinDescriptionEvent& OnAddToCollectionCheckinDescriptionEvent() = 0;`
- L506 _public prototype_ `UE_INTERNAL virtual void SuppressObjectDeletionHandling() = 0;` — Internal API for processing HandleObjectsDeleted calls in a batch-friendly way
- L507 _public prototype_ `UE_INTERNAL virtual void ResumeObjectDeletionHandling() = 0;`

#### Free symbols / members of external scopes

- L456 _delegate_ `DECLARE_EVENT_OneParam(ICollectionManager, FCollectionContainerCreatedEvent, const TSharedRef<ICollectionContainer>&);` — Event for when collection containers are created
- L460 _delegate_ `DECLARE_EVENT_OneParam(ICollectionManager, FCollectionContainerDestroyedEvent, const TSharedRef<ICollectionContainer>&);` — Event for when collection containers are destroyed
- L464 _delegate_ `DECLARE_EVENT_OneParam( ICollectionManager, FCollectionCreatedEvent, const FCollectionNameType& );` — Event for when collections are created
- L469 _delegate_ `DECLARE_EVENT_OneParam( ICollectionManager, FCollectionDestroyedEvent, const FCollectionNameType& );` — Event for when collections are destroyed
- L474 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAssetsAddedToCollection, const FCollectionNameType&, TConstArrayView<FSoftObjectPath> );` — Event for when assets are added to a collection
- L479 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams( FOnAssetsRemovedFromCollection, const FCollectionNameType&, TConstArrayView<FSoftObjectPath> );` — Event for when assets are removed from a collection
- L484 _delegate_ `DECLARE_EVENT_TwoParams( ICollectionManager, FCollectionRenamedEvent, const FCollectionNameType&, const FCollectionNameType& );` — Event for when collections are renamed
- L489 _delegate_ `DECLARE_EVENT_ThreeParams( ICollectionManager, FCollectionReparentedEvent, const FCollectionNameType&, const TOptional<FCollectionNameType>&, const TOptional<FCollectionNameType>& );` — Event for when collections are re-parented (params: Collection, OldParent, NewParent)
- L494 _delegate_ `DECLARE_EVENT_OneParam( ICollectionManager, FCollectionUpdatedEvent, const FCollectionNameType& );` — Event for when collections is updated, or otherwise changed and we can't tell exactly how (eg, after updating from source control and merging)
- L502 _delegate_ `DECLARE_EVENT_TwoParams( ICollectionManager, FAddToCollectionCheckinDescriptionEvent, const FName& , TArray<FText>& );` — When a collection checkin happens, use this event to add additional text to the changelist description. Delegates bound to this event must be safe to call on any thread.

### `Source/Developer/CollectionManager/Public/ICollectionSource.h` (Public)


#### class `ICollectionSource`  
`class ICollectionSource`  
_L8-34_
- L11 _public prototype_ `ICollectionSource() = default;`
- L12 _public prototype_ `ICollectionSource(const ICollectionSource&) = delete;`
- L13 _public prototype_ `virtual ~ICollectionSource() = default;`
- L15 _public prototype_ `ICollectionSource& operator=(const ICollectionSource&) = delete;`
- L18 _public prototype_ `virtual FName GetName() const = 0;` — Returns a name that identifies this collection source.
- L21 _public prototype_ `virtual FText GetTitle() const = 0;` — Returns a friendly name to display to the user for this collection source.
- L24 _public prototype_ `virtual const FString& GetCollectionFolder(const ECollectionShareType::Type InCollectionShareType) const = 0;` — Returns the folder path used to store the collections of a given share type.
- L27 _public prototype_ `virtual FString GetEditorPerProjectIni() const = 0;` — Returns the file path of the config file used to store settings related to this collection source.
- L30 _public prototype_ `virtual FString GetSourceControlStatusHintFilename() const = 0;` — Returns the file path to a file that can be used to check the source control status of collections in this collection source.
- L33 _public prototype_ `virtual TArray<FText> GetSourceControlCheckInDescription(FName CollectionName) const = 0;` — Returns lines to add to the description when checking in changes to a collection to source control.
