# Plugins / RivermaxSync

- module root: `Plugins/VirtualProduction/Rivermax/RivermaxSync/Source/RivermaxSync`
- headers: 2; symbols: 35
- symbol kinds: class=2, delegate=1, function=4, member=10, prototype=15, struct=2, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, RivermaxMedia, UnrealEd
- PublicDependencyModuleNames: DisplayCluster, DisplayClusterMedia, RivermaxCore, StageDataCore

### `Plugins/VirtualProduction/Rivermax/RivermaxSync/Source/RivermaxSync/Private/RivermaxSyncLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRivermaxSync, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRivermaxSync, Log, All);`

### `Plugins/VirtualProduction/Rivermax/RivermaxSync/Source/RivermaxSync/Public/MediaOutputSynchronizationPolicyRivermax.h` (Public)


#### class `FMediaOutputSynchronizationPolicyRivermaxHandler`  
`class FMediaOutputSynchronizationPolicyRivermaxHandler : public FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBaseHandler`  
_L18-137_
- inherits: `FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBaseHandler`
- desc: Synchronization logic handler class for UMediaOutputSynchronizationPolicyRivermax.
- L21 _private typedef_ `using Super = FDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBaseHandler;`
- L24 _public prototype_ `FMediaOutputSynchronizationPolicyRivermaxHandler(UMediaOutputSynchronizationPolicyRivermax* InPolicyObject);`
- L27 _public prototype_ `virtual TSubclassOf<UDisplayClusterMediaOutputSynchronizationPolicy> GetPolicyClass() const override;`
- L32 _public prototype_ `virtual void Synchronize() override;` — We do our own synchronization by looking at distance to alignment point.
- L35 _public prototype_ `virtual bool IsCaptureTypeSupported(UMediaCapture* MediaCapture) const override;` — Returns true if specified media capture type can be synchonized by the policy implementation
- L106 _protected prototype_ `virtual bool InitializeBarrier(const FString& SyncInstanceId) override;` — Initializes dynamic barrier on the primary node.
- L109 _protected prototype_ `void HandleBarrierSync(FGenericBarrierSynchronizationDelegateData& BarrierSyncData);` — Barrier callback containing data from each node to detect if cluster is out of sync.
- L112 _protected prototype_ `double GetTimeBeforeNextSyncPoint() const;` — Returns amount of time before next synchronization point.
- L121 _protected prototype_ `bool PickPtpBaseNodeAndData( const FGenericBarrierSynchronizationDelegateData& BarrierSyncData, const FMediaSyncBarrierData*& OutPtpBaseNodeData, FString& OutPtpBaseNodeId ) const;` — Deterministically picks a node to base ptp offsets on other nodes from. @param BarrierSyncData the barrier data from all the clients. @param OutPtpBaseNodeData Will be populated with a pointer to the barrier sync data of the selected ptp base node. @param OutPtpBaseNodeId For convenience, this returns the name of the ptp base node.
- L130 _protected member_ `struct FMediaSyncBarrierData BarrierDataStruct;` — Holds data provided to server by this node when joining the barrier
- L133 _protected member_ `float MarginMs = 5.0f;` — Synchronization margin (ms)
- L136 _protected member_ `TArray<uint8> BarrierData;` — Memory buffer used to contain data exchanged in the barrier

#### struct `FMediaOutputSynchronizationPolicyRivermaxHandler::FMediaSyncBarrierData`  
`struct FMediaSyncBarrierData`  
_L40-101_
- desc: Holds data provided to server by each node when joining the barrier
- L42 _public function_ `FMediaSyncBarrierData()`
- L48 _public function_ `void Reset()` — Reset the data to default values
- L58 _public function_ `void InsertFrameInfo(const UE::RivermaxCore::FPresentedFrameInfo& FrameInfo)` — Insert the given frame information into the recorded presentation history
- L73 _public prototype_ `FString LastRenderedFrameNumbersAsString() const;` — Rendered frames as comma separated string
- L76 _public prototype_ `FString PresentedFrameBoundaryNumbersAsString() const;` — Presented frame boundaries as comma separated string
- L91 _public prototype_ `bool HasConfirmedDesync(const FMediaSyncBarrierData& OtherBarrierData, int64& OutVsyncDelta) const;` — Returns true if the frame presentation history indicates a desynced state. @param OtherBarrierData Barrier data of the node we're comparing with. @param OutVsyncDelta When the same frame is presented at different Vsync frame boundaries, this parameter contains the delta between them. Useful in detecting large PTP differences between nodes. @return True if different frames were presented at the same Vsync frame boundaries.
- L94 _public member_ `static constexpr int32 FRAMEHISTORYLEN = 2;` — How many frames to include in the history
- L97 _public member_ `uint64 PresentedFrameBoundaryNumber[FRAMEHISTORYLEN];` — Frame boundary number at which the last frame was presented.
- L100 _public member_ `uint32 LastRenderedFrameNumber[FRAMEHISTORYLEN];` — Last engine frame number that was presented

#### class `UMediaOutputSynchronizationPolicyRivermax`  
`class UMediaOutputSynchronizationPolicyRivermax : public UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBase`  
_L144-160_
- reflection: `UCLASS(editinlinenew, Blueprintable, meta = (DisplayName = "Rivermax (PTP)"))`
- inherits: `UDisplayClusterMediaOutputSynchronizationPolicyEthernetBarrierBase`
- desc: Rivermax media synchronization policy implementation
- L151 _public prototype_ `virtual TSharedPtr<IDisplayClusterMediaOutputSynchronizationPolicyHandler> GetHandler() override;`
- L154 _protected member_ `TSharedPtr<IDisplayClusterMediaOutputSynchronizationPolicyHandler> Handler;`
- L159 _public member_ `float MarginMs = 5.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings", meta = (DisplayName = "Margin (ms)", ClampMin = "1", ClampMax = "20", UIMin = "1", UIMax = "20"))` — Synchronization margin (ms)

#### struct `FRivermaxClusterPtpUnsyncEvent`  
`struct FRivermaxClusterPtpUnsyncEvent : public FStageProviderEventMessage`  
_L166-193_
- reflection: `USTRUCT()`
- inherits: `FStageProviderEventMessage`
- desc: Stage Monitor event to report nodes that are out of PTP sync with respect to a given PTP base node.
- L171 _public prototype_ `FRivermaxClusterPtpUnsyncEvent() = default;`
- L173 _public function_ `FRivermaxClusterPtpUnsyncEvent(const TMap<FString, int64>& InNodePtpFrameDeltas, const FString& InPtpBaseNodeId) : NodePtpFrameDeltas(InNodePtpFrameDeltas) , PtpBaseNodeId(InPtpBaseNodeId)`
- L182 _public member_ `TMap<FString, int64> NodePtpFrameDeltas;` — `UPROPERTY(VisibleAnywhere, Category = "PtpSync")` — Nodes with PTP video frame mismatches compared to the ptp base node id.
- L186 _public member_ `FString PtpBaseNodeId;` — `UPROPERTY(VisibleAnywhere, Category = "PtpSync")` — Id of the base node the PTP delta video frames are compared with
- L191 _public prototype_ `virtual FString ToString() const override;`
