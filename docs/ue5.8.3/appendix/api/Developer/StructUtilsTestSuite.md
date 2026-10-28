# Developer / StructUtilsTestSuite

- module root: `Source/Developer/StructUtilsTestSuite`
- headers: 2; symbols: 71
- symbol kinds: class=7, enum=2, enumerator=5, function=9, member=19, prototype=14, struct=15
- PrivateDependencyModuleNames: UnrealEd
- PublicDependencyModuleNames: AIModule, AITestSuite, Core, CoreUObject, Engine

### `Source/Developer/StructUtilsTestSuite/Public/StructUtilsTestSuiteModule.h` (Public)


#### class `IStructUtilsTestSuiteModule`  
`class IStructUtilsTestSuiteModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline IStructUtilsTestSuiteModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Source/Developer/StructUtilsTestSuite/Public/StructUtilsTestTypes.h` (Public)


#### struct `FTestStructSimpleBase`  
`struct FTestStructSimpleBase`  
_L10-13_
- reflection: `USTRUCT()`

#### struct `FTestStructSimple`  
`struct FTestStructSimple : public FTestStructSimpleBase`  
_L16-30_
- reflection: `USTRUCT()`
- inherits: `FTestStructSimpleBase`
- L20 _public prototype_ `FTestStructSimple() = default;`
- L21 _public function_ `FTestStructSimple(const float InFloat) : Float(InFloat)`
- L23 _public function_ `bool operator==(const FTestStructSimple& Other) const`
- L29 _public member_ `float Float = 0.0f;` — `UPROPERTY()`

#### struct `FTestStructSimpleNonZeroDefault`  
`struct FTestStructSimpleNonZeroDefault : public FTestStructSimpleBase`  
_L33-53_
- reflection: `USTRUCT()`
- inherits: `FTestStructSimpleBase`
- L37 _public prototype_ `FTestStructSimpleNonZeroDefault() = default;`
- L39 _public function_ `bool operator==(const FTestStructSimpleNonZeroDefault& Other) const`
- L44 _public function_ `bool operator!=(const FTestStructSimpleNonZeroDefault& Other) const`
- L50 _public member_ `float Float = 100.0f;` — `UPROPERTY()`
- L51 _public member_ `bool Bool = true;`

#### struct `FTestStructComplex`  
`struct FTestStructComplex`  
_L56-68_
- reflection: `USTRUCT()`
- L60 _public prototype_ `FTestStructComplex() = default;`
- L61 _public function_ `FTestStructComplex(const FString& InString) : String(InString)`
- L64 _public member_ `FString String;` — `UPROPERTY()`
- L67 _public member_ `TArray<FString> StringArray;` — `UPROPERTY()`

#### struct `FTestStructSimple1`  
`struct FTestStructSimple1 : public FTestStructSimpleBase`  
_L71-79_
- reflection: `USTRUCT()`
- inherits: `FTestStructSimpleBase`
- L75 _public prototype_ `FTestStructSimple1() = default;`
- L78 _public member_ `float Float = 0.0f;` — `UPROPERTY()`

#### struct `FTestStructSimple2`  
`struct FTestStructSimple2 : public FTestStructSimpleBase`  
_L82-90_
- reflection: `USTRUCT()`
- inherits: `FTestStructSimpleBase`
- L86 _public prototype_ `FTestStructSimple2() = default;`
- L89 _public member_ `float Float = 0.0f;` — `UPROPERTY()`

#### struct `FTestStructSimple3`  
`struct FTestStructSimple3 : public FTestStructSimpleBase`  
_L93-101_
- reflection: `USTRUCT()`
- inherits: `FTestStructSimpleBase`
- L97 _public prototype_ `FTestStructSimple3() = default;`
- L100 _public member_ `float Float = 0.0f;` — `UPROPERTY()`

#### struct `FTestStructSimple4`  
`struct FTestStructSimple4 : public FTestStructSimpleBase`  
_L104-112_
- reflection: `USTRUCT()`
- inherits: `FTestStructSimpleBase`
- L108 _public prototype_ `FTestStructSimple4() = default;`
- L111 _public member_ `float Float = 0.0f;` — `UPROPERTY()`

#### struct `FTestStructSimple5`  
`struct FTestStructSimple5 : public FTestStructSimpleBase`  
_L115-123_
- reflection: `USTRUCT()`
- inherits: `FTestStructSimpleBase`
- L119 _public prototype_ `FTestStructSimple5() = default;`
- L122 _public member_ `float Float = 0.0f;` — `UPROPERTY()`

