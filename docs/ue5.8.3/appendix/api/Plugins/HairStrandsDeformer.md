# Plugins / HairStrandsDeformer

- module root: `Plugins/Runtime/HairStrands/Source/HairStrandsDeformer`
- headers: 11; symbols: 463
- symbol kinds: class=30, enum=2, enumerator=25, function=35, member=165, namespace=9, prototype=174, struct=14, typedef=9
- PrivateDependencyModuleNames: Chaos, ComputeFramework, Core, CoreUObject, Engine, HairStrandsCore, HairStrandsSolver, Niagara, NiagaraCore, OptimusCore, RHI, RenderCore, Renderer
- PrivateIncludePathModuleNames: Shaders

### `Plugins/Runtime/HairStrands/Source/HairStrandsDeformer/Private/DeformerGroomAttributeRead.h` (Private)


#### enum `EOptimusGroomAttributeTypes`  
`enum class EOptimusGroomAttributeTypes : uint8`  
_L25-43_
- reflection: `UENUM()`
- desc: List of attribute types on which you could paint in dataflow
- L27 _public enumerator_ `None = 0 UMETA(Hidden)`
- L28 _public enumerator_ `Bool UMETA(DisplayName = "Bool")`
- L29 _public enumerator_ `Int UMETA(DisplayName = "Int")`
- L30 _public enumerator_ `IntVector2 UMETA(DisplayName = "Int Vector 2")`
- L31 _public enumerator_ `IntVector3 UMETA(DisplayName = "Int Vector 3")`
- L32 _public enumerator_ `IntVector4 UMETA(DisplayName = "Int Vector 4")`
- L33 _public enumerator_ `Uint UMETA(DisplayName = "Uint")`
- L34 _public enumerator_ `Float UMETA(DisplayName = "Float")`
- L35 _public enumerator_ `Vector2 UMETA(DisplayName = "Vector 2")`
- L36 _public enumerator_ `Vector3 UMETA(DisplayName = "Vector 3")`
- L37 _public enumerator_ `Vector4 UMETA(DisplayName = "Vector 4")`
- L38 _public enumerator_ `LinearColor UMETA(DisplayName = "Linear Color")`
- L39 _public enumerator_ `Quat UMETA(DisplayName = "Quat")`
- L40 _public enumerator_ `Rotator UMETA(DisplayName = "Rotator")`
- L41 _public enumerator_ `Transform UMETA(DisplayName = "Transform")`
- L42 _public enumerator_ `Matrix3x4 UMETA(DisplayName = "Matrix 3x4")`

#### class `UOptimusGroomAttributeReadDataInterface`  
`class UOptimusGroomAttributeReadDataInterface : public UOptimusComputeDataInterface`  
_L47-95_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading groom strands.
- L53 _public prototype_ `virtual FString GetDisplayName() const override;`
- L54 _public prototype_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L55 _public prototype_ `virtual TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L56 _public prototype_ `virtual TArray<FOptimusCDIPropertyPinDefinition> GetPropertyPinDefinitions() const override;`
- L57 _public function_ `virtual bool CanPinDefinitionChange() override`
- L58 _public prototype_ `virtual void RegisterPropertyChangeDelegatesForOwningNode(UOptimusNode* InNode) override;`
- L60 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L65 _public function_ `virtual TCHAR const* GetClassName() const override`
- L66 _public prototype_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L67 _public prototype_ `virtual void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L68 _public prototype_ `virtual TCHAR const* GetShaderVirtualPath() const override;`
- L69 _public prototype_ `virtual void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const override;`
- L70 _public prototype_ `virtual void GetShaderHash(FString& InOutKey) const override;`
- L71 _public prototype_ `virtual void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L72 _public prototype_ `virtual UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L77 _private member_ `static TCHAR const* TemplateFilePath;` — File holding the hlsl implementation
- L79 _private prototype_ `static FName GetGroomAttributeName();`
- L83 _private member_ `FName GroomAttributeName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Groom Attribute")` — Attribute name
- L87 _private member_ `EOptimusGroomExecDomain GroomAttributeGroup = EOptimusGroomExecDomain::GuidesPoints;` — `UPROPERTY(EditAnywhere, Category = "Groom Attribute")` — Attribute group
- L91 _private member_ `EOptimusGroomAttributeTypes GroomAttributeType = EOptimusGroomAttributeTypes::Float;` — `UPROPERTY(EditAnywhere, Category = "Groom Attribute")` — Attribute type
- L94 _private member_ `FOnPinDefinitionChanged OnPinDefinitionChangedDelegate;` — Delegate to change the pin definition context based on the group selected

#### class `UOptimusGroomAttributeReadDataProvider`  
`class UOptimusGroomAttributeReadDataProvider : public UComputeDataProvider`  
_L99-122_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading groom strands.
- L105 _public member_ `TObjectPtr<UMeshComponent> MeshComponent = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L109 _public member_ `FName GroomAttributeName = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Groom Attribute")` — Attribute name
- L113 _public member_ `EOptimusGroomExecDomain GroomAttributeGroup = EOptimusGroomExecDomain::GuidesPoints;` — `UPROPERTY(EditAnywhere, Category = "Groom Attribute")` — Attribute group
- L117 _public member_ `EOptimusGroomAttributeTypes GroomAttributeType = EOptimusGroomAttributeTypes::Float;` — `UPROPERTY(EditAnywhere, Category = "Groom Attribute")` — Attribute type
- L120 _public prototype_ `virtual FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusGroomAttributeReadProviderProxy`  
`class FOptimusGroomAttributeReadProviderProxy : public FComputeDataProviderRenderProxy`  
_L124-172_
- inherits: `FComputeDataProviderRenderProxy`
- L127 _public prototype_ `FOptimusGroomAttributeReadProviderProxy(UMeshComponent* InGroomComponent, const FName& InAtributeName, const EOptimusGroomExecDomain InAttributeGroup, const EOptimusGroomAttributeTypes InAttributeType);`
- L131 _public prototype_ `virtual bool IsValid(FValidationData const& InValidationData) const override;`
- L132 _public prototype_ `virtual void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L133 _public prototype_ `virtual void GatherPermutations(FPermutationData& InOutPermutationData) const override;`
- L134 _public prototype_ `virtual void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L138 _private typedef_ `using FParameters = FOptimusGroomAttributeReadParameters;`
- L141 _private prototype_ `void CreateInternalBuffers(FRDGBuilder& GraphBuilder);` — Create internal buffers
- L144 _private member_ `TArray<TRefCountPtr<const FHairGroupInstance>> GroupInstances;` — List of instances (invocations) used in that data interface
- L147 _private member_ `TArray<TPair<UGroomAsset*, UE::Groom::Private::FGroupElements>> GroupElements;` — Groom assets group indices the proxy instance is linked to
- L150 _private member_ `TArray<TArray<int32>> NumElements;` — Num elements per assets that will be used in deformer for each invocation (usually larger than the number of source elements)
- L153 _private member_ `TArray<FRDGBufferSRVRef> AttributeValuesResources;` — Attribute Resources used to dispatch CS on GPU
- L156 _private member_ `TArray<FRDGBufferSRVRef> IndexMappingResources;` — Index mappings resources
- L159 _private member_ `TArray<uint32> bHasIndexMapping;` — Check if we need to use the index mappings
- L162 _private member_ `FName GroomAttributeName = NAME_None;` — Attribute name
- L165 _private member_ `EOptimusGroomExecDomain GroomAttributeGroup = EOptimusGroomExecDomain::GuidesPoints;` — Attribute group
- L168 _private member_ `EOptimusGroomAttributeTypes GroomAttributeType = EOptimusGroomAttributeTypes::Float;` — Attribute type
- L171 _private member_ `FRDGBufferSRVRef FallbackStructuredSRV = nullptr;` — Fallback resources

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Groom` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Groom`)

