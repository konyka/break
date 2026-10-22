# Plugins / AppleARKitFaceSupport

- module root: `Plugins/Runtime/AR/AppleAR/AppleARKitFaceSupport/Source/AppleARKitFaceSupport`
- headers: 8; symbols: 259
- symbol kinds: class=16, delegate=3, enum=2, enumerator=6, function=71, macro=1, member=64, prototype=91, struct=5
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AppleARKit, AppleImageUtils, AugmentedReality, CoreUObject, HeadMountedDisplay, LiveLinkInterface, OnlineSubsystem, ProceduralMeshComponent, PropertyEditor, Slate, SlateCore, Sockets, XRBase
- PublicDependencyModuleNames: Core, Engine

### `Plugins/Runtime/AR/AppleAR/AppleARKitFaceSupport/Source/AppleARKitFaceSupport/Private/AppleARKitFaceMeshConversion.h` (Private)


#### Free symbols / members of external scopes

- L10 _function_ `static FORCEINLINE TArray<int32> To32BitIndexBuffer(const int16_t* Indices, const uint64 IndexCount)`
- L27 _function_ `static FORCEINLINE TArray<FVector> ToVertexBuffer(const vector_float3* Vertices, const uint64 VertexCount)` — @todo JoeG - An option for which way to orient tris (down +X or -X)
- L39 _function_ `static FORCEINLINE FARBlendShapeMap ToBlendShapeMap(bool bFaceMirrored, NSDictionary<ARBlendShapeLocation,NSNumber *>* BlendShapes, const FTransform& Transform, const FTransform& LeftEyeTransform, const FTransform& RightEyeTransform)`
- L81 _macro_ `#define SET_BLEND_SHAPE(AppleShape, UEShape) \`

### `Plugins/Runtime/AR/AppleAR/AppleARKitFaceSupport/Source/AppleARKitFaceSupport/Private/AppleARKitFaceSupportImpl.h` (Private)


#### class `FAppleARKitFaceSupport`  
`class FAppleARKitFaceSupport : public IAppleARKitFaceSupport, public FSelfRegisteringExec, public TSharedFromThis<FAppleARKitFaceSupport, ESPMode::ThreadSafe>`  
_L13-85_
- inherits: `IAppleARKitFaceSupport,FSelfRegisteringExec,TSharedFromThis<FAppleARKitFaceSupport,ESPMode::ThreadSafe>`
- L19 _public prototype_ `FAppleARKitFaceSupport();`
- L20 _public prototype_ `virtual ~FAppleARKitFaceSupport();`
- L22 _public prototype_ `void Init();`
- L23 _public prototype_ `void Shutdown();`
- L28 _private prototype_ `virtual TArray<TSharedPtr<FAppleARKitAnchorData>> MakeAnchorData(NSArray<ARAnchor*>* NewAnchors, const FRotator& AdjustBy, EARFaceTrackingUpdate UpdateSetting) override;`
- L29 _private prototype_ `virtual ARConfiguration* ToARConfiguration(UARSessionConfig* InSessionConfig, UTimecodeProvider* InProvider) override;`
- L31 _private prototype_ `virtual bool DoesSupportFaceAR() override;`
- L34 _private prototype_ `virtual NSArray<ARVideoFormat*>* GetSupportedVideoFormats() const override;`
- L38 _private prototype_ `virtual bool IsARFrameSemanticsSupported(ARFrameSemantics InSemantics) const override;`
- L43 _private prototype_ `void ProcessRealTimePublishers(TSharedPtr<FAppleARKitAnchorData> AnchorData);` — Publishes the remote publisher and the file writer if present
- L45 _private prototype_ `virtual void PublishLiveLinkData(const FGuid& SessionGuid, TSharedPtr<FAppleARKitAnchorData> Anchor) override;`
- L48 _private prototype_ `virtual int32 GetNumberOfTrackedFacesSupported() const override;`
- L51 _private prototype_ `void InitRealtimeProviders();` — Inits the real time providers if needed
- L53 _private prototype_ `FName GetLiveLinkSubjectName(const FGuid& AnchorId);`
- L56 _private member_ `bool bFaceMirrored;` — Whether the face data is mirrored or not
- L60 _protected prototype_ `virtual bool Exec_Runtime(UWorld*, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L64 _protected member_ `TSharedPtr<ILiveLinkSourceARKit> LiveLinkSource;` — If requested, publishes face ar updates to LiveLink for the animation system to use
- L66 _protected member_ `FName LocalDeviceId;` — The id of this device
- L68 _protected member_ `TSharedPtr<IARKitBlendShapePublisher, ESPMode::ThreadSafe> RemoteLiveLinkPublisher;` — A publisher that sends to a remote machine
- L70 _protected member_ `TSharedPtr<IARKitBlendShapePublisher, ESPMode::ThreadSafe> LiveLinkFileWriter;` — A publisher that writes the data to disk
- L76 _protected member_ `UTimecodeProvider* TimecodeProvider;` — The time code provider to use when tagging time stamps Note: this requires the FAppleARKitSystem object to mark it in use so GC doesn't destroy it. Normally it would implement the FGCObject interface but this gets created before UObjects are init-ed so not possible
- L79 _protected member_ `FGuid LastSessionId;` — The id of the last session
- L82 _protected member_ `TMap<FGuid, FName> AnchorIdToSubjectName;` — { Anchor Id : livelink subject name }
- L84 _protected member_ `FCriticalSection AnchorIdLock;`

### `Plugins/Runtime/AR/AppleAR/AppleARKitFaceSupport/Source/AppleARKitFaceSupport/Private/AppleARKitFaceSupportModule.h` (Private)


#### class `FAppleARKitFaceSupportModule`  
`class FAppleARKitFaceSupportModule : public IModuleInterface`  
_L8-26_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private prototype_ `void OnModularFeatureAvailable(const FName& Type, class IModularFeature* ModularFeature);` — Handler called when a modular feature is made available. Used to start a remote listener after the livelink client is registered.
- L22 _private member_ `TSharedPtr<class FAppleARKitFaceSupport, ESPMode::ThreadSafe> FaceSupportInstance;` — Interface / helper for sending AR Face data to LiveLink from an IOS device.
- L25 _private member_ `TSharedPtr<class ILiveLinkSourceARKit> LiveLinkSource;` — LiveLinkSource responsible for receiving remote LiveLink data and publishing it to the LiveLink client.

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAppleARKitFace, Log, All);`
- L28 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAppleARKitFace, Log, All);`
- L30 _delegate_ `DECLARE_STATS_GROUP(TEXT("Face AR"), STATGROUP_FaceAR, STATCAT_Adv`

