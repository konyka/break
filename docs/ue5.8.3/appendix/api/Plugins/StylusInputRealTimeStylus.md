# Plugins / StylusInputRealTimeStylus

- module root: `Plugins/Editor/StylusInput/Source/StylusInputRealTimeStylus`
- headers: 9; symbols: 280
- symbol kinds: class=10, delegate=3, enum=2, enumerator=33, externvar=1, function=27, member=71, namespace=31, prototype=81, struct=5, typedef=16

### `Plugins/Editor/StylusInput/Source/StylusInputRealTimeStylus/Private/RealTimeStylusAPI.h` (Private)


#### class `UE::StylusInput::RealTimeStylus::FRealTimeStylusAPI`  
`class FRealTimeStylusAPI`  
_L15-70_
- L18 _public prototype_ `static FName GetName();`
- L19 _public prototype_ `static const FRealTimeStylusAPI& GetInstance();`
- L21 _public prototype_ `bool IsValid() const;`
- L23 _public typedef_ `using FFuncGetTickCount = DWORD();`
- L24 _public member_ `FFuncGetTickCount* GetTickCount = nullptr;`
- L26 _public typedef_ `using FFuncGetClientRect = BOOL(HWND, LPRECT);`
- L27 _public member_ `FFuncGetClientRect* GetClientRect = nullptr;`
- L29 _public typedef_ `using FFuncGetDC = HDC(HWND);`
- L30 _public member_ `FFuncGetDC* GetDC = nullptr;`
- L32 _public typedef_ `using FFuncReleaseDC = int(HWND, HDC);`
- L33 _public member_ `FFuncReleaseDC* ReleaseDC = nullptr;`
- L35 _public typedef_ `using FFuncGetDeviceCaps = int(HDC, int);`
- L36 _public member_ `FFuncGetDeviceCaps* GetDeviceCaps = nullptr;`
- L38 _public typedef_ `using FFuncCoCreateInstance = HRESULT(REFCLSID, IUnknown*, DWORD, REFIID, LPVOID*);`
- L39 _public member_ `FFuncCoCreateInstance* CoCreateInstance = nullptr;`
- L41 _public typedef_ `using FFuncCoCreateFreeThreadedMarshaler = HRESULT(LPUNKNOWN, LPUNKNOWN*);`
- L42 _public member_ `FFuncCoCreateFreeThreadedMarshaler* CoCreateFreeThreadedMarshaler = nullptr;`
- L44 _public typedef_ `using FFuncCoTaskMemFree = void(LPVOID);`
- L45 _public member_ `FFuncCoTaskMemFree* CoTaskMemFree = nullptr;`
- L47 _public typedef_ `using FFuncStringFromGUID2 = int(REFGUID, LPOLESTR, int);`
- L48 _public member_ `FFuncStringFromGUID2* StringFromGUID2 = nullptr;`
- L50 _public typedef_ `using FFuncSysFreeString = void(BSTR);`
- L51 _public member_ `FFuncSysFreeString* SysFreeString = nullptr;`
- L53 _public typedef_ `using FFuncVariantClear = HRESULT(VARIANTARG*);`
- L54 _public member_ `FFuncVariantClear* VariantClear = nullptr;`
- L56 _public typedef_ `using FFuncVariantInit = void(VARIANTARG*);`
- L57 _public member_ `FFuncVariantInit* VariantInit = nullptr;`
- L61 _private prototype_ `FRealTimeStylusAPI();`
- L62 _private prototype_ `~FRealTimeStylusAPI();`
- L64 _private member_ `TArray<void*> DllHandles;`
- L66 _private member_ `bool bInitializedComLibrary = false;`
- L67 _private member_ `bool bHasRTSComDllHandle = false;`
- L68 _private member_ `bool bHasInkObjDllHandle = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace StylusInput` (scope `UE`)
- L13 _namespace_ `namespace RealTimeStylus` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInputRealTimeStylus/Private/RealTimeStylusInstance.h` (Private)


#### class `UE::StylusInput::RealTimeStylus::FRealTimeStylusInstance`  
`class FRealTimeStylusInstance : public IStylusInputInstance`  
_L26-67_
- inherits: `IStylusInputInstance`
- L29 _public prototype_ `explicit FRealTimeStylusInstance(uint32 ID, HWND OSWindowHandle);`
- L32 _public prototype_ `virtual bool AddEventHandler(IStylusInputEventHandler* EventHandler, EEventHandlerThread Thread) override;`
- L33 _public prototype_ `virtual bool RemoveEventHandler(IStylusInputEventHandler* EventHandler) override;`
- L35 _public prototype_ `virtual const TSharedPtr<IStylusInputTabletContext> GetTabletContext(uint32 TabletContextID) override;`
- L36 _public prototype_ `virtual const TSharedPtr<IStylusInputStylusInfo> GetStylusInfo(uint32 StylusID) override;`
- L38 _public prototype_ `virtual float GetPacketsPerSecond(EEventHandlerThread EventHandlerThread) const override;`
- L40 _public prototype_ `virtual FName GetInterfaceName() override;`
- L41 _public prototype_ `virtual FText GetName() override;`
- L43 _public prototype_ `virtual bool WasInitializedSuccessfully() const override;`
- L46 _private prototype_ `void EnablePlugin(EEventHandlerThread EventHandlerThread, IStylusInputEventHandler* EventHandler);`
- L47 _private prototype_ `void DisablePlugin(EEventHandlerThread EventHandlerThread);`
- L49 _private prototype_ `void SetupWindowContext(HWND HWindow);`
- L50 _private prototype_ `const FWindowContext& GetWindowContext() const;`
- L52 _private prototype_ `void UpdateStylusInfo(STYLUS_ID StylusID);`
- L53 _private prototype_ `void UpdateTabletContexts(const FTabletContextContainer& InTabletContexts);`
- L55 _private member_ `const uint32 ID;`
- L56 _private member_ `const FRealTimeStylusAPI& RealTimeStylusAPI;`
- L57 _private member_ `FWindowContext WindowContext;`
- L59 _private member_ `TComPtr<IRealTimeStylus> RealTimeStylus;`
- L60 _private member_ `TUniquePtr<FRealTimeStylusPluginAsync> AsyncPlugin;`
- L61 _private member_ `TUniquePtr<FRealTimeStylusPluginSync> SyncPlugin;`
- L63 _private member_ `FTabletContextThreadSafeContainer TabletContexts;`
- L64 _private member_ `FStylusInfoThreadSafeContainer StylusInfos;`
- L66 _private member_ `bool bWasInitializedSuccessfully = true;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace StylusInput` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace StylusInput` (scope `UE`)
- L20 _namespace_ `namespace RealTimeStylus` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInputRealTimeStylus/Private/RealTimeStylusInterface.h` (Private)


#### class `UE::StylusInput::RealTimeStylus::FRealTimeStylusInterface`  
`class FRealTimeStylusInterface : public IStylusInputInterface`  
_L14-35_
- inherits: `IStylusInputInterface`
- L17 _public prototype_ `virtual FName GetName() const override;`
- L19 _public prototype_ `virtual IStylusInputInstance* CreateInstance(SWindow& Window) override;`
- L20 _public prototype_ `virtual bool ReleaseInstance(IStylusInputInstance* Instance) override;`
- L25 _private prototype_ `static TUniquePtr<IStylusInputInterface> Create();`
- L33 _private member_ `TMap<SWindow*, FRefCountedInstance> Instances;`
- L34 _private member_ `uint32 NextInstanceID = 0;`

#### struct `UE::StylusInput::RealTimeStylus::FRealTimeStylusInterface::FRefCountedInstance`  
`struct FRefCountedInstance`  
_L27-31_
- L29 _public member_ `TUniquePtr<FRealTimeStylusInstance> Instance;`
- L30 _public member_ `int32 RefCount;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace StylusInput` (scope `UE`)
- L10 _namespace_ `namespace RealTimeStylus` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInputRealTimeStylus/Private/RealTimeStylusPluginAsync.h` (Private)


