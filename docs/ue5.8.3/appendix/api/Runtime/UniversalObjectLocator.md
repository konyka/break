# Runtime / UniversalObjectLocator

- module root: `Source/Runtime/UniversalObjectLocator`
- headers: 19; symbols: 400
- symbol kinds: class=1, enum=9, enumerator=29, function=100, macro=2, member=65, namespace=32, prototype=110, struct=37, typedef=15
- PublicDependencyModuleNames: Core, CoreUObject, HTTP

### `Source/Runtime/UniversalObjectLocator/Private/UniversalObjectLocatorRegistry.h` (Private)


#### struct `UE::UniversalObjectLocator::FRegistry`  
`struct FRegistry : FGCObject`  
_L14-26_
- inherits: `FGCObject`
- L17 _public prototype_ `static FRegistry& Get();`
- L19 _public prototype_ `const FFragmentType* FindFragmentType(FName ID) const;`
- L21 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L22 _public prototype_ `FString GetReferencerName() const override;`
- L24 _public member_ `TArray<TObjectPtr<UScriptStruct>> ParameterTypes;`
- L25 _public member_ `TArray<FFragmentType> FragmentTypes;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)

### `Source/Runtime/UniversalObjectLocator/Public/DirectPathObjectLocator.h` (Public)


#### struct `FDirectPathObjectLocator`  
`struct FDirectPathObjectLocator`  
_L16-42_
- reflection: `USTRUCT()`
- desc: Object locator type that simply references its object by a direct path
- L21 _public member_ `FSoftObjectPath Path;` — `UPROPERTY()`
- L23 _public member_ `static UE::UniversalObjectLocator::TFragmentTypeHandle<FDirectPathObjectLocator> FragmentType;`
- L35 _public prototype_ `UE::UniversalObjectLocator::FResolveResult Resolve(const UE::UniversalObjectLocator::FResolveParams& Params) const;`
- L36 _public prototype_ `UE::UniversalObjectLocator::FInitializeResult Initialize(const UE::UniversalObjectLocator::FInitializeParams& InParams);`
- L38 _public prototype_ `void ToString(FStringBuilderBase& OutStringBuilder) const;`
- L39 _public prototype_ `UE::UniversalObjectLocator::FParseStringResult TryParseString(FStringView InString, const UE::UniversalObjectLocator::FParseStringParams& Params);`
- L41 _public prototype_ `static uint32 ComputePriority(const UObject* Object, const UObject* Context);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDirectPathObjectLocator> : public TStructOpsTypeTraitsBase2<FDirectPathObjectLocator>`  
_L45-51_
- inherits: `TStructOpsTypeTraitsBase2<FDirectPathObjectLocator>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L48-50_

#### Free symbols / members of external scopes

- L25 _function_ `friend uint32 GetTypeHash(const FDirectPathObjectLocator& A)`
- L30 _function_ `friend bool operator==(const FDirectPathObjectLocator& A, const FDirectPathObjectLocator& B)`
- L49 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon36f1d6b30103`)

### `Source/Runtime/UniversalObjectLocator/Public/IUniversalObjectLocatorModule.h` (Public)


#### struct `UE::UniversalObjectLocator::FFragmentTypeParameters`  
`struct FFragmentTypeParameters`  
_L22-35_
- L24 _public function_ `FFragmentTypeParameters(FName InFragmentTypeID, FText InDisplayText) : DisplayText(InDisplayText) , FragmentTypeID(InFragmentTypeID) , Flags(EFragmentTypeFlags::None)`
- L31 _public member_ `FText DisplayText;`
- L32 _public member_ `FName FragmentTypeID;`
- L33 _public member_ `FName PrimaryEditorType;`
- L34 _public member_ `EFragmentTypeFlags Flags;`

#### class `UE::UniversalObjectLocator::IUniversalObjectLocatorModule`  
`class IUniversalObjectLocatorModule : public IModuleInterface`  
_L37-134_
- inherits: `IModuleInterface`
- L70 _public function_ `TFragmentTypeHandle<PayloadStructType> RegisterFragmentType(FFragmentTypeParameters& FragmentTypeParameters)`
- L111 _public function_ `template<typename ParameterType> TParameterTypeHandle<ParameterType> RegisterParameterType()`
- L116 _public function_ `void UnregisterParameterType(FParameterTypeHandle InHandle)`
- L122 _public function_ `template<typename PayloadStructType> void UnregisterFragmentType(TFragmentTypeHandle<PayloadStructType> FragmentType)`
- L129 _private prototype_ `virtual FFragmentTypeHandle RegisterFragmentTypeImpl(const FFragmentType& FragmentType) = 0;`
- L130 _private prototype_ `virtual void UnregisterFragmentTypeImpl(FFragmentTypeHandle FragmentType) = 0;`
- L132 _private prototype_ `virtual FParameterTypeHandle RegisterParameterTypeImpl(UScriptStruct* Struct) = 0;`
- L133 _private prototype_ `virtual void UnregisterParameterTypeImpl(FParameterTypeHandle ParameterType) = 0;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)
- L86 _function_ `` (scope `UE::UniversalObjectLocator::IUniversalObjectLocatorModule::RegisterFragmentType`)

### `Source/Runtime/UniversalObjectLocator/Public/SubObjectLocator.h` (Public)


