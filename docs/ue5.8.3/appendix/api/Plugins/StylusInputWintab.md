# Plugins / StylusInputWintab

- module root: `Plugins/Editor/StylusInput/Source/StylusInputWintab`
- headers: 7; symbols: 257
- symbol kinds: class=10, enum=5, enumerator=37, function=31, macro=5, member=82, namespace=23, prototype=48, struct=5, typedef=11

### `Plugins/Editor/StylusInput/Source/StylusInputWintab/Private/WintabAPI.h` (Private)


#### struct `UE::StylusInput::Wintab::FWintabInterfaceInfo`  
`struct FWintabInterfaceInfo`  
_L27-44_
- L35 _public member_ `FString ID;`
- L36 _public member_ `FVersion SpecificationVersion = { 0, 0 };`
- L37 _public member_ `FVersion ImplementationVersion = { 0, 0 };`
- L38 _public member_ `uint32 MaximumNumberOfCursorTypes = 0;`
- L39 _public member_ `uint32 MaximumNumberOfContexts = 0;`
- L40 _public member_ `bool bSupportsPacketMessages = false;`
- L41 _public member_ `bool bSupportsCursorChangeMessages = false;`
- L43 _public member_ `mutable uint32 NumberOfDevices = 0;`

#### struct `UE::StylusInput::Wintab::FWintabInterfaceInfo::FVersion`  
`struct FVersion`  
_L29-33_
- L31 _public member_ `uint16 Major;`
- L32 _public member_ `uint16 Minor;`

#### class `UE::StylusInput::Wintab::FWintabAPI`  
`class FWintabAPI`  
_L46-91_
- L49 _public prototype_ `static bool DriverIsAvailable();`
- L51 _public prototype_ `static FName GetName();`
- L52 _public prototype_ `static const FWintabAPI& GetInstance();`
- L54 _public prototype_ `bool IsValid() const;`
- L56 _public prototype_ `void LogValidityDiagnostics() const;`
- L58 _public prototype_ `void UpdateNumberOfDevices() const;`
- L60 _public typedef_ `using FFuncGetWindowRect = BOOL(HWND, LPRECT);`
- L61 _public member_ `FFuncGetWindowRect* GetWindowRect = nullptr;`
- L63 _public typedef_ `using FFuncGetSystemMetrics = int(int);`
- L64 _public member_ `FFuncGetSystemMetrics* GetSystemMetrics = nullptr;`
- L66 _public typedef_ `using FFuncWtInfo = UINT(UINT, UINT, LPVOID);`
- L67 _public member_ `FFuncWtInfo* WtInfo = nullptr;`
- L69 _public typedef_ `using FFuncWtOpen = HCTX(HWND, LPLOGCONTEXT, BOOL);`
- L70 _public member_ `FFuncWtOpen* WtOpen = nullptr;`
- L72 _public typedef_ `using FFuncWtClose = BOOL(HCTX);`
- L73 _public member_ `FFuncWtClose* WtClose = nullptr;`
- L75 _public typedef_ `using FFuncWtOverlap = BOOL(HCTX, BOOL);`
- L76 _public member_ `FFuncWtOverlap* WtOverlap = nullptr;`
- L78 _public typedef_ `using FFuncWtPacket = BOOL(HCTX, UINT, LPVOID);`
- L79 _public member_ `FFuncWtPacket* WtPacket = nullptr;`
- L81 _public member_ `FWintabInterfaceInfo InterfaceInfo;`
- L85 _private prototype_ `FWintabAPI();`
- L86 _private prototype_ `~FWintabAPI();`
- L88 _private prototype_ `void QueryInterfaceInfo();`
- L90 _private member_ `TArray<void*> DllHandles;`

