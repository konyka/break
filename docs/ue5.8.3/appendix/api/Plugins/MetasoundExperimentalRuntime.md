# Plugins / MetasoundExperimentalRuntime

- module root: `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalRuntime`
- headers: 12; symbols: 110
- symbol kinds: class=5, enum=4, enumerator=11, function=1, member=30, namespace=8, prototype=41, struct=8, typedef=2
- PrivateDependencyModuleNames: AudioChannelAgnosticCore, Core, MetasoundFrontend, MetasoundGraphCore, MetasoundStandardNodes, Projects, Serialization, SignalProcessing
- PublicDependencyModuleNames: AudioExperimentalRuntime, Core, CoreUObject, MetasoundFrontend, MetasoundGraphCore

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalRuntime/Private/MetasoundCatBreakNode.h` (Private)


#### struct `FMetaSoundCatBreakNodeConfiguration`  
`struct FMetaSoundCatBreakNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L12-32_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- L16 _public prototype_ `FMetaSoundCatBreakNodeConfiguration() = default;`
- L19 _public member_ `FName Format = TEXT("Cat` — `UPROPERTY(EditAnywhere, Category = General, meta = (GetOptions="MetasoundCatCastingOptionsHelper.GetCastingOptions_NoAbstract"))`
- L22 _public member_ `EMetasoundCatCastingMethod TranscodeMethod = EMetasoundCatCastingMethod::ChannelDrop;` — `UPROPERTY(EditAnywhere, Category = General)`
- L25 _public member_ `EMetasoundChannelMapMonoUpmixMethod MixMethod = EMetasoundChannelMapMonoUpmixMethod::EqualPower;` — `UPROPERTY(EditAnywhere, Category = General, meta = (EditCondition = "TranscodeMethod == EMetasoundCatCastingMethod::MixUpOrDown", EditConditionHides))`
- L28 _public prototype_ `virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const override;` — Get the current interface for the class based upon the node extension
- L31 _public prototype_ `virtual TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;` — Pass data down to the operator.

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalRuntime/Private/MetasoundCatCastingNode.h` (Private)


#### class `UMetasoundCatCastingOptionsHelper`  
`class UMetasoundCatCastingOptionsHelper : public UObject`  
_L16-34_
- reflection: `UCLASS()`
- inherits: `UObject`
- L21 _private prototype_ `static TArray<FPropertyTextFName> GetCastingOptions();` — `UFUNCTION()`
- L24 _private prototype_ `static TArray<FPropertyTextFName> GetCastingOptions_NoAbstract();` — `UFUNCTION()`
- L28 _private prototype_ `static TArray<FPropertyTextFName> GetCastingOptions_DiscreteOnly();` — `UFUNCTION()` — Only discrete (mixer-compatible) formats. Excludes soundfield, ambisonics, composite.
- L33 _private prototype_ `static TArray<FPropertyTextFName> GetCastingOptions_AudioMixerOnly();` — `UFUNCTION()` — Only the standard AudioMixer formats: Mono 1.0, Stereo 2.0, Quad 4.0, 5.1, 7.1. For MetaSound Source custom format dropdown — must match what AudioMixer can interleave.

#### enum `EMetasoundCatCastingMethod`  
`enum class EMetasoundCatCastingMethod : uint8`  
_L37-41_
- reflection: `UENUM()`
- L39 _public enumerator_ `ChannelDrop = static_cast<uint8>(Audio::EChannelTranscodeMethod::ChannelDrop)`
- L40 _public enumerator_ `MixUpOrDown = static_cast<uint8>(Audio::EChannelTranscodeMethod::MixUpOrDown)`

#### enum `EMetasoundChannelMapMonoUpmixMethod`  
`enum class EMetasoundChannelMapMonoUpmixMethod : uint8`  
_L44-49_
- reflection: `UENUM()`
- L46 _public enumerator_ `Linear = static_cast<uint8>(Audio::EChannelMapMonoUpmixMethod::Linear)`
- L47 _public enumerator_ `EqualPower = static_cast<uint8>(Audio::EChannelMapMonoUpmixMethod::EqualPower)`
- L48 _public enumerator_ `FullVolume = static_cast<uint8>(Audio::EChannelMapMonoUpmixMethod::FullVolume)`

#### struct `FMetaSoundCatCastingNodeConfiguration`  
`struct FMetaSoundCatCastingNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L52-72_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- L56 _public prototype_ `FMetaSoundCatCastingNodeConfiguration() = default;`
- L59 _public member_ `FName ToType = TEXT("Mon` — `UPROPERTY(EditAnywhere, Category = General, meta = (GetOptions="MetasoundCatCastingOptionsHelper.GetCastingOptions_NoAbstract"))`
- L62 _public member_ `EMetasoundCatCastingMethod TranscodeMethod = EMetasoundCatCastingMethod::ChannelDrop;` — `UPROPERTY(EditAnywhere, Category = General)`
- L65 _public member_ `EMetasoundChannelMapMonoUpmixMethod MixMethod = EMetasoundChannelMapMonoUpmixMethod::EqualPower;` — `UPROPERTY(EditAnywhere, Category = General, meta = (EditCondition = "TranscodeMethod == EMetasoundCatCastingMethod::MixUpOrDown", EditCOonditionHides))`
- L68 _public prototype_ `virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const override;` — Get the current interface for the class based upon the node extension
- L71 _public prototype_ `virtual TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;` — Pass data down to the operator.

