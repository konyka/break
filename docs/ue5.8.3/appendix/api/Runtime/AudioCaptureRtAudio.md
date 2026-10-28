# Runtime / AudioCaptureRtAudio

- module root: `Source/Runtime/AudioCaptureImplementations/AudioCaptureRtAudio`
- headers: 3; symbols: 410
- symbol kinds: class=15, enum=5, enumerator=31, function=54, macro=10, member=89, namespace=2, prototype=165, struct=8, typedef=17, variable=14
- PrivateDependencyModuleNames: AudioCaptureCore, Core

### `Source/Runtime/AudioCaptureImplementations/AudioCaptureRtAudio/Private/AudioCaptureRtAudio.h` (Private)


#### class `Audio::FAudioCaptureRtAudioStream`  
`class FAudioCaptureRtAudioStream : public IAudioCaptureStream`  
_L22-50_
- inherits: `IAudioCaptureStream`
- L25 _public prototype_ `FAudioCaptureRtAudioStream();`
- L27 _public prototype_ `virtual bool GetCaptureDeviceInfo(FCaptureDeviceInfo& OutInfo, int32 DeviceIndex) override;`
- L28 _public prototype_ `virtual bool OpenAudioCaptureStream(const FAudioCaptureDeviceParams& InParams, FOnAudioCaptureFunction InOnCapture, uint32 NumFramesDesired) override;`
- L29 _public prototype_ `virtual bool CloseStream() override;`
- L30 _public prototype_ `virtual bool StartStream() override;`
- L31 _public prototype_ `virtual bool StopStream() override;`
- L32 _public prototype_ `virtual bool AbortStream() override;`
- L33 _public prototype_ `virtual bool GetStreamTime(double& OutStreamTime) override;`
- L34 _public function_ `virtual int32 GetSampleRate() const override`
- L35 _public prototype_ `virtual bool IsStreamOpen() const override;`
- L36 _public prototype_ `virtual bool IsCapturing() const override;`
- L37 _public prototype_ `virtual void OnAudioCapture(void* InBuffer, uint32 InBufferFrames, double StreamTime, bool bOverflow) override;`
- L38 _public prototype_ `virtual bool GetInputDevicesAvailable(TArray<FCaptureDeviceInfo>& OutDevices) override;`
- L41 _private member_ `FOnAudioCaptureFunction OnCapture;`
- L42 _private member_ `int32 NumChannels;`
- L43 _private member_ `int32 SampleRate;`
- L45 _private prototype_ `uint32 GetDefaultInputDevice();`
- L48 _private member_ `RtAudio CaptureDevice;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define WITH_RTAUDIO 0`
- L20 _namespace_ `namespace Audio`

### `Source/Runtime/AudioCaptureImplementations/AudioCaptureRtAudio/Private/RtAudio.h` (Private)


#### class `RtAudioError`  
`class RtAudioError : public std::runtime_error`  
_L252-288_
- inherits: `std::runtime_error`
- L271 _public function_ `RtAudioError( const std::string& message, Type type = RtAudioError::UNSPECIFIED ) : std::runtime_error(message), type_(type)` — The constructor.
- L276 _public function_ `virtual void printMessage( void ) const` — Prints thrown error message to stderr.
- L280 _public function_ `virtual const Type& getType(void) const` — Returns the thrown error message type.
- L283 _public function_ `virtual const std::string getMessage(void) const` — Returns the thrown error message string.
- L287 _protected member_ `Type type_;`

#### enum `RtAudioError::Type`  
`enum Type`  
_L256-268_
- desc: Defined RtAudioError types.
- L257 _public enumerator_ `WARNING`
- L258 _public enumerator_ `DEBUG_WARNING` — WARNING,            < A non-critical error.
- L259 _public enumerator_ `UNSPECIFIED` — DEBUG_WARNING,      < A non-critical error which might be useful for debugging.
- L260 _public enumerator_ `NO_DEVICES_FOUND` — UNSPECIFIED,        < The default, unspecified error type.
- L261 _public enumerator_ `INVALID_DEVICE` — NO_DEVICES_FOUND,   < No devices found on system.
- L262 _public enumerator_ `MEMORY_ERROR` — INVALID_DEVICE,     < An invalid device ID was specified.
- L263 _public enumerator_ `INVALID_PARAMETER` — MEMORY_ERROR,       < An error occured during memory allocation.
- L264 _public enumerator_ `INVALID_USE` — INVALID_PARAMETER,  < An invalid parameter was specified to a function.
- L265 _public enumerator_ `DRIVER_ERROR` — INVALID_USE,        < The function was called incorrectly.
- L266 _public enumerator_ `SYSTEM_ERROR` — DRIVER_ERROR,       < A system driver error occured.
- L267 _public enumerator_ `THREAD_ERROR` — SYSTEM_ERROR,       < A system error occured.

