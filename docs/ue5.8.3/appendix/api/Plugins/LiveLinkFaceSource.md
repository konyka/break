# Plugins / LiveLinkFaceSource

- module root: `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSource`
- headers: 9; symbols: 155
- symbol kinds: class=9, delegate=5, enum=2, enumerator=5, function=2, member=50, namespace=2, prototype=78, struct=1, typedef=1
- PrivateDependencyModuleNames: CaptureProtocolStack, CaptureUtils, CoreUObject, HTTP, InputCore, Json, JsonUtilities, LiveLink, LiveLinkInterface, MetaHumanCoreTech, MetaHumanLiveLinkSource, Networking, Slate, SlateCore, Sockets
- PublicDependencyModuleNames: Core, Engine

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSource/Private/LiveLinkFaceControl.h` (Private)


#### class `FLiveLinkFaceControl`  
`class FLiveLinkFaceControl : public FRunnable`  
_L14-106_
- inherits: `FRunnable`
- L41 _public typedef_ `using FRemoteSubjects = TArray<FRemoteSubject>;`
- L43 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(const FRemoteSubject, FOnSelectRemoteSubject, const FRemoteSubjects&);`
- L44 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnStreamingStarted, const FRemoteSubject&);`
- L46 _public prototype_ `FLiveLinkFaceControl(FGuid InSourceGuid, FString InControlHost, uint16 InControlPort, uint16 InStreamPort, FOnSelectRemoteSubject InOnSelectRemoteSubject, FOnStreamingStarted InOnStreamingStarted);`
- L47 _public prototype_ `~FLiveLinkFaceControl();`
- L49 _public prototype_ `void Start();`
- L51 _public prototype_ `void RestartConnection();`
- L53 _public prototype_ `const FText& GetServerName() const;`
- L54 _public prototype_ `const FText& GetServerModel() const;`
- L55 _public prototype_ `const FText& GetServerPlatform() const;`
- L59 _public prototype_ `virtual uint32 Run() override;`
- L60 _public prototype_ `virtual void Stop() override;`
- L66 _private member_ `bool bIsConnected;`
- L69 _private member_ `bool bStopping;` — Flag indicating that the thread is stopping.
- L71 _private member_ `TUniquePtr<UE::CaptureManager::FControlMessenger> ControlMessenger;`
- L73 _private member_ `FText ServerName;`
- L74 _private member_ `FText ServerModel;`
- L75 _private member_ `FText ServerPlatform;`
- L77 _private member_ `const FString Host;`
- L79 _private member_ `const uint16 Port;`
- L81 _private member_ `const FGuid SourceGuid;`
- L83 _private member_ `const uint16 StreamPort;`
- L85 _private member_ `FRemoteSubjects RemoteSubjects;`
- L87 _private member_ `const FOnSelectRemoteSubject SelectRemoteSubjectDelegate;`
- L88 _private member_ `const FOnStreamingStarted StreamingStartedDelegate;`
- L90 _private member_ `TUniquePtr<FRunnableThread> Thread;`
- L92 _private prototype_ `bool StartSession();`
- L93 _private prototype_ `void StopSession();`
- L95 _private prototype_ `bool Connect();`
- L96 _private prototype_ `bool StartControlSession();`
- L97 _private prototype_ `bool GetControlServerInformation();`
- L98 _private prototype_ `bool GetSubjects();`
- L99 _private prototype_ `bool StartStreaming(const FRemoteSubject& InRemoteSubject);`
- L100 _private prototype_ `void StopStreaming();`
- L101 _private prototype_ `void StopControlSession();`
- L102 _private prototype_ `void Disconnect();`
- L104 _private prototype_ `void OnDisconnect(const FString& InCause);`

#### struct `FLiveLinkFaceControl::FRemoteSubject`  
`struct FRemoteSubject`  
_L18-39_
- L26 _public member_ `FString Id;`
- L27 _public member_ `FString Name;`
- L28 _public member_ `EAnimationType AnimationType;`
- L29 _public member_ `uint16 AnimationVersion;`
- L30 _public member_ `TArray<FName> PropertyNames;`
- L32 _public function_ `FRemoteSubject(const FString& InId, const FString& InName, const EAnimationType InAnimationType, const uint16 InAnimationVersion, const TArray<FName>& InPropertyNames) : Id(InId) , Name(InName) , AnimationType(InAnimationType) , AnimationVersion(InAnimationVersion) , PropertyNames(InPropertyNames)`

#### enum `FLiveLinkFaceControl::FRemoteSubject::EAnimationType`  
`enum class EAnimationType`  
_L20-24_
- L22 _public enumerator_ `ArKit`
- L23 _public enumerator_ `Mha`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace CaptureManager` (scope `UE`)
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkFaceControl, Log, All) class FLiveLinkFaceControl : public FRunnable { public: struct FRemoteSubject { enum class EAnimationType { ArKit, Mha }; FString Id; FString Name; EAnimationType AnimationType; uint16 AnimationVersion; TArray<FName> PropertyNames; FRemoteSubject(const FString& InId, const FString& InName, const EAnimationType InAnimationType, const uint16 InAnimationVersion, const TArray<FName>& InPropertyNames) : Id(InId) , Name(InName) , AnimationType(InAnimationType) , AnimationVersion(InAnimationVersion) , PropertyNames(InPropertyNames) {} }; using FRemoteSubjects = TArray<FRemoteSubject>; DECLARE_DELEGATE_RetVal_OneParam(const FRemoteSubject, FOnSelectRemoteSubject, const FRemoteSubjects&); DECLARE_DELEGATE_OneParam(FOnStreamingStarted, const FRemoteSubject&); FLiveLinkFaceControl(FGuid InSourceGuid, FString InControlHost, uint16 InControlPort, uint16 InStreamPort, FOnSelectRemoteSubject InOnSelectRemoteSubject, FOnStreamingStarted InOnStreamingStarted); ~FLiveLinkFaceControl(); void Start(); void RestartConnection();`
- L43 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(const FRemoteSubject, FOnSelectRemoteSubject, const FRemoteSubjects&);`
- L44 _delegate_ `DECLARE_DELEGATE_OneParam(FOnStreamingStarted, const FRemoteSubject&);`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSource/Private/LiveLinkFacePacket.h` (Private)


#### class `FLiveLinkFacePacket`  
`class FLiveLinkFacePacket`  
_L8-35_
- L11 _public member_ `static constexpr int32 HeadPoseValueCount = 6;`
- L13 _public prototype_ `bool Read(const FArrayReaderPtr& InPayloadPtr);`
- L15 _public prototype_ `uint16 GetVersion() const;`
- L16 _public prototype_ `FString GetSubjectId() const;`
- L17 _public prototype_ `FQualifiedFrameTime GetQualifiedFrameTime() const;`
- L18 _public prototype_ `const TArray<uint16>& GetControlValues() const;`
- L19 _public prototype_ `const TArray<float>& GetHeadPose() const;`
- L23 _private member_ `uint16 Version = 0;`
- L24 _private member_ `FString SubjectId;`
- L25 _private member_ `FQualifiedFrameTime QualifiedFrameTime;`
- L26 _private member_ `TArray<uint16> ControlValues;`
- L27 _private member_ `TArray<float> HeadPose;`
- L29 _private prototype_ `TArray<uint8> ReadData(FArrayReader& InArrayReader, const uint32 InLen);`
- L30 _private prototype_ `FString ReadString(FArrayReader& InArrayReader, const uint32 InLen);`
- L31 _private prototype_ `FName ReadName(FArrayReader& InArrayReader, const uint32 InLen);`
- L32 _private prototype_ `FQualifiedFrameTime ReadQualifiedFrameTime(FArrayReader& InArrayReader);`
- L33 _private prototype_ `void ReadControlValues(FArrayReader& InArrayReader, TArray<uint16>& OutControlValues);`
- L34 _private prototype_ `void ReadHeadPose(FArrayReader& InArrayReader, TArray<float>& OutHeadPose);`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSource/Private/LiveLinkFaceSource.h` (Private)


#### class `FLiveLinkFaceSource`  
`class FLiveLinkFaceSource : public ILiveLinkSource, public TSharedFromThis<FLiveLinkFaceSource>`  
_L20-106_
- inherits: `ILiveLinkSource,TSharedFromThis<FLiveLinkFaceSource>`
- L24 _public member_ `static FText SourceType;`
- L26 _public prototype_ `FLiveLinkFaceSource(const FString& InConnectionString);`
- L31 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;`
- L32 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L33 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L34 _public prototype_ `virtual FText GetSourceType() const override;`
- L35 _public prototype_ `virtual FText GetSourceMachineName() const override;`
- L36 _public prototype_ `virtual FText GetSourceStatus() const override;`
- L37 _public prototype_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const override;`
- L38 _public prototype_ `virtual void InitializeSettings(ULiveLinkSourceSettings* InSettings) override;`
- L42 _public prototype_ `void Connect(const ULiveLinkFaceSourceSettings* InSettings);`
- L44 _public prototype_ `void Stop();`
- L46 _public prototype_ `const FGuid& GetSourceGuid() const;`
- L57 _private member_ `FString CustomSubjectName;`
- L60 _private member_ `EStatus Status;` — The current status of the Live Link source
- L63 _private member_ `const FString ConnectionString;` — The connection string passed to the source on construction
- L66 _private member_ `TUniquePtr<FLiveLinkFaceControl> Control;` — The Control instance used to interact with a remote streaming device
- L69 _private member_ `const float ControlValueScalingFactor;` — The scaling factor to apply when converting uInt16 control values to float
- L72 _private member_ `ILiveLinkClient* LiveLinkClient = nullptr;` — The client used to push Live Link data to the editor
- L75 _private member_ `FGuid SourceGuid;` — The GUID of the Live Link Source
- L77 _private member_ `TSharedPtr<FLiveLinkFaceControl::FRemoteSubject> RemoteSubject;`
- L80 _private member_ `TUniquePtr<FSocket, FSocketDeleter> UdpSocket;` — The socket used for receiving multicast UDP packets
- L83 _private member_ `TUniquePtr<FUdpSocketReceiver> UdpReceiver;` — Manages the receipt of UDP packets
- L86 _private member_ `bool bSendAnalytics = false;` — Analytics info
- L87 _private member_ `double ProcessingStarted = 0;`
- L88 _private member_ `int32 NumAnimationFrames = 0;`
- L89 _private member_ `TMap<FString, FString> AnalyticsItems;`
- L90 _private member_ `FDelegateHandle AnalyticsShutdownHandler;`
- L91 _private prototype_ `void SendAnalytics();`
- L93 _private prototype_ `bool InitUdpReceiver();`
- L95 _private prototype_ `void OnDataReceived(const FArrayReaderPtr& InPayload, const FIPv4Endpoint& InEndpoint);`
- L96 _private prototype_ `const FLiveLinkFaceControl::FRemoteSubject OnSelectRemoteSubject(const FLiveLinkFaceControl::FRemoteSubjects& InRemoteSubjects);`
- L97 _private prototype_ `void OnStreamingStarted(const FLiveLinkFaceControl::FRemoteSubject& InRemoteSubject);`
- L99 _private prototype_ `void ProcessPacket(const FLiveLinkFacePacket &InPacket);`
- L100 _private prototype_ `void PopulatePropertyValues(const TArray<uint16>& InControlValues, TArray<float>& OutPropertyValues);`
- L102 _private prototype_ `TArray<FLiveLinkSubjectKey> GetSubjects() const;`
- L103 _private prototype_ `void SubjectAdded(FLiveLinkSubjectKey InSubjectKey);`
- L105 _private prototype_ `void PushStaticData(const FLiveLinkSubjectKey &InSubjectKey, const TArray<FName> InPropertyNames);`

#### enum `FLiveLinkFaceSource::EStatus`  
`enum EStatus`  
_L50-55_
- L52 _public enumerator_ `Disconnected = 0`
- L53 _public enumerator_ `Connecting = 1`
- L54 _public enumerator_ `Connected = 2`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkFaceSource, Log, All) class FLiveLinkFaceSource : public ILiveLinkSource, public TSharedFromThis<FLiveLinkFaceSource> { public: static FText SourceType; FLiveLinkFaceSource(const FString& InConnectionString); virtual ~FLiveLinkFaceSource() override;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSource/Private/LiveLinkFaceSourceFactory.h` (Private)


#### class `ULiveLinkFaceSourceFactory`  
`class ULiveLinkFaceSourceFactory : public ULiveLinkSourceFactory`  
_L12-25_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceFactory`
- L19 _public prototype_ `virtual FText GetSourceDisplayName() const override;`
- L20 _public prototype_ `virtual FText GetSourceTooltip() const override;`
- L21 _public function_ `virtual EMenuType GetMenuType() const override`
- L22 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& InConnectionString) const override;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkFaceSourceFactory, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkFaceSourceFactory, Log, All);`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSource/Private/LiveLinkFaceSourceModule.h` (Private)