#### class `UE::StylusInput::Wintab::FWintabInfoOutputBuffer`  
`class FWintabInfoOutputBuffer`  
_L110-133_
- L113 _public function_ `TCHAR* Allocate(UINT, UINT)`
- L125 _public function_ `static UINT SizeInBytes()`
- L132 _private member_ `TUniquePtr<TCHAR[]> Buffer;`
- L140 _public function_ `FWintabInfoOutputBuffer() : WintabAPI(FWintabAPI::GetInstance())`
- L145 _public function_ `TCHAR* Allocate(const UINT Category, const UINT Index)`
- L164 _public function_ `UINT SizeInBytes() const`
- L170 _private member_ `const FWintabAPI& WintabAPI;`
- L172 _private member_ `UINT Size = 0;`

#### enum `UE::StylusInput::Wintab::FWintabInfoOutputBuffer::(anonymous)`  
`enum`  
_L131-131_

#### class `UE::StylusInput::Wintab::FWintabInfoOutputBuffer`  
`class FWintabInfoOutputBuffer`  
_L137-173_
- L113 _public function_ `TCHAR* Allocate(UINT, UINT)`
- L125 _public function_ `static UINT SizeInBytes()`
- L132 _private member_ `TUniquePtr<TCHAR[]> Buffer;`
- L140 _public function_ `FWintabInfoOutputBuffer() : WintabAPI(FWintabAPI::GetInstance())`
- L145 _public function_ `TCHAR* Allocate(const UINT Category, const UINT Index)`
- L164 _public function_ `UINT SizeInBytes() const`
- L170 _private member_ `const FWintabAPI& WintabAPI;`
- L172 _private member_ `UINT Size = 0;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define WIN32_LEAN_AND_MEAN`
- L17 _macro_ `#define PACKETDATA (/*PK_CONTEXT |*/ PK_STATUS | PK_TIME | /*PK_CHANGED |*/ PK_SERIAL_NUMBER | PK_CURSOR | PK_BUTTONS | PK_X | PK_Y | PK_Z | PK_NORMAL_PRESSURE | PK_TANGENT_PRESSURE | PK_ORIENTATION | PK_ROTATION)`
- L18 _macro_ `#define PACKETMODE PK_BUTTONS`
- L23 _macro_ `#define WTINFO_WORKAROUND_FOR_OUTPUT_BUFFER_SIZE_BUG 1`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace StylusInput` (scope `UE`)
- L25 _namespace_ `namespace Wintab` (scope `UE::StylusInput`)
- L93 _function_ `inline uint32 HctxToUint32(const HCTX Hctx)` (scope `UE::StylusInput::Wintab`)
- L98 _function_ `inline float Fix32ToFloat(const FIX32 Value)` (scope `UE::StylusInput::Wintab`)
- L131 _enumerator_ `enum { Size = 8192 }; TUniquePtr<TCHAR[]> Buffer;` (scope `UE::StylusInput::Wintab::FWintabInfoOutputBuffer::__anonf74483070103`)

### `Plugins/Editor/StylusInput/Source/StylusInputWintab/Private/WintabInstance.h` (Private)


#### class `UE::StylusInput::Wintab::FWintabInstance`  
`class FWintabInstance : public IStylusInputInstance`  
_L25-90_
- inherits: `IStylusInputInstance`
- L28 _public prototype_ `explicit FWintabInstance(uint32 ID, HWND OSWindowHandle, FWintabInterface& Interface);`
- L31 _public prototype_ `virtual bool AddEventHandler(IStylusInputEventHandler* EventHandler, EEventHandlerThread Thread) override;`
- L32 _public prototype_ `virtual bool RemoveEventHandler(IStylusInputEventHandler* EventHandler) override;`
- L34 _public prototype_ `virtual const TSharedPtr<IStylusInputTabletContext> GetTabletContext(uint32 TabletContextID) override;`
- L35 _public prototype_ `virtual const TSharedPtr<IStylusInputStylusInfo> GetStylusInfo(uint32 StylusID) override;`
- L37 _public prototype_ `virtual float GetPacketsPerSecond(EEventHandlerThread EventHandlerThread) const override;`
- L39 _public prototype_ `virtual FName GetInterfaceName() override;`
- L40 _public prototype_ `virtual FText GetName() override;`
- L42 _public prototype_ `virtual bool WasInitializedSuccessfully() const override;`
- L44 _public function_ `HWND GetOSWindowHandle() const`
- L46 _public prototype_ `void OnPacket(HCTX TabletContextHandle, UINT SerialNumber);`
- L47 _public prototype_ `void OnProximity(HCTX TabletContextHandle, LPARAM LParam);`
- L48 _public prototype_ `void OnCursorChange(HCTX TabletContextHandle, UINT SerialNumber);`
- L49 _public prototype_ `void OnInfoChange();`
- L50 _public prototype_ `void OnWindowActivated();`
- L51 _public prototype_ `void OnWindowPosChanged();`
- L52 _public prototype_ `void OnDisplayChange();`
- L53 _public prototype_ `void OnDpiChanged();`
- L56 _private prototype_ `const FTabletContext* GetTabletContextInternal(uint32 TabletContextID) const;`
- L57 _private prototype_ `uint32 GetStylusID(uint32 TabletContextID, uint32 CursorIndex);`
- L59 _private prototype_ `void ClearTabletContexts();`
- L60 _private prototype_ `void UpdateTabletContexts();`
- L61 _private prototype_ `void UpdateWindowRect();`
- L63 _private prototype_ `void ProcessCursorChange(uint32 TabletContextID, const PACKET& WintabPacket);`
- L64 _private prototype_ `FStylusInputPacket ProcessPacket(uint32 TabletContextID, const PACKET& WintabPacket);`
- L66 _private prototype_ `void DebugEvent(const FString& Message);`
- L68 _private member_ `const uint32 ID;`
- L69 _private member_ `const FWintabAPI& WintabAPI;`
- L70 _private member_ `FWintabInterface& Interface;`
- L71 _private member_ `const HWND OSWindowHandle;`
- L72 _private member_ `RECT WindowRect = {};`
- L74 _private member_ `FTabletContextContainer TabletContexts;`
- L75 _private member_ `FStylusInfoContainer StylusInfos;`
- L77 _private member_ `TArray<IStylusInputEventHandler*> EventHandlers;`
- L78 _private member_ `FPacketStats PacketStats;`
- L80 _private member_ `uint32 CurrentStylusID = 0;`
- L81 _private member_ `TArray<TTuple<uint64, uint32>> CursorIDToStylusIDMappings;`
- L83 _private member_ `bool bCursorChange = false;`
- L84 _private member_ `bool bLastPacketOnDigitizer = false;`
- L87 _private member_ `uint32 CursorChangeTabletContextID = 0;`
- L88 _private member_ `uint32 CursorChangeSerialNumber = 0;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define CHECK_MESSAGE_ORDER_ASSUMPTIONS NDEBUG`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace StylusInput` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace StylusInput` (scope `UE`)
- L20 _namespace_ `namespace Wintab` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInputWintab/Private/WintabInterface.h` (Private)


#### class `UE::StylusInput::Wintab::FWintabInterface`  
`class FWintabInterface : public IStylusInputInterface`  
_L17-64_
- inherits: `IStylusInputInterface`
- L20 _public prototype_ `FWintabInterface();`
- L21 _public prototype_ `virtual ~FWintabInterface();`
- L23 _public prototype_ `virtual FName GetName() const override;`
- L25 _public prototype_ `virtual IStylusInputInstance* CreateInstance(SWindow& Window) override;`
- L26 _public prototype_ `virtual bool ReleaseInstance(IStylusInputInstance* Instance) override;`
- L28 _public prototype_ `void RegisterTabletContext(HCTX Handle, FWintabInstance* Instance);`
- L29 _public prototype_ `void UnregisterTabletContext(HCTX Handle);`
- L31 _public prototype_ `FWintabInstance* FindInstanceByHctx(HCTX Handle) const;`
- L32 _public prototype_ `FWintabInstance* FindInstanceByHwnd(HWND Window) const;`
- L35 _public function_ `template <typename FuncType> void ForEachInstance(FuncType&& Func) const`
- L49 _private prototype_ `static TUniquePtr<IStylusInputInterface> Create();`
- L57 _private member_ `FWintabMessageHandler MessageHandler;`
- L59 _private member_ `TMap<HWND, FWintabInstance*> InstancesByHwnd;`
- L60 _private member_ `TMap<HCTX, FWintabInstance*> InstancesByHctx;`
- L62 _private member_ `TMap<SWindow*, FRefCountedInstance> Instances;`
- L63 _private member_ `uint32 NextInstanceID = 0;`

