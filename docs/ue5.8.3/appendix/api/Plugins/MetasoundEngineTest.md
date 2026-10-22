# Plugins / MetasoundEngineTest

- module root: `Plugins/Runtime/Metasound/Source/MetasoundEngineTest`
- headers: 4; symbols: 112
- symbol kinds: class=1, externvar=6, function=5, macro=2, member=14, namespace=15, prototype=62, struct=6, typedef=1
- PrivateDependencyModuleNames: AudioChannelAgnosticCore, AudioExtensions, AudioMixer, AutomationDriver, CQTest, Core, CoreUObject, Engine, InputCore, MetasoundEditor, Projects, PropertyEditor, SignalProcessing, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: MetasoundEngine, MetasoundFrontend, MetasoundGenerator, MetasoundGraphCore, MetasoundStandardNodes

### `Plugins/Runtime/Metasound/Source/MetasoundEngineTest/Private/EngineTestMetaSoundAutomatedNodeTest.h` (Private)


#### struct `Metasound::EngineTest::IDataReferenceAnalyzer`  
`struct IDataReferenceAnalyzer`  
_L48-55_
- desc: Interface for data reference analyzers.
- L50 _public prototype_ `virtual ~IDataReferenceAnalyzer() = default;`
- L51 _public prototype_ `virtual FAnyDataReference Copy(const FAnyDataReference& InDataRef) const = 0;`
- L52 _public prototype_ `virtual bool IsEqual(const FAnyDataReference& InLHS, const FAnyDataReference& InRHS) const = 0;`
- L53 _public prototype_ `virtual bool IsValid(const FAnyDataReference& InDataRef) const = 0;`
- L54 _public prototype_ `virtual FString ToString(const FAnyDataReference& InDataRef) const = 0;`

#### struct `Metasound::EngineTest::FOutputVertexDataTestController`  
`struct FOutputVertexDataTestController`  
_L58-91_
- desc: Convenience class for setting node input data reference values to default, min, max or random values.
- L78 _public prototype_ `FOutputVertexDataTestController( const FOutputVertexInterface& InOutputInterface, const FOutputVertexInterfaceData& InOutputData);`
- L80 _public prototype_ `int32 GetNumAnalyzableOutputs() const;`
- L82 _public prototype_ `bool AreAllAnalyzableOutputsValid() const;`
- L84 _public prototype_ `void CaptureCurrentOutputValues();`
- L86 _public prototype_ `bool AreAllOutputValuesEqualToCapturedValues() const;`
- L90 _private member_ `TArray<FAnalyzableOutput> AnalyzableOutputs;`

#### struct `Metasound::EngineTest::FOutputVertexDataTestController::FAnalyzableOutput`  
`struct FAnalyzableOutput`  
_L60-76_
- L62 _public member_ `FAnyDataReference CapturedValue;`
- L63 _public member_ `FAnyDataReference DataReference;`
- L64 _public member_ `FVertexName VertexName;`
- L65 _public member_ `TSharedPtr<const IDataReferenceAnalyzer> DataReferenceAnalyzer;`
- L67 _public prototype_ `void CaptureValue();`
- L69 _public prototype_ `bool IsDataReferenceValid() const;`
- L71 _public prototype_ `bool IsDataReferenceEqualToCapturedValue() const;`
- L73 _public prototype_ `FString DataReferenceToString() const;`
- L75 _public prototype_ `FString CapturedValueToString() const;`

#### struct `Metasound::EngineTest::IDataReferenceMutator`  
`struct IDataReferenceMutator`  
_L94-104_
- desc: Interface for mutating data references
- L96 _public prototype_ `virtual ~IDataReferenceMutator() = default;`
- L97 _public prototype_ `virtual void SetDefault(const FOperatorSettings& InSettings, const FAnyDataReference& InDataRef) const = 0;`
- L98 _public prototype_ `virtual void SetMax(const FOperatorSettings& InSettings, const FAnyDataReference& InDataRef) const = 0;`
- L99 _public prototype_ `virtual void SetMin(const FOperatorSettings& InSettings, const FAnyDataReference& InDataRef) const = 0;`
- L100 _public prototype_ `virtual void SetRandom(const FOperatorSettings& InSettings, const FAnyDataReference& InDataRef) const = 0;`
- L101 _public prototype_ `virtual FAnyDataReference Copy(const FAnyDataReference& InDataRef) const = 0;`
- L102 _public prototype_ `virtual void SetValue(const FAnyDataReference& InSrcDataRef, const FAnyDataReference& InDstDataRef) const = 0;`
- L103 _public prototype_ `virtual FString ToString(const FAnyDataReference& InDataRef) const = 0;`

#### struct `Metasound::EngineTest::FInputVertexDataTestController`  
`struct FInputVertexDataTestController`  
_L110-135_
- desc: Convenience class for setting node input data reference values to default, min, max or random values.
- L119 _public prototype_ `FInputVertexDataTestController(const FOperatorSettings& InSettings, const FInputVertexInterface& InInputInterface, const FInputVertexInterfaceData& InInputData);`
- L121 _public prototype_ `int32 GetNumMutableInputs() const;`
- L122 _public prototype_ `FInterfaceState GetInterfaceState() const;`
- L124 _public prototype_ `void SetMutableInputsToState(const FInterfaceState& InState);`
- L125 _public prototype_ `void SetMutableInputsToMin();`
- L126 _public prototype_ `void SetMutableInputsToMax();`
- L127 _public prototype_ `void SetMutableInputsToDefault();`
- L128 _public prototype_ `void SetMutableInputsToRandom();`
- L129 _public prototype_ `TArray<FString> GetInputValueStrings() const;`
- L133 _private member_ `FOperatorSettings Settings;`
- L134 _private member_ `TArray<FMutableInput> MutableInputs;`

#### struct `Metasound::EngineTest::FInputVertexDataTestController::FMutableInput`  
`struct FMutableInput`  
_L112-117_
- L114 _public member_ `FAnyDataReference DataReference;`
- L115 _public member_ `FVertexName VertexName;`
- L116 _public member_ `TSharedPtr<const IDataReferenceMutator> DataReferenceMutator;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace Audio`
- L28 _namespace_ `namespace Metasound`
- L36 _namespace_ `namespace Metasound`
- L36 _namespace_ `namespace EngineTest` (scope `Metasound`)
- L39 _prototype_ `Audio::FMixerDevice* GetAudioMixerDevice();` (scope `Metasound::EngineTest`) — Return audio mixer device if one is available
- L42 _prototype_ `FMetasoundEnvironment GetSourceEnvironmentForTest();` (scope `Metasound::EngineTest`) — Create an example environment that generally exists for a UMetaSoundSoruce
- L45 _prototype_ `FString GetPrettyName(const Frontend::FNodeRegistryKey& InRegistryKey);` (scope `Metasound::EngineTest`) — Return string for printing test errors
- L107 _typedef_ `using FInterfaceState = TSortedVertexNameMap<FAnyDataReference>;` (scope `Metasound::EngineTest`) — Captures current data references on interface
- L139 _prototype_ `TUniquePtr<INode> CreateNodeFromRegistry(const Frontend::FNodeRegistryKey& InNodeRegistryKey);` (scope `Metasound::EngineTest`) — Create a node from a node registry key
- L142 _prototype_ `void GetAllRegisteredNodes(TArray<FString>& OutBeautifiedNames, TArray<FString>& OutNodeRegistryKeys, bool bInIncludeDeprecatedNodes);` (scope `Metasound::EngineTest`) — Return an array of all currently registered MetaSound nodes.
- L145 _prototype_ `void GetAllRegisteredNativeNodes(TArray<FString>& OutBeautifiedNames, TArray<FString>& OutNodeRegistryKeys, bool bInIncludeDeprecatedNodes);` (scope `Metasound::EngineTest`) — Return an array of all currently registered native MetaSound nodes.
- L148 _prototype_ `void CreateVariables(const FOperatorSettings& InOperatorSettings, FInputVertexInterfaceData& OutVertexData);` (scope `Metasound::EngineTest`) — Create any variables that exist on the vertex interface.
- L151 _prototype_ `void CreateDefaultsAndVariables(const FOperatorSettings& InOperatorSettings, FInputVertexInterfaceData& OutVertexData);` (scope `Metasound::EngineTest`) — Create default references and variables for the vertex interface data.

### `Plugins/Runtime/Metasound/Source/MetasoundEngineTest/Private/EngineTestMetaSoundBuilder.h` (Private)


#### Free symbols / members of external scopes

- L24 _namespace_ `namespace EngineTestMetaSoundPatchBuilderPrivate`
- L26 _function_ `inline UMetaSoundPatchBuilder& CreatePatchBuilderChecked(FAutomationTestBase& Test, FName BuilderName, const TArray<FName>& InterfaceNamesToAdd)` (scope `EngineTestMetaSoundPatchBuilderPrivate`)
- L42 _function_ `inline UMetaSoundPatch* CreatePatchFromBuilder(FAutomationTestBase& Test, const FString& PatchName, const TArray<FName>& InterfaceNamesToAdd)` (scope `EngineTestMetaSoundPatchBuilderPrivate`)
- L53 _prototype_ `DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FMetaSoundSourceBuilderDisconnectInputLatentCommand, FAutomationTestBase&, Test, UMetaSoundBuilderBase*, Builder, FMetaSoundBuilderNodeInputHandle, InputToDisconnect);`
- L55 _prototype_ `DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FMetaSoundSourceBuilderSetLiteralLatentCommand, FAutomationTestBase&, Test, UMetaSoundBuilderBase*, Builder, FMetaSoundBuilderNodeInputHandle, NodeInput, FMetasoundFrontendLiteral, NewValue);`
- L57 _prototype_ `DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FMetaSoundSourceBuilderRemoveNodeDefaultLiteralLatentCommand, FAutomationTestBase&, Test, UMetaSoundBuilderBase*, Builder, FMetaSoundBuilderNodeInputHandle, NodeInput);`
- L59 _prototype_ `DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FMetaSoundSourceBuilderCreateAndConnectTriGeneratorNodeLatentCommand, FAutomationTestBase&, Test, UMetaSoundSourceBuilder*, Builder, FMetaSoundBuilderNodeInputHandle, AudioOutNodeInput);`
- L61 _prototype_ `DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FBuilderRemoveFromRootLatentCommand, UMetaSoundBuilderBase*, Builder);`

