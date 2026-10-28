# Plugins / AvalancheCore

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheCore`
- headers: 10; symbols: 97
- symbol kinds: class=4, enum=1, enumerator=2, function=35, macro=5, member=9, namespace=10, prototype=16, struct=12, typedef=2, variable=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheCore/Public/AvaDataView.h` (Public)


#### struct `UE::Ava::FDataView`  
`struct FDataView`  
_L15-95_
- desc: Short-lived pointer to an object or struct.
- L17 _public prototype_ `FDataView() = default;`
- L25 _public prototype_ `explicit FDataView(const UStruct* InStruct, void* InMemory);` — Generic struct constructor. Valid UStruct is required when passing in valid memory pointer. Both can be null and the constructed data view will be considered as invalid. @see IsValid
- L28 _public prototype_ `explicit FDataView(UObject* Object);` — UObject constructor.
- L34 _public prototype_ `bool IsValid() const;` — Check is the view is valid (both pointer and type are set). @return True if the view is valid.
- L37 _public prototype_ `bool IsValidFor(const UStruct* InStruct) const;` — Returns true if both the type and memory are set for the given struct.
- L41 _public function_ `template<typename T> bool IsValidFor() const` — Returns true if both the type and memory are set for the given struct.
- L47 _public function_ `template<typename T> const T* GetPtr() const`
- L53 _public function_ `template<typename T> const T& Get() const`
- L59 _public function_ `template<typename T> T* GetMutablePtr() const`
- L69 _public function_ `template<typename T> T& GetMutable() const`
- L75 _public function_ `const UStruct* GetStruct() const`
- L80 _public function_ `const void* GetMemory() const`
- L85 _public function_ `void* GetMutableMemory() const`
- L92 _protected member_ `const UStruct* Struct = nullptr;` — UClass or UScriptStruct of the data.
- L94 _protected member_ `void* Memory = nullptr;` — Memory pointing at the class or struct