#### struct `UE::StylusInput::Wintab::FWintabInterface::FRefCountedInstance`  
`struct FRefCountedInstance`  
_L51-55_
- L53 _public member_ `TUniquePtr<FWintabInstance> Instance;`
- L54 _public member_ `int32 RefCount;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace StylusInput` (scope `UE`)
- L13 _namespace_ `namespace Wintab` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInputWintab/Private/WintabMessageHandler.h` (Private)


#### class `UE::StylusInput::Wintab::FWintabMessageHandler`  
`class FWintabMessageHandler : public IWindowsMessageHandler`  
_L12-23_
- inherits: `IWindowsMessageHandler`
- L15 _public prototype_ `FWintabMessageHandler(FWintabInterface& Interface);`
- L16 _public prototype_ `virtual ~FWintabMessageHandler() = default;`
- L18 _public prototype_ `virtual bool ProcessMessage(HWND Hwnd, uint32 Msg, WPARAM WParam, LPARAM LParam, int32& OutResult) override;`
- L21 _private member_ `FWintabInterface& Interface;`
- L22 _private member_ `const FWintabAPI& WintabAPI;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace StylusInput` (scope `UE`)
- L7 _namespace_ `namespace Wintab` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInputWintab/Private/WintabStats.h` (Private)


#### class `UE::StylusInput::Wintab::FPacketStats`  
`class FPacketStats`  
_L9-60_
- L12 _public function_ `void NewPacket(uint32 SerialNumber)`
- L30 _public function_ `void InvalidPacket()`
- L35 _public function_ `float GetPacketsPerSecond() const`
- L41 _public function_ `uint32 GetNumInvalidPackets() const`
- L46 _public function_ `uint32 GetNumLostPackets() const`
- L52 _private member_ `uint64 EarliestTimestamp = 0;`
- L53 _private member_ `uint64 LatestTimestamp = 0;`
- L54 _private member_ `uint32 LatestSerialNumber = -1;`
- L55 _private member_ `uint32 NumPackets = 0;`
- L56 _private member_ `uint32 NumInvalidPackets = 0;`
- L57 _private member_ `uint32 NumLostPackets = 0;`
- L58 _private member_ `float PacketsPerSecond = 0.0f;`
- L59 _private member_ `const double CyclesPerSecond = 1.0 / FPlatformTime::GetSecondsPerCycle64();`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace StylusInput` (scope `UE`)
- L7 _namespace_ `namespace Wintab` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInputWintab/Private/WintabStylus.h` (Private)


#### enum `UE::StylusInput::Wintab::ECursorType`  
`enum class ECursorType : uint16`  
_L10-20_
- L12 _public enumerator_ `GeneralStylus = 0x0802`
- L13 _public enumerator_ `Airbrush = 0x0902`
- L14 _public enumerator_ `ArtPen = 0x0804`
- L15 _public enumerator_ `FourDMouse = 0x0004`
- L16 _public enumerator_ `FiveButtonPuck = 0x0006`
- L18 _public enumerator_ `CursorTypeMask = 0x0F06` — Use this to mask any values coming from the Wintab API to get a valid cursor type.
- L19 _public enumerator_ `CursorIdMask = 0xFF6` — Use this to mask any values coming from the Wintab API to differentiate between different devices, incl. colors.

#### enum `UE::StylusInput::Wintab::ECursorIndexType`  
`enum class ECursorIndexType : int8`  
_L51-62_
- L53 _public enumerator_ `PuckDevice1 = 0`
- L54 _public enumerator_ `StylusDevice1 = 1`
- L55 _public enumerator_ `InvertedStylusDevice1 = 2`
- L56 _public enumerator_ `PuckDevice2 = 3`
- L57 _public enumerator_ `StylusDevice2 = 4`
- L58 _public enumerator_ `InvertedStylusDevice2 = 5`
- L60 _public enumerator_ `Num_Enumerators`
- L61 _public enumerator_ `Invalid_Enumerator = INDEX_NONE`

