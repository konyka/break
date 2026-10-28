# Plugins / MetaHumanCharacterPalette

- module root: `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette`
- headers: 34; symbols: 755
- symbol kinds: class=26, delegate=13, enum=18, enumerator=56, externvar=7, function=30, macro=15, member=182, namespace=8, prototype=343, struct=46, typedef=11
- PrivateDependencyModuleNames: UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DeveloperSettings, Engine, MetaHumanSDKRuntime

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Private/MetaHumanCharacterPaletteLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCharacterPalette, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMetaHumanCharacterPalette, Log, All);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/EditorOnlyAssetReference.h` (Public)


#### struct `FEditorOnlyAssetReference`  
`struct FEditorOnlyAssetReference`  
_L34-108_
- reflection: `USTRUCT(BlueprintType)`
- desc: A reference to a UObject asset that can be used as an identifier in cooked builds without causing the referenced asset to be cooked as a dependency. In editor builds the reference uses a TSoftObjectPtr, so moving or renaming the referenced asset updates this property as it would any other soft pointer. The API is intentionally very similar to TSoftObjectPtr, so that it can be used as a drop-in replacement for it in many cases. This struct can even be used to replace an existing TSoftObjectPtr UPROPERTY. Existing saved data that wrote the property as a TSoftObjectPtr migrates automatically on load via SerializeFromMismatchedTag. No core redirect, rename, or deprecation is required, but note that the conversion only works from TSoftObjectPtr to FEditorOnlyAssetReference. Once the FEditorOnlyAssetReference is saved into the object, it can't be automatically converted back to TSoftObjectPtr if the code change is reverted.
- L39 _public prototype_ `FEditorOnlyAssetReference();`
- L40 _public prototype_ `explicit FEditorOnlyAssetReference(const TSoftObjectPtr<UObject>& InAsset);`
- L41 _public prototype_ `explicit FEditorOnlyAssetReference(const FSoftObjectPath& InPath);`
- L42 _public prototype_ `explicit FEditorOnlyAssetReference(const UObject* InObject);`
- L44 _public prototype_ `FEditorOnlyAssetReference& operator=(const TSoftObjectPtr<UObject>& InAsset);`
- L45 _public prototype_ `FEditorOnlyAssetReference& operator=(const FSoftObjectPath& InPath);`
- L46 _public prototype_ `FEditorOnlyAssetReference& operator=(const UObject* InObject);`
- L49 _public prototype_ `FSoftObjectPath ToSoftObjectPath() const;` — Returns the stored asset path. Available in all builds
- L53 _public prototype_ `TSoftObjectPtr<UObject> ToSoftObjectPtr() const;` — Returns the editor-only TSoftObjectPtr
- L57 _public prototype_ `bool IsNull() const;` — These functions operate on the reference as an identifier and can be used in any build
- L58 _public prototype_ `void Reset();`
- L59 _public prototype_ `FString ToString() const;`
- L60 _public prototype_ `FString GetAssetName() const;`
- L64 _public prototype_ `UObject* LoadSynchronous() const;` — These functions involve loading or fetching the referenced object and are therefore editor-only
- L65 _public prototype_ `bool IsValid() const;`
- L66 _public prototype_ `UObject* Get() const;`
- L69 _public prototype_ `bool Serialize(FArchive& Ar);`
- L70 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L97 _private member_ `TSoftObjectPtr<UObject> Asset;` — `UPROPERTY(EditAnywhere, Category = "Asset")` — Authoritative editor-only reference
- L107 _private member_ `FSoftObjectPath AssetIdentifier;` — `UPROPERTY(meta=(Untracked))` — Runtime-available identifier. Refreshed from Asset inside Serialize() when saving. The Untracked metadata tells the Asset Registry to ignore this reference, so that it won't influence cooking.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FEditorOnlyAssetReference> : TStructOpsTypeTraitsBase2<FEditorOnlyAssetReference>`  
_L111-119_
- inherits: `TStructOpsTypeTraitsBase2<FEditorOnlyAssetReference>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L114-118_

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`
- L115 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon6b22b8590103`)
- L116 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon6b22b8590103`)
- L117 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon6b22b8590103`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/IMetaHumanValidationContext.h` (Public)


#### class `UMetaHumanValidationContext`  
`class UMetaHumanValidationContext : public UInterface`  
_L10-13_
- reflection: `UINTERFACE()`
- inherits: `UInterface`

#### class `IMetaHumanValidationContext`  
`class IMetaHumanValidationContext`  
_L18-31_
- desc: @brief Interface for a validation context to be used by pipelines to validate items
- L30 _public prototype_ `virtual bool ValidateWardrobeItem(const class UMetaHumanWardrobeItem* InWardrobeItem) = 0;` — @brief Validates a wardrobe item using the rules defined in the MetaHuman SDK @param InWardrobeItem The item to be validated @return true if the item is valid and false otherwise

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanCharacterActorInterface.h` (Public)


#### class `UMetaHumanCharacterActorInterface`  
`class UMetaHumanCharacterActorInterface : public UInterface`  
_L19-22_
- reflection: `UINTERFACE(BlueprintType)`
- inherits: `UInterface`
- desc: Interface for actors that can be initialized from a UMetaHumanInstance. An actor implementing this interface can be used as a preview actor in the Collection editor.

#### class `IMetaHumanCharacterActorInterface`  
`class IMetaHumanCharacterActorInterface`  
_L24-49_
- L40 _public prototype_ `void SetMetaHumanInstance(UMetaHumanInstance* MetaHumanInstance);` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, CallInEditor, Category = "MetaHuman|Character")` — Initializes the actor from the given MetaHuman Instance. This function is called when the Instance has changed, so implementers *must* re-assemble from the given Instance when this is called, even if this Instance was already set on the actor. The easiest way to do this is to call GetAssemblyOutput, which will trigger re-assembly only if needed.
- L44 _public prototype_ `void SetCharacterInstance(UMetaHumanInstance* CharacterInstance);` — `UE_DEPRECATED(5.8, "This function has been renamed. Use SetMetaHumanInstance instead")` — `UFUNCTION(BlueprintImplementableEvent, CallInEditor, meta=(DeprecatedFunction, DeprecationMessage="Use SetMetaHumanInstance instead"))`
- L48 _public prototype_ `UMetaHumanInstance* GetMetaHumanInstance() const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCallable, CallInEditor, Category = "MetaHuman|Character")` — Returns the MetaHuman Instance that this actor is currently using, even if it wasn't set by SetMetaHumanInstance

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanCharacterEditorPipeline.h` (Public)


#### enum `EMetaHumanBuildStatus`  
`enum class EMetaHumanBuildStatus : uint8`  
_L25-29_
- reflection: `UENUM()`
- L27 _public enumerator_ `Succeeded`
- L28 _public enumerator_ `Failed`

#### enum `EMetaHumanWardrobeItemCompatibility`  
`enum class EMetaHumanWardrobeItemCompatibility : uint8`  
_L32-42_
- reflection: `UENUM()`
- L35 _public enumerator_ `None` — The Wardrobe Item is not compatible with the slot
- L38 _public enumerator_ `Add` — The Wardrobe Item can be added directly to the slot
- L41 _public enumerator_ `Import` — The Wardrobe Item can be imported into the slot by calling TryImportWardrobeItem on the Collection Pipeline

#### enum `EMetaHumanPipelineDisplayCategory`  
`enum class EMetaHumanPipelineDisplayCategory : uint8`  
_L45-51_
- reflection: `UENUM()`
- L47 _public enumerator_ `Advanced`
- L48 _public enumerator_ `Targets`
- L49 _public enumerator_ `Textures`
- L50 _public enumerator_ `Materials`

#### class `UMetaHumanCharacterEditorPipeline`  
`class UMetaHumanCharacterEditorPipeline : public UObject`  
_L57-95_
- reflection: `UCLASS(Abstract, MinimalAPI, NotBlueprintable, EditInlineNew)`
- inherits: `UObject`
- desc: The editor-only component of a UMetaHumanCharacterPipeline.
- L64 _public member_ `inline static const FName PipelineDisplay = TEXT("Pip` — Metadata tag for properties that should be displayed in the pipeline tool
- L67 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnUnpackComplete, EMetaHumanBuildStatus );`
- L69 _public typedef_ `using FTryUnpackObjectDelegate = TDelegate<bool(TNotNull<UObject*> , FString& )>;`
- L72 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterPipeline*> GetRuntimeCharacterPipeline() const PURE_VIRTUAL(UMetaHumanCharacterEditorPipeline::GetRuntimeCharacterPipeline, return NewObject<UMetaHumanCharacterPipeline>(););` — Get the corresponding runtime pipeline
- L76 _public prototype_ `bool IsPrincipalAssetClassCompatibleWithSlot(FName SlotName, TNotNull<const UClass*> AssetClass) const;` — Returns true if an asset of the given class can be added to the given slot on a palette.
- L79 _public prototype_ `virtual EMetaHumanWardrobeItemCompatibility TestWardrobeItemCompatibilityWithSlot(FName SlotName, TNotNull<const UMetaHumanWardrobeItem*> WardrobeItem) const;` — Tests whether the given Wardrobe Item is compatible with the given slot on a palette.
- L82 _public prototype_ `bool IsWardrobeItemCompatibleWithSlot(FName SlotName, TNotNull<const UMetaHumanWardrobeItem*> WardrobeItem) const;` — `UE_DEPRECATED(5.8, "Use TestWardrobeItemCompatibilityWithSlot instead")`
- L84 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterEditorPipelineSpecification*> GetSpecification() const PURE_VIRTUAL(UMetaHumanCharacterEditorPipeline::GetSpecification, return NewObject<UMetaHumanCharacterEditorPipelineSpecification>(););`
- L92 _public function_ `virtual void SetValidationContext(TScriptInterface<class IMetaHumanValidationContext> InValidationContext)` — @brief Sets the validation context to be used when validating items during assembly. Can be set to nullptr The validation context is ignored unless a pipeline chooses to use it

#### Free symbols / members of external scopes

- L67 _delegate_ `DECLARE_DELEGATE_OneParam(FOnUnpackComplete, EMetaHumanBuildStatus );`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanCharacterEditorPipelineSpecification.h` (Public)


#### struct `FMetaHumanCharacterPipelineSlotEditorData`  
`struct FMetaHumanCharacterPipelineSlotEditorData`  
_L17-46_
- reflection: `USTRUCT()`
- L22 _public prototype_ `bool SupportsAsset(const FAssetData& Asset) const;` — Returns true if the given asset is accepted by this slot
- L25 _public prototype_ `bool SupportsAssetType(TNotNull<const UClass*> AssetType) const;` — Returns true if the given asset class is supported by the slot
- L29 _public member_ `TObjectPtr<UScriptStruct> BuildInputStruct;` — `UPROPERTY()` — The type of the expected Build Input struct for this slot
- L36 _public member_ `TObjectPtr<UScriptStruct> ItemEditorPropertiesStruct;` — `UPROPERTY()` — The type of the PipelineEditorProperties struct stored on FMetaHumanCharacterPaletteItem for items in this slot.
- L45 _public member_ `TArray<TSoftClassPtr<UObject>> SupportedPrincipalAssetTypes;` — `UPROPERTY()` — The asset types accepted by this slot. If the runtime slot is a virtual slot, SupportedPrincipalAssetTypes on this slot must be a subset of the target slot's SupportedPrincipalAssetTypes.

#### class `UMetaHumanCharacterEditorPipelineSpecification`  
`class UMetaHumanCharacterEditorPipelineSpecification : public UObject`  
_L50-82_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L59 _public prototype_ `bool IsValid(TNotNull<const UMetaHumanCharacterPipelineSpecification*> RuntimeSpec) const;` — Returns true if the editor specification is internally consistent and consistent with the given runtime specification.
- L68 _public member_ `TObjectPtr<UScriptStruct> BuildInputStruct;` — `UPROPERTY()` — The type of the expected Build Input struct for this palette. This is on the editor specification, rather than the runtime specification, so that it can reference editor-only types.
- L81 _public member_ `TMap<FName, FMetaHumanCharacterPipelineSlotEditorData> SlotEditorData;` — `UPROPERTY()` — Editor-only data for slots defined in the runtime pipeline spec. Slots in the runtime pipeline spec, i.e. UMetaHumanCharacterPipelineSpecification, may or may not have editor-only data here. The runtime pipeline spec is the source of truth for what slots exist on the pipeline. SlotEditorData is not guaranteed to contain all slots, so when iterating slots, for example, use the runtime pipeline spec instead and use SlotEditorData only as a lookup.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanCharacterInstance.h` (Public)
_(no declarations extracted)_

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanCharacterPalette.h` (Public)


#### struct `FMetaHumanPaletteBuiltData`  
`struct FMetaHumanPaletteBuiltData`  
_L24-64_
- reflection: `USTRUCT()`
- desc: The output of the build for an entire palette, include its items and items' items, etc.
- L30 _public prototype_ `bool HasBuildOutputForItem(const FMetaHumanPaletteItemPath& ItemPath) const;` — Returns true if there is any build output for this specific item
- L38 _public prototype_ `bool ContainsOnlyValidBuildOutputForItem(const FMetaHumanPaletteItemPath& ItemPath) const;` — Returns true if this struct contains *only* the build output for the given item and its sub-items. This is used to validate the output of item pipelines.
- L47 _public prototype_ `void IntegrateItemBuiltData(const FMetaHumanPaletteItemPath& SourceItemPath, FName SourceItemSlotName, FMetaHumanPaletteBuiltData&& SourceItemBuiltData);` — Move the build output from an item into this struct. Call ContainsOnlyValidBuildOutputForItem on the source data first, to ensure it's valid. Passing invalid source data into this function will cause an assertion to fail.
- L63 _public member_ `FMetaHumanPipelineBuiltDataCollection ItemBuiltData;` — `UPROPERTY()` — The built data for each item in the palette, including items nested within other items. The key is the path to the item *from the owning Collection*. In other words, it's the absolute path to the item, rather than the relative path from this palette. The output for the Collection itself is stored with the empty item path as the key. SlotName will be ignored for this entry. In future, we will improve the encapsulation of item built data by making this private and only allowing an item's pipeline to access data belonging to that item.

#### struct `FMetaHumanPaletteBuildCacheEntry`  
`struct FMetaHumanPaletteBuildCacheEntry`  
_L67-71_
- desc: Caches data that is expensive to rebuild
- L70 _public member_ `FInstancedStruct CachedData;` — `UE_DEPRECATED(5.8, "FMetaHumanPaletteBuildCacheEntry is unused and will be removed")`

#### class `UMetaHumanCharacterPalette`  
`class UMetaHumanCharacterPalette : public UObject`  
_L77-231_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: Base class for objects that can contain items targeting a Character Pipeline.
- L85 _public prototype_ `[[nodiscard]] bool TryAddItemFromPrincipalAsset(FName SlotName, const FSoftObjectPath& PrincipalAsset, FMetaHumanPaletteItemKey& OutNewItemKey);` — Creates a new internal Wardrobe Item for a principal asset and adds it to the palette.
- L94 _public prototype_ `[[nodiscard]] bool TryAddItemFromWardrobeItem(FName SlotName, UMetaHumanWardrobeItem* WardrobeItem, FMetaHumanPaletteItemKey& OutNewItemKey);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Wardrobe")` — Adds a Wardrobe Item to the palette. The Wardrobe Item must be a self-contained asset, rather than an internal Wardrobe Item from another palette.
- L105 _public prototype_ `[[nodiscard]] bool TryAddItem(const FMetaHumanCharacterPaletteItem& NewItem);` — Adds an item to this palette, if there's no existing item with the same key. Prefer to call TryAddItemFromPrincipalAsset or TryAddItemFromWardrobeItem if possible, as those handle setting up the item correctly for you. This function is guaranteed to succeed if the item's Variation is set from a call to GenerateUniqueVariationName.
- L111 _public prototype_ `[[nodiscard]] virtual bool TryRemoveItem(const FMetaHumanPaletteItemKey& ExistingKey);` — Removes a single item from the palette for the given key. Returns boolean indicating success or failure of the operation.
- L118 _public prototype_ `[[nodiscard]] bool TryUpdateItemNonBuildProperties(const FMetaHumanPaletteItemKey& Key, const FMetaHumanCharacterPaletteItem& Source);` — Update fields on the item that don't contribute to the palette build. Doesn't invalidate the build.
- L133 _public prototype_ `[[nodiscard]] bool TryReplaceItem(const FMetaHumanPaletteItemKey& ExistingKey, const FMetaHumanCharacterPaletteItem& NewItem);` — Replace an existing item with a new item. The new item is allowed to have a different item key. The list of items is ordered, and the new item will be put at the same index as the existing item it replaces. In other words, the existing item will be overwritten in place by the new one. If the new item's key conflicts with another item in the palette, this operation will fail. It's guaranteed to succeed if an item matching ExistingKey exists, and the new item's Variation is set from a call to GenerateUniqueVariationName.
- L140 _public prototype_ `int32 RemoveAllItemsForSlot(FName SlotName);` — Remove all items assigned to the given slot Returns the number of items that were removed.
- L148 _public prototype_ `FName GenerateUniqueVariationName(const FMetaHumanPaletteItemKey& SourceKey) const;` — If this palette already contains an item matching the SourceKey, generate a variation name that doesn't match any existing item. If there is no matching item, simply returns SourceKey's Variation.
- L150 _public prototype_ `virtual const UMetaHumanCharacterEditorPipeline* GetPaletteEditorPipeline() const PURE_VIRTUAL(UMetaHumanCharacterPalette::GetPaletteEditorPipeline, return nullptr;);`
- L155 _public prototype_ `bool ContainsItem(const FMetaHumanPaletteItemKey& Key) const;` — Returns true if an item with the given key exists in this palette
- L158 _public prototype_ `[[nodiscard]] bool TryFindItem(const FMetaHumanPaletteItemKey& Key, FMetaHumanCharacterPaletteItem& OutItem) const;` — Fetches the item with the given key, if it exists
- L161 _public prototype_ `[[nodiscard]] bool TryResolveItem(const FMetaHumanPaletteItemPath& ItemPath, const UMetaHumanCharacterPalette*& OutContainingPalette, FMetaHumanCharacterPaletteItem& OutItem) const;` — Try to find the item and its containing palette referenced by the given path.
- L168 _public prototype_ `[[nodiscard]] bool TryResolvePipeline(const FMetaHumanPaletteItemPath& ItemPath, const UMetaHumanCharacterPipeline*& OutPipeline) const;` — Try to find the pipeline corresponding to the given item path. Note that an empty item path refers to the Collection itself.
- L177 _public prototype_ `[[nodiscard]] bool TryResolveItemPipeline(const FMetaHumanPaletteItemPath& ItemPath, const UMetaHumanItemPipeline*& OutPipeline) const;` — Same as TryResolvePipeline, except that it can only resolve item pipelines, not the Collection's pipeline. This is convenient if you know the path corresponds to an item, because it saves you from having to cast the return value to UMetaHumanItemPipeline.
- L180 _public prototype_ `const TArray<FMetaHumanCharacterPaletteItem>& GetItems() const;` — Provides const access to the items array
- L182 _public prototype_ `virtual const UMetaHumanCharacterPipeline* GetPalettePipeline() const PURE_VIRTUAL(UMetaHumanCharacterPalette::GetPalettePipeline, return nullptr;);`
- L196 _protected prototype_ `void CopyContentsFromPalette(TNotNull<const UMetaHumanCharacterPalette*> Other);` — Copies the contents of the Other palette into this palette, discarding this palette's existing contents. Used for setting up a palette to match another palette as closely as possible. Should give a near-identical result to DuplicateObject on Other, except that it updates this object in place instead of creating a new object.
- L203 _protected prototype_ `virtual void OnItemsModified();` — Called when any of the palette's items are modified, e.g. when items are added or removed. This allows subclasses to rebuild any derived data.
- L213 _protected prototype_ `virtual bool TryImportWardrobeItem(FName SlotName, TNotNull<const UMetaHumanWardrobeItem*> SourceWardrobeItem, FMetaHumanPaletteItemKey& OutNewItemKey);` — Called by TryAddItemFromWardrobeItem when TestWardrobeItemCompatibilityWithSlot returns Import. Subclasses that support importing Wardrobe Items with alternative pipelines should override this to delegate to their Collection Editor Pipeline's TryCreateItemForImport. @return true if the item was imported and added to the palette
- L225 _protected member_ `TArray<FMetaHumanCharacterPaletteItem> Items;` — `UPROPERTY()` — The items contained in this palette. Each item must have a unique Item Key (returned by GetItemKey) within this palette. This list is ordered. Operations on the list must not arbitrarily reorder it, e.g. by use of RemoveSwap.
- L229 _private prototype_ `void AddItemFromKnownCompatibleWardrobeItem(FName SlotName, TNotNull<UMetaHumanWardrobeItem*> WardrobeItem, FMetaHumanPaletteItemKey& OutNewItemKey);`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanCharacterPaletteItem.h` (Public)


#### struct `FMetaHumanCharacterPaletteItem`  
`struct FMetaHumanCharacterPaletteItem`  
_L18-81_
- reflection: `USTRUCT()`
- L24 _public prototype_ `FMetaHumanPaletteItemKey GetItemKey() const;` — Return a key for this item that must be unique within its containing palette
- L32 _public prototype_ `FText GetOrGenerateDisplayName() const;` — Return a friendly name that can be displayed in the UI If DisplayName is set, this just returns DisplayName, otherwise it will use the other properties to generate a name.
- L41 _public prototype_ `UObject* LoadPrincipalAssetSynchronous() const;` — Convenience function for calling LoadSynchronous on the Wardrobe Item's principal asset. Editor only because principal assets are not guaranteed to be cooked, so we shouldn't rely on loading them outside the editor.
- L50 _public member_ `TObjectPtr<class UMetaHumanWardrobeItem> WardrobeItem;` — `UPROPERTY(VisibleAnywhere, Category = "Character", meta = (NoResetToDefault))` — The Wardrobe Item that this item represents. Note that this could be its own asset or a subobject of a MetaHuman Collection.
- L54 _public member_ `FName Variation;` — `UPROPERTY(EditAnywhere, Category = "Character")` — A name used to disambiguate items that have the same WardrobeItem
- L58 _public member_ `FName SlotName;` — `UPROPERTY(VisibleAnywhere, Category = "Character")` — The slot that this item targets
- L64 _public member_ `FText DisplayName;` — `UPROPERTY(EditAnywhere, Category = "Character")` — An optional display name to use in the editor UI
- L68 _public member_ `FInstancedStruct PipelineEditorProperties;` — `UPROPERTY(EditAnywhere, Category = "Character")` — Editor-only properties managed by the owning palette's pipeline
- L80 _public member_ `FInstancedStruct PipelineProperties;` — `UPROPERTY(EditAnywhere, Category = "Character")` — Properties managed by the owning palette's pipeline. This is useful when a Collection pipeline does significant work on an item that is not covered by the item's pipeline, and so the Collection needs a place for the user to set properties to configure this work.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanCharacterPaletteProjectSettings.h` (Public)