### `Plugins/Runtime/HairStrands/Source/HairStrandsDeformer/Private/DeformerGroomCollisionRead.h` (Private)


#### class `UOptimusGroomCollisionReadDataInterface`  
`class UOptimusGroomCollisionReadDataInterface : public UOptimusComputeDataInterface`  
_L22-48_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading groom collision.
- L29 _public prototype_ `virtual FString GetDisplayName() const override;`
- L30 _public prototype_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L31 _public prototype_ `virtual TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L35 _public function_ `virtual TCHAR const* GetClassName() const override`
- L36 _public prototype_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L37 _public prototype_ `virtual void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L38 _public prototype_ `virtual TCHAR const* GetShaderVirtualPath() const override;`
- L39 _public prototype_ `virtual void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const override;`
- L40 _public prototype_ `virtual void GetShaderHash(FString& InOutKey) const override;`
- L41 _public prototype_ `virtual void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L42 _public prototype_ `virtual UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L47 _private member_ `static TCHAR const* TemplateFilePath;` — File holding the hlsl implementation

#### class `UOptimusGroomCollisionReadDataProvider`  
`class UOptimusGroomCollisionReadDataProvider : public UComputeDataProvider`  
_L52-64_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading groom meshes.
- L59 _public member_ `TObjectPtr<UGroomSolverComponent> SolverComponent = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L62 _public prototype_ `virtual FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusGroomCollisionReadDataProviderProxy`  
`class FOptimusGroomCollisionReadDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L66-99_
- inherits: `FComputeDataProviderRenderProxy`
- L69 _public prototype_ `FOptimusGroomCollisionReadDataProviderProxy(UGroomSolverComponent* SolverComponent);`
- L72 _public prototype_ `virtual bool IsValid(FValidationData const& InValidationData) const override;`
- L73 _public prototype_ `virtual void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L74 _public prototype_ `virtual void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L78 _private typedef_ `using FParameters = FOptimusGroomCollisionReadParameters;`
- L81 _private member_ `TMap<TObjectPtr<UMeshComponent>, int32> CollisionObjects;` — Skeletal mesh objects to extract the bones from
- L95 _private member_ `TArray<FCollisionResources> CollisionResources;` — List of collision resources per invocations
- L98 _private member_ `FRDGBufferSRVRef FallbackStructuredSRV = nullptr;` — Fallback resources

#### struct `FOptimusGroomCollisionReadDataProviderProxy::FCollisionResources`  
`struct FCollisionResources`  
_L84-92_
- desc: Collision resources used to dispatch CS on GPU
- L86 _public member_ `FRHIShaderResourceView* VertexPositions = nullptr;`
- L87 _public member_ `FRHIShaderResourceView* TriangleIndices = nullptr;`
- L88 _public member_ `int32 VertexOffset = 0;`
- L89 _public member_ `int32 TriangleOffset = 0;`
- L90 _public member_ `int32 NumVertices = 0;`
- L91 _public member_ `int32 NumTriangles = 0;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsDeformer/Private/DeformerGroomDomainsExec.h` (Private)


#### enum `EOptimusGroomExecDomain`  
`enum class EOptimusGroomExecDomain : uint8`  
_L15-34_
- reflection: `UENUM()`
- L17 _public enumerator_ `None = 0 UMETA(Hidden)`
- L19 _public enumerator_ `ControlPoint = 1 UMETA(DisplayName = "StrandsPoints")` — Run kernel with one thread per strands points.
- L21 _public enumerator_ `Curve UMETA(DisplayName = "StrandsCurves")` — Run kernel with one thread per strands curves.
- L23 _public enumerator_ `StrandsEdges UMETA(DisplayName = "StrandsEdges")` — Run kernel with one thread per strands edges.
- L25 _public enumerator_ `StrandsObjects UMETA(DisplayName = "StrandsObjects")` — Run kernel with one thread per strands objects.
- L27 _public enumerator_ `GuidesPoints UMETA(DisplayName = "GuidesPoints")` — Run kernel with one thread per guides points.
- L29 _public enumerator_ `GuidesCurves UMETA(DisplayName = "GuidesCurves")` — Run kernel with one thread per guides curves.
- L31 _public enumerator_ `GuidesEdges UMETA(DisplayName = "GuidesEdges")` — Run kernel with one thread per guides edges.
- L33 _public enumerator_ `GuidesObjects UMETA(DisplayName = "GuidesObjects")` — Run kernel with one thread per guides objects.

