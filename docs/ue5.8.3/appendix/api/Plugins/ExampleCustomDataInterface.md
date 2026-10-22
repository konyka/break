# Plugins / ExampleCustomDataInterface

- module root: `Plugins/FX/ExampleCustomDataInterface/Source/ExampleCustomDataInterface`
- headers: 2; symbols: 21
- symbol kinds: class=2, function=2, member=1, prototype=16
- PrivateDependencyModuleNames: UnrealEd

### `Plugins/FX/ExampleCustomDataInterface/Source/ExampleCustomDataInterface/Private/NiagaraDataInterfaceMousePosition.h` (Private)


#### class `UNiagaraDataInterfaceMousePosition`  
`class UNiagaraDataInterfaceMousePosition : public UNiagaraDataInterface`  
_L13-54_
- reflection: `UCLASS(EditInlineNew, Category = "Mouse", meta = (DisplayName = "MousePosition Query"))`
- inherits: `UNiagaraDataInterface`
- L23 _public prototype_ `virtual void PostInitProperties() override;` — UObject Interface
- L27 _public prototype_ `virtual void GetVMExternalFunction(const FVMExternalFunctionBindingInfo& BindingInfo, void* InstanceData, FVMExternalFunction &OutFunc) override;` — UNiagaraDataInterface Interface
- L28 _public function_ `virtual bool CanExecuteOnTarget(ENiagaraSimTarget Target) const override`
- L30 _public prototype_ `virtual bool AppendCompileHash(FNiagaraCompileHashVisitor* InVisitor) const override;`
- L31 _public prototype_ `virtual bool GetFunctionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, const FNiagaraDataInterfaceGeneratedFunction& FunctionInfo, int FunctionInstanceIndex, FString& OutHLSL) override;`
- L32 _public prototype_ `virtual void GetParameterDefinitionHLSL(const FNiagaraDataInterfaceGPUParamInfo& ParamInfo, FString& OutHLSL) override;`
- L34 _public prototype_ `virtual void BuildShaderParameters(FNiagaraShaderParametersBuilder& ShaderParametersBuilder) const override;`
- L35 _public prototype_ `virtual void SetShaderParameters(const FNiagaraDataInterfaceSetShaderParametersContext& Context) const override;`
- L37 _public prototype_ `virtual bool InitPerInstanceData(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance) override;`
- L38 _public prototype_ `virtual void DestroyPerInstanceData(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance) override;`
- L39 _public prototype_ `virtual int32 PerInstanceDataSize() const override;`
- L40 _public function_ `virtual bool HasPreSimulateTick() const override`
- L41 _public prototype_ `virtual bool PerInstanceTick(void* PerInstanceData, FNiagaraSystemInstance* SystemInstance, float DeltaSeconds) override;`
- L42 _public prototype_ `virtual void ProvidePerInstanceDataForRenderThread(void* DataForRenderThread, void* PerInstanceData, const FNiagaraSystemInstanceID& SystemInstance) override;`
- L45 _public prototype_ `void GetMousePositionVM(FVectorVMExternalFunctionContext& Context);`
- L49 _protected prototype_ `virtual void GetFunctionsInternal(TArray<FNiagaraFunctionSignature>& OutFunctions) const override;`
- L53 _private member_ `static const FName GetMousePositionName;`

### `Plugins/FX/ExampleCustomDataInterface/Source/ExampleCustomDataInterface/Public/ExampleCustomDataInterface.h` (Public)


#### class `FExampleCustomDataInterfaceModule`  
`class FExampleCustomDataInterfaceModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
