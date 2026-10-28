# Plugins / MetaHumanAnimationSerialization

- module root: `Plugins/MetaHuman/MetaHumanAnimationTools/Source/MetaHumanAnimationSerialization`
- headers: 1; symbols: 26
- symbol kinds: class=1, enum=2, enumerator=7, macro=1, member=7, prototype=8
- PrivateDependencyModuleNames: Core, Engine
- PublicDependencyModuleNames: 

### `Plugins/MetaHuman/MetaHumanAnimationTools/Source/MetaHumanAnimationSerialization/Public/MetaHumanAnimationSerialization.h` (Public)


#### class `FMetaHumanAnimationSerialization`  
`class FMetaHumanAnimationSerialization`  
_L13-57_
- L33 _public prototype_ `bool SetupEncoder(FArchive& InOutArchive, EMaxPrecisionType InMaxPrecisionType, ECompressionMethod InCompressionMethod);`
- L34 _public prototype_ `bool Encode(FArchive& InOutArchive, float InTime, const TArray<float>& InCurves);`
- L36 _public prototype_ `bool SetupDecoder(FArchive& InOutArchive);`
- L37 _public prototype_ `bool Decode(FArchive& InOutArchive, float& OutTime, TArray<float>& OutCurves);`
- L39 _public prototype_ `EMaxPrecisionType GetMaxPrecisionType() const;`
- L40 _public prototype_ `ECompressionMethod GetCompressionMethod() const;`
- L44 _private member_ `EMaxPrecisionType MaxPrecisionType = EMaxPrecisionType::Undefined;`
- L45 _private member_ `ECompressionMethod CompressionMethod = ECompressionMethod::Undefined;`
- L47 _private member_ `TArray<float> PreviousCurves;`
- L49 _private member_ `float SparsePrecision = 0.001f;`
- L50 _private member_ `float SparseFullDataInterval = 1;`
- L51 _private member_ `float SparseLastFullDataTime = -1;`
- L53 _private prototype_ `bool EncodeMaxPrecisionValues(FArchive& InOutArchive, const TArray<float>& InValues);`
- L54 _private prototype_ `bool DecodeMaxPrecisionValues(FArchive& InOutArchive, TArray<float>& OutValues);`
- L56 _private member_ `static const FString MagicNumber;`

#### enum `FMetaHumanAnimationSerialization::EMaxPrecisionType`  
`enum class EMaxPrecisionType : uint8`  
_L18-24_
- L20 _public enumerator_ `Undefined = 0`
- L21 _public enumerator_ `Float`
- L22 _public enumerator_ `Int16`
- L23 _public enumerator_ `Int10`

#### enum `FMetaHumanAnimationSerialization::ECompressionMethod`  
`enum class ECompressionMethod : uint8`  
_L26-31_
- L28 _public enumerator_ `Undefined = 0`
- L29 _public enumerator_ `None`
- L30 _public enumerator_ `Sparse`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANANIMATIONSERIALIZATION_API`
