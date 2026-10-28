# Runtime / SignalProcessing

- module root: `Source/Runtime/SignalProcessing`
- headers: 102; symbols: 3816
- symbol kinds: class=139, enum=43, enumerator=271, function=354, macro=26, member=1345, namespace=113, prototype=1415, struct=82, typedef=24, variable=4
- PrivateDependencyModuleNames: Core, MathCore
- PrivateIncludePathModuleNames: AudioMixerCore, Engine, TargetPlatform
- PublicDependencyModuleNames: IntelISPC

### `Source/Runtime/SignalProcessing/Private/UniformPartitionConvolution.h` (Private)


#### struct `Audio::FUniformPartitionConvolutionSettings`  
`struct FUniformPartitionConvolutionSettings`  
_L13-26_
- desc: Settings for creating a uniform partition convolution.
- L16 _public member_ `int32 NumInputChannels = 0;` — Number of input channels for convolution.
- L19 _public member_ `int32 NumOutputChannels = 0;` — Number of output channels for convolution.
- L22 _public member_ `int32 NumImpulseResponses = 0;` — Number of impulse responses for convolution.
- L25 _public member_ `int32 MaxNumImpulseResponseSamples = 0;` — Maximum number of samples in an impulse response.

#### class `Audio::FUniformPartitionConvolution`  
`class FUniformPartitionConvolution : public IConvolutionAlgorithm`  
_L42-258_
- inherits: `IConvolutionAlgorithm`
- desc: FUniformPartitionConvolution FUniformPartitionConvolution implements a fft based convolution algorithm supporting multiple inputs, impulse responses and outputs. The algorithm subdivides an impulse response into uniform blocks which results in several positive side effects: 1. Latency is set to the block size which in many cases is less than the length of the impulse response. 2. Increased performance over brute time domain convolution. 3. Reuse of fourier transformed data when inputs are mapped to multiple outputs. The block size and latency is determined by the FFT algorithm passed to the constructor. BlockSize = FFTAlgorithm->Size() / 2 Latency = FFTAlgorithm->Size() / 2
- L46 _public typedef_ `using FSharedFFTRef = TSharedRef<IFFTAlgorithm>;` — Shared reference to FFT algorithm.
- L53 _public prototype_ `FUniformPartitionConvolution(const FUniformPartitionConvolutionSettings& InSettings, FSharedFFTRef InFFTAlgorithm);` — Create a Uniform Partition Convolution Algorithm @params InSettings - Settings for algorithm. @param InFFTAlgorithm - FFTAlgorithm used to transform inputs, outputs and impulse responses.
- L56 _public prototype_ `virtual ~FUniformPartitionConvolution();` — Destructor.
- L59 _public prototype_ `virtual int32 GetNumSamplesInBlock() const override;` — Returns the number of samples in an audio block.
- L62 _public prototype_ `virtual int32 GetNumAudioInputs() const override;` — Returns number of audio inputs.
- L65 _public prototype_ `virtual int32 GetNumAudioOutputs() const override;` — Returns number of audio outputs.
- L75 _public prototype_ `virtual void ProcessAudioBlock(const float* const InSamples[], float* const OutSamples[]) override;` — Process one block of audio. InSamples is processed by the impulse responses. The output is placed in OutSamples. @params InSamples - A 2D array of input deinterleaved audio samples. InSamples[GetNumAudioInputs()][GetNumSamplesInBlock()] @params OutSamples - A 2D array of output deinterleaved audio samples. OutSamples[GetNumAudioOutputs()][GetNumSamplesInBlock()]
- L78 _public prototype_ `virtual void ResetAudioHistory() override;` — Reset internal history buffer for all audio inputs.
- L81 _public prototype_ `virtual int32 GetMaxNumImpulseResponseSamples() const override;` — Maximum supported length of impulse response.
- L84 _public prototype_ `virtual int32 GetNumImpulseResponses() const override;` — Return the number of impulse responses.
- L87 _public prototype_ `virtual int32 GetNumImpulseResponseSamples(int32 InImpulseResponseIndex) const override;` — Return the number of samples in an impulse response.
- L90 _public prototype_ `virtual void SetImpulseResponse(int32 InImpulseResponseIndex, const float* InSamples, int32 InNumSamples) override;` — Set impulse response values.
- L96 _public prototype_ `virtual void SetMatrixGain(int32 InAudioInputIndex, int32 InImpulseResponseIndex, int32 InAudioOutputIndex, float InGain) override;` — Sets the gain between an audio input channel, impulse response and audio output channel. ([audio inputs] * [impulse responses]) x [gain matrix] = [audio outputs]
- L102 _public prototype_ `virtual float GetMatrixGain(int32 InAudioInputIndex, int32 InImpulseResponseIndex, int32 InAudioOutputIndex) const override;` — Gets the gain between an audio input channel, impulse response and audio output channel. ([audio inputs] * [impulse responses]) x [gain matrix] = [audio outputs]
- L107 _private member_ `static const int32 NumSimdMask;` — Bit mask to determine how many values to apply SIMD optimization.
- L133 _private prototype_ `void VectorComplexMultiplyAdd(const FAlignedFloatBuffer& InA, const FAlignedFloatBuffer& InB, FAlignedFloatBuffer& Out) const;` — Vector optimized complex multiply add
- L136 _private prototype_ `void VectorMultiplyByConstant(const FAlignedFloatBuffer& InBuffer, float InConstant, FAlignedFloatBuffer& OutBuffer) const;` — Vector optimized multiply
- L244 _private member_ `FUniformPartitionConvolutionSettings Settings;`
- L246 _private member_ `int32 BlockSize;`
- L247 _private member_ `int32 NumFFTOutputFloats;`
- L248 _private member_ `int32 NumBlocks;`
- L249 _private member_ `FAlignedFloatBuffer TransformedAndScaledInput;`
- L250 _private member_ `TSharedRef<IFFTAlgorithm> FFTAlgorithm;`
- L252 _private member_ `TArray<FInput> Inputs;`
- L253 _private member_ `TArray<FOutput> Outputs;`
- L254 _private member_ `TArray<FImpulseResponse> ImpulseResponses;`
- L256 _private member_ `TMap<FInputTransformOutputGroup, float> NonZeroGains;`
- L257 _private member_ `TArray<bool> IsOutputZero;`

#### struct `Audio::FUniformPartitionConvolution::FInputTransformOutputGroup`  
`struct FInputTransformOutputGroup : public TTuple<int32, int32, int32>`  
_L110-130_
- inherits: `TTuple<int32,int32,int32>`
- desc: Triple index into 3D mixing matrix.
- L112 _public function_ `FInputTransformOutputGroup(int32 InInputIndex, int32 InTransformIndex, int32 InOutputIndex) : TTuple<int32, int32, int32>(InInputIndex, InTransformIndex, InOutputIndex)`
- L116 _public function_ `int32 GetInputIndex() const`
- L121 _public function_ `int32 GetTransformIndex() const`
- L126 _public function_ `int32 GetOutputIndex() const`

#### struct `Audio::FUniformPartitionConvolution::FInput`  
`struct FInput`  
_L141-163_
- desc: Contains a single input channel. The input channel holds the FFT of the latest input block.
- L144 _public prototype_ `FInput(FSharedFFTRef InFFTAlgorithm);`
- L147 _public prototype_ `void PushBlock(const float* InSamples);` — Add one block of audio samples.
- L150 _public prototype_ `const FAlignedFloatBuffer& GetTransformedBlock() const;` — Reference to latest transformed block.
- L153 _public prototype_ `void Reset();` — Clears the transformed block
- L156 _public member_ `const int32 BlockSize;` — Number of samples in a block
- L160 _private member_ `FSharedFFTRef FFTAlgorithm;`
- L161 _private member_ `FAlignedFloatBuffer InputBuffer;`
- L162 _private member_ `FAlignedFloatBuffer OutputBuffer;`

#### struct `Audio::FUniformPartitionConvolution::FOutput`  
`struct FOutput`  
_L169-203_
- desc: Contains a single output channel The output channel holds a running history of fourier transformed output blocks. When a block is popped, it converts it from the fourier domain to the time domain.
- L175 _public prototype_ `FOutput(int32 InNumBlocks, FSharedFFTRef InFFTAlgorithm);` — Construct an output @param InNumBlocks - Number of running history blocks @param InFFTAlgorithm - FFT algorithm for performing inverse FFT.
- L177 _public prototype_ `~FOutput();`
- L180 _public prototype_ `FAlignedFloatBuffer& GetTransformedBlock(int32 InBlockIndex);` — Returns the history block at the given index.
- L183 _public prototype_ `void PopBlock();` — Pop the latest block without performing inverse FFT
- L187 _public prototype_ `void PopBlock(float* OutSamples);` — Pop the latest block and perform inverse fft. Out samples should hold InFFTAlgorithm->Size() / 2 floats.
- L190 _public prototype_ `void Reset();` — Reset history of output blocks.
- L192 _public member_ `const int32 NumBlocks;`
- L193 _public member_ `const int32 BlockSize;`
- L194 _public member_ `const int32 NumFFTOutputFloats;`
- L197 _private member_ `FSharedFFTRef FFTAlgorithm;`
- L198 _private member_ `FAlignedFloatBuffer OutputBuffer;`
- L200 _private member_ `int32 HeadBlockIndex;`
- L201 _private member_ `TArray<FAlignedFloatBuffer> Blocks;`

#### struct `Audio::FUniformPartitionConvolution::FImpulseResponse`  
`struct FImpulseResponse`  
_L208-242_
- desc: Contains a single impulse response The impulse response is broken into blocks and transformed to the fourier domain.
- L214 _public prototype_ `FImpulseResponse(int32 InNumBlocks, FSharedFFTRef InFFTAlgorithm);` — Constructor @params InNumBlocks - Maximum number of FFT blocks @param InFFTAlgorithm - FFT algorithm to convert samples to fourier.
- L216 _public prototype_ `~FImpulseResponse();`
- L219 _public prototype_ `void SetImpulseResponse(const float* InSamples, int32 InNum);` — Sets the impulse response.
- L222 _public prototype_ `const FAlignedFloatBuffer& GetTransformedBlock(int32 InBlockIndex) const;` — Returns a block of the transformed impulse response.
- L227 _public prototype_ `int32 GetNumActiveBlocks() const;` — Returns the number of active blocks. This may be less than the maximum number of blocks if the impulse response is shorter than the maximum number of impulse response samples.
- L230 _public prototype_ `int32 GetNumImpulseResponseSamples() const;` — Returns the number of samples in the impulse response.
- L232 _public member_ `const int32 NumBlocks;`
- L233 _public member_ `const int32 BlockSize;`
- L236 _private member_ `FSharedFFTRef FFTAlgorithm;`
- L237 _private member_ `int32 NumFFTOutputFloats;`
- L238 _private member_ `int32 NumActiveBlocks;`
- L239 _private member_ `int32 NumImpulseResponseSamples;`
- L240 _private member_ `FAlignedFloatBuffer FFTInput;`
- L241 _private member_ `TArray<FAlignedFloatBuffer> Blocks;`

#### class `Audio::FUniformPartitionConvolutionFactory`  
`class FUniformPartitionConvolutionFactory : public IConvolutionAlgorithmFactory`  
_L261-282_
- inherits: `IConvolutionAlgorithmFactory`
- desc: FUniformPartitionConvolutionFactory creates FUniformPartitionConvolution algorithms.
- L264 _public prototype_ `virtual ~FUniformPartitionConvolutionFactory();`
- L267 _public prototype_ `virtual const FName GetFactoryName() const override;` — Name of this particular factory.
- L270 _public prototype_ `virtual bool IsHardwareAccelerated() const override;` — If true, this implementation uses hardware acceleration.
- L273 _public prototype_ `virtual bool AreConvolutionSettingsSupported(const FConvolutionSettings& InSettings) const override;` — Returns true if the input settings are supported by this factory.
- L276 _public prototype_ `virtual TUniquePtr<IConvolutionAlgorithm> NewConvolutionAlgorithm(const FConvolutionSettings& InSettings) override;` — Creates a new Convolution algorithm.
- L281 _private prototype_ `static FFFTSettings FFTSettingsFromConvolutionSettings(const FConvolutionSettings& InConvolutionSettings);` — Convert the convolution settings into FFTAlgorithm settings.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Private/VectorFFT.h` (Private)


#### class `Audio::FVectorRealToComplexFFT`  
`class FVectorRealToComplexFFT : public IFFTAlgorithm`  
_L13-106_
- inherits: `IFFTAlgorithm`
- L17 _public member_ `static const int32 MinLog2FFTSize;` — Minimum log2 size of fft.
- L20 _public member_ `static const int32 MaxLog2FFTSize;` — Maximum log 2 size of fft
- L26 _public prototype_ `FVectorRealToComplexFFT(int32 InLog2Size);` — Construct a FVectorRealToComplex FFT @param InLog2Size - Determines the size of the FFT.  FFTSize = 2^InLog2Size.
- L28 _public prototype_ `virtual ~FVectorRealToComplexFFT();`
- L31 _public prototype_ `virtual int32 Size() const override;` — Number of elements in FFT
- L34 _public prototype_ `virtual EFFTScaling ForwardScaling() const override;` — Scaling applied when performing forward FFT.
- L37 _public prototype_ `virtual EFFTScaling InverseScaling() const override;` — Scaling applied when performing inverse FFT.
- L47 _public prototype_ `virtual void ForwardRealToComplex(const float* RESTRICT InReal, float* RESTRICT OutComplex) override;` — ForwardRealToComplex Perform the forward FFT on real data and produce complex data. @param InReal - Array of floats to input into fourier transform. Must have FFTSize() elements. @param OutComplex - Array of floats to store output of fourier transform. Must have (FFTSize() + 2) float elements which represent ((FFTSize() / 2) + 1) complex numbers in interleaved format.
- L56 _public prototype_ `virtual void InverseComplexToReal(const float* RESTRICT InComplex, float* RESTRICT OutReal) override;` — InverseComplexToReal Perform the inverse FFT on complex data and produce real data. @param InComplex - Array of floats to input into inverse fourier transform. Must have (FFTSize() + 2) float elements which represent ((FFTSize() / 2) + 1) complex numbers in interleaved format. @param OutReal - Array of floats to store output of inverse fourier transform. Must have FFTSize() elements.
- L66 _public prototype_ `virtual void BatchForwardRealToComplex(int32 InCount, const float* const RESTRICT InReal[], float* RESTRICT OutComplex[]) override;` — BatchForwardRealToComplex Perform the forward FFT on real data and produce complex data. @param InCount - The number of transforms to compute. @param InReal - Array of array of floats to input into fourier transform. Must have InCount elements, each containing FFTSize() elements. @param OutComplex - Array of array of floats to store output of fourier transform. Must have InCount elements, each with (FFTSize() + 2) float elements which represent ((FFTSize() / 2) + 1) complex numbers in interleaved format.
- L76 _public prototype_ `virtual void BatchInverseComplexToReal(int32 InCount, const float* const RESTRICT InComplex[], float* RESTRICT OutReal[]) override;` — BatchInverseComplexToReal Perform the inverse FFT on complex data and produce real data. @param InCount - The number of transforms to compute. @param InComplex - Array of array of floats to input into inverse fourier transform. Must have InCount elements, each with (FFTSize() + 2) float elements which represent ((FFTSize() / 2) + 1) complex numbers in interleaved format. @param OutReal - Array of array of floats to store output of inverse fourier transform. Must have InCount elements, each with FFTSize() float elements.
- L91 _private prototype_ `void InitRealSequenceConversionBuffers();` — Initializes conversion buffers
- L94 _private prototype_ `void ConvertSequence(const FConversionBuffers& InBuffers, const float* RESTRICT InValues, int32 InStartIndex, float* RESTRICT OutValues);` — Converts a buffer
- L96 _private member_ `int32 FFTSize;`
- L97 _private member_ `int32 Log2FFTSize;`
- L99 _private member_ `FAlignedFloatBuffer WorkBuffer;`
- L101 _private member_ `FConversionBuffers ForwardConvBuffers;`
- L102 _private member_ `FConversionBuffers InverseConvBuffers;`
- L105 _private member_ `TUniquePtr<FVectorComplexFFT> ComplexFFT;` — Complex FFT implementation.

#### struct `Audio::FVectorRealToComplexFFT::FConversionBuffers`  
`struct FConversionBuffers`  
_L81-87_
- desc: Needed to convert buffers for implementation of real-to-complex fft using complex-to-comlex fft.
- L83 _public member_ `FAlignedFloatBuffer AlphaReal;`
- L84 _public member_ `FAlignedFloatBuffer AlphaImag;`
- L85 _public member_ `FAlignedFloatBuffer BetaReal;`
- L86 _public member_ `FAlignedFloatBuffer BetaImag;`

#### class `Audio::FVectorFFTFactory`  
`class FVectorFFTFactory : public IFFTAlgorithmFactory`  
_L109-128_
- inherits: `IFFTAlgorithmFactory`
- desc: Algorithm factory for FVectorFFT
- L112 _public prototype_ `virtual ~FVectorFFTFactory();`
- L115 _public prototype_ `virtual FName GetFactoryName() const override;` — Name of this particular factory.
- L118 _public prototype_ `virtual bool IsHardwareAccelerated() const override;` — If true, this implementation uses hardware acceleration.
- L121 _public prototype_ `virtual bool Expects128BitAlignedArrays() const override;` — If true, this implementation requires input and output arrays to be 128 bit aligned.
- L124 _public prototype_ `virtual bool AreFFTSettingsSupported(const FFFTSettings& InSettings) const override;` — Returns true if the input settings are supported by this factory.
- L127 _public prototype_ `virtual TUniquePtr<IFFTAlgorithm> NewFFTAlgorithm(const FFFTSettings& InSettings) override;` — Creates a new FFT algorithm.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/CheckedAudioBuffer.h` (Public)


#### class `Audio::FCheckedAudioBuffer`  
`class FCheckedAudioBuffer`  
_L16-61_
- desc: Opaque wrapper around FAlignedFloatBuffer. Will perform different checks on accessing the buffer, which can be enabled by flags. Error states are sticky.
- L19 _public typedef_ `using ECheckBehavior = Audio::EBufferCheckBehavior;`
- L21 _public function_ `void SetName(const FString& InName)`
- L22 _public function_ `void SetCheckBehavior(const ECheckBehavior InBehavior)`
- L23 _public function_ `void SetCheckFlags(const ECheckBufferFlags InCheckFlags)`
- L26 _public function_ `operator FAlignedFloatBuffer&()` — Automatic conversions to FAlignedBuffer with a Check.
- L27 _public function_ `operator TArrayView<float>()`
- L28 _public function_ `operator TArrayView<const float>() const`
- L29 _public function_ `operator const FAlignedFloatBuffer&() const`
- L30 _public prototype_ `void operator=(const FAlignedFloatBuffer& InOther);`
- L31 _public function_ `const FAlignedFloatBuffer* operator&() const`
- L32 _public function_ `FAlignedFloatBuffer* operator&()`
- L34 _public prototype_ `int32 Num() const;`
- L35 _public prototype_ `void Reserve(const int32 InSize);`
- L36 _public prototype_ `void Reset(const int32 InSize=0);`
- L37 _public prototype_ `void AddZeroed(const int32 InSize);`
- L38 _public prototype_ `void SetNumZeroed(const int32 InSize);`
- L39 _public prototype_ `void SetNumUninitialized(const int32 InNum);`
- L42 _public prototype_ `const FAlignedFloatBuffer& GetBuffer() const;` — Const.
- L45 _public prototype_ `FAlignedFloatBuffer& GetBuffer();` — Non-const.
- L46 _public prototype_ `float* GetData();`
- L48 _public prototype_ `void Append(const FAlignedFloatBuffer& InBuffer);`
- L49 _public prototype_ `void Append(TArrayView<const float> InView);`
- L50 _public prototype_ `void Append(const FCheckedAudioBuffer& InBuffer);`
- L52 _private prototype_ `void DoCheck(TArrayView<const float> InBuffer) const;`
- L54 _private member_ `FString DescriptiveName;` — String so this can be procedural.
- L55 _private member_ `FAlignedFloatBuffer Buffer;` — Wrapped buffer.
- L57 _private member_ `ECheckBehavior Behavior = ECheckBehavior::Nothing;`
- L58 _private member_ `ECheckBufferFlags CheckFlags = ECheckBufferFlags::None;`
- L59 _private member_ `mutable ECheckBufferFlags FailedFlags = ECheckBufferFlags::None;`
- L60 _private member_ `mutable bool bFailedChecks = false;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SIGNALPROCESSING_API`
- L9 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/AlignedBlockBuffer.h` (Public)


#### class `Audio::FAlignedBlockBuffer`  
`class FAlignedBlockBuffer`  
_L14-86_
- desc: First In First Out Buffer designed for audio buffers. Generally performs best when buffers are greater than 16 samples, optimally for buffers between 256 to 4096 samples.  Memory operations are designed for audio applications by ensuring memory allocations only occur in the constructor or when capacity is altered, memory freeing only happens in the destructor or when capacity is altered. All assignments are performed using block memory copies.
- L19 _public prototype_ `FAlignedBlockBuffer(int32 InSampleCapacity=8192, int32 InMaxNumInspectSamples=1024, uint32 InByteAlignment=AUDIO_SIMD_BYTE_ALIGNMENT, uint32 InAllocByteAlignment=AUDIO_BUFFER_ALIGNMENT);` — Constructor
- L22 _public prototype_ `~FAlignedBlockBuffer() throw();` — Destructor
- L25 _public prototype_ `int32 GetSampleCapacity() const;` — Maximum size of buffer
- L28 _public prototype_ `int32 GetNumAvailable() const;` — Amount of samples left over in buffer
- L31 _public prototype_ `void AddZeros(int32 InNum);` — Add zeros to the buffer
- L34 _public prototype_ `void AddSamples(const float* InSamples, int32 InNum);` — Add samples to the buffer.
- L37 _public prototype_ `void RemoveSamples(int32 InNum);` — Remove samples from the buffer
- L40 _public prototype_ `void ClearSamples();` — Clear entire buffer
- L45 _public prototype_ `const float* InspectSamples(int32 InNum, int32 InOffset=0);` — Inspect samples in the buffer. Returned samples abide by the memory alignment specified during construction. Warning: Not thread safe. The returned pointer is only valid as long as this object exists and before any mutating operations are made to this object.
- L48 _public prototype_ `int32 GetMaxNumInspectSamples() const;` — Maximum number of elements that can be inspected
- L53 _protected prototype_ `void SetMaxNumInspectSamples(int32 InMax);` — Set the maximum number of elements that can be inspected
- L55 _protected prototype_ `float* AllocateAlignedFloatArray(int32 InNum) const;`
- L56 _protected prototype_ `void FreeFloatArray(float*& Array) const;`
- L57 _protected prototype_ `void ZeroFloatArray(float* InArray, int32 InNum) const;`
- L58 _protected prototype_ `void CopyFloatArray(float* ToArray, const float* FromArray, int32 InNum) const;`
- L62 _private prototype_ `int32 CheckNumAndIncrementWriteCount(int32 InNum);`
- L65 _private prototype_ `FAlignedBlockBuffer& operator=(const FAlignedBlockBuffer& rhs);` — Hide copy and assignment operators
- L66 _private prototype_ `FAlignedBlockBuffer(const FAlignedBlockBuffer& CopyBuff);`
- L69 _private member_ `uint32 AllocByteAlignment;` — Alignment definition
- L70 _private member_ `uint32 ByteAlignment;`
- L71 _private member_ `uint32 FloatAlignment;`
- L74 _private member_ `float* InternalBuffer;` — Internal memory
- L75 _private member_ `float* RolloverBuffer;`
- L78 _private member_ `float* ReadPointer;` — Read and write pointers
- L79 _private member_ `float* WritePointer;`
- L81 _private member_ `int32 SampleCapacity;`
- L82 _private member_ `int32 MaxNumInspectSamples;`
- L83 _private member_ `int32 WriteCount;`
- L84 _private member_ `int32 WritePos;`
- L85 _private member_ `int32 ReadPos;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/AlignedBuffer.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define AUDIO_BUFFER_ALIGNMENT 16` — TODO: Move BufferVectorOperations AUDIO_BUFFER_ALIGNMENT define to more central location and reference here.
- L12 _macro_ `#define AUDIO_SIMD_BYTE_ALIGNMENT (16)`
- L13 _macro_ `#define AUDIO_NUM_FLOATS_PER_VECTOR_REGISTER (4)`
- L16 _namespace_ `namespace Audio`
- L19 _typedef_ `using FAudioBufferAlignedAllocator = TAlignedHeapAllocator<AUDIO_BUFFER_ALIGNMENT>;` (scope `Audio`) — Aligned allocator used for fast operations.
- L21 _typedef_ `using FAlignedByteBuffer = TArray<uint8, FAudioBufferAlignedAllocator>;` (scope `Audio`)
- L22 _typedef_ `using FAlignedFloatBuffer = TArray<float, FAudioBufferAlignedAllocator>;` (scope `Audio`)
- L23 _typedef_ `using FAlignedInt32Buffer = TArray<int32, FAudioBufferAlignedAllocator>;` (scope `Audio`)
- L26 _typedef_ `typedef TArray<uint8, FAudioBufferAlignedAllocator> AlignedByteBuffer;` (scope `Audio`) — Deprecated in favor of versions above
- L27 _typedef_ `typedef TArray<float, FAudioBufferAlignedAllocator> AlignedFloatBuffer;` (scope `Audio`)
- L28 _typedef_ `typedef TArray<int32, FAudioBufferAlignedAllocator> AlignedInt32Buffer;` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/AllPassFilter.h` (Public)


#### class `Audio::FDelayAPF`  
`class FDelayAPF : public FDelay`  
_L12-31_
- inherits: `FDelay`
- desc: Implementation of a delay line with a feedback/feedforward gain coefficient APF filters pass all frequencies but changes phase relationships of frequencies
- L16 _public prototype_ `FDelayAPF();` — Constructor
- L19 _public prototype_ `~FDelayAPF();` — Destructor
- L22 _public function_ `void SetG(float InG)` — Set the APF feedback/feedforward gain coefficient
- L25 _public prototype_ `virtual float ProcessAudioSample(const float pInput) override;` — overrides
- L29 _protected member_ `float G;` — Feedback/Feedforward gain coefficient

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/AllPassFractionalDelay.h` (Public)


#### class `Audio::FAllPassFractionalDelay`  
`class FAllPassFractionalDelay`  
_L12-43_
- desc: Performs a fractional delay utilzing a single order all pass filter.
- L17 _public prototype_ `FAllPassFractionalDelay(int32 InMaxDelay, int32 InNumInternalBufferSamples);` — InMaxDelay sets the maximum allowable delay that this object can support. The minimum delay is 0.5 InNumInternalBufferSamples sets the maximum block processing size.
- L19 _public prototype_ `~FAllPassFractionalDelay();`
- L23 _public prototype_ `void ProcessAudio(const FAlignedFloatBuffer& InSamples, const FAlignedFloatBuffer& InDelays, FAlignedFloatBuffer& OutSamples);` — Apply delay to InSamples. Fill OutSamples with data from the delay line at a delay of InDelay. InDelay must be equal length to InSamples.
- L26 _public prototype_ `void Reset();` — Set all values in internal delay line to zero.
- L29 _private prototype_ `void ProcessAudioBlock(const float* InSamples, const float* InDelays, const int32 InNum, float* OutSamples);`
- L31 _private member_ `int32 MaxDelay;`
- L32 _private member_ `int32 NumInternalBufferSamples;`
- L35 _private member_ `float Z1;` — Delay element for all pass filter.
- L37 _private member_ `TUniquePtr<FAlignedBlockBuffer> DelayLine;`
- L39 _private member_ `FAlignedFloatBuffer Coefficients;`
- L40 _private member_ `FAlignedFloatBuffer FractionalDelays;`
- L41 _private member_ `FAlignedInt32Buffer IntegerDelays;`
- L42 _private member_ `FAlignedInt32Buffer IntegerDelayOffsets;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/Ambisonics.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`
- L9 _prototype_ `void EncodeMonoAmbisonicMixIn(TArrayView<const float> Src, TArrayView<float*> Dst, TArrayView<const float> AmbisonicGains);` (scope `Audio`)
- L10 _prototype_ `void DecodeMonoAmbisonicMixIn(TArrayView<const float*> Src, TArrayView<float> Dst, TArrayView<const float> AmbisonicGains);` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/Amp.h` (Public)


#### struct `Audio::FWetDry`  
`struct FWetDry`  
_L10-23_
- L13 _public member_ `float WetLevel;` — Level of wet signal
- L16 _public member_ `float DryLevel;` — Level of dry signal
- L18 _public function_ `FWetDry(float InWetLevel = 1.0f, float InDryLevel = 0.0f) : WetLevel(InWetLevel) , DryLevel(InDryLevel)`

#### class `Audio::FAmp`  
`class FAmp`  
_L26-132_
- desc: Class which manages scaling audio input and performing panning operations
- L29 _public prototype_ `FAmp();`
- L30 _public prototype_ `~FAmp();`
- L33 _public prototype_ `void Init(const int32 InVoiceId = INDEX_NONE, FModulationMatrix* ModMatrix = nullptr);` — Initializes the amp with the mod matrix
- L36 _public prototype_ `void SetGainDb(const float InGainDB);` — Sets the direct gain in decibel
- L39 _public prototype_ `void SetGainModDb(const float InGainModDb);` — Sets the gain modulation in decibel
- L42 _public prototype_ `void SetGain(const float InGainLinear);` — Sets the direct gain in linear
- L45 _public prototype_ `void SetGainMod(const float InBipolarGainModLinear);` — Sets the gain modulation in linear. Expects modulation value to be bipolar (for AM synth, etc)
- L48 _public prototype_ `void SetGainEnv(const float InGainEnv);` — Sets the gain based on an envelope value
- L51 _public prototype_ `void SetGainEnvDb(const float InGainEnvDb);` — Sets the gain based on an envelope value
- L54 _public prototype_ `void SetGainRange(const float InMin, const float InMax);` — Change the allowed range of the gain output
- L57 _public prototype_ `void SetVelocity(const float InVelocity);` — Sets the gain using a midi velocity value
- L60 _public prototype_ `void SetPan(const float InPan);` — Sets the pan
- L63 _public prototype_ `void SetPanModulator(const float InPanMod);` — Sets the pan modulator
- L66 _public prototype_ `void ProcessAudio(const float LeftIn, float* LeftOutput, float* RightOutput);` — Takes mono input and generates stereo output
- L69 _public prototype_ `void ProcessAudio(const float LeftIn, const float RightIn, float* LeftOutput, float* RightOutput);` — Takes stereo input and generates stereo output
- L72 _public prototype_ `void Generate(float& OutGainLeft, float& OutGainRight);` — Generates a new gain value for left and right outputs.
- L74 _public prototype_ `void Reset();`
- L77 _public prototype_ `void Update();` — Updates the final output left and right gain based on current settings
- L79 _public function_ `const FPatchDestination GetModDestGainScale() const`
- L80 _public function_ `const FPatchDestination GetModDestGainEnv() const`
- L81 _public function_ `const FPatchDestination GetModDestPan() const`
- L84 _protected member_ `int32 VoiceId;`
- L87 _protected member_ `float LeftGain;` — The final left and right output gain values
- L88 _protected member_ `float RightGain;`
- L91 _protected member_ `float TargetLeftGain;` — Values used for lerping gain values to avoid zippering
- L92 _protected member_ `float TargetRightGain;`
- L94 _protected member_ `int32 TargetDeltaSamples;`
- L95 _protected member_ `int32 CurrentLerpSample;`
- L97 _protected member_ `float TargetLeftSlope;`
- L98 _protected member_ `float TargetRightSlope;`
- L102 _protected member_ `float GainMin;` — Min and max output gain, can be changed based on need
- L103 _protected member_ `float GainMax;`
- L106 _protected member_ `float GainControl;` — Direct input gain control (i.e. gain slider)
- L109 _protected member_ `float GainVelocity;` — Gain due to midi velocity
- L112 _protected member_ `float GainMod;` — A modulated value of gain, can be used for tremolo or amplitude modulation
- L115 _protected member_ `float GainEnv;` — Gain set from envelope
- L118 _protected member_ `float Pan;` — Linear pan value [-1.0, 1.0]
- L121 _protected member_ `float PanMod;` — Linear pan modulator
- L124 _protected member_ `FModulationMatrix* ModMatrix;` — Mod matrix
- L125 _protected member_ `FPatchDestination GainScaleDest;`
- L126 _protected member_ `FPatchDestination GainEnvDest;`
- L127 _protected member_ `FPatchDestination GainPanDest;`
- L130 _protected member_ `bool bChanged;` — Whether or not something changed since the last time generate was called

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/AudioBufferDistanceAttenuation.h` (Public)


#### struct `Audio::FAudioBufferDistanceAttenuationSettings`  
`struct FAudioBufferDistanceAttenuationSettings`  
_L12-25_
- desc: Settings for audio buffer distance attenuation
- L14 _public prototype_ `FAudioBufferDistanceAttenuationSettings() = default;`
- L15 _public prototype_ `~FAudioBufferDistanceAttenuationSettings() = default;`
- L18 _public member_ `FVector2D DistanceRange = { 400.0f, 4000.0f };` — The min and max distance range to apply attenuation to the voip stream based on distance from listener.
- L21 _public member_ `float AttenuationDbAtMaxRange = -60.0f;` — The attenuation (in Decibels) at max range. The attenuation will be performed in dB and clamped to zero (linear) greater than max attenuation past the max range.
- L24 _public member_ `Audio::FLinearCurve AttenuationCurve;` — A curve (values are expected to be normalized between 0.0 and 1.0) to use to control attenuation vs distance from listener.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L35 _prototype_ `void DistanceAttenuationProcessAudio( TArrayView<int16>& InOutBuffer, uint32 InNumChannels, float InDistance, const FAudioBufferDistanceAttenuationSettings& InSettings, float& InOutAttenuation);` (scope `Audio`) — Processes the audio buffer with the given distance attenuation InOutAudioFrames - The audio buffer to attenuate. Note there is a function override for int16 and float formats. InFrameCount - The number of frames of audio in the buffer InNumChannels - The number of channels of audio in the buffer InDistance - The current distance to use to compute the attenuation InSettings - The settings to use to compute the attenuation InOutAttenuation - The input value of previous attenuation and the output value after performing the current distance attenuation. Use -1.0 if this is the first call to this function. The value is used to interpolate the attenuation smoothly.
- L42 _prototype_ `void DistanceAttenuationProcessAudio( TArrayView<float>& InOutBuffer, uint32 InNumChannels, float InDistance, const FAudioBufferDistanceAttenuationSettings& InSettings, float& InOutAttenuation);` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/AudioChannelFormatConverter.h` (Public)


#### class `Audio::IChannelFormatConverter`  
`class IChannelFormatConverter`  
_L13-48_
- desc: Inteface for Channel Format Converters which process deinterleaved audio.
- L30 _public prototype_ `virtual ~IChannelFormatConverter() = default;`
- L33 _public prototype_ `virtual const FInputFormat& GetInputFormat() const = 0;` — Return the input format handled by this converter.
- L36 _public prototype_ `virtual const FOutputFormat& GetOutputFormat() const = 0;` — Return the output format handled by this converter.
- L47 _public prototype_ `virtual void ProcessAudio(const TArray<FAlignedFloatBuffer>& InInputBuffers, TArray<FAlignedFloatBuffer>& OutOutputBuffers) = 0;` — Converter the audio format from the FInputFormat to the FOutputFormat. The input buffer array must have the same number of channels as the FInputFormat return from GetInputFormat().  Each buffer within that array must have the same number of samples. @param InInputBuffers - An array of input audio buffers. @param OutOutputBuffers - An array of buffers where output audio is stored.

#### struct `Audio::IChannelFormatConverter::FInputFormat`  
`struct FInputFormat`  
_L17-21_
- desc: Description of input audio format.
- L20 _public member_ `int32 NumChannels = 0;` — Number of channels in input audio format.

#### struct `Audio::IChannelFormatConverter::FOutputFormat`  
`struct FOutputFormat`  
_L24-28_
- desc: Description of output audio format.
- L27 _public member_ `int32 NumChannels = 0;` — Number of channels in output audio format.

#### class `Audio::FBaseChannelFormatConverter`  
`class FBaseChannelFormatConverter : public IChannelFormatConverter`  
_L54-219_
- inherits: `IChannelFormatConverter`
- desc: FBaseChannelFormatConverter implements channel conversion using a simple mixing matrix.
- L74 _public prototype_ `virtual ~FBaseChannelFormatConverter();`
- L77 _public prototype_ `const FInputFormat& GetInputFormat() const override;` — Return the input format handled by this converter.
- L80 _public prototype_ `const FOutputFormat& GetOutputFormat() const override;` — Return the output format handled by this converter.
- L89 _public prototype_ `void SetOutputGain(float InOutputGain, bool bFadeToGain=true);` — Sets the output gain scalar to apply to all output audio. @param InOutputGain - Scalar gain value. @param bFadeToGain - If true, gain values are linearly faded over the duration of a single buffer. If false, gain values are applied immediately.
- L98 _public prototype_ `void SetMixGain(const FChannelMixEntry& InEntry, bool bFadeToGain=true);` — Sets the gain scalar to apply to a specific input/output channel pair. @param InMixEntry - Description of mix routing and gain. @param bFadeToGain - If true, gain values are linearly faded over the duration of a single buffer. If false, gain values are applied immediately.
- L110 _public prototype_ `void SetMixGain(int32 InInputChannelIndex, int32 InOutputChannelIndex, float InGain, bool bFadeToGain=true);` — Sets the gain scalar to apply to a specific input/output channel pair. @param InInputChannelIndex - The index of the source channel audio. @param InOutputChannelIndex - The index of the destination channel audio. @param InGain - The scalar gain to apply to the source channel before adding it to the destination channel. @param bFadeToGain - If true, gain values are linearly faded over the duration of a single buffer. If false, gain values are applied immediately.
- L118 _public prototype_ `float GetTargetMixGain(int32 InInputChannelIndex, int32 InOutputChannelIndex) const;` — Returns the scalar gain used to mix the input channel index into the output channel index. If the gains are to be faded during the subsequent call to ProcessAudio(), this will return the ending gain.
- L125 _public prototype_ `float GetTargetOutputGain() const;` — Returns the scalar gain applied to the output audio. If the gain is to be faded during the subsequent call to ProcessAudio(), this will return the ending gain.
- L136 _public prototype_ `void ProcessAudio(const TArray<FAlignedFloatBuffer>& InInputBuffers, TArray<FAlignedFloatBuffer>& OutOutputBuffers) override;` — Converter the audio format from the FInputFormat to the FOutputFormat. The input buffer array must have the same number of channels as the FInputFormat return from GetInputFormat().  Each buffer within that array must have `InNumFramesPerCall` as set on creation. @param InInputBuffers - An array of input audio buffers. @param OutOutputBuffers - An array of buffers where output audio is stored.
- L148 _public prototype_ `static TUniquePtr<FBaseChannelFormatConverter> CreateBaseFormatConverter(const FInputFormat& InInputFormat, const FOutputFormat& InOutputFormat, TArrayView<const FChannelMixEntry> InMixEntries, int32 InNumFramesPerCall);` — Create a FBaseChannelFormatConverter @param InInputFormat - The format of the input audio. @param InOutputFormat - The desired output audio format. @param InMixEntries - An array of mixing values to use to mix input audio to output audio. @param InNumFramesPerCall - The number of frames used for each call to ProcessAudio. @return A TUniquePtr to a FBaseChannelFormatConverter.
- L152 _protected prototype_ `FBaseChannelFormatConverter(const FInputFormat& InInputFormat, const FOutputFormat& InOutputFormat, TArrayView<const FChannelMixEntry> InMixEntries, int32 InNumFramesPerCall);`
- L197 _private function_ `friend bool operator<(const FChannelMixKey& InLHS, const FChannelMixKey& InRHS)` — Operator needed for using in a TSortedMap
- L209 _private member_ `FInputFormat InputFormat;` — The input audio format
- L212 _private member_ `FOutputFormat OutputFormat;` — The output audio format.
- L215 _private member_ `FOutputGainState OutputGainState;` — Gain states
- L216 _private member_ `TSortedMap<FChannelMixKey, FChannelMixState> ChannelMixStates;`
- L218 _private member_ `int32 NumFramesPerCall;`

#### struct `Audio::FBaseChannelFormatConverter::FChannelMixEntry`  
`struct FChannelMixEntry`  
_L61-72_
- desc: FChannelMixEntry denotes how an input channel should be mixed into an output channel.
- L64 _public member_ `int32 InputChannelIndex = 0;` — The index of the input channel to use as a source.
- L67 _public member_ `int32 OutputChannelIndex = 0;` — The index of the output channel to use as a destination.
- L71 _public member_ `float Gain = 0.f;` — The scalar gain to apply to input audio samples when adding them to output audio samples.

#### struct `Audio::FBaseChannelFormatConverter::FOutputGainState`  
`struct FOutputGainState`  
_L157-162_
- desc: Output gain state holds current and next gain levels.
- L159 _public member_ `float Gain = 1.f;`
- L160 _public member_ `float NextGain = 0.f;`
- L161 _public member_ `bool bFadeToNextGain = false;`

#### struct `Audio::FBaseChannelFormatConverter::FChannelMixState`  
`struct FChannelMixState : FChannelMixEntry`  
_L165-176_
- inherits: `FChannelMixEntry`
- desc: Channel mix entry holds current and next gain levels for a mix entry.
- L167 _public prototype_ `FChannelMixState() = default;`
- L169 _public function_ `FChannelMixState(const FChannelMixEntry& InEntry) : FChannelMixEntry(InEntry)`
- L174 _public member_ `bool bFadeToNextGain = false;`
- L175 _public member_ `float NextGain = 0.f;`

#### struct `Audio::FBaseChannelFormatConverter::FChannelMixKey`  
`struct FChannelMixKey`  
_L179-206_
- desc: Channel mix key is used to lookup entries from a TSortedMap
- L181 _public member_ `const int32 InputChannelIndex = 0;`
- L182 _public member_ `const int32 OutputChannelIndex = 0;`
- L184 _public function_ `FChannelMixKey(int32 InInputChannelIndex, int32 InOutputChannelIndex) : InputChannelIndex(InInputChannelIndex) , OutputChannelIndex(InOutputChannelIndex)`
- L190 _public function_ `FChannelMixKey(const FChannelMixEntry& InEntry) : InputChannelIndex(InEntry.InputChannelIndex) , OutputChannelIndex(InEntry.OutputChannelIndex)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/AudioChannelUtils.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define UE_API SIGNALPROCESSING_API`
- L8 _namespace_ `namespace Audio`
- L8 _namespace_ `namespace ChannelUtils` (scope `Audio`)
- L11 _prototype_ `bool GetChannelTypeAtIndex(const int32 Index, EAudioMixerChannel::Type& OutType);` (scope `Audio::ChannelUtils`) — Helper function to get the channel map type at the given index.
- L14 _prototype_ `float GetChannelWeight(EAudioMixerChannel::Type InType);` (scope `Audio::ChannelUtils`) — Helper function to get the channel weight given a channel type.

### `Source/Runtime/SignalProcessing/Public/DSP/AudioDebuggingUtilities.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define USE_AUDIO_DEBUGGING UE_BUILD_DEBUG`
- L9 _prototype_ `void BreakWhenAudible(float* InBuffer, int32 NumSamples);`
- L10 _prototype_ `void BreakWhenTooLoud(float* InBuffer, int32 NumSamples);`
- L13 _macro_ `#define BREAK_WHEN_AUDIBLE(Ptr, Num) BreakWhenAudible(Ptr, Num);`
- L14 _macro_ `#define BREAK_WHEN_TOO_LOUD(Ptr, Num) BreakWhenTooLoud(Ptr, Num);`
- L16 _macro_ `#define BREAK_WHEN_AUDIBLE(Ptr, Num)`
- L17 _macro_ `#define BREAK_WHEN_TOO_LOUD(Ptr, Num)`

### `Source/Runtime/SignalProcessing/Public/DSP/AudioFFT.h` (Public)


#### enum `Audio::ESpectrumType`  
`enum class ESpectrumType : uint8`  
_L15-19_
- L17 _public enumerator_ `MagnitudeSpectrum`
- L18 _public enumerator_ `PowerSpectrum`

#### enum `Audio::EWindowType`  
`enum class EWindowType : uint8`  
_L22-28_
- L24 _public enumerator_ `None` — No window is applied. Technically a boxcar window.
- L25 _public enumerator_ `Hamming` — Mainlobe width of -3 dB and sidelove attenuation of ~-40 dB. Good for COLA.
- L26 _public enumerator_ `Hann` — Mainlobe width of -3 dB and sidelobe attenuation of ~-30dB. Good for COLA.
- L27 _public enumerator_ `Blackman` — Mainlobe width of -3 dB and sidelobe attenuation of ~-60db. Tricky for COLA.

#### class `Audio::FWindow`  
`class FWindow`  
_L45-74_
- desc: Class used to generate, contain and apply a DSP window of a given type.
- L48 _public prototype_ `FWindow() = delete;`
- L59 _public prototype_ `FWindow(EWindowType InType, int32 InNumFrames, int32 InNumChannels, bool bIsPeriodic);` — Constructor. Allocates buffer and generates window inside of it. @param InType: The type of window that should be generated. @param InNumFrames: The number of samples that should be generated divided by the number of channels. @param InNumChannels: The amount of channels that will be used in the signal this is applied to. @param bIsPeriodic: If false, the window will be symmetrical. If true, the window will be periodic. Generally, set this to false if using this window with an STFT, but use true if this window will be used on an entire, self-contained signal.
- L63 _public prototype_ `void ApplyToBuffer(float* InBuffer);` — Apply this window to InBuffer, which is expected to be an interleaved buffer with the same amount of frames and channels this window was constructed with.
- L65 _public prototype_ `EWindowType GetWindowType() const;`
- L68 _private member_ `EWindowType WindowType;`
- L69 _private member_ `FAlignedFloatBuffer WindowBuffer;`
- L70 _private member_ `int32 NumSamples;`
- L73 _private prototype_ `void Generate(int32 NumFrames, int32 NumChannels, bool bIsPeriodic);` — Generate the window. Called on constructor.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Audio`
- L31 _prototype_ `void GenerateRectangularWindow(float* WindowBuffer, int32 NumFrames, int32 NumChannels);` (scope `Audio`) — Utility functions for generating different types of windows. Called in FWindow::Generate.
- L32 _prototype_ `void GenerateHammingWindow(float* WindowBuffer, int32 NumFrames, int32 NumChannels, bool bIsPeriodic);` (scope `Audio`)
- L33 _prototype_ `void GenerateHannWindow(float* WindowBuffer, int32 NumFrames, int32 NumChannels, bool bIsPeriodic);` (scope `Audio`)
- L34 _prototype_ `void GenerateBlackmanWindow(float* WindowBuffer, int32 NumFrames, int32 NumChannels, bool bIsPeriodic);` (scope `Audio`)
- L35 _prototype_ `void GenerateWindow(float* InOutWindowBuffer, EWindowType InType, int32 InNumFrames, int32 InNumChannels, bool bIsPeriodic);` (scope `Audio`)
- L40 _prototype_ `uint32 GetCOLAHopSizeForWindow(EWindowType InType, uint32 WindowLength);` (scope `Audio`) — Returns the hop size in samples necessary to maintain constant overlap add. For more information on COLA, see the following page: https://ccrma.stanford.edu/~jos/sasp/Overlap_Add_OLA_STFT_Processing.html
- L77 _prototype_ `int32 CeilLog2(int32 InNum);` (scope `Audio`) — Return the ceiling of the log2 of InNum
- L81 _prototype_ `float GetPowerSpectrumScaling(int32 FFTSize, EFFTScaling InCurrentScaling, EFFTScaling InTargetScaling);` (scope `Audio`) — Return the scaling factor needed to apply to a power spectrum given a current and target FFT scaling.
- L85 _prototype_ `void ScalePowerSpectrumInPlace(int32 FFTSize, EFFTScaling InCurrentScaling, EFFTScaling InTargetScaling, TArrayView<float> InPowerSpectrum);` (scope `Audio`) — Scale the power spectrum to remove any scaling introduced by the FFT algorithm implementation.

### `Source/Runtime/SignalProcessing/Public/DSP/AudioLinearCurve.h` (Public)


#### class `Audio::FLinearCurve`  
`class FLinearCurve`  
_L12-48_
- desc: A simple curve class that takes FVector2D points Required to decouple from Engine module
- L15 _public prototype_ `FLinearCurve() = default;`
- L16 _public prototype_ `FLinearCurve(const TArray<FVector2D>& InCurve);`
- L17 _public prototype_ `FLinearCurve(TArray<FVector2D>&& InCurve);`
- L19 _public prototype_ `virtual ~FLinearCurve() = default;`
- L22 _public prototype_ `void SetCurvePoints(const TArray<FVector2D>& InPoints);` — Sets curve array
- L23 _public prototype_ `void SetCurvePoints(TArray<FVector2D>&& InPoints);`
- L26 _public prototype_ `void ClearPoints();` — Clears the points array
- L29 _public function_ `int32 Num() const` — Returns the number of points in the curve
- L32 _public prototype_ `void AddPoint(const FVector2D& InPoint);` — Adds individual points
- L33 _public prototype_ `void AddPoints(const TArray<FVector2D>& InPoints);`
- L36 _public prototype_ `const TArray<FVector2D>& GetCurvePoints() const;` — Retrieves curve array
- L41 _public prototype_ `bool Eval(float InDomain, float& OutValue) const;` — Evaluates the curve with the given domain. Returns false if the curve was incapable of evaluation (i.e. empty). Will clamp the output to the values of the domain
- L46 _private prototype_ `void Sort();` — Will sort the curve according to increasing domain values
- L47 _private member_ `TArray<FVector2D> Points;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/BiQuadFilter.h` (Public)


#### class `Audio::FBiquad`  
`class UE_DEPRECATED(5.5, "Audio::FBiquad is deprecated in favor of Audio::FBiquadFilter due to performance issues") FBiquad`  
_L14-64_
- desc: Simple biquad filter structure handling a biquad formulation See: https://en.wikipedia.org/wiki/Digital_biquad_filter Calculations of coefficients are handled outside this class. Filter coefficients are public and are intended to be used externally.
- L17 _public function_ `FBiquad() : A0(1.0f) , A1(0.0f) , A2(0.0f) , B1(0.0f) , B2(0.0f)`
- L27 _public function_ `inline float ProcessAudio(const float InSample)`
- L43 _public function_ `void Reset()` — Reset the filter (flush delays)
- L53 _public member_ `float A0;` — Biquad filter coefficients
- L54 _public member_ `float A1;`
- L55 _public member_ `float A2;`
- L56 _public member_ `float B1;`
- L57 _public member_ `float B2;`
- L60 _protected member_ `float X_Z1;` — previous inputs z-transforms
- L61 _protected member_ `float X_Z2;`
- L62 _protected member_ `float Y_Z1;` — prvious outputs z-transforms
- L63 _protected member_ `float Y_Z2;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/BitCrusher.h` (Public)


#### class `Audio::FBitCrusher`  
`class FBitCrusher`  
_L12-54_
- desc: Bit crushing effect https://en.wikipedia.org/wiki/Bitcrusher
- L16 _public prototype_ `FBitCrusher();` — Constructor
- L19 _public prototype_ `~FBitCrusher();` — Destructor
- L22 _public prototype_ `void Init(const float InSampleRate, const int32 InNumChannels);` — Initialize the equalizer
- L25 _public prototype_ `void SetSampleRateCrush(const float InFrequency);` — The amount to reduce the sample rate of the audio stream.
- L28 _public prototype_ `void SetBitDepthCrush(const float InBitDepth);` — The amount to reduce the bit depth of the audio stream.
- L31 _public prototype_ `void ProcessAudioFrame(const float* InFrame, float* OutFrame);` — Processes audio
- L32 _public prototype_ `void ProcessAudio(const float* InBuffer, const int32 InNumSamples, float* OutBuffer);`
- L35 _public prototype_ `static float GetMaxBitDepth();` — Returns the maximum value given bit depths will be clamped to.
- L39 _private member_ `float SampleRate;` — i.e. 8 bit, etc. But can be float!
- L40 _private member_ `float BitDepth;`
- L41 _private member_ `float BitDelta;`
- L42 _private member_ `float ReciprocalBitDelta;`
- L45 _private member_ `float Phase;` — The current phase of the bit crusher
- L48 _private member_ `float PhaseDelta;` — The amount of phase to increment each sample
- L51 _private member_ `float LastOutput[2];` — Used to sample+hold the last output
- L53 _private member_ `int32 NumChannels;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/BlockCorrelator.h` (Public)


#### struct `Audio::FBlockCorrelatorSettings`  
`struct FBlockCorrelatorSettings`  
_L13-23_
- desc: Settings for block correlator
- L16 _public member_ `int32 Log2NumValuesInBlock = 10;` — Logarithm base 2 of the number of values in a block.
- L19 _public member_ `EWindowType WindowType = EWindowType::Blackman;` — Audio window type to apply to input.
- L22 _public member_ `bool bDoNormalize = true;` — If true, autocorrelation values will be normalized to reduce bias introduced by block windowing.

#### class `Audio::FBlockCorrelator`  
`class FBlockCorrelator`  
_L26-103_
- desc: Correlation calculator which utilizes FFT to perform fast correlation calculations.
- L30 _public prototype_ `FBlockCorrelator(const FBlockCorrelatorSettings& InSettings);` — Construct a block correlator with FBlockCorrelatorSettings
- L33 _public prototype_ `const FBlockCorrelatorSettings& GetSettings() const;` — Return settings used to construct block correlator.
- L36 _public prototype_ `int32 GetNumInputValues() const;` — Returns the number of input values to use when calling CrossCorrelate(...) or AutoCorrelate(...)
- L39 _public prototype_ `int32 GetNumOutputValues() const;` — Returns the number of output values to use when calling CrossCorrelate(...) or AutoCorrelate(...)
- L56 _public prototype_ `void CrossCorrelate(const FAlignedFloatBuffer& InputA, const FAlignedFloatBuffer& InputB, FAlignedFloatBuffer& Output);` — Cross correlate two input signals. The Output array is filled with the cross correlation between InputA and InputB. Care should be taken when interpreting the output as the elements are ordered so that the cross correlation value of zero lag is in the first element. CrossCorr[k] = Sum_n(InputA[n] * InputB[n + k]) Then for M = `GetNumInputValues()` the Output array contains: Output = [CrossCorr[0], CrossCorr[1], ..., CrossCorr[M-1], CrossCorr[M], CrossCorr[-M + 1], CrossCorr[-M + 2], ..., CrossCorr[-2], CrossCorr[-1]] @param InputA - First input block with `GetNumInputValues()` elements. @param InputB - Second input block with `GetNumInputValues()` elements. @param Output - Output block with `GetNumOutputValues()` elements.
- L71 _public prototype_ `void AutoCorrelate(const FAlignedFloatBuffer& Input, FAlignedFloatBuffer& Output);` — Autocorrelate an input signal. The Output array is filled with the autocorrelation of the Input. Care should be taken when interpreting the output as the elements are ordered so that the autocorrelation value of zero lag is in the first element. AutoCorr[k] = Sum_n(Input[n] * Input[n + k]) Then for M = `GetNumInputValues()` the Output array contains: Output = [AutoCorr[0], AutoCorr[1], ..., AutoCorr[M-1], AutoCorr[M], AutoCorr[-M + 1], AutoCorr[-M + 2], ..., AutoCorr[-2], AutoCorr[-1]] @param Input - input block with `GetNumInputValues()` elements. @param Output - Output block with `GetNumOutputValues()` elements.
- L76 _private prototype_ `void CyclicCrossCorrelate(const FAlignedFloatBuffer& InputA, const FAlignedFloatBuffer& InputB, FAlignedFloatBuffer& Output);` — No normalization or windowing.
- L79 _private prototype_ `void CyclicAutoCorrelate(const FAlignedFloatBuffer& Input, FAlignedFloatBuffer& Output);` — No normalization or windowing.
- L81 _private prototype_ `void InitializeNormalizationBuffer();`
- L83 _private member_ `FBlockCorrelatorSettings Settings;`
- L85 _private member_ `int32 NumValuesInBlock;`
- L86 _private member_ `int32 NumValuesInFFTRealBuffer;`
- L87 _private member_ `int32 NumValuesInFFTComplexBuffer;`
- L89 _private member_ `TUniquePtr<IFFTAlgorithm> FFTAlgorithm;`
- L91 _private member_ `FWindow Window;`
- L92 _private member_ `FAlignedFloatBuffer NormalizationBuffer;`
- L94 _private member_ `FAlignedFloatBuffer WindowedBufferA;`
- L95 _private member_ `FAlignedFloatBuffer WindowedBufferB;`
- L97 _private member_ `FAlignedFloatBuffer ComplexBufferA;`
- L98 _private member_ `FAlignedFloatBuffer ComplexBufferB;`
- L100 _private member_ `FAlignedFloatBuffer ComplexCorrelationBuffer;`
- L102 _private member_ `FAlignedFloatBuffer FullOutputBuffer;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/BufferDiagnostics.h` (Public)


#### enum `Audio::ECheckBufferFlags`  
`enum class ECheckBufferFlags : uint32`  
_L54-61_
- L56 _public enumerator_ `None = 0`
- L57 _public enumerator_ `Infinity = 1 << 1`
- L58 _public enumerator_ `Nan = 1 << 2`
- L59 _public enumerator_ `Denormalized = 1 << 3`
- L60 _public enumerator_ `All = Infinity | Nan | Denormalized`

#### enum `Audio::EBufferCheckBehavior`  
`enum class EBufferCheckBehavior : uint8`  
_L89-95_
- L91 _public enumerator_ `Nothing`
- L92 _public enumerator_ `Ensure`
- L93 _public enumerator_ `Log`
- L94 _public enumerator_ `Break`

#### struct `Audio::FCheckedBufferState`  
`struct FCheckedBufferState`  
_L97-120_
- L100 _public member_ `static FCriticalSection ListCs;` — Statics.
- L101 _public member_ `static FCheckedBufferState* Head;`
- L102 _public prototype_ `static void ForEach(TFunctionRef<void (FCheckedBufferState&)> InCmd);`
- L105 _public member_ `FCheckedBufferState* Next = nullptr;` — Per check state.
- L106 _public member_ `const TCHAR* Name = nullptr;`
- L107 _public member_ `int32 Line = 0;`
- L108 _public member_ `const TCHAR* File = nullptr;`
- L109 _public member_ `ECheckBufferFlags CheckFlags = ECheckBufferFlags::None;`
- L110 _public member_ `ECheckBufferFlags FailFlags = ECheckBufferFlags::None;`
- L111 _public member_ `EBufferCheckBehavior Behavior = EBufferCheckBehavior::Ensure;`
- L113 _public prototype_ `FCheckedBufferState(const int32 InLine, const TCHAR* InFile, const TCHAR* InName, const ECheckBufferFlags InCheckFlags = ECheckBufferFlags::None, const EBufferCheckBehavior InCheckBehavior = EBufferCheckBehavior::Ensure);`
- L118 _public prototype_ `bool DoCheck(TArrayView<const float> InBuffer);` — The CHECK_AUDIO_BUFFER Macros calls these two member functions.
- L119 _public prototype_ `void FailedBufferCheckImpl(const TCHAR* InFormat, ...) const;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Audio`
- L21 _function_ `inline static bool IsDenormalized(const float InValue)` (scope `Audio`) — Denormalized.
- L29 _prototype_ `int32 FindDenormalized(TArrayView<const float> InBuffer);` (scope `Audio`)
- L31 _prototype_ `bool ContainsDenormalized(TArrayView<const float> InBuffer);` (scope `Audio`)
- L36 _function_ `inline static bool IsInfinity(const float InValue)` (scope `Audio`) — Infinity.
- L44 _prototype_ `int32 FindInfinity(TArrayView<const float> InBuffer);` (scope `Audio`)
- L45 _prototype_ `bool ContainsInfinity(TArrayView<const float> InBuffer);` (scope `Audio`)
- L50 _prototype_ `int32 FindNan(TArrayView<const float> InBuffer);` (scope `Audio`) — NaN (Not a number)
- L52 _prototype_ `bool ContainsNan(TArrayView<const float> InBuffer);` (scope `Audio`)
- L63 _function_ `inline ECheckBufferFlags operator|(const ECheckBufferFlags A, const ECheckBufferFlags B)` (scope `Audio`)
- L68 _function_ `inline ECheckBufferFlags& operator|=(ECheckBufferFlags& Out, const ECheckBufferFlags Other)` (scope `Audio`)
- L73 _function_ `inline ECheckBufferFlags operator&(const ECheckBufferFlags A, const ECheckBufferFlags B)` (scope `Audio`)
- L79 _prototype_ `FString ToDelimitedString(const ECheckBufferFlags InEnum);` (scope `Audio`) — ToString with deliminators i.e. "Nan|Infinity" etc.
- L87 _prototype_ `bool CheckBuffer(TArrayView<const float> InBuffer, const ECheckBufferFlags InFlags, ECheckBufferFlags& OutFailedFlags);` (scope `Audio`) — Performs various tests on a audio buffer. @param InBuffer Buffer to examine @parm InFlags Bitfield of checks to perform @return true if check passes, false otherwise
- L127 _macro_ `#define WITH_AUDIO_BUFFERDIAGNOSTICS (!UE_BUILD_SHIPPING)` — By default enabled in all but ship
- L131 _macro_ `#define AUDIO_CHECK_BUFFER(BUFFER)\`
- L138 _macro_ `#define AUDIO_CHECK_BUFFER_NAMED(BUFFER,NAME)\`
- L145 _macro_ `#define AUDIO_CHECK_BUFFER_NAMED_MSG(BUFFER,NAME,MSG,...)\`
- L152 _macro_ `#define AUDIO_CHECK_BUFFER_NAMED(BUFFER,NAME)`
- L153 _macro_ `#define AUDIO_CHECK_BUFFER(BUFFER)`
- L154 _macro_ `#define AUDIO_CHECK_BUFFER_NAMED_MSG(BUFFER,NAME,MSG,...)`

### `Source/Runtime/SignalProcessing/Public/DSP/BufferOnePoleLPF.h` (Public)


#### class `Audio::FBufferOnePoleLPF`  
`class FBufferOnePoleLPF`  
_L13-44_
- desc: Simple 1-pole lowpass filter
- L18 _public prototype_ `FBufferOnePoleLPF(float InG = 0.0f);` — Constructor
- L21 _public prototype_ `void SetG(float InG);` — Set the LPF gain coefficient
- L24 _public prototype_ `void Reset();` — Resets the sample delay to 0
- L27 _public prototype_ `void FlushAudio();` — Resets the audio to silence.
- L30 _public prototype_ `void SetFrequency(const float InFrequency);` — Sets the filter frequency using normalized frequency (between 0.0 and 1.0f or 0.0 hz and Nyquist Frequency in Hz)
- L33 _public prototype_ `void ProcessAudio(const FAlignedFloatBuffer& InSamples, FAlignedFloatBuffer& OutSamples);` — Process InSamples and place filtered audio in OutSamples
- L36 _protected member_ `float CutoffFrequency;`
- L39 _protected member_ `float B1;` — Filter coefficients
- L40 _protected member_ `float A0;`
- L43 _protected member_ `float Z1;` — 1-sample delay

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/BufferVectorOperations.h` (Public)


#### class `Audio::FBufferLinearEase`  
`class FBufferLinearEase`  
_L155-180_
- desc: Class which handles a vectorized interpolation of an entire buffer to the values of a target buffer
- L158 _public prototype_ `FBufferLinearEase();`
- L159 _public prototype_ `FBufferLinearEase(const FAlignedFloatBuffer& InSourceValues, const FAlignedFloatBuffer& InTargetValues, int32 InLerpLength);`
- L160 _public prototype_ `~FBufferLinearEase();`
- L163 _public prototype_ `void Init(const FAlignedFloatBuffer& InSourceValues, const FAlignedFloatBuffer& InTargetValues, int32 InLerpLength);` — will cache SourceValues ptr and manually update SourceValues on Update()
- L166 _public prototype_ `bool Update(FAlignedFloatBuffer& InSourceValues);` — Performs Vectorized update of SourceValues float buffer. Returns true if interpolation is complete
- L169 _public prototype_ `bool Update(uint32 StepsToJumpForward, FAlignedFloatBuffer& InSourceValues);` — Update overloaded to let you jump forward more than a single time-step
- L172 _public prototype_ `const FAlignedFloatBuffer& GetDeltaBuffer();` — returns const reference to the deltas buffer for doing interpolation elsewhere
- L175 _private member_ `int32 BufferLength {0};`
- L176 _private member_ `int32 LerpLength {0};`
- L177 _private member_ `int32 CurrentLerpStep{0};`
- L178 _private member_ `FAlignedFloatBuffer DeltaBuffer;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L17 _prototype_ `void Apply2ChannelGain(FAlignedFloatBuffer& StereoBuffer, const float* RESTRICT Gains);` (scope `Audio`) — Takes a 2 channel interleaved buffer and applies Gains to it. Gains is expected to point to a 2 float long buffer. StereoBuffer must have an even number of frames. If StartGains and EndGains are provided, this function will interpolate between the two across the buffer.
- L18 _prototype_ `void Apply2ChannelGain(float* RESTRICT StereoBuffer, int32 NumSamples, const float* RESTRICT Gains);` (scope `Audio`)
- L19 _prototype_ `void Apply2ChannelGain(FAlignedFloatBuffer& StereoBuffer, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L20 _prototype_ `void Apply2ChannelGain(float* RESTRICT StereoBuffer, int32 NumSamples, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L26 _prototype_ `void MixMonoTo2ChannelsFast(const FAlignedFloatBuffer& MonoBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT Gains);` (scope `Audio`) — Takes a 1 channel buffer and mixes it to a stereo buffer using Gains. Gains is expected to point to a 2 float long buffer. these buffers must have an even number of frames. If StartGains and EndGains are provided, this function will interpolate between the two across the buffer.
- L27 _prototype_ `void MixMonoTo2ChannelsFast(const float* RESTRICT MonoBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT Gains);` (scope `Audio`)
- L28 _prototype_ `void MixMonoTo2ChannelsFast(const FAlignedFloatBuffer& MonoBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L29 _prototype_ `void MixMonoTo2ChannelsFast(const float* RESTRICT MonoBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L30 _prototype_ `void MixMonoTo2ChannelsFast(const FAlignedFloatBuffer& MonoBuffer, FAlignedFloatBuffer& DestinationBuffer);` (scope `Audio`)
- L31 _prototype_ `void MixMonoTo2ChannelsFast(const float* RESTRICT MonoBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames);` (scope `Audio`)
- L38 _prototype_ `void Mix2ChannelsTo2ChannelsFast(const FAlignedFloatBuffer& SourceBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT Gains);` (scope `Audio`) — Takes a 2 channel buffer and mixes it to an 2 channel interleaved buffer using Gains. Gains is expected to point to a 16 float long buffer. Output gains for the left input channel should be the first 8 values in Gains, and Output gains for the right input channel should be rest. NumFrames must be a multiple of 4. If StartGains and EndGains are provided, this function will interpolate between the two across the buffer.
- L39 _prototype_ `void Mix2ChannelsTo2ChannelsFast(const float* RESTRICT SourceBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT Gains);` (scope `Audio`)
- L40 _prototype_ `void Mix2ChannelsTo2ChannelsFast(const FAlignedFloatBuffer& SourceBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L41 _prototype_ `void Mix2ChannelsTo2ChannelsFast(const float* RESTRICT SourceBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L46 _prototype_ `void Apply4ChannelGain(FAlignedFloatBuffer& InterleavedBuffer, const float* RESTRICT Gains);` (scope `Audio`) — Takes a 4 channel interleaved buffer and applies Gains to it. Gains is expected to point to a 2 float long buffer. If StartGains and EndGains are provided, this function will interpolate between the two across the buffer.
- L47 _prototype_ `void Apply4ChannelGain(float* RESTRICT InterleavedBuffer, int32 NumSamples, const float* RESTRICT Gains);` (scope `Audio`)
- L48 _prototype_ `void Apply4ChannelGain(FAlignedFloatBuffer& InterleavedBuffer, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L49 _prototype_ `void Apply4ChannelGain(float* RESTRICT InterleavedBuffer, int32 NumSamples, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L55 _prototype_ `void MixMonoTo4ChannelsFast(const FAlignedFloatBuffer& MonoBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT Gains);` (scope `Audio`) — Takes a 1 channel buffer and mixes it to an 8 channel interleaved buffer using Gains. Gains is expected to point to a 8 float long buffer. these buffers must have an even number of frames. If StartGains and EndGains are provided, this function will interpolate between the two across the buffer.
- L56 _prototype_ `void MixMonoTo4ChannelsFast(const float* RESTRICT MonoBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT Gains);` (scope `Audio`)
- L57 _prototype_ `void MixMonoTo4ChannelsFast(const FAlignedFloatBuffer& MonoBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L58 _prototype_ `void MixMonoTo4ChannelsFast(const float* RESTRICT MonoBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L65 _prototype_ `void Mix2ChannelsTo4ChannelsFast(const FAlignedFloatBuffer& SourceBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT Gains);` (scope `Audio`) — Takes a 2 channel buffer and mixes it to an 8 channel interleaved buffer using Gains. Gains is expected to point to a 16 float long buffer. Output gains for the left input channel should be the first 8 values in Gains, and Output gains for the right input channel should be rest. NumFrames must be a multiple of 4. If StartGains and EndGains are provided, this function will interpolate between the two across the buffer.
- L66 _prototype_ `void Mix2ChannelsTo4ChannelsFast(const float* RESTRICT SourceBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT Gains);` (scope `Audio`)
- L67 _prototype_ `void Mix2ChannelsTo4ChannelsFast(const FAlignedFloatBuffer& SourceBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L68 _prototype_ `void Mix2ChannelsTo4ChannelsFast(const float* RESTRICT SourceBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L73 _prototype_ `void Apply6ChannelGain(FAlignedFloatBuffer& InterleavedBuffer, const float* RESTRICT Gains);` (scope `Audio`) — Takes a 6 channel interleaved buffer and applies Gains to it. Gains is expected to point to a 2 float long buffer. InterleavedBuffer must have an even number of frames.
- L74 _prototype_ `void Apply6ChannelGain(float* RESTRICT InterleavedBuffer, int32 NumSamples, const float* RESTRICT Gains);` (scope `Audio`)
- L75 _prototype_ `void Apply6ChannelGain(FAlignedFloatBuffer& InterleavedBuffer, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L76 _prototype_ `void Apply6ChannelGain(float* RESTRICT InterleavedBuffer, int32 NumSamples, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L82 _prototype_ `void MixMonoTo6ChannelsFast(const FAlignedFloatBuffer& MonoBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT Gains);` (scope `Audio`) — Takes a 1 channel buffer and mixes it to an 8 channel interleaved buffer using Gains. Gains is expected to point to a 8 float long buffer. these buffers must have an even number of frames. If StartGains and EndGains are provided, this function will interpolate between the two across the buffer.
- L83 _prototype_ `void MixMonoTo6ChannelsFast(const float* RESTRICT MonoBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT Gains);` (scope `Audio`)
- L84 _prototype_ `void MixMonoTo6ChannelsFast(const FAlignedFloatBuffer& MonoBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L85 _prototype_ `void MixMonoTo6ChannelsFast(const float* RESTRICT MonoBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L92 _prototype_ `void Mix2ChannelsTo6ChannelsFast(const FAlignedFloatBuffer& SourceBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT Gains);` (scope `Audio`) — Takes a 2 channel buffer and mixes it to an 8 channel interleaved buffer using Gains. Gains is expected to point to a 16 float long buffer. Output gains for the left input channel should be the first 8 values in Gains, and Output gains for the right input channel should be rest. NumFrames must be a multiple of 4. If StartGains and EndGains are provided, this function will interpolate between the two across the buffer.
- L93 _prototype_ `void Mix2ChannelsTo6ChannelsFast(const float* RESTRICT SourceBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT Gains);` (scope `Audio`)
- L94 _prototype_ `void Mix2ChannelsTo6ChannelsFast(const FAlignedFloatBuffer& SourceBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L95 _prototype_ `void Mix2ChannelsTo6ChannelsFast(const float* RESTRICT SourceBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L98 _prototype_ `void Apply8ChannelGain(FAlignedFloatBuffer& InterleavedBuffer, const float* RESTRICT Gains);` (scope `Audio`) — Takes an 8 channel interleaved buffer and applies Gains to it. Gains is expected to point to an 8 float long buffer.
- L99 _prototype_ `void Apply8ChannelGain(float* RESTRICT InterleavedBuffer, int32 NumSamples, const float* RESTRICT Gains);` (scope `Audio`)
- L100 _prototype_ `void Apply8ChannelGain(FAlignedFloatBuffer& InterleavedBuffer, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L101 _prototype_ `void Apply8ChannelGain(float* RESTRICT InterleavedBuffer, int32 NumSamples, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L107 _prototype_ `void MixMonoTo8ChannelsFast(const FAlignedFloatBuffer& MonoBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT Gains);` (scope `Audio`) — Takes a 1 channel buffer and mixes it to an 8 channel interleaved buffer using Gains. Gains is expected to point to a 8 float long buffer. these buffers must have an even number of frames. If StartGains and EndGains are provided, this function will interpolate between the two across the buffer.
- L108 _prototype_ `void MixMonoTo8ChannelsFast(const float* RESTRICT MonoBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT Gains);` (scope `Audio`)
- L109 _prototype_ `void MixMonoTo8ChannelsFast(const FAlignedFloatBuffer& MonoBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L110 _prototype_ `void MixMonoTo8ChannelsFast(const float* RESTRICT MonoBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L117 _prototype_ `void Mix2ChannelsTo8ChannelsFast(const FAlignedFloatBuffer& SourceBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT Gains);` (scope `Audio`) — Takes a 2 channel buffer and mixes it to an 8 channel interleaved buffer using Gains. Gains is expected to point to a 16 float long buffer. Output gains for the left input channel should be the first 8 values in Gains, and Output gains for the right input channel should be rest. these buffers must have an even number of frames. If StartGains and EndGains are provided, this function will interpolate between the two across the buffer.
- L118 _prototype_ `void Mix2ChannelsTo8ChannelsFast(const float* RESTRICT SourceBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT Gains);` (scope `Audio`)
- L119 _prototype_ `void Mix2ChannelsTo8ChannelsFast(const FAlignedFloatBuffer& SourceBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L120 _prototype_ `void Mix2ChannelsTo8ChannelsFast(const float* RESTRICT SourceBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L125 _prototype_ `void DownmixBuffer(int32 NumSourceChannels, int32 NumDestinationChannels, const FAlignedFloatBuffer& SourceBuffer, FAlignedFloatBuffer& DestinationBuffer, const float* RESTRICT Gains);` (scope `Audio`) — This is a generalized operation that uses the channel gain matrix provided in Gains to mix an interleaved source buffer to the interleaved downmix buffer. This operation is not explicitly vectorized and will almost always be slower than using one of the functions above.
- L126 _prototype_ `void DownmixBuffer(int32 NumSourceChannels, int32 NumDestinationChannels, const float* RESTRICT SourceBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, const float* RESTRICT Gains);` (scope `Audio`)
- L127 _prototype_ `void DownmixBuffer(int32 NumSourceChannels, int32 NumDestinationChannels, const FAlignedFloatBuffer& SourceBuffer, FAlignedFloatBuffer& DestinationBuffer, float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L128 _prototype_ `void DownmixBuffer(int32 NumSourceChannels, int32 NumDestinationChannels, const float* RESTRICT SourceBuffer, float* RESTRICT DestinationBuffer, int32 NumFrames, float* RESTRICT StartGains, const float* RESTRICT EndGains);` (scope `Audio`)
- L133 _prototype_ `void DownmixAndSumIntoBuffer(int32 NumSourceChannels, int32 NumDestinationChannels, const FAlignedFloatBuffer& SourceBuffer, FAlignedFloatBuffer& BufferToSumTo, const float* RESTRICT Gains);` (scope `Audio`) — This is similar to DownmixBuffer, except that it sums into DestinationBuffer rather than overwriting it.
- L134 _prototype_ `void DownmixAndSumIntoBuffer(int32 NumSourceChannels, int32 NumDestinationChannels, const float* RESTRICT SourceBuffer, float* RESTRICT BufferToSumTo, int32 NumFrames, const float* RESTRICT Gains);` (scope `Audio`)
- L137 _prototype_ `void BufferInterleave2ChannelFast(const FAlignedFloatBuffer& InBuffer1, const FAlignedFloatBuffer& InBuffer2, FAlignedFloatBuffer& OutBuffer);` (scope `Audio`) — Interleaves samples from two input buffers
- L140 _prototype_ `void BufferInterleave2ChannelFast(const float* RESTRICT InBuffer1, const float* RESTRICT InBuffer2, float* RESTRICT OutBuffer, const int32 InNum);` (scope `Audio`) — Interleaves samples from two input buffers
- L143 _prototype_ `void BufferDeinterleave2ChannelFast(const FAlignedFloatBuffer& InBuffer, FAlignedFloatBuffer& OutBuffer1, FAlignedFloatBuffer& OutBuffer2);` (scope `Audio`) — Deinterleaves samples from a 2 channel input buffer
- L146 _prototype_ `void BufferDeinterleave2ChannelFast(const float* RESTRICT InBuffer, float* RESTRICT OutBuffer1, float* RESTRICT OutBuffer2, const int32 InNum);` (scope `Audio`) — Deinterleaves samples from a 2 channel input buffer
- L149 _prototype_ `void BufferSum2ChannelToMonoFast(const FAlignedFloatBuffer& InSamples, FAlignedFloatBuffer& OutSamples);` (scope `Audio`) — Sums 2 channel interleaved input samples. OutSamples[n] = InSamples[2n] + InSamples[2n + 1]
- L152 _prototype_ `void BufferSum2ChannelToMonoFast(const float* RESTRICT InSamples, float* RESTRICT OutSamples, const int32 InNumFrames);` (scope `Audio`) — Sums 2 channel interleaved input samples. OutSamples[n] = InSamples[2n] + InSamples[2n + 1]

### `Source/Runtime/SignalProcessing/Public/DSP/ChannelMap.h` (Public)


#### enum `Audio::EChannelMapOrder`  
`enum class EChannelMapOrder : uint8`  
_L16-46_
- desc: Denotes the order of gain coefficients for a channel map.
- L30 _public enumerator_ `OutputMajorOrder` — The channel map matrix is in output major order, meaning that adjacent values increment the output channel index. G_In_Om is the gain for input channel (n) and output channel (m). If there are (N) input channels and (M) output channel, then the channel map will be in the form: [ G_I0_O0, G_I0_O1, ... G_I0_OM, G_I1_O0, G_I1_O1, ... G_I0_OM, ... G_IN_O0, G_IN_O1, ... G_I0_OM, ]
- L45 _public enumerator_ `InputMajorOrder` — The channel map matrix is in input major order, meaning that adjacent values increment the input channel index. G_In_Om is the gain for input channel (n) and output channel (m). If there are (N) input channels and (M) output channel, then the channel map will be in the form: [ G_I0_O0, G_I1_O0, ... G_IN_O0, G_I0_O1, G_I1_O1, ... G_IN_O1, ... G_I0_OM, G_I1_OM, ... G_IN_OM, ]

#### enum `Audio::EChannelMapMonoUpmixMethod`  
`enum class EChannelMapMonoUpmixMethod : uint8`  
_L50-60_
- desc: Denotes the upmix method for mixing a mono input into the front left and front right speakers.
- L53 _public enumerator_ `Linear` — The mono channel is split 0.5 left/right
- L56 _public enumerator_ `EqualPower` — The mono channel is split 0.707 left/right
- L59 _public enumerator_ `FullVolume` — The mono channel is split 1.0 left/right

#### struct `Audio::FChannelMapParams`  
`struct FChannelMapParams`  
_L63-76_
- desc: Parameters for creating 2D channel maps.
- L66 _public member_ `int32 NumInputChannels;` — Number of channels in the input audio.
- L68 _public member_ `int32 NumOutputChannels;` — Number of channels in the output audio.
- L70 _public member_ `EChannelMapOrder Order;` — Order of gain coefficients in the output channel map.
- L72 _public member_ `EChannelMapMonoUpmixMethod MonoUpmixMethod;` — Method for upmixing mono audio (only used if NumInputChannels == 1)
- L75 _public member_ `bool bIsCenterChannelOnly;` — If true and (NumInputChannels == 1) and the output format has a center channel, then the mono channel will be routed directly to the center channel.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
- L11 _variable_ `static constexpr uint32 ChannelMapMaxNumChannels = 8;` (scope `Audio`) — Maximum number of channels supported by channel maps (Corresponds to 7.1 format)
- L13 _variable_ `static constexpr uint32 ChannelMapVorbisNumChannels = 6;` (scope `Audio`) — Number of channels in a vorbis input (Corresponds to 5.1 with vorbis channel ordering).
- L85 _prototype_ `bool Create2DChannelMap(const FChannelMapParams& InParams, TArray<float>& OutChannelMap);` (scope `Audio`) — Create a 2D channel map. @param InParams - Configuration of channel map. @param OutChannelMap - Array to append with channel map. @return true on success, false on failure.
- L95 _prototype_ `bool CreateVorbis2DChannelMap(int32 InNumOutputChannels, EChannelMapOrder InOrder, TArray<float>& OutVorbisChannelMap);` (scope `Audio`) — Create a 2D channel map for 5.1 vorbis input audio. @param InNumOutputChannels - Number of channels in the output audio. @param InOrder - Order of gian coefficients in the output channel map. @param OutChannelMap - Array to append with channel map. @return true on success, false on failure.

### `Source/Runtime/SignalProcessing/Public/DSP/Chorus.h` (Public)


#### enum `Audio::EChorusDelays::Type`  
`enum Type`  
_L13-19_
- L15 _public enumerator_ `Left`
- L16 _public enumerator_ `Center`
- L17 _public enumerator_ `Right`
- L18 _public enumerator_ `NumDelayTypes`

#### class `Audio::FChorus`  
`class FChorus`  
_L22-58_
- L25 _public prototype_ `FChorus();`
- L26 _public prototype_ `~FChorus();`
- L28 _public prototype_ `void Init(const float InSampleRate, const int32 InNumChannels, const float InDelayLengthSec = 2.0f, const int32 InControlSamplePeriod = 256);`
- L30 _public function_ `inline int32 GetNumChannels() const`
- L35 _public prototype_ `void SetDepth(const EChorusDelays::Type InType, const float InDepth);`
- L36 _public prototype_ `void SetFrequency(const EChorusDelays::Type InType, const float InFrequency);`
- L37 _public prototype_ `void SetFeedback(const EChorusDelays::Type InType, const float InFeedback);`
- L38 _public prototype_ `void SetWetLevel(const float InWetLevel);`
- L39 _public prototype_ `void SetDryLevel(const float InDryLevel);`
- L40 _public prototype_ `void SetSpread(const float InSpread);`
- L41 _public prototype_ `void ProcessAudioFrame(const float* InFrame, float* OutFrame);`
- L42 _public prototype_ `void ProcessAudio(const float* InBuffer, const int32 InNumSamples, float* OutBuffer);`
- L45 _protected member_ `FDelay Delays[EChorusDelays::NumDelayTypes];`
- L46 _protected member_ `FLFO LFOs[EChorusDelays::NumDelayTypes];`
- L47 _protected member_ `FLinearEase Depth[EChorusDelays::NumDelayTypes];`
- L48 _protected member_ `float Feedback[EChorusDelays::NumDelayTypes];`
- L50 _protected member_ `float MinDelayMsec;`
- L51 _protected member_ `float MaxDelayMsec;`
- L52 _protected member_ `float DelayRangeMsec;`
- L53 _protected member_ `float Spread;`
- L54 _protected member_ `float MaxFrequencySpread;`
- L55 _protected member_ `float WetLevel;`
- L56 _protected member_ `float DryLevel;`
- L57 _protected member_ `int32 NumChannels;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L11 _namespace_ `namespace EChorusDelays` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/ConstantQ.h` (Public)


#### enum `Audio::EPseudoConstantQNormalization`  
`enum class EPseudoConstantQNormalization : uint8`  
_L11-16_
- desc: Band normalization schemes
- L13 _public enumerator_ `EqualAmplitude` — No energy scaling. All bands weighted so max is 1.
- L14 _public enumerator_ `EqualEuclideanNorm` — Scale energy by euclidean norm. Good when using magnitude spectrum.
- L15 _public enumerator_ `EqualEnergy` — Scale energy by total energy. Good when using power spectrum.

#### struct `Audio::FPseudoConstantQKernelSettings`  
`struct FPseudoConstantQKernelSettings`  
_L19-35_
- desc: Settings for Pseudo Constant Q Kernel generation.
- L21 _public member_ `int32 NumBands;` — Total number of resulting constant Q bands.
- L22 _public member_ `float NumBandsPerOctave;` — Number of bands to space within an octave.
- L23 _public member_ `float KernelLowestCenterFreq;` — The starting frequency of the first band.
- L24 _public member_ `float BandWidthStretch;` — Stretching factor to control overlap of adjacent bands.
- L25 _public member_ `EPseudoConstantQNormalization Normalization;` — Normalization scheme for bands.
- L28 _public function_ `FPseudoConstantQKernelSettings() : NumBands(96) , NumBandsPerOctave(12) , KernelLowestCenterFreq(40.f) , BandWidthStretch(1.0) , Normalization(EPseudoConstantQNormalization::EqualEnergy)` — Default settings for Pseudo Constant Q Kernel

#### struct `Audio::FPseudoConstantQBandSettings`  
`struct FPseudoConstantQBandSettings`  
_L56-72_
- desc: Settings for a single constant q band.
- L59 _public member_ `float CenterFreq;` — Center frequency of band in Hz.
- L62 _public member_ `float BandWidth;` — Width of band in Hz.
- L65 _public member_ `int32 FFTSize;` — Size of FFT used.
- L68 _public member_ `float SampleRate;` — Samplerate of audio.
- L71 _public member_ `EPseudoConstantQNormalization Normalization;` — Desired normalization.

#### struct `Audio::FPseudoConstantQ`  
`struct FPseudoConstantQ`  
_L74-84_
- L77 _public prototype_ `static float GetConstantQCenterFrequency(const int32 InBandIndex, const float InBaseFrequency, const float InBandsPerOctave);` — Returns the center frequency of a given CQT band.
- L80 _public prototype_ `static float GetConstantQBandWidth(const float InBandCenter, const float InBandsPerOctave, const float InBandWidthStretch);` — Returns the bandwidth for a given CQT band.
- L83 _public prototype_ `static void FillArrayWithConstantQBand(const FPseudoConstantQBandSettings& InSettings, FAlignedFloatBuffer& OutOffsetArray, int32& OutOffsetIndex);` — Fills an array with the spectrum weights to apply to an FFT magnitude or power spectrum output.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
- L53 _prototype_ `TUniquePtr<FContiguousSparse2DKernelTransform> NewPseudoConstantQKernelTransform(const FPseudoConstantQKernelSettings& InSettings, const int32 InFFTSize, const float InSampleRate);` (scope `Audio`) — NewPseudoConstantQKernelTransform This creates a new Pseudo Constant Q Kernel Transform. Pseudo Constant Q differs from standard Constant Q in that it applies a window to an existing DFT output as opposed to using a bank of filters.  The use of an FFT speeds up the calculation but introduces some limitations in bandwidth due to the granularity of the DFT. The resulting kernel will transform an array with (InFFTSize / 2 + 1) elements into an array with InSettings.NumBands elements. InSettings controls the number of bands and band properties. InFFTSize controls the expected input size to the kernel. InSampleRate describes the sampling rate of the analyzed audio. Returns a TUniquePtr to a FContiguousSparse2DKernelTransform.

### `Source/Runtime/SignalProcessing/Public/DSP/ConvertDeinterleave.h` (Public)


#### struct `Audio::FConvertDeinterleaveParams`  
`struct FConvertDeinterleaveParams`  
_L13-23_
- desc: Parameters for creating a IConvertDeinterleave object.
- L16 _public member_ `int32 NumInputChannels = 0;` — Number of channels in the input audio.
- L19 _public member_ `int32 NumOutputChannels = 0;` — Number of channels in the output audio.
- L22 _public member_ `EChannelMapMonoUpmixMethod MonoUpmixMethod = EChannelMapMonoUpmixMethod::EqualPower;` — Method for upmixing mono audio (only used if NumInputChannels == 1)

#### struct `Audio::IConvertDeinterleave`  
`struct IConvertDeinterleave`  
_L33-73_
- desc: IConvertDeinterleave is an interface for transforming multichannel interleaved audio samples into multichannel deinterleaved samples. The channel count of the input and output audio may differ. The deinterleaving and channel format conversion operations are combined into this single object as both operations are often required for any given source audio.
- L35 _public prototype_ `virtual ~IConvertDeinterleave() = default;`
- L46 _public function_ `void ProcessAudio(TArrayView<const float> InSamples, FMultichannelBuffer& OutSamples) const` — Deinterleave and convert the channel format of the input audio. @param InSamples - ArrayView of interleaved input samples. The number of samples must be evenly divisible by the number of input channels. @param OutSamples - A multichannel buffer of samples generated by deinterleaving the input samples and possibly upmixing or downmixing them to the target channel count.
- L61 _public prototype_ `virtual void ProcessAudio(TArrayView<const float> InSamples, const TArray<TArrayView<float>>& OutMultiChannelAudio) const = 0;` — Deinterleave and convert the channel format of the input audio. @param InSamples - ArrayView of interleaved input samples. The number of samples must be evenly divisible by the number of input channels. @param OutMultiChannelAudio - A multichannel buffer of samples generated by deinterleaving the input samples and possibly upmixing or downmixing them to the target channel count.
- L72 _public prototype_ `static TUniquePtr<IConvertDeinterleave> Create(const FConvertDeinterleaveParams& InParams);` — Create an IConvertDeinterleave object for a given number of input and output channels. @param InNumInputChannels - Number of input channels in incoming audio. @param InNumOutputChannels - Number of output channels in outgoing audio. @return A valid TUniquePtr<> on success, an invalid TUniquePtr<> on failure.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/ConvolutionAlgorithm.h` (Public)


#### struct `Audio::FConvolutionSettings`  
`struct FConvolutionSettings`  
_L14-48_
- desc: FConvolutionSettings Settings for creating an IConvolutionAlgorithm.
- L17 _public member_ `bool bEnableHardwareAcceleration = true;` — If true, hardware accelerated algorithms are valid.
- L20 _public member_ `int32 BlockNumSamples = 256;` — Defines size of audio processing block.
- L23 _public member_ `int32 NumInputChannels = 0;` — Number of input audio channels to support.
- L26 _public member_ `int32 NumOutputChannels = 0;` — Number of output audio channels to support.
- L29 _public member_ `int32 NumImpulseResponses = 0;` — Number of impulse responses to support.
- L32 _public member_ `int32 MaxNumImpulseResponseSamples = 0;` — Maximum number of samples in an impulse responses.
- L34 _public function_ `bool operator==(const FConvolutionSettings& Other)`
- L44 _public function_ `bool operator!=(const FConvolutionSettings& Other)`

#### class `Audio::IConvolutionAlgorithm`  
`class IConvolutionAlgorithm`  
_L55-108_
- desc: IConvolutionAlgorithm Interface for Convolution algorithm.
- L60 _public prototype_ `virtual ~IConvolutionAlgorithm() = default;` — virtual destructor for inheritance.
- L63 _public prototype_ `virtual int32 GetNumSamplesInBlock() const = 0;` — Returns the number of samples in an audio block.
- L66 _public prototype_ `virtual int32 GetNumAudioInputs() const = 0;` — Returns number of audio inputs.
- L69 _public prototype_ `virtual int32 GetNumAudioOutputs() const = 0;` — Returns number of audio outputs.
- L79 _public prototype_ `virtual void ProcessAudioBlock(const float* const InSamples[], float* const OutSamples[]) = 0;` — Process one block of audio. InSamples is processed by the impulse responses. The output is placed in OutSamples. @params InSamples - A 2D array of input deinterleaved audio samples. InSamples[GetNumAudioInputs()][GetNumSamplesInBlock()] @params OutSamples - A 2D array of output deinterleaved audio samples. OutSamples[GetNumAudioOutputs()][GetNumSamplesInBlock()]
- L82 _public prototype_ `virtual void ResetAudioHistory() = 0;` — Reset internal history buffers.
- L85 _public prototype_ `virtual int32 GetMaxNumImpulseResponseSamples() const = 0;` — Maximum supported length of impulse response.
- L89 _public prototype_ `virtual int32 GetNumImpulseResponses() const = 0;` — Return the number of impulse responses.
- L92 _public prototype_ `virtual int32 GetNumImpulseResponseSamples(int32 InImpulseResponseIndex) const = 0;` — Return the number of samples in an impulse response.
- L95 _public prototype_ `virtual void SetImpulseResponse(int32 InImpulseResponseIndex, const float* InSamples, int32 NumSamples) = 0;` — Set impulse response values.
- L101 _public prototype_ `virtual void SetMatrixGain(int32 InAudioInputIndex, int32 InImpulseResponseIndex, int32 InAudioOutputIndex, float InGain) = 0;` — Sets the gain between an audio input, impulse response and audio output. ([audio input] * [impulse response]) x gain = [audio output]
- L107 _public prototype_ `virtual float GetMatrixGain(int32 InAudioInputIndex, int32 InImpulseResponseIndex, int32 InAudioOutputIndex) const = 0;` — Gets the gain between an audio input, impulse response and audio output. ([audio input] * [impulse response]) x gain = [audio output]

#### class `Audio::IConvolutionAlgorithmFactory`  
`class IConvolutionAlgorithmFactory : public IModularFeature`  
_L114-133_
- inherits: `IModularFeature`
- desc: IConvolutionAlgorithmFactory Factory interface for creating convolution algorithms.
- L117 _public prototype_ `virtual ~IConvolutionAlgorithmFactory();`
- L120 _public prototype_ `static const FName GetModularFeatureName();` — Name of modular feature for Convolution factory.
- L123 _public prototype_ `virtual const FName GetFactoryName() const = 0;` — Name of this particular factory.
- L126 _public prototype_ `virtual bool IsHardwareAccelerated() const = 0;` — If true, this implementation uses hardware acceleration.
- L129 _public prototype_ `virtual bool AreConvolutionSettingsSupported(const FConvolutionSettings& InSettings) const = 0;` — Returns true if the input settings are supported by this factory.
- L132 _public prototype_ `virtual TUniquePtr<IConvolutionAlgorithm> NewConvolutionAlgorithm(const FConvolutionSettings& InSettings) = 0;` — Creates a new Convolution algorithm.

#### class `Audio::FConvolutionFactory`  
`class FConvolutionFactory`  
_L139-154_
- desc: FConvolutionFactory FConvolutionFactory creates convolution algorithms. It will choose hardware accelerated versions when they are available.
- L143 _public member_ `static const FName AnyAlgorithmFactory;` — This denotes that no specific IConvolutionAlgorithmFactory is desired.
- L153 _public prototype_ `static TUniquePtr<IConvolutionAlgorithm> NewConvolutionAlgorithm(const FConvolutionSettings& InSettings, const FName& InAlgorithmFactoryName = AnyAlgorithmFactory);` — NewConvolutionAlgorithm Creates and returns a new ConvolutionAlgorithm. @param InSettings - The settings used to create the Convolution algorithm. @param InAlgorithmFactoryName - If not equal to FConvolutionFactory::AnyAlgorithmFactory, will only uses Convolution algorithm facotry if IConvolutionAlgorithmFactory::GetFactoryName() equals InAlgorithmFactoryName. @return A TUniquePtr<IConvolutionAlgorithm> to the created Convolution. This pointer can be invalid if an error occured or the fft algorithm could not be created.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/DeinterleaveView.h` (Public)


#### class `Audio::TDeinterleaveView`  
`template <typename T> class TDeinterleaveView`  
_L14-170_
- desc: TDeinterleaveView TDeinterleaveView provides iterators to access deinterleaved arrays from an interleaved array.
- L140 _public function_ `TDeinterleaveView(TArrayView<const T> InInterleavedArray, int32 InNumChannels) : InterleavedArray(InInterleavedArray) , NumChannels(InNumChannels) , NumElementsPerChannel(0)` — TDeinterleave constructor. InInterleavedArray is the interleaved array to be deinterleaved. InNumChannels is the number of channels in the deinterleaved array.
- L152 _public function_ `template <typename InAllocator = FDefaultAllocator> TChannelIterator<InAllocator> begin(TArray<T, InAllocator>& InArrayToFill) const` — Return an STL iterator to the first channel. It fills the given array with channel elements
- L159 _public function_ `template <typename InAllocator = FDefaultAllocator> TChannelIterator<InAllocator> end(TArray<T, InAllocator>& InArrayToFill) const` — Return an STL iterator to the end.
- L166 _private member_ `TArrayView<const T> InterleavedArray;` — view to interleaved data
- L168 _private member_ `int32 NumChannels;`
- L169 _private member_ `int32 NumElementsPerChannel;`

#### class `Audio::TDeinterleaveView::TChannel`  
`template<typename InAllocator = FDefaultAllocator> class TChannel`  
_L25-35_
- desc: TChannel TChannel provides a contiguous copy of an single channel from an interleaved array.
- L28 _public member_ `TArray<T, InAllocator>& Values;`
- L29 _public member_ `const int32 ChannelIndex;`
- L31 _public function_ `TChannel(TArray<T, InAllocator>& InValues, const int32 InChannelIndex) : Values(InValues) , ChannelIndex(InChannelIndex)`

#### class `Audio::TDeinterleaveView::TChannelIterator`  
`template<typename InAllocator = FDefaultAllocator> class TChannelIterator`  
_L43-133_
- desc: TChannelIterator TChannelIterator iterates over channels in an interleaved array and providing contiguous arrays of a single channel.
- L45 _private member_ `TDeinterleaveView<T> DeinterleaveView;`
- L46 _private member_ `TArray<T, InAllocator>& ArrayToFill;`
- L47 _private member_ `int32 ChannelIndex;`
- L52 _public member_ `static const int32 ChannelIndexEnd = INDEX_NONE;` — Denotes the end of a channel iterator
- L62 _public function_ `TChannelIterator(TDeinterleaveView<T> InDeinterleaveView, TArray<T, InAllocator>& InArrayToFill, int32 InChannelIndex) : DeinterleaveView(InDeinterleaveView) , ArrayToFill(InArrayToFill) , ChannelIndex(InChannelIndex)` — TChannelIterator TChannelIterator allows iteration over interleaved arrays and provides contiguous arrays of single channels. InDeinterleaveView is the parent view provides the source interleaved array for this iterator. InArrayToFill is the array which will be populated with contiguous elements for a channel. InChannelIndex is the channel index which this iterator will point to.
- L77 _public function_ `TChannelIterator& operator++()` — Increment the iterator forward by one channel
- L91 _public function_ `bool operator!=(const TChannelIterator& Other) const` — Check equality between iterators
- L97 _public function_ `int32 GetChannelIndex() const` — Get the current channel index
- L103 _public function_ `TChannel<InAllocator> operator*()` — Dereference the iterator, returns a TChannel object

#### class `Audio::TAutoDeinterleaveView`  
`template <typename T, typename InAllocator = FDefaultAllocator> class TAutoDeinterleaveView : public TDeinterleaveView<T>`  
_L185-214_
- inherits: `TDeinterleaveView<T>`
- desc: TAutoDeinterleaveView TAutoDeinterlaveView provides a STL like iterators which exposes contiguous channel arrays from interleaved arrays.  As opposed to TDeinterleaveView, this class can be used in range based for loops, but only one iterator is valid at a time since they all share the same InArrayToFill. Example: TArray<float> ArrayToFill; for (auto Channel : TAudoDeineterleaveView(InterleavedArray, ArrayToFill, 2)) { DoSomethingWithAudio(Channel.Values, Channel.ChannelIndex); }
- L187 _private member_ `TArray<T, InAllocator>& ArrayToFill;`
- L189 _private typedef_ `typedef typename TDeinterleaveView<T>::template TChannelIterator<InAllocator> TAutoChannelIterator;`
- L198 _public function_ `TAutoDeinterleaveView(TArrayView<const T> InInterleavedArray, TArray<T, InAllocator>& InArrayToFill, int32 InNumChannels) : TDeinterleaveView<T>(InInterleavedArray, InNumChannels) , ArrayToFill(InArrayToFill)` — TAutoDeinterleaveView Constructor. InInterleavedArray is the interleaved array to be deinterleaved. InArrayToFill is the array which will be populated with contiguous elements for a channel. InNumChannels is the number of channels in the deinterleaved array.
- L204 _public function_ `TAutoChannelIterator begin()` — Return an STL iterator to the first channel.
- L210 _public function_ `TAutoChannelIterator end()` — Return an STL iterator to the end.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/Delay.h` (Public)


#### class `Audio::FDelay`  
`class FDelay`  
_L12-109_
- desc: Circular Buffer Delay Line
- L16 _public prototype_ `FDelay();` — Constructor
- L19 _public prototype_ `virtual ~FDelay();` — Virtual Destructor
- L23 _public prototype_ `void Init(const float InSampleRate, const float InBufferLengthSec = 2.0f);` — Initialization of the delay with given sample rate and max buffer size in samples. (calls Reset())
- L27 _public prototype_ `void Reset();` — Resets the delay line state, flushes buffer and resets read/write pointers. (called by Init())
- L28 _public prototype_ `void ResetWithFade();`
- L32 _public prototype_ `void SetDelayMsec(const float InDelayMsec);` — Sets the delay line length. Will clamp to within range of the max initialized delay line length (won't resize).
- L35 _public prototype_ `void SetDelaySamples(const float InDelaySamples);` — Same as SetDelayMsec, except in samples.
- L38 _public prototype_ `void SetEasedDelayMsec(const float InDelayMsec, const bool bIsInit = false);` — Sets the delay line length but using the internal easing function for smooth delay line interpolation.
- L41 _public prototype_ `void SetEaseFactor(const float InEaseFactor);` — Sets the easing factor for the delay line's internal exponential interpolator.
- L44 _public prototype_ `void SetOutputAttenuationDB(const float InDelayAttenDB);` — Sets the output attenuation in DB
- L47 _public function_ `float GetDelayLengthSamples() const` — Returns the current delay line length (in samples).
- L50 _public prototype_ `float Read() const;` — Reads the delay line at current read index without writing or incrementing read/write pointers.
- L53 _public prototype_ `float ReadDelayAt(const float InReadMsec) const;` — Reads the delay line at an arbitrary time in Msec without writing or incrementing read/write pointers.
- L56 _public prototype_ `void WriteDelayAndInc(const float InDelayInput);` — Write the input and increment read/write pointers
- L59 _public prototype_ `virtual float ProcessAudioSample(const float InAudio);` — Process audio in the delay line, return the delayed value
- L61 _public prototype_ `virtual void ProcessAudioBuffer(const float* InAudio, int32 InNumSamples, float* OutAudio);`
- L65 _protected prototype_ `void Update(bool bForce = false);` — Updates delay line based on any recent changes to settings
- L68 _protected prototype_ `void ResizeIfNeeded(const int32 InNewNumSamples);` — Updates delay line based on any recent changes to settings
- L71 _protected member_ `FAlignedFloatBuffer AudioBuffer;` — Pointer to the circular buffer of audio.
- L74 _protected member_ `int32 AudioBufferSize;` — Max length of buffer (in samples)
- L77 _protected member_ `int32 ReadIndex;` — Read index for circular buffer.
- L80 _protected member_ `int32 WriteIndex;` — Write index for circular buffer.
- L83 _protected member_ `float SampleRate;` — Sample rate
- L86 _protected member_ `float DelayInSamples;` — Delay in samples; float supports fractional delay
- L89 _protected member_ `int32 MaxBufferLengthSamples;` — Upper limit of where we will resize the array
- L92 _protected member_ `FExponentialEase EaseDelayMsec;` — Eased delay in msec
- L95 _protected member_ `float OutputAttenuation;` — Output attenuation value.
- L99 _protected member_ `float OutputAttenuationDB;` — Attenuation in decibel
- L104 _private member_ `float InputAttenuation = 1.f;` — Used to do a quick fade-in of input after a call to "ResetWithFade()"
- L105 _private member_ `float InputFadeGainStep = 0.f;`
- L107 _private prototype_ `void WriteToBuffer(const float InInput);`
- L108 _private prototype_ `void AdvanceIndices();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/DelayStereo.h` (Public)


#### enum `Audio::EStereoDelayMode::Type`  
`enum Type`  
_L14-21_
- L16 _public enumerator_ `Normal`
- L17 _public enumerator_ `Cross`
- L18 _public enumerator_ `PingPong`
- L20 _public enumerator_ `NumStereoDelayModes`

#### class `Audio::FDelayStereo`  
`class FDelayStereo`  
_L24-109_
- L27 _public prototype_ `FDelayStereo();`
- L28 _public prototype_ `~FDelayStereo();`
- L31 _public prototype_ `void Init(const float InSampleRate, const int32 InNumChannels, const float InDelayLengthSec = 2.0f);` — Initializes the stereo delay with given sample rate and default max delay length
- L34 _public prototype_ `void Reset();` — Resets the stereo delay state
- L37 _public prototype_ `void ProcessAudioFrame(const float* InFrame, float* OutFrame);` — Process a single frame of audio
- L40 _public prototype_ `void ProcessAudio(const float* InBuffer, const int32 InNumSamples, float* OutBuffer);` — Process a buffer of audio
- L43 _public prototype_ `void SetMode(const EStereoDelayMode::Type InMode);` — Sets which delay stereo mode to use
- L46 _public function_ `EStereoDelayMode::Type GetMode() const` — Gets the current stereo dealy mode
- L49 _public prototype_ `void SetDelayTimeMsec(const float InDelayTimeMsec);` — Sets the delay time in msec.
- L52 _public prototype_ `void SetFeedback(const float InFeedback);` — Sets the feedback amount
- L55 _public prototype_ `void SetDelayRatio(const float InDelayRatio);` — Sets the delay ratio (scales difference between left and right stereo delays)
- L58 _public prototype_ `void SetWetLevel(const float InWetLevel);` — Sets the amount of the effect to mix in the output
- L61 _public prototype_ `void SetDryLevel(const float InDryLevel);` — Sets the amount of the effect to mix in the output
- L64 _public prototype_ `void SetFilterEnabled(bool bInEnabled);` — Sets whether or not the filter is enabled
- L67 _public prototype_ `void SetFilterSettings(EBiquadFilter::Type InFilterType, const float InCutoffFrequency, const float InQ);` — Sets the filter settings
- L71 _protected prototype_ `void UpdateDelays();` — Updates the delays based on recent parameters
- L74 _protected member_ `TArray<FDelay> Delays;` — Delay lines per channel
- L77 _protected member_ `TArray<FBiquadFilter> BiquadFilters;` — Biquad filter per channel to feed the delay output through
- L80 _protected member_ `EStereoDelayMode::Type DelayMode = EStereoDelayMode::Normal;` — What mode the stereo delay is in
- L83 _protected member_ `float DelayTimeMsec = 0.0f;` — Amount of delay time in msec
- L86 _protected member_ `float Feedback = 0.0f;` — How much delay feedback to use
- L89 _protected member_ `float DelayRatio = 0.0f;` — How much to shift the delays from each other
- L92 _protected member_ `float WetLevel = 0.0f;` — The amount of wet level on the output
- L95 _protected member_ `float DryLevel = 1.0f;` — The amount of dry level on the output
- L98 _protected member_ `float FilterFreq = 20000.0f;` — Filter data
- L99 _protected member_ `float FilterQ = 2.0f;`
- L100 _protected member_ `EBiquadFilter::Type FilterType = EBiquadFilter::Lowpass;`
- L103 _protected member_ `int32 NumChannels = 0;` — The number of channels to use (will sum mono)
- L106 _protected member_ `bool bIsInit = true;` — If the delay has started processing yet
- L108 _protected member_ `bool bIsFilterEnabled = false;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L12 _namespace_ `namespace EStereoDelayMode` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/DirectedGraphAlgo.h` (Public)


#### struct `Audio::FStronglyConnectedComponent`  
`struct UE_DEPRECATED(5.5, "This has moved to the UE::MathCore::Graph namespace") FStronglyConnectedComponent`  
_L22-31_
- desc: A strongly connected component contains a subgraph of strongly connected vertices and their corresponding edges.
- L25 _public member_ `TArray<int32> Vertices;` — Vertices in the strongly connected component.
- L29 _public member_ `TArray<FDirectedEdge> Edges;` — Edges in the strongly connected component.

#### struct `Audio::FDirectedGraphAlgo`  
`struct FDirectedGraphAlgo`  
_L43-138_
- L52 _public prototype_ `static void BuildDirectedTree(TArrayView<const FDirectedEdge> InEdges, FDirectedTree& OutTree);` — `UE_DEPRECATED(5.5, "This has moved to the UE::MathCore::Graph namespace")` — Build a directed tree from an array of edges. @parma InEdges - An array of directed eges. @param OutTree - A tree structure built from the edges.
- L64 _public prototype_ `static void BuildTransposeDirectedTree(TArrayView<const FDirectedEdge> InEdges, FDirectedTree& OutTree);` — `UE_DEPRECATED(5.5, "This has moved to the UE::MathCore::Graph namespace")` — Build a transpose directed tree from an array of edges. The transpose of a directed graph is created by reversing each edge. @parma InEdges - An array of directed eges. @param OutTree - A tree structure built from the reversed edges.
- L79 _public prototype_ `static void DepthFirstTraversal(int32 InInitialVertex, const FDirectedTree& InTree, TFunctionRef<bool (int32)> InVisitFunc);` — `UE_DEPRECATED(5.5, "This has moved to the UE::MathCore::Graph namespace")` — Traverse a tree in a depth first ordering. @param InInitialVertex - The starting vertex for traversal. @param InTree          - The tree structure to traverse. @param InVisitFunc     - A function that is called for each vertex that is visited. If this function returns true, traversal is continued in a depth first manner. If this function returns false, the children of the current vertex are not visited.
- L95 _public prototype_ `static void BreadthFirstTraversal(int32 InInitialVertex, const FDirectedTree& InTree, TFunctionRef<bool (int32)> InVisitFunc);` — `UE_DEPRECATED(5.5, "This has moved to the UE::MathCore::Graph namespace")` — Traverse a tree in a breadth first ordering. @param InInitialVertex - The starting vertex for traversal. @param InTree          - The tree structure to traverse. @param InVisitFunc     - A function that is called for each vertex that is visited. If this function returns true, the children of this vertex will be visited in the future.  If this function returns false, then the children of the current vertex will not be visited.
- L108 _public prototype_ `static bool DepthFirstTopologicalSort(TArrayView<const int32> InUniqueVertices, TArrayView<const FDirectedEdge> InUniqueEdges, TArray<int32>& OutVertexOrder);` — `UE_DEPRECATED(5.5, "This has moved to the UE::MathCore::Graph namespace")` — Sort vertices topologically using a depth first sorting algorithm. @param InUniqueVertices - An array of vertices to sort. @param InUniqueEdges - An array of edges describing dependencies. @param OutVertexOrder - An array where ordered vertices are placed. @return True if sorting was successful. False otherwise.
- L121 _public prototype_ `static bool KahnTopologicalSort(TArrayView<const int32> InUniqueVertices, TArrayView<const FDirectedEdge> InUniqueEdges, TArray<int32>& OutVertexOrder);` — `UE_DEPRECATED(5.5, "This has moved to the UE::MathCore::Graph namespace")` — Sort vertices topologically using a Kahn's sorting algorithm. @param InUniqueVertices - An array of vertices to sort. @param InUniqueEdges - An array of edges describing dependencies. @param OutVertexOrder - An array where ordered vertices are placed. @return True if sorting was successful. False otherwise.
- L136 _public prototype_ `static bool TarjanStronglyConnectedComponents(const TSet<FDirectedEdge>& InEdges, TArray<FStronglyConnectedComponent>& OutComponents, bool bExcludeSingleVertex = true);` — `UE_DEPRECATED(5.5, "This has moved to the UE::MathCore::Graph namespace")` — Find strongly connected components given a set of edges using Tarjan algorithm. @param InEdges - Edges in the directed graph. @param OutComponents - Strongly connected components found in the graph are be added to this array. @param bExcludeSingleVertex - If true, single vertices are not be returned as strongly connected components. If false, single vertices may be returned as strongly connected components. @return True if one or more strongly connected components are added to OutComponents. False otherwise.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L17 _typedef_ `typedef TTuple<int32, int32> FDirectedEdge;` (scope `Audio`) — `UE_DEPRECATED(5.5, "This has moved to the UE::MathCore::Graph namespace")` — A pair of int32s represent a directed edge. The first value represents the source vertex, and the second value represents the destination vertex.
- L35 _typedef_ `typedef UE::MathCore::Graph::FDirectedTreeElement FDirectedTreeElement;` (scope `Audio`) — `UE_DEPRECATED(5.5, "This has moved to the UE::MathCore::Graph namespace")` — An element in a directed tree with references to children of a vertex.
- L40 _typedef_ `typedef TMap<int32, FDirectedTreeElement> FDirectedTree;` (scope `Audio`) — `UE_DEPRECATED(5.5, "This has moved to the UE::MathCore::Graph namespace")` — A directed tree graph represenation.

### `Source/Runtime/SignalProcessing/Public/DSP/Dsp.h` (Public)


#### class `Audio::FSinOsc2DRotation`  
`class FSinOsc2DRotation`  
_L125-239_
- desc: Generates a sine wave in the given buffer with the given frequency. Uses the method of generating a 2D point on the unit circle and multiplying with a 2d rotation matrix to advance the phase. Very accurate and very fast. Use this unless you're changing frequency every few samples on very tiny blocks (single digit sample count) Distortion vs directly calling FMath::Sin() is on the order of -100db, and is roughly 10x faster (for constant frequency). Frequency changes are not interpolated across the buffer, so dramatic changes could introduce aliasing due to a discontinuous derivative in the output. If you're changing frequencies by a lot, constantly, you should probably use VectorSinCos in a loop. Usage: constexpr const int32 ChunkSampleCount = 480; alignas (sizeof(VectorRegister4Float)) float ChunkBuffer[ChunkSampleCount]; FSinOscBufferGenerator Generator; Generator.GenerateBuffer(48000, 400, ChunkBuffer, ChunkSampleCount); ChunkBuffer now has 10ms of sine tone at 400hz. The next call will continue the sine tone where it left off.
- L128 _public function_ `FSinOsc2DRotation(float InStartingPhaseRadians = 0.f)`
- L145 _public function_ `void GenerateBuffer(float SampleRate, float ClampedFrequency, float* Buffer, int32 BufferSampleCount)` — Generates the sine tone, continuing from the last phase. @param SampleRate the sample rate the buffer will be played at @param ClampedFrequency the frequency of the tone to emit, clamped to nyquist (SampleRate/2) @param Buffer the output buffer @param BufferSampleCount the number of samples in the buffer. Generally, this should be %4 granularity.
- L236 _private member_ `VectorRegister4Float QuadDxVec, QuadDyVec;`
- L236 _private member_ `VectorRegister4Float QuadDxVec, QuadDyVec;`
- L237 _private member_ `float LastPhasePerSample;`
- L238 _private member_ `float LastPhase;`

#### class `Audio::FExponentialEase`  
`class FExponentialEase`  
_L552-663_
- desc: Simple exponential easing class. Useful for cheaply and smoothly interpolating parameters.
- L555 _public function_ `FExponentialEase(float InInitValue = 0.0f, float InEaseFactor = 0.001f, float InThreshold = UE_KINDA_SMALL_NUMBER) : CurrentValue(InInitValue) , Threshold(InThreshold) , TargetValue(InInitValue) , EaseFactor(InEaseFactor) , OneMinusEase(1.0f - InEaseFactor) , EaseTimesTarget(EaseFactor * InInitValue)`
- L565 _public function_ `void Init(float InInitValue, float InEaseFactor = 0.001f)`
- L575 _public function_ `bool IsDone() const`
- L580 _public function_ `float GetNextValue()`
- L600 _public function_ `float GetNextValue(uint32 NumTicksToJumpAhead)` — same as GetValue(), but overloaded to jump forward by NumTicksToJumpAhead timesteps (before getting the value)
- L611 _public function_ `float PeekCurrentValue() const`
- L616 _public function_ `void SetEaseFactor(const float InEaseFactor)`
- L622 _public function_ `void operator=(const float& InValue)`
- L627 _public function_ `void SetValue(const float InValue, const bool bIsInit = false)`
- L639 _public function_ `static float GetFactorForTau(float InTau, float InSampleRate)` — This is a method for getting the factor to use for a given tau and sample rate. Tau here is defined as the time it takes the interpolator to be within 1/e of it's destination.
- L647 _private member_ `float CurrentValue;` — Current value of the exponential ease
- L650 _private member_ `float Threshold;` — Threshold to use to evaluate if the ease is done
- L653 _private member_ `float TargetValue;` — Target value
- L656 _private member_ `float EaseFactor;` — Percentage to move toward target value from current value each tick
- L659 _private member_ `float OneMinusEase;` — 1.0f - EaseFactor
- L662 _private member_ `float EaseTimesTarget;` — EaseFactor * TargetValue

#### class `Audio::FLinearEase`  
`class FLinearEase`  
_L666-784_
- desc: Simple easing function used to help interpolate params
- L669 _public function_ `FLinearEase() : StartValue(0.0f) , CurrentValue(0.0f) , DeltaValue(0.0f) , SampleRate(44100.0f) , DurationTicks(0) , DefaultDurationTicks(0) , CurrentTick(0) , bIsInit(true)`
- L681 _public prototype_ `~FLinearEase() = default;`
- L683 _public function_ `bool IsDone() const`
- L688 _public function_ `void Init(float InSampleRate)`
- L694 _public function_ `void SetValueRange(const float Start, const float End, const float InTimeSec)`
- L701 _public function_ `float GetNextValue()`
- L716 _public function_ `float GetNextValue(int32 NumTicksToJumpAhead)` — same as GetValue(), but overloaded to increment Current Tick by NumTicksToJumpAhead (before getting the value)
- L729 _public function_ `float PeekCurrentValue() const`
- L736 _public function_ `void SetValueInterrupt(const float InValue)` — Updates the target value without changing the duration or tick data. Sets the state as if the new value was the target value all along
- L751 _public function_ `void SetValue(const float InValue, float InTimeSec = 0.0f)`
- L776 _private member_ `float StartValue;`
- L777 _private member_ `float CurrentValue;`
- L778 _private member_ `float DeltaValue;`
- L779 _private member_ `float SampleRate;`
- L780 _private member_ `int32 DurationTicks;`
- L781 _private member_ `int32 DefaultDurationTicks;`
- L782 _private member_ `int32 CurrentTick;`
- L783 _private member_ `bool bIsInit;`

#### class `Audio::TParams`  
`template<typename T> class TParams`  
_L788-825_
- desc: Simple parameter object which uses critical section to write to and read from data
- L791 _public function_ `TParams() : bChanged(false)`
- L796 _public function_ `void SetParams(const T& InParams)` — Sets the params
- L804 _public function_ `bool GetParams(T* OutParamsCopy)` — Returns a copy of the params safely if they've changed since last time this was called
- L816 _public function_ `void CopyParams(T& OutParamsCopy) const`
- L822 _public member_ `bool bChanged;`
- L823 _public member_ `T CurrentParams;`
- L824 _public member_ `mutable FCriticalSection CritSect;`

#### struct `Audio::DisjointedArrayView`  
`template <typename SampleType> struct DisjointedArrayView`  
_L828-871_
- L830 _public function_ `DisjointedArrayView(TArrayView<SampleType> && InFirstBuffer, TArrayView<SampleType> && InSecondBuffer) : FirstBuffer(MoveTemp(InFirstBuffer)) , SecondBuffer(MoveTemp(InSecondBuffer))`
- L836 _public function_ `template <typename OtherSampleType> DisjointedArrayView<OtherSampleType> SplitOtherToMatch(OtherSampleType* Other, int32 InNum) const`
- L847 _public function_ `int32 CopyIntoBuffer(SampleType* InDestination, int32 InNumSamples)`
- L863 _public function_ `int32 FirstNum() const`
- L864 _public function_ `int32 SecondNum() const`
- L865 _public function_ `int32 Num() const`
- L868 _public member_ `TArrayView<SampleType> FirstBuffer;` — data:
- L869 _public member_ `TArrayView<SampleType> SecondBuffer;`

#### class `Audio::TCircularAudioBuffer`  
`template <typename SampleType, size_t Alignment = 16> class TCircularAudioBuffer`  
_L879-1206_
- desc: Basic implementation of a circular buffer built for pushing and popping arbitrary amounts of data at once. Designed to be thread safe for SPSC; However, if Push() and Pop() are both trying to access an overlapping area of the buffer, One of the calls will be truncated. Thus, it is advised that you use a high enough capacity that the producer and consumer are never in contention.
- L883 _private member_ `TArray<SampleType, TAlignedHeapAllocator<Alignment>> InternalBuffer;`
- L884 _private member_ `uint32 Capacity;`
- L885 _private member_ `FThreadSafeCounter ReadCounter;`
- L886 _private member_ `FThreadSafeCounter WriteCounter;`
- L889 _public function_ `TCircularAudioBuffer()`
- L894 _public function_ `TCircularAudioBuffer(const TCircularAudioBuffer<SampleType, Alignment>& InOther)`
- L899 _public function_ `TCircularAudioBuffer& operator=(const TCircularAudioBuffer<SampleType, Alignment>& InOther)`
- L910 _public function_ `TCircularAudioBuffer(uint32 InCapacity)`
- L915 _public function_ `void Reset(uint32 InCapacity = 0)`
- L920 _public function_ `void Empty()`
- L927 _public function_ `void SetCapacity(uint32 InCapacity)`
- L942 _public function_ `void Reserve(uint32 InMinimumCapacity, bool bRetainExistingSamples)` — Reserve capacity. @param InMinimumCapacity - Minimum capacity of circular buffer. @param bRetainExistingSamples - If true, existing samples in the buffer will be retained. If false, they are discarded.
- L963 _public function_ `int32 Push(TArrayView<const SampleType> InBuffer)` — Push an array of values into circular buffer.
- L971 _public function_ `int32 Push(const SampleType* InBuffer, uint32 NumSamples)` — Pushes some amount of samples into this circular buffer. Returns the amount of samples written. This can only be used for trivially copyable types.
- L990 _public function_ `int32 PushZeros(uint32 NumSamplesOfZeros)` — Pushes some amount of zeros into the circular buffer. Useful when acting as a blocked, mono/interleaved delay line
- L1009 _public function_ `bool Push(const SampleType& InElement)` — Push a single sample onto this buffer. Returns false if the buffer is full.
- L1028 _public function_ `bool Push(SampleType && InElement)`
- L1048 _public function_ `int32 Peek(SampleType* OutBuffer, uint32 NumSamples) const` — Same as Pop(), but does not increment the read counter.
- L1068 _public function_ `DisjointedArrayView <const SampleType> PeekInPlace(uint32 NumSamples) const` — same Peek(), but provides a (possibly) disjointed view of the memory in-place Push calls while the returned view is being accessed is undefined behavior
- L1086 _public function_ `bool Peek(SampleType& OutElement) const` — Peeks a single element. returns false if the element is empty.
- L1105 _public function_ `int32 Pop(SampleType* OutBuffer, uint32 NumSamples)` — Pops some amount of samples into this circular buffer. Returns the amount of samples read.
- L1117 _public function_ `DisjointedArrayView<const SampleType> PopInPlace(uint32 NumSamples)` — Same as Pop(), but provides a (possibly) disjinted view of memory in-place Push calls while the returned view is being accessed is undefined behavior
- L1130 _public function_ `int32 Pop(uint32 NumSamples)` — Pops some amount of samples into this circular buffer. Returns the amount of samples read.
- L1143 _public function_ `SampleType Pop()` — Pops a single element. Will assert if the buffer is empty. Please check Num() > 0 before calling.
- L1159 _public function_ `void SetNum(uint32 NumSamples, bool bRetainOldestSamples = false)` — When called, seeks the read or write cursor to only retain either the NumSamples latest data (if bRetainOldestSamples is false) or the NumSamples oldest data (if bRetainOldestSamples is true) in the buffer. Cannot be used to increase the capacity of this buffer.
- L1180 _public function_ `uint32 Num() const` — Get number of samples that can be popped off of the buffer.
- L1196 _public function_ `uint32 GetCapacity() const` — Get the current capacity of the buffer
- L1202 _public function_ `uint32 Remainder() const` — Get number of samples that can be pushed onto the buffer before it is full.

#### struct `Audio::TGetPower`  
`template <int Base, int Exp> struct TGetPower`  
_L1212-1216_
- desc: This allows us to write a compile time exponent of a number.
- L1215 _public member_ `static const int64 Value = Base * TGetPower<Base, Exp - 1>::Value;`
- L1221 _public member_ `static const int64 Value = 1;`

#### struct `Audio::TGetPower`  
`template <int Base> struct TGetPower<Base, 0>`  
_L1219-1222_
- L1215 _public member_ `static const int64 Value = Base * TGetPower<Base, Exp - 1>::Value;`
- L1221 _public member_ `static const int64 Value = 1;`

#### class `Audio::TSample`  
`template <typename SampleType, uint32 Q = (sizeof(SampleType) * 8 - 1)> class TSample`  
_L1229-1398_
- desc: TSample<SampleType, Q> Variant type to simplify converting and performing operations on fixed precision and floating point samples.
- L1231 _private member_ `SampleType Sample;`
- L1234 _private function_ `template <typename SampleTypeToCheck> static void CheckValidityOfSampleType()`
- L1241 _private function_ `template <typename SampleTypeToCheck, uint32 QToCheck> static void CheckValidityOfQ()`
- L1249 _private member_ `static constexpr float QFactor = TGetPower<2, Q>::Value - 1;` — This is the number used to convert from float to our fixed precision value.
- L1252 _private member_ `static constexpr float MaxValue = TGetPower<2, (sizeof(SampleType) * 8 - Q)>::Value;` — for fixed precision types, the max and min values that we can represent are calculated here:
- L1253 _private member_ `static constexpr float MinValue = !!TIsSigned<SampleType>::Value ? (-1.0f * MaxValue) : 0.0f;`
- L1257 _public function_ `TSample(SampleType& InSample) : Sample(InSample)`
- L1265 _public function_ `template<typename ReturnType = float> ReturnType AsFloat() const`
- L1286 _public function_ `template<typename ReturnType, uint32 ReturnQ = (sizeof(SampleType) * 8 - 1)> ReturnType AsFixedPrecisionInt()`
- L1314 _public function_ `template <typename OtherSampleType> TSample<SampleType, Q>& operator =(const OtherSampleType InSample)`

#### class `Audio::TSampleRef`  
`template <typename SampleType, uint32 Q = (sizeof(SampleType) * 8 - 1)> class TSampleRef`  
_L1417-1588_
- desc: TSampleRef<SampleType, Q> Ref version of TSample. Useful for converting between fixed and float precisions. Example usage: int16 FixedPrecisionSample; TSampleRef<int16, 15> SampleRef(FixedPrecisionSample); // Set the sample value directly: SampleRef = 0.5f; // Or multiply the the sample: SampleRef *= 0.5f; bool bThisCodeWorks = FixedPrecisionSample == TNumericLimits<int16>::Max() / 4;
- L1419 _private member_ `SampleType& Sample;`
- L1422 _private function_ `template <typename SampleTypeToCheck> static void CheckValidityOfSampleType()`
- L1429 _private function_ `template <typename SampleTypeToCheck, uint32 QToCheck> static void CheckValidityOfQ()`
- L1437 _private member_ `static constexpr float QFactor = TGetPower<2, Q>::Value - 1;` — This is the number used to convert from float to our fixed precision value.
- L1440 _private member_ `static constexpr float MaxValue = TGetPower<2, (sizeof(SampleType) * 8 - Q)>::Value;` — for fixed precision types, the max and min values that we can represent are calculated here:
- L1441 _private member_ `static constexpr float MinValue = !!TIsSigned<SampleType>::Value ? (-1.0f * MaxValue) : 0.0f;`
- L1445 _public function_ `TSampleRef(SampleType& InSample) : Sample(InSample)`
- L1453 _public function_ `template<typename ReturnType = float> ReturnType AsFloat() const`
- L1474 _public function_ `template<typename ReturnType, uint32 ReturnQ = (sizeof(SampleType) * 8 - 1)> ReturnType AsFixedPrecisionInt()`
- L1503 _public function_ `template <typename OtherSampleType> TSampleRef<SampleType, Q>& operator =(const OtherSampleType InSample)`

#### Free symbols / members of external scopes

- L22 _macro_ `#define CHECK_SAMPLE(VALUE) Audio::CheckSample(VALUE)`
- L23 _macro_ `#define CHECK_SAMPLE2(VALUE) Audio::CheckSample(VALUE)`
- L26 _namespace_ `namespace Audio`
- L30 _function_ `inline void CheckSample(float InSample, float Threshold = 0.001f)` (scope `Audio`) — Utility to check for sample clipping. Put breakpoint in conditional to find DSP code that's not behaving correctly
- L40 _function_ `inline float UnderflowClamp(const float InValue)` (scope `Audio`) — `UE_DEPRECATED(5.5, "Audio code relies on denormals flush to zero floating point mode from now on. Please use FScopedFTZFloatMode instead of this API")` — Clamps floats to 0 if they are in sub-normal range
- L50 _function_ `inline float ConvertToDecibels(const float InLinear, const float InFloor = UE_SMALL_NUMBER)` (scope `Audio`) — Function converts linear scale volume to decibels
- L56 _function_ `inline float ConvertToLinear(const float InDecibels)` (scope `Audio`) — Function converts decibel to linear scale
- L62 _function_ `inline float GetGainFromVelocity(const float InVelocity)` (scope `Audio`) — Given a velocity value [0,127], return the linear gain
- L73 _function_ `inline float FastSin(const float X)` (scope `Audio`) — Low precision, high performance approximation of sine using parabolic polynomial approx Valid on interval [-PI, PI]
- L79 _function_ `inline float FastSin2(const float X)` (scope `Audio`) — Slightly higher precision, high performance approximation of sine using parabolic polynomial approx
- L89 _function_ `inline float FastSin3(const float X)` (scope `Audio`) — Valid on interval [-PI, PI] Sine approximation using Bhaskara I technique discovered in 7th century. https://en.wikipedia.org/wiki/Bh%C4%81skara_I
- L242 _function_ `inline float FastTanh(float X)` (scope `Audio`) — Fast tanh based on pade approximation
- L251 _function_ `inline float FastTan(float X)` (scope `Audio`) — Based on sin parabolic approximation
- L259 _function_ `inline float GetBipolar(const float X)` (scope `Audio`) — Gets polar value from unipolar
- L265 _function_ `inline float GetUnipolar(const float X)` (scope `Audio`) — Converts bipolar value to unipolar
- L272 _function_ `inline void ConvertBipolarBufferToUnipolar(float* InAlignedBuffer, int32 NumSamples)` (scope `Audio`) — Converts in place a buffer into Unipolar (0..1) This is a Vector op version of the GetUnipolar function. (0.5f * X + 0.5f).
- L289 _function_ `inline bool IsAudioBufferSilent(const float* AudioBuffer, const int32 NumSamples)` (scope `Audio`)
- L328 _function_ `inline float GetFrequencyFromMidi(const float InMidiNote)` (scope `Audio`) — Using midi tuning standard, compute frequency in hz from midi value
- L334 _function_ `inline float GetLogFrequencyClamped(const float InValue, const FVector2D& Domain, const FVector2D& Range)` (scope `Audio`) — Returns the log frequency of the input value. Maps linear domain and range values to log output (good for linear slider controlling frequency)
- L359 _function_ `inline float GetLinearFrequencyClamped(const float InFrequencyValue, const FVector2D& Domain, const FVector2D& Range)` (scope `Audio`) — Returns the linear frequency of the input value. Maps log domain and range values to linear output (good for linear slider representation/visualization of log frequency). Reverse of GetLogFrequencyClamped.
- L384 _function_ `inline float GetMidiFromFrequency(const float InFrequency)` (scope `Audio`) — Using midi tuning standard, compute midi from frequency in hz
- L390 _function_ `inline float GetMidiFromFrequency(const float InFrequency, const float TuningFrequency)` (scope `Audio`) — Using passed in tuning frequency (standard is 440), compute midi from frequency in hz
- L400 _function_ `inline float GetPitchScaleFromMIDINote(int32 BaseMidiNote, int32 TargetMidiNote)` (scope `Audio`) — Return a pitch scale factor based on the difference between a base midi note and a target midi note. Useful for samplers.
- L409 _function_ `inline float GetFrequencyMultiplier(const float InPitchSemitones)` (scope `Audio`) — Returns the frequency multiplier to scale a base frequency given the input semitones
- L420 _function_ `inline float GetSemitones(const float InMultiplier)` (scope `Audio`) — Returns the number of semitones relative to a base frequency given the input frequency multiplier
- L431 _function_ `inline void GetStereoPan(const float InLinearPan, float& OutLeft, float& OutRight)` (scope `Audio`) — Calculates equal power stereo pan using sinusoidal-panning law and cheap approximation for sin InLinear pan is [-1.0, 1.0] so it can be modulated by a bipolar LFO
- L440 _function_ `inline void EncodeMidSide(float& LeftChannel, float& RightChannel)` (scope `Audio`) — Encodes a stereo Left/Right signal into a stereo Mid/Side signal
- L449 _prototype_ `void EncodeMidSide( const FAlignedFloatBuffer& InLeftChannel, const FAlignedFloatBuffer& InRightChannel, FAlignedFloatBuffer& OutMidChannel, FAlignedFloatBuffer& OutSideChannel);` (scope `Audio`) — Encodes a stereo Left/Right signal into a stereo Mid/Side signal
- L457 _function_ `inline void DecodeMidSide(float& MidChannel, float& SideChannel)` (scope `Audio`) — Decodes a stereo Mid/Side signal into a stereo Left/Right signal
- L466 _prototype_ `void DecodeMidSide( const FAlignedFloatBuffer& InMidChannel, const FAlignedFloatBuffer& InSideChannel, FAlignedFloatBuffer& OutLeftChannel, FAlignedFloatBuffer& OutRightChannel);` (scope `Audio`) — Decodes a stereo Mid/Side signal into a stereo Left/Right signal
- L473 _function_ `inline float GetBandwidthFromQ(const float InQ)` (scope `Audio`) — Helper function to get bandwidth from Q
- L483 _function_ `inline float GetQFromBandwidth(const float InBandwidth)` (scope `Audio`) — Helper function get Q from bandwidth
- L498 _function_ `inline bool QuadraticPeakInterpolation(const float InValues[3], float& OutPeakLoc, float& OutPeakValue)` (scope `Audio`) — Given three values, determine peak location and value of quadratic fitted to the data. @param InValues - An array of 3 values with the maximum value located in InValues[1]. @param OutPeakLoc - The peak location relative to InValues[1]. @param OutPeakValue - The value of the peak at the peak location. @returns True if a peak was found, false if the values do not represent a peak.
- L525 _function_ `inline float LagrangianInterpolation(const TArray<FVector2D> Points, const float Alpha)` (scope `Audio`) — Polynomial interpolation using lagrange polynomials. https://en.wikipedia.org/wiki/Lagrange_polynomial
- L1343 _function_ `template <typename OtherSampleType> friend TSample<SampleType, Q> operator *(const TSample<SampleType, Q>& LHS, const OtherSampleType& RHS)` (scope `Audio`)
- L1532 _function_ `template <typename OtherSampleType> friend SampleType operator *(const TSampleRef<SampleType>& LHS, const OtherSampleType& RHS)` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/DynamicDelayAPF.h` (Public)


#### class `Audio::FDynamicDelayAPF`  
`class FDynamicDelayAPF`  
_L15-66_
- desc: All Pass Filter with a long fractional delay which can be set per a sample. This filter is specifically designed for reverb applications where filter delay lines are long.
- L23 _public prototype_ `FDynamicDelayAPF(float InG, int32 InMinDelay, int32 InMaxDelay, int32 InMaxNumInternalBufferSamples, float InSampleRate);` — InG is the filter coefficient used in the long delay all pass filter. InMinDelay is the minimum allowable delay of the all pass filter. InMaxDelay is the maximum allowable delay of the all pass filter. InMaxNumInternalBufferSamples is the maximum internal block size used internally. InSampleRate is the current rendering sample rate. Used to convert parameter ease time from seconds to samples.
- L26 _public prototype_ `~FDynamicDelayAPF();` — Destructor
- L29 _public function_ `void SetG(float InG)` — Set the APF feedback/feedforward gain coefficient
- L36 _public prototype_ `void ProcessAudio(const FAlignedFloatBuffer& InSamples, const FAlignedFloatBuffer& InDelays, FAlignedFloatBuffer& OutSamples);` — Processes InSamples through the all pass filter and populates OutSamples with the filter output. InDelays denotes the per-sample delay of the allpass. It must have an equal number of elements as InSamples
- L39 _public prototype_ `void Reset();` — Zeros the internal delay line.
- L41 _public function_ `void SetEaseTimeInSec(float InEaseTimeInSec)`
- L46 _protected prototype_ `void ProcessAudioBlock(const float* InSamples, const FAlignedFloatBuffer& InFractionalDelays, const int32 InNum, float* OutSamples);` — Process one block of audio.
- L50 _private member_ `FLinearEase G;` — Feedback/Feedforward gain coefficient
- L51 _private member_ `float EaseTimeInSec;`
- L52 _private member_ `int32 MinDelay;`
- L53 _private member_ `int32 MaxDelay;`
- L54 _private member_ `int32 NumDelaySamples;`
- L55 _private member_ `int32 NumInternalBufferSamples;`
- L58 _private member_ `FAlignedFloatBuffer FractionalDelays;` — Buffers for block processing
- L59 _private member_ `FAlignedFloatBuffer DelayLineInput;`
- L60 _private member_ `FAlignedFloatBuffer WorkBufferA;`
- L61 _private member_ `FAlignedFloatBuffer WorkBufferB;`
- L64 _private member_ `TUniquePtr<FAlignedBlockBuffer> IntegerDelayLine;` — Delay line memory.
- L65 _private member_ `TUniquePtr<FLinearInterpFractionalDelay> FractionalDelayLine;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/DynamicStateVariableFilter.h` (Public)


#### enum `Audio::EDynamicFilterType`  
`enum EDynamicFilterType`  
_L10-15_
- L12 _public enumerator_ `Bell`
- L13 _public enumerator_ `LowShelf`
- L14 _public enumerator_ `HighShelf`

#### class `Audio::FDynamicStateVariableFilter`  
`class FDynamicStateVariableFilter`  
_L18-128_
- desc: combination of two state-variable filters, the first filtering a key signal, which drives gain in the second
- L21 _public prototype_ `void Init(const float InSampleRate, const int32 InNumChannels);`
- L22 _public prototype_ `void Reset();`
- L24 _public prototype_ `void ProcessAudio(const float* InSamples, float* OutSamples, const int32 InNumSamples);`
- L25 _public prototype_ `void ProcessAudio(const float* InSamples, float* OutSamples, const float* KeySamples, const int32 InNumSamples);`
- L27 _public prototype_ `void SetFrequency(const float InFrequency);`
- L28 _public prototype_ `void SetQ(const float InQ);`
- L29 _public prototype_ `void SetGain(const float InGain);`
- L30 _public prototype_ `void SetFilterType(const EDynamicFilterType InFilterType);`
- L32 _public prototype_ `void SetAnalog(const bool bInAnalog);`
- L33 _public prototype_ `void SetAttackTime(const float InAttackTime);`
- L34 _public prototype_ `void SetReleaseTime(const float InReleaseTime);`
- L35 _public prototype_ `void SetThreshold(const float InThresholdDb);`
- L36 _public prototype_ `void SetEnvMode(const EPeakMode::Type InMode);`
- L37 _public prototype_ `void SetDynamicRange(const float InDynamicRange);`
- L38 _public prototype_ `void SetRatio(const float InRatio);`
- L39 _public prototype_ `void SetKnee(const float InKnee);`
- L41 _public prototype_ `float GetGainReduction();`
- L44 _protected member_ `float SampleRate = 48000.f;`
- L45 _protected member_ `float OneOverSampleRate = 1.f / 48000.f;`
- L46 _protected member_ `int32 NumChannels = 0;`
- L49 _protected member_ `EDynamicFilterType FilterType = EDynamicFilterType::Bell;` — human readable parameters
- L51 _protected member_ `float Frequency = 1000.f;`
- L52 _protected member_ `float Q = 1.f;`
- L53 _protected member_ `float OneOverQ = 1.f;`
- L54 _protected member_ `float ThresholdDb = -12.f;`
- L55 _protected member_ `float DynamicRangeDb = 0.f;`
- L56 _protected member_ `float Ratio = 1.5f;`
- L57 _protected member_ `float GainDb = 1.f;`
- L58 _protected member_ `float Knee = 12.f;`
- L59 _protected member_ `float HalfKnee = 6.f;`
- L62 _protected member_ `float ScaledGainLinear = 1.f;` — cached result of envelope follower
- L65 _protected member_ `float SlopeFactor = 0.f;` — Cached Gain ratio, only needs to be updated when Ratio is changed
- L68 _protected member_ `bool bNeedsUpdate = true;` — whether coefficients need updating
- L106 _protected member_ `FInlineEnvelopeFollower Envelope;`
- L108 _protected member_ `FSVFState KeyFilterState;`
- L110 _protected member_ `TArray<FSVFState> FilterState;` — One per channel
- L112 _protected member_ `FSVFCoefficients KeyVars;`
- L114 _protected member_ `FSVFCoefficients OutputVars;`
- L117 _protected member_ `TArray<FVector2D> KneePoints;` — Points in the knee used for lagrangian interpolation
- L119 _protected prototype_ `void ProcessBell(const float* InSamples, float* OutSamples, const float* KeySamples, const int32 InNumSamples);`
- L120 _protected prototype_ `void ProcessLowShelf(const float* InSamples, float* OutSamples, const float* KeySamples, const int32 InNumSamples);`
- L121 _protected prototype_ `void ProcessHighShelf(const float* InSamples, float* OutSamples, const float* KeySamples, const int32 InNumSamples);`
- L123 _protected prototype_ `void UpdateSettings();`
- L124 _protected prototype_ `void UpdatePreFilterVariables();`
- L125 _protected prototype_ `void UpdatePostFilterVariables();`
- L127 _protected prototype_ `float CalcGain(const float KeySample);`

#### struct `Audio::FDynamicStateVariableFilter::FSVFCoefficients`  
`struct FSVFCoefficients`  
_L72-90_
- desc: state-variable coefficient formulas for the included filter modes can be found here: https://cytomic.com/files/dsp/SvfLinearTrapOptimised2.pdf
- L75 _public member_ `float G = 0.f;` — TanOmega
- L78 _public member_ `float K = 0.f;` — Feedback / 1/Q
- L81 _public member_ `float A0 = 1.f;` — Node Scalars
- L82 _public member_ `float A1 = 0.f;`
- L83 _public member_ `float A2 = 0.f;`
- L84 _public member_ `float A3 = 0.f;`
- L87 _public member_ `float M0 = 1.f;` — Output Scalars
- L88 _public member_ `float M1 = 0.f;`
- L89 _public member_ `float M2 = 0.f;`

#### struct `Audio::FDynamicStateVariableFilter::FSVFState`  
`struct FSVFState`  
_L92-104_
- L95 _public member_ `float V1 = 0.f;` — Nodes
- L96 _public member_ `float V2 = 0.f;`
- L97 _public member_ `float V3 = 0.f;`
- L100 _public member_ `float Z1 = 0.f;` — Delays
- L101 _public member_ `float Z2 = 0.f;`
- L103 _public prototype_ `void ProcessSample(const FSVFCoefficients& Coeffs, const float InSample);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/DynamicsProcessor.h` (Public)


#### enum `Audio::EDynamicsProcessingMode::Type`  
`enum Type`  
_L15-23_
- L17 _public enumerator_ `Compressor`
- L18 _public enumerator_ `Limiter`
- L19 _public enumerator_ `Expander`
- L20 _public enumerator_ `Gate`
- L21 _public enumerator_ `UpwardsCompressor`
- L22 _public enumerator_ `Count`

#### enum `Audio::EDynamicsProcessorChannelLinkMode`  
`enum class EDynamicsProcessorChannelLinkMode : uint8`  
_L26-32_
- L28 _public enumerator_ `Disabled`
- L29 _public enumerator_ `Average`
- L30 _public enumerator_ `Peak`
- L31 _public enumerator_ `Count`

#### class `Audio::FDynamicsProcessor`  
`class FDynamicsProcessor`  
_L36-190_
- desc: Dynamic range compressor https://en.wikipedia.org/wiki/Dynamic_range_compression
- L39 _public prototype_ `FDynamicsProcessor();`
- L40 _public prototype_ `~FDynamicsProcessor();`
- L42 _public prototype_ `void Init(const float InSampleRate, const int32 InNumChannels = 2);`
- L44 _public prototype_ `int32 GetNumChannels() const;`
- L45 _public prototype_ `int32 GetKeyNumChannels() const;`
- L46 _public prototype_ `float GetMaxLookaheadMsec() const;`
- L48 _public prototype_ `void SetLookaheadMsec(const float InLookAheadMsec);`
- L49 _public prototype_ `void SetAttackTime(const float InAttackTimeMsec);`
- L50 _public prototype_ `void SetReleaseTime(const float InReleaseTimeMsec);`
- L51 _public prototype_ `void SetThreshold(const float InThresholdDb);`
- L52 _public prototype_ `void SetRatio(const float InCompressionRatio);`
- L53 _public prototype_ `void SetKneeBandwidth(const float InKneeBandwidthDb);`
- L54 _public prototype_ `void SetInputGain(const float InInputGainDb);`
- L55 _public prototype_ `void SetKeyAudition(const bool InAuditionEnabled);`
- L56 _public prototype_ `void SetKeyGain(const float InKeyGain);`
- L57 _public prototype_ `void SetKeyHighshelfCutoffFrequency(const float InCutoffFreq);`
- L58 _public prototype_ `void SetKeyHighshelfEnabled(const bool bInEnabled);`
- L59 _public prototype_ `void SetKeyHighshelfGain(const float InGainDb);`
- L60 _public prototype_ `void SetKeyLowshelfCutoffFrequency(const float InCutoffFreq);`
- L61 _public prototype_ `void SetKeyLowshelfEnabled(const bool bInEnabled);`
- L62 _public prototype_ `void SetKeyLowshelfGain(const float InGainDb);`
- L63 _public prototype_ `void SetKeyNumChannels(const int32 InNumChannels);`
- L64 _public prototype_ `void SetNumChannels(const int32 InNumChannels);`
- L65 _public prototype_ `void SetOutputGain(const float InOutputGainDb);`
- L66 _public prototype_ `void SetChannelLinkMode(const EDynamicsProcessorChannelLinkMode InLinkMode);`
- L67 _public prototype_ `void SetAnalogMode(const bool bInIsAnalogMode);`
- L68 _public prototype_ `void SetPeakMode(const EPeakMode::Type InEnvelopeFollowerModeType);`
- L69 _public prototype_ `void SetProcessingMode(const EDynamicsProcessingMode::Type ProcessingMode);`
- L71 _public prototype_ `void ProcessAudioFrame(const float* InFrame, float* OutFrame, const float* InKeyFrame);`
- L72 _public prototype_ `void ProcessAudioFrame(const float* InFrame, float* OutFrame, const float* InKeyFrame, float* OutGain);`
- L73 _public prototype_ `void ProcessAudio(const float* InBuffer, const int32 InNumSamples, float* OutBuffer, const float* InKeyBuffer = nullptr, float* OutEnvelope = nullptr);`
- L76 _public prototype_ `void ProcessAudio(const float* const* const InBuffers, const int32 InNumFrames, float* const* OutBuffers, const float* const* const InKeyBuffers, float* const* OutEnvelopes);` — For single channels of audio OR non-interleaved blocks of multichannel audio.
- L79 _protected prototype_ `float ComputeGain(const float InEnvFollowerDb);`
- L80 _protected prototype_ `void ComputeGains(float* InEnvFollowerDbOutGain, const int32 InNumSamples);`
- L84 _protected prototype_ `bool ProcessKeyFrame(const float* InKeyFrame, float* OutFrame, bool bKeyIsInput);` — Process key frame, returning true if should continue processing (Returns false in audition mode and writes straight to output).
- L86 _protected prototype_ `bool IsInProcessingThreshold(const float InEnvFollowerDb) const;`
- L89 _protected member_ `FBiquadFilter InputLowshelfFilter;` — (Optional) Low-pass filter for input signal
- L92 _protected member_ `FBiquadFilter InputHighshelfFilter;` — (Optional) High-pass filter for input signal
- L94 _protected member_ `EDynamicsProcessingMode::Type ProcessingMode;`
- L96 _protected member_ `float SlopeFactor;`
- L99 _protected member_ `EPeakMode::Type EnvelopeFollowerPeakMode;` — Peak mode of envelope followers
- L102 _protected member_ `TArray<FIntegerDelay> LookaheadDelay;` — Lookahead delay lines
- L105 _protected member_ `TArray<FInlineEnvelopeFollower> EnvFollower;` — Envelope followers
- L108 _protected member_ `TArray<float> DetectorOuts;` — Channel values of cached detector sample
- L111 _protected member_ `TArray<float> Gain;` — Channel values of cached gain sample
- L114 _protected member_ `float LookaheadDelayMsec;` — How far ahead to look in the audio
- L117 _protected member_ `float AttackTimeMsec;` — The period of which the compressor decreases gain to the level determined by the compression ratio
- L120 _protected member_ `float ReleaseTimeMsec;` — The period of which the compressor increases gain to 0 dB once level has fallen below the threshold
- L123 _protected member_ `float ThresholdDb;` — Amplitude threshold above which gain will be reduced
- L126 _protected member_ `float Ratio;` — Amount of gain reduction
- L129 _protected member_ `float HalfKneeBandwidthDb;` — Defines how hard or soft the gain reduction blends from no gain reduction to gain reduction (determined by the ratio)
- L132 _protected member_ `float InputGain;` — Amount of input gain
- L135 _protected member_ `float OutputGain;` — Amount of output gain
- L138 _protected member_ `float KeyGain;` — Gain of key detector signal in dB
- L141 _protected member_ `float SampleRate;` — Sample rate of both key and input (must match)
- L144 _protected member_ `EDynamicsProcessorChannelLinkMode LinkMode;` — Whether or not input channels are linked, and if so, how to calculate gain
- L147 _protected member_ `bool bIsAnalogMode;` — Whether or not we're in analog mode
- L150 _protected member_ `bool bKeyAuditionEnabled;` — Whether or not to bypass processor and only output key modulator
- L153 _protected member_ `bool bKeyHighshelfEnabled;` — Whether or not key high-pass filter is enabled
- L156 _protected member_ `bool bKeyLowshelfEnabled;` — Whether or not key low-pass filter is enabled
- L158 _protected member_ `static constexpr float UpwardsCompressionMaxGain = 36.0f;`
- L160 _protected member_ `static constexpr float MaxLookaheadMsec = 100.0f;`
- L168 _private prototype_ `void ProcessAudioDeinterleaveInternal(const float* const* const InBuffers, const int32 InNumFrames, float* const* OutBuffers, const float* const* const InKeyBuffers, float* const* OutEnvelopes);` — OutBuffers is also used a temporary buffer for processing the Key. Thus, OutBuffers must supply enough valid memory to support it's use as a temporary buffer and needs to have Max(NumInputChannels, NumKeyChannels) buffers available.
- L170 _private prototype_ `int32 GetNumDelayFrames() const;`
- L172 _private prototype_ `void CalculateSlope();`
- L174 _private prototype_ `void CalculateKnee();`
- L182 _private member_ `TArray<FKneePoint> KneePoints;`
- L185 _private member_ `float Denominator0Minus1;` — For optimized LagrangianInterpolation on blocks...
- L188 _private member_ `float Denominator1Minus0;` — For optimized LagrangianInterpolation on blocks...

#### struct `Audio::FDynamicsProcessor::FKneePoint`  
`struct FKneePoint`  
_L177-181_
- desc: Points in the knee used for lagrangian interpolation
- L179 _public member_ `float X{ 0.0f };`
- L180 _public member_ `float Y{ 0.0f };`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`
- L13 _namespace_ `namespace EDynamicsProcessingMode` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/EQ.h` (Public)


#### class `Audio::FEqualizer`  
`class FEqualizer`  
_L13-53_
- desc: Equalizer filter An equalizer is a cascaded (serial) band of parametric EQs This filter allows for setting each band with variable Bandwidth/Q, Frequency, and Gain
- L17 _public prototype_ `FEqualizer();` — Constructor
- L20 _public prototype_ `~FEqualizer();` — Destructor
- L23 _public prototype_ `void Init(const float InSampleRate, const int32 InNumBands, const int32 InNumChannels);` — Initialize the equalizer
- L26 _public prototype_ `void SetBandEnabled(const int32 InBand, const bool bEnabled);` — Sets whether or not the band is enabled
- L29 _public prototype_ `void SetBandParams(const int32 InBand, const float InFrequency, const float InBandwidth, const float InGainDB);` — Sets all params of the band at once
- L32 _public prototype_ `void SetBandFrequency(const int32 InBand, const float InFrequency);` — Sets the band frequency
- L35 _public prototype_ `void SetBandBandwidth(const int32 InBand, const float InBandwidth);` — Sets the band resonance (use alternatively to bandwidth)
- L38 _public prototype_ `void SetBandGainDB(const int32 InBand, const float InGainDB);` — Sets the band gain in decibels
- L41 _public prototype_ `void ProcessAudioFrame(const float* InAudio, float* OutAudio);` — Processes the audio frame (audio frame must have channels equal to that used during initialization)
- L46 _private member_ `int32 NumChannels;` — The number of channels in the equalizer
- L49 _private member_ `TArray<FBiquadFilter> FilterBands;` — The array of biquad filters
- L52 _private member_ `TArray<float> WorkBuffer;` — Temporary array for processing audio.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/EarlyReflectionsFast.h` (Public)


#### struct `Audio::FEarlyReflectionsFastSettings`  
`struct FEarlyReflectionsFastSettings`  
_L14-36_
- L17 _public member_ `float Gain;` — Early reflections gain
- L20 _public member_ `float PreDelayMsec;` — Delay between input signal and early reflections
- L23 _public member_ `float Bandwidth;` — Input sample bandwidth before entering early reflections
- L26 _public member_ `float Decay;` — Early reflections decay (lower value is longer)
- L29 _public member_ `float Absorption;` — Early reflection high frequency absorption factor
- L31 _public prototype_ `FEarlyReflectionsFastSettings();`
- L33 _public prototype_ `bool operator==(const FEarlyReflectionsFastSettings& Other) const;`
- L35 _public prototype_ `bool operator!=(const FEarlyReflectionsFastSettings& Other) const;`

#### class `Audio::FEarlyReflectionsFast`  
`class FEarlyReflectionsFast`  
_L41-99_
- desc: Basic implementation of early reflections using a predelay, low pass filter and feedback delay network (FDN). The FDN utilizes four delay lines where each delay line consists of an all pass filter and low pass filter to control diffusion and absorption.
- L46 _public member_ `static const float MaxGain;` — Limits for settings
- L47 _public member_ `static const float MinGain;`
- L48 _public member_ `static const float MaxPreDelay;`
- L49 _public member_ `static const float MinPreDelay;`
- L50 _public member_ `static const float MaxBandwidth;`
- L51 _public member_ `static const float MinBandwidth;`
- L52 _public member_ `static const float MaxDecay;`
- L53 _public member_ `static const float MinDecay;`
- L54 _public member_ `static const float MaxAbsorption;`
- L55 _public member_ `static const float MinAbsorption;`
- L57 _public member_ `static const FEarlyReflectionsFastSettings DefaultSettings;`
- L60 _public prototype_ `FEarlyReflectionsFast(float InSampleRate, int32 InMaxNumInternalBufferSamples, const FEarlyReflectionsFastSettings& InSettings=DefaultSettings);` — InMaxNumInternalBufferSamples sets the maximum possible samples in an internal buffer.
- L61 _public prototype_ `~FEarlyReflectionsFast();`
- L64 _public prototype_ `void SetSettings(const FEarlyReflectionsFastSettings& InSettings);` — Sets the reverb settings, clamps, applies, and updates
- L67 _public prototype_ `void ProcessAudio(const FAlignedFloatBuffer& InSamples, const int32 InNumChannels, FAlignedFloatBuffer& OutLeftSamples, FAlignedFloatBuffer& OutRightSamples);` — Process the single audio frame
- L70 _public prototype_ `void FlushAudio();` — Silence internal audio.
- L73 _public prototype_ `static void ClampSettings(FEarlyReflectionsFastSettings& InOutSettings);` — Clamps settings to acceptable values.
- L76 _private prototype_ `void ApplySettings();`
- L78 _private member_ `FEarlyReflectionsFastSettings Settings;`
- L79 _private member_ `float SampleRate;`
- L81 _private member_ `FAlignedFloatBuffer LeftInputBuffer;`
- L82 _private member_ `FAlignedFloatBuffer LeftWorkBufferA;`
- L83 _private member_ `FAlignedFloatBuffer LeftWorkBufferB;`
- L84 _private member_ `FAlignedFloatBuffer RightInputBuffer;`
- L85 _private member_ `FAlignedFloatBuffer RightWorkBufferA;`
- L86 _private member_ `FAlignedFloatBuffer RightWorkBufferB;`
- L88 _private member_ `FFDNCoefficients LeftCoefficients;`
- L89 _private member_ `FFDNCoefficients RightCoefficients;`
- L91 _private member_ `FFeedbackDelayNetwork LeftFDN;`
- L92 _private member_ `FFeedbackDelayNetwork RightFDN;`
- L94 _private member_ `FIntegerDelay LeftPreDelay;`
- L95 _private member_ `FIntegerDelay RightPreDelay;`
- L97 _private member_ `FBufferOnePoleLPF LeftInputLPF;`
- L98 _private member_ `FBufferOnePoleLPF RightInputLPF;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/Encoders/IAudioEncoder.h` (Public)


#### class `Audio::IAudioEncoder`  
`class IAudioEncoder`  
_L15-97_
- desc: IAudioEncoder Interface used to implement a runtime audio encoder.
- L23 _public prototype_ `IAudioEncoder(uint32 AudioBufferSlack, uint32 DataBufferSlack = 4096);` — Must be constructed with AudioBufferSlack. Optionally, DataBufferSlack can be called with a different value depending on how often PushAudio, EncodeIfPossible, or PopData will be called.
- L24 _public prototype_ `virtual ~IAudioEncoder();`
- L32 _public prototype_ `bool PushAudio(const float* InBuffer, int32 NumSamples, bool bEncodeIfPossible = true);` — Call this function when audio is available. If you would like to handle compression on a separate thread or call, Call this function with bEncodeIfPossible set to false. Returns true if audio was successfully pushed, false, if the internal buffer is full.
- L39 _public prototype_ `int32 PopData(uint8* OutData, int32 DataSize);` — Pop compressed data. If you are using this encoder for streaming over network, use the size returned by GetCompressedPacketSize(). Returns number of bytes written.
- L44 _public prototype_ `virtual int32 GetCompressedPacketSize() const = 0;` — Used for internet streaming. Should return the amount of bytes required for a self contained packet.
- L50 _public prototype_ `bool EncodeIfPossible();` — If you'd like to run audio encoding on a separate thread, use this call. Otherwise, ensure that bEncodeIfPossible is set to true when you call PushAudio.
- L56 _public prototype_ `int64 Finalize();` — Call this once you are finished pushing audio. Returns the amount of bytes left to pop if positive, and if negative indicates a failiure.
- L63 _protected prototype_ `void Init(const FSoundQualityInfo& InQualityInfo);` — Should be called in the constructor of any implementation of IAudioEncoder. Calls StartFile if necessary.
- L68 _protected prototype_ `virtual int64 SamplesRequiredPerEncode() const = 0;` — How many samples of decoded audio that are required for a single compression operation.
- L75 _protected prototype_ `virtual bool StartFile(const FSoundQualityInfo& InQualityInfo, TArray<uint8>& OutFileStart) = 0;` — This should be overridden to, give the properties in InQualityInfo, write a header into OutFileStart. returns true on success, or false on failure.
- L81 _protected prototype_ `virtual bool EncodeChunk(const TArray<float>& InAudio, TArray<uint8>& OutBytes) = 0;` — Override this to compress InAudio to OutBytes. Returns true on success, false on failure.
- L87 _protected prototype_ `virtual bool EndFile(TArray<uint8>& OutBytes) = 0;` — Override this to compress InAudio to OutBytes. Returns true on success, false on failure.
- L90 _private prototype_ `IAudioEncoder();`
- L92 _private member_ `TArray<float> CurrentAudioBuffer;`
- L93 _private member_ `TArray<uint8> CurrentCompressedBuffer;`
- L95 _private member_ `TCircularAudioBuffer<float> UncompressedAudioBuffer;`
- L96 _private member_ `TCircularAudioBuffer<uint8> CompressedDataBuffer;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/Encoders/OggVorbisEncoder.h` (Public)


#### class `FOggVorbisEncoder`  
`class FOggVorbisEncoder : public Audio::IAudioEncoder`  
_L12-36_
- inherits: `Audio::IAudioEncoder`
- L15 _public prototype_ `FOggVorbisEncoder(const FSoundQualityInfo& InInfo, int32 AverageBufferCallbackSize);`
- L18 _public prototype_ `virtual int32 GetCompressedPacketSize() const override;` — From IAudioEncoder: returns 0, since Ogg Vorbis is not built for networked streaming.
- L23 _protected prototype_ `virtual int64 SamplesRequiredPerEncode() const override;` — From IAudioEncoder:
- L24 _protected prototype_ `virtual bool StartFile(const FSoundQualityInfo& InQualityInfo, TArray<uint8>& OutFileStart) override;`
- L25 _protected prototype_ `virtual bool EncodeChunk(const TArray<float>& InAudio, TArray<uint8>& OutBytes) override;`
- L26 _protected prototype_ `virtual bool EndFile(TArray<uint8>& OutBytes) override;`
- L29 _private prototype_ `FOggVorbisEncoder();`
- L31 _private member_ `int32 NumChannels;`
- L35 _private member_ `FOggVorbisEncoderPrivateState* PrivateState;` — Private, uniquely owned state. This must be a raw pointer because it has a non-default destructor that isn't public.

### `Source/Runtime/SignalProcessing/Public/DSP/Encoders/OpusEncoder.h` (Public)


#### enum `EOpusFrameSizes`  
`enum class EOpusFrameSizes : uint8`  
_L14-22_
- desc: Possible frame sizes to use for the encoder.
- L16 _public enumerator_ `Min` — 2.5 milliseconds
- L17 _public enumerator_ `Small` — 5 milliseconds
- L18 _public enumerator_ `MediumLow` — 10 milliseconds
- L19 _public enumerator_ `MediumHigh` — 20 milliseconds
- L20 _public enumerator_ `High` — 40 milliseconds
- L21 _public enumerator_ `Max` — 60 milliseconds

#### enum `EOpusMode`  
`enum class EOpusMode : uint8`  
_L24-29_
- L26 _public enumerator_ `File` — Use this when encoding a .opus file. Pushes the Opus frames into Ogg packets.
- L27 _public enumerator_ `AudioStream` — Use this for general music and non-speech streaming applications.
- L28 _public enumerator_ `VoiceStream` — Use this for Voice-specific applications.

#### class `FOpusEncoder`  
`class FOpusEncoder : public Audio::IAudioEncoder`  
_L31-66_
- inherits: `Audio::IAudioEncoder`
- L34 _public prototype_ `FOpusEncoder(const FSoundQualityInfo& InInfo, int32 AverageBufferCallbackSize, EOpusFrameSizes InFrameSize = EOpusFrameSizes::MediumLow, EOpusMode InMode = EOpusMode::File);`
- L35 _public prototype_ `~FOpusEncoder();`
- L37 _public prototype_ `virtual int32 GetCompressedPacketSize() const override;`
- L40 _protected prototype_ `virtual int64 SamplesRequiredPerEncode() const override;`
- L41 _protected prototype_ `virtual bool StartFile(const FSoundQualityInfo& InQualityInfo, TArray<uint8>& OutFileStart) override;`
- L42 _protected prototype_ `virtual bool EncodeChunk(const TArray<float>& InAudio, TArray<uint8>& OutBytes) override;`
- L43 _protected prototype_ `virtual bool EndFile(TArray<uint8>& OutBytes) override;`
- L46 _private prototype_ `FOpusEncoder();`
- L48 _private prototype_ `int32 GetNumSamplesForEncode(EOpusFrameSizes InFrameSize) const;`
- L49 _private prototype_ `int32 GetNumSamplesForPreskip();`
- L51 _private member_ `int32 LastValidFrameSize;`
- L52 _private member_ `int32 NumChannels;`
- L53 _private member_ `int32 SampleRate;`
- L54 _private member_ `int32 UncompressedFrameSize;`
- L58 _private member_ `FOpusEncoderPrivateState* PrivateOpusState;` — Private state so that we don't have a public dependency on opus libraries. Uniquely owned by this instance. Only a raw pointer because the destructor is not accessible.
- L61 _private member_ `FOggEncapsulator* PrivateOggEncapsulator;` — Private state. Only used if we are generating a .opus file, which are ogg encapsulations of an opus stream.
- L64 _private member_ `uint32 GranulePos;` — Used for .opus files only:
- L65 _private member_ `uint32 PacketIndex;`

### `Source/Runtime/SignalProcessing/Public/DSP/Encoders/WavEncoder.h` (Public)


#### class `FWavEncoder`  
`class FWavEncoder : public Audio::IAudioEncoder`  
_L8-26_
- inherits: `Audio::IAudioEncoder`
- L11 _public prototype_ `FWavEncoder(const FSoundQualityInfo& InInfo, int32 AudioCallbackSize);`
- L13 _public prototype_ `virtual int32 GetCompressedPacketSize() const override;`
- L16 _protected prototype_ `virtual int64 SamplesRequiredPerEncode() const override;`
- L17 _protected prototype_ `virtual bool StartFile(const FSoundQualityInfo& InQualityInfo, TArray<uint8>& OutFileStart) override;`
- L18 _protected prototype_ `virtual bool EncodeChunk(const TArray<float>& InAudio, TArray<uint8>& OutBytes) override;`
- L19 _protected prototype_ `virtual bool EndFile(TArray<uint8>& OutBytes) override;`
- L22 _private member_ `int32 CallbackSize;`
- L24 _private prototype_ `FWavEncoder();`

### `Source/Runtime/SignalProcessing/Public/DSP/Envelope.h` (Public)


#### class `Audio::FEnvelope`  
`class FEnvelope`  
_L13-166_
- desc: Envelope class generates ADSR style envelope
- L27 _public prototype_ `FEnvelope();`
- L28 _public prototype_ `virtual ~FEnvelope();`
- L31 _public prototype_ `void Init(const float InSampleRate, const int32 InVoiceId = 0, FModulationMatrix* InModMatrix = nullptr, const bool bInSimulateAnalog = true);` — Initialize the envelope with the given sample rate
- L34 _public prototype_ `void SetSimulateAnalog(const bool bInSimulatingAnalog);` — Sets the envelope mode
- L37 _public function_ `void SetLegato(const bool bInLegatoMode)` — Sets whether the envelope is in legato mode. Legato mode doesn't restart the envelope if it's already playing
- L40 _public function_ `void SetRetrigger(const bool bInRetrigger)` — Sets whether or not the envelope is zero'd when reset
- L41 _public function_ `bool IsRetrigger() const`
- L44 _public prototype_ `virtual void Start();` — Start the envelope, puts envelope in attack state
- L47 _public prototype_ `virtual void StartLegato(const float InNewDepth);` — For truly legato envelope logic, we need to know the new sustain gain (if its being changed).
- L48 _public function_ `virtual void StartLegato()`
- L51 _public prototype_ `virtual void Stop();` — Stop the envelope, puts in the release state. Can optionally force to off state.
- L54 _public prototype_ `virtual void Shutdown();` — Puts envelope into shutdown mode, which is a much faster cutoff than release, but avoids pops
- L57 _public prototype_ `virtual void Kill();` — Kills the envelope (will cause discontinuity)
- L60 _public prototype_ `virtual bool IsDone() const;` — Queries if the envelope has finished
- L63 _public prototype_ `virtual void Reset();` — Resets the envelope
- L66 _public prototype_ `virtual void Update();` — Update the state of the envelope
- L70 _public prototype_ `virtual float Generate(float* BiasedOutput = nullptr);` — Generate the next output value of the envelope. Optionally outputs the bias output (i.e. -1.0 to 1.0)
- L72 _public prototype_ `virtual EEnvelopeState GetState() const;`
- L75 _public prototype_ `virtual void SetAttackTime(const float InAttackTimeMsec);` — Sets the envelope attack time in msec
- L78 _public prototype_ `virtual void SetDecayTime(const float InDecayTimeMsec);` — Sets the envelope decay time in msec
- L81 _public prototype_ `virtual void SetSustainGain(const float InSustainGain);` — Sets the envelope sustain gain in linear gain values
- L84 _public prototype_ `virtual void SetReleaseTime(const float InReleaseTimeMsec);` — Sets the envelope release time in msec
- L87 _public prototype_ `virtual void SetInvert(const bool bInInvert);` — Inverts the value of envelope output
- L90 _public prototype_ `virtual void SetBiasInvert(const bool bInBiasInvert);` — Inverts the value of the biased envelope output
- L93 _public prototype_ `virtual void SetDepth(const float InDepth);` — Sets the envelope depth.
- L96 _public prototype_ `virtual void SetBiasDepth(const float InDepth);` — Sets the depth of the bias output.
- L99 _public function_ `const FPatchSource GetModSourceEnv() const` — Get the envelope's patch nodes
- L100 _public function_ `const FPatchSource GetModSourceBiasEnv() const`
- L119 _protected member_ `int32 VoiceId;` — The current envelope value, used to compute exponential envelope curves
- L120 _protected member_ `float CurrentEnvelopeValue;`
- L121 _protected member_ `float CurrentEnvelopeBiasValue;`
- L122 _protected member_ `float SampleRate;`
- L123 _protected member_ `float AttackTimeMSec;`
- L124 _protected member_ `float DecayTimeMsec;`
- L125 _protected member_ `float SustainGain;`
- L126 _protected member_ `float ReleaseTimeMsec;`
- L127 _protected member_ `float ShutdownTimeMsec;`
- L128 _protected member_ `float ShutdownDelta;`
- L129 _protected member_ `float Depth;`
- L130 _protected member_ `float BiasDepth;`
- L131 _protected member_ `float OutputGain;`
- L133 _protected member_ `FEnvData AttackData;`
- L134 _protected member_ `FEnvData DecayData;`
- L135 _protected member_ `FEnvData ReleaseData;`
- L137 _protected member_ `EEnvelopeState CurrentState;`
- L140 _protected member_ `FModulationMatrix* ModMatrix;` — Mod matrix
- L142 _protected member_ `FPatchSource EnvSource;`
- L143 _protected member_ `FPatchSource BiasedEnvSource;`
- L146 _protected member_ `uint8 bIsSimulatingAnalog:1;` — Whether or not we want to simulate analog behavior
- L149 _protected member_ `uint8 bIsLegatoMode:1;` — Whether or not the envelope is reset back to attack when started
- L152 _protected member_ `uint8 bIsRetriggerMode:1;` — Whether or not the envelope value is set to zero when finished
- L155 _protected member_ `uint8 bChanged:1;` — Whether or not this envelope has changed and needs to have values recomputed
- L158 _protected member_ `uint8 bInvert:1;` — Inverts the output
- L161 _protected member_ `uint8 bBiasInvert:1;` — Bias output inversions
- L165 _protected member_ `uint8 bCurrentCycleIsADOnly:1;` — tracks if the current envelope was started with sustain at 0.0 (avoids bug where sustain being turned up during decay phase makes note hang)

#### enum `Audio::FEnvelope::EEnvelopeState`  
`enum class EEnvelopeState`  
_L17-25_
- desc: States for the envelope state machine
- L19 _public enumerator_ `Off`
- L20 _public enumerator_ `Attack`
- L21 _public enumerator_ `Decay`
- L22 _public enumerator_ `Sustain`
- L23 _public enumerator_ `Release`
- L24 _public enumerator_ `Shutdown`

#### struct `Audio::FEnvelope::FEnvData`  
`struct FEnvData`  
_L103-116_
- L105 _public member_ `float Coefficient;`
- L106 _public member_ `float Offset;`
- L107 _public member_ `float TCO;`
- L108 _public member_ `float TimeSamples;`
- L110 _public function_ `FEnvData() : Coefficient(0.0f) , Offset(0.0f) , TCO(0.0f) , TimeSamples(0.0f)`

#### class `Audio::FADEnvelope`  
`class FADEnvelope`  
_L169-208_
- desc: sample accurate attack-decay style envelope generator
- L172 _public function_ `FADEnvelope()`
- L173 _public prototype_ `~FADEnvelope() = default;`
- L175 _public prototype_ `void Init(int32 InSampleRate);`
- L177 _public prototype_ `void SetAttackTimeSeconds(float InAttackTimeSeconds);`
- L178 _public prototype_ `void SetDecayTimeSeconds(float InReleaseTimeSeconds);`
- L179 _public prototype_ `void SetAttackCurveFactor(float InAttackCurve);`
- L180 _public prototype_ `void SetDecayCurveFactor(float InDecayCurve);`
- L182 _public function_ `void SetLooping(bool bInIsLooping)`
- L183 _public function_ `bool IsLooping() const`
- L186 _public prototype_ `void Attack();` — Call function to trigger a new attack-phase of the envelope generator
- L189 _public prototype_ `void GetNextEnvelopeOut(int32 StartFrame, int32 EndFrame, TArray<int32>& OutFinishedFrames, Audio::AlignedFloatBuffer& OutEnvelope);` — Generates an output audio buffer (used for audio-rate envelopes)
- L192 _public prototype_ `void GetNextEnvelopeOut(int32 StartFrame, int32 EndFrame, TArray<int32>& OutFinishedFrames, float& OutEnvelope);` — Generates a single float value (used for control-rate envelopes)
- L193 _public prototype_ `bool GetNextEnvelopeOut(float& OutEnvelope);`
- L196 _private member_ `int32 CurrentSampleIndex = INDEX_NONE;`
- L197 _private member_ `float StartingEnvelopeValue = 0.0f;`
- L198 _private member_ `float CurrentEnvelopeValue = 0.0f;`
- L199 _private member_ `float AttackTimeSeconds = 0.0f;`
- L200 _private member_ `float DecayTimeSeconds = 0.1f;`
- L201 _private member_ `int32 AttackSampleCount = 0;`
- L202 _private member_ `int32 DecaySampleCount = 0;`
- L203 _private member_ `float AttackCurveFactor = 1.0f;`
- L204 _private member_ `float DecayCurveFactor = 1.0f;`
- L205 _private member_ `float SampleRate = 0.0f;`
- L206 _private member_ `bool bIsLooping = false;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/EnvelopeFollower.h` (Public)


#### enum `Audio::EPeakMode::Type`  
`enum Type`  
_L16-23_
- L18 _public enumerator_ `MeanSquared`
- L19 _public enumerator_ `RootMeanSquared`
- L20 _public enumerator_ `Peak`
- L21 _public enumerator_ `TruePeak`
- L22 _public enumerator_ `Count`

#### class `Audio::FAttackRelease`  
`class FAttackRelease`  
_L28-79_
- desc: Conversion between attack/release time and attack/release sample counts.
- L32 _private member_ `static constexpr float AnalogTimeConstant = 1.00239343f;` — see https://en.wikipedia.org/wiki/RC_time_constant Time constants indicate how quickly the envelope follower responds to changes in input
- L33 _private member_ `static constexpr float DigitalTimeConstant = 4.60517019f;`
- L43 _public prototype_ `FAttackRelease(float InSampleRate, float InAttackTimeMsec, float InReleaseTimeMsec, bool bInIsAnalog);` — Construct an FAttackRelease object. @param InSampleRate - The number of frames per a second. @param InAttackTimeMsec - The desired attack time in milliseconds. @param InReleaseTimeMsec - The desired release time in milliseconds. @param bInIsAnalog - Whether to model analog RC circuits or use digital models.
- L45 _public prototype_ `void SetAnalog(bool bInIsAnalog);`
- L46 _public prototype_ `void SetAttackTime(float InAttackTimeMsec);`
- L47 _public prototype_ `void SetReleaseTime(float InReleaseTimeMsec);`
- L50 _public function_ `inline bool GetAnalog() const` — Get whether set to analog or digital time constant. (True is analog, false is digital)
- L53 _public function_ `inline float GetAttackTimeSamples() const` — Get the attack time in samples.
- L56 _public function_ `inline float GetReleaseTimeSamples() const` — Get the release time in samples.
- L59 _public function_ `inline float GetAttackTimeMsec() const` — Get the attack time in milliseconds.
- L62 _public function_ `inline float GetReleaseTimeMsec() const` — Get the release time in milliseconds.
- L65 _public function_ `inline float GetSampleRate() const` — Get the sample rate.
- L69 _protected prototype_ `void SetSampleRate(float InSampleRate);`
- L73 _private member_ `float SampleRate;`
- L74 _private member_ `float AttackTimeSamples;`
- L75 _private member_ `float AttackTimeMsec;`
- L76 _private member_ `float ReleaseTimeSamples;`
- L77 _private member_ `float ReleaseTimeMsec;`
- L78 _private member_ `bool bIsAnalog;`

#### class `Audio::FAttackReleaseSmoother`  
`class FAttackReleaseSmoother : public FAttackRelease`  
_L83-122_
- inherits: `FAttackRelease`
- desc: Smooths signals using attack and release settings.
- L94 _public prototype_ `FAttackReleaseSmoother(float InSampleRate, int32 InNumChannels, float InAttackTimeMsec, float InReleaseTimeMsec, bool bInIsAnalog);` — Construct an FAttackReleaseSmoother. @param InSampleRate - The number of samples per a second of incoming data. @param InNumChannels - The number of input channels. @param InAttackTimeMsec - The desired attack time in milliseconds. @param InReleaseTimeMsec - The desired release time in milliseconds. @param bInIsAnalog - Whether to model analog RC circuits or use digital models.
- L101 _public prototype_ `void ProcessAudio(const float* InBuffer, int32 InNumFrames);` — Process channel interleaved data. @param InBuffer - Interleaved channel data. @param InNumFrames - Number of frames in InBuffer.
- L109 _public prototype_ `void ProcessAudio(const float* InBuffer, int32 InNumFrames, float* OutBuffer);` — Process channel interleaved data. @param InBuffer - Interleaved input data. @param InNumFrames - Number of frames in InBuffer. @param OutBuffer - Output interleaved envelope data. Should be same size as InBuffer.
- L112 _public prototype_ `const TArray<float>& GetEnvelopeValues() const;` — Retrieve the final values of the envelope for each channel.
- L115 _public prototype_ `void SetNumChannels(int32 InNumChannels);` — Set the number of input channels
- L117 _public prototype_ `void Reset();`
- L120 _private member_ `int32 NumChannels;`
- L121 _private member_ `TArray<float> PriorEnvelopeValues;`

#### class `Audio::FMeanSquaredFIR`  
`class FMeanSquaredFIR`  
_L125-166_
- desc: Compute mean squared using FIR method.
- L127 _private member_ `static constexpr int32 DefaultHistoryCapacity = 16384;`
- L137 _public prototype_ `FMeanSquaredFIR(float InSampleRate, int32 InNumChannels, float InWindowTimeMsec);` — Construct an FMeanSquaredFIR @parma InSampleRate - Number of frames per a second. @param InNumChannels - Number of channels per a frame. @param InWindowTimeMsec - Number of milliseconds per a mean squared window.
- L140 _public prototype_ `void SetWindowSize(float InWindowTimeMsec);` — Set the size of the analysis window.
- L143 _public prototype_ `void SetNumChannels(int32 InNumChannels);` — Set the number of input channels.
- L145 _public prototype_ `void Reset();`
- L153 _public prototype_ `void ProcessAudio(const float* InBuffer, int32 InNumFrames, float* OutBuffer);` — Calculate mean squared per sample. @param InBuffer - Interleaved input data. @param InNumFrames - Number of frames in InBuffer. @param OutBuffer - Output interleaved data. Should be same size as InBuffer.
- L156 _private member_ `float SampleRate;`
- L157 _private member_ `int32 NumChannels;`
- L158 _private member_ `int32 WindowTimeFrames;`
- L159 _private member_ `int32 WindowTimeSamples;`
- L160 _private member_ `float NormFactor;`
- L162 _private member_ `TArray<float> ChannelValues;`
- L163 _private member_ `TCircularAudioBuffer<float> HistorySquared;`
- L164 _private member_ `FAlignedFloatBuffer SquaredHistoryBuffer;`
- L165 _private member_ `FAlignedFloatBuffer SquaredInputBuffer;`

#### class `Audio::FMeanSquaredIIR`  
`class FMeanSquaredIIR`  
_L169-203_
- desc: Compute mean squared using IIR method.
- L178 _public prototype_ `FMeanSquaredIIR(float InSampleRate, int32 InNumChannels, float InWindowTimeMsec);` — Construct an FMeanSquaredIIR @parma InSampleRate - Number of frames per a second. @param InNumChannels - Number of channels per a frame. @param InWindowTimeMsec - Number of milliseconds per a mean squared window.
- L181 _public prototype_ `void SetWindowSize(float InWindowTimeMsec);` — Set the size of the analysis window.
- L184 _public prototype_ `void SetNumChannels(int32 InNumChannels);` — Set the number of input channels.
- L186 _public prototype_ `void Reset();`
- L194 _public prototype_ `void ProcessAudio(const float* InBuffer, int32 InNumFrames, float* OutBuffer);` — Calculate mean squared per sample. @param InBuffer - Interleaved input data. @param InNumFrames - Number of frames in InBuffer. @param OutBuffer - Output interleaved data. Should be same size as InBuffer.
- L197 _private member_ `float SampleRate;`
- L198 _private member_ `int32 NumChannels;`
- L199 _private member_ `float Alpha;`
- L200 _private member_ `float Beta;`
- L202 _private member_ `TArray<float> ChannelValues;`

#### class `Audio::FTruePeak`  
`class FTruePeak`  
_L206-234_
- desc: Compute True-Peak as defined by ITU-R BS.1770-5
- L209 _public function_ `FTruePeak(int32 InNumChannels) : NumChannels(InNumChannels)`
- L218 _public function_ `void SetNumChannels(int32 InNumChannels)`
- L227 _public prototype_ `void Reset();`
- L228 _public prototype_ `void ProcessAudio(const float* InBuffer, int32 InNumFrames, float* OutBuffer);`
- L231 _private member_ `int32 NumChannels = 0;`
- L232 _private member_ `TArray<float> AllChannelSignalHistories;`
- L233 _private member_ `uint32 HistoryPosition = 0;`

#### struct `Audio::FEnvelopeFollowerInitParams`  
`struct FEnvelopeFollowerInitParams`  
_L236-252_
- L239 _public member_ `float SampleRate = 48000.f;` — Number of frames per a second.
- L241 _public member_ `int32 NumChannels = 1;` — Number of channels per a frame.
- L243 _public member_ `float AttackTimeMsec = 10.0f;` — The desired attack time in milliseconds.
- L245 _public member_ `float ReleaseTimeMsec = 100.0f;` — The desired release time in milliseconds.
- L247 _public member_ `EPeakMode::Type Mode = EPeakMode::Peak;` — Technique for measuring amplitude of input signal.
- L249 _public member_ `bool bIsAnalog = true;` — Whether to model analog RC circuits or use digital models.
- L251 _public member_ `float AnalysisWindowMsec=5.f;` — Number of milliseconds per a (root) mean squared window.

#### class `Audio::FEnvelopeFollower`  
`class FEnvelopeFollower`  
_L257-333_
- desc: A simple utility that returns a smoothed value given audio input using an RC circuit.  Used for following the envelope of an audio stream.
- L261 _public prototype_ `FEnvelopeFollower();` — Construct an envelope follower.
- L264 _public prototype_ `FEnvelopeFollower(const FEnvelopeFollowerInitParams& InParams);` — Construct an envelope follower.
- L267 _public prototype_ `void Init(const FEnvelopeFollowerInitParams& InParams);` — Initialize the envelope follower.
- L270 _public prototype_ `int32 GetNumChannels() const;` — Returns the number of channels per an input frame
- L273 _public prototype_ `float GetSampleRate() const;` — Returns the number of frames per a second set on initialization
- L276 _public prototype_ `float GetAttackTimeMsec() const;` — Returns the envelope follower attack time (how fast the envelope responds to input)
- L279 _public prototype_ `float GetReleaseTimeMsec() const;` — Returns the envelope follower release time (how slow the envelope dampens from input)
- L282 _public prototype_ `bool GetAnalog() const;` — Returns whether or not to use analog or digital time constants
- L285 _public prototype_ `EPeakMode::Type GetMode() const;` — Returns the input mode of the envelope follower
- L288 _public prototype_ `void SetNumChannels(int32 InNumChannels);` — Set the number of channels per an input frame.
- L291 _public prototype_ `void SetAnalog(bool bInIsAnalog);` — Sets whether or not to use analog or digital time constants
- L294 _public prototype_ `void SetAttackTime(float InAttackTimeMsec);` — Sets the envelope follower attack time (how fast the envelope responds to input)
- L297 _public prototype_ `void SetReleaseTime(float InReleaseTimeMsec);` — Sets the envelope follower release time (how slow the envelope dampens from input)
- L300 _public prototype_ `void SetMode(EPeakMode::Type InMode);` — Sets the input mode of the envelope follower
- L308 _public prototype_ `void ProcessAudio(const float* InBuffer, int32 InNumFrames, float* OutBuffer);` — Calculate envelope per sample. @param InBuffer - Interleaved input data. @param InNumFrames - Number of frames in InBuffer. @param OutBuffer - Output interleaved data. Should be same size as InBuffer.
- L315 _public prototype_ `void ProcessAudio(const float* InBuffer, int32 InNumFrames);` — Calculate envelope @param InBuffer - Interleaved input data. @param InNumFrames - Number of frames in InBuffer.
- L318 _public prototype_ `const TArray<float>& GetEnvelopeValues() const;` — Retrieve the final values of the envelope for each channel.
- L321 _public prototype_ `void Reset();` — Resets the state of the envelope follower
- L324 _private prototype_ `void ProcessWorkBuffer(const float* InBuffer, int32 InNumFrames);`
- L326 _private member_ `FAlignedFloatBuffer WorkBuffer;`
- L327 _private member_ `FMeanSquaredIIR MeanSquaredProcessor;`
- L328 _private member_ `FTruePeak TruePeakProcessor;`
- L329 _private member_ `FAttackReleaseSmoother Smoother;`
- L331 _private member_ `int32 NumChannels;`
- L332 _private member_ `EPeakMode::Type EnvMode;`

#### struct `Audio::FInlineEnvelopeFollowerInitParams`  
`struct FInlineEnvelopeFollowerInitParams`  
_L335-349_
- L338 _public member_ `float SampleRate = 48000.f;` — Number of frames per a second.
- L340 _public member_ `float AttackTimeMsec = 10.0f;` — The desired attack time in milliseconds.
- L342 _public member_ `float ReleaseTimeMsec = 100.0f;` — The desired release time in milliseconds.
- L344 _public member_ `EPeakMode::Type Mode = EPeakMode::Peak;` — Technique for measuring amplitude of input signal.
- L346 _public member_ `bool bIsAnalog = true;` — Whether to model analog RC circuits or use digital models.
- L348 _public member_ `float AnalysisWindowMsec=5.f;` — Number of milliseconds per a (root) mean squared window.

#### class `Audio::FInlineEnvelopeFollower`  
`class FInlineEnvelopeFollower : public FAttackRelease`  
_L355-550_
- inherits: `FAttackRelease`
- desc: FInlineEnvelopeFollower is useful for low sample rate use cases and where samples are only available one at a time. This class is inlined because there are situations where it is needed in a CPU intensive situations.
- L361 _public function_ `FInlineEnvelopeFollower(const FInlineEnvelopeFollowerInitParams& InParams) : FAttackRelease(InParams.SampleRate, InParams.AttackTimeMsec, InParams.ReleaseTimeMsec, InParams.bIsAnalog) , Value(0.f) , Mode((InParams.Mode != EPeakMode::TruePeak) ? InParams.Mode : EPeakMode::Peak) , AnalysisValue(0.f) , AnalysisWindowMsec(5.f)` — Construct an envelope follower.
- L372 _public function_ `FInlineEnvelopeFollower() : FInlineEnvelopeFollower(FInlineEnvelopeFollowerInitParams{})`
- L378 _public function_ `void Init(const FInlineEnvelopeFollowerInitParams& InParams)` — Initialize an envelope follower.
- L390 _public function_ `void SetMode(EPeakMode::Type InMode)` — Sets the input analysis mode of the envelope follower
- L399 _public function_ `void SetAnalysisWindow(float InAnalysisWindowMsec)` — Set the analysis window size (for MeanSquared and RootMeanSquared).
- L409 _public function_ `inline float ProcessSample(float InSample)` — Process a single sample and return the envelope value.
- L426 _public function_ `inline void ProcessBuffer(const float* InSamples, const int32 InNumSamples, float* OutSamples)`
- L448 _public function_ `void Reset()`
- L454 _public function_ `inline float GetValue() const` — Return the most recent envelope value.
- L460 _private function_ `inline float NormalizeSample(float InSample)`
- L493 _private function_ `inline void NormalizeSamples(const float* InSamples, const int32 InNumSamples, float* OutSamples)`
- L535 _private function_ `void InitMeanSquaredCoefficients(float InWinMsec, float InSampleRate)`
- L544 _private member_ `float Value = 0.f;`
- L545 _private member_ `EPeakMode::Type Mode = EPeakMode::Peak;`
- L546 _private member_ `float AnalysisValue = 0.f;`
- L547 _private member_ `float AnalysisWindowMsec = 10.f;`
- L548 _private member_ `float AnalysisFilterAlpha = 0.f;`
- L549 _private member_ `float AnalysisFilterBeta = 1.f;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Audio`
- L14 _namespace_ `namespace EPeakMode` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/EventQuantizer.h` (Public)


#### enum `Audio::EEventQuantization`  
`enum class EEventQuantization : uint8`  
_L9-27_
- L11 _public enumerator_ `None`
- L12 _public enumerator_ `Bars8`
- L13 _public enumerator_ `Bars4`
- L14 _public enumerator_ `Bars2`
- L15 _public enumerator_ `Bar`
- L16 _public enumerator_ `HalfNote`
- L17 _public enumerator_ `HalfNoteTriplet`
- L18 _public enumerator_ `QuarterNote`
- L19 _public enumerator_ `QuarterNoteTriplet`
- L20 _public enumerator_ `EighthNote`
- L21 _public enumerator_ `EighthNoteTriplet`
- L22 _public enumerator_ `SixteenthNote`
- L23 _public enumerator_ `SixteenthNoteTriplet`
- L24 _public enumerator_ `ThirtySecondNote`
- L26 _public enumerator_ `Count`

#### struct `Audio::FEventQuantizationSettings`  
`struct FEventQuantizationSettings`  
_L29-57_
- L32 _public member_ `uint32 SampleRate;` — The sample rate (in frames per second) of the output audio buffer
- L35 _public member_ `uint32 NumChannels;` — Number of channels in the output audio buffer
- L38 _public member_ `float BeatsPerMinute;` — The beats per minute
- L41 _public member_ `uint32 BeatsPerBar;` — The beats per bar
- L44 _public member_ `EEventQuantization GlobalQuantization;` — What the "global" quantization setting is
- L47 _public member_ `uint16 BeatDivision;` — The beat division (must be power of 2)
- L49 _public function_ `FEventQuantizationSettings() : SampleRate(0.0f) , NumChannels(2) , BeatsPerMinute(90.0f) , BeatsPerBar(4) , GlobalQuantization(EEventQuantization::Bar) , BeatDivision(4)`

#### class `Audio::IQuantizedEventListener`  
`class IQuantizedEventListener`  
_L62-71_
- desc: Event listener interface. Event listeners make callbacks to objects that are interested in specific events. Can be hooked to non-audio systems to trigger BP delegates, animation triggering, etc. Note: this event listener is called from the audio render thread (or async audio rendering/generation task).
- L70 _public prototype_ `virtual void OnEvent(EEventQuantization EventQuantizationType, int32 Bars, float Beat) = 0;` — Callback for when a specific event type occurs. Listeners register themselves for specific events. But will get the same callback called. I.e. same object can register for multiple events. @param EventQuantizationType			The event type that just happened @param Bars							The number of bars in that this event happened @param Beat							The beat within the bar that the event happened (can be fractional for sub-division events)

#### class `Audio::FEventQuantizer`  
`class FEventQuantizer`  
_L74-165_
- desc: Class which handles the details of event quantization.
- L77 _public prototype_ `FEventQuantizer();`
- L78 _public prototype_ `~FEventQuantizer();`
- L81 _public prototype_ `void SetQuantizationSettings(const FEventQuantizationSettings& QuantizationSettings);` — Sets the quantization settings for the event quantizer
- L82 _public function_ `const FEventQuantizationSettings& GetQuantizationSettings() const`
- L85 _public prototype_ `void SetBPM(const float InBPM);` — Allows continuous control over BPM for the event quantizer
- L86 _public function_ `float GetBPM() const`
- L89 _public prototype_ `void SetBeatDivision(const uint16 InBeatDivision);` — Set the beat division
- L90 _public function_ `uint16 GetBeatDivision() const`
- L92 _public prototype_ `float GetPlaybacktimeSeconds() const;`
- L94 _public prototype_ `uint32 GetDurationInFrames(int32 NumBars, float NumBeats) const;`
- L98 _public prototype_ `void NotifyEvents(int32 NumFrames);` — Called to perform notifications for any events which happen in the next given number of frames. This function should be called in an audio buffer render callback.
- L101 _public prototype_ `void EnqueueEvent(EEventQuantization InQuantization, TFunction<void(uint32 NumFramesOffset)> Lambda);` — Enqueues a quantized event
- L104 _public prototype_ `void RegisterListenerForEvent(IQuantizedEventListener* InListener, EEventQuantization InQuantization);` — Register event listener for specific events
- L107 _public prototype_ `void UnregisterListenerForEvent(IQuantizedEventListener* InListener);` — Unregisters the event listener for all quantization events
- L110 _public prototype_ `void UnregisterListenerForEvent(IQuantizedEventListener* InListener, EEventQuantization InQuantization);` — Unregister the event listener for specific quantization event
- L114 _private prototype_ `void SetQuantizationSettingsInternal(const FEventQuantizationSettings& QuantizationSettings);`
- L115 _private prototype_ `void SetBPMInternal(const float InBPM);`
- L116 _private prototype_ `void ResetEventState();`
- L139 _private prototype_ `void NotifyEventForState(FEventQuantizationState& State, EEventQuantization Type, bool bIsQuantizationEvent, int32 NumFrames);`
- L142 _private member_ `uint32 FrameCount;` — The frame count of the whole event quantizer since it started. Passed to listeners.
- L143 _private member_ `uint32 NumFramesPerBar;`
- L144 _private member_ `uint32 NumFramesPerBeat;`
- L147 _private member_ `TArray<TFunction<void(uint32 NumFramesOffset)>> CopiedEvents;` — Scratch buffer for copied events
- L150 _private member_ `FEventQuantizationSettings QuantizationSettings;` — The quantization settings of the event quantizer
- L151 _private member_ `EEventQuantization EventQuantizationForSettingsChange;`
- L155 _private member_ `FEventQuantizationState EventQuantizationStates[(int32)EEventQuantization::Count];` — Array of quantization states, one for each quantization type Zero'th index is reserved for pending quantization events
- L158 _private member_ `FEventQuantizationState BPMQuantizationState;` — Quantization state used for quantizing BPM changes
- L161 _private member_ `bool bQuantizationSettingsSet;` — Whether or not we've set the quantization settings
- L164 _private member_ `bool bResetEventState;` — Whether or not to reset pending event states. Set after quantization settings have changed.

#### struct `Audio::FEventQuantizer::FEventQuantizationState`  
`struct FEventQuantizationState`  
_L119-137_
- desc: Struct for defining and hold quantization timing state
- L122 _public member_ `uint32 FrameCount;` — The current frame count of this quantization type
- L125 _public member_ `uint32 EventFrameDuration;` — The frame duration of this quantization type (how many frames for the event to reoccur)
- L128 _public member_ `TArray<TFunction<void(uint32 NumFramesOffset)>> QueuedEvents;` — Array of events queued for this state
- L131 _public member_ `TArray<IQuantizedEventListener*> EventListeners;` — Event listeners for this specific event
- L133 _public function_ `FEventQuantizationState() : FrameCount(0) , EventFrameDuration(INDEX_NONE)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/FFTAlgorithm.h` (Public)


#### enum `Audio::EFFTScaling`  
`enum class EFFTScaling : uint8`  
_L17-33_
- desc: EFFTScaling EFFTScaling describes how transformed data is scaled. IFFTAlgorithm implementations must return this value to describe how to achieve equal energy between input data and transformed data. It is assumed that applying the logical inverse of the scaling will produce equal energy.
- L20 _public enumerator_ `None` — No scaling needed to maintain equal energy.
- L23 _public enumerator_ `MultipliedByFFTSize` — Output is effectively multiplied by FFTSize. To maintain equal energy, output must be divided by the FFTSize.
- L26 _public enumerator_ `MultipliedBySqrtFFTSize` — Output is effectively multiplied by the square root of the FFTSize. To maintain equal energy, output must be divided by the square root of the FFTSize.
- L29 _public enumerator_ `DividedByFFTSize` — Output is effectively divided by the square root of the FFTSize. To maintain equal energy, output must be multiplied by the square root of the FFTSize.
- L32 _public enumerator_ `DividedBySqrtFFTSize` — Output is effectively divided by the square root of the FFTSize. To maintain equal energy, output must be multiplied by the square root of the FFTSize.

#### struct `Audio::FFFTSettings`  
`struct FFFTSettings`  
_L39-49_
- desc: FFFTSettings Settings for creating an IFFTAlgorithm.
- L42 _public member_ `int32 Log2Size;` — Log2Size of FFT algorithm.
- L45 _public member_ `bool bArrays128BitAligned;` — If true, the algorithm expects input & ouput arrays to be 128bit aligned.
- L48 _public member_ `bool bEnableHardwareAcceleration;` — If true, hardware accelerated algorithms are valid.

#### class `Audio::IFFTAlgorithm`  
`class IFFTAlgorithm`  
_L55-114_
- desc: IFFTAlgorithm Interface for FFT algorithm.
- L59 _public prototype_ `virtual ~IFFTAlgorithm();` — virtual destructor for inheritance.
- L62 _public prototype_ `virtual int32 Size() const = 0;` — Number of elements in FFT
- L65 _public function_ `int32 NumInputFloats() const` — Number of floats expected in input.
- L68 _public function_ `int32 NumOutputFloats() const` — Number of floats produced in output.
- L71 _public prototype_ `virtual EFFTScaling ForwardScaling() const = 0;` — Scaling applied when performing forward FFT.
- L74 _public prototype_ `virtual EFFTScaling InverseScaling() const = 0;` — Scaling applied when performing inverse FFT.
- L84 _public prototype_ `virtual void ForwardRealToComplex(const float* RESTRICT InReal, float* RESTRICT OutComplex) = 0;` — ForwardRealToComplex Perform the forward FFT on real data and produce complex data. @param InReal - Array of floats to input into fourier transform. Must have NumInputFloats() elements. @param OutComplex - Array of floats to store output of fourier transform. Must have NumOutputFloats() elements which represent (NumOutputFloats() / 2) complex numbers in interleaved format.
- L93 _public prototype_ `virtual void InverseComplexToReal(const float* RESTRICT InComplex, float* RESTRICT OutReal) = 0;` — InverseComplexToReal Perform the inverse FFT on complex data and produce real data. @param InComplex - Array of floats to input into inverse fourier transform. Must have NumOutputFloats() elements which represent complex numbers in interleaved format. @param OutReal - Array of floats to store output of inverse fourier transform. Must have NumInputFloats() elements.
- L103 _public prototype_ `virtual void BatchForwardRealToComplex(int32 InCount, const float* const RESTRICT InReal[], float* RESTRICT OutComplex[]) = 0;` — BatchForwardRealToComplex Perform the forward FFT on real data and produce complex data. @param InCount - The number of transforms to compute. @param InReal - Array of array of floats to input into fourier transform. Must have InCount elements, each containing NumInputFloats() elements. @param OutComplex - Array of array of floats to store output of fourier transform. Must have InCount elements, each with NumOutputFloats()elements which represent complex numbers in interleaved format.
- L113 _public prototype_ `virtual void BatchInverseComplexToReal(int32 InCount, const float* const RESTRICT InComplex[], float* RESTRICT OutReal[]) = 0;` — BatchInverseComplexToReal Perform the inverse FFT on complex data and produce real data. @param InCount - The number of transforms to compute. @param InComplex - Array of array of floats to input into inverse fourier transform. Must have InCount elements, each with NumOutputFloats() elements which represent complex numbers in interleaved format. @param OutReal - Array of array of floats to store output of inverse fourier transform. Must have InCount elements, each with NumInputFloats() elements.

#### class `Audio::IFFTAlgorithmFactory`  
`class IFFTAlgorithmFactory : public IModularFeature`  
_L120-142_
- inherits: `IModularFeature`
- desc: IFFTAlgorithmFactory Factory interface for creating fft algorithms.
- L123 _public prototype_ `virtual ~IFFTAlgorithmFactory() = default;`
- L126 _public prototype_ `static const FName GetModularFeatureName();` — Name of modular feature for FFT factory.
- L129 _public prototype_ `virtual FName GetFactoryName() const = 0;` — Name of this particular factory.
- L132 _public prototype_ `virtual bool IsHardwareAccelerated() const = 0;` — If true, this implementation uses hardware acceleration.
- L135 _public prototype_ `virtual bool Expects128BitAlignedArrays() const = 0;` — If true, this implementation requires input and output arrays to be 128 bit aligned.
- L138 _public prototype_ `virtual bool AreFFTSettingsSupported(const FFFTSettings& InSettings) const = 0;` — Returns true if the input settings are supported by this factory.
- L141 _public prototype_ `virtual TUniquePtr<IFFTAlgorithm> NewFFTAlgorithm(const FFFTSettings& InSettings) = 0;` — Creates a new FFT algorithm.

#### class `Audio::FFFTFactory`  
`class FFFTFactory`  
_L148-173_
- desc: FFFTFactory FFFTFactory creates fft algorithms. It will choose hardware accelerated versions of the FFT when they are available.
- L152 _public member_ `static const FName AnyAlgorithmFactory;` — This denotes that no specific IFFTAlgorithmFactory is desired.
- L162 _public prototype_ `static TUniquePtr<IFFTAlgorithm> NewFFTAlgorithm(const FFFTSettings& InSettings, const FName& InAlgorithmFactoryName = AnyAlgorithmFactory);` — NewFFTAlgorithm Creates and returns a new FFTAlgorithm. @param InSettings - The settings used to create the FFT algorithm. @param InAlgorithmFactoryName - If not equal to FFFTFactory::AnyAlgorithmFactory, will only uses FFT algorithm facotry if IFFTAlgorithmFactory::GetFactoryName() equals InAlgorithmFactoryName. @return A TUniquePtr<IFFTAlgorithm> to the created FFT. This pointer can be invalid if an error occured or the fft algorithm could not be created.
- L172 _public prototype_ `static bool AreFFTSettingsSupported(const FFFTSettings& InSettings, const FName& InAlgorithmFactoryName = AnyAlgorithmFactory);` — AreFFTSettingsSupported Returns true if a valid FFT algorithm can be created which satifies the given settings. @param InSettings - Settings describing desired FFT algorithm. @param InAlgorithmFactoryName - If not equal to FFFTFactory::AnyAlgorithmFactory, will only uses FFT algorithm facotry if IFFTAlgorithmFactory::GetFactoryName() equals InAlgorithmFactoryName. @return True if settings are supported. Otherwise false.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/FeedbackDelayNetwork.h` (Public)


#### struct `Audio::FFDNDelaySettings`  
`struct FFDNDelaySettings`  
_L14-29_
- desc: Delay settings of 4 channel feedback delay network
- L17 _public member_ `int32 APF0DelayNumSamples;` — Number of samples for delay line 0
- L19 _public member_ `int32 APF1DelayNumSamples;` — Number of samples for delay line 1
- L21 _public member_ `int32 APF2DelayNumSamples;` — Number of samples for delay line 2
- L23 _public member_ `int32 APF3DelayNumSamples;` — Number of samples for delay line 3
- L26 _public prototype_ `static FFDNDelaySettings DefaultLeftDelays(float InSampleRate);` — Default delay line settings for left channel.
- L28 _public prototype_ `static FFDNDelaySettings DefaultRightDelays(float InSampleRate);` — Default delay line settings for right channel.

#### struct `Audio::FFDNCoefficients`  
`struct FFDNCoefficients`  
_L32-44_
- desc: Filter coefficients of 4 channel feedback delay network.
- L35 _public member_ `float InputScale;` — Sample multiplier of input samples before they enter the delay line.
- L37 _public member_ `float APFG[4];` — All pass filter coefficients. One coefficient for each filter.
- L39 _public member_ `float LPFA[4];` — Low pass filter feed back coefficients. One coefficient for each filter.
- L41 _public member_ `float LPFB[4];` — Low pass filter feed forward coefficients. One coefficient for each filter.
- L43 _public member_ `float Feedback;` — Feedback multiplier of mixing matrix output to network input.

#### class `Audio::FFeedbackDelayNetwork`  
`class FFeedbackDelayNetwork`  
_L47-97_
- desc: 4 channel feedback delay network (FDN) for artificial reverberation.
- L52 _public prototype_ `FFeedbackDelayNetwork(int32 InMaxNumInternalBufferSamples, const FFDNDelaySettings& InSettings);` — InMaxNumInternalBufferSamples controls the internal buffer size used for vector operations. InSettings controls the delay line lengths.
- L54 _public prototype_ `~FFeedbackDelayNetwork();`
- L57 _public prototype_ `void SetCoefficients(const FFDNCoefficients& InCoefficients);` — Sets the coefficient values of the all pass filters, low pass filters, input scalers and feedback scalers.
- L60 _public prototype_ `void ProcessAudio(const FAlignedFloatBuffer& InSamples, FAlignedFloatBuffer& OutSamples);` — Generates artificial reverberation for InSamples and places results in OutSamples.
- L63 _public prototype_ `void FlushAudio();` — Sets internal audio samples to silence.
- L66 _public prototype_ `int32 GetNumInternalBufferSamples() const;` — Returns the actual number of samples in an internal buffer.
- L72 _private prototype_ `void ProcessAudioBuffer(const float* InSampleData, const int32 InNum, float* OutSampleData);` — Process single internal buffer of audio.
- L74 _private member_ `FFDNDelaySettings Settings;`
- L77 _private member_ `int32 NumInternalBufferSamples;` — Internal buffer size.
- L80 _private member_ `FFDNCoefficients Coefficients;` — Coefficients structure for APF, LPF, input scaling and feedback.
- L83 _private member_ `float LPFZ[4];` — Previous output of low pass filters.
- L86 _private member_ `float FMO[4];` — Previous output of mixing matrix.
- L88 _private member_ `TUniquePtr<FAlignedBlockBuffer> DelayLine0;`
- L89 _private member_ `TUniquePtr<FAlignedBlockBuffer> DelayLine1;`
- L90 _private member_ `TUniquePtr<FAlignedBlockBuffer> DelayLine2;`
- L91 _private member_ `TUniquePtr<FAlignedBlockBuffer> DelayLine3;`
- L93 _private member_ `FAlignedFloatBuffer WorkBuffer0;`
- L94 _private member_ `FAlignedFloatBuffer WorkBuffer1;`
- L95 _private member_ `FAlignedFloatBuffer WorkBuffer2;`
- L96 _private member_ `FAlignedFloatBuffer WorkBuffer3;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/FileEncoder.h` (Public)


#### class `Audio::FAudioFileWriter`  
`class FAudioFileWriter`  
_L11-47_
- L16 _public prototype_ `FAudioFileWriter(const FString& InPath, const FSoundQualityInfo& InInfo);` — Constructor. Takes an absolute file path and metadata about the audio in question. Immediately allocates all data necessary.
- L19 _public prototype_ `~FAudioFileWriter();` — Calling the destructor on this class finalizes and closes out the file.
- L22 _public prototype_ `void GetFileInfo(FSoundQualityInfo& OutInfo);` — Returns file information.
- L27 _public prototype_ `bool PushAudio(const float* InAudio, int32 NumSamples, bool bEncodeIfPossible = true);` — Use this to push audio to the file writer. If you'd like to move encoding and file writing to a separate thread from PushAudio, Call this with bEncodeIfPossible = false.
- L30 _public prototype_ `bool EncodeIfPossible();` — If PushAudio is called with bEncodeIfPossible set to false, this will need to be called.
- L33 _private prototype_ `FAudioFileWriter();`
- L35 _private member_ `FSoundQualityInfo QualityInfo;`
- L36 _private member_ `TArray<uint8> DataBuffer;`
- L39 _private member_ `TUniquePtr<IAudioEncoder> Encoder;` — Compressor we are using.
- L42 _private member_ `TUniquePtr<IFileHandle> FileHandle;` — Handle to file we are writing to.
- L44 _private prototype_ `IAudioEncoder* GetNewEncoderForFile(const FString& InPath);`
- L45 _private prototype_ `FString GetExtensionForFile(const FString& InPath);`
- L46 _private prototype_ `void FlushEncoderToFile(int32 DataBufferSize = 4096);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/Filter.h` (Public)


#### enum `Audio::EBiquadFilter::Type`  
`enum Type`  
_L15-27_
- L17 _public enumerator_ `Lowpass`
- L18 _public enumerator_ `Highpass`
- L19 _public enumerator_ `Bandpass`
- L20 _public enumerator_ `Notch`
- L21 _public enumerator_ `ParametricEQ`
- L22 _public enumerator_ `LowShelf`
- L23 _public enumerator_ `HighShelf`
- L24 _public enumerator_ `AllPass`
- L25 _public enumerator_ `ButterworthLowPass`
- L26 _public enumerator_ `ButterworthHighPass`

#### class `Audio::FBiquadFilter`  
`class FBiquadFilter`  
_L32-111_
- desc: Biquad filter class which wraps a biquad filter struct Handles multi-channel audio to avoid calculating filter coefficients for multiple channels of audio.
- L36 _public prototype_ `FBiquadFilter();` — Constructor
- L38 _public prototype_ `virtual ~FBiquadFilter();` — Destructor
- L41 _public prototype_ `void Init(const float InSampleRate, const int32 InNumChannels, const EBiquadFilter::Type InType, const float InCutoffFrequency = 20000.0f, const float InBandwidth = 2.0f, const float InGain = 0.0f);` — Initialize the filter
- L44 _public prototype_ `int32 GetNumChannels() const;` — Returns number of channels initialized with
- L47 _public prototype_ `void Reset();` — Resets the filter state
- L50 _public prototype_ `void ProcessAudioFrame(const float* InFrame, float* OutFrame);` — Processes a single frame of audio
- L53 _public prototype_ `void ProcessAudio(const float* InBuffer, const int32 InNumSamples, float* OutBuffer);` — Process a mono buffer or an interleaved buffer of multichannel audio
- L56 _public prototype_ `void ProcessAudio(const float* const* InBuffers, const int32 InNumSamples, float* const* OutBuffers);` — Process a non-interleaved buffer of multichannel audio
- L59 _public prototype_ `void SetParams(const EBiquadFilter::Type InFilterType, const float InCutoffFrequency, const float InBandwidth, const float InGainDB);` — Sets all filter parameters with one function
- L62 _public prototype_ `void SetType(const EBiquadFilter::Type InType);` — Sets the type of the filter to use
- L65 _public prototype_ `void SetFrequency(const float InCutoffFrequency);` — Sets the filter frequency
- L68 _public prototype_ `void SetBandwidth(const float InBandwidth);` — Sets the bandwidth (octaves) of the filter
- L71 _public prototype_ `void SetGainDB(const float InGainDB);` — Sets the gain of the filter in decibels
- L74 _public prototype_ `void SetEnabled(const bool bInEnabled);` — Sets whether or no this filter is enabled (if disabled audio is passed through)
- L77 _public prototype_ `void ArrayCalculateResponseInPlace(TArrayView<float> InOutComplexValues) const;` — Apply the filter transfer function to each z-domain value in the given array (complex numbers given as interleaved floats). Passing in z-domain values on the complex unit circle will give the frequency response.
- L83 _protected prototype_ `void CalculateBiquadCoefficients();` — Function computes biquad coefficients based on current filter settings
- L86 _protected prototype_ `float ClampCutoffFrequency(float InCutoffFrequency);` — Function used to clamp the cutoff frequency.
- L89 _protected member_ `EBiquadFilter::Type FilterType;` — What kind of filter to use when computing coefficients
- L92 _protected member_ `FBiquadCoeff* Biquad;` — Biquad filter objects for each channel
- L95 _protected member_ `float SampleRate;` — The sample rate of the filter
- L98 _protected member_ `int32 NumChannels;` — Number of channels in the filter
- L101 _protected member_ `float Frequency;` — Current frequency of the filter
- L104 _protected member_ `float Bandwidth;` — Current bandwidth/resonance of the filter
- L107 _protected member_ `float GainDB;` — The gain of the filter in DB (for filters that use gain)
- L110 _protected member_ `bool bEnabled;` — Whether or not this filter is enabled (will bypass otherwise)

#### enum `Audio::EFilter::Type`  
`enum Type`  
_L115-123_
- L117 _public enumerator_ `LowPass`
- L118 _public enumerator_ `HighPass`
- L119 _public enumerator_ `BandPass`
- L120 _public enumerator_ `BandStop`
- L122 _public enumerator_ `NumFilterTypes`

#### class `Audio::IFilter`  
`class IFilter`  
_L129-238_
- desc: Base class for filters usable in synthesis
- L132 _public prototype_ `IFilter();`
- L133 _public prototype_ `IFilter(const IFilter&);`
- L134 _public prototype_ `virtual ~IFilter();`
- L137 _public prototype_ `virtual void Init(const float InSampleRate, const int32 InNumChannels, const int32 InVoiceId, FModulationMatrix* InModMatrix = nullptr);` — Initialize the filter
- L140 _public prototype_ `virtual void SetFrequency(const float InCutoffFrequency);` — Sets the cutoff frequency of the filter.
- L143 _public prototype_ `virtual void SetFrequencyMod(const float InModFrequency);` — Sets an external modulated frequency
- L146 _public prototype_ `virtual void SetQ(const float InQ);` — Sets the quality/resonance of the filter
- L149 _public prototype_ `virtual void SetQMod(const float InModQ);` — Sets an external modulated quality/resonance of the filter
- L152 _public function_ `virtual void SetSaturation(const float InSaturation)` — Sets the filter saturation (not used on all filters)
- L155 _public function_ `virtual void SetBandStopControl(const float InBandStop)` — Sets the band stop control param (not used on all filters)
- L158 _public function_ `virtual void SetPassBandGainCompensation(const float InPassBandGainCompensation)` — Sets the band pass gain compensation (not used on all filters)
- L161 _public prototype_ `virtual void SetFilterType(const EFilter::Type InFilterType);` — Sets the filter type
- L164 _public prototype_ `virtual void Reset();` — Reset the filter
- L167 _public prototype_ `virtual void Update();` — Updates the filter
- L170 _public function_ `virtual void ProcessAudioFrame(const float* InFrame, float* OutFrame)` — Processes a single frame of audio. Number of channels MUST be what was used during filter initialization.
- L176 _public prototype_ `virtual void ProcessAudio(const float* InBuffer, const int32 InNumSamples, float* OutBuffer) = 0;` — Process a mono buffer or an interleaved buffer of multichannel audio
- L179 _public prototype_ `virtual void ProcessAudio(const float* const* InBuffers, const int32 InNumSamples, float* const* OutBuffers) = 0;` — Process a non-interleaved buffer of multichannel audio
- L182 _public function_ `FPatchDestination GetModDestCutoffFrequency() const` — Filter patch destinations
- L183 _public function_ `FPatchDestination GetModDestQ() const`
- L187 _protected function_ `inline float GetGCoefficient() const`
- L196 _protected member_ `int32 VoiceId;` — The voice id of the owner of the filter (for use with mod matrix)
- L199 _protected member_ `float SampleRate;` — Sample rate of the filter
- L202 _protected member_ `int32 NumChannels;` — Number of channels of the sound
- L205 _protected member_ `float Frequency;` — The cutoff frequency currently used by the filter (can be modulated)
- L208 _protected member_ `float BaseFrequency;` — The base filter cutoff frequency
- L211 _protected member_ `float ModFrequency;` — A modulated frequency
- L214 _protected member_ `float ExternalModFrequency;` — A modulatied frequency driven externally
- L217 _protected member_ `float Q;` — The current Q
- L220 _protected member_ `float ModQ;` — The modulated Q
- L223 _protected member_ `float BaseQ;` — The base
- L226 _protected member_ `float ExternalModQ;` — An external modulation of Q
- L229 _protected member_ `EFilter::Type FilterType;` — The filter type of the filter
- L231 _protected member_ `FModulationMatrix* ModMatrix;`
- L234 _protected member_ `FPatchDestination ModCutoffFrequencyDest;` — Mod matrix patchable destinations
- L235 _protected member_ `FPatchDestination ModQDest;`
- L237 _protected member_ `bool bChanged;`

#### class `Audio::FOnePoleFilter`  
`class FOnePoleFilter : public IFilter`  
_L242-268_
- inherits: `IFilter`
- desc: A virtual analog one-pole filter. Defaults to a low-pass mode, but can be switched to high-pass
- L245 _public prototype_ `FOnePoleFilter();`
- L246 _public prototype_ `virtual ~FOnePoleFilter();`
- L248 _public prototype_ `virtual void Init(const float InSampleRate, const int32 InNumChannels, const int32 InVoiceId = 0, FModulationMatrix* InModMatrix = nullptr) override;`
- L249 _public prototype_ `virtual void Reset() override;`
- L250 _public prototype_ `virtual void Update() override;`
- L251 _public prototype_ `virtual void ProcessAudioFrame(const float* InFrame, float* OutFrame) override;`
- L253 _public prototype_ `virtual void ProcessAudio(const float* InSamples, const int32 InNumSamples, float* OutSamples) override;` — Process a mono buffer or an interleaved buffer of multichannel audio
- L255 _public prototype_ `virtual void ProcessAudio(const float* const* InBuffers, const int32 InNumSamples, float* const* OutBuffers) override;` — Process a non-interleaved buffer of multichannel audio
- L257 _public function_ `void SetCoefficient(const float InCoefficient)`
- L258 _public function_ `float GetCoefficient() const`
- L260 _public function_ `float GetState(const int32 InChannel) const`
- L263 _public prototype_ `void ArrayCalculateResponseInPlace(TArrayView<float> InOutComplexValues) const;` — Apply the filter transfer function to each z-domain value in the given array (complex numbers given as interleaved floats). Passing in z-domain values on the complex unit circle will give the frequency response.
- L266 _protected member_ `float A0;`
- L267 _protected member_ `float* Z1;`

#### class `Audio::FStateVariableFilter`  
`class FStateVariableFilter : public IFilter`  
_L270-314_
- inherits: `IFilter`
- L273 _public prototype_ `FStateVariableFilter();`
- L274 _public prototype_ `virtual ~FStateVariableFilter();`
- L276 _public prototype_ `virtual void Init(const float InSampleRate, const int32 InNumChannels, const int32 InVoiceId = 0, FModulationMatrix* InModMatrix = nullptr) override;`
- L277 _public prototype_ `virtual void SetBandStopControl(const float InBandStop) override;`
- L278 _public prototype_ `virtual void Reset() override;`
- L279 _public prototype_ `virtual void Update() override;`
- L281 _public prototype_ `virtual void ProcessAudio(const float* InSamples, const int32 InNumSamples, float* OutSamples) override;` — Process a mono buffer or an interleaved buffer of multichannel audio
- L283 _public prototype_ `virtual void ProcessAudio(const float* const* InBuffers, const int32 InNumSamples, float* const* OutBuffers) override;` — Process a non-interleaved buffer of multichannel audio
- L286 _public prototype_ `void ProcessAudio(const float* InSamples, const int32 InNumSamples, float* LpfOutput, float* HpfOutput, float* BpfOutput, float* BsfOutput);` — Process a mono buffer or an interleaved buffer of multichannel audio
- L289 _public prototype_ `void ProcessAudio(const float* const* InBuffers, const int32 InNumSamples, float* const* LpfOutBuffers, float* const* HpfOutBuffers, float* const* BpfOutBuffers, float* const* BsfOutBuffers);` — Process a non-interleaved buffer of multichannel audio
- L294 _public prototype_ `void ArrayCalculateResponseInPlace(TArrayView<float> InOutComplexValues) const;` — Apply the filter transfer function to each z-domain value in the given array (complex numbers given as interleaved floats). Passing in z-domain values on the complex unit circle will give the frequency response. The transfer function utilized here represents the behavior of the filter if the non-linearity were removed.
- L297 _protected member_ `float InputScale;`
- L298 _protected member_ `float A0;`
- L299 _protected member_ `float Feedback;`
- L300 _protected member_ `float BandStopParam;`
- L313 _protected member_ `TArray<FFilterState> FilterState;`

#### struct `Audio::FStateVariableFilter::FFilterState`  
`struct FFilterState`  
_L302-311_
- L304 _public member_ `float Z1_1;`
- L305 _public member_ `float Z1_2;`
- L307 _public function_ `FFilterState() : Z1_1(0.0f) , Z1_2(0.0f)`

#### class `Audio::FLadderFilter`  
`class FLadderFilter : public IFilter`  
_L316-348_
- inherits: `IFilter`
- L319 _public prototype_ `FLadderFilter();`
- L320 _public prototype_ `virtual ~FLadderFilter();`
- L322 _public prototype_ `virtual void Init(const float InSampleRate, const int32 InNumChannels, const int32 InVoiceId = 0, FModulationMatrix* InModMatrix = nullptr) override;`
- L323 _public prototype_ `virtual void Reset() override;`
- L324 _public prototype_ `virtual void Update() override;`
- L325 _public prototype_ `virtual void SetQ(const float InQ) override;`
- L326 _public prototype_ `virtual void SetPassBandGainCompensation(const float InPassBandGainCompensation) override;`
- L329 _public prototype_ `virtual void ProcessAudio(const float* InSamples, const int32 InNumSamples, float* OutSamples) override;` — Process a mono buffer or an interleaved buffer of multichannel audio
- L332 _public prototype_ `virtual void ProcessAudio(const float* const* InBuffers, const int32 InNumSamples, float* const* OutBuffers) override;` — Process a non-interleaved buffer of multichannel audio
- L336 _public prototype_ `void ArrayCalculateResponseInPlace(TArrayView<float> InOutComplexValues) const;` — Apply the filter transfer function to each z-domain value in the given array (complex numbers given as interleaved floats). Passing in z-domain values on the complex unit circle will give the frequency response. The transfer function utilized here represents the behavior of the filter if the non-linearity were removed.
- L341 _protected member_ `FOnePoleFilter OnePoleFilters[4];` — Ladder filter is made of 4 LPF filters
- L342 _protected member_ `float Beta[4];`
- L343 _protected member_ `float K;`
- L344 _protected member_ `float Gamma;`
- L345 _protected member_ `float Alpha;`
- L346 _protected member_ `float Factors[5];`
- L347 _protected member_ `float PassBandGainCompensation;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`
- L13 _namespace_ `namespace EBiquadFilter` (scope `Audio`)
- L113 _namespace_ `namespace EFilter` (scope `Audio`)
- L126 _variable_ `static const int32 MaxFilterChannels = 8;` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/Flanger.h` (Public)


#### class `Audio::FFlanger`  
`class FFlanger`  
_L11-58_
- L14 _public prototype_ `FFlanger();`
- L15 _public prototype_ `~FFlanger();`
- L17 _public prototype_ `void Init(const float InSampleRate);`
- L19 _public prototype_ `void SetModulationRate(const float InModulationRate);`
- L20 _public prototype_ `void SetModulationDepth(const float InModulationDepth);`
- L21 _public prototype_ `void SetCenterDelay(const float InCenterDelay);`
- L22 _public prototype_ `void SetMixLevel(const float InMixLevel);`
- L24 _public prototype_ `void ProcessAudio(const FAlignedFloatBuffer& InBuffer, const int32 InNumSamples, FAlignedFloatBuffer& OutBuffer);`
- L26 _protected member_ `static const float MaxDelaySec;`
- L27 _protected member_ `static const float MaxModulationRate;`
- L28 _protected member_ `static const float MaxCenterDelay;`
- L32 _protected member_ `float ModulationRate = 0.5f;` — LFO parameters LFO frequency
- L34 _protected member_ `float ModulationDepth = 0.5f;` — Modulation depth is clamped to CenterDelayMsec to avoid clipping
- L35 _protected member_ `float CenterDelayMsec = 0.5f;`
- L41 _protected member_ `float MixLevel = 0.5f;` — Balance between original and delayed signal (Should be between 0 and 1.0; 0.5 is equal amounts of each and > 0.5 is more delayed signal than non-delayed signal)
- L42 _protected member_ `float DelayedSignalLevel = 0.5f;`
- L43 _protected member_ `float NonDelayedSignalLevel = 0.5f;`
- L46 _protected member_ `FDelay DelayBuffer;` — Internal delay buffer
- L48 _protected member_ `FAlignedFloatBuffer ScratchBuffer;` — Scratch buffer used for accumulating delay samples per block
- L51 _protected member_ `float DelaySample = 0.0f;` — Delay sample generated from LFO per block
- L54 _protected member_ `FSinOsc2DRotation LFO;` — Internal LFO for delay amount
- L57 _protected member_ `float SampleRate = 48000.0f;` — The audio sample rate, Init() must be called to initialize this

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/FloatArrayMath.h` (Public)


#### class `Audio::FContiguousSparse2DKernelTransform`  
`class FContiguousSparse2DKernelTransform`  
_L326-386_
- desc: FContiguousSparse2DKernelTransform FContiguousSparse2DKernelTransform applies a matrix transformation to an input array. [OutArray] = [[Kernal]][InView] It provides some optimization by exploit the contiguous and sparse qualities of the kernel rows, which allows it to skip multiplications with the number zero. It works with non-sparse and non-contiguous kernels as well, but will be more computationally expensive than a naive implementation. Also, only takes advantage of sparse contiguous rows, not columns.
- L335 _public prototype_ `FContiguousSparse2DKernelTransform(const FContiguousSparse2DKernelTransform& ) = delete;`
- L336 _public prototype_ `FContiguousSparse2DKernelTransform(const FContiguousSparse2DKernelTransform&& ) = delete;`
- L337 _public prototype_ `FContiguousSparse2DKernelTransform& operator=(const FContiguousSparse2DKernelTransform& ) = delete;`
- L343 _public prototype_ `FContiguousSparse2DKernelTransform(const int32 NumInElements, const int32 NumOutElements);` — NumInElements sets the expected number of input array elements as well as the number of elements in a row. NumOutElements sets the number of output array elements as well as the number or rows.
- L344 _public prototype_ `virtual ~FContiguousSparse2DKernelTransform();`
- L347 _public prototype_ `int32 GetNumInElements() const;` — Returns the required size of the input array
- L350 _public prototype_ `int32 GetNumOutElements() const;` — Returns the size of the output array
- L358 _public prototype_ `void SetRow(const int32 RowIndex, const int32 StartIndex, TArrayView<const float> OffsetValues);` — Set the kernel values for an individual row. RowIndex determines which row is being set. StartIndex denotes the offset into the row where the OffsetValues will be inserted. OffsetValues contains the contiguous chunk of values which represent all the nonzero elements in the row.
- L365 _public prototype_ `void TransformArray(TArrayView<const float> InView, TArray<float>& OutArray) const;` — Transforms the input array given the kernel. InView is the array to be transformed. It must have `NumInElements` number of elements. OutArray is the transformed array. It will have `NumOutElements` number of elements.
- L372 _public prototype_ `void TransformArray(TArrayView<const float> InView, FAlignedFloatBuffer& OutArray) const;` — Transforms the input array given the kernel. InView is the array to be transformed. It must have `NumInElements` number of elements. OutArray is the transformed array. It will have `NumOutElements` number of elements.
- L379 _public prototype_ `void TransformArray(const float* InArray, float* OutArray) const;` — Transforms the input array given the kernel. InArray is the array to be transformed. It must have `NumInElements` number of elements. OutArray is the transformed array. It must be allocated to hold at least NumOutElements.
- L383 _private member_ `int32 NumIn;`
- L384 _private member_ `int32 NumOut;`
- L385 _private member_ `TArray<FRow> Kernel;`

#### struct `Audio::FContiguousSparse2DKernelTransform::FRow`  
`struct FRow`  
_L328-332_
- L330 _public member_ `int32 StartIndex = 0;`
- L331 _public member_ `TArray<float> OffsetValues;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
- L11 _prototype_ `void ArraySum(TArrayView<const float> InValues, float& OutSum);` (scope `Audio`) — Sum all values in an array.
- L14 _prototype_ `void ArraySum(TArrayView<const float> InFloatBuffer1, TArrayView<const float> InFloatBuffer2, TArrayView<float> OutputBuffer);` (scope `Audio`) — Sums two buffers together and places the result in the resulting buffer.
- L21 _prototype_ `void ArrayCumulativeSum(TArrayView<const float> InView, TArray<float>& OutData);` (scope `Audio`) — Cumulative sum of array. InView contains data to be cumulatively summed. OutData contains sum and is same size as InView.
- L28 _prototype_ `void ArrayMean(TArrayView<const float> InView, float& OutMean);` (scope `Audio`) — Mean of array. Equivalent to Sum(InView) / InView.Num() InView contains data to be analyzed. OutMean contains the result.
- L35 _prototype_ `void ArrayMeanSquared(TArrayView<const float> InView, float& OutMean);` (scope `Audio`) — Mean Squared of array. Equivalent to Sum(InView * InView) / InView.Num() InArray contains data to be analyzed. OutMean contains the result.
- L38 _prototype_ `float ArrayGetMagnitude(TArrayView<const float> Buffer);` (scope `Audio`) — Takes an audio buffer and returns the magnitude across that buffer.
- L41 _prototype_ `float ArrayGetAverageValue(TArrayView<const float> Buffer);` (scope `Audio`) — Takes an audio buffer and gets the average amplitude across that buffer.
- L44 _prototype_ `float ArrayGetAverageAbsValue(TArrayView<const float> Buffer);` (scope `Audio`) — Takes an audio buffer and gets the average absolute amplitude across that buffer.
- L56 _prototype_ `void ArrayMeanFilter(TArrayView<const float> InView, int32 WindowSize, int32 WindowOrigin, TArray<float>& OutData);` (scope `Audio`) — Mean filter of array. Note: Uses standard biased mean estimator of Sum(x) / Count(x). Note: At array boundaries, this algorithm truncates windows where no valid array data exists. Values calculated with truncated windows have corresponding increased variances. InView contains data to be filtered. WindowSize determines the number of samples from InView analyzed to produce a value in OutData. WindowOrigin describes the offset from the windows first sample to the index of OutData. For example, if WindowOrigin = WindowSize/4, then OutData[i] = Mean(InView[i - Window/4 : i + 3 * Window / 4]). OutData contains the produceds data.
- L67 _prototype_ `void ArrayMaxFilter(TArrayView<const float> InView, int32 WindowSize, int32 WindowOrigin, TArray<float>& OutData);` (scope `Audio`) — Max filter of array. Note: At array boundaries, this algorithm truncates windows where no valid array data exists. InView contains data to be filtered. WindowSize determines the number of samples from InView analyzed to produce a value in OutData. WindowOrigin describes the offset from the windows first sample to the index of OutData. For example, if WindowOrigin = WindowSize/4, then OutData[i] = Max(InView[i - Window/4 : i + 3 * Window / 4]). OutData contains the produceds data.
- L70 _prototype_ `void ArrayGetEuclideanNorm(TArrayView<const float> InView, float& OutEuclideanNorm);` (scope `Audio`) — Computes the EuclideanNorm of the InView. Same as calculating the energy in window.
- L73 _prototype_ `void ArrayAbs(TArrayView<const float> InBuffer, TArrayView<float> OutBuffer);` (scope `Audio`) — Absolute value of array elements
- L79 _prototype_ `void ArrayAbsInPlace(TArrayView<float> InBuffer);` (scope `Audio`) — Absolute value of array elements in place. InBuffer contains the data to be manipulated.
- L86 _prototype_ `void ArrayClampMinInPlace(TArrayView<float> InView, float InMin);` (scope `Audio`) — Clamp minimum value of array in place. InView contains data to be clamped. InMin contains the minimum value allowable in InView.
- L93 _prototype_ `void ArrayClampMaxInPlace(TArrayView<float> InView, float InMax);` (scope `Audio`) — Clamp maximum value of array in place. InView contains data to be clamped. InMax contains the maximum value allowable in InView.
- L101 _prototype_ `void ArrayClampInPlace(TArrayView<float> InView, float InMin, float InMax);` (scope `Audio`) — Clamp values in an array. InView is a view of a float array to be clamped. InMin is the minimum value allowable in the array. InMax is the maximum value allowable in the array.
- L108 _prototype_ `void ArrayMinMaxNormalize(TArrayView<const float> InView, TArray<float>& OutArray);` (scope `Audio`) — Scale an array so the minimum is 0 and the maximum is 1 InView is the view of a float array with the input data. OutArray is an array which will hold the normalized data.
- L112 _prototype_ `void ArrayMax(const TArrayView<const float>& InView1, const TArrayView<const float>& InView2, const TArrayView<float>& OutView);` (scope `Audio`) — Element-wise Max
- L117 _prototype_ `float ArrayMaxAbsValue(const TArrayView<const float> InView);` (scope `Audio`) — Returns the largest value of an array irrespective of sign (ex. {-3, 2, 1} would return 3). InView is a view of a float array to get the largest absolute value from.
- L120 _prototype_ `void ArrayMultiply(TArrayView<const float> InFloatBufferA, TArrayView<const float> InFloatBufferB, TArrayView<float> OutBuffer);` (scope `Audio`) — Multiply the second buffer by the first buffer.
- L123 _prototype_ `void ArrayMultiplyInPlace(TArrayView<const float> InFloatBuffer, TArrayView<float> BufferToMultiply);` (scope `Audio`) — Multiply the second buffer in place by the first buffer.
- L129 _prototype_ `void ArrayComplexMultiplyInPlace(TArrayView<const float> InValues1, TArrayView<float> InValues2);` (scope `Audio`) — Multiplies two complex valued arrays element-wise. This assumes elements are in interleaved format [real_0, imag_0, ..., real_N, imag_N] Stores result in InValues2
- L135 _prototype_ `void ArrayComplexMultiplyAdd(TArrayView<const float> InValues1, TArrayView<const float> InValues2, TArrayView<float> OutArray);` (scope `Audio`) — Multiplies two complex valued arrays element-wise. This assumes elements are in interleaved format [real_0, imag_0, ..., real_N, imag_N] Adds result to OutArray
- L138 _prototype_ `void ArrayMultiplyByConstant(TArrayView<const float> InFloatBuffer, float InValue, TArrayView<float> OutFloatBuffer);` (scope `Audio`) — Multiplies the input float buffer with the given value.
- L141 _prototype_ `void ArrayMultiplyByConstantInPlace(TArrayView<float> InOutBuffer, float InGain);` (scope `Audio`) — Similar to ArrayMultiplyByConstant, but performs the multiply in place.
- L148 _prototype_ `void ArrayAddInPlace(TArrayView<const float> InValues, TArrayView<float> InAccumulateValues);` (scope `Audio`) — Add arrays element-wise in place. InAccumulateValues[i] += InValues[i] InValues is the array to add. InAccumulateValues is the array which holds the sum.
- L151 _prototype_ `void ArrayAddConstantInplace(TArrayView<float> InOutBuffer, float InConstant);` (scope `Audio`) — Adds a constant to a buffer (useful for DC offset removal)
- L159 _prototype_ `void ArrayMultiplyAddInPlace(TArrayView<const float> InValues, float InMultiplier, TArrayView<float> InAccumulateValues);` (scope `Audio`) — Multiply Add arrays element-wise in place. InAccumulateValues[i] += InMultiplier * InValues[i] @param InValues - The array to add. @param InMultiplier - The value to multiply against InValues @param InAccumulateValues - The array which holds the sum.
- L169 _prototype_ `void ArrayLerpAddInPlace(TArrayView<const float> InValues, float InStartMultiplier, float InEndMultiplier, TArrayView<float> InAccumulateValues);` (scope `Audio`) — Linearly Interpolate Add arrays element-wise in place. InAccumulateValues[i] += ((1 - alpha) * InStartMultiplier + alpha * InEndMultipler) * InValues[i] Interpolation is performed over the length of the array. @param InValues - The array to add. @param InStartMultiplier - The beginning value to multiply against InValues @param InEndMultiplier - The ending value to multiply against InValues @param InAccumulateValues - The array which holds the sum.
- L177 _prototype_ `void ArraySubtract(TArrayView<const float> InMinuend, TArrayView<const float> InSubtrahend, TArrayView<float> OutBuffer);` (scope `Audio`) — Subract arrays element-wise. OutArray = InMinuend - InSubtrahend InMinuend is the array of data to be subtracted from. InSubtrahend is the array of data to subtract. OutBuffer is the array which holds the result.
- L180 _prototype_ `void ArraySubtractInPlace1(TArrayView<const float> InMinuend, TArrayView<float> InOutSubtrahend);` (scope `Audio`) — Performs element-wise in-place subtraction placing the result in the subtrahend. InOutSubtrahend = InMinuend - InOutSubtrahend
- L183 _prototype_ `void ArraySubtractInPlace2(TArrayView<float> InOutMinuend, TArrayView<const float> InSubtrahend);` (scope `Audio`) — Performs element-wise in-place subtraction placing the result in the minuend. InOutMinuend = InOutMinuend - InSubtrahend
- L186 _prototype_ `void ArraySubtractByConstantInPlace(TArrayView<float> InValues, float InSubtrahend);` (scope `Audio`) — Subtract value from each element in InValues
- L189 _prototype_ `void ArraySquare(TArrayView<const float> InValues, TArrayView<float> OutValues);` (scope `Audio`) — Square values
- L192 _prototype_ `void ArraySquareInPlace(TArrayView<float> InValues);` (scope `Audio`) — Square values in place.
- L195 _prototype_ `void ArraySqrtInPlace(TArrayView<float> InValues);` (scope `Audio`) — Take Square Root of values in place.
- L198 _prototype_ `void ArrayComplexConjugate(TArrayView<const float> InValues, TArrayView<float> OutValues);` (scope `Audio`) — Perform complex conjugate of array.  Assumes complex numbers are interlaves [real_0, imag_0, real_1, image_1, ..., real_N, imag_N].
- L200 _prototype_ `void ArrayComplexConjugateInPlace(TArrayView<float> InValues);` (scope `Audio`)
- L203 _prototype_ `void ArrayMagnitudeToDecibelInPlace(TArrayView<float> InValues, float InMinimumDb);` (scope `Audio`) — Convert magnitude values to decibel values in place. db = 20 * log10(val)
- L206 _prototype_ `void ArrayPowerToDecibelInPlace(TArrayView<float> InValues, float InMinimumDb);` (scope `Audio`) — Convert power values to decibel values in place. db = 10 * log10(val)
- L209 _prototype_ `void ArrayComplexToPower(TArrayView<const float> InComplexSamples, TArrayView<float> OutPowerSamples);` (scope `Audio`) — Compute power of complex data. Out[i] = Complex[2 * i] * Complex[2 * i] + Complex[2 * i + 1] * Complex[2 * i + 1]
- L212 _prototype_ `void ArrayComplexToPower(TArrayView<const float> InRealSamples, TArrayView<const float> InImaginarySamples, TArrayView<float> OutPowerSamples);` (scope `Audio`) — Compute power of complex data. Out[i] = Real[i] * Real[i] + Imaginary[i] * Imaginary[i]
- L216 _prototype_ `void ArrayUnderflowClamp(TArrayView<float> InOutBuffer);` (scope `Audio`) — `UE_DEPRECATED(5.5, "Audio code relies on denormals flush to zero floating point mode from now on. Please use FScopedFTZFloatMode instead of this API")` — Sets a values to zero if value is denormal. Denormal numbers significantly slow down floating point operations.
- L219 _prototype_ `void ArrayRangeClamp(TArrayView<float> InOutBuffer, float InMinValue, float InMaxValue);` (scope `Audio`) — Clamps the values in a buffer between a min and max value.
- L222 _prototype_ `void ArraySetToConstantInplace(TArrayView<float> InOutBuffer, float InConstant);` (scope `Audio`) — Sets a constant to a buffer (useful for DC offset application)
- L225 _prototype_ `void ArrayWeightedSum(TArrayView<const float> InBuffer1, float InGain1, TArrayView<const float> InBuffer2, float InGain2, TArrayView<float> OutBuffer);` (scope `Audio`) — Performs an element-wise weighted sum OutputBuffer = (InBuffer1 x InGain1) + (InBuffer2 x InGain2)
- L228 _prototype_ `void ArrayWeightedSum(TArrayView<const float> InBuffer1, float InGain1, TArrayView<const float> InBuffer2, TArrayView<float> OutBuffer);` (scope `Audio`) — Performs an element-wise weighted sum OutputBuffer = (InBuffer1 x InGain1) + InBuffer2
- L233 _prototype_ `void ArrayFade(TArrayView<float> InOutBuffer, const float StartValue, const float EndValue);` (scope `Audio`) — if the buffer needs to fade all channels uniformly.
- L234 _prototype_ `void ArrayFade(TArrayView<const float> InBuffer, const float InStartValue, const float InEndValue, TArrayView<float> OutBuffer);` (scope `Audio`)
- L237 _prototype_ `void ArrayMixIn(TArrayView<const float> InFloatBuffer, TArrayView<float> BufferToSumTo, const float Gain);` (scope `Audio`) — Takes buffer InFloatBuffer, optionally multiplies it by Gain, and adds it to BufferToSumTo.
- L238 _prototype_ `void ArrayMixIn(TArrayView<const float> InFloatBuffer, TArrayView<float> BufferToSumTo);` (scope `Audio`)
- L241 _prototype_ `void ArrayMixIn(TArrayView<const int16> InPcm16Buffer, TArrayView<float> BufferToSumTo, const float Gain = 1.0f);` (scope `Audio`) — Takes buffer InPcm16Buffer, converts it to float and optionally multiplies it by Gain, and adds it to BufferToSumTo.
- L244 _prototype_ `void ArrayMixIn(TArrayView<const float> InFloatBuffer, TArrayView<float> BufferToSumTo, const float StartGain, const float EndGain);` (scope `Audio`) — This version of ArrayMixIn will fade from StartGain to EndGain.
- L248 _prototype_ `void ArrayFilterAndMixIn(TArrayView<const float> InFloatBuffer, TArrayView<float> BufferToSumTo, const float Gain, const int32 InNumChannels, bool bEnableLPF, float InLpfCutoff, bool bEnableHPF, float InHpfCutoff, FInterpolatedLPF& InLpf, FInterpolatedHPF& InHpf, FAlignedFloatBuffer& ScratchBuffer);` (scope `Audio`)
- L250 _prototype_ `void ArrayFloatToPcm16(TArrayView<const float> InView, TArrayView<int16> OutView);` (scope `Audio`)
- L251 _prototype_ `void ArrayPcm16ToFloat(TArrayView<const int16> InView, TArrayView<float> OutView);` (scope `Audio`)
- L254 _prototype_ `void ArrayFloatToPcm24(TArrayView<const float> InView, TArrayView<int8> OutView);` (scope `Audio`) — Converts float PCM data to 24 bit integer PCM data
- L256 _prototype_ `void AssignPcm24Value(int8* OutPtr, const int32 InValue, const bool bIsOutputLittleEndian);` (scope `Audio`) — Copies 24 bits of a 32 bit integer (assumes data has been clamped to 24-bits)
- L258 _prototype_ `void ArrayFloatToPcm32(TArrayView<const float> InView, TArrayView<int32> OutView);` (scope `Audio`) — Converts float PCM data to 32 bit integer PCM data
- L260 _prototype_ `void ArrayFloatToPcmDouble(TArrayView<const float> InView, TArrayView<double> OutView);` (scope `Audio`) — Converts float PCM data to double PCM data
- L263 _prototype_ `void ArrayInterleave(const TArray<FAlignedFloatBuffer>& InBuffers, FAlignedFloatBuffer& OutBuffer);` (scope `Audio`) — Interleaves samples from an array of input buffers
- L266 _prototype_ `void ArrayInterleave(const float* const* RESTRICT InBuffers, float* RESTRICT OutBuffer, const int32 InFrames, const int32 InChannels);` (scope `Audio`) — Interleaves samples from an array of input buffers
- L269 _prototype_ `void ArrayDeinterleave(const FAlignedFloatBuffer& InBuffer, TArray<FAlignedFloatBuffer>& OutBuffers, const int32 InChannels);` (scope `Audio`) — Interleaves samples from an array of input buffers
- L272 _prototype_ `void ArrayDeinterleave(const TArrayView<const float> InView, TArray<FAlignedFloatBuffer>& OutBuffers, const int32 InChannels);` (scope `Audio`) — Interleaves samples from an array of input buffers
- L275 _prototype_ `void ArrayDeinterleave(const float* RESTRICT InBuffer, float* const* RESTRICT OutBuffers, const int32 InFrames, const int32 InChannels);` (scope `Audio`) — Interleaves samples from an array of input buffers
- L278 _prototype_ `void ArrayInterpolate(const float* RESTRICT InBuffer, float* RESTRICT OutBuffer, const int32 NumInSamples, const int32 NumOutSamples);` (scope `Audio`) — Interpolates a Mono audio buffer.
- L281 _prototype_ `void ArrayInt16SwapBytes(TArrayView<int16> InView);` (scope `Audio`) — Vectorized 16-bit integer byte swapping.
- L284 _prototype_ `void ArrayInt24SwapBytes(TArrayView<int8> InView);` (scope `Audio`) — Vectorized 24-bit integer byte swapping.
- L287 _prototype_ `void ArrayInt32SwapBytes(TArrayView<int32> InView);` (scope `Audio`) — Vectorized 32-bit integer byte swapping.
- L290 _prototype_ `void ArrayFloatSwapBytes(TArrayView<float> InView);` (scope `Audio`) — Vectorized 32-bit float byte swapping.
- L293 _prototype_ `void ArrayDoubleSwapBytes(TArrayView<double> InView);` (scope `Audio`) — Vectorized 64-bit float byte swapping.
- L297 _function_ `constexpr bool IsHostLittleEndian()` (scope `Audio`) — `UE_DEPRECATED(5.5, "Big Endian platforms are no longer supported.")` — Returns true if host has little endian byte ordering
- L307 _prototype_ `void ArrayAPFLongDelayProcess(const float* InSamples, const float* InDelaySamples, const int32 InNum, float* OutSamples, float* OutDelaySamples, const float Gain);` (scope `Audio`) — All Pass Filter with a long delay.
- L310 _prototype_ `void ArrayLerpFractionalDelay(const float* InSamples, const float* InDelays, const float* DelayData, const int* IntegerDelays, int* UpperDelayPos, int* LowerDelayPos, const int32 InNum, float* OutSamples, const float MaxDelay);` (scope `Audio`) — Fractional delay using linear interpolation.
- L313 _prototype_ `void ArrayScaledComplexConjugate(const float* RESTRICT InValues, const int32 Num, float* RESTRICT OutValues, const float Scale);` (scope `Audio`) — Perform complex conjugate as well as scale.

### `Source/Runtime/SignalProcessing/Public/DSP/FoldbackDistortion.h` (Public)


#### class `Audio::FFoldbackDistortion`  
`class FFoldbackDistortion`  
_L12-60_
- desc: Foldback distortion effect https://en.wikipedia.org/wiki/Foldback_(power_supply_design)
- L16 _public prototype_ `FFoldbackDistortion();` — Constructor
- L19 _public prototype_ `~FFoldbackDistortion();` — Destructor
- L22 _public prototype_ `void Init(const float InSampleRate, const int32 InNumChannels);` — Initialize the equalizer
- L25 _public prototype_ `void SetThresholdDb(const float InThresholdDb);` — Sets the foldback distortion threshold
- L28 _public prototype_ `void SetInputGainDb(const float InInputGainDb);` — Sets the input gain
- L31 _public prototype_ `void SetOutputGainDb(const float InOutputGainDb);` — Sets the output gain
- L34 _public prototype_ `float ProcessAudioSample(const float InSample);` — Processes a single audio sample
- L37 _public prototype_ `void ProcessAudioFrame(const float* InFrame, float* OutFrame);` — Processes a mono stream
- L40 _public prototype_ `void ProcessAudio(const float* InBuffer, const int32 InNumSamples, float* OutBuffer);` — Processes a stereo stream
- L44 _private member_ `float Threshold;` — Threshold to check before folding audio back on itself
- L47 _private member_ `float Threshold2;` — Threshold times 2
- L50 _private member_ `float Threshold4;` — Threshold time 4
- L53 _private member_ `float InputGain;` — Input gain used to force hitting the threshold
- L56 _private member_ `float OutputGain;` — A final gain scaler to apply to the output
- L59 _private member_ `int32 NumChannels;` — How many channels we expect the audio intput to be.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/GrainDelay.h` (Public)


#### class `Audio::GrainDelay::FGrainDelay`  
`class FGrainDelay`  
_L13-117_
- L16 _public prototype_ `FGrainDelay(const float InSampleRate, const float InMaxDelaySeconds = 2.0f);`
- L17 _public prototype_ `~FGrainDelay();`
- L19 _public prototype_ `void Reset();`
- L22 _public prototype_ `float GetGrainDelayClamped(const float InDelay) const;` — Helpers to clamp audio
- L23 _public prototype_ `float GetGrainDurationClamped(const float InDuration) const;`
- L24 _public prototype_ `float GetGrainDelayRatioClamped(const float InGrainDelayRatio) const;`
- L25 _public prototype_ `float GetGrainPitchShiftClamped(const float InPitchShift) const;`
- L26 _public prototype_ `float GetGrainPitchShiftFrameRatio(const float InPitchShift) const;`
- L29 _public prototype_ `void SetMaxGrains(const int32 InMaxGrains);` — Dynamically sets the max grains
- L32 _public prototype_ `void SetGrainEnvelope(const Audio::Grain::EEnvelope InGrainEnvelope);` — Sets the grain envelope
- L35 _public prototype_ `void SetFeedbackAmount(float InFeedbackAmount);` — Sets the feedback amount (how much output grain audio feeds into the delay line)
- L38 _public prototype_ `void SetGrainBasePitchShiftRatio(const float InPitchRatioBase);` — Sets the base pitch shift ratio of all grains
- L41 _public prototype_ `void SpawnGrain(const float InDelay, const float InDuration, const float InPitchShiftRatioOffset);` — Spawns a new grain with the given parameters
- L44 _public prototype_ `void SynthesizeAudio(const int32 StartFrame, const int32 EndFrame, const float* InAudioBuffer, float* OutAudioBuffer);` — Synthesize audio in the given frame range from input audio. Writes to OutAudioBuffer
- L48 _private prototype_ `float SynthesizeFrame(const Audio::FDelay& InDelayLine);` — Synthesize a single frame of audio
- L50 _private prototype_ `void InitDynamicsProcessor();`
- L80 _private member_ `TArray<int32> FreeGrains;` — Free grain indices in the grain pool
- L83 _private member_ `TArray<int32> ActiveGrains;` — Active grain indices in the grain pool
- L86 _private member_ `TArray<FGrain> GrainPool;` — The actual grain pool. Reuses tracking memory for grain lifetimes.
- L89 _private member_ `Grain::FEnvelope GrainEnvelope;` — The shared envelope value. Recomputed when a new envelope is set.
- L90 _private member_ `Grain::EEnvelope GrainEnvelopeType = Grain::EEnvelope::Gaussian;`
- L93 _private member_ `TArray<FTapDelayPitchShifter> DelayPitchShifters;` — A pitch shifting delay line
- L96 _private member_ `FDelay GrainDelayLine;` — The shared delay lines per channel
- L99 _private member_ `float FeedbackAmount = 0.0f;` — The current feedback amount
- L102 _private member_ `float LastFrame = 0.0f;` — Cached value of last rendered frame. Used for feedback
- L105 _private member_ `FDynamicsProcessor DynamicsProcessor;` — Dynamics processor for the grain synthesis
- L108 _private member_ `int32 MaxGrains = 16;` — The maximum grains to have rendering
- L111 _private member_ `float SampleRate = 0.0f;` — Sample rate track to easily deal with pitch scale calculations
- L114 _private member_ `float PitchShiftRatioBase = 1.0f;` — The base pitch shift ratio (pitch scale) of all grains in the grain delay
- L116 _private member_ `float MaxDelaySeconds = 2.0f;`

#### struct `Audio::GrainDelay::FGrainDelay::FGrain`  
`struct FGrain`  
_L53-77_
- desc: Simple grain data structure for tracking grain state
- L56 _public member_ `float DelayTapPositionMilliseconds = 0.0f;` — Where the grain is currently tapped from the delay line
- L59 _public member_ `float NumFramesRendered = 0.0f;` — The current frame the grain is in it's duration
- L62 _public member_ `float DurationFrames = 0.0f;` — The total number of frames this grain will render for
- L65 _public member_ `float PitchShiftRatioOffset = 1.0f;` — The unique randomized pitch scale, so we can modulate the base pitch scale
- L68 _public member_ `FTapDelayPitchShifter PitchShifter;` — The tap delay pitch shifter which manages taps from the shared delay line for each grain
- L71 _public function_ `void SetGrainPitchShiftRatio(const float InPitchShiftRatioBase, const float InSampleRate)` — Helper function for computing the phaser frequency and phaser increment

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L11 _namespace_ `namespace GrainDelay` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/GrainEnvelope.h` (Public)


#### enum `Audio::Grain::EEnvelope`  
`enum class EEnvelope`  
_L15-24_
- desc: Grain envelope types
- L17 _public enumerator_ `Gaussian`
- L18 _public enumerator_ `Triangle`
- L19 _public enumerator_ `DownwardTriangle`
- L20 _public enumerator_ `UpwardTriangle`
- L21 _public enumerator_ `ExponentialDecay`
- L22 _public enumerator_ `ExponentialAttack`
- L23 _public enumerator_ `Hann`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`
- L10 _namespace_ `namespace Grain` (scope `Audio`)
- L12 _typedef_ `typedef TArray<float> FEnvelope;` (scope `Audio::Grain`)
- L27 _function_ `static void GenerateEnvelopeData(FEnvelope& InData, const int32 InNumFrames, const EEnvelope InEnvelopeType)` (scope `Audio::Grain`) — Utility function generates an envelope with the input array for the number of desired frames
- L106 _function_ `static float GetValue(const FEnvelope& InGrainData, const float InFraction)` (scope `Audio::Grain`) — Returns the interpolated envelope value given the fraction through the grain

### `Source/Runtime/SignalProcessing/Public/DSP/Granulator.h` (Public)


#### enum `Audio::EGranularSynthMode`  
`enum class EGranularSynthMode : uint8`  
_L16-22_
- L18 _public enumerator_ `Synthesis`
- L19 _public enumerator_ `Granulation`
- L21 _public enumerator_ `Count`

#### enum `Audio::EGrainEnvelopeType`  
`enum class EGrainEnvelopeType`  
_L24-42_
- L26 _public enumerator_ `Rectangular`
- L27 _public enumerator_ `Triangle`
- L28 _public enumerator_ `DownwardTriangle`
- L29 _public enumerator_ `UpwardTriangle`
- L30 _public enumerator_ `ExponentialDecay`
- L31 _public enumerator_ `ExponentialIncrease`
- L32 _public enumerator_ `Gaussian`
- L33 _public enumerator_ `Hanning`
- L34 _public enumerator_ `Lanczos`
- L35 _public enumerator_ `Cosine`
- L36 _public enumerator_ `CosineSquared`
- L37 _public enumerator_ `Welch`
- L38 _public enumerator_ `Blackman`
- L39 _public enumerator_ `BlackmanHarris`
- L41 _public enumerator_ `Count`

#### class `Audio::FGrainEnvelope`  
`class FGrainEnvelope`  
_L45-57_
- desc: Simple class that generates an envelope and lets you retrieve interpolated values at any given fraction
- L48 _public prototype_ `FGrainEnvelope();`
- L49 _public prototype_ `~FGrainEnvelope();`
- L51 _public prototype_ `void GenerateEnvelope(const EGrainEnvelopeType EnvelopeType, const int32 NumFrames);`
- L52 _public prototype_ `float GetValue(const float Fraction) const;`
- L55 _private member_ `EGrainEnvelopeType CurrentType;`
- L56 _private member_ `TArray<float> GrainEnvelope;`

#### struct `Audio::FGrainData`  
`struct FGrainData`  
_L59-81_
- L62 _public member_ `EOsc::Type OscType;` — What oscillator type to use
- L65 _public member_ `float BufferSeekTime;` — Where in the buffer to seek the grain playback to
- L68 _public member_ `float DurationSeconds;` — Duration of the grain
- L71 _public member_ `float PitchScale;` — Grain pitch scale (if in buffer reading mode)
- L74 _public member_ `float Frequency;` — The grain frequency (if in synthesis mode)
- L77 _public member_ `float Volume;` — Grain volume
- L80 _public member_ `float Pan;` — Grain pan

#### class `Audio::FGrain`  
`class FGrain`  
_L86-166_
- desc: Class representing a grain of audio
- L89 _public prototype_ `FGrain(const int32 InGrainId, FGranularSynth* InParent);`
- L90 _public prototype_ `~FGrain();`
- L93 _public prototype_ `void Play(const FGrainData& InGrainData);` — Plays the grain with the supplied grain data
- L96 _public prototype_ `void SetOscType(const EOsc::Type InType);` — Changes the oscillator type for the grain (if the grain is in synth mode)
- L99 _public prototype_ `void SetOscFrequency(const float InFrequency);` — Sets the oscillator frequency
- L102 _public prototype_ `void SetOscFrequencyModuation(const float InFrequencyModulation);` — Sets the oscillator frequency modulation
- L105 _public prototype_ `void SetPitchModulation(const float InPitchModulation);` — Sets the grain pitch modulation
- L108 _public prototype_ `void SetVolumeModulation(const float InVolumeModulation);` — Sets the grain modulation
- L111 _public prototype_ `void SetPanModulation(const float InPanModulation);` — Sets the pan modulation angle
- L114 _public prototype_ `void SetDurationScale(const float InDurationScale);` — Changes how quickly the grain reads through envelope
- L117 _public prototype_ `bool IsDone() const;` — Queries if this grain is finished playing and needs to be reaped
- L120 _public prototype_ `bool GenerateFrame(float* OutStereoFrame);` — Generates the next frame from the grain
- L123 _protected prototype_ `float GetEnvelopeValue();`
- L126 _protected member_ `int32 GrainId;` — Grain id
- L129 _protected member_ `FGranularSynth* Parent;` — Parent synth
- L132 _protected member_ `FGrainData GrainData;` — Grain data struct
- L135 _protected member_ `FSampleBufferReader SampleBufferReader;` — The sample buffer reader to use for the grain of the mode is granulation
- L138 _protected member_ `FOsc Osc;` — Oscillator to use for synthesis mode
- L141 _protected member_ `float CurrentPitch;` — The current pitch
- L144 _protected member_ `float CurrentFrequency;` — Current frequency
- L147 _protected member_ `float CurrentVolumeScale;` — The current volume scale
- L150 _protected member_ `float CurrentPan;` — The current pan
- L153 _protected member_ `float DurationScale;` — How quickly we read through the envelope
- L156 _protected member_ `float CurrentFrameCount;` — The current frame count the grain is on
- L159 _protected member_ `float EndFrameCount;` — The end frame count the grain will finish on
- L162 _protected member_ `TArray<float> SpeakerMap;` — Speaker map based on the current grain azimuth
- L165 _protected member_ `TArray<float> FrameScratch;` — Scratch buffer for sample reading

#### class `Audio::FGranularSynth`  
`class FGranularSynth`  
_L169-351_
- desc: A stereo granulator
- L172 _public prototype_ `FGranularSynth();`
- L173 _public prototype_ `~FGranularSynth();`
- L175 _public prototype_ `void Init(const int32 InSampleRate, const int32 InNumInitialGrains);`
- L178 _public prototype_ `void LoadSampleBuffer(const TSampleBuffer<int16>& InSampleBuffer);` — Loads a sound wave to use for granular synth mode
- L181 _public prototype_ `void NoteOn(const uint32 InMidiNote, const float InVelocity, const float InDurationSec = INDEX_NONE);` — Plays a granular synthesis "Note"
- L184 _public prototype_ `void NoteOff(const uint32 InMidiNote, const bool bKill);` — Note off, triggers release envelope
- L187 _public prototype_ `void SetAttackTime(const float InAttackTimeMSec);` — Sets the granular synth attack time
- L190 _public prototype_ `void SetDecayTime(const float InDecayTimeMSec);` — Sets the granular synth decay time
- L193 _public prototype_ `void SetSustainGain(const float InSustainGain);` — Sets the granular synth sustain gain
- L196 _public prototype_ `void SetReleaseTime(const float InReleaseTimeMSec);` — Sets the granular synth releas etime
- L199 _public prototype_ `void SeekTime(const float InTimeSec, const float LerpTimeSec = 0.0f, const ESeekType::Type InSeekType = ESeekType::FromBeginning);` — Seeks the loaded buffer used for granulation. Grains will spawn from this location
- L202 _public prototype_ `void SetScrubMode(const bool bIsScrubMode);` — Sets whether or not the buffer playback advances on its own or if it just sits in one place
- L205 _public prototype_ `void SetPlaybackSpeed(const float InPlaybackSpeed);` — Sets how fast the granular play head for granulation is is played (and in what direction)
- L208 _public prototype_ `void SetGrainsPerSecond(const float InNumberOfGrainsPerSecond);` — The rate at which new grains are attempted to be spawned
- L211 _public prototype_ `void SetGrainProbability(const float InGrainProbability);` — The probability at which a grain will occur when a grain tries to spawn. Allows for sporatic grain generation.
- L214 _public prototype_ `void SetGrainEnvelopeType(const EGrainEnvelopeType InGrainEnvelopeType);` — Sets the envelope type to use for new grains. Will instantly switch all grains to this envelope type so may cause discontinuities if switched while playing.
- L217 _public prototype_ `void SetGrainOscType(const EOsc::Type InGrainOscType);` — Sets the grain oscillator type (for use with granular synthesis mode)
- L220 _public prototype_ `void SetGrainVolume(const float InBaseVolume, const FVector2D InVolumeRange = FVector2D::ZeroVector);` — Sets the base grain volume and randomization range
- L223 _public prototype_ `void SetGrainVolumeModulation(const float InVolumeModulation);` — Sets the grain modulation -- allows modulating actively playing grain volumes
- L226 _public prototype_ `void SetGrainPitch(const float InBasePitch, const FVector2D InPitchRange = FVector2D::ZeroVector);` — Sets the base grain pitch and randomization range
- L229 _public prototype_ `void SetGrainFrequency(const float InFrequency, const FVector2D InPitchRange = FVector2D::ZeroVector);` — Sets the grain frequency
- L232 _public prototype_ `void SetGrainFrequencyModulation(const float InFrequencyModulation);` — Sets the grain frequency modulation
- L235 _public prototype_ `void SetGrainPitchModulation(const float InPitchModulation);` — Sets the grain pitch modulation -- allows modulating actively playing grain pitches
- L238 _public prototype_ `void SetGrainPan(const float InBasePan, const FVector2D InPanRange = FVector2D::ZeroVector);` — Sets the grain azimuth (pan) and randomization range
- L241 _public prototype_ `void SetGrainPanModulation(const float InPanModulation);` — Sets the grain azimuth modulation - allows modulating actively playing grain azimuths
- L244 _public prototype_ `void SetGrainDuration(const float InBaseDuration, const FVector2D InDurationRange = FVector2D::ZeroVector);` — Sets the grain duration.
- L247 _public prototype_ `void SetGrainDurationScale(const float InDurationScale);` — Sets the grain duration modulation.
- L250 _public prototype_ `int32 GetNumActiveGrains() const;` — Return the number of currently active grains
- L253 _public prototype_ `float GetCurrentPlayheadTime() const;` — Get current playback time (in granular mode)
- L256 _public prototype_ `float GetSampleDuration() const;` — Returns the duration of the internal loaded sample buffer
- L259 _public prototype_ `void Generate(float* OutAudiobuffer, const int32 NumFrames);` — Generate the next audio buffer
- L263 _protected prototype_ `void SpawnGrain();` — Spawns grains
- L266 _protected prototype_ `float GetWrappedPlayheadPosition(float PlayheadFrame);` — Return wrapped playhead position
- L292 _protected member_ `int32 SampleRate;`
- L293 _protected member_ `int32 NumChannels;`
- L296 _protected member_ `FGrainEnvelope GrainEnvelope;` — The single envelope function used by all grains
- L299 _protected member_ `EGranularSynthMode Mode;` — What mode the granular synthesizer is in
- L302 _protected member_ `EOsc::Type GrainOscType;` — The oscillator type to use if in synthesis mode
- L305 _protected member_ `EGrainEnvelopeType GrainEnvelopeType;` — Current grain envelope type
- L308 _protected member_ `TArray<FGrain> GrainPool;` — A pool of free grains. Will dynamically grow to needed grains based on grain density.
- L309 _protected member_ `TArray<int32> FreeGrains;`
- L310 _protected member_ `TArray<int32> ActiveGrains;`
- L311 _protected member_ `TArray<int32> DeadGrains;`
- L314 _protected member_ `float GrainsPerSecond;` — The rate at which grains are spawned
- L317 _protected member_ `float GrainProbability;` — The probability of a grain occurring when it tries to spawn (based off the GrainsPerSecond)
- L320 _protected member_ `int32 CurrentSpawnFrameCount;` — The current number of frames since last attempt to spawn
- L323 _protected member_ `int32 NextSpawnFrame;` — The next frame when a grain needs to spawn
- L326 _protected member_ `int32 NoteDurationFrameCount;` — Counts for overall note duration of the granulator
- L327 _protected member_ `int32 NoteDurationFrameEnd;`
- L329 _protected member_ `FGrainParam Pan;`
- L330 _protected member_ `FGrainParam Volume;`
- L331 _protected member_ `FGrainParam Pitch;`
- L332 _protected member_ `FGrainParam Frequency;`
- L333 _protected member_ `FGrainParam Duration;`
- L336 _protected member_ `FEnvelope GainEnv;` — Overall envelope of the granulator
- L337 _protected member_ `FAmp Amp;`
- L338 _protected member_ `FDynamicsProcessor DynamicsProcessor;`
- L341 _protected member_ `TSampleBuffer<int16> SampleBuffer;` — The buffer which holds the sample to be granulated
- L344 _protected member_ `float CurrentPlayHeadFrame;` — The current playhead frame
- L345 _protected member_ `float PlaybackSpeed;`
- L346 _protected member_ `int32 NumActiveGrains;`
- L347 _protected member_ `bool bScrubMode;`
- L348 _protected member_ `FLinearEase SeekingPlayheadTimeFrame;`

#### struct `Audio::FGranularSynth::FGrainParam`  
`struct FGrainParam`  
_L270-290_
- desc: Current grain azimuth modulation
- L272 _public member_ `float Modulation;`
- L273 _public member_ `float Base;`
- L274 _public member_ `FVector2D Range;`
- L276 _public function_ `float GetValue() const`
- L281 _public function_ `float GetModulation() const`
- L286 _public function_ `FGrainParam() : Modulation(0.0f) , Base(0.0f)`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/IntegerDelay.h` (Public)


#### class `Audio::FIntegerDelay`  
`class FIntegerDelay`  
_L14-78_
- desc: An adjustable delay line. Delays values are limited to integer values.
- L20 _public prototype_ `FIntegerDelay(int32 InMaxNumDelaySamples, int32 InNumDelaySamples, int32 InNumInternalBufferSamples = 256);` — InMaxDelaySamples is the maximum supported delay. InDelaySamples is the initial delay in samples.
- L23 _public prototype_ `~FIntegerDelay();` — Destructor
- L26 _public prototype_ `void SetDelayLengthSamples(int32 InNumDelaySamples);` — Sets the current delay in samples. InDelay must be less than or equal to the InMaxDelaySamples set in the constructor.
- L29 _public prototype_ `void Reset();` — Resets the delay line state, flushes buffer and resets read/write pointers.
- L32 _public prototype_ `int32 GetNumDelaySamples() const;` — Returns the current delay length in samples.
- L35 _public function_ `inline float ProcessAudioSample(float InSample)` — Process InSamples, placing delayed versions in OutSamples.
- L49 _public prototype_ `void ProcessAudio(const Audio::FAlignedFloatBuffer& InSamples, Audio::FAlignedFloatBuffer& OutSamples);`
- L51 _public prototype_ `void ProcessAudio(TArrayView<const float> InSamples, TArrayView<float> OutSamples);` — Process InSamples, placing delayed versions in OutSamples.
- L55 _public prototype_ `void PeekDelayLine(int32 InNum, Audio::FAlignedFloatBuffer& OutSamples);` — Retrieve a copy of the internal delay line. InNum must be less than or equal to InMaxNumDelaySamples.
- L59 _private prototype_ `void ProcessAudioBlock(const float* InSamples, const int32 InNum, float* OutSamples);` — Process a block of audio. InNum is always less than or equal to NumInternalBufferSamples.
- L62 _private member_ `int32 MaxNumDelaySamples;` — Maximum supported number of delay samples
- L65 _private member_ `int32 NumDelaySamples;` — Current number of delay samples
- L68 _private member_ `int32 NumDelayLineOffsetSamples;` — Offset of output delayed samples relative to DelayLine block buffer
- L71 _private member_ `int32 NumBufferOffsetSamples;` — Offset to handle delay values which are not multiple of required buffer alignment.
- L74 _private member_ `int32 NumInternalBufferSamples;` — Number of samples in an internal buffer
- L77 _private member_ `TUniquePtr<FAlignedBlockBuffer> DelayLine;` — Buffer for holding delayed data.

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/InterpolatedLinearPitchShifter.h` (Public)


#### class `Audio::FLinearPitchShifter`  
`class FLinearPitchShifter`  
_L11-36_
- L15 _public prototype_ `FLinearPitchShifter(int32 InNumChannels = 0);` — ctor
- L17 _public prototype_ `void Reset(int32 InNumChannels, float InInitialPitchShiftSemitones = 0.0f, int32 InInterpLengthFrames = 100);`
- L21 _public prototype_ `int32 ProcessAudio(const TArrayView<float> InputBuffer, Audio::TCircularAudioBuffer<float>& OutputBuffer);` — Sample rate converts the input audio buffer and pushes converted audio to the output circular buffer. (Returns the number of output frames generated.)
- L23 _public prototype_ `void UpdatePitchShift(float InNewPitchSemitones);`
- L27 _private prototype_ `float GetNextIndexDelta();` — returns next fractional index increment
- L29 _private member_ `TArray<float> PreviousFrame;`
- L30 _private member_ `FParam PitchShiftRatio;`
- L31 _private member_ `float CurrentIndex{ 0.0f };`
- L32 _private member_ `int32 NumChannels{ 0 };`
- L33 _private member_ `int32 InterpLengthFrames{ 100 };`
- L34 _private member_ `int32 InterpFramesRemaining{ 0 };`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/InterpolatedMultiTapDelay.h` (Public)


#### class `Audio::FInterpolatedMultiTapDelay`  
`class FInterpolatedMultiTapDelay`  
_L15-36_
- desc: Delay line supporting multiple interpolated tap reads before advancing InBufferSizeSamples must be >= the size of the output buffer passed into Read If the delay length can be less than the output buffer size, Advance should be called before Read
- L18 _public prototype_ `FInterpolatedMultiTapDelay() = default;`
- L20 _public prototype_ `void Init(const int32 InDelayBufferSamples);`
- L22 _public prototype_ `void Advance(TArrayView<const float> InBuffer);`
- L26 _public prototype_ `uint32 Read(const uint32 StartNumDelaySamples, const uint32 StartSampleFraction, const uint32 EndNumDelaySamples, TArrayView<float> OutBuffer);` — Read and interpolate a variable number of samples back in the delay line return a fixed-point representation of fraction of the last sample, which should be passed as StartSampleFraction on successive reads for that tap.
- L27 _public prototype_ `void Reset();`
- L28 _public prototype_ `bool IsInitialized() const;`
- L31 _private member_ `int32 WriteIndex = 0;`
- L33 _private member_ `FAlignedFloatBuffer DelayLine;`
- L34 _private member_ `FAlignedFloatBuffer WrapBuffer;`
- L35 _private member_ `FVectorLinearResampler Resampler;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/InterpolatedOnePole.h` (Public)


#### class `Audio::FInterpolatedLPF`  
`class FInterpolatedLPF`  
_L10-76_
- L14 _public prototype_ `FInterpolatedLPF();` — ctor
- L16 _public function_ `inline float GetCutoffFrequency() const`
- L21 _public prototype_ `void Init(float InSampleRate, int32 InNumChannels);`
- L32 _public prototype_ `void StartFrequencyInterpolation(const float InTargetFrequency, const int32 InterpLength = 1);` — StartFrequencyInterpolation(): Intended use: call once at the beginning of callback, pass the callback length then call ProcessAudioFrame() exactly "InterpLength" number of times At the end of the callback, call StopFrequencyInterpolation() Failing to call StopFrequencyInterpolation() after more than InterpLength calls to ProcessAudioFrame will cause the filter to become unstable and blow up to +/- inf!
- L35 _public prototype_ `void ProcessAudioFrame(const float* RESTRICT InputFrame, float* RESTRICT OutputFrame);` — interpolates coefficient and processes a sample
- L38 _public prototype_ `void ProcessAudioBuffer(const float* RESTRICT InputBuffer, float* RESTRICT OutputBuffer, const int32 NumSamples);` — interpolates coefficient and processes a buffer
- L41 _public prototype_ `void ProcessBufferInPlace(float* InOutBuffer, int32 NumSamples);` — interpolates coefficient and processes a buffer
- L48 _public function_ `inline void StopFrequencyInterpolation()` — StopFrequencyInterpolation() needs to be called manually when the interpolation should be done. Snaps the coefficient to the target value. Setting the lerp delta to 0.0f avoids introducing a branch in ProcessAudioFrame()
- L55 _public prototype_ `void Reset();` — Resets the sample delay to 0
- L59 _public prototype_ `void ClearMemory();` — Clears memory without reevaluating coefficients. This function is useful when there is a break between ProcessAudio calls.
- L62 _public prototype_ `void ArrayCalculateResponseInPlace(TArrayView<float> InOutComplexValues) const;` — Apply the filter transfer function to each z-domain value in the given array (complex numbers given as interleaved floats). Passing in z-domain values on the complex unit circle will give the frequency response.
- L65 _private member_ `float CutoffFrequency{ -1.0f };`
- L66 _private member_ `float B1Curr{ 0.0f };` — coefficient
- L67 _private member_ `float B1Delta{ 0.0f };` — coefficient step size
- L68 _private member_ `float B1Target{ 0.0f };`
- L69 _private member_ `TArray<float> Z1;` — multi-channel delay terms
- L70 _private member_ `int32 CurrInterpLength{ 0 };`
- L71 _private member_ `int32 NumInterpSteps;`
- L72 _private member_ `float SampleRate{ 0 };`
- L73 _private member_ `int32 NumChannels{ 1 };`
- L74 _private member_ `bool bIsFirstFrequencyChange{ true };`

#### class `Audio::FInterpolatedHPF`  
`class FInterpolatedHPF`  
_L80-147_
- L84 _public prototype_ `FInterpolatedHPF();` — ctor
- L86 _public function_ `inline float GetCutoffFrequency() const`
- L91 _public prototype_ `void Init(float InSampleRate, int32 InNumChannels);`
- L102 _public prototype_ `void StartFrequencyInterpolation(const float InTargetFrequency, const int32 InterpLength = 1);` — StartFrequencyInterpolation(): Intended use: call once at the beginning of callback, pass the callback length then call ProcessAudioFrame() exactly "InterpLength" number of times At the end of the callback, call StopFrequencyInterpolation() Failing to call StopFrequencyInterpolation() after more than InterpLength calls to ProcessAudioFrame will cause the filter to become unstable and blow up to +/- inf!
- L105 _public prototype_ `void ProcessAudioFrame(const float* RESTRICT InputFrame, float* RESTRICT OutputFrame);` — interpolates coefficient and processes a sample
- L108 _public prototype_ `void ProcessAudioBuffer(const float* RESTRICT InputBuffer, float* RESTRICT OutputBuffer, const int32 NumSamples);` — interpolates coefficient and processes a buffer
- L111 _public prototype_ `void ProcessBufferInPlace(float* InOutBuffer, int32 NumSamples);` — interpolates coefficients and processes a buffer in place
- L118 _public function_ `inline void StopFrequencyInterpolation()` — StopFrequencyInterpolation() needs to be called manually when the interpolation should be done. Snaps the coefficient to the target value. Setting the lerp delta to 0.0f avoids introducing a branch in ProcessAudioFrame()
- L125 _public prototype_ `void Reset();` — Resets the sample delay to 0
- L129 _public prototype_ `void ClearMemory();` — Clears memory without reevaluating coefficients. This function is useful when there is a break between ProcessAudio calls.
- L132 _public prototype_ `void ArrayCalculateResponseInPlace(TArrayView<float> InOutComplexValues) const;` — Apply the filter transfer function to each z-domain value in the given array (complex numbers given as interleaved floats). Passing in z-domain values on the complex unit circle will give the frequency response.
- L135 _private member_ `float CutoffFrequency{ -1.0f };`
- L136 _private member_ `float A0Curr{ 0.0f };` — coefficient
- L137 _private member_ `float A0Delta{ 0.0f };` — coefficient step size
- L138 _private member_ `float A0Target{ 0.0f };`
- L139 _private member_ `TArray<float> Z1;` — multi-channel delay terms
- L140 _private member_ `int32 CurrInterpLength{ 0 };`
- L141 _private member_ `int32 NumInterpSteps;`
- L142 _private member_ `float SampleRate{ 0 };`
- L143 _private member_ `float NyquistLimit{ 0.0f };`
- L144 _private member_ `int32 NumChannels{ 1 };`
- L145 _private member_ `bool bIsFirstFrequencyChange{ true };`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/LFO.h` (Public)


#### enum `Audio::ELFO::Type`  
`enum Type`  
_L12-23_
- L14 _public enumerator_ `Sine = 0`
- L15 _public enumerator_ `UpSaw`
- L16 _public enumerator_ `DownSaw`
- L17 _public enumerator_ `Square`
- L18 _public enumerator_ `Triangle`
- L19 _public enumerator_ `Exponential`
- L20 _public enumerator_ `RandomSampleHold`
- L22 _public enumerator_ `NumLFOTypes`

#### enum `Audio::ELFOMode::Type`  
`enum Type`  
_L28-40_
- L31 _public enumerator_ `Sync = 0` — Constantly oscillates
- L34 _public enumerator_ `OneShot` — Performs the LFO only once, then stops
- L37 _public enumerator_ `Free` — Doesn't restart the phase of the LFO on subsequent calls to Start
- L39 _public enumerator_ `NumLFOModes`

#### class `Audio::FLFO`  
`class FLFO : public IOscBase`  
_L44-112_
- inherits: `IOscBase`
- desc: Low frequency oscillator
- L47 _public prototype_ `FLFO();`
- L48 _public prototype_ `virtual ~FLFO();`
- L51 _public prototype_ `virtual void Init(const float InSampleRate, const int32 InVoiceId = 0, FModulationMatrix* InMatrix = nullptr, const int32 ModMatrixStage = 1) override;`
- L52 _public prototype_ `virtual void Start() override;`
- L53 _public prototype_ `virtual void Stop() override;`
- L54 _public prototype_ `virtual void Reset() override;`
- L55 _public prototype_ `virtual float Generate(float* QuadPhaseOutput = nullptr) override;`
- L59 _public prototype_ `void SetBipolar(const bool bInBipolar);` — Set whether or not LFO outputs in bipolar domain or unipolar (false) domain. Defaults to bipolar.
- L62 _public prototype_ `void SetType(const ELFO::Type InLFOType);` — Set the waveform type of LFO generator
- L65 _public prototype_ `ELFO::Type GetType() const;` — Returns current waveform type of LFO generator
- L68 _public prototype_ `void SetMode(const ELFOMode::Type InLFOMode);` — Sets mode of LFO (Looping or one-shot.  Free not supported)
- L71 _public prototype_ `ELFOMode::Type GetMode() const;` — Returns current mode of LFO
- L74 _public prototype_ `void SetPhaseOffset(const float InOffset);` — Sets a phase offset for the LFO.  Clamped to positive values only
- L77 _public prototype_ `void SetExponentialFactor(const float InExpFactor);` — Sets the exponential factor of LFO if type is "exponential". Clamped to positive, non-zero values.
- L80 _public prototype_ `FPatchSource GetModSourceNormalPhase() const;` — Returns mod source's normal phase patch source
- L83 _public prototype_ `FPatchSource GetModSourceQuadPhase() const;` — Returns mod source's quad phase patch source
- L86 _protected prototype_ `float ComputeLFO(float InputPhase, float* OutQuad = nullptr);`
- L91 _protected prototype_ `float GetInitPhase() const;` — Returns initial phase, which differs between generators ensuring certain LFO shapes start on rising edge from zero- crossing by default (assuming user's provided phase offset is 0).
- L94 _protected prototype_ `virtual void ResetPhase() override;` — Resets generator to initial phase
- L96 _protected member_ `ELFO::Type LFOType;`
- L97 _protected member_ `ELFOMode::Type LFOMode;`
- L98 _protected member_ `float ExponentialFactor;`
- L99 _protected member_ `uint32 RSHCounter;`
- L100 _protected member_ `float RSHValue;`
- L101 _protected member_ `float ModScale;`
- L102 _protected member_ `float ModAdd;`
- L103 _protected member_ `float LastOutput;`
- L104 _protected member_ `float LoopCount;`
- L105 _protected member_ `float QuadLastOutput;`
- L106 _protected member_ `float PhaseOffset;`
- L108 _protected member_ `bool bBipolar;`
- L110 _protected member_ `FPatchSource ModNormalPhase;`
- L111 _protected member_ `FPatchSource ModQuadPhase;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`
- L10 _namespace_ `namespace ELFO` (scope `Audio`)
- L26 _namespace_ `namespace ELFOMode` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/LKFSAnalyzer.h` (Public)


#### struct `Audio::FLKFSAnalyzerSettings`  
`struct FLKFSAnalyzerSettings`  
_L16-55_
- desc: Settings for FLKFSAnalyzer
- L19 _public member_ `static constexpr float StandardShortTermLoudnessDuration = 3.f;` — These values are taken from the suggested standards for LKFS/LUFS defined in ITU-R BS.1770
- L20 _public member_ `static constexpr float StandardIntegratedLoudnessAnalysisPeriod = 1.f;` — 1 second
- L24 _public member_ `static constexpr float DefaultIntegratedLoudnessDuration = 60.f;` — Streaming audio does not have a natural end point. Integrated loudness in this implementation is taken over a long duration (as opposed to accumulating indefinitely).
- L26 _public member_ `FLoudnessAnalyzerSettings LoudnessAnalyzerSettings { .FFTSize = 4096, .WindowType = EWindowType::None, .LoudnessCurveType = ELoudnessCurveType::K, .MinAnalysisFrequency = 20.0f, .MaxAnalysisFrequency = 24000.0f, .ScalingMethod = ELoudnessAnalyzerScalingMethod::Corrected };`
- L36 _public member_ `float AnalysisPeriod = 0.1f;` — Number of seconds between loudness measurements
- L39 _public member_ `float AnalysisWindowDuration = 0.4f;` — Number of seconds of audio analyzed for each loudness measurements
- L42 _public member_ `float ShortTermLoudnessDuration = StandardShortTermLoudnessDuration;` — Duration of audio analyzed for short term loudness.
- L45 _public member_ `float IntegratedLoudnessAnalysisPeriod = StandardIntegratedLoudnessAnalysisPeriod;` — Number of seconds between long term loudness updates.
- L48 _public member_ `float IntegratedLoudnessDuration = DefaultIntegratedLoudnessDuration;` — Duration of audio analyzed for long term loudness.
- L51 _public member_ `bool bCalculatePerChannelLoudnessRange = false;` — Should the Loudness Range (LRA) statistic be calculated for each channel?
- L54 _public member_ `bool bCalculateOverallLoudnessRange = false;` — Should the overall Loudness Range (LRA) statistic be calculated?

#### struct `Audio::FLKFSResult`  
`struct FLKFSResult`  
_L58-83_
- desc: LKFS Result for a single channel (or overall channels result if Channel is set to -1)
- L61 _public member_ `int32 Channel = 0;` — The audio channel index which produced this result. If -1, then the data was produced by combining all other audio channels
- L64 _public member_ `float Timestamp = 0.0f;` — Time in seconds of the source audio which corresponds to the loudness measurements.
- L67 _public member_ `float Energy = 0.f;` — The instantaneous, perceptually weighted energy relative to full scale.
- L70 _public member_ `float Loudness = 0.0f;` — The instantaneous, perceptually weighted loudness in dB.
- L73 _public member_ `float ShortTermLoudness = 0.0f;` — The average loudness over a short term window of time in dB.
- L76 _public member_ `float IntegratedLoudness = 0.0f;` — The average loudness over a long term window of time in dB.
- L79 _public member_ `float GatedLoudness = 0.0f;` — The average gated loudness over a long term window of time in dB.
- L82 _public member_ `TOptional<FFloatInterval> LoudnessRange;` — Loudness Range (LRA), as defined in EBU Tech 3342.

#### class `Audio::FLKFSAnalyzerResults`  
`class FLKFSAnalyzerResults`  
_L86-109_
- desc: Analyzer results contains all channels LKFS results
- L90 _public prototype_ `FLKFSAnalyzerResults() = default;` — Construct analyzer results
- L93 _public prototype_ `int32 GetNumChannels() const;` — The number of individual channels available in the result.
- L96 _public prototype_ `void Add(FLKFSResult InResults);` — Add to the result.
- L99 _public prototype_ `const TArray<FLKFSResult>& GetChannelLoudnessResults(int32 ChannelIdx) const;` — Returns const reference to a FLKFSResult array for individual channel.
- L102 _public prototype_ `const TArray<FLKFSResult>& GetLoudnessResults() const;` — Returns const reference to a FLKFSResult array associated with overall loudness.
- L105 _public member_ `inline static const int32 ChannelIndexOverall = -1;` — Denotes the overall loudness channel index as opposed individual channel indices.
- L108 _private member_ `TSortedMap<int32, TArray<FLKFSResult>> ChannelResults;`

#### class `Audio::FLKFSAnalyzer`  
`class FLKFSAnalyzer`  
_L119-221_
- desc: FLKFSAnalyzer FLKFSAnalyzer computes Loudness K-Weighted FS (LKFS) metrics for interleaved audio channels. Uses a sliding window approach and an internal perceptual energy analyzer. Produces instantaneous energy and loudness as well as short term, integrated, gated LKFS and optionally the loudness range (based on EBU-3342).
- L123 _public prototype_ `FLKFSAnalyzer(int32 InNumChannels, float InSampleRate, const FLKFSAnalyzerSettings& InSettings);` — Construct analyzer
- L126 _public prototype_ `const FLKFSAnalyzerSettings& GetSettings() const;` — Return const reference to settings used inside this analyzer.
- L129 _public prototype_ `void Analyze(TArrayView<const float> InAudio, FLKFSAnalyzerResults& OutLKFSResults);` — Analyze audio to obtain LKFS values (see FLKFSAnalyzerResults and FLKFSResult for more details)
- L170 _private prototype_ `void AddCurrentLoudnessDataToResult(FLKFSAnalyzerResults& OutResult);`
- L171 _private prototype_ `void AnalyzeSlidingWindow(TAutoSlidingWindow<float>& InSlidingWindow, FLKFSAnalyzerResults& OutResult);`
- L172 _private prototype_ `void AnalyzeWindow(TArrayView<const float> InWindow);`
- L174 _private prototype_ `void AddCurrentLoudnessDataToHistory();`
- L176 _private prototype_ `void UpdateAggregateLoudnessStats();`
- L177 _private prototype_ `void UpdateAggregateLoudnessStats(const TCircularBuffer<float>& InHistory, int32 InOffset, int32 InStride, bool bInUpdateIntegratedLoudness, FAggregateLoudnessStats& OutStats, FLoudnessRange* LoudnessRange = nullptr) const;`
- L179 _private member_ `FLKFSAnalyzerSettings Settings;`
- L181 _private member_ `int32 NumChannels = 0;`
- L182 _private member_ `float SampleRate = 0.0f;`
- L184 _private member_ `int32 NumAnalyzedBuffers = 0;`
- L185 _private member_ `int32 NumEnergyHistory = 0;`
- L186 _private member_ `int32 NumSlidingWindowHopFrames = 0;`
- L189 _private member_ `int32 NumAnalysisHopWindows = 1;` — Number of windows between each loudness analysis
- L192 _private member_ `int32 NumAnalysisWindows = 1;` — Number of windows inspected for each loudness analysis
- L195 _private member_ `int32 NumShortTermHistoryResults = 1;` — Number of values in the "EnergyHistory" to analyze for short term loudness
- L198 _private member_ `int32 NumIntegratedHistoryResults = 1;` — Number of values in the "EnergyHistory" to analyze for integrated and gated loudness
- L201 _private member_ `int32 NumIntegratedHopHistoryResults = 1;` — Number of values in the "EnergyHistory" between integrated and gated loudness anlysis
- L203 _private member_ `TArray<float> ChannelPerceptualEnergy;`
- L204 _private member_ `TArray<float> OverallPerceptualEnergy;`
- L205 _private member_ `TArray<float> InternalWindow;`
- L208 _private member_ `TSortedMap<int32, FAggregateLoudnessStats> AggregateLoudnessStats;` — Per channel stats for short-term, integrated and gated loudness, and optional loudness range.
- L211 _private member_ `TSortedMap<int32, FLoudnessRange> LoudnessRangeStatePerChannel;` — Per channel state for calculating Loudness Range.
- L215 _private member_ `TCircularBuffer<float> ChannelEnergyHistory;` — Channel interleaved history buffer of energy measurements. These are taken once per an loudness analysis, not necessarily once per a audio window.
- L216 _private member_ `TCircularBuffer<float> OverallEnergyHistory;`
- L218 _private member_ `TSlidingBuffer<float> InternalBuffer;`
- L220 _private member_ `FMultichannelLoudnessAnalyzer LoudnessAnalyzer;`

#### struct `Audio::FLKFSAnalyzer::FAggregateLoudnessStats`  
`struct FAggregateLoudnessStats`  
_L135-144_
- desc: Holds aggregated loudness statistics calculated over a history of energy measurements.
- L137 _public member_ `static constexpr float InvalidLoudness = TNumericLimits<float>::Lowest();`
- L139 _public member_ `float ShortTermLoudness = InvalidLoudness;`
- L140 _public member_ `float IntegratedLoudness = InvalidLoudness;`
- L141 _public member_ `float GatedLoudness = InvalidLoudness;`
- L143 _public member_ `TOptional<FFloatInterval> LoudnessRange;`

#### class `Audio::FLKFSAnalyzer::FLoudnessRange`  
`class FLoudnessRange`  
_L149-168_
- desc: Holds state for Loudness Range calculation (for a single channel).
- L152 _public function_ `explicit FLoudnessRange(uint32 InMaxShortTermHistorySize) : ShortTermEnergyHistory(InMaxShortTermHistorySize) , MaxShortTermHistorySize(InMaxShortTermHistorySize)`
- L158 _public prototype_ `void AddShortTermEnergyMeasurement(float InShortTermEnergy);`
- L160 _public prototype_ `TOptional<FFloatInterval> CalculateLoudnessRange() const;`
- L163 _private member_ `TCircularBuffer<float> ShortTermEnergyHistory;`
- L165 _private member_ `uint32 MaxShortTermHistorySize = 0;`
- L166 _private member_ `uint32 ShortTermHistorySize = 0;`
- L167 _private member_ `uint32 ShortTermWriteIndex = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SIGNALPROCESSING_API`
- L11 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/LKFSUtils.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SIGNALPROCESSING_API`
- L9 _namespace_ `namespace Audio`
- L9 _namespace_ `namespace LKFSUtils` (scope `Audio`)
- L14 _prototype_ `UE_INTERNAL void TuneSlidingWindowHopSize(int32 InNumAnalysisHopFrames, int32 InNumSlidingWindowFrames, int32& InNumSlidingWindowHopFrames, int32& InNumAnalysisHopWindows);` (scope `Audio::LKFSUtils`) — There may be multiple calls to the LoudnessAnalyzer to produce a single result. The sliding window hop is tuned here so that it best matches the desired AnalysisPeriod while maintaining between a 25% to 75% window overlap.

### `Source/Runtime/SignalProcessing/Public/DSP/LateReflectionsFast.h` (Public)


#### struct `Audio::FLateReflectionsPlateOutputs`  
`struct FLateReflectionsPlateOutputs`  
_L15-28_
- desc: Structure to hold the various delay line tap outputs produced from a plate.
- L18 _public member_ `static const int32 NumTaps = 7;` — Number of tap locations in plate reverb
- L21 _public member_ `FAlignedFloatBuffer Taps[NumTaps];` — Tap sample buffers.
- L24 _public member_ `FAlignedFloatBuffer Output;` — Output sample buffer.
- L27 _public prototype_ `void ResizeAndZero(int32 InNumSamples);` — Resizes and zero all buffers in structure.

#### struct `Audio::FLateReflectionsPlateDelays`  
`struct FLateReflectionsPlateDelays`  
_L32-117_
- desc: Delay line settings for reverb plate delay Tap locations are determined by analyzing these delay values.
- L88 _public member_ `int32 NumSamplesModulatedBase;` — Base delay samples for modulated delay
- L90 _public member_ `int32 NumSamplesModulatedDelta;` — Max delta samples for modulated delay
- L92 _public member_ `int32 NumSamplesDelayA;` — Tap 0 exists at the output of DelayA
- L94 _public member_ `int32 NumSamplesDelayB;` — Tap 1 exists at the output of DelayB
- L96 _public member_ `int32 NumSamplesDelayC;` — Tap 2 exists at the output of DelayC
- L98 _public member_ `int32 NumSamplesDelayD;` — Delay line length
- L100 _public member_ `int32 NumSamplesAPF;` — All pass filter length
- L102 _public member_ `int32 NumSamplesDelayE;` — Tap 3 exists at the output of DelayE
- L104 _public member_ `int32 NumSamplesDelayF;` — Tap 4 exists at the output of DelayF
- L106 _public member_ `int32 NumSamplesDelayG;` — Tap 5 exists at the output of DelayG
- L108 _public member_ `int32 NumSamplesDelayH;` — Tap 6 exists at the output of DelayH
- L110 _public member_ `int32 NumSamplesDelayI;` — Output tap exists at the output of DelayI
- L113 _public prototype_ `static FLateReflectionsPlateDelays DefaultLeftDelays(float InSampleRate);` — Default delay settings for left channel.
- L116 _public prototype_ `static FLateReflectionsPlateDelays DefaultRightDelays(float InSampleRate);` — Default delay settings for right channel.

#### class `Audio::FLateReflectionsPlate`  
`class FLateReflectionsPlate`  
_L121-188_
- desc: Single plate channel for plate reverberation.
- L124 _public prototype_ `FLateReflectionsPlate( float InSampleRate, int32 InMaxNumInternalBufferSamples, const FLateReflectionsPlateDelays& InDelays);` — InMaxNumInternalBufferSamples sets the mmaximum number of samples in an internal buffer.
- L129 _public prototype_ `~FLateReflectionsPlate();`
- L136 _public prototype_ `void ProcessAudioFrames( const FAlignedFloatBuffer& InSamples, const FAlignedFloatBuffer& InFeedbackSamples, const FAlignedFloatBuffer& InDelayModulations, FLateReflectionsPlateOutputs& OutPlateSamples);` — Processing input samples. All input buffers must be of equal length. InSamples contains previously unseen audio samples. InFeedbackSamples contains the delay line output from the other plate. InDelayModulations contains the fractional delay values per a sample to modulate the first all pass filters delay line. OutPlateSamples is filled with audio from the various tap points and delay line output.
- L143 _public prototype_ `void FlushAudio();` — Flush internal audio to silence.
- L145 _public prototype_ `void SetDensity(float InDensity);`
- L146 _public prototype_ `void SetDampening(float InDampening);`
- L147 _public prototype_ `void SetDecay(float InDecay);`
- L151 _public prototype_ `int32 GetNumInternalBufferSamples() const;` — The number of samples in an internal buffer. This describes the limit of how many values are accessible via PeekDelayLineOutput(...)
- L156 _public prototype_ `void PeekDelayLine(int32 InNum, FAlignedFloatBuffer& OutSamples);` — Retrieve the internal delay line data. The number of samples retrieved is limited to the number of samples in the internal buffer. That amount can be determined by calling "GetNumInternalBufferSamples()".
- L160 _protected member_ `float SampleRate;` — Current parameter settings of reverb
- L161 _protected member_ `int32 NumInternalBufferSamples;`
- L162 _protected member_ `float Dampening;`
- L163 _protected member_ `float Decay;`
- L164 _protected member_ `float Density;`
- L167 _protected member_ `FLateReflectionsPlateDelays PlateDelays;` — Sample delay values
- L170 _protected member_ `static const int32 PresetSampleRate = 29761;` — Sample rate used for hard-coded delay line values
- L172 _protected member_ `TUniquePtr<FDynamicDelayAPF> ModulatedAPF;`
- L173 _protected member_ `TUniquePtr<FIntegerDelay> DelayA;`
- L174 _protected member_ `TUniquePtr<FIntegerDelay> DelayB;`
- L175 _protected member_ `TUniquePtr<FIntegerDelay> DelayC;`
- L176 _protected member_ `TUniquePtr<FIntegerDelay> DelayD;`
- L177 _protected member_ `TUniquePtr<FBufferOnePoleLPF> LPF;`
- L178 _protected member_ `TUniquePtr<FLongDelayAPF> APF;`
- L179 _protected member_ `TUniquePtr<FIntegerDelay> DelayE;`
- L180 _protected member_ `TUniquePtr<FIntegerDelay> DelayF;`
- L181 _protected member_ `TUniquePtr<FIntegerDelay> DelayG;`
- L182 _protected member_ `TUniquePtr<FIntegerDelay> DelayH;`
- L183 _protected member_ `TUniquePtr<FIntegerDelay> DelayI;`
- L185 _protected member_ `Audio::FAlignedFloatBuffer WorkBufferA;`
- L186 _protected member_ `Audio::FAlignedFloatBuffer WorkBufferB;`
- L187 _protected member_ `Audio::FAlignedFloatBuffer WorkBufferC;`

#### struct `Audio::FLateReflectionsFastSettings`  
`struct FLateReflectionsFastSettings`  
_L191-219_
- desc: Settings for controlling the FLateReflections
- L194 _public member_ `float LateDelayMsec;` — Milliseconds for the predelay
- L197 _public member_ `float LateGainDB;` — Initial attenuation of audio after it leaves the predelay
- L200 _public member_ `float Bandwidth;` — Frequency bandwidth of audio going into input diffusers. 0.999 is full bandwidth
- L203 _public member_ `float Diffusion;` — Amount of input diffusion (larger value results in more diffusion)
- L206 _public member_ `float Dampening;` — The amount of high-frequency dampening in plate feedback paths
- L209 _public member_ `float Decay;` — The amount of decay in the feedback path. Lower value is larger reverb time.
- L212 _public member_ `float Density;` — The amount of diffusion in decay path. Larger values is a more dense reverb.
- L214 _public prototype_ `FLateReflectionsFastSettings();`
- L216 _public prototype_ `bool operator==(const FLateReflectionsFastSettings& Other) const;`
- L218 _public prototype_ `bool operator!=(const FLateReflectionsFastSettings& Other) const;`

#### class `Audio::FLateReflectionsFast`  
`class FLateReflectionsFast`  
_L225-316_
- desc: FLateReflections generates the long tail reverb of an input audio signal using a relatively fast algorithm using all pass filter delay lines. It supports 1 or 2 channel input and always produces 2 channel output.
- L229 _public member_ `static const float MaxLateDelayMsec;` — Limits on settings.
- L230 _public member_ `static const float MinLateDelayMsec;`
- L231 _public member_ `static const float MaxLateGainDB;`
- L232 _public member_ `static const float MaxBandwidth;`
- L233 _public member_ `static const float MinBandwidth;`
- L234 _public member_ `static const float MaxDampening;`
- L235 _public member_ `static const float MinDampening;`
- L236 _public member_ `static const float MaxDiffusion;`
- L237 _public member_ `static const float MinDiffusion;`
- L238 _public member_ `static const float MaxDecay;`
- L239 _public member_ `static const float MinDecay;`
- L240 _public member_ `static const float MaxDensity;`
- L241 _public member_ `static const float MinDensity;`
- L243 _public member_ `static const FLateReflectionsFastSettings DefaultSettings;`
- L248 _public prototype_ `` — InMaxNumInternalBufferSamples sets the maximum possible number of samples in an internal buffer. This only affectsinternal chunking and does not affect the number of samples that
- L250 _public prototype_ `~FLateReflectionsFast();`
- L253 _public prototype_ `void SetSettings(const FLateReflectionsFastSettings& InSettings);` — Copies the reverb settings internally, clamps the internal copy and applies the clamped settings.
- L256 _public prototype_ `static void ClampSettings(FLateReflectionsFastSettings& InOutSettings);` — Alters settings to ensure they are within acceptable ranges.
- L261 _public prototype_ `void ProcessAudio(const FAlignedFloatBuffer& InSamples, const int32 InNumChannels, FAlignedFloatBuffer& OutLeftSamples, FAlignedFloatBuffer& OutRightSamples);` — Create reverberation in OutSamples based upon InSamples. OutSamples is a 2 channel audio buffer no matter the value of InNumChannels. OutSamples is mixed with InSamples based upon gain.
- L264 _public prototype_ `void FlushAudio();` — Flush internal audio to silence.
- L267 _private prototype_ `void ProcessAudioBuffer(const float* InSampleData, const int32 InNumFrames, const int32 InNumChannels, float* OutLeftSampleData, float* OutRightSampleData);`
- L269 _private prototype_ `void ApplySettings();`
- L271 _private prototype_ `void GeneraterPlateModulations(const int32 InNum, FAlignedFloatBuffer& OutLeftDelays, FAlignedFloatBuffer& OutRightDelays);`
- L273 _private member_ `float SampleRate;`
- L274 _private member_ `float Gain;`
- L275 _private member_ `float ModulationPhase;`
- L276 _private member_ `float ModulationQuadPhase;`
- L277 _private member_ `float ModulationPhaseIncrement;`
- L278 _private member_ `int32 NumInternalBufferSamples;`
- L281 _private member_ `FLateReflectionsFastSettings Settings;` — Current parameter settings of reverb
- L284 _private member_ `static const int32 PresetSampleRate = 29761;` — Sample rate used for hard-coded delay line values
- L287 _private member_ `TUniquePtr<FIntegerDelay> PreDelay;` — A simple pre-delay line to emulate large delays for late-reflections
- L290 _private member_ `TUniquePtr<FBufferOnePoleLPF> InputLPF;` — Input diffusion
- L291 _private member_ `TUniquePtr<FLongDelayAPF> APF1;`
- L292 _private member_ `TUniquePtr<FLongDelayAPF> APF2;`
- L293 _private member_ `TUniquePtr<FLongDelayAPF> APF3;`
- L294 _private member_ `TUniquePtr<FLongDelayAPF> APF4;`
- L297 _private member_ `FLateReflectionsPlateDelays LeftPlateDelays;` — The plate delay data
- L298 _private member_ `FLateReflectionsPlateDelays RightPlateDelays;`
- L301 _private member_ `TUniquePtr<FLateReflectionsPlate> LeftPlate;` — The plates.
- L302 _private member_ `TUniquePtr<FLateReflectionsPlate> RightPlate;`
- L305 _private member_ `FLateReflectionsPlateOutputs LeftPlateOutputs;` — The plate outputs
- L306 _private member_ `FLateReflectionsPlateOutputs RightPlateOutputs;`
- L309 _private member_ `FAlignedFloatBuffer LeftDelayModSamples;` — Buffer for delay modulation of left and right plates.
- L310 _private member_ `FAlignedFloatBuffer RightDelayModSamples;`
- L312 _private member_ `FAlignedFloatBuffer WorkBufferA;`
- L313 _private member_ `FAlignedFloatBuffer WorkBufferB;`
- L314 _private member_ `FAlignedFloatBuffer WorkBufferC;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/LinearInterpFractionalDelay.h` (Public)


#### class `Audio::FLinearInterpFractionalDelay`  
`class FLinearInterpFractionalDelay`  
_L11-38_
- desc: Fractional delay using linear interpolation.
- L17 _public prototype_ `FLinearInterpFractionalDelay(int32 InMaxDelay, int32 InMaxNumInternalBufferSamples);` — InMaxDelay sets the maximum allowable delay that this object can support. The minimum delay is 0.0 InNumInternalBufferSamples sets the maximum block processing size.
- L18 _public prototype_ `~FLinearInterpFractionalDelay();`
- L22 _public prototype_ `void ProcessAudio(const FAlignedFloatBuffer& InSamples, const FAlignedFloatBuffer& InDelays, FAlignedFloatBuffer& OutSamples);` — Apply delay to InSamples. Fill OutSamples with data from the delay line at a delay of InDelay. InDelay must be equal length to InSamples.
- L25 _public prototype_ `void Reset();` — Set all values in internal delay line to zero.
- L28 _private prototype_ `void ProcessAudioBlock(const float* InSamples, const float* InDelays, const int32 InNum, float* OutSamples);`
- L30 _private member_ `int32 MaxDelay;`
- L31 _private member_ `int32 NumInternalBufferSamples;`
- L33 _private member_ `TUniquePtr<FAlignedBlockBuffer> DelayLine;`
- L34 _private member_ `AlignedInt32Buffer IntegerDelayOffsets;`
- L35 _private member_ `int* UpperDelayPos;`
- L36 _private member_ `int* LowerDelayPos;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/LinkwitzRileyBandSplitter.h` (Public)


#### struct `Audio::FLinkwitzRileyBandFilter`  
`struct FLinkwitzRileyBandFilter`  
_L14-19_
- L16 _public member_ `TArray<FVariablePoleFilter> Filters;`
- L18 _public function_ `FVariablePoleFilter& operator[](int32 InIndex)`

#### struct `Audio::FMultibandBuffer`  
`struct FMultibandBuffer`  
_L21-65_
- L23 _public member_ `Audio::FAlignedFloatBuffer Buffer;`
- L25 _public member_ `int32 NumBands = 0;`
- L26 _public member_ `int32 NumSamples = 0;`
- L28 _public prototype_ `FMultibandBuffer() = default;`
- L30 _public function_ `FMultibandBuffer(int32 InBands, int32 InSamples) : NumBands(InBands) , NumSamples(InSamples)`
- L37 _public function_ `void Init(int32 InBands, int32 InSamples)`
- L45 _public function_ `void SetBands(int32 InBands)`
- L51 _public function_ `void SetSamples(int32 InSamples)`
- L58 _public function_ `void Reset()` — Zero buffers
- L64 _public function_ `float* operator[](int32 BandIndex)`

#### class `Audio::FLinkwitzRileyBandSplitter`  
`class FLinkwitzRileyBandSplitter`  
_L71-112_
- desc: Helper for Multi-Band processing to generate Linwitz-Riley filtered outputs from input https://en.wikipedia.org/wiki/Linkwitz%E2%80%93Riley_filter
- L80 _public function_ `FLinkwitzRileyBandSplitter()`
- L83 _public prototype_ `void Init(const int32 InChannels, const float InSampleRate, const EFilterOrder FilterOrder, const bool bInPhaseCompensate, const TArray<float>& InCrossovers);` — initalize filters
- L89 _public prototype_ `void ProcessAudioFrame(const float* InBuffer, FMultibandBuffer& OutBuffer);`
- L90 _public prototype_ `void ProcessAudioBuffer(const float* InBuffer, FMultibandBuffer& OutBuffer, const int32 NumFrames);`
- L92 _public prototype_ `void SetCrossovers(const TArray<float>& InCrossoverFrequencies);`
- L95 _private member_ `EFilterOrder FilterOrder = EFilterOrder::FourPole;`
- L97 _private member_ `int32 NumBands = 1;`
- L98 _private member_ `int32 NumChannels = 2;`
- L99 _private member_ `float SampleRate = 48000.f;`
- L101 _private member_ `TArray<float> SharedBuffer;`
- L102 _private member_ `TArray<float> BandWorkBuffer;`
- L103 _private member_ `FAlignedFloatBuffer SharedAlignedBuffer;`
- L104 _private member_ `FAlignedFloatBuffer BandAlignedBuffer;`
- L106 _private member_ `TArray<FLinkwitzRileyBandFilter> BandFilters;`
- L107 _private member_ `TArray<FCrossoverBandwidthPair> Crossovers;`
- L109 _private prototype_ `void CopyToBuffer(float* Destination, const float* Origin, const int32 NumSamples);`
- L110 _private prototype_ `void InvertBuffer(float* Buffer, const int32 NumSamples);`
- L111 _private prototype_ `float GetQ(EFilterOrder InFilterOrder);`

#### struct `Audio::FLinkwitzRileyBandSplitter::FCrossoverBandwidthPair`  
`struct FCrossoverBandwidthPair`  
_L74-78_
- L76 _public member_ `float Frequency = 0.f;`
- L77 _public member_ `float Bandwidth = 0.f;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define MAX_BUFFER_SIZE 8192 // 8 channels * 1024 samples`
- L12 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/LongDelayAPF.h` (Public)


#### class `Audio::FLongDelayAPF`  
`class FLongDelayAPF`  
_L13-61_
- desc: All Pass Filter with a long delay. This filter is specifically designed for reverb applications where filter delay lines are long.
- L19 _public prototype_ `FLongDelayAPF(float InG, int32 InNumDelaySamples, int32 InMaxNumInternalBufferSamples);` — InG is the filter coefficient used in the long delay all pass filter. InNumDelaySamples is the delay line length in samples. InMaxNumInternalBufferSamples is the maximum internal block size used internally.
- L22 _public prototype_ `~FLongDelayAPF();` — Destructor
- L25 _public function_ `void SetG(float InG)` — Set the APF feedback/feedforward gain coefficient
- L28 _public prototype_ `void ProcessAudio(const FAlignedFloatBuffer& InSamples, FAlignedFloatBuffer& OutSamples);` — Process InSamples and place filtered data in OutSamples
- L31 _public prototype_ `void ProcessAudio(FAlignedFloatBuffer& Samples);` — Process Samples in place
- L35 _public prototype_ `void ProcessAudio(const FAlignedFloatBuffer& InSamples, FAlignedFloatBuffer& OutSamples, FAlignedFloatBuffer& OutDelaySamples);` — Process InSamples and place filtered data in OutSamples and delay line samples in OutDelaySamples. The OutDelaySamples correspond to "w[n] = InSamples[n] + InG * w[n - InDelay]"
- L38 _public prototype_ `void Reset();` — Sets delay line values to zero.
- L43 _private prototype_ `void ProcessAudioBlock(const float* InSamples, const float* InDelaySamples, const int32 InNum, float* OutSamples, float* OutDelaySamples);` — Performs all pass filtering on an audio block of BlockSize samples are less. InNum must be less than or equal to BlockSize.
- L45 _private prototype_ `int32 GetNumInternalBufferSamples() const;`
- L48 _private member_ `float G;` — Feedback/Feedforward gain coefficient
- L51 _private member_ `int32 NumDelaySamples;` — Delay in samples
- L54 _private member_ `int32 NumInternalBufferSamples;` — Buffer size for internal block processing.
- L57 _private member_ `FAlignedFloatBuffer WorkBuffer;` — Buffer for block operations.
- L60 _private member_ `TUniquePtr<FAlignedBlockBuffer> DelayLine;` — Filter delay line memory.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/LoudnessAnalyzer.h` (Public)


#### enum `Audio::ELoudnessCurveType`  
`enum class ELoudnessCurveType : uint8`  
_L14-22_
- desc: Equal loudness curves from: ANSI Standards S1.4-1983 and S1.42-2001
- L16 _public enumerator_ `A`
- L17 _public enumerator_ `B`
- L18 _public enumerator_ `C`
- L19 _public enumerator_ `D`
- L20 _public enumerator_ `K`
- L21 _public enumerator_ `None`

#### enum `Audio::ELoudnessAnalyzerScalingMethod`  
`enum class ELoudnessAnalyzerScalingMethod : uint8`  
_L39-51_
- L46 _public enumerator_ `BackCompatible` — Normalize by FFTSize and having perceptual curves be unity gain at 1khz. Note: This method does not correctly account for different window functions and also reduces the energy by half. It remains here for backwards compatibility.
- L50 _public enumerator_ `Corrected` — Normalize by Window Function. Use this when performing loudness analysis which must match the LKFS standardized measurements.

#### struct `Audio::FLoudnessAnalyzerSettings`  
`struct FLoudnessAnalyzerSettings`  
_L54-82_
- desc: Settings for FLoudnessAnalyzer
- L57 _public member_ `int32 FFTSize = 8192;` — Size of FFT describe in number of samples
- L60 _public member_ `EWindowType WindowType = EWindowType::Blackman;` — Type of window to be applied to input audio
- L63 _public member_ `ELoudnessCurveType LoudnessCurveType = ELoudnessCurveType::D;` — Type of equal loudness curve to weight power spectrum
- L66 _public member_ `float MinAnalysisFrequency = 20.f;` — Minimum frequency for analyzing audio
- L69 _public member_ `float MaxAnalysisFrequency = 10000.f;` — Maximum frequency for analyzing audio
- L76 _public member_ `int32 WindowSize = -1;` — Size of the audio analysis window in samples. If this is less than 1, it will become equal to the FFTSize. Otherwise, this must be less than or equal to the FFT Size.
- L81 _public member_ `ELoudnessAnalyzerScalingMethod ScalingMethod = ELoudnessAnalyzerScalingMethod::BackCompatible;` — Method to use for scaling and normalizing data. Corrected is preferred in terms of correctness. BackCompatible is available for backwards compatibility.

#### class `Audio::FLoudnessAnalyzer`  
`class FLoudnessAnalyzer`  
_L90-150_
- desc: FLoudnessAnalyzer FLoudnessAnalyzer will calculate perceptual energy or loudness one window at a time. This analyzer only handles mono audio. See FMultichannelLoudnessAnalyzer for multichannel support.
- L94 _public prototype_ `FLoudnessAnalyzer(float InSampleRate, const FLoudnessAnalyzerSettings& InSettings);` — Construct analyzer
- L100 _public prototype_ `float CalculatePerceptualEnergy(TArrayView<const float> InSampleView);` — Calculate the perceptual energy for the input samples.  The number of input samples must be equal to the FFTSize supplied in FLoudnessAnalyzerSettings.
- L106 _public prototype_ `float CalculateLoudness(TArrayView<const float> InSampleView);` — Calculate the loudness for the input samples.  The number of  input samples must be equal to the FFTSize supplied in FLoudnessAnalyzerSettings.
- L111 _public prototype_ `static float ConvertPerceptualEnergyToLoudness(float InPerceptualEnergy);` — Convert from perceptual energy to loudness [Loudness = 10 * log_10(Energy)]
- L116 _public prototype_ `static float ConvertPerceptualEnergyToLKFS(float InPerceptualEnergy);` — Convert from perceptual energy to loudness [LKFS = -0.691 + 10 * log_10(Energy)]
- L121 _public prototype_ `const FLoudnessAnalyzerSettings& GetSettings() const;` — Return const reference to settings used inside this analyzer.
- L124 _private prototype_ `float CalculateEnergyScaling() const;`
- L125 _private prototype_ `float GetEqualLoudnessWeightForFrequency(float InHz) const;`
- L126 _private prototype_ `float CalculateEnergyScalingBackCompatible() const;`
- L127 _private prototype_ `float CalculateEnergyScalingCorrected() const;`
- L128 _private prototype_ `float CalculateWindowEnergyScaling() const;`
- L130 _private member_ `FLoudnessAnalyzerSettings Settings;`
- L133 _private member_ `float EnergyScale = 1.f;` — Scale factor used to normalize between differing window sizes and fft sizes
- L135 _private member_ `int32 MinFreqIndex = 0;`
- L136 _private member_ `int32 MaxFreqIndex = 0;`
- L139 _private member_ `int32 FFTFreqSize = 0;` — Number of FFTFrequency bins worth looking at.
- L140 _private member_ `int32 ActualFFTSize = 0;`
- L142 _private member_ `TUniquePtr<IFFTAlgorithm> FFT;`
- L144 _private member_ `FAlignedFloatBuffer Window;`
- L145 _private member_ `FAlignedFloatBuffer WindowedSamples;`
- L146 _private member_ `FAlignedFloatBuffer ComplexSpectrum;`
- L147 _private member_ `FAlignedFloatBuffer RealSpectrum;`
- L149 _private member_ `FAlignedFloatBuffer CurveWeights;`

#### class `Audio::FMultichannelLoudnessAnalyzer`  
`class FMultichannelLoudnessAnalyzer`  
_L159-234_
- desc: FMultichannelLoudnessAnalyzer FMultichannelLoudnessAnalyzer will calculate perceptual energy or loudness one window at a time. This module can handle one or more channels at a time. It expects interleaved audio samples.
- L163 _public prototype_ `FMultichannelLoudnessAnalyzer(float InSampleRate, const FLoudnessAnalyzerSettings& InSettings);` — Construct analyzer.
- L178 _public prototype_ `float CalculatePerceptualEnergy(TArrayView<const float> InSampleView, const int32 InNumChannels, TArray<float>& OutChannelEnergies);` — `UE_DEPRECATED(5.7, "Use method which accepts a TArrayView<float> for OutChannelEnergies")` — Calculate perceptual energy. InSampleView		  InSampleView is expected to contain interleaved audio with (InSettings.FFTSize * InNumChannels) number of samples. InNumChannels      Number of input channels. OutChannelEnergies Will be populated with energies on a per channel basis. The overall perceptual energy is returned.
- L192 _public prototype_ `float CalculatePerceptualEnergy(TArrayView<const float> InSampleView, const int32 InNumChannels, TArrayView<float> OutChannelEnergies);` — Calculate perceptual energy. InSampleView		  InSampleView is expected to contain interleaved audio with (InSettings.FFTSize * InNumChannels) number of samples. InNumChannels      Number of input channels. OutChannelEnergies Will be populated with energies on a per channel basis. The overall perceptual energy is returned.
- L207 _public prototype_ `float CalculateLoudness(TArrayView<const float> InSampleView, const int32 InNumChannels, TArray<float>& OutChannelLoudness);` — `UE_DEPRECATED(5.7, "Use method which accepts a TArrayView<float> for OutChannelLoudness")` — Calculate loudness InSampleView		  InSampleView is expected to contain interleaved audio with (InSettings.FFTSize * InNumChannels) number of samples. InNumChannels      Number of input channels. OutChannelLoudness Will be populated with energies on a per channel basis. The overall loudness is returned.
- L221 _public prototype_ `float CalculateLoudness(TArrayView<const float> InSampleView, const int32 InNumChannels, TArrayView<float> OutChannelLoudness);` — Calculate loudness InSampleView		  InSampleView is expected to contain interleaved audio with (InSettings.FFTSize * InNumChannels) number of samples. InNumChannels      Number of input channels. OutChannelLoudness Will be populated with energies on a per channel basis. The overall loudness is returned.
- L226 _public prototype_ `const FLoudnessAnalyzerSettings& GetSettings() const;` — Return const reference to settings used inside this analyzer.
- L229 _private prototype_ `void InitializeChannelWeights(int32 InNumChannels);`
- L231 _private member_ `FAlignedFloatBuffer MonoBuffer;`
- L232 _private member_ `TArray<float> ChannelWeights;`
- L233 _private member_ `FLoudnessAnalyzer Analyzer;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SIGNALPROCESSING_API`
- L9 _namespace_ `namespace Audio`
- L11 _namespace_ `namespace Audio`
- L25 _prototype_ `float GetEqualLoudnessAWeigthForFrequency(const float Freq);` (scope `Audio`) — Generate equal loudness weight for magnitude spectrum using curve A
- L28 _prototype_ `float GetEqualLoudnessBWeigthForFrequency(const float Freq);` (scope `Audio`) — Generate equal loudness weight for magnitude spectrum using curve B
- L31 _prototype_ `float GetEqualLoudnessCWeigthForFrequency(const float Freq);` (scope `Audio`) — Generate equal loudness weight for magnitude spectrum using curve C
- L34 _prototype_ `float GetEqualLoudnessDWeigthForFrequency(const float Freq);` (scope `Audio`) — Generate equal loudness weight for magnitude spectrum using curve D
- L37 _prototype_ `float GetEqualLoudnessNoneWeigthForFrequency(const float Freq);` (scope `Audio`) — Generate equal loudness weight for magnitude spectrum using curve None

### `Source/Runtime/SignalProcessing/Public/DSP/MelScale.h` (Public)


#### enum `Audio::EMelNormalization`  
`enum class EMelNormalization : uint8`  
_L18-23_
- desc: Normalization methods for a mel transform.
- L20 _public enumerator_ `EqualAmplitude` — Useful when working on magnitude spectrum
- L21 _public enumerator_ `EqualEuclideanNorm` — Scale energy by euclidean norm. Good when using magnitude spectrum.
- L22 _public enumerator_ `EqualEnergy` — Useful when working on power spectrum

#### struct `Audio::FMelSpectrumKernelSettings`  
`struct FMelSpectrumKernelSettings`  
_L27-42_
- desc: Settings for a mel kernel which transforms an linearly space spectrum (e.g. FFT Magnitude) to a mel spectrum
- L29 _public member_ `int32 NumBands;` — Number of bands in Mel spectrum
- L30 _public member_ `float KernelMinCenterFreq;` — Minimum frequency of lowest mel band.
- L31 _public member_ `float KernelMaxCenterFreq;` — Maximum frequency of highest mel band.
- L32 _public member_ `EMelNormalization Normalization;` — Mel band scaling. EqualAmplitude is better for the magnitude spectrum, while EqualEnergy is better for the power spectrum.
- L33 _public member_ `float BandWidthStretch;` — Controls the wideness of each band.
- L35 _public function_ `FMelSpectrumKernelSettings() : NumBands(26) , KernelMinCenterFreq(100.f) , KernelMaxCenterFreq(10000.f) , Normalization(EMelNormalization::EqualEnergy) , BandWidthStretch(1.f)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L12 _prototype_ `float MelToHz(float InMel);` (scope `Audio`) — Convert a mel frequency to a frequency in hz.
- L15 _prototype_ `float HzToMel(float InHz);` (scope `Audio`) — Convert  a frequency in hz to a mel frequency.
- L44 _prototype_ `TUniquePtr<FContiguousSparse2DKernelTransform> NewMelSpectrumKernelTransform(const FMelSpectrumKernelSettings& InSettings, const int32 InFFTSize, const float InSampleRate);` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/MidiNoteQuantizer.h` (Public)


#### enum `Audio::EMusicalScale::Scale`  
`enum Scale`  
_L13-62_
- desc: Any additions to this Enum should also be added to MetasoundMidiNoteQuantizerNode.cpp in the "#pragma region Metasound Enums" area to show up as options in that Node
- L16 _public enumerator_ `Major` — Modes
- L17 _public enumerator_ `Minor_Dorian`
- L18 _public enumerator_ `Phrygian`
- L19 _public enumerator_ `Lydian`
- L20 _public enumerator_ `Dominant7th_Mixolydian`
- L21 _public enumerator_ `NaturalMinor_Aeolian`
- L22 _public enumerator_ `HalfDiminished_Locrian`
- L25 _public enumerator_ `Chromatic` — Non-Diatonic
- L26 _public enumerator_ `WholeTone`
- L27 _public enumerator_ `DiminishedWholeTone`
- L30 _public enumerator_ `MajorPentatonic` — pentatonic
- L31 _public enumerator_ `MinorPentatonic`
- L32 _public enumerator_ `Blues`
- L35 _public enumerator_ `Bebop_Major` — bebop
- L36 _public enumerator_ `Bebop_Minor`
- L37 _public enumerator_ `Bebop_MinorNumber2`
- L38 _public enumerator_ `Bebop_Dominant`
- L41 _public enumerator_ `HarmonicMajor` — common major/minors
- L42 _public enumerator_ `HarmonicMinor`
- L43 _public enumerator_ `MelodicMinor`
- L44 _public enumerator_ `SixthModeOfHarmonicMinor`
- L47 _public enumerator_ `LydianAugmented` — lydian/augmented
- L48 _public enumerator_ `LydianDominant`
- L49 _public enumerator_ `Augmented`
- L52 _public enumerator_ `Diminished` — diminished
- L53 _public enumerator_ `Diminished_BeginWithHalfStep`
- L54 _public enumerator_ `Diminished_BeginWithWholeStep`
- L55 _public enumerator_ `HalfDiminished_LocrianNumber2`
- L58 _public enumerator_ `Spanish_or_Jewish` — other
- L59 _public enumerator_ `Hindu`
- L61 _public enumerator_ `Count`

#### struct `Audio::ScaleDegreeSet`  
`struct ScaleDegreeSet`  
_L65-76_
- L69 _public prototype_ `ScaleDegreeSet(const TArray<float>& InScaleDegrees, const TArray<float>& InChordTones = {});` — ctor
- L71 _public prototype_ `TArrayView<float> GetScaleDegreeSet(bool bChordTonesOnlyIfApplicable = false);`
- L74 _private member_ `TArray<float> ScaleDegrees;`
- L75 _private member_ `TArray<float> ChordTones;`

#### class `Audio::FMidiNoteQuantizer`  
`class FMidiNoteQuantizer`  
_L78-91_
- L81 _public prototype_ `static float QuantizeMidiNote(const float InNote, const float InRoot, EMusicalScale::Scale InScale, bool bChordTonesOnlyIfApplicable = false);`
- L82 _public prototype_ `static float QuantizeMidiNote(const float InNote, const float InRoot, const TArrayView<float> InScaleDegrees, const float InSemitoneScaleRange = 12.0f);`
- L85 _private prototype_ `static float QuantizeValueToScaleDegree(const float InValue, const TArrayView<float> InScaleDegrees, const float InSemitoneScaleRange = 12.0f);`
- L89 _public member_ `static TMap<EMusicalScale::Scale, ScaleDegreeSet> ScaleDegreeSetMap;` — Statically-defined scale/chord tone definitions.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`
- L9 _namespace_ `namespace EMusicalScale` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/ModulationMatrix.h` (Public)


#### struct `Audio::FPatchSource`  
`struct FPatchSource`  
_L11-34_
- L13 _public function_ `FPatchSource() : Id(INDEX_NONE)`
- L17 _public function_ `FPatchSource(const uint32 InId) : Id(InId)`
- L21 _public function_ `void SetName(const FString& InName)`
- L28 _public member_ `uint32 Id;`
- L31 _public member_ `FString Name;`

#### struct `Audio::FPatchDestination`  
`struct FPatchDestination`  
_L36-65_
- L38 _public function_ `FPatchDestination() : Id(INDEX_NONE) , Stage(INDEX_NONE) , Depth(0.0f)`
- L44 _public function_ `FPatchDestination(const uint32 InId) : Id(InId) , Stage(INDEX_NONE) , Depth(0.0f)`
- L50 _public member_ `uint32 Id;`
- L52 _public member_ `int32 Stage;`
- L53 _public member_ `float Depth;`
- L55 _public function_ `void SetName(const FString& InName)`
- L63 _public member_ `FString Name;`

#### struct `Audio::FPatch`  
`struct FPatch`  
_L67-99_
- L69 _public function_ `FPatch() : Source(INDEX_NONE) , bEnabled(true)`
- L75 _public function_ `FPatch(const FPatchSource& InSourceId, const FPatchDestination& InDestinationId) : Source(InSourceId) , bEnabled(true)`
- L82 _public function_ `void SetName(const FString& InName)`
- L90 _public member_ `FPatchSource Source;` — The modulation source of the patch
- L93 _public member_ `TArray<FPatchDestination> Destinations;` — The modulation destinations of the patch to support multiple destinations
- L96 _public member_ `FString Name;`
- L98 _public member_ `bool bEnabled;`

#### class `Audio::FModulationMatrix`  
`class FModulationMatrix`  
_L101-164_
- L104 _public prototype_ `FModulationMatrix();`
- L105 _public prototype_ `virtual ~FModulationMatrix();`
- L108 _public prototype_ `void Init(const int32 NumVoices);` — Initialize the modulation matrix with the desired number of voices
- L111 _public prototype_ `int32 GetNumPatches(const int32 VoiceId) const;` — Returns the number of patch connections
- L114 _public prototype_ `FPatchSource CreatePatchSource(const int32 VoiceId);` — Creates a new patch source object and returns the patch source id
- L117 _public prototype_ `FPatchDestination CreatePatchDestination(const int32 VoiceId, const int32 Stage, const float DefaultDepth);` — Crates a new patch destination object and returns the patch destination id
- L120 _public prototype_ `bool AddPatch(const int32 VoiceId, FPatch* Patch);` — Adds a new patch connection between one source and one or more destinations
- L123 _public prototype_ `bool RemovePatch(const int32 VoiceId, FPatch* Patch);` — Removes the given patch connection between a source and one or more destinations
- L126 _public prototype_ `void ResetPatchSourceState();` — Reset all patch state
- L129 _public prototype_ `void ClearPatches(const int32 VoiceId);` — Clear all patch connections
- L132 _public prototype_ `bool SetSourceValue(const int32 VoiceId, const FPatchSource& Source, const float Value);` — Set the modulation source value of the given id
- L135 _public prototype_ `bool GetDestinationValue(const int32 VoiceId, const FPatchDestination& Destination, float& OutValue) const;` — Get the modulation destination value of the given destination id
- L138 _public prototype_ `void Update(const int32 VoiceId, const int32 Stage = INDEX_NONE);` — Perform the matrix update. Optionally do only a given stage.
- L142 _protected prototype_ `void ResetDestinations(const int32 VoiceId);`
- L143 _protected prototype_ `bool ValidatePatch(const int32 VoiceId, FPatch* Patch);`
- L145 _protected member_ `int32 NumVoices;`
- L146 _protected member_ `TArray<TArray<FPatch*>> Patches;`
- L147 _protected member_ `TArray<TArray<float>> Sources;`
- L163 _protected member_ `TArray<TArray<FDestData>> Destinations;`

#### struct `Audio::FModulationMatrix::FDestData`  
`struct FDestData`  
_L149-161_
- L152 _public member_ `float Value;` — What the value of the destination is
- L155 _public member_ `bool bDirty;` — Whether or not anybody changed it
- L157 _public function_ `FDestData() : Value(0.0f) , bDirty(false)`

#### Free symbols / members of external scopes

- L7 _macro_ `#define MOD_MATRIX_DEBUG_NAMES 1`
- L9 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/MultiMono.h` (Public)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace Audio`
- L17 _variable_ `constexpr int32 MaxStackMultiMonoChannels = 128;` (scope `Audio`) — Some relatively high number. These are just pointers on stack.
- L20 _typedef_ `template<typename T> using TStackArrayOfPointers = TArray<T*,TInlineAllocator<MaxStackMultiMonoChannels>>;` (scope `Audio`) — Stack array of pointers alias.
- L24 _function_ `template<typename T> TStackArrayOfPointers<T> MakeMultiMonoPointersFromView(TArrayView<T> InMultiMono, const int32 InNumFrames, const int32 InNumChannels)` (scope `Audio`) — Helper to create array of pointers from multi-mono. Warning Array of pointers will be larger than you need, but filled to InNumChannels
- L48 _prototype_ `void MultiMonoMixUpOrDown( TArrayView<const float> InSrc, const TArrayView<float> InDst, const int32 NumFrames, TArrayView<const float> MixGains, const int32 NumSrcChannels, const int32 NumDstChannels);` (scope `Audio`) — Given a Matrix of Gains (produced by calling ChannelMap.cpp (Audio::Create2DChannelMap), Mix Up/Down Source into Destination. @param InSrc ArrayView to Source (Multi-mono) @param InDst ArrayView to Destination (Mult-mono). @param NumFrames Number of Frames in Each Channel. @param MixGains Matrix of Gains (in Row Major Format, see Create2DChannelMap). [NumDstChannels*NumSrcChannels] @param NumDstChannels Num Of Destination Channels. @param NumSrcChannels Num Of Source Channels.
- L52 _prototype_ `void MultiMonoMixUpOrDown( TArrayView<const float*> InSrc, TArrayView<float*> InDst, const int32 NumFrames,TArrayView<const float> MixGains);` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/MultichannelBuffer.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L12 _typedef_ `using FMultichannelBuffer = TArray<Audio::FAlignedFloatBuffer>;` (scope `Audio`) — A deinterleaved multichannel buffer
- L18 _typedef_ `using FMultichannelBufferView = TArray<TArrayView<float>>;` (scope `Audio`) — A deinterleaved multichannel buffer view. The semantics are similar to TArray<> and TArrayView<>. FMultichannelBufferView allows sample values to be read and written, but it cannot be resized.
- L21 _typedef_ `using FMultichannelCircularBuffer = TArray<Audio::TCircularAudioBuffer<float>>;` (scope `Audio`) — A deinterleaved multichannel circular buffer
- L29 _prototype_ `void SetMultichannelBufferSize(int32 InNumChannels, int32 InNumFrames, FMultichannelBuffer& OutBuffer);` (scope `Audio`) — Set the number of channels and frames for a multichannel buffer. @param InNumChannels - Number of channels to hold in the buffer. @param InNumFrames - Number of frames to hold in the buffer. @param OutBuffer - Buffer to resize.
- L37 _prototype_ `void SetMultichannelCircularBufferCapacity(int32 InNumChannels, int32 InNumFrames, FMultichannelCircularBuffer& OutBuffer);` (scope `Audio`) — Set the number of channels and capacity for a multichannel circular buffer. @param InNumChannels - Number of channels to hold in the buffer. @param InNumFrames - Maximum number of frames the buffer can hold. @param OutBuffer - Buffer to resize.
- L44 _prototype_ `void SetMultichannelBufferSize(int32 InNumFrames, FMultichannelBuffer& OutBuffer);` (scope `Audio`) — Set the number of frames for a multichannel buffer. @param InNumFrames - Number of frames to hold in the buffer. @param OutBuffer - Buffer to resize.
- L48 _prototype_ `int32 GetMultichannelBufferNumFrames(const FMultichannelBuffer& InBuffer);` (scope `Audio`) — Return the number of frames in the buffer. It is expected that each channel contains the same number of frames.
- L52 _prototype_ `int32 GetMultichannelBufferNumFrames(const FMultichannelCircularBuffer& InBuffer);` (scope `Audio`) — Return the number of frames in the buffer. It is expected that each channel contains the same number of frames.
- L56 _prototype_ `int32 GetMultichannelBufferNumFrames(const FMultichannelBufferView& InBuffer);` (scope `Audio`) — Return the number of frames in the buffer. It is expected that each channel contains the same number of frames.
- L59 _prototype_ `FMultichannelBufferView MakeMultichannelBufferView(FMultichannelBuffer& InBuffer);` (scope `Audio`) — Creates a FMultichannelBufferView from a FMultichannelBuffer.
- L62 _prototype_ `FMultichannelBufferView MakeMultichannelBufferView(FMultichannelBuffer& InBuffer, int32 InStartFrameIndex, int32 InNumFrames);` (scope `Audio`) — Creates a FMultichannelBufferView from a FMultichannelBuffer.
- L65 _prototype_ `FMultichannelBufferView SliceMultichannelBufferView(const FMultichannelBufferView& View, int32 InStartFrameIndex, int32 InNumFrames);` (scope `Audio`) — Slice a multichannel buffer view to a given frame range.
- L68 _prototype_ `void ShiftMultichannelBufferView(int32 InNumFrames, FMultichannelBufferView& View);` (scope `Audio`) — Shift the start frame of a multichannel buffer view to a given number of frames.

### `Source/Runtime/SignalProcessing/Public/DSP/MultichannelLinearResampler.h` (Public)


#### class `Audio::FMultichannelLinearResampler`  
`class FMultichannelLinearResampler`  
_L12-95_
- desc: Linear resampler working on multichannel buffers
- L14 _private member_ `static constexpr float MinFrameRatioFrameDelta = 0.001f;`
- L17 _public member_ `static const float MaxFrameRatio;`
- L18 _public member_ `static const float MinFrameRatio;`
- L24 _public prototype_ `FMultichannelLinearResampler(int32 InNumChannels);` — Construct a linear resampler. @param InNumChannel - Number of audio channels in input and output buffers.
- L33 _public prototype_ `void SetFrameRatio(float InRatio, int32 InNumFramesToInterpolate=0);` — Sets the number of input frames to read per an output frame. 0.5 is half speed, 1.f is normal speed, 2.0 is double speed. @param InRatio - Ratio of input frames consumed per an output frame produced. @param InNumFramesToInterpolate - Number of output frames over which to interpolate the frame ratio.
- L44 _public prototype_ `float MapInputFrameToOutputFrame(float InInputFrameIndex) const;` — Translates an input frame index to an output frame index given the state of the resampler. Note: Indices are relative to the buffers passed to `ProcessAudio(...)`. The resampler does not maintain a sample counter between calls to `ProcessAudio(...)`. @param InInputFrameIndex - Index of input frame. @return Index of output frame.
- L55 _public prototype_ `float MapOutputFrameToInputFrame(float InOutputFrameIndex) const;` — Translates an output frame index to an input frame index given the state of the resampler. Note: Indices are relative to the buffers passed to `ProcessAudio(...)`. The resampler does not maintain a sample counter between calls to `ProcessAudio(...)`. @param InOutputFrameIndex - Index of output frame. @return Index of input frame.
- L63 _public prototype_ `int32 GetNumInputFramesNeededToProduceOutputFrames(int32 InNumOutputFrames) const;` — Returns the minimum number of input frames needed to produce the desired number of output frames given the current state of the resampler. @param InNumOutputFrames - The desired number of output frames. @return The minimum number of input frames.
- L76 _public prototype_ `int32 ProcessAndConsumeAudio(FMultichannelCircularBuffer& InAudio, FMultichannelBuffer& OutAudio);` — Consumes audio from the input buffer and produces audio in the output buffer. The desired number of frames to produce is determined by the output audio buffer size. For the desired number of samples to be produced, the input audio must have the minimum number of frames needed to produce the output frames (see `GetNumInputFramesNeededToProduceOutputFrames(...)`). Input samples which are no longer needed are removed from the input buffer. @param InAudio - Multichannel circular buffer of input audio. @param OutAudio - Multichannel buffer of output audio. @return Actual number of frames produced.
- L77 _public prototype_ `int32 ProcessAndConsumeAudio(FMultichannelCircularBuffer& InAudio, FMultichannelBufferView& OutAudio);`
- L82 _private prototype_ `template<typename OutputMultichannelBufferType> int32 ProcessAndConsumeAudioInternal(FMultichannelCircularBuffer& InAudio, OutputMultichannelBufferType& OutAudio);`
- L85 _private prototype_ `float ProcessChannelAudioInternal(TArrayView<const float> InAudio, TArrayView<float> OutAudio);`
- L86 _private prototype_ `int32 GetNumBufferFramesToProduceOutputFrames(int32 InNumOutputFrames) const;`
- L88 _private member_ `Audio::FAlignedFloatBuffer WorkBuffer;`
- L89 _private member_ `float CurrentInputFrameIndex = 0.f;`
- L90 _private member_ `float CurrentFrameRatio = 1.f;`
- L91 _private member_ `float TargetFrameRatio = 1.f;`
- L92 _private member_ `float FrameRatioFrameDelta = 0.f;`
- L93 _private member_ `int32 NumFramesToInterpolate = 0;`
- L94 _private member_ `int32 NumChannels = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/MultithreadedPatching.h` (Public)


#### struct `Audio::FPatchOutput`  
`struct FPatchOutput`  
_L32-89_
- desc: This class can be thought of as an output for a single constructed instance of FPatchInput. Each FPatchOutput can only be connected to one FPatchInput. To route multiple outputs, see FPatchSplitter. To route multiple inputs, see FPatchMixer. Example usage: FPatchOutputStrongPtr NewOutput(new FPatchOutput(4096)); FPatchInput NewInput(NewOutput); // On one thread, push audio to the output: NewInput.PushAudio(AudioBufferPtr, AudioBufferNumSamples); // and on a seperate thread, retrieve the audio: NewOutput->PopAudio(OutAudioBufferPtr, AudioBufferNumSamples);
- L35 _public prototype_ `FPatchOutput(int32 InMaxCapacity, float InGain = 1.0f);`
- L38 _public prototype_ `FPatchOutput();` — The default constructor will result in an uninitialized, disconnected patch point.
- L40 _public prototype_ `virtual ~FPatchOutput();`
- L43 _public prototype_ `int32 PopAudio(float* OutBuffer, int32 NumSamples, bool bUseLatestAudio);` — Copies the minimum of NumSamples or however many samples are available into OutBuffer. Returns the number of samples copied, or -1 if this output's corresponding input has been destroyed.
- L46 _public prototype_ `int32 MixInAudio(float* OutBuffer, int32 NumSamples, bool bUseLatestAudio);` — Sums the minimum of NumSamples or however many samples are available into OutBuffer. Returns the number of samples summed into OutBuffer.
- L49 _public prototype_ `int32 GetNumSamplesAvailable() const;` — Returns the current number of samples buffered on this output.
- L52 _public prototype_ `int32 GetNumSamplesOverhead() const;` — Returns the amount of space available in this output.
- L55 _public prototype_ `bool WaitUntilNumSamplesAvailable(int32 NumSamples, uint32 TimeOutMilliseconds = MAX_uint32);` — Pauses the current thread until there are the given number of samples available to pop. Will return true if it succeeded, false if it timed out.
- L58 _public prototype_ `bool IsInputStale() const;` — Returns true if the input for this patch has been destroyed.
- L65 _private prototype_ `int32 PushAudioToInternalBuffer(const float* InBuffer, int32 NumSamples);`
- L67 _private prototype_ `void EmptyInternalBuffer();`
- L70 _private member_ `TCircularAudioBuffer<float> InternalBuffer;` — Internal buffer.
- L73 _private member_ `FAlignedFloatBuffer MixingBuffer;` — For MixInAudio, audio is popped off of InternalBuffer onto here, and then mixed into OutBuffer in MixInAudio.
- L76 _private member_ `TAtomic<float> TargetGain;` — This is applied in PopAudio or MixInAudio.
- L77 _private member_ `float PreviousGain;`
- L80 _private member_ `int32 PatchID;` — This is used to breadcrumb the FPatchOutput when we want to delete it.
- L83 _private member_ `std::atomic<int32> NumAliveInputs;` — Counter that is incremented/decremented to allow FPatchInput to be copied around safely.
- L86 _private member_ `std::atomic<FEvent*> SamplesPushedEvent;` — Event to pause the current thread until a given number of samples has been filled
- L88 _private member_ `static TAtomic<int32> PatchIDCounter;`

#### class `Audio::FPatchInput`  
`class FPatchInput`  
_L98-147_
- desc: Handle to a patch. Should only be used by a single thread.
- L102 _public prototype_ `FPatchInput(const FPatchOutputStrongPtr& InOutput);` — PatchInputs can only be created from explicit outputs.
- L103 _public prototype_ `FPatchInput(const FPatchInput& Other);`
- L104 _public prototype_ `FPatchInput& operator=(const FPatchInput& Other);`
- L105 _public prototype_ `FPatchInput& operator=(FPatchInput&& Other);`
- L106 _public prototype_ `FPatchInput(FPatchInput&& Other);`
- L109 _public prototype_ `FPatchInput() = default;` — Default constructed FPatchInput instances will always return -1 for PushAudio and true for IsOutputStillActive.
- L111 _public prototype_ `~FPatchInput();`
- L117 _public prototype_ `int32 PushAudio(const float* InBuffer, int32 NumSamples);` — Pushes audio from InBuffer to the corresponding FPatchOutput. Pushes zeros if InBuffer is nullptr. Returns how many samples were able to be pushed, or -1 if the output was disconnected.
- L120 _public prototype_ `void ClearAudio();` — Clears any audio queued up in the patch.
- L123 _public prototype_ `int32 GetNumSamplesAvailable() const;` — Returns the current number of samples buffered in this input.
- L126 _public prototype_ `int32 GetNumSamplesOverhead() const;` — Returns the amount of space available in this input.
- L128 _public prototype_ `void SetGain(float InGain);`
- L131 _public prototype_ `bool IsOutputStillActive() const;` — Returns false if this output was removed, either because someone called FPatchMixer::RemoveTap with this FPatchInput, or the FPatchMixer was destroyed.
- L134 _public prototype_ `bool IsValid() const;` — Returns false if this output was not initialized properly.
- L136 _public prototype_ `void Reset();`
- L143 _private member_ `FPatchOutputStrongPtr OutputHandle;` — Strong pointer to our destination buffer.
- L146 _private member_ `int32 PushCallsCounter = 0;` — Counter of the number of push calls.

#### class `Audio::FPatchMixer`  
`class FPatchMixer`  
_L154-202_
- desc: This class is used for retrieving and mixing down audio from multiple threads. Important to note that this is MPSC: while multiple threads can enqueue audio on an instance of FPatchMixer using instances of FPatchInput, only one thread can call PopAudio safely.
- L158 _public prototype_ `FPatchInput AddNewInput(int32 MaxLatencyInSamples, float InGain);` — Adds a new input to the tap collector. Calling this is thread safe, but individual instances of FPatchInput are only safe to be used from one thread.
- L161 _public prototype_ `void AddNewInput(const FPatchInput& InPatchInput);` — Adds an existing patch input to the patch mixer.
- L164 _public prototype_ `void RemovePatch(const FPatchInput& InPatchInput);` — Removes a tap from the tap collector. Calling this is thread safe, though FPatchOutput will likely not be deleted until the next call of PopAudio.
- L167 _public prototype_ `int32 PopAudio(float* OutBuffer, int32 OutNumSamples, bool bUseLatestAudio);` — Mixes all inputs into a single buffer. This should only be called from a single thread. Returns the number of non-silent samples popped to OutBuffer.
- L170 _public prototype_ `int32 Num();` — This returns the number of inputs currently connected to this patch mixer. Thread safe, but blocks for PopAudio.
- L173 _public prototype_ `int32 MaxNumberOfSamplesThatCanBePopped();` — This function call gets the maximum number of samples that's safe to pop, based on the thread with the least amount of samples buffered. Thread safe, but blocks for PopAudio.
- L176 _public prototype_ `bool WaitUntilNumSamplesAvailable(int32 NumSamples, uint32 TimeOutMilliseconds = MAX_uint32);` — Pauses the current thread until there are the given number of samples available to pop. Will return true if it succeeded, false if it timed out.
- L179 _public prototype_ `void DisconnectAllInputs();` — Disconnect everything currently connected to this mixer.
- L183 _private prototype_ `void ConnectNewPatches();` — Called within PopAudio. Flushes the PendingNewPatches array into CurrentPatches. During this function, AddNewPatch is blocked.
- L187 _private prototype_ `void CleanUpDisconnectedPatches();` — Called within PopAudio and MaxNumberOfSamplesThatCanBePopped. Removes PendingTapsToDelete from CurrentPatches and ConnectNewPatches. During this function, RemoveTap and AddNewPatch are blocked. Callers of this function must have CurrentPatchesCriticalSection locked.
- L190 _private member_ `TArray<FPatchOutputStrongPtr> PendingNewInputs;` — New taps are added here in AddNewPatch, and then are moved to CurrentPatches in ConnectNewPatches.
- L192 _private member_ `FCriticalSection PendingNewInputsCriticalSection;` — Contended by AddNewPatch, ConnectNewPatches and CleanUpDisconnectedTaps.
- L195 _private member_ `TArray<int32> DisconnectedInputs;` — Patch IDs of individual audio taps that will be removed on the next call of CleanUpDisconnectedPatches.
- L197 _private member_ `FCriticalSection InputDeletionCriticalSection;` — Contended by RemoveTap, AddNewPatch, and ConnectNewPatches.
- L200 _private member_ `TArray<FPatchOutputStrongPtr> CurrentInputs;` — Only accessed within PopAudio. Indirect array of taps that are mixed in during PopAudio.
- L201 _private member_ `FCriticalSection CurrentPatchesCriticalSection;`

#### class `Audio::FPatchSplitter`  
`class FPatchSplitter`  
_L209-239_
- desc: This class is used to post audio from one source to multiple threads. This class is SPMC: multiple threads can call FPatchOutputStrongPtr->PopAudio safely, but only one thread can call PushAudio.
- L216 _public prototype_ `FPatchOutputStrongPtr AddNewPatch(int32 MaxLatencyInSamples, float InGain);` — Adds a new output. Calling this is thread safe, but individual instances of FPatchOutput are only safe to be used from one thread. the returned FPatchOutputPtr can be safely destroyed at any point.
- L219 _public prototype_ `void AddNewPatch(FPatchOutputStrongPtr&& InPatchOutputStrongPtr);` — Adds a new a patch from an existing patch output.
- L220 _public prototype_ `void AddNewPatch(const FPatchOutputStrongPtr& InPatchOutputStrongPtr);`
- L223 _public prototype_ `int32 PushAudio(const float* InBuffer, int32 InNumSamples);` — This call pushes audio to all outputs connected to this splitter. Only should be called from one thread.
- L226 _public prototype_ `int32 Num();` — This returns the number of outputs currently connected to this patch splitter. Thread safe, but blocks for PushAudio.
- L229 _public prototype_ `int32 MaxNumberOfSamplesThatCanBePushed();` — This function call gets the maximum number of samples that's safe to push. Thread safe, but blocks for PushAudio.
- L232 _private prototype_ `void AddPendingPatches();`
- L234 _private member_ `TArray<FPatchInput> PendingOutputs;`
- L235 _private member_ `FCriticalSection PendingOutputsCriticalSection;`
- L237 _private member_ `TArray<FPatchInput> ConnectedOutputs;`
- L238 _private member_ `FCriticalSection ConnectedOutputsCriticalSection;`

#### class `Audio::FPatchMixerSplitter`  
`class FPatchMixerSplitter`  
_L245-275_
- desc: This class is used to mix multiple inputs from disparate threads to a single mixdown and deliver that mixdown to multiple outputs. This class is MPMC, but only one thread can and should call ProcessAudio().
- L252 _public prototype_ `FPatchOutputStrongPtr AddNewOutput(int32 MaxLatencyInSamples, float InGain);` — Adds a new output. Calling this is thread safe, but individual instances of FPatchOutput are only safe to be used from one thread. the returned FPatchOutputPtr can be safely destroyed at any point.
- L255 _public prototype_ `void AddNewOutput(const FPatchOutputStrongPtr& InPatchOutputStrongPtr);` — Adds a new a patch from an existing patch output.
- L258 _public prototype_ `FPatchInput AddNewInput(int32 MaxLatencyInSamples, float InGain);` — Adds a new input to the tap collector. Calling this is thread safe, but individual instances of FPatchInput are only safe to be used from one thread.
- L261 _public prototype_ `void AddNewInput(FPatchInput& InInput);` — Adds a new a patch input from an existing patch input object.
- L264 _public prototype_ `void RemovePatch(const FPatchInput& InInput);` — Removes a tap from the tap collector. Calling this is thread safe, though FPatchOutput will likely not be deleted until the next call of PopAudio.
- L267 _public prototype_ `void ProcessAudio();` — Mixes audio from all inputs and pushes it to all outputs. Should be called regularly.
- L270 _private member_ `FPatchMixer Mixer;`
- L271 _private member_ `FPatchSplitter Splitter;`
- L274 _private member_ `FAlignedFloatBuffer IntermediateBuffer;` — This buffer is used to pop audio from our Mixer and push to our splitter.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Audio`
- L92 _typedef_ `typedef TSharedPtr<FPatchOutput, ESPMode::ThreadSafe> FPatchOutputStrongPtr;` (scope `Audio`) — Patch outputs are owned by the FPatchMixer, and are pinned by the FPatchInput.
- L93 _typedef_ `typedef TWeakPtr<FPatchOutput, ESPMode::ThreadSafe> FPatchOutputWeakPtr;` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/Noise.h` (Public)


#### class `Audio::FWhiteNoise`  
`class FWhiteNoise`  
_L14-33_
- desc: White noise generator Flat spectrum
- L17 _public prototype_ `FWhiteNoise();`
- L18 _public prototype_ `FWhiteNoise(int32 InRandomSeed);`
- L21 _public function_ `inline float Generate()` — Generate next sample of white noise
- L27 _public function_ `inline float Generate(float InScale, float InAdd)` — Generate next sample of white noise (with optional Scale and Add params)
- L32 _private member_ `FRandomStream RandomStream;`

#### class `Audio::FPinkNoise`  
`class FPinkNoise`  
_L39-62_
- desc: Pink noise generator 1/Frequency noise spectrum
- L43 _public prototype_ `FPinkNoise();` — Constructor. Without seed argument, uses Cpu cycles to chose one at "random"
- L46 _public prototype_ `FPinkNoise(int32 InRandomSeed);` — Constructor with seed input
- L49 _public prototype_ `float Generate();` — Generate next sample of pink noise.
- L52 _public function_ `void SetFilterGain(float InFilterGain)` — Set Pink Noise Filter Gain (default -3db)
- L58 _private member_ `FWhiteNoise Noise;`
- L59 _private member_ `float X_Z[4];`
- L60 _private member_ `float Y_Z[4];`
- L61 _private member_ `float A0 = 1.f;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/OnePole.h` (Public)


#### class `Audio::FOnePoleLPF`  
`class FOnePoleLPF`  
_L11-65_
- desc: Simple 1-pole lowpass filter
- L16 _public function_ `FOnePoleLPF() : CutoffFrequency(0.0f) , B1(0.0f) , A0(1.0f) , Z1(0.0f)` — Constructor
- L24 _public function_ `inline void SetG(float InG)` — Set the LPF gain coefficient
- L31 _public function_ `void Reset()` — Resets the sample delay to 0
- L39 _public function_ `inline void SetFrequency(const float InFrequency)` — Sets the filter frequency using normalized frequency (between 0.0 and 1.0f or 0.0 hz and Nyquist Frequency in Hz)
- L49 _public function_ `inline float ProcessAudioSample(const float InputSample)`
- L57 _protected member_ `float CutoffFrequency;`
- L60 _protected member_ `float B1;` — Filter coefficients
- L61 _protected member_ `float A0;`
- L64 _protected member_ `float Z1;` — 1-sample delay

#### class `Audio::FOnePoleLPFBank`  
`class FOnePoleLPFBank`  
_L68-144_
- desc: one pole LPF filter for multiple channels
- L71 _public function_ `FOnePoleLPFBank() : DelayPtr(nullptr) , NumChannels(1) , CutoffFrequency(-1.0f) , B1(0.0f) , A0(1.0f)`
- L82 _public function_ `void Init(int32 InSampleRate, int32 InNumChannels)`
- L93 _public function_ `inline void SetG(float InG)` — Set the LPF gain coefficient
- L100 _public function_ `void ClearMemory()` — Clears memory without reevaluating coefficients. This function is useful when there is a break between ProcessAudio calls.
- L106 _public function_ `void Reset()` — Resets the sample delay to 0
- L114 _public function_ `void SetFrequency(const float InFrequency)` — Sets the filter frequency using normalized frequency (between 0.0 and 1.0f or 0.0 hz and Nyquist Frequency in Hz)
- L125 _public function_ `inline void ProcessAudio(float* InputFrame, float* OutputFrame)`
- L137 _protected member_ `TArray<float> Z1;`
- L138 _protected member_ `float* DelayPtr;`
- L139 _protected member_ `int32 NumChannels;`
- L140 _protected member_ `float CutoffFrequency;`
- L141 _protected member_ `int32 SampleRate;`
- L142 _protected member_ `float B1;`
- L143 _protected member_ `float A0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/Osc.h` (Public)


#### struct `Audio::FOscFrequencyMod`  
`struct FOscFrequencyMod`  
_L13-49_
- desc: Struct which wraps all factors which contribute to pitch of the oscillator
- L16 _public member_ `float Scale;` — A factor which directly scales the frequency output (used for FM modulation)
- L19 _public member_ `float ExternalMod;` — External modulation source
- L22 _public member_ `float Mod;` — The modulated frequency value
- L25 _public member_ `float Detune;` — Exponential frequency modulation
- L28 _public member_ `float PitchBend;` — Pitch bend modulation (i.e. from mod wheel)
- L31 _public member_ `float Octave;` — Octave frequency modulation
- L34 _public member_ `float Semitones;` — Semitones frequency modulation
- L37 _public member_ `float Cents;` — cents frequency modulation
- L39 _public function_ `FOscFrequencyMod() : Scale(1.0f) , ExternalMod(0.0f) , Mod(0.0f) , Detune(0.0f) , PitchBend(0.0f) , Octave(0.0f) , Semitones(0.0f) , Cents(0.0f)`

#### class `Audio::IOscBase`  
`class IOscBase`  
_L52-235_
- desc: Oscillator base class
- L55 _public prototype_ `IOscBase();`
- L56 _public prototype_ `IOscBase(const IOscBase&);`
- L57 _public prototype_ `virtual ~IOscBase();`
- L60 _public prototype_ `virtual void Init(const float InSampleRate, const int32 InVoiceId = 0, FModulationMatrix* InMatrix = nullptr, const int32 ModMatrixStage = 1);` — Initializes the oscillator
- L63 _public prototype_ `virtual void Start() = 0;` — Starts the oscillator
- L66 _public prototype_ `virtual void Stop() = 0;` — Stops the oscillator
- L69 _public prototype_ `virtual float Generate(float* AuxOutput = nullptr) = 0;` — Generates the next sample of audio, optionally passes out the auxillary output (supported in some oscillators)
- L72 _public prototype_ `virtual void Update();` — Updates oscillator state
- L75 _public prototype_ `virtual void Reset();` — Resets the oscillator
- L78 _public prototype_ `virtual void ResetPhase();` — Resets the phase of this oscillator to 0.0f
- L81 _public function_ `void SetGain(const float InGain)` — Sets the gain of the oscillator
- L84 _public function_ `void SetGainMod(const float InGainMod)` — Sets the gain modulator of the oscillator
- L87 _public prototype_ `void SetFrequency(const float InFreqBase);` — Sets the base frequency of the oscillator
- L90 _public prototype_ `void SetFrequencyMod(const float InFreqMod);` — Sets a frequency modulation value
- L93 _public prototype_ `void SetNote(const float InNote);` — Sets the base frequency of the oscillator from the midi note number
- L96 _public function_ `float GetFrequency() const` — Returns the frequency of the oscillator
- L99 _public function_ `float GetGain() const` — Returns the frequency of the oscillator
- L101 _public prototype_ `void SetCents(const float InCents);`
- L102 _public prototype_ `void SetOctave(const float InOctave);`
- L103 _public prototype_ `void SetSampleRate(const float InSampleRate);`
- L104 _public prototype_ `void SetSemitones(const float InSemiTone);`
- L105 _public prototype_ `void SetDetune(const float InDetune);`
- L106 _public prototype_ `void SetPitchBend(const float InPitchBend);`
- L107 _public prototype_ `void SetFreqScale(const float InFreqScale);`
- L110 _public prototype_ `void SetPulseWidth(const float InPulseWidth);` — Sets the LFO pulse width for square-wave type oscillators
- L113 _public function_ `bool IsPlaying() const` — Returns whether or not this oscillator is playing
- L116 _public function_ `bool IsSync() const` — Returns if this oscillator should be synced to a leader oscillator
- L119 _public function_ `void SetSync(const bool bInSync)` — Sets whether or not this oscillator should be synced to a leader oscillator. leader oscillator needs to have set this oscillator as its follower.
- L123 _public prototype_ `void SetSlaveOsc(IOscBase* InSlaveOsc);` — `UE_DEPRECATED(5.1, "SetSlaveOsc is deprecated, please use SetFollowerOsc instead.")` — Deprecated: use SetFollowerOsc
- L126 _public prototype_ `void SetFollowerOsc(IOscBase* InFollowerOsc);` — Sets the input oscillator as the follower of this oscillator
- L129 _public function_ `FPatchDestination GetModDestFrequency() const` — Return patch destinations for various modulatable parameters
- L130 _public function_ `FPatchDestination GetModDestPulseWidth() const`
- L131 _public function_ `FPatchDestination GetModDestGain() const`
- L132 _public function_ `FPatchDestination GetModDestAdd() const`
- L133 _public function_ `FPatchDestination GetModDestScale() const`
- L138 _protected function_ `void UpdatePhase()` — Updates the phase based on the phase increment
- L144 _protected function_ `bool WrapPhase()` — Returns true if there was a phase wrap this update
- L167 _protected function_ `inline float GetPhase() const` — Returns the current phase of the oscillator
- L173 _protected function_ `inline float GetQuadPhase() const` — Returns the quadrature phase, wrapped
- L181 _protected member_ `int32 VoiceId;` — The voice ID that this oscillator belongs to
- L184 _protected member_ `float SampleRate;` — Sample rate of the oscillator
- L187 _protected member_ `float Nyquist;` — Maximum frequency allowed
- L190 _protected member_ `float Freq;` — The final frequency of the oscillator after computing all factors contributing to frequency
- L193 _protected member_ `float BaseFreq;` — The base frequency of the oscillator
- L196 _protected member_ `FOscFrequencyMod FreqData;` — Holds all frequency data
- L199 _protected member_ `float Gain;` — Linear gain of the oscillator
- L202 _protected member_ `float ExternalGainMod;` — Linear gain modulation of the oscillator (used in amplitude modulation)
- L205 _protected member_ `float Phase;` — The current phase of oscillator (between 0.0 and 1.0)
- L208 _protected member_ `float PhaseInc;` — How much to increment the phase each update
- L211 _protected member_ `float PulseWidthBase;` — Pulse width used in square LFOs
- L214 _protected member_ `float PulseWidthMod;` — Pulse width modulator factor
- L217 _protected member_ `float PulseWidth;` — The final pulse width
- L220 _protected member_ `FModulationMatrix* ModMatrix;` — Modulation matrix to use for this oscillator
- L222 _protected member_ `FPatchDestination ModFrequencyDest;`
- L223 _protected member_ `FPatchDestination ModPulseWidthDest;`
- L224 _protected member_ `FPatchDestination ModGainDest;`
- L225 _protected member_ `FPatchDestination ModScaleDest;`
- L226 _protected member_ `FPatchDestination ModAddDest;`
- L229 _protected member_ `IOscBase* FollowerOsc;` — Ptr to a follower oscillator that can be triggered to 0 phase if it is synced.
- L232 _protected member_ `bool bIsPlaying;` — Whether or not the oscillator is on or off
- L233 _protected member_ `bool bChanged;`
- L234 _protected member_ `bool bIsSync;`

#### enum `Audio::EOsc::Type`  
`enum Type`  
_L239-247_
- L241 _public enumerator_ `Sine`
- L242 _public enumerator_ `Saw`
- L243 _public enumerator_ `Triangle`
- L244 _public enumerator_ `Square`
- L245 _public enumerator_ `Noise`
- L246 _public enumerator_ `NumOscTypes`

#### class `Audio::FOsc`  
`class FOsc : public IOscBase`  
_L251-290_
- inherits: `IOscBase`
- desc: Pitched oscillator
- L254 _public prototype_ `FOsc();`
- L255 _public prototype_ `virtual ~FOsc();`
- L258 _public prototype_ `virtual void Start() override;`
- L259 _public prototype_ `virtual void Stop() override;`
- L260 _public prototype_ `virtual void Reset() override;`
- L261 _public prototype_ `virtual void Update() override;`
- L262 _public prototype_ `virtual float Generate(float* AuxOutput = nullptr) override;`
- L266 _public function_ `void SetType(const EOsc::Type InType)` — Sets the oscillator type
- L269 _public function_ `EOsc::Type GetType() const` — Gets the oscillator type
- L274 _protected prototype_ `float PolySmooth(const float InPhase, const float InPhaseInc);` — Smooth out the saw-tooth discontinuities to improve aliasing
- L277 _protected member_ `float TriangleSign;` — Current sign of the square mod, used for triangle wave generation
- L280 _protected member_ `float DPW_z1;` — Used to store state for triangular differentiator
- L283 _protected member_ `FExponentialEase PulseWidthLerped;` — The pulse width base lerped
- L286 _protected member_ `EOsc::Type OscType;` — The type of the oscillator
- L289 _protected member_ `FWhiteNoise Noise;` — a noise generator

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`
- L237 _namespace_ `namespace EOsc` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/ParamInterpolator.h` (Public)


#### class `Audio::FParam`  
`class FParam`  
_L9-75_
- L12 _public function_ `FParam() : CurrentValue(0.0f) , StartingValue(0.0f) , TargetValue(0.0f) , DeltaValue(0.0f) , bIsInit(true)`
- L21 _public function_ `inline void SetValue(const float InValue, const int32 InNumInterpFrames = 0)` — Set the parameter value to the given target value over the given interpolation frames.
- L38 _public function_ `inline void Init()`
- L44 _public function_ `inline void Reset()` — Resets the delta value back to 0.0. To be called at beginning of callback render.
- L51 _public function_ `inline float Update()` — Updates the parameter, assumes called in one of the frames.
- L58 _public function_ `inline float GetValue() const` — Returns the current value, but does not update the value
- L64 _public function_ `inline float GetTarget() const` — Returns the target value
- L70 _private member_ `float CurrentValue;`
- L71 _private member_ `float StartingValue;`
- L72 _private member_ `float TargetValue;`
- L73 _private member_ `float DeltaValue;`
- L74 _private member_ `bool bIsInit;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/PassiveFilter.h` (Public)


#### struct `Audio::FPassiveFilterParams`  
`struct FPassiveFilterParams`  
_L16-50_
- L30 _public member_ `EClass Class;`
- L31 _public member_ `EType Type;`
- L33 _public member_ `int32 Order;`
- L34 _public member_ `float NormalizedCutoffFrequency;`
- L35 _public member_ `float UnitGain;`
- L37 _public member_ `bool bRemoveDC;`
- L38 _public member_ `bool bScaleByOffset;`
- L40 _public function_ `FPassiveFilterParams() : Class(EClass::Butterworth) , Type(EType::Lowpass) , Order(4) , NormalizedCutoffFrequency(0.8f) , UnitGain(1.0f) , bRemoveDC(false) , bScaleByOffset(true)`

#### enum `Audio::FPassiveFilterParams::EClass`  
`enum class EClass`  
_L18-22_
- L20 _public enumerator_ `Butterworth`
- L21 _public enumerator_ `Chebyshev`

#### enum `Audio::FPassiveFilterParams::EType`  
`enum class EType`  
_L24-28_
- L26 _public enumerator_ `Lowpass`
- L27 _public enumerator_ `Highpass`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Audio`
- L52 _function_ `static float EvaluateChebyshevPolynomial(float FrequencyRatio, int32 Order)` (scope `Audio`)
- L97 _function_ `static float GetGainForFrequency(float NormalizedFreq, const FPassiveFilterParams& InParams)` (scope `Audio`)
- L122 _function_ `static void Filter(TArrayView<float>& Signal, const FPassiveFilterParams& InParams)` (scope `Audio`) — This can be called on any TArrayView<float> whose length is a power of 2.
- L191 _function_ `` (scope `Audio::Filter`)
- L222 _function_ `static void Filter(TArray<float>& Signal, const FPassiveFilterParams& InParams)` (scope `Audio`) — Static function for applying a filter to any time series.

### `Source/Runtime/SignalProcessing/Public/DSP/PerlinNoise.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`
- L17 _prototype_ `float PerlinValueNoise1D(const float InX, const int32 InNumOctaves);` (scope `Audio`) — PerlinValueNoise1D. Computes 1 sample of "value" noise using the Perlin 1D function with N octaves. Each "Octave" is a new layer and comes from the doubling of frequencies (through the noise), hence octave. The higher frequencies have less amplitude, creating higher "detail". @param InX: The input "X" Value to hash into Perlin noise space. Time or an "X" coordinate (in the case of 1d) is often used. @param InNumOctaves: The number of octaves (layers) to compute. Each octave has higher frequency and less amplitude. Value needs to be > 0.
- L27 _prototype_ `void PerlinValueNoise1DBuffer(TArrayView<const float> InXBuffer, const float InOffset, const int32 InNumOctaves, TArrayView<float> OutNoiseBuffer);` (scope `Audio`) — PerlinValueNoise1DBuffer. Whole buffer version of Value noise. @param InXBuffer: Buffer to compute value noise on. @param InOffset: Offset each value is offset by. This is normally used to give different results when using multiple calls with the same input. @param InNumOctaves: The number of octaves (layers) to compute. Each octave has higher frequency and less amplitude. @param OutNoiseBuffer: Buffer to write the noise too. Should be as big as the input buffer.

### `Source/Runtime/SignalProcessing/Public/DSP/Phaser.h` (Public)


#### class `Audio::FPhaser`  
`class FPhaser`  
_L13-69_
- L16 _public prototype_ `FPhaser();`
- L17 _public prototype_ `~FPhaser();`
- L19 _public prototype_ `void Init(const float SampleRate, const int32 InNumChannels);`
- L22 _public prototype_ `void SetFrequency(const float InFreqHz);` — Sets the phaser LFO rate
- L25 _public prototype_ `void SetWetLevel(const float InWetLevel);` — Sets the wet level of the phaser
- L28 _public prototype_ `void SetFeedback(const float InFeedback);` — Sets the feedback of the phaser
- L31 _public prototype_ `void SetLFOType(const ELFO::Type LFOType);` — Sets the phaser LFO type
- L34 _public prototype_ `void SetQuadPhase(const bool bQuadPhase);` — Sets whether or not to put the phaser in quadrature mode
- L37 _public prototype_ `void ProcessAudioFrame(const float* InFrame, float* OutFrame);` — Process an audio frame
- L40 _public prototype_ `void ProcessAudio(const float* InBuffer, const int32 InNumSamples, float* OutBuffer);` — Process an audio buffer.
- L43 _protected prototype_ `void ComputeNewCoefficients(const int32 ChannelIndex, const float LFOValue);`
- L46 _protected member_ `static const int32 NumApfs = 6;` — First-order all-pass filters in series
- L47 _protected member_ `static const int32 MaxNumChannels = 2;`
- L49 _protected member_ `int32 ControlSampleCount;`
- L50 _protected member_ `int32 ControlRate;`
- L51 _protected member_ `float Frequency;`
- L52 _protected member_ `float WetLevel;`
- L53 _protected member_ `float Feedback;`
- L54 _protected member_ `ELFO::Type LFOType;`
- L57 _protected member_ `FBiquadFilter APFs[MaxNumChannels][NumApfs];` — 6 APFs per channel
- L58 _protected member_ `FVector2D APFFrequencyRanges[NumApfs];`
- L61 _protected member_ `float FeedbackFrame[MaxNumChannels];` — Feedback samples
- L63 _protected member_ `FLFO LFO;`
- L66 _protected member_ `int32 NumChannels;` — Number of channels actually used
- L68 _protected member_ `bool bIsBiquadPhase;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/Reverb.h` (Public)


#### struct `Audio::FEarlyReflectionsSettings`  
`struct FEarlyReflectionsSettings`  
_L15-39_
- L18 _public member_ `float Gain;` — Early reflections gain
- L21 _public member_ `float PreDelayMsec;` — Delay between input signal and early reflections
- L24 _public member_ `float Bandwidth;` — Input sample bandwidth before entering early reflections
- L27 _public member_ `float Decay;` — Early reflections decay (lower value is longer)
- L30 _public member_ `float Absorption;` — Early reflection high frequency absorption factor
- L32 _public function_ `FEarlyReflectionsSettings() : Gain(1.0f) , PreDelayMsec(0.0f) , Bandwidth(0.8f) , Decay(0.5f) , Absorption(0.7f)`

#### class `Audio::FEarlyReflections`  
`class FEarlyReflections`  
_L42-82_
- desc: Basic implementation of a 4x4 Feedback Delay Network
- L45 _public prototype_ `FEarlyReflections();`
- L46 _public prototype_ `virtual ~FEarlyReflections();`
- L48 _public prototype_ `void Init(const int32 InSampleRate);`
- L51 _public prototype_ `void SetSettings(const FEarlyReflectionsSettings& InSettings);` — Sets the reverb settings, applies, and updates
- L54 _public prototype_ `void ProcessAudioFrame(const float* InBuffer, const int32 InChannels, float* OutBuffer, const int32 OutChannels);` — Process the single audio frame
- L57 _protected prototype_ `void ApplySettings();`
- L58 _protected prototype_ `float ProcessDelayLine(const float InSample, FDelayAPF& InAPF, FOnePoleLPF& InLPF);`
- L60 _protected member_ `FEarlyReflectionsSettings Settings;`
- L78 _protected member_ `float MatrixScaleFactor;`
- L81 _protected member_ `FFDNDelayData Data[2];` — Stereo input/output for early reflections

#### struct `Audio::FEarlyReflections::FFDNDelayData`  
`struct FFDNDelayData`  
_L62-76_
- L65 _public member_ `FDelay PreDelay;` — Pre-Delay for the input audio to the FDN reverberator
- L68 _public member_ `FOnePoleLPF InputLPF;` — Input LPF for early reflections
- L71 _public member_ `FDelayAPF APF[4];` — 4 feedback delay lines per input channel (stereo) which feed into each other using a normalized feedback matrix
- L72 _public member_ `FOnePoleLPF LPF[4];`
- L74 _public member_ `float DelayLineInputs[4];`
- L75 _public member_ `float DelayLineOuputs[4];`

#### struct `Audio::FPlateReverbSettings`  
`struct FPlateReverbSettings`  
_L84-123_
- L87 _public member_ `FEarlyReflectionsSettings EarlyReflections;` — The settings for the early reflections part of the reverb
- L90 _public member_ `float LateDelayMsec;` — Milliseconds for the predelay
- L93 _public member_ `float LateGain;` — Initial attenuation of audio after it leaves the predelay
- L96 _public member_ `float Bandwidth;` — Frequency bandwidth of audio going into input diffusers. 0.999 is full bandwidth
- L99 _public member_ `float Diffusion;` — Amount of input diffusion (larger value results in more diffusion)
- L102 _public member_ `float Dampening;` — The amount of high-frequency dampening in plate feedback paths
- L105 _public member_ `float Decay;` — The amount of decay in the feedback path. Lower value is larger reverb time.
- L108 _public member_ `float Density;` — The amount of diffusion in decay path. Larger values is a more dense reverb.
- L111 _public member_ `float Wetness;` — The amount of output wetness of the reverb as a whole
- L113 _public function_ `FPlateReverbSettings() : LateDelayMsec(0.0f) , LateGain(0.0f) , Bandwidth(0.5f) , Diffusion(0.5f) , Dampening(0.5f) , Decay(0.5f) , Density(0.5f) , Wetness(0.5f)`

#### class `Audio::FPlateReverb`  
`class FPlateReverb`  
_L125-208_
- L128 _public prototype_ `FPlateReverb();`
- L129 _public prototype_ `~FPlateReverb();`
- L132 _public prototype_ `void Init(const int32 InSampleRate);` — Initialize the reverb with the given sample rate
- L135 _public prototype_ `void EnableLateReflections(const bool bInEnableLateReflections);` — Whether or not to enable late reflections
- L138 _public prototype_ `void EnableEarlyReflections(const bool bInEnableEarlyReflections);` — Whether or not to enable late reflections
- L141 _public prototype_ `void SetSettings(const FPlateReverbSettings& InSettings);` — Sets the reverb settings, applies, and updates
- L144 _public prototype_ `void ProcessAudioFrame(const float* InBuffer, const int32 InChannels, float* OutBuffer, const int32 OutChannels);` — Process the single audio frame
- L148 _protected prototype_ `void ApplySettings();`
- L151 _protected member_ `FPlateReverbSettings Settings;` — Current parameter settings of reverb
- L154 _protected member_ `FEarlyReflections EarlyReflections;` — Early reflections effect
- L157 _protected member_ `static const int32 PresetSampleRate = 29761;` — Sample rate used for hard-coded delay line values
- L160 _protected member_ `FDelay PreDelay;` — A simple pre-delay line to emulate large delays for late-reflections
- L163 _protected member_ `FOnePoleLPF InputLPF;` — Input diffusion
- L164 _protected member_ `FDelayAPF APF1;`
- L165 _protected member_ `FDelayAPF APF2;`
- L166 _protected member_ `FDelayAPF APF3;`
- L167 _protected member_ `FDelayAPF APF4;`
- L170 _protected member_ `TSharedPtr<FWaveTableOsc> LFO;` — Wave table oscillator, modulates input APF in plates
- L194 _protected member_ `FPlate LeftPlate;` — The plate data
- L195 _protected member_ `FPlate RightPlate;`
- L198 _protected member_ `static const int32 NumTaps = 7;` — Tap points to read audio from various delay lines in plates
- L200 _protected member_ `float LeftTaps[NumTaps];`
- L201 _protected member_ `float RightTaps[NumTaps];`
- L204 _protected member_ `bool bEnableLateReflections;` — Whether or not late reflections are enabled
- L207 _protected member_ `bool bEnableEarlyReflections;` — Whether or not to enable early reflections

#### struct `Audio::FPlateReverb::FPlate`  
`struct FPlate`  
_L173-191_
- desc: Plate data struction to organize each plate's delay lines and filters
- L175 _public member_ `FDelayAPF ModulatedAPF;`
- L176 _public member_ `FDelay Delay1;`
- L177 _public member_ `FOnePoleLPF LPF;`
- L178 _public member_ `FDelayAPF APF;`
- L179 _public member_ `FDelay Delay2;`
- L182 _public member_ `float PreviousSample;` — Sample output of tank
- L183 _public member_ `float ModulatedBaseDelayMsec;`
- L184 _public member_ `float ModulatedDeltaDelayMsec;`
- L186 _public function_ `FPlate() : PreviousSample(0.0f) , ModulatedBaseDelayMsec(0.0f) , ModulatedDeltaDelayMsec(0.0f)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/ReverbFast.h` (Public)


#### struct `Audio::FPlateReverbFastSettings`  
`struct FPlateReverbFastSettings`  
_L17-52_
- desc: Settings for plate reverb
- L30 _public prototype_ `FPlateReverbFastSettings();`
- L32 _public prototype_ `bool operator==(const FPlateReverbFastSettings& Other) const;`
- L34 _public prototype_ `bool operator!=(const FPlateReverbFastSettings& Other) const;`
- L38 _public member_ `FEarlyReflectionsFastSettings EarlyReflections;` — EarlyReflectionSettings controls the initial perceived echoes from a sound, modeling the first few orders of reflections from a sound source to the listener's ears.
- L42 _public member_ `FLateReflectionsFastSettings LateReflections;` — LateReflectionSettings controls the long tail diffused echo modeling the higher order reflections from a sound source to the listener's ears.
- L45 _public member_ `bool bEnableEarlyReflections;` — Enables / Disables early reflections.
- L48 _public member_ `bool bEnableLateReflections;` — Enables / Disables late reflections.
- L51 _public member_ `EQuadBehavior QuadBehavior;` — Set how reverb module generates reverb when there are 5 or more output channels.

#### enum `Audio::FPlateReverbFastSettings::EQuadBehavior`  
`enum class EQuadBehavior : uint8`  
_L20-28_
- desc: EQuadBehavior describes how reverb is generated when there are 5 or more output channels.
- L23 _public enumerator_ `StereoOnly` — Only produce reverb in front left and front right.
- L25 _public enumerator_ `QuadMatched` — Produce reverb in front left and front right. Copy front left to rear left and front right to rear right.
- L27 _public enumerator_ `QuadFlipped` — Produce reverb in front left and front right. Copy front left to rear right and front right to rear left.

#### class `Audio::FPlateReverbFast`  
`class FPlateReverbFast`  
_L57-104_
- desc: The Plate Reverb emulates the interactions between a sound, the listener and the space they share. Early reflections are modeled using a feedback delay network while late reflections are modeled using a plate reverb. This class aims to support a flexible and pleasant sounding reverb balanced with computational efficiency.
- L59 _public member_ `static const FPlateReverbFastSettings DefaultSettings;`
- L62 _public prototype_ `FPlateReverbFast(float InSampleRate, int32 InMaxInternalBufferSamples = 512, const FPlateReverbFastSettings& InSettings=DefaultSettings);` — InMaxInternalBufferSamples sets the maximum number of samples used in internal buffers.
- L64 _public prototype_ `~FPlateReverbFast();`
- L67 _public prototype_ `void SetSettings(const FPlateReverbFastSettings& InSettings);` — Copies, clamps and applies settings.
- L69 _public prototype_ `const FPlateReverbFastSettings& GetSettings() const;`
- L74 _public prototype_ `void ProcessAudio(const FAlignedFloatBuffer& InSamples, const int32 InNumChannels, FAlignedFloatBuffer& OutSamples, const int32 OutNumChannels);` — Creates reverberated audio in OutSamples based upon InSamples InNumChannels can be 1 or 2 channels. OutSamples must be greater or equal to 2.
- L76 _public prototype_ `void FlushAudio();`
- L79 _public prototype_ `static void ClampSettings(FPlateReverbFastSettings& InOutSettings);` — Clamp individual settings to values supported by this class.
- L83 _private prototype_ `void InterleaveAndMixOutput(const FAlignedFloatBuffer& InFrontLeftSamples, const FAlignedFloatBuffer& InFrontRightSamples, FAlignedFloatBuffer& OutSamples, const int32 OutNumChannels);` — Copy reverberated samples to interleaved output samples. Map channels according to internal settings.
- L85 _private prototype_ `void ApplySettings();`
- L88 _private member_ `float SampleRate;`
- L90 _private member_ `FPlateReverbFastSettings Settings;`
- L91 _private member_ `FEarlyReflectionsFast EarlyReflections;`
- L92 _private member_ `FLateReflectionsFast LateReflections;`
- L94 _private member_ `FAlignedFloatBuffer FrontLeftLateReflectionsSamples;`
- L95 _private member_ `FAlignedFloatBuffer FrontRightLateReflectionsSamples;`
- L96 _private member_ `FAlignedFloatBuffer FrontLeftEarlyReflectionsSamples;`
- L97 _private member_ `FAlignedFloatBuffer FrontRightEarlyReflectionsSamples;`
- L98 _private member_ `FAlignedFloatBuffer FrontLeftReverbSamples;`
- L99 _private member_ `FAlignedFloatBuffer FrontRightReverbSamples;`
- L100 _private member_ `FAlignedFloatBuffer LeftAttenuatedSamples;`
- L101 _private member_ `FAlignedFloatBuffer RightAttenuatedSamples;`
- L102 _private member_ `FAlignedFloatBuffer ScaledInputBuffer;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/RingModulation.h` (Public)


#### class `Audio::FRingModulation`  
`class FRingModulation`  
_L13-58_
- desc: Ring modulation effect https://en.wikipedia.org/wiki/Ring_modulation
- L17 _public prototype_ `FRingModulation();` — Constructor
- L20 _public prototype_ `~FRingModulation();` — Destructor
- L23 _public prototype_ `void Init(const float InSampleRate, const int32 InNumChannels);` — Initialize the equalizer
- L26 _public prototype_ `void SetModulatorWaveType(const EOsc::Type InType);` — The type of modulation
- L29 _public prototype_ `void SetModulationFrequency(const float InModulationFrequency);` — Set the ring modulation frequency
- L32 _public prototype_ `void SetModulationDepth(const float InModulationDepth);` — Set the ring modulation depth
- L35 _public prototype_ `void SetExternalPatchSource(Audio::FPatchOutputStrongPtr InPatch);` — Sets that the modulation buffer is external
- L38 _public function_ `void SetDryLevel(const float InDryLevel)` — Set the dry level of the ring modulation
- L41 _public prototype_ `void SetWetLevel(const float InWetLevel);` — Set the wet level of the ring modulation
- L44 _public prototype_ `void ProcessAudio(const float* InBuffer, const int32 InNumSamples, float* OutBuffer);` — Process audio buffer
- L47 _private prototype_ `void UpdateScale();`
- L49 _private member_ `Audio::FPatchOutputStrongPtr Patch;`
- L50 _private member_ `Audio::FOsc Osc;`
- L51 _private member_ `float ModulationFrequency;`
- L52 _private member_ `float ModulationDepth;`
- L53 _private member_ `float DryLevel;`
- L54 _private member_ `float WetLevel;`
- L55 _private member_ `float Scale;`
- L56 _private member_ `int32 NumChannels;`
- L57 _private member_ `TArray<float> ModulationBuffer;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/RuntimeResampler.h` (Public)


#### class `Audio::FRuntimeResampler`  
`class FRuntimeResampler`  
_L16-142_
- desc: Linear interpolating resampler which supports any number of channels of audio, interleaved or deinterleaved. To support different types of input and output objects, add a new "Process..." method which wraps around calls to ProcessAudioInternal().
- L20 _public member_ `static const float MaxFrameRatio;`
- L21 _public member_ `static const float MinFrameRatio;`
- L27 _public prototype_ `FRuntimeResampler(int32 InNumChannels);` — Construct a linear resampler. @param InNumChannel - Number of audio channels in input and output buffers.
- L36 _public prototype_ `void SetFrameRatio(float InRatio, int32 InNumFramesToInterpolate = 0);` — Sets the number of input frames to read per an output frame. 0.5 is half speed, 1.f is normal speed, 2.0 is double speed. @param InRatio - Ratio of input frames consumed per an output frame produced. @param InNumFramesToInterpolate - Number of output frames over which to interpolate the frame ratio.
- L44 _public prototype_ `int32 GetNumInputFramesNeededToProduceOutputFrames(int32 InNumOutputFrames) const;` — Returns the minimum number of input frames needed to produce the desired number of output frames given the current state of the resampler. @param InNumOutputFrames - The desired number of output frames. @return The minimum number of input frames.
- L52 _public prototype_ `int32 GetNumOutputFramesProducedByInputFrames(int32 InNumInputFrames) const;` — Returns the maximum number of output frames that can be produced from the provided number of input frames given the current state of the resampler. @param InNumInputFrames - The number of provided input frames. @return The maximum number of output frames.
- L66 _public prototype_ `int32 ProcessCircularBuffer(FMultichannelCircularBuffer& InAudio, FMultichannelBuffer& OutAudio);` — Consumes audio from the input buffer and produces audio in the output buffer. The desired number of frames to produce is determined by the output audio buffer size. For the desired number of samples to be produced, the input audio must have the minimum number of frames needed to produce the output frames (see `GetNumInputFramesNeededToProduceOutputFrames(...)`). Input samples which are no longer needed are removed from the input buffer. @param InAudio - Multichannel circular buffer of input audio. @param OutAudio - Multichannel buffer of output audio. FMultichannelBuffer @return Actual number of frames produced.
- L80 _public prototype_ `int32 ProcessCircularBuffer(FMultichannelCircularBuffer& InAudio, FMultichannelBufferView& OutAudio);` — Consumes audio from the input buffer and produces audio in the output buffer. The desired number of frames to produce is determined by the output audio buffer size. For the desired number of samples to be produced, the input audio must have the minimum number of frames needed to produce the output frames (see `GetNumInputFramesNeededToProduceOutputFrames(...)`). Input samples which are no longer needed are removed from the input buffer. @param InAudio - Multichannel circular buffer of input audio. @param OutAudio - Multichannel buffer of output audio. FMultichannelBuffer @return Actual number of frames produced.
- L92 _public prototype_ `void ProcessInterleaved(TArrayView<const float> Input, TArrayView<float> Output, int32& OutNumInputFramesConsumed, int32& OutNumOutputFramesProduced);` — Consumes audio in an interleaved channel format from the input buffer and produces audio in the output buffer. The desired number of frames to produce is determined by the output audio buffer size. For the desired number of samples to be produced, the input audio must have the minimum number of frames needed to produce the output frames (see `GetNumInputFramesNeededToProduceOutputFrames(...)`). @param InAudio - Multichannel interleaved audio to use as input. @param OutAudio - Buffer to receive multichannel interleaved output audio. @param OutNumInputFramesConsumed - Receives the actual number of frames of input consumed. @param OutNumOutputFramesProduced - Receives the actual number of frames of output produced.
- L97 _public prototype_ `void Reset(int32 InNumChannels);` — Reset the internal state of the resampler. Call this if the next audio data to be submitted is unrelated to the audio that has been submitted previously.
- L100 _private prototype_ `int64 MapOutputFrameToInputFrameFP(int32 InOutputFrameIndex) const;`
- L115 _private prototype_ `void ProcessAudioInternal(ResamplingParameters& Parameters);`
- L117 _private prototype_ `void ProcessAudioInBatches(ResamplingParameters& Parameters, int32 MaxSamplesPerBatch);`
- L120 _private prototype_ `bool DoDirectCopy(ResamplingParameters& Parameters);` — Perform a quick memcpy if appropriate rather than resampling. Returns true if the memcpy was performed, false otherwise.
- L122 _private prototype_ `void GenericResamplingCore(const ResamplingParameters& Parameters, int32& OutInputFrameIndexFP, uint32& OutInputFrameRatioFP, int32 OutputSampleIndex, int32 OutputEndIndex);`
- L123 _private prototype_ `void MonoResamplingCore(const float* Input, float* Output, int32& OutInputFrameIndexFP, uint32& OutInputFrameRatioFP, int32 OutputSampleIndex, int32 OutputEndIndex);`
- L124 _private prototype_ `void StereoInterleavedResamplingCore(const float* Input, float* Output, int32& OutInputFrameIndexFP, uint32& OutInputFrameRatioFP, int32 OutputSampleIndex, int32 OutputEndIndex);`
- L125 _private prototype_ `void StereoDeinterleavedResamplingCore(const float* InputLeft, const float* InputRight, float* OutputLeft, float* OutputRight, int32& OutInputFrameIndexFP, uint32& OutInputFrameRatioFP, int32 OutputSampleIndex, int32 OutputEndIndex);`
- L128 _private prototype_ `template<typename OutputBufferType, typename OutputChannelType> int32 ProcessCircularBufferGeneric(FMultichannelCircularBuffer& InAudio, OutputBufferType& OutAudio);`
- L130 _private member_ `static const int32 FPScale;`
- L131 _private member_ `static const float FPScaleFloat;`
- L133 _private member_ `int32 CurrentInputFrameIndexFP = 0;`
- L134 _private member_ `uint32 CurrentFrameRatioFP = 0;`
- L135 _private member_ `uint32 TargetFrameRatioFP = 0;`
- L136 _private member_ `int32 FrameRatioFrameDeltaFP = 0;`
- L137 _private member_ `int32 NumFramesToInterpolate = 0;`
- L139 _private member_ `TArray<float, TInlineAllocator<2>> PreviousFrame;`
- L140 _private member_ `TArray<const float*, TInlineAllocator<2>> TempInputPointers;`
- L141 _private member_ `TArray<float*, TInlineAllocator<2>> TempOutputPointers;`

#### struct `Audio::FRuntimeResampler::ResamplingParameters`  
`struct ResamplingParameters`  
_L102-113_
- L104 _public member_ `TConstArrayView<const float*> InputAudio;`
- L105 _public member_ `int32 InputStride = 0;`
- L106 _public member_ `int32 NumInputFrames = -1;`
- L107 _public member_ `TConstArrayView<float*> OutputAudio;`
- L108 _public member_ `int32 OutputStride = 0;`
- L109 _public member_ `int32 NumOutputFrames = -1;`
- L111 _public member_ `int32 OutNumInputFramesConsumed = 0;`
- L112 _public member_ `int32 OutNumOutputFramesProduced = 0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SIGNALPROCESSING_API`
- L11 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/SampleBufferReader.h` (Public)


#### enum `Audio::ESeekType::Type`  
`enum Type`  
_L13-18_
- L15 _public enumerator_ `FromBeginning`
- L16 _public enumerator_ `FromCurrentPosition`
- L17 _public enumerator_ `FromEnd`

#### class `Audio::FSampleBufferReader`  
`class FSampleBufferReader`  
_L21-105_
- L24 _public prototype_ `FSampleBufferReader();`
- L25 _public prototype_ `~FSampleBufferReader();`
- L27 _public prototype_ `void Init(const int32 InSampleRate);`
- L30 _public prototype_ `void SetBuffer(const int16* InBufferPtr, const int32 InNumBufferSamples, const int32 InNumChannels, const int32 InBufferSampleRate);` — This must be a completely loaded buffer. This buffer reader doesn't OWN the buffer memory.
- L33 _public prototype_ `void SeekTime(const float InTimeSec, const ESeekType::Type InSeekType = ESeekType::FromBeginning, const bool bWrap = true);` — Seeks the buffer the given time in seconds. Returns true if succeeded.
- L36 _public prototype_ `void SetPitch(const float InPitch, const float InterpolationTimeSec = 0.0f);` — Sets the pitch of the buffer reader. Can be negative. Will linearly interpolate over the given time value.
- L39 _public prototype_ `void SetScrubMode(const bool bInIsScrubMode);` — Puts the wave reader into scrub mode
- L42 _public prototype_ `void SetScrubTimeWidth(const float InScrubTimeWidthSec);` — Sets the scrub width. The sound will loop between the scrub width region and the current frame
- L45 _public function_ `int32 GetNumChannels() const` — Returns the number of channels of this buffer.
- L48 _public function_ `int32 GetNumFrames() const` — Returns the number of frames of the buffer.
- L51 _public function_ `float GetPlaybackProgress() const` — Returns the current playback position in seconds
- L54 _public prototype_ `bool Generate(float* OutAudioBuffer, const int32 NumFrames, const int32 OutChannels, const bool bWrap = false);` — Generates the next block of audio. Returns true if it's no longer playing (reached end of the buffer and not set to wrap)
- L57 _public function_ `bool HasBuffer() const` — Whether or not the buffer reader has a buffer
- L60 _public prototype_ `void ClearBuffer();` — Clears current buffer and resets state
- L64 _protected prototype_ `float GetSampleValueForChannel(const int32 Channel);`
- L65 _protected prototype_ `void UpdateScrubMinAndMax();`
- L66 _protected prototype_ `void UpdateSeekFrame();`
- L67 _protected prototype_ `float GetSampleValue(const int16* InBuffer, const int32 SampleIndex);`
- L69 _protected member_ `const int16* BufferPtr;`
- L70 _protected member_ `int32 BufferNumSamples;`
- L71 _protected member_ `int32 BufferNumFrames;`
- L72 _protected member_ `int32 BufferSampleRate;`
- L73 _protected member_ `int32 BufferNumChannels;`
- L74 _protected member_ `int32 FadeFrames;`
- L75 _protected member_ `float FadeValue;`
- L76 _protected member_ `float FadeIncrement;`
- L78 _protected member_ `float DeviceSampleRate;`
- L81 _protected member_ `float BasePitch;` — The current frame alpha
- L82 _protected member_ `float PitchScale;`
- L83 _protected member_ `Audio::FLinearEase Pitch;`
- L85 _protected member_ `int32 CurrentFrameIndex;`
- L86 _protected member_ `int32 NextFrameIndex;`
- L87 _protected member_ `double AlphaLerp;`
- L89 _protected member_ `double CurrentBufferFrameIndexInterpolated;`
- L91 _protected member_ `float PlaybackProgress;`
- L93 _protected member_ `double ScrubAnchorFrame;`
- L94 _protected member_ `double ScrubMinFrame;`
- L95 _protected member_ `double ScrubMaxFrame;`
- L97 _protected member_ `double ScrubWidthFrames;`
- L98 _protected member_ `float CurrentSeekTime;`
- L99 _protected member_ `float CurrentScrubWidthSec;`
- L101 _protected member_ `ESeekType::Type CurrentSeekType;`
- L102 _protected member_ `bool bWrap;`
- L103 _protected member_ `bool bIsScrubMode;`
- L104 _protected member_ `bool bIsFinished;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L11 _namespace_ `namespace ESeekType` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/SampleRateConverter.h` (Public)


#### class `Audio::ISampleRateConverter`  
`class ISampleRateConverter`  
_L9-43_
- L12 _public prototype_ `virtual ~ISampleRateConverter() = default;`
- L14 _public prototype_ `virtual void Init(const float InSampleRateRatio, const int32 InNumChannels) = 0;`
- L17 _public prototype_ `virtual void SetSampleRateRatio(const float InSampleRateRatio, const int32 NumInterpolationFrames = 0) = 0;` — Sets the sample rate ratio and the number of frames to interpolate from the current sample rate ratio
- L26 _public prototype_ `virtual int32 ProcessFullbuffer(const int16* InBuffer, const int32 InNumSamples, TArray<float>& OutBuffer) = 0;` — Given an input buffer, the output buffer is fully sample-rate converted. @param	InBuffer		Input audio buffer @param	InNumSamples	Number of input samples. @param  OutBuffer		The output buffer of converted audio. @return Number of frames generated.
- L27 _public prototype_ `virtual int32 ProcessFullbuffer(const float* InBuffer, const int32 InNumSamples, TArray<float>& OutBuffer) = 0;`
- L38 _public prototype_ `virtual int32 ProcessChunk(const int16* BufferChunk, const int32 NumInputSamples, const int32 RequestedFrames, TArray<float>& OutBuffer) = 0;` — Process chunks of audio at a time. Saves state so can properly handle buffer boundaries. Use with Reset() to reset internal state before starting realtime SRC. @param	BufferChunk		Input audio buffer chunk @param	NumInputSamples	Number of input samples. @param	RequestedFrames	Number of frames requested to process @param  OutBuffer		The output buffer of converted audio. @return Number of frames generated.
- L39 _public prototype_ `virtual int32 ProcessChunk(const float* BufferChunk, const int32 NumInputSamples, const int32 RequestedFrames, TArray<float>& OutBuffer) = 0;`
- L42 _public prototype_ `static ISampleRateConverter* CreateSampleRateConverter();` — Creates a new instance

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/SinOsc.h` (Public)


#### class `Audio::FSineOsc`  
`class FSineOsc`  
_L16-55_
- desc: FOsc Direct-form sinusoid oscillator. Created with a biquad filter (using only feedback coefficients) with poles directly on unit circle in z-plane. Setting frequency uses current filter state to compute initial conditions to avoid pops when changing frequency. Extremely cheap to run but expensive to set new frequencies. Good for test tones.
- L20 _public prototype_ `FSineOsc();` — Constructor
- L23 _public prototype_ `FSineOsc(const int32 InSampleRate, const float InFrequencyHz, const float Scale = 1.0f, const float Add = 0.0f);` — Non-default constructor
- L26 _public prototype_ `virtual ~FSineOsc();` — Virtual destructor
- L29 _public prototype_ `void Init(const int32 InSampleRate, const float InFrequencyHz, const float Scale = 1.0f, const float Add = 0.0f);` — Initialize the oscillator with a sample rate and new frequency. Must be called before playing oscillator.
- L32 _public prototype_ `void SetScale(const float InScale);` — Sets the scale of the oscillator.
- L35 _public prototype_ `void SetAdd(const float InAdd);` — Sets the scale of the oscillator.
- L38 _public prototype_ `void SetFrequency(const float InFrequencyHz);` — Sets the frequency of the oscillator in Hz (based on sample rate). Performs initial condition calculation to avoid pops.
- L41 _public prototype_ `float GetFrequency() const;` — Returns the current frequency.
- L44 _public prototype_ `float ProcessAudio();` — Generates the next sample of the oscillator.
- L47 _protected member_ `int32 SampleRate;`
- L48 _protected member_ `float FrequencyHz;`
- L49 _protected member_ `float B1;` — Biquad feedback coefficients
- L50 _protected member_ `float B2;`
- L51 _protected member_ `float Yn_1;` — y(n - 1)
- L52 _protected member_ `float Yn_2;` — y(n - 2)
- L53 _protected member_ `float Scale;`
- L54 _protected member_ `float Add;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/SineWaveTableOsc.h` (Public)


#### class `Audio::FSineWaveTableOsc`  
`class FSineWaveTableOsc`  
_L13-69_
- desc: A sinusoidal wave table oscillator class
- L17 _public prototype_ `FSineWaveTableOsc();` — Constructor
- L20 _public prototype_ `virtual ~FSineWaveTableOsc();` — Virtual Destructor
- L23 _public prototype_ `void Init(const float InSampleRate, const float InFrequencyHz, const float InPhase);` — Initialize the wave table oscillator
- L26 _public prototype_ `void SetSampleRate(const float InSampleRate);` — Sets the sample rate of the oscillator.
- L29 _public prototype_ `void Reset();` — Resets the wave table read indices.
- L32 _public prototype_ `void SetFrequencyHz(const float InFrequencyHz);` — Sets the frequency of the wave table oscillator.
- L35 _public function_ `float GetFrequencyHz() const` — Returns the frequency of the wave table oscillator.
- L38 _public prototype_ `void SetPhase(const float InPhase);` — Sets the phase of the wave table oscillator.
- L41 _public prototype_ `void Generate(float* OutBuffer, const int32 NumSamples);` — Processes the wave table and fills a buffer
- L44 _public prototype_ `static const TArray<float>& GetWaveTable();` — The static sinusoidal wave table
- L47 _protected prototype_ `void UpdatePhaseIncrement();`
- L50 _protected member_ `const TArray<float>& WaveTableBuffer = GetWaveTable();` — The wave table buffer
- L53 _protected member_ `float FrequencyHz = 440.0f;` — The frequency of the output (given the sample rate)
- L56 _protected member_ `float SampleRate = 48000.0f;` — The sample rate of the oscillator
- L59 _protected member_ `float ReadIndex = 0.0f;` — Read index
- L62 _protected member_ `float PhaseIncrement = 0.0f;` — The phase increment (based on frequency)
- L65 _protected member_ `float InitialPhase = 0.0f;` — The initial/cached phase, will be clamped to range 0.0 - 1.0f
- L68 _protected member_ `float InstantaneousPhase = 0.0f;` — The instantaneous phase, clamped to range 0.0 - 1.0f

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/SlidingWindow.h` (Public)


#### class `Audio::TSlidingBuffer`  
`template <typename InSampleType> class TSlidingBuffer`  
_L27-181_
- desc: TSlidingBuffer TSlidingBuffer defines the window size and hop size of the sliding window, and it stores any samples needed to produce additional windows. TSlidingBuffer should be used in conjunction with the TSlidingWindow, TScopedSlidingWindow or TAutoSlidingWindow classes.
- L34 _public function_ `TSlidingBuffer(const int32 InNumWindowSamples, const int32 InNumHopSamples) : NumWindowSamples(InNumWindowSamples) , NumHopSamples(InNumHopSamples) , NumUnderflowSamples(0)` — Constructs a TSlidingBuffer with a constant window and hop size
- L43 _public function_ `TSlidingBuffer() : TSlidingBuffer(1, 1)`
- L48 _public prototype_ `TSlidingBuffer(const TSlidingBuffer&) = default;`
- L49 _public prototype_ `TSlidingBuffer(TSlidingBuffer&&) = default;`
- L51 _public prototype_ `TSlidingBuffer& operator=(const TSlidingBuffer& InOther) = default;`
- L52 _public prototype_ `TSlidingBuffer& operator=(TSlidingBuffer&& InOther) = default;`
- L55 _public function_ `int32 GetNumWindowSamples() const` — Returns the number of samples in a window.
- L61 _public function_ `int32 GetNumHopSamples() const` — Returns the number of samples between windows.
- L67 _public function_ `int32 GetNumUnderflowSamples() const` — Returns the number of underflow samples (when hopsize > windowsize)
- L72 _public function_ `TArrayView<const InSampleType> GetStorage() const`
- L82 _public function_ `void StoreForFutureWindows(TArrayView<const InSampleType> InBuffer)` — StoreForFutureWindows stores the necessary samples from InBuffer which will be needed for future windows. It ignores all values in InBuffer which can already be composed as a complete window.
- L162 _public function_ `void Reset()` — Resets the internal storage.
- L170 _private member_ `int32 NumWindowSamples;` — NumWindowSamples describes the number of samples in a window.
- L173 _private member_ `int32 NumHopSamples;` — NumHopSamples describes the number of samples between adjacent windows.
- L176 _private member_ `TArray<InSampleType> StorageBuffer;` — Stores samples from previous calls which are still needed for future buffers
- L180 _private member_ `int32 NumUnderflowSamples;` — When HopSize is greater than WindowSize a situation can occur where we need to account for hop samples that we have not yet ingested.

#### class `Audio::TSlidingWindow`  
`template <typename InSampleType> class TSlidingWindow`  
_L189-403_
- desc: TSlidingWindow TSlidingWindow allows windows of samples to be iterated over with STL like iterators.
- L195 _protected member_ `TArrayView<const InSampleType> StorageBuffer;` — Accessed from friendship with TSlidingBuffer
- L198 _protected member_ `TArrayView<const InSampleType> NewBuffer;` — New buffer passed in.
- L201 _protected member_ `const int32 NumWindowSamples;` — Copied from TSlidingBuffer
- L204 _protected member_ `const int32 NumHopSamples;` — Copied from TSlidingBuffer
- L208 _private member_ `int32 MaxReadIndex;`
- L209 _private member_ `int32 NumUnderflowSamples;`
- L333 _public function_ `TSlidingWindow(const TSlidingBuffer<InSampleType>& InSlidingBuffer, TArrayView<const InSampleType> InNewBuffer, bool bDoFlush) : StorageBuffer(InSlidingBuffer.GetStorage()) , NewBuffer(InNewBuffer) , NumWindowSamples(InSlidingBuffer.GetNumWindowSamples()) , NumHopSamples(InSlidingBuffer.GetNumHopSamples()) , MaxReadIndex(0) , NumUnderflowSamples(InSlidingBuffer.GetNumUnderflowSamples())` — TSlidingWindow constructor InSlidingBuffer Holds the previous samples which were not completely used in previous sliding windows.  It also defines the window and hop size. InNewBuffer Holds new samples which have not yet been ingested by the InSlidingBuffer. bDoFlush Controls whether zeros to the final output windows until all possible windows with data from InNewBuffer have been covered.
- L375 _public prototype_ `virtual ~TSlidingWindow() = default;`
- L383 _public function_ `template<typename InAllocator = FDefaultAllocator> TSlidingWindowIterator<InAllocator> begin(TArray<InSampleType, InAllocator>& OutWindowBuffer) const` — Creates STL like iterator which slides over samples. OutWindowBuffer Used to construct the TSlidingWindowIterator. The iterator will populate the window with samples when the * operator is called.
- L399 _public function_ `template<typename InAllocator = FDefaultAllocator> TSlidingWindowIterator<InAllocator> end(TArray<InSampleType, InAllocator>& OutWindowBuffer) const` — Creates STL like iterator denotes the end of the sliding window. OutWindowBuffer Used to construct the TSlidingWindowIterator. The iterator will populate the window with samples when the * operator is called.

#### class `Audio::TSlidingWindow::TSlidingWindowIterator`  
`template<typename InAllocator = FDefaultAllocator> class TSlidingWindowIterator`  
_L218-324_
- desc: TSlidingWindowIterator An forward iterator which slides a window over the given buffers.
- L220 _private member_ `const TSlidingWindow SlidingWindow;`
- L223 _private member_ `TArray<InSampleType, InAllocator>& WindowBuffer;` — Samples in window will be copied into this array.
- L226 _private member_ `int32 ReadIndex;` — Index into array for reading out data.
- L231 _public member_ `static const int32 ReadIndexEnd = INDEX_NONE;` — Sentinel value marking that the last possible window has been generated.
- L236 _public function_ `TSlidingWindowIterator(const TSlidingWindow& InSlidingWindow, TArray<InSampleType, InAllocator>& OutWindowBuffer, int32 InReadIndex) : SlidingWindow(InSlidingWindow) , WindowBuffer(OutWindowBuffer) , ReadIndex(InReadIndex)` — Construct an iterator over a sliding window.
- L250 _public function_ `TSlidingWindowIterator operator++()` — Increment sliding window iterator forward.
- L268 _public function_ `bool operator!=(const TSlidingWindowIterator& Other) const` — Check whether iterators are equal. TSlidingWindowIterators derived from different TSlidingWindows should not be compared.
- L276 _public function_ `TArray<InSampleType, InAllocator>& operator*()` — Access array of windowed data currently pointed to by iterator.

#### class `Audio::TScopedSlidingWindow`  
`template <class InSampleType> class TScopedSlidingWindow : public TSlidingWindow<InSampleType>`  
_L412-442_
- inherits: `TSlidingWindow<InSampleType>`
- desc: TScopedSlidingWindow TScopedSlidingWindow provides a sliding window iterator interface over arrays. When TScopedSlidingWindow is destructed, it calls StoreForFutureWindow(...) on the TSlidingBuffer passed into the constructor.
- L415 _private prototype_ `TScopedSlidingWindow(TScopedSlidingWindow const &) = delete;` — Do not allow copying or moving since that may cause the destructor to be called inadvertently.
- L416 _private prototype_ `void operator=(TScopedSlidingWindow const &) = delete;`
- L417 _private prototype_ `TScopedSlidingWindow(TScopedSlidingWindow&&) = delete;`
- L418 _private prototype_ `TScopedSlidingWindow& operator=(TScopedSlidingWindow&&) = delete;`
- L420 _private member_ `TSlidingBuffer<InSampleType>& SlidingBuffer;`
- L430 _public function_ `TScopedSlidingWindow(TSlidingBuffer<InSampleType>& InSlidingBuffer, TArrayView<const InSampleType> InNewBuffer, bool bDoFlush = false) : TSlidingWindow<InSampleType>(InSlidingBuffer, InNewBuffer, bDoFlush) , SlidingBuffer(InSlidingBuffer)` — TScopedSlidingWindow constructor InSlidingBuffer Holds the previous samples which were not completely used in previous sliding windows.  It also defines the window and hop size. InNewBuffer Holds new samples which have not yet been ingested by the InSlidingBuffer. bDoFlush Controls whether zeros to the final output windows until all possible windows with data from InNewBuffer have been covered.
- L438 _public function_ `virtual ~TScopedSlidingWindow()` — Calls InSlidingBuffer.StoreForFutureWindows(InNewBuffer).

#### class `Audio::TAutoSlidingWindow`  
`template <typename InSampleType, typename InAllocator = FDefaultAllocator> class TAutoSlidingWindow : public TScopedSlidingWindow<InSampleType>`  
_L477-516_
- inherits: `TScopedSlidingWindow<InSampleType>`
- desc: TAutoSlidingWindow TAutoSlidingWindow enables use of a sliding window within a range-based for loop. Example: void ProcessAudio(TSlidingBuffer<float>& SlidingBuffer, const TArray<float>& NewSamples) { TArray<float> WindowData; TAutoSlidingWindow<float> SlidingWindow(SlidingBuffer, NewSamples, WindowData); for (TArray<float>& Window : SlidingWindow) { ... audio processing on single window here } } int main() { int32 NumWindowSamples = 4; int32 NumHopSamples = 2; TSlidingBuffer<float> SlidingBuffer(NumWindowSamples, NumHopSamples); TArray<float> Buffer1({1, 2, 3, 4, 5, 6, 7}); ProcessAudio(SlidingBuffer, Buffer1); TArray<float> Buffer2({8, 9, 10, 11}); ProcessAudio(SlidingBuffer, Buffer2); }
- L479 _private member_ `TArray<InSampleType, InAllocator>& WindowBuffer;`
- L481 _private typedef_ `typedef typename TSlidingWindow<InSampleType>::template TSlidingWindowIterator<InAllocator> TAutoSlidingWindowIterator;`
- L492 _public function_ `TAutoSlidingWindow(TSlidingBuffer<InSampleType>& InBuffer, TArrayView<const InSampleType> InNewBuffer, TArray<InSampleType, InAllocator>& OutWindow, bool bDoFlush = false) : TScopedSlidingWindow<InSampleType>(InBuffer, InNewBuffer, bDoFlush) , WindowBuffer(OutWindow)` — TAutoSlidingWindow constructor InSlidingBuffer Holds the previous samples which were not completely used in previous sliding windows.  It also defines the window and hop size. InNewBuffer Holds new samples which have not yet been ingested by the InSlidingBuffer. OutWindow is shared by all iterators created by calling begin() or end(). bDoFlush Controls whether zeros to the final output windows until all possible windows with data from InNewBuffer have been covered.
- L502 _public function_ `TAutoSlidingWindowIterator begin()` — Creates STL like iterator which slides over samples. This iterator maintains a reference to the OutWindow passed into the constructor. That array will be manipulated when the iterator's * operator is called.
- L512 _public function_ `TAutoSlidingWindowIterator end()` — Creates STL like iterator denotes the end of the sliding window. This iterator maintains a reference to the OutWindow passed into the constructor. That array will be manipulated when the iterator's * operator is called.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/SpectrumAnalyzer.h` (Public)


#### struct `Audio::FSpectrumAnalyzerSettings`  
`struct FSpectrumAnalyzerSettings`  
_L17-48_
- L32 _public member_ `EWindowType WindowType;`
- L33 _public member_ `EFFTSize FFTSize;`
- L41 _public member_ `float HopSize;` — Hop size as a percentage of FFTSize. 1.0 indicates a full hop. Keeping this as 0.0 will use whatever hop size can be used for WindowType to maintain COLA.
- L43 _public function_ `FSpectrumAnalyzerSettings() : WindowType(EWindowType::Hann) , FFTSize(EFFTSize::Default) , HopSize(0.0f)`

#### enum `Audio::FSpectrumAnalyzerSettings::EFFTSize`  
`enum class EFFTSize : uint16`  
_L20-30_
- desc: Actual FFT size used. For FSpectrumAnalyzer, we never zero pad the input buffer.
- L22 _public enumerator_ `Default = 512`
- L23 _public enumerator_ `TestingMin_8 = 8`
- L24 _public enumerator_ `Min_64 = 64`
- L25 _public enumerator_ `Small_256 = 256`
- L26 _public enumerator_ `Medium_512 = 512`
- L27 _public enumerator_ `Large_1024 = 1024`
- L28 _public enumerator_ `VeryLarge_2048 = 2048`
- L29 _public enumerator_ `TestLarge_4096 = 4096`

#### struct `Audio::FSpectrumBandExtractorSettings`  
`struct FSpectrumBandExtractorSettings`  
_L52-94_
- desc: Settings for band extractor.
- L69 _public member_ `EMetric Metric = EMetric::Decibel;` — Metric used to calculate return value.
- L73 _public member_ `float DecibelNoiseFloor = -40.f;` — If the metric is Decibel, this is the minimum decibel value allowed.
- L81 _public member_ `bool bDoNormalize = true;` — If true, all values are scaled and clamped between 0.0 and 1.f. In the case of Decibels, 0.0 corresponds to the decibel noise floor and 1.f to 0dB. If bDoAutoRange is true, then values are relatively to recent maximum and minimums regardless of the metric used.
- L87 _public member_ `bool bDoAutoRange = true;` — If true and bDoNormalize is true, then values will be scaled between 0 and 1 based upon relatively recent minimum and maximum values.
- L90 _public member_ `float AutoRangeReleaseTimeInSeconds = 30.f;` — Time in seconds for autorange to reach 99% of a smaller range.
- L93 _public member_ `float AutoRangeAttackTimeInSeconds = 1.f;` — Time in seconds for autorange to reach 99% of a larger range.

#### enum `Audio::FSpectrumBandExtractorSettings::EMetric`  
`enum class EMetric : uint8`  
_L55-66_
- desc: Metric for output band values.
- L58 _public enumerator_ `Magnitude` — Return the magnitude spectrum value.
- L61 _public enumerator_ `Power` — Return the power spectrum value.
- L65 _public enumerator_ `Decibel` — Return the decibel spectrum value. Decibels are calculated with 0dB equal to 1.f magnitude.

#### struct `Audio::FSpectrumBandExtractorSpectrumSettings`  
`struct FSpectrumBandExtractorSpectrumSettings`  
_L97-133_
- desc: Settings describing the spectrum used for in the band extractor.
- L100 _public member_ `float SampleRate;` — Sample rate of audio
- L103 _public member_ `int32 FFTSize;` — Size of fft used in spectrum analyzer
- L106 _public member_ `EFFTScaling FFTScaling;` — Forward scaling of FFT used in spectrum analyzer
- L109 _public member_ `EWindowType WindowType;` — Window used when perform FFT
- L111 _public function_ `FSpectrumBandExtractorSpectrumSettings() : SampleRate(48000.f) , FFTSize(1024) , FFTScaling(EFFTScaling::None) , WindowType(EWindowType::None)`
- L119 _public function_ `bool operator==(const FSpectrumBandExtractorSpectrumSettings& Other) const` — Compare whether two settings structures are equal.
- L129 _public function_ `bool operator!=(const FSpectrumBandExtractorSpectrumSettings& Other) const` — Compare whether two settings structures are not equal.

#### class `Audio::ISpectrumBandExtractor`  
`class ISpectrumBandExtractor`  
_L142-204_
- desc: Interface for spectrum band extractors. The SpectrumBandExtractor allows for band information to be maintained across multiple calls to retrieve bands values. By maintaining band information across multiple calls, some intermediate values can be cached to speed up the operation.
- L177 _public prototype_ `virtual ~ISpectrumBandExtractor() = default;`
- L180 _public prototype_ `virtual void SetSettings(const FSpectrumBandExtractorSettings& InSettings) = 0;` — Sets and updates the settings for the band extractor
- L183 _public prototype_ `virtual void SetSpectrumSettings(const FSpectrumBandExtractorSpectrumSettings& InSettings) = 0;` — Set the settings and update cached internal values if needed
- L186 _public prototype_ `virtual void RemoveAllBands() = 0;` — Removes all added bands.
- L189 _public prototype_ `virtual int32 GetNumBands() const = 0;` — Returns the total number of bands.
- L192 _public prototype_ `virtual void AddBand(const FBandSettings& InSettings) = 0;` — Adds a band to extract based on the given settings.
- L200 _public prototype_ `virtual void ExtractBands(const FAlignedFloatBuffer& InComplexBuffer, double InTimestamp, TArray<float>& OutValues) = 0;` — Extract the bands from a complex frequency buffer. @param InComplexBuffer - Buffer of complex frequency data from a FFT. @param InTimestamp - A timestamp associated with the input complex buffer. @param OutValues - Array to store output bands.
- L203 _public prototype_ `static TUniquePtr<ISpectrumBandExtractor> CreateSpectrumBandExtractor(const FSpectrumBandExtractorSettings& InSettings);` — Creates a ISpectrumBandExtractor.

#### enum `Audio::ISpectrumBandExtractor::EBandType`  
`enum class EBandType : uint8`  
_L146-159_
- L149 _public enumerator_ `NearestNeighbor` — Look up band value via nearest FFT band.
- L152 _public enumerator_ `Lerp` — Band value is calculated by lerping between FFT bands adjacent to center frequency.
- L155 _public enumerator_ `Quadratic` — Band value is calculated by fitting quadratic to 3 adjancent FFT bands and solving for center frequency.
- L158 _public enumerator_ `ConstantQ` — Band value is calculated by a weighted sum of a window of fft bands around center frequency. The window size is determined by the QFactor of the band.

#### struct `Audio::ISpectrumBandExtractor::FBandSettings`  
`struct FBandSettings`  
_L162-175_
- desc: Settings for a single band
- L165 _public member_ `EBandType Type = EBandType::ConstantQ;` — Type of band to extract.
- L168 _public member_ `float CenterFrequency = 0.f;` — Frequency of interest in hz.
- L174 _public member_ `float QFactor = 10.0f;` — QFactor is only applicable for the ConstantQ band type. QFactor = CenterFreq / BandWidth. Eg. A small QFactor results in a wide band.

#### class `Audio::FSpectrumAnalyzerBuffer`  
`class FSpectrumAnalyzerBuffer`  
_L210-246_
- desc: This class locks an input buffer (for writing) and an output buffer (for reading). Uses triple buffering semantics.
- L213 _public prototype_ `FSpectrumAnalyzerBuffer();`
- L214 _public prototype_ `FSpectrumAnalyzerBuffer(int32 InNum);`
- L216 _public prototype_ `void Reset(int32 InNum);`
- L219 _public prototype_ `FAlignedFloatBuffer& StartWorkOnBuffer();` — Input. Used on analysis thread to lock a buffer to write to.
- L222 _public prototype_ `void StopWorkOnBuffer(double InTimestamp);` — When calling stop work on buffer, also set timestmap associated with buffer.
- L225 _public prototype_ `const FAlignedFloatBuffer& LockMostRecentBuffer() const;` — Output. Used to lock the most recent buffer we analyzed.
- L229 _public prototype_ `const FAlignedFloatBuffer& LockMostRecentBuffer(double& OutTimestamp) const;` — Output. Used to lock the most recent buffer we analyzed. OutTimestamp is populated with the timestamp associated with the buffer wehn StopWorkOnBuffer is called.
- L230 _public prototype_ `void UnlockBuffer();`
- L233 _private member_ `TArray<FAlignedFloatBuffer> ComplexBuffers;`
- L234 _private member_ `TArray<double> Timestamps;`
- L238 _private prototype_ `void IncrementInputIndex();` — Private functions. Either increments or decrements the respective counter, based on which index is currently in use. Mutually locked.
- L239 _private prototype_ `void IncrementOutputIndex();`
- L241 _private member_ `int32 OutputIndex;`
- L242 _private member_ `int32 InputIndex;`
- L245 _private member_ `mutable FCriticalSection BufferIndicesCriticalSection;` — This mutex is locked when we increment either the input or output index.

#### class `Audio::FSpectrumAnalysisAsyncWorker`  
`class FSpectrumAnalysisAsyncWorker`  
_L248-280_
- L252 _public function_ `FSpectrumAnalysisAsyncWorker(TWeakPtr<FSpectrumAnalyzer, ESPMode::ThreadSafe> InAnalyzer, bool bInUseLatestAudio) : AnalyzerWeakPtr(InAnalyzer) , bUseLatestAudio(bInUseLatestAudio) , bIsAbandoned(false)`
- L258 _public function_ `inline TStatId GetStatId() const`
- L263 _public prototype_ `void DoWork();`
- L265 _public function_ `bool CanAbandon()`
- L270 _public prototype_ `void Abandon();`
- L273 _private prototype_ `FSpectrumAnalysisAsyncWorker() = delete;`
- L275 _private member_ `TWeakPtr<FSpectrumAnalyzer, ESPMode::ThreadSafe> AnalyzerWeakPtr;`
- L276 _private member_ `bool bUseLatestAudio;`
- L277 _private member_ `bool bIsAbandoned;`
- L279 _private member_ `FCriticalSection NonAbandonableSection;`

#### class `Audio::FSpectrumAnalyzer`  
`class FSpectrumAnalyzer`  
_L290-386_
- desc: Class built to be a rolling spectrum analyzer for arbitrary, monaural audio data. Class is meant to scale accuracy with CPU and memory budgets. Typical usage is to either call PushAudio() and then PerformAnalysisIfPossible immediately afterwards, or have a separate thread call PerformAnalysisIfPossible().
- L304 _public prototype_ `FSpectrumAnalyzer();` — If an instance is created using the default constructor, Init() must be called before it is used.
- L307 _public prototype_ `FSpectrumAnalyzer(float InSampleRate);` — If an instance is created using either of these constructors, Init() is not neccessary.
- L308 _public prototype_ `FSpectrumAnalyzer(const FSpectrumAnalyzerSettings& InSettings, float InSampleRate);`
- L310 _public prototype_ `virtual ~FSpectrumAnalyzer() = default;`
- L313 _public prototype_ `void Init(float InSampleRate);` — Initialize sample rate of analyzer if not known at time of construction
- L314 _public prototype_ `void Init(const FSpectrumAnalyzerSettings& InSettings, float InSampleRate);`
- L317 _public prototype_ `void SetSettings(const FSpectrumAnalyzerSettings& InSettings);` — Update the settings used by this Spectrum Analyzer. Safe to call on any thread, but should not be called every tick.
- L320 _public prototype_ `void GetSettings(FSpectrumAnalyzerSettings& OutSettings);` — Get the current settings used by this Spectrum Analyzer.
- L323 _public prototype_ `float GetMagnitudeForFrequency(float InFrequency, EPeakInterpolationMethod InMethod = EPeakInterpolationMethod::Linear);` — Samples magnitude (linearly) for a given frequency, in Hz.
- L324 _public prototype_ `float GetNormalizedMagnitudeForFrequency(float InFrequency, EPeakInterpolationMethod InMethod = EPeakInterpolationMethod::Linear);`
- L327 _public prototype_ `float GetPhaseForFrequency(float InFrequency, EPeakInterpolationMethod InMethod = EPeakInterpolationMethod::Linear);` — Samples phase for a given frequency, in Hz.
- L330 _public prototype_ `void GetBands(ISpectrumBandExtractor& InExtractor, TArray<float>& OutValues);` — Return array of bands using spectrum band extractor.
- L336 _public prototype_ `void LockOutputBuffer();` — You can call this function to ensure that you're sampling the same window of frequency data, Then call UnlockOutputBuffer when you're done. Otherwise, GetMagnitudeForFrequency and GetPhaseForFrequency will always use the latest window of frequency data.
- L337 _public prototype_ `void UnlockOutputBuffer();`
- L340 _public prototype_ `bool PushAudio(const TSampleBuffer<float>& InBuffer);` — Push audio to queue. Returns false if the queue is already full.
- L341 _public prototype_ `bool PushAudio(const float* InBuffer, int32 NumSamples);`
- L346 _public prototype_ `bool PerformAnalysisIfPossible(bool bUseLatestAudio = false);` — Thread safe call to perform actual FFT. Returns true if it performed the FFT, false otherwise. If bUseLatestAudio is set to true, this function will flush the entire input buffer, potentially losing data. Otherwise it will only consume enough samples necessary to perform a single FFT.
- L350 _public prototype_ `bool IsInitialized();` — Returns false if this instance of FSpectrumAnalyzer was constructed with the default constructor and Init() has not been called yet.
- L356 _private prototype_ `void ResetSettings();` — Called on analysis thread.
- L359 _private prototype_ `void PerformInterpolation(const FAlignedFloatBuffer& InComplexBuffer, EPeakInterpolationMethod InMethod, const float InFreq, float& OutReal, float& OutImag);` — Called in GetMagnitudeForFrequency and GetPhaseForFrequency.
- L362 _private member_ `FSpectrumAnalyzerSettings CurrentSettings;` — Cached current settings. Only actually used in ResetSettings().
- L363 _private member_ `volatile bool bSettingsWereUpdated;`
- L365 _private member_ `volatile bool bIsInitialized;`
- L367 _private member_ `float SampleRate;`
- L370 _private member_ `FWindow Window;` — Cached window that is applied prior to running the FFT.
- L371 _private member_ `int32 FFTSize;`
- L372 _private member_ `int32 HopInSamples;`
- L373 _private member_ `EFFTScaling FFTScaling;`
- L375 _private member_ `FAlignedFloatBuffer AnalysisTimeDomainBuffer;`
- L376 _private member_ `FThreadSafeCounter SampleCounter;`
- L377 _private member_ `TCircularAudioBuffer<float> InputQueue;`
- L378 _private member_ `FSpectrumAnalyzerBuffer FrequencyBuffer;`
- L381 _private member_ `double LockedBufferTimestamp;` — if non-null, owns pointer to locked frequency vector we're using.
- L382 _private member_ `const FAlignedFloatBuffer* LockedFrequencyVector;`
- L385 _private member_ `TUniquePtr<IFFTAlgorithm> FFT;`

#### enum `Audio::FSpectrumAnalyzer::EPeakInterpolationMethod`  
`enum class EPeakInterpolationMethod : uint8`  
_L296-301_
- desc: Peak interpolation method. If the EFFTSize is small but will be densely sampled, it's worth using a linear or quadratic interpolation method.
- L298 _public enumerator_ `NearestNeighbor`
- L299 _public enumerator_ `Linear`
- L300 _public enumerator_ `Quadratic`

#### class `Audio::FSpectrumAnalyzerScopeLock`  
`class FSpectrumAnalyzerScopeLock`  
_L388-404_
- L391 _public function_ `FSpectrumAnalyzerScopeLock(FSpectrumAnalyzer* InAnalyzer) : Analyzer(InAnalyzer)`
- L397 _public function_ `~FSpectrumAnalyzerScopeLock()`
- L403 _private member_ `FSpectrumAnalyzer* Analyzer;`

#### class `Audio::FAsyncSpectrumAnalyzer`  
`class FAsyncSpectrumAnalyzer`  
_L407-478_
- desc: SpectrumAnalyzer for computing spectrum in async task.
- L410 _private prototype_ `FAsyncSpectrumAnalyzer(const FSpectrumAnalyzer&) = delete;`
- L411 _private prototype_ `FAsyncSpectrumAnalyzer(FSpectrumAnalyzer&&) = delete;`
- L413 _private prototype_ `FAsyncSpectrumAnalyzer& operator=(const FSpectrumAnalyzer&) = delete;`
- L414 _private prototype_ `FAsyncSpectrumAnalyzer& operator=(FSpectrumAnalyzer&&) = delete;`
- L418 _public prototype_ `FAsyncSpectrumAnalyzer();`
- L420 _public prototype_ `FAsyncSpectrumAnalyzer(float InSampleRate);` — If an instance is created using either of these constructors, Init() is not neccessary.
- L421 _public prototype_ `FAsyncSpectrumAnalyzer(const FSpectrumAnalyzerSettings& InSettings, float InSampleRate);`
- L423 _public prototype_ `virtual ~FAsyncSpectrumAnalyzer();`
- L426 _public prototype_ `void Init(float InSampleRate);` — Initialize sample rate of analyzer if not known at time of construction
- L427 _public prototype_ `void Init(const FSpectrumAnalyzerSettings& InSettings, float InSampleRate);`
- L431 _public prototype_ `bool IsInitialized();` — Returns false if this instance of FSpectrumAnalyzer was constructed with the default constructor and Init() has not been called yet.
- L434 _public prototype_ `void SetSettings(const FSpectrumAnalyzerSettings& InSettings);` — Update the settings used by this Spectrum Analyzer. Safe to call on any thread, but should not be called every tick.
- L437 _public prototype_ `void GetSettings(FSpectrumAnalyzerSettings& OutSettings);` — Get the current settings used by this Spectrum Analyzer.
- L440 _public prototype_ `float GetMagnitudeForFrequency(float InFrequency, FSpectrumAnalyzer::EPeakInterpolationMethod InMethod = FSpectrumAnalyzer::EPeakInterpolationMethod::Linear);` — Samples magnitude (linearly) for a given frequency, in Hz.
- L441 _public prototype_ `float GetNormalizedMagnitudeForFrequency(float InFrequency, FSpectrumAnalyzer::EPeakInterpolationMethod InMethod = FSpectrumAnalyzer::EPeakInterpolationMethod::Linear);`
- L444 _public prototype_ `float GetPhaseForFrequency(float InFrequency, FSpectrumAnalyzer::EPeakInterpolationMethod InMethod = FSpectrumAnalyzer::EPeakInterpolationMethod::Linear);` — Samples phase for a given frequency, in Hz.
- L447 _public prototype_ `void GetBands(ISpectrumBandExtractor& InExtractor, TArray<float>& OutValues);` — Return array of bands using spectrum band extractor.
- L453 _public prototype_ `void LockOutputBuffer();` — You can call this function to ensure that you're sampling the same window of frequency data, Then call UnlockOutputBuffer when you're done. Otherwise, GetMagnitudeForFrequency and GetPhaseForFrequency will always use the latest window of frequency data.
- L454 _public prototype_ `void UnlockOutputBuffer();`
- L457 _public prototype_ `bool PushAudio(const TSampleBuffer<float>& InBuffer);` — Push audio to queue. Returns false if the queue is already full.
- L458 _public prototype_ `bool PushAudio(const float* InBuffer, int32 NumSamples);`
- L463 _public prototype_ `bool PerformAnalysisIfPossible(bool bUseLatestAudio = false);` — Thread safe call to perform actual FFT. Returns true if it performed the FFT, false otherwise. If bUseLatestAudio is set to true, this function will flush the entire input buffer, potentially losing data. Otherwise it will only consume enough samples necessary to perform a single FFT.
- L469 _public prototype_ `bool PerformAsyncAnalysisIfPossible(bool bUseLatestAudio = false);` — Thread safe call to perform actual FFT. Returns true if it performed the FFT, false otherwise. If bUseLatestAudio is set to true, this function will flush the entire input buffer, potentially losing data. Otherwise it will only consume enough samples necessary to perform a single FFT.
- L474 _private member_ `TSharedRef<FSpectrumAnalyzer, ESPMode::ThreadSafe> Analyzer;`
- L477 _private member_ `TUniquePtr<FSpectrumAnalyzerTask> AsyncAnalysisTask;` — This is used if PerformAsyncAnalysisIfPossible is called

#### class `Audio::FAsyncSpectrumAnalyzerScopeLock`  
`class FAsyncSpectrumAnalyzerScopeLock`  
_L480-496_
- L483 _public function_ `FAsyncSpectrumAnalyzerScopeLock(FAsyncSpectrumAnalyzer* InAnalyzer) : Analyzer(InAnalyzer)`
- L489 _public function_ `~FAsyncSpectrumAnalyzerScopeLock()`
- L495 _private member_ `FAsyncSpectrumAnalyzer* Analyzer;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Audio`
- L282 _typedef_ `typedef FAsyncTask<FSpectrumAnalysisAsyncWorker> FSpectrumAnalyzerTask;` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/DSP/SphericalHarmonicCalculator.h` (Public)


#### class `FSphericalHarmonicCalculator`  
`class FSphericalHarmonicCalculator`  
_L16-52_
- L29 _public prototype_ `static void ComputeSoundfieldChannelGains(const int32 Order, const float Azimuth, const float Elevation, float* OutGains);`
- L30 _public prototype_ `static void ComputeSoundfieldChannelGains(const int32 Order, const float Azimuth, const float Elevation, TArrayView<float> OutGains);`
- L32 _public prototype_ `static void GenerateFirstOrderRotationMatrixGivenRadians(const float RotXRadians, const float RotYRadians, const float RotZRadians, FMatrix& OutMatrix);`
- L33 _public prototype_ `static void GenerateFirstOrderRotationMatrixGivenDegrees(const float RotXDegrees, const float RotYDegrees, const float RotZDegrees, FMatrix& OutMatrix);`
- L36 _public function_ `template<typename T> static void AdjustUESphericalCoordinatesForAmbisonics(UE::Math::TVector2<T>& InOutVector)`
- L42 _public function_ `static int64 OrderToNumChannels(const int32 InOrder)`
- L48 _public prototype_ `static bool IndexToOrderAndDegree(const int32 InChannel, int32& OutOrder, int32& OutDegree);`
- L51 _public prototype_ `static void NormalizeGains(TArrayView<float> Gains);`

#### enum `FSphericalHarmonicCalculator::AmbiChanNumber`  
`enum UE_DEPRECATED(5.7, "Not necessary, please use a raw index for ACN values") AmbiChanNumber`  
_L19-27_
- L21 _public enumerator_ `ACN_0 = 0`
- L22 _public enumerator_ `ACN_1`
- L22 _public enumerator_ `ACN_1`
- L22 _public enumerator_ `ACN_1`
- L23 _public enumerator_ `ACN_4`
- L23 _public enumerator_ `ACN_4`
- L23 _public enumerator_ `ACN_4`
- L23 _public enumerator_ `ACN_4`
- L23 _public enumerator_ `ACN_4`
- L24 _public enumerator_ `ACN_9`
- L24 _public enumerator_ `ACN_9`
- L24 _public enumerator_ `ACN_9`
- L24 _public enumerator_ `ACN_9`
- L24 _public enumerator_ `ACN_9`
- L24 _public enumerator_ `ACN_9`
- L24 _public enumerator_ `ACN_9`
- L25 _public enumerator_ `ACN_16`
- L25 _public enumerator_ `ACN_16`
- L25 _public enumerator_ `ACN_16`
- L25 _public enumerator_ `ACN_16`
- L25 _public enumerator_ `ACN_16`
- L25 _public enumerator_ `ACN_16`
- L25 _public enumerator_ `ACN_16`
- L25 _public enumerator_ `ACN_16`
- L25 _public enumerator_ `ACN_16`
- L26 _public enumerator_ `ACN_25`
- L26 _public enumerator_ `ACN_25`
- L26 _public enumerator_ `ACN_25`
- L26 _public enumerator_ `ACN_25`
- L26 _public enumerator_ `ACN_25`
- L26 _public enumerator_ `ACN_25`
- L26 _public enumerator_ `ACN_25`
- L26 _public enumerator_ `ACN_25`
- L26 _public enumerator_ `ACN_25`
- L26 _public enumerator_ `ACN_25`
- L26 _public enumerator_ `ACN_25`

### `Source/Runtime/SignalProcessing/Public/DSP/TapDelayPitchShifter.h` (Public)


#### class `Audio::FTapDelayPitchShifter`  
`class FTapDelayPitchShifter`  
_L12-53_
- desc: Class which reads doppler-shifted tap from a delay buffer
- L15 _public member_ `static constexpr float MinDelayLength = 10.0f;`
- L16 _public member_ `static constexpr float MaxDelayLength = 100.0f;`
- L17 _public member_ `static constexpr float MaxAbsPitchShiftInOctaves = 6.0f;`
- L20 _public prototype_ `FTapDelayPitchShifter();` — Constructor
- L23 _public prototype_ `virtual ~FTapDelayPitchShifter();` — Virtual Destructor
- L26 _public prototype_ `void Init(const float InSampleRate, const float InPitchShift, const float InDelayLength);` — Initialization of the internal delay with given sample rate, pitch shift in semitones, and delay length in milliseconds
- L29 _public prototype_ `void SetDelayLength(const float InDelayLength);` — Sets the internal delay line length.
- L32 _public prototype_ `void SetPitchShift(const float InPitchScaleSemitones);` — Sets the pitch shift in semitones
- L35 _public prototype_ `void SetPitchShiftRatio(const float InPitchShiftRatio);` — Sets the pitch shift in terms of a sample rate ratio
- L38 _public prototype_ `float ReadDopplerShiftedTapFromDelay(const Audio::FDelay& InDelayBuffer, const float ReadOffsetMilliseconds = 0.0f);` — Reads the next sample tap from the input delay buffer
- L41 _public prototype_ `void ProcessAudio(Audio::FDelay& InDelayBuffer, const float* InAudioBuffer, const int32 InNumFrames, float* OutAudioBuffer);` — Process whole block of audio reading to and writing from delay line from input buffer
- L44 _private prototype_ `void UpdatePhasorPhaseIncrement();`
- L46 _private member_ `float SampleRate = 0.0f;`
- L47 _private member_ `Audio::FExponentialEase CurrentDelayLength;`
- L48 _private member_ `float CurrentTargetDelayLength = 0.0f;`
- L49 _private member_ `float CurrentPitchShift = 0.0f;`
- L50 _private member_ `float CurrentPitchShiftRatio = 1.0f;`
- L51 _private member_ `float PhasorPhase = 0.0f;`
- L52 _private member_ `float PhasorPhaseIncrement = 0.0f;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/VariablePoleFilter.h` (Public)


#### enum `Audio::EFilterOrder`  
`enum class EFilterOrder : uint32`  
_L10-16_
- L12 _public enumerator_ `TwoPole = 1`
- L13 _public enumerator_ `FourPole`
- L14 _public enumerator_ `SixPole`
- L15 _public enumerator_ `EightPole`

#### class `Audio::FVariablePoleFilter`  
`class FVariablePoleFilter`  
_L18-47_
- L21 _public member_ `int32 NumFilters = 0;`
- L22 _public member_ `int32 NumChannels = 0;`
- L25 _public member_ `EBiquadFilter::Type Type = EBiquadFilter::Lowpass;`
- L26 _public function_ `FVariablePoleFilter()`
- L28 _public prototype_ `void Init(EFilterOrder InOrder , const float InSampleRate , const int32 InNumChannels , const float InFrequency , const EBiquadFilter::Type InType , const float InBandwidth = 2.f , const float InGain = 0.f);`
- L36 _public prototype_ `void SetParams(const EBiquadFilter::Type InFilterType, const float InCutoffFrequency, const float InBandwidth = 2.f, const float InGain = 0.f);`
- L38 _public prototype_ `void ProcessAudioFrame(const float* InFrame, float* OutFrame);`
- L39 _public prototype_ `void ProcessAudioBuffer(const float* InFrame, float* OutFrame, const int32 NumSamples);`
- L41 _public prototype_ `void Reset();`
- L43 _public function_ `const TArray<FBiquadFilter>& GetFilters() const`
- L46 _private member_ `TArray<FBiquadFilter> Filters;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/Vbap.h` (Public)


#### struct `Audio::IDiscretePanner`  
`struct IDiscretePanner`  
_L11-45_
- desc: Generic panner interface.
- L13 _public prototype_ `virtual ~IDiscretePanner() = default;`
- L42 _public prototype_ `virtual bool ComputeGains(const FInputParams& InParams, FOutputParams& OutResults) const = 0;`
- L44 _public prototype_ `static FVector3f SphericalToUnitCartesian(const float InAzimuth, const float InElevation);`

#### struct `Audio::IDiscretePanner::FSpeaker`  
`struct FSpeaker`  
_L14-21_
- L17 _public member_ `float AzimuthDegrees = 0.0f;` — Listener relative in degrees
- L18 _public member_ `float ElevationDegrees = 0.0f;` — -180 - 180.  (0 ground).
- L19 _public member_ `FName ChannelID = {};` — Unique id of speaker.
- L20 _public member_ `int32 ChannelIndex = INDEX_NONE;` — Index in the format.

#### struct `Audio::IDiscretePanner::FInputParams`  
`struct FInputParams`  
_L22-29_
- L25 _public member_ `float AzimuthDegrees=0.0f;` — Listener relative in degrees
- L26 _public member_ `float ElevationDegrees=0.0f;` — -180 - 180.  (0 ground).
- L27 _public member_ `bool bAllowAzimuthMirroring = false;` — Optionally mirror the azimuth into the northern hemisphere.

#### struct `Audio::IDiscretePanner::FPanResult`  
`struct FPanResult`  
_L30-35_
- L32 _public member_ `FName ChannelID={};` — Unique ID of the Speaker Name.
- L33 _public member_ `int32 ChannelIndex=INDEX_NONE;` — Index in the speaker in format.
- L34 _public member_ `float Gain=0.0f;`

#### struct `Audio::IDiscretePanner::FOutputParams`  
`struct FOutputParams`  
_L36-41_
- L38 _public member_ `static constexpr int32 MaxResults = 3;`
- L39 _public member_ `TArray<FPanResult, TInlineAllocator<MaxResults>> Results;`
- L40 _public function_ `void Reset()`

#### class `Audio::FVBap2D`  
`class FVBap2D final : public IDiscretePanner`  
_L47-68_
- inherits: `IDiscretePanner`
- L50 _public prototype_ `explicit FVBap2D(const TArray<FSpeaker>& InSpeaker);`
- L51 _public prototype_ `virtual ~FVBap2D() override = default;`
- L52 _public prototype_ `virtual bool ComputeGains(const FInputParams& InParams, FOutputParams& OutResults) const override;`
- L62 _private member_ `TArray<FSpan> Spans;`
- L63 _private member_ `float MaxAzimuth = TNumericLimits<float>::Lowest();`
- L64 _private member_ `float MinAzimuth = TNumericLimits<float>::Max();`
- L66 _private prototype_ `void BuildSpans(const TArray<FSpeaker>& InSpeakers);`
- L67 _private prototype_ `int32 FindBestSpan(const float InAzimuthDegrees) const;`

#### struct `Audio::FVBap2D::FSpan`  
`struct FSpan`  
_L55-61_
- L57 _public member_ `FSpeaker A;` — Start.
- L58 _public member_ `FSpeaker B;` — End
- L59 _public member_ `FVector2f DirA;`
- L60 _public member_ `FVector2f DirB;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/VectorLinearResampler.h` (Public)


#### struct `Audio::FVectorLinearResampler`  
`struct FVectorLinearResampler`  
_L92-114_
- desc: FVectorLinearResampler Performs a basic linear resampling using SIMD for optimization. Advancing is done in fixed point - 65536 is a 1.0f sample rate. Stereo requires a deinterleaved format. The design is based on a "pull" model, assuming you need to fill a buffer from a source, rather than computing how much output you would need to resample a given input. If you need to do that, just run the resampler in chunks until you drain the input, appending to the output as you go. Usage: FVectorLinearResample Resampler = {}; uint32 FixedSampleRate = (uint32)(1.0f * 65536); the example source buffer is assumed to be stereo deinterleaved with the right channel directly after the left. float* SourceFrames = 0;//<data from elsewhere>; uint32 SourceBufferFrameCount = 0;//<# of frames - i.e.len(SourceFrames) / (sizeof(float) * 2) since stereo>; uint32 SourceBufferFloatsToRightChannel = SourceBufferFrameCount; // right channel directly after the left const uint32 OutputChunkFrames = 512; while (SourceBufferFrameCount) { stereo output chunk. Or pointer to wherever you're mixing to. float OutputFrames[OutputChunkFrames * 2]; find out how much input we need for the resampler to be able to generate our chunk. uint32 SourceFramesNeeded = Resampler.SourceFramesNeeded(OutputChunkFrames, FixedSampleRate); make sure we have that available. if (SourceFramesNeeded <= SourceBufferFrameCount) { direct resample uint32 SourceFramesConsumed = Resampler.ResampleStereo(OutputChunkFrames, FixedSampleRate, So
- L94 _public member_ `uint32 CurrentFrameFraction;`
- L98 _public function_ `uint32 SourceFramesNeeded(uint32 OutputFramesNeeded, uint32 FixedPointSampleRate)` — Returns the number of source frames necessary to generate the requested output count at the given fixed point sample rate (1.0 rate is 65536)
- L112 _public prototype_ `uint32 ResampleMono(uint32 OutputFramesNeeded, uint32 FixedPointSampleRate, float const* SourceFrames, float* OutputFrames);` — Generate OutputFramesNeeded resampled output at the given fixed point sample rate (1.0 = 65536). Returns the number of source frames to consume. The next run of the resample expects to get SourceFrames + previous runs return value. stereo is deinterleaved, with the right channels being specified by Frames+StrideFloats.
- L113 _public prototype_ `uint32 ResampleStereo(uint32 OutputFramesNeeded, uint32 FixedPointSampleRate, float const* SourceFrames, uint32 SourceFramesStrideFloats, float* OutputFrames, uint32 OutputFramesStrideFloats);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/Viterbi.h` (Public)


#### class `Audio::IViterbiObservations`  
`class IViterbiObservations`  
_L18-37_
- desc: Interface class for viterbi observations. An IViterbiObservations serves as the source of information for the - Number of possible states. - Number of possible timesteps. - Emission log probability for a given state and timestep. Note that probabilities are returned as the logarithm of a probability to avoid numerical under/over flows.
- L21 _public prototype_ `virtual ~IViterbiObservations() = default;`
- L24 _public prototype_ `virtual int32 GetNumStates() const = 0;` — Returns the number of states at a given states.
- L27 _public prototype_ `virtual int32 GetNumTimeSteps() const = 0;` — Returns the number of given time steps.
- L36 _public prototype_ `virtual float GetEmissionLogProbability(int32 InTimeStep, int32 InState) const = 0;` — Returns the log probability for a given state at a specific time step. @param InTimeStep - The timestep of interest in the range [0 , GetNumTimeSteps() - 1]. @param InState - The state of interest in the range [0, GetNumStates() - 1]. @return The log prability of the emission at the specified timestep for the specified state.

#### class `Audio::IViterbiInitialProbability`  
`class IViterbiInitialProbability`  
_L40-52_
- desc: Interface class for viterbi initial log probabilities.
- L43 _public prototype_ `virtual ~IViterbiInitialProbability() = default;`
- L51 _public prototype_ `virtual float GetInitialLogProbability(int32 InState) const = 0;` — Returns the log probability of an initial state. @param InState - The state of interest. @return The initial log probability of the state.

#### class `Audio::IViterbiTransitionProbability`  
`class IViterbiTransitionProbability`  
_L55-69_
- desc: Interface class for viterbi transition log probabilities.
- L58 _public prototype_ `virtual ~IViterbiTransitionProbability() = default;`
- L68 _public prototype_ `virtual float GetTransitionLogProbability(int32 InTimeStep, int32 InPreviousState, int32 InCurrentState) const = 0;` — Return the log probability of going from one state to another state at a specific time step. @param InTimeStep - The current time step. @param InPreviousState - The state at the previous time step. @param InCurrentState - The state at the current time step. @return The log probability of going from InPreviousState to InCurrentState at timestep InTimeStep.

#### struct `Audio::FViterbi`  
`struct FViterbi`  
_L71-82_
- L81 _public prototype_ `static TArray<int32> Decode(const IViterbiObservations& InObservations, const IViterbiInitialProbability& InInitialProbability, const IViterbiTransitionProbability& InTransitionProbability);` — Decode a sequence using the viterbi algorithm. @param InObservations - The emission log probabilities for all observations. @param InInitialProbability - The initial log probabilities for all states. @param InTransitionProbability - The transition log probability for all transitions. @return An array of the most likely state sequence determined by decoding using the viterbi algorithm.

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/VoiceProcessing.h` (Public)


#### class `Audio::FMovingAverager`  
`class FMovingAverager`  
_L17-38_
- desc: This class buffers audio while maintaining a running average of the underlying buffer. This is useful for cases where we can't use a peak detector with asymptotic tracking. For example: lookahead limiters, silence detection, etc.
- L21 _public prototype_ `FMovingAverager(uint32 NumSamples);` — Delay length in samples.
- L24 _public prototype_ `float ProcessInput(const float& Input, float& Output);` — Returns average amplitude across the internal buffer, and fills Output with the delay line output.
- L26 _public prototype_ `void SetNumSamples(uint32 NumSamples);`
- L29 _private prototype_ `FMovingAverager();`
- L31 _private member_ `TArray<float> AudioBuffer;`
- L32 _private member_ `int32 BufferCursor;`
- L34 _private member_ `float AccumulatedSum;`
- L37 _private member_ `FCriticalSection ProcessCriticalSection;` — Contended by ProcessInput and SetNumSamples.

#### class `Audio::FMovingVectorAverager`  
`class FMovingVectorAverager`  
_L43-62_
- desc: Vectorized version of FMovingAverager.
- L47 _public prototype_ `FMovingVectorAverager(uint32 NumSamples);` — Delay length in samples. NumSamples must be divisible by four.
- L50 _public prototype_ `float ProcessAudio(const VectorRegister4Float& Input, VectorRegister4Float& Output);` — Returns average amplitude across the internal buffer, and fills Output with the delay line output.
- L53 _private prototype_ `FMovingVectorAverager();`
- L55 _private member_ `TArray<VectorRegister4Float> AudioBuffer;`
- L56 _private member_ `int32 BufferCursor;`
- L58 _private member_ `VectorRegister4Float AccumulatedSum;`
- L61 _private member_ `FCriticalSection ProcessCriticalSection;` — Contended by ProcessInput and SetNumSamples.

#### class `Audio::FSilenceDetection`  
`class FSilenceDetection`  
_L68-97_
- desc: This object will return buffered audio while the input signal is louder than the specified threshold, and buffer audio when the input signal otherwise.
- L75 _public prototype_ `FSilenceDetection(float InOnsetThreshold, float InReleaseThreshold, int32 AttackDurationInSamples, int32 ReleaseDurationInSamples);` — InOnsetThreshold is the minimum amplitude of a signal before we begin outputting audio, in linear gain. InReleaseThreshold is the amplitude of the signal before we stop outputting audio, in linear gain. AttackDurationInSamples is the amount of samples we average over when calculating our amplitude when the in audio is below the threshold. ReleaseDurationInSamples is the amount of samples we average over when calculating our amplitude when the input audio is above the threshold.
- L81 _public prototype_ `int32 ProcessBuffer(const float* InAudio, float* OutAudio, int32 NumSamples);` — Buffers InAudio and renders any non-silent audio to OutAudio. Returns the number of samples written to OutAudio. The number of samples returned will only be less than NumSamples if the signal becomes audible mid-buffer. We do not return partial buffers when returning from an audible state to a silent state. This should also work in place, i.e. if InAudio == OutAudio.
- L84 _public prototype_ `void SetThreshold(float InThreshold);` — Set the threshold of audibility, in terms of linear gain.
- L87 _public prototype_ `float GetCurrentAmplitude();` — Returns the current estimate of the current amplitude of the input signal, in linear gain.
- L89 _private prototype_ `FSilenceDetection();`
- L91 _private member_ `FMovingVectorAverager Averager;`
- L92 _private member_ `float ReleaseTau;`
- L93 _private member_ `float OnsetThreshold;`
- L94 _private member_ `float ReleaseThreshold;`
- L95 _private member_ `float CurrentAmplitude;`
- L96 _private member_ `bool bOnsetWasInLastBuffer;`

#### class `Audio::FSlowAdaptiveGainControl`  
`class FSlowAdaptiveGainControl`  
_L103-129_
- desc: This object accepts an input buffer and current amplitude estimate of that input buffer, Then applies a computed gain target. Works like a standard feed forward limiter, with a threshold of 0.
- L110 _public prototype_ `FSlowAdaptiveGainControl(float InGainTarget, int32 InAdaptiveRate, float InGainMin = 0.01f, float InGainMax = 2.0f);` — InGainTarget is our target running linear gain. InAdaptiveRate is the time it will take to respond to changes in amplitude, in numbers of buffer callbacks. InGainMin is the most we will attenuate the input signal. InGainMax is the most we will amplify the input signal.
- L114 _public prototype_ `float ProcessAudio(float* InAudio, int32 NumSamples, float InAmplitude);` — Takes an amplitude estimate and an input buffer, and attenuates InAudio based on it. Returns the linear gain applied to InAudio.
- L117 _public prototype_ `void SetAdaptiveRate(int32 InAdaptiveRate);` — Sets the responsiveness of the adaptive gain control, in number of buffer callbacks.
- L120 _private prototype_ `FSlowAdaptiveGainControl();`
- L122 _private prototype_ `float GetTargetGain(float InAmplitude);`
- L124 _private member_ `FMovingAverager PeakDetector;`
- L125 _private member_ `float GainTarget;`
- L126 _private member_ `float PreviousGain;`
- L127 _private member_ `float GainMin;`
- L128 _private member_ `float GainMax;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/VolumeFader.h` (Public)


#### enum `Audio::EFaderCurve`  
`enum class EFaderCurve : uint8`  
_L10-25_
- desc: Type of fade to use when adjusting a fader's volume over time.
- L13 _public enumerator_ `Linear` — Linear Fade
- L16 _public enumerator_ `Logarithmic` — Logarithmic Fade
- L19 _public enumerator_ `SCurve` — S-Curve, Sinusoidal Fade
- L22 _public enumerator_ `Sin` — Equal Power, Sinusoidal Fade
- L24 _public enumerator_ `Count`

#### class `Audio::FVolumeFader`  
`class FVolumeFader`  
_L29-157_
- desc: Control-rate fader for managing volume fades of various standard shapes.
- L32 _public prototype_ `FVolumeFader();`
- L37 _public prototype_ `void Activate();` — Activates the fader if currently deactivated. Sets duration to indefinite (-1.0f)
- L43 _public prototype_ `void Deactivate();` — Deactivates the fader, causing it to remain at the current value and disregard update.
- L48 _public prototype_ `float GetActiveDuration() const;` — Gets time fader is to remain active (-1.0f if always active).
- L53 _public prototype_ `float GetVolume() const;` — Returns current volume of fader
- L60 _public prototype_ `float GetVolumeAfterTime(float InDeltaTime) const;` — Returns the volume given the delta from the current time into the future (Effectively like running to retrieve volume but without actually updating internal state).
- L65 _public prototype_ `float GetFadeDuration() const;` — Returns the duration of the fade.
- L70 _public prototype_ `EFaderCurve GetCurve() const;` — Returns the curve type of the fader
- L75 _public prototype_ `float GetTargetVolume() const;` — Returns the target volume of the fader
- L80 _public prototype_ `bool IsActive() const;` — Whether or not the fader is active.
- L86 _public prototype_ `bool IsFading() const;` — Returns whether or not the fader is currently fading over time.
- L92 _public prototype_ `bool IsFadingIn() const;` — Returns whether or not the fader is currently fading over time and value is increasing.
- L98 _public prototype_ `bool IsFadingOut() const;` — Returns whether or not the fader is currently fading over time and value is decreasing.
- L107 _public prototype_ `void SetActiveDuration(float InDuration);` — Sets the duration the fader is to be active in the future, after which point the fader is disabled.  When disabled, fader will hold the current fade state until activated, at which point it will continue applying the fade over the remainder of the fade duration.
- L112 _public prototype_ `void SetVolume(float InVolume);` — Sets the volume immediately, interrupting any currently active fade.
- L117 _public prototype_ `void StartFade(float InVolume, float InDuration, EFaderCurve InCurve);` — Applies a volume fade over time with the provided parameters.
- L122 _public prototype_ `void StopFade();` — Stops fade, maintaining the current value as the target.
- L127 _public prototype_ `void Update(float InDeltaTime);` — Updates the fader's state with the given delta in time since last update.
- L131 _private prototype_ `static float AlphaToVolume(float InAlpha, EFaderCurve InCurve, float InStartingValue, float InTarget);` — Converts value to final resulting volume
- L136 _private member_ `float Alpha;` — Current value used to linear interpolate over update delta (Normalized value for non-log, -80dB to 0dB for log)
- L141 _private member_ `float Target;` — Target value used to linear interpolate over update delta (Normalized value for non-log, -80dB to 0dB for log)
- L144 _private member_ `float ActiveDuration;` — Duration fader is to be active
- L147 _private member_ `float FadeDuration;` — Duration fader is to perform fade
- L150 _private member_ `float Elapsed;` — Time elapsed since fade has been initiated
- L153 _private member_ `EFaderCurve FadeCurve;` — Audio fader curve to use
- L156 _private member_ `float StartingValue;` — Initial value from the start of the fade

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/WavFormatUtils.h` (Public)


#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SIGNALPROCESSING_API`
- L15 _namespace_ `namespace WavFormatUtils`
- L23 _prototype_ `bool ChannelIdToMixerChannels(const TArray<FName>& InChannelIds, TArray<EAudioMixerChannel::Type>& OutChannels);` (scope `WavFormatUtils`) — Convert Array of channel names into AudioMixer enum entries. If they match. @param InChannelIds Array of Channel Names. @param OutChannels  Array of AudioMixerChannel enum entries. @return true if all channels correctly mapped to an enum entry. false if it was a partial/fail.
- L30 _prototype_ `void MixerChannelToChannelIds(const TArray<EAudioMixerChannel::Type>& InMixerChannels, TArray<FName>& OutChannelIds);` (scope `WavFormatUtils`) — Convert Array of AudioMixerChannel enum entries to an array of channel Ids (names). @param InMixerChannels Array of AudioMixerChannel entries. @param OutChannelIds Array of channel Ids (names).
- L37 _prototype_ `const TCHAR* LexToStringWavChannelMask(const uint32 InSingleSpeakerMask);` (scope `WavFormatUtils`) — Convert a single speaker to a string that describes the mask. @param InSingleSpeakerMask Bitfield containing a single bit that describes which channel you want a description for. @return Pointer the text description or "Unknown WavBitMask".
- L44 _prototype_ `const TCHAR* LexToStringCommonFormat(const uint32 InChannelMask);` (scope `WavFormatUtils`) — Returns a string for the "common" name of this channel mask. Examples being. "Stereo (2.0)" etc. @param InChannelMask The channel mask to query. @return Pointer to the text description. Or "Unknown WavFormat" if it fails to find one.
- L51 _prototype_ `const TCHAR* LexToShortString(const EAudioMixerChannel::Type InChannel);` (scope `WavFormatUtils`) — Get a short version of the AudioMixerChannel. i.e. FrontLeft -> FL. @param InChannel AudioMixerEntry to query. @return Pointer to the Description. "Unknown" otherwise.
- L58 _prototype_ `const TCHAR* LexToStringCommonFormat(const TArray<FName>& InChannelIds);` (scope `WavFormatUtils`) — Returns a string for the "common" name of this channel mask. Examples being. "Stereo (2.0)" etc. @param InChannelIds Array of Channel ID (Names). @return Pointer to the text description. Or "Unknown WavFormat" if it fails to find one.
- L65 _prototype_ `const TCHAR* LexToStringCommonFormat(const TArray<EAudioMixerChannel::Type>& InChannels);` (scope `WavFormatUtils`) — Returns a string for the "common" name of this channel mask. Examples being. "Stereo (2.0)" etc. @param InChannels Array of AudioMixerChannels. (enums). @return Pointer to the text description. Or "Unknown WavFormat" if it fails to find one.
- L72 _prototype_ `FString MakePrettyString(const uint32 InChannelMask);` (scope `WavFormatUtils`) — Make a pretty string for logging of the Channel Mask. i.e. "FrontLeft, FrontRight" @param InChannelMask ChannelMask to use @return A Generated String.
- L79 _prototype_ `FString MakePrettyString(const TArray<EAudioMixerChannel::Type>& InArray);` (scope `WavFormatUtils`) — Make pretty string for logging of the AudioMixerChannel array. i.e. "FrontLeft, FrontRight". @param InArray of AudioMixerChannel entries. @return A Generated String.
- L86 _prototype_ `FString MakePrettyString(const TArray<FName>& InChannelIDs );` (scope `WavFormatUtils`) — Make pretty string for logging of the AudioMixerChannel array. i.e. "FrontLeft, FrontRight". @param InChannelIDs Array of ChannelIds. (names). @return A Generated String.
- L92 _prototype_ `FString MakePrettyShortString(const uint32 InChannelMask);` (scope `WavFormatUtils`) — Makes a pretty "short" string, i.e. abbreviated form. "FL, FR" @return A Generated String.
- L99 _prototype_ `FString MakePrettyShortString(const TArray<EAudioMixerChannel::Type>& InChannels);` (scope `WavFormatUtils`) — Makes a pretty "short" string, i.e. abbreviated form. "FL, FR" @param InChannels Array of AudioMixerChannel entries. @return A Generated String.
- L107 _prototype_ `FString MakePrettyShortString(const TArray<FName>& InChannelIds);` (scope `WavFormatUtils`) — Makes a pretty "short" string, i.e. abbreviated form. "FL, FR" NOTE: If this fails to map the AudioMixerChannels, it will just render the long form instead. @param InChannelIds Array of Channel IDs (names). @return  A Generated String.
- L114 _prototype_ `TArray<EAudioMixerChannel::Type> ChannelMaskToMixerChannels(const uint32 InChannelMask);` (scope `WavFormatUtils`) — Converts a Channel Mask into an Array of AudioMixerChannels @param InChannelMask The ChannelMask @return Array of AudioMixerChannels.
- L121 _prototype_ `EAudioMixerChannel::Type ChannelMaskToMixerChannel(const uint32 InChannelMask);` (scope `WavFormatUtils`) — Convert a single bit of a channel mask to AudioMixerChannel. NOTE. > 1 bit will assert. @param InChannelMask The Single Channel mask. @return AudioMixerChannel enum.
- L128 _prototype_ `uint32 MixerChannelsToChannelMask(const TArray<EAudioMixerChannel::Type>& InChannels);` (scope `WavFormatUtils`) — Convert an Array of AudioMixerChannels to a ChannelMask @param InChannels Array of AudioMixerChannel @return the ChannelMask.
- L137 _prototype_ `const TArray<EAudioMixerChannel::Type>& NumChannelsToMixerChannelsRef(const int32 InNumChannels);` (scope `WavFormatUtils`) — NumChannels -> Array of AudioMixerChannels (ref version). NOTE: This is an optimized form of NumChannelsToMixerChannels which caches statically the results. As a result this is limited to <= 8 channels. > 8 will assert. @param InNumChannels Num of Channels to use for lookup. @return Array of AudioMixerChannels (const reference)
- L146 _prototype_ `TOptional<TArray<EAudioMixerChannel::Type>> NumChannelsToMixerChannels(const int32 InNumChannels);` (scope `WavFormatUtils`) — NumChannels -> Array of AudioMixerChannels. Attempts to map NumChannels to a particular AudioMixerChannel order. This is mainly for legacy reasons, and a Bitmask/Array of channels is preferred for ambiguity reasons. @param InNumChannels Num of Channels to use for lookup. @return Array of AudioMixerChannels.
- L155 _prototype_ `TOptional<uint32> NumChannelsToCommonChannelMask(const int32 InNumChannels);` (scope `WavFormatUtils`) — NumChannels -> Bitmask Attempts to map Num Of Channels to a bitmask. This is mainly for legacy reasons, and a bitmask/array is preferred for ambiguity reasons. @param InNumChannels Num of Chanels to use for lookup. @return Optional bitmask. Optional will not be set if a good mapping can't be found.
- L160 _prototype_ `const TCHAR* LexToString(const EAudioSpeakers Speaker);` (scope `WavFormatUtils`) — Back compat with old EAudioSpeakers enum. These will likely not be necessary, as we will be deprecating EAudioSpeakers enum shortly.
- L161 _prototype_ `const TCHAR* LexToShortString(const EAudioSpeakers InSpeaker);` (scope `WavFormatUtils`)
- L162 _prototype_ `FString MakePrettyString(const TArray<EAudioSpeakers>& InSpeakers);` (scope `WavFormatUtils`)
- L163 _prototype_ `FString MakePrettyShortString(const TArray<EAudioSpeakers>& InSpeakers);` (scope `WavFormatUtils`)
- L164 _prototype_ `TArray<EAudioSpeakers> ChannelMaskToSpeakers(const uint32 InChannelMask);` (scope `WavFormatUtils`)
- L165 _prototype_ `uint32 SpeakersToChannelMask(const TArray<EAudioSpeakers>& InSpeakers);` (scope `WavFormatUtils`)
- L166 _prototype_ `TArray<EAudioMixerChannel::Type> SpeakersToMixerChannels(const TArray<EAudioSpeakers>& InSpeakers);` (scope `WavFormatUtils`)
- L167 _prototype_ `bool MixerChannelsToSpeakers(const TArray<EAudioMixerChannel::Type>& InChannelIds, TArray<EAudioSpeakers>& OutSpeakers);` (scope `WavFormatUtils`)

### `Source/Runtime/SignalProcessing/Public/DSP/WaveShaper.h` (Public)


#### enum `Audio::EWaveShaperType`  
`enum class EWaveShaperType : int32`  
_L9-16_
- L11 _public enumerator_ `Sin`
- L12 _public enumerator_ `ATan`
- L13 _public enumerator_ `Tanh`
- L14 _public enumerator_ `Cubic`
- L15 _public enumerator_ `HardClip`

#### class `Audio::FWaveShaper`  
`class FWaveShaper`  
_L20-68_
- desc: A digital wave shaping effect to cause audio distortion https://en.wikipedia.org/wiki/Waveshaper
- L24 _public prototype_ `FWaveShaper();` — Constructor
- L27 _public prototype_ `~FWaveShaper();` — Destructor
- L30 _public prototype_ `void Init(const float InSampleRate);` — Initialize the equalizer
- L33 _public prototype_ `void SetAmount(const float InAmount);` — Sets the amount of wave shapping. 0.0 is no effect.
- L36 _public prototype_ `void SetBias(const float InBias);` — Set DC offset before processing
- L39 _public prototype_ `void SetOutputGainDb(const float InGainDb);` — Sets the output gain of the waveshaper
- L42 _public prototype_ `void SetOutputGainLinear(const float InGainLinear);` — Sets the output gain of the waveshaper
- L44 _public prototype_ `void SetType(const EWaveShaperType InType);`
- L48 _public prototype_ `void ProcessAudio(const float InSample, float& OutSample);` — Processes one Sample, using ATan Deprecating in favor of ProcessAudioBuffer
- L51 _public prototype_ `void ProcessAudioBuffer(const float* InBuffer, float* OutBuffer, int32 NumFrames);` — Process an entire buffer of audio
- L55 _private member_ `float Amount;`
- L56 _private member_ `float OutputGain;`
- L57 _private member_ `float Bias;`
- L58 _private member_ `EWaveShaperType Type;`
- L60 _private member_ `float OneOverAtanAmount;`
- L61 _private member_ `float OneOverTanhAmount;`
- L63 _private prototype_ `void ProcessHardClip(const float* InBuffer, float* OutBuffer, int32 NumSamples);`
- L64 _private prototype_ `void ProcessTanh(const float* InBuffer, float* OutBuffer, int32 NumSamples);`
- L65 _private prototype_ `void ProcessATan(const float* InBuffer, float* OutBuffer, int32 NumSamples);`
- L66 _private prototype_ `void ProcessCubic(const float* InBuffer, float* OutBuffer, int32 NumSamples);`
- L67 _private prototype_ `void ProcessSin(const float* InBuffer, float* OutBuffer, int32 NumSamples);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`

### `Source/Runtime/SignalProcessing/Public/DSP/WaveTableOsc.h` (Public)


#### enum `Audio::EWaveTable::Type`  
`enum Type`  
_L12-23_
- L14 _public enumerator_ `None`
- L15 _public enumerator_ `SineWaveTable`
- L16 _public enumerator_ `SawWaveTable`
- L17 _public enumerator_ `TriangleWaveTable`
- L18 _public enumerator_ `SquareWaveTable`
- L19 _public enumerator_ `BandLimitedSawWaveTable`
- L20 _public enumerator_ `BandLimitedTriangleWaveTable`
- L21 _public enumerator_ `BandLimitedSquareWaveTable`
- L22 _public enumerator_ `Custom`

#### class `Audio::FWaveTableOsc`  
`class FWaveTableOsc`  
_L30-99_
- desc: A wave table oscillator class
- L34 _public prototype_ `FWaveTableOsc();` — Constructor
- L37 _public prototype_ `virtual ~FWaveTableOsc();` — Virtual Destructor
- L40 _public prototype_ `void Init(const float InSampleRate, const float InFrequencyHz);` — Initialize the wave table oscillator
- L43 _public prototype_ `void SetSampleRate(const float InSampleRate);` — Sets the sample rate of the oscillator.
- L46 _public prototype_ `void Reset();` — Resets the wave table read indices.
- L49 _public prototype_ `void SetScaleAdd(const float InScale, const float InAdd);` — Sets the amount to scale and add to the output of the wave table
- L52 _public function_ `EWaveTable::Type GetType() const` — Returns the type of the wave table oscillator.
- L55 _public prototype_ `void SetFrequencyHz(const float InFrequencyHz);` — Sets the frequency of the wave table oscillator.
- L58 _public function_ `float GetFrequencyHz() const` — Returns the frequency of the wave table oscillator.
- L61 _public prototype_ `TArray<float>& GetTable();` — Returns the internal table used in the wave table.
- L62 _public prototype_ `const TArray<float>& GetTable() const;`
- L65 _public prototype_ `void Generate(float* OutputNormalPhase, float* OutputQuadPhase = nullptr);` — Processes the wave table, outputs the normal and quad phase (optional) values
- L68 _public prototype_ `static TSharedPtr<FWaveTableOsc> CreateWaveTable(const EWaveTable::Type WaveTableType, const int32 WaveTableSize = 1024);` — Creates a wave table using internal factories for standard wave tables or uses custom wave table factor if it exists.
- L71 _protected prototype_ `void UpdateFrequency();`
- L74 _protected member_ `TArray<float> WaveTableBuffer;` — The wave table buffer
- L77 _protected member_ `float FrequencyHz;` — The frequency of the output (given the sample rate)
- L80 _protected member_ `float SampleRate;` — The sample rate of the oscillator
- L83 _protected member_ `float NormalPhaseReadIndex;` — Normal phase read index
- L86 _protected member_ `float QuadPhaseReadIndex;` — The quad-phase read index
- L89 _protected member_ `float PhaseIncrement;` — The phase increment (based on frequency)
- L92 _protected member_ `float OutputScale;` — Amount to scale the output by
- L95 _protected member_ `float OutputAdd;` — Amount to add to the output
- L98 _protected member_ `EWaveTable::Type WaveTableType;` — The wave table oscillator type

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Audio`
- L10 _namespace_ `namespace EWaveTable` (scope `Audio`)

### `Source/Runtime/SignalProcessing/Public/SampleBuffer.h` (Public)


#### class `Audio::TSampleBuffer`  
`template <class SampleType = DefaultUSoundWaveSampleType> class TSampleBuffer`  
_L23-487_
- desc: /
- L27 _private member_ `TArray<SampleType> RawPCMData;` — raw PCM data buffer
- L29 _private member_ `int32 NumSamples;` — The number of samples in the buffer
- L31 _private member_ `int32 NumFrames;` — The number of frames in the buffer
- L33 _private member_ `int32 NumChannels;` — The number of channels in the buffer
- L35 _private member_ `int32 SampleRate;` — The sample rate of the buffer
- L37 _private member_ `float SampleDuration;` — The duration of the buffer in seconds
- L43 _public function_ `inline TSampleBuffer() : NumSamples(0) , NumFrames(0) , NumChannels(0) , SampleRate(0) , SampleDuration(0.0f)`
- L51 _public function_ `inline TSampleBuffer(const TSampleBuffer& Other)`
- L64 _public function_ `inline TSampleBuffer(const FAlignedFloatBuffer& InData, int32 InNumChannels, int32 InSampleRate)`
- L69 _public function_ `inline TSampleBuffer(const float* InBufferPtr, int32 InNumSamples, int32 InNumChannels, int32 InSampleRate)`
- L102 _public function_ `inline TSampleBuffer(const int16* InBufferPtr, int32 InNumSamples, int32 InNumChannels, int32 InSampleRate)`
- L133 _public function_ `TSampleBuffer& operator=(const TSampleBuffer& Other)` — Vanilla assignment operator:
- L151 _public function_ `template<class OtherSampleType> TSampleBuffer& operator=(const TSampleBuffer<OtherSampleType>& Other)` — SampleType converting assignment operator:
- L190 _public function_ `void CopyFrom(const TArray<SampleType>& InArray, int32 InNumChannels, int32 InSampleRate)` — copy from a container of the same element type
- L206 _public function_ `template<class OtherSampleType> void Append(const OtherSampleType* InputBuffer, int32 InNumSamples)` — Append audio data to internal buffer of different sample type of this sample buffer
- L244 _public function_ `template<class OtherSampleType> void Append(const OtherSampleType* InputBuffer, int32 InNumSamples, int32 InNumChannels, int32 InSampleRate)` — Overload of Append that also sets the number of channels and sample rate.
- L252 _public prototype_ `~TSampleBuffer() = default;`
- L254 _public function_ `void Reset()`
- L265 _public function_ `inline const SampleType* GetData() const` — Gets the raw PCM data of the sound wave
- L270 _public function_ `inline TArrayView<SampleType> GetArrayView()`
- L275 _public function_ `inline TArrayView<const SampleType> GetArrayView() const`
- L281 _public function_ `inline int32 GetNumSamples() const` — Gets the number of samples of the sound wave
- L287 _public function_ `inline int32 GetNumFrames() const` — Gets the number of frames of the sound wave
- L293 _public function_ `inline int32 GetNumChannels() const` — Gets the number of channels of the sound wave
- L299 _public function_ `inline int32 GetSampleRate() const` — Gets the sample rate of the sound wave
- L304 _public function_ `inline float GetSampleDuration() const`
- L309 _public function_ `void MixBufferToChannels(int32 InNumChannels)`
- L345 _public function_ `void Clamp(float Ceiling = 1.0f)`
- L386 _public function_ `void ZeroPad(int32 NumFramesToAppend = 0)` — Appends zeroes to the end of this buffer. If called with no arguments or NumFramesToAppend = 0, this will ZeroPad
- L398 _public function_ `void SetNumFrames(int32 InNumFrames)`
- L408 _public function_ `float GetAudioFrameAtFractionalIndex(float InIndex, TArray<SampleType>& OutFrame) const` — InIndex [0.0f, NumSamples - 1.0f] OutFrame is the multichannel output for one index value Returns InIndex wrapped between 0.0 and NumFrames
- L420 _public function_ `float GetAudioFrameAtPhase(float InPhase, TArray<SampleType>& OutFrame) const` — InPhase [0, 1], wrapped, through duration of file (ignores sample rate) OutFrame is the multichannel output for one phase value Returns InPhase wrapped between 0.0 and 1.0
- L433 _public function_ `float GetAudioFrameAtTime(float InTimeSec, TArray<SampleType>& OutFrame) const` — InTimeSec, get the value of the buffer at the given time (uses sample rate) OutFrame is the multichannel output for one time value Returns InTimeSec wrapped between 0.0 and (NumSamples / SampleRate)
- L450 _private function_ `void GetAudioFrameAtFractionalIndexInternal(float InIndex, TArray<SampleType>& OutFrame) const` — Internal implementation. Called by all public GetAudioFrameAt_ _ _ _() functions public functions do range checking/wrapping and then call this function

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
- L11 _typedef_ `typedef int16 DefaultUSoundWaveSampleType;` (scope `Audio`)
- L490 _typedef_ `typedef TSampleBuffer<> FSampleBuffer;` (scope `Audio`) — FSampleBuffer is a strictly defined TSampleBuffer that uses the same sample format we use for USoundWaves.

### `Source/Runtime/SignalProcessing/Public/SignalProcessingModule.h` (Public)


#### Free symbols / members of external scopes

- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSignalProcessing, Log, All);`