### `Plugins/Runtime/AR/AppleAR/AppleARKitFaceSupport/Source/AppleARKitFaceSupport/Private/AppleARKitLiveLinkConnectionSettings.h` (Private)


#### struct `FAppleARKitLiveLinkConnectionSettings`  
`struct FAppleARKitLiveLinkConnectionSettings`  
_L8-15_
- reflection: `USTRUCT()`
- L14 _public member_ `int32 Port = 11111;` — `UPROPERTY(EditAnywhere, Category = "Connection Settings", meta = (ClampMin = "1", ClampMax = "32765"))` — The port to use when listening/sending LiveLink face blend shapes via the network

### `Plugins/Runtime/AR/AppleAR/AppleARKitFaceSupport/Source/AppleARKitFaceSupport/Private/AppleARKitLiveLinkSource.h` (Private)


#### class `FNboSerializeToBuffer`  
`class FNboSerializeToBuffer`  
_L25-409_
- desc: Serializes data in network byte order form into a buffer
- L28 _private prototype_ `FNboSerializeToBuffer(void);` — Hidden on purpose
- L34 _protected member_ `TArray<uint8> Data;` — Holds the data as it is serialized
- L38 _protected member_ `uint32 NumBytes;` — Tracks how many bytes have been written in the packet
- L41 _protected member_ `bool bHasOverflowed;` — Indicates whether writing to the buffer caused an overflow or not
- L47 _public function_ `FNboSerializeToBuffer(uint32 Size) : NumBytes(0), bHasOverflowed(false)` — Inits the write tracking
- L58 _public function_ `inline operator uint8*(void) const` — Cast operator to get at the formatted buffer data
- L66 _public function_ `inline const TArray<uint8>& GetBuffer(void) const` — Cast operator to get at the formatted buffer data
- L74 _public function_ `inline uint32 GetByteCount(void) const` — Returns the size of the buffer we've built up
- L82 _public function_ `inline uint32 GetBufferSize(void) const` — Returns the number of bytes preallocated in the array
- L90 _public function_ `inline void TrimBuffer()` — Trim any extra space in the buffer that is not used
- L101 _public function_ `inline void Reset()` — Act as if the buffer is now empty. Useful for buffers that are reused
- L287 _public function_ `inline FNboSerializeToBuffer& AddString(const ANSICHAR* String,const int32 Length)` — Adds a substring to the buffer
- L366 _public function_ `inline void WriteBinary(const uint8* Buffer,uint32 NumToWrite)` — Writes a blob of data to the buffer @param Buffer the source data to append @param NumToWrite the size of the blob to write
- L382 _public function_ `inline uint8* GetRawBuffer(uint32 Offset)` — Gets the buffer at a specific point
- L392 _public function_ `inline void SkipAheadBy(uint32 Amount)` — Skips forward in the buffer by the specified amount @param Amount the number of bytes to skip ahead
- L405 _public function_ `inline bool HasOverflow(void) const` — Returns whether the buffer had an overflow when writing to it

