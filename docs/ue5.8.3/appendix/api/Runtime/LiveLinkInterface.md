# Runtime / LiveLinkInterface

- module root: `Source/Runtime/LiveLinkInterface`
- headers: 41; symbols: 852
- symbol kinds: class=34, delegate=13, enum=5, enumerator=18, function=147, macro=5, member=249, namespace=6, prototype=303, struct=57, typedef=8, variable=7
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/LiveLinkInterface/Private/LiveLinkPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkRoles, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkRoles, Log, All);`

### `Source/Runtime/LiveLinkInterface/Public/ILiveLinkClient.h` (Public)


#### enum `ELiveLinkSubjectState`  
`enum class ELiveLinkSubjectState : uint8`  
_L27-41_
- reflection: `UENUM(BlueprintType)`
- desc: Describes the state of a live link subject
- L30 _public enumerator_ `Connected` — The input is connected.
- L32 _public enumerator_ `Unresponsive` — The input is connected but no data is available.
- L34 _public enumerator_ `Disconnected` — The input is not connected.
- L36 _public enumerator_ `InvalidOrDisabled` — The subject is invalid or disabled
- L38 _public enumerator_ `Paused` — The subject is currently paused.
- L40 _public enumerator_ `Unknown` — The state of the subject is unknown. e.g. It cannot be queried

#### class `ILiveLinkClient`  
`class ILiveLinkClient : public IModularFeature`  
_L60-371_
- inherits: `IModularFeature`
- desc: Interface for streaming and consuming data from external sources into UE4. A LiveLinkSource, may stream multiple LiveLinkSubject. Pushing and evaluating data can be executed on any thread. The other functions must be executed on the Game Thread. Subject may shared name between sources, but only 1 of those subjects may be enabled.
- L63 _public member_ `static const int32 LIVELINK_VERSION = 2;`
- L65 _public prototype_ `virtual ~ILiveLinkClient() = default;`
- L67 _public member_ `static FName ModularFeatureName;`
- L70 _public prototype_ `virtual FGuid AddSource(TSharedPtr<ILiveLinkSource> Source) = 0;` — Add a new live link source to the client
- L73 _public prototype_ `virtual FGuid AddVirtualSubjectSource(FName SourceName) = 0;` — Add a new live link VirtualSubject source to the client
- L76 _public prototype_ `virtual bool CreateSource(const FLiveLinkSourcePreset& SourcePreset) = 0;` — Create from the factory a new live link source and add it to the client. The settings will be duplicated.
- L79 _public prototype_ `virtual void RemoveSource(TSharedPtr<ILiveLinkSource> Source) = 0;` — Remove the specified source from the live link client
- L82 _public prototype_ `virtual void RemoveSource(FGuid SourceGuid) = 0;` — Remove the source specified by the source Id from the live link client
- L85 _public prototype_ `virtual bool HasSourceBeenAdded(TSharedPtr<ILiveLinkSource> Source) const = 0;` — Is the source been added
- L92 _public prototype_ `virtual TArray<FGuid> GetSources(bool bEvenIfPendingKill = false) const = 0;` — Get a list of all the sources @param bEvenIfPendingKill Whether or not to include sources that are pending kill. @return the list of sources.
- L99 _public prototype_ `virtual TArray<FGuid> GetVirtualSources(bool bEvenIfPendingKill = false) const = 0;` — Get a list of all the VirtualSubjects sources @param bEvenIfPendingKill Whether or not to include sources that are pending kill. @return the list of sources.
- L102 _public prototype_ `virtual FLiveLinkSourcePreset GetSourcePreset(FGuid SourceGuid, UObject* DuplicatedObjectOuter) const = 0;` — Get the source preset from the live link client. The settings will be duplicated into DuplicatedObjectOuter.
- L105 _public prototype_ `virtual FText GetSourceType(FGuid SourceGuid) const = 0;` — Get the type of a source
- L108 _public prototype_ `virtual FText GetSourceStatus(FGuid EntryGuid) const = 0;` — Get the status of a source
- L111 _public prototype_ `virtual FText GetSourceToolTip(FGuid EntryGuid) const = 0;` — Get the tooltip of a source
- L114 _public prototype_ `virtual FText GetSourceMachineName(FGuid EntryGuid) const = 0;` — Get the machine name of the source.
- L117 _public prototype_ `virtual bool IsSourceStillValid(FGuid EntryGuid) const = 0;` — Returns whether the Source is connected to its data provider and can still push valid data.
- L120 _public prototype_ `virtual void PushSubjectStaticData_AnyThread(const FLiveLinkSubjectKey& SubjectKey, TSubclassOf<ULiveLinkRole> Role, FLiveLinkStaticDataStruct&& StaticData) = 0;` — Push static data for a specific subject for a certain role. This will clear all buffered frames
- L123 _public prototype_ `virtual void PushSubjectFrameData_AnyThread(const FLiveLinkSubjectKey& SubjectKey, FLiveLinkFrameDataStruct&& FrameData) = 0;` — Push frame data for a specific subject for a certain role
- L126 _public prototype_ `virtual bool CreateSubject(const FLiveLinkSubjectPreset& SubjectPreset) = 0;` — Create and add a new live link subject to the client
- L129 _public prototype_ `virtual bool AddVirtualSubject(const FLiveLinkSubjectKey& VirtualSubjectKey, TSubclassOf<ULiveLinkVirtualSubject> VirtualSubjectClass) = 0;` — Add a new virtual subject to the client
- L132 _public prototype_ `virtual void RemoveVirtualSubject(const FLiveLinkSubjectKey& VirtualSubjectKey) = 0;` — Removes a virtual subject from the client
- L135 _public prototype_ `virtual void RemoveSubject_AnyThread(const FLiveLinkSubjectKey& SubjectName) = 0;` — Clear the subject from the specific source
- L138 _public prototype_ `virtual void PauseSubject_AnyThread(FLiveLinkSubjectName SubjectName) = 0;` — Pause a subject. It will keep its subject snapshot until it's unpaused.
- L141 _public prototype_ `virtual void UnpauseSubject_AnyThread(FLiveLinkSubjectName SubjectName) = 0;` — Unpause a subject, resuming its normal operation.
- L144 _public prototype_ `virtual void ClearSubjectsFrames_AnyThread(FLiveLinkSubjectName SubjectName) = 0;` — Clear the stored frames associated with the enabled subject
- L147 _public prototype_ `virtual void ClearSubjectsFrames_AnyThread(const FLiveLinkSubjectKey& SubjectKey) = 0;` — Clear the stored frames associated with the subject
- L150 _public prototype_ `virtual void ClearAllSubjectsFrames_AnyThread() = 0;` — Clear all subjects frames
- L153 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetSubjectRole_AnyThread(const FLiveLinkSubjectKey& SubjectKey) const = 0;` — Get the role of a subject from a specific source
- L156 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetSubjectRole_AnyThread(FLiveLinkSubjectName SubjectName) const = 0;` — Get the role of the subject with this name
- L162 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetSubjectTranslatedRole_AnyThread(const FLiveLinkSubjectKey& SubjectKey) const = 0;` — Get the translated role of a subject (if it's being translated before being rebroadcast). If the subject is not being translated, this function will return an invalid TSubclassOf.
- L165 _public prototype_ `virtual bool DoesSubjectSupportsRole_AnyThread(const FLiveLinkSubjectKey& SubjectKey, TSubclassOf<ULiveLinkRole> SupportedRole) const = 0;` — Whether a subject support a particular role, either directly or through a translator
- L168 _public prototype_ `virtual bool DoesSubjectSupportsRole_AnyThread(FLiveLinkSubjectName SubjectName, TSubclassOf<ULiveLinkRole> SupportedRole) const = 0;` — Whether a subject support a particular role, either directly or through a translator
- L171 _public prototype_ `virtual FLiveLinkSubjectPreset GetSubjectPreset(const FLiveLinkSubjectKey& SubjectKey, UObject* DuplicatedObjectOuter) const = 0;` — Get the subject preset from the live link client. The settings will be duplicated into DuplicatedObjectOuter.
- L174 _public prototype_ `virtual TArray<FLiveLinkSubjectKey> GetSubjects(bool bIncludeDisabledSubject, bool bIncludeVirtualSubject) const = 0;` — Get a list of all subjects
- L177 _public prototype_ `virtual bool IsSubjectValid(const FLiveLinkSubjectKey& SubjectKey) const = 0;` — Whether or not a subject from a specific source is valid and has valid snapshot data
- L180 _public prototype_ `virtual bool IsSubjectValid(FLiveLinkSubjectName SubjectName) const = 0;` — Whether or not the client has a subject with this name that is valid and has valid snapshot data
- L188 _public prototype_ `virtual bool IsSubjectEnabled(const FLiveLinkSubjectKey& SubjectKey, bool bForThisFrame) const = 0;` — Whether or not a subject from the specific source is the enabled subject. Only 1 subject with the same name can be enabled. At the start of the frame, a snapshot of the enabled subjects will be made. That snapshot dictate which subject will be used for the duration of that frame.
- L196 _public prototype_ `virtual bool IsSubjectEnabled(FLiveLinkSubjectName SubjectName) const = 0;` — Whether or not the client has a subject with this name enabled Only 1 subject with the same name can be enabled. At the start of the frame, a snapshot of the enabled subjects will be made. That snapshot dictate which subject will be used for the duration of that frame.
- L205 _public prototype_ `virtual void SetSubjectEnabled(const FLiveLinkSubjectKey& SubjectKey, bool bEnabled) = 0;` — Set the subject's from a specific source to enabled, disabling the other in the process. Only 1 subject with the same name can be enabled. At the start of the frame, a snapshot of the enabled subjects will be made. That snapshot dictate which subject will be used for the duration of that frame. SetSubjectEnabled will take effect on the next frame.
- L214 _public prototype_ `virtual void SetSubjectEnabled(FLiveLinkSubjectName SubjectName, bool bEnabled) = 0;` — Set the subject's from a specific source to enabled, disabling the other in the process. Only 1 subject with the same name can be enabled. At the start of the frame, a snapshot of the enabled subjects will be made. That snapshot dictate which subject will be used for the duration of that frame. SetSubjectEnabled will take effect on the next frame.
- L217 _public prototype_ `virtual bool IsSubjectTimeSynchronized(const FLiveLinkSubjectKey& SubjectKey) const = 0;` — Whether or not the subject's data, from a specific source, is time synchronized or not
- L220 _public prototype_ `virtual bool IsSubjectTimeSynchronized(FLiveLinkSubjectName SubjectName) const = 0;` — Whether or not the subject's data is time synchronized or not
- L223 _public prototype_ `virtual bool IsVirtualSubject(const FLiveLinkSubjectKey& SubjectKey) const = 0;` — Whether the subject key points to a virtual subject
- L226 _public prototype_ `virtual ELiveLinkSubjectState GetSubjectState(FLiveLinkSubjectName InSubjectName) const = 0;` — Returns the state of the given subject name.
- L229 _public prototype_ `virtual TArray<FLiveLinkSubjectKey> GetSubjectsSupportingRole(TSubclassOf<ULiveLinkRole> SupportedRole, bool bIncludeDisabledSubject, bool bIncludeVirtualSubject) const = 0;` — Get a list of name of subjects supporting a certain role
- L235 _public prototype_ `virtual TArray<FLiveLinkTime> GetSubjectFrameTimes(const FLiveLinkSubjectKey& SubjectKey) const = 0;` — Get the time of all the frames for a specific subject, including computed offsets. @note Use for debugging purposes.
- L240 _public prototype_ `virtual ULiveLinkSourceSettings* GetSourceSettings(const FGuid& SourceKey) const = 0;` — Get the Settings of this source.
- L246 _public prototype_ `virtual TArray<FLiveLinkTime> GetSubjectFrameTimes(FLiveLinkSubjectName SubjectName) const = 0;` — Get the time of all the frames for a specific subject, including computed offsets. @note Use for debugging purposes.
- L252 _public prototype_ `virtual UObject* GetSubjectSettings(const FLiveLinkSubjectKey& SubjectKey) const = 0;` — Get the Settings of this subject. @note If subject is a VirtualSubject, the VirtualSubject itself is returned.
- L255 _public prototype_ `virtual FText GetSourceNameOverride(const FLiveLinkSubjectKey& SubjectKey) const = 0;` — Get the source name override for a given subject. Allows subjects to modify the source's display name in the UI when needed.
- L258 _public prototype_ `virtual FText GetSubjectDisplayName(const FLiveLinkSubjectKey& SubjectKey) const = 0;` — Get the display name for a subject. Returns an empty text if the source is invalid.
- L265 _public prototype_ `virtual const FLiveLinkStaticDataStruct* GetSubjectStaticData_AnyThread(const FLiveLinkSubjectKey& InSubjectKey, bool bGetOverrideData=true) const = 0;` — Utility method to grab a subject's static data. Used by the RecordingController when static data is missing from the recording. @param InSubjectKey The subject key to use. @param bGetOverrideData Whether to get static override data if it exists.
- L273 _public prototype_ `virtual bool EvaluateFrameFromSource_AnyThread(const FLiveLinkSubjectKey& SubjectKey, TSubclassOf<ULiveLinkRole> Role, FLiveLinkSubjectFrameData& OutFrame) = 0;` — Return the evaluated subject from a specific source snapshot for a specific role. A subject could have to go through a translator to output in the desired role. @note This will always return the same value for a specific frame. @note The prefer method is EvaluateFrame_AnyThread this method should be used for diagnostic or replication.
- L282 _public prototype_ `virtual bool EvaluateFrame_AnyThread(FLiveLinkSubjectName SubjectName, TSubclassOf<ULiveLinkRole> Role, FLiveLinkSubjectFrameData& OutFrame) = 0;` — Return the evaluated subject snapshot for a specific role. The subject may go through a translator to get the desired role's frame data. @return True if the snapshot is valid. @note This will always return the same value for a specific frame. @see ULiveLinkSourceSettings
- L292 _public prototype_ `virtual bool EvaluateFrameAtWorldTime_AnyThread(FLiveLinkSubjectName SubjectName, double WorldTime, TSubclassOf<ULiveLinkRole> DesiredRole, FLiveLinkSubjectFrameData& OutFrame) = 0;` — Evaluates a subject for a specific role. The subject may go through a translator to get the desired role's frame data. If it's a virtual subject EvaluateFrame_AnyThread will be used instead. @return True if a frame data was calculated. @note This value is not cached. @see ULiveLinkSourceSettings
- L295 _public function_ `virtual bool EvaluateFrameAtSceneTime_AnyThread(FLiveLinkSubjectName SubjectName, const FTimecode& SceneTime, TSubclassOf<ULiveLinkRole> DesiredRole, FLiveLinkSubjectFrameData& OutFrame)` — `UE_DEPRECATED(4.25, "ILiveLinkClient::EvaluateFrameAtSceneTime_AnyThread is deprecated. Please use ILiveLinkClient::EvaluateFrameAtSceneTime_AnyThread with a QualifiedFrameTime instead!")`
- L305 _public prototype_ `virtual bool EvaluateFrameAtSceneTime_AnyThread(FLiveLinkSubjectName SubjectName, const FQualifiedFrameTime& SceneTime, TSubclassOf<ULiveLinkRole> DesiredRole, FLiveLinkSubjectFrameData& OutFrame) = 0;` — Evaluates a subject for a specific role at a scene time. The subject may go through a translator to get the desired role's frame data. If it's a virtual subject EvaluateFrame_AnyThread will be used instead. @return True if a frame data was calculated. @note This value is not cached. @see ULiveLinkSourceSettings
- L308 _public prototype_ `virtual FSimpleMulticastDelegate& OnLiveLinkTicked() = 0;` — Notify when the LiveLinkClient has ticked.
- L313 _public prototype_ `virtual void ForceTick() = 0;` — Performs an internal Tick(). This is to be used when we want to run live link outside of the normal engine tick workflow, for example when we need to export data that requires live link evaluation during the export process.
- L316 _public prototype_ `virtual bool HasPendingSubjectFrames() = 0;` — Returns true if the client has pending subject frames to process during its next tick
- L319 _public prototype_ `virtual void ClearOverrideStaticData_AnyThread(const FLiveLinkSubjectKey& InSubjectKey) = 0;` — Claer the override static data used by the subject remapper.
- L322 _public prototype_ `virtual FSimpleMulticastDelegate& OnLiveLinkSourcesChanged() = 0;` — Notify when the list of sources has changed.
- L325 _public prototype_ `virtual FSimpleMulticastDelegate& OnLiveLinkSubjectsChanged() = 0;` — Notify when the list of subject has changed.
- L328 _public prototype_ `virtual FOnLiveLinkSourceChangedDelegate& OnLiveLinkSourceAdded() = 0;` — Notify when a new source has been added
- L331 _public prototype_ `virtual FOnLiveLinkSourceChangedDelegate& OnLiveLinkSourceRemoved() = 0;` — Notify when a source has been removed
- L334 _public prototype_ `virtual FOnLiveLinkSubjectChangedDelegate& OnLiveLinkSubjectAdded() = 0;` — Notify when a new subject has been added
- L337 _public prototype_ `virtual FOnLiveLinkSubjectChangedDelegate& OnLiveLinkSubjectRemoved() = 0;` — Notify when a subject has been removed
- L340 _public prototype_ `virtual FOnLiveLinkSubjectStateChanged& OnLiveLinkSubjectStateChanged() = 0;` — Notify when a subject's state has changed.
- L343 _public prototype_ `virtual FOnLiveLinkSubjectEnabledDelegate& OnLiveLinkSubjectEnabledChanged() = 0;` — Notify when a subject is enabled or disabled.
- L347 _public prototype_ `virtual FOnLiveLinkSubjectEvaluated& OnLiveLinkSubjectEvaluated() = 0;` — Notify the debug interface when a subject has been evaluated. Only available in editor and used for debugging purpose.
- L355 _public prototype_ `virtual void RegisterForFrameDataReceived(const FLiveLinkSubjectKey& InSubjectKey, const FOnLiveLinkSubjectStaticDataReceived::FDelegate& OnStaticDataReceived_AnyThread, const FOnLiveLinkSubjectFrameDataReceived::FDelegate& OnFrameDataReceived_AnyThread, FDelegateHandle& OutStaticDataReceivedHandle, FDelegateHandle& OutFrameDataReceivedHandleconst) = 0;` — Register for when a frame data was received. This will be called as soon as it is received. It has not been validated or added. The frame is not ready to be used. The callback may be call on any thread.
- L357 _public prototype_ `virtual void UnregisterForFrameDataReceived(const FLiveLinkSubjectKey& InSubjectKey, FDelegateHandle InStaticDataReceivedHandle, FDelegateHandle InFrameDataReceivedHandle) = 0;` — Unregister delegate registered with RegisterForFrameDataReceived.
- L366 _public prototype_ `virtual bool RegisterForSubjectFrames(FLiveLinkSubjectName SubjectName, const FOnLiveLinkSubjectStaticDataAdded::FDelegate& OnStaticDataAdded, const FOnLiveLinkSubjectFrameDataAdded::FDelegate& OnFrameDataAddedd, FDelegateHandle& OutStaticDataAddedHandle, FDelegateHandle& OutFrameDataAddeddHandle, TSubclassOf<ULiveLinkRole>& OutSubjectRole, FLiveLinkStaticDataStruct* OutStaticData = nullptr) = 0;` — Register for when a frame has been validated, added and ready to be used. If provided, OutStaticData may be invalid if the Subject has not received Static Data, or if the static data has not been processed yet. @return True if the subject was found and the delegates were registered. False otherwise.
- L369 _public prototype_ `virtual void UnregisterSubjectFramesHandle(FLiveLinkSubjectName SubjectName, FDelegateHandle StaticDataAddedHandle, FDelegateHandle FrameDataAddedHandle) = 0;` — Unregister delegates registered with RegisterForSubjectFrames.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API LIVELINKINTERFACE_API`
- L44 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnLiveLinkSourceChangedDelegate, FGuid );`
- L44 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnLiveLinkSourceChangedDelegate, FGuid );`
- L45 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnLiveLinkSubjectChangedDelegate, FLiveLinkSubjectKey );`
- L45 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnLiveLinkSubjectChangedDelegate, FLiveLinkSubjectKey );`
- L46 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnLiveLinkSubjectStaticDataReceived, const FLiveLinkStaticDataStruct& ) DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnLiveLinkSubjectFrameDataReceived, const FLiveLinkFrameDataStruct& ) DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnLiveLinkSubjectStaticDataAdded, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkStaticDataStruct& ) DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnLiveLinkSubjectFrameDataAdded, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkFrameDataStruct& ) DECLARE_TS_MULTICAST_DELEGATE_FiveParams(FOnLiveLinkSubjectEvaluated, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkTime& , bool , const FLiveLinkTime& ) DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnLiveLinkSubjectStateChanged, FLiveLinkSubjectKey , ELiveLinkSubjectState );`
- L46 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnLiveLinkSubjectStaticDataReceived, const FLiveLinkStaticDataStruct& ) DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnLiveLinkSubjectFrameDataReceived, const FLiveLinkFrameDataStruct& ) DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnLiveLinkSubjectStaticDataAdded, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkStaticDataStruct& ) DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnLiveLinkSubjectFrameDataAdded, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkFrameDataStruct& ) DECLARE_TS_MULTICAST_DELEGATE_FiveParams(FOnLiveLinkSubjectEvaluated, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkTime& , bool , const FLiveLinkTime& ) DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnLiveLinkSubjectStateChanged, FLiveLinkSubjectKey , ELiveLinkSubjectState );`
- L47 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_OneParam(FOnLiveLinkSubjectFrameDataReceived, const FLiveLinkFrameDataStruct& ) DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnLiveLinkSubjectStaticDataAdded, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkStaticDataStruct& ) DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnLiveLinkSubjectFrameDataAdded, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkFrameDataStruct& ) DECLARE_TS_MULTICAST_DELEGATE_FiveParams(FOnLiveLinkSubjectEvaluated, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkTime& , bool , const FLiveLinkTime& ) DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnLiveLinkSubjectStateChanged, FLiveLinkSubjectKey , ELiveLinkSubjectState );`
- L48 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnLiveLinkSubjectStaticDataAdded, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkStaticDataStruct& ) DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnLiveLinkSubjectFrameDataAdded, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkFrameDataStruct& ) DECLARE_TS_MULTICAST_DELEGATE_FiveParams(FOnLiveLinkSubjectEvaluated, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkTime& , bool , const FLiveLinkTime& ) DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnLiveLinkSubjectStateChanged, FLiveLinkSubjectKey , ELiveLinkSubjectState );`
- L49 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(FOnLiveLinkSubjectFrameDataAdded, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkFrameDataStruct& ) DECLARE_TS_MULTICAST_DELEGATE_FiveParams(FOnLiveLinkSubjectEvaluated, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkTime& , bool , const FLiveLinkTime& ) DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnLiveLinkSubjectStateChanged, FLiveLinkSubjectKey , ELiveLinkSubjectState );`
- L50 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_FiveParams(FOnLiveLinkSubjectEvaluated, FLiveLinkSubjectKey , TSubclassOf<ULiveLinkRole> , const FLiveLinkTime& , bool , const FLiveLinkTime& ) DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnLiveLinkSubjectStateChanged, FLiveLinkSubjectKey , ELiveLinkSubjectState );`
- L51 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnLiveLinkSubjectStateChanged, FLiveLinkSubjectKey , ELiveLinkSubjectState );`
- L52 _delegate_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnLiveLinkSubjectEnabledDelegate, FLiveLinkSubjectKey , bool );`
- L52 _prototype_ `DECLARE_TS_MULTICAST_DELEGATE_TwoParams(FOnLiveLinkSubjectEnabledDelegate, FLiveLinkSubjectKey , bool );`

### `Source/Runtime/LiveLinkInterface/Public/ILiveLinkSource.h` (Public)


#### class `ILiveLinkSource`  
`class ILiveLinkSource`  
_L15-73_
- L18 _public prototype_ `virtual ~ILiveLinkSource() = default;`
- L21 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) = 0;` — The source has been added to the Client and a Guid has been associated.
- L27 _public function_ `virtual void InitializeSettings(ULiveLinkSourceSettings* Settings)` — The setting class has been created. Called after ReceiveClient. @see GetSettingsClass
- L33 _public function_ `virtual void Update()` — Update the source. This is called in a critical path on the game thread. The user is expected to return quickly.
- L36 _public function_ `virtual bool CanBeDisplayedInUI() const` — Can this source be displayed in the Source UI list
- L39 _public prototype_ `virtual bool IsSourceStillValid() const = 0;` — Returns whether the Source is connected to its data provider and can still push valid data.
- L46 _public prototype_ `virtual bool RequestSourceShutdown() = 0;` — Request the source to shutdown. This may be called multiple times. Should return true, when the source can be destroyed. RequestSourceShutdown will be called multiple times until it returns true. If the source is multithreaded, the source should test if it can be shutdown, set a flag and return immediately.
- L49 _public prototype_ `virtual FText GetSourceType() const = 0;` — For UI, what is the identifier of the source.
- L52 _public prototype_ `virtual FText GetSourceMachineName() const = 0;` — For UI, from where the source data is coming from.
- L56 _public prototype_ `virtual FText GetSourceStatus() const = 0;` — For UI, what is the status of the source. Should be: "Active", "Not responding", "Connecting" or any short message that makes sense for the source.
- L61 _public function_ `virtual FText GetSourceToolTip() const` — For UI, what should be shown in the source list when hovering this source.
- L67 _public function_ `virtual TSubclassOf<ULiveLinkSourceSettings> GetSettingsClass() const` — Setting class to display and used by the Source. An instance of that class will be constructed when the source is added to the Client. Then InitializeSettings will be called.
- L69 _public function_ `virtual UClass* GetCustomSettingsClass() const` — `UE_DEPRECATED(4.24, "ILiveLinkClient::GetCustomSettingsClass is deprecated. Please use GetSettingsClass instead!")`
- L72 _public function_ `virtual void OnSettingsChanged(ULiveLinkSourceSettings* Settings, const FPropertyChangedEvent& PropertyChangedEvent)` — Notification when a setting value has changed via the UI.

