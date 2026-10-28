# Runtime / DataflowCore

- module root: `Source/Runtime/Dataflow/Core`
- headers: 45; symbols: 2307
- symbol kinds: class=17, delegate=12, enum=15, enumerator=76, function=425, macro=33, member=499, namespace=66, prototype=828, struct=260, typedef=76
- PublicDependencyModuleNames: ApplicationCore, AssetRegistry, Chaos, Core, CoreUObject, DeveloperSettings, ImageCore, InputCore, SlateCore

### `Source/Runtime/Dataflow/Core/Private/Dataflow/DataflowConvertNodes.h` (Private)


#### struct `FConvertNumericTypesDataflowNode`  
`struct FConvertNumericTypesDataflowNode : public FDataflowNode`  
_L28-48_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert Numeric types (double, float, int64, uint64, int32, uint32, int16, uint16, int8, uint8)
- L40 _public member_ `FDataflowNumericTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L43 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L47 _public prototype_ `FConvertNumericTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertVectorTypesDataflowNode`  
`struct FConvertVectorTypesDataflowNode : public FDataflowNode`  
_L55-75_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert Vector types (2D, 3D and 4D vector, single and double precision)
- L63 _private member_ `FDataflowVectorTypes In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L67 _private member_ `FDataflowVectorTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L70 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L74 _public prototype_ `FConvertVectorTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertStringTypesDataflowNode`  
`struct FConvertStringTypesDataflowNode : public FDataflowNode`  
_L82-102_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert String types (FString or FName or FText)
- L90 _private member_ `FDataflowStringTypes In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L94 _private member_ `FDataflowStringTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L97 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L101 _public prototype_ `FConvertStringTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertBoolTypesDataflowNode`  
`struct FConvertBoolTypesDataflowNode : public FDataflowNode`  
_L108-128_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert Bool types
- L116 _private member_ `FDataflowBoolTypes In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L120 _private member_ `FDataflowBoolTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L123 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L127 _public prototype_ `FConvertBoolTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertTransformTypesDataflowNode`  
`struct FConvertTransformTypesDataflowNode : public FDataflowNode`  
_L134-154_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert Transform types
- L142 _private member_ `FDataflowTransformTypes In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L146 _private member_ `FDataflowTransformTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L149 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L153 _public prototype_ `FConvertTransformTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertStringConvertibleTypesDataflowNode`  
`struct FConvertStringConvertibleTypesDataflowNode : public FDataflowNode`  
_L161-181_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert String convertible types (String types, Numeric types, Vector types and Booleans)
- L169 _private member_ `FDataflowStringConvertibleTypes In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L173 _private member_ `FDataflowStringConvertibleTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L176 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L180 _public prototype_ `FConvertStringConvertibleTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertUObjectConvertibleTypesDataflowNode`  
`struct FConvertUObjectConvertibleTypesDataflowNode : public FDataflowNode`  
_L187-207_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert UObject types
- L195 _private member_ `FDataflowUObjectConvertibleTypes In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L199 _private member_ `FDataflowUObjectConvertibleTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L202 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L206 _public prototype_ `FConvertUObjectConvertibleTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertSelectionTypesDataflowNode`  
`struct FConvertSelectionTypesDataflowNode : public FDataflowNode`  
_L213-243_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert Selection types
- L221 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — GeometryCollection for the selection
- L225 _private member_ `FDataflowSelectionTypes In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L231 _private member_ `bool bAllElementsMustBeSelected = false;` — `UPROPERTY(EditAnywhere, Category = "Selection")` — If true then for converting vertex/face selection to transform/geometry selection all vertex/face must be selected for selecting the associated transform/geometry or going from vertex to face selection all vertices must be selected to select the face
- L235 _private member_ `FDataflowSelectionTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L238 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L242 _public prototype_ `FConvertSelectionTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertSelectionTypesToIndexArrayDataflowNode`  
`struct FConvertSelectionTypesToIndexArrayDataflowNode : public FDataflowNode`  
_L249-270_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert Selection to Index Array
- L258 _private member_ `FDataflowSelectionTypes In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L262 _private member_ `TArray<int32> Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L265 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L269 _public prototype_ `FConvertSelectionTypesToIndexArrayDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertIndexToSelectionTypesDataflowNode`  
`struct FConvertIndexToSelectionTypesDataflowNode : public FDataflowNode`  
_L276-301_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert Index to Selection
- L282 _public prototype_ `FConvertIndexToSelectionTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L288 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection for the selection
- L292 _private member_ `int32 In = 0;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L296 _private member_ `FDataflowSelectionTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L299 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FConvertIndexArrayToSelectionTypesDataflowNode`  
`struct FConvertIndexArrayToSelectionTypesDataflowNode : public FDataflowNode`  
_L307-332_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert Index Array to Selection
- L313 _public prototype_ `FConvertIndexArrayToSelectionTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L319 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection", DataflowIntrinsic))` — Collection for the selection
- L323 _private member_ `TArray<int32> In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L327 _private member_ `FDataflowSelectionTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L330 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FConvertVectorArrayTypesDataflowNode`  
`struct FConvertVectorArrayTypesDataflowNode : public FDataflowNode`  
_L339-359_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert Vector array types
- L347 _private member_ `FDataflowVectorArrayTypes In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L351 _private member_ `FDataflowVectorArrayTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L354 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L358 _public prototype_ `FConvertVectorArrayTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertNumericArrayTypesDataflowNode`  
`struct FConvertNumericArrayTypesDataflowNode : public FDataflowNode`  
_L365-385_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert Numeric array types
- L373 _private member_ `FDataflowNumericArrayTypes In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L377 _private member_ `FDataflowNumericArrayTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L380 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L384 _public prototype_ `FConvertNumericArrayTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertStringArrayTypesDataflowNode`  
`struct FConvertStringArrayTypesDataflowNode : public FDataflowNode`  
_L391-411_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert String array types
- L399 _private member_ `FDataflowStringArrayTypes In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L403 _private member_ `FDataflowStringArrayTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L406 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L410 _public prototype_ `FConvertStringArrayTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertBoolArrayTypesDataflowNode`  
`struct FConvertBoolArrayTypesDataflowNode : public FDataflowNode`  
_L417-437_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert Bool array types
- L425 _private member_ `FDataflowBoolArrayTypes In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L429 _private member_ `FDataflowBoolArrayTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L432 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L436 _public prototype_ `FConvertBoolArrayTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertTransformArrayTypesDataflowNode`  
`struct FConvertTransformArrayTypesDataflowNode : public FDataflowNode`  
_L443-463_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert Transform array types
- L451 _private member_ `FDataflowTransformArrayTypes In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L455 _private member_ `FDataflowTransformArrayTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L458 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L462 _public prototype_ `FConvertTransformArrayTypesDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FConvertRotationDataflowNode`  
`struct FConvertRotationDataflowNode : public FDataflowNode`  
_L470-490_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert Rotation (FQuat, FRotator, FVector)
- L478 _private member_ `FDataflowRotationTypes In;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic))` — Input value
- L482 _private member_ `FDataflowRotationTypes Out;` — `UPROPERTY(meta = (DataflowOutput))` — Output value
- L485 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L489 _public prototype_ `FConvertRotationDataflowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### Free symbols / members of external scopes

- L21 _macro_ `#define DATAFLOW_CONVERT_NODES_CATEGORY "Convert"`
- L492 _namespace_ `namespace UE`
- L492 _namespace_ `namespace Dataflow` (scope `UE`)
- L494 _prototype_ `void RegisterDataflowConvertNodes();` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Core/Private/Dataflow/DataflowCoreLogPrivate.h` (Private)


#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_STATS_GROUP(TEXT("Dataflow"), STATGROUP_Dataflow, STATCAT_Ad`

### `Source/Runtime/Dataflow/Core/Private/Dataflow/DataflowCoreModule.h` (Private)


#### class `IDataflowCoreModule`  
`class IDataflowCoreModule : public IModuleInterface`  
_L14-30_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public prototype_ `virtual void StartupModule() override;`
- L23 _public prototype_ `virtual void ShutdownModule() override;`
- L25 _public function_ `virtual bool SupportsDynamicReloading() override`

### `Source/Runtime/Dataflow/Core/Private/Dataflow/DataflowCoreNodeAndPinTypeColors.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Dataflow` (scope `UE`)
- L7 _prototype_ `void RegisterDataflowCoreColors();` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Core/Private/Dataflow/DataflowDemandPullSlice.h` (Private)


#### struct `UE::Dataflow::FDemandPullSlice`  
`struct FDemandPullSlice`  
_L22-26_
- desc: Result of a demand-pull slice computation. SliceMask          : per-node bit, sized to CompiledGraph.GetNumNodes(); true if the node needs to evaluate. Sync evaluators only need OrderedNodeIndices, but the async/TaskGraph variant uses the mask for O(1) "is upstream node N in the slice?" prerequisite filtering. OrderedNodeIndices : slice node indices in the compiled graph's topological order. Subset of [0, NumNodes).
- L24 _public member_ `TBitArray<> SliceMask;`
- L25 _public member_ `TArray<int32> OrderedNodeIndices;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Dataflow` (scope `UE`)
- L41 _prototype_ `void ComputeDemandPullSlice( const FCompiledGraph& CompiledGraph, FContext& Context, TConstArrayView<FGuid> TargetNodeIds, FDemandPullSlice& OutSlice);` (scope `UE::Dataflow`) — Compute the minimal upstream slice required to bring a set of target nodes up to date. Walks the source FGraph's input/output topology starting from each target, pruning at any upstream output whose cache is already valid (FDataflowOutput::HasValidData) or frozen. The resulting slice is then sweep-ordered against FCompiledGraph::Nodes (which is itself topologically ordered, sources-first). TargetNodeIds == empty => seed from every terminal in the compiled graph (full evaluation with cache-aware pruning, equivalent to today's left-to-right behaviour but skipping cached nodes). Game-thread only. Must not overlap with a FDataflowTaskGraphEvaluator run on the same FContext.

### `Source/Runtime/Dataflow/Core/Private/Dataflow/DataflowImageNodes.h` (Private)


#### enum `EDataflowConvertToResolutionMethod`  
`enum class EDataflowConvertToResolutionMethod : int32`  
_L13-18_
- reflection: `UENUM()`
- L15 _public enumerator_ `UseClosest = 0 UMETA(DisplayName = "Closest resolution")`
- L16 _public enumerator_ `UsePrevious = 1 UMETA(DisplayName = "Previous resolution")`
- L17 _public enumerator_ `UseNext = 2 UMETA(DisplayName = "Next resolution")`

#### struct `FDataflowConvertToResolutionNode`  
`struct FDataflowConvertToResolutionNode : public FDataflowNode`  
_L24-46_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Convert a numeric value into a resolution
- L35 _private member_ `FDataflowNumericTypes Value;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — Arbitrary value to convert to a image resolution type
- L39 _private member_ `EDataflowConvertToResolutionMethod Method = EDataflowConvertToResolutionMethod::UseClosest;` — `UPROPERTY(EditAnywhere, Category = Options)` — Method to use to match the resolution
- L43 _private member_ `EDataflowImageResolution Resolution = EDataflowImageResolution::Resolution16;` — `UPROPERTY(meta = (DataflowOutput))` — Output resolution
- L45 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowImageFromColorNode`  
`struct FDataflowImageFromColorNode : public FDataflowNode`  
_L53-75_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Create a RGBA image from a single color at a specific resolution Outputs are single channel images
- L59 _public prototype_ `FDataflowImageFromColorNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L64 _private member_ `FLinearColor FillColor = FLinearColor::Black;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — color  to fill the image with
- L68 _private member_ `EDataflowImageResolution Resolution = EDataflowImageResolution::Resolution16;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DataflowInput))` — resolution of the output image
- L72 _private member_ `FDataflowImage Image;` — `UPROPERTY(meta = (DataflowOutput))` — Output image
- L74 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowImageSplitChannelsNode`  
`struct FDataflowImageSplitChannelsNode : public FDataflowNode`  
_L82-112_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Split a image in individual channels Outputs are single channel images
- L88 _public prototype_ `FDataflowImageSplitChannelsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L93 _private member_ `FDataflowImage Image;` — `UPROPERTY(meta = (DataflowInput))` — Input image to split per channel
- L97 _private member_ `FDataflowImage Red;` — `UPROPERTY(meta = (DataflowOutput, PinColor = "R=1, G=0, B=0"))` — Red channel
- L101 _private member_ `FDataflowImage Green;` — `UPROPERTY(meta = (DataflowOutput, PinColor = "R=0, G=1, B=0"))` — Green channel
- L105 _private member_ `FDataflowImage Blue;` — `UPROPERTY(meta = (DataflowOutput, PinColor = "R=0, G=0.2, B=1"))` — Blue channel
- L109 _private member_ `FDataflowImage Alpha;` — `UPROPERTY(meta = (DataflowOutput, PinColor = "R=0.7, G=0.7, B=0.7"))` — Alpha channel
- L111 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### enum `EDataflowImageCombineResolutionOption`  
`enum class EDataflowImageCombineResolutionOption : int32`  
_L115-120_
- reflection: `UENUM()`
- L117 _public enumerator_ `Lowest = 0 UMETA(DisplayName = "Lowest Resolution")`
- L118 _public enumerator_ `Highest = 1 UMETA(DisplayName = "Highest Resolution")`
- L119 _public enumerator_ `UserDefined = 2 UMETA(DisplayName = "User Defined Resolution ")`

#### struct `FDataflowImageCombineChannelsNode`  
`struct FDataflowImageCombineChannelsNode : public FDataflowNode`  
_L127-167_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Combine channels into a single RGBA image Outputs are single channel images
- L133 _public prototype_ `FDataflowImageCombineChannelsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L138 _private member_ `FDataflowImage Red;` — `UPROPERTY(meta = (DataflowInput, PinColor = "R=1, G=0, B=0"))` — Red channel - if not connected, use black color
- L142 _private member_ `FDataflowImage Green;` — `UPROPERTY(meta = (DataflowInput, PinColor = "R=0, G=1, B=0"))` — Green channel - if not connected, use black color
- L146 _private member_ `FDataflowImage Blue;` — `UPROPERTY(meta = (DataflowInput, PinColor = "R=0, G=0.2, B=1"))` — Blue channel - if not connected, use black color
- L150 _private member_ `FDataflowImage Alpha;` — `UPROPERTY(meta = (DataflowInput, PinColor = "R=0.7, G=0.7, B=0.7"))` — Alpha channel - if not connected, use black color
- L154 _private member_ `FDataflowImage Image;` — `UPROPERTY(meta = (DataflowOutput))` — Output image recombined from input channels
- L158 _private member_ `EDataflowImageCombineResolutionOption ResolutionOptions = EDataflowImageCombineResolutionOption::Highest;` — `UPROPERTY(EditAnywhere, Category = Options)` — resolution option
- L162 _private member_ `EDataflowImageResolution Resolution = EDataflowImageResolution::Resolution512;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (EditCondition = "ResolutionOptions == EDataflowImageCombineResolutionOption::UserDefined"))` — resolution of the output image if the resolution option is set to user defined
- L164 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L166 _private prototype_ `void GetUserDefinedResolution(const TArray<const FDataflowImage*>& Images, int32& OutWidth, int32& OutHeight) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define DATAFLOW_IMAGE_NODES_CATEGORY "Image"`
- L169 _namespace_ `namespace UE`
- L169 _namespace_ `namespace Dataflow` (scope `UE`)
- L171 _prototype_ `void RegisterDataflowImageNodes();` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Core/Private/Dataflow/DataflowMathNodes.h` (Private)


#### struct `FDataflowMathOneInputOperatorNode`  
`struct FDataflowMathOneInputOperatorNode : public FDataflowNode`  
_L23-41_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: One input operators base class
- L28 _public member_ `FDataflowNumericTypes A;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))`
- L31 _public member_ `FDataflowNumericTypes Result;` — `UPROPERTY(meta = (DataflowOutput))`
- L34 _public function_ `FDataflowMathOneInputOperatorNode()`
- L35 _public prototype_ `FDataflowMathOneInputOperatorNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L36 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L39 _protected prototype_ `void RegisterInputsAndOutputs();`
- L40 _protected function_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const`

#### struct `FDataflowMathTwoInputsOperatorNode`  
`struct FDataflowMathTwoInputsOperatorNode : public FDataflowNode`  
_L45-66_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Two inputs operators base class
- L50 _public member_ `FDataflowNumericTypes A;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))`
- L53 _public member_ `FDataflowNumericTypes B;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))`
- L56 _public member_ `FDataflowNumericTypes Result;` — `UPROPERTY(meta = (DataflowOutput))`
- L59 _public function_ `FDataflowMathTwoInputsOperatorNode()`
- L60 _public prototype_ `FDataflowMathTwoInputsOperatorNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L61 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L64 _protected prototype_ `void RegisterInputsAndOutputs();`
- L65 _protected function_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA, double InB) const`

#### struct `FDataflowMathAddNode`  
`struct FDataflowMathAddNode : public FDataflowMathTwoInputsOperatorNode`  
_L70-78_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathTwoInputsOperatorNode`
- desc: Addition (A + B)
- L76 _public prototype_ `FDataflowMathAddNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L77 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA, double InB) const override;`

#### struct `FDataflowMathSubtractNode`  
`struct FDataflowMathSubtractNode : public FDataflowMathTwoInputsOperatorNode`  
_L82-90_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathTwoInputsOperatorNode`
- desc: Subtraction (A - B)
- L88 _public prototype_ `FDataflowMathSubtractNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L89 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA, double InB) const override;`

#### struct `FDataflowMathMultiplyNode`  
`struct FDataflowMathMultiplyNode : public FDataflowMathTwoInputsOperatorNode`  
_L94-102_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathTwoInputsOperatorNode`
- desc: Multiplication (A * B)
- L100 _public prototype_ `FDataflowMathMultiplyNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L101 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA, double InB) const override;`

