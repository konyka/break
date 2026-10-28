# Plugins / MetasoundEngine

- module root: `Plugins/Runtime/Metasound/Source/MetasoundEngine`
- headers: 34; symbols: 1432
- symbol kinds: class=37, delegate=25, enum=8, enumerator=28, externvar=51, function=121, macro=19, member=255, namespace=87, prototype=735, struct=45, typedef=21
- PrivateDependencyModuleNames: AssetRegistry, AudioChannelAgnosticCore, AudioExtensions, AudioMixer, MetasoundGenerator, MetasoundGraphCore, Projects, SignalProcessing
- PrivateIncludePathModuleNames: AVEncoder
- PublicDependencyModuleNames: AudioPlatformConfiguration, Core, CoreUObject, DeveloperSettings, Engine, MetasoundFrontend, MetasoundStandardNodes, Serialization, WaveTable

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Private/Interfaces/MetasoundDeprecatedInterfaces.h` (Private)


#### class `Metasound::Engine::MetasoundOutputFormatMonoV1_1::FUpdateInterface`  
`class FUpdateInterface : public Frontend::IDocumentTransform`  
_L52-56_
- inherits: `Frontend::IDocumentTransform`
- L55 _public prototype_ `virtual bool Transform(Frontend::FDocumentHandle InDocument) const override;`

#### class `Metasound::Engine::MetasoundOutputFormatMonoV1_2::FUpdateInterface`  
`class FUpdateInterface : public Frontend::IDocumentTransform`  
_L66-70_
- inherits: `Frontend::IDocumentTransform`
- L69 _public prototype_ `virtual bool Transform(Frontend::FDocumentHandle InDocument) const override;`

#### class `Metasound::Engine::MetasoundOutputFormatStereoV1_1::FUpdateInterface`  
`class FUpdateInterface : public Frontend::IDocumentTransform`  
_L81-85_
- inherits: `Frontend::IDocumentTransform`
- L84 _public prototype_ `virtual bool Transform(Frontend::FDocumentHandle InDocument) const override;`

#### class `Metasound::Engine::MetasoundOutputFormatStereoV1_2::FUpdateInterface`  
`class FUpdateInterface : public Frontend::IDocumentTransform`  
_L95-99_
- inherits: `Frontend::IDocumentTransform`
- L98 _public prototype_ `virtual bool Transform(Frontend::FDocumentHandle InDocument) const override;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Metasound`
- L20 _namespace_ `namespace Engine` (scope `Metasound`)
- L23 _namespace_ `namespace MetasoundV1_0` (scope `Metasound::Engine`)
- L25 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::MetasoundV1_0`)
- L26 _prototype_ `FMetasoundFrontendInterface GetInterface();` (scope `Metasound::Engine::MetasoundV1_0`)
- L30 _namespace_ `namespace MetasoundOutputFormatMonoV1_0` (scope `Metasound::Engine`)
- L32 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::MetasoundOutputFormatMonoV1_0`)
- L33 _prototype_ `const FVertexName& GetAudioOutputName();` (scope `Metasound::Engine::MetasoundOutputFormatMonoV1_0`)
- L34 _prototype_ `FMetasoundFrontendInterface GetInterface();` (scope `Metasound::Engine::MetasoundOutputFormatMonoV1_0`)
- L38 _namespace_ `namespace MetasoundOutputFormatStereoV1_0` (scope `Metasound::Engine`)
- L40 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::MetasoundOutputFormatStereoV1_0`)
- L41 _prototype_ `const FVertexName& GetAudioOutputName();` (scope `Metasound::Engine::MetasoundOutputFormatStereoV1_0`)
- L42 _prototype_ `FMetasoundFrontendInterface GetInterface();` (scope `Metasound::Engine::MetasoundOutputFormatStereoV1_0`)
- L46 _namespace_ `namespace MetasoundOutputFormatMonoV1_1` (scope `Metasound::Engine`)
- L48 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::MetasoundOutputFormatMonoV1_1`)
- L49 _prototype_ `const FVertexName& GetAudioOutputName();` (scope `Metasound::Engine::MetasoundOutputFormatMonoV1_1`)
- L50 _prototype_ `FMetasoundFrontendInterface GetInterface();` (scope `Metasound::Engine::MetasoundOutputFormatMonoV1_1`)
- L61 _namespace_ `namespace MetasoundOutputFormatMonoV1_2` (scope `Metasound::Engine`)
- L63 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::MetasoundOutputFormatMonoV1_2`)
- L64 _prototype_ `FMetasoundFrontendInterface GetInterface();` (scope `Metasound::Engine::MetasoundOutputFormatMonoV1_2`)
- L74 _namespace_ `namespace MetasoundOutputFormatStereoV1_1` (scope `Metasound::Engine`)
- L76 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::MetasoundOutputFormatStereoV1_1`)
- L77 _prototype_ `const FVertexName& GetLeftAudioOutputName();` (scope `Metasound::Engine::MetasoundOutputFormatStereoV1_1`)
- L78 _prototype_ `const FVertexName& GetRightAudioOutputName();` (scope `Metasound::Engine::MetasoundOutputFormatStereoV1_1`)
- L79 _prototype_ `FMetasoundFrontendInterface GetInterface();` (scope `Metasound::Engine::MetasoundOutputFormatStereoV1_1`)
- L90 _namespace_ `namespace MetasoundOutputFormatStereoV1_2` (scope `Metasound::Engine`)
- L92 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::MetasoundOutputFormatStereoV1_2`)
- L93 _prototype_ `FMetasoundFrontendInterface GetInterface();` (scope `Metasound::Engine::MetasoundOutputFormatStereoV1_2`)
- L102 _prototype_ `void RegisterDeprecatedInterfaces();` (scope `Metasound::Engine`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Private/Interfaces/MetasoundInterface.h` (Private)


#### class `Metasound::Engine::FInterfaceRegistryEntry`  
`class FInterfaceRegistryEntry : public Frontend::IInterfaceRegistryEntry`  
_L14-36_
- inherits: `Frontend::IInterfaceRegistryEntry`
- desc: Entry for registered interface.
- L17 _public prototype_ `FInterfaceRegistryEntry(FMetasoundFrontendInterface&& InInterface, FName InRouterName = IDataReference::RouterName, bool bInIsDeprecated = false);`
- L18 _public prototype_ `FInterfaceRegistryEntry(const FMetasoundFrontendInterface& InInterface, FName InRouterName = IDataReference::RouterName, bool bInIsDeprecated = false);`
- L19 _public prototype_ `FInterfaceRegistryEntry(FMetasoundFrontendInterface InInterface, TUniquePtr<Frontend::IBuilderVersionTransform>&& InUpdateTransform, FName InRouterName, bool bInIsDeprecated = false);`
- L22 _public prototype_ `FInterfaceRegistryEntry(const FMetasoundFrontendInterface& InInterface, TUniquePtr<Frontend::IDocumentTransform>&& InUpdateTransform, FName InRouterName = IDataReference::RouterName, bool bInIsDeprecated = false);` — Ctor is here for back compat.  Future registry entries that provide update transforms should use overload providing builder version transform
- L24 _public prototype_ `virtual FName GetRouterName() const override;`
- L25 _public prototype_ `virtual const FMetasoundFrontendInterface& GetInterface() const override;`
- L26 _public prototype_ `virtual bool IsDeprecated() const override;`
- L27 _public prototype_ `virtual bool UpdateRootGraphInterface(Frontend::FDocumentHandle InDocument) const override;`
- L28 _public prototype_ `virtual bool UpdateRootGraphInterface(FMetaSoundFrontendDocumentBuilder& InDocumentBuilder) const override;`
- L29 _public prototype_ `virtual TSharedRef<Frontend::IBuilderVersionTransform> GetUpdateTransform() const override;`
- L32 _private member_ `FMetasoundFrontendInterface Interface;`
- L33 _private member_ `TSharedPtr<Frontend::IBuilderVersionTransform> UpdateTransform;`
- L34 _private member_ `FName RouterName;`
- L35 _private member_ `bool bIsDeprecated = false;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Metasound`
- L11 _namespace_ `namespace Engine` (scope `Metasound`)
- L38 _prototype_ `void RegisterInterfaces();` (scope `Metasound::Engine`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Private/Interfaces/MetasoundInterfaceBindingsPrivate.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace Metasound`
- L5 _namespace_ `namespace Engine` (scope `Metasound`)
- L7 _prototype_ `void RegisterInternalInterfaceBindings();` (scope `Metasound::Engine`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Private/MetasoundAudioBusPrivate.h` (Private)


#### class `Metasound::AudioBusPrivate::FResampledPatchOutput`  
`class FResampledPatchOutput`  
_L17-30_
- desc: Resample audio popped from an audio bus.
- L20 _public prototype_ `FResampledPatchOutput(int32 InNumChannels, float InAudioBusSampleRate, float InMetaSoundSampleRate, int32 InMetaSoundBlockSize, TSharedRef<Audio::FPatchOutput> InPatchOutput);`
- L22 _public prototype_ `int32 PopAudio(float* OutAudio, int32 InNumSamplesToPop, bool bInUseLatestAudio);`
- L26 _private member_ `int32 NumChannels = 0;`
- L27 _private member_ `Audio::FRuntimeResampler Resampler;`
- L28 _private member_ `Audio::FAlignedFloatBuffer ScratchBuffer;`
- L29 _private member_ `TSharedRef<Audio::FPatchOutput> PatchOutput;`

#### class `Metasound::AudioBusPrivate::FResampledPatchInput`  
`class FResampledPatchInput`  
_L33-46_
- desc: Resample audio pushed to an audio bus.
- L36 _public prototype_ `FResampledPatchInput(int32 InNumChannels, float InAudioBusSampleRate, float InMetaSoundSampleRate, int32 InMetaSoundBlockSize, Audio::FPatchInput InPatchInput);`
- L38 _public prototype_ `int32 PushAudio(float const* InAudio, int32 InNumSamplesToPush);`
- L42 _private member_ `int32 NumChannels = 0;`
- L43 _private member_ `Audio::FRuntimeResampler Resampler;`
- L44 _private member_ `Audio::FAlignedFloatBuffer ScratchBuffer;`
- L45 _private member_ `Audio::FPatchInput PatchInput;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Metasound`
- L10 _namespace_ `namespace AudioBusPrivate` (scope `Metasound`)
- L14 _externvar_ `extern int32 EnableResampledAudioBus;` (scope `Metasound::AudioBusPrivate`) — Enablement flag for resampling of audio when the MetaSound sample rate does not match the AudioMixer sample rate.

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Private/MetasoundBuilderPrivate.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Metasound`
- L10 _namespace_ `namespace Engine` (scope `Metasound`)
- L15 _function_ `template<typename ElementType> const ElementType* FindPreferredPage_ThreadSafe(const TArray<ElementType>& InElements)` (scope `Metasound::Engine`) — UMetaSoundSettings::GetPageOrder() is only available on GT. This ThreadSafe version is available for use in the builder when things are not on the GT.

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Private/MetasoundEngineAsset.h` (Private)


#### struct `Metasound::Engine::FAssetHelper`  
`struct FAssetHelper`  
_L45-405_
- desc: MetaSound Engine Asset helper provides routines for UObject based MetaSound assets. Any UObject deriving from FMetaSoundAssetBase should use these helper functions in their UObject overrides.
- L48 _public function_ `static void PreDuplicate(TScriptInterface<IMetaSoundDocumentInterface> MetaSound, FObjectDuplicationParameters& DupParams)`
- L53 _public function_ `static void PostDuplicate(TScriptInterface<IMetaSoundDocumentInterface> MetaSound, EDuplicateMode::Type InDuplicateMode)`
- L76 _public function_ `static void PostEditUndo(TScriptInterface<IMetaSoundDocumentInterface>& InDocInterface)`
- L101 _public function_ `template<typename TMetaSoundObject> static void SetReferencedAssets(TMetaSoundObject& InMetaSound, TSet<Frontend::IMetaSoundAssetManager::FAssetRef>&& InAssetRefs)`
- L123 _public function_ `static EDataValidationResult IsClassNameUnique(const FMetasoundFrontendDocument& Document, FDataValidationContext& InOutContext)`
- L155 _public function_ `static EDataValidationResult IsDataValid(const UObject& MetaSound, const FMetasoundFrontendDocument& Document, FDataValidationContext& InOutContext)`
- L221 _public function_ `static void GetAssetRegistryTags(TScriptInterface<const IMetaSoundDocumentInterface> DocInterface, FAssetRegistryTagsContext& Context)`
- L242 _public function_ `template <typename TMetaSoundObject> static FTopLevelAssetPath GetAssetPathChecked(TMetaSoundObject& InMetaSound)`
- L251 _public function_ `template <typename TMetaSoundObject> static TArray<FMetasoundAssetBase*> GetReferencedAssets(const TMetaSoundObject& InMetaSound)`
- L274 _public function_ `static void PreSaveAsset(FMetasoundAssetBase& InMetaSound, FObjectPreSaveContext InSaveContext)`
- L332 _public function_ `static void SerializeToArchive(FMetasoundAssetBase& InMetaSound, FArchive& InArchive)`
- L337 _public function_ `static void PostLoad(FMetasoundAssetBase& InMetaSound, TSet<FSoftObjectPath>& ReferenceAssetClassCache)`
- L377 _public function_ `template<typename TMetaSoundObject> static void OnAsyncReferencedAssetsLoaded(TMetaSoundObject& InMetaSound, const TArray<FMetasoundAssetBase*>& InAsyncReferences)`

#### Free symbols / members of external scopes

- L36 _macro_ `#define LOCTEXT_NAMESPACE "MetasoundEngine"`
- L39 _namespace_ `namespace Metasound`
- L39 _namespace_ `namespace Engine` (scope `Metasound`)
- L143 _function_ `Algo::Transform(AssetPaths, PathStrings, [](const FTopLevelAssetPath& Path) { return FText::FromString(Path.ToString()); });` (scope `Metasound::Engine::FAssetHelper::IsClassNameUnique`)
- L176 _function_ `` (scope `Metasound::Engine::FAssetHelper::IsDataValid`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Private/MetasoundEngineModule.h` (Private)


#### enum `Metasound::Engine::EAssetTagPrimeRequestStatus`  
`enum class EAssetTagPrimeRequestStatus : uint8`  
_L15-20_
- L17 _public enumerator_ `NotRequested = 0`
- L18 _public enumerator_ `Requested = 1`
- L19 _public enumerator_ `Complete = 2`

#### class `Metasound::Engine::FModule`  
`class FModule : public IMetasoundEngineModule`  
_L26-93_
- inherits: `IMetasoundEngineModule`
- L64 _public prototype_ `virtual void StartupModule() override;`
- L65 _public prototype_ `virtual void ShutdownModule() override;`
- L68 _public prototype_ `virtual void PrimeAssetManager() override;`
- L69 _public prototype_ `virtual FOnMetasoundGraphRegister& GetOnGraphRegisteredDelegate() override;`
- L70 _public prototype_ `virtual FOnMetasoundGraphUnregister& GetOnGraphUnregisteredDelegate() override;`
- L75 _private prototype_ `void AddClassRegistryAsset(const FAssetData& InAssetData);`
- L76 _private prototype_ `void UpdateClassRegistryAsset(const FAssetData& InAssetData);`
- L77 _private prototype_ `void RemoveAssetFromClassRegistry(const FAssetData& InAssetData);`
- L78 _private prototype_ `void RenameAssetInClassRegistry(const FAssetData& InAssetData, const FString& InOldObjectPath);`
- L79 _private prototype_ `void ShutdownAssetClassRegistry();`
- L81 _private prototype_ `void OnPackageReloaded(const EPackageReloadPhase InPackageReloadPhase, FPackageReloadedEvent* InPackageReloadedEvent);`
- L82 _private prototype_ `void OnAssetScanFinished();`
- L84 _private prototype_ `void PrimeAssetManagerInternal();`
- L87 _private member_ `FOnMetasoundGraphRegister OnGraphRegister;` — Asset registry delegates for calling MetaSound editor module
- L88 _private member_ `FOnMetasoundGraphUnregister OnGraphUnregister;`
- L91 _private member_ `EAssetTagPrimeRequestStatus AssetTagPrimeStatus = EAssetTagPrimeRequestStatus::NotRequested;` — Prime tag registry state

#### class `Metasound::Engine::FModule::FObjectReferencer`  
`class FObjectReferencer : public FMetasoundFrontendRegistryContainer::IObjectReferencer , public FGCObject`  
_L30-61_
- inherits: `FMetasoundFrontendRegistryContainer::IObjectReferencer,FGCObject`
- desc: Supplies GC referencing in the MetaSound Frontend node registry for doing async work on UObjets
- L35 _public function_ `virtual void AddObject(UObject* InObject) override`
- L41 _public function_ `virtual void RemoveObject(UObject* InObject) override`
- L47 _public function_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override`
- L53 _public function_ `virtual FString GetReferencerName() const override`
- L59 _private member_ `mutable FCriticalSection ObjectArrayCriticalSection;`
- L60 _private member_ `TArray<TObjectPtr<UObject>> ObjectArray;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Metasound`
- L13 _namespace_ `namespace Engine` (scope `Metasound`)
- L23 _prototype_ `bool GetEditorAssetValidationEnabled();` (scope `Metasound::Engine`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/Analysis/MetasoundVertexAnalyzerAudioBusWriter.h` (Public)


#### class `Metasound::Engine::FVertexAnalyzerAudioBusWriter`  
`class FVertexAnalyzerAudioBusWriter : public Frontend::FVertexAnalyzerBase`  
_L13-49_
- inherits: `Frontend::FVertexAnalyzerBase`
- L16 _public typedef_ `using FAnalyzerOutput = Frontend::FAnalyzerOutput;`
- L17 _public typedef_ `using FCreateAnalyzerParams = Frontend::FCreateAnalyzerParams;`
- L19 _public prototype_ `static const FName& GetAnalyzerName();`
- L20 _public prototype_ `static const FName& GetDataType();`
- L21 _public prototype_ `static FName GetAnalyzerMemberName(const Audio::FDeviceId InDeviceID, const uint32 InAudioBusID);`
- L33 _public prototype_ `FVertexAnalyzerAudioBusWriter(const FCreateAnalyzerParams& InParams);`
- L34 _public prototype_ `virtual ~FVertexAnalyzerAudioBusWriter() = default;`
- L36 _public prototype_ `virtual void Execute() override;`
- L48 _private member_ `Audio::FPatchInput AudioBusPatchInput;`

#### class `Metasound::Engine::FVertexAnalyzerAudioBusWriter::FFactory`  
`class FFactory : public Frontend::TVertexAnalyzerFactory<FVertexAnalyzerAudioBusWriter>`  
_L23-31_
- inherits: `Frontend::TVertexAnalyzerFactory<FVertexAnalyzerAudioBusWriter>`
- L26 _public function_ `virtual const TArray<FAnalyzerOutput>& GetAnalyzerOutputs() const override`

#### struct `Metasound::Engine::FVertexAnalyzerAudioBusWriter::FBusAddress`  
`struct FBusAddress`  
_L39-46_
- L41 _public member_ `Audio::FDeviceId DeviceID = 0;`
- L42 _public member_ `uint32 AudioBusID = 0;`
- L44 _public prototype_ `FString ToString() const;`
- L45 _public prototype_ `static FBusAddress FromString(const FString& InAnalyzerMemberName);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METASOUNDENGINE_API`
- L11 _namespace_ `namespace Metasound`
- L11 _namespace_ `namespace Engine` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/DocumentTemplates/MetasoundDocumentConfigurator.h` (Public)


#### struct `Metasound::Engine::FDocumentConfigurator`  
`struct FDocumentConfigurator`  
_L19-228_
- L36 _public prototype_ `UE_INTERNAL FDocumentConfigurator(UMetaSoundBuilderBase& InBuilder);` — Constructor exposed to enable testing configurator that wraps a transient builder. Not for use with runtime or editor behavior.
- L39 _public prototype_ `FDocumentConfigurator(const FArgs& Args);`
- L40 _public prototype_ `~FDocumentConfigurator();`
- L163 _public function_ `template <typename TemplateType> FDocumentConfigurator& Add(TArray<TemplateType> Args)`
- L174 _public function_ `template <> FDocumentConfigurator& Add<FInterface>(TArray<FInterface> Interfaces)`
- L206 _public function_ `template <typename TemplateType> FDocumentConfigurator& Set(TArray<TemplateType> Args)`
- L220 _private prototype_ `FDocumentConfigurator& AddInternal(TArray<FInterface> Interfaces);`
- L222 _private member_ `TStrongObjectPtr<UMetaSoundBuilderBase> Builder;`
- L223 _private member_ `mutable EMetaSoundBuilderResult Result = EMetaSoundBuilderResult::Succeeded;`
- L225 _private member_ `TMap<FName, FMetaSoundNodeHandle> NodeNameToHandle;`
- L227 _private member_ `FVector2D Offset;`

#### struct `Metasound::Engine::FDocumentConfigurator::FArgs`  
`struct FArgs`  
_L21-31_
- L23 _public member_ `FMetaSoundFrontendDocumentBuilder* Builder = nullptr;`
- L27 _public member_ `FVector2D Offset = FVector2D::Zero();` — Offset to use when positioning new nodes via the configuration
- L30 _public member_ `bool bResetDoc = true;`

#### struct `Metasound::Engine::FDocumentConfigurator::FInterface`  
`struct FInterface`  
_L48-51_
- L50 _public member_ `FMetasoundFrontendVersion Version;`

#### struct `Metasound::Engine::FDocumentConfigurator::FInput`  
`struct FInput`  
_L55-62_
- L57 _public member_ `FName Name = "Fl`
- L58 _public member_ `FName DataType = GetMetasoundDataTypeName<float>();`
- L59 _public member_ `FMetasoundFrontendLiteral DefaultValue = Frontend::MakeFrontendLiteral(0.f);`
- L60 _public member_ `FVector2D Location = FVector2D::Zero();`
- L61 _public member_ `bool bIsConstructorInput = false;`

#### struct `Metasound::Engine::FDocumentConfigurator::FInputNode`  
`struct FInputNode`  
_L67-72_
- L69 _public member_ `FName NodeName = "Fl`
- L70 _public member_ `FName InputName = "Fl`
- L71 _public member_ `FVector2D Location = FVector2D::Zero();`

#### struct `Metasound::Engine::FDocumentConfigurator::FOutput`  
`struct FOutput`  
_L77-84_
- L79 _public member_ `FName Name = "Fl`
- L80 _public member_ `FName DataType = GetMetasoundDataTypeName<float>();`
- L81 _public member_ `FMetasoundFrontendLiteral DefaultValue = Frontend::MakeFrontendLiteral(0.f);`
- L82 _public member_ `FVector2D Location = FVector2D::Zero();`
- L83 _public member_ `bool bIsConstructorOutput = false;`

#### struct `Metasound::Engine::FDocumentConfigurator::FVariable`  
`struct FVariable`  
_L88-93_
- L90 _public member_ `FName Name = "Fl`
- L91 _public member_ `FName DataType = GetMetasoundDataTypeName<float>();`
- L92 _public member_ `FMetasoundFrontendLiteral DefaultValue = Frontend::MakeFrontendLiteral(0.f);`

#### struct `Metasound::Engine::FDocumentConfigurator::FVariableSetNode`  
`struct FVariableSetNode`  
_L97-102_
- L99 _public member_ `FName Name;`
- L100 _public member_ `FName VariableName;`
- L101 _public member_ `FVector2D Location = FVector2D::Zero();`

#### struct `Metasound::Engine::FDocumentConfigurator::FVariableGetNode`  
`struct FVariableGetNode`  
_L106-111_
- L108 _public member_ `FName Name;`
- L109 _public member_ `FName VariableName;`
- L110 _public member_ `FVector2D Location = FVector2D::Zero();`

#### struct `Metasound::Engine::FDocumentConfigurator::FVariableGetDelayedNode`  
`struct FVariableGetDelayedNode`  
_L115-120_
- L117 _public member_ `FName Name;`
- L118 _public member_ `FName VariableName;`
- L119 _public member_ `FVector2D Location = FVector2D::Zero();`

#### struct `Metasound::Engine::FDocumentConfigurator::FNode`  
`struct FNode`  
_L124-130_
- L126 _public member_ `FName Name;`
- L127 _public member_ `FMetasoundFrontendClassName ClassName;`
- L128 _public member_ `FTopLevelAssetPath AssetPath;`
- L129 _public member_ `FVector2D Location = FVector2D::Zero();`

#### struct `Metasound::Engine::FDocumentConfigurator::FEdge`  
`struct FEdge`  
_L134-140_
- L136 _public member_ `FName OutputNode;`
- L137 _public member_ `FName Output;`
- L138 _public member_ `FName InputNode;`
- L139 _public member_ `FName Input;`

#### struct `Metasound::Engine::FDocumentConfigurator::FEdgeFromInput`  
`struct FEdgeFromInput`  
_L144-149_
- L146 _public member_ `FName GraphInput;`
- L147 _public member_ `FName Node;`
- L148 _public member_ `FName NodeInput;`

#### struct `Metasound::Engine::FDocumentConfigurator::FEdgeToOutput`  
`struct FEdgeToOutput`  
_L153-158_
- L155 _public member_ `FName Node;`
- L156 _public member_ `FName NodeOutput;`
- L157 _public member_ `FName GraphOutput;`

#### struct `Metasound::Engine::FDocumentConfigurator::FInputLocation`  
`struct FInputLocation`  
_L188-192_
- L190 _public member_ `FName Name;`
- L191 _public member_ `FVector2D Location = FVector2D::Zero();`

#### struct `Metasound::Engine::FDocumentConfigurator::FNodeInputDefault`  
`struct FNodeInputDefault`  
_L196-201_
- L198 _public member_ `FName Node;`
- L199 _public member_ `FName Input;`
- L200 _public member_ `FMetasoundFrontendLiteral Value;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METASOUNDENGINE_API`
- L17 _namespace_ `namespace Metasound`
- L17 _namespace_ `namespace Engine` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/DocumentTemplates/MetasoundRandomizerTemplate.h` (Public)


#### struct `FMetaSoundRandomizerTemplate`  
`struct FMetaSoundRandomizerTemplate : public FMetaSoundFrontendDocumentTemplate`  
_L19-53_
- reflection: `USTRUCT(BlueprintType, meta = (Hidden, DisplayName = "Randomizer"))`
- inherits: `FMetaSoundFrontendDocumentTemplate`
- L23 _public prototype_ `virtual ~FMetaSoundRandomizerTemplate() = default;`
- L26 _public prototype_ `UE_INTERNAL virtual bool ConfigureDocument(FMetaSoundFrontendDocumentBuilder& OutBuilder) override;`
- L41 _public prototype_ `static bool RemoveInvalidSounds(const FMetaSoundFrontendDocumentBuilder& ParentBuilder, bool bRemoveNullEntries, TArray<TObjectPtr<USoundWave>>& OutSounds);` — Helper function to remove sounds that cannot be referenced by randomizer (i.e. if the sounds are not exactly of type USoundWave or, optionally, if the underlying pointer is null). Returns true if sounds were removed, false if not.
- L46 _public member_ `bool bIsOneShot = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Category = "Randomizer Options"))`
- L49 _public member_ `TArray<TObjectPtr<USoundWave>> Sounds;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Category = "Randomizer Options", DisallowedClasses = "/Script/MetasoundEngine.MetaSoundSource, /Script/Engine.SoundSourceBus"))`
- L52 _public member_ `FVector2f Pitch = { -3.f, 3.f };` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Category = "Randomizer Options", ClampMin = "-36.0", ClampMax = "36.0", UIMin = "-12.0", UIMax = "12.0"))`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDENGINE_API`

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/IMetasoundEngineModule.h` (Public)


#### enum `Metasound::Engine::EAssetScanStatus`  
`enum class EAssetScanStatus : uint8`  
_L13-18_
- desc: AssetScanStatus is no longer necessary and will be deprecated once usage is removed from MetaSound plugin API
- L15 _public enumerator_ `NotRequested = 0`
- L16 _public enumerator_ `InProgress = 2`
- L17 _public enumerator_ `Complete = 3`

#### enum `Metasound::Engine::ENodeClassRegistryPrimeStatus`  
`enum class ENodeClassRegistryPrimeStatus : uint8`  
_L21-28_
- desc: NodeClassRegistryPrimeStatus is no longer necessary and will be deprecated once usage is removed from MetaSound plugin API
- L23 _public enumerator_ `NotRequested = 0`
- L24 _public enumerator_ `Requested = 1`
- L25 _public enumerator_ `InProgress = 2`
- L26 _public enumerator_ `Complete = 3`
- L27 _public enumerator_ `Canceled = 4`

#### enum `Metasound::Engine::ERegistrationAssetContext`  
`enum class ERegistrationAssetContext`  
_L30-36_
- L32 _public enumerator_ `None` — No special asset context associated with this graph registration action
- L33 _public enumerator_ `Removing` — Graph registration during asset removal
- L34 _public enumerator_ `Renaming` — Graph registration during asset rename
- L35 _public enumerator_ `Reloading` — Graph registration during asset reload

