# Plugins / NNERuntimeBasicCpu

- module root: `Plugins/Experimental/NNERuntimeBasicCpu/Source/NNERuntimeBasicCpu`
- headers: 4; symbols: 157
- symbol kinds: class=6, delegate=1, enum=4, enumerator=11, function=5, macro=2, member=27, namespace=10, prototype=87, struct=2, typedef=2
- PrivateDependencyModuleNames: CoreUObject
- PublicDependencyModuleNames: Core, Engine, NNE

### `Plugins/Experimental/NNERuntimeBasicCpu/Source/NNERuntimeBasicCpu/Private/NNERuntimeBasicCpu.h` (Private)


#### class `UNNERuntimeBasicCpuImpl`  
`class UNNERuntimeBasicCpuImpl : public UObject, public INNERuntime, public INNERuntimeCPU`  
_L25-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,INNERuntime,INNERuntimeCPU`
- desc: This plugin is a basic, performant, cross-platform CPU runtime for NNE that supports simple models such as MLPs. To use this runtime, the custom ".ubnne" file format is used, which can be exported from python using the functions in the provided "nne_runtime_basic_cpu.py" found in the "Content" folder of this plugin. The idea behind this plugin is not to be a general purpose runtime, but rather to provide performant cross-platform implementations for simple CPU models such as MLPs with minimal overhead and memory usage.
- L31 _public function_ `virtual FString GetRuntimeName() const override`
- L33 _public prototype_ `virtual ECanCreateModelDataStatus CanCreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L34 _public prototype_ `virtual TSharedPtr<UE::NNE::FSharedModelData> CreateModelData(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) override;`
- L35 _public prototype_ `virtual FString GetModelDataIdentifier(const FString& FileType, TConstArrayView64<uint8> FileData, const TMap<FString, TConstArrayView64<uint8>>& AdditionalFileData, const FGuid& FileId, const ITargetPlatform* TargetPlatform) const override;`
- L37 _public prototype_ `virtual ECanCreateModelCPUStatus CanCreateModelCPU(const TObjectPtr<UNNEModelData> ModelData) const override;`
- L38 _public prototype_ `virtual TSharedPtr<UE::NNE::IModelCPU> CreateModelCPU(const TObjectPtr<UNNEModelData> ModelData) override;`
- L42 _private member_ `static const uint32 Alignment;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNERuntimeBasicCPU, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogNNERuntimeBasicCPU, Log, All);`
- L14 _macro_ `#define UE_API NNERUNTIMEBASICCPU_API`

### `Plugins/Experimental/NNERuntimeBasicCpu/Source/NNERuntimeBasicCpu/Private/NNERuntimeBasicCpuModel.h` (Private)


#### class `UE::NNE::RuntimeBasic::FModelInstanceCPU`  
`class FModelInstanceCPU : public IModelInstanceCPU`  
_L27-54_
- inherits: `IModelInstanceCPU`
- desc: Basic implementation of a model instance used for performing inference in this runtime.
- L30 _public typedef_ `using ESetInputTensorShapesStatus = IModelInstanceCPU::ESetInputTensorShapesStatus;`
- L31 _public typedef_ `using ERunSyncStatus = IModelInstanceCPU::ERunSyncStatus;`
- L33 _public prototype_ `FModelInstanceCPU(const TSharedPtr<FModelCPU>& InModel);`
- L36 _public function_ `virtual TConstArrayView<FTensorDesc> GetInputTensorDescs() const override final`
- L37 _public function_ `virtual TConstArrayView<FTensorDesc> GetOutputTensorDescs() const override final`
- L38 _public function_ `virtual TConstArrayView<FTensorShape> GetInputTensorShapes() const override final`
- L39 _public function_ `virtual TConstArrayView<FTensorShape> GetOutputTensorShapes() const override final`
- L40 _public prototype_ `virtual ESetInputTensorShapesStatus SetInputTensorShapes(TConstArrayView<FTensorShape> InInputShapes) override final;`
- L41 _public prototype_ `virtual ERunSyncStatus RunSync(TConstArrayView<FTensorBindingCPU> InInputBindings, TConstArrayView<FTensorBindingCPU> InOutputBindings) override final;`
- L44 _public member_ `TSharedPtr<FModelCPU> Model;`
- L45 _public member_ `FTensorDesc InputTensorDesc;`
- L46 _public member_ `FTensorDesc OutputTensorDesc;`
- L47 _public member_ `FTensorShape InputTensorShape;`
- L48 _public member_ `FTensorShape OutputTensorShape;`
- L49 _public member_ `TSharedPtr<Private::ILayerInstance> Instance;`
- L51 _public member_ `uint32 BatchSize = 0;`
- L52 _public member_ `uint32 InputSize = 0;`
- L53 _public member_ `uint32 OutputSize = 0;`

