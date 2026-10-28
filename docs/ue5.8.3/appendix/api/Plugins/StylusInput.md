# Plugins / StylusInput

- module root: `Plugins/Editor/StylusInput/Source/StylusInput`
- headers: 5; symbols: 161
- symbol kinds: class=7, enum=5, enumerator=39, function=32, member=26, namespace=11, prototype=35, struct=3, typedef=3

### `Plugins/Editor/StylusInput/Source/StylusInput/Public/StylusInput.h` (Public)


#### enum `UE::StylusInput::EEventHandlerThread`  
`enum class EEventHandlerThread : int8`  
_L51-55_
- desc: Defines the type of thread on which an event handler will be called by the stylus input instance.
- L53 _public enumerator_ `OnGameThread` — The event handler will be called on the game thread.
- L54 _public enumerator_ `Asynchronous` — The event handler will be called on an unspecific thread that is not the game thread.

#### class `UE::StylusInput::IStylusInputInstance`  
`class IStylusInputInstance`  
_L60-137_
- desc: Interface for a stylus input instance.
- L63 _public prototype_ `virtual ~IStylusInputInstance() = default;`
- L74 _public prototype_ `virtual bool AddEventHandler(IStylusInputEventHandler* EventHandler, EEventHandlerThread Thread) = 0;` — Adds an event handler that gets called for any processed stylus input event. Multiple event handlers can get added for a single stylus input instance. Please note that long-running calls will block any other event handlers, the processing of additional events, and potentially the game thread itself. Thus, make sure to have an event handler call return as soon as possible. @param EventHandler The event handler that gets called for each processed stylus input event. @param Thread The type of thread the event handler calls are performed on. @returns True if the event handler was added successfully.
- L83 _public prototype_ `virtual bool RemoveEventHandler(IStylusInputEventHandler* EventHandler) = 0;` — Removes an event handler from this stylus input instances, and frees up all associated resources. The given event handler should have been added previously via a call to @see AddEventHandler. @param EventHandler The event handler to be released. @returns True if the event handler was removed successfully.
- L95 _public prototype_ `virtual const TSharedPtr<IStylusInputTabletContext> GetTabletContext(uint32 TabletContextID) = 0;` — Provides the tablet context information for a given tablet context ID. This function should only be called with tablet context IDs recently provided by the stylus input instance, e.g. within a @see FStylusPacket as part of an event handler callback. Calls to this function are thread-safe, i.e. can be made from an event handler callback running on any thread. @param TabletContextID The unique identifier of the tablet context as provided by this stylus input instance via an event handler callback. @returns Pointer to tablet context information or nullptr if the tablet context ID was invalid or an error occured.
- L107 _public prototype_ `virtual const TSharedPtr<IStylusInputStylusInfo> GetStylusInfo(uint32 StylusID) = 0;` — Provides the stylus a.k.a. cursor or pen information for a given stylus ID. This function should only be called with stylus IDs recently provided by the stylus input instance, e.g. within a @see FStylusPacket as part of an event handler callback. Calls to this function are thread-safe, i.e. can be made from an event handler callback running on any thread. @param StylusID The unique identifier of the stylus/cursor/pen as provided by this stylus input instance via an event handler callback. @returns Pointer to stylus information or nullptr if the stylus ID was invalid or an error occured.
- L116 _public function_ `virtual float GetPacketsPerSecond(EEventHandlerThread Thread) const` — Provides the approximate number of stylus input packets processed per second for the given thread type for diagnostic purposes. The result will only be meaningful if at least one event handler was added for the given thread type. @param Thread Selects the set of event handlers, i.e. number of packets processed on the game thread versus processed asynchronously. @returns Approximate number of stylus input packets processed per second, or -1 if there is no valid data available.
- L123 _public prototype_ `virtual FName GetInterfaceName() = 0;` — Provides the name of the interface used for this instance. @returns Name of the interface.
- L130 _public prototype_ `virtual FText GetName() = 0;` — Provides the name of this instance for diagnostic purposes. @returns Name of this instance.
- L136 _public prototype_ `virtual bool WasInitializedSuccessfully() const = 0;` — @returns true if this instance was initialized successfully and able to provide stylus input events.

