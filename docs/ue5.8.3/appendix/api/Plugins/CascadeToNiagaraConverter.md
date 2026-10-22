# Plugins / CascadeToNiagaraConverter

- module root: `Plugins/FX/CascadeToNiagaraConverter/Source/CascadeToNiagaraConverter`
- headers: 2; symbols: 345
- symbol kinds: class=7, delegate=2, enum=8, enumerator=44, function=42, member=64, prototype=165, struct=13
- PrivateDependencyModuleNames: MessageLog
- PublicDependencyModuleNames: AssetRegistry, Core, CoreUObject, Engine, Niagara, NiagaraCore, NiagaraEditor, PythonScriptPlugin, Slate, SlateCore
- PublicIncludePathModuleNames: Sequencer

### `Plugins/FX/CascadeToNiagaraConverter/Source/CascadeToNiagaraConverter/Public/CascadeToNiagaraConverterModule.h` (Public)


#### struct `FNiagaraConverterMessageTopics`  
`struct FNiagaraConverterMessageTopics`  
_L15-19_
- L17 _public member_ `static const FName VerboseConversionEventTopicName;`
- L18 _public member_ `static const FName ConversionEventTopicName;`

#### class `ICascadeToNiagaraConverterModule`  
`class ICascadeToNiagaraConverterModule : public IModuleInterface`  
_L21-33_
- inherits: `IModuleInterface`
- L26 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L27 _public prototype_ `virtual void ShutdownModule() override;`
- L30 _private prototype_ `static TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& SelectedAssets);`
- L31 _private prototype_ `static void AddMenuExtenderConvertEntry(FMenuBuilder& MenuBuilder, TArray<FAssetData> SelectedAssets);`
- L32 _private prototype_ `static void ExecuteConvertCascadeSystemToNiagaraSystem(TArray<UParticleSystem*> CascadeSystems);`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogFXConverter, Log, Verbose);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogFXConverter, Log, Verbose);`

### `Plugins/FX/CascadeToNiagaraConverter/Source/CascadeToNiagaraConverter/Public/NiagaraStackGraphUtilitiesAdapterLibrary.h` (Public)


#### enum `EScriptExecutionCategory`  
`enum class EScriptExecutionCategory : uint8`  
_L134-143_
- reflection: `UENUM()`
- L136 _public enumerator_ `EmitterSpawn = 0`
- L137 _public enumerator_ `EmitterUpdate`
- L138 _public enumerator_ `ParticleSpawn`
- L139 _public enumerator_ `ParticleUpdate`
- L140 _public enumerator_ `ParticleEvent UMETA(Hidden)`
- L142 _public enumerator_ `NONE`

#### enum `EDistributionType`  
`enum class EDistributionType : uint8`  
_L146-155_
- reflection: `UENUM()`
- L148 _public enumerator_ `Const = 0`
- L149 _public enumerator_ `ConstCurve`
- L150 _public enumerator_ `Uniform`
- L151 _public enumerator_ `UniformCurve`
- L152 _public enumerator_ `Parameter`
- L154 _public enumerator_ `NONE`

#### enum `EDistributionValueType`  
`enum class EDistributionValueType : uint8`  
_L158-164_
- reflection: `UENUM()`
- L160 _public enumerator_ `Float = 0`
- L161 _public enumerator_ `Vector`
- L163 _public enumerator_ `NONE`

#### enum `ECascadeRendererType`  
`enum class ECascadeRendererType : uint8`  
_L167-176_
- reflection: `UENUM()`
- L169 _public enumerator_ `Sprite = 0`
- L170 _public enumerator_ `Mesh`
- L171 _public enumerator_ `Ribbon`
- L172 _public enumerator_ `Beam`
- L173 _public enumerator_ `AnimTrail`
- L175 _public enumerator_ `NONE`

#### enum `ENiagaraScriptInputType`  
`enum class ENiagaraScriptInputType : uint8`  
_L179-196_
- reflection: `UENUM()`
- L181 _public enumerator_ `Int = 0`
- L182 _public enumerator_ `Float`
- L183 _public enumerator_ `Vec2`
- L184 _public enumerator_ `Vec3`
- L185 _public enumerator_ `Vec4`
- L186 _public enumerator_ `LinearColor`
- L187 _public enumerator_ `Matrix`
- L188 _public enumerator_ `Quaternion`
- L189 _public enumerator_ `Struct`
- L190 _public enumerator_ `Enum`
- L191 _public enumerator_ `DataInterface`
- L192 _public enumerator_ `Bool`
- L193 _public enumerator_ `Position`
- L195 _public enumerator_ `NONE`

#### enum `ERibbonConversionMode`  
`enum class ERibbonConversionMode : uint8`  
_L199-205_
- reflection: `UENUM()`
- L201 _public enumerator_ `Event = 0`
- L202 _public enumerator_ `DirectRead`
- L204 _public enumerator_ `NONE`

#### enum `EStackEntryAddActionMode`  
`enum class EStackEntryAddActionMode : uint8`  
_L208-214_
- reflection: `UENUM()`
- L210 _public enumerator_ `Module = 0`
- L211 _public enumerator_ `SetParameter`
- L213 _public enumerator_ `NONE`

#### enum `ENiagaraEventHandlerAddMode`  
`enum class ENiagaraEventHandlerAddMode : uint8`  
_L217-223_
- reflection: `UENUM()`
- L219 _public enumerator_ `AddEvent`
- L220 _public enumerator_ `AddEventAndEventGenerator`
- L222 _public enumerator_ `NONE`

#### struct `FEmitterDynamicParameterBP`  
`struct FEmitterDynamicParameterBP`  
_L232-287_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: BlueprintType wrapper around FEmitterDynamicParameter to allow managing in blueprint/python logic.
- L238 _public member_ `FName ParamName;` — `UPROPERTY(BlueprintReadWrite, Category = EmitterDynamicParameter)` — The parameter name - from the material DynamicParameter expression. READ-ONLY
- L242 _public member_ `bool bUseEmitterTime;` — `UPROPERTY(BlueprintReadWrite, Category = EmitterDynamicParameter)` — If true, use the EmitterTime to retrieve the value, otherwise use Particle RelativeTime.
- L246 _public member_ `bool bSpawnTimeOnly;` — `UPROPERTY(BlueprintReadWrite, Category = EmitterDynamicParameter)` — If true, only set the value at spawn time of the particle, otherwise update each frame.
- L250 _public member_ `TEnumAsByte<EEmitterDynamicParameterValue> ValueMethod;` — `UPROPERTY(BlueprintReadWrite, Category = EmitterDynamicParameter)` — Where to get the parameter value from.
- L254 _public member_ `bool bScaleVelocityByParamValue;` — `UPROPERTY(BlueprintReadWrite, Category = EmitterDynamicParameter)` — If true, scale the velocity value selected in ValueMethod by the evaluated ParamValue.
- L258 _public member_ `struct FRawDistributionFloat ParamValue;` — `UPROPERTY(EditAnywhere, Category = EmitterDynamicParameter)` — The distribution for the parameter value.
- L261 _public function_ `FEmitterDynamicParameterBP() : bUseEmitterTime(false) , bSpawnTimeOnly(false) , ValueMethod(0) , bScaleVelocityByParamValue(false)`
- L268 _public function_ `FEmitterDynamicParameterBP(FName InParamName, uint32 InUseEmitterTime, TEnumAsByte<EEmitterDynamicParameterValue> InValueMethod, UDistributionFloatConstant* InDistribution) : ParamName(InParamName) , bUseEmitterTime((bool)InUseEmitterTime) , bSpawnTimeOnly(false) , ValueMethod(InValueMethod) , bScaleVelocityByParamValue(false)`
- L278 _public function_ `FEmitterDynamicParameterBP(const FEmitterDynamicParameter& DynamicParameter) : ParamName(DynamicParameter.ParamName) , bUseEmitterTime(DynamicParameter.bUseEmitterTime) , bSpawnTimeOnly(DynamicParameter.bSpawnTimeOnly) , ValueMethod(DynamicParameter.ValueMethod) , bScaleVelocityByParamValue(DynamicParameter.bScaleVelocityByParamValue)`

#### struct `FOrbitOptionsBP`  
`struct FOrbitOptionsBP`  
_L291-326_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: BlueprintType wrapper around FOrbitOptions to allow managing in blueprint/python logic.
- L299 _public member_ `bool bProcessDuringSpawn;` — `UPROPERTY(EditAnywhere, Category=OrbitOptions)` — Whether to process the data during spawning.
- L305 _public member_ `bool bProcessDuringUpdate;` — `UPROPERTY(EditAnywhere, Category=OrbitOptions)` — Whether to process the data during updating.
- L311 _public member_ `bool bUseEmitterTime;` — `UPROPERTY(EditAnywhere, Category=OrbitOptions)` — Whether to use emitter time during data retrieval.
- L313 _public function_ `FOrbitOptionsBP() : bProcessDuringSpawn(true) , bProcessDuringUpdate(false) , bUseEmitterTime(false)`
- L320 _public function_ `FOrbitOptionsBP(const FOrbitOptions& OrbitOptions) : bProcessDuringSpawn(OrbitOptions.bProcessDuringSpawn) , bProcessDuringUpdate(OrbitOptions.bProcessDuringUpdate) , bUseEmitterTime(OrbitOptions.bUseEmitterTime)`

#### struct `FParticleBurstBlueprint`  
`struct FParticleBurstBlueprint`  
_L330-358_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- desc: BlueprintType wrapper around FParticleBurst to allow managing in blueprint/python logic.
- L334 _public function_ `FParticleBurstBlueprint()`
- L341 _public function_ `FParticleBurstBlueprint(const FParticleBurst& InParticleBurst) : Count(InParticleBurst.Count) , CountLow(InParticleBurst.CountLow) , Time(InParticleBurst.Time)`
- L349 _public member_ `int32 Count;` — `UPROPERTY(BlueprintReadWrite, Category = ParticleBurst)` — The number of particles to burst
- L353 _public member_ `int32 CountLow;` — `UPROPERTY(BlueprintReadWrite, Category = ParticleBurst)` — If >= 0, use as a range [CountLow..Count]
- L357 _public member_ `float Time;` — `UPROPERTY(BlueprintReadWrite, Category = ParticleBurst)` — The time at which to burst them (0..1: emitter lifetime)

#### struct `FRichCurveKeyBP`  
`struct FRichCurveKeyBP : public FRichCurveKey`  
_L361-374_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FRichCurveKey`
- L365 _public function_ `FRichCurveKeyBP() :FRichCurveKey()`
- L369 _public function_ `FRichCurveKeyBP(const FRichCurveKey& Other) :FRichCurveKey(Other)`
- L373 _public prototype_ `static TArray<FRichCurveKey> KeysToBase(const TArray<FRichCurveKeyBP>& InKeyBPs);`