#### struct `FSubObjectLocator`  
`struct FSubObjectLocator`  
_L13-38_
- reflection: `USTRUCT()`
- L18 _public member_ `FString PathWithinContext;` — `UPROPERTY()`
- L20 _public member_ `static UE::UniversalObjectLocator::TFragmentTypeHandle<FSubObjectLocator> FragmentType;`
- L32 _public prototype_ `UE::UniversalObjectLocator::FResolveResult Resolve(const UE::UniversalObjectLocator::FResolveParams& Params) const;`
- L33 _public prototype_ `UE::UniversalObjectLocator::FInitializeResult Initialize(const UE::UniversalObjectLocator::FInitializeParams& InParams);`
- L34 _public prototype_ `void ToString(FStringBuilderBase& OutStringBuilder) const;`
- L35 _public prototype_ `UE::UniversalObjectLocator::FParseStringResult TryParseString(FStringView InString, const UE::UniversalObjectLocator::FParseStringParams& Params);`
- L37 _public prototype_ `static uint32 ComputePriority(const UObject* Object, const UObject* Context);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FSubObjectLocator> : public TStructOpsTypeTraitsBase2<FSubObjectLocator>`  
_L41-47_
- inherits: `TStructOpsTypeTraitsBase2<FSubObjectLocator>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L44-46_

#### Free symbols / members of external scopes

- L22 _function_ `friend uint32 GetTypeHash(const FSubObjectLocator& A)`
- L27 _function_ `friend bool operator==(const FSubObjectLocator& A, const FSubObjectLocator& B)`
- L45 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anond9a4c0b50103`)

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocator.h` (Public)


#### struct `FUniversalObjectLocator`  
`struct FUniversalObjectLocator`  
_L31-254_
- reflection: `USTRUCT(BlueprintType, Category=GameFramework, meta=(HasNativeMake="/Script/Engine.UniversalObjectLocatorScriptingExtensions.MakeUniversalObjectLocator"))`
- desc: Universal Object Locators (UOLs) define an address to an object. The address is implemented as a chain of FUniversalObjectLocatorFragments, allowing addressing of objects that may be nested deeply within levels of externally defined spawn or ownership logic. For example, a Universal Object Locator may reference an Anim Instance within a Skeletal Mesh Actor is spawned by a Child Actor Component that is spawned by Sequencer. This is impossible with a regular soft object path, but is perfectly feasible for a UOL. This type is 16 bytes.
- L35 _public typedef_ `using FResolveParams = UE::UniversalObjectLocator::FResolveParams;`
- L36 _public typedef_ `using FResolveResult = UE::UniversalObjectLocator::FResolveResult;`
- L37 _public typedef_ `using FResolveResultData = UE::UniversalObjectLocator::FResolveResultData;`
- L38 _public typedef_ `using FParseStringParams = UE::UniversalObjectLocator::FParseStringParams;`
- L39 _public typedef_ `using FParseStringResult = UE::UniversalObjectLocator::FParseStringResult;`
- L44 _public prototype_ `FUniversalObjectLocator();` — Default constructor
- L54 _public prototype_ `FUniversalObjectLocator(UObject* Object, UObject* Context = nullptr, UObject* StopAtContext = nullptr);` — Attempt to construct this locator from a given object. May result in an empty locator if no suitable address could be created. @param Object           The object that this locator should represent @param Context          (Optional) Constrain this universal reference based on the specified context. This context should be passed to Resolve otherwise the resolution may fail. @param StopAtContext    (Optional) Stop constructing this universal reference when we reach the following context (can be used if that context is always passed to Resolve to keep this type smaller)
- L59 _public function_ `bool IsEmpty() const` — Check if this locator is 'empty'. An empty locator contains no fragments and will never resolve.
- L70 _public prototype_ `FResolveResult Resolve(const FResolveParams& Params) const;` — Attempt to resolve this locator by invoking the payload's 'Resolve' function @param Params           Resolution parameters defining the type of resolution to perform @return A result structure defining the resolved object pointer, and associated flags
- L79 _public prototype_ `FResolveResult AsyncFind(UObject* Context = nullptr) const;` — Attempt to find the object this locator points to. Shorthand for Resolve(FResolveParams::AsyncFind(Context)).AsObject().ReleaseFuture(). @param Context          (Optional) An optional context to use for finding the object - should match what was specified in Reset() or in construction @return A result structure that may or may not already have a result populated
- L88 _public prototype_ `FResolveResult AsyncLoad(UObject* Context = nullptr) const;` — Attempt to find the object this locator points to, loading it if necessary (and possible). Shorthand for Resolve(FResolveParams::AsyncLoad(Context)).AsObject().ReleaseFuture(). @param Context          (Optional) An optional context to use for finding/loading the object - should match what was specified in Reset() @return A result structure that may or may not already have a result populated
- L97 _public prototype_ `FResolveResult AsyncUnload(UObject* Context = nullptr) const;` — Attempt to unload the object this locator points to if possible. Shorthand for Resolve(FResolveParams::AsyncUnload(Context)).AsVoid().ReleaseFuture(). @param Context          (Optional) An optional context to use for finding/loading the object - should match what was specified in Reset() @return A result structure that may or may not already have a result populated
- L106 _public prototype_ `UObject* SyncFind(UObject* Context = nullptr) const;` — Attempt to find the object this locator points to. Shorthand for Resolve(FResolveParams::SyncFind(Context)).AsObject().SyncGet().Object. @param Context          (Optional) An optional context to use for finding the object - should match what was specified in Reset() or in construction @return The located object, or nullptr on failure
- L115 _public prototype_ `UObject* SyncLoad(UObject* Context = nullptr) const;` — Attempt to find the object this locator points to, loading it if necessary (and possible), and blocking until it is loaded. Shorthand for Resolve(FResolveParams::SyncLoad(Context)).AsObject().SyncGet().Object. @param Context          (Optional) An optional context to use for finding/loading the object - should match what was specified in Reset() @return The located object, or nullptr on failure
- L124 _public prototype_ `void SyncUnload(UObject* Context = nullptr) const;` — Attempt to unload the object this locator points to if possible. Shorthand for Resolve(FResolveParams::SyncUnload(Context)).AsVoid().SyncGet(). @param Context          (Optional) An optional context to use for finding/loading the object - should match what was specified in Reset() @return The located object, or nullptr on failure
- L129 _public prototype_ `const UE::UniversalObjectLocator::FFragmentType* GetLastFragmentType() const;` — Retrieve the fragment type relating to the last locator in this address
- L134 _public prototype_ `UE::UniversalObjectLocator::FFragmentTypeHandle GetLastFragmentTypeHandle() const;` — Retrieve the fragment type handle relating to the last locator in this address
- L141 _public prototype_ `void ToString(FStringBuilderBase& OutString) const;` — Convert this locator to its string representation @param OutString        String builder to populate
- L150 _public prototype_ `FParseStringResult TryParseString(FStringView InString, const FParseStringParams& InParams);` — Attempt to deserialize this locator from a string @param InString         The string to parse @param InParams         Additional string parameters @return Parse result, specifying success or failure, and number of characters that were parsed
- L160 _public prototype_ `static FUniversalObjectLocator FromString(FStringView InString, const FParseStringParams& InParams);` — Attempt to deserialize a new locator from a string. Shorthand for FUniversalObjectLocator L; L.TryParseString(InString, InParams);. @param InString         The string to parse @param InParams         Additional string parameters @return A (perhaps empty) object locator
- L167 _public prototype_ `void Reset();` — Reset this locator back to its default-constructed, empty state
- L177 _public prototype_ `void Reset(UObject* Object, UObject* Context = nullptr, UObject* StopAtContext = nullptr);` — Attempt to reset this locator to point at a different object. May result in an empty locator if no suitable address could be created. @param Object           The object that this locator should represent @param Context          (Optional) Constrain this universal reference based on the specified context. This context should be passed to Resolve otherwise the resolution may fail. @param StopAtContext    (Optional) Stop constructing this universal reference when we reach the following context (can be used if that context is always passed to Resolve to keep this type smaller)
- L184 _public prototype_ `void AddFragment(FUniversalObjectLocatorFragment&& InFragment);` — Add a fragment to the end of this locator @param InFragment       The fragment to add
- L192 _public prototype_ `template<typename FragmentType, typename ...ArgTypes> void AddFragment(ArgTypes&&... FragmentArgs);` — Templated helper for AddFragment @param InFragment       The fragment to add
- L197 _public prototype_ `FUniversalObjectLocatorFragment* GetLastFragment();` — Retrieve the last fragment in this address
- L202 _public prototype_ `const FUniversalObjectLocatorFragment* GetLastFragment() const;` — Retrieve the last fragment in this address
- L209 _public prototype_ `bool ForEachFragment(TFunctionRef<bool(int32, int32, const FUniversalObjectLocatorFragment&)> InFunction) const;` — Iterate the fragments in this address @param InFunction       The visitor function to call for each fragment in this address. Function should return false to stop iteration. @return false if the iteration was stopped early, true if the iteration succeeded (or if empty)
- L214 _public prototype_ `UE::UniversalObjectLocator::EFragmentTypeFlags GetDefaultFlags() const;` — Iterates over all fragments and combines their types' default flags.
- L234 _public prototype_ `bool ExportTextItem(FString& ValueStr, const FUniversalObjectLocator& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const;` — ~ Begin TStructOpsTypeTraits implementation
- L235 _public prototype_ `bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText, FArchive* InSerializingArchive = nullptr);`
- L236 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L241 _private prototype_ `bool AddFragment(const UObject* Object, UObject* Context, UObject* StopAtContext);` — Adds the 'best' fragment according to the input object and context, as well as any potential required relative fragments
- L243 _private prototype_ `FResolveResult ResolveSyncImpl(const FResolveParams& Params) const;`
- L244 _private prototype_ `FResolveResult ResolveAsyncImpl(const FResolveParams& Params) const;`
- L250 _private member_ `TArray<FUniversalObjectLocatorFragment> Fragments;` — `UPROPERTY()` — Array of relative locators ordered sequentially from outer to inner. The first locator is probably 'absolute' and is resolved with no context, although that is not a hard restriction
- L257 _function_ `template<typename FragmentType, typename ...ArgTypes> void FUniversalObjectLocator::AddFragment(ArgTypes&&... FragmentArgs)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUniversalObjectLocator> : public TStructOpsTypeTraitsBase2<FUniversalObjectLocator>`  
_L264-273_
- inherits: `TStructOpsTypeTraitsBase2<FUniversalObjectLocator>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L267-272_

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)
- L268 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anond46767640103`)
- L269 _enumerator_ `WithExportTextItem = true` (scope `TStructOpsTypeTraits::__anond46767640103`)
- L270 _enumerator_ `WithImportTextItem = true` (scope `TStructOpsTypeTraits::__anond46767640103`)
- L271 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anond46767640103`)

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocatorFragment.h` (Public)


#### struct `FUniversalObjectLocatorFragment`  
`struct alignas(8) FUniversalObjectLocatorFragment`  
_L35-355_
- reflection: `USTRUCT(BlueprintType)`
- desc: Universal Object Locator (UOL) Fragments provide an extensible mechanism for referencing permanent, transient or dynamically created objects relative to an external context. UOLs comprise zero or more nested fragments. Creation and resolution of a fragment requires a context to be provided; normally this will be the object on which the UOL exists as a property. The way in which the object is referenced is defined by globally registered 'FragmentTypes' (See IUniversalObjectLocatorModule::RegisterFragmentType). Each FragmentType can be thought of as somewhat equivalent to a www URI fragment type, though the 'path' is not necessarily just a string, but includes support for the full set of Engine Property types. The type is implemented as a type-erased payload block, a fragment type handle and some internal flags. Payloads will be allocated using the inline memory if alignment and size constraints allow, but will fall back to a heap allocation if necessary. Allocation should be avoided by keeping payload types small. Aligned to 8 bytes, 32 (runtime) or 64 (editor) bytes big.
- L39 _public typedef_ `using FParseStringResult = UE::UniversalObjectLocator::FParseStringResult;`
- L40 _public typedef_ `using FParseStringParams = UE::UniversalObjectLocator::FParseStringParams;`
- L42 _public member_ `static inline constexpr FAsciiSet ValidFragmentTypeCharacters = "ab`
- L44 _public member_ `static inline constexpr FAsciiSet ValidFragmentDelimiters = "%!` — Valid fragment delimiters are those that are allowable by RFC3986 for the query part (unreserved / pct-encoded / sub-delims / ":" / "@" / "/" / "?") excluding '&' which we use to separate fragments within a path
- L45 _public member_ `static inline constexpr FAsciiSet ValidFragmentPayloadCharacters = ValidFragmentTypeCharacters | ValidFragmentDelimiters;`
- L49 _public member_ `static constexpr SIZE_T SizeInMemory = 64;`
- L51 _public member_ `static constexpr SIZE_T SizeInMemory = 32;`
- L63 _public prototype_ `template<typename T, typename ...ArgTypes> FUniversalObjectLocatorFragment(UE::UniversalObjectLocator::TFragmentTypeHandle<T> InHandle, ArgTypes&& ...InArgs);` — Construct a new fragment with a specific fragment type and data. Used when a specific type of relative fragment is required. @param InHandle    A typed handle to the fragment type to use for construction. Retrieved from IUniversalObjectLocatorModule::RegisterFragmentType. @param InArgs      (Optional) Payload construction arguments to be passed to T on construction. Omission implies default construction.
- L72 _public prototype_ `FUniversalObjectLocatorFragment(const UE::UniversalObjectLocator::FFragmentType& InFragmentType);` — Construct a new fragment with a specific fragment type and default-constructed payload. Used when a specific type of relative fragment is required. @param InFragmentType  The fragment type to use with this fragment
- L78 _public prototype_ `FUniversalObjectLocatorFragment(const UObject* InObject, UObject* Context);` — Construct this fragment by binding it to an object within a given context. @note: This constructor can 'fail' and result in an Empty fragment if no suitable fragment type could be found for the object
- L81 _public prototype_ `FUniversalObjectLocatorFragment();` — Default constructor: initializes to an empty fragment with no fragment type
- L84 _public prototype_ `~FUniversalObjectLocatorFragment();` — Destructor - destructs the payload, and frees any heap allocation as necessary
- L87 _public prototype_ `FUniversalObjectLocatorFragment(const FUniversalObjectLocatorFragment& RHS);` — Copy construction/assignment
- L88 _public prototype_ `FUniversalObjectLocatorFragment& operator=(const FUniversalObjectLocatorFragment& RHS);`
- L91 _public prototype_ `FUniversalObjectLocatorFragment(FUniversalObjectLocatorFragment&& RHS);` — Move construction/assignment
- L92 _public prototype_ `FUniversalObjectLocatorFragment& operator=(FUniversalObjectLocatorFragment&& RHS);`
- L108 _public prototype_ `UE::UniversalObjectLocator::FResolveResult Resolve(const UE::UniversalObjectLocator::FResolveParams& Params) const;` — Attempt to resolve this fragment by invoking the payload's 'Resolve' function @param Params           Resolution parameters, defining the context to resolve within, and the type of resolution to perform @return A result structure defining the resolved object pointer, and associated flags
- L114 _public function_ `bool IsEmpty() const` — Check whether this reference is empty. @note: An empty fragment can never resolve to an object, but is distinct from, and not equal to, a populated fragment that does points to a non-existent or irretrievable object.
- L124 _public prototype_ `void Reset();` — Reset this fragment back to its default-constructed, empty state
- L130 _public prototype_ `void Reset(const UObject* InObject, UObject* Context);` — Reset this fragment to point to a new object from the specified context @note: If no suitable fragment type could be found for the object and context, results in an Empty fragment
- L136 _public prototype_ `void Reset(const UObject* InObject, UObject* Context, TFunctionRef<bool(UE::UniversalObjectLocator::FFragmentTypeHandle)> CanUseFragmentType);` — Reset this fragment to point to a new object from the specified context using a filtered set of fragment types @note: If no suitable fragment type could be found for the object and context, results in an Empty fragment
- L145 _public prototype_ `void ToString(FStringBuilderBase& OutString) const;` — Convert this fragment to a string of the form fragment-id[=fragment-payload] @param OutString        String builder to populate
- L155 _public prototype_ `FParseStringResult TryParseString(FStringView InString, const FParseStringParams& InParams);` — Attempt to initialize this fragment from a string of the form fragment-type-id[=payload] The state of this instance will not be changed if this function returns false. @param InString         The string to parse. @param InParams         Additional string parameters @return Parse result, specifying success or failure, and number of characters that were parsed
- L165 _public prototype_ `FParseStringResult TryParseFragmentType(FStringView InString, const FParseStringParams& InParams);` — Attempt to default initialize this fragment using a string that defines the type The state of this instance will not be changed if this function returns false. @param InString         The string to parse. @param InParams         Additional string parameters @return Parse result, specifying success or failure, and number of characters that were parsed
- L175 _public prototype_ `FParseStringResult TryParseFragmentPayload(FStringView InString, const FParseStringParams& InParams);` — Attempt to deserialize this fragment's payload from a string, based on its currently assigned type The state of this instance will not be changed if this function returns false. @param InString         The string to parse. @param InParams         Additional string parameters @return Parse result, specifying success or failure, and number of characters that were parsed
- L186 _public prototype_ `template<typename T> T* GetPayloadAs(UE::UniversalObjectLocator::TFragmentTypeHandle<T> InType);` — Try and retrieve this fragment's payload as a specific type using its fragment type handle @param InType           The handle of the fragment type to this payload to. This is returned from IUniversalObjectLocatorModule::RegisterFragmentType on registration. @return A mutable pointer to the payload, or nullptr if this fragment is empty or of a different type.
- L195 _public prototype_ `template<typename T> const T* GetPayloadAs(UE::UniversalObjectLocator::TFragmentTypeHandle<T> InType) const;` — Try and retrieve this fragment's payload as a specific type using its fragment type handle @param InType           The handle of the fragment type to this payload to. This is returned from IUniversalObjectLocatorModule::RegisterFragmentType on registration. @return A mutable pointer to the payload, or nullptr if this fragment is empty or of a different type.
- L205 _public prototype_ `template<typename T> bool TryGetPayloadAs(UE::UniversalObjectLocator::TFragmentTypeHandle<T> InType, T*& OutData);` — Try and retrieve this fragment's payload as a specific type using its fragment type handle @param InType           The handle of the fragment type to this payload to. This is returned from IUniversalObjectLocatorModule::RegisterFragmentType on registration. @param OutData          Pointer to retrieve the resulting payload ptr @return true on success, false if this fragment is empty or of a different type.
- L215 _public prototype_ `template<typename T> bool TryGetPayloadAs(UE::UniversalObjectLocator::TFragmentTypeHandle<T> InType, const T*& OutData) const;` — Try and retrieve this fragment's payload as a specific type using its fragment type handle @param InType           The handle of the fragment type to this payload to. This is returned from IUniversalObjectLocatorModule::RegisterFragmentType on registration. @param OutData          Pointer to retrieve the resulting payload ptr @return true on success, false if this fragment is empty or of a different type.
- L222 _public prototype_ `void* GetPayload();` — Retrieve this fragment's payload data @return The payload data or nullptr if this fragment is empty
- L229 _public prototype_ `const void* GetPayload() const;` — Retrieve this fragment's payload data @return The payload data or nullptr if this fragment is empty
- L236 _public prototype_ `const UE::UniversalObjectLocator::FFragmentType* GetFragmentType() const;` — Retrieve this fragment's fragment type @return The fragment type or nullptr if this fragment is empty
- L243 _public prototype_ `UScriptStruct* GetFragmentStruct() const;` — Retrieve this fragment's fragment struct type @return The fragment struct type or nullptr if this fragment is empty
- L250 _public prototype_ `UE::UniversalObjectLocator::FFragmentTypeHandle GetFragmentTypeHandle() const;` — Retrieve this fragment's fragment type handle @return The fragment type handle (possibly invalid if this fragment is empty)
- L255 _public prototype_ `bool Serialize(FArchive& Ar);` — ~ Begin TStructOpsTypeTraits implementation
- L256 _public prototype_ `void AddStructReferencedObjects(FReferenceCollector& Collector);`
- L257 _public prototype_ `bool ExportTextItem(FString& ValueStr, const FUniversalObjectLocatorFragment& DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope) const;`
- L258 _public prototype_ `bool ImportTextItem(const TCHAR*& Buffer, int32 PortFlags, UObject* Parent, FOutputDevice* ErrorText, FArchive* InSerializingArchive = nullptr);`
- L259 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);`
- L260 _public prototype_ `void GetPreloadDependencies(TArray<UObject*>& OutDeps);`
- L269 _protected prototype_ `void CheckPayloadType(UScriptStruct* TypeToCompare) const;` — Runtime type-checking against a specific struct type. Compiled out if checks are not enabled.
- L304 _protected prototype_ `FAllocatedPayload AllocatePayload(size_t Size, size_t Alignment);` — Allocate (but do not initialize) the fragment payload using the specified size and alignment, accounting for enough space to fit a debug vftable ptr whern UE_UNIVERSALOBJECTLOCATOR_DEBUG is enabled. @return Structure identifying the payload
- L309 _protected prototype_ `void DefaultConstructPayload(const UE::UniversalObjectLocator::FFragmentType& InFragmentType);` — Default-initialize the fragment payload using the specified type
- L314 _protected prototype_ `void DestroyPayload();` — Destroy the payload (if valid) by calling its destructor and freeing the memory (if necessary)
- L318 _private function_ `uint32 GetDebugHeaderOffset() const`
- L343 _private member_ `uint8 Data[SizeInMemory-2];` — Payload data - implicitly aligned to a 8 byte boundary since it's the first member. Given payload type T, this is either a type-erased T() value (where bIsInline==1), or a T* to a heap allocated T (where bIsInline==0) SizeInMemory is specifically defined by the desired overall size of FUniversalObjectLocatorFragment::SizeInMemory, minus space for other members
- L346 _private member_ `UE::UniversalObjectLocator::FFragmentTypeHandle FragmentType;` — 1 Byte - the fragment type portion of the universal fragment
- L350 _private member_ `uint8 bIsInitialized : 1;` — True when FragmentType has been assigned to a valid handle, and Data has been initialized with FragmentType::PayloadType
- L352 _private member_ `uint8 bIsInline : 1;` — True if Data is an inline allocation of FragmentType::PayloadType, false means Data is a (void*) to the heap allocated data.
- L354 _private member_ `uint8 DebugHeaderSizeLog2 : 6;` — Offset from the allocated memory to the fragment payload stored as a power of 2. Only non-zero when UE_UNIVERSALOBJECTLOCATOR_DEBUG is enabled.
- L373 _function_ `template<typename T, typename ...ArgTypes> FUniversalObjectLocatorFragment::FUniversalObjectLocatorFragment(UE::UniversalObjectLocator::TFragmentTypeHandle<T> InHandle, ArgTypes&& ...InArgs) : FragmentType(InHandle) , bIsInitialized(0) , DebugHeaderSizeLog2(0)`
- L394 _function_ `template<typename T> T* FUniversalObjectLocatorFragment::GetPayloadAs(UE::UniversalObjectLocator::TFragmentTypeHandle<T> InType)`
- L404 _function_ `template<typename T> const T* FUniversalObjectLocatorFragment::GetPayloadAs(UE::UniversalObjectLocator::TFragmentTypeHandle<T> InType) const`
- L410 _function_ `template<typename T> bool FUniversalObjectLocatorFragment::TryGetPayloadAs(UE::UniversalObjectLocator::TFragmentTypeHandle<T> InType, T*& OutData)`
- L421 _function_ `template<typename T> bool FUniversalObjectLocatorFragment::TryGetPayloadAs(UE::UniversalObjectLocator::TFragmentTypeHandle<T> InType, const T*& OutData) const`

#### struct `FUniversalObjectLocatorFragment::FAllocatedPayload`  
`struct FAllocatedPayload`  
_L288-296_
- desc: Describes a UOL fragment payload after it has been allocated Where UE_UNIVERSALOBJECTLOCATOR_DEBUG is enabled, the allocation will be laid out as such: 0..								8..															8+sizeof(T) [TFragmentPayload<T>				| T Payload													] When UE_UNIVERSALOBJECTLOCATOR_DEBUG is disabled, the allocation is simply: 0..															sizeof(T) | T Payload													]
- L292 _public member_ `void* DebugVFTablePtr;` — Pointer to artificially inserted vtable ptr that identifies the fragment data polymorphically
- L295 _public member_ `void* Payload;` — Pointer to the actual typed fragment data

#### struct `FUniversalObjectLocatorFragment::FDebuggableFragmentType`  
`struct FDebuggableFragmentType`  
_L327-330_
- desc: ~ Utility symbol name to guarantee that FFragmentType can be resolved within the context of a FUniversalObjectLocatorFragment within natvis expressions
- L329 _public typedef_ `using Type = UE::UniversalObjectLocator::FFragmentType;`

#### struct `FUniversalObjectLocatorFragment::FDebuggableFragment`  
`struct FDebuggableFragment`  
_L331-334_
- L333 _public typedef_ `using Type = UE::UniversalObjectLocator::IFragmentPayload;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FUniversalObjectLocatorFragment> : public TStructOpsTypeTraitsBase2<FUniversalObjectLocatorFragment>`  
_L358-369_
- inherits: `TStructOpsTypeTraitsBase2<FUniversalObjectLocatorFragment>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L361-368_