#### struct `FLiveLinkSourceHandle`  
`struct FLiveLinkSourceHandle`  
_L77-90_
- reflection: `USTRUCT(BlueprintType)`
- desc: A Blueprint handle to a specific LiveLink Source
- L81 _public prototype_ `FLiveLinkSourceHandle() = default;`
- L82 _public prototype_ `virtual ~FLiveLinkSourceHandle() = default;`
- L84 _public function_ `void SetSourcePointer(TSharedPtr<ILiveLinkSource> InSourcePointer)`
- L89 _public member_ `TSharedPtr<ILiveLinkSource> SourcePointer;`

### `Source/Runtime/LiveLinkInterface/Public/ILiveLinkSubject.h` (Public)


#### class `ILiveLinkSubject`  
`class ILiveLinkSubject`  
_L25-92_
- desc: The base class of a LiveLink subject. Subjects are individual streams of data within the client. An animating character could be a subject for instance.
- L28 _public prototype_ `virtual ~ILiveLinkSubject() = default;`
- L29 _public prototype_ `virtual void Initialize(FLiveLinkSubjectKey SubjectKey, TSubclassOf<ULiveLinkRole> Role, ILiveLinkClient* LiveLinkClient) = 0;`
- L30 _public prototype_ `virtual void Update() = 0;`
- L31 _public prototype_ `virtual bool EvaluateFrame(TSubclassOf<ULiveLinkRole> InDesiredRole, FLiveLinkSubjectFrameData& OutFrame);`
- L32 _public prototype_ `virtual void ClearFrames() = 0;`
- L34 _public prototype_ `virtual FLiveLinkSubjectKey GetSubjectKey() const = 0;`
- L35 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const = 0;`
- L36 _public prototype_ `virtual bool SupportsRole(TSubclassOf<ULiveLinkRole> InDesiredRole) const;`
- L38 _public prototype_ `virtual bool HasValidFrameSnapshot() const = 0;`
- L39 _public prototype_ `virtual FLiveLinkStaticDataStruct& GetStaticData(bool bGetOverrideData=true) = 0;`
- L40 _public prototype_ `virtual const FLiveLinkStaticDataStruct& GetStaticData() const = 0;`
- L41 _public prototype_ `virtual TArray<FLiveLinkTime> GetFrameTimes() const = 0;`
- L44 _public prototype_ `virtual const TArray<ULiveLinkFrameTranslator::FWorkerSharedPtr> GetFrameTranslators() const = 0;` — List of available translator the subject can use.
- L47 _public prototype_ `virtual const ULiveLinkSubjectRemapper::FWorkerSharedPtr GetFrameRemapper() const = 0;` — Get this subject's frame remapper.
- L50 _public prototype_ `virtual bool IsRebroadcasted() const = 0;` — Whether this subject is rebroadcasted
- L53 _public prototype_ `virtual bool HasStaticDataBeenRebroadcasted() const = 0;` — When rebroadcasting, has the static data been rebroadcasted?
- L56 _public prototype_ `virtual void SetStaticDataAsRebroadcasted(const bool bInSent) = 0;` — Sets the static data for this subject as rebroadcasted
- L60 _public function_ `virtual void PreprocessFrame(FLiveLinkFrameDataStruct& InOutFrameData)` — `UE_DEPRECATED(5.6, "Replaced with a new version of PreprocessFrame that also provides const static data.")` — Apply this subject's preprocessors to frame data.
- L63 _public function_ `virtual void PreprocessFrame(const FLiveLinkStaticDataStruct& InStaticData, FLiveLinkFrameDataStruct& InOutFrameData)` — Apply this subject's preprocessors to frame data. Provides static data as a const reference.
- L66 _public function_ `virtual void RemapFrame(FLiveLinkSkeletonStaticData& InOutSkeletonData, FLiveLinkAnimationFrameData& InOutFrameData)` — Apply a remapper to a frame data. Called after preprocessing.
- L69 _public prototype_ `virtual bool IsPaused() const = 0;` — Pause/Unpause subject.
- L72 _public prototype_ `virtual void PauseSubject() = 0;` — Pause subject.
- L75 _public prototype_ `virtual void UnpauseSubject() = 0;` — Unpause subject.
- L78 _public function_ `FLiveLinkFrameIdentifier GetSnapshotFrameId() const` — Get the frame ID of the last snapshot that was captured.
- L88 _protected prototype_ `virtual const FLiveLinkSubjectFrameData& GetFrameSnapshot() const = 0;`
- L91 _protected prototype_ `static bool Translate(const ILiveLinkSubject* LinkSubject, TSubclassOf<ULiveLinkRole> DesiredRole, const FLiveLinkStaticDataStruct& StaticData, const FLiveLinkFrameDataStruct& FrameData, FLiveLinkSubjectFrameData& OutFrame);`

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkController.h` (Public)


#### class `ULiveLinkController`  
`class ULiveLinkController : public UObject`  
_L21-37_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Basic object to control a UObject live link frames
- L26 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const PURE_VIRTUAL(ULiveLinkController::GetRole, return TSubclassOf<ULiveLinkRole>(););`
- L29 _public function_ `virtual void OnRegistered()` — Initialize the controller at the first tick of its owner component.
- L32 _public function_ `virtual void Tick(float DeltaTime, const FLiveLinkSubjectRepresentation& SubjectRepresentation)` — Function called every frame.
- L35 _public function_ `virtual void InitializeInEditor(UObject* FromObject)`

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkCurveRemapSettings.h` (Public)


#### struct `FLiveLinkCurveConversionSettings`  
`struct FLiveLinkCurveConversionSettings`  
_L19-25_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public member_ `TMap<FString, FSoftObjectPath> CurveConversionAssetMap;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (AllowedClasses = "/Script/Engine.PoseAsset"))`