#### class `UMetaHumanCharacterPaletteProjectSettings`  
`class UMetaHumanCharacterPaletteProjectSettings : public UDeveloperSettings`  
_L13-42_
- reflection: `UCLASS(Config = MetaHumanCharacter, DefaultConfig)`
- inherits: `UDeveloperSettings`
- L18 _public prototype_ `UMetaHumanCharacterPaletteProjectSettings();`
- L21 _public function_ `virtual FName GetCategoryName() const override`
- L22 _public function_ `virtual FName GetSectionName() const override`
- L24 _public function_ `virtual FText GetSectionText() const override`
- L25 _public function_ `virtual FText GetSectionDescription() const override`
- L32 _public member_ `TSoftClassPtr<class UMetaHumanCollectionPipeline> DefaultCharacterPipelineClass;` — `UPROPERTY(Config, EditAnywhere, Category = "Build")` — The default MetaHuman Collection Pipeline that will be used by new MetaHuman Characters and Collections
- L36 _public member_ `TMap<EMetaHumanQualityLevel, TSoftClassPtr<class UMetaHumanCollectionPipeline>> DefaultCharacterLegacyPipelines;` — `UPROPERTY(Config, EditAnywhere, Category = "Build", EditFixedSize, NoClear)` — The default legacy MetaHuman Collection Pipelines that is used to build legacy Actor-based blueprints.
- L39 _public member_ `TMap<EMetaHumanQualityLevel, TSoftClassPtr<class UMetaHumanCollectionPipeline>> DefaultCharacterUEFNPipelines;` — `UPROPERTY(Config, EditAnywhere, Category = "Build", EditFixedSize, NoClear)`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanCharacterPipeline.h` (Public)


#### enum `EMetaHumanCharacterPaletteBuildQuality`  
`enum class EMetaHumanCharacterPaletteBuildQuality : uint8`  
_L36-42_
- reflection: `UENUM()`
- desc: The level of quality that the Palette content should be or was built for. In future, Pipelines may be able to define their own quality levels. For now, this is a fixed list.
- L39 _public enumerator_ `Production` — Full, shipping quality
- L41 _public enumerator_ `Preview` — Reduced quality for the purpose of quick preview while editing

#### struct `FMetaHumanInstanceParameterOutput`  
`struct FMetaHumanInstanceParameterOutput`  
_L54-72_
- reflection: `USTRUCT()`
- desc: Output produced during assembly to specify what Instance Parameters are available. The set of supported parameters may change from one assembly to the next due to a number of factors, so users must always refer to the Parameter Output from the latest assembly to see what parameters are available and the context that should be passed when setting them. See the Instance Parameter functions on UMetaHumanInstance for more info.
- L63 _public member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY()` — Each supported Instance Parameter should have a property set to the default value of the parameter in this property bag.
- L71 _public member_ `FInstancedStruct ParameterContext;` — `UPROPERTY()` — A context struct that has meaning only to the pipeline instance that produced it. Other code should not try to parse this struct.

#### struct `FMetaHumanAssemblyOutput`  
`struct FMetaHumanAssemblyOutput`  
_L78-125_
- reflection: `USTRUCT()`
- desc: The result of assembling an Instance using a Collection.
- L83 _public prototype_ `FMetaHumanAssemblyOutput() = default;`
- L84 _public prototype_ `FMetaHumanAssemblyOutput(const FMetaHumanAssemblyOutput& Other) = default;`
- L85 _public prototype_ `FMetaHumanAssemblyOutput(FMetaHumanAssemblyOutput&& Other) = default;`
- L86 _public prototype_ `FMetaHumanAssemblyOutput& operator=(const FMetaHumanAssemblyOutput& Other) = default;`
- L95 _public member_ `FInstancedStruct PipelineAssemblyOutput;` — `UPROPERTY()` — The main data produced by the pipeline. Its type should match AssemblyOutputStruct from the pipeline specification.
- L99 _public member_ `TArray<FMetaHumanGeneratedAssetMetadata> Metadata;` — `UPROPERTY()` — An array of every asset generated for this assembly
- L111 _public member_ `TMap<FMetaHumanPaletteItemPath, FMetaHumanInstanceParameterOutput> InstanceParameters;` — `UE_DEPRECATED(5.8, "There are now two types of Instance Parameters: Assembly Parameters and Post-Assembly Parameters. Only Post-Assembly Parameters are used in this context.")` — `UPROPERTY()` — The Instance Parameters that are available to set on this assembly and their default values. Items are not required to support Instance Parameters, so there may not be an entry for every assembled item. The Collection's own Instance Parameters are stored using the empty item path as the key.
- L124 _public member_ `FMetaHumanPostAssemblyParameterOutputCollection PostAssemblyParameters;` — `UPROPERTY()` — The Post-Assembly Parameters that are available to set on this assembly and their default values. Some items may not provide Post-Assembly Parameters, so there may not be an entry for every assembled item. The Collection's own Post-Assembly Parameters are stored using the empty item path as the key.

#### class `UMetaHumanCharacterPipeline`  
`class UMetaHumanCharacterPipeline : public UObject`  
_L138-193_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: A Pipeline contains the functionality for building a Palette and assembling Instances from it. Each Pipeline owns an Editor Pipeline that provides its editor-only functionality, such as building the Palette. The Pipeline itself is responsible for assembling Instances, so this can be done either in editor or in a cooked build.
- L144 _public typedef_ `using FOnAssemblyComplete = TDelegate<void(FMetaHumanAssemblyOutput&& )>;` — If the AssemblyOutput parameter is invalid, the evaluation failed
- L152 _public prototype_ `virtual void SetDefaultEditorPipeline() PURE_VIRTUAL(UMetaHumanCharacterPipeline::SetDefaultEditorPipeline,);` — Create an instance of this pipeline's corresponding Editor Pipeline class and use it as this pipeline's editor-only component, i.e. GetEditorPipeline should return this new instance.
- L172 _public prototype_ `virtual void SetInstanceParameters(const FInstancedStruct& ParameterContext, const FInstancedPropertyBag& Parameters) const;` — `UE_DEPRECATED(5.8, "There are now two types of Instance Parameters: Assembly Parameters and Post-Assembly Parameters. This function has been replaced with SetPostAssemblyParameters.")` — Apply the Instance Parameter values to the Assembly Output. The Parameters argument is guaranteed to have the same members as the struct returned in the FMetaHumanInstanceParameterOutput that was produced during assembly. ParameterContext will be the same struct returned in FMetaHumanInstanceParameterOutput. Implementations can assume that no member variables on this Pipeline instance have been modified since the assembly was done. If the parameter values are out of the expected range, implementations should try to handle this gracefully, e.g. by clamping to the allowed range. They may log warnings or errors about this, but should not assert or crash if at all possible.
- L179 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterPipelineSpecification*> GetSpecification() const PURE_VIRTUAL(UMetaHumanCharacterPipeline::GetSpecification, return NewObject<UMetaHumanCharacterPipelineSpecification>(););` — Returns the specification implemented by this pipeline. Should always returns a valid pointer.
- L185 _public prototype_ `static TArrayView<const FMetaHumanPinnedSlotSelection> FilterPinnedSlotSelectionsToItem( TArrayView<const FMetaHumanPinnedSlotSelection> SortedSlotSelections, const FMetaHumanPaletteItemPath& FilteredItem);` — Takes a sorted list of selections and returns a view of any selections that relate to the filtered item or its sub-items.
- L190 _public prototype_ `static TArrayView<const FMetaHumanPaletteItemPath> FilterItemPaths( TArrayView<const FMetaHumanPaletteItemPath> SortedItemPaths, const FMetaHumanPaletteItemPath& FilteredItem);` — Takes a sorted list of item paths and returns a view of any that include the filtered item.

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanCharacterPipelineSpecification.h` (Public)


#### enum `EMetaHumanAssemblyOutputMappingMethod`  
`enum class EMetaHumanAssemblyOutputMappingMethod : uint8`  
_L42-79_
- reflection: `UENUM()`
- desc: Determines the interpretation of FMetaHumanAssemblyOutputMapping. See FMetaHumanAssemblyOutputMapping for more details.
- L48 _public enumerator_ `Ignore` — No automatic processing. Pipelines can still override SetPostAssemblyParameters to handle this slot manually.
- L54 _public enumerator_ `DirectProperty` — The Item's Assembly Output is stored in a property on the Collection Assembly Output, or a property within a struct on the Collection Assembly Output.
- L63 _public enumerator_ `ArrayProperty` — The Item's Assembly Output is stored in an array on the Collection Assembly Output, or a property within a struct in an array on the Collection Assembly Output. The index into the array should be assigned to PipelineAssemblyOutputArrayIndex on the item's FMetaHumanPostAssemblyParameterOutput during assembly.
- L69 _public enumerator_ `CustomReference` — GetItemAssemblyOutputReference will be called on the pipeline to fetch a reference to the Item's Assembly Output on the Collection Assembly Output.
- L78 _public enumerator_ `CustomValue` — GetItemAssemblyOutputValue will be called on the pipeline to fetch the Item's Assembly Output by value. SetItemAssemblyOutputValue will be called to set the Item's Assembly Output after it has been modified.

#### struct `FMetaHumanAssemblyOutputMapping`  
`struct FMetaHumanAssemblyOutputMapping`  
_L93-115_
- reflection: `USTRUCT()`
- desc: Features such as Post-Assembly Parameters rely on retrieving an Item's Assembly Output from the Collection Assembly Output. In many cases, the Item's output is simply stored unmodified on the Collection's output and so the mapping is very simple. Occasionally the Item's output is stored in a different format on the Collection's output or transformed in some way and more custom handling is needed. This struct allows the mapping to be declared, so that simple cases can be handled automatically. This saves pipeline authors from having to write boilerplate code to map one property to another.
- L99 _public member_ `EMetaHumanAssemblyOutputMappingMethod Method = EMetaHumanAssemblyOutputMappingMethod::Ignore;` — `UPROPERTY()` — The method used to perform the mapping
- L103 _public member_ `FName PipelineOutputPropertyName;` — `UPROPERTY()` — The name of the property on the Collection Assembly Output
- L114 _public member_ `FName PipelineOutputInnerPropertyName;` — `UPROPERTY()` — The name of the property within the struct property specified by PipelineOutputPropertyName. For example, if an Item's Assembly Output is stored within a struct on the Collection Assembly Output, so that to access it you would have to write CollectionAssemblyOutput.SomeStruct.ItemAssemblyOutput, you would set PipelineOutputPropertyName to "SomeStruct" and this property to "ItemAssemblyOutput".

#### struct `FMetaHumanCharacterPipelineSlot`  
`struct FMetaHumanCharacterPipelineSlot`  
_L118-170_
- reflection: `USTRUCT()`
- L123 _public prototype_ `bool IsVirtual() const;`
- L130 _public member_ `TObjectPtr<UScriptStruct> ItemPropertiesStruct;` — `UPROPERTY()` — The type of the PipelineProperties struct stored on FMetaHumanCharacterPaletteItem for items in this slot.
- L133 _public member_ `TObjectPtr<UScriptStruct> BuildOutputStruct;` — `UPROPERTY()`
- L136 _public member_ `TObjectPtr<UScriptStruct> AssemblyInputStruct;` — `UPROPERTY()`
- L139 _public member_ `TObjectPtr<UScriptStruct> AssemblyOutputStruct;` — `UPROPERTY()`
- L143 _public member_ `FMetaHumanAssemblyOutputMapping AssemblyOutputMapping;` — `UPROPERTY()` — For virtual slots, this is ignored
- L150 _public member_ `FName TargetSlot;` — `UPROPERTY()` — If TargetSlot is a valid name, this slot is a virtual slot that forwards its selections to a target slot, which may be virtual or real.
- L154 _public member_ `bool bAllowsMultipleSelection = false;` — `UPROPERTY()` — If true, multiple items can be selected for this slot simultaneously
- L165 _public member_ `bool bVisibleToUser = true;` — `UPROPERTY()` — If true, this slot will be shown in UI such as the MetaHuman Instance editor. When you have multiple wearables that are processed in the same way by the pipeline, e.g. earrings and glasses, it's useful to have a single, hidden slot that can process an arbitrary number of them. You can then easily add virtual slots that target this hidden slot to allow more types of wearable, without modifying the pipeline.
- L169 _public member_ `FLinearColor SlotColor = FLinearColor::White;` — `UPROPERTY()` — Color used to identify this slot in the UI (e.g. colored band on tile thumbnails)

#### class `UMetaHumanCharacterPipelineSpecification`  
`class UMetaHumanCharacterPipelineSpecification : public UObject`  
_L178-208_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: This class represents the data interface of a UMetaHumanCharacterPipeline. It allows code to determine if two pipelines are compatible.
- L183 _public prototype_ `bool IsValid() const;`
- L190 _public prototype_ `TOptional<FName> ResolveRealSlotName(FName SlotName) const;` — Given a virtual or real slot name, returns the real slot that it resolves to. If the slot name is not found, the return value will be unset.
- L193 _public member_ `TObjectPtr<UScriptStruct> BuildOutputStruct;` — `UPROPERTY()`
- L196 _public member_ `TObjectPtr<UScriptStruct> AssemblyInputStruct;` — `UPROPERTY()`
- L199 _public member_ `TObjectPtr<UScriptStruct> AssemblyOutputStruct;` — `UPROPERTY()`
- L207 _public member_ `TMap<FName, FMetaHumanCharacterPipelineSlot> Slots;` — `UPROPERTY()` — The specification for each slot. The key is the slot name.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MetaHuman` (scope `UE`)
- L14 _namespace_ `namespace CharacterPipelineSlots` (scope `UE::MetaHuman`)
- L20 _externvar_ `extern const FName Character;` (scope `UE::MetaHuman::CharacterPipelineSlots`) — A pipeline that accepts MetaHuman Characters should have a slot for them with this name, to ensure compatibility with the MetaHuman Character editor.
- L28 _externvar_ `extern const FName Hair;` (scope `UE::MetaHuman::CharacterPipelineSlots`) — Suggested slot names to improve compatibility between pipelines. These names are not hard requirements, but using the same names for the same types of slot makes it easier to migrate content across pipelines.
- L29 _externvar_ `extern const FName Eyebrows;` (scope `UE::MetaHuman::CharacterPipelineSlots`)
- L30 _externvar_ `extern const FName Beard;` (scope `UE::MetaHuman::CharacterPipelineSlots`)
- L31 _externvar_ `extern const FName Mustache;` (scope `UE::MetaHuman::CharacterPipelineSlots`)
- L32 _externvar_ `extern const FName Eyelashes;` (scope `UE::MetaHuman::CharacterPipelineSlots`)
- L33 _externvar_ `extern const FName Peachfuzz;` (scope `UE::MetaHuman::CharacterPipelineSlots`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanCollection.h` (Public)


#### enum `EMetaHumanCharacterUnpackPathMode`  
`enum class EMetaHumanCharacterUnpackPathMode : uint8`  
_L17-33_
- reflection: `UENUM()`
- L26 _public enumerator_ `SubfolderNamedForPalette UMETA(Hidden)` — Assets will be unpacked to a subfolder of the Palette's current folder. The subfolder will have the same name as the Palette. For example, when a Palette called A is at path /Game/Palettes, its assets would be unpacked to the /Game/Palettes/A folder.
- L29 _public enumerator_ `Relative` — UnpackFolderPath is a relative path from the folder containing the Palette
- L32 _public enumerator_ `Absolute` — UnpackFolderPath is an absolute path

#### enum `EMetaHumanCharacterAssetsUnpackResult`  
`enum class EMetaHumanCharacterAssetsUnpackResult : uint8`  
_L36-40_
- reflection: `UENUM()`
- L38 _public enumerator_ `Succeeded`
- L39 _public enumerator_ `Failed`

#### struct `FMetaHumanCollectionBuiltData`  
`struct FMetaHumanCollectionBuiltData`  
_L47-60_
- reflection: `USTRUCT()`
- desc: The output of the Collection Pipeline's build step
- L53 _public prototype_ `bool IsValid() const;` — Returns true if this built data has been populated from a successful build
- L56 _public member_ `FMetaHumanPaletteBuiltData PaletteBuiltData;` — `UPROPERTY()`
- L59 _public member_ `TArray<FMetaHumanPinnedSlotSelection> SortedPinnedSlotSelections;` — `UPROPERTY()`

