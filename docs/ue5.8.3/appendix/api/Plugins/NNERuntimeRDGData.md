# Plugins / NNERuntimeRDGData

- module root: `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGData`
- headers: 6; symbols: 91
- symbol kinds: class=2, enum=3, enumerator=17, function=21, member=26, namespace=6, struct=16
- PrivateDependencyModuleNames: Core, CoreUObject, Engine
- PublicDependencyModuleNames: NNE

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGData/Internal/NNERuntimeRDGDataAttributeDataType.h` (Internal)


#### enum `ENNERuntimeRDGDataAttributeDataType`  
`enum class ENNERuntimeRDGDataAttributeDataType : uint8`  
_L15-26_
- reflection: `UENUM()`
- desc: Attribute data types Note: also extend NNERuntimeRDGDataAttributeValueTraits.h for more type support
- L17 _public enumerator_ `None`
- L18 _public enumerator_ `Float` — 32-bit floating number
- L19 _public enumerator_ `FloatArray` — TArray of 32-bit floating numbers
- L20 _public enumerator_ `Int32` — 32-bit signed integer
- L21 _public enumerator_ `Int32Array` — TArray of 32-bit signed integers
- L22 _public enumerator_ `String` — built-in FString
- L23 _public enumerator_ `StringArray` — TArray of built-in FString
- L24 _public enumerator_ `Tensor` — FAttributeTensor
- L25 _public enumerator_ `TensorArray` — TArray of FAttributeTensor

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGData/Internal/NNERuntimeRDGDataAttributeMap.h` (Internal)


#### class `UE::NNERuntimeRDGData::Internal::FAttributeMap`  
`class FAttributeMap`  
_L10-81_
- L14 _public function_ `void SetAttribute(const FString& Name, const FNNERuntimeRDGDataAttributeValue& Value)` — Set attribute
- L24 _public function_ `template<typename T> T GetValue(const FString& Name) const`
- L33 _public function_ `template<typename T> T GetValueOrDefault(const FString& Name, T Default) const` — Query attributes
- L39 _public function_ `const FNNERuntimeRDGDataAttributeValue* GetAttributeValue(const FString& Name) const`
- L50 _public function_ `int32 Num() const` — Iteration
- L55 _public function_ `const FString& GetName(int32 Idx) const`
- L61 _public function_ `const FNNERuntimeRDGDataAttributeValue& GetAttributeValue(int32 Idx) const`
- L80 _private member_ `TArray<FEntry> Attributes;`