#### class `ULiveLinkCurveRemapSettings`  
`class ULiveLinkCurveRemapSettings : public ULiveLinkSourceSettings`  
_L28-42_
- reflection: `UCLASS(config=Engine, defaultconfig, meta=(DisplayName="LiveLink"), MinimalAPI)`
- inherits: `ULiveLinkSourceSettings`
- L34 _public member_ `FLiveLinkCurveConversionSettings CurveConversionSettings;` — `UPROPERTY(EditAnywhere, config, Category = "Curve Conversion Settings")`
- L39 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject override so we can change this setting when changed in editor

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkCustomVersion.h` (Public)


#### struct `FLiveLinkCustomVersion`  
`struct FLiveLinkCustomVersion`  
_L11-30_
- desc: Custom serialization version for all packages containing LiveLink dependent asset types
- L26 _public member_ `static const FGuid GUID;` — The GUID for this custom version number
- L29 _private function_ `FLiveLinkCustomVersion()`

#### enum `FLiveLinkCustomVersion::Type`  
`enum Type`  
_L13-23_
- L16 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made in the plugin
- L18 _public enumerator_ `NewLiveLinkRoleSystem`
- L21 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L22 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LIVELINKINTERFACE_API`

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkDefaultColumns.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace LiveLink` (scope `UE`)
- L8 _namespace_ `namespace DefaultColumn` (scope `UE::LiveLink`)
- L10 _variable_ `inline const FName Action = "Ac` (scope `UE::LiveLink::DefaultColumn`)
- L11 _variable_ `inline const FName Name = "Na` (scope `UE::LiveLink::DefaultColumn`)
- L12 _variable_ `inline const FName Machine = "Ma` (scope `UE::LiveLink::DefaultColumn`)
- L13 _variable_ `inline const FName TranslatedRole = "Tr` (scope `UE::LiveLink::DefaultColumn`)
- L14 _variable_ `inline const FName Role = "Ro` (scope `UE::LiveLink::DefaultColumn`)
- L15 _variable_ `inline const FName Status = "St` (scope `UE::LiveLink::DefaultColumn`)

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkFrameInterpolationProcessor.h` (Public)


#### struct `FLiveLinkInterpolationInfo`  
`struct FLiveLinkInterpolationInfo`  
_L20-37_
- desc: Information about the interpolation that was done Used to give some cues to the caller about what's happened
- L23 _public member_ `float ExpectedEvaluationDistanceFromNewestSeconds;` — Distance in seconds between expected evaluation time and newest sample
- L26 _public member_ `float ExpectedEvaluationDistanceFromOldestSeconds;` — Distance in seconds between expected evaluation time and oldest sample
- L29 _public member_ `int32 FrameIndexA = INDEX_NONE;` — Frame indices interpolated between
- L30 _public member_ `int32 FrameIndexB = INDEX_NONE;`
- L33 _public member_ `bool bUnderflowDetected = false;` — Whether sampling was done below our oldest sample
- L36 _public member_ `bool bOverflowDetected = false;` — Whether interpolation point was above our newest sample

#### class `ILiveLinkFrameInterpolationProcessorWorker`  
`class ILiveLinkFrameInterpolationProcessorWorker`  
_L45-52_
- desc: Basic object to interpolate live link frames Inherit from it to do custom blending for your data type @note It can be called from any thread
- L48 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const = 0;`
- L50 _public prototype_ `virtual void Interpolate(double InTime, const FLiveLinkStaticDataStruct& InStaticData, const TArray<FLiveLinkFrameDataStruct>& InSourceFrames, FLiveLinkSubjectFrameData& OutBlendedFrame, FLiveLinkInterpolationInfo& OutInterpolationInfo) = 0;`
- L51 _public prototype_ `virtual void Interpolate(const FQualifiedFrameTime& InTime, const FLiveLinkStaticDataStruct& InStaticData, const TArray<FLiveLinkFrameDataStruct>& InSourceFrames, FLiveLinkSubjectFrameData& OutBlendedFrame, FLiveLinkInterpolationInfo& OutInterpolationInfo) = 0;`

#### class `ULiveLinkFrameInterpolationProcessor`  
`class ULiveLinkFrameInterpolationProcessor : public UObject`  
_L61-70_
- reflection: `UCLASS(Abstract, editinlinenew, ClassGroup = (LiveLink), MinimalAPI)`
- inherits: `UObject`
- desc: Basic object to interpolate live link frames Inherit from it to do custom blending for your data type @note It can only be used on the Game Thread. See ILiveLinkFrameInterpolationProcessorWorker for the any thread implementation.
- L66 _public typedef_ `using FWorkerSharedPtr = TSharedPtr<ILiveLinkFrameInterpolationProcessorWorker, ESPMode::ThreadSafe>;`
- L68 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const PURE_VIRTUAL(ULiveLinkFrameInterpolationProcessor::GetFromRole, return TSubclassOf<ULiveLinkRole>(););`
- L69 _public prototype_ `virtual FWorkerSharedPtr FetchWorker() PURE_VIRTUAL(ULiveLinkFrameInterpolationProcessor::FetchWorker, return FWorkerSharedPtr(););`

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkFramePreProcessor.h` (Public)


#### class `ILiveLinkFramePreProcessorWorker`  
`class ILiveLinkFramePreProcessorWorker`  
_L21-32_
- desc: Basic object to apply preprocessing to a live link frame. Inherit from it to add specific operations / options for a certain type of data @note It can be called from any thread
- L24 _public prototype_ `virtual ~ILiveLinkFramePreProcessorWorker() = default;`
- L25 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const = 0;`
- L28 _public function_ `virtual bool PreProcessFrame(FLiveLinkFrameDataStruct& InOutFrame) const` — Implement this method if you only require the frame data.
- L31 _public function_ `virtual bool PreProcessFrame(const FLiveLinkStaticDataStruct& InStaticData, FLiveLinkFrameDataStruct& InOutFrame)` — Implement this method if you require access to static and frame data. Note that the static data is a const reference.

#### class `ULiveLinkFramePreProcessor`  
`class ULiveLinkFramePreProcessor : public UObject`  
_L41-50_
- reflection: `UCLASS(Abstract, Blueprintable, editinlinenew, ClassGroup = (LiveLink), MinimalAPI)`
- inherits: `UObject`
- desc: Basic object to apply preprocessing to a live link frame. Inherit from it to add specific operations / options for a certain type of data @note It can only be used on the Game Thread. See ILiveLinkFramePreProcessorWorker for the any thread implementation.
- L46 _public typedef_ `using FWorkerSharedPtr = TSharedPtr<ILiveLinkFramePreProcessorWorker, ESPMode::ThreadSafe>;`
- L48 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const PURE_VIRTUAL(ULiveLinkFramePreProcessor::GetFromRole, return TSubclassOf<ULiveLinkRole>(););`
- L49 _public prototype_ `virtual FWorkerSharedPtr FetchWorker() PURE_VIRTUAL(ULiveLinkFramePreProcessor::FetchWorker, return FWorkerSharedPtr(););`

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkFrameTranslator.h` (Public)


#### class `ILiveLinkFrameTranslatorWorker`  
`class ILiveLinkFrameTranslatorWorker`  
_L25-32_
- desc: Basic object to translate data from one role to another @note It can be called from any thread
- L28 _public prototype_ `bool CanTranslate(TSubclassOf<ULiveLinkRole> ToRole) const;`
- L29 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetFromRole() const = 0;`
- L30 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetToRole() const = 0;`
- L31 _public prototype_ `virtual bool Translate(const FLiveLinkStaticDataStruct& InStaticData, const FLiveLinkFrameDataStruct& InFrameData, FLiveLinkSubjectFrameData& OutTranslatedFrame) const = 0;`

#### class `ULiveLinkFrameTranslator`  
`class ULiveLinkFrameTranslator : public UObject`  
_L40-52_
- reflection: `UCLASS(Abstract, editinlinenew, ClassGroup = (LiveLink), MinimalAPI)`
- inherits: `UObject`
- desc: Basic object to translate data from one role to another @note It can only be used on the Game Thread. See ILiveLinkFrameTranslatorWorker for the any thread implementation.
- L45 _public typedef_ `using FWorkerSharedPtr = TSharedPtr<ILiveLinkFrameTranslatorWorker, ESPMode::ThreadSafe>;`
- L47 _public prototype_ `bool CanTranslate(TSubclassOf<ULiveLinkRole> ToRole) const;`
- L49 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetFromRole() const PURE_VIRTUAL(ULiveLinkFrameTranslator::GetFromRole, return TSubclassOf<ULiveLinkRole>(););`
- L50 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetToRole() const PURE_VIRTUAL(ULiveLinkFrameTranslator::GetToRole, return TSubclassOf<ULiveLinkRole>(););`
- L51 _public prototype_ `virtual FWorkerSharedPtr FetchWorker() PURE_VIRTUAL(ULiveLinkFrameTranslator::FetchWorker, return FWorkerSharedPtr(););`

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkHub/ILiveLinkRecordingSession.h` (Public)


#### class `ILiveLinkRecordingSession`  
`class ILiveLinkRecordingSession : public IModularFeature`  
_L11-53_
- inherits: `IModularFeature`
- desc: Provides an interface for querying and controlling the recording session.
- L14 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSessionStringChanged, FStringView);`
- L15 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSessionIntChanged, int32);`
- L18 _public function_ `static FName GetModularFeatureName()` — Name of the modular feature.
- L25 _public function_ `static ILiveLinkRecordingSession& Get()` — Convenience accessor for modular implementation.
- L33 _public prototype_ `virtual FString GetSessionName() const = 0;`
- L34 _public prototype_ `virtual FString GetSlateName() const = 0;`
- L35 _public prototype_ `virtual int32 GetTakeNumber() const = 0;`
- L37 _public prototype_ `virtual bool SetSessionName(FStringView InSessionName) = 0;`
- L38 _public prototype_ `virtual bool SetSlateName(FStringView InSlateName) = 0;`
- L39 _public prototype_ `virtual bool SetTakeNumber(int32 InTakeNumber) = 0;`
- L41 _public prototype_ `virtual FOnSessionStringChanged& OnSessionNameChanged() = 0;`
- L42 _public prototype_ `virtual FOnSessionStringChanged& OnSlateNameChanged() = 0;`
- L43 _public prototype_ `virtual FOnSessionIntChanged& OnTakeNumberChanged() = 0;`
- L45 _public prototype_ `virtual bool IsRecording() const = 0;`
- L47 _public prototype_ `virtual FSimpleMulticastDelegate& OnRecordingStarted() = 0;`
- L48 _public prototype_ `virtual FSimpleMulticastDelegate& OnRecordingStopped() = 0;`
- L50 _public prototype_ `virtual bool CanRecord() const = 0;`
- L51 _public prototype_ `virtual bool StartRecording() = 0;`
- L52 _public prototype_ `virtual bool StopRecording() = 0;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSessionStringChanged, FStringView);`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSessionIntChanged, int32);`

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkHub/LiveLinkHubSessionExtraData.h` (Public)


#### class `ULiveLinkHubSessionExtraData`  
`class ULiveLinkHubSessionExtraData : public UObject`  
_L12-15_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Derive from this class to define additional UProperties that participate in session serialization.

#### class `ILiveLinkHubSessionExtraDataHandler`  
`class ILiveLinkHubSessionExtraDataHandler : public IModularFeature`  
_L19-57_
- inherits: `IModularFeature`
- desc: Implement this interface to provide session save/load handlers for your extra data subclass.
- L23 _public prototype_ `virtual TSubclassOf<ULiveLinkHubSessionExtraData> GetExtraDataClass() const = 0;` — Which derived type this handler will receive save/load events for.
- L26 _public prototype_ `virtual void OnExtraDataSessionSaving(ULiveLinkHubSessionExtraData* InExtraData) = 0;` — Update your extra data fields prior to session save.
- L29 _public prototype_ `virtual void OnExtraDataSessionLoaded(const ULiveLinkHubSessionExtraData* InExtraData) = 0;` — Handle session load. If the session was previously saved without your handler active, InExtraData may be null.
- L33 _public function_ `static FName GetModularFeatureName()` — The modular feature name used for handler registration/iteration.
- L40 _public function_ `void RegisterExtraDataHandler()` — Call this from your derived class to participate in session save/load.
- L46 _public function_ `void UnregisterExtraDataHandler()` — Call this from your derived class when finished.
- L52 _public function_ `static TArray<ILiveLinkHubSessionExtraDataHandler*> GetRegisteredHandlers()` — Used internally to iterate over registered implementations.

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkLog.h` (Public)


#### class `FLiveLinkLog`  
`class FLiveLinkLog`  
_L23-167_
- desc: This class represents a log of LiveLink output each of which can be a rich tokenized message
- L28 _public function_ `template<typename... ArgsType> static void Error(UE::Core::TCheckedFormatString<FString::FmtCharType, ArgsType...> Format, ArgsType... Args)` — Write an error in to the LiveLink log.
- L38 _public function_ `template<typename... ArgsType> static void ErrorOnce(FName MessageID, const FLiveLinkSubjectKey& SubjectKey, UE::Core::TCheckedFormatString<FString::FmtCharType, ArgsType...> Format, ArgsType... Args)` — Write a error in to the LiveLink log. If the error occurred more than once for that SubjectKey, a counter will indicate the number of time it did occurred.
- L48 _public function_ `template<typename... ArgsType> static void Warning(UE::Core::TCheckedFormatString<FString::FmtCharType, ArgsType...> Format, ArgsType... Args)` — Write an warning in to the LiveLink log.
- L58 _public function_ `template<typename... ArgsType> static void WarningOnce(FName MessageID, const FLiveLinkSubjectKey& SubjectKey, UE::Core::TCheckedFormatString<FString::FmtCharType, ArgsType...> Format, ArgsType... Args)` — Write a warning in to the LiveLink log. If the warning occurred more than once for that SubjectKey, a counter will indicate the number of time it did occurred.
- L68 _public function_ `template<typename... ArgsType> static void Info(UE::Core::TCheckedFormatString<FString::FmtCharType, ArgsType...> Format, ArgsType... Args)` — Write an info in to the LiveLink log.
- L78 _public function_ `template<typename... ArgsType> static void InfoOnce(FName MessageID, const FLiveLinkSubjectKey& SubjectKey, UE::Core::TCheckedFormatString<FString::FmtCharType, ArgsType...> Format, ArgsType... Args)` — Write a info in to the LiveLink log. If the info occurred more than once for that SubjectKey, a counter will indicate the number of time it did occurred.
- L91 _public function_ `template<typename... ArgsType> static TSharedPtr<FTokenizedMessage> TokenizedMessage(EMessageSeverity::Type Severity, UE::Core::TCheckedFormatString<FString::FmtCharType, ArgsType...> Format, ArgsType... Args)` — Write an message in to the LiveLink log. Will returns a valid TokenizedMessage if a new TokenizedMessage was created.
- L104 _public function_ `template<typename... ArgsType> static TSharedPtr<FTokenizedMessage> TokenizedMessageOnce(EMessageSeverity::Type Severity, FName MessageID, const FLiveLinkSubjectKey& SubjectKey, UE::Core::TCheckedFormatString<FString::FmtCharType, ArgsType...> Format, ArgsType... Args)` — Write a repeatable message in to the LiveLink log. Will returns a valid TokenizedMessage if a new TokenizedMessage was created. If the info occurred more than once for that SubjectKey, a counter will indicate the number of time it did occurred.
- L113 _public function_ `static FLiveLinkLog* GetInstance()`
- L117 _public prototype_ `virtual ~FLiveLinkLog() = default;` — Dtor
- L120 _public prototype_ `virtual TPair<int32, FTimespan> GetOccurrence(FName MessageID, FLiveLinkSubjectKey SubjectKey) const = 0;` — Get the number of time the message with the MessageID and SubjectKey occurred.
- L123 _public prototype_ `virtual TPair<int32, FTimespan> GetSelectedOccurrence() const = 0;` — Get the number of time the selected message occurred.
- L126 _public prototype_ `virtual void GetLogCount(int32& OutErrorCount, int32& OutWarningCount, int32& OutInfoCount) const = 0;` — Get the total number of error, warning and info messages that occurred.
- L130 _private function_ `template<typename... ArgsType> static void Log_Internal(EMessageSeverity::Type Severity, FName MessageID, const FLiveLinkSubjectKey& SubjectKey, UE::Core::TCheckedFormatString<FString::FmtCharType, ArgsType...> Format, ArgsType... Args)`
- L145 _private function_ `template<typename... ArgsType> static TSharedPtr<FTokenizedMessage> CreateTokenizedMessage_Internal(EMessageSeverity::Type Severity, FName MessageID, const FLiveLinkSubjectKey& SubjectKey, UE::Core::TCheckedFormatString<FString::FmtCharType, ArgsType...> Format, ArgsType... Args)`
- L161 _protected prototype_ `virtual void LogMessage(EMessageSeverity::Type Severity, FName MessageID, const FLiveLinkSubjectKey& SubjectKey, FString&& Message) = 0;`
- L162 _protected prototype_ `virtual TSharedPtr<FTokenizedMessage> CreateTokenizedMessage(EMessageSeverity::Type Severity, FName MessageID, const FLiveLinkSubjectKey& SubjectKey, FString&& Message) = 0;`
- L166 _protected member_ `static TUniquePtr<FLiveLinkLog> Instance;` — The instance that will manage the logging

#### Free symbols / members of external scopes

- L20 _macro_ `#define ENABLE_LIVELINK_LOGGING (!NO_LOGGING && !UE_BUILD_TEST)`

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkPresetTypes.h` (Public)


#### struct `FLiveLinkSourcePreset`  
`struct FLiveLinkSourcePreset`  
_L18-31_
- reflection: `USTRUCT()`
- L23 _public member_ `FGuid Guid;` — `UPROPERTY(VisibleAnywhere, Category="LiveLinkSourcePresets")`
- L26 _public member_ `TObjectPtr<ULiveLinkSourceSettings> Settings = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "LiveLinkSourcePresets", Instanced)`
- L30 _public member_ `FText SourceType;` — `UPROPERTY(VisibleAnywhere, Category = "LiveLinkSourcePresets")` — The SourceType when the source was saved to a Preset.

#### struct `FLiveLinkSubjectPreset`  
`struct FLiveLinkSubjectPreset`  
_L35-53_
- reflection: `USTRUCT()`
- L40 _public member_ `FLiveLinkSubjectKey Key;` — `UPROPERTY(VisibleAnywhere, Category = "LiveLinkSubjectPresets")`
- L43 _public member_ `TSubclassOf<ULiveLinkRole> Role;` — `UPROPERTY(VisibleAnywhere, Category = "LiveLinkSubjectPresets")`
- L46 _public member_ `TObjectPtr<ULiveLinkSubjectSettings> Settings = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "LiveLinkSubjectPresets", Instanced)`
- L49 _public member_ `TObjectPtr<ULiveLinkVirtualSubject> VirtualSubject = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "LiveLinkSubjectPresets", Instanced)`
- L52 _public member_ `bool bEnabled = false;` — `UPROPERTY(VisibleAnywhere, Category = "LiveLinkSubjectPresets")`

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkRefSkeleton.h` (Public)


