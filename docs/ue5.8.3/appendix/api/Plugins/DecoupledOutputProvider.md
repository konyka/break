# Plugins / DecoupledOutputProvider

- module root: `Plugins/VirtualProduction/VirtualCameraCore/Source/DecoupledOutputProvider`
- headers: 6; symbols: 105
- symbol kinds: class=6, delegate=2, enum=1, enumerator=2, function=20, member=11, namespace=10, prototype=51, struct=2
- PrivateDependencyModuleNames: Core, CoreUObject, Engine
- PublicDependencyModuleNames: VCamCore

### `Plugins/VirtualProduction/VirtualCameraCore/Source/DecoupledOutputProvider/Private/DecoupledOutputProviderModule.h` (Private)


#### class `UE::DecoupledOutputProvider::FDecoupledOutputProviderModule`  
`class FDecoupledOutputProviderModule : public IDecoupledOutputProviderModule`  
_L20-82_
- inherits: `IDecoupledOutputProviderModule`
- L25 _public function_ `static FDecoupledOutputProviderModule& Get()`
- L26 _public function_ `static bool IsAvailable()`
- L29 _public prototype_ `virtual void StartupModule() override;`
- L30 _public prototype_ `virtual void ShutdownModule() override;`
- L34 _public prototype_ `virtual void RegisterLogicFactory(TSubclassOf<UDecoupledOutputProvider> Class, FOutputProviderLogicFactoryDelegate FactoryDelegate) override;`
- L35 _public prototype_ `virtual void UnregisterLogicFactory(TSubclassOf<UDecoupledOutputProvider> Class) override;`
- L36 _public prototype_ `virtual void ForEachOutputProvidersWithLogicObject(TFunctionRef<EBreakBehavior(UDecoupledOutputProvider&)> Callback, TSubclassOf<UDecoupledOutputProvider> Class) const override;`
- L39 _public prototype_ `void OnInitialize(IOutputProviderEvent& Args);`
- L40 _public prototype_ `void OnDeinitialize(IOutputProviderEvent& Args);`
- L41 _public prototype_ `void OnTick(IOutputProviderEvent& Args, const float DeltaTime);`
- L42 _public prototype_ `void OnActivate(IOutputProviderEvent& Args);`
- L43 _public prototype_ `void OnDeactivate(IOutputProviderEvent& Args);`
- L44 _public prototype_ `TOptional<VCamCore::EViewportChangeReply> PreReapplyViewport(IOutputProviderEvent& Args);`
- L45 _public prototype_ `void PostReapplyViewport(IOutputProviderEvent& Args);`
- L46 _public prototype_ `void OnAddReferencedObjects(IOutputProviderEvent& Args, FReferenceCollector& Collector);`
- L47 _public prototype_ `void OnBeginDestroy(IOutputProviderEvent& Args);`
- L48 _public prototype_ `void OnSerialize(IOutputProviderEvent& Args, FArchive& Ar);`
- L49 _public prototype_ `void OnPostLoad(IOutputProviderEvent& Args);`
- L50 _public prototype_ `TFuture<FVCamStringPromptResponse> PromptClientForString(IOutputProviderEvent& Args, const FVCamStringPromptRequest& Request);`
- L52 _public prototype_ `void PreEditChange(IOutputProviderEvent& Args, FProperty* PropertyAboutToChange);`
- L53 _public prototype_ `void PreEditChange(IOutputProviderEvent& Args, FEditPropertyChain& PropertyAboutToChange);`
- L54 _public prototype_ `void OnPostEditChangeProperty(IOutputProviderEvent& Args, FPropertyChangedEvent& PropertyChangedEvent);`
- L66 _private member_ `TMap<UClass*, FOutputProviderClassMetaData> RegisteredFactories;` — Keeps track of registered factory functions
- L69 _private member_ `TMap<TWeakObjectPtr<UDecoupledOutputProvider>, TSharedRef<IOutputProviderLogic>> ActiveLogic;` — Maps output providers to their logic. There can be at most one logic object per output provider.
- L72 _private prototype_ `TSharedPtr<IOutputProviderLogic> GetOrCreateLogicFor(UDecoupledOutputProvider& OutputProviderBase);` — Creates a new logic object that will be associated with OutputProviderBase, or if one was previously associated, returns the preexisting one.
- L75 _private prototype_ `void ForEachRegisteredClassInClassHierarchy(UClass* Class, TFunctionRef<EBreakBehavior(UClass& Key, FOutputProviderClassMetaData&)> Callback);` — Data queries
- L76 _private prototype_ `void ForEachRegisteredClassInClassHierarchy(UClass* Class, TFunctionRef<EBreakBehavior(UClass& Key, const FOutputProviderClassMetaData&)> Callback) const;`
- L77 _private prototype_ `TPair<UClass*, FOutputProviderClassMetaData*> FindRegisteredFactoryInClassHierarchy(UClass* Class);`
- L78 _private prototype_ `TPair<UClass*, const FOutputProviderClassMetaData*> FindRegisteredFactoryInClassHierarchy(UClass* Class) const;`
- L81 _private prototype_ `void OnWorldCleanup(UWorld* World, bool bArg, bool bCond);` — Delegates

