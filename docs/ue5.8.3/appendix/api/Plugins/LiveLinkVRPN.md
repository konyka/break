# Plugins / LiveLinkVRPN

- module root: `Plugins/VirtualProduction/LiveLinkVRPN/Source/LiveLinkVRPN`
- headers: 6; symbols: 79
- symbol kinds: class=5, delegate=2, enum=1, enumerator=4, function=9, member=31, prototype=25, struct=1, union=1
- PrivateDependencyModuleNames: CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: Core, LiveLinkInterface, Messaging, Networking, Sockets

### `Plugins/VirtualProduction/LiveLinkVRPN/Source/LiveLinkVRPN/Private/SLiveLinkVRPNSourceFactory.h` (Private)


#### class `SLiveLinkVRPNSourceFactory`  
`class SLiveLinkVRPNSourceFactory : public SCompoundWidget`  
_L19-39_
- inherits: `SCompoundWidget`
- L21 _private function_ `SLATE_BEGIN_ARGS(SLiveLinkVRPNSourceFactory)`
- L23 _private prototype_ `SLATE_EVENT(FOnLiveLinkVRPNConnectionSettingsAccepted, OnConnectionSettingsAccepted) SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L30 _private member_ `FLiveLinkVRPNConnectionSettings ConnectionSettings;`
- L33 _private member_ `TSharedPtr<FStructOnScope> StructOnScope;`
- L34 _private member_ `TSharedPtr<IStructureDetailsView> StructureDetailsView;`
- L37 _private prototype_ `FReply OnSettingsAccepted();`
- L38 _private member_ `FOnLiveLinkVRPNConnectionSettingsAccepted OnConnectionSettingsAccepted;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnLiveLinkVRPNConnectionSettingsAccepted, FLiveLinkVRPNConnectionSettings);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnLiveLinkVRPNConnectionSettingsAccepted, FLiveLinkVRPNConnectionSettings);`

### `Plugins/VirtualProduction/LiveLinkVRPN/Source/LiveLinkVRPN/Public/LiveLinkVRPN.h` (Public)


#### class `FLiveLinkVRPNModule`  
`class FLiveLinkVRPNModule : public IModuleInterface`  
_L10-22_
- inherits: `IModuleInterface`
- L14 _public function_ `static FLiveLinkVRPNModule& Get()`
- L20 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L21 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkVRPN, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkVRPN, Log, All);`

### `Plugins/VirtualProduction/LiveLinkVRPN/Source/LiveLinkVRPN/Public/LiveLinkVRPNConnectionSettings.h` (Public)


#### enum `EVRPNDeviceType`  
`enum class EVRPNDeviceType : uint8`  
_L9-15_
- reflection: `UENUM(BlueprintType)`
- L11 _public enumerator_ `Analog`
- L12 _public enumerator_ `Dial`
- L13 _public enumerator_ `Button`
- L14 _public enumerator_ `Tracker`

#### struct `FLiveLinkVRPNConnectionSettings`  
`struct FLiveLinkVRPNConnectionSettings`  
_L18-41_
- reflection: `USTRUCT()`
- L24 _public member_ `FString IPAddress = TEXT("127` — `UPROPERTY(EditAnywhere, Category = "Connection Settings")` — IP address of the VRPN server
- L28 _public member_ `uint32 LocalUpdateRateInHz = 120;` — `UPROPERTY(EditAnywhere, Category = "Connection Settings", meta = (ClampMin = 1, ClampMax = 1000))` — Maximum rate (in Hz) at which to ask the VRPN server to update
- L32 _public member_ `FString DeviceName = TEXT("Mou` — `UPROPERTY(EditAnywhere, Category = "Connection Settings")` — VRPN device name
- L36 _public member_ `FString SubjectName = TEXT("Mou` — `UPROPERTY(EditAnywhere, Category = "Connection Settings")` — LiveLink subject name
- L40 _public member_ `EVRPNDeviceType Type = EVRPNDeviceType::Analog;` — `UPROPERTY(EditAnywhere, Category = "Connection Settings")` — Device type

### `Plugins/VirtualProduction/LiveLinkVRPN/Source/LiveLinkVRPN/Public/LiveLinkVRPNSource.h` (Public)


#### union `VRPNDeviceUnion`  
`union VRPNDeviceUnion`  
_L33-40_
- L35 _public member_ `vrpn_Analog_Remote* Analog;`
- L36 _public member_ `vrpn_Dial_Remote* Dial;`
- L37 _public member_ `vrpn_Button_Remote* Button;`
- L38 _public member_ `vrpn_Tracker_Remote* Tracker;`
- L39 _public member_ `void* RawPointer;`