#### struct `FLiveLinkRefSkeleton`  
`FLiveLinkRefSkeleton`  
_L13-38_
- reflection: `UE_DEPRECATED(4.23, "FLiveLinkRefSkeleton is no longer used, please use LiveLink animation role instead.")`
- L18 _public function_ `void SetBoneNames(const TArray<FName>& InBoneNames)` — Set the bone names for this skeleton
- L21 _public function_ `const TArray<FName>& GetBoneNames() const` — Get the bone names for this skeleton
- L24 _public function_ `void SetBoneParents(const TArray<int32> InBoneParents)` — Set the parent bones for this skeleton (Array of indices to parent)
- L27 _public function_ `const TArray<int32>& GetBoneParents() const` — Get skeleton's parent bones array
- L33 _public member_ `TArray<FName> BoneNames;` — `UPROPERTY()` — Names of each bone in the skeleton
- L37 _public member_ `TArray<int32> BoneParents;` — `UPROPERTY()` — Parent Indices: For each bone it specifies the index of its parent

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkRole.h` (Public)


#### class `ULiveLinkRole`  
`class ULiveLinkRole : public UObject`  
_L17-31_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Basic object to extend the meaning of incoming live link frames.
- L22 _public prototype_ `virtual UScriptStruct* GetStaticDataStruct() const PURE_VIRTUAL(ULiveLinkRole::GetStaticDataStruct, return nullptr;);`
- L23 _public prototype_ `virtual UScriptStruct* GetFrameDataStruct() const PURE_VIRTUAL(ULiveLinkRole::GetFrameDataStruct, return nullptr;);`
- L24 _public prototype_ `virtual UScriptStruct* GetBlueprintDataStruct() const PURE_VIRTUAL(ULiveLinkRole::GetBlueprintDataStruct, return nullptr;);`
- L26 _public prototype_ `virtual bool InitializeBlueprintData(const FLiveLinkSubjectFrameData& InSourceData, FLiveLinkBlueprintDataStruct& OutBlueprintData) const PURE_VIRTUAL(ULiveLinkRole::InitializeBlueprintData, return false;);`
- L28 _public prototype_ `virtual FText GetDisplayName() const;`
- L29 _public function_ `virtual bool IsStaticDataValid(const FLiveLinkStaticDataStruct& InStaticData, bool& bOutShouldLogWarning) const`
- L30 _public function_ `virtual bool IsFrameDataValid(const FLiveLinkStaticDataStruct& InStaticData, const FLiveLinkFrameDataStruct& InFrameData, bool& bOutShouldLogWarning) const`

#### struct `FLiveLinkSubjectRepresentation`  
`struct FLiveLinkSubjectRepresentation`  
_L35-51_
- reflection: `USTRUCT(BlueprintType)`
- L39 _public prototype_ `FLiveLinkSubjectRepresentation() = default;`
- L40 _public function_ `FLiveLinkSubjectRepresentation(const FLiveLinkSubjectName& InSubject, const TSubclassOf<ULiveLinkRole>& InRole) : Subject(InSubject), Role(InRole)`
- L45 _public member_ `FLiveLinkSubjectName Subject;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Live Link")`
- L48 _public member_ `TSubclassOf<ULiveLinkRole> Role;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Live Link")`
- L50 _public function_ `bool operator==(const FLiveLinkSubjectRepresentation& Other) const`

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkRoleTrait.h` (Public)


#### class `FLiveLinkRoleTrait`  
`class FLiveLinkRoleTrait`  
_L24-54_
- L28 _public prototype_ `static TArray<TSubclassOf<ULiveLinkRole>> GetRoles();` — Get the list of all the LiveLinkRole.
- L31 _public prototype_ `static TArray<TSubclassOf<ULiveLinkFrameInterpolationProcessor>> GetFrameInterpolationProcessorClasses(TSubclassOf<ULiveLinkRole> Role);` — Get the list of all the Frame Interpolation Processor for the Role.
- L34 _public prototype_ `static TArray<TSubclassOf<ULiveLinkFramePreProcessor>> GetFramePreProcessorClasses(TSubclassOf<ULiveLinkRole> Role);` — Get the list of all the Frame Pre Processor for the Role.
- L37 _public prototype_ `static TArray<TSubclassOf<ULiveLinkFrameTranslator>> GetFrameTranslatorClassesTo(TSubclassOf<ULiveLinkRole> Role);` — Get the list of all the Frame Translator to convert into a Role.
- L40 _public prototype_ `static TArray<TSubclassOf<ULiveLinkFrameTranslator>> GetFrameTranslatorClassesFrom(TSubclassOf<ULiveLinkRole> Role);` — Get the list of all the Frame Translator to convert from a Role.
- L43 _public prototype_ `static TArray<TSubclassOf<ULiveLinkVirtualSubject>> GetVirtualSubjectClasses();` — Get the list of all the Frame Virtual Subject for a Role.
- L44 _public prototype_ `static TArray<TSubclassOf<ULiveLinkVirtualSubject>> GetVirtualSubjectClasses(TSubclassOf<ULiveLinkRole> Role);`
- L47 _public prototype_ `static TSubclassOf<ULiveLinkController> GetControllerClass(TSubclassOf<ULiveLinkRole> Role);` — Get the Controller class for a Role.
- L50 _public prototype_ `static bool Validate(TSubclassOf<ULiveLinkRole> Role, const FLiveLinkStaticDataStruct& StaticData);` — Return true if the StaticData matches the Role static data type.
- L53 _public prototype_ `static bool Validate(TSubclassOf<ULiveLinkRole> Role, const FLiveLinkFrameDataStruct& FrameData);` — Return true if the FrameData matches the Role frame data type.

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkSourceFactory.h` (Public)


#### class `ULiveLinkSourceFactory`  
`class ULiveLinkSourceFactory : public UObject`  
_L27-74_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Base class of factory that creates Source. A source can be created in the editor via the Live Link panel or at runtime via a connection string.
- L33 _public prototype_ `virtual FText GetSourceDisplayName() const PURE_VIRTUAL( ULiveLinkSourceFactory::GetSourceDisplayName, return FText(); );` — The name of the menu item (of any EMenuType)
- L36 _public prototype_ `virtual FText GetSourceTooltip() const PURE_VIRTUAL(ULiveLinkSourceFactory::GetSourceTooltip, return FText(); );` — The tooltip of the menu item (of any EMenyType)
- L39 _public prototype_ `virtual TSharedPtr<SWidget> CreateSourceCreationPanel();` — `UE_DEPRECATED(4.23, "CreateSourceCreationPanel is deprecated. LiveLinkSourceFactory can now be used at runtime. This factory won't work until it's been updated.")`
- L42 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> OnSourceCreationPanelClosed(bool bMakeSource);` — `UE_DEPRECATED(4.23, "OnSourceCreationPanelClosed is deprecated. LiveLinkSourceFactory can now be used at runtime. The factory won't work until it's been updated.")`
- L55 _public function_ `virtual EMenuType GetMenuType() const` — How the factory should be visible in the LiveLink UI. If SubPanel, BuildCreationPanel should be implemented.
- L57 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnLiveLinkSourceCreated, TSharedPtr<ILiveLinkSource> , FString );`
- L64 _public prototype_ `virtual TSharedPtr<SWidget> BuildCreationPanel(FOnLiveLinkSourceCreated OnLiveLinkSourceCreated) const;` — Create a widget responsible for the creation of a Live Link source. @param OnLiveLinkSourceCreated Callback to call when the source has been created by the custom UI. @return The subpanel UI created by the factory.
- L67 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FString& ConnectionString) const PURE_VIRTUAL(ULiveLinkSourceFactory::CreateSource, return TSharedPtr<ILiveLinkSource>(); );` — Create a new source from a ConnectionString
- L70 _public prototype_ `virtual TSharedPtr<ILiveLinkSource> CreateSource(const FLiveLinkSourcePreset& SourcePreset);` — Override this method in child classes to allow creating a source with more context from the source preset.
- L73 _public function_ `virtual bool IsEnabled() const` — Whether this factory is enabled. Can be overriden to disable it in certain configurations.

#### enum `ULiveLinkSourceFactory::EMenuType`  
`enum class EMenuType`  
_L44-49_
- L46 _public enumerator_ `SubPanel` — In the UI, a sub menu will used
- L47 _public enumerator_ `MenuEntry` — In the UI, a button will be used
- L48 _public enumerator_ `Disabled` — In the UI, the button will be used but it will be disabled

#### Free symbols / members of external scopes

- L57 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnLiveLinkSourceCreated, TSharedPtr<ILiveLinkSource> , FString );`

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkSourceSettings.h` (Public)


#### class `ULiveLinkDefaultSourceSettings`  
`class ULiveLinkDefaultSourceSettings : public UObject`  
_L24-32_
- reflection: `UCLASS(config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Utility class that allows specifying default values for Source settings.
- L31 _public member_ `int32 DefaultSourceFrameBufferSize = 64;` — `UPROPERTY(config)` — Default number of frames that should be buffered by a LiveLink source.

#### enum `ELiveLinkSourceMode`  
`enum class ELiveLinkSourceMode : uint8`  
_L40-56_
- reflection: `UENUM()`
- L44 _public enumerator_ `Latest` — The source will the latest frame available to evaluate its subjects. This mode will not attempt any type of interpolation or time synchronization.
- L48 _public enumerator_ `EngineTime` — The source will use the engine's time to evaluate its subjects. This mode is most useful when smooth animation is desired.
- L55 _public enumerator_ `Timecode` — The source will use the engine's timecode to evaluate its subjects. This mode is most useful when sources need to be synchronized with multiple other external inputs (such as video or other time synchronized sources). Should not be used when the engine isn't setup with a Timecode provider.

#### struct `FLiveLinkSourceBufferManagementSettings`  
`struct FLiveLinkSourceBufferManagementSettings`  
_L60-142_
- reflection: `USTRUCT()`
- L66 _public member_ `bool bValidEngineTimeEnabled = false;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta=(InlineEditConditionToggle=true))` — Enabled the ValidEngineTime setting.
- L70 _public member_ `float ValidEngineTime = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta=(ForceUnits=s, ClampMin=0.5, EditCondition="bValidEngineTimeEnabled"))` — If the frame is older than ValidTime, remove it from the buffer list (in seconds).
- L74 _public member_ `float EngineTimeOffset = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta=(ForceUnits=s))` — When evaluating with time: how far back from current time should we read the buffer (in seconds)
- L78 _public member_ `double EngineTimeClockOffset = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", AdvancedDisplay, meta = (ForceUnits = s))` — Continuously updated clock offset estimator between source clock and engine clock (in seconds)
- L82 _public member_ `double SmoothEngineTimeOffset = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", AdvancedDisplay, meta = (ForceUnits = s))` — Continuously updated offset to achieve a smooth evaluation time (in seconds)
- L89 _public member_ `FFrameRate TimecodeFrameRate_DEPRECATED = {24, 1};` — `UPROPERTY()` — DEPRECATED: TimecodeFrameRate is now read from each individual subject from FQualifiedFrameTime. It is expected that all subjects under a source have the same and it will be readable in DetectedFrameRate variable
- L93 _public member_ `bool bGenerateSubFrame = false;` — `UPROPERTY(EditAnywhere, Category = "Settings")`
- L97 _public member_ `FFrameRate DetectedFrameRate = { 24, 1 };` — `UPROPERTY(VisibleAnywhere, Category = "Settings")` — FrameRate taken from one of the subjects. It's expected that all subjects have the same FrameRate
- L105 _public member_ `bool bUseTimecodeSmoothLatest = false;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — When evaluating with timecode, align source timecode using a continuous clock offset to do a smooth latest This means that even if engine Timecode and source Timecode are not aligned, the offset between both clocks will be tracked to keep them aligned. With an additionnal offset, 1.5 is a good number, you can evaluate your subject using the latest frame by keeping just enough margin to have a smooth playback and avoid starving.
- L113 _public member_ `FFrameRate SourceTimecodeFrameRate = { 24, 1 };` — `UPROPERTY(EditAnywhere, Category = "Settings", meta=(EditCondition="bGenerateSubFrame"))` — What is the source frame rate. When the refresh rate of the source is bigger than the timecode frame rate, LiveLink will try to generate sub frame numbers. @note The source should generate the sub frame numbers. Use this setting when the source is not able to do so. @note The generated sub frame numbers will not be saved by Sequencer.
- L117 _public member_ `bool bValidTimecodeFrameEnabled = false;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta=(InlineEditConditionToggle=true))` — If the frame timecode is older than ValidTimecodeFrame, remove it from the buffer list (in TimecodeFrameRate).
- L121 _public member_ `int32 ValidTimecodeFrame = 30;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta=(ClampMin=1, EditCondition="bValidTimecodeFrameEnabled"))` — If the frame timecode is older than ValidTimecodeFrame, remove it from the buffer list (in TimecodeFrameRate).
- L125 _public member_ `float TimecodeFrameOffset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — When evaluating with timecode: how far back from current timecode should we read the buffer (in TimecodeFrameRate).
- L129 _public member_ `double TimecodeClockOffset = 0.0;` — `UPROPERTY(VisibleAnywhere, Category = "Settings", AdvancedDisplay, meta = (ForceUnits = s))` — Continuously updated clock offset estimator between source timecode clock and engine timecode provider clock (in seconds)
- L133 _public member_ `int32 LatestOffset = 0;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — When evaluating with latest: how far back from latest frame should we read the buffer
- L137 _public member_ `int32 MaxNumberOfFrameToBuffered = 10;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta=(ClampMin=1, DisplayName="Buffer Size (Frames)"))` — Maximum number of frames to keep in memory.
- L141 _public member_ `bool bKeepAtLeastOneFrame = true;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Settings")` — When cleaning the buffer keep at least one frame, even if the frame doesn't matches the other options.

#### struct `FLiveLinkSourceDebugInfo`  
`struct FLiveLinkSourceDebugInfo`  
_L145-157_
- reflection: `USTRUCT()`
- L150 _public member_ `FLiveLinkSubjectName SubjectName;` — `UPROPERTY(VisibleAnywhere, Category = "Debug")`
- L153 _public member_ `int32 SnapshotIndex = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Debug")`
- L156 _public member_ `int32 NumberOfBufferAtSnapshot = 0;` — `UPROPERTY(VisibleAnywhere, Category = "Debug")`