#### class `UOptimusGroomExecDataInterface`  
`class UOptimusGroomExecDataInterface : public UOptimusComputeDataInterface, public IOptimusDeprecatedExecutionDataInterface`  
_L38-77_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface,IOptimusDeprecatedExecutionDataInterface`
- desc: Compute Framework Data Interface for executing kernels over a skinned mesh domain.
- L46 _public prototype_ `virtual FString GetDisplayName() const override;`
- L47 _public prototype_ `virtual FName GetCategory() const override;`
- L48 _public function_ `virtual bool IsVisible() const override`
- L49 _public prototype_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L50 _public prototype_ `virtual TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L54 _public function_ `virtual TCHAR const* GetClassName() const override`
- L55 _public function_ `virtual bool IsExecutionInterface() const override`
- L56 _public prototype_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L57 _public prototype_ `virtual void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L58 _public prototype_ `virtual TCHAR const* GetShaderVirtualPath() const override;`
- L59 _public prototype_ `virtual void GetShaderHash(FString& InOutKey) const override;`
- L60 _public prototype_ `virtual void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L61 _public prototype_ `virtual UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L65 _public prototype_ `virtual FName GetSelectedExecutionDomainName() const override;`
- L69 _public prototype_ `static FName GetExecutionDomainName(const EOptimusGroomExecDomain ExecutionDomain);` — static function to retrieve the execution domain name
- L73 _public member_ `EOptimusGroomExecDomain Domain = EOptimusGroomExecDomain::ControlPoint;` — `UPROPERTY(EditAnywhere, Category = Execution)` — Groom execution domain
- L76 _private member_ `static TCHAR const* TemplateFilePath;`

#### class `UOptimusGroomExecDataProvider`  
`class UOptimusGroomExecDataProvider : public UComputeDataProvider`  
_L81-96_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for executing kernels over a groom execution.
- L87 _public member_ `TObjectPtr<UMeshComponent> MeshComponent = nullptr;` — `UPROPERTY()`
- L91 _public member_ `EOptimusGroomExecDomain Domain = EOptimusGroomExecDomain::ControlPoint;` — `UPROPERTY()` — Groom execution domain
- L94 _public prototype_ `virtual FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusGroomExecDataProviderProxy`  
`class FOptimusGroomExecDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L98-120_
- inherits: `FComputeDataProviderRenderProxy`
- L101 _public prototype_ `FOptimusGroomExecDataProviderProxy(UMeshComponent* MeshComponent, EOptimusGroomExecDomain InDomain);`
- L104 _public prototype_ `virtual int32 GetDispatchThreadCount(TArray<FIntVector>& ThreadCounts) const override;`
- L105 _public prototype_ `virtual bool IsValid(FValidationData const& InValidationData) const override;`
- L106 _public prototype_ `virtual void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L110 _private typedef_ `using FParameters = FGroomExecDataInterfaceParameters;`
- L113 _private member_ `TArray<TRefCountPtr<const FHairGroupInstance>> GroupInstances;` — List of instances (invocations) used in that data interface
- L116 _private member_ `TArray<int32> GroupCounts;` — Number of elements for each invocation
- L119 _private member_ `EOptimusGroomExecDomain Domain = EOptimusGroomExecDomain::ControlPoint;` — Groom execution domain

### `Plugins/Runtime/HairStrands/Source/HairStrandsDeformer/Private/DeformerGroomDomainsSource.h` (Private)


#### class `UOptimusGroomAssetComponentSource`  
`class UOptimusGroomAssetComponentSource : public UOptimusComponentSource`  
_L14-51_
- reflection: `UCLASS()`
- inherits: `UOptimusComponentSource`
- desc: Execution domain that will be used by the groom asset optimus data interfaces
- L42 _public prototype_ `virtual FText GetDisplayName() const override;`
- L43 _public function_ `virtual FName GetBindingName() const override`
- L44 _public prototype_ `virtual TSubclassOf<UActorComponent> GetComponentClass() const override;`
- L45 _public prototype_ `virtual TArray<FName> GetExecutionDomains() const override;`
- L46 _public prototype_ `virtual int32 GetLodIndex(const UActorComponent* InComponent) const override;`
- L47 _public prototype_ `virtual uint32 GetDefaultNumInvocations(const UActorComponent* InComponent, int32 InLod) const override;`
- L48 _public prototype_ `virtual bool GetComponentElementCountsForExecutionDomain(FName InDomainName, const UActorComponent* InComponent, int32 InLodIndex, TArray<int32>& OutInvocationElementCounts) const override;`
- L49 _public prototype_ `virtual bool IsUsableAsPrimarySource() const override;`

#### struct `UOptimusGroomAssetComponentSource::FGuidesExecutionDomains`  
`struct FGuidesExecutionDomains`  
_L19-25_
- L21 _public member_ `static FName Edges;`
- L22 _public member_ `static FName Curves;`
- L23 _public member_ `static FName Objects;`
- L24 _public member_ `static FName Points;`

#### struct `UOptimusGroomAssetComponentSource::FStrandsExecutionDomains`  
`struct FStrandsExecutionDomains`  
_L27-33_
- L29 _public member_ `static FName Edges;`
- L30 _public member_ `static FName Curves;`
- L31 _public member_ `static FName Objects;`
- L32 _public member_ `static FName Points;`

#### struct `UOptimusGroomAssetComponentSource::FMeshesExecutionDomains`  
`struct FMeshesExecutionDomains`  
_L35-39_
- L37 _public member_ `static FName Bones;`
- L38 _public member_ `static FName Vertices;`

#### class `UOptimusGroomSolverComponentSource`  
`class UOptimusGroomSolverComponentSource : public UOptimusComponentSource`  
_L55-94_
- reflection: `UCLASS()`
- inherits: `UOptimusComponentSource`
- desc: Execution domain that will be used by the groom solver optimus data interfaces
- L60 _public member_ `static constexpr int32 GroupSize = 64;`
- L85 _public prototype_ `virtual FText GetDisplayName() const override;`
- L86 _public function_ `virtual FName GetBindingName() const override`
- L87 _public prototype_ `virtual TSubclassOf<UActorComponent> GetComponentClass() const override;`
- L88 _public prototype_ `virtual TArray<FName> GetExecutionDomains() const override;`
- L89 _public prototype_ `virtual int32 GetLodIndex(const UActorComponent* InComponent) const override;`
- L90 _public prototype_ `virtual uint32 GetDefaultNumInvocations(const UActorComponent* InComponent, int32 InLod) const override;`
- L91 _public prototype_ `virtual bool GetComponentElementCountsForExecutionDomain(FName InDomainName, const UActorComponent* InComponent, int32 InLodIndex, TArray<int32>& OutInvocationElementCounts) const override;`
- L92 _public prototype_ `virtual bool IsUsableAsPrimarySource() const override;`

#### struct `UOptimusGroomSolverComponentSource::FSolverExecutionDomains`  
`struct FSolverExecutionDomains`  
_L62-68_
- L64 _public member_ `static FName Edges;`
- L65 _public member_ `static FName Curves;`
- L66 _public member_ `static FName Objects;`
- L67 _public member_ `static FName Points;`

#### struct `UOptimusGroomSolverComponentSource::FDynamicExecutionDomains`  
`struct FDynamicExecutionDomains`  
_L70-75_
- L72 _public member_ `static FName Points;`
- L73 _public member_ `static FName Curves;`
- L74 _public member_ `static FName Edges;`

#### struct `UOptimusGroomSolverComponentSource::FKinematicExecutionDomains`  
`struct FKinematicExecutionDomains`  
_L77-82_
- L79 _public member_ `static FName Points;`
- L80 _public member_ `static FName Curves;`
- L81 _public member_ `static FName Edges;`

#### class `UOptimusGroomCollisionComponentSource`  
`class UOptimusGroomCollisionComponentSource : public UOptimusComponentSource`  
_L98-122_
- reflection: `UCLASS()`
- inherits: `UOptimusComponentSource`
- desc: Execution domain that will be used by the groom collision optimus data interfaces
- L103 _public member_ `static constexpr int32 GroupSize = 64;`
- L113 _public prototype_ `virtual FText GetDisplayName() const override;`
- L114 _public function_ `virtual FName GetBindingName() const override`
- L115 _public prototype_ `virtual TSubclassOf<UActorComponent> GetComponentClass() const override;`
- L116 _public prototype_ `virtual TArray<FName> GetExecutionDomains() const override;`
- L117 _public prototype_ `virtual int32 GetLodIndex(const UActorComponent* InComponent) const override;`
- L118 _public prototype_ `virtual uint32 GetDefaultNumInvocations(const UActorComponent* InComponent, int32 InLod) const override;`
- L119 _public prototype_ `virtual bool GetComponentElementCountsForExecutionDomain(FName InDomainName, const UActorComponent* InComponent, int32 InLodIndex, TArray<int32>& OutInvocationElementCounts) const override;`
- L120 _public prototype_ `virtual bool IsUsableAsPrimarySource() const override;`

#### struct `UOptimusGroomCollisionComponentSource::FCollisionExecutionDomains`  
`struct FCollisionExecutionDomains`  
_L105-110_
- L107 _public member_ `static FName Vertices;`
- L108 _public member_ `static FName Triangles;`
- L109 _public member_ `static FName Implicits;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsDeformer/Private/DeformerGroomGuidesRead.h` (Private)


#### class `UOptimusGroomGuidesReadDataInterface`  
`class UOptimusGroomGuidesReadDataInterface : public UOptimusComputeDataInterface`  
_L20-46_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading groom guides.
- L27 _public prototype_ `virtual FString GetDisplayName() const override;`
- L28 _public prototype_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L29 _public prototype_ `virtual TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L33 _public function_ `virtual TCHAR const* GetClassName() const override`
- L34 _public prototype_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L35 _public prototype_ `virtual void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L36 _public prototype_ `virtual TCHAR const* GetShaderVirtualPath() const override;`
- L37 _public prototype_ `virtual void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const override;`
- L38 _public prototype_ `virtual void GetShaderHash(FString& InOutKey) const override;`
- L39 _public prototype_ `virtual void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L40 _public prototype_ `virtual UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L45 _private member_ `static TCHAR const* TemplateFilePath;` — File holding the hlsl implementation

#### class `UOptimusGroomGuidesReadDataProvider`  
`class UOptimusGroomGuidesReadDataProvider : public UComputeDataProvider`  
_L50-62_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading groom guides.
- L57 _public member_ `TObjectPtr<UMeshComponent> MeshComponent = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L60 _public prototype_ `virtual FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusGroomGuidesReadDataProviderProxy`  
`class FOptimusGroomGuidesReadDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L64-104_
- inherits: `FComputeDataProviderRenderProxy`
- L67 _public prototype_ `FOptimusGroomGuidesReadDataProviderProxy(UMeshComponent* MeshComponent);`
- L70 _public prototype_ `virtual bool IsValid(FValidationData const& InValidationData) const override;`
- L71 _public prototype_ `virtual void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L72 _public prototype_ `virtual void GatherPermutations(FPermutationData& InOutPermutationData) const override;`
- L73 _public prototype_ `virtual void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L77 _private typedef_ `using FParameters = FOptimusGroomGuidesReadParameters;`
- L80 _private member_ `TArray<TRefCountPtr<const FHairGroupInstance>> GroupInstances;` — List of instances (invocations) used in that data interface
- L92 _private member_ `TArray<FBindingResources> BindingResources;`
- L103 _private member_ `TArray<FInstanceResources> InstanceResources;`

#### struct `FOptimusGroomGuidesReadDataProviderProxy::FBindingResources`  
`struct FBindingResources`  
_L83-91_
- desc: Binding Resources used to dispatch CS on GPU
- L85 _public member_ `FMatrix44f ObjectRestTransform = FMatrix44f::Identity;`
- L86 _public member_ `FMatrix44f ObjectDeformedTransform = FMatrix44f::Identity;`
- L87 _public member_ `FRDGBufferSRVRef TriangleRestPositions = nullptr;`
- L88 _public member_ `FRDGBufferSRVRef TriangleDeformedPositions = nullptr;`
- L89 _public member_ `FRDGBufferSRVRef CurveBarycentricCoordinates = nullptr;`
- L90 _public member_ `FRDGBufferSRVRef CurveTriangleIndices = nullptr;`

#### struct `FOptimusGroomGuidesReadDataProviderProxy::FInstanceResources`  
`struct FInstanceResources`  
_L95-102_
- desc: Instance resources used to dispatch CS on GPU
- L97 _public member_ `FRDGBufferSRVRef CurvePointOffsets = nullptr;`
- L98 _public member_ `FRDGBufferSRVRef PointRestPositions = nullptr;`
- L99 _public member_ `FRDGBufferSRVRef PointCurveIndices = nullptr;`
- L100 _public member_ `FRDGBufferSRVRef CurveMapping = nullptr;`
- L101 _public member_ `FRDGBufferSRVRef PointMapping = nullptr;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsDeformer/Private/DeformerGroomGuidesWrite.h` (Private)


#### class `UOptimusGroomGuidesWriteDataInterface`  
`class UOptimusGroomGuidesWriteDataInterface : public UOptimusComputeDataInterface`  
_L19-45_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for writing groom strands.
- L25 _public prototype_ `virtual FString GetDisplayName() const override;`
- L26 _public prototype_ `virtual FName GetCategory() const override;`
- L27 _public prototype_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L28 _public prototype_ `virtual TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L32 _public function_ `virtual TCHAR const* GetClassName() const override`
- L33 _public prototype_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L34 _public prototype_ `virtual void GetSupportedOutputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L35 _public prototype_ `virtual void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L36 _public prototype_ `virtual TCHAR const* GetShaderVirtualPath() const override;`
- L37 _public prototype_ `virtual void GetShaderHash(FString& InOutKey) const override;`
- L38 _public prototype_ `virtual void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L39 _public prototype_ `virtual UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L44 _private member_ `static TCHAR const* TemplateFilePath;` — File holding the hlsl implementation