#### class `FLiveLinkFaceSourceModule`  
`class FLiveLinkFaceSourceModule : public IModuleInterface`  
_L7-17_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void ShutdownModule() override;`
- L14 _public prototype_ `virtual void StartupModule() override;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSource/Private/LiveLinkFaceSubjectSettings.h` (Private)


#### class `ULiveLinkFaceSubjectSettings`  
`class ULiveLinkFaceSubjectSettings : public UMetaHumanLiveLinkSubjectSettings`  
_L10-33_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UMetaHumanLiveLinkSubjectSettings`
- L17 _public member_ `bool bHeadOrientation = true;` — `UPROPERTY(EditAnywhere, Category = "Controls", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))`
- L20 _public prototype_ `void SetHeadOrientation(bool HeadOrientation);` — `UFUNCTION(BlueprintCallable, Category = "Live Link Face")`
- L23 _public prototype_ `void GetHeadOrientation(bool& HeadOrientation) const;` — `UFUNCTION(BlueprintCallable, Category = "Live Link Face")`
- L26 _public member_ `bool bHeadTranslation = true;` — `UPROPERTY(EditAnywhere, Category = "Controls", meta = (EditCondition = "bIsLiveProcessing", HideEditConditionToggle, EditConditionHides))`
- L29 _public prototype_ `void SetHeadTranslation(bool HeadTranslation);` — `UFUNCTION(BlueprintCallable, Category = "Live Link Face")`
- L32 _public prototype_ `void GetHeadTranslation(bool& HeadTranslation) const;` — `UFUNCTION(BlueprintCallable, Category = "Live Link Face")`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSource/Public/LiveLinkFaceSourceBlueprint.h` (Public)


#### class `ULiveLinkFaceSourceBlueprint`  
`class ULiveLinkFaceSourceBlueprint : public UBlueprintFunctionLibrary`  
_L13-25_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UBlueprintFunctionLibrary`
- L21 _public prototype_ `static void CreateLiveLinkFaceSource(FLiveLinkSourceHandle& LiveLinkFaceSource, bool& Succeeded);` — `UFUNCTION(BlueprintCallable, Category = "Live Link Face")`
- L24 _public prototype_ `static void Connect(const FLiveLinkSourceHandle& LiveLinkFaceSource, const FString& SubjectName, const FString& Address, bool& Succeeded, int32 Port = 14785);` — `UFUNCTION(BlueprintCallable, Category = "Live Link Face")`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSource/Public/LiveLinkFaceSourceDefaults.h` (Public)


#### class `ULiveLinkFaceSourceDefaults`  
`class ULiveLinkFaceSourceDefaults : public UObject`  
_L12-23_
- reflection: `UCLASS(config = Editor, defaultconfig)`
- inherits: `UObject`
- L19 _public member_ `bool bHeadOrientation = true;` — `UPROPERTY(config, EditAnywhere, Category = "Subject")`
- L22 _public member_ `bool bHeadTranslation = true;` — `UPROPERTY(config, EditAnywhere, Category = "Subject")`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceSource/Public/LiveLinkFaceSourceSettings.h` (Public)


