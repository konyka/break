# Plugins / PCGNiagaraInterop

- module root: `Plugins/Experimental/PCGInterops/PCGNiagaraInterop/Source/PCGNiagaraInterop`
- headers: 3; symbols: 28
- symbol kinds: class=3, delegate=1, function=6, member=6, namespace=1, prototype=9, struct=1, typedef=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Niagara, PCG

### `Plugins/Experimental/PCGInterops/PCGNiagaraInterop/Source/PCGNiagaraInterop/Public/Elements/PCGWriteToNiagaraDataChannel.h` (Public)


#### class `UPCGWriteToNiagaraDataChannelSettings`  
`class UPCGWriteToNiagaraDataChannelSettings : public UPCGSettings`  
_L18-57_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSettings`
- desc: Allow writing attributes to a Niagara Data Channel.
- L25 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L26 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L27 _public function_ `virtual EPCGSettingsType GetType() const override`
- L31 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L32 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L33 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L38 _public member_ `TSoftObjectPtr<UNiagaraDataChannelAsset> DataChannel;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (PCG_Overridable))`
- L41 _public member_ `TMap<FName, FPCGAttributePropertyInputSelector> NiagaraVariablesPCGAttributeMapping;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")`
- L45 _public member_ `bool bVisibleToGame = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Visibility", meta = (PCG_Overridable))` — Data written to this data channel is visible to Blueprint and C++ logic reading from it
- L49 _public member_ `bool bVisibleToCPU = true;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Visibility", meta = (PCG_Overridable))` — Data written to this data channel is visible to Niagara CPU emitters
- L53 _public member_ `bool bVisibleToGPU = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Visibility", meta = (PCG_Overridable))` — Data written to this data channel is visible to Niagara GPU emitters
- L56 _public member_ `bool bSynchronousLoad = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings|Debug")`

#### struct `FPCGWriteToNiagaraDataChannelContext`  
`struct FPCGWriteToNiagaraDataChannelContext : public FPCGContext, public IPCGAsyncLoadingContext`  
_L59-59_
- inherits: `FPCGContext,IPCGAsyncLoadingContext`

#### class `FPCGWriteToNiagaraDataChannelElement`  
`class FPCGWriteToNiagaraDataChannelElement : public IPCGElementWithCustomContext<FPCGWriteToNiagaraDataChannelContext>`  
_L61-70_
- inherits: `IPCGElementWithCustomContext<FPCGWriteToNiagaraDataChannelContext>`
- L64 _public function_ `virtual bool IsCacheable(const UPCGSettings* InSettings) const override`
- L65 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`
- L67 _protected prototype_ `virtual bool PrepareDataInternal(FPCGContext* InContext) const override;`
- L68 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`
- L69 _protected function_ `virtual bool SupportsBasePointDataInputs(FPCGContext* InContext) const override`

### `Plugins/Experimental/PCGInterops/PCGNiagaraInterop/Source/PCGNiagaraInterop/Public/Helpers/PCGAttributeNiagaraTraits.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PCGAttributeNiagaraTraits`
- L12 _prototype_ `bool AreTypesCompatible(uint16 PCGType, const FNiagaraVariableBase& NiagaraVar, bool bPCGToNiagara);` (scope `PCGAttributeNiagaraTraits`)
- L15 _function_ `template <typename Func, typename ...Args> decltype(auto) CallbackWithNiagaraType(const FNiagaraVariableBase& NiagaraVar, Func Callback, Args&& ...InArgs)` (scope `PCGAttributeNiagaraTraits`)
- L17 _typedef_ `using ReturnType = decltype(Callback(double{}, std::forward<Args>(InArgs)...));` (scope `PCGAttributeNiagaraTraits::CallbackWithNiagaraType`)

### `Plugins/Experimental/PCGInterops/PCGNiagaraInterop/Source/PCGNiagaraInterop/Public/PCGNiagaraInteropModule.h` (Public)


#### class `FPCGNiagaraInteropModule`  
`class FPCGNiagaraInteropModule final : public IModuleInterface`  
_L10-16_
- inherits: `IModuleInterface`
- L14 _public function_ `virtual bool SupportsDynamicReloading() override`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGNiagaraInterop, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGNiagaraInterop, Log, All);`