#### class `UOptimusGroomGuidesWriteDataProvider`  
`class UOptimusGroomGuidesWriteDataProvider : public UComputeDataProvider`  
_L49-63_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for writing skinned mesh.
- L55 _public member_ `TObjectPtr<UMeshComponent> MeshComponent = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L58 _public member_ `uint64 OutputMask = 0;` — Output mask used to know the buffer format
- L61 _public prototype_ `virtual FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusGroomGuidesWriteProviderProxy`  
`class FOptimusGroomGuidesWriteProviderProxy : public FComputeDataProviderRenderProxy`  
_L65-93_
- inherits: `FComputeDataProviderRenderProxy`
- L68 _public prototype_ `FOptimusGroomGuidesWriteProviderProxy(UMeshComponent* MeshComponent, uint64 InOutputMask);`
- L71 _public prototype_ `virtual bool IsValid(FValidationData const& InValidationData) const override;`
- L72 _public prototype_ `virtual void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L73 _public prototype_ `virtual void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L77 _private typedef_ `using FParameters = FOptimusGroomGuidesWriteParameters;`
- L80 _private member_ `TArray<TRefCountPtr<const FHairGroupInstance>> GroupInstances;` — List of instances (invocations) used in that data interface
- L83 _private member_ `uint64 OutputMask = 0;` — Output mask for gpu buffer format
- L92 _private member_ `TArray<FInstanceResources> InstanceResources;`

#### struct `FOptimusGroomGuidesWriteProviderProxy::FInstanceResources`  
`struct FInstanceResources`  
_L86-91_
- desc: Instance resources used to dispatch CS on GPU
- L88 _public member_ `FRDGBufferSRVRef DeformedPositionOffset = nullptr;`
- L89 _public member_ `FRDGBufferSRVRef PointRestPositions = nullptr;`
- L90 _public member_ `FRDGBufferUAVRef PointDeformedPositions = nullptr;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsDeformer/Private/DeformerGroomInterfaceUtils.h` (Private)


#### struct `UE::Groom::Private::FGroupElements`  
`struct FGroupElements`  
_L507-512_
- L509 _public member_ `TArray<int32> GroupIndices;`
- L510 _public member_ `TArray<int32> GroupOffsets;`
- L511 _public member_ `TArray<TRefCountPtr<const FHairGroupInstance>> GroupInstances;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Groom` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Groom`)
- L18 _function_ `FORCEINLINE bool HasDeformationEnabledOrHasMeshDeformer(const UGroomComponent* GroomComponent, const int32 GroupIndex)` (scope `UE::Groom::Private`)
- L23 _function_ `FORCEINLINE USkeletalMeshComponent* GetGroupSkelMesh(const UGroomComponent* GroomComponent, const int32 GroupIndex, int32& MeshLOD)` (scope `UE::Groom::Private`)
- L49 _function_ `FORCEINLINE void GroomComponentsToInstances(const TArray<const UGroomComponent*>& GroomComponents, TArray<TRefCountPtr<const FHairGroupInstance>>& GroupInstances)` (scope `UE::Groom::Private`)
- L68 _function_ `FORCEINLINE void GroomComponentsToSkelmeshes(const TArray<const UGroomComponent*>& GroomComponents, TArray<const FSkeletalMeshObject*>& SkeletalMeshes, TArray<FMatrix44f>& SkeletalTransforms, TArray<TArray<FMatrix44f>>& BonesRefToLocals, TArray<TArray<FMatrix44f>>& BindTransforms, TArray<TRefCountPtr<const FHairGroupInstance>>& GroupInstances)` (scope `UE::Groom::Private`)
- L137 _function_ `FORCEINLINE void GatherGroomComponents(const UActorComponent* ActorComponent, TArray<const UGroomComponent*>& GroomComponents)` (scope `UE::Groom::Private`)
- L153 _function_ `FORCEINLINE void GatherGroupInstances(const UActorComponent* ActorComponent, TArray<TRefCountPtr<const FHairGroupInstance>>& GroupInstances)` (scope `UE::Groom::Private`)
- L161 _function_ `FORCEINLINE void GatherGroupSkelmeshes(const UActorComponent* ActorComponent, TArray<const FSkeletalMeshObject*>& SkeletalMeshes, TArray<FMatrix44f>& SkeletalTransforms, TArray<TArray<FMatrix44f>>& BonesRefToLocals, TArray<TArray<FMatrix44f>>& BindTransforms, TArray<TRefCountPtr<const FHairGroupInstance>>& GroupInstances)` (scope `UE::Groom::Private`)
- L171 _function_ `template<typename DataType> static bool HaveValidInstanceResources(const DataType& InstanceData)` (scope `UE::Groom::Private`)
- L184 _function_ `static bool HaveGuidesInstanceResources(const TArray<TRefCountPtr<const FHairGroupInstance>>& GroupInstances)` (scope `UE::Groom::Private`)
- L196 _function_ `FORCEINLINE bool HaveStrandsInstanceResources(const TArray<TRefCountPtr<const FHairGroupInstance>>& GroupInstances)` (scope `UE::Groom::Private`)
- L209 _function_ `template<typename DataType> static bool HaveValidSkinnedResources(const DataType& SkinnedData, const int32 LODIndex)` (scope `UE::Groom::Private`)
- L225 _function_ `static bool HaveGuidesSkinnedResources(const TArray<TRefCountPtr<const FHairGroupInstance>>& GroupInstances)` (scope `UE::Groom::Private`)
- L247 _function_ `FORCEINLINE bool HaveStrandsSkinnedResources(const TArray<TRefCountPtr<const FHairGroupInstance>>& GroupInstances)` (scope `UE::Groom::Private`)
- L269 _function_ `static void GetGroomGroupElementOffsets(const UGroomComponent* GroomComponent, const FName DomainName, TArray<int32>& GroupOffsets, const bool bSourceElements = false)` (scope `UE::Groom::Private`)
- L339 _function_ `static int32 GetGroomInvocationElementCounts(const TArray<const UGroomComponent*>& GroomComponents, const FName DomainName, TArray<int32>& InvocationCounts, const bool bSourceElements = false)` (scope `UE::Groom::Private`)
- L364 _function_ `static int32 FillCollisionOverlappingComponents(const TSet<TObjectPtr<UGroomComponent>>& GroomComponents, const TMap<TObjectPtr<UMeshComponent>, int32>& CollisionComponents, TArray<TPair<TObjectPtr<UMeshComponent>, int32>>& OverlappingComponents)` (scope `UE::Groom::Private`)
- L395 _function_ `static int32 GetCollisionNumInvocations(const TArray<TPair<TObjectPtr<UMeshComponent>, int32>>& CollisionComponents)` (scope `UE::Groom::Private`)
- L436 _function_ `static int32 GetCollisionInvocationElementCounts(const TArray<TPair<TObjectPtr<UMeshComponent>, int32>>& CollisionComponents, const FName DomainName, TArray<int32>& InvocationCounts)` (scope `UE::Groom::Private`)
- L514 _function_ `FORCEINLINE void GetGroomInvocationElementGroups(const TArray<const UGroomComponent*>& GroomComponents, const FName DomainName, TArray<TPair<UGroomAsset*, FGroupElements>>& InvocationGroups, const bool bSourceElements = false)` (scope `UE::Groom::Private`)

