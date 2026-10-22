# Runtime / MassCore

- module root: `Source/Runtime/Mass/MassCore`
- headers: 7; symbols: 122
- symbol kinds: enum=3, enumerator=5, externvar=1, function=49, macro=10, member=11, namespace=7, prototype=18, struct=18
- PublicDependencyModuleNames: Core, CoreUObject, TraceLog

### `Source/Runtime/Mass/MassCore/Public/Mass/ArchetypeGroup.h` (Public)


#### struct `UE::Mass::FArchetypeGroupType`  
`struct FArchetypeGroupType`  
_L14-52_
- L16 _public member_ `constexpr static uint32 InvalidArchetypeGroupTypeIdentifier = static_cast<uint32>(INDEX_NONE);`
- L18 _public function_ `explicit FArchetypeGroupType(const uint32 Value = InvalidArchetypeGroupTypeIdentifier) : Identifier(Value)`
- L23 _public prototype_ `FArchetypeGroupType(const FArchetypeGroupType& Source) = default;`
- L30 _public function_ `bool operator==(const FArchetypeGroupType Other) const`
- L35 _public function_ `bool operator<(const FArchetypeGroupType Other) const`
- L40 _public function_ `explicit operator int32() const`
- L45 _public function_ `bool IsValid() const`
- L51 _private member_ `uint32 Identifier;`

#### struct `UE::Mass::FArchetypeGroupID`  
`struct FArchetypeGroupID`  
_L55-93_
- L57 _public member_ `constexpr static uint32 InvalidArchetypeGroupID = static_cast<uint32>(INDEX_NONE);`
- L58 _public member_ `constexpr static uint32 FirstGroupID = 0;`
- L60 _public prototype_ `FArchetypeGroupID() = default;`
- L61 _public function_ `FArchetypeGroupID(const uint32 InID) : ID(InID)`
- L66 _public function_ `bool operator==(const FArchetypeGroupID Other) const`
- L71 _public function_ `bool IsValid() const`
- L76 _public function_ `operator int32() const`
- L81 _public function_ `static FArchetypeGroupID First()`
- L86 _public function_ `FArchetypeGroupID Next() const`
- L92 _private member_ `uint32 ID = InvalidArchetypeGroupID;`

#### struct `UE::Mass::FArchetypeGroupHandle`  
`struct FArchetypeGroupHandle`  
_L98-154_
- L100 _public function_ `explicit FArchetypeGroupHandle(const FArchetypeGroupType InGroupType, const FArchetypeGroupID InGroupID) : GroupType(InGroupType), GroupID(InGroupID)`
- L105 _public prototype_ `FArchetypeGroupHandle() = default;`
- L107 _public function_ `bool operator==(const FArchetypeGroupHandle Other) const`
- L112 _public function_ `bool operator!=(const FArchetypeGroupHandle Other) const`
- L123 _public function_ `FArchetypeGroupType GetGroupType() const`
- L128 _public function_ `FArchetypeGroupID GetGroupID() const`
- L133 _public function_ `bool operator<(const FArchetypeGroupHandle Other) const`
- L138 _public function_ `void UpdateID(const FArchetypeGroupHandle Other)`
- L146 _public function_ `bool IsValid() const`
- L152 _private member_ `FArchetypeGroupType GroupType;`
- L153 _private member_ `FArchetypeGroupID GroupID;`