#### struct `FLocationBoneSocketInfoBP`  
`struct FLocationBoneSocketInfoBP : public FLocationBoneSocketInfo`  
_L377-388_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- inherits: `FLocationBoneSocketInfo`
- L381 _public function_ `FLocationBoneSocketInfoBP() :FLocationBoneSocketInfo()`
- L385 _public function_ `FLocationBoneSocketInfoBP(const FLocationBoneSocketInfo& Other) :FLocationBoneSocketInfo(Other)`

#### struct `FNiagaraAddEventGeneratorOptions`  
`struct FNiagaraAddEventGeneratorOptions`  
_L391-404_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- L395 _public prototype_ `FNiagaraAddEventGeneratorOptions() = default;`
- L399 _public member_ `FName SourceEmitterName;` — `UPROPERTY(BlueprintReadWrite, Category = "Event Generator Options")` — The name to lookup the emitter which has the event generator.
- L403 _public member_ `FAssetData EventGeneratorScriptAssetData;` — `UPROPERTY(BlueprintReadWrite, Category = "Event Generator Options")` — AssetData pointing to the UNiagaraScript that generates the event.

#### struct `FNiagaraEventHandlerAddAction`  
`struct FNiagaraEventHandlerAddAction`  
_L407-460_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- L411 _public function_ `FNiagaraEventHandlerAddAction() : Mode(ENiagaraEventHandlerAddMode::AddEvent) , AddEventGeneratorOptions() , ExecutionMode(EScriptExecutionMode::EveryParticle) , SpawnNumber(0) , MaxEventsPerFrame(0) , SourceEmitterID() , SourceEventName() , bRandomSpawnNumber(false) , MinSpawnNumber(0)`
- L424 _public member_ `ENiagaraEventHandlerAddMode Mode;` — `UPROPERTY(BlueprintReadWrite, Category = "Event Handler Options")`
- L427 _public member_ `FNiagaraAddEventGeneratorOptions AddEventGeneratorOptions;` — `UPROPERTY(BlueprintReadWrite, Category = "Event Handler Options")`
- L432 _public member_ `EScriptExecutionMode ExecutionMode;` — `UPROPERTY(BlueprintReadWrite, Category = "Event Handler Options")` — Controls which particles have the event script run on them.
- L436 _public member_ `int32 SpawnNumber;` — `UPROPERTY(BlueprintReadWrite, Category = "Event Handler Options")` — Controls whether or not particles are spawned as a result of handling the event. Only valid for EScriptExecutionMode::SpawnedParticles. If Random Spawn Number is used, this will act as the maximum spawn range.
- L440 _public member_ `int32 MaxEventsPerFrame;` — `UPROPERTY(BlueprintReadWrite, Category = "Event Handler Options")` — Controls how many events are consumed by this event handler. If there are more events generated than this value, they will be ignored.
- L444 _public member_ `FGuid SourceEmitterID;` — `UPROPERTY()` — Id of the Emitter Handle that generated the event. If all zeroes, the event generator is assumed to be this emitter.
- L448 _public member_ `FName SourceEventName;` — `UPROPERTY(BlueprintReadWrite, Category = "Event Handler Options")` — The name of the event generated. This will be "Collision" for collision events and the Event Name field on the DataSetWrite node in the module graph for others.
- L452 _public member_ `bool bRandomSpawnNumber;` — `UPROPERTY(BlueprintReadWrite, Category = "Event Handler Options")` — Whether using a random spawn number.
- L456 _public member_ `int32 MinSpawnNumber;` — `UPROPERTY(BlueprintReadWrite, Category = "Event Handler Options")` — The minimum spawn number when random spawn is used. Spawn Number is used as the maximum range.
- L459 _public prototype_ `FNiagaraEventScriptProperties GetEventScriptProperties() const;`

#### struct `FStackEntryID`  
`struct FStackEntryID`  
_L463-489_
- reflection: `USTRUCT(BlueprintType)`
- L467 _public function_ `FStackEntryID() : ScriptExecutionCategory(EScriptExecutionCategory::EmitterSpawn) , EventName()`
- L472 _public function_ `FStackEntryID(EScriptExecutionCategory TargetExecutionCategory) : ScriptExecutionCategory(TargetExecutionCategory) , EventName()`
- L477 _public function_ `FStackEntryID(const FNiagaraEventHandlerAddAction& TargetEventHandlerStackEntry) : ScriptExecutionCategory(EScriptExecutionCategory::ParticleEvent) , EventName(TargetEventHandlerStackEntry.SourceEventName)`
- L484 _public member_ `EScriptExecutionCategory ScriptExecutionCategory;` — `UPROPERTY()` — The stack group to put a stack entry in.
- L488 _public member_ `FName EventName;` — `UPROPERTY()` — If the ScriptExecutionCategory is ParticleEvent, this FName is the key to find the desired event stack group.