#### class `Metasound::Engine::IMetasoundEngineModule`  
`class IMetasoundEngineModule : public IModuleInterface`  
_L42-56_
- inherits: `IModuleInterface`
- L45 _public prototype_ `virtual void StartupModule() override = 0;`
- L46 _public prototype_ `virtual void ShutdownModule() override = 0;`
- L50 _public prototype_ `virtual void PrimeAssetManager() = 0;` — Request enumeration of scanned assets and kick off add of MetaSound asset tag data to MetaSoundAssetManager
- L53 _public prototype_ `virtual FOnMetasoundGraphRegister& GetOnGraphRegisteredDelegate() = 0;` — Asset registry delegates for calling MetaSound editor module register/unregister with frontend
- L54 _public prototype_ `virtual FOnMetasoundGraphUnregister& GetOnGraphUnregisteredDelegate() = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Metasound`
- L9 _namespace_ `namespace Engine` (scope `Metasound`)
- L38 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMetasoundGraphRegister, UObject&, ERegistrationAssetContext) DECLARE_DELEGATE_TwoParams(FOnMetasoundGraphUnregister, UObject&, ERegistrationAssetContext) #endif`
- L39 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMetasoundGraphUnregister, UObject&, ERegistrationAssetContext) #endif`

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/Interfaces/MetasoundInputFormatInterfaces.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Metasound`
- L9 _namespace_ `namespace Engine` (scope `Metasound`)
- L11 _namespace_ `namespace InputFormatMonoInterface` (scope `Metasound::Engine`)
- L13 _namespace_ `namespace Inputs` (scope `Metasound::Engine::InputFormatMonoInterface`)
- L15 _externvar_ `const extern FName MonoIn;` (scope `Metasound::Engine::InputFormatMonoInterface::Inputs`)
- L18 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::InputFormatMonoInterface`)
- L19 _prototype_ `Audio::FParameterInterfacePtr CreateInterface();` (scope `Metasound::Engine::InputFormatMonoInterface`)
- L20 _prototype_ `TArray<FMetasoundFrontendInterfaceBinding> CreateBindings();` (scope `Metasound::Engine::InputFormatMonoInterface`)
- L23 _namespace_ `namespace InputFormatStereoInterface` (scope `Metasound::Engine`)
- L25 _namespace_ `namespace Inputs` (scope `Metasound::Engine::InputFormatStereoInterface`)
- L27 _externvar_ `const extern FName LeftIn;` (scope `Metasound::Engine::InputFormatStereoInterface::Inputs`)
- L28 _externvar_ `const extern FName RightIn;` (scope `Metasound::Engine::InputFormatStereoInterface::Inputs`)
- L31 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::InputFormatStereoInterface`)
- L32 _prototype_ `Audio::FParameterInterfacePtr CreateInterface();` (scope `Metasound::Engine::InputFormatStereoInterface`)
- L33 _prototype_ `TArray<FMetasoundFrontendInterfaceBinding> CreateBindings();` (scope `Metasound::Engine::InputFormatStereoInterface`)
- L36 _namespace_ `namespace InputFormatQuadInterface` (scope `Metasound::Engine`)
- L38 _namespace_ `namespace Inputs` (scope `Metasound::Engine::InputFormatQuadInterface`)
- L40 _externvar_ `const extern FName FrontLeftIn;` (scope `Metasound::Engine::InputFormatQuadInterface::Inputs`)
- L41 _externvar_ `const extern FName FrontRightIn;` (scope `Metasound::Engine::InputFormatQuadInterface::Inputs`)
- L42 _externvar_ `const extern FName SideLeftIn;` (scope `Metasound::Engine::InputFormatQuadInterface::Inputs`)
- L43 _externvar_ `const extern FName SideRightIn;` (scope `Metasound::Engine::InputFormatQuadInterface::Inputs`)
- L46 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::InputFormatQuadInterface`)
- L47 _prototype_ `Audio::FParameterInterfacePtr CreateInterface();` (scope `Metasound::Engine::InputFormatQuadInterface`)
- L48 _prototype_ `TArray<FMetasoundFrontendInterfaceBinding> CreateBindings();` (scope `Metasound::Engine::InputFormatQuadInterface`)
- L51 _namespace_ `namespace InputFormatFiveDotOneInterface` (scope `Metasound::Engine`)
- L53 _namespace_ `namespace Inputs` (scope `Metasound::Engine::InputFormatFiveDotOneInterface`)
- L55 _externvar_ `const extern FName FrontLeftIn;` (scope `Metasound::Engine::InputFormatFiveDotOneInterface::Inputs`)
- L56 _externvar_ `const extern FName FrontRightIn;` (scope `Metasound::Engine::InputFormatFiveDotOneInterface::Inputs`)
- L57 _externvar_ `const extern FName FrontCenterIn;` (scope `Metasound::Engine::InputFormatFiveDotOneInterface::Inputs`)
- L58 _externvar_ `const extern FName LowFrequencyIn;` (scope `Metasound::Engine::InputFormatFiveDotOneInterface::Inputs`)
- L59 _externvar_ `const extern FName SideLeftIn;` (scope `Metasound::Engine::InputFormatFiveDotOneInterface::Inputs`)
- L60 _externvar_ `const extern FName SideRightIn;` (scope `Metasound::Engine::InputFormatFiveDotOneInterface::Inputs`)
- L63 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::InputFormatFiveDotOneInterface`)
- L64 _prototype_ `Audio::FParameterInterfacePtr CreateInterface();` (scope `Metasound::Engine::InputFormatFiveDotOneInterface`)
- L65 _prototype_ `TArray<FMetasoundFrontendInterfaceBinding> CreateBindings();` (scope `Metasound::Engine::InputFormatFiveDotOneInterface`)
- L68 _namespace_ `namespace InputFormatSevenDotOneInterface` (scope `Metasound::Engine`)
- L70 _namespace_ `namespace Inputs` (scope `Metasound::Engine::InputFormatSevenDotOneInterface`)
- L72 _externvar_ `const extern FName FrontLeftIn;` (scope `Metasound::Engine::InputFormatSevenDotOneInterface::Inputs`)
- L73 _externvar_ `const extern FName FrontRightIn;` (scope `Metasound::Engine::InputFormatSevenDotOneInterface::Inputs`)
- L74 _externvar_ `const extern FName FrontCenterIn;` (scope `Metasound::Engine::InputFormatSevenDotOneInterface::Inputs`)
- L75 _externvar_ `const extern FName LowFrequencyIn;` (scope `Metasound::Engine::InputFormatSevenDotOneInterface::Inputs`)
- L76 _externvar_ `const extern FName SideLeftIn;` (scope `Metasound::Engine::InputFormatSevenDotOneInterface::Inputs`)
- L77 _externvar_ `const extern FName SideRightIn;` (scope `Metasound::Engine::InputFormatSevenDotOneInterface::Inputs`)
- L78 _externvar_ `const extern FName BackLeftOut;` (scope `Metasound::Engine::InputFormatSevenDotOneInterface::Inputs`)
- L79 _externvar_ `const extern FName BackRightOut;` (scope `Metasound::Engine::InputFormatSevenDotOneInterface::Inputs`)
- L82 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::InputFormatSevenDotOneInterface`)
- L83 _prototype_ `Audio::FParameterInterfacePtr CreateInterface();` (scope `Metasound::Engine::InputFormatSevenDotOneInterface`)
- L84 _prototype_ `TArray<FMetasoundFrontendInterfaceBinding> CreateBindings();` (scope `Metasound::Engine::InputFormatSevenDotOneInterface`)
- L87 _namespace_ `namespace InputFormatChannelAgnosticInterface` (scope `Metasound::Engine`)
- L89 _namespace_ `namespace Inputs` (scope `Metasound::Engine::InputFormatChannelAgnosticInterface`)
- L91 _externvar_ `const extern FName CatIn;` (scope `Metasound::Engine::InputFormatChannelAgnosticInterface::Inputs`)
- L94 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::InputFormatChannelAgnosticInterface`)
- L95 _prototype_ `Audio::FParameterInterfacePtr CreateInterface();` (scope `Metasound::Engine::InputFormatChannelAgnosticInterface`)
- L96 _prototype_ `TArray<FMetasoundFrontendInterfaceBinding> CreateBindings();` (scope `Metasound::Engine::InputFormatChannelAgnosticInterface`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/Interfaces/MetasoundInterfaceBindings.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Metasound`
- L7 _namespace_ `namespace Engine` (scope `Metasound`)
- L9 _prototype_ `void RegisterInterfaceBindings(const TArray<FMetasoundFrontendInterfaceBinding>& InBindings);` (scope `Metasound::Engine`)
- L10 _prototype_ `bool UnregisterInterfaceBinding(const FMetasoundFrontendVersion& InInputInterfaceVersion, const FMetasoundFrontendVersion& InOutputInterfaceVersion);` (scope `Metasound::Engine`)
- L11 _prototype_ `bool UnregisterAllInterfaceBindings(const FMetasoundFrontendVersion& InInputInterfaceVersion);` (scope `Metasound::Engine`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/Interfaces/MetasoundOutputFormatInterfaces.h` (Public)


#### enum `EMetaSoundOutputAudioFormat`  
`enum class EMetaSoundOutputAudioFormat : uint8`  
_L16-25_
- reflection: `UENUM()`
- desc: Declares supported MetaSound output audio formats
- L18 _public enumerator_ `Mono`
- L19 _public enumerator_ `Stereo`
- L20 _public enumerator_ `Quad`
- L21 _public enumerator_ `FiveDotOne UMETA(DisplayName = "5.1")`
- L22 _public enumerator_ `SevenDotOne UMETA(DisplayName = "7.1")`
- L23 _public enumerator_ `ChannelAgnostic UMETA(DisplayName = "Channel Agnostic (Experimental)", Hidden)`
- L24 _public enumerator_ `COUNT UMETA(Hidden)`

#### struct `Metasound::Engine::FOutputAudioFormatInfo`  
`struct FOutputAudioFormatInfo`  
_L126-130_
- desc: Contains information on output audio formats
- L128 _public member_ `FMetasoundFrontendVersion InterfaceVersion;`
- L129 _public member_ `TArray<Metasound::FVertexName> OutputVertexChannelOrder;`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace Metasound`
- L27 _namespace_ `namespace Engine` (scope `Metasound`)
- L29 _namespace_ `namespace OutputFormatMonoInterface` (scope `Metasound::Engine`)
- L31 _namespace_ `namespace Outputs` (scope `Metasound::Engine::OutputFormatMonoInterface`)
- L33 _externvar_ `const extern FName MonoOut;` (scope `Metasound::Engine::OutputFormatMonoInterface::Outputs`)
- L36 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::OutputFormatMonoInterface`)
- L39 _prototype_ `Audio::FParameterInterfacePtr CreateInterface(const UClass& InClass);` (scope `Metasound::Engine::OutputFormatMonoInterface`) — `UE_DEPRECATED(5.3, "Interfaces are no longer registered with the UClass as interfaces can support multiple UClasses")`
- L40 _prototype_ `Audio::FParameterInterfacePtr CreateInterface();` (scope `Metasound::Engine::OutputFormatMonoInterface`)
- L43 _namespace_ `namespace OutputFormatStereoInterface` (scope `Metasound::Engine`)
- L45 _namespace_ `namespace Outputs` (scope `Metasound::Engine::OutputFormatStereoInterface`)
- L47 _externvar_ `const extern FName LeftOut;` (scope `Metasound::Engine::OutputFormatStereoInterface::Outputs`)
- L48 _externvar_ `const extern FName RightOut;` (scope `Metasound::Engine::OutputFormatStereoInterface::Outputs`)
- L51 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::OutputFormatStereoInterface`)
- L54 _prototype_ `Audio::FParameterInterfacePtr CreateInterface(const UClass& InClass);` (scope `Metasound::Engine::OutputFormatStereoInterface`) — `UE_DEPRECATED(5.3, "Interfaces are no longer registered with the UClass as interfaces can support multiple UClasses")`
- L55 _prototype_ `Audio::FParameterInterfacePtr CreateInterface();` (scope `Metasound::Engine::OutputFormatStereoInterface`)
- L58 _namespace_ `namespace OutputFormatQuadInterface` (scope `Metasound::Engine`)
- L60 _namespace_ `namespace Outputs` (scope `Metasound::Engine::OutputFormatQuadInterface`)
- L62 _externvar_ `const extern FName FrontLeftOut;` (scope `Metasound::Engine::OutputFormatQuadInterface::Outputs`)
- L63 _externvar_ `const extern FName FrontRightOut;` (scope `Metasound::Engine::OutputFormatQuadInterface::Outputs`)
- L64 _externvar_ `const extern FName SideLeftOut;` (scope `Metasound::Engine::OutputFormatQuadInterface::Outputs`)
- L65 _externvar_ `const extern FName SideRightOut;` (scope `Metasound::Engine::OutputFormatQuadInterface::Outputs`)
- L68 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::OutputFormatQuadInterface`)
- L71 _prototype_ `Audio::FParameterInterfacePtr CreateInterface(const UClass& InClass);` (scope `Metasound::Engine::OutputFormatQuadInterface`) — `UE_DEPRECATED(5.3, "Interfaces are no longer registered with the UClass as interfaces can support multiple UClasses")`
- L72 _prototype_ `Audio::FParameterInterfacePtr CreateInterface();` (scope `Metasound::Engine::OutputFormatQuadInterface`)
- L75 _namespace_ `namespace OutputFormatFiveDotOneInterface` (scope `Metasound::Engine`)
- L77 _namespace_ `namespace Outputs` (scope `Metasound::Engine::OutputFormatFiveDotOneInterface`)
- L79 _externvar_ `const extern FName FrontLeftOut;` (scope `Metasound::Engine::OutputFormatFiveDotOneInterface::Outputs`)
- L80 _externvar_ `const extern FName FrontRightOut;` (scope `Metasound::Engine::OutputFormatFiveDotOneInterface::Outputs`)
- L81 _externvar_ `const extern FName FrontCenterOut;` (scope `Metasound::Engine::OutputFormatFiveDotOneInterface::Outputs`)
- L82 _externvar_ `const extern FName LowFrequencyOut;` (scope `Metasound::Engine::OutputFormatFiveDotOneInterface::Outputs`)
- L83 _externvar_ `const extern FName SideLeftOut;` (scope `Metasound::Engine::OutputFormatFiveDotOneInterface::Outputs`)
- L84 _externvar_ `const extern FName SideRightOut;` (scope `Metasound::Engine::OutputFormatFiveDotOneInterface::Outputs`)
- L87 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::OutputFormatFiveDotOneInterface`)
- L90 _prototype_ `Audio::FParameterInterfacePtr CreateInterface(const UClass& InClass);` (scope `Metasound::Engine::OutputFormatFiveDotOneInterface`) — `UE_DEPRECATED(5.3, "Interfaces are no longer registered with the UClass as interfaces can support multiple UClasses")`
- L91 _prototype_ `Audio::FParameterInterfacePtr CreateInterface();` (scope `Metasound::Engine::OutputFormatFiveDotOneInterface`)
- L94 _namespace_ `namespace OutputFormatSevenDotOneInterface` (scope `Metasound::Engine`)
- L96 _namespace_ `namespace Outputs` (scope `Metasound::Engine::OutputFormatSevenDotOneInterface`)
- L98 _externvar_ `const extern FName FrontLeftOut;` (scope `Metasound::Engine::OutputFormatSevenDotOneInterface::Outputs`)
- L99 _externvar_ `const extern FName FrontRightOut;` (scope `Metasound::Engine::OutputFormatSevenDotOneInterface::Outputs`)
- L100 _externvar_ `const extern FName FrontCenterOut;` (scope `Metasound::Engine::OutputFormatSevenDotOneInterface::Outputs`)
- L101 _externvar_ `const extern FName LowFrequencyOut;` (scope `Metasound::Engine::OutputFormatSevenDotOneInterface::Outputs`)
- L102 _externvar_ `const extern FName SideLeftOut;` (scope `Metasound::Engine::OutputFormatSevenDotOneInterface::Outputs`)
- L103 _externvar_ `const extern FName SideRightOut;` (scope `Metasound::Engine::OutputFormatSevenDotOneInterface::Outputs`)
- L104 _externvar_ `const extern FName BackLeftOut;` (scope `Metasound::Engine::OutputFormatSevenDotOneInterface::Outputs`)
- L105 _externvar_ `const extern FName BackRightOut;` (scope `Metasound::Engine::OutputFormatSevenDotOneInterface::Outputs`)
- L108 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::OutputFormatSevenDotOneInterface`)
- L111 _prototype_ `Audio::FParameterInterfacePtr CreateInterface(const UClass& InClass);` (scope `Metasound::Engine::OutputFormatSevenDotOneInterface`) — `UE_DEPRECATED(5.3, "Interfaces are no longer registered with the UClass as interfaces can support multiple UClasses")`
- L112 _prototype_ `Audio::FParameterInterfacePtr CreateInterface();` (scope `Metasound::Engine::OutputFormatSevenDotOneInterface`)
- L115 _namespace_ `namespace OutputFormatChannelAgnosticInterface` (scope `Metasound::Engine`)
- L117 _namespace_ `namespace Outputs` (scope `Metasound::Engine::OutputFormatChannelAgnosticInterface`)
- L119 _externvar_ `const extern FName CatOut;` (scope `Metasound::Engine::OutputFormatChannelAgnosticInterface::Outputs`)
- L122 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Engine::OutputFormatChannelAgnosticInterface`)
- L123 _prototype_ `Audio::FParameterInterfacePtr CreateInterface();` (scope `Metasound::Engine::OutputFormatChannelAgnosticInterface`)
- L132 _typedef_ `using FOutputAudioFormatInfoMap = TMap<EMetaSoundOutputAudioFormat, FOutputAudioFormatInfo>;` (scope `Metasound::Engine`)
- L133 _typedef_ `using FOutputAudioFormatInfoPair = TPair<EMetaSoundOutputAudioFormat, FOutputAudioFormatInfo>;` (scope `Metasound::Engine`)
- L136 _prototype_ `const FOutputAudioFormatInfoMap& GetOutputAudioFormatInfo();` (scope `Metasound::Engine`) — Return a map containing all the supported output audio formats for a MetaSound.

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/Metasound.h` (Public)


#### class `UMetasoundEditorGraphBase`  
`class UMetasoundEditorGraphBase : public UEdGraph`  
_L35-65_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UEdGraph`
- L40 _public function_ `virtual bool IsEditorOnly() const override`
- L41 _public function_ `virtual bool NeedsLoadForEditorGame() const override`
- L43 _public function_ `virtual void RegisterGraphWithFrontend(Metasound::Frontend::FMetaSoundAssetRegistrationOptions* RegOptions = nullptr) PURE_VIRTUAL(UMetasoundEditorGraphBase::RegisterGraphWithFrontend(), ) #if WITH_EDITORONLY_DATA UE_DEPRECATED(5.5, "ModifyContext is to be replaced by builder API delegates providing context when items changed and it will be up to the caller to track modification deltas.") virtual FMetasoundFrontendDocumentModifyContext& GetModifyContext()`
- L50 _public function_ `virtual const FMetasoundFrontendDocumentModifyContext& GetModifyContext() const` — `UE_DEPRECATED(5.5, "ModifyContext is to be replaced by builder API delegates providing context when items changed and it will be up to the caller to track modification deltas.")`
- L53 _public function_ `virtual void ClearVersionedOnLoad()` — `UE_DEPRECATED(5.5, "Editor Graph is now transient, so versioning flag moved to AssetBase.")`
- L56 _public function_ `virtual bool GetVersionedOnLoad() const` — `UE_DEPRECATED(5.5, "Editor Graph is now transient, so versioning flag moved to AssetBase.")`
- L59 _public function_ `virtual void SetVersionedOnLoad()` — `UE_DEPRECATED(5.5, "Editor Graph is now transient, so versioning flag moved to AssetBase.")`
- L61 _public prototype_ `virtual void MigrateEditorDocumentData(FMetaSoundFrontendDocumentBuilder & OutBuilder) PURE_VIRTUAL(UMetasoundEditorGraphBase::MigrateEditorDocumentData(), ) #endif`

#### class `UMetaSoundPatch`  
`class UMetaSoundPatch : public UObject, public FMetasoundAssetBase, public IMetaSoundDocumentInterface`  
_L73-218_
- reflection: `UCLASS(MinimalAPI, hidecategories = object, BlueprintType, meta = (DisplayName = "MetaSound Patch"))`
- inherits: `UObject,FMetasoundAssetBase,IMetaSoundDocumentInterface`
- desc: This asset type is used for Metasound assets that can only be used as nodes in other Metasound graphs. Because of this, they contain no required inputs or outputs.
- L82 _protected member_ `FMetasoundFrontendDocument RootMetaSoundDocument;` — `UPROPERTY(EditAnywhere, Category = CustomView)`
- L85 _protected member_ `TSet<FString> ReferencedAssetClassKeys;` — `UPROPERTY()`
- L88 _protected member_ `TSet<TObjectPtr<UObject>> ReferencedAssetClassObjects;` — `UPROPERTY()`
- L92 _protected member_ `TSet<FSoftObjectPath> ReferenceAssetClassCache;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Soft reference cache is no longer supported"))`
- L95 _protected member_ `TObjectPtr<UMetasoundEditorGraphBase> Graph;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage = "Use EditorGraph instead as it is now transient and generated via the FrontendDocument dynamically."))`
- L98 _protected member_ `TObjectPtr<UMetasoundEditorGraphBase> EditorGraph;` — `UPROPERTY(Transient, NonTransactional)`
- L102 _public prototype_ `UMetaSoundPatch(const FObjectInitializer& ObjectInitializer);`
- L106 _public member_ `FGuid AssetClassID;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property is now serialized directly as asset tag"))`
- L109 _public member_ `FString RegistryInputTypes;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property is now serialized directly as asset tag"))`
- L112 _public member_ `FString RegistryOutputTypes;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property is now serialized directly as asset tag"))`
- L115 _public member_ `int32 RegistryVersionMajor = 0;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property is now serialized directly as asset tag"))`
- L118 _public member_ `int32 RegistryVersionMinor = 0;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property is now serialized directly as asset tag"))`
- L121 _public member_ `bool bIsPreset = false;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property is now serialized directly as asset tag"))`
- L125 _public function_ `static FName GetDocumentPropertyName()` — Returns document name (for editor purposes, and avoids making document public for edit while allowing editor to reference directly)
- L131 _public prototype_ `virtual FText GetDisplayName() const override;` — Name to display in editors
- L136 _public prototype_ `virtual UEdGraph* GetGraph() const override;` — Returns the graph associated with this Metasound. Graph is required to be referenced on Metasound UObject for editor serialization purposes. @return Editor graph associated with UMetaSoundSource.
- L137 _public prototype_ `virtual UEdGraph& GetGraphChecked() const override;`
- L138 _public prototype_ `virtual void MigrateEditorGraph(FMetaSoundFrontendDocumentBuilder& OutBuilder) override;`
- L143 _public function_ `virtual void SetGraph(UEdGraph* InGraph) override` — Sets the graph associated with this Metasound. Graph is required to be referenced on Metasound UObject for editor serialization purposes. @param Editor graph associated with UMetaSoundSource.
- L149 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L151 _public prototype_ `virtual FTopLevelAssetPath GetAssetPathChecked() const override;`
- L152 _public prototype_ `virtual const UClass& GetBaseMetaSoundUClass() const final override;`
- L153 _public prototype_ `virtual const UClass& GetBuilderUClass() const final override;`
- L154 _public prototype_ `virtual const FMetasoundFrontendDocument& GetConstDocument() const override;`
- L155 _public prototype_ `virtual EMetasoundFrontendClassAccessFlags GetDefaultAccessFlags() const final override;`
- L158 _public prototype_ `virtual void PreDuplicate(FObjectDuplicationParameters& DupParams) override;`
- L159 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L160 _public prototype_ `virtual void PostEditUndo() override;`
- L161 _public prototype_ `virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;`
- L165 _public prototype_ `virtual void BeginDestroy() override;`
- L166 _public prototype_ `virtual void PreSave(FObjectPreSaveContext InSaveContext) override;`
- L167 _public prototype_ `virtual void Serialize(FArchive& InArchive) override;`
- L168 _public prototype_ `virtual void PostLoad() override;`
- L170 _public function_ `virtual bool ConformObjectToDocument() override`
- L172 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;`
- L174 _public function_ `virtual const TSet<FString>& GetReferencedAssetClassKeys() const override`
- L178 _public prototype_ `virtual TArray<FMetasoundAssetBase*> GetReferencedAssets() const override;`
- L182 _public prototype_ `virtual void OnAsyncReferencedAssetsLoaded(const TArray<FMetasoundAssetBase*>& InAsyncReferences) override;` — `UE_DEPRECATED(5.8, "This is deprecated behavior and will become UE_INTERNAL API in a future release for back compat.")`
- L185 _public function_ `UObject* GetOwningAsset() override`
- L190 _public function_ `const UObject* GetOwningAsset() const override`
- L195 _public prototype_ `virtual bool IsActivelyBuilding() const override;`
- L199 _protected prototype_ `virtual void SetReferencedAssets(TSet<Metasound::Frontend::IMetaSoundAssetManager::FAssetRef>&& InAssetRefs) override;`
- L205 _protected prototype_ `Metasound::Frontend::FDocumentAccessPtr GetDocumentAccessPtr(bool bReloadBuilder = true) override;` — `UE_DEPRECATED(5.6, "AccessPtrs are actively being deprecated. Writable access outside of the builder API " "is particularly problematic as in so accessing, the builder's caches are reset which can cause major " "editor performance regressions.")`
- L206 _protected prototype_ `Metasound::Frontend::FConstDocumentAccessPtr GetDocumentConstAccessPtr() const override;`
- L209 _private function_ `virtual FMetasoundFrontendDocument& GetDocument() override`
- L214 _private prototype_ `virtual void OnBeginActiveBuilder() override;`
- L215 _private prototype_ `virtual void OnFinishActiveBuilder() override;`
- L217 _private member_ `bool bIsBuilderActive = false;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API METASOUNDENGINE_API`
- L28 _namespace_ `namespace Metasound`
- L28 _namespace_ `namespace Engine` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundAssetSubsystem.h` (Public)


