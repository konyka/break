# Plugins / PropertyBindingUtils

- module root: `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtils`
- headers: 9; symbols: 364
- symbol kinds: class=4, enum=11, enumerator=66, externvar=1, function=113, macro=3, member=64, namespace=6, prototype=81, struct=15
- PrivateDependencyModuleNames: DeveloperSettings, InputCore, RenderCore
- PublicDependencyModuleNames: BlueprintGraph, Core, CoreUObject, Engine, UnrealEd

### `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtils/Private/PropertyBindingSettings.h` (Private)


#### class `UPropertyBindingSettings`  
`class UPropertyBindingSettings : public UDeveloperSettings`  
_L9-21_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig)`
- inherits: `UDeveloperSettings`
- L14 _public prototype_ `UPropertyBindingSettings();`
- L20 _public member_ `TArray<FName> MetaDataToKeepWhenPromotingToParameter;` — `UPROPERTY(EditAnywhere, config, Category = "Property Binding")` — Meta-data that are not in the MetaDataToKeepWhenPromotingToParameter are removed when a property is promoted.

### `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtils/Public/PropertyBindingBindableStructDescriptor.h` (Public)


#### struct `FPropertyBindingBindableStructDescriptor`  
`struct FPropertyBindingBindableStructDescriptor`  
_L12-63_
- reflection: `USTRUCT()`
- desc: Descriptor for a struct or class that can be a binding source or target. Each struct has unique identifier, which is used to distinguish them, and name that is mostly for debugging and UI.
- L16 _public prototype_ `FPropertyBindingBindableStructDescriptor() = default;`
- L17 _public prototype_ `virtual ~FPropertyBindingBindableStructDescriptor();`
- L20 _public function_ `FPropertyBindingBindableStructDescriptor(const FName InName, const UStruct* InStruct, const FGuid InGuid) : Struct(InStruct) , Name(InName) , ID(InGuid)`
- L27 _public function_ `bool operator==(const FPropertyBindingBindableStructDescriptor& RHS) const`
- L33 _public function_ `virtual FString GetSection() const` — Optional section that can be provided to the UI to organize the menus.
- L39 _public function_ `bool IsValid() const`
- L44 _public prototype_ `virtual FString ToString() const;`
- L48 _public member_ `TObjectPtr<const UStruct> Struct = nullptr;` — `UPROPERTY()` — The type of the struct or class.
- L52 _public member_ `FName Name;` — `UPROPERTY()` — Display name of the struct (used for debugging, logging, cosmetic), different from Struct->GetName().
- L57 _public member_ `FGuid ID;` — `UPROPERTY()` — Unique identifier of the struct.
- L61 _public member_ `FString Category;` — `UPROPERTY()` — Category of the bindable struct. Can be used to display the category in a menu.

### `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtils/Public/PropertyBindingBinding.h` (Public)


#### struct `FPropertyBindingBinding`  
`struct FPropertyBindingBinding`  
_L12-131_
- reflection: `USTRUCT()`
- desc: Representation of a property binding
- L16 _public prototype_ `FPropertyBindingBinding() = default;`
- L18 _public function_ `FPropertyBindingBinding(const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath) : SourcePropertyPath(InSourcePath) , TargetPropertyPath(InTargetPath)`
- L24 _public function_ `FPropertyBindingBinding(const FPropertyBindingBinding& Other) : SourcePropertyPath(Other.SourcePropertyPath) , TargetPropertyPath(Other.TargetPropertyPath) #if WITH_EDITOR , PropertyFunctionNode(Other.PropertyFunctionNode) #endif`
- L33 _public function_ `FPropertyBindingBinding& operator=(const FPropertyBindingBinding& Other)`
- L47 _public function_ `FPropertyBindingBinding(FPropertyBindingBinding&& Other) : SourcePropertyPath(MoveTemp(Other.SourcePropertyPath)) , TargetPropertyPath(MoveTemp(Other.TargetPropertyPath)) #if WITH_EDITOR , PropertyFunctionNode(MoveTemp(Other.PropertyFunctionNode)) #endif`
- L56 _public function_ `FPropertyBindingBinding& operator=(FPropertyBindingBinding&& Other)`
- L71 _public function_ `FPropertyBindingBinding(FConstStructView InFunctionNodeStruct, const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath) : SourcePropertyPath(InSourcePath) , TargetPropertyPath(InTargetPath) , PropertyFunctionNode(InFunctionNodeStruct)`
- L79 _public prototype_ `virtual ~FPropertyBindingBinding() = default;`
- L81 _public function_ `const FPropertyBindingPath& GetSourcePath() const`
- L86 _public function_ `const FPropertyBindingPath& GetTargetPath() const`
- L91 _public function_ `FPropertyBindingPath& GetMutableSourcePath()`
- L96 _public function_ `FPropertyBindingPath& GetMutableTargetPath()`
- L101 _public prototype_ `virtual FConstStructView GetSourceDataHandleStruct() const PURE_VIRTUAL(FPropertyBindingBinding::GetSourceDataHandle, return {};);`
- L104 _public function_ `FConstStructView GetPropertyFunctionNode() const`
- L109 _public function_ `FStructView GetMutablePropertyFunctionNode()`
- L115 _public prototype_ `FString ToString() const;`
- L120 _protected member_ `FPropertyBindingPath SourcePropertyPath;` — `UPROPERTY(VisibleAnywhere, Category = "Bindings")` — Source property path of the binding
- L124 _protected member_ `FPropertyBindingPath TargetPropertyPath;` — `UPROPERTY(VisibleAnywhere, Category = "Bindings")` — Target property path of the binding
- L129 _protected member_ `FInstancedStruct PropertyFunctionNode;` — `UPROPERTY(VisibleAnywhere, Category = "Bindings")` — Instance of bound PropertyFunction.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPropertyBindingBinding> : TStructOpsTypeTraitsBase2<FPropertyBindingBinding>`  
_L134-141_
- inherits: `TStructOpsTypeTraitsBase2<FPropertyBindingBinding>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L138-140_

#### Free symbols / members of external scopes