#### class `FLiveLinkVRPNSource`  
`class FLiveLinkVRPNSource : public ILiveLinkSource, public FRunnable, public TSharedFromThis<FLiveLinkVRPNSource>`  
_L42-127_
- inherits: `ILiveLinkSource,FRunnable,TSharedFromThis<FLiveLinkVRPNSource>`
- L46 _public prototype_ `FLiveLinkVRPNSource(const FLiveLinkVRPNConnectionSettings& ConnectionSettings);`
- L48 _public prototype_ `virtual ~FLiveLinkVRPNSource();`
- L52 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;`
- L54 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L56 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L58 _public function_ `virtual FText GetSourceType() const override`
- L59 _public function_ `virtual FText GetSourceMachineName() const override`
- L60 _public function_ `virtual FText GetSourceStatus() const override`
- L62 _public function_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const override`
- L68 _public function_ `virtual bool Init() override`
- L69 _public prototype_ `virtual uint32 Run() override;`
- L70 _public prototype_ `void Start();`
- L71 _public prototype_ `virtual void Stop() override;`
- L72 _public function_ `virtual void Exit() override`
- L77 _private prototype_ `const FString& DeviceTypeToString(const EVRPNDeviceType InDeviceType);`
- L79 _private prototype_ `void Send(FLiveLinkFrameDataStruct* FrameDataToSend, const int32 NumProperties);`
- L82 _private member_ `ILiveLinkClient* Client;`
- L85 _private member_ `FGuid SourceGuid;` — Our identifier in LiveLink
- L87 _private member_ `FMessageAddress ConnectionAddress;`
- L89 _private member_ `FText SourceType;`
- L90 _private member_ `FText SourceMachineName;`
- L91 _private member_ `FText SourceStatus;`
- L94 _private member_ `FThreadSafeBool Stopping;` — Threadsafe Bool for terminating the main thread loop
- L97 _private member_ `FRunnableThread* Thread;` — Thread to run updates on
- L100 _private member_ `FString ThreadName;` — Name of the updates thread
- L103 _private member_ `TSet<FName> EncounteredSubjects;` — List of subjects we've already encountered
- L106 _private member_ `FDelegateHandle DeferredStartDelegateHandle;` — Deferred start delegate handle
- L109 _private member_ `FString IPAddress = TEXT("127` — IP address of the VRPN server
- L112 _private member_ `uint32 LocalUpdateRateInHz = 120;` — Maximum rate at which to refresh the server
- L115 _private member_ `EVRPNDeviceType DeviceType;` — VRPN device parameters
- L116 _private member_ `FString DeviceName;`
- L117 _private member_ `FName SubjectName;`
- L120 _private member_ `VRPNDeviceUnion VRPNDevice;` — Actual VRPN device
- L123 _private prototype_ `static void VRPN_CALLBACK OnAnalogChange(void* UserData, vrpn_ANALOGCB const AnalogData);` — Callbacks for VRPN change handlers
- L124 _private prototype_ `static void VRPN_CALLBACK OnDialChange(void* UserData, vrpn_DIALCB const DialData);`
- L125 _private prototype_ `static void VRPN_CALLBACK OnButtonChange(void* UserData, vrpn_BUTTONCB const ButtonData);`
- L126 _private prototype_ `static void VRPN_CALLBACK OnTrackerChange(void* UserData, vrpn_TRACKERCB const TrackerData);`

### `Plugins/VirtualProduction/LiveLinkVRPN/Source/LiveLinkVRPN/Public/LiveLinkVRPNSourceFactory.h` (Public)


#### class `ULiveLinkVRPNSourceFactory`  
`class ULiveLinkVRPNSourceFactory : public ULiveLinkSourceFactory`  
_L10-24_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceFactory`
- L15 _public prototype_ `virtual FText GetSourceDisplayName() const override;`
- L16 _public prototype_ `virtual FText GetSourceTooltip() const override;`
- L18 _public function_ `virtual EMenuType GetMenuType() const override`
- L19 _public prototype_ `virtual TSharedPtr<SWidget> BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const override;`
- L20 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const override;`
- L23 _private prototype_ `void CreateSourceFromSettings(FLiveLinkVRPNConnectionSettings ConnectionSettings, FOnLiveLinkSourceCreated OnSourceCreated) const;`

### `Plugins/VirtualProduction/LiveLinkVRPN/Source/LiveLinkVRPN/Public/LiveLinkVRPNSourceSettings.h` (Public)


#### class `ULiveLinkVRPNSourceSettings`  
`class ULiveLinkVRPNSourceSettings : public ULiveLinkSourceSettings`  
_L10-13_
- reflection: `UCLASS()`
- inherits: `ULiveLinkSourceSettings`