#### struct `FUniversalObjectLocatorEmptyPayload`  
`struct FUniversalObjectLocatorEmptyPayload`  
_L434-437_
- reflection: `USTRUCT()`
- desc: Empty struct type used for deserializing unknown fragment type payloads

#### struct `TUniversalObjectLocatorFragment`  
`template<typename PayloadType> struct TUniversalObjectLocatorFragment : FUniversalObjectLocatorFragment`  
_L441-476_
- inherits: `FUniversalObjectLocatorFragment`
- L443 _public function_ `TUniversalObjectLocatorFragment() : FUniversalObjectLocatorFragment(PayloadType::FragmentType)`
- L448 _public function_ `TUniversalObjectLocatorFragment(UE::UniversalObjectLocator::TFragmentTypeHandle<PayloadType> InHandle) : FUniversalObjectLocatorFragment(InHandle)`
- L454 _public function_ `template<typename ...ArgTypes> TUniversalObjectLocatorFragment(ArgTypes&& ...InArgs) : FUniversalObjectLocatorFragment(PayloadType::FragmentType, Forward<ArgTypes>(InArgs)...)`
- L460 _public function_ `template<typename ...ArgTypes> TUniversalObjectLocatorFragment(UE::UniversalObjectLocator::TFragmentTypeHandle<PayloadType> InHandle, ArgTypes&& ...InArgs) : FUniversalObjectLocatorFragment(InHandle, Forward<ArgTypes>(InArgs)...)`
- L465 _public function_ `PayloadType* GetPayload()`
- L471 _public function_ `const PayloadType* GetPayload() const`