- L139 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anone6ac27390103`)
- L143 _namespace_ `namespace UE`
- L143 _namespace_ `namespace PropertyBinding` (scope `UE`)
- L145 _prototype_ `extern FString GetDescriptorAndPathAsString(const FPropertyBindingBindableStructDescriptor& InDescriptor, const FPropertyBindingPath& InPath);` (scope `UE::PropertyBinding`)

### `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtils/Public/PropertyBindingBindingCollection.h` (Public)


#### struct `FPropertyBindingBindingCollection`  
`struct FPropertyBindingBindingCollection`  
_L23-408_
- reflection: `USTRUCT()`
- desc: Base structure to inherit from to facilitate operations on property bindings. @see FPropertyBindingExtension, IPropertyBindingBindingCollectionOwner
- L27 _public prototype_ `virtual ~FPropertyBindingBindingCollection() = default;`
- L39 _public function_ `IPropertyBindingBindingCollectionOwner* GetBindingsOwner() const` — Get the associated bindings owner.
- L45 _public function_ `UObject* GetBindingsOwnerObject() const` — Get the associated bindings owner as a UObject.
- L51 _public function_ `void SetBindingsOwner(TScriptInterface<IPropertyBindingBindingCollectionOwner> InBindingsOwner)` — Sets associated bindings owner, used to validate added property paths.
- L70 _public function_ `virtual void OnBindingsOwnerSet(TScriptInterface<IPropertyBindingBindingCollectionOwner> InBindingsOwner)` — Can be overridden by derived classed to track newly assigned bindings owner interface.
- L79 _public prototype_ `void AddBinding(const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath);` — Adds binding between source and destination paths. Removes any bindings to InTargetPath before adding the new one. @param InSourcePath Binding source property path. @param InTargetPath Binding target property path.
- L86 _public prototype_ `void RemoveBindings(const FPropertyBindingPath& InTargetPath, ESearchMode InSearchMode = ESearchMode::Exact);` — Removes all bindings to target path. @param InTargetPath Target property path. @param InSearchMode Requirement for InTargetPath to be considered a match for a binding
- L92 _public prototype_ `void RemoveBindings(TFunctionRef<bool(FPropertyBindingBinding&)> InPredicate);` — Removes all bindings that match the predicate @param InPredicate Predicate to validate the binding
- L114 _public prototype_ `void RemoveInvalidBindings(const TMap<FGuid, const FPropertyBindingDataView>& InValidStructs, EInvalidBindingCriteria InCriteria = EInvalidBindingCriteria::Default);` — Removes bindings which do not point to valid structs IDs. @param InValidStructs Set of struct IDs that are currently valid. @param InCriteria Rules for what bindings are regarded as invalid
- L120 _public prototype_ `bool HasBinding(const FPropertyBindingPath& InTargetPath, ESearchMode InSearchMode = ESearchMode::Exact) const;` — Has any binding to the target path. @return True of the target path has any bindings.
- L125 _public prototype_ `const FPropertyBindingBinding* FindBinding(const FPropertyBindingPath& InTargetPath, ESearchMode InSearchMode = ESearchMode::Exact) const;` — @return binding to the target path.
- L133 _public prototype_ `void CopyBindings(const FGuid InFromStructID, const FGuid InToStructID);` — Copies property bindings from an existing struct to another. Overrides a binding to a specific property if it already exists in InToStructID. @param InFromStructID ID of the struct to copy from. @param InToStructID ID of the struct to copy to.
- L138 _public prototype_ `const FPropertyBindingPath* GetBindingSource(const FPropertyBindingPath& InTargetPath) const;` — @return Source path for given target path, or null if binding does not exist.
- L145 _public prototype_ `void GetBindingsFor(const FGuid InStructID, TArray<const FPropertyBindingBinding*>& OutBindings) const;` — Returns all pointers to bindings for a specified structs based in struct ID. @param InStructID ID of the struct to find bindings for. @param OutBindings Bindings for specified struct.
- L148 _protected prototype_ `virtual FPropertyBindingBinding* AddBindingInternal(const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath) PURE_VIRTUAL(FPropertyBindingBindingCollection::AddBindingInternal, return nullptr; );`
- L149 _protected prototype_ `virtual void CopyBindingsInternal(const FGuid InFromStructID, const FGuid InToStructID);`
- L150 _protected prototype_ `virtual void RemoveBindingsInternal(TFunctionRef<bool(FPropertyBindingBinding&)> InPredicate) PURE_VIRTUAL(FPropertyBindingBindingCollection::RemoveBindingsInternal, );`
- L151 _protected prototype_ `virtual bool HasBindingInternal(TFunctionRef<bool(const FPropertyBindingBinding&)> InPredicate) const PURE_VIRTUAL(FPropertyBindingBindingCollection::HasBindingInternal, return false; );`
- L152 _protected prototype_ `virtual const FPropertyBindingBinding* FindBindingInternal(TFunctionRef<bool(const FPropertyBindingBinding&)> InPredicate) const PURE_VIRTUAL(FPropertyBindingBindingCollection::FindBindingInternal, return nullptr; );`
- L155 _protected prototype_ `void CopyBindingsImplementation(const FGuid InFromStructID, const FGuid InToStructID, TFunctionRef<bool(const FPropertyBindingBinding& Binding)> CanCopy);` — Copies property bindings from an existing struct to another.
- L158 _protected prototype_ `void UpdateSegmentsForNewlyAddedBinding(FPropertyBindingBinding& AddedBinding);` — Update newly added binding's segments from struct value so that the segments are up to date.
- L160 _protected prototype_ `const UObject* GetLogOwner() const;`
- L163 _public function_ `FPropertyBindingCopyInfoBatch& AddCopyBatch()`
- L168 _public function_ `int32 GetNumCopyBatches() const`
- L173 _public function_ `const TArray<FPropertyBindingCopyInfoBatch>& GetCopyBatches() const`
- L178 _public function_ `TArray<FPropertyBindingCopyInfoBatch>& GetMutableCopyBatches()`
- L184 _public prototype_ `virtual int32 GetNumBindableStructDescriptors() const PURE_VIRTUAL(FPropertyBindingBindingCollection::GetNumBindableStructDescriptors, return INDEX_NONE;);` — @return Number of bindable struct descriptors available in the collection.
- L186 _public prototype_ `virtual const FPropertyBindingBindableStructDescriptor* GetBindableStructDescriptorFromHandle(FConstStructView InSourceHandleView) const PURE_VIRTUAL(FPropertyBindingBindingCollection::GetBindableStructDescriptorFromHandle, return nullptr; );`
- L189 _public prototype_ `virtual int32 GetNumBindings() const PURE_VIRTUAL(FPropertyBindingBindingCollection::GetNumBindings, return INDEX_NONE;);` — @return The amount of registered bindings.
- L198 _public prototype_ `virtual void ForEachBinding(TFunctionRef<void(const FPropertyBindingBinding& Binding)> InFunction) const PURE_VIRTUAL(FPropertyBindingBindingCollection::ForEachBinding, );` — Iterates through all bindings and calls the provided function on each non-mutable binding. @param InFunction Function to call on each binding. @note To be able to modify the binding, use ForEachMutableBinding @note To be able to break iteration, use VisitBindings or VisitMutableBindings @see ForEachMutableBinding, VisitBindings, VisitMutableBindings
- L209 _public prototype_ `virtual void ForEachBinding(FPropertyBindingIndex16 InBegin, FPropertyBindingIndex16 InEnd, TFunctionRef<void(const FPropertyBindingBinding& Binding, const int32 BindingIndex)> InFunction) const PURE_VIRTUAL(FPropertyBindingBindingCollection::ForEachBinding, );` — Iterates through all bindings between indices [Begin, End) and calls the provided function on each non-mutable binding. @param InBegin Index of the first binding to process @param InEnd Index to one past the last binding to process @param InFunction Function to call on each binding. @note To be able to modify the binding, use ForEachMutableBinding @note To be able to break iteration, use VisitBindings or VisitMutableBindings @see ForEachMutableBinding, VisitBindings, VisitMutableBindings
- L218 _public prototype_ `virtual void ForEachMutableBinding(TFunctionRef<void(FPropertyBindingBinding& Binding)> InFunction) PURE_VIRTUAL(FPropertyBindingBindingCollection::ForEachMutableBinding, );` — Iterates through all bindings and calls the provided function on each mutable binding. @param InFunction Function to call on each binding. @note For read access only, consider using ForEachBinding @note To be able to break iteration, use VisitBindings or VisitMutableBindings @see ForEachBinding, VisitBindings, VisitMutableBindings
- L228 _public prototype_ `virtual void VisitBindings(TFunctionRef<EVisitResult(const FPropertyBindingBinding& Binding)> InFunction) const PURE_VIRTUAL(FPropertyBindingBindingCollection::VisitBindings, );` — Iterates through all bindings and calls the provided function on each non-mutable binding. That function must return whether the iteration should stop or not (i.e., EVisitResult::Break / Continue). @param InFunction Function to call on each binding and that indicates whether the visit should stop @note To be able to modify the binding use VisitMutableBindings @note If breaking the iteration is not required, consider using ForEachBinding or ForEachMutableBinding @see VisitMutableBindings, ForEachBinding, ForEachMutableBinding
- L240 _public prototype_ `virtual void VisitBindings(FPropertyBindingIndex16 InBegin, FPropertyBindingIndex16 InEnd, TFunctionRef<EVisitResult(const FPropertyBindingBinding& Binding, const int32 BindingIndex)> InFunction) const PURE_VIRTUAL(FPropertyBindingBindingCollection::VisitBindings, );` — Iterates all bindings between indices [Begin, End) and calls the provided function on each non-mutable binding. That function must return whether the iteration should stop or not (i.e., EVisitResult::Break / Continue). @param InBegin Index of the first binding to process @param InEnd Index to one past the last binding to process @param InFunction Function to call on each binding and that indicates whether the visit should stop @note To be able to modify the binding use VisitMutableBindings @note If breaking the iteration is not required, consider using ForEachBinding or ForEachMutableBinding @see VisitMutableBindings, ForEachBinding, ForEachMutableBinding
- L251 _public prototype_ `virtual void VisitMutableBindings(TFunctionRef<EVisitResult(FPropertyBindingBinding& Binding)> InFunction) PURE_VIRTUAL(FPropertyBindingBindingCollection::VisitMutableBindings, );` — Iterates through all bindings and calls the provided function on each mutable binding. That function must return whether the iteration should stop or not (i.e., EVisitResult::Break / Continue). @param InFunction Function to call on each binding and that indicates whether the visit should stop. @note For read access only, consider using VisitBindings @note If breaking the iteration is not required, consider using ForEachBinding or ForEachMutableBinding @see VisitBindings, ForEachBinding, ForEachMutableBinding
- L256 _public prototype_ `void Reset();` — Clears all bindings and related data.
- L261 _public function_ `virtual void OnReset()` — Optional virtual that derived classes could override to when bindings should be reset.
- L269 _public prototype_ `[[nodiscard]] bool ResolvePaths();` — Resolves paths to indirections. @return True if resolve succeeded.
- L275 _public function_ `[[nodiscard]] virtual bool OnResolvingPaths()` — Optional virtual that derived classes could override to resolve additional paths. @return True if resolve succeeded.
- L283 _public function_ `bool IsValid() const` — @return True if bindings have been resolved.
- L295 _public prototype_ `bool CopyProperty(const FPropertyBindingCopyInfo& Copy, FPropertyBindingDataView SourceStructView, FPropertyBindingDataView TargetStructView) const;` — Copies a property from Source to Target based on the provided Copy. @param Copy Describes which parameter and how is copied. @param SourceStructView Pointer and type for the source containing the property to be copied. @param TargetStructView Pointer and type for the target containing the property to be copied. @return true if the property was copied successfully.
- L298 _public function_ `const FPropertyBindingCopyInfoBatch& GetBatch(const FPropertyBindingIndex16 TargetBatchIndex) const` — @return copy batch at specified index.
- L305 _public function_ `TConstArrayView<FPropertyBindingCopyInfo> GetBatchCopies(const FPropertyBindingIndex16 TargetBatchIndex) const` — @return All the property copies for a specific batch.
- L311 _public function_ `TConstArrayView<FPropertyBindingCopyInfo> GetBatchCopies(const FPropertyBindingCopyInfoBatch& Batch) const` — @return All the property copies for a specific batch.
- L327 _public prototype_ `bool ResetObjects(const FPropertyBindingIndex16 TargetBatchIndex, FPropertyBindingDataView TargetStructView) const;` — Resets copied properties in TargetStructView. Can be used e.g. to erase UObject references. @param TargetBatchIndex Batch index to copy (see FStateTreePropertyBindingCompiler). @param TargetStructView View to struct where properties are copied to. @return true if all resets succeeded (a reset can fail e.g. if source or destination struct view is invalid).
- L332 _public prototype_ `bool ContainsAnyStruct(const TSet<const UStruct*>& InStructs) const;` — @return true if any of the elements in the property bindings contains any of the structs in the set.
- L343 _public prototype_ `[[nodiscard]] virtual bool ResolveBindingCopyInfo(const FPropertyBindingBinding& InResolvedBinding, const FPropertyBindingPathIndirection& InBindingSourceLeafIndirection, const FPropertyBindingPathIndirection& InBindingTargetLeafIndirection, FPropertyBindingCopyInfo& OutCopyInfo);` — Resolves copy info for a resolved binding. Will resolve CopyType, CopySize and Leaf Properties. The other information has already been set in ResolvePaths. @param InResolvedBinding Resolved Binding corresponding to the resulting copy type, @param InBindingSourceLeafIndirection Property path indirections of the leaf property of binding source, @param InBindingTargetLeafIndirection Property path indirections of the leaf property of binding target. @param OutCopyInfo Resulting copy type. @return true if copy was resolved, or false if no copy could be resolved.
- L346 _public function_ `[[nodiscard]] static bool ResolveCopyType(const FPropertyBindingPathIndirection& SourceIndirection, const FPropertyBindingPathIndirection& TargetIndirection, FPropertyBindingCopyInfo& OutCopy, const UScriptStruct* StructReferenceType = nullptr)` — `UE_DEPRECATED(5.7, "ResolveCopyType is deprecated. Use ResolveBindingCopyInfo instead.")`
- L353 _protected prototype_ `[[nodiscard]] FString DebugAsString() const;`
- L356 _protected prototype_ `[[nodiscard]] bool ResolvePath(const UStruct* Struct, const FPropertyBindingPath& Path, FPropertyBindingPropertyIndirection& OutFirstIndirection, FPropertyBindingPathIndirection& OutLeafIndirection);`
- L357 _protected prototype_ `[[nodiscard]] bool ResolvePath(const FPropertyBindingDataView DataView, const FPropertyBindingPath& Path, FPropertyBindingPropertyIndirection& OutFirstIndirection, FPropertyBindingPathIndirection& OutLeafIndirection);`
- L366 _protected prototype_ `[[nodiscard]] bool ResolveCopyInfoBetweenIndirections(const FPropertyBindingPathIndirection& InSourceIndirection, const FPropertyBindingPathIndirection& InTargetIndirection, FPropertyBindingCopyInfo& OutCopyInfo) const;` — Resolves what kind of copy type to use between specified property indirections and what should be the correct copy size. @param InSourceIndirection Leaf path indirection of the copy source, @param InTargetIndirection Leaf path indirection of the copy target. @param OutCopyInfo copy info to resolve @return true if it was resolved, or false if it cannot be resolved between paths.
- L368 _protected prototype_ `bool PerformCopy(const FPropertyBindingCopyInfo& Copy, uint8* SourceAddress, uint8* TargetAddress) const;`
- L369 _protected prototype_ `void PerformResetObjects(const FPropertyBindingCopyInfo& Copy, uint8* TargetAddress) const;`
- L370 _protected prototype_ `uint8* GetAddress(FPropertyBindingDataView InStructView, const FPropertyBindingPropertyIndirection& FirstIndirection, const FProperty* LeafProperty) const;`
- L372 _protected function_ `virtual void VisitSourceStructDescriptorInternal(TFunctionRef<EVisitResult(const FPropertyBindingBindableStructDescriptor& Descriptor)> InFunction) const`
- L381 _protected member_ `TArray<FPropertyBindingCopyInfoBatch> CopyBatches;` — `UPROPERTY()` — Array of copy batches.
- L385 _protected member_ `TArray<FPropertyBindingCopyInfo> PropertyCopies;` — `UPROPERTY(Transient)` — Array of property copies
- L391 _private member_ `TArray<FPropertyBindingPropertyIndirection> PropertyIndirections;` — `UPROPERTY(Transient)` — Array of property indirections, indexed by accesses
- L394 _private member_ `bool bBindingsResolved = false;` — Flag indicating if the properties has been resolved successfully .
- L398 _protected member_ `TScriptInterface<IPropertyBindingBindingCollectionOwner> BindingsOwner = nullptr;` — `UPROPERTY(Transient)`
- L401 _protected member_ `TObjectPtr<UScriptStruct> PropertyReferenceStructType;` — Type for struct references copy type
- L404 _protected member_ `TFunction<void(const FStructProperty& SourceStructProperty, uint8* SourceAddress, uint8* TargetAddress)> PropertyReferenceCopyFunc;` — Functor to handle property copy for EPropertyCopyType::StructReference
- L407 _protected member_ `TFunction<void(uint8* TargetAddress)> PropertyReferenceResetFunc;` — Functor to handle reset object for EPropertyCopyType::StructReference

#### enum `FPropertyBindingBindingCollection::EVisitResult`  
`enum class EVisitResult : uint8`  
_L30-36_
- desc: Result returned from a visitor functor indicating to continue or to quit early
- L33 _public enumerator_ `Break` — Stop iterating through bindings and early exit
- L35 _public enumerator_ `Continue` — Continue to iterate through all bindings

#### enum `FPropertyBindingBindingCollection::ESearchMode`  
`enum class ESearchMode : uint8`  
_L61-67_
- desc: Enum describing what is required for a binding path to be considered a match for a binding
- L64 _public enumerator_ `Exact` — Binding with exact matching path
- L66 _public enumerator_ `Includes` — Binding with path that matches but the binding path can be longer

#### enum `FPropertyBindingBindingCollection::EInvalidBindingCriteria`  
`enum class EInvalidBindingCriteria : uint8`  
_L94-107_
- L97 _public enumerator_ `RemoveMissingSourceStruct = 1 << 0` — Binding is removed if Binding Source Struct is invalid
- L99 _public enumerator_ `RemoveMissingTargetStruct = 1 << 1` — Binding is removed if Binding Target Struct is invalid
- L101 _public enumerator_ `RemoveFailedToResolveSourcePath = 1 << 2` — Binding is removed if Binding Source Path failed to resolve
- L103 _public enumerator_ `RemoveFailedToResolveTargetPath = 1 << 3` — Binding is removed if Binding Target Path failed to resolve
- L106 _public enumerator_ `Default = RemoveMissingTargetStruct | RemoveFailedToResolveSourcePath | RemoveFailedToResolveTargetPath` — Missing Source Struct is not included to be consistent with the old behavior

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPropertyBindingBindingCollection> : public TStructOpsTypeTraitsBase2<FPropertyBindingBindingCollection>`  
_L411-417_
- inherits: `TStructOpsTypeTraitsBase2<FPropertyBindingBindingCollection>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L414-416_

#### Free symbols / members of external scopes

- L415 _enumerator_ `WithPureVirtual = true` (scope `TStructOpsTypeTraits::__anon926170250103`)

### `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtils/Public/PropertyBindingBindingCollectionOwner.h` (Public)


#### class `UPropertyBindingBindingCollectionOwner`  
`class UPropertyBindingBindingCollectionOwner : public UInterface`  
_L23-26_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPropertyBindingBindingCollectionOwner`  
`class IPropertyBindingBindingCollectionOwner`  
_L33-128_
- desc: Interface that asset or their associated Editor-only data could inherit from to facilitate operations on property bindings. @see FPropertyBindingExtension
- L52 _public function_ `virtual bool GetBindingDataView(const FPropertyBindingBinding& InBinding, EBindingSide InSide, FPropertyBindingDataView& OutDataView)` — Returns a data view for a given existing binding side. @param InBinding Binding to get a data view for @param InSide Side of the binding to get the data view for (source or target) @param OutDataView Result data view @return True if data view is found.
- L64 _public prototype_ `virtual void GetBindableStructs(const FGuid InTargetStructID, TArray<TInstancedStruct<FPropertyBindingBindableStructDescriptor>>& OutStructDescs) const = 0;` — Returns structs within the owner that are visible for target struct. @param InTargetStructID Target struct ID @param OutStructDescs Result descriptors of the visible structs.
- L72 _public prototype_ `virtual bool GetBindableStructByID(const FGuid InStructID, TInstancedStruct<FPropertyBindingBindableStructDescriptor>& OutStructDesc) const = 0;` — Returns struct descriptor based on struct ID. @param InStructID Target struct ID @param OutStructDesc Result descriptor. @return True if struct found.
- L80 _public prototype_ `virtual bool GetBindingDataViewByID(const FGuid InStructID, FPropertyBindingDataView& OutDataView) const = 0;` — Returns data view based on struct ID. @param InStructID Target struct ID @param OutDataView Result data view. @return True if struct found.
- L83 _public prototype_ `virtual FPropertyBindingBindingCollection* GetEditorPropertyBindings() = 0;` — @return Pointer to editor property bindings.
- L86 _public prototype_ `virtual const FPropertyBindingBindingCollection* GetEditorPropertyBindings() const = 0;` — @return Pointer to const editor property bindings.
- L93 _public function_ `virtual bool CanCreateParameter(const FGuid InStructID) const` — Can be overridden to determine whether the struct matching the given struct id is capable of adding new properties. @param InStructID Target struct ID @return Whether the struct supports adding new properties
- L102 _public prototype_ `virtual void OnPromotingToParameter(FPropertyBagPropertyDesc& PropertyDesc);` — Called when a property is being promoted to a parameter. @param PropertyDesc The newly created property descriptor
- L109 _public prototype_ `virtual void CreateParametersForStruct(const FGuid InStructID, TArrayView<UE::PropertyBinding::FPropertyCreationDescriptor> InOutCreationDescs) = 0;` — Creates the given properties in the property bag of the struct matching the given struct ID @param InStructID Target struct ID @param InOutCreationDescs the descriptions of the properties to create. This is modified to update the property names that actually got created
- L112 _public function_ `virtual FGuid GetFallbackStructID() const` — Can be overridden to provide a fallback structure ID to build the property path if no bindable structs are found when traversing a PropertyHandle hierarchy.
- L119 _public function_ `virtual void AppendBindablePropertyFunctionStructs(TArray<TInstancedStruct<FPropertyBindingBindableStructDescriptor>>& InOutStructs) const` — Can be overridden to provide additional bindable structs from property functions.
- L124 _public function_ `virtual void OnPropertyBindingChanged(const FPropertyBindingPath& InSourcePath, const FPropertyBindingPath& InTargetPath)` — Can be overridden to perform additional operations when property bindings changed.