#### class `UMetaHumanCollection`  
`class UMetaHumanCollection : public UMetaHumanCharacterPalette`  
_L70-331_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMetaHumanCharacterPalette`
- desc: A collection of character parts (e.g. MetaHuman Characters, clothing, hairstyles) that target slots on a Character Pipeline. Create an Instance from a Collection to assemble a renderable character from the parts contained in the Collection.
- L76 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPaletteBuilt, EMetaHumanCharacterPaletteBuildQuality );` — `UE_DEPRECATED(5.8, "FOnPaletteBuilt has been replaced by FOnCollectionBuilt")`
- L78 _public prototype_ `UMetaHumanCollection();`
- L82 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnCollectionBuilt);`
- L83 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPipelineChanged);`
- L84 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnBuildComplete, EMetaHumanBuildStatus );`
- L91 _public prototype_ `void SetQuality(EMetaHumanCharacterPaletteBuildQuality InQuality);` — Set the Quality that will be used when this Collection is built. Clears built data if changing to a different quality level.
- L94 _public prototype_ `void Build( const FInstancedStruct& BuildInput, const FOnBuildComplete& OnComplete, const TArray<FMetaHumanPinnedSlotSelection>& PinnedSlotSelections = TArray<FMetaHumanPinnedSlotSelection>(), const TArray<FMetaHumanPaletteItemPath>& ItemsToExclude = TArray<FMetaHumanPaletteItemPath>());` — Builds the collection so that Instances can assemble characters from it
- L101 _public prototype_ `void Build( const FInstancedStruct& BuildInput, EMetaHumanCharacterPaletteBuildQuality InQuality, ITargetPlatform* TargetPlatform, const FOnBuildComplete& OnComplete, const TArray<FMetaHumanPinnedSlotSelection>& PinnedSlotSelections = TArray<FMetaHumanPinnedSlotSelection>(), const TArray<FMetaHumanPaletteItemPath>& ItemsToExclude = TArray<FMetaHumanPaletteItemPath>());` — `UE_DEPRECATED(5.8, "Quality is now a property of the Collection. TargetPlatform is no longer used at build time. Use the new Build overload.")`
- L110 _public prototype_ `void ClearBuiltData();` — Clear any built data in this Collection, resetting it to an unbuilt state
- L113 _public prototype_ `void RefreshBuildCacheGuid();` — Regenerates the BuildCacheGuid, invalidating any cached build results for this Collection.
- L122 _public prototype_ `void UnpackAssets(const FOnMetaHumanCharacterAssetsUnpacked& OnComplete = FOnMetaHumanCharacterAssetsUnpacked());` — Moves any built assets stored within this Collection to their own asset packages, making them standalone assets that can be referenced from other objects. The Collection can still be used as normal after this, as it will still reference the unpacked assets as it did before they were unpacked.
- L129 _public prototype_ `void SetDefaultPipeline();` — Sets the default Pipeline from the project settings. Call this after constructing a Collection if you don't have a specific Pipeline to use.
- L139 _public prototype_ `void SetPipeline(UMetaHumanCollectionPipeline* InPipeline);` — Set the Pipeline for this Collection to use. It's not necessary to provide each Collection instance with a unique Pipeline instance, as the Pipeline is intended to be stateless. However, the Pipeline instance will be editable in Details panels wherever the Collection is visible for editing, and users editing a Pipeline's properties from there may be surprised if these edits affect other Collections.
- L144 _public prototype_ `void SetPipelineFromClass(TSubclassOf<UMetaHumanCollectionPipeline> InPipelineClass);` — Sets the Pipeline to be an instance of the given class
- L147 _public prototype_ `const UMetaHumanCollectionEditorPipeline* GetEditorPipeline() const;` — Convenience function to access the editor pipeline
- L149 _public prototype_ `virtual const UMetaHumanCharacterEditorPipeline* GetPaletteEditorPipeline() const override;`
- L151 _public prototype_ `[[nodiscard]] virtual bool TryRemoveItem(const FMetaHumanPaletteItemKey& ExistingKey) override;`
- L164 _public prototype_ `void CopyContentsFrom(TNotNull<const UMetaHumanCollection*> Other);` — Copies the contents of the Other Collection into this Collection, discarding this Collection's existing contents and leaving it in an unbuilt state. Used for copying edits from a temporary Collection back to the persistent Collection. Contents in this case refers to the Collection's items and its default MetaHuman Instance. Note that some properties, such as Quality, are considered settings rather than contents and are intentionally not copied.
- L171 _public prototype_ `UMetaHumanCollectionPipeline* GetMutablePipeline();` — The Pipeline targeted by this Collection. May be null if the user hasn't set a pipeline yet.
- L179 _public prototype_ `const UMetaHumanCollectionPipeline* GetPipeline() const;` — The Pipeline targeted by this Collection. May be null if the user hasn't set a pipeline yet.
- L181 _public prototype_ `virtual const UMetaHumanCharacterPipeline* GetPalettePipeline() const override;`
- L184 _public prototype_ `const FMetaHumanCollectionBuiltData& GetBuiltData() const;` — Note that the returned data is not guaranteed to be valid. Call IsValid on the result to check.
- L187 _public prototype_ `const FMetaHumanCollectionBuiltData& GetBuiltData(EMetaHumanCharacterPaletteBuildQuality InQuality) const;` — `UE_DEPRECATED(5.8, "Quality is now a property of the Collection. Use the GetBuiltData overload with no parameters.")`
- L190 _public prototype_ `EMetaHumanCharacterPaletteBuildQuality GetQuality() const;` — Note that in any cooked Collection, Quality will always be Production.
- L198 _public prototype_ `TNotNull<const UMetaHumanInstance*> GetDefaultInstance() const;` — The Collection contains a default instance that is used for preview. Guaranteed to be non-null.
- L200 _public prototype_ `TNotNull<UMetaHumanInstance*> GetMutableDefaultInstance();`
- L203 _public prototype_ `virtual void PostInitProperties() override;`
- L204 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L205 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L224 _public prototype_ `[[nodiscard]] TArray<FMetaHumanPipelineSlotSelectionData> PropagateVirtualSlotSelections(const TArray<FMetaHumanPipelineSlotSelectionData>& Selections) const;` — Resolves virtual slots in the given array of selections. For each selection in the array, if that selection targets a virtual slot, it will be updated to target the underlying real slot. Once this is done, code using the resulting array can just operate on real slots and doesn't have to handle virtual slots at all. This function assumes that PipelineSpec is valid (i.e. PipelineSpec->IsValid() returns true), otherwise it may assert or never return. Any selections that don't resolve to valid items in the Collection will be omitted from the returned array.
- L236 _public member_ `FOnPipelineChanged OnPipelineChanged;` — Delegate fired when a new Pipeline has been set on this Collection. This can only happen in editor. If any changes need to be made to the Collection in response to the Pipeline changing, such as removing items from slots that don't exist on the new Pipeline, those changes will be made before this delegate is fired.
- L239 _public member_ `FOnCollectionBuilt OnCollectionBuilt;` — Delegate fired when the Collection has finished building, if it succeeded
- L251 _public member_ `FGuid BuildCacheGuid;` — `UPROPERTY()` — A GUID used in DDC keys made during this Collection's build. In theory Collections should be safe to all use the same DDC keys, but if the cached data needs to be rebuilt for any reason, this setup allows a Collection to rebuild only its own cache by regenerating this GUID.
- L255 _public member_ `bool bAutoBuildForPreview = false;` — `UPROPERTY()` — If true, this Collection's preview counterpart will be built automatically whenever an edit is made to it in the Collection editor
- L259 _public member_ `bool bBuildAllItemsForPreview = false;` — `UPROPERTY()` — If false, only the currently selected items will be built for preview in the Collection editor. If true, all items will be built.
- L263 _public member_ `EMetaHumanCharacterUnpackPathMode UnpackPathMode = EMetaHumanCharacterUnpackPathMode::Relative;` — `UPROPERTY(EditAnywhere, Category = "Targets")` — The mode for determining which folder to unpack the Collection's assets to
- L267 _public member_ `FString UnpackFolderPath = TEXT("Unp` — `UPROPERTY(EditAnywhere, Category = "Targets", meta = (EditCondition = "UnpackPathMode != EMetaHumanCharacterUnpackPathMode::SubfolderNamedForPalette", EditConditionHides))` — The folder path that assets will be unpacked to. Interpreted according to UnpackPathMode.
- L270 _public prototype_ `FString GetUnpackFolder() const;` — Returns the folder path where the assets will be unpacked, depending on the UnpackPathMode
- L275 _public member_ `FOnPaletteBuilt OnPaletteBuilt;` — `UE_DEPRECATED(5.8, "OnPaletteBuilt has been replaced by OnCollectionBuilt")`
- L280 _protected prototype_ `virtual void OnItemsModified() override;`
- L281 _protected prototype_ `virtual bool TryImportWardrobeItem(FName SlotName, TNotNull<const UMetaHumanWardrobeItem*> SourceWardrobeItem, FMetaHumanPaletteItemKey& OutNewItemKey) override;`
- L294 _private prototype_ `TArray<UClass*> GetDisallowedPipelineClasses() const;` — `UFUNCTION()` — Returns the list of Collection Pipeline classes that should *not* be selectable in the Collection editor. This is used to exclude pipelines that are intended for use by MetaHuman Creator only.
- L299 _private member_ `TObjectPtr<UMetaHumanCollectionPipeline> Pipeline;` — `UPROPERTY(EditAnywhere, Instanced, Category = "Character", meta = (GetDisallowedClasses = "GetDisallowedPipelineClasses"))` — The MetaHuman Collection Pipeline used to build this collection
- L303 _private member_ `TObjectPtr<UMetaHumanInstance> DefaultInstance;` — `UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess))`
- L316 _private member_ `FMetaHumanCollectionBuiltData BuiltData;` — `UPROPERTY(DuplicateTransient)` — The data produced by the Collection Pipeline during the last successful call to Build.
- L326 _private member_ `EMetaHumanCharacterPaletteBuildQuality Quality = EMetaHumanCharacterPaletteBuildQuality::Production;` — `UPROPERTY()` — The build quality that will be used by this Collection. Note that Preview Collections are intended to be transient and shouldn't be saved into persistent storage. They will intentionally fail to cook, in order to help prevent accidental misuse.
- L330 _private member_ `bool bIsUnpacked;` — `UPROPERTY(DuplicateTransient)` — True if the assets in this Collection have been unpacked and are in their own packages.

#### Free symbols / members of external scopes

- L42 _delegate_ `DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterAssetsUnpacked, EMetaHumanCharacterAssetsUnpackResult );`
- L42 _prototype_ `DECLARE_DELEGATE_OneParam(FOnMetaHumanCharacterAssetsUnpacked, EMetaHumanCharacterAssetsUnpackResult );`
- L76 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPaletteBuilt, EMetaHumanCharacterPaletteBuildQuality );`
- L82 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnCollectionBuilt);`
- L83 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPipelineChanged);`
- L84 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBuildComplete, EMetaHumanBuildStatus );`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanCollectionBlueprintLibrary.h` (Public)


#### class `UMetaHumanPaletteKeyBlueprintLibrary`  
`class UMetaHumanPaletteKeyBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L30-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: @brief Exposes blueprint functions to operate on FMetaHumanPaletteItemKey. Functions are tagged with ScriptMethod so they can be called directly on the struct without the need to reference the library.
- L39 _public prototype_ `static bool ReferencesSameAsset(const FMetaHumanPaletteItemKey& InKey, const FMetaHumanPaletteItemKey& InOther);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Item", meta = (ScriptMethod))` — @brief Returns true if the other key is identical to this one except for Variation
- L45 _public prototype_ `static FString ToAssetNameString(const FMetaHumanPaletteItemKey& InKey);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Item", meta = (ScriptMethod))` — @brief Produces a string suitable for using as part of an asset name
- L51 _public prototype_ `static bool IsNull(const FMetaHumanPaletteItemKey& InKey);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Item", meta = (ScriptMethod))` — @brief Returns true if the key is the null item key (does not reference any asset).

#### class `UMetaHumanPaletteItemPathBlueprintLibrary`  
`class UMetaHumanPaletteItemPathBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L59-71_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: @brief Exposes blueprint functions to operate on FMetaHumanPaletteItemPath.
- L70 _public prototype_ `static FMetaHumanPaletteItemPath MakeItemPath(const FMetaHumanPaletteItemKey& InItemKey);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Item", meta = (NativeMakeFunc))` — @brief Constructs a FMetaHumanPaletteItemPath from a FMetaHumanPaletteItemKey. Exposed as a Make function for FMetaHumanPaletteItemPath.

#### enum `EMetaHumanCharacterInstanceParameterType`  
`enum class EMetaHumanCharacterInstanceParameterType : uint8`  
_L81-91_
- reflection: `UENUM()`
- desc: The types of parameters supported by Wardrobe Items. These map directly to EPropertyBagPropertyType but since not all values are exposed (e.g. Struct is hidden) we have a mapped enum to keep the surface area scoped.
- L83 _public enumerator_ `None = (uint8) EPropertyBagPropertyType::None UMETA(Hidden)`
- L84 _public enumerator_ `Bool = (uint8) EPropertyBagPropertyType::Bool`
- L85 _public enumerator_ `Float = (uint8) EPropertyBagPropertyType::Float`
- L86 _public enumerator_ `Name = (uint8) EPropertyBagPropertyType::Name`
- L87 _public enumerator_ `String = (uint8) EPropertyBagPropertyType::String`
- L88 _public enumerator_ `Color = (uint8) EPropertyBagPropertyType::Struct`
- L89 _public enumerator_ `Object = (uint8) EPropertyBagPropertyType::Object`
- L90 _public enumerator_ `SoftObject = (uint8) EPropertyBagPropertyType::SoftObject`

#### struct `FMetaHumanCharacterInstanceParameter`  
`struct FMetaHumanCharacterInstanceParameter`  
_L103-131_
- reflection: `USTRUCT(BlueprintType)`
- desc: @brief Struct that represents a parameter of a particular item in a collection. This struct is designed to work in scripting environments and has functions to get and set values exposed via UMetaHumanCharacterInstanceParameterBlueprintLibrary. Note that calling one of the Set functions automatically updates the parameter value for the item it represents on the instance that was used when querying them.
- L109 _public member_ `FName Name;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MetaHuman|Parameters")` — The name of the parameter.
- L113 _public member_ `EMetaHumanCharacterInstanceParameterType Type = EMetaHumanCharacterInstanceParameterType::None;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MetaHuman|Parameters")` — The type of the parameter. Use this to decide which Set/Get function to call.
- L117 _public member_ `FMetaHumanPaletteItemPath ItemPath;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MetaHuman|Parameters")` — The item path that this parameter belongs to.
- L126 _public member_ `TObjectPtr<UClass> ObjectClass = nullptr;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MetaHuman|Parameters")` — For Object and SoftObject parameters, the class the property is constrained to. Useful for telling whether a particular Object parameter is asking for a UTexture2D, a UMaterialInterface, etc, before deciding what to set on it.
- L130 _public member_ `TWeakObjectPtr<UMetaHumanInstance> Instance;` — `UPROPERTY()` — Pointer back to the instance this parameter was queried from.

#### class `UMetaHumanCharacterInstanceParameterBlueprintLibrary`  
`class UMetaHumanCharacterInstanceParameterBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L141-216_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: @brief Provides Get/Set functions for FMetaHumanCharacterInstanceParameter. Calling a Set function applies the new value to the instance that the parameter was queried from, immediately.
- L147 _public prototype_ `static bool GetBoolInstanceParameter(const FMetaHumanCharacterInstanceParameter& InInstanceParam, bool& OutValue);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parameters", meta = (ScriptMethod = "GetBool", Keywords = "GetBool"))`
- L150 _public prototype_ `static bool SetBoolInstanceParameter(const FMetaHumanCharacterInstanceParameter& InInstanceParam, bool InValue);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parameters", meta = (ScriptMethod = "SetBool", Keywords = "SetBool"))`
- L153 _public prototype_ `static bool GetFloatInstanceParameter(const FMetaHumanCharacterInstanceParameter& InInstanceParam, float& OutValue);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parameters", meta = (ScriptMethod = "GetFloat", Keywords = "GetFloat GetScalar"))`
- L156 _public prototype_ `static bool SetFloatInstanceParameter(const FMetaHumanCharacterInstanceParameter& InInstanceParam, float InValue);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parameters", meta = (ScriptMethod = "SetFloat", Keywords = "SetFloat SetScalar"))`
- L159 _public prototype_ `static bool GetNameInstanceParameter(const FMetaHumanCharacterInstanceParameter& InInstanceParam, FName& OutValue);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parameters", meta = (ScriptMethod = "GetName", Keywords = "GetName"))`
- L162 _public prototype_ `static bool SetNameInstanceParameter(const FMetaHumanCharacterInstanceParameter& InInstanceParam, FName InValue);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parameters", meta = (ScriptMethod = "SetName", Keywords = "SetName"))`
- L165 _public prototype_ `static bool GetStringInstanceParameter(const FMetaHumanCharacterInstanceParameter& InInstanceParam, FString& OutValue);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parameters", meta = (ScriptMethod = "GetString", Keywords = "GetString"))`
- L168 _public prototype_ `static bool SetStringInstanceParameter(const FMetaHumanCharacterInstanceParameter& InInstanceParam, const FString& InValue);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parameters", meta = (ScriptMethod = "SetString", Keywords = "SetString"))`
- L171 _public prototype_ `static bool GetColorInstanceParameter(const FMetaHumanCharacterInstanceParameter& InInstanceParam, FLinearColor& OutValue);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parameters", meta = (ScriptMethod = "GetColor", Keywords = "GetColor GetVector"))`
- L174 _public prototype_ `static bool SetColorInstanceParameter(const FMetaHumanCharacterInstanceParameter& InInstanceParam, const FLinearColor& InValue);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parameters", meta = (ScriptMethod = "SetColor", Keywords = "SetColor SetVector"))`
- L184 _public prototype_ `static bool GetObjectInstanceParameter(const FMetaHumanCharacterInstanceParameter& InInstanceParam, UObject*& OutValue);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parameters", meta = (ScriptMethod = "GetObject", Keywords = "GetObject GetTexture"))` — Get the object value of an Object-typed parameter. @param OutValue Receives the current value, possibly nullptr if the parameter is unset. @return true if the read succeeded, false on type mismatch or if the parameter could not be located on the instance.
- L195 _public prototype_ `static bool SetObjectInstanceParameter(const FMetaHumanCharacterInstanceParameter& InInstanceParam, UObject* InValue);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parameters", meta = (ScriptMethod = "SetObject", Keywords = "SetObject SetTexture"))` — Set the object value of an Object-typed parameter. The provided object's class must derive from FMetaHumanCharacterInstanceParameter::ObjectClass. Pass nullptr to clear the parameter. @return true if the write succeeded.
- L204 _public prototype_ `static bool GetSoftObjectInstanceParameter(const FMetaHumanCharacterInstanceParameter& InInstanceParam, TSoftObjectPtr<UObject>& OutValue);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parameters", meta = (ScriptMethod = "GetSoftObject", Keywords = "GetSoftObject"))` — Get the soft-object path of a SoftObject-typed parameter. @param OutValue Receives the current path, which may be empty if the parameter is unset. @return true if the read succeeded.
- L215 _public prototype_ `static bool SetSoftObjectInstanceParameter(const FMetaHumanCharacterInstanceParameter& InInstanceParam, const TSoftObjectPtr<UObject>& InValue);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Parameters", meta = (ScriptMethod = "SetSoftObject", Keywords = "SetSoftObject"))` — Set the soft-object value of a SoftObject-typed parameter. The referenced asset's class (when loaded) must derive from FMetaHumanCharacterInstanceParameter::ObjectClass. Pass an empty soft-pointer to clear. @return true if the write succeeded.

