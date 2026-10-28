# Plugins / StylusInputDebugWidget

- module root: `Plugins/Editor/StylusInput/Source/StylusInputDebugWidget`
- headers: 2; symbols: 75
- symbol kinds: class=4, delegate=2, function=5, member=25, namespace=8, prototype=29, struct=2

### `Plugins/Editor/StylusInput/Source/StylusInputDebugWidget/Private/StylusInputDebugPaintWidget.h` (Private)


#### class `UE::StylusInput::DebugWidget::SStylusInputDebugPaintWidget`  
`class SStylusInputDebugPaintWidget : public SCompoundWidget`  
_L16-46_
- inherits: `SCompoundWidget`
- L19 _public function_ `SLATE_BEGIN_ARGS(SStylusInputDebugPaintWidget)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args);`
- L27 _public prototype_ `void Add(const FStylusInputPacket& Packet);`
- L29 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L32 _public prototype_ `virtual TOptional<EMouseCursor::Type> GetCursor() const;`
- L43 _private prototype_ `int32 DrawPaintPackets(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L45 _private member_ `mutable TRingBuffer<FPaintPacket> PaintPackets;`

#### struct `UE::StylusInput::DebugWidget::SStylusInputDebugPaintWidget::FPaintPacket`  
`struct FPaintPacket`  
_L35-41_
- L37 _public member_ `FVector2f Position = FVector2f::ZeroVector;`
- L38 _public member_ `float NormalPressure = 0.0f;`
- L39 _public member_ `EPenStatus PenStatus = EPenStatus::None;`
- L40 _public member_ `double TimeAddedMS = 0.0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace StylusInput` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace StylusInput` (scope `UE`)
- L14 _namespace_ `namespace DebugWidget` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInputDebugWidget/Private/StylusInputDebugWidget.h` (Private)


#### class `UE::StylusInput::DebugWidget::FDebugEventHandlerAsynchronous`  
`class FDebugEventHandlerAsynchronous final : public IStylusInputEventHandler, FTickableEditorObject`  
_L17-36_
- inherits: `IStylusInputEventHandler,FTickableEditorObject`
- L20 _public prototype_ `FDebugEventHandlerAsynchronous(FOnPacketCallback&& OnPacketCallback, FOnDebugEventCallback&& OnDebugEventCallback);`
- L22 _public function_ `virtual FString GetName() override`
- L24 _public prototype_ `virtual void OnPacket(const FStylusInputPacket& Packet, IStylusInputInstance* Instance) override;`
- L25 _public prototype_ `virtual void OnDebugEvent(const FString& Message, IStylusInputInstance* Instance) override;`
- L27 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L28 _public function_ `virtual TStatId GetStatId() const override`
- L31 _private member_ `FOnPacketCallback OnPacketCallback;`
- L32 _private member_ `FOnDebugEventCallback OnDebugEventCallback;`
- L34 _private member_ `TSpscQueue<FStylusInputPacket> PacketQueue;`
- L35 _private member_ `TSpscQueue<FString> DebugEventQueue;`

#### class `UE::StylusInput::DebugWidget::FDebugEventHandlerOnGameThread`  
`class FDebugEventHandlerOnGameThread final : public IStylusInputEventHandler`  
_L38-51_
- inherits: `IStylusInputEventHandler`
- L41 _public prototype_ `FDebugEventHandlerOnGameThread(FOnPacketCallback&& OnPacketCallback, FOnDebugEventCallback&& OnDebugEventCallback);`
- L43 _public function_ `virtual FString GetName() override`
- L45 _public prototype_ `virtual void OnPacket(const FStylusInputPacket& Packet, IStylusInputInstance* Instance) override;`
- L46 _public prototype_ `virtual void OnDebugEvent(const FString& Message, IStylusInputInstance* Instance) override;`
- L49 _private member_ `FOnPacketCallback OnPacketCallback;`
- L50 _private member_ `FOnDebugEventCallback OnDebugEventCallback;`

#### class `UE::StylusInput::DebugWidget::SStylusInputDebugWidget`  
`class SStylusInputDebugWidget : public SCompoundWidget`  
_L53-107_
- inherits: `SCompoundWidget`
- L56 _public function_ `SLATE_BEGIN_ARGS(SStylusInputDebugWidget)`
- L61 _public prototype_ `virtual ~SStylusInputDebugWidget() override;`
- L63 _public prototype_ `void Construct(const FArguments& Args);`
- L65 _public prototype_ `void NotifyWidgetRelocated();`
- L68 _private prototype_ `void AcquireStylusInput();`
- L69 _private prototype_ `void ReleaseStylusInput();`
- L70 _private prototype_ `void RegisterEventHandler();`
- L71 _private prototype_ `void UnregisterEventHandler();`
- L73 _private prototype_ `const IStylusInputTabletContext* GetTabletContext(uint32 TabletContextID);`
- L74 _private prototype_ `const IStylusInputStylusInfo* GetStylusInfo(uint32 StylusID);`
- L76 _private prototype_ `void OnPacket(const FStylusInputPacket& Packet);`
- L77 _private prototype_ `void OnDebugEvent(const FString& Message);`
- L79 _private prototype_ `TSharedRef<SWidget> GetInterfaceMenu();`
- L80 _private prototype_ `void SetInterface(FName InInterface);`
- L81 _private member_ `FName Interface;`
- L83 _private prototype_ `TSharedRef<SWidget> GetEventHandlerThreadMenu();`
- L84 _private prototype_ `void SetEventHandlerThread(EEventHandlerThread InEventHandlerThread);`
- L85 _private member_ `EEventHandlerThread EventHandlerThread = EEventHandlerThread::OnGameThread;`
- L87 _private member_ `IStylusInputInstance* StylusInput = nullptr;`
- L88 _private member_ `TUniquePtr<IStylusInputEventHandler> EventHandler;`
- L89 _private member_ `TWeakPtr<SWindow> StylusInputWindow;`
- L91 _private member_ `TSharedPtr<SStylusInputDebugPaintWidget> PaintWidget;`
- L93 _private member_ `TMap<uint32, TSharedPtr<IStylusInputTabletContext>> TabletContexts;`
- L94 _private member_ `TMap<uint32, TSharedPtr<IStylusInputStylusInfo>> StylusInfos;`
- L96 _private member_ `FString DebugMessages;`
- L106 _private member_ `FLastPacketData LastPacketData;`

#### struct `UE::StylusInput::DebugWidget::SStylusInputDebugWidget::FLastPacketData`  
`struct FLastPacketData`  
_L98-104_
- L100 _public member_ `bool bIsSet = false;`
- L101 _public member_ `FStylusInputPacket Packet;`
- L102 _public member_ `const IStylusInputTabletContext* TabletContext = nullptr;`
- L103 _public member_ `const IStylusInputStylusInfo* StylusInfo = nullptr;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace StylusInput` (scope `UE`)
- L12 _namespace_ `namespace DebugWidget` (scope `UE::StylusInput`)
- L14 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPacketCallback, const FStylusInputPacket&);`
- L14 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPacketCallback, const FStylusInputPacket&);` (scope `UE::StylusInput::DebugWidget`)
- L15 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDebugEventCallback, const FString&);`
- L15 _prototype_ `DECLARE_DELEGATE_OneParam(FOnDebugEventCallback, const FString&);` (scope `UE::StylusInput::DebugWidget`)