#### struct `UE::Mass::FArchetypeGroups`  
`struct FArchetypeGroups`  
_L159-212_
- L161 _public prototype_ `FArchetypeGroups() = default;`
- L162 _public prototype_ `FArchetypeGroups(const FArchetypeGroups& InGroups) = default;`
- L163 _public prototype_ `FArchetypeGroups(FArchetypeGroups&& InGroups) = default;`
- L165 _public prototype_ `bool operator==(const FArchetypeGroups& OtherGroups) const;`
- L166 _public prototype_ `FArchetypeGroups& operator=(FArchetypeGroups&& InGroups);`
- L167 _public prototype_ `FArchetypeGroups& operator=(const FArchetypeGroups& InGroups);`
- L172 _public prototype_ `void Add(FArchetypeGroupHandle GroupHandle);` — Adds or updates the given (GroupType, GroupID) combination to IDContainer
- L179 _public prototype_ `[[nodiscard]] FArchetypeGroups Add(FArchetypeGroupHandle GroupHandle) const;` — Adds or updates the given (GroupType, GroupID) combination to IDContainer @return a copy of this FArchetypeGroups container with GroupHandle added to the ID container @note using [[nodiscard]] to avoid accidental calls on const instances that would not produce any effects
- L185 _public prototype_ `void Remove(FArchetypeGroupType GroupType);` — Removes the stored GroupID associated with the given GroupType. If the given group type is not stored in IDContainer the request is ignored.
- L193 _public prototype_ `[[nodiscard]] FArchetypeGroups Remove(FArchetypeGroupType GroupType) const;` — Removes the stored GroupID associated with the given GroupType. If the given group type is not stored in IDContainer the request is ignored. @return a copy of this FArchetypeGroups container with GroupType removed. @note using [[nodiscard]] to avoid accidental calls on const instances that would not produce any effects
- L195 _public prototype_ `void Shrink();`
- L196 _public prototype_ `bool IsShrunk() const;`
- L198 _public function_ `FArchetypeGroupID GetID(const FArchetypeGroupType GroupType) const`
- L203 _public function_ `bool ContainsType(const FArchetypeGroupType GroupType) const`
- L211 _protected member_ `TSparseArray<FArchetypeGroupID> IDContainer;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mass` (scope `UE`)
- L25 _function_ `friend uint32 GetTypeHash(const FArchetypeGroupType& Instance)` (scope `UE::Mass`)
- L117 _function_ `friend uint32 GetTypeHash(const FArchetypeGroupHandle& Instance)` (scope `UE::Mass`)

### `Source/Runtime/Mass/MassCore/Public/Mass/EntityElementTypes.h` (Public)


#### struct `FMassElement`  
`struct FMassElement`  
_L8-11_
- reflection: `USTRUCT()`

#### struct `FMassFragment`  
`struct FMassFragment : public FMassElement`  
_L15-18_
- reflection: `USTRUCT()`
- inherits: `FMassElement`
- desc: This is the base class for all Mass fragments

#### struct `FMassSparseFragment`  
`struct FMassSparseFragment : public FMassFragment`  
_L30-33_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- desc: Special-case base class for fragments. Derive from this if you intend to use the fragment type as a sparse fragment See UE::Mass::FSparseElementsStorage for more details on sparse elements.

#### struct `FMassTag`  
`struct FMassTag : public FMassElement`  
_L40-43_
- reflection: `USTRUCT()`
- inherits: `FMassElement`
- desc: This is the base class for types that will only be tested for presence/absence, i.e. Tags. Subclasses should never contain any member properties.

#### struct `FMassSparseTag`  
`struct FMassSparseTag : public FMassTag`  
_L50-53_
- reflection: `USTRUCT()`
- inherits: `FMassTag`
- desc: Special-case base class for tags. Derive from this if you intend to use the tag type as a sparse tag See UE::Mass::FSparseElementsStorage for more details on sparse elements.

#### struct `FMassChunkFragment`  
`struct FMassChunkFragment : public FMassElement`  
_L56-59_
- reflection: `USTRUCT()`
- inherits: `FMassElement`

#### struct `FMassSharedFragment`  
`struct FMassSharedFragment : public FMassElement`  
_L62-65_
- reflection: `USTRUCT()`
- inherits: `FMassElement`

#### struct `FMassConstSharedFragment`  
`struct FMassConstSharedFragment : public FMassElement`  
_L68-71_
- reflection: `USTRUCT()`
- inherits: `FMassElement`

#### Free symbols / members of external scopes