#### class `UMetaHumanPipelineSlotSelectionBlueprintLibrary`  
`class UMetaHumanPipelineSlotSelectionBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L223-242_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: @brief Exposes blueprint functions to operate on FMetaHumanPipelineSlotSelection.
- L232 _public prototype_ `static FMetaHumanPipelineSlotSelection MakeSlotSelection(FName SlotName, const FMetaHumanPaletteItemKey& SelectedItem, FMetaHumanPaletteItemPath ParentItemPath = FMetaHumanPaletteItemPath());` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Pipeline", meta = (NativeMakeFunc))` — Construct a slot selection for a virtual slot on the Collection itself.
- L235 _public prototype_ `static FMetaHumanPaletteItemPath GetSelectedItemPath(const FMetaHumanPipelineSlotSelection& InSlotSelection);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Pipeline", meta = (ScriptMethod))`
- L238 _public prototype_ `static FName GetSelectedSlotName(const FMetaHumanPipelineSlotSelection& InSlotSelection);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Pipeline", meta = (ScriptMethod))`
- L241 _public prototype_ `static FMetaHumanPaletteItemKey GetSelectedItemKey(const FMetaHumanPipelineSlotSelection& InSlotSelection);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Pipeline", meta = (ScriptMethod))`

#### class `UMetaHumanCollectionBlueprintLibrary`  
`class UMetaHumanCollectionBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L250-308_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: @brief Exposes blueprint functions to enumerate the contents of a UMetaHumanCharacterPalette, which is the base class of both UMetaHumanCollection and UMetaHumanWardrobeItem.
- L260 _public prototype_ `static UMetaHumanCharacterPipelineSpecification* GetPipelineSpecification(UMetaHumanCharacterPalette* Palette);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Palette", meta = (ScriptMethod))` — Returns the pipeline specification for the palette's pipeline. May be null if no pipeline is set or the pipeline doesn't expose a specification.
- L269 _public prototype_ `static TArray<FName> GetSlotNames(UMetaHumanCharacterPalette* Palette);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Palette", meta = (ScriptMethod))` — Returns the virtual slot names defined by the palette's pipeline. Slot selections on a MetaHuman Instance should target virtual slots; real (backing) slots are an implementation detail of the pipeline.
- L273 _public prototype_ `static TArray<FMetaHumanPaletteItemKey> GetAllItemKeys(UMetaHumanCharacterPalette* Palette);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Palette", meta = (ScriptMethod))` — Returns the keys of every item in the palette.
- L282 _public prototype_ `static TArray<FMetaHumanPaletteItemKey> GetItemKeysForSlot(UMetaHumanCharacterPalette* Palette, FName SlotName);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Palette", meta = (ScriptMethod))` — Returns the keys of items targeting the given virtual slot. The slot name is resolved through the pipeline so callers can safely pass virtual slot names (the same names returned by GetSlotNames).
- L291 _public prototype_ `static TArray<FMetaHumanPaletteItemKey> GetItemKeysForPrincipalAsset(UMetaHumanCharacterPalette* Palette, UObject* PrincipalAsset);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Palette", meta = (ScriptMethod))` — Returns the keys of items in the palette whose principal asset is the given asset. Multiple results are possible if the palette contains multiple Variations of the same asset.
- L297 _public prototype_ `static TArray<FMetaHumanPaletteItemKey> GetItemKeysForWardrobeItem(UMetaHumanCharacterPalette* Palette, UMetaHumanWardrobeItem* WardrobeItem);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Palette", meta = (ScriptMethod))` — Returns the keys of items in the palette that reference the given external wardrobe item.
- L301 _public prototype_ `static FName GetItemSlotName(UMetaHumanCharacterPalette* Palette, const FMetaHumanPaletteItemKey& ItemKey);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Palette", meta = (ScriptMethod))` — Returns the slot name an item is authored against, or NAME_None if the key is not found.
- L306 _public prototype_ `static FText GetItemDisplayName(UMetaHumanCharacterPalette* Palette, const FMetaHumanPaletteItemKey& ItemKey);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Palette", meta = (ScriptMethod))` — Returns the display name for an item, or empty text if the key is not found.

#### class `UMetaHumanCharacterInstanceBlueprintLibrary`  
`class UMetaHumanCharacterInstanceBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L315-361_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: @brief Exposes blueprint functions to operate on UMetaHumanInstance for procedural authoring.
- L328 _public prototype_ `static UMetaHumanInstance* DuplicateMetaHumanInstance(UMetaHumanInstance* Source, UObject* Outer = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Instance")` — Creates a new transient UMetaHumanInstance that is an unassembled duplicate of the source @param Source         The instance to duplicate. If null, returns null. @param Outer          Optional outer for the new instance. If null, the transient package is used. @return The new instance, or null if Source was null.
- L334 _public prototype_ `static TArray<FMetaHumanCharacterInstanceParameter> GetInstanceParametersForItem(UMetaHumanInstance* InInstance, const FMetaHumanPaletteItemPath& ItemPath);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Instance", meta = (ScriptMethod = "GetInstanceParameters"))` — @brief Gets the list of all instance parameters for a given item.
- L342 _public prototype_ `static TArray<FMetaHumanPaletteItemPath> GetInstanceParameterItemPaths(UMetaHumanInstance* InInstance);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Instance", meta = (ScriptMethod))` — Returns every item path on this instance that has any instance parameters defined. The empty path represents the Collection itself.
- L350 _public prototype_ `static bool TryGetInstanceParameter(UMetaHumanInstance* InInstance, const FMetaHumanPaletteItemPath& ItemPath, FName ParameterName, FMetaHumanCharacterInstanceParameter& OutParameter);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Instance", meta = (ScriptMethod))` — Look up a single parameter on the instance by item path and name. @return true if found.
- L360 _public prototype_ `static TArray<FMetaHumanPaletteItemKey> GetAllowedItemKeysForSlot(UMetaHumanInstance* InInstance, FName SlotName);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Instance", meta = (ScriptMethod))` — Returns the item keys targeting the given slot that are allowed by the Instance's Collection Pipeline given the Instance's current slot selections. Use this to ask "with what I've already picked, which items can I now select for SlotName?". For example, after picking a body, this can return the heads compatible with that body.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanCollectionEditorPipeline.h` (Public)


#### struct `FMetaHumanBuildInputBase`  
`struct FMetaHumanBuildInputBase`  
_L26-37_
- reflection: `USTRUCT(BlueprintType)`
- desc: The Build Input struct that will be set by the Character editor for builds initiated from there. If your pipeline has a custom Build Input struct, have it inherit from this one for compatibility with the Character editor.
- L36 _public member_ `FMetaHumanPaletteItemKey EditorPreviewCharacter;` — `UPROPERTY()` — The Character being edited by this Character editor. Pipelines should use the preview assets for this Character when building.

#### class `UMetaHumanCollectionEditorPipeline`  
`class UMetaHumanCollectionEditorPipeline : public UMetaHumanCharacterEditorPipeline`  
_L43-236_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UMetaHumanCharacterEditorPipeline`
- desc: The editor-only component of a UMetaHumanCollectionPipeline.
- L49 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnBuildComplete, EMetaHumanBuildStatus , TSharedPtr<FMetaHumanCollectionBuiltData> );`
- L83 _public prototype_ `virtual void BuildCollection(const FBuildCollectionParams& Params, const FOnBuildComplete& OnComplete) const PURE_VIRTUAL(UMetaHumanCollectionEditorPipeline::BuildCollection,);`
- L95 _public prototype_ `virtual bool ValidateCollection(TNotNull<UMetaHumanCollection*> Collection);` — Returns true if the Collection is in a valid state to be built. Implementations may modify this pipeline instance or the Collection to automatically fix configuration errors. They may also show interactive UI when FApp::IsUnattended() returns false. If this function returns false, the build will be aborted.
- L98 _public prototype_ `void BuildCollection( TNotNull<const UMetaHumanCollection*> Collection, TNotNull<UObject*> OuterForGeneratedAssets, const TArray<FMetaHumanPinnedSlotSelection>& SortedPinnedSlotSelections, const TArray<FMetaHumanPaletteItemPath>& SortedItemsToExclude, const FInstancedStruct& BuildInput, EMetaHumanCharacterPaletteBuildQuality Quality, ITargetPlatform* TargetPlatform, const FOnBuildComplete& OnComplete) const;` — `UE_DEPRECATED(5.8, "Quality is now a property of the Collection. TargetPlatform is no longer used at build time. Use the new BuildCollection overload.")`
- L112 _public prototype_ `virtual bool CanBuild() const PURE_VIRTUAL(UMetaHumanCollectionEditorPipeline::CanBuild, return true;);` — Utility to check if the pipeline has valid properties to build and unpack a collection Gives the opportunity for backwards compatibility checks and user prompts before even attempting to unpack
- L119 _public prototype_ `virtual bool ShouldCookInstanceAsAssembled(TNotNull<const UMetaHumanInstance*> Instance) const;` — Returns true if the given MetaHuman Instance should have its assembly output baked into the cooked package by default.
- L131 _public prototype_ `virtual void UnpackCollectionAssets( TNotNull<const UMetaHumanCollection*> Collection, FMetaHumanCollectionBuiltData& CollectionBuiltData, const FOnUnpackComplete& OnComplete) const;` — IMPORTANT: Don't call this directly. Call UnpackAssets on the Collection. Moves any internal assets from the Collection's built data, such as meshes and textures, out to their own packages, so that they are visible in the Content Browser. These assets will still be referenced from the Collection's built data. Requires the Collection to be built first.
- L154 _public prototype_ `virtual bool TryCreateItemForImport( TNotNull<UMetaHumanCollection*> Collection, FName SlotName, TNotNull<const UMetaHumanWardrobeItem*> SourceWardrobeItem, FMetaHumanCharacterPaletteItem& OutItem);` — Creates a FMetaHumanCharacterPaletteItem for a Wardrobe Item whose pipeline is not directly compatible with the target slot. The implementation should: - Create a new internal UMetaHumanWardrobeItem as a subobject of the Collection - Set up the appropriate compatible item pipeline on it - Populate the new pipeline, e.g. copy relevant settings from the source Wardrobe Item The Variation field does not need to be set; the Collection will ensure uniqueness. @param Collection          The Collection being imported into (use as outer for the new internal WI) @param SlotName            The target slot @param SourceWardrobeItem  The WI of the item being imported @param OutItem             The item to be added to the Collection @return true if the item was created successfully
- L165 _public prototype_ `virtual bool TryUnpackInstanceAssets( TNotNull<UMetaHumanInstance*> Instance, FInstancedStruct& AssemblyOutput, TArray<FMetaHumanGeneratedAssetMetadata>& AssemblyAssetMetadata, const FString& TargetFolder) const PURE_VIRTUAL(UMetaHumanCollectionEditorPipeline::TryUnpackInstanceAssets,return false;);` — IMPORTANT: Don't call this directly. Call TryUnpack on the Instance. Unpacks any assets generated during Assembly and contained in the Instance itself.
- L173 _public prototype_ `virtual TNotNull<const UMetaHumanCollectionPipeline*> GetRuntimePipeline() const;` — Returns the runtime pipeline instance corresponding to this editor pipeline instance.
- L176 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterPipeline*> GetRuntimeCharacterPipeline() const override;` — Calls GetRuntimePipeline. No need for subclasses to implement this.
- L188 _public prototype_ `virtual TSubclassOf<AActor> GetEditorActorClass() const PURE_VIRTUAL(UMetaHumanCollectionEditorPipeline::GetEditorActorClass, return nullptr;);` — Returns an actor class that supports Instances targeting this pipeline. This actor type will be used in the Character editor viewport. The returned class must implement IMetaHumanCharacterEditorActorInterface. If this returns null, it will be treated as an error but callers will handle it gracefully. Pipelines that don't have their own editor actor class can return AMetaHumanCharacterEditorActor::StaticClass().
- L206 _public prototype_ `virtual bool BeginCharacterEditorAssemble(TNotNull<UMetaHumanCollection*> InCollection, const FString& InCharacterName);` — These functions are called before and after the Character editor assembly process. The passed-in Collection is a copy of the Character's internal Collection, and this pipeline instance is also a copy, so these functions may modify the Collection and pipeline without affecting the associated Character.
- L207 _public prototype_ `virtual void EndCharacterEditorAssemble(TNotNull<UMetaHumanCollection*> InCollection);`
- L216 _public prototype_ `virtual UBlueprint* WriteActorBlueprint(const FString & InBlueprintPath) const;` — `UE_DEPRECATED(5.7, "Use WriteActorBlueprint(const FWriteBlueprintSettings&) instead.")` — Generates a blueprint actor asset on the given path and quality level. Resulting blueprint should be an asset based on or a duplicate of the GetActorClass(), but this is implementation dependent.
- L224 _public prototype_ `virtual UBlueprint* WriteActorBlueprint(const FWriteBlueprintSettings& InWriteBlueprintSettings) const;`
- L232 _public prototype_ `virtual bool UpdateActorBlueprint( const UMetaHumanInstance* InCharacterInstance, UBlueprint* InBlueprint) const;` — Updates the given blueprint asset with the given instance. In the implementation, user can add components to the blueprint or reconfigure it depending on the parameters (e.g. legacy, export quality etc.).

#### struct `UMetaHumanCollectionEditorPipeline::FBuildCollectionParams`  
`struct FBuildCollectionParams`  
_L74-81_
- desc: Build the Collection Most code should call UMetaHumanCollection::Build instead of calling this directly. For any slot that has at least one entry in SortedPinnedSlotSelections, the slot will be locked to the given selections at assembly time and users won't be able to make any assignment to the slot on the Instance. A null selection may be pinned by having a slot selection that specifies the null item. Items assigned to a pinned slot that are not part of the pinned selection will be added to SortedItemsToExclude automatically. SortedPinnedSlotSelections is a hint to the pipeline that no other selection will be possible for the slot. The pipeline is not obliged to use this information for anything, but it may choose to bake certain data into its build output based on its knowledge about which items will be selected at assembly time. Items named in pinned selections should still produce build output, and will still have AssembleItem called for them when the Instance is assembled. Pinned items may still produce Instance Parameters during assembly.
- L76 _public member_ `TNotNull<const UMetaHumanCollection*> Collection;`
- L77 _public member_ `TNotNull<UObject*> OuterForGeneratedAssets;`
- L78 _public member_ `TConstArrayView<FMetaHumanPinnedSlotSelection> SortedPinnedSlotSelections;`
- L79 _public member_ `TConstArrayView<FMetaHumanPaletteItemPath> SortedItemsToExclude;`
- L80 _public member_ `FInstancedStruct BuildInput;`

#### struct `UMetaHumanCollectionEditorPipeline::FWriteBlueprintSettings`  
`struct FWriteBlueprintSettings`  
_L218-223_
- L220 _public member_ `FString BlueprintPath;`
- L221 _public member_ `EMetaHumanQualityLevel QualityLevel = EMetaHumanQualityLevel::Cinematic;`
- L222 _public member_ `FName AnimationSystemName;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`
- L49 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnBuildComplete, EMetaHumanBuildStatus , TSharedPtr<FMetaHumanCollectionBuiltData> );`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanCollectionPipeline.h` (Public)


#### class `UMetaHumanCollectionPipeline`  
`class UMetaHumanCollectionPipeline : public UMetaHumanCharacterPipeline`  
_L19-172_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UMetaHumanCharacterPipeline`
- desc: A Collection-specific subclass of Character Pipeline
- L26 _public prototype_ `virtual const UMetaHumanCollectionEditorPipeline* GetEditorPipeline() const PURE_VIRTUAL(UMetaHumanCollectionPipeline::GetEditorPipeline,return nullptr;);` — Returns the editor-only component of this pipeline
- L30 _public prototype_ `virtual UMetaHumanCollectionEditorPipeline* GetMutableEditorPipeline() PURE_VIRTUAL(UMetaHumanCollectionPipeline::GetMutableEditorPipeline, return nullptr;);` — Override to narrow down the return type for collection pipelines
- L54 _public prototype_ `virtual void AssembleCollection(const FAssembleCollectionParams& Params, const FOnAssemblyComplete& OnComplete) const PURE_VIRTUAL(UMetaHumanCollectionPipeline::AssembleCollection,);`
- L58 _public prototype_ `void AssembleCollection( TNotNull<const UMetaHumanCollection*> Collection, EMetaHumanCharacterPaletteBuildQuality Quality, const TArray<FMetaHumanPipelineSlotSelectionData>& SlotSelections, const FInstancedStruct& AssemblyInput, TNotNull<UObject*> OuterForGeneratedObjects, const FOnAssemblyComplete& OnComplete) const;` — `UE_DEPRECATED(5.8, "This overload of AssembleCollection is deprecated")`
- L80 _public prototype_ `virtual void SetPostAssemblyParameters( TNotNull<const UMetaHumanCollection*> Collection, const FMetaHumanPostAssemblyParameterOutputCollectionView& AllPostAssemblyParameters, const FMetaHumanPaletteItemPath& TargetItemPath, const FInstancedPropertyBag& ModifiedPostAssemblyParameters, FInstancedStruct& InOutCollectionAssemblyOutput) const;` — Set Post-Assembly Parameters on the given item path. The empty item path signifies the Collection's own parameters. AllPostAssemblyParameters contains the complete set of Post-Assembly Parameters that were produced during assembly and their parameter context. ModifiedPostAssemblyParameters contains any PAPs that have been modified since the last call to SetPostAssemblyParameters or the last assembly, whichever was more recent. Note that PAPs can only be modified on one item at a time and this function must be called after each change. This shouldn't be too restrictive for most use cases and helps to simplify Collection Pipeline implementations.
- L94 _public prototype_ `virtual TSubclassOf<AActor> GetActorClass() const PURE_VIRTUAL(UMetaHumanCollectionPipeline::GetActorClass, return nullptr;);` — Returns an actor class that supports Instances targeting this pipeline. The returned class must implement IMetaHumanCharacterActorInterface. May return null.
- L124 _public prototype_ `virtual bool AreSlotSelectionsAllowed( TNotNull<const UMetaHumanCollection*> Collection, TArrayView<const FMetaHumanPipelineSlotSelection> SlotSelections, FText& OutDisallowedReason) const;` — Returns true if the given slot selections are a permitted combination. Note that the Collection must have been built before calling this. This allows the pipeline to restrict Instances to selecting items that are compatible with each other using any arbitary logic. If AreSlotSelectionsAllowed returns false, the text assigned to OutDisallowedReason may be shown to the user to explain why this combination is not allowed. If SlotSelections is empty, AreSlotSelectionsAllowed must return true. If there's no entry for a certain slot in the SlotSelections array, the pipeline must implicitly make a valid selection for that slot. In other words, a pipeline can't return false from AreSlotSelectionsAllowed for the reason that there's no explicit selection for a certain slot. If SlotSelections specifies the empty item key for a slot, this means that no item is selected. It's valid for a pipeline to *disallow* selecting no item for a slot, meaning that at least one item must be selected for the slot, but in that case, if there's no SlotSelections entry for the slot it must implicitly select a valid item. The order of elements in SlotSelections must not affect the return value of this function. It may affect OutDisallowedReason, for example if there are multiple reasons why the selection is not allowed.
- L136 _public prototype_ `virtual const UMetaHumanItemPipeline* GetFallbackItemPipelineForAssetType(const TSoftClassPtr<UObject>& InAssetClass) const;` — Returns an item pipeline instance for given asset class. This utility can be used to provide common item pipeline class for all principal assets of the given class, effectively removing the necessity for defining a pipeline for each wardrobe item asset.
- L145 _protected prototype_ `virtual FStructView GetItemAssemblyOutputReference( TNotNull<const UMetaHumanCollection*> Collection, const FMetaHumanPostAssemblyParameterOutputCollectionView& AllPostAssemblyParameters, const FMetaHumanPaletteItemPath& TargetItemPath, const FInstancedPropertyBag& ModifiedPostAssemblyParameters, FInstancedStruct& InCollectionAssemblyOutput) const;` — Will be called when setting Post-Assembly Parameters if EMetaHumanAssemblyOutputMappingMethod::CustomReference is specified for the target slot. See comments on EMetaHumanAssemblyOutputMappingMethod.
- L158 _protected prototype_ `virtual FInstancedStruct GetItemAssemblyOutputValue( TNotNull<const UMetaHumanCollection*> Collection, const FMetaHumanPostAssemblyParameterOutputCollectionView& AllPostAssemblyParameters, const FMetaHumanPaletteItemPath& TargetItemPath, const FInstancedPropertyBag& ModifiedPostAssemblyParameters, const FInstancedStruct& InCollectionAssemblyOutput) const;` — Will be called when setting Post-Assembly Parameters if EMetaHumanAssemblyOutputMappingMethod::CustomValue is specified for the target slot. See comments on EMetaHumanAssemblyOutputMappingMethod.
- L165 _protected prototype_ `virtual void SetItemAssemblyOutputValue( TNotNull<const UMetaHumanCollection*> Collection, const FMetaHumanPostAssemblyParameterOutputCollectionView& AllPostAssemblyParameters, const FMetaHumanPaletteItemPath& TargetItemPath, const FInstancedPropertyBag& ModifiedPostAssemblyParameters, FInstancedStruct&& ItemAssemblyOutput, FInstancedStruct& InOutCollectionAssemblyOutput) const;`

#### struct `UMetaHumanCollectionPipeline::FAssembleCollectionParams`  
`struct FAssembleCollectionParams`  
_L45-52_
- desc: Takes the opaque built data from the Collection and evaluates it with the given parameters to produce the meshes (etc) and populate the Assembly Output. All entries in SlotSelections are guaranteed to reference valid items in the Collection, and AreSlotSelectionsAllowed must have returned true with this set of slot selections. AssemblyParameters doesn't have to contain all parameters that were produced by the build stage, it may just be a subset. Pipelines can read the full set of parameters from the built data.
- L47 _public member_ `TNotNull<const UMetaHumanCollection*> Collection;`
- L48 _public member_ `TNotNull<UObject*> OuterForGeneratedObjects;`
- L49 _public member_ `TConstArrayView<FMetaHumanPipelineSlotSelectionData> SlotSelections;`
- L50 _public member_ `FMetaHumanInstanceParameterCollectionView AssemblyParameters;`
- L51 _public member_ `FInstancedStruct AssemblyInput;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanGeneratedAssetMetadata.h` (Public)


#### struct `FMetaHumanGeneratedAssetMetadata`  
`struct FMetaHumanGeneratedAssetMetadata`  
_L16-48_
- reflection: `USTRUCT()`
- desc: Metadata about a generated asset, usually one that is not in its own package. This is used when unpacking assets into their own packages, to give them friendly names and helpful paths chosen by the system that generated them.
- L20 _public prototype_ `FMetaHumanGeneratedAssetMetadata() = default;`
- L21 _public prototype_ `~FMetaHumanGeneratedAssetMetadata() = default;`
- L23 _public prototype_ `FMetaHumanGeneratedAssetMetadata(const FMetaHumanGeneratedAssetMetadata&) = default;`
- L24 _public prototype_ `FMetaHumanGeneratedAssetMetadata(FMetaHumanGeneratedAssetMetadata&&) = default;`
- L25 _public prototype_ `FMetaHumanGeneratedAssetMetadata& operator=(const FMetaHumanGeneratedAssetMetadata&) = default;`
- L26 _public prototype_ `FMetaHumanGeneratedAssetMetadata& operator=(FMetaHumanGeneratedAssetMetadata&&) = default;`
- L28 _public prototype_ `FMetaHumanGeneratedAssetMetadata(TObjectPtr<UObject> InObject, const FString& InPreferredSubfolderPath, const FString& InPreferredName, bool bInSubfolderIsAbsolute = false);`
- L31 _public member_ `TObjectPtr<UObject> Object;` — `UPROPERTY()`
- L39 _public member_ `FString PreferredSubfolderPath;` — `UPROPERTY()` — A hint providing a useful subfolder path that this asset could be unpacked to. May contain multiple path elements, e.g. "Face/Textures".
- L43 _public member_ `bool bSubfolderIsAbsolute = false;` — `UPROPERTY()` — If true, treat PreferredSubfolderPath as an absolute package path.
- L47 _public member_ `FString PreferredName;` — `UPROPERTY()` — A hint providing a useful name that this asset could be given when it's unpacked.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanInstance.h` (Public)