### `Plugins/Runtime/HairStrands/Source/HairStrandsDeformer/Private/DeformerGroomMeshesRead.h` (Private)


#### class `UOptimusGroomMeshesReadDataInterface`  
`class UOptimusGroomMeshesReadDataInterface : public UOptimusComputeDataInterface`  
_L21-47_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading groom meshes.
- L28 _public prototype_ `virtual FString GetDisplayName() const override;`
- L29 _public prototype_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L30 _public prototype_ `virtual TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L34 _public function_ `virtual TCHAR const* GetClassName() const override`
- L35 _public prototype_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L36 _public prototype_ `virtual void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L37 _public prototype_ `virtual TCHAR const* GetShaderVirtualPath() const override;`
- L38 _public prototype_ `virtual void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const override;`
- L39 _public prototype_ `virtual void GetShaderHash(FString& InOutKey) const override;`
- L40 _public prototype_ `virtual void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L41 _public prototype_ `virtual UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L46 _private member_ `static TCHAR const* TemplateFilePath;` — File holding the hlsl implementation

#### class `UOptimusGroomMeshesReadDataProvider`  
`class UOptimusGroomMeshesReadDataProvider : public UComputeDataProvider`  
_L51-63_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading groom meshes.
- L58 _public member_ `TObjectPtr<UMeshComponent> MeshComponent = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L61 _public prototype_ `virtual FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusGroomMeshesReadDataProviderProxy`  
`class FOptimusGroomMeshesReadDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L65-99_
- inherits: `FComputeDataProviderRenderProxy`
- L68 _public prototype_ `FOptimusGroomMeshesReadDataProviderProxy(UMeshComponent* MeshComponent);`
- L71 _public prototype_ `virtual bool IsValid(FValidationData const& InValidationData) const override;`
- L72 _public prototype_ `virtual void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L73 _public prototype_ `virtual void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L77 _private typedef_ `using FParameters = FOptimusGroomMeshesReadParameters;`
- L80 _private member_ `TArray<const FSkeletalMeshObject*> SkeletalMeshObjects;` — Skeletal mesh objects to extract the bones from
- L83 _private member_ `TArray<FMatrix44f> SkeletalMeshTransforms;` — Skeletal mesh transforms in group space
- L86 _private member_ `TArray<TArray<FMatrix44f>> BonesRefToLocals;` — Bones refs to locals matrices
- L89 _private member_ `TArray<TArray<FMatrix44f>> BindTransforms;` — Bind Transforms
- L92 _private member_ `TArray<TRefCountPtr<const FHairGroupInstance>> GroupInstances;` — List of instances (invocations) used in that data interface
- L95 _private member_ `TArray<FRDGBufferSRVRef> BoneMatricesResources;` — Bones Resources used to dispatch CS on GPU
- L98 _private member_ `FRDGBufferSRVRef FallbackStructuredSRV = nullptr;` — Fallback resources