#### struct `FStackEntryAddAction`  
`struct FStackEntryAddAction`  
_L492-530_
- reflection: `USTRUCT()`
- L496 _public prototype_ `FStackEntryAddAction() = default;`
- L498 _public function_ `FStackEntryAddAction(UNiagaraScriptConversionContext* InScriptConversionContext, const FStackEntryID& InStackEntryID, const FName& InModuleName) : Mode(EStackEntryAddActionMode::Module) , ScriptConversionContext(InScriptConversionContext) , StackEntryID(InStackEntryID) , ModuleName(InModuleName)`
- L505 _public function_ `FStackEntryAddAction(UNiagaraClipboardFunction* InParameterSetClipboardFunction, const FStackEntryID& InStackEntryID) : Mode(EStackEntryAddActionMode::SetParameter) , ClipboardFunction(InParameterSetClipboardFunction) , StackEntryID(InStackEntryID)`
- L513 _public member_ `EStackEntryAddActionMode Mode = EStackEntryAddActionMode::Module;` — `UPROPERTY()` — The mode of the AddStackEntryAction: when the action is applied to a UNiagaraEmitterConversionContext during Finalize(), the mode chooses what form of stack entry to add.
- L517 _public member_ `TObjectPtr<UNiagaraScriptConversionContext> ScriptConversionContext = nullptr;` — `UPROPERTY()` — If Mode is Module, represents the pending module script to create a stack entry for. Otherwise this value is ignored.
- L521 _public member_ `TObjectPtr<UNiagaraClipboardFunction> ClipboardFunction = nullptr;` — `UPROPERTY()` — If mode is SetParameter, represents the pending parameter to set directly and create a stack entry for. Otherwise this value is ignored.
- L525 _public member_ `FStackEntryID StackEntryID;` — `UPROPERTY()` — Info to find the category of the stack to add the stack entry to.
- L529 _public member_ `FName ModuleName;` — `UPROPERTY()` — If Mode is Module, acts as a key to lookup the ScriptConversionContext.

#### struct `FNiagaraScriptVersion`  
`struct FNiagaraScriptVersion`  
_L533-550_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- L538 _public prototype_ `FNiagaraScriptVersion() = default;`
- L540 _public function_ `FNiagaraScriptVersion(const int32 InMajorVersion, const int32 InMinorVersion) : MajorVersion(InMajorVersion) , MinorVersion(InMinorVersion)`
- L546 _public member_ `int32 MajorVersion = 0;` — `UPROPERTY(BlueprintReadOnly, Category = AssetData, transient)`
- L549 _public member_ `int32 MinorVersion = 0;` — `UPROPERTY(BlueprintReadOnly, Category = AssetData, transient)`

#### struct `FCreateScriptContextArgs`  
`struct FCreateScriptContextArgs`  
_L553-579_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- L558 _public prototype_ `FCreateScriptContextArgs() = default;`
- L560 _public function_ `FCreateScriptContextArgs(FAssetData InScriptAsset) : ScriptAsset(InScriptAsset) , ScriptVersion()`
- L565 _public function_ `FCreateScriptContextArgs(FAssetData InScriptAsset, FNiagaraScriptVersion InScriptVersion) : ScriptAsset(InScriptAsset) , bScriptVersionSet(true) , ScriptVersion(InScriptVersion)`
- L572 _public member_ `FAssetData ScriptAsset;` — `UPROPERTY(BlueprintReadOnly, Category = AssetData, transient)`
- L575 _public member_ `bool bScriptVersionSet = false;` — `UPROPERTY()`
- L578 _public member_ `FNiagaraScriptVersion ScriptVersion;` — `UPROPERTY(BlueprintReadOnly, Category = AssetData, transient)`

#### struct `FGenericConverterMessage`  
`struct FGenericConverterMessage`  
_L585-601_
- reflection: `USTRUCT(BlueprintInternalUseOnly)`
- L590 _public function_ `FGenericConverterMessage()`
- L592 _public function_ `FGenericConverterMessage(FString InMessage, ENiagaraMessageSeverity InMessageSeverity, bool bInIsVerbose) : Message(InMessage) , MessageSeverity(InMessageSeverity) , bIsVerbose(bInIsVerbose)`
- L598 _public member_ `FString Message;`
- L599 _public member_ `ENiagaraMessageSeverity MessageSeverity;`
- L600 _public member_ `bool bIsVerbose;`

#### class `UNiagaraSystemConversionContext`  
`class UNiagaraSystemConversionContext : public UObject`  
_L610-664_
- reflection: `UCLASS(BlueprintInternalUseOnly)`
- inherits: `UObject`
- desc: Wrapper for modifying a UNiagaraSystem by adding Emitters through UNiagaraEmitterConversionContexts.
- L615 _public function_ `UNiagaraSystemConversionContext()`
- L622 _public function_ `void Init(UNiagaraSystem* InSystem, const TSharedPtr<FNiagaraSystemViewModel>& InSystemViewModel)` — Init the System Conversion Context. @param InSystem				The System to convert. @param InSystemViewModel		The FNiagaraSystemViewModel pointing at the InSystem.
- L629 _public prototype_ `void Cleanup();` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L633 _public prototype_ `UNiagaraEmitterConversionContext* AddEmptyEmitter(FString NewEmitterNameString);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")` — Add an empty emitter to the system and return an emitter conversion context.
- L637 _public prototype_ `UNiagaraEmitterConversionContext* AddTemplateEmitter(FString NewEmitterNameString, FString Template);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")` — Add an emitter based on the specified template to the system and return an emitter conversion context.
- L640 _public prototype_ `void SetWarmupTime(float InWarmupTime);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L643 _public prototype_ `void SetWarmupTickDelta(float InWarmupTickDelta);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L652 _public prototype_ `void Finalize();` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")` — Apply all pending UNiagaraScriptConversionContexts and UNiagaraRendererProperties to the owned UNiagaraEmitterContexts by creating clipboard inputs and pasting them onto the emitter conversion context's Emitter. Afterwards compile the system so the changes take effect.
- L654 _public prototype_ `UNiagaraEmitterConversionContext* FindEmitterConversionContextByName(const FName& EmitterName);`
- L658 _private member_ `TObjectPtr<UNiagaraSystem> System;` — `UPROPERTY()`
- L660 _private member_ `TSharedPtr<FNiagaraSystemViewModel> SystemViewModel;`
- L663 _private member_ `TMap<FName, TObjectPtr<UNiagaraEmitterConversionContext>> EmitterNameToConversionContextMap;` — `UPROPERTY()`