#### class `Metasound::Engine::FMetaSoundAssetManager`  
`class FMetaSoundAssetManager : public Frontend::FMetaSoundAssetManagerBase, public FGCObject`  
_L34-225_
- inherits: `Frontend::FMetaSoundAssetManagerBase,FGCObject`
- L41 _public typedef_ `using FAssetClassInfoMap = TMap<FMetaSoundAssetKey, TArray<Frontend::FMetaSoundAssetClassInfo>>;`
- L42 _public typedef_ `using FOnUpdatedAssetLoaded = Frontend::IMetaSoundAssetManager::FOnUpdatedAssetLoaded;`
- L45 _public typedef_ `using FAssetInfo UE_DEPRECATED(5.6, "Use FAssetRef instead which is more compact and us`
- L48 _public typedef_ `using FNodeRegistryKey = Frontend::FNodeRegistryKey;`
- L51 _public typedef_ `using FVersionAssetResults = Frontend::IMetaSoundAssetManager::FVersionAssetResults;`
- L54 _public prototype_ `FMetaSoundAssetManager() = default;`
- L55 _public prototype_ `virtual ~FMetaSoundAssetManager();`
- L57 _public function_ `static FMetaSoundAssetManager* Get()`
- L63 _public function_ `static FMetaSoundAssetManager& GetChecked()`
- L77 _public prototype_ `Frontend::FMetaSoundAssetClassInfo FindAssetClassInfo(const FTopLevelAssetPath& InPath) const;` — Attempts to find the most recent class query info for the asset at the given path without loading asset. 1. If asset is loaded, builds tag data from asset (to ensure version provided is "freshest" if it has been edited but not re-serialized. 2. If asset is not loaded: a. Returns entry in Manager if sole entry found. b. If not registered or multiple entries found (may be more than one due to errors in duplication of assets, improper plugin migration), builds directly from the asset data last serialized with the given path/asset. c. If the asset data is out-of-date or not found, returns invalid query info.
- L83 _public prototype_ `virtual TArray<Frontend::FMetaSoundClassInfo> FindRegisteredClassInfo(const FMetaSoundAssetKey& InKey) const override;` — Returns all asset query info with the given asset key (may be more than one due to errors in duplication of assets, improper plugin migration, etc. but should usually just be a single entry) registered with the manager. Info may not be returned if the asset has yet to be registered with the MetaSoundAssetManager or may be out-of-date if edited after last registration attempt via AddOrUpdate... calls.
- L85 _public prototype_ `FMetaSoundAssetKey GetAssetKey(const FSoftObjectPath& InObjectPath) const;`
- L88 _public prototype_ `int32 GetActiveAsyncLoadRequestCount() const;`
- L91 _public prototype_ `bool IsInitialAssetScanComplete() const;`
- L94 _public prototype_ `void RebuildDenyListCache(const UAssetManager& InAssetManager);` — `UE_DEPRECATED(5.7, "DenyList Cache no longer supported (auto-update is now required when cooking and not supported at runtime")`
- L96 _public prototype_ `void RegisterAssetClassesInDirectories(const TArray<FMetaSoundAssetDirectory>& Directories);`
- L99 _public prototype_ `bool ReplaceReferencesInAsset(TScriptInterface<IMetaSoundDocumentInterface> InMetaSound, const Frontend::FNodeRegistryKey& OldClassKey, const Frontend::FNodeRegistryKey& NewClassKey) const;`
- L100 _public prototype_ `bool ReplaceReferencesInDirectory(const TArray<FMetaSoundAssetDirectory>& InDirectories, const FNodeRegistryKey& OldClassKey, const FNodeRegistryKey& NewClassKey) const;`
- L107 _public prototype_ `virtual void RequestAsyncLoadReferencedAssets(FMetasoundAssetBase& InAssetBase, const TSet<FSoftObjectPath>* Paths = nullptr) override;` — `UE_DEPRECATED(5.8, "This is a deprecated feature, and exists to port old soft object references to hard references. " "This will become UE_INTERNAL API in a future release.")`
- L110 _public prototype_ `void SearchAndIterateDirectoryAssets(const TArray<FDirectoryPath>& InDirectories, TFunctionRef<void(const FAssetData&)> InFunction) const;`
- L113 _public prototype_ `void SetCanNotifyAssetTagScanComplete();`
- L116 _public prototype_ `FMetasoundAssetBase* TryLoadAsset(const FSoftObjectPath& InObjectPath) const;`
- L117 _public prototype_ `void UnregisterAssetClassesInDirectories(const TArray<FMetaSoundAssetDirectory>& Directories);`
- L121 _public prototype_ `virtual bool AddAssetReferences(FMetasoundAssetBase& InAssetBase) override;`
- L123 _public prototype_ `virtual FMetaSoundAssetKey AddOrUpdateFromObject(const UObject& InObject) override;`
- L124 _public prototype_ `virtual void AddOrLoadAndUpdateFromObjectAsync(const FAssetData& InAssetData, Frontend::IMetaSoundAssetManager::FOnUpdatedAssetLoaded&& OnUpdatedAssetLoaded) override;`
- L125 _public prototype_ `virtual void AddOrUpdateFromAssetData(const FAssetData& InAssetData) override;`
- L127 _public prototype_ `virtual bool ContainsKey(const FMetaSoundAssetKey& InKey) const override;`
- L128 _public prototype_ `virtual bool ContainsKey(const Frontend::FNodeRegistryKey& InRegistryKey) const override;`
- L129 _public prototype_ `virtual FMetasoundAssetBase* FindAsset(const FMetaSoundAssetKey& InKey) const override;`
- L130 _public prototype_ `virtual TScriptInterface<IMetaSoundDocumentInterface> FindAssetAsDocumentInterface(const FMetaSoundAssetKey& InKey) const override;`
- L131 _public prototype_ `virtual FTopLevelAssetPath FindAssetPath(const FMetaSoundAssetKey& InKey) const override;`
- L132 _public prototype_ `virtual TArray<FTopLevelAssetPath> FindAssetPaths(const FMetaSoundAssetKey& InKey) const override;`
- L133 _public prototype_ `virtual FMetasoundAssetBase* GetAsAsset(UObject& InObject) const override;`
- L134 _public prototype_ `virtual const FMetasoundAssetBase* GetAsAsset(const UObject& InObject) const override;`
- L136 _public prototype_ `virtual TSet<Frontend::IMetaSoundAssetManager::FAssetRef> GetReferencedAssets(const FMetasoundAssetBase& InAssetBase) const override;`
- L137 _public prototype_ `virtual bool GetReferencedPresetHierarchy(FMetasoundAssetBase& InAsset, TArray<FMetasoundAssetBase*>& OutReferencedAssets) const override;`
- L138 _public prototype_ `virtual bool ReassignClassName(TScriptInterface<IMetaSoundDocumentInterface> DocInterface) override;`
- L141 _public prototype_ `virtual bool IsAssetClass(const FMetasoundFrontendClassMetadata& ClassMetadata) const override;`
- L145 _public prototype_ `void IterateAssetTagData(TFunctionRef<void(Frontend::FMetaSoundAssetClassInfo)> Iter, bool bIterateDuplicates = false) const;` — Iterates all asset tag data (Only recommended in certain editor contexts, as slow and blocks access to reference map).
- L149 _public prototype_ `void IterateReferences(const FMetaSoundAssetKey& InKey, TFunctionRef<void(const FMetaSoundAssetKey&)> VisitFunction) const;` — Iterates all references of a given asset key entry (Only recommended in certain editor contexts, as can be slow for deep reference trees and blocks access to reference map).
- L152 _public prototype_ `virtual void RemoveAsset(const UObject& InObject) override;`
- L153 _public prototype_ `virtual void RemoveAsset(const FAssetData& InAssetData) override;`
- L154 _public prototype_ `virtual void RenameAsset(const FAssetData& InAssetData, const FString& InOldObjectPath) override;`
- L155 _public prototype_ `virtual void ReregisterLoadedAssets() const override;`
- L156 _public prototype_ `virtual void SetLogActiveAssetsOnShutdown(bool bInLogActiveAssetsOnShutdown) override;`
- L157 _public prototype_ `virtual FMetasoundAssetBase* TryLoadAssetFromKey(const FMetaSoundAssetKey& InKey) const override;`
- L158 _public prototype_ `virtual bool TryGetAssetIDFromClassName(const FMetasoundFrontendClassName& InClassName, FGuid& OutGuid) const override;`
- L159 _public prototype_ `virtual bool TryLoadReferencedAssets(const FMetasoundAssetBase& InAssetBase, TArray<FMetasoundAssetBase*>& OutReferencedAssets) const override;`
- L161 _public prototype_ `FMetaSoundAssetManager::FVersionAssetResults SetAccessFlagsOnAssetsInFolders(const TArray<FString>& FolderPaths, EMetasoundFrontendClassAccessFlags Flags, bool bRecursePaths) const override;`
- L162 _public prototype_ `virtual FVersionAssetResults VersionAssetsInFolders(const TArray<FString>& FolderPaths, bool bRecursePaths = true) const override;`
- L163 _public prototype_ `virtual void WaitUntilAsyncLoadReferencedAssetsComplete(const FMetasoundAssetBase& InAssetBase) override;`
- L167 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject
- L168 _public function_ `virtual FString GetReferencerName() const override`
- L170 _public prototype_ `UE_INTERNAL virtual Frontend::FMetaSoundAssetRegistrationOptions GetRegistrationOptions() const override;`
- L173 _private prototype_ `FMetaSoundAssetKey AddOrUpdateFromObjectInternal(const UObject& InObject);`
- L176 _private member_ `TArray<FMetaSoundAsyncAssetDependencies> LoadingDependencies;`
- L179 _private prototype_ `static void DepthFirstVisit_AssetKey(const FMetaSoundAssetKey& InKey, TFunctionRef<TSet<FMetaSoundAssetKey>(const FMetaSoundAssetKey&)> VisitFunction);`
- L185 _private prototype_ `TArray<Frontend::FMetaSoundAssetClassInfo> FindAssetClassInfoInternal(const FMetaSoundAssetKey& InKey) const;` — Returns all asset query info with the given asset key (may be more than one due to errors in duplication of assets, improper plugin migration, etc. but should usually just be a single entry) registered with the manager. Info may not be returned if the asset has yet to be registered with the MetaSoundAssetManager or may be out-of-date if edited after last registration attempt via AddOrUpdate... calls.
- L188 _private prototype_ `FMetaSoundAsyncAssetDependencies* FindLoadingDependencies(const UObject* InParentAsset);`
- L189 _private prototype_ `FMetaSoundAsyncAssetDependencies* FindLoadingDependencies(int32 InLoadID);`
- L190 _private prototype_ `void RemoveLoadingDependencies(int32 InLoadID);`
- L191 _private prototype_ `void OnReferencedAssetsLoaded(int32 InLoadID);`
- L195 _private prototype_ `bool GetReferencedPresetHierarchyInternal(FMetasoundAssetBase& InAsset, TArray<FMetasoundAssetBase*>& OutReferencedAssets) const;`
- L198 _private prototype_ `bool ReplaceReferencesInAssetInternal(UObject* MetaSoundObject, const TMap<FNodeRegistryKey, FNodeRegistryKey>& InOldToNewReferenceKeys) const;`
- L209 _private prototype_ `static void OnPackageLoaded(const FPackageLoadedArgs& PackageLoadedArgs);`
- L211 _private member_ `FStreamableManager StreamableManager;`
- L212 _private member_ `int32 AsyncLoadIDCounter = 0;`
- L214 _private member_ `FAssetClassInfoMap ClassInfoMap;`
- L217 _private member_ `mutable FCriticalSection TagDataMapCriticalSection;` — Critical section primarily for allowing safe access of class info map during async loading of MetaSound assets.
- L219 _private member_ `bool bLogActiveAssetsOnShutdown = true;`
- L222 _private member_ `bool bNotifyTagDataScanComplete = false;`
- L223 _private member_ `int32 ActiveAsyncAssetLoadRequests = 0;`

#### struct `Metasound::Engine::FMetaSoundAssetManager::FPackageLoadedArgs`  
`struct FPackageLoadedArgs`  
_L201-207_
- L203 _public member_ `FName PackageName;`
- L204 _public member_ `UPackage* Package = nullptr;`
- L205 _public member_ `EAsyncLoadingResult::Type Result = EAsyncLoadingResult::Failed;`
- L206 _public member_ `FOnUpdatedAssetLoaded OnUpdatedAssetLoaded;`

#### struct `FMetaSoundAssetDirectory`  
`struct FMetaSoundAssetDirectory`  
_L230-236_
- reflection: `USTRUCT(BlueprintType)`
- L235 _public member_ `FDirectoryPath Directory;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Directories, meta = (RelativePath, LongPackageName))`

#### struct `FMetaSoundAsyncAssetDependencies`  
`struct FMetaSoundAsyncAssetDependencies`  
_L240-258_
- reflection: `USTRUCT()`
- desc: Contains info of assets which are currently async loading.
- L246 _public member_ `int32 LoadID = 0;` — ID of the async load
- L250 _public member_ `TObjectPtr<UObject> MetaSound;` — `UPROPERTY(Transient)` — Parent MetaSound
- L253 _public member_ `TArray<FSoftObjectPath> Dependencies;` — Dependencies of parent MetaSound
- L256 _public member_ `TSharedPtr<FStreamableHandle> StreamableHandle;` — Handle to in-flight streaming request

#### class `UMetaSoundAssetSubsystem`  
`class UMetaSoundAssetSubsystem : public UEngineSubsystem`  
_L262-322_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "MetaSound Asset Subsystem"))`
- inherits: `UEngineSubsystem`
- L268 _public typedef_ `using FAssetInfo UE_DEPRECATED(5.6, "No longer supported in favor of more compact and direct Asset`
- L271 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& InCollection) override;`
- L279 _public prototype_ `UPARAM(DisplayName = "Info Found") bool FindAssetClassInfo( UPARAM(DisplayName = "Path") const FTopLevelAssetPath& InPath, UPARAM(DisplayName = "Document Info") FMetaSoundDocumentInfo& OutDocInfo, UPARAM(DisplayName = "Interface Info") FMetaSoundClassInterfaceInfo& OutInterfaceInfo, UPARAM(DisplayName = "Force Load") bool bForceLoad = tr` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Utilities", meta = (AdvancedDisplay = "3"))` — Returns asset class info for the given MetaSound asset. Will attempt to get info without loading the asset if its tag data is up-to-date, or if set to force load, will load otherwise (synchronously and can be slow).  Returns true if asset is found, was MetaSound, and all data was retrieved successfully, false if not.
- L289 _public prototype_ `UPARAM(DisplayName = "Reference Info Found") bool FindReferencingAssetClassInfo( UPARAM(DisplayName = "MetaSound") TScriptInterface<IMetaSoundDocumentInterface> MetaSound, UPARAM(DisplayName = "Reference Paths") TArray<FTopLevelAssetPath>& OutPaths, UPARAM(DisplayName = "Document Info") TArray<FMetaSoundDocumentInfo>& OutDocInfo, UPARAM(DisplayName = "Interface Info") TArray<FMetaSoundClassInterfaceInfo>& OutInterfaceInfo, UPARAM(DisplayName = "Only Presets") bool bOnlyPresets = false, UPARAM(DisplayName = "Force Load") bool bForceLoad = tr` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Utilities", meta = (DisplayName = "Find Referencing Asset Class Info", AdvancedDisplay = "5"))` — Returns info for all MetaSounds assets referencing the given MetaSound as a dependency.  Only returns assets on disk (i.e. not in-memory, transient MetaSounds created by the builder API).  (Optional) Only returns references that are presets of the given MetaSound if bOnlyPresets is true.
- L299 _public prototype_ `UPARAM(DisplayName = "Reassigned") bool ReassignClassName(TScriptInterface<IMetaSoundDocumentInterface> DocI` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Utilities")` — Reassigns a new class name for the given MetaSound object, invalidating all references to the given MetaSound Asset.
- L305 _public prototype_ `UPARAM(DisplayName = "References Replaced") bool ReplaceReferencesInDirectory( const TArray<FMetaSoundAssetDirectory>& InDirectories, const FMetasoundFrontendClassName& OldClassName, const FMetasoundFrontendClassName& NewClassName, const FMetasoundFrontendVersionNumber OldVersion = FMetasoundFrontendVersionNumber(), const FMetasoundFrontendVersionNumber NewVersion = FMetasoundFrontendVersionNumber());` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Utilities", meta = (AdvancedDisplay = "3"))` — Replaces dependencies in a MetaSound with the given class name and version with another MetaSound with the given class name and version.  Can be asset or code-defined.  It is up to the caller to validate the two classes have matching interfaces (Swapping with classes of unmatched interfaces can leave MetaSound in non-executable state).
- L314 _public prototype_ `void RegisterAssetClassesInDirectories(const TArray<FMetaSoundAssetDirectory>& Directories);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Registration")`
- L317 _public prototype_ `void UnregisterAssetClassesInDirectories(const TArray<FMetaSoundAssetDirectory>& Directories);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Registration")`
- L320 _private prototype_ `void PostEngineInitInternal();`
- L321 _private prototype_ `void PostInitAssetScanInternal();`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API METASOUNDENGINE_API`
- L28 _namespace_ `namespace Metasound`
- L28 _namespace_ `namespace Engine` (scope `Metasound`)
- L30 _prototype_ `void DeinitializeAssetManager();` (scope `Metasound::Engine`)
- L31 _prototype_ `void InitializeAssetManager();` (scope `Metasound::Engine`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundAudioBus.h` (Public)


#### class `Metasound::FAudioBusAsset`  
`class FAudioBusAsset`  
_L18-44_
- desc: Metasound data type that holds onto a weak ptr. Mostly used as a placeholder until we have a proper proxy type.
- L20 _private member_ `FAudioBusProxyPtr AudioBusProxy;`
- L24 _public prototype_ `FAudioBusAsset() = default;`
- L25 _public prototype_ `FAudioBusAsset(const FAudioBusAsset&) = default;`
- L26 _public prototype_ `FAudioBusAsset& operator=(const FAudioBusAsset& Other) = default;`
- L28 _public prototype_ `FAudioBusAsset(const TSharedPtr<Audio::IProxyData>& InInitData);`
- L30 _public function_ `const FAudioBusProxyPtr& GetAudioBusProxy() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METASOUNDENGINE_API`
- L12 _namespace_ `namespace Metasound`
- L35 _function_ `friend inline uint32 GetTypeHash(const Metasound::FAudioBusAsset& InAudioBusAsset)` (scope `Metasound`)
- L48 _prototype_ `int32 AudioBusReaderNodeInitialNumBlocks(int32 BlockSizeFrames, int32 AudioMixerOutputFrames);` (scope `Metasound`)
- L49 _prototype_ `int32 AudioBusWriterNodeInitialNumBlocks(int32 BlockSizeFrames, int32 AudioMixerOutputFrames);` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundAudioBusWriterNode.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Metasound`
- L9 _namespace_ `namespace AudioBusWriterNode` (scope `Metasound`)
- L12 _function_ `template<uint32 NumChannels> const FNodeClassName& GetClassName()` (scope `Metasound::AudioBusWriterNode`)
- L19 _prototype_ `int32 GetCurrentMajorVersion();` (scope `Metasound::AudioBusWriterNode`)
- L21 _namespace_ `namespace Inputs` (scope `Metasound::AudioBusWriterNode`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundBuilderBase.h` (Public)


#### struct `FMetaSoundBuilderNodeInputHandle`  
`struct FMetaSoundBuilderNodeInputHandle : public FMetasoundFrontendVertexHandle`  
_L39-50_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "MetaSound Node Input Handle"))`
- inherits: `FMetasoundFrontendVertexHandle`
- L44 _public prototype_ `FMetaSoundBuilderNodeInputHandle() = default;`
- L45 _public function_ `FMetaSoundBuilderNodeInputHandle(const FGuid InNodeID, const FGuid& InVertexID)`

#### struct `FMetaSoundBuilderNodeOutputHandle`  
`struct FMetaSoundBuilderNodeOutputHandle : public FMetasoundFrontendVertexHandle`  
_L53-64_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "MetaSound Node Output Handle"))`
- inherits: `FMetasoundFrontendVertexHandle`
- L58 _public prototype_ `FMetaSoundBuilderNodeOutputHandle() = default;`
- L59 _public function_ `FMetaSoundBuilderNodeOutputHandle(const FGuid InNodeID, const FGuid& InVertexID)`

#### struct `FMetaSoundNodeHandle`  
`struct FMetaSoundNodeHandle`  
_L67-87_
- reflection: `USTRUCT(BlueprintType, meta = (DisplayName = "MetaSound Node Handle"))`
- L72 _public member_ `FGuid NodeID;` — `UPROPERTY()`
- L75 _public prototype_ `FMetaSoundNodeHandle() = default;`
- L76 _public function_ `FMetaSoundNodeHandle(const FGuid& InNodeID) : NodeID(InNodeID)`
- L83 _public function_ `bool IsSet() const` — Returns whether or not the vertex handle is set (may or may not be valid depending on what builder context it is referenced against)

#### struct `FMetaSoundBuilderOptions`  
`struct FMetaSoundBuilderOptions`  
_L90-114_
- reflection: `USTRUCT(BlueprintType)`
- L97 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaSound|Builder")` — Name of generated object. If object already exists, used as the base name to ensure new object is unique. If left 'None', creates unique name.
- L103 _public member_ `bool bForceUniqueClassName = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MetaSound|Builder", meta = (AdvancedDisplay))` — If the resulting MetaSound is building over an existing document, a unique class name will be generated, invalidating any referencing MetaSounds and registering the MetaSound as a new entry in the Frontend. If building a new document, option is ignored (new document always generates a unique class name).
- L108 _public member_ `bool bAddToRegistry = true;` — `UPROPERTY()` — If true, adds MetaSound to node registry, making it available for reference by other dynamically created MetaSounds.
- L113 _public member_ `TScriptInterface<IMetaSoundDocumentInterface> ExistingMetaSound;` — `UPROPERTY()` — If set, builder overwrites the given MetaSound's document with the builder's copy (ignores the Name field above).

#### enum `EMetaSoundBuilderResult`  
`enum class EMetaSoundBuilderResult : uint8`  
_L117-121_
- reflection: `UENUM(BlueprintType, meta = (DisplayName = "MetaSound Builder Result"))`
- L119 _public enumerator_ `Succeeded`
- L120 _public enumerator_ `Failed`

