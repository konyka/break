# Plugins / DisplayClusterMonitorEditor

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor`
- headers: 14; symbols: 424
- symbol kinds: class=14, delegate=11, enum=3, enumerator=18, function=49, member=97, namespace=6, prototype=220, struct=2, typedef=4
- PrivateDependencyModuleNames: Core, CoreUObject, DisplayClusterMedia, DisplayClusterMonitor, EditorStyle, EditorWidgets, InputCore, LevelEditor, Media, MediaAssets, MediaPlayerEditor, NDIMedia, OutputLog, Projects, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor/Private/Core/ClusterMonitorController.h` (Private)


#### class `FClusterMonitorController`  
`class FClusterMonitorController : public IClusterMonitorController , public TSharedFromThis<FClusterMonitorController>`  
_L25-199_
- inherits: `IClusterMonitorController,TSharedFromThis<FClusterMonitorController>`
- desc: Cluster monitor controller implementation Responsible for acquiring data from outside (observables), and propagate it among internal consumers (e.g. GUI panels). It also provides the API for obsrvation session management.
- L29 _private typedef_ `using FDCMessenger = UE::nDisplay::Monitor::FDCMessenger;`
- L33 _public prototype_ `FClusterMonitorController();`
- L34 _public prototype_ `virtual ~FClusterMonitorController() override = default;`
- L41 _public function_ `virtual TSharedRef<UE::nDisplay::Monitor::FDCMessenger> GetMessenger() override`
- L46 _public prototype_ `virtual bool StartCommunication() override;`
- L47 _public prototype_ `virtual void StopCommunication() override;`
- L51 _public prototype_ `virtual TSharedPtr<IClusterObservable> GetObservable(const FGuid& InObservableGuid) const override;`
- L52 _public prototype_ `virtual TSharedPtr<IClusterResidence> GetResidence(const FGuid& InObservableGuid) const override;`
- L54 _public prototype_ `virtual int32 GetObservablesNum() const override;`
- L55 _public prototype_ `virtual int32 GetActiveSessionsNum() const override;`
- L56 _public prototype_ `virtual int32 GetUnresponsiveNodesNum() const override;`
- L60 _public prototype_ `virtual void Rescan() override;`
- L61 _public prototype_ `virtual void ClearUnresponsiveEndpoints() override;`
- L63 _public prototype_ `virtual void RequestSessionStart(const FGuid& InObservableGuid) override;`
- L64 _public prototype_ `virtual void RequestSessionStop(const FGuid& InObservableGuid) override;`
- L65 _public prototype_ `virtual void RequestAllSessionsStop() override;`
- L69 _public function_ `virtual FObservableJoinedEvent& OnObservableJoined() override`
- L74 _public function_ `virtual FObservableUpdatedEvent& OnObservableUpdated() override`
- L79 _public function_ `virtual FObservableLeftEvent& OnObservableLeft() override`
- L84 _public function_ `virtual FObservableTimeoutEvent& OnObservableTimeout() override`
- L91 _public function_ `virtual FSessionStartRequestedEvent& OnSessionStartRequested() override`
- L96 _public function_ `virtual FSessionStopRequestedEvent& OnSessionStopRequested() override`
- L101 _public function_ `virtual FSessionStartedEvent& OnSessionStarted() override`
- L106 _public function_ `virtual FSessionStoppedEvent& OnSessionStopped() override`
- L116 _private prototype_ `TSharedRef<IClusterResidence> FindOrCreateNodeResidence(const FDCMData_ResidenceDescriptor& InResidence);` — Finds existing, or creates a new residence entity for local tracking based on the residence descriptor
- L119 _private prototype_ `void RemoveNodeResidence(const FDCMData_ResidenceDescriptor& InResidence);` — Remove specified residence
- L122 _private prototype_ `TSharedRef<IClusterObservable> CreateObservable(const FDCMData_ResidenceDescriptor& InResidence, const FDCMData_ObservableInfo& InObservableInfo);` — Creates new observable entity with the residence descriptor
- L125 _private prototype_ `TSharedRef<IClusterObservable> CreateObservable(const TSharedRef<IClusterResidence>& InResidence, const FDCMData_ObservableInfo& InObservableInfo);` — Creates new observable entity with an existing residence entity
- L128 _private prototype_ `void RemoveObservable(const FGuid& ObservableId);` — Removes specified observable from internal data
- L131 _private prototype_ `void UpdateObsrevable(const FDCMData_ResidenceDescriptor& InResidence, const FDCMData_ObservableInfo& InObservableInfo);` — Updates the requested observable entity from the original source
- L134 _private prototype_ `void CheckObservable(const FDCMData_ResidenceDescriptor& InResidence, const FDCMData_ObservableInfo& InObservableInfo);` — Checks if an observable entity exists for a given source data. If not, creates it.
- L139 _private prototype_ `void OnEndpointJoined(const FDCEndpoint& InEndpoint);` — Handles notification that a new endpoint was discovered
- L142 _private prototype_ `void OnEndpointLeft(const FDCEndpoint& InEndpoint, const FString& InReason);` — Handles notification that an endpoint was shut down
- L145 _private prototype_ `void OnEndpointTimeout(const FDCEndpoint& InEndpoint);` — Handles notification that specified endpoint is now considered unresponsive (timeout)
- L150 _private prototype_ `void HandleObservablesInfo(const FDCEndpoint& InEndpoint, const FDCMData_NodeObservables& InNodeObservables);` — Processes observable information that we get from various providers
- L153 _private prototype_ `void OnObservablesInfoResponse(const FDCEndpoint& InEndpoint, const FDCMMessage_NodeObservablesResponse& InResponseMsg);` — Handles responses to requests for node observables info
- L156 _private prototype_ `void OnObservablesInfoNotification(const FDCEndpoint& InEndpoint, const FDCMMessage_NodeObservablesNotification& InResponseMsg);` — Handles notifications about changes in node observables
- L161 _private member_ `TSet<FGuid> Clusters;` — Discovered cluster GUIDs
- L164 _private member_ `TMap<FGuid, TSharedRef<IClusterResidence>> Residences;` — Discovered cluster node GUIDs(residences)
- L167 _private member_ `TMap<FGuid, TSharedRef<IClusterObservable>> Observables;` — Discovered observable entities
- L170 _private member_ `TMap<FGuid, TSharedRef<IClusterObservable>> UnresponsiveObservables;` — Observable entities that are considered unresponsive
- L173 _private member_ `TMap<FGuid, TSharedRef<IClusterObservable>> ActiveSessions;` — Observable entities that have active seessions
- L176 _private member_ `TSharedRef<FDCMessenger> Messenger;` — MessageBus messenger
- L181 _private member_ `FObservableJoinedEvent ObservableJoinedEvent;` — Observable event: New observable has been discovered
- L183 _private member_ `FObservableUpdatedEvent ObservableUpdatedEvent;` — Observable event: An observable has been updated
- L185 _private member_ `FObservableLeftEvent ObservableLeftEvent;` — Observable event: An observable has left
- L187 _private member_ `FObservableTimeoutEvent ObservableTimeoutEvent;` — Observable event: An observable is considered unresponsive
- L192 _private member_ `FSessionStartRequestedEvent SessionStartRequestedEvent;` — Session event: New session start requested
- L194 _private member_ `FSessionStartedEvent SessionStartedEvent;` — Session event: Session started
- L196 _private member_ `FSessionStopRequestedEvent SessionStopRequestedEvent;` — Session event: Session stop requested
- L198 _private member_ `FSessionStoppedEvent SessionStoppedEvent;` — Session event: Session stopped

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace nDisplay` (scope `UE`)
- L12 _namespace_ `namespace Monitor` (scope `UE::nDisplay`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor/Private/Core/ClusterObservable.h` (Private)