#### class `UE::StylusInput::RealTimeStylus::FRealTimeStylusPluginAsync`  
`class FRealTimeStylusPluginAsync final : public IStylusAsyncPlugin, public FRealTimeStylusPluginBase`  
_L9-69_
- inherits: `IStylusAsyncPlugin,FRealTimeStylusPluginBase`
- L12 _public prototype_ `FRealTimeStylusPluginAsync(IStylusInputInstance* Instance, FGetWindowContextCallback&& GetWindowContext, FUpdateTabletContextsCallback&& UpdateTabletContextsCallback, FUpdateStylusInfoCallback UpdateStylusInfoCallback, IStylusInputEventHandler* EventHandler);`
- L18 _public function_ `virtual HRESULT QueryInterface(REFIID InterfaceID, void** InterfaceObject) override` — IUnknown
- L31 _public function_ `virtual ULONG AddRef() override`
- L36 _public function_ `virtual ULONG Release() override`
- L46 _public prototype_ `virtual HRESULT RealTimeStylusEnabled(IRealTimeStylus* RealTimeStylus, ULONG TabletContextIDsCount, const TABLET_CONTEXT_ID* TabletContextIDs) override;` — IStylusPlugin
- L47 _public prototype_ `virtual HRESULT RealTimeStylusDisabled(IRealTimeStylus* RealTimeStylus, ULONG TabletContextIDsCount, const TABLET_CONTEXT_ID* TabletContextIDs) override;`
- L48 _public prototype_ `virtual HRESULT StylusDown(IRealTimeStylus* RealTimeStylus, const StylusInfo* StylusInfo, ULONG PropertyCount, LONG* PacketBuffer, LONG** InOutPkt) override;`
- L49 _public prototype_ `virtual HRESULT StylusUp(IRealTimeStylus* RealTimeStylus, const StylusInfo* StylusInfo, ULONG PropertyCount, LONG* PacketBuffer, LONG** InOutPkt) override;`
- L50 _public prototype_ `virtual HRESULT TabletAdded(IRealTimeStylus* RealTimeStylus, IInkTablet* Tablet) override;`
- L51 _public prototype_ `virtual HRESULT TabletRemoved(IRealTimeStylus* RealTimeStylus, LONG TabletIndex) override;`
- L52 _public prototype_ `virtual HRESULT InAirPackets(IRealTimeStylus* RealTimeStylus, const StylusInfo* StylusInfo, ULONG PacketCount, ULONG PacketBufferLength, LONG* PacketBuffer, ULONG* InOutPacketCount, LONG** InOutPacketBuffer) override;`
- L53 _public prototype_ `virtual HRESULT Packets(IRealTimeStylus* RealTimeStylus, const StylusInfo* StylusInfo, ULONG PacketCount, ULONG PacketBufferLength, LONG* PacketBuffer, ULONG* InOutPacketCount, LONG** InOutPacketBuffer) override;`
- L54 _public prototype_ `virtual HRESULT StylusInRange(IRealTimeStylus* RealTimeStylus, TABLET_CONTEXT_ID TabletContextID, STYLUS_ID StylusID) override;`
- L55 _public prototype_ `virtual HRESULT StylusOutOfRange(IRealTimeStylus* RealTimeStylus, TABLET_CONTEXT_ID TabletContextID, STYLUS_ID StylusID) override;`
- L56 _public prototype_ `virtual HRESULT StylusButtonDown(IRealTimeStylus* RealTimeStylus, STYLUS_ID StylusID, const GUID* GuidStylusButton, POINT* StylusPos) override;`
- L57 _public prototype_ `virtual HRESULT StylusButtonUp(IRealTimeStylus* RealTimeStylus, STYLUS_ID StylusID, const GUID* GuidStylusButton, POINT* StylusPos) override;`
- L58 _public prototype_ `virtual HRESULT CustomStylusDataAdded(IRealTimeStylus* RealTimeStylus, const GUID* GuidId, ULONG DataCount, const BYTE* Data) override;`
- L59 _public prototype_ `virtual HRESULT SystemEvent(IRealTimeStylus* RealTimeStylus, TABLET_CONTEXT_ID TabletContextID, STYLUS_ID StylusID, SYSTEM_EVENT Event, SYSTEM_EVENT_DATA EventData) override;`
- L60 _public prototype_ `virtual HRESULT Error(IRealTimeStylus* RealTimeStylus, IStylusPlugin* Plugin, RealTimeStylusDataInterest DataInterest, HRESULT ErrorCode, LONG_PTR* InternalKey) override;`
- L61 _public prototype_ `virtual HRESULT UpdateMapping(IRealTimeStylus* RealTimeStylus) override;`
- L62 _public prototype_ `virtual HRESULT DataInterest(RealTimeStylusDataInterest* DataInterest) override;`
- L65 _protected function_ `virtual FString GetName() const override`
- L68 _private member_ `int32 RefCount = 1;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace StylusInput` (scope `UE`)
- L7 _namespace_ `namespace RealTimeStylus` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInputRealTimeStylus/Private/RealTimeStylusPluginBase.h` (Private)


#### class `UE::StylusInput::RealTimeStylus::FRealTimeStylusPluginBase`  
`class FRealTimeStylusPluginBase`  
_L30-68_
- L33 _public prototype_ `bool AddEventHandler(IStylusInputEventHandler* EventHandler);`
- L34 _public prototype_ `bool RemoveEventHandler(IStylusInputEventHandler* EventHandler);`
- L35 _public function_ `int32 NumEventHandlers() const`
- L37 _public function_ `float GetPacketsPerSecond() const`
- L40 _protected prototype_ `FRealTimeStylusPluginBase(IStylusInputInstance* Instance, FGetWindowContextCallback&& GetWindowContextCallback, FUpdateTabletContextsCallback&& UpdateTabletContextsCallback, FUpdateStylusInfoCallback&& UpdateStylusInfoCallback);`
- L42 _protected prototype_ `virtual ~FRealTimeStylusPluginBase() = default;`
- L44 _protected prototype_ `virtual FString GetName() const = 0;`
- L46 _protected prototype_ `void DebugEvent(const FString& Message) const;`
- L48 _protected prototype_ `HRESULT ProcessDataInterest(RealTimeStylusDataInterest* DataInterest);`
- L49 _protected prototype_ `HRESULT ProcessError(RealTimeStylusDataInterest DataInterest, HRESULT ErrorCode);`
- L50 _protected prototype_ `HRESULT ProcessPackets(const StylusInfo* StylusInfo, uint32 PacketCount, uint32 PacketBufferLength, EPacketType Type, const int32* PacketBuffer);`
- L51 _protected prototype_ `HRESULT ProcessRealTimeStylusEnabled(IRealTimeStylus* RealTimeStylus, uint32 TabletContextIDsCount, const TABLET_CONTEXT_ID* TabletContextIDs);`
- L52 _protected prototype_ `HRESULT ProcessRealTimeStylusDisabled(IRealTimeStylus* RealTimeStylus, uint32 TabletContextIDsCount, const TABLET_CONTEXT_ID* TabletContextIDs);`
- L53 _protected prototype_ `HRESULT ProcessStylusInRange(IRealTimeStylus* RealTimeStylus, TABLET_CONTEXT_ID TabletContextID, STYLUS_ID StylusID);`
- L54 _protected prototype_ `HRESULT ProcessTabletAdded(IInkTablet* Tablet);`
- L55 _protected prototype_ `HRESULT ProcessTabletRemoved(LONG TabletIndex);`
- L58 _private prototype_ `const FPacketPropertyHandler* GetPacketPropertyHandlers(uint32 TabletContextID) const;`
- L59 _private prototype_ `HRESULT UpdateTabletContexts(IRealTimeStylus* RealTimeStylus, uint32 TabletContextIDsNum, const TABLET_CONTEXT_ID* TabletContextIDs);`
- L61 _private member_ `IStylusInputInstance *const Instance;`
- L62 _private member_ `FPacketStats PacketStats;`
- L63 _private member_ `FGetWindowContextCallback GetWindowContextCallback;`
- L64 _private member_ `FUpdateTabletContextsCallback UpdateTabletContextsCallback;`
- L65 _private member_ `FUpdateStylusInfoCallback UpdateStylusInfoCallback;`
- L66 _private member_ `FTabletContextContainer TabletContexts;`
- L67 _private member_ `TArray<IStylusInputEventHandler*> EventHandlers;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace StylusInput` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace StylusInput` (scope `UE`)
- L22 _namespace_ `namespace RealTimeStylus` (scope `UE::StylusInput`)
- L26 _delegate_ `DECLARE_DELEGATE_RetVal(const FWindowContext&, FGetWindowContextCallback);`
- L26 _prototype_ `DECLARE_DELEGATE_RetVal(const FWindowContext&, FGetWindowContextCallback);` (scope `UE::StylusInput::RealTimeStylus`)
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FUpdateTabletContextsCallback, const FTabletContextContainer&);`
- L27 _prototype_ `DECLARE_DELEGATE_OneParam(FUpdateTabletContextsCallback, const FTabletContextContainer&);` (scope `UE::StylusInput::RealTimeStylus`)
- L28 _delegate_ `DECLARE_DELEGATE_OneParam(FUpdateStylusInfoCallback, STYLUS_ID);`
- L28 _prototype_ `DECLARE_DELEGATE_OneParam(FUpdateStylusInfoCallback, STYLUS_ID);` (scope `UE::StylusInput::RealTimeStylus`)

### `Plugins/Editor/StylusInput/Source/StylusInputRealTimeStylus/Private/RealTimeStylusPluginSync.h` (Private)


#### class `UE::StylusInput::RealTimeStylus::FRealTimeStylusPluginSync`  
`class FRealTimeStylusPluginSync final : public IStylusSyncPlugin, public FRealTimeStylusPluginBase`  
_L9-79_
- inherits: `IStylusSyncPlugin,FRealTimeStylusPluginBase`
- L12 _public prototype_ `FRealTimeStylusPluginSync(IStylusInputInstance* Instance, FGetWindowContextCallback&& GetWindowContext, FUpdateTabletContextsCallback&& UpdateTabletContextsCallback, FUpdateStylusInfoCallback UpdateStylusInfoCallback, IStylusInputEventHandler* EventHandler);`
- L17 _public prototype_ `HRESULT CreateFreeThreadMarshaler();`
- L20 _public function_ `virtual HRESULT QueryInterface(REFIID InterfaceID, void** InterfaceObject) override` — IUnknown
- L38 _public function_ `virtual ULONG AddRef() override`
- L43 _public function_ `virtual ULONG Release() override`
- L53 _public prototype_ `virtual HRESULT RealTimeStylusEnabled(IRealTimeStylus* RealTimeStylus, ULONG TabletContextIDsCount, const TABLET_CONTEXT_ID* TabletContextIDs) override;` — IStylusPlugin
- L54 _public prototype_ `virtual HRESULT RealTimeStylusDisabled(IRealTimeStylus* RealTimeStylus, ULONG TabletContextIDsCount, const TABLET_CONTEXT_ID* TabletContextIDs) override;`
- L55 _public prototype_ `virtual HRESULT StylusDown(IRealTimeStylus* RealTimeStylus, const StylusInfo* StylusInfo, ULONG PropertyCount, LONG* PacketBuffer, LONG** InOutPkt) override;`
- L56 _public prototype_ `virtual HRESULT StylusUp(IRealTimeStylus* RealTimeStylus, const StylusInfo* StylusInfo, ULONG PropertyCount, LONG* PacketBuffer, LONG** InOutPkt) override;`
- L57 _public prototype_ `virtual HRESULT TabletAdded(IRealTimeStylus* RealTimeStylus, IInkTablet* Tablet) override;`
- L58 _public prototype_ `virtual HRESULT TabletRemoved(IRealTimeStylus* RealTimeStylus, LONG TabletIndex) override;`
- L59 _public prototype_ `virtual HRESULT InAirPackets(IRealTimeStylus* RealTimeStylus, const StylusInfo* StylusInfo, ULONG PacketCount, ULONG PacketBufferLength, LONG* PacketBuffer, ULONG* InOutPacketCount, LONG** InOutPacketBuffer) override;`
- L60 _public prototype_ `virtual HRESULT Packets(IRealTimeStylus* RealTimeStylus, const StylusInfo* StylusInfo, ULONG PacketCount, ULONG PacketBufferLength, LONG* PacketBuffer, ULONG* InOutPacketCount, LONG** InOutPacketBuffer) override;`
- L61 _public prototype_ `virtual HRESULT StylusInRange(IRealTimeStylus* RealTimeStylus, TABLET_CONTEXT_ID TabletContextID, STYLUS_ID StylusID) override;`
- L62 _public prototype_ `virtual HRESULT StylusOutOfRange(IRealTimeStylus* RealTimeStylus, TABLET_CONTEXT_ID TabletContextID, STYLUS_ID StylusID) override;`
- L63 _public prototype_ `virtual HRESULT StylusButtonDown(IRealTimeStylus* RealTimeStylus, STYLUS_ID StylusID, const GUID* GuidStylusButton, POINT* StylusPos) override;`
- L64 _public prototype_ `virtual HRESULT StylusButtonUp(IRealTimeStylus* RealTimeStylus, STYLUS_ID StylusID, const GUID* GuidStylusButton, POINT* StylusPos) override;`
- L65 _public prototype_ `virtual HRESULT CustomStylusDataAdded(IRealTimeStylus* RealTimeStylus, const GUID* GuidId, ULONG DataCount, const BYTE* Data) override;`
- L66 _public prototype_ `virtual HRESULT SystemEvent(IRealTimeStylus* RealTimeStylus, TABLET_CONTEXT_ID TabletContextID, STYLUS_ID StylusID, SYSTEM_EVENT Event, SYSTEM_EVENT_DATA EventData) override;`
- L67 _public prototype_ `virtual HRESULT Error(IRealTimeStylus* RealTimeStylus, IStylusPlugin* Plugin, RealTimeStylusDataInterest DataInterest, HRESULT ErrorCode, LONG_PTR* InternalKey) override;`
- L68 _public prototype_ `virtual HRESULT UpdateMapping(IRealTimeStylus* RealTimeStylus) override;`
- L69 _public prototype_ `virtual HRESULT DataInterest(RealTimeStylusDataInterest* DataInterest) override;`
- L73 _protected function_ `virtual FString GetName() const override` — FRealTimeStylusPluginBase
- L76 _private member_ `int32 RefCount = 1;`
- L78 _private member_ `IUnknown* FreeThreadedMarshaler = nullptr;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace StylusInput` (scope `UE`)
- L7 _namespace_ `namespace RealTimeStylus` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInputRealTimeStylus/Private/RealTimeStylusStats.h` (Private)


#### class `UE::StylusInput::RealTimeStylus::FPacketStats`  
`class FPacketStats`  
_L9-39_
- L12 _public function_ `void NewPacket()`
- L27 _public function_ `float GetPacketsPerSecond() const`
- L34 _private member_ `uint64 EarliestTimestamp = 0;`
- L35 _private member_ `uint64 LatestTimestamp = 0;`
- L36 _private member_ `uint32 NumPackets = 0;`
- L37 _private member_ `float PacketsPerSecond = 0.0f;`
- L38 _private member_ `const double CyclesPerSecond = 1.0 / FPlatformTime::GetSecondsPerCycle64();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace StylusInput` (scope `UE`)
- L7 _namespace_ `namespace RealTimeStylus` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInputRealTimeStylus/Private/RealTimeStylusTabletContext.h` (Private)


#### enum `UE::StylusInput::RealTimeStylus::EPacketPropertyType`  
`enum class EPacketPropertyType : int8`  
_L19-45_
- L21 _public enumerator_ `X = 0` — The x-coordinate in the tablet coordinate space. Each packet contains this property by default. The origin (0,0) of the tablet is the upper-left corner.
- L22 _public enumerator_ `Y` — The y-coordinate in the tablet coordinate space. Each packet contains this property by default. The origin (0,0) of the tablet is the upper-left corner.
- L23 _public enumerator_ `Z` — The z-coordinate or distance of the pen tip from the tablet surface. The TabletPropertyMetricUnit enumeration type determines the unit of measurement for this property.
- L24 _public enumerator_ `PacketStatus` — Contains one or more of the following flag values: The cursor is touching the drawing surface (Value = 1). The cursor is inverted. For example, the eraser end of the pen is pointing toward the surface (Value = 2). Not used (Value = 4). The barrel button is pressed (Value = 8).
- L25 _public enumerator_ `TimerTick` — The time the packet was generated in milliseconds since system start.
- L26 _public enumerator_ `SerialNumber` — The packet property for identifying the packet. This is the same value you use to retrieve the packet from the packet queue.
- L27 _public enumerator_ `NormalPressure` — The pressure of the pen tip perpendicular to the tablet surface. The greater the pressure on the pen tip, the more ink that is drawn.
- L28 _public enumerator_ `TangentPressure` — The pressure of the pen tip along the plane of the tablet surface.
- L29 _public enumerator_ `ButtonPressure` — The pressure on a pressure sensitive button.
- L30 _public enumerator_ `XTiltOrientation` — The angle between the y,z-plane and the pen and y-axis plane. Applies to a pen cursor. The value is 0 when the pen is perpendicular to the drawing surface and is positive when the pen is to the right of perpendicular.
- L31 _public enumerator_ `YTiltOrientation` — The angle between the x,z-plane and the pen and x-axis plane. Applies to a pen cursor. The value is 0 when the pen is perpendicular to the drawing surface and is positive when the pen is upward or away from the user.
- L32 _public enumerator_ `AzimuthOrientation` — The clockwise rotation of the cursor about the z-axis through a full circular range.
- L33 _public enumerator_ `AltitudeOrientation` — The angle between the axis of the pen and the surface of the tablet. The value is 0 when the pen is parallel to the surface and 90 when the pen is perpendicular to the surface. The values are negative when the pen is inverted.
- L34 _public enumerator_ `TwistOrientation` — The clockwise rotation of the cursor about its own axis.
- L35 _public enumerator_ `PitchRotation` — The packet property that indicates whether the tip is above or below a horizontal line that is perpendicular to the writing surface. Note: This requires a 3D digitizer. The value is positive if the tip is above the line and negative if it is below the line. For example, if you hold the pen in front 
- L36 _public enumerator_ `RollRotation` — The clockwise rotation of the pen around its own axis. Note: This requires a 3D digitizer.
- L37 _public enumerator_ `YawRotation` — The angle of the pen to the left or right around the center of its horizontal axis when the pen is horizontal. Note: This requires a 3D digitizer. If you hold the pen in front of you and write on an imaginary wall, zero yaw indicates that the pen is perpendicular to the wall. The value is negative i
- L38 _public enumerator_ `Width` — The width of the contact area on a touch digitizer.
- L39 _public enumerator_ `Height` — The height of the contact area on a touch digitizer.
- L40 _public enumerator_ `FingerContactConfidence` — The level of confidence that there was finger contact on a touch digitizer.
- L41 _public enumerator_ `DeviceContactID` — The device contact identifier for a packet.
- L43 _public enumerator_ `Num_Enumerators` — THIS IS NOT A VALID ENUMERATOR, BUT IT CAN BE USED TO QUERY HOW MANY PACKET PROPERTIES THERE ARE.
- L44 _public enumerator_ `Invalid_Enumerator = INDEX_NONE` — THIS IS NOT A VALID ENUMERATOR, BUT IT CAN BE USED TO INDICATE THAT A PACKET PROPERTY ENTRY IS INVALID.

#### enum `UE::StylusInput::RealTimeStylus::ETabletPropertyMetricUnit`  
`enum class ETabletPropertyMetricUnit : int8`  
_L47-60_
- L49 _public enumerator_ `Default` — Units are unknown.
- L50 _public enumerator_ `Inches`
- L51 _public enumerator_ `Centimeters`
- L52 _public enumerator_ `Degrees`
- L53 _public enumerator_ `Radians`
- L54 _public enumerator_ `Seconds`
- L55 _public enumerator_ `Pounds`
- L56 _public enumerator_ `Grams`
- L58 _public enumerator_ `Num_Enumerators` — THIS IS NOT A VALID ENUMERATOR, BUT IT CAN BE USED TO QUERY HOW MANY PACKET PROPERTIES THERE ARE.
- L59 _public enumerator_ `Invalid_Enumerator = INDEX_NONE` — THIS IS NOT A VALID ENUMERATOR, BUT IT CAN BE USED TO INDICATE THAT A PACKET PROPERTY ENTRY IS INVALID.

#### struct `UE::StylusInput::RealTimeStylus::FPacketProperty`  
`struct FPacketProperty`  
_L62-69_
- L64 _public member_ `EPacketPropertyType Type = EPacketPropertyType::Invalid_Enumerator;`
- L65 _public member_ `ETabletPropertyMetricUnit MetricUnit = ETabletPropertyMetricUnit::Default;`
- L66 _public member_ `int32 Minimum = 0;`
- L67 _public member_ `int32 Maximum = 0;`
- L68 _public member_ `float Resolution = 0.0f;`

#### struct `UE::StylusInput::RealTimeStylus::FPacketPropertyHandler`  
`struct FPacketPropertyHandler`  
_L71-78_
- L73 _public typedef_ `using FFuncSetProperty = void(FStylusInputPacket&, int32, const int8*);`
- L74 _public member_ `FFuncSetProperty* SetProperty = nullptr;`
- L76 _public member_ `static constexpr int32 SetPropertyDataBufferLength = 24;`
- L77 _public member_ `int8 SetPropertyData[SetPropertyDataBufferLength];`

#### struct `UE::StylusInput::RealTimeStylus::FPacketPropertyConstant`  
`struct FPacketPropertyConstant`  
_L80-85_
- L82 _public member_ `EPacketPropertyType PacketPropertyType;`
- L83 _public member_ `GUID Guid;`
- L84 _public member_ `const wchar_t* StrGuid;`

#### struct `UE::StylusInput::RealTimeStylus::FWindowContext`  
`struct FWindowContext`  
_L89-94_
- L91 _public member_ `FVector2d XYScale;`
- L92 _public member_ `FVector2d XYMaximum;`
- L93 _public member_ `FVector2d WindowSize;`

#### class `UE::StylusInput::RealTimeStylus::FTabletContext`  
`class FTabletContext final : public IStylusInputTabletContext`  
_L96-126_
- inherits: `IStylusInputTabletContext`
- L99 _public function_ `explicit FTabletContext(const uint32 ID) : ID(ID)`
- L103 _public function_ `virtual uint32 GetID() const override`
- L105 _public function_ `virtual FString GetName() const override`
- L114 _public function_ `virtual FIntRect GetInputRectangle() const override`
- L115 _public function_ `virtual ETabletHardwareCapabilities GetHardwareCapabilities() const override`
- L116 _public function_ `virtual ETabletSupportedProperties GetSupportedProperties() const override`
- L118 _public member_ `uint32 ID = 0;`
- L119 _public member_ `FString Name;`
- L120 _public member_ `FString PlugAndPlayID;`
- L121 _public member_ `FIntRect InputRectangle;`
- L122 _public member_ `ETabletSupportedProperties SupportedProperties = ETabletSupportedProperties::None;`
- L123 _public member_ `ETabletHardwareCapabilities HardwareCapabilities = ETabletHardwareCapabilities::None;`
- L124 _public member_ `FPacketProperty PacketProperties[static_cast<uint32>(EPacketPropertyType::Num_Enumerators)] = {};`
- L125 _public member_ `FPacketPropertyHandler PacketPropertyHandlers[static_cast<uint32>(EPacketPropertyType::Num_Enumerators)] = {};`

#### class `UE::StylusInput::RealTimeStylus::FStylusButton`  
`class FStylusButton final : public IStylusInputStylusButton`  
_L131-139_
- inherits: `IStylusInputStylusButton`
- L134 _public function_ `virtual FString GetID() const override`
- L135 _public function_ `virtual FString GetName() const override`
- L137 _public member_ `FString ID;`
- L138 _public member_ `FString Name;`

#### class `UE::StylusInput::RealTimeStylus::FStylusInfo`  
`class FStylusInfo final : public IStylusInputStylusInfo`  
_L141-160_
- inherits: `IStylusInputStylusInfo`
- L144 _public function_ `explicit FStylusInfo(const uint32 ID) : ID(ID)`
- L148 _public function_ `virtual uint32 GetID() const override`
- L149 _public function_ `virtual FString GetName() const override`
- L150 _public function_ `virtual uint32 GetNumButtons() const override`
- L152 _public function_ `virtual const IStylusInputStylusButton* GetButton(int32 Index) const override`
- L157 _public member_ `uint32 ID = 0;`
- L158 _public member_ `FString Name;`
- L159 _public member_ `TArray<FStylusButton> Buttons;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace StylusInput` (scope `UE`)
- L17 _namespace_ `namespace RealTimeStylus` (scope `UE::StylusInput`)
- L87 _externvar_ `extern FPacketPropertyConstant PacketPropertyConstants[static_cast<uint32>(EPacketPropertyType::Num_Enumerators)];` (scope `UE::StylusInput::RealTimeStylus`)
- L128 _typedef_ `using FTabletContextContainer = Private::TSharedRefDataContainer<FTabletContext, false>;` (scope `UE::StylusInput::RealTimeStylus`)
- L129 _typedef_ `using FTabletContextThreadSafeContainer = Private::TSharedRefDataContainer<FTabletContext, true>;` (scope `UE::StylusInput::RealTimeStylus`)
- L162 _typedef_ `using FStylusInfoThreadSafeContainer = Private::TSharedRefDataContainer<FStylusInfo, true>;` (scope `UE::StylusInput::RealTimeStylus`)

### `Plugins/Editor/StylusInput/Source/StylusInputRealTimeStylus/Private/RealTimeStylusUtils.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace StylusInput` (scope `UE`)
- L7 _namespace_ `namespace RealTimeStylus` (scope `UE::StylusInput`)
- L9 _prototype_ `void LogCOMError(const FString& Preamble, HRESULT Result);` (scope `UE::StylusInput::RealTimeStylus`)
- L11 _function_ `inline bool Succeeded(const HRESULT Result, const FString& LogPreamble)` (scope `UE::StylusInput::RealTimeStylus`)
- L21 _function_ `inline bool Failed(const HRESULT Result, const FString& LogPreamble)` (scope `UE::StylusInput::RealTimeStylus`)