#### class `RtAudio`  
`class RtAudio`  
_L312-626_
- L430 _public prototype_ `static std::string getVersion( void );` — A static function to determine the current RtAudio version.
- L438 _public prototype_ `static void getCompiledApi( std::vector<RtAudio::Api> &apis );` — The values returned in the std::vector can be compared against the enumerated list values.  Note that there can be more than one API compiled for certain operating systems.
- L449 _public prototype_ `RtAudio( RtAudio::Api api=UNSPECIFIED );` — The constructor performs minor initialization tasks.  An exception can be thrown if no API support is compiled. If no API argument is specified and multiple API support has been compiled, the default order of use is JACK, ALSA, OSS (Linux systems) and ASIO, DS (Windows systems).
- L456 _public prototype_ `~RtAudio();` — If a stream is running or open, it will be stopped and closed automatically.
- L459 _public prototype_ `RtAudio::Api getCurrentApi( void );` — Returns the audio API specifier for the current instance of RtAudio.
- L467 _public prototype_ `unsigned int getDeviceCount( void );` — This function performs a system query of available devices each time it is called, thus supporting devices connected \e after instantiation. If a system error occurs during processing, a warning will be issued.
- L480 _public prototype_ `RtAudio::DeviceInfo getDeviceInfo( unsigned int device );` — Any device integer between 0 and getDeviceCount() - 1 is valid. If an invalid argument is provided, an RtAudioError (type = INVALID_USE) will be thrown.  If a device is busy or otherwise unavailable, the structure member "probed" will have a value of "false" and all other members are undefined.  If the specified device is the current default input or output device, the corresponding "isDefault" member will have a value of "true".
- L490 _public prototype_ `unsigned int getDefaultOutputDevice( void );` — If the underlying audio API does not provide a "default device", or if no devices are available, the return value will be 0.  Note that this is a valid device identifier and it is the client's responsibility to verify that a device is available before attempting to open a stream.
- L500 _public prototype_ `unsigned int getDefaultInputDevice( void );` — If the underlying audio API does not provide a "default device", or if no devices are available, the return value will be 0.  Note that this is a valid device identifier and it is the client's responsibility to verify that a device is available before attempting to open a stream.
- L542 _public prototype_ `void openStream( RtAudio::StreamParameters *outputParameters, RtAudio::StreamParameters *inputParameters, RtAudioFormat format, unsigned int sampleRate, unsigned int *bufferFrames, RtAudioCallback callback, void *userData = NULL, RtAudio::StreamOptions *options = NULL, RtAudioErrorCallback errorCallback = NULL );` — An RtAudioError (type = SYSTEM_ERROR) is thrown if a stream cannot be opened with the specified parameters or an error occurs during processing.  An RtAudioError (type = INVALID_USE) is thrown if any invalid device ID or channel number parameters are specified. \param outputParameters Specifies output stream parameters to use when opening a stream, including a device ID, number of channels, and starting channel number.  For input-only streams, this argument should be NULL.  The device ID is an index value between 0 and getDeviceCount() - 1. \param inputParameters Specifies input stream parameters to use when opening a stream, including a device ID, number of channels, and starting channel number.  For output-only streams, this argument should be NULL.  The device ID is an index value between 0 and getDeviceCount() - 1. \param format An RtAudioFormat specifying the desired sample data format. \param sampleRate The desired sample rate (sample frames per second). \param *bufferFrames A pointer to a value indicating the desired internal buffer size in sample frames.  The actual value used by the device is returned via the same pointer.  A value of zero can be specified, in which case the lowest allowable value is determined. \param callback A client-defined function that will be invoked when input data is available and/or output data is needed. \param userData An optional pointer to data that can be accessed from within the callback function. \param options An optional pointer to
- L553 _public prototype_ `void closeStream( void );` — If a stream is not open, this function issues a warning and returns (no exception is thrown).
- L562 _public prototype_ `void startStream( void );` — An RtAudioError (type = SYSTEM_ERROR) is thrown if an error occurs during processing.  An RtAudioError (type = INVALID_USE) is thrown if a stream is not open.  A warning is issued if the stream is already running.
- L571 _public prototype_ `void stopStream( void );` — An RtAudioError (type = SYSTEM_ERROR) is thrown if an error occurs during processing.  An RtAudioError (type = INVALID_USE) is thrown if a stream is not open.  A warning is issued if the stream is already stopped.
- L580 _public prototype_ `void abortStream( void );` — An RtAudioError (type = SYSTEM_ERROR) is thrown if an error occurs during processing.  An RtAudioError (type = INVALID_USE) is thrown if a stream is not open.  A warning is issued if the stream is already stopped.
- L583 _public prototype_ `bool isStreamOpen( void ) const;` — Returns true if a stream is open and false if not.
- L586 _public prototype_ `bool isStreamRunning( void ) const;` — Returns true if the stream is running and false if it is stopped or not open.
- L592 _public prototype_ `double getStreamTime( void );` — If a stream is not open, an RtAudioError (type = INVALID_USE) will be thrown.
- L598 _public prototype_ `void setStreamTime( double time );` — If a stream is not open, an RtAudioError (type = INVALID_USE) will be thrown.
- L609 _public prototype_ `long getStreamLatency( void );` — The stream latency refers to delay in audio input and/or output caused by internal buffering by the audio system and/or hardware. For duplex streams, the returned value will represent the sum of the input and output latencies.  If a stream is not open, an RtAudioError (type = INVALID_USE) will be thrown.  If the API does not report latency, the return value will be zero.
- L617 _public prototype_ `unsigned int getStreamSampleRate( void );` — On some systems, the sample rate used may be slightly different than that specified in the stream parameters.  If a stream is not open, an RtAudioError (type = INVALID_USE) will be thrown.
- L620 _public prototype_ `void showWarnings( bool value = true );` — Specify whether warning messages should be printed to stderr.
- L624 _protected prototype_ `void openRtApi( RtAudio::Api api );`
- L625 _protected member_ `RtApi *rtapi_;`
- L879 _function_ `inline RtAudio::Api RtAudio :: getCurrentApi( void )`
- L880 _function_ `inline unsigned int RtAudio :: getDeviceCount( void )`
- L881 _function_ `inline RtAudio::DeviceInfo RtAudio :: getDeviceInfo( unsigned int device )`
- L882 _function_ `inline unsigned int RtAudio :: getDefaultInputDevice( void )`
- L883 _function_ `inline unsigned int RtAudio :: getDefaultOutputDevice( void )`
- L884 _function_ `inline void RtAudio :: closeStream( void )`
- L885 _function_ `inline void RtAudio :: startStream( void )`
- L886 _function_ `inline void RtAudio :: stopStream( void )`
- L887 _function_ `inline void RtAudio :: abortStream( void )`
- L888 _function_ `inline bool RtAudio :: isStreamOpen( void ) const`
- L889 _function_ `inline bool RtAudio :: isStreamRunning( void ) const`
- L890 _function_ `inline long RtAudio :: getStreamLatency( void )`
- L891 _function_ `inline unsigned int RtAudio :: getStreamSampleRate( void )`
- L892 _function_ `inline double RtAudio :: getStreamTime( void )`
- L893 _function_ `inline void RtAudio :: setStreamTime( double time )`
- L894 _function_ `inline void RtAudio :: showWarnings( bool value )`