#### class `UE::StylusInput::IStylusInputEventHandler`  
`class IStylusInputEventHandler`  
_L142-174_
- desc: Interface for a stylus input event handler.
- L145 _public prototype_ `virtual ~IStylusInputEventHandler() = default;`
- L152 _public prototype_ `virtual FString GetName() = 0;` — Returns the name of the event handler. This is used internally for diagnostic purposes and reporting warnings and errors. @returns Name of the event handler.
- L162 _public prototype_ `virtual void OnPacket(const FStylusInputPacket& Packet, IStylusInputInstance* Instance) = 0;` — Callback for each packet processed by the stylus input instance. This function is called on the game thread or asynchronously to the game thread depending on how the event handler was added to the stylus input instance. The implementation of this function is responsible for any thread synchronization that might be necessary. @param Packet The packet being processed. @param Instance The stylus input instance that sent the packet.
- L173 _public function_ `virtual void OnDebugEvent(const FString& Message, IStylusInputInstance* Instance)` — Callback for each debug event sent by the stylus input instance for diagnostic purposes. This function is called on the game thread or asynchronously to the game thread depending on how the event handler was added to the stylus input instance. The implementation of this function is responsible for any thread synchronization that might be necessary. The base class implementation of this function does nothing. @param Message The debug message sent by the stylus input instance. @param Instance The stylus input instance that sent the debug message.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace StylusInput` (scope `UE`)
- L25 _prototype_ `IStylusInputInstance* CreateInstance(SWindow& Window);` (scope `UE::StylusInput`) — Creates a stylus input instance for a given window. Any call to this function that returns a valid instance pointer should have a corresponding call to @see #ReleaseInstance. @param Window The window the stylus input is mapped to. @returns The stylus input instance for the given window or a nullptr if no valid interface is available or the instance could not be initialized.
- L36 _prototype_ `IStylusInputInstance* CreateInstance(SWindow& Window, FName Interface, bool bRequestedInterfaceOnly);` (scope `UE::StylusInput`) — Creates a stylus input instance for a given window and a requested interface. Any call to this function that returns a valid instance pointer should have a corresponding call to @see #ReleaseInstance. @param Window The window the stylus input is mapped to. @param Interface Request a specific interface to be used for handling stylus input. @param bRequestedInterfaceOnly Only use the requested stylus input interface, and return nullptr if this interface is not available. @returns The stylus input instance for the given window or a nullptr if no valid interface is available or the instance could not be initialized.
- L46 _prototype_ `bool ReleaseInstance(IStylusInputInstance* Instance);` (scope `UE::StylusInput`) — Releases any resources held for the given stylus input instance. This function should be called for any corresponding successful call to @see #CreateInstance, e.g. when stylus input is no longer needed or the window related to the instance is destroyed. @param Instance The stylus input instance to be released. @returns True if the given instance is not a nullptr and was successfully released.

### `Plugins/Editor/StylusInput/Source/StylusInput/Public/StylusInputInterface.h` (Public)


#### class `UE::StylusInput::IStylusInputInterface`  
`class IStylusInputInterface`  
_L43-64_
- desc: Interface for platform APIs that provide stylus input data.
- L46 _public prototype_ `virtual ~IStylusInputInterface() = default;`
- L53 _public prototype_ `virtual FName GetName() const = 0;` — Provides the name of the interface; this needs to be unique among all interfaces. @returns Name of the interface.
- L58 _public prototype_ `virtual IStylusInputInstance* CreateInstance(SWindow& Window) = 0;` — Implementation of /see StylusInput::CreateInstance for this interface.
- L63 _public prototype_ `virtual bool ReleaseInstance(IStylusInputInstance* Instance) = 0;` — Implementation of /see StylusInput::ReleaseInstance for this interface.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace StylusInput` (scope `UE`)
- L19 _prototype_ `TArray<FName> GetAvailableInterfaces();` (scope `UE::StylusInput`) — Provides the names of all currently available stylus input interfaces. @return Names of available interfaces.
- L29 _prototype_ `bool RegisterInterface(IStylusInputInterface* Interface);` (scope `UE::StylusInput`) — Adds an interface to the StylusInput module. Calls to this function are only allowed after the "Default" loading phase. This can be ensured by loading modules providing stylus input interfaces in the "PostDefault" loading phase. @param Interface The interface to be registered.
- L38 _prototype_ `bool UnregisterInterface(IStylusInputInterface* Interface);` (scope `UE::StylusInput`) — Removes an interface from the StylusInput module. The StylusInput module does not deallocate the provided interface. @param Interface The interface to be unregistered.