#### struct `UE::DecoupledOutputProvider::FDecoupledOutputProviderModule::FOutputProviderClassMetaData`  
`struct FOutputProviderClassMetaData`  
_L59-63_
- L62 _public member_ `FOutputProviderLogicFactoryDelegate Factory;` — Used to create new logic objects.

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DecoupledOutputProvider` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace DecoupledOutputProvider` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/DecoupledOutputProvider/Private/LogDecoupledOutputProvider.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDecoupledOutputProvider, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDecoupledOutputProvider, Log, All);`

### `Plugins/VirtualProduction/VirtualCameraCore/Source/DecoupledOutputProvider/Public/BuiltinProviders/VCamPixelStreamingSession.h` (Public)


#### class `UVCamPixelStreamingSession`  
`class UVCamPixelStreamingSession : public UDecoupledOutputProvider`  
_L9-47_
- reflection: `UCLASS(meta = (DisplayName = "Pixel Streaming Provider"))`
- inherits: `UDecoupledOutputProvider`
- L14 _public prototype_ `UVCamPixelStreamingSession();`
- L18 _public member_ `int32 FromComposureOutputProviderIndex_DEPRECATED = INDEX_NONE;` — `UE_DEPRECATED(5.7, "Using composure as an output provider is no longer supported. You can specify a final render target directly on the output provider.")` — `UPROPERTY()`
- L22 _public member_ `bool bMatchRemoteResolution = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output", meta = (DisplayPriority = "11"))` — If true the streamed UE viewport will match the resolution of the remote device.
- L26 _public member_ `bool EnableARKitTracking = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output", meta = (DisplayPriority = "12"))` — Check this if you wish to control the corresponding CineCamera with transform data received from the LiveLink app
- L30 _public member_ `bool PreventEditorIdle = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output", meta = (DisplayPriority = "13"))` — If not selected, when the editor is not the foreground application, input through the vcam session may seem sluggish or unresponsive.
- L34 _public member_ `bool bAutoSetLiveLinkSubject = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output", meta = (DisplayPriority = "14"))` — If true then the Live Link Subject of the owning VCam Component will be set to the subject created by this Output Provider when the Provider is enabled
- L38 _public member_ `bool bOverrideStreamerName = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output", meta = (DisplayPriority = "15"))` — Whether to override StreamerId with a user provided name.
- L46 _public member_ `FString StreamerId;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Output", meta = (EditCondition = "bOverrideStreamerName", DisplayPriority = "16"))` — The name of this streamer to be reported to the signalling server. Defaults to the actor label if unique, and uses the soft object path if not. If ids are not unique issues can occur.

### `Plugins/VirtualProduction/VirtualCameraCore/Source/DecoupledOutputProvider/Public/DecoupledOutputProvider.h` (Public)