#### enum `RtAudio::Api`  
`enum Api`  
_L317-328_
- desc: Audio API specifier arguments.
- L318 _public enumerator_ `UNSPECIFIED`
- L319 _public enumerator_ `LINUX_ALSA` — UNSPECIFIED,     < Search for a working compiled API.
- L320 _public enumerator_ `LINUX_PULSE` — LINUX_ALSA,      < The Advanced Linux Sound Architecture API.
- L321 _public enumerator_ `LINUX_OSS` — LINUX_PULSE,     < The Linux PulseAudio API.
- L322 _public enumerator_ `UNIX_JACK` — LINUX_OSS,       < The Linux Open Sound System API.
- L323 _public enumerator_ `MACOSX_CORE` — UNIX_JACK,       < The Jack Low-Latency Audio Server API.
- L324 _public enumerator_ `WINDOWS_WASAPI` — MACOSX_CORE,     < Macintosh OS-X Core Audio API.
- L325 _public enumerator_ `WINDOWS_ASIO` — WINDOWS_WASAPI,  < The Microsoft WASAPI API.
- L326 _public enumerator_ `WINDOWS_DS` — WINDOWS_ASIO,    < The Steinberg Audio Stream I/O API.
- L327 _public enumerator_ `RTAUDIO_DUMMY` — WINDOWS_DS,      < The Microsoft Direct Sound API.

#### struct `RtAudio::DeviceInfo`  
`struct DeviceInfo`  
_L331-348_
- desc: The public device information structure for returning queried values.
- L332 _public member_ `bool probed;`
- L333 _public member_ `std::string name;` — bool probed;                   < true if the device capabilities were successfully probed.
- L334 _public member_ `std::string deviceId;` — std::string name;              < Character string device display name.
- L335 _public member_ `unsigned int outputChannels;` — std::string deviceId;                < Character string device identifier.
- L336 _public member_ `unsigned int inputChannels;` — unsigned int outputChannels;   < Maximum output channels supported by device.
- L337 _public member_ `unsigned int duplexChannels;` — unsigned int inputChannels;    < Maximum input channels supported by device.
- L338 _public member_ `bool isDefaultOutput;` — unsigned int duplexChannels;   < Maximum simultaneous input/output channels supported by device.
- L339 _public member_ `bool isDefaultInput;` — bool isDefaultOutput;          < true if this is the default output device.
- L340 _public member_ `std::vector<unsigned int> sampleRates;` — bool isDefaultInput;           < true if this is the default input device.
- L341 _public member_ `unsigned int preferredSampleRate;` — std::vector<unsigned int> sampleRates;  < Supported sample rates (queried from list of standard rates).
- L342 _public member_ `RtAudioFormat nativeFormats;` — unsigned int preferredSampleRate;  < Preferred sample rate, eg. for WASAPI the system sample rate.
- L345 _public function_ `DeviceInfo() :probed(false), outputChannels(0), inputChannels(0), duplexChannels(0), isDefaultOutput(false), isDefaultInput(false), preferredSampleRate(0), nativeFormats(0)` — Default constructor.

#### struct `RtAudio::StreamParameters`  
`struct StreamParameters`  
_L351-359_
- desc: The structure for specifying input or ouput stream parameters.
- L352 _public member_ `unsigned int deviceId;`
- L353 _public member_ `unsigned int nChannels;` — unsigned int deviceId;      < Device index (0 to getDeviceCount() - 1).
- L354 _public member_ `unsigned int firstChannel;` — unsigned int nChannels;     < Number of channels.
- L357 _public function_ `StreamParameters() : deviceId(0), nChannels(0), firstChannel(0)` — Default constructor.

#### struct `RtAudio::StreamOptions`  
`struct StreamOptions`  
_L418-427_
- desc: The following flags can be OR'ed together to allow a client to make changes to the default stream behavior: - \e RTAUDIO_NONINTERLEAVED:    Use non-interleaved buffers (default = interleaved). - \e RTAUDIO_MINIMIZE_LATENCY:  Attempt to set stream parameters for lowest possible latency. - \e RTAUDIO_HOG_DEVICE:        Attempt grab device for exclusive use. - \e RTAUDIO_SCHEDULE_REALTIME: Attempt to select realtime scheduling for callback thread. - \e RTAUDIO_ALSA_USE_DEFAULT:  Use the "default" PCM device (ALSA only). By default, RtAudio streams pass and receive audio data from the client in an interleaved format.  By passing the RTAUDIO_NONINTERLEAVED flag to the openStream() function, audio data will instead be presented in non-interleaved buffers.  In this case, each buffer argument in the RtAudioCallback function will point to a single array of data, with \c nFrames samples for each channel concatenated back-to-back.  For example, the first sample of data for the second channel would be located at index \c nFrames (assuming the \c buffer pointer was recast to the correct data type for the stream). Certain audio APIs offer a number of parameters that influence the I/O latency of a stream.  By default, RtAudio will attempt to set these parameters internally for robust (glitch-free) performance (though some APIs, like Windows Direct Sound, make this difficult). By passing the RTAUDIO_MINIMIZE_LATENCY flag to the openStream() function, internal stream settings will be influenc
- L419 _public member_ `RtAudioStreamFlags flags;`
- L420 _public member_ `unsigned int numberOfBuffers;` — RtAudioStreamFlags flags;       < A bit-mask of stream flags (RTAUDIO_NONINTERLEAVED, RTAUDIO_MINIMIZE_LATENCY, RTAUDIO_HOG_DEVICE, RTAUDIO_ALSA_USE_DEFAULT).
- L421 _public member_ `std::string streamName;` — unsigned int numberOfBuffers;   < Number of stream buffers.
- L422 _public member_ `int priority;` — std::string streamName;         < A stream name (currently used only in Jack).
- L425 _public function_ `StreamOptions() : flags(0), numberOfBuffers(0), priority(0)` — Default constructor.

#### struct `CallbackInfo`  
`struct CallbackInfo`  
_L658-672_
- desc: This global structure type is used to pass callback information between the private RtAudio stream structure and global callback handling functions.
- L659 _public member_ `void *object;` — Used as a "this" pointer.
- L660 _public member_ `ThreadHandle thread;`
- L661 _public member_ `void *callback;`
- L662 _public member_ `void *userData;`
- L663 _public member_ `void *errorCallback;`
- L664 _public member_ `void *apiInfo;` — void pointer for API specific callback information
- L665 _public member_ `bool isRunning;`
- L666 _public member_ `bool doRealtime;`
- L667 _public member_ `int priority;`
- L670 _public function_ `CallbackInfo() :object(0), callback(0), userData(0), errorCallback(0), apiInfo(0), isRunning(false), doRealtime(false), priority(0)` — Default constructor.