#### class `FNboSerializeFromBuffer`  
`class FNboSerializeFromBuffer`  
_L418-714_
- desc: Class used to read data from a NBO data buffer
- L422 _protected member_ `const uint8* Data;` — Pointer to the data this reader is attached to
- L424 _protected member_ `const int32 NumBytes;` — The size of the data in bytes
- L426 _protected member_ `int32 CurrentOffset;` — The current location in the byte stream for reading
- L428 _protected member_ `bool bHasOverflowed;` — Indicates whether reading from the buffer caused an overflow or not
- L431 _protected prototype_ `FNboSerializeFromBuffer(void);` — Hidden on purpose
- L440 _public function_ `FNboSerializeFromBuffer(const uint8* InData,int32 Length) : Data(InData), NumBytes(Length), CurrentOffset(0), bHasOverflowed(false)` — Initializes the buffer, size, and zeros the read offset @param InData the buffer to attach to @param Length the size of the buffer we are attaching to
- L657 _public function_ `void ReadBinary(uint8* OutBuffer,uint32 NumToRead)` — Reads a blob of data from the buffer @param OutBuffer the destination buffer @param NumToRead the size of the blob to read
- L675 _public function_ `void Seek(int32 Pos)` — Seek to the desired position in the buffer @param Pos the offset from the start of the buffer
- L690 _public function_ `inline int32 Tell(void) const` — @return Current position of the buffer being to be read
- L696 _public function_ `inline bool HasOverflow(void) const` — Returns whether the buffer had an overflow when reading from it
- L702 _public function_ `inline int32 AvailableToRead(void) const` — @return Number of bytes remaining to read from the current offset to the end of the buffer
- L710 _public function_ `inline int32 GetBufferSize(void) const` — Returns the number of total bytes in the buffer

#### class `FAppleARKitLiveLinkRemoteListener`  
`class FAppleARKitLiveLinkRemoteListener : public FTickableGameObject`  
_L725-756_
- inherits: `FTickableGameObject`
- desc: Listens for LiveLink publication events and publishes them to the local LiveLinkClient
- L729 _public prototype_ `FAppleARKitLiveLinkRemoteListener(const TSharedPtr<ILiveLinkSourceARKit>& ArkitSource);`
- L730 _public prototype_ `virtual ~FAppleARKitLiveLinkRemoteListener();`
- L733 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableGameObject interface
- L734 _public function_ `virtual bool IsTickable() const override`
- L735 _public function_ `virtual TStatId GetStatId() const override`
- L739 _public function_ `virtual bool IsTickableInEditor() const override`
- L740 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L743 _public prototype_ `bool InitReceiveSocket(int32 Port);`
- L748 _private member_ `FSocket* RecvSocket;` — Socket that is read from to publish remote data to this local LiveLinkClient
- L750 _private member_ `TArray<uint8> RecvBuffer;` — Buffer to reuse for receiving data
- L752 _private member_ `FARBlendShapeMap BlendShapes;` — The reused blend shape map to avoid allocs/frees
- L755 _private member_ `TWeakPtr<ILiveLinkSourceARKit> Source;` — The source used to publish events from the remote socket

#### class `FAppleARKitLiveLinkRemotePublisher`  
`class FAppleARKitLiveLinkRemotePublisher : public IARKitBlendShapePublisher`  
_L759-783_
- inherits: `IARKitBlendShapePublisher`
- desc: Forwards face blend shapes to another machine for LiveLink publication
- L763 _public prototype_ `FAppleARKitLiveLinkRemotePublisher();`
- L764 _public prototype_ `FAppleARKitLiveLinkRemotePublisher(const FString& InRemoteIp);`
- L765 _public prototype_ `virtual ~FAppleARKitLiveLinkRemotePublisher();`
- L768 _public prototype_ `virtual void PublishBlendShapes(FName SubjectName, const FQualifiedFrameTime& FrameTime, const FARBlendShapeMap& FaceBlendShapes, FName DeviceId = NAME_None) override;` — IARKitBlendShapePublisher interface
- L769 _public function_ `virtual void Shutdown() override`
- L772 _public prototype_ `bool InitSendSocket();`
- L775 _private prototype_ `TSharedRef<FInternetAddr> GetSendAddress();`
- L778 _private member_ `FString RemoteIp;` — The IP address to send the blend shapes to
- L780 _private member_ `FSocket* SendSocket;` — Socket to send the data via to the remote listener
- L782 _private member_ `FNboSerializeToBuffer SendBuffer;` — The ram buffer to serialize the packet to