#### class `FClusterObservable`  
`class FClusterObservable : public IClusterObservable , public FGCObject , public TSharedFromThis<FClusterObservable>`  
_L22-216_
- inherits: `IClusterObservable,FGCObject,TSharedFromThis<FClusterObservable>`
- desc: Monitor side observable implementation
- L29 _public prototype_ `FClusterObservable(const TSharedRef<IClusterResidence>& InResidence, const FDCMData_ObservableInfo& InObservableInfo, TWeakPtr<IClusterMonitorController> InController);`
- L35 _public prototype_ `static const FSlateBrush* GetDefaultIcon(EDCObservableType InObservableType);` — Returns default icon for the specified observable type
- L41 _public function_ `virtual TSharedRef<IClusterResidence> GetResidence() const override`
- L46 _public function_ `virtual FGuid GetId() const override`
- L51 _public function_ `virtual FString GetName() const override`
- L56 _public function_ `virtual EDCObservableType GetType() const override`
- L61 _public function_ `virtual const FSlateBrush* GetDisplayIcon() const override`
- L66 _public function_ `virtual FIntPoint GetResolution() const override`
- L73 _public function_ `virtual bool IsTile() const override`
- L78 _public function_ `virtual TOptional<FString> GetParentName() const override`
- L83 _public function_ `virtual TOptional<FIntPoint> GetTilePos() const override`
- L90 _public function_ `virtual ESessionState GetSessionState() const override`
- L95 _public prototype_ `virtual bool HasAnyUpdates(const FDCMData_ObservableInfo& InObservableInfo) const override;`
- L96 _public prototype_ `virtual void Update(const FDCMData_ObservableInfo& InObservableInfo) override;`
- L100 _public prototype_ `virtual bool IsSessionRunning() const override;`
- L101 _public prototype_ `virtual void StartSession() override;`
- L102 _public prototype_ `virtual void StopSession() override;`
- L106 _public prototype_ `virtual void Play() override;`
- L107 _public prototype_ `virtual void Pause() override;`
- L108 _public prototype_ `virtual void Stop() override;`
- L112 _public function_ `virtual UNDIMediaSource* GetMediaSource() const override`
- L117 _public function_ `virtual UMediaTexture* GetMediaTexture() const override`
- L122 _public function_ `virtual UMediaPlayer* GetMediaPlayer() const override`
- L129 _public function_ `virtual FSessionStateChangedEvent& OnSessionStateChanged() override`
- L134 _public function_ `virtual FObservableUpdatedEvent& OnObservableUpdated() override`
- L144 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L145 _public function_ `virtual FString GetReferencerName() const override`
- L154 _private prototype_ `void SetSessionState(ESessionState InNewState);` — Set new session state
- L157 _private prototype_ `void ConfigureMediaSource(const FString& InObservableName);` — Configures the media source based on the specified name
- L162 _private prototype_ `void OnMediaEvent(EMediaEvent MediaEvent);` — Handles state events from the media player
- L165 _private prototype_ `void OnStartSessionResponse(const FDCEndpoint& InEndpoint, const FDCMMessage_StartSessionResponse& InMessage);` — Handles StartSession responses
- L168 _private prototype_ `void OnObservableControlResponse(const FDCEndpoint& InEndpoint, const FDCMMessage_ObservableControlResponse& InMessage);` — Handles control (play, pause, stop) responses
- L173 _private member_ `TWeakPtr<IClusterMonitorController> Controller;` — Cluster controller
- L176 _private member_ `TSharedRef<IClusterResidence> Residence;` — The entity of a residence that owns this observable
- L179 _private member_ `FGuid Id;` — Observable GUID
- L182 _private member_ `FString Name;` — Observable name
- L185 _private member_ `EDCObservableType Type = EDCObservableType::None;` — Observable type
- L188 _private member_ `FIntPoint Resolution = FIntPoint::ZeroValue;` — Observable texture size
- L191 _private member_ `TOptional<FString> ParentName;` — Parent name if any (tiles only)
- L193 _private member_ `TOptional<FIntPoint> TilePos;` — Tile position (tiles only)
- L196 _private member_ `ESessionState SessionState = ESessionState::None;` — Current session state
- L201 _private member_ `TObjectPtr<UNDIMediaSource> MediaSource;` — Session media source (where to get media from)
- L204 _private member_ `TObjectPtr<UMediaTexture> MediaTexture;` — Session media texture (weher to render media to)
- L207 _private member_ `TObjectPtr<UMediaPlayer> MediaPlayer;` — Session media player (who will be doing all that
- L212 _private member_ `FSessionStateChangedEvent SessionStateChangedEvent;` — Fired every time when this observation session changes its state
- L215 _private member_ `FObservableUpdatedEvent ObservableUpdatedEvent;` — Fired every time when this observate gets updated (e.g. on the provider side)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor/Private/Core/ClusterResidence.h` (Private)


#### class `FClusterResidence`  
`class FClusterResidence : public IClusterResidence`  
_L14-98_
- inherits: `IClusterResidence`
- desc: Cluster residence implementation
- L19 _public prototype_ `FClusterResidence(const FDCMData_ResidenceDescriptor& InResidence);`
- L20 _public prototype_ `virtual ~FClusterResidence() override = default;`
- L26 _public function_ `virtual FGuid GetClusterId() const override`
- L31 _public function_ `virtual FString GetClusterName() const override`
- L36 _public function_ `virtual FGuid GetNodeId() const override`
- L41 _public function_ `virtual FString GetNodeName() const override`
- L46 _public function_ `virtual FString GetHostname() const override`
- L51 _public function_ `virtual bool IsNodeOffscreen() const override`
- L56 _public function_ `virtual int32 GetActiveObservablesNum() const override`
- L61 _public function_ `virtual EConnectionState GetConnectionState() const override`
- L66 _public function_ `virtual void SetConnectionState(EConnectionState InNewState) override`
- L76 _private member_ `FGuid ClusterId;` — Cluster GUID
- L78 _private member_ `FString ClusterName;` — Cluster name
- L81 _private member_ `FGuid NodeId;` — Cluster node GUID
- L83 _private member_ `FString NodeName;` — Cluster node name
- L86 _private member_ `FString Hostname;` — Machine name of this residence
- L89 _private member_ `bool bIsPrimary = false;` — Whether it's primary node
- L91 _private member_ `bool bIsOffscreen = false;` — Whether it's running offscreen
- L94 _private member_ `int32 ActiveObservablesNum = 0;` — The number of active observables
- L97 _private member_ `EConnectionState ConnectionState = EConnectionState::Offline;` — Current connection state

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor/Private/Core/IClusterMonitorController.h` (Private)


#### class `IClusterMonitorController`  
`class IClusterMonitorController`  
_L21-108_
- desc: Cluster monitor controller interface
- L25 _public prototype_ `virtual ~IClusterMonitorController() = default;`
- L30 _public prototype_ `virtual TSharedRef<UE::nDisplay::Monitor::FDCMessenger> GetMessenger() = 0;` — Returns MessageBus messenger
- L33 _public prototype_ `virtual bool StartCommunication() = 0;` — Appear online for other cluster monitor messengers. Start discovery and messaging.
- L36 _public prototype_ `virtual void StopCommunication() = 0;` — Go offline. Stop discovery and messaging.
- L42 _public prototype_ `virtual TSharedPtr<IClusterObservable> GetObservable(const FGuid& Guid) const = 0;` — Returns observable entity with the specified GUID. If requested observable has not been discovered yet, or went offline, return nullptr.
- L45 _public prototype_ `virtual TSharedPtr<IClusterResidence> GetResidence(const FGuid& ObservableGuid) const = 0;` — Returns residence entity of an observable with the specified GUID
- L48 _public prototype_ `virtual int32 GetObservablesNum() const = 0;` — Returns the number of observable entities that have been discovered
- L51 _public prototype_ `virtual int32 GetActiveSessionsNum() const = 0;` — Returns the number of active observation sessions
- L54 _public prototype_ `virtual int32 GetUnresponsiveNodesNum() const = 0;` — Returns the number of unresponsive residences (cluster nodes)
- L57 _public prototype_ `virtual void Rescan() = 0;` — Re-discovers the cluster monitoring network from scratch
- L60 _public prototype_ `virtual void ClearUnresponsiveEndpoints() = 0;` — Forgets about all unresponsive nodes. Those won't be available anymore.
- L65 _public prototype_ `virtual void RequestSessionStart(const FGuid& Observable) = 0;` — Requests observation session start for an observable entity with the specified GUID
- L68 _public prototype_ `virtual void RequestSessionStop(const FGuid& Observable) = 0;` — Requests observation session stop for an observable entity with the specified GUID
- L71 _public prototype_ `virtual void RequestAllSessionsStop() = 0;` — Requests to stop all active observation sessions
- L76 _public prototype_ `DECLARE_EVENT_OneParam(IClusterMonitorController, FObservableJoinedEvent, const TSharedRef<IClusterObservable>& );` — Fired when new observable is discovered
- L77 _public prototype_ `virtual FObservableJoinedEvent& OnObservableJoined() = 0;`
- L80 _public prototype_ `DECLARE_EVENT_OneParam(IClusterMonitorController, FObservableUpdatedEvent, const TSharedRef<IClusterObservable>& );` — Fired when a known observable has been updated
- L81 _public prototype_ `virtual FObservableUpdatedEvent& OnObservableUpdated() = 0;`
- L84 _public prototype_ `DECLARE_EVENT_TwoParams(IClusterMonitorController, FObservableLeftEvent, const TSharedRef<IClusterObservable>& , const FString& );` — Fired when a known observable goes offline (intentional shutdown)
- L85 _public prototype_ `virtual FObservableLeftEvent& OnObservableLeft() = 0;`
- L88 _public prototype_ `DECLARE_EVENT_OneParam(IClusterMonitorController, FObservableTimeoutEvent, const TSharedRef<IClusterObservable>& );` — Fired when a known observable is considered unresponsive
- L89 _public prototype_ `virtual FObservableTimeoutEvent& OnObservableTimeout() = 0;`
- L94 _public prototype_ `DECLARE_EVENT_OneParam(IClusterMonitorController, FSessionStartRequestedEvent, const TSharedRef<IClusterObservable>& );` — Fired when new observation session is requested to start
- L95 _public prototype_ `virtual FSessionStartRequestedEvent& OnSessionStartRequested() = 0;`
- L98 _public prototype_ `DECLARE_EVENT_OneParam(IClusterMonitorController, FSessionStopRequestedEvent, const TSharedRef<IClusterObservable>& );` — Fired when an observation session is requested to stop
- L99 _public prototype_ `virtual FSessionStopRequestedEvent& OnSessionStopRequested() = 0;`
- L102 _public prototype_ `DECLARE_EVENT_OneParam(IClusterMonitorController, FSessionStartedEvent, const TSharedRef<IClusterObservable>& );` — Fired when an observation session starts
- L103 _public prototype_ `virtual FSessionStartedEvent& OnSessionStarted() = 0;`
- L106 _public prototype_ `DECLARE_EVENT_OneParam(IClusterMonitorController, FSessionStoppedEvent, const TSharedRef<IClusterObservable>& );` — Fired when an observation session stops
- L107 _public prototype_ `virtual FSessionStoppedEvent& OnSessionStopped() = 0;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace nDisplay` (scope `UE`)
- L12 _namespace_ `namespace Monitor` (scope `UE::nDisplay`)
- L76 _delegate_ `DECLARE_EVENT_OneParam(IClusterMonitorController, FObservableJoinedEvent, const TSharedRef<IClusterObservable>& );` — Fired when new observable is discovered
- L80 _delegate_ `DECLARE_EVENT_OneParam(IClusterMonitorController, FObservableUpdatedEvent, const TSharedRef<IClusterObservable>& );` — Fired when a known observable has been updated
- L84 _delegate_ `DECLARE_EVENT_TwoParams(IClusterMonitorController, FObservableLeftEvent, const TSharedRef<IClusterObservable>& , const FString& );` — Fired when a known observable goes offline (intentional shutdown)
- L88 _delegate_ `DECLARE_EVENT_OneParam(IClusterMonitorController, FObservableTimeoutEvent, const TSharedRef<IClusterObservable>& );` — Fired when a known observable is considered unresponsive
- L94 _delegate_ `DECLARE_EVENT_OneParam(IClusterMonitorController, FSessionStartRequestedEvent, const TSharedRef<IClusterObservable>& );` — Fired when new observation session is requested to start
- L98 _delegate_ `DECLARE_EVENT_OneParam(IClusterMonitorController, FSessionStopRequestedEvent, const TSharedRef<IClusterObservable>& );` — Fired when an observation session is requested to stop
- L102 _delegate_ `DECLARE_EVENT_OneParam(IClusterMonitorController, FSessionStartedEvent, const TSharedRef<IClusterObservable>& );` — Fired when an observation session starts
- L106 _delegate_ `DECLARE_EVENT_OneParam(IClusterMonitorController, FSessionStoppedEvent, const TSharedRef<IClusterObservable>& );` — Fired when an observation session stops

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor/Private/Core/IClusterObservable.h` (Private)


#### class `IClusterObservable`  
`class IClusterObservable`  
_L22-126_
- desc: Monitor side observable interface Declares API of an observable entities on the cluster monitor side (data consumer part).
- L26 _public prototype_ `virtual ~IClusterObservable() = default;`
- L45 _public prototype_ `virtual TSharedRef<IClusterResidence> GetResidence() const = 0;` — Returns residence of the observable entity
- L48 _public prototype_ `virtual FGuid GetId() const = 0;` — Returns GUID of the observable entity
- L51 _public prototype_ `virtual FString GetName() const = 0;` — Returns display name of the observable entity
- L54 _public prototype_ `virtual EDCObservableType GetType() const = 0;` — Returns type of the observable entity
- L57 _public prototype_ `virtual const FSlateBrush* GetDisplayIcon() const = 0;` — Returns current observable icon
- L60 _public prototype_ `virtual FIntPoint GetResolution() const = 0;` — Returns resolution of the observable media stream
- L65 _public prototype_ `virtual bool IsTile() const = 0;` — Returns true if this observable entity is a tile
- L68 _public prototype_ `virtual TOptional<FString> GetParentName() const = 0;` — Returns name of the parent owner if this entity is a tile
- L71 _public prototype_ `virtual TOptional<FIntPoint> GetTilePos() const = 0;` — Returns tile position if it's a tile
- L76 _public prototype_ `virtual ESessionState GetSessionState() const = 0;` — Returns current observation session state
- L79 _public prototype_ `virtual bool HasAnyUpdates(const FDCMData_ObservableInfo& InObservableInfo) const = 0;` — Checks if there were any changes to the original source item
- L82 _public prototype_ `virtual void Update(const FDCMData_ObservableInfo& InObservableInfo) = 0;` — Update observable data from the source
- L87 _public prototype_ `virtual bool IsSessionRunning() const = 0;` — Returns true if this observable has started local session
- L90 _public prototype_ `virtual void StartSession() = 0;` — Start observation session for this observable entity
- L93 _public prototype_ `virtual void StopSession() = 0;` — Stop observation session
- L98 _public prototype_ `virtual void Play() = 0;` — Session control: Play command
- L101 _public prototype_ `virtual void Pause() = 0;` — Session control: Pause command
- L104 _public prototype_ `virtual void Stop() = 0;` — Session control: Stop command
- L109 _public prototype_ `virtual UNDIMediaSource* GetMediaSource() const = 0;` — Returns media source associated with this observable entity
- L112 _public prototype_ `virtual UMediaTexture* GetMediaTexture() const = 0;` — Returns media texture associated with this observable entity
- L115 _public prototype_ `virtual UMediaPlayer* GetMediaPlayer() const = 0;` — Returns media player associated with this observable entity
- L120 _public prototype_ `DECLARE_EVENT_OneParam(IClusterObservable, FSessionStateChangedEvent, ESessionState );` — Called when observation session changes its state
- L121 _public prototype_ `virtual FSessionStateChangedEvent& OnSessionStateChanged() = 0;`
- L124 _public prototype_ `DECLARE_EVENT(IClusterObservable, FObservableUpdatedEvent);` — Called when this observable entity gets updated from the original source
- L125 _public prototype_ `virtual FObservableUpdatedEvent& OnObservableUpdated() = 0;`

#### enum `IClusterObservable::ESessionState`  
`enum class ESessionState : uint8`  
_L33-40_
- desc: Observation session state
- L35 _public enumerator_ `None`
- L36 _public enumerator_ `Transition`
- L37 _public enumerator_ `Inactive`
- L38 _public enumerator_ `Active`
- L39 _public enumerator_ `Error`

#### Free symbols / members of external scopes

- L120 _delegate_ `DECLARE_EVENT_OneParam(IClusterObservable, FSessionStateChangedEvent, ESessionState );` — Called when observation session changes its state
- L124 _delegate_ `DECLARE_EVENT(IClusterObservable, FObservableUpdatedEvent);` — Called when this observable entity gets updated from the original source

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor/Private/Core/IClusterResidence.h` (Private)


#### class `IClusterResidence`  
`class IClusterResidence`  
_L16-62_
- desc: Residence interface Declares the API of residences (cluster nodes)
- L20 _public prototype_ `virtual ~IClusterResidence() = default;`
- L37 _public prototype_ `virtual FGuid GetClusterId() const = 0;` — Returns cluster GUID
- L40 _public prototype_ `virtual FString GetClusterName() const = 0;` — Returns cluster name
- L43 _public prototype_ `virtual FGuid GetNodeId() const = 0;` — Returns cluster node GUID
- L46 _public prototype_ `virtual FString GetNodeName() const = 0;` — Returns cluster node name
- L49 _public prototype_ `virtual FString GetHostname() const = 0;` — Returns the hostname of a machine where this cluster node is running on
- L52 _public prototype_ `virtual bool IsNodeOffscreen() const = 0;` — Returns true if this cluster node is runing offscreen
- L55 _public prototype_ `virtual int32 GetActiveObservablesNum() const = 0;` — Returns the number of observables on this cluster node
- L58 _public prototype_ `virtual EConnectionState GetConnectionState() const = 0;` — Returns current connection state of this cluster node
- L61 _public prototype_ `virtual void SetConnectionState(EConnectionState InNewState) = 0;` — Set new connection state

#### enum `IClusterResidence::EConnectionState`  
`enum class EConnectionState : uint8`  
_L27-32_
- desc: Residence connection states
- L29 _public enumerator_ `Online` — Connected
- L30 _public enumerator_ `Timeout` — Unresponsive
- L31 _public enumerator_ `Offline` — Disconnected

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor/Private/DCMonitorEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogClusterMonitorEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogClusterMonitorEditor, Log, All);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor/Private/DCMonitorEditorModule.h` (Private)


#### class `FDCMonitorEditorModule`  
`class FDCMonitorEditorModule : public IModuleInterface`  
_L12-41_
- inherits: `IModuleInterface`
- desc: DisplayClusterMonitorEditor module implementation
- L15 _private member_ `static const FLazyName NAME_ClusterMonitor_Container;` — Cluster monitor settings container
- L17 _private member_ `static const FLazyName NAME_ClusterMonitor_Category;` — Cluster monitor settings category
- L19 _private member_ `static const FLazyName NAME_ClusterMonitor_Section;` — Cluster monitor settings section
- L24 _public prototype_ `virtual void StartupModule() override;`
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L31 _private prototype_ `void RegisterSettings();` — Registers internal settings
- L34 _private prototype_ `void UnregisterSettings();` — Unregisters internal settings
- L37 _private prototype_ `void RegisterTabs();` — Registers internal UI tabs
- L40 _private prototype_ `void UnregisterTabs();` — Unregisters internal UI tabs

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor/Private/DCMonitorEditorStyle.h` (Private)