#### class `S24`  
`class S24`  
_L689-715_
- L692 _protected member_ `unsigned char c3[3];`
- L695 _public function_ `S24()`
- L697 _public function_ `S24& operator = ( const int& i )`
- L704 _public function_ `S24( const S24& v )`
- L705 _public function_ `S24( const double& d )`
- L706 _public function_ `S24( const float& f )`
- L707 _public function_ `S24( const signed short& s )`
- L708 _public function_ `S24( const char& c )`
- L710 _public function_ `int asInt()`

#### class `RtApi`  
`class RtApi`  
_L724-871_
- L728 _public prototype_ `RtApi();`
- L729 _public prototype_ `virtual ~RtApi();`
- L730 _public prototype_ `virtual RtAudio::Api getCurrentApi( void ) = 0;`
- L731 _public prototype_ `virtual unsigned int getDeviceCount( void ) = 0;`
- L732 _public prototype_ `virtual RtAudio::DeviceInfo getDeviceInfo( unsigned int device ) = 0;`
- L733 _public prototype_ `virtual unsigned int getDefaultInputDevice( void );`
- L734 _public prototype_ `virtual unsigned int getDefaultOutputDevice( void );`
- L735 _public prototype_ `void openStream( RtAudio::StreamParameters *outputParameters, RtAudio::StreamParameters *inputParameters, RtAudioFormat format, unsigned int sampleRate, unsigned int *bufferFrames, RtAudioCallback callback, void *userData, RtAudio::StreamOptions *options, RtAudioErrorCallback errorCallback );`
- L741 _public prototype_ `virtual void closeStream( void );`
- L742 _public prototype_ `virtual void startStream( void ) = 0;`
- L743 _public prototype_ `virtual void stopStream( void ) = 0;`
- L744 _public prototype_ `virtual void abortStream( void ) = 0;`
- L745 _public prototype_ `long getStreamLatency( void );`
- L746 _public prototype_ `unsigned int getStreamSampleRate( void );`
- L747 _public prototype_ `virtual double getStreamTime( void );`
- L748 _public prototype_ `virtual void setStreamTime( double time );`
- L749 _public function_ `bool isStreamOpen( void ) const`
- L750 _public function_ `bool isStreamRunning( void ) const`
- L751 _public function_ `void showWarnings( bool value )`
- L756 _protected member_ `static const unsigned int MAX_SAMPLE_RATES;`
- L757 _protected member_ `static const unsigned int SAMPLE_RATES[];`
- L818 _protected typedef_ `typedef S24 Int24;`
- L819 _protected typedef_ `typedef signed short Int16;`
- L820 _protected typedef_ `typedef signed int Int32;`
- L821 _protected typedef_ `typedef float Float32;`
- L822 _protected typedef_ `typedef double Float64;`
- L824 _protected member_ `std::ostringstream errorStream_;`
- L825 _protected member_ `std::string errorText_;`
- L826 _protected member_ `bool showWarnings_;`
- L827 _protected member_ `RtApiStream stream_;`
- L828 _protected member_ `bool firstErrorOccurred_;`
- L837 _protected prototype_ `virtual bool probeDeviceOpen( unsigned int device, StreamMode mode, unsigned int channels, unsigned int firstChannel, unsigned int sampleRate, RtAudioFormat format, unsigned int *bufferSize, RtAudio::StreamOptions *options );` — Protected, api-specific method that attempts to open a device with the given parameters.  This function MUST be implemented by all subclasses.  If an error is encountered during the probe, a "warning" message is reported and FAILURE is returned. A successful probe is indicated by a return value of SUCCESS.
- L843 _protected prototype_ `void tickStreamTime( void );` — A protected function used to increment the stream time.
- L846 _protected prototype_ `void clearStreamInfo();` — Protected common method to clear an RtApiStream structure.
- L852 _protected prototype_ `void verifyStream( void );` — Protected common method that throws an RtAudioError (type = INVALID_USE) if a stream is not open.
- L855 _protected prototype_ `void error( RtAudioError::Type type );` — Protected common error method to allow global control over error handling.
- L861 _protected prototype_ `void convertBuffer( char *outBuffer, char *inBuffer, ConvertInfo &info );` — Protected method used to perform format, channel number, and/or interleaving conversions between the user and device buffers.
- L864 _protected prototype_ `void byteSwapBuffer( char *buffer, unsigned int samples, RtAudioFormat format );` — Protected common method used to perform byte-swapping on buffers.
- L867 _protected prototype_ `unsigned int formatBytes( RtAudioFormat format );` — Protected common method that returns the number of bytes for a given format.
- L870 _protected prototype_ `void setConvertInfo( StreamMode mode, unsigned int firstChannel );` — Protected common method that sets up the parameters for buffer conversion.

#### enum `RtApi::(anonymous)`  
`enum`  
_L759-759_

#### enum `RtApi::StreamState`  
`enum StreamState`  
_L761-766_
- L762 _public enumerator_ `STREAM_STOPPED`
- L763 _public enumerator_ `STREAM_STOPPING`
- L764 _public enumerator_ `STREAM_RUNNING`
- L765 _public enumerator_ `STREAM_CLOSED = -50`

#### enum `RtApi::StreamMode`  
`enum StreamMode`  
_L768-773_
- L769 _public enumerator_ `OUTPUT`
- L770 _public enumerator_ `INPUT`
- L771 _public enumerator_ `DUPLEX`
- L772 _public enumerator_ `UNINITIALIZED = -75`

#### struct `RtApi::ConvertInfo`  
`struct ConvertInfo`  
_L776-782_
- desc: A protected structure used for buffer conversion.
- L777 _public member_ `int channels;`
- L778 _public member_ `int inJump, outJump;`
- L778 _public member_ `int inJump, outJump;`
- L779 _public member_ `RtAudioFormat inFormat, outFormat;`
- L779 _public member_ `RtAudioFormat inFormat, outFormat;`
- L780 _public member_ `std::vector<int> inOffset;`
- L781 _public member_ `std::vector<int> outOffset;`