#### class `UDecoupledOutputProvider`  
`class UDecoupledOutputProvider : public UVCamOutputProviderBase`  
_L21-48_
- reflection: `UCLASS(Abstract, NotBlueprintable)`
- inherits: `UVCamOutputProviderBase`
- desc: A decoupled output provider only contains data and forwards all important events to an IOutputProviderLogic, which may or may not exist. This allows the data to be loaded on all platforms but perform no operations on unsupported platforms. This decoupling is important to avoid failing LoadPackage warnings during cooking. Example: Pixel Streaming.
- L27 _public prototype_ `virtual void Initialize() override;`
- L28 _public prototype_ `virtual void Deinitialize() override;`
- L29 _public prototype_ `virtual void Tick(const float DeltaTime) override;`
- L30 _public prototype_ `virtual void OnActivate() override;`
- L31 _public prototype_ `virtual void OnDeactivate() override;`
- L32 _public prototype_ `virtual UE::VCamCore::EViewportChangeReply PreReapplyViewport() override;`
- L33 _public prototype_ `virtual void PostReapplyViewport() override;`
- L34 _public prototype_ `virtual TFuture<FVCamStringPromptResponse> PromptClientForString(const FVCamStringPromptRequest& Request) override;`
- L38 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L39 _public prototype_ `virtual void BeginDestroy() override;`
- L40 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L41 _public prototype_ `virtual void PostLoad() override;`
- L43 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L44 _public prototype_ `virtual void PreEditChange(FEditPropertyChain& PropertyAboutToChange) override;`
- L45 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DecoupledOutputProvider` (scope `UE`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/DecoupledOutputProvider/Public/IDecoupledOutputProviderModule.h` (Public)


#### struct `UE::DecoupledOutputProvider::FOutputProviderLogicCreationArgs`  
`struct FOutputProviderLogicCreationArgs`  
_L16-19_
- L18 _public member_ `UDecoupledOutputProvider* Provider;`

#### class `UE::DecoupledOutputProvider::IDecoupledOutputProviderModule`  
`class IDecoupledOutputProviderModule : public IModuleInterface`  
_L23-55_
- inherits: `IModuleInterface`
- desc: Provides an interface for managing decoupled output provider logic objects.
- L27 _public function_ `static IDecoupledOutputProviderModule& Get()`
- L34 _public prototype_ `virtual void RegisterLogicFactory(TSubclassOf<UDecoupledOutputProvider> Class, FOutputProviderLogicFactoryDelegate FactoryDelegate) = 0;` — Registers a factory delegate for Class and its subclasses. You can overwrite subclasses to use a different delegate. @param Class The base class for which to register the logic @param FactoryDelegate The delegate that will create the logic object
- L39 _public prototype_ `virtual void UnregisterLogicFactory(TSubclassOf<UDecoupledOutputProvider> Class) = 0;` — Unregisters a previously registered delegate. Existing logic objects will continue to exist; if you want them to be removed: BeginDestroy will implicitly destroy the associated logic object. @param Class You must supply the exact class previously passed to RegisterLogicFactory. This does not remove subclass overrides.
- L47 _public prototype_ `virtual void ForEachOutputProvidersWithLogicObject(TFunctionRef<EBreakBehavior(UDecoupledOutputProvider&)> Callback, TSubclassOf<UDecoupledOutputProvider> Class = UDecoupledOutputProvider::StaticClass()) const = 0;` — Iterates all output providers with the given class for which a logic object has been created. Note this includes subclass overrides as well.
- L49 _public function_ `TArray<UDecoupledOutputProvider*> GetOutputProvidersWithLogicObjects(TSubclassOf<UDecoupledOutputProvider> Class = UDecoupledOutputProvider::StaticClass()) const` — Gets all output providers for which a logic object has been created. Note this includes subclass overrides as well.

