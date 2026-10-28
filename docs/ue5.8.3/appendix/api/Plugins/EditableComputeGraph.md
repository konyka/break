# Plugins / EditableComputeGraph

- module root: `Plugins/Runtime/ComputeFramework/Source/EditableComputeGraph`
- headers: 1; symbols: 39
- symbol kinds: class=1, delegate=1, function=2, macro=1, member=22, prototype=7, struct=5
- PrivateDependencyModuleNames: ComputeDataInterface, RHI, RenderCore
- PublicDependencyModuleNames: ComputeFramework, Core, CoreUObject, Engine

### `Plugins/Runtime/ComputeFramework/Source/EditableComputeGraph/Internal/ComputeFramework/EditableComputeGraph.h` (Internal)


#### struct `FKernelPin`  
`struct FKernelPin`  
_L17-34_
- reflection: `USTRUCT()`
- desc: Describes one kernel pin: a binding between a kernel HLSL parameter and a data interface function.
- L23 _public member_ `FString KernelFunctionName;` — `UPROPERTY(EditAnywhere, Category = "Pin", meta = (DisplayName = "Kernel Function"))` — Name of the corresponding parameter in the kernel HLSL.
- L26 _public member_ `FName DataInterfaceName;` — `UPROPERTY(EditAnywhere, Category = "Pin", meta = (DisplayName = "Data Interface"))` — Name of a DataInterface entry in the owning FComputeGraphDesc.
- L29 _public member_ `FString DataInterfaceFunctionName;` — `UPROPERTY(EditAnywhere, Category = "Pin", meta = (DisplayName = "Data Interface Function"))` — Name of the function exposed by that data interface.
- L33 _public member_ `bool bOrphaned = false;` — `UPROPERTY(Transient, VisibleAnywhere, Category = "Pin")` — Transient value that the details customization uses this to display an orphan warning.

#### struct `FComputeGraphKernelDesc`  
`struct FComputeGraphKernelDesc`  
_L38-60_
- reflection: `USTRUCT()`
- desc: Describes a single compute kernel: shader source and associated properties.
- L44 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Kernel")` — Unique name identifying this kernel within the graph.
- L47 _public member_ `FString SourceText;` — `UPROPERTY(EditAnywhere, Category = "Kernel")` — Full HLSL source text for this kernel.
- L50 _public member_ `FString EntryPoint;` — `UPROPERTY(EditAnywhere, Category = "Kernel")` — Name of the HLSL function that serves as the compute shader entry point.
- L53 _public member_ `FIntVector GroupSize = FIntVector(64, 1, 1);` — `UPROPERTY(EditAnywhere, Category = "Kernel")` — Thread-group dimensions passed to the shader compiler (X * Y * Z threads per group).
- L56 _public member_ `TArray<FKernelPin> Inputs;` — `UPROPERTY(EditAnywhere, Category = "Kernel")` — Kernel inputs. Each entry maps a kernel HLSL parameter to a data interface read function.
- L59 _public member_ `TArray<FKernelPin> Outputs;` — `UPROPERTY(EditAnywhere, Category = "Kernel")` — Kernel outputs. Each entry maps a kernel HLSL parameter to a data interface write function.