#### class `UMetaSoundBuilderBase`  
`class UMetaSoundBuilderBase : public UObject`  
_L125-730_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Transient, meta = (DisplayName = "MetaSound Builder Base"))`
- inherits: `UObject`
- desc: Base implementation of MetaSound builder
- L131 _public prototype_ `virtual void BeginDestroy() override;`
- L137 _public prototype_ `UPARAM(DisplayName = "Output Handle") FMetaSoundBuilderNodeOutputHandle AddGraphInputNode(FName Name, FName DataType, FMetasoundFrontendLiteral DefaultValue, EMetaSoundBuilderResult& OutResult, bool bIsConstructorIn` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult", AdvancedDisplay = "3"))` — Adds a graph input node with the given name, DataType, and sets the graph input to default value. Returns the new input node's output handle if it was successfully created, or an invalid handle if it failed.
- L142 _public prototype_ `UPARAM(DisplayName = "Input Handle") FMetaSoundBuilderNodeInputHandle AddGraphOutputNode(FName Name, FName DataType, FMetasoundFrontendLiteral DefaultValue, EMetaSoundBuilderResult& OutResult, bool bIsConstructorOutp` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult", AdvancedDisplay = "3"))` — Adds a graph output node with the given name, DataType, and sets output node's input to default value. Returns the new output node's input handle if it was successfully created, or an invalid handle if it failed.
- L148 _public prototype_ `void AddGraphPage(FName PageName, bool bDuplicateLastGraph, bool bSetAsBuildGraph, EMetaSoundBuilderResult& OutResult);` — Adds a graph page to the given builder's document. Fails if the page is not a valid page registered with MetaSoundSettings or if the document already contains a page with the given name. No check is done here to determine cook eligibility (i.e. pages can be added even if set to be stripped for the active platform).
- L153 _public prototype_ `void AddGraphVariable(FName Name, FName DataType, FMetasoundFrontendLiteral DefaultValue, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Adds a graph variable node with the given name, DataType, and sets to default value.
- L157 _public prototype_ `UPARAM(DisplayName = "Get Node Handle") FMetaSoundNodeHandle AddGraphVariableGetNode(FName Name, EMetaSoundBuilderResu` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Adds a graph variable node with the given name, DataType, and sets to default value.
- L161 _public prototype_ `UPARAM(DisplayName = "Get Delayed Node Handle") FMetaSoundNodeHandle AddGraphVariableGetDelayedNode(FName Name, EMetaSoundBui` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Adds a graph variable node with the given name, DataType, and sets to default value.
- L165 _public prototype_ `UPARAM(DisplayName = "Set Node Handle") FMetaSoundNodeHandle AddGraphVariableSetNode(FName Name, EMetaSoundBuilderResu` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Adds a graph variable node with the given name, DataType, and sets to default value.
- L169 _public prototype_ `void AddInterface(FName InterfaceName, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Adds an interface registered with the given name to the graph, adding associated input and output nodes.
- L174 _public prototype_ `UPARAM(DisplayName = "Node Handle") FMetaSoundNodeHandle AddNode(const TScriptInterface<IMetaSoundDocumentInterface>& NodeClass, EMetaSoundBuilderResult&` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", DisplayName = "Add MetaSound Node From Asset Class", meta = (ExpandEnumAsExecs = "OutResult"))` — Adds a node to the graph using the provided MetaSound asset as its defining NodeClass. Returns a node handle to the created node if successful, or an invalid handle if it failed.
- L179 _public prototype_ `UPARAM(DisplayName = "Node Handle") FMetaSoundNodeHandle AddNodeByClassName(const FMetasoundFrontendClassName& ClassName, EMetaSoundBuilderResult& OutResult, int32 MajorVe` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", DisplayName = "Add MetaSound Node By ClassName", meta = (ExpandEnumAsExecs = "OutResult", AdvancedDisplay = "2"))` — Adds node referencing the highest native class version of the given class name to the document. Returns a node handle to the created node if successful, or an invalid handle if it failed.
- L182 _public prototype_ `UPARAM(DisplayName = "Node Handle") FMetaSoundNodeHandle AddNodeByClassName(const FMetasoundFrontendClassName& ClassName, int32 MajorVersion, EMetaSoundBuilderResult&` — `UE_DEPRECATED(5.4, "This version of AddNodeByClassName is deprecated. Use the one with a default MajorVersion of 1.")`
- L187 _public prototype_ `FDelegateHandle AddTransactionListener(TSharedRef<Metasound::Frontend::IDocumentBuilderTransactionListener> BuilderListener);` — Adds transaction listener which allows objects to respond to when certain graph operations are applied from anywhere (adding or removing nodes, edges, pages, etc.) Currently there is no guarantee all transactions will be represented until the Controller API is fully deprecated! (ex. if a node or edge is added or removed via a controller API call, the transaction will be missed). OnBuilderReloaded is however guaranteed to be called on mutable controller creation.
- L190 _public prototype_ `bool ClearMemberMetadata(const FGuid& InMemberID);`
- L197 _public prototype_ `void ConnectNodes(const FMetaSoundBuilderNodeOutputHandle& NodeOutputHandle, const FMetaSoundBuilderNodeInputHandle& NodeInputHandle, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Connects node output to a node input. Does *NOT* provide loop detection for performance reasons.  Loop detection is checked on class registration when built or played. Returns succeeded if connection made, failed if connection already exists with input, the data types do not match, or the connection is not supported due to access type incompatibility (ex. constructor input to non-constructor input).
- L201 _public prototype_ `void ConnectNodesByInterfaceBindings(const FMetaSoundNodeHandle& FromNodeHandle, const FMetaSoundNodeHandle& ToNodeHandle, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Connects two nodes using defined MetaSound Interface Bindings registered with the MetaSound Interface registry.
- L205 _public prototype_ `UPARAM(DisplayName = "Connected Graph Output Node Inputs") TArray<FMetaSoundBuilderNodeInputHandle> ConnectNodeOutputsToMatchingGraphInterfaceOutputs(const FMetaSoundNodeHandle& NodeHandle, EM` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Connects a given node's outputs to all graph outputs for shared interfaces implemented on both the node's referenced class and the builder's MetaSound graph. Returns inputs of connected output nodes.
- L209 _public prototype_ `UPARAM(DisplayName = "Connected Graph Input Node Outputs") TArray<FMetaSoundBuilderNodeOutputHandle> ConnectNodeInputsToMatchingGraphInterfaceInputs(const FMetaSoundNodeHandle& NodeHandle, EM` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Connects a given node's inputs to all graph inputs for shared interfaces implemented on both the node's referenced class and the builder's MetaSound graph. Returns outputs of connected input nodes.
- L213 _public prototype_ `void ConnectNodeOutputToGraphOutput(FName GraphOutputName, const FMetaSoundBuilderNodeOutputHandle& NodeOutputHandle, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Connects a given node output to the graph output with the given name.
- L217 _public function_ `inline void ConnectNamedNodeOutputToNamedGraphOutput(const FMetaSoundNodeHandle& SourceNode, const FName& NodeOutputName, const FName& GraphOutputName, EMetaSoundBuilderResult& OutResult)` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Connects a given node's named output to the graph output with the given name.
- L221 _public prototype_ `void ConnectNodeToGraphOutput(const FMetaSoundNodeHandle& SourceNode, const FName& NodeOutputName, const FName& GraphOutputName, EMetaSoundBuilderResult& OutResult);`
- L225 _public function_ `inline void ConnectNamedNodeOutputToGraphOutput(const FMetaSoundNodeHandle& SourceNode, const FName& NodeOutputName, const FMetaSoundBuilderNodeInputHandle& GraphOutput, EMetaSoundBuilderResult& OutResult)` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Connects a given node's named output to the graph output with the given handle.
- L229 _public prototype_ `void ConnectNodeToGraphOutput(const FMetaSoundNodeHandle& SourceNode, const FName& NodeOutputName, const FMetaSoundBuilderNodeInputHandle& GraphOutput, EMetaSoundBuilderResult& OutResult);`
- L233 _public prototype_ `void ConnectNodeInputToGraphInput(FName GraphInputName, const FMetaSoundBuilderNodeInputHandle& NodeInputHandle, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Connects a given node input to the graph input with the given name.
- L235 _public prototype_ `void ConnectGraphInputToNode(const FName& GraphInputName, const FMetaSoundNodeHandle& DestinationNode, const FName& InputName, EMetaSoundBuilderResult& OutResult);`
- L237 _public prototype_ `void ConnectNodes(const FMetaSoundNodeHandle& SourceNode, const FName& OutputName, const FMetaSoundNodeHandle& DestinationNode, const FName& InputName, EMetaSoundBuilderResult& OutResult);`
- L241 _public prototype_ `UPARAM(DisplayName = "IsValid") bool ContainsNode(const FMetaSoundNodeHandle& Node)` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Returns whether node exists.
- L245 _public prototype_ `UPARAM(DisplayName = "IsValid") bool ContainsNodeInput(const FMetaSoundBuilderNodeInputHandle& Input)` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Returns whether node input exists.
- L249 _public prototype_ `UPARAM(DisplayName = "IsValid") bool ContainsNodeOutput(const FMetaSoundBuilderNodeOutputHandle& Output)` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Returns whether node output exists.
- L253 _public prototype_ `void DisconnectNodes(const FMetaSoundBuilderNodeOutputHandle& NodeOutputHandle, const FMetaSoundBuilderNodeInputHandle& NodeInputHandle, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Disconnects node output to a node input. Returns success if connection was removed, failed if not.
- L257 _public prototype_ `void DisconnectNodeInput(const FMetaSoundBuilderNodeInputHandle& NodeInputHandle, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Removes connection to a given node input. Returns success if connection was removed, failed if not.
- L261 _public prototype_ `void DisconnectNodeOutput(const FMetaSoundBuilderNodeOutputHandle& NodeOutputHandle, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Removes all connections from a given node output. Returns success if all connections were removed, failed if not.
- L266 _public prototype_ `void DisconnectNodesByInterfaceBindings(const FMetaSoundNodeHandle& FromNodeHandle, const FMetaSoundNodeHandle& ToNodeHandle, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Disconnects two nodes using defined MetaSound Interface Bindings registered with the MetaSound Interface registry. Returns success if all connections were found and removed, failed if any connections were not.
- L270 _public prototype_ `UPARAM(DisplayName = "Node Handle") FMetaSoundNodeHandle FindGraphInputNode(FName InputName, UPARAM(DisplayName = "Data Type") FName& OutDataType, FMetaSoundBuilderNodeOutputHandle& NodeOutputHandle, EMetaSoundBuilde` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns graph input node by the given name if it exists, or an invalid handle if not found.
- L272 _public prototype_ `UPARAM(DisplayName = "Node Handle") FMetaSoundNodeHandle FindGraphInputNode(FName InputName, EMetaSoundBuilderResult&`
- L276 _public prototype_ `UPARAM(DisplayName = "Node Handle") FMetaSoundNodeHandle FindGraphOutputNode(FName OutputName, UPARAM(DisplayName = "Data Type") FName& OutDataType, FMetaSoundBuilderNodeInputHandle& NodeInputHandle, EMetaSoundBuilde` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns graph output node by the given name if it exists, or an invalid handle if not found.
- L278 _public prototype_ `UPARAM(DisplayName = "Node Handle") FMetaSoundNodeHandle FindGraphOutputNode(FName OutputName, EMetaSoundBuilderResult&`
- L281 _public prototype_ `UMetaSoundFrontendMemberMetadata* FindMemberMetadata(const FGuid& InMemberID);`
- L286 _public prototype_ `UPARAM(DisplayName = "Input Handle") FMetaSoundBuilderNodeInputHandle FindNodeInputByName(const FMetaSoundNodeHandle& NodeHandle, FName InputName, EMetaSoundBuilderResult&` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns node input by the given name if it exists, or an invalid handle if not found.
- L290 _public prototype_ `UPARAM(DisplayName = "Input Handles") TArray<FMetaSoundBuilderNodeInputHandle> FindNodeInputs(const FMetaSoundNodeHandle& NodeHandle, EMetaSoundBuilderResul` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns all node inputs.
- L294 _public prototype_ `UPARAM(DisplayName = "Input Handles") TArray<FMetaSoundBuilderNodeInputHandle> FindNodeInputsByDataType(const FMetaSoundNodeHandle& NodeHandle, EMetaSoundBuilderResult& OutResult, FNa` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns node inputs by the given DataType (ex. "Audio", "Trigger", "String", "Bool", "Float", "Int32", etc.).
- L298 _public prototype_ `UPARAM(DisplayName = "Output Handle") FMetaSoundBuilderNodeOutputHandle FindNodeOutputByName(const FMetaSoundNodeHandle& NodeHandle, FName OutputName, EMetaSoundBuilderResult` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns node output by the given name.
- L302 _public prototype_ `UPARAM(DisplayName = "Output Handles") TArray<FMetaSoundBuilderNodeOutputHandle> FindNodeOutputs(const FMetaSoundNodeHandle& NodeHandle, EMetaSoundBuilderResul` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns all node outputs.
- L306 _public prototype_ `UPARAM(DisplayName = "Output Handles") TArray<FMetaSoundBuilderNodeOutputHandle> FindNodeOutputsByDataType(const FMetaSoundNodeHandle& NodeHandle, EMetaSoundBuilderResult& OutResult, FN` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns node outputs by the given DataType (ex. "Audio", "Trigger", "String", "Bool", "Float", "Int32", etc.).
- L310 _public prototype_ `UPARAM(DisplayName = "Input Node Handles") TArray<FMetaSoundNodeHandle> FindInterfaceInputNodes(FName InterfaceName, EMetaSoundBuilderR` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns input nodes associated with a given interface.
- L314 _public prototype_ `UPARAM(DisplayName = "Output Node Handles") TArray<FMetaSoundNodeHandle> FindInterfaceOutputNodes(FName InterfaceName, EMetaSoundBuilder` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns output nodes associated with a given interface.
- L318 _public prototype_ `UPARAM(DisplayName = "Node Handle") FMetaSoundNodeHandle FindNodeInputParent(const FMetaSoundBuilderNodeInputHandle& InputHandle, EMetaSoundBuilderResult&` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns input's parent node if the input is valid, otherwise returns invalid node handle.
- L322 _public prototype_ `UPARAM(DisplayName = "Node Handle") FMetaSoundNodeHandle FindNodeOutputParent(const FMetaSoundBuilderNodeOutputHandle& OutputHandle, EMetaSoundBuilderResult&` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns output's parent node if the input is valid, otherwise returns invalid node handle.
- L326 _public prototype_ `UPARAM(DisplayName = "Node Class Version") FMetasoundFrontendVersion FindNodeClassVersion(const FMetaSoundNodeHandle& NodeHandle, EMetaSoundBuilderR` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns output's parent node if the input is valid, otherwise returns invalid node handle.
- L330 _public prototype_ `TInstancedStruct<FMetaSoundFrontendDocumentTemplate> GetDocumentTemplate(EMetaSoundBuilderResult& OutResult) const;` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns copy of the builder's template. Returns success if the builder has a template set, fails if not.
- L333 _public function_ `TInstancedStruct<FMetaSoundFrontendDocumentTemplate> GetConfiguration(EMetaSoundBuilderResult& OutResult) const` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DeprecatedFunction, DeprecationMessage = "5.8 - Use GetDocumentTemplate instead", ExpandEnumAsExecs = "OutResult"))`
- L337 _public prototype_ `UPARAM(DisplayName = "Graph Inputs") TArray<FName> GetGraphInputNames(EMetaSoundBuilderResult& OutRe` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Gets names of all graph inputs.
- L341 _public prototype_ `UPARAM(DisplayName = "Graph Outputs") TArray<FName> GetGraphOutputNames(EMetaSoundBuilderResult& OutR` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Gets names of all graph outputs.
- L346 _public prototype_ `UPARAM(DisplayName = "Literal Value") FMetasoundFrontendLiteral GetGraphInputDefault(FName InputName, EMetaSoundBuilderResult& OutResult, FName PageName = FN` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult", AdvancedDisplay = "PageName"))` — Gets the graph input's default literal value. @param PageName	If the page name is not specified or not found, the builder's current build page will be used (which can be set in the MetaSound editor).
- L350 _public prototype_ `UPARAM(DisplayName = "Literal Value") FMetasoundFrontendLiteral GetGraphVariableDefault(FName VariableName, EMetaSoundBuilderResult& OutR` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Gets the graph variable's default literal value.
- L354 _public prototype_ `UPARAM(DisplayName = "Class Name") FMetasoundFrontendClassName GetRootGraphClassNam` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder|Advanced", meta = (DisplayName = "Get MetaSound Class Name"))` — Returns the MetaSound asset's graph class name (used by the MetaSound Node Class Registry)
- L358 _public prototype_ `UPARAM(DisplayName = "MetaSound") TScriptInterface<IMetaSoundDocumentInterface> GetMetaSound` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Returns the interface to the MetaSound the builder is acting on.
- L362 _public prototype_ `void GetNodeInputData(const FMetaSoundBuilderNodeInputHandle& InputHandle, FName& Name, FName& DataType, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns node input's data if valid (including things like name and datatype).
- L366 _public prototype_ `UPARAM(DisplayName = "Default") FMetasoundFrontendLiteral GetNodeInputDefault(const FMetaSoundBuilderNodeInputHandle& InputHandle, EMetaSoundBuilderResult& OutR` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns node input's literal value if set on graph, otherwise fails and returns default literal.
- L370 _public prototype_ `UPARAM(DisplayName = "Default") FMetasoundFrontendLiteral GetNodeInputClassDefault(const FMetaSoundBuilderNodeInputHandle& InputHandle, EMetaSoundBuilderResult& OutR` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns node input's class literal value if set, otherwise fails and returns default literal.
- L374 _public prototype_ `UPARAM(DisplayName = "Is Constructor Pin") bool GetNodeInputIsConstructorPin(const FMetaSoundBuilderNodeInputHandle& I` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Returns whether the given node input is a constructor pin
- L378 _public prototype_ `void GetNodeOutputData(const FMetaSoundBuilderNodeOutputHandle& OutputHandle, FName& Name, FName& DataType, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns node output's data if valid (including things like name and datatype).
- L382 _public prototype_ `UPARAM(DisplayName = "Is Constructor Pin") bool GetNodeOutputIsConstructorPin(const FMetaSoundBuilderNodeOutputHandle& Ou` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Returns whether the given node output is a constructor pin
- L386 _public prototype_ `UPARAM(DisplayName = "Referenced Preset") UObject* GetReferencedPre` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Get Preset Parent"))` — Return the parent asset referenced by this preset builder. Returns nullptr if the builder is not a preset.
- L390 _public prototype_ `UPARAM(DisplayName = "Is Declared") bool InterfaceIsDeclared(FName InterfaceN` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Returns if a given interface is declared.
- L394 _public prototype_ `UPARAM(DisplayName = "Connected") bool NodesAreConnected(const FMetaSoundBuilderNodeOutputHandle& OutputHandle, const FMetaSoundBuilderNodeInputHandle& InputHandl` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Returns if a given node output and node input are connected.
- L398 _public prototype_ `UPARAM(DisplayName = "Connected") bool NodeInputIsConnected(const FMetaSoundBuilderNodeInputHandle& InputHandl` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Returns if a given node input has connections.
- L402 _public prototype_ `UPARAM(DisplayName = "Connected") bool NodeOutputIsConnected(const FMetaSoundBuilderNodeOutputHandle& OutputHandl` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Returns if a given node output is connected.
- L406 _public prototype_ `UPARAM(DisplayName = "Is Preset") bool IsPreset` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Returns whether this is a preset.
- L410 _public prototype_ `void ConvertFromPreset(EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Converts this preset to a fully accessible MetaSound; sets result to succeeded if it was converted successfully and failed if it was not.
- L414 _public prototype_ `void ConvertToPreset(UPARAM(DisplayName = "Parent Node Class") const TScriptInterface<IMetaSoundDocumentInterface>& ReferencedNodeClass, EMetaSoundBuilderRe` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Convert this builder to a MetaSound preset using the given MetaSoundDocumentInterface as its parent.
- L419 _public prototype_ `void ResetGraphInputDefaults(FName Name, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Removes input literal defaults for all pages if set, reverting the value to the class defaults Returns success if values reset, false if not (i.e. wasn't set to begin with).
- L423 _public prototype_ `void ResetGraphPages(bool bClearDefaultPage);` — Removes all graph pages except the default.  If bClearDefaultPage is true, clears the default graph page implementation.
- L428 _public prototype_ `void RemoveGraphInput(FName Name, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Removes input from all paged graphs if it exists; sets result to succeeded if it was removed and failed if it was not.
- L434 _public prototype_ `void RemoveGraphInputDefault(FName Name, EMetaSoundBuilderResult& OutResult, FName PageName = FName());` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult", AdvancedDisplay = "PageName"))` — Removes graph input literal default if set, reverting the value to the class default @param PageName If the page name is not specified or not found, the builder's current build page will be used (which can be set in the MetaSound editor). Returns success if value was removed, false if not removed (i.e. wasn't set to begin with).
- L438 _public prototype_ `void RemoveGraphOutput(FName Name, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Removes output from all paged graphs if it exists; sets result to succeeded if it was removed and failed if it was not.
- L442 _public prototype_ `void RemoveGraphPage(FName Name, EMetaSoundBuilderResult& OutResult);` — Removes a graph page with the given name, setting result to failed if the name was not found or was invalid.
- L447 _public prototype_ `void RemoveGraphVariable(FName Name, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Removes graph variable from the current build graph if it exists; sets result to succeeded if it was removed and failed if it was not.
- L452 _public prototype_ `void RemoveInterface(FName InterfaceName, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Removes the interface with the given name from the builder's MetaSound. Removes any graph inputs and outputs associated with the given interface and their respective connections (if any).
- L457 _public prototype_ `void RemoveNode(const FMetaSoundNodeHandle& NodeHandle, EMetaSoundBuilderResult& OutResult, bool bRemoveUnusedDependencies = true);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult", AdvancedDisplay = "2"))` — Removes node and any associated connections from the current build graph. (Advanced) Optionally, remove unused dependencies from the internal dependency list on successful removal of node.
- L462 _public prototype_ `void RemoveNodeInputDefault(const FMetaSoundBuilderNodeInputHandle& InputHandle, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Removes node input literal default if set, reverting the value to be whatever the node class defaults the value to. Returns success if value was removed, false if not removed (i.e. wasn't set to begin with).
- L466 _public prototype_ `void RemoveTransactionListener(FDelegateHandle BuilderListenerDelegateHandle);` — Explicitly remove transaction listener from builder (see corresponding 'AddTransactionListener' function). (If listener provided with `AddTransactionListener` is destroyed, handled automatically)
- L470 _public prototype_ `void RemoveUnusedDependencies();` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Removes dependencies in document that are no longer referenced by nodes
- L473 _public prototype_ `void RenameRootGraphClass(const FMetasoundFrontendClassName& InName);` — `UE_DEPRECATED(5.5, "Use IDocumentBuilderRegistry::GenerateNewClassName instead to maintain registry mappings.")`
- L477 _public prototype_ `void ReloadCache(bool bPrimeCache = true);` — `UE_DEPRECATED(5.5, "Moved to internal implementation and only accessible via registry to ensure delegates are properly reloaded, " "path keys kept aligned, and priming managed internally")`
- L481 _public prototype_ `void SetAuthor(const FString& InAuthor);` — Sets the author of the MetaSound.
- L486 _public prototype_ `void SetTemplate(TInstancedStruct<FMetaSoundFrontendDocumentTemplate> Configuration);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Sets the given builder's template and immediately configures the MetaSound.
- L489 _public function_ `void SetConfiguration(TInstancedStruct<FMetaSoundFrontendDocumentTemplate> Configuration)` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DeprecatedFunction, DeprecationMessage = "5.8 - Use SetTemplate instead"))`
- L492 _public prototype_ `void SetTemplateProperties(TFunctionRef<void(TStructView<FMetaSoundFrontendDocumentTemplate>)> SetPropertiesFunction);` — Passes view of struct along for mutating properties, firing OnDocumentTemplateChanged on completion and immediately reconfigures the MetaSound.
- L495 _public function_ `void SetConfigurationProperties(TFunctionRef<void(TStructView<FMetaSoundFrontendDocumentTemplate>)> SetPropertiesFunction)` — `UE_DEPRECATED(5.8, "Use SetTemplateProperties() instead")`
- L498 _public function_ `template <typename TConfig> bool SetTemplateProperties(TFunctionRef<void(TConfig&)> SetPropertyFunction)`
- L512 _public prototype_ `void SetNodeInputDefault(const FMetaSoundBuilderNodeInputHandle& NodeInputHandle, const FMetasoundFrontendLiteral& Literal, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Sets the node's input default value (used if no connection to the given node input is present)
- L516 _public function_ `template <typename LiteralType> void SetNodeInputDefault(const FMetaSoundNodeHandle& NodeHandle, const FName& InputName, const LiteralType& Literal, EMetaSoundBuilderResult& OutResult)` — Templated convenience function for setting the node's input default value (used if no connection to the given node input is present)
- L531 _public prototype_ `void SetGraphInputAccessType(FName InputName, EMetasoundFrontendVertexAccessType AccessType, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Disconnects the given graph input's respective template nodes and sets the graph input's AccessType should it not match the current AccessType. Result succeeds if the AccessType was successfully changed or if the provided AccessType is already the input's current AccessType.
- L536 _public prototype_ `void SetGraphInputDataType(FName InputName, FName DataType, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Disconnects the given graph input's respective template nodes and sets the graph input's DataType should it not match the current DataType. Result succeeds if the DataType was successfully changed or if the provided DataType is already the input's current DataType.
- L542 _public prototype_ `void SetGraphInputDefault(FName InputName, const FMetasoundFrontendLiteral& Literal, EMetaSoundBuilderResult& OutResult, FName PageName = FName());` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult", AdvancedDisplay = "PageName"))` — Sets the input node's default value, overriding the default provided by the referenced graph if the graph is a preset. @param PageName	If the page name is not specified or not found, the builder's current build page will be used (which can be set in the MetaSound editor).
- L547 _public prototype_ `void SetGraphInputName(FName InputName, FName NewName, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Sets the given graph input's name to the new name. Result succeeds if the name was successfully changed or the new name is the same as the old name, and fails if the given input name doesn't exist.
- L552 _public prototype_ `void SetGraphOutputAccessType(FName OutputName, EMetasoundFrontendVertexAccessType AccessType, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Disconnects the given graph output's respective template nodes and sets the graph output's AccessType should it not match the current AccessType. Result succeeds if the AccessType was successfully changed or if the provided AccessType is already the output's current AccessType.
- L557 _public prototype_ `void SetGraphOutputDataType(FName OutputName, FName DataType, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Disconnects the given graph output's respective template nodes and sets the graph output's DataType should it not match the current DataType. Result succeeds if the DataType was successfully changed or if the provided DataType is already the output's current DataType.
- L562 _public prototype_ `void SetGraphOutputName(FName OutputName, FName NewName, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Sets the given graph output's name to the new name. Result succeeds if the name was successfully changed or the new name is the same as the old name, and fails if the given output name doesn't exist.
- L564 _public prototype_ `void SetMemberMetadata(UMetaSoundFrontendMemberMetadata& NewMetadata);`
- L567 _public function_ `virtual UPARAM(DisplayName = "MetaSound") TScriptInterface<IMetaSoundDocumentInterface> Build(UObject* Parent, const FMetaSoundBuilderOptions& Option` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (WorldContext = "Parent", DisplayName = "Build (Soft Deprecated. Parent no longer supported and field is ignored.)"))`
- L570 _public prototype_ `TScriptInterface<IMetaSoundDocumentInterface> Build(const FMetaSoundBuilderOptions& Options) const;`
- L579 _public prototype_ `void BuildAndOverwriteMetaSound(UPARAM(DisplayName = "Existing MetaSound") TScriptInterface<IMetaSoundDocumentInterface> ExistingMetaSound, bool bForceUniqueC` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Build And Overwrite MetaSound", AdvancedDisplay = "1"))` — Copies a transient MetaSound with the provided builder options, copying the underlying MetaSound managed by this builder and registering it with the MetaSound Node Registry as a unique name. If 'Force Unique Class Name' is true, registers MetaSound as a new class in the registry, potentially invalidating existing references in other MetaSounds. Not permissible to overwrite MetaSound asset, only transient MetaSound (see EditorSubsystem for overwriting assets at edit time).
- L586 _public prototype_ `virtual UPARAM(DisplayName = "New MetaSound") TScriptInterface<IMetaSoundDocumentInterface> BuildNewMetaSound(FName NameBase) const PURE_VIRTUAL(UMetaSoundBuilderBase::BuildNewMetaSound, r` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Build New MetaSound"))` — Builds a transient MetaSound with the provided builder options, copying the underlying MetaSound managed by this builder and registering it with the MetaSound Node Registry as a unique class. If existing MetaSound exists with the provided NameBase, will make object with unique name with the given NameBase as prefix.
- L588 _public prototype_ `virtual bool ConformObjectToDocument();`
- L591 _public prototype_ `virtual const UClass& GetBaseMetaSoundUClass() const PURE_VIRTUAL(UMetaSoundBuilderBase::GetBaseMetaSoundUClass, return *UClass::StaticClass(); );` — Returns the base class registered with the MetaSound UObject registry.
- L594 _public function_ `virtual const UClass& GetBuilderUClass() const` — `UE_DEPRECATED(5.5, "Renamed to 'GetBaseMetaSoundUClass' for consistency")`
- L596 _public prototype_ `Metasound::Frontend::FDocumentModifyDelegates& GetBuilderDelegates();`
- L599 _public prototype_ `virtual void InitNodeLocations();` — Initializes and ensures all nodes have a position (required prior to exporting to an asset if expected to be viewed in the editor).
- L607 _public prototype_ `void InjectInputTemplateNodes(bool bForceNodeCreation, EMetaSoundBuilderResult& OutResult);` — Injects template nodes between builder's document inputs not connected to existing template inputs, copying locational data from the represented input metadata. If bForceNodeCreation is false, only generates a template input node if a connection between the input and other nodes exists. If true, will inject template node irrespective of whether or not the input has connections.
- L609 _public prototype_ `const FMetaSoundFrontendGraphComment* FindGraphComment(const FGuid& InCommentID) const;`
- L610 _public prototype_ `FMetaSoundFrontendGraphComment* FindGraphComment(const FGuid & InCommentID);`
- L611 _public prototype_ `FMetaSoundFrontendGraphComment& FindOrAddGraphComment(const FGuid& InCommentID);`
- L612 _public prototype_ `bool RemoveGraphComment(const FGuid& InCommentID);`
- L614 _public prototype_ `void SetNodeComment(const FMetaSoundNodeHandle& InNodeHandle, const FString& InNewComment, EMetaSoundBuilderResult& OutResult);`
- L615 _public prototype_ `void SetNodeCommentVisible(const FMetaSoundNodeHandle& InNodeHandle, bool bIsVisible, EMetaSoundBuilderResult& OutResult);`
- L616 _public prototype_ `void SetNodeLocation(const FMetaSoundNodeHandle& InNodeHandle, const FVector2D& InLocation, EMetaSoundBuilderResult& OutResult);`
- L617 _public prototype_ `void SetNodeLocation(const FMetaSoundNodeHandle & InNodeHandle, const FVector2D& InLocation, const FGuid& InLocationGuid, EMetaSoundBuilderResult& OutResult);`
- L620 _public prototype_ `FMetaSoundFrontendDocumentBuilder& GetBuilder();`
- L621 _public prototype_ `const FMetaSoundFrontendDocumentBuilder& GetConstBuilder() const;`
- L622 _public prototype_ `int32 GetLastTransactionRegistered() const;`
- L625 _public prototype_ `void Initialize();` — Resets FrontendBuilder instance, creating a transient MetaSound document that is managed by this UObject Builder.
- L628 _public prototype_ `void Initialize(TScriptInterface<IMetaSoundDocumentInterface>& DocInterface);` — Initializes builder given an existing document interface
- L631 _protected prototype_ `virtual void BuildAndOverwriteMetaSoundInternal(TScriptInterface<IMetaSoundDocumentInterface> ExistingMetaSound, bool bForceUniqueClassName) const PURE_VIRTUAL(UMetaSoundBuilderBase::BuildAndOverwriteMetaSoundInternal, ;);`
- L632 _protected prototype_ `virtual void InitDelegates(Metasound::Frontend::FDocumentModifyDelegates& OutDocumentDelegates);`
- L634 _protected prototype_ `virtual void OnAssetReferenceAdded(TScriptInterface<IMetaSoundDocumentInterface> DocInterface) PURE_VIRTUAL(UMetaSoundBuilderBase::OnAssetReferenceAdded, );`
- L635 _protected prototype_ `virtual void OnRemovingAssetReference(TScriptInterface<IMetaSoundDocumentInterface> DocInterface) PURE_VIRTUAL(UMetaSoundBuilderBase::OnRemovingAssetReference, );`
- L639 _protected function_ `template <typename UClassType> UClassType& BuildInternal(UObject* Parent, const FMetaSoundBuilderOptions& BuilderOptions) const` — Runs build, conforming the document and corresponding object data on a MetaSound UObject to that managed by this builder.
- L701 _protected prototype_ `static void RegisterGraphIfOutstandingTransactions(UObject& InMetaSound);` — Only registers provided MetaSound's graph class and referenced graphs recursively if it has yet to be registered or if it has an attached builder reporting outstanding transactions that have yet to be registered.
- L704 _protected member_ `FMetaSoundFrontendDocumentBuilder Builder;` — `UPROPERTY()`
- L708 _protected member_ `FMetasoundFrontendClassName ClassName;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "5.5 - No longer used. ClassName should be queried from associated FrontendBuilder's MetaSound"))`
- L711 _protected member_ `bool bIsAttached = false;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "5.4 - All source builders now operate on an underlying document source document that is also used to audition."))`
- L715 _private prototype_ `void BuildInternal(TScriptInterface<IMetaSoundDocumentInterface> NewMetaSound, const FMetasoundFrontendClassName* InDocClassName) const;`
- L716 _private prototype_ `void OnDependencyAdded(int32 Index);`
- L717 _private prototype_ `void OnRemoveSwappingDependency(int32 Index, int32 LastIndex);`
- L723 _private prototype_ `void Reload(TScriptInterface<IMetaSoundDocumentInterface> NewMetaSound = { }, bool bPrimeCache = false);` — Reloads the builder, freeing the internal cache and rebuilding delegate bindings. Optionally, can be associated with a new MetaSound (ex. during rename. Otherwise it reuses the existing document object reference) or can have its cache primed.
- L725 _private member_ `Metasound::Engine::FOnBuilderReload BuilderReloadDelegate;`
- L727 _private member_ `int32 LastTransactionRegistered = 0;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API METASOUNDENGINE_API`
- L29 _namespace_ `namespace Metasound`
- L29 _namespace_ `namespace Engine` (scope `Metasound`)
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuilderReload, Metasound::Frontend::FDocumentModifyDelegates& ) }`

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundBuilderSubsystem.h` (Public)


#### class `UMetaSoundPatchBuilder`  
`class UMetaSoundPatchBuilder : public UMetaSoundBuilderBase`  
_L53-67_
- reflection: `UCLASS(MinimalAPI, Transient, BlueprintType, meta = (DisplayName = "MetaSound Patch Builder"))`
- inherits: `UMetaSoundBuilderBase`
- desc: Builder in charge of building a MetaSound Patch
- L58 _public prototype_ `virtual TScriptInterface<IMetaSoundDocumentInterface> BuildNewMetaSound(FName NameBase) const override;`
- L59 _public prototype_ `virtual const UClass& GetBaseMetaSoundUClass() const override;`
- L62 _protected prototype_ `virtual void BuildAndOverwriteMetaSoundInternal(TScriptInterface<IMetaSoundDocumentInterface> ExistingMetaSound, bool bForceUniqueClassName) const override;`
- L63 _protected prototype_ `virtual void OnAssetReferenceAdded(TScriptInterface<IMetaSoundDocumentInterface> DocInterface) override;`
- L64 _protected prototype_ `virtual void OnRemovingAssetReference(TScriptInterface<IMetaSoundDocumentInterface> DocInterface) override;`

#### class `UMetaSoundSourceBuilder`  
`class UMetaSoundSourceBuilder : public UMetaSoundBuilderBase`  
_L71-160_
- reflection: `UCLASS(MinimalAPI, Transient, BlueprintType, meta = (DisplayName = "MetaSound Source Builder"))`
- inherits: `UMetaSoundBuilderBase`
- desc: Builder in charge of building a MetaSound Source
- L77 _public prototype_ `void Audition(UObject* Parent, UAudioComponent* AudioComponent, FOnCreateAuditionGeneratorHandleDelegate OnCreateGenerator, bool bLiveUpdatesEnabled = false);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (WorldContext = "Parent", AdvancedDisplay = "2"))`
- L81 _public prototype_ `bool GetLiveUpdatesEnabled() const;` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Returns whether or not live updates are both globally enabled (via cvar) and are enabled on this builder's last built sound, which may or may not still be playing.
- L85 _public prototype_ `void SetBlockRateOverride(float BlockRate);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Sets the MetaSound's BlockRate override
- L89 _public prototype_ `void SetFormat(EMetaSoundOutputAudioFormat OutputFormat, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Sets the output audio format of the source
- L93 _public prototype_ `void SetSampleRateOverride(int32 SampleRate);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Sets the MetaSound's SampleRate override
- L95 _public prototype_ `const Metasound::Engine::FOutputAudioFormatInfoPair* FindOutputAudioFormatInfo() const;`
- L97 _public prototype_ `virtual TScriptInterface<IMetaSoundDocumentInterface> BuildNewMetaSound(FName NameBase) const override;`
- L98 _public prototype_ `virtual const UClass& GetBaseMetaSoundUClass() const override;`
- L102 _public prototype_ `void SetPlatformBlockRateOverride(const FPerPlatformFloat& PlatformFloat);` — Sets the MetaSound's BlockRate override (editor only, to allow setting per-platform values)
- L105 _public prototype_ `void SetPlatformSampleRateOverride(const FPerPlatformInt& PlatformInt);` — Sets the MetaSound's BlockRate override (editor only, to allow setting per-platform values)
- L110 _public prototype_ `void SetQuality(FName Quality);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Sets the MetaSound's Quality level
- L113 _protected prototype_ `virtual void BuildAndOverwriteMetaSoundInternal(TScriptInterface<IMetaSoundDocumentInterface> ExistingMetaSound, bool bForceUniqueClassName) const override;`
- L114 _protected prototype_ `virtual void InitDelegates(Metasound::Frontend::FDocumentModifyDelegates& OutDocumentDelegates) override;`
- L115 _protected prototype_ `virtual void OnAssetReferenceAdded(TScriptInterface<IMetaSoundDocumentInterface> DocInterface) override;`
- L116 _protected prototype_ `virtual void OnRemovingAssetReference(TScriptInterface<IMetaSoundDocumentInterface> DocInterface) override;`
- L119 _private prototype_ `const FMetasoundFrontendGraph& GetConstTargetPageGraphChecked() const;`
- L121 _private prototype_ `UMetaSoundSource& GetMetaSoundSource() const;`
- L123 _private prototype_ `void InitTargetPageDelegates(Metasound::Frontend::FDocumentModifyDelegates& OutDocumentDelegates);`
- L125 _private prototype_ `void OnDocumentTemplateChanged(const Metasound::Frontend::FDocumentTemplateChangedArgs& Args) const;`
- L126 _private prototype_ `void OnEdgeAdded(int32 EdgeIndex) const;`
- L127 _private prototype_ `void OnInputAdded(int32 InputIndex);`
- L128 _private prototype_ `void OnInputDataTypeChanged(int32 InputIndex);`
- L129 _private prototype_ `void OnInputDefaultChanged(const Metasound::Frontend::FDocumentArrayPagedInputArgs& Args) const;`
- L131 _private prototype_ `void OnInputNameChanged(FName OldName, FName NewName);`
- L132 _private prototype_ `void OnLiveComponentFinished(UAudioComponent* AudioComponent);`
- L133 _private prototype_ `void OnNodeAdded(int32 NodeIndex) const;`
- L134 _private prototype_ `void OnNodeConfigurationUpdated(int32 NodeIndex) const;`
- L135 _private prototype_ `void OnNodeInputLiteralSet(int32 NodeIndex, int32 VertexIndex, int32 LiteralIndex) const;`
- L136 _private prototype_ `void OnOutputAdded(int32 OutputIndex) const;`
- L137 _private prototype_ `void OnPageAdded(const Metasound::Frontend::FDocumentMutatePageArgs& InArgs);`
- L138 _private prototype_ `void OnRemoveSwappingEdge(int32 SwapIndex, int32 LastIndex) const;`
- L139 _private prototype_ `void OnRemovingInput(int32 InputIndex);`
- L140 _private prototype_ `void OnRemoveSwappingNode(int32 SwapIndex, int32 LastIndex) const;`
- L141 _private prototype_ `void OnRemovingNodeInputLiteral(int32 NodeIndex, int32 VertexIndex, int32 LiteralIndex) const;`
- L142 _private prototype_ `void OnRemovingOutput(int32 OutputIndex) const;`
- L143 _private prototype_ `void OnRemovingPage(const Metasound::Frontend::FDocumentMutatePageArgs& InArgs);`
- L145 _private prototype_ `bool AddEdgeToTransactor(const FMetasoundFrontendEdge& NewEdge, Metasound::DynamicGraph::FDynamicOperatorTransactor& Transactor) const;`
- L146 _private prototype_ `bool AddNodeInputLiteralToTransactor( const FMetasoundFrontendNode& Node, const FMetasoundFrontendVertex& Input, const FMetasoundFrontendLiteral& InputDefault, Metasound::DynamicGraph::FDynamicOperatorTransactor& Transactor) const;`
- L152 _private typedef_ `using FAuditionableTransaction = TFunctionRef<bool(Metasound::DynamicGraph::FDynamicOperatorTransactor&)>;`
- L153 _private prototype_ `bool ExecuteAuditionableTransaction(FAuditionableTransaction Transaction) const;`
- L155 _private member_ `TArray<uint64> LiveComponentIDs;`
- L156 _private member_ `FDelegateHandle LiveComponentHandle;`
- L157 _private member_ `FGuid TargetPageID = Metasound::Frontend::DefaultPageID;`

#### class `UMetaSoundBuilderSubsystem`  
`class UMetaSoundBuilderSubsystem : public UEngineSubsystem`  
_L164-295_
- reflection: `UCLASS(MinimalAPI, meta = (DisplayName = "MetaSound Builder Subsystem"))`
- inherits: `UEngineSubsystem`
- desc: The subsystem in charge of tracking MetaSound builders
- L170 _private member_ `TMap<FName, TObjectPtr<UMetaSoundBuilderBase>> NamedBuilders;` — `UPROPERTY()`
- L173 _public prototype_ `static UMetaSoundBuilderSubsystem* Get();`
- L174 _public prototype_ `static UMetaSoundBuilderSubsystem& GetChecked();`
- L175 _public prototype_ `static const UMetaSoundBuilderSubsystem* GetConst();`
- L176 _public prototype_ `static const UMetaSoundBuilderSubsystem& GetConstChecked();`
- L179 _public prototype_ `UPARAM(DisplayName = "Patch Builder") UMetaSoundPatchBuilder* CreatePatchBuilder(FName BuilderName, EMetaSoundBuilderResult` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))`
- L182 _public prototype_ `UPARAM(DisplayName = "Source Builder") UMetaSoundSourceBuilder* CreateSourceBuilder( FName BuilderName, FMetaSoundBuilderNodeOutputHandle& OnPlayNodeOutput, FMetaSoundBuilderNodeInputHandle& OnFinishedNodeInput, TArray<FMetaSoundBuilderNodeInputHandle>& AudioOutNodeInputs, EMetaSoundBuilderResult& OutResult, EMetaSoundOutputAudioFormat OutputFormat = EMetaSoundOutputAudioFormat::Mono, bool bIsOneShot = true);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))`
- L193 _public prototype_ `UPARAM(DisplayName = "Patch Preset Builder") UMetaSoundPatchBuilder* CreatePatchPresetBuilder(FName BuilderName, UPARAM(DisplayName = "Reference Patch") const TScriptInterface<IMetaSoundDocumentInterface>& ReferencedPatchClass, E` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Creates a builder that acts on a generated, transient preset MetaSound UObject. Fails if Referenced MetaSound is not a UMetaSoundPatch.
- L195 _public prototype_ `UMetaSoundBuilderBase& CreatePresetBuilder(FName BuilderName, const TScriptInterface<IMetaSoundDocumentInterface>& ReferencedMetaSound, EMetaSoundBuilderResult& OutResult);`
- L199 _public prototype_ `UPARAM(DisplayName = "Source Preset Builder") UMetaSoundSourceBuilder* CreateSourcePresetBuilder(FName BuilderName, UPARAM(DisplayName = "Reference Source") const TScriptInterface<IMetaSoundDocumentInterface>& ReferencedSourceClass,` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (ExpandEnumAsExecs = "OutResult"))` — Creates a builder that acts on a generated, transient preset MetaSound UObject. Fails if Referenced MetaSound is not a UMetaSoundSource.
- L202 _public prototype_ `UPARAM(DisplayName = "Bool Literal") FMetasoundFrontendLiteral CreateBoolMetaSoundLiteral(bool Value, FName` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Create MetaSound Bool Literal"))`
- L205 _public prototype_ `UPARAM(DisplayName = "Bool Array Literal") FMetasoundFrontendLiteral CreateBoolArrayMetaSoundLiteral(const TArray<bool>& Value,` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Create MetaSound Bool Array Literal"))`
- L208 _public prototype_ `UPARAM(DisplayName = "Float Literal") FMetasoundFrontendLiteral CreateFloatMetaSoundLiteral(float Value, FNam` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Create MetaSound Float Literal"))`
- L211 _public prototype_ `UPARAM(DisplayName = "Float Array Literal") FMetasoundFrontendLiteral CreateFloatArrayMetaSoundLiteral(const TArray<float>& Value` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Create MetaSound Float Array Literal"))`
- L214 _public prototype_ `UPARAM(DisplayName = "Int32 Literal") FMetasoundFrontendLiteral CreateIntMetaSoundLiteral(int32 Value, FNam` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Create MetaSound Int Literal"))`
- L217 _public prototype_ `UPARAM(DisplayName = "Int32 Array Literal") FMetasoundFrontendLiteral CreateIntArrayMetaSoundLiteral(const TArray<int32>& Value` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Create MetaSound Int Array Literal"))`
- L220 _public prototype_ `UPARAM(DisplayName = "Object Literal") FMetasoundFrontendLiteral CreateObjectMetaSoundLiteral(UO` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Create MetaSound Object Literal"))`
- L223 _public prototype_ `UPARAM(DisplayName = "Object Array Literal") FMetasoundFrontendLiteral CreateObjectArrayMetaSoundLiteral(const TArra` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Create MetaSound Object Array Literal"))`
- L226 _public prototype_ `UPARAM(DisplayName = "String Literal") FMetasoundFrontendLiteral CreateStringMetaSoundLiteral(const FString& Value, FNa` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Create MetaSound String Literal"))`
- L229 _public prototype_ `UPARAM(DisplayName = "String Array Literal") FMetasoundFrontendLiteral CreateStringArrayMetaSoundLiteral(const TArray<FString>& Valu` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Create MetaSound String Array Literal"))`
- L232 _public prototype_ `UPARAM(DisplayName = "Param Literal") FMetasoundFrontendLiteral CreateMetaSoundLiteralFromParam(const FAudioParam` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Create MetaSound Literal From AudioParameter"))`
- L236 _public prototype_ `UPARAM(DisplayName = "Builder") UMetaSoundBuilderBase* FindBuilder(FName Builde` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Find Builder By Name"))` — Returns the builder manually registered with the MetaSound Builder Subsystem with the provided custom name (if previously registered)
- L240 _public prototype_ `UPARAM(DisplayName = "Builder") UMetaSoundBuilderBase* FindBuilderOfDocument(TScriptInterface<const IMetaSoundDocumentInterface> InMetaSound)` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Find Builder By MetaSound"))` — Returns the builder associated with the given MetaSound (if one exists, transient or asset).
- L247 _public prototype_ `UPARAM(DisplayName = "Builder") UMetaSoundBuilderBase* FindParentBuilderOfPreset(TScriptInterface<const IMetaSoundDocumentInterface> InMetaSoundPreset, bool bFollowPresetChain =` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder", meta = (DisplayName = "Find Parent Builder of MetaSound Preset"))` — Returns the builder associated with the given MetaSound preset's parent. If bFollowPresetChain is true, continues traversing up the preset chain to return the highest non-preset ancestor. Returns nullptr if the given MetaSound is not a preset, or if the parent builder is not yet registered.
- L251 _public prototype_ `UPARAM(DisplayName = "Patch Builder") UMetaSoundPatchBuilder* FindPatchBuilder(FName` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Returns the patch builder manually registered with the MetaSound Builder Subsystem with the provided custom name (if previously registered)
- L255 _public prototype_ `UPARAM(DisplayName = "Source Builder") UMetaSoundSourceBuilder* FindSourceBuilder(FName` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Returns the source builder manually registered with the MetaSound Builder Subsystem with the provided custom name (if previously registered)
- L258 _public prototype_ `UPARAM(DisplayName = "Is Registered") bool IsInterfaceRegistered(FName InInterfac` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")`
- L262 _public function_ `void PostBuilderAssetTransaction(const FMetasoundFrontendClassName& InClassName)` — `UE_DEPRECATED(5.5, "No longer required as reload is now just directly called on a given builder.")`
- L267 _public prototype_ `void RegisterBuilder(FName BuilderName, UMetaSoundBuilderBase* Builder);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Adds builder to subsystem's registry to make it persistent and easily accessible by multiple systems or Blueprints
- L271 _public prototype_ `void RegisterPatchBuilder(FName BuilderName, UMetaSoundPatchBuilder* Builder);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Adds builder to subsystem's registry to make it persistent and easily accessible by multiple systems or Blueprints
- L275 _public prototype_ `void RegisterSourceBuilder(FName BuilderName, UMetaSoundSourceBuilder* Builder);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")` — Adds builder to subsystem's registry to make it persistent and easily accessible by multiple systems or Blueprints
- L282 _public prototype_ `UPARAM(DisplayName = "TargetPageChanged") bool SetTargetPage` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Pages")` — Sets the targeted page for all MetaSound graph & input default to resolve against. If target page is not implemented (or cooked in a runtime build) for the active platform, uses order of cooked pages(see 'Page Settings' for order) falling back to lower index - ordered page implemented in MetaSound asset. If no fallback is found, uses default graph/input default.
- L285 _public prototype_ `UPARAM(DisplayName = "Unregistered") bool UnregisterBuilder(FName B` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")`
- L288 _public prototype_ `UPARAM(DisplayName = "Unregistered") bool UnregisterPatchBuilder(FName B` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")`
- L291 _public prototype_ `UPARAM(DisplayName = "Unregistered") bool UnregisterSourceBuilder(FName B` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Builder")`

#### Free symbols / members of external scopes

- L24 _macro_ `#define UE_API METASOUNDENGINE_API`
- L41 _namespace_ `namespace Metasound`
- L41 _namespace_ `namespace Engine` (scope `Metasound`)
- L49 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCreateAuditionGeneratorHandleDelegate, UMetasoundGeneratorHandle*, GeneratorHandle);`
- L49 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCreateAuditionGeneratorHandleDelegate, UMetasoundGeneratorHandle*, GeneratorHandle);`

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundChannelAgnosticAutoFormat.h` (Public)


#### class `Metasound::FChannelAgnosticAutoFormatHelper`  
`class FChannelAgnosticAutoFormatHelper`  
_L14-30_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METASOUNDENGINE_API`
- L12 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundDocumentBuilderRegistry.h` (Public)


#### class `Metasound::Engine::FDocumentBuilderRegistry`  
`class FDocumentBuilderRegistry : public Frontend::IDocumentBuilderRegistry`  
_L21-202_
- inherits: `Frontend::IDocumentBuilderRegistry`
- L23 _private member_ `mutable TMultiMap<FMetasoundFrontendClassName, TWeakObjectPtr<UMetaSoundBuilderBase>> Builders;`
- L26 _private member_ `mutable FCriticalSection BuildersCriticalSection;` — Critical section primarily for allowing builder collection mutation during async loading of MetaSound assets.
- L29 _public prototype_ `FDocumentBuilderRegistry() = default;`
- L30 _public prototype_ `virtual ~FDocumentBuilderRegistry();`
- L32 _public function_ `static FDocumentBuilderRegistry& GetChecked()`
- L43 _public function_ `template <typename BuilderClass> BuilderClass& CreateTransientBuilder(FName BuilderName = FName())`
- L69 _public function_ `template <typename BuilderClass = UMetaSoundBuilderBase> BuilderClass& FindOrBeginBuilding(UObject& InMetaSoundObject, bool bIsTransacting = false) const` — Find or begin building a MetaSound asset.  Optionally, provide whether or not the builder is being accessed during a transaction. If false, enforces MetaSound being built is an asset.  If true, does not enforce (transactions may result in assets being moved and becoming transient wherein the builder can and should be valid to act on the transient UObject in these rare cases).
- L118 _public prototype_ `UE_DEPRECATED(5.7, "Use Metasound::Frontend::StripUnusedPages(...) instead") virtual bool CookPages(FName PlatformName, FMeta` — Given the provided builder, removes paged data within the associated document for a cooked build. This function removes graphs and input defaults which are not to ever be used by a given cook platform, allowing users to optimize away data and scale the amount of memory required for initial load of input UObjects and graph topology, which can also positively effect runtime performance as well, etc. Returns true if builder modified the document, false if not.
- L119 _public prototype_ `virtual FMetaSoundFrontendDocumentBuilder& FindOrBeginBuilding(TScriptInterface<IMetaSoundDocumentInterface> MetaSound) override;` — `UE_DEPRECATED(5.7, "Use Metasound::Frontend::StripUnusedPages(...) instead")` — Given the provided builder, removes paged data within the associated document for a cooked build. This function removes graphs and input defaults which are not to ever be used by a given cook platform, allowing users to optimize away data and scale the amount of memory required for initial load of input UObjects and graph topology, which can also positively effect runtime performance as well, etc. Returns true if builder modified the document, false if not.
- L122 _public prototype_ `virtual FMetaSoundFrontendDocumentBuilder* FindBuilder(TScriptInterface<IMetaSoundDocumentInterface> MetaSound) const override;`
- L123 _public prototype_ `virtual FMetaSoundFrontendDocumentBuilder* FindBuilder(const FMetasoundFrontendClassName& InClassName, const FTopLevelAssetPath& AssetPath) const override;`
- L125 _public prototype_ `virtual TArray<FMetaSoundFrontendDocumentBuilder*> FindBuilders(const FMetasoundFrontendClassName& ClassName) const override;`
- L127 _public prototype_ `virtual FMetaSoundFrontendDocumentBuilder* FindOutermostBuilder(const UObject& InSubObject) const override;`
- L129 _public prototype_ `virtual bool FinishBuilding(const FMetasoundFrontendClassName& InClassName, bool bForceUnregisterNodeClass = false) const override;`
- L130 _public prototype_ `virtual bool FinishBuilding(const FMetasoundFrontendClassName& InClassName, const FTopLevelAssetPath& AssetPath, bool bForceUnregisterNodeClass = false) const override;`
- L133 _public prototype_ `UMetaSoundBuilderBase* FindBuilderObject(TScriptInterface<const IMetaSoundDocumentInterface> MetaSound) const;` — Returns the builder object associated with the given MetaSound asset if one is registered and active.
- L139 _public prototype_ `UMetaSoundBuilderBase* FindBuilderObject(const FMetasoundFrontendClassName& InClassName, const FTopLevelAssetPath& AssetPath) const;` — Returns the builder object associated with the given ClassName if one is registered and active. Optionally, if provided the AssetPath and there is a conflict (i.e. more than one asset is registered with a given ClassName), will return the one with the provided AssetPath.  Otherwise, will arbitrarily return one.
- L142 _public prototype_ `TArray<UMetaSoundBuilderBase*> FindBuilderObjects(const FMetasoundFrontendClassName& InClassName) const;` — Returns all builder objects registered and active associated with the given ClassName.
- L146 _public prototype_ `UE_DEPRECATED(5.7, "Use UMetaSoundSettings::GetOnResolveAuditionPageDelegate() instead.`
- L151 _public prototype_ `UE_DEPRECATED(5.7, "This is no longer supported") FOnResolvePage& GetOnResolvePro`
- L154 _public prototype_ `bool ReloadBuilder(const FMetasoundFrontendClassName& InClassName) const override;`
- L157 _public prototype_ `UE_DEPRECATED(5.7, "This is no longer supported.") virtual FGuid ResolveTargetPageID(const FMetasoundFrontendGraphClass& I` — Given the provided document and its respective pages, returns the PageID to be used for runtime IGraph and proxy generation.
- L158 _public prototype_ `UE_DEPRECATED(5.7, "This is no longer supported.") virtual FGuid ResolveTargetPageID(const FMetasoundFrontendClassInput& I` — `UE_DEPRECATED(5.7, "This is no longer supported.")` — Given the provided document and its respective pages, returns the PageID to be used for runtime IGraph and proxy generation.
- L159 _public prototype_ `UE_DEPRECATED(5.7, "This is no longer supported.") virtual FGuid ResolveTargetPageID(const TArray<FMetasoundFrontendClassInputDefault` — `UE_DEPRECATED(5.7, "This is no longer supported.")` — `UE_DEPRECATED(5.7, "This is no longer supported.")` — Given the provided document and its respective pages, returns the PageID to be used for runtime IGraph and proxy generation.
- L161 _public prototype_ `UE_DEPRECATED(5.7, "Retrieve page order from UMetaSoundSettings.") FGuid ResolveTargetPageID(c`
- L164 _public prototype_ `virtual TArrayView<const FGuid> GetPageOrder() const override;` — `UE_DEPRECATED(5.7, "This method exist only to supported deprecated functionality in FrontendNodeControllers and should not be in any new code.")`
- L168 _public prototype_ `virtual TArray<FGuid> GetCookedTargetPages(FName InPlatformName) const override;` — `UE_DEPRECATED(5.7, "This is only used to support existing deprecated functionality in FMetasoundAssetBase cooking and should not be used in any new code.")`
- L171 _public prototype_ `virtual TArray<FGuid> GetCookedPageOrder(FName InPlatformName) const override;` — `UE_DEPRECATED(5.7, "This is only used to support existing deprecated functionality in FMetasoundAssetBase cooking and should not be used in any new code.")`
- L174 _public prototype_ `void SetEventLogVerbosity(ELogEvent Event, ELogVerbosity::Type Verbosity);`
- L178 _private prototype_ `void WaitUntilVersioningComplete(UObject& InMetaSoundObject) const;`
- L181 _private prototype_ `void AddBuilderInternal(const FMetasoundFrontendClassName& InClassName, UMetaSoundBuilderBase* NewBuilder) const;`
- L182 _private prototype_ `bool CanPostEventLog(ELogEvent Event, ELogVerbosity::Type Verbosity) const;`
- L183 _private prototype_ `void FinishBuildingInternal(UMetaSoundBuilderBase& Builder, bool bForceUnregisterNodeClass) const;`
- L184 _private prototype_ `FGuid ResolveTargetPageIDInternal(const UMetaSoundSettings& Settings, const TArray<FGuid>& PageIdsToResolve, const FGuid& TargetPageID, FName PlatformName) const;`
- L188 _private member_ `FOnResolveEditorPage OnResolveAuditionPage;`
- L193 _private member_ `FOnResolvePage OnResolveProjectPage;`
- L198 _private member_ `mutable TArray<FGuid> TargetPageResolveScratch;` — Reuseable scratch array of pages to resolve, which is used to optimize/reduce number of allocations required when resolving document.
- L199 _private member_ `mutable FCriticalSection TargetPageResolveScratchCritSec;`
- L201 _private member_ `TSortedMap<ELogEvent, ELogVerbosity::Type> EventLogVerbosity;`

#### enum `Metasound::Engine::FDocumentBuilderRegistry::ELogEvent`  
`enum class ELogEvent : uint8`  
_L37-40_
- L39 _public enumerator_ `DuplicateEntries`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API METASOUNDENGINE_API`
- L19 _namespace_ `namespace Metasound`
- L19 _namespace_ `namespace Engine` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundEngineEnvironment.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundEngineNodesNames.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Metasound`
- L9 _namespace_ `namespace EngineNodes` (scope `Metasound`)
- L11 _externvar_ `extern const FName Namespace;` (scope `Metasound::EngineNodes`)
- L13 _externvar_ `extern const FName MonoVariant;` (scope `Metasound::EngineNodes`)
- L14 _externvar_ `extern const FName StereoVariant;` (scope `Metasound::EngineNodes`)
- L15 _externvar_ `extern const FName QuadVariant;` (scope `Metasound::EngineNodes`)
- L16 _externvar_ `extern const FName FiveDotOneVariant;` (scope `Metasound::EngineNodes`)
- L17 _externvar_ `extern const FName SevenDotOneVariant;` (scope `Metasound::EngineNodes`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundFrontendLiteralBlueprintAccess.h` (Public)


#### class `UMetasoundFrontendLiteralBlueprintAccess`  
`class UMetasoundFrontendLiteralBlueprintAccess : public UBlueprintFunctionLibrary`  
_L15-203_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint support for FMetasoundFrontendLiteral
- L20 _private prototype_ `static FString Conv_MetaSoundLiteralToString(const FMetasoundFrontendLiteral& Literal);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "To String (MetaSound Literal)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|String")`
- L23 _private prototype_ `static UPARAM(DisplayName = "Type") EMetasoundFrontendLiteralType GetType(const FMetasoundFrontendLiteral& Liter` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound", meta = (DisplayName = "Get MetaSound Literal Type"))`
- L26 _private prototype_ `static bool EqualEqual_MetaSoundLiteral(const FMetasoundFrontendLiteral& LiteralA, const FMetasoundFrontendLiteral& LiteralB);` — `UFUNCTION(BlueprintPure, meta=(DisplayName = "Equal (MetaSound Literal)", CompactNodeTitle = "==", Keywords = "== equal"), Category="Audio|MetaSound")`
- L32 _private prototype_ `static UPARAM(DisplayName = "Bool Literal") FMetasoundFrontendLiteral CreateBoolMetaSoundLiteral(` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Create Literal", meta = (DisplayName = "Create MetaSound Literal from Boolean"))` — Creates a MetaSound Literal using the given boolean value.
- L36 _private prototype_ `static UPARAM(DisplayName = "Bool Array Literal") FMetasoundFrontendLiteral CreateBoolArrayMetaSoundLiteral(const TAr` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Create Literal", meta = (DisplayName = "Create MetaSound Literal from Boolean Array"))` — Creates a MetaSound Literal using the given boolean array.
- L40 _private prototype_ `static UPARAM(DisplayName = "Float Literal") FMetasoundFrontendLiteral CreateFloatMetaSoundLiteral(` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Create Literal", meta = (DisplayName = "Create MetaSound Literal from Float"))` — Creates a MetaSound Literal using the given float value.
- L44 _private prototype_ `static UPARAM(DisplayName = "Float Array Literal") FMetasoundFrontendLiteral CreateFloatArrayMetaSoundLiteral(const TAr` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Create Literal", meta = (DisplayName = "Create MetaSound Literal from Float Array"))` — Creates a MetaSound Literal using the given float array.
- L48 _private prototype_ `static UPARAM(DisplayName = "Int32 Literal") FMetasoundFrontendLiteral CreateIntMetaSoundLiteral(` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Create Literal", meta = (DisplayName = "Create MetaSound Literal from Integer"))` — Creates a MetaSound Literal using the given integer value.
- L52 _private prototype_ `static UPARAM(DisplayName = "Int32 Array Literal") FMetasoundFrontendLiteral CreateIntArrayMetaSoundLiteral(const TAr` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Create Literal", meta = (DisplayName = "Create MetaSound Literal from Integer Array"))` — Creates a MetaSound Literal using the given integer array.
- L56 _private prototype_ `static UPARAM(DisplayName = "Object Literal") FMetasoundFrontendLiteral CreateObjectMetaSoundLiteral(UO` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Create Literal", meta = (DisplayName = "Create MetaSound Literal from Object"))` — Creates a MetaSound Literal using the given object.
- L60 _private prototype_ `static UPARAM(DisplayName = "Object Array Literal") FMetasoundFrontendLiteral CreateObjectArrayMetaSoundLiteral(const TArra` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Create Literal", meta = (DisplayName = "Create MetaSound Literal from Object Array"))` — Creates a MetaSound Literal using the given object array.
- L64 _private prototype_ `static UPARAM(DisplayName = "String Literal") FMetasoundFrontendLiteral CreateStringMetaSoundLiteral(const FS` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Create Literal", meta = (DisplayName = "Create MetaSound Literal from String"))` — Creates a MetaSound Literal using the given string.
- L68 _private prototype_ `static UPARAM(DisplayName = "String Array Literal") FMetasoundFrontendLiteral CreateStringArrayMetaSoundLiteral(const TArr` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Create Literal", meta = (DisplayName = "Create MetaSound Literal from String Array"))` — Creates a MetaSound Literal using the given string array.
- L72 _private prototype_ `static UPARAM(DisplayName = "Param Literal") FMetasoundFrontendLiteral CreateMetaSoundLiteralFromParam(const FAudioParam` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Create Literal", meta = (DisplayName = "Create MetaSound Literal from Audio Parameter"))` — Creates a MetaSound Literal using the given audio parameter.
- L78 _private prototype_ `static FMetasoundFrontendLiteral CreateMetaSoundLiteralFromBoolean(const bool InBoolean);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Create Literal", DisplayName = "Create MetaSound Literal from Boolean (Pure)")` — Creates a MetaSound Literal using the given boolean value.
- L82 _private prototype_ `static FMetasoundFrontendLiteral CreateMetaSoundLiteralFromBooleanArray(const TArray<bool>& InBooleanArray);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Create Literal", DisplayName = "Create MetaSound Literal from Boolean Array (Pure)")` — Creates a MetaSound Literal using the given boolean array.
- L86 _private prototype_ `static FMetasoundFrontendLiteral CreateMetaSoundLiteralFromFloat(const float InFloat);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Create Literal", DisplayName = "Create MetaSound Literal from Float (Pure)")` — Creates a MetaSound Literal using the given float value.
- L90 _private prototype_ `static FMetasoundFrontendLiteral CreateMetaSoundLiteralFromFloatArray(const TArray<float>& InFloatArray);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Create Literal", DisplayName = "Create MetaSound Literal from Float Array (Pure)")` — Creates a MetaSound Literal using the given float array.
- L94 _private prototype_ `static FMetasoundFrontendLiteral CreateMetaSoundLiteralFromInteger(const int32 InInteger);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Create Literal", DisplayName = "Create MetaSound Literal from Integer (Pure)")` — Creates a MetaSound Literal using the given integer value.
- L98 _private prototype_ `static FMetasoundFrontendLiteral CreateMetaSoundLiteralFromIntegerArray(const TArray<int32>& InIntegerArray);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Create Literal", DisplayName = "Create MetaSound Literal from Integer Array (Pure)")` — Creates a MetaSound Literal using the given integer array.
- L102 _private prototype_ `static FMetasoundFrontendLiteral CreateMetaSoundLiteralFromObject(UObject* InObject);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Create Literal", DisplayName = "Create MetaSound Literal from Object (Pure)")` — Creates a MetaSound Literal using the given object.
- L106 _private prototype_ `static FMetasoundFrontendLiteral CreateMetaSoundLiteralFromObjectArray(const TArray<UObject*>& InObjectArray);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Create Literal", DisplayName = "Create MetaSound Literal from Object Array (Pure)")` — Creates a MetaSound Literal using the given object array.
- L110 _private prototype_ `static FMetasoundFrontendLiteral CreateMetaSoundLiteralFromString(const FString& InString);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Create Literal", DisplayName = "Create MetaSound Literal from String (Pure)")` — Creates a MetaSound Literal using the given string.
- L114 _private prototype_ `static FMetasoundFrontendLiteral CreateMetaSoundLiteralFromStringArray(const TArray<FString>& InStringArray);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Create Literal", DisplayName = "Create MetaSound Literal from String Array (Pure)")` — Creates a MetaSound Literal using the given string array.
- L118 _private prototype_ `static FMetasoundFrontendLiteral CreateMetaSoundLiteralFromAudioParameter(const FAudioParameter& InAudioParameter);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Create Literal", DisplayName = "Create MetaSound Literal from Audio Parameter (Pure)")` — Creates a MetaSound Literal using the given audio parameter.
- L124 _private prototype_ `static bool GetBoolValueFromLiteral(const FMetasoundFrontendLiteral& Literal, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Bool", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns the value of the given MetaSound Literal as a bool. Has separate execution outputs for success and failure.
- L128 _private prototype_ `static TArray<bool> GetBoolArrayValueFromLiteral(const FMetasoundFrontendLiteral& Literal, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Bool Array", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns the value of the given MetaSound Literal as a bool array. Has separate execution outputs for success and failure.
- L132 _private prototype_ `static float GetFloatValueFromLiteral(const FMetasoundFrontendLiteral& Literal, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Float", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns the value of the given MetaSound Literal as a float. Has separate execution outputs for success and failure.
- L136 _private prototype_ `static TArray<float> GetFloatArrayValueFromLiteral(const FMetasoundFrontendLiteral& Literal, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Float Array", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns the value of the given MetaSound Literal as a float array. Has separate execution outputs for success and failure.
- L140 _private prototype_ `static int32 GetIntValueFromLiteral(const FMetasoundFrontendLiteral& Literal, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Integer", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns the value of the given MetaSound Literal as an integer. Has separate execution outputs for success and failure.
- L144 _private prototype_ `static TArray<int32> GetIntArrayValueFromLiteral(const FMetasoundFrontendLiteral& Literal, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Integer Array", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns the value of the given MetaSound Literal as an integer array. Has separate execution outputs for success and failure.
- L148 _private prototype_ `static UObject* GetObjectValueFromLiteral(const FMetasoundFrontendLiteral& Literal, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Object", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns the value of the given MetaSound Literal as an object. Has separate execution outputs for success and failure.
- L152 _private prototype_ `static TArray<UObject*> GetObjectArrayValueFromLiteral(const FMetasoundFrontendLiteral& Literal, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Object Array", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns the value of the given MetaSound Literal as an object array. Has separate execution outputs for success and failure.
- L156 _private prototype_ `static FString GetStringValueFromLiteral(const FMetasoundFrontendLiteral& Literal, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as String", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns the value of the given MetaSound Literal as a string. Has separate execution outputs for success and failure.
- L160 _private prototype_ `static TArray<FString> GetStringArrayValueFromLiteral(const FMetasoundFrontendLiteral& Literal, EMetaSoundBuilderResult& OutResult);` — `UFUNCTION(BlueprintCallable, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as String Array", meta = (ExpandEnumAsExecs = "OutResult"))` — Returns the value of the given MetaSound Literal as a string array. Has separate execution outputs for success and failure.
- L166 _private prototype_ `static bool GetMetaSoundLiteralAsBool(const FMetasoundFrontendLiteral& InLiteral);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Bool (Pure)")` — Returns the value of the given MetaSound Literal as a bool. Logs a warning if the value fails to be retrieved.
- L170 _private prototype_ `static TArray<bool> GetMetaSoundLiteralAsBoolArray(const FMetasoundFrontendLiteral& InLiteral);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Bool Array (Pure)")` — Returns the value of the given MetaSound Literal as a bool array. Logs a warning if the value fails to be retrieved.
- L174 _private prototype_ `static float GetMetaSoundLiteralAsFloat(const FMetasoundFrontendLiteral& InLiteral);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Float (Pure)")` — Returns the value of the given MetaSound Literal as a float. Logs a warning if the value fails to be retrieved.
- L178 _private prototype_ `static TArray<float> GetMetaSoundLiteralAsFloatArray(const FMetasoundFrontendLiteral& InLiteral);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Float Array (Pure)")` — Returns the value of the given MetaSound Literal as a float array. Logs a warning if the value fails to be retrieved.
- L182 _private prototype_ `static int32 GetMetaSoundLiteralAsInteger(const FMetasoundFrontendLiteral& InLiteral);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Integer (Pure)")` — Returns the value of the given MetaSound Literal as an integer. Logs a warning if the value fails to be retrieved.
- L186 _private prototype_ `static TArray<int32> GetMetaSoundLiteralAsIntegerArray(const FMetasoundFrontendLiteral& InLiteral);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Integer Array (Pure)")` — Returns the value of the given MetaSound Literal as an integer array. Logs a warning if the value fails to be retrieved.
- L190 _private prototype_ `static UObject* GetMetaSoundLiteralAsObject(const FMetasoundFrontendLiteral& InLiteral);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Object (Pure)")` — Returns the value of the given MetaSound Literal as an object. Logs a warning if the value fails to be retrieved.
- L194 _private prototype_ `static TArray<UObject*> GetMetaSoundLiteralAsObjectArray(const FMetasoundFrontendLiteral& InLiteral);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as Object Array (Pure)")` — Returns the value of the given MetaSound Literal as an object array. Logs a warning if the value fails to be retrieved.
- L198 _private prototype_ `static FString GetMetaSoundLiteralAsString(const FMetasoundFrontendLiteral& InLiteral);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as String (Pure)")` — Returns the value of the given MetaSound Literal as a string. Logs a warning if the value fails to be retrieved.
- L202 _private prototype_ `static TArray<FString> GetMetaSoundLiteralAsStringArray(const FMetasoundFrontendLiteral& InLiteral);` — `UFUNCTION(BlueprintPure, Category = "Audio|MetaSound|Get Literal As", DisplayName = "Get MetaSound Literal as String Array (Pure)")` — Returns the value of the given MetaSound Literal as a string array. Logs a warning if the value fails to be retrieved.

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundGeneratorHandle.h` (Public)


#### class `Metasound::FMetasoundGeneratorHandle`  
`class FMetasoundGeneratorHandle : public TSharedFromThis<FMetasoundGeneratorHandle>`  
_L40-413_
- inherits: `TSharedFromThis<FMetasoundGeneratorHandle>`
- desc: User-facing interface to a FMetasoundGenerator on a UAudioComponent.
- L50 _public prototype_ `explicit FMetasoundGeneratorHandle(FPrivateToken, TWeakObjectPtr<UAudioComponent>&& InAudioComponent);` — NOTE: This constructor is effectively private, but will work with TSharedPtr/TSharedFromThis. (see TIntrusiveReferenceController for explanation) Use FMetasoundGeneratorHandle::Create instead
- L58 _public prototype_ `static TSharedPtr<FMetasoundGeneratorHandle> Create(TWeakObjectPtr<UAudioComponent>&& InAudioComponent);` — Create a handle to a MetaSound generator on the given audio component @param InAudioComponent The audio component to attach to @return The generator handle, if successfully created
- L60 _public prototype_ `~FMetasoundGeneratorHandle();`
- L67 _public prototype_ `bool IsValid() const;` — Find out if this handle is still valid. @return Whether this handle is still valid
- L75 _public prototype_ `uint64 GetAudioComponentId() const;` — Get the id for the UAudioComponent associated with this handle. NOTE: Be sure to check IsValid() before expecting a valid return from this method. @returns The audio component's id, or INDEX_NONE if the component is no longer valid.
- L77 _public prototype_ `TSharedPtr<FMetasoundGenerator> GetGenerator() const;`
- L79 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnGeneratorSet, TWeakPtr<FMetasoundGenerator>&&);`
- L84 _public member_ `FOnGeneratorSet OnGeneratorSet;` — Fires on the game thread when a generator is set or unset on this handle.
- L86 _public prototype_ `DECLARE_DELEGATE(FOnGeneratorGraphSet);`
- L91 _public member_ `FOnGeneratorGraphSet OnGraphUpdated;` — Fires on the game thread when a graph is updated on the generator.
- L93 _public prototype_ `DECLARE_DELEGATE(FOnGeneratorIOUpdated);`
- L99 _public member_ `FOnGeneratorIOUpdated OnGeneratorIOUpdated;` — `UE_DEPRECATED(5.5, "Use OnGeneratorIOUpdatedWithChanges.")` — Fires on the game thread when the generator's graph inputs or outputs change.
- L101 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnGeneratorIOUpdatedWithChanges, const TArray<FVertexInterfaceChange>&);`
- L106 _public member_ `FOnGeneratorIOUpdatedWithChanges OnGeneratorIOUpdatedWithChanges;` — Fires on the game thread when the generator's graph inputs or outputs change, and includes a list of those changes.
- L114 _public prototype_ `void UpdateParameters(const UMetasoundParameterPack& ParameterPack);` — Update the current parameter state on this handle and enqueue the changes on the generator. @param ParameterPack The parameter pack to set, which will be merged with the current state. @return true if parameters were updated, false otherwise
- L125 _public prototype_ `bool WatchOutput( FName OutputName, const FOnMetasoundOutputValueChanged& OnOutputValueChanged, FName AnalyzerName = NAME_None, FName AnalyzerOutputName = NAME_None);` — Watch an output value. @param OutputName - The user-specified name of the output in the Metasound @param OnOutputValueChanged - The event to fire when the output's value changes @param AnalyzerName - (optional) The name of the analyzer to use on the output, defaults to a passthrough @param AnalyzerOutputName - (optional) The name of the output on the analyzer to watch, defaults to the passthrough output @returns true if the watch setup succeeded, false otherwise
- L131 _public prototype_ `bool WatchOutput( FName OutputName, const FOnMetasoundOutputValueChangedNative& OnOutputValueChanged, FName AnalyzerName = NAME_None, FName AnalyzerOutputName = NAME_None);`
- L146 _public prototype_ `bool UnwatchOutput( FName OutputName, const FOnMetasoundOutputValueChanged& OnOutputValueChanged, FName AnalyzerName = NAME_None, FName AnalyzerOutputName = NAME_None);` — Unwatch/Stop watching an output value @param OutputName - The user-specified name of the output in the Metasound @param OnOutputValueChanged - The event or handle previously watched @param AnalyzerName - (optional) The name of the analyzer to use on the output, defaults to a passthrough @param AnalyzerOutputName - (optional) The name of the output on the analyzer to watch, defaults to the passthrough output @returns true if the unwatch setup succeeded, false otherwise
- L152 _public prototype_ `bool UnwatchOutput( FName OutputName, const FOnMetasoundOutputValueChangedNative& OnOutputValueChanged, FName AnalyzerName = NAME_None, FName AnalyzerOutputName = NAME_None);`
- L158 _public prototype_ `bool UnwatchOutput( FName OutputName, const FDelegateHandle& OnOutputValueChanged, FName AnalyzerName = NAME_None, FName AnalyzerOutputName = NAME_None);`
- L164 _public prototype_ `bool TryCreateAnalyzerAddress( const FName OutputName, const FName AnalyzerName, const FName AnalyzerOutputName, Frontend::FAnalyzerAddress& OutAnalyzerAddress);`
- L174 _public function_ `void UpdateOutputWatchers() const` — `UE_DEPRECATED(5.5, "Directly calling UpdateOutputWatchers() is no longer necessary.")` — Update any watched outputs
- L183 _public prototype_ `static void RegisterPassthroughAnalyzerForType(FName TypeName, FName AnalyzerName, FName OutputName);` — Map a type name to a passthrough analyzer name to use as a default for UMetasoundOutputSubsystem::WatchOutput() @param TypeName - The type name returned from GetMetasoundDataTypeName() @param AnalyzerName - The name of the analyzer to use @param OutputName - The name of the output in the analyzer
- L190 _public prototype_ `void EnableRuntimeRenderTiming(bool Enable);` — Enable the profiling of the MetaSound render for this playing instance. You must call this before calling "GetRuntimeCPUCoreUtilization" (below) or you will just get 0.0 back for core utilization.
- L197 _public prototype_ `double GetCPUCoreUtilization() const;` — Get the CPU usage as "fraction of real time" used to render this metasound. NOTE: The MetasoundSource asset MUST have had its EnableRenderTiming function called before the metasound is started!
- L202 _public prototype_ `FString ToString() const;` — Returns a text representation of this generator handle, useful for logging
- L205 _private prototype_ `void SetGenerator(TWeakPtr<FMetasoundGenerator>&& InGenerator);`
- L207 _private prototype_ `void RegisterGeneratorEvents();`
- L209 _private prototype_ `void UnregisterGeneratorEvents() const;`
- L211 _private prototype_ `TWeakObjectPtr<UMetaSoundSource> GetMetaSoundSource() const;`
- L213 _private prototype_ `void SendParametersToGenerator() const;`
- L227 _private prototype_ `bool WatchOutputInternal( FName OutputName, const FWatchOutputUnifiedDelegate& OnOutputValueChanged, FName AnalyzerName = NAME_None, FName AnalyzerOutputName = NAME_None);`
- L233 _private prototype_ `bool UnwatchOutputInternal( FName OutputName, const FWatchOutputUnifiedDelegate& OnOutputValueChanged, FName AnalyzerName = NAME_None, FName AnalyzerOutputName = NAME_None);`
- L239 _private prototype_ `void UpdateOutputWatchersInternal();`
- L240 _private prototype_ `void FixUpOutputWatchers();`
- L242 _private prototype_ `void CreateOutputWatcher( const Frontend::FAnalyzerAddress& AnalyzerAddress, const FWatchOutputUnifiedDelegate& OnOutputValueChanged);`
- L246 _private prototype_ `void RemoveOutputWatcher( const Frontend::FAnalyzerAddress& AnalyzerAddress, const FWatchOutputUnifiedDelegate& OnOutputValueChanged);`
- L250 _private member_ `TWeakObjectPtr<UAudioComponent> AudioComponent;`
- L251 _private member_ `const uint64 AudioComponentId;`
- L256 _private prototype_ `void HandleGeneratorCreated(const FGeneratorInstanceInfo& GeneratorInfo);` — Delegate management
- L257 _private member_ `FDelegateHandle GeneratorCreatedDelegateHandle;`
- L259 _private prototype_ `void HandleGeneratorDestroyed(const FGeneratorInstanceInfo& GeneratorInfo);`
- L260 _private member_ `FDelegateHandle GeneratorDestroyedDelegateHandle;`
- L262 _private prototype_ `void HandleGeneratorGraphSet();`
- L263 _private member_ `FDelegateHandle GeneratorGraphSetDelegateHandle;`
- L265 _private prototype_ `void HandleGeneratorVertexInterfaceChanged(const TArray<FVertexInterfaceChange>& VertexInterfaceData);`
- L266 _private member_ `FDelegateHandle GeneratorVertexInterfaceChangedDelegateHandle;`
- L268 _private prototype_ `void HandleOutputChanged( FName AnalyzerName, FName OutputName, FName AnalyzerOutputName, TSharedPtr<IOutputStorage> OutputData);`
- L273 _private member_ `FDelegateHandle GeneratorOutputChangedDelegateHandle;`
- L275 _private member_ `TWeakPtr<FMetasoundGenerator> Generator;`
- L277 _private member_ `FSharedMetasoundParameterStoragePtr LatestParameterState;`
- L284 _private member_ `static TMap<FName, FPassthroughAnalyzerInfo> PassthroughAnalyzers;`
- L382 _private member_ `TMap<FOutputWatcherKey, FOutputWatcher> OutputWatchers;`
- L401 _private member_ `uint64 CurrentGeneratorInstanceID;`
- L403 _private member_ `TSpscQueue<FOutputPayload> ChangedOutputs;`
- L406 _private member_ `static constexpr int32 ChangedOutputsQueueMax = 1024;` — Keep ChangedOutputs from growing infinitely
- L407 _private member_ `std::atomic<int32> ChangedOutputsQueueCount{ 0 };`
- L408 _private member_ `std::atomic<bool> ChangedOutputsQueueShouldLogIfFull{ true };`
- L410 _private member_ `std::atomic_flag OutputWatcherUpdateScheduled = ATOMIC_FLAG_INIT;`
- L412 _private member_ `bool bRuntimeRenderTimingShouldBeEnabled{ false };`

#### struct `Metasound::FMetasoundGeneratorHandle::FPrivateToken`  
`struct FPrivateToken`  
_L42-42_
- L42 _public prototype_ `struct FPrivateToken`

#### struct `Metasound::FMetasoundGeneratorHandle::FWatchOutputUnifiedDelegate`  
`struct FWatchOutputUnifiedDelegate`  
_L215-225_
- L217 _public member_ `FOnMetasoundOutputValueChanged WatchDelegate;`
- L218 _public member_ `FOnMetasoundOutputValueChangedNative NativeWatchDelegate;`
- L219 _public member_ `FDelegateHandle NativeWatchDelegateHandle;`
- L221 _public function_ `FWatchOutputUnifiedDelegate()`
- L222 _public function_ `FWatchOutputUnifiedDelegate(const FOnMetasoundOutputValueChanged& Delegate) : WatchDelegate(Delegate)`
- L223 _public function_ `FWatchOutputUnifiedDelegate(const FOnMetasoundOutputValueChangedNative& Delegate) : NativeWatchDelegate(Delegate), NativeWatchDelegateHandle(Delegate.GetHandle())`
- L224 _public function_ `FWatchOutputUnifiedDelegate(const FDelegateHandle& DelegateHandle) : NativeWatchDelegateHandle(DelegateHandle)`

#### struct `Metasound::FMetasoundGeneratorHandle::FPassthroughAnalyzerInfo`  
`struct FPassthroughAnalyzerInfo`  
_L279-283_
- L281 _public member_ `FName AnalyzerName;`
- L282 _public member_ `FName OutputName;`

#### struct `Metasound::FMetasoundGeneratorHandle::FOutputWatcherKey`  
`struct FOutputWatcherKey`  
_L286-303_
- L288 _public member_ `FName OutputName;`
- L289 _public member_ `FName AnalyzerName;`
- L290 _public member_ `FName AnalyzerMemberName;`
- L292 _public function_ `bool operator==(const FOutputWatcherKey& Other) const`
- L299 _public function_ `bool operator!=(const FOutputWatcherKey& Other) const`

#### struct `Metasound::FMetasoundGeneratorHandle::FWatchOutputUnifiedMulticastDelegate`  
`struct FWatchOutputUnifiedMulticastDelegate`  
_L312-363_
- L314 _public member_ `FOnMetasoundOutputValueChangedMulticast WatchDelegates;`
- L315 _public member_ `FOnMetasoundOutputValueChangedNativeMulticast NativeWatchDelegates;`
- L317 _public function_ `void Add(const FWatchOutputUnifiedDelegate& Delegate)`
- L330 _public function_ `void Remove(const FWatchOutputUnifiedDelegate& Delegate)`
- L343 _public function_ `bool IsBound() const`
- L358 _public function_ `void Broadcast(FName OutputName, const FMetaSoundOutput& Output) const`

#### struct `Metasound::FMetasoundGeneratorHandle::FOutputWatcher`  
`struct FOutputWatcher`  
_L368-380_
- desc: Info about an output being watched by one or more listeners
- L370 _public member_ `Frontend::FAnalyzerAddress AnalyzerAddress;`
- L371 _public member_ `FWatchOutputUnifiedMulticastDelegate OnOutputValueChanged;`
- L373 _public function_ `FOutputWatcher( const Frontend::FAnalyzerAddress& InAnalyzerAddress, const FWatchOutputUnifiedDelegate& InOnOutputValueChanged) : AnalyzerAddress(InAnalyzerAddress)`

#### struct `Metasound::FMetasoundGeneratorHandle::FOutputPayload`  
`struct FOutputPayload`  
_L384-399_
- L386 _public member_ `FName AnalyzerName;`
- L387 _public member_ `FName OutputName;`
- L388 _public member_ `FMetaSoundOutput OutputValue;`
- L390 _public function_ `FOutputPayload( const FName InAnalyzerName, const FName InOutputName, const FName AnalyzerOutputName, TSharedPtr<IOutputStorage> OutputData) : AnalyzerName(InAnalyzerName) , OutputName(InOutputName) , OutputValue(AnalyzerOutputName, OutputData)`

#### class `UMetasoundGeneratorHandle`  
`class UMetasoundGeneratorHandle : public UObject`  
_L420-549_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Category = "MetaSound", meta = (DisplayName = "MetaSound Generator Handle"))`
- inherits: `UObject`
- desc: Blueprint-facing interface to a FMetasoundGenerator on a UAudioComponent.
- L426 _public prototype_ `static UMetasoundGeneratorHandle* CreateMetaSoundGeneratorHandle(UAudioComponent* OnComponent);` — `UFUNCTION(BlueprintCallable, Category="MetaSound")`
- L428 _public prototype_ `virtual void BeginDestroy() override;`
- L430 _public prototype_ `bool IsValid() const;`
- L438 _public prototype_ `uint64 GetAudioComponentId() const;` — Get the id for the UAudioComponent associated with this handle. NOTE: Be sure to check IsValid() before expecting a valid return from this method. @returns The audio component's id, or INDEX_NONE if the component is no longer valid.
- L447 _public prototype_ `bool ApplyParameterPack(UMetasoundParameterPack* Pack);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundParameterPack")` — Makes a copy of the supplied parameter pack and passes it to the MetaSoundGenerator for asynchronous processing. IT ALSO caches this copy so that if the AudioComponent is virtualized the parameter pack will be sent again when/if the AudioComponent is "unvirtualized".
- L456 _public prototype_ `TSharedPtr<Metasound::FMetasoundGenerator> GetGenerator() const;` — Get a shared pointer to the generator, if available. NOTE: while the shared pointer is safe to get from threads other than the audio render thread, not all methods on the generator are safe to use from other threads. Ensure you know what you're doing. @return A shared pointer to the generator, if available.
- L465 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAttached);` — UMetasoundGeneratorHandle shields its "clients" from "cross thread" issues related to callbacks coming in the audio control or rendering threads that game thread clients (e.g. blueprints) want to know about. That is why these next delegate definitions do not need to be the "TS" variants. Assignments to members of this type, and the broadcasts there to will all happen on the game thread. EVEN IF the instigator of those callbacks is on the audio render thread.
- L466 _public member_ `FOnAttached OnGeneratorHandleAttached;`
- L468 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnDetached);`
- L469 _public member_ `FOnDetached OnGeneratorHandleDetached;`
- L471 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSetGraph);`
- L472 _public prototype_ `FDelegateHandle AddGraphSetCallback(UMetasoundGeneratorHandle::FOnSetGraph::FDelegate&& Delegate);`
- L473 _public prototype_ `bool RemoveGraphSetCallback(const FDelegateHandle& Handle);`
- L475 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnIOUpdated) UE_DEPRECATED(5.5, "Use OnIOUpdatedWithChanges.") FOnIOUpdated OnIOUpdated;`
- L479 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIOUpdatedWithChanges, const TArray<Metasound::FVertexInterfaceChange>&) FOnIOUpdatedWithChanges OnIOUpdatedWithChanges;`
- L482 _public prototype_ `bool TryCreateAnalyzerAddress( const FName OutputName, const FName AnalyzerName, const FName AnalyzerOutputName, Metasound::Frontend::FAnalyzerAddress& OutAnalyzerAddress);`
- L498 _public prototype_ `bool WatchOutput( FName OutputName, const FOnMetasoundOutputValueChanged& OnOutputValueChanged, FName AnalyzerName = NAME_None, FName AnalyzerOutputName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput", meta=(AdvancedDisplay = "2"))` — Watch an output value. @param OutputName - The user-specified name of the output in the Metasound @param OnOutputValueChanged - The event to fire when the output's value changes @param AnalyzerName - (optional) The name of the analyzer to use on the output, defaults to a passthrough @param AnalyzerOutputName - (optional) The name of the output on the analyzer to watch, defaults to the passthrough output @returns true if the watch setup succeeded, false otherwise
- L504 _public prototype_ `bool WatchOutput( FName OutputName, const FOnMetasoundOutputValueChangedNative& OnOutputValueChanged, FName AnalyzerName = NAME_None, FName AnalyzerOutputName = NAME_None);`
- L517 _public prototype_ `static void RegisterPassthroughAnalyzerForType(FName TypeName, FName AnalyzerName, FName OutputName);` — Map a type name to a passthrough analyzer name to use as a default for UMetasoundOutputSubsystem::WatchOutput() @param TypeName - The type name returned from GetMetasoundDataTypeName() @param AnalyzerName - The name of the analyzer to use @param OutputName - The name of the output in the analyzer
- L524 _public prototype_ `void UpdateWatchers() const;` — `UE_DEPRECATED(5.5, "Directly calling UpdateWatchers() is no longer necessary.")` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")` — Update any watched outputs
- L532 _public prototype_ `void EnableRuntimeRenderTiming(bool Enable) const;` — `UFUNCTION(BlueprintCallable, Category="MetaSoundPerf")` — Enable the profiling of the MetaSound render for this playing instance. You must call this before calling "GetRuntimeCPUCoreUtilization" (below) or you will just get 0.0 back for core utilization.
- L540 _public prototype_ `double GetCPUCoreUtilization() const;` — `UFUNCTION(BlueprintCallable, Category="MetaSoundPerf")` — Get the CPU usage as "fraction of real time" used to render this metasound. NOTE: The MetasoundSource asset MUST have had its EnableRenderTiming function called before the metasound is started!
- L543 _private prototype_ `bool InitGeneratorHandle(TWeakObjectPtr<UAudioComponent>&& AudioComponent);`
- L545 _private member_ `TSharedPtr<Metasound::FMetasoundGeneratorHandle> GeneratorHandle;`
- L547 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSetGraphMulticast);`
- L548 _private member_ `FOnSetGraphMulticast OnGeneratorsGraphChanged;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API METASOUNDENGINE_API`
- L21 _namespace_ `namespace Metasound`
- L28 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMetasoundOutputValueChanged, FName, OutputName, const FMetaSoundOutput&, Output);`
- L28 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMetasoundOutputValueChanged, FName, OutputName, const FMetaSoundOutput&, Output);`
- L29 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnMetasoundOutputValueChangedNative, FName, const FMetaSoundOutput&);`
- L29 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnMetasoundOutputValueChangedNative, FName, const FMetaSoundOutput&);`
- L31 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMetasoundOutputValueChangedMulticast, FName, Name, const FMetaSoundOutput&, Output);`
- L31 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMetasoundOutputValueChangedMulticast, FName, Name, const FMetaSoundOutput&, Output);`
- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMetasoundOutputValueChangedNativeMulticast, FName, const FMetaSoundOutput&);`
- L32 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnMetasoundOutputValueChangedNativeMulticast, FName, const FMetaSoundOutput&);`
- L35 _namespace_ `namespace Metasound`
- L79 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGeneratorSet, TWeakPtr<FMetasoundGenerator>&&);`
- L86 _delegate_ `DECLARE_DELEGATE(FOnGeneratorGraphSet);`
- L93 _delegate_ `DECLARE_DELEGATE(FOnGeneratorIOUpdated);`
- L101 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGeneratorIOUpdatedWithChanges, const TArray<FVertexInterfaceChange>&);`
- L305 _function_ `friend uint32 GetTypeHash(FOutputWatcherKey Key)` (scope `Metasound`)
- L465 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAttached);` — UMetasoundGeneratorHandle shields its "clients" from "cross thread" issues related to callbacks coming in the audio control or rendering threads that game thread clients (e.g. blueprints) want to know about. That is why these next delegate definitions do not need to be the "TS" variants. Assignments to members of this type, and the broadcasts there to will all happen on the game thread. EVEN IF the instigator of those callbacks is on the audio render thread.
- L468 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnDetached);`
- L471 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSetGraph);`
- L475 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnIOUpdated) UE_DEPRECATED(5.5, "Use OnIOUpdatedWithChanges.") FOnIOUpdated OnIOUpdated;`
- L479 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnIOUpdatedWithChanges, const TArray<Metasound::FVertexInterfaceChange>&) FOnIOUpdatedWithChanges OnIOUpdatedWithChanges;`
- L547 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSetGraphMulticast);`

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundOperatorCacheSubsystem.h` (Public)


#### class `UMetaSoundCacheSubsystem`  
`class UMetaSoundCacheSubsystem : public UAudioEngineSubsystem`  
_L25-55_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAudioEngineSubsystem`
- desc: UMetaSoundCacheSubsystem
- L31 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L32 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L33 _public prototype_ `virtual void Update() override;`
- L39 _public prototype_ `void PrecacheMetaSound(UPARAM(DisplayName = "MetaSound Source") UMetaSoundSource* InMetaSound, UPARAM(DisplayName = "Num Instances` — `UFUNCTION(BlueprintCallable, Category = "MetaSound", meta = (DisplayName = "Precache MetaSound"))` — Builds the requested number of MetaSound operators (asynchronously) and puts them in the pool for playback. (If these operators are not yet available when the MetaSound attempts to play, one will be created Independent of this request.)
- L45 _public prototype_ `void TouchOrPrecacheMetaSound(UPARAM(DisplayName = "MetaSound Source") UMetaSoundSource* InMetaSound, UPARAM(DisplayName = "Num Instances` — `UFUNCTION(BlueprintCallable, Category = "MetaSound", meta = (DisplayName = "Touch or Precache MetaSound"))` — same as PrecacheMetaSound except cached operator that already exists in the cache will be moved to the top instead of building, any operators that we couldn't move to the top, will be built. (i.e. if 2 operators are already cached and Num Instances is 4, it will construct 2 and move the existing 2 to the top of the cache)
- L49 _public prototype_ `void RemoveCachedOperatorsForMetaSound(UPARAM(DisplayName = "MetaSound Source") UMetaSoundSourc` — `UFUNCTION(BlueprintCallable, Category = "MetaSound", meta = (DisplayName = "RemoveCached Operators for MetaSound"))` — Clear the operator pool of any operators associated with the given MetaSound
- L52 _private prototype_ `void PrecacheMetaSoundInternal(UMetaSoundSource* InMetaSound, int32 InNumInstances, bool bTouchExisting);`
- L54 _private member_ `FSoundGeneratorInitParams BuildParams;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API METASOUNDENGINE_API`

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundOutput.h` (Public)


#### struct `FMetaSoundOutput`  
`struct FMetaSoundOutput : public FSoundGeneratorOutput`  
_L17-135_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FSoundGeneratorOutput`
- desc: Exposes the value of an output on a FMetasoundGenerator.
- L21 _public prototype_ `FMetaSoundOutput() = default;`
- L23 _public prototype_ `FMetaSoundOutput(const FMetaSoundOutput& Other);`
- L25 _public prototype_ `FMetaSoundOutput& operator=(const FMetaSoundOutput& Other);`
- L27 _public prototype_ `FMetaSoundOutput(FMetaSoundOutput&& Other) noexcept;`
- L29 _public prototype_ `FMetaSoundOutput& operator=(FMetaSoundOutput&& Other) noexcept;`
- L31 _public prototype_ `FMetaSoundOutput(FName InName, const TSharedPtr<Metasound::IOutputStorage>& InData);`
- L38 _public prototype_ `bool IsValid() const;` — Has this output been initialized? @returns true if the output has been initialized, false otherwise
- L45 _public prototype_ `FName GetDataTypeName() const;` — Get the type name of the output @returns The type name, or none if invalid
- L54 _public function_ `template<typename DataType> void Init(const DataType& InitialValue)` — Initialize the output with some data. @tparam DataType - The type to use for initialization @param InitialValue - The initial value to use
- L67 _public function_ `template<typename DataType> bool IsType() const` — Check if this output is of the given type @tparam DataType - The data type to check @returns true if it's the given type, false otherwise
- L81 _public function_ `template<typename DataType> bool Get(DataType& Value) const` — Get the value, for copyable registered Metasound data types @tparam DataType - The expected data type of the output @param Value - The value to use @returns true if the value was retrieved, false otherwise
- L101 _public function_ `template<typename DataType> bool Set(const DataType& Value)` — Set the value, for copyable registered Metasound data types @tparam DataType - The expected data type of the output @param Value - The value to use @returns true if the value was set, false otherwise
- L121 _public function_ `template<typename DataType> bool Set(DataType&& Value)` — Set the value, for moveable registered Metasound data types @tparam DataType - The expected data type of the output @param Value - The value to use @returns true if the value was set, false otherwise
- L134 _private member_ `TUniquePtr<Metasound::IOutputStorage> Data;`

#### class `UMetasoundOutputBlueprintAccess`  
`class UMetasoundOutputBlueprintAccess final : public UBlueprintFunctionLibrary`  
_L142-170_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint support for core types. If you want to support more core types, add them here. If you want to support types introduced in other plugins, create a blueprint library in that plugin.
- L147 _private prototype_ `static bool IsFloat(const FMetaSoundOutput& Output);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`
- L149 _private prototype_ `static float GetFloat(const FMetaSoundOutput& Output, bool& Success);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`
- L152 _private prototype_ `static bool IsInt32(const FMetaSoundOutput& Output);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`
- L154 _private prototype_ `static int32 GetInt32(const FMetaSoundOutput& Output, bool& Success);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`
- L157 _private prototype_ `static bool IsBool(const FMetaSoundOutput& Output);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`
- L159 _private prototype_ `static bool GetBool(const FMetaSoundOutput& Output, bool& Success);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`
- L162 _private prototype_ `static bool IsString(const FMetaSoundOutput& Output);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`
- L164 _private prototype_ `static FString GetString(const FMetaSoundOutput& Output, bool& Success);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`
- L167 _private prototype_ `static bool IsTime(const FMetaSoundOutput& Output);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`
- L169 _private prototype_ `static double GetTimeSeconds(const FMetaSoundOutput& Output, bool& Success);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput")`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDENGINE_API`
- L56 _typedef_ `using FOutputData = Metasound::TOutputStorage<DataType>;` (scope `FMetaSoundOutput::Init`)
- L88 _typedef_ `using FOutputData = Metasound::TOutputStorage<DataType>;` (scope `FMetaSoundOutput::Get`)
- L108 _typedef_ `using FOutputData = Metasound::TOutputStorage<DataType>;` (scope `FMetaSoundOutput::Set`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundOutputSubsystem.h` (Public)


#### class `UMetaSoundOutputSubsystem`  
`class UMetaSoundOutputSubsystem : public UWorldSubsystem`  
_L18-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem`
- desc: Provides access to a playing Metasound generator's outputs
- L23 _public prototype_ `virtual ~UMetaSoundOutputSubsystem() override = default;`
- L36 _public prototype_ `bool WatchOutput( UAudioComponent* AudioComponent, FName OutputName, const FOnMetasoundOutputValueChanged& OnOutputValueChanged, FName AnalyzerName = NAME_None, FName AnalyzerOutputName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category="MetaSoundOutput", meta=(AdvancedDisplay = "3"))` — Watch an output on a Metasound playing on a given audio component. @param AudioComponent - The audio component @param OutputName - The user-specified name of the output in the Metasound @param OnOutputValueChanged - The event to fire when the output's value changes @param AnalyzerName - (optional) The name of the analyzer to use on the output, defaults to a passthrough @param AnalyzerOutputName - (optional) The name of the output on the analyzer to watch, defaults to the passthrough output @returns true if the watch setup succeeded, false otherwise
- L43 _public prototype_ `bool WatchOutput( UAudioComponent* AudioComponent, FName OutputName, const FOnMetasoundOutputValueChangedNative& OnOutputValueChanged, FName AnalyzerName = NAME_None, FName AnalyzerOutputName = NAME_None);`
- L51 _public prototype_ `bool UnwatchOutput( UAudioComponent* AudioComponent, FName OutputName, const FOnMetasoundOutputValueChanged& OnOutputValueChanged, FName AnalyzerName = NAME_None, FName AnalyzerOutputName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "MetaSoundOutput", meta = (AdvancedDisplay = "3"))`
- L58 _public prototype_ `bool UnwatchOutput( UAudioComponent* AudioComponent, FName OutputName, const FOnMetasoundOutputValueChangedNative& OnOutputValueChanged, FName AnalyzerName = NAME_None, FName AnalyzerOutputName = NAME_None);`
- L66 _private prototype_ `TSharedPtr<Metasound::FMetasoundGeneratorHandle> GetOrCreateGeneratorHandle(UAudioComponent* AudioComponent);`
- L67 _private prototype_ `void CleanUpInvalidGeneratorHandles();`
- L69 _private member_ `TArray<TSharedPtr<Metasound::FMetasoundGeneratorHandle>> TrackedGenerators;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METASOUNDENGINE_API`

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundSettings.h` (Public)


#### struct `Metasound::Engine::FTargetPageOverride`  
`struct FTargetPageOverride`  
_L30-34_
- L32 _public member_ `FName PlatformName;`
- L33 _public member_ `TOptional<FGuid> PageID;`

#### enum `EMetaSoundMessageLevel`  
`enum class EMetaSoundMessageLevel : uint8`  
_L50-55_
- reflection: `UENUM()`
- L52 _public enumerator_ `Error`
- L53 _public enumerator_ `Warning`
- L54 _public enumerator_ `Info`

#### struct `FDefaultMetaSoundAssetAutoUpdateSettings`  
`struct FDefaultMetaSoundAssetAutoUpdateSettings`  
_L58-65_
- reflection: `USTRUCT()`
- L64 _public member_ `FSoftObjectPath MetaSound;` — `UPROPERTY(EditAnywhere, Category = "AutoUpdate", meta = (AllowedClasses = "/Script/MetasoundEngine.MetaSound, /Script/MetasoundEngine.MetaSoundSource"))` — MetaSound to prevent from AutoUpdate.

#### class `UMetaSoundQualityHelper`  
`class UMetaSoundQualityHelper : public UObject`  
_L68-78_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UObject`
- L77 _public function_ `static TArray<FName> GetQualityNames()` — `UFUNCTION(meta = (DeprecatedFunction, DeprecationMessage = "Use UMetaSoundSettings::GetQualityNames instead"))` — Returns a list of quality settings to present to a combobox

#### struct `FMetaSoundPageSettings`  
`struct FMetaSoundPageSettings`  
_L81-128_
- reflection: `USTRUCT()`
- L86 _public member_ `FGuid UniqueId = Metasound::Frontend::DefaultPageID;` — `UPROPERTY()`
- L90 _public member_ `FName Name = Metasound::Frontend::DefaultPageName;` — `UPROPERTY(EditAnywhere, Category = "Pages", meta = (EditCondition = "!bIsDefaultPage"))` — Name of this page's setting to be displayed in editors and used for identification from Blueprint/native API.
- L100 _private member_ `FPerPlatformBool CanTarget = true;` — `UPROPERTY(EditAnywhere, Category = "Pages", meta = (DisplayName = "Targetable"))` — When true, page asset data (i.e. graphs and input defaults) can be targeted for the most applicable platform/platform group. If associated asset data is defined, will always be cooked. If false, asset page data is only cooked if it is resolved to from a higher-indexed page setting and is not set to explicitly "ExcludeFromCook".
- L105 _private member_ `bool bIsDefaultPage = true;` — `UPROPERTY(EditAnywhere, Category = "Pages", meta = (EditCondition = false, EditConditionHides))` — Just used to inform edit condition to enable/disable exclude from cook. Maintained by ConformPageSettings on object load/mutation. EditCondition meta mark-up is hack to avoid boolean being default added to name field
- L112 _private member_ `FPerPlatformBool ExcludeFromCook = false;` — `UPROPERTY(EditAnywhere, Category = "Pages", meta = (EditCondition = "!bIsDefaultPage"))` — When true, exclude page data when cooking from the assigned platform(s)/platform group(s). If false, page data may or may not be included in cook depending on whether or not the given page data is required in order to ensure a value is always resolved for the cook platform target(s). (Ignored if 'Targetable' is true for most applicable platform/platform group).
- L118 _public prototype_ `bool GetExcludeFromCook(FName PlatformName) const;` — Returns whether or not page should be excluded from being cooked on the given platform/platform group.
- L121 _public prototype_ `TArray<FName> GetTargetPlatforms() const;` — Returns array of platforms/platform groups page is valid target on.
- L124 _public prototype_ `bool PlatformCanTargetPage(FName PlatformName) const;` — Returns whether platform/platform group provided can target the provided page.

#### struct `FMetaSoundQualitySettings`  
`struct FMetaSoundQualitySettings`  
_L131-151_
- reflection: `USTRUCT()`
- L137 _public member_ `FGuid UniqueId;` — `UPROPERTY()` — A hidden GUID that will be generated once when adding a new entry. This prevents orphaning of renamed entries.
- L142 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "Quality")` — Name of this quality setting. This will appear in the quality dropdown list. The names should be unique but are not guaranteed to be (use guid for unique match)
- L146 _public member_ `FPerPlatformInt SampleRate = 0;` — `UPROPERTY(EditAnywhere, config, Category = "Quality", meta = (ClampMin = "0", ClampMax="96000"))` — Sample Rate (in Hz). NOTE: A Zero value will have no effect and use the Device Rate.
- L150 _public member_ `FPerPlatformFloat BlockRate = 0.f;` — `UPROPERTY(EditAnywhere, config, Category = "Quality", meta = (ClampMin = "0", ClampMax="1000"))` — Block Rate (in Hz). NOTE: A Zero value will have no effect and use the Default (100)

#### class `UMetaSoundSettings`  
`class UMetaSoundSettings : public UDeveloperSettings`  
_L155-348_
- reflection: `UCLASS(MinimalAPI, config = MetaSound, defaultconfig, meta = (DisplayName = "MetaSounds"))`
- inherits: `UDeveloperSettings`
- L162 _public member_ `bool bAutoUpdateEnabled = true;` — `UPROPERTY(meta = (Deprecated, DeprecationMessage = "5.7 - For performance reasons, AutoUpdate is now always only called during cook."))`
- L165 _public member_ `TArray<FMetasoundFrontendClassName> AutoUpdateDenylist;` — `UPROPERTY(meta = (Deprecated, DeprecationMessage = "5.7 - For performance reasons, AutoUpdate is now always only called during cook."))`
- L168 _public member_ `TArray<FDefaultMetaSoundAssetAutoUpdateSettings> AutoUpdateAssetDenylist;` — `UPROPERTY(meta = (Deprecated, DeprecationMessage = "For performance reasons, AutoUpdate is now always only called during cook."))`
- L173 _public member_ `bool bAutoUpdateLogWarningOnDroppedConnection = true;` — `UPROPERTY(EditAnywhere, config, Category = AutoUpdate, meta = (DisplayName = "Log Warning on Dropped Connection", EditCondition = "bAutoUpdateEnabled"))` — If true, warnings will be logged if updating a node results in existing connections being discarded.
- L181 _public member_ `TArray<FDirectoryPath> DirectoriesToRegister;` — `UPROPERTY(EditAnywhere, config, Category = Registration, meta = (RelativePath, LongPackageName))` — Directories to scan & automatically register MetaSound post initial asset scan on engine start-up. May speed up subsequent calls to playback MetaSounds post asset scan but increases application load time. See 'MetaSoundAssetSubsystem::RegisterAssetClassesInDirectories' to dynamically register or 'MetaSoundAssetSubsystem::UnregisterAssetClassesInDirectories' to unregister asset classes.
- L186 _public member_ `int32 DenyListCacheChangeID = 0;` — `UE_DEPRECATED(5.7, "DenyList no longer supported (auto-update automatically executed during cook and not supported at runtime")` — `UPROPERTY(Transient)`
- L191 _private member_ `Metasound::Engine::FOnSettingsDefaultConformed OnDefaultRenamed;`
- L192 _private member_ `Metasound::Engine::FOnPageSettingsUpdated OnPageSettingsUpdated;`
- L200 _private member_ `FName TargetPageName = Metasound::Frontend::DefaultPageName;` — `UPROPERTY(EditAnywhere, config, Category = "Pages (Experimental)", meta = (GetOptions = "MetasoundEngine.MetaSoundSettings.GetPageNames"))` — Page Name to target when attempting to execute MetaSound. If target page is not implemented (or cooked in a runtime build) for the active platform, uses order of cooked pages (see 'Page Settings' for order) falling back to lower index-ordered page implemented in MetaSound asset. If no fallback is found, uses default implementation.
- L204 _private member_ `FMetaSoundPageSettings DefaultPageSettings;` — `UPROPERTY(EditAnywhere, config, Category = "Pages (Experimental)")` — Default page settings to be used in editor and if no other page settings are targeted or defined.
- L211 _private member_ `TArray<FMetaSoundPageSettings> PageSettings;` — `UPROPERTY(EditAnywhere, config, Category = "Pages (Experimental)")` — Array of possible page settings that can be added to a MetaSound object. Order defines default fallback logic whereby a higher index-ordered page implemented in a MetaSound asset is higher priority (see 'Target Page').
- L215 _private member_ `TArray<FMetaSoundQualitySettings> QualitySettings;` — `UPROPERTY(EditAnywhere, config, Category = Quality)` — Array of possible quality settings for Metasounds to chose from
- L218 _private member_ `TOptional<FName> TargetPageNameOverride;` — Target page override to use set from code/script (supercedes serialized 'TargetPageName' field).
- L221 _private member_ `mutable FCriticalSection CookPlatformTargetCritSec;`
- L222 _private member_ `mutable TArray<FGuid> CookPlatformTargetPageIDs;`
- L223 _private member_ `mutable TArray<FGuid> CookPlatformPageOrder;`
- L224 _private member_ `mutable FName CookPlatformTargetPage;`
- L227 _private prototype_ `virtual FName GetCategoryName() const override;`
- L230 _private prototype_ `TArray<FGuid> GeneratePageOrderInternal(const FName& InPlatformName, const FGuid& InTargetPageID) const;` — Generates the page order for a given platform and desired target page ID
- L232 _private member_ `std::atomic<bool> bIsPageOrderCached = false;`
- L233 _private member_ `TArray<FGuid> CachedPageOrder;`
- L235 _private prototype_ `void UpdateCachedPageOrder();` — Updates the cached page order with the latest settings.
- L239 _public prototype_ `static const FGuid* GetPageID(FName PageName);` — Helper function to convert page name to id. Returns nullptr if page name not found.
- L242 _public prototype_ `static FName GetPageName(FGuid PageID);` — Helper function to convert page ID into page name. If page ID is not found, returns default page.
- L245 _public prototype_ `static TArrayView<const FGuid> GetPageOrder();` — Returns a cached global version of the PageOrder from the UMetaSoundSettings Default Object.
- L248 _public prototype_ `TArray<FGuid> GeneratePageOrder() const;` — Generates the page order for a current configured platform and target ID
- L252 _public prototype_ `const FMetaSoundPageSettings* FindPageSettings(FName Name) const;` — Returns the page settings with the provided name. If there are multiple settings with the same name, selection within the duplicates is undefined.
- L255 _public prototype_ `const FMetaSoundPageSettings* FindPageSettings(const FGuid& InPageID) const;` — Returns the page settings with the unique ID given.
- L259 _public prototype_ `const FMetaSoundQualitySettings* FindQualitySettings(FName Name) const;` — Returns the quality settings with the provided name. If there are multiple settings with the same name, selection within the duplicates is undefined.
- L262 _public prototype_ `const FMetaSoundQualitySettings* FindQualitySettings(const FGuid& InQualityID) const;` — Returns the quality settings with the unique ID given.
- L264 _public prototype_ `const FMetaSoundPageSettings& GetDefaultPageSettings() const;`
- L268 _public prototype_ `TArray<FGuid> GetCookedTargetPageIDs(FName PlatformName) const;` — Returns PageIDs to be cooked to the given platform/platform group.
- L269 _public prototype_ `TArray<FGuid> GetCookedPageOrder(FName PlatformName) const;`
- L272 _public prototype_ `void IterateCookedTargetPageIDs(FName PlatformName, TFunctionRef<void(const FGuid&)> Iter) const;` — Iterates PageIDs cooked to the given platform/platform group.
- L277 _public prototype_ `TArray<FName> GetAllPlatformNamesImplementingTargets() const;` — Returns superset of page platforms (and groups) that define page target(s).
- L281 _public function_ `const TArray<FMetaSoundPageSettings>& GetProjectPageSettings() const` — Returns the project-specific page settings (does not include the required default settings).
- L284 _public prototype_ `const FMetaSoundPageSettings& GetTargetPageSettings() const;` — Returns the currently targeted page settings.
- L286 _public function_ `const TArray<FMetaSoundQualitySettings>& GetQualitySettings() const`
- L289 _public prototype_ `void OverrideTargetPageSettings(TOptional<Metasound::Engine::FTargetPageOverride> InOverride);`
- L293 _public prototype_ `Metasound::Engine::FOnSettingsDefaultConformed& GetOnDefaultRenamedDelegate();`
- L294 _public prototype_ `Metasound::Engine::FOnPageSettingsUpdated& GetOnPageSettingsUpdatedDelegate();`
- L296 _public prototype_ `static FName GetPageSettingPropertyName();`
- L297 _public prototype_ `static FName GetQualitySettingPropertyName();`
- L302 _public prototype_ `void IteratePageSettings(TFunctionRef<void(const FMetaSoundPageSettings&)> Iter, bool bReverse = false) const;` — Iterates possible page settings in order (including the default page settings, which is always last). If optionally set to reverse, iterates in reverse.
- L306 _public prototype_ `bool SetTargetPage(FName PageName);` — Sets the target page to the given name. Returns true if associated page settings were found and target set, false if not found and not set.
- L315 _public prototype_ `static TArray<FName> GetPageNames();` — `UFUNCTION()` — Returns an array of page names. Can be used to present to a combobox. Ex: UPROPERTY(... meta=(GetOptions="MetasoundEngine.MetaSoundSettings.GetPageNames")) FName Page;
- L322 _public prototype_ `static TArray<FName> GetQualityNames();` — `UFUNCTION()` — Returns an array of quality setting names. Can be used to present to a combobox. Ex: UPROPERTY(... meta=(GetOptions="MetasoundEngine.MetaSoundSettings.GetQualityNames")) FName QualitySetting;
- L327 _private prototype_ `void CacheCookedPageIDs(const FName InPlatformName) const;`
- L332 _private prototype_ `void ConformPageSettings(bool bNotifyDefaultRenamed);`
- L334 _private prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L335 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L337 _private prototype_ `const FMetaSoundPageSettings* GetTargetPageSettingsFromOverride(const FName InTargetPageName) const;`
- L338 _private prototype_ `TArray<FGuid> GeneratePageOrderFromOverride() const;`
- L340 _private member_ `TOptional<Metasound::Engine::FTargetPageOverride> PageOverrideData;`
- L343 _private prototype_ `virtual void PostInitProperties() override;`
- L346 _private member_ `mutable bool bWarnAccessBeforeInit = true;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API METASOUNDENGINE_API`
- L23 _namespace_ `namespace Metasound`
- L23 _namespace_ `namespace Engine` (scope `Metasound`)
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSettingsDefaultConformed);`
- L26 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSettingsDefaultConformed);` (scope `Metasound::Engine`)
- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnPageSettingsUpdated);`
- L27 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnPageSettingsUpdated);` (scope `Metasound::Engine`)
- L37 _typedef_ `using FPageResolutionEditorResults UE_DEPRECATED(5.7, "Use FTargetPageOverride i` (scope `Metasound::Engine`)
- L40 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FTargetPageOverride, FOnResolveEditorPage, const TArray<FGuid>& );`
- L40 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FTargetPageOverride, FOnResolveEditorPage, const TArray<FGuid>& );` (scope `Metasound::Engine`) — `UE_DEPRECATED(5.7, "Use FOverrideTargetPageSettings instead.")`
- L46 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FGuid, FOnResolvePage, const TArray<FGuid>& );`
- L46 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FGuid, FOnResolvePage, const TArray<FGuid>& );` (scope `Metasound::Engine`) — `UE_DEPRECATED(5.7, "This is no longer supported.")`

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundSource.h` (Public)


#### struct `Metasound::FGeneratorInstanceInfo`  
`struct FGeneratorInstanceInfo`  
_L68-75_
- L70 _public prototype_ `FGeneratorInstanceInfo() = default;`
- L71 _public prototype_ `FGeneratorInstanceInfo(uint64 InAudioComponentID, uint64 InInstanceID, TWeakPtr<FMetasoundGenerator> InGenerator);`
- L72 _public member_ `uint64 AudioComponentID;`
- L73 _public member_ `uint64 InstanceID;`
- L74 _public member_ `TWeakPtr<FMetasoundGenerator> Generator;`

#### class `UMetaSoundSource`  
`class UMetaSoundSource : public USoundWaveProcedural, public FMetasoundAssetBase, public IMetaSoundDocumentInterface`  
_L89-489_
- reflection: `UCLASS(MinimalAPI, hidecategories = object, BlueprintType, meta = (DisplayName = "MetaSound Source"))`
- inherits: `USoundWaveProcedural,FMetasoundAssetBase,IMetaSoundDocumentInterface`
- desc: This Metasound type can be played as an audio source.
- L140 _protected member_ `FMetasoundFrontendDocument RootMetasoundDocument;` — `UPROPERTY(EditAnywhere, Category = CustomView)`
- L143 _protected member_ `TSet<FString> ReferencedAssetClassKeys;` — `UPROPERTY()`
- L146 _protected member_ `TSet<TObjectPtr<UObject>> ReferencedAssetClassObjects;` — `UPROPERTY()`
- L150 _protected member_ `TSet<FSoftObjectPath> ReferenceAssetClassCache;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Soft reference cache is no longer supported"))`
- L153 _protected member_ `TObjectPtr<UMetasoundEditorGraphBase> Graph;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage = "Use EditorGraph instead as it is now transient and generated via the FrontendDocument dynamically."))`
- L156 _protected member_ `TObjectPtr<UMetasoundEditorGraphBase> EditorGraph;` — `UPROPERTY(Transient, NonTransactional)`
- L160 _public prototype_ `UMetaSoundSource(const FObjectInitializer& ObjectInitializer);`
- L164 _public member_ `EMetaSoundOutputAudioFormat OutputFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Metasound)` — The output audio format of the metasound source.
- L167 _public member_ `EMetasoundChannelAgnosticSourceFormatChooser ChannelAgnosticFormatChooser = EMetasoundChannelAgnosticSourceFormatChooser::Auto;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Metasound, meta = (DisplayName = "Source Format (exp)", EditConditionHides, EditCondition = "OutputFormat == EMetaSoundOutputAudioFormat::ChannelAgnostic"))`
- L172 _public member_ `FName ChannelAgnosticCustomFormat;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Metasound, meta = (DisplayName = "Custom Format Name", GetOptions="MetasoundCatCastingOptionsHelper.GetCastingOptions_AudioMixerOnly", EditConditionHides, EditCondition = "OutputFormat == EMetaSoundOutputAudioFormat::ChannelAgnostic && ChannelAgnosticFormatChooser == EMetasoundChannelAgnosticSourceFormatChooser::Custom"))` — The custom channel-agnostic format name (e.g. "Cat:Discrete:Stereo"). Only used when ChannelAgnosticFormatChooser == Custom. Restricted to discrete (mixer-compatible) formats only — soundfield/ambisonics are not supported by AudioMixer.
- L177 _public member_ `FName QualitySetting;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AssetRegistrySearchable, meta = (GetOptions="MetasoundEngine.MetaSoundSettings.GetQualityNames"), Category = "Metasound")` — The QualitySetting MetaSound will use, as defined in 'MetaSound' Settings.
- L181 _public member_ `FGuid QualitySettingGuid;` — `UPROPERTY()` — This a editor only look up for the Quality Setting above. Preventing orphaning of the original name.
- L185 _public member_ `FPerPlatformFloat BlockRateOverride = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = Metasound, meta = (UIMin = 0, UIMax = 1000.0, DisplayAfter="OutputFormat", DisplayName = "Override Block Rate (in Hz)"))` — Override the BlockRate for this Sound (overrides Quality). NOTE: A Zero value will have no effect and use either the Quality setting (if set), or the defaults.
- L189 _public member_ `FPerPlatformInt SampleRateOverride = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = Metasound, meta = (UIMin = 0, UIMax = 96000, DisplayName = "Override Sample Rate (in Hz)"))` — Override the SampleRate for this Sound (overrides Quality). NOTE: A Zero value will have no effect and use either the Quality setting (if set), or the Device Rate
- L192 _public member_ `FGuid AssetClassID;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property is now serialized directly as asset tag"))`
- L195 _public member_ `FString RegistryInputTypes;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property is now serialized directly as asset tag"))`
- L198 _public member_ `FString RegistryOutputTypes;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property is now serialized directly as asset tag"))`
- L201 _public member_ `int32 RegistryVersionMajor = 0;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property is now serialized directly as asset tag"))`
- L204 _public member_ `int32 RegistryVersionMinor = 0;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property is now serialized directly as asset tag"))`
- L207 _public member_ `bool bIsPreset = false;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Property is now serialized directly as asset tag"))`
- L211 _public function_ `static FName GetDocumentPropertyName()` — Returns document name (for editor purposes, and avoids making document public for edit while allowing editor to reference directly)
- L217 _public prototype_ `virtual FText GetDisplayName() const override;` — Name to display in editors
- L222 _public prototype_ `virtual UEdGraph* GetGraph() const override;` — Returns the graph associated with this Metasound. Graph is required to be referenced on Metasound UObject for editor serialization purposes. @return Editor graph associated with UMetaSoundSource.
- L223 _public prototype_ `virtual UEdGraph& GetGraphChecked() const override;`
- L224 _public prototype_ `virtual void MigrateEditorGraph(FMetaSoundFrontendDocumentBuilder& OutBuilder) override;`
- L229 _public function_ `virtual void SetGraph(UEdGraph* InGraph) override` — Sets the graph associated with this Metasound. Graph is required to be referenced on Metasound UObject for editor serialization purposes. @param Editor graph associated with UMetaSoundSource.
- L237 _public prototype_ `virtual void PostEditUndo() override;`
- L239 _public function_ `virtual bool GetRedrawThumbnail() const override`
- L244 _public function_ `virtual void SetRedrawThumbnail(bool bInRedraw) override`
- L248 _public function_ `virtual bool CanVisualizeAsset() const override`
- L253 _public prototype_ `virtual void PreDuplicate(FObjectDuplicationParameters& DupParams) override;`
- L254 _public prototype_ `virtual void PostDuplicate(EDuplicateMode::Type InDuplicateMode) override;`
- L255 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;`
- L256 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L258 _public prototype_ `virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;`
- L261 _private prototype_ `void PostEditChangeOutputFormat();`
- L262 _private prototype_ `void PostEditChangeQualitySettings();`
- L266 _public function_ `virtual const TSet<FString>& GetReferencedAssetClassKeys() const override`
- L270 _public prototype_ `virtual TArray<FMetasoundAssetBase*> GetReferencedAssets() const override;`
- L274 _public prototype_ `virtual void OnAsyncReferencedAssetsLoaded(const TArray<FMetasoundAssetBase*>& InAsyncReferences) override;` — `UE_DEPRECATED(5.8, "This is deprecated behavior and will become UE_INTERNAL API in a future release for back compat.")`
- L277 _public prototype_ `virtual void BeginDestroy() override;`
- L278 _public prototype_ `virtual void PreSave(FObjectPreSaveContext InSaveContext) override;`
- L279 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L280 _public prototype_ `virtual void PostLoad() override;`
- L282 _public prototype_ `void PostLoadQualitySettings();`
- L284 _public prototype_ `virtual bool ConformObjectToDocument() override;`
- L286 _public prototype_ `virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;`
- L288 _public prototype_ `virtual FTopLevelAssetPath GetAssetPathChecked() const override;`
- L290 _public function_ `UObject* GetOwningAsset() override`
- L295 _public function_ `const UObject* GetOwningAsset() const override`
- L299 _public prototype_ `virtual void InitParameters(TArray<FAudioParameter>& ParametersToInit, FName InFeatureName) override;`
- L301 _public prototype_ `virtual void InitResources() override;`
- L303 _public prototype_ `virtual TSharedPtr<Audio::IProxyData> CreateProxyData(const Audio::FProxyDataInitParams& InitParams) override;`
- L306 _public prototype_ `virtual void UpdateAndRegisterForExecution(const Metasound::Frontend::FMetaSoundAssetRegistrationOptions& InRegistrationOptions) override;`
- L308 _public prototype_ `virtual bool IsPlayable() const override;`
- L309 _public prototype_ `virtual float GetDuration() const override;`
- L310 _public prototype_ `virtual bool ImplementsParameterInterface(Audio::FParameterInterfacePtr InInterface) const override;`
- L311 _public prototype_ `virtual ISoundGeneratorPtr CreateSoundGenerator(const FSoundGeneratorInitParams& InParams, TArray<FAudioParameter>&& InDefaultParameters) override;`
- L312 _public prototype_ `virtual void OnEndGenerate(ISoundGeneratorPtr Generator) override;`
- L313 _public prototype_ `virtual TSharedPtr<Audio::IParameterTransmitter> CreateParameterTransmitter(Audio::FParameterTransmitterInitParams&& InParams) const override;`
- L314 _public prototype_ `virtual bool IsParameterValid(const FAudioParameter& InParameter) const override;`
- L315 _public prototype_ `virtual bool IsLooping() const override;`
- L316 _public prototype_ `virtual bool IsOneShot() const override;`
- L317 _public function_ `UE_DEPRECATED(5.7, "This is no longer used.") virtual bool EnableSubmixSendsOnPr`
- L326 _public prototype_ `TWeakPtr<Metasound::FMetasoundGenerator> GetGeneratorForAudioComponent(uint64 ComponentId) const;` — Attempt to get a generator for a given AudioComponentID. You should only pass a valid AudioComponentID. If the ID is set to INDEX_NONE, e.g. from using FAudioDevice::PlaySoundAtLocation, use GetGeneratorForInstanceID instead. @param ComponentId The ID of the AudioComponent you want the generator from. @return A generator if it exists. A null weak pointer otherwise.
- L334 _public prototype_ `TWeakPtr<Metasound::FMetasoundGenerator> GetGeneratorForInstanceID(uint64 InstanceId) const;` — Attempt to get a generator for a given InstanceID. Use Audio::GetTransmitterID to construct an appropriate InstanceID. @param InstanceId The hash of the ComponentID, WaveInstanceHash and the ActiveSound Play Order @return A generator if it exists. A null weak pointer otherwise.
- L335 _public prototype_ `bool IsDynamic() const;`
- L339 _public member_ `FOnGeneratorInstanceCreated OnGeneratorInstanceCreated;` — `UE_DEPRECATED(5.6, "Use OnGeneratorInstanceInfoCreated instead.")`
- L341 _public member_ `FOnGeneratorInstanceDestroyed OnGeneratorInstanceDestroyed;` — `UE_DEPRECATED(5.6, "Use OnGeneratorInstanceInfoDestroyed instead.")`
- L343 _public member_ `FGeneratorInstanceInfoDelegate OnGeneratorInstanceInfoCreated;`
- L344 _public member_ `FGeneratorInstanceInfoDelegate OnGeneratorInstanceInfoDestroyed;`
- L345 _public prototype_ `Metasound::FOperatorSettings GetOperatorSettings(Metasound::FSampleRate InDeviceSampleRate) const;`
- L347 _public prototype_ `virtual const FMetasoundFrontendDocument& GetConstDocument() const override;`
- L348 _public prototype_ `virtual bool IsActivelyBuilding() const override;`
- L350 _public prototype_ `virtual const UClass& GetBaseMetaSoundUClass() const final override;`
- L351 _public prototype_ `virtual const UClass& GetBuilderUClass() const final override;`
- L352 _public prototype_ `virtual EMetasoundFrontendClassAccessFlags GetDefaultAccessFlags() const final override;`
- L355 _public prototype_ `UE_INTERNAL TArray<FRuntimeInput> GatherVerseParameters() const;`
- L362 _protected prototype_ `Metasound::Frontend::FDocumentAccessPtr GetDocumentAccessPtr(bool bReloadBuilder = true) override;` — `UE_DEPRECATED(5.6, "AccessPtrs are actively being deprecated. Writable access outside of the builder API " "is particularly problematic as in so accessing, the builder's caches are reset which can cause major " "editor performance regressions.")`
- L363 _protected prototype_ `Metasound::Frontend::FConstDocumentAccessPtr GetDocumentConstAccessPtr() const override;`
- L366 _protected prototype_ `virtual bool GetAllDefaultParameters(TArray<FAudioParameter>& OutParameters) const override;` — Gets all the default parameters for this Asset.
- L369 _protected prototype_ `virtual void SetReferencedAssets(TSet<Metasound::Frontend::IMetaSoundAssetManager::FAssetRef>&& InAssetRefs) override;`
- L373 _private function_ `virtual FMetasoundFrontendDocument& GetDocument() override`
- L378 _private prototype_ `virtual void OnBeginActiveBuilder() override;`
- L379 _private prototype_ `virtual void OnFinishActiveBuilder() override;`
- L382 _private prototype_ `void InitParametersInternal(const Metasound::TSortedVertexNameMap<FRuntimeInput>& InputMap, TArray<FAudioParameter>& ParametersToInit, FName InFeatureName) const;`
- L384 _private prototype_ `bool IsParameterValidInternal(const FAudioParameter& InParameter, const FName& InTypeName, Metasound::Frontend::IDataTypeRegistry& InDataTypeRegistry) const;`
- L386 _private prototype_ `static Metasound::SourcePrivate::FParameterRouter& GetParameterRouter();`
- L389 _public prototype_ `Metasound::FMetasoundEnvironment CreateEnvironment(const FSoundGeneratorInitParams& InParams) const;`
- L390 _public prototype_ `const TArray<Metasound::FVertexName>& GetOutputAudioChannelOrder() const;`
- L400 _public prototype_ `TSharedPtr<const Audio::FChannelTypeFamily> CalculateAutoSourceFormat(const TArray<FAudioParameter>& InParams) const;` — Determines the "Auto" Channel Agnostic Format for this Source. Consults the document layer and makes a best guess at the appropriate format from wave proxy channel counts. Can be called before graph evaluation. @param InParams - Audio parameters to inspect for wave proxies. Pass empty array to use defaults. @return Shared pointer to the resolved channel type family, or nullptr if no format could be determined.
- L417 _public prototype_ `FResolvedSourceFormat ResolveSourceFormatAndNumChannels(const FSoundGeneratorInitParams& InParams, const TArray<FAudioParameter>& InDefaultParameters, Metasound::FMetasoundEnvironment& InOutEnvironment);` — Resolves SourceFormatName and NumChannels based on the current OutputFormat. For ChannelAgnostic sources, determines format via Custom > Auto priority and populates the Environment. For discrete sources, derives NumChannels from GetOutputAudioChannelOrder(). Does NOT modify USoundWave::NumChannels -- the caller is responsible for assigning the returned value where appropriate. @param InParams - Sound generator init params (used for fallback channel count). @param InDefaultParameters - Audio parameters for auto-format detection (pass empty for precache). @param InOutEnvironment - Environment to populate with SourceFormatName. @return FResolvedSourceFormat containing the format name and channel count.
- L429 _public prototype_ `const UMetaSoundSource& FindFirstNoninflatableSource(Metasound::FMetasoundEnvironment& InOutEnvironment, TFunctionRef<void(const UMetaSoundSource&)> OnTraversal) const;` — Find the Source related to this Preset. If this MetaSound is a preset and preset graph inflation is enabled, this will traverse the MetaSound Preset hierarchy until a UMetaSoundSource is found which is either - Not a preset AND/OR - Has modified constructor pin overrides.
- L432 _private prototype_ `const UMetaSoundSource& FindFirstNoninflatableSourceInternal(TArray<FGuid>& OutHierarchy, TFunctionRef<void(const UMetaSoundSource&)> OnTraversal) const;`
- L433 _private prototype_ `TSharedPtr<const Metasound::IGraph> FindFirstNoninflatableGraph(UMetaSoundSource::FAudioParameterCollector& InOutParameterCollector, Metasound::FMetasoundEnvironment& InOutEnvironment) const;`
- L435 _private prototype_ `Metasound::FMetasoundEnvironment CreateEnvironment() const;`
- L436 _private prototype_ `Metasound::FMetasoundEnvironment CreateEnvironment(const Audio::FParameterTransmitterInitParams& InParams) const;`
- L438 _private member_ `mutable FCriticalSection GeneratorMapCriticalSection;`
- L439 _private member_ `TArray<Metasound::FGeneratorInstanceInfo> Generators;`
- L440 _private prototype_ `void TrackGenerator(Metasound::FGeneratorInstanceInfo&& GeneratorInfo);`
- L442 _private prototype_ `void ForgetGenerator(ISoundGeneratorPtr Generator);`
- L445 _private prototype_ `static FRuntimeInput CreateRuntimeInput(const Metasound::Frontend::IDataTypeRegistry& Registry, const FMetasoundFrontendClassInput& Input, bool bCreateUObjectProxies, TArrayView<const FGuid> InPageOrder);`
- L446 _private prototype_ `Metasound::TSortedVertexNameMap<FRuntimeInput> CreateRuntimeInputMap(bool bCreateUObjectProxies, TArrayView<const FGuid> InPageOrder) const;`
- L448 _private prototype_ `void CacheRuntimeInputData(TArrayView<const FGuid> InPageOrder);`
- L449 _private prototype_ `void InvalidateCachedRuntimeInputData();`
- L451 _private member_ `FRuntimeInputData RuntimeInputData;`
- L461 _private prototype_ `TSharedPtr<Metasound::DynamicGraph::FDynamicOperatorTransactor> SetDynamicGeneratorEnabled(bool bInIsEnabled);` — Enable/disable dynamic generator. Once a dynamic generator is enabled, all changes to the MetaSound should be applied to the FDynamicOperatorTransactor in order to keep parity between the document and active graph. Note: Disabling the dynamic generator will sever the communication between any active generators even if the dynamic generator is re-enabled during the lifetime of the active generators
- L468 _private prototype_ `TSharedPtr<Metasound::DynamicGraph::FDynamicOperatorTransactor> GetDynamicGeneratorTransactor() const;` — Get dynamic transactor If dynamic generators are enabled, this will return a valid pointer to a dynamic transactor. Changes to this transactor will be forwarded to any active Dynamic MetaSound Generators.
- L470 _private member_ `TSharedPtr<Metasound::DynamicGraph::FDynamicOperatorTransactor> DynamicTransactor;`
- L473 _private member_ `mutable Metasound::FSampleRate CachedAudioDeviceSampleRate = 0;` — Cache the AudioDevice Samplerate. (so that if we have to regenerate operator settings without the device rate we can use this).
- L475 _private member_ `bool bIsBuilderActive = false;`
- L476 _private member_ `bool bHasWarnedAboutStartTime = false;`
- L481 _private member_ `bool bIsPresetGraphInflationSupported = false;` — Preset graph inflation is a performance optimization intended for use with the MetaSoundOperatorPool. If multiple presets utilize the same base MetaSound, they may be able to share their operators in the operator pool. This makes for a more efficient use of the operator pool.
- L484 _private prototype_ `bool GetQualitySettings(const FName InPlatformName, Metasound::SourcePrivate::FCookedQualitySettings& OutQualitySettings) const;` — Quality settings.
- L485 _private prototype_ `void ResolveQualitySettings(const UMetaSoundSettings* Settings);`
- L486 _private prototype_ `void SerializeCookedQualitySettings(const FName PlatformName, FArchive& Ar);`
- L487 _private member_ `TPimplPtr<Metasound::SourcePrivate::FCookedQualitySettings> CookedQualitySettings;`

#### struct `UMetaSoundSource::FResolvedSourceFormat`  
`struct FResolvedSourceFormat`  
_L101-108_
- desc: Result of ResolveSourceFormatAndNumChannels.
- L104 _public member_ `FName SourceFormatName;` — The resolved source format name (NAME_None for discrete/non-CAT sources).
- L107 _public member_ `int32 NumChannels = INDEX_NONE;` — The resolved channel count, or INDEX_NONE on failure.

#### struct `UMetaSoundSource::FRuntimeInput`  
`struct UE_INTERNAL FRuntimeInput`  
_L111-127_
- desc: FRuntimeInput represents an input to a MetaSound which can be manipulated.
- L114 _public member_ `FName Name;` — Name of input vertex
- L116 _public member_ `FName TypeName;` — Data type name of input vertex.
- L118 _public member_ `EMetasoundFrontendVertexAccessType AccessType;` — Access type of input vertex.
- L120 _public member_ `FAudioParameter DefaultParameter;` — Default parameter of input vertex.
- L122 _public member_ `bool bIsTransmittable;` — True if the data type is transmittable. False otherwise.
- L125 _public member_ `bool bIsPaged = false;` — True if the data / default value deviates from the default page (graph)

#### struct `UMetaSoundSource::FRuntimeInputData`  
`struct FRuntimeInputData`  
_L130-136_
- L132 _public member_ `std::atomic<bool> bIsValid = false;`
- L134 _public member_ `Metasound::TSortedVertexNameMap<FRuntimeInput> InputMap;`

#### Free symbols / members of external scopes

- L26 _macro_ `#define UE_API METASOUNDENGINE_API`
- L38 _namespace_ `namespace Audio`
- L40 _typedef_ `using DeviceID = uint32;` (scope `Audio`)
- L43 _namespace_ `namespace Metasound`
- L47 _namespace_ `namespace DynamicGraph` (scope `Metasound`)
- L52 _namespace_ `namespace Engine` (scope `Metasound`)
- L57 _namespace_ `namespace Frontend` (scope `Metasound`)
- L62 _namespace_ `namespace SourcePrivate` (scope `Metasound`)
- L65 _typedef_ `using FCookedQualitySettings = FMetaSoundQualitySettings;` (scope `Metasound::SourcePrivate`)
- L80 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnGeneratorInstanceCreated, uint64, TSharedPtr<Metasound::FMetasoundGenerator>);`
- L80 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnGeneratorInstanceCreated, uint64, TSharedPtr<Metasound::FMetasoundGenerator>);` — `UE_DEPRECATED(5.6, "Use FGeneratorInstanceInfoDelegate instead.")`
- L82 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnGeneratorInstanceDestroyed, uint64, TSharedPtr<Metasound::FMetasoundGenerator>);`
- L82 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnGeneratorInstanceDestroyed, uint64, TSharedPtr<Metasound::FMetasoundGenerator>);` — `UE_DEPRECATED(5.6, "Use FGeneratorInstanceInfoDelegate instead.")`
- L83 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FGeneratorInstanceInfoDelegate, const Metasound::FGeneratorInstanceInfo&);`
- L83 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FGeneratorInstanceInfoDelegate, const Metasound::FGeneratorInstanceInfo&);`

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundUObjectRegistry.h` (Public)


#### class `Metasound::IMetasoundUObjectRegistryEntry`  
`class IMetasoundUObjectRegistryEntry`  
_L26-70_
- desc: Interface for an entry into the Metasound-UObject Registry. An entry provides information linking a FMetasoundFrontendClassInterface to a UClass. It also provides methods for accessing the FMetasoundAssetBase from a UObject.
- L29 _public prototype_ `virtual ~IMetasoundUObjectRegistryEntry() = default;`
- L32 _public function_ `virtual const FMetasoundFrontendVersion& GetInterfaceVersion() const` — `UE_DEPRECATED(5.3, "Interfaces queries are no longer restricted to a single UObjectRegistryEntry. Options set upon registering interface determines supported UClasses.")`
- L39 _public prototype_ `virtual UClass* GetUClass() const = 0;` — UClass associated with this entry.
- L42 _public prototype_ `virtual bool IsChildClass(const UObject* InObject) const = 0;` — Returns true if the UObject is of a Class which is a child of this UClass associated with this entry.
- L45 _public prototype_ `virtual bool IsChildClass(const UClass* InClass) const = 0;` — Returns true if the UClass is a child of this UClass associated with this entry.
- L48 _public prototype_ `virtual bool IsAssetType() const = 0;` — Returns whether entry's class is a serialized asset or a transient type
- L51 _public prototype_ `virtual FMetasoundAssetBase* Cast(UObject* InObject) const = 0;` — Attempts to cast the UObject to an FMetasoundAssetBase
- L54 _public prototype_ `virtual const FMetasoundAssetBase* Cast(const UObject* InObject) const = 0;` — Attempts to cast the UObject to an FMetasoundAssetBase
- L58 _public function_ `virtual UObject* NewObject(UPackage* InPackage, const FName& InName) const` — `UE_DEPRECATED(5.3, "NewObject is now done via the MetaSoundBuilder system. Attempting to create a MetaSound via this call will now always fail.")` — Creates a new object of the UClass type.
- L65 _private prototype_ `IMetasoundUObjectRegistryEntry() = default;`

#### class `Metasound::TMetasoundUObjectRegistryEntry`  
`template<typename UClassType> class TMetasoundUObjectRegistryEntry : public IMetasoundUObjectRegistryEntry`  
_L78-149_
- inherits: `IMetasoundUObjectRegistryEntry`
- desc: An entry into the Metasound-UObject registry. @Tparam UClassType A class which derives from UObject and IMetaSoundDocumentInterface. @Tparam IsAssetType If true, type derives from FMetasoundAssetBase and is considered a serializable, playable asset.
- L85 _public prototype_ `TMetasoundUObjectRegistryEntry() = default;`
- L86 _public prototype_ `virtual ~TMetasoundUObjectRegistryEntry() = default;`
- L88 _public function_ `UClass* GetUClass() const override`
- L93 _public function_ `virtual bool IsChildClass(const UObject* InObject) const override`
- L102 _public function_ `virtual bool IsChildClass(const UClass* InClass) const override`
- L111 _public function_ `virtual bool IsAssetType() const override`
- L116 _public function_ `virtual FMetasoundAssetBase* Cast(UObject * InObject) const override`
- L133 _public function_ `virtual const FMetasoundAssetBase* Cast(const UObject* InObject) const override`

#### class `Metasound::IMetasoundUObjectRegistry`  
`class IMetasoundUObjectRegistry`  
_L157-207_
- desc: IMetasoundUObjectRegistry contains IMetasoundUObjectRegistryEntries. Registered UObject classes can utilize the Metasound Editor. It also enables the creation of a UObject directly from a FMetasoundFrontendDocument.
- L160 _public prototype_ `virtual ~IMetasoundUObjectRegistry() = default;`
- L163 _public prototype_ `static IMetasoundUObjectRegistry& Get();` — Return static singleton instance of the registry.
- L166 _public prototype_ `virtual void RegisterUClass(TUniquePtr<IMetasoundUObjectRegistryEntry>&& InEntry) = 0;` — Adds an entry to the registry.
- L169 _public function_ `virtual void RegisterUClassInterface(TUniquePtr<IMetasoundUObjectRegistryEntry>&& InEntry)` — `UE_DEPRECATED(5.3, "Interfaces are no longer registered with the UObject registry as interfaces now support multiple UClasses that are registered with the interface registry.")`
- L172 _public function_ `virtual TArray<const IMetasoundUObjectRegistryEntry*> FindInterfaceEntriesByName(FName InName) const` — `UE_DEPRECATED(5.3, "Interfaces are no longer registered with the UObject registry as interfaces now support multiple UClasses that are registered with the interface registry.")`
- L175 _public function_ `virtual TArray<UClass*> FindSupportedInterfaceClasses(const FMetasoundFrontendVersion& InInterfaceVersion) const` — `UE_DEPRECATED(5.3, "Interfaces are no longer registered with the UObject registry as interfaces now support multiple UClasses that are registered with the interface registry.")`
- L187 _public function_ `virtual UObject* NewObject(UClass* InClass, const FMetasoundFrontendDocument& InDocument, const FString& InPath) const` — `UE_DEPRECATED(5.3, "UObject registry form of NewObject is no longer used. Use UMetaSoundBuilderSubsystem to author MetaSounds instead.")` — Creates a new object from a MetaSound document. @param InClass - A registered UClass to create. @param InDocument - The FMetasoundFrontendDocument to use when creating the class. @param InInterfaceVersion - The version of the FMetasoundFrontendClassInterface to use when creating the class. @param InPath - If in editor, the created asset will be stored at this content path. @return A new object. A nullptr on error.
- L190 _public prototype_ `virtual void IterateRegisteredUClasses(TFunctionRef<void(UClass&)> InFunc, bool bAssetTypesOnly = true) const = 0;` — Iterate all registered UClasses that serve as MetaSound assets.
- L193 _public prototype_ `virtual bool IsRegisteredClass(UObject* InObject) const = 0;` — Returns true if the InObject is of a class or child class which is registered.
- L196 _public prototype_ `virtual bool IsRegisteredClass(const UClass& InClass) const = 0;` — Returns true if the InClass matches a class or child class which is registered.
- L201 _public prototype_ `virtual FMetasoundAssetBase* GetObjectAsAssetBase(UObject* InObject) const = 0;` — Returns casts the UObject to a FMetasoundAssetBase if the UObject is of a registered type. If the UObject's UClass is not registered, then a nullptr is returned.
- L206 _public prototype_ `virtual const FMetasoundAssetBase* GetObjectAsAssetBase(const UObject* InObject) const = 0;` — Returns casts the UObject to a FMetasoundAssetBase if the UObject is of a registered type. If the UObject's UClass is not registered, then a nullptr is returned.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METASOUNDENGINE_API`
- L19 _namespace_ `namespace Metasound`

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundWave.h` (Public)


#### struct `Metasound::TIsExplicit`  
`template <> struct TIsExplicit<FWaveAsset>`  
_L22-25_
- desc: Helper utility to test if exact types are required for a datatype.
- L24 _public member_ `static constexpr bool Value = true;`

#### class `Metasound::FWaveAsset`  
`class FWaveAsset`  
_L28-75_
- desc: Metasound data type that holds onto a shared ptr. Mostly used as a placeholder until we have a proper proxy type.
- L31 _private member_ `TSharedPtr<FSoundWaveProxy, ESPMode::ThreadSafe> SoundWaveProxy;` — todo: this can be TSharedPtr<const FSoundWaveProxy> once depprecated functions are removed
- L35 _public prototype_ `FWaveAsset() = default;`
- L36 _public prototype_ `FWaveAsset(const FWaveAsset&) = default;`
- L37 _public prototype_ `FWaveAsset& operator=(const FWaveAsset& Other) = default;`
- L39 _public prototype_ `FWaveAsset(const TSharedPtr<const Audio::IProxyData>& InInitData);`
- L41 _public prototype_ `bool IsSoundWaveValid() const;`
- L44 _public function_ `const FSoundWaveProxyPtr& GetSoundWaveProxy() const` — `UE_DEPRECATED(5.8, "Use GetWaveProxy() instead, mutable proxy access is deprecated")`
- L49 _public function_ `const TSharedPtr<const FSoundWaveProxy> GetWaveProxy() const`
- L54 _public function_ `const FSoundWaveProxy* operator->() const`
- L60 _public function_ `FSoundWaveProxy* operator->()` — `UE_DEPRECATED(5.8, "Use GetWaveProxy() for non-const objects instead. (mutable proxy access is deprecated)")`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METASOUNDENGINE_API`
- L14 _namespace_ `namespace Metasound`
- L18 _typedef_ `typedef TDataReadReference<FWaveAsset> FWaveAssetReadRef;` (scope `Metasound`)
- L65 _function_ `friend inline uint32 GetTypeHash(const Metasound::FWaveAsset& InWaveAsset)` (scope `Metasound`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngine/Public/MetasoundWaveTable.h` (Public)


#### class `Metasound::FWaveTableBankAsset`  
`class FWaveTableBankAsset`  
_L22-88_
- L24 _private member_ `FWaveTableBankAssetProxyPtr Proxy;`
- L27 _public function_ `FWaveTableBankAsset() : Proxy(nullptr)`
- L32 _public function_ `FWaveTableBankAsset(const FWaveTableBankAsset& InOther) : Proxy(InOther.Proxy)`
- L37 _public function_ `FWaveTableBankAsset& operator=(const FWaveTableBankAsset& InOther)`
- L43 _public function_ `FWaveTableBankAsset& operator=(FWaveTableBankAsset&& InOther)`
- L49 _public function_ `FWaveTableBankAsset(const TSharedPtr<Audio::IProxyData>& InInitData)`
- L60 _public function_ `bool IsValid() const`
- L65 _public function_ `const FWaveTableBankAssetProxyPtr& GetProxy() const`
- L70 _public function_ `const FWaveTableBankAssetProxy* operator->() const`
- L75 _public function_ `FWaveTableBankAssetProxy* operator->()`

#### struct `Metasound::TEnableAutoArrayTypeRegistration`  
`template<> struct TEnableAutoArrayTypeRegistration<WaveTable::FWaveTable>`  
_L92-95_
- desc: Disable arrays of WaveTables (as of addition, not supported by UX). Must be defined prior to DataType declaration macro below.
- L94 _public member_ `static constexpr bool Value = false;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Metasound`
- L18 _typedef_ `using FWaveTableBankAssetReadRef = TDataReadReference<FWaveTableBankAsset>;` (scope `Metasound`)
- L19 _typedef_ `using FWaveTableReadRef = TDataReadReference<WaveTable::FWaveTable>;` (scope `Metasound`)
- L20 _typedef_ `using FWaveTableWriteRef = TDataWriteReference<WaveTable::FWaveTable>;` (scope `Metasound`)
- L80 _function_ `friend inline uint32 GetTypeHash(const Metasound::FWaveTableBankAsset& InWaveTableBankAsset)` (scope `Metasound`)