#### class `ULiveLinkFaceSourceSettings`  
`class ULiveLinkFaceSourceSettings : public ULiveLinkSourceSettings`  
_L13-57_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceSettings`
- L20 _public prototype_ `void Init(FLiveLinkFaceSource* InSource, const FString& InConnectionString);` — Initialize the source settings with the owning source and a connection string in the format 'ADDRESS:PORT'
- L23 _public prototype_ `void SetAddress(const FString& InAddress);` — Update the stored address value
- L26 _public prototype_ `void SetPort(const uint16 InPort);` — Update the stored port value
- L29 _public prototype_ `void SetSubjectName(const FString& InSubjectName);` — Update the stored subject name value
- L32 _public prototype_ `bool RequestConnect();` — Request the owning Live Link source to connect to the server
- L35 _public prototype_ `bool IsAddressValid() const;` — Check whether the stored address is valid
- L38 _public prototype_ `const FString& GetAddress() const;` — Get the stored address value
- L41 _public prototype_ `const uint16 GetPort() const;` — Get the stored port value
- L44 _public prototype_ `const FString& GetSubjectName() const;` — Get the store subject name value
- L48 _private member_ `static const FString IPAddressRegex;`
- L50 _private member_ `FLiveLinkFaceSource* Source = nullptr;`
- L51 _private member_ `FString Address;`
- L52 _private member_ `uint16 Port = 14785;` — If you change this be sure to update the default port number in LiveLinkFaceSourceBlueprint.h
- L53 _private member_ `FString SubjectName;`
- L55 _private prototype_ `void UpdateConnectionString();`