#### Free symbols / members of external scopes

- L362 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon4e98e8580103`)
- L363 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon4e98e8580103`)
- L364 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon4e98e8580103`)
- L365 _enumerator_ `WithExportTextItem = true` (scope `TStructOpsTypeTraits::__anon4e98e8580103`)
- L366 _enumerator_ `WithImportTextItem = true` (scope `TStructOpsTypeTraits::__anon4e98e8580103`)
- L367 _enumerator_ `WithAddStructReferencedObjects = true` (scope `TStructOpsTypeTraits::__anon4e98e8580103`)

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocatorFragmentDebugging.h` (Public)


#### struct `UE::UniversalObjectLocator::IFragmentPayload`  
`struct alignas(8) IFragmentPayload`  
_L22-27_
- desc: Type whose sole purpose is to add a vtable pointer in front of a fragment to assist in debugging. When allocating the fragment, a TFragmentPayload<T> is allocated in the preceeding 8 bytes which can be used by a natvis expression to show the proceeding bytes as a (T*)
- L24 _public function_ `virtual ~IFragmentPayload()`

#### struct `UE::UniversalObjectLocator::TFragmentPayload`  
`template<typename T> struct TFragmentPayload : IFragmentPayload`  
_L34-37_
- inherits: `IFragmentPayload`
- desc: Templated version of IFragmentPayload that is added to the start of a fragment. Utilizes a zero-sized array to cast the proceeding bytes to a T*.
- L36 _public member_ `UE_NO_UNIQUE_ADDRESS uint8 Ptr[];`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_UNIVERSALOBJECTLOCATOR_DEBUG !UE_BUILD_SHIPPING`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocatorFragmentType.h` (Public)