#### struct `RtApi::RtApiStream`  
`struct RtApiStream`  
_L785-816_
- desc: A protected structure for audio streams.
- L786 _public member_ `unsigned int device[2];` — Playback and record, respectively.
- L787 _public member_ `void *apiHandle;` — void pointer for API specific stream handle information
- L788 _public member_ `StreamMode mode;` — OUTPUT, INPUT, or DUPLEX.
- L789 _public member_ `StreamState state;` — STOPPED, RUNNING, or CLOSED
- L790 _public member_ `char *userBuffer[2];` — Playback and record, respectively.
- L791 _public member_ `char *deviceBuffer;`
- L792 _public member_ `bool doConvertBuffer[2];` — Playback and record, respectively.
- L793 _public member_ `bool userInterleaved;`
- L794 _public member_ `bool deviceInterleaved[2];` — Playback and record, respectively.
- L795 _public member_ `bool doByteSwap[2];` — Playback and record, respectively.
- L796 _public member_ `unsigned int sampleRate;`
- L797 _public member_ `unsigned int bufferSize;`
- L798 _public member_ `unsigned int nBuffers;`
- L799 _public member_ `unsigned int nUserChannels[2];` — Playback and record, respectively.
- L800 _public member_ `unsigned int nDeviceChannels[2];` — Playback and record channels, respectively.
- L801 _public member_ `unsigned int channelOffset[2];` — Playback and record, respectively.
- L802 _public member_ `unsigned long latency[2];` — Playback and record, respectively.
- L803 _public member_ `RtAudioFormat userFormat;`
- L804 _public member_ `RtAudioFormat deviceFormat[2];` — Playback and record, respectively.
- L805 _public member_ `StreamMutex mutex;`
- L806 _public member_ `CallbackInfo callbackInfo;`
- L807 _public member_ `ConvertInfo convertInfo[2];`
- L808 _public member_ `double streamTime;` — Number of elapsed seconds since the stream started.
- L811 _public member_ `struct timeval lastTickTimestamp;`
- L814 _public function_ `RtApiStream() :apiHandle(0), deviceBuffer(0)`

#### class `RtApiCore`  
`class RtApiCore: public RtApi`  
_L902-934_
- inherits: `RtApi`
- L906 _public prototype_ `RtApiCore();`
- L907 _public prototype_ `~RtApiCore();`
- L908 _public function_ `RtAudio::Api getCurrentApi( void )`
- L909 _public prototype_ `unsigned int getDeviceCount( void );`
- L910 _public prototype_ `RtAudio::DeviceInfo getDeviceInfo( unsigned int device );`
- L911 _public prototype_ `unsigned int getDefaultOutputDevice( void );`
- L912 _public prototype_ `unsigned int getDefaultInputDevice( void );`
- L913 _public prototype_ `void closeStream( void );`
- L914 _public prototype_ `void startStream( void );`
- L915 _public prototype_ `void stopStream( void );`
- L916 _public prototype_ `void abortStream( void );`
- L917 _public prototype_ `long getStreamLatency( void );`
- L923 _public prototype_ `bool callbackEvent( AudioDeviceID deviceId, const AudioBufferList *inBufferList, const AudioBufferList *outBufferList );` — This function is intended for internal use only.  It must be public because it is called by the internal callback handler, which is not a member of RtAudio.  External use of this function will most likely produce highly undesireable results!
- L929 _private prototype_ `bool probeDeviceOpen( unsigned int device, StreamMode mode, unsigned int channels, unsigned int firstChannel, unsigned int sampleRate, RtAudioFormat format, unsigned int *bufferSize, RtAudio::StreamOptions *options );`
- L933 _private prototype_ `static const char* getErrorCode( OSStatus code );`

#### class `RtApiJack`  
`class RtApiJack: public RtApi`  
_L940-969_
- inherits: `RtApi`
- L944 _public prototype_ `RtApiJack();`
- L945 _public prototype_ `~RtApiJack();`
- L946 _public function_ `RtAudio::Api getCurrentApi( void )`
- L947 _public prototype_ `unsigned int getDeviceCount( void );`
- L948 _public prototype_ `RtAudio::DeviceInfo getDeviceInfo( unsigned int device );`
- L949 _public prototype_ `void closeStream( void );`
- L950 _public prototype_ `void startStream( void );`
- L951 _public prototype_ `void stopStream( void );`
- L952 _public prototype_ `void abortStream( void );`
- L953 _public prototype_ `long getStreamLatency( void );`
- L959 _public prototype_ `bool callbackEvent( unsigned long nframes );` — This function is intended for internal use only.  It must be public because it is called by the internal callback handler, which is not a member of RtAudio.  External use of this function will most likely produce highly undesireable results!
- L963 _private prototype_ `bool probeDeviceOpen( unsigned int device, StreamMode mode, unsigned int channels, unsigned int firstChannel, unsigned int sampleRate, RtAudioFormat format, unsigned int *bufferSize, RtAudio::StreamOptions *options );`
- L968 _private member_ `bool shouldAutoconnect_;`

#### class `RtApiAsio`  
`class RtApiAsio: public RtApi`  
_L975-1005_
- inherits: `RtApi`
- L979 _public prototype_ `RtApiAsio();`
- L980 _public prototype_ `~RtApiAsio();`
- L981 _public function_ `RtAudio::Api getCurrentApi( void )`
- L982 _public prototype_ `unsigned int getDeviceCount( void );`
- L983 _public prototype_ `RtAudio::DeviceInfo getDeviceInfo( unsigned int device );`
- L984 _public prototype_ `void closeStream( void );`
- L985 _public prototype_ `void startStream( void );`
- L986 _public prototype_ `void stopStream( void );`
- L987 _public prototype_ `void abortStream( void );`
- L988 _public prototype_ `long getStreamLatency( void );`
- L994 _public prototype_ `bool callbackEvent( long bufferIndex );` — This function is intended for internal use only.  It must be public because it is called by the internal callback handler, which is not a member of RtAudio.  External use of this function will most likely produce highly undesireable results!
- L998 _private member_ `std::vector<RtAudio::DeviceInfo> devices_;`
- L999 _private prototype_ `void saveDeviceInfo( void );`
- L1000 _private member_ `bool coInitialized_;`
- L1001 _private prototype_ `bool probeDeviceOpen( unsigned int device, StreamMode mode, unsigned int channels, unsigned int firstChannel, unsigned int sampleRate, RtAudioFormat format, unsigned int *bufferSize, RtAudio::StreamOptions *options );`