### `Plugins/Runtime/HairStrands/Source/HairStrandsDeformer/Private/DeformerGroomSolverRead.h` (Private)


#### class `UOptimusGroomSolverReadDataInterface`  
`class UOptimusGroomSolverReadDataInterface : public UOptimusComputeDataInterface`  
_L25-59_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading groom guides.
- L31 _public prototype_ `static FName GetResetSimulationTriggerName();`
- L34 _public prototype_ `virtual FString GetDisplayName() const override;`
- L35 _public prototype_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L36 _public prototype_ `virtual TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L37 _public prototype_ `virtual TArray<FOptimusCDIPropertyPinDefinition> GetPropertyPinDefinitions() const override;`
- L38 _public prototype_ `virtual void RegisterTypes() override;`
- L42 _public function_ `virtual TCHAR const* GetClassName() const override`
- L43 _public prototype_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L44 _public prototype_ `virtual void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L45 _public prototype_ `virtual TCHAR const* GetShaderVirtualPath() const override;`
- L46 _public prototype_ `virtual void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const override;`
- L47 _public prototype_ `virtual void GetShaderHash(FString& InOutKey) const override;`
- L48 _public prototype_ `virtual void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L49 _public prototype_ `virtual UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L50 _public function_ `virtual bool CanSupportUnifiedDispatch() const override`
- L55 _private member_ `static TCHAR const* TemplateFilePath;` — File holding the hlsl implementation
- L58 _private member_ `FName ResetSimulationTrigger = NAME_None;` — `UPROPERTY(EditAnywhere, Category = "Simulation Trigger")`

#### class `UOptimusGroomSolverReadDataProvider`  
`class UOptimusGroomSolverReadDataProvider : public UComputeDataProvider, public IOptimusDeformerInstanceAccessor`  
_L63-89_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider,IOptimusDeformerInstanceAccessor`
- desc: Compute Framework Data Provider for reading groom guides.
- L70 _public prototype_ `virtual void SetDeformerInstance(UOptimusDeformerInstance* InInstance) override;`
- L74 _public member_ `TObjectPtr<UGroomSolverComponent> SolverComponent = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L77 _public prototype_ `virtual FComputeDataProviderRenderProxy* GetRenderProxy() override;`
- L82 _public member_ `TObjectPtr<UOptimusDeformerInstance> DeformerInstance = nullptr;` — `UPROPERTY()` — Deformer instance using this provider
- L85 _public member_ `TWeakObjectPtr<const UOptimusGroomSolverReadDataInterface> WeakDataInterface;` — Data interface from which this provider has been created
- L88 _public member_ `int32 bResetSimulationCount = 0;` — Reset simulation count