#### class `UE::StylusInput::Wintab::FStylusButton`  
`class FStylusButton final : public IStylusInputStylusButton`  
_L69-77_
- inherits: `IStylusInputStylusButton`
- L72 _public function_ `virtual FString GetID() const override`
- L73 _public function_ `virtual FString GetName() const override`
- L75 _public member_ `FString ID;`
- L76 _public member_ `FString Name;`

#### class `UE::StylusInput::Wintab::FStylusInfo`  
`class FStylusInfo final : public IStylusInputStylusInfo`  
_L79-104_
- inherits: `IStylusInputStylusInfo`
- L82 _public prototype_ `FStylusInfo() = default;`
- L84 _public function_ `explicit FStylusInfo(const uint32 ID) : ID(ID)`
- L89 _public function_ `virtual uint32 GetID() const override`
- L90 _public function_ `virtual FString GetName() const override`
- L91 _public function_ `virtual uint32 GetNumButtons() const override`
- L93 _public function_ `virtual const IStylusInputStylusButton* GetButton(int32 Index) const override`
- L98 _public member_ `uint32 ID = 0;` — This will almost always be the physical ID, unless there is a rare collision between physical IDs of cursors of different types.
- L99 _public member_ `FString Name;`
- L100 _public member_ `TArray<FStylusButton> Buttons;`
- L102 _public member_ `uint32 WintabPhysicalID = -1;`
- L103 _public member_ `uint16 WintabCursorType = -1;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace StylusInput` (scope `UE`)
- L8 _namespace_ `namespace Wintab` (scope `UE::StylusInput`)
- L22 _function_ `inline uint16 MaskCursorType(const UINT CursorType)` (scope `UE::StylusInput::Wintab`)
- L27 _function_ `inline uint16 MaskCursorId(const UINT CursorType)` (scope `UE::StylusInput::Wintab`)
- L32 _function_ `inline FString MaskedCursorTypeToString(uint16 MaskedCursorType)` (scope `UE::StylusInput::Wintab`)
- L64 _function_ `inline bool CursorIsInverted(ECursorIndexType Type)` (scope `UE::StylusInput::Wintab`)
- L106 _typedef_ `using FStylusInfoContainer = Private::TSharedRefDataContainer<FStylusInfo, false>;` (scope `UE::StylusInput::Wintab`)
- L107 _typedef_ `using FStylusInfoThreadSafeContainer = Private::TSharedRefDataContainer<FStylusInfo, false>;` (scope `UE::StylusInput::Wintab`)

### `Plugins/Editor/StylusInput/Source/StylusInputWintab/Private/WintabTabletContext.h` (Private)


#### enum `UE::StylusInput::Wintab::EPacketPropertyType`  
`enum class EPacketPropertyType : int8`  
_L14-32_
- L16 _public enumerator_ `Status = 0`
- L17 _public enumerator_ `Time`
- L18 _public enumerator_ `Changed`
- L19 _public enumerator_ `SerialNumber`
- L20 _public enumerator_ `Cursor`
- L21 _public enumerator_ `Buttons`
- L22 _public enumerator_ `X`
- L23 _public enumerator_ `Y`
- L24 _public enumerator_ `Z`
- L25 _public enumerator_ `NormalPressure`
- L26 _public enumerator_ `TangentPressure`
- L27 _public enumerator_ `Orientation`
- L28 _public enumerator_ `Rotation`
- L30 _public enumerator_ `Num_Enumerators` — THIS IS NOT A VALID ENUMERATOR, BUT IT CAN BE USED TO QUERY HOW MANY PACKET PROPERTIES THERE ARE.
- L31 _public enumerator_ `Invalid_Enumerator = INDEX_NONE` — THIS IS NOT A VALID ENUMERATOR, BUT IT CAN BE USED TO INDICATE THAT A PACKET PROPERTY ENTRY IS INVALID.