#### class `FAppleARKitLiveLinkFileWriter`  
`class FAppleARKitLiveLinkFileWriter : public FSelfRegisteringExec, public IARKitBlendShapePublisher`  
_L786-837_
- inherits: `FSelfRegisteringExec,IARKitBlendShapePublisher`
- desc: Writes files to disk with the face tracking information
- L791 _public function_ `virtual ~FAppleARKitLiveLinkFileWriter()`
- L792 _public prototype_ `virtual void SetTimecodeProvider(UTimecodeProvider* InTimecodeProvider = nullptr) override;`
- L793 _public prototype_ `virtual void Shutdown() override;`
- L796 _protected prototype_ `FAppleARKitLiveLinkFileWriter(const TCHAR* InFileExtension);`
- L811 _protected prototype_ `virtual void PublishBlendShapes(FName SubjectName, const FQualifiedFrameTime& FrameTime, const FARBlendShapeMap& FaceBlendShapes, FName DeviceId = NAME_None) override;` — IARKitBlendShapePublisher interface
- L815 _protected prototype_ `virtual bool Exec_Runtime(UWorld*, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L818 _protected prototype_ `virtual FString BuildSaveData() = 0;`
- L820 _protected prototype_ `void SaveFileData();`
- L821 _protected prototype_ `FString GenerateFilePath();`
- L824 _protected member_ `FCriticalSection CriticalSection;` — Needed because Exec commands are on the game thread and updates are on an arbitrary thread
- L826 _protected member_ `FString FileExtension;` — The file extension to write to
- L828 _protected member_ `TArray<FFaceTrackingFrame> FrameHistory;` — The list of the last frames seen. Used when rolling up all data in one file
- L830 _protected member_ `FName DeviceName;` — The name to use when generating the file to save to
- L836 _protected member_ `UTimecodeProvider* TimecodeProvider;` — The time code provider to use when tagging file time stamps Note: this requires the FAppleARKitSystem object to mark it in use so GC doesn't destroy it. Normally it would implement the FGCObject interface but this gets created before UObjects are init-ed so not possible

#### struct `FAppleARKitLiveLinkFileWriter::FFaceTrackingFrame`  
`struct FFaceTrackingFrame`  
_L798-808_
- L800 _public function_ `FFaceTrackingFrame(const FQualifiedFrameTime& InFrameTime, const FARBlendShapeMap& InBlendShapes) : FrameTime(InFrameTime) , BlendShapes(InBlendShapes)`
- L806 _public member_ `FQualifiedFrameTime FrameTime;`
- L807 _public member_ `FARBlendShapeMap BlendShapes;`

#### class `FAppleARKitLiveLinkFileWriterJson`  
`class FAppleARKitLiveLinkFileWriterJson : public FAppleARKitLiveLinkFileWriter`  
_L839-854_
- inherits: `FAppleARKitLiveLinkFileWriter`
- L843 _public prototype_ `FAppleARKitLiveLinkFileWriterJson();`
- L844 _public function_ `virtual ~FAppleARKitLiveLinkFileWriterJson()`
- L848 _private prototype_ `virtual FString BuildSaveData() override;`
- L849 _private prototype_ `FString BuildJsonRow(const FFaceTrackingFrame& Frame);`
- L853 _private member_ `TArray<FString> BlendShapeJsonKeyNames;` — A list of the keys to use when generating JSON files, cached because can't access off game thread

#### class `FAppleARKitLiveLinkFileWriterCsv`  
`class FAppleARKitLiveLinkFileWriterCsv : public FAppleARKitLiveLinkFileWriter`  
_L856-871_
- inherits: `FAppleARKitLiveLinkFileWriter`
- L860 _public prototype_ `FAppleARKitLiveLinkFileWriterCsv();`
- L861 _public function_ `virtual ~FAppleARKitLiveLinkFileWriterCsv()`
- L865 _private prototype_ `virtual FString BuildSaveData() override;`
- L866 _private prototype_ `FString BuildCsvRow(const FFaceTrackingFrame& Frame);`
- L870 _private member_ `FString CsvFrameHeader;` — A pre-made header to use when writing CSV files, cached because can't access off game thread

#### class `FAppleARKitLiveLinkSource`  
`class FAppleARKitLiveLinkSource : public ILiveLinkSourceARKit, public TSharedFromThis<FAppleARKitLiveLinkSource>`  
_L874-931_
- inherits: `ILiveLinkSourceARKit,TSharedFromThis<FAppleARKitLiveLinkSource>`
- desc: Publishes face blend shapes to LiveLink for use locally
- L878 _public prototype_ `FAppleARKitLiveLinkSource();`
- L880 _public prototype_ `FAppleARKitLiveLinkSource(FAppleARKitLiveLinkConnectionSettings InConnectionSettings);` — Constructor invoked from the AppleARKitLiveLinkSourceFactory wit the settings specified by the user.
- L881 _public function_ `virtual ~FAppleARKitLiveLinkSource()`
- L884 _public prototype_ `void InitializeRemoteListener();` — Bind the remote listener to the port provided by this source's connection settings.
- L886 _public function_ `virtual void Shutdown() override`
- L889 _private prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;` — ILiveLinkSource interface
- L890 _private prototype_ `virtual void InitializeSettings(ULiveLinkSourceSettings* Settings) override;`
- L891 _private prototype_ `virtual bool IsSourceStillValid() const override;`
- L892 _private prototype_ `virtual bool RequestSourceShutdown() override;`
- L893 _private prototype_ `virtual FText GetSourceMachineName() const override;`
- L894 _private prototype_ `virtual FText GetSourceStatus() const override;`
- L895 _private prototype_ `virtual FText GetSourceType() const override;`
- L899 _private prototype_ `virtual void PublishBlendShapes(FName SubjectName, const FQualifiedFrameTime& FrameTime, const FARBlendShapeMap& FaceBlendShapes, FName DeviceId = NAME_None) override;` — IARKitBlendShapePublisher interface
- L903 _private prototype_ `void UpdateStaticData(FName SubjectName, const FARBlendShapeMap& FaceBlendShapes, FName DeviceId);` — Update static data property names from blend shape map. Should only happen once per subject name. Pushes static data to livelink to register subject
- L908 _private member_ `ILiveLinkClient* Client;` — The local client to push data updates to
- L911 _private member_ `FGuid SourceGuid;` — Our identifier in LiveLink
- L914 _private member_ `uint32 LastFramePublished;` — The last time we sent the data. Used to not send redundant data
- L924 _private member_ `TMap<FName, FBlendShapeStaticData> BlendShapePerDeviceMap;` — Used to track names changes for a given device and keep track of property names contained in subject
- L927 _private member_ `TUniquePtr<FAppleARKitLiveLinkRemoteListener> RemoteListener;` — Used to listen on a socket for incoming face data and publishing this data to livelink.
- L930 _private member_ `FAppleARKitLiveLinkConnectionSettings ConnectionSettings;` — Connection settings for this source.