#### class `FOptimusGroomSolverReadDataProviderProxy`  
`class FOptimusGroomSolverReadDataProviderProxy : public FComputeDataProviderRenderProxy`  
_L91-165_
- inherits: `FComputeDataProviderRenderProxy`
- L94 _public prototype_ `FOptimusGroomSolverReadDataProviderProxy(UGroomSolverComponent* SolverComponent, const bool bResetSimulation);`
- L97 _public prototype_ `virtual bool IsValid(FValidationData const& InValidationData) const override;`
- L98 _public prototype_ `virtual void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L99 _public prototype_ `virtual void GatherPermutations(FPermutationData& InOutPermutationData) const override;`
- L100 _public prototype_ `virtual void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L104 _private typedef_ `using FParameters = FOptimusGroomSolverReadParameters;`
- L107 _private prototype_ `void CreateInternalBuffers(FRDGBuilder& GraphBuilder);` — Create internal buffers
- L110 _private member_ `FGroomSolverSettings SolverSettings;` — Solver settings used in the solver
- L113 _private member_ `FRDGBufferRef ObjectPointOffsetsBuffer = nullptr;` — Groom solver buffers built from the deformer
- L114 _private member_ `FRDGBufferRef ObjectCurveOffsetsBuffer = nullptr;`
- L115 _private member_ `FRDGBufferRef ObjectNumPointsBuffer = nullptr;`
- L116 _private member_ `FRDGBufferRef ObjectNumCurvesBuffer = nullptr;`
- L117 _private member_ `FRDGBufferRef PointObjectIndicesBuffer = nullptr;`
- L118 _private member_ `FRDGBufferRef CurveObjectIndicesBuffer = nullptr;`
- L119 _private member_ `FRDGBufferRef DynamicPointIndicesBuffer = nullptr;`
- L120 _private member_ `FRDGBufferRef DynamicCurveIndicesBuffer = nullptr;`
- L121 _private member_ `FRDGBufferRef KinematicPointIndicesBuffer = nullptr;`
- L122 _private member_ `FRDGBufferRef KinematicCurveIndicesBuffer = nullptr;`
- L123 _private member_ `FRDGBufferRef ObjectDistanceLodsBuffer = nullptr;`
- L126 _private member_ `TArray<int32> PointsCounts;` — Invocation points count
- L129 _private member_ `TArray<int32> CurvesCounts;` — Invocation curves count
- L132 _private member_ `int32 NumPoints = 0;` — Total number of points
- L135 _private member_ `int32 NumCurves = 0;` — Total number of curves
- L138 _private member_ `FRDGBufferSRVRef ObjectPointOffsetsResource = nullptr;` — Groom solver resources built from the deformer
- L139 _private member_ `FRDGBufferSRVRef ObjectCurveOffsetsResource = nullptr;`
- L140 _private member_ `FRDGBufferSRVRef ObjectNumPointsResource = nullptr;`
- L141 _private member_ `FRDGBufferSRVRef ObjectNumCurvesResource = nullptr;`
- L142 _private member_ `FRDGBufferSRVRef PointObjectIndicesResource = nullptr;`
- L143 _private member_ `FRDGBufferSRVRef CurveObjectIndicesResource = nullptr;`
- L144 _private member_ `FRDGBufferSRVRef DynamicPointIndicesResource = nullptr;`
- L145 _private member_ `FRDGBufferSRVRef DynamicCurveIndicesResource = nullptr;`
- L146 _private member_ `FRDGBufferSRVRef KinematicPointIndicesResource = nullptr;`
- L147 _private member_ `FRDGBufferSRVRef KinematicCurveIndicesResource = nullptr;`
- L148 _private member_ `FRDGBufferSRVRef ObjectDistanceLodsResource = nullptr;`
- L151 _private member_ `TArray<TRefCountPtr<const FHairGroupInstance>> GroupInstances;` — List of instances (invocations) used in that data interface
- L154 _private member_ `bool bResetSimulationTrigger = false;` — Reset simulation trigger
- L159 _private member_ `FSceneInterface* SceneInterface;` — Scene interface used to retrieve the TLAS
- L162 _private member_ `FRHIShaderResourceView* AccelerationStructure = nullptr;` — Acceleration structure used for geometric collisions

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Groom` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Groom`)

### `Plugins/Runtime/HairStrands/Source/HairStrandsDeformer/Private/DeformerGroomStrandsRead.h` (Private)


#### class `UOptimusGroomStrandsReadDataInterface`  
`class UOptimusGroomStrandsReadDataInterface : public UOptimusComputeDataInterface`  
_L18-43_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for reading groom strands.
- L24 _public prototype_ `virtual FString GetDisplayName() const override;`
- L25 _public prototype_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L26 _public prototype_ `virtual TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L30 _public function_ `virtual TCHAR const* GetClassName() const override`
- L31 _public prototype_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L32 _public prototype_ `virtual void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L33 _public prototype_ `virtual TCHAR const* GetShaderVirtualPath() const override;`
- L34 _public prototype_ `virtual void GetPermutations(FComputeKernelPermutationVector& OutPermutationVector) const override;`
- L35 _public prototype_ `virtual void GetShaderHash(FString& InOutKey) const override;`
- L36 _public prototype_ `virtual void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L37 _public prototype_ `virtual UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L42 _private member_ `static TCHAR const* TemplateFilePath;` — File holding the hlsl implementation