#### class `UE::NNE::RuntimeBasic::FModelCPU`  
`class FModelCPU : public IModelCPU`  
_L59-93_
- inherits: `IModelCPU`
- desc: Basic implementation of a model storing the network weights in this runtime.
- L64 _public member_ `static uint32 ModelMagicNumber;` — Magic number for the serialization format of this model data
- L67 _public member_ `static uint32 ModelVersionNumber;` — Version number for the serialization format of this model data
- L70 _public prototype_ `virtual TSharedPtr<IModelInstanceCPU> CreateModelInstanceCPU() override final;`
- L74 _public prototype_ `void SerializationSize(uint64& InOutOffset) const;` — Computes the number of bytes required to save or load this model
- L77 _public prototype_ `bool SerializationLoad(uint64& InOutOffset, TConstArrayView<uint8> Data);` — Loads the model from the array of bytes starting at the given offset
- L80 _public prototype_ `void SerializationSave(uint64& InOutOffset, TArrayView<uint8> Data) const;` — Saves the model to the array of bytes starting at the given offset
- L83 _public member_ `TSharedPtr<Private::ILayer> Layer;` — Private implementation of the model
- L86 _public member_ `TSharedPtr<FSharedModelData> ModelData;` — Shared pointer to the actual model data
- L92 _public member_ `TWeakPtr<FModelCPU> WeakThis;` — We need to store a TWeakPtr to ourselves so that when we construct the instance we can pass it a TSharedPtr to this object, which ensures the Model does not get deleted while there are still instances alive.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NNE` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NNE` (scope `UE`)
- L13 _namespace_ `namespace RuntimeBasic` (scope `UE::NNE`)
- L15 _namespace_ `namespace Private` (scope `UE::NNE::RuntimeBasic`)

### `Plugins/Experimental/NNERuntimeBasicCpu/Source/NNERuntimeBasicCpu/Private/NNERuntimeBasicCpuModule.h` (Private)


