# Plugins / NNERuntimeRDG

- module root: `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG`
- headers: 56; symbols: 488
- symbol kinds: class=14, function=48, macro=1, member=53, namespace=244, prototype=104, struct=8, typedef=13, variable=3
- PrivateDependencyModuleNames: MetalRHI, NNE, NNEHlslShaders, NNERuntimeRDGData, NNERuntimeRDGUtils, Projects, RHI, TraceLog, VulkanRHI
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, RenderCore

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Helper/NNERuntimeRDGHelperCast.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L9 _namespace_ `namespace CPUHelper` (scope `UE::NNERuntimeRDG::Private`)
- L9 _namespace_ `namespace Cast` (scope `UE::NNERuntimeRDG::Private::CPUHelper`)
- L11 _prototype_ `void Apply(const FTensor& Tensor, FTensor& OutputTensor);` (scope `UE::NNERuntimeRDG::Private::CPUHelper::Cast`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Helper/NNERuntimeRDGHelperConcat.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace CPUHelper` (scope `UE::NNERuntimeRDG::Private`)
- L8 _namespace_ `namespace Concat` (scope `UE::NNERuntimeRDG::Private::CPUHelper`)
- L10 _prototype_ `void Apply(TConstArrayView<FTensorRef> InputTensors, FTensor& OutputTensor, int32 Axis);` (scope `UE::NNERuntimeRDG::Private::CPUHelper::Concat`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Helper/NNERuntimeRDGHelperElementWiseBinary.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L10 _namespace_ `namespace CPUHelper` (scope `UE::NNERuntimeRDG::Private`)
- L10 _namespace_ `namespace ElementWiseBinary` (scope `UE::NNERuntimeRDG::Private::CPUHelper`)
- L12 _prototype_ `void Apply(UE::NNEHlslShaders::Internal::EElementWiseBinaryOperatorType OpType, const FTensor& LHSTensor, const FTensor& RHSTensor, FTensor& OutputTensor);` (scope `UE::NNERuntimeRDG::Private::CPUHelper::ElementWiseBinary`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Helper/NNERuntimeRDGHelperElementWiseUnary.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L10 _namespace_ `namespace CPUHelper` (scope `UE::NNERuntimeRDG::Private`)
- L10 _namespace_ `namespace ElementWiseUnary` (scope `UE::NNERuntimeRDG::Private::CPUHelper`)
- L12 _prototype_ `void Apply(UE::NNEHlslShaders::Internal::EElementWiseUnaryOperatorType OpType, const FTensor& Tensor, float Alpha, float Beta, float Gamma, FTensor& OutputTensor);` (scope `UE::NNERuntimeRDG::Private::CPUHelper::ElementWiseUnary`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Helper/NNERuntimeRDGHelperGather.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L9 _namespace_ `namespace CPUHelper` (scope `UE::NNERuntimeRDG::Private`)
- L9 _namespace_ `namespace Gather` (scope `UE::NNERuntimeRDG::Private::CPUHelper`)
- L11 _prototype_ `void Apply(const FTensor& DataTensor, const FTensor& IndicesTensor, int32 Axis, FTensor& OutputTensor);` (scope `UE::NNERuntimeRDG::Private::CPUHelper::Gather`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Helper/NNERuntimeRDGHelperReshape.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L13 _namespace_ `namespace ShapeHelper` (scope `UE::NNERuntimeRDG::Private`)
- L13 _namespace_ `namespace Reshape` (scope `UE::NNERuntimeRDG::Private::ShapeHelper`)
- L16 _function_ `template<typename DataType, class OutputShapeType > bool ReshapeTensor( const NNE::FTensorShape& InputTensorShape, const FTensor& ShapeTensor, bool bAllowZero, OutputShapeType& OutShape)` (scope `UE::NNERuntimeRDG::Private::ShapeHelper::Reshape`)
- L58 _function_ `` (scope `UE::NNERuntimeRDG::Private::ShapeHelper::Reshape::ReshapeTensor`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Helper/NNERuntimeRDGHelperSlice.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L9 _namespace_ `namespace CPUHelper` (scope `UE::NNERuntimeRDG::Private`)
- L9 _namespace_ `namespace Slice` (scope `UE::NNERuntimeRDG::Private::CPUHelper`)
- L11 _prototype_ `void Apply(const FTensor& InputTensor, FTensor& OutputTensor, TConstArrayView<int32> Starts, TConstArrayView<int32> Steps);` (scope `UE::NNERuntimeRDG::Private::CPUHelper::Slice`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Helper/NNERuntimeRDGHelperTranspose.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L9 _namespace_ `namespace CPUHelper` (scope `UE::NNERuntimeRDG::Private`)
- L9 _namespace_ `namespace Transpose` (scope `UE::NNERuntimeRDG::Private::CPUHelper`)
- L11 _prototype_ `bool Apply(const FTensor& DataTensor, TConstArrayView<int32> Perms, FTensor& OutputTensor);` (scope `UE::NNERuntimeRDG::Private::CPUHelper::Transpose`)
- L12 _prototype_ `bool TransposePreparedData(FTensor& Tensor, TConstArrayView<int32> Perms);` (scope `UE::NNERuntimeRDG::Private::CPUHelper::Transpose`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Helper/NNERuntimeRDGLogHelper.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace LogHelper` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `FString GetTensorDataTypeName(ENNETensorDataType DataType);` (scope `UE::NNERuntimeRDG::Private::LogHelper`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Helper/NNERuntimeRDGOperatorHelper.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L9 _namespace_ `namespace OperatorHelper` (scope `UE::NNERuntimeRDG::Private`)
- L11 _prototype_ `bool GetInt32ArrayFromConstTensor(TArray<int32, TInlineAllocator<NNE::FTensorShape::MaxRank>>& Attr, const FTensorRef Tensor);` (scope `UE::NNERuntimeRDG::Private::OperatorHelper`)
- L12 _prototype_ `bool GetInt32ArrayFromConstTensor(TArray<int32, TInlineAllocator<2 * NNE::FTensorShape::MaxRank>>& Attr, const FTensorRef Tensor);` (scope `UE::NNERuntimeRDG::Private::OperatorHelper`)
- L13 _prototype_ `bool GetInt32ArrayFromConstTensor(TArray<int32>& Attr, const FTensorRef Tensor);` (scope `UE::NNERuntimeRDG::Private::OperatorHelper`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Helper/NNERuntimeRDGTensorIdxIterator.h` (Private)


#### class `UE::NNERuntimeRDG::Private::TensorIdxIterator`  
`class TensorIdxIterator`  
_L10-22_
- L12 _private member_ `const NNE::FTensorShape& TensorShape;`
- L13 _private member_ `TArray<uint32, TInlineAllocator<NNE::FTensorShape::MaxRank>> CurrentPosition;`
- L16 _public prototype_ `TensorIdxIterator(const NNE::FTensorShape& InTensorShape);`
- L17 _public prototype_ `bool Advance();`
- L18 _public prototype_ `int32 GetIndexToBroadcastedShape(const NNE::FTensorShape& InTensorShape) const;`
- L19 _public prototype_ `int32 GetIndex() const;`
- L20 _public prototype_ `TConstArrayView<uint32> GetPositions() const;`
- L21 _public prototype_ `int32 GetIndexFromPosition(TConstArrayView<uint32> Position) const;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGBatchNormalization.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterBatchNormalizationOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGCast.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterCastOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGConcat.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterConcatOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGConstant.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterConstantOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGConv.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterConvOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGConvTranspose.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterConvTransposeOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGCumSum.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L7 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L9 _prototype_ `bool RegisterCumSumOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGDepthToSpace.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterDepthToSpaceOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGDropout.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterDropoutOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGElementWiseBinary.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterElementWiseBinaryOperators(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGElementWiseUnary.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterElementWiseUnaryOperators(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGElementWiseVariadic.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterElementWiseVariadicOperators(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGFlatten.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterFlattenOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGGather.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterGatherOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGGatherElements.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterGatherElementsOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGGemm.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterGemmOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGGlobalPool.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L7 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L9 _prototype_ `bool RegisterGlobalPoolOperators(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGIdentity.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterIdentityOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGInstanceNormalization.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterInstanceNormalizationOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGLayerNormalization.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterLayerNormalizationOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGMatMul.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterMatMulOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGPad.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterPadOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGPool.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterPoolOperators(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGReduce.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L7 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L9 _prototype_ `bool RegisterReduceOperators(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGReshape.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterReshapeOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGResize.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterResizeOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGScatterND.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterScatterNDOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGShape.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterShapeOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGSize.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterSizeOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGSlice.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterSliceOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGSoftmax.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L7 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L9 _prototype_ `bool RegisterSoftmaxOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGSplit.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterSplitOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGSqueeze.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterSqueezeOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGTranspose.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterTransposeOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGUnsqueeze.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterUnsqueezeOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/Hlsl/NNERuntimeRDGUpsample.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L8 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L10 _prototype_ `bool RegisterUpsampleOperator(FOperatorRegistryHlsl& Registry);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/NNERuntimeRDGAttributes.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L10 _namespace_ `namespace AttrName` (scope `UE::NNERuntimeRDG::Private`)
- L12 _variable_ `static constexpr auto* Mode = TEXT("mod` (scope `UE::NNERuntimeRDG::Private::AttrName`)
- L15 _namespace_ `namespace AttrValue` (scope `UE::NNERuntimeRDG::Private`)
- L17 _variable_ `static constexpr auto* Nearest = TEXT("nea` (scope `UE::NNERuntimeRDG::Private::AttrValue`)
- L18 _variable_ `static constexpr auto* Linear = TEXT("lin` (scope `UE::NNERuntimeRDG::Private::AttrValue`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/NNERuntimeRDGBase.h` (Private)


#### struct `UE::NNERuntimeRDG::Private::IPrepareOperator`  
`struct IPrepareOperator`  
_L36-40_
- desc: Interface for all operators to prepare the model tensors at scheduling time
- L38 _public prototype_ `virtual ~IPrepareOperator() = default;`
- L39 _public prototype_ `virtual int PrepareOutputs(TConstArrayView<FTensorRef> InputTensors, TArrayView<FTensorRef> OutputTensors) = 0;`

#### struct `UE::NNERuntimeRDG::Private::IOperatorRDG`  
`struct IOperatorRDG`  
_L45-48_
- desc: Interface for all ML operators running on the RDG
- L47 _public prototype_ `virtual ~IOperatorRDG() = default;`

#### class `UE::NNERuntimeRDG::Private::FTensorRDG`  
`class FTensorRDG : public FTensor`  
_L50-74_
- inherits: `FTensor`
- L52 _private member_ `FRDGBufferRef Buffer{};`
- L55 _public function_ `static FTensorRDG Make(const NNE::FTensorDesc& TensorDesc, const NNE::FTensorShape& Shape, FRDGBufferRef Buffer)`
- L70 _public function_ `bool IsValid() const`
- L71 _public function_ `bool HasBuffer() const`
- L72 _public function_ `void SetBuffer(FRDGBufferRef Inbuffer)`
- L73 _public function_ `FRDGBufferRef GetBuffer() const`

#### class `UE::NNERuntimeRDG::Private::FInputValidator`  
`class FInputValidator`  
_L83-98_
- L86 _public prototype_ `FInputValidator();`
- L87 _public prototype_ `void AddRequired(int32 TemplateIdx = 0);`
- L88 _public prototype_ `void AddOptional(int32 TemplateIdx = 0);`
- L89 _public prototype_ `void SetTemplateCount(int32 TemplateCount);`
- L90 _public prototype_ `void AddSupportedType(ENNETensorDataType Type, int32 TemplateIdx = 0);`
- L91 _public prototype_ `bool Validate(TConstArrayView<ENNETensorDataType> InputTypes);`
- L94 _private member_ `TArray<TSet<ENNETensorDataType>, TInlineAllocator<16>> TemplateTypes;`
- L95 _private member_ `FIntArray InputTemplateIndices;`
- L96 _private member_ `int32 NumRequiredInput;`
- L97 _private member_ `int32 NumOptionalInput;`

#### class `UE::NNERuntimeRDG::Private::FAttributeValidator`  
`class FAttributeValidator`  
_L100-125_
- L103 _public prototype_ `void AddOptional(const FString& Name, ENNERuntimeRDGDataAttributeDataType Type);`
- L104 _public prototype_ `void AddRequired(const FString& Name, ENNERuntimeRDGDataAttributeDataType Type);`
- L105 _public prototype_ `bool Validate(const NNERuntimeRDGData::Internal::FAttributeMap& AttributesToValidate);`
- L123 _private member_ `TArray<FEntry> RequiredAttributes;`
- L124 _private member_ `TArray<FEntry> OptionalAttributes;`

#### struct `UE::NNERuntimeRDG::Private::FAttributeValidator::FEntry`  
`struct FEntry`  
_L108-121_
- L110 _public function_ `FEntry(const FString& InName, ENNERuntimeRDGDataAttributeDataType InType) : Name(InName), Type(InType)`
- L119 _public member_ `FString Name;` — Idea: we could extended as needed by operator to support more validation especially around the range of the values. An example is ConvTranspose `auto_pad` enum style string that can only take a few values In the same direction we might only support a range of value for a float (for example we only support integer but the type is float, or only positive values for an int32)
- L120 _public member_ `ENNERuntimeRDGDataAttributeDataType Type;`

#### struct `UE::NNERuntimeRDG::Private::FOperatorDescUnversioned`  
`struct FOperatorDescUnversioned`  
_L129-138_
- L131 _public member_ `FString OpName;`
- L132 _public member_ `FString DomainName;`
- L134 _public function_ `bool operator==(FOperatorDescUnversioned const& Other) const`

#### struct `UE::NNERuntimeRDG::Private::FOperatorDesc`  
`struct FOperatorDesc : public FOperatorDescUnversioned`  
_L146-156_
- inherits: `FOperatorDescUnversioned`
- L148 _public member_ `TOptional<TOperatorVersionType> Version;` — Unset means no versioning for the operator
- L151 _public function_ `FString GetFullName() const` — Return the full name	in the format <DomainName>:<OpName>(:<Version>)

#### class `UE::NNERuntimeRDG::Private::TOperatorRegistryRDG`  
`template<class TOperatorType> class TOperatorRegistryRDG`  
_L174-343_
- desc: Registry for RDG ML operators Operators can be registered either as versioned or unversioned (FOperatorDesc::Version unset). The same operator (op and domain name pair) can be registered for different versions, but there can only be one unversioned registration (and no versioned registration in such case). When finding a registration via OpFind() and OpFindValidation() - in case there's an unversioned registration of an operator: any input OpDesc with the same (OpName, DomainName) pair will match the registration, - in case there are versioned registrations of an operator: the registration with same (OpName, DomainName) pair and highest version (but <= than input OpDesc.Version) will match the input OpDesc.
- L178 _public typedef_ `typedef TOperatorType* (*OperatorCreateFunc)();`
- L179 _public typedef_ `typedef bool (*OperatorValidateFunc)(const NNERuntimeRDGData::Internal::FAttributeMap& AttributeMap, TConstArrayView<ENNETensorDataType> InputTypes, TConstArrayView<NNE::FSymbolicTensorShape> InputShapes);`
- L181 _public function_ `static TOperatorRegistryRDG* Get()`
- L188 _public function_ `OperatorValidateFunc OpFindValidation(const FOperatorDesc& OpDesc)`
- L200 _public function_ `OperatorCreateFunc OpFind(const FOperatorDesc& OpDesc)`
- L212 _public function_ `bool OpAdd(const FOperatorDesc& OpDesc, OperatorCreateFunc CreateFunc, OperatorValidateFunc ValidateFunc = AlwaysValidValidationFunction)`
- L240 _public function_ `FString ListAllRegisteredOperators() const`
- L320 _private function_ `const FOperatorFunctions* OpFindFunctions(const FOperatorDesc& OpDesc) const`
- L340 _private typedef_ `typedef TMap<TOptional<TOperatorVersionType>, FOperatorFunctions> TOperatorVersionToFunctionsMap;`
- L342 _private member_ `TMap<FOperatorDescUnversioned, TOperatorVersionToFunctionsMap> Operators;`

#### class `UE::NNERuntimeRDG::Private::TOperatorRegistryRDG::ListAllRegisteredOperators::FLoggableOperatorDesc`  
`class FLoggableOperatorDesc`  
_L242-285_
- L244 _private member_ `FString OpDomainAndName;`
- L245 _private member_ `FString SupportedOpsets;`
- L249 _public function_ `FLoggableOperatorDesc(const FOperatorDescUnversioned& InOpDesc, TArrayView<TOptional<TOperatorVersionType>> InOpVersions)`
- L277 _public function_ `const FString& GetDomainAndName() const`
- L281 _public function_ `const FString& GetSupportedOpset() const`

#### struct `UE::NNERuntimeRDG::Private::TOperatorRegistryRDG::FOperatorFunctions`  
`struct FOperatorFunctions`  
_L314-318_
- L316 _public member_ `OperatorCreateFunc CreateFunc;`
- L317 _public member_ `OperatorValidateFunc ValidateFunc;`

#### class `UE::NNERuntimeRDG::Private::TModelValidatorRDG`  
`template<class TOperatorType> class TModelValidatorRDG : public NNERuntimeRDGUtils::Internal::IModelValidator`  
_L350-404_
- inherits: `NNERuntimeRDGUtils::Internal::IModelValidator`
- desc: Validator for RDG ML operators
- L353 _public function_ `virtual FString GetName() const`
- L358 _public function_ `virtual bool ValidateModel(TConstArrayView<uint8> InputModel) const override`

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace NNE` (scope `UE`)
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L30 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L76 _typedef_ `using FTensorRDGRef = FTensorRDG*;` (scope `UE::NNERuntimeRDG::Private`)
- L77 _typedef_ `using FTensorRDGArray = TArray<FTensorRDG, TInlineAllocator<16>>;` (scope `UE::NNERuntimeRDG::Private`)
- L78 _typedef_ `using FTensorRDGRefMap = TMap<int32, FTensorRDGRef>;` (scope `UE::NNERuntimeRDG::Private`)
- L79 _typedef_ `using FIntArray = TArray<int32, TInlineAllocator<16>>;` (scope `UE::NNERuntimeRDG::Private`)
- L81 _prototype_ `bool AlwaysValidValidationFunction(const NNERuntimeRDGData::Internal::FAttributeMap& AttributeMap, TConstArrayView<ENNETensorDataType> InputTypes, TConstArrayView<NNE::FSymbolicTensorShape> InputShapes);` (scope `UE::NNERuntimeRDG::Private`)
- L127 _typedef_ `typedef uint32 TOperatorVersionType;` (scope `UE::NNERuntimeRDG::Private`)
- L140 _function_ `FORCEINLINE uint32 GetTypeHash(const FOperatorDescUnversioned& OpDescUnversioned)` (scope `UE::NNERuntimeRDG::Private`)
- L256 _function_ `` (scope `UE::NNERuntimeRDG::Private::TOperatorRegistryRDG::ListAllRegisteredOperators::FLoggableOperatorDesc::FLoggableOperatorDesc`)
- L297 _function_ `` (scope `UE::NNERuntimeRDG::Private::TOperatorRegistryRDG::ListAllRegisteredOperators`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/NNERuntimeRDGHlsl.h` (Private)


#### class `UNNERuntimeRDGHlslImpl`  
`class UNNERuntimeRDGHlslImpl : public UObject, public INNERuntime`  
_L16-34_
- reflection: `UCLASS()`
- inherits: `UObject,INNERuntime`
- L21 _public member_ `static FGuid GUID;`
- L22 _public member_ `static int32 Version;`
- L24 _public function_ `UNNERuntimeRDGHlslImpl()`
- L25 _public function_ `virtual ~UNNERuntimeRDGHlslImpl()`
- L27 _public prototype_ `bool Init();`
- L29 _public function_ `virtual FString GetRuntimeName() const override`
- L31 _public prototype_ `virtual ECanCreateModelDataStatus CanCreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L32 _public prototype_ `virtual TSharedPtr<UE::NNE::FSharedModelData> CreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) override;`
- L33 _public prototype_ `virtual FString GetModelDataIdentifier(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`

#### class `UNNERuntimeRDGHlslImplRDG`  
`class UNNERuntimeRDGHlslImplRDG : public UNNERuntimeRDGHlslImpl, public INNERuntimeRDG`  
_L37-46_
- reflection: `UCLASS()`
- inherits: `UNNERuntimeRDGHlslImpl,INNERuntimeRDG`
- L42 _public function_ `virtual ~UNNERuntimeRDGHlslImplRDG()`
- L44 _public prototype_ `virtual ECanCreateModelRDGStatus CanCreateModelRDG(const TObjectPtr<UNNEModelData> ModelData) const override;`
- L45 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelRDG> CreateModelRDG(const TObjectPtr<UNNEModelData> ModelData) override;`

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/NNERuntimeRDGHlslHelper.h` (Private)


#### struct `UE::NNERuntimeRDG::Private::Hlsl::FTensorInfoParamArraySpan`  
`struct FTensorInfoParamArraySpan`  
_L17-28_
- L19 _public member_ `TFunction<FUintVector4& (uint32)> ArrayAtFunction;`
- L20 _public member_ `uint32 Offset = 0;`
- L21 _public member_ `static constexpr uint32 Length = NXRT_TENSORSTRIDEINFO_MAX_NUM_DIMENSIONS;`
- L22 _public function_ `FUintVector4& operator[](uint32 Idx)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L11 _macro_ `#define NXRT_TENSORSTRIDEINFO_MAX_NUM_DIMENSIONS 8`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L13 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L15 _typedef_ `using FTensorInfoParam = TStaticArray<UE::Core::TAlignedElement<FUintVector4, 16>, NXRT_TENSORSTRIDEINFO_MAX_NUM_DIMENSIONS>;` (scope `UE::NNERuntimeRDG::Private::Hlsl`)
- L31 _prototype_ `template<typename TTensorInfoParam> void FillTensorSizeShaderParameters(const FTensor& Tensor, TTensorInfoParam& OutTensorInfoParam, int32 Idx);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)
- L33 _prototype_ `template<typename TTensorInfoParam> void FillTensorStrideShaderParameters(const FTensor& Tensor, TTensorInfoParam& OutTensorInfoParam, int32 Idx, int32 TargetNumdimensionForBroadcast = -1);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)
- L35 _prototype_ `template<typename TTensorInfoParam> void FillTensorStrideForBroadcastShaderParameters(const FTensor& Tensor, int32 OutputNumdimension, TTensorInfoParam& OutTensorInfoParam, int32 Idx);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)
- L36 _prototype_ `FIntVector ComputeElementWiseThreadGroups(uint32 ElementCount, uint32 GroupSizeX);` (scope `UE::NNERuntimeRDG::Private::Hlsl`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/NNERuntimeRDGHlslOp.h` (Private)


#### struct `UE::NNERuntimeRDG::Private::Hlsl::FOperatorHlsl`  
`struct FOperatorHlsl : public IOperatorRDG, public IPrepareOperator`  
_L12-18_
- inherits: `IOperatorRDG,IPrepareOperator`
- desc: Base class for all Hlsl ML operators
- L14 _public prototype_ `virtual ~FOperatorHlsl() = default;`
- L15 _public prototype_ `virtual bool Initialize(TConstArrayView<NNE::FTensorDesc> InputTensorDescs, TConstArrayView<NNE::FTensorDesc> OutputTensorDescs, const NNERuntimeRDGData::Internal::FAttributeMap& Attributes) = 0;`
- L16 _public prototype_ `virtual void Dispatch(FRDGBuilder& GraphBuilder, TConstArrayView<FTensorRDGRef> InInputTensors, TConstArrayView<FTensorRDGRef> InOutputTensors) = 0;`
- L17 _public function_ `virtual void OptimizeInputsWeights(TArrayView<FTensorRDGRef> InputWeights)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L7 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)
- L23 _typedef_ `typedef TOperatorRegistryRDG<FOperatorHlsl> FOperatorRegistryHlsl;` (scope `UE::NNERuntimeRDG::Private::Hlsl`) — HLSL ML operator registry

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/NNERuntimeRDGModel.h` (Private)


#### class `UE::NNERuntimeRDG::Private::FModelInstanceRDG`  
`class FModelInstanceRDG : public NNE::IModelInstanceRDG`  
_L12-64_
- inherits: `NNE::IModelInstanceRDG`
- L15 _public typedef_ `using ESetInputTensorShapesStatus = NNE::IModelInstanceRDG::ESetInputTensorShapesStatus;`
- L16 _public typedef_ `using EEnqueueRDGStatus = NNE::IModelInstanceRDG::EEnqueueRDGStatus;`
- L18 _public function_ `FModelInstanceRDG()`
- L19 _public prototype_ `virtual ~FModelInstanceRDG() = default;`
- L21 _public prototype_ `virtual TConstArrayView<NNE::FTensorDesc> GetInputTensorDescs() const override;`
- L22 _public prototype_ `virtual TConstArrayView<NNE::FTensorDesc> GetOutputTensorDescs() const override;`
- L23 _public prototype_ `virtual TConstArrayView<NNE::FTensorShape> GetInputTensorShapes() const override;`
- L24 _public prototype_ `virtual TConstArrayView<NNE::FTensorShape> GetOutputTensorShapes() const override;`
- L25 _public prototype_ `virtual ESetInputTensorShapesStatus SetInputTensorShapes(TConstArrayView<NNE::FTensorShape> InInputShapes) override;`
- L26 _public prototype_ `virtual EEnqueueRDGStatus EnqueueRDG(FRDGBuilder& RDGBuilder, TConstArrayView<NNE::FTensorBindingRDG> InInputBindings, TConstArrayView<NNE::FTensorBindingRDG> InOutputBindings) override;`
- L29 _protected prototype_ `static FRDGBufferDesc CreateRDGBufferDescForTensorRDG(const FTensorRDG& Tensor);`
- L30 _protected prototype_ `bool LoadModel(TConstArrayView<uint8> ModelData, FNNERuntimeRDGDataModelFormat& Format, int32 GuidAndVersionSize);`
- L31 _protected prototype_ `int32 SetTensors(FRDGBuilder& GraphBuilder, FTensorRDGArray& InTensorRDGs, TConstArrayView<NNE::FTensorBindingRDG> InBindings);`
- L33 _protected prototype_ `virtual int PrepareTensorShapesAndData() = 0;`
- L34 _protected function_ `virtual bool PrepareModelRDG(FRDGBuilder& RDGBuilder)`
- L35 _protected prototype_ `virtual void AddDispatchOps_RenderThread(FRDGBuilder& GraphBuilder) = 0;`
- L38 _protected member_ `TArray<NNE::FTensorShape> InputTensorShapes;` — Tensor shapes and descriptions
- L39 _protected member_ `TArray<NNE::FTensorShape> OutputTensorShapes;`
- L40 _protected member_ `TArray<NNE::FTensorDesc> InputSymbolicTensors;`
- L41 _protected member_ `TArray<NNE::FTensorDesc> OutputSymbolicTensors;`
- L44 _protected member_ `TMap<int32, NNE::FTensorDesc> AllSymbolicTensorDescs;` — Tensor descriptor
- L47 _protected member_ `TArray<int32> IntermediateTensorIndices;` — Tensor indices for models
- L48 _protected member_ `TArray<int32> WeightTensorIndices;`
- L49 _protected member_ `TArray<int32> InputTensorIndices;`
- L50 _protected member_ `TArray<int32> OutputTensorIndices;`
- L51 _protected member_ `TArray<int32> EmptyTensorIndices;`
- L54 _protected member_ `TArray<TArray<uint32>> OperatorInputTensorIndices;` — Tensor indices by operator
- L55 _protected member_ `TArray<TArray<uint32>> OperatorOutputTensorIndices;`
- L58 _protected member_ `FTensorRDGRefMap AllTensorRDGRefs;` — RDG Tensors
- L59 _protected member_ `FTensorRDGArray InputTensorRDGs;`
- L60 _protected member_ `FTensorRDGArray OutputTensorRDGs;`
- L61 _protected member_ `FTensorRDGArray EmptyTensorRDGs;`
- L62 _protected member_ `FTensorRDGArray IntermediateTensorRDGs;`
- L63 _protected member_ `FTensorRDGArray WeightTensorRDGs;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/NNERuntimeRDGModelHlsl.h` (Private)


#### class `UE::NNERuntimeRDG::Private::Hlsl::FModelInstance`  
`class FModelInstance : public FModelInstanceRDG`  
_L15-37_
- inherits: `FModelInstanceRDG`
- L20 _public prototype_ `~FModelInstance();`
- L22 _public prototype_ `bool Init(TConstArrayView<uint8> ModelData);`
- L26 _protected prototype_ `virtual int PrepareTensorShapesAndData() override;`
- L27 _protected prototype_ `virtual bool PrepareModelRDG(FRDGBuilder& RDGBuilder) override;`
- L28 _protected prototype_ `virtual void AddDispatchOps_RenderThread(FRDGBuilder& GraphBuilder) override;`
- L30 _protected prototype_ `void PrepareWeights();`
- L34 _private member_ `TArray<FOperatorHlsl*> Operators;`
- L35 _private member_ `TArray<TRefCountPtr<FRDGPooledBuffer>> WeightsExternalRDGResources;`
- L36 _private member_ `TArray<TRefCountPtr<FRDGPooledBuffer>> ConstantsExternalRDGResources;`

#### class `UE::NNERuntimeRDG::Private::Hlsl::FModel`  
`class FModel : public NNE::IModelRDG`  
_L39-49_
- inherits: `NNE::IModelRDG`
- L42 _public prototype_ `FModel(const TSharedPtr<UE::NNE::FSharedModelData>& InModelData);`
- L43 _public function_ `virtual ~FModel()`
- L45 _public prototype_ `virtual TSharedPtr<NNE::IModelInstanceRDG> CreateModelInstanceRDG() override;`
- L48 _private member_ `TSharedPtr<UE::NNE::FSharedModelData> ModelData;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L11 _namespace_ `namespace Hlsl` (scope `UE::NNERuntimeRDG::Private`)

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/NNERuntimeRDGModule.h` (Private)


#### class `FNNERuntimeRDGModule`  
`class FNNERuntimeRDGModule : public IModuleInterface`  
_L13-24_
- inherits: `IModuleInterface`
- L16 _private prototype_ `void RegisterRuntime();`
- L19 _public member_ `TWeakObjectPtr<UNNERuntimeRDGHlslImpl> NNERuntimeRDGHlsl{ nullptr };`
- L22 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/NNERuntimeRDG/Source/NNERuntimeRDG/Private/NNERuntimeRDGTensor.h` (Private)


#### class `UE::NNERuntimeRDG::Private::FTensor`  
`class FTensor`  
_L12-119_
- desc: Concrete tensor with data accessible by graph scheduling
- L15 _protected member_ `FString Name;`
- L16 _protected member_ `ENNETensorDataType DataType;`
- L17 _protected member_ `NNE::FTensorShape Shape;`
- L18 _protected member_ `TArray<uint8> PreparedData;`
- L19 _protected member_ `uint64 DataSize = 0;`
- L20 _protected member_ `uint32 Volume = 0;`
- L22 _protected prototype_ `FTensor() = default;`
- L25 _public function_ `const FString& GetName() const`
- L30 _public function_ `ENNETensorDataType GetDataType() const`
- L35 _public function_ `uint32 GetElementByteSize() const`
- L40 _public function_ `const NNE::FTensorShape& GetShape() const`
- L45 _public function_ `template <typename T> TConstArrayView<T> GetPreparedData() const`
- L54 _public function_ `void SetShape(const NNE::FTensorShape& InShape)`
- L63 _public function_ `template <typename T> void SetPreparedData(TConstArrayView<T> Data)`
- L73 _public function_ `bool IsEmpty() const`
- L80 _public function_ `bool HasPreparedData() const`
- L85 _public function_ `bool IsConstant() const`
- L90 _public function_ `uint32 GetVolume() const`
- L95 _public function_ `uint64 GetDataSize() const`
- L100 _public function_ `static FTensor Make(const FString& Name, const NNE::FTensorShape& Shape, ENNETensorDataType DataType)`
- L109 _public function_ `static FTensor Make(const NNE::FTensorDesc& TensorDesc, const NNE::FTensorShape& Shape)`
- L115 _public function_ `static FTensor MakeFromSymbolicDesc(const NNE::FTensorDesc& TensorDesc)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNERuntimeRDG` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::NNERuntimeRDG`)
- L121 _typedef_ `using FTensorRef = FTensor*;` (scope `UE::NNERuntimeRDG::Private`)