#### class `UOptimusGroomStrandsReadDataProvider`  
`class UOptimusGroomStrandsReadDataProvider : public UComputeDataProvider`  
_L47-58_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for reading groom strands.
- L53 _public member_ `TObjectPtr<UMeshComponent> MeshComponent = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L56 _public prototype_ `virtual FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusGroomStrandsReadProviderProxy`  
`class FOptimusGroomStrandsReadProviderProxy : public FComputeDataProviderRenderProxy`  
_L60-98_
- inherits: `FComputeDataProviderRenderProxy`
- L63 _public prototype_ `FOptimusGroomStrandsReadProviderProxy(UMeshComponent* InGroomComponent);`
- L66 _public prototype_ `virtual bool IsValid(FValidationData const& InValidationData) const override;`
- L67 _public prototype_ `virtual void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L68 _public prototype_ `virtual void GatherPermutations(FPermutationData& InOutPermutationData) const override;`
- L69 _public prototype_ `virtual void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L73 _private typedef_ `using FParameters = FOptimusGroomStrandsReadParameters;`
- L76 _private member_ `TArray<TRefCountPtr<const FHairGroupInstance>> GroupInstances;` — List of instances (invocations) used in that data interface
- L90 _private member_ `TArray<FBindingResources> BindingResources;`
- L93 _private member_ `TArray<FHairStrandsInstanceResourceParameters> GroupResources;` — Resources used to dispatch CS on GPU
- L94 _private member_ `TArray<FHairStrandsInstanceInterpolationParameters> GroupInterpolations;`
- L97 _private member_ `FRDGBufferSRVRef FallbackByteAddressSRV = nullptr;` — Fallback resources

#### struct `FOptimusGroomStrandsReadProviderProxy::FBindingResources`  
`struct FBindingResources`  
_L79-89_
- desc: Binding Resources
- L81 _public member_ `FMatrix44f RigidRestTransform = FMatrix44f::Identity;`
- L82 _public member_ `FMatrix44f RigidDeformedTransform = FMatrix44f::Identity;`
- L83 _public member_ `FRDGBufferSRVRef TriangleRestPositions = nullptr;`
- L84 _public member_ `FRDGBufferSRVRef TriangleDeformedPositions = nullptr;`
- L85 _public member_ `FRDGBufferSRVRef CurveBarycentricCoordinates = nullptr;`
- L86 _public member_ `FRDGBufferSRVRef CurveTriangleIndices = nullptr;`
- L87 _public member_ `FRDGBufferSRVRef CurveInterpolationBuffer = nullptr;`
- L88 _public member_ `FRDGBufferSRVRef PointInterpolationBuffer = nullptr;`

### `Plugins/Runtime/HairStrands/Source/HairStrandsDeformer/Private/DeformerGroomStrandsWrite.h` (Private)


#### class `UOptimusGroomStrandsWriteDataInterface`  
`class UOptimusGroomStrandsWriteDataInterface : public UOptimusComputeDataInterface`  
_L20-46_
- reflection: `UCLASS(Category = ComputeFramework)`
- inherits: `UOptimusComputeDataInterface`
- desc: Compute Framework Data Interface for writing groom strands.
- L26 _public prototype_ `virtual FString GetDisplayName() const override;`
- L27 _public prototype_ `virtual FName GetCategory() const override;`
- L28 _public prototype_ `virtual TArray<FOptimusCDIPinDefinition> GetPinDefinitions() const override;`
- L29 _public prototype_ `virtual TSubclassOf<UActorComponent> GetRequiredComponentClass() const override;`
- L33 _public function_ `virtual TCHAR const* GetClassName() const override`
- L34 _public prototype_ `virtual void GetSupportedInputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L35 _public prototype_ `virtual void GetSupportedOutputs(TArray<FShaderFunctionDefinition>& OutFunctions) const override;`
- L36 _public prototype_ `virtual void GetShaderParameters(TCHAR const* UID, FShaderParametersMetadataBuilder& InOutBuilder, FShaderParametersMetadataAllocations& InOutAllocations) const override;`
- L37 _public prototype_ `virtual TCHAR const* GetShaderVirtualPath() const override;`
- L38 _public prototype_ `virtual void GetShaderHash(FString& InOutKey) const override;`
- L39 _public prototype_ `virtual void GetHLSL(FString& OutHLSL, FString const& InDataInterfaceName) const override;`
- L40 _public prototype_ `virtual UComputeDataProvider* CreateDataProvider(TObjectPtr<UObject> InBinding, uint64 InInputMask, uint64 InOutputMask) const override;`
- L45 _private member_ `static TCHAR const* TemplateFilePath;` — File holding the hlsl implementation

#### class `UOptimusGroomStrandsWriteDataProvider`  
`class UOptimusGroomStrandsWriteDataProvider : public UComputeDataProvider`  
_L50-64_
- reflection: `UCLASS(BlueprintType, editinlinenew, Category = ComputeFramework)`
- inherits: `UComputeDataProvider`
- desc: Compute Framework Data Provider for writing skinned mesh.
- L56 _public member_ `TObjectPtr<UMeshComponent> MeshComponent = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Binding)`
- L59 _public member_ `uint64 OutputMask = 0;` — Output mask used to know the buffer format
- L62 _public prototype_ `virtual FComputeDataProviderRenderProxy* GetRenderProxy() override;`

#### class `FOptimusGroomStrandsWriteProviderProxy`  
`class FOptimusGroomStrandsWriteProviderProxy : public FComputeDataProviderRenderProxy`  
_L66-101_
- inherits: `FComputeDataProviderRenderProxy`
- L69 _public prototype_ `FOptimusGroomStrandsWriteProviderProxy(UMeshComponent* MeshComponent, uint64 InOutputMask);`
- L72 _public prototype_ `virtual bool IsValid(FValidationData const& InValidationData) const override;`
- L73 _public prototype_ `virtual void AllocateResources(FRDGBuilder& GraphBuilder, FAllocationData const& InAllocationData) override;`
- L74 _public prototype_ `virtual void GatherDispatchData(FDispatchData const& InDispatchData) override;`
- L78 _private typedef_ `using FParameters = FOptimusGroomStrandsWriteParameters;`
- L81 _private member_ `TArray<TRefCountPtr<const FHairGroupInstance>> GroupInstances;` — List of instances (invocations) used in that data interface
- L84 _private member_ `uint64 OutputMask = 0;` — Output mask for gpu buffer format
- L95 _private member_ `TArray<FDispatchResources> GroupResources;`
- L98 _private member_ `FRDGBufferSRVRef FallbackPositionBufferSRV= nullptr;` — Fallback resources
- L99 _private member_ `FRDGBufferUAVRef FallbackPositionBufferUAV = nullptr;`
- L100 _private member_ `FRDGBufferUAVRef FallbackAttributeBufferUAV = nullptr;`

#### struct `FOptimusGroomStrandsWriteProviderProxy::FDispatchResources`  
`struct FDispatchResources`  
_L87-94_
- desc: Resources used to dispatch CS on GPU
- L89 _public member_ `FRDGBufferSRVRef DeformedPositionOffset = nullptr;`
- L90 _public member_ `FRDGBufferSRVRef PointRestPositions = nullptr;`
- L91 _public member_ `FRDGBufferUAVRef OutPointDeformedPositions = nullptr;`
- L92 _public member_ `FRDGBufferUAVRef OutPointAttributeBuffer = nullptr;`
- L93 _public member_ `FRDGBufferUAVRef OutCurveAttributeBuffer = nullptr;`