#### class `ULiveLinkSourceSettings`  
`class ULiveLinkSourceSettings : public UObject`  
_L161-213_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base class for live link source settings (can be replaced by sources themselves)
- L166 _public prototype_ `ULiveLinkSourceSettings();`
- L173 _public member_ `ELiveLinkSourceMode Mode = ELiveLinkSourceMode::EngineTime;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta=(DisplayName="Evaluation Mode"))` — The the subject how to create the frame snapshot. @note A client may evaluate manually the subject in a different mode by using EvaluateFrameAtWorldTime or EvaluateFrameAtSceneTime.
- L177 _public member_ `FLiveLinkSourceBufferManagementSettings BufferSettings;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — How the frame buffers are managed.
- L181 _public member_ `bool bTransmitEvaluatedData = false;` — `UPROPERTY(EditAnywhere, Category = "Settings")` — Whether to rebroadcast evaluted data.
- L185 _public member_ `FString ConnectionString;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "Settings")` — Connection information that is needed by the factory to recreate the source from a preset.
- L189 _public member_ `TSubclassOf<ULiveLinkSourceFactory> Factory;` — `UPROPERTY()` — Factory used to create the source.
- L198 _public member_ `FLiveLinkSubjectName ParentSubject;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (DisplayName="Sync Subject"))` — Which subject should be used as a synchronization source for this source. If this is set, this source's subjects will only be rebroadcast when the parent subject receives data. Additionally this source's subjects' timecode will match the parent's subject received timecode. This can be useful for synchronizing a higher frequency source to a lower frequency one.
- L202 _public member_ `TArray<FLiveLinkSourceDebugInfo> SourceDebugInfos_DEPRECATED;` — `UPROPERTY()`
- L206 _public prototype_ `virtual FText GetSourceNameOverride(class ULiveLinkSubjectSettings* SubjectSettings, FText SourceType);` — Get the source name that should be displayed in the UI, based on the subject's source name override and the source type.
- L208 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L211 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`

#### struct `FLiveLinkTimeSynchronizationSettings`  
`FLiveLinkTimeSynchronizationSettings`  
_L218-235_
- reflection: `UE_DEPRECATED(4.23, "FLiveLinkTimeSynchronizationSettings is now unused.")`
- L222 _public function_ `FLiveLinkTimeSynchronizationSettings() : FrameRate(60, 1)`
- L230 _public member_ `FFrameRate FrameRate;` — `UPROPERTY(EditAnywhere, Category = Settings)` — The frame rate of the source. This should be the frame rate the source is "stamped" at, not necessarily the frame rate the source is sending. The source should supply this whenever possible.
- L234 _public member_ `FFrameNumber FrameOffset;` — `UPROPERTY(EditAnywhere, Category = Settings)` — When evaluating: how far back from current timecode should we read the buffer (in frame number)

#### struct `FLiveLinkInterpolationSettings`  
`FLiveLinkInterpolationSettings`  
_L240-255_
- reflection: `UE_DEPRECATED(4.23, "FLiveLinkInterpolationSettings is now unused.")`
- L244 _public function_ `FLiveLinkInterpolationSettings() : bUseInterpolation_DEPRECATED(false) , InterpolationOffset(0.5f)`
- L250 _public member_ `bool bUseInterpolation_DEPRECATED;` — `UPROPERTY()`
- L254 _public member_ `float InterpolationOffset;` — `UPROPERTY(EditAnywhere, Category = Settings)` — When interpolating: how far back from current time should we read the buffer (in seconds)

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkSubjectRemapper.h` (Public)


#### class `ILiveLinkSubjectRemapperWorker`  
`class ILiveLinkSubjectRemapperWorker`  
_L17-30_
- desc: Basic object to transform incoming static and frame data for a subject. @note Can be called from any thread.
- L20 _public prototype_ `virtual ~ILiveLinkSubjectRemapperWorker() = default;`
- L23 _public function_ `virtual void RemapStaticData(FLiveLinkStaticDataStruct& InOutStaticData)` — Remap the static data of a subject. Can be used to modify bone names and bone parents.
- L26 _public function_ `virtual void RemapFrameData(const FLiveLinkStaticDataStruct& InStaticData, FLiveLinkFrameDataStruct& InOutFrameData)` — Remap the frame data of a subject.
- L29 _public function_ `virtual bool IsRemapperCompatible(const FLiveLinkStaticDataStruct& InStaticData)` — Returns if the remapper is compatible with the static data.

#### class `ULiveLinkSubjectRemapper`  
`class ULiveLinkSubjectRemapper : public UObject`  
_L34-70_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Class used to remap livelink subjects without having to rely on animation blueprints.
- L39 _public typedef_ `using FWorkerSharedPtr = TSharedPtr<ILiveLinkSubjectRemapperWorker>;`
- L44 _public prototype_ `virtual FWorkerSharedPtr CreateWorker() PURE_VIRTUAL(ULiveLinkSubjectRemapper::CreateWorker, return FWorkerSharedPtr(););` — Create an instance of a ILiveLinkSubjectRemapperWorker that can be used outside of the game thread.
- L50 _public prototype_ `virtual FWorkerSharedPtr GetWorker() const PURE_VIRTUAL(ULiveLinkSubjectRemapper::GetWorker, return FWorkerSharedPtr(););` — Get the instance of ILiveLinkSubjectRemapperWorker that was created by the CreateWorker method. Returns an invalid pointer if no instance was created.
- L55 _public function_ `virtual void Initialize(const FLiveLinkSubjectKey& SubjectKey)` — Called to initialize the remapper with information from the subject that owns the remapper.
- L58 _public prototype_ `virtual TSubclassOf<ULiveLinkRole> GetSupportedRole() const PURE_VIRTUAL(ULiveLinkSubjectRemapper::GetSupportedRole, return TSubclassOf<ULiveLinkRole>(););` — Get what role is supported by this remapper.
- L61 _public prototype_ `virtual bool IsValidRemapper() const PURE_VIRTUAL(ULiveLinkSubjectRemapper::IsValid, return false;);` — Retuns whether the remapper can currently be used for remapping.
- L66 _public member_ `TMap<FName, FName> BoneNameMap;` — `UPROPERTY(EditAnywhere, Category="Remapper")` — Name mapping between source bone name and transformed bone name
- L69 _public member_ `bool bDirty = false;` — When this is true, livelink's buffered frames will be remapped and the subject's static data will be updated.

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkSubjectSettings.h` (Public)


#### class `ULiveLinkDefaultSubjectSettings`  
`class ULiveLinkDefaultSubjectSettings : public UObject`  
_L30-48_
- reflection: `UCLASS(config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Utility class that allows specifying default values for Subject settings.
- L37 _public member_ `bool bRebroadcastSubjectsByDefault = false;` — `UPROPERTY(config)` — Whether subjects should be rebroadcasted by default.
- L47 _private member_ `bool bAllowEditingRebroadcastProperty_DEPRECATED = true;` — `UE_DEPRECATED(5.6, "Not used anymore.")` — `UPROPERTY(config)` — Whether a user should be able to edit the bRebroadcastSubject property. Setting this to false in a target config will prevent a user from turning on or off the rebroadcast flag on a subject.

#### class `ULiveLinkSubjectSettings`  
`class ULiveLinkSubjectSettings : public UObject`  
_L53-134_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base class for live link subject settings
- L58 _public prototype_ `ULiveLinkSubjectSettings();`
- L61 _public function_ `virtual void Initialize(FLiveLinkSubjectKey InSubjectKey)` — Initialize the settings.
- L67 _public function_ `virtual FName GetRebroadcastName() const` — Get the name that should be used when the subject is rebroadcasted.
- L72 _public function_ `virtual FText GetDisplayName() const`
- L79 _public member_ `TArray<TObjectPtr<ULiveLinkFramePreProcessor>> PreProcessors;` — `UPROPERTY(EditAnywhere, Instanced, Category = "LiveLink", meta = (DisplayName = "Pre Processors"))` — List of available preprocessor the subject will use.
- L83 _public member_ `TObjectPtr<ULiveLinkFrameInterpolationProcessor> InterpolationProcessor;` — `UPROPERTY(EditAnywhere, Instanced, Category = "LiveLink", meta = (DisplayName = "Interpolation"))` — The interpolation processor the subject will use.
- L87 _public member_ `TArray<TObjectPtr<ULiveLinkFrameTranslator>> Translators;` — `UPROPERTY(EditAnywhere, Instanced, Category = "LiveLink", meta = (DisplayName = "Translators"))` — List of available translator the subject can use.
- L91 _public member_ `TObjectPtr<ULiveLinkSubjectRemapper> Remapper;` — `UPROPERTY(EditAnywhere, Instanced, Category = "LiveLink")` — Remapper used to modify incoming static and frame data for a subject.
- L94 _public member_ `TSubclassOf<ULiveLinkRole> Role;` — `UPROPERTY()`
- L98 _public member_ `FFrameRate FrameRate;` — `UPROPERTY(VisibleAnywhere, Category="LiveLink")` — Last FrameRate estimated by the subject. If in Timecode mode, this will come directly from the QualifiedFrameTime.
- L102 _public member_ `bool bRebroadcastSubject;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")` — If enabled, rebroadcast this subject
- L106 _public member_ `FName OriginalSourceName;` — `UPROPERTY()` — For sources created through LiveLinkHub, this contains the name of the original source for display purposes.
- L111 _public prototype_ `bool ValidateProcessors();` — Validate PreProcessors, Translators and Interpolation processors. Usually called after a property change event. Will revert a given change if it does not match the current subject role.
- L116 _public prototype_ `virtual void PreEditChange(FProperty* Property) override;`
- L117 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L124 _protected member_ `FLiveLinkSubjectKey Key;` — `UPROPERTY()` — Key of the subject that owns this setting.
- L128 _private member_ `TStrongObjectPtr<ULiveLinkSubjectRemapper> RemapperBeingReset;` — We need to keep track of the remapper when it's reset in order to restore the static data.
- L133 _private member_ `bool bAllowModifyingRebroadcast_DEPRECATED = true;` — `UE_DEPRECATED(5.6, "Not used anymore.")` — `UPROPERTY()` — Allows settings to dictate whether the rebroadcast flag is editable.

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkTypes.h` (Public)


#### struct `FLiveLinkSubjectName`  
`struct FLiveLinkSubjectName`  
_L39-72_
- reflection: `USTRUCT(BlueprintType)`
- L44 _public prototype_ `FLiveLinkSubjectName() = default;`
- L45 _public function_ `FLiveLinkSubjectName(FName InName) : Name(InName)`
- L46 _public function_ `FLiveLinkSubjectName(EName InName) : Name(InName)`
- L50 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Live Link")` — Name of the subject
- L52 _public function_ `bool IsNone() const`
- L53 _public function_ `FString ToString() const`
- L56 _public function_ `operator FName&()` — FName operators
- L57 _public function_ `operator const FName&() const`
- L59 _public function_ `bool operator==(const FLiveLinkSubjectName& Other) const`
- L60 _public function_ `bool operator==(const FName Other) const`

#### struct `FLiveLinkSubjectKey`  
`struct FLiveLinkSubjectKey`  
_L77-106_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure that identifies an individual subject
- L83 _public member_ `FGuid Source;` — `UPROPERTY(BlueprintReadOnly, Category="LiveLink")` — The guid for this subjects source
- L87 _public member_ `FLiveLinkSubjectName SubjectName;` — `UPROPERTY(BlueprintReadOnly, Category="LiveLink")` — The Name of this subject
- L89 _public prototype_ `FLiveLinkSubjectKey() = default;`
- L90 _public function_ `FLiveLinkSubjectKey(FGuid InSource, FName InSubjectName) : Source(InSource), SubjectName(InSubjectName)`
- L92 _public function_ `bool operator== (const FLiveLinkSubjectKey& Other) const`
- L93 _public function_ `bool operator!=(const FLiveLinkSubjectKey& Other) const`

#### struct `FLiveLinkWorldTime`  
`struct FLiveLinkWorldTime`  
_L110-168_
- reflection: `USTRUCT()`
- L116 _public function_ `FLiveLinkWorldTime() : Offset(0.0)`
- L122 _public function_ `FLiveLinkWorldTime(const double InTime) : Time(InTime)`
- L129 _public function_ `explicit FLiveLinkWorldTime(const double InTime, const double InOffset) : Time(InTime) , Offset(InOffset)`
- L136 _public function_ `double GetSourceTime() const` — Returns the raw time received from the sender
- L142 _public function_ `double GetOffset() const` — Returns offset between source time and engine time
- L148 _public function_ `double GetOffsettedTime() const` — Returns the time + the adjustment between source clock and engine clock to have a time comparable to engine one
- L154 _public function_ `void SetClockOffset(double ClockOffset)` — Adjust clock offset with a better evaluation of the difference between source clock and engine clock
- L162 _private member_ `double Time;` — `UPROPERTY(meta = (IgnoreForMemberInitializationTest))` — SourceTime for this frame. Used during interpolation and to compute a running clock offset
- L167 _private member_ `double Offset;` — `UPROPERTY()` — Value calculated on create to represent the different between the source time and client time Can also be updated afterwards if a better continuous offset is calculated

#### struct `FLiveLinkTime`  
`struct FLiveLinkTime`  
_L172-193_
- reflection: `USTRUCT(BlueprintType)`
- L177 _public member_ `double WorldTime;` — `UPROPERTY(EditAnywhere, Category="LiveLink")`
- L180 _public member_ `FQualifiedFrameTime SceneTime;` — `UPROPERTY(EditAnywhere, Category="LiveLink")`
- L182 _public function_ `FLiveLinkTime() : WorldTime(0.0) , SceneTime()`
- L188 _public function_ `FLiveLinkTime(double InWorldTime, const FQualifiedFrameTime& InSceneTime) : WorldTime(InWorldTime) , SceneTime(InSceneTime)`

#### struct `FLiveLinkMetaData`  
`struct FLiveLinkMetaData`  
_L197-206_
- reflection: `USTRUCT(BlueprintType)`
- L202 _public member_ `TMap<FName, FString> StringMetaData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LiveLink")`
- L205 _public member_ `FQualifiedFrameTime SceneTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LiveLink")`

#### struct `FLiveLinkBaseFrameData`  
`struct FLiveLinkBaseFrameData`  
_L216-247_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base data structure for each frame coming in for a subject @note subclass can't contains reference to UObject
- L222 _public member_ `FLiveLinkWorldTime WorldTime;` — `UPROPERTY(VisibleAnywhere, Category="LiveLink")` — Time in seconds the frame was created.
- L226 _public member_ `FLiveLinkMetaData MetaData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LiveLink")` — Frame's metadata.
- L230 _public member_ `TArray<float> PropertyValues;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LiveLink")` — Values of the properties defined in the static structure. Use FLiveLinkBaseStaticData.FindPropertyValue to evaluate.
- L233 _public member_ `FLiveLinkTime ArrivalTime;` — Time at which this frame was received - populated once inside pipeline
- L237 _public member_ `int32 FrameId = INDEX_NONE;` — `UPROPERTY()` — Frame identifier for tracking sent frames and detecting dropped frames when set
- L240 _public function_ `FLiveLinkTime GetLiveLinkTime() const` — Return the LiveLinkTime struct constructed from this frame data.
- L245 _public member_ `TMap<FName, double> Timestamps;` — `UPROPERTY(VisibleAnywhere, Category = "LiveLink")` — This frame timestamps used for measuring latency

#### struct `FLiveLinkBaseStaticData`  
`struct FLiveLinkBaseStaticData`  
_L256-278_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base static data structure for a subject Use to store information that is common to every frame @note subclass can't contains reference to UObject
- L262 _public member_ `TArray<FName> PropertyNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LiveLink")` — Names for each curve values that will be sent for each frame
- L265 _public function_ `bool FindPropertyValue(const FLiveLinkBaseFrameData& FrameData, const FName PropertyName, float& OutValue) const`

#### struct `FLiveLinkBaseBlueprintData`  
`struct FLiveLinkBaseBlueprintData`  
_L286-293_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base blueprint data structure for a subject frame Can be used to do blueprint facilitator per role
- L290 _public prototype_ `FLiveLinkBaseBlueprintData() = default;`
- L292 _public prototype_ `virtual ~FLiveLinkBaseBlueprintData() = default;`

