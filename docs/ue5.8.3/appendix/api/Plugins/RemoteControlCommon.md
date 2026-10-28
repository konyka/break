# Plugins / RemoteControlCommon

- module root: `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlCommon`
- headers: 10; symbols: 403
- symbol kinds: class=5, enum=6, enumerator=11, function=93, macro=3, member=55, namespace=9, prototype=44, struct=84, typedef=82, variable=11
- PrivateDependencyModuleNames: ApplicationCore, AssetRegistry, AssetTools, BlueprintGraph, Core, CoreUObject, DeveloperSettings, EditorSubsystem, EditorWidgets, Engine, InputCore, Projects, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: PropertyEditor

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlCommon/Private/RemoteControlCommonModule.h` (Private)


#### class `FRemoteControlCommonModule`  
`class FRemoteControlCommonModule : public IModuleInterface`  
_L9-12_
- inherits: `IModuleInterface`

#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRemoteControlCommon, Log, All);`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlCommon/Public/RCAllowedRemoteFunctionCall.h` (Public)


#### struct `FRCAllowedRemoteFunctionCall`  
`struct FRCAllowedRemoteFunctionCall`  
_L11-33_
- reflection: `USTRUCT()`
- desc: Describes a rule to allow a function (or all the functions) within a specified class to be called remotely
- L17 _public member_ `FSoftClassPath ClassPath;` — `UPROPERTY(EditAnywhere, Category="Remote Control")` — The path of the class to allow
- L25 _public member_ `TOptional<FString> FunctionName;` — `UPROPERTY(EditAnywhere, Category="Remote Control")` — If set, the name of the function to allow. If unset, any function in the class will be allowed. NOTE: This only accepts the reflected UFUNCTION name, not the script name. E.g. USceneComponent::K2_GetComponentToWorld's script name is 'GetWorldTransform', but "K2_GetComponentToWorld" needs to be specified instead.
- L32 _public member_ `bool bAllowChildClasses = false;` — `UPROPERTY(EditAnywhere, Category="Remote Control", meta=(DisplayAfter="ClassPath"))` — Determines whether child classes of ClassPath are allowed. NOTE: Prefer keeping this disabled when 'FunctionName' is not set to disallow arbitrary child classes from executing their functions because of this rule.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlCommon/Public/RCAllowedRemoteFunctionCallUtilities.h` (Public)


#### struct `UE::RemoteControl::FRCRemoteFunctionCallParams`  
`struct FRCRemoteFunctionCallParams`  
_L19-25_
- L22 _public member_ `const UClass* ObjectClass = nullptr;` — Required: Path to the object class containing the function prospect to call
- L24 _public member_ `FString FunctionName;` — Required: Name of the function prospect to call

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API REMOTECONTROLCOMMON_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace RemoteControl` (scope `UE`)
- L27 _prototype_ `FRCRemoteFunctionCallParams MakeRemoteFunctionCallParams(const UObject* InObject, const UFunction* InFunction);` (scope `UE::RemoteControl`) — Makes a remote function call with the given function and object.
- L35 _prototype_ `bool IsRemoteFunctionCallAllowed(const FRCRemoteFunctionCallParams& InParams, const FRCAllowedRemoteFunctionCall& InAllowedCall);` (scope `UE::RemoteControl`) — Checks whether the given parameters match the single allowed call. @param InParams the call parameters (object class and function) to test @param InAllowedCall the call to match @return true if the remote call from the parameters is allowed
- L43 _prototype_ `bool IsRemoteFunctionCallAllowed(const FRCRemoteFunctionCallParams& InParams, TConstArrayView<FRCAllowedRemoteFunctionCall> InAllowedCalls);` (scope `UE::RemoteControl`) — Returns true if the given remote call satisfy at least one of the given filters @param InParams the call parameters (object class and function) to test @param InAllowedCalls allowlist of calls @return true if the remote call from the parameters is allowed

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlCommon/Public/RCPropertyContainer.h` (Public)


#### class `URCPropertyContainerBase`  
`class URCPropertyContainerBase : public UObject`  
_L15-76_
- reflection: `UCLASS(Transient, Abstract)`
- inherits: `UObject`
- L21 _public prototype_ `void SetValue(const uint8* InData, const SIZE_T& InSize = 0);` — Sets the value from the incoming raw data. Provide size for array, string, etc.
- L26 _public function_ `SetValue(const ValueType& InValue)`
- L59 _public prototype_ `SIZE_T GetValue(uint8* OutData);` — Writes to the provided raw data pointer. Returns size for array, string, etc.
- L62 _public prototype_ `SIZE_T GetValue(TArray<uint8>& OutData);` — Writes to the provided data array. Returns size for array, string, etc.
- L66 _public function_ `template <typename ValueType> ValueType* GetValue()` — Returns the Value as ValueType. Not necessarily valid if using incorrect ValueType.
- L72 _public prototype_ `virtual FProperty* GetValueProperty();` — Returns the Property for Value
- L75 _private member_ `TWeakFieldPtr<FProperty> ValueProperty;`

#### struct `FRCPropertyContainerKey`  
`struct FRCPropertyContainerKey`  
_L80-88_
- reflection: `USTRUCT()`
- desc: Minimal information needed to lookup a unique property container class
- L85 _public member_ `FName ValueTypeName;` — `UPROPERTY()`
- L87 _public prototype_ `FName ToClassName() const;`

#### class `URCPropertyContainerRegistry`  
`class URCPropertyContainerRegistry : public UEngineSubsystem`  
_L96-110_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: A subsystem to provide and cache dynamically created PropertyContainer classes.
- L102 _public prototype_ `URCPropertyContainerBase* CreateContainer(UObject* InOwner, const FName& InValueTypeName, const FProperty* InValueSrcProperty);` — Creates a (UObject) container, with a single Value property of the given type.
- L106 _private member_ `TMap<FRCPropertyContainerKey, TSubclassOf<URCPropertyContainerBase>> CachedContainerClasses;` — `UPROPERTY(Transient)`
- L109 _private prototype_ `TSubclassOf<URCPropertyContainerBase>& FindOrAddContainerClass(const FName& InValueTypeName, const FProperty* InValueSrcProperty);` — Finds (cached) or creates a new container for the given property.

#### Free symbols / members of external scopes

