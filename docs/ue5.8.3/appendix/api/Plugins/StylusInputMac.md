# Plugins / StylusInputMac

- module root: `Plugins/Editor/StylusInput/Source/StylusInputMac`
- headers: 5; symbols: 175
- symbol kinds: class=7, enum=2, enumerator=33, externvar=1, function=21, member=49, namespace=22, prototype=33, struct=4, typedef=3

### `Plugins/Editor/StylusInput/Source/StylusInputMac/Private/MacInstance.h` (Private)


#### class `UE::StylusInput::Mac::FMacInstance`  
`class FMacInstance : public IStylusInputInstance`  
_L22-58_
- inherits: `IStylusInputInstance`
- L25 _public prototype_ `explicit FMacInstance(uint32 ID, const FCocoaWindow* OSWindowHandle);`
- L28 _public prototype_ `virtual bool AddEventHandler(IStylusInputEventHandler* EventHandler, EEventHandlerThread Thread) override;`
- L29 _public prototype_ `virtual bool RemoveEventHandler(IStylusInputEventHandler* EventHandler) override;`
- L31 _public prototype_ `virtual const TSharedPtr<IStylusInputTabletContext> GetTabletContext(uint32 TabletContextID) override;`
- L32 _public prototype_ `virtual const TSharedPtr<IStylusInputStylusInfo> GetStylusInfo(uint32 StylusID) override;`
- L34 _public prototype_ `virtual float GetPacketsPerSecond(EEventHandlerThread EventHandlerThread) const override;`
- L36 _public prototype_ `virtual FName GetInterfaceName() override;`
- L37 _public prototype_ `virtual FText GetName() override;`
- L39 _public prototype_ `virtual bool WasInitializedSuccessfully() const override;`
- L42 _private prototype_ `void EnableEventHandler(EEventHandlerThread EventHandlerThread, IStylusInputEventHandler* EventHandler);`
- L43 _private prototype_ `void DisableEventHandler(EEventHandlerThread EventHandlerThread);`
- L46 _private prototype_ `void SetupTabletContexts();` — There isn't such a thing as a "Tablet context" with NSEvent. Instead, we'll store all the devices known by the user computer and sort the events by ID
- L48 _private prototype_ `void UpdateTabletContexts(FTabletContextContainer& InTabletContexts);`
- L50 _private member_ `const FCocoaWindow* CocoaWindow;`
- L52 _private member_ `TUniquePtr<FNSEventHandler> NSEventHandler;`
- L54 _private member_ `FTabletContextContainer TabletContexts;`
- L55 _private member_ `FStylusInfoContainer StylusInfo;`
- L57 _private member_ `const uint32 ID;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace StylusInput` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace StylusInput` (scope `UE`)
- L18 _namespace_ `namespace Mac` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInputMac/Private/MacInterface.h` (Private)


#### class `UE::StylusInput::Mac::FMacInterface`  
`class FMacInterface : public IStylusInputInterface`  
_L19-40_
- inherits: `IStylusInputInterface`
- L22 _public prototype_ `virtual FName GetName() const override;`
- L24 _public prototype_ `virtual IStylusInputInstance* CreateInstance(SWindow& Window) override;`
- L25 _public prototype_ `virtual bool ReleaseInstance(IStylusInputInstance* Instance) override;`
- L30 _private prototype_ `static TUniquePtr<IStylusInputInterface> Create();`
- L38 _private member_ `TMap<SWindow*, FRefCountedInstance> Instances;`
- L39 _private member_ `uint32 NextInstanceID = 0;`

#### struct `UE::StylusInput::Mac::FMacInterface::FRefCountedInstance`  
`struct FRefCountedInstance`  
_L32-36_
- L34 _public member_ `TUniquePtr<FMacInstance> Instance;`
- L35 _public member_ `int32 RefCount;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace StylusInput` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::StylusInput`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace StylusInput` (scope `UE`)
- L15 _namespace_ `namespace Mac` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInputMac/Private/MacStats.h` (Private)


#### class `UE::StylusInput::Mac::FPacketStats`  
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
- L7 _namespace_ `namespace Mac` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInputMac/Private/MacTabletContext.h` (Private)