#### enum `EMetaHumanCharacterAssemblyResult`  
`enum class EMetaHumanCharacterAssemblyResult : uint8`  
_L23-27_
- reflection: `UENUM()`
- L25 _public enumerator_ `Succeeded`
- L26 _public enumerator_ `Failed`

#### enum `EMetaHumanInstanceParameterOverrideResult`  
`enum class EMetaHumanInstanceParameterOverrideResult : uint8`  
_L30-37_
- reflection: `UENUM(meta = (Bitflags))`
- L32 _public enumerator_ `NoParametersWereModified = 0`
- L34 _public enumerator_ `ReassemblyRequiredToApplyNewParameters = 1 << 0`
- L35 _public enumerator_ `PostAssemblyParametersWereModified = 1 << 1`
- L36 _public enumerator_ `UnrecognizedParametersWereStored = 1 << 2`

#### enum `EMetaHumanInstanceCookBehavior`  
`enum class EMetaHumanInstanceCookBehavior : uint8`  
_L45-58_
- reflection: `UENUM()`
- desc: Determines whether a MetaHuman Instance should be assembled at cook time and have its assembly output baked into the cooked package.
- L51 _public enumerator_ `PipelineDefault` — Defer to the Collection Editor Pipeline's ShouldCookInstanceAsAssembled function to decide whether to assemble the Instance at cook time.
- L54 _public enumerator_ `Yes` — Always assemble the Instance at cook time.
- L57 _public enumerator_ `No` — Never assemble the Instance at cook time.

#### struct `FMetaHumanProcessedAssemblyOutput`  
`struct FMetaHumanProcessedAssemblyOutput`  
_L62-103_
- reflection: `USTRUCT()`
- desc: The output of an assembly and its associated data
- L68 _public prototype_ `FMetaHumanProcessedAssemblyOutput() = default;` — Explicit defaults required because of the deprecated UPROPERTY below.
- L69 _public prototype_ `~FMetaHumanProcessedAssemblyOutput() = default;`
- L70 _public prototype_ `FMetaHumanProcessedAssemblyOutput(const FMetaHumanProcessedAssemblyOutput&) = default;`
- L71 _public prototype_ `FMetaHumanProcessedAssemblyOutput(FMetaHumanProcessedAssemblyOutput&&) = default;`
- L72 _public prototype_ `FMetaHumanProcessedAssemblyOutput& operator=(const FMetaHumanProcessedAssemblyOutput&) = default;`
- L73 _public prototype_ `FMetaHumanProcessedAssemblyOutput& operator=(FMetaHumanProcessedAssemblyOutput&&) = default;`
- L77 _public function_ `bool IsValid() const` — Returns true if there's a valid assembly output stored in this struct.
- L89 _public member_ `FInstancedStruct AssemblyOutput;` — `UPROPERTY()` — A structure produced by the Character Pipeline that contains the assets belonging to this instance, such as meshes and materials. The type of this struct is guaranteed to be Collection->GetPipeline()->GetSpecification()->AssemblyOutputStruct
- L93 _public member_ `FMetaHumanPostAssemblyParameterOutputCollection PostAssemblyParametersFromPipeline;` — `UPROPERTY()` — The unmodified set of Post-Assembly Parameters produced by the most recent assembly
- L97 _public member_ `TSet<FMetaHumanPaletteItemPath> ItemsUsingDeprecatedInstanceParameters;` — `UE_DEPRECATED(5.8, "This is only used to process the deprecated form of Instance Parameters")` — `UPROPERTY()`
- L101 _public member_ `TArray<FMetaHumanGeneratedAssetMetadata> AssemblyAssetMetadata;` — `UPROPERTY()`

#### enum `EMetaHumanUnusedSlotBehavior`  
`enum class EMetaHumanUnusedSlotBehavior : uint8`  
_L109-120_
- desc: Determines how pipeline slots that don't have an item selected for them should be handled when the Instance is converted to a set of pinned slot selections.
- L116 _public enumerator_ `Unpinned` — Unused slots should be left unpinned. In the built Collection, the user will be able to assign these slots using an Instance.
- L119 _public enumerator_ `PinnedToEmpty` — Unused slots should be "pinned to empty", so they will not be assignable by an Instance.