#### class `RtApiDs`  
`class RtApiDs: public RtApi`  
_L1011-1044_
- inherits: `RtApi`
- L1015 _public prototype_ `RtApiDs();`
- L1016 _public prototype_ `~RtApiDs();`
- L1017 _public function_ `RtAudio::Api getCurrentApi( void )`
- L1018 _public prototype_ `unsigned int getDeviceCount( void );`
- L1019 _public prototype_ `unsigned int getDefaultOutputDevice( void );`
- L1020 _public prototype_ `unsigned int getDefaultInputDevice( void );`
- L1021 _public prototype_ `RtAudio::DeviceInfo getDeviceInfo( unsigned int device );`
- L1022 _public prototype_ `void closeStream( void );`
- L1023 _public prototype_ `void startStream( void );`
- L1024 _public prototype_ `void stopStream( void );`
- L1025 _public prototype_ `void abortStream( void );`
- L1026 _public prototype_ `long getStreamLatency( void );`
- L1032 _public prototype_ `void callbackEvent( void );` — This function is intended for internal use only.  It must be public because it is called by the internal callback handler, which is not a member of RtAudio.  External use of this function will most likely produce highly undesireable results!
- L1036 _private member_ `bool coInitialized_;`
- L1037 _private member_ `bool buffersRolling;`
- L1038 _private member_ `long duplexPrerollBytes;`
- L1039 _private member_ `std::vector<struct DsDevice> dsDevices;`
- L1040 _private prototype_ `bool probeDeviceOpen( unsigned int device, StreamMode mode, unsigned int channels, unsigned int firstChannel, unsigned int sampleRate, RtAudioFormat format, unsigned int *bufferSize, RtAudio::StreamOptions *options );`

#### class `RtApiWasapi`  
`class RtApiWasapi : public RtApi`  
_L1052-1081_
- inherits: `RtApi`
- L1055 _public prototype_ `RtApiWasapi();`
- L1056 _public prototype_ `~RtApiWasapi();`
- L1058 _public function_ `RtAudio::Api getCurrentApi( void )`
- L1059 _public prototype_ `unsigned int getDeviceCount( void );`
- L1060 _public prototype_ `RtAudio::DeviceInfo getDeviceInfo( unsigned int device );`
- L1061 _public prototype_ `unsigned int getDefaultOutputDevice( void );`
- L1062 _public prototype_ `unsigned int getDefaultInputDevice( void );`
- L1063 _public prototype_ `void closeStream( void );`
- L1064 _public prototype_ `void startStream( void );`
- L1065 _public prototype_ `void stopStream( void );`
- L1066 _public prototype_ `void abortStream( void );`
- L1069 _private member_ `bool coInitialized_;`
- L1070 _private member_ `IMMDeviceEnumerator* deviceEnumerator_;`
- L1072 _private prototype_ `bool probeDeviceOpen( unsigned int device, StreamMode mode, unsigned int channels, unsigned int firstChannel, unsigned int sampleRate, RtAudioFormat format, unsigned int* bufferSize, RtAudio::StreamOptions* options );`
- L1077 _private prototype_ `static DWORD WINAPI runWasapiThread( void* wasapiPtr );`
- L1078 _private prototype_ `static DWORD WINAPI stopWasapiThread( void* wasapiPtr );`
- L1079 _private prototype_ `static DWORD WINAPI abortWasapiThread( void* wasapiPtr );`
- L1080 _private prototype_ `void wasapiThread();`

#### class `RtApiAlsa`  
`class RtApiAlsa: public RtApi`  
_L1087-1115_
- inherits: `RtApi`
- L1091 _public prototype_ `RtApiAlsa();`
- L1092 _public prototype_ `~RtApiAlsa();`
- L1093 _public function_ `RtAudio::Api getCurrentApi()`
- L1094 _public prototype_ `unsigned int getDeviceCount( void );`
- L1095 _public prototype_ `RtAudio::DeviceInfo getDeviceInfo( unsigned int device );`
- L1096 _public prototype_ `void closeStream( void );`
- L1097 _public prototype_ `void startStream( void );`
- L1098 _public prototype_ `void stopStream( void );`
- L1099 _public prototype_ `void abortStream( void );`
- L1105 _public prototype_ `void callbackEvent( void );` — This function is intended for internal use only.  It must be public because it is called by the internal callback handler, which is not a member of RtAudio.  External use of this function will most likely produce highly undesireable results!
- L1109 _private member_ `std::vector<RtAudio::DeviceInfo> devices_;`
- L1110 _private prototype_ `void saveDeviceInfo( void );`
- L1111 _private prototype_ `bool probeDeviceOpen( unsigned int device, StreamMode mode, unsigned int channels, unsigned int firstChannel, unsigned int sampleRate, RtAudioFormat format, unsigned int *bufferSize, RtAudio::StreamOptions *options );`

#### class `RtApiPulse`  
`class RtApiPulse: public RtApi`  
_L1121-1147_
- inherits: `RtApi`
- L1124 _public prototype_ `~RtApiPulse();`
- L1125 _public function_ `RtAudio::Api getCurrentApi()`
- L1126 _public prototype_ `unsigned int getDeviceCount( void );`
- L1127 _public prototype_ `RtAudio::DeviceInfo getDeviceInfo( unsigned int device );`
- L1128 _public prototype_ `void closeStream( void );`
- L1129 _public prototype_ `void startStream( void );`
- L1130 _public prototype_ `void stopStream( void );`
- L1131 _public prototype_ `void abortStream( void );`
- L1137 _public prototype_ `void callbackEvent( void );` — This function is intended for internal use only.  It must be public because it is called by the internal callback handler, which is not a member of RtAudio.  External use of this function will most likely produce highly undesireable results!
- L1141 _private member_ `std::vector<RtAudio::DeviceInfo> devices_;`
- L1142 _private prototype_ `void saveDeviceInfo( void );`
- L1143 _private prototype_ `bool probeDeviceOpen( unsigned int device, StreamMode mode, unsigned int channels, unsigned int firstChannel, unsigned int sampleRate, RtAudioFormat format, unsigned int *bufferSize, RtAudio::StreamOptions *options );`