#### enum `UE::DecoupledOutputProvider::IDecoupledOutputProviderModule::EBreakBehavior`  
`enum class EBreakBehavior`  
_L41-45_
- L43 _public enumerator_ `Continue`
- L44 _public enumerator_ `Break`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace DecoupledOutputProvider` (scope `UE`)
- L20 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IOutputProviderLogic>, FOutputProviderLogicFactoryDelegate, const FOutputProviderLogicCreationArgs&);`
- L20 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IOutputProviderLogic>, FOutputProviderLogicFactoryDelegate, const FOutputProviderLogicCreationArgs&);` (scope `UE::DecoupledOutputProvider`)
- L52 _function_ `ForEachOutputProvidersWithLogicObject([&Result](UDecoupledOutputProvider& OutputProvider){ Result.Emplace(&OutputProvider); return EBreakBehavior::Continue; }, Class);` (scope `UE::DecoupledOutputProvider::IDecoupledOutputProviderModule::GetOutputProvidersWithLogicObjects`)

### `Plugins/VirtualProduction/VirtualCameraCore/Source/DecoupledOutputProvider/Public/IOutputProviderLogic.h` (Public)


#### class `UE::DecoupledOutputProvider::IOutputProviderEvent`  
`class IOutputProviderEvent`  
_L19-33_
- desc: Exposes certain data and manages the call to the super function.
- L27 _public prototype_ `virtual void ExecuteSuperFunction() = 0;` — Calls the super UVCamOutputProviderBase function version. If this is not called, the call to super takes place automatically after the IOutputProviderLogic function call.
- L30 _public prototype_ `virtual UDecoupledOutputProvider& GetOutputProvider() const = 0;` — Gets the associated output provider
- L32 _public prototype_ `virtual ~IOutputProviderEvent() = default;`

#### class `UE::DecoupledOutputProvider::IOutputProviderLogic`  
`class IOutputProviderLogic : public TSharedFromThis<IOutputProviderLogic>`  
_L44-75_
- inherits: `TSharedFromThis<IOutputProviderLogic>`
- desc: Receives events from an output provider's and implements its logic. This pattern decouples the output provider's data from its logic allowing the data to be loaded on all platforms but only have the logic be loaded on supported platforms. A logic's lifetime is bound to that of the output provider and is managed by the DecoupledOutputProvider's module. You can register a factory function with IDecoupledOutputProviderModule::RegisterLogicFactory.
- L49 _public function_ `virtual void OnInitialize(IOutputProviderEvent& Args)` — UVCamOutputProviderBase events
- L50 _public function_ `virtual void OnDeinitialize(IOutputProviderEvent& Args)`
- L51 _public function_ `virtual void OnActivate(IOutputProviderEvent& Args)`
- L52 _public function_ `virtual void OnDeactivate(IOutputProviderEvent& Args)`
- L53 _public function_ `virtual void OnTick(IOutputProviderEvent& Args, const float DeltaTime)`
- L54 _public function_ `virtual VCamCore::EViewportChangeReply PreReapplyViewport(IOutputProviderEvent& Args)`
- L55 _public function_ `virtual void PostReapplyViewport(IOutputProviderEvent& Args)`
- L56 _public function_ `virtual TFuture<FVCamStringPromptResponse> PromptClientForString(IOutputProviderEvent& Args, const FVCamStringPromptRequest& Request)`
- L62 _public function_ `virtual void OnAddReferencedObjects(IOutputProviderEvent& Args, FReferenceCollector& Collector)` — UObject events
- L63 _public function_ `virtual void OnBeginDestroy(IOutputProviderEvent& Args)`
- L64 _public function_ `virtual void OnSerialize(IOutputProviderEvent& Args, FArchive& Ar)`
- L65 _public function_ `virtual void OnPostLoad(IOutputProviderEvent& Args)`
- L68 _public function_ `virtual void OnPreEditChange(IOutputProviderEvent& Args, FProperty* PropertyAboutToChange)` — Called when root property is changed.
- L70 _public function_ `virtual void OnPreEditChange(IOutputProviderEvent& Args, FEditPropertyChain& PropertyAboutToChange)` — Called non-root property is changed.
- L71 _public function_ `virtual void OnPostEditChangeProperty(IOutputProviderEvent& Args, FPropertyChangedEvent& PropertyChangedEvent)`
- L74 _public prototype_ `virtual ~IOutputProviderLogic() = default;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace DecoupledOutputProvider` (scope `UE`)