### `Plugins/Editor/StylusInput/Source/StylusInput/Public/StylusInputPacket.h` (Public)


#### enum `UE::StylusInput::EPenStatus`  
`enum class EPenStatus : uint8`  
_L13-20_
- desc: Flags for the status of the stylus pen.
- L15 _public enumerator_ `None = 0b00000000` — There is no pen flag.
- L16 _public enumerator_ `CursorIsTouching = 0b00000001` — The pen cursor is touching the drawing surface.
- L17 _public enumerator_ `CursorIsInverted = 0b00000010` — The pen cursor is inverted, e.g. the eraser end of the pen is pointing toward the drawing surface.
- L18 _public enumerator_ `NotUsed = 0b00000100` — Not used.
- L19 _public enumerator_ `BarrelButtonPressed = 0b00001000` — The barrel button is pressed.

#### enum `UE::StylusInput::EPacketType`  
`enum class EPacketType : uint8`  
_L25-32_
- desc: Describes the interaction between pen and drawing surface (a.k.a. digitizer) for which the packet was generated.
- L27 _public enumerator_ `Invalid` — The packet is not valid.
- L28 _public enumerator_ `OnDigitizer` — The packet was generated while the pen's cursor is touching the drawing surface.
- L29 _public enumerator_ `AboveDigitizer` — The packet was generated while the pen's cursor is hovering in proximity above the drawing surface.
- L30 _public enumerator_ `StylusDown` — The packet was generated when the pen's cursor started touching the drawing surface.
- L31 _public enumerator_ `StylusUp` — The packet was generated when the pen's cursor stopped touching the drawing surface.