#### class `Metasound::FCatCastingOperator`  
`class FCatCastingOperator final : public TExecutableOperator<FCatCastingOperator>`  
_L83-112_
- inherits: `TExecutableOperator<FCatCastingOperator>`
- L86 _public prototype_ `FCatCastingOperator(const FBuildOperatorParams& InParams, FChannelAgnosticTypeReadRef&& InInputCat, const CatCastingPrivate::FCatCastingOperatorData& InData, const FName InConcreteName);`
- L87 _public prototype_ `virtual ~FCatCastingOperator() override = default;`
- L89 _public prototype_ `static FVertexInterface GetInterface(const FName InSrc, const FName InDst);`
- L91 _public prototype_ `static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults);`
- L93 _public prototype_ `virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override;`
- L95 _public prototype_ `virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override;`
- L97 _public prototype_ `void Reset(const FResetParams& InParams);`
- L99 _public prototype_ `void Execute();`
- L101 _public prototype_ `static FNodeClassMetadata GetNodeInfo();`
- L104 _private typedef_ `using FTranscoder = Audio::ChannelAgnosticTranscoder::FTranscoder;`
- L105 _private member_ `FChannelAgnosticTypeReadRef InputFrom;`
- L106 _private member_ `FName ToFormatName;`
- L107 _private member_ `TDataWriteReference<FChannelAgnosticType> OutputCastResult;`
- L108 _private member_ `FOperatorSettings Settings;`
- L109 _private member_ `FTranscoder Transcoder;`
- L110 _private member_ `Audio::EChannelTranscodeMethod TranscodeMethod;`
- L111 _private member_ `Audio::EChannelMapMonoUpmixMethod MixMethod;`

#### Free symbols / members of external scopes

- L74 _namespace_ `namespace Metasound`
- L76 _namespace_ `namespace CatCastingPrivate` (scope `Metasound`)
- L114 _typedef_ `using FCatCastingNode = TNodeFacade<FCatCastingOperator>;` (scope `Metasound`)

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalRuntime/Private/MetasoundCatConversionNode.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace Metasound`
- L7 _prototype_ `void RegisterCatConvertNode();` (scope `Metasound`)

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalRuntime/Private/MetasoundCatMakeNode.h` (Private)