#### enum `UE::UniversalObjectLocator::EFragmentTypeFlags`  
`enum class EFragmentTypeFlags : uint8`  
_L25-40_
- L27 _public enumerator_ `None`
- L34 _public enumerator_ `CanBeLoaded = 1 << 0` — Flag to indicate that this fragment type can be loaded, indicating that asset loading or actor spawning will occur if the 'Load' flag is passed in the FResolveParams. If a fragment type can be loaded, then it will also react to resolve with the 'Unload' flag by unloading which may mean destructing an asset or destroying a spawned actor. Specific to Editor, some fragment types may spawn a 'preview' object/actor and have different behavior in runtime.
- L39 _public enumerator_ `LoadedByDefault = 1 << 1` — Flag to indicate that this fragment type should be loaded by default. This flag is used to signal to the resolver of what this fragment type expects when being resolved.

#### struct `UE::UniversalObjectLocator::FFragmentType`  
`struct FFragmentType`  
_L69-132_
- desc: A Universal Object Locator fragment type defines a specific mechanism for resolving an object that is referenced inside a Universal Object Locator (which can be considered a chain of fragments). Each fragment contains the attributes defining its payload, and how to interact that payload. In order to define a new fragment type, consumers must provide a UStruct 'payload' that defines the data required for the reference. The struct also defines how to interact with the payload via the following functions: // Initialize the fragment to point at an object within a context FInitializeResult Initialize(const FInitializeParams& InParams) const; // Resolve the fragment to the resulting object, potentially loading or unloading it FResolveResult Resolve(const FResolveParams& Params) const; // Convert this fragment to its string representation void ToString(FStringBuilderBase& OutStringBuilder) const; // Try and parse this fragment from its string representation FParseStringResult TryParseString(FStringView InString, const FParseStringParams& Params) const; // Compute a priority for this fragment based on an object and context in order to decide which fragment type should be used if multiple can address the same object static uint32 ComputePriority(const UObject* Object, const UObject* Context) const; Types must also be UStructs that are equality comparable, and GetTypeHashable. These functions are bound as function pointers on construction, allowing them potentially to be inlined into t
- L71 _public prototype_ `FResolveResult ResolvePayload(const void* Payload, const FResolveParams& Params) const;`
- L72 _public prototype_ `FInitializeResult InitializePayload(void* Payload, const FInitializeParams& InParams) const;`
- L73 _public prototype_ `void ToString(const void* Payload, FStringBuilderBase& OutStringBuilder) const;`
- L74 _public prototype_ `FParseStringResult TryParseString(void* Payload, FStringView InString, const FParseStringParams& Params) const;`
- L76 _public prototype_ `uint32 ComputePriority(const UObject* Object, const UObject* Context) const;`
- L78 _public typedef_ `using FResolveCallback = FResolveResult (*)(const void* , const FResolveParams& );`
- L79 _public typedef_ `using FInitializeCallback = FInitializeResult (*)(void* , const FInitializeParams&);`
- L80 _public typedef_ `using FToString = void (*)(const void* , FStringBuilderBase& );`
- L81 _public typedef_ `using FTryParseString = FParseStringResult (*)(void* , FStringView , const FParseStringParams& );`
- L83 _public typedef_ `using FPriorityCallback = uint32 (*)(const UObject* , const UObject* );`
- L86 _public typedef_ `using FFragmentDebugInitializer = void (*)(void*);`
- L100 _public member_ `} InstanceBindings;`
- L111 _public member_ `} StaticBindings;`
- L114 _public member_ `TObjectPtr<const UScriptStruct> PayloadType;` — Struct pointer to the payload type
- L117 _public member_ `FText DisplayText;` — Descriptive display text for this type of fragment type
- L120 _public member_ `FName FragmentTypeID;` — Unique identifier for this fragment type. This is serialized persistently to identify the fragment type, and exists as part of the fragment type's string representation
- L123 _public member_ `FName PrimaryEditorType;` — Name of the primary editor type for this fragment type, defining how it appears on UI
- L126 _public member_ `EFragmentTypeFlags Flags;` — Flags defining behavior of this fragment type
- L128 _public function_ `UScriptStruct* GetStruct() const`

#### struct `UE::UniversalObjectLocator::FFragmentType::(anonymous)`  
``  
_L91-100_

#### struct `UE::UniversalObjectLocator::FFragmentType::(anonymous)`  
``  
_L104-111_