- L28 _typedef_ `using DecayedValueType = typename TDecay<TRemovePointer<ValueType>>::Type;` (scope `URCPropertyContainerBase::SetValue`)
- L90 _function_ `inline uint64 GetTypeHash(const FRCPropertyContainerKey& InValue)`
- L91 _function_ `inline bool operator==(const FRCPropertyContainerKey& Lhs, const FRCPropertyContainerKey& Rhs)`
- L92 _function_ `inline bool operator!=(const FRCPropertyContainerKey& Lhs, const FRCPropertyContainerKey& Rhs)`
- L112 _namespace_ `namespace PropertyContainers`
- L114 _prototype_ `URCPropertyContainerBase* CreateContainerForProperty(UObject* InOwner, const FProperty* InSrcProperty);` (scope `PropertyContainers`)
- L118 _prototype_ `FProperty* CreateProperty(const FFieldVariant& InParent, const FFieldVariant& InChild, const FName& InPropertyName = NAME_None, EObjectFlags InObjectFlags = EObjectFlags::RF_Public);` (scope `PropertyContainers`) — @note: use with caution, currently only used for testing

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlCommon/Public/RCPropertyUtilities.h` (Public)


#### class `RemoteControlPropertyUtilities::FRCPropertyVariant`  
`class FRCPropertyVariant`  
_L21-111_
- desc: Container that can hold either a PropertyHandle, or Property/Data pair. Similar to FFieldVariant
- L24 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle = nullptr;`
- L26 _private member_ `TWeakFieldPtr<const FProperty> Property = nullptr;`
- L27 _private member_ `void* PropertyData = nullptr;`
- L28 _private member_ `TArray<uint8>* PropertyContainer = nullptr;`
- L30 _private member_ `bool bHasHandle = false;`
- L31 _private member_ `int32 NumElements = 1;`
- L34 _public prototype_ `explicit FRCPropertyVariant() = default;`
- L38 _public prototype_ `FRCPropertyVariant(const TSharedPtr<IPropertyHandle>& InPropertyHandle);` — Construct from an IPropertyHandle.
- L42 _public prototype_ `FRCPropertyVariant(const FProperty* InProperty, const void* InPropertyData, const int32& InNumElements = 1);` — Construct from a Property, PropertyData ptr, and the expected element count (needed for arrays, strings, etc.).
- L45 _public prototype_ `FRCPropertyVariant(const FProperty* InProperty, TArray<uint8>& InPropertyData, const int32& InNumElements = -1);` — Construct from a Property and backing data array. Preferred over a raw ptr.
- L47 _public prototype_ `virtual ~FRCPropertyVariant() = default;`
- L50 _public prototype_ `FProperty* GetProperty() const;` — Gets the property.
- L54 _public function_ `template <typename PropertyType> PropertyType* GetProperty() const` — Gets the typed property, returns nullptr if not cast.
- L62 _public prototype_ `TArray<uint8>* GetPropertyContainer() const;` — Gets the property container (byte array), if available.
- L65 _public prototype_ `void* GetPropertyData(const FProperty* InContainer = nullptr, int32 InIdx = 0) const;` — Gets the data pointer
- L69 _public function_ `template <typename ValueType> ValueType* GetPropertyValue(const FProperty* InContainer = nullptr, int32 InIdx = 0) const` — Returns the data as the ValueType.
- L75 _public function_ `bool IsHandle() const` — Is this backed by an IPropertyHandle?
- L81 _public prototype_ `void Init(int32 InSize = -1);` — Initialize/allocate if necessary.
- L84 _public function_ `int32 Num() const` — Gets the number of elements, more than 1 if an array.
- L90 _public function_ `int32 Size() const` — Gets the size of the underlying data.
- L96 _public prototype_ `int32 GetElementSize() const;` — Gets individual element size (for arrays, etc.).
- L99 _public prototype_ `void InferNum(const FRCPropertyVariant* InOtherProperty = nullptr);` — Calculate number of elements based on available info. If OtherProperty is specified, that's used instead.
- L102 _public function_ `bool operator==(const FRCPropertyVariant& InOther) const` — Comparison is by property, not by property instance value.
- L107 _public function_ `bool operator!=(const FRCPropertyVariant& InOther) const`
- L114 _prototype_ `template <> FString* FRCPropertyVariant::GetPropertyValue<FString>(const FProperty* InContainer, int32 InIdx) const;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace RemoteControlPropertyUtilities`
- L16 _variable_ `static TMap<TWeakFieldPtr<const FProperty>, TWeakObjectPtr<UFunction>> CachedSetterFunctions;` (scope `RemoteControlPropertyUtilities`)
- L17 _variable_ `static const FName NAME_BlueprintGetter(TEXT("Blue` (scope `RemoteControlPropertyUtilities`)
- L18 _variable_ `static const FName NAME_BlueprintSetter(TEXT("Blue` (scope `RemoteControlPropertyUtilities`)
- L125 _prototype_ `Deserialize(const FRCPropertyVariant& InSrc, FRCPropertyVariant& OutDst);` (scope `RemoteControlPropertyUtilities`)
- L136 _prototype_ `Serialize(const FRCPropertyVariant& InSrc, FRCPropertyVariant& OutDst);` (scope `RemoteControlPropertyUtilities`)
- L140 _prototype_ `template <> bool Deserialize<FBoolProperty>(const FRCPropertyVariant& InSrc, FRCPropertyVariant& OutDst);` (scope `RemoteControlPropertyUtilities`) — Specialization for FBoolProperty.
- L144 _prototype_ `template <> bool Deserialize<FStructProperty>(const FRCPropertyVariant& InSrc, FRCPropertyVariant& OutDst);` (scope `RemoteControlPropertyUtilities`) — Specialization for FStructProperty.
- L160 _prototype_ `static FProperty* FindSetterArgument(UFunction* SetterFunction, const FProperty* PropertyToModify);` (scope `RemoteControlPropertyUtilities`)
- L163 _prototype_ `static FName FindLightSetterFunctionInternal(const FProperty* Property, UClass* OwnerClass);` (scope `RemoteControlPropertyUtilities`) — LightComponent derived components use a lot of property setters, without specifying BlueprintSetter, so handle here.
- L165 _prototype_ `static UFunction* FindSetterFunctionInternal(const FProperty* Property, UClass* OwnerClass);` (scope `RemoteControlPropertyUtilities`)
- L167 _prototype_ `static UFunction* FindSetterFunction(const FProperty* Property, UClass* OwnerClass = nullptr);` (scope `RemoteControlPropertyUtilities`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlCommon/Public/RCPropertyUtilities.inl` (Public)


#### Free symbols / members of external scopes

- L18 _namespace_ `namespace RemoteControlPropertyUtilities`
- L22 _function_ `inline FRCPropertyVariant::FRCPropertyVariant(const TSharedPtr<IPropertyHandle>& InPropertyHandle) : bHasHandle(true)` (scope `RemoteControlPropertyUtilities::FRCPropertyVariant`) — Construct from an IPropertyHandle.
- L31 _function_ `inline FRCPropertyVariant::FRCPropertyVariant(const FProperty* InProperty, const void* InPropertyData, const int32& InNumElements) : NumElements(InNumElements)` (scope `RemoteControlPropertyUtilities::FRCPropertyVariant`) — Construct from a Property, PropertyData ptr, and the expected element count (needed for arrays, strings, etc.).
- L39 _function_ `inline FRCPropertyVariant::FRCPropertyVariant(const FProperty* InProperty, TArray<uint8>& InPropertyData, const int32& InNumElements)` (scope `RemoteControlPropertyUtilities::FRCPropertyVariant`) — Construct from a Property and backing data array. Preferred over a raw ptr.
- L49 _function_ `inline FProperty* FRCPropertyVariant::GetProperty() const` (scope `RemoteControlPropertyUtilities::FRCPropertyVariant`) — Gets the property.
- L68 _function_ `inline TArray<uint8>* FRCPropertyVariant::GetPropertyContainer() const` (scope `RemoteControlPropertyUtilities::FRCPropertyVariant`) — Gets the property container (byte array), if available.
- L79 _function_ `inline void* FRCPropertyVariant::GetPropertyData(const FProperty* InContainer, int32 InIdx) const` (scope `RemoteControlPropertyUtilities::FRCPropertyVariant`) — Gets the data pointer
- L103 _function_ `inline void FRCPropertyVariant::Init(int32 InSize)` (scope `RemoteControlPropertyUtilities::FRCPropertyVariant`) — Initialize/allocate if necessary.
- L122 _function_ `inline int32 FRCPropertyVariant::GetElementSize() const` (scope `RemoteControlPropertyUtilities::FRCPropertyVariant`) — Gets individual element size (for arrays, etc.).
- L142 _function_ `inline void FRCPropertyVariant::InferNum(const FRCPropertyVariant* InOtherProperty)` (scope `RemoteControlPropertyUtilities::FRCPropertyVariant`) — Calculate number of elements based on available info. If OtherProperty is specified, that's used instead.
- L202 _function_ `template <> inline FString* FRCPropertyVariant::GetPropertyValue<FString>(const FProperty* InContainer, int32 InIdx) const` (scope `RemoteControlPropertyUtilities::FRCPropertyVariant`)
- L216 _function_ `Deserialize(const FRCPropertyVariant& InSrc, FRCPropertyVariant& OutDst)` (scope `RemoteControlPropertyUtilities`)
- L218 _typedef_ `using ValueType = typename TRemoteControlPropertyTypeTraits<PropertyType>::ValueType;` (scope `RemoteControlPropertyUtilities::Deserialize`)
- L284 _function_ `Serialize(const FRCPropertyVariant& InSrc, FRCPropertyVariant& OutDst)` (scope `RemoteControlPropertyUtilities`)
- L286 _typedef_ `using ValueType = typename TRemoteControlPropertyTypeTraits<PropertyType>::ValueType;` (scope `RemoteControlPropertyUtilities::Serialize`)
- L307 _function_ `template <> inline bool Deserialize<FBoolProperty>(const FRCPropertyVariant& InSrc, FRCPropertyVariant& OutDst)` (scope `RemoteControlPropertyUtilities`) — Specialization for FBoolProperty.
- L309 _typedef_ `using ValueType = TRemoteControlPropertyTypeTraits<FBoolProperty>::ValueType;` (scope `RemoteControlPropertyUtilities::Deserialize`)
- L325 _function_ `template <> inline bool Deserialize<FStructProperty>(const FRCPropertyVariant& InSrc, FRCPropertyVariant& OutDst)` (scope `RemoteControlPropertyUtilities`) — Specialization for FStructProperty.
- L366 _function_ `static FProperty* FindSetterArgument(UFunction* SetterFunction, const FProperty* PropertyToModify)` (scope `RemoteControlPropertyUtilities`)
- L393 _function_ `static FName FindLightSetterFunctionInternal(const FProperty* Property, UClass* OwnerClass)` (scope `RemoteControlPropertyUtilities`) — LightComponent derived components use a lot of property setters, without specifying BlueprintSetter, so handle here.
- L467 _function_ `static UFunction* FindSetterFunctionInternal(const FProperty* Property, UClass* OwnerClass)` (scope `RemoteControlPropertyUtilities`)
- L553 _function_ `static UFunction* FindSetterFunction(const FProperty* Property, UClass* OwnerClass)` (scope `RemoteControlPropertyUtilities`)
- L577 _function_ `template <> inline bool Deserialize<FProperty>(const FRCPropertyVariant& InSrc, FRCPropertyVariant& OutDst)` (scope `RemoteControlPropertyUtilities`)
- L587 _function_ `template <> inline bool Serialize<FProperty>(const FRCPropertyVariant& InSrc, FRCPropertyVariant& OutDst)` (scope `RemoteControlPropertyUtilities`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlCommon/Public/RCTypeTraits.h` (Public)


#### struct `RemoteControlTypeTraits::Concepts::CNumerical`  
`struct CNumerical`  
_L19-25_
- desc: Concept to check if T has NumericLimits
- L22 _public prototype_ `template <typename T> auto Requires() -> decltype( std::is_same_v<typename TNumericLimits<T>::NumericType, T> && !std::is_same_v<T, bool>);`

#### struct `RemoteControlTypeTraits::Concepts::CPropertyValuePair`  
`struct CPropertyValuePair`  
_L28-32_
- desc: Concept to check if PropertyType::TCppType matches ValueType
- L31 _public prototype_ `template <typename PropertyType, typename ValueType> auto Requires() -> decltype(TIsDerivedFrom<PropertyType, TProperty<ValueType, PropertyType>>::Value);`

#### struct `RemoteControlTypeTraits::Concepts::CPropertyHasTCppType`  
`struct CPropertyHasTCppType`  
_L35-39_
- desc: Concept to check if PropertyType has a TCppType
- L38 _public prototype_ `template <typename PropertyType> auto Requires() -> decltype(std::is_same_v<typename PropertyType::TCppType, void>);`

#### struct `RemoteControlTypeTraits::TIsStringLikeProperty`  
`template <typename PropertyType, typename Enable = void> struct TIsStringLikeProperty`  
_L44-47_
- desc: Catch-all for string-like property types

#### enum `RemoteControlTypeTraits::TIsStringLikeProperty::(anonymous)`  
`enum`  
_L46-46_

#### struct `RemoteControlTypeTraits::TIsStringLikeProperty`  
`template <typename PropertyType> struct TIsStringLikeProperty< PropertyType, typename TEnableIf< std::is_same_v<PropertyType, FStrProperty> || std::is_same_v<PropertyType, FNameProperty> || std::is_same_v<PropertyType, FTextProperty>>::Type>`  
_L50-61_

#### enum `RemoteControlTypeTraits::TIsStringLikeProperty::(anonymous)`  
``  
_L58-60_

#### struct `RemoteControlTypeTraits::TIsStringLikeValue`  
`template <typename ValueType, typename Enable = void> struct TIsStringLikeValue`  
_L65-68_
- desc: Catch-all for string-like value types

#### enum `RemoteControlTypeTraits::TIsStringLikeValue::(anonymous)`  
`enum`  
_L67-67_

#### struct `RemoteControlTypeTraits::TIsStringLikeValue`  
`template <typename ValueType> struct TIsStringLikeValue< ValueType, typename TEnableIf< std::is_same_v<ValueType, FString> || std::is_same_v<ValueType, FName> || std::is_same_v<ValueType, FText>>::Type>`  
_L71-82_

#### enum `RemoteControlTypeTraits::TIsStringLikeValue::(anonymous)`  
``  
_L79-81_

#### struct `TRemoteControlTypeTraits`  
`template <typename ValueType> struct TRemoteControlTypeTraits<ValueType, typename TEnableIf< std::is_arithmetic_v<ValueType> && !std::is_floating_point_v<ValueType> && TModels_V<RemoteControlTypeTraits::Concepts::CNumerical, ValueType>, void>::Type>`  
_L101-126_
- desc: RemoteControlTypeTraits for integers
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlTypeTraits`  
`template <typename ValueType> struct TRemoteControlTypeTraits<ValueType, typename TEnableIf<TIsFloatingPoint<ValueType>::Value, void>::Type>`  
_L130-148_
- desc: RemoteControlTypeTraits for floats
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlPropertyTypeTraits`  
`template <> struct TRemoteControlPropertyTypeTraits<FNumericProperty>`  
_L155-165_
- desc: RemoteControlPropertyTypeTraits for FNumericProperty Currently all numeric types are supported so we can shortcut the above (rather than doing a series of CastField's)
- L157 _public typedef_ `using PropertyType = FNumericProperty;`
- L158 _public typedef_ `using ValueType = void;`
- L161 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L164 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L172 _public typedef_ `using PropertyType = InPropertyType;`
- L173 _public typedef_ `using ValueType = typename InPropertyType::TCppType;`
- L186 _public typedef_ `using PropertyType = FEnumProperty;`
- L187 _public typedef_ `using ValueType = uint8;`
- L223 _public typedef_ `using PropertyType = FBoolProperty;`
- L224 _public typedef_ `using ValueType = bool;`
- L233 _public function_ `static constexpr ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L236 _public function_ `static constexpr ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L239 _public function_ `static constexpr ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L242 _public function_ `static constexpr ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L272 _public typedef_ `using PropertyType = FStrProperty;`
- L273 _public typedef_ `using ValueType = FString;`
- L282 _public function_ `static ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L285 _public function_ `static ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L288 _public function_ `static ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L291 _public function_ `static ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L319 _public typedef_ `using PropertyType = FNameProperty;`
- L320 _public typedef_ `using ValueType = FName;`
- L366 _public typedef_ `using PropertyType = FTextProperty;`
- L367 _public typedef_ `using ValueType = FText;`
- L394 _public typedef_ `using PropertyType = FArrayProperty;`
- L395 _public typedef_ `using ValueType = TArray<uint8>;`
- L408 _public typedef_ `using PropertyType = FSetProperty;`
- L422 _public typedef_ `using PropertyType = FMapProperty;`
- L438 _public typedef_ `using PropertyType = FStructProperty;`

#### struct `TRemoteControlPropertyTypeTraits`  
`template <typename InPropertyType> struct TRemoteControlPropertyTypeTraits<InPropertyType, typename TEnableIf<TModels_V<RemoteControlTypeTraits::Concepts::CPropertyHasTCppType, InPropertyType>, void>::Type>`  
_L169-180_
- desc: RemoteControlPropertyTypeTraits for any property with a TCppType
- L157 _public typedef_ `using PropertyType = FNumericProperty;`
- L158 _public typedef_ `using ValueType = void;`
- L161 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L164 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L172 _public typedef_ `using PropertyType = InPropertyType;`
- L173 _public typedef_ `using ValueType = typename InPropertyType::TCppType;`
- L186 _public typedef_ `using PropertyType = FEnumProperty;`
- L187 _public typedef_ `using ValueType = uint8;`
- L223 _public typedef_ `using PropertyType = FBoolProperty;`
- L224 _public typedef_ `using ValueType = bool;`
- L233 _public function_ `static constexpr ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L236 _public function_ `static constexpr ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L239 _public function_ `static constexpr ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L242 _public function_ `static constexpr ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L272 _public typedef_ `using PropertyType = FStrProperty;`
- L273 _public typedef_ `using ValueType = FString;`
- L282 _public function_ `static ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L285 _public function_ `static ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L288 _public function_ `static ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L291 _public function_ `static ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L319 _public typedef_ `using PropertyType = FNameProperty;`
- L320 _public typedef_ `using ValueType = FName;`
- L366 _public typedef_ `using PropertyType = FTextProperty;`
- L367 _public typedef_ `using ValueType = FText;`
- L394 _public typedef_ `using PropertyType = FArrayProperty;`
- L395 _public typedef_ `using ValueType = TArray<uint8>;`
- L408 _public typedef_ `using PropertyType = FSetProperty;`
- L422 _public typedef_ `using PropertyType = FMapProperty;`
- L438 _public typedef_ `using PropertyType = FStructProperty;`

#### struct `TRemoteControlPropertyTypeTraits`  
`template <> struct TRemoteControlPropertyTypeTraits<FEnumProperty>`  
_L184-194_
- desc: RemoteControlPropertyTypeTraits for FEnumProperty
- L157 _public typedef_ `using PropertyType = FNumericProperty;`
- L158 _public typedef_ `using ValueType = void;`
- L161 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L164 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L172 _public typedef_ `using PropertyType = InPropertyType;`
- L173 _public typedef_ `using ValueType = typename InPropertyType::TCppType;`
- L186 _public typedef_ `using PropertyType = FEnumProperty;`
- L187 _public typedef_ `using ValueType = uint8;`
- L223 _public typedef_ `using PropertyType = FBoolProperty;`
- L224 _public typedef_ `using ValueType = bool;`
- L233 _public function_ `static constexpr ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L236 _public function_ `static constexpr ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L239 _public function_ `static constexpr ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L242 _public function_ `static constexpr ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L272 _public typedef_ `using PropertyType = FStrProperty;`
- L273 _public typedef_ `using ValueType = FString;`
- L282 _public function_ `static ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L285 _public function_ `static ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L288 _public function_ `static ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L291 _public function_ `static ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L319 _public typedef_ `using PropertyType = FNameProperty;`
- L320 _public typedef_ `using ValueType = FName;`
- L366 _public typedef_ `using PropertyType = FTextProperty;`
- L367 _public typedef_ `using ValueType = FText;`
- L394 _public typedef_ `using PropertyType = FArrayProperty;`
- L395 _public typedef_ `using ValueType = TArray<uint8>;`
- L408 _public typedef_ `using PropertyType = FSetProperty;`
- L422 _public typedef_ `using PropertyType = FMapProperty;`
- L438 _public typedef_ `using PropertyType = FStructProperty;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<bool>`  
_L200-217_
- desc: RemoteControlTypeTraits for bool
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlPropertyTypeTraits`  
`template <> struct TRemoteControlPropertyTypeTraits<FBoolProperty>`  
_L221-243_
- desc: RemoteControlPropertyTypeTraits for FBoolProperty
- L157 _public typedef_ `using PropertyType = FNumericProperty;`
- L158 _public typedef_ `using ValueType = void;`
- L161 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L164 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L172 _public typedef_ `using PropertyType = InPropertyType;`
- L173 _public typedef_ `using ValueType = typename InPropertyType::TCppType;`
- L186 _public typedef_ `using PropertyType = FEnumProperty;`
- L187 _public typedef_ `using ValueType = uint8;`
- L223 _public typedef_ `using PropertyType = FBoolProperty;`
- L224 _public typedef_ `using ValueType = bool;`
- L233 _public function_ `static constexpr ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L236 _public function_ `static constexpr ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L239 _public function_ `static constexpr ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L242 _public function_ `static constexpr ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L272 _public typedef_ `using PropertyType = FStrProperty;`
- L273 _public typedef_ `using ValueType = FString;`
- L282 _public function_ `static ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L285 _public function_ `static ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L288 _public function_ `static ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L291 _public function_ `static ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L319 _public typedef_ `using PropertyType = FNameProperty;`
- L320 _public typedef_ `using ValueType = FName;`
- L366 _public typedef_ `using PropertyType = FTextProperty;`
- L367 _public typedef_ `using ValueType = FText;`
- L394 _public typedef_ `using PropertyType = FArrayProperty;`
- L395 _public typedef_ `using ValueType = TArray<uint8>;`
- L408 _public typedef_ `using PropertyType = FSetProperty;`
- L422 _public typedef_ `using PropertyType = FMapProperty;`
- L438 _public typedef_ `using PropertyType = FStructProperty;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FString>`  
_L249-266_
- desc: RemoteControlTypeTraits for FString
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlPropertyTypeTraits`  
`template <> struct TRemoteControlPropertyTypeTraits<FStrProperty>`  
_L270-292_
- desc: RemoteControlPropertyTypeTraits for FStrProperty
- L157 _public typedef_ `using PropertyType = FNumericProperty;`
- L158 _public typedef_ `using ValueType = void;`
- L161 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L164 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L172 _public typedef_ `using PropertyType = InPropertyType;`
- L173 _public typedef_ `using ValueType = typename InPropertyType::TCppType;`
- L186 _public typedef_ `using PropertyType = FEnumProperty;`
- L187 _public typedef_ `using ValueType = uint8;`
- L223 _public typedef_ `using PropertyType = FBoolProperty;`
- L224 _public typedef_ `using ValueType = bool;`
- L233 _public function_ `static constexpr ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L236 _public function_ `static constexpr ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L239 _public function_ `static constexpr ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L242 _public function_ `static constexpr ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L272 _public typedef_ `using PropertyType = FStrProperty;`
- L273 _public typedef_ `using ValueType = FString;`
- L282 _public function_ `static ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L285 _public function_ `static ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L288 _public function_ `static ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L291 _public function_ `static ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L319 _public typedef_ `using PropertyType = FNameProperty;`
- L320 _public typedef_ `using ValueType = FName;`
- L366 _public typedef_ `using PropertyType = FTextProperty;`
- L367 _public typedef_ `using ValueType = FText;`
- L394 _public typedef_ `using PropertyType = FArrayProperty;`
- L395 _public typedef_ `using ValueType = TArray<uint8>;`
- L408 _public typedef_ `using PropertyType = FSetProperty;`
- L422 _public typedef_ `using PropertyType = FMapProperty;`
- L438 _public typedef_ `using PropertyType = FStructProperty;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FName>`  
_L296-313_
- desc: RemoteControlTypeTraits for FName
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlPropertyTypeTraits`  
`template <> struct TRemoteControlPropertyTypeTraits<FNameProperty>`  
_L317-339_
- desc: RemoteControlPropertyTypeTraits for FNameProperty
- L157 _public typedef_ `using PropertyType = FNumericProperty;`
- L158 _public typedef_ `using ValueType = void;`
- L161 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L164 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L172 _public typedef_ `using PropertyType = InPropertyType;`
- L173 _public typedef_ `using ValueType = typename InPropertyType::TCppType;`
- L186 _public typedef_ `using PropertyType = FEnumProperty;`
- L187 _public typedef_ `using ValueType = uint8;`
- L223 _public typedef_ `using PropertyType = FBoolProperty;`
- L224 _public typedef_ `using ValueType = bool;`
- L233 _public function_ `static constexpr ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L236 _public function_ `static constexpr ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L239 _public function_ `static constexpr ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L242 _public function_ `static constexpr ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L272 _public typedef_ `using PropertyType = FStrProperty;`
- L273 _public typedef_ `using ValueType = FString;`
- L282 _public function_ `static ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L285 _public function_ `static ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L288 _public function_ `static ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L291 _public function_ `static ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L319 _public typedef_ `using PropertyType = FNameProperty;`
- L320 _public typedef_ `using ValueType = FName;`
- L366 _public typedef_ `using PropertyType = FTextProperty;`
- L367 _public typedef_ `using ValueType = FText;`
- L394 _public typedef_ `using PropertyType = FArrayProperty;`
- L395 _public typedef_ `using ValueType = TArray<uint8>;`
- L408 _public typedef_ `using PropertyType = FSetProperty;`
- L422 _public typedef_ `using PropertyType = FMapProperty;`
- L438 _public typedef_ `using PropertyType = FStructProperty;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FText>`  
_L343-360_
- desc: RemoteControlTypeTraits for FText
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlPropertyTypeTraits`  
`template <> struct TRemoteControlPropertyTypeTraits<FTextProperty>`  
_L364-386_
- desc: RemoteControlPropertyTypeTraits for FTextProperty
- L157 _public typedef_ `using PropertyType = FNumericProperty;`
- L158 _public typedef_ `using ValueType = void;`
- L161 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L164 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L172 _public typedef_ `using PropertyType = InPropertyType;`
- L173 _public typedef_ `using ValueType = typename InPropertyType::TCppType;`
- L186 _public typedef_ `using PropertyType = FEnumProperty;`
- L187 _public typedef_ `using ValueType = uint8;`
- L223 _public typedef_ `using PropertyType = FBoolProperty;`
- L224 _public typedef_ `using ValueType = bool;`
- L233 _public function_ `static constexpr ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L236 _public function_ `static constexpr ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L239 _public function_ `static constexpr ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L242 _public function_ `static constexpr ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L272 _public typedef_ `using PropertyType = FStrProperty;`
- L273 _public typedef_ `using ValueType = FString;`
- L282 _public function_ `static ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L285 _public function_ `static ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L288 _public function_ `static ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L291 _public function_ `static ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L319 _public typedef_ `using PropertyType = FNameProperty;`
- L320 _public typedef_ `using ValueType = FName;`
- L366 _public typedef_ `using PropertyType = FTextProperty;`
- L367 _public typedef_ `using ValueType = FText;`
- L394 _public typedef_ `using PropertyType = FArrayProperty;`
- L395 _public typedef_ `using ValueType = TArray<uint8>;`
- L408 _public typedef_ `using PropertyType = FSetProperty;`
- L422 _public typedef_ `using PropertyType = FMapProperty;`
- L438 _public typedef_ `using PropertyType = FStructProperty;`

#### struct `TRemoteControlPropertyTypeTraits`  
`template <> struct TRemoteControlPropertyTypeTraits<FArrayProperty>`  
_L392-402_
- desc: RemoteControlPropertyTypeTraits for FArrayProperty
- L157 _public typedef_ `using PropertyType = FNumericProperty;`
- L158 _public typedef_ `using ValueType = void;`
- L161 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L164 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L172 _public typedef_ `using PropertyType = InPropertyType;`
- L173 _public typedef_ `using ValueType = typename InPropertyType::TCppType;`
- L186 _public typedef_ `using PropertyType = FEnumProperty;`
- L187 _public typedef_ `using ValueType = uint8;`
- L223 _public typedef_ `using PropertyType = FBoolProperty;`
- L224 _public typedef_ `using ValueType = bool;`
- L233 _public function_ `static constexpr ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L236 _public function_ `static constexpr ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L239 _public function_ `static constexpr ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L242 _public function_ `static constexpr ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L272 _public typedef_ `using PropertyType = FStrProperty;`
- L273 _public typedef_ `using ValueType = FString;`
- L282 _public function_ `static ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L285 _public function_ `static ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L288 _public function_ `static ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L291 _public function_ `static ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L319 _public typedef_ `using PropertyType = FNameProperty;`
- L320 _public typedef_ `using ValueType = FName;`
- L366 _public typedef_ `using PropertyType = FTextProperty;`
- L367 _public typedef_ `using ValueType = FText;`
- L394 _public typedef_ `using PropertyType = FArrayProperty;`
- L395 _public typedef_ `using ValueType = TArray<uint8>;`
- L408 _public typedef_ `using PropertyType = FSetProperty;`
- L422 _public typedef_ `using PropertyType = FMapProperty;`
- L438 _public typedef_ `using PropertyType = FStructProperty;`

#### struct `TRemoteControlPropertyTypeTraits`  
`template <> struct TRemoteControlPropertyTypeTraits<FSetProperty>`  
_L406-416_
- desc: RemoteControlPropertyTypeTraits for FSetProperty
- L157 _public typedef_ `using PropertyType = FNumericProperty;`
- L158 _public typedef_ `using ValueType = void;`
- L161 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L164 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L172 _public typedef_ `using PropertyType = InPropertyType;`
- L173 _public typedef_ `using ValueType = typename InPropertyType::TCppType;`
- L186 _public typedef_ `using PropertyType = FEnumProperty;`
- L187 _public typedef_ `using ValueType = uint8;`
- L223 _public typedef_ `using PropertyType = FBoolProperty;`
- L224 _public typedef_ `using ValueType = bool;`
- L233 _public function_ `static constexpr ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L236 _public function_ `static constexpr ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L239 _public function_ `static constexpr ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L242 _public function_ `static constexpr ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L272 _public typedef_ `using PropertyType = FStrProperty;`
- L273 _public typedef_ `using ValueType = FString;`
- L282 _public function_ `static ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L285 _public function_ `static ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L288 _public function_ `static ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L291 _public function_ `static ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L319 _public typedef_ `using PropertyType = FNameProperty;`
- L320 _public typedef_ `using ValueType = FName;`
- L366 _public typedef_ `using PropertyType = FTextProperty;`
- L367 _public typedef_ `using ValueType = FText;`
- L394 _public typedef_ `using PropertyType = FArrayProperty;`
- L395 _public typedef_ `using ValueType = TArray<uint8>;`
- L408 _public typedef_ `using PropertyType = FSetProperty;`
- L422 _public typedef_ `using PropertyType = FMapProperty;`
- L438 _public typedef_ `using PropertyType = FStructProperty;`

#### struct `TRemoteControlPropertyTypeTraits`  
`template <> struct TRemoteControlPropertyTypeTraits<FMapProperty>`  
_L420-430_
- desc: RemoteControlPropertyTypeTraits for FMapProperty
- L157 _public typedef_ `using PropertyType = FNumericProperty;`
- L158 _public typedef_ `using ValueType = void;`
- L161 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L164 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L172 _public typedef_ `using PropertyType = InPropertyType;`
- L173 _public typedef_ `using ValueType = typename InPropertyType::TCppType;`
- L186 _public typedef_ `using PropertyType = FEnumProperty;`
- L187 _public typedef_ `using ValueType = uint8;`
- L223 _public typedef_ `using PropertyType = FBoolProperty;`
- L224 _public typedef_ `using ValueType = bool;`
- L233 _public function_ `static constexpr ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L236 _public function_ `static constexpr ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L239 _public function_ `static constexpr ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L242 _public function_ `static constexpr ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L272 _public typedef_ `using PropertyType = FStrProperty;`
- L273 _public typedef_ `using ValueType = FString;`
- L282 _public function_ `static ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L285 _public function_ `static ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L288 _public function_ `static ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L291 _public function_ `static ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L319 _public typedef_ `using PropertyType = FNameProperty;`
- L320 _public typedef_ `using ValueType = FName;`
- L366 _public typedef_ `using PropertyType = FTextProperty;`
- L367 _public typedef_ `using ValueType = FText;`
- L394 _public typedef_ `using PropertyType = FArrayProperty;`
- L395 _public typedef_ `using ValueType = TArray<uint8>;`
- L408 _public typedef_ `using PropertyType = FSetProperty;`
- L422 _public typedef_ `using PropertyType = FMapProperty;`
- L438 _public typedef_ `using PropertyType = FStructProperty;`

#### struct `TRemoteControlPropertyTypeTraits`  
`template <> struct TRemoteControlPropertyTypeTraits<FStructProperty>`  
_L436-446_
- desc: RemoteControlPropertyTypeTraits for FStructProperty
- L157 _public typedef_ `using PropertyType = FNumericProperty;`
- L158 _public typedef_ `using ValueType = void;`
- L161 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L164 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L172 _public typedef_ `using PropertyType = InPropertyType;`
- L173 _public typedef_ `using ValueType = typename InPropertyType::TCppType;`
- L186 _public typedef_ `using PropertyType = FEnumProperty;`
- L187 _public typedef_ `using ValueType = uint8;`
- L223 _public typedef_ `using PropertyType = FBoolProperty;`
- L224 _public typedef_ `using ValueType = bool;`
- L233 _public function_ `static constexpr ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L236 _public function_ `static constexpr ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L239 _public function_ `static constexpr ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L242 _public function_ `static constexpr ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L272 _public typedef_ `using PropertyType = FStrProperty;`
- L273 _public typedef_ `using ValueType = FString;`
- L282 _public function_ `static ValueType DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L285 _public function_ `static ValueType DefaultRangeValueMax()` — The default maximum value for newly created range.
- L288 _public function_ `static ValueType DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L291 _public function_ `static ValueType DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L319 _public typedef_ `using PropertyType = FNameProperty;`
- L320 _public typedef_ `using ValueType = FName;`
- L366 _public typedef_ `using PropertyType = FTextProperty;`
- L367 _public typedef_ `using ValueType = FText;`
- L394 _public typedef_ `using PropertyType = FArrayProperty;`
- L395 _public typedef_ `using ValueType = TArray<uint8>;`
- L408 _public typedef_ `using PropertyType = FSetProperty;`
- L422 _public typedef_ `using PropertyType = FMapProperty;`
- L438 _public typedef_ `using PropertyType = FStructProperty;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FVector>`  
_L450-463_
- desc: RemoteControlTypeTraits for FVector
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FVector2D>`  
_L467-480_
- desc: RemoteControlTypeTraits for FVector2D
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FVector4>`  
_L484-497_
- desc: RemoteControlTypeTraits for FVector4
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FRotator>`  
_L501-514_
- desc: RemoteControlTypeTraits for FRotator
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FQuat>`  
_L518-531_
- desc: RemoteControlTypeTraits for FQuat
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FTransform>`  
_L535-560_
- desc: RemoteControlTypeTraits for FTransform
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FIntPoint>`  
_L564-577_
- desc: RemoteControlTypeTraits for FIntPoint
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FIntVector>`  
_L581-594_
- desc: RemoteControlTypeTraits for FIntVector
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FBox>`  
_L598-621_
- desc: RemoteControlTypeTraits for FBox
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FBox2D>`  
_L625-648_
- desc: RemoteControlTypeTraits for FBox2D
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FBoxSphereBounds>`  
_L652-665_
- desc: RemoteControlTypeTraits for FBoxSphereBounds
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FColor>`  
_L669-693_
- desc: RemoteControlTypeTraits for FColor
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRemoteControlTypeTraits`  
`template <> struct TRemoteControlTypeTraits<FLinearColor>`  
_L697-720_
- desc: RemoteControlTypeTraits for FLinearColor
- L107 _public typedef_ `using Type = ValueType;`
- L110 _public function_ `static constexpr bool IsSupportedRangeType()` — Is ValueType supported as a range (protocol input) value?
- L113 _public function_ `static constexpr bool IsSupportedMappingType()` — Is ValueType supported as a mapping (property output) value?
- L116 _public function_ `static constexpr Type DefaultRangeValueMin()` — The default minimum value for newly created range (protocol, input).
- L119 _public function_ `static constexpr Type DefaultRangeValueMax()` — The default maximum value for newly created range.
- L122 _public function_ `static constexpr Type DefaultMappingValueMin()` — The default minimum value for newly created mapping.
- L125 _public function_ `static constexpr Type DefaultMappingValueMax()` — The default maximum value for newly created mapping.
- L202 _public typedef_ `using Type = bool;`
- L251 _public typedef_ `using Type = FString;`
- L259 _public function_ `static Type DefaultRangeValueMin()`
- L261 _public function_ `static Type DefaultRangeValueMax()`
- L263 _public function_ `static Type DefaultMappingValueMin()`
- L265 _public function_ `static Type DefaultMappingValueMax()`
- L298 _public typedef_ `using Type = FName;`
- L345 _public typedef_ `using Type = FText;`
- L452 _public typedef_ `using Type = FVector;`
- L469 _public typedef_ `using Type = FVector2D;`
- L486 _public typedef_ `using Type = FVector4;`
- L503 _public typedef_ `using Type = FRotator;`
- L520 _public typedef_ `using Type = FQuat;`
- L537 _public typedef_ `using Type = FTransform;`
- L566 _public typedef_ `using Type = FIntPoint;`
- L583 _public typedef_ `using Type = FIntVector;`
- L600 _public typedef_ `using Type = FBox;`
- L627 _public typedef_ `using Type = FBox2D;`
- L654 _public typedef_ `using Type = FBoxSphereBounds;`
- L671 _public typedef_ `using Type = FColor;`
- L699 _public typedef_ `using Type = FLinearColor;`

#### struct `TRCTypeNameToType`  
`template <EName TypeName> struct TRCTypeNameToType`  
_L727-727_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_Int8Property>`  
_L729-729_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_Int8Property>`  
_L730-730_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_Int8Property>`  
_L731-731_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_Int8Property>`  
_L732-732_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_ByteProperty>`  
_L733-733_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_Int16Property>`  
_L734-734_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_UInt16Property>`  
_L735-735_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_IntProperty>`  
_L736-736_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_Int32Property>`  
_L737-737_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_FloatProperty>`  
_L739-739_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_FloatProperty>`  
_L740-740_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_FloatProperty>`  
_L741-741_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_BoolProperty>`  
_L743-743_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_BoolProperty>`  
_L744-744_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_StrProperty>`  
_L746-746_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_StrProperty>`  
_L747-747_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_StrProperty>`  
_L748-748_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_StrProperty>`  
_L749-749_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_ArrayProperty>`  
_L751-751_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_ArrayProperty>`  
_L752-752_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_ArrayProperty>`  
_L753-753_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_StructProperty>`  
_L755-755_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_StructProperty>`  
_L756-756_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_StructProperty>`  
_L757-757_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_StructProperty>`  
_L758-758_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_VectorProperty>`  
_L759-759_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_Vector>`  
_L760-760_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_Vector2D>`  
_L761-761_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_RotatorProperty>`  
_L762-762_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_Rotator>`  
_L763-763_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_ObjectProperty>`  
_L764-764_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_Box>`  
_L765-765_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_BoxSphereBounds>`  
_L766-766_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_Color>`  
_L767-767_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_IntPoint>`  
_L768-768_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_IntRect>`  
_L769-769_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_LinearColor>`  
_L770-770_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_Matrix>`  
_L771-771_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_Plane>`  
_L772-772_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### struct `TRCTypeNameToType`  
`template <> struct TRCTypeNameToType<NAME_Quat>`  
_L773-773_
- L727 _public typedef_ `template <EName TypeName> struct TRCTypeNameToType { using Type = void; };`
- L729 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int8Property> { using Type = int8; };`
- L733 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ByteProperty> { using Type = uint8; };`
- L734 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int16Property> { using Type = int16; };`
- L735 _public typedef_ `template <> struct TRCTypeNameToType<NAME_UInt16Property> { using Type = uint16; };`
- L736 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntProperty> { using Type = int32; };`
- L737 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Int32Property> { using Type = int32; };`
- L739 _public typedef_ `template <> struct TRCTypeNameToType<NAME_FloatProperty> { using Type = float; };`
- L743 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoolProperty> { using Type = bool; };`
- L746 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StrProperty> { using Type = FString; };`
- L751 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ArrayProperty> { using Type = FScriptArray; };`
- L755 _public typedef_ `template <> struct TRCTypeNameToType<NAME_StructProperty> { using Type = UScriptStruct; };`
- L759 _public typedef_ `template <> struct TRCTypeNameToType<NAME_VectorProperty> { using Type = FVector; };`
- L760 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector> { using Type = FVector; };`
- L761 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Vector2D> { using Type = FVector2D; };`
- L762 _public typedef_ `template <> struct TRCTypeNameToType<NAME_RotatorProperty> { using Type = FRotator; };`
- L763 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Rotator> { using Type = FRotator; };`
- L764 _public typedef_ `template <> struct TRCTypeNameToType<NAME_ObjectProperty> { using Type = UObject; };`
- L765 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Box> { using Type = FBox; };`
- L766 _public typedef_ `template <> struct TRCTypeNameToType<NAME_BoxSphereBounds> { using Type = FBoxSphereBounds; };`
- L767 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Color> { using Type = FColor; };`
- L768 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntPoint> { using Type = FIntPoint; };`
- L769 _public typedef_ `template <> struct TRCTypeNameToType<NAME_IntRect> { using Type = FIntRect; };`
- L770 _public typedef_ `template <> struct TRCTypeNameToType<NAME_LinearColor> { using Type = FLinearColor; };`
- L771 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Matrix> { using Type = FMatrix; };`
- L772 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Plane> { using Type = FPlane; };`
- L773 _public typedef_ `template <> struct TRCTypeNameToType<NAME_Quat> { using Type = FQuat; };`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace RemoteControlTypeTraits`
- L16 _namespace_ `namespace Concepts` (scope `RemoteControlTypeTraits`)
- L46 _enumerator_ `enum { Value = false };` (scope `RemoteControlTypeTraits::TIsStringLikeProperty::__anon6fea54570103`)
- L59 _enumerator_ `Value = true` (scope `RemoteControlTypeTraits::TIsStringLikeProperty::__anon6fea54570203`)
- L67 _enumerator_ `enum { Value = false };` (scope `RemoteControlTypeTraits::TIsStringLikeValue::__anon6fea54570303`)
- L80 _enumerator_ `Value = true` (scope `RemoteControlTypeTraits::TIsStringLikeValue::__anon6fea54570403`)
- L86 _variable_ `template <typename ValueType> constexpr bool TNumericValueConstraint_V = TModels_V<RemoteControlTypeTraits::Concepts::CNumerical, ValueType>;` (scope `RemoteControlTypeTraits`) — Ensures ValueType is a numeric type.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlCommon/Public/RCTypeUtilities.h` (Public)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace RemoteControlTypeUtilities`
- L35 _macro_ `#define FOREACH_CAST_PROPERTY(Property, Func) \` — Iterate and attempt to cast Property to different types (as CastPropertyType), where the instance will be CastProperty Usage: FProperty* SomePropertyInstance; template <> void SomeFunc<FNumericProperty>(const FNumericProperty*); etc.. FOREACH_CAST_PROPERTY(SomePropertyInstance, SomeFunc<CastPropertyType>(CastProperty))
- L147 _variable_ `static FName ClampMinKey = "Cl` (scope `RemoteControlTypeUtilities`)
- L148 _variable_ `static FName ClampMaxKey = "Cl` (scope `RemoteControlTypeUtilities`)
- L150 _variable_ `static FName UIMinKey = "UI` (scope `RemoteControlTypeUtilities`)
- L151 _variable_ `static FName UIMaxKey = "UI` (scope `RemoteControlTypeUtilities`)
- L155 _function_ `template <typename ValueType> static auto MinOp = [](auto&& InValues)` (scope `RemoteControlTypeUtilities`) — Delegated Min operator.
- L155 _variable_ `template <typename ValueType> static auto MinOp = [](auto&& InValues) { return FMath::Min(InValues); };` (scope `RemoteControlTypeUtilities`) — Delegated Min operator.
- L159 _function_ `template <typename ValueType> static auto MaxOp = [](auto&& InValues)` (scope `RemoteControlTypeUtilities`) — Delegated Max operator.
- L159 _variable_ `template <typename ValueType> static auto MaxOp = [](auto&& InValues) { return FMath::Max(InValues); };` (scope `RemoteControlTypeUtilities`) — Delegated Max operator.
- L167 _function_ `constexpr static ValueType GetMetadataValue(const PropertyType* InProperty, const FName& InKey, const ValueType& InDefaultValue)` (scope `RemoteControlTypeUtilities`)
- L194 _function_ `template <class Func, class PropertyType, class ValueType> static ValueType GetClampedValue(Func InFunc, const PropertyType* InProperty, ValueType InValue, const TArray<FName>& InMetaKeys)` (scope `RemoteControlTypeUtilities`)
- L212 _function_ `template <typename PropertyType, typename ValueType> static ValueType ClampToPropertyType(const FNumericProperty* InProperty, ValueType& InOutValue)` (scope `RemoteControlTypeUtilities`) — Clamps the value to the PropertyType, for example if an int64 is requested but the PropertyType is UInt16Property.
- L221 _typedef_ `using T = uint8;` (scope `RemoteControlTypeUtilities::ClampToPropertyType`)
- L226 _typedef_ `using T = int8;` (scope `RemoteControlTypeUtilities::ClampToPropertyType`)
- L231 _typedef_ `using T = int16;` (scope `RemoteControlTypeUtilities::ClampToPropertyType`)
- L236 _typedef_ `using T = uint16;` (scope `RemoteControlTypeUtilities::ClampToPropertyType`)
- L241 _typedef_ `using T = int32;` (scope `RemoteControlTypeUtilities::ClampToPropertyType`)
- L246 _typedef_ `using T = uint32;` (scope `RemoteControlTypeUtilities::ClampToPropertyType`)
- L251 _typedef_ `using T = int64;` (scope `RemoteControlTypeUtilities::ClampToPropertyType`)
- L256 _typedef_ `using T = uint64;` (scope `RemoteControlTypeUtilities::ClampToPropertyType`)
- L265 _typedef_ `using T = float;` (scope `RemoteControlTypeUtilities::ClampToPropertyType`)
- L270 _typedef_ `using T = double;` (scope `RemoteControlTypeUtilities::ClampToPropertyType`)
- L281 _prototype_ `template <typename PropertyType> static bool IsSupportedRangeType(const PropertyType* InProperty);` (scope `RemoteControlTypeUtilities`)
- L285 _function_ `template <typename PropertyType> static bool IsSupportedRangeType(const PropertyType* InProperty)` (scope `RemoteControlTypeUtilities`) — Is ValueType supported as a range (protocol input) value?
- L311 _prototype_ `template <typename PropertyType> static bool IsSupportedMappingType(const PropertyType* InProperty);` (scope `RemoteControlTypeUtilities`) — Is ValueType supported as a mapping (property output) value?
- L315 _function_ `template <typename PropertyType> static bool IsSupportedMappingType(const PropertyType* InProperty)` (scope `RemoteControlTypeUtilities`) — Is ValueType supported as a mapping (property output) value?
- L340 _function_ `template <typename ValueType> static constexpr ValueType GetDefaultRangeValueMin()` (scope `RemoteControlTypeUtilities`)
- L346 _function_ `template <typename ValueType> static ValueType GetDefaultRangeValueMin(const FProperty* InProperty)` (scope `RemoteControlTypeUtilities`)
- L370 _function_ `template <typename ValueType> static constexpr ValueType GetDefaultRangeValueMax()` (scope `RemoteControlTypeUtilities`)
- L376 _function_ `template <typename ValueType> static ValueType GetDefaultRangeValueMax(const FProperty* InProperty)` (scope `RemoteControlTypeUtilities`)
- L400 _function_ `template <typename ValueType> static constexpr ValueType GetDefaultMappingValueMin()` (scope `RemoteControlTypeUtilities`)
- L406 _function_ `template <typename ValueType> static ValueType GetDefaultMappingValueMin(const FProperty* InProperty)` (scope `RemoteControlTypeUtilities`)
- L432 _function_ `static TSharedPtr<ValueType> GetDefaultMappingValueMin(const FStructProperty* InProperty)` (scope `RemoteControlTypeUtilities`)
- L451 _function_ `template <typename ValueType> static constexpr ValueType GetDefaultMappingValueMax()` (scope `RemoteControlTypeUtilities`)
- L457 _function_ `template <typename ValueType> static ValueType GetDefaultMappingValueMax(const FProperty* InProperty)` (scope `RemoteControlTypeUtilities`)
- L483 _function_ `static TSharedPtr<ValueType> GetDefaultMappingValueMax(const FStructProperty* InProperty)` (scope `RemoteControlTypeUtilities`)
- L493 _variable_ `template <typename PropertyType> constexpr bool TPropertyConstraint_V = std::is_base_of_v<FProperty, PropertyType>;` (scope `RemoteControlTypeUtilities`)
- L500 _function_ `static ValueType GetDefaultRangeValueMin(const PropertyType* InProperty)` (scope `RemoteControlTypeUtilities`)
- L504 _typedef_ `using FTraits = TRemoteControlTypeTraits<ValueType>;` (scope `RemoteControlTypeUtilities::GetDefaultRangeValueMin`)
- L514 _function_ `static ValueType GetDefaultRangeValueMax(const FProperty* InProperty)` (scope `RemoteControlTypeUtilities`)
- L518 _typedef_ `using FTraits = TRemoteControlTypeTraits<ValueType>;` (scope `RemoteControlTypeUtilities::GetDefaultRangeValueMax`)
- L528 _function_ `static ValueType GetDefaultMappingValueMin(const FProperty* InProperty)` (scope `RemoteControlTypeUtilities`)
- L532 _typedef_ `using FTraits = TRemoteControlTypeTraits<ValueType>;` (scope `RemoteControlTypeUtilities::GetDefaultMappingValueMin`)
- L542 _function_ `static ValueType GetDefaultMappingValueMax(const FProperty* InProperty)` (scope `RemoteControlTypeUtilities`)
- L546 _typedef_ `using FTraits = TRemoteControlTypeTraits<ValueType>;` (scope `RemoteControlTypeUtilities::GetDefaultMappingValueMax`)
- L552 _prototype_ `SIZE_T GetPropertySize(const FProperty* InProperty, void* InData);` (scope `RemoteControlTypeUtilities`) — Size of given property + data, accounting for item count (arrays, strings, etc.)
- L556 _prototype_ `SIZE_T GetPropertySize(const TSharedPtr<IPropertyHandle>& InPropertyHandle);` (scope `RemoteControlTypeUtilities`) — Size of given property + data, accounting for item count (arrays, strings, etc.)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlCommon/Public/RemoteControlCommon.h` (Public)


#### enum `ERCProtocolBinding::Op`  
`enum Op : int`  
_L12-17_
- L14 _public enumerator_ `Added`
- L16 _public enumerator_ `Removed`

#### enum `ERCMask`  
`enum class ERCMask : uint8`  
_L21-32_
- reflection: `UENUM()`
- L23 _public enumerator_ `NoMask = 0x00`
- L25 _public enumerator_ `MaskA = 0x01`
- L27 _public enumerator_ `MaskB = 0x02`
- L29 _public enumerator_ `MaskC = 0x04`
- L31 _public enumerator_ `MaskD = 0x08`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ERCProtocolBinding`
- L35 _macro_ `#define RC_AllMasks (ERCMask)0xFF // All masks, used mainly for initialization` — Mask for all remote control masking flags
- L37 _prototype_ `ENUM_CLASS_FLAGS(ERCMask);`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlCommon/Public/RemoteControlSettings.h` (Public)


#### struct `FRCNetworkAddress`  
`struct FRCNetworkAddress`  
_L15-69_
- reflection: `USTRUCT(BlueprintType)`
- desc: Utility struct to represent IPv4 Network addresses.
- L19 _public prototype_ `FRCNetworkAddress() = default;`
- L20 _public function_ `FRCNetworkAddress(uint8 InClassA, uint8 InClassB, uint8 InClassC, uint8 InClassD) : ClassA(InClassA), ClassB(InClassB), ClassC(InClassC), ClassD(InClassD)`
- L24 _public function_ `bool operator==(const FRCNetworkAddress& OtherNetworkAddress) const`
- L49 _public function_ `const FString ToString() const` — Retrieves the network address as string e.g. 192.168.1.1
- L56 _public member_ `uint8 ClassA = 192;` — `UPROPERTY(EditAnywhere, Category="Network Address")` — Denotes the first octet of the IPv4 address (0-255.xxx.xxx.xxx)
- L60 _public member_ `uint8 ClassB = 168;` — `UPROPERTY(EditAnywhere, Category = "Network Address")` — Denotes the second octet of the IPv4 address (xxx.0-255.xxx.xxx)
- L64 _public member_ `uint8 ClassC = 1;` — `UPROPERTY(EditAnywhere, Category = "Network Address")` — Denotes the third octet of the IPv4 address (xxx.xxx.0-255.xxx)
- L68 _public member_ `uint8 ClassD = 1;` — `UPROPERTY(EditAnywhere, Category = "Network Address")` — Denotes the fourth octet of the IPv4 address (xxx.xxx.xxx.0-255)

#### struct `FRCNetworkAddressRange`  
`struct FRCNetworkAddressRange`  
_L75-158_
- reflection: `USTRUCT(BlueprintType)`
- desc: Utility struct to represent range of IPv4 Network addresses.
- L79 _public prototype_ `FRCNetworkAddressRange() = default;`
- L80 _public function_ `FRCNetworkAddressRange(FRCNetworkAddress InLowerBound, FRCNetworkAddress InUpperBound) : LowerBound(InLowerBound), UpperBound(InUpperBound)`
- L84 _public function_ `static FRCNetworkAddressRange AllowAllIPs()`
- L92 _public function_ `bool operator==(const FRCNetworkAddressRange& OtherNetworkAddressRange) const`
- L112 _public function_ `bool IsInRange(const FString& InNetworkAddress) const`
- L128 _public function_ `bool IsInRange(const FRCNetworkAddress& InNetworkAddress) const`
- L139 _private function_ `bool IsInRange_Internal(uint8 InClassA, uint8 InClassB, uint8 InClassC, uint8 InClassD) const`
- L153 _public member_ `FRCNetworkAddress LowerBound = { 192, 168, 1, 1 };` — `UPROPERTY(EditAnywhere, Category="Network Address Range")` — Denotes the lower bound IPv4 address.
- L157 _public member_ `FRCNetworkAddress UpperBound = { 192, 168, 255, 255 };` — `UPROPERTY(EditAnywhere, Category = "Network Address Range")` — Denotes the upper bound IPv4 address.

#### struct `FRCPassphrase`  
`struct FRCPassphrase`  
_L164-175_
- reflection: `USTRUCT(BlueprintType)`
- desc: Passphrase Struct
- L168 _public function_ `FRCPassphrase()`
- L171 _public member_ `FString Identifier;` — `UPROPERTY(EditAnywhere, Category="Passphrase")`
- L174 _public member_ `FString Passphrase;` — `UPROPERTY(EditAnywhere, Category="Passphrase")`

#### class `URemoteControlSettings`  
`class URemoteControlSettings : public UDeveloperSettings`  
_L181-421_
- reflection: `UCLASS(config = RemoteControl)`
- inherits: `UDeveloperSettings`
- desc: Global remote control settings
- L186 _public prototype_ `URemoteControlSettings();`
- L189 _public function_ `virtual FName GetContainerName() const` — Gets the settings container name for the settings, either Project or Editor
- L195 _public function_ `virtual FName GetCategoryName() const` — Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc.
- L201 _public function_ `virtual FName GetSectionName() const` — The unique name for your section of settings, uses the class's FName.
- L206 _public function_ `virtual FText GetSectionText() const`
- L211 _public function_ `virtual TArray<FString> GetHashedPassphrases() const`
- L223 _public function_ `virtual void AllowClient(const FString& InClientAddressStr)`
- L248 _public function_ `virtual bool IsClientAllowed(const FString& InClientAddressStr) const`
- L262 _public function_ `static const TSet<FName>& GetExposedEntitiesColumnNames()` — Returns the names of the columns visualized in the RC Panel Entities list.
- L283 _public member_ `bool bProtocolsGenerateTransactions_DEPRECATED = true;` — `UE_DEPRECATED(5.5, "Protocol Generate Transactions is now a per Preset option. See URemoteControlPreset::GetProtocolModifyOperationFlags.")` — `UPROPERTY(config)` — DEPRECATED 5.5 Should transactions be generated for events received through protocols (ie. MIDI, DMX etc.) Disabling transactions improves performance but will prevent events from being transacted to Multi-User unless using the Remote Control Interception feature.
- L287 _public member_ `FString RemoteControlWebInterfaceBindAddress = TEXT("0.0` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control Web Interface", DisplayName = "Remote Control Web Interface bind address")` — The remote control web app bind address.
- L291 _public member_ `uint32 RemoteControlWebInterfacePort = 30000;` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control Web Interface", DisplayName = "Remote Control Web Interface http Port")` — The remote control web app http port.
- L295 _public member_ `bool bForceWebAppBuildAtStartup = false;` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control Web Interface", DisplayName = "Force WebApp build at startup")` — Should force a build of the WebApp at startup.
- L299 _public member_ `bool bWebAppLogRequestDuration = false;` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control Web Interface", DisplayName = "Log WebApp requests handle duration")` — Should WebApp log timing.
- L303 _public member_ `bool bAutoStartWebServer = true;` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control Web Server")` — Whether web server is started automatically.
- L307 _public member_ `bool bAutoStartWebSocketServer = true;` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control Web Server")` — Whether web socket server is started automatically.
- L311 _public member_ `uint32 RemoteControlHttpServerPort = 30010;` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control Web Server", DisplayName = "Remote Control HTTP Server Port")` — The web remote control HTTP server's port.
- L315 _public member_ `FString RemoteControlWebsocketServerBindAddress = TEXT("0.0` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control Web Server", DisplayName = "Remote Control Websocket Bind Address")` — The address to bind the websocket server to. 0.0.0.0 will open the connection to everyone on your network, while 127.0.0.1 will only allow local requests to come through.
- L319 _public member_ `uint32 RemoteControlWebSocketServerPort = 30020;` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control Web Server", DisplayName = "Remote Control WebSocket Server Port")` — The web remote control WebSocket server's port.
- L323 _public member_ `bool bDisplayInEditorOnlyWarnings = false;` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control Preset", DisplayName = "Show a warning when exposing editor-only entities.")` — Show a warning icon for exposed editor-only fields.
- L327 _public member_ `float TreeBindingSplitRatio = 0.7f;` — `UPROPERTY(config)` — The split widget control ratio between entity tree and details/protocol binding list.
- L331 _public member_ `float ActionPanelSplitRatio = 0.6f;` — `UPROPERTY(config)` — The split widget control ratio between entity tree and details/protocol binding list.
- L334 _public member_ `bool bUseRebindingContext = true;` — `UPROPERTY(config)`
- L337 _public member_ `bool bIgnoreProtectedCheck = false;` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control Preset", DisplayName = "Ignore Remote Control Protected Check")`
- L340 _public member_ `bool bIgnoreGetterSetterCheck = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Remote Control Preset", DisplayName = "Ignore Remote Control Getter/Setter Check")`
- L343 _public member_ `bool bIgnoreWarnings = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Remote Control Preset")`
- L351 _public member_ `bool bAllowAnyRemoteFunctionCall = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Remote Control | Security")` — Enables any remote function execution, enabling this could open you up to vulnerabilities if an outside actor has access to your server. If true, any remote function call will be allowed. If false, only the built-in allowed functions and those specified in 'CustomAllowedRemoteFunctionCalls' will be considered.
- L355 _public member_ `bool bRestrictServerAccess = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Remote Control | Security")` — Whether to restrict access to a list of hostname/IPs in the AllowedOrigins setting.
- L359 _public member_ `bool bEnableRemotePythonExecution = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Remote Control | Security", meta = (editCondition = bRestrictServerAccess))` — Enable remote python execution, enabling this could open you up to vulnerabilities if an outside actor has access to your server.
- L363 _public member_ `bool bAllowConsoleCommandRemoteExecution = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Remote Control | Security", meta = (editCondition = bRestrictServerAccess))` — Enable calling 'ExecuteConsoleCommand' through the web api. Enabling this could open you up to vulnerabilities if an outside actor has access to your server.
- L370 _public member_ `TArray<FRCAllowedRemoteFunctionCall> AllowedRemoteFunctionCalls;` — `UPROPERTY()` — Specifies built-in function calls that are allowed to be called remotely. This is only considered if `bAllowAnyRemoteFunctionCall` is false NOTE: For console command and python execution, 'bAllowConsoleCommandRemoteExecution' and 'bEnableRemotePythonExecution' are still required to be enabled respectively.
- L377 _public member_ `TArray<FRCAllowedRemoteFunctionCall> CustomAllowedRemoteFunctionCalls;` — `UPROPERTY(Config, EditAnywhere, Category = "Remote Control | Security", meta = (EditCondition="!bAllowAnyRemoteFunctionCall", DisplayAfter="bAllowAnyRemoteFunctionCall"))` — Specifies custom function calls that are allowed to be called remotely. This is only considered if `bAllowAnyRemoteFunctionCall` is false NOTE: For console command and python execution, 'bAllowConsoleCommandRemoteExecution' and 'bEnableRemotePythonExecution' are still required to be enabled respectively.
- L381 _public member_ `TSet<FRCNetworkAddressRange> AllowlistedClients = { FRCNetworkAddressRange::AllowAllIPs() };` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control | Security", DisplayName = "Range of Allowlisted Clients", Meta = (EditCondition = bRestrictServerAccess, EditConditionHides))` — List of IP Addresses that are allowed to access the Web API without authentication.
- L389 _public member_ `FString AllowedOrigin = TEXT("*")` — `UPROPERTY(Config, EditAnywhere, Category = "Remote Control | Security", meta=(EditCondition=bRestrictServerAccess))` — Origin that can make requests to the remote control server. Should contain the hostname or IP of the server making requests to remote control. ie. "http://yourdomain.com", or "*" to allow all origins. @Note: This is used to block requests coming from a browser (ie. Coming from a script running on a website), ideally you should use both this setting and AllowListedClients, as a request coming from a websocket client can have an empty Origin. @Note Supports wildcards (ie. *.yourdomain.com)
- L395 _public member_ `bool bEnforcePassphraseForRemoteClients = true;` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control | Security", meta = (EditCondition = bRestrictServerAccess))` — Controls whether a passphrase should be required when remote control is accessed by a client outside of localhost.
- L399 _public member_ `TArray<FRCPassphrase> Passphrases = {};` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control | Security", DisplayName = "Remote Control Passphrase", meta = (EditCondition=bEnforcePassphraseForRemoteClients, EditConditionHides))` — List of passphrases used for accessing remote control outside of localhost.
- L403 _public member_ `bool bShowPassphraseDisabledWarning = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Remote Control | Security", DisplayName = "Warn that Passphrase might be disabled ", meta=(EditCondition=bRestrictServerAccess))` — Whether the User should be warned that Passphrase usage is disabled or now. Initially activated
- L406 _public member_ `bool bLogicPanelVisibility = false;` — `UPROPERTY(Config, EditAnywhere, Category = "Remote Control Preset", DisplayName = "Hide or Show the Logic panel by default")`
- L409 _public member_ `TSet<FName> EntitiesListHiddenColumns;` — `UPROPERTY(Config, EditAnywhere, Category = "Remote Control Preset", DisplayName = "Which columns to hide in the exposed entities list")`
- L412 _public member_ `FName DefaultPanelMode = TEXT("Set` — `UPROPERTY(Config, EditAnywhere, Category = "Remote Control Preset", DisplayName = "Default mode (e.g. Setup/Operation)")`
- L416 _public member_ `bool bRefreshExposedEntitiesOnObjectPropertyUpdate = true;` — `UPROPERTY(config, EditAnywhere, Category = "Remote Control Preset", DisplayName = "Refresh all exposed entities widgets on object properties update")` — Refresh all widgets in the exposed properties list when object properties are updated
- L420 _private member_ `bool bSecuritySettingsReviewed = false;` — `UPROPERTY(config)`

#### Free symbols / members of external scopes

- L38 _function_ `friend uint32 GetTypeHash(const FRCNetworkAddress& NetworkAddress)` — Calculates the hash for a Network Address. @param NetworkAddress The Network address to calculate the hash for. @return The hash.
- L104 _function_ `friend uint32 GetTypeHash(const FRCNetworkAddressRange& NetworkAddressRange)` — Calculates the hash for a Network Address Range. @param NetworkAddress The Network address range to calculate the hash for. @return The hash.