#### struct `FMetaSoundCatMakeNodeConfiguration`  
`struct FMetaSoundCatMakeNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L11-25_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- L15 _public prototype_ `FMetaSoundCatMakeNodeConfiguration() = default;`
- L18 _public member_ `FName Format = TEXT("Cat` — `UPROPERTY(EditAnywhere, Category = General, meta = (GetOptions="MetasoundCatCastingOptionsHelper.GetCastingOptions_NoAbstract"))`
- L21 _public prototype_ `virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const override;` — Get the current interface for the class based upon the node extension
- L24 _public prototype_ `virtual TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;` — Pass data down to the operator.

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalRuntime/Private/MetasoundCatMixerNode.h` (Private)


#### enum `EMetasoundMixerFormatChoosingMethod`  
`enum class EMetasoundMixerFormatChoosingMethod: uint8`  
_L13-19_
- reflection: `UENUM()`
- L15 _public enumerator_ `HighestInput UMETA(DisplayName = "Highest Num Channels", ToolTip = "Output will be the MAX Channel count of the input channel")`
- L16 _public enumerator_ `LowestInput UMETA(DisplayName = "Lowest Num Channels", ToolTip = "Output will be the MIN Channel count of the input channel")`
- L17 _public enumerator_ `MetasoundOutput UMETA(DisplayName = "Metasound Output", ToolTip = "Output will match the Metasound Output setting")`
- L18 _public enumerator_ `Custom UMETA(DisplayName = "Custom", ToolTip = "Custom mix format")`

#### struct `FMetaSoundCatMixingNodeConfiguration`  
`struct FMetaSoundCatMixingNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L22-45_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- L26 _public prototype_ `FMetaSoundCatMixingNodeConfiguration() = default;`
- L29 _public member_ `EMetasoundMixerFormatChoosingMethod FormatChoosingMethod = EMetasoundMixerFormatChoosingMethod::HighestInput;` — `UPROPERTY(EditAnywhere, Category = General, DisplayName = "Mix Format Method")`
- L32 _public member_ `EMetasoundChannelMapMonoUpmixMethod ChannelMapMonoUpmixMethod = EMetasoundChannelMapMonoUpmixMethod::EqualPower;` — `UPROPERTY(EditAnywhere, Category = General, meta=(EditCondition = "CatCastingMethod == EMetasoundCatCastingMethod::MixUpOrDown", EditConditionHides))`
- L35 _public member_ `EMetasoundCatCastingMethod CatCastingMethod = EMetasoundCatCastingMethod::ChannelDrop;` — `UPROPERTY(EditAnywhere, Category = General)`
- L38 _public member_ `FName CustomMixFormat = TEXT("Cat` — `UPROPERTY(EditAnywhere, Category = General, meta = (GetOptions="MetasoundCatCastingOptionsHelper.GetCastingOptions", EditCondition = "FormatChoosingMethod == EMetasoundMixerFormatChoosingMethod::Custom", EditConditionHides))`
- L41 _public member_ `int32 NumInputs = 1;` — `UPROPERTY(EditAnywhere, Category = General, meta = (ClampMin=1, ClampMax=100))`
- L43 _public prototype_ `virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const override;`
- L44 _public prototype_ `virtual TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;`

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalRuntime/Private/MetasoundCatTestingNode.h` (Private)


#### struct `FMetaSoundCatTestingNodeConfiguration`  
`struct FMetaSoundCatTestingNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L11-25_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- L15 _public prototype_ `FMetaSoundCatTestingNodeConfiguration() = default;`
- L18 _public member_ `FName ToType = TEXT("Mon` — `UPROPERTY(EditAnywhere, Category = General, meta = (GetOptions="MetasoundCatCastingOptionsHelper.GetCastingOptions"))`
- L21 _public prototype_ `virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const override;` — Get the current interface for the class based upon the node extension
- L24 _public prototype_ `virtual TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;` — Pass data down to the operator.

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalRuntime/Private/MetasoundExamplePolymorphicDataTypeNode.h` (Private)
_(no declarations extracted)_

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalRuntime/Private/MetasoundExampleWeightedSumNode.h` (Private)
_(no declarations extracted)_

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalRuntime/Private/MetasoundExperimentalRuntimeModule.h` (Private)


#### class `FMetasoundExperimentalRuntimeModule`  
`class FMetasoundExperimentalRuntimeModule : public IModuleInterface`  
_L9-19_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _private member_ `TArray<FName> RegisteredDataSchemas;`

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalRuntime/Public/MetasoundCatPannerNode.h` (Public)


#### class `UMetasoundCatAzimuthalChannelOptionsHelper`  
`class UMetasoundCatAzimuthalChannelOptionsHelper : public UObject`  
_L12-18_
- reflection: `UCLASS()`
- inherits: `UObject`
- L17 _private prototype_ `static TArray<FPropertyTextFName> GetAzimuthalChannelOptions();` — `UFUNCTION()`

#### enum `ECatPannerMethod`  
`enum class ECatPannerMethod : uint8`  
_L21-28_
- reflection: `UENUM()`
- L24 _public enumerator_ `EqualPower` — Panning is done using equal-power law
- L27 _public enumerator_ `Linear` — Panning is done linearly

#### struct `FMetaSoundCatPannerNodeConfiguration`  
`struct FMetaSoundCatPannerNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L32-51_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- L36 _public prototype_ `FMetaSoundCatPannerNodeConfiguration() = default;`
- L40 _public member_ `FName PanToType = TEXT("Cat` — `UPROPERTY(EditAnywhere, Category = General, meta = (GetOptions="MetasoundCatAzimuthalChannelOptionsHelper.GetAzimuthalChannelOptions"))` — What the CAT output type is. Only azimuthal discrete channel types supported.
- L44 _public member_ `ECatPannerMethod PanningMethod = ECatPannerMethod::EqualPower;` — `UPROPERTY(EditAnywhere, Category = General)` — What panning method to use. Panning method defines the mapping function of gains between pair-wise channels.
- L47 _public prototype_ `virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const override;` — Get the current interface for the class based upon the node extension
- L50 _public prototype_ `virtual TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;` — Pass data down to the operator.

#### Free symbols / members of external scopes

- L54 _namespace_ `namespace Metasound`
- L57 _prototype_ `float NormalizedAzimuthToDegrees(const float InNormalizedAzimuth);` (scope `Metasound`) — Normalization utility.

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalRuntime/Public/MetasoundExampleNodeConfiguration.h` (Public)


#### struct `FMetaSoundExperimentalExampleNodeConfiguration`  
`struct FMetaSoundExperimentalExampleNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L16-36_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- L20 _public prototype_ `FMetaSoundExperimentalExampleNodeConfiguration();`
- L23 _public member_ `FString String;` — `UPROPERTY(EditAnywhere, Category = General)`
- L26 _public member_ `uint32 NumInputs;` — `UPROPERTY(EditAnywhere, Category = General, meta = (ClampMin = "1", ClampMax = "1000"))`
- L29 _public member_ `uint32 NumOutputs;` — `UPROPERTY(EditAnywhere, Category = General, meta = (ClampMin = "1", ClampMax = "1000"))`
- L32 _public prototype_ `virtual TInstancedStruct<FMetasoundFrontendClassInterface> OverrideDefaultInterface(const FMetasoundFrontendClass& InNodeClass) const;` — Get the current interface for the class based upon the node extension
- L35 _public prototype_ `virtual TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;` — Pass data down to the operator.

#### class `Metasound::Experimental::FWidgetExampleOperatorData`  
`class FWidgetExampleOperatorData : public TOperatorData<FWidgetExampleOperatorData>`  
_L40-51_
- inherits: `TOperatorData<FWidgetExampleOperatorData>`
- L43 _public member_ `static const FLazyName OperatorDataTypeName;`
- L45 _public function_ `FWidgetExampleOperatorData(const float& InFloat) : MyFloat(InFloat)`
- L50 _public member_ `float MyFloat;`

#### struct `FMetaSoundWidgetExampleNodeConfiguration`  
`struct FMetaSoundWidgetExampleNodeConfiguration : public FMetaSoundFrontendNodeConfiguration`  
_L55-68_
- reflection: `USTRUCT()`
- inherits: `FMetaSoundFrontendNodeConfiguration`
- L59 _public prototype_ `FMetaSoundWidgetExampleNodeConfiguration();`
- L62 _public member_ `float MyFloat;` — `UPROPERTY(EditAnywhere, Category = General)`
- L64 _public prototype_ `TSharedPtr<const Metasound::IOperatorData> GetOperatorData() const override;`
- L67 _private member_ `mutable TSharedPtr<Metasound::Experimental::FWidgetExampleOperatorData> OperatorData;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Metasound`
- L10 _namespace_ `namespace Experimental` (scope `Metasound`)
- L38 _namespace_ `namespace Metasound`
- L38 _namespace_ `namespace Experimental` (scope `Metasound`)

### `Plugins/Experimental/MetasoundExperimental/Source/MetasoundExperimentalRuntime/Public/MetasoundFormatAgnosticType.h` (Public)
_(no declarations extracted)_