#### struct `FAppleARKitLiveLinkSource::FBlendShapeStaticData`  
`struct FBlendShapeStaticData`  
_L917-921_
- desc: Helper struct to contain BlendShape data per deviceId
- L919 _public member_ `FLiveLinkSubjectKey SubjectKey;`
- L920 _public member_ `FLiveLinkSkeletonStaticData StaticData;`

#### Free symbols / members of external scopes

- L110 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const char Ch)` — Adds a char to the buffer
- L127 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const uint8& B)` — Adds a byte to the buffer
- L145 _function_ `template<class TEnum> friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const TEnumAsByte<TEnum>& B)` — Adds a byte to the buffer
- L153 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const int32& I)` — Adds an int32 to the buffer
- L161 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const uint32& D)` — Adds a uint32 to the buffer
- L182 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const uint64& Q)` — Adds a uint64 to the buffer
- L207 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const float& F)` — Adds a float to the buffer
- L216 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const double& Dbl)` — Adds a double to the buffer
- L225 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const FString& String)` — Adds a FString to the buffer
- L256 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const TCHAR* String)` — Adds a string to the buffer
- L314 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const FName& Name)` — Adds an FName to the buffer as a string
- L325 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const FInternetAddr& Addr)` — Adds an ip address to the buffer
- L339 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const FGuid& Guid)` — Adds a FGuid to the buffer
- L351 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar, const FQualifiedFrameTime& FrameTime)` — Adds a FQualifiedFrameTime to the buffer
- L451 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,char& Ch)` — Reads a char from the buffer
- L467 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,uint8& B)` — Reads a byte from the buffer
- L483 _function_ `template<class TEnum> friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,TEnumAsByte<TEnum>& B)` — Reads a byte from the buffer
- L491 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,int32& I)` — Reads an int32 from the buffer
- L499 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,uint32& D)` — Reads a uint32 from the buffer
- L520 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,uint64& Q)` — Adds a uint64 to the buffer
- L544 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,float& F)` — Reads a float from the buffer
- L552 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,double& Dbl)` — Reads a double from the buffer
- L560 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,FString& String)` — Reads a FString from the buffer
- L599 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,FName& Name)` — Reads an FName from the buffer
- L610 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,FInternetAddr& Addr)` — Reads an ip address from the buffer
- L624 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,FGuid& Guid)` — Reads a FGuid from the buffer
- L636 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar, FQualifiedFrameTime& FrameTime)` — Reads a FQualifiedFrameTime from the buffer

### `Plugins/Runtime/AR/AppleAR/AppleARKitFaceSupport/Source/AppleARKitFaceSupport/Private/SAppleARKitLiveLinkSourceFactory.h` (Private)


#### class `SAppleARKitLiveLinkSourceFactory`  
`class SAppleARKitLiveLinkSourceFactory : public SCompoundWidget`  
_L19-39_
- inherits: `SCompoundWidget`
- L21 _private function_ `SLATE_BEGIN_ARGS(SAppleARKitLiveLinkSourceFactory)`
- L23 _private prototype_ `SLATE_EVENT(FOnConnectionSettingsAccepted, OnConnectionSettingsAccepted) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L30 _private member_ `FAppleARKitLiveLinkConnectionSettings ConnectionSettings;`
- L33 _private member_ `TSharedPtr<FStructOnScope> StructOnScope;`
- L34 _private member_ `TSharedPtr<IStructureDetailsView> StructureDetailsView;`
- L37 _private prototype_ `FReply OnSettingsAccepted();`
- L38 _private member_ `FOnConnectionSettingsAccepted OnConnectionSettingsAccepted;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnConnectionSettingsAccepted, const FAppleARKitLiveLinkConnectionSettings&);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnConnectionSettingsAccepted, const FAppleARKitLiveLinkConnectionSettings&);`