- L21 _macro_ `#define _MASS_INVALID_FRAGMENT_CORE_MESSAGE "Make sure to inherit from FMassFragment or one of its child-types and ensure that the struct is trivially copyable, or opt out by specializing TMassFragmentTraits for this type and setting Author` — these are the messages we'll print out when static checks whether a given type is a fragment fails
- L22 _macro_ `#define MASS_INVALID_FRAGMENT_MSG "Given struct doesn't represent a valid fragment type." _MASS_INVALID_FRAGMENT_CORE_MESSAGE`
- L23 _macro_ `#define MASS_INVALID_FRAGMENT_MSG_F "Type %s is not a valid fragment type." _MASS_INVALID_FRAGMENT_CORE_MESSAGE`
- L73 _namespace_ `namespace UE`
- L73 _namespace_ `namespace Mass` (scope `UE`)
- L76 _function_ `template<typename T> bool IsA(const UStruct* )` (scope `UE::Mass`)
- L82 _function_ `template<> inline bool IsA<FMassElement>(const UStruct* Struct)` (scope `UE::Mass`)
- L89 _function_ `template<> inline bool IsA<FMassFragment>(const UStruct* Struct)` (scope `UE::Mass`)
- L95 _function_ `template<> inline bool IsA<FMassSparseFragment>(const UStruct* Struct)` (scope `UE::Mass`)
- L101 _function_ `template<> inline bool IsA<FMassTag>(const UStruct* Struct)` (scope `UE::Mass`)
- L107 _function_ `template<> inline bool IsA<FMassSparseTag>(const UStruct* Struct)` (scope `UE::Mass`)
- L113 _function_ `template<> inline bool IsA<FMassChunkFragment>(const UStruct* Struct)` (scope `UE::Mass`)
- L119 _function_ `template<> inline bool IsA<FMassSharedFragment>(const UStruct* Struct)` (scope `UE::Mass`)
- L125 _function_ `template<> inline bool IsA<FMassConstSharedFragment>(const UStruct* Struct)` (scope `UE::Mass`)
- L130 _function_ `inline bool IsSparse(TNotNull<const UStruct*> Struct)` (scope `UE::Mass`)

### `Source/Runtime/Mass/MassCore/Public/Mass/EntityFragments.h` (Public)


#### struct `FTransformFragment`  
`struct FTransformFragment : public FMassFragment`  
_L10-38_
- reflection: `USTRUCT()`
- inherits: `FMassFragment`
- L14 _public prototype_ `FTransformFragment() = default;`
- L15 _public function_ `FTransformFragment(const FTransform& InTransform) : Transform(InTransform)`
- L20 _public function_ `const FTransform& GetTransform() const`
- L25 _public function_ `void SetTransform(const FTransform& InTransform)`
- L30 _public function_ `FTransform& GetMutableTransform()`
- L37 _protected member_ `FTransform Transform;` — `UPROPERTY()`

### `Source/Runtime/Mass/MassCore/Public/Mass/EntityHandle.h` (Public)


#### struct `FMassEntityHandle`  
`struct alignas(8) FMassEntityHandle`  
_L12-89_
- reflection: `USTRUCT(BlueprintType)`
- desc: A handle to a Mass entity. An entity is used in conjunction with the FMassEntityManager for the current world and can contain lightweight fragments.
- L16 _public prototype_ `FMassEntityHandle() = default;`
- L17 _public function_ `FMassEntityHandle(const int32 InIndex, const int32 InSerialNumber) : Index(InIndex), SerialNumber(InSerialNumber)`
- L23 _public member_ `int32 Index = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Mass|Debug", Transient)`
- L26 _public member_ `int32 SerialNumber = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Mass|Debug", Transient)`
- L28 _public function_ `bool operator==(const FMassEntityHandle Other) const`
- L33 _public function_ `bool operator!=(const FMassEntityHandle Other) const`
- L39 _public function_ `bool operator<(const FMassEntityHandle Other) const` — Has meaning only for sorting purposes
- L46 _public function_ `bool IsSet() const` — Note that this function is merely checking if Index and SerialNumber are set. There's no way to validate if these indicate a valid entity in an EntitySubsystem without asking the system.
- L51 _public function_ `inline bool IsValid() const`
- L56 _public function_ `void Reset()`
- L63 _public function_ `uint64 AsNumber() const` — Relying on the fact that this struct only stores 2 integers and is aligned correctly.
- L68 _public function_ `static FMassEntityHandle FromNumber(uint64 Value)` — Reconstruct the entity handle from an anonymously shared integer.
- L85 _public function_ `FString DebugGetDescription() const`

#### Free symbols / members of external scopes