#### struct `FDataflowMathDivideNode`  
`struct FDataflowMathDivideNode : public FDataflowMathTwoInputsOperatorNode`  
_L109-120_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathTwoInputsOperatorNode`
- desc: Division (A / B) if B is equal to 0, 0 is returned Fallback value
- L115 _public member_ `FDataflowNumericTypes Fallback;` — `UPROPERTY(EditAnywhere, Category = SafeDivide, meta = (DataflowInput))`
- L118 _public prototype_ `FDataflowMathDivideNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L119 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA, double InB) const override;`

#### struct `FDataflowMathMinimumNode`  
`struct FDataflowMathMinimumNode : public FDataflowMathTwoInputsOperatorNode`  
_L128-136_
- reflection: `USTRUCT(meta = (Deprecated = "5.6"))`
- inherits: `FDataflowMathTwoInputsOperatorNode`
- desc: Minimum ( Min(A, B) ) Deprecated (5.6) Use Minimum (V2) with variable number of inputs instead
- L134 _public prototype_ `FDataflowMathMinimumNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L135 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA, double InB) const override;`

#### struct `FDataflowMathMinimumNode_v2`  
`struct FDataflowMathMinimumNode_v2 : public FDataflowNode`  
_L142-171_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Minimum ( Min(A, B, C, ... ) )
- L149 _private member_ `TArray<FDataflowNumericTypes> Inputs;` — `UPROPERTY()`
- L152 _private member_ `FDataflowNumericTypes Result;` — `UPROPERTY(meta = (DataflowOutput))`
- L155 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L156 _private prototype_ `virtual bool CanAddPin() const override;`
- L157 _private prototype_ `virtual bool CanRemovePin() const override;`
- L158 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L159 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L160 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L161 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L164 _private prototype_ `UE::Dataflow::TConnectionReference<FDataflowNumericTypes> GetConnectionReference(int32 Index) const;`
- L166 _private member_ `static constexpr int32 NumOtherInputs = 0;` — No other inputs
- L167 _private member_ `static constexpr int32 NumInitialVariableInputs = 2;`
- L170 _public prototype_ `FDataflowMathMinimumNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FDataflowMathMaximumNode`  
`struct FDataflowMathMaximumNode : public FDataflowMathTwoInputsOperatorNode`  
_L179-187_
- reflection: `USTRUCT(meta = (Deprecated = "5.6"))`
- inherits: `FDataflowMathTwoInputsOperatorNode`
- desc: Maximum ( Max(A, B) ) Deprecated (5.6) Use Maximum (V2) with variable number of inputs instead
- L185 _public prototype_ `FDataflowMathMaximumNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L186 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA, double InB) const override;`

#### struct `FDataflowMathMaximumNode_v2`  
`struct FDataflowMathMaximumNode_v2 : public FDataflowNode`  
_L191-220_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Maximum ( Max(A, B, C, ... ) )
- L198 _private member_ `TArray<FDataflowNumericTypes> Inputs;` — `UPROPERTY()`
- L201 _private member_ `FDataflowNumericTypes Result;` — `UPROPERTY(meta = (DataflowOutput))`
- L204 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L205 _private prototype_ `virtual bool CanAddPin() const override;`
- L206 _private prototype_ `virtual bool CanRemovePin() const override;`
- L207 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L208 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L209 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L210 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L213 _private prototype_ `UE::Dataflow::TConnectionReference<FDataflowNumericTypes> GetConnectionReference(int32 Index) const;`
- L215 _private member_ `static constexpr int32 NumOtherInputs = 0;` — No other inputs
- L216 _private member_ `static constexpr int32 NumInitialVariableInputs = 2;`
- L219 _public prototype_ `FDataflowMathMaximumNode_v2(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`

#### struct `FDataflowMathReciprocalNode`  
`struct FDataflowMathReciprocalNode : public FDataflowMathOneInputOperatorNode`  
_L227-238_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Reciprocal( 1 / A ) if A is equal to 0, returns Fallback
- L233 _public member_ `FDataflowNumericTypes Fallback;` — `UPROPERTY(EditAnywhere, Category = SafeDivide, meta = (DataflowInput))`
- L236 _public prototype_ `FDataflowMathReciprocalNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L237 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathSquareNode`  
`struct FDataflowMathSquareNode : public FDataflowMathOneInputOperatorNode`  
_L242-250_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Square ( A * A )
- L248 _public prototype_ `FDataflowMathSquareNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L249 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathCubeNode`  
`struct FDataflowMathCubeNode : public FDataflowMathOneInputOperatorNode`  
_L254-262_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Cube ( A * A * A )
- L260 _public prototype_ `FDataflowMathCubeNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L261 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathSquareRootNode`  
`struct FDataflowMathSquareRootNode : public FDataflowMathOneInputOperatorNode`  
_L266-274_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Square Root ( sqrt(A) )
- L272 _public prototype_ `FDataflowMathSquareRootNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L273 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathInverseSquareRootNode`  
`struct FDataflowMathInverseSquareRootNode : public FDataflowMathOneInputOperatorNode`  
_L281-292_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Inverse Square Root ( 1 / sqrt(A) ) if A is equal to 0, returns Fallback
- L287 _public member_ `FDataflowNumericTypes Fallback;` — `UPROPERTY(EditAnywhere, Category = SafeDivide, meta = (DataflowInput))`
- L290 _public prototype_ `FDataflowMathInverseSquareRootNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L291 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathNegateNode`  
`struct FDataflowMathNegateNode : public FDataflowMathOneInputOperatorNode`  
_L296-304_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Negate ( -A )
- L302 _public prototype_ `FDataflowMathNegateNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L303 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathAbsNode`  
`struct FDataflowMathAbsNode : public FDataflowMathOneInputOperatorNode`  
_L308-316_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Absolute value ( |A| )
- L314 _public prototype_ `FDataflowMathAbsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L315 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathFloorNode`  
`struct FDataflowMathFloorNode : public FDataflowMathOneInputOperatorNode`  
_L320-328_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Floor ( 1.4 => 1.0 | 1.9 => 1.0 | -5.3 => -6.0 )
- L326 _public prototype_ `FDataflowMathFloorNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L327 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathCeilNode`  
`struct FDataflowMathCeilNode : public FDataflowMathOneInputOperatorNode`  
_L332-340_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Ceil ( 1.4 => 2.0 | 1.9 => 2.0 | -5.3 => -5.0)
- L338 _public prototype_ `FDataflowMathCeilNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L339 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathRoundNode`  
`struct FDataflowMathRoundNode : public FDataflowMathOneInputOperatorNode`  
_L344-352_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Round ( 1.4 => 1.0 | 1.9 => 2.0 | -5.3 => -5.0)
- L350 _public prototype_ `FDataflowMathRoundNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L351 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathTruncNode`  
`struct FDataflowMathTruncNode : public FDataflowMathOneInputOperatorNode`  
_L356-364_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Trunc ( 1.4 => 1.0 | 1.9 => 1.0 | -5.3 => -5.0)
- L362 _public prototype_ `FDataflowMathTruncNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L363 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathFracNode`  
`struct FDataflowMathFracNode : public FDataflowMathOneInputOperatorNode`  
_L368-376_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Frac ( 1.4 => 0.4 | 1.9 => 0.9 | -5.3 => 0.3 )
- L374 _public prototype_ `FDataflowMathFracNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L375 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathPowNode`  
`struct FDataflowMathPowNode : public FDataflowMathTwoInputsOperatorNode`  
_L380-388_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathTwoInputsOperatorNode`
- desc: power ( A ^ B)
- L386 _public prototype_ `FDataflowMathPowNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L387 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA, double InB) const override;`

#### struct `FDataflowMathLogXNode`  
`struct FDataflowMathLogXNode : public FDataflowMathOneInputOperatorNode`  
_L395-406_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Log for a specific base ( Log[Base](A) ) If base is negative or zero returns 0
- L401 _public member_ `FDataflowNumericTypes Base;` — `UPROPERTY(EditAnywhere, Category = SafeDivide, meta = (DataflowInput))`
- L404 _public prototype_ `FDataflowMathLogXNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L405 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathLogNode`  
`struct FDataflowMathLogNode : public FDataflowMathOneInputOperatorNode`  
_L410-418_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Natural log ( Log(A) )
- L416 _public prototype_ `FDataflowMathLogNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L417 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathExpNode`  
`struct FDataflowMathExpNode : public FDataflowMathOneInputOperatorNode`  
_L422-430_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Exponential ( Exp(A) )
- L428 _public prototype_ `FDataflowMathExpNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L429 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathSignNode`  
`struct FDataflowMathSignNode : public FDataflowMathOneInputOperatorNode`  
_L434-442_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: return -1, 0, +1 whether the input is respectively negative, zero or positive ( Sign(A) )
- L440 _public prototype_ `FDataflowMathSignNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L441 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathOneMinusNode`  
`struct FDataflowMathOneMinusNode : public FDataflowMathOneInputOperatorNode`  
_L446-454_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: One minus (1 - A)
- L452 _public prototype_ `FDataflowMathOneMinusNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L453 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### enum `EDataflowMathConstantsEnum`  
`enum class EDataflowMathConstantsEnum : uint8`  
_L457-475_
- reflection: `UENUM(BlueprintType)`
- L459 _public enumerator_ `Dataflow_Math_Constants_Pi UMETA(DisplayName = "Pi")`
- L460 _public enumerator_ `Dataflow_Math_Constants_HalfPi UMETA(DisplayName = "HalfPi")`
- L461 _public enumerator_ `Dataflow_Math_Constants_TwoPi UMETA(DisplayName = "TwoPi")`
- L462 _public enumerator_ `Dataflow_Math_Constants_FourPi UMETA(DisplayName = "FourPi")`
- L463 _public enumerator_ `Dataflow_Math_Constants_InvPi UMETA(DisplayName = "InvPi")`
- L464 _public enumerator_ `Dataflow_Math_Constants_InvTwoPi UMETA(DisplayName = "InvTwoPi")`
- L465 _public enumerator_ `Dataflow_Math_Constants_Sqrt2 UMETA(DisplayName = "Sqrt2")`
- L466 _public enumerator_ `Dataflow_Math_Constants_InvSqrt2 UMETA(DisplayName = "InvSqrt2")`
- L467 _public enumerator_ `Dataflow_Math_Constants_Sqrt3 UMETA(DisplayName = "Sqrt3")`
- L468 _public enumerator_ `Dataflow_Math_Constants_InvSqrt3 UMETA(DisplayName = "InvSqrt3")`
- L469 _public enumerator_ `Dataflow_Math_Constants_E UMETA(DisplayName = "e")`
- L470 _public enumerator_ `Dataflow_Math_Constants_Gamma UMETA(DisplayName = "Gamma")`
- L471 _public enumerator_ `Dataflow_Math_Constants_GoldenRatio UMETA(DisplayName = "GoldenRatio")`
- L474 _public enumerator_ `Dataflow_Math_Constants_Max UMETA(Hidden)` — 256th entry

#### struct `FDataflowMathConstantNode`  
`struct FDataflowMathConstantNode : public FDataflowNode`  
_L479-497_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Math constants ( see EDataflowMathConstantsEnum )
- L486 _public member_ `EDataflowMathConstantsEnum Constant = EDataflowMathConstantsEnum::Dataflow_Math_Constants_Pi;` — `UPROPERTY(EditAnywhere, Category = "Constants")` — Math constant to output
- L489 _public member_ `FDataflowNumericTypes Result;` — `UPROPERTY(meta = (DataflowOutput))`
- L492 _public prototype_ `FDataflowMathConstantNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L493 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`
- L496 _private prototype_ `double GetConstant() const;`

#### struct `FDataflowMathClampNode`  
`struct FDataflowMathClampNode : public FDataflowMathOneInputOperatorNode`  
_L501-515_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Clamp(A, Min, Max) clamp a value to specific range (inclusive)
- L510 _public member_ `FDataflowNumericTypes Max;` — `UPROPERTY(EditAnywhere, Category = "Clamp", meta = (DataflowInput))`
- L513 _public prototype_ `FDataflowMathClampNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L514 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathSinNode`  
`struct FDataflowMathSinNode : public FDataflowMathOneInputOperatorNode`  
_L527-535_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Sin(A) with A in radians
- L533 _public prototype_ `FDataflowMathSinNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L534 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathCosNode`  
`struct FDataflowMathCosNode : public FDataflowMathOneInputOperatorNode`  
_L539-547_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Cos(A) with A in radians
- L545 _public prototype_ `FDataflowMathCosNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L546 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathTanNode`  
`struct FDataflowMathTanNode : public FDataflowMathOneInputOperatorNode`  
_L551-559_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: Tan(A) with A in radians
- L557 _public prototype_ `FDataflowMathTanNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L558 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathArcSinNode`  
`struct FDataflowMathArcSinNode : public FDataflowMathOneInputOperatorNode`  
_L563-571_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: ArcSin(A) returns a value in radians
- L569 _public prototype_ `FDataflowMathArcSinNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L570 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathArcCosNode`  
`struct FDataflowMathArcCosNode : public FDataflowMathOneInputOperatorNode`  
_L575-583_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: ArcCos(A) returns a value in radians
- L581 _public prototype_ `FDataflowMathArcCosNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L582 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathArcTanNode`  
`struct FDataflowMathArcTanNode : public FDataflowMathOneInputOperatorNode`  
_L587-595_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: ArcTan(A) returns a value in radians
- L593 _public prototype_ `FDataflowMathArcTanNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L594 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathArcTan2Node`  
`struct FDataflowMathArcTan2Node : public FDataflowMathTwoInputsOperatorNode`  
_L599-607_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathTwoInputsOperatorNode`
- desc: ArcTan2(A, B) returns a value in radians
- L605 _public prototype_ `FDataflowMathArcTan2Node(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L606 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA, double InB) const override;`

#### struct `FDataflowMathDegToRadNode`  
`struct FDataflowMathDegToRadNode : public FDataflowMathOneInputOperatorNode`  
_L612-620_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: DegToRad(A) convert degrees to radians
- L618 _public prototype_ `FDataflowMathDegToRadNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L619 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### struct `FDataflowMathRadToDegNode`  
`struct FDataflowMathRadToDegNode : public FDataflowMathOneInputOperatorNode`  
_L624-632_
- reflection: `USTRUCT()`
- inherits: `FDataflowMathOneInputOperatorNode`
- desc: RadToDeg(A) convert radians to degrees
- L630 _public prototype_ `FDataflowMathRadToDegNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L631 _public prototype_ `virtual double ComputeResult(UE::Dataflow::FContext& Context, double InA) const override;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define DATAFLOW_MATH_NODES_CATEGORY "Math|Scalar"`
- L523 _macro_ `#define DATAFLOW_MATH_TRIG_NODES_CATEGORY "Math|Trig"`
- L655 _namespace_ `namespace UE`
- L655 _namespace_ `namespace Dataflow` (scope `UE`)
- L657 _prototype_ `void RegisterDataflowMathNodes();` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Core/Private/Dataflow/DataflowSystem.h` (Private)


#### struct `UE::Dataflow::FSystem`  
`struct FSystem`  
_L9-16_
- L12 _public prototype_ `static Dataflow::FSystem& Get();`
- L15 _public member_ `Dataflow::FTaskGraph TaskGraph;` — TaskGraph to schedule Dtaaflow specific tasks

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Dataflow` (scope `UE`)

### `Source/Runtime/Dataflow/Core/Private/Dataflow/DataflowTaskGraph.h` (Private)


#### struct `UE::Dataflow::FTask`  
`struct FTask`  
_L12-25_
- desc: encapsulation of a task so that we cannot for example wait on them
- L15 _public prototype_ `bool IsCompleted() const;`
- L16 _public prototype_ `bool IsValid() const;`
- L20 _public prototype_ `void Wait() = delete;` — Explicitly delete the wait method to avoid future implementer to add it Dtaaflow Tasks should not be awaited and should be listen to using a completion callback/task instead
- L24 _private member_ `UE::Tasks::FTask Task;`

#### struct `UE::Dataflow::FTaskGraph`  
`struct FTaskGraph`  
_L27-76_
- L30 _public prototype_ `FTaskGraph();`
- L31 _public prototype_ `~FTaskGraph();`
- L33 _public typedef_ `using FCancellationTokenPtr = TSharedPtr<UE::Tasks::FCancellationToken>;`
- L39 _public prototype_ `FTask LaunchGameThreadTask(const TCHAR* DebugName, TUniqueFunction<void()>&& TaskBody, const TArray<FTask>& Prerequisites, FCancellationTokenPtr CancellationToken = {});` — Launch a task to run on the game thread Execution will happen during the next execution of tick method of the taskgraph when all dependent tasks have be completed
- L44 _public prototype_ `FTask LaunchAnyThreadTask(const TCHAR* DebugName, TUniqueFunction<void()>&& TaskBody, const TArray<FTask>& Prerequisites, FCancellationTokenPtr CancellationToken = {});` — Launch a task to run on any thread
- L68 _private typedef_ `using FGameThreadTaskRef = TSharedRef<FGameThreadTask>;`
- L70 _private member_ `FTSTicker::FDelegateHandle TickDelegateHandle;`
- L71 _private prototype_ `bool OnTick(float DeltaTime);`
- L73 _private member_ `TArray<FGameThreadTaskRef> GameThreadTasks;`

#### struct `UE::Dataflow::FTaskGraph::FGameThreadTask`  
`struct FGameThreadTask`  
_L47-67_
- L50 _public member_ `const TCHAR* DebugName = TEXT("Dat` — Debug name of the task
- L53 _public member_ `TUniqueFunction<void()> TaskBody;` — Function to execute when running the task
- L56 _public member_ `TArray<FTask> Prerequisites;` — List of pPrerequisites
- L59 _public member_ `FCancellationTokenPtr CancellationToken;` — optional cancellation token
- L62 _public member_ `UE::Tasks::FTaskEvent CompletionTaskEvent;` — Task event that completes when the body has executed
- L64 _public prototype_ `bool CanExecute() const;`
- L65 _public prototype_ `bool IsCancelled() const;`
- L66 _public prototype_ `bool TryExecute();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Dataflow` (scope `UE`)

### `Source/Runtime/Dataflow/Core/Private/Dataflow/DataflowVectorNodes.h` (Private)


#### struct `FDataflowVectorMakeVec2Node`  
`struct FDataflowVectorMakeVec2Node : public FDataflowNode`  
_L13-35_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a 2D Vector
- L24 _private member_ `FDataflowNumericTypes X;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — X component
- L28 _private member_ `FDataflowNumericTypes Y;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — Y component
- L32 _private member_ `FDataflowVectorTypes Vector2D;` — `UPROPERTY(meta = (DataflowOutput))` — 2D Vector {X, Y}
- L34 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowVectorMakeVec3Node`  
`struct FDataflowVectorMakeVec3Node : public FDataflowNode`  
_L39-65_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a 3D Vector
- L45 _public prototype_ `FDataflowVectorMakeVec3Node(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L50 _private member_ `FDataflowNumericTypes X;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — X component
- L54 _private member_ `FDataflowNumericTypes Y;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — Y component
- L58 _private member_ `FDataflowNumericTypes Z;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — Z component
- L62 _private member_ `FDataflowVectorTypes Vector3D;` — `UPROPERTY(meta = (DataflowOutput))` — 3D Vector {X, Y, Z}
- L64 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowVectorMakeVec4Node`  
`struct FDataflowVectorMakeVec4Node : public FDataflowNode`  
_L70-100_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Make a 4D Vector
- L76 _public prototype_ `FDataflowVectorMakeVec4Node(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L81 _private member_ `FDataflowNumericTypes X;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — X component
- L85 _private member_ `FDataflowNumericTypes Y;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — Y component
- L89 _private member_ `FDataflowNumericTypes Z;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — Z component
- L93 _private member_ `FDataflowNumericTypes W;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — W component
- L97 _private member_ `FDataflowVectorTypes Vector4D;` — `UPROPERTY(meta = (DataflowOutput))` — 4D Vector {X, Y, Z, W}
- L99 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowVectorBreakNode`  
`struct FDataflowVectorBreakNode: public FDataflowNode`  
_L108-138_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Break a vector in 4 components if the input vector is of a lower dimension than 4, the remaining components will be set to zero
- L114 _public prototype_ `FDataflowVectorBreakNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L119 _private member_ `FDataflowVectorTypes V;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — Vector to break into components
- L123 _private member_ `FDataflowNumericTypes X;` — `UPROPERTY(meta = (DataflowOutput))` — X component
- L127 _private member_ `FDataflowNumericTypes Y;` — `UPROPERTY(meta = (DataflowOutput))` — Y component
- L131 _private member_ `FDataflowNumericTypes Z;` — `UPROPERTY(meta = (DataflowOutput))` — Z component
- L135 _private member_ `FDataflowNumericTypes W;` — `UPROPERTY(meta = (DataflowOutput))` — W component
- L137 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowVectorAddNode`  
`struct FDataflowVectorAddNode : public FDataflowNode`  
_L142-164_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Add two vectors component wise : V = (A + B)
- L148 _public prototype_ `FDataflowVectorAddNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L153 _private member_ `FDataflowVectorTypes A;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — A Vector operand
- L157 _private member_ `FDataflowVectorTypes B;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — B Vector operand
- L161 _private member_ `FDataflowVectorTypes V;` — `UPROPERTY(meta = (DataflowOutput))` — Add result V=A+B
- L163 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowVectorSubtractNode`  
`struct FDataflowVectorSubtractNode : public FDataflowNode`  
_L168-190_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Subtract two vectors component wise: V = (A - B)
- L174 _public prototype_ `FDataflowVectorSubtractNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L179 _private member_ `FDataflowVectorTypes A;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — A Vector operand
- L183 _private member_ `FDataflowVectorTypes B;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — B Vector operand
- L187 _private member_ `FDataflowVectorTypes V;` — `UPROPERTY(meta = (DataflowOutput))` — Add result V=A-B
- L189 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowVectorMultiplyNode`  
`struct FDataflowVectorMultiplyNode : public FDataflowNode`  
_L194-216_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Multiply two vectors component wise: V = (A * B)
- L200 _public prototype_ `FDataflowVectorMultiplyNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L205 _private member_ `FDataflowVectorTypes A;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — A Vector operand
- L209 _private member_ `FDataflowVectorTypes B;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — B Vector operand
- L213 _private member_ `FDataflowVectorTypes V;` — `UPROPERTY(meta = (DataflowOutput))` — Add result V=A*B
- L215 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowVectorDivideNode`  
`struct FDataflowVectorDivideNode : public FDataflowNode`  
_L223-249_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Multiply two vectors component wise: V = (A / B) When a component of B is zero, use the falback value as a return value for the specific component
- L229 _public prototype_ `FDataflowVectorDivideNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L234 _private member_ `FDataflowVectorTypes A;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — A Vector operand
- L238 _private member_ `FDataflowVectorTypes B;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — B Vector operand
- L242 _private member_ `FDataflowVectorTypes Fallback;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — Fallback Vector used when components of B are zero
- L246 _private member_ `FDataflowVectorTypes V;` — `UPROPERTY(meta = (DataflowOutput))` — Add result V=A*B
- L248 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowVectorDotProductNode`  
`struct FDataflowVectorDotProductNode : public FDataflowNode`  
_L253-275_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Compute the dot product between two vectors : DotProduct = A.B
- L259 _public prototype_ `FDataflowVectorDotProductNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L264 _private member_ `FDataflowVectorTypes A;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — A Vector operand
- L268 _private member_ `FDataflowVectorTypes B;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — B Vector operand
- L272 _private member_ `FDataflowNumericTypes DotProduct;` — `UPROPERTY(meta = (DataflowOutput))` — Resulting dot product : DotProduct=A.B
- L274 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowVectorLengthNode`  
`struct FDataflowVectorLengthNode : public FDataflowNode`  
_L279-297_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Compute the Length of a vector : Length = |V|
- L285 _public prototype_ `FDataflowVectorLengthNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L290 _private member_ `FDataflowVectorTypes V;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — Vector to get length from
- L294 _private member_ `FDataflowNumericTypes Length;` — `UPROPERTY(meta = (DataflowOutput))` — Length of the input vector : Length=|V|
- L296 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowVectorSquaredLengthNode`  
`struct FDataflowVectorSquaredLengthNode : public FDataflowNode`  
_L301-319_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Compute the Squared length of a vector : Length = |V||V|
- L307 _public prototype_ `FDataflowVectorSquaredLengthNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L312 _private member_ `FDataflowVectorTypes V;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — Vector to get squared length from
- L316 _private member_ `FDataflowNumericTypes SquaredLength;` — `UPROPERTY(meta = (DataflowOutput))` — Length of the input vector : SquaredLength = |V||V|
- L318 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowVectorDistanceNode`  
`struct FDataflowVectorDistanceNode : public FDataflowNode`  
_L323-345_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Compute the distance between two vectors : Distance = |B-A|
- L329 _public prototype_ `FDataflowVectorDistanceNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L334 _private member_ `FDataflowVectorTypes A;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — A Vector operand
- L338 _private member_ `FDataflowVectorTypes B;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — B Vector operand
- L342 _private member_ `FDataflowNumericTypes Distance;` — `UPROPERTY(meta = (DataflowOutput))` — Distance between A and B : Distance=|B-A|
- L344 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowVectorCrossProductNode`  
`struct FDataflowVectorCrossProductNode : public FDataflowNode`  
_L352-374_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Compute the cross product of two vectors :  CrossProduct = B^A This node only operates in 3 dimensions, inputs will be converted to a 3D vector internally and result will be a vector with a zero W component
- L358 _public prototype_ `FDataflowVectorCrossProductNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L363 _private member_ `FDataflowVectorTypes A;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — A Vector operand
- L367 _private member_ `FDataflowVectorTypes B;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — B Vector operand
- L371 _private member_ `FDataflowVectorTypes CrossProduct;` — `UPROPERTY(meta = (DataflowOutput))` — Resulting cross product of A and B : CrossProduct=B^A
- L373 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowVectorScaleNode`  
`struct FDataflowVectorScaleNode : public FDataflowNode`  
_L378-400_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Scale a vector by a scalar : Scaled = (V * Scale)
- L384 _public prototype_ `FDataflowVectorScaleNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L389 _private member_ `FDataflowVectorTypes V;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — Vector to scale
- L393 _private member_ `FDataflowNumericTypes Scale;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — Scale factor
- L397 _private member_ `FDataflowVectorTypes Scaled;` — `UPROPERTY(meta = (DataflowOutput))` — Scaled vector : Scaled=(V * Scale)
- L399 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowVectorNormalize`  
`struct FDataflowVectorNormalize : public FDataflowNode`  
_L404-422_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Normalize a vector : Normalized = V/|V|
- L410 _public prototype_ `FDataflowVectorNormalize(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L415 _private member_ `FDataflowVectorTypes V;` — `UPROPERTY(EditAnywhere, Category = Operands, meta = (DataflowInput))` — Vector to normalize
- L419 _private member_ `FDataflowVectorTypes Normalized;` — `UPROPERTY(meta = (DataflowOutput))` — Normalized vector : Normalized=V/|V|
- L421 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define DATAFLOW_MATH_VECTOR_NODES_CATEGORY "Math|Vectors"`
- L424 _namespace_ `namespace UE`
- L424 _namespace_ `namespace Dataflow` (scope `UE`)
- L426 _prototype_ `void RegisterDataflowVectorNodes();` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowAnyType.h` (Public)


#### struct `FDataflowAnyType`  
`struct FDataflowAnyType`  
_L13-20_
- reflection: `USTRUCT()`
- desc: Any supported type
- L15 _public typedef_ `using FPolicyType = FDataflowAllTypesPolicy;`
- L16 _public typedef_ `using FStorageType = void;`
- L19 _public member_ `static const FName TypeName;`

#### struct `FDataflowAllTypes`  
`struct FDataflowAllTypes : public FDataflowAnyType`  
_L24-29_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: Any supported type
- L26 _public typedef_ `using FPolicyType = FDataflowAllTypesPolicy;`
- L27 _public typedef_ `using FStorageType = void;`

#### struct `FDataflowArrayTypes`  
`struct FDataflowArrayTypes : public FDataflowAnyType`  
_L34-39_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: Generic Array types
- L36 _public typedef_ `using FPolicyType = FDataflowArrayTypePolicy;`
- L37 _public typedef_ `using FStorageType = void;`

#### struct `FDataflowUStructTypes`  
`struct FDataflowUStructTypes : public FDataflowAnyType`  
_L43-48_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: UStruct based types
- L45 _public typedef_ `using FPolicyType = FDataflowUStructTypePolicy;`
- L46 _public typedef_ `using FStorageType = void;`

#### enum `EDataflowNumericType`  
`enum class EDataflowNumericType : uint8`  
_L51-63_
- reflection: `UENUM()`
- L53 _public enumerator_ `Double UMETA(DisplayName = "double")`
- L54 _public enumerator_ `Float UMETA(DisplayName = "float")`
- L55 _public enumerator_ `Int64 UMETA(DisplayName = "int64")`
- L56 _public enumerator_ `UInt64 UMETA(DisplayName = "uint64")`
- L57 _public enumerator_ `Int32 UMETA(DisplayName = "int32")`
- L58 _public enumerator_ `UInt32 UMETA(DisplayName = "uint32")`
- L59 _public enumerator_ `Int16 UMETA(DisplayName = "int16")`
- L60 _public enumerator_ `UInt16 UMETA(DisplayName = "uint16")`
- L61 _public enumerator_ `Int8 UMETA(DisplayName = "int8")`
- L62 _public enumerator_ `UInt8 UMETA(DisplayName = "uint8")`

#### struct `FDataflowNumericTypes`  
`struct FDataflowNumericTypes : public FDataflowAnyType`  
_L70-79_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: Numeric types (double, float, int64, uint64, int32, uint32, int16, uint16, int8, uint8)"
- L72 _public typedef_ `using FPolicyType = FDataflowNumericTypePolicy;`
- L73 _public typedef_ `using FStorageType = double;`
- L78 _public member_ `double Value = 0.0;` — `UPROPERTY(EditAnywhere, Category=Value)`

#### struct `FDataflowVectorTypes`  
`struct FDataflowVectorTypes : public FDataflowAnyType`  
_L86-95_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: Vector types (2D, 3D and 4D vector, single and double precision)
- L88 _public typedef_ `using FPolicyType = FDataflowVectorTypePolicy;`
- L89 _public typedef_ `using FStorageType = FVector4;`
- L94 _public member_ `FVector4 Value = FVector4(0, 0, 0, 0);` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FDataflowStringTypes`  
`struct FDataflowStringTypes : public FDataflowAnyType`  
_L99-108_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: String types (FString or FName or FText)
- L101 _public typedef_ `using FPolicyType = FDataflowStringTypePolicy;`
- L102 _public typedef_ `using FStorageType = FString;`
- L107 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FDataflowBoolTypes`  
`struct FDataflowBoolTypes : public FDataflowAnyType`  
_L112-121_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: Bool types
- L114 _public typedef_ `using FPolicyType = TDataflowSingleTypePolicy<bool>;`
- L115 _public typedef_ `using FStorageType = bool;`
- L120 _public member_ `bool Value = true;` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FDataflowTransformTypes`  
`struct FDataflowTransformTypes : public FDataflowAnyType`  
_L125-134_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: Transform types
- L127 _public typedef_ `using FPolicyType = TDataflowSingleTypePolicy<FTransform>;`
- L128 _public typedef_ `using FStorageType = FTransform;`
- L133 _public member_ `FTransform Value = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FDataflowStringConvertibleTypes`  
`struct FDataflowStringConvertibleTypes : public FDataflowAnyType`  
_L141-150_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: String convertible types (String types, Numeric types, Vector types and Booleans)
- L143 _public typedef_ `using FPolicyType = FDataflowStringConvertibleTypePolicy;`
- L144 _public typedef_ `using FStorageType = FString;`
- L149 _public member_ `FString Value;` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FDataflowUObjectConvertibleTypes`  
`struct FDataflowUObjectConvertibleTypes : public FDataflowAnyType`  
_L154-163_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: UObject types
- L156 _public typedef_ `using FPolicyType = FDataflowUObjectConvertibleTypePolicy;`
- L157 _public typedef_ `using FStorageType = TObjectPtr<UObject>;`
- L162 _public member_ `TObjectPtr<UObject> Value = nullptr;` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FDataflowSelectionTypes`  
`struct FDataflowSelectionTypes : public FDataflowAnyType`  
_L167-176_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: Selection types
- L169 _public typedef_ `using FPolicyType = FDataflowSelectionTypePolicy;`
- L170 _public typedef_ `using FStorageType = FDataflowSelection;`
- L175 _public member_ `FDataflowSelection Value;` — `UPROPERTY()`

#### struct `FDataflowVectorArrayTypes`  
`struct FDataflowVectorArrayTypes : public FDataflowAnyType`  
_L180-189_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: Vector array types
- L182 _public typedef_ `using FPolicyType = FDataflowVectorArrayPolicy;`
- L183 _public typedef_ `using FStorageType = TArray<FVector4>;`
- L188 _public member_ `TArray<FVector4> Value;` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FDataflowNumericArrayTypes`  
`struct FDataflowNumericArrayTypes : public FDataflowAnyType`  
_L193-202_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: Numeric array types
- L195 _public typedef_ `using FPolicyType = FDataflowNumericArrayPolicy;`
- L196 _public typedef_ `using FStorageType = TArray<double>;`
- L201 _public member_ `TArray<double> Value;` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FDataflowStringArrayTypes`  
`struct FDataflowStringArrayTypes : public FDataflowAnyType`  
_L206-215_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: String array types
- L208 _public typedef_ `using FPolicyType = FDataflowStringArrayPolicy;`
- L209 _public typedef_ `using FStorageType = TArray<FString>;`
- L214 _public member_ `TArray<FString> Value;` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FDataflowBoolArrayTypes`  
`struct FDataflowBoolArrayTypes : public FDataflowAnyType`  
_L219-228_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: Bool array types
- L221 _public typedef_ `using FPolicyType = TDataflowSingleTypePolicy<TArray<bool>>;`
- L222 _public typedef_ `using FStorageType = TArray<bool>;`
- L227 _public member_ `TArray<bool> Value;` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FDataflowTransformArrayTypes`  
`struct FDataflowTransformArrayTypes : public FDataflowAnyType`  
_L232-241_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: Transform array types
- L234 _public typedef_ `using FPolicyType = TDataflowSingleTypePolicy<TArray<FTransform>>;`
- L235 _public typedef_ `using FStorageType = TArray<FTransform>;`
- L240 _public member_ `TArray<FTransform> Value;` — `UPROPERTY(EditAnywhere, Category = Value)`

#### struct `FDataflowRotationTypes`  
`struct FDataflowRotationTypes : public FDataflowAnyType`  
_L245-254_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: Rotation types
- L247 _public typedef_ `using FPolicyType = FDataflowRotationTypePolicy;`
- L248 _public typedef_ `using FStorageType = FRotator;`
- L253 _public member_ `FRotator Value = FRotator(EForceInit::ForceInitToZero);` — `UPROPERTY()`

#### struct `FDataflowMeshSelectionTypes`  
`struct FDataflowMeshSelectionTypes : public FDataflowAnyType`  
_L258-267_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- desc: Mesh Selection types
- L260 _public typedef_ `using FPolicyType = FDataflowMeshSelectionTypePolicy;`
- L261 _public typedef_ `using FStorageType = FDataflowSelection;`
- L266 _public member_ `FDataflowSelection Value;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L269 _namespace_ `namespace UE`
- L269 _namespace_ `namespace Dataflow` (scope `UE`)
- L271 _prototype_ `bool AreTypesCompatible(FName TypeA, FName TypeB);` (scope `UE::Dataflow`)
- L273 _prototype_ `void RegisterAnyTypes();` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowAnyTypeRegistry.h` (Public)


#### struct `UE::Dataflow::FAnyTypesRegistry`  
`struct FAnyTypesRegistry`  
_L11-69_
- L14 _public typedef_ `using FTypeFilterFunction = TFunction<bool(FName, FName)>;`
- L17 _public function_ `template<typename T> static void RegisterTypeStatic(FName TypeName)`
- L21 _public prototype_ `static bool AreTypesCompatibleStatic(FName TypeA, FName TypeB);`
- L22 _public prototype_ `static FName GetStorageTypeStatic(FName Type);`
- L24 _public prototype_ `static void RegisterAutoConvertNodeTypeStatic(FName FromType, FName ToType, FName AutoConvertNode, FTypeFilterFunction TypeFilterFunction = {});`
- L25 _public prototype_ `static FName GetAutoConvertNodeTypeStatic(FName FromType, FName ToType);`
- L27 _public prototype_ `static bool IsAnyTypeStatic(FName Type);`
- L28 _public prototype_ `static FAnyTypesRegistry& GetInstance();`
- L31 _private typedef_ `typedef bool(*FSupportTypeFunction)(FName);`
- L47 _private function_ `FAnyTypesRegistry()`
- L50 _private function_ `template<typename T> void RegisterType(FName TypeName)`
- L60 _private prototype_ `void RegisterAutoConvertNodeType(FName FromType, FName ToType, FName AutoConvertNode, FTypeFilterFunction TypeFilterFunction);`
- L62 _private prototype_ `bool AreTypesCompatible(FName TypeA, FName TypeB) const;`
- L63 _private prototype_ `FName GetStorageType(FName Type) const;`
- L64 _private prototype_ `FName GetAutoConvertNodeType(FName FromType, FName ToType) const;`
- L65 _private prototype_ `bool IsAnyType(FName Type) const;`
- L67 _private member_ `TMap<FName, FTypeInfo> TypeInfosByName;`
- L68 _private member_ `TArray<FAutoConvertNodeInfo> AutoConvertNodes;`

#### struct `UE::Dataflow::FAnyTypesRegistry::FTypeInfo`  
`struct FTypeInfo`  
_L33-37_
- L35 _public member_ `FSupportTypeFunction SupportTypeFunction = nullptr;`
- L36 _public member_ `FName StorageType;`

#### struct `UE::Dataflow::FAnyTypesRegistry::FAutoConvertNodeInfo`  
`struct FAutoConvertNodeInfo`  
_L39-45_
- L41 _public member_ `FName FromType;`
- L42 _public member_ `FName ToType;`
- L43 _public member_ `FName AutoConvertNode;`
- L44 _public member_ `FTypeFilterFunction TypeFilterFunction;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Dataflow` (scope `UE`)
- L72 _macro_ `#define UE_DATAFLOW_REGISTER_ANYTYPE(Type) UE::Dataflow::FAnyTypesRegistry::RegisterTypeStatic<Type>(#Type)`
- L73 _macro_ `#define UE_DATAFLOW_REGISTER_AUTOCONVERT(FromType, ToType, NodeType) UE::Dataflow::FAnyTypesRegistry::RegisterAutoConvertNodeTypeStatic(#FromType, #ToType, #NodeType)`
- L74 _macro_ `#define UE_DATAFLOW_REGISTER_AUTOCONVERT_WITH_FILTER(FromType, ToType, NodeType, FilterFunc) UE::Dataflow::FAnyTypesRegistry::RegisterAutoConvertNodeTypeStatic(#FromType, #ToType, #NodeType, FilterFunc)`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowArchive.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define DATAFLOW_OPTIONAL_BLOCK_WRITE_BEGIN(){\` — The following code serializes the size of the PropertyData to serialize so that when loading, we can skip over it if the function could not be loaded. Serialize a temporary value for the delta in order to end up with an archive of the right size. Then serialize the PropertyData in order to get its size.
- L19 _macro_ `#define DATAFLOW_OPTIONAL_BLOCK_WRITE_END()\` — Only go back and serialize the number of argument bytes if there is actually an underlying buffer to seek to. Come back to the temporary value we wrote and overwrite it with the PropertyData size we just calculated. And finally seek back to the end.
- L31 _macro_ `#define DATAFLOW_OPTIONAL_BLOCK_READ_BEGIN(COND) \`
- L37 _macro_ `#define DATAFLOW_OPTIONAL_BLOCK_READ_ELSE() \`
- L41 _macro_ `#define DATAFLOW_OPTIONAL_BLOCK_READ_END() }}`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowCategoryRegistry.h` (Public)


#### struct `UE::Dataflow::FCategoryRegistry`  
`struct FCategoryRegistry`  
_L13-30_
- desc: registry for categories This is used for node in editor filtering
- L16 _public prototype_ `static FCategoryRegistry& Get();`
- L17 _public prototype_ `static void TearDown();`
- L19 _public typedef_ `using FCategoryName = FName;`
- L20 _public typedef_ `using FAssetType = FName;`
- L23 _public prototype_ `void RegisterCategoryForAssetType(const FCategoryName Category, const FAssetType AssetType);` — register a category name for a specific type of asset
- L24 _public prototype_ `bool IsCategoryForAssetType(const FCategoryName Category, const FAssetType AssetType) const;`
- L27 _private member_ `TMap<FCategoryName, TArray<FAssetType>> AssetTypesByCategory;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Dataflow` (scope `UE`)
- L33 _macro_ `#define UE_DATAFLOW_REGISTER_CATEGORY_FORASSET_TYPE(CATEGORY_NAME, ASSET_TYPE) \`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowCompiledGraph.h` (Public)


#### struct `UE::Dataflow::FCompiledGraph`  
`struct FCompiledGraph`  
_L27-129_
- desc: This structure stores a compiled graph A compiled graph allow a dataflow evaluator to evaluate a graph efficiently without having to parse the graph again Reference to nodes are sorted by tasks in order of execution and dependency Making it easy to spawn actual async task from for example The data is also organized in arrays of fixed sized structure for faster cache access and limited allocation Note that a compiled graph is associated to a specific main or sub graph Todo(dataflow) : A compiled graph do not yet provide any information about branching and conditional, this will be added in the near future
- L30 _public prototype_ `FCompiledGraph(TSharedRef<const FGraph> InSourceGraph);`
- L32 _public prototype_ `int32 StartTask();`
- L41 _public prototype_ `void AddNode(FGuid NodeId, TConstArrayView<FGuid> UpstreamNodeIds = {}, bool bIsTerminal = false);` — Add a node to the current task. UpstreamNodeIds : nodes whose outputs feed this node's inputs. Must already have been added to the compiled graph (topological order is preserved by the compiler). bIsTerminal    : true if Node->IsTerminal() — cached here so evaluators can enumerate terminals without walking the source FGraph.
- L43 _public prototype_ `void AddDependency(int32 TaskId);`
- L44 _public prototype_ `void EndTask();`
- L46 _public prototype_ `int32 GetNumNodes() const;`
- L47 _public prototype_ `FGuid GetNextNodeId(int32 NodeIndex) const;`
- L50 _public prototype_ `FGuid GetNodeId(int32 NodeIndex) const;` — O(1) lookup of a node's id by its index in the compiled graph. Returns invalid FGuid for out-of-range.
- L56 _public prototype_ `int32 FindNodeIndex(const FGuid& NodeId) const;` — O(1) lookup of a node's index in the compiled graph by its FGuid. Returns INDEX_NONE if the node is not part of this compiled graph.
- L59 _public prototype_ `TConstArrayView<int32> GetUpstreamNodeIndices(int32 NodeIndex) const;` — Indices (into Nodes) of nodes whose outputs feed the given node. Empty for source nodes.
- L62 _public prototype_ `TConstArrayView<int32> GetTerminalNodeIndices() const;` — Indices of all terminal nodes (nodes with IsTerminal() == true) in the compiled graph.
- L64 _public prototype_ `int32 GetNumTasks() const;`
- L65 _public prototype_ `void GetTasksNodesAndDependencies(int32 TaskId, TArray<FGuid>& OutNodeIds, TArray<int32>& OutParentTaskIds) const;`
- L67 _public prototype_ `TSharedRef<const FGraph> GetSourceGraph() const;`
- L111 _private member_ `TArray<FTask> Tasks;` — List of tasks (index into the command buffer array)
- L114 _private member_ `TArray<FNode> Nodes;` — List of nodes (with back reference to the task array)
- L117 _private member_ `TMap<FGuid, int32> NodeIdToIndex;` — O(1) lookup table mapping a node's FGuid to its index in Nodes.
- L120 _private member_ `TArray<int32> UpstreamEdgesFlat;` — CSR storage of upstream-node-index edges for every node. Indexed via FNode::UpstreamEdgeStart/Count.
- L123 _private member_ `TArray<int32> TerminalNodeIndices;` — Pre-baked list of terminal node indices, populated at compile time from Node->IsTerminal().
- L126 _private member_ `TArray<FCommand> Commands;` — List of commands (with reference to the task and node arrays)
- L128 _private member_ `TSharedRef<const FGraph> SourceGraph;`

#### enum `UE::Dataflow::FCompiledGraph::ECommandType`  
`enum class ECommandType`  
_L70-75_
- L72 _public enumerator_ `AddNode` — Parameter is an index into a node array
- L73 _public enumerator_ `AddDependency` — Parameter is an index into a task array
- L74 _public enumerator_ `LaunchTask` — Parameter is an index into a task array

#### struct `UE::Dataflow::FCompiledGraph::FTask`  
`struct FTask`  
_L77-84_
- L80 _public member_ `int32 CommandIndex = INDEX_NONE;` — Index into the command buffer ( Start of the task )
- L83 _public member_ `int32 NumCommands = 0;` — Number of commands for this task

#### struct `UE::Dataflow::FCompiledGraph::FNode`  
`struct FNode`  
_L86-99_
- L89 _public member_ `FGuid NodeId;` — Guid uniquely identifying a node in the graph
- L92 _public member_ `int32 TaskIndex = INDEX_NONE;` — index of the task in the task array
- L95 _public member_ `int32 UpstreamEdgeStart = 0;` — CSR offset into UpstreamEdgesFlat for this node's upstream edges.
- L98 _public member_ `int32 UpstreamEdgeCount = 0;` — Number of upstream edges for this node.

#### struct `UE::Dataflow::FCompiledGraph::FCommand`  
`struct FCommand`  
_L101-108_
- L104 _public member_ `ECommandType Type = ECommandType::LaunchTask;` — Type of the command (see ECommandType)
- L107 _public member_ `int32 Parameter = 0;` — Parameter of the command (an index if the task or node array)

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Dataflow` (scope `UE`)

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowConnection.h` (Public)


#### struct `UE::Dataflow::FPin`  
`struct FPin`  
_L27-45_
- L34 _public member_ `EDirection Direction;`
- L35 _public member_ `FName Type;`
- L36 _public member_ `FName Name;`
- L37 _public member_ `bool bHidden = false;`
- L39 _public function_ `bool operator==(const FPin& Other) const`
- L44 _public member_ `static const FPin InvalidPin;`

#### enum `UE::Dataflow::FPin::EDirection`  
`enum class EDirection : uint8`  
_L29-33_
- L30 _public enumerator_ `NONE = 0`
- L31 _public enumerator_ `INPUT`
- L32 _public enumerator_ `OUTPUT`

#### struct `UE::Dataflow::FConnectionParameters`  
`struct FConnectionParameters`  
_L47-64_
- L49 _public function_ `FConnectionParameters(FName InType = FName(), FName InName = FName(), FDataflowNode* InOwner = nullptr, const FProperty* InProperty = nullptr, uint32 InOffset = INDEX_NONE, FGuid InGuid = FGuid::NewGuid()) : Type(InType) , Name(InName) , Owner(InOwner) , Property(InProperty) , Offset(InOffset) , Guid(InGuid)`
- L58 _public member_ `FName Type;`
- L59 _public member_ `FName Name;`
- L60 _public member_ `FDataflowNode* Owner = nullptr;`
- L61 _public member_ `const FProperty* Property = nullptr;`
- L62 _public member_ `uint32 Offset = INDEX_NONE;`
- L63 _public member_ `FGuid Guid;`

#### struct `UE::Dataflow::FConnectionReference`  
`struct FConnectionReference`  
_L69-80_
- desc: Do not hold onto FConnectionReference when Reference is dynamically allocated (e.g., when using array inputs). Use FConnectionKey instead.
- L71 _public member_ `const void* Reference;`
- L72 _public member_ `int32 Index = INDEX_NONE;`
- L73 _public member_ `const void* ContainerReference = nullptr;`
- L75 _public function_ `FConnectionReference(const void* InReference, int32 InIndex = INDEX_NONE, const void* InContainerReference = nullptr) : Reference(InReference) , Index(InIndex) , ContainerReference(InContainerReference)`

#### struct `UE::Dataflow::TConnectionReference`  
`template<typename T> struct TConnectionReference : public FConnectionReference`  
_L83-88_
- inherits: `FConnectionReference`
- L85 _public function_ `TConnectionReference(const T* InReference, int32 InIndex = INDEX_NONE, const void* InContainerReference = nullptr) : FConnectionReference(InReference, InIndex, InContainerReference)`

#### class `UE::Dataflow::FConnectionKey`  
`class FConnectionKey`  
_L90-121_
- L93 _public prototype_ `FConnectionKey() = default;`
- L95 _public function_ `bool operator==(const FConnectionKey& Other) const`
- L105 _public member_ `static const FConnectionKey Invalid;`
- L112 _private function_ `FConnectionKey(uint32 InOffset, int32 InContainerIndex, uint32 InContainerElementOffset) : Offset(InOffset) , ContainerIndex(InContainerIndex) , ContainerElementOffset(InContainerElementOffset)`
- L118 _private member_ `uint32 Offset = INDEX_NONE;`
- L119 _private member_ `int32 ContainerIndex = INDEX_NONE;`
- L120 _private member_ `uint32 ContainerElementOffset = INDEX_NONE;`

#### struct `FDataflowConnection`  
`struct FDataflowConnection`  
_L130-315_
- reflection: `USTRUCT()`
- desc: Input Output Base
- L135 _protected member_ `FDataflowNode* OwningNode = nullptr;`
- L136 _protected member_ `const FProperty* Property = nullptr;`
- L137 _protected member_ `FGuid Guid;`
- L138 _protected member_ `IDataflowTypePolicy* TypePolicy = nullptr;`
- L139 _protected member_ `uint32 Offset;`
- L140 _protected member_ `UE::Dataflow::FPin::EDirection Direction;`
- L141 _protected member_ `bool bIsAnyType:1 = false;`
- L142 _protected member_ `bool bHasConcreteType : 1 = false;`
- L143 _protected member_ `bool bCanHidePin:1 = false;`
- L144 _protected member_ `bool bPinIsHidden:1 = false;`
- L147 _private member_ `FName OriginalType;`
- L148 _private member_ `FName Type;`
- L149 _private member_ `FName Name;`
- L152 _private member_ `bool bLockType:1 = false;` — Lock the type from being changed
- L157 _private member_ `FName TypeDependencyGroup;` — Name of the group dependecy the connection is part of This applies to anytype connections All other connection with the same group will inherit type from each other
- L163 _protected prototype_ `void SetTypeInternal(FName NewType);`
- L165 _protected prototype_ `bool IsOwningNodeEnabled() const;`
- L168 _protected prototype_ `void SetAsAnyType(bool bAnyType, const FName& ConcreteType);` — this should only be used for serialization
- L171 _protected prototype_ `void ForceSimpleType(FName InType);` — this should only be used for serialization - for support of old simple TArray types
- L172 _protected prototype_ `void FixAndPropagateType();`
- L173 _protected function_ `virtual void FixAndPropagateType(FName InType)`
- L179 _protected prototype_ `bool IsExtendedType(FName InType) const;` — returns true is the parameter type is an extension of the current type TArray<int> from TArray for example
- L187 _protected prototype_ `bool ResetToOriginalType();` — reset the output to its original type no-op for non enytypes types Anytypes connection will fail if it is already connected or has connected type dependencies @return true if the change was made
- L190 _protected prototype_ `void Rename(FName NewName);` — Rename the connection
- L192 _protected prototype_ `void ForceTypeDependencyGroup(FName InTypeDependencyGroup);`
- L195 _public function_ `FDataflowConnection()`
- L196 _public prototype_ `FDataflowConnection(UE::Dataflow::FPin::EDirection Direction, const UE::Dataflow::FConnectionParameters& Params);`
- L197 _public prototype_ `virtual ~FDataflowConnection() = default;`
- L199 _public function_ `FDataflowNode* GetOwningNode()`
- L200 _public function_ `const FDataflowNode* GetOwningNode() const`
- L202 _public prototype_ `FGuid GetOwningNodeGuid() const;`
- L203 _public prototype_ `uint32 GetOwningNodeValueHash() const;`
- L204 _public prototype_ `UE::Dataflow::FTimestamp GetOwningNodeTimestamp() const;`
- L206 _public function_ `const FProperty* GetProperty() const`
- L208 _public prototype_ `FString GetPropertyTooltip() const;`
- L209 _public prototype_ `FString GetPropertyTypeNameTooltip() const;`
- L211 _public function_ `UE::Dataflow::FPin::EDirection GetDirection() const`
- L212 _public function_ `uint32 GetOffset() const`
- L213 _public function_ `virtual int32 GetContainerIndex() const`
- L214 _public function_ `virtual uint32 GetContainerElementOffset() const`
- L215 _public function_ `UE::Dataflow::FConnectionKey GetConnectionKey() const`
- L230 _public prototype_ `bool SetConcreteType(FName InType);` — Set the concrete type of an anytype connection Changing the type may fail or assert if : - the connection is connected to another one, - the type is incompatible with the original type - the type has any type dependencies connected - the type is locked ( see LockType() ) (see IsSafeToTryChangingType) @return true if the type was effectivelly changed
- L232 _public function_ `void LockType()`
- L233 _public function_ `void UnlockType()`
- L234 _public function_ `bool IsTypeLocked() const`
- L236 _public function_ `FName GetType() const`
- L237 _public function_ `FName GetOriginalType() const`
- L240 _public function_ `template <typename T> bool IsType() const`
- L245 _public function_ `FGuid GetGuid() const`
- L246 _public function_ `void SetGuid(FGuid InGuid)`
- L248 _public function_ `FName GetName() const`
- L249 _public function_ `void SetName(FName InName)`
- L251 _public function_ `virtual void* RealAddress() const`
- L252 _public function_ `UE::Dataflow::FContextCacheKey CacheKey() const`
- L260 _public prototype_ `bool IsSafeToTryChangingType() const;` — check is this connection can chage type case where it cannot are : it is already connected it has copnnected type dependencies
- L262 _public function_ `virtual bool IsConnected() const`
- L263 _public function_ `virtual bool AddConnection(FDataflowConnection* In)`
- L264 _public function_ `virtual bool RemoveConnection(FDataflowConnection* In)`
- L265 _public function_ `virtual void GetConnections(TArray<FDataflowConnection*>& OutConnections) const`
- L267 _public function_ `bool IsAnyType() const`
- L268 _public prototype_ `static bool IsAnyType(const FName& InType);`
- L269 _public function_ `bool HasConcreteType() const`
- L270 _public prototype_ `void SetTypePolicy(IDataflowTypePolicy* InTypePolicy);`
- L271 _public prototype_ `bool SupportsType(FName InType) const;`
- L277 _public prototype_ `void GetSupportedTypes(TArray<FName>& OutSupportedTypes) const;` — return the short list of supported types if the type of the connection is a broad anytype and that the list of supported type is not finite, then nothing is returned
- L280 _public prototype_ `FDataflowConnection& SetTypeDependencyGroup(FName DependencyGroupName);`
- L281 _public function_ `FName GetTypeDependencyGroup() const`
- L283 _public prototype_ `bool IsAnytypeDependencyConnected() const;`
- L286 _public function_ `template<class T> bool IsA(const T* InVar) const`
- L291 _public function_ `virtual void Invalidate(const UE::Dataflow::FTimestamp& ModifiedTimestamp = UE::Dataflow::FTimestamp::Current())`
- L293 _public function_ `bool GetCanHidePin() const`
- L294 _public function_ `bool GetPinIsHidden() const`
- L295 _public function_ `FDataflowConnection& SetCanHidePin(bool bInCanHidePin)`
- L300 _public function_ `FDataflowConnection& SetPinIsHidden(bool bInPinIsHidden)`
- L311 _public prototype_ `static FName GetTypeNameFromProperty(const FProperty* Property);` — extract the type name from a FProperty this method make sure the resulting typename is consistent with Dataflow standard where there's no space in the name for example FProperty returns : "TArray<TObjectPtr<UObject> >" but dataflow compatible typename is "TArray<TObjectPtr<UObject>>"
- L314 _private prototype_ `void InitFromType();`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Dataflow` (scope `UE`)
- L24 _prototype_ `template<class T> inline FName GraphConnectionTypeName();` (scope `UE::Dataflow`)
- L25 _prototype_ `template<class T> inline FName GraphConnectionTypeName();` (scope `UE::Dataflow`)
- L100 _function_ `friend uint32 GetTypeHash(const FConnectionKey& Key)` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowContextAssetStore.h` (Public)


#### struct `UE::Dataflow::IContextAssetStoreInterface`  
`struct IContextAssetStoreInterface`  
_L14-46_
- desc: interface to be implemented by the context that expose the asset store API
- L22 _public function_ `template <typename T> inline T* AddAssetTyped(const FString& AssetPath)` — Typed version of the AddAsset virtual method @see AddAsset
- L32 _public prototype_ `virtual UObject* AddAsset(const FString& PersistentAssetPath, const UClass* AssetClass) = 0;` — Create an new asset to be commited later ( when the terminal nodes are evaluated ) When commited, the asset will be duplicated to a final package matching PersistentAssetPath @return an UObject owned by the transient package
- L39 _public prototype_ `virtual UObject* CommitAsset(const FString& TransientAssetPath) = 0;` — Commit the asset matching the TransientAssetPath If such asset was added previously this will duplicate it and save it to a persistent package @return the newly created persistent UObject asset
- L44 _public prototype_ `virtual void ClearAssets() = 0;` — Clear all assets from the store

#### struct `UE::Dataflow::FContextAssetStore`  
`struct FContextAssetStore: public FGCObject`  
_L49-97_
- inherits: `FGCObject`
- desc: asset store to managed creation and storage of assets during the evaluation of the Dataflow graph
- L57 _public prototype_ `UObject* AddAsset(const FString& PersistentAssetPath, const UClass* AssetClass);` — Create an new asset to be commited later ( when the terminal nodes are evaluated ) When commited, the asset will be duplicated to a final package matching PersistentAssetPath @return an UObject owned by the transient package
- L64 _public prototype_ `UObject* CommitAsset(const FString& TransientAssetPath);` — Commit the asset matching the TransientAssetPath If such asset was added previously this will duplicate it and save it to a persistent package @return the newly created persistent UObject asset
- L71 _public prototype_ `UObject* CommitAsset(const UObject* TransientAsset);` — Commit the asset matching the TransientAsset If such asset was added previously this will duplicate it and save it to a package matching AssetPath @return the newly created persistent UObject asset
- L76 _public prototype_ `void ClearAssets();` — Clear all assets from the store
- L79 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L80 _public function_ `virtual FString GetReferencerName() const override`
- L91 _private prototype_ `const FAssetData* FindByTransientPath(const FString& TransientAssetPath) const;`
- L92 _private prototype_ `const FAssetData* FindByTransientAsset(const UObject* TransientAsset) const;`
- L94 _private prototype_ `UObject* CommitAsset(const FAssetData& AssetData);`
- L96 _private member_ `TArray<FAssetData> AssetData;`

#### struct `UE::Dataflow::FContextAssetStore::FAssetData`  
`struct FAssetData`  
_L84-89_
- L86 _public member_ `FString PersistentPath;`
- L87 _public member_ `FString TransientPath;`
- L88 _public member_ `TObjectPtr<UObject> TransientAsset = nullptr;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Dataflow` (scope `UE`)

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowContextCache.h` (Public)


#### struct `UE::Dataflow::TIsUObjectPtrElement`  
`template <typename T> struct TIsUObjectPtrElement`  
_L27-31_
- desc: Trait used to select the UObject* or TObjectPtr cache element path code.
- L29 _public typedef_ `typedef typename TDecay<T>::Type Type;`
- L30 _public member_ `static constexpr bool Value = (std::is_pointer_v<Type> && std::is_convertible_v<Type, const UObjectBase*>) || TIsTObjectPtr_V<Type>;`

#### struct `UE::Dataflow::Private::THasTBaseStructureGet`  
`template <typename T, typename = void> struct THasTBaseStructureGet`  
_L37-37_
- desc: True if TBaseStructure<T> provides a Get() (USTRUCT or explicit TBaseStructure specialization).
- L37 _public member_ `template <typename T, typename = void> struct THasTBaseStructureGet { static constexpr bool Value = false; };` — True if TBaseStructure<T> provides a Get() (USTRUCT or explicit TBaseStructure specialization).
- L39 _public member_ `template <typename T> struct THasTBaseStructureGet<T, std::void_t<decltype(&TBaseStructure<T>::Get)>> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::THasTBaseStructureGet`  
`template <typename T> struct THasTBaseStructureGet<T, std::void_t<decltype(&TBaseStructure<T>::Get)>>`  
_L39-39_
- L37 _public member_ `template <typename T, typename = void> struct THasTBaseStructureGet { static constexpr bool Value = false; };` — True if TBaseStructure<T> provides a Get() (USTRUCT or explicit TBaseStructure specialization).
- L39 _public member_ `template <typename T> struct THasTBaseStructureGet<T, std::void_t<decltype(&TBaseStructure<T>::Get)>> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <typename T> struct TIsReflectedCoreVariant`  
_L44-44_
- desc: True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <typename T> struct TIsReflectedCoreVariant`  
_L45-45_
- desc: True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <typename T> struct TIsReflectedCoreVariant`  
_L46-46_
- desc: True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <typename T> struct TIsReflectedCoreVariant`  
_L47-47_
- desc: True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FVector2f>`  
_L48-48_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FVector2d>`  
_L49-49_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FVector3f>`  
_L50-50_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FVector3d>`  
_L51-51_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FVector4f>`  
_L52-52_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FVector4d>`  
_L53-53_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FPlane4f>`  
_L54-54_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FPlane4d>`  
_L55-55_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FQuat4f>`  
_L56-56_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FQuat4d>`  
_L57-57_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FRotator3f>`  
_L58-58_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FRotator3d>`  
_L59-59_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FTransform3f>`  
_L60-60_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FTransform3d>`  
_L61-61_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FMatrix44f>`  
_L62-62_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FMatrix44d>`  
_L63-63_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::Private::TIsReflectedCoreVariant`  
`template <> struct TIsReflectedCoreVariant<FBox2f>`  
_L64-64_
- L44 _public member_ `template <typename T> struct TIsReflectedCoreVariant { static constexpr bool Value = false; };` — True if T is reflected via a TVariantStructure specialization (LWC float/double core variant types). we need to explicitly list them ( like in many other place in the engine ) because TVariantStructure will static assert in its default implementation IMPORTANT : Keep in sync with UE_DECLARE_CORE_VARIANT_TYPE invocations in CoreUObject/Public/UObject/Class.h.
- L48 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2f> { static constexpr bool Value = true; };`
- L49 _public member_ `template <> struct TIsReflectedCoreVariant<FVector2d> { static constexpr bool Value = true; };`
- L50 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3f> { static constexpr bool Value = true; };`
- L51 _public member_ `template <> struct TIsReflectedCoreVariant<FVector3d> { static constexpr bool Value = true; };`
- L52 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4f> { static constexpr bool Value = true; };`
- L53 _public member_ `template <> struct TIsReflectedCoreVariant<FVector4d> { static constexpr bool Value = true; };`
- L54 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4f> { static constexpr bool Value = true; };`
- L55 _public member_ `template <> struct TIsReflectedCoreVariant<FPlane4d> { static constexpr bool Value = true; };`
- L56 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4f> { static constexpr bool Value = true; };`
- L57 _public member_ `template <> struct TIsReflectedCoreVariant<FQuat4d> { static constexpr bool Value = true; };`
- L58 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3f> { static constexpr bool Value = true; };`
- L59 _public member_ `template <> struct TIsReflectedCoreVariant<FRotator3d> { static constexpr bool Value = true; };`
- L60 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3f> { static constexpr bool Value = true; };`
- L61 _public member_ `template <> struct TIsReflectedCoreVariant<FTransform3d> { static constexpr bool Value = true; };`
- L62 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44f> { static constexpr bool Value = true; };`
- L63 _public member_ `template <> struct TIsReflectedCoreVariant<FMatrix44d> { static constexpr bool Value = true; };`
- L64 _public member_ `template <> struct TIsReflectedCoreVariant<FBox2f> { static constexpr bool Value = true; };`

#### struct `UE::Dataflow::TIsReflectedStruct`  
`template <typename T> struct TIsReflectedStruct`  
_L90-95_
- desc: Trait used to select the UStruct cache element path code.
- L92 _public member_ `static constexpr bool Value = Private::THasTBaseStructureGet<typename TDecay<T>::Type>::Value || Private::TIsReflectedCoreVariant<typename TDecay<T>::Type>::Value;`

#### struct `UE::Dataflow::FTimestamp`  
`struct FTimestamp`  
_L97-111_
- L99 _public typedef_ `typedef uint64 Type;`
- L100 _public member_ `Type Value = Type(0);`
- L102 _public function_ `FTimestamp(Type InValue) : Value(InValue)`
- L103 _public function_ `bool operator>=(const FTimestamp& InTimestamp) const`
- L104 _public function_ `bool operator<(const FTimestamp& InTimestamp) const`
- L105 _public function_ `bool operator==(const FTimestamp& InTimestamp) const`
- L106 _public function_ `bool IsInvalid()`
- L107 _public function_ `bool IsInvalid() const`
- L109 _public prototype_ `static Type Current();`
- L110 _public member_ `static Type Invalid;` — 0

#### struct `UE::Dataflow::IContextCacheStore`  
`struct IContextCacheStore`  
_L113-117_
- L115 _public prototype_ `virtual const TUniquePtr<FContextCacheElementBase>* FindCacheElement(FContextCacheKey Key) const = 0;`
- L116 _public prototype_ `virtual bool HasCacheElement(FContextCacheKey Key, FTimestamp InTimestamp = FTimestamp::Invalid) const = 0;`

#### struct `UE::Dataflow::FContextCacheElementBase`  
`struct FContextCacheElementBase`  
_L122-196_
- L135 _public function_ `FContextCacheElementBase(EType CacheElementType, FGuid InNodeGuid = FGuid(), const FProperty* InProperty = nullptr, uint32 InNodeHash = 0, FTimestamp InTimestamp = FTimestamp::Invalid) : Type(CacheElementType) , NodeGuid(InNodeGuid) , Property(InProperty) , NodeHash(InNodeHash) , Timestamp(InTimestamp)`
- L142 _public prototype_ `virtual ~FContextCacheElementBase() = default;`
- L145 _public prototype_ `inline TUniquePtr<FContextCacheElementBase> CreateReference(FContextCacheKey InReferenceDataKey) const;` — InReferenceDataKey is the key of the cache element this function is called on
- L148 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> Clone(const IContextCacheStore& Context) const = 0;` — clone the cache entry
- L151 _public prototype_ `template<typename T> inline const T& GetTypedData(const IContextCacheStore& Context, const FProperty* PropertyIn, const T& Default) const;`
- L153 _public prototype_ `virtual const void* GetUntypedData(const IContextCacheStore& Context, const FProperty* PropertyIn) const = 0;`
- L155 _public prototype_ `virtual bool IsArray(const IContextCacheStore& Context) const = 0;`
- L156 _public prototype_ `virtual int32 GetNumArrayElements(const IContextCacheStore& Context) const = 0;`
- L157 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateFromArrayElement(const IContextCacheStore& Context, int32 Index, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const = 0;`
- L158 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElement(const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const = 0;`
- L160 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElementAndAppend(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const = 0;` — DereferencedElements will not be FContextCacheElementReference and instead be the final element any reference stored.
- L162 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> AppendArrayElements(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const = 0;` — DereferencedElements will not be FContextCacheElementReference and instead be the final element any reference stored.
- L165 _public function_ `virtual FConstStructView GetConstStructView(const IContextCacheStore& Context) const` — Get the matching const struct view if available, otherwise return an invalid one
- L167 _public function_ `EType GetType() const`
- L169 _public function_ `const FProperty* GetProperty() const`
- L170 _public function_ `const FTimestamp& GetTimestamp() const`
- L171 _public function_ `void SetTimestamp(const FTimestamp& InTimestamp)`
- L173 _public function_ `const FGuid& GetNodeGuid() const`
- L174 _public function_ `const uint32 GetNodeHash() const`
- L177 _public function_ `void SetProperty(const FProperty* NewProperty)` — use this with caution: setting the property of a wrong type may cause problems
- L180 _public function_ `void UpdatePropertyAndNodeData(const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp)` — use this with caution: setting the property of a wrong type may cause problems
- L191 _private member_ `EType Type;`
- L192 _private member_ `FGuid NodeGuid;`
- L193 _private member_ `const FProperty* Property = nullptr;`
- L194 _private member_ `uint32 NodeHash = 0;`
- L195 _private member_ `FTimestamp Timestamp = FTimestamp::Invalid;`
- L734 _function_ `template<class T> const T& FContextCacheElementBase::GetTypedData(const IContextCacheStore& Context, const FProperty* PropertyIn, const T& Default) const` — cache element method implementation
- L798 _function_ `TUniquePtr<FContextCacheElementBase> FContextCacheElementBase::CreateReference(FContextCacheKey InReferenceDataKey) const`

#### enum `UE::Dataflow::FContextCacheElementBase::EType`  
`enum EType`  
_L124-133_
- L126 _public enumerator_ `CacheElementTyped`
- L127 _public enumerator_ `CacheElementReference`
- L128 _public enumerator_ `CacheElementNull`
- L129 _public enumerator_ `CacheElementUObject` — UObjectPtr
- L130 _public enumerator_ `CacheElementUObjectArray` — TArray of UObjectPtr
- L131 _public enumerator_ `CacheElementUStruct`
- L132 _public enumerator_ `CacheElementUStructArray`

#### struct `UE::Dataflow::TContextCacheElement`  
`template<class T> struct TContextCacheElement : public FContextCacheElementBase`  
_L202-318_
- inherits: `FContextCacheElementBase`
- L204 _public function_ `TContextCacheElement(FGuid InNodeGuid, const FProperty* InProperty, T&& InData, uint32 InNodeHash, FTimestamp Timestamp) : FContextCacheElementBase(EType::CacheElementTyped, InNodeGuid, InProperty, InNodeHash, Timestamp) , Data(Forward<T>(InData))`
- L209 _public function_ `TContextCacheElement(const TContextCacheElement<T>& Other) : FContextCacheElementBase(EType::CacheElementTyped, Other.GetNodeGuid(), Other.GetProperty(), Other.GetNodeHash(), Other.GetTimestamp()) , Data(Other.Data)`
- L214 _public prototype_ `inline const T& GetData(const IContextCacheStore& Context, const FProperty* PropertyIn, const T& Default) const;`
- L216 _public function_ `virtual const void* GetUntypedData(const IContextCacheStore& Context, const FProperty* PropertyIn) const`
- L221 _public function_ `virtual bool IsArray(const IContextCacheStore& Context) const override`
- L226 _public function_ `virtual int32 GetNumArrayElements(const IContextCacheStore& Context) const override`
- L238 _public function_ `virtual TUniquePtr<FContextCacheElementBase> CreateFromArrayElement(const IContextCacheStore& Context, int32 Index, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override`
- L254 _public function_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElement(const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override`
- L267 _public function_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElementAndAppend(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override`
- L290 _public function_ `virtual TUniquePtr<FContextCacheElementBase> AppendArrayElements(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override`
- L311 _public function_ `const T& GetDataDirect() const`
- L313 _public prototype_ `inline virtual TUniquePtr<FContextCacheElementBase> Clone(const IContextCacheStore& Context) const override;`
- L316 _private typedef_ `typedef typename TDecay<T>::Type FDataType;` — Using universal references here means T could be either const& or an rvalue reference
- L317 _private member_ `const FDataType Data;` — Decaying T removes any reference and gets the correct underlying storage data type
- L804 _function_ `template<class T> const T& TContextCacheElement<T>::GetData(const IContextCacheStore& Context, const FProperty* PropertyIn, const T& Default) const`
- L810 _function_ `template<class T> TUniquePtr<FContextCacheElementBase> TContextCacheElement<T>::Clone(const IContextCacheStore& Context) const`

#### struct `UE::Dataflow::FContextCacheElementReference`  
`struct FContextCacheElementReference : public FContextCacheElementBase`  
_L323-357_
- inherits: `FContextCacheElementBase`
- L325 _public function_ `FContextCacheElementReference(FGuid InNodeGuid, const FProperty* InProperty, FContextCacheKey InDataKey, uint32 InNodeHash, FTimestamp Timestamp) : FContextCacheElementBase(EType::CacheElementReference, InNodeGuid, InProperty, InNodeHash, Timestamp) , DataKey(InDataKey)`
- L332 _public prototype_ `template<class T> inline const T& GetData(const IContextCacheStore& Context, const FProperty* PropertyIn, const T& Default) const;`
- L334 _public prototype_ `virtual const void* GetUntypedData(const IContextCacheStore& Context, const FProperty* PropertyIn) const override;`
- L336 _public prototype_ `virtual bool IsArray(const IContextCacheStore& Context) const override;`
- L338 _public prototype_ `virtual int32 GetNumArrayElements(const IContextCacheStore& Context) const override;`
- L340 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateFromArrayElement(const IContextCacheStore& Context, int32 Index, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L342 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElement(const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L344 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElementAndAppend(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L346 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> AppendArrayElements(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L348 _public prototype_ `virtual FConstStructView GetConstStructView(const IContextCacheStore& Context) const;`
- L350 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> Clone(const IContextCacheStore& Context) const override;`
- L353 _public prototype_ `const FContextCacheElementBase* GetReferencedElement(const IContextCacheStore& Context) const;` — Traverse references until the non-reference element is found.
- L356 _private member_ `const FContextCacheKey DataKey;` — this is a key to another cache element
- L816 _function_ `template<class T> const T& FContextCacheElementReference::GetData(const IContextCacheStore& Context, const FProperty* InProperty, const T& Default) const`

#### struct `UE::Dataflow::FContextCacheElementNull`  
`struct FContextCacheElementNull : public FContextCacheElementBase`  
_L362-387_
- inherits: `FContextCacheElementBase`
- L369 _public function_ `FContextCacheElementNull(FGuid InNodeGuid, const FProperty* InProperty, FContextCacheKey InDataKey, uint32 InNodeHash, FTimestamp Timestamp) : FContextCacheElementBase(EType::CacheElementNull, InNodeGuid, InProperty, InNodeHash, FTimestamp((Timestamp.Value == 0)? 0: (Timestamp.Value - 1)))` — `UE_DEPRECATED(5.6, "Use the other constructor that does not pass a DataKey (the key is not needed)")` — IMPORTANT: Timestamp must be set to (Timestamp.Value - 1) to make sure that this type of entry is always invalid
- L373 _public function_ `FContextCacheElementNull(FGuid InNodeGuid, const FProperty* InProperty, uint32 InNodeHash, FTimestamp Timestamp) : FContextCacheElementBase(EType::CacheElementNull, InNodeGuid, InProperty, InNodeHash, FTimestamp((Timestamp.Value == 0) ? 0 : (Timestamp.Value - 1)))`
- L377 _public prototype_ `virtual const void* GetUntypedData(const IContextCacheStore& Context, const FProperty* PropertyIn) const override;`
- L379 _public prototype_ `virtual bool IsArray(const IContextCacheStore& Context) const override;`
- L380 _public prototype_ `virtual int32 GetNumArrayElements(const IContextCacheStore& Context) const override;`
- L381 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateFromArrayElement(const IContextCacheStore& Context, int32 Index, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L382 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElement(const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L383 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElementAndAppend(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L384 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> AppendArrayElements(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L386 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> Clone(const IContextCacheStore& Context) const override;`

#### struct `UE::Dataflow::TContextCacheElementUObject`  
`template<class T> struct TContextCacheElementUObject : public FContextCacheElementBase, public FGCObject`  
_L393-466_
- inherits: `FContextCacheElementBase,FGCObject`
- L395 _public function_ `TContextCacheElementUObject(FGuid InNodeGuid, const FProperty* InProperty, T&& InObjectPtr, uint32 InNodeHash, FTimestamp Timestamp) : FContextCacheElementBase(EType::CacheElementUObject, InNodeGuid, InProperty, InNodeHash, Timestamp) , ObjectPtr(InObjectPtr)`
- L400 _public function_ `TContextCacheElementUObject(const TContextCacheElementUObject<T>& Other) : FContextCacheElementBase(EType::CacheElementUObject, Other.GetNodeGuid(), Other.GetProperty(), Other.GetNodeHash(), Other.GetTimestamp()) , ObjectPtr(Other.ObjectPtr)`
- L405 _public function_ `const T& GetData(const IContextCacheStore& , const FProperty* , const T& ) const`
- L410 _public function_ `virtual const void* GetUntypedData(const IContextCacheStore& , const FProperty* ) const override`
- L415 _public function_ `virtual bool IsArray(const IContextCacheStore& Context) const override`
- L420 _public function_ `virtual int32 GetNumArrayElements(const IContextCacheStore& Context) const override`
- L425 _public function_ `virtual TUniquePtr<FContextCacheElementBase> CreateFromArrayElement(const IContextCacheStore& Context, int32 Index, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override`
- L430 _public function_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElement(const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override`
- L436 _public function_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElementAndAppend(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override`
- L451 _public function_ `virtual TUniquePtr<FContextCacheElementBase> AppendArrayElements(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override`
- L456 _public prototype_ `inline virtual TUniquePtr<FContextCacheElementBase> Clone(const IContextCacheStore& Context) const override;`
- L459 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L460 _public function_ `virtual FString GetReferencerName() const override`
- L464 _private typedef_ `typedef typename TDecay<T>::Type FDataType;` — Using universal references here means T could be either const& or an rvalue reference
- L465 _private member_ `FDataType ObjectPtr;` — Decaying T removes any reference and gets the correct underlying storage data type
- L826 _function_ `template<class T> TUniquePtr<FContextCacheElementBase> TContextCacheElementUObject<T>::Clone(const IContextCacheStore& Context) const`

#### struct `UE::Dataflow::TContextCacheElementUObjectArray`  
`template<class T> struct TContextCacheElementUObjectArray : public FContextCacheElementBase, public FGCObject`  
_L472-550_
- inherits: `FContextCacheElementBase,FGCObject`
- L475 _public function_ `template<typename ArrayT> TContextCacheElementUObjectArray(FGuid InNodeGuid, const FProperty* InProperty, ArrayT&& InObjectPtrArray, uint32 InNodeHash, FTimestamp Timestamp) : FContextCacheElementBase(EType::CacheElementUObjectArray, InNodeGuid, InProperty, InNodeHash, Timestamp) , ObjectPtrArray(Forward<ArrayT>(InObjectPtrArray))`
- L481 _public function_ `TContextCacheElementUObjectArray(const TContextCacheElementUObjectArray<T>& Other) : FContextCacheElementBase(EType::CacheElementUObjectArray, Other.GetNodeGuid(), Other.GetProperty(), Other.GetNodeHash(), Other.GetTimestamp()) , ObjectPtrArray(Other.ObjectPtrArray)`
- L486 _public function_ `virtual bool IsArray(const IContextCacheStore& Context) const override`
- L491 _public function_ `const TArray<T>& GetData(const IContextCacheStore& , const FProperty* , const TArray<T>& ) const`
- L496 _public function_ `virtual const void* GetUntypedData(const IContextCacheStore& , const FProperty* ) const override`
- L501 _public function_ `virtual int32 GetNumArrayElements(const IContextCacheStore& Context) const override`
- L506 _public function_ `virtual TUniquePtr<FContextCacheElementBase> CreateFromArrayElement(const IContextCacheStore& Context, int32 Index, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override`
- L516 _public function_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElement(const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override`
- L521 _public function_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElementAndAppend(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override`
- L526 _public function_ `virtual TUniquePtr<FContextCacheElementBase> AppendArrayElements(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override`
- L540 _public prototype_ `inline virtual TUniquePtr<FContextCacheElementBase> Clone(const IContextCacheStore& Context) const override;`
- L543 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L544 _public function_ `virtual FString GetReferencerName() const override`
- L548 _private typedef_ `typedef typename TDecay<T>::Type FDataType;` — Using universal references here means T could be either const& or an rvalue reference
- L549 _private member_ `TArray<FDataType> ObjectPtrArray;` — Decaying T removes any reference and gets the correct underlying storage data type
- L832 _function_ `template<class T> TUniquePtr<FContextCacheElementBase> TContextCacheElementUObjectArray<T>::Clone(const IContextCacheStore& Context) const`

#### struct `UE::Dataflow::FContextCacheElementUStruct`  
`struct FContextCacheElementUStruct : public FContextCacheElementBase, public FGCObject`  
_L555-618_
- inherits: `FContextCacheElementBase,FGCObject`
- L557 _public prototype_ `explicit FContextCacheElementUStruct(FGuid InNodeGuid, const FProperty* InProperty, const FConstStructView& StructView, uint32 InNodeHash, FTimestamp Timestamp);`
- L560 _public function_ `template<typename T> explicit FContextCacheElementUStruct(FGuid InNodeGuid, const FProperty* InProperty, T&& InStruct, uint32 InNodeHash, FTimestamp Timestamp) : FContextCacheElementBase(EType::CacheElementUStruct, InNodeGuid, InProperty, InNodeHash, Timestamp)`
- L577 _public prototype_ `explicit FContextCacheElementUStruct(const FContextCacheElementUStruct& Other);`
- L580 _public function_ `template<typename T> inline const T& GetData(const IContextCacheStore& , const FProperty* , const T& Default) const`
- L597 _public prototype_ `virtual const void* GetUntypedData(const IContextCacheStore& , const FProperty* ) const override;`
- L599 _public prototype_ `virtual bool IsArray(const IContextCacheStore& Context) const override;`
- L600 _public prototype_ `virtual int32 GetNumArrayElements(const IContextCacheStore& Context) const override;`
- L601 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateFromArrayElement(const IContextCacheStore& Context, int32 Index, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L602 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElement(const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L603 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElementAndAppend(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L604 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> AppendArrayElements(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L607 _public prototype_ `virtual FConstStructView GetConstStructView(const IContextCacheStore& Context) const;` — Get the matching const struct view if available, otherwise return an invalid one
- L609 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> Clone(const IContextCacheStore& Context) const override;`
- L612 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L613 _public prototype_ `FString GetReferencerName() const override;`
- L617 _private member_ `FInstancedStruct InstancedStruct;`

#### struct `UE::Dataflow::FContextCacheElementUStructArray`  
`struct FContextCacheElementUStructArray : public FContextCacheElementBase, public FGCObject`  
_L623-730_
- inherits: `FContextCacheElementBase,FGCObject`
- L625 _public function_ `explicit FContextCacheElementUStructArray(FGuid InNodeGuid, const FProperty* InProperty, const FConstStructArrayView& InStructArrayView, uint32 InNodeHash, FTimestamp Timestamp) : FContextCacheElementBase(EType::CacheElementUStructArray, InNodeGuid, InProperty, InNodeHash, Timestamp) , InstancedStructArray(InStructArrayView)`
- L631 _public function_ `explicit FContextCacheElementUStructArray(FGuid InNodeGuid, const FProperty* InProperty, const FConstStructView& InStructView, uint32 InNodeHash, FTimestamp Timestamp) : FContextCacheElementBase(EType::CacheElementUStructArray, InNodeGuid, InProperty, InNodeHash, Timestamp) , InstancedStructArray(InStructView)` — construct from a single struct view into an array
- L635 _public function_ `explicit FContextCacheElementUStructArray(FGuid InNodeGuid, const FProperty* InProperty, const TArray<FConstStructView>& InStructViews, uint32 InNodeHash, FTimestamp Timestamp) : FContextCacheElementBase(EType::CacheElementUStructArray, InNodeGuid, InProperty, InNodeHash, Timestamp) , InstancedStructArray(InStructViews)`
- L641 _public function_ `template<typename T> explicit FContextCacheElementUStructArray(FGuid InNodeGuid, const FProperty* InProperty, TArray<T>&& InStructArray, uint32 InNodeHash, FTimestamp Timestamp) : FContextCacheElementBase(EType::CacheElementUStructArray, InNodeGuid, InProperty, InNodeHash, Timestamp) , InstancedStructArray(Private::GetReflectedScriptStruct<T>())`
- L648 _public function_ `explicit FContextCacheElementUStructArray(const FContextCacheElementUStructArray& Other) : FContextCacheElementUStructArray(Other.GetNodeGuid(), Other.GetProperty(), Other.GetStructArrayView(), Other.GetNodeHash(), Other.GetTimestamp())`
- L652 _public prototype_ `virtual ~FContextCacheElementUStructArray() override = default;`
- L655 _public function_ `template<typename T> const TArray<T>& GetData(const IContextCacheStore& , const FProperty* , const TArray<T>& ) const`
- L660 _public prototype_ `virtual const void* GetUntypedData(const IContextCacheStore& , const FProperty* ) const override;`
- L662 _public prototype_ `virtual bool IsArray(const IContextCacheStore& Context) const override;`
- L663 _public prototype_ `virtual int32 GetNumArrayElements(const IContextCacheStore& Context) const override;`
- L664 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateFromArrayElement(const IContextCacheStore& Context, int32 Index, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L665 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElement(const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L666 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> CreateArrayFromElementAndAppend(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L667 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> AppendArrayElements(const TArray<const FContextCacheElementBase*>& DereferencedElements, const IContextCacheStore& Context, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const override;`
- L669 _public prototype_ `virtual TUniquePtr<FContextCacheElementBase> Clone(const IContextCacheStore& Context) const override;`
- L672 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L673 _public prototype_ `FString GetReferencerName() const override;`
- L677 _private prototype_ `FConstStructArrayView GetStructArrayView() const;`
- L729 _private member_ `FInstancedStructArray InstancedStructArray;`

#### struct `UE::Dataflow::FContextCacheElementUStructArray::FInstancedStructArray`  
`struct FInstancedStructArray final : private TArray<uint8>`  
_L680-727_
- inherits: `TArray<uint8>`
- desc: Implements a FInstancedStruct for arrays (FInstancedStructContainer cannot be cast to a TArray)
- L682 _public prototype_ `explicit FInstancedStructArray(const UScriptStruct* const InScriptStruct);`
- L683 _public prototype_ `explicit FInstancedStructArray(const FConstStructView& StructView);`
- L684 _public prototype_ `explicit FInstancedStructArray(const TArray<FConstStructView>& StructViews);`
- L685 _public prototype_ `explicit FInstancedStructArray(const FConstStructArrayView& StructArrayView);`
- L686 _public prototype_ `~FInstancedStructArray();`
- L694 _public prototype_ `const int32 GetStructureSize() const;`
- L696 _public prototype_ `const UScriptStruct* GetScriptStruct() const;`
- L698 _public prototype_ `FConstStructView GetScriptViewAt(int32 Index) const;`
- L700 _public prototype_ `const void* GetMemory() const;`
- L702 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);`
- L705 _public prototype_ `void AddElements(const TArray<FConstStructView>& StructViews);` — Add elements from other struct views.
- L708 _public prototype_ `void AppendElements(const TArray<const FInstancedStructArray*>& OtherArrays);` — Append arrays from other FInstancedStructArrays
- L711 _public function_ `template<typename T> const TArray<T>& Get() const`
- L718 _public function_ `template<typename T> TArray<T>& Get()`
- L724 _private prototype_ `void InitFromRawData(const void* Data, const int32 Num);`
- L726 _private member_ `const UScriptStruct* const ScriptStruct;`

#### struct `UE::Dataflow::FContextCache`  
`struct FContextCache : public TMap<FContextCacheKey, TUniquePtr<FContextCacheElementBase>>`  
_L790-793_
- inherits: `TMap<FContextCacheKey,TUniquePtr<FContextCacheElementBase>>`
- L792 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `UE::Dataflow::FContextValue`  
`struct FContextValue`  
_L839-886_
- L842 _public prototype_ `FContextValue(IContextCacheStore& InContext, FContextCacheKey InCacheKey);`
- L843 _public prototype_ `FContextValue(IContextCacheStore& InContext, TUniquePtr<FContextCacheElementBase>&& InCacheElement);`
- L845 _public prototype_ `int32 Num() const;`
- L846 _public prototype_ `bool IsArray() const;`
- L847 _public prototype_ `FContextValue GetAt(int32 Index) const;`
- L848 _public prototype_ `FContextValue ToArray() const;`
- L850 _public prototype_ `static FContextValue MakeArray(IContextCacheStore& InContext, const TArray<const FContextValue>& Elements);` — Warning: no checking will be done to verify that Elements can be appended to the array for strongly typed TContextCacheElement arrays and elements. It is assumed they can be cast to the correct type.
- L852 _public prototype_ `static FContextValue AppendArrays(IContextCacheStore& InContext, const TArray<const FContextValue>& ArrayElements);` — Warning: no checking will be done to verify that Elements can be appended to the array for strongly typed TContextCacheElement arrays and elements. It is assumed they can be cast to the correct type.
- L854 _public prototype_ `FConstStructView GetConstStructView() const;`
- L855 _public prototype_ `FInstancedStruct GetInstancedStruct() const;`
- L858 _public function_ `template<typename T> const T* GetTypedStructPtr() const`
- L864 _public function_ `template<typename T> const TInstancedStruct<T> GetTypedInstancedStruct() const`
- L876 _public prototype_ `const FContextCacheElementBase* GetCacheEntry() const;` — `UE_DEPRECATED(5.8, "From release 5.10, this method is going to be private, direct access to the cache element is not authorized and the rest of the API of this class should be used instead to get data from the cache")`
- L881 _private prototype_ `const FContextCacheElementBase* GetCacheEntryPrivate() const;`
- L883 _private member_ `IContextCacheStore& Context;`
- L884 _private member_ `FContextCacheKey CacheKey;` — only set when CacheElement is null
- L885 _private member_ `TSharedPtr<FContextCacheElementBase> CacheElement;` — when CacheKey is define this should be null

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Dataflow` (scope `UE`)
- L23 _typedef_ `typedef uint32 FContextCacheKey;` (scope `UE::Dataflow`)
- L33 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L69 _function_ `template <typename T> UScriptStruct* GetReflectedScriptStruct()` (scope `UE::Dataflow::Private`) — Resolves to TBaseStructure<T>::Get() when available, otherwise to TVariantStructure<T>::Get() (covers LWC float/double variants like FVector3f, FQuat4f, FTransform3d, ...).
- L71 _typedef_ `using FStruct = typename TDecay<T>::Type;` (scope `UE::Dataflow::Private::GetReflectedScriptStruct`)
- L563 _typedef_ `using FStruct = typename TDecay<T>::Type;` (scope `UE::Dataflow::FContextCacheElementUStruct::FContextCacheElementUStruct`)
- L582 _typedef_ `using FStruct = typename TDecay<T>::Type;` (scope `UE::Dataflow::FContextCacheElementUStruct::GetData`)
- L889 _prototype_ `FArchive& operator<<(FArchive& Ar, UE::Dataflow::FTimestamp& ValueIn);`
- L890 _prototype_ `FArchive& operator<<(FArchive& Ar, UE::Dataflow::FContextCache& ValueIn);`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowContextCachingFactory.h` (Public)


#### struct `UE::Dataflow::FContextCacheData`  
`struct FContextCacheData`  
_L14-24_
- L16 _public function_ `FContextCacheData(FName InType, FGuid InNodeGuid, FContextCacheElementBase* InData, uint32 InNodeHash, FTimestamp InTimestamp) : Type(InType), NodeGuid(InNodeGuid), Data(InData), NodeHash(InNodeHash), Timestamp(InTimestamp)`
- L19 _public member_ `FName Type;`
- L20 _public member_ `FGuid NodeGuid;`
- L21 _public member_ `FContextCacheElementBase* Data = nullptr;`
- L22 _public member_ `uint32 NodeHash;`
- L23 _public member_ `FTimestamp Timestamp = FTimestamp::Invalid;`

#### class `UE::Dataflow::FContextCachingFactory`  
`class FContextCachingFactory`  
_L29-76_
- L31 _private typedef_ `typedef TFunction<FContextCacheElementBase*(FArchive& Ar, FContextCacheElementBase* InData)> FSerializeFunction;`
- L34 _private member_ `TMap<FName, FSerializeFunction > CachingMap;` — All Maps indexed by TypeName
- L35 _private member_ `static FContextCachingFactory* Instance;`
- L36 _private function_ `FContextCachingFactory()`
- L39 _public function_ `~FContextCachingFactory()`
- L41 _public function_ `static FContextCachingFactory* GetInstance()`
- L50 _public prototype_ `void RegisterSerializeFunction(const FName& Type, FSerializeFunction InSerializeFunc);`
- L53 _public function_ `template<class T> static const T& GetTypedElement(const FContextCacheElementBase* InElement, const T& Default)`
- L66 _public function_ `template<class T> static FContextCacheElementBase* NewTypedElement(T&& Data)`
- L72 _public prototype_ `FContextCacheElementBase* Serialize(FArchive& Ar, FContextCacheData&& Data);`
- L74 _public function_ `bool Contains(FName InType) const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAFLOWCORE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Dataflow` (scope `UE`)

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowContextEvaluator.h` (Public)


#### struct `UE::Dataflow::FContextEvaluator`  
`struct FContextEvaluator`  
_L34-88_
- desc: Asynchronously evaluate a dataflow nodes This may be slower than executing the graph in one go synchronously but this offers the following advantage: - this can be cancelled at anytime ( only the in progress node will have finish evaluating while all the pending ones will be discarded ) - nodes that need to run on the game thread will do so ( see FDataflowNode EvaluateOnGameThreadOnly method )
- L37 _public typedef_ `using FNodeId = FGuid;`
- L57 _public function_ `FContextEvaluator(FContext& InOwningContext) : OwningContext(InOwningContext)`
- L62 _public prototype_ `void ScheduleNodeEvaluation(const FDataflowNode& Node, FOnPostEvaluationFunction OnPostEvaluation);`
- L63 _public prototype_ `void ScheduleOutputEvaluation(const FDataflowOutput& Output, FOnPostEvaluationFunction OnPostEvaluation);`
- L65 _public prototype_ `void Process();`
- L66 _public prototype_ `void Cancel();`
- L67 _public prototype_ `void GetStats(int32& OutNumPendingTasks, int32& OutNumRunningTasks, int32& OutNumCompletedTasks) const;`
- L69 _public function_ `int32 GetNumPendingTasks() const`
- L70 _public function_ `int32 GetNumRunningTasks() const`
- L71 _public function_ `int32 GetNumCompletedTasks() const`
- L74 _private prototype_ `bool IsScheduledOrRunning(const FNodeId& Id) const;`
- L76 _private prototype_ `void FindInvalidUpstreamNodes(const FDataflowNode& Node, TArray<const FDataflowNode*>& OutInvalidUpstreamNodes);`
- L77 _private prototype_ `bool ShouldRunOnGameThread(const FDataflowNode& Node);`
- L78 _private prototype_ `void ScheduleEvaluation(const FEvaluationEntry& Entry);`
- L80 _private prototype_ `bool TryScheduleTask(const FEvaluationEntry& Entry);`
- L81 _private prototype_ `void ScheduleTask(const FEvaluationEntry& Entry);`
- L82 _private prototype_ `void ClearCompletedTasks();`
- L84 _private member_ `FContext& OwningContext;`
- L85 _private member_ `TMap<FNodeId, FEvaluationEntry> PendingEvaluationEntries;`
- L86 _private member_ `TMap<FNodeId, FGraphEventRef> RunningTasks;`
- L87 _private member_ `TSet<FNodeId> CompletedTasks;`

#### struct `UE::Dataflow::FContextEvaluator::FEvaluationEntry`  
`struct FEvaluationEntry`  
_L39-55_
- L41 _public member_ `FNodeId Id;`
- L42 _public member_ `TWeakPtr<const FDataflowNode> WeakNode;`
- L43 _public member_ `FOnPostEvaluationFunction OnPostEvaluation;`
- L45 _public function_ `bool operator == (const FEvaluationEntry& Other) const`
- L49 _public function_ `bool operator == (const FNodeId& Other) const`
- L54 _public prototype_ `FString ToString() const;`

#### struct `UE::Dataflow::FDataflowEvaluatorParameters`  
`struct FDataflowEvaluatorParameters`  
_L90-117_
- L92 _public function_ `FDataflowEvaluatorParameters(TSharedRef<const FCompiledGraph> InCompiledGraph) : CompiledGraph(InCompiledGraph)`
- L97 _public member_ `TSharedRef<const FCompiledGraph> CompiledGraph;` — Compiled graph to evaluate
- L104 _public member_ `FGuid NodeId;` — Optional Id of the node to evaluate in particular Evaluator will try to its best to evaluate only the relevant nodes that leads to this one If not specified the entire graph will be evaluated
- L109 _public member_ `FOnPostEvaluationFunction OnPostEvaluation;` — Optional function to call when evaluation is done
- L116 _public member_ `FOnTerminalNodeEvaluatedFunction OnTerminalNodeEvaluated;` — Optional function to call each time after a "terminal" node has been evaluated A terminal node is a type of node that has its IsTerminal() method to return true (see FDataflowTerminalNode, FDataflowSubGraphOutputNode, FDataflowExecutionNode)

#### struct `UE::Dataflow::IDataflowEvaluator`  
`struct IDataflowEvaluator`  
_L119-128_
- L121 _public prototype_ `virtual ~IDataflowEvaluator() = default;`
- L122 _public prototype_ `virtual void Start(const FDataflowEvaluatorParameters& InParams) = 0;`
- L123 _public prototype_ `virtual void Cancel() = 0;`
- L125 _public prototype_ `virtual bool IsRunning() const = 0;`
- L126 _public prototype_ `virtual float GetProgress() const = 0;`
- L127 _public prototype_ `virtual FText GetProgressMessage() const = 0;`

#### struct `UE::Dataflow::FThreadSafeProgressTracker`  
`struct FThreadSafeProgressTracker`  
_L135-149_
- desc: Evaluator progress tracking Easy drop-in structure to set and get progress in a thread safe way
- L138 _public prototype_ `float GetProgress() const;`
- L139 _public prototype_ `FText GetProgressMessage() const;`
- L141 _public prototype_ `void SetProgress(float InCurrent, float InTotal, FName InNodeName);`
- L142 _public prototype_ `void SetProgress(float InProgress, FName InNodeName);`
- L143 _public prototype_ `void AddProgress(float InProgressDelta, FName InNodeName);`
- L146 _private member_ `mutable FCriticalSection ProgressLock;`
- L147 _private member_ `FName NodeName;`
- L148 _private member_ `float Progress = 0.f;`

#### struct `UE::Dataflow::FDataflowDirectEvaluator`  
`struct FDataflowDirectEvaluator : public IDataflowEvaluator`  
_L156-177_
- inherits: `IDataflowEvaluator`
- desc: This evaluator will evaluate the graph in one go when Start is called This is useful for running simulation graph for example that needs to execute in exactly one frame or evaluating graph from a blueprint
- L159 _public prototype_ `FDataflowDirectEvaluator(FContext& InOwningContext);`
- L160 _public prototype_ `virtual ~FDataflowDirectEvaluator() = default;`
- L163 _public prototype_ `virtual void Start(const FDataflowEvaluatorParameters& StartParams) override;`
- L164 _public prototype_ `virtual void Cancel() override;`
- L165 _public prototype_ `virtual bool IsRunning() const override;`
- L166 _public prototype_ `virtual float GetProgress() const override;`
- L167 _public prototype_ `virtual FText GetProgressMessage() const override;`
- L171 _private member_ `FContext& OwningContext;`
- L173 _private member_ `std::atomic<bool> bIsCanceled = false;`
- L174 _private member_ `std::atomic<bool> bIsRunning = false;`
- L176 _private member_ `FThreadSafeProgressTracker ProgressTracker;`

#### struct `UE::Dataflow::FDataflowTickEvaluator`  
`struct FDataflowTickEvaluator: public IDataflowEvaluator`  
_L184-224_
- inherits: `IDataflowEvaluator`
- desc: This evaluator will try evaluate the graph on the game thread tick It will run as many nodes it can based on a time budget Note that a node may take more than the budget and create hitches
- L186 _public prototype_ `FDataflowTickEvaluator(FContext& InOwningContext);`
- L187 _public prototype_ `virtual ~FDataflowTickEvaluator();`
- L190 _public prototype_ `virtual void Start(const FDataflowEvaluatorParameters& InParams) override;`
- L191 _public prototype_ `virtual void Cancel() override;`
- L192 _public prototype_ `virtual bool IsRunning() const override;`
- L193 _public prototype_ `virtual float GetProgress() const override;`
- L194 _public prototype_ `virtual FText GetProgressMessage() const override;`
- L198 _private prototype_ `void Reset();`
- L199 _private prototype_ `bool Tick(float DeltaTime);`
- L200 _private prototype_ `void OnEvaluationCompleted();`
- L201 _private prototype_ `void OnEvaluationCanceled();`
- L203 _private member_ `FContext& OwningContext;`
- L204 _private member_ `TSharedPtr<const FCompiledGraph> CompiledGraph;`
- L205 _private member_ `TSharedPtr<const FGraph> DataflowGraph;`
- L206 _private member_ `FOnPostEvaluationFunction PostEvaluationFunction;`
- L207 _private member_ `FOnTerminalNodeEvaluatedFunction TerminalNodeEvaluatedFunction;`
- L208 _private member_ `FGuid NodeId;`
- L210 _private member_ `FTSTicker::FDelegateHandle TickDelegateHandle;`
- L215 _private member_ `TArray<int32> NodeIndicesToEvaluate;` — Node indices (into CompiledGraph->Nodes) to evaluate this run, in topological order. When p.Dataflow.UseDemandPullTick != 0 this is the demand-pull slice; otherwise it is the full [0, NumNodes) sweep matching the legacy behaviour.
- L218 _private member_ `int32 NextNodeCursor = 0;` — Position within NodeIndicesToEvaluate of the next node to evaluate.
- L220 _private member_ `std::atomic<bool> bIsCanceled = false;`
- L221 _private member_ `std::atomic<bool> bIsRunning = false;`
- L223 _private member_ `FThreadSafeProgressTracker ProgressTracker;`

#### struct `UE::Dataflow::FDataflowTaskGraphEvaluator`  
`struct FDataflowTaskGraphEvaluator : public IDataflowEvaluator`  
_L234-255_
- inherits: `IDataflowEvaluator`
- desc: This evaluator will evaluate the graph in one go when Start is called This is useful for running simulation graph for example that needs to execute in exactly one frame it is required to run from a worker thread and will assert if a node requires gamethread evaluation Note that it is safe to cancel or query if its running or its progress from another thread
- L237 _public prototype_ `FDataflowTaskGraphEvaluator(FContext& InOwningContext);`
- L238 _public prototype_ `virtual ~FDataflowTaskGraphEvaluator() = default;`
- L241 _public prototype_ `virtual void Start(const FDataflowEvaluatorParameters& InParams) override;`
- L242 _public prototype_ `virtual void Cancel() override;`
- L243 _public prototype_ `virtual bool IsRunning() const override;`
- L244 _public prototype_ `virtual float GetProgress() const override;`
- L245 _public prototype_ `virtual FText GetProgressMessage() const override;`
- L249 _private member_ `FContext& OwningContext;`
- L251 _private member_ `TSharedPtr<FTask> CompletionTask;`
- L252 _private member_ `TSharedRef<UE::Tasks::FCancellationToken> CancellationToken;`
- L254 _private member_ `TSharedRef<FThreadSafeProgressTracker> ProgressTracker;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API DATAFLOWCORE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Dataflow` (scope `UE`)
- L25 _typedef_ `using FOnPostEvaluationFunction = TFunction<void(FContext&)>;` (scope `UE::Dataflow`)
- L26 _typedef_ `using FOnTerminalNodeEvaluatedFunction = TFunction<void(FContext&, const FDataflowNode& Node)>;` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowCore.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowCoreNodes.h` (Public)


#### struct `FDataflowReRouteNode`  
`struct FDataflowReRouteNode : public FDataflowNode`  
_L16-30_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- L24 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const;`
- L29 _public member_ `FDataflowAnyType Value;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Value", DisplayName = "Value"))`

#### struct `FDataflowBranchNode`  
`struct FDataflowBranchNode : public FDataflowNode`  
_L33-55_
- reflection: `USTRUCT(meta=(Icon="GraphEditor.Branch_16x"))`
- inherits: `FDataflowNode`
- L40 _public prototype_ `FDataflowBranchNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid());`
- L41 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const;`
- L45 _public member_ `FDataflowAnyType TrueValue;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic, DisplayName = "TrueValue"))`
- L48 _public member_ `FDataflowAnyType FalseValue;` — `UPROPERTY(meta = (DataflowInput, DataflowIntrinsic, DisplayName = "FalseValue"))`
- L51 _public member_ `bool bCondition = true;` — `UPROPERTY(EditAnywhere, Category="Condition", meta = (DataflowInput, DisplayName = "Condition"))`
- L54 _public member_ `FDataflowAnyType Result;` — `UPROPERTY(meta = (DataflowOutput, DisplayName = "Result"))`

#### struct `FDataflowSelectNode`  
`struct FDataflowSelectNode : public FDataflowNode`  
_L59-92_
- reflection: `USTRUCT(meta = (Icon = "GraphEditor.Branch_16x"))`
- inherits: `FDataflowNode`
- L66 _public prototype_ `FDataflowSelectNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid());`
- L67 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const;`
- L71 _public member_ `TArray<FDataflowAnyType> Inputs;` — `UPROPERTY()`
- L74 _public member_ `int32 SelectedIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "Condition", meta = (DataflowInput))`
- L77 _public member_ `FDataflowAnyType Result;` — `UPROPERTY(meta = (DataflowOutput, DataflowPassthrough = "Inputs[0]"))`
- L80 _private prototype_ `virtual TArray<UE::Dataflow::FPin> AddPins() override;`
- L81 _private function_ `virtual bool CanAddPin() const override`
- L82 _private function_ `virtual bool CanRemovePin() const override`
- L83 _private prototype_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const override;`
- L84 _private prototype_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin) override;`
- L85 _private prototype_ `virtual void PostSerialize(const FArchive& Ar) override;`
- L87 _private prototype_ `UE::Dataflow::TConnectionReference<FDataflowAnyType> GetConnectionReference(int32 Index) const;`
- L89 _private member_ `static constexpr int32 NumRequiredDataflowInputs = 1;`
- L90 _private member_ `static constexpr int32 NumInitialInputs = 2;`
- L91 _private member_ `static const FName MainTypeGroup;`

#### struct `FDataflowPrintNode`  
`struct FDataflowPrintNode : public FDataflowNode`  
_L99-112_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Print value in the log Supports any type comnvertible to a string
- L106 _public prototype_ `FDataflowPrintNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid());`
- L107 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const;`
- L111 _public member_ `FDataflowStringConvertibleTypes Value;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Value", DisplayName = "Value"))`

#### struct `FDataflowForceDependencyNode`  
`struct FDataflowForceDependencyNode : public FDataflowNode`  
_L118-138_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Force an evaluation dependency between two values
- L125 _public prototype_ `FDataflowForceDependencyNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid());`
- L126 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const;`
- L133 _public member_ `FDataflowAnyType Value;` — `UPROPERTY(meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Value"))` — Evaluating Value will force an evaluation of DependentValue
- L137 _public member_ `FDataflowAnyType DependentValue;` — `UPROPERTY(meta = (DataflowInput))` — Evaluating Value will force an evaluation of DependentValue

#### Free symbols / members of external scopes

- L140 _namespace_ `namespace UE`
- L140 _namespace_ `namespace Dataflow` (scope `UE`)
- L142 _prototype_ `void RegisterCoreNodes();` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowDebugDrawInterface.h` (Public)


#### struct `IDataflowDebugDrawObject`  
`struct IDataflowDebugDrawObject : public FRefCountedObject`  
_L13-21_
- inherits: `FRefCountedObject`
- desc: Dataflow object debug draw interface
- L15 _public prototype_ `virtual ~IDataflowDebugDrawObject() = default;`
- L17 _public function_ `static FName StaticType()`
- L20 _public function_ `virtual bool IsA(FName InType) const` — Check of the object type

#### class `IDataflowDebugDrawInterface`  
`class IDataflowDebugDrawInterface: public Chaos::IDebugDrawInterface`  
_L23-44_
- inherits: `Chaos::IDebugDrawInterface`
- L26 _public typedef_ `using FDataflowElementsType = TArray<TSharedPtr<FDataflowBaseElement>>;`
- L28 _public prototype_ `virtual ~IDataflowDebugDrawInterface() = default;`
- L31 _public prototype_ `virtual void DrawObject(const TRefCountPtr<IDataflowDebugDrawObject>& Object) = 0;` — Draw a Dataflow debug draw object ( for example skeleton bones )
- L34 _public prototype_ `virtual void DrawOverlayText(const FString& InString) = 0;` — Render a string a part of the Dataflow construction view overlay
- L37 _public prototype_ `virtual FString GetOverlayText() const = 0;` — Get the text overlay string ( concatenated string from DrawOverlayText calls )
- L40 _public prototype_ `virtual FDataflowElementsType& ModifyDataflowElements() = 0;` — Dataflow elements non const accessor
- L43 _public prototype_ `virtual const FDataflowElementsType& GetDataflowElements() const = 0;` — Dataflow elements const accessor

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowDynamicMeshDebugDrawMesh.h` (Public)


#### struct `FDynamicMeshDebugDrawMesh`  
`struct FDynamicMeshDebugDrawMesh : public IDataflowDebugDrawInterface::IDebugDrawMesh`  
_L7-24_
- inherits: `IDataflowDebugDrawInterface::IDebugDrawMesh`
- L9 _public prototype_ `FDynamicMeshDebugDrawMesh(const class UE::Geometry::FDynamicMesh3* DynamicMesh);`
- L11 _public prototype_ `virtual ~FDynamicMeshDebugDrawMesh() = default;`
- L13 _public prototype_ `virtual int32 GetMaxVertexIndex() const override;`
- L14 _public prototype_ `virtual bool IsValidVertex(int32 VertexIndex) const override;`
- L15 _public prototype_ `virtual FVector GetVertexPosition(int32 VertexIndex) const override;`
- L16 _public prototype_ `virtual FVector GetVertexNormal(int32 VertexIndex) const override;`
- L18 _public prototype_ `virtual int32 GetMaxTriangleIndex() const override;`
- L19 _public prototype_ `virtual bool IsValidTriangle(int32 VertexIndex) const override;`
- L20 _public prototype_ `virtual FIntVector3 GetTriangle(int32 VertexIndex) const override;`
- L23 _private member_ `const class UE::Geometry::FDynamicMesh3* DynamicMesh;`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowElement.h` (Public)


#### struct `FDataflowBaseElement`  
`struct FDataflowBaseElement`  
_L11-44_
- reflection: `USTRUCT()`
- desc: Base dataflow scene element that could be used in outliner and for rendering
- L15 _public function_ `FDataflowBaseElement()`
- L17 _public function_ `FDataflowBaseElement(const FString& InElementName, FDataflowBaseElement* InParentElement, const FBox& InBoundingBox, const bool bInIsConstruction) : ElementName(InElementName), ParentElement(InParentElement), BoundingBox(InBoundingBox), bIsConstruction(bInIsConstruction)`
- L20 _public prototype_ `virtual ~FDataflowBaseElement() = default;`
- L22 _public function_ `static FName StaticType()`
- L25 _public function_ `virtual bool IsA(FName InType) const` — Check of the element type
- L28 _public member_ `FString ElementName = "No` — Element name to be used to retrieve
- L31 _public member_ `FDataflowBaseElement* ParentElement = nullptr;` — Parent element to build the hierarchy if necessary
- L34 _public member_ `FBox BoundingBox = FBox();` — Bounding box to focus
- L37 _public member_ `bool bIsConstruction = true;` — Construction flag
- L40 _public member_ `bool bIsVisible = true;` — Visible flag to enable/disable the rendering
- L43 _public member_ `bool bIsSelected = false;` — Selection flag

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowFunctionProperty.h` (Public)


#### struct `FDataflowFunctionProperty`  
`struct FDataflowFunctionProperty`  
_L45-60_
- reflection: `USTRUCT()`
- desc: Function property for all Dataflow nodes. The structure is also used in DataFlow::FFunctionPropertyCustomization to appear as text and/or image buttons. This helps with the equivalent UCLASS UFUNCTION CallInEditor functionality that is missing from the USTRUCT implementation. By default the text of the button is the name of the structure property. The tooltip is the property source documentation. Further (but optional) customizations can be achieved by using the following Meta tags where declaring the property: DisplayName ButtonImage Specifying an empty DisplayName string will only display the icon and no text. For example: UPROPERTY(EditAnywhere, Category = "Functions") FDataflowFunctionProperty ReimportAssetTextOnly; UPROPERTY(EditAnywhere, Category = "Functions", Meta = (ButtonImage = "Persona.ReimportAsset")) FDataflowFunctionProperty ReimportAssetTextAndIcon; UPROPERTY(EditAnywhere, Category = "Functions", Meta = (DisplayName = "", ButtonImage = "Persona.ReimportAsset")) FDataflowFunctionProperty ReimportAssetIconOnly; UPROPERTY(EditAnywhere, Category = "Functions", Meta = (DisplayName = "Reimport Asset")) FDataflowFunctionProperty ReimportAssetOverriddenText; UPROPERTY(EditAnywhere, Category = "Functions", Meta = (DisplayName = "Reimport Asset", ButtonImage = "Persona.ReimportAsset")) FDataflowFunctionProperty ReimportAssetOverriddenTextAndIcon;
- L50 _public prototype_ `DECLARE_DELEGATE_OneParam(FDelegate, UE::Dataflow::FContext&);`
- L52 _public prototype_ `FDataflowFunctionProperty() = default;`
- L54 _public function_ `explicit FDataflowFunctionProperty(FDelegate&& InDelegate) : Delegate(MoveTemp(InDelegate))`
- L56 _public function_ `void Execute(UE::Dataflow::FContext& Context) const`
- L59 _private member_ `FDelegate Delegate;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Dataflow` (scope `UE`)
- L50 _delegate_ `DECLARE_DELEGATE_OneParam(FDelegate, UE::Dataflow::FContext&);`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowGeneratorNodes.h` (Public)


#### struct `IDataflowValueGenerator`  
`struct IDataflowValueGenerator`  
_L10-13_
- L12 _public prototype_ `virtual void GenerateValues(TArray<double>& InOutValues) const = 0;`

#### struct `FDataflowValueGenerator`  
`struct FDataflowValueGenerator`  
_L16-29_
- reflection: `USTRUCT()`
- L21 _public function_ `FDataflowValueGenerator(TSharedPtr<IDataflowValueGenerator> InGenerator = {}) : Generator(InGenerator)`
- L25 _public prototype_ `void GenerateValues(TArray<double>& InOutValues) const;`
- L28 _private member_ `TSharedPtr<IDataflowValueGenerator> Generator;`

#### struct `FDataflowRandomGeneratorNode`  
`struct FDataflowRandomGeneratorNode : public FDataflowNode`  
_L37-61_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Generator to generate a random sequence
- L43 _public prototype_ `FDataflowRandomGeneratorNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid());`
- L44 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const;`
- L48 _public member_ `int32 Seed = 0;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput))`
- L51 _public member_ `FDataflowNumericTypes RandomMin;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput))`
- L54 _public member_ `FDataflowNumericTypes RandomMax;` — `UPROPERTY(EditAnywhere, Category = "Random", meta = (DataflowInput))`
- L57 _public member_ `bool bReverseOrder = false;` — `UPROPERTY(EditAnywhere, Category = "Random")`
- L60 _public member_ `FDataflowValueGenerator Generator;` — `UPROPERTY(meta = (DataflowOutput))`

#### struct `FDataflowLinearSequenceGeneratorNode`  
`struct FDataflowLinearSequenceGeneratorNode : public FDataflowNode`  
_L69-90_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Generator to generate a linear sequence
- L75 _public prototype_ `FDataflowLinearSequenceGeneratorNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid());`
- L76 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const;`
- L80 _public member_ `FDataflowNumericTypes Start;` — `UPROPERTY(EditAnywhere, Category = "Sequence", meta = (DataflowInput))`
- L83 _public member_ `FDataflowNumericTypes Increment;` — `UPROPERTY(EditAnywhere, Category = "Sequence", meta = (DataflowInput))`
- L86 _public member_ `bool bReverseOrder = false;` — `UPROPERTY(EditAnywhere, Category = "Sequence")`
- L89 _public member_ `FDataflowValueGenerator Generator;` — `UPROPERTY(meta = (DataflowOutput))`

#### struct `FDataflowPerlinNoiseGeneratorNode`  
`struct FDataflowPerlinNoiseGeneratorNode : public FDataflowNode`  
_L98-128_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Generator to generate a sequence from Perlin noise
- L104 _public prototype_ `FDataflowPerlinNoiseGeneratorNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid());`
- L105 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const;`
- L109 _public member_ `float Frequency = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Perlin", meta = (DataflowInput, UIMin = 0.01, ClampMin = 0.01))`
- L112 _public member_ `float Offset = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Perlin", meta = (DataflowInput))`
- L115 _public member_ `float NoiseMin = -1.0;` — `UPROPERTY(EditAnywhere, Category = "Perlin", meta = (DataflowInput))`
- L118 _public member_ `float NoiseMax = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Perlin", meta = (DataflowInput))`
- L121 _public member_ `bool bClamp = false;` — `UPROPERTY(EditAnywhere, Category = "Perlin")`
- L124 _public member_ `bool bReverseOrder = false;` — `UPROPERTY(EditAnywhere, Category = "Perlin")`
- L127 _public member_ `FDataflowValueGenerator Generator;` — `UPROPERTY(meta = (DataflowOutput))`

#### struct `FDataflowSimpleRegexGeneratorNode`  
`struct FDataflowSimpleRegexGeneratorNode : public FDataflowNode`  
_L137-155_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: Generator to generate a sequence from a simple regex Example: "0, 2, 5-10, 12-15"
- L143 _public prototype_ `FDataflowSimpleRegexGeneratorNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid());`
- L144 _public prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const;`
- L148 _public member_ `FString List;` — `UPROPERTY(EditAnywhere, Category = "Regex")`
- L151 _public member_ `bool bReverseOrder = false;` — `UPROPERTY(EditAnywhere, Category = "Regex")`
- L154 _public member_ `FDataflowValueGenerator Generator;` — `UPROPERTY(meta = (DataflowOutput))`

#### Free symbols / members of external scopes

- L159 _namespace_ `namespace UE`
- L159 _namespace_ `namespace Dataflow` (scope `UE`)
- L161 _prototype_ `void RegisterGeneratorNodes();` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowGraph.h` (Public)


#### class `UDataflowGraphInterface`  
`class UDataflowGraphInterface : public UInterface`  
_L25-28_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: Interface for objects that owns a dataflow graph

#### class `IDataflowGraphInterface`  
`class IDataflowGraphInterface`  
_L30-36_
- L35 _public prototype_ `virtual TSharedPtr<UE::Dataflow::FGraph> GetDataflowGraph() const = 0;`

#### struct `UE::Dataflow::FLink`  
`struct FLink`  
_L44-71_
- desc: A link structure defines a connection between one output and one input of two separate Dataflow nodes The Guids are the unique identifiers of the node and inputs/outputs in the dataflow graph (see FGraph class below)
- L46 _public member_ `FGuid InputNode;`
- L47 _public member_ `FGuid Input;`
- L48 _public member_ `FGuid OutputNode;`
- L49 _public member_ `FGuid Output;`
- L51 _public prototype_ `FLink() = default;`
- L53 _public function_ `FLink(FGuid InOutputNode, FGuid InOutput, FGuid InInputNode, FGuid InInput) : InputNode(InInputNode), Input(InInput) , OutputNode(InOutputNode), Output(InOutput)`
- L57 _public function_ `FLink(const FLink& Other) : InputNode(Other.InputNode), Input(Other.Input) , OutputNode(Other.OutputNode), Output(Other.Output)`
- L61 _public function_ `bool operator==(const FLink& Other) const`
- L66 _public function_ `bool Equals(const FLink& Other) const`

#### class `UE::Dataflow::FGraph`  
`class FGraph`  
_L78-207_
- desc: A Dataflow graph is a collection of interconnected nodes Each node has aunique Guid and name and a list of inputs and outputs ( see FDataflowNode )
- L81 _public typedef_ `using FNodeSharedPtr = TSharedPtr<FDataflowNode>;`
- L82 _public typedef_ `using FConstNodeSharedPtr = TSharedPtr<const FDataflowNode>;`
- L85 _private member_ `FGuid Guid;`
- L86 _private member_ `TArray<FNodeSharedPtr> Nodes;`
- L87 _private member_ `TMap<FName, TArray<FNodeSharedPtr>> FilteredNodes;`
- L88 _private member_ `TArray<FLink> Connections;`
- L89 _private member_ `TSet<FName> DisabledNodes;`
- L95 _private member_ `FGuid GraphTopologyGuid;` — This guid changes whenever the topology of the graph changes (Add/Remove nodes, Connect/Disconnect input and/or outputs)
- L98 _private member_ `static TSet<FName> RegisteredFilters;` — Node filter type that could be used for fast access
- L104 _public prototype_ `FGraph(FGuid InGuid = FGuid::NewGuid());`
- L105 _public prototype_ `virtual ~FGraph() = default;`
- L108 _public prototype_ `const TArray<FNodeSharedPtr>& GetFilteredNodes(const FName& NodeFilter) const;` — Get the list of node matching a specific named filter (@see RegisterNodeFilter)
- L114 _public function_ `const TArray<FNodeSharedPtr>& GetNodes() const` — Get all the nodes of the graph ( const method ) this includes the node in all subgraphs
- L120 _public function_ `TArray<FNodeSharedPtr>& GetNodes()` — Get all the nodes of the graph ( non-const method ) this includes the node in all subgraphs
- L123 _public function_ `int32 NumNodes()` — Get the number of nodes in the graph including the ones in the subgraphs
- L127 _public function_ `TSharedPtr<T> AddNode(T* InNode)` — `UE_DEPRECATED(5.8, "Use the Shared pointer parameter version of AddNode instead")`
- L136 _public function_ `TSharedPtr<T> AddNode(TUniquePtr<T> &&InNode)` — `UE_DEPRECATED(5.8, "Use the Shared pointer parameter version of AddNode instead")`
- L144 _public prototype_ `FNodeSharedPtr AddNode(FNodeSharedPtr NewNode);` — Add a new Dataflow node to the graph
- L147 _public prototype_ `FNodeSharedPtr FindBaseNode(FGuid InGuid);` — Find a node by its unique identifier (non-const method)
- L150 _public prototype_ `FConstNodeSharedPtr FindBaseNode(FGuid InGuid) const;` — Find a node by its unique identifier (const method)
- L153 _public prototype_ `FNodeSharedPtr FindBaseNode(FName InName);` — Find a node by its name (non-const method)
- L156 _public prototype_ `FConstNodeSharedPtr FindBaseNode(FName InName) const;` — Find a node by its name (const method)
- L159 _public prototype_ `FNodeSharedPtr FindFilteredNode(const FName& NodeFilter, FName InName) const;` — Find a node by name from a named filter (@see RegisterNodeFilter method)
- L166 _public prototype_ `void RemoveNode(FNodeSharedPtr Node);` — Remove a specific node from the graph Removal of the node will automatically disconnect the inputs and outputs this will also remove the node from any filters it may be in
- L172 _public function_ `const TArray<FLink>& GetConnections() const` — Get all the graph connections This includes all the subgraph connections as well
- L174 _public prototype_ `void ClearConnections(FDataflowConnection* ConnectionBase);`
- L175 _public prototype_ `void ClearConnections(FDataflowInput* Input);`
- L176 _public prototype_ `void ClearConnections(FDataflowOutput* Output);`
- L186 _public prototype_ `bool CanConnect(const FDataflowOutput& Output, const FDataflowInput& Input) const;`
- L187 _public prototype_ `EConnectType GetConnectType(const FDataflowOutput& Output, const FDataflowInput& Input) const;`
- L188 _public prototype_ `bool Connect(FDataflowOutput& Output, FDataflowInput& Input);`
- L190 _public prototype_ `bool Connect(FDataflowConnection* ConnectionA, FDataflowConnection* ConnectionB);`
- L191 _public prototype_ `void Connect(FDataflowOutput* OutputConnection, FDataflowInput* InputConnection);`
- L192 _public prototype_ `void Disconnect(FDataflowOutput* OutputConnection, FDataflowInput* InputConnection);`
- L194 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);`
- L196 _public prototype_ `virtual void Serialize(FArchive& Ar, UObject* OwningObject);`
- L197 _public function_ `const TSet<FName>& GetDisabledNodes() const`
- L199 _public prototype_ `static void SerializeForSaving(FArchive& Ar, FGraph* InGraph, TArray<TSharedPtr<FDataflowNode>>& InNodes, TArray<FLink>& InConnections);`
- L200 _public prototype_ `static void SerializeForLoading(FArchive& Ar, FGraph* InGraph, UObject* OwningObject);`
- L202 _public function_ `const FGuid& GetGraphTopologyGuid() const`
- L205 _private prototype_ `void Reset();`
- L206 _private prototype_ `void OnChangeGraphTopology();`

#### enum `UE::Dataflow::FGraph::EConnectType`  
`enum class EConnectType : uint8`  
_L178-184_
- L180 _public enumerator_ `REJECTED = 0`
- L181 _public enumerator_ `DIRECT` — both are already compatible
- L182 _public enumerator_ `INPUT_PROMOTION` — input can be changed to adapt the output type
- L183 _public enumerator_ `OUTPUT_PROMOTION` — output can be changed to adapt the input type

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API DATAFLOWCORE_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Dataflow` (scope `UE`)
- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace Dataflow` (scope `UE`)
- L209 _prototype_ `void RegisterNodeFilter(const FName& NodeFilter);` (scope `UE::Dataflow`)
- L213 _function_ `inline FArchive& operator<<(FArchive& Ar, UE::Dataflow::FLink& Value)`
- L219 _function_ `inline FArchive& operator<<(Chaos::FChaosArchive& Ar, UE::Dataflow::FLink& Value)`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowImage.h` (Public)


#### enum `EDataflowImageResolution`  
`enum class EDataflowImageResolution : int32`  
_L10-22_
- reflection: `UENUM()`
- L12 _public enumerator_ `Resolution16 = 16 UMETA(DisplayName = "16 x 16")`
- L13 _public enumerator_ `Resolution32 = 32 UMETA(DisplayName = "32 x 32")`
- L14 _public enumerator_ `Resolution64 = 64 UMETA(DisplayName = "64 x 64")`
- L15 _public enumerator_ `Resolution128 = 128 UMETA(DisplayName = "128 x 128")`
- L16 _public enumerator_ `Resolution256 = 256 UMETA(DisplayName = "256 x 256")`
- L17 _public enumerator_ `Resolution512 = 512 UMETA(DisplayName = "512 x 512")`
- L18 _public enumerator_ `Resolution1024 = 1024 UMETA(DisplayName = "1024 x 1024")`
- L19 _public enumerator_ `Resolution2048 = 2048 UMETA(DisplayName = "2048 x 2048")`
- L20 _public enumerator_ `Resolution4096 = 4096 UMETA(DisplayName = "4096 x 4096")`
- L21 _public enumerator_ `Resolution8192 = 8192 UMETA(DisplayName = "8192 x 8192")`

#### enum `EDataflowImageChannel`  
`enum class EDataflowImageChannel : int32`  
_L25-31_
- reflection: `UENUM()`
- L27 _public enumerator_ `Red = 0 UMETA(DisplayName = "Red Channel")`
- L28 _public enumerator_ `Green = 1 UMETA(DisplayName = "Green Channel")`
- L29 _public enumerator_ `Blue = 2 UMETA(DisplayName = "Blue Channel")`
- L30 _public enumerator_ `Alpha = 3 UMETA(DisplayName = "Alpha Channel")`

#### struct `FDataflowImage`  
`struct FDataflowImage`  
_L38-104_
- reflection: `USTRUCT()`
- desc: Represents image for dataflow type is constrained to Float32 with 1 or 4 channels
- L42 _public prototype_ `int32 GetWidth() const;`
- L43 _public prototype_ `int32 GetHeight() const;`
- L46 _public prototype_ `const FImage& GetImage() const;` — get the readonly underlying image object
- L49 _public prototype_ `void CreateR32F(EDataflowImageResolution Resolution, TArrayView64<float> InPixels = {});` — Create a single channel float format image
- L52 _public prototype_ `void CreateR32F(int32 Width, int32 Height, TArrayView64<float> InPixels = {});` — Create a single channel float format image
- L55 _public prototype_ `void CreateRGBA32F(EDataflowImageResolution Resolution, TArrayView64<FVector4f> InPixels = {});` — Create a four channels float format image
- L58 _public prototype_ `void CreateRGBA32F(int32 Width, int32 Height, TArrayView64<FVector4f> InPixels = {});` — Create a four channels float format image
- L61 _public prototype_ `void CreateFromColor(EDataflowImageResolution Resolution, FLinearColor Color);` — Create a four channels float format image filled with a specific color
- L64 _public prototype_ `void CreateFromColor(int32 Width, int32 Height, FLinearColor Color);` — Create a four channels float format image filled with a specific color
- L71 _public prototype_ `bool CopyPixels(TArrayView64<float> Pixels);` — Copy R32F pixels to the image Number of pixels must match and format must be R32F return false if the copy could not be done
- L78 _public prototype_ `bool CopyPixels(TArrayView64<FVector4f> Pixels);` — Copy RGBA32F pixels to the image Number of pixels must match and format must be RGBA32F return false if the copy could not be done
- L79 _public prototype_ `bool CopyRGBAPixels(TArrayView64<FVector4f> Pixels);`
- L85 _public prototype_ `void ConvertToRGBA32F();` — Convert the current image to a 4 channel float pixel format previous data is kept
- L87 _public prototype_ `bool Serialize(FArchive& Ar);`
- L93 _public prototype_ `void ReadChannel(EDataflowImageChannel Channel, FDataflowImage& OutImage) const;` — Get a specific color channel and copy it to an image Warning : the outImage will be resized to the size of the current image and any previously store data will be lost
- L100 _public prototype_ `void WriteChannel(EDataflowImageChannel Channel, const FDataflowImage& SrcImage);` — write to a sepcific channel from an existing image if the source image is not the same size it will be resized to adapt the size of the current image if the source image is not a greyscale image it will be converted to greyscale before copy the data to the channel
- L103 _private member_ `FImage Image;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDataflowImage> : public TStructOpsTypeTraitsBase2<FDataflowImage>`  
_L106-112_
- inherits: `TStructOpsTypeTraitsBase2<FDataflowImage>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L109-111_

#### Free symbols / members of external scopes

- L110 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon5f92c6fc0103`)

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowInputOutput.h` (Public)


#### struct `UE::Dataflow::FInputParameters`  
`struct FInputParameters : public FConnectionParameters`  
_L23-28_
- inherits: `FConnectionParameters`
- L25 _public function_ `FInputParameters(FName InType = NAME_None, FName InName = NAME_None, FDataflowNode* InOwner = nullptr, const FProperty* InProperty = nullptr, uint32 InOffset = INDEX_NONE, FGuid InGuid = FGuid::NewGuid()) : FConnectionParameters(InType, InName, InOwner, InProperty, InOffset, InGuid)`

#### struct `UE::Dataflow::FArrayInputParameters`  
`struct FArrayInputParameters : public FInputParameters`  
_L30-37_
- inherits: `FInputParameters`
- L32 _public function_ `FArrayInputParameters() : FInputParameters()`
- L35 _public member_ `const FArrayProperty* ArrayProperty = nullptr;`
- L36 _public member_ `uint32 InnerOffset = INDEX_NONE;`

#### struct `FDataflowInput`  
`struct FDataflowInput : public FDataflowConnection`  
_L41-103_
- reflection: `USTRUCT()`
- inherits: `FDataflowConnection`
- L45 _public member_ `static FDataflowInput NoOpInput;`
- L49 _public member_ `FDataflowOutput* Connection = nullptr ;`
- L53 _protected prototype_ `virtual void FixAndPropagateType(FName InType) override;`
- L57 _private member_ `bool bIsRequired = false;` — if the Input has DATAFLOW_INTRINSIC metatag specified
- L58 _private prototype_ `void CheckRequired(UE::Dataflow::FContext& Context) const;`
- L61 _public prototype_ `FDataflowInput(const UE::Dataflow::FInputParameters& Param = {});`
- L63 _public prototype_ `virtual bool IsConnected() const override;`
- L64 _public prototype_ `virtual bool AddConnection(FDataflowConnection* InOutput) override;`
- L65 _public prototype_ `virtual bool RemoveConnection(FDataflowConnection* InOutput) override;`
- L67 _public prototype_ `virtual void GetConnections(TArray<FDataflowConnection*>& OutConnections) const override;`
- L69 _public function_ `FDataflowOutput* GetConnection()`
- L70 _public function_ `const FDataflowOutput* GetConnection() const`
- L71 _public function_ `bool HasAnyConnections() const`
- L73 _public prototype_ `virtual TArray< FDataflowOutput* > GetConnectedOutputs();`
- L74 _public prototype_ `virtual const TArray< const FDataflowOutput* > GetConnectedOutputs() const;`
- L81 _public prototype_ `template<class T> const T& GetValue(UE::Dataflow::FContext& Context, const T& Default) const;` — Get the value of this input by evaluating the value of the connected output @return the typed value of the input
- L84 _public prototype_ `template<typename TAnyType UE_REQUIRES(!std::is_same_v<typename TAnyType::FStorageType, void>)> typename TAnyType::FStorageType GetValueFromAnyType(UE::Dataflow::FContext& Context, const typename TAnyType::FStorageType& Default) const;`
- L87 _public prototype_ `template<typename TAnyType UE_REQUIRES(std::is_same_v<typename TAnyType::FStorageType, void>)> typename UE::Dataflow::FContextValue GetValueFromAnyType(UE::Dataflow::FContext& Context) const;`
- L93 _public prototype_ `void PullValue(UE::Dataflow::FContext& Context) const;` — pull the value from the upstream connections the upstream graph is evaluated if necessary and values are cached along the way
- L97 _public prototype_ `TFuture<const T&> GetValueParallel(UE::Dataflow::FContext& Context, const T& Default) const;` — `UE_DEPRECATED(5.8, "This code path is not supported, use context to evaluate nodes and connections asynchronously")`
- L99 _public prototype_ `virtual void Invalidate(const UE::Dataflow::FTimestamp& ModifiedTimestamp = UE::Dataflow::FTimestamp::Current()) override;`
- L101 _public function_ `bool IsRequired() const`
- L102 _public function_ `void SetIsRequired(const bool bInIsRequired)`
- L393 _function_ `template<typename T> const T& FDataflowInput::GetValue(UE::Dataflow::FContext& Context, const T& Default) const`
- L416 _function_ `template<typename TAnyType UE_REQUIRES(!std::is_same_v<typename TAnyType::FStorageType, void>)> typename TAnyType::FStorageType FDataflowInput::GetValueFromAnyType(UE::Dataflow::FContext& Context, const typename TAnyType::FStorageType& Default) const`
- L448 _function_ `template<typename TAnyType UE_REQUIRES(std::is_same_v<typename TAnyType::FStorageType, void>)> typename UE::Dataflow::FContextValue FDataflowInput::GetValueFromAnyType(UE::Dataflow::FContext& Context) const`
- L469 _function_ `TFuture<const T&> FDataflowInput::GetValueParallel(UE::Dataflow::FContext& Context, const T& Default) const` — `UE_DEPRECATED(5.8, "This code path is not supported, use context to evaluate nodes and connections asynchronously")`

#### struct `FDataflowArrayInput`  
`struct FDataflowArrayInput : public FDataflowInput`  
_L106-122_
- reflection: `USTRUCT()`
- inherits: `FDataflowInput`
- L111 _private member_ `int32 Index;`
- L112 _private member_ `uint32 ElementOffset;` — Offset to Property inside an array element
- L113 _private member_ `const FArrayProperty* ArrayProperty = nullptr;`
- L117 _public prototype_ `explicit FDataflowArrayInput(int32 InIndex = INDEX_NONE, const UE::Dataflow::FArrayInputParameters& Param = {});`
- L119 _public prototype_ `virtual void* RealAddress() const override;`
- L120 _public function_ `virtual int32 GetContainerIndex() const override`
- L121 _public function_ `virtual uint32 GetContainerElementOffset() const override`

#### struct `UE::Dataflow::FOutputParameters`  
`struct FOutputParameters: public FConnectionParameters`  
_L129-134_
- inherits: `FConnectionParameters`
- L131 _public function_ `FOutputParameters(FName InType = NAME_None, FName InName = NAME_None, FDataflowNode* InOwner = nullptr, const FProperty* InProperty = nullptr, uint32 InOffset = INDEX_NONE, FGuid InGuid = FGuid::NewGuid()) : FConnectionParameters(InType, InName, InOwner, InProperty, InOffset, InGuid)`

#### struct `UE::Dataflow::FArrayOutputParameters`  
`struct FArrayOutputParameters : public FOutputParameters`  
_L136-143_
- inherits: `FOutputParameters`
- L138 _public function_ `FArrayOutputParameters() : FOutputParameters()`
- L141 _public member_ `const FArrayProperty* ArrayProperty = nullptr;`
- L142 _public member_ `uint32 InnerOffset = INDEX_NONE;`

#### struct `FDataflowOutput`  
`struct FDataflowOutput : public FDataflowConnection`  
_L147-354_
- reflection: `USTRUCT()`
- inherits: `FDataflowConnection`
- L153 _public member_ `TArray< FDataflowInput* > Connections;`
- L155 _public member_ `UE::Dataflow::FConnectionKey PassthroughKey;`
- L159 _protected prototype_ `virtual void FixAndPropagateType(FName InType) override;`
- L162 _public member_ `static FDataflowOutput NoOpOutput;`
- L164 _public member_ `mutable TSharedPtr<FCriticalSection> OutputLock;`
- L166 _public prototype_ `FDataflowOutput(const UE::Dataflow::FOutputParameters& Param = {});`
- L169 _public prototype_ `~FDataflowOutput() = default;`
- L170 _public prototype_ `FDataflowOutput(const FDataflowOutput&) = delete;`
- L171 _public prototype_ `FDataflowOutput(FDataflowOutput&&) = delete;`
- L172 _public prototype_ `FDataflowOutput& operator=(const FDataflowOutput&) = delete;`
- L173 _public prototype_ `FDataflowOutput& operator=(FDataflowOutput&&) = delete;`
- L176 _public prototype_ `TArray<FDataflowInput*>& GetConnections();`
- L177 _public prototype_ `const TArray<FDataflowInput*>& GetConnections() const;`
- L178 _public function_ `bool HasAnyConnections() const`
- L179 _public function_ `virtual bool IsConnected() const override`
- L181 _public prototype_ `virtual TArray<FDataflowInput*> GetConnectedInputs();`
- L182 _public prototype_ `virtual const TArray<const FDataflowInput*> GetConnectedInputs() const;`
- L184 _public prototype_ `virtual bool AddConnection(FDataflowConnection* InOutput) override;`
- L186 _public prototype_ `virtual bool RemoveConnection(FDataflowConnection* InInput) override;`
- L188 _public prototype_ `virtual void GetConnections(TArray<FDataflowConnection*>& OutConnections) const override;`
- L190 _public prototype_ `FDataflowOutput& SetPassthroughInput(const UE::Dataflow::FConnectionReference& Reference);`
- L191 _public prototype_ `FDataflowOutput& SetPassthroughInput(const UE::Dataflow::FConnectionKey& Key);`
- L193 _public prototype_ `const FDataflowInput* GetPassthroughInput() const;`
- L195 _public function_ `virtual void* GetPassthroughRealAddress() const`
- L205 _public function_ `template<class T> void SetValue(T&& InVal, UE::Dataflow::FContext& Context) const`
- L213 _public function_ `void SetValueFromStructView(const FConstStructView& StructView, UE::Dataflow::FContext& Context) const`
- L221 _public function_ `void SetValueFromStructArrayView(const FConstStructArrayView& StructArrayView, UE::Dataflow::FContext& Context) const`
- L230 _public function_ `template<typename TAnyType> void SetValueFromAnyType(const typename TAnyType::FStorageType& InVal, UE::Dataflow::FContext& Context) const`
- L244 _public prototype_ `void SetNullValue(UE::Dataflow::FContext& Context) const;` — Set a null value : this means that the connected input will get a default value and that this output will not be set re-evaluate next time
- L253 _public function_ `template<class T, typename = std::enable_if_t<!std::is_base_of_v<FDataflowAnyType, T>>> const T& ReadValue(UE::Dataflow::FContext& Context, const T& Default) const` — Read value returns the cache value on the output without causing an evaluation of the corresponding node as a result it does not cause a cascading evaluation of the graph if there's no cached value this will return the default value passed as a parameter @see GetValue
- L267 _public function_ `template<typename TAnyType, typename = std::enable_if_t<std::is_base_of_v<FDataflowAnyType, TAnyType>>> typename TAnyType::FStorageType ReadValue(UE::Dataflow::FContext& Context, const typename TAnyType::FStorageType& Default) const`
- L298 _public function_ `template<class T> const T& GetValue(UE::Dataflow::FContext& Context, const T& Default) const` — Get most updated value of the output if the value is cache or frozen return it otherwise evaluates the node with potentially cascading evaluation of the graph @see GetValue
- L319 _public function_ `template<class T> const T& GetFrozenValue(const T& Default) const` — Return a pointer to the node's output storage if it has been successfully evaluated and frozen, or the provided default value otherwise.
- L324 _public prototype_ `void Freeze(UE::Dataflow::FContext& Context, struct FInstancedPropertyBag& FrozenProperties);` — Freeze the value of this output to the node property bag.
- L326 _public prototype_ `bool HasFrozenValue() const;` — Return whether the output has a frozen value in its owner node.
- L328 _public function_ `bool HasCachedValue(const UE::Dataflow::FContext& Context) const`
- L335 _public prototype_ `void ForwardInput(const UE::Dataflow::FConnectionReference& InputReference, UE::Dataflow::FContext& Context) const;` — there's no need for a templatized version as the parameter will not be used the method do check if the type of the input is the same as the output type though
- L336 _public prototype_ `void ForwardInput(const FDataflowInput* Input, UE::Dataflow::FContext& Context) const;`
- L338 _public prototype_ `bool HasValidData(UE::Dataflow::FContext& Context) const;`
- L340 _public prototype_ `bool EvaluateImpl(UE::Dataflow::FContext& Context) const;`
- L342 _public prototype_ `bool Evaluate(UE::Dataflow::FContext& Context) const;`
- L345 _public prototype_ `TFuture<bool> EvaluateParallel(UE::Dataflow::FContext& Context) const;` — `UE_DEPRECATED(5.8, "This code path is not supported, use context to evaluate nodes and connections asynchronously")`
- L347 _public prototype_ `virtual void Invalidate(const UE::Dataflow::FTimestamp& ModifiedTimestamp = UE::Dataflow::FTimestamp::Current()) override;`
- L350 _public prototype_ `bool HasNodeFailedOrErrored(UE::Dataflow::FContext& Context) const;` — `UE_DEPRECATED(5.8, "HasNodeFailedOrErrored is deprecated and will only return false, failure or error of node should be done by listening to the context log messages")`
- L353 _private prototype_ `const uint8* GetFrozenPropertyValue(const uint8* Default) const;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDataflowOutput> : public TStructOpsTypeTraitsBase2<FDataflowOutput>`  
_L357-363_
- inherits: `TStructOpsTypeTraitsBase2<FDataflowOutput>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L360-362_

#### struct `FDataflowArrayOutput`  
`struct FDataflowArrayOutput : public FDataflowOutput`  
_L366-381_
- reflection: `USTRUCT()`
- inherits: `FDataflowOutput`
- L371 _private member_ `int32 Index;`
- L372 _private member_ `uint32 ElementOffset;` — Offset to Property inside an array element
- L373 _private member_ `const FArrayProperty* ArrayProperty = nullptr;`
- L376 _public prototype_ `explicit FDataflowArrayOutput(int32 InIndex = INDEX_NONE, const UE::Dataflow::FArrayOutputParameters& Param = {});`
- L378 _public prototype_ `virtual void* RealAddress() const override;`
- L379 _public function_ `virtual int32 GetContainerIndex() const override`
- L380 _public function_ `virtual uint32 GetContainerElementOffset() const override`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDataflowArrayOutput> : public TStructOpsTypeTraitsBase2<FDataflowArrayOutput>`  
_L384-390_
- inherits: `TStructOpsTypeTraitsBase2<FDataflowArrayOutput>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L387-389_

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Dataflow` (scope `UE`)
- L127 _namespace_ `namespace UE`
- L127 _namespace_ `namespace Dataflow` (scope `UE`)
- L234 _function_ `` (scope `FDataflowOutput::SetValueFromAnyType`)
- L235 _typedef_ `using FSingleType = typename decltype(SingleTypePolicy)::FType;` (scope `FDataflowOutput::SetValueFromAnyType::__anon1798635a0102`)
- L280 _function_ `` (scope `FDataflowOutput::ReadValue`)
- L281 _typedef_ `using FSingleType = typename decltype(SingleTypePolicy)::FType;` (scope `FDataflowOutput::ReadValue::__anon1798635a0202`)
- L361 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon1798635a0303`)
- L388 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anon1798635a0403`)
- L434 _function_ `` (scope `FDataflowInput::GetValueFromAnyType`)
- L435 _typedef_ `using FSingleType = typename decltype(SingleTypePolicy)::FType;` (scope `FDataflowInput::GetValueFromAnyType::__anon1798635a0502`)
- L471 _function_ `return Async(EAsyncExecution::TaskGraph, [&]() -> const T& { return this->GetValue<T>(Context, Default); });` (scope `FDataflowInput::GetValueParallel`)

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowNode.h` (Public)


#### struct `UE::Dataflow::FNodeParameters`  
`struct FNodeParameters`  
_L23-26_
- L24 _public member_ `FName Name;`
- L25 _public member_ `UObject* OwningObject = nullptr;`

#### struct `FDataflowNodeDelegates`  
`struct FDataflowNodeDelegates`  
_L32-39_
- L36 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNodeInvalidated, FDataflowNode&);` — Called when the node is being invalidated
- L37 _public member_ `static FOnNodeInvalidated OnNodeInvalidated;`

#### struct `FDataflowFreezeActions`  
`struct FDataflowFreezeActions final`  
_L43-46_
- reflection: `USTRUCT()`
- desc: Empty class for the freeze UI customization.

#### struct `FDataflowNode`  
`struct FDataflowNode #if CPP : public TSharedFromThis<FDataflowNode, ESPMode::ThreadSafe> #endif`  
_L58-929_
- reflection: `USTRUCT()`
- inherits: `TSharedFromThis<FDataflowNode,ESPMode::ThreadSafe>`
- desc: FNode Base class for node based evaluation within the Dataflow graph. Note : Do NOT create mutable variables in the classes derived from FDataflowNode. The state is stored on the FContext. The Evaluate is const to allow support for multithreaded evaluation.
- L71 _public member_ `bool bOverrideColor = false;` — `UE_DEPRECATED(5.7, "Will be made private in 5.9, use IsColorOverriden() instead.")` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (InlineEditConditionToggle, DisplayAfter = "bActive"))`
- L75 _public member_ `FLinearColor OverrideColor = FLinearColor::White;` — `UE_DEPRECATED(5.7, "Will be made private in 5.9, use GetOverrideColor() instead.")` — `UPROPERTY(EditAnywhere, Category = "Dataflow", meta = (EditCondition="bOverrideColor"))`
- L77 _public prototype_ `FDataflowNode();`
- L78 _public prototype_ `FDataflowNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid());`
- L81 _public function_ `virtual ~FDataflowNode()`
- L86 _public function_ `FDataflowNode& operator=(const FDataflowNode& Other)` — Warning: FDataflowNodes aren't actually safe to copy/move yet. These are here to disable deprecation warnings from the implicit operators that were getting created anyways. (Deleting the operators would require tagging all derived classes since this is a USTRUCT, so also not doing that here).
- L92 _public function_ `FGuid GetGuid() const`
- L93 _public function_ `FName GetName() const`
- L94 _public function_ `void SetName(FName InName)`
- L95 _public function_ `UE::Dataflow::FTimestamp GetTimestamp() const`
- L96 _public prototype_ `uint32 GetValueHash();`
- L98 _public function_ `static FName StaticType()`
- L99 _public function_ `virtual FName GetType() const`
- L100 _public function_ `virtual FName GetDisplayName() const`
- L101 _public function_ `virtual FName GetCategory() const`
- L102 _public function_ `virtual FString GetTags() const`
- L103 _public prototype_ `virtual FString GetToolTip() const;`
- L104 _public prototype_ `FString GetPinToolTip(const FName& PropertyName, const UE::Dataflow::FPin::EDirection Direction = UE::Dataflow::FPin::EDirection::NONE) const;`
- L105 _public prototype_ `FText GetPinDisplayName(const FName& PropertyName, const UE::Dataflow::FPin::EDirection Direction = UE::Dataflow::FPin::EDirection::NONE) const;`
- L106 _public prototype_ `TArray<FString> GetPinMetaData(const FName& PropertyName, const UE::Dataflow::FPin::EDirection Direction = UE::Dataflow::FPin::EDirection::NONE) const;`
- L107 _public function_ `virtual TArray<UE::Dataflow::FRenderingParameter> GetRenderParameters() const`
- L110 _public function_ `virtual bool HasRenderCollectionPrimitives() const` — Override if node will generate primitives from the RenderCollection.
- L129 _public function_ `virtual bool CanDebugDraw() const` — Override if DebugDraw has been implemented.
- L134 _public function_ `virtual bool CanDebugDrawViewMode(const FName& ViewModeName) const` — Specify whether or not DebugDraw supports this ViewMode
- L139 _public function_ `virtual void DebugDraw(UE::Dataflow::FContext& Context, IDataflowDebugDrawInterface& DataflowRenderingInterface, const FDebugDrawParameters& DebugDrawParameters) const` — Debug drawing callback. This will only be called for nodes which CanDebugDrawViewMode for the current view mode.
- L143 _public function_ `virtual void OnDoubleClicked(UE::Dataflow::FContext* Context) const`
- L150 _public prototype_ `TArray<UE::Dataflow::FPin> GetPins() const;`
- L153 _public function_ `virtual TArray<UE::Dataflow::FPin> AddPins()` — Override this function to add the AddOptionPin functionality to the node's context menu.
- L158 _public function_ `virtual bool CanAddPin() const` — Override this function to add the AddOptionPin functionality to the node's context menu.
- L160 _public function_ `virtual TArray<UE::Dataflow::FPin> GetPinsToRemove() const` — Override this function to add the RemoveOptionPin functionality to the node's context menu. OnPinRemoved will be called in this order.
- L168 _public function_ `virtual void OnPinRemoved(const UE::Dataflow::FPin& Pin)` — Override this to update any bookkeeping when a pin is being removed. This will be called before the pin is unregistered as an input.
- L170 _public function_ `virtual bool CanRemovePin() const` — Override this function to add the RemoveOptionPin functionality to the node's context menu.
- L173 _public prototype_ `bool InputSupportsType(FName Name, FName Type) const;`
- L174 _public prototype_ `bool OutputSupportsType(FName Name, FName Type) const;`
- L176 _public prototype_ `virtual void AddInput(FDataflowInput* InPtr);`
- L177 _public prototype_ `int32 GetNumInputs() const;`
- L178 _public prototype_ `TArray< FDataflowInput* > GetInputs() const;`
- L179 _public prototype_ `void ClearInputs();`
- L180 _public prototype_ `bool HasHideableInputs() const;`
- L181 _public prototype_ `bool HasHiddenInputs() const;`
- L183 _public prototype_ `const FDataflowConnection* FindConnection(const UE::Dataflow::FConnectionKey& Key) const;`
- L184 _public prototype_ `FDataflowConnection* FindConnection(const UE::Dataflow::FConnectionKey& Key);`
- L185 _public prototype_ `FDataflowConnection* FindConnection(const UE::Dataflow::FConnectionReference& Reference);`
- L187 _public prototype_ `FDataflowInput* FindInput(FName Name);`
- L188 _public prototype_ `FDataflowInput* FindInput(const UE::Dataflow::FConnectionKey& Key);`
- L190 _public prototype_ `FDataflowInput* FindInput(const UE::Dataflow::FConnectionReference& Reference);` — This version can find array inputs if only the Reference is supplied by searching through all inputs
- L191 _public prototype_ `const FDataflowInput* FindInput(FName Name) const;`
- L192 _public prototype_ `const FDataflowInput* FindInput(const UE::Dataflow::FConnectionKey& Key) const;`
- L194 _public prototype_ `const FDataflowInput* FindInput(const UE::Dataflow::FConnectionReference& Reference) const;` — This version can find array inputs if only the Reference is supplied by searching through all inputs
- L195 _public prototype_ `const FDataflowInput* FindInput(const FGuid& InGuid) const;`
- L197 _public prototype_ `virtual void AddOutput(FDataflowOutput* InPtr);`
- L198 _public prototype_ `int NumOutputs() const;`
- L199 _public prototype_ `TArray< FDataflowOutput* > GetOutputs() const;`
- L200 _public prototype_ `void ClearOutputs();`
- L201 _public prototype_ `bool HasHideableOutputs() const;`
- L202 _public prototype_ `bool HasHiddenOutputs() const;`
- L204 _public prototype_ `FDataflowOutput* FindOutput(FName Name);`
- L205 _public prototype_ `FDataflowOutput* FindOutput(uint32 GuidHash);`
- L206 _public prototype_ `FDataflowOutput* FindOutput(const UE::Dataflow::FConnectionKey& Key);`
- L207 _public prototype_ `FDataflowOutput* FindOutput(const UE::Dataflow::FConnectionReference& Reference);`
- L208 _public prototype_ `const FDataflowOutput* FindOutput(FName Name) const;`
- L209 _public prototype_ `const FDataflowOutput* FindOutput(uint32 GuidHash) const;`
- L210 _public prototype_ `const FDataflowOutput* FindOutput(const UE::Dataflow::FConnectionKey& Key) const;`
- L211 _public prototype_ `const FDataflowOutput* FindOutput(const UE::Dataflow::FConnectionReference& Reference) const;`
- L212 _public prototype_ `const FDataflowOutput* FindOutput(const FGuid& InGuid) const;`
- L214 _public prototype_ `bool TryRenameInput(const UE::Dataflow::FConnectionReference& Reference, FName NewName);`
- L215 _public prototype_ `bool TryRenameInput(FDataflowInput& InputToRename, FName NewName);`
- L216 _public prototype_ `bool TryRenameOutput(const UE::Dataflow::FConnectionReference& Reference, FName NewName);`
- L217 _public prototype_ `bool TryRenameOutput(FDataflowOutput& OutputToRename, FName NewName);`
- L220 _public prototype_ `uint32 GetPropertyOffset(const FName& PropertyFullName) const;` — Return a property's byte offset from the dataflow base node address using the full property name (must includes its parent struct property names). Does not work with array properties.
- L222 _public member_ `static const FName DataflowInput;`
- L223 _public member_ `static const FName DataflowOutput;`
- L224 _public member_ `static const FName DataflowPassthrough;`
- L225 _public member_ `static const FName DataflowIntrinsic;`
- L226 _public member_ `static const FName DataflowSkipConnection;`
- L228 _public member_ `static const FLinearColor DefaultNodeTitleColor;`
- L229 _public member_ `static const FLinearColor DefaultNodeBodyTintColor;`
- L232 _public function_ `virtual void Serialize(FArchive& Ar)` — Override this method to provide custom serialization for this node.
- L235 _public function_ `virtual void PostSerialize(const FArchive& Ar)` — Override this method to provide custom post-serialization for this node. This method will be called after Serialize. It is also called after copy-paste with ArchiveState IsLoading.
- L238 _public function_ `virtual FDataflowInput* RedirectSerializedInput(const FName& MissingInputName)` — Override this method to provide custom reconnections when a node inputs has been deprecated and removed.
- L240 _public function_ `virtual FDataflowOutput* RedirectSerializedOutput(const FName& MissingOutputName)` — Override this method to provide custom reconnections when a node outputs has been deprecated and removed.
- L246 _public function_ `virtual void SerializeInternal(FArchive& Ar)`
- L247 _public function_ `virtual FStructOnScope* NewStructOnScope()`
- L248 _public function_ `virtual const UScriptStruct* TypedScriptStruct() const`
- L250 _public prototype_ `TUniquePtr<const FStructOnScope> NewStructOnScopeConst() const;`
- L254 _public function_ `template<typename T> FDataflowInput& RegisterInputConnection(const UE::Dataflow::TConnectionReference<T>& Reference, const FName& PropertyName = NAME_None)` — Register the Input and Outputs after the creation in the factory. Use PropertyName to disambiguate a struct name from its first property.
- L265 _public function_ `template <typename T> FDataflowInput& RegisterInputConnection(const T* Reference, const FName& PropertyName = NAME_None)`
- L271 _public function_ `template <typename T> FDataflowOutput& RegisterOutputConnection(const UE::Dataflow::TConnectionReference<T>& Reference, const UE::Dataflow::TConnectionReference<T>& Passthrough = UE::Dataflow::TConnectionReference<T>(nullptr), const FName& PropertyName = NAME_None)`
- L287 _public function_ `template <typename T> FDataflowOutput& RegisterOutputConnection(const T* Reference, const T* Passthrough = nullptr, const FName& PropertyName = NAME_None)`
- L293 _public function_ `template<typename T> FDataflowInput& RegisterInputArrayConnection(const UE::Dataflow::TConnectionReference<T>& Reference, const FName& ElementPropertyName = NAME_None, const FName& ArrayPropertyName = NAME_None)`
- L305 _public function_ `template<typename T> FDataflowInput& FindOrRegisterInputArrayConnection(const UE::Dataflow::TConnectionReference<T>& Reference, const FName& ElementPropertyName = NAME_None, const FName& ArrayPropertyName = NAME_None)`
- L322 _public function_ `template<typename T> FDataflowOutput& RegisterOutputArrayConnection(const UE::Dataflow::TConnectionReference<T>& Reference, const FName& ElementPropertyName = NAME_None, const FName& ArrayPropertyName = NAME_None)`
- L334 _public function_ `template<typename T> FDataflowOutput& FindOrRegisterOutputArrayConnection(const UE::Dataflow::TConnectionReference<T>& Reference, const FName& ElementPropertyName = NAME_None, const FName& ArrayPropertyName = NAME_None)`
- L351 _public function_ `void UnregisterInputConnection(const UE::Dataflow::FConnectionReference& Reference)` — Unregister the input connection if one exists matching this property, and then invalidate the graph.
- L355 _public prototype_ `void UnregisterInputConnection(const UE::Dataflow::FConnectionKey& Key);`
- L357 _public prototype_ `void UnregisterPinConnection(const UE::Dataflow::FPin& Pin);` — Unregister the connection if one exists matching this pin, then invalidate the graph.
- L359 _public function_ `void UnregisterOutputConnection(const UE::Dataflow::FConnectionReference& Reference)`
- L363 _public prototype_ `void UnregisterOutputConnection(const UE::Dataflow::FConnectionKey& Key);`
- L375 _public prototype_ `bool EvaluateNode(UE::Dataflow::FContext& Context) const;` — This evaluate the node based on the existing state of the outputs if the node has no output then evaluate will be called with a null output otherwise Evaluate will be called for each connected output if it has an outdated cached value in the context Return true if at least one output was evaluated or forwarded
- L377 _public function_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput*) const`
- L379 _public function_ `virtual bool EvaluateOnGameThreadOnly() const`
- L382 _public prototype_ `void Freeze(UE::Dataflow::FContext& Context);` — Freeze the node's outputs.
- L384 _public prototype_ `void Unfreeze(UE::Dataflow::FContext& Context);` — Unfreeze the node's outputs.
- L386 _public function_ `bool IsFrozen() const` — Return whether the node is frozen.
- L391 _public function_ `const FInstancedPropertyBag& GetFrozenFroperties() const` — Return the frozen output property bag.
- L396 _public function_ `bool IsColorOverriden() const`
- L403 _public function_ `const FLinearColor& GetOverrideColor() const`
- L413 _public function_ `static const FName GetActivePropertyName()` — Gets the property name for bActive. This exists so the property can be made private later.
- L422 _public prototype_ `bool IsActive(bool bCheckFlagOnly = false) const;` — If bCheckFlagOnly is false, this function returns true if both the bActive property and the CVAR p.Dataflow.EnableGraphEval are true If bCheckFlagOnly is true, this function returns true if the bActive property is true
- L435 _public function_ `template<class T UE_REQUIRES(!std::is_base_of_v<FDataflowAnyType, T>)> const T& GetValue(UE::Dataflow::FContext& Context, const UE::Dataflow::TConnectionReference<T>& Reference) const` — GetValue(...) Get the value of the Reference output, invoking up stream evaluations if not cached in the contexts data store. @param Context : The evaluation context that holds the data store. @param Reference : Pointer to a member of this node that corresponds with the output to set. *Reference will be used as the default if the input is not connected.
- L442 _public function_ `template<typename TAnyType UE_REQUIRES(std::is_base_of_v<FDataflowAnyType, TAnyType> && !std::is_same_v<typename TAnyType::FStorageType, void>)> typename TAnyType::FStorageType GetValue(UE::Dataflow::FContext& Context, const UE::Dataflow::TConnectionReference<TAnyType>& Reference) const`
- L449 _public function_ `template<typename TAnyType UE_REQUIRES(std::is_base_of_v<FDataflowAnyType, TAnyType> && std::is_same_v<typename TAnyType::FStorageType, void>)> typename UE::Dataflow::FContextValue GetValue(UE::Dataflow::FContext& Context, const UE::Dataflow::TConnectionReference<TAnyType>& Reference) const`
- L456 _public function_ `template<class T UE_REQUIRES(!std::is_base_of_v<FDataflowAnyType, T>)> const T& GetValue(UE::Dataflow::FContext& Context, const T* Reference) const`
- L475 _public function_ `TFuture<const T&> GetValueParallel(UE::Dataflow::FContext& Context, const UE::Dataflow::TConnectionReference<T>& Reference) const` — `UE_DEPRECATED(5.8, "This code path is not supported, use context to evaluate nodes and connections asynchronously")`
- L485 _public function_ `TFuture<const T&> GetValueParallel(UE::Dataflow::FContext& Context, const T* Reference) const` — `UE_DEPRECATED(5.8, "This code path is not supported, use context to evaluate nodes and connections asynchronously")`
- L502 _public function_ `template<class T> const T& GetValue(UE::Dataflow::FContext& Context, const UE::Dataflow::TConnectionReference<T>& Reference, const T& Default) const` — GetValue(...) Get the value of the Reference output, invoking up stream evaluations if not cached in the contexts data store. @param Context : The evaluation context that holds the data store. @param Reference : Pointer to a member of this node that corresponds with the output to set. @param Default : Default value if the input is not connected.
- L508 _public function_ `template<class T> const T& GetValue(UE::Dataflow::FContext& Context, const T* Reference, const T& Default) const`
- L513 _public function_ `template<class T> const T& GetOutputValue(UE::Dataflow::FContext& Context, const T* Reference, const T& Default) const`
- L538 _public function_ `template<class T, class U UE_REQUIRES(!std::is_base_of_v<FDataflowAnyType, U>)> void SetValue(UE::Dataflow::FContext& Context, T&& Value, const U* Reference) const` — SetValue(...) Set the value of the Reference output. Note: If the compiler errors out with "You cannot bind an lvalue to an rvalue reference", then simply remove the explicit template parameter from the function call to allow for a const reference type to be deducted. const int32 Value = 0; SetValue<int32>(Context, Value, &Reference);  // Error: You cannot bind an lvalue to an rvalue reference const int32 Value = 0; SetValue(Context, Value, &Reference);  // Fine const int32 Value = 0; SetValue<const int32&>(Context, Value, &Reference);  // Fine @param Context : The evaluation context that holds the data store. @param Value : The value to store in the contexts data store. @param Reference : Pointer to a member of this node that corresponds with the output to set.
- L554 _public function_ `template<typename TAnyType UE_REQUIRES(std::is_base_of_v<FDataflowAnyType, TAnyType> && !std::is_same_v<typename TAnyType::FStorageType, void>)> void SetValue(UE::Dataflow::FContext& Context, const typename TAnyType::FStorageType& Value, const TAnyType* Reference) const`
- L567 _public function_ `template<typename TAnyType UE_REQUIRES(std::is_base_of_v<FDataflowAnyType, TAnyType> && std::is_same_v<typename TAnyType::FStorageType, void>)> void SetValue(UE::Dataflow::FContext& Context, UE::Dataflow::FContextValue&& Value, const TAnyType* Reference) const`
- L579 _public function_ `void SetError(UE::Dataflow::FContext& Context, const void* Reference, const FString& InError) const`
- L597 _public prototype_ `void ForwardInput(UE::Dataflow::FContext& Context, const UE::Dataflow::FConnectionReference& InputReference, const UE::Dataflow::FConnectionReference& Reference) const;` — ForwardInput(...) Forward an input to this output. This will not cache the value itself but cache a reference to the input connection cache entry. This is memory efficient and do not require a runtime copy of the data. Input and output references must match in type. Note that forwarding an input never sets a default value when no input is connected, use SafeForwardInput instead. @param Context : The evaluation context that holds the data store. @param InputReference : Pointer to a input member of this node that needs to be forwarded. @param Reference : Pointer to a member of this node that corresponds with the output to set.
- L611 _public function_ `template<class T> void SafeForwardInput(UE::Dataflow::FContext& Context, const UE::Dataflow::FConnectionReference& InputReference, const T* Reference) const` — SafeForwardInput(...) Forward an input to this output or set a default value if no input is connected. This is more memory efficient when an input is connected than setting the value. Input and output references must match in type. @param Context : The evaluation context that holds the data store. @param InputReference : Pointer to a input member of this node that needs to be forwarded. @param Reference : Pointer to a member of this node that corresponds with the output to set.
- L633 _public prototype_ `void SetArraySizeFromInput(UE::Dataflow::FContext& Context, const UE::Dataflow::FConnectionReference& InputReference, const int32* OutputReference) const;` — `UE_DEPRECATED(5.7, "Use UE::Dataflow::FContextValue from calling GetValue on the node to access the same functionality")` — This method infers the array size from an input and set it on the specified output. When called, the input will be pulled as a result. If the input is not an array, the value set on the output will be 0
- L641 _public prototype_ `void SetArrayElementFromInput(UE::Dataflow::FContext& Context, const UE::Dataflow::FConnectionReference& InputReference, int32 Index, const void* OutputReference) const;` — `UE_DEPRECATED(5.7, "Use UE::Dataflow::FContextValue from calling GetValue on the node to access the same functionality")` — This method extracts an element from the specified input at a specific index and set it as output to the specified output. When called, the input will be pulled as a result. If the input is not an array or if the index is out of bounds, a null value will be set on the output (which will result in a default value when read from)
- L648 _public function_ `template <typename TFunction> void ForEachConnection(TFunction Function) const` — Go through all connections and execute a function Signature of the function is bool Function(FDataflowConnection* Connection)
- L673 _public function_ `bool IsConnected(const UE::Dataflow::FConnectionReference& Reference) const` — IsConnected(...) Checks if Reference input is connected. @param Reference : Pointer to a member of this node that corresponds with the input.
- L680 _public function_ `template<typename T> bool IsConnected(const T* Reference) const`
- L685 _public function_ `void PauseInvalidations()`
- L694 _public function_ `void ResumeInvalidations()`
- L703 _public prototype_ `void Invalidate(const UE::Dataflow::FTimestamp& ModifiedTimestamp = UE::Dataflow::FTimestamp::Current());`
- L705 _public function_ `virtual void OnInvalidate()`
- L707 _public prototype_ `virtual bool ValidateConnections();`
- L709 _public prototype_ `virtual void ValidateProperties();`
- L712 _public function_ `virtual bool SupportsAssetProperty(UObject* Asset) const` — return true if the node supports a specific type of asset to be assign to it
- L715 _public function_ `virtual void SetAssetProperty(UObject* Asset)` — Set an asset property on this node ( called when SupportsAssetProperty returns true )
- L718 _public function_ `virtual void OnPropertyChanged(UE::Dataflow::FContext& Context, const FPropertyChangedEvent& InPropertyChangedEvent)` — Called when UPROPERTY members of the dataflow node have been changed in the editor
- L721 _public function_ `virtual bool SupportsDropConnectionOnNode(FName TypeName, UE::Dataflow::FPin::EDirection Direction) const` — check if the node support dropped connections
- L725 _public function_ `virtual const FDataflowConnection* OnDropConnectionOnNode(const FDataflowConnection& DroppedConnection)` — called when a dragged pin is dropped on the node if the node creates a connection, returns its pointer
- L728 _public prototype_ `virtual bool ShouldInvalidateOnPropertyChanged(const FPropertyChangedEvent& InPropertyChangedEvent) const;` — Override when a property change musn't invalidate the node. Must return the base implementation when the property name isn't recognised.
- L731 _public function_ `virtual bool MakeConnectedPropertiesReadOnly() const` — returns true to disable node properties in its detail view when the corresponding input is connected ( default is true )
- L744 _public function_ `virtual FAttributeKey GetVertexAttributeToVisualize(UE::Dataflow::FContext& Context, const FName OutputName, const FName RenderGroup) const` — return a vertex attribute to visualize This attribute will be used as vertex color and displayed in the viewport this is only used for collection based visualizations
- L749 _public function_ `virtual void GetSelectionToVisualize(UE::Dataflow::FContext& Context, const FName OutputName, const FName RenderGroup, FDataflowSelection& OutSelection) const` — Fills a dataflow selection object used to visualize the selection a node may output for a sepcific output and render group
- L753 _public function_ `virtual void OnRenderOutput(UE::Dataflow::FContext& Context, const FName OutputName, const FName RenderGroup, const TArray<UPrimitiveComponent*>& RenderComponents) const` — this method is called when the construction viewport render a specific output in the viewport this allow the node to be able to set extra properties on the component or set it up differently
- L755 _public function_ `bool HasValidConnections() const`
- L763 _public function_ `virtual bool IsTerminal() const` — Define is a node is a terminal type of node terminal nodes can be pulled from to generate content (see FDataflowTerminalNode ) or write results to a simulation for example ( see FDataflowSimulationNode ) The dataflow compiler also use this infromation to decide what part of the graph is a dead end and can be optimized out
- L768 _public function_ `virtual bool IsA(FName InType) const`
- L774 _public function_ `template<class T> const T* AsType() const`
- L785 _public function_ `template<class T> T* AsType()`
- L795 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNodeInvalidated, FDataflowNode*);`
- L796 _public function_ `FOnNodeInvalidated& GetOnNodeInvalidatedDelegate()`
- L800 _public prototype_ `bool TrySetConnectionType(FDataflowConnection* Connection, FName NewType);` — returns true if the type was changed successfully only unset datatype connection will be set a new type
- L803 _public prototype_ `void NotifyConnectionTypeChanged(FDataflowConnection* Connection);` — Only used when forcing types on connection in order to make sure the node properly refreshes the rest of its connection accordingly if there's any dependencies between their types
- L806 _public prototype_ `bool SetInputConcreteType(const UE::Dataflow::FConnectionReference& InputReference, FName NewType);` — returns true if the input type was changed successfully
- L809 _public prototype_ `bool SetOutputConcreteType(const UE::Dataflow::FConnectionReference& OutputReference, FName NewType);` — returns true if the output type was changed successfully
- L812 _public prototype_ `bool SetOutputConnectionConcreteType(FDataflowConnection* Output, FName NewType);` — returns true if the output type was changed successfully
- L815 _public prototype_ `bool IsAnytypeDependencyConnected(FName DependencyGroup, const FDataflowConnection* IgnoreConnection = nullptr) const;` — Check if any connection matching a specific type dependency group are connected
- L817 _public function_ `bool IsAsyncEvaluating() const`
- L818 _public function_ `void SetAsyncEvaluating(bool bValue) const`
- L820 _public prototype_ `TSharedPtr<UE::Dataflow::FGraph> GetDataflowGraph() const;`
- L823 _protected prototype_ `bool OnConnectionTypeChanged(const FDataflowConnection& Connection);`
- L829 _protected prototype_ `virtual FName GetDependentConnectionType(const FDataflowConnection& SourceConnection, const FDataflowConnection& DependentConnection) const;` — When enforcing type dependency returns the type of the target connection from a source one being changed the default implementation returns the same type
- L832 _protected function_ `template <typename T> bool SetInputConcreteType(const UE::Dataflow::FConnectionReference& InputReference)`
- L838 _protected function_ `template <typename T> bool SetOutputConcreteType(const UE::Dataflow::FConnectionReference& OutputReference)`
- L848 _protected prototype_ `bool SetConnectionConcreteType(const UE::Dataflow::FConnectionKey& ConnectionKey, FName NewType);` — Set a connection identified by key to be of a specific type If the connection is already connected, the method prevents the connection from changing and returns false returns true if the connection has successfully changed type
- L856 _protected prototype_ `bool SetConnectionConcreteType(FDataflowConnection* Connection, FName NewType, FName InTypeDependencyGroup = NAME_None);` — Set a connection to be of a specific type or optional set its type dependency group If the connection is already connected, the method prevents the connection from changing and returns false The type dependency group can only be set on anytype connections and only if the connecion does not have already a type depencency returns true if the connection has successfully changed type
- L859 _protected prototype_ `bool SetAllConnectionConcreteType(FName NewType);` — returns true if any of the types was changed successfully
- L861 _protected prototype_ `FDataflowInput& RegisterInputConnectionInternal(const UE::Dataflow::FConnectionReference& Reference, const FName& PropertyName = NAME_None);`
- L862 _protected prototype_ `FDataflowOutput& RegisterOutputConnectionInternal(const UE::Dataflow::FConnectionReference& Reference, const FName& PropertyName = NAME_None);`
- L863 _protected prototype_ `FDataflowInput& RegisterInputArrayConnectionInternal(const UE::Dataflow::FConnectionReference& Reference, const FName& ElementPropertyName = NAME_None, const FName& ArrayPropertyName = NAME_None);`
- L864 _protected prototype_ `FDataflowOutput& RegisterOutputArrayConnectionInternal(const UE::Dataflow::FConnectionReference& Reference, const FName& ElementPropertyName = NAME_None, const FName& ArrayPropertyName = NAME_None);`
- L868 _private prototype_ `void InitConnectionParametersFromPropertyReference(const FStructOnScope& StructOnScope, const void* PropertyRef, const FName& PropertyName, UE::Dataflow::FConnectionParameters& OutParams);`
- L870 _private prototype_ `static FString GetPropertyFullNameString(const TConstArrayView<const FProperty*>& PropertyChain, int32 ContainerIndex = INDEX_NONE);` — This will add [ContainerIndex] to any array it finds unless ContainerIndex == INDEX_NONE.
- L871 _private prototype_ `static FName GetPropertyFullName(const TArray<const FProperty*>& PropertyChain, int32 ContainerIndex = INDEX_NONE);`
- L872 _private prototype_ `static FText GetPropertyDisplayNameText(const TArray<const FProperty*>& PropertyChain, int32 ContainerIndex = INDEX_NONE);`
- L873 _private prototype_ `static FString StripContainerIndexFromPropertyFullName(const FString& PropertyFullName);`
- L874 _private prototype_ `static uint32 GetPropertyOffset(const TArray<const FProperty*>& PropertyChain);`
- L875 _private prototype_ `uint32 GetConnectionOffsetFromReference(const void* Reference) const;`
- L876 _private prototype_ `UE::Dataflow::FConnectionKey GetKeyFromReference(const UE::Dataflow::FConnectionReference& Reference) const;`
- L883 _private prototype_ `const FProperty* FindProperty(const UStruct* Struct, const void* Property, const FName& PropertyName, TArray<const FProperty*>* OutPropertyChain = nullptr) const;` — Find a property using the property address and name (not including its parent struct property names). If NAME_None is used as the name, and the same address is shared by a parent structure property and its first child property, then the parent will be returned.
- L884 _private prototype_ `const FProperty& FindPropertyChecked(const UStruct* Struct, const void* Property, const FName& PropertyName, TArray<const FProperty*>* OutPropertyChain = nullptr) const;`
- L887 _private prototype_ `const FProperty* FindProperty(const UStruct* Struct, const FName& PropertyFullName, TArray<const FProperty*>* OutPropertyChain = nullptr) const;` — Find a property using the property full name (must includes its parent struct property names).
- L889 _private function_ `virtual TArray<UE::Dataflow::FRenderingParameter> GetRenderParametersImpl() const`
- L891 _private member_ `FGuid Guid;`
- L892 _private member_ `FName Name;`
- L893 _private member_ `UE::Dataflow::FTimestamp LastModifiedTimestamp;`
- L895 _private member_ `bool bHasValidConnections = true;`
- L896 _private member_ `TMap<UE::Dataflow::FConnectionKey, FDataflowInput*> ExpandedInputs;`
- L897 _private member_ `TMap<uint32, const FArrayProperty*> InputArrayProperties;` — Used to calculate ContainerElementOffsets
- L899 _private member_ `TMap<UE::Dataflow::FConnectionKey, FDataflowOutput*> ExpandedOutputs;`
- L900 _private member_ `TMap<uint32, const FArrayProperty*> OutputArrayProperties;` — Used to calculate ContainerElementOffsets
- L911 _private member_ `bool bActive = true;` — `UPROPERTY(EditAnywhere, Category = "Dataflow")`
- L915 _private member_ `FInstancedPropertyBag FrozenProperties;` — `UPROPERTY()` — Property bag for frozen outputs
- L918 _private member_ `bool bIsFrozen = false;` — `UPROPERTY()`
- L920 _private member_ `TWeakPtr<UE::Dataflow::FGraph> WeakDataflowGraph;`
- L922 _private member_ `mutable TAtomic<bool> bIsAsyncEvaluating = false;`
- L925 _protected member_ `bool bPauseInvalidations = false;`
- L926 _protected member_ `UE::Dataflow::FTimestamp PausedModifiedTimestamp = UE::Dataflow::FTimestamp::Invalid;` — When unpausing invalidations, Invalidate will be called with this timestamp.
- L927 _protected member_ `FOnNodeInvalidated OnNodeInvalidatedDelegate;`

#### struct `FDataflowNode::FDebugDrawParameters`  
`struct FDebugDrawParameters`  
_L116-126_
- L119 _public member_ `bool bNodeIsSelected = false;` — Boolean to check if the node is selected or not
- L122 _public member_ `bool bNodeIsPinned = false;` — Boolean to check if the node is pinned or not
- L125 _public member_ `FName CurrentViewMode = NAME_None;` — Current view mode to use in the debug draw

#### struct `FDataflowNode::FAttributeKey`  
`struct FAttributeKey`  
_L733-737_
- L735 _public member_ `FName AttributeName;`
- L736 _public member_ `FName GroupName;`

#### class `UE::Dataflow::FDataflowNodePauseInvalidationScope`  
`class FDataflowNodePauseInvalidationScope`  
_L934-959_
- L937 _public function_ `explicit FDataflowNodePauseInvalidationScope(FDataflowNode* InNode) :Node(InNode)`
- L946 _public function_ `~FDataflowNodePauseInvalidationScope()`
- L954 _public prototype_ `FDataflowNodePauseInvalidationScope() = delete;`
- L955 _public prototype_ `FDataflowNodePauseInvalidationScope(const FDataflowNodePauseInvalidationScope&) = delete;`
- L956 _public prototype_ `FDataflowNodePauseInvalidationScope(FDataflowNodePauseInvalidationScope&&) = delete;`
- L958 _private member_ `FDataflowNode* Node;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Dataflow` (scope `UE`)
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNodeInvalidated, FDataflowNode&);` — Called when the node is being invalidated
- L540 _typedef_ `using FInValueType = typename TDecay<decltype(Value)>::Type;` (scope `FDataflowNode::SetValue`)
- L541 _typedef_ `using FInReferenceType = typename TDecay<decltype(*Reference)>::Type;` (scope `FDataflowNode::SetValue`)
- L795 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNodeInvalidated, FDataflowNode*);`
- L931 _namespace_ `namespace UE`
- L931 _namespace_ `namespace Dataflow` (scope `UE`)
- L965 _macro_ `#define DATAFLOW_NODE_REGISTER_CREATION_FACTORY(A) \`
- L968 _macro_ `#define DATAFLOW_NODE_RENDER_TYPE(A, B, ...) \`
- L974 _macro_ `#define DATAFLOW_NODE_RENDER_TYPE_START() \`
- L978 _macro_ `#define DATAFLOW_NODE_RENDER_TYPE_ADD(A, B, ...) \`
- L981 _macro_ `#define DATAFLOW_NODE_RENDER_TYPE_END() \`
- L984 _macro_ `#define DATAFLOW_NODE_DEFINE_INTERNAL(TYPE, DISPLAY_NAME, CATEGORY, TAGS) \`
- L1009 _macro_ `#define DATAFLOW_NODE_REGISTER_CREATION_FACTORY_NODE_COLORS_BY_CATEGORY(CategoryName, C1, C2) \`
- L1014 _macro_ `#define DATAFLOW_REGISTER_CATEGORY_ICON_BY_CATEGORY(CategoryName, IconName) \`
- L1019 _macro_ `#define DATAFLOW_REGISTER_CATEGORY_ICON_AND_STYLE_BY_CATEGORY(CategoryName, IconName, StyleName) \`
- L1024 _macro_ `#define DATAFLOW_NODE_REGISTER_CREATION_FACTORY_PIN_SETTINGS_BY_TYPE(A, C, T) \`
- L1029 _macro_ `#define DATAFLOW_NODE_REGISTER_GETTER_FOR_ASSET(ASSETTYPE, NODETYPE) \`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowNodeColorsRegistry.h` (Public)