#### struct `UE::StylusInput::FStylusInputPacket`  
`struct FStylusInputPacket`  
_L40-69_
- desc: Data for an interaction between the pen and the drawing surface. Note that not all devices support all properties. The set of valid properties can be queried via @see IStylusInputTabletContext#GetSupportedProperties, and a description of all properties is available in @see ETabletSupportedProperties.
- L43 _public member_ `uint32 TabletContextID = 0;` — Metadata
- L44 _public member_ `uint32 CursorID = 0;` — Unique identifier for the stylus/cursor/pen that was used to create the packet.
- L45 _public member_ `EPacketType Type = EPacketType::Invalid;` — The type of interaction between pen and drawing surface that created the packet.
- L46 _public member_ `EPenStatus PenStatus = EPenStatus::None;` — The status of the stylus/cursor/pen when the packet was created.
- L49 _public member_ `float X = 0.0f;` — Properties
- L50 _public member_ `float Y = 0.0f;`
- L51 _public member_ `float Z = 0.0f;`
- L52 _public member_ `uint32 TimerTick = 0;`
- L53 _public member_ `uint32 SerialNumber = 0;`
- L54 _public member_ `float NormalPressure = 0.0f;`
- L55 _public member_ `float TangentPressure = 0.0f;`
- L56 _public member_ `float ButtonPressure = 0.0f;`
- L57 _public member_ `float XTiltOrientation = 0.0f;`
- L58 _public member_ `float YTiltOrientation = 0.0f;`
- L59 _public member_ `float AzimuthOrientation = 0.0f;`
- L60 _public member_ `float AltitudeOrientation = 0.0f;`
- L61 _public member_ `float TwistOrientation = 0.0f;`
- L62 _public member_ `float PitchRotation = 0.0f;`
- L63 _public member_ `float RollRotation = 0.0f;`
- L64 _public member_ `float YawRotation = 0.0f;`
- L65 _public member_ `float Width = 0.0f;`
- L66 _public member_ `float Height = 0.0f;`
- L67 _public member_ `float FingerContactConfidence = 0.0f;`
- L68 _public member_ `int32 DeviceContactID = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace StylusInput` (scope `UE`)
- L73 _function_ `inline EPenStatus operator|(EPenStatus A, EPenStatus B)` (scope `UE::StylusInput`)
- L78 _function_ `inline EPenStatus operator&(EPenStatus A, EPenStatus B)` (scope `UE::StylusInput`)
- L83 _function_ `inline EPenStatus operator^(EPenStatus A, EPenStatus B)` (scope `UE::StylusInput`)
- L88 _function_ `inline EPenStatus operator~(EPenStatus A)` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInput/Public/StylusInputTabletContext.h` (Public)


#### enum `UE::StylusInput::ETabletHardwareCapabilities`  
`enum class ETabletHardwareCapabilities : uint8`  
_L13-20_
- desc: Flags describing tablet hardware capabilities.
- L15 _public enumerator_ `None = 0`
- L16 _public enumerator_ `Integrated = 1 << 0` — The digitizer is integrated with the display.
- L17 _public enumerator_ `CursorMustTouch = 1 << 1` — The cursor must be in physical contact with the device to report position.
- L18 _public enumerator_ `HardProximity = 1 << 2` — The device can generate in-air packets when the cursor is in the physical detection range (proximity) of the device.
- L19 _public enumerator_ `CursorsHavePhysicalIds = 1 << 3` — The device can uniquely identify the active cursor.

#### enum `UE::StylusInput::ETabletSupportedProperties`  
`enum class ETabletSupportedProperties : uint32`  
_L25-49_
- desc: Flags denoting the properties supported by a tablet.
- L27 _public enumerator_ `None = 0`
- L28 _public enumerator_ `X = 1 << 0` — The x-coordinate in the coordinate space of the window that was used to create the stylus input instance. Each packet contains this property by default.
- L29 _public enumerator_ `Y = 1 << 1` — The y-coordinate in the coordinate space of the window that was used to create the stylus input instance. Each packet contains this property by default.
- L30 _public enumerator_ `Z = 1 << 2` — The z-coordinate or distance of the pen tip from the tablet surface. The TabletPropertyMetricUnit enumeration  type determines the unit of measurement for this property.
- L31 _public enumerator_ `PacketStatus = 1 << 3` — Contains one or more of the following flag values: The cursor is touching the drawing surface (Value = 1). The cursor is inverted. For example, the eraser end of the pen is pointing toward the surface (Value = 2). Not used (Value = 4). The barrel button is pressed (Value = 8).
- L32 _public enumerator_ `TimerTick = 1 << 4` — The time the packet was generated in milliseconds since system start.
- L33 _public enumerator_ `SerialNumber = 1 << 5` — The packet property for identifying the packet. This is the same value you use to retrieve the packet from the packet queue.
- L34 _public enumerator_ `NormalPressure = 1 << 6` — The pressure of the pen tip perpendicular to the tablet surface. The greater the pressure on the pen tip, the  more ink that is drawn.
- L35 _public enumerator_ `TangentPressure = 1 << 7` — The pressure of the pen tip along the plane of the tablet surface.
- L36 _public enumerator_ `ButtonPressure = 1 << 8` — The pressure on a pressure sensitive button.
- L37 _public enumerator_ `XTiltOrientation = 1 << 9` — The angle between the y,z-plane and the pen and y-axis plane. Applies to a pen cursor. The value is 0 when the pen is perpendicular to the drawing surface and is positive when the pen is to the right of perpendicular.
- L38 _public enumerator_ `YTiltOrientation = 1 << 10` — The angle between the x,z-plane and the pen and x-axis plane. Applies to a pen cursor. The value is 0 when the pen is perpendicular to the drawing surface and is positive when the pen is upward or away from the user.
- L39 _public enumerator_ `AzimuthOrientation = 1 << 11` — The clockwise rotation of the cursor about the z-axis through a full circular range.
- L40 _public enumerator_ `AltitudeOrientation = 1 << 12` — The angle between the axis of the pen and the surface of the tablet. The value is 0 when the pen is parallel to the surface and 90 when the pen is perpendicular to the surface. The values are negative when the pen is inverted.
- L41 _public enumerator_ `TwistOrientation = 1 << 13` — The clockwise rotation of the cursor about its own axis.
- L42 _public enumerator_ `PitchRotation = 1 << 14` — The packet property that indicates whether the tip is above or below a horizontal line that is perpendicular to the writing surface. Note: This requires a 3D digitizer. The value is positive if the tip is above the line and negative if it is below the line. For example, if you hold the pen in front 
- L43 _public enumerator_ `RollRotation = 1 << 15` — The clockwise rotation of the pen around its own axis. Note: This requires a 3D digitizer.
- L44 _public enumerator_ `YawRotation = 1 << 16` — The angle of the pen to the left or right around the center of its horizontal axis when the pen is horizontal. Note: This requires a 3D digitizer. If you hold the pen in front of you and write on an imaginary wall, zero yaw indicates that the pen is perpendicular to the wall. The value is negative i
- L45 _public enumerator_ `Width = 1 << 17` — The width of the contact area on a touch digitizer.
- L46 _public enumerator_ `Height = 1 << 18` — The height of the contact area on a touch digitizer.
- L47 _public enumerator_ `FingerContactConfidence = 1 << 19` — The level of confidence that there was finger contact on a touch digitizer.
- L48 _public enumerator_ `DeviceContactID = 1 << 20` — The device contact identifier for a packet, e.g. to identify individual fingers.

#### class `UE::StylusInput::IStylusInputTabletContext`  
`class IStylusInputTabletContext`  
_L54-99_
- desc: Identifies and describes the capabilities of a tablet drawing surface.
- L57 _public prototype_ `virtual ~IStylusInputTabletContext() = default;`
- L66 _public prototype_ `virtual uint32 GetID() const = 0;` — Returns the unique identifier for the tablet context. The returned ID is only unique and identical for a given stylus input instance, i.e. the same tablet device might have different IDs for different stylus input instances, and different tablet devices might have the same ID in two separate stylus input instances. @returns The unique identifier for the tablet context for the respective stylus input instance.
- L74 _public prototype_ `virtual FString GetName() const = 0;` — Returns the name of the tablet context. This usually allows to identify the tablet device based on the hardware product name and model. @returns The name of the tablet context.
- L83 _public prototype_ `virtual FIntRect GetInputRectangle() const = 0;` — Returns the dimensions of the digitizer surface in device coordinates. This mainly gives an indication of the spatial resolution of the device, and it is not related to the coordinate space of the window that was used to create the stylus input instance. @returns The dimensions of the digitizer surface.
- L90 _public prototype_ `virtual ETabletHardwareCapabilities GetHardwareCapabilities() const = 0;` — Returns the hardware capabilities of the device associated with the tablet context. @return The hardware capability flags.
- L98 _public prototype_ `virtual ETabletSupportedProperties GetSupportedProperties() const = 0;` — Returns the supported properties for a tablet context. Only explicitly supported properties for a tablet context provide valid values in the packet data with the respective tablet context ID. @returns The supported properties flags.

#### class `UE::StylusInput::IStylusInputStylusButton`  
`class IStylusInputStylusButton`  
_L104-118_
- desc: Description of a button on a stylus pen.
- L107 _public prototype_ `virtual ~IStylusInputStylusButton() = default;`
- L112 _public prototype_ `virtual FString GetID() const = 0;` — @returns The GUID string for the button.
- L117 _public prototype_ `virtual FString GetName() const = 0;` — @returns  The name of the button.

#### class `UE::StylusInput::IStylusInputStylusInfo`  
`class IStylusInputStylusInfo`  
_L123-156_
- desc: Description of a stylus pen.
- L126 _public prototype_ `virtual ~IStylusInputStylusInfo() = default;`
- L134 _public prototype_ `virtual uint32 GetID() const = 0;` — Returns the identifier for the type of stylus being used. Note that different hardware pens can have the same ID within a tablet context. @returns Identifier of the stylus pen.
- L139 _public prototype_ `virtual FString GetName() const = 0;` — @returns The name of the stylus pen.
- L147 _public prototype_ `virtual uint32 GetNumButtons() const = 0;` — Returns the number of buttons on the stylus. Note that some hardware buttons might not show up in the stylus info provided by the tablet context. @returns The number of buttons on the stylus.
- L155 _public prototype_ `virtual const IStylusInputStylusButton* GetButton(int32 Index) const = 0;` — Returns a description of the button for a given index. @param Index A number in [0, @see #GetNumButtons). @returns Pointer to a stylus button.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace StylusInput` (scope `UE`)
- L160 _function_ `inline ETabletHardwareCapabilities operator|(ETabletHardwareCapabilities A, ETabletHardwareCapabilities B)` (scope `UE::StylusInput`)
- L166 _function_ `inline ETabletHardwareCapabilities operator&(ETabletHardwareCapabilities A, ETabletHardwareCapabilities B)` (scope `UE::StylusInput`)
- L172 _function_ `inline ETabletHardwareCapabilities operator^(ETabletHardwareCapabilities A, ETabletHardwareCapabilities B)` (scope `UE::StylusInput`)
- L178 _function_ `inline ETabletHardwareCapabilities operator~(ETabletHardwareCapabilities A)` (scope `UE::StylusInput`)
- L183 _function_ `inline ETabletSupportedProperties operator|(ETabletSupportedProperties A, ETabletSupportedProperties B)` (scope `UE::StylusInput`)
- L189 _function_ `inline ETabletSupportedProperties operator&(ETabletSupportedProperties A, ETabletSupportedProperties B)` (scope `UE::StylusInput`)
- L195 _function_ `inline ETabletSupportedProperties operator^(ETabletSupportedProperties A, ETabletSupportedProperties B)` (scope `UE::StylusInput`)
- L201 _function_ `inline ETabletSupportedProperties operator~(ETabletSupportedProperties A)` (scope `UE::StylusInput`)

