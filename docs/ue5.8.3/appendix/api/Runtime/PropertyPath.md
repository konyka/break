# Runtime / PropertyPath

- module root: `Source/Runtime/PropertyPath`
- headers: 2; symbols: 211
- symbol kinds: enum=1, enumerator=1, function=86, member=16, namespace=3, prototype=74, struct=30
- PrivateDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/PropertyPath/Public/PropertyPathHelpers.h` (Public)


#### struct `FPropertyPathSegment`  
`struct FPropertyPathSegment`  
_L27-86_
- reflection: `USTRUCT()`
- desc: Base class for cached property path segments
- L34 _public prototype_ `FPropertyPathSegment();` — UStruct boilerplate constructor - do not use
- L37 _public prototype_ `FPropertyPathSegment(int32 InCount, const TCHAR* InString);` — Construct from char count and storage
- L42 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Called after this event has been serialized in order to cache the field pointer if necessary
- L45 _public prototype_ `static FPropertyPathSegment MakeUnresolvedCopy(const FPropertyPathSegment& ToCopy);` — Make a copy which is unresolved
- L51 _public prototype_ `FFieldVariant Resolve(UStruct* InStruct) const;` — Resolves the name on the given Struct.  Can be used to cache the resulting property so that future calls can be processed quickly. @param InStruct the ScriptStruct or Class to look for the property on.
- L54 _public prototype_ `FName GetName() const;` — @return the name of this segment
- L57 _public prototype_ `int32 GetArrayIndex() const;` — @return the array index of this segment
- L60 _public prototype_ `FFieldVariant GetField() const;` — @return the resolved field
- L63 _public prototype_ `UStruct* GetStruct() const;` — @return the resolved struct
- L69 _public member_ `FName Name;` — `UPROPERTY()` — The sub-component of the property path, a single value between .'s of the path
- L73 _public member_ `int32 ArrayIndex;` — `UPROPERTY()` — The optional array index.
- L79 _private member_ `mutable TObjectPtr<UStruct> Struct;` — `UPROPERTY(Transient)` — The cached Class or ScriptStruct that was used last to resolve Name to a property.
- L85 _private member_ `mutable FFieldVariant Field;` — The cached property on the Struct that this Name resolved to on it last time Resolve was called, if the Struct doesn't change, this value is returned to avoid performing another Field lookup.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPropertyPathSegment> : TStructOpsTypeTraitsBase2<FPropertyPathSegment>`  
_L89-92_
- inherits: `TStructOpsTypeTraitsBase2<FPropertyPathSegment>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L91-91_

#### struct `FCachedPropertyPath`  
`struct FCachedPropertyPath`  
_L96-247_
- reflection: `USTRUCT()`
- desc: Base class for cached property paths
- L101 _public prototype_ `FCachedPropertyPath();` — UStruct boilerplate constructor - do not use
- L104 _public prototype_ `FCachedPropertyPath(const FString& Path);`
- L107 _public prototype_ `FCachedPropertyPath(const FPropertyPathSegment& Segment);`
- L110 _public prototype_ `FCachedPropertyPath(const TArray<FString>& PathSegments);`
- L113 _public prototype_ `FCachedPropertyPath(const FPropertyChangedChainEvent& PropertyChangedChainEvent);` — Allows constructing a cached property path from the standard events of a PostEditChange Notify or Callback
- L114 _public prototype_ `FCachedPropertyPath(const FPropertyChangedEvent& PropertyChangedEvent, const FEditPropertyChain& PropertyChain);`
- L117 _public prototype_ `~FCachedPropertyPath();`
- L120 _public function_ `bool IsValid() const` — Check whether this property path is non-empty
- L123 _public prototype_ `void MakeFromString(const FString& InPropertyPath);` — Make a new property path from a string
- L126 _public prototype_ `void MakeFromChangeEvent(const FPropertyChangedChainEvent& PropertyChangedChainEvent);` — Make a new property path from the chain of properties that come standard in PostEditPropertyChain events
- L127 _public prototype_ `void MakeFromChangeEvent(const FPropertyChangedEvent& PropertyChangedEvent, const FEditPropertyChain& PropertyChain);`
- L130 _public prototype_ `static FCachedPropertyPath MakeUnresolvedCopy(const FCachedPropertyPath& ToCopy);` — Make a copy which is unresolved
- L133 _public prototype_ `FCachedPropertyPath MakeParentPath() const;` — Make a copy without the last segment, if the path is resolved, the new path is also resolved.
- L136 _public prototype_ `int32 GetNumSegments() const;` — @return Get the number of segments in this path
- L143 _public prototype_ `const FPropertyPathSegment& GetSegment(int32 InSegmentIndex) const;` — Get the path segment at the specified index @param	InSegmentIndex	The index of the segment @return the segment at the specified index
- L149 _public prototype_ `const FPropertyPathSegment& GetLastSegment() const;` — Get the path segment at the end of the path @return the segment at the specified index
- L155 _public prototype_ `bool Resolve(UObject* InContainer) const;` — Resolve this property path against the specified object. @return true if the path could be resolved
- L158 _public prototype_ `void SetCanSafelyUsedCachedAddress(bool bInCanSafelyUsedCachedAddress) const;` — Set whether this path resolves over object or dynamic array boundaries, making it unsafe for general direct cached access
- L161 _public prototype_ `void SetCachedLastContainer(void* InContainer, int32 InIndex) const;` — Update cached last container property in path & correspondng index, invalidates 'bCanSafelyUsedCachedAddress'
- L164 _public prototype_ `void* GetCachedLastContainerInPath() const;` — Get cached last container property in path
- L167 _public prototype_ `int32 GetCachedLastContainerInPathIndex() const;` — Get cached index of last container property in path, INDEX_NONE if last container is not in path
- L170 _public prototype_ `void ResolveLeaf(void* InAddress) const;` — Cache a resolved address for faster subsequent access
- L173 _public prototype_ `void ResolveLeaf(UFunction* InFunction) const;` — Cache a resolved function for faster subsequent access
- L180 _public prototype_ `bool IsResolved() const;` — Check whether a path is resolved. This means that it has a cached address, but may resolve over an object boundary or a dynamic array. @return true if the path is resolved
- L187 _public prototype_ `bool IsFullyResolved() const;` — Check whether a path is fully resolved. This means that it has a cached address and does not resolve over an object boundary or a dynamic array. @return true if the path is fully resolved
- L190 _public prototype_ `void* GetCachedAddress() const;` — Get the cached address for this property path, if any
- L193 _public prototype_ `UFunction* GetCachedFunction() const;` — Get the cached function for this property path, if any
- L196 _public prototype_ `FPropertyChangedEvent ToPropertyChangedEvent(EPropertyChangeType::Type InChangeType) const;` — Convert this property path to a FPropertyChangedEvent. Note that the path must be resolved.
- L199 _public prototype_ `void ToEditPropertyChain(FEditPropertyChain& OutPropertyChain) const;` — Convert this property path to a FEditPropertyChain. Note that the path must be resolved.
- L202 _public prototype_ `FString ToString() const;` — Make a string representation of this property path
- L205 _public prototype_ `bool operator==(const FString& Other) const;` — Compares this property path to a string
- L208 _public prototype_ `bool Equals(const FString& Other) const;` — Compares this property path to a string
- L211 _public prototype_ `void* GetCachedContainer() const;` — Get the cached container for this property path, for checking purposes
- L214 _public prototype_ `void SetCachedContainer(void* InContainer) const;` — Set the cached container for this property path, for checking purposes
- L217 _public prototype_ `void RemoveFromEnd(int32 InNumSegments = 1);` — Trims this property path at the end
- L220 _public prototype_ `void RemoveFromStart(int32 InNumSegments = 1);` — Trims this property path at the start
- L223 _public prototype_ `FProperty* GetFProperty() const;` — Returns FProperty if valid. This can be UFunction
- L227 _private member_ `TArray<FPropertyPathSegment> Segments;` — `UPROPERTY()` — Path segments for this path
- L230 _private member_ `mutable void* CachedAddress;` — Cached read/write address for property-terminated paths
- L234 _private member_ `mutable TObjectPtr<UFunction> CachedFunction;` — `UPROPERTY()` — Cached function for function-terminated paths
- L237 _private member_ `mutable void* CachedContainer;` — Cached container
- L240 _private member_ `mutable void* CachedLastContainerInPath;` — Cached last container
- L243 _private member_ `mutable int32 CachedLastContainerInPathIndex;` — Index of last container property in path, INDEX_NONE if last container is not in path
- L246 _private member_ `mutable bool bCanSafelyUsedCachedAddress;` — Whether this path resolves over object or dynamic array boundaries, making it unsafe for general direct cached access

#### struct `PropertyPathHelpersInternal::FPropertyPathResolver`  
`struct FPropertyPathResolver`  
_L630-643_
- desc: Base class for resolving property paths
- L633 _public prototype_ `virtual ~FPropertyPathResolver() = default;` — Virtual destructor
- L641 _public prototype_ `virtual bool Resolve(void* InContainer, const FCachedPropertyPath& InPropertyPath) = 0;` — Callbacks for a leaf segment in a property path iteration. Used to resolve the property path. @param InContainer			The containing object/structure for the current path iteration @param InPropertyPath		The property path to resolve @return true if the iteration should continue.
- L642 _public prototype_ `virtual bool Resolve(UObject* InContainer, const FCachedPropertyPath& InPropertyPath) = 0;`

#### struct `PropertyPathHelpersInternal::FPropertyStructView`  
`struct FPropertyStructView`  
_L646-656_
- desc: Helper struct to represent a view of a struct, used to specialize behavior against
- L648 _public function_ `explicit FPropertyStructView(const UScriptStruct* InScriptStruct, const uint8* InMemory) : ScriptStruct(InScriptStruct) , Memory(InMemory)`
- L654 _public member_ `const UScriptStruct* ScriptStruct;`
- L655 _public member_ `const uint8* Memory;`

#### struct `PropertyPathHelpersInternal::TPropertyPathResolver`  
`template<typename DerivedType> struct TPropertyPathResolver : public FPropertyPathResolver`  
_L660-671_
- inherits: `FPropertyPathResolver`
- desc: Recurring template allowing derived types to only implement templated Resolve_Impl
- L662 _public function_ `virtual bool Resolve(void* InContainer, const FCachedPropertyPath& InPropertyPath) override`
- L667 _public function_ `virtual bool Resolve(UObject* InContainer, const FCachedPropertyPath& InPropertyPath) override`

#### struct `PropertyPathHelpersInternal::FCallGetterFunctionHelper`  
`template<typename T, typename ContainerType> struct FCallGetterFunctionHelper`  
_L688-695_
- desc: Non-UObject helper struct for GetValue function calls
- L690 _public function_ `static bool CallGetterFunction(ContainerType* InContainer, UFunction* InFunction, T& OutValue)`
- L701 _public function_ `static bool CallGetterFunction(UObject* InContainer, UFunction* InFunction, T& OutValue)`

#### struct `PropertyPathHelpersInternal::FCallGetterFunctionHelper`  
`template<typename T> struct FCallGetterFunctionHelper<T, UObject>`  
_L699-735_
- desc: UObject partial specialization of FCallGetterFunctionHelper
- L690 _public function_ `static bool CallGetterFunction(ContainerType* InContainer, UFunction* InFunction, T& OutValue)`
- L701 _public function_ `static bool CallGetterFunction(UObject* InContainer, UFunction* InFunction, T& OutValue)`

#### struct `PropertyPathHelpersInternal::FGetValueHelper`  
`template<typename T, typename ContainerType> struct FGetValueHelper`  
_L739-769_
- desc: Helper function used to get a value
- L741 _public function_ `static bool GetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, T& OutValue, FProperty*& OutProperty)`
- L775 _public function_ `static bool GetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, T(&OutValue)[N], FProperty*& OutProperty)`
- L803 _public function_ `static bool GetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, bool& OutValue, FProperty*& OutProperty)`

#### struct `PropertyPathHelpersInternal::FGetValueHelper`  
`template<typename T, typename ContainerType, int32 N> struct FGetValueHelper<T[N], ContainerType>`  
_L773-797_
- desc: Partial specialization for arrays
- L741 _public function_ `static bool GetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, T& OutValue, FProperty*& OutProperty)`
- L775 _public function_ `static bool GetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, T(&OutValue)[N], FProperty*& OutProperty)`
- L803 _public function_ `static bool GetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, bool& OutValue, FProperty*& OutProperty)`

#### struct `PropertyPathHelpersInternal::FGetValueHelper`  
`template<typename ContainerType> struct FGetValueHelper<bool, ContainerType>`  
_L801-828_
- desc: Partial specialization for bools/bitfields
- L741 _public function_ `static bool GetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, T& OutValue, FProperty*& OutProperty)`
- L775 _public function_ `static bool GetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, T(&OutValue)[N], FProperty*& OutProperty)`
- L803 _public function_ `static bool GetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, bool& OutValue, FProperty*& OutProperty)`

#### struct `PropertyPathHelpersInternal::FInternalGetterResolver`  
`template<typename T> struct FInternalGetterResolver : public TPropertyPathResolver<FInternalGetterResolver<T>>`  
_L905-921_
- inherits: `TPropertyPathResolver<FInternalGetterResolver<T>>`
- L907 _public function_ `FInternalGetterResolver(T& InValue, FProperty*& InOutProperty) : Value(InValue) , Property(InOutProperty)`
- L914 _public function_ `template<typename ContainerType> bool Resolve_Impl(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath)`
- L919 _public member_ `T& Value;`
- L920 _public member_ `FProperty*& Property;`

#### struct `PropertyPathHelpersInternal::FCallSetterFunctionHelper`  
`template<typename T, typename ContainerType> struct FCallSetterFunctionHelper`  
_L925-932_
- desc: Non-UObject helper struct for SetValue function calls
- L927 _public function_ `static bool CallSetterFunction(ContainerType* InContainer, UFunction* InFunction, const T& InValue)`
- L938 _public function_ `static bool CallSetterFunction(UObject* InContainer, UFunction* InFunction, const T& InValue)`

#### struct `PropertyPathHelpersInternal::FCallSetterFunctionHelper`  
`template<typename T> struct FCallSetterFunctionHelper<T, UObject>`  
_L936-976_
- desc: UObject partial specialization of FCallSetterFunctionHelper
- L927 _public function_ `static bool CallSetterFunction(ContainerType* InContainer, UFunction* InFunction, const T& InValue)`
- L938 _public function_ `static bool CallSetterFunction(UObject* InContainer, UFunction* InFunction, const T& InValue)`

#### struct `PropertyPathHelpersInternal::FSetValueHelper`  
`template<typename T, typename ContainerType> struct FSetValueHelper`  
_L980-1032_
- desc: Helper function used to set a value
- L982 _public function_ `static bool SetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, const T& InValue)`
- L1038 _public function_ `static bool SetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, const T(&InValue)[N])`
- L1066 _public function_ `static bool SetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, const bool& InValue)`

#### struct `PropertyPathHelpersInternal::FSetValueHelper`  
`template<typename T, typename ContainerType, int32 N> struct FSetValueHelper<T[N], ContainerType>`  
_L1036-1060_
- desc: Partial specialization for arrays
- L982 _public function_ `static bool SetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, const T& InValue)`
- L1038 _public function_ `static bool SetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, const T(&InValue)[N])`
- L1066 _public function_ `static bool SetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, const bool& InValue)`

#### struct `PropertyPathHelpersInternal::FSetValueHelper`  
`template<typename ContainerType> struct FSetValueHelper<bool, ContainerType>`  
_L1064-1101_
- desc: Partial specialization for bools/bitfields
- L982 _public function_ `static bool SetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, const T& InValue)`
- L1038 _public function_ `static bool SetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, const T(&InValue)[N])`
- L1066 _public function_ `static bool SetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, const bool& InValue)`

#### struct `PropertyPathHelpersInternal::FInternalSetterResolver`  
`template<typename T> struct FInternalSetterResolver : public TPropertyPathResolver<FInternalSetterResolver<T>>`  
_L1199-1213_
- inherits: `TPropertyPathResolver<FInternalSetterResolver<T>>`
- L1201 _public function_ `FInternalSetterResolver(const T& InValueToSet) : Value(InValueToSet)`
- L1207 _public function_ `template<typename ContainerType> bool Resolve_Impl(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath)`
- L1212 _public member_ `const T& Value;`

#### struct `PropertyPathHelpersInternal::FGetValueFastHelper`  
`template<typename T> struct FGetValueFastHelper`  
_L1255-1284_
- desc: Helper function used to get a value from an already-resolved property path
- L1257 _public function_ `static bool GetValue(const FCachedPropertyPath& InPropertyPath, T& OutValue, FProperty*& OutProperty)`
- L1290 _public function_ `static bool GetValue(const FCachedPropertyPath& InPropertyPath, T(&OutValue)[N], FProperty*& OutProperty)`

#### struct `PropertyPathHelpersInternal::FGetValueFastHelper`  
`template<typename T, int32 N> struct FGetValueFastHelper<T[N]>`  
_L1288-1301_
- desc: Partial specialization for arrays
- L1257 _public function_ `static bool GetValue(const FCachedPropertyPath& InPropertyPath, T& OutValue, FProperty*& OutProperty)`
- L1290 _public function_ `static bool GetValue(const FCachedPropertyPath& InPropertyPath, T(&OutValue)[N], FProperty*& OutProperty)`

#### struct `PropertyPathHelpersInternal::FSetValueFastHelper`  
`template<typename T> struct FSetValueFastHelper`  
_L1328-1389_
- desc: Helper function used to set a value from an already-resolved property path
- L1330 _public function_ `static bool SetValue(const FCachedPropertyPath& InPropertyPath, const T& InValue)`
- L1395 _public function_ `static bool SetValue(const FCachedPropertyPath& InPropertyPath, const T(&InValue)[N])`
- L1412 _public function_ `static bool SetValue(const FCachedPropertyPath& InPropertyPath, const bool& InValue)`

#### struct `PropertyPathHelpersInternal::FSetValueFastHelper`  
`template<typename T, int32 N> struct FSetValueFastHelper<T[N]>`  
_L1393-1406_
- desc: Partial specialization for arrays
- L1330 _public function_ `static bool SetValue(const FCachedPropertyPath& InPropertyPath, const T& InValue)`
- L1395 _public function_ `static bool SetValue(const FCachedPropertyPath& InPropertyPath, const T(&InValue)[N])`
- L1412 _public function_ `static bool SetValue(const FCachedPropertyPath& InPropertyPath, const bool& InValue)`

#### struct `PropertyPathHelpersInternal::FSetValueFastHelper`  
`template<> struct FSetValueFastHelper<bool>`  
_L1410-1442_
- desc: Explicit specialization for bools/bitfields
- L1330 _public function_ `static bool SetValue(const FCachedPropertyPath& InPropertyPath, const T& InValue)`
- L1395 _public function_ `static bool SetValue(const FCachedPropertyPath& InPropertyPath, const T(&InValue)[N])`
- L1412 _public function_ `static bool SetValue(const FCachedPropertyPath& InPropertyPath, const bool& InValue)`

#### Free symbols / members of external scopes

- L91 _enumerator_ `enum { WithPostSerialize = true };` (scope `TStructOpsTypeTraits::__anon37ff69b30103`)
- L250 _namespace_ `namespace PropertyPathHelpersInternal`
- L257 _prototype_ `bool ResolvePropertyPath(UObject* InContainer, const FString& InPropertyPath, FPropertyPathResolver& InResolver);` (scope `PropertyPathHelpersInternal`)
- L258 _prototype_ `bool ResolvePropertyPath(UObject* InContainer, const FCachedPropertyPath& InPropertyPath, FPropertyPathResolver& InResolver);` (scope `PropertyPathHelpersInternal`)
- L259 _prototype_ `bool ResolvePropertyPath(void* InContainer, UStruct* InStruct, const FString& InPropertyPath, FPropertyPathResolver& InResolver);` (scope `PropertyPathHelpersInternal`)
- L260 _prototype_ `bool ResolvePropertyPath(void* InContainer, UStruct* InStruct, const FCachedPropertyPath& InPropertyPath, FPropertyPathResolver& InResolver);` (scope `PropertyPathHelpersInternal`)
- L261 _prototype_ `template<typename T, typename ContainerType> bool GetValueFast(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, T& OutValue, FProperty*& OutProperty);` (scope `PropertyPathHelpersInternal`)
- L262 _prototype_ `template<typename T, typename ContainerType> bool GetValueFast(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, T& OutValue, FProperty*& OutProperty);` (scope `PropertyPathHelpersInternal`)
- L266 _namespace_ `namespace PropertyPathHelpers`
- L275 _prototype_ `bool GetPropertyValueAsString(UObject* InContainer, const FString& InPropertyPath, FString& OutValue, uint32 PPF_Flags = PPF_None);` (scope `PropertyPathHelpers`) — Get the value represented by this property path as a string @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path string @param	OutValue		The string to write the properties value to @return true if the property value was successfully copied
- L285 _prototype_ `bool GetPropertyValueAsString(UObject* InContainer, const FString& InPropertyPath, FString& OutValue, FProperty*& OutProperty, uint32 PPF_Flags = PPF_None);` (scope `PropertyPathHelpers`) — Get the value represented by this property path as a string @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path string @param	OutValue		The string to write the properties value to @param	OutProperty		The leaf property that the path resolved to @return true if the property value was successfully copied
- L295 _prototype_ `bool GetPropertyValueAsString(void* InContainer, UStruct* InStruct, const FString& InPropertyPath, FString& OutValue, uint32 PPF_Flags = PPF_None);` (scope `PropertyPathHelpers`) — Get the value represented by this property path as a string @param	InContainer		A pointer to the container structure to resolve the property path against @param	InStruct		The struct type that InContainer points to @param	InPropertyPath	The property path string @param	OutValue		The string to write the properties value to @return true if the property value was successfully copied
- L306 _prototype_ `bool GetPropertyValueAsString(void* InContainer, UStruct* InStruct, const FString& InPropertyPath, FString& OutValue, FProperty*& OutProperty, uint32 PPF_Flags = PPF_None);` (scope `PropertyPathHelpers`) — Get the value represented by this property path as a string @param	InContainer		A pointer to the container structure to resolve the property path against @param	InStruct		The struct type that InContainer points to @param	InPropertyPath	The property path string @param	OutValue		The string to write the properties value to @param	OutProperty		The leaf property that the path resolved to @return true if the property value was successfully copied
- L315 _prototype_ `bool GetPropertyValueAsString(UObject* InContainer, const FCachedPropertyPath& InPropertyPath, FString& OutValue, uint32 PPF_Flags = PPF_None);` (scope `PropertyPathHelpers`) — Get the value represented by this property path as a string @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path @param	OutValue		The string to write the properties value to @return true if the property value was successfully copied
- L325 _prototype_ `bool GetPropertyValueAsString(void* InContainer, UStruct* InStruct, const FCachedPropertyPath& InPropertyPath, FString& OutValue, uint32 PPF_Flags = PPF_None);` (scope `PropertyPathHelpers`) — Get the value represented by this property path as a string @param	InContainer		A pointer to the container structure to resolve the property path against @param	InStruct		The struct type that InContainer points to @param	InPropertyPath	The property path @param	OutValue		The string to write the properties value to @return true if the property value was successfully copied
- L334 _prototype_ `bool SetPropertyValueFromString(UObject* InContainer, const FString& InPropertyPath, const FString& InValue, uint32 PPF_Flags = PPF_None);` (scope `PropertyPathHelpers`) — Set the value represented by this property path from a string @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path string @param	InValue			The string to read the properties value from @return true if the property value was successfully copied
- L343 _prototype_ `bool SetPropertyValueFromString(UObject* InContainer, const FCachedPropertyPath& InPropertyPath, const FString& InValue, uint32 PPF_Flags = PPF_None);` (scope `PropertyPathHelpers`) — Set the value represented by this property path from a string @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path @param	InValue			The string to read the properties value from @return true if the property value was successfully copied
- L353 _prototype_ `bool SetPropertyValueFromString(void* InContainer, UStruct* InStruct, const FString& InPropertyPath, const FString& InValue, uint32 PPF_Flags = PPF_None);` (scope `PropertyPathHelpers`) — Set the value represented by this property path from a string @param	InContainer		A pointer to the container structure to resolve the property path against @param	InStruct		The struct type that InContainer points to @param	InPropertyPath	The property path string @param	InValue			The string to read the properties value from @return true if the property value was successfully copied
- L363 _prototype_ `bool SetPropertyValueFromString(void* InContainer, UStruct* InStruct, const FCachedPropertyPath& InPropertyPath, const FString& InValue, uint32 PPF_Flags = PPF_None);` (scope `PropertyPathHelpers`) — Set the value represented by this property path from a string @param	InContainer		A pointer to the container structure to resolve the property path against @param	InStruct		The struct type that InContainer points to @param	InPropertyPath	The property path @param	InValue			The string to read the properties value from @return true if the property value was successfully copied
- L375 _function_ `template<typename T> bool GetPropertyValueFast(UObject* InContainer, const FCachedPropertyPath& InPropertyPath, T& OutValue)` (scope `PropertyPathHelpers`) — Get the value represented by this property path. forcing the use of cached addresses whether or not the path resolves over object or dynamic array boundaries. Using this function implies that the path is resolved and has not changed since last resolution. @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path @param	OutValue		The value to write to @return true if the property value was successfully copied
- L392 _function_ `template<typename T> bool GetPropertyValueFast(UObject* InContainer, const FCachedPropertyPath& InPropertyPath, T& OutValue, FProperty*& OutProperty)` (scope `PropertyPathHelpers`) — Get the value and the leaf property represented by this property path, forcing the use of cached addresses whether or not the path resolves over object or dynamic array boundaries. Using this function implies that the path is resolved and has not changed since last resolution. @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path @param	OutValue		The value to write to @param	OutProperty		The leaf property that the path resolved to @return true if the property value was successfully copied
- L414 _function_ `template<typename T> bool GetPropertyValue(UObject* InContainer, const FCachedPropertyPath& InPropertyPath, T& OutValue, FProperty*& OutProperty)` (scope `PropertyPathHelpers`) — Get the value and the leaf property represented by this property path. If the cached property path has a cached address it will use that as a 'fast path' instead of iterating the path. This has safety implications depending on the form of the path, so paths that are resolved over object boundaries or dynamic arrays will always use the slow path for safety. @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path @param	OutValue		The value to write to @param	OutProperty		The leaf property that the path resolved to @return true if the property value was successfully copied
- L441 _function_ `template<typename T> bool GetPropertyValue(UObject* InContainer, const FString& InPropertyPath, T& OutValue)` (scope `PropertyPathHelpers`) — Get the value represented by this property path. If the cached property path has a cached address it will use that as a 'fast path' instead of iterating the path. This has safety implications depending on the form of the path, so paths that are resolved over object boundaries or dynamic arrays will always use the slow path for safety. @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path string @param	OutValue		The value to write to @return true if the property value was successfully copied
- L461 _function_ `template<typename T> bool GetPropertyValue(UObject* InContainer, const FString& InPropertyPath, T& OutValue, FProperty*& OutProperty)` (scope `PropertyPathHelpers`) — Get the value and the leaf property represented by this property path. If the cached property path has a cached address it will use that as a 'fast path' instead of iterating the path. This has safety implications depending on the form of the path, so paths that are resolved over object boundaries or dynamic arrays will always use the slow path for safety. @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path string @param	OutValue		The value to write to @param	OutProperty		The leaf property that the path resolved to @return true if the property value was successfully copied
- L479 _function_ `template<typename T> bool GetPropertyValue(UObject* InContainer, const FCachedPropertyPath& InPropertyPath, T& OutValue)` (scope `PropertyPathHelpers`) — Get the value represented by this property path. If the cached property path has a cached address it will use that as a 'fast path' instead of iterating the path. This has safety implications depending on the form of the path, so paths that are resolved over object boundaries or dynamic arrays will always use the slow path for safety. @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path @param	OutValue		The value to write to @return true if the property value was successfully copied
- L494 _function_ `template<typename T> bool SetPropertyValueFast(UObject* InContainer, const FCachedPropertyPath& InPropertyPath, const T& InValue)` (scope `PropertyPathHelpers`) — Get the value represented by this property path. Fast, unsafe version. Using this function implies that the path is resolved and has not changed since last resolution. @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path @param	InValue			The value to write from @return true if the property value was successfully copied
- L515 _function_ `template<typename T> bool SetPropertyValue(UObject* InContainer, const FCachedPropertyPath& InPropertyPath, const T& InValue)` (scope `PropertyPathHelpers`) — Set the value and the leaf property represented by this property path If the cached property path has a cached address it will use that as a 'fast path' instead of iterating the path. This has safety implications depending on the form of the path, so paths that are resolved over object boundaries or dynamic arrays will always use the slow path for safety. @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path @param	InValue			The value to write from @return true if the property value was successfully copied
- L542 _function_ `template<typename T> bool SetPropertyValue(UObject* InContainer, const FString& InPropertyPath, const T& InValue)` (scope `PropertyPathHelpers`) — Set the value and the leaf property represented by this property path If the cached property path has a cached address it will use that as a 'fast path' instead of iterating the path. This has safety implications depending on the form of the path, so paths that are resolved over object boundaries or dynamic arrays will always use the slow path for safety. @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path string @param	InValue			The value to write from @return true if the property value was successfully copied
- L560 _prototype_ `bool SetPropertyValue(UObject* InContainer, const FCachedPropertyPath& InPropertyPath, const UScriptStruct* InScriptStruct, const uint8* InValue);` (scope `PropertyPathHelpers`) — Set the value and the leaf property represented by this property path If the cached property path has a cached address it will use that as a 'fast path' instead of iterating the path. This has safety implications depending on the form of the path, so paths that are resolved over object boundaries or dynamic arrays will always use the slow path for safety. @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path @param	InScriptStruct	The struct type to set @param	InValue			A pointer to the desired value for the given struct type @return true if the property value was successfully copied
- L574 _prototype_ `bool SetPropertyValue(UObject* InContainer, const FString& InPropertyPath, const UScriptStruct* InScriptStruct, const uint8* InValue);` (scope `PropertyPathHelpers`) — Set the value and the leaf property represented by this property path If the cached property path has a cached address it will use that as a 'fast path' instead of iterating the path. This has safety implications depending on the form of the path, so paths that are resolved over object boundaries or dynamic arrays will always use the slow path for safety. @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path string @param	InScriptStruct	The struct type to set @param	InValue			A pointer to the desired value for the given struct type @return true if the property value was successfully copied
- L583 _prototype_ `bool CopyPropertyValue(UObject* InContainer, const FCachedPropertyPath& InDestPropertyPath, const FCachedPropertyPath& InSrcPropertyPath);` (scope `PropertyPathHelpers`) — Copy values between two property paths in the same container. @param	InContainer			The container object to resolve the property path against @param	InDestPropertyPath	The property path to copy to @param	InSrcPropertyPath	The property path to copy from @return true if the copy was successful
- L595 _prototype_ `bool CopyPropertyValueFast(UObject* InContainer, const FCachedPropertyPath& InDestPropertyPath, const FCachedPropertyPath& InSrcPropertyPath);` (scope `PropertyPathHelpers`) — Copy values between two property paths in the same container. Fast, unsafe version. Using this requires that the two paths are pre-resolved from either a previous call to CopyPropertyValue (or GetPropertyValue/SetPropertyValue) or FCachedPropertyPath::Resolve(). @param	InContainer			The container object to resolve the property path against @param	InDestPropertyPath	The property path to copy to @param	InSrcPropertyPath	The property path to copy from @return true if the copy was successful
- L605 _prototype_ `void FindFieldNameAndArrayIndex(int32 InCount, const TCHAR* InString, int32& OutCount, const TCHAR** OutPropertyName, int32& OutArrayIndex);` (scope `PropertyPathHelpers`) — Parses a property path segment name of the form PropertyName[OptionalArrayIndex] @param	InCount			The length of the input string @param	InString        The Input string to parse @param	OutCount		The length of the resulting property name string @param   OutPropertyName The string storing the name of the property @param	OutArrayIndex	The resulting array index, if any
- L614 _prototype_ `bool PerformArrayOperation(UObject* InContainer, const FString& InPropertyPath, TFunctionRef<bool(FScriptArrayHelper&,int32)> InOperation);` (scope `PropertyPathHelpers`) — Perform the specified operation on the array referenced by the property path @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path string @param	InOperation		The operation to perform. The function will receive a script array helper and an index (if the path specified one). @return true if the operation was successful
- L623 _prototype_ `bool PerformArrayOperation(UObject* InContainer, const FCachedPropertyPath& InPropertyPath, TFunctionRef<bool(FScriptArrayHelper&,int32)> InOperation);` (scope `PropertyPathHelpers`) — Perform the specified operation on the array referenced by the property path @param	InContainer		The container object to resolve the property path against @param	InPropertyPath	The property path @param	InOperation		The operation to perform. The function will receive a script array helper and an index (if the path specified one). @return true if the operation was successful
- L627 _namespace_ `namespace PropertyPathHelpersInternal`
- L674 _prototype_ `FProperty* GetFirstParamProperty(UFunction* InFunction);` (scope `PropertyPathHelpersInternal`) — Find the first param that isnt a return property for the specified function
- L677 _prototype_ `void CallParentSetters(const FCachedPropertyPath& InPropertyPath);` (scope `PropertyPathHelpersInternal`) — Helper function used to call parent setters, used when modifying elements without setters in a struct that has one
- L684 _prototype_ `void CallParentGetters(void* OutValue, const FCachedPropertyPath& InPropertyPath, const void* InPropertyAddress);` (scope `PropertyPathHelpersInternal`) — Helper function used to call parent getters, used when modifying elements without getters in a struct that has one @return True if a parent getter was called.
- L839 _function_ `template<typename T, typename ContainerType> bool GetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, FProperty*& OutProperty, T& OutValue)` (scope `PropertyPathHelpersInternal`) — Resolve a property path to a property and a value. Supports functions as input fields. @param InContainer			The containing object/structure for the current path iteration @param InPropertyPath		The property path to get from @param OutProperty			The resolved property @param OutValue				The resolved value @return true if the address and property were resolved
- L1112 _function_ `template<typename T, typename ContainerType> bool SetValue(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, const T& InValue)` (scope `PropertyPathHelpersInternal`) — Resolve a property path to a property and a value. @param InContainer			The containing object/structure for the current path iteration @param InPropertyPath		The property path to set from @param InValue				The value to set @return true if the value was resolved @note This method is specialized internally to work with FPropertyStructView
- L1312 _function_ `template<typename T, typename ContainerType> bool GetValueFast(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, T& OutValue, FProperty*& OutProperty)` (scope `PropertyPathHelpersInternal`) — Fast, unsafe version of GetValue(). @param	InContainer		The containing object/structure to iterate against @param	InPropertyPath	The property path to use @param	OutValue		The value to write to @param	OutProperty		The leaf property that the path resolved to @return true if the value was written successfully
- L1348 _function_ `` (scope `PropertyPathHelpersInternal::FSetValueFastHelper::SetValue`)
- L1452 _function_ `template<typename T, typename ContainerType> bool SetValueFast(ContainerType* InContainer, const FCachedPropertyPath& InPropertyPath, const T& InValue)` (scope `PropertyPathHelpersInternal`) — Fast, unsafe version of SetValue(). @param	InContainer		The containing object/structure to iterate against @param	InPropertyPath	The property path to use @param	OutValue		The value to read from @return true if the value was read successfully

### `Source/Runtime/PropertyPath/Public/PropertyTypeCompatibility.h` (Public)


#### struct `FConcreteTypeCompatibleWithReflectedTypeHelper`  
`template<typename T> struct FConcreteTypeCompatibleWithReflectedTypeHelper`  
_L326-345_
- desc: Standard implementation
- L328 _public function_ `static bool IsConcreteTypeCompatibleWithReflectedType(FProperty* Property)`

#### struct `FConcreteTypeCompatibleWithReflectedTypeHelper`  
`template<typename T> struct FConcreteTypeCompatibleWithReflectedTypeHelper<TArray<T>>`  
_L349-360_
- desc: Dynamic array partial specialization
- L328 _public function_ `static bool IsConcreteTypeCompatibleWithReflectedType(FProperty* Property)`

#### struct `FConcreteTypeCompatibleWithReflectedTypeHelper`  
`template<typename T, int32 N> struct FConcreteTypeCompatibleWithReflectedTypeHelper<T[N]>`  
_L364-370_
- desc: Static array partial specialization
- L328 _public function_ `static bool IsConcreteTypeCompatibleWithReflectedType(FProperty* Property)`

#### struct `FConcreteTypeCompatibleWithReflectedTypeHelper`  
`template<typename T> struct FConcreteTypeCompatibleWithReflectedTypeHelper<TWeakObjectPtr<T>>`  
_L374-380_
- desc: Weak object partial specialization
- L328 _public function_ `static bool IsConcreteTypeCompatibleWithReflectedType(FProperty* Property)`

#### struct `FConcreteTypeCompatibleWithReflectedTypeHelper`  
`template<typename T> struct FConcreteTypeCompatibleWithReflectedTypeHelper<TLazyObjectPtr<T>>`  
_L384-390_
- desc: Weak object partial specialization
- L328 _public function_ `static bool IsConcreteTypeCompatibleWithReflectedType(FProperty* Property)`

#### struct `FPropertySizesMatchHelper`  
`template<typename T> struct FPropertySizesMatchHelper`  
_L465-471_
- L467 _public function_ `static bool PropertySizesMatch(FProperty* InProperty)`

#### struct `FPropertySizesMatchHelper`  
`template<typename T, int32 N> struct FPropertySizesMatchHelper<T[N]>`  
_L474-480_
- L467 _public function_ `static bool PropertySizesMatch(FProperty* InProperty)`

#### Free symbols / members of external scopes

- L17 _function_ `template<typename T> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl(FProperty* Property)` — Generic (struct) implementation
- L28 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<bool>(FProperty* Property)`
- L34 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<int8>(FProperty* Property)`
- L45 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<uint8>(FProperty* Property)`
- L60 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<int16>(FProperty* Property)`
- L71 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<uint16>(FProperty* Property)`
- L86 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<int32>(FProperty* Property)`
- L97 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<uint32>(FProperty* Property)`
- L112 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<int64>(FProperty* Property)`
- L123 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<uint64>(FProperty* Property)`
- L138 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<float>(FProperty* Property)`
- L144 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<double>(FProperty* Property)`
- L150 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FText>(FProperty* Property)`
- L156 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FString>(FProperty* Property)`
- L162 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FName>(FProperty* Property)`
- L168 _function_ `template<typename T> inline bool IsConcreteTypeCompatibleWithReflectedType_BuiltInStruct(FProperty* Property)`
- L181 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FColor>(FProperty* Property)`
- L187 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FLinearColor>(FProperty* Property)`
- L193 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FVector2D>(FProperty* Property)`
- L199 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FVector>(FProperty* Property)`
- L205 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FRotator>(FProperty* Property)`
- L211 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FQuat>(FProperty* Property)`
- L217 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FTransform>(FProperty* Property)`
- L223 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FBox2D>(FProperty* Property)`
- L229 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FGuid>(FProperty* Property)`
- L235 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FInterpCurvePointFloat>(FProperty* Property)`
- L241 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FInterpCurvePointVector>(FProperty* Property)`
- L247 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FInterpCurvePointVector2D>(FProperty* Property)`
- L253 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FInterpCurvePointQuat>(FProperty* Property)`
- L259 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FInterpCurvePointTwoVectors>(FProperty* Property)`
- L265 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FInterpCurvePointLinearColor>(FProperty* Property)`
- L271 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FFloatRangeBound>(FProperty* Property)`
- L277 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FFloatRange>(FProperty* Property)`
- L283 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FDoubleInterval>(FProperty* Property)`
- L289 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FInt32RangeBound>(FProperty* Property)`
- L295 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FInt32Range>(FProperty* Property)`
- L301 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FFloatInterval>(FProperty* Property)`
- L307 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FInt32Interval>(FProperty* Property)`
- L313 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FSoftObjectPath>(FProperty* Property)`
- L319 _function_ `template<> inline bool IsConcreteTypeCompatibleWithReflectedType_Impl<FSoftClassPath>(FProperty* Property)`
- L397 _function_ `template<typename T> static inline bool IsConcreteTypeCompatibleWithReflectedType(FProperty* Property)` — Check whether the concrete type T is compatible with the reflected type of a FProperty for the purposes of CopysingleValue()
- L410 _function_ `template<typename T> inline bool PropertySizesMatch_Impl(FProperty* InProperty)`
- L421 _function_ `template<> inline bool PropertySizesMatch_Impl<uint8>(FProperty* InProperty)`
- L432 _function_ `template<> inline bool PropertySizesMatch_Impl<uint16>(FProperty* InProperty)`
- L443 _function_ `template<> inline bool PropertySizesMatch_Impl<uint32>(FProperty* InProperty)`
- L454 _function_ `template<> inline bool PropertySizesMatch_Impl<uint64>(FProperty* InProperty)`
- L483 _function_ `template<typename T> inline bool PropertySizesMatch(FProperty* InProperty)`