#### struct `FComputeGraphDataBindingObjectDesc`  
`struct FComputeGraphDataBindingObjectDesc`  
_L64-74_
- reflection: `USTRUCT()`
- desc: Describes a binding object: a named ActorComponent class that data interfaces can reference.
- L70 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "BindingObject")` — Unique name identifying this binding object within the graph.
- L73 _public member_ `TObjectPtr<UClass> Type;` — `UPROPERTY(EditAnywhere, Category = "BindingObject", meta = (AllowedClasses = "/Script/Engine.ActorComponent"))` — The ActorComponent subclass that this binding object wraps.

#### struct `FComputeGraphDataInterfaceDesc`  
`struct FComputeGraphDataInterfaceDesc`  
_L78-94_
- reflection: `USTRUCT()`
- desc: Describes a data interface: a named UComputeDataInterface class optionally bound to a binding object.
- L84 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "DataInterface")` — Unique name identifying this data interface within the graph.
- L87 _public member_ `FName BindingObjectName;` — `UPROPERTY(EditAnywhere, Category = "DataInterface", meta = (DisplayName = "Binding Object"))` — Name of the FComputeGraphDataBindingObjectDesc that provides the component instance at runtime.
- L90 _public member_ `TObjectPtr<UClass> Type;` — `UPROPERTY(EditAnywhere, Category = "DataInterface", meta = (AllowedClasses = "/Script/ComputeFramework.ComputeDataInterface"))` — The ComputeDataInterface subclass that implements the read/write functions for this interface.
- L93 _public member_ `TObjectPtr<UComputeDataInterface> Settings;` — `UPROPERTY(VisibleAnywhere, Category = "DataInterface", Instanced, NoClear, meta = (ShowOnlyInnerProperties, EditCondition = "Type!=nullptr", EditConditionHides))` — Per-instance settings object. This is created automatically when Type is set.

#### struct `FComputeGraphDesc`  
`struct FComputeGraphDesc`  
_L98-111_
- reflection: `USTRUCT()`
- desc: Top-level description of an editable compute graph: its kernels, binding objects, and data interfaces.
- L104 _public member_ `TArray<FComputeGraphKernelDesc> Kernels;` — `UPROPERTY(EditAnywhere, Category = "Kernel")` — All compute kernels in the graph.
- L107 _public member_ `TArray<FComputeGraphDataBindingObjectDesc> BindingObjects;` — `UPROPERTY(EditAnywhere, Category = "BindingObject")` — All binding objects available for data interfaces to reference.
- L110 _public member_ `TArray<FComputeGraphDataInterfaceDesc> DataInterfaces;` — `UPROPERTY(EditAnywhere, Category = "DataInterface")` — All data interfaces that supply read/write functions to kernel pins.

#### class `UEditableComputeGraph`  
`class UEditableComputeGraph : public UComputeGraph`  
_L115-157_
- reflection: `UCLASS(MinimalAPI, meta = (Experimental))`
- inherits: `UComputeGraph`
- desc: Simple data driven compute graph implementation.
- L123 _protected member_ `FComputeGraphDesc GraphDescription;` — `UPROPERTY(EditAnywhere, Category = "Graph", meta = (EditInline))` — The graph description.
- L129 _public function_ `FComputeGraphDesc const& GetGraphDescription() const` — Returns the graph description (read-only and mutable overloads).
- L130 _public function_ `FComputeGraphDesc& GetGraphDescription()`
- L133 _public prototype_ `void RebuildGraph();` — Rebuild the compute graph topology and trigger shader compilation. Called by the asset editor Compile button.
- L136 _public member_ `FOnComputeGraphCompileOutput OnCompileOutputChanged;` — Fired on the game thread for each kernel that finishes compiling.
- L140 _protected prototype_ `void PostInitProperties() override;`
- L141 _protected prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L142 _protected prototype_ `void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L146 _protected prototype_ `void OnKernelCompilationComplete(int32 InKernelIndex, FComputeKernelCompileResults const& InCompileResults) override;`
- L151 _private prototype_ `void Rebuild();` — Translates GraphDescription into a UComputeGraph topology and submits kernels for compilation.
- L154 _private member_ `TArray<FName> KernelIndexToName;` — Maps compiled kernel index as seen by OnKernelCompilationComplete() to a kernel display name. Populated by Rebuild().

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API EDITABLECOMPUTEGRAPH_API`
- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnComputeGraphCompileOutput, TArray<FComputeKernelCompileMessage> const&);`
- L13 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnComputeGraphCompileOutput, TArray<FComputeKernelCompileMessage> const&);`
