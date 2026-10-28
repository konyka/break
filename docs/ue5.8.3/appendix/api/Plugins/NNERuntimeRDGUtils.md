# Plugins / NNERuntimeRDGUtils

- module root: `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGUtils`
- headers: 8; symbols: 83
- symbol kinds: class=8, enum=1, enumerator=3, function=4, member=4, namespace=24, prototype=35, struct=1, typedef=2, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, NNEHlslShaders, NNERuntimeRDGData, NNERuntimeRDGOnnxEditor, NNERuntimeRDGOnnxruntimeEditor, NNERuntimeRDGProtobufEditor, Projects
- PublicDependencyModuleNames: NNE

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGUtils/Internal/NNERuntimeRDGUtilsModelOptimizer.h` (Internal)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeRDGUtils` (scope `UE`)
- L7 _namespace_ `namespace Internal` (scope `UE::NNERuntimeRDGUtils`)
- L10 _prototype_ `TUniquePtr<IModelOptimizer> CreateModelOptimizer();` (scope `UE::NNERuntimeRDGUtils::Internal`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGUtils/Internal/NNERuntimeRDGUtilsModelOptimizerInterface.h` (Internal)


#### class `UE::NNERuntimeRDGUtils::Internal::IModelValidator`  
`class IModelValidator`  
_L13-19_
- desc: Interface class for NNE model validator
- L16 _public prototype_ `virtual ~IModelValidator() = default;`
- L17 _public prototype_ `virtual FString GetName() const = 0;`
- L18 _public prototype_ `virtual bool ValidateModel(TConstArrayView<uint8> InputModel) const = 0;`

#### class `UE::NNERuntimeRDGUtils::Internal::IModelOptimizerPass`  
`class IModelOptimizerPass`  
_L22-30_
- desc: Interface class for NNE model optimizer pass
- L25 _public prototype_ `virtual ~IModelOptimizerPass() = default;`
- L26 _public prototype_ `virtual FString GetName() const = 0;`
- L29 _public prototype_ `virtual bool ApplyPass(TArray<uint8>& Model) const = 0;` — Optimize the model in place, potentially changing the format

#### class `UE::NNERuntimeRDGUtils::Internal::IModelOptimizer`  
`class IModelOptimizer`  
_L33-47_
- desc: Interface class for NNE model optimizer
- L36 _public prototype_ `virtual ~IModelOptimizer() = default;`
- L37 _public prototype_ `virtual FString GetName() const = 0;`
- L40 _public prototype_ `virtual void AddOptimizationPass(TSharedPtr<IModelOptimizerPass> ModelOptimizerPass) = 0;` — Allow to extend/customize an optimizer by adding passes. They should be executed in order.
- L43 _public prototype_ `virtual void AddValidator(TSharedPtr<IModelValidator>) = 0;` — Allow to extend/customize an optimizer all validators should be run between each pass.
- L46 _public prototype_ `virtual bool Optimize(TConstArrayView<uint8> InputModel, TArray<uint8>& OutModel) = 0;` — Apply all passes and validators to the input model, produce an optimized model potentially in a different format

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNERuntimeRDGUtils` (scope `UE`)
- L9 _namespace_ `namespace Internal` (scope `UE::NNERuntimeRDGUtils`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGUtils/Private/NNERuntimeRDGUtilsHelpers.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace NNERuntimeRDGUtils` (scope `UE`)
- L6 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDGUtils`)
- L9 _prototype_ `TOptional<uint32> GetOpVersionFromOpsetVersion(const FString& OpType, int OpsetVersion);` (scope `UE::NNERuntimeRDGUtils::Private`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGUtils/Private/NNERuntimeRDGUtilsModelBuilder.h` (Private)


#### class `UE::NNERuntimeRDGUtils::Private::IModelBuilder`  
`class IModelBuilder`  
_L15-62_
- L33 _public typedef_ `typedef struct THandle<EHandleType::Tensor> FHTensor;`
- L34 _public typedef_ `typedef struct THandle<EHandleType::Operator> FHOperator;`
- L37 _public function_ `template<EHandleType Tag> THandle<Tag> MakeHandle(void* Ptr)`
- L45 _public prototype_ `virtual ~IModelBuilder() = default;`
- L48 _public prototype_ `virtual bool Begin(const FString& GraphName = TEXT("DefaultG` — Initialize the model builder
- L51 _public prototype_ `virtual bool End(TArray<uint8>& Data) = 0;` — Serialize the model to given array
- L53 _public prototype_ `virtual FHTensor AddTensor(const FString& Name, ENNETensorDataType DataType, TArrayView<const int32> Shape) = 0;`
- L54 _public prototype_ `virtual FHTensor AddConstantTensor(const FString& Name, ENNETensorDataType DataType, TArrayView<const int32> Shape, const void* Data, uint64 DataSize) = 0;`
- L55 _public prototype_ `virtual FHTensor AddEmptyTensor() = 0;`
- L56 _public prototype_ `virtual bool AddInput(FHTensor InTensor) = 0;`
- L57 _public prototype_ `virtual bool AddOutput(FHTensor OutTensor) = 0;`
- L58 _public prototype_ `virtual FHOperator AddOperator(const FString& Type, const FString& Domain, TOptional<uint32> Version = FNullOpt{0}, const FString& Name = TEXT("")) = 0;`
- L59 _public prototype_ `virtual bool AddOperatorInput(FHOperator Op, FHTensor Tensor) = 0;`
- L60 _public prototype_ `virtual bool AddOperatorAttribute(FHOperator Op, const FString& Name, const FNNERuntimeRDGDataAttributeValue& Value) = 0;`
- L61 _public prototype_ `virtual bool AddOperatorOutput(FHOperator Op, FHTensor Tensor) = 0;`

#### enum `UE::NNERuntimeRDGUtils::Private::IModelBuilder::EHandleType`  
`enum class EHandleType : uint8`  
_L19-24_
- L21 _public enumerator_ `Invalid`
- L22 _public enumerator_ `Tensor`
- L23 _public enumerator_ `Operator`

#### struct `UE::NNERuntimeRDGUtils::Private::IModelBuilder::THandle`  
`template<EHandleType Tag> struct THandle`  
_L27-31_
- L29 _public member_ `void* Ptr { nullptr };`
- L30 _public member_ `EHandleType Type { Tag };`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace NNERuntimeRDGUtils` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDGUtils`)
- L64 _variable_ `static constexpr TCHAR OnnxDomainName[] = TEXT("Onn` (scope `UE::NNERuntimeRDGUtils::Private`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGUtils/Private/NNERuntimeRDGUtilsModelBuilderNNE.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDGUtils` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDGUtils`)
- L11 _prototype_ `TUniquePtr<IModelBuilder> CreateNNEModelBuilder();` (scope `UE::NNERuntimeRDGUtils::Private`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGUtils/Private/NNERuntimeRDGUtilsModelOptimizerBase.h` (Private)


#### class `UE::NNERuntimeRDGUtils::Private::FModelValidatorONNX`  
`class FModelValidatorONNX : public Internal::IModelValidator`  
_L10-15_
- inherits: `Internal::IModelValidator`
- L13 _public prototype_ `virtual FString GetName() const override;`
- L14 _public prototype_ `virtual bool ValidateModel(TConstArrayView<uint8> InputModel) const override;`

#### class `UE::NNERuntimeRDGUtils::Private::FModelOptimizerBase`  
`class FModelOptimizerBase : public Internal::IModelOptimizer`  
_L17-31_
- inherits: `Internal::IModelOptimizer`
- L20 _protected function_ `FModelOptimizerBase()`
- L21 _protected member_ `TArray<TSharedPtr<Internal::IModelOptimizerPass>> OptimizationPasses;`
- L22 _protected member_ `TArray<TSharedPtr<Internal::IModelValidator>> Validators;`
- L24 _protected prototype_ `bool IsModelValid(TConstArrayView<uint8> ModelToValidate);`
- L25 _protected prototype_ `bool ApplyAllPassesAndValidations(TArray<uint8>& OptimizedModel);`
- L28 _public prototype_ `virtual void AddOptimizationPass(TSharedPtr<Internal::IModelOptimizerPass> ModelOptimizerPass) override;`
- L29 _public prototype_ `virtual void AddValidator(TSharedPtr<Internal::IModelValidator> ModelValidator) override;`
- L30 _public prototype_ `virtual bool Optimize(TConstArrayView<uint8> InputModel, TArray<uint8>& OutModel) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDGUtils` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDGUtils`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGUtils/Private/NNERuntimeRDGUtilsModelOptimizerNNE.h` (Private)


#### class `UE::NNERuntimeRDGUtils::Private::FModelOptimizerONNXToNNERT`  
`class FModelOptimizerONNXToNNERT : public FModelOptimizerBase`  
_L10-19_
- inherits: `FModelOptimizerBase`
- L13 _public function_ `virtual FString GetName() const override`
- L18 _public prototype_ `virtual bool Optimize(TConstArrayView<uint8> InputModel, TArray<uint8>& OutModel) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeRDGUtils` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDGUtils`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDGUtils/Private/NNERuntimeRDGUtilsModelOptimizerONNX.h` (Private)


#### class `UE::NNERuntimeRDGUtils::Private::FModelOptimizerONNXToONNX`  
`class FModelOptimizerONNXToONNX : public FModelOptimizerBase`  
_L10-19_
- inherits: `FModelOptimizerBase`
- L13 _public prototype_ `FModelOptimizerONNXToONNX();`
- L15 _public function_ `virtual FString GetName() const override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeRDGUtils` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDGUtils`)