#### enum `IPropertyBindingBindingCollectionOwner::EBindingSide`  
`enum class EBindingSide : uint8`  
_L39-43_
- L41 _public enumerator_ `Source`
- L42 _public enumerator_ `Target`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API PROPERTYBINDINGUTILS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace PropertyBinding` (scope `UE`)

### `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtils/Public/PropertyBindingDataView.h` (Public)


#### struct `FPropertyBindingDataView`  
`struct FPropertyBindingDataView`  
_L16-199_
- desc: Short-lived pointer to an object or struct. Can be constructed directly from a pointer to a UObject or from a StructView. When creating from a generic UStruct, the data view expects a valid type (UStruct) when a valid memory pointer is provided. It that case it is also fine to provide null for both and the constructed data view will be considered as invalid.
- L18 _public prototype_ `FPropertyBindingDataView() = default;`
- L26 _public function_ `FPropertyBindingDataView(const UStruct* InStruct, void* InMemory) : Struct(InStruct), Memory(InMemory)` — Generic struct constructor. Valid UStruct is required when passing in valid memory pointer. Both can be null and the constructed data view will be considered as invalid. @see IsValid
- L33 _public function_ `FPropertyBindingDataView(UObject* Object) : Struct(Object ? Object->GetClass() : nullptr), Memory(Object)` — UObject constructor.
- L40 _public function_ `FPropertyBindingDataView(const FStructView StructView) : Struct(StructView.GetScriptStruct()), Memory(StructView.GetMemory())` — Struct from a StructView.
- L47 _public function_ `FPropertyBindingDataView(FInstancedStruct& InstancedStruct) : Struct(InstancedStruct.GetScriptStruct()), Memory(InstancedStruct.GetMutableMemory())` — Struct from a InstancedStruct.
- L57 _public function_ `bool IsValid() const` — Check is the view is valid (both pointer and type are set). On valid views it is safe to call the Get<>() methods returning a reference. @return True if the view is valid.
- L66 _public function_ `template <typename T> typename TEnableIf<TIsDerivedFrom<T, UObject>::IsDerived, const T&>::Type Get() const` — UObject getters (reference & pointer, const & mutable)
- L75 _public function_ `template <typename T> typename TEnableIf<TIsDerivedFrom<T, UObject>::IsDerived, T&>::Type GetMutable() const`
- L84 _public function_ `template <typename T> typename TEnableIf<TIsDerivedFrom<T, UObject>::IsDerived, const T*>::Type GetPtr() const`
- L93 _public function_ `template <typename T> typename TEnableIf<TIsDerivedFrom<T, UObject>::IsDerived, T*>::Type GetMutablePtr() const`
- L105 _public function_ `template <typename T> typename TEnableIf<!TIsDerivedFrom<T, UObject>::IsDerived && !TIsIInterface<T>::Value, const T&>::Type Get() const` — Struct getters (reference & pointer, const & mutable)
- L114 _public function_ `template <typename T> typename TEnableIf<!TIsDerivedFrom<T, UObject>::IsDerived && !TIsIInterface<T>::Value, T&>::Type GetMutable() const`
- L123 _public function_ `template <typename T> typename TEnableIf<!TIsDerivedFrom<T, UObject>::IsDerived && !TIsIInterface<T>::Value, const T*>::Type GetPtr() const`
- L132 _public function_ `template <typename T> typename TEnableIf<!TIsDerivedFrom<T, UObject>::IsDerived && !TIsIInterface<T>::Value, T*>::Type GetMutablePtr() const`
- L144 _public function_ `template <typename T> typename TEnableIf<TIsIInterface<T>::Value, const T&>::Type Get() const` — IInterface getters (reference & pointer, const & mutable)
- L152 _public function_ `template <typename T> typename TEnableIf<TIsIInterface<T>::Value, T&>::Type GetMutable() const`
- L160 _public function_ `template <typename T> typename TEnableIf<TIsIInterface<T>::Value, const T*>::Type GetPtr() const`
- L168 _public function_ `template <typename T> typename TEnableIf<TIsIInterface<T>::Value, T*>::Type GetMutablePtr() const`
- L176 _public function_ `const UStruct* GetStruct() const` — @return Struct describing the data type.
- L182 _public function_ `const void* GetMemory() const` — @return Raw const pointer to the data.
- L188 _public function_ `void* GetMutableMemory() const` — @return Raw mutable pointer to the data.
- L195 _protected member_ `const UStruct* Struct = nullptr;` — UClass or UScriptStruct of the data.
- L198 _protected member_ `void* Memory = nullptr;` — Memory pointing at the class or struct

### `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtils/Public/PropertyBindingPath.h` (Public)


#### struct `FPropertyBindingPathIndirection`  
`struct FPropertyBindingPathIndirection`  
_L26-137_
- desc: Struct describing an indirection at specific segment at path. Returned by FPropertyBindingPath::ResolveIndirections() and FPropertyBindingPath::ResolveIndirectionsWithValue(). Generally there's one indirection per FProperty. Containers have one path segment but two indirection (container + inner type).
- L28 _public prototype_ `FPropertyBindingPathIndirection() = default;`
- L29 _public function_ `explicit FPropertyBindingPathIndirection(const UStruct* InContainerStruct) : ContainerStruct(InContainerStruct)`
- L34 _public function_ `const FProperty* GetProperty() const`
- L39 _public function_ `const void* GetContainerAddress() const`
- L44 _public function_ `const UStruct* GetInstanceStruct() const`
- L49 _public function_ `const UStruct* GetContainerStruct() const`
- L54 _public function_ `int32 GetArrayIndex() const`
- L59 _public function_ `int32 GetPropertyOffset() const`
- L64 _public function_ `int32 GetPathSegmentIndex() const`
- L69 _public function_ `EPropertyBindingPropertyAccessType GetAccessType() const`
- L74 _public function_ `const void* GetPropertyAddress() const`
- L79 _public function_ `void* GetMutablePropertyAddress() const`
- L85 _public function_ `FName GetDisplayName() const`
- L90 _public function_ `FName GetRedirectedName() const`
- L95 _public function_ `FGuid GetPropertyGuid() const`
- L103 _private member_ `const FProperty* Property = nullptr;` — Property at the indirection.
- L106 _private member_ `const void* ContainerAddress = nullptr;` — Address of the container class/struct where the property belongs to. Only valid if created with ResolveIndirectionsWithValue()
- L109 _private member_ `const UStruct* ContainerStruct = nullptr;` — Type of the container class/struct.
- L112 _private member_ `const UStruct* InstanceStruct = nullptr;` — Type of the instance class/struct of when AccessType is ObjectInstance or StructInstance.
- L115 _private member_ `int32 ArrayIndex = INDEX_NONE;` — Array index for static and dynamic arrays. Note: static array indexing is baked in the PropertyOffset.
- L118 _private member_ `int32 PropertyOffset = INDEX_NONE;` — Offset of the property relative to ContainerAddress. Includes static array indexing.
- L121 _private member_ `int32 PathSegmentIndex = INDEX_NONE;` — Index of the path segment where indirection originated from.
- L124 _private member_ `EPropertyBindingPropertyAccessType AccessType = EPropertyBindingPropertyAccessType::Offset;` — How to access the data through the indirection.
- L127 _private member_ `FName DisplayName;`
- L130 _private member_ `FName RedirectedName;` — Redirected name, if the give property name was not found but was reconciled using core redirect or property Guid. Requires ResolveIndirections/WithValue() to be called with bHandleRedirects = true.
- L133 _private member_ `FGuid PropertyGuid;` — Guid of the property for Blueprint classes or User Defined Structs. Requires ResolveIndirections/WithValue() to be called with bHandleRedirects = true.

#### struct `FPropertyBindingPathSegment`  
`struct FPropertyBindingPathSegment`  
_L141-253_
- reflection: `USTRUCT()`
- desc: Struct describing a path segment in FPropertyBindingPath.
- L145 _public prototype_ `FPropertyBindingPathSegment() = default;`
- L147 _public function_ `explicit FPropertyBindingPathSegment(const FName InName, const int32 InArrayIndex = INDEX_NONE) : Name(InName) , ArrayIndex(InArrayIndex)`
- L153 _public function_ `explicit FPropertyBindingPathSegment(const FName InName, const int32 InArrayIndex, const UStruct* InInstanceStruct, const EPropertyBindingPropertyAccessType InAccessType) : Name(InName) , ArrayIndex(InArrayIndex) , InstanceStruct(InInstanceStruct) , InstancedStructAccessType(InAccessType)`
- L161 _public function_ `bool operator==(const FPropertyBindingPathSegment& RHS) const`
- L166 _public function_ `bool operator!=(const FPropertyBindingPathSegment& RHS) const`
- L171 _public function_ `void SetName(const FName InName)`
- L176 _public function_ `FName GetName() const`
- L181 _public function_ `void SetArrayIndex(const int32 InArrayIndex)`
- L186 _public function_ `int32 GetArrayIndex() const`
- L191 _public function_ `void SetInstanceStruct(const UStruct* InInstanceStruct, const EPropertyBindingPropertyAccessType InAccessType = EPropertyBindingPropertyAccessType::StructInstance)`
- L197 _public function_ `const UStruct* GetInstanceStruct() const`
- L202 _public function_ `EPropertyBindingPropertyAccessType GetInstancedStructAccessType() const`
- L208 _public function_ `FName GetDisplayName() const`
- L213 _public function_ `void SetDisplayName(const FName InName)`
- L218 _public function_ `FGuid GetPropertyGuid() const`
- L223 _public function_ `void SetPropertyGuid(const FGuid NewGuid)`
- L232 _private member_ `FName Name;` — `UPROPERTY(VisibleAnywhere, Category = "Bindings")` — Name of the property
- L236 _private member_ `int32 ArrayIndex = INDEX_NONE;` — `UPROPERTY(VisibleAnywhere, Category = "Bindings")` — Array index if the property is dynamic or static array.
- L240 _private member_ `TObjectPtr<const UStruct> InstanceStruct = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "Bindings")` — Type of the instanced struct or object reference by the property at the segment. This allows the path to be resolved when it points to a specific instance.
- L243 _private member_ `EPropertyBindingPropertyAccessType InstancedStructAccessType = EPropertyBindingPropertyAccessType::Unset;` — `UPROPERTY(VisibleAnywhere, Category = "Bindings")`
- L247 _private member_ `FName DisplayName;` — `UPROPERTY(VisibleAnywhere, Category = "Bindings")`
- L251 _private member_ `FGuid PropertyGuid;` — `UPROPERTY(transient, VisibleAnywhere, Category = "Bindings", AdvancedDisplay)` — Guid of the property for Blueprint classes, User Defined Structs, or Property Bags.

#### struct `FPropertyBindingPath`  
`struct FPropertyBindingPath`  
_L266-483_
- reflection: `USTRUCT()`
- desc: Representation of a property path that can be used for property access and binding. The engine supports many types of property paths, this implementation has these specific properties: - Allow to resolve all the indirections from a base value (object or struct) up to the leaf property - handle redirects from Core Redirect, BP classes, User Defines Structs and Property Bags You may also take a look at: FCachedPropertyPath, TFieldPath<>, FPropertyPath.
- L270 _public prototype_ `FPropertyBindingPath() = default;`
- L273 _public function_ `explicit FPropertyBindingPath(const FGuid InStructID) : StructID(InStructID)`
- L278 _public function_ `explicit FPropertyBindingPath(const FGuid InStructID, const FName PropertyName) : StructID(InStructID)`
- L284 _public function_ `explicit FPropertyBindingPath(const FGuid InStructID, TConstArrayView<FPropertyBindingPathSegment> InSegments) : StructID(InStructID) , Segments(InSegments)`
- L296 _public prototype_ `bool FromString(const FStringView InPath);` — Parses path from string. The path should be in format: Foo.Bar[1].Baz @param InPath Path string to parse @return true if path was parsed successfully.
- L306 _public prototype_ `FString ToString(const int32 HighlightedSegment = INDEX_NONE, const TCHAR* HighlightPrefix = nullptr, const TCHAR* HighlightPostfix = nullptr, const bool bOutputInstances = false, const int32 FirstSegment = 0) const;` — Returns the property path as a one string. Highlight allows to decorate a specific segment. @param HighlightedSegment Index of the highlighted path segment @param HighlightPrefix String to append before highlighted segment @param HighlightPostfix String to append after highlighted segment @param bOutputInstances if true, the instance struct types will be output. @param FirstSegment Index of the first path segment to be stringified.
- L317 _public prototype_ `bool ResolveIndirections(const UStruct* BaseStruct, TArray<FPropertyBindingPathIndirection>& OutIndirections, FString* OutError = nullptr, bool bHandleRedirects = false, bool bResetIndirectionsIfFailed = true) const;` — Resolves the property path against base struct type. The path is assumed to be relative to the BaseStruct. @param BaseStruct Base struct/class type the path is relative to. @param OutIndirections Indirections describing how the properties were accessed. @param OutError Optional, pointer to string where error will be logged if update fails. @param bHandleRedirects If true, the method will try to resolve missing properties using core redirects, and properties on Blueprint and User Defined Structs by ID. Available only in editor builds! @param bResetIndirectionsIfFailed If true, indirections resolved so far will be cleared if the path failed to resolve in the end. @return true of path could be resolved against the base value, and instance types were updated.
- L318 _public prototype_ `bool ResolveIndirections(const UStruct* BaseStruct, TArray<FPropertyBindingPathIndirection, TInlineAllocator<16>>& OutIndirections, FString* OutError = nullptr, bool bHandleRedirects = false, bool bResetIndirectionsIfFailed = true) const;`
- L329 _public prototype_ `bool ResolveIndirectionsWithValue(const FPropertyBindingDataView BaseValueView, TArray<FPropertyBindingPathIndirection>& OutIndirections, FString* OutError = nullptr, bool bHandleRedirects = false, bool bResetIndirectionsIfFailed = true) const;` — Resolves the property path against base value. The path is assumed to be relative to the BaseValueView. @param BaseValueView Base value the path is relative to. @param OutIndirections Indirections describing how the properties were accessed. @param OutError Optional, pointer to string where error will be logged if update fails. @param bHandleRedirects If true, the method will try to resolve missing properties using core redirects, and properties on Blueprint and User Defined Structs by ID. Available only in editor builds! @param bResetIndirectionsIfFailed If true, indirections resolved so far will be cleared if the path failed to resolve in the end. @return true of path could be resolved against the base value, and instance types were updated.
- L330 _public prototype_ `bool ResolveIndirectionsWithValue(const FPropertyBindingDataView BaseValueView, TArray<FPropertyBindingPathIndirection, TInlineAllocator<16>>& OutIndirections, FString* OutError = nullptr, bool bHandleRedirects = false, bool bResetIndirectionsIfFailed = true) const;`
- L339 _public prototype_ `bool UpdateSegments(const UStruct* BaseStruct, FString* OutError = nullptr);` — Updates property segments from base struct type. The path is expected to be relative to the BaseStruct. The method handles renamed properties (core redirect, Blueprint, User Defined Structs and Property Bags by ID). @param BaseStruct Base struct/class type the path is relative to @param OutError Optional, pointer to string where error will be logged if update fails. @return true of path could be resolved against the base value, and instance types were updated.
- L349 _public prototype_ `bool UpdateSegmentsFromValue(const FPropertyBindingDataView BaseValueView, FString* OutError = nullptr);` — Updates property segments from base value. The path is expected to be relative to the base value. The method updates instance types, and handles renamed properties (core redirect, Blueprint, User Defined Structs and Property Bags by ID). By storing the instance types on the path, we can resolve the path without the base value later. @param BaseValueView Base value the path is relative to. @param OutError Optional, pointer to string where error will be logged if update fails. @return true of path could be resolved against the base value, and instance types were updated.
- L357 _public prototype_ `void UpdateSegmentsFromIndirections(const TConstArrayView<FPropertyBindingPathIndirection>& Indirections);` — Updates property segments from resolved indirections. The path is expected to be relative to the base value. The method updates instance types, and handles renamed properties (core redirect, Blueprint, User Defined Structs and Property Bags by ID). By storing the instance types on the path, we can resolve the path without the base value later. @param Indirections completely resolved indirections
- L364 _public prototype_ `bool ContainsAnyStruct(TConstArrayView<const UStruct*> InStructs) const;` — Check if the binding path contains any structs from cached instance struct type. @param InStructs any structs the binding path may contain @return true if path contains any struct
- L372 _public prototype_ `bool ContainsAnyStruct(TConstArrayView<const UStruct*> InStructs, const UStruct* BaseStruct) const;` — Check if the binding path contains any structs from base struct type. @param InStructs any structs the binding path may contain @param BaseStruct Base struct/class type the path is relative to @return true if path contains any struct
- L380 _public prototype_ `bool ContainsAnyStructWithValue(TConstArrayView<const UStruct*> InStructs, const FPropertyBindingDataView BaseValueView) const;` — Check if the binding path contains any structs from base value. @param InStructs any structs the binding path may contain @param BaseValueView Base value the path is relative to @return true if path contains any struct
- L388 _public prototype_ `static bool IndirectionsContainAnyStruct(TConstArrayView<const UStruct*> InStructs, const TConstArrayView<FPropertyBindingPathIndirection> Indirections);` — Check if indirections contain any structs. @param InStructs any structs the binding path may contain @param Indirections Indirections resolved so far to check against @return true if indirections contains any struct
- L391 _public function_ `bool IsPathEmpty() const` — @return true if the path is empty. In that case the path points to the struct.
- L397 _public function_ `bool HasAnyInstancedIndirection() const` — @return true if any of the path segments is and indirection via instanced struct or object.
- L406 _public function_ `void Reset()` — Reset the path to empty.
- L415 _public function_ `const FGuid& GetStructID() const`
- L420 _public function_ `void SetStructID(const FGuid NewStructID)`
- L426 _public function_ `TConstArrayView<FPropertyBindingPathSegment> GetSegments() const`
- L431 _public function_ `TArrayView<FPropertyBindingPathSegment> GetMutableSegments()`
- L436 _public function_ `int32 NumSegments() const`
- L441 _public function_ `const FPropertyBindingPathSegment& GetSegment(const int32 Index) const`
- L447 _public function_ `void AddPathSegment(const FName InName , const int32 InArrayIndex = INDEX_NONE , const UStruct* InInstanceType = nullptr , EPropertyBindingPropertyAccessType InInstanceAccessType = EPropertyBindingPropertyAccessType::StructInstance)` — Adds a path segment to the path.
- L456 _public function_ `void AddPathSegment(const FPropertyBindingPathSegment& PathSegment)` — Adds a path segment to the path.
- L462 _public prototype_ `bool operator==(const FPropertyBindingPath& RHS) const;` — Test if paths are equal.
- L468 _public prototype_ `bool Includes(const FPropertyBindingPath& Other) const;` — Test if this paths includes the provided path. A path includes another one when they are == but this path can be longer.
- L474 _private member_ `FGuid StructID;` — `UPROPERTY(VisibleAnywhere, Category = "Bindings", AdvancedDisplay)` — ID of the struct this property path is relative to.
- L479 _private member_ `TArray<FPropertyBindingPathSegment> Segments;` — `UPROPERTY(VisibleAnywhere, Category = "Bindings")` — Path segments pointing to a specific property on the path.
- L482 _private prototype_ `template<typename Allocator> bool ResolveIndirectionsWithValue(const FPropertyBindingDataView BaseValueView, TArray<FPropertyBindingPathIndirection, Allocator>& OutIndirections, FString* OutError = nullptr, bool bHandleRedirects = false, bool bResetIndirectionsIfFailed = true) const;`

#### enum `EPropertyCopyType`  
`enum class EPropertyCopyType : uint8`  
_L490-540_
- reflection: `UENUM()`
- desc: Describes how the copy should be performed.
- L492 _public enumerator_ `None` — No copying
- L494 _public enumerator_ `CopyPlain` — For plain old data types, we do a simple memcpy.
- L495 _public enumerator_ `CopyComplex` — For more complex data types, we need to call the properties copy function
- L496 _public enumerator_ `CopyBool` — Read and write properties using bool property helpers, as source/dest could be bitfield or boolean
- L497 _public enumerator_ `CopyStruct` — Use struct copy operation, as this needs to correctly handle CPP struct ops
- L498 _public enumerator_ `CopyObject` — Read and write properties using object property helpers, as source/dest could be regular/weak/soft etc.
- L499 _public enumerator_ `CopyName` — FName needs special case because its size changes between editor/compiler and runtime.
- L500 _public enumerator_ `CopyFixedArray` — Array needs special handling for fixed size TArrays
- L502 _public enumerator_ `StructReference` — Copies pointer to a source struct into a given struct specified by FPropertyBindingBindingCollection::PropertyReferenceStructType.
- L507 _public enumerator_ `PromoteBoolToByte` — Bool promotions
- L508 _public enumerator_ `PromoteBoolToInt32`
- L509 _public enumerator_ `PromoteBoolToUInt32`
- L510 _public enumerator_ `PromoteBoolToInt64`
- L511 _public enumerator_ `PromoteBoolToFloat`
- L512 _public enumerator_ `PromoteBoolToDouble`
- L515 _public enumerator_ `PromoteByteToInt32` — Byte promotions
- L516 _public enumerator_ `PromoteByteToUInt32`
- L517 _public enumerator_ `PromoteByteToInt64`
- L518 _public enumerator_ `PromoteByteToFloat`
- L519 _public enumerator_ `PromoteByteToDouble`
- L522 _public enumerator_ `PromoteInt32ToInt64` — Int32 promotions
- L523 _public enumerator_ `PromoteInt32ToFloat` — This is strictly sketchy because of potential data loss, but it is usually OK in the general case
- L524 _public enumerator_ `PromoteInt32ToDouble`
- L527 _public enumerator_ `PromoteUInt32ToInt64` — UInt32 promotions
- L528 _public enumerator_ `PromoteUInt32ToFloat` — This is strictly sketchy because of potential data loss, but it is usually OK in the general case
- L529 _public enumerator_ `PromoteUInt32ToDouble`
- L532 _public enumerator_ `PromoteFloatToInt32` — Float promotions
- L533 _public enumerator_ `PromoteFloatToInt64`
- L534 _public enumerator_ `PromoteFloatToDouble`
- L537 _public enumerator_ `DemoteDoubleToInt32` — Double promotions
- L538 _public enumerator_ `DemoteDoubleToInt64`
- L539 _public enumerator_ `DemoteDoubleToFloat`

#### struct `FPropertyBindingPropertyIndirection`  
`struct FPropertyBindingPropertyIndirection`  
_L547-584_
- reflection: `USTRUCT()`
- desc: Used internally. Property indirection is a resolved property path segment, used for accessing properties in structs.
- L553 _public member_ `FPropertyBindingIndex16 ArrayIndex;` — `UPROPERTY()` — Index in the array the property points at.
- L557 _public member_ `uint16 Offset = 0;` — `UPROPERTY()` — Cached offset of the property
- L561 _public member_ `FPropertyBindingIndex16 NextIndex;` — `UPROPERTY()` — Cached offset of the property
- L565 _public member_ `EPropertyBindingPropertyAccessType Type = EPropertyBindingPropertyAccessType::Offset;` — `UPROPERTY()` — Type of access/indirection.
- L569 _public member_ `TObjectPtr<const UStruct> InstanceStruct = nullptr;` — `UPROPERTY()` — Type of the struct or object instance in case the segment is pointing into an instanced data.
- L572 _public member_ `const FArrayProperty* ArrayProperty = nullptr;` — Cached array property.

#### struct `FPropertyBindingCopyInfo`  
`struct FPropertyBindingCopyInfo`  
_L592-636_
- reflection: `USTRUCT()`
- desc: Used internally. Describes property copy, the property from source is copied into the property at the target. Copy target struct is described in the property copy batch.
- L598 _public member_ `FPropertyBindingPropertyIndirection SourceIndirection;` — `UPROPERTY()` — Source property access.
- L602 _public member_ `FPropertyBindingPropertyIndirection TargetIndirection;` — `UPROPERTY()` — Target property access.
- L606 _public member_ `FInstancedStruct SourceDataHandle;` — `UPROPERTY()` — Describes how to get the source data pointer for the copy.
- L609 _public member_ `const FProperty* SourceLeafProperty = nullptr;` — Cached pointer to the leaf property of the access.
- L612 _public member_ `const FProperty* TargetLeafProperty = nullptr;` — Cached pointer to the leaf property of the access.
- L616 _public member_ `TObjectPtr<const UStruct> SourceStructType = nullptr;` — `UPROPERTY(Transient)` — Type of the source data, used for validation.
- L620 _public member_ `int32 CopySize = 0;` — `UPROPERTY()` — Cached property element size * dim.
- L624 _public member_ `EPropertyCopyType Type = EPropertyCopyType::None;` — `UPROPERTY()` — Type of the copy
- L631 _public member_ `bool bPromoteArrayCopy = false;` — `UPROPERTY()` — The source property and the target property are array properties. The inner type of the source property can be promoted to the inner type of the target property.
- L635 _public member_ `bool bCopyFromTargetToSource = false;` — `UPROPERTY()` — Copy will be performed from target property to the source property.

#### struct `FPropertyBindingCopyInfoBatch`  
`struct FPropertyBindingCopyInfoBatch`  
_L643-666_
- reflection: `USTRUCT()`
- desc: Describes a batch of property copies from many sources to one target struct. Note: The batch is used to reference both bindings and copies (a binding turns into copy when resolved).
- L649 _public member_ `TInstancedStruct<FPropertyBindingBindableStructDescriptor> TargetStruct;` — `UPROPERTY()` — Expected target struct
- L653 _public member_ `FPropertyBindingIndex16 BindingsBegin;` — `UPROPERTY()` — Index to first binding/copy.
- L657 _public member_ `FPropertyBindingIndex16 BindingsEnd;` — `UPROPERTY()` — Index to one past the last binding/copy.
- L661 _public member_ `FPropertyBindingIndex16 PropertyFunctionsBegin;` — `UPROPERTY()` — Index to first property function.
- L665 _public member_ `FPropertyBindingIndex16 PropertyFunctionsEnd;` — `UPROPERTY()` — Index to one past the last property function.

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API PROPERTYBINDINGUTILS_API`
- L400 _function_ `` (scope `FPropertyBindingPath::HasAnyInstancedIndirection`)
- L574 _function_ `friend uint32 GetTypeHash(const FPropertyBindingPropertyIndirection& Indirection)`