#### struct `UE::Dataflow::FColorScheme`  
`struct FColorScheme`  
_L19-24_
- desc: Default color scheme for Dataflow nodes before any category-specific overrides are registered.
- L21 _public member_ `static inline const FLinearColor Asset = FColor(180, 120, 110);`
- L22 _public member_ `static inline const FLinearColor NodeHeader = FColor(180, 120, 110);`
- L23 _public member_ `static inline const FLinearColor NodeBody = FColor(18, 12, 11, 127);`

#### class `UE::Dataflow::FNodeColorsRegistry`  
`class FNodeColorsRegistry`  
_L29-48_
- desc: Registry for custom Node colors
- L32 _public prototype_ `static FNodeColorsRegistry& Get();`
- L33 _public prototype_ `static void TearDown();`
- L35 _public prototype_ `void RegisterNodeColors(const FName& Category, const FNodeColors& NodeColors);`
- L36 _public prototype_ `FLinearColor GetNodeTitleColor(const FName& Category) const;`
- L37 _public prototype_ `FLinearColor GetNodeBodyTintColor(const FName& Category) const;`
- L38 _public prototype_ `void NodeColorsChangedInSettings(const FNodeColorsMap& NodeColorsMap);`
- L41 _private prototype_ `FNodeColorsRegistry();`
- L42 _private prototype_ `~FNodeColorsRegistry();`
- L44 _private member_ `FNodeColorsMap ColorsMap;` — [Category] -> Colors
- L45 _private member_ `FDelegateHandle DataflowSettingsChangedDelegateHandle;`

