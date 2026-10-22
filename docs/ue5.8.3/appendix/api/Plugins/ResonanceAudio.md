# Plugins / ResonanceAudio

- module root: `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio`
- headers: 119; symbols: 2060
- symbol kinds: class=91, delegate=1, enum=14, enumerator=95, function=207, macro=167, member=514, namespace=104, prototype=706, struct=19, typedef=62, variable=80
- PrivateDependencyModuleNames: AudioExtensions, EditorFramework, InputCore, Landscape, ProceduralMeshComponent, Projects, UnrealEd
- PrivateIncludePathModuleNames: TargetPlatform
- PublicDependencyModuleNames: AudioMixer, Core, CoreUObject, Engine, ProceduralMeshComponent, SoundFieldRendering

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioAmbisonics.h` (Private)


#### class `ResonanceAudio::FResonancePacket`  
`class FResonancePacket : public ISoundfieldAudioPacket`  
_L13-45_
- inherits: `ISoundfieldAudioPacket`
- desc: Packet passed between Resonance submixes. All it holds onto is a raw pointer to the Resonance system used to encode whatever sources were passed in.
- L16 _private function_ `FResonancePacket()`
- L18 _private member_ `vraudio::ResonanceAudioApi* ResonanceSystem;`
- L21 _public function_ `FResonancePacket(vraudio::ResonanceAudioApi* InSystem) : ResonanceSystem(InSystem)`
- L26 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L27 _public prototype_ `virtual TUniquePtr<ISoundfieldAudioPacket> Duplicate() const override;`
- L28 _public prototype_ `virtual void Reset() override;`
- L30 _public function_ `vraudio::ResonanceAudioApi* GetResonanceApi() const`
- L35 _public function_ `void SetResonanceApi(vraudio::ResonanceAudioApi* InResonanceSystem)`
- L41 _public function_ `vraudio::ResonanceAudioApi* GetResonanceApi()`

#### class `ResonanceAudio::FAmbisonicsFactory`  
`class FAmbisonicsFactory : public ISoundfieldFactory`  
_L47-79_
- inherits: `ISoundfieldFactory`
- L50 _public prototype_ `FAmbisonicsFactory();`
- L51 _public prototype_ `virtual ~FAmbisonicsFactory();`
- L54 _public function_ `void SetResonanceAudioApi(uint32 AudioDeviceID, FResonanceAudioApiSharedPtr InResonanceAudioApi)` — This function is called by the ResonanceAudioPluginListener as soon as the ResonanceAudioApi is initialized.
- L61 _public prototype_ `virtual FName GetSoundfieldFormatName() override;`
- L62 _public prototype_ `virtual TUniquePtr<ISoundfieldEncoderStream> CreateEncoderStream(const FAudioPluginInitializationParams& InitInfo, const ISoundfieldEncodingSettingsProxy& InitialSettings) override;`
- L63 _public prototype_ `virtual TUniquePtr<ISoundfieldDecoderStream> CreateDecoderStream(const FAudioPluginInitializationParams& InitInfo, const ISoundfieldEncodingSettingsProxy& InitialSettings) override;`
- L64 _public prototype_ `virtual TUniquePtr<ISoundfieldTranscodeStream> CreateTranscoderStream(const FName SourceFormat, const ISoundfieldEncodingSettingsProxy& InitialSourceSettings, const FName DestinationFormat, const ISoundfieldEncodingSettingsProxy& InitialDestinationSettings, const FAudioPluginInitializationParams& InitInfo) override;`
- L65 _public prototype_ `virtual TUniquePtr<ISoundfieldMixerStream> CreateMixerStream(const ISoundfieldEncodingSettingsProxy& InitialSettings) override;`
- L66 _public prototype_ `virtual TUniquePtr<ISoundfieldAudioPacket> CreateEmptyPacket() override;`
- L67 _public prototype_ `virtual bool IsTranscodeRequiredBetweenSettings(const ISoundfieldEncodingSettingsProxy& SourceSettings, const ISoundfieldEncodingSettingsProxy& DestinationSettings) override;`
- L68 _public prototype_ `virtual bool CanTranscodeFromSoundfieldFormat(FName SourceFormat, const ISoundfieldEncodingSettingsProxy& SourceEncodingSettings) override;`
- L69 _public prototype_ `virtual bool CanTranscodeToSoundfieldFormat(FName DestinationFormat, const ISoundfieldEncodingSettingsProxy& DestinationEncodingSettings) override;`
- L70 _public prototype_ `virtual UClass* GetCustomEncodingSettingsClass() const override;`
- L71 _public prototype_ `virtual const USoundfieldEncodingSettingsBase* GetDefaultEncodingSettings() override;`
- L75 _private prototype_ `FResonanceAudioApiSharedPtr CreateNewResonanceApiInstance(FAudioDevice* AudioDevice, const FAudioPluginInitializationParams& InInitInfo);`
- L78 _private member_ `TMap<uint32, FResonanceAudioApiSharedPtr> ResonanceAudioAPIMap;` — Map of which audio engine StreamIds map to which Resonance SourceIds.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ResonanceAudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioAmbisonicsSettingsProxy.h` (Private)


#### class `FResonanceAmbisonicsSettingsProxy`  
`class FResonanceAmbisonicsSettingsProxy : public ISoundfieldEncodingSettingsProxy`  
_L13-30_
- inherits: `ISoundfieldEncodingSettingsProxy`
- L16 _public member_ `vraudio::RenderingMode RenderingMode;`
- L18 _public function_ `virtual uint32 GetUniqueId() const override`
- L23 _public function_ `virtual TUniquePtr<ISoundfieldEncodingSettingsProxy> Duplicate() const override`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioCommon.h` (Private)


#### Free symbols / members of external scopes

- L21 _namespace_ `namespace ResonanceAudio`
- L23 _typedef_ `typedef vraudio::ResonanceAudioApi::SourceId RaSourceId;` (scope `ResonanceAudio`)
- L24 _typedef_ `typedef vraudio::RoomProperties RaRoomProperties;` (scope `ResonanceAudio`)
- L25 _typedef_ `typedef vraudio::ReflectionProperties RaReflectionProperties;` (scope `ResonanceAudio`)
- L26 _typedef_ `typedef vraudio::ReverbProperties RaReverbProperties;` (scope `ResonanceAudio`)
- L29 _typedef_ `typedef TSharedPtr<vraudio::ResonanceAudioApi, ESPMode::ThreadSafe> FResonanceAudioApiSharedPtr;` (scope `ResonanceAudio`) — Lifecycle of a ResonanceAudioApi is managed by a threadsafe TSharedPtr
- L33 _prototype_ `void* LoadResonanceAudioDynamicLibrary();` (scope `ResonanceAudio`) — Attempts to load the dynamic library pertaining to the given platform, performing some basic error checking. Returns handle to dynamic library or nullptr on error.
- L36 _prototype_ `vraudio::ResonanceAudioApi* CreateResonanceAudioApi(void* DynamicLibraryHandle, size_t NumChannels, size_t NumFrames, int SampleRate);` (scope `ResonanceAudio`) — Calls the CreateVrAudioApi method either from the given dynamic library or directly in the case of static linkage.
- L39 _variable_ `const RaSourceId RA_INVALID_SOURCE_ID = vraudio::ResonanceAudioApi::kInvalidSourceId;` (scope `ResonanceAudio`) — Invalid Source ID.
- L42 _prototype_ `vraudio::MaterialName ConvertToResonanceMaterialName(ERaMaterialName UnrealMaterialName);` (scope `ResonanceAudio`) — Converts between Unreal enum and Resonance Audio room surface coefficient.
- L45 _prototype_ `FVector ConvertToResonanceAudioCoordinates(const FVector& UnrealVector);` (scope `ResonanceAudio`) — Converts between Unreal and Resonance Audio position coordinates.
- L46 _prototype_ `FVector ConvertToResonanceAudioCoordinates(const Audio::FChannelPositionInfo& ChannelPositionInfo);` (scope `ResonanceAudio`)
- L49 _prototype_ `FQuat ConvertToResonanceAudioRotation(const FQuat& UnrealQuat);` (scope `ResonanceAudio`) — Converts between Unreal and Resonance Audio rotation quaternions.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioConstants.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace ResonanceAudio`
- L12 _variable_ `const FColor ASSET_COLOR = FColor(0, 198, 246);` (scope `ResonanceAudio`) — Resonance Audio assets base color.
- L15 _variable_ `constexpr int NUM_SURFACES = 6;` (scope `ResonanceAudio`) — Number of surfaces in a shoe-box room.
- L18 _variable_ `constexpr float SCALE_FACTOR = 0.01f;` (scope `ResonanceAudio`) — Conversion factor between Resonance Audio and Unreal world distance units (1cm in Unreal = 0.01m in Resonance Audio).

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioDirectivityVisualizer.h` (Private)


#### class `AResonanceAudioDirectivityVisualizer`  
`class AResonanceAudioDirectivityVisualizer : public AActor`  
_L19-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `AActor`
- L25 _public prototype_ `AResonanceAudioDirectivityVisualizer();` — Sets default values for this actor's properties.
- L28 _public prototype_ `void DrawPattern();` — Draws given directivity pattern as a 2D mesh based on Settings.
- L30 _public function_ `void SetSettings(UResonanceAudioSpatializationSourceSettings* InSettings)`
- L31 _public function_ `UResonanceAudioSpatializationSourceSettings* GetSettings() const`
- L35 _private member_ `const int CIRCLE_SECTIONS = 128;` — Controls the smoothness of mesh visualization.
- L38 _private member_ `TArray<FVector> Vertices;` — Arrays required by Procedural Mesh Component.
- L39 _private member_ `TArray<int32> Triangles;`
- L40 _private member_ `TArray<FVector> Normals;`
- L41 _private member_ `TArray<FColor> VertexColors;`
- L44 _private member_ `TArray<FVector2D> UV0;` — Optional arrays.
- L45 _private member_ `TArray<FProcMeshTangent> Tangents;`
- L48 _private member_ `UProceduralMeshComponent* Mesh;`
- L52 _private member_ `TObjectPtr<UMaterial> Material;` — `UPROPERTY()`
- L55 _private member_ `TObjectPtr<UResonanceAudioSpatializationSourceSettings> Settings;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API RESONANCEAUDIO_API`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/platforms/common/room_effects_utils.h` (Private)


#### struct `vraudio::RoomMaterial`  
`struct RoomMaterial`  
_L30-36_
- desc: Room material properties.
- L32 _public member_ `MaterialName name;` — Material surface integer identifier.
- L35 _public member_ `float absorption_coefficients[kNumReverbOctaveBands];` — An array of absorption coefficients defined in octave bands.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_PLATFORM_COMMON_ROOM_EFFECTS_UTILS_H_`
- L27 _namespace_ `namespace vraudio`
- L41 _prototype_ `ReflectionProperties ComputeReflectionProperties( const RoomProperties& room_properties);` (scope `vraudio`) — Generates |ReflectionProperties| based on given |room_properties|. @param room_properties Room properties.
- L47 _prototype_ `ReverbProperties ComputeReverbProperties(const RoomProperties& room_properties);` (scope `vraudio`) — Generates |ReverbProperties| based on given |room_properties|. @param room_properties Room properties.
- L56 _prototype_ `ReverbProperties ComputeReverbPropertiesFromRT60s(const float* rt60_values, float brightness_modifier, float time_scalar, float gain_multiplier);` (scope `vraudio`) — Generates |ReverbProperties| by directly setting the RT60 values, subject to modifications by |brightness_modifier| and |time_scaler|. @param rt60_values RT60 values. @param brightness_modifier Modifier adjusting the brightness of reverb. @param time_scalar Modifier scaling the reverb time. @param gain_multiplier Modifier scaling the reverb gain.
- L71 _prototype_ `float ComputeRoomEffectsGain(const WorldPosition& source_position, const WorldPosition& room_position, const WorldRotation& room_rotation, const WorldPosition& room_dimensions);` (scope `vraudio`) — Calculates the gain value for |source_position| with respect to the given room properties. The sound level for the room effects will remain the same inside the room, otherwise, it will decrease with a linear ramp from the closest point on the room. @param source_position World position of the source. @param room_position Center position of the room. @param room_rotation Orientation of the room. @param room_dimensions Dimensions of the room.. @return Attenuation (gain) value in range [0.0f, 1.0f].
- L79 _prototype_ `RoomMaterial GetRoomMaterial(size_t material_index);` (scope `vraudio`) — Gets the room material properties from a material index. @param material_index Index of the material.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/platforms/common/room_properties.h` (Private)


#### enum `vraudio::MaterialName`  
`enum MaterialName`  
_L38-64_
- desc: Room surface material names, used to set room properties. Note that this enum is C-compatible by design to be used across external C/C++ and C# implementations.
- L39 _public enumerator_ `kTransparent = 0`
- L40 _public enumerator_ `kAcousticCeilingTiles`
- L41 _public enumerator_ `kBrickBare`
- L42 _public enumerator_ `kBrickPainted`
- L43 _public enumerator_ `kConcreteBlockCoarse`
- L44 _public enumerator_ `kConcreteBlockPainted`
- L45 _public enumerator_ `kCurtainHeavy`
- L46 _public enumerator_ `kFiberGlassInsulation`
- L47 _public enumerator_ `kGlassThin`
- L48 _public enumerator_ `kGlassThick`
- L49 _public enumerator_ `kGrass`
- L50 _public enumerator_ `kLinoleumOnConcrete`
- L51 _public enumerator_ `kMarble`
- L52 _public enumerator_ `kMetal`
- L53 _public enumerator_ `kParquetOnConcrete`
- L54 _public enumerator_ `kPlasterRough`
- L55 _public enumerator_ `kPlasterSmooth`
- L56 _public enumerator_ `kPlywoodPanel`
- L57 _public enumerator_ `kPolishedConcreteOrTile`
- L58 _public enumerator_ `kSheetrock`
- L59 _public enumerator_ `kWaterOrIceSurface`
- L60 _public enumerator_ `kWoodCeiling`
- L61 _public enumerator_ `kWoodPanel`
- L62 _public enumerator_ `kUniform`
- L63 _public enumerator_ `kNumMaterialNames`

#### struct `vraudio::RoomProperties`  
`struct RoomProperties`  
_L70-119_
- desc: Acoustic room properties. This struct can be used to describe an acoustic environment with a given geometry and surface properties. Note that this struct is C-compatible by design to be used across external C/C++ and C# implementations.
- L72 _public function_ `RoomProperties() : position` — Constructs |RoomProperties| with the default values.
- L86 _public member_ `float position[3];` — Center position of the room in world space, uses right-handed coordinate system.
- L90 _public member_ `float rotation[4];` — Rotation (quaternion) of the room in world space, uses right-handed coordinate system.
- L94 _public member_ `float dimensions[3];` — Size of the shoebox room in world space, uses right-handed coordinate system.
- L103 _public member_ `MaterialName material_names[6];` — Material name of each surface of the shoebox room in this order: [0] (-)ive x-axis wall (left) [1] (+)ive x-axis wall (right) [2] (-)ive y-axis wall (bottom) [3] (+)ive y-axis wall (top) [4] (-)ive z-axis wall (front) [5] (+)ive z-axis wall (back)
- L106 _public member_ `float reflection_scalar;` — User defined uniform scaling factor for all reflection coefficients.
- L109 _public member_ `float reverb_gain;` — User defined reverb tail gain multiplier.
- L113 _public member_ `float reverb_time;` — Adjusts the reverberation time across all frequency bands. RT60 values are multiplied by this factor. Has no effect when set to 1.0f.
- L118 _public member_ `float reverb_brightness;` — Controls the slope of a line from the lowest to the highest RT60 values (increases high frequency RT60s when positive, decreases when negative). Has no effect when set to 0.0f.

#### Free symbols / members of external scopes

- L31 _macro_ `#define RESONANCE_AUDIO_PLATFORM_COMMON_ROOM_PROPERTIES_H_`
- L33 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/ambisonics/ambisonic_binaural_decoder.h` (Private)


#### class `vraudio::AmbisonicBinauralDecoder`  
`class AmbisonicBinauralDecoder`  
_L33-67_
- desc: Decodes an Ambisonic sound field, of an arbitrary order, to binaural stereo, by performing convolution in the spherical harmonics domain. The order (hence the number of channels) of the input must match the order (hence the number of channels) of the spherical harmonic-encoded Head Related Impulse Responses (HRIRs). Assumes that HRIRs are symmetric with respect to the sagittal plane.
- L44 _public prototype_ `AmbisonicBinauralDecoder(const AudioBuffer& sh_hrirs, size_t frames_per_buffer, FftManager* fft_manager);` — Constructs an |AmbisonicBinauralDecoder| from an |AudioBuffer| containing spherical harmonic representation of HRIRs. The order of spherical harmonic-encoded HRIRs (hence the number of channels) must match the order of the Ambisonic sound field input. @param sh_hrirs |AudioBuffer| containing time-domain spherical harmonic encoded symmetric HRIRs. @param frames_per_buffer Number of frames in each input/output buffer. @param fft_manager Pointer to a manager to perform FFT transformations.
- L52 _public prototype_ `void Process(const AudioBuffer& input, AudioBuffer* output);` — Processes an Ambisonic sound field input and outputs a binaurally decoded stereo buffer. @param input Input buffer to be processed. @param output Pointer to a stereo output buffer.
- L56 _private member_ `FftManager* const fft_manager_;` — Manager for all FFT related functionality (not owned).
- L59 _private member_ `std::vector<std::unique_ptr<PartitionedFftFilter>> sh_hrir_filters_;` — Spherical Harmonic HRIR filter kernels.
- L62 _private member_ `PartitionedFftFilter::FreqDomainBuffer freq_input_;` — Frequency domain representation of the input signal.
- L66 _private member_ `AudioBuffer filtered_input_;` — Temporary audio buffer to store the convolution output for asymmetric or symmetric spherical harmonic HRIR.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_AMBISONICS_AMBISONIC_BINAURAL_DECODER_H_`
- L26 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/ambisonics/ambisonic_codec.h` (Private)


#### class `vraudio::AmbisonicCodec`  
`class AmbisonicCodec`  
_L28-58_
- desc: An encoder/decoder for ambisonic sound fields. It supports variable ambisonic order, ACN channel sequencing and SN3D normalization.
- L30 _public prototype_ `virtual ~AmbisonicCodec() = default;`
- L35 _public prototype_ `virtual void EncodeBuffer(const AudioBuffer& input, AudioBuffer* output) = 0;` — Encodes the given buffer of decoded vectors (unencoded data). @param input |AudioBuffer| of decoded (unencoded) data. @param output |AudioBuffer| to store the encoded data.
- L41 _public prototype_ `virtual void DecodeBuffer(const AudioBuffer& input, AudioBuffer* output) = 0;` — Decodes the given |AudioBuffer| of planar (non-interleaved) encoded data. @param input |AudioBuffer| of encoded data. @param output |AudioBuffer| to store the decoded data.
- L44 _public prototype_ `virtual int ambisonic_order() const = 0;` — Returns the maximum periphonic ambisonic order that this codec supports.
- L47 _public prototype_ `virtual size_t num_angles() const = 0;` — Returns the number of angles for this codec.
- L50 _public prototype_ `virtual size_t num_spherical_harmonics() const = 0;` — Returns the maximum number of spherical harmonics computed by this codec.
- L54 _public prototype_ `virtual const std::vector<SphericalAngle>& angles() const = 0;` — Returns the spherical angles currently used to define the encoder/decoder matrices.
- L57 _public prototype_ `virtual void set_angles(const std::vector<SphericalAngle>& angles) = 0;` — Sets the spherical angles used to build the encoder/decoder matrices.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_AMBISONICS_AMBISONIC_CODEC_H_`
- L25 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/ambisonics/ambisonic_codec_impl.h` (Private)


#### class `vraudio::AmbisonicCodecImpl`  
`class AmbisonicCodecImpl : public AmbisonicCodec`  
_L44-117_
- inherits: `AmbisonicCodec`
- L47 _public typedef_ `typedef Eigen::Matrix<float, NumSphericalHarmonics, NumAngles> EncoderMatrix;` — Spherical harmonics encoder matrix.
- L49 _public typedef_ `typedef Eigen::Matrix<float, NumAngles, NumSphericalHarmonics> DecoderMatrix;` — Spherical harmonics decoder matrix.
- L52 _public typedef_ `typedef Eigen::Matrix<float, NumSphericalHarmonics, 1> EncodedVector;` — Spherical harmonics encoding of a frame or collection of frames (i.e., a vector of spherical harmonics).
- L55 _public typedef_ `typedef Eigen::Matrix<float, NumAngles, 1> DecodedVector;` — Decoded sequence of values for each angle / mono frame (i.e., a vector with a decoded mono frame for each angle).
- L59 _public prototype_ `AmbisonicCodecImpl(int ambisonic_order, const std::vector<SphericalAngle>& angles);` — Creates a codec with the given |ambisonic_order| and spherical |angles| to compute encoder/decoder matrices.
- L63 _public prototype_ `void EncodeBuffer(const AudioBuffer& input, AudioBuffer* output) override;` — Implements |AmbisonicCodec|.
- L64 _public prototype_ `void DecodeBuffer(const AudioBuffer& input, AudioBuffer* output) override;`
- L65 _public prototype_ `int ambisonic_order() const override;`
- L66 _public prototype_ `size_t num_angles() const override;`
- L67 _public prototype_ `size_t num_spherical_harmonics() const override;`
- L68 _public prototype_ `const std::vector<SphericalAngle>& angles() const override;`
- L69 _public prototype_ `void set_angles(const std::vector<SphericalAngle>& angles) override;`
- L73 _public prototype_ `void Encode(const Eigen::Ref<const Eigen::MatrixXf> decoded_vector, Eigen::Ref<Eigen::MatrixXf> encoded_vector);`
- L78 _public prototype_ `void Decode(const Eigen::Ref<const Eigen::MatrixXf> encoded_vector, Eigen::Ref<Eigen::MatrixXf> decoded_vector);`
- L82 _public prototype_ `const Eigen::Ref<const Eigen::MatrixXf> GetEncoderMatrix();` — Gets the ambisonic sound field encoder matrix.
- L85 _public prototype_ `const Eigen::Ref<const Eigen::MatrixXf> GetDecoderMatrix();` — Gets the ambisonic sound field decoder matrix.
- L93 _private prototype_ `float UnnormalizedSphericalHarmonic(int degree, int order, const SphericalAngle& angle) const;` — Returns the unnormalized spherical harmonic Y_degree^order(azimuth, elevation).
- L98 _private member_ `const int ambisonic_order_;` — The maximum-ordered ambisonic sound field handled by this codec. In the case of a periphonic codec, this is the order of the ambisonic sound field.
- L102 _private member_ `std::vector<SphericalAngle> angles_;` — Spherical angles used to compute spherical harmonics. For example, for a decoder, virtual loudspeaker positions; for an encoder, the position(s) of virtual sources relative to the listener.
- L105 _private member_ `EncoderMatrix encoder_matrix_;` — Current spherical harmonics encoder matrix if encoder_matrix_invalid_ is false.
- L107 _private member_ `bool encoder_matrix_invalid_;` — True if encoder_matrix_ needs to be recomputed.
- L110 _private member_ `DecoderMatrix decoder_matrix_;` — Current spherical harmonics decoder matrix if encoder_matrix_invalid_ is false.
- L112 _private member_ `bool decoder_matrix_invalid_;` — True if decoder_matrix_ needs to be recomputed.
- L114 _private member_ `AssociatedLegendrePolynomialsGenerator alp_generator_;` — The associated Legendre polynomial generator for this codec.
- L116 _private member_ `std::vector<float> associated_legendre_polynomials_temp_;` — Temporary storage for associated Legendre polynomials generated.
- L120 _function_ `template <int NumAngles, int NumSphericalHarmonics> AmbisonicCodecImpl<NumAngles, NumSphericalHarmonics>::AmbisonicCodecImpl( int ambisonic_order, const std::vector<SphericalAngle>& angles) : ambisonic_order_(ambisonic_order), alp_generator_(ambisonic_order, false, false)`
- L129 _function_ `template <int NumAngles, int NumSphericalHarmonics> void AmbisonicCodecImpl<NumAngles, NumSphericalHarmonics>::Encode( const Eigen::Ref<const Eigen::MatrixXf> decoded_vector, Eigen::Ref<Eigen::MatrixXf> encoded_vector)`
- L136 _function_ `template <int NumAngles, int NumSphericalHarmonics> void AmbisonicCodecImpl<NumAngles, NumSphericalHarmonics>::Decode( const Eigen::Ref<const Eigen::MatrixXf> encoded_vector, Eigen::Ref<Eigen::MatrixXf> decoded_vector)`
- L143 _function_ `template <int NumAngles, int NumSphericalHarmonics> void AmbisonicCodecImpl<NumAngles, NumSphericalHarmonics>::EncodeBuffer( const AudioBuffer& input, AudioBuffer* output)`
- L165 _function_ `template <int NumAngles, int NumSphericalHarmonics> void AmbisonicCodecImpl<NumAngles, NumSphericalHarmonics>::DecodeBuffer( const AudioBuffer& input, AudioBuffer* output)`
- L189 _function_ `AmbisonicCodecImpl<NumAngles, NumSphericalHarmonics>::GetEncoderMatrix()`
- L218 _function_ `AmbisonicCodecImpl<NumAngles, NumSphericalHarmonics>::GetDecoderMatrix()`
- L238 _function_ `template <int NumAngles, int NumSphericalHarmonics> int AmbisonicCodecImpl<NumAngles, NumSphericalHarmonics>::ambisonic_order() const`
- L244 _function_ `template <int NumAngles, int NumSphericalHarmonics> size_t AmbisonicCodecImpl<NumAngles, NumSphericalHarmonics>::num_angles() const`
- L251 _function_ `template <int NumAngles, int NumSphericalHarmonics> size_t AmbisonicCodecImpl< NumAngles, NumSphericalHarmonics>::num_spherical_harmonics() const`
- L259 _function_ `AmbisonicCodecImpl<NumAngles, NumSphericalHarmonics>::angles() const`
- L264 _function_ `template <int NumAngles, int NumSphericalHarmonics> void AmbisonicCodecImpl<NumAngles, NumSphericalHarmonics>::set_angles( const std::vector<SphericalAngle>& angles)`
- L274 _function_ `UnnormalizedSphericalHarmonic(int degree, int order, const SphericalAngle& angle) const`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_AMBISONICS_AMBISONIC_CODEC_IMPL_H_`
- L33 _namespace_ `namespace vraudio`
- L286 _typedef_ `template <int NumSphericalHarmonics = Eigen::Dynamic> using MonoAmbisonicCodec = AmbisonicCodecImpl<1, NumSphericalHarmonics>;` (scope `vraudio`) — Codec for a single source.
- L290 _typedef_ `template <int NumAngles> using FirstOrderPeriphonicAmbisonicCodec = AmbisonicCodecImpl<NumAngles, GetNumPeriphonicComponentsStatic<1>::value>;` (scope `vraudio`) — Codec for a N-speaker first-order periphonic setup.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/ambisonics/ambisonic_lookup_table.h` (Private)


#### class `vraudio::AmbisonicLookupTable`  
`class AmbisonicLookupTable`  
_L29-88_
- desc: Represents a lookup table for encoding of Ambisonic periphonic sound fields. Supports arbitrary Ambisonic order and uses AmbiX convention (ACN channel sequencing, SN3D normalization).
- L34 _public prototype_ `explicit AmbisonicLookupTable(int max_ambisonic_order);` — Creates Ambisonic (AmbiX) encoder lookup table given the |max_ambisonic_order| used by the client. AmbiX convention uses ACN channel sequencing and SN3D normalization.
- L45 _public prototype_ `void GetEncodingCoeffs(int ambisonic_order, const SphericalAngle& source_direction, float source_spread_deg, std::vector<float>* encoding_coeffs) const;` — Gets spherical harmonic encoding coefficients for a given order and writes them to |encoding_coeffs|. @param ambisonic_order Ambisonic order of the encoded sound source. @param source_direction Direction of a sound source in spherical coordinates. @param source_spread_deg Encoded sound source angular spread in degrees. @param encoding_coeffs Pointer to a vector of Ambisonic encoding coefficients.
- L53 _private prototype_ `void ComputeEncoderTable();` — Computes a lookup table of encoding coefficients for one quadrant of the sphere.
- L60 _private prototype_ `void ComputeSymmetriesTable();` — Computes a table of spherical harmonics symmetry information for all cartesian axes. Value of 1 indicates that the current spherical harmonic is symmetric with respect to the current axis. Value of -1 indicates that the current spherical harmonic is anti-symmetric with respect to the current axis.
- L70 _private prototype_ `float UnnormalizedSphericalHarmonic(float alp_value, int order, float azimuth_rad);` — Returns the unnormalized spherical harmonic coefficient: Y_degree^order(azimuth, elevation). @param alp_value Associated Legendre polynomial for the given degree and order evaluated at sin elevation angle: P_degree^order(sin(elevation)). @param order Order of the Associated Legendre polynomial. @param azimuth_rad Azimuth angle in radians. @return Unnormalized spherical harmonic coefficient.
- L74 _private member_ `const int max_ambisonic_order_;` — Ambisonic order.
- L80 _private member_ `const size_t max_num_coeffs_in_table_;` — Maximum number of coefficients to be stored in the lookup table equal to the number of Ambisonic channels for |max_ambisonic_order_| - 1. This is because we do not need to store the coefficient for the first spherical harmonic coefficient as it is always 1.
- L84 _private member_ `std::vector<float> encoder_table_;` — Lookup table for storing Ambisonic encoding coefficients for one quadrant of the sphere.
- L87 _private member_ `std::vector<float> symmetries_table_;` — Lookup table for storing information about spherical harmonic symmetries.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_AMBISONICS_AMBISONIC_LOOKUP_TABLE_H_`
- L24 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/ambisonics/ambisonic_spread_coefficients.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_AMBISONICS_AMBISONIC_SPREAD_COEFFICIENTS_H_`
- L20 _namespace_ `namespace vraudio`
- L26 _variable_ `static const float kSpreadCoeffs[5089] = { 1.0f, 1.0019f, 0.998092f, 1.01441f, 0.985357f, 1.02704f, 0.972176f, 1.03975f, 0.958555f, 1.05252f, 0.944499f, 1.06532f, 0.930017f, 1.07813f, 0.915119f, 1.09091f, 0.899819f, 1.10365f, 0.884131f, 1.11631f, 0.868073f, 1.12886f, 0.851665f, 1.14128f, 0.834929f, 1.15354f, 0.817888f, 1.16561f, 0.800569f, 1.17747f, 0.782999f, 1.1891f, 0.76521f, 1.20046f, 0.747231f, 1.21155f, 0.729095f, 1.22234f, 0.710837f, 1.23281f, 0.692489f, 1.24296f, 0.674086f, 1.25276f, 0.655664f, 1.26221f, 0.637256f, 1.27131f, 0.618896f, 1.28003f, 0.600619f, 1.28839f, 0.582456f, 1.29637f, 0.564439f, 1.30399f, 0.546597f, 1.31123f, 0.528959f, 1.31811f, 0.511551f, 1.32463f, 0.494397f, 1.3308f, 0.47752f, 1.33663f, 0.46094f, 1.34212f, 0.444677f, 1.34729f, 0.428746f, 1.35214f, 0.413161f, 1.3567f, 0.397935f, 1.36096f, 0.383079f, 1.36495f, 0.3686f, 1.36867f, 0.354505f, 1.37215f, 0.340799f, 1.37538f, 0.327486f, 1.37839f, 0.314566f, 1.38118f, 0.302039f, 1.38378f, 0.289906f, 1.38618f, 0.278163f, 1.38841f, 0.266808f, 1.39047f, 0.255835f, 1.39238f, 0.24524f, 1.39414f, 0.235017f, 1.39576f, 0.225159f, 1.39726f, 0.21566f, 1.39864f, 0.206511f, 1.39991f, 0.197704f, 1.40108f, 0.189232f, 1.40215f, 0.181084f, 1.40314f, 0.173254f, 1.40405f, 0.165731f, 1.40488f, 0.158507f, 1.40565f, 0.151572f, 1.40635f, 0.144918f, 1.40699f, 0.138535f, 1.40758f, 0.132414f, 1.40812f, 0.126546f, 1.40861f, 0.120923f, 1.40906f, 0.115536f, 1.40947f, 0.110376f, 1.40985f, 0.105436f, 1.4102f, 0.100705f, 1.41051f, 0.09 ...` (scope `vraudio`) — Lookup table with gain coefficients to control Ambisonic sound source spread at different orders, up to and including order 3. For information on how the spread control coefficients have been derived please refer to Matlab code as well as the corresponding paper.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/ambisonics/associated_legendre_polynomials_generator.h` (Private)


#### class `vraudio::AssociatedLegendrePolynomialsGenerator`  
`class AssociatedLegendrePolynomialsGenerator`  
_L26-85_
- desc: Generates associated Legendre polynomials.
- L35 _public prototype_ `AssociatedLegendrePolynomialsGenerator(int max_degree, bool condon_shortley_phase, bool compute_negative_order);` — Constructs a generator for associated Legendre polynomials (ALP). @param max_degree The maximum ALP degree supported by this generator. @param condon_shortley_phase Whether the Condon-Shortley phase, (-1)^order, should be included in the polynomials generated. @param compute_negative_order Whether this generator should compute negative-ordered polynomials.
- L44 _public prototype_ `std::vector<float> Generate(float x) const;` — Generates the associated Legendre polynomials for the given |x|, returning the computed sequence. @param x The abscissa (the polynomials' variable). @return Output vector of computed values.
- L50 _public prototype_ `size_t GetNumValues() const;` — Gets the number of associated Legendre polynomials this generator produces. @return The number of associated Legendre polynomials this generator produces.
- L58 _public prototype_ `size_t GetIndex(int degree, int order) const;` — Gets the index into the output vector for the given |degree| and |order|. @param degree The polynomial's degree. @param order The polynomial's order. @return The index into the vector of computed values corresponding to the specified ALP.
- L69 _private prototype_ `inline float ComputeValue(int degree, int order, float x, const std::vector<float>& values) const;` — Computes the ALP for (degree, order) the given |x| using recurrence relations. It is assumed that the ALPs necessary for each computation are already computed and stored in |values|. @param degree The degree of the polynomial being computed. @param degree The order of the polynomial being computed. @param values The previously computed values. @return The computed polynomial.
- L76 _private prototype_ `inline void CheckIndexValidity(int degree, int order) const;` — Checks the validity of the given index. @param degree The polynomial's degree. @param order The polynomial's order.
- L79 _private member_ `int max_degree_ = 0;` — The maximum polynomial degree that can be computed; must be >= 0.
- L82 _private member_ `bool condon_shortley_phase_ = false;` — Whether the Condon-Shortley phase, (-1)^order, should be included in the polynomials generated.
- L84 _private member_ `bool compute_negative_order_ = false;` — Whether this generator should compute negative-ordered polynomials.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_AMBISONICS_ASSOCIATED_LEGENDRE_POLYNOMIALS_GENERATOR_H_`
- L23 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/ambisonics/foa_rotator.h` (Private)


#### class `vraudio::FoaRotator`  
`class FoaRotator`  
_L27-57_
- desc: Rotator for first order ambisonic soundfields. It supports ACN channel ordering and SN3D normalization (AmbiX).
- L33 _public prototype_ `bool Process(const WorldRotation& target_rotation, const AudioBuffer& input, AudioBuffer* output);` — @param target_rotation Target rotation to be applied to the input buffer. @param input First order soundfield input buffer to be rotated. @param output Pointer to output buffer. @return True if rotation has been applied.
- L45 _private prototype_ `void Rotate(const WorldRotation& target_rotation, size_t start_location, size_t duration, const AudioBuffer& input, AudioBuffer* output);` — Method which rotates a specified chunk of data in the AudioBuffer. @param target_rotation Target rotation to be applied to the soundfield. @param start_location Sample index in the soundfield where the rotation should begin. @param duration Number of samples in soundfield to be rotated. @param input First order soundfield input buffer to be rotated. @param output Pointer to output buffer.
- L50 _private member_ `WorldRotation current_rotation_;` — Current rotation which is used in the interpolation process in order to perform a smooth rotation. Initialized with an identity matrix.
- L53 _private member_ `AudioPosition temp_audio_position_;` — Preallocation of temporary variables used during rotation.
- L54 _private member_ `WorldPosition temp_world_position_;`
- L55 _private member_ `AudioPosition temp_rotated_audio_position_;`
- L56 _private member_ `WorldPosition temp_rotated_world_position_;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_AMBISONICS_FOA_ROTATOR_H_`
- L23 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/ambisonics/hoa_rotator.h` (Private)


#### class `vraudio::HoaRotator`  
`class HoaRotator`  
_L31-66_
- desc: Rotator for higher order ambisonic sound fields. It supports ACN channel ordering and SN3D normalization (AmbiX).
- L36 _public prototype_ `explicit HoaRotator(int ambisonic_order);` — Constructs a sound field rotator of an arbitrary ambisonic order. @param ambisonic_order Order of ambisonic sound field.
- L45 _public prototype_ `bool Process(const WorldRotation& target_rotation, const AudioBuffer& input, AudioBuffer* output);` — Performs a smooth inplace rotation of a sound field buffer from |current_rotation_| to |target_rotation|. @param target_rotation Target rotation to be applied to the input buffer. @param input Higher order sound field input buffer to be rotated. @param output Pointer to output buffer. @return True if rotation has been applied.
- L52 _private prototype_ `void UpdateRotationMatrix(const WorldRotation& rotation);` — Updates the rotation matrix with using supplied WorldRotation. @param rotation World rotation.
- L55 _private member_ `const int ambisonic_order_;` — Order of the ambisonic sound field handled by the rotator.
- L59 _private member_ `WorldRotation current_rotation_;` — Current rotation which is used in the interpolation process in order to compute new rotation matrix. Initialized with an identity rotation.
- L62 _private member_ `std::vector<Eigen::MatrixXf> rotation_matrices_;` — Spherical harmonics rotation sub-matrices for each order.
- L65 _private member_ `Eigen::MatrixXf rotation_matrix_;` — Final spherical harmonics rotation matrix.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_AMBISONICS_HOA_ROTATOR_H_`
- L27 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/ambisonics/stereo_from_soundfield_converter.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_AMBISONICS_STEREO_FROM_SOUNDFIELD_CONVERTER_H_`
- L22 _namespace_ `namespace vraudio`
- L30 _prototype_ `void StereoFromSoundfield(const AudioBuffer& soundfield_input, AudioBuffer* stereo_output);` (scope `vraudio`) — Performs Ambisonic to stereo decode by performing Mid-Side (M-S) matrixing. Soundfield format assumed is Ambix (ACN/SN3D). Only first order channels are used for the stereo decode. @param soundfield_input Soundfield of arbitrary order. @param stereo_output Pointer to stereo output buffer.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/ambisonics/utils.h` (Private)


#### struct `vraudio::GetNumPeriphonicComponentsStatic`  
`template <size_t AmbisonicOrder> struct GetNumPeriphonicComponentsStatic`  
_L53-55_
- desc: Returns the number of spherical harmonics for a periphonic ambisonic sound field of |ambisonic_order| at compile-time. We have to use template metaprogramming because MSVC12 doesn't support constexpr.

#### enum `vraudio::GetNumPeriphonicComponentsStatic::(anonymous)`  
`enum`  
_L54-54_

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_AMBISONICS_UTILS_H_`
- L26 _namespace_ `namespace vraudio`
- L29 _function_ `inline int AcnSequence(int degree, int order)` (scope `vraudio`) — Returns ACN channel sequence from a degree and order of a spherical harmonic.
- L39 _function_ `inline float Sn3dNormalization(int degree, int order)` (scope `vraudio`) — Returns normalization factor for Schmidt semi-normalized spherical harmonics used in AmbiX.
- L54 _enumerator_ `enum { value = (AmbisonicOrder + 1) * (AmbisonicOrder + 1) };` (scope `vraudio::GetNumPeriphonicComponentsStatic::__anon703cd2120103`)
- L59 _function_ `inline size_t GetNumPeriphonicComponents(int ambisonic_order)` (scope `vraudio`) — Returns the number of spherical harmonics for a periphonic ambisonic sound field of |ambisonic_order|.
- L67 _function_ `inline size_t GetNumNthOrderPeriphonicComponents(int ambisonic_order)` (scope `vraudio`) — Returns the number of periphonic spherical harmonics (SHs) for a particular Ambisonic order. E.g. number of 1st, 2nd or 3rd degree SHs in a 3rd order sound field.
- L75 _function_ `inline int GetPeriphonicAmbisonicOrder(size_t num_components)` (scope `vraudio`) — Calculates the ambisonic order of a periphonic sound field with the given number of spherical harmonics.
- L92 _function_ `inline int GetPeriphonicAmbisonicOrderForChannel(size_t channel)` (scope `vraudio`) — Calculates the order of the current spherical harmonic channel as the integer part of a square root of the channel number. Please note, that in Ambisonics the terms 'order' (usually denoted as 'n') and 'degree' (usually denoted as 'm') are used in the opposite meaning as in more traditional maths or physics conventions: [1] C. Nachbar, F. Zotter, E. Deleflie, A. Sontacchi, "AMBIX - A SUGGESTED AMBISONICS FORMAT", Proc. of the 2nd Ambisonics Symposium, June 2-3 2011, Lexington, KY, https://goo.gl/jzt4Yy.
- L103 _function_ `inline int GetPeriphonicAmbisonicDegreeForChannel(size_t channel)` (scope `vraudio`) — Calculates the degree of the current spherical harmonic channel. Please note, that in Ambisonics the terms 'order' (usually denoted as 'n') and 'degree' (usually denoted as 'm') are used in the opposite meaning as in more traditional maths or physics conventions: [1] C. Nachbar, F. Zotter, E. Deleflie, A. Sontacchi, "AMBIX - A SUGGESTED AMBISONICS FORMAT", Proc. of the 2nd Ambisonics Symposium, June 2-3 2011, Lexington, KY, https://goo.gl/jzt4Yy.
- L110 _function_ `inline bool IsValidAmbisonicOrder(size_t num_channels)` (scope `vraudio`) — Returns whether the given |num_channels| corresponds to a valid ambisonic order configuration.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/api/binaural_surround_renderer.h` (Private)


#### class `vraudio::BinauralSurroundRenderer`  
`class BinauralSurroundRenderer`  
_L30-251_
- desc: Renders virtual surround sound as well as ambisonic soundfields to binaural stereo.
- L109 _public prototype_ `virtual ~BinauralSurroundRenderer() = default;`
- L119 _public prototype_ `static BinauralSurroundRenderer* Create(size_t frames_per_buffer, int sample_rate_hz, SurroundFormat surround_format);` — Factory method to create a |BinauralSurroundRenderer| instance. Caller must take ownership of returned instance and destroy it via operator delete. @param frames_per_buffer Number of frames in output buffer. @param sample_rate_hz Sample rate of audio buffers. @param surround_format Input surround sound format. @param return |BinauralSurroundRenderer| instance, nullptr if creation fails.
- L130 _public prototype_ `virtual void SetStereoSpeakerMode(bool enabled) = 0;` — Enables the stereo speaker mode. When activated, it disables HRTF-based filtering and switches to computationally cheaper stereo-panning. This helps to avoid HRTF-based coloring effects when stereo speakers are used and reduces computational complexity when headphone-based HRTF filtering is not needed. By default the stereo speaker mode is disabled. @param enabled Flag to enable stereo speaker mode.
- L135 _public prototype_ `virtual size_t GetNumAvailableFramesInInputBuffer() const = 0;` — Returns the number of frames the input buffer is currently able to consume. @return Number of available frames in input buffer.
- L148 _public prototype_ `virtual size_t AddInterleavedInput(const int16* input_buffer_ptr, size_t num_channels, size_t num_frames) = 0;` — Adds interleaved int16 audio data to the renderer. If enough data has been provided for an output buffer to be generated then it will be immediately available via |Get[Interleaved|Planar]StereoOutputBuffer|. The input data is copied into an internal buffer which allows the caller to re-use the input buffer immediately. The available space in the internal buffer can be obtained via |GetAvailableInputSizeSamples|. @param input_buffer_ptr Pointer to interleaved input data. @param num_channels Number of channels in input buffer. @param num_frames Number of frames in input buffer. @return The number of consumed frames.
- L163 _public prototype_ `virtual size_t AddInterleavedInput(const float* input_buffer_ptr, size_t num_channels, size_t num_frames) = 0;` — Adds interleaved floating point audio data to the renderer. If enough data has been provided for an output buffer to be generated then it will be immediately available via |Get[Interleaved|Planar]StereoOutputBuffer|. The input data is copied into an internal buffer which allows the caller to re-use the input buffer immediately. The available space in the internal buffer can be obtained via |GetAvailableInputSizeSamples|. @param input_buffer_ptr Pointer to interleaved input data. @param num_channels Number of channels in input buffer. @param num_frames Number of frames in input buffer. @return The number of consumed frames.
- L178 _public prototype_ `virtual size_t AddPlanarInput(const int16* const* input_buffer_ptrs, size_t num_channels, size_t num_frames) = 0;` — Adds planar int16 audio data to the renderer. If enough data has been provided for an output buffer to be generated then it will be immediately available via |Get[Interleaved|Planar]StereoOutputBuffer|. The input data is copied into an internal buffer which allows the caller to re-use the input buffer immediately. The available space in the internal buffer can be obtained via |GetAvailableInputSizeSamples|. @param input_buffer_ptrs Array of pointers to planar channel data. @param num_channels Number of channels in input buffer. @param num_frames Number of frames in input buffer. @return The number of consumed frames.
- L192 _public prototype_ `virtual size_t AddPlanarInput(const float* const* input_buffer_ptrs, size_t num_channels, size_t num_frames) = 0;` — Adds planar floating point audio data to the renderer. If enough data has been provided for an output buffer to be generated then it will be immediately available via |Get[Interleaved|Planar]StereoOutputBuffer|. The input data is copied into an internal buffer which allows the caller to re-use the input buffer immediately. The available space in the internal buffer can be obtained via |GetAvailableInputSizeSamples|. @param input_buffer_ptrs Array of pointers to planar channel data. @param num_channels Number of channels in input buffer. @param num_frames Number of frames in input buffer. @return The number of consumed frames.
- L198 _public prototype_ `virtual size_t GetAvailableFramesInStereoOutputBuffer() const = 0;` — Returns the number of samples available in the output buffer. @return Number of available samples in output buffer.
- L205 _public prototype_ `virtual size_t GetInterleavedStereoOutput(int16* output_buffer_ptr, size_t num_frames) = 0;` — Gets a processed output buffer in interleaved int16 format. @param output_buffer_ptr Pointer to allocated interleaved output buffer. @param num_frames Size of output buffer in frames. @return The number of consumed frames.
- L213 _public prototype_ `virtual size_t GetInterleavedStereoOutput(float* output_buffer_ptr, size_t num_frames) = 0;` — Gets a processed output buffer in interleaved float format. @param output_buffer_ptr Pointer to allocated interleaved output buffer. @param num_frames Size of output buffer in frames. @return The number of consumed frames.
- L221 _public prototype_ `virtual size_t GetPlanarStereoOutput(int16** output_buffer_ptrs, size_t num_frames) = 0;` — Gets a processed output buffer in planar int16 point format. @param output_buffer_ptrs Array of pointers to planar channel data. @param num_frames Number of frames in output buffer. @return The number of consumed frames.
- L229 _public prototype_ `virtual size_t GetPlanarStereoOutput(float** output_buffer_ptrs, size_t num_frames) = 0;` — Gets a processed output buffer in planar floating point format. @param output_buffer_ptrs Array of pointers to planar channel data. @param num_frames Number of frames in output buffer. @return The number of consumed frames.
- L234 _public prototype_ `virtual void Clear() = 0;` — Removes all buffered input and processed output buffers from the buffer queues.
- L242 _public prototype_ `virtual bool TriggerProcessing() = 0;` — Triggers the processing of data that has been input but not yet processed. Note after calling this method, all processed output must be consumed via |Get[Interleaved|Planar]StereoOutputBuffer| before adding new input buffers. @return Whether any data was processed.
- L250 _public prototype_ `virtual void SetHeadRotation(float w, float x, float y, float z) = 0;` — Updates the head rotation. @param w W component of quaternion. @param x X component of quaternion. @param y Y component of quaternion. @param z Z component of quaternion.

#### enum `vraudio::BinauralSurroundRenderer::SurroundFormat`  
`enum SurroundFormat`  
_L33-106_
- L35 _public enumerator_ `kInvalid = 0` — Enables to initialize a yet undefined rendering mode.
- L38 _public enumerator_ `kSurroundMono = 1` — Binaurally renders a single virtual speaker at 0 degrees in front.
- L42 _public enumerator_ `kSurroundStereo = 2` — Binaurally renders virtual stereo speakers at -30 degrees and +30 degrees.
- L56 _public enumerator_ `kSurroundFiveDotOne = 3` — Binaurally renders 5.1 surround sound according to the ITU-R BS.775-3 speaker configuration recommendation: - Left (L) at 30 degrees. - Right (R) at -30 degrees. - Center (C) at 0 degrees. - Low frequency effects (LFE) at front center at 0 degrees. - Left surround (LS) at 110 degrees. - Right surround (RS) at -110 degrees. The 5.1 channel input layout must matches AAC: L, R, C, LFE, LS, RS. Note that this differs from the Vorbis/Opus 5.1 channel layout, which is: L, C, R, LS, RS, LFE.
- L73 _public enumerator_ `kSurroundSevenDotOne = 10` — Binaurally renders 7.1 surround sound according to the ITU-R BS.775-3 speaker configuration recommendation: - Left (FL) at 30 degrees. - Right (FR) at -30 degrees. - Center (C) at 0 degrees. - Low frequency effects (LFE) at front center at 0 degrees. - Left surround 1 (LS1) at 90 degrees. - Right surround 1 (RS1) at -90 degrees. - Left surround 2 (LS2) at 150 degrees. - Right surround 2 (LS2) at -150 degrees. The 7.1 channel input layout must matches AAC: L, R, C, LFE, LS1, RS1, LS2, RS2. Note that this differs from the Vorbis/Opus 7.1 channel layout, which is: L, C, R, LS1, RS1, LS2, RS2, LFE.
- L77 _public enumerator_ `kFirstOrderAmbisonics = 4` — Binaurally renders first-order ambisonics (AmbiX format: 4 channels, ACN channel ordering, SN3D normalization).
- L81 _public enumerator_ `kSecondOrderAmbisonics = 5` — Binaurally renders second-order ambisonics. (AmbiX format: 9 channels, ACN channel ordering, SN3D normalization).
- L85 _public enumerator_ `kThirdOrderAmbisonics = 6` — Binaurally renders third-order ambisonics. (AmbiX format: 16 channels, ACN channel ordering, SN3D normalization).
- L91 _public enumerator_ `kFirstOrderAmbisonicsWithNonDiegeticStereo = 7` — Binaurally renders first-order ambisonics with a non-diegetic-stereo track. The first 4 channels contain ambisonic AmbiX format. (AmbiX format: 4 channels, ACN channel ordering, SN3D normalization). Channel 5 to 6 contain non-diegetic-stereo.
- L97 _public enumerator_ `kSecondOrderAmbisonicsWithNonDiegeticStereo = 8` — Binaurally renders second-order ambisonics with a non-diegetic-stereo track. The first 9 channels contain ambisonic AmbiX format. (AmbiX format: 9 channels, ACN channel ordering, SN3D normalization). Channel 10 to 11 contain non-diegetic-stereo.
- L103 _public enumerator_ `kThirdOrderAmbisonicsWithNonDiegeticStereo = 9` — Binaurally renders third-order ambisonics with a non-diegetic-stereo track. The first 16 channels contain ambisonic AmbiX format. (AmbiX format: 16 channels, ACN channel ordering, SN3D normalization). Channel 17 to 18 contain non-diegetic-stereo.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_API_BINAURAL_SURROUND_RENDERER_H_`
- L24 _typedef_ `typedef int16_t int16;` — Avoid dependency to base/integral_types.h
- L26 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/api/resonance_audio_api.h` (Private)


#### enum `vraudio::RenderingMode`  
`enum RenderingMode`  
_L37-56_
- desc: Rendering modes define CPU load / rendering quality balances. Note that this struct is C-compatible by design to be used across external C/C++ and C# implementations.
- L39 _public enumerator_ `kStereoPanning = 0` — Stereo panning, i.e., this disables HRTF-based rendering.
- L42 _public enumerator_ `kBinauralLowQuality` — HRTF-based rendering using First Order Ambisonics, over a virtual array of 8 loudspeakers arranged in a cube configuration around the listener's head.
- L46 _public enumerator_ `kBinauralMediumQuality` — HRTF-based rendering using Second Order Ambisonics, over a virtual array of 12 loudspeakers arranged in a dodecahedral configuration (using faces of the dodecahedron).
- L49 _public enumerator_ `kBinauralHighQuality` — HRTF-based rendering using Third Order Ambisonics, over a virtual array of 26 loudspeakers arranged in a Lebedev grid: https://goo.gl/DX1wh3.
- L55 _public enumerator_ `kRoomEffectsOnly` — Room effects only rendering. This disables HRTF-based rendering and direct (dry) output of a sound object. Note that this rendering mode should *not* be used for general-purpose sound object spatialization, as it will only render the corresponding room effects of given sound objects without the direct spatialization.

#### enum `vraudio::DistanceRolloffModel`  
`enum DistanceRolloffModel`  
_L61-68_
- desc: Distance rolloff models used for distance attenuation. Note that this enum is C-compatible by design to be used across external C/C++ and C# implementations.
- L63 _public enumerator_ `kLogarithmic = 0` — Logarithmic distance rolloff model.
- L65 _public enumerator_ `kLinear` — Linear distance rolloff model.
- L67 _public enumerator_ `kNone` — Distance attenuation value will be explicitly set by the user.

#### struct `vraudio::ReflectionProperties`  
`struct ReflectionProperties`  
_L73-106_
- desc: Early reflection properties of an acoustic environment. Note that this struct is C-compatible by design to be used across external C/C++ and C# implementations.
- L75 _public function_ `ReflectionProperties() : room_position` — Default constructor initializing all data members to 0.
- L84 _public member_ `float room_position[3];` — Center position of the shoebox room in world space.
- L87 _public member_ `float room_rotation[4];` — Rotation (quaternion) of the shoebox room in world space.
- L90 _public member_ `float room_dimensions[3];` — Size of the shoebox shoebox room in world space.
- L93 _public member_ `float cutoff_frequency;` — Frequency threshold for low pass filtering (-3dB cuttoff).
- L102 _public member_ `float coefficients[6];` — Reflection coefficients that are stored in world space as follows: [0]  (-)ive x-axis wall (left) [1]  (+)ive x-axis wall (right) [2]  (-)ive y-axis wall (bottom) [3]  (+)ive y-axis wall (top) [4]  (-)ive z-axis wall (front) [5]  (+)ive z-axis wall (back)
- L105 _public member_ `float gain;` — Uniform reflections gain which is applied to all reflections.

#### struct `vraudio::ReverbProperties`  
`struct ReverbProperties`  
_L111-123_
- desc: Late reverberation properties of an acoustic environment. Note that this struct is C-compatible by design to be used across external C/C++ and C# implementations.
- L113 _public function_ `ReverbProperties() : rt60_values` — Default constructor initializing all data members to 0.
- L119 _public member_ `float rt60_values[9];` — RT60's of the reverberation tail at different octave band centre frequencies in seconds.
- L122 _public member_ `float gain;` — Reverb gain.

#### class `vraudio::ResonanceAudioApi`  
`class ResonanceAudioApi`  
_L142-411_
- desc: The ResonanceAudioApi library renders high-quality spatial audio. It provides methods to binaurally render virtual sound sources with simulated room acoustics. In addition, it supports decoding and binaural rendering of ambisonic soundfields. Its implementation is single-threaded, thread-safe and non-blocking to be able to process raw PCM audio buffers directly on the audio thread while receiving parameter updates from the main/render thread.
- L145 _public typedef_ `typedef int SourceId;` — Sound object / ambisonic source identifier.
- L149 _public member_ `static const SourceId kInvalidSourceId = -1;` — Invalid source id that can be used to initialize handler variables during class construction.
- L151 _public prototype_ `virtual ~ResonanceAudioApi() = default;`
- L159 _public prototype_ `virtual bool FillInterleavedOutputBuffer(size_t num_channels, size_t num_frames, float* buffer_ptr) = 0;` — Renders and outputs an interleaved output buffer in float format. @param num_frames Size of output buffer in frames. @param num_channels Number of channels in output buffer. @param buffer_ptr Raw float pointer to audio buffer. @return True if a valid output was successfully rendered, false otherwise.
- L169 _public prototype_ `virtual bool FillInterleavedOutputBuffer(size_t num_channels, size_t num_frames, int16* buffer_ptr) = 0;` — Renders and outputs an interleaved output buffer in int16 format. @param num_channels Number of channels in output buffer. @param num_frames Size of output buffer in frames. @param buffer_ptr Raw int16 pointer to audio buffer. @return True if a valid output was successfully rendered, false otherwise.
- L180 _public prototype_ `virtual bool FillPlanarOutputBuffer(size_t num_channels, size_t num_frames, float* const* buffer_ptr) = 0;` — Renders and outputs a planar output buffer in float format. @param num_frames Size of output buffer in frames. @param num_channels Number of channels in output buffer. @param buffer_ptr Pointer to array of raw float pointers to each channel of the audio buffer. @return True if a valid output was successfully rendered, false otherwise.
- L190 _public prototype_ `virtual bool FillPlanarOutputBuffer(size_t num_channels, size_t num_frames, int16* const* buffer_ptr) = 0;` — Renders and outputs a planar output buffer in int16 format. @param num_channels Number of channels in output buffer. @param num_frames Size of output buffer in frames. @param buffer_ptr Pointer to array of raw int16 pointers to each channel of the audio buffer. @return True if a valid output was successfully rendered, false otherwise.
- L198 _public prototype_ `virtual void SetHeadPosition(float x, float y, float z) = 0;` — Sets listener's head position. @param x X coordinate of head position in world space. @param y Y coordinate of head position in world space. @param z Z coordinate of head position in world space.
- L206 _public prototype_ `virtual void SetHeadRotation(float x, float y, float z, float w) = 0;` — Sets listener's head rotation. @param x X component of quaternion. @param y Y component of quaternion. @param z Z component of quaternion. @param w W component of quaternion.
- L212 _public prototype_ `virtual void SetPrimaryVolume(float volume) = 0;` — Sets the Primary volume of the main audio output. @param volume Primary volume (linear) in amplitude in range [0, 1] for attenuation, range [1, inf) for gain boost.
- L223 _public prototype_ `virtual void SetStereoSpeakerMode(bool enabled) = 0;` — Enables the stereo speaker mode. When activated, it disables HRTF-based filtering and switches to computationally cheaper stereo-panning. This helps to avoid HRTF-based coloring effects when stereo speakers are used and reduces computational complexity when headphone-based HRTF filtering is not needed. By default the stereo speaker mode is disabled. Note that stereo speaker mode overrides the |enable_hrtf| flag in |CreateSoundObjectSource|. @param enabled Flag to enable stereo speaker mode.
- L229 _public prototype_ `virtual SourceId CreateAmbisonicSource(size_t num_channels) = 0;` — Creates an ambisonic source instance. @param num_channels Number of input channels. @return Id of new ambisonic source.
- L236 _public prototype_ `virtual SourceId CreateStereoSource(size_t num_channels) = 0;` — Creates a stereo non-spatialized source instance, which directly plays back mono or stereo audio. @param num_channels Number of input channels. @return Id of new non-spatialized source.
- L242 _public prototype_ `virtual SourceId CreateSoundObjectSource(RenderingMode rendering_mode) = 0;` — Creates a sound object source instance. @param rendering_mode Rendering mode which governs quality and performance. @return Id of new sound object source.
- L247 _public prototype_ `virtual void DestroySource(SourceId id) = 0;` — Destroys source instance. @param source_id Id of source to be destroyed.
- L255 _public prototype_ `virtual void SetInterleavedBuffer(SourceId source_id, const float* audio_buffer_ptr, size_t num_channels, size_t num_frames) = 0;` — Sets the next audio buffer in interleaved float format to a sound source. @param source_id Id of sound source. @param audio_buffer_ptr Pointer to interleaved float audio buffer. @param num_channels Number of channels in interleaved audio buffer. @param num_frames Number of frames per channel in interleaved audio buffer.
- L265 _public prototype_ `virtual void SetInterleavedBuffer(SourceId source_id, const int16* audio_buffer_ptr, size_t num_channels, size_t num_frames) = 0;` — Sets the next audio buffer in interleaved int16 format to a sound source. @param source_id Id of sound source. @param audio_buffer_ptr Pointer to interleaved int16 audio buffer. @param num_channels Number of channels in interleaved audio buffer. @param num_frames Number of frames per channel in interleaved audio buffer.
- L276 _public prototype_ `virtual void SetPlanarBuffer(SourceId source_id, const float* const* audio_buffer_ptr, size_t num_channels, size_t num_frames) = 0;` — Sets the next audio buffer in planar float format to a sound source. @param source_id Id of sound source. @param audio_buffer_ptr Pointer to array of pointers referring to planar audio buffers for each channel. @param num_channels Number of planar input audio buffers. @param num_frames Number of frames per channel.
- L287 _public prototype_ `virtual void SetPlanarBuffer(SourceId source_id, const int16* const* audio_buffer_ptr, size_t num_channels, size_t num_frames) = 0;` — Sets the next audio buffer in planar int16 format to a sound source. @param source_id Id of sound source. @param audio_buffer_ptr Pointer to array of pointers referring to planar audio buffers for each channel. @param num_channels Number of planar input audio buffers. @param num_frames Number of frames per channel.
- L297 _public prototype_ `virtual void SetSourceDistanceAttenuation(SourceId source_id, float distance_attenuation) = 0;` — Sets the given source's distance attenuation value explicitly. The distance rolloff model of the source must be set to |DistanceRolloffModel::kNone| for the set value to take effect. @param source_id Id of source. @param distance_attenuation Distance attenuation value.
- L308 _public prototype_ `virtual void SetSourceDistanceModel(SourceId source_id, DistanceRolloffModel rolloff, float min_distance, float max_distance) = 0;` — Sets the given source's distance attenuation method with minimum and maximum distances. Maximum distance must be greater than the minimum distance for the method to be set. @param source_id Id of source. @param rolloff Linear or logarithmic distance rolloff models. @param min_distance Minimum distance to apply distance attenuation method. @param max_distance Maximum distance to apply distance attenuation method.
- L321 _public prototype_ `virtual void SetSourcePosition(SourceId source_id, float x, float y, float z) = 0;` — Sets the given source's position. Note that, the given position for an ambisonic source is only used to determine the corresponding room effects to be applied. @param source_id Id of source. @param x X coordinate of source position in world space. @param y Y coordinate of source position in world space. @param z Z coordinate of source position in world space.
- L329 _public prototype_ `virtual void SetSourceRoomEffectsGain(SourceId source_id, float room_effects_gain) = 0;` — Sets the room effects contribution for the given source. @param source_id Id of source. @param room_effects_gain Linear room effects volume in amplitude in range [0, 1] for attenuation, range [1, inf) for gain boost.
- L339 _public prototype_ `virtual void SetSourceRotation(SourceId source_id, float x, float y, float z, float w) = 0;` — Sets the given source's rotation. @param source_id Id of source. @param x X component of quaternion. @param y Y component of quaternion. @param z Z component of quaternion. @param w W component of quaternion.
- L347 _public prototype_ `virtual void SetSourceVolume(SourceId source_id, float volume) = 0;` — Sets the given source's volume. @param source_id Id of source. @param volume Linear source volume in amplitude in range [0, 1] for attenuation, range [1, inf) for gain boost.
- L357 _public prototype_ `virtual void SetSoundObjectDirectivity(SourceId sound_object_source_id, float alpha, float order) = 0;` — Sets the given sound object source's directivity. @param sound_object_source_id Id of sound object source. @param alpha Weighting balance between figure of eight pattern and circular pattern for source emission in range [0, 1]. A value of 0.5 results in a cardioid pattern. @param order Order applied to computed directivity. Higher values will result in narrower and sharper directivity patterns. Range [1, inf).
- L371 _public prototype_ `virtual void SetSoundObjectListenerDirectivity( SourceId sound_object_source_id, float alpha, float order) = 0;` — Sets the listener's directivity with respect to the given sound object. This method could be used to simulate an angular rolloff in terms of the listener's orientation, given the polar pickup pattern with |alpha| and |order|. @param sound_object_source_id Id of sound object source. @param alpha Weighting balance between figure of eight pattern and circular pattern for listener's pickup in range [0, 1]. A value of 0.5 results in a cardioid pattern. @param order Order applied to computed pickup pattern. Higher values will result in narrower and sharper pickup patterns. Range [1, inf).
- L379 _public prototype_ `virtual void SetSoundObjectNearFieldEffectGain( SourceId sound_object_source_id, float gain) = 0;` — Sets the gain (linear) of the near field effect. @param sound_object_source_id Id of sound object source. @param gain Gain of the near field effect. Range [0, 9] (corresponding to approx. (-Inf, +20dB]).
- L387 _public prototype_ `virtual void SetSoundObjectOcclusionIntensity(SourceId sound_object_source_id, float intensity) = 0;` — Sets the given sound object source's occlusion intensity. @param sound_object_source_id Id of sound object source. @param intensity Number of occlusions occurred for the object. The value can be set to fractional for partial occlusions. Range [0, inf).
- L394 _public prototype_ `virtual void SetSoundObjectSpread(SourceId sound_object_source_id, float spread_deg) = 0;` — Sets the given sound object source's spread. @param sound_object_source_id Id of sound object source. @param spread_deg Spread in degrees.
- L398 _public prototype_ `virtual void EnableRoomEffects(bool enable) = 0;` — Turns on/off the reflections and reverberation.
- L403 _public prototype_ `virtual void SetReflectionProperties( const ReflectionProperties& reflection_properties) = 0;` — Sets the early reflection properties of the environment. @param reflection_properties Reflection properties.
- L409 _public prototype_ `virtual void SetReverbProperties( const ReverbProperties& reverb_properties) = 0;` — Sets the late reverberation properties of the environment. @param reverb_properties Reverb properties.

#### Free symbols / members of external scopes

- L19 _macro_ `#define RESONANCE_AUDIO_API_RESONANCE_AUDIO_API_H_`
- L23 _macro_ `#define EXPORT_API`
- L30 _typedef_ `typedef int16_t int16;`
- L32 _namespace_ `namespace vraudio`
- L133 _prototype_ `extern "C" ResonanceAudioApi* CreateResonanceAudioApi( size_t num_channels, size_t frames_per_buffer, int sample_rate_hz);` (scope `vraudio`) — Factory method to create a |ResonanceAudioApi| instance. Caller must take ownership of returned instance and destroy it via operator delete. @param num_channels Number of channels of audio output. @param frames_per_buffer Number of frames per buffer. @param sample_rate_hz System sample rate.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/base/aligned_allocator.h` (Private)


#### class `vraudio::AlignedAllocator`  
`template <typename Type, size_t Alignment> class AlignedAllocator : public std::allocator<Type>`  
_L83-123_
- inherits: `std::allocator<Type>`
- desc: Class that allocates aligned memory. It is derived from std::allocator class to be used with STL containers. @tparam Type Datatype of container to allocate. @tparam Alignment Size of memory alignment.
- L85 _public typedef_ `using Pointer = typename std::allocator_traits<std::allocator<Type>>::pointer;`
- L86 _public typedef_ `using ConstPointer = typename std::allocator_traits<std::allocator<Type>>::const_pointer;`
- L87 _public typedef_ `using SizeType = typename std::allocator_traits<std::allocator<Type>>::size_type;`
- L89 _public function_ `AlignedAllocator()`
- L96 _public function_ `Pointer allocate(SizeType size)` — Allocates memory for |size| elements and returns a pointer that is aligned to a multiple to |Alignment|. @param size Number of elements to allocate. @return Returns memory aligned pointer.
- L103 _public function_ `Pointer allocate(SizeType size, ConstPointer )` — Allocates memory for |size| elements and returns a pointer that is aligned to a multiple to |Alignment|. @param size Number of elements to allocate. @return Returns memory aligned pointer.
- L108 _public function_ `void deallocate(Pointer mem_block_aligned, size_t size)`
- L114 _public function_ `template <typename U> explicit AlignedAllocator<Type, Alignment>( const AlignedAllocator<U, Alignment>& other)` — Copy constructor to support rebind operation (to make MSVC happy).

#### struct `vraudio::AlignedAllocator::rebind`  
`template <typename U> struct rebind`  
_L120-122_
- desc: Rebind is used to allocate container internal variables of type |U| (which don't need to be aligned).
- L121 _public typedef_ `typedef AlignedAllocator<U, Alignment> other;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_BASE_ALIGNED_ALLOCATOR_H_`
- L40 _namespace_ `namespace vraudio`
- L44 _function_ `template <size_t TypeSize, size_t Alignment> void StaticAlignmentCheck()` (scope `vraudio`) — Performs static assert checks on the types size and alignment parameters.
- L55 _function_ `template <typename Type, typename SizeType, typename PointerType> PointerType AllignedMalloc(SizeType size, SizeType alignment)` (scope `vraudio`) — Returns a pointer to aligned memory.
- L73 _function_ `template <typename PointerType> void AllignedFree(PointerType mem_block_aligned)` (scope `vraudio`) — Frees memory that has been aligned with |AllignedMalloc|.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/base/audio_buffer.h` (Private)


#### class `vraudio::AudioBuffer`  
`class AudioBuffer`  
_L78-218_
- desc: Audio buffer that manages multi-channel audio data in a planar data format. All channels are sequentially stored within a single consecutive chunk of memory. To access individual channel data, the array subscript operator can be used to obtain a |AudioBuffer::Channel|. Note that the user must guarantee that the AudioBuffer instance lives as long as its channel data is accessed via |AudioBuffer::Channel|s. Note that allocated buffers may *not* be initialized to zero. Examples: // Range-based for-loop over all channels and all samples. AudioBuffer audio_buffer(...) for (AudioBuffer::Channel& channel : audio_buffer) { for (float& sample : channel) { sample *= gain; } } // Range-based for-loop over all channels and array subscripts-based for-loop // to access samples. AudioBuffer audio_buffer(...) for (AudioBuffer::Channel& channel : audio_buffer) { for (size_t i = 0; i < channel.num_frames(); ++i) { channel[i] *= gain; } } // Array subscript-based for-loops over all channels samples. // AudioBuffer audio_buffer(...) for (size_t c=0; c < audio_buffer.num_channels(); ++c) { // First obtain a reference to AudioBuffer::Channel. AudioBuffer::Channel& channel = audio_buffer[c]; for (size_t i = 0; i < channel.num_frames(); ++i) { channel[i] *= gain; } } Note do *NOT* use double array subscripts to iterate over multiple samples since it performs a channel iterator lookup for every sample: for (size_t c=0; c < audio_buffer.num_channels(); ++c) { for (size_t i = 0; i < channel.size(); ++i
- L81 _public typedef_ `typedef ChannelView Channel;` — View on separate audio channel.
- L84 _public typedef_ `typedef AlignedAllocator<float, kMemoryAlignmentBytes> FloatAllocator;` — Allocator class to allocate aligned floats.
- L87 _public typedef_ `typedef AlignedAllocator<int16, kMemoryAlignmentBytes> Int16Allocator;` — Allocator class to allocate aligned int16s.
- L90 _public typedef_ `typedef std::vector<float, FloatAllocator> AlignedFloatVector;` — AlignedFloatBuffer for storing audio data.
- L93 _public typedef_ `typedef std::vector<int16, Int16Allocator> AlignedInt16Vector;` — AlignedInt16Buffer for storing audio data.
- L96 _public prototype_ `AudioBuffer();` — Default constructor initializes an empty |AudioBuffer|.
- L102 _public prototype_ `AudioBuffer(size_t num_channels, size_t num_frames);` — Constructor. @param num_channels Number of channels. @param num_frames Number of frames.
- L105 _public prototype_ `AudioBuffer(AudioBuffer&& other);` — Move constructor.
- L109 _public prototype_ `AudioBuffer(const AudioBuffer& other) = delete;` — Copy constructor is explicitly deleted to prevent accidental copies. Use copy assignment operator instead.
- L112 _public prototype_ `AudioBuffer& operator=(const AudioBuffer& other);` — Copy assignment from AudioBuffer.
- L115 _public function_ `size_t num_channels() const` — Returns the number of audio channels.
- L118 _public function_ `size_t num_frames() const` — Returns the number of frames per buffer.
- L121 _public function_ `SourceId source_id() const` — Returns this buffer's source id.
- L124 _public function_ `Channel& operator[](size_t channel)` — Returns a reference to the selected ChannelView.
- L130 _public function_ `const Channel& operator[](size_t channel) const` — Returns a const reference to the selected ChannelView.
- L136 _public function_ `AudioBuffer& operator=(const std::vector<std::vector<float>>& other)` — Copy assignment from std::vector<std::vector<float>>.
- L145 _public function_ `AudioBuffer& operator+=(const AudioBuffer& other)` — += operator
- L155 _public function_ `AudioBuffer& operator-=(const AudioBuffer& other)` — -= operator
- L165 _public function_ `std::vector<Channel>::iterator begin()` — Returns an iterator to the ChannelView of the first channel.
- L168 _public function_ `std::vector<Channel>::iterator end()` — Returns an iterator to the end of the ChannelView vector.
- L171 _public function_ `std::vector<Channel>::const_iterator begin() const` — Returns a const_iterator to the ChannelView of the first channel.
- L176 _public function_ `std::vector<Channel>::const_iterator end() const` — Returns an const_iterator to the end of the ChannelView vector.
- L181 _public function_ `void Clear()` — Fills all channels with zeros and reenables |Channel|s.
- L191 _public function_ `size_t GetChannelStride() const` — Returns the number of allocated frames per |Channel|. Note this may differ from the actual size of the |Channel| to ensure alignment of all |Channel|s.
- L197 _public function_ `void set_source_id(SourceId source_id)` — Sets the source id of which the buffer belongs to.
- L201 _private prototype_ `void InitChannelViews(size_t num_channels);` — Allocates memory and initializes vector of |ChannelView|s.
- L204 _private member_ `size_t num_frames_;` — Number of frames per buffer.
- L208 _private member_ `AlignedFloatVector data_;` — Audio buffer that sequentially stores multiple audio channels in a planar format.
- L211 _private member_ `size_t data_size_;` — Size of audio buffer.
- L214 _private member_ `std::vector<Channel> channel_views_;` — Vector of |AudioBuffer::Channel|s.
- L217 _private member_ `SourceId source_id_;` — Id of a source that this buffer belongs to.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_BASE_AUDIO_BUFFER_H_`
- L31 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/base/channel_view.h` (Private)


#### class `vraudio::ChannelView`  
`class ChannelView`  
_L30-140_
- desc: Provides an interface to a single audio channel in |AudioBuffer|. Note that a |ChannelView| instance does not own the data it is initialized with.
- L35 _public prototype_ `ChannelView(const ChannelView&) = default;` — @third party code - Epic Games Begin This is here for this warning as of Clang 16: channel_view.h(82,16): error: definition of implicit copy constructor for 'ChannelView' is deprecated because it has a user-provided copy assignment operator [-Werror,-Wdeprecated-copy-with-user-provided-copy]
- L39 _public function_ `float& operator[](size_t index)` — Array subscript operator returning a reference.
- L46 _public function_ `const float& operator[](size_t index) const` — Const array subscript operator returning a const reference.
- L53 _public function_ `size_t size() const` — Returns the size of the channel in samples.
- L56 _public function_ `float* begin()` — Returns a float pointer to the begin of the channel data.
- L62 _public function_ `float* end()` — Returns a float pointer to the end of the channel data.
- L68 _public function_ `const float* begin() const` — Returns a const float pointer to the begin of the channel data.
- L74 _public function_ `const float* end() const` — Returns a const float pointer to the end of the channel data.
- L80 _public function_ `ChannelView& operator=(const std::vector<float>& other)` — Copy assignment from float vector.
- L88 _public function_ `ChannelView& operator=(const ChannelView& other)` — Copy assignment from ChannelView.
- L98 _public prototype_ `ChannelView& operator+=(const ChannelView& other);` — Adds a |ChannelView| to this |ChannelView|.
- L101 _public prototype_ `ChannelView& operator-=(const ChannelView& other);` — Subtracts a |ChannelView| from this |ChannelView|.
- L104 _public prototype_ `ChannelView& operator*=(const ChannelView& other);` — Pointwise multiplies a |ChannelView| with this |Channelview|.
- L107 _public function_ `void Clear()` — Fills channel buffer with zeros.
- L117 _public function_ `void SetEnabled(bool enabled)` — Allows for disabling the channel to prevent access to the channel data and channel iterators. It is used in the |Mixer| class to prevent the copies of silence |ChannelView|s. Note that |ChannelView| are enabled by default. @param enabled True to enable the channel.
- L122 _public function_ `bool IsEnabled() const` — Returns true if |ChannelView| is enabled. @return State of |enabled_| flag.
- L129 _private function_ `ChannelView(float* begin_itr, size_t size) : begin_itr_(begin_itr), size_(size), enabled_(true)` — Constructor is initialized with a float pointer to the first sample and the size of chunk of planar channel data.
- L133 _private member_ `float* const begin_itr_;` — Iterator of first and last element in channel.
- L136 _private member_ `const size_t size_;` — Channel size.
- L139 _private member_ `bool enabled_;` — Flag indicating if the channel is enabled.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_BASE_CHANNEL_VIEW_H_`
- L26 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/base/constants_and_types.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_BASE_CONSTANTS_AND_TYPES_H_`
- L24 _macro_ `#define DEFINED_M_PI`
- L25 _macro_ `#define M_PI 3.14159265358979323846`
- L28 _namespace_ `namespace vraudio`
- L32 _typedef_ `typedef int SourceId;` (scope `vraudio`)
- L36 _variable_ `inline constexpr SourceId kInvalidSourceId = -1;` (scope `vraudio`) — Invalid source id that can be used to initialize handler variables during class construction.
- L42 _variable_ `inline const size_t kMemoryAlignmentBytes = 64;` (scope `vraudio`) — Defines memory alignment of audio buffers. Note that not only the first element of the |data_| buffer is memory aligned but also the address of the first elements of the |ChannelView|s.
- L49 _variable_ `inline constexpr int kMaxSupportedAmbisonicOrder = 3;` (scope `vraudio`) — Maximum Ambisonic order currently supported in vr audio, equivalent to High Quality sound object rendering mode. This number is limited by a) number of HRIR data points used in the binaural renderer; b) size of the lookup table controlling the angular spread of a sound source in the Ambisonic Lookup Table class.
- L52 _variable_ `inline const size_t kMaxSupportedNumFrames = 16384;` (scope `vraudio`) — Maximum allowed size of internal buffers.
- L55 _variable_ `inline constexpr size_t kNumMonoChannels = 1;` (scope `vraudio`) — Number of mono channels.
- L58 _variable_ `inline constexpr size_t kNumStereoChannels = 2;` (scope `vraudio`) — Number of stereo channels.
- L61 _variable_ `inline constexpr size_t kNumSurroundFiveDotOneChannels = 6;` (scope `vraudio`) — Number of surround 5.1 channels.
- L64 _variable_ `inline constexpr size_t kNumSurroundSevenDotOneChannels = 8;` (scope `vraudio`) — Number of surround 7.1 channels.
- L67 _variable_ `inline constexpr size_t kNumFirstOrderAmbisonicChannels = 4;` (scope `vraudio`) — Number of first-order ambisonic channels.
- L70 _variable_ `inline constexpr size_t kNumSecondOrderAmbisonicChannels = 9;` (scope `vraudio`) — Number of second-order ambisonic channels.
- L73 _variable_ `inline constexpr size_t kNumThirdOrderAmbisonicChannels = 16;` (scope `vraudio`) — Number of third-order ambisonic channels.
- L76 _variable_ `inline constexpr size_t kNumFirstOrderAmbisonicWithNonDiegeticStereoChannels = 6;` (scope `vraudio`) — Number of first-order ambisonic with non-diegetic stereo channels.
- L79 _variable_ `inline constexpr size_t kNumSecondOrderAmbisonicWithNonDiegeticStereoChannels = 11;` (scope `vraudio`) — Number of second-order ambisonic with non-diegetic stereo channels.
- L82 _variable_ `inline constexpr size_t kNumThirdOrderAmbisonicWithNonDiegeticStereoChannels = 18;` (scope `vraudio`) — Number of third-order ambisonic with non-diegetic stereo channels.
- L85 _variable_ `inline constexpr float kNegative60dbInAmplitude = 0.001f;` (scope `vraudio`) — Negative 60dB in amplitude.
- L88 _variable_ `inline constexpr double kEpsilonDouble = 1e-6;` (scope `vraudio`) — Tolerated error margins for floating points.
- L89 _variable_ `inline constexpr float kEpsilonFloat = 1e-6f;` (scope `vraudio`)
- L92 _variable_ `inline const float kInverseSqrtTwo = 1.0f / std::sqrt(2.0f);` (scope `vraudio`) — Inverse square root of two (equivalent to -3dB audio signal attenuation).
- L95 _variable_ `inline const float kSqrtTwo = std::sqrt(2.0f);` (scope `vraudio`) — Square roots.
- L96 _variable_ `inline const float kSqrtThree = std::sqrt(3.0f);` (scope `vraudio`)
- L99 _variable_ `inline constexpr float kPi = static_cast<float>(M_PI);` (scope `vraudio`) — Pi in radians.
- L101 _variable_ `inline constexpr float kHalfPi = static_cast<float>(M_PI / 2.0);` (scope `vraudio`) — Half pi in radians.
- L103 _variable_ `inline constexpr float kTwoPi = static_cast<float>(2.0 * M_PI);` (scope `vraudio`) — Two pi in radians.
- L106 _variable_ `inline constexpr float kRadiansFromDegrees = static_cast<float>(M_PI / 180.0);` (scope `vraudio`) — Defines conversion factor from degrees to radians.
- L109 _variable_ `inline constexpr float kDegreesFromRadians = static_cast<float>(180.0 / M_PI);` (scope `vraudio`) — Defines conversion factor from radians to degrees.
- L112 _variable_ `inline const float kNegativeLog1000 = -std::log(1000.0f);` (scope `vraudio`) — The negated natural logarithm of 1000.
- L115 _variable_ `inline constexpr float kLowestOctaveBandHz = 31.25f;` (scope `vraudio`) — The lowest octave band for computing room effects.
- L118 _variable_ `inline constexpr size_t kNumReverbOctaveBands = 9;` (scope `vraudio`) — Number of octave bands in which room effects are computed.
- L134 _variable_ `const float kOctaveBandCentres[kNumReverbOctaveBands] = { 31.25f, 62.5f, 125.0f, 250.0f, 500.0f, 1000.0f, 2000.0f, 4000.0f, 8000.0f};` (scope `vraudio`)
- L138 _variable_ `inline constexpr size_t kNumRoomSurfaces = 6;` (scope `vraudio`) — Number of surfaces in a shoe-box room.
- L142 _variable_ `inline constexpr float kSpeedOfSound = 343.0f;` (scope `vraudio`) — Speed of sound in air at 20 degrees Celsius in meters per second. http://www.sengpielaudio.com/calculator-speedsound.htm
- L145 _variable_ `inline constexpr float kStereoLeftDegrees = 90.0f;` (scope `vraudio`) — Locations of the stereo virtual loudspeakers in degrees.
- L146 _variable_ `inline constexpr float kStereoRightDegrees = -90.0f;` (scope `vraudio`)
- L149 _variable_ `inline constexpr float kMillisecondsFromSeconds = 1000.0f;` (scope `vraudio`) — Conversion factor from seconds to milliseconds.
- L152 _variable_ `inline constexpr float kSecondsFromMilliseconds = 0.001f;` (scope `vraudio`) — Conversion factor from milliseconds to seconds.
- L155 _variable_ `inline constexpr double kMicrosecondsFromSeconds = 1e6;` (scope `vraudio`) — Conversion factor from seconds to milliseconds.
- L158 _variable_ `inline constexpr double kSecondsFromMicroseconds = 1e-6;` (scope `vraudio`) — Conversion factor from milliseconds to seconds.
- L161 _variable_ `inline constexpr float kNearFieldThreshold = 1.0f;` (scope `vraudio`) — The distance threshold where the near field effect should fade in.
- L165 _variable_ `inline constexpr float kMinNearFieldDistance = 0.1f;` (scope `vraudio`) — Minimum allowed distance of a near field sound source used to cap the allowed energy boost.
- L168 _variable_ `inline constexpr float kMaxNearFieldEffectGain = 9.0f;` (scope `vraudio`) — Maximum gain applied by Near Field Effect to the mono source signal.
- L173 _variable_ `inline constexpr size_t kUnitRampLength = 2048;` (scope `vraudio`)
- L177 _variable_ `inline constexpr float kRotationQuantizationRad = 1.0f * kRadiansFromDegrees;` (scope `vraudio`)

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/base/integral_types.h` (Private)


#### Free symbols / members of external scopes

- L34 _macro_ `#define BASE_INTEGRAL_TYPES_H_`
- L37 _typedef_ `typedef signed char schar;` — Standard typedefs
- L38 _typedef_ `typedef signed char int8;`
- L39 _typedef_ `typedef short int16;`
- L40 _typedef_ `typedef int int32;`
- L42 _typedef_ `typedef __int64 int64;`
- L44 _typedef_ `typedef long long int64;`
- L53 _typedef_ `typedef unsigned char uint8;`
- L54 _typedef_ `typedef unsigned short uint16;`
- L55 _typedef_ `typedef unsigned int uint32;`
- L57 _typedef_ `typedef unsigned __int64 uint64;`
- L59 _typedef_ `typedef unsigned long long uint64;`
- L66 _typedef_ `typedef signed int char32;` — A type to represent a Unicode code-point value. As of Unicode 4.0, such values require up to 21 bits. (For type-checking on pointers, make this explicitly signed, and it should always be the signed version of whatever int32 is.)
- L75 _typedef_ `typedef unsigned long uword_t;` — A type to represent a natural machine word (for e.g. efficiently scanning through memory for checksums or index searching). Don't use this for storing normal integers. Ideally this would be just unsigned int, but our 64-bit architectures use the LP64 model (http://en.wikipedia.org/wiki/64-bit_computing#64-bit_data_models), hence their ints are only 32 bits. We want to use the same fundamental type on all archs if possible to preserve *printf() compatability.
- L86 _macro_ `#define GG_LONGLONG(x) x##I64` — VC++ long long suffixes
- L87 _macro_ `#define GG_ULONGLONG(x) x##UI64`
- L90 _macro_ `#define GG_LL_FORMAT "I64" // As in printf("%I64d", ...)` — Length modifier in printf format string for int64's (e.g. within %d)
- L91 _macro_ `#define GG_LL_FORMAT_W L"I64"`
- L95 _macro_ `#define GG_LONGLONG(x) x##LL`
- L96 _macro_ `#define GG_ULONGLONG(x) x##ULL`
- L97 _macro_ `#define GG_LL_FORMAT "ll" // As in "%lld". Note that "q" is poor form also.`
- L98 _macro_ `#define GG_LL_FORMAT_W L"ll"`
- L103 _variable_ `static const uint8 kuint8max = (( uint8) 0xFF);`
- L104 _variable_ `static const uint16 kuint16max = ((uint16) 0xFFFF);`
- L105 _variable_ `static const uint32 kuint32max = ((uint32) 0xFFFFFFFF);`
- L106 _variable_ `static const uint64 kuint64max = ((uint64) GG_LONGLONG(0xFFFFFFFFFFFFFFFF));`
- L107 _variable_ `static const int8 kint8min = (( int8) ~0x7F);`
- L108 _variable_ `static const int8 kint8max = (( int8) 0x7F);`
- L109 _variable_ `static const int16 kint16min = (( int16) ~0x7FFF);`
- L110 _variable_ `static const int16 kint16max = (( int16) 0x7FFF);`
- L111 _variable_ `static const int32 kint32min = (( int32) ~0x7FFFFFFF);`
- L112 _variable_ `static const int32 kint32max = (( int32) 0x7FFFFFFF);`
- L113 _variable_ `static const int64 kint64min = (( int64) GG_LONGLONG(~0x7FFFFFFFFFFFFFFF));`
- L114 _variable_ `static const int64 kint64max = (( int64) GG_LONGLONG(0x7FFFFFFFFFFFFFFF));`
- L117 _typedef_ `typedef uint64 Fprint;`
- L118 _variable_ `static const Fprint kIllegalFprint = 0;`
- L119 _variable_ `static const Fprint kMaxFprint = GG_ULONGLONG(0xFFFFFFFFFFFFFFFF);`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/base/logging.h` (Private)


#### class `NullLogger`  
`class NullLogger`  
_L45-51_
- desc: This class is used to disable logging, while still allowing for log messages to contain '<<' expressions.
- L47 _public function_ `std::ostream& GetStream()`

#### class `FatalLogger`  
`class FatalLogger`  
_L83-99_
- desc: This class is used to log to std::cerr.
- L85 _public function_ `FatalLogger(const char* file, int line)`
- L88 _public function_ `~FatalLogger()`
- L95 _public function_ `std::ostream& GetStream()`
- L98 _private member_ `std::ostringstream error_string_;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_PLATFORM_LOGGING_H_`
- L57 _macro_ `#define DISABLE_CHECKS 1`
- L58 _macro_ `#define INCLUDE_UNUSED_CODE 0`
- L61 _macro_ `#define DCHECK(expr)`
- L71 _macro_ `#define DCHECK_OP(val1, val2, op) DCHECK((val1)op(val2))`
- L73 _macro_ `#define DCHECK_EQ(val1, val2) DCHECK_OP((val1), (val2), ==)`
- L74 _macro_ `#define DCHECK_NE(val1, val2) DCHECK_OP((val1), (val2), !=)`
- L75 _macro_ `#define DCHECK_LE(val1, val2) DCHECK_OP((val1), (val2), <=)`
- L76 _macro_ `#define DCHECK_LT(val1, val2) DCHECK_OP((val1), (val2), <)`
- L77 _macro_ `#define DCHECK_GE(val1, val2) DCHECK_OP((val1), (val2), >=)`
- L78 _macro_ `#define DCHECK_GT(val1, val2) DCHECK_OP((val1), (val2), >)`
- L80 _macro_ `#define ABORT_ON_FATAL_LOG 0`
- L101 _macro_ `#define CHECK(condition) \`
- L105 _macro_ `#define CHECK_OP(val1, val2, op) CHECK((val1)op(val2))`
- L107 _macro_ `#define CHECK_EQ(val1, val2) CHECK_OP((val1), (val2), ==)`
- L108 _macro_ `#define CHECK_NE(val1, val2) CHECK_OP((val1), (val2), !=)`
- L109 _macro_ `#define CHECK_LE(val1, val2) CHECK_OP((val1), (val2), <=)`
- L110 _macro_ `#define CHECK_LT(val1, val2) CHECK_OP((val1), (val2), <)`
- L111 _macro_ `#define CHECK_GE(val1, val2) CHECK_OP((val1), (val2), >=)`
- L112 _macro_ `#define CHECK_GT(val1, val2) CHECK_OP((val1), (val2), >)`
- L116 _function_ `template <typename T> T CheckNotNull(T&& t)` — Helper for CHECK_NOTNULL(), using C++11 perfect forwarding.
- L120 _macro_ `#define CHECK_NOTNULL(val) CheckNotNull(val)`
- L122 _macro_ `#define LOG(severity) NullLogger().GetStream()`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/base/misc_math.h` (Private)


#### class `vraudio::WorldPosition`  
`class WorldPosition : public Eigen::Matrix<float, 3, 1, Eigen::DontAlign>`  
_L38-55_
- inherits: `Eigen::Matrix<float,3,1,Eigen::DontAlign>`
- L43 _public function_ `template <typename Arg1, typename... Args> WorldPosition(const Arg1& arg1, Args&&... args) : Matrix(arg1, std::forward<Args>(args)...)` — Inherits all constructors with 1-or-more arguments. Necessary because MSVC12 doesn't support inheriting constructors.
- L47 _public prototype_ `WorldPosition();` — Constructs a zero vector.
- L50 _public function_ `bool operator!=(const WorldPosition& other) const` — Returns True if other |WorldPosition| differs by at least |kEpsilonFloat|.

#### class `vraudio::WorldRotation`  
`class WorldRotation : public Eigen::Quaternion<float, Eigen::DontAlign>`  
_L57-73_
- inherits: `Eigen::Quaternion<float,Eigen::DontAlign>`
- L62 _public function_ `template <typename Arg1, typename... Args> WorldRotation(const Arg1& arg1, Args&&... args) : Quaternion(arg1, std::forward<Args>(args)...)` — Inherits all constructors with 1-or-more arguments. Necessary because MSVC12 doesn't support inheriting constructors.
- L66 _public prototype_ `WorldRotation();` — Constructs an identity rotation.
- L69 _public function_ `float AngularDifferenceRad(const WorldRotation& other) const` — Returns the shortest arc between two |WorldRotation|s in radians.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_BASE_MISC_MATH_H_`
- L21 _macro_ `#define _USE_MATH_DEFINES // Enable MSVC math constants (e.g., M_PI).`
- L36 _namespace_ `namespace vraudio`
- L75 _typedef_ `typedef Eigen::AngleAxis<float> AngleAxisf;` (scope `vraudio`)
- L77 _typedef_ `typedef WorldPosition AudioPosition;` (scope `vraudio`)
- L79 _typedef_ `typedef WorldRotation AudioRotation;` (scope `vraudio`)
- L91 _function_ `inline void ConvertAudioFromWorldPosition(const WorldPosition& world_position, AudioPosition* audio_position)` (scope `vraudio`) — Converts |world_position| into an equivalent audio space position. The world space follows the typical CG coordinate system convention: Positive x points right, positive y points up, negative z points forward. The audio space follows the ambiX coordinate system convention that is commonly accepted in literature [http://goo.gl/XdYNm9]: Positive x points forward, negative y points right, positive z points up. Positions in both world space and audio space are in meters. @param world_position 3D position in world space. @param audio_position Output 3D position in audio space.
- L109 _function_ `inline void ConvertWorldFromAudioPosition(const AudioPosition& audio_position, AudioPosition* world_position)` (scope `vraudio`) — Converts |audio_position| into an equivalent world space position. The world space follows the typical CG coordinate system convention: Positive x points right, positive y points up, negative z points forward. The audio space follows the ambiX coordinate system convention that is commonly accepted in literature [http://goo.gl/XdYNm9]: Positive x points forward, negative y points right, positive z points up. Positions in both world space and audio space are in meters. @param audio_position 3D position in audio space. @param world_position Output 3D position in world space.
- L127 _function_ `inline void ConvertAudioFromWorldRotation(const WorldRotation& world_rotation, AudioRotation* audio_rotation)` (scope `vraudio`) — Converts |world_rotation| into an equivalent audio space rotation. The world space follows the typical CG coordinate system convention: Positive x points right, positive y points up, negative z points forward. The audio space follows the ambiX coordinate system convention that is commonly accepted in literature [http://goo.gl/XdYNm9]: Positive x points forward, negative y points right, positive z points up. Positions in both world space and audio space are in meters. @param world_rotation 3D rotation in world space. @param audio_rotation Output 3D rotation in audio space.
- L143 _function_ `inline void GetRelativeDirection(const WorldPosition& from_position, const WorldRotation& from_rotation, const WorldPosition& to_position, WorldPosition* relative_direction)` (scope `vraudio`) — Returns the relative direction vector |from_position| and |to_position| by rotating the relative position vector with respect to |from_rotation|. @param from_position Origin position of the direction. @param from_rotation Origin orientation of the direction. @param to_position Target position of the direction. @param relative_direction Relative direction vector (not normalized).
- L158 _function_ `inline void GetClosestPositionInAabb(const WorldPosition& relative_position, const WorldPosition& aabb_dimensions, WorldPosition* closest_position)` (scope `vraudio`) — Returns the closest relative position in an axis-aligned bounding box to the given |relative_position|. @param position Input position relative to the center of the bounding box. @param aabb_dimensions Bounding box dimensions. @return aabb bounded position.
- L177 _function_ `inline bool IsPositionInAabb(const WorldPosition& position, const WorldPosition& aabb_center, const WorldPosition& aabb_dimensions)` (scope `vraudio`) — Returns true if given world |position| is in given axis-aligned bounding box. @param position Position to be tested. @param aabb_center Bounding box center. @param aabb_dimensions Bounding box dimensions. @return True if |position| is within bounding box, false otherwise.
- L193 _function_ `template <typename T> inline bool DoesIntegerMultiplicationOverflow(T a, T b, T x)` (scope `vraudio`) — Returns true if an integer overflow occurred during the calculation of x = a * b. @param a First multiplicand. @param b Second multiplicand. @param x Product. @return True if integer overflow occurred, false otherwise.
- L206 _function_ `template <typename T> inline bool DoesIntegerAdditionOverflow(T a, T b)` (scope `vraudio`) — Returns true if an integer overflow occurred during the calculation of a + b. @param a First summand. @param b Second summand. @return True if integer overflow occurred, false otherwise.
- L216 _function_ `inline bool DoesIntSafelyConvertToSizeT(int i, size_t* x)` (scope `vraudio`) — Safely converts an int to a size_t. @param i Integer input. @param x Size_t output. @return True if integer overflow occurred, false otherwise.
- L229 _function_ `inline bool DoesSizeTSafelyConvertToInt(size_t i, int* x)` (scope `vraudio`) — Safely converts a size_t to an int. @param i Size_t input. @param x Integer output. @return True if integer overflow occurred, false otherwise.
- L243 _function_ `inline int FindGcd(int a, int b)` (scope `vraudio`) — Finds the greatest common divisor between two integer values using the Euclidean algorithm. Always returns a positive integer. @param a First of the two integer values. @param b second of the two integer values. @return The greatest common divisor of the two integer values.
- L260 _function_ `inline size_t NextPowTwo(size_t input)` (scope `vraudio`) — Finds the next power of two from an integer. This method works with values representable by unsigned 32 bit integers. @param input Integer value. @return The next power of two from |input|.
- L275 _function_ `inline float Factorial(int x)` (scope `vraudio`) — Returns the factorial (!) of x. If x < 0, it returns 0.
- L286 _function_ `inline float DoubleFactorial(int x)` (scope `vraudio`) — Returns the double factorial (!!) of x. For odd x:  1 * 3 * 5 * ... * (x - 2) * x For even x: 2 * 4 * 6 * ... * (x - 2) * x If x < 0, it returns 0.
- L300 _function_ `template <typename Iterator> inline bool EqualSafe(const Iterator& lhs_begin, const Iterator& lhs_end, const Iterator& rhs_begin, const Iterator& rhs_end)` (scope `vraudio`) — This is a *safe* alternative to std::equal function as a workaround in order to avoid MSVC compiler warning C4996 for unchecked iterators (see https://msdn.microsoft.com/en-us/library/aa985965.aspx). Also note that, an STL equivalent of this function was introduced in C++14 to be replaced with this implementation (see version (5) in http://en.cppreference.com/w/cpp/algorithm/equal).
- L318 _function_ `inline float FastReciprocalSqrt(float input)` (scope `vraudio`) — Fast reciprocal of square-root. See: https://goo.gl/fqvstz for details. @param input The number to be inverse rooted. @return An approximation of the reciprocal square root of |input|.
- L345 _prototype_ `bool LinearLeastSquareFitting(const std::vector<float>& x_array, const std::vector<float>& y_array, float* slope, float* intercept, float* r_squared);` (scope `vraudio`) — Finds the best-fitting line to a given set of 2D points by minimizing the sum of the squares of the vertical (along y-axis) offsets. The slope and intercept of the fitted line are recorded, as well as the coefficient of determination, which gives the quality of the fitting. See http://mathworld.wolfram.com/LeastSquaresFitting.html for how to compute these values. @param x_array Array of the x coordinates of the points. @param y_array Array of the y coordinates of the points. @param slope Output slope of the fitted line. @param intercept Output slope of the fitted line. @param r_squared Coefficient of determination. @return False if the fitting fails.
- L367 _function_ `template <typename T> static inline T IntegerPow(T base, int exp)` (scope `vraudio`) — This method is reproduced here so vraudio classes don't need to depend on //util/math/mathutil.h @tparam base Input to the exponent function. Any type for which *= is defined. @param exp Integer exponent, must be greater than or equal to zero. @return |base|^|exp|.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/base/object_transform.h` (Private)


#### struct `vraudio::ObjectTransform`  
`struct ObjectTransform`  
_L24-27_
- L25 _public member_ `WorldPosition position;`
- L26 _public member_ `WorldRotation rotation;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_BASE_OBJECT_TRANSFORM_H_`
- L22 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/base/simd_macros.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_BASE_SIMD_MACROS_H_`
- L24 _typedef_ `typedef __m128 SimdVector;`
- L25 _macro_ `#define SIMD_SSE`
- L26 _macro_ `#define SIMD_LENGTH 4`
- L27 _macro_ `#define SIMD_MULTIPLY(a, b) _mm_mul_ps(a, b)`
- L28 _macro_ `#define SIMD_ADD(a, b) _mm_add_ps(a, b)`
- L29 _macro_ `#define SIMD_SUB(a, b) _mm_sub_ps(a, b)`
- L30 _macro_ `#define SIMD_MULTIPLY_ADD(a, b, c) _mm_add_ps(_mm_mul_ps(a, b), c)`
- L31 _macro_ `#define SIMD_SQRT(a) _mm_rcp_ps(_mm_rsqrt_ps(a))`
- L32 _macro_ `#define SIMD_RECIPROCAL_SQRT(a) _mm_rsqrt_ps(a)`
- L33 _macro_ `#define SIMD_LOAD_ONE_FLOAT(p) _mm_set1_ps(p)`
- L38 _typedef_ `typedef float32x4_t SimdVector;`
- L39 _macro_ `#define SIMD_NEON`
- L41 _macro_ `#define SIMD_MULTIPLY(a, b) vmulq_f32(a, b)`
- L42 _macro_ `#define SIMD_ADD(a, b) vaddq_f32(a, b)`
- L43 _macro_ `#define SIMD_SUB(a, b) vsubq_f32(a, b)`
- L44 _macro_ `#define SIMD_MULTIPLY_ADD(a, b, c) vmlaq_f32(c, a, b)`
- L45 _macro_ `#define SIMD_SQRT(a) vrecpeq_f32(vrsqrteq_f32(a))`
- L46 _macro_ `#define SIMD_RECIPROCAL_SQRT(a) vrsqrteq_f32(a)`
- L47 _macro_ `#define SIMD_LOAD_ONE_FLOAT(p) vld1q_dup_f32(&(p))`
- L51 _typedef_ `typedef float SimdVector;`
- L52 _macro_ `#define SIMD_DISABLED`
- L53 _macro_ `#define SIMD_LENGTH 1`
- L54 _macro_ `#define SIMD_MULTIPLY(a, b) ((a) * (b))`
- L55 _macro_ `#define SIMD_ADD(a, b) ((a) + (b))`
- L56 _macro_ `#define SIMD_SUB(a, b) ((a) - (b))`
- L57 _macro_ `#define SIMD_MULTIPLY_ADD(a, b, c) ((a) * (b) + (c))`
- L58 _macro_ `#define SIMD_SQRT(a) (1.0f / FastReciprocalSqrt(a))`
- L59 _macro_ `#define SIMD_RECIPROCAL_SQRT(a) FastReciprocalSqrt(a)`
- L60 _macro_ `#define SIMD_LOAD_ONE_FLOAT(p) (p)`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/base/simd_utils.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_BASE_SIMD_UTILS_H_`
- L23 _namespace_ `namespace vraudio`
- L29 _prototype_ `bool IsAligned(const float* pointer);` (scope `vraudio`) — Checks if the pointer provided is correctly aligned for SIMD. @param pointer Pointer to check. @return True if the pointer is correctly aligned.
- L30 _prototype_ `bool IsAligned(const int16_t* pointer);` (scope `vraudio`)
- L40 _prototype_ `size_t FindNextAlignedArrayIndex(size_t length, size_t type_size_bytes, size_t memory_alignment_bytes);` (scope `vraudio`) — Rounds a number of frames up to the next aligned memory address based on |memory_alignment_bytes|. This allows for aligning offset pointers into a single chunk of allocated memory. @param length Number of samples before the desired offset pointer. @param type_size_bytes Size of the type of each entry in the array. @param memory_alignment_bytes Number of bytes to which an address is aligned. @return Number of samples into the memory chunk to ensure aligned memory.
- L50 _prototype_ `void AddPointwise(size_t length, const float* input_a, const float* input_b, float* output);` (scope `vraudio`) — Adds a float array |input_a| to another float array |input_b| and stores the result in |output|. @param length Number of floats. @param input_a Pointer to the first float in input_a array. @param input_b Pointer to the first float in input_b array. @param output Pointer to the first float in output array.
- L59 _prototype_ `void SubtractPointwise(size_t length, const float* input_a, const float* input_b, float* output);` (scope `vraudio`) — Subtracts a float array |input|, pointwise from another float array |output|. @param length Number of floats. @param input Pointer to the first float in input_a array. @param output Pointer to the first float in input_b array. @param output Pointer to the first float in output array.
- L69 _prototype_ `void MultiplyPointwise(size_t length, const float* input_a, const float* input_b, float* output);` (scope `vraudio`) — Pointwise multiplies a float array |input_a| with another float array |input_b| and stores the result in |output|. @param length Number of floats. @param input Pointer to the first float in input_a array. @param input Pointer to the first float in input_b array. @param output Pointer to the first float in output array.
- L79 _prototype_ `void MultiplyAndAccumulatePointwise(size_t length, const float* input_a, const float* input_b, float* accumulator);` (scope `vraudio`) — Pointwise multiplies a float array |input_a| with another float array |input_b| and adds the result onto |accumulator|. @param length Number of floats. @param input_a Pointer to the first float in input_a array. @param input_b Pointer to the first float in input_b array. @param accumulator Pointer to the first float in accumulator array.
- L88 _prototype_ `void ScalarMultiply(size_t length, float gain, const float* input, float* output);` (scope `vraudio`) — Multiplies a float array |input| by a scalar |gain| over |length| samples. @param length Number of floats. @param gain Scalar value with which to multiply the input. @param input Pointer to the first float in input array. @param output Pointer to the first float in output array.
- L98 _prototype_ `void ScalarMultiplyAndAccumulate(size_t length, float gain, const float* input, float* accumulator);` (scope `vraudio`) — Multiplies a float array |input| by a scalar |gain| over |length| samples and adds the result onto |accumulator|. @param length Number of floats. @param gain Scalar value with which to multiply the input. @param input Pointer to the first float in input array. @param output Pointer to the first float in accumulator array.
- L106 _prototype_ `void ReciprocalSqrt(size_t length, const float* input, float* output);` (scope `vraudio`) — Calculates an approximmate reciprocal square root. @param length Number of floats. @param input Pointer to the first float in input array. @param output Pointer to the first float in output array.
- L113 _prototype_ `void Sqrt(size_t length, const float* input, float* output);` (scope `vraudio`) — Calculates an approximate square root. @param length Number of floats. @param input Pointer to the first float in input array. @param output Pointer to the first float in output array.
- L121 _prototype_ `void ApproxComplexMagnitude(size_t length, const float* input, float* output);` (scope `vraudio`) — Calculates the approximate magnitudes of interleaved complex numbers. @param length Number of complex numbers in the input array, (i.e. half its length). @param input Pointer to the first float in input array. Length: 2 * |length|. @param output Pointer to the first float in output array, Length: |length|.
- L135 _prototype_ `void ComplexInterleavedFormatFromMagnitudeAndSinCosPhase( size_t length, const float* magnitude, const float* cos_phase, const float* sin_phase, float* complex_interleaved_format_output);` (scope `vraudio`) — Calculates the complex values in interleaved format (real, imaginary), from a vector of magnitudes and of sines and cosines of phase. @param length Number of total entries (real & imaginary) in the input array. @param magnitude Pointer to the first float in the magnitude array, Length: |length| /  2 @param cos_phase Pointer to the first float in the cosine phase array, Length: |length| /  2 @param sin_phase Pointer to the first float in the sine phase array, Length: |length| /  2 @param complex_interleaved_format_output Pointer to the first float in the output array. Length: |length|.
- L146 _prototype_ `void StereoFromMonoSimd(size_t length, const float* mono, float* left, float* right);` (scope `vraudio`) — Generates an identical left and right pair of stereo channels from a mono input channel, where each channel is the mono channel times 1/sqrt(2). @param length Number of floats. @param mono Pointer to the first float in an input mono array. @param left Pointer to the first float in the left output array. @param right Pointer to the first float in the right output array.
- L156 _prototype_ `void MonoFromStereoSimd(size_t length, const float* left, const float* right, float* mono);` (scope `vraudio`) — Generates a mono downmix from a pair of stereo channels, where the output is equal to the sum of the two inputs times 1/sqrt(2). @param length Number of floats. @param left Pointer to the first float in the left input array. @param right Pointer to the first float in the right input array. @param mono Pointer to the first float in an output mono array.
- L164 _prototype_ `void Int16FromFloat(size_t length, const float* input, int16_t* output);` (scope `vraudio`) — Converts an array of 32 bit float input to clamped 16 bit int output. @param length Number of floats in the input array and int16_ts in the output. @param input Float array. @param output Int array.
- L171 _prototype_ `void FloatFromInt16(size_t length, const int16_t* input, float* output);` (scope `vraudio`) — Converts an array of 16 bit int input to 32 bit float output. @param length Number of int16_ts in the input array and floats in the output. @param input Int array. @param output Float array.
- L180 _prototype_ `void InterleaveStereo(size_t length, const int16_t* channel_0, const int16_t* channel_1, int16_t* interleaved_buffer);` (scope `vraudio`) — Interleaves a pair of mono buffers of int_16 data into a stereo buffer. @param length Number of frames per mono channel. The interleaved buffer must be twice this size. @param channel_0 Input buffer of mono data for the first channel. @param channel_1 Input buffer of mono data for the second channel. @param interleaved_buffer Output buffer of stereo interleaved data.
- L190 _prototype_ `void InterleaveStereo(size_t length, const float* channel_0, const float* channel_1, float* interleaved_buffer);` (scope `vraudio`) — Interleaves a pair of mono buffers of float data into a stereo buffer. @param length Number of frames per mono channel. The interleaved buffer must be twice this size. @param channel_0 Input buffer of mono data for the first channel. @param channel_1 Input buffer of mono data for the second channel. @param interleaved_buffer Output buffer of stereo interleaved data.
- L201 _prototype_ `void InterleaveStereo(size_t length, const float* channel_0, const float* channel_1, int16_t* interleaved_buffer);` (scope `vraudio`) — Interleaves a pair of mono buffers of float data into a stereo buffer of int16_t data. @param length Number of frames per mono channel. The interleaved buffer must be twice this size. @param channel_0 Input buffer of mono data for the first channel (float). @param channel_1 Input buffer of mono data for the second channel (float). @param interleaved_buffer Output buffer of stereo interleaved data (int16_t).
- L211 _prototype_ `void DeinterleaveStereo(size_t length, const int16_t* interleaved_buffer, int16_t* channel_0, int16_t* channel_1);` (scope `vraudio`) — Deinterleaves a stereo buffer of int16_t data into a pair of mono buffers. @param length Number of frames per mono channel. The interleaved buffer must be twice this size. @param interleaved_buffer Input buffer of stereo interleaved data. @param channel_0 Output buffer of mono data for the first channel. @param channel_1 Output buffer of mono data for the second channel.
- L221 _prototype_ `void DeinterleaveStereo(size_t length, const float* interleaved_buffer, float* channel_0, float* channel_1);` (scope `vraudio`) — Deinterleaves a stereo buffer of float data into a pair of mono buffers. @param length Number of frames per mono channel. The interleaved buffer must be twice this size. @param interleaved_buffer Input buffer of stereo interleaved data. @param channel_0 Output buffer of mono data for the first channel. @param channel_1 Output buffer of mono data for the second channel.
- L232 _prototype_ `void DeinterleaveStereo(size_t length, const int16_t* interleaved_buffer, float* channel_0, float* channel_1);` (scope `vraudio`) — Deinterleaves a stereo buffer of int16_t data into a pair of mono float buffers, performing the int16 to floating point conversion. @param length Number of frames per mono channel. The interleaved buffer must be twice this size. @param interleaved_buffer Input buffer of stereo interleaved data (int16_t). @param channel_0 Output buffer of mono data for the first channel (float). @param channel_1 Output buffer of mono data for the second channel (float).
- L245 _prototype_ `void InterleaveQuad(size_t length, const int16_t* channel_0, const int16_t* channel_1, const int16_t* channel_2, const int16_t* channel_3, int16_t* workspace, int16_t* interleaved_buffer);` (scope `vraudio`) — Interleaves four mono buffers of int16_t data into a quad buffer. @param length Number of frames per mono channel. The interleaved buffer must be four times this size and the workspace must be five times this size. @param channel_0 Input buffer of mono data for the first channel. @param channel_1 Input buffer of mono data for the second channel. @param channel_2 Input buffer of mono data for the third channel. @param channel_3 Input buffer of mono data for the fourth channel. @param workspace Aligned buffer of 5 * |length| samples in length. @param interleaved_buffer Output buffer of quad interleaved data.
- L260 _prototype_ `void InterleaveQuad(size_t length, const float* channel_0, const float* channel_1, const float* channel_2, const float* channel_3, float* workspace, float* interleaved_buffer);` (scope `vraudio`) — Interleaves four mono buffers of float data into a quad buffer. @param length Number of frames per mono channel. The interleaved buffer must be four times this size and the workspace must be five times this size. @param channel_0 Input buffer of mono data for the first channel. @param channel_1 Input buffer of mono data for the second channel. @param channel_2 Input buffer of mono data for the third channel. @param channel_3 Input buffer of mono data for the fourth channel. @param workspace Aligned buffer of 5 * |length| samples in length. @param interleaved_buffer Output buffer of quad interleaved data.
- L275 _prototype_ `void DeinterleaveQuad(size_t length, const int16_t* interleaved_buffer, int16_t* workspace, int16_t* channel_0, int16_t* channel_1, int16_t* channel_2, int16_t* channel_3);` (scope `vraudio`) — Deinterleaves a quad buffer of int16_t data into four mono buffers. @param length Number of frames per mono channel. The interleaved buffer must be four times this size and the workspace must be five times this size. @param interleaved_buffer Input buffer of quad interleaved data. @param workspace Aligned buffer of 5 * |length| samples in length. @param channel_0 Output buffer of mono data for the first channel. @param channel_1 Output buffer of mono data for the second channel. @param channel_2 Output buffer of mono data for the third channel. @param channel_3 Output buffer of mono data for the fourth channel.
- L290 _prototype_ `void DeinterleaveQuad(size_t length, const float* interleaved_buffer, float* workspace, float* channel_0, float* channel_1, float* channel_2, float* channel_3);` (scope `vraudio`) — Deinterleaves a quad buffer of float data into four mono buffers. @param length Number of frames per mono channel. The interleaved buffer must be four times this size and the workspace must be five times this size. @param interleaved_buffer Input buffer of quad interleaved data. @param workspace Aligned buffer of 5 * |length| samples in length. @param channel_0 Output buffer of mono data for the first channel. @param channel_1 Output buffer of mono data for the second channel. @param channel_2 Output buffer of mono data for the third channel. @param channel_3 Output buffer of mono data for the fourth channel.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/base/source_parameters.h` (Private)


#### enum `vraudio::AttenuationType`  
`enum AttenuationType`  
_L28-34_
- desc: Gain attenuation types for audio sources.
- L29 _public enumerator_ `kInput = 0`
- L30 _public enumerator_ `kDirect`
- L31 _public enumerator_ `kReflections`
- L32 _public enumerator_ `kReverb`
- L33 _public enumerator_ `kNumAttenuationTypes`

#### struct `vraudio::SourceParameters`  
`struct SourceParameters`  
_L37-97_
- desc: Parameters describing an audio source.
- L39 _public member_ `ObjectTransform object_transform;` — Object transform associated with this buffer.
- L42 _public member_ `float spread_deg = 0.0f;` — Angular spread in degrees. Range [0, 360].
- L45 _public member_ `float gain = 1.0f;` — Source gain factor.
- L48 _public member_ `float attenuations[kNumAttenuationTypes];` — Source gain attenuation factors to be calculated per each buffer.
- L52 _public member_ `float distance_attenuation = 1.0f;` — Distance attenuation. Value 1 represents no attenuation should be applied, value 0 will fully attenuate the volume. Range [0, 1].
- L55 _public member_ `DistanceRolloffModel distance_rolloff_model = DistanceRolloffModel::kLogarithmic;` — Distance attenuation rolloff model to use.
- L59 _public member_ `float minimum_distance = 0.0f;` — Minimum distance at which to apply distance attenuation.
- L62 _public member_ `float maximum_distance = 500.0f;` — Maximum distance at which to apply distance attenuation.
- L68 _public member_ `float directivity_alpha = 0.0f;` — Alpha weighting of source's directivity pattern. This sets the balance between the dipole and omnidirectional directivity patterns which combine to produce the single directivity output value. Range [0, 1], where 0 is fully omnidirectional and 1 is fully dipole.
- L72 _public member_ `float directivity_order = 1.0f;` — Source directivity order. Increasing this value increases the directivity towards the front of the source. Range [1, inf).
- L78 _public member_ `float listener_directivity_alpha = 0.0f;` — Alpha weighting of listener's directivity pattern. This sets the balance between the dipole and omnidirectional pickup patterns which combine to produce the single output value. Range [0, 1], where 0 is fully omnidirectional and 1 is fully dipole.
- L82 _public member_ `float listener_directivity_order = 1.0f;` — Listener directivity order. Increasing this value increases the directivity towards the front of the listener. Range [1, inf).
- L87 _public member_ `float occlusion_intensity = 0.0f;` — Occlusion intensity. Value 0 represents no occlusion, values greater than 1 represent multiple occlusions. The intensity of each occlusion is scaled in range [0, 1].
- L90 _public member_ `float near_field_gain = 0.0f;` — Near field effect gain. Range [0, 9].
- L93 _public member_ `float room_effects_gain = 1.0f;` — Source gain factor for the room effects.
- L96 _public member_ `bool enable_hrtf = true;` — Whether the source uses binaural rendering or stereo panning.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_BASE_SOURCE_PARAMETERS_H_`
- L25 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/base/spherical_angle.h` (Private)


#### class `vraudio::SphericalAngle`  
`class SphericalAngle`  
_L25-83_
- desc: Represents angular position on a sphere in terms of azimuth and elevation.
- L28 _public prototype_ `SphericalAngle(float azimuth, float elevation);` — Constructs a spherical angle with the given azimuth and elevation.
- L31 _public prototype_ `SphericalAngle();` — Constructs a default spherical angle (azimuth = 0, elevation = 0).
- L34 _public prototype_ `SphericalAngle(const SphericalAngle& other);` — Constructs a spherical angle from a given one.
- L36 _public prototype_ `SphericalAngle& operator=(const SphericalAngle other);`
- L43 _public prototype_ `static SphericalAngle FromWorldPosition(const WorldPosition& world_position);` — Returns a spherical angle representation of given |world_position| (World Space). @param world_position 3D position in world space. @return Spherical angle that represents the |world_position|.
- L46 _public prototype_ `static SphericalAngle FromDegrees(float azimuth_degrees, float elevation_degrees);` — Returns a spherical angle from azimuth and elevation in degrees.
- L53 _public prototype_ `SphericalAngle FlipAzimuth() const;` — Returns another spherical angle with the same elevation but the azimuth sign flipped. @return Horizontally flipped version of the spherical angle.
- L63 _public prototype_ `WorldPosition GetWorldPositionOnUnitSphere() const;` — Returns the |WorldPosition| coordinates (World Space) on the unit sphere corresponding to this spherical angle. The transformation is defined as such: x = -cos(elevation) * sin(azimuth) y = sin(elevation) z = -cos(elevation) * cos(azimuth) @return 3D position in world space.
- L70 _public prototype_ `SphericalAngle Rotate(const WorldRotation& rotation) const;` — Returns the rotated version of the spherical angle using given |WorldRotation|. @param rotation Rotation to be applied to the spherical angle. @return Rotated version of the spherical angle.
- L72 _public function_ `void set_azimuth(float azimuth)`
- L73 _public function_ `void set_elevation(float elevation)`
- L75 _public function_ `float azimuth() const`
- L76 _public function_ `float elevation() const`
- L78 _public prototype_ `bool operator==(const SphericalAngle& other) const;`
- L81 _private member_ `float azimuth_;`
- L82 _private member_ `float elevation_;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_BASE_SPHERICAL_ANGLE_H_`
- L22 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/base/unique_ptr_wrapper.h` (Private)


#### struct `UniquePtrWrapper`  
`template <typename T> struct UniquePtrWrapper`  
_L25-31_
- desc: Wrapper around std::unique_ptr to enable the binding of unique_ptr buffers to std:function and/or lambda function.
- L26 _public function_ `UniquePtrWrapper(const UniquePtrWrapper& other) : ptr(std::move(other.ptr))`
- L27 _public function_ `UniquePtrWrapper(UniquePtrWrapper&& other) : ptr(std::move(other.ptr))`
- L28 _public function_ `explicit UniquePtrWrapper(std::unique_ptr<T> buffer) : ptr(std::move(buffer))`
- L30 _public member_ `mutable std::unique_ptr<T> ptr;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_BASE_UNIQUE_PTR_WRAPPER_H_`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/config/global_config.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_CONFIG_GLOBAL_CONFIG_H_`
- L22 _namespace_ `namespace vraudio`
- L24 _function_ `inline GraphManagerConfig GlobalConfig()` (scope `vraudio`)

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/config/source_config.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_CONFIG_SOURCE_CONFIG_H_`
- L22 _namespace_ `namespace vraudio`
- L24 _prototype_ `SourceGraphConfig StereoPanningConfig();` (scope `vraudio`)
- L25 _prototype_ `SourceGraphConfig BinauralLowQualityConfig();` (scope `vraudio`)
- L26 _prototype_ `SourceGraphConfig BinauralMediumQualityConfig();` (scope `vraudio`)
- L27 _prototype_ `SourceGraphConfig BinauralHighQualityConfig();` (scope `vraudio`)
- L28 _prototype_ `SourceGraphConfig RoomEffectsOnlyConfig();` (scope `vraudio`)

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/biquad_filter.h` (Private)


#### struct `vraudio::BiquadCoefficients`  
`struct BiquadCoefficients`  
_L31-46_
- desc: Set of transfer function coefficients.
- L34 _public function_ `BiquadCoefficients(float a0, float a1, float a2, float b0, float b1, float b2) : a({{a0, a1, a2}}), b({{b0, b1, b2}})` — Constructor takes as its arguments 6 floats representing the transfer function coefficients of a biquad filter.
- L40 _public function_ `BiquadCoefficients() : BiquadCoefficients(1.0, 0.0, 0.0, 1.0, 0.0, 0.0)` — Default constructor that sets a0 and b0 == 1 so that if the coefficients are used, the filter is stable and has no effect on input. i.e. input appears to just pass through.
- L43 _public member_ `std::array<float, 3> a;` — The denominator quadratic coefficients.
- L45 _public member_ `std::array<float, 3> b;` — The numerator quadratic coefficients.

#### class `vraudio::BiquadFilter`  
`class BiquadFilter`  
_L50-136_
- desc: Class representing a biquad filter as its transfer function coefficients. This class also performs filtering.
- L59 _public prototype_ `BiquadFilter(const BiquadCoefficients& coefficients, size_t frames_per_buffer);` — Constructs a BiquadFilter using a BiquadCoefficients struct. @param coefficients A BiquadCoefficients to set the internal |coefficients_|. @param frames_per_buffer The number of frames in each data buffer to be processed. This is used to set the number of samples to iterate over during a change of filter state.
- L66 _public prototype_ `void Filter(const AudioBuffer::Channel& input_channel, AudioBuffer::Channel* output_channel);` — Filter method for use with AudioBuffer::Channel. @param input_channel An AudioBuffer::Channel of input. @param output_channel A pointer to an AudioBuffer::Channel for output.
- L73 _public prototype_ `void SetCoefficients(const BiquadCoefficients& coefficients);` — Sets the fiter's coefficents to those passed, with all coefficients bar a0 scaled by 1/a0. @param coefficients A set of BiquadCoefficients.
- L79 _public prototype_ `void InterpolateToCoefficients(const BiquadCoefficients& coefficients);` — Sets the target coefficients to be interpolated. @param coefficents The BiquadCoefficients we wish to interpolate to over samples_to_iterate_over_ samples of the next input buffer.
- L82 _public prototype_ `void Clear();` — Clears the internal state of the filter, except for coefficients.
- L93 _private prototype_ `float FilterSample(float input, std::array<float, 2>* delay_line, const BiquadCoefficients& coefficients);` — Filters a single sample of input. @param input A single input sample from a Planar or Interleaved buffer. @param delay_line The delay_line to use (important for interpolation). @param coefficients The biquad coeffients for use in filtering. @return An output value to be placed in a Planar or Interleaved buffer.
- L100 _private prototype_ `void UpdateInterpolate();` — If InterpolateToState() has been called to assign new filter coefficients, this function will be called samples_to_iterate_over_ times within the next call of the Filter() function to slowly transition to the new coefficients which were passed to InterpolateToState() previously.
- L107 _private prototype_ `float InterpolateFilterSample(float input);` — Filters a single sample of input while transitioning between coefficients. Performs a linear crossfade over samples_to_iterate_over_ samples. @param input A single input sample from a Planar or Interleaved buffer. @return Output value to be placed in an audio buffer.
- L110 _private member_ `std::array<float, 2> biquad_delay_line_;` — Stores the memory state of the biquad
- L114 _private member_ `bool interpolate_flag_;` — Flag that denotes whether or not we are transitioning to another set of coefficients via interpolation.
- L118 _private member_ `size_t interpolate_counter_;` — Counter that denotes how far we are into transitioning to another set of coefficients via interpolation.
- L121 _private member_ `std::array<float, 2> old_delay_line_;` — Stores the memory state of the biquad.
- L124 _private member_ `size_t samples_to_iterate_over_;` — Number of samples over which to apply the filter coefficients.
- L127 _private member_ `float fade_scale_;` — Value used to crossfade between filter outputs.
- L131 _private member_ `BiquadCoefficients old_coefficients_;` — A set of coefficient which are updated as we interpolate between filter coefficients.
- L135 _private member_ `BiquadCoefficients coefficients_;` — Represents and maintains the state of the biquad filter in terms of its transfer function coefficients.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_BIQUAD_FILTER_H_`
- L28 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/channel_converter.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_CHANNEL_CONVERTER_H_`
- L22 _namespace_ `namespace vraudio`
- L29 _prototype_ `void ConvertStereoFromMono(const AudioBuffer& input, AudioBuffer* output);` (scope `vraudio`) — Converts a mono |input| buffer to a stereo |output| buffer by preserving the signal energy. @param input Mono input buffer. @param output Pointer to a stereo output buffer.
- L36 _prototype_ `void ConvertMonoFromStereo(const AudioBuffer& input, AudioBuffer* output);` (scope `vraudio`) — Converts a stereo |input| buffer to a mono |output| buffer by preserving the signal energy. @param input Stereo input buffer. @param output Pointer to a mono output buffer.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/circular_buffer.h` (Private)


#### class `vraudio::CircularBuffer`  
`class CircularBuffer`  
_L25-92_
- desc: Class that implements a simple mono circular buffer, accepting input and output of different length.
- L34 _public prototype_ `CircularBuffer(size_t buffer_length, size_t num_input_frames, size_t num_output_frames);` — Constructs a circular buffer. @param buffer_length The length of the Circular buffer. This value must be at least |num_input_frames| + |num_output_frames| so that we can always either add or remove data. @param num_input_frames Length of the input buffers in frames. @param num_output_frames Length of the output buffers in frames.
- L42 _public prototype_ `bool InsertBuffer(const AudioBuffer::Channel& input);` — Inserts a buffer of mono input into the |CircularBuffer| if space permits. @param input A channel of input data |num_input_frames| in length. @return True if there was space in the buffer and the input was successfully inserted, false otherwise.
- L52 _public prototype_ `bool RetrieveBuffer(AudioBuffer::Channel* output);` — Retrieves a buffer of output from the |CircularBuffer| if it contains sufficient data. @param output A channel to hold |num_output_frames| of output data. The channel may be greater in length than |num_output_frames|, in this case only the first |num_output_frames| will be overwritten. @return True if there was sufficient data in the buffer and the output was successfully retrieved.
- L64 _public prototype_ `bool RetrieveBufferWithOffset(size_t offset, AudioBuffer::Channel* output);` — Retrieves a buffer of output from the |CircularBuffer| to an offset location in an output channel, provided it contains sufficient data. @param offset Number of samples of offset into the |output| channel. @param output A channel to hold |num_output_frames| of output data. The channel may be greater in length than |num_output_frames| + |offset|, in this case only the first |num_output_frames| after |offset| will be overwritten. @return True if there was sufficient data in the buffer and the output was successfully retrieved.
- L69 _public function_ `size_t GetOccupancy() const` — Returns the number of samples of data currently in the |CircularBuffer|. @return The number of samples of data currently in the buffer.
- L72 _public prototype_ `void Clear();` — Resets the |CircularBuffer|.
- L76 _private member_ `const size_t num_input_frames_;` — Number of input frames to be inserted into the buffer.
- L79 _private member_ `const size_t num_output_frames_;` — Number of output frames to be retrieved from the buffer.
- L82 _private member_ `AudioBuffer buffer_;` — Mono audio buffer to hold the data.
- L85 _private member_ `size_t write_cursor_;` — Position at which we are writing into the buffer.
- L88 _private member_ `size_t read_cursor_;` — position at which we are reading from the buffer.
- L91 _private member_ `size_t num_valid_frames_;` — Number of frames of data currently stored within the buffer.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_CIRCULAR_BUFFER_H_`
- L22 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/delay_filter.h` (Private)


#### class `vraudio::DelayFilter`  
`class DelayFilter`  
_L32-81_
- desc: Single channel delay line class. Delays input buffer data by a non-negative integer number of samples. This implementation is not thread safe. The ClearBuffer() and InsertData() functions should not be called by a seperate thread during GetDelayedData().
- L39 _public prototype_ `DelayFilter(size_t max_delay_length, size_t frames_per_buffer);` — Constructs a DelayFilter. @param max_delay_length Maximum number of samples the input should be delayed by. @param frames_per_buffer Number of frames in each processed buffer.
- L45 _public prototype_ `void SetMaximumDelay(size_t max_delay_length);` — Sets the maximum delay length. It will allocate more space in the |delay_line_| if the new |max_delay_length| is more than doubled. @param max_delay_length New maximum delay in samples.
- L48 _public function_ `size_t GetDelayBufferLength() const` — Returns the current length of the |delay_line_|.
- L51 _public function_ `size_t GetMaximumDelayLength() const` — Returns the current maximum delay applicable to input buffers.
- L54 _public function_ `void ClearBuffer()` — Sets all of the |delay_line_| samples to zero.
- L59 _public prototype_ `void InsertData(const AudioBuffer::Channel& input);` — Copies an |AudioBuffer::Channel| of data to the delay line. @param input Input data.
- L67 _public prototype_ `void GetDelayedData(size_t delay_samples, AudioBuffer::Channel* buffer);` — Fills an |AudioBuffer::Channel| with data delayed by a specified amount less than or equal to the delay line's set |max_delay_length_|. @param delay_samples Requested delay to the data extraced from the delay line. Must be less than or equal to |max_delay_length_|. @param buffer Pointer to the output data, i.e., delayed input data.
- L71 _private member_ `size_t max_delay_length_;` — Maximum length of the delay to be applied (in samples).
- L74 _private member_ `size_t frames_per_buffer_;` — Number of frames in each AudioBuffer input/output.
- L77 _private member_ `std::unique_ptr<AudioBuffer> delay_line_;` — The delay line holding all of the delayed samples.
- L80 _private member_ `size_t write_cursor_;` — Position in the delay line to begin writing to.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_DELAY_FILTER_H_`
- L25 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/distance_attenuation.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_DISTANCE_ATTENUATION_H_`
- L23 _namespace_ `namespace vraudio`
- L37 _prototype_ `float ComputeLogarithmicDistanceAttenuation( const WorldPosition& listener_position, const WorldPosition& source_position, float min_distance, float max_distance);` (scope `vraudio`) — Returns the distance attenuation for |source_position| with respect to |listener_position|. The amplitude will decrease by approximately 6 dB every time the distance is doubled, i.e., the sound pressure "p" (amplitude) approximately falls inversely proportional to the distance "1/r". @param listener_position World position of the listener. @param source_position World position of the source. @param min_distance The minimum distance at which distance attenuation is applied. @param max_distance The maximum distance at which the direct sound has a gain of 0.0. @return Attenuation (gain) value in range [0.0f, 1.0f].
- L53 _prototype_ `float ComputeLinearDistanceAttenuation(const WorldPosition& listener_position, const WorldPosition& source_position, float min_distance, float max_distance);` (scope `vraudio`) — Returns the distance attenuation for |source_position| with respect to |listener_position|. The amplitude will decrease linearly between |min_distance| and |max_distance| from 1.0 to 0.0. @param listener_position World position of the listener. @param source_position World position of the source. @param min_distance The minimum distance at which distance attenuation is applied. @param max_distance The maximum distance at which the direct sound has a gain of 0.0. @return Attenuation (gain) value in range [0.0f, 1.0f].
- L65 _prototype_ `float ComputeNearFieldEffectGain(const WorldPosition& listener_position, const WorldPosition& source_position);` (scope `vraudio`) — Calculates the gain to be applied to the near field compensating stereo mix. This function will return 0.0f for all sources further away than one meter and will return a value between 0.0 and 9.0 for sources as they approach the listener's head location. @param listener_position World position of the listener. @param source_position World position of the source. @return Gain value in range [0.0f, 9.0f].
- L75 _prototype_ `void UpdateAttenuationParameters(float master_gain, float reflections_gain, float reverb_gain, const WorldPosition& listener_position, SourceParameters* parameters);` (scope `vraudio`) — Calculates and updates gain attenuations of the given source |parameters|. @param master_gain Global gain adjustment in amplitude. @param reflections_gain Reflections gain in amplitude. @param reverb_gain Reverb gain in amplitude. @param listener_position World position of the listener. @param parameters Source parameters to apply the gain attenuations into.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/fft_manager.h` (Private)


#### class `vraudio::FftManager`  
`class FftManager`  
_L28-178_
- desc: This class wraps the pffft library and enables reall FFT transformations to be performed on aligned float buffers of data. The class also manages all necessary data buffers and zero padding. This class is not thread safe.
- L31 _public member_ `static const size_t kMinFftSize;` — Minimum required FFT size.
- L37 _public prototype_ `explicit FftManager(size_t frames_per_buffer);` — Constructs a FftManager insatnce. One instance of this class can be shared. This class is not thread safe. @param frames_per_buffer System's number of frames per buffer.
- L40 _public prototype_ `~FftManager();` — Destroys a FftManager instance freeing associated aligned memory.
- L48 _public prototype_ `void FreqFromTimeDomain(const AudioBuffer::Channel& time_channel, AudioBuffer::Channel* freq_channel);` — Transforms a single channel of time domain input data into a frequency domain representation. @param time_channel Time domain input. If the length is less than |fft_size_|, the input is zeropadded. The max length is |fft_size_|. @param freq_channel Frequency domain output, |fft_size| samples long.
- L61 _public prototype_ `void TimeFromFreqDomain(const AudioBuffer::Channel& freq_channel, AudioBuffer::Channel* time_channel);` — Transforms a single channel of frequency domain input data into a time domain representation. Note: The input must be in pffft format see: goo.gl/LYbgX7. This method can output to a buffer of either |frames_per_buffer_| or |fft_size_| in length. This feature ensures an additional copy is not needed where this method is to be used with an overlap add. @param freq_channel Frequency domain input, |fft_size| samples long. @param time_channel Time domain output, |frames_per_buffer_| samples long OR |fft_size_| samples long.
- L69 _public prototype_ `void ApplyReverseFftScaling(AudioBuffer::Channel* time_channel);` — Applies a 1/|fft_size_| scaling to time domain output. NOTE this need not be applied where a convolution is taking place as the scaling will be included therein. @param time_channel Time domain data to be scaled.
- L80 _public prototype_ `void GetCanonicalFormatFreqBuffer(const AudioBuffer::Channel& input, AudioBuffer::Channel* output);` — Transforms a pffft frequency domain format buffer into canonical format with alternating real and imaginary values with increasing frequency. The first two entries of |output| are the real part of the DC and Nyquist frequencies (imaginary part is zero). The alternating real and imaginary parts start from the third entry in |output|. For more info on the pffft format see: goo.gl/LYbgX7 @param input Frequency domain input channel, |fft_size| samples long. @param output Frequency domain output channel,|fft_size| samples long.
- L88 _public prototype_ `void GetPffftFormatFreqBuffer(const AudioBuffer::Channel& input, AudioBuffer::Channel* output);` — Transforms a canonical frequency domain format buffer into pffft format. For more info on the pffft format see: goo.gl/LYbgX7 @param input Frequency domain input channel, |fft_size| samples long. @param output Frequency domain output channel, |fft_size| samples long.
- L99 _public prototype_ `void MagnitudeFromCanonicalFreqBuffer( const AudioBuffer::Channel& freq_channel, AudioBuffer::Channel* magnitude_channel);` — Genarates a buffer containing the single sided magnitude spectrum of a frequency domain buffer. The input must be in Canonical format. The output will have DC frequency as it's first entry and the Nyquist as it's last. @param freq_channel Canonical format frequency domain buffer, |fft_size_| samples long. @param magnitude_channel Magnitude of the |freq_channel|. |frames_per_buffer_| + 1 samples long.
- L113 _public prototype_ `void CanonicalFreqBufferFromMagnitudeAndPhase( const AudioBuffer::Channel& magnitude_channel, const AudioBuffer::Channel& phase_channel, AudioBuffer::Channel* canonical_freq_channel);` — Combines single sided magnitude and phase spectra into a canonical format frequency domain buffer. The inputs must have DC frequency as their first entry and the Nyquist as their last. @param magnitude_channel Magnitude of the |frequency_buffer|. |frames_per_buffer_| + 1 samples long. @param phase_channel Phase of the |frequency_buffer|. |frames_per_buffer_| + 1 samples long. @param canonical_freq_channel Canonical format frequency domain buffer, |fft_size_| samples long.
- L133 _public prototype_ `void CanonicalFreqBufferFromMagnitudeAndSinCosPhase( size_t phase_offset, const AudioBuffer::Channel& magnitude_channel, const AudioBuffer::Channel& sin_phase_channel, const AudioBuffer::Channel& cos_phase_channel, AudioBuffer::Channel* canonical_freq_channel);` — Combines single sided magnitude spectrum and the cosine and sine of a phase spectrum into a canonical format frequency domain buffer. The inputs must have DC frequency as their first entry and the Nyquist as their last. The phase spectra channels can be offset by |phase_offset|. This feature is specifically for use as an optimization in the |SpectralReverb|. @param phase_offset An offset into the channels of the phase buffer. @param magnitude_channel Magnitude of the |frequency_buffer|. |frames_per_buffer_| + 1 samples long. @param sin_phase_channel Sine of the phase of the |frequency_buffer|. |frames_per_buffer_| + 1 samples long. @param cos_phase_channel Cosine of the phase of the |frequency_buffer|. |frames_per_buffer_| + 1 samples long. @param canonical_freq_channel Canonical format frequency domain buffer, |fft_size_| samples long.
- L147 _public prototype_ `void FreqDomainConvolution(const AudioBuffer::Channel& input_a, const AudioBuffer::Channel& input_b, AudioBuffer::Channel* scaled_output);` — Performs a pointwise complex multiplication of two frequency domain buffers and applies tha inverse scaling factor of 1/|fft_size_|. This operation is equivalent to a time domain circular convolution. @param input_a Frequency domain input channel, |fft_size| samples long. @param input_b Frequency domain input channel, |fft_size| samples long. @param scaled_output Frequency domain output channel, |fft_size| samples long.
- L152 _public function_ `size_t GetFftSize() const` — Returns the number of points in the FFT.
- L156 _private member_ `const size_t fft_size_;` — FFT size in samples.
- L159 _private member_ `const size_t frames_per_buffer_;` — Number of frames in each buffer of input data.
- L163 _private member_ `const float inverse_fft_scale_;` — Inverse scale to be applied to buffers transformed from frequency to time domain.
- L166 _private member_ `AudioBuffer temp_zeropad_buffer_;` — Temporary time domain buffer to store zeropadded input.
- L169 _private member_ `AudioBuffer temp_freq_buffer_;` — Temporary freq domain buffer to store.
- L172 _private member_ `PFFFT_Setup* fft_;` — pffft states.
- L177 _private member_ `float* pffft_workspace_ = nullptr;` — Workspace for pffft. This pointer should be set to null for |fft_size_| less than 2^14. In which case the stack is used. This is the recommendation by the author of the pffft library.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_FFT_MANAGER_H_`
- L23 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/filter_coefficient_generators.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_FILTER_COEFFICIENT_GENERATORS_H_`
- L28 _namespace_ `namespace vraudio`
- L53 _prototype_ `BiquadCoefficients ComputeBandPassBiquadCoefficients(int sample_rate, float centre_frequency, int bandwidth);` (scope `vraudio`) — Computes corresponding biquad coefficients for band pass filter with respect to the centre frequency and the bandwidth between -3 dB frequencies. b0 + b1*z^-1 + b2*z^-2 H(z) = ------------------------ a0 + a1*z^-1 + a2*z^-2 where: w0 = 2*pi*center_frequency/sample_rate alpha = sin(w0)*sinh( ln(2)/2 * bandwidth * w0/sin(w0) ) b0 =   alpha b1 =   0 b2 =  -alpha a0 =   1 + alpha a1 =  -2*cos(w0) a2 =   1 - alpha @param sample_rate Sampling rate in Hz. @param centre_frequency Centre frequency of passband. @param bandwidth Bandwidth in octaves between -3 dB frequencies. @return Output structure of band-pass BiquadCoefficients.
- L103 _prototype_ `void ComputeDualBandBiquadCoefficients( int sample_rate, float crossover_frequency, BiquadCoefficients* low_pass_coefficients, BiquadCoefficients* high_pass_coefficients);` (scope `vraudio`) — Computes two sets of transfer function coefficients to be used with a pair of generic bi-quad filters. The coefficients are used to implement a phase-matched low-pass |low_pass_state| and high-pass |high_pass_state| filter pair with a cross-over frequency defined as |crossover_frequency|. Implementation of the matched bi-quad filter pair as described in: http://www.ai.sri.com/ajh/ambisonics/BLaH3.pdf b0 + b1*z^-1 + b2*z^-2 H(z) = ------------------------ a0 + a1*z^-1 + a2*z^-2 where: a0 = 1 2(k^2 − 1) a1 = -------------- k^2 + 2k + 1 k^2 - 2k + 1 a2 = -------------- k^2 + 2k + 1 low-pass:                   high-pass: k^2                          1 b0 = -------------          b0 = -------------- k^2 + 2k + 1                k^2 + 2k + 1 b1 = 2b0                    b1 = -2b0 b2 = b0                     b2 = b0 and pi * crossover_frequency k = tan -------------------------- sample_frequency @param sample_rate Sampling rate in [Hz] @param crossover_frequency Cross-over frequency in [Hz] @param low_pass_coefficients Output structure of low-pass bi-quad coefficients @param high_pass_coefficients Output structure of high-pass bi-quad coefficients.
- L145 _prototype_ `BiquadCoefficients ComputeLowPassBiquadCoefficients( int sample_rate, float specification_frequency, float attenuation);` (scope `vraudio`) — @param sample_rate Sampling rate in Hz. @param specification_frequency Frequency at which attenuation applies in Hz. @param attenuation Attenuation at specification_frequency in negative dB. @return low_pass Output structure of low-pass BiquadCoefficients.
- L172 _prototype_ `float ComputeLowPassMonoPoleCoefficient(float cuttoff_frequency, int sample_rate);` (scope `vraudio`) — Generates a coefficient for the |MonoPoleFilterClass| based on a 3dB bandwidth. The Laplace transfer function of a first order low pass system is: 1 ------------     where tau is the RC time constant of the system. 1 + tau * s For a discrete moving average filter with input x[n] and output y[n], the difference equation is: y[n] =  a * y[n - 1] + (1 - a) * x[n] tau a = ----------   where T is the sample period. tau + T since the -3dB bandwith of a first order system can be 1       related to its time constant by f3 = -------------- 2 * pi * tau       we can obtain 'a' from cuttoff_frequency and sample rate. @param cuttoff_frequency The -3dB frequency in Hz of the low pass lobe. @param sample_rate System sampling rate. @return A |MonoPoleFilterClass| coefficient for the specified bandwidth.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/fir_filter.h` (Private)


#### class `vraudio::FirFilter`  
`class FirFilter`  
_L24-58_
- L30 _public prototype_ `FirFilter(const AudioBuffer::Channel& filter_coefficients, size_t frames_per_buffer);` — Constructs a |FirFilter| from a mono |AudioBuffer| of filter coefficients. @param filter_coefficients FIR filter coefficients. @param frames_per_buffer Number of frames of data in each audio buffer.
- L38 _public prototype_ `void Process(const AudioBuffer::Channel& input, AudioBuffer::Channel* output);` — Filters an array of input with a finite impulse response (FIR) filter in the time domain. All pointers and lengths passed must be SIMD compatible. @param input Pointer to an aray of input. @param output Pointer to a cleared block of memory of the input length.
- L43 _public function_ `size_t filter_length() const` — Returns the length of the filter kernel after zeropadding. @return Length of the FIR filter in frames.
- L47 _private member_ `size_t filter_length_;` — Length of the filter kernel in frames after zeropadding.
- L51 _private member_ `size_t num_filter_chunks_;` — Number of filter chunks equivalent to the filter length after zeropadding divided by the SIMD_LENGTH.
- L54 _private member_ `AudioBuffer coefficients_;` — Coefficients of the filter stored in a repeated format.
- L57 _private member_ `AudioBuffer state_;` — Aligned buffer of previous and current input.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_FIR_FILTER_H_`
- L22 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/gain.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_GAIN_H_`
- L23 _namespace_ `namespace vraudio`
- L35 _prototype_ `float LinearGainRamp(size_t ramp_length, float start_gain, float end_gain, const AudioBuffer::Channel& input_samples, AudioBuffer::Channel* output_samples, bool accumulate_output);` (scope `vraudio`) — Implements a linearly-interpolated application of gain to a buffer channel. @param ramp_length Length of interpolation ramp in samples. Must be > 0. @param start_gain Starting gain value for ramp. @param end_gain Finishing gain value for ramp. @param input_samples Channel buffer to which interpolated gain is applied. @param output_samples Channel buffer to contain scaled output. @param accumulate_output True if the processed input should be mixed into the output. Otherwise, the output will be replaced by the processed input. @return Next gain value to be applied to the buffer channel.
- L48 _prototype_ `void ConstantGain(size_t offset_index, float gain, const AudioBuffer::Channel& input_samples, AudioBuffer::Channel* output_samples, bool accumulate_output);` (scope `vraudio`) — Applies a gain value to a vector of buffer samples starting at some offset. @param offset_index Starting index for gain application in buffer. @param gain Gain value applied to samples. @param input_samples Channel buffer to which gain is applied. @param output_samples Channel buffer to contain scaled output. @param accumulate_output True if the processed input should be mixed into the output. Otherwise, the output will be replaced by the processed input.
- L56 _prototype_ `bool IsGainNearZero(float gain);` (scope `vraudio`) — Checks if the gain factor is close enough to zero (less than -60 decibels). @param gain Gain value to be tested. @return true if the current gain factors are near zero, false otherwise.
- L63 _prototype_ `bool IsGainNearUnity(float gain);` (scope `vraudio`) — Checks if the gain state is close enough to Unity (less than -60 decibels below or above). @param gain Gain value to be tested. @return true if the current gain factors are near unity, false otherwise.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/gain_mixer.h` (Private)


#### class `vraudio::GainMixer`  
`class GainMixer`  
_L30-92_
- L32 _public prototype_ `GainMixer(size_t num_channels, size_t frames_per_buffer);`
- L40 _public prototype_ `void AddInput(const AudioBuffer& input, const std::vector<float>& gains);` — Adds a separately scaled version of each channel of the input buffer to the output buffer's corresponding channels. @param input Input buffer to be added. @param gains Gains to be applied to the buffers channels. Must be equal in length to the number of channels in |input|.
- L49 _public prototype_ `void AddInputChannel(const AudioBuffer::Channel& input, SourceId source_id, const std::vector<float>& gains);` — Adds a single input channel to each of the output buffer's channels, with a separate gain applied to the input channel per output channel. @param input Input channel to be added. @param source_id Identifier corresponding to the input. @param gains Gains to be applied to the buffers channels. Must be equal in length to the number of channels in the output buffer.
- L56 _public prototype_ `const AudioBuffer* GetOutput() const;` — Returns a pointer to the accumulator. @return Pointer to the processed (mixed) output buffer, or nullptr if no input has been added to the accumulator.
- L59 _public prototype_ `void Reset();` — Resets the state of the accumulator.
- L79 _private prototype_ `std::vector<GainProcessor>* GetOrCreateProcessors(SourceId source_id);` — Returns the |GainProcessor|s associated with a |source_id| (or creates one if needed) and sets the corresponding |processors_active| flag to true. @param source_id Identifier for a given input. @return The corresponding |ScalingAccumulators|.
- L82 _private member_ `const size_t num_channels_;` — Number of channels.
- L85 _private member_ `AudioBuffer output_;` — Output buffer (accumulator).
- L88 _private member_ `bool is_empty_;` — Denotes whether the accumulator has processed any inputs or not.
- L91 _private member_ `std::unordered_map<SourceId, GainProcessors> source_gain_processors_;` — Scale and accumulation processors, one per channel for each source.

#### struct `vraudio::GainMixer::GainProcessors`  
`struct GainProcessors`  
_L64-72_
- desc: Comprises one |GainProcessor| per channel of a source and a boolean to denote whether that source is active.
- L65 _public prototype_ `explicit GainProcessors(size_t num_channels);`
- L68 _public member_ `bool processors_active;` — Bool to signify if a given source is still passing data to a processor.
- L71 _public member_ `std::vector<GainProcessor> processors;` — Scale and accumulation processors, one per channel for each source.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_GAIN_MIXER_H_`
- L28 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/gain_processor.h` (Private)


#### class `vraudio::GainProcessor`  
`class GainProcessor`  
_L31-70_
- desc: Processor class which applies a gain to a vector of samples from an audio buffer. A short linear ramp is applied to the gain to reduce audible artifacts in the output.
- L35 _public prototype_ `GainProcessor();` — Default constructor keeps the gain state uninitialized. The first call to |ApplyGain| sets the internal gain state.
- L41 _public prototype_ `explicit GainProcessor(float initial_gain);` — Constructs |GainProcessor| with some initial gain value. @param initial_gain Gain value used as starting point for first processing period's gain ramping.
- L51 _public prototype_ `void ApplyGain(float target_gain, const AudioBuffer::Channel& input, AudioBuffer::Channel* output, bool accumulate_output);` — Applies gain supplied to the input samples. @param target_gain Target gain value. @param input Samples to which gain will be applied. @param output Samples to which gain has been applied. @param accumulate_output True if the processed input should be mixed into the output. Otherwise, the output will be replaced by the processed input.
- L57 _public prototype_ `float GetGain() const;` — Returns the |current_gain_| value. @return Current gain applied by the |GainProcessor|.
- L62 _public prototype_ `void Reset(float gain);` — Resets the gain processor to a new gain factor. @param gain Gain value.
- L66 _private member_ `float current_gain_;` — Latest gain value to be applied to buffer values.
- L69 _private member_ `bool is_initialized_;` — Flag to indiciate if an initial gain has been assigned.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_GAIN_PROCESSOR_H_`
- L26 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/mixer.h` (Private)


#### class `vraudio::Mixer`  
`class Mixer`  
_L30-58_
- desc: Accepts multiple input buffers and outputs a downmix to a single output buffer. All input buffers must have the same number of frames per buffer, the output will have the target number of channels regardless of the input number of channels.
- L36 _public prototype_ `Mixer(size_t target_num_channels, size_t frames_per_buffer);` — Constructor. @param target_num_channels Target number of channels in accumulator buffer. @param frames_per_buffer Number of frames in accumulator buffer.
- L41 _public prototype_ `void AddInput(const AudioBuffer& input);` — Adds an input buffer to the mixer, updates the output buffer accordingly. @param input Input buffer to be added.
- L47 _public prototype_ `const AudioBuffer* GetOutput() const;` — Returns a pointer to the accumulator. @return Pointer to the processed (mixed) output buffer, or nullptr if no input has been added to the accumulator.
- L50 _public prototype_ `void Reset();` — Resets the state of the accumulator.
- L54 _private member_ `AudioBuffer output_;` — Output buffer (accumulator).
- L57 _private member_ `bool is_empty_;` — Denotes whether the accumulator has processed any inputs or not.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_MIXER_H_`
- L24 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/mono_pole_filter.h` (Private)


#### class `vraudio::MonoPoleFilter`  
`class MonoPoleFilter`  
_L25-53_
- desc: Class representing a mono pole filter. This class also performs filtering.
- L30 _public prototype_ `explicit MonoPoleFilter(float coefficient);` — Constructs a |MonoPoleFilter| given a single coefficient. @param coefficient A single coefficient between 0.0f and 1.0f.
- L39 _public prototype_ `bool Filter(const AudioBuffer::Channel& input, AudioBuffer::Channel* output);` — Filter method for use with AudioBuffer::Channel. @param input |AudioBuffer::Channel| of input to be processed. @param output Pointer to output |AudioBuffer::Channel|. @return Returns false if the filter has an allpass configuration. This helps to avoid copies whenever the output is expected to be identical to the input.
- L44 _public prototype_ `void SetCoefficient(float coefficient);` — Sets the filter's coefficent. @param coefficient A mono pole filter coefficient.
- L48 _private member_ `float previous_output_;` — The previous frame computed by the filter.
- L52 _private member_ `float coefficient_;` — Represents and maintains the state of the filter in terms of its transfer function coefficient.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_MONO_POLE_FILTER_H_`
- L22 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/multi_channel_iir.h` (Private)


#### class `vraudio::MultiChannelIir`  
`class MultiChannelIir`  
_L30-86_
- desc: Class that performs IIR filtering on interleaved data. This class can be used to implement any order of IIR filter on multichannel data where the number of channels is a multiple of the SIMD vector length.
- L41 _public prototype_ `static std::unique_ptr<MultiChannelIir> Create( size_t num_channels, size_t frames_per_buffer, const std::vector<std::vector<float>>& numerators, const std::vector<std::vector<float>>& denominators);` — Returns a |MultiChannelIir| given valid parameters. @param num_channels Number of channels in each input buffer. The number of channels must be divisible by |SIMD_LENGTH|. @param frames_per_buffer Number of frames in each input buffer. @param numerators Numerator coefficients, one set per channel. @param denominators Denominator coefficients, should be equal in length to the |numerator| vector, one set per channel. @return A |MultiChannelIir| instance.
- L51 _public prototype_ `void Process(AudioBuffer::Channel* interleaved_buffer);` — Processes an interleaved buffer of input data with the given IIR filter. @param interleaved_buffer A single channel of data containing input in interleaved format, this will contain output data in interleaved format on return.
- L61 _private prototype_ `MultiChannelIir(size_t num_channels, size_t frames_per_buffer, size_t num_coefficients);` — Constructs a |MultiChannelIir|. @param num_channels Number of channels in each input buffer. The number of channels must be divisible by |SIMD_LENGTH|. @param frames_per_buffer Number of frames in each input buffer. @param num_coefficients Number of coefficients in the numerator, which equals the number in the denominator.
- L65 _private member_ `const size_t num_channels_;` — Number of channels in each input buffer.
- L69 _private member_ `const size_t frames_per_buffer_;` — Number of frames in each input buffer.
- L73 _private member_ `const size_t num_coefficients_;` — Number of coefficients in the numerator and denominator polynomials.
- L76 _private member_ `size_t delay_line_front_;` — Current front of the delay line which is circularly indexed.
- L79 _private member_ `AudioBuffer numerator_;` — Stores numerator coefficients in repeated fashion.
- L82 _private member_ `AudioBuffer denominator_;` — Stores denominator coefficients in repeated fashion.
- L85 _private member_ `AudioBuffer delay_line_;` — Holds previous data computed from the numerator section.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_MULTI_CHANNEL_IIR_H_`
- L25 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/near_field_processor.h` (Private)


#### class `vraudio::NearFieldProcessor`  
`class NearFieldProcessor`  
_L32-71_
- desc: Class which applies an approximate near field effect to a source mono input. The effect consists of a +6dB bass boost (shelf-filter) as well as phase correction (HRTF group delay compensation) when the signal is to be combined with the binaural output. For more information: [internal ref]
- L39 _public prototype_ `NearFieldProcessor(int sample_rate, size_t frames_per_buffer);` — Constructor of the |NearFieldProcessor|, uses the following parameters: @param sample_rate Sampling rate in [Hz]. @param frames_per_buffer Number of frames per buffer in the input/output signal.
- L42 _public function_ `size_t GetDelayCompensation() const` — Returns currently used delay compensation in samples.
- L49 _public prototype_ `void Process(const AudioBuffer::Channel& input, AudioBuffer::Channel* output, bool enable_hrtf);` — Applies approximate near field effect to the source mono input signal. @param input Mono input channel. @param output Pointer to mono output channel. @param enable_hrtf Whether to enable delay compensation for HRTF filtering.
- L54 _private member_ `const size_t frames_per_buffer_;` — Number of frames per buffer.
- L59 _private member_ `const size_t delay_compensation_;` — Delay compensation computed as average group delay of the HRTF filter minus average group delay of the shelf-filter. Should be disabled when using with stereo-panned sound sources.
- L62 _private member_ `BiquadFilter lo_pass_filter_;` — Biquad filters that apply frequency splitting of the input mono signal.
- L63 _private member_ `BiquadFilter hi_pass_filter_;`
- L67 _private member_ `AudioBuffer low_passed_buffer_;` — Buffer for the low-passed signal. We do not modify the high-passed signal so we can write it directly to the output channel.
- L70 _private member_ `DelayFilter delay_filter_;` — Delay filter used to delay the incoming input mono buffer.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_NEAR_FIELD_PROCESSOR_H_`
- L24 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/occlusion_calculator.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_OCCLUSION_CALCULATOR_H_`
- L22 _namespace_ `namespace vraudio`
- L38 _prototype_ `float CalculateDirectivity(float alpha, float order, const SphericalAngle& spherical_angle);` (scope `vraudio`) — Calculates directivity gain value for supplied source and listener parameters. @param alpha Balance between dipole pattern and omnidirectional pattern for source emission. By varying this value, differing directivity patterns can be formed. Value in range [0, 1]. 2D visualization for several values: http://goo.gl/GhKvoc. @param order Order of directivity function. Higher values will result in increased directivity. Value in range [1, +inf]. 2D visualization for several orders: http://goo.gl/sNrm1a. @param spherical_angle Spherical angle of the listener relative to the audio source which is being shaped. @return Gain value in range [0, 1].
- L49 _prototype_ `float CalculateOcclusionFilterCoefficient(float directivity, float occlusion_intensity);` (scope `vraudio`) — This function calculates a |MonoPoleFilter| coefficient based upon the directivity and occlusion values. The coefficient calculation was designed via empirical methods. @param directivity Gain value calculated based upon the directivity. @param occlusion_intensity Gain value calculated based upon the degree of occlusion. @return Filter coefficient for a mono pole low pass filter.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/partitioned_fft_filter.h` (Private)


#### class `vraudio::PartitionedFftFilter`  
`class PartitionedFftFilter`  
_L34-163_
- desc: Class performing a FFT-based overlap and add FIR convolution. Given an FFT size N and a filter size M > N/2; the filter is broken in to floor(M/(N/2)) partitions in the time domain. This results in a set of frequency domain "filters" of length (N/2)+1.
- L38 _public typedef_ `typedef AudioBuffer FreqDomainBuffer;` — Typedef declares the data type for storing frequency domain buffers. Each channel stores the kernel for a partition.
- L47 _public prototype_ `PartitionedFftFilter(size_t filter_size, size_t frames_per_buffer, FftManager* fft_manager);` — Constructor preallocates memory based on the |filter_size|. This can be used for simplicity if the filter size will be constant after creation. @param filter_size Length of the time domain filter in samples. This will be increased such that it becomes a multiple of |chunk_size_|. @param frames_per_buffer Number of points in each time domain input buffer. @param fft_manager Pointer to a manager to perform FFT transformations.
- L59 _public prototype_ `PartitionedFftFilter(size_t filter_size, size_t frames_per_buffer, size_t max_filter_size, FftManager* fft_manager);` — Constructor preallocates memory based on the |max_filter_size|. The |fft_size_| will be twice |frames_per_buffer| if this is a power of two and twice the next larger power of two if it is not. @param filter_size Length of the time domain filter in samples. This will be increased such that it becomes a multiple of |chunk_size_|. @param frames_per_buffer Number of points in each time domain input buffer. @param max_filter_size Maximum length that |filter_size| can get. @param fft_manager Pointer to a manager for all fft related functionality.
- L65 _public prototype_ `void SetTimeDomainKernel(const AudioBuffer::Channel& kernel);` — Initializes the FIR filter from a time domain kernel. @parem kernel Time domain filter to be used for processing.
- L70 _public prototype_ `void SetFreqDomainKernel(const FreqDomainBuffer& kernel);` — Initializes the FIR filter from a precomputed frequency domain kernel. @param kernel Frequency domain filter to be used for processing.
- L79 _public prototype_ `void ReplacePartition(size_t partition_index, const AudioBuffer::Channel& kernel_chunk);` — Replaces a partition indicated by the |partition_index| with |kernel_chunk|'s frequency domain equivalent. @param partition_index Location (partition) of the time domain filter we wish to replace. @param kernel_chunk |fft_size_|/2 length chunk of a filter used to replace the |partition_index|th partition.
- L88 _public prototype_ `void SetFilterLength(size_t new_filter_size);` — Alters the filter length by adding or removing partitions in the frequency domain. If |new_filter_size| is not a multiple of |chunk_size_| (i.e. frames per buffer), then the time domain filter kernel will be zeropadded to a multiple of |chunk_size_|. @param new_filter_size New length of the time domain filter kernel.
- L94 _public prototype_ `void Filter(const FreqDomainBuffer::Channel& input);` — Processes a block of frequency domain samples. The size of the input block must be |fft_size_|. @param Frequency domain input buffer.
- L99 _public prototype_ `void GetFilteredSignal(AudioBuffer::Channel* output);` — Returns block of filtered signal output of size |fft_size_|/2. @param output Time domain block filtered with the given kernel.
- L102 _public prototype_ `void Clear();` — Resets the filter state.
- L112 _private prototype_ `void ResetFreqDomainBuffers(size_t new_kernel_size);` — Adjusts the |num_partitions_| and the size of |freq_domain_buffers_| for use with a new time domain filter kernel greater in length than the previous kernel. @param new_kernel_size Length of the time domain filter kernel.
- L115 _private member_ `FftManager* const fft_manager_;` — Manager for all FFT related functionality (not owned).
- L118 _private member_ `const size_t fft_size_;` — Number of points in the |fft_manager_|s FFT.
- L121 _private member_ `const size_t chunk_size_;` — Size of each partition of the filter in time domain.
- L124 _private member_ `const size_t frames_per_buffer_;` — Number of frames in each buffer of input data.
- L127 _private member_ `const size_t max_filter_size_;` — Maximum filter size in samples.
- L130 _private member_ `const size_t max_num_partitions_;` — Maximum partition count.
- L133 _private member_ `size_t filter_size_;` — Filter size in samples.
- L136 _private member_ `size_t num_partitions_;` — Partition Count.
- L139 _private member_ `FreqDomainBuffer kernel_freq_domain_buffer_;` — Kernel buffer in frequency domain.
- L142 _private member_ `size_t buffer_selector_;` — Buffer selector to switch between two filtered signal buffers.
- L145 _private member_ `size_t curr_front_buffer_;` — The freq_domain_buffer we will write new incoming audio into.
- L148 _private member_ `FreqDomainBuffer freq_domain_buffer_;` — Frequency domain buffer used to perform filtering.
- L151 _private member_ `AudioBuffer filtered_time_domain_buffers_;` — Two buffers that are consecutively filled with filtered signal output.
- L154 _private member_ `FreqDomainBuffer freq_domain_accumulator_;` — Accumulator for the outputs from each convolution partition
- L158 _private member_ `AudioBuffer temp_zeropad_buffer_;` — Temporary time domain buffer to store output when zero padding has been applied due to non power of two input buffer lengths.
- L162 _private member_ `AudioBuffer temp_kernel_chunk_buffer_;` — Temporary time domain buffer to hold time domain kernel chunks during conversion of a kernel from time to frequency domain.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_PARTITIONED_FFT_FILTER_H_`
- L28 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/reflection.h` (Private)


#### struct `vraudio::Reflection`  
`struct Reflection`  
_L24-30_
- desc: Describes a room reflection that contains information on its time of arrival and magnitude.
- L26 _public member_ `float delay_time_seconds = 0.0f;` — Time of arrival of the reflection in seconds.
- L29 _public member_ `float magnitude = 0.0f;` — Magnitude of the reflection.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_REFLECTION_H_`
- L20 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/reflections_processor.h` (Private)


#### class `vraudio::ReflectionsProcessor`  
`class ReflectionsProcessor`  
_L41-124_
- desc: Class that accepts single mono buffer as input and outputs a first order ambisonic buffer of the mix of all the rooms early reflections computed for the buffer. The input consists of a mono mix of all the sound objects in the system. The reflections are assumed to be aligned with the aabb axes and thus the first order ambisonic axes.
- L47 _public prototype_ `ReflectionsProcessor(int sample_rate, size_t frames_per_buffer);` — Constructs a |ReflectionsProcessor|. @param sample_rate System sampling rate. @param frames_per_buffer System frames per buffer.
- L53 _public prototype_ `void Update(const ReflectionProperties& reflection_properties, const WorldPosition& listener_position);` — Updates reflections according to the new |ReflectionProperties|. @param reflection_properties New reflection properties. @param listener_position New listener position.
- L60 _public prototype_ `void Process(const AudioBuffer& input, AudioBuffer* output);` — Processes a mono |AudioBuffer| into an ambisonic |AudioBuffer|. @param input Mono input buffer. @param output Ambisonic output buffer.
- L65 _public function_ `size_t num_frames_to_process_on_empty_input() const` — Returns the number of frames required to keep processing on empty input signal. This value can be used to avoid any potential artifacts on the final output signal when the input signal stream is empty.
- L71 _private prototype_ `void UpdateGainsAndDelays();` — Updates |gains_| and |delays_| vectors of the |ReflectionsProcessor|.
- L77 _private prototype_ `void ApplyReflections(AudioBuffer* output);` — Applies |target_reflections_| and fast-encodes them into first order ambisonics. @param output Ambisonic output buffer.
- L80 _private member_ `const int sample_rate_;` — System sampling rate.
- L83 _private member_ `const size_t frames_per_buffer_;` — System number of frames per buffer.
- L86 _private member_ `const size_t max_delay_samples_;` — Maximum allowed delay time for a reflection (in samples).
- L89 _private member_ `MonoPoleFilter low_pass_filter_;` — Low pass filter to be applied to input signal.
- L92 _private member_ `AudioBuffer temp_mono_buffer_;` — Audio buffer to store mono low pass filtered buffers during processing.
- L95 _private member_ `AudioBuffer current_reflection_buffer_;` — Audio buffers to store FOA reflections buffers during crossfading.
- L96 _private member_ `AudioBuffer target_reflection_buffer_;`
- L99 _private member_ `std::vector<Reflection> target_reflections_;` — Target reflections filled with new data when |Update| is called.
- L102 _private member_ `bool crossfade_;` — Indicates whether relfections have been updated and a crossfade is needed.
- L105 _private member_ `BufferCrossfader crossfader_;` — Buffer crossfader to apply linear crossfade during reflections update.
- L108 _private member_ `size_t num_frames_to_process_on_empty_input_;` — Number of frames needed to keep processing on empty input signal.
- L111 _private member_ `std::vector<size_t> delays_;` — Number of samples of delay to be applied for each reflection.
- L114 _private member_ `DelayFilter delay_filter_;` — Delay filter to delay the incoming buffer.
- L117 _private member_ `AudioBuffer delay_buffer_;` — Delay buffer used to store delayed reflections before scaling and encoding.
- L120 _private member_ `std::vector<float> gains_;` — Gains to be applied for each reflection.
- L123 _private member_ `std::vector<GainProcessor> gain_processors_;` — |GainProcessor|s to apply |gains_|.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_REFLECTIONS_PROCESSOR_H_`
- L32 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/resampler.h` (Private)


#### class `vraudio::Resampler`  
`class Resampler`  
_L25-131_
- desc: Class that provides rational resampling of audio data.
- L27 _public prototype_ `Resampler();`
- L34 _public prototype_ `void Process(const AudioBuffer& input, AudioBuffer* output);` — Resamples an |AudioBuffer| of input data sampled at |source_frequency| to |destination_frequency|. @param input Input data to be resampled. @param output Resampled output data.
- L42 _public prototype_ `size_t GetMaxOutputLength(size_t input_length) const;` — Returns the maximum length which the output buffer will be, given the current source and destination frequencies and input length. The actual output length will either be this or one less. @param input_length Length of the input. @return Maximum length of the output.
- L49 _public prototype_ `size_t GetNextOutputLength(size_t input_length) const;` — Returns the next length which the output buffer will be, given the current source and destination frequencies and input length. @param input_length Length of the input. @return Next length of the output.
- L58 _public prototype_ `void SetRateAndNumChannels(int source_frequency, int destination_frequency, size_t num_channels);` — Sets the source and destination sampling rate as well as the number of channels. Note this method only resets the filter state number of channel changes. @param source_frequency Sampling rate of input data. @param destination_frequency Desired output sampling rate. @param num_channels Number of channels to process.
- L66 _public prototype_ `static bool AreSampleRatesSupported(int source, int destination);` — Returns whether the sampling rates provided are supported by the resampler. @param source Source sampling rate. @param destination Destination sampling rate. @return True if the sampling rate pair are supported.
- L70 _public prototype_ `void ResetState();` — Resets the inner state of the |Resampler| allowing its use repeatedly on different data streams.
- L79 _private prototype_ `void InitializeStateBuffer(size_t old_state_num_frames);` — Initializes the |state_| buffer. Called when sampling rate is changed or the state is reset. @param size_t old_state_num_frames Number of frames in the |state_| buffer previous to the most recent call to |GenerateInterpolatingFilter|.
- L84 _private prototype_ `void GenerateInterpolatingFilter(int sample_rate);` — Generates a windowed sinc to act as the interpolating/anti-aliasing filter. @param sample_rate The system sampling rate.
- L91 _private prototype_ `void ArrangeFilterAsPolyphase(size_t filter_length, const AudioBuffer::Channel& filter);` — Arranges the anti aliasing filter coefficients in polyphase filter format. @param filter_length Number of frames in |filter| containing filter coefficients. @param filter Vector of filter coefficients.
- L101 _private prototype_ `void GenerateSincFilter(float cutoff_frequency, float sample_rate, size_t filter_length, AudioBuffer::Channel* buffer);` — Generates Hann windowed sinc function anti aliasing filters. @param cutoff_frequency Transition band (-3dB) frequency of the filter. @param sample_rate The system sampling rate. @param filter_length Number of frames in |buffer| containing filter coefficients. @param buffer |AudioBuffer::Channel| to contain the filter coefficients.
- L105 _private member_ `size_t up_rate_;` — Rate of the interpolator section of the rational sampling rate converter.
- L108 _private member_ `size_t down_rate_;` — Rate of the decimator section of the rational sampling rate convereter.
- L111 _private member_ `size_t time_modulo_up_rate_;` — Time variable for the polyphase filter.
- L114 _private member_ `size_t last_processed_sample_;` — Marks the last processed sample of the input.
- L117 _private member_ `size_t num_channels_;` — Number of channels in the |AudioBuffer|s processed.
- L120 _private member_ `size_t coeffs_per_phase_;` — Number of filter coefficients in each phase of the polyphase filter.
- L123 _private member_ `AudioBuffer transposed_filter_coeffs_;` — Filter coefficients stored in polyphase form.
- L127 _private member_ `AudioBuffer temporary_filter_coeffs_;` — Filter coefficients in planar form, used for calculating the transposed filter.
- L130 _private member_ `AudioBuffer state_;` — Buffer holding the samples of input required between input buffers.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_RESAMPLER_H_`
- L22 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/reverb_onset_compensator.h` (Private)


#### class `vraudio::ReverbOnsetCompensator`  
`class ReverbOnsetCompensator`  
_L32-106_
- desc: Implements a convolutional compensator for the spectral reverb onset curve.
- L39 _public prototype_ `ReverbOnsetCompensator(int sampling_rate, size_t frames_per_buffer, FftManager* fft_manager);` — Constructs a |ReverbOnsetCompensator|. @param sampling_rate The sampling rate in Hz. @param frames_per_buffer The number of frames per buffer in the system. @param fft_manager Pointer to a FftManager to perform FFT transformations.
- L49 _public prototype_ `void Update(const float* rt60_values, float gain);` — Resets the reverb with a new set of reverberation times. The new tail is generated by replacing the current tail buffer by buffer. @param rt60_values |kNumReverbOctaveBands| values denoting the reverberation decay time to -60dB in octave bands starting at |kLowestOctaveBand|. @param gain Gain to be applied across all frequencies.
- L55 _public prototype_ `void Process(const AudioBuffer& input, AudioBuffer* output);` — Processes a mono |AudioBuffer| with a reverberant tail. @param input A mono |AudioBuffer| of input data. @param output Pointer to stereo output buffer.
- L62 _private prototype_ `void GenerateCorrectionCurves();` — Generates the constituent curves which are combined to make up the correction curve envelopes. These envelopes ensure the initial part of the specral reverb's impulse response, which exhibits 'growing' behaviour, follows the desired exponential decay.
- L65 _private prototype_ `void GenerateNoiseVectors();` — Generates a pair of |kNumOctaveBands| band, octave filtered, noise buffers.
- L68 _private member_ `FftManager* const fft_manager_;` — Manager for all FFT related functionality (not owned).
- L71 _private member_ `const int sampling_rate_;` — The system sampling rate.
- L74 _private member_ `const size_t frames_per_buffer_;` — The system number of frames per buffer.
- L77 _private member_ `std::vector<AudioBuffer> bandpassed_noise_left_;` — Pre-generated band-passed noise to be used as a base for the reverb tail.
- L78 _private member_ `std::vector<AudioBuffer> bandpassed_noise_right_;`
- L81 _private member_ `AudioBuffer base_curves_;` — The constituent curves used to generate the onset compensation envelopes.
- L82 _private member_ `AudioBuffer adder_curves_;`
- L85 _private member_ `PartitionedFftFilter left_filter_;` — Filter for processing the left reverberant channel.
- L88 _private member_ `PartitionedFftFilter right_filter_;` — Filter for processing the right reverberant channel.
- L92 _private member_ `DelayFilter delay_filter_;` — Delay filter used to ensure the compensation curve starts at the same point as the spectral reverb.
- L95 _private member_ `size_t num_active_processors_;` — Number of active update processors.
- L99 _private member_ `std::list<std::unique_ptr<ReverbOnsetUpdateProcessor>> update_processors_;` — Active reverb update processors to replace the corresponding filter partitions of the reverb tail within each process call.
- L102 _private member_ `AudioBuffer temp_kernel_buffer_;` — Temporary buffer used to process filter kernel partitions.
- L105 _private member_ `PartitionedFftFilter::FreqDomainBuffer temp_freq_buffer_;` — Temporary buffer to hold FFT frequency domain output.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_REVERB_ONSET_COMPENSATOR_H_`
- L29 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/reverb_onset_update_processor.h` (Private)


#### class `vraudio::ReverbOnsetUpdateProcessor`  
`class ReverbOnsetUpdateProcessor`  
_L27-109_
- desc: Updater for the |ReverbOnsetCompensator|.
- L35 _public prototype_ `ReverbOnsetUpdateProcessor(size_t frames_per_buffer, int sampling_rate, AudioBuffer* base_curves, AudioBuffer* adder_curves);` — Constructs a update processor for the sprectral reverb onset compensator. @param frames_per_buffer_ System buffer length in frames. @param sampling_rate System sample rate. @param base_curves Constituent curve used for envelope generation. @param ader_curves Constituent curve used for envelope generation.
- L44 _public prototype_ `void SetReverbTimes(const float* rt60_values);` — Sets reverberation times in different frequency bands. @param rt60_values |kNumReverbOctaveBands| values denoting the reverberation decay time to -60dB in octave bands starting at |kLowestOctaveBand|.
- L49 _public function_ `void SetGain(float gain)` — Sets the gain applied to the overall compensation envelope. @param gain Gain applied to overall envelope.
- L58 _public prototype_ `bool Process(const std::vector<AudioBuffer>& bandpassed_noise_left, const std::vector<AudioBuffer>& bandpassed_noise_right, AudioBuffer::Channel* kernel_channel_left, AudioBuffer::Channel* kernel_channel_right);` — Processes the next tail update. @param bandpassed_noise_left Pre-computed bandpassed noise buffer. @param bandpassed_noise_right Pre-computed bandpassed noise buffer. @param kernel_channel_left Kernel channel to fill in the processed output. @param kernel_channel_right Kernel channel to fill in the processed output. @return True if the tail update continues.
- L66 _public function_ `size_t GetCurrentPartitionIndex() const` — Returns the partition index of the current update state. @return Current partition index.
- L73 _public prototype_ `ReverbOnsetUpdateProcessor(ReverbOnsetUpdateProcessor const&) = delete;` — Disable copy and assignment operator.
- L74 _public prototype_ `void operator=(ReverbOnsetUpdateProcessor const&) = delete;`
- L78 _private member_ `int sampling_rate_;` — System sample rate.
- L81 _private member_ `size_t tail_update_cursor_;` — Current frame position of the reverb tail to be updated.
- L84 _private member_ `size_t tail_length_;` — Length of the new reverb tail to be replaced in frames.
- L87 _private member_ `float gain_;` — Gain applied to the reverb compensation.
- L91 _private member_ `std::vector<int> curve_indices_;` — Indices of the multiplication factor to be used to create the onset compensation curve at each frequency band.
- L95 _private member_ `std::vector<float> pure_decay_coefficients_;` — Decay coefficients per each band of the reverb tail, used below 0.15s @48kHz.
- L99 _private member_ `std::vector<float> pure_decay_exponents_;` — Decay exponential per each band of the reverb tail, used below 0.15s @48kHz.
- L102 _private member_ `AudioBuffer band_buffer_;` — Temporary buffers used to process the decayed noise per each band.
- L103 _private member_ `AudioBuffer envelope_buffer_;`
- L107 _private member_ `AudioBuffer* base_curves_;` — Pointers to audio buffers owned by the |ReverbOnsetCompensator| storing the constituent curves used to generate the onset compensation envelopes.
- L108 _private member_ `AudioBuffer* adder_curves_;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_REVERB_ONSET_UPDATE_PROCESSOR_H_`
- L24 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/sh_hrir_creator.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_SH_HRIR_CREATOR_H_`
- L24 _namespace_ `namespace vraudio`
- L37 _prototype_ `std::unique_ptr<AudioBuffer> CreateShHrirsFromWav(const Wav& wav, int target_sample_rate_hz, Resampler* resampler);` (scope `vraudio`) — Creates a multichannel audio buffer of Spherical Harmonic-encoded Head Related Impulse Responses (SH HRIRs) from Wav SH HRIR assets. It also checks if the channel count of the SH HRIR file is correct and resamples the SH HRIRs if necessary to match the system (target) sampling rate. @param wav |Wav| instance that contains SH HRIRs. @param target_sample_rate_hz Target sampling rate in Hertz. @param resampler Pointer to a resampler used to convert HRIRs to the system rate, (This resampler's internal state will be reset on each function call). @return Unique pointer to |AudioBuffer| where the SH HRIRs will be written.
- L48 _prototype_ `std::unique_ptr<AudioBuffer> CreateShHrirsFromAssets( const std::string& filename, int target_sample_rate_hz, Resampler* resampler);` (scope `vraudio`) — Creates a SH HRIR multichannel audio buffer from assets. @param filename Name of the Wav file that contains SH HRIRs. @param target_sample_rate_hz Target sampling rate in Hertz. @param resampler Pointer to a resampler used to convert HRIRs to the system rate. @return Unique pointer to |AudioBuffer| where the SH HRIRs will be written.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/shoe_box_room.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_SHOE_BOX_ROOM_H_`
- L25 _namespace_ `namespace vraudio`
- L37 _prototype_ `void ComputeReflections(const WorldPosition& relative_listener_position, const WorldPosition& room_dimensions, const float* reflection_coefficients, std::vector<Reflection>* reflections);` (scope `vraudio`) — Computes a set of reflections from each surface of a shoe-box room model. Uses a simplified calculation method which assumes that all the sources are 'attached' to the listener. Also, assumes that the listener is inside the shoe-box room. @param relative_listener_position Relative listener position to the center of the room. @param room_dimensions Dimensions of the room. @param reflection_coefficients Reflection coefficients. @return List of computed reflections by the image source method.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/spectral_reverb.h` (Private)


#### class `vraudio::SpectralReverb`  
`class SpectralReverb`  
_L33-169_
- desc: Implements a spectral reverb producing a decorrelated stereo output. See: [1] E. Vickers, J-L Wu, P.G. Krishnan, R. N. K. Sadanandam, "Frequency Domain Artificial Reverberation using Spectral Magnitude Decay", https://goo.gl/hv1pdJ.
- L40 _public prototype_ `SpectralReverb(int sample_rate, size_t frames_per_buffer);` — Constructs a spectral reverb. @param sample_rate The system sample rate. @param frames_per_buffer System frames per buffer of input and output. Note that this class expects power of two buffers of input and output.
- L45 _public prototype_ `void SetGain(float gain);` — Sets the overall gain to be applied to the output of the reverb. @param gain Gain to be applied to the reverb output, min value 0.0f.
- L54 _public prototype_ `void SetRt60PerOctaveBand(const float* rt60_values);` — Sets the |SpectralReverb|'s reverberation times in different frequency bands. Supports times between: (0.15 * 48000 / |sample_rate|)s and (25 * 48000 / |sample_rate|)s. @param rt60_values |kNumReverbOctaveBands| values denoting the reverberation decay time to -60dB in octave bands starting at |kLowestOctaveBand|.
- L62 _public prototype_ `void Process(const AudioBuffer::Channel& input, AudioBuffer::Channel* left_out, AudioBuffer::Channel* right_out);` — Applies reverb to an input channel of audio data and produces a stereo output. @param input Mono inpu data. @param left_out Left channel of reverberated output. @param right_out Right channel of reverberated output.
- L71 _private prototype_ `void AccumulateOverlap(size_t channel_index, const AudioBuffer::Channel& buffer);` — Uses an AudioBuffer with four channels to overlap add and insert the final reverb into the output circular buffers. @param channel_index Denotes the (left or right) channel to output to. @param buffer The buffer to be added onto the pre-existing reverb output.
- L77 _private prototype_ `void GenerateAnalysisWindow();` — Generates a window function which is a normalized sum of three overlapping (50%) hann windows of length (|kFftSize| / 2) that also incorporates the inverse fft scaling.
- L82 _private prototype_ `` — Generates a large buffer of sines and cosines of random noise between 0 and pi to be randomly indexed into in order to cheaply generate highly
- L91 _private prototype_ `void GetNextReverbBlock(size_t delay_index, AudioBuffer::Channel* left_channel, AudioBuffer::Channel* right_channel);` — Obtains the next stero pair of time domain reverb blocks which can then be summed together in an overlap add fashion to provide the reverb output. @param delay_index An index into the frequency domain magnitude ring buffer. @param left_channel Channel to contain the left partial reverb output. @param right_channel Channel to contain the right partial reverb output.
- L99 _private prototype_ `void InitializeCircularBuffersAndAccumulators();` — Initializes the output circular buffers such that they contain zeros if the value of |frames_per_buffer_| is sufficiently smaller than that of |kOverlapLength| that buffering of input will be required prior to processing. Also allocates memory for the output accumulators.
- L102 _private member_ `const int sample_rate_;` — System sample rate.
- L105 _private member_ `const size_t frames_per_buffer_;` — System frames per buffer.
- L109 _private member_ `size_t magnitude_delay_index_;` — Indices into the magnitude and overlap add delay lines, modulo of their respective lengths.
- L110 _private member_ `size_t overlap_add_index_;`
- L114 _private member_ `FftManager fft_manager_;` — Manages the time-frequency transforms and phase/magnitude-frequency transforms.
- L118 _private member_ `AudioBuffer sin_cos_random_phase_buffer_;` — Buffer containing sines and cosines of random values between 0 and pi to be used for phase.
- L122 _private member_ `AudioBuffer unscaled_window_;` — Buffer containing a triple overlapping hann window for windowing time domain data.
- L126 _private member_ `AudioBuffer window_;` — Buffer containing a triple overlapping hann window for windowing time domain data, this window has been scaled by the output gain factor.
- L129 _private member_ `AudioBuffer feedback_;` — Buffer containing RT60 tuned feedback values.
- L133 _private member_ `AudioBuffer magnitude_compensation_;` — Buffer used to store scaling values which account for the different initial peak magnitudes for different RT60s.
- L136 _private member_ `AudioBuffer magnitude_delay_;` — Buffer that acts as the frequency domain magnitde delay.
- L139 _private member_ `AudioBuffer fft_size_input_;` — Buffer to contain a linear |kFftSize| chunk of input data.
- L143 _private member_ `CircularBuffer input_circular_buffer_;` — Circular buffers to sit at the input and output of the |Process()| method to allow |frames_per_buffer_| to differ from |kFftSize|.
- L144 _private member_ `std::vector<std::unique_ptr<CircularBuffer>> output_circular_buffers_;`
- L147 _private member_ `AudioBuffer out_time_buffer_;` — Time domain buffer used to store reverb before the overlap add operation.
- L151 _private member_ `AudioBuffer temp_freq_buffer_;` — Temporary frequency domain buffer, used to store frequency domain data when transforming between Pffft and Canonical format frequency domain data.
- L154 _private member_ `AudioBuffer scaled_magnitude_buffer_;` — Buffer used to store feedback scaled magnitude values.
- L157 _private member_ `AudioBuffer temp_magnitude_buffer_;` — Buffer used for the accumulation of scaled magnitude buffers.
- L160 _private member_ `AudioBuffer temp_phase_buffer_;` — Buffer used to store randomized phase.
- L163 _private member_ `std::vector<AudioBuffer> output_accumulator_;` — Buffers used to calculate the overlap add at the output.
- L167 _private member_ `bool is_gain_near_zero_;` — Processing of the spectral reverb is bypassed when the feedback values are all approximately zero OR when the gain is set to near zero.
- L168 _private member_ `bool is_feedback_near_zero_;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_SPECTRAL_REVERB_H_`
- L27 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/spectral_reverb_constants_and_tables.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_SPECTRAL_REVERB_CONSTANTS_AND_TABLES_H_`
- L23 _namespace_ `namespace vraudio`
- L27 _variable_ `static const float kDefaultSpectralReverbSampleRate = 48000.0f;` (scope `vraudio`) — Sampling rate for which the spectral reverb feedback coefficients are calculated.
- L30 _variable_ `static const float kMinReverbTimeForFeedback48kHz = 0.15f;` (scope `vraudio`) — Minimum reverb time supported by the feedback table below (seconds).
- L34 _variable_ `static const float kTimeStepSizeForFeedback48kHz = 0.01f;` (scope `vraudio`) — Step size between each reverberation time supported by the feedback table (seconds).
- L37 _variable_ `static const size_t kNumFeedbackValues = 2485;` (scope `vraudio`) — Number of entries in the feedback table below.
- L42 _variable_ `const int kInvalidIndex = -1;` (scope `vraudio`) — Value denoting an invalid index into the feedback and magnitude correction tables. The feedback and magnitude correction factors will be 0.0 when this value is returned from the index lookup method.
- L45 _variable_ `const size_t kCompensationOnsetLength = 1024;` (scope `vraudio`) — Number of frames of zeros before the reverb onset curve.
- L48 _variable_ `const size_t kCorrectionCurveLength = 6144;` (scope `vraudio`) — Length in samples of the spectral reverb onset correction curves.
- L52 _variable_ `const size_t kCurveChangeoverIndex = 51;` (scope `vraudio`) — Index of the feedback factor and curve multipliers. below which the low frequency correction curves must be used.
- L56 _variable_ `const float kCurveOffset = 3584.5f;` (scope `vraudio`) — Offset and scaling values for the compensation curve polynomials. Used to ensure the polynomial fitting was well conditioned.
- L57 _variable_ `const float kCurveScale = 0.00027897893709025f;` (scope `vraudio`)
- L60 _variable_ `const size_t kCurvePolynomialLength = 5;` (scope `vraudio`) — Number of coefficients in the curve generation polynomials.
- L64 _variable_ `const float kHighReverberationCorrectionCurve[kCurvePolynomialLength] = { 0.207891278205479f, -0.32101050261694f, 0.124608132159297f, 0.0119620847734548f, -0.0093840571415877f};` (scope `vraudio`) — Coefficients of the curves making up the first part of the compensation envelopes, split into low and high frequency part.
- L68 _variable_ `const float kLowReverberationCorrectionCurve[kCurvePolynomialLength] = { 0.0277040197264401f, -0.0394421854392145f, 0.0519110103856154f, -0.0778183422829366f, 0.0343221444553963f};` (scope `vraudio`)
- L73 _variable_ `const size_t kReverbLookupOffset = static_cast<size_t>( kMinReverbTimeForFeedback48kHz / kTimeStepSizeForFeedback48kHz);` (scope `vraudio`) — Offset from zero for indexing into the feedback array.
- L84 _function_ `static inline int GetFeedbackIndexFromRt60(float reverberation_time, float sample_rate)` (scope `vraudio`) — Returns an index to the feedback factor corresponding to the given reverberation time. Supports times between: (0.15 * 48000 / |sample_rate|)s and (25 * 48000 / |sample_rate|)s. @param reverberation_time RT60 in seconds. @return Index to the closest spectral reverb feedback factor in |kSpectralReverbFeedback|, or |kInvalidIndex| if |reverberation_time| is too small.
- L103 _variable_ `static const float kSpectralReverbFeedback[kNumFeedbackValues] = { 0.231626448720861f, 0.231626448720861f, 0.271965742827169f, 0.291599040391330f, 0.313450848869688f, 0.332864905289138f, 0.350285532738638f, 0.366049684043223f, 0.383143567924904f, 0.398574170268545f, 0.427500186399158f, 0.441038795823222f, 0.453430889363735f, 0.466397294153677f, 0.478272702354267f, 0.490519904155818f, 0.501757394995813f, 0.512125955040727f, 0.521739757418252f, 0.548135448526531f, 0.548135448526531f, 0.563990087718933f, 0.571497329505391f, 0.578784680803617f, 0.585892965998708f, 0.592858971592466f, 0.599714945736390f, 0.606488097764666f, 0.613200097727167f, 0.619866575922435f, 0.626496622430680f, 0.633092286646765f, 0.639648076813205f, 0.646150459553150f, 0.652577359403386f, 0.658897658347319f, 0.665070695347976f, 0.671045765880981f, 0.676761621467567f, 0.682145969207546f, 0.682145969207546f, 0.687114971312322f, 0.691572744637866f, 0.695410860217716f, 0.700728670360266f, 0.701931035813262f, 0.700570291691920f, 0.718477641957808f, 0.718477641957808f, 0.721948612036913f, 0.725341703212013f, 0.728658944837357f, 0.731902322614612f, 0.735073779107144f, 0.738175214254303f, 0.741208485885712f, 0.744175410235544f, 0.747077762456819f, 0.749917277135678f, 0.752695648805674f, 0.755414532462056f, 0.758075544076055f, 0.760680261109167f, 0.763230223027440f, 0.765726931815758f, 0.768171852492127f, 0.770566413621959f, 0.772912007832361f, 0.775209992326414f, 0.777461689397460f, 0.779668386943394f, 0.78183133898 ...` (scope `vraudio`) — Mapping between reverberation times at a given frequency and the corresponding feedback value required in the specral reverb. This table covers reverberation times between kMinReverbTimeForFeedback and kNumFeedbackValues * kTimeStepSizeForFeedback, i.e. 0.15s and 25s @48kHz.
- L940 _variable_ `static const float kMagnitudeCompensation[kNumFeedbackValues] = { 17.3996715487709f, 17.4034178858004f, 16.6795907475848f, 16.3502965109599f, 15.9879028507326f, 15.6718483944106f, 15.4042251167111f, 15.1677088170684f, 14.9119678952536f, 14.6906933374371f, 14.2839187463763f, 14.0999475816121f, 13.9338828421032f, 13.7652114598195f, 13.6133888181873f, 13.4638764218013f, 13.3247278048121f, 13.1976499042192f, 13.0833841919256f, 12.7669049046296f, 12.7761019806869f, 12.7855596748707f, 12.5979372062571f, 12.5244917829334f, 12.4453918694998f, 12.3672592847373f, 12.3020244979211f, 12.2257529341565f, 12.1547662449381f, 12.0845455398564f, 12.0231689748723f, 11.9586881174297f, 11.8906434508319f, 11.8264759328308f, 11.7652619217413f, 11.7033346037227f, 11.6379964417238f, 11.5862703081324f, 11.5299758955061f, 11.4741541469989f, 11.4224679633351f, 11.4302928484179f, 11.3885962828649f, 11.3488611750486f, 11.3151942251170f, 11.2687417305887f, 11.2651043092380f, 11.2873091969354f, 11.1115917717737f, 11.1187139401529f, 11.0873969606168f, 11.0667794924678f, 11.0355838523984f, 11.0107298415034f, 10.9796516432030f, 10.9630980289917f, 10.9420391333514f, 10.9144740761416f, 10.8934689087169f, 10.8708578658852f, 10.8533772904939f, 10.8325917807584f, 10.8084481007036f, 10.7910279996611f, 10.7720483888874f, 10.7547079194992f, 10.7374196414357f, 10.7165315149605f, 10.6992241376899f, 10.6906704210781f, 10.6696884648005f, 10.6557033369952f, 10.6417418339839f, 10.6206945653294f, 10.6123225679390f, 10.598410 ...` (scope `vraudio`) — Mapping between reverberation times at a given frequency and the corresponding magnitude compensation value required in the specral reverb to achieve 1.0 magnitude for any decay rate when combined with the convolution compensator. This table covers reverberation times between kMinReverbTimeForFeedback and kNumFeedbackValues * kTimeStepSizeForFeedback, i.e. 0.15s and 25s @48kHz.
- L1567 _variable_ `static const float kCurveCorrectionMultipliers[kNumFeedbackValues] = { 0.000249027612622225f, 0.0475827382701585f, 0.0982856973675534f, 0.144077780284872f, 0.187710331328442f, 0.229214552437128f, 0.268761703298196f, 0.306384317687497f, 0.342116205684862f, 0.376122154314109f, 0.408019265118341f, 0.438826303187204f, 0.468213758592444f, 0.496269855121223f, 0.523103160344453f, 0.548734562484123f, 0.573191744554386f, 0.596776538466997f, 0.619556090502133f, 0.646894092669191f, 0.661870435136273f, 0.675494733319630f, 0.701821797958321f, 0.713358543560036f, 0.731743894313465f, 0.749694785147017f, 0.758967096040535f, 0.775801399270244f, 0.792218438223182f, 0.808206900102085f, 0.815142557606016f, 0.830420164791760f, 0.845380788487056f, 0.859865023229817f, 0.865296767216337f, 0.879331838452952f, 0.893145291831122f, 0.897272345317607f, 0.910373690471610f, 0.923470208927849f, 0.936268613920194f, 0.940724814169454f, 0.943721434222406f, 0.956465808252697f, 0.959628673835810f, 0.971718784707243f, 0.974554123797995f, 0.977943937294408f, 0.997154666216203f, 0.999999999999996f, 0.00847079214371323f, 0.0104396896429595f, 0.0383165227008017f, 0.0405943838116957f, 0.0685361482242258f, 0.0701917817593536f, 0.0713216738657547f, 0.0986119509733789f, 0.0995868953874107f, 0.127034424762083f, 0.127777689282131f, 0.128246886910136f, 0.155790763336654f, 0.156203946276228f, 0.183007628720406f, 0.182664049029335f, 0.182636700276451f, 0.209980982953741f, 0.209930104556972f, 0.209208261790760f, 0.236016550641 ...` (scope `vraudio`) — Set of scalers, one per reverberation time, by which the |kHighCorrectionCurve| and |kLowCorrectionCurve| curves are multiplied in order to generate the correct onset compensation curves.
- L2402 _variable_ `static const float kHighCorrectionCurve[kCorrectionCurveLength] = { 0.00905424704513036f, 0.00926599025691877f, 0.00947778313262726f, 0.00968962562016418f, 0.00990151766744984f, 0.0101134592224174f, 0.0103254502330116f, 0.0105374906471899f, 0.0107495804129221f, 0.0109617194781898f, 0.0111739077909878f, 0.0113861452993219f, 0.0115984319512115f, 0.0118107676946871f, 0.0120231524777923f, 0.0122355862485828f, 0.0124480689551263f, 0.0126606005455030f, 0.0128731809678055f, 0.0130858101701389f, 0.0132984881006193f, 0.0135112147073766f, 0.0137239899385524f, 0.0139368137423006f, 0.0141496860667869f, 0.0143626068601902f, 0.0145755760707011f, 0.0147885936465225f, 0.0150016595358697f, 0.0152147736869704f, 0.0154279360480643f, 0.0156411465674036f, 0.0158544051932527f, 0.0160677118738880f, 0.0162810665575990f, 0.0164944691926864f, 0.0167079197274641f, 0.0169214181102577f, 0.0171349642894055f, 0.0173485582132578f, 0.0175621998301772f, 0.0177758890885386f, 0.0179896259367293f, 0.0182034103231487f, 0.0184172421962087f, 0.0186311215043333f, 0.0188450481959587f, 0.0190590222195339f, 0.0192730435235194f, 0.0194871120563886f, 0.0197012277666270f, 0.0199153906027323f, 0.0201296005132146f, 0.0203438574465959f, 0.0205581613514112f, 0.0207725121762073f, 0.0209869098695431f, 0.0212013543799902f, 0.0214158456561324f, 0.0216303836465656f, 0.0218449682998980f, 0.0220595995647505f, 0.0222742773897556f, 0.0224890017235585f, 0.0227037725148169f, 0.0229185897122002f, 0.0231334532643903f, 0.0233483631200817f, ...` (scope `vraudio`) — Curve which is scaled by |kCurveCorrectionMultipliers| and added to the curve generated by the |kHighReverberationCorrectionCurve| polynomial, for reverberation times which result in a feedback factor index greater than |kCurveChangeoverIndex|.
- L4456 _variable_ `static const float kLowCorrectionCurve[kCorrectionCurveLength] = { 0.0355835132858260f, 0.0361471820669677f, 0.0367104001412021f, 0.0372731677107544f, 0.0378354849778072f, 0.0383973521445001f, 0.0389587694129315f, 0.0395197369851564f, 0.0400802550631881f, 0.0406403238489973f, 0.0411999435445122f, 0.0417591143516188f, 0.0423178364721608f, 0.0428761101079397f, 0.0434339354607135f, 0.0439913127321995f, 0.0445482421240714f, 0.0451047238379613f, 0.0456607580754581f, 0.0462163450381097f, 0.0467714849274197f, 0.0473261779448504f, 0.0478804242918223f, 0.0484342241697123f, 0.0489875777798562f, 0.0495404853235463f, 0.0500929470020328f, 0.0506449630165243f, 0.0511965335681860f, 0.0517476588581411f, 0.0522983390874708f, 0.0528485744572133f, 0.0533983651683647f, 0.0539477114218787f, 0.0544966134186670f, 0.0550450713595981f, 0.0555930854454990f, 0.0561406558771536f, 0.0566877828553037f, 0.0572344665806487f, 0.0577807072538459f, 0.0583265050755101f, 0.0588718602462131f, 0.0594167729664848f, 0.0599612434368130f, 0.0605052718576424f, 0.0610488584293762f, 0.0615920033523746f, 0.0621347068269552f, 0.0626769690533939f, 0.0632187902319240f, 0.0637601705627360f, 0.0643011102459783f, 0.0648416094817569f, 0.0653816684701354f, 0.0659212874111350f, 0.0664604665047346f, 0.0669992059508706f, 0.0675375059494370f, 0.0680753667002852f, 0.0686127884032250f, 0.0691497712580228f, 0.0696863154644029f, 0.0702224212220476f, 0.0707580887305970f, 0.0712933181896472f, 0.0718281097987538f, 0.0723624637574293f, 0.072 ...` (scope `vraudio`) — Curve which is scaled by |kCurveCorrectionMultipliers| and added to the curve generated by the |kLowReverberationCorrectionCurve| polynomial, for reverberation times which result in a feedback factor index less than |kCurveChangeoverIndex|.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/stereo_panner.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_STEREO_PANNER_H_`
- L24 _namespace_ `namespace vraudio`
- L30 _prototype_ `void CalculateStereoPanGains(const SphericalAngle& source_direction, std::vector<float>* stereo_gains);` (scope `vraudio`) — Computes a pair of stereo panner gains based on the |source_direction|. @param source_direction Azimuth and elevation of the sound source. @param stereo_gains A pointer to vector of stereo loudspeaker gains.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/dsp/utils.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_DSP_UTILS_H_`
- L22 _namespace_ `namespace vraudio`
- L30 _prototype_ `void GenerateGaussianNoise(float mean, float std_deviation, unsigned seed, AudioBuffer::Channel* noise_channel);` (scope `vraudio`) — Generates a gaussian white noise signal. @param mean The mean distribution parameter. @param std_deviation The standard deviation distribution parameter. @param seed A seed for the random generator. @param noise_channel Buffer channel in which to store the noise.
- L39 _prototype_ `void GenerateUniformNoise(float min, float max, unsigned seed, AudioBuffer::Channel* noise_channel);` (scope `vraudio`) — Generates  a gaussian white noise signal. @param min The lowest value in the distribution. @param max The highest value in te distribution, must be > min. @param seed A seed for the random generator. @param noise_channel Buffer channel in which to store the noise.
- L48 _prototype_ `void GenerateBandLimitedGaussianNoise(float center_frequency, int sampling_rate, unsigned seed, AudioBuffer* noise_buffer);` (scope `vraudio`) — Generates a band limited gaussian white noise signal, one octave band wide. @param center_frequency Center frequency of the given octave band in Hz. @param sampling_rate System sampling rate in Hz. @param seed A seed for the random generator. @param noise_buffer Buffer in which to store the band limited noise.
- L56 _prototype_ `std::unique_ptr<AudioBuffer> GenerateDecorrelationFilters(int sampling_rate);` (scope `vraudio`) — Genarates a pair of decorrelation filters (for use in low quality/high effiency mode reverb). @param sampling_rate System sampling rate in Hz. @return Buffer containing the stereo filters.
- L62 _prototype_ `size_t GetNumReverbOctaveBands(int sampling_rate);` (scope `vraudio`) — Returns the number of octave bands necessary for the given |sampling_rate|. @param sampling_rate Sampling rate in Hertz. @return Number of reverb octave bands.
- L71 _prototype_ `size_t GetNumSamplesFromMilliseconds(float milliseconds, int sampling_rate);` (scope `vraudio`) — Converts the given |milliseconds| to number of samples with the given |sampling_rate|. This method should *not* be used when more precise (double-precission) value is desired. @param milliseconds Milliseconds in single-precission floating point. @param sampling_rate Sampling rate in Hertz. @return Number of samples.
- L78 _prototype_ `size_t CeilToMultipleOfFramesPerBuffer(size_t size, size_t frames_per_buffer);` (scope `vraudio`) — Ceils the given |size| to the next multiple of given |frames_per_buffer|. @param size Input size in frames. @param frames_per_buffer Frames per buffer. @return Ceiled size in frames.
- L88 _prototype_ `void GenerateHannWindow(bool full_window, size_t window_length, AudioBuffer::Channel* buffer);` (scope `vraudio`) — Generates a Hann window (used for smooth onset and tapering of the generated reverb response tails). @param full_window True to generate a full window, false to generate a half. @param window_length Length of the window to be generated. Must be less than or equal to the number of frames in the |buffer|. @param buffer AudioBuffer::Channel to which the window is written, the number of frames will be the length in samples of the generated Hann window.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/ambisonic_binaural_decoder_node.h` (Private)


#### class `vraudio::AmbisonicBinauralDecoderNode`  
`class AmbisonicBinauralDecoderNode : public ProcessingNode`  
_L35-84_
- inherits: `ProcessingNode`
- desc: Node that takes an ambisonic soundfield as input and renders a binaural stereo buffer as output.
- L44 _public prototype_ `AmbisonicBinauralDecoderNode(const SystemSettings& system_settings, int ambisonic_order, const std::string& sh_hrir_filename, FftManager* fft_manager, Resampler* resampler);` — Initializes AmbisonicBinauralDecoderNode class. @param system_settings Global system configuration. @param ambisonic_order Ambisonic order. @param sh_hrir_filename Filename to load the HRIR data from. @param fft_manager Pointer to a manager to perform FFT transformations. @resampler Pointer to a resampler used to convert HRIRs to the system rate.
- L53 _protected prototype_ `const AudioBuffer* AudioProcess(const NodeInput& input) override;` — Implements ProcessingNode.
- L56 _private member_ `const SystemSettings& system_settings_;`
- L59 _private member_ `const size_t num_ambisonic_channels_;` — Number of Ambisonic channels.
- L62 _private member_ `bool is_stereo_speaker_mode_;` — Denotes if the stereo speaker mode is enabled.
- L65 _private member_ `std::unique_ptr<AmbisonicBinauralDecoder> ambisonic_binaural_decoder_;` — Ambisonic decoder used to render binaural output.
- L67 _private member_ `size_t num_frames_processed_on_empty_input_;`
- L70 _private member_ `AudioBuffer stereo_output_buffer_;` — Stereo output buffer.
- L73 _private member_ `AudioBuffer silence_input_buffer_;` — Silence mono buffer to render reverb tails.
- L77 _private member_ `BufferCrossfader crossfader_;` — Buffer crossfader to apply linear crossfade when the stereo speaker mode is changed.
- L80 _private member_ `AudioBuffer crossfaded_output_buffer_;` — Stereo output buffer to store the crossfaded decode output when necessary.
- L83 _private member_ `AudioBuffer temp_crossfade_buffer_;` — Temporary crossfade buffer to store the intermediate stereo output.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_AMBISONIC_BINAURAL_DECODER_NODE_H_`
- L31 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/ambisonic_mixing_encoder_node.h` (Private)


#### class `vraudio::AmbisonicMixingEncoderNode`  
`class AmbisonicMixingEncoderNode : public ProcessingNode`  
_L33-67_
- inherits: `ProcessingNode`
- desc: Node that accepts single mono sound object buffer as input and encodes it into an Ambisonic sound field.
- L40 _public prototype_ `AmbisonicMixingEncoderNode(const SystemSettings& system_settings, const AmbisonicLookupTable& lookup_table, int ambisonic_order);` — Initializes AmbisonicMixingEncoderNode class. @param system_settings Global system configuration. @param lookup_table Ambisonic encoding lookup table. @param ambisonic_order Order of Ambisonic sources.
- L45 _public function_ `bool CleanUp() final` — Node implementation.
- L53 _protected prototype_ `const AudioBuffer* AudioProcess(const NodeInput& input) override;` — Implements ProcessingNode.
- L56 _private member_ `const SystemSettings& system_settings_;`
- L57 _private member_ `const AmbisonicLookupTable& lookup_table_;`
- L60 _private member_ `const int ambisonic_order_;` — Ambisonic order of encoded sources.
- L63 _private member_ `GainMixer gain_mixer_;` — |GainMixer| instance.
- L66 _private member_ `std::vector<float> coefficients_;` — Encoding coefficient values to be applied to encode the input.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_AMBISONIC_MIXING_ENCODER_NODE_H_`
- L29 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/binaural_surround_renderer_impl.h` (Private)


#### class `vraudio::BinauralSurroundRendererImpl`  
`class BinauralSurroundRendererImpl : public BinauralSurroundRenderer`  
_L34-186_
- inherits: `BinauralSurroundRenderer`
- desc: Renders virtual surround sound as well as ambisonic soundfields to binaural stereo.
- L40 _public prototype_ `BinauralSurroundRendererImpl(size_t frames_per_buffer, int sample_rate_hz);` — Constructor. @param frames_per_buffer Number of frames in output buffer. @param sample_rate_hz Sample rate of audio buffers.
- L42 _public prototype_ `~BinauralSurroundRendererImpl() override= default;`
- L48 _public prototype_ `bool Init(SurroundFormat surround_format);` — Initializes surround sound decoding. @param surround_format Surround sound input format. @return True on success.
- L51 _public prototype_ `void SetStereoSpeakerMode(bool enabled) override;` — Implements |AudioRenderer| interface.
- L52 _public prototype_ `size_t GetNumAvailableFramesInInputBuffer() const override;`
- L53 _public prototype_ `size_t AddInterleavedInput(const int16* input_buffer_ptr, size_t num_channels, size_t num_frames) override;`
- L55 _public prototype_ `size_t AddInterleavedInput(const float* input_buffer_ptr, size_t num_channels, size_t num_frames) override;`
- L57 _public prototype_ `size_t AddPlanarInput(const int16* const* input_buffer_ptrs, size_t num_channels, size_t num_frames) override;`
- L59 _public prototype_ `size_t AddPlanarInput(const float* const* input_buffer_ptrs, size_t num_channels, size_t num_frames) override;`
- L61 _public prototype_ `size_t GetAvailableFramesInStereoOutputBuffer() const override;`
- L62 _public prototype_ `size_t GetInterleavedStereoOutput(int16* output_buffer_ptr, size_t num_frames) override;`
- L64 _public prototype_ `size_t GetInterleavedStereoOutput(float* output_buffer_ptr, size_t num_frames) override;`
- L66 _public prototype_ `size_t GetPlanarStereoOutput(int16** output_buffer_ptrs, size_t num_frames) override;`
- L68 _public prototype_ `size_t GetPlanarStereoOutput(float** output_buffer_ptrs, size_t num_frames) override;`
- L70 _public prototype_ `bool TriggerProcessing() override;`
- L71 _public prototype_ `void Clear() override;`
- L72 _public prototype_ `void SetHeadRotation(float w, float x, float y, float z) override;`
- L76 _protected prototype_ `BinauralSurroundRendererImpl();` — Protected default constructor for mock tests.
- L84 _private prototype_ `AudioBuffer* BufferPartitionerCallback(AudioBuffer* processed_buffer);` — Callback triggered by |buffer_partitioner_| whenever a new |AudioBuffer| has been generated. @param processed_buffer Pointer to processed buffer. @return Pointer to next |AudioBuffer| to be filled up.
- L95 _private prototype_ `template <typename BufferType> size_t AddInputBufferTemplated(const BufferType input_buffer_ptr, size_t num_channels, size_t num_frames);` — Helper method to implement |AddInterleavedInput| independently from the sample type. @tparam BufferType Input buffer type. @param input_buffer_ptr Pointer to interleaved input data. @param num_channels Number of channels in input buffer. @param num_frames Number of frames in input buffer. @return The number of consumed samples.
- L106 _private prototype_ `template <typename BufferType> size_t GetStereoOutputBufferTemplated(BufferType output_buffer_ptr, size_t num_frames);` — Helper method to implement |GetInterleavedOutput| independently from the sample type. @tparam BufferType Output buffer type. @param output_buffer_ptr Pointer to allocated interleaved output buffer. @param num_frames Size of output buffer in frames. @return The number of consumed frames.
- L114 _private prototype_ `static size_t GetExpectedNumChannelsFromSurroundFormat( SurroundFormat surround_format);` — Helper method to obtain the expected number of audio channels for a given surround format. @param surround_format Surround format query. @return Number of audio channels.
- L118 _private prototype_ `AudioBuffer* ProcessBuffer();` — Process method executed by |buffer_unpartitioner_|.
- L121 _private prototype_ `void InitializeBinauralMono();` — Initializes binaural mono rendering.
- L124 _private prototype_ `void InitializeBinauralStereo();` — Initializes binaural stereo rendering.
- L127 _private prototype_ `void InitializeBinauralSurround5dot1();` — Initializes binaural 5.1 rendering.
- L130 _private prototype_ `void InitializeBinauralSurround7dot1();` — Initializes binaural 7.1 rendering.
- L133 _private prototype_ `void InitializeAmbisonics();` — Initializes binaural ambisonic rendering.
- L136 _private prototype_ `void InitializeAmbisonicsWithNonDiegeticStereo();` — Initializes binaural ambisonic rendering with non-diegetic stereo.
- L139 _private prototype_ `SourceId CreateSoundObject(float azimuth_deg);` — Creates a sound object at given angle within the horizontal listener plane.
- L142 _private prototype_ `void InitializeRoomReverb();` — Initializes room reverb for virtual surround sound rendering.
- L145 _private member_ `std::unique_ptr<ResonanceAudioApi> resonance_audio_api_;` — ResonanceAudioApi instance.
- L148 _private member_ `const size_t frames_per_buffer_;` — Frames per buffer.
- L151 _private member_ `const int sample_rate_hz_;` — System sample rate.
- L154 _private member_ `SurroundFormat surround_format_;` — Selected surround sound format.
- L157 _private member_ `size_t num_input_channels_;` — Number of input channels.
- L160 _private member_ `std::unique_ptr<BufferPartitioner> buffer_partitioner_;` — Partitions input buffers into |AudioBuffer|s.
- L163 _private member_ `std::unique_ptr<ThreadsafeFifo<AudioBuffer>> input_audio_buffer_queue_;` — Buffer queue containing partitioned input |AudioBuffer|s.
- L166 _private member_ `AudioBuffer output_buffer_;` — Binaural stereo output buffer.
- L169 _private member_ `std::unique_ptr<BufferUnpartitioner> buffer_unpartitioner_;` — Unpartitions processed |AudioBuffer|s into interleaved output buffers.
- L172 _private member_ `std::vector<SourceId> source_ids_;` — Vector containing the source ids of all rendered sound sources.
- L175 _private member_ `size_t total_frames_buffered_;` — Total number of frames currently buffered.
- L178 _private member_ `size_t num_zero_padded_frames_;` — Total number of zero padded frames from |TriggerProcessing| calls.
- L181 _private member_ `std::vector<const float*> temp_planar_buffer_ptrs_;` — Temporary buffer to store pointers to planar ambisonic and stereo channels.
- L185 _private member_ `float output_gain_;` — Global output gain adjustment, to avoid clipping of individual channels in virtual speaker modes.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_BINAURAL_SURROUND_RENDERER_IMPL_H_`
- L30 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/buffered_source_node.h` (Private)


#### class `vraudio::BufferedSourceNode`  
`class BufferedSourceNode : public SourceNode`  
_L29-58_
- inherits: `SourceNode`
- desc: Node that sets the |AudioBuffer| of a source. This class is *not* thread-safe and calls to this class must be synchronized with the graph processing.
- L35 _public prototype_ `BufferedSourceNode(SourceId source_id, size_t num_channels, size_t frames_per_buffer);` — Constructor. @param source_id Source id. @param num_channel Number of channels in output buffers.
- L43 _public prototype_ `AudioBuffer* GetMutableAudioBufferAndSetNewBufferFlag();` — Returns a mutable pointer to the internal |AudioBuffer| and sets a flag to process the buffer in the next graph processing iteration. Calls to this method must be synchronized with the audio graph processing. @return Mutable audio buffer pointer.
- L47 _protected prototype_ `const AudioBuffer* AudioProcess() override;` — Implements SourceNode.
- L50 _protected member_ `const SourceId source_id_;` — Source id.
- L53 _protected member_ `AudioBuffer input_audio_buffer_;` — Input audio buffer.
- L57 _protected member_ `bool new_buffer_flag_;` — Flag indicating if an new audio buffer has been set via |GetMutableAudioBufferAndSetNewBufferFlag|.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_BUFFERED_SOURCE_NODE_H_`
- L24 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/foa_rotator_node.h` (Private)


#### class `vraudio::FoaRotatorNode`  
`class FoaRotatorNode : public ProcessingNode`  
_L33-50_
- inherits: `ProcessingNode`
- desc: Node that accepts a single first order PeriphonicSoundfieldBuffer as input and outputs a rotated PeriphonicSoundfieldBuffer of the corresponding soundfield input using head rotation information from the system settings.
- L35 _public prototype_ `FoaRotatorNode(SourceId source_id, const SystemSettings& system_settings);`
- L40 _protected prototype_ `const AudioBuffer* AudioProcess(const NodeInput& input) override;` — Implements ProcessingNode. Returns a null pointer if we are in stereo loudspeaker or stereo pan mode.
- L43 _private member_ `const SystemSettings& system_settings_;`
- L46 _private member_ `FoaRotator foa_rotator_;` — Soundfield rotator used to rotate first order soundfields.
- L49 _private member_ `AudioBuffer output_buffer_;` — Output buffer.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_FOA_ROTATOR_NODE_H_`
- L28 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/gain_mixer_node.h` (Private)


#### class `vraudio::GainMixerNode`  
`class GainMixerNode : public ProcessingNode`  
_L31-64_
- inherits: `ProcessingNode`
- desc: Node that accepts multiple input buffers, calculates and applies a gain value to each buffer based upon the given |AttenuationType| and then mixes the results together.
- L38 _public prototype_ `GainMixerNode(const AttenuationType& attenuation_type, const SystemSettings& system_settings, size_t num_channels);` — Constructs |GainMixerNode| with given gain calculation method. @param attenuation_type Gain attenuation type to be used. @param system_settings Global system settings. @param num_channels Number of channels.
- L43 _public prototype_ `void SetMute(bool mute_enabled);` — Mute the mixer node by skipping the audio processing and outputting nullptr buffers.
- L46 _public prototype_ `bool CleanUp() final;` — Node implementation.
- L50 _protected prototype_ `const AudioBuffer* AudioProcess(const NodeInput& input) override;` — Implements ProcessingNode.
- L54 _private member_ `bool mute_enabled_;` — Flag indicating the mute status.
- L57 _private member_ `const AttenuationType attenuation_type_;` — Gain attenuation type.
- L60 _private member_ `GainMixer gain_mixer_;` — Gain mixer.
- L63 _private member_ `const SystemSettings& system_settings_;` — Global system settings.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_GAIN_MIXER_NODE_H_`
- L26 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/gain_node.h` (Private)


#### class `vraudio::GainNode`  
`class GainNode : public ProcessingNode`  
_L34-65_
- inherits: `ProcessingNode`
- desc: Node that calculates and applies a gain value to each channel of an input buffer based upon the given |GainCalculator|.
- L42 _public prototype_ `GainNode(SourceId source_id, size_t num_channels, const AttenuationType& attenuation_type, const SystemSettings& system_settings);` — Constructs |GainNode| with given gain attenuation method. @param source_id Output buffer source id. @param num_channels Number of channels in the input buffer. @param attenuation_type Gain attenuation type to be used. @param system_settings Global system settings.
- L48 _protected prototype_ `const AudioBuffer* AudioProcess(const NodeInput& input) override;` — Implements ProcessingNode.
- L52 _private member_ `const size_t num_channels_;` — Number of channels of the audio buffer.
- L55 _private member_ `const AttenuationType attenuation_type_;` — Gain attenuation type.
- L58 _private member_ `std::vector<GainProcessor> gain_processors_;` — Gain processors per each channel.
- L61 _private member_ `const SystemSettings& system_settings_;` — Global system settings.
- L64 _private member_ `AudioBuffer output_buffer_;` — Output buffer.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_GAIN_NODE_H_`
- L30 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/graph_manager.h` (Private)


#### class `vraudio::GraphManager`  
`class GraphManager`  
_L46-391_
- desc: The GraphManager class manages the construction and lifetime of the audio processing graph. It owns the output node that connects the audio processing graph to the audio hardware.
- L51 _public prototype_ `explicit GraphManager(const SystemSettings& system_settings);` — Initializes GraphManager class. @param system_settings Global system configuration.
- L56 _public prototype_ `std::shared_ptr<SinkNode> GetSinkNode();` — Returns the sink node the audio graph is connected to. @return Shared pointer of the sink node.
- L59 _public prototype_ `void Process();` — Triggers processing of the audio graph for all the connected nodes.
- L67 _public prototype_ `AudioBuffer* GetMutableAudioBuffer(SourceId source_id);` — Returns a mutable pointer to the |AudioBuffer| of an audio source with given |source_id|. Calls to this method must be synchronized with the audio graph processing. @param source_id Source id. @return Mutable audio buffer pointer. Nullptr if source_id not found.
- L94 _public prototype_ `void CreateAmbisonicPannerSource(SourceId sound_object_source_id, bool enable_hrtf);` — Creates an ambisonic panner source with given |sound_object_source_id|. Processing graph: +-------------------+ |                   | +------------+ SoundObjectSource +----------+ |            |                   |          | |            +---------+---------+          | |                                           | +-----------v-----------+                     +---------v----------+ |                       |                     |                    | | AmbisonicMixingPanner |                     | StereoMixingPanner | |                       |                     |                    | +-----------+-----------+                     +---------+----------+ |                                           | +-----------v-----------+                     +---------v----------+ |                       |                     |                    | |    AmbisonicMixer     |                     |    StereoMixer     | |                       |                     |                    | +-----------+-----------+                     +--------------------+ @param sound_object_source_id Id of sound object source. @param enable_hrtf Flag to enable HRTF-based spatialization.
- L120 _public prototype_ `void CreateStereoSource(SourceId stereo_source_id);` — Creates a new stereo non-spatialized source with given |stereo_source_id|. Processing graph: +--------------+ |              | | StereoSource | |              | +-------+------+ | +-------v------+ |              | |     Gain     | |              | +-------+------+ | +-------V------+ |              | | StereoMixer  | |              | +--------------+ @param stereo_source_id Id of new stereo source.
- L128 _public prototype_ `void DestroySource(SourceId source_id);` — Destroys source with given |source_id|. Note that this call only sets a flag to indicate that this source can be removed. The actual disconnect happens from the audio processing thread the next time the processing graph is triggered. @param source_id Id of source to be destroyed.
- L163 _public prototype_ `void CreateAmbisonicSource(SourceId ambisonic_source_id, size_t num_channels);` — Creates a new ambisonic source subgraph with given |ambisonic_source_id|. Note: Ambisonic source subgraph is only created if the rendering mode is HRTF. Processing graph (all the graphs created using http://asciiflow.com/): +-----------------+ |                 | +-------+ AmbisonicSource +-------+ |       |                 |       | |       +-----------------+       | |                                 | +----v---+                  +----------v---------+ |        |                  |                    | |  Gain  |               +--+ MonoFromSoundfield +--+ |        |               |  |                    |  | +----+---+               |  +--------------------+  | |                   |                          | |                   |                          | +--------v-------+  +--------v---------+         +------v------+ |                |  |                  |         |             | | Foa/HoaRotator |  | ReflectionsMixer |         | ReverbMixer | |                |  |                  |         |             | +--------+-------+  +--------+---------+         +------+------+ | +--------v-------+ |                | | AmbisonicMixer | |                | +--------+-------+ @param ambisonic_source_id Id of new ambisonic source. @param num_channels Number of input channels of ambisonic source node.
- L204 _public prototype_ `void CreateSoundObjectSource(SourceId sound_object_source_id, int ambisonic_order, bool enable_hrtf, bool enable_direct_rendering);` — Creates a new sound object source with given |sound_object_source_id|. Processing graph: +-------------------+ |                   | +-------------+ SoundObjectSource +----------+ |             |                   |          | |             +---------+---------+          | |                       |                    | +----------v-----------+ +---------v---------+ +--------v--------+ |                      | |                   | |                 | | ReflectionsGainMixer | | DirectAttenuation | | ReverbGainMixer | |                      | |                   | |                 | +----------+-----------+ +---------+---------+ +--------+--------+ | +---------v---------+ HRTF    |                   |    Stereo Panning +------------+     Occlusion     +----------+ |            |                   |          | |            +---------+---------+          | |                      |                    | +-----------v-----------+ +--------v--------+ +---------v----------+ |                       | |                 | |                    | | AmbisonicMixingPanner | | NearFieldEffect | | StereoMixingPanner | |                       | |                 | |                    | +-----------+-----------+ +--------+--------+ +---------+----------+ |                      |                    | +-----------v-----------+ +--------v--------+           | |                       | |                 |           | |    AmbisonicMixer     | |   StereoMixer   <-----------+ |                      
- L211 _public prototype_ `void EnableRoomEffects(bool enable);` — Mutes on/off the room effects mixers. @param Whether to enable room effects.
- L220 _public prototype_ `const AudioBuffer* GetAmbisonicBuffer() const;` — Returns the last processed output audio buffer of the ambisonic mix with the highest possible ambisonic channel configuration. Note that, this method will *not* trigger the processing of the audio graph. |GraphManager::Process| must be called prior to this method call to ensure that the output buffer is up-to-date. @return Output audio buffer of the ambisonic mix, or nullptr if no output.
- L228 _public prototype_ `const AudioBuffer* GetStereoBuffer() const;` — Returns the last processed output audio buffer of the stereo (binaural) mix. Note that, this method will *not* trigger the processing of the audio graph. |GraphManager::Process| must be called prior to this method call to ensure that the output buffer is up-to-date. @return Output audio buffer of the stereo mix, or nullptr if no output.
- L233 _public prototype_ `size_t GetNumMaxAmbisonicChannels() const;` — Returns the maximum allowed number of ambisonic channels. @return Number of channels based on Ambisonic order in the global config.
- L238 _public prototype_ `bool GetRoomEffectsEnabled() const;` — Returns whether the room effects graph is enabled. @return True if room effects are enabled.
- L242 _public prototype_ `void UpdateRoomReflections();` — Updates the room reflections with the current properties for room effects processing.
- L245 _public prototype_ `void UpdateRoomReverb();` — Updates the room reverb.
- L275 _private prototype_ `void InitializeAmbisonicRendererGraph(int ambisonic_order, const std::string& sh_hrir_filename);` — Initializes the Ambisonic renderer subgraph for the speficied Ambisonic order and connects it to the |StereoMixerNode|. Processing graph: +------------------+ |                  | |  AmbisonicMixer  | |                  | +--------+---------+ | | +------------v-------------+ |                          | | AmbisonicBinauralDecoder | |                          | +------------+-------------+ | | +-----------v------------+ |                        | |      StereoMixer       | |                        | +------------------------+ @param ambisonic_order Ambisonic order. @param sh_hrir_filename Filename to load the HRIR data from.
- L282 _private prototype_ `std::shared_ptr<BufferedSourceNode> LookupSourceNode(SourceId source_id);` — Helper method to lookup a source node with given |source_id|. @param source_id Source id. @returns Shared pointer to source node instance, nullptr if not found.
- L307 _private prototype_ `void InitializeReflectionsGraph();` — Creates an audio subgraph that renders early reflections based on a room model on a single mix. Processing graph: +---------------------------+ |                           | |    ReflectionsGainMixer   | |                           | +-------------+-------------+ | +----------v----------+ |                     | |     Reflections     | |                     | +----------+----------+ | +----------v----------+ |                     | |   AmbisonicMixer    | |                     | +----------+----------+
- L332 _private prototype_ `void InitializeReverbGraph();` — Creates an audio subgraph that renders a reverb from a mono mix of all the sound objects based on a room model. Processing graph: +-----------------+ |                 | | ReverbGainMixer | |                 | +--------+--------+ | +--------v--------+ |                 | |     Reverb      | |                 | +--------+--------+ | +--------v--------+ |                 | |   StereoMixer   | |                 | +-----------------+
- L335 _private member_ `bool room_effects_enabled_;` — Flag indicating if room effects are enabled.
- L338 _private member_ `std::shared_ptr<GainMixerNode> reverb_gain_mixer_node_;` — Mono mixer to accumulate all reverb sources.
- L341 _private member_ `std::shared_ptr<ReflectionsNode> reflections_node_;` — Reflections node.
- L344 _private member_ `std::shared_ptr<GainMixerNode> reflections_gain_mixer_node_;` — Mono mixer node to accumulate the early reflection sources.
- L347 _private member_ `std::shared_ptr<ReverbNode> reverb_node_;` — Reverb node.
- L351 _private member_ `std::unique_ptr<Mixer> ambisonic_output_mixer_;` — Ambisonic output mixer to accumulate incoming ambisonic inputs into a single ambisonic output buffer.
- L354 _private member_ `const GraphManagerConfig config_;` — Global config passed in during construction.
- L357 _private member_ `const SystemSettings& system_settings_;` — Manages system wide settings.
- L360 _private member_ `std::unique_ptr<AmbisonicLookupTable> lookup_table_;` — Provides Ambisonic encoding coefficients.
- L363 _private member_ `FftManager fft_manager_;` — |FftManager| to be used in nodes that require FFT transformations.
- L366 _private member_ `Resampler resampler_;` — |Resampler| to be used to convert HRIRs to the system sample rate.
- L370 _private member_ `std::unordered_map<int, std::shared_ptr<MixerNode>> ambisonic_mixer_nodes_;` — Ambisonic mixer nodes per each ambisonic order to accumulate the ambisonic sources for the corresponding binaural Ambisonic decoders.
- L373 _private member_ `std::shared_ptr<MixerNode> stereo_mixer_node_;` — Stereo mixer to combine all the stereo and binaural output.
- L378 _private member_ `ambisonic_mixing_encoder_nodes_;`
- L382 _private member_ `std::shared_ptr<StereoMixingPannerNode> stereo_mixing_panner_node_;` — Stereo mixing panner node to apply stereo panning gains and accumulate the buffers.
- L385 _private member_ `std::shared_ptr<SinkNode> output_node_;` — Output node that enables audio playback of a single audio stream.
- L390 _private member_ `source_nodes_;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_GRAPH_MANAGER_H_`
- L41 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/graph_manager_config.h` (Private)


#### struct `vraudio::GraphManagerConfig`  
`struct GraphManagerConfig`  
_L27-36_
- desc: Configuration of the GraphManager and the nodes it is instantiating.
- L29 _public member_ `std::string configuration_name;` — Configuration name.
- L32 _public member_ `int max_ambisonic_order = 1;` — Maximum ambisonic order allowed.
- L35 _public member_ `std::vector<std::pair<int, std::string>> sh_hrir_filenames = {};` — HRIR filenames (second element) per ambisonic order (first element).

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_GRAPH_MANAGER_CONFIG_H_`
- L24 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/hoa_rotator_node.h` (Private)


#### class `vraudio::HoaRotatorNode`  
`class HoaRotatorNode : public ProcessingNode`  
_L33-51_
- inherits: `ProcessingNode`
- desc: Node that accepts a single PeriphonicSoundfieldBuffer as input and outputs a rotated PeriphonicSoundfieldBuffer of the corresponding soundfield input using head rotation information from the system settings.
- L35 _public prototype_ `HoaRotatorNode(SourceId source_id, const SystemSettings& system_settings, int ambisonic_order);`
- L41 _protected prototype_ `const AudioBuffer* AudioProcess(const NodeInput& input) override;` — Implements ProcessingNode. Returns a null pointer if we are in stereo loudspeaker or stereo pan mode.
- L44 _private member_ `const SystemSettings& system_settings_;`
- L47 _private member_ `HoaRotator hoa_rotator_;` — Soundfield rotator used to rotate higher order soundfields.
- L50 _private member_ `AudioBuffer output_buffer_;` — Output buffer.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_HOA_ROTATOR_NODE_H_`
- L28 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/mixer_node.h` (Private)


#### class `vraudio::MixerNode`  
`class MixerNode : public ProcessingNode`  
_L30-50_
- inherits: `ProcessingNode`
- desc: Accepts multiple input buffers and outputs a downmix to a single output buffer. All input buffers must have the same number of channels and the same number of frames per buffer.
- L32 _public prototype_ `MixerNode(const SystemSettings& system_settings, size_t num_channels);`
- L37 _public prototype_ `const AudioBuffer* GetOutputBuffer() const;` — Returns the current output buffer of the mixer. @return Output audio buffer.
- L40 _public prototype_ `bool CleanUp() final;` — Node implementation.
- L44 _protected prototype_ `const AudioBuffer* AudioProcess(const NodeInput& input) override;` — Implements ProcessingNode.
- L47 _private member_ `const size_t num_channels_;`
- L49 _private member_ `Mixer mixer_;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_MIXER_NODE_H_`
- L25 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/mono_from_soundfield_node.h` (Private)


#### class `vraudio::MonoFromSoundfieldNode`  
`class MonoFromSoundfieldNode : public ProcessingNode`  
_L28-40_
- inherits: `ProcessingNode`
- desc: Node that accepts an ambisonic buffer as input and extracts its W channel onto a mono output buffer.
- L30 _public prototype_ `MonoFromSoundfieldNode(SourceId source_id, const SystemSettings& system_settings);`
- L35 _protected prototype_ `const AudioBuffer* AudioProcess(const NodeInput& input) override;` — Implements |ProcessingNode|.
- L39 _private member_ `AudioBuffer output_buffer_;` — Mono audio buffer to store output data.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_MONO_FROM_SOUNDFIELD_NODE_H_`
- L24 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/near_field_effect_node.h` (Private)


#### class `vraudio::NearFieldEffectNode`  
`class NearFieldEffectNode : public ProcessingNode`  
_L35-65_
- inherits: `ProcessingNode`
- desc: Node that accepts a single mono audio buffer as input, applies an appoximate near field effect and outputs a processed stereo audio buffer. The stereo output buffer can then be combined with a binaural output in order to simulate a sound source which is close (<1m) to the listener's head.
- L41 _public prototype_ `NearFieldEffectNode(SourceId source_id, const SystemSettings& system_settings);` — Constructor. @param source_id Output buffer source id. @param system_settings Global system settings.
- L46 _protected prototype_ `const AudioBuffer* AudioProcess(const NodeInput& input) override;` — Implements ProcessingNode.
- L50 _private member_ `GainProcessor left_panner_;` — Left and right processors apply both near field gain and panner gains.
- L51 _private member_ `GainProcessor right_panner_;`
- L54 _private member_ `std::vector<float> pan_gains_;` — Left and right gains for near field and panning combined.
- L58 _private member_ `NearFieldProcessor near_field_processor_;` — Near field processor used to apply approximate near field effect to the mono source signal.
- L61 _private member_ `const SystemSettings& system_settings_;` — Used to obtain head rotation.
- L64 _private member_ `AudioBuffer output_buffer_;` — Output buffer.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_NEAR_FIELD_EFFECT_NODE_H_`
- L29 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/occlusion_node.h` (Private)


#### class `vraudio::OcclusionNode`  
`class OcclusionNode : public ProcessingNode`  
_L30-55_
- inherits: `ProcessingNode`
- desc: Node that accepts a single audio buffer as input and outputs the input buffer with its cuttoff frequency scaled by listener/source directivity and occlusion intensity.
- L36 _public prototype_ `OcclusionNode(SourceId source_id, const SystemSettings& system_settings);` — Constructor. @param source_id Output buffer source id. @param system_settings Global system settings.
- L40 _protected prototype_ `const AudioBuffer* AudioProcess(const NodeInput& input) override;` — Implements ProcessingNode.
- L45 _private member_ `const SystemSettings& system_settings_;`
- L48 _private member_ `MonoPoleFilter low_pass_filter_;` — Used to low-pass input audio when a source is occluded or self-occluded.
- L51 _private member_ `float current_occlusion_;` — Occlusion intensity value for the current input buffer.
- L54 _private member_ `AudioBuffer output_buffer_;` — Output buffer.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_OCCLUSION_NODE_H_`
- L25 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/reflections_node.h` (Private)


#### class `vraudio::ReflectionsNode`  
`class ReflectionsNode : public ProcessingNode`  
_L34-74_
- inherits: `ProcessingNode`
- desc: Node that accepts a single mono buffer as input and outputs an ambisonically encoded sound field buffer of the mix of all the early room reflections.
- L39 _public prototype_ `explicit ReflectionsNode(const SystemSettings& system_settings);` — Initializes |ReflectionsNode| class. @param system_settings Global system configuration.
- L44 _public prototype_ `void Update();` — Updates the reflections. Depending on whether to use RT60s for reverb according to the global system settings, the reflections are calculated either by the current room properties or the proxy room properties.
- L48 _protected prototype_ `const AudioBuffer* AudioProcess(const NodeInput& input) override;` — Implements ProcessingNode.
- L51 _private member_ `const SystemSettings& system_settings_;`
- L55 _private member_ `FoaRotator foa_rotator_;` — First-order-ambisonics rotator to be used to rotate the reflections with respect to the listener's orientation.
- L58 _private member_ `ReflectionsProcessor reflections_processor_;` — Processes and encodes reflections into an ambisonic buffer.
- L61 _private member_ `ReflectionProperties reflection_properties_;` — Most recently updated reflection properties.
- L64 _private member_ `WorldPosition listener_position_;` — Most recently updated listener position.
- L66 _private member_ `size_t num_frames_processed_on_empty_input_;`
- L69 _private member_ `AudioBuffer output_buffer_;` — Ambisonic output buffer.
- L73 _private member_ `AudioBuffer silence_mono_buffer_;` — Silence mono buffer to render reflection tails during the absence of input buffers.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_REFLECTIONS_NODE_H_`
- L30 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/resonance_audio_api_impl.h` (Private)


#### class `vraudio::ResonanceAudioApiImpl`  
`class ResonanceAudioApiImpl : public ResonanceAudioApi`  
_L34-166_
- inherits: `ResonanceAudioApi`
- desc: Implementation of ResonanceAudioApi interface.
- L41 _public prototype_ `ResonanceAudioApiImpl(size_t num_channels, size_t frames_per_buffer, int sample_rate_hz);` — Constructor that initializes |ResonanceAudioApi| with system configuration. @param num_channels Number of channels of audio output. @param frames_per_buffer Number of frames per buffer. @param sample_rate_hz System sample rate.
- L51 _public prototype_ `bool FillInterleavedOutputBuffer(size_t num_channels, size_t num_frames, float* buffer_ptr) override;` — Obtain processed output buffers.
- L53 _public prototype_ `bool FillInterleavedOutputBuffer(size_t num_channels, size_t num_frames, int16* buffer_ptr) override;`
- L55 _public prototype_ `bool FillPlanarOutputBuffer(size_t num_channels, size_t num_frames, float* const* buffer_ptr) override;`
- L57 _public prototype_ `bool FillPlanarOutputBuffer(size_t num_channels, size_t num_frames, int16* const* buffer_ptr) override;`
- L61 _public prototype_ `void SetHeadPosition(float x, float y, float z) override;` — Listener configuration.
- L62 _public prototype_ `void SetHeadRotation(float x, float y, float z, float w) override;`
- L63 _public prototype_ `void SetPrimaryVolume(float volume) override;`
- L64 _public prototype_ `void SetStereoSpeakerMode(bool enabled) override;`
- L67 _public prototype_ `SourceId CreateAmbisonicSource(size_t num_channels) override;` — Create and destroy sources.
- L68 _public prototype_ `SourceId CreateStereoSource(size_t num_channels) override;`
- L69 _public prototype_ `SourceId CreateSoundObjectSource(RenderingMode rendering_mode) override;`
- L70 _public prototype_ `void DestroySource(SourceId source_id) override;`
- L73 _public prototype_ `void SetInterleavedBuffer(SourceId source_id, const float* audio_buffer_ptr, size_t num_channels, size_t num_frames) override;` — Set source data.
- L75 _public prototype_ `void SetInterleavedBuffer(SourceId source_id, const int16* audio_buffer_ptr, size_t num_channels, size_t num_frames) override;`
- L77 _public prototype_ `void SetPlanarBuffer(SourceId source_id, const float* const* audio_buffer_ptr, size_t num_channels, size_t num_frames) override;`
- L79 _public prototype_ `void SetPlanarBuffer(SourceId source_id, const int16* const* audio_buffer_ptr, size_t num_channels, size_t num_frames) override;`
- L83 _public prototype_ `void SetSourceDistanceAttenuation(SourceId source_id, float distance_attenuation) override;` — Source configuration.
- L85 _public prototype_ `void SetSourceDistanceModel(SourceId source_id, DistanceRolloffModel rolloff, float min_distance, float max_distance) override;`
- L87 _public prototype_ `void SetSourcePosition(SourceId source_id, float x, float y, float z) override;`
- L89 _public prototype_ `void SetSourceRoomEffectsGain(SourceId source_id, float room_effects_gain) override;`
- L91 _public prototype_ `void SetSourceRotation(SourceId source_id, float x, float y, float z, float w) override;`
- L93 _public prototype_ `void SetSourceVolume(SourceId source_id, float volume) override;`
- L96 _public prototype_ `void SetSoundObjectDirectivity(SourceId sound_object_source_id, float alpha, float order) override;` — Sound object configuration.
- L98 _public prototype_ `void SetSoundObjectListenerDirectivity(SourceId sound_object_source_id, float alpha, float order) override;`
- L100 _public prototype_ `void SetSoundObjectNearFieldEffectGain(SourceId sound_object_source_id, float gain) override;`
- L102 _public prototype_ `void SetSoundObjectOcclusionIntensity(SourceId sound_object_source_id, float intensity) override;`
- L104 _public prototype_ `void SetSoundObjectSpread(SourceId sound_object_source_id, float spread_deg) override;`
- L108 _public prototype_ `void EnableRoomEffects(bool enable) override;` — Room effects configuration.
- L109 _public prototype_ `void SetReflectionProperties( const ReflectionProperties& reflection_properties) override;`
- L111 _public prototype_ `void SetReverbProperties(const ReverbProperties& reverb_properties) override;`
- L120 _public prototype_ `const AudioBuffer* GetAmbisonicOutputBuffer() const;` — Returns the last processed output buffer of the ambisonic mix. @return Pointer to ambisonic output buffer.
- L125 _public prototype_ `const AudioBuffer* GetStereoOutputBuffer() const;` — Returns the last processed output buffer of the stereo (binaural) mix. @return Pointer to stereo output buffer.
- L128 _public prototype_ `void ProcessNextBuffer();` — Triggers processing of the audio graph with the updated system properties.
- L141 _private prototype_ `template <typename OutputType> bool FillOutputBuffer(size_t num_channels, size_t num_frames, OutputType buffer_ptr);` — This method triggers the processing of the audio graph and outputs a binaural stereo output buffer. @tparam OutputType Output sample format, only float and int16 are supported. @param num_channels Number of channels in output buffer. @param num_frames Size of buffer in frames. @param buffer_ptr Raw pointer to audio buffer. @return True if a valid output was successfully rendered, false otherwise.
- L151 _private prototype_ `template <typename SampleType> void SetSourceBuffer(SourceId source_id, SampleType audio_buffer_ptr, size_t num_input_channels, size_t num_frames);` — Sets the next audio buffer to a sound source. @param source_id Id of sound source. @param audio_buffer_ptr Pointer to planar or interleaved audio buffer. @param num_input_channels Number of input channels. @param num_frames Number of frames per channel / audio buffer.
- L155 _private member_ `std::unique_ptr<GraphManager> graph_manager_;` — Graph manager used to create and destroy sound objects.
- L158 _private member_ `SystemSettings system_settings_;` — Manages system wide settings.
- L162 _private member_ `LocklessTaskQueue task_queue_;` — Task queue to cache manipulation of all the entities in the system. All tasks are executed from the audio thread.
- L165 _private member_ `std::atomic<int> source_id_counter_;` — Incremental source id counter.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_RESONANCE_AUDIO_API_IMPL_H_`
- L31 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/reverb_node.h` (Private)


#### class `vraudio::ReverbNode`  
`class ReverbNode : public ProcessingNode`  
_L32-93_
- inherits: `ProcessingNode`
- desc: Implements a spectral reverb producing a decorrelated stereo output with onset compensated by a pair of convolution filters.
- L38 _public prototype_ `ReverbNode(const SystemSettings& system_settings, FftManager* fft_manager);` — Constructs a |ReverbNode|. @param system_settings Global system configuration. @param fft_manager Pointer to a manager to perform FFT transformations.
- L42 _public prototype_ `void Update();` — Updates the |SpectralReverb| using the current room properties or RT60 values depending on the system settings.
- L46 _protected prototype_ `const AudioBuffer* AudioProcess(const NodeInput& input) override;` — Implements ProcessingNode.
- L50 _private member_ `const SystemSettings& system_settings_;` — Global system configuration.
- L53 _private member_ `ReverbProperties reverb_properties_;` — Current reverb properties.
- L56 _private member_ `ReverbProperties new_reverb_properties_;` — New reverb properties.
- L59 _private member_ `std::vector<float> rt60_band_update_steps_;` — Per band reverb time update step sizes.
- L62 _private member_ `float gain_update_step_;` — Update step size for the gain parameter.
- L65 _private member_ `bool rt60_updating_;` — Denotes whether the rt60s are currently being updated.
- L68 _private member_ `bool gain_updating_;` — Denotes whether the gain is currently being updated.
- L71 _private member_ `float buffers_to_update_;` — Number of buffers to updae rt60s over.
- L74 _private member_ `SpectralReverb spectral_reverb_;` — DSP class to perform filtering associated with the reverb.
- L77 _private member_ `ReverbOnsetCompensator onset_compensator_;` — DSP class to perform spectral reverb onset compensation.
- L81 _private member_ `size_t num_frames_processed_on_empty_input_;` — Number of frames of zeroed out data to be processed by the node to ensure the entire tail is rendered after input has ceased.
- L84 _private member_ `size_t reverb_length_frames_;` — Longest current reverb time, across all bands, in frames.
- L87 _private member_ `AudioBuffer output_buffer_;` — Output buffers for mixing spectral reverb and compensator output.
- L88 _private member_ `AudioBuffer compensator_output_buffer_;`
- L92 _private member_ `AudioBuffer silence_mono_buffer_;` — Silence mono buffer to render reverb tails during the absence of input buffers.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_REVERB_NODE_H_`
- L28 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/source_graph_config.h` (Private)


#### struct `vraudio::SourceGraphConfig`  
`struct SourceGraphConfig`  
_L27-39_
- desc: Configuration of a source and the nodes it is instantiating.
- L29 _public member_ `std::string configuration_name;` — Configuration name.
- L32 _public member_ `int ambisonic_order = 1;` — Ambisonic order to encode to/decode from source.
- L35 _public member_ `bool enable_hrtf = true;` — Flag to enable HRTF-based rendering of source.
- L38 _public member_ `bool enable_direct_rendering = true;` — Flag to enable direct rendering of source.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_SOURCE_GRAPH_CONFIG_H_`
- L24 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/source_parameters_manager.h` (Private)


#### class `vraudio::SourceParametersManager`  
`class SourceParametersManager`  
_L29-64_
- desc: Class that manages the corresponding parameters of each registered source.
- L32 _public typedef_ `using Process = std::function<void(SourceParameters*)>;` — Alias for the parameters process closure type.
- L37 _public prototype_ `void Register(SourceId source_id);` — Registers new source parameters for given |source_id|. @param source_id Source id.
- L42 _public prototype_ `void Unregister(SourceId source_id);` — Unregisters the source parameters for given |source_id|. @param source_id Source id.
- L48 _public prototype_ `const SourceParameters* GetParameters(SourceId source_id) const;` — Returns read-only source parameters for given |source_id|. @param source_id Source id. @return Read-only source parameters, nullptr if |source_id| not found.
- L54 _public prototype_ `SourceParameters* GetMutableParameters(SourceId source_id);` — Returns mutable source parameters for given |source_id|. @param source_id Source id. @return Mutable source parameters, nullptr if |source_id| not found.
- L59 _public prototype_ `void ProcessAllParameters(const Process& process);` — Executes given |process| for the parameters of each registered source. @param process Parameters processing method.
- L63 _private member_ `std::unordered_map<SourceId, SourceParameters> parameters_;` — Registered source parameters.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_SOURCE_PARAMETERS_MANAGER_H_`
- L26 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/stereo_mixing_panner_node.h` (Private)


#### class `vraudio::StereoMixingPannerNode`  
`class StereoMixingPannerNode : public ProcessingNode`  
_L31-57_
- inherits: `ProcessingNode`
- desc: Node that accepts single mono sound object buffer as input and pans into a stereo panorama.
- L36 _public prototype_ `explicit StereoMixingPannerNode(const SystemSettings& system_settings);` — Initializes StereoMixingPannerNode class. @param system_settings Global system configuration.
- L39 _public function_ `bool CleanUp() final` — Node implementation.
- L47 _protected prototype_ `const AudioBuffer* AudioProcess(const NodeInput& input) override;` — Implements ProcessingNode.
- L50 _private member_ `const SystemSettings& system_settings_;`
- L53 _private member_ `GainMixer gain_mixer_;` — |GainMixer| instance.
- L56 _private member_ `std::vector<float> coefficients_;` — Panning coefficients to be applied the input.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_STEREO_MIXING_PANNER_NODE_H_`
- L27 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/graph/system_settings.h` (Private)


#### class `vraudio::SystemSettings`  
`class SystemSettings`  
_L30-185_
- desc: Contains system-wide settings and parameters. Note that this class is not thread-safe. Updating system parameters must be avoided during the audio graph processing.
- L37 _public function_ `SystemSettings(size_t num_output_channels, size_t frames_per_buffer, int sample_rate_hz) : sample_rate_hz_(sample_rate_hz), frames_per_buffer_(frames_per_buffer), num_channels_(num_output_channels), head_rotation_(WorldRotation::Identity()), head_position_(WorldPosition::Zero()), primary_gain_(1.0f), stereo_speaker_mode_(false)` — Constructor initializes the system configuration. @param num_output_channels Number of output channels. @param frames_per_buffer Buffer size in frames. @param sample_rate_hz Sample rate.
- L50 _public function_ `void SetHeadRotation(const WorldRotation& head_rotation)` — Sets the listener head orientation. @param head_rotation Listener head orientation.
- L57 _public function_ `void SetHeadPosition(const WorldPosition& head_position)` — Sets the listener head position. @param head_position Listener head position.
- L66 _public function_ `void SetStereoSpeakerMode(bool enabled)` — Sets the global stereo speaker mode flag. This flag enforces stereo panning and disables HRTF-based binauralization. The stereo speaker mode is disabled by default. @param enabled Defines the stereo speaker mode state.
- L71 _public function_ `SourceParametersManager* GetSourceParametersManager()` — Returns the source parameters manager. @return Mutable source parameters manager.
- L79 _public function_ `const SourceParameters* GetSourceParameters(SourceId source_id) const` — Returns the parameters of source with given |source_id|. @param source_id Source id. @return Pointer to source parameters, nullptr if |source_id| not found.
- L86 _public function_ `int GetSampleRateHz() const` — Returns the sample rate. @return Sample rate in Hertz.
- L91 _public function_ `size_t GetFramesPerBuffer() const` — Returns the frames per buffer. @return Buffer size in frames.
- L96 _public function_ `size_t GetNumChannels() const` — Returns the number of output channels. @return Number of output channels.
- L101 _public function_ `const WorldRotation& GetHeadRotation() const` — Returns the head rotation. @return Head orientation.
- L106 _public function_ `const WorldPosition& GetHeadPosition() const` — Returns the head position. @return Head position.
- L111 _public function_ `bool IsStereoSpeakerModeEnabled() const` — Returns the stereo speaker mode state. @return Current stereo speaker mode state.
- L116 _public function_ `void SetPrimaryGain(float primary_gain)` — Sets the primary gain. @param primary_gain primary output gain.
- L121 _public function_ `void SetReflectionProperties( const ReflectionProperties& reflection_properties)` — Sets current reflection properties. @param reflection_properties Reflection properties.
- L129 _public function_ `void SetReverbProperties(const ReverbProperties& reverb_properties)` — Sets current reverb properties. @param reverb_properties Reflection properties.
- L136 _public function_ `float GetPrimaryGain() const` — Returns the primary gain. @return primary output gain.
- L141 _public function_ `const ReflectionProperties& GetReflectionProperties() const` — Returns the current reflection properties of the environment. @return Current reflection properties.
- L148 _public function_ `const ReverbProperties& GetReverbProperties() const` — Returns the current reverb properties of the environment. @return Current reverb properties.
- L154 _public prototype_ `SystemSettings& operator=(const SystemSettings&) = delete;` — Disable copy and assignment operator. Since |SystemSettings| serves as a global parameter storage, it should never be copied.
- L155 _public prototype_ `SystemSettings(const SystemSettings&) = delete;`
- L159 _private member_ `const int sample_rate_hz_;` — Sampling rate.
- L162 _private member_ `const size_t frames_per_buffer_;` — Frames per buffer.
- L165 _private member_ `const size_t num_channels_;` — Number of channels per buffer.
- L168 _private member_ `WorldRotation head_rotation_;` — The most recently updated head rotation and position.
- L169 _private member_ `WorldPosition head_position_;`
- L172 _private member_ `SourceParametersManager source_parameters_manager_;` — Source parameters manager.
- L175 _private member_ `float primary_gain_;` — primary gain in amplitude.
- L178 _private member_ `ReflectionProperties reflection_properties_;` — Current reflection properties of the environment.
- L181 _private member_ `ReverbProperties reverb_properties_;` — Current reverb properties of the environment.
- L184 _private member_ `bool stereo_speaker_mode_;` — Defines the state of the global speaker mode.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_GRAPH_SYSTEM_SETTINGS_H_`
- L25 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/node/node.h` (Private)


#### class `vraudio::Node`  
`class Node : public std::enable_shared_from_this<Node>`  
_L47-150_
- inherits: `std::enable_shared_from_this<Node>`
- desc: Implements a processing node in a synchronous processing graph. This processing graph is expected to be directed, acyclic, and accessed from a single thread. Subclasses are expected to implement Process(), which will read from all of the instance's inputs, process the data as necessary, and then write to all of its outputs. Data is passed through unique_ptrs, so nodes are expected to modify data in place whenever it suits their purposes. If an outputs is connected to more than one input, copies will be made for each input. Graphs are managed through shared_ptrs. Orphaned nodes are kept alive as long as they output to a living input. Ownership is unidirectional -- from input to output -- in order to avoid circular dependencies.
- L49 _public prototype_ `virtual ~Node() = default;`
- L50 _public prototype_ `virtual void Process() = 0;`
- L57 _public prototype_ `virtual bool CleanUp() = 0;` — Disconnects from input nodes that are marked to be at the end of data stream. @return True if node is does not have any inputs and can be removed, false otherwise.

#### class `vraudio::Node::Input`  
`template <typename T> class Input`  
_L66-109_
- desc: An endpoint for a node, this object consumes data from any connected outputs. Because an input may be connected to more than one output, it returns a vector of read data. All outputs must be of the same type.
- L70 _public typedef_ `typedef std::unordered_map<Output<T>*, std::shared_ptr<Node>> OutputNodeMap;` — Unordered map that stores pairs of input Node instances and their |Output| member.
- L72 _public function_ `Input()`
- L73 _public prototype_ `~Input();`
- L76 _public prototype_ `const std::vector<T>& Read();` — Returns a vector of computed data, one for each connected output.
- L82 _public prototype_ `void Connect(const std::shared_ptr<Node>& node, Output<T>* output);` — Connects this input to the specified output. @param node The parent of the output. @param output The output to connect to.
- L87 _public prototype_ `void Disconnect(Output<T>* output);` — Disconnects this input from the specified output. @param output The output to be disconnected.
- L92 _public prototype_ `size_t GetNumConnections() const;` — Returns the number of connected outputs. @return Number of connected outputs.
- L96 _public prototype_ `const OutputNodeMap& GetConnectedNodeOutputPairs();` — Returns reference to OutputNodeMap map to obtain all connected nodes and their outputs.
- L99 _public prototype_ `Input(const Input& that) = delete;` — Disable copy constructor.
- L104 _private prototype_ `void AddOutput(const std::shared_ptr<Node>& node, Output<T>* output);`
- L105 _private prototype_ `void RemoveOutput(Output<T>* output);`
- L107 _private member_ `OutputNodeMap outputs_;`
- L108 _private member_ `std::vector<T> read_data_;`
- L153 _function_ `template <class T> Node::Input<T>::~Input()`
- L160 _function_ `template <class T> const std::vector<T>& Node::Input<T>::Read()`
- L175 _function_ `template <class T> void Node::Input<T>::Connect(const std::shared_ptr<Node>& node, Output<T>* output)`
- L184 _function_ `template <class T> void Node::Input<T>::Disconnect(Output<T>* output)` — RemoveOutput(output) may trigger *output be destructed, so we need to call output->RemoveInput(this) first.
- L190 _function_ `template <class T> size_t Node::Input<T>::GetNumConnections() const`
- L196 _function_ `Node::Input<T>::GetConnectedNodeOutputPairs()`
- L201 _function_ `template <class T> void Node::Input<T>::AddOutput(const std::shared_ptr<Node>& node, Output<T>* output)`
- L209 _function_ `template <class T> void Node::Input<T>::RemoveOutput(Output<T>* output)`

#### class `vraudio::Node::Output`  
`template <typename T> class Output`  
_L120-149_
- desc: An endpoint for a node, this object produces data for any connected inputs. Because an output may have more than one input, this object will duplicate any computed data, once for each connected input. All inputs must be of the same type. If an output does not have any data to deliver, it will ask its parent node to process more data. It is assumed that after processing, some new data will be written to this output.
- L122 _public function_ `explicit Output(Node* node) : parent_(node)`
- L128 _public prototype_ `void Write(T data);` — Parent nodes should call this function to push new data to any connected inputs. This data will be copied once for each connected input. @param data New data to pass to all connected inputs.
- L131 _public prototype_ `Output(const Output& that) = delete;` — Disable copy constructor.
- L137 _private typedef_ `typedef T (*CopyOperator)(const T&);` — Signature of copy operator.
- L141 _private prototype_ `T PullData();` — Returns a single piece of stored processed data. If no data exists, the parent node is processed to produce more data.
- L143 _private prototype_ `void AddInput(Input<T>* input);`
- L144 _private prototype_ `bool RemoveInput(Input<T>* input);`
- L146 _private member_ `std::set<Input<T>*> inputs_;`
- L147 _private member_ `std::vector<T> written_data_;`
- L148 _private member_ `Node* parent_;`
- L214 _function_ `template <class T> T Node::Output<T>::PullData()`
- L227 _function_ `template <class T> void Node::Output<T>::Write(T data)`
- L241 _function_ `template <class T> void Node::Output<T>::AddInput(Input<T>* input)`
- L246 _function_ `template <class T> bool Node::Output<T>::RemoveInput(Input<T>* input)`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_NODE_NODE_H_`
- L28 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/node/processing_node.h` (Private)


#### class `vraudio::ProcessingNode`  
`class ProcessingNode : public Node, public SubscriberNode<const AudioBuffer*>, public PublisherNode<const AudioBuffer*>`  
_L31-111_
- inherits: `Node,SubscriberNode<constAudioBuffer*>,PublisherNode<constAudioBuffer*>`
- desc: Audio processing node that reads from multiple inputs, processes the received data and outputs its result.
- L35 _public typedef_ `typedef SubscriberNode<const AudioBuffer*> SubscriberNodeType;`
- L36 _public typedef_ `typedef PublisherNode<const AudioBuffer*> PublisherNodeType;`
- L67 _public prototype_ `ProcessingNode();`
- L70 _public prototype_ `void Connect( const std::shared_ptr<PublisherNodeType>& publisher_node) override;` — SubscriberNode<InputType> implementation.
- L74 _public prototype_ `void Process() final;` — Node implementation.
- L75 _public prototype_ `bool CleanUp() override;`
- L80 _public prototype_ `void EnableProcessOnEmptyInput(bool enable);` — By default, calls to AudioProcess() are skipped in case of empty input buffers. This enables this node to process audio buffers in the absence of input data (which is needed for instance for a reverberation effect).
- L83 _public prototype_ `ProcessingNode(const ProcessingNode& that) = delete;` — Disable copy constructor.
- L87 _protected prototype_ `void CallCleanUpOnInputNodes();` — Calls |CleanUp| on all connected input nodes.
- L95 _protected prototype_ `virtual const AudioBuffer* AudioProcess(const NodeInput& input) = 0;` — Pure virtual method to implement the audio processing method. This method receives a vector of all input arguments to be processed and requires to output a single output buffer. @param input Input instance to receive pointers to input |AudioBuffer|s. @return Returns output data.
- L99 _private prototype_ `std::shared_ptr<Node> GetSharedNodePtr() final;` — PublisherNode<OutputType> implementation.
- L100 _private prototype_ `Node::Output<const AudioBuffer*>* GetOutput() final;`
- L103 _private member_ `Node::Input<const AudioBuffer*> input_stream_;` — Input stream to poll for incoming data.
- L106 _private member_ `Node::Output<const AudioBuffer*> output_stream_;` — Output stream to write processed data to.
- L110 _private member_ `bool process_on_no_input_;` — Flag that indicates if |AudioProcess| should be called in case no input data is available.

#### class `vraudio::ProcessingNode::NodeInput`  
`class NodeInput`  
_L39-65_
- desc: Helper class to manage incoming |AudioBuffer|s.
- L45 _public prototype_ `explicit NodeInput(const std::vector<const AudioBuffer*>& input_vector);` — Constructor. @param input_vector Vector containing pointers to incoming |AudioBuffer|s.
- L52 _public prototype_ `const AudioBuffer* GetSingleInput() const;` — Returns a nullptr if zero or more than one input buffers are available. Otherwise a pointer to the single input |AudioBuffer| is returned. This method should be used if only a single input |AudioBuffer| is expected. @return Pointer to single input |AudioBuffer|.
- L57 _public prototype_ `const std::vector<const AudioBuffer*>& GetInputBuffers() const;` — Returns vector with input |AudioBuffer|s. @return Pointer to single input |AudioBuffer|.
- L60 _public prototype_ `NodeInput(const NodeInput& that) = delete;` — Delete copy constructor.
- L64 _private member_ `const std::vector<const AudioBuffer*>& input_vector_;` — Const reference to vector of input |AudioBuffer|s.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_NODE_PROCESSING_NODE_H_`
- L27 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/node/publisher_node.h` (Private)


#### class `vraudio::PublisherNode`  
`template <typename OutputType> class PublisherNode`  
_L34-47_
- desc: Interface for publisher nodes that declares helper methods required to connect to a publisher node. All publishing nodes need to implement this interface. @tparam OutputType Type of the output container being streamed. @interface
- L36 _public prototype_ `virtual ~PublisherNode() = default;`
- L41 _public prototype_ `virtual std::shared_ptr<Node> GetSharedNodePtr() = 0;` — Creates a shared pointer of the Node instance. @return Returns a shared pointer the of Node instance.
- L46 _public prototype_ `virtual Node::Output<OutputType>* GetOutput() = 0;` — Get internal Node::Output instance. @return Returns a pointer to the internal Node::Output instance.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_NODE_PUBLISHER_NODE_H_`
- L25 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/node/sink_node.h` (Private)


#### class `vraudio::SinkNode`  
`class SinkNode : public Node, public SubscriberNode<const AudioBuffer*>`  
_L30-55_
- inherits: `Node,SubscriberNode<constAudioBuffer*>`
- desc: Audio sink node that reads from multiple inputs.
- L32 _public typedef_ `typedef PublisherNode<const AudioBuffer*> PublisherNodeType;`
- L34 _public prototype_ `SinkNode();`
- L39 _public prototype_ `const std::vector<const AudioBuffer*>& ReadInputs();` — Polls for data on all inputs of the sink node. @return A vector of input data.
- L42 _public prototype_ `void Connect( const std::shared_ptr<PublisherNodeType>& publisher_node) override;` — SubscriberNode<AudioBuffer> implementation.
- L46 _public prototype_ `void Process() final;` — Node implementation.
- L47 _public prototype_ `bool CleanUp() final;`
- L50 _public prototype_ `SinkNode(const SinkNode& that) = delete;` — Disable copy constructor.
- L54 _private member_ `Node::Input<const AudioBuffer*> input_stream_;` — Input stream to poll for incoming data.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_NODE_SINK_NODE_H_`
- L27 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/node/source_node.h` (Private)


#### class `vraudio::SourceNode`  
`class SourceNode : public Node, public PublisherNode<const AudioBuffer*>`  
_L29-64_
- inherits: `Node,PublisherNode<constAudioBuffer*>`
- desc: Audio source node that outputs data via the AudioProcess() method.
- L31 _public typedef_ `typedef PublisherNode<const AudioBuffer*> PublisherNodeType;`
- L33 _public prototype_ `SourceNode();`
- L36 _public prototype_ `void Process() final;` — Node implementation.
- L37 _public prototype_ `bool CleanUp() final;`
- L40 _public prototype_ `std::shared_ptr<Node> GetSharedNodePtr() final;` — PublisherNode<OutputType> implementation.
- L41 _public prototype_ `Node::Output<const AudioBuffer*>* GetOutput() final;`
- L45 _public prototype_ `void MarkEndOfStream();` — Marks this node as being out of data and to be removed during the next clean-up cycle.
- L48 _public prototype_ `SourceNode(const SourceNode& that) = delete;` — Disable copy constructor.
- L56 _protected prototype_ `virtual const AudioBuffer* AudioProcess() = 0;` — Pure virtual method to implement the audio processing method. This method requires to return a single output buffer that can be processed by the node subscribers. @return Returns output data.
- L60 _private member_ `Node::Output<const AudioBuffer*> output_stream_;` — Output stream to write processed data to.
- L63 _private member_ `std::atomic<bool> end_of_stream_;` — Flag indicating if this source node can be removed.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_NODE_SOURCE_NODE_H_`
- L26 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/node/subscriber_node.h` (Private)


#### class `vraudio::SubscriberNode`  
`template <typename InputType> class SubscriberNode`  
_L35-44_
- desc: Interface for subscriber nodes that declares the connection and disconnection methods. All subscribing nodes need to implement this interface. @tparam InputType Input data type, i. e., the output data type of nodes to connect to. @interface
- L37 _public prototype_ `virtual ~SubscriberNode() = default;`
- L42 _public prototype_ `virtual void Connect( const std::shared_ptr<PublisherNode<InputType>>& publisher_node) = 0;` — Connects this node to |publisher_node|. @param publisher_node Publisher node to connect to.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_NODE_SUBSCRIBER_NODE_H_`
- L25 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/buffer_crossfader.h` (Private)


#### class `vraudio::BufferCrossfader`  
`class BufferCrossfader`  
_L26-44_
- desc: Class that takes two input buffers and produces an output buffer by applying linear crossfade between the inputs.
- L28 _public prototype_ `explicit BufferCrossfader(size_t num_frames);`
- L37 _public prototype_ `void ApplyLinearCrossfade(const AudioBuffer& input_fade_in, const AudioBuffer& input_fade_out, AudioBuffer* output) const;` — Applies linear crossfade for given input buffers and stores the result in |output| buffer. Note that, in-place processing is *not* supported by this method, the output buffer must be different than the input buffers. @param input_fade_in Input buffer to fade-in to. @param input_fade_out Input buffer to fade-out from. @param output Output buffer to store the crossfaded result.
- L43 _private member_ `AudioBuffer crossfade_buffer_;` — Stereo audio buffer to store crossfade decay and growth multipliers.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_BUFFER_CROSSFADER_H_`
- L22 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/buffer_partitioner.h` (Private)


#### class `vraudio::BufferPartitioner`  
`class BufferPartitioner`  
_L29-148_
- desc: Packages input buffers of arbitrary sizes into fixed size |AudioBuffer|s.
- L36 _public typedef_ `typedef std::function<AudioBuffer*(AudioBuffer* output)> NewBufferCallback;` — Callback to receive processed and assign empty |AudioBuffer|s while processing input buffers. @param output Pointer to partitioned |AudioBuffer| with input audio data. @return Pointer to the next |AudioBuffer| to be filled.
- L43 _public prototype_ `BufferPartitioner(size_t num_channels, size_t frames_per_buffer, NewBufferCallback buffer_callback);` — Constructor. @param num_channels Number of audio channels in input and output buffers. @param frames_per_buffer Number of frames in output |AudioBuffer|s. @param buffer_callback Callback to receive output |AudioBuffer|s.
- L51 _public prototype_ `size_t GetNumGeneratedBuffersForNumInputFrames(size_t num_input_frames) const;` — Predicts the number of generated buffers for a given number of input frames and based on the current fill state of the internal |temp_buffer_|. @param num_input_frames Number of input frames. @return Number of generated output buffers.
- L54 _public prototype_ `size_t GetNumBufferedFrames() const;` — Returns the number of buffered frames in internal |temp_buffer_|.
- L62 _public prototype_ `void AddBuffer(const int16* interleaved_buffer, size_t num_channels, size_t num_frames);` — Adds an interleaved int16 input buffer. This method triggers |NewBufferCallback| whenever a new |AudioBuffer| has been generated. @param interleaved_buffer Interleaved input buffer. @param num_channels Number of channels in input buffer. @param num_frames Number of frames in input buffer.
- L71 _public prototype_ `void AddBuffer(const float* interleaved_buffer, size_t num_channels, size_t num_frames);` — Adds an interleaved float input buffer. This method triggers |NewBufferCallback| whenever a new |AudioBuffer| has been generated. @param interleaved_buffer Interleaved input buffer. @param num_channels Number of channels in input buffer. @param num_frames Number of frames in input buffer.
- L80 _public prototype_ `void AddBuffer(const float* const* planar_buffer, size_t num_channels, size_t num_frames);` — Adds a planar float input buffer. This method triggers |NewBufferCallback| whenever a new |AudioBuffer| has been generated. @param planar_buffer Pointer to array of pointers for each audio channel. @param num_channels Number of channels in input buffer. @param num_frames Number of frames in input buffer.
- L89 _public prototype_ `void AddBuffer(const int16* const* planar_buffer, size_t num_channels, size_t num_frames);` — Adds a planar int16 input buffer. This method triggers |NewBufferCallback| whenever a new |AudioBuffer| has been generated. @param planar_buffer Pointer to array of pointers for each audio channel. @param num_channels Number of channels in input buffer. @param num_frames Number of frames in input buffer.
- L96 _public prototype_ `void AddBuffer(const AudioBuffer& audio_buffer);` — Adds an |AudioBuffer|. This method triggers |NewBufferCallback| whenever a new |AudioBuffer| has been generated. @param audio_buffer Planar |AudioBuffer| input.
- L105 _public prototype_ `void AddBuffer(size_t num_valid_frames, const AudioBuffer& audio_buffer);` — Adds an |AudioBuffer| and specifies how many of that audio buffers frames are valid. This method triggers |NewBufferCallback| whenever a new |AudioBuffer| has been generated. @param num_valid_frames Indicates the number of frames which are actually valid in the audio buffer passed. Frames after this will be ignored. @param audio_buffer Planar |AudioBuffer| input.
- L112 _public prototype_ `size_t Flush();` — Flushes the internal temporary |AudioBuffer| by filling the remaining audio frames with silence. @return Number of zero padded audio frames. Zero if the internal buffer is empty.
- L115 _public prototype_ `void Clear();` — Clears internal temporary buffer that holds remaining audio frames.
- L127 _private prototype_ `template <typename BufferType> void AddBufferTemplated(BufferType buffer, size_t num_channels, size_t num_frames);` — Adds an interleaved and planar float and int16 input buffer as well as planar |AudioBuffer| input. This method triggers |NewBufferCallback| whenever a new |AudioBuffer| has been generated. @tparam BufferType Input buffer type. @param buffer Input buffer. @param num_channels Number of channels in input buffer. @param num_frames Number of frames in input buffer.
- L131 _private member_ `const size_t num_channels_;` — Number of channels in input buffers.
- L134 _private member_ `const size_t frames_per_buffer_;` — Number of frames per buffer in output buffers.
- L137 _private member_ `const NewBufferCallback buffer_callback_;` — Callback to output generated |AudioBuffer|s.
- L140 _private member_ `AudioBuffer* current_buffer_ptr_;` — Temporary buffer to remaining samples from input buffers.
- L143 _private member_ `size_t current_buffer_write_position_frames_;` — Current write position in frames in temporary buffer.
- L147 _private member_ `std::vector<const float*> planar_channel_ptrs_;` — Helper vector to obtain an array of planar channel pointers from an |AudioBuffer|.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_BUFFER_PARTITIONER_H_`
- L26 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/buffer_unpartitioner.h` (Private)


#### class `vraudio::BufferUnpartitioner`  
`class BufferUnpartitioner`  
_L29-133_
- desc: Unpackages |AudioBuffer| into output buffers of arbitrary sizes.
- L33 _public typedef_ `typedef std::function<const AudioBuffer*()> GetBufferCallback;` — Callback to obtain input |AudioBuffer|s. Returns a nullptr if no buffers are available.
- L40 _public prototype_ `BufferUnpartitioner(size_t num_channels, size_t frames_per_buffer, GetBufferCallback buffer_callback);` — Constructor. @param num_channels Number of audio channels in input and output buffers. @param frames_per_buffer Number of frames per input buffer. @param buffer_callback Callback to receive output |AudioBuffer|s.
- L48 _public prototype_ `size_t GetNumBuffersRequestedForNumInputFrames( size_t num_output_frames) const;` — Returns the number of input buffers required for a given number of output frames and based on the current fill state of the internal |temp_buffer_|. @param num_output_frames Number of output frames. @return Number of required input |AudioBuffer|s.
- L52 _public prototype_ `size_t GetNumBufferedFrames() const;` — Returns the number of buffered frames in internal |temp_buffer_|.
- L61 _public prototype_ `size_t GetBuffer(int16* output_buffer, size_t num_channels, size_t num_frames);` — Requests an interleaved int16 output buffer. This method triggers |GetBufferCallback|. @param output_buffer Interleaved output buffer to write to. @param num_channels Number of channels in output buffer. @param num_frames Number of frames in output buffer. @return Number of frames actually written.
- L71 _public prototype_ `size_t GetBuffer(float* output_buffer, size_t num_channels, size_t num_frames);` — Requests an interleaved float output buffer. This method triggers |GetBufferCallback|. @param output_buffer Interleaved output buffer to write to. @param num_channels Number of channels in output buffer. @param num_frames Number of frames in output buffer. @return Number of frames actually written.
- L81 _public prototype_ `size_t GetBuffer(int16** output_buffer, size_t num_channels, size_t num_frames);` — Requests a planar int16 output buffer. This method triggers |GetBufferCallback|. @param output_buffer Planar output buffer to write to. @param num_channels Number of channels in output buffer. @param num_frames Number of frames in output buffer. @return Number of frames actually written.
- L91 _public prototype_ `size_t GetBuffer(float** output_buffer, size_t num_channels, size_t num_frames);` — Requests a planar float output buffer. This method triggers |GetBufferCallback|. @param output_buffer Planar output buffer to write to. @param num_channels Number of channels in output buffer. @param num_frames Number of frames in output buffer. @return Number of frames actually written.
- L95 _public prototype_ `void Clear();` — Clears internal temporary buffer that holds remaining audio frames.
- L102 _private prototype_ `size_t GetNumFramesAvailableInBuffer() const;` — Returns the number of frames that are buffered in |current_input_buffer_|. @return Number of frames in |current_input_buffer_|. If |current_input_buffer_| is undefined, it returns 0.
- L114 _private prototype_ `template <typename BufferType> size_t GetBufferTemplated(BufferType buffer, size_t num_channels, size_t num_frames);` — Writes output buffer into target buffer. Supported buffer types are planar and interleaved floating point abd interleaved int16 output. This method triggers |GetBufferCallback|. @tparam BufferType Output buffer type. @param buffer Output buffer to write to. @param num_channels Number of channels in output buffer. @param num_frames Number of frames in output buffer. @return Number of frames actually written.
- L119 _private member_ `const size_t num_channels_;` — Number of channels in output buffers.
- L123 _private member_ `const size_t frames_per_buffer_;` — Number of frames per buffer in output buffers.
- L126 _private member_ `const GetBufferCallback buffer_callback_;` — Callback to request input |AudioBuffer|s.
- L129 _private member_ `const AudioBuffer* current_input_buffer_;` — Temporary buffer containing remaining audio frames.
- L132 _private member_ `size_t current_buffer_read_offset_frames_;` — Current read position in |current_input_buffer_|.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_BUFFER_UNPARTITIONER_H_`
- L26 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/lockless_task_queue.h` (Private)


#### class `vraudio::LocklessTaskQueue`  
`class LocklessTaskQueue`  
_L48-126_
- desc: Lock-less task queue which is thread safe for cocurrent task producers and a single task executor thread.
- L51 _public typedef_ `typedef std::function<void()> Task;` — Alias for the task closure type.
- L56 _public prototype_ `explicit LocklessTaskQueue(size_t max_tasks);` — Constructor. Preallocates nodes on the task queue list. @param max_tasks Maximum number of tasks on the task queue.
- L58 _public prototype_ `~LocklessTaskQueue();`
- L63 _public prototype_ `void Post(Task&& task);` — Posts a new task to task queue. @param task Task to process.
- L66 _public prototype_ `void Execute();` — Executes all tasks on the task queue.
- L69 _public prototype_ `void Clear();` — Removes all tasks on the task queue.
- L90 _private prototype_ `void PushNodeToList(std::atomic<Node*>* list_head, Node* node);` — Pushes a node to the front of a list. @param list_head Pointer to list head. @param node Node to be pushed to the front of the list.
- L96 _private prototype_ `Node* PopNodeFromList(std::atomic<Node*>* list_head);` — Pops a node from the front of a list. @param list_head Pointer to list head. @return Front node, nullptr if list is empty.
- L103 _private prototype_ `void ProcessTaskList(Node* list_head, bool execute);` — Iterates over list and moves all tasks to |temp_tasks_| to be executed in FIFO order. All processed nodes are pushed back to the free list. @param list_head Head node of list to be processed. @param execute If true, tasks on task list are executed.
- L108 _private prototype_ `void Init(size_t num_nodes);` — Initializes task queue structures and preallocates task queue nodes. @param num_nodes Number of nodes to be initialized on free list.
- L111 _private member_ `std::atomic<Node*> free_list_head_;` — Pointer to head node of free list.
- L114 _private member_ `std::atomic<Node*> task_list_head_;` — Pointer to head node of task list.
- L117 _private member_ `std::vector<Node> nodes_;` — Holds preallocated nodes.
- L121 _private member_ `std::vector<Task> temp_tasks_;` — Temporary vector to hold |Task|s in order to execute them in reverse order (FIFO, instead of LIFO).
- L124 _private member_ `std::mutex tasks_mutex_;` — this mutex guarantees that temp_tasks_ is not mutated while being iterated on.
- L125 _private member_ `size_t max_tasks_;`

#### struct `vraudio::LocklessTaskQueue::Node`  
`struct Node`  
_L73-84_
- desc: Node to model a single-linked list.
- L74 _public prototype_ `Node() = default;`
- L77 _public function_ `Node(const Node& ) : next()` — Dummy copy constructor to enable vector::resize allocation.
- L80 _public member_ `LocklessTaskQueue::Task task;` — User task.
- L83 _public member_ `std::atomic<Node*> next;` — Pointer to next node.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_LOCKLESS_TASK_QUEUE_H_`
- L44 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/ogg_vorbis_recorder.h` (Private)


#### class `vraudio::OggVorbisRecorder`  
`class OggVorbisRecorder`  
_L32-90_
- L36 _public prototype_ `OggVorbisRecorder(int sample_rate_hz, size_t num_channels, size_t num_frames, size_t max_num_buffers);`
- L42 _public prototype_ `void AddInput(std::unique_ptr<AudioBuffer> input_buffer);` — Adds next input buffer at the end of the record data. @param input_buffer Next audio buffer to be recorded.
- L45 _public prototype_ `void Reset();` — Flushes the record data.
- L56 _public prototype_ `bool WriteToFile(const std::string& file_path, float quality, bool seamless);` — Writes the current record data into a file and resets the recorder. @param file_path Full path of the file to be recorded into. @param quality Compression quality of the record. The usable range is from -0.1 (lowest quality, smallest file) to 1.0 (highest quality, largest file). @param seamless True to record seamlessly for looping. Note that this option will truncate the record length by |num_frames_| samples. @return False if fails to successfully write data into |file_path|.
- L60 _private prototype_ `void MakeSeamless();` — Helper method to make record data seamless.
- L63 _private member_ `const int sample_rate_hz_;` — Record sampling rate.
- L66 _private member_ `const size_t num_channels_;` — Record number of channels.
- L69 _private member_ `const size_t num_frames_;` — Record number of frames per buffer.
- L72 _private member_ `const size_t max_num_buffers_;` — Maximum number of input buffers allowed to record.
- L75 _private member_ `std::vector<std::unique_ptr<AudioBuffer>> data_;` — Record data that is stored as a list of planar audio buffers.
- L79 _private member_ `std::vector<const float*> temp_data_channel_ptrs_;` — Temporary vector to extract pointers to planar channels in an |AudioBuffer|.
- L82 _private member_ `BufferCrossfader crossfader_;` — Buffer crossfader that is used to create seamless loop.
- L86 _private member_ `AudioBuffer crossfade_buffer_;`
- L89 _private member_ `VorbisStreamEncoder encoder_;` — OGG Vorbis encoder to write record data into file in compressed format.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_OGG_VORBIS_RECORDER_H_`
- L27 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/planar_interleaved_conversion.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_PLANAR_INTERLEAVED_CONVERSION_H_`
- L26 _namespace_ `namespace vraudio`
- L36 _prototype_ `void PlanarFromInterleaved(const float* interleaved_buffer, size_t num_input_frames, size_t num_input_channels, const std::vector<float*>& planar_buffer_ptr, size_t num_output_frames);` (scope `vraudio`) — Copies interleaved audio data from a raw float pointer into separate channel buffers specified by a vector of raw float pointers. @param interleaved_buffer Raw float pointer to interleaved audio data. @param num_input_frames Size of |interleaved_buffer| in frames. @param num_input_channels Number of channels in interleaved audio data. @param planar_buffer_ptr Raw float pointers to each planar channel buffer. @param num_output_frames Number of frames per channel in output buffer.
- L49 _prototype_ `void PlanarFromInterleaved(const int16* interleaved_buffer, size_t num_input_frames, size_t num_input_channels, const std::vector<float*>& planar_buffer_ptr, size_t num_output_frames);` (scope `vraudio`) — Copies interleaved audio data from a raw int16 pointer into separate channel buffers specified by a vector of raw float pointers. @param interleaved_buffer Raw int16 pointer to interleaved audio data. @param num_input_frames Size of |interleaved_buffer| in frames. @param num_input_channels Number of channels in interleaved audio data. @param planar_buffer_ptr Raw float pointers to each planar channel buffer. @param num_output_frames Number of frames per channel in output buffer.
- L62 _prototype_ `void FillAudioBuffer(const float* interleaved_buffer, size_t num_input_frames, size_t num_input_channels, AudioBuffer* output);` (scope `vraudio`) — Copies interleaved audio data from a raw float pointer into a planar |AudioBuffer|. Note that the number of output channels and frames is defined by the target |AudioBuffer| instance. @param interleaved_buffer Raw float pointer to interleaved audio data. @param num_input_frames Size of interleaved_buffer in frames. @param num_input_channels Number of channels in interleaved audio data. @param output Target output buffer.
- L73 _prototype_ `void FillAudioBuffer(const int16* interleaved_buffer, size_t num_input_frames, size_t num_input_channels, AudioBuffer* output);` (scope `vraudio`) — Copies interleaved audio data from a raw int16 pointer into a planar |AudioBuffer|. Note that the number of output channels and frames is defined by the target |AudioBuffer| instance. @param interleaved_buffer Raw int16 pointer to interleaved audio data. @param num_input_frames Size of interleaved_buffer in frames. @param num_input_channels Number of channels in interleaved audio data. @param output Target output buffer.
- L83 _prototype_ `void FillAudioBuffer(const std::vector<float>& interleaved_buffer, size_t num_input_channels, AudioBuffer* output);` (scope `vraudio`) — Copies interleaved audio data from a float vector into a planar |AudioBuffer|. Note that the number of output channels and frames is defined by the target |AudioBuffer| instance. @param interleaved_buffer Interleaved audio data. @param num_input_channels Number of channels in interleaved audio data. @param output Target output buffer.
- L93 _prototype_ `void FillAudioBuffer(const std::vector<int16>& interleaved_buffer, size_t num_input_channels, AudioBuffer* output);` (scope `vraudio`) — Copies interleaved audio data from a int16 vector into a planar |AudioBuffer|. Note that the number of output channels and frames is defined by the target |AudioBuffer| instance. @param interleaved_buffer Interleaved audio data. @param num_input_channels Number of channels in interleaved audio data. @param output Target output buffer.
- L104 _prototype_ `void FillAudioBuffer(const float* const* planar_ptrs, size_t num_input_frames, size_t num_input_channels, AudioBuffer* output);` (scope `vraudio`) — Copies raw planar float audio data into a planar |AudioBuffer|. Note that the number of output channels and frames is defined by the target |AudioBuffer| instance. @param planar_ptrs Pointer to an array of pointers to raw float channel data. @param num_input_frames Size of planar input in frames. @param num_input_channels Number of channels in planar input buffer. @param output Target output buffer.
- L115 _prototype_ `void FillAudioBuffer(const int16* const* planar_ptrs, size_t num_input_frames, size_t num_input_channels, AudioBuffer* output);` (scope `vraudio`) — Copies raw planar int16 audio data into a planar |AudioBuffer|. Note that the number of output channels and frames is defined by the target |AudioBuffer| instance. @param planar_ptrs Pointer to an array of pointers to raw int16 channel data. @param num_input_frames Size of planar input in frames. @param num_input_channels Number of channels in planar input buffer. @param output Target output buffer.
- L129 _prototype_ `void FillAudioBufferWithOffset(const float* interleaved_buffer, size_t num_input_frames, size_t num_input_channels, size_t input_frame_offset, size_t output_frame_offset, size_t num_frames_to_copy, AudioBuffer* output);` (scope `vraudio`) — Copies interleaved audio data from a raw float pointer into a planar |AudioBuffer| with a specified output frame offset. Note that the number of output channels is defined by the target |AudioBuffer| instance. @param interleaved_buffer Raw float pointer to interleaved audio data. @param num_input_frames Size of |interleaved_buffer| in frames. @param num_input_channels Number of channels in interleaved audio data. @param input_frame_offset First source frame position in input. @param output_frame_offset First frame destination in output. @param num_frames_to_copy Number of frames per copy. @param output Target output buffer.
- L147 _prototype_ `void FillAudioBufferWithOffset(const int16* interleaved_buffer, size_t num_input_frames, size_t num_input_channels, size_t input_frame_offset, size_t output_frame_offset, size_t num_frames_to_copy, AudioBuffer* output);` (scope `vraudio`) — Copies interleaved audio data from a raw int16 pointer into a planar |AudioBuffer| with a specified output frame offset. Note that the number of output channels is defined by the target |AudioBuffer| instance. @param interleaved_buffer Raw int16 pointer to interleaved audio data. @param num_input_frames Size of |interleaved_buffer| in frames. @param num_input_channels Number of channels in interleaved audio data. @param input_frame_offset First source frame position in input. @param output_frame_offset First frame destination in output. @param num_frames_to_copy Number of frames per copy. @param output Target output buffer.
- L165 _prototype_ `void FillAudioBufferWithOffset(const float* const* planar_ptrs, size_t num_input_frames, size_t num_input_channels, size_t input_frame_offset, size_t output_frame_offset, size_t num_frames_to_copy, AudioBuffer* output);` (scope `vraudio`) — Copies raw planar float audio data into a planar |AudioBuffer| with a specified output frame offset. Note that the number of output channels is defined by the target |AudioBuffer| instance. @param planar_ptrs Pointer to an array of pointers to raw float channel data. @param num_input_frames Size of |interleaved_buffer| in frames. @param num_input_channels Number of channels in interleaved audio data. @param input_frame_offset First source frame position in input. @param output_frame_offset First frame destination in output. @param num_frames_to_copy Number of frames per copy. @param output Target output buffer.
- L183 _prototype_ `void FillAudioBufferWithOffset(const int16* const* planar_ptrs, size_t num_input_frames, size_t num_input_channels, size_t input_frame_offset, size_t output_frame_offset, size_t num_frames_to_copy, AudioBuffer* output);` (scope `vraudio`) — Copies raw planar int16 audio data into a planar |AudioBuffer| with a specified output frame offset. Note that the number of output channels is defined by the target |AudioBuffer| instance. @param planar_ptrs Pointer to an array of pointers to raw int16 channel data. @param num_input_frames Size of |interleaved_buffer| in frames. @param num_input_channels Number of channels in interleaved audio data. @param input_frame_offset First source frame position in input. @param output_frame_offset First frame destination in output. @param num_frames_to_copy Number of frames per copy. @param output Target output buffer.
- L202 _prototype_ `void FillAudioBufferWithChannelRemapping(const int16* interleaved_buffer, size_t num_input_frames, size_t num_input_channels, const std::vector<size_t>& channel_map, AudioBuffer* output);` (scope `vraudio`) — Copies interleaved audio data from a raw int16 pointer into a planar |AudioBuffer|. The |channel_map| argument allows to reorder the channel mapping between the interleaved input and output buffer. The i'th channel in the output buffer corresponds to the |channel_map[i]|'th input channel. Note that the number of output channels and frames is derived from the target |AudioBuffer| instance. @param interleaved_buffer Raw int16 pointer to interleaved audio data. @param num_input_frames Size of interleaved_buffer in frames. @param num_input_channels Number of input channels. @param channel_map Mapping that maps output channels to input channels @param output Target output buffer.
- L220 _prototype_ `void FillAudioBufferWithChannelRemapping(const float* interleaved_buffer, size_t num_input_frames, size_t num_input_channels, const std::vector<size_t>& channel_map, AudioBuffer* output);` (scope `vraudio`) — Copies interleaved audio data from a raw float pointer into a planar |AudioBuffer|. The |channel_map| argument allows to reorder the channel mapping between the interleaved input and output buffer. The i'th channel in the output buffer corresponds to the |channel_map[i]| input channel. Note that the number of output channels and frames is derived from the target |AudioBuffer| instance. @param interleaved_buffer Raw float pointer to interleaved audio data. @param num_input_frames Size of interleaved_buffer in frames. @param num_input_channels Number of input channels. @param channel_map Mapping that maps output channels to input channels @param output Target output buffer.
- L237 _prototype_ `void FillAudioBufferWithChannelRemapping(const float* const* planar_ptr, size_t num_input_frames, size_t num_input_channels, const std::vector<size_t>& channel_map, AudioBuffer* output);` (scope `vraudio`) — Copies raw planar float audio data into a planar |AudioBuffer|. The |channel_map| argument allows to reorder the channel mapping between the planar input and output buffer. The i'th channel in the output buffer corresponds to the |channel_map[i]| input channel. Note that the number of output channels and frames is derived from the target |AudioBuffer| instance. @param planar_ptrs Pointer to an array of pointers to raw float channel data. @param num_input_frames Size of interleaved_buffer in frames. @param num_input_channels Number of input channels. @param channel_map Mapping that maps output channels to input channels @param output Target output buffer.
- L254 _prototype_ `void FillAudioBufferWithChannelRemapping(const int16* const* planar_ptr, size_t num_input_frames, size_t num_input_channels, const std::vector<size_t>& channel_map, AudioBuffer* output);` (scope `vraudio`) — Copies raw planar int16 audio data into a planar |AudioBuffer|. The |channel_map| argument allows to reorder the channel mapping between the planar input and output buffer. The i'th channel in the output buffer corresponds to the |channel_map[i]| input channel. Note that the number of output channels and frames is derived from the target |AudioBuffer| instance. @param planar_ptrs Pointer to an array of pointers to raw int16 channel data. @param num_input_frames Size of interleaved_buffer in frames. @param num_input_channels Number of input channels. @param channel_map Mapping that maps output channels to input channels @param output Target output buffer.
- L266 _prototype_ `void FillExternalBuffer(const AudioBuffer& input, std::vector<float>* output);` (scope `vraudio`) — Copies planar audio data from an |AudioBuffer| to an external interleaved float vector. Note this method resizes the target vector to match number of input samples. @param input Input audio buffer. @param output interleaved output vector.
- L274 _prototype_ `void FillExternalBuffer(const AudioBuffer& input, std::vector<int16>* output);` (scope `vraudio`) — Copies and converts planar audio data from an |AudioBuffer| to an external interleaved int16 vector. Note this method resizes the target vector to match number of input samples. @param input Input audio buffer. @param output interleaved output vector.
- L284 _prototype_ `void FillExternalBuffer(const AudioBuffer& input, float* const* planar_output_ptrs, size_t num_output_frames, size_t num_output_channels);` (scope `vraudio`) — Copies planar audio data from an |AudioBuffer| to an external planar raw float buffer. Note that the input and output buffer must match in terms of number of channels and frames. @param input Input audio buffer. @param planar_output_ptrs Planar output vector. @param num_output_frames Number of frames in output buffer. @param num_output_channels Number of channels in output buffer.
- L296 _prototype_ `void FillExternalBuffer(const AudioBuffer& input, int16* const* planar_output_ptrs, size_t num_output_frames, size_t num_output_channels);` (scope `vraudio`) — Copies and converts audio data from an |AudioBuffer| to an external planar int16 buffer. Note that the input and output buffer must match in terms of number of channels and frames. @param input Input audio buffer. @param planar_output_ptrs Planar output vector. @param num_output_frames Number of frames in output buffer. @param num_output_channels Number of channels in output buffer.
- L308 _prototype_ `void FillExternalBuffer(const AudioBuffer& input, int16* interleaved_output_buffer, size_t num_output_frames, size_t num_output_channels);` (scope `vraudio`) — Copies and converts planar audio data from an |AudioBuffer| to an external interleaved raw int16 buffer. Note that the input and output buffer must match in terms of number of channels and frames. @param input Input audio buffer. @param interleaved_output_buffer Interleaved output vector. @param num_output_frames Number of frames in output buffer. @param num_output_channels Number of channels in output buffer.
- L320 _prototype_ `void FillExternalBuffer(const AudioBuffer& input, float* interleaved_output_buffer, size_t num_output_frames, size_t num_output_channels);` (scope `vraudio`) — Copies planar audio data from an |AudioBuffer| to an external interleaved raw float buffer. Note that the input and output buffer must match in terms of number of channels and frames. @param input Input audio buffer. @param interleaved_output_buffer Interleaved output vector. @param num_output_frames Number of frames in output buffer. @param num_output_channels Number of channels in output buffer.
- L335 _prototype_ `void FillExternalBufferWithOffset(const AudioBuffer& input, size_t input_offset_frames, int16* const* planar_output_ptrs, size_t num_output_frames, size_t num_output_channels, size_t output_offset_frames, size_t num_frames_convert_and_copy);` (scope `vraudio`) — Copies and converts audio data from an |AudioBuffer| to an external planar raw int16 buffer with the ability to specify an offset into the input and output buffer. @param input Input audio buffer. @param input_offset_frames Offset into input buffer in frames. @param planar_output_ptrs Planar output vector. @param num_output_frames Number of frames in output buffer. @param num_output_channels Number of channels in output buffer. @param output_offset_frames Offset into the output buffer in frames. @param num_frames_convert_and_copy Number of frames to be processed.
- L354 _prototype_ `void FillExternalBufferWithOffset(const AudioBuffer& input, size_t input_offset_frames, float* const* planar_output_ptrs, size_t num_output_frames, size_t num_output_channels, size_t output_offset_frames, size_t num_frames_convert_and_copy);` (scope `vraudio`) — Copies audio data from an |AudioBuffer| to an external planar raw float buffer with the ability to specify an offset into the input and output buffer. @param input Input audio buffer. @param input_offset_frames Offset into input buffer in frames. @param planar_output_ptrs Planar output vector. @param num_output_frames Number of frames in output buffer. @param num_output_channels Number of channels in output buffer. @param output_offset_frames Offset into the output buffer in frames. @param num_frames_convert_and_copy Number of frames to be processed.
- L373 _prototype_ `void FillExternalBufferWithOffset(const AudioBuffer& input, size_t input_offset_frames, int16* interleaved_output_buffer, size_t num_output_frames, size_t num_output_channels, size_t output_offset_frames, size_t num_frames_convert_and_copy);` (scope `vraudio`) — Copies and converts audio data from an |AudioBuffer| to an external interleaved raw int16 buffer with the ability to specify an offset into the input and output buffer. @param input Input audio buffer. @param input_offset_frames Offset into input buffer in frames. @param interleaved_output_buffer Interleaved output vector. @param num_output_frames Number of frames in output buffer. @param num_output_channels Number of channels in output buffer. @param output_offset_frames Offset into the output buffer in frames. @param num_frames_convert_and_copy Number of frames to be processed.
- L392 _prototype_ `void FillExternalBufferWithOffset(const AudioBuffer& input, size_t input_offset_frames, float* interleaved_output_buffer, size_t num_output_frames, size_t num_output_channels, size_t output_offset_frames, size_t num_frames_convert_and_copy);` (scope `vraudio`) — Copies and audio data from an |AudioBuffer| to an external interleaved raw float buffer with the ability to specify an offset into the input and output buffer. @param input Input audio buffer. @param input_offset_frames Offset into input buffer in frames. @param interleaved_output_buffer Interleaved output vector. @param num_output_frames Number of frames in output buffer. @param num_output_channels Number of channels in output buffer. @param output_offset_frames Offset into the output buffer in frames. @param num_frames_convert_and_copy Number of frames to be processed.
- L406 _prototype_ `void GetRawChannelDataPointersFromAudioBuffer( AudioBuffer* audio_buffer, std::vector<float*>* channel_ptr_vector);` (scope `vraudio`) — Generates a vector of mutable float pointers to the beginning of each channel buffer in an |AudioBuffer|. The size of the |channel_ptr_vector| output vector must match the number of channels in |audio_buffer|. @param audio_buffer Audio buffer. @param channel_ptr_vector Output std::vector<float*> vector.
- L415 _prototype_ `void GetRawChannelDataPointersFromAudioBuffer( const AudioBuffer& audio_buffer, std::vector<const float*>* channel_ptr_vector);` (scope `vraudio`) — Generates a vector of immutable float pointers to the beginning of each channel buffer in an |AudioBuffer|. The size of the |channel_ptr_vector| output vector must match the number of channels in |audio_buffer|. @param audio_buffer Audio buffer. @param channel_ptr_vector Output std::vector<const float*> vector.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/pseudoinverse.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_PSEUDOINVERSE_H_`
- L22 _namespace_ `namespace vraudio`
- L32 _function_ `Pseudoinverse(const MatrixType& matrix)` (scope `vraudio`)

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/sample_type_conversion.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_SAMPLE_TYPE_CONVERSION_H_`
- L25 _namespace_ `namespace vraudio`
- L28 _function_ `inline void ConvertSampleToFloatFormat(int16 input, float* output)` (scope `vraudio`) — Convert the given int16 to a float in the range [-1.0f, 1.0f].
- L36 _function_ `inline void ConvertSampleToFloatFormat(float input, float* output)` (scope `vraudio`) — Overloaded input argument to support sample type templated methods.
- L42 _function_ `inline void ConvertSampleFromFloatFormat(float input, int16* output)` (scope `vraudio`) — Saturating if the float is not in [-1.0f, 1.0f].
- L56 _function_ `inline void ConvertSampleFromFloatFormat(float input, float* output)` (scope `vraudio`) — Overloaded output argument to support sample type templated methods.
- L62 _prototype_ `void ConvertPlanarSamples(size_t length, const int16* input, float* output);` (scope `vraudio`) — Convert a vector of int16 samples to float format in the range [-1.0f, 1.0f].
- L66 _prototype_ `void ConvertPlanarSamples(size_t length, const float* input, float* output);` (scope `vraudio`) — Overloaded input argument to support sample type templated methods.
- L70 _prototype_ `void ConvertPlanarSamples(size_t length, const float* input, int16* output);` (scope `vraudio`) — Overloaded method to support methods templated against the input sample type.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/semi_lockless_fifo.h` (Private)


#### class `vraudio::SemiLocklessFifo`  
`template <typename DataType> class SemiLocklessFifo`  
_L37-125_
- desc: Thread-safe multiple producer - single consumer FIFO queue to share data between threads. The FIFO takes over ownership of the queue elements. Note that |PushBack| calls are synchronized with a mutex and may block. Calls to |PopFront| are lockless and never block. @tparam DataType Object type that the FIFO handles.
- L39 _public typedef_ `typedef std::chrono::steady_clock::duration ClockDuration;`
- L41 _public prototype_ `SemiLocklessFifo();`
- L43 _public prototype_ `~SemiLocklessFifo();`
- L48 _public prototype_ `void PushBack(DataType&& input);` — Takes over ownership of |input| and pushes it to the FIFO queue back. @param input Input element to be added to the FIFO queue.
- L54 _public prototype_ `DataType PopFront();` — Pops element from FIFO queue front. @return Element from FIFO queue front. Must not be called if the queue is empty.
- L58 _public prototype_ `bool Empty() const;` — Returns true if FIFO queue is empty, false otherwise. This method is *not* thread-safe and should only be called from the consumer thread.
- L62 _public prototype_ `void Clear();` — Clears the FIFO queue and deletes all its elements. This method is *not* thread-safe and should only be called from the consumer thread.
- L72 _public prototype_ `bool SleepUntilBelowSizeTarget(size_t target_size, const ClockDuration& max_wait);` — Sleeps until the number of elements in the FIFO queue drop below a target threshold. This method can be used to synchronize the producer and the consumer. Sleeping is enabled by default and can be disabled via |EnableBlockingSleepUntilMethods|. @param target_size Target size of FIFO queue. @param max_wait Maximum waiting period. @return True if number of FIFO elements is below target size.
- L84 _public prototype_ `bool SleepUntilNumElementsInQueue(size_t target_size, const ClockDuration& max_wait);` — Sleeps until the number of elements in the FIFO queue is greater or equal a target threshold. This method can be used to synchronize the producer and the consumer. Sleeping is enabled by default and can be disabled via |EnableBlockingSleepUntilMethods|. @param target_size Target size of FIFO queue. @param max_wait Maximum waiting period. @return True if number of FIFO elements is greater or equal the target size.
- L89 _public prototype_ `void EnableBlockingSleepUntilMethods(bool enable);` — Allows for unblocking |SleepUntil[BelowSizeTarget|NumElementsInQueue]| method.
- L100 _private member_ `Node* head_;` — Head of linked list.
- L103 _private member_ `Node* tail_;` — Tail of linked list.
- L106 _private member_ `std::atomic<size_t> fifo_size_;` — Number of elements.
- L109 _private member_ `std::mutex push_mutex_;` — Mutex to synchronize |PushBack| calls from multiple threads.
- L112 _private member_ `std::condition_variable pop_conditional_;` — Conditional to signal consumption.
- L115 _private member_ `std::mutex pop_conditional_mutex_;` — Mutex to block on until signal consumption occurs.
- L118 _private member_ `std::condition_variable push_conditional_;` — Conditional to signal new elements on the FIFO.
- L121 _private member_ `std::mutex push_conditional_mutex_;` — Mutex to block on until new elements have been added to the FIFO.
- L124 _private member_ `std::atomic<bool> enable_sleeping_;` — Flag to enable and disable blocking sleeping calls.
- L128 _function_ `template <typename DataType> SemiLocklessFifo<DataType>::SemiLocklessFifo() : fifo_size_(0), enable_sleeping_(true)`
- L134 _function_ `template <typename DataType> SemiLocklessFifo<DataType>::~SemiLocklessFifo()`
- L142 _function_ `template <typename DataType> void SemiLocklessFifo<DataType>::PushBack(DataType&& input)`
- L161 _function_ `template <typename DataType> DataType SemiLocklessFifo<DataType>::PopFront()`
- L184 _function_ `template <typename DataType> bool SemiLocklessFifo<DataType>::Empty() const`
- L189 _function_ `template <typename DataType> void SemiLocklessFifo<DataType>::Clear()`
- L197 _function_ `template <typename DataType> bool SemiLocklessFifo<DataType>::SleepUntilBelowSizeTarget( size_t target_size, const ClockDuration& max_wait)`
- L208 _function_ `template <typename DataType> bool SemiLocklessFifo<DataType>::SleepUntilNumElementsInQueue( size_t target_size, const ClockDuration& max_wait)`
- L219 _function_ `template <typename DataType> void SemiLocklessFifo<DataType>::EnableBlockingSleepUntilMethods(bool enable)`

#### struct `vraudio::SemiLocklessFifo::Node`  
`struct Node`  
_L93-97_
- desc: Node in single-linked list.
- L94 _public function_ `Node() : next(nullptr)`
- L95 _public member_ `std::atomic<Node*> next;`
- L96 _public member_ `DataType data;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_SEMI_LOCKLESS_FIFO_H_`
- L28 _namespace_ `namespace vraudio`
- L201 _function_ `pop_conditional_.wait_for(lock, max_wait, [this, target_size]() { return fifo_size_ < target_size || !enable_sleeping_.load(); });` (scope `vraudio::SemiLocklessFifo::SleepUntilBelowSizeTarget`)
- L212 _function_ `push_conditional_.wait_for(lock, max_wait, [this, target_size]() { return fifo_size_ >= target_size || !enable_sleeping_.load(); });` (scope `vraudio::SemiLocklessFifo::SleepUntilNumElementsInQueue`)

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/sum_and_difference_processor.h` (Private)


#### class `vraudio::SumAndDifferenceProcessor`  
`class SumAndDifferenceProcessor`  
_L27-40_
- desc: Class which converts a 2-channel input audio buffer into its sum and difference signals and stores them in the left and right channel respectively.
- L32 _public prototype_ `explicit SumAndDifferenceProcessor(size_t num_frames);` — Constructs a stereo sum and difference processor. @param num_frames Number of frames in the stereo input audio buffer.
- L35 _public prototype_ `void Process(AudioBuffer* stereo_buffer);` — Converts a 2-channel buffer signals into their sum and difference.
- L39 _private member_ `AudioBuffer temp_buffer_;` — Temporary audio buffer to store left channel input data during conversion.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_SUM_AND_DIFFERENCE_PROCESSOR_H_`
- L22 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/task_thread_pool.h` (Private)


#### class `vraudio::TaskThreadPool`  
`class TaskThreadPool`  
_L57-138_
- desc: A very basic thread pool for launching discrete encapsulated task functions on a configurable number of task threads. Note that this pool expects tasks to complete their work with no management by the pool itself. Any means of managing or terminating tasks must be designed into the task contexts and managed externally in a thread-safe way.
- L64 _public typedef_ `typedef std::function<void()> TaskClosure;` — Type definition for task function which may be assigned to a |WorkerThread| in this pool. Note that tasks should be self-contained and not require communication with other tasks.
- L68 _public prototype_ `TaskThreadPool();` — Constructor.
- L70 _public prototype_ `~TaskThreadPool();`
- L78 _public prototype_ `bool StartThreadPool(size_t num_worker_threads);` — Creates and initializes thread pool. This method blocks until all threads are loaded and initialized. @param num_worker_threads The number of worker threads to make available in the pool. @return true on success or if thread pool has been already started.
- L81 _public prototype_ `void StopThreadPool();` — Signals all |WorkerThread|s to stop and waits for completion.
- L88 _public prototype_ `bool WaitUntilWorkerBecomesAvailable();` — Waits until a |WorkerThread| becomes available. It is assumed that only a single thread will dispatch threads using this function, and therefore this function should not itself be considered thread safe. @return True if a |WorkerThread| is available.
- L98 _public prototype_ `bool RunOnWorkerThread(TaskClosure closure);` — Executes a |TaskClosure| on a |WorkerThread|. It is assumed that only a signal thread will dispatch threads using this function, and therefore this function should not itself be considered thread safe. @param closure The client task which will begin execution if and when this function returns True. @return True if a |WorkerThread| is allocated to execute the closure function, false if no |WorkerThread| is available.
- L101 _public prototype_ `size_t GetAvailableTaskThreadCount() const;` — Query the number of |WorkerThread|s current available to do work.
- L111 _private prototype_ `bool IsPoolRunning();` — Query whether the |TaskThreadPool| is active. @return True if the pool is still running.
- L115 _private prototype_ `void SignalWorkerAvailable();` — Signals to thread pool that a worker thread has become available for task assignment.
- L118 _private prototype_ `void WorkerLoopFunction();` — Closure reusable task loop to be executed by each |WorkerThread|.
- L121 _private prototype_ `void WorkerThreadLoop();` — Task Loop executed by each worker thread.
- L124 _private member_ `std::atomic<int> num_worker_threads_available_;` — Number of worker threads currently available to execute tasks.
- L127 _private member_ `std::atomic<bool> is_pool_running_;` — Control of all worker thread loops.
- L131 _private member_ `std::vector<WorkerThread> worker_threads_;`
- L134 _private member_ `std::condition_variable worker_available_condition_;` — Condition to indicate that a worker thread has become available.
- L137 _private member_ `std::mutex worker_available_mutex_;` — Mutex for the worker thread available condition notification receiver.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_TASK_THREAD_POOL_H_`
- L48 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/threadsafe_fifo.h` (Private)


#### class `vraudio::ThreadsafeFifo`  
`template <typename T> class ThreadsafeFifo`  
_L37-121_
- desc: Container to share preallocated data between threads. It is thread-safe for single producer - single consumer FIFO usage. @tparam T Object type that the FIFO handles.
- L45 _public prototype_ `explicit ThreadsafeFifo(size_t max_objects);` — Constructor preallocates the maximum number of objects in the FIFO queue and defines the maximum waiting period before triggering a buffer underflow or overflow event. Sleeping is enabled by default and can be disabled via |EnableBlockingSleepUntilMethods|. @param max_objects Maximum number of objects in FIFO queue.
- L53 _public prototype_ `ThreadsafeFifo(size_t max_objects, const T& init);` — Constructor preallocates the maximum number of objects in the FIFO queue. Sleeping is enabled by default and can be disabled via |EnableBlockingSleepUntilMethods|. @param max_objects Maximum number of objects in FIFO queue. @param init Initializer to be assigned to allocated objects.
- L60 _public prototype_ `T* AcquireInputObject();` — Returns a pointer to an available input object T. If the queue is full, a nullptr is returned. @return Pointer to an available input object. Nullptr if no input object is available.
- L64 _public prototype_ `void ReleaseInputObject(const T* object);` — Releases a previously acquired input object to be pushed onto the FIFO front.
- L70 _public prototype_ `T* AcquireOutputObject();` — Returns a pointer to an output object T. If the queue is empty, a nullptr is returned. @return Pointer to the output object. Nullptr on empty queue.
- L73 _public prototype_ `void ReleaseOutputObject(const T* object);` — Releases a previously acquired output object back to the FIFO.
- L79 _public prototype_ `bool SleepUntilInputObjectIsAvailable() const;` — Blocks until the FIFO queue has an input object available or |EnableBlockingSleepUntilMethods(false)| is called. Returns true if free slot is available.
- L85 _public prototype_ `bool SleepUntilOutputObjectIsAvailable() const;` — Blocks until the FIFO queue has an output object available or |EnableBlockingSleepUntilMethods(false)| is called. Returns true if an object is available.
- L89 _public prototype_ `void EnableBlockingSleepUntilMethods(bool enable);` — Allows for unblocking |SleepUntil[Input|Output]ObjectIsAvailable| method.
- L92 _public prototype_ `size_t Size() const;` — Returns the number of objects in the FIFO queue.
- L95 _public prototype_ `bool Empty() const;` — Returns true if FIFO queue is empty, false otherwise.
- L98 _public prototype_ `bool Full() const;` — Returns true if FIFO queue is full, false otherwise.
- L102 _public prototype_ `void Clear();` — Clears the FIFO queue. This call is only thread-safe if called by the consumer.
- L106 _private member_ `mutable std::mutex fifo_empty_mutex_;` — Conditional to signal empty/full queue events.
- L107 _private member_ `mutable std::condition_variable fifo_empty_conditional_;`
- L109 _private member_ `mutable std::mutex fifo_full_mutex_;`
- L110 _private member_ `mutable std::condition_variable fifo_full_conditional_;`
- L113 _private member_ `std::vector<T> fifo_;` — Vector that stores all objects.
- L114 _private member_ `size_t read_pos_;`
- L115 _private member_ `size_t write_pos_;`
- L118 _private member_ `std::atomic<size_t> fifo_size_;` — Atomic counter that reflects the size of |fifo_|.
- L120 _private member_ `std::atomic<bool> enable_sleeping_;`
- L124 _function_ `template <typename T> ThreadsafeFifo<T>::ThreadsafeFifo(size_t max_objects) : fifo_(max_objects), read_pos_(0), write_pos_(0), fifo_size_(0), enable_sleeping_(true)`
- L134 _function_ `template <typename T> ThreadsafeFifo<T>::ThreadsafeFifo(size_t max_objects, const T& init) : ThreadsafeFifo(max_objects)`
- L142 _function_ `template <typename T> T* ThreadsafeFifo<T>::AcquireInputObject()`
- L153 _function_ `template <typename T> void ThreadsafeFifo<T>::ReleaseInputObject(const T* object)`
- L171 _function_ `template <typename T> T* ThreadsafeFifo<T>::AcquireOutputObject()`
- L180 _function_ `template <typename T> void ThreadsafeFifo<T>::ReleaseOutputObject(const T* object)`
- L199 _function_ `template <typename T> bool ThreadsafeFifo<T>::SleepUntilInputObjectIsAvailable() const`
- L210 _function_ `template <typename T> bool ThreadsafeFifo<T>::SleepUntilOutputObjectIsAvailable() const`
- L220 _function_ `template <typename T> void ThreadsafeFifo<T>::EnableBlockingSleepUntilMethods(bool enable)`
- L232 _function_ `template <typename T> size_t ThreadsafeFifo<T>::Size() const`
- L237 _function_ `template <typename T> bool ThreadsafeFifo<T>::Empty() const`
- L242 _function_ `template <typename T> bool ThreadsafeFifo<T>::Full() const`
- L247 _function_ `template <typename T> void ThreadsafeFifo<T>::Clear()`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_THREADSAFE_FIFO_H_`
- L30 _namespace_ `namespace vraudio`
- L203 _function_ `fifo_full_conditional_.wait(lock, [this]() { return fifo_size_.load() < fifo_.size() || !enable_sleeping_.load(); });` (scope `vraudio::ThreadsafeFifo::SleepUntilInputObjectIsAvailable`)
- L213 _function_ `fifo_empty_conditional_.wait(lock, [this]() { return fifo_size_.load() > 0 || !enable_sleeping_.load(); });` (scope `vraudio::ThreadsafeFifo::SleepUntilOutputObjectIsAvailable`)

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/vorbis_stream_encoder.h` (Private)


#### class `vraudio::VorbisStreamEncoder`  
`class VorbisStreamEncoder`  
_L51-131_
- L62 _public prototype_ `VorbisStreamEncoder();`
- L77 _public prototype_ `bool InitializeForFile(const std::string& filename, size_t num_channels, int sample_rate, EncodingMode encoding_mode, int bitrate, float quality);` — Initializes Vorbis encoding. @param filename Ogg vorbis output file. If it doesn't exist, it will be created. Existing files will be overwritten. @param num_channels Number of input channels. @param sample_rate Sample rate of input audio buffers. @param encoding_mode Selects variable (VBR) or average encoding (ABR). @param bitrate Target bitrate (only used when selecting ABR encoding). @param quality Target quality (only used when selecting VBR encoding). The usable range is -.1 (lowest quality, smallest file) to 1. (highest quality, largest file). @return False in case of file I/O errors or libvorbis initialization failures like non-supported channel/sample rate configuration.
- L87 _public prototype_ `bool AddPlanarBuffer(const float* const* input_ptrs, size_t num_channels, size_t num_frames);` — Feeds input audio data into libvorbis encoder and triggers encoding. @param Array of pointers to planar channel data. @param num_channels Number of input channels. @param num_frames Number of input frames. @return False in case of file I/O errors or missing encoder initialization.
- L93 _public prototype_ `bool FlushAndClose();` — Flushes the remaining audio buffers and closes the output file. @return False in case of file I/O errors or missing encoder initialization.
- L101 _private prototype_ `void PrepareVorbisBuffer(const float* const* input_ptrs, size_t num_channels, size_t num_frames);` — Copies input audio data into libvorbis encoder buffer. @param Array of pointers to planar channel data. @param num_channels Number of input channels. @param num_frames Number of input frames.
- L108 _private prototype_ `bool PerformEncoding();` — Performs encoding of audio data prepared via |PrepareVorbisBuffer| or when the end of stream has been signaled. @return False in case of file I/O errors or missing encoder initialization.
- L113 _private prototype_ `bool WriteOggPage();` — Dumps data from |ogg_page_| struct to |output_file_stream_|. @return False in case of file I/O errors or missing encoder initialization.
- L116 _private member_ `bool init_;` — Flag indicating if encoder has been successfully initialized.
- L119 _private member_ `std::ofstream output_file_stream_;` — Output file stream.
- L122 _private member_ `ogg_stream_state stream_state_;` — libogg structs.
- L123 _private member_ `ogg_page ogg_page_;`
- L124 _private member_ `ogg_packet ogg_packet_;`
- L127 _private member_ `vorbis_info vorbis_info_;` — libvorbis structs.
- L128 _private member_ `vorbis_comment vorbis_comment_;`
- L129 _private member_ `vorbis_dsp_state vorbis_state_;`
- L130 _private member_ `vorbis_block vorbis_block_;`

#### enum `vraudio::VorbisStreamEncoder::EncodingMode`  
`enum class EncodingMode`  
_L54-60_
- desc: Supported encoding modes.
- L55 _public enumerator_ `kUndefined`
- L57 _public enumerator_ `kVariableBitRate` — Variable bit rate mode (VBR).
- L59 _public enumerator_ `kAverageBitRate` — Average bit rate mode (ABR).

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_VORBIS_STREAM_ENCODER_H_`
- L49 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/wav.h` (Private)


#### class `vraudio::Wav`  
`class Wav`  
_L27-62_
- desc: Wraps WavReader class to decode a wav file into memory.
- L29 _public prototype_ `~Wav();`
- L32 _public prototype_ `static std::unique_ptr<const Wav> CreateOrNull(const unsigned char* byte_array, size_t array_size);` — Reads a RIFF WAVE from a byte array.
- L35 _public function_ `const std::vector<int16_t>& interleaved_samples() const` — Returns reference to interleaved samples.
- L40 _public function_ `size_t GetNumChannels() const` — Returns number of channels.
- L43 _public function_ `int GetSampleRateHz() const` — Returns sample rate.
- L51 _private prototype_ `Wav(size_t num_channels, int sample_rate, std::vector<int16_t>&& interleaved_samples);` — Private constructor used by static factory methods. @param num_channels Number of audio channels. @param sample_rate Sample rate. @param interleaved_samples Decoded interleaved samples.
- L55 _private member_ `size_t num_channels_;` — Number of channels.
- L58 _private member_ `int sample_rate_;` — Sample rate.
- L61 _private member_ `std::vector<int16_t> interleaved_samples_;` — Interleaved samples.

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_WAV_H_`
- L24 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/resonance_audio/utils/wav_reader.h` (Private)


#### class `vraudio::WavReader`  
`class WavReader`  
_L30-117_
- desc: Basic RIFF WAVE decoder that supports multichannel 16-bit PCM.
- L37 _public prototype_ `explicit WavReader(const unsigned char* byte_array, const size_t num_bytes);` — Constructor that takes a pointer to a raw byte array and the size of that byte stream. @param byte_array Pointer to raw array of bytes. @param num_bytes Size of byte_array.
- L40 _public prototype_ `bool IsHeaderValid() const;` — True if WAV header was successfully parsed.
- L44 _public prototype_ `size_t GetNumTotalSamples() const;` — Returns the total number of samples defined in the WAV header. Note that the actual number of samples in the file can differ.
- L47 _public prototype_ `size_t GetNumChannels() const;` — Returns number of channels.
- L50 _public prototype_ `int GetSampleRateHz() const;` — Returns sample rate in Hertz.
- L58 _public prototype_ `int64 SeekToFrame(const uint64 frame_position);` — Seek to a specific frame position within the wave file. If frame_position is not a valid address, then the internal read position remains unchanged. @param frame_position Destination frame position for play cursor. @return Actual frame position of cursor after this seek operation. A negative return value indicates a stream failure.
- L65 _public prototype_ `size_t ReadSamples(size_t num_samples, int16_t* target_buffer);` — Reads samples from WAV file into target buffer. @param num_samples Number of samples to read. @param target_buffer Target buffer to write to. @return Number of decoded samples.
- L71 _private prototype_ `bool ParseHeader();` — Parses WAV header. @return True on success.
- L78 _private prototype_ `size_t ReadBinaryDataFromStream(void* target_ptr, size_t size);` — Helper method to read binary data from input stream. @param size Number of bytes to read. @param target_ptr Target buffer to write to. @return Number of bytes read.
- L95 _private member_ `SourceByteArray source;` — source we are deserializing.
- L98 _private member_ `bool init_;` — Flag indicating if the WAV header was parsed successfully.
- L101 _private member_ `size_t num_channels_;` — Number of audio channels.
- L104 _private member_ `int sample_rate_hz_;` — Sample rate in Hertz.
- L107 _private member_ `size_t num_total_samples_;` — Total number of samples.
- L110 _private member_ `size_t num_remaining_samples_;` — Number of remaining samples in WAV file.
- L113 _private member_ `size_t bytes_per_sample_;` — Bytes per sample as defined in the WAV header.
- L116 _private member_ `uint64 pcm_offset_bytes_;` — Offset into data stream where PCM data begins.

#### struct `vraudio::WavReader::SourceByteArray`  
`struct SourceByteArray`  
_L80-92_
- L82 _public member_ `const unsigned char* byte_array;`
- L83 _public member_ `const size_t num_bytes;`
- L84 _public member_ `size_t current_byte_index;`
- L86 _public function_ `SourceByteArray(const unsigned char* in_byte_array, const size_t in_num_bytes) : byte_array(in_byte_array) , num_bytes(in_num_bytes) , current_byte_index(0)`

#### Free symbols / members of external scopes

- L18 _macro_ `#define RESONANCE_AUDIO_UTILS_WAV_READER_H_`
- L27 _namespace_ `namespace vraudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/third_party/SADIE_hrtf_database/generated/hrtf_assets.h` (Private)


#### Free symbols / members of external scopes

- L18 _macro_ `#define THIRD_PARTY_SADIE_HRTF_DATABASE_GENERATED_HRTF_ASSETS_H_`
- L25 _namespace_ `namespace sadie`
- L28 _namespace_ `namespace HrtfAssets` (scope `sadie`)
- L34 _prototype_ `const unsigned char* GetFile(const std::string& filename, size_t& out_file_size);` (scope `sadie::HrtfAssets`) — Lookups and retrieves a file from an asset class. @param filename: Filename to be retrieved. @return std::string with raw file data. In case of an error, a nullptr is returned. Caller must take over the ownership of the returned data.

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/third_party/pfft/fftpack.h` (Private)


#### Free symbols / members of external scopes

- L46 _macro_ `#define FFTPACK_H`
- L55 _typedef_ `typedef float fftpack_real;`
- L56 _typedef_ `typedef int fftpack_int;`
- L62 _prototype_ `void cffti(fftpack_int n, fftpack_real *wsave);`
- L64 _prototype_ `void cfftf(fftpack_int n, fftpack_real *c, fftpack_real *wsave);`
- L66 _prototype_ `void cfftb(fftpack_int n, fftpack_real *c, fftpack_real *wsave);`
- L68 _prototype_ `void rffti(fftpack_int n, fftpack_real *wsave);`
- L69 _prototype_ `void rfftf(fftpack_int n, fftpack_real *r, fftpack_real *wsave);`
- L70 _prototype_ `void rfftb(fftpack_int n, fftpack_real *r, fftpack_real *wsave);`
- L72 _prototype_ `void cosqi(fftpack_int n, fftpack_real *wsave);`
- L73 _prototype_ `void cosqf(fftpack_int n, fftpack_real *x, fftpack_real *wsave);`
- L74 _prototype_ `void cosqb(fftpack_int n, fftpack_real *x, fftpack_real *wsave);`
- L76 _prototype_ `void costi(fftpack_int n, fftpack_real *wsave);`
- L77 _prototype_ `void cost(fftpack_int n, fftpack_real *x, fftpack_real *wsave);`
- L79 _prototype_ `void sinqi(fftpack_int n, fftpack_real *wsave);`
- L80 _prototype_ `void sinqb(fftpack_int n, fftpack_real *x, fftpack_real *wsave);`
- L81 _prototype_ `void sinqf(fftpack_int n, fftpack_real *x, fftpack_real *wsave);`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioLibrary/third_party/pfft/pffft.h` (Private)


#### enum `(anonymous)`  
`typedef enum`  
_L93-93_
- desc: direction of the transform

#### enum `(anonymous)`  
`typedef enum`  
_L96-96_
- desc: type of transform

#### Free symbols / members of external scopes

- L78 _macro_ `#define PFFFT_H`
- L90 _typedef_ `typedef struct PFFFT_Setup PFFFT_Setup;` — opaque struct holding internal stuff (precomputed twiddle factors) this struct can be shared by many threads as it contains only read-only data.
- L93 _enumerator_ `typedef enum { PFFFT_FORWARD, PFFFT_BACKWARD } pffft_direction_t; typedef enum { PFFFT_REAL, PFFFT_COMPLEX } pffft_transform_t; /* prepare for performing transforms of size N -- the returned PFFFT_Setup structure is read-only so it can safely be shared by` (scope `__anonfd28491a0103`) — direction of the transform
- L93 _enumerator_ `typedef enum { PFFFT_FORWARD, PFFFT_BACKWARD } pffft_direction_t; typedef enum { PFFFT_REAL, PFFFT_COMPLEX } pffft_transform_t; /* prepare for performing transforms of size N -- the returned PFFFT_Setup structure is read-only so it can safely be shared by` (scope `__anonfd28491a0103`) — direction of the transform
- L93 _typedef_ `typedef enum { PFFFT_FORWARD, PFFFT_BACKWARD } pffft_direction_t;` — direction of the transform
- L96 _enumerator_ `typedef enum { PFFFT_REAL, PFFFT_COMPLEX } pffft_transform_t; /* prepare for performing transforms of size N -- the returned PFFFT_Setup structure is read-only so it can safely be shared by multiple concurrent threads. */ PFFFT_Setup *pffft_new_setup(int N, pffft_transform_t transform);` (scope `__anonfd28491a0203`) — type of transform
- L96 _enumerator_ `typedef enum { PFFFT_REAL, PFFFT_COMPLEX } pffft_transform_t; /* prepare for performing transforms of size N -- the returned PFFFT_Setup structure is read-only so it can safely be shared by multiple concurrent threads. */ PFFFT_Setup *pffft_new_setup(int N, pffft_transform_t transform);` (scope `__anonfd28491a0203`) — type of transform
- L96 _typedef_ `typedef enum { PFFFT_REAL, PFFFT_COMPLEX } pffft_transform_t;` — type of transform
- L103 _prototype_ `PFFFT_Setup *pffft_new_setup(int N, pffft_transform_t transform);` — prepare for performing transforms of size N -- the returned PFFFT_Setup structure is read-only so it can safely be shared by multiple concurrent threads.
- L104 _prototype_ `void pffft_destroy_setup(PFFFT_Setup *);`
- L123 _prototype_ `void pffft_transform(PFFFT_Setup *setup, const float *input, float *output, float *work, pffft_direction_t direction);` — Perform a Fourier transform , The z-domain data is stored in the most efficient order for transforming it back, or using it for convolution. If you need to have its content sorted in the "usual" way, that is as an array of interleaved complex numbers, either use pffft_transform_ordered , or call pffft_zreorder after the forward fft, and before the backward fft. Transforms are not scaled: PFFFT_BACKWARD(PFFFT_FORWARD(x)) = N*x. Typically you will want to scale the backward transform by 1/N. The 'work' pointer should point to an area of N (2*N for complex fft) floats, properly aligned. If 'work' is NULL, then stack will be used instead (this is probably the best strategy for small FFTs, say for N < 16384). input and output may alias.
- L132 _prototype_ `void pffft_transform_ordered(PFFFT_Setup *setup, const float *input, float *output, float *work, pffft_direction_t direction);` — Similar to pffft_transform, but makes sure that the output is ordered as expected (interleaved complex numbers).  This is similar to calling pffft_transform and then pffft_zreorder. input and output may alias.
- L146 _prototype_ `void pffft_zreorder(PFFFT_Setup *setup, const float *input, float *output, pffft_direction_t direction);` — call pffft_zreorder(.., PFFFT_FORWARD) after pffft_transform(..., PFFFT_FORWARD) if you want to have the frequency components in the correct "canonical" order, as interleaved complex numbers. (for real transforms, both 0-frequency and half frequency components, which are real, are assembled in the first entry as F(0)+i*F(n/2+1). Note that the original fftpack did place F(n/2+1) at the end of the arrays). input and output should not alias.
- L160 _prototype_ `void pffft_zconvolve_accumulate(PFFFT_Setup *setup, const float *dft_a, const float *dft_b, float *dft_ab, float scaling);` — Perform a multiplication of the frequency components of dft_a and dft_b and accumulate them into dft_ab. The arrays should have been obtained with pffft_transform(.., PFFFT_FORWARD) and should not* have been reordered with pffft_zreorder (otherwise just perform the operation yourself as the dft coefs are stored as interleaved complex numbers). the operation performed is: dft_ab += (dft_a * fdt_b)*scaling The dft_a, dft_b and dft_ab pointers may alias.
- L167 _prototype_ `void *pffft_aligned_malloc(size_t nb_bytes);` — the float buffers must have the correct alignment (16-byte boundary on intel and powerpc). This function may be used to obtain such correctly aligned buffers.
- L168 _prototype_ `void pffft_aligned_free(void *);`
- L171 _prototype_ `int pffft_simd_size();` — return 4 or 1 wether support SSE/Altivec instructions was enable when building pffft.c

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioModule.h` (Private)


#### class `ResonanceAudio::FSpatializationPluginFactory`  
`class FSpatializationPluginFactory : public IAudioSpatializationFactory`  
_L19-46_
- inherits: `IAudioSpatializationFactory`
- desc: /
- L23 _public function_ `virtual FString GetDisplayName() override`
- L29 _public function_ `virtual bool SupportsPlatform(const FString& PlatformName) override`
- L34 _public prototype_ `virtual TAudioSpatializationPtr CreateNewSpatializationPlugin(FAudioDevice* OwningDevice) override;`
- L35 _public function_ `virtual UClass* GetCustomSpatializationSettingsClass() const override`
- L37 _public function_ `virtual bool IsExternalSend() override`
- L39 _public function_ `virtual int32 GetMaxSupportedChannels() override`
- L44 _public function_ `virtual bool ReturnsToSubmixGraph() const override`

#### class `ResonanceAudio::FReverbPluginFactory`  
`class FReverbPluginFactory : public IAudioReverbFactory`  
_L51-69_
- inherits: `IAudioReverbFactory`
- desc: /
- L55 _public function_ `virtual FString GetDisplayName() override`
- L61 _public function_ `virtual bool SupportsPlatform(const FString& PlatformName) override`
- L66 _public prototype_ `virtual TAudioReverbPtr CreateNewReverbPlugin(FAudioDevice* OwningDevice) override;`
- L67 _public function_ `virtual bool IsExternalSend() override`
- L68 _public function_ `virtual bool ReturnsToSubmixGraph() const override`

#### class `ResonanceAudio::FResonanceAudioModule`  
`class FResonanceAudioModule : public IResonanceAudioModule`  
_L74-115_
- inherits: `IResonanceAudioModule`
- desc: /
- L77 _public prototype_ `FResonanceAudioModule();`
- L78 _public prototype_ `~FResonanceAudioModule();`
- L80 _public prototype_ `virtual void StartupModule() override;`
- L81 _public prototype_ `virtual void ShutdownModule() override;`
- L84 _public prototype_ `IAudioPluginFactory* GetPluginFactory(EAudioPlugin PluginType);` — Returns a pointer to a given PluginType or nullptr if PluginType is invalid.
- L87 _public prototype_ `void RegisterAudioDevice(FAudioDevice* AudioDeviceHandle);` — Registers given audio device with the Resonance Audio module.
- L90 _public prototype_ `void UnregisterAudioDevice(FAudioDevice* AudioDeviceHandle);` — Unregisters given audio device from the Resonance Audio module.
- L93 _public function_ `TArray<FAudioDevice*>& GetRegisteredAudioDevices()` — Get all registered Audio Devices that are using Resonance Audio as their reverb plugin.
- L96 _public function_ `static void* GetResonanceAudioDynamicLibraryHandle()` — Returns Resonance Audio API dynamic library handle.
- L99 _public prototype_ `static UResonanceAudioSpatializationSourceSettings* GetGlobalSpatializationSourceSettings();` — Returns the global spatialization source settings set in the project settings
- L103 _private member_ `static void* ResonanceAudioDynamicLibraryHandle;` — Resonance Audio API dynamic library handle.
- L106 _private member_ `static UResonanceAudioSpatializationSourceSettings* GlobalSpatializationSourceSettings;` — The global resonance audio spatialization source settings
- L109 _private member_ `TArray<FAudioDevice*> RegisteredAudioDevices;` — List of registered audio devices.
- L112 _private member_ `FSpatializationPluginFactory SpatializationPluginFactory;` — Plugin factories.
- L113 _private member_ `FReverbPluginFactory ReverbPluginFactory;`
- L114 _private member_ `FAmbisonicsFactory AmbisonicsFactory;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace ResonanceAudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioPluginListener.h` (Private)


#### class `ResonanceAudio::FResonanceAudioPluginListener`  
`class FResonanceAudioPluginListener : public IAudioPluginListener`  
_L19-50_
- inherits: `IAudioPluginListener`
- desc: Dispatches listener information to the Resonance Audio plugins and owns the vraudio::ResonanceAudioApi.
- L23 _public prototype_ `FResonanceAudioPluginListener();`
- L24 _public prototype_ `~FResonanceAudioPluginListener();`
- L26 _public prototype_ `virtual void OnListenerInitialize(FAudioDevice* AudioDevice, UWorld* ListenerWorld) override;`
- L27 _public prototype_ `virtual void OnListenerUpdated(FAudioDevice* AudioDevice, const int32 ViewportIndex, const FTransform& ListenerTransform, const float InDeltaSeconds) override;`
- L28 _public prototype_ `virtual void OnListenerShutdown(FAudioDevice* AudioDevice) override;`
- L29 _public prototype_ `virtual void OnTick(UWorld* InWorld, const int32 ViewportIndex, const FTransform& ListenerTransform, const float InDeltaSeconds) override;`
- L31 _public prototype_ `static FResonanceAudioApiSharedPtr GetResonanceAPIForAudioDevice(const FAudioDevice* InAudioDevice);`
- L32 _public prototype_ `static void SetResonanceAPIForAudioDevice(const FAudioDevice* InAudioDevice, FResonanceAudioApiSharedPtr InResonanceSystem);`
- L33 _public prototype_ `static void RemoveResonanceAPIForAudioDevice(const FAudioDevice* InAudioDevice);`
- L34 _public prototype_ `static void RemoveResonanceAPIForAudioDevice(const vraudio::ResonanceAudioApi* InResonanceSystem);`
- L38 _private member_ `FResonanceAudioApiSharedPtr ResonanceAudioApi;` — Resonance Audio API instance.
- L41 _private member_ `static TMap<const FAudioDevice*, FResonanceAudioApiSharedPtr> ResonanceApiMap;` — Map of Resonance API systems to Audio Device IDs.
- L42 _private member_ `static FCriticalSection ResonanceApiMapCriticalSection;`
- L45 _private member_ `const FAudioDevice* OwningAudioDevice;` — This audio device ptr should only be used to remove the ResonanceAudioApi* from the ResonanceApiMap on destruction.
- L47 _private member_ `class FResonanceAudioModule* ResonanceAudioModule;`
- L48 _private member_ `class FResonanceAudioReverb* ReverbPtr;`
- L49 _private member_ `class FResonanceAudioSpatialization* SpatializationPtr;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace ResonanceAudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioPrivatePCH.h` (Private)
_(no declarations extracted)_

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioReverb.h` (Private)


#### struct `FResonanceAudioReverbPluginSettings`  
`struct FResonanceAudioReverbPluginSettings`  
_L20-102_
- reflection: `USTRUCT(BlueprintType)`
- L26 _public member_ `bool bEnableRoomEffects;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")` — Whether Resonance Audio room effects are enabled
- L31 _public member_ `bool bGetTransformFromAudioVolume = false;` — `UPROPERTY(EditAnywhere, Category = "Room Transform")` — Whether the room transform should be taken from the Audio Volume this preset is attached to. If not used with the Audio Volume, last saved values will be used.
- L35 _public member_ `FVector RoomPosition;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Transform", meta = (EditCondition = "!bGetTransformFromAudioVolume"))` — Room position in 3D space
- L39 _public member_ `FQuat RoomRotation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Transform", meta = (EditCondition = "!bGetTransformFromAudioVolume"))` — Room rotation in 3D space
- L43 _public member_ `FVector RoomDimensions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Room Transform", meta = (EditCondition = "!bGetTransformFromAudioVolume"))` — Room dimensions in 3D space
- L47 _public member_ `ERaMaterialName LeftWallMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acoustic Materials")` — Left wall acoustic material
- L51 _public member_ `ERaMaterialName RightWallMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acoustic Materials")` — Right wall acoustic material
- L55 _public member_ `ERaMaterialName FloorMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acoustic Materials")` — Floor acoustic material
- L59 _public member_ `ERaMaterialName CeilingMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acoustic Materials")` — Ceiling acoustic material
- L63 _public member_ `ERaMaterialName FrontWallMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acoustic Materials")` — Front wall acoustic material
- L67 _public member_ `ERaMaterialName BackWallMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Acoustic Materials")` — Back wall acoustic material
- L71 _public member_ `float ReflectionScalar;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Early Reflections", meta = (ClampMin = "0.0", ClampMax = "10.0", UIMin = "0.0", UIMax = "10.0"))` — Early reflections gain multiplier. Default: 1.0
- L75 _public member_ `float ReverbGain;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reverb", meta = (ClampMin = "0.0", ClampMax = "10.0", UIMin = "0.0", UIMax = "10.0"))` — Reverb gain multiplier. Default: 1.0
- L79 _public member_ `float ReverbTimeModifier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reverb", meta = (ClampMin = "0.0", ClampMax = "10.0", UIMin = "0.0", UIMax = "10.0"))` — Reverb time modifier. Default: 1.0
- L83 _public member_ `float ReverbBrightness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reverb", meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))` — Reverb brightness modifier. Default: 0.0
- L85 _public function_ `FResonanceAudioReverbPluginSettings() : bEnableRoomEffects(false) , RoomPosition(FVector::ZeroVector) , RoomRotation(FQuat::Identity) , RoomDimensions(FVector::ZeroVector) , LeftWallMaterial(ERaMaterialName::TRANSPARENT) , RightWallMaterial(ERaMaterialName::TRANSPARENT) , FloorMaterial(ERaMaterialName::TRANSPARENT) , CeilingMaterial(ERaMaterialName::TRANSPARENT) , FrontWallMaterial(ERaMaterialName::TRANSPARENT) , BackWallMaterial(ERaMaterialName::TRANSPARENT) , ReflectionScalar(1.0f) , ReverbGain(1.0f) , ReverbTimeModifier(1.0f) , ReverbBrightness(0.0f)`

#### class `ResonanceAudio::FResonanceAudioReverb`  
`class FResonanceAudioReverb : public IAudioReverb`  
_L107-159_
- inherits: `IAudioReverb`
- L111 _public prototype_ `FResonanceAudioReverb();`
- L112 _public prototype_ `~FResonanceAudioReverb();`
- L114 _public prototype_ `virtual void Initialize(const FAudioPluginInitializationParams InitializationParams) override;`
- L115 _public prototype_ `virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, const uint32 NumChannels, UReverbPluginSourceSettingsBase* InSettings) override;`
- L116 _public prototype_ `virtual void OnReleaseSource(const uint32 SourceId) override;`
- L117 _public prototype_ `virtual FSoundEffectSubmixPtr GetEffectSubmix() override;`
- L118 _public prototype_ `virtual USoundSubmix* GetSubmix() override;`
- L119 _public prototype_ `virtual USoundSubmix* LoadSubmix() override;`
- L120 _public prototype_ `virtual void ProcessSourceAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData) override;`
- L122 _public function_ `void SetResonanceAudioApi(vraudio::ResonanceAudioApi* InResonanceAudioApi)`
- L123 _public prototype_ `void SetPreset(UResonanceAudioReverbPluginPreset* InPreset);`
- L124 _public prototype_ `void ProcessMixedAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData);`
- L126 _public prototype_ `void SetGlobalReverbPluginPreset(UResonanceAudioReverbPluginPreset* InPreset);`
- L127 _public prototype_ `UResonanceAudioReverbPluginPreset* GetGlobalReverbPluginPreset();`
- L130 _public prototype_ `void UpdateRoomEffects();` — Sets & updates Room Effect params from current |ReverbPluginPreset|.
- L131 _public prototype_ `void SetRoomPosition();`
- L132 _public prototype_ `void SetRoomRotation();`
- L133 _public prototype_ `void SetRoomDimensions();`
- L134 _public prototype_ `void SetRoomMaterials();`
- L135 _public prototype_ `void SetReflectionScalar();`
- L136 _public prototype_ `void SetReverbGain();`
- L137 _public prototype_ `void SetReverbTimeModifier();`
- L138 _public prototype_ `void SetReverbBrightness();`
- L142 _private prototype_ `void InitEffectSubmix();`
- L144 _private member_ `FResonanceAudioReverbPluginSettings ReverbSettings;`
- L145 _private member_ `RaRoomProperties RoomProperties;`
- L146 _private member_ `RaReverbProperties ReverbProperties;`
- L147 _private member_ `RaReflectionProperties ReflectionProperties;`
- L150 _private member_ `vraudio::ResonanceAudioApi* ResonanceAudioApi;`
- L151 _private member_ `FResonanceAudioModule* ResonanceAudioModule;`
- L152 _private member_ `UResonanceAudioReverbPluginPreset* ReverbPluginPreset;`
- L153 _private member_ `Audio::AlignedFloatBuffer TemporaryStereoBuffer;`
- L155 _private member_ `FSoundEffectSubmixPtr SubmixEffect;`
- L158 _private member_ `USoundSubmix* ReverbSubmixPtr;` — Reverb submix to be used only when Resonance fails to load the submix asset.

#### class `FResonanceAudioReverbPlugin`  
`class FResonanceAudioReverbPlugin : public FSoundEffectSubmix`  
_L163-177_
- inherits: `FSoundEffectSubmix`
- L166 _public prototype_ `FResonanceAudioReverbPlugin();`
- L168 _public prototype_ `virtual void Init(const FSoundEffectSubmixInitData& InData) override;`
- L169 _public prototype_ `virtual uint32 GetDesiredInputChannelCountOverride() const override;`
- L170 _public prototype_ `virtual void OnProcessAudio(const FSoundEffectSubmixInputData& InData, FSoundEffectSubmixOutputData& OutData) override;`
- L171 _public prototype_ `virtual void OnPresetChanged() override;`
- L173 _public prototype_ `void SetResonanceAudioReverbPlugin(ResonanceAudio::FResonanceAudioReverb* InResonanceAudioReverbPlugin);`
- L176 _private member_ `ResonanceAudio::FResonanceAudioReverb* ResonanceAudioReverb;`

#### class `UResonanceAudioReverbPluginPreset`  
`class UResonanceAudioReverbPluginPreset : public USoundEffectSubmixPreset`  
_L180-231_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `USoundEffectSubmixPreset`
- L186 _public prototype_ `EFFECT_PRESET_METHODS(ResonanceAudioReverbPlugin) UPROPERTY(EditAnywhere, Category = "Resonance Audio Room Effect Settings", Meta = (ShowOnlyInnerProperties)) FResonanceAudioReverbPluginSettings Settings;`
- L192 _public function_ `bool UseAudioVolumeTransform()` — Returns true, if the transform should be obtained from the Audio Volume, instead of set manually.
- L196 _public prototype_ `void SetEnableRoomEffects(bool bInEnableRoomEffects);` — `UFUNCTION(BlueprintCallable, Category = "Resonance Audio Room Effect Settings")` — Enables/disables Resonance Audio room effects
- L200 _public prototype_ `void SetRoomPosition(const FVector& InPosition);` — `UFUNCTION(BlueprintCallable, Category = "Resonance Audio Room Effect Settings")` — Sets room position in 3D space
- L204 _public prototype_ `void SetRoomRotation(const FQuat& InRotation);` — `UFUNCTION(BlueprintCallable, Category = "Resonance Audio Room Effect Settings")` — Sets room rotation in 3D space
- L208 _public prototype_ `void SetRoomDimensions(const FVector& InDimensions);` — `UFUNCTION(BlueprintCallable, Category = "Resonance Audio Room Effect Settings")` — Sets room dimensions in 3D space
- L212 _public prototype_ `void SetRoomMaterials(const TArray<ERaMaterialName>& InMaterials);` — `UFUNCTION(BlueprintCallable, Category = "Resonance Audio Room Effect Settings")` — Sets Resonance Audio room's acoustic materials
- L216 _public prototype_ `void SetReflectionScalar(float InReflectionScalar);` — `UFUNCTION(BlueprintCallable, Category = "Resonance Audio Room Effect Settings")` — Sets early reflections gain multiplier
- L220 _public prototype_ `void SetReverbGain(float InReverbGain);` — `UFUNCTION(BlueprintCallable, Category = "Resonance Audio Room Effect Settings")` — Sets reverb gain multiplier
- L225 _public prototype_ `void SetReverbTimeModifier(float InReverbTimeModifier);` — `UFUNCTION(BlueprintCallable, Category = "Resonance Audio Room Effect Settings")` — Adjusts the reverberation time across all frequency bands by multiplying the computed values by this factor. Has no effect when set to 1.0
- L230 _public prototype_ `void SetReverbBrightness(float InReverbBrightness);` — `UFUNCTION(BlueprintCallable, Category = "Resonance Audio Room Effect Settings")` — Increases high frequency reverberation times when positive, decreases when negative. Has no effect when set to 0.0

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API RESONANCEAUDIO_API`
- L104 _namespace_ `namespace ResonanceAudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioSettings.h` (Private)


#### class `UResonanceAudioSettings`  
`class UResonanceAudioSettings : public UObject`  
_L13-36_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig)`
- inherits: `UObject`
- L19 _public prototype_ `UResonanceAudioSettings();`
- L23 _public member_ `FSoftObjectPath OutputSubmix;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "Reverb", meta = (AllowedClasses = "/Script/Engine.SoundSubmix"))` — Reference to submix where reverb plugin audio is routed.
- L27 _public member_ `ERaQualityMode QualityMode;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = General)` — Global Quality mode to use for directional sound sources.
- L31 _public member_ `FSoftObjectPath GlobalReverbPreset;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = General, meta = (AllowedClasses = "/Script/ResonanceAudio.ResonanceAudioReverbPluginPreset"))` — Default settings for global reverb: This is overridden when a player enters Audio Volumes.
- L35 _public member_ `FSoftObjectPath GlobalSourcePreset;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = General, meta = (AllowedClasses = "/Script/ResonanceAudio.ResonanceAudioSpatializationSourceSettings"))` — Default settings for global source settings

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RESONANCEAUDIO_API`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceAudioSpatialization.h` (Private)


#### struct `ResonanceAudio::FBinauralSource`  
`struct FBinauralSource`  
_L13-26_
- L15 _public member_ `RaSourceId Id;`
- L16 _public member_ `float Pattern;`
- L17 _public member_ `float Sharpness;`
- L18 _public member_ `float Spread;`
- L20 _public function_ `FBinauralSource() : Id(RA_INVALID_SOURCE_ID) , Pattern(0.0f) , Sharpness(1.0f) , Spread(0.0f)`

#### class `ResonanceAudio::FResonanceAudioSpatialization`  
`class FResonanceAudioSpatialization : public IAudioSpatialization`  
_L28-51_
- inherits: `IAudioSpatialization`
- L31 _public prototype_ `FResonanceAudioSpatialization();`
- L32 _public prototype_ `~FResonanceAudioSpatialization();`
- L34 _public prototype_ `virtual void Initialize(const FAudioPluginInitializationParams InitializationParams) override;`
- L35 _public prototype_ `virtual bool IsSpatializationEffectInitialized() const override;`
- L36 _public prototype_ `virtual void OnInitSource(const uint32 SourceId, const FName& AudioComponentUserId, USpatializationPluginSourceSettingsBase* InSettings) override;`
- L37 _public prototype_ `virtual void OnReleaseSource(const uint32 SourceId) override;`
- L38 _public prototype_ `virtual void ProcessAudio(const FAudioPluginSourceInputData& InputData, FAudioPluginSourceOutputData& OutputData) override;`
- L40 _public function_ `void SetResonanceAudioApi(vraudio::ResonanceAudioApi* InResonanceAudioApi)`
- L43 _private prototype_ `bool DirectivityChanged(const uint32 SourceId);`
- L44 _private prototype_ `bool SpreadChanged(const uint32 SourceId);`
- L46 _private member_ `bool bIsInitialized;`
- L47 _private member_ `TArray<FBinauralSource> BinauralSources;`
- L48 _private member_ `vraudio::ResonanceAudioApi* ResonanceAudioApi;`
- L49 _private member_ `class FResonanceAudioModule* ResonanceAudioModule;`
- L50 _private member_ `TArray<UResonanceAudioSpatializationSourceSettings*> SpatializationSettings;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ResonanceAudio`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Private/ResonanceEigenHelper.h` (Private)
_(no declarations extracted)_

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Public/IResonanceAudioModule.h` (Public)


#### class `IResonanceAudioModule`  
`class IResonanceAudioModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L24 _public function_ `static inline IResonanceAudioModule& Get()` — Singleton-like access to this module's interface. This is just for convenience! Beware of calling this during the shutdown phase, though. Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready. It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Public/ResonanceAudioAmbisonicsSettings.h` (Public)


#### enum `EResonanceRenderMode`  
`enum class EResonanceRenderMode : uint8`  
_L15-35_
- reflection: `UENUM()`
- L18 _public enumerator_ `StereoPanning` — Stereo panning, i.e., this disables HRTF-based rendering.
- L21 _public enumerator_ `BinauralLowQuality` — HRTF-based rendering using First Order Ambisonics, over a virtual array of 8 loudspeakers arranged in a cube configuration around the listener's head.
- L25 _public enumerator_ `BinauralMediumQuality` — HRTF-based rendering using Second Order Ambisonics, over a virtual array of 12 loudspeakers arranged in a dodecahedral configuration (using faces of the dodecahedron).
- L28 _public enumerator_ `BinauralHighQuality` — HRTF-based rendering using Third Order Ambisonics, over a virtual array of 26 loudspeakers arranged in a Lebedev grid: https://goo.gl/DX1wh3.
- L34 _public enumerator_ `RoomEffectsOnly` — Room effects only rendering. This disables HRTF-based rendering and direct (dry) output of a sound object. Note that this rendering mode should *not* be used for general-purpose sound object spatialization, as it will only render the corresponding room effects of given sound objects without the direct spatialization.

#### class `UResonanceAudioSoundfieldSettings`  
`class UResonanceAudioSoundfieldSettings : public USoundfieldEncodingSettingsBase`  
_L38-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USoundfieldEncodingSettingsBase`
- L45 _public member_ `EResonanceRenderMode RenderMode = EResonanceRenderMode::BinauralHighQuality;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ambisonics)` — Which order of ambisonics to use for this submix.
- L47 _public prototype_ `virtual TUniquePtr<ISoundfieldEncodingSettingsProxy> GetProxy() const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API RESONANCEAUDIO_API`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Public/ResonanceAudioBlueprintFunctionLibrary.h` (Public)


#### class `UResonanceAudioBlueprintFunctionLibrary`  
`class UResonanceAudioBlueprintFunctionLibrary : public UBlueprintFunctionLibrary`  
_L15-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L23 _public prototype_ `static void SetGlobalReverbPreset(UResonanceAudioReverbPluginPreset* InPreset);` — `UFUNCTION(BlueprintCallable, Category = "ResonanceAudio|GlobalReverbPreset")` — This function overrides the Global Reverb Preset for Resonance Audio
- L27 _public prototype_ `static UResonanceAudioReverbPluginPreset* GetGlobalReverbPreset();` — `UFUNCTION(BlueprintCallable, Category = "ResonanceAudio|GlobalReverbPreset")` — This function retrieves the Global Reverb Preset for Resonance Audio

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API RESONANCEAUDIO_API`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Public/ResonanceAudioEnums.h` (Public)


#### enum `ERaQualityMode`  
`enum class ERaQualityMode : uint8`  
_L15-25_
- reflection: `UENUM(BlueprintType)`
- L18 _public enumerator_ `STEREO_PANNING UMETA(DisplayName = "Stereo Panning")` — Stereo panning.
- L20 _public enumerator_ `BINAURAL_LOW UMETA(DisplayName = "Binaural Low Quality")` — Binaural Low (First Order Ambisonics).
- L22 _public enumerator_ `BINAURAL_MEDIUM UMETA(DisplayName = "Binaural Medium Quality")` — Binaural Medium (Second Order Ambisonics).
- L24 _public enumerator_ `BINAURAL_HIGH UMETA(DisplayName = "Binaural High Quality")` — Binaural High (Third Order Ambisonics = Default).

#### enum `ERaSpatializationMethod`  
`enum class ERaSpatializationMethod : uint8`  
_L28-34_
- reflection: `UENUM(BlueprintType)`
- L31 _public enumerator_ `STEREO_PANNING UMETA(DisplayName = "Stereo Panning")` — Stereo panning.
- L33 _public enumerator_ `HRTF UMETA(DisplayName = "HRTF")` — Binaural rendering via HRTF.

#### enum `ERaDistanceRolloffModel`  
`enum class ERaDistanceRolloffModel : uint8`  
_L37-45_
- reflection: `UENUM(BlueprintType)`
- L40 _public enumerator_ `LOGARITHMIC UMETA(DisplayName = "Logarithmic")` — Logarithmic distance attenuation model (default).
- L42 _public enumerator_ `LINEAR UMETA(DisplayName = "Linear")` — Linear distance attenuation model.
- L44 _public enumerator_ `NONE UMETA(DisplayName = "None")` — Use Unreal Engine attenuation settings.

#### enum `ERaMaterialName`  
`enum class ERaMaterialName : uint8`  
_L48-76_
- reflection: `UENUM(BlueprintType)`
- L51 _public enumerator_ `TRANSPARENT UMETA(DisplayName = "Transparent")` — Full acoustic energy absorption.
- L52 _public enumerator_ `ACOUSTIC_CEILING_TILES UMETA(DisplayName = "Acoustic Ceiling Tiles")`
- L53 _public enumerator_ `BRICK_BARE UMETA(DisplayName = "Brick Bare")`
- L54 _public enumerator_ `BRICK_PAINTED UMETA(DisplayName = "Brick Painted")`
- L55 _public enumerator_ `CONCRETE_BLOCK_COARSE UMETA(DisplayName = "Concrete Block Coarse")`
- L56 _public enumerator_ `CONCRETE_BLOCK_PAINTED UMETA(DisplayName = "Concrete Block Painted")`
- L57 _public enumerator_ `CURTAIN_HEAVY UMETA(DisplayName = "Curtain Heavy")`
- L58 _public enumerator_ `FIBER_GLASS_INSULATION UMETA(DisplayName = "Fiber Glass Insulation")`
- L59 _public enumerator_ `GLASS_THIN UMETA(DisplayName = "Glass Thin")`
- L60 _public enumerator_ `GLASS_THICK UMETA(DisplayName = "Glass Thick")`
- L61 _public enumerator_ `GRASS UMETA(DisplayName = "Grass")`
- L62 _public enumerator_ `LINOLEUM_ON_CONCRETE UMETA(DisplayName = "Linoleum On Concrete")`
- L63 _public enumerator_ `MARBLE UMETA(DisplayName = "Marble")`
- L64 _public enumerator_ `METAL UMETA(DisplayName = "Metal")`
- L65 _public enumerator_ `PARQUET_ONCONCRETE UMETA(DisplayName = "Parquet On Concrete")`
- L66 _public enumerator_ `PLASTER_ROUGH UMETA(DisplayName = "Plaster Rough")`
- L67 _public enumerator_ `PLASTER_SMOOTH UMETA(DisplayName = "Plaster Smooth")`
- L68 _public enumerator_ `PLYWOOD_PANEL UMETA(DisplayName = "Plywood Panel")`
- L69 _public enumerator_ `POLISHED_CONCRETE_OR_TILE UMETA(DisplayName = "Polished Concrete Or Tile")`
- L70 _public enumerator_ `SHEETROCK UMETA(DisplayName = "Sheetrock")`
- L71 _public enumerator_ `WATER_OR_ICE_SURFACE UMETA(DisplayName = "Water Or Ice Surface")`
- L72 _public enumerator_ `WOOD_CEILING UMETA(DisplayName = "Wood Ceiling")`
- L73 _public enumerator_ `WOOD_PANEL UMETA(DisplayName = "Wood Panel")`
- L75 _public enumerator_ `UNIFORM UMETA(DisplayName = "Uniform")` — Uniform acoustic energy absorption across all frequency bands.

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogResonanceAudio, Display, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogResonanceAudio, Display, All);`

### `Plugins/Runtime/ResonanceAudio/Source/ResonanceAudio/Public/ResonanceAudioSpatializationSourceSettings.h` (Public)


#### class `UResonanceAudioSpatializationSourceSettings`  
`class UResonanceAudioSpatializationSourceSettings : public USpatializationPluginSourceSettingsBase`  
_L14-74_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USpatializationPluginSourceSettingsBase`
- L19 _public prototype_ `UResonanceAudioSpatializationSourceSettings();`
- L25 _public prototype_ `bool DoesAudioComponentReferenceThis(class UAudioComponent* InAudioComponent);` — See if Audio Component references this settings instance:
- L27 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L28 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L33 _public member_ `ERaSpatializationMethod SpatializationMethod;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "SpatializationSettings")` — Spatialization method to use for sound object(s). NOTE: Has no effect if 'Stereo Panning' global quality mode is selected for the project
- L37 _public member_ `float Pattern;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "SpatializationSettings|Directivity", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Directivity pattern: 0.0 (omnidirectional), 0.5 (cardioid), 1.0 (figure-of-8)
- L41 _public member_ `float Sharpness;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "SpatializationSettings|Directivity", meta = (ClampMin = "1.0", ClampMax = "100.0", UIMin = "1.0", UIMax = "100.0"))` — Sharpness of the directivity pattern. Higher values result in a narrower sound emission beam
- L45 _public member_ `bool bToggleVisualization;` — `UPROPERTY(EditAnywhere, Category = "SpatializationSettings|Directivity")` — Whether to visualize directivity pattern in the viewport.
- L49 _public member_ `float Scale;` — `UPROPERTY(EditAnywhere, Category = "SpatializationSettings|Directivity", meta = (ClampMin = "0.0", ClampMax = "10.0", UIMin = "0.0", UIMax = "10.0"))` — Scale (for directivity pattern visualization only).
- L53 _public member_ `float Spread;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "SpatializationSettings|Source spread (width)", meta = (ClampMin = "0.0", ClampMax = "180.0", UIMin = "0.0", UIMax = "180.0"))` — Spread (width) of the sound source (in degrees). Note: spread control is not available if 'Stereo Panning' global quality mode is enabled for the project and / or 'Stereo Panning' spatialization mode is enabled for the sound source
- L57 _public member_ `ERaDistanceRolloffModel Rolloff;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "SpatializationSettings|Distance attenuation")` — Roll-off model to use for sound source distance attenuation. Select 'None' (default) to use Unreal attenuation settings
- L61 _public member_ `float MinDistance;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "SpatializationSettings|Distance attenuation", meta = (ClampMin = "0.0", ClampMax = "1000000.0", UIMin = "0.0", UIMax = "1000000.0"))` — Minimum distance to apply the chosen attenuation method (default = 100.0 cm)
- L65 _public member_ `float MaxDistance;` — `UPROPERTY(GlobalConfig, EditAnywhere, Category = "SpatializationSettings|Distance attenuation", meta = (ClampMin = "0.0", ClampMax = "1000000.0", UIMin = "0.0", UIMax = "1000000.0"))` — Maximum distance to apply the chosen attenuation method ((default = 50000.0 cm)
- L69 _public prototype_ `void SetSoundSourceDirectivity(float InPattern, float InSharpness);` — `UFUNCTION(BlueprintCallable, Category = "ResonanceAudio|SoundSourceSpatializationSettings")` — Sets the sound source directivity, applies, and updates
- L73 _public prototype_ `void SetSoundSourceSpread(float InSpread);` — `UFUNCTION(BlueprintCallable, Category = "ResonanceAudio|SoundSourceSpatializationSettings")` — Sets the sound source spread (width), applies, and updates

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API RESONANCEAUDIO_API`