### `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtils/Public/PropertyBindingTypes.h` (Public)


#### enum `EPropertyBindingAccessType`  
`enum class UE_DEPRECATED(5.6, "Use EPropertyBindingPropertyAccessType instead") EPropertyBindingAccessType : uint8`  
_L16-25_
- reflection: `UENUM()`
- L18 _public enumerator_ `Offset` — Access node is a simple basePtr + offset
- L19 _public enumerator_ `Object` — Access node needs to dereference an object at its current address
- L20 _public enumerator_ `WeakObject` — Access is a weak object
- L21 _public enumerator_ `SoftObject` — Access is a soft object
- L22 _public enumerator_ `ObjectInstance` — Access node needs to dereference an object of specific type at its current address
- L23 _public enumerator_ `StructInstance` — Access node needs to dereference an instanced struct of specific type at its current address
- L24 _public enumerator_ `IndexArray` — Access node indexes a dynamic array

#### enum `EPropertyBindingPropertyAccessType`  
`enum class EPropertyBindingPropertyAccessType : uint8`  
_L28-40_
- reflection: `UENUM()`
- L30 _public enumerator_ `Offset` — Access node is a simple basePtr + offset
- L31 _public enumerator_ `Object` — Access node needs to dereference an object at its current address
- L32 _public enumerator_ `WeakObject` — Access is a weak object
- L33 _public enumerator_ `SoftObject` — Access is a soft object
- L34 _public enumerator_ `ObjectInstance` — Access node needs to dereference an object of specific type at its current address
- L35 _public enumerator_ `StructInstance` — Access node needs to dereference an instanced struct of specific type at its current address
- L36 _public enumerator_ `IndexArray` — Access node indexes a dynamic array
- L37 _public enumerator_ `SharedStruct` — Access node needs to dereference a shared struct of specific type at its current address
- L38 _public enumerator_ `StructInstanceContainer` — Access node needs to dereference an instanced struct container at its current address
- L39 _public enumerator_ `Unset`