#### class `UE::Dataflow::FPinSettingsRegistry`  
`class FPinSettingsRegistry`  
_L53-73_
- desc: Registry for custom Pin colors
- L56 _public prototype_ `static FPinSettingsRegistry& Get();`
- L57 _public prototype_ `static void TearDown();`
- L59 _public prototype_ `void RegisterPinSettings(const FName& PinType, const FPinSettings& InSettings);`
- L60 _public prototype_ `FLinearColor GetPinColor(const FName& PinType) const;`
- L61 _public prototype_ `float GetPinWireThickness(const FName& PinType) const;`
- L62 _public prototype_ `void PinSettingsChangedInSettings(const FPinSettingsMap& PinSettingsrMap);`
- L63 _public prototype_ `bool IsPinTypeRegistered(const FName& PinType) const;`
- L66 _private prototype_ `FPinSettingsRegistry();`
- L67 _private prototype_ `~FPinSettingsRegistry();`
- L69 _private member_ `FPinSettingsMap SettingsMap;` — [PinType] -> {Color, WireThickness}
- L70 _private member_ `FDelegateHandle DataflowSettingsChangedDelegateHandle;`

#### class `UE::Dataflow::FIconCategoryRegistry`  
`class FIconCategoryRegistry`  
_L78-94_
- desc: Registry for category icons
- L81 _public prototype_ `static FIconCategoryRegistry& Get();`
- L83 _public prototype_ `void RegisterCategoryIcon(const TCHAR* Category, const TCHAR* IconName, const TCHAR* StyleName = nullptr);`
- L84 _public prototype_ `FSlateIcon GetCategoryIcon(const FName Category) const;`
- L93 _private member_ `TMap<FName, FIconInfo> IconsByCategory;`