#### class `UNiagaraEmitterConversionContext`  
`class UNiagaraEmitterConversionContext : public UObject`  
_L671-838_
- reflection: `UCLASS(BlueprintInternalUseOnly)`
- inherits: `UObject`
- desc: Wrapper for modifying a UNiagaraEmitter by adding Scripts and Renderers through UNiagaraScriptConversionContexts and UNiagaraRendererProperties, respectively.
- L675 _private prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPasteScript, int32, ScriptIdx);`
- L678 _public function_ `UNiagaraEmitterConversionContext() : bEnabled(false) , PastedFunctionCallNode(nullptr)`
- L684 _public prototype_ `void Cleanup();` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L691 _public prototype_ `UNiagaraScriptConversionContext* FindOrAddModuleScript( FString ScriptNameString , FCreateScriptContextArgs CreateScriptContextArgs , EScriptExecutionCategory ModuleScriptExecutionCategory );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")` — Find or add a script conversion context to this emitter conversion context. If a script conversion context is not found by name string then a new one is created and initialized from the NiagaraScriptAssetData.
- L702 _public prototype_ `UNiagaraScriptConversionContext* FindOrAddModuleEventScript( FString ScriptNameString , FCreateScriptContextArgs CreateScriptContextArgs , FNiagaraEventHandlerAddAction EventScriptProps );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")` — Find a module script conversion context or add a module script conversion context  to this emitter conversion context for an event category. If a script conversion context is not found by name string then a new one is created and initialized from the NiagaraScriptAssetData.
- L710 _public prototype_ `UNiagaraScriptConversionContext* FindModuleScript(FString ScriptNameString);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L713 _public prototype_ `void AddModuleScript( FString ScriptNameString , UNiagaraScriptConversionContext* ScriptConversionContext , EScriptExecutionCategory ModuleScriptExecutionCategory );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L720 _public prototype_ `void AddModuleEventScript( FString ScriptNameString , UNiagaraScriptConversionContext* ScriptConversionContext , FNiagaraEventHandlerAddAction EventScriptProps );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L730 _public prototype_ `void SetParameterDirectly( FString ParameterNameString , UNiagaraScriptConversionContextInput* ParameterInput , EScriptExecutionCategory SetParameterExecutionCategory );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")` — Add a set parameter module to the emitter handled by this emitter conversion context.
- L738 _public prototype_ `void AddRenderer(FString RendererNameString, UNiagaraRendererProperties* NewRendererProperties);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")` — Add a renderer to this emitter conversion context through renderer properties.
- L742 _public prototype_ `UNiagaraRendererProperties* FindRenderer(FString RendererNameString);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")` — Find an added renderer properties by name string.
- L745 _public prototype_ `TArray<UNiagaraRendererProperties*> GetAllRenderers();` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L754 _public prototype_ `void Log(FString Message, ENiagaraMessageSeverity Severity, bool bIsVerbose = false);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")` — Log a message to the niagara message log for the emitter. @param Message		The message string to display. @param Severity		The severity of the message. @param bIsVerbose	Whether the message is verbose and should be displayed conditionally.
- L762 _public prototype_ `void Finalize();` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")` — Apply all pending UNiagaraScriptConversionContexts and UNiagaraRendererProperties to this UNiagaraEmitterContext by creating clipboard inputs and pasting them onto the emitter conversion context's Emitter.
- L765 _public function_ `UNiagaraEmitter* GetEmitter()` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L768 _public function_ `void SetSimTarget(ENiagaraSimTarget InTarget)` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L771 _public function_ `void SetLocalSpace(bool bLocalSpace)` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L773 _public prototype_ `void InternalFinalizeEvents(UNiagaraSystemConversionContext* OwningSystemConversionContext);`
- L775 _public prototype_ `void InternalFinalizeStackEntryAddActions();`
- L782 _public function_ `void Init(FVersionedNiagaraEmitter InEmitter, const TSharedPtr<FNiagaraEmitterHandleViewModel>& InEmitterHandleViewModel)` — Init the Emitter Conversion Context. @param InEmitter						The Emitter to convert. @param InEmitterHandleViewModelGuid	A Guid key to the FNiagaraEmitterHandleViewModel pointing at the InEmitter.
- L789 _public prototype_ `FGuid GetEmitterHandleId() const;`
- L792 _public function_ `void SetEnabled(bool bInEnabled)` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L795 _public function_ `bool GetEnabled() const` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L798 _public prototype_ `void SetDetailBitMask(int32 BitMask);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L801 _public prototype_ `void AddEventHandler(FNiagaraEventHandlerAddAction EventScriptPropertiesBP);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L804 _public prototype_ `void SetRendererBinding(UNiagaraRendererProperties* InRendererProperties, FName BindingName, FName VariableToBindName, ENiagaraRendererSourceDataMode SourceDataMode);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L807 _public prototype_ `void RemoveModuleScriptsForAssets(TArray<FAssetData> ScriptsToRemove);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L811 _private member_ `FVersionedNiagaraEmitter Emitter;` — `UPROPERTY()`
- L813 _private member_ `TSharedPtr<FNiagaraEmitterHandleViewModel> EmitterHandleViewModel;`
- L815 _private member_ `TArray<FNiagaraEventHandlerAddAction> EventHandlerAddActions;`
- L818 _private member_ `TArray<FStackEntryAddAction> StackEntryAddActions;` — `UPROPERTY()`
- L821 _private member_ `TMap<FString, TObjectPtr<UNiagaraRendererProperties>> RendererNameToStagedRendererPropertiesMap;` — `UPROPERTY()`
- L823 _private member_ `TArray<FGenericConverterMessage> EmitterMessages;`
- L825 _private member_ `bool bEnabled;`
- L828 _private member_ `TObjectPtr<UNiagaraNodeFunctionCall> PastedFunctionCallNode;` — `UPROPERTY()`
- L831 _private function_ `void SetPastedFunctionCallNode(UNiagaraNodeFunctionCall* InFunctionCallNode)` — `UFUNCTION()`
- L833 _private prototype_ `UNiagaraScriptConversionContext* PrivateFindOrAddModuleScript( const FString& ScriptNameString , const FCreateScriptContextArgs& CreateScriptContextArgs , const FStackEntryID& StackEntryID );`

#### class `UNiagaraScriptConversionContext`  
`class UNiagaraScriptConversionContext : public UObject`  
_L842-910_
- reflection: `UCLASS(BlueprintInternalUseOnly)`
- inherits: `UObject`
- desc: Wrapper for programmatically adding scripts to a UNiagaraEmitter through a UNiagaraEmitterConversionContext.
- L847 _public function_ `UNiagaraScriptConversionContext() : TargetExecutionCategory(EScriptExecutionCategory::NONE) , FunctionInputs() , Script(nullptr) , ScriptVersionGuid() , StackMessages() , InputNameToTypeDefMap() , bModuleEnabled(true)`
- L858 _public prototype_ `void Init(const FAssetData& InNiagaraScriptAssetData, TOptional<FNiagaraScriptVersion> InNiagaraScriptVersion = TOptional<FNiagaraScriptVersion>());` — Init the Niagara Script Conversion Context with the assetdata to a UNiagaraScript.
- L867 _public prototype_ `bool SetParameter(FString ParameterName, UNiagaraScriptConversionContextInput* ParameterInput, bool bInHasEditCondition = false, bool bInEditConditionValue = false);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")` — Set a parameter on the Script this Script Conversion Context holds. @param ParameterName		The target parameter name. @param ParameterInput	Value to set on the parameter. @return Whether setting the parameter was successful.
- L876 _public prototype_ `void Log(FString Message, ENiagaraMessageSeverity Severity, bool bIsVerbose = false);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")` — Log a message to the stack and the niagara message log for the module associated with this script. @param Message		The message string to display. @param Severity		The severity of the message. @param bIsVerbose	Whether the message is verbose and should be displayed conditionally.
- L879 _public function_ `void SetModuleEnabled(bool bInModuleEnabled)` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L882 _public function_ `bool GetModuleEnabled() const` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L884 _public function_ `const TArray<const UNiagaraClipboardFunctionInput*>& GetClipboardFunctionInputs()`
- L886 _public function_ `UNiagaraScript* GetScript()`
- L888 _public function_ `const FGuid& GetScriptVersionGuid()`
- L890 _public function_ `const TArray<FGenericConverterMessage>& GetStackMessages() const`
- L894 _private member_ `EScriptExecutionCategory TargetExecutionCategory;` — Execution category to add this script to when it is finalized to a system or emitter.
- L897 _private member_ `TArray<TObjectPtr<const UNiagaraClipboardFunctionInput>> FunctionInputs;` — `UPROPERTY()`
- L900 _private member_ `TObjectPtr<UNiagaraScript> Script;` — `UPROPERTY()`
- L902 _private member_ `FGuid ScriptVersionGuid;`
- L904 _private member_ `TArray<FGenericConverterMessage> StackMessages;`
- L907 _private member_ `TMap<FString, FNiagaraTypeDefinition> InputNameToTypeDefMap;` — Map of input variable names to their type defs for verifying inputs.
- L909 _private member_ `bool bModuleEnabled;`

#### class `UNiagaraScriptConversionContextInput`  
`class UNiagaraScriptConversionContextInput : public UObject`  
_L914-936_
- reflection: `UCLASS(BlueprintInternalUseOnly)`
- inherits: `UObject`
- desc: Wrapper for setting the value on a parameter of a UNiagaraScript, applied through a UNiagaraScriptConversionContext.
- L919 _public function_ `UNiagaraScriptConversionContextInput() : InputType(ENiagaraScriptInputType::NONE)`
- L924 _public prototype_ `void Init(UNiagaraClipboardFunctionInput* InClipboardFunctionInput, const ENiagaraScriptInputType InInputType, const FNiagaraTypeDefinition& InTypeDefinition);` — `UFUNCTION()`
- L927 _public member_ `TObjectPtr<UNiagaraClipboardFunctionInput> ClipboardFunctionInput;` — `UPROPERTY()`
- L930 _public member_ `ENiagaraScriptInputType InputType;` — `UPROPERTY(BlueprintReadOnly, Category = StaticValue)`
- L933 _public member_ `FNiagaraTypeDefinition TypeDefinition;` — `UPROPERTY()`
- L935 _public member_ `TArray<FGenericConverterMessage> StackMessages;`