#### class `UMetaHumanInstance`  
`class UMetaHumanInstance : public UObject`  
_L133-512_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: Used to assemble a renderable character from a MetaHuman Collection. Can be either an asset used in the editor or a transient object generated at runtime.
- L144 _public prototype_ `void Assemble(const FMetaHumanCharacterAssembled& OnAssembled);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Instance")` — Runs the associated Character Pipeline's assembly function to populate the AssemblyOutput. Fails gracefully if no MetaHuman Collection is set.
- L145 _public prototype_ `void Assemble(const FMetaHumanCharacterAssembledNative& OnAssembledNative = FMetaHumanCharacterAssembledNative());`
- L146 _public prototype_ `void Assemble(const FMetaHumanCharacterAssembled& OnAssembled, const FMetaHumanCharacterAssembledNative& OnAssembledNative);`
- L149 _public prototype_ `void Assemble(EMetaHumanCharacterPaletteBuildQuality Quality, const FMetaHumanCharacterAssembled& OnAssembled);` — `UE_DEPRECATED(5.8, "Quality is now a property of the Collection. This overload will be removed.")`
- L151 _public prototype_ `void Assemble(EMetaHumanCharacterPaletteBuildQuality Quality, const FMetaHumanCharacterAssembledNative& OnAssembledNative = FMetaHumanCharacterAssembledNative());` — `UE_DEPRECATED(5.8, "Quality is now a property of the Collection. This overload will be removed.")`
- L153 _public prototype_ `void Assemble(EMetaHumanCharacterPaletteBuildQuality Quality, const FMetaHumanCharacterAssembled& OnAssembled, const FMetaHumanCharacterAssembledNative& OnAssembledNative);` — `UE_DEPRECATED(5.8, "Quality is now a property of the Collection. This overload will be removed.")`
- L157 _public prototype_ `const FInstancedStruct& GetAssemblyOutput();` — `UFUNCTION(BlueprintPure, Category = "MetaHuman|Instance")` — Assemble if necessary and return the assembly output
- L160 _public prototype_ `const FInstancedStruct& GetAssemblyOutput() const;` — `UE_DEPRECATED(5.8, "GetAssemblyOutput has been made non-const. Use GetExistingAssemblyOutput to get the assembly output without the possibility of triggering assembly.")`
- L171 _public prototype_ `const FInstancedStruct& GetExistingAssemblyOutput() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Instance")` — GetAssemblyOutput should be used instead of this function in most cases. Returns the existing assembly output, if any. This is useful if you're in a const-only context and are triggering assembly via a different path, or deliberately want to avoid triggering assembly if it hasn't been done yet.
- L175 _public prototype_ `bool IsAssembled() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Instance")` — Returns true if the Instance is assembled and up to date
- L183 _public prototype_ `void ClearAssemblyOutput();` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Instance")` — Clear the result of the last assembly. GetAssemblyOutput will return an empty struct after calling this.
- L191 _public prototype_ `void SetMetaHumanCollection(UMetaHumanCollection* InCollection);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Instance")` — Set the MetaHuman Collection that this instance will assemble from. Call with nullptr to clear the existing Collection.
- L199 _public prototype_ `UMetaHumanCollection* GetMetaHumanCollection() const;` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman|Instance")` — Return the MetaHuman Collection that this instance will assemble from. Returns nullptr if no collection has been set.
- L212 _public prototype_ `void CopyContentsFrom(TNotNull<const UMetaHumanInstance*> Other);` — Copies the contents of the Other Instance into this Instance, discarding this Instance's existing contents and leaving it in an unassembled state. Used for copying edits from a temporary Instance back to the persistent Instance. Contents in this case refers to the Instance's slot selections and Instance parameters. This instance will be set to point to the Other Instance's Collection. If this is not desired you can call SetMetaHumanCollection afterwards to change it.
- L220 _public prototype_ `void SetSingleSlotSelection(FName SlotName, const FMetaHumanPaletteItemKey& ItemKey);` — `UFUNCTION(BlueprintCallable, Category = "Slots")` — Remove any existing selections for this slot and select only the given item. If ItemKey is NAME_None, no item will be selected for this slot.
- L221 _public prototype_ `void SetSingleSlotSelection(const FMetaHumanPaletteItemPath& ParentItemPath, FName SlotName, const FMetaHumanPaletteItemKey& ItemKey);`
- L225 _public prototype_ `[[nodiscard]] bool TryAddSlotSelection(const FMetaHumanPipelineSlotSelection& Selection);` — `UFUNCTION(BlueprintCallable, Category = Instance)` — Adds the provided slot selection if valid, e.g. won't allow duplicate selections or multiple selections for slots that don't allow it
- L233 _public prototype_ `[[nodiscard]] bool TryGetAnySlotSelection(FName SlotName, FMetaHumanPaletteItemKey& OutItemKey) const;` — Get a single item selection for this slot, if there is at least one. If there are multiple selections for this slot, this function returns an arbitrary selection and repeated calls may return a different selection.
- L234 _public prototype_ `[[nodiscard]] bool TryGetAnySlotSelection(const FMetaHumanPaletteItemPath& ParentItemPath, FName SlotName, FMetaHumanPaletteItemKey& OutItemKey) const;`
- L236 _public prototype_ `[[nodiscard]] static bool TryGetAnySlotSelection( TConstArrayView<FMetaHumanPipelineSlotSelectionData> SlotSelections, FName SlotName, FMetaHumanPaletteItemKey& OutItemKey);`
- L241 _public prototype_ `[[nodiscard]] static bool TryGetAnySlotSelection( TConstArrayView<FMetaHumanPipelineSlotSelectionData> SlotSelections, const FMetaHumanPaletteItemPath& ParentItemPath, FName SlotName, FMetaHumanPaletteItemKey& OutItemKey);`
- L247 _public prototype_ `[[nodiscard]] static bool TryGetAnySlotSelection( TConstArrayView<FMetaHumanPipelineSlotSelection> SlotSelections, FName SlotName, FMetaHumanPaletteItemKey& OutItemKey);`
- L252 _public prototype_ `[[nodiscard]] static bool TryGetAnySlotSelection( TConstArrayView<FMetaHumanPipelineSlotSelection> SlotSelections, const FMetaHumanPaletteItemPath& ParentItemPath, FName SlotName, FMetaHumanPaletteItemKey& OutItemKey);`
- L258 _public prototype_ `bool ContainsSlotSelection(const FMetaHumanPipelineSlotSelection& Selection) const;`
- L260 _public prototype_ `bool TryRemoveSlotSelection(const FMetaHumanPipelineSlotSelection& Selection);` — Returns true if the selection existed and was removed, false if it didn't exist
- L263 _public prototype_ `const TArray<FMetaHumanPipelineSlotSelectionData>& GetSlotSelectionData() const;` — `UFUNCTION(BlueprintCallable, Category = "Slots")`
- L269 _public prototype_ `TArray<FMetaHumanPinnedSlotSelection> ToPinnedSlotSelections(EMetaHumanUnusedSlotBehavior UnusedSlotBehavior) const;` — Formats the slot selections and overridden instance parameters stored in this instance to be passed into a Collection build as pinned selections.
- L275 _public prototype_ `TMap<FMetaHumanPaletteItemPath, FInstancedPropertyBag> GetAssemblyInstanceParameters() const;` — `UE_DEPRECATED(5.8, "There are now two types of Instance Parameters: Assembly Parameters and Post-Assembly Parameters, with corresponding functions")` — The term Instance Parameters now refers to both Assembly and Post-Assembly Parameters. In other words, Assembly and Post-Assembly Parameters are types of Instance Parameter.
- L286 _public prototype_ `TMap<FMetaHumanPaletteItemPath, FInstancedPropertyBag> GetAssemblyParameters() const;` — Returns the Assembly Parameters produced by the last build and their original values. Assembly Parameters are values that can be set at assembly time. Although they come from the build output, this function is provided here for convenience. The parameters for the empty item path are the Collection's own parameters.
- L299 _public prototype_ `TMap<FMetaHumanPaletteItemPath, FInstancedPropertyBag> GetPostAssemblyParameters() const;` — Returns the Post-Assembly Parameters produced by the last assembly and their original values. Post-Assembly Parameters are values that can be set after assembly, such as material parameters. They are strictly a subset of Assembly Parameters. In other words, every Post-Assembly Parameter is also an Assembly Parameter but not vice versa. The parameters for the empty item path are the Collection's own parameters.
- L309 _public prototype_ `TMap<FMetaHumanPaletteItemPath, FInstancedPropertyBag> GetOverriddenInstanceParameters() const;` — Returns the Instance Parameters stored in this instance as overrides. These overrides will be applied to any assembly created through this instance. They may include overrides for items and parameters that don't exist on the current assembly. These persist indefinitely until explicitly cleared.
- L318 _public prototype_ `FInstancedPropertyBag GetCurrentInstanceParametersForItem(const FMetaHumanPaletteItemPath& ItemPath) const;` — Returns the Instance Parameters produced by the last assembly and their effective values. If a parameter has an override value (from GetOverriddenInstanceParameters), it will be set to this override value. Otherwise, it will be set to the original value from the assembly (from GetAssemblyInstanceParameters).
- L330 _public prototype_ `EMetaHumanInstanceParameterOverrideResult OverrideInstanceParameters(const FMetaHumanPaletteItemPath& ItemPath, const FInstancedPropertyBag& NewInstanceParameterValues);` — Set the overridden Instance Parameter values for a given item, or the Collection itself if an empty item path is specified. Overridden values set via this function will persist indefinitely until explicitly cleared. These parameter values will be applied immediately if there's a valid assembly. If Assemble is called after this and a new assembly is created, they will automatically be applied to that assembly and any future assemblies.
- L333 _public prototype_ `void ClearAllOverriddenInstanceParameters();` — Functions to clear overridden Instance Parameters
- L334 _public prototype_ `void ClearOverriddenInstanceParameters(const FMetaHumanPaletteItemPath& ItemPath);`
- L344 _public prototype_ `bool TryUnpack(const FString& TargetFolder);` — Unpacks only the assets contained in this Instance. Does not unpack assets from the Collection that this Instance depends on. This function is intended for internal use and may change or be removed in future.
- L361 _public prototype_ `void NotifyAssemblyOutputInvalidated();` — Notify users of this Instance that they should call GetAssemblyOutput again and update themselves. This is an editor-only mechanism to handle cases such as notifying actors placed in the world that a MetaHuman Instance they reference has been modified. Editor code that modifies an Instance should call this when its edits are done. This is deliberately not automatically triggered on every edit, because edits are often grouped together and we don't want to repeatedly notify objects while the Instance is still in the process of being modified. Project code that generates transient Instances and modifies them at runtime should have its own system for notifying any objects that need to know.
- L363 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L364 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L368 _public prototype_ `virtual void PostLoad() override;` — UObject interface
- L371 _public member_ `mutable FMetaHumanInstanceUpdatedNative OnInstanceUpdatedNative;` — `UE_DEPRECATED(5.8, "This delegate is not robust and will be removed")`
- L376 _private prototype_ `void RemoveStaleOverriddenInstanceParameters();` — Removes entries from OverriddenInstanceParameters whose keys don't resolve to items in the Collection
- L385 _private prototype_ `EMetaHumanInstanceCookBehavior ResolveShouldCookAsAssembled() const;` — Resolves ShouldCookAsAssembled to a concrete Yes/No, consulting the Collection's editor pipeline if the value is PipelineDefault. Returns the unresolved value (which may still be PipelineDefault) if the editor pipeline isn't reachable.
- L388 _private prototype_ `void RefreshWillCookAsAssembled();` — Updates WillCookAsAssembled based on the current ShouldCookAsAssembled value.
- L396 _private prototype_ `void MarkAssemblyOutputSubobjectsAsTransient();` — Walks references from the editor assembly output and marks all reached subobjects of this Instance as RF_Transient, so they don't get saved into the package. Called on a successful Assemble in the editor (skipped during cook commandlet).
- L406 _private prototype_ `void MoveAssemblyOutputSubobjectsToTransientPackage();` — Walks references from the editor assembly output, marks reached subobjects of this Instance as RF_Transient and renames them into the transient package with auto-generated names. Used to fully detach the previous assembly's subobjects so a new assembly is free to reuse their names. Called from ClearAssemblyOutput in the editor (skipped during cook commandlet).
- L415 _private prototype_ `void ValidateAndSanitizeSlotSelections(bool bShouldRemoveMissingItemSelections);` — Validate this Instance's slot selections and correct any invalid data. If bShouldRemoveMissingItemSelections is true, selections that reference missing items will be removed.
- L418 _private prototype_ `EMetaHumanInstanceParameterOverrideResult ApplyOverriddenInstanceParameters(const FMetaHumanPaletteItemPath& ItemPath) const;` — Legacy function to support item pipelines still using the deprecated Instance Parameters
- L424 _private prototype_ `const FMetaHumanProcessedAssemblyOutput& GetActiveAssemblyOutput() const;` — Returns a reference to the active assembly output, either EditorAssemblyOutput or RuntimeAssemblyOutput depending on the context.
- L425 _private prototype_ `FMetaHumanProcessedAssemblyOutput& GetActiveAssemblyOutput();`
- L433 _private prototype_ `bool CanModifyInstance(const TCHAR* DebugOperationName) const;` — Returns true if any edit operations are permitted on the Instance. DebugOperationName should be set to the name of the operation the caller wants to perform, to be used in debug logging if the edit is denied.
- L445 _private member_ `FMetaHumanProcessedAssemblyOutput EditorAssemblyOutput;` — `UPROPERTY(Transient, DuplicateTransient)` — The assembly output and associated data for this Instance while it's being edited in the editor. Transient so that it's always freshly recreated on load and there's no chance of stale references being kept to the Collection's built data, or of other assets saving references to this assembly output into their packages.
- L457 _private member_ `FMetaHumanProcessedAssemblyOutput RuntimeAssemblyOutput;` — `UPROPERTY(DuplicateTransient)` — The assembly output and associated data for this Instance in cooked builds. Should be unpopulated in editor. If bIsAssemblyOutputCooked is true, this data was created during cook and the Instance can't be modified or re-assembled at runtime.
- L464 _private member_ `bool bIsAssemblyOutputCooked = false;` — `UPROPERTY(Transient, DuplicateTransient)` — True if this Instance was loaded from a cooked package and has a valid baked RuntimeAssemblyOutput. When true, edits and re-assembly are not permitted.
- L471 _private member_ `EMetaHumanInstanceCookBehavior ShouldCookAsAssembled = EMetaHumanInstanceCookBehavior::PipelineDefault;` — `UPROPERTY(EditAnywhere, Category = Instance)` — Determines whether this Instance should be assembled at cook time and have its assembly output baked into the cooked package.
- L481 _private member_ `EMetaHumanInstanceCookBehavior WillCookAsAssembled = EMetaHumanInstanceCookBehavior::PipelineDefault;` — `UPROPERTY(VisibleAnywhere, Transient, Category = Instance)` — The effective resolved value of ShouldCookAsAssembled. The purpose of this property is purely to display in the editor UI what the cook behavior will be. It has no effect on any logic.
- L486 _private member_ `FMetaHumanInstanceParameterCollection CurrentOverriddenAssemblyParameters;` — `UPROPERTY(Transient, DuplicateTransient)` — Used by the assembly that's currently in progress
- L489 _private member_ `TMap<FMetaHumanPaletteItemPath, FInstancedPropertyBag> OverriddenInstanceParameters;` — `UPROPERTY()`
- L496 _private member_ `FInstancedPropertyBag OverriddenCollectionInstanceParameters;` — `UPROPERTY()` — OverriddenInstanceParameters for the Collection pipeline itself, so that we can detect when a key in OverriddenInstanceParameters has been reset to the empty path due to a missing asset.
- L508 _private member_ `TArray<FMetaHumanPipelineSlotSelectionData> SlotSelections;` — `UPROPERTY()` — The selected items for slots on the Pipeline. Slots with no selection will select the default item for the slot. Some slots allow multiple selections. This is determined by the UMetaHumanCharacterPipelineSpecification. The order of items in this array has no significance. Consider it an unordered set.
- L511 _private member_ `TObjectPtr<UMetaHumanCollection> Collection;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L122 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FMetaHumanCharacterAssembled, EMetaHumanCharacterAssemblyResult, Result);`
- L122 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FMetaHumanCharacterAssembled, EMetaHumanCharacterAssemblyResult, Result);`
- L123 _delegate_ `DECLARE_DELEGATE_OneParam(FMetaHumanCharacterAssembledNative, EMetaHumanCharacterAssemblyResult );`
- L123 _prototype_ `DECLARE_DELEGATE_OneParam(FMetaHumanCharacterAssembledNative, EMetaHumanCharacterAssemblyResult );`
- L125 _delegate_ `DECLARE_MULTICAST_DELEGATE(FMetaHumanInstanceUpdatedNative);`
- L125 _prototype_ `DECLARE_MULTICAST_DELEGATE(FMetaHumanInstanceUpdatedNative);`
- L514 _typedef_ `using UMetaHumanCharacterInstance UE_DEPRECATED(5.8, "UMetaHumanCharacterInsta`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanInstanceParameterCollection.h` (Public)


#### struct `FMetaHumanInstanceParameterCollectionPair`  
`struct FMetaHumanInstanceParameterCollectionPair`  
_L18-28_
- reflection: `USTRUCT()`
- L24 _public member_ `FMetaHumanPaletteItemPath Key;` — `UPROPERTY()`
- L27 _public member_ `FInstancedPropertyBag Value;` — `UPROPERTY()`

#### struct `FMetaHumanInstanceParameterCollection`  
`struct FMetaHumanInstanceParameterCollection`  
_L31-45_
- reflection: `USTRUCT()`
- L36 _public prototype_ `FMetaHumanInstanceParameterCollectionEditor Edit();`
- L37 _public prototype_ `FMetaHumanInstanceParameterCollectionView View() const;`
- L39 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L44 _private member_ `TArray<FMetaHumanInstanceParameterCollectionPair> SortedElements;` — `UPROPERTY()` — Sorted by ItemPath

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMetaHumanInstanceParameterCollection> : public TStructOpsTypeTraitsBase2<FMetaHumanInstanceParameterCollection>`  
_L48-54_
- inherits: `TStructOpsTypeTraitsBase2<FMetaHumanInstanceParameterCollection>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L51-53_

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`
- L14 _typedef_ `using FMetaHumanInstanceParameterCollectionEditor = UE::MetaHuman::TMetaHumanItemPathMapEditor<FMetaHumanInstanceParameterCollectionPair, FInstancedPropertyBag>;`
- L15 _typedef_ `using FMetaHumanInstanceParameterCollectionView = UE::MetaHuman::TMetaHumanItemPathMapView<FMetaHumanInstanceParameterCollectionPair, FInstancedPropertyBag>;`
- L52 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon14c22c230103`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanItemEditorPipeline.h` (Public)


#### class `UMetaHumanItemEditorPipeline`  
`class UMetaHumanItemEditorPipeline : public UMetaHumanCharacterEditorPipeline`  
_L26-114_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UMetaHumanCharacterEditorPipeline`
- desc: The editor-only component of a UMetaHumanItemPipeline.
- L32 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnBuildComplete, FMetaHumanPaletteBuiltData&& );`
- L62 _public prototype_ `virtual UE::Tasks::TTask<FMetaHumanPaletteBuiltData> BuildItem(const FBuildItemParams& Params) const PURE_VIRTUAL(UMetaHumanItemEditorPipeline::BuildItem, return {};);`
- L66 _public prototype_ `void BuildItem( const FMetaHumanPaletteItemPath& ItemPath, TNotNull<const UMetaHumanWardrobeItem*> WardrobeItem, const FInstancedStruct& BuildInput, TConstArrayView<FMetaHumanPinnedSlotSelection> SortedPinnedSlotSelections, TConstArrayView<FMetaHumanPaletteItemPath> SortedItemsToExclude, FMetaHumanPaletteBuildCacheEntry& BuildCache, EMetaHumanCharacterPaletteBuildQuality Quality, ITargetPlatform* TargetPlatform, TNotNull<UObject*> OuterForGeneratedObjects, const FOnBuildComplete& OnComplete) const;` — `UE_DEPRECATED(5.8, "TargetPlatform is no longer used at build time. Use the new BuildItem overload.")`
- L78 _public prototype_ `virtual void BuildItemSynchronous(const FBuildItemParams& Params, FMetaHumanPaletteBuiltData& OutBuiltData) const;`
- L81 _public prototype_ `void BuildItemSynchronous( const FMetaHumanPaletteItemPath& ItemPath, TNotNull<const UMetaHumanWardrobeItem*> WardrobeItem, const FInstancedStruct& BuildInput, TConstArrayView<FMetaHumanPinnedSlotSelection> SortedPinnedSlotSelections, TConstArrayView<FMetaHumanPaletteItemPath> SortedItemsToExclude, FMetaHumanPaletteBuildCacheEntry& BuildCache, EMetaHumanCharacterPaletteBuildQuality Quality, ITargetPlatform* TargetPlatform, TNotNull<UObject*> OuterForGeneratedObjects, FMetaHumanPaletteBuiltData& OutBuiltData) const;` — `UE_DEPRECATED(5.8, "TargetPlatform is no longer used at build time. Use the new BuildItemSynchronous overload.")`
- L101 _public prototype_ `virtual bool TryUnpackItemAssets( TNotNull<const UMetaHumanWardrobeItem*> WardrobeItem, const FMetaHumanPaletteItemPath& BaseItemPath, FMetaHumanPipelineBuiltDataCollectionMutableView ItemBuiltData, const FString& UnpackFolder, const FTryUnpackObjectDelegate& TryUnpackObjectDelegate) const;` — Unpacks the assets contained in the built data for this item and any sub-items. Calls the provided TryUnpackObjectDelegate to do the actual unpacking. This base implementation should be good enough for most pipelines, but there is the option to override it if any assets need special handling.
- L109 _public prototype_ `virtual TNotNull<const UMetaHumanItemPipeline*> GetRuntimePipeline() const;` — Returns the runtime pipeline instance corresponding to this editor pipeline instance.
- L112 _public prototype_ `virtual TNotNull<const UMetaHumanCharacterPipeline*> GetRuntimeCharacterPipeline() const override;` — Calls GetRuntimePipeline. No need for subclasses to implement this.

#### struct `UMetaHumanItemEditorPipeline::FBuildItemParams`  
`struct FBuildItemParams`  
_L50-60_
- desc: Builds the item based on input from the hosting Collection pipeline. For example, the build input could be a body mesh that this item pipeline should fit clothing to. Can only be called from a Collection or Item pipeline. Items can't be built by themselves, they need to be hosted by a Collection. SortedPinnedSlotSelections will be filtered to only include this item and its sub-items. If this item is pinned, it will be in SortedPinnedSlotSelections. SortedItemsToExclude will be filtered to only include sub-items of this item. If this item is excluded, BuildItem won't be called at all, so there is no need to search SortedItemsToExclude for this item.
- L52 _public member_ `FMetaHumanPaletteItemPath ItemPath;`
- L53 _public member_ `TNotNull<const UMetaHumanWardrobeItem*> WardrobeItem;`
- L54 _public member_ `EMetaHumanCharacterPaletteBuildQuality Quality = EMetaHumanCharacterPaletteBuildQuality::Production;`
- L55 _public member_ `TNotNull<UObject*> OuterForGeneratedObjects;`
- L56 _public member_ `FInstancedStruct BuildInput;`
- L57 _public member_ `TConstArrayView<FMetaHumanPinnedSlotSelection> SortedPinnedSlotSelections;`
- L58 _public member_ `TConstArrayView<FMetaHumanPaletteItemPath> SortedItemsToExclude;`
- L59 _public member_ `FGuid BuildCacheGuid;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`
- L32 _delegate_ `DECLARE_DELEGATE_OneParam(FOnBuildComplete, FMetaHumanPaletteBuiltData&& );`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanItemPathMap.h` (Public)


#### class `UE::MetaHuman::TMetaHumanItemPathMapView`  
`template<typename PairType, typename ValueType> class TMetaHumanItemPathMapView`  
_L21-118_
- L24 _public prototype_ `TMetaHumanItemPathMapView() = default;`
- L26 _public function_ `TMetaHumanItemPathMapView(TConstArrayView<PairType> InSortedElements) : SortedElements(InSortedElements)`
- L31 _public function_ `int32 IndexOf(const FMetaHumanPaletteItemPath& ItemPath) const`
- L36 _public function_ `int32 IndexOfChecked(const FMetaHumanPaletteItemPath& ItemPath) const`
- L44 _public function_ `bool Contains(const FMetaHumanPaletteItemPath& ItemPath) const`
- L49 _public function_ `const ValueType* Find(const FMetaHumanPaletteItemPath& ItemPath) const`
- L60 _public function_ `const ValueType& operator[](const FMetaHumanPaletteItemPath& Key) const`
- L67 _public function_ `TMetaHumanItemPathMapView<PairType, ValueType> FilterByBasePath(const FMetaHumanPaletteItemPath& BasePath) const`
- L80 _public function_ `bool TryFindRangeForBasePath( const FMetaHumanPaletteItemPath& BasePath, int32& OutStartIndex, int32& OutCount) const`
- L117 _public member_ `TConstArrayView<PairType> SortedElements;`

#### class `UE::MetaHuman::TMetaHumanItemPathMapMutableView`  
`template<typename PairType, typename ValueType> class TMetaHumanItemPathMapMutableView : public TMetaHumanItemPathMapView<PairType, ValueType>`  
_L121-166_
- inherits: `TMetaHumanItemPathMapView<PairType,ValueType>`
- L124 _public typedef_ `using Super = TMetaHumanItemPathMapView<PairType, ValueType>;`
- L126 _public prototype_ `TMetaHumanItemPathMapMutableView() = default;`
- L128 _public function_ `TMetaHumanItemPathMapMutableView(TArrayView<PairType> InSortedElements) : Super(InSortedElements) , MutableSortedElements(InSortedElements)`
- L134 _public function_ `ValueType* Find(const FMetaHumanPaletteItemPath& ItemPath)`
- L145 _public function_ `ValueType& operator[](const FMetaHumanPaletteItemPath& Key)`
- L152 _public function_ `TMetaHumanItemPathMapMutableView<PairType, ValueType> FilterByBasePath(const FMetaHumanPaletteItemPath& BasePath)`
- L165 _public member_ `TArrayView<PairType> MutableSortedElements;`