#### class `FLiveLinkBaseDataStruct`  
`template<typename BaseType> class FLiveLinkBaseDataStruct`  
_L301-510_
- desc: Wrapper around FStructOnScope to handle FLiveLinkBaseFrameData Can safely cast to the specific outer type
- L304 _public prototype_ `FLiveLinkBaseDataStruct() = default;`
- L307 _public function_ `FLiveLinkBaseDataStruct(const UScriptStruct* InType, BaseType* InData) : WrappedStruct(InType, reinterpret_cast<uint8*>(InData))` — Build the wrapper struct using external data location
- L313 _public function_ `FLiveLinkBaseDataStruct(const UScriptStruct* InType) : WrappedStruct(InType)` — Build the wrapper struct for a specific type but without any data to initialize it with
- L318 _public function_ `FLiveLinkBaseDataStruct(FLiveLinkBaseDataStruct&& InOther) : WrappedStruct(MoveTemp(InOther.WrappedStruct))`
- L324 _public function_ `bool IsValid() const`
- L329 _public function_ `void Reset()`
- L334 _public function_ `BaseType* GetBaseData()`
- L339 _public function_ `const BaseType* GetBaseData() const`
- L344 _public function_ `const UScriptStruct* GetStruct() const`
- L354 _public function_ `template<typename DataType> void InitializeWith(const DataType* InData)` — Initialize ourselves with another data struct directly. @note: We could have been initialized before so if it's the case, previous memory will be destroyed.
- L364 _public function_ `void InitializeWith(const UScriptStruct* InOtherStruct, const BaseType* InData)` — Initialize ourselves with another struct. @note: We could have been initialized before so if it's the case, previous memory will be destroyed.
- L380 _public function_ `void InitializeWith(const FLiveLinkBaseDataStruct& InOther)` — Initialize ourselves with another data struct. @note: We could have been initialized before so if it's the case, previous memory will be destroyed.
- L390 _public function_ `BaseType* CloneData() const`
- L403 _public function_ `template<typename Type> Type* Cast()`
- L409 _public function_ `template<typename Type> const Type* Cast() const`
- L414 _public function_ `FLiveLinkBaseDataStruct& operator=(FLiveLinkBaseDataStruct&& InOther)`
- L420 _public function_ `bool operator==(const FLiveLinkBaseDataStruct& Other) const`
- L433 _public function_ `bool operator!=(const FLiveLinkBaseDataStruct& Other) const`
- L509 _protected member_ `FStructOnScope WrappedStruct;`

#### struct `FLiveLinkBaseDataStruct::FCastImpl`  
`template<typename Type> struct FCastImpl`  
_L477-506_
- L479 _public function_ `static Type* Cast(const UScriptStruct* ScriptStruct, BaseType* BaseData)`
- L495 _public function_ `static const Type* ConstCast(const UScriptStruct* ScriptStruct, const BaseType* BaseData)`

#### struct `FLiveLinkSubjectFrameData`  
`struct FLiveLinkSubjectFrameData`  
_L526-531_
- desc: Wrapper around static and dynamic data to be used when fetching a subject complete data
- L529 _public member_ `FLiveLinkStaticDataStruct StaticData;`
- L530 _public member_ `FLiveLinkFrameDataStruct FrameData;`

#### struct `FLiveLinkFrameRate`  
`FLiveLinkFrameRate : public FFrameRate`  
_L538-563_
- reflection: `UE_DEPRECATED(4.20, "FLiveLinkFrameRate is no longer used, please use FFrameRate from TimeManagement instead.")`
- inherits: `FFrameRate`
- L544 _public function_ `bool IsValid() const`
- L549 _public member_ `static const FLiveLinkFrameRate FPS_15;`
- L550 _public member_ `static const FLiveLinkFrameRate FPS_24;`
- L551 _public member_ `static const FLiveLinkFrameRate FPS_25;`
- L552 _public member_ `static const FLiveLinkFrameRate FPS_30;`
- L553 _public member_ `static const FLiveLinkFrameRate FPS_48;`
- L554 _public member_ `static const FLiveLinkFrameRate FPS_50;`
- L555 _public member_ `static const FLiveLinkFrameRate FPS_60;`
- L556 _public member_ `static const FLiveLinkFrameRate FPS_100;`
- L557 _public member_ `static const FLiveLinkFrameRate FPS_120;`
- L558 _public member_ `static const FLiveLinkFrameRate FPS_240;`
- L560 _public member_ `static const FLiveLinkFrameRate NTSC_24;`
- L561 _public member_ `static const FLiveLinkFrameRate NTSC_30;`
- L562 _public member_ `static const FLiveLinkFrameRate NTSC_60;`

#### struct `FLiveLinkTimeCode_Base_DEPRECATED`  
`struct FLiveLinkTimeCode_Base_DEPRECATED`  
_L566-589_
- reflection: `USTRUCT()`
- L572 _public member_ `int32 Seconds;` — `UPROPERTY()` — Integer Seconds since Epoch
- L576 _public member_ `int32 Frames;` — `UPROPERTY()` — Integer Frames since last second
- L580 _public member_ `FLiveLinkFrameRate FrameRate;` — `UPROPERTY()` — Value calculated on create to represent the different between the source time and client time
- L582 _public function_ `FLiveLinkTimeCode_Base_DEPRECATED() : Seconds(0), Frames(0), FrameRate()`
- L586 _public function_ `FLiveLinkTimeCode_Base_DEPRECATED(const int32 InSeconds, const int32 InFrames, const FLiveLinkFrameRate& InFrameRate) : Seconds(InSeconds), Frames(InFrames), FrameRate(InFrameRate)`

#### struct `FLiveLinkTimeCode`  
`FLiveLinkTimeCode : public FLiveLinkTimeCode_Base_DEPRECATED`  
_L595-620_
- reflection: `UE_DEPRECATED(4.20, "FLiveLinkTimeCode is no longer used, please use FQualifiedFrameTime from TimeManagement instead.")`
- inherits: `FLiveLinkTimeCode_Base_DEPRECATED`
- L602 _public function_ `operator FQualifiedFrameTime() const` — Implicit conversion to FTimecode
- L609 _public function_ `FLiveLinkTimeCode& operator=(const FQualifiedFrameTime& InFrameTime)`

#### struct `FLiveLinkCurveElement`  
`FLiveLinkCurveElement`  
_L626-646_
- reflection: `UE_DEPRECATED(4.23, "FLiveLinkFrameData is no longer used, please use the LiveLink roles instead.")`
- L631 _public function_ `FLiveLinkCurveElement() : CurveName(NAME_None) , CurveValue(0.f)`
- L636 _public function_ `FLiveLinkCurveElement(FName InCurveName, float InCurveValue) : CurveName(InCurveName) , CurveValue(InCurveValue)`
- L642 _public member_ `FName CurveName;` — `UPROPERTY()`
- L645 _public member_ `float CurveValue;` — `UPROPERTY()`

#### struct `FLiveLinkFrameData`  
`FLiveLinkFrameData`  
_L653-669_
- reflection: `UE_DEPRECATED(4.23, "FLiveLinkFrameData is no longer used, please use the LiveLink animation role instead.")`
- L658 _public member_ `TArray<FTransform> Transforms;` — `UPROPERTY()`
- L661 _public member_ `TArray<FLiveLinkCurveElement> CurveElements;` — `UPROPERTY()`
- L664 _public member_ `FLiveLinkWorldTime WorldTime;` — `UPROPERTY()`
- L667 _public member_ `FLiveLinkMetaData MetaData;` — `UPROPERTY()`

#### struct `FOptionalCurveElement`  
`FOptionalCurveElement`  
_L674-715_
- reflection: `UE_DEPRECATED(4.23, "FOptionalCurveElement is no longer used, please use FLiveLinkBaseStaticData::PropertyNames and FLiveLinkBaseFrameData::PropertyValues instead.")`
- L677 _public member_ `float Value;` — Curve Value
- L679 _public member_ `bool bValid;` — Whether this value is set or not
- L681 _public function_ `FOptionalCurveElement(float InValue) : Value(InValue) , bValid(true)`
- L686 _public function_ `FOptionalCurveElement() : Value(0.f) , bValid(false)`
- L691 _public function_ `bool IsValid() const`
- L696 _public function_ `void SetValue(float InValue)`
- L702 _public function_ `FOptionalCurveElement& operator=(const FLiveLinkCurveElement& InCurveElement)`

#### struct `FLiveLinkCurveIntegrationData`  
`FLiveLinkCurveIntegrationData`  
_L721-730_
- reflection: `UE_DEPRECATED(4.23, "FLiveLinkCurveIntegrationData is no longer used, please use FLiveLinkBaseStaticData::PropertyNames and FLiveLinkBaseFrameData::PropertyValues instead.")`
- L726 _public member_ `int32 NumNewCurves;` — Number of new curves that need to be added to existing frames
- L729 _public member_ `TArray<FOptionalCurveElement> CurveValues;` — Built curve buffer for current frame in existing curve key format

#### struct `FLiveLinkCurveKey`  
`FLiveLinkCurveKey`  
_L735-740_
- reflection: `UE_DEPRECATED(4.23, "FLiveLinkCurveKey is no longer used, please use FLiveLinkBaseStaticData::PropertyNames and FLiveLinkBaseFrameData::PropertyValues instead.")`
- L737 _public member_ `TArray<FName> CurveNames;`
- L739 _public prototype_ `FLiveLinkCurveIntegrationData UpdateCurveKey(const TArray<FLiveLinkCurveElement>& CurveElements);`

#### struct `FLiveLinkSubjectFrame`  
`FLiveLinkSubjectFrame`  
_L746-765_
- reflection: `UE_DEPRECATED(4.23, "FLiveLinkSubjectFrame is no longer used, please use the LiveLink animation role instead.")`
- L749 _public member_ `FLiveLinkRefSkeleton RefSkeleton;` — Ref Skeleton for transforms
- L752 _public member_ `FGuid RefSkeletonGuid;` — Guid for ref skeleton so we can track modifications
- L755 _public member_ `FLiveLinkCurveKey CurveKeyData;` — Key for storing curve data (Names)
- L758 _public member_ `TArray<FTransform> Transforms;` — Transforms for this frame
- L761 _public member_ `TArray<FOptionalCurveElement> Curves;` — Curve data for this frame
- L764 _public member_ `FLiveLinkMetaData MetaData;` — Metadata for this frame

#### struct `FLiveLinkFrame`  
`FLiveLinkFrame`  
_L771-793_
- reflection: `UE_DEPRECATED(4.23, "FLiveLinkFrame is no longer used, please use the LiveLink animation role instead.")`
- L773 _public member_ `TArray<FTransform> Transforms;`
- L774 _public member_ `TArray<FOptionalCurveElement> Curves;`
- L776 _public member_ `FLiveLinkMetaData MetaData;`
- L778 _public member_ `FLiveLinkWorldTime WorldTime;`
- L780 _public function_ `void ExtendCurveData(int32 ExtraCurves)`

#### Free symbols / members of external scopes

- L62 _function_ `friend FArchive& operator<<(FArchive& Ar, FLiveLinkSubjectName& InSubjectName)`
- L68 _function_ `friend inline uint32 GetTypeHash(const FLiveLinkSubjectName& Value)`
- L95 _function_ `friend FArchive& operator<<(FArchive& Ar, FLiveLinkSubjectKey& InSubjectKey)`
- L102 _function_ `friend uint32 GetTypeHash(const FLiveLinkSubjectKey& SubjectKey)`
- L209 _typedef_ `using FLiveLinkFrameIdentifier = int32;` — Identifier assigned to each incoming frame once in the pipeline
- L438 _function_ `friend FArchive& operator<<(FArchive& Ar, FLiveLinkBaseDataStruct& InStruct)`
- L514 _typedef_ `using FLiveLinkStaticDataStruct = FLiveLinkBaseDataStruct<FLiveLinkBaseStaticData>;` — Specialization of our wrapped struct for FLiveLinkBaseStaticData
- L517 _typedef_ `using FLiveLinkFrameDataStruct = FLiveLinkBaseDataStruct<FLiveLinkBaseFrameData>;` — Specialization of our wrapped struct for FLiveLinkBaseFrameData
- L520 _typedef_ `using FLiveLinkBlueprintDataStruct = FLiveLinkBaseDataStruct<FLiveLinkBaseBlueprintData>;` — Specialization of our wrapped struct for FLiveLinkBaseBlueprintData
- L708 _function_ `friend FArchive& operator<<(FArchive& Ar, FOptionalCurveElement& InElement)`
- L785 _function_ `friend FArchive& operator<<(FArchive& Ar, FLiveLinkFrame& InFrame)`
- L799 _namespace_ `namespace UE`
- L799 _namespace_ `namespace LiveLink` (scope `UE`)
- L799 _namespace_ `namespace SourceTypes` (scope `UE::LiveLink`)
- L802 _variable_ `inline constexpr const TCHAR* SequencerSourcePrefix = TEXT("Seq` (scope `UE::LiveLink::SourceTypes`) — Identifier prefix for sequencer-driven Live Link sources

### `Source/Runtime/LiveLinkInterface/Public/LiveLinkVirtualSubject.h` (Public)


#### class `ULiveLinkVirtualSubject`  
`class ULiveLinkVirtualSubject : public UObject, public ILiveLinkSubject`  
_L28-171_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject,ILiveLinkSubject`
- desc: A Virtual subject is made up of one or more real subjects from a source
- L34 _public prototype_ `virtual void Initialize(FLiveLinkSubjectKey SubjectKey, TSubclassOf<ULiveLinkRole> Role, ILiveLinkClient* LiveLinkClient) override;`
- L35 _public prototype_ `virtual void Update() override;`
- L36 _public prototype_ `virtual bool EvaluateFrame(TSubclassOf<ULiveLinkRole> InDesiredRole, FLiveLinkSubjectFrameData& OutFrame) override;`
- L37 _public prototype_ `virtual void ClearFrames() override;`
- L38 _public function_ `virtual FLiveLinkSubjectKey GetSubjectKey() const override`
- L39 _public function_ `virtual TSubclassOf<ULiveLinkRole> GetRole() const override`
- L40 _public prototype_ `virtual bool HasValidFrameSnapshot() const override;`
- L41 _public function_ `virtual FLiveLinkStaticDataStruct& GetStaticData(bool bGetOverrideData=true) override`
- L42 _public function_ `virtual const FLiveLinkStaticDataStruct& GetStaticData() const override`
- L43 _public function_ `virtual const TArray<ULiveLinkFrameTranslator::FWorkerSharedPtr> GetFrameTranslators() const override`
- L44 _public function_ `virtual const ULiveLinkSubjectRemapper::FWorkerSharedPtr GetFrameRemapper() const override`
- L45 _public prototype_ `virtual TArray<FLiveLinkTime> GetFrameTimes() const override;`
- L46 _public function_ `virtual bool IsRebroadcasted() const override`
- L47 _public function_ `virtual bool HasStaticDataBeenRebroadcasted() const override`
- L48 _public function_ `virtual void SetStaticDataAsRebroadcasted(const bool bInSent) override`
- L49 _public prototype_ `virtual bool IsPaused() const override;`
- L50 _public prototype_ `virtual void PauseSubject() override;`
- L51 _public prototype_ `virtual void UnpauseSubject() override;`
- L54 _protected function_ `virtual const FLiveLinkSubjectFrameData& GetFrameSnapshot() const override`
- L58 _protected prototype_ `bool HasValidStaticData() const;` — Whether snapshot has valid static data
- L61 _protected prototype_ `bool HasValidFrameData() const;` — Whether snapshot has valid frame data
- L66 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L70 _public function_ `ILiveLinkClient* GetClient() const`
- L73 _public function_ `const TArray<FLiveLinkSubjectName>& GetSubjects() const` — Returns the live subjects associated with this virtual one
- L76 _public function_ `const TArray<ULiveLinkFrameTranslator*>& GetTranslators() const` — Returns the translators assigned to this virtual subject
- L79 _public function_ `const FLiveLinkFrameDataStruct& GetFrameData() const` — Returns the current frame data of this virtual subject
- L82 _public prototype_ `virtual bool DependsOnSubject(FName SubjectName) const;` — Returns true whether this virtual subject depends on the Subject named SubjectName
- L85 _public function_ `virtual FText GetDisplayName() const` — Get display name for this subject.
- L91 _public function_ `virtual FName GetRebroadcastName() const` — Get the name that should be used when the subject is rebroadcast.
- L97 _public prototype_ `virtual ELiveLinkSubjectState GetState() const;` — Get the state of the virtual subject.
- L102 _public member_ `FLiveLinkSubjectName SyncSubject;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")` — If set, the virtual subject will only update and transmit data when the sync subject receives new data.
- L107 _protected prototype_ `void UpdateTranslatorsForThisFrame();` — Updates the list of translators valid for this frame
- L110 _protected prototype_ `void UpdateStaticDataSnapshot(FLiveLinkStaticDataStruct&& NewStaticData);` — Updates our snapshot's static data
- L113 _protected prototype_ `void UpdateFrameDataSnapshot(FLiveLinkFrameDataStruct&& NewFrameData);` — Updates our snapshot's frame data
- L116 _protected prototype_ `void InvalidateStaticData();` — Invalidates our snapshot's static data
- L119 _protected prototype_ `void InvalidateFrameData();` — Invalidates our snapshot's frame data
- L124 _protected member_ `TSubclassOf<ULiveLinkRole> Role;` — `UPROPERTY()` — The role the subject was build with.
- L128 _protected member_ `TArray<FLiveLinkSubjectName> Subjects;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")` — Names of the real subjects to combine into a virtual subject
- L132 _protected member_ `TArray<TObjectPtr<ULiveLinkFrameTranslator>> FrameTranslators;` — `UPROPERTY(EditAnywhere, Instanced, Category = "LiveLink", meta=(DisplayName="Translators"))` — List of available translator the subject can use.
- L136 _protected member_ `bool bRebroadcastSubject = false;` — `UPROPERTY(EditAnywhere, Category = "LiveLink")` — If enabled, rebroadcast this subject
- L139 _protected member_ `ILiveLinkClient* LiveLinkClient;` — LiveLinkClient to get access to subjects
- L142 _protected member_ `FLiveLinkSubjectFrameData FrameSnapshot;` — `UE_DEPRECATED(4.27, "VirtualSubject FrameSnapshot is now private to have thread safe accesses. Please use UpdateStaticDataSnapshot or UpdateFrameDataSnapshot to update its value")`
- L145 _protected member_ `FLiveLinkSubjectKey SubjectKey;` — Name of the subject
- L148 _protected member_ `bool bHasStaticDataBeenRebroadcast = false;` — If true, static data has been sent for this rebroadcast
- L156 _protected member_ `mutable FCriticalSection SnapshotAccessCriticalSection;` — Lock to protect the FrameSnapshot. VirtualSubjects can be manipulated from anywhere versus LiveSubjects that have an access controlled in the Source Collection. Evaluating subjects is AnyThread so we can be evaluated while our snapshot is getting set
- L160 _private prototype_ `bool ValidateTranslators();` — Validate that the translators on this subject match its role.
- L163 _private member_ `TArray<ULiveLinkFrameTranslator::FWorkerSharedPtr> CurrentFrameTranslators;`
- L165 _private member_ `ULiveLinkSubjectRemapper::FWorkerSharedPtr CurrentSubjectRemapper;` — Current subject remapper.
- L168 _private member_ `FLiveLinkSubjectFrameData CurrentFrameSnapshot;` — Last evaluated frame for this subject.
- L170 _private member_ `std::atomic<bool> bPaused = false;`

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkAnimationBlueprintStructs.h` (Public)


#### struct `FSubjectMetadata`  
`struct FSubjectMetadata`  
_L24-36_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public member_ `TMap<FName, FString> StringMetadata;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LiveLink")`
- L32 _public member_ `FTimecode SceneTimecode;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LiveLink")`
- L35 _public member_ `FFrameRate SceneFramerate;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LiveLink")`