#### struct `UE::UniversalObjectLocator::TFragmentType`  
`template<typename T> struct TFragmentType : FFragmentType`  
_L135-137_
- inherits: `FFragmentType`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)
- L93 _member_ `FInitializeCallback Initialize;` (scope `UE::UniversalObjectLocator::FFragmentType::__anona11c1b3a0108`) — Function binding for initializing a payload with this fragment type
- L95 _member_ `FResolveCallback Resolve;` (scope `UE::UniversalObjectLocator::FFragmentType::__anona11c1b3a0108`) — Function binding for resolving a payload for this fragment type
- L97 _member_ `FToString ToString;` (scope `UE::UniversalObjectLocator::FFragmentType::__anona11c1b3a0108`) — Function binding for serializing this payload to a string
- L99 _member_ `FTryParseString TryParseString;` (scope `UE::UniversalObjectLocator::FFragmentType::__anona11c1b3a0108`) — Function binding for parsing this payload from a string
- L106 _member_ `FPriorityCallback Priority;` (scope `UE::UniversalObjectLocator::FFragmentType::__anona11c1b3a0208`) — static function binding for computing the priority of this fragment type
- L109 _member_ `FFragmentDebugInitializer FragmentDebugInitializer;` (scope `UE::UniversalObjectLocator::FFragmentType::__anona11c1b3a0208`) — Function callback for initializing a vftable for the fragment for debugging purposes

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocatorFragmentTypeHandle.h` (Public)


#### struct `UE::UniversalObjectLocator::FFragmentTypeHandle`  
`struct FFragmentTypeHandle`  
_L18-76_
- desc: A handled to a globally registered Universal Object Locator fragment type. Registered through IUniversalObjectLocatorModule::RegisterFragmentType, fragment types define all the attributes for a specific type of object resolution protocol that can be represented in a UOL.
- L20 _public function_ `FFragmentTypeHandle() : Handle(0xff)`
- L25 _public function_ `explicit FFragmentTypeHandle(uint8 InHandleOffset) : Handle(InHandleOffset)`
- L31 _public function_ `explicit operator bool() const`
- L36 _public function_ `bool IsValid() const`
- L41 _public function_ `uint8 GetIndex() const`
- L71 _public prototype_ `FFragmentType* Resolve() const;`
- L75 _private member_ `uint8 Handle;` — Global index into UE::UniversalObjectLocator::FRegistry::Get().FragmentTypes

#### struct `UE::UniversalObjectLocator::TFragmentTypeHandle`  
`template<typename T> struct TFragmentTypeHandle : FFragmentTypeHandle`  
_L83-103_
- inherits: `FFragmentTypeHandle`
- desc: Typed version of FFragmentTypeHandle that provides typed access to the underlying fragment type
- L85 _public function_ `TFragmentTypeHandle()`
- L89 _public function_ `TFragmentType<T>* Resolve() const`
- L99 _private function_ `TFragmentTypeHandle(FFragmentTypeHandle InHandle) : FFragmentTypeHandle(InHandle)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)
- L46 _function_ `friend uint32 GetTypeHash(FFragmentTypeHandle In)` (scope `UE::UniversalObjectLocator`)
- L51 _function_ `friend bool operator==(FFragmentTypeHandle A, FFragmentTypeHandle B)` (scope `UE::UniversalObjectLocator`)
- L56 _function_ `friend bool operator!=(FFragmentTypeHandle A, FFragmentTypeHandle B)` (scope `UE::UniversalObjectLocator`)
- L61 _function_ `friend bool operator<(FFragmentTypeHandle A, FFragmentTypeHandle B)` (scope `UE::UniversalObjectLocator`)
- L66 _function_ `friend bool operator>(FFragmentTypeHandle A, FFragmentTypeHandle B)` (scope `UE::UniversalObjectLocator`)

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocatorFwd.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocatorInitializeParams.h` (Public)


#### struct `UE::UniversalObjectLocator::FInitializeParams`  
`struct FInitializeParams`  
_L15-36_
- desc: Fragment initialization parameter structure
- L18 _public member_ `const UObject* Object = nullptr;` — The object that should be referenced by this locator (or, in the case of transient objects, an equivalent object).
- L21 _public member_ `const UObject* Context = nullptr;` — The context within which Object will be resolved within. Maybe null.
- L25 _public function_ `template<typename T> const T* GetObjectAs() const` — Retrieve the context as a specific type.
- L32 _public function_ `template<typename T> const T* GetContextAs() const` — Retrieve the context as a specific type.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocatorInitializeResult.h` (Public)


#### enum `UE::UniversalObjectLocator::ELocatorType`  
`enum class ELocatorType : uint8`  
_L13-18_
- L15 _public enumerator_ `Absolute`
- L16 _public enumerator_ `Relative`
- L17 _public enumerator_ `Undefined`