#### struct `UE::Dataflow::FIconCategoryRegistry::FIconInfo`  
`struct FIconInfo`  
_L87-91_
- L89 _public member_ `FName IconName;`
- L90 _public member_ `FName StyleName;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Dataflow` (scope `UE`)

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowNodeFactory.h` (Public)


#### struct `UE::Dataflow::FNewNodeParameters`  
`struct FNewNodeParameters`  
_L14-20_
- L16 _public member_ `FGuid Guid;`
- L17 _public member_ `FName Type;`
- L18 _public member_ `FName Name;`
- L19 _public member_ `UObject* OwningObject = nullptr;`

#### struct `UE::Dataflow::FFactoryParameters`  
`struct FFactoryParameters`  
_L22-53_
- L24 _public member_ `FName TypeName;`
- L25 _public member_ `FName DisplayName;`
- L26 _public member_ `FName Category;`
- L27 _public member_ `FString Tags;`
- L28 _public member_ `FString ToolTip;`
- L29 _public member_ `bool bIsDeprecated = false;`
- L30 _public member_ `bool bIsExperimental = false;`
- L31 _public member_ `FName NodeVersion = FName("v1"`
- L32 _public member_ `TSharedPtr<FDataflowNode> DefaultNodeObject;`
- L34 _public function_ `bool IsValid() const`
- L39 _public function_ `bool IsDeprecated() const`
- L44 _public function_ `bool IsExperimental() const`
- L49 _public function_ `FName GetVersion() const`

#### class `UE::Dataflow::FNodeFactory`  
`class FNodeFactory`  
_L58-140_
- L61 _public typedef_ `typedef TFunction<TUniquePtr<FDataflowNode> (const FNewNodeParameters&)> FNewNodeFunction;`
- L64 _private typedef_ `typedef TUniquePtr<FDataflowNode> FRawNewNodeFunction(const FNewNodeParameters&);`
- L67 _private member_ `TMap<FName, FNewNodeFunction > ClassMap;` — All Maps indexed by TypeName
- L68 _private member_ `TMap<FName, FFactoryParameters > ParametersMap;` — [TypeName] -> Parameters
- L69 _private member_ `TMap<FName, TArray<FName>> VersionMap;` — [TypeNameNoVersion] -> Array of TypeName(versions)
- L71 _private member_ `TMap<FName, FName> GetterNodesByAssetType;` — list of getter nodes that relate to a specific asset type
- L73 _private member_ `static FNodeFactory* Instance;`
- L74 _private prototype_ `FNodeFactory();`
- L76 _private prototype_ `static void RegisterNodeStaticInternal( UScriptStruct* StaticStruct, FName StaticType, const char* StaticDisplay, const char* StaticCategory, const FString& StaticTags, FRawNewNodeFunction CreationFunction );`
- L82 _public prototype_ `~FNodeFactory();`
- L84 _public prototype_ `static FNodeFactory* GetInstance();`
- L87 _public function_ `template<typename T> static void RegisterNodeFromType()`
- L103 _public prototype_ `void RegisterGetterNodeForAssetType(FName AssetTypeName, FName NodeTypeName);`
- L105 _public prototype_ `FName GetGetterNodeFromAssetClass(const UClass& AssetClass) const;`
- L107 _public prototype_ `const FFactoryParameters& GetParameters(FName InTypeName) const;`
- L109 _public prototype_ `TSharedPtr<FDataflowNode> NewNodeFromRegisteredType(FGraph& Graph, const FNewNodeParameters& Param);`
- L111 _public prototype_ `TArray<FFactoryParameters> RegisteredParameters() const;`
- L113 _public prototype_ `static bool IsNodeDeprecated(const FName NodeType);`
- L115 _public prototype_ `static bool IsNodeExperimental(const FName NodeType);`
- L118 _private prototype_ `void RegisterNode(const FFactoryParameters& Parameters, FNewNodeFunction NewFunction);`
- L120 _private prototype_ `static FName GetVersionFromTypeName(const FName& TypeName);`
- L122 _private prototype_ `static int32 GetNumVersionFromVersion(const FName& Version);`
- L124 _private prototype_ `static bool IsNodeDeprecated(const UStruct* Struct);`
- L126 _private prototype_ `static bool IsNodeExperimental(const UStruct* Struct);`
- L128 _private prototype_ `static FName GetTypeNameNoVersion(const FName& TypeName);`
- L130 _private prototype_ `static FName GetDisplayNameNoVersion(const FName& DisplayName);`
- L132 _private prototype_ `static FString GetToolTipFromStruct(UScriptStruct* InStruct, const FName& InTypeName, const FName& InDisplayName);`
- L134 _private function_ `template<class T> TSharedPtr<T> NewNode(FGraph& Graph, const FNewNodeParameters& Param)`
- L139 _private prototype_ `void RegisterDefaultNodes();`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Dataflow` (scope `UE`)
- L90 _function_ `` (scope `UE::Dataflow::FNodeFactory::RegisterNodeFromType`)

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowNodeParameters.h` (Public)


#### struct `UE::Dataflow::FRenderingParameter`  
`struct FRenderingParameter`  
_L26-40_
- L28 _public function_ `FRenderingParameter()`
- L29 _public function_ `FRenderingParameter(FString InRenderName, FName InTypeName, const TArray<FName>& InOutputs, const FName& InViewMode = FName("3DView")) : Name(InRenderName), Type(InTypeName), Outputs(InOutputs), ViewMode(InViewMode)`
- L31 _public function_ `FRenderingParameter(FString InRenderName, FName InTypeName, TArray<FName>&& InOutputs, const FName& InViewMode = FName("3DView")) : Name(InRenderName), Type(InTypeName), Outputs(InOutputs), ViewMode(InViewMode)`
- L34 _public prototype_ `bool operator==(const FRenderingParameter& Other) const = default;`
- L36 _public member_ `FString Name = FString();`
- L37 _public member_ `FName Type = FName();`
- L38 _public member_ `TArray<FName> Outputs;`
- L39 _public member_ `FName ViewMode = FName();`

#### struct `UE::Dataflow::FContextPerfData`  
`struct FContextPerfData`  
_L47-62_
- desc: Performance data per connection
- L49 _public prototype_ `void Reset();`
- L50 _public prototype_ `void Accumulate(const FDataflowConnection* Connection, uint64 TotalTime, uint64 ExternalTime);`
- L51 _public prototype_ `void Append(const FContextPerfData& InPerfData);`
- L60 _public member_ `TMap<FGuid, FData> DataPerOutput;`
- L61 _public member_ `bool bEnabled = false;`

#### struct `UE::Dataflow::FContextPerfData::FData`  
`struct FData`  
_L53-59_
- L55 _public member_ `float InclusiveTimeMs = 0;`
- L56 _public member_ `float ExclusiveTimeMs = 0;`
- L57 _public member_ `int32 NumCalls = 0;`
- L58 _public member_ `FTimestamp LastTimestamp = FTimestamp(0);` — timestamp of the owner node when data was last collected

#### struct `UE::Dataflow::FContextCallstack`  
`struct FContextCallstack`  
_L70-92_
- desc: Connection context callstack Used to detected loops and use for error handling
- L72 _public prototype_ `void Push(const FDataflowConnection* Connection);`
- L73 _public prototype_ `void Pop(const FDataflowConnection* Connection, uint64& OutTotalTime, uint64& OutExternalTime);`
- L74 _public prototype_ `const FDataflowConnection* Top() const;`
- L76 _public prototype_ `int32 Num() const;`
- L77 _public prototype_ `const FDataflowConnection* operator[](int32 Index);`
- L78 _public prototype_ `bool Contains(const FDataflowConnection* Connection) const;`
- L91 _public member_ `TArray<FEntry> Callstack;`

#### struct `UE::Dataflow::FContextCallstack::FEntry`  
`struct FEntry`  
_L80-90_
- L82 _public member_ `const FDataflowConnection* Connection;`
- L83 _public member_ `uint64 StartTime = 0;`
- L84 _public member_ `uint64 ExternalTime = 0;`
- L86 _public function_ `bool operator==(const FDataflowConnection* OtherConnection) const`

#### class `UE::Dataflow::FScopedOptionalLock`  
`class FScopedOptionalLock final`  
_L95-128_
- L98 _public function_ `UE_NODISCARD_CTOR explicit FScopedOptionalLock(FCriticalSection* InCriticalSection) : CriticalSection(InCriticalSection)`
- L107 _public function_ `~FScopedOptionalLock()`
- L112 _public function_ `void Unlock()`
- L122 _private prototype_ `FScopedOptionalLock() = delete;`
- L123 _private prototype_ `FScopedOptionalLock(const FScopedOptionalLock& InScopeLock) = delete;`
- L124 _private prototype_ `FScopedOptionalLock& operator=(const FScopedOptionalLock& InScopeLock) = delete;`
- L127 _private member_ `FCriticalSection* CriticalSection;`

#### class `UE::Dataflow::FContext`  
`class FContext: public IContextCacheStore, public IContextAssetStoreInterface`  
_L135-407_
- inherits: `IContextCacheStore,IContextAssetStoreInterface`
- desc: Dataflow context base class
- L138 _protected prototype_ `FContext(FContext&&) = delete;`
- L139 _protected prototype_ `FContext& operator=(FContext&&) = delete;`
- L141 _protected prototype_ `FContext(const FContext&) = delete;`
- L142 _protected prototype_ `FContext& operator=(const FContext&) = delete;`
- L144 _protected member_ `FContextCache DataStore;`
- L145 _protected member_ `TUniquePtr<FCriticalSection> DataLock;`
- L147 _protected member_ `FContextEvaluator AsyncEvaluator;`
- L150 _public prototype_ `FContext();`
- L153 _public prototype_ `virtual ~FContext() = default;`
- L156 _public function_ `static FName StaticType()`
- L158 _public function_ `virtual bool IsA(FName InType) const`
- L160 _public function_ `virtual FName GetType() const`
- L163 _public function_ `template<class T> const T* AsType() const`
- L173 _public function_ `template<class T> T* AsType()`
- L182 _public function_ `bool IsThreaded() const`
- L183 _public prototype_ `void SetThreaded(bool bValue);`
- L185 _public prototype_ `bool IsAsyncEvaluating() const;`
- L186 _public prototype_ `void CancelAsyncEvaluation();`
- L187 _public prototype_ `void GetAsyncEvaluationStats(int32& OutNumPendingTasks, int32& OutNumRunningTasks, int32& OutNumCompletedTasks) const;`
- L189 _public prototype_ `virtual void SetDataImpl(FContextCacheKey Key, TUniquePtr<FContextCacheElementBase>&& DataStoreEntry);`
- L190 _public prototype_ `virtual const TUniquePtr<FContextCacheElementBase>* GetDataImpl(FContextCacheKey Key) const;`
- L191 _public prototype_ `virtual bool HasDataImpl(FContextCacheKey Key, FTimestamp InTimestamp = FTimestamp::Invalid) const;`
- L192 _public prototype_ `virtual bool IsEmptyImpl() const;`
- L193 _public prototype_ `virtual int32 GetKeys(TSet<FContextCacheKey>& InKeys) const;`
- L195 _public prototype_ `void Evaluate(const FDataflowNode* Node, const FDataflowOutput* Output, FOnPostEvaluationFunction PostEvaluationFunction);`
- L197 _public prototype_ `virtual void Evaluate(const FDataflowNode* Node, const FDataflowOutput* Output );`
- L198 _public prototype_ `virtual bool Evaluate(const FDataflowOutput& Connection );`
- L200 _public prototype_ `void ClearAllData();`
- L203 _public function_ `template<typename T> void SetData(FContextCacheKey InKey, const FProperty* InProperty, T&& InValue, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp)`
- L261 _public prototype_ `void SetDataFromStructView(FContextCacheKey InKey, const FProperty* InProperty, const FConstStructView& StructView, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp);`
- L263 _public prototype_ `void SetDataFromStructArrayView(FContextCacheKey InKey, const FProperty* InProperty, const FConstStructArrayView& StructArrayView, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp);`
- L265 _public prototype_ `void SetDataReference(FContextCacheKey Key, const FProperty* Property, FContextCacheKey ReferenceKey, const FTimestamp& InTimestamp);`
- L270 _public prototype_ `void SetNullData(FContextCacheKey InKey, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp);` — this is useful when there's a need to have to have cache entry but  the type is not known and there no connected output ( like reroute nodes with unconnected input for example ) in that case posting an invalid reference, will allow the evaluatino to go through and the node reading it will get a default value instead
- L272 _public prototype_ `bool CopyDataToAnotherContext(const FContextCacheKey InSourceKey, FContext& TargetContext, const FContextCacheKey InTargetKey, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp) const;`
- L275 _public function_ `template<class T> const T& GetData(FContextCacheKey Key, const FProperty* InProperty, const T& Default = T()) const`
- L284 _public prototype_ `const void* GetUntypedData(FContextCacheKey Key, const FProperty* InProperty) const;`
- L285 _public prototype_ `bool HasData(FContextCacheKey Key, FTimestamp InTimestamp = FTimestamp::Invalid) const;`
- L286 _public prototype_ `bool IsEmpty() const;`
- L287 _public prototype_ `virtual void Serialize(FArchive& Ar);`
- L290 _public prototype_ `virtual const TUniquePtr<FContextCacheElementBase>* FindCacheElement(FContextCacheKey InKey) const override;`
- L291 _public prototype_ `virtual bool HasCacheElement(FContextCacheKey InKey, FTimestamp InTimestamp = FTimestamp::Invalid) const override;`
- L295 _public prototype_ `virtual UObject* AddAsset(const FString& AssetPath, const UClass* AssetClass) override;`
- L296 _public prototype_ `virtual UObject* CommitAsset(const FString& AssetPath) override;`
- L297 _public prototype_ `virtual void ClearAssets() override;`
- L300 _public prototype_ `FTimestamp GetTimestamp(FContextCacheKey Key) const;`
- L302 _public prototype_ `void PushToCallstack(const FDataflowConnection* Connection);`
- L303 _public prototype_ `void PopFromCallstack(const FDataflowConnection* Connection);`
- L304 _public prototype_ `bool IsInCallstack(const FDataflowConnection* Connection) const;`
- L306 _public prototype_ `FContextPerfData::FData GetPerfDataForNode(const FDataflowNode& Node) const;`
- L307 _public prototype_ `void ResetPerfDataForNode(const FDataflowNode& Node);`
- L308 _public prototype_ `void AddExternalPerfData(const FContextPerfData& InPerfData);`
- L309 _public prototype_ `void ClearAllPerfData();`
- L310 _public prototype_ `void EnablePerfData(bool bEnable);`
- L311 _public prototype_ `bool IsPerfDataEnabled() const;`
- L313 _public prototype_ `bool IsCacheEntryAfterTimestamp(FContextCacheKey InKey, const FTimestamp InTimestamp) const;`
- L315 _public prototype_ `void Info(const FText& InInfo, const FDataflowNode* InNode = nullptr, const FDataflowOutput* InOutput = nullptr);`
- L316 _public prototype_ `void Info(const FString& InInfo, const FDataflowNode* InNode = nullptr, const FDataflowOutput* InOutput = nullptr);`
- L318 _public prototype_ `void Warning(const FText& InWarning, const FDataflowNode* InNode = nullptr, const FDataflowOutput* InOutput = nullptr);`
- L319 _public prototype_ `void Warning(const FString& InWarning, const FDataflowNode* InNode = nullptr, const FDataflowOutput* InOutput = nullptr);`
- L321 _public prototype_ `void Error(const FText& InError, const FDataflowNode* InNode = nullptr, const FDataflowOutput* InOutput = nullptr);`
- L322 _public prototype_ `void Error(const FString& InError, const FDataflowNode* InNode = nullptr, const FDataflowOutput* InOutput = nullptr);`
- L324 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnNodeBeginEvaluateMulticast, const FDataflowNode* Node, const FDataflowOutput* Output);`
- L325 _public member_ `FOnNodeBeginEvaluateMulticast OnNodeBeginEvaluateMulticast;`
- L327 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnNodeFinishEvaluateMulticast, const FDataflowNode* Node, const FDataflowOutput* Output);`
- L328 _public member_ `FOnNodeFinishEvaluateMulticast OnNodeFinishEvaluateMulticast;`
- L338 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnContextLogMulticast, const FLogMessage& Message);`
- L339 _public function_ `FOnContextLogMulticast& GetOnContextLogMulticast()`
- L345 _public prototype_ `int32 GetArraySizeFromData(const FContextCacheKey InKey) const;` — `UE_DEPRECATED(5.7, "Use UE::Dataflow::FContextValue from calling GetValue on the node to access the same functionality")`
- L348 _public prototype_ `void SetArrayElementFromData(const FContextCacheKey InArrayKey, int32 Index, const FContextCacheKey InElementKey, const FProperty* InProperty, const FGuid& InNodeGuid, uint32 InNodeHash, const FTimestamp& InTimestamp);` — `UE_DEPRECATED(5.7, "Use UE::Dataflow::FContextValue from calling GetValue on the node to access the same functionality")`
- L351 _public function_ `int32 GetNumInfo() const` — `UE_DEPRECATED(5.8, "Deprecated method, context no longer count the Info calls")`
- L354 _public function_ `int32 GetNumWarnings() const` — `UE_DEPRECATED(5.8, "Deprecated method, context no longer count the Warning calls")`
- L357 _public function_ `int32 GetNumErrors() const` — `UE_DEPRECATED(5.8, "Deprecated method, context no longer count the Error calls")`
- L360 _public function_ `bool NodeHasWarning(const FDataflowNode* InNode) const` — `UE_DEPRECATED(5.8, "Deprecated method, context does not store the warning state of a node, this is the responsability of the code using the context")`
- L363 _public function_ `bool NodeHasError(const FDataflowNode* InNode) const` — `UE_DEPRECATED(5.8, "Deprecated method, context does not store the error state of a node, this is the responsability of the code using the context")`
- L366 _public function_ `bool NodeFailed(const FDataflowNode* InNode) const` — `UE_DEPRECATED(5.8, "Deprecated state of a node, failure state is not longer reported")`
- L369 _public function_ `void ClearNodesData()` — `UE_DEPRECATED(5.8, "ClearNodesData is deprecated as it is no longer needed")`
- L372 _public function_ `void ClearNodeData(const FDataflowNode* InNode)` — `UE_DEPRECATED(5.8, "ClearNodeData is deprecated as it is no longer needed")`
- L374 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnContextHasInfoMulticast, const FDataflowNode* Node, const FDataflowOutput* Output, const FString& Info);`
- L376 _public member_ `FOnContextHasInfoMulticast OnContextHasInfo;` — `UE_DEPRECATED(5.8, "Use OnContextLogMulticast instead.")`
- L378 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnContextHasWarningMulticast, const FDataflowNode* Node, const FDataflowOutput* Output, const FString& Info);`
- L380 _public member_ `FOnContextHasWarningMulticast OnContextHasWarning;` — `UE_DEPRECATED(5.8, "Use OnContextLogMulticast instead.")`
- L382 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnContextHasErrorMulticast, const FDataflowNode* Node, const FDataflowOutput* Output, const FString& Info);`
- L384 _public member_ `FOnContextHasErrorMulticast OnContextHasError;` — `UE_DEPRECATED(5.8, "Use OnContextLogMulticast instead.")`
- L387 _protected prototype_ `void BeginContextEvaluation(const FDataflowNode* Node, const FDataflowOutput* Output);`
- L389 _protected prototype_ `const FContextPerfData& GetPerfData() const;`
- L391 _protected prototype_ `virtual void BroadCastLog(EMessageSeverity::Type Severity, const FText& InMessage, const FDataflowNode* InNode, const FDataflowOutput* InOutput);`
- L399 _private member_ `TSharedRef<FDelegates> Delegates;`
- L402 _private member_ `FContextCallstack Callstack;`
- L403 _private member_ `FContextPerfData PerfData;`
- L406 _private member_ `FContextAssetStore AssetStore;` — used to store the dependent asset created during the evaluation of the graph

#### struct `UE::Dataflow::FContext::FLogMessage`  
`struct FLogMessage`  
_L330-336_
- L332 _public member_ `EMessageSeverity::Type Severity = EMessageSeverity::Info;`
- L333 _public member_ `TWeakPtr<const FDataflowNode> Node;`
- L334 _public member_ `FGuid OutputGuid;`
- L335 _public member_ `FText Text;`

#### struct `UE::Dataflow::FContext::FDelegates`  
`struct FDelegates`  
_L395-398_
- desc: have the delegate in a shared ref so we can keep a weakpointer on them when scheduling on the gamethread from another thread
- L397 _public member_ `FOnContextLogMulticast OnContextLog;`

#### struct `UE::Dataflow::FContextScopedCallstack`  
`struct FContextScopedCallstack`  
_L409-421_
- L412 _public prototype_ `FContextScopedCallstack(FContext& InContext, const FDataflowConnection* InConnection);`
- L413 _public prototype_ `~FContextScopedCallstack();`
- L415 _public function_ `bool IsLoopDetected() const`
- L418 _private member_ `bool bLoopDetected;`
- L419 _private member_ `FContext& Context;`
- L420 _private member_ `const FDataflowConnection* Connection;`

#### class `UE::Dataflow::FContextSingle`  
`class FContextSingle : public FContext`  
_L429-433_
- inherits: `FContext`
- L432 _public prototype_ `DATAFLOW_CONTEXT_INTERNAL(FContext, FContextSingle);`

#### class `UE::Dataflow::FContextThreaded`  
`class FContextThreaded : public FContext`  
_L435-445_
- inherits: `FContext`
- L438 _public prototype_ `DATAFLOW_CONTEXT_INTERNAL(FContext, FContextThreaded);`
- L440 _public function_ `FContextThreaded() : FContext()`

#### Free symbols / members of external scopes

- L22 _macro_ `#define DATAFLOW_EDITOR_EVALUATION WITH_EDITOR`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Dataflow` (scope `UE`)
- L223 _typedef_ `typedef typename TDecay<T>::Type ArrayType;` (scope `UE::Dataflow::FContext::SetData`)
- L324 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnNodeBeginEvaluateMulticast, const FDataflowNode* Node, const FDataflowOutput* Output);`
- L327 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnNodeFinishEvaluateMulticast, const FDataflowNode* Node, const FDataflowOutput* Output);`
- L338 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnContextLogMulticast, const FLogMessage& Message);`
- L374 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnContextHasInfoMulticast, const FDataflowNode* Node, const FDataflowOutput* Output, const FString& Info);`
- L378 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnContextHasWarningMulticast, const FDataflowNode* Node, const FDataflowOutput* Output, const FString& Info);`
- L382 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnContextHasErrorMulticast, const FDataflowNode* Node, const FDataflowOutput* Output, const FString& Info);`
- L423 _macro_ `#define DATAFLOW_CONTEXT_INTERNAL(PARENTTYPE, TYPENAME) \`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowOverrideNode.h` (Public)