### `Plugins/Runtime/Metasound/Source/MetasoundEngineTest/Private/Interfaces/MetasoundTestInterfaces.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Metasound`
- L9 _namespace_ `namespace Test` (scope `Metasound`)
- L11 _macro_ `#define AUDIO_PARAMETER_INTERFACE_NAMESPACE "UE.Test.Update"`
- L12 _namespace_ `namespace UpdateTestInterface_0_1` (scope `Metasound::Test`)
- L14 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Test::UpdateTestInterface_0_1`)
- L16 _namespace_ `namespace Inputs` (scope `Metasound::Test::UpdateTestInterface_0_1`)
- L18 _externvar_ `const extern FName InputTrigger;` (scope `Metasound::Test::UpdateTestInterface_0_1::Inputs`)
- L21 _namespace_ `namespace Outputs` (scope `Metasound::Test::UpdateTestInterface_0_1`)
- L23 _externvar_ `const extern FName OutputTrigger;` (scope `Metasound::Test::UpdateTestInterface_0_1::Outputs`)
- L26 _prototype_ `Audio::FParameterInterfacePtr CreateInterface(const UClass& InClass);` (scope `Metasound::Test::UpdateTestInterface_0_1`)
- L29 _namespace_ `namespace UpdateTestInterface_0_2` (scope `Metasound::Test`)
- L31 _prototype_ `const FMetasoundFrontendVersion& GetVersion();` (scope `Metasound::Test::UpdateTestInterface_0_2`)
- L33 _namespace_ `namespace Inputs` (scope `Metasound::Test::UpdateTestInterface_0_2`)
- L35 _externvar_ `const extern FName InputTrigger;` (scope `Metasound::Test::UpdateTestInterface_0_2::Inputs`)
- L36 _externvar_ `const extern FName InputFloat;` (scope `Metasound::Test::UpdateTestInterface_0_2::Inputs`)
- L39 _namespace_ `namespace Outputs` (scope `Metasound::Test::UpdateTestInterface_0_2`)
- L41 _externvar_ `const extern FName OutputTrigger;` (scope `Metasound::Test::UpdateTestInterface_0_2::Outputs`)
- L42 _externvar_ `const extern FName OutputFloat;` (scope `Metasound::Test::UpdateTestInterface_0_2::Outputs`)
- L45 _prototype_ `Audio::FParameterInterfacePtr CreateInterface(const UClass& InClass);` (scope `Metasound::Test::UpdateTestInterface_0_2`)

### `Plugins/Runtime/Metasound/Source/MetasoundEngineTest/Public/NodeTestGraphBuilder.h` (Public)


#### class `Metasound::Test::FNodeTestGraphBuilder`  
`class FNodeTestGraphBuilder`  
_L15-222_
- desc: Helper to make testing nodes simpler.
- L18 _public prototype_ `FNodeTestGraphBuilder();`
- L27 _public prototype_ `Frontend::FNodeHandle AddNode(const FNodeClassName& ClassName, int32 MajorVersion) const;` — Add a node to the graph @param ClassName		Class name of the node to add @param MajorVersion	Major version of the node to add @return				NodeHandle of the added node
- L35 _public prototype_ `Frontend::FNodeHandle GetInput(const FName& Name) const;` — Add an input node from the graph by name @param Name			The name of the input node to get @return				NodeHandle, which can be invalid if an input with the given name doesn't exist in the graph
- L43 _public prototype_ `Frontend::FNodeHandle GetOutput(const FName& Name) const;` — Add an output node from the graph by name @param Name			The name of the output node to get @return				NodeHandle, which can be invalid if an input with the given name doesn't exist in the graph
- L53 _public prototype_ `Frontend::FNodeHandle AddInput( const FName& InputName, const FName& TypeName, EMetasoundFrontendVertexAccessType AccessType = EMetasoundFrontendVertexAccessType::Reference) const;` — Add an input node from the graph by name, type, and access type @param InputName		The name of the input node to add @param TypeName		The type of the node to add (use: GetMetasoundDataTypeName<DataType>()); @param AccessType		Whether the node should be a Value, Reference, or Unset type @return				NodeHandle of the added node, can be invalid if failed to add
- L66 _public function_ `template<typename DataType> Frontend::FNodeHandle AddConstructorInput(const FName& InputName, const DataType& Value) const` — Add a constructor input node from the graph by name and type @param InputName		The name of the input node to add @param Value			The value for the node to hold. The type of the value will determine the type for the node. @return				NodeHandle of the added node, can be invalid if failed to add
- L86 _public prototype_ `Frontend::FNodeHandle AddOutput(const FName& OutputName, const FName& TypeName);` — Add a data reference output node from the graph by name and type @param InputName		The name of the output node to add @param TypeName		The type for the node to reference @return				NodeHandle of the added node, can be invalid if failed to add
- L98 _public function_ `template <typename DataType> Frontend::FNodeHandle AddAndConnectConstructorInput(const Frontend::FNodeHandle& NodeToConnect, const FName& InputName, const DataType& Value, const FName& NodeName = NAME_None) const` — Adds a constructor input node to the graph and connects it as an input to the NodeToConnect @param NodeToConnect	The node to connect the newly added constructor input node to @param InputName		The name of the input pin to connect the node to, and the name to use for the new node. @param Value			The value for the node to hold. The type of the value will determine the type for the node. @param NodeName		Optional name to use for the created constructor input node @return				NodeHandle of the added node, can be invalid if failed to add
- L119 _public function_ `template<typename InputDataType, typename LiteralDataType> Frontend::FNodeHandle AddAndConnectConstructorInput( const Frontend::FNodeHandle& NodeToConnect, const FName& InputName, const LiteralDataType& Value, const FName& NodeName = NAME_None) const` — Adds a constructor input node to the graph and connects it as an input to the NodeToConnect. This version handles input data types that don't have direct support in FLiteral. @tparam InputDataType The data type of the input vertex @tparam LiteralDataType The data type of the literal used to set the input vertex @param NodeToConnect The node to connect the newly added constructor input node to @param InputName The name of the input pin to connect the node to, and the name to use for the new node. @param Value The value for the node to hold. The type of the value will determine the type for the node. @param NodeName Optional name to use for the created constructor input node @return NodeHandle of the added node, can be invalid if failed to add
- L149 _public prototype_ `bool AddAndConnectDataReferenceInputs(const Frontend::FNodeHandle& NodeHandle);` — Adds data reference input nodes for each input on the NodeHandle and connects them to the inputs of the NodeHandle @param NodeHandle		The node to connect the input reference nodes to @return				whether all the nodes were successfully created and connected
- L160 _public prototype_ `Frontend::FNodeHandle AddAndConnectDataReferenceInput(const Frontend::FNodeHandle& NodeToConnect, const FName& InputName, const FName& TypeName, const FName& NodeName = NAME_None) const;` — Adds a data reference input node with InputName and connects it to the node's input with the same name @param NodeToConnect	The node to connect the newly added constructor input node to @param InputName		The name of the input pin to connect the node to, and the name to use for the new node. @param TypeName		The type name of the data reference @param NodeName		Optional name to use for the created data reference input node @return				NodeHandle of the added node, can be invalid if failed to add
- L170 _public prototype_ `Frontend::FNodeHandle AddAndConnectDataReferenceOutput(const Frontend::FNodeHandle& NodeToConnect, const FName& OutputName, const FName& TypeName, const FName& NodeName = NAME_None);` — Adds a data reference output node with OutputName and connects it to the node's output with the same name @param NodeToConnect	The node to connect the newly added constructor input node to @param InputName		The name of the output pin to connect the node to, and the name to use for the new node. @param TypeName		The type name of the data reference @param NodeName		Optoinal name to use for the created data reference output node @return				NodeHandle of the added node, can be invalid if failed to add
- L179 _public prototype_ `TUniquePtr<FMetasoundGenerator> BuildGenerator(FSampleRate SampleRate = 48000, int32 SamplesPerBlock = 256) const;` — Call last to create a generator from the graph constructed using the other method. @param SampleRate			The Sample Rate the generator should render audio at @param SamplesPerBlock	The number of samples to render per block @return					A unique pointer to the Metasound Generator created
- L190 _public prototype_ `static TUniquePtr<FMetasoundGenerator> MakeSingleNodeGraph( const FNodeClassName& ClassName, int32 MajorVersion, FSampleRate SampleRate = 48000, int32 SamplesPerBlock = 256);` — Helper that will add a single node, wire up the node's inputs and outputs, and hand back the graph's operator @param ClassName			The class name of the node to add @param MajorVersion		The version of the node to use @param SampleRate			The sample rate the generator should render audio at @param SamplesPerBlock	The number of samples to render per block @return					A unique pointer to the Metasound Generator created
- L205 _public prototype_ `static bool ConnectNodes(const Frontend::FNodeHandle& LeftNode, const FName& OutputName, const Frontend::FNodeHandle& RightNode, const FName& InputName);` — Connects an Input (Left) Node's output with name OutputName to another (Right) node's input with name InputName @param LeftNode		The "left hand" side node to connect from @param OutputName		The name of the output pin to connect from the left node @param RightNode		The "right hand" side node to connect to @param InputName		The name of the input pin to connect to the right node @bool					true if able to connect the nodes (ie. all nodes were valid, all input/outputs were valid)
- L215 _public prototype_ `static bool ConnectNodes(const Frontend::FNodeHandle& LeftNode, const Frontend::FNodeHandle& RightNode, const FName& InputOutputName);` — Connects an Input (Left) Node's output with name OutputName to another (Right) node's input with name InputName @param LeftNode			The "left hand" side node to connect from @param RightNode			The "right hand" side node to connect to @param InputOutputName	The name of the input pin to connect to the right node @bool						true if able to connect the nodes (ie. all nodes were valid, all input/outputs were valid)
- L218 _private member_ `FMetasoundFrontendDocument Document;`
- L219 _private member_ `Frontend::FDocumentHandle DocumentHandle = Frontend::IDocumentController::GetInvalidHandle();`
- L220 _private member_ `Frontend::FGraphHandle RootGraph = Frontend::IGraphController::GetInvalidHandle();`
- L221 _private member_ `TArray<FVertexName> AudioOutputNames;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METASOUNDENGINETEST_API`
- L12 _namespace_ `namespace Metasound`
- L12 _namespace_ `namespace Test` (scope `Metasound`)