### `Plugins/Editor/StylusInput/Source/StylusInput/Public/StylusInputUtils.h` (Public)


#### class `UE::StylusInput::Private::TSharedRefDataContainer`  
`template <typename DataType, bool ThreadSafe> class TSharedRefDataContainer`  
_L34-131_
- L37 _public function_ `TSharedRef<DataType> Add(uint32 ID)`
- L43 _public function_ `void AddOrReplace(TSharedPtr<DataType>&& Item)`
- L64 _public function_ `bool Contains(uint32 ID) const`
- L74 _public function_ `TSharedPtr<DataType> Get(uint32 ID) const`
- L84 _public function_ `bool Remove(uint32 ID)`
- L100 _public function_ `void Clear()`
- L106 _public function_ `void Update(const TSharedRefDataContainer<DataType, false>& InData)`
- L116 _public function_ `uint32 Num() const`
- L118 _public function_ `const TSharedRef<DataType>& operator[](const uint32 Index) const`
- L125 _private typedef_ `using LockType = std::conditional_t<ThreadSafe, FRWLock, FNoLock>;`
- L126 _private typedef_ `using ReadScopeLockType = std::conditional_t<ThreadSafe, FReadScopeLock, FScopeNoLock>;`
- L127 _private typedef_ `using WriteScopeLockType = std::conditional_t<ThreadSafe, FWriteScopeLock, FScopeNoLock>;`
- L129 _private member_ `UE_NO_UNIQUE_ADDRESS mutable LockType RWLock;`
- L130 _private member_ `TArray<TSharedRef<DataType>> Data;`