- L75 _function_ `friend uint32 GetTypeHash(const FMassEntityHandle Entity)`
- L80 _function_ `friend FString LexToString(const FMassEntityHandle Entity)`

### `Source/Runtime/Mass/MassCore/Public/Mass/EntityMacros.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define WITH_MASSENTITY_DEBUG (!(UE_BUILD_SHIPPING || UE_BUILD_SHIPPING_WITH_EDITOR || UE_BUILD_TEST) && WITH_STRUCTUTILS_DEBUG && 1)`

### `Source/Runtime/Mass/MassCore/Public/Mass/ExternalSubsystemTraits.h` (Public)


#### struct `TMassExternalSubsystemTraits`  
`template <typename T> struct TMassExternalSubsystemTraits final`  
_L26-36_
- desc: Traits describing how a given piece of code can be used by Mass. We require author or user of a given subsystem to define its traits. To do it add the following in an accessible location. template<> struct TMassExternalSubsystemTraits<UMyCustomManager> { enum { GameThreadOnly = false } } this will let Mass know it can access UMyCustomManager on any thread. This information is being used to calculate processor and query dependencies as well as appropriate distribution of calculations across threads.

#### enum `TMassExternalSubsystemTraits::(anonymous)`  
``  
_L29-35_

#### struct `TMassSharedFragmentTraits`  
`template <typename T> struct TMassSharedFragmentTraits final`  
_L43-50_
- desc: Shared Fragment traits. @see TMassExternalSubsystemTraits

#### enum `TMassSharedFragmentTraits::(anonymous)`  
``  
_L46-49_

#### struct `TMassFragmentTraits`  
`template <typename T> struct TMassFragmentTraits final`  
_L57-67_
- desc: Fragment traits. @see TMassExternalSubsystemTraits

#### enum `TMassFragmentTraits::(anonymous)`  
``  
_L60-66_

#### Free symbols / members of external scopes

- L31 _enumerator_ `GameThreadOnly = true` (scope `TMassExternalSubsystemTraits::__anon6121cea80103`) — Unless configured otherwise each subsystem will be treated as "game-thread only".
- L34 _enumerator_ `ThreadSafeWrite = !GameThreadOnly` (scope `TMassExternalSubsystemTraits::__anon6121cea80103`) — If set to true all RW and RO operations will be viewed as RO when calculating processor dependencies
- L47 _enumerator_ `GameThreadOnly = false` (scope `TMassSharedFragmentTraits::__anon6121cea80203`)
- L48 _enumerator_ `ThreadSafeWrite = false` (scope `TMassSharedFragmentTraits::__anon6121cea80203`)
- L65 _enumerator_ `AuthorAcceptsItsNotTriviallyCopyable = false` (scope `TMassFragmentTraits::__anon6121cea80303`) — Fragment types are best kept trivially copyable for performance reasons. To enforce that we test this trait when checking if a given type is a valid fragment type. This test can be skipped by specifically opting out, which also documents that making the given type non-trivially-copyable was a deliberate decision.

### `Source/Runtime/Mass/MassCore/Public/Mass/TestableEnsures.h` (Public)


#### struct `FMassTestableEnsureScope`  
`struct FMassTestableEnsureScope`  
_L71-71_

#### Free symbols / members of external scopes

- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMassTestableEnsures, Log, All);`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Mass` (scope `UE`)
- L20 _namespace_ `namespace Test` (scope `UE::Mass`)
- L24 _externvar_ `extern int32 TestsInProgress;` (scope `UE::Mass::Test`) — Counter indicating how many test scopes are active. When > 0, testable macros log instead of crashing.
- L27 _macro_ `#define testableEnsureMsgf(InExpression, InFormat, ... ) \`
- L41 _macro_ `#define testableCheckf(InExpression, InFormat, ... ) \`
- L55 _macro_ `#define testableCheckfReturn(InExpression, ReturnExpression, InFormat, ... ) \`
- L73 _macro_ `#define testableEnsureMsgf ensureMsgf`
- L74 _macro_ `#define testableCheckf checkf`
- L75 _macro_ `#define testableCheckfReturn(InExpression, ReturnValue, InFormat, ... ) checkf(InExpression, InFormat, ##__VA_ARGS__)`