#### class `FDCMonitorEditorStyle`  
`class FDCMonitorEditorStyle : public FSlateStyleSet`  
_L11-30_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the cluster monitor UI.
- L16 _private prototype_ `FDCMonitorEditorStyle();` — Private singleton constructor
- L24 _public prototype_ `static FDCMonitorEditorStyle& Get();` — Access the singleton instance for this style set
- L29 _private prototype_ `void Initialize();` — Initializes internal data

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor/Private/Widgets/SClusterMonitorPanel.h` (Private)


#### class `SClusterMonitorPanel`  
`class SClusterMonitorPanel : public SCompoundWidget`  
_L20-126_
- inherits: `SCompoundWidget`
- desc: The main cluster monitor panel
- L22 _private typedef_ `using Super = SCompoundWidget;`
- L27 _public prototype_ `static void RegisterTabSpawner(TSharedRef<FWorkspaceItem> InWorkspaceItem);` — Registers this panel widget as a nomad tab
- L30 _public prototype_ `static void UnregisterTabSpawner();` — Unregisters this panel from the tab management sytem
- L33 _public prototype_ `static TSharedPtr<SClusterMonitorPanel> GetPanelInstance();` — Returns this panel instance (may be invalid if not currently spawned)
- L38 _private member_ `static TWeakPtr<SClusterMonitorPanel> PanelInstance;` — References the cluster monitor panel widget when its open
- L44 _private member_ `static FDelegateHandle LevelEditorTabManagerChangedHandle;` — Delegate responsible for processing the tab manager changes to keep this panel always properly registered
- L47 _private member_ `static const FLazyName NAME_ClusterMonitorTabId;` — Tab ID to use for registering this panel
- L50 _private member_ `static const FLazyName NAME_LevelEditorModuleName;` — LevelEditor module name (owns the tab manager)
- L55 _private prototype_ `static TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& Args);` — Factory method that instantiates this panel widget
- L59 _public function_ `SLATE_BEGIN_ARGS(SClusterMonitorPanel)`
- L61 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L67 _public prototype_ `virtual ~SClusterMonitorPanel();` — Widget destruction
- L72 _private prototype_ `TSharedRef<SWidget> CreateWidget_Toolbar();` — Entry point to build the toolbar widget
- L75 _private prototype_ `TSharedRef<SWidget> CreateWidget_Workspace();` — Entry point to build the main workspace widget
- L78 _private prototype_ `TSharedRef<SWidget> CreateWidget_Status();` — Entry point to build the status bar widget
- L83 _public prototype_ `void Rescan();` — Rescan clusters from scratch
- L86 _public prototype_ `void ClearUnresponsiveEntities();` — Clears all unresponsive entities
- L91 _private prototype_ `FReply OnClicked_ShowSettings();` — Handles 'show settings' button clicks
- L94 _private prototype_ `FReply OnClicked_Rescan();` — Handles 'rescan' button clicks
- L97 _private prototype_ `FReply OnClicked_StopAllSessions();` — Handles 'stop all sessions' button clicks
- L100 _private prototype_ `FReply OnClicked_ClearUnresponsiveEntities();` — Handles 'clear unresponsive entities' button clicks
- L103 _private prototype_ `bool OnOverrideHistory(const FName& InExecutorName, TArray<FString>& OutHistory);`
- L106 _private prototype_ `bool OnInterceptConsoleCommand(const FName& InExecutorName, const FString& InExecCommand);`
- L109 _private prototype_ `void PropagateConsoleCommand(const FString& ExecutorName, const FString& Command);`
- L114 _private member_ `TSharedPtr<IClusterMonitorController> Controller;` — A controller that provides cluster data, and manages internal processes
- L117 _private member_ `TSharedPtr<SClusterTreeView> ClusterTreeView;` — A tree based layout showing currently existing observables
- L120 _private member_ `TSharedPtr<SClusterSessionsView> ClusterSessionsView;` — A grid based layout showing active streams
- L123 _private member_ `TSharedPtr<SMultiLineEditableTextBox> ConsoleEditBox;` — Console commands widget
- L125 _private member_ `TMap<FName, TArray<FString>> CommandHistory;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor/Private/Widgets/SClusterSessionsView.h` (Private)


#### class `SClusterSessionsView`  
`class SClusterSessionsView : public SCompoundWidget`  
_L20-153_
- inherits: `SCompoundWidget`
- desc: Cluster Sessions View Represents all the observation sessions as separate widgets. Responsible for: - Creating and deleting of session viewports - Viewport view modes (maximized, immersive)
- L25 _public function_ `SLATE_BEGIN_ARGS(SClusterSessionsView)`
- L27 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<IClusterMonitorController>& InController);`
- L38 _public prototype_ `bool CanMaximizeViewport(const FGuid& InObservableId) const;` — Whether a viewport can be maximized now
- L41 _public prototype_ `void MaximizeViewport(const FGuid& InObservableId);` — Maximize viewport of a specified session
- L44 _public prototype_ `bool IsViewportMaximized(const FGuid& InObservableId) const;` — Whether a specified viewport is currently maximized
- L47 _public prototype_ `bool CanResetMaximized() const;` — Whether there is a maximized viewport, and we can get back to normal grid view
- L50 _public prototype_ `void ResetMaximized();` — Get back to normal grid view
- L55 _public prototype_ `void SetViewportImmersive(const FGuid& InObservableId);` — Switches specified viewport into immersive mode
- L58 _public prototype_ `bool IsViewportImmersive(const FGuid& InObservableId) const;` — Whether a specified viewport is in immersive mode
- L61 _public prototype_ `void ResetImmersive();` — Reset immersive mode
- L66 _private prototype_ `void UpdateDisplays();` — Generates UI layout for active sessions
- L69 _private prototype_ `TSharedRef<SWidget> ConstructViewportLayout();` — UI layout generation entry point
- L72 _private prototype_ `TSharedRef<SWidget> CreateWidget_NoViewportsAvailable();` — Generates UI when no active sessions (viewports) available
- L75 _private prototype_ `TSharedRef<SWidget> CreateWidget_ViewportGrid();` — Generates UI layout
- L78 _private prototype_ `TSharedRef<SWidget> CreateWidget_Viewport(const FGuid& InObservableId);` — Generates viewport widget
- L81 _private prototype_ `TSharedRef<SWidget> CreateWidget_Viewport(FViewportItem& InViewportItem);` — Generates viewport widget
- L86 _private function_ `bool HasViewport(const FGuid& Id) const` — Checks if a specified session viewport exists
- L95 _private function_ `FViewportItem* GetViewportItem(const FGuid& Id)` — Returns content item by observalbe GUID. Ohterwise nullptr.
- L106 _private prototype_ `void OnSessionStartRequested(const TSharedRef<IClusterObservable>& InObservable);` — Handles session start request notifications. Creates a corresponding viewport.
- L109 _private prototype_ `void OnSessionStopRequested(const TSharedRef<IClusterObservable>& InObservable);` — Handles session stop request notifications. Deletes a corresponding viewport.
- L112 _private prototype_ `void OnObservableLeft(const TSharedRef<IClusterObservable>& InObservable, const FString& InReason);` — Handles observable left notifications. Deletes a corresponding viewport.
- L117 _private prototype_ `void AddViewport(const TSharedRef<IClusterObservable>& InObservable);` — Creates viewport for a specified observable session
- L120 _private prototype_ `void RemoveViewport(const TSharedRef<IClusterObservable>& InObservable);` — Removes viewport of a specified observable session
- L125 _private member_ `TWeakPtr<IClusterMonitorController> Controller;` — Cluster monitor controller
- L128 _private member_ `TSharedPtr<SOverlay> LayoutContainer;` — The root widget of the viewport layout
- L146 _private member_ `TArray<FViewportItem> ViewportItems;` — Currently active observation sessions
- L149 _private member_ `FGuid MaximizedViewportId;` — Viewport that is currently maximized
- L152 _private member_ `FGuid ImmersiveViewportId;` — Viewport that is currently in immersive mode

#### struct `SClusterSessionsView::FViewportItem`  
`struct FViewportItem`  
_L133-143_
- desc: Internal content item. Keeps data associated with an observation session
- L136 _public member_ `FGuid Id;` — Observable GUID
- L139 _public member_ `TSharedPtr<IClusterObservable> Observable;` — Observable entity
- L142 _public member_ `TSharedPtr<SWidget> Widget;` — Session viewport widget

#### Free symbols / members of external scopes

- L89 _function_ `` (scope `SClusterSessionsView::HasViewport`)
- L98 _function_ `` (scope `SClusterSessionsView::GetViewportItem`)

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor/Private/Widgets/SClusterTreeView.h` (Private)


#### class `SClusterTreeView`  
`class SClusterTreeView : public SCompoundWidget`  
_L22-255_
- inherits: `SCompoundWidget`
- desc: A tree view that shows all available clusters and their observables. Also provides interface to manipulate the observation sessions.
- L146 _private typedef_ `using FTreeItemPtr = TSharedPtr<FTreeItem>;`
- L150 _public function_ `SLATE_BEGIN_ARGS(SClusterTreeView)`
- L152 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedPtr<IClusterMonitorController>& InController);`
- L163 _public prototype_ `void ExpandAll(bool bIncludingChildren = true);` — Expands all tree items
- L166 _public prototype_ `void CollapseAll(bool bIncludingChildren = true);` — Collapses all tree items
- L169 _public prototype_ `void SetExpansion(FTreeItemPtr InTreeItem, bool bExpanded, bool bIncludingChildren);` — Expand or collapse specific tree item
- L172 _public prototype_ `void SetExpansion(bool bExpanded, bool bIncludingChildren = true);` — Expands or collapses all tree items
- L177 _private prototype_ `TSharedRef<ITableRow> GenerateTreeItemRow(FTreeItemPtr InTreeItem, const TSharedRef<STableViewBase>& InOwnerTableView);` — Generates new row
- L180 _private prototype_ `FTreeItemPtr FindOrCreateClusterItem(const TSharedRef<IClusterObservable>& InObservable);` — Finds or creates a 1st level cluster item
- L183 _private prototype_ `FTreeItemPtr FindOrCreateNodeItem(const TSharedRef<IClusterObservable>& InObservable);` — Finds or creates a 2nd level cluster node item
- L186 _private prototype_ `FTreeItemPtr FindObservableItem(const TSharedRef<IClusterObservable>& InObservable);` — Returns a tree item for a specified observable
- L189 _private prototype_ `FTreeItemPtr CreateObservableItem(const TSharedRef<IClusterObservable>& InObservable);` — Creates a tree item for a specified observable
- L192 _private prototype_ `FTreeItemPtr FindOrCreateGroupItem(FTreeItemPtr NodeItem, EItemType InType, const FString& InName);` — Finds or creates a tile group tree item
- L197 _private prototype_ `void GetTreeItemChildren(FTreeItemPtr InTreeItem, TArray<FTreeItemPtr>& OutChildren) const;` — Reports all children that aren't filtered out currently
- L200 _private prototype_ `void TryStartObservationSession(FTreeItemPtr InTreeItem);` — Starts obsevation of a specified observable if not started yet
- L203 _private prototype_ `void RemoveEmptyItems();` — Removes empty tree items that aren't the leaves
- L208 _private prototype_ `void OnObservableJoined(const TSharedRef<IClusterObservable>& InObservable);` — Called when a new observable is discovered, and becomes available for observation.
- L211 _private prototype_ `void OnObservableUpdated(const TSharedRef<IClusterObservable>& InObservable);` — Called when the state of an observable has been updated
- L214 _private prototype_ `void OnObservableLeft(const TSharedRef<IClusterObservable>& InObservable, const FString& InReason);` — Called when an observable shuts down
- L217 _private prototype_ `void OnObservableTimeout(const TSharedRef<IClusterObservable>& InObservable);` — Called when an observable stops responding and is considered timed out
- L220 _private prototype_ `void OnSessionChanged(const TSharedRef<IClusterObservable>& InObservable);` — Called when the observation session state for an observable changes
- L223 _private prototype_ `void OnItemDoubleClicked(FTreeItemPtr InTreeItem);` — Handles LMB double clicks on tree items
- L229 _private prototype_ `void OnFilterChanged();` — Raised when the filter has changed in the toolbar, updates the tree view's source list to show only filtered items
- L234 _private member_ `TSharedPtr<SClusterTreeToolbar> Toolbar;` — Tree view toolbar that provides some additional tree manipulation tools (filters)
- L237 _private member_ `TArray<FTreeItemPtr> TreeItems;` — Cluster items displayed in the tree view
- L240 _private member_ `TSharedPtr<STreeView<FTreeItemPtr>> TreeView;` — Tree view based cluster outliner widget
- L243 _private member_ `TWeakPtr<IClusterMonitorController> Controller;` — A reference to the cluster monitor controller
- L248 _private member_ `static const FLazyName Column_ItemConnection;` — Column name: connection state
- L250 _private member_ `static const FLazyName Column_ItemName;` — Column name: item name
- L252 _private member_ `static const FLazyName Column_ItemInfo;` — Column name: item extra information
- L254 _private member_ `static const FLazyName Column_ItemStream;` — Column name: item session state