#### class `UFXConverterUtilitiesLibrary`  
`class UFXConverterUtilitiesLibrary : public UBlueprintFunctionLibrary`  
_L945-1676_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UBlueprintFunctionLibrary`
- desc: A C++ and Blueprint accessible library for converting fx type assets (Cascade and Niagara)
- L952 _public function_ `static FString GetLongPackagePath(const FString& InLongPackageName)` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")` — Generic Utilities
- L957 _public prototype_ `static TArray<UParticleEmitter*> GetCascadeSystemEmitters(const UParticleSystem* System);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")` — Cascade Emitter and ParticleLodLevel Getters
- L960 _public prototype_ `static float GetWarmupTime(const UParticleSystem* System);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L963 _public prototype_ `static UParticleLODLevel* GetCascadeEmitterLodLevel(UParticleEmitter* Emitter, const int32 Idx);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L966 _public prototype_ `static bool GetLodLevelIsEnabled(UParticleLODLevel* LodLevel);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L969 _public prototype_ `static TArray<UParticleModule*> GetLodLevelModules(UParticleLODLevel* LodLevel);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L972 _public prototype_ `static UParticleModuleSpawn* GetLodLevelSpawnModule(UParticleLODLevel* LodLevel);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L975 _public prototype_ `static UParticleModuleRequired* GetLodLevelRequiredModule(UParticleLODLevel* LodLevel);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L978 _public prototype_ `static UParticleModuleTypeDataBase* GetLodLevelTypeDataModule(UParticleLODLevel* LodLevel);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L981 _public prototype_ `static bool GetParticleModuleIsEnabled(UParticleModule* Module);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L984 _public prototype_ `static FName GetCascadeEmitterName(UParticleEmitter* Emitter);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L987 _public prototype_ `static int32 GetCascadeEmitterRenderMode(UParticleEmitter* Emitter);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L992 _public prototype_ `static UNiagaraScriptConversionContext* CreateScriptContext(const FCreateScriptContextArgs& Args);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")` — Niagara Script and Script Input Helpers
- L996 _public prototype_ `static FAssetData CreateAssetData(FString InPath);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L999 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputLinkedEnum(const FString& ParameterNameString, const FString& UserDefinedEnumAssetPath);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1002 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputLinkedParameter(FString ParameterNameString, ENiagaraScriptInputType InputType);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1005 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputLinkedParameterEx(FString ParameterNameString, UNiagaraScriptConversionContextInput* InBaseInput);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1008 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputFloat(float Value);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1011 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputLinearColor(FLinearColor Value);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1014 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputMatrix(FMatrix44f Value);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1017 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputQuat(FQuat4f Value);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1020 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputVec2(FVector2D Value);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1023 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputVec4(FVector4f Value);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1026 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputVector(FVector Value);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1029 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputStruct(UUserDefinedStruct* Value);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1032 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputEnum(const FString& UserDefinedEnumAssetPath, const FString& UserDefinedEnumValueNameString);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1035 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputInt(int32 Value);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1038 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputDynamic(UNiagaraScriptConversionContext* Value, ENiagaraScriptInputType InputType);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1041 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputDI(UNiagaraDataInterface* Value);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1044 _public prototype_ `static UNiagaraScriptConversionContextInput* CreateScriptInputBool(bool Value);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1047 _public prototype_ `static UNiagaraRibbonRendererProperties* CreateRibbonRendererProperties();` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1050 _public prototype_ `static UNiagaraMeshRendererProperties* CreateMeshRendererProperties();` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1053 _public prototype_ `static UNiagaraLightRendererProperties* CreateLightRendererProperties();` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1056 _public prototype_ `static UNiagaraComponentRendererProperties* CreateComponentRendererProperties();` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1061 _public prototype_ `static UNiagaraDataInterfaceSkeletalMesh* CreateSkeletalMeshDataInterface();` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")` — Niagara DI Helpers
- L1064 _public prototype_ `static UNiagaraDataInterfaceCurve* CreateFloatCurveDI(TArray<FRichCurveKeyBP> Keys);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1067 _public prototype_ `static UNiagaraDataInterfaceVector2DCurve* CreateVec2CurveDI(TArray<FRichCurveKeyBP> X_Keys, TArray<FRichCurveKeyBP> Y_Keys);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1070 _public prototype_ `static UNiagaraDataInterfaceVectorCurve* CreateVec3CurveDI( TArray<FRichCurveKeyBP> X_Keys, TArray<FRichCurveKeyBP> Y_Keys, TArray<FRichCurveKeyBP> Z_Keys );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1077 _public prototype_ `static UNiagaraDataInterfaceVector4Curve* CreateVec4CurveDI( TArray<FRichCurveKeyBP> X_Keys, TArray<FRichCurveKeyBP> Y_Keys, TArray<FRichCurveKeyBP> Z_Keys, TArray<FRichCurveKeyBP> W_Keys );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1087 _public prototype_ `static UNiagaraSystemConversionContext* CreateSystemConversionContext(UNiagaraSystem* InSystem);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")` — Niagara System and Emitter Helpers
- L1090 _public prototype_ `static void GetParticleModuleTypeDataGpuProps(UParticleModuleTypeDataGpu* ParticleModule);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1093 _public prototype_ `static void GetParticleModuleTypeDataBeam2Props(UParticleModuleTypeDataBeam2* ParticleModule);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1096 _public prototype_ `static void GetParticleModuleTypeDataMeshProps( UParticleModuleTypeDataMesh* ParticleModule , UStaticMesh*& OutMesh , float& OutLODSizeScale , bool& bOutUseStaticMeshLODs , bool& bOutCastShadows , bool& bOutDoCollisions , TEnumAsByte<EMeshScreenAlignment>& OutMeshAlignment , bool& bOutOverrideMaterial , bool& bOutOverrideDefaultMotionBlurSettings , bool& bOutEnableMotionBlur , UDistribution*& OutRollPitchYawRange , TEnumAsByte<EParticleAxisLock>& OutAxisLockOption , bool& bOutCameraFacing , TEnumAsByte<EMeshCameraFacingUpAxis>& OutCameraFacingUpAxisOption_DEPRECATED , TEnumAsByte<EMeshCameraFacingOptions>& OutCameraFacingOption , bool& bOutApplyParticleRotationAsSpin , bool& bOutFacingCameraDirectionRatherThanPosition , bool& bOutCollisionsConsiderParticleSize );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1118 _public prototype_ `static UClass* GetParticleModuleTypeDataRibbonClass();` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1121 _public prototype_ `static void GetParticleModuleTypeDataRibbonProps( UParticleModuleTypeDataRibbon* ParticleModule , int32& OutMaxTessellationBetweenParticles , int32& OutSheetsPerTrail , int32& OutMaxTrailCount , int32& OutMaxParticleInTrailCount , bool& bOutDeadTrailsOnDeactivate , bool& bOutClipSourceSegment , bool& bOutEnablePreviousTangentRecalculation , bool& bOutTangentRecalculationEveryFrame , bool& bOutSpawnInitialParticle , TEnumAsByte<ETrailsRenderAxisOption>& OutRenderAxis , float& OutTangentSpawningScalar , bool& bOutRenderGeometry , bool& bOutRenderSpawnPoints , bool& bOutRenderTangents , bool& bOutRenderTessellation , float& OutTilingDistance , float& OutDistanceTessellationStepSize , bool& bOutEnableTangentDiffInterpScale , float& OutTangentTessellationScalar );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1145 _public prototype_ `static void GetParticleModuleSpawnProps( UParticleModuleSpawn* ParticleModuleSpawn , UDistribution*& OutRate , UDistribution*& OutRateScale , TEnumAsByte<EParticleBurstMethod>& OutBurstMethod , TArray<FParticleBurstBlueprint>& OutBurstList , UDistribution*& OutBurstScale , bool& bOutApplyGlobalSpawnRateScale , bool& bOutProcessSpawnRate , bool& bOutProcessSpawnBurst );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1158 _public prototype_ `static void GetParticleModuleSpawnPerUnitProps( UParticleModuleSpawnPerUnit* ParticleModule , float& OutUnitScalar , float& OutMovementTolerance , UDistribution*& OutSpawnPerUnit , float& OutMaxFrameDistance , bool& bOutIgnoreSpawnRateWhenMoving , bool& bOutIgnoreMovementAlongX , bool& bOutIgnoreMovementAlongY , bool& bOutIgnoreMovementAlongZ , bool& bOutProcessSpawnRate , bool& bOutProcessBurstList );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1173 _public prototype_ `static void GetParticleModuleRequiredPerRendererProps( UParticleModuleRequired* ParticleModuleRequired , UMaterialInterface*& OutMaterialInterface , TEnumAsByte<EParticleScreenAlignment>& OutScreenAlignment , int32& OutSubImages_Horizontal , int32& OutSubImages_Vertical , TEnumAsByte<EParticleSortMode>& OutSortMode , TEnumAsByte<EParticleSubUVInterpMethod>& OutInterpolationMethod , uint8& bOutRemoveHMDRoll , float& OutMinFacingCameraBlendDistance , float& OutMaxFacingCameraBlendDistance , UTexture2D*& OutCutoutTexture , TEnumAsByte<ESubUVBoundingVertexCount>& OutBoundingMode , TEnumAsByte<EOpacitySourceMode>& OutOpacitySourceMode , TEnumAsByte< EEmitterNormalsMode>& OutEmitterNormalsMode , float& OutAlphaThreshold );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1192 _public prototype_ `static void GetParticleModuleRequiredPerModuleProps( UParticleModuleRequired* ParticleModuleRequired , bool& bOutOrbitModuleAffectsVelocityAlignment , float& OutRandomImageTime , int32& OutRandomImageChanges , bool& bOutOverrideSystemMacroUV , FVector& OutMacroUVPosition , float& OutMacroUVRadius );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1203 _public prototype_ `static void GetParticleModuleRequiredPerEmitterProps( UParticleModuleRequired* ParticleModuleRequired , FVector& OutEmitterOrigin , FRotator& OutEmitterRotation , bool& bOutUseLocalSpace , bool& bOutKillOnDeactivate , bool& bOutKillOnCompleted , bool& bOutUseLegacyEmitterTime , bool& bOutEmitterDurationUseRange , float& OutEmitterDuration , float& OutEmitterDurationLow , bool& bOUtEmitterDelayUseRange , bool& bOutDelayFirstLoopOnly , float& OutEmitterDelay , float& OutEmitterDelayLow , bool& bOutDurationRecalcEachLoop , int32& OutEmitterLoops );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1223 _public prototype_ `static void GetParticleModuleColorProps(UParticleModuleColor* ParticleModule, UDistribution*& OutStartColor, UDistribution*& OutStartAlpha, bool& bOutClampAlpha);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1226 _public prototype_ `static void GetParticleModuleColorOverLifeProps(UParticleModuleColorOverLife* ParticleModule, UDistribution*& OutColorOverLife, UDistribution*& OutAlphaOverLife, bool& bOutClampAlpha);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1229 _public prototype_ `static void GetParticleModuleLifetimeProps(UParticleModuleLifetime* ParticleModule, UDistribution*& OutLifetime);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1232 _public prototype_ `static void GetParticleModuleSizeProps(UParticleModuleSize* ParticleModule, UDistribution*& OutStartSize);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1235 _public prototype_ `static void GetParticleModuleVelocityProps(UParticleModuleVelocity* ParticleModule, UDistribution*& OutStartVelocity, UDistribution*& OutStartVelocityRadial, bool& bOutInWorldSpace, bool& bOutApplyOwnerScale);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1238 _public prototype_ `static void GetParticleModuleVelocityConeProps(UParticleModuleVelocityCone* ParticleModule, UDistribution*& OutAngleDistribution, UDistribution*& OutVelocityDistribution, FVector& OutDirection, bool& bOutWorldSpace, bool& bOutApplyOwnerScale);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1241 _public prototype_ `static void GetParticleModuleVelocityOverLifetimeProps( UParticleModuleVelocityOverLifetime* ParticleModule , UDistribution*& OutVelOverLife , bool& bOutAbsolute , bool& bOutInWorldSpace , bool& bOutApplyOwnerScale );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1250 _public prototype_ `static void GetParticleModuleConstantAccelerationProps(UParticleModuleAccelerationConstant* ParticleModule, FVector& OutConstAcceleration);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1253 _public prototype_ `static void GetParticleModuleLocationPrimitiveSphereProps( UParticleModuleLocationPrimitiveSphere* ParticleModule , UDistribution*& OutStartRadius , bool& bOutPositiveX , bool& bOutPositiveY , bool& bOutPositiveZ , bool& bOutNegativeX , bool& bOutNegativeY , bool& bOutNegativeZ , bool& bOutSurfaceOnly , bool& bOutVelocity , UDistribution*& OutVelocityScale , UDistribution*& OutStartLocation );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1269 _public prototype_ `static void GetParticleModuleLocationPrimitiveCylinderProps( UParticleModuleLocationPrimitiveCylinder* ParticleModule , bool& bOutRadialVelocity , UDistribution*& OutStartRadius , UDistribution*& OutStartHeight , TEnumAsByte<CylinderHeightAxis>& OutHeightAxis , bool& bOutPositiveX , bool& bOutPositiveY , bool& bOutPositiveZ , bool& bOutNegativeX , bool& bOutNegativeY , bool& bOutNegativeZ , bool& bOutSurfaceOnly , bool& bOutVelocity , UDistribution*& OutVelocityScale , UDistribution*& OutStartLocation );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1288 _public prototype_ `static void GetParticleModuleOrientationAxisLockProps(UParticleModuleOrientationAxisLock* ParticleModule, TEnumAsByte<EParticleAxisLock>& OutLockAxisFlags);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1291 _public prototype_ `static void GetParticleModuleVelocityInheritParentProps( UParticleModuleVelocityInheritParent* ParticleModule , UDistribution*& OutScale , bool& bOutInWorldSpace , bool& bOutApplyOwnerScale );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1299 _public prototype_ `static void GetParticleModuleMeshRotationProps(UParticleModuleMeshRotation* ParticleModule, UDistribution*& OutStartRotation, bool& bOutInheritParentRotation);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1302 _public prototype_ `static void GetParticleModuleCollisionProps( UParticleModuleCollision* ParticleModule , UDistribution*& OutDampingFactor , UDistribution*& OutDampingFactorRotation , UDistribution*& OutMaxCollisions , TEnumAsByte<EParticleCollisionComplete>& OutCollisionCompleteOption , TArray<TEnumAsByte<EObjectTypeQuery>>& OutCollisionTypes , bool& bOutApplyPhysics , bool& bOutIgnoreTriggerVolumes , UDistribution*& OutParticleMass , float& OutDirScalar , bool& bOutPawnsDoNotDecrementCount , bool& bOutOnlyVerticalNormalsDecrementCount , float& OutVerticalFudgeFactor , UDistribution*& OutDelayAmount , bool& bOutDropDetail , bool& bOutCollideOnlyIfVisible , bool& bOutIgnoreSourceActor , float& OutMaxCollisionDistance );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1324 _public prototype_ `static void GetParticleModuleSizeScaleProps(UParticleModuleSizeScale* ParticleModule, UDistribution*& OutSizeScale);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1327 _public prototype_ `static void GetParticleModuleSizeScaleBySpeedProps(UParticleModuleSizeScaleBySpeed* ParticleModule, FVector2D& OutSpeedScale, FVector2D& OutMaxScale);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1330 _public prototype_ `static void GetParticleModuleVectorFieldLocalProps( UParticleModuleVectorFieldLocal* ParticleModule , UVectorField* OutVectorField , FVector& OutRelativeTranslation , FRotator& OutRelativeRotation , FVector& OutRelativeScale3D , float& OutIntensity , float& OutTightness , bool& bOutIgnoreComponentTransform , bool& bOutTileX , bool& bOutTileY , bool& bOutTileZ , bool& bOutUseFixDT );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1346 _public prototype_ `static void GetParticleModuleVectorFieldRotationRateProps(UParticleModuleVectorFieldRotationRate* ParticleModule, FVector& OutRotationRate);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1349 _public prototype_ `static void GetParticleModuleOrbitProps( UParticleModuleOrbit* ParticleModule , TEnumAsByte<EOrbitChainMode>& OutChainMode , UDistribution*& OutOffsetAmount , FOrbitOptionsBP& OutOffsetOptions , UDistribution*& OutRotationAmount , FOrbitOptionsBP& OutRotationOptions , UDistribution*& OutRotationRateAmount , FOrbitOptionsBP& OutRotationRateOptions );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1361 _public prototype_ `static void GetParticleModuleSizeMultiplyLifeProps( UParticleModuleSizeMultiplyLife* ParticleModule , UDistribution*& OutLifeMultiplier , bool& OutMultiplyX , bool& OutMultiplyY , bool& OutMultiplyZ );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1370 _public prototype_ `static void GetParticleModuleColorScaleOverLifeProps( UParticleModuleColorScaleOverLife* ParticleModule , UDistribution*& OutColorScaleOverLife , UDistribution*& OutAlphaScaleOverLife , bool& bOutEmitterTime );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1378 _public prototype_ `static void GetParticleModuleRotationProps(UParticleModuleRotation* ParticleModule, UDistribution*& OutStartRotation);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1381 _public prototype_ `static void GetParticleModuleRotationRateProps(UParticleModuleRotationRate* ParticleModule, UDistribution*& OutStartRotationRate);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1384 _public prototype_ `static void GetParticleModuleRotationRateMultiplyLifeProps(UParticleModuleRotationRateMultiplyLife* ParticleModule, UDistribution*& OutLifeMultiplier);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1387 _public prototype_ `static void GetParticleModuleMeshRotationRateProps(UParticleModuleMeshRotationRate* ParticleModule, UDistribution*& OutStartRotationRate);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1390 _public prototype_ `static void GetParticleModuleRotationOverLifetimeProps(UParticleModuleRotationOverLifetime* ParticleModule, UDistribution*& OutRotationOverLife, bool& bOutScale);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1393 _public prototype_ `static void GetParticleModuleMeshRotationRateMultiplyLifeProps(UParticleModuleMeshRotationRateMultiplyLife* ParticleModule, UDistribution*& OutLifeMultiplier);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1396 _public prototype_ `static void GetParticleModuleMeshRotationRateOverLifeProps(UParticleModuleMeshRotationRateOverLife* ParticleModule, UDistribution*& OutRotRate, bool& bOutScaleRotRate);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1399 _public prototype_ `static void GetParticleModulePivotOffsetProps(UParticleModulePivotOffset* ParticleModule, FVector2D& OutPivotOffset);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1402 _public prototype_ `static void GetParticleModuleSubUVProps( UParticleModuleSubUV* ParticleModule , USubUVAnimation*& OutAnimation , UDistribution*& OutSubImageIndex , bool& bOutUseRealTime );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1410 _public prototype_ `static void GetParticleModuleCameraOffsetProps( UParticleModuleCameraOffset* ParticleModule , UDistribution*& OutCameraOffset , bool& bOutSpawnTimeOnly , TEnumAsByte<EParticleCameraOffsetUpdateMethod>& OutUpdateMethod );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1418 _public prototype_ `static void GetParticleModuleSubUVMovieProps( UParticleModuleSubUVMovie* ParticleModule , bool& bOutUseEmitterTime , UDistribution*& OutFrameRate , int32& OutStartingFrame );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1426 _public prototype_ `static void GetParticleModuleParameterDynamicProps(UParticleModuleParameterDynamic* ParticleModule, TArray<FEmitterDynamicParameterBP>& OutDynamicParams, bool& bOutUsesVelocity);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1429 _public prototype_ `static void GetParticleModuleAccelerationDragProps(UParticleModuleAccelerationDrag* ParticleModule, UDistribution*& OutDragCoefficientRaw);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1432 _public prototype_ `static void GetParticleModuleAccelerationDragScaleOverLifeProps(UParticleModuleAccelerationDragScaleOverLife* ParticleModule, UDistribution*& OutDragScaleRaw);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1435 _public prototype_ `static void GetParticleModuleAccelerationProps(UParticleModuleAcceleration* ParticleModule, UDistribution*& OutAcceleration, bool& bOutApplyOwnerScale);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1438 _public prototype_ `static void GetParticleModuleAccelerationOverLifetimeProps(UParticleModuleAccelerationOverLifetime* ParticleModule, UDistribution*& OutAccelOverLife);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1441 _public prototype_ `static void GetParticleModuleTrailSourceProps( UParticleModuleTrailSource* ParticleModule , TEnumAsByte<ETrail2SourceMethod>& OutSourceMethod , FName& OutSourceName , UDistribution*& OutSourceStrength , bool& bOutLockSourceStrength , int32& OutSourceOffsetCount , TArray<FVector>& OutSourceOffsetDefaults , TEnumAsByte<EParticleSourceSelectionMethod>& OutSelectionMethod , bool& bOutInheritRotation );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1454 _public prototype_ `static void GetParticleModuleAttractorParticleProps( UParticleModuleAttractorParticle* ParticleModule , FName& OutEmitterName, UDistribution*& OutRange , bool& bOutStrengthByDistance , UDistribution*& OutStrength , bool& bOutAffectBaseVelocity , TEnumAsByte<EAttractorParticleSelectionMethod>& OutSelectionMethod , bool& bOutRenewSource , bool& bOutInheritSourceVelocity );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1466 _public prototype_ `static void GetParticleModuleAttractorPointProps( UParticleModuleAttractorPoint* ParticleModule , UDistribution*& OutPosition , UDistribution*& OutRange , UDistribution*& OutStrength , bool& boutStrengthByDistance , bool& bOutAffectsBaseVelocity , bool& bOutOverrideVelocity , bool& bOutUseWorldSpacePosition , bool& bOutPositiveX , bool& bOutPositiveY , bool& bOutPositiveZ , bool& bOutNegativeX , bool& bOutNegativeY , bool& bOutNegativeZ );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1484 _public prototype_ `static void GetParticleModuleAttractorLineProps( UParticleModuleAttractorLine* ParticleModule , FVector& OutStartPoint , FVector& OutEndPoint , UDistribution*& OutRange , UDistribution*& OutStrength );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1493 _public prototype_ `static void GetParticleModuleLocationDirectProps( UParticleModuleLocationDirect* ParticleModule , UDistribution*& OutLocation , UDistribution*& OutLocationOffset , UDistribution*& OutScaleFactor );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1501 _public prototype_ `static void GetParticleModuleLocationProps( UParticleModuleLocation* ParticleModule , UDistribution*& OutStartLocation , float& OutDistributeOverNPoints , float& OutDistributeThreshold );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1509 _public prototype_ `static void GetParticleModuleLocationBoneSocketProps( UParticleModuleLocationBoneSocket* ParticleModule , TEnumAsByte<ELocationBoneSocketSource>& OutSourceType , FVector& OutUniversalOffset , TArray<FLocationBoneSocketInfoBP>& OutSourceLocations , TEnumAsByte<ELocationBoneSocketSelectionMethod>& OutSelectionMethod , bool& bOutUpdatePositionEachFrame , bool& bOutOrientMeshEmitters , bool& bOutInheritBoneVelocity , float& OutInheritVelocityScale , FName& OutSkelMeshActorParamName , int32& OutNumPreSelectedIndices , USkeletalMesh*& OutEditorSkelMesh );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1525 _public prototype_ `static void GetParticleModuleLocationWorldOffsetProps( UParticleModuleLocationWorldOffset* ParticleModule , UDistribution*& OutStartLocation , float& OutDistributeOverNPoints , float& OutDistributeThreshold );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1533 _public prototype_ `static void GetParticleModuleLocationSkelVertSurfaceProps( UParticleModuleLocationSkelVertSurface* ParticleModule , TEnumAsByte<ELocationSkelVertSurfaceSource>& OutSourceType , FVector& OutUniversalOffset , bool& bOutUpdatePositionEachFrame , bool& bOutOrientMeshEmitters , bool& bOutInheritBoneVelocity , float& OutInheritVelocityScale , FName& OutSkelMeshActorParamName , USkeletalMesh*& OutEditorSkelMesh , TArray<FName>& OutValidAssociatedBones , bool& bOutEnforceNormalCheck , FVector& OutNormalToCompare , float& OutNormalCheckToleranceDegrees , float& OutNormalCheckTolerance , TArray<int32>& OutValidMaterialIndices , bool& bOutInheritVertexColor , bool& bOutInheritUV , int32& OutInheritUVChannel );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1555 _public prototype_ `static void GetParticleModuleKillBoxProps( UParticleModuleKillBox* ParticleModule , UDistribution*& OutLowerLeftCorner , UDistribution*& OutUpperRightCorner , bool& bOutWorldSpaceCoords , bool& bOutKillInside , bool& bOutAxisAlignedAndFixedSize );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1565 _public prototype_ `static void GetParticleModuleLightProps( UParticleModuleLight* ParticleModule , bool& bOutUseInverseSquaredFalloff , bool& bOutAffectsTranslucency , bool& bOutPreviewLightRadius , float& OutSpawnFraction , UDistribution*& OutColorScaleOverLife , UDistribution*& OutBrightnessOverLife , UDistribution*& OutRadiusScale , UDistribution*& OutLightExponent , FLightingChannels& OutLightingChannels , float& OutVolumetricScatteringIntensity , bool& bOutHighQualityLights , bool& bOutShadowCastingLights );` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1582 _public prototype_ `static void GetParticleModuleMeshMaterialProps(UParticleModuleMeshMaterial* ParticleModule, TArray<UMaterialInterface*>& OutMeshMaterials);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1585 _public prototype_ `static void GetParticleModuleBeamSourceProps(UParticleModuleBeamSource* ParticleModule, UDistribution*& OutSource, bool& bOutSourceAbsolute);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1587 _public prototype_ `static void GetParticleModuleBeamTargetProps(UParticleModuleBeamTarget* ParticleModule, UDistribution*& OutTarget, bool& bOutTargetAbsolute);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1589 _public prototype_ `static void GetParticleModuleBeamNoiseProps(UParticleModuleBeamNoise* ParticleModule);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1592 _public prototype_ `static void SetMeshRendererMaterialOverridesFromCascade(UNiagaraMeshRendererProperties* MeshRendererProps, TArray<UMaterialInterface*> MeshMaterials);` — `UFUNCTION(BlueprintCallable, Category = "FXConverterUtilities")`
- L1596 _public prototype_ `static void GetDistributionMinMaxValues( UDistribution* Distribution, bool& bOutSuccess, FVector& OutMinValue, FVector& OutMaxValue );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")` — Cascade Distribution Getters
- L1604 _public prototype_ `static TArray<TEnumAsByte<EDistributionVectorLockFlags>> GetDistributionLockedAxes(UDistribution* Distribution);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1607 _public prototype_ `static void GetDistributionType( UDistribution* Distribution , EDistributionType& OutDistributionType , EDistributionValueType& OutCascadeDistributionValueType );` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1614 _public prototype_ `static void GetFloatDistributionConstValues(UDistributionFloatConstant* Distribution, float& OutConstFloat);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1617 _public prototype_ `static void GetVectorDistributionConstValues(UDistributionVectorConstant* Distribution, FVector& OutConstVector);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1620 _public prototype_ `static void GetFloatDistributionUniformValues(UDistributionFloatUniform* Distribution, float& OutMin, float& OutMax);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1623 _public prototype_ `static void GetVectorDistributionUniformValues(UDistributionVectorUniform* Distribution, FVector& OutMin, FVector& OutMax);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1626 _public prototype_ `static void GetFloatDistributionConstCurveValues(UDistributionFloatConstantCurve* Distribution, FInterpCurveFloat& OutInterpCurveFloat);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1629 _public prototype_ `static void GetVectorDistributionConstCurveValues(UDistributionVectorConstantCurve* Distribution, FInterpCurveVector& OutInterpCurveVector);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1632 _public prototype_ `static void GetFloatDistributionUniformCurveValues(UDistributionFloatUniformCurve* Distribution, FInterpCurveVector2D& OutInterpCurveVector2D);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1635 _public prototype_ `static void GetVectorDistributionUniformCurveValues(UDistributionVectorUniformCurve* Distribution, FInterpCurveTwoVectors& OutInterpCurveTwoVectors);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1638 _public prototype_ `static void GetFloatDistributionParameterValues(UDistributionFloatParameterBase* Distribution, FName& OutParameterName, float& OutMinInput, float& OutMaxInput, float& OutMinOutput, float& OutMaxOutput);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1641 _public prototype_ `static void GetVectorDistributionParameterValues(UDistributionVectorParameterBase* Distribution, FName& OutParameterName, FVector& OutMinInput, FVector& OutMaxInput, FVector& OutMinOutput, FVector& OutMaxOutput);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1646 _public prototype_ `static TArray<FRichCurveKeyBP> KeysFromInterpCurveFloat(FInterpCurveFloat Curve);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")` — Cascade curve helpers
- L1649 _public prototype_ `static TArray<FRichCurveKeyBP> KeysFromInterpCurveVector(FInterpCurveVector Curve, int32 ComponentIdx);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1652 _public prototype_ `static TArray<FRichCurveKeyBP> KeysFromInterpCurveVector2D(FInterpCurveVector2D Curve, int32 ComponentIdx);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1655 _public prototype_ `static TArray<FRichCurveKeyBP> KeysFromInterpCurveTwoVectors(FInterpCurveTwoVectors Curve, int32 ComponentIdx);` — `UFUNCTION(BlueprintCallable, meta = (ScriptMethod), Category = "FXConverterUtilities")`
- L1659 _public prototype_ `static FName GetNiagaraScriptInputTypeName(ENiagaraScriptInputType InputType);` — Code only utilities
- L1663 _private prototype_ `static void GetParticleModuleLocationPrimitiveBaseProps( UParticleModuleLocationPrimitiveBase* ParticleModule , bool& bOutPositiveX , bool& bOutPositiveY , bool& bOutPositiveZ , bool& bOutNegativeX , bool& bOutNegativeY , bool& bOutNegativeZ , bool& bOutSurfaceOnly , bool& bOutVelocity , UDistribution*& OutVelocityScale , UDistribution*& OutStartLocation );` — Internal cascade module getters

#### class `UConvertCascadeToNiagaraResults`  
`class UConvertCascadeToNiagaraResults : public UObject`  
_L1682-1698_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- desc: Wrapper class for passing results back from the ConvertCascadeToNiagara python script.
- L1688 _public function_ `void Init()` — `UFUNCTION()`
- L1693 _public member_ `bool bCancelledByUser;` — `UPROPERTY(BlueprintReadWrite, Category = "Results")` — Whether the converter process was cancelled by the user.
- L1697 _public member_ `bool bCancelledByPythonError;` — `UPROPERTY(BlueprintReadWrite, Category = "Results")` — Whether the converter process was cancelled due to an unrecoverable error in the python script process.

#### Free symbols / members of external scopes

- L675 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPasteScript, int32, ScriptIdx);`