#### struct `FCachedSubjectFrame`  
`struct FCachedSubjectFrame`  
_L39-90_
- reflection: `USTRUCT()`
- L43 _public prototype_ `FCachedSubjectFrame();`
- L45 _public prototype_ `FCachedSubjectFrame(const FLiveLinkSkeletonStaticData* InStaticData, const FLiveLinkAnimationFrameData* InAnimData);`
- L47 _public prototype_ `virtual ~FCachedSubjectFrame() = default;`
- L49 _public prototype_ `void SetCurvesFromCache(TMap<FName, float>& OutCurves) const;`
- L51 _public prototype_ `bool GetCurveValueByName(FName InCurveName, float& OutCurveValue) const;`
- L53 _public prototype_ `void GetSubjectMetadata(FSubjectMetadata& OutSubjectMetadata) const;`
- L55 _public prototype_ `int32 GetNumberOfTransforms() const;`
- L57 _public prototype_ `void GetTransformNames(TArray<FName>& OutTransformNames) const;`
- L59 _public prototype_ `void GetTransformName(const int32 InTransformIndex, FName& OutName) const;`
- L61 _public prototype_ `int32 GetTransformIndexFromName(FName InTransformName) const;`
- L63 _public prototype_ `int32 GetParentTransformIndex(const int32 InTransformIndex) const;`
- L65 _public prototype_ `void GetChildTransformIndices(const int32 InTransformIndex, TArray<int32>& OutChildIndices) const;`
- L67 _public prototype_ `void GetTransformParentSpace(const int32 InTransformIndex, FTransform& OutTransform) const;`
- L69 _public prototype_ `void GetTransformRootSpace(const int32 InTransformIndex, FTransform& OutTransform) const;`
- L71 _public prototype_ `int32 GetRootIndex() const;`
- L73 _public function_ `const FLiveLinkSkeletonStaticData& GetSourceSkeletonData() const`
- L75 _public function_ `const FLiveLinkAnimationFrameData& GetSourceAnimationFrameData() const`
- L78 _private member_ `FLiveLinkSkeletonStaticData SourceSkeletonData;`
- L79 _private member_ `FLiveLinkAnimationFrameData SourceAnimationFrameData;`
- L82 _private member_ `mutable TArray<TPair<bool, FTransform>> CachedRootSpaceTransforms;` — Cache. Does not affect the underlying frame data
- L83 _private member_ `mutable TArray<TPair<bool, TArray<int32>>> CachedChildTransformIndices;`
- L84 _private member_ `mutable TMap<FName, float> CachedCurves;`
- L85 _private member_ `mutable bool bHaveCachedCurves;`
- L87 _private prototype_ `void CacheCurves() const;`
- L89 _private prototype_ `bool IsValidTransformIndex(int32 InTransformIndex) const;`

#### struct `FLiveLinkTransform`  
`struct FLiveLinkTransform`  
_L93-124_
- reflection: `USTRUCT(BlueprintType)`
- L97 _public prototype_ `FLiveLinkTransform();`
- L99 _public prototype_ `virtual ~FLiveLinkTransform() = default;`
- L101 _public prototype_ `void GetName(FName& Name) const;`
- L103 _public prototype_ `void GetTransformParentSpace(FTransform& OutTransform) const;`
- L105 _public prototype_ `void GetTransformRootSpace(FTransform& OutTransform) const;`
- L107 _public prototype_ `bool HasParent() const;`
- L109 _public prototype_ `void GetParent(FLiveLinkTransform& OutParentTransform) const;`
- L111 _public prototype_ `int32 GetChildCount() const;`
- L113 _public prototype_ `void GetChildren(TArray<FLiveLinkTransform>& OutChildTransforms) const;`
- L115 _public prototype_ `void SetCachedFrame(TSharedPtr<FCachedSubjectFrame> InCachedFrame);`
- L117 _public prototype_ `void SetTransformIndex(const int32 InTransformIndex);`
- L119 _public prototype_ `int32 GetTransformIndex() const;`
- L122 _private member_ `TSharedPtr<FCachedSubjectFrame> CachedFrame;`
- L123 _private member_ `int32 TransformIndex;`

#### struct `FSubjectFrameHandle`  
`struct FSubjectFrameHandle : public FLiveLinkBaseBlueprintData`  
_L127-159_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseBlueprintData`
- L131 _public prototype_ `FSubjectFrameHandle() = default;`
- L133 _public prototype_ `virtual ~FSubjectFrameHandle() = default;`
- L135 _public prototype_ `void GetCurves(TMap<FName, float>& OutCurves) const;`
- L137 _public prototype_ `bool GetCurveValueByName(FName CurveName, float& CurveValue) const;`
- L139 _public prototype_ `void GetSubjectMetadata(FSubjectMetadata& OutMetadata) const;`
- L141 _public prototype_ `int32 GetNumberOfTransforms() const;`
- L143 _public prototype_ `void GetTransformNames(TArray<FName>& OutTransformNames) const;`
- L145 _public prototype_ `void GetRootTransform(FLiveLinkTransform& OutLiveLinkTransform) const;`
- L147 _public prototype_ `void GetTransformByIndex(int32 InTransformIndex, FLiveLinkTransform& OutLiveLinkTransform) const;`
- L149 _public prototype_ `void GetTransformByName(FName InTransformName, FLiveLinkTransform& OutLiveLinkTransform) const;`
- L151 _public prototype_ `void SetCachedFrame(TSharedPtr<FCachedSubjectFrame> InCachedFrame);`
- L153 _public prototype_ `const FLiveLinkSkeletonStaticData* GetSourceSkeletonStaticData() const;`
- L155 _public prototype_ `const FLiveLinkAnimationFrameData* GetSourceAnimationFrameData() const;`
- L158 _private member_ `TSharedPtr<FCachedSubjectFrame> CachedFrame;`

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkAnimationRole.h` (Public)


#### class `ULiveLinkAnimationRole`  
`class ULiveLinkAnimationRole : public ULiveLinkBasicRole`  
_L23-39_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "Animation Role"), MinimalAPI)`
- inherits: `ULiveLinkBasicRole`
- desc: Role associated for Animation / Skeleton data.
- L29 _public prototype_ `virtual UScriptStruct* GetStaticDataStruct() const override;`
- L30 _public prototype_ `virtual UScriptStruct* GetFrameDataStruct() const override;`
- L31 _public prototype_ `virtual UScriptStruct* GetBlueprintDataStruct() const override;`
- L33 _public prototype_ `bool InitializeBlueprintData(const FLiveLinkSubjectFrameData& InSourceData, FLiveLinkBlueprintDataStruct& OutBlueprintData) const override;`
- L35 _public prototype_ `virtual FText GetDisplayName() const override;`
- L36 _public prototype_ `virtual bool IsStaticDataValid(const FLiveLinkStaticDataStruct& InStaticData, bool& bOutShouldLogWarning) const override;`
- L37 _public prototype_ `virtual bool IsFrameDataValid(const FLiveLinkStaticDataStruct& InStaticData, const FLiveLinkFrameDataStruct& InFrameData, bool& bOutShouldLogWarning) const override;`

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkAnimationTypes.h` (Public)


#### struct `FLiveLinkSkeletonStaticData`  
`struct FLiveLinkSkeletonStaticData : public FLiveLinkBaseStaticData`  
_L13-43_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseStaticData`
- desc: Static data for Animation purposes. Contains data about bones that shouldn't change every frame.
- L20 _public function_ `void SetBoneNames(const TArray<FName>& InBoneNames)` — Set the bone names for this skeleton
- L23 _public function_ `const TArray<FName>& GetBoneNames() const` — Get the bone names for this skeleton
- L26 _public function_ `void SetBoneParents(const TArray<int32> InBoneParents)` — Set the parent bones for this skeleton (Array of indices to parent)
- L29 _public function_ `const TArray<int32>& GetBoneParents() const` — Get skeleton's parent bones array
- L32 _public function_ `int32 FindRootBone() const` — Find skeleton root bone, which is the bone with an invalid parent bone index.
- L38 _public member_ `TArray<FName> BoneNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skeleton")` — Names of each bone in the skeleton
- L42 _public member_ `TArray<int32> BoneParents;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skeleton")` — Parent Indices: For each bone it specifies the index of its parent

#### struct `FLiveLinkAnimationFrameData`  
`struct FLiveLinkAnimationFrameData : public FLiveLinkBaseFrameData`  
_L49-58_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseFrameData`
- desc: Dynamic data for Animation purposes.
- L57 _public member_ `TArray<FTransform> Transforms;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skeleton")` — Array of transforms for each bone of the skeleton

#### struct `FLiveLinkFloatAnimationFrameData`  
`struct FLiveLinkFloatAnimationFrameData : public FLiveLinkBaseFrameData`  
_L62-97_
- reflection: `USTRUCT()`
- inherits: `FLiveLinkBaseFrameData`
- desc: Single-precision floating point equivalent of FLiveLinkAnimationFrameData.
- L67 _public function_ `static FLiveLinkFloatAnimationFrameData FromAnimData(const FLiveLinkAnimationFrameData& InAnimData)` — Converts double-precision float animation data to single-precision float animation data.
- L81 _public function_ `static FLiveLinkAnimationFrameData ToAnimData(const FLiveLinkFloatAnimationFrameData& InFloatData)` — Converts single-precision float animation data to double-precision float animation data.
- L96 _public member_ `TArray<FTransform3f> Transforms;` — `UPROPERTY()` — Array of transforms for each bone of the skeleton

#### Free symbols / members of external scopes

- L32 _function_ `int32 FindRootBone() const` (scope `FLiveLinkSkeletonStaticData::FindRootBone`) — Find skeleton root bone, which is the bone with an invalid parent bone index.
- L75 _function_ `Algo::Transform(InAnimData.Transforms, FloatData.Transforms, [](const FTransform& Transform) { return FTransform3f(Transform); });` (scope `FLiveLinkFloatAnimationFrameData::FromAnimData`)
- L89 _function_ `Algo::Transform(InFloatData.Transforms, AnimData.Transforms, [](const FTransform3f& Transform) { return FTransform(Transform); });` (scope `FLiveLinkFloatAnimationFrameData::ToAnimData`)

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkBasicRole.h` (Public)


#### class `ULiveLinkBasicRole`  
`class ULiveLinkBasicRole : public ULiveLinkRole`  
_L20-35_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "Basic Role"), MinimalAPI)`
- inherits: `ULiveLinkRole`
- desc: Role associated for no specific role data.
- L26 _public prototype_ `virtual UScriptStruct* GetStaticDataStruct() const override;`
- L27 _public prototype_ `virtual UScriptStruct* GetFrameDataStruct() const override;`
- L28 _public prototype_ `virtual UScriptStruct* GetBlueprintDataStruct() const override;`
- L30 _public prototype_ `virtual bool InitializeBlueprintData(const FLiveLinkSubjectFrameData& InSourceData, FLiveLinkBlueprintDataStruct& OutBlueprintData) const override;`
- L32 _public prototype_ `virtual FText GetDisplayName() const override;`
- L33 _public prototype_ `virtual bool IsFrameDataValid(const FLiveLinkStaticDataStruct& InStaticData, const FLiveLinkFrameDataStruct& InFrameData, bool& bOutShouldLogWarning) const override;`

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkBasicTypes.h` (Public)


#### struct `FLiveLinkBasicBlueprintData`  
`struct FLiveLinkBasicBlueprintData : public FLiveLinkBaseBlueprintData`  
_L12-23_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseBlueprintData`
- desc: Facility structure to handle base data in blueprint
- L18 _public member_ `FLiveLinkBaseStaticData StaticData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Data")` — Static data that should not change every frame
- L22 _public member_ `FLiveLinkBaseFrameData FrameData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Data")` — Dynamic data that can change every frame

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkCameraRole.h` (Public)


#### class `ULiveLinkCameraRole`  
`class ULiveLinkCameraRole : public ULiveLinkTransformRole`  
_L20-34_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "Camera Role"), MinimalAPI)`
- inherits: `ULiveLinkTransformRole`
- desc: Role associated for Camera data.
- L26 _public prototype_ `virtual UScriptStruct* GetStaticDataStruct() const override;`
- L27 _public prototype_ `virtual UScriptStruct* GetFrameDataStruct() const override;`
- L28 _public prototype_ `virtual UScriptStruct* GetBlueprintDataStruct() const override;`
- L30 _public prototype_ `virtual bool InitializeBlueprintData(const FLiveLinkSubjectFrameData& InSourceData, FLiveLinkBlueprintDataStruct& OutBlueprintData) const override;`
- L32 _public prototype_ `virtual FText GetDisplayName() const override;`

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkCameraTypes.h` (Public)


#### enum `ELiveLinkCameraProjectionMode`  
`enum class ELiveLinkCameraProjectionMode : uint8`  
_L10-14_
- reflection: `UENUM()`
- L12 _public enumerator_ `Perspective`
- L13 _public enumerator_ `Orthographic`

#### struct `FLiveLinkCameraStaticData`  
`struct FLiveLinkCameraStaticData : public FLiveLinkTransformStaticData`  
_L20-65_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkTransformStaticData`
- desc: Static data for Camera data.
- L28 _public member_ `bool bIsFieldOfViewSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether FieldOfView in frame data can be used
- L32 _public member_ `bool bIsAspectRatioSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether AspectRatio in frame data can be used
- L36 _public member_ `bool bIsFocalLengthSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether FocalLength in frame data can be used
- L40 _public member_ `bool bIsProjectionModeSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether ProjectionMode in frame data can be used
- L44 _public member_ `float FilmBackWidth = -1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Used with CinematicCamera. Values greater than 0 will be applied
- L48 _public member_ `float FilmBackHeight = -1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Used with CinematicCamera. Values greater than 0 will be applied
- L52 _public member_ `bool bIsApertureSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether Aperture in frame data can be used
- L56 _public member_ `bool bIsFocusDistanceSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether FocusDistance in frame data can be used
- L60 _public member_ `bool bIsDepthOfFieldSupported = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Set to false to force the camera to disable depth of field
- L64 _public member_ `bool bIsDynamicFilmbackSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Specifies if the live link subject will send dynamic changes to the film back.