#### struct `FPropertyBindingIndex16`  
`struct FPropertyBindingIndex16`  
_L44-115_
- reflection: `USTRUCT(BlueprintType)`
- desc: uint16 index that can be invalid.
- L48 _public member_ `static constexpr uint16 InvalidValue = MAX_uint16;`
- L49 _public member_ `static const FPropertyBindingIndex16 Invalid;`
- L57 _public function_ `static bool IsValidIndex(const int32 Index)` — @return true if the given index can be represented by the type.
- L62 _public prototype_ `FPropertyBindingIndex16() = default;`
- L68 _public function_ `explicit FPropertyBindingIndex16(const uint16 InIndex) : Value(InIndex)` — Construct from a uint16 index where MAX_uint16 is considered an invalid index (i.e., FPropertyBindingIndex16::InvalidValue).
- L76 _public function_ `explicit FPropertyBindingIndex16(const int32 InIndex)` — Construct from an int32 index where INDEX_NONE is considered an invalid index and converted to FPropertyBindingIndex16::InvalidValue (i.e., MAX_uint16).
- L83 _public function_ `uint16 Get() const` — @return value of the index or FPropertyBindingIndex16::InvalidValue (i.e. MAX_uint16) if invalid.
- L89 _public function_ `int32 AsInt32() const` — @return the index value as int32, mapping invalid value to INDEX_NONE.
- L95 _public function_ `bool IsValid() const` — @return true if the index is valid.
- L100 _public function_ `bool operator==(const FPropertyBindingIndex16& RHS) const`
- L105 _public function_ `bool operator!=(const FPropertyBindingIndex16& RHS) const`
- L110 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L114 _protected member_ `uint16 Value = InvalidValue;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPropertyBindingIndex16> : TStructOpsTypeTraitsBase2<FPropertyBindingIndex16>`  
_L118-125_
- inherits: `TStructOpsTypeTraitsBase2<FPropertyBindingIndex16>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L122-124_

#### enum `UE::PropertyBinding::EPropertyCompatibility`  
`enum class EPropertyCompatibility : uint8`  
_L139-147_
- desc: Enum describing property compatibility
- L142 _public enumerator_ `Incompatible` — Properties are incompatible
- L144 _public enumerator_ `Compatible` — Properties are directly compatible
- L146 _public enumerator_ `Promotable` — Properties can be copied with a simple type promotion

#### struct `UE::PropertyBinding::FPropertyCreationDescriptor`  
`struct FPropertyCreationDescriptor`  
_L150-160_
- desc: Struct of parameters used to create a property in a property bag.
- L153 _public member_ `FPropertyBagPropertyDesc PropertyDesc;` — Property Bag Description of the Property to Create
- L156 _public member_ `const FProperty* SourceProperty = nullptr;` — Optional: property to copy into the new created property
- L159 _public member_ `const void* SourceContainerAddress = nullptr;` — Optional: container address of the property to copy

#### Free symbols / members of external scopes

- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPropertyBindingUtils, Warning, All);`
- L12 _macro_ `#define WITH_PROPERTYBINDINGUTILS_DEBUG (!(UE_BUILD_SHIPPING || UE_BUILD_SHIPPING_WITH_EDITOR || UE_BUILD_TEST) && 1)`
- L51 _function_ `friend inline uint32 GetTypeHash(const FPropertyBindingIndex16 Index)`
- L123 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anon7d683b730103`)
- L128 _namespace_ `namespace UE`
- L128 _namespace_ `namespace PropertyBinding` (scope `UE`)
- L135 _externvar_ `extern TArray<TFunction<bool(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, TNotNull<FPropertyBindingIndex16*> Index)>> PropertyBindingIndex16ConversionFuncList;` (scope `UE::PropertyBinding`) — List of external types conversion functors that can be used to convert compatible struct types to FPropertyBindingIndex16 in FPropertyBindingIndex16::SerializeFromMismatchedTag
- L163 _prototype_ `EPropertyCompatibility GetPropertyCompatibility(const FProperty* FromProperty, const FProperty* ToProperty);` (scope `UE::PropertyBinding`) — @return how properties are compatible for copying.
- L171 _prototype_ `void CreateUniquelyNamedPropertiesInPropertyBag(TArrayView<FPropertyCreationDescriptor> InOutCreationDescs, FInstancedPropertyBag& OutPropertyBag);` (scope `UE::PropertyBinding`) — Helper function to 1. Generate unique names for the incoming property descriptors (to avoid changing the existing properties in the property bag) 2. Add uniquely named properties to the property bag 3. Attempt to copy values from the Source Property / Address og the property descriptors.

### `Plugins/Runtime/PropertyBindingUtils/Source/PropertyBindingUtils/Public/PropertyBindingUtilsModule.h` (Public)


#### class `IPropertyBindingUtilsModule`  
`class IPropertyBindingUtilsModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline IPropertyBindingUtilsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