#### enum `UE::StylusInput::Mac::EPacketPropertyType`  
`enum class EPacketPropertyType : int8`  
_L13-39_
- L15 _public enumerator_ `X = 0` — The x-coordinate in the tablet coordinate space. Each packet contains this property by default. The origin (0,0) of the tablet is the upper-left corner.
- L16 _public enumerator_ `Y` — The y-coordinate in the tablet coordinate space. Each packet contains this property by default. The origin (0,0) of the tablet is the upper-left corner.
- L17 _public enumerator_ `Z` — The z-coordinate or distance of the pen tip from the tablet surface. The TabletPropertyMetricUnit enumeration type determines the unit of measurement for this property.
- L18 _public enumerator_ `PacketStatus` — Contains one or more of the following flag values: The cursor is touching the drawing surface (Value = 1). The cursor is inverted. For example, the eraser end of the pen is pointing toward the surface (Value = 2). Not used (Value = 4). The barrel button is pressed (Value = 8).
- L19 _public enumerator_ `TimerTick` — The time the packet was generated.
- L20 _public enumerator_ `SerialNumber` — The packet property for identifying the packet. This is the same value you use to retrieve the packet from the packet queue.
- L21 _public enumerator_ `NormalPressure` — The pressure of the pen tip perpendicular to the tablet surface. The greater the pressure on the pen tip, the more ink that is drawn.
- L22 _public enumerator_ `TangentPressure` — The pressure of the pen tip along the plane of the tablet surface.
- L23 _public enumerator_ `ButtonPressure` — The pressure on a pressure sensitive button.
- L24 _public enumerator_ `XTiltOrientation` — The angle between the y,z-plane and the pen and y-axis plane. Applies to a pen cursor. The value is 0 when the pen is perpendicular to the drawing surface and is positive when the pen is to the right of perpendicular.
- L25 _public enumerator_ `YTiltOrientation` — The angle between the x,z-plane and the pen and x-axis plane. Applies to a pen cursor. The value is 0 when the pen is perpendicular to the drawing surface and is positive when the pen is upward or away from the user.
- L26 _public enumerator_ `AzimuthOrientation` — The clockwise rotation of the cursor about the z-axis through a full circular range.
- L27 _public enumerator_ `AltitudeOrientation` — The angle between the axis of the pen and the surface of the tablet. The value is 0 when the pen is parallel to the surface and 90 when the pen is perpendicular to the surface. The values are negative when the pen is inverted.
- L28 _public enumerator_ `TwistOrientation` — The clockwise rotation of the cursor about its own axis.
- L29 _public enumerator_ `PitchRotation` — The packet property that indicates whether the tip is above or below a horizontal line that is perpendicular to the writing surface. Note: This requires a 3D digitizer. The value is positive if the tip is above the line and negative if it is below the line. For example, if you hold the pen in front 
- L30 _public enumerator_ `RollRotation` — The clockwise rotation of the pen around its own axis. Note: This requires a 3D digitizer.
- L31 _public enumerator_ `YawRotation` — The angle of the pen to the left or right around the center of its horizontal axis when the pen is horizontal. Note: This requires a 3D digitizer. If you hold the pen in front of you and write on an imaginary wall, zero yaw indicates that the pen is perpendicular to the wall. The value is negative i
- L32 _public enumerator_ `Width` — The width of the contact area on a touch digitizer.
- L33 _public enumerator_ `Height` — The height of the contact area on a touch digitizer.
- L34 _public enumerator_ `FingerContactConfidence` — The level of confidence that there was finger contact on a touch digitizer.
- L35 _public enumerator_ `DeviceContactID` — The device contact identifier for a packet.
- L37 _public enumerator_ `Num_Enumerators` — THIS IS NOT A VALID ENUMERATOR, BUT IT CAN BE USED TO QUERY HOW MANY PACKET PROPERTIES THERE ARE.
- L38 _public enumerator_ `Invalid_Enumerator = INDEX_NONE` — THIS IS NOT A VALID ENUMERATOR, BUT IT CAN BE USED TO INDICATE THAT A PACKET PROPERTY ENTRY IS INVALID.