#### struct `FTestStructSimple6`  
`struct FTestStructSimple6 : public FTestStructSimpleBase`  
_L126-134_
- reflection: `USTRUCT()`
- inherits: `FTestStructSimpleBase`
- L130 _public prototype_ `FTestStructSimple6() = default;`
- L133 _public member_ `float Float = 0.0f;` — `UPROPERTY()`

#### struct `FTestStructSimple7`  
`struct FTestStructSimple7 : public FTestStructSimpleBase`  
_L137-145_
- reflection: `USTRUCT()`
- inherits: `FTestStructSimpleBase`
- L141 _public prototype_ `FTestStructSimple7() = default;`
- L144 _public member_ `float Float = 0.0f;` — `UPROPERTY()`

#### struct `FTestStructHashable1`  
`struct FTestStructHashable1 : public FTestStructSimpleBase`  
_L148-156_
- reflection: `USTRUCT()`
- inherits: `FTestStructSimpleBase`
- L152 _public prototype_ `FTestStructHashable1() = default;`
- L155 _public member_ `float Float = 0.0f;` — `UPROPERTY()`

#### struct `FTestStructHashable2`  
`struct FTestStructHashable2 : public FTestStructSimpleBase`  
_L161-169_
- reflection: `USTRUCT()`
- inherits: `FTestStructSimpleBase`
- L165 _public prototype_ `FTestStructHashable2() = default;`
- L168 _public member_ `int Int = 0;` — `UPROPERTY()`

#### struct `FTestStructNonTrivialDestructor`  
`struct FTestStructNonTrivialDestructor`  
_L174-189_
- reflection: `USTRUCT()`
- L178 _public function_ `FTestStructNonTrivialDestructor()`
- L183 _public function_ `~FTestStructNonTrivialDestructor()`
- L188 _public member_ `static inline int32 NumConstructed = 0;`

#### class `UBagTestObject1`  
`class UBagTestObject1 : public UObject`  
_L192-195_
- reflection: `UCLASS()`
- inherits: `UObject`

#### class `UBagTestObject2`  
`class UBagTestObject2 : public UObject`  
_L198-201_
- reflection: `UCLASS()`
- inherits: `UObject`

#### class `UBagTestObject1Derived`  
`class UBagTestObject1Derived : public UBagTestObject1`  
_L204-207_
- reflection: `UCLASS()`
- inherits: `UBagTestObject1`

#### class `UBagTestObject1Derived2`  
`class UBagTestObject1Derived2 : public UBagTestObject1`  
_L210-213_
- reflection: `UCLASS()`
- inherits: `UBagTestObject1`

#### enum `EPropertyBagTest1`  
`enum class EPropertyBagTest1 : uint8`  
_L216-221_
- reflection: `UENUM()`
- L218 _public enumerator_ `Foo`
- L219 _public enumerator_ `Bar`
- L220 _public enumerator_ `Baz`

#### enum `EPropertyBagTest2`  
`enum class EPropertyBagTest2 : uint8`  
_L224-228_
- reflection: `UENUM()`
- L226 _public enumerator_ `Bingo`
- L227 _public enumerator_ `Bongo`

#### class `UTestObjectWithPropertyBag`  
`class UTestObjectWithPropertyBag : public UObject`  
_L231-238_
- reflection: `UCLASS()`
- inherits: `UObject`
- L237 _public member_ `FInstancedPropertyBag Bag;` — `UPROPERTY()`

#### class `UTestObjectWithInstanceStruct`  
`class UTestObjectWithInstanceStruct : public UObject`  
_L241-248_
- reflection: `UCLASS()`
- inherits: `UObject`
- L247 _public member_ `FInstancedStruct Value;` — `UPROPERTY()`

#### struct `FTestStructWithSubClassOf`  
`struct FTestStructWithSubClassOf`  
_L251-260_
- reflection: `USTRUCT()`
- L256 _public member_ `TSubclassOf<UBagTestObject1> ClassProperty;` — `UPROPERTY()`
- L259 _public member_ `TSoftClassPtr<UBagTestObject1> SoftClassProperty;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L158 _prototype_ `uint32 GetTypeHash(const FTestStructHashable1& other);`
- L171 _prototype_ `uint32 GetTypeHash(const FTestStructHashable2& other);`
