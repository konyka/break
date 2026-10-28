# Runtime / AudioPlatformSupportWasapi

- module root: `Source/Runtime/AudioPlatformSupport/Windows/WASAPI`
- headers: 3; symbols: 35
- symbol kinds: class=2, enum=1, enumerator=8, macro=2, member=2, namespace=2, prototype=18
- PrivateDependencyModuleNames: Core

### `Source/Runtime/AudioPlatformSupport/Windows/WASAPI/Public/AudioPlatformSupportWasapiLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioPlatformSupportWasapi, Log, All);`

### `Source/Runtime/AudioPlatformSupport/Windows/WASAPI/Public/WasapiAudioFormat.h` (Public)


#### enum `Audio::EWasapiAudioEncoding`  
`enum class EWasapiAudioEncoding : uint8`  
_L23-33_
- desc: EWasapiAudioEncoding - Audio bit depths supported by WASAPI implementation
- L25 _public enumerator_ `UNKNOWN`
- L26 _public enumerator_ `PCM_8`
- L27 _public enumerator_ `PCM_16`
- L28 _public enumerator_ `PCM_24`
- L29 _public enumerator_ `PCM_24_IN_32`
- L30 _public enumerator_ `PCM_32`
- L31 _public enumerator_ `FLOATING_POINT_32`
- L32 _public enumerator_ `FLOATING_POINT_64`

#### class `Audio::FWasapiAudioFormat`  
`class FWasapiAudioFormat`  
_L38-103_
- desc: FWasapiAudioFormat - Wrapper class for Windows WAVEFORMATEX and WAVEFORMATEXTENSIBLE structs.
- L42 _public prototype_ `FWasapiAudioFormat();` — FWasapiAudioFormat - Constructs underlying WAVEFORMATEX with default values.
- L50 _public prototype_ `explicit FWasapiAudioFormat(WAVEFORMATEX* InFormat);` — FWasapiAudioFormat - Constructs underlying data structure with given WAVEFORMATEX parameter. @param InFormat - Pointer to a WAVEFORMATEX struct from which to construct this object. Correctly handles the extended form, WAVEFORMATEXTENSIBLE.
- L59 _public prototype_ `FWasapiAudioFormat(uint16 InChannels, uint32 InSampleRate, EWasapiAudioEncoding InEncoding);` — FWasapiAudioFormat - Constructs underlying data structure using given parameters. @param InChannels - Number of audio channels. @param InSampleRate - Samples per second (Hz). @param InEncoding - For PCM data, this is the bit depth of data (e.g. 16-bit integer, 32-bit float, etc.)
- L62 _public prototype_ `EWasapiAudioEncoding GetEncoding() const;` — GetEncoding - Returns the encoding for this audio format.
- L65 _public prototype_ `uint32 GetNumChannels() const;` — GetNumChannels - Returns the number of audio channels present in this format.
- L68 _public prototype_ `uint32 GetSampleRate() const;` — GetSampleRate - Returns the audio sample rate for this format.
- L71 _public prototype_ `uint32 GetBitsPerSample() const;` — GetBitsPerSample - Returns the bit depth for the audio data as an integer value.
- L74 _public prototype_ `uint32 GetBytesPerSample() const;` — GetBytesPerSample - Returns the number of bytes needed to store a single sample of audio data.
- L77 _public prototype_ `uint32 GetFrameSizeInBytes() const;` — GetFrameSizeInBytes - Returns the number of bytes needed to store a singe frame of audio data.
- L80 _public prototype_ `FString GetEncodingString() const;` — GetEncodingString - Returns string form of encoding. Suitable for logging.
- L86 _public prototype_ `const WAVEFORMATEX* GetWaveFormat() const;` — GetWaveFormat - Returns pointer to raw WAVEFORMATEX struct. Use this for specific OS API calls which require it. Otherwise use the accessors above.
- L91 _private prototype_ `void InitAudioFormat(uint16 InChannels, uint32 InSampleRate, EWasapiAudioEncoding InEncoding);` — InitAudioFormat - Init method used by constructors to initialize data.
- L93 _private prototype_ `void InitAudioEncoding();` — InitAudioEncoding - Parses underlying WAVEFORMATEXTENSIBLE structure and determines corresponding encoding.
- L95 _private prototype_ `static EWasapiAudioEncoding DetermineAudioEncoding(const WAVEFORMATEXTENSIBLE& InFormat);` — DetermineAudioEncoding - Helper function for determining audio encoding from WAVEFORMATEXTENSIBLE struct.
- L97 _private prototype_ `static uint16 EncodingToBitDepth(EWasapiAudioEncoding InEncoding);` — EncodingToBitDepth - Helper function for getting bit depth from InEncoding parameter.
- L100 _private member_ `WAVEFORMATEXTENSIBLE WaveFormat = {};` — WaveFormat - Windows wave format struct which this object wraps.
- L102 _private member_ `EWasapiAudioEncoding Encoding = EWasapiAudioEncoding::UNKNOWN;` — Encoding - Audio encoding for this object.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API AUDIOPLATFORMSUPPORTWASAPI_API`
- L18 _namespace_ `namespace Audio`

### `Source/Runtime/AudioPlatformSupport/Windows/WASAPI/Public/WasapiAudioUtils.h` (Public)


#### class `Audio::FWasapiAudioUtils`  
`class FWasapiAudioUtils`  
_L23-31_
- desc: FWasapiAudioUtils - WASAPI utility class
- L27 _public prototype_ `static REFERENCE_TIME FramesToRefTime(const uint32 InNumFrames, const uint32 InSampleRate);` — FramesToRefTime - Converts a given number of frames at the given sample rate to REFERENCE_TIME.
- L30 _public prototype_ `static uint64 RefTimeToFrames(const REFERENCE_TIME InRefTime, const uint32 InSampleRate);` — RefTimeToFrames - Converts the given REFERENCE_TIME to a number of frames at the given sample rate.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API AUDIOPLATFORMSUPPORTWASAPI_API`
- L18 _namespace_ `namespace Audio`