#### class `RtApiOss`  
`class RtApiOss: public RtApi`  
_L1153-1179_
- inherits: `RtApi`
- L1157 _public prototype_ `RtApiOss();`
- L1158 _public prototype_ `~RtApiOss();`
- L1159 _public function_ `RtAudio::Api getCurrentApi()`
- L1160 _public prototype_ `unsigned int getDeviceCount( void );`
- L1161 _public prototype_ `RtAudio::DeviceInfo getDeviceInfo( unsigned int device );`
- L1162 _public prototype_ `void closeStream( void );`
- L1163 _public prototype_ `void startStream( void );`
- L1164 _public prototype_ `void stopStream( void );`
- L1165 _public prototype_ `void abortStream( void );`
- L1171 _public prototype_ `void callbackEvent( void );` — This function is intended for internal use only.  It must be public because it is called by the internal callback handler, which is not a member of RtAudio.  External use of this function will most likely produce highly undesireable results!
- L1175 _private prototype_ `bool probeDeviceOpen( unsigned int device, StreamMode mode, unsigned int channels, unsigned int firstChannel, unsigned int sampleRate, RtAudioFormat format, unsigned int *bufferSize, RtAudio::StreamOptions *options );`

#### class `RtApiDummy`  
`class RtApiDummy: public RtApi`  
_L1185-1204_
- inherits: `RtApi`
- L1189 _public function_ `RtApiDummy()`
- L1190 _public function_ `RtAudio::Api getCurrentApi( void )`
- L1191 _public function_ `unsigned int getDeviceCount( void )`
- L1192 _public function_ `RtAudio::DeviceInfo getDeviceInfo( unsigned int )`
- L1193 _public function_ `void closeStream( void )`
- L1194 _public function_ `void startStream( void )`
- L1195 _public function_ `void stopStream( void )`
- L1196 _public function_ `void abortStream( void )`
- L1200 _private function_ `bool probeDeviceOpen( unsigned int , StreamMode , unsigned int , unsigned int , unsigned int , RtAudioFormat , unsigned int * , RtAudio::StreamOptions * )`

#### Free symbols / members of external scopes

- L52 _macro_ `#define __RTAUDIO_H`
- L59 _macro_ `#define __WINDOWS_DS__`
- L76 _macro_ `#define __WINDOWS_WASAPI__`
- L81 _macro_ `#define __MACOSX_CORE__`
- L85 _macro_ `#define RTAUDIO_VERSION "5.0.0"`
- L88 _macro_ `#define RTAUDIO_DLL_PUBLIC`
- L91 _macro_ `#define RTAUDIO_DLL_PUBLIC __attribute__( (visibility( "default" )) )`
- L120 _typedef_ `typedef unsigned long RtAudioFormat;` — \typedef typedef unsigned long RtAudioFormat; \brief RtAudio data format type. Support for signed integers and floats.  Audio data fed to/from an RtAudio stream is assumed to ALWAYS be in host byte order.  The internal routines will automatically take care of any necessary byte-swapping between the host format and the soundcard.  Thus, endian-ness is not a concern in the following format definitions. - \e RTAUDIO_SINT8:   8-bit signed integer. - \e RTAUDIO_SINT16:  16-bit signed integer. - \e RTAUDIO_SINT24:  24-bit signed integer. - \e RTAUDIO_SINT32:  32-bit signed integer. - \e RTAUDIO_FLOAT32: Normalized between plus/minus 1.0. - \e RTAUDIO_FLOAT64: Normalized between plus/minus 1.0.
- L121 _variable_ `static const RtAudioFormat RTAUDIO_SINT8 = 0x1;` — 8-bit signed integer.
- L122 _variable_ `static const RtAudioFormat RTAUDIO_SINT16 = 0x2;` — 16-bit signed integer.
- L123 _variable_ `static const RtAudioFormat RTAUDIO_SINT24 = 0x4;` — 24-bit signed integer.
- L124 _variable_ `static const RtAudioFormat RTAUDIO_SINT32 = 0x8;` — 32-bit signed integer.
- L125 _variable_ `static const RtAudioFormat RTAUDIO_FLOAT32 = 0x10;` — Normalized between plus/minus 1.0.
- L126 _variable_ `static const RtAudioFormat RTAUDIO_FLOAT64 = 0x20;` — Normalized between plus/minus 1.0.
- L174 _typedef_ `typedef unsigned int RtAudioStreamFlags;` — \typedef typedef unsigned long RtAudioStreamFlags; \brief RtAudio stream option flags. The following flags can be OR'ed together to allow a client to make changes to the default stream behavior: - \e RTAUDIO_NONINTERLEAVED:   Use non-interleaved buffers (default = interleaved). - \e RTAUDIO_MINIMIZE_LATENCY: Attempt to set stream parameters for lowest possible latency. - \e RTAUDIO_HOG_DEVICE:       Attempt grab device for exclusive use. - \e RTAUDIO_ALSA_USE_DEFAULT: Use the "default" PCM device (ALSA only). - \e RTAUDIO_JACK_DONT_CONNECT: Do not automatically connect ports (JACK only). By default, RtAudio streams pass and receive audio data from the client in an interleaved format.  By passing the RTAUDIO_NONINTERLEAVED flag to the openStream() function, audio data will instead be presented in non-interleaved buffers.  In this case, each buffer argument in the RtAudioCallback function will point to a single array of data, with \c nFrames samples for each channel concatenated back-to-back.  For example, the first sample of data for the second channel would be located at index \c nFrames (assuming the \c buffer pointer was recast to the correct data type for the stream). Certain audio APIs offer a number of parameters that influence the I/O latency of a stream.  By default, RtAudio will attempt to set these parameters internally for robust (glitch-free) performance (though some APIs, like Windows Direct Sound, make this difficult). By passing the RTAUDIO_MINIMIZE_LATENCY flag
- L175 _variable_ `static const RtAudioStreamFlags RTAUDIO_NONINTERLEAVED = 0x1;` — Use non-interleaved buffers (default = interleaved).
- L176 _variable_ `static const RtAudioStreamFlags RTAUDIO_MINIMIZE_LATENCY = 0x2;` — Attempt to set stream parameters for lowest possible latency.
- L177 _variable_ `static const RtAudioStreamFlags RTAUDIO_HOG_DEVICE = 0x4;` — Attempt grab device and prevent use by others.
- L178 _variable_ `static const RtAudioStreamFlags RTAUDIO_SCHEDULE_REALTIME = 0x8;` — Try to select realtime scheduling for callback thread.
- L179 _variable_ `static const RtAudioStreamFlags RTAUDIO_ALSA_USE_DEFAULT = 0x10;` — Use the "default" PCM device (ALSA only).
- L180 _variable_ `static const RtAudioStreamFlags RTAUDIO_JACK_DONT_CONNECT = 0x20;` — Do not automatically connect ports (JACK only).
- L193 _typedef_ `typedef unsigned int RtAudioStreamStatus;` — \typedef typedef unsigned long RtAudioStreamStatus; \brief RtAudio stream status (over- or underflow) flags. Notification of a stream over- or underflow is indicated by a non-zero stream \c status argument in the RtAudioCallback function. The stream status can be one of the following two options, depending on whether the stream is open for output and/or input: - \e RTAUDIO_INPUT_OVERFLOW:   Input data was discarded because of an overflow condition at the driver. - \e RTAUDIO_OUTPUT_UNDERFLOW: The output buffer ran low, likely producing a break in the output sound.
- L194 _variable_ `static const RtAudioStreamStatus RTAUDIO_INPUT_OVERFLOW = 0x1;` — Input data was discarded because of an overflow condition at the driver.
- L195 _variable_ `static const RtAudioStreamStatus RTAUDIO_OUTPUT_UNDERFLOW = 0x2;` — The output buffer ran low, likely causing a gap in the output sound.
- L236 _typedef_ `typedef int (*RtAudioCallback)( void *outputBuffer, void *inputBuffer, unsigned int nFrames, double streamTime, RtAudioStreamStatus status, void *userData );` — All RtAudio clients must create a function of type RtAudioCallback to read and/or write data from/to the audio stream.  When the underlying audio system is ready for new input or output data, this function will be invoked. \param outputBuffer For output (or duplex) streams, the client should write \c nFrames of audio sample frames into this buffer.  This argument should be recast to the datatype specified when the stream was opened.  For input-only streams, this argument will be NULL. \param inputBuffer For input (or duplex) streams, this buffer will hold \c nFrames of input audio sample frames.  This argument should be recast to the datatype specified when the stream was opened.  For output-only streams, this argument will be NULL. \param nFrames The number of sample frames of input or output data in the buffers.  The actual buffer size in bytes is dependent on the data type and number of channels in use. \param streamTime The number of seconds that have elapsed since the stream was started. \param status If non-zero, this argument indicates a data overflow or underflow condition for the stream.  The particular condition can be determined by comparison with the RtAudioStreamStatus flags. \param userData A pointer to optional data provided by the client when opening the stream (default = NULL). To continue normal stream operation, the RtAudioCallback function should return a value of zero.  To stop the stream and drain the output buffer, the function should return a value of 
- L295 _typedef_ `typedef void (*RtAudioErrorCallback)( RtAudioError::Type type, const std::string &errorText );` — \param type Type of error. \param errorText Error description.
- L632 _macro_ `#define NOMINMAX`
- L637 _typedef_ `typedef uintptr_t ThreadHandle;`
- L638 _typedef_ `typedef CRITICAL_SECTION StreamMutex;`
- L644 _typedef_ `typedef pthread_t ThreadHandle;`
- L645 _typedef_ `typedef pthread_mutex_t StreamMutex;`
- L649 _macro_ `#define __RTAUDIO_DUMMY__`
- L650 _typedef_ `typedef int ThreadHandle;`
- L651 _typedef_ `typedef int StreamMutex;`
- L759 _enumerator_ `enum { FAILURE, SUCCESS }; enum StreamState { STREAM_STOPPED, STREAM_STOPPING, STREAM_RUNNING, STREAM_CLOSED = -50 };` (scope `RtApi::__anon141ad59c0103`)
- L759 _enumerator_ `enum { FAILURE, SUCCESS }; enum StreamState { STREAM_STOPPED, STREAM_STOPPING, STREAM_RUNNING, STREAM_CLOSED = -50 };` (scope `RtApi::__anon141ad59c0103`)