#### struct `FDataflowOverrideNode`  
`struct FDataflowOverrideNode : public FDataflowNode`  
_L24-71_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: FDataflowOverrideNode Base class for override nodes within the Dataflow graph. Override Nodes allow to access to Override property on the asset. They can read the values by the key.
- L39 _public prototype_ `virtual ~FDataflowOverrideNode() = default;`
- L41 _public prototype_ `bool ShouldInvalidate(FName InKey) const;`
- L44 _public function_ `template <class T> T GetDefaultValue(UE::Dataflow::FContext& Context) const`
- L50 _public prototype_ `template <> int32 GetDefaultValue(UE::Dataflow::FContext& Context) const;`
- L53 _public prototype_ `template <> float GetDefaultValue(UE::Dataflow::FContext& Context) const;`
- L55 _public prototype_ `FString GetValueFromAsset(UE::Dataflow::FContext& Context, const UObject* InOwner) const;`
- L60 _public function_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const` — Evaluate
- L64 _public member_ `FName Key = "Ke` — `UPROPERTY(EditAnywhere, Category = "Overrides", meta = (DataflowInput))`
- L67 _public member_ `FString Default = FString("0")` — `UPROPERTY(EditAnywhere, Category = "Overrides", meta = (DataflowInput))`
- L70 _public member_ `bool IsOverriden = false;` — `UPROPERTY(meta = (DataflowOutput))`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowPath.h` (Public)


#### struct `FDataflowPath`  
`struct FDataflowPath final`  
_L8-39_
- reflection: `USTRUCT()`
- L12 _public prototype_ `FDataflowPath() = default;`
- L14 _public function_ `explicit FDataflowPath(const FString& InGraph, const FString& InNode, const FString& InInput = TEXT(""), const FString& InOutput = TEXT("")) : Graph(InGraph) , Node(InNode) , Input(InInput) , Output(InOutput)`
- L21 _public function_ `const FString& GetGraph() const`
- L22 _public function_ `const FString& GetNode() const`
- L23 _public function_ `const FString& GetInput() const`
- L24 _public function_ `const FString& GetOutput() const`
- L25 _public function_ `void SetGraph(const FString InGraph)`
- L26 _public function_ `void SetNode(const FString InNode)`
- L27 _public function_ `void SetInput(const FString InInput)`
- L28 _public function_ `void SetOutput(const FString InOutput)`
- L29 _public prototype_ `FString ToString() const;`
- L30 _public prototype_ `void DecodePath(const FString InPath);`
- L31 _public prototype_ `bool PathHasInput() const;`
- L32 _public prototype_ `bool PathHasOutput() const;`
- L35 _private member_ `FString Graph;`
- L36 _private member_ `FString Node;`
- L37 _private member_ `FString Input;`
- L38 _private member_ `FString Output;`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowPlane.h` (Public)