#### class `FNNERuntimeBasicCpuModule`  
`class FNNERuntimeBasicCpuModule : public IModuleInterface`  
_L12-20_
- inherits: `IModuleInterface`
- L15 _public member_ `TWeakObjectPtr<UNNERuntimeBasicCpuImpl> NNERuntimeBasicCpu{ nullptr };`
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/NNERuntimeBasicCpu/Source/NNERuntimeBasicCpu/Public/NNERuntimeBasicCpuBuilder.h` (Public)


#### class `UE::NNE::RuntimeBasic::FModelBuilderElement`  
`class FModelBuilderElement`  
_L21-36_
- desc: Represents an element of a model (such as a layer) created by the Model Builder.
- L27 _public prototype_ `FModelBuilderElement();`
- L28 _public prototype_ `FModelBuilderElement(const TSharedPtr<Private::ILayer>& Ptr);`
- L29 _public prototype_ `~FModelBuilderElement();`
- L31 _public prototype_ `int32 GetInputSize() const;`
- L32 _public prototype_ `int32 GetOutputSize() const;`
- L35 _private member_ `TSharedPtr<Private::ILayer> Layer;`

#### class `UE::NNE::RuntimeBasic::FModelBuilder`  
`class FModelBuilder`  
_L47-757_
- desc: This class can be used to construct Models for use with the Basic CPU Runtime. Effectively it works by constructing the model in-memory and then serializing this out to create a FileData object which can then be loaded with NNE. Note: If you pass your own views into this model builder they must out-live the builder itself as it will not create internal copies. If you want to create an internal copy use the `MakeValuesCopy` function.
- L125 _public prototype_ `FModelBuilder(int32 Seed = 0x0a974e75);` — Construct a new Model Builder with the given random seed.
- L135 _public prototype_ `FModelBuilderElement MakeLinear( const uint32 InputSize, const uint32 OutputSize, const TConstArrayView<float> Weights, const TConstArrayView<float> Biases);` — Makes a new linear layer. @param InputSize		Input Vector Size (Number of Rows) @param OutputSize	Output Vector Size (Number of Columns) @param Weights		Linear layer weights. @param Biases		Linear layer biases.
- L151 _public prototype_ `FModelBuilderElement MakeCompressedLinear( const uint32 InputSize, const uint32 OutputSize, const TConstArrayView<uint16> Weights, const TConstArrayView<float> WeightOffsets, const TConstArrayView<float> WeightScales, const TConstArrayView<float> Biases);` — Makes a new compressed linear layer. @param InputSize		Input Vector Size (Number of Rows) @param OutputSize	Output Vector Size (Number of Columns) @param Weights		Compressed Linear layer weights. @param WeightOffsets	Compressed Linear layer weight offsets. @param WeightScales	Compressed Linear layer weight biases. @param Biases		Compressed Linear layer biases.
- L167 _public prototype_ `FModelBuilderElement MakeLipschiztLinear( const uint32 InputSize, const uint32 OutputSize, const TConstArrayView<float> Weights, const TConstArrayView<float> Biases);` — Makes a new Lipschizt linear layer. @param InputSize		Input Vector Size (Number of Rows) @param OutputSize	Output Vector Size (Number of Columns) @param Weights		Linear layer weights. @param Biases		Linear layer biases.
- L180 _public prototype_ `FModelBuilderElement MakeLinearLayer( const uint32 InputSize, const uint32 OutputSize, const FLinearLayerSettings& Settings = FLinearLayerSettings());` — Makes a new linear layer with the given settings. @param InputSize		Input Vector Size (Number of Rows) @param OutputSize	Output Vector Size (Number of Columns) @param Settings		Layer Settings.
- L194 _public prototype_ `FModelBuilderElement MakeMultiLinear( const uint32 InputSize, const uint32 OutputSize, const uint32 BlockNum, const TConstArrayView<float> Weights, const TConstArrayView<float> Biases);` — Makes a new multi linear layer. @param InputSize		Input Vector Size (Number of Rows) @param OutputSize	Output Vector Size (Number of Columns) @param BlockNum		Number of blocks (Number of Matrices) @param Weights		Multi-Linear layer weights. @param Biases		Multi-Linear layer biases.
- L207 _public prototype_ `FModelBuilderElement MakeNormalize( const uint32 InputOutputSize, const TConstArrayView<float> Mean, const TConstArrayView<float> Std);` — Makes a new Normalization layer. @param Mean		Normalization Mean. @param Std		Normalization Std.
- L218 _public prototype_ `FModelBuilderElement MakeDenormalize( const uint32 InputOutputSize, const TConstArrayView<float> Mean, const TConstArrayView<float> Std);` — Makes a new Denormalization layer. @param Mean		Denormalization Mean. @param Std		Denormalization Std.
- L224 _public prototype_ `FModelBuilderElement MakeReLU(const uint32 InputOutputSize);` — Makes a ReLU Activation Layer
- L227 _public prototype_ `FModelBuilderElement MakeELU(const uint32 InputOutputSize);` — Makes a ELU Activation Layer
- L230 _public prototype_ `FModelBuilderElement MakeGELU(const uint32 InputOutputSize);` — Makes a GELU Activation Layer
- L233 _public prototype_ `FModelBuilderElement MakeTanH(const uint32 InputOutputSize);` — Makes a TanH Activation Layer
- L236 _public prototype_ `FModelBuilderElement MakeSoftmax(const uint32 InputOutputSize);` — Makes a Softmax Layer
- L239 _public prototype_ `FModelBuilderElement MakeCopy(const uint32 InputOutputSize);` — Makes a Copy Layer
- L242 _public prototype_ `FModelBuilderElement MakeSlice(const uint32 InputSize, const uint32 SliceOffset, const uint32 SliceSize);` — Makes a Slice Layer
- L245 _public prototype_ `FModelBuilderElement MakeClamp(const uint32 InputOutputSize, const TConstArrayView<float> MinValues, const TConstArrayView<float> MaxValues);` — Makes a Clamp Layer
- L248 _public prototype_ `FModelBuilderElement MakeActivation(const uint32 InputOutputSize, const EActivationFunction ActivationFunction);` — Makes a new activation layer with the given activation function
- L256 _public prototype_ `FModelBuilderElement MakePReLU(const uint32 InputOutputSize, const TConstArrayView<float> Alpha);` — Makes a PReLU Activation Layer @param LayerSize			Number of neurons in layer. @param Alpha				PReLU alpha parameter for each neuron.
- L261 _public prototype_ `FModelBuilderElement MakeSequence(const TConstArrayView<FModelBuilderElement> Elements);` — Makes a Sequence layer, which will evaluate the given list of layers in order.
- L274 _public prototype_ `FModelBuilderElement MakeMLP( const uint32 InputSize, const uint32 OutputSize, const uint32 HiddenSize, const uint32 LayerNum, const EActivationFunction ActivationFunction, const bool bActivationOnFinalLayer = false, const FLinearLayerSettings& LinearLayerSettings = FLinearLayerSettings());` — Makes a Multi-Layer Perceptron network. @param InputSize					Input Vector Size @param OutputSize				Output Vector Size @param HiddenSize				Number of hidden units to use on internal layers. @param LayerNum					Number of layers. Includes input and output layers. @param ActivationFunction		Activation function to use. @param bActivationOnFinalLayer	If the activation function should be used on the final output layer. @param LinearLayerSettings		Settings for the linear layers in the MLP.
- L294 _public prototype_ `FModelBuilderElement MakeMLPWithLayerNorm( const uint32 InputSize, const uint32 OutputSize, const uint32 HiddenSize, const uint32 LayerNum, const EActivationFunction ActivationFunction, const bool bActivationOnFinalLayer = false, const FLinearLayerSettings& LinearLayerSettings = FLinearLayerSettings());` — Makes a Multi-Layer Perceptron network with LayerNorm before all activations. @param InputSize					Input Vector Size @param OutputSize				Output Vector Size @param HiddenSize				Number of hidden units to use on internal layers. @param LayerNum					Number of layers. Includes input and output layers. @param ActivationFunction		Activation function to use. @param bActivationOnFinalLayer	If the activation function should be used on the final output layer. @param LinearLayerSettings		Settings for the linear layers in the MLP.
- L314 _public prototype_ `FModelBuilderElement MakeSkipMLP( const uint32 InputSize, const uint32 OutputSize, const uint32 HiddenSize, const uint32 LayerNum, const EActivationFunction ActivationFunction, const bool bActivationOnFinalLayer = false, const FLinearLayerSettings& LinearLayerSettings = FLinearLayerSettings());` — Makes a Multi-Layer Perceptron network using Skip layers that concatenate the input to each intermediate layer. @param InputSize					Input Vector Size @param OutputSize				Output Vector Size @param HiddenSize				Number of hidden units to use on internal layers. @param LayerNum					Number of layers. Includes input and output layers. @param ActivationFunction		Activation function to use. @param bActivationOnFinalLayer	If the activation function should be used on the final output layer. @param LinearLayerSettings		Settings for the linear layers in the MLP.
- L334 _public prototype_ `FModelBuilderElement MakeSkipMLPWithLayerNorm( const uint32 InputSize, const uint32 OutputSize, const uint32 HiddenSize, const uint32 LayerNum, const EActivationFunction ActivationFunction, const bool bActivationOnFinalLayer = false, const FLinearLayerSettings& LinearLayerSettings = FLinearLayerSettings());` — Makes a Multi-Layer Perceptron network using Skip layers that concatenate the input to each intermediate layer followed by a LayerNorm. @param InputSize					Input Vector Size @param OutputSize				Output Vector Size @param HiddenSize				Number of hidden units to use on internal layers. @param LayerNum					Number of layers. Includes input and output layers. @param ActivationFunction		Activation function to use. @param bActivationOnFinalLayer	If the activation function should be used on the final output layer. @param LinearLayerSettings		Settings for the linear layers in the MLP.
- L354 _public prototype_ `FModelBuilderElement MakeResidualMLP( const uint32 InputSize, const uint32 OutputSize, const uint32 HiddenSize, const uint32 LayerNum, const EActivationFunction ActivationFunction, const bool bActivationOnFinalLayer = false, const FLinearLayerSettings& LinearLayerSettings = FLinearLayerSettings());` — Makes a Multi-Layer Perceptron network using Residual layers. @param InputSize					Input Vector Size @param OutputSize				Output Vector Size @param HiddenSize				Number of hidden units to use on internal layers. @param LayerNum					Number of layers. Includes input and output layers. @param ActivationFunction		Activation function to use. @param bActivationOnFinalLayer	If the activation function should be used on the final output layer. @param LinearLayerSettings		Settings for the linear layers in the MLP.
- L374 _public prototype_ `FModelBuilderElement MakeResidualMLPWithLayerNorm( const uint32 InputSize, const uint32 OutputSize, const uint32 HiddenSize, const uint32 LayerNum, const EActivationFunction ActivationFunction, const bool bActivationOnFinalLayer = false, const FLinearLayerSettings& LinearLayerSettings = FLinearLayerSettings());` — Makes a Multi-Layer Perceptron network using Residual layers followed by LayerNorm layers. @param InputSize					Input Vector Size @param OutputSize				Output Vector Size @param HiddenSize				Number of hidden units to use on internal layers. @param LayerNum					Number of layers. Includes input and output layers. @param ActivationFunction		Activation function to use. @param bActivationOnFinalLayer	If the activation function should be used on the final output layer. @param LinearLayerSettings		Settings for the linear layers in the MLP.
- L395 _public prototype_ `FModelBuilderElement MakeMemoryCell( const uint32 InputNum, const uint32 OutputNum, const uint32 MemoryNum, const FModelBuilderElement& RememberLayer, const FModelBuilderElement& PassthroughLayer, const FModelBuilderElement& MemoryUpdateLayer, const FModelBuilderElement& OutputInputUpdateLayer, const FModelBuilderElement& OutputMemoryUpdateLayer);` — Make a new Memory Cell layer. @param InputNum					Number of normal inputs to the model. @param OutputNum					Number of normal outputs from the model. @param MemoryNum					The size of the memory vector used by the model. @param RememberLayer				Layer used for the Remember Gate. @param PassthroughLayer			Layer used for the Passthrough Gate. @param MemoryUpdateLayer			Layer used for updating the memory Gate. @param OutputInputUpdateLayer	Layer used for updating the output from the input. @param OutputMemoryUpdateLayer	Layer used for updating the output from the memory.
- L413 _public prototype_ `FModelBuilderElement MakeMemoryCellLayer( const uint32 InputNum, const uint32 OutputNum, const uint32 MemoryNum, const FLinearLayerSettings& LinearLayerSettings = FLinearLayerSettings());` — Make a new Memory Cell layer with the given linear layer settings. @param InputNum				Number of normal inputs to the model @param OutputNum				Number of normal outputs from the model @param MemoryNum				The size of the memory vector used by the model @param LinearLayerSettings	Settings for the linear layers in the Memory Cell.
- L428 _public prototype_ `FModelBuilderElement MakeGRUCell( const uint32 InputNum, const uint32 OutputNum, const FModelBuilderElement& RememberLayer, const FModelBuilderElement& UpdateLayer, const FModelBuilderElement& ActivationLayer);` — Make a new GRU Cell layer. @param InputNum					Number of inputs to the model. @param OutputNum					Number of outputs from the model. Will also be the memory size. @param RememberLayer				Layer used for the Remember Gate. @param UpdateLayer				Layer used for the Update Gate. @param ActivationLayer			Layer used for producing the Activation values.
- L442 _public prototype_ `FModelBuilderElement MakeGRUCellLayer( const uint32 InputNum, const uint32 OutputNum, const FLinearLayerSettings& LinearLayerSettings = FLinearLayerSettings());` — Make a new GRU Cell layer with the given linear layer settings. @param InputNum				Number of inputs to the model. @param OutputNum				Number of outputs from the model. Will also be the memory size. @param LinearLayerSettings	Settings for the linear layers in the Memory Cell.
- L455 _public prototype_ `FModelBuilderElement MakeMemoryBackbone( const uint32 MemoryNum, const FModelBuilderElement& Prefix, const FModelBuilderElement& Cell, const FModelBuilderElement& Postfix);` — Make a new Memory Backbone layer. @param MemoryNum				The size of the memory vector used by the model @param Prefix				Prefix Element @param Cell					Memory Cell Element @param Postfix				Postfix Element
- L465 _public prototype_ `FModelBuilderElement MakeConcat(const TConstArrayView<FModelBuilderElement> Elements);` — Makes a Concat layer, which will evaluate each of the given elements on different slices of the input vector, concatenating the result into the output vector.
- L471 _public prototype_ `FModelBuilderElement MakeSpread(const TConstArrayView<FModelBuilderElement> Elements);` — Makes a Spread layer, which will evaluate each of the given elements on the input vector, concatenating the result into the output vector.
- L479 _public prototype_ `FModelBuilderElement MakeArray(const uint32 ElementNum, const FModelBuilderElement& SubLayer);` — Make a layer which runs the given sublayer on an array of elements. @param ElementNum	Number of elements in the array. @param SubLayer		Sublayer to evaluate on each item in the array.
- L486 _public prototype_ `FModelBuilderElement MakeResidual(const FModelBuilderElement& SubLayer);` — Make a residual layer which adds the result of evaluating the given sublayer on the input, to the input. @param SubLayer		Sublayer to evaluate on the input.
- L491 _public prototype_ `FModelBuilderElement MakeAggregateSet( const uint32 MaxElementNum, const uint32 OutputEncodingSize, const uint32 AttentionEncodingSize, const uint32 AttentionHeadNum, const FModelBuilderElement& SubLayer, const FModelBuilderElement& QueryLayer, const FModelBuilderElement& KeyLayer, const FModelBuilderElement& ValueLayer);` — Make a layer which aggregates a set of other observations using attention. This is used by LearningAgents.
- L504 _public prototype_ `FModelBuilderElement MakeAggregateOrExclusive( const uint32 OutputEncodingSize, const TConstArrayView<FModelBuilderElement> SubLayers, const TConstArrayView<FModelBuilderElement> Encoders);` — Make a layer which aggregates an Exclusive Or of other observations. This is used by LearningAgents.
- L512 _public prototype_ `FModelBuilderElement MakeAggregateOrInclusive( const uint32 OutputEncodingSize, const uint32 AttentionEncodingSize, const uint32 AttentionHeadNum, const TConstArrayView<FModelBuilderElement> SubLayers, const TConstArrayView<FModelBuilderElement> QueryLayers, const TConstArrayView<FModelBuilderElement> KeyLayers, const TConstArrayView<FModelBuilderElement> ValueLayers);` — Make a layer which aggregates an Inclusive Or of other observations using attention. This is used by LearningAgents.
- L529 _public prototype_ `FModelBuilderElement MakeSparseMixtureOfExperts( const uint32 InputNum, const uint32 OutputNum, const FModelBuilderElement& GatingLayer, const TConstArrayView<FModelBuilderElement> SubLayers);` — Make a new Top-Two Sparse Mixture of Experts Layer. @param InputNum					Number of normal inputs to the model. @param OutputNum					Number of normal outputs from the model. @param GatingLayer				Layer used to choose the experts. Input should be of size InputNum, output should be of size SubLayerNum. @param SubLayers					Expert layers. All Layers here should have input of size InputNum, output of size OutputNum.
- L543 _public prototype_ `FModelBuilderElement MakeLayerNorm( const uint32 InputOutputSize, const TConstArrayView<float> Offsets, const TConstArrayView<float> Scales, const float Epsilon = 1e-5f);` — Makes a new Layer Norm layer. @param InputOutputSize	Input and Output Vector Size @param Offsets			Initial Offsets @param Scales			Initial Scales @param Epsilon			Standard Deviation Epsilon
- L550 _public prototype_ `FModelBuilderElement MakeTile(const uint32 InputSize, const uint32 Repeats);` — Makes a Tile Layer
- L559 _public prototype_ `FModelBuilderElement MakeFiLMNetwork( const FModelBuilderElement& Prefix, const FModelBuilderElement& Condition, const FModelBuilderElement& Postfix);` — Make a new FiLM conditioned Network. @param Prefix				Prefix Element @param Condition				Condition Element @param Postfix				Postfix Element
- L577 _public prototype_ `FModelBuilderElement MakeConv1d( const uint32 InputLength, const uint32 InChannels, const uint32 OutChannels, const uint32 KernelSize, const uint32 Padding, const EPaddingMode PaddingMode, const TConstArrayView<float> Weights, const TConstArrayView<float> Biases, const FModelBuilderElement& SubLayer);` — Make a new 1D Convolution Layer. @param InputLength			Length of 1 dimensional input @param InChannels			Number of channels in the input @param OutChannels			Number of channels produced by the convolution @param KernelSize			Size of the convolving kernel @param Padding				The amount of padding added to both sides of the input @param PaddingMode			"Zeros" or "Circular" @param Weights				Convolutional layer weights @param Biases				Convolutional layer biases @param SubLayer				The sublayer to evaluate on the input
- L603 _public prototype_ `FModelBuilderElement MakeConv2d( const uint32 InputHeight, const uint32 InputWidth, const uint32 InChannels, const uint32 OutChannels, const uint32 KernelSize, const uint32 Stride, const uint32 Padding, const EPaddingMode PaddingMode, const TConstArrayView<float> Weights, const TConstArrayView<float> Biases, const FModelBuilderElement& SubLayer);` — Make a new 2D Convolution Layer. @param InputHeight			Height of the 2d flat buffer input @param InputWidth				Width of the 2d flat buffer input @param InChannels				Number of channels in the input @param OutChannels			Number of channels produced by the convolution @param KernelSize				Size of the convolving kernel @param Stride					The stride of the cross correlation @param Padding				The amount of padding added to both sides of the input @param PaddingMode			"Zeros" or "Circular" @param Weights				Convolutional layer weights @param Biases					Convolutional layer biases @param SubLayer				The sublayer to evaluate on the input
- L619 _public prototype_ `TArrayView<float> MakeValuesCopy(const TConstArrayView<float> Values);` — Creates a array of values from a copy of the given array view
- L622 _public prototype_ `TArrayView<float> MakeValuesZero(const uint32 Size);` — Creates a array of values set to zero of the given size
- L625 _public prototype_ `TArrayView<float> MakeValuesOne(const uint32 Size);` — Creates a array of values set to one of the given size
- L628 _public prototype_ `TArrayView<float> MakeValuesConstant(const uint32 Size, const float Value);` — Creates a array of values set to the provided constant value of the given size
- L631 _public prototype_ `TArrayView<float> MakeWeightsRandomKaimingGaussian(const uint32 InputSize, const uint32 OutputSize, const float Scale = 1.0f);` — Creates a array of weights randomly initialized using the Gaussian Kaiming method
- L634 _public prototype_ `TArrayView<float> MakeWeightsRandomKaimingUniform(const uint32 InputSize, const uint32 OutputSize, const float Scale = 1.0f);` — Creates a array of weights randomly initialized using the Uniform Kaiming method
- L637 _public prototype_ `TArrayView<float> MakeBiasesRandomKaimingGaussian(const uint32 Size, const float Scale = 1.0f);` — Creates a array of biases randomly initialized using the Gaussian Kaiming method
- L640 _public prototype_ `TArrayView<float> MakeBiasesRandomKaimingUniform(const uint32 Size, const float Scale = 1.0f);` — Creates a array of biases randomly initialized using the Uniform Kaiming method#
- L643 _public prototype_ `void MakeCompressedWeightsRandomKaimingGaussian( TArrayView<uint16>& OutWeightsView, TArrayView<float>& OutWeightOffsetsView, TArrayView<float>& OutWeightScalesView, const uint32 InputSize, const uint32 OutputSize, const float Scale = 1.0f);` — Creates a array of weights randomly initialized using the Gaussian Kaiming method and compresses them
- L652 _public prototype_ `void MakeCompressedWeightsRandomKaimingUniform( TArrayView<uint16>& OutWeightsView, TArrayView<float>& OutWeightOffsetsView, TArrayView<float>& OutWeightScalesView, const uint32 InputSize, const uint32 OutputSize, const float Scale = 1.0f);` — Creates a array of weights randomly initialized using the Uniform Kaiming method and compresses them
- L661 _public prototype_ `TArrayView<float> MakeInitialWeights( const uint32 InputSize, const uint32 OutputSize, const FWeightInitializationSettings& WeightInitializationSettings = FWeightInitializationSettings());` — Creates a array of weights initialized using the given settings
- L667 _public prototype_ `TArrayView<float> MakeInitialBiases( const uint32 OutputSize, const FWeightInitializationSettings& WeightInitializationSettings = FWeightInitializationSettings());` — Creates a array of biases initialized using the given settings
- L672 _public prototype_ `void MakeInitialCompressedWeights( TArrayView<uint16>& OutWeightsView, TArrayView<float>& OutWeightOffsetsView, TArrayView<float>& OutWeightScalesView, const uint32 InputSize, const uint32 OutputSize, const FWeightInitializationSettings& WeightInitializationSettings = FWeightInitializationSettings());` — Creates a array of weights randomly initialized using the given settings and compresses them
- L681 _public prototype_ `TArrayView<uint32> MakeSizesZero(const uint32 Size);` — Creates an array of sizes, initialized to zero.
- L684 _public prototype_ `TArrayView<uint32> MakeSizesLayerInputs(const TConstArrayView<FModelBuilderElement> Elements);` — Creates an array of sizes from an array of builder elements' input sizes.
- L687 _public prototype_ `TArrayView<uint32> MakeSizesLayerOutputs(const TConstArrayView<FModelBuilderElement> Elements);` — Creates an array of sizes from an array of builder elements' output sizes.
- L692 _public prototype_ `void Reset();` — Reset the builder clearing all memory.
- L697 _public prototype_ `uint64 GetWriteByteNum(const FModelBuilderElement& Element) const;` — Get the number of bytes this builder currently wants to write for the given element.
- L708 _public prototype_ `void WriteFileData(TArrayView<uint8> OutFileData, uint32& OutInputSize, uint32& OutOutputSize, const FModelBuilderElement& Element) const;` — Write the Model to FileData. Use `GetWriteByteNum` to get the number of bytes this will write so that `FileData` can be allocated to the right size. @param OutFileData			Output File data to write to @param OutInputSize			Output for the number of float inputs to the model @param OutOutputSize			Output for the number of float outputs from the model @param Element				Builder element to write the model FileData for.
- L719 _public prototype_ `void WriteFileData(TArray<uint8>& OutFileData, uint32& OutInputSize, uint32& OutOutputSize, const FModelBuilderElement& Element) const;` — Write the model to the FileData. Use `GetWriteByteNum` to get the number of bytes this will write so that `FileData` can be allocated to the right size. @param OutFileData			Output File data to write to @param OutInputSize			Output for the number of float inputs to the model @param OutOutputSize			Output for the number of float outputs from the model @param Element				Builder element to write the model FileData for.
- L729 _public prototype_ `void WriteFileDataAndReset(TArrayView<uint8> OutFileData, uint32& OutInputSize, uint32& OutOutputSize, const FModelBuilderElement& Element);` — Write the model to the FileData and Reset the builder clearing all memory used. @param OutFileData			Output File data to write to @param OutInputSize			Output for the number of float inputs to the model @param OutOutputSize			Output for the number of float outputs from the model @param Element				Builder element to write the model FileData for.
- L739 _public prototype_ `void WriteFileDataAndReset(TArray<uint8>& OutFileData, uint32& OutInputSize, uint32& OutOutputSize, const FModelBuilderElement& Element);` — Write the model to the FileData and Reset the builder clearing all memory used. @param OutFileData			Output File data to write to @param OutInputSize			Output for the number of float inputs to the model @param OutOutputSize			Output for the number of float outputs from the model @param Element				Builder element to write the model FileData for.
- L744 _private member_ `static constexpr uint32 RngInitialState = 0xafcc2b45;` — Default initial state for the random number generator.
- L747 _private member_ `uint32 Rng = RngInitialState;` — Random Number State for generating random weights
- L750 _private member_ `TArray<TArray<float>> WeightsPool;` — Pool of all weights data used by the `MakeValues`, `MakeWeights` `MakeBiases` functions.
- L753 _private member_ `TArray<TArray<uint16>> CompressedWeightsPool;` — Pool of all compressed weights data used by the `MakeCompressedWeights` functions.
- L756 _private member_ `TArray<TArray<uint32>> SizesPool;` — Pool of all sizes data used by the `MakeSizes` functions.

#### enum `UE::NNE::RuntimeBasic::FModelBuilder::EActivationFunction`  
`enum class EActivationFunction : uint8`  
_L53-59_
- desc: Common activation function types.
- L55 _public enumerator_ `ReLU = 0`
- L56 _public enumerator_ `ELU = 1`
- L57 _public enumerator_ `TanH = 2`
- L58 _public enumerator_ `GELU = 3`

#### enum `UE::NNE::RuntimeBasic::FModelBuilder::ELinearLayerType`  
`enum class ELinearLayerType : uint8`  
_L62-67_
- desc: Linear Layer types.
- L64 _public enumerator_ `Normal = 0`
- L65 _public enumerator_ `Compressed = 1`
- L66 _public enumerator_ `Lipschizt = 2`

#### enum `UE::NNE::RuntimeBasic::FModelBuilder::EWeightInitializationType`  
`enum class EWeightInitializationType : uint8`  
_L70-77_
- desc: Weight initialization types.
- L73 _public enumerator_ `KaimingGaussian = 0` — Good all-round default weight initialization
- L76 _public enumerator_ `KaimingUniform = 1` — Default initialization used in PyTorch for Linear Layers

#### enum `UE::NNE::RuntimeBasic::FModelBuilder::EPaddingMode`  
`enum class EPaddingMode : uint8`  
_L80-86_
- desc: Padding Mode for Convolutions
- L83 _public enumerator_ `Zeros = 0` — The input will be padded with zeroes on both sides
- L85 _public enumerator_ `Circular = 1` — The input will be padded with wrap around values

#### struct `UE::NNE::RuntimeBasic::FModelBuilder::FWeightInitializationSettings`  
`struct FWeightInitializationSettings`  
_L96-109_
- desc: Weight initialization settings.
- L99 _public prototype_ `FWeightInitializationSettings();` — Workaround for clang compiler bug...
- L102 _public member_ `EWeightInitializationType Type = EWeightInitializationType::KaimingUniform;` — Type of initialization to use
- L105 _public member_ `float Scale = 1.0f;` — Overall scale of the weight initialization
- L108 _public member_ `bool bInitializeBiases = true;` — If true, initializes biases using the given initialization method, otherwise initializes them to zeros

#### struct `UE::NNE::RuntimeBasic::FModelBuilder::FLinearLayerSettings`  
`struct FLinearLayerSettings`  
_L112-122_
- desc: Linear Layer settings including the type of layer and the way the weights are initialized
- L115 _public prototype_ `FLinearLayerSettings();` — Workaround for clang compiler bug...
- L118 _public member_ `ELinearLayerType Type = ELinearLayerType::Normal;` — Type of the Linear Layer to construct
- L121 _public member_ `FWeightInitializationSettings WeightInitializationSettings;` — Weight initialization Settings for the linear Layer

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API NNERUNTIMEBASICCPU_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace NNE` (scope `UE`)
- L9 _namespace_ `namespace RuntimeBasic` (scope `UE::NNE`)
- L11 _namespace_ `namespace Private` (scope `UE::NNE::RuntimeBasic`)