### `Plugins/Runtime/AR/AppleAR/AppleARKitFaceSupport/Source/AppleARKitFaceSupport/Public/AppleARKitFaceMeshComponent.h` (Public)


#### enum `EARFaceComponentTransformMixing`  
`enum class EARFaceComponentTransformMixing : uint8`  
_L14-24_
- reflection: `UENUM(BlueprintType, Category="AR AugmentedReality", meta=(Experimental))`
- L17 _public enumerator_ `ComponentOnly` — Uses the component's transform exclusively. Only setting for non-tracked meshes
- L19 _public enumerator_ `ComponentLocationTrackedRotation` — Use the component's location and apply the rotation from the tracked mesh
- L21 _public enumerator_ `ComponentWithTracked` — Concatenate the component and the tracked face transforms
- L23 _public enumerator_ `TrackingOnly` — Use only the tracked face transform

#### struct `FNetQuantizeFaceCurve`  
`struct FNetQuantizeFaceCurve`  
_L30-94_
- reflection: `USTRUCT()`
- desc: Packs the curve into 2 bytes with the amount being +/- 127
- L34 _public function_ `inline FNetQuantizeFaceCurve()`
- L38 _public function_ `inline FNetQuantizeFaceCurve(EARFaceBlendShape InBlendShape, float InAmount) : BlendShape((uint8)InBlendShape) , Amount(ConvertAmountToInt(InAmount))`
- L44 _public function_ `inline float GetAmountAsFloat() const`
- L49 _public function_ `inline EARFaceBlendShape GetBlendShape() const`
- L55 _public function_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)`
- L73 _public function_ `static bool IsDifferentEnough(float Val1, float Val2)`
- L79 _private member_ `static constexpr float Scale = 127.f;`
- L80 _private member_ `static constexpr float InvScale = 1.f / Scale;`
- L82 _private function_ `static inline float ConvertAmountToFloat(int8 InAmount)`
- L87 _private function_ `static inline int8 ConvertAmountToInt(float InAmount)`
- L92 _private member_ `uint8 BlendShape;`
- L93 _private member_ `int8 Amount;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FNetQuantizeFaceCurve > : public TStructOpsTypeTraitsBase2< FNetQuantizeFaceCurve >`  
_L97-104_
- inherits: `TStructOpsTypeTraitsBase2<FNetQuantizeFaceCurve>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L100-103_