#### struct `UE::UniversalObjectLocator::FInitializeResult`  
`struct FInitializeResult`  
_L23-54_
- desc: Fragment initialization result structure, specfying the type of locator that was created and an optional relative 'parent'
- L26 _public member_ `const UObject* RelativeToContext = nullptr;` — Optional object that this fragment should be resolved relative to
- L29 _public member_ `ELocatorType Type = ELocatorType::Undefined;` — The type of the locator fragment
- L31 _public function_ `static FInitializeResult Absolute()`
- L38 _public function_ `static FInitializeResult Relative(const UObject* InRelativeToContext)`
- L48 _public function_ `static FInitializeResult Failure()`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocatorParameterTypeHandle.h` (Public)


#### struct `UE::UniversalObjectLocator::FParameterTypeHandle`  
`struct FParameterTypeHandle`  
_L18-76_
- desc: A handle to a globally registered Universal Object Locator fragment type. Registered through IUniversalObjectLocatorModule::RegisterParameterType, fragment types define all the attributes for a specific type of object resolution protocol that can be represented in a UOL.
- L20 _public function_ `FParameterTypeHandle() : Handle(0xff)`
- L25 _public function_ `explicit FParameterTypeHandle(uint8 InHandleOffset) : Handle(InHandleOffset)`
- L31 _public function_ `explicit operator bool() const`
- L36 _public function_ `bool IsValid() const`
- L41 _public function_ `uint8 GetIndex() const`
- L71 _public prototype_ `UScriptStruct* Resolve(UScriptStruct* Expected = nullptr) const;`
- L75 _private member_ `uint8 Handle;` — Global index into UE::UniversalObjectLocator::FRegistry::Get().ParameterTypes

#### struct `UE::UniversalObjectLocator::TParameterTypeHandle`  
`template<typename T> struct TParameterTypeHandle : FParameterTypeHandle`  
_L83-103_
- inherits: `FParameterTypeHandle`
- desc: Typed version of FParameterTypeHandle that provides typed access to the underlying parameter type
- L85 _public function_ `TParameterTypeHandle()`
- L89 _public function_ `UScriptStruct* Resolve() const`
- L99 _private function_ `TParameterTypeHandle(FParameterTypeHandle InHandle) : FParameterTypeHandle(InHandle)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)
- L46 _function_ `friend uint32 GetTypeHash(FParameterTypeHandle In)` (scope `UE::UniversalObjectLocator`)
- L51 _function_ `friend bool operator==(FParameterTypeHandle A, FParameterTypeHandle B)` (scope `UE::UniversalObjectLocator`)
- L56 _function_ `friend bool operator!=(FParameterTypeHandle A, FParameterTypeHandle B)` (scope `UE::UniversalObjectLocator`)
- L61 _function_ `friend bool operator<(FParameterTypeHandle A, FParameterTypeHandle B)` (scope `UE::UniversalObjectLocator`)
- L66 _function_ `friend bool operator>(FParameterTypeHandle A, FParameterTypeHandle B)` (scope `UE::UniversalObjectLocator`)

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocatorResolveParameterBuffer.h` (Public)


#### struct `UE::UniversalObjectLocator::FResolveParameterHeader`  
`struct FResolveParameterHeader`  
_L19-35_
- desc: Header that describes an entry in the parameter buffer.
- L22 _public member_ `uint16 ParameterOffset = 0;` — 2 Bytes
- L25 _public member_ `uint8 Sizeof = 0;` — 1 Byte
- L28 _public member_ `uint8 Alignment = 0;` — 1 Byte
- L31 _public function_ `void* Resolve(void* InMemory) const` — Resolve the given raw pointer into a parameter pointer

#### struct `UE::UniversalObjectLocator::FResolveParameterBuffer`  
`struct FResolveParameterBuffer`  
_L45-160_
- desc: A buffer of parameter structs that can be optionally supplied to a UOL when resolving to supply additional context. Parameter types are registered through IUniversalObjectLocatorModule::RegisterParameterType and are identified by a unique index. Parameter structs are stored contiguously in memory after an array of headers that specify the offset of each parameter type. Checking for the presence of a specific parameter type is very fast, amounting to a a simple bit operation.
- L50 _public prototype_ `FResolveParameterBuffer();` — Default constructor
- L55 _public prototype_ `~FResolveParameterBuffer();` — Destructor that calls each parameter's destructor, and frees the memory if necessary
- L60 _public prototype_ `FResolveParameterBuffer(const FResolveParameterBuffer&) = delete;` — Non-copyable
- L61 _public prototype_ `FResolveParameterBuffer& operator=(const FResolveParameterBuffer&) = delete;`
- L66 _public prototype_ `FResolveParameterBuffer(FResolveParameterBuffer&& RHS) = delete;` — Non-moveable
- L67 _public prototype_ `FResolveParameterBuffer& operator=(FResolveParameterBuffer&& RHS) = delete;`
- L78 _public prototype_ `template<typename T> const T* FindParameter() const;` — Find a parameter of the specified type. Relies upon the struct type defining a static TParameterTypeHandle<T> called ParameterType that was previously registered through RegisterParameterType. @return A pointer to the parameter if present, nullptr otherwise
- L87 _public prototype_ `template<typename T> const T* FindParameter(TParameterTypeHandle<T> ParameterTypeHandle) const;` — Find a parameter within this container that was added with the specified handle. @return A pointer to the parameter if present, nullptr otherwise
- L99 _public prototype_ `template<typename T, typename ...ArgTypes> T* AddParameter(TParameterTypeHandle<T> ParameterTypeHandle, ArgTypes&&... InArgs);` — Add a new parameter to this container using its preregistered type handle. This function is accepts 0 or more additional construction arguments which are passed to the parameter's constructor. @note: The definition of this function is located in UniversalObjectLocatorResolveParameterBuffer.inl @return A pointer to the parameter if present, nullptr otherwise
- L106 _protected prototype_ `bool HasParameter(uint32 ParameterBit) const;` — Check whether the parameter for the specified parameter bit is present
- L111 _protected prototype_ `const void* FindParameterImpl(uint32 ParameterBit) const;` — Implementation function for finding a parameter ptr by its bit
- L120 _protected prototype_ `template<typename ParameterType, typename ...ArgTypes> ParameterType* AddParameterImpl(uint32 ParameterBit, ArgTypes&&... InArgs);` — Creates and stores a new Parameter object at the given bit. @note: The definition of this function is located in UniversalObjectLocatorResolveParameterBuffer.inl
- L126 _protected prototype_ `const FResolveParameterHeader& GetHeader(uint8 Index) const;` — Retrieve the header at the specified index
- L132 _protected prototype_ `int32 GetParameterIndex(uint32 ParameterBit) const;` — Compute the index of the parameter that relates to the specified bit
- L138 _protected prototype_ `void Destroy();` — Destroy this buffer and all its parameters
- L143 _protected member_ `uint8* Memory = nullptr;` — Memory allocation of the layout [header_1|...|header_n|entry_0|...|entry_n]
- L146 _protected member_ `uint32 AllParameters = 0u;` — Bitmask of all the parameters contained within this container
- L149 _protected member_ `uint16 Capacity = 0u;` — Current capacity of Memory in bytes
- L152 _protected member_ `uint8 Num = 0u;` — The number of parameters (and thus, headers) in this container
- L155 _protected member_ `bool bCanFreeMemory = false;` — Boolean that indicates whether we own the memory pointed to by Memory, or if it was supplied externally
- L159 _public member_ `static constexpr int32 MaxNumParameters = sizeof(AllParameters) * 8;`
- L184 _function_ `template<typename T> const T* FResolveParameterBuffer::FindParameter() const`
- L190 _function_ `template<typename T> const T* FResolveParameterBuffer::FindParameter(TParameterTypeHandle<T> ParameterTypeHandle) const`
- L198 _function_ `inline bool FResolveParameterBuffer::HasParameter(uint32 ParameterBit) const`
- L203 _function_ `inline const void* FResolveParameterBuffer::FindParameterImpl(uint32 ParameterBit) const`
- L215 _function_ `inline const FResolveParameterHeader& FResolveParameterBuffer::GetHeader(uint8 Index) const`
- L221 _function_ `inline int32 FResolveParameterBuffer::GetParameterIndex(uint32 ParameterBit) const`

#### struct `UE::UniversalObjectLocator::TInlineResolveParameterBuffer`  
`template<int InlineByteSize> struct alignas(8) TInlineResolveParameterBuffer : FResolveParameterBuffer`  
_L166-180_
- inherits: `FResolveParameterBuffer`
- desc: A FResolveParameterBuffer that has an inline memory capacity of the specified size
- L168 _public function_ `TInlineResolveParameterBuffer()`
- L179 _private member_ `uint8 InlineBuffer[InlineByteSize];` — Inline memory buffer

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocatorResolveParameterBuffer.inl` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)
- L12 _function_ `template<typename T, typename ...ArgTypes> T* FResolveParameterBuffer::AddParameter(TParameterTypeHandle<T> ParameterTypeHandle, ArgTypes&&... InArgs)` (scope `UE::UniversalObjectLocator::FResolveParameterBuffer`)
- L28 _function_ `template<typename ParameterType, typename ...ArgTypes> ParameterType* FResolveParameterBuffer::AddParameterImpl(uint32 ParameterBit, ArgTypes&&... InArgs)` (scope `UE::UniversalObjectLocator::FResolveParameterBuffer`)
- L113 _function_ `` (scope `UE::UniversalObjectLocator::FResolveParameterBuffer::AddParameterImpl`)

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocatorResolveParams.h` (Public)


#### enum `ELocatorResolveFlags`  
`enum class ELocatorResolveFlags : uint8`  
_L15-37_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- L17 _public enumerator_ `None`
- L20 _public enumerator_ `Load = 1 << 0` — Flag to indicate whether the object should be loaded if it is not currently findable
- L23 _public enumerator_ `Unload = 1 << 1` — Flag to indicate whether the object should be unloaded or destroyed. Mutually exclusive with bLoad.
- L30 _public enumerator_ `Async = 1 << 2` — Indicates that the operation should be performed asynchronously if possible. When not combined with WillWait, the caller will never block waiting for the result. When combined with WillWait, the caller will block on this thread until the result is available, so care needs to be taken avoid a deadlock if there are additional threading constraints on the load.
- L33 _public enumerator_ `WillWait = 1 << 3` — Indicates the calling code is going to block waiting for the result.
- L36 _public enumerator_ `AsyncWait = Async | WillWait` — Combination of Async and WillWait.

#### struct `UE::UniversalObjectLocator::FResolveParams`  
`struct FResolveParams`  
_L46-137_
- desc: Parameters required to resolve a universal object locator
- L48 _public function_ `FResolveParams() : Context(nullptr) , ParameterBuffer(nullptr) , Flags(ELocatorResolveFlags::None)`
- L55 _public function_ `FResolveParams(UObject* InContext) : Context(InContext) , ParameterBuffer(nullptr) , Flags(ELocatorResolveFlags::None)`
- L62 _public function_ `FResolveParams(UObject* InContext, ELocatorResolveFlags InFlags) : Context(InContext) , ParameterBuffer(nullptr) , Flags(InFlags)`
- L70 _public function_ `template<typename T> const T* FindParameter() const`
- L76 _public function_ `template<typename T> const T* FindParameter(TParameterTypeHandle<T> ParameterType) const`
- L84 _public function_ `static FResolveParams AsyncFind(UObject* InContext = nullptr)` — Utility function to indicate that the object should be found, but not loaded or created if it is not currently
- L92 _public function_ `static FResolveParams AsyncLoad(UObject* InContext = nullptr)` — Utility function to indicate that the object should be loaded (or dynamically created) if it is not currently
- L100 _public function_ `static FResolveParams AsyncUnload(UObject* InContext)` — Utility function to indicate that the object should be unloaded (or dynamically destroyed) if it is not currently
- L108 _public function_ `static FResolveParams SyncFind(UObject* InContext = nullptr)` — Utility function to indicate that the object should be found, but not loaded or created if it is not currently
- L116 _public function_ `static FResolveParams SyncLoad(UObject* InContext = nullptr)` — Utility function to indicate that the object should be loaded (or dynamically created) if it is not currently
- L124 _public function_ `static FResolveParams SyncUnload(UObject* InContext)` — Utility function to indicate that the object should be unloaded (or dynamically destroyed) if it is not currently
- L130 _public member_ `UObject* Context;` — (Optional) Object to use as a context for resolution. Normally this is the object that owns the reference being resolved
- L133 _public member_ `FResolveParameterBuffer* ParameterBuffer;` — (Optional) Resolve buffer
- L136 _public member_ `ELocatorResolveFlags Flags;` — Flag structure

#### struct `UE::UniversalObjectLocator::TResolveParamsWithBuffer`  
`template<int InlineSize> struct TResolveParamsWithBuffer : TInlineResolveParameterBuffer<InlineSize>, FResolveParams`  
_L140-158_
- inherits: `TInlineResolveParameterBuffer<InlineSize>,FResolveParams`
- L142 _public function_ `TResolveParamsWithBuffer()`
- L147 _public function_ `TResolveParamsWithBuffer(UObject* InContext) : FResolveParams(InContext)`
- L153 _public function_ `TResolveParamsWithBuffer(UObject* InContext, ELocatorResolveFlags InFlags) : FResolveParams(InContext, InFlags)`

#### struct `UE::UniversalObjectLocator::FResolveResultFlags`  
`struct FResolveResultFlags`  
_L166-178_
- desc: Flag structure returned from an attempt to resolve a Universal Object Locator
- L168 _public function_ `FResolveResultFlags() : bWasLoaded(0) , bWasLoadedIndirectly(0)`
- L175 _public member_ `uint8 bWasLoaded : 1;` — Indicates the object was loaded as a result of this request
- L177 _public member_ `uint8 bWasLoadedIndirectly : 1;` — Indicates that an outer object was loaded in order to fulfil this request, and the final object itself was loaded as a result

#### struct `UE::UniversalObjectLocator::FResolveResultData`  
`struct FResolveResultData`  
_L180-201_
- L182 _public function_ `FResolveResultData() : Object(nullptr)`
- L187 _public function_ `FResolveResultData(UObject* InObject, FResolveResultFlags InFlags = FResolveResultFlags()) : Object(InObject) , Flags(InFlags)`
- L197 _public member_ `UObject* Object = nullptr;` — The resulting object or nullptr if it could not be found or loaded per the request params. Should only be set if Params.Flags.bAsync is false.
- L200 _public member_ `FResolveResultFlags Flags;` — Flags relating to the operation

#### struct `UE::UniversalObjectLocator::FResolveResult`  
`struct FResolveResult`  
_L204-335_
- L206 _public function_ `FResolveResult() : Value(TInPlaceType<FResolveResultData>())`
- L211 _public function_ `FResolveResult(FResolveResultData InValue) : Value(TInPlaceType<FResolveResultData>(), MoveTemp(InValue))`
- L216 _public function_ `FResolveResult(TFuture<FResolveResultData>&& InFuture) : Value(TInPlaceType<TFuture<FResolveResultData>>(), MoveTemp(InFuture))`
- L221 _public prototype_ `FResolveResult(const FResolveResult&) = delete;`
- L222 _public prototype_ `void operator=(const FResolveResult&) = delete;`
- L224 _public prototype_ `FResolveResult(FResolveResult&&) = default;`
- L225 _public prototype_ `FResolveResult& operator=(FResolveResult&&) = default;`
- L232 _public function_ `bool IsAsync() const` — Check whether this result is asynchronous
- L242 _public function_ `TFuture<FResolveResultData> ReleaseFuture()` — Release the future from this type if it is set. WARNING: This can only be called once per instance. Invalidates this class. @return This result's future, or an empty one if the result has already been applied.
- L255 _public function_ `bool NeedsWait() const` — Check whether the result needs to be waited on. @return true if the result hasn't been set yet: SyncGet will block, and SyncGetNoWait will return null. If false, SyncGet will always return immediately, and SyncGetNoWait will never return null.
- L267 _public function_ `const FResolveResultData* SyncGetNoWait()` — Retrieve the result if it is currently available without waiting. Returns null if it is still being processed.
- L287 _public function_ `FResolveResultData SyncGet() const` — Retrieve the result, blocking this thread if necessary.
- L304 _public function_ `void AsyncGet(TUniqueFunction<void(const FResolveResultData&)>&& OnComplete)` — Retrieve this result asynchronously. WARNING: This can only be called once per instance.
- L334 _private member_ `> Value;`

#### Free symbols / members of external scopes

- L40 _namespace_ `namespace UE`
- L40 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)
- L317 _function_ `` (scope `UE::UniversalObjectLocator::FResolveResult::AsyncGet`)

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocatorStringParams.h` (Public)