#### enum `SClusterTreeView::EItemType`  
`enum class EItemType : uint8`  
_L32-44_
- desc: Tree item types
- L34 _public enumerator_ `Unknown` — For validation
- L35 _public enumerator_ `Cluster` — Cluster root item
- L36 _public enumerator_ `Node` — Onscreen cluster node
- L37 _public enumerator_ `NodeOffscreen` — Offscreen cluster node
- L38 _public enumerator_ `ICVFXCameraTiled` — Non-observable group of tiles
- L39 _public enumerator_ `Obs_Backbuffer` — Backbuffer (observable)
- L40 _public enumerator_ `Obs_UI` — UI layer (observable)
- L41 _public enumerator_ `Obs_Viewport` — Viewport (observable)
- L42 _public enumerator_ `Obs_ICVFXCamera` — ICVFX camera (observable)
- L43 _public enumerator_ `Obs_ICVFXCameraTile` — ICVFX camera tile (observable)

#### struct `SClusterTreeView::FTreeItem`  
`struct FTreeItem : public TSharedFromThis<FTreeItem>`  
_L49-144_
- inherits: `TSharedFromThis<FTreeItem>`
- desc: Struct to store information for each element displayed in the tree view
- L54 _public function_ `static TSharedRef<FTreeItem> Create(const FGuid& InGuid)` — Factory method to create new tree items
- L65 _public function_ `static TSharedPtr<FTreeItem> Find(const FGuid& InGuid)` — Quick search for a tree item by GUID
- L74 _private function_ `FTreeItem(const FGuid& InGuid) : Id(InGuid)` — No direct instantiation
- L80 _public function_ `~FTreeItem()`
- L89 _public member_ `TSharedPtr<IClusterResidence> Residence;` — Item residence (optional)
- L92 _public member_ `TSharedPtr<IClusterObservable> Observable;` — Item observable (optional)
- L95 _public member_ `EItemType Type = EItemType::Unknown;` — Item type
- L98 _public member_ `FGuid Id;` — Item GUID
- L101 _public member_ `FString Name;` — Item name
- L104 _public member_ `FIntPoint Resolution = FIntPoint::ZeroValue;` — Item resolution (optional)
- L107 _public member_ `bool bFilteredOut = false;` — Whether this item is currently filtered out
- L110 _public member_ `TWeakPtr<FTreeItem> Parent;` — Parent item in the tree
- L113 _public member_ `TArray<TSharedPtr<FTreeItem>> Children;` — Child items
- L118 _public prototype_ `static EItemType GetTreeItemType(EDCObservableType InObservableType);` — Converts observable types into tree item types
- L121 _public prototype_ `static const FSlateBrush* GetTreeItemIcon(EItemType Type);` — Returns icon for a specific tree item type
- L126 _public prototype_ `bool IsLeaf() const;` — Returns true if this tree item is a leaf
- L129 _public prototype_ `bool IsClusterNode() const;` — Returns true if this item is a cluster node
- L132 _public prototype_ `void SortChildren();` — Sort children items
- L135 _public prototype_ `void Update();` — Updates local tree item data from the original observable item
- L138 _public prototype_ `TSharedPtr<FTreeItem> GetTopMostParent() const;` — Returns the top most parent tree item of this one
- L143 _private member_ `inline static TMap<FGuid, TWeakPtr<FTreeItem>> TreeItemGuids;` — Tree items map for quick access

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor/Private/Widgets/SObservableMediaImage.h` (Private)


#### class `SObservableMediaImage`  
`class SObservableMediaImage : public SMediaImage`  
_L21-135_
- inherits: `SMediaImage`
- desc: Observable Media Image Widget Extends SMediaImage with the following features: - Automatically manages horizontal and vertical scrollbars - Supports image panning - Supports image zooming
- L23 _private typedef_ `using Super = SMediaImage;`
- L27 _public function_ `SLATE_BEGIN_ARGS(SObservableMediaImage) : _ScrollBarThickness(FVector2D(8.f, 8.f))`
- L31 _public prototype_ `SLATE_ARGUMENT(FVector2D, ScrollBarThickness) SLATE_ARGUMENT(float, ZoomStep) SLATE_ARGUMENT(float, ZoomMin) SLATE_ARGUMENT(float, ZoomMax) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<IClusterObservable> InObservable);` — Thickness of the scrollbar handles
- L52 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L53 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L54 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L55 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L56 _public prototype_ `virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L62 _public prototype_ `float GetCurrentZoom() const;` — Returns current scale multiplier
- L65 _public prototype_ `void ZoomToFit();` — Zooms the media image to fit within the available space
- L68 _public prototype_ `void ZoomTo100();` — Makes the original image look unscaled
- L73 _private prototype_ `void ApplyZoom(float NewScale, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Recalculates internal widget states in order to follow the new scale
- L76 _private prototype_ `void HandleResize(const FVector2D& InNewImageSize);` — Recalculates internal widget states on order to follow the new image size
- L79 _private prototype_ `void OnObservableUpdated();` — Called when the observable entity bound to this widget is changed
- L84 _private member_ `TWeakPtr<IClusterObservable> Observable;` — Actual observable being shown by this widget
- L89 _private member_ `TSharedPtr<SScrollBox> ScrollBoxH;` — Horizontal scroll box. Manages the visible area of the media image.
- L92 _private member_ `TSharedPtr<SScrollBar> HScrollBar;` — Horizontal scroll bar. Used to scroll the image horizontally.
- L95 _private member_ `TSharedPtr<SScrollBox> ScrollBoxV;` — Vertical scroll box. Manages the visible area of the media image.
- L98 _private member_ `TSharedPtr<SScrollBar> VScrollBar;` — Vertical scroll bar. Used to scroll the image vertically.
- L103 _private member_ `bool bIsPanning = false;` — Whether is panning currently
- L106 _private member_ `FVector2D PanStartMousePos = FVector2D::ZeroVector;` — Cursor position at which panning has started
- L109 _private member_ `float PanStartScrollOffsetH = 0.f;` — Current scroll step provided by a correpsonding scroll box (horizontal). Used to calculate final panning offset.
- L112 _private member_ `float PanStartScrollOffsetV = 0.f;` — Current scroll step provided by a correpsonding scroll box (vertical). Used to calculate final panning offset.
- L117 _private member_ `float CurrentZoom = 1.f;` — Current image scale
- L120 _private member_ `float ZoomStep = 0.1f;` — Scale step per iteration (mouse wheel notch)
- L123 _private member_ `float ZoomMin = 0.1f;` — Minimum possible zoom
- L126 _private member_ `float ZoomMax = 8.f;` — Maximum possible zoom
- L131 _private member_ `TSharedPtr<SBox> ImageSizeBox;` — The box widget used to control the actual content (media image) size
- L134 _private member_ `FVector2D OriginalImageSize = FVector2D(512.f, 512.f);` — Original non-scaled image size

### `Plugins/Runtime/nDisplay/Source/DisplayClusterMonitorEditor/Private/Widgets/SSessionViewport.h` (Private)


#### class `UClusterObservableViewportToolbarContext`  
`class UClusterObservableViewportToolbarContext : public UObject`  
_L24-46_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Session viewport toolbar context Provides contextual information to the viewport toolbar
- L31 _public function_ `TSharedPtr<SSessionViewport> GetViewportWidget() const` — Returns owning viewport widget
- L37 _public function_ `void SetViewportWidget(const TSharedPtr<SSessionViewport>& InWidget)` — Sets owning viewport widget
- L45 _private member_ `TWeakPtr<SSessionViewport> ViewportWidget;` — Session viewport widget that owns the toolbar

#### class `SSessionViewport`  
`class SSessionViewport : public SCompoundWidget`  
_L57-160_
- inherits: `SCompoundWidget`
- desc: Session Viewport Widget This widget represents a single media observation session. It also: - Provides some additional session control tools - Provides some session information - Provides Maximized and Immersive panel modes
- L60 _public function_ `SLATE_BEGIN_ARGS(SSessionViewport)`
- L62 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<SClusterSessionsView> InOwningView, TSharedPtr<IClusterMonitorController> InController, TSharedPtr<IClusterObservable> InObservable);`
- L70 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L71 _public prototype_ `virtual bool SupportsKeyboardFocus() const override;`
- L77 _private prototype_ `TSharedRef<SWidget> CreateWidget_Toolbar();` — Creates viewport toolbar widget
- L80 _private prototype_ `TSharedRef<SWidget> CreateWidget_Media();` — Creates media output widget
- L83 _private prototype_ `TSharedRef<SWidget> CreateWidget_Statusbar();` — Creates information/status bar
- L86 _private prototype_ `TSharedRef<SWidget> CreateWidget_ZoomControl();` — Creates zoom control widget
- L91 _private prototype_ `void BindCommands();` — Binds UI commands that this viewport handles
- L94 _private prototype_ `FToolMenuEntry CreateMenu_Title();` — Toolbar: Viewport title
- L97 _private prototype_ `FToolMenuEntry CreateMenu_SessionControl();` — Toolbar: Session control tools (play, stop, etc.)
- L100 _private prototype_ `FToolMenuEntry CreateMenu_ZoomControl();` — Toolbar: Zoom control tools (Fit, 100%, etc.)
- L103 _private prototype_ `FToolMenuEntry CreateMenu_ViewportControl();` — Toolbar: Viewport control tools (maximize, immerse)
- L106 _private prototype_ `FToolMenuEntry CreateSubMenu_ViewportMaximize();` — Toolbar: Maximize viewport button
- L109 _private prototype_ `FToolMenuEntry CreateMenu_ViewportClose();` — Toolbar: Close viewport button
- L114 _private prototype_ `bool IsMaximized() const;` — Whether this viewport is maximized currently
- L117 _private prototype_ `bool IsImmersive() const;` — Whether this viewport is in immersive mode currently
- L122 _private prototype_ `void OnClicked_Play();` — Handles 'Play' button pressed
- L125 _private prototype_ `void OnClicked_Pause();` — Handles 'Pause' button pressed
- L128 _private prototype_ `void OnClicked_Stop();` — Handles 'Stop' button pressed
- L133 _private prototype_ `EVisibility GetLayerVisibility_Throbber() const;` — Returns current visibility of the throbber layer
- L136 _private prototype_ `EVisibility GetLayerVisibility_Error() const;` — Returns current visibility of the error message layer
- L141 _private member_ `TWeakPtr<SClusterSessionsView> OwningView;` — The owning session view panel
- L144 _private member_ `TWeakPtr<IClusterMonitorController> Controller;` — Current cluster monitor controller
- L147 _private member_ `TWeakPtr<IClusterObservable> Observable;` — Actual observable entity bound to this session viewport
- L150 _private member_ `TSharedPtr<FUICommandList> CommandList;` — UI commands bound to this viewport
- L153 _private member_ `TSharedPtr<SObservableMediaImage> MediaImage;` — Media image widget
- L159 _private member_ `bool bWasMaximizedBeforeImmersive = false;` — Stores the window's maximized state before entering immersive mode. This allows restoring the correct state after exiting immersive mode.