#### enum `UE::StylusInput::Mac::ETabletPropertyMetricUnit`  
`enum class ETabletPropertyMetricUnit : int8`  
_L41-54_
- L43 _public enumerator_ `Default` — Units are unknown.
- L44 _public enumerator_ `Inches`
- L45 _public enumerator_ `Centimeters`
- L46 _public enumerator_ `Degrees`
- L47 _public enumerator_ `Radians`
- L48 _public enumerator_ `Seconds`
- L49 _public enumerator_ `Pounds`
- L50 _public enumerator_ `Grams`
- L52 _public enumerator_ `Num_Enumerators` — THIS IS NOT A VALID ENUMERATOR, BUT IT CAN BE USED TO QUERY HOW MANY PACKET PROPERTIES THERE ARE.
- L53 _public enumerator_ `Invalid_Enumerator = INDEX_NONE` — THIS IS NOT A VALID ENUMERATOR, BUT IT CAN BE USED TO INDICATE THAT A PACKET PROPERTY ENTRY IS INVALID.

#### struct `UE::StylusInput::Mac::FPacketProperty`  
`struct FPacketProperty`  
_L58-69_
- L60 _public member_ `EPacketPropertyType Type = EPacketPropertyType::Invalid_Enumerator;`
- L61 _public member_ `ETabletPropertyMetricUnit MetricUnit = ETabletPropertyMetricUnit::Default;`
- L62 _public member_ `int32 Minimum = 0;`
- L63 _public member_ `int32 Maximum = 0;`
- L64 _public member_ `float Resolution = 0.0f;`
- L65 _public member_ `FuncSetProperty* SetProperty = nullptr;`
- L67 _public member_ `static constexpr int32 SetPropertyDataBufferLength = 24;`
- L68 _public member_ `int8 SetPropertyData[SetPropertyDataBufferLength];`

#### struct `UE::StylusInput::Mac::FPacketPropertyConstant`  
`struct FPacketPropertyConstant`  
_L71-76_
- L73 _public member_ `EPacketPropertyType PacketPropertyType;`
- L75 _public member_ `const wchar_t* StrGuid;` — GUID Guid;

#### struct `UE::StylusInput::Mac::FWindowContext`  
`struct FWindowContext`  
_L80-86_
- L82 _public member_ `FVector2d XYScale;`
- L83 _public member_ `FVector2d XYMaximum;`
- L84 _public member_ `FVector2d WindowSize;`

#### class `UE::StylusInput::Mac::FTabletContext`  
`class FTabletContext final : public IStylusInputTabletContext`  
_L88-118_
- inherits: `IStylusInputTabletContext`
- L91 _public function_ `explicit FTabletContext(const uint32 ID) : ID(ID)`
- L95 _public function_ `virtual uint32 GetID() const override`
- L96 _public function_ `virtual FString GetName() const override`
- L98 _public function_ `virtual uint32 GetProductID() const`
- L99 _public function_ `virtual FString GetVendorName() const`
- L100 _public function_ `virtual uint32 GetVendorID() const`
- L101 _public function_ `virtual FString GetSerialNumber() const`
- L103 _public function_ `virtual FIntRect GetInputRectangle() const override`
- L104 _public function_ `virtual ETabletHardwareCapabilities GetHardwareCapabilities() const override`
- L105 _public function_ `virtual ETabletSupportedProperties GetSupportedProperties() const override`
- L107 _public member_ `uint32 ID;`
- L108 _public member_ `FString ProductName;`
- L110 _public member_ `uint32 ProductID;`
- L111 _public member_ `FString VendorName;`
- L112 _public member_ `uint32 VendorID;`
- L113 _public member_ `FString SerialNumber;`
- L114 _public member_ `FIntRect InputRectangle;`
- L115 _public member_ `ETabletSupportedProperties SupportedProperties = ETabletSupportedProperties::None;`
- L116 _public member_ `ETabletHardwareCapabilities HardwareCapabilities = ETabletHardwareCapabilities::None;`
- L117 _public member_ `FPacketProperty PacketDescriptions[static_cast<uint32>(EPacketPropertyType::Num_Enumerators)];`

#### class `UE::StylusInput::Mac::FStylusButton`  
`class FStylusButton final : IStylusInputStylusButton`  
_L122-130_
- inherits: `IStylusInputStylusButton`
- L125 _public function_ `virtual FString GetID() const override`
- L126 _public function_ `virtual FString GetName() const override`
- L128 _public member_ `FString ID;`
- L129 _public member_ `FString Name;`

