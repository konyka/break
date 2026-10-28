# Plugins / NiagaraMRQ

- module root: `Plugins/FX/NiagaraMRQ/Source/NiagaraMRQ`
- headers: 2; symbols: 20
- symbol kinds: class=2, function=2, prototype=16
- PrivateDependencyModuleNames: UnrealEd

### `Plugins/FX/NiagaraMRQ/Source/NiagaraMRQ/Private/NiagaraDataInterfaceMRQ.h` (Private)


#### class `UNiagaraDataInterfaceMRQ`  
`class UNiagaraDataInterfaceMRQ : public UNiagaraDataInterface`  
_L13-54_
- reflection: `UCLASS(EditInlineNew, Category = "MRQ", meta = (DisplayName = "MovieRenderQueue"))`
- inherits: `UNiagaraDataInterface`
- L25 _public prototype_ `UNiagaraDataInterfaceMRQ(FObjectInitializer const& ObjectInitializer = FObjectInitializer::Get());`
- L28 _public prototype_ `virtual void PostInitProperties() override;` — UObject Interface
- L32 _public prototype_ `virtual void GetVMExternalFunction(const FVMExternalFunctionBindingInfo& BindingInfo, void* InstanceData, FVMExternalFunction &OutFunc) override;` — UNiagaraDataInterface Interface
- L33 _public function_ `virtual bool CanExecuteOnTarget(ENiagaraSimTarget Target) const override`
- L35 _public prototype_ `virtual bool AppendCompileHash(FNiagaraCompileHashVisitor* InVisitor) const override;`
- L36 _public prototype_ `virtual bool GetFunctionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, const FNiagaraDataInterfaceGeneratedFunction& FunctionInfo, int FunctionInstanceIndex, FString& OutHLSL) override;`
- L37 _public prototype_ `virtual void GetParameterDefinitionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, FString& OutHLSL) override;`
- L39 _public prototype_ `virtual void BuildShaderParameters(FNiagaraShaderParametersBuilder& ShaderParametersBuilder) const override;`
- L40 _public prototype_ `virtual void SetShaderParameters(const FNiagaraDataInterfaceSetShaderParametersContext& Context) const override;`
- L42 _public prototype_ `virtual bool InitPerInstanceData(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance) override;`
- L43 _public prototype_ `virtual void DestroyPerInstanceData(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance) override;`
- L44 _public prototype_ `virtual int32 PerInstanceDataSize() const override;`
- L45 _public function_ `virtual bool HasPreSimulateTick() const override`
- L46 _public prototype_ `virtual bool PerInstanceTick(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance, float DeltaSeconds) override;`
- L47 _public prototype_ `virtual void ProvidePerInstanceDataForRenderThread(void* DataForRenderThread, void* PerInstanceData, const FNiagaraSystemInstanceID& SystemInstance) override;`
- L52 _protected prototype_ `virtual void GetFunctionsInternal(TArray<FNiagaraFunctionSignature>& OutFunctions) const override;`

### `Plugins/FX/NiagaraMRQ/Source/NiagaraMRQ/Private/NiagaraMRQModule.h` (Private)


#### class `FNiagaraMRQModule`  
`class FNiagaraMRQModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