#### class `UAppleARKitFaceMeshComponent`  
`class UAppleARKitFaceMeshComponent : public UProceduralMeshComponent`  
_L110-262_
- reflection: `UCLASS(hidecategories = (Object, LOD, "Components|ProceduralMesh"), meta = (BlueprintSpawnableComponent), ClassGroup = "AR")`
- inherits: `UProceduralMeshComponent`
- desc: This component is updated by the ARSystem with face data on devices that have support for it
- L124 _public prototype_ `void CreateMesh(const TArray<FVector>& Vertices, const TArray<int32>& Triangles, const TArray<FVector2D>& UV0);` — `UFUNCTION(BlueprintCallable, Category = "Components|ARFaceMesh", meta = (DisplayName = "Create Face Mesh", AutoCreateRefTerm = "UV0"))` — Create the initial face mesh from raw mesh data @param	Vertices			Vertex buffer of all vertex positions to use for this mesh section. @param	Triangles			Index buffer indicating which vertices make up each triangle. Length must be a multiple of 3. @param	UV0					Optional array of texture co-ordinates for each vertex. If supplied, must be same length as Vertices array.
- L132 _public prototype_ `void SetBlendShapes(const TMap<EARFaceBlendShape, float>& InBlendShapes);` — `UFUNCTION(BlueprintCallable, Category = "Components|ARFaceMesh", meta = (DisplayName = "Create Face Mesh from Blend Shapes"))` — Set all of the blend shapes for this instance from a set of blend shapes @param	BlendShapes			The set of blend shapes to conform the face mesh to
- L141 _public prototype_ `void SetBlendShapeAmount(EARFaceBlendShape BlendShape, float Amount);` — `UFUNCTION(BlueprintCallable, Category = "Components|ARFaceMesh", meta = (DisplayName = "Set the value of a Blend Shape"))` — Sets the amount for a given blend shape @param	BlendShape			The blend shape to modify @param	Amount				The amount of the blend shape to apply (0..1)
- L151 _public prototype_ `float GetFaceBlendShapeAmount(EARFaceBlendShape BlendShape) const;` — `UFUNCTION(BlueprintPure, Category = "Components|ARFaceMesh")` — Returns the value of the specified blend shape @param BlendShape			The blend shape to query @return the current amount the blend shape should be applied
- L157 _public prototype_ `void UpdateMeshFromBlendShapes();` — `UFUNCTION(BlueprintCallable, Category = "Components|ARFaceMesh", meta = (DisplayName = "Update Face Mesh from Blend Shapes"))` — Create/replace the face mesh from the current set of blend shapes if the device supports it
- L165 _public prototype_ `void UpdateMesh(const TArray<FVector>& Vertices);` — `UFUNCTION(BlueprintCallable, Category = "Components|ARFaceMesh", meta = (DisplayName = "Update Mesh Section FColor"))` — Updates the face mesh vertices. The topology and UVs do not change post creation so only vertices are updated @param	Vertices			Vertex buffer of all vertex positions to use for this mesh section.
- L173 _public prototype_ `void SetAutoBind(bool bAutoBind);` — `UFUNCTION(BlueprintCallable, Category = "Components|ARFaceMesh", meta = (DisplayName = "Modify auto bind to local face tracking"))` — If auto bind is true, then this component will update itself from the local face tracking data each tick. If auto bind is off, ticking is disabled @param	bAutoBind			true to enable, false to disable
- L177 _public prototype_ `int32 GetLastUpdateFrameNumber() const;` — `UFUNCTION(BlueprintPure, Category = "Components|ARFaceMesh")` — Returns the frame number that was last used to update this component
- L181 _public prototype_ `float GetLastUpdateTimestamp() const;` — `UFUNCTION(BlueprintPure, Category = "Components|ARFaceMesh")` — Returns the frame timestamp that was last used to update this component
- L185 _public prototype_ `void PublishViaLiveLink(FName SubjectName);` — `UFUNCTION(BlueprintCallable, Category = "Components|ARFaceMesh")` — Starts LiveLink publishing of this face component's data so that it can be used by the animation system
- L189 _public prototype_ `FTransform GetTransform() const;` — `UFUNCTION(BlueprintPure, Category = "Components|ARFaceMesh")` — Get the transform that the AR camera has detected
- L193 _public member_ `bool bWantsMeshUpdates;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components|ARFaceMesh")` — Indicates whether the face mesh data should be built for rendering or not
- L197 _public member_ `bool bWantsCollision;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components|ARFaceMesh")` — Indicates whether collision should be created for this face mesh. This adds significant cost, so only use if you need to trace against the face mesh.
- L201 _public member_ `bool bAutoBindToLocalFaceMesh;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components|ARFaceMesh")` — If true, the mesh data will come from the local ARKit face mesh data. The face mesh will update every tick and will handle loss of face tracking
- L205 _public member_ `EARFaceComponentTransformMixing TransformSetting;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components|ARFaceMesh")` — Determines how the transform from tracking data and the component's transform are mixed together
- L209 _public member_ `bool bFlipTrackedRotation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components|ARFaceMesh")` — If true, the face mesh will be rotated to face out of the screen (-X) rather than into the screen (+X) and corresponding axises to match
- L213 _public member_ `TObjectPtr<class UMaterialInterface> FaceMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components|ARFaceMesh")` — Used when rendering the face mesh (mostly debug reasons)
- L217 _public member_ `FName LiveLinkSubjectName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components|ARFaceMesh")` — Used to identify this component's face ar data uniquely as part of the LiveLink animation pipeline
- L221 _public member_ `TArray<FNetQuantizeFaceCurve> RemoteCurves;` — `UPROPERTY(ReplicatedUsing=OnRep_RemoteCurves, Transient)` — The set of changed curves to replicate to the other clients
- L224 _private prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L225 _private prototype_ `virtual void InitializeComponent() override;`
- L226 _private prototype_ `virtual FMatrix GetRenderMatrix() const override;`
- L227 _private prototype_ `virtual class UMaterialInterface* GetMaterial(int32 ElementIndex) const override;`
- L228 _private prototype_ `virtual void SetMaterial(int32 ElementIndex, class UMaterialInterface* Material) override;`
- L232 _private prototype_ `void OnRep_RemoteCurves();` — `UFUNCTION()` — Merges in the face curve deltas and pushes them to LiveLink
- L240 _private prototype_ `void ServerUpdateFaceCurves(const TArray<FNetQuantizeFaceCurve>& ClientCurves);` — `UFUNCTION(Reliable, Server, WithValidation)` — Sends the updated curves from the client to the server so that it can replicate to other clients @param ClientCurves the client's set of updated curves
- L247 _private prototype_ `void BuildUpdatedCurves(const FARBlendShapeMap& NewCurves);` — Builds the delta set of curves needed for replication @param NewCurves the updated set of curves from the ar system
- L249 _private prototype_ `UARFaceGeometry* FindFaceGeometry();`
- L252 _private member_ `FARBlendShapeMap BlendShapes;` — The current set of blend shapes for this component instance
- L254 _private member_ `FTransform LocalToWorldTransform;` — Transform of the face mesh
- L257 _private member_ `uint32 LastUpdateFrameNumber;` — The frame number this component was last updated on
- L259 _private member_ `double LastUpdateTimestamp;` — The time reported by the AR system that this object was last updated
- L261 _private member_ `TSharedPtr<ILiveLinkSourceARKit> LiveLinkSource;` — If this mesh is being published via LiveLink, the source to update with blendshapes

