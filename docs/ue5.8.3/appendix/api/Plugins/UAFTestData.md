# Plugins / UAFTestData

- module root: `Plugins/Experimental/UAF/UAF/Source/UAFTestData`
- headers: 1; symbols: 145
- symbol kinds: enum=2, enumerator=6, member=132, namespace=1, struct=4
- PublicDependencyModuleNames: Core, CoreUObject, UAF

### `Plugins/Experimental/UAF/UAF/Source/UAFTestData/Public/UAFTestVars.h` (Public)


#### enum `EUAFTestEnum`  
`enum class EUAFTestEnum : uint8`  
_L9-14_
- reflection: `UENUM()`
- L11 _public enumerator_ `ValueA = 0`
- L12 _public enumerator_ `ValueB = 1`
- L13 _public enumerator_ `ValueC = 2`

#### enum `EUAFTestByteEnum::Type`  
`enum Type : uint8`  
_L20-25_
- L22 _public enumerator_ `ByteA = 0`
- L23 _public enumerator_ `ByteB = 1`
- L24 _public enumerator_ `ByteC = 2`

#### struct `FUAFPackedByteStruct`  
`struct FUAFPackedByteStruct`  
_L30-45_
- reflection: `USTRUCT()`
- desc: Struct with adjacent small fields for testing SubProperty overread safety.
- L35 _public member_ `uint8 Val1 = 0;` — `UPROPERTY()`
- L38 _public member_ `uint8 Val2 = 0;` — `UPROPERTY()`
- L41 _public member_ `EUAFTestEnum EnumVal = EUAFTestEnum::ValueA;` — `UPROPERTY()`
- L44 _public member_ `float FloatVal = 0.0f;` — `UPROPERTY()`

#### struct `FUAFNestedTestStruct`  
`struct FUAFNestedTestStruct`  
_L49-61_
- reflection: `USTRUCT()`
- desc: Nested struct for FBindableStruct SubProperty binding tests.
- L54 _public member_ `FVector Vec = FVector::ZeroVector;` — `UPROPERTY()`
- L57 _public member_ `FQuat Quat = FQuat::Identity;` — `UPROPERTY()`
- L60 _public member_ `FTransform Transform = FTransform::Identity;` — `UPROPERTY()`

#### struct `FUAFTestVars`  
`struct FUAFTestVars`  
_L70-118_
- reflection: `USTRUCT()`
- desc: Minimal USTRUCT used only in UAF LLT unit tests. Provides a set of typed properties that cover the common resolved types (bool, float, double, int32, FVector, FQuat) so that FBindableXxx runtime resolution tests can exercise variable and sub-property binding against a live FUAFAssetInstance.
- L75 _public member_ `bool bBool = false;` — `UPROPERTY()`
- L78 _public member_ `float FloatVal = 0.0f;` — `UPROPERTY()`
- L81 _public member_ `double DoubleVal = 0.0;` — `UPROPERTY()`
- L84 _public member_ `int32 IntVal = 0;` — `UPROPERTY()`
- L87 _public member_ `FVector VectorVar = FVector::ZeroVector;` — `UPROPERTY()`
- L90 _public member_ `FQuat QuatVar = FQuat::Identity;` — `UPROPERTY()`
- L93 _public member_ `FTransform TransformVar = FTransform::Identity;` — `UPROPERTY()`
- L96 _public member_ `FUAFNestedTestStruct NestedVar;` — `UPROPERTY()`
- L99 _public member_ `int64 Int64Val = 0;` — `UPROPERTY()`
- L102 _public member_ `uint8 ByteVal = 0;` — `UPROPERTY()`
- L105 _public member_ `FName NameVar;` — `UPROPERTY()`
- L108 _public member_ `EUAFTestEnum EnumVar = EUAFTestEnum::ValueA;` — `UPROPERTY()`
- L111 _public member_ `TEnumAsByte<EUAFTestByteEnum::Type> EnumAsByteVar = EUAFTestByteEnum::ByteA;` — `UPROPERTY()`
- L114 _public member_ `TObjectPtr<UObject> ObjectVar = nullptr;` — `UPROPERTY()`
- L117 _public member_ `FUAFPackedByteStruct PackedByteVar;` — `UPROPERTY()`