#### enum `UE::UniversalObjectLocator::EParseStringFlags`  
`enum class EParseStringFlags : uint8`  
_L13-19_
- L15 _public enumerator_ `None = 0`
- L18 _public enumerator_ `ErrorMessaging = 1 << 0` — Whether the user desires error messages to be emited

#### struct `UE::UniversalObjectLocator::FParseStringParams`  
`struct FParseStringParams`  
_L25-34_
- desc: String parameter structure specifying additional information required for a string to be parsed
- L28 _public member_ `EParseStringFlags Flags = EParseStringFlags::None;` — Parse flags
- L30 _public function_ `bool NeedsErrorMessaging() const`

#### struct `UE::UniversalObjectLocator::FParseStringResult`  
`struct FParseStringResult`  
_L42-79_
- desc: String parse result structure, specfying success/failure, number of characters that were parsed, and any error information.
- L45 _public member_ `FText ErrorMessage;` — Optional error message, only populated when FParseStringParams::bWantsErrorMessaging is true
- L50 _public member_ `int32 NumCharsParsed = 0;` — The number of characters that were parsed. On Success this indicates the last character that resulted in the successful parse, on failure, this may be 0, or the point at which parsing finished
- L53 _public member_ `bool bSuccess = false;` — Whether parsing was successful or not
- L55 _public function_ `explicit operator bool() const`
- L60 _public function_ `FParseStringResult& Success(int32 AdditionalNumCharsParsed = 0)`
- L67 _public function_ `FParseStringResult& Failure(const FText& InFailureText)`
- L78 _public prototype_ `FStringView Progress(FStringView CurrentString, int32 NumToProgress);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)
- L36 _macro_ `#define UE_UOL_PARSE_ERROR(InParams, ...) InParams.NeedsErrorMessaging() ? (__VA_ARGS__) : FText()`

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocatorStringUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)
- L11 _prototype_ `bool ParseUnsignedInteger(FStringView InString, uint32& OutResult, int32* OutNumCharsParsed = nullptr);` (scope `UE::UniversalObjectLocator`)

### `Source/Runtime/UniversalObjectLocator/Public/UniversalObjectLocatorType.h` (Public)


#### enum `UE::UniversalObjectLocator::ELocatorFragmentType`  
`enum class ELocatorFragmentType : uint8`  
_L11-16_
- L13 _public enumerator_ `Absolute`
- L14 _public enumerator_ `Relative`
- L15 _public enumerator_ `Undefined`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UniversalObjectLocator` (scope `UE`)