#### enum `UE::StylusInput::Wintab::ETabletPropertyMetricUnit`  
`enum class ETabletPropertyMetricUnit : int8`  
_L34-43_
- L36 _public enumerator_ `Default` — Units are unknown.
- L37 _public enumerator_ `Inches`
- L38 _public enumerator_ `Centimeters`
- L39 _public enumerator_ `Circle`
- L41 _public enumerator_ `Num_Enumerators` — THIS IS NOT A VALID ENUMERATOR, BUT IT CAN BE USED TO QUERY HOW MANY PACKET PROPERTIES THERE ARE.
- L42 _public enumerator_ `Invalid_Enumerator = INDEX_NONE` — THIS IS NOT A VALID ENUMERATOR, BUT IT CAN BE USED TO INDICATE THAT A PACKET PROPERTY ENTRY IS INVALID.

#### struct `UE::StylusInput::Wintab::FPacketProperty`  
`struct FPacketProperty`  
_L45-52_
- L47 _public member_ `EPacketPropertyType Type = EPacketPropertyType::Invalid_Enumerator;`
- L48 _public member_ `ETabletPropertyMetricUnit MetricUnit = ETabletPropertyMetricUnit::Default;`
- L49 _public member_ `int32 Minimum = 0;`
- L50 _public member_ `int32 Maximum = 0;`
- L51 _public member_ `float Resolution = 0.0f;`

#### struct `UE::StylusInput::Wintab::FPacketPropertyHandler`  
`struct FPacketPropertyHandler`  
_L54-61_
- L56 _public typedef_ `using FFuncSetProperty = void(FStylusInputPacket&, const PACKET&, const int8*);`
- L57 _public member_ `FFuncSetProperty* SetProperty = nullptr;`
- L59 _public member_ `static constexpr int32 SetPropertyDataBufferLength = 20;`
- L60 _public member_ `int8 SetPropertyData[SetPropertyDataBufferLength];`

#### class `UE::StylusInput::Wintab::FTabletContext`  
`class FTabletContext final : public IStylusInputTabletContext`  
_L63-99_
- inherits: `IStylusInputTabletContext`
- L66 _public function_ `explicit FTabletContext(const uint32 ID) : ID(ID)`
- L70 _public function_ `virtual uint32 GetID() const override`
- L72 _public function_ `virtual FString GetName() const override`
- L81 _public function_ `virtual FIntRect GetInputRectangle() const override`
- L82 _public function_ `virtual ETabletHardwareCapabilities GetHardwareCapabilities() const override`
- L83 _public function_ `virtual ETabletSupportedProperties GetSupportedProperties() const override`
- L85 _public member_ `uint32 ID = 0;`
- L86 _public member_ `FString Name;`
- L87 _public member_ `FString PlugAndPlayID;`
- L88 _public member_ `FIntRect InputRectangle;`
- L89 _public member_ `ETabletSupportedProperties SupportedProperties = ETabletSupportedProperties::None;`
- L90 _public member_ `ETabletHardwareCapabilities HardwareCapabilities = ETabletHardwareCapabilities::None;`
- L91 _public member_ `uint32 NumPacketProperties = 0;`
- L92 _public member_ `FPacketProperty PacketProperties[static_cast<uint32>(EPacketPropertyType::Num_Enumerators)] = {};`
- L93 _public member_ `FPacketPropertyHandler PacketPropertyHandlers[static_cast<uint32>(EPacketPropertyType::Num_Enumerators)] = {};`
- L95 _public member_ `UINT WintabContextIndex = -1;`
- L96 _public member_ `HCTX WintabContextHandle = nullptr;`
- L97 _public member_ `uint8 WintabFirstCursor = -1;`
- L98 _public member_ `uint8 WintabNumCursors = -1;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace StylusInput` (scope `UE`)
- L12 _namespace_ `namespace Wintab` (scope `UE::StylusInput`)
- L101 _typedef_ `using FTabletContextContainer = Private::TSharedRefDataContainer<FTabletContext, false>;` (scope `UE::StylusInput::Wintab`)