#### Free symbols / members of external scopes

- L101 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon9cd5a6600103`)
- L102 _enumerator_ `WithNetSharedSerialization = true` (scope `TStructOpsTypeTraits::__anon9cd5a6600103`)

### `Plugins/Runtime/AR/AppleAR/AppleARKitFaceSupport/Source/AppleARKitFaceSupport/Public/AppleARKitLiveLinkSourceFactory.h` (Public)


#### class `IARKitBlendShapePublisher`  
`class IARKitBlendShapePublisher`  
_L15-21_
- desc: Interface that publishes face ar blend shape information
- L18 _public function_ `virtual void SetTimecodeProvider(UTimecodeProvider* InTimecodeProvider = nullptr)`
- L19 _public prototype_ `virtual void PublishBlendShapes(FName SubjectName, const FQualifiedFrameTime& FrameTime, const FARBlendShapeMap& BlendShapes, FName DeviceID = NAME_None) = 0;`
- L20 _public prototype_ `virtual void Shutdown() = 0;`

#### class `ILiveLinkSourceARKit`  
`class ILiveLinkSourceARKit : public IARKitBlendShapePublisher, public ILiveLinkSource`  
_L24-28_
- inherits: `IARKitBlendShapePublisher,ILiveLinkSource`
- desc: Interface that publishes face ar blend shape information via LiveLink

#### class `FAppleARKitLiveLinkSourceFactory`  
`class FAppleARKitLiveLinkSourceFactory`  
_L31-45_
- desc: Factory that creates and registers the sources with the LiveLink client
- L35 _public prototype_ `static TSharedPtr<ILiveLinkSourceARKit> CreateLiveLinkSource();` — Creates a face mesh source that will autobind to the tracked face mesh
- L38 _public prototype_ `static TSharedPtr<ILiveLinkSourceARKit> CreateLiveLinkSource(const FAppleARKitLiveLinkConnectionSettings& ConnectionSettings);` — Creates a AppleARKit source that holds a livelink remote listener.
- L41 _public prototype_ `static TSharedPtr<IARKitBlendShapePublisher, ESPMode::ThreadSafe> CreateLiveLinkRemotePublisher(const FString& RemoteAddr = FString());` — Creates the publisher that will send remote events to a specified IP
- L44 _public prototype_ `static TSharedPtr<IARKitBlendShapePublisher, ESPMode::ThreadSafe> CreateLiveLinkLocalFileWriter();` — Creates the publisher that will write the curve data to disk

#### class `UAppleARKitLiveLinkSourceFactory`  
`class UAppleARKitLiveLinkSourceFactory : public ULiveLinkSourceFactory`  
_L48-62_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceFactory`
- L53 _public prototype_ `virtual FText GetSourceDisplayName() const override;`
- L54 _public prototype_ `virtual FText GetSourceTooltip() const override;`
- L56 _public function_ `virtual EMenuType GetMenuType() const override`
- L57 _public prototype_ `virtual TSharedPtr<SWidget> BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const override;`
- L58 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const override;`
- L61 _private prototype_ `void CreateSourceFromSettings(const FAppleARKitLiveLinkConnectionSettings& ConnectionSettings, FOnLiveLinkSourceCreated OnSourceCreated) const;`