#### struct `FUAFPerfVars10`  
`struct FUAFPerfVars10`  
_L122-466_
- reflection: `USTRUCT()`
- desc: 10-property struct used by bulk-resolution performance benchmarks.
- L128 _public member_ `float f0 = 0.f;` — `UPROPERTY()` — Float targets/sources for variable-binding benchmark
- L131 _public member_ `float f1 = 0.f;` — `UPROPERTY()`
- L134 _public member_ `float f2 = 0.f;` — `UPROPERTY()`
- L137 _public member_ `float f3 = 0.f;` — `UPROPERTY()`
- L140 _public member_ `float f4 = 0.f;` — `UPROPERTY()`
- L143 _public member_ `float f5 = 0.f;` — `UPROPERTY()`
- L146 _public member_ `float f6 = 0.f;` — `UPROPERTY()`
- L149 _public member_ `float f7 = 0.f;` — `UPROPERTY()`
- L152 _public member_ `float f8 = 0.f;` — `UPROPERTY()`
- L155 _public member_ `float f9 = 0.f;` — `UPROPERTY()`
- L159 _public member_ `FVector v0 = FVector::ZeroVector;` — `UPROPERTY()` — Vector sources for subproperty-binding benchmark (bind .X → f0..f9)
- L162 _public member_ `FVector v1 = FVector::ZeroVector;` — `UPROPERTY()`
- L165 _public member_ `FVector v2 = FVector::ZeroVector;` — `UPROPERTY()`
- L168 _public member_ `FVector v3 = FVector::ZeroVector;` — `UPROPERTY()`
- L171 _public member_ `FVector v4 = FVector::ZeroVector;` — `UPROPERTY()`
- L174 _public member_ `FVector v5 = FVector::ZeroVector;` — `UPROPERTY()`
- L177 _public member_ `FVector v6 = FVector::ZeroVector;` — `UPROPERTY()`
- L180 _public member_ `FVector v7 = FVector::ZeroVector;` — `UPROPERTY()`
- L183 _public member_ `FVector v8 = FVector::ZeroVector;` — `UPROPERTY()`
- L186 _public member_ `FVector v9 = FVector::ZeroVector;` — `UPROPERTY()`
- L190 _public member_ `bool bBool0 = false;` — `UPROPERTY()` — Bool sources for FBindableBool direct binding benchmark
- L193 _public member_ `bool bBool1 = false;` — `UPROPERTY()`
- L196 _public member_ `bool bBool2 = false;` — `UPROPERTY()`
- L199 _public member_ `bool bBool3 = false;` — `UPROPERTY()`
- L202 _public member_ `bool bBool4 = false;` — `UPROPERTY()`
- L205 _public member_ `bool bBool5 = false;` — `UPROPERTY()`
- L208 _public member_ `bool bBool6 = false;` — `UPROPERTY()`
- L211 _public member_ `bool bBool7 = false;` — `UPROPERTY()`
- L214 _public member_ `bool bBool8 = false;` — `UPROPERTY()`
- L217 _public member_ `bool bBool9 = false;` — `UPROPERTY()`
- L221 _public member_ `double d0 = 0.0;` — `UPROPERTY()` — Double sources for FBindableDouble direct binding benchmark
- L224 _public member_ `double d1 = 0.0;` — `UPROPERTY()`
- L227 _public member_ `double d2 = 0.0;` — `UPROPERTY()`
- L230 _public member_ `double d3 = 0.0;` — `UPROPERTY()`
- L233 _public member_ `double d4 = 0.0;` — `UPROPERTY()`
- L236 _public member_ `double d5 = 0.0;` — `UPROPERTY()`
- L239 _public member_ `double d6 = 0.0;` — `UPROPERTY()`
- L242 _public member_ `double d7 = 0.0;` — `UPROPERTY()`
- L245 _public member_ `double d8 = 0.0;` — `UPROPERTY()`
- L248 _public member_ `double d9 = 0.0;` — `UPROPERTY()`
- L252 _public member_ `int32 i0 = 0;` — `UPROPERTY()` — Int32 sources for FBindableInt32 direct binding benchmark
- L255 _public member_ `int32 i1 = 0;` — `UPROPERTY()`
- L258 _public member_ `int32 i2 = 0;` — `UPROPERTY()`
- L261 _public member_ `int32 i3 = 0;` — `UPROPERTY()`
- L264 _public member_ `int32 i4 = 0;` — `UPROPERTY()`
- L267 _public member_ `int32 i5 = 0;` — `UPROPERTY()`
- L270 _public member_ `int32 i6 = 0;` — `UPROPERTY()`
- L273 _public member_ `int32 i7 = 0;` — `UPROPERTY()`
- L276 _public member_ `int32 i8 = 0;` — `UPROPERTY()`
- L279 _public member_ `int32 i9 = 0;` — `UPROPERTY()`
- L283 _public member_ `int64 l0 = 0;` — `UPROPERTY()` — Int64 sources for FBindableInt64 direct binding benchmark
- L286 _public member_ `int64 l1 = 0;` — `UPROPERTY()`
- L289 _public member_ `int64 l2 = 0;` — `UPROPERTY()`
- L292 _public member_ `int64 l3 = 0;` — `UPROPERTY()`
- L295 _public member_ `int64 l4 = 0;` — `UPROPERTY()`
- L298 _public member_ `int64 l5 = 0;` — `UPROPERTY()`
- L301 _public member_ `int64 l6 = 0;` — `UPROPERTY()`
- L304 _public member_ `int64 l7 = 0;` — `UPROPERTY()`
- L307 _public member_ `int64 l8 = 0;` — `UPROPERTY()`
- L310 _public member_ `int64 l9 = 0;` — `UPROPERTY()`
- L314 _public member_ `uint8 u0 = 0;` — `UPROPERTY()` — Byte sources for FBindableByte direct binding benchmark
- L317 _public member_ `uint8 u1 = 0;` — `UPROPERTY()`
- L320 _public member_ `uint8 u2 = 0;` — `UPROPERTY()`
- L323 _public member_ `uint8 u3 = 0;` — `UPROPERTY()`
- L326 _public member_ `uint8 u4 = 0;` — `UPROPERTY()`
- L329 _public member_ `uint8 u5 = 0;` — `UPROPERTY()`
- L332 _public member_ `uint8 u6 = 0;` — `UPROPERTY()`
- L335 _public member_ `uint8 u7 = 0;` — `UPROPERTY()`
- L338 _public member_ `uint8 u8 = 0;` — `UPROPERTY()`
- L341 _public member_ `uint8 u9 = 0;` — `UPROPERTY()`
- L345 _public member_ `FName nm0;` — `UPROPERTY()` — FName sources for FBindableName direct binding benchmark
- L348 _public member_ `FName nm1;` — `UPROPERTY()`
- L351 _public member_ `FName nm2;` — `UPROPERTY()`
- L354 _public member_ `FName nm3;` — `UPROPERTY()`
- L357 _public member_ `FName nm4;` — `UPROPERTY()`
- L360 _public member_ `FName nm5;` — `UPROPERTY()`
- L363 _public member_ `FName nm6;` — `UPROPERTY()`
- L366 _public member_ `FName nm7;` — `UPROPERTY()`
- L369 _public member_ `FName nm8;` — `UPROPERTY()`
- L372 _public member_ `FName nm9;` — `UPROPERTY()`
- L376 _public member_ `EUAFTestEnum en0 = EUAFTestEnum::ValueA;` — `UPROPERTY()` — Enum sources for FBindableEnum direct binding benchmark
- L379 _public member_ `EUAFTestEnum en1 = EUAFTestEnum::ValueA;` — `UPROPERTY()`
- L382 _public member_ `EUAFTestEnum en2 = EUAFTestEnum::ValueA;` — `UPROPERTY()`
- L385 _public member_ `EUAFTestEnum en3 = EUAFTestEnum::ValueA;` — `UPROPERTY()`
- L388 _public member_ `EUAFTestEnum en4 = EUAFTestEnum::ValueA;` — `UPROPERTY()`
- L391 _public member_ `EUAFTestEnum en5 = EUAFTestEnum::ValueA;` — `UPROPERTY()`
- L394 _public member_ `EUAFTestEnum en6 = EUAFTestEnum::ValueA;` — `UPROPERTY()`
- L397 _public member_ `EUAFTestEnum en7 = EUAFTestEnum::ValueA;` — `UPROPERTY()`
- L400 _public member_ `EUAFTestEnum en8 = EUAFTestEnum::ValueA;` — `UPROPERTY()`
- L403 _public member_ `EUAFTestEnum en9 = EUAFTestEnum::ValueA;` — `UPROPERTY()`
- L407 _public member_ `FQuat q0 = FQuat::Identity;` — `UPROPERTY()` — Quat sources for FBindableQuat direct binding benchmark
- L410 _public member_ `FQuat q1 = FQuat::Identity;` — `UPROPERTY()`
- L413 _public member_ `FQuat q2 = FQuat::Identity;` — `UPROPERTY()`
- L416 _public member_ `FQuat q3 = FQuat::Identity;` — `UPROPERTY()`
- L419 _public member_ `FQuat q4 = FQuat::Identity;` — `UPROPERTY()`
- L422 _public member_ `FQuat q5 = FQuat::Identity;` — `UPROPERTY()`
- L425 _public member_ `FQuat q6 = FQuat::Identity;` — `UPROPERTY()`
- L428 _public member_ `FQuat q7 = FQuat::Identity;` — `UPROPERTY()`
- L431 _public member_ `FQuat q8 = FQuat::Identity;` — `UPROPERTY()`
- L434 _public member_ `FQuat q9 = FQuat::Identity;` — `UPROPERTY()`
- L438 _public member_ `FUAFNestedTestStruct ns0;` — `UPROPERTY()` — FUAFNestedTestStruct sources for FBindableVector sub-property benchmark (bind .Vec)
- L441 _public member_ `FUAFNestedTestStruct ns1;` — `UPROPERTY()`
- L444 _public member_ `FUAFNestedTestStruct ns2;` — `UPROPERTY()`
- L447 _public member_ `FUAFNestedTestStruct ns3;` — `UPROPERTY()`
- L450 _public member_ `FUAFNestedTestStruct ns4;` — `UPROPERTY()`
- L453 _public member_ `FUAFNestedTestStruct ns5;` — `UPROPERTY()`
- L456 _public member_ `FUAFNestedTestStruct ns6;` — `UPROPERTY()`
- L459 _public member_ `FUAFNestedTestStruct ns7;` — `UPROPERTY()`
- L462 _public member_ `FUAFNestedTestStruct ns8;` — `UPROPERTY()`
- L465 _public member_ `FUAFNestedTestStruct ns9;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace EUAFTestByteEnum`