#### struct `UE::StylusInput::Private::TSharedRefDataContainer::FNoLock`  
`struct FNoLock`  
_L122-122_

#### struct `UE::StylusInput::Private::TSharedRefDataContainer::FScopeNoLock`  
`struct FScopeNoLock`  
_L123-123_
- L123 _public function_ `struct FScopeNoLock`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace StylusInput` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::StylusInput`)
- L11 _function_ `DECLARE_LOG_CATEGORY_EXTERN(LogStylusInput, Log, All) inline void LogError(const FString& Preamble, const FString& Message)` (scope `UE::StylusInput::Private`)
- L18 _function_ `inline void LogWarning(const FString& Preamble, const FString& Message)` (scope `UE::StylusInput::Private`)
- L23 _function_ `inline void Log(const FString& Preamble, const FString& Message)` (scope `UE::StylusInput::Private`)
- L28 _function_ `inline void LogVerbose(const FString& Preamble, const FString& Message)` (scope `UE::StylusInput::Private`)
- L48 _function_ `` (scope `UE::StylusInput::Private::TSharedRefDataContainer::AddOrReplace`)
- L68 _function_ `` (scope `UE::StylusInput::Private::TSharedRefDataContainer::Contains`)
- L78 _function_ `` (scope `UE::StylusInput::Private::TSharedRefDataContainer::Get`)
- L89 _function_ `Index = Data.IndexOfByPredicate([ID](const TSharedRef<DataType>& Tc) { return Tc->ID == ID; });` (scope `UE::StylusInput::Private::TSharedRefDataContainer::Remove`)