#### class `UE::StylusInput::Mac::FStylusInfo`  
`class FStylusInfo final : public IStylusInputStylusInfo`  
_L132-151_
- inherits: `IStylusInputStylusInfo`
- L135 _public function_ `explicit FStylusInfo(const uint32 ID) : ID(ID)`
- L139 _public function_ `virtual uint32 GetID() const override`
- L140 _public function_ `virtual FString GetName() const override`
- L141 _public function_ `virtual uint32 GetNumButtons() const override`
- L143 _public function_ `virtual const IStylusInputStylusButton* GetButton(int32 Index) const override`
- L148 _public member_ `uint32 ID = 0;`
- L149 _public member_ `FString Name;`
- L150 _public member_ `TArray<FStylusButton> Buttons;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace StylusInput` (scope `UE`)
- L11 _namespace_ `namespace Mac` (scope `UE::StylusInput`)
- L56 _typedef_ `using FuncSetProperty = void(FStylusInputPacket&, int32, const int8*);` (scope `UE::StylusInput::Mac`)
- L78 _externvar_ `extern FPacketPropertyConstant PacketPropertyConstants[static_cast<uint32>(EPacketPropertyType::Num_Enumerators)];` (scope `UE::StylusInput::Mac`)
- L120 _typedef_ `using FTabletContextContainer = Private::TSharedRefDataContainer<FTabletContext, false>;` (scope `UE::StylusInput::Mac`)
- L153 _typedef_ `using FStylusInfoContainer = Private::TSharedRefDataContainer<FStylusInfo, false>;` (scope `UE::StylusInput::Mac`)
- L154 _prototype_ `bool GetMacTabletDevices(FTabletContextContainer& OutDevices);` (scope `UE::StylusInput::Mac`)

### `Plugins/Editor/StylusInput/Source/StylusInputMac/Private/NSEventHandler.h` (Private)


#### class `UE::StylusInput::Mac::FNSEventHandler`  
`class FNSEventHandler`  
_L28-71_
- L31 _public prototype_ `FNSEventHandler(IStylusInputInstance* Instance, const FCocoaWindow* CocoaWindow, IStylusInputEventHandler* EventHandler);`
- L32 _public prototype_ `virtual ~FNSEventHandler();`
- L34 _public prototype_ `bool AddEventHandler(IStylusInputEventHandler* EventHandler);`
- L35 _public prototype_ `bool RemoveEventHandler(IStylusInputEventHandler* EventHandler);`
- L36 _public function_ `int32 NumEventHandlers() const`
- L38 _public function_ `float GetPacketsPerSecond() const`
- L41 _public prototype_ `virtual void StartListen();` — Starts listening to events on all tablet contexts we have
- L44 _public prototype_ `virtual void StopListen();` — Stops listening to events on all tablet contexts we have
- L46 _public prototype_ `FTabletContextContainer& GetTabletContexts();`
- L48 _public prototype_ `void SetTabletContextID(uint32 ID);`
- L49 _public prototype_ `void SetCurrentPenStatus(EPenStatus);`
- L50 _public prototype_ `void SetCurrentPacketType(EPacketType);`
- L53 _protected prototype_ `void DebugEvent(const FString& Message) const;`
- L56 _protected prototype_ `static bool IsIOHIDAvailable();` — Used to get the device ID of the device that sent the last event. We treat the actual event with NSEvent
- L57 _protected prototype_ `static void HandleHIDEvent(void* context, IOReturn result, void* sender, IOHIDValueRef value);`
- L58 _protected prototype_ `virtual NSEvent* HandleNSEvent(NSEvent* Event);`
- L60 _protected prototype_ `bool ConvertCocoaEventPositionToSlate(NSEvent* Event, NSPoint* oPoint);`
- L63 _protected member_ `IStylusInputInstance* const Instance;`
- L64 _protected member_ `FPacketStats PacketStats;`
- L65 _protected member_ `const FCocoaWindow* CocoaWindow;`
- L66 _protected member_ `FTabletContextContainer TabletContexts;`
- L67 _protected member_ `TArray<IStylusInputEventHandler*> EventHandlers;`
- L69 _protected member_ `id TabletContextListener = nil;`
- L70 _protected member_ `IOHIDManagerRef HIDManagerRef;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace StylusInput` (scope `UE`)
- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace StylusInput` (scope `UE`)
- L26 _namespace_ `namespace Mac` (scope `UE::StylusInput`)