#### class `UE::MetaHuman::TMetaHumanItemPathMapEditor`  
`template<typename PairType, typename ValueType> class TMetaHumanItemPathMapEditor`  
_L169-316_
- L172 _public function_ `TMetaHumanItemPathMapEditor(TArray<PairType>& InSortedElements) : SortedElements(InSortedElements)`
- L177 _public function_ `ValueType& Add(const FMetaHumanPaletteItemPath& ItemPath, ValueType&& Value)`
- L194 _public function_ `ValueType& Add(const FMetaHumanPaletteItemPath& ItemPath, const ValueType& Value = ValueType())`
- L200 _public function_ `ValueType& FindOrAdd(const FMetaHumanPaletteItemPath& ItemPath)`
- L211 _public function_ `void Append(TMetaHumanItemPathMapEditor<PairType, ValueType>&& SourceEditor)`
- L254 _public function_ `void RemoveSingleItem(const FMetaHumanPaletteItemPath& ItemPath)`
- L266 _public function_ `void RemoveItemsByBasePath(const FMetaHumanPaletteItemPath& BasePath)`
- L276 _public function_ `void Empty(int32 Slack = 0)`
- L281 _public function_ `void PostSerialize(const FArchive& Ar)`
- L296 _public function_ `TMetaHumanItemPathMapView<PairType, ValueType> View() const`
- L302 _private function_ `bool IsSorted() const`
- L315 _private member_ `TArray<PairType>& SortedElements;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MetaHuman` (scope `UE`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanItemPipeline.h` (Public)


#### class `UMetaHumanItemPipeline`  
`class UMetaHumanItemPipeline : public UMetaHumanCharacterPipeline`  
_L19-141_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UMetaHumanCharacterPipeline`
- desc: The Wardrobe Item-specific subclass of Character Pipeline
- L25 _public prototype_ `virtual const UMetaHumanItemEditorPipeline* GetEditorPipeline() const PURE_VIRTUAL(UMetaHumanItemPipeline::GetEditorPipeline,return nullptr;);`
- L33 _public prototype_ `virtual UMetaHumanItemEditorPipeline* GetMutableEditorPipeline();` — Mutable accessor for the editor pipeline. The default implementation calls GetEditorPipeline and removes const from the result.
- L56 _public prototype_ `virtual void AssembleItem(const FAssembleItemParams& Params, const FOnAssemblyComplete& OnComplete) const PURE_VIRTUAL(UMetaHumanItemPipeline::AssembleItem,);`
- L59 _public prototype_ `void AssembleItemSynchronous(const FAssembleItemParams& Params, FMetaHumanAssemblyOutput& OutAssemblyOutput) const;`
- L62 _public prototype_ `void AssembleItem( const FMetaHumanPaletteItemPath& BaseItemPath, const TArray<FMetaHumanPipelineSlotSelectionData>& SlotSelections, const FMetaHumanPaletteBuiltData& ItemBuiltData, const FInstancedStruct& AssemblyInput, TNotNull<UObject*> OuterForGeneratedObjects, const FOnAssemblyComplete& OnComplete) const;` — `UE_DEPRECATED(5.8, "This overload of AssembleItem is deprecated")`
- L71 _public prototype_ `void AssembleItemSynchronous( const FMetaHumanPaletteItemPath& BaseItemPath, const TArray<FMetaHumanPipelineSlotSelectionData>& SlotSelections, const FMetaHumanPaletteBuiltData& ItemBuiltData, const FInstancedStruct& AssemblyInput, TNotNull<UObject*> OuterForGeneratedObjects, FMetaHumanAssemblyOutput& OutAssemblyOutput) const;` — `UE_DEPRECATED(5.8, "This overload of AssembleItemSynchronous is deprecated")`
- L118 _public prototype_ `virtual void SetPostAssemblyParameters(const FSetPostAssemblyParametersParams& Params, FInstancedStruct& InOutItemAssemblyOutput) const;`
- L136 _public prototype_ `virtual bool AreSlotSelectionsAllowed( const FMetaHumanPaletteItemPath& BaseItemPath, TArrayView<const FMetaHumanPipelineSlotSelection> SlotSelections, const FMetaHumanPaletteBuiltData& ItemBuiltData, FText& OutDisallowedReason) const;` — Returns true if the given slot selections are a permitted combination. This allows the pipeline to restrict Instances to selecting items that are compatible with each other using any arbitary logic. As with AssembleItem, SlotSelections and ItemBuiltData will only contain entries relating to this item and its sub-items. If AreSlotSelectionsAllowed returns false, the text assigned to OutDisallowedReason may be shown to the user to explain why this combination is not allowed. The order of elements in SlotSelections must not affect the return value of this function. It may affect OutDisallowedReason, for example if there are multiple reasons why the selection is not allowed.

#### struct `UMetaHumanItemPipeline::FAssembleItemParams`  
`struct FAssembleItemParams`  
_L45-54_
- desc: Assembles the item using the build output that was generated by the corresponding editor pipeline. Can only be called from a Collection pipeline. Items can't be assembled without a Collection. ItemBuiltData is a filtered view of the built data that only allows access to data belonging to this item and its sub-items.
- L47 _public member_ `FMetaHumanPaletteItemPath BaseItemPath;`
- L48 _public member_ `TNotNull<UObject*> OuterForGeneratedObjects;`
- L49 _public member_ `FMetaHumanPipelineBuiltDataCollectionView ItemBuiltData;`
- L50 _public member_ `EMetaHumanCharacterPaletteBuildQuality Quality = EMetaHumanCharacterPaletteBuildQuality::Production;`
- L51 _public member_ `TConstArrayView<FMetaHumanPipelineSlotSelectionData> SortedSlotSelections;`
- L52 _public member_ `FInstancedStruct AssemblyInput;`
- L53 _public member_ `FMetaHumanInstanceParameterCollectionView AssemblyParameters;`

#### struct `UMetaHumanItemPipeline::FSetPostAssemblyParametersParams`  
`struct FSetPostAssemblyParametersParams`  
_L108-116_
- desc: Item version of UMetaHumanCollectionPipeline::SetPostAssemblyParameters. See comments there for more information. Should only be called from SetPostAssemblyParameters on the collection pipeline or the owning item's pipeline. Note that the InOutItemAssemblyOutput is *not* guaranteed to be identical to the assembly output produced by AssembleItem. For example, if the assembly output from this item included a mesh and a set of materials, and the owning collection pipeline has merged that mesh with other meshes during assembly, and then the user wants to set a Post-Assembly Parameter that would affect a material parameter: a) 	The original mesh may no longer exist (e.g. if it was generated by this pipeline during assembly and discarded), so it may not be feasible to pass it in here, and b) 	The mesh is not actually needed to set a material parameter, so it doesn't make sense to require it. The item pipeline's requirements for setting a specific Post-Assembly Parameter are part of its API and it's the caller's responsibility to manage this. In simple "passthrough" cases, where the item pipeline's assembly output is passed through to the collection pipeline's assembly output without being modified, the collection pipeline can easily provide the item's original assembly output to this function. It's only when the collection pipeline modifies the item's assembly output in some way that this API becomes important and the collection pipeline must accept the maintenance burden for that.
- L110 _public member_ `EMetaHumanCharacterPaletteBuildQuality Quality = EMetaHumanCharacterPaletteBuildQuality::Production;`
- L111 _public member_ `FMetaHumanPaletteItemPath BaseItemPath;`
- L112 _public member_ `FMetaHumanPipelineBuiltDataCollectionView ItemBuiltData;`
- L113 _public member_ `FMetaHumanPostAssemblyParameterOutputCollectionView AllPostAssemblyParameters;`
- L114 _public member_ `FMetaHumanPaletteItemPath TargetItemPath;`
- L115 _public member_ `const FInstancedPropertyBag& ModifiedPostAssemblyParameters;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanPaletteItemKey.h` (Public)


#### struct `FMetaHumanPaletteItemKey`  
`struct FMetaHumanPaletteItemKey`  
_L15-99_
- reflection: `USTRUCT(BlueprintType)`
- desc: Uniquely identifies an item in a UMetaHumanCharacterPalette
- L20 _public prototype_ `FMetaHumanPaletteItemKey();`
- L21 _public prototype_ `~FMetaHumanPaletteItemKey();`
- L22 _public prototype_ `FMetaHumanPaletteItemKey(const FMetaHumanPaletteItemKey&);`
- L23 _public prototype_ `FMetaHumanPaletteItemKey(FMetaHumanPaletteItemKey&&);`
- L24 _public prototype_ `FMetaHumanPaletteItemKey& operator=(const FMetaHumanPaletteItemKey&);`
- L25 _public prototype_ `FMetaHumanPaletteItemKey& operator=(FMetaHumanPaletteItemKey&&);`
- L27 _public prototype_ `static FMetaHumanPaletteItemKey FromPrincipalAsset(const TSoftObjectPtr<UObject>& InPrincipalAsset, const FName& InVariation);`
- L28 _public prototype_ `static FMetaHumanPaletteItemKey FromExternalWardrobeItem(const TSoftObjectPtr<UMetaHumanWardrobeItem>& InExternalWardrobeItem, const FName& InVariation);`
- L31 _public prototype_ `bool ReferencesExternalWardrobeItem() const;` — Returns true if the Wardrobe Item referenced by this palette item is a self-contained asset
- L39 _public prototype_ `[[nodiscard]] bool TryGetPrincipalAsset(FEditorOnlyAssetReference& OutPrincipalAsset) const;` — If this item references a Principal Asset *directly*, this function succeeds and returns it via the given argument. Otherwise, it will fail and return nothing.
- L47 _public prototype_ `[[nodiscard]] bool TryGetExternalWardrobeItem(FEditorOnlyAssetReference& OutWardrobeItem) const;` — If this item references an external Wardrobe Item, this function succeeds and returns it via the given argument. Otherwise, it will fail and return nothing.
- L50 _public prototype_ `bool ReferencesSameAsset(const FMetaHumanPaletteItemKey& Other) const;` — Returns true if the other key is identical to this one except for Variation
- L59 _public prototype_ `bool IsNull() const;` — Returns false if this key *could* represent an item. This does not guarantee that the item exists in any Palette. If this returns true, this key represents the null item and can be used to specify that a slot should not have any item selected, for example.
- L62 _public prototype_ `void Reset();` — Resets the key to the null state
- L70 _public prototype_ `FString ToAssetNameString() const;` — Produces a string suitable for using as part of an asset name Not guaranteed to be unique within the owning Palette, e.g. if you call this on every item in the Palette, it may return the same string for multiple items.
- L73 _public prototype_ `FString ToDebugString() const;` — Produces a string with the contents of this key, suitable for log messages, etc
- L91 _public member_ `FName Variation;` — `UPROPERTY(VisibleAnywhere, Category = "Pipeline")` — A name used to disambiguate items that reference the same asset or wardrobe item. This is expected to be NAME_None in most cases.
- L95 _private member_ `FEditorOnlyAssetReference PrincipalAssetOrExternalWardrobeItem;` — `UPROPERTY(VisibleAnywhere, Category = "Pipeline", meta = (ShowOnlyInnerProperties))`
- L98 _private member_ `bool bReferencesExternalWardrobeItem = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pipeline", meta = (AllowPrivateAccess))`

#### Free symbols / members of external scopes

- L75 _function_ `friend uint32 GetTypeHash(const FMetaHumanPaletteItemKey& ItemKey)`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanPaletteItemPath.h` (Public)


#### struct `FMetaHumanPaletteItemPath`  
`struct FMetaHumanPaletteItemPath`  
_L19-105_
- reflection: `USTRUCT(BlueprintType, meta = (HasNativeMake="/Script/MetaHumanCharacterPalette.MetaHumanPaletteItemPathBlueprintLibrary.MakeItemPath"))`
- desc: Represents the path to a Wardrobe Item within a Collection. Items can contain other items, and a FMetaHumanPaletteItemKey is only unique within the Collection or Wardrobe Item it belongs to, so to address a unique item takes a sequence of FMetaHumanPaletteItemKeys: one for each level of nesting.
- L24 _public prototype_ `FMetaHumanPaletteItemPath();`
- L25 _public prototype_ `~FMetaHumanPaletteItemPath();`
- L26 _public prototype_ `FMetaHumanPaletteItemPath(const FMetaHumanPaletteItemPath&);`
- L27 _public prototype_ `FMetaHumanPaletteItemPath(FMetaHumanPaletteItemPath&&);`
- L28 _public prototype_ `FMetaHumanPaletteItemPath& operator=(const FMetaHumanPaletteItemPath&);`
- L29 _public prototype_ `FMetaHumanPaletteItemPath& operator=(FMetaHumanPaletteItemPath&&);`
- L30 _public prototype_ `explicit FMetaHumanPaletteItemPath(const FMetaHumanPaletteItemKey& InItem);`
- L31 _public prototype_ `FMetaHumanPaletteItemPath(const TArray<FMetaHumanPaletteItemKey>& InParentItems, const FMetaHumanPaletteItemKey& InItem);`
- L32 _public prototype_ `FMetaHumanPaletteItemPath(const FMetaHumanPaletteItemPath& InParentItemPath, const FMetaHumanPaletteItemKey& InItem);`
- L41 _public member_ `static const FMetaHumanPaletteItemPath Collection;` — In many contexts, the empty item path represents the path to the containing Collection itself. This constant contains the empty path to help make it explicit that a caller is referencing the Collection, as opposed to using a default-constructed path.
- L43 _public prototype_ `bool IsEmpty() const;`
- L45 _public prototype_ `int32 GetNumPathEntries() const;`
- L48 _public prototype_ `FMetaHumanPaletteItemKey GetPathEntry(int32 Index) const;` — Index must be in the range 0 .. GetNumPathEntries() - 1, otherwise an assertion will fail.
- L56 _public prototype_ `bool IsDirectChildPathOf(const FMetaHumanPaletteItemPath& ParentPath) const;` — Compares this path to the given path and returns true if this path contains exactly one more entry, and the other entries exactly match the given path. For example, using filesystem syntax "/A/B/C".IsDirectChildPathOf("/A/B") would return true.
- L68 _public prototype_ `bool IsEqualOrChildPathOf(const FMetaHumanPaletteItemPath& ParentPath) const;` — Returns true if this path is equal to the other path, or is a child path of it. This is useful when filtering a list of item paths to include only paths that relate to a particular item and its sub-items. For example, given a list of item paths, if the expression X.IsEqualOrChildPathOf(ItemToFilter) returns true for a path X from the list, it's either ItemToFilter itself or one of its sub-items (or sub-sub-items, etc).
- L70 _public prototype_ `void Append(const FMetaHumanPaletteItemPath& PathToAppend);`
- L72 _public prototype_ `FString ToDebugString() const;`
- L79 _public prototype_ `int32 Compare(const FMetaHumanPaletteItemPath& Other) const;` — Compare this path with the other path to determine their sort order. Returns -1 if this path is "less" than the other, 1 if it's "more", and 0 if they're equal.
- L100 _private member_ `TArray<FMetaHumanPaletteItemKey> ParentItems;` — `UPROPERTY(VisibleAnywhere, Category = "Character")` — The sequence of parent items to reach the actual item referenced by this path. For the simple case where this path references a Wardrobe Item that is directly contained in a Collection, with no item nesting, this array will be empty.
- L104 _private member_ `FMetaHumanPaletteItemKey Item;` — `UPROPERTY(VisibleAnywhere, Category = "Character")` — The last item in the path

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanParameterMappingTable.h` (Public)


#### enum `EMetaHumanParameterMappingInputSourceType`  
`enum class EMetaHumanParameterMappingInputSourceType : uint8`  
_L14-20_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Parameter`
- L17 _public enumerator_ `Scalability`
- L18 _public enumerator_ `ConsoleVariable`
- L19 _public enumerator_ `Platform`

#### struct `FMetaHumanParameterMappingInput`  
`struct FMetaHumanParameterMappingInput`  
_L23-41_
- reflection: `USTRUCT()`
- L28 _public member_ `EMetaHumanParameterMappingInputSourceType Type = EMetaHumanParameterMappingInputSourceType::Parameter;` — `UPROPERTY()`
- L31 _public member_ `FName Name;` — `UPROPERTY()`
- L34 _public member_ `FName NameValue;` — `UPROPERTY()`
- L37 _public member_ `float FloatValue = 0.0f;` — `UPROPERTY()`
- L40 _public member_ `bool bBoolValue = false;` — `UPROPERTY()`

#### enum `EMetaHumanParameterValueType`  
`enum class EMetaHumanParameterValueType : uint8`  
_L44-53_
- reflection: `UENUM()`
- L47 _public enumerator_ `Invalid` — TODO: Do we want to have an invalid value here? Or just allow a null Texture to be the invalid value?
- L48 _public enumerator_ `Texture`
- L49 _public enumerator_ `Name`
- L50 _public enumerator_ `Color`
- L51 _public enumerator_ `Float`
- L52 _public enumerator_ `Bool`

#### struct `FMetaHumanParameterValue`  
`struct FMetaHumanParameterValue`  
_L57-82_
- reflection: `USTRUCT(BlueprintType)`
- desc: TODO: Is there a neater way of doing this using existing engine functionality?
- L62 _public member_ `TSoftObjectPtr<UTexture2D> TextureValue;` — `UPROPERTY()`
- L65 _public member_ `FName NameValue;` — `UPROPERTY()`
- L68 _public member_ `FLinearColor ColorValue = FLinearColor(ForceInit);` — `UPROPERTY()`
- L71 _public member_ `float FloatValue = 0.0f;` — `UPROPERTY()`
- L74 _public member_ `bool bBoolValue = false;` — `UPROPERTY()`
- L77 _public member_ `EMetaHumanParameterValueType Type = EMetaHumanParameterValueType::Invalid;` — `UPROPERTY()`
- L79 _public prototype_ `bool operator==(const FMetaHumanParameterValue& Other) const;`
- L81 _public prototype_ `bool Matches(const FMetaHumanParameterMappingInput& MappingInput) const;`

#### struct `FMetaHumanParameterMappingRow`  
`struct FMetaHumanParameterMappingRow`  
_L85-94_
- reflection: `USTRUCT()`
- L90 _public member_ `TArray<FMetaHumanParameterMappingInput> InputParameters;` — `UPROPERTY()`
- L93 _public member_ `FMetaHumanParameterValue Value;` — `UPROPERTY()`

#### struct `FMetaHumanParameterMapping`  
`struct FMetaHumanParameterMapping`  
_L97-106_
- reflection: `USTRUCT()`
- L102 _public member_ `FName ParameterName;` — `UPROPERTY()`
- L105 _public member_ `TArray<FMetaHumanParameterMappingRow> Rows;` — `UPROPERTY()`

#### struct `FMetaHumanParameterMappingInputColumnSet`  
`struct FMetaHumanParameterMappingInputColumnSet`  
_L110-122_
- reflection: `USTRUCT()`
- L115 _public member_ `FName TypeColumn;` — `UPROPERTY(EditAnywhere, Category = ParameterMapping)`
- L118 _public member_ `FName NameColumn;` — `UPROPERTY(EditAnywhere, Category = ParameterMapping)`
- L121 _public member_ `TArray<FName> ValueColumns;` — `UPROPERTY(EditAnywhere, Category = ParameterMapping)`

#### struct `FMetaHumanParameterMappingOutputColumnSet`  
`struct FMetaHumanParameterMappingOutputColumnSet`  
_L125-134_
- reflection: `USTRUCT()`
- L130 _public member_ `FName NameColumn;` — `UPROPERTY(EditAnywhere, Category = ParameterMapping)`
- L133 _public member_ `TArray<FName> ValueColumns;` — `UPROPERTY(EditAnywhere, Category = ParameterMapping)`

#### struct `FMetaHumanScalabilityValueSet`  
`struct FMetaHumanScalabilityValueSet`  
_L141-147_
- reflection: `USTRUCT()`
- desc: When a TMap is marked as a UPROPERTY, its value can't be a TArray, but it can be a struct containing a TArray, so that's the purpose of this struct.
- L146 _public member_ `TArray<int32> Values;` — `UPROPERTY()`

#### struct `FMetaHumanCompiledParameterMappingTable`  
`struct FMetaHumanCompiledParameterMappingTable`  
_L154-199_
- reflection: `USTRUCT()`
- desc: An optimized form of the table that is faster to evaluate and doesn't contain rows that would be unreachable given the target platform and constant parameters.
- L158 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOutputParameterDelegate, FName , const FMetaHumanParameterValue& );`
- L160 _public prototype_ `FMetaHumanCompiledParameterMappingTable( TArray<FMetaHumanParameterMapping>&& InMappings, TMap<FName, FMetaHumanScalabilityValueSet>&& InReachableScalabilityValues);`
- L164 _public prototype_ `FMetaHumanCompiledParameterMappingTable() = default;`
- L173 _public prototype_ `void Evaluate( const TMap<FName, FMetaHumanParameterValue>& TableInputParameters, const TArray<FMetaHumanParameterMappingInput>& ConsoleVariableOverrides, const FOutputParameterDelegate& OutputParameterDelegate) const;` — Evaluates the table using the given parameters as well as the current values of any cvars referenced. OutputParameterDelegate will be called for each parameter set by the table. It's valid to evaluate a default-constructed table. It will simply not call OutputParameterDelegate.
- L180 _private member_ `TArray<FMetaHumanParameterMapping> Mappings;` — `UPROPERTY()`
- L194 _private member_ `TMap<FName, FMetaHumanScalabilityValueSet> ReachableScalabilityValues;` — `UPROPERTY()` — The list of values that the mapping table compiler has determined to be reachable on this target platform for the given scalability console variables. The compiler makes assumptions based on this range of values, and so if the current value for a scalability variable is outside of the expected range, the table evaluation may produce invalid results. Therefore, the range of expected values is saved alongside the compiled table, so that we can detect when a variable is outside the expected range and fail the evaluation gracefully.
- L198 _private member_ `FName TargetPlatformName;` — `UPROPERTY()` — The name of the target platform that was passed in when this table was compiled, if any

#### struct `FMetaHumanParameterMappingTable`  
`struct FMetaHumanParameterMappingTable`  
_L210-255_
- reflection: `USTRUCT()`
- desc: A table for mapping high level parameters and other data sources, such as scalability variables, to low level parameter values. For example, a high level "Character Quality" parameter with values such as High, Medium and Low could control several low level parameter values, such as "Texture Size", "Minimum Mesh LOD" and so on.
- L229 _public prototype_ `bool TryCompile( const TMap<FName, FMetaHumanParameterValue>& ConstantParameters, const ITargetPlatform* TargetPlatform, FMetaHumanCompiledParameterMappingTable& OutCompiledTable, TMap<FName, TArray<FMetaHumanParameterValue>>& OutPossibleParameterValues) const;` — Compiles the table into a format that is faster to evaluate. The parameters in ConstantParameters will be locked to constants in the compiled table. If passed in as parameters at evaluation time, they will be ignored. Any Scalability cvars used as input will be locked to the reachable range for the target platform based on the scalability and device profile inis. Any unreachable rows, e.g. rows that would only be activated on other platforms, will be omitted from the compiled data. TargetPlatform may be null, in which case the compiled data will be usable on any platform.
- L242 _public prototype_ `bool IsValid() const;` — Returns true if the Character Pipeline should attempt to compile and use this table. Otherwise the Pipeline will assume that the user doesn't want a Parameter Mapping Table and will build the Character without one.
- L246 _public member_ `TObjectPtr<UDataTable> Table;` — `UPROPERTY(EditAnywhere, Category = ParameterMapping)` — The data table that will be evaluated
- L250 _public member_ `TArray<FMetaHumanParameterMappingInputColumnSet> InputColumnSets;` — `UPROPERTY(EditAnywhere, Category = ParameterMapping)` — The table columns to be used for input parameters should be specified here
- L254 _public member_ `TArray<FMetaHumanParameterMappingOutputColumnSet> OutputColumnSets;` — `UPROPERTY(EditAnywhere, Category = ParameterMapping)` — The table columns to be used for output parameters should be specified here

#### Free symbols / members of external scopes

- L158 _delegate_ `DECLARE_DELEGATE_TwoParams(FOutputParameterDelegate, FName , const FMetaHumanParameterValue& );`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanPinnedSlotSelection.h` (Public)


#### struct `FMetaHumanPinnedSlotSelection`  
`struct FMetaHumanPinnedSlotSelection`  
_L18-49_
- reflection: `USTRUCT()`
- desc: An item pinned to a slot at build time At assembly time, if a slot has any pinned items, it won't be able to have non-pinned items selected for it.
- L24 _public prototype_ `FMetaHumanPinnedSlotSelection() = default;`
- L25 _public prototype_ `FMetaHumanPinnedSlotSelection(const FMetaHumanPinnedSlotSelection& Other) = default;`
- L26 _public prototype_ `FMetaHumanPinnedSlotSelection(FMetaHumanPinnedSlotSelection&& Other) = default;`
- L27 _public prototype_ `FMetaHumanPinnedSlotSelection& operator=(const FMetaHumanPinnedSlotSelection& Other) = default;`
- L30 _public prototype_ `static bool IsItemPinned(TConstArrayView<FMetaHumanPinnedSlotSelection> SortedSelections, const FMetaHumanPaletteItemPath& ItemPath);`
- L31 _public prototype_ `static bool TryGetPinnedItem(TConstArrayView<FMetaHumanPinnedSlotSelection> SortedSelections, const FMetaHumanPaletteItemPath& ItemPath, const FMetaHumanPinnedSlotSelection*& OutPinnedItem);`
- L34 _public member_ `FMetaHumanPipelineSlotSelection Selection;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")`
- L38 _public member_ `FInstancedPropertyBag InstanceParameters;` — `UE_DEPRECATED(5.8, "There are now two types of Instance Parameters: Assembly Parameters and Post-Assembly Parameters. Only Assembly Parameters are used in this context.")` — `UPROPERTY(EditAnywhere, Category = "Pipeline")`
- L48 _public member_ `FInstancedPropertyBag AssemblyParameters;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")` — If the pipeline does any baking at build time that would use Assembly Parameters, it should use these values. If the parameters are still settable, they will be passed in again after assembly, so pipelines don't have to store this data at build time if they don't do anything with it.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanPipelineBuiltData.h` (Public)


#### struct `FMetaHumanPipelineBuiltData`  
`struct FMetaHumanPipelineBuiltData`  
_L19-57_
- reflection: `USTRUCT()`
- desc: The output of a single Character Pipeline's build step. In other words, the output of the build step for a palette itself, i.e. a Collection or a Wardrobe Item, not including any items within that palette.
- L31 _public member_ `FName SlotName;` — `UPROPERTY()` — If this is an item, SlotName is the real slot in the parent pipeline that this item was built for. This property is ignored for Collection build output.
- L34 _public member_ `FInstancedStruct BuildOutput;` — `UPROPERTY()`
- L38 _public member_ `FInstancedPropertyBag AssemblyParameters;` — `UPROPERTY()` — A struct of parameters that are settable for the assemble step, assigned to their default values
- L42 _public member_ `TArray<FMetaHumanGeneratedAssetMetadata> Metadata;` — `UPROPERTY()`
- L51 _public member_ `FString DefaultUnpackSubfolder;` — `UPROPERTY()` — If set, specifies the default sub-directory that this item's assets should be unpacked to when no explicit metadata entry exists for them. Has no influence on assets that have explicit metadata entries.
- L55 _public member_ `bool bDefaultSubfolderIsAbsolute = false;` — `UPROPERTY()` — If true, treat DefaultUnpackSubfolder as an absolute package path rather than a relative one.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanPipelineBuiltDataCollection.h` (Public)


#### struct `FMetaHumanPipelineBuiltDataCollectionPair`  
`struct FMetaHumanPipelineBuiltDataCollectionPair`  
_L17-27_
- reflection: `USTRUCT()`
- L23 _public member_ `FMetaHumanPaletteItemPath Key;` — `UPROPERTY()`
- L26 _public member_ `FMetaHumanPipelineBuiltData Value;` — `UPROPERTY()`

#### struct `FMetaHumanPipelineBuiltDataCollection`  
`struct FMetaHumanPipelineBuiltDataCollection`  
_L30-62_
- reflection: `USTRUCT()`
- L35 _public prototype_ `FMetaHumanPipelineBuiltDataCollectionEditor Edit();`
- L36 _public prototype_ `FMetaHumanPipelineBuiltDataCollectionMutableView MutableView();`
- L37 _public prototype_ `FMetaHumanPipelineBuiltDataCollectionView View() const;`
- L39 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L44 _public prototype_ `FMetaHumanPipelineBuiltData& Add(const FMetaHumanPaletteItemPath& ItemPath, FMetaHumanPipelineBuiltData&& Value);` — `UE_DEPRECATED(5.8, "Call Edit() to get an editing interface to this collection")`
- L47 _public prototype_ `FMetaHumanPipelineBuiltData& Add(const FMetaHumanPaletteItemPath& ItemPath);` — `UE_DEPRECATED(5.8, "Call Edit() to get an editing interface to this collection")`
- L50 _public prototype_ `const FMetaHumanPipelineBuiltData& operator[](const FMetaHumanPaletteItemPath& ItemPath) const;` — `UE_DEPRECATED(5.8, "Call View() to get a read-only view onto this collection")`
- L53 _public prototype_ `const FMetaHumanPipelineBuiltData* Find(const FMetaHumanPaletteItemPath& ItemPath) const;` — `UE_DEPRECATED(5.8, "Call View() to get a read-only view onto this collection")`
- L56 _public prototype_ `bool Contains(const FMetaHumanPaletteItemPath& ItemPath) const;` — `UE_DEPRECATED(5.8, "Call View() to get a read-only view onto this collection")`
- L61 _private member_ `TArray<FMetaHumanPipelineBuiltDataCollectionPair> SortedElements;` — `UPROPERTY()` — Sorted by ItemPath

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMetaHumanPipelineBuiltDataCollection> : public TStructOpsTypeTraitsBase2<FMetaHumanPipelineBuiltDataCollection>`  
_L65-71_
- inherits: `TStructOpsTypeTraitsBase2<FMetaHumanPipelineBuiltDataCollection>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L68-70_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`
- L12 _typedef_ `using FMetaHumanPipelineBuiltDataCollectionEditor = UE::MetaHuman::TMetaHumanItemPathMapEditor<FMetaHumanPipelineBuiltDataCollectionPair, FMetaHumanPipelineBuiltData>;`
- L13 _typedef_ `using FMetaHumanPipelineBuiltDataCollectionView = UE::MetaHuman::TMetaHumanItemPathMapView<FMetaHumanPipelineBuiltDataCollectionPair, FMetaHumanPipelineBuiltData>;`
- L14 _typedef_ `using FMetaHumanPipelineBuiltDataCollectionMutableView = UE::MetaHuman::TMetaHumanItemPathMapMutableView<FMetaHumanPipelineBuiltDataCollectionPair, FMetaHumanPipelineBuiltData>;`
- L69 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon67b19d3d0103`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanPipelineSlotSelection.h` (Public)


#### struct `FMetaHumanPipelineSlotSelection`  
`struct FMetaHumanPipelineSlotSelection`  
_L12-57_
- reflection: `USTRUCT(BlueprintType, meta = (HasNativeMake="/Script/MetaHumanCharacterPalette.MetaHumanPipelineSlotSelectionBlueprintLibrary.MakeSlotSelection"))`
- desc: An item selected for a slot
- L17 _public prototype_ `FMetaHumanPipelineSlotSelection() = default;`
- L18 _public prototype_ `FMetaHumanPipelineSlotSelection(const FMetaHumanPipelineSlotSelection&) = default;`
- L19 _public prototype_ `FMetaHumanPipelineSlotSelection(FMetaHumanPipelineSlotSelection&&) = default;`
- L20 _public prototype_ `FMetaHumanPipelineSlotSelection& operator=(const FMetaHumanPipelineSlotSelection&) = default;`
- L21 _public prototype_ `FMetaHumanPipelineSlotSelection& operator=(FMetaHumanPipelineSlotSelection&&) = default;`
- L22 _public prototype_ `~FMetaHumanPipelineSlotSelection() = default;`
- L24 _public prototype_ `FMetaHumanPipelineSlotSelection(FName InSlotName, const FMetaHumanPaletteItemKey& InSelectedItem);`
- L25 _public prototype_ `FMetaHumanPipelineSlotSelection(const FMetaHumanPaletteItemPath& InParentItemPath, FName InSlotName, const FMetaHumanPaletteItemKey& InSelectedItem);`
- L42 _public prototype_ `FMetaHumanPaletteItemPath GetSelectedItemPath() const;` — Returns the full path to the selected item
- L50 _public member_ `FMetaHumanPaletteItemPath ParentItemPath;` — `UPROPERTY(EditAnywhere, Category = "Pipeline")` — The path to the Collection or Wardrobe Item that contains the slot referenced by SlotName. If the slot is on the Collection itself, this path will be empty.
- L53 _public member_ `FName SlotName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipeline")`
- L56 _public member_ `FMetaHumanPaletteItemKey SelectedItem;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pipeline")`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanPipelineSlotSelectionData.h` (Public)


#### struct `FMetaHumanPipelineSlotSelectionData`  
`struct FMetaHumanPipelineSlotSelectionData`  
_L20-34_
- reflection: `USTRUCT(BlueprintType)`
- desc: An item selected for a slot, with additional data about the selection. It's a fine distinction, but FMetaHumanPipelineSlotSelection is like a key that identifies the selection, which may be passed around via public APIs. This struct contains data that is used to process the selection.
- L25 _public prototype_ `FMetaHumanPipelineSlotSelectionData() = default;`
- L26 _public prototype_ `~FMetaHumanPipelineSlotSelectionData() = default;`
- L27 _public prototype_ `FMetaHumanPipelineSlotSelectionData(const FMetaHumanPipelineSlotSelectionData&) = default;`
- L28 _public prototype_ `explicit FMetaHumanPipelineSlotSelectionData(const FMetaHumanPipelineSlotSelection& InSelection);`
- L31 _public member_ `FMetaHumanPipelineSlotSelection Selection;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")`

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanPostAssemblyParameterOutput.h` (Public)


#### struct `FMetaHumanPostAssemblyParameterOutput`  
`struct FMetaHumanPostAssemblyParameterOutput`  
_L12-37_
- reflection: `USTRUCT()`
- desc: TODO: Consider renaming to FMetaHumanPostAssemblyParameterState?
- L21 _public member_ `FInstancedPropertyBag Parameters;` — `UPROPERTY()` — Each supported Instance Parameter should have a property set to the default value of the parameter in this property bag.
- L29 _public member_ `FInstancedStruct ParameterContext;` — `UPROPERTY()` — A context struct that has meaning only to the pipeline instance that produced it. Other code should not try to parse this struct.
- L36 _public member_ `int32 PipelineAssemblyOutputArrayIndex = INDEX_NONE;` — `UPROPERTY()` — Used to locate this Item's Assembly Output in an array on the Collection Assembly Output when a slot specifies ArrayProperty as its EMetaHumanAssemblyOutputMappingMethod.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanPostAssemblyParameterOutputCollection.h` (Public)


#### struct `FMetaHumanPostAssemblyParameterOutputCollectionPair`  
`struct FMetaHumanPostAssemblyParameterOutputCollectionPair`  
_L19-29_
- reflection: `USTRUCT()`
- L25 _public member_ `FMetaHumanPaletteItemPath Key;` — `UPROPERTY()`
- L28 _public member_ `FMetaHumanPostAssemblyParameterOutput Value;` — `UPROPERTY()`

#### struct `FMetaHumanPostAssemblyParameterOutputCollection`  
`struct FMetaHumanPostAssemblyParameterOutputCollection`  
_L32-46_
- reflection: `USTRUCT()`
- L37 _public prototype_ `FMetaHumanPostAssemblyParameterOutputCollectionEditor Edit();`
- L38 _public prototype_ `FMetaHumanPostAssemblyParameterOutputCollectionView View() const;`
- L40 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L45 _private member_ `TArray<FMetaHumanPostAssemblyParameterOutputCollectionPair> SortedElements;` — `UPROPERTY()` — Sorted by ItemPath

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMetaHumanPostAssemblyParameterOutputCollection> : public TStructOpsTypeTraitsBase2<FMetaHumanPostAssemblyParameterOutputCollection>`  
_L49-55_
- inherits: `TStructOpsTypeTraitsBase2<FMetaHumanPostAssemblyParameterOutputCollection>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L52-54_

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`
- L15 _typedef_ `using FMetaHumanPostAssemblyParameterOutputCollectionEditor = UE::MetaHuman::TMetaHumanItemPathMapEditor<FMetaHumanPostAssemblyParameterOutputCollectionPair, FMetaHumanPostAssemblyParameterOutput>;`
- L16 _typedef_ `using FMetaHumanPostAssemblyParameterOutputCollectionView = UE::MetaHuman::TMetaHumanItemPathMapView<FMetaHumanPostAssemblyParameterOutputCollectionPair, FMetaHumanPostAssemblyParameterOutput>;`
- L53 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anon0d9add850103`)

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanUnpackUtilities.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANCHARACTERPALETTE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MetaHuman` (scope `UE`)
- L12 _namespace_ `namespace UnpackUtilities` (scope `UE::MetaHuman`)
- L28 _prototype_ `TSet<UObject*> GetDirectSubobjectsOfOwnerFromStruct( TNotNull<const UScriptStruct*> StructType, TNotNull<const void*> StructMemory, TNotNull<const UObject*> OwnerObject, bool bRecursive);` (scope `UE::MetaHuman::UnpackUtilities`) — Returns a set of objects that are referenced from the given USTRUCT instance and have OwnerObject as their direct Outer. This is used to find generated assets that are subobjects of a MetaHuman Collection or Instance. If bRecursive is true, references from objects (including those not under OwnerObject) will be recursively followed until all referenced objects have been found. If bRecursive is false, only objects referenced from the USTRUCT will be included in the results. In all cases, only the objects with OwnerObject as their direct Outer will be in the returned set.
- L48 _prototype_ `TSet<UObject*> GetDirectSubobjectsOfOwnerFromRoots(const TArray<UObject*>& RootObjects, TNotNull<const UObject*> OwnerObject, bool bRecursive);` (scope `UE::MetaHuman::UnpackUtilities`) — Returns a set of objects that are referenced from the given root objects and have OwnerObject as their direct Outer. This is used to find generated assets that are subobjects of a MetaHuman Collection or Instance. If bRecursive is true, references from objects (including those not under OwnerObject) will be recursively followed until all referenced objects have been found. If bRecursive is false, only objects referenced from the root objects will be included in the results. In all cases, only the objects with OwnerObject as their direct Outer will be in the returned set.
- L60 _prototype_ `TSet<UObject*> GetAllSubobjectsOfOwnerFromRoots(const TArray<UObject*>& RootObjects, TNotNull<const UObject*> OwnerObject, bool bRecursive);` (scope `UE::MetaHuman::UnpackUtilities`) — Returns a set of objects that are referenced from the given root objects and are in OwnerObject's outer chain (i.e. subobjects at any nesting depth). If bRecursive is true, references from objects (including those not under OwnerObject) will be recursively followed until all referenced objects have been found. If bRecursive is false, only objects referenced from the root objects will be included in the results.
- L74 _prototype_ `TSet<UObject*> GetAllSubobjectsOfOwnerFromStruct( TNotNull<const UScriptStruct*> StructType, TNotNull<const void*> StructMemory, TNotNull<const UObject*> OwnerObject, bool bRecursive);` (scope `UE::MetaHuman::UnpackUtilities`) — Returns a set of objects that are referenced from the given USTRUCT instance and have OwnerObject in their outer chain. If bRecursive is true, references from objects (including those not under OwnerObject) will be recursively followed until all referenced objects have been found. If bRecursive is false, only objects referenced from the USTRUCT will be included in the results. In all cases, only the objects with OwnerObject in their outer chain will be in the returned set.
- L90 _prototype_ `void MarkUnreferencedSubobjectsAsTransient(TNotNull<UObject*> OwnerObject);` (scope `UE::MetaHuman::UnpackUtilities`) — Finds all subobjects of OwnerObject (at any nesting depth) that are not referenced, directly or indirectly, from OwnerObject itself, and marks them as RF_Transient to prevent them from being saved. OwnerObject does not need to be a top level asset. When OwnerObject is itself a subobject of some larger object (e.g. a UMetaHumanCollection embedded as a subobject of another asset), this function will still correctly clean up only OwnerObject's own unreferenced subobjects without touching siblings or parent objects.
- L106 _prototype_ `bool TryUnpackObject( TNotNull<UObject*> Object, TNotNull<const UObject*> TopLevelAsset, FString& InOutAssetPackageName, TSet<FString>& OutUnpackedAssetPaths);` (scope `UE::MetaHuman::UnpackUtilities`) — Attempt to move the given object out of TopLevelAsset's package and into its own package as a standalone asset. InOutAssetPackageName must be set to the suggested package name that the new asset will be unpacked to. If there is a name conflict, TryUnpackObject will adjust the name to make it suitable. If the function succeeds, InOutAssetPackageName will be set to the name of the actual package that the asset was unpacked to. OutUnpackedAssetPaths should be a set shared by all unpacking operations for the same top level asset, to ensure that different assets don't overwrite each other as they're unpacked.
- L118 _prototype_ `bool TryUnpackItemAssetsFromMetaData( const FMetaHumanPaletteItemPath& BaseItemPath, FMetaHumanPipelineBuiltDataCollectionMutableView ItemBuiltData, const FString& UnpackFolder, const UMetaHumanCharacterEditorPipeline::FTryUnpackObjectDelegate& TryUnpackObjectDelegate);` (scope `UE::MetaHuman::UnpackUtilities`) — Uses the metadata from the given item's built data to unpack the item's assets to their preferred locations. TryUnpackObjectDelegate will be called to do the actual unpacking.

### `Plugins/MetaHuman/MetaHumanCharacter/Source/MetaHumanCharacterPalette/Public/MetaHumanWardrobeItem.h` (Public)


#### class `UMetaHumanWardrobeItem`  
`class UMetaHumanWardrobeItem : public UMetaHumanCharacterPalette`  
_L14-69_
- reflection: `UCLASS()`
- inherits: `UMetaHumanCharacterPalette`
- L22 _public prototype_ `void SetPipeline(TNotNull<UMetaHumanItemPipeline*> InPipeline);` — Set the Pipeline for this Wardrobe Item to use.
- L24 _public prototype_ `const UMetaHumanItemEditorPipeline* GetEditorPipeline() const;`
- L25 _public prototype_ `virtual const UMetaHumanCharacterEditorPipeline* GetPaletteEditorPipeline() const override;`
- L28 _public prototype_ `TObjectPtr<const UMetaHumanItemPipeline> GetPipeline() const;`
- L29 _public prototype_ `virtual const UMetaHumanCharacterPipeline* GetPalettePipeline() const override;`
- L34 _public prototype_ `bool IsExternal() const;` — Returns true if this Wardrobe Item is its own asset, false if it's a subobject of a Palette.
- L38 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L46 _public member_ `FEditorOnlyAssetReference PrincipalAsset;` — `UPROPERTY(EditAnywhere, DisplayName = "Principal Asset", Category = "Character", meta = (ShowOnlyInnerProperties))` — The main asset this item represents, e.g. a mesh.
- L50 _public member_ `TObjectPtr<class UThumbnailInfo> ThumbnailInfo;` — `UPROPERTY(VisibleAnywhere, Instanced, AdvancedDisplay, DisplayName = "Thumbnail Info", Category = "Thumbnail")`
- L54 _public member_ `TSoftObjectPtr<UTexture2D> ThumbnailImage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, DisplayName = "Thumbnail Image", Category = "Thumbnail")` — A selectable texture that will be used as wardrobe item thumbnail in editor
- L58 _public member_ `FText ThumbnailName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, DisplayName = "Thumbnail Name", Category = "Thumbnail")` — An editable text that will be used as thumbnail item name
- L68 _private member_ `TObjectPtr<UMetaHumanItemPipeline> Pipeline;` — `UPROPERTY(EditAnywhere, Instanced, DisplayName = "Pipeline", Category = "Character")` — The pipeline that will be used to build this Item. Choose the appropriate pipeline for the type of Principal Asset.