#### struct `FDataflowPlane`  
`struct FDataflowPlane`  
_L15-47_
- reflection: `USTRUCT()`
- desc: Represents a plane for dataflow This uses a point and a normal to represent a plane
- L19 _public function_ `FDataflowPlane() : Point(FVector::ZeroVector), Normal(FVector::UpVector)`
- L24 _public function_ `FDataflowPlane(const FVector& InPoint, const FVector& InNormal) : Point(InPoint), Normal(InNormal.GetSafeNormal())`
- L29 _public prototype_ `FDataflowPlane(const FPlane& InPlane);`
- L31 _public function_ `FVector GetPoint() const`
- L32 _public function_ `FVector GetNormal() const`
- L34 _public prototype_ `FPlane AsPlane() const;`
- L35 _public prototype_ `FTransform AsTransform() const;`
- L37 _public prototype_ `double DistanceFromPoint(const FVector& InPoint) const;`
- L39 _public prototype_ `FDataflowPlane GetTransformed(const FTransform& InTransform) const;`
- L43 _private member_ `FVector Point;` — `UPROPERTY(EditAnywhere, Category = "Plane")`
- L46 _private member_ `FVector Normal;` — `UPROPERTY(EditAnywhere, Category = "Plane")`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowPoints.h` (Public)


#### struct `FDataflowPoints`  
`struct FDataflowPoints`  
_L15-29_
- reflection: `USTRUCT()`
- desc: Represents a pointcloud with attributes for dataflow Data stored in Points group
- L20 _public prototype_ `const GeometryCollection::Facades::FPointsFacade GetPointsFacade() const;`
- L21 _public prototype_ `GeometryCollection::Facades::FPointsFacade GetPointsFacade();`
- L23 _public prototype_ `void Set(const FManagedArrayCollection& InCollection);`
- L24 _public prototype_ `void Set(FManagedArrayCollection& InCollection);`
- L28 _private member_ `FManagedArrayCollection Collection;` — `UPROPERTY()`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowPrimitiveTypes.h` (Public)


#### struct `FDataflowPrimitiveTypesStorage`  
`struct FDataflowPrimitiveTypesStorage`  
_L13-44_
- reflection: `USTRUCT()`
- L17 _public prototype_ `FDataflowPrimitiveTypesStorage() = default;`
- L18 _public prototype_ `FDataflowPrimitiveTypesStorage(const FDataflowPrimitiveTypesStorage& Other) = default;`
- L19 _public prototype_ `FDataflowPrimitiveTypesStorage& operator=(const FDataflowPrimitiveTypesStorage& Other) = default;`
- L20 _public prototype_ `FDataflowPrimitiveTypesStorage(FDataflowPrimitiveTypesStorage&& Other) = default;`
- L21 _public prototype_ `FDataflowPrimitiveTypesStorage& operator=(FDataflowPrimitiveTypesStorage&& Other) = default;`
- L22 _public function_ `FDataflowPrimitiveTypesStorage(const FBox& Primitive) : Storage(TInPlaceType<FBox>(), Primitive)`
- L26 _public function_ `FDataflowPrimitiveTypesStorage(const FSphere& Primitive) : Storage(TInPlaceType<FSphere>(), Primitive)`
- L30 _public function_ `FDataflowPrimitiveTypesStorage(const FDataflowPlane& Primitive) : Storage(TInPlaceType<FDataflowPlane>(), Primitive)`
- L36 _public function_ `template<typename T> const T* TryGet() const`
- L43 _private member_ `TVariant<FBox, FSphere, FDataflowPlane> Storage;` — Currently we don't support serialization for this storage

#### struct `FDataflowConverter`  
`template <> struct FDataflowConverter<FDataflowPrimitiveTypesStorage>`  
_L47-62_
- L50 _public function_ `template <typename TFromType> static void From(const TFromType& From, FDataflowPrimitiveTypesStorage& To)`
- L55 _public function_ `template <typename TToType> static void To(const FDataflowPrimitiveTypesStorage& From, TToType& To)`
- L128 _public function_ `template <typename TFromType> static void From(const TFromType& From, FDataflowPrimitiveArrayStorage& To)`
- L133 _public function_ `template <typename TToType> static void To(const FDataflowPrimitiveArrayStorage& From, TToType& To)`

#### struct `FDataflowPrimitiveTypePolicy`  
`struct FDataflowPrimitiveTypePolicy : public TDataflowMultiTypePolicy<FBox, FSphere, FDataflowPlane>`  
_L70-73_
- inherits: `TDataflowMultiTypePolicy<FBox,FSphere,FDataflowPlane>`

#### struct `FDataflowPrimitiveTypes`  
`struct FDataflowPrimitiveTypes : public FDataflowAnyType`  
_L76-86_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- L78 _public typedef_ `using FPolicyType = FDataflowPrimitiveTypePolicy;`
- L79 _public typedef_ `using FStorageType = FDataflowPrimitiveTypesStorage;`
- L85 _public member_ `FDataflowPrimitiveTypesStorage Value;` — `UPROPERTY()` — `UPROPERTY()`

#### struct `FDataflowPrimitiveArrayStorage`  
`struct FDataflowPrimitiveArrayStorage`  
_L91-122_
- reflection: `USTRUCT()`
- L95 _public prototype_ `FDataflowPrimitiveArrayStorage() = default;`
- L96 _public prototype_ `FDataflowPrimitiveArrayStorage(const FDataflowPrimitiveArrayStorage& Other) = default;`
- L97 _public prototype_ `FDataflowPrimitiveArrayStorage& operator=(const FDataflowPrimitiveArrayStorage& Other) = default;`
- L98 _public prototype_ `FDataflowPrimitiveArrayStorage(FDataflowPrimitiveArrayStorage&& Other) = default;`
- L99 _public prototype_ `FDataflowPrimitiveArrayStorage& operator=(FDataflowPrimitiveArrayStorage&& Other) = default;`
- L100 _public function_ `FDataflowPrimitiveArrayStorage(const TArray<FBox>& PrimitiveArray) : Storage(TInPlaceType<TArray<FBox>>(), PrimitiveArray)`
- L104 _public function_ `FDataflowPrimitiveArrayStorage(const TArray<FSphere>& PrimitiveArray) : Storage(TInPlaceType<TArray<FSphere>>(), PrimitiveArray)`
- L108 _public function_ `FDataflowPrimitiveArrayStorage(const TArray<FDataflowPlane>& PrimitiveArray) : Storage(TInPlaceType<TArray<FDataflowPlane>>(), PrimitiveArray)`
- L114 _public function_ `template<typename T> const T* TryGet() const`
- L121 _private member_ `TVariant<TArray<FBox>, TArray<FSphere>, TArray<FDataflowPlane>> Storage;` — Currently we don't support serialization for this storage

#### struct `FDataflowConverter`  
`template <> struct FDataflowConverter<FDataflowPrimitiveArrayStorage>`  
_L125-140_
- L50 _public function_ `template <typename TFromType> static void From(const TFromType& From, FDataflowPrimitiveTypesStorage& To)`
- L55 _public function_ `template <typename TToType> static void To(const FDataflowPrimitiveTypesStorage& From, TToType& To)`
- L128 _public function_ `template <typename TFromType> static void From(const TFromType& From, FDataflowPrimitiveArrayStorage& To)`
- L133 _public function_ `template <typename TToType> static void To(const FDataflowPrimitiveArrayStorage& From, TToType& To)`

#### struct `FDataflowPrimitiveArrayPolicy`  
`struct FDataflowPrimitiveArrayPolicy : public TDataflowMultiTypePolicy<TArray<FBox>, TArray<FSphere>, TArray<FDataflowPlane>>`  
_L144-147_
- inherits: `TDataflowMultiTypePolicy<TArray<FBox>,TArray<FSphere>,TArray<FDataflowPlane>>`