#### struct `UE::NNERuntimeRDGData::Internal::FAttributeMap::FEntry`  
`struct FEntry`  
_L69-78_
- L71 _public function_ `FEntry(const FString& InName, const FNNERuntimeRDGDataAttributeValue& InValue) : Name(InName), Value(InValue)`
- L76 _public member_ `FString Name;`
- L77 _public member_ `FNNERuntimeRDGDataAttributeValue Value;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeRDGData` (scope `UE`)
- L7 _namespace_ `namespace Internal` (scope `UE::NNERuntimeRDGData`)
- L17 _function_ `const bool bIsUnique = (nullptr == Attributes.FindByPredicate([Name](const FEntry& Other) { return Other.Name == Name; }));` (scope `UE::NNERuntimeRDGData::Internal::FAttributeMap::SetAttribute`)
- L41 _function_ `const FEntry * entry = Attributes.FindByPredicate([Name](const FEntry& Other) { return Other.Name == Name; });` (scope `UE::NNERuntimeRDGData::Internal::FAttributeMap::GetAttributeValue`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGData/Internal/NNERuntimeRDGDataAttributeTensor.h` (Internal)


#### class `UE::NNERuntimeRDGData::Internal::FAttributeTensor`  
`class FAttributeTensor`  
_L11-59_
- L14 _protected member_ `ENNETensorDataType DataType;`
- L15 _protected member_ `TArray<uint32, TInlineAllocator<NNE::FTensorShape::MaxRank>> Shape;`
- L16 _protected member_ `TArray<uint8> Data;`
- L20 _public function_ `ENNETensorDataType GetDataType() const`
- L25 _public function_ `TConstArrayView<uint8> GetData() const`
- L30 _public function_ `NNE::FTensorShape GetShape() const`
- L35 _public function_ `static FAttributeTensor Make(const NNE::FTensorShape& Shape, ENNETensorDataType DataType, TConstArrayView<uint8> Data)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNERuntimeRDGData` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNERuntimeRDGData`)
- L52 _function_ `friend FArchive& operator<<(FArchive& Ar, FAttributeTensor& Tensor)` (scope `UE::NNERuntimeRDGData::Internal`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGData/Internal/NNERuntimeRDGDataAttributeValue.h` (Internal)


#### struct `FNNERuntimeRDGDataAttributeValue`  
`struct FNNERuntimeRDGDataAttributeValue`  
_L13-56_
- reflection: `USTRUCT()`
- L17 _public function_ `FNNERuntimeRDGDataAttributeValue()`
- L23 _public function_ `template<typename T> explicit FNNERuntimeRDGDataAttributeValue(T InValue)`
- L32 _public function_ `template<typename T> T GetValue() const`
- L44 _public function_ `ENNERuntimeRDGDataAttributeDataType GetType() const`
- L52 _private member_ `ENNERuntimeRDGDataAttributeDataType Type;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`
- L55 _private member_ `TArray<uint8> Value;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGData/Internal/NNERuntimeRDGDataAttributeValueTraits.h` (Internal)


#### struct `TNNERuntimeRDGDataAttributeValueTraits`  
`template<typename T> struct TNNERuntimeRDGDataAttributeValueTraits`  
_L8-15_
- L10 _public function_ `static constexpr ENNERuntimeRDGDataAttributeDataType GetType()`

#### struct `TNNERuntimeRDGDataAttributeValueTraits`  
`template<> struct TNNERuntimeRDGDataAttributeValueTraits<float>`  
_L18-21_
- desc: Attribute specializations
- L10 _public function_ `static constexpr ENNERuntimeRDGDataAttributeDataType GetType()`

#### struct `TNNERuntimeRDGDataAttributeValueTraits`  
`template<> struct TNNERuntimeRDGDataAttributeValueTraits<int32>`  
_L23-26_
- L10 _public function_ `static constexpr ENNERuntimeRDGDataAttributeDataType GetType()`

#### struct `TNNERuntimeRDGDataAttributeValueTraits`  
`template<> struct TNNERuntimeRDGDataAttributeValueTraits<FString>`  
_L28-31_
- L10 _public function_ `static constexpr ENNERuntimeRDGDataAttributeDataType GetType()`

#### struct `TNNERuntimeRDGDataAttributeValueTraits`  
`template<> struct TNNERuntimeRDGDataAttributeValueTraits<UE::NNERuntimeRDGData::Internal::FAttributeTensor>`  
_L33-36_
- L10 _public function_ `static constexpr ENNERuntimeRDGDataAttributeDataType GetType()`

#### struct `TNNERuntimeRDGDataAttributeValueTraits`  
`template<> struct TNNERuntimeRDGDataAttributeValueTraits<TArray<int32>>`  
_L38-41_
- L10 _public function_ `static constexpr ENNERuntimeRDGDataAttributeDataType GetType()`

#### struct `TNNERuntimeRDGDataAttributeValueTraits`  
`template<> struct TNNERuntimeRDGDataAttributeValueTraits<TArray<float>>`  
_L43-46_
- L10 _public function_ `static constexpr ENNERuntimeRDGDataAttributeDataType GetType()`

#### struct `TNNERuntimeRDGDataAttributeValueTraits`  
`template<> struct TNNERuntimeRDGDataAttributeValueTraits<TArray<FString>>`  
_L48-51_
- L10 _public function_ `static constexpr ENNERuntimeRDGDataAttributeDataType GetType()`

#### struct `TNNERuntimeRDGDataAttributeValueTraits`  
`template<> struct TNNERuntimeRDGDataAttributeValueTraits<TArray<UE::NNERuntimeRDGData::Internal::FAttributeTensor>>`  
_L53-56_
- L10 _public function_ `static constexpr ENNERuntimeRDGDataAttributeDataType GetType()`

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGData/Internal/NNERuntimeRDGDataFormat.h` (Internal)


#### enum `ENNERuntimeRDGDataTensorType`  
`enum class ENNERuntimeRDGDataTensorType : uint8`  
_L12-22_
- reflection: `UENUM()`
- L14 _public enumerator_ `None`
- L15 _public enumerator_ `Input`
- L16 _public enumerator_ `Output`
- L17 _public enumerator_ `Intermediate`
- L18 _public enumerator_ `Initializer`
- L19 _public enumerator_ `Empty`
- L21 _public enumerator_ `NUM`

#### struct `FNNERuntimeRDGDataAttributeDesc`  
`struct FNNERuntimeRDGDataAttributeDesc`  
_L25-34_
- reflection: `USTRUCT()`
- L30 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`
- L33 _public member_ `FNNERuntimeRDGDataAttributeValue Value;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`

#### struct `FNNERuntimeRDGDataOperatorDesc`  
`struct FNNERuntimeRDGDataOperatorDesc`  
_L37-58_
- reflection: `USTRUCT()`
- L42 _public member_ `FString TypeName;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")` — For example "Relu"
- L45 _public member_ `FString DomainName;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")` — For example "onnx"
- L48 _public member_ `TOptional<uint32> Version;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")` — For example 7
- L51 _public member_ `TArray<uint32> InTensors;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`
- L54 _public member_ `TArray<uint32> OutTensors;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`
- L57 _public member_ `TArray<FNNERuntimeRDGDataAttributeDesc> Attributes;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`

#### struct `FNNERuntimeRDGDataTensorDesc`  
`struct FNNERuntimeRDGDataTensorDesc`  
_L61-82_
- reflection: `USTRUCT()`
- L66 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`
- L69 _public member_ `TArray<int32> Shape;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`
- L72 _public member_ `ENNERuntimeRDGDataTensorType Type = ENNERuntimeRDGDataTensorType::None;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`
- L75 _public member_ `ENNETensorDataType DataType = ENNETensorDataType::None;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`
- L78 _public member_ `uint64 DataSize = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`
- L81 _public member_ `uint64 DataOffset = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`

#### struct `FNNERuntimeRDGDataModelFormat`  
`struct FNNERuntimeRDGDataModelFormat`  
_L85-120_
- reflection: `USTRUCT()`
- L90 _public member_ `TArray<FNNERuntimeRDGDataTensorDesc> Tensors;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`
- L93 _public member_ `TArray<FNNERuntimeRDGDataOperatorDesc> Operators;` — `UPROPERTY(VisibleAnywhere, Category = "Neural Network Inference")`
- L95 _public member_ `uint64 DataSize;`
- L96 _public member_ `TArray64<uint8> TensorData;`
- L98 _public function_ `bool Serialize(FArchive& Ar)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FNNERuntimeRDGDataModelFormat> : public TStructOpsTypeTraitsBase2<FNNERuntimeRDGDataModelFormat>`  
_L123-129_
- inherits: `TStructOpsTypeTraitsBase2<FNNERuntimeRDGDataModelFormat>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L126-128_

#### Free symbols / members of external scopes

- L127 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon537ccae70103`)