#### struct `UE::Ava::FConstDataView`  
`struct FConstDataView`  
_L98-157_
- desc: Short-lived const pointer to an object or struct.
- L100 _public prototype_ `FConstDataView() = default;`
- L108 _public prototype_ `explicit FConstDataView(const UStruct* InStruct, const void* InMemory);` — Generic struct constructor. Valid UStruct is required when passing in valid memory pointer. Both can be null and the constructed data view will be considered as invalid. @see IsValid
- L111 _public prototype_ `explicit FConstDataView(const UObject* Object);` — UObject constructor.
- L114 _public prototype_ `bool IsValid() const;` — Returns true if both the type and memory are set.
- L117 _public prototype_ `bool IsValidFor(const UStruct* InStruct) const;` — Returns true if both the type and memory are set for the given struct.
- L120 _public function_ `template<typename T> bool IsValidFor() const`
- L126 _public function_ `template<typename T> requires (std::is_const_v<T>) T* GetPtr() const`
- L136 _public function_ `template<typename T> requires (std::is_const_v<T>) T& Get() const`
- L142 _public function_ `const UStruct* GetStruct() const`
- L147 _public function_ `const void* GetMemory() const`
- L154 _protected member_ `const UStruct* Struct = nullptr;` — UClass or UScriptStruct of the data.
- L156 _protected member_ `const void* Memory = nullptr;` — Const memory pointing at the class or struct

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API AVALANCHECORE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheCore/Public/AvaEnums.h` (Public)


#### enum `UE::Ava::EControlFlow`  
`enum class EControlFlow : uint8`  
_L11-17_
- desc: Indicates how iteration should be handled
- L14 _public enumerator_ `Continue` — Continue iteration
- L16 _public enumerator_ `Break` — Break iteration

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Ava` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheCore/Public/AvaField.h` (Public)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace AvaCore` (scope `UE`)
- L24 _variable_ `template<typename InStructType, typename InPropertyType> constexpr bool TFindPropertyCondition_V = ( TModels_V<CStaticClassProvider, InStructType> || TModels_V<CStaticStructProvider, InStructType> ) && std::is_base_of_v<FProperty, InPropertyType>;` (scope `UE::AvaCore`) — Find Property Conditions: 1) InStructType has a way to get UStruct (either via T::StaticClass(), or T::StaticStruct()) AND 2) InPropertyType is derived from FProperty
- L33 _function_ `InPropertyType* GetProperty(FName InMemberPropertyName)` (scope `UE::AvaCore`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheCore/Public/AvaPropertyChangeDispatcher.h` (Public)


#### class `TAvaPropertyChangeDispatcher`  
`template<typename InClassType> class TAvaPropertyChangeDispatcher`  
_L12-33_
- L15 _public typedef_ `using FMemberFunctionType = typename TMemFunPtrType< false, InClassType, void()>::Type;`
- L17 _public function_ `TAvaPropertyChangeDispatcher(std::initializer_list<TPairInitializer<const FName&, const FMemberFunctionType&>> InCallbacks) : PropertyChangedFunctions(InCallbacks)`
- L21 _public function_ `void OnPropertyChanged(InClassType* InObject, const FPropertyChangedEvent& InPropertyChangedEvent) const`
- L32 _private member_ `TMap<FName, FMemberFunctionType> PropertyChangedFunctions;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheCore/Public/AvaType.h` (Public)


#### struct `TAvaType`  
`template<typename T, bool = TIsValidAvaType<T>::Value> struct TAvaType`  
_L27-45_
- desc: Helps retrieve the FAvaTypeId for a given type T that satisfies the TIsValidAvaType requirement If this is requirement is not satisfied, TAvaType<T>::GetTypeId will be undefined for T. @see TIsValidAvaType
- L29 _public function_ `static FAvaTypeId GetTypeId()`

#### struct `TAvaType`  
`template<typename T> struct TAvaType<T, false>`  
_L49-51_
- desc: No support for types that do not have a way to get their FAvaTypeId
- L29 _public function_ `static FAvaTypeId GetTypeId()`

#### class `TAvaInherits`  
`template<typename T, typename... InSuperTypes> class TAvaInherits`  
_L58-113_
- desc: Holds the direct super types of a given type T. Also serves to Cast a provided pointer to a desired type id.
- L64 _private function_ `template<typename, typename InSuperType, typename... InOtherSuperTypes> static const void* Cast(const T* InPtr, const FAvaTypeId& InCastToType)`
- L93 _private function_ `template<typename> static const void* Cast(const T* InPtr, const FAvaTypeId& InCastToType)`
- L99 _public function_ `static const void* Cast(const T* InPtr, const FAvaTypeId& InCastToType)`

#### class `IAvaTypeCastable`  
`class IAvaTypeCastable`  
_L165-200_
- desc: Interface Class to perform actions like IsA, or CastTo @see UE_AVA_INHERITS
- L170 _public prototype_ `virtual ~IAvaTypeCastable() = default;`
- L172 _public prototype_ `virtual FAvaTypeId GetTypeId() const = 0;`
- L174 _public prototype_ `virtual const void* CastTo_Impl(FAvaTypeId InId) const = 0;`
- L177 _public function_ `template<typename T> bool IsA() const`
- L183 _public function_ `template<typename T> bool IsExactlyA() const`
- L189 _public function_ `template<typename T> T* CastTo()`
- L196 _public function_ `template<typename T> const T* CastTo() const`

#### Free symbols / members of external scopes

- L19 _typedef_ `template<typename T> using TIsValidAvaType = TOr<TModels<CAvaStaticTypeable, T>, TModels<CAvaStaticTypeable, TAvaExternalType<T>>>;` — Determines that a typename T is a valid "Ava Type" if a FAvaTypeId can be retrieved by calling either T::GetStaticTypeId() (via UE_AVA_TYPE) or TAvaExternalType<T>::GetStaticTypeId() (via UE_AVA_TYPE_EXTERNAL)
- L120 _macro_ `#define UE_AVA_TYPE(InThisType, ...) \` — Macro to provide type information (type id and super types). This should be used within the class/struct scope only. @see UE_AVA_TYPE_EXTERNAL for providing type information outside the class/struct scope
- L133 _macro_ `#define UE_AVA_TYPE_EXTERNAL(InExternalType, ...) \` — Macro to implement a specialization of TAvaExternalType to specify the UE_AVA_TYPE for a given type. This should only be done for types where a UE_AVA_TYPE internal implementation is not possible or desired. @see UE_AVA_TYPE
- L146 _macro_ `#define UE_AVA_INHERITS(InThisType, ...) \` — Macro to implement UE_AVA_TYPE for a given type and the overrides for the IAvaTypeCastable interface. This should be used within a class/struct that ultimately inherits from IAvaTypeCastable @see IAvaTypeCastable @see UE_AVA_TYPE
- L157 _macro_ `#define UE_AVA_INHERITS_WITH_SUPER(InThisType, InSuperType, ...) \`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheCore/Public/AvaTypeConcepts.h` (Public)


#### struct `CAvaStaticTypeable`  
`struct CAvaStaticTypeable`  
_L6-12_
- desc: Describes a type that has a GetStaticTypeId() static function that returns FAvaTypeId
- L9 _public prototype_ `template <typename T> auto Requires(class FAvaTypeId& Value)->decltype( Value = T::GetStaticTypeId() );`

#### struct `CAvaInheritable`  
`struct CAvaInheritable`  
_L18-22_
- desc: Describes a type with a FAvaInherits typedef or using declaration @see UE_AVA_TYPE macro
- L21 _public prototype_ `template<typename T> auto Requires()->typename T::FAvaInherits&;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheCore/Public/AvaTypeId.h` (Public)


#### class `FAvaTypeId`  
`class FAvaTypeId`  
_L8-48_
- L11 _public function_ `static FAvaTypeId Invalid()`
- L16 _public function_ `explicit FAvaTypeId(FName InTypeName) : Name(InTypeName)`
- L26 _public function_ `bool operator==(FAvaTypeId InOther) const`
- L31 _public function_ `bool IsValid() const`
- L36 _public function_ `FName ToName() const`
- L41 _public function_ `FString ToString() const`
- L47 _private member_ `FName Name;`

#### Free symbols / members of external scopes

- L21 _function_ `friend uint32 GetTypeHash(FAvaTypeId InTypeId)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheCore/Public/AvaTypeSharedPointer.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace AvaCore` (scope `UE`)
- L11 _function_ `template<typename InCastToType> TSharedPtr<InCastToType> CastSharedPtr(const TSharedPtr<IAvaTypeCastable>& InSharedPtr)` (scope `UE::AvaCore`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheCore/Public/AvaTypeTraits.h` (Public)


#### struct `UE::AvaCore::TIsDerivedFromAll`  
`template<typename InDerivedType> struct TIsDerivedFromAll<InDerivedType>`  
_L14-17_
- L16 _public member_ `static constexpr bool Value = true;`
- L22 _public member_ `static constexpr bool Value = std::is_base_of_v<InBaseType, InDerivedType>;`
- L28 _public member_ `static constexpr bool Value = TIsDerivedFromAll<InDerivedType, InBaseType>::Value && TIsDerivedFromAll<InDerivedType, InOtherBaseTypes...>::Value;`

#### struct `UE::AvaCore::TIsDerivedFromAll`  
`template<typename InDerivedType, typename InBaseType> struct TIsDerivedFromAll<InDerivedType, InBaseType>`  
_L20-23_
- L16 _public member_ `static constexpr bool Value = true;`
- L22 _public member_ `static constexpr bool Value = std::is_base_of_v<InBaseType, InDerivedType>;`
- L28 _public member_ `static constexpr bool Value = TIsDerivedFromAll<InDerivedType, InBaseType>::Value && TIsDerivedFromAll<InDerivedType, InOtherBaseTypes...>::Value;`

#### struct `UE::AvaCore::TIsDerivedFromAll`  
`template<typename InDerivedType, typename InBaseType, typename... InOtherBaseTypes> struct TIsDerivedFromAll<InDerivedType, InBaseType, InOtherBaseTypes...>`  
_L26-30_
- L16 _public member_ `static constexpr bool Value = true;`
- L22 _public member_ `static constexpr bool Value = std::is_base_of_v<InBaseType, InDerivedType>;`
- L28 _public member_ `static constexpr bool Value = TIsDerivedFromAll<InDerivedType, InBaseType>::Value && TIsDerivedFromAll<InDerivedType, InOtherBaseTypes...>::Value;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace AvaCore` (scope `UE`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheCore/Public/AvaWorldSubsystemUtils.h` (Public)


#### struct `CAvaWorldProvider`  
`struct CAvaWorldProvider`  
_L26-32_
- L29 _public prototype_ `template <typename T> auto Requires(UWorld*& OutWorld, const T& InObject) -> decltype( OutWorld = InObject.GetWorld() );`

#### struct `FAvaWorldSubsystemUtils`  
`struct FAvaWorldSubsystemUtils`  
_L34-86_
- L38 _public function_ `static InWorldSubsystemType* GetWorldSubsystem(const InWorldContextType* InWorldContext, bool bInGenerateErrors = false)`

#### struct `TAvaWorldSubsystemInterface`  
`template<typename InWorldSubsystemType> struct TAvaWorldSubsystemInterface`  
_L89-120_
- L93 _public function_ `static InWorldSubsystemType* Get(const InWorldContextType* InWorldContext, bool bInGenerateErrors = false)`
- L100 _public function_ `static bool SupportsWorldType(InWorldContextType* InWorldContext)`