#### struct `FDataflowPrimitiveArrayTypes`  
`struct FDataflowPrimitiveArrayTypes : public FDataflowAnyType`  
_L150-160_
- reflection: `USTRUCT()`
- inherits: `FDataflowAnyType`
- L152 _public typedef_ `using FPolicyType = FDataflowPrimitiveArrayPolicy;`
- L153 _public typedef_ `using FStorageType = FDataflowPrimitiveArrayStorage;`
- L159 _public member_ `FDataflowPrimitiveArrayStorage Value;` — `UPROPERTY()` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L162 _namespace_ `namespace UE`
- L162 _namespace_ `namespace Dataflow` (scope `UE`)
- L164 _prototype_ `void RegisterPrimitiveTypes();` (scope `UE::Dataflow`)

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowSelection.h` (Public)


#### struct `FDataflowSelection`  
`struct FDataflowSelection`  
_L13-95_
- reflection: `USTRUCT()`
- L17 _public function_ `FDataflowSelection()`
- L20 _public function_ `FDataflowSelection(FName InGroupName) : GroupName(InGroupName)`
- L24 _public prototype_ `void Initialize(int32 NumBits, bool Value);`
- L25 _public prototype_ `void Initialize(const FDataflowSelection& Other);`
- L26 _public prototype_ `void Initialize(const TBitArray<>& Other);`
- L27 _public prototype_ `void InitializeFromCollection(const FManagedArrayCollection& InCollection, bool Value);`
- L28 _public prototype_ `void Clear();`
- L29 _public prototype_ `int32 Num() const;`
- L30 _public prototype_ `int32 NumSelected() const;`
- L31 _public prototype_ `bool AnySelected() const;`
- L33 _public prototype_ `bool IsValid() const;`
- L35 _public function_ `inline bool IsValidIndex(int32 Idx) const`
- L39 _public function_ `bool IsSelected(int32 Idx) const`
- L40 _public function_ `void SetSelected(int32 Idx)`
- L41 _public prototype_ `void SetSelected(const TArray<int32>& Indices);`
- L42 _public prototype_ `bool SetSelectedWithCheck(const TArray<int32>& Indices);`
- L43 _public function_ `void SetNotSelected(int32 Idx)`
- L44 _public prototype_ `void AsArray(TArray<int32>& SelectionArr) const;`
- L45 _public prototype_ `TArray<int32> AsArray() const;`
- L46 _public prototype_ `void AsArrayValidated(TArray<int32>& SelectionArr, const FManagedArrayCollection& InCollection) const;`
- L47 _public prototype_ `TArray<int32> AsArrayValidated(const FManagedArrayCollection& InCollection) const;`
- L53 _public prototype_ `bool SetFromArray(const TArray<int32>& SelectionArr);` — Sets the selection from a sparse array (it only contains the indices of the selected items) @return true if all indices were successfully set, false if some indices were invalid and could not be set
- L54 _public prototype_ `void SetFromBitArray(TBitArray<>&& Other);`
- L60 _public prototype_ `void SetFromArray(const TArray<bool>& SelectionArr);` — Sets the selection from a dense array (it contains a true/false element for every item) (for example from the "Internal" attr from FacesGroup)
- L61 _public prototype_ `void AND(const FDataflowSelection& Other, FDataflowSelection& Result) const;`
- L62 _public prototype_ `void OR(const FDataflowSelection& Other, FDataflowSelection& Result) const;`
- L63 _public prototype_ `void XOR(const FDataflowSelection& Other, FDataflowSelection& Result) const;`
- L65 _public prototype_ `void Subtract(const FDataflowSelection& Other, FDataflowSelection& Result) const;` — subtract the selected elements of 'Other' from this selection
- L66 _public function_ `void Invert()`
- L67 _public prototype_ `void SetWithMask(const bool Value, const FDataflowSelection& Mask);`
- L68 _public function_ `const TBitArray<>& GetBitArray() const`
- L74 _public prototype_ `bool InitFromArray(const FManagedArrayCollection& InCollection, const TArray<int32>& InSelectionArr);` — Initialize from a Collection and an array @return true if all indices were successfully set, false if some indices were invalid and could not be set
- L77 _public prototype_ `bool IsValidForCollection(const FManagedArrayCollection& InCollection) const;` — @return true if this selection is valid for the given collection -- i.e., if the selection expects the group to have the correct number of elements
- L83 _public prototype_ `FString ToString();` — Print selection in "Selected Transforms: 23 of 34" format;
- L85 _public function_ `FName GetGroupName() const`
- L90 _public prototype_ `static FName GetSelectionTypeFromCollection(const FDataflowConnection& InConnection);` — Returns group name from input or output connection
- L93 _private member_ `FName GroupName;`
- L94 _private member_ `TBitArray<> SelectionArray;`

#### struct `FDataflowTransformSelection`  
`struct FDataflowTransformSelection : public FDataflowSelection`  
_L98-107_
- reflection: `USTRUCT()`
- inherits: `FDataflowSelection`
- L102 _public member_ `inline static const FName TransformGroupName = "Tr`
- L104 _public function_ `FDataflowTransformSelection() : FDataflowSelection(TransformGroupName)`

#### struct `FDataflowVertexSelection`  
`struct FDataflowVertexSelection : public FDataflowSelection`  
_L111-120_
- reflection: `USTRUCT()`
- inherits: `FDataflowSelection`
- L115 _public member_ `inline static const FName VerticesGroupName = "Ve`
- L117 _public function_ `FDataflowVertexSelection() : FDataflowSelection(VerticesGroupName)`

#### struct `FDataflowFaceSelection`  
`struct FDataflowFaceSelection : public FDataflowSelection`  
_L124-133_
- reflection: `USTRUCT()`
- inherits: `FDataflowSelection`
- L128 _public member_ `inline static const FName FacesGroupName = "Fa`
- L130 _public function_ `FDataflowFaceSelection() : FDataflowSelection(FacesGroupName)`

#### struct `FDataflowGeometrySelection`  
`struct FDataflowGeometrySelection : public FDataflowSelection`  
_L136-145_
- reflection: `USTRUCT()`
- inherits: `FDataflowSelection`
- L140 _public member_ `inline static const FName GeometryGroupName = "Ge`
- L142 _public function_ `FDataflowGeometrySelection() : FDataflowSelection(GeometryGroupName)`

#### struct `FDataflowMaterialSelection`  
`struct FDataflowMaterialSelection : public FDataflowSelection`  
_L148-157_
- reflection: `USTRUCT()`
- inherits: `FDataflowSelection`
- L152 _public member_ `inline static const FName MaterialGroupName = "Ma`
- L154 _public function_ `FDataflowMaterialSelection() : FDataflowSelection(MaterialGroupName)`

#### struct `FDataflowCurveSelection`  
`struct FDataflowCurveSelection : public FDataflowSelection`  
_L160-169_
- reflection: `USTRUCT()`
- inherits: `FDataflowSelection`
- L164 _public member_ `inline static const FName CurveGroupName = "Cu`
- L166 _public function_ `FDataflowCurveSelection() : FDataflowSelection(CurveGroupName)`

#### struct `FDataflowPointsSelection`  
`struct FDataflowPointsSelection : public FDataflowSelection`  
_L172-182_
- reflection: `USTRUCT()`
- inherits: `FDataflowSelection`
- L176 _public member_ `inline static const FName PointsGroupName = "Po`
- L178 _public function_ `FDataflowPointsSelection() : FDataflowSelection(PointsGroupName)`

#### enum `EDataflowSelectionType`  
`enum class EDataflowSelectionType : uint8`  
_L185-194_
- reflection: `UENUM(BlueprintType)`
- L187 _public enumerator_ `Transform UMETA(DisplayName = "Transform")`
- L188 _public enumerator_ `Vertices UMETA(DisplayName = "Vertices")`
- L189 _public enumerator_ `Faces UMETA(DisplayName = "Faces")`
- L190 _public enumerator_ `Geometry UMETA(DisplayName = "Geometry")`
- L191 _public enumerator_ `Curves UMETA(DisplayName = "Curves")`
- L192 _public enumerator_ `Points UMETA(DisplayName = "Points")`
- L193 _public enumerator_ `Material UMETA(DisplayName = "Material")`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowSettings.h` (Public)


#### struct `FNodeColors`  
`struct FNodeColors`  
_L14-23_
- reflection: `USTRUCT()`
- L19 _public member_ `FLinearColor NodeTitleColor = FLinearColor(0.f, 0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = Colors)`
- L22 _public member_ `FLinearColor NodeBodyTintColor = FLinearColor(0.f, 0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = Colors)`

#### struct `FPinSettings`  
`struct FPinSettings`  
_L26-35_
- reflection: `USTRUCT()`
- L31 _public member_ `FLinearColor PinColor = FLinearColor(0.f, 0.f, 0.f);` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L34 _public member_ `float WireThickness = 1.f;` — `UPROPERTY(EditAnywhere, Category = Settings)`

#### struct `FTransformLevelColors`  
`struct FTransformLevelColors`  
_L38-47_
- reflection: `USTRUCT()`
- L43 _public member_ `TArray<FLinearColor> LevelColors;` — `UPROPERTY(EditAnywhere, Category = Colors)`
- L46 _public member_ `FLinearColor BlankColor = FLinearColor(255, 255, 255, 255);` — `UPROPERTY(EditAnywhere, Category = Colors)`

#### class `UDataflowSettings`  
`class UDataflowSettings : public UDeveloperSettings`  
_L50-93_
- reflection: `UCLASS(config = Editor, defaultconfig, meta = (DisplayName = "Dataflow"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- L55 _private member_ `TMap<FName, FNodeColors> NodeColorsMap;` — `UPROPERTY(config, EditAnywhere, Category = NodeColors)`
- L58 _private member_ `TMap<FName, FPinSettings> PinSettingsMap;` — `UPROPERTY(config, EditAnywhere, Category = PinSettings)`
- L61 _private member_ `FTransformLevelColors TransformLevelColors;` — `UPROPERTY(config, EditAnywhere, Category = TransformLevelColors)`
- L64 _private prototype_ `virtual FName GetCategoryName() const override;`
- L66 _private prototype_ `FNodeColors RegisterColors(const FName& Category, const FNodeColors& Colors);`
- L67 _private prototype_ `FPinSettings RegisterPinSettings(const FName& PinType, const FPinSettings& InSettings);`
- L69 _private function_ `const TMap<FName, FNodeColors>& GetNodeColorsMap()`
- L70 _private function_ `const TMap<FName, FPinSettings>& GetPinSettingsMap()`
- L73 _private prototype_ `virtual FText GetSectionText() const override;`
- L78 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L82 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDataflowSettingsChanged, const FNodeColorsMap&);`
- L83 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDataflowSettingsChangedPinSettings, const FPinSettingsMap&);`
- L86 _public function_ `FOnDataflowSettingsChanged& GetOnDataflowSettingsChangedDelegate()` — Gets a multicast delegate which is called whenever one of the parameters in this settings object changes.
- L87 _public function_ `FOnDataflowSettingsChangedPinSettings& GetOnDataflowSettingsChangedPinSettingsDelegate()`
- L90 _protected member_ `FOnDataflowSettingsChanged OnDataflowSettingsChangedDelegate;`
- L91 _protected member_ `FOnDataflowSettingsChangedPinSettings OnDataflowSettingsChangedPinSettingsDelegate;`

#### Free symbols / members of external scopes

- L10 _typedef_ `typedef TMap<FName, FNodeColors> FNodeColorsMap;`
- L11 _typedef_ `typedef TMap<FName, FPinSettings> FPinSettingsMap;`
- L82 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDataflowSettingsChanged, const FNodeColorsMap&);`
- L83 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDataflowSettingsChangedPinSettings, const FPinSettingsMap&);`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowSimpleDebugDrawMesh.h` (Public)


#### struct `FSimpleDebugDrawMesh`  
`struct FSimpleDebugDrawMesh : public IDataflowDebugDrawInterface::IDebugDrawMesh`  
_L7-27_
- inherits: `IDataflowDebugDrawInterface::IDebugDrawMesh`
- L9 _public member_ `TArray<FVector> Vertices;`
- L10 _public member_ `TArray<FIntVector3> Triangles;`
- L11 _public member_ `TArray<FVector> VertexNormals;`
- L13 _public prototype_ `virtual ~FSimpleDebugDrawMesh() = default;`
- L14 _public prototype_ `virtual int32 GetMaxVertexIndex() const override;`
- L15 _public prototype_ `virtual bool IsValidVertex(int32 VertexIndex) const override;`
- L16 _public prototype_ `virtual FVector GetVertexPosition(int32 VertexIndex) const override;`
- L17 _public prototype_ `virtual FVector GetVertexNormal(int32 VertexIndex) const override;`
- L18 _public prototype_ `void SetVertex(const int32 VertexIndex, const FVector& VertexPosition);`
- L20 _public prototype_ `virtual int32 GetMaxTriangleIndex() const override;`
- L21 _public prototype_ `virtual bool IsValidTriangle(int32 VertexIndex) const override;`
- L22 _public prototype_ `virtual FIntVector3 GetTriangle(int32 VertexIndex) const override;`
- L23 _public prototype_ `void SetTriangle(const int32 TriangleIndex, const int32 VertexIndexA, const int32 VertexIndexB, const int32 VertexIndexC);`
- L25 _public prototype_ `void MakeRectangleMesh(const FVector& Origin, const float Width, const float Height, const int32 WidthVertexCount, const int32 HeightVertexCount);`
- L26 _public prototype_ `void TransformVertices(const FTransform& Transform);`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowTerminalNode.h` (Public)


#### struct `FDataflowTerminalNode`  
`struct FDataflowTerminalNode : public FDataflowNode`  
_L32-87_
- reflection: `USTRUCT()`
- inherits: `FDataflowNode`
- desc: FDataflowTerminalNode Base class for terminal nodes within the Dataflow graph. Terminal Nodes allow for non-const access to UObjects as edges in the graph. They are used to push data out to asset or the world from the calling client. Terminals may not have outputs, they are only leaf nodes in the evaluation graph.
- L36 _public function_ `FDataflowTerminalNode() : Super()`
- L39 _public function_ `FDataflowTerminalNode(const UE::Dataflow::FNodeParameters& Param, FGuid InGuid = FGuid::NewGuid()) : Super(Param,InGuid)`
- L43 _public prototype_ `virtual ~FDataflowTerminalNode() = default;`
- L45 _public function_ `static FName StaticType()`
- L47 _public function_ `virtual bool IsA(FName InType) const override`
- L53 _public function_ `virtual bool IsTerminal() const override`
- L59 _public function_ `virtual TObjectPtr<UObject> GetTerminalAsset() const` — Return the terminal asset
- L69 _public function_ `virtual void SetAssetValue(TObjectPtr<UObject> Asset, UE::Dataflow::FContext& Context) const` — Write the terminal node's evaluated value into the bound asset. Note: Asset may be null when the graph is evaluated standalone (no owning asset). Implementations must tolerate a null Asset and simply do nothing in that case.
- L75 _public function_ `virtual void Evaluate(UE::Dataflow::FContext& Context) const`
- L78 _protected prototype_ `static FString GetAssetPath(const FString& InputPath, UObject* BoundAsset);`
- L80 _protected prototype_ `UObject* GetOrCreateAsset(UE::Dataflow::FContext& Context, const FString& InAssetPath, const UClass* AssetClass) const;`
- L83 _private function_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DATAFLOWCORE_API`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowTypePolicy.h` (Public)


#### struct `TDataflowPolicyTypeName`  
`template<typename TType> struct TDataflowPolicyTypeName`  
_L15-17_
- L41 _public function_ `static const TCHAR* GetName()`

#### struct `TDataflowPolicyTypeName`  
`template<> struct TDataflowPolicyTypeName<void>`  
_L39-45_
- desc: special version for void
- L41 _public function_ `static const TCHAR* GetName()`

#### struct `IDataflowTypePolicy`  
`struct IDataflowTypePolicy`  
_L108-116_
- L111 _public prototype_ `virtual bool SupportsType(FName Type) const = 0;` — Check if a specific type if supported
- L115 _public function_ `virtual void GetSupportedTypes(TArray<FName>& OutSupportedTypes) const` — Add the supported list of types if there's a short list of them for full anytype, no types will be added to the array

#### struct `FDataflowAllTypesPolicy`  
`struct FDataflowAllTypesPolicy : public IDataflowTypePolicy`  
_L118-135_
- inherits: `IDataflowTypePolicy`
- L120 _public function_ `virtual bool SupportsType(FName InType) const override`
- L125 _public function_ `static bool SupportsTypeStatic(FName InType)`
- L130 _public function_ `static IDataflowTypePolicy* GetInterface()`

#### struct `TDataflowSingleTypePolicy`  
`template <typename T> struct TDataflowSingleTypePolicy : public IDataflowTypePolicy`  
_L138-181_
- inherits: `IDataflowTypePolicy`
- L140 _public typedef_ `using FType = T;`
- L142 _public function_ `virtual bool SupportsType(FName InType) const override`
- L147 _public function_ `static bool SupportsTypeStatic(FName InType)`
- L152 _public function_ `virtual void GetSupportedTypes(TArray<FName>& OutSupportedTypes) const override`
- L157 _public function_ `static void GetSupportedTypesStatic(TArray<FName>& OutSupportedTypes)`
- L163 _public function_ `template <typename TVisitor> static bool VisitPolicyByType(FName RequestedType, TVisitor Visitor)`
- L174 _public function_ `static IDataflowTypePolicy* GetInterface()`
- L180 _public member_ `inline static const FName TypeName = FName(TDataflowPolicyTypeName<T>::GetName());`

#### struct `TDataflowMultiTypePolicy`  
`template <> struct TDataflowMultiTypePolicy<>: public IDataflowTypePolicy`  
_L187-204_
- inherits: `IDataflowTypePolicy`
- L189 _public function_ `virtual bool SupportsType(FName InType) const override`
- L194 _public function_ `static bool SupportsTypeStatic(FName InType)`
- L200 _public function_ `template <typename TVisitor> static bool VisitPolicyByType(FName RequestedType, TVisitor Visitor)`
- L209 _public typedef_ `using Super = TDataflowMultiTypePolicy<TTypes...>;`
- L222 _public function_ `virtual void GetSupportedTypes(TArray<FName>& OutSupportedTypes) const override`
- L238 _public function_ `static IDataflowTypePolicy* GetInterface()`

#### struct `TDataflowMultiTypePolicy`  
`template <typename T, typename... TTypes> struct TDataflowMultiTypePolicy<T, TTypes...>: public TDataflowMultiTypePolicy<TTypes...>`  
_L207-243_
- inherits: `TDataflowMultiTypePolicy<TTypes...>`
- L189 _public function_ `virtual bool SupportsType(FName InType) const override`
- L194 _public function_ `static bool SupportsTypeStatic(FName InType)`
- L200 _public function_ `template <typename TVisitor> static bool VisitPolicyByType(FName RequestedType, TVisitor Visitor)`
- L209 _public typedef_ `using Super = TDataflowMultiTypePolicy<TTypes...>;`
- L222 _public function_ `virtual void GetSupportedTypes(TArray<FName>& OutSupportedTypes) const override`
- L238 _public function_ `static IDataflowTypePolicy* GetInterface()`

#### struct `FDataflowArrayTypePolicy`  
`struct FDataflowArrayTypePolicy: public IDataflowTypePolicy`  
_L245-283_
- inherits: `IDataflowTypePolicy`
- L247 _public member_ `static constexpr TCHAR ArrayPrefix[] = TEXT("TAr`
- L248 _public member_ `static constexpr TCHAR ArrayFormat[] = TEXT("TAr`
- L250 _public function_ `virtual bool SupportsType(FName InType) const override`
- L255 _public function_ `static bool SupportsTypeStatic(FName InType)`
- L260 _public function_ `static IDataflowTypePolicy* GetInterface()`
- L266 _public function_ `static FName GetElementType(FName InType)`
- L279 _public function_ `static FName GetArrayType(FName InType)`

#### struct `FDataflowUStructTypePolicy`  
`struct FDataflowUStructTypePolicy : IDataflowTypePolicy`  
_L285-332_
- inherits: `IDataflowTypePolicy`
- L287 _public function_ `virtual bool SupportsType(FName InType) const override`
- L292 _public function_ `static bool SupportsTypeStatic(FName InType)`
- L307 _public function_ `static IDataflowTypePolicy* GetInterface()`
- L319 _public function_ `static bool GetStructType(const FString& InTypeStr, FString& OutInnerType)` — Provided an InTypeString outputs the same type without the type decorations (like prefixes). @param InTypeStr The object type @param OutInnerType The object type without the struct prefix ("F") @return true if the prefix was found, false otherwise

#### struct `FDataflowUDerivedStructTypePolicy`  
`template <typename BaseStructType> struct FDataflowUDerivedStructTypePolicy : IDataflowTypePolicy`  
_L335-362_
- inherits: `IDataflowTypePolicy`
- L337 _public function_ `virtual bool SupportsType(FName InType) const override`
- L342 _public function_ `static bool SupportsTypeStatic(FName InType)`
- L357 _public function_ `static IDataflowTypePolicy* GetInterface()`

#### struct `FDataflowNumericTypePolicy`  
`struct FDataflowNumericTypePolicy : public TDataflowMultiTypePolicy<double, float, int64, uint64, int32, uint32, int16, uint16, int8, uint8>`  
_L364-367_
- inherits: `TDataflowMultiTypePolicy<double,float,int64,uint64,int32,uint32,int16,uint16,int8,uint8>`

#### struct `FDataflowNumericArrayPolicy`  
`struct FDataflowNumericArrayPolicy: public TDataflowMultiTypePolicy<TArray<double>, TArray<float>, TArray<int64>, TArray<uint64>, TArray<int32>, TArray<uint32>, TArray<int16>, TArray<uint16>, TArray<int8>, TArray<uint8>>`  
_L369-373_
- inherits: `TDataflowMultiTypePolicy<TArray<double>,TArray<float>,TArray<int64>,TArray<uint64>,TArray<int32>,TArray<uint32>,TArray<int16>,TArray<uint16>,TArray<int8>,TArray<uint8>>`

#### struct `FDataflowVectorTypePolicy`  
`struct FDataflowVectorTypePolicy: public TDataflowMultiTypePolicy<FVector2D, FVector, FVector4, FVector2f, FVector3f, FVector4f, FQuat, FQuat4f, FLinearColor, FIntPoint, FIntVector, FIntVector4, FRotator>`  
_L375-378_
- inherits: `TDataflowMultiTypePolicy<FVector2D,FVector,FVector4,FVector2f,FVector3f,FVector4f,FQuat,FQuat4f,FLinearColor,FIntPoint,FIntVector,FIntVector4,FRotator>`

#### struct `FDataflowVectorArrayPolicy`  
`struct FDataflowVectorArrayPolicy: public TDataflowMultiTypePolicy<TArray<FVector2D>, TArray<FVector>, TArray<FVector4>, TArray<FVector2f>, TArray<FVector3f>, TArray<FVector4f>, TArray<FQuat>, TArray<FQuat4f>, TArray<FLinearColor>, TArray<FIntPoint>, TArray<FIntVector>, TArray<FIntVector4>, TArray<FRotator>>`  
_L380-385_
- inherits: `TDataflowMultiTypePolicy<TArray<FVector2D>,TArray<FVector>,TArray<FVector4>,TArray<FVector2f>,TArray<FVector3f>,TArray<FVector4f>,TArray<FQuat>,TArray<FQuat4f>,TArray<FLinearColor>,TArray<FIntPoint>,TArray<FIntVector>,TArray<FIntVector4>,TArray<FRotator>>`

#### struct `FDataflowStringTypePolicy`  
`struct FDataflowStringTypePolicy : public TDataflowMultiTypePolicy<FString, FName, FText>`  
_L387-390_
- inherits: `TDataflowMultiTypePolicy<FString,FName,FText>`

#### struct `FDataflowSelectionTypePolicy`  
`struct FDataflowSelectionTypePolicy : public TDataflowMultiTypePolicy<FDataflowTransformSelection, FDataflowVertexSelection, FDataflowFaceSelection, FDataflowGeometrySelection, FDataflowMaterialSelection, FDataflowCurveSelection>`  
_L392-395_
- inherits: `TDataflowMultiTypePolicy<FDataflowTransformSelection,FDataflowVertexSelection,FDataflowFaceSelection,FDataflowGeometrySelection,FDataflowMaterialSelection,FDataflowCurveSelection>`

#### struct `FDataflowStringArrayPolicy`  
`struct FDataflowStringArrayPolicy : public TDataflowMultiTypePolicy<TArray<FString>, TArray<FName>>`  
_L397-400_
- inherits: `TDataflowMultiTypePolicy<TArray<FString>,TArray<FName>>`

#### struct `FDataflowRotationTypePolicy`  
`struct FDataflowRotationTypePolicy : public TDataflowMultiTypePolicy<FVector, FQuat, FRotator>`  
_L402-405_
- inherits: `TDataflowMultiTypePolicy<FVector,FQuat,FRotator>`

#### struct `FDataflowMeshSelectionTypePolicy`  
`struct FDataflowMeshSelectionTypePolicy : public TDataflowMultiTypePolicy<FDataflowVertexSelection, FDataflowFaceSelection>`  
_L407-410_
- inherits: `TDataflowMultiTypePolicy<FDataflowVertexSelection,FDataflowFaceSelection>`

#### struct `FDataflowStringConvertibleTypePolicy`  
`struct FDataflowStringConvertibleTypePolicy : IDataflowTypePolicy`  
_L419-452_
- inherits: `IDataflowTypePolicy`
- desc: string comvertible types - FString / Fname - Numeric types ( see FDataflowNumericTypePolicy ) - Vector types ( see FDataflowVectorTypePolicy ) - bool
- L421 _public function_ `virtual bool SupportsType(FName InType) const override`
- L426 _public function_ `static bool SupportsTypeStatic(FName InType)`
- L437 _public function_ `template <typename TVisitor> static bool VisitPolicyByType(FName RequestedType, TVisitor Visitor)`
- L447 _public function_ `static IDataflowTypePolicy* GetInterface()`

#### struct `FDataflowUObjectConvertibleTypePolicy`  
`struct FDataflowUObjectConvertibleTypePolicy : IDataflowTypePolicy`  
_L454-508_
- inherits: `IDataflowTypePolicy`
- L456 _public function_ `virtual bool SupportsType(FName InType) const override`
- L461 _public function_ `static bool SupportsTypeStatic(FName InType)`
- L476 _public function_ `template <typename TVisitor> static bool VisitPolicyByType(FName RequestedType, TVisitor Visitor)`
- L487 _public function_ `static IDataflowTypePolicy* GetInterface()`
- L494 _public function_ `static bool GetObjectPtrInnerType(const FString& InTypeStr, FString& InnerType)` — returns true if the type was a TObjectPtr and the inner type was properly extracted

#### struct `FDataflowConverter`  
`template <typename T> struct FDataflowConverter`  
_L513-520_
- L516 _public function_ `template <typename TFromType> static void From(const TFromType& From, T& To)`
- L519 _public function_ `template <typename TToType> static void To(const T& From, TToType& To)`
- L539 _public function_ `template <typename TFromType> static void From(const TFromType& From, FString& To)`
- L568 _public function_ `template <typename TToType> static void To(const FString& From, TToType& To)`
- L603 _public function_ `template <typename TFromType> static void From(const TFromType& From, FVector4& To)`
- L648 _public function_ `template <typename TToType> static void To(const FVector4& From, TToType& To)`
- L709 _public function_ `template <typename TFromType> static void From(const TFromType& From, FDataflowSelection& To)`
- L715 _public function_ `template <typename TToType> static void To(const FDataflowSelection& From, TToType& To)`
- L725 _public function_ `template <typename TFromType> static void From(const TFromType& From, TArray<ArrayType>& To)`
- L735 _public function_ `template <typename TToType> static void To(const TArray<ArrayType>& From, TToType& To)`
- L749 _public function_ `template <typename TFromType> static void From(const TFromType& From, FRotator& To)`
- L766 _public function_ `template <typename TToType> static void To(const FRotator& From, TToType& To)`

#### struct `FDataflowConverter`  
`template <> struct FDataflowConverter<FString>`  
_L536-597_
- L516 _public function_ `template <typename TFromType> static void From(const TFromType& From, T& To)`
- L519 _public function_ `template <typename TToType> static void To(const T& From, TToType& To)`
- L539 _public function_ `template <typename TFromType> static void From(const TFromType& From, FString& To)`
- L568 _public function_ `template <typename TToType> static void To(const FString& From, TToType& To)`
- L603 _public function_ `template <typename TFromType> static void From(const TFromType& From, FVector4& To)`
- L648 _public function_ `template <typename TToType> static void To(const FVector4& From, TToType& To)`
- L709 _public function_ `template <typename TFromType> static void From(const TFromType& From, FDataflowSelection& To)`
- L715 _public function_ `template <typename TToType> static void To(const FDataflowSelection& From, TToType& To)`
- L725 _public function_ `template <typename TFromType> static void From(const TFromType& From, TArray<ArrayType>& To)`
- L735 _public function_ `template <typename TToType> static void To(const TArray<ArrayType>& From, TToType& To)`
- L749 _public function_ `template <typename TFromType> static void From(const TFromType& From, FRotator& To)`
- L766 _public function_ `template <typename TToType> static void To(const FRotator& From, TToType& To)`

#### struct `FDataflowConverter`  
`template <> struct FDataflowConverter<FVector4>`  
_L600-703_
- L516 _public function_ `template <typename TFromType> static void From(const TFromType& From, T& To)`
- L519 _public function_ `template <typename TToType> static void To(const T& From, TToType& To)`
- L539 _public function_ `template <typename TFromType> static void From(const TFromType& From, FString& To)`
- L568 _public function_ `template <typename TToType> static void To(const FString& From, TToType& To)`
- L603 _public function_ `template <typename TFromType> static void From(const TFromType& From, FVector4& To)`
- L648 _public function_ `template <typename TToType> static void To(const FVector4& From, TToType& To)`
- L709 _public function_ `template <typename TFromType> static void From(const TFromType& From, FDataflowSelection& To)`
- L715 _public function_ `template <typename TToType> static void To(const FDataflowSelection& From, TToType& To)`
- L725 _public function_ `template <typename TFromType> static void From(const TFromType& From, TArray<ArrayType>& To)`
- L735 _public function_ `template <typename TToType> static void To(const TArray<ArrayType>& From, TToType& To)`
- L749 _public function_ `template <typename TFromType> static void From(const TFromType& From, FRotator& To)`
- L766 _public function_ `template <typename TToType> static void To(const FRotator& From, TToType& To)`

#### struct `FDataflowConverter`  
`template <> struct FDataflowConverter<FDataflowSelection>`  
_L706-719_
- L516 _public function_ `template <typename TFromType> static void From(const TFromType& From, T& To)`
- L519 _public function_ `template <typename TToType> static void To(const T& From, TToType& To)`
- L539 _public function_ `template <typename TFromType> static void From(const TFromType& From, FString& To)`
- L568 _public function_ `template <typename TToType> static void To(const FString& From, TToType& To)`
- L603 _public function_ `template <typename TFromType> static void From(const TFromType& From, FVector4& To)`
- L648 _public function_ `template <typename TToType> static void To(const FVector4& From, TToType& To)`
- L709 _public function_ `template <typename TFromType> static void From(const TFromType& From, FDataflowSelection& To)`
- L715 _public function_ `template <typename TToType> static void To(const FDataflowSelection& From, TToType& To)`
- L725 _public function_ `template <typename TFromType> static void From(const TFromType& From, TArray<ArrayType>& To)`
- L735 _public function_ `template <typename TToType> static void To(const TArray<ArrayType>& From, TToType& To)`
- L749 _public function_ `template <typename TFromType> static void From(const TFromType& From, FRotator& To)`
- L766 _public function_ `template <typename TToType> static void To(const FRotator& From, TToType& To)`

#### struct `FDataflowConverter`  
`template <typename ArrayType> struct FDataflowConverter<TArray<ArrayType>>`  
_L722-743_
- L516 _public function_ `template <typename TFromType> static void From(const TFromType& From, T& To)`
- L519 _public function_ `template <typename TToType> static void To(const T& From, TToType& To)`
- L539 _public function_ `template <typename TFromType> static void From(const TFromType& From, FString& To)`
- L568 _public function_ `template <typename TToType> static void To(const FString& From, TToType& To)`
- L603 _public function_ `template <typename TFromType> static void From(const TFromType& From, FVector4& To)`
- L648 _public function_ `template <typename TToType> static void To(const FVector4& From, TToType& To)`
- L709 _public function_ `template <typename TFromType> static void From(const TFromType& From, FDataflowSelection& To)`
- L715 _public function_ `template <typename TToType> static void To(const FDataflowSelection& From, TToType& To)`
- L725 _public function_ `template <typename TFromType> static void From(const TFromType& From, TArray<ArrayType>& To)`
- L735 _public function_ `template <typename TToType> static void To(const TArray<ArrayType>& From, TToType& To)`
- L749 _public function_ `template <typename TFromType> static void From(const TFromType& From, FRotator& To)`
- L766 _public function_ `template <typename TToType> static void To(const FRotator& From, TToType& To)`

#### struct `FDataflowConverter`  
`template <> struct FDataflowConverter<FRotator>`  
_L746-781_
- L516 _public function_ `template <typename TFromType> static void From(const TFromType& From, T& To)`
- L519 _public function_ `template <typename TToType> static void To(const T& From, TToType& To)`
- L539 _public function_ `template <typename TFromType> static void From(const TFromType& From, FString& To)`
- L568 _public function_ `template <typename TToType> static void To(const FString& From, TToType& To)`
- L603 _public function_ `template <typename TFromType> static void From(const TFromType& From, FVector4& To)`
- L648 _public function_ `template <typename TToType> static void To(const FVector4& From, TToType& To)`
- L709 _public function_ `template <typename TFromType> static void From(const TFromType& From, FDataflowSelection& To)`
- L715 _public function_ `template <typename TToType> static void To(const FDataflowSelection& From, TToType& To)`
- L725 _public function_ `template <typename TFromType> static void From(const TFromType& From, TArray<ArrayType>& To)`
- L735 _public function_ `template <typename TToType> static void To(const TArray<ArrayType>& From, TToType& To)`
- L749 _public function_ `template <typename TFromType> static void From(const TFromType& From, FRotator& To)`
- L766 _public function_ `template <typename TToType> static void To(const FRotator& From, TToType& To)`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Dataflow` (scope `UE`)
- L22 _function_ `template<typename T> FName GetTypeName()` (scope `UE::Dataflow`)
- L25 _function_ `template<typename T> FName GetTypeName(bool bAsArray)` (scope `UE::Dataflow`)
- L47 _macro_ `#define UE_DATAFLOW_MAKE_STRING(x) #x`
- L48 _macro_ `#define UE_DATAFLOW_POLICY_DECLARE_TYPENAME(TType) \`

### `Source/Runtime/Dataflow/Core/Public/Dataflow/DataflowUtils.h` (Public)


#### enum `UE::Dataflow::Utils::EErrorCode`  
`enum class EErrorCode`  
_L11-18_
- L13 _public enumerator_ `None = 0`
- L14 _public enumerator_ `InvalidChars = 1`
- L15 _public enumerator_ `InvalidFormatInSegment = 2`
- L16 _public enumerator_ `NumberInRangeTooBig = 3`
- L17 _public enumerator_ `InvalidRangeStartEnd = 4`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Dataflow` (scope `UE`)
- L9 _namespace_ `namespace Utils` (scope `UE::Dataflow`)
- L21 _prototype_ `EErrorCode ParseIndicesStr(const FString& InFramesString, TArray<int32>& OutIndices);` (scope `UE::Dataflow::Utils`) — e.g. "0, 2, 5-10, 12-15"
- L24 _prototype_ `void GetMinMaxInArray(const TArray<float>& InArray, float& OutMin, float& OutMax);` (scope `UE::Dataflow::Utils`) — Compute Min/Max value in an array