### `Source/Runtime/AudioCaptureImplementations/AudioCaptureRtAudio/Public/RtAudioWrapper.h` (Public)


#### class `Audio::FRtAudioInputWrapper`  
`class UE_DEPRECATED(5.3, "FRtAudioInputWrapper is deprecated, please use FAudioCapture instead.") FRtAudioInputWrapper`  
_L13-64_
- desc: FRtAudioInputWrapper wraps RtAudio implementation and provides a way to capture input audio from an hardware audio device.
- L16 _public member_ `static constexpr uint32 InvalidDeviceID = INDEX_NONE;`
- L19 _public typedef_ `using FAudioCallback = int (*)(void *OutputBuffer, void *InputBuffer, unsigned int NumFrames, double StreamTime, uint32 StreamStatus, void *UserData);` — Callback function for receiving audio from RtAudio
- L35 _public prototype_ `FRtAudioInputWrapper();`
- L38 _public prototype_ `uint32 GetDefaultInputDevice();` — Returns ID of default input device
- L41 _public prototype_ `FDeviceInfo GetDeviceInfo(uint32 InDeviceID);` — Returns info about device.
- L44 _public prototype_ `bool OpenStream(const FStreamParameters& InStreamParams, float InDesiredSampleRate, uint32* InOutDesiredBufferNumFrames, FAudioCallback Callback, void* InUserData);` — Opens an audio stream. Returns true on success, false on error.
- L47 _public prototype_ `bool IsStreamOpen();` — Returns true if the stream is open.
- L50 _public prototype_ `void StartStream();` — Starts an open stream
- L53 _public prototype_ `void AbortStream();` — Stops stream, discarding any remaining samples
- L56 _public prototype_ `void StopStream();` — Stops stream, allowing any remaining samples to be played.
- L59 _public prototype_ `void CloseStream();` — Close stream and free associated memory.
- L63 _private member_ `TPimplPtr<RtAudio> Impl;`

#### struct `Audio::FRtAudioInputWrapper::FStreamParameters`  
`struct FStreamParameters`  
_L22-26_
- desc: Parameters used for opening streams
- L24 _public member_ `uint32 DeviceID = 0;`
- L25 _public member_ `uint32 NumChannels = 0;`

#### struct `Audio::FRtAudioInputWrapper::FDeviceInfo`  
`struct FDeviceInfo`  
_L29-33_
- desc: Parameters describing audio input device.
- L31 _public member_ `float PreferredSampleRate = 0.f;`
- L32 _public member_ `uint32 NumChannels = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace Audio`