#### struct `FLiveLinkCameraFrameData`  
`struct FLiveLinkCameraFrameData : public FLiveLinkTransformFrameData`  
_L71-107_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkTransformFrameData`
- desc: Dynamic data for camera
- L77 _public member_ `float FieldOfView = 90.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Field of View of the camera in degrees
- L81 _public member_ `float AspectRatio = 1.777778f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Aspect Ratio of the camera (Width / Heigth)
- L85 _public member_ `float FocalLength = 50.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Focal length of the camera
- L89 _public member_ `float Aperture = 2.8f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Aperture of the camera in terms of f-stop
- L93 _public member_ `float FocusDistance = 100000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Focus distance of the camera in cm. Works only in manual focus method
- L97 _public member_ `ELiveLinkCameraProjectionMode ProjectionMode = ELiveLinkCameraProjectionMode::Perspective;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — ProjectionMode of the camera (Perspective, Orthographic, etc...)
- L101 _public member_ `float FilmBackWidth = -1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Used with CinematicCamera. Values greater than 0 will be applied if bIsDynamicFilmbackSupported is true on static data.
- L105 _public member_ `float FilmBackHeight = -1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Used with CinematicCamera. Values greater than 0 will be applied if bIsDynamicFilmbackSupported is true on static data.

#### struct `FLiveLinkCameraBlueprintData`  
`struct FLiveLinkCameraBlueprintData : public FLiveLinkBaseBlueprintData`  
_L113-124_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseBlueprintData`
- desc: Facility structure to handle camera data in blueprint
- L119 _public member_ `FLiveLinkCameraStaticData StaticData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Static data that should not change every frame
- L123 _public member_ `FLiveLinkCameraFrameData FrameData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Dynamic data that can change every frame

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkCharacterRole.h` (Public)


#### class `ULiveLinkCharacterRole`  
`class ULiveLinkCharacterRole : public ULiveLinkAnimationRole`  
_L18-32_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "Character Role"), MinimalAPI)`
- inherits: `ULiveLinkAnimationRole`
- desc: Role associated for streaming animation and component transform.
- L24 _public prototype_ `virtual UScriptStruct* GetStaticDataStruct() const override;`
- L25 _public prototype_ `virtual UScriptStruct* GetFrameDataStruct() const override;`
- L26 _public prototype_ `virtual UScriptStruct* GetBlueprintDataStruct() const override;`
- L28 _public prototype_ `virtual FText GetDisplayName() const override;`
- L29 _public prototype_ `virtual bool IsStaticDataValid(const FLiveLinkStaticDataStruct& InStaticData, bool& bOutShouldLogWarning) const override;`
- L30 _public prototype_ `virtual bool IsFrameDataValid(const FLiveLinkStaticDataStruct& InStaticData, const FLiveLinkFrameDataStruct& InFrameData, bool& bOutShouldLogWarning) const override;`

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkCharacterTypes.h` (Public)


#### struct `FLiveLinkCharacterStaticData`  
`struct FLiveLinkCharacterStaticData : public FLiveLinkSkeletonStaticData`  
_L15-30_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkSkeletonStaticData`
- desc: Static data for Animation purposes. Contains data about bones that shouldn't change every frame.
- L21 _public member_ `bool bIsLocationSupported = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")`
- L25 _public member_ `bool bIsRotationSupported = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether rotation in frame data should be used
- L29 _public member_ `bool bIsScaleSupported = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether scale in frame data should be used

#### struct `FLiveLinkCharacterFrameData`  
`struct FLiveLinkCharacterFrameData : public FLiveLinkAnimationFrameData`  
_L36-44_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkAnimationFrameData`
- desc: Dynamic data for Animation purposes.
- L43 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", Interp)` — Transform of the frame

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkInputDeviceRole.h` (Public)


#### class `ULiveLinkInputDeviceRole`  
`class ULiveLinkInputDeviceRole : public ULiveLinkBasicRole`  
_L19-33_
- reflection: `UCLASS(MinimalAPI, BlueprintType, meta = (DisplayName = "Input Device Role"))`
- inherits: `ULiveLinkBasicRole`
- desc: Role associated with Input Device data.
- L25 _public prototype_ `virtual UScriptStruct* GetStaticDataStruct() const override;`
- L26 _public prototype_ `virtual UScriptStruct* GetFrameDataStruct() const override;`
- L27 _public prototype_ `virtual UScriptStruct* GetBlueprintDataStruct() const override;`
- L29 _public prototype_ `virtual bool InitializeBlueprintData(const FLiveLinkSubjectFrameData& InSourceData, FLiveLinkBlueprintDataStruct& OutBlueprintData) const override;`
- L31 _public prototype_ `virtual FText GetDisplayName() const override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API LIVELINKINTERFACE_API`

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkInputDeviceTypes.h` (Public)


#### struct `FLiveLinkGamepadInputDeviceStaticData`  
`struct FLiveLinkGamepadInputDeviceStaticData : public FLiveLinkBaseStaticData`  
_L14-17_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseStaticData`
- desc: Struct for static Gamepad Input Device data

#### struct `FLiveLinkGamepadInputDeviceFrameData`  
`struct FLiveLinkGamepadInputDeviceFrameData : public FLiveLinkBaseFrameData`  
_L23-122_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseFrameData`
- desc: Struct for dynamic (per-frame) Gampead Input Device data
- L28 _public member_ `float LeftAnalogX = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L31 _public member_ `float LeftAnalogY = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L34 _public member_ `float RightAnalogX = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L37 _public member_ `float RightAnalogY = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L40 _public member_ `float LeftTriggerAnalog = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L43 _public member_ `float RightTriggerAnalog = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L46 _public member_ `float LeftThumb = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L49 _public member_ `float RightThumb = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L52 _public member_ `float SpecialLeft = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L55 _public member_ `float SpecialLeft_X = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L58 _public member_ `float SpecialLeft_Y = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L61 _public member_ `float SpecialRight = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L64 _public member_ `float FaceButtonBottom = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L67 _public member_ `float FaceButtonRight = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L70 _public member_ `float FaceButtonLeft = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L73 _public member_ `float FaceButtonTop = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L76 _public member_ `float LeftShoulder = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L79 _public member_ `float RightShoulder = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L82 _public member_ `float LeftTriggerThreshold = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L85 _public member_ `float RightTriggerThreshold = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L88 _public member_ `float DPadUp = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L91 _public member_ `float DPadDown = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L94 _public member_ `float DPadRight = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L97 _public member_ `float DPadLeft = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L100 _public member_ `float LeftStickUp = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L103 _public member_ `float LeftStickDown = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L106 _public member_ `float LeftStickRight = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L109 _public member_ `float LeftStickLeft = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L112 _public member_ `float RightStickUp = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L115 _public member_ `float RightStickDown = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L118 _public member_ `float RightStickRight = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`
- L121 _public member_ `float RightStickLeft = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gamepad Input Device")`

#### struct `FLiveLinkGamepadInputDeviceBlueprintData`  
`struct FLiveLinkGamepadInputDeviceBlueprintData : public FLiveLinkBaseBlueprintData`  
_L128-139_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseBlueprintData`
- desc: Facility structure to handle Preston MDR data in blueprint
- L134 _public member_ `FLiveLinkGamepadInputDeviceStaticData StaticData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Static data that should not change every frame
- L138 _public member_ `FLiveLinkGamepadInputDeviceFrameData FrameData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Dynamic data that can change every frame

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkLightRole.h` (Public)


#### class `ULiveLinkLightRole`  
`class ULiveLinkLightRole : public ULiveLinkTransformRole`  
_L20-34_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "Light Role"), MinimalAPI)`
- inherits: `ULiveLinkTransformRole`
- desc: Role associated for Light data.
- L26 _public prototype_ `virtual UScriptStruct* GetStaticDataStruct() const override;`
- L27 _public prototype_ `virtual UScriptStruct* GetFrameDataStruct() const override;`
- L28 _public prototype_ `virtual UScriptStruct* GetBlueprintDataStruct() const override;`
- L30 _public prototype_ `bool InitializeBlueprintData(const FLiveLinkSubjectFrameData& InSourceData, FLiveLinkBlueprintDataStruct& OutBlueprintData) const override;`
- L32 _public prototype_ `virtual FText GetDisplayName() const override;`

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkLightTypes.h` (Public)


#### struct `FLiveLinkLightStaticData`  
`struct FLiveLinkLightStaticData : public FLiveLinkTransformStaticData`  
_L12-53_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkTransformStaticData`
- desc: Static data for Light data.
- L20 _public member_ `bool bIsTemperatureSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether Temperature can be used in the frame data
- L24 _public member_ `bool bIsIntensitySupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether Intensity can be used in the frame data
- L28 _public member_ `bool bIsLightColorSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether LightColor can be used in the frame data
- L32 _public member_ `bool bIsInnerConeAngleSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether InnerConeAngle can be used in the frame data. Only used for spot lights
- L36 _public member_ `bool bIsOuterConeAngleSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether OuterConeAngle can be used in the frame data. Only used for spot lights
- L40 _public member_ `bool bIsAttenuationRadiusSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether AttenuationRadius can be used in the frame data. Only used for spot lights
- L44 _public member_ `bool bIsSourceLenghtSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether SourceLength can be used in the frame data. Only used for spot lights
- L48 _public member_ `bool bIsSourceRadiusSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether SourceRadius can be used in the frame data. Only used for spot lights
- L52 _public member_ `bool bIsSoftSourceRadiusSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether SoftSourceRadius can be used in the frame data. Only used for spot lights

#### struct `FLiveLinkLightFrameData`  
`struct FLiveLinkLightFrameData : public FLiveLinkTransformFrameData`  
_L59-98_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkTransformFrameData`
- desc: Dynamic data for light.
- L65 _public member_ `float Temperature = 6500.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Color temperature in Kelvin of the blackbody illuminant
- L69 _public member_ `float Intensity = 3.1415926535897932f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Total energy that the light emits in lux.
- L73 _public member_ `FColor LightColor = FColor::White;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Filter color of the light.
- L77 _public member_ `float InnerConeAngle = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Inner cone angle in degrees for a Spotlight.
- L81 _public member_ `float OuterConeAngle = 44.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Outer cone angle in degrees for a Spotlight.
- L85 _public member_ `float AttenuationRadius = 1000.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Light visible influence. Works for Pointlight and Spotlight.
- L89 _public member_ `float SourceRadius = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Radius of light source shape. Works for Pointlight and Spotlight.
- L93 _public member_ `float SoftSourceRadius = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Soft radius of light source shape. Works for Pointlight and Spotlight.
- L97 _public member_ `float SourceLength = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", Interp)` — Length of light source shape. Works for Pointlight and Spotlight.

#### struct `FLiveLinkLightBlueprintData`  
`struct FLiveLinkLightBlueprintData : public FLiveLinkBaseBlueprintData`  
_L104-115_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseBlueprintData`
- desc: Facility structure to handle light data in blueprint
- L110 _public member_ `FLiveLinkLightStaticData StaticData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Static data that should not change every frame
- L114 _public member_ `FLiveLinkLightFrameData FrameData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Dynamic data that can change every frame

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkLocatorRole.h` (Public)


#### class `ULiveLinkLocatorRole`  
`class ULiveLinkLocatorRole : public ULiveLinkBasicRole`  
_L19-34_
- reflection: `UCLASS(MinimalAPI, Blueprintable, meta = (DisplayName = "Locator Role"))`
- inherits: `ULiveLinkBasicRole`
- desc: Role associated with Locator / Marker data. This is intended for optical motion capture marker clouds.
- L25 _public prototype_ `virtual UScriptStruct* GetStaticDataStruct() const override;`
- L26 _public prototype_ `virtual UScriptStruct* GetFrameDataStruct() const override;`
- L27 _public prototype_ `virtual UScriptStruct* GetBlueprintDataStruct() const override;`
- L29 _public prototype_ `virtual bool InitializeBlueprintData(const FLiveLinkSubjectFrameData& InSourceData, FLiveLinkBlueprintDataStruct& OutBlueprintData) const override;`
- L31 _public prototype_ `virtual FText GetDisplayName() const override;`
- L32 _public prototype_ `virtual bool IsFrameDataValid(const FLiveLinkStaticDataStruct& InStaticData, const FLiveLinkFrameDataStruct& InFrameData, bool& bOutShouldLogWarning) const override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API LIVELINKINTERFACE_API`

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkLocatorTypes.h` (Public)


#### struct `FLiveLinkLocatorStaticData`  
`struct FLiveLinkLocatorStaticData : public FLiveLinkBaseStaticData`  
_L13-36_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseStaticData`
- desc: Static data for Locator purposes. Contains data about locators that should not change every frame. If data is unlabelled markers, Locator names array must be empty.
- L20 _public function_ `void SetLocatorNames(const TArray<FName>& InLocatorNames)` — Set the locator names
- L23 _public function_ `const TArray<FName>& GetLocatorNames() const` — Get the locator names
- L26 _public function_ `void SetUnlabelledData(const bool& InbUnlabelledData)` — Set as Unlabelled data
- L29 _public member_ `TArray<FName> LocatorNames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locator")`
- L35 _public member_ `bool bUnlabelledData=false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locator")` — Set this to true if you wish to send an unstructured number of locators that can vary from one frame to the next.

#### struct `FLiveLinkLocatorFrameData`  
`struct FLiveLinkLocatorFrameData : public FLiveLinkBaseFrameData`  
_L42-52_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseFrameData`
- desc: Dynamic data for Animation purposes.
- L51 _public member_ `TArray<FVector> Locators;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locator")` — Array of locations for each locator/marker

#### struct `FLiveLinkLocatorBlueprintData`  
`struct FLiveLinkLocatorBlueprintData : public FLiveLinkBaseBlueprintData`  
_L59-70_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseBlueprintData`
- L65 _public member_ `FLiveLinkLocatorStaticData StaticData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locator")` — Static data should not change every frame
- L68 _public member_ `FLiveLinkLocatorFrameData FrameData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locator")`

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkTransformRole.h` (Public)


#### class `ULiveLinkTransformRole`  
`class ULiveLinkTransformRole : public ULiveLinkBasicRole`  
_L20-34_
- reflection: `UCLASS(BlueprintType, meta = (DisplayName = "Transform Role"), MinimalAPI)`
- inherits: `ULiveLinkBasicRole`
- desc: Role associated for Camera data.
- L26 _public prototype_ `virtual UScriptStruct* GetStaticDataStruct() const override;`
- L27 _public prototype_ `virtual UScriptStruct* GetFrameDataStruct() const override;`
- L28 _public prototype_ `virtual UScriptStruct* GetBlueprintDataStruct() const override;`
- L30 _public prototype_ `virtual bool InitializeBlueprintData(const FLiveLinkSubjectFrameData& InSourceData, FLiveLinkBlueprintDataStruct& OutBlueprintData) const override;`
- L32 _public prototype_ `virtual FText GetDisplayName() const override;`

### `Source/Runtime/LiveLinkInterface/Public/Roles/LiveLinkTransformTypes.h` (Public)


#### struct `FLiveLinkTransformStaticData`  
`struct FLiveLinkTransformStaticData : public FLiveLinkBaseStaticData`  
_L12-27_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseStaticData`
- desc: Static data for Transform data.
- L18 _public member_ `bool bIsLocationSupported = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether location in frame data should be used
- L22 _public member_ `bool bIsRotationSupported = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether rotation in frame data should be used
- L26 _public member_ `bool bIsScaleSupported = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Whether scale in frame data should be used

#### struct `FLiveLinkTransformFrameData`  
`struct FLiveLinkTransformFrameData : public FLiveLinkBaseFrameData`  
_L33-40_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseFrameData`
- desc: Dynamic data for Transform
- L39 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties", Interp)` — Transform of the frame

#### struct `FLiveLinkTransformBlueprintData`  
`struct FLiveLinkTransformBlueprintData : public FLiveLinkBaseBlueprintData`  
_L46-57_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLiveLinkBaseBlueprintData`
- desc: Facility structure to handle transform data in blueprint
- L52 _public member_ `FLiveLinkTransformStaticData StaticData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Data")` — Static data that should not change every frame
- L56 _public member_ `FLiveLinkTransformFrameData FrameData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform Data")` — Dynamic data that can change every frame
