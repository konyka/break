# Plugins / DMXProtocol

- module root: `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol`
- headers: 30; symbols: 700
- symbol kinds: class=20, delegate=8, enum=7, enumerator=29, function=178, macro=14, member=188, namespace=9, prototype=217, struct=19, typedef=11
- DynamicallyLoadedModuleNames: Settings
- PrivateDependencyModuleNames: CoreUObject, Engine, InputCore, Json, Networking, Serialization, Slate, SlateCore, Sockets
- PrivateIncludePathModuleNames: Settings
- PublicDependencyModuleNames: Core, Projects

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Internal/IO/DMXConflictMonitor.h` (Internal)


#### struct `UE::DMX::FDMXMonitoredOutboundDMXData`  
`struct FDMXMonitoredOutboundDMXData : public TSharedFromThis<FDMXMonitoredOutboundDMXData>`  
_L22-45_
- inherits: `TSharedFromThis<FDMXMonitoredOutboundDMXData>`
- L25 _public function_ `FDMXMonitoredOutboundDMXData( TWeakPtr<FDMXOutputPort> InOutputPort, int32 InLocalUniverseID, TMap<int32, uint8> InChannelToValueMap, FName InTrace) : OutputPort(InOutputPort) , LocalUniverseID(InLocalUniverseID) , ChannelToValueMap(InChannelToValueMap) , Trace(InTrace)`
- L37 _public prototype_ `bool ConflictsWith(const FDMXMonitoredOutboundDMXData& Other) const;` — Returns true if this data conflicts with Other
- L39 _public member_ `const TWeakPtr<FDMXOutputPort> OutputPort;`
- L40 _public member_ `const int32 LocalUniverseID;`
- L41 _public member_ `const TMap<int32, uint8> ChannelToValueMap;`
- L44 _public member_ `const FName Trace;` — The users that raised this specific trace, in callstack order.

#### class `UE::DMX::FDMXConflictMonitorUserSession`  
`class FDMXConflictMonitorUserSession : public TSharedFromThis<FDMXConflictMonitorUserSession>`  
_L48-65_
- inherits: `TSharedFromThis<FDMXConflictMonitorUserSession>`
- desc: User session for a conflict monitor user. Create via FDMXConflictMonitor::Join
- L52 _public prototype_ `~FDMXConflictMonitorUserSession();`
- L61 _private prototype_ `FDMXConflictMonitorUserSession() = default;`
- L62 _private prototype_ `FDMXConflictMonitorUserSession(FName InUserName);`
- L64 _private member_ `FName UserName;`

#### class `UE::DMX::FDMXConflictMonitor`  
`class FDMXConflictMonitor : public TSharedFromThis<FDMXConflictMonitor>`  
_L72-141_
- inherits: `TSharedFromThis<FDMXConflictMonitor>`
- desc: Monitors outbound DMX for possible conflicts. Only sees conflict created within a single port. User objects usually will want to refer to the instance declared in port manager, see FDMXPortManager::GetConflictMonitor.
- L79 _public prototype_ `virtual ~FDMXConflictMonitor();`
- L85 _public prototype_ `[[nodiscard]] static TSharedRef<FDMXConflictMonitorUserSession> Join(const FName& UserName);` — Joins monitoring for conflicts. Returns a user session. The monitor actively scans for outbound DMX conflicts while the user session is alive.
- L88 _public prototype_ `static bool IsEnabled();` — Returns true if the conflict monitor is enabled
- L91 _public prototype_ `static FDMXConflictMonitor* Get();` — Returns the conflict monitor, or nullptr if it has no users (see Join to add users).
- L94 _public prototype_ `TMap<FName, TArray<TSharedRef<FDMXMonitoredOutboundDMXData>>> GetOutboundConflictsSynchronous() const;` — Returns current conflicts, locking.
- L97 _public function_ `TArray<TSharedRef<FDMXMonitoredOutboundDMXData>> GetMonitoredOutboundData() const` — Returns currently monitored data. This contains non-conflicting data as well.
- L100 _public prototype_ `void TraceUser(const FMinimalName& User);` — Adds a trace to the queue stack.
- L103 _public prototype_ `void PopTrace(const FMinimalName& User);` — Pops the last trace from the trace stack
- L106 _public prototype_ `void MonitorOutboundDMX(const TSharedRef<FDMXOutputPort>& InOutputPort, int32 InLocalUniverseID, const TMap<int32, uint8>& InChannelToValueMap);` — Monitors outbound DMX. Can be called from the game thread only.
- L109 _public function_ `double GetTimeGameThread() const` — Returns the time the monitor consumes on the game thread
- L113 _private prototype_ `static void RemoveUser(const FName& UserName);` — Removes a user from the monitor. If all user objects left, the monitor is disabled.
- L116 _private member_ `TArray<FMinimalName> TraceStack;` — The currently stacked traces
- L119 _private member_ `TMap<int32, uint8> ChannelToValueMap;` — Channel values this frame
- L122 _private member_ `TArray<TSharedRef<FDMXMonitoredOutboundDMXData>> MonitoredOutboundData;` — Current outbound data
- L125 _private member_ `TMap<FName, TArray<TSharedRef<FDMXMonitoredOutboundDMXData>>> Conflicts;` — An array of conflicting traces
- L128 _private member_ `uint64 FrameNumber = 0;` — The last frame number that was handled on the monitor thread
- L131 _private member_ `double TimeGameThread = 0.0;` — The time the monitor uses on the game thread
- L134 _private member_ `static TArray<FName> UserNames;` — Users of the monitor
- L137 _private member_ `static TSharedPtr<FDMXConflictMonitor> Instance;` — Global instance. Only valid if there are users.
- L140 _private member_ `mutable FCriticalSection MutexAccessConflicts;` — Mutex access for the Conflicts array

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace DMX` (scope `UE`)

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Internal/IO/DMXTrace.h` (Internal)


#### class `UE::DMX::Private::Trace::FDMXScopedSendDMXTrace`  
`class FDMXScopedSendDMXTrace`  
_L13-21_
- L16 _public prototype_ `FDMXScopedSendDMXTrace(const FName& InUser);`
- L17 _public prototype_ `virtual ~FDMXScopedSendDMXTrace();`
- L20 _private member_ `FMinimalName User;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace DMX` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::DMX`)
- L11 _namespace_ `namespace Trace` (scope `UE::DMX::Private`)
- L24 _macro_ `#define UE_DMX_SCOPED_TRACE_SENDDMX(Name) \`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXAttribute.h` (Public)


#### struct `FDMXAttribute`  
`struct FDMXAttribute`  
_L19-45_
- reflection: `USTRUCT()`
- L25 _public member_ `FName Name;` — `UPROPERTY(EditDefaultsOnly, Category = "DMX")` — Name of this Attribute, displayed on Attribute selectors
- L32 _public member_ `FString Keywords;` — `UPROPERTY(EditDefaultsOnly, Category = "DMX")` — Keywords used when auto-mapping Fixture Functions from a GDTF file to match Fixture Functions to existing Attributes.
- L35 _public function_ `inline bool operator==(const FDMXAttribute& Other) const` — Comparison operator
- L39 _public function_ `inline bool operator!=(const FDMXAttribute& Other) const`
- L41 _public prototype_ `TArray<FString> GetKeywords() const;`
- L44 _public prototype_ `void CleanupKeywords();` — cleanup the list of keywords using commas and removing spaces/tabs

#### struct `FDMXAttributeName`  
`struct FDMXAttributeName`  
_L54-84_
- reflection: `USTRUCT(BlueprintType, Category = "DMX")`
- L58 _public typedef_ `using IDMXAttributeEditorContext = UE::DMX::Attribute::IDMXAttributeEditorContext;`
- L61 _public prototype_ `FDMXAttributeName();`
- L64 _public prototype_ `explicit FDMXAttributeName(const FDMXAttribute& InAttribute);` — Construct from an Attribute
- L67 _public prototype_ `FDMXAttributeName(const FName& NameAttribute);` — Construct from an Attribute name
- L70 _public prototype_ `void SetFromName(const FName& InName);`
- L73 _public function_ `bool IsValid() const` — IsValid member accessor
- L77 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "DMX")` — The Attribute Name
- L80 _public prototype_ `static TArray<FName> GetPredefinedValues();` — Returns the predefined values
- L83 _public prototype_ `bool Serialize(FArchive& Ar);` — Custom serializer to maintain the upgrade path

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FDMXAttributeName> : public TStructOpsTypeTraitsBase2<FDMXAttributeName>`  
_L87-94_
- inherits: `TStructOpsTypeTraitsBase2<FDMXAttributeName>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L91-93_

#### class `UDMXAttributeNameConversions`  
`class UDMXAttributeNameConversions : public UBlueprintFunctionLibrary`  
_L114-125_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L121 _public prototype_ `static FString Conv_DMXAttributeToString(const FDMXAttributeName& InAttribute);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (DMX Attribute)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|DMX")`
- L124 _public prototype_ `static FName Conv_DMXAttributeToName(const FDMXAttributeName& InAttribute);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "ToName (DMX Attribute)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|DMX")`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace DMX` (scope `UE`)
- L13 _namespace_ `namespace Attribute` (scope `UE::DMX`)
- L48 _function_ `inline uint32 GetTypeHash(const FDMXAttribute& Attribute)` — Unique hash from a DMX Attribute
- L92 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon07d255910103`)
- L96 _function_ `inline uint32 GetTypeHash(const FDMXAttributeName& DMXNameListItem)`
- L103 _function_ `inline bool operator==(const FDMXAttributeName& V1, const FDMXAttributeName& V2)`
- L108 _function_ `inline bool operator!=(const FDMXAttributeName& V1, const FDMXAttributeName& V2)`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXConversions.h` (Public)


#### class `FDMXConversions`  
`class FDMXConversions`  
_L15-75_
- desc: Common conversions for dmx
- L24 _public function_ `template <typename T, typename U = typename TEnableIf<std::is_same_v<T, uint32>>::Type> static TArray<uint8> UnsignedInt32ToByteArray(T Value, EDMXFixtureSignalFormat SignalFormat, bool bLSBOrder)` — Converts a uint32 to a byte array
- L46 _public function_ `template <typename T, typename U = typename TEnableIf<std::is_same_v<T, float>>::Type> static TArray<uint8> NormalizedDMXValueToByteArray(T NormalizedValue, EDMXFixtureSignalFormat SignalFormat, bool bLSBOrder)` — Converts a normalized value to a byte array. Normalized value has to be in the 0-1 range. Assumes max signal format is 24bit.
- L58 _public prototype_ `static uint8 GetSizeOfSignalFormat(EDMXFixtureSignalFormat SignalFormat);` — Returns the number of Bytes the Signal Format uses
- L66 _public prototype_ `static uint32 GetSignalFormatMaxValue(EDMXFixtureSignalFormat SignalFormat);` — Returns the Max Value the Data Type can take @param DataType		The Signal Format in quesion. @return				The Max Value of the Data Type, e.g. 255 for EDMXFixtureSignalFormat::E8Bit.
- L69 _public prototype_ `static uint32 ClampValueBySignalFormat(uint32 Value, EDMXFixtureSignalFormat SignalFormat);` — Clamps the Value to be in value range of the Signal Format
- L71 _public prototype_ `template <typename T> static uint32 ClampValueBySignalFormat(T Value, EDMXFixtureSignalFormat SignalFormat) = delete;` — No implicit conversions
- L74 _private prototype_ `FDMXConversions() = delete;`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXNameListItem.h` (Public)


#### struct `FDMXNameListItem`  
`struct FDMXNameListItem`  
_L86-110_
- reflection: `UE_DEPRECATED(5.1, "Removed to overcome restrictions of the generic base struct. Ustructs that have a Name property should declare it themselves instead.")`
- reflection: `USTRUCT()`
- desc: Types that represent names in a SNameListPicker dropdown must: - inherit this struct and override the virtual functions. - use the DMX_NAMELISTITEM_STATICS macros above to declare the expected statics.
- L91 _public member_ `static const FName None;` — The value of no item selected.
- L93 _public prototype_ `virtual ~FDMXNameListItem() = default;`
- L97 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "DMX")` — Label of the item this struct represents
- L100 _public function_ `virtual FName GetName() const` — The name representation of this object
- L103 _public function_ `virtual void SetFromName(const FName& InName)` — Set this object from a FName
- L106 _public function_ `virtual bool IsNone() const` — Whether the current value is None
- L109 _public function_ `virtual void SetToNone()` — Set this object to represent a None value

#### Free symbols / members of external scopes

- L19 _macro_ `#define DECLARE_DMX_NAMELISTITEM_STATICS(CanBeNone) \` — Types that represent names in a SNameListPicker dropdown must implement this macro in their type declaration body, just like it's done with GENERATED_BODY(). In the type's cpp file, use IMPLEMENT_DMX_NAMELISTITEM_STATICS to define the static variable and function. @param bCanBeNone	Defines if the type can display a None value in its SNameListPicker dropdown.
- L35 _macro_ `#define IMPLEMENT_DMX_NAMELISTITEM_STATICVARS(TypeName) \` — Use this macro in the cpp file of the types that represent names in a SNameListPicker dropdown to declare the static variables implementation @param TypeName	The name of the type implementing the statics
- L55 _macro_ `#define IMPLEMENT_DMX_NAMELISTITEM_GetAllValues(TypeName) \` — Implements the GetPossibleValues static function for a type that represents names in a SNameListPicker dropdown. Don't use ';' after the macro. Instead, add the body of GetPossibleValues to it and return a TArray<FName> with all the possible values for the type. Like so: IMPLEMENT_DMX_NAMELISTITEM_GetAllValues(TypeName) { TArray<FName> Names; // Add possible values to Names ... return Names; } @param TypeName	The name of the type implementing the function
- L76 _macro_ `#define IMPLEMENT_DMX_NAMELISTITEM_IsValid(TypeName) \` — Implements the IsValid static function for a type that represents names in a SNameListPicker dropdown. Don't use ';' after the macro. Instead, add the body of IsValid to it and return a bool that is true if the InName parameter represents a valid name for the type. Like so: IMPLEMENT_DMX_NAMELISTITEM_IsValid(TypeName) { bool bIsNameValid = false; // Check the validity of InName ... return bIsNameValid; } @param TypeName	The name of the type implementing the function

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXProtocolBlueprintLibrary.h` (Public)


#### class `UDMXProtocolBlueprintLibrary`  
`class UDMXProtocolBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L15-89_
- reflection: `UCLASS(meta = (ScriptName = "DMXRuntimeLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L26 _public prototype_ `static void SetSendDMXEnabled(bool bSendDMXEnabled = true, bool bAffectEditor = false);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Sets if DMX is sent to the network @param bSendDMXEnabled		If true, sends DMX packets to the output ports, else ignores all send calls globally. @param bAffectEditor			If true, affects the editor.
- L33 _public prototype_ `static bool IsSendDMXEnabled();` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Returns whether send DMX to the network is enabled globally. @return		If true, DMX is sent to the Network
- L41 _public prototype_ `static void SetReceiveDMXEnabled(bool bReceiveDMXEnabled = true, bool bAffectEditor = false);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Sets if DMX is received from the network @param bReceiveDMXEnabled	If true, receives inbound DMX packets on the input ports, else ignores them, globally. @param bAffectEditor			If true, affects the editor.
- L48 _public prototype_ `static bool IsReceiveDMXEnabled();` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Returns whether Receive DMX from the network is enabled globally. @return		If true, DMX is received from the Network
- L55 _public prototype_ `static TArray<FString> GetLocalDMXNetworkInterfaceCardIPs();` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Returns the IP addresses of the network interface cards available to the system. @return		The Network Interface Card IP Addresses
- L63 _public prototype_ `static void SetDMXInputPortDeviceAddress(FDMXInputPortReference InputPort, const FString& DeviceAddress);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Sets the Device Address of the Output Port. For networking Protocols that's the IP Adress of the network interface card. @param InputPort			The Input Port for which the Device Address should be set @param DeviceAddress		The Device Address the Input Port should use
- L71 _public prototype_ `static void SetDMXOutputPortDeviceAddress(FDMXOutputPortReference OutputPort, const FString& DeviceAddress);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Sets the Device Address of the Output Port. For networking Protocols that's the IP Adress of the network interface card. @param OutputPort		The Output Port for which the Device Address should be set @param DeviceAddress		The Device Address the Output Port should use
- L79 _public prototype_ `static void SetDMXOutputPortDestinationAddresses(FDMXOutputPortReference OutputPort, const TArray<FString>& DestinationAddresses);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Sets the Destination Address Address of the Output Port. For networking Protocols that's the Unicast IP Adress. Not required for Multicast and Broadcast. @param PortName				The Output Port for which the Unicast IP Address should be set @param DestinationAddress	The Destination Address the Output Port should use
- L88 _public prototype_ `static void SetDMXOutputPortDestinationAddress(FDMXOutputPortReference OutputPort, const FString& DestinationAddress);` — `UE_DEPRECATED(5.0, "Output Ports now support many destination addresses. Please use UDMXProtocolBlueprintLibrary::SetDMXOutputPortDestinationAddresses instead")` — `UFUNCTION(BlueprintCallable, Category = "DMX", meta = (DeprecatedFunction, DeprecationMessage = "Deprecated 5.0. Output Ports now support many Destination Addresses. Please use SetDMXOutputPortDestinationAddresses instead."))` — Sets the Destination Address Address of the Output Port. For networking Protocols that's the Unicast IP Adress. Not required for Multicast and Broadcast. @param PortName				The Output Port for which the Unicast IP Address should be set @param DestinationAddress	The Destination Address the Output Port should use

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXProtocolCommon.h` (Public)


#### Free symbols / members of external scopes

- L16 _typedef_ `using IDMXProtocolPtr = TSharedPtr<IDMXProtocol, ESPMode::ThreadSafe>;` — Protocol
- L17 _typedef_ `using IDMXProtocolPtrWeak = TWeakPtr<IDMXProtocol, ESPMode::ThreadSafe>;`
- L20 _typedef_ `using FDMXPortSharedPtr = TSharedPtr<class FDMXPort, ESPMode::ThreadSafe>;` — Ports
- L21 _typedef_ `using FDMXPortSharedRef = TSharedRef<class FDMXPort, ESPMode::ThreadSafe>;`
- L23 _typedef_ `using FDMXInputPortSharedPtr = TSharedPtr<FDMXInputPort, ESPMode::ThreadSafe>;`
- L24 _typedef_ `using FDMXInputPortSharedRef = TSharedRef<FDMXInputPort, ESPMode::ThreadSafe>;`
- L26 _typedef_ `using FDMXOutputPortSharedPtr = TSharedPtr<FDMXOutputPort, ESPMode::ThreadSafe>;`
- L27 _typedef_ `using FDMXOutputPortSharedRef = TSharedRef<FDMXOutputPort, ESPMode::ThreadSafe>;`
- L30 _typedef_ `using FDMXSignalSharedPtr = TSharedPtr<FDMXSignal, ESPMode::ThreadSafe>;` — Signal
- L31 _typedef_ `using FDMXSignalSharedRef = TSharedRef<FDMXSignal, ESPMode::ThreadSafe>;`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXProtocolConstants.h` (Public)


#### enum `(anonymous)`  
``  
_L8-12_

#### Free symbols / members of external scopes

- L9 _enumerator_ `DMX_UNIVERSE_SIZE = 512` (scope `__anon643fa72c0103`)
- L10 _enumerator_ `DMX_MAX_CHANNEL_VALUE = 255` (scope `__anon643fa72c0103`)
- L11 _enumerator_ `RDM_UID_WIDTH = 6` (scope `__anon643fa72c0103`)
- L14 _macro_ `#define DMX_RATE 44`
- L15 _macro_ `#define DMX_MAX_ADDRESS 512`
- L16 _macro_ `#define DMX_MAX_VALUE 255`
- L17 _macro_ `#define DMX_MAX_FUNCTION_SIZE ((int32)sizeof(int32))`
- L18 _macro_ `#define DMX_MAX_UNIVERSE 63999`
- L19 _macro_ `#define DMX_K2_CATEGORY_NAME "DMX"`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXProtocolLog.h` (Public)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogDMXProtocol, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogDMXProtocol, Log, All);`
- L10 _macro_ `#define UE_LOG_DMXPROTOCOL(Verbosity, Format, ...) \`
- L15 _macro_ `#define UE_CLOG_DMXPROTOCOL(Conditional, Verbosity, Format, ...) \`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXProtocolMacros.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define REGISTER_DMX_ARCHIVE(ProtocolDMXPacket) \`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXProtocolModule.h` (Public)


#### struct `FDMXProtocolRegistrationParams`  
`struct FDMXProtocolRegistrationParams`  
_L14-21_
- L17 _public member_ `FName ProtocolName;` — The name to use for the protocol (also used in UIs)
- L20 _public member_ `IDMXProtocolFactory* ProtocolFactory = nullptr;` — The factory used to create the protocol

#### class `FDMXProtocolModule`  
`class FDMXProtocolModule : public IModuleInterface`  
_L31-91_
- inherits: `IModuleInterface`
- desc: Implements the Protocol Module, that enables specific Protocol implementations. For use in Engine, see comments in DMXPortManager.h For protocol development, see comments in IDMXProtocol.h
- L42 _public prototype_ `DECLARE_EVENT_OneParam(FDMXProtocolModule, FDMXOnRequestProtocolRegistrationEvent, TArray<FDMXProtocolRegistrationParams>& );` — Event Broadcast when protocols need to register with the Protocol Module. The event is broadcast at the end of the end of the PreDefault loading phase, so all protocol implementations should be implemented as PreDefault loading phase modules. See DMXProtocolArtNet for an example of a Protocol implementation.
- L43 _public prototype_ `static FDMXOnRequestProtocolRegistrationEvent& GetOnRequestProtocolRegistration();`
- L46 _public prototype_ `DECLARE_EVENT_OneParam(FDMXProtocolModule, FDMXOnRequestProtocolBlocklistEvent, TArray<FName>& );` — Event broadcast so other Plugins can block specific protocols from registering.
- L47 _public prototype_ `static FDMXOnRequestProtocolBlocklistEvent& GetOnRequestProtocolBlocklist();`
- L50 _public prototype_ `void RegisterProtocol(const FName& ProtocolName, IDMXProtocolFactory* Factory);` — `UE_DEPRECATED(4.27, "Please use the OnRequestProtocolRegistration event instead.")`
- L52 _public prototype_ `void UnregisterProtocol(const FName& ProtocolName);`
- L55 _public prototype_ `static FDMXProtocolModule& Get();` — Get the instance of this module.
- L62 _public prototype_ `virtual IDMXProtocolPtr GetProtocol(const FName InProtocolName = NAME_None);` — If protocol exists return the pointer otherwise it create a new protocol first and then return the pointer. @param  InProtocolName Name of the requested protocol @return Return the pointer to protocol.
- L65 _public prototype_ `const TMap<FName, IDMXProtocolFactory*>& GetProtocolFactories() const;` — Get the reference to all protocol factories map
- L68 _public prototype_ `const TMap<FName, IDMXProtocolPtr>& GetProtocols() const;` — Get the reference to all protocols map
- L71 _public prototype_ `virtual void StartupModule() override;`
- L72 _public prototype_ `virtual void ShutdownModule() override;`
- L75 _public member_ `static const FName DefaultProtocolArtNetName;`
- L76 _public member_ `static const FName DefaultProtocolSACNName;`
- L80 _private prototype_ `void OnPluginLoadingPhaseComplete(ELoadingPhase::Type LoadingPhase, bool bPhaseSuccessful);` — Called after each loading phase during startup
- L82 _private prototype_ `void ShutdownDMXProtocol(const FName& ProtocolName);`
- L83 _private prototype_ `void ShutdownAllDMXProtocols();`
- L86 _private member_ `static FDMXOnRequestProtocolRegistrationEvent OnRequestProtocolRegistrationEvent;`
- L87 _private member_ `static FDMXOnRequestProtocolBlocklistEvent OnRequestProtocolBlocklistEvent;`
- L89 _private member_ `TMap<FName, IDMXProtocolFactory*> DMXProtocolFactories;`
- L90 _private member_ `TMap<FName, IDMXProtocolPtr> DMXProtocols;`

#### Free symbols / members of external scopes

- L42 _delegate_ `DECLARE_EVENT_OneParam(FDMXProtocolModule, FDMXOnRequestProtocolRegistrationEvent, TArray<FDMXProtocolRegistrationParams>& );` — Event Broadcast when protocols need to register with the Protocol Module. The event is broadcast at the end of the end of the PreDefault loading phase, so all protocol implementations should be implemented as PreDefault loading phase modules. See DMXProtocolArtNet for an example of a Protocol implementation.
- L46 _delegate_ `DECLARE_EVENT_OneParam(FDMXProtocolModule, FDMXOnRequestProtocolBlocklistEvent, TArray<FName>& );` — Event broadcast so other Plugins can block specific protocols from registering.

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXProtocolObjectVersion.h` (Public)


#### struct `FDMXProtocolObjectVersion`  
`struct FDMXProtocolObjectVersion`  
_L8-31_
- desc: Custom serialization version for changes to DMX Protocol Objects
- L27 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L30 _private function_ `FDMXProtocolObjectVersion()`

#### enum `FDMXProtocolObjectVersion::Type`  
`enum Type`  
_L10-24_
- L13 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Roughly corresponds to 4.27
- L16 _public enumerator_ `OutputPortSupportsManyUnicastAddresses` — Update Ports to allow for an array of Unicast Addresses instead of just one
- L19 _public enumerator_ `FixAttributeNameDefaultValue` — 5.5 fix UE-224455, variable default for FDXMAttribute::Name
- L22 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L23 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXProtocolSettings.h` (Public)


#### class `UDMXProtocolSettings`  
`class UDMXProtocolSettings : public UObject`  
_L22-215_
- reflection: `UCLASS(Config = Engine, DefaultConfig, AutoExpandCategories = ("DMX|Communication Settings"), Meta = (DisplayName = "DMX"))`
- inherits: `UObject`
- desc: DMX Project Settings. Note: To handle Port changes in code please refer to FDMXPortManager.
- L25 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXOnSendDMXEnabled, bool );`
- L26 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXOnReceiveDMXEnabled, bool );`
- L27 _private prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXOnAllFixturePatchesReceiveDMXInEditorEnabled, bool );`
- L33 _public prototype_ `UDMXProtocolSettings();`
- L36 _public prototype_ `virtual void PostInitProperties() override;`
- L38 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L39 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedChainEvent) override;`
- L45 _public function_ `template <typename Predicate> FDMXInputPortConfig* FindInputPortConfig(Predicate Pred)` — Returns the input port matching the predicate, or nullptr if it cannot be found
- L52 _public function_ `template <typename Predicate> FDMXOutputPortConfig* FindOutputPortConfig(Predicate Pred)` — Returns the input port matching the predicate, or nullptr if it cannot be found
- L59 _public member_ `TArray<FDMXInputPortConfig> InputPortConfigs;` — `UPROPERTY(Config, EditAnywhere, Category = "DMX|Communication Settings", Meta = (DisplayName = "Input Ports"))` — DMX Input Port Configs
- L63 _public member_ `TArray<FDMXOutputPortConfig> OutputPortConfigs;` — `UPROPERTY(Config, EditAnywhere, Category = "DMX|Communication Settings", Meta = (DisplayName = "Output Ports"))` — DMX Output Port Configs
- L67 _public member_ `uint32 SendingRefreshRate;` — `UPROPERTY(Config, EditAnywhere, Category = "DMX|Communication Settings", Meta = (ClampMin = "1", ClampMax = "1000"), Meta = (DisplayName = "DMX Send Rate"))` — Rate at which DMX is sent, in Hz from 1 to 1000. 44Hz is recommended.
- L71 _public member_ `uint32 ReceivingRefreshRate_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "ReceivingRefreshRate is deprecated without replacement. It would prevent from precise timestamps on the receivers."))` — Rate at which DMX is received, in Hz from 1 to 1000. 44Hz is recommended
- L75 _public member_ `TSet<FName> FixtureCategories;` — `UPROPERTY(Config, EditAnywhere, Category = "DMX|Fixture Settings", Meta = (DisplayName = "Fixture Categories"))` — Fixture Categories ENum
- L79 _public member_ `TSet<FDMXAttribute> Attributes;` — `UPROPERTY(Config, EditAnywhere, Category = "DMX|Fixture Settings", Meta = (DisplayName = "Fixture Attributes"))` — Common names to map Fixture Functions to and access them easily on Blueprints
- L82 _public function_ `bool IsSendDMXEnabled() const` — Returns whether send DMX is currently enabled, considering runtime override
- L85 _public prototype_ `void OverrideSendDMXEnabled(bool bEnabled);` — Overrides if send DMX is enabled at runtime
- L88 _public function_ `bool IsReceiveDMXEnabled() const` — Returns whether receive DMX is currently enabled, considering runtime override
- L91 _public prototype_ `void OverrideReceiveDMXEnabled(bool bEnabled);` — Overrides if send DMX is enabled at runtime
- L94 _public prototype_ `FString GetUniqueInputPortName() const;` — Returns an automatic/unique name for an InputPort
- L97 _public prototype_ `FString GetUniqueOutputPortName() const;` — Returns an automatic/unique name for an OutputPort
- L100 _public function_ `FSimpleMulticastDelegate& GetOnSendingRefresRateChanged()` — Gets a delegate broadcast when the Sending Refresh Rate (the DMX send rate) changed
- L106 _public function_ `FDMXOnSendDMXEnabled& GetOnSetSendDMXEnabled()` — Gets a delegate broadcast when send DMX is enabled or disabled
- L112 _public function_ `FDMXOnSendDMXEnabled& GetOnSetReceiveDMXEnabled()` — Gets a delegate broadcast when receive DMX is enabled or disabled
- L118 _public function_ `FSimpleMulticastDelegate& GetOnDefaultAttributesChanged()` — Gets a delegate broadcast when default attributes were changed
- L124 _public function_ `FSimpleMulticastDelegate& GetOnDefaultFixtureCategoriesChanged()` — Gets a delegate broadcast when default fixture categories were changed
- L131 _public function_ `bool ShouldAllFixturePatchesReceiveDMXInEditor() const` — Returns true if Fixture Patches should receive DMX in Editor
- L134 _public function_ `FDMXOnAllFixturePatchesReceiveDMXInEditorEnabled& GetOnAllFixturePatchesReceiveDMXInEditorEnabled()` — Gets a Delegate Broadcast when receive DMX is enabled or disabled
- L142 _public member_ `FDMXOnSendDMXEnabled OnSetSendDMXEnabled;` — `UE_DEPRECATED(5.1, "The OnSetSendDMXEnabled delegate is no longer directly accessible. Please use UDMXProtocolSettings::GetOnSetDMXEnabled() instead to access the delegate")` — DEPRECATED 5.1
- L146 _public member_ `FDMXOnReceiveDMXEnabled OnSetReceiveDMXEnabled;` — `UE_DEPRECATED(5.1, "The OnSetReceiveDMXEnabled delegate is no longer directly accessible. Please use UDMXProtocolSettings::GetOnSetReceiveDMXEnabled() instead to access the delegate")` — DEPRECATED 5.1
- L149 _public function_ `FORCEINLINE static FName GetDefaultSendDMXEnabledPropertyName()` — Returns the property name of the bDefaultSendDMXEnabled Property
- L152 _public function_ `FORCEINLINE static FName GetDefaultReceiveDMXEnabledPropertyName()` — Returns the property name of the bDefaultReceiveDMXEnabled Property
- L156 _public function_ `FORCEINLINE static FName GetAllFixturePatchesReceiveDMXInEditorPropertyName()` — Returns the property name of the bDMXComponentRecievesDMXInEditor Property
- L162 _private member_ `bool bDefaultSendDMXEnabled = true;` — `UPROPERTY(Config, EditAnywhere, Category = "DMX|Communication Settings", Meta = (AllowPrivateAccess = true, DisplayName = "Send DMX by default"))` — Whether DMX is sent to the network. Recalled whenever editor or game starts.
- L166 _private member_ `bool bDefaultReceiveDMXEnabled = true;` — `UPROPERTY(Config, EditAnywhere, Category = "DMX|Communication Settings", Meta = (AllowPrivateAccess = true, DisplayName = "Receive DMX by default"))` — Whether DMX is received from the network. Recalled whenever editor or game starts.
- L169 _private member_ `bool bOverrideSendDMXEnabled = true;` — Overrides the default bDefaultSendDMXEnabled value at runtime
- L172 _private member_ `bool bOverrideReceiveDMXEnabled = true;` — Overrides the default bDefaultReceiveDMXEnabled value at runtime
- L175 _private member_ `FSimpleMulticastDelegate OnSendingRefresRateChanged;` — Broadcast the Sending Refresh Rate (the DMX send rate) changed
- L178 _private member_ `FDMXOnSendDMXEnabled OnSetSendDMXEnabledDelegate;` — Broadcast when send DMX is enabled or disabled
- L181 _private member_ `FDMXOnReceiveDMXEnabled OnSetReceiveDMXEnabledDelegate;` — Broadcast when receive DMX is enabled or disabled
- L184 _private member_ `FSimpleMulticastDelegate OnDefaultAttributesChanged;` — Broadcast when default attributets changed
- L187 _private member_ `FSimpleMulticastDelegate OnDefaultFixtureCategoriesChanged;` — Broadcast when default fixture categories changed
- L192 _private member_ `bool bAllFixturePatchesReceiveDMXInEditor = true;` — `UPROPERTY(Config, EditAnywhere, Category = "DMX|Communication Settings", Meta = (DisplayName = "All Fixture Patches receive DMX in Editor"))` — If true, all fixture patches receive DMX in Editor. This overrides the fixture patches 'Receive DMX In Editor' property.
- L195 _private member_ `FDMXOnAllFixturePatchesReceiveDMXInEditorEnabled OnAllFixturePatchesReceiveDMXInEditorEnabled;` — Broadcast when Fixture Patches recieve DMX in Editor is enabled or disabled
- L204 _public member_ `FString InterfaceIPAddress_DEPRECATED;` — `UE_DEPRECATED(4.27, "Now in Port Configs to support many NICs")` — `UPROPERTY(Config, Meta = (DeprecatedProperty, DeprecationMessage = "InterfaceIPAddress is deprecated. Use Ports instead."))` — DEPRECATED 4.27
- L209 _public member_ `int32 GlobalArtNetUniverseOffset_DEPRECATED;` — `UE_DEPRECATED(4.27, "Now in Port Configs to support many NICs")` — `UPROPERTY(Config, Meta = (DeprecatedProperty, DeprecationMessage = "GlobalArtNetUniverseOffset is deprecated. Use Ports instead."))` — DEPRECATED 4.27
- L214 _public member_ `int32 GlobalSACNUniverseOffset_DEPRECATED;` — `UE_DEPRECATED(4.27, "Now in Port Configs to support many NICs")` — `UPROPERTY(Config, Meta = (DeprecatedProperty, DeprecationMessage = "GlobalSACNUniverseOffset is deprecated. Use Ports instead."))` — DEPRECATED 4.27

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXOnSendDMXEnabled, bool );`
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXOnReceiveDMXEnabled, bool );`
- L27 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDMXOnAllFixturePatchesReceiveDMXInEditorEnabled, bool );`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXProtocolTypes.h` (Public)


#### enum `EDMXCommunicationType`  
`enum class EDMXCommunicationType : uint8`  
_L21-27_
- reflection: `UENUM()`
- desc: Type of network communication
- L23 _public enumerator_ `Broadcast`
- L24 _public enumerator_ `Unicast`
- L25 _public enumerator_ `Multicast`
- L26 _public enumerator_ `InternalOnly` — For protocols that do not expose this as a selection to users

#### class `FDMXSignal`  
`class FDMXSignal : public TSharedFromThis<FDMXSignal, ESPMode::ThreadSafe>`  
_L30-71_
- inherits: `TSharedFromThis<FDMXSignal,ESPMode::ThreadSafe>`
- desc: A single, generic DMX signal. One universe of raw DMX data received
- L34 _public function_ `FDMXSignal() : Timestamp() , ExternUniverseID(0) , Priority(0) , ChannelData()`
- L43 _public function_ `FDMXSignal(const double InTimestamp, const int32 InUniverseID, const int32 InPriority, const TArray<uint8>& InChannelData) : Timestamp(InTimestamp) , ExternUniverseID(InUniverseID) , Priority(InPriority) , ChannelData(InChannelData)`
- L50 _public function_ `FDMXSignal(const double InTimestamp, const int32 InUniverseID, const int32 InPriority, TArray<uint8>&& InChannelData) : Timestamp(InTimestamp) , ExternUniverseID(InUniverseID) , ChannelData(InChannelData)`
- L56 _public function_ `void Serialize(FArchive& Ar)`
- L64 _public member_ `double Timestamp;`
- L66 _public member_ `int32 ExternUniverseID;`
- L68 _public member_ `int32 Priority = 100;`
- L70 _public member_ `TArray<uint8> ChannelData;`

#### enum `EDMXSendResult`  
`enum class EDMXSendResult : uint8`  
_L75-83_
- reflection: `UENUM(BlueprintType, Category = "DMX")`
- desc: Result when sending a DMX packet
- L77 _public enumerator_ `Success UMETA(DisplayName = "Successfully sent")`
- L78 _public enumerator_ `ErrorGetUniverse UMETA(DisplayName = "Error Get Universe")`
- L79 _public enumerator_ `ErrorSetBuffer UMETA(DisplayName = "Error Set Buffer")`
- L80 _public enumerator_ `ErrorSizeBuffer UMETA(DisplayName = "Error Size Buffer")`
- L81 _public enumerator_ `ErrorEnqueuePackage UMETA(DisplayName = "Error Enqueue Package")`
- L82 _public enumerator_ `ErrorNoSenderInterface UMETA(DisplayName = "Error No Sending Interface")`

#### enum `EDMXFixtureSignalFormat`  
`enum class EDMXFixtureSignalFormat : uint8`  
_L86-96_
- reflection: `UENUM(BlueprintType, Category = "DMX")`
- L89 _public enumerator_ `E8Bit = 0 UMETA(DisplayName = "8 Bit")` — Uses 1 channel (byte). Range: 0 to 255
- L91 _public enumerator_ `E16Bit = 1 UMETA(DisplayName = "16 Bit")` — Uses 2 channels (bytes). Range: 0 to 65.535
- L93 _public enumerator_ `E24Bit = 2 UMETA(DisplayName = "24 Bit")` — Uses 3 channels (bytes). Range: 0 to 16.777.215
- L95 _public enumerator_ `E32Bit = 3 UMETA(DisplayName = "32 Bit")` — Uses 4 channels (bytes). Range: 0 to 4.294.967.295

#### struct `FDMXProtocolName`  
`struct FDMXProtocolName`  
_L100-155_
- reflection: `USTRUCT(BlueprintType, Category = "DMX")`
- desc: A DMX protocol as a name that can be displayed in UI. The protocol is directly accessible via GetProtocol
- L105 _public prototype_ `FDMXProtocolName();`
- L108 _public prototype_ `explicit FDMXProtocolName(const FName& InName);` — Construct from a protocol name
- L111 _public prototype_ `FDMXProtocolName(IDMXProtocolPtr InProtocol);` — Construct from a protocol
- L114 _public prototype_ `IDMXProtocolPtr GetProtocol() const;` — Returns the Protocol this name represents
- L117 _public function_ `bool IsValid() const` — IsValid member accessor
- L120 _public function_ `operator FName&()`
- L121 _public function_ `operator const FName&() const`
- L124 _public function_ `operator IDMXProtocolPtr()`
- L125 _public function_ `operator const IDMXProtocolPtr() const`
- L129 _public function_ `operator bool() const` — `UE_DEPRECATED(5.1, "Please use IsValid() instead.")` — Bool (is valid) operator
- L133 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "DMX")` — The Protocol Name
- L136 _public function_ `bool operator==(const FDMXProtocolName& Other) const`
- L137 _public function_ `bool operator!=(const FDMXProtocolName& Other) const`
- L138 _public function_ `bool operator==(const IDMXProtocolPtr& Other) const`
- L139 _public function_ `bool operator!=(const IDMXProtocolPtr& Other) const`
- L140 _public function_ `bool operator==(const FName& Other) const`
- L141 _public function_ `bool operator!=(const FName& Other) const`
- L146 _public prototype_ `static TArray<FName> GetPossibleValues();` — `UE_DEPRECATED(5.1, "Instead please use IDMXProtocol::GetProtocolNames")` — Deprecated members originating from deprecated FDMXNameListItem
- L150 _public member_ `static const bool bCanBeNone;` — `UE_DEPRECATED(5.1, "Obsolete. The value never can and never should be none in any case.")` — Deprecated without replacement. Always false.
- L154 _public member_ `static FSimpleMulticastDelegate OnValuesChanged;` — `UE_DEPRECATED(5.1, "Obsolete. Protocols cannot be enabled or disabled after engine startup.")` — Deprecated without replacement. Protocols cannot be enabled or disabled after engine startup.

#### struct `FDMXFixtureCategory`  
`struct FDMXFixtureCategory`  
_L159-201_
- reflection: `USTRUCT(BlueprintType, Category = "DMX")`
- desc: Category of a fixture
- L164 _public prototype_ `static FName GetFirstValue();`
- L166 _public prototype_ `FDMXFixtureCategory();`
- L168 _public prototype_ `explicit FDMXFixtureCategory(const FName& InName);`
- L172 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Category = "DMX")` — The Protocol Name
- L175 _public prototype_ `static TArray<FName> GetPredefinedValues();` — Returns the predefined values
- L178 _public function_ `operator FName&()`
- L179 _public function_ `operator const FName&() const`
- L183 _public function_ `operator bool() const` — `UE_DEPRECATED(5.1, "Please use IsValid() instead.")` — Bool (is valid) operator
- L186 _public function_ `bool operator==(const FDMXFixtureCategory& Other) const`
- L187 _public function_ `bool operator==(const FName& Other) const`
- L192 _public prototype_ `static TArray<FName> GetPossibleValues();` — `UE_DEPRECATED(5.1, "Please use GetPredefinedValues() instead")` — Deprecated members originating from deprecated FDMXNameListItem
- L196 _public member_ `static const bool bCanBeNone;` — `UE_DEPRECATED(5.1, "Obsolete. The value never can and never should be none in any case.")` — Deprecated without replacement. Always false
- L200 _public member_ `static FSimpleMulticastDelegate OnValuesChanged;` — `UE_DEPRECATED(5.1, "Obsolete. To listen to default fixture category changes, please refer to UDMXProtocolSettings::GetOnDefaultFixtureCategoriesChanged().")` — Deprecated without replacement. Protocols cannot be enabled or disabled after engine startup.

#### class `UDMXNameContainersConversions`  
`class UDMXNameContainersConversions : public UBlueprintFunctionLibrary`  
_L204-221_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L211 _public prototype_ `static FString Conv_DMXProtocolNameToString(const FDMXProtocolName& InProtocolName);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (DMX Protocol Name)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|DMX")`
- L214 _public prototype_ `static FName Conv_DMXProtocolNameToName(const FDMXProtocolName& InProtocolName);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "ToName (DMX Protocol Name)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|DMX")`
- L217 _public prototype_ `static FString Conv_DMXFixtureCategoryToString(const FDMXFixtureCategory& InFixtureCategory);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (DMX Fixture Category)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|DMX")`
- L220 _public prototype_ `static FName Conv_DMXFixtureCategoryToName(const FDMXFixtureCategory& InFixtureCategory);` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "ToName (DMX Fixture Category)", CompactNodeTitle = "->", BlueprintAutocast), Category = "Utilities|DMX")`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXProtocolUtils.h` (Public)


#### class `FDMXProtocolUtils`  
`class FDMXProtocolUtils`  
_L10-47_
- L14 _public prototype_ `static TArray<TSharedPtr<FString>> GetLocalNetworkInterfaceCardIPs();` — Returns an array of local network interfaces
- L24 _public prototype_ `static TSharedPtr<FInternetAddr> CreateInternetAddr(const FString& IPAddress, int32 Port);` — Creates an Internet Address @param IPAddress	The IP Address to use @param Port		The Port to use @return			The Internet Address or nullptr if IPAddress and Port don't yield a valid Internet Address
- L27 _public prototype_ `static bool FindLocalNetworkInterfaceCardIPAddress(const FString& InIPAddressWithWildcards, FString& OutLocalNetworkInterfaceCardIPAddress);` — Tries to find a local network interface card IP that matches an IP Address with wildcards
- L33 _public prototype_ `static FString GenerateUniqueNameFromExisting(const TSet<FString>& InExistingNames, const FString& InBaseName);` — Generates a unique name given a base one and a list of existing ones, by appending an index to existing names. If InBaseName is an empty String, it returns "Default name".
- L43 _public prototype_ `static bool GetNameAndIndexFromString(const FString& InString, FString& OutName, int32& OutIndex);` — Utility to separate a name from an index at the end. @param InString	The string to be separated. @param OutName	The string without an index at the end. White spaces and '_' are also removed. @param OutIndex	Index that was separated from the name. If there was none, it's zero. Check the return value to know if there was an index on InString. @return True if there was an index on InString.
- L46 _public prototype_ `FDMXProtocolUtils() = delete;` — can't instantiate this class

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/DMXStats.h` (Public)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_STATS_GROUP(TEXT("DMX"), STATGROUP_DMX, STATCAT_Advance`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/IO/DMXInputPort.h` (Public)


#### class `FDMXInputPort`  
`class FDMXInputPort : public FDMXPort , public FTickableGameObject`  
_L29-158_
- inherits: `FDMXPort,FTickableGameObject`
- desc: Higher level abstraction of a DMX input hiding networking specific and protocol specific complexity from the game. To input DMX into your objects, refer to DMXRawListener and DMXTickedUniverseListener. Can only be constructed via DMXPortManger, see FDMXPortManager::CreateInputPort and FDMXPortManager::CreateInputPortFromConfig
- L41 _protected prototype_ `static FDMXInputPortSharedRef CreateFromConfig(FDMXInputPortConfig& InputPortConfig);` — Creates an output port tied to a specific config. Makes the config valid if it's invalid.
- L44 _public prototype_ `virtual ~FDMXInputPort();`
- L47 _public prototype_ `FDMXInputPortConfig MakeInputPortConfig() const;` — Creates a dmx input port config that corresponds to the port
- L55 _public prototype_ `void UpdateFromConfig(FDMXInputPortConfig& InOutInputPortConfig, bool bForceUpdateRegistrationWithProtocol = false);` — Updates the Port to use the config of the InputPortConfig. Makes the config valid if it's invalid. @param InOutInputPortConfig					The config that is applied. May be changed to a valid config. @param bForceUpdateRegistrationWithProtocol	Optional: Forces the port to update its registration with the protocol (useful for runtime changes)
- L58 _public prototype_ `virtual bool IsRegistered() const override;`
- L59 _public prototype_ `virtual const FGuid& GetPortGuid() const override;`
- L60 _public prototype_ `virtual bool CheckPriority(const int32 InPriority);`
- L62 _protected prototype_ `virtual void AddRawListener(TSharedRef<FDMXRawListener> InRawListener) override;`
- L63 _protected prototype_ `virtual void RemoveRawListener(TSharedRef<FDMXRawListener> InRawListenerToRemove) override;`
- L64 _protected prototype_ `virtual bool Register() override;`
- L65 _protected prototype_ `virtual void Unregister() override;`
- L69 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L70 _protected function_ `virtual bool IsTickableInEditor() const override`
- L71 _protected prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L72 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L77 _public prototype_ `void ClearBuffers();` — Clears all buffers
- L80 _public prototype_ `void InputDMXSignal(const FDMXSignalSharedRef& DMXSignal);` — Thread-safe: Pushes a DMX Signal into the buffer
- L84 _public prototype_ `void SingleProducerInputDMXSignal(const FDMXSignalSharedRef& DMXSignal);` — `UE_DEPRECATED(5.0, "Input ports now support multiple producers. Use InputDMXSignal instead.")` — Single Producer thread-safe: Pushes a DMX Signal into the buffer (For protocol only)
- L87 _public prototype_ `bool GameThreadGetDMXSignal(int32 LocalUniverseID, FDMXSignalSharedPtr& OutDMXSignal);` — Gets the last signal received in specified local universe. Returns false if no signal was received. Game-Thread only
- L90 _public prototype_ `const TMap<int32, FDMXSignalSharedPtr>& GameThreadGetAllDMXSignals() const;` — Gets all the last signal received. Game-Thread only
- L94 _public prototype_ `bool GameThreadGetDMXSignalFromRemoteUniverse(FDMXSignalSharedPtr& OutDMXSignal, int32 RemoteUniverseID, bool bEvenIfNotLoopbackToEngine = false);` — `UE_DEPRECATED(4.27, "Use GameThreadGetDMXSignal instead. GameThreadGetDMXSignalFromRemoteUniverse only exists to support deprecated blueprint nodes.")` — DEPRECATED 4.27. Gets the DMX signal from an extern (remote) Universe ID.
- L97 _public function_ `bool IsReceiveDMXEnabled() const` — Returns true if receive DMX is disabled
- L104 _public prototype_ `void GameThreadInjectDMXSignal(const FDMXSignalSharedRef& DMXSignal);` — Injects a dmx signal into the game thread. Note, only signals get from game thread are affected but not raw listeners. Useful for nDisplay replication.
- L111 _public prototype_ `void SetUseDefaultQueue(bool bUse);` — Sets if the port should listen to its default queue. If false, another raw listener can create the default queue by adding a raw listener and inject its data via GameThreadInjectDMXSignal Useful for nDisplay replication.
- L115 _private prototype_ `void OnSetReceiveDMXEnabled(bool bEnabled);` — Called to set if receive DMX should be enabled
- L118 _private member_ `TQueue<FDMXSignalSharedPtr, EQueueMode::Mpsc> DefaultInputQueue;` — The default buffer, which is being read on tick
- L121 _private member_ `bool bReceiveDMXEnabled = false;` — According to DMXProtcolSettings, true if DMX should be received
- L124 _private member_ `bool bUseDefaultInputQueue = true;` — If true, adds data to the default input queue and fills the UniverseToLatestSignalMap with it
- L127 _private member_ `EDMXPortPriorityStrategy PriorityStrategy;` — How to manage priority
- L130 _private member_ `int32 Priority;` — the Priority value, used by the PriorityStrategy
- L133 _private member_ `int32 HighestReceivedPriority = 0;` — The highest priority received
- L136 _private member_ `int32 LowestReceivedPriority = 0;` — The highest priority received
- L139 _private member_ `TMap<int32, TSet<TSharedRef<FDMXTickedUniverseListener>>> LocalUniverseToListenerGroupMap;` — Map of Universe Inputs with their Universes
- L142 _private member_ `TMap<int32, FDMXSignalSharedPtr> ExternUniverseToLatestSignalMap;` — Map of latest Singals per extern Universe
- L145 _private member_ `TSet<TSharedRef<FDMXRawListener>> RawListeners;` — Map of raw isteners
- L148 _private member_ `FCriticalSection AccessRawListenersMutex;` — Mutex access for the RawListeners array
- L151 _private member_ `bool bPendingRegistration = false;` — True while registration is pending
- L154 _private member_ `TAtomic<bool> bRegistered = false;` — True if the port is registered with it its protocol
- L157 _private member_ `FGuid PortGuid;` — The unique identifier of this port, shared with the port config this was constructed from. Should not be changed after construction.

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/IO/DMXInputPortConfig.h` (Public)


#### enum `EDMXPortPriorityStrategy`  
`enum class EDMXPortPriorityStrategy : uint8`  
_L24-38_
- reflection: `UENUM()`
- desc: Strategy for priority system (when receiving packets) Not: Not all protocols have a use for this
- L27 _public enumerator_ `None` — Always manage the packet
- L29 _public enumerator_ `Equal` — Manage the packet only if the priority is equal to the specified value
- L31 _public enumerator_ `HigherThan` — Manage the packet only if the priority is higher than the specified value
- L33 _public enumerator_ `LowerThan` — Manage the packet only if the priority is lower than the specified value
- L35 _public enumerator_ `Highest` — Manage the packet only if it matches the highest received priority
- L37 _public enumerator_ `Lowest` — Manage the packet only if it matches the lowest received priority

#### struct `FDMXInputPortConfigParams`  
`struct FDMXInputPortConfigParams`  
_L41-57_
- desc: Data to create a new input port config with related constructor.
- L43 _public prototype_ `FDMXInputPortConfigParams() = default;`
- L44 _public prototype_ `FDMXInputPortConfigParams(const FDMXInputPortConfig& InputPortConfig);`
- L46 _public member_ `FString PortName;`
- L47 _public member_ `FName ProtocolName;`
- L48 _public member_ `EDMXCommunicationType CommunicationType;`
- L49 _public member_ `bool bAutoCompleteDeviceAddressEnabled;`
- L50 _public member_ `FString AutoCompleteDeviceAddress;`
- L51 _public member_ `FString DeviceAddress;`
- L52 _public member_ `int32 LocalUniverseStart;`
- L53 _public member_ `int32 NumUniverses;`
- L54 _public member_ `int32 ExternUniverseStart;`
- L55 _public member_ `EDMXPortPriorityStrategy PriorityStrategy;`
- L56 _public member_ `int32 Priority;`

#### struct `FDMXInputPortConfig`  
`struct FDMXInputPortConfig`  
_L65-185_
- reflection: `USTRUCT(BlueprintType)`
- desc: Blueprint Configuration of a Port, used in DXM Settings to specify inputs and outputs. Property changes are handled in details customization consistently.
- L71 _public prototype_ `FDMXInputPortConfig();` — Default constructor, only for Default Objects
- L74 _public prototype_ `explicit FDMXInputPortConfig(const FGuid& InPortGuid);` — Constructs a config from the guid
- L77 _public prototype_ `FDMXInputPortConfig(const FGuid& InPortGuid, const FDMXInputPortConfigParams& InitializationData);` — Constructs a config from the guid and given initialization data
- L80 _public prototype_ `void MakeValid();` — Changes members to result in a valid config
- L83 _public prototype_ `void Upgrade();` — Upgrades this config to the latest engine version
- L85 _public function_ `const FString& GetPortName() const`
- L86 _public function_ `const FName& GetProtocolName() const`
- L87 _public function_ `EDMXCommunicationType GetCommunicationType() const`
- L88 _public function_ `bool IsAutoCompleteDeviceAddressEnabled() const`
- L89 _public function_ `FString GetAutoCompleteDeviceAddress() const`
- L90 _public prototype_ `FString GetDeviceAddress() const;`
- L91 _public function_ `int32 GetLocalUniverseStart() const`
- L92 _public function_ `int32 GetNumUniverses() const`
- L93 _public function_ `int32 GetExternUniverseStart() const`
- L94 _public function_ `const FGuid& GetPortGuid() const`
- L95 _public function_ `const EDMXPortPriorityStrategy GetPortPriorityStrategy() const`
- L96 _public function_ `const int32 GetPriority() const`
- L99 _public function_ `static FName GetPortNamePropertyNameChecked()`
- L100 _public function_ `static FName GetProtocolNamePropertyNameChecked()`
- L101 _public function_ `static FName GetCommunicationTypePropertyNameChecked()`
- L102 _public function_ `static FName GetAutoCompleteDeviceAddressEnabledPropertyNameChecked()`
- L103 _public function_ `static FName GetAutoCompleteDeviceAddressPropertyNameChecked()`
- L104 _public function_ `static FName GetDeviceAddressPropertyNameChecked()`
- L105 _public function_ `static FName GetLocalUniverseStartPropertyNameChecked()`
- L106 _public function_ `static FName GetNumUniversesPropertyNameChecked()`
- L107 _public function_ `static FName GetExternUniverseStartPropertyNameChecked()`
- L108 _public function_ `static FName GetIsExternUnivereStartEditablePropertyNameChecked()`
- L109 _public function_ `static FName GetPriorityStrategyPropertyNameChecked()`
- L110 _public function_ `static FName GetPriorityPropertyNameChecked()`
- L111 _public function_ `static FName GetPortGuidPropertyNameChecked()`
- L117 _protected member_ `FString PortName;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config")` — The name displayed wherever the port can be displayed
- L121 _protected member_ `FName ProtocolName = FDMXProtocolModule::DefaultProtocolArtNetName;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config", Meta = (DisplayName = "Protocol Type"))` — DMX Protocol
- L125 _protected member_ `EDMXCommunicationType CommunicationType = EDMXCommunicationType::InternalOnly;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config")` — The type of communication used with this port
- L129 _protected member_ `bool bAutoCompleteDeviceAddressEnabled = false;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config")` — Enables 'Auto Complete Device Address', hidden via customization - EditConditionInlineToggle doesn't support Config
- L142 _protected member_ `FString AutoCompleteDeviceAddress = TEXT("192` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config", Meta = (DisplayName = "Auto Complete Network Interface Card IP Address"))` — Searches available Network Interface Card IP Addresses and uses the first match as the 'Network Interface Card IP Address' (both in Editor and Game). Supports wildcards, examples: '192' '192.*' '192.168.?.*'. If empty or '*' the first best available IP will be selected (not recommended)
- L146 _protected member_ `FString DeviceAddress = TEXT("127` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config", Meta = (DisplayName = "Network Interface Card IP Address"))` — The Network Interface Card's IP Adress, over which DMX is received
- L150 _protected member_ `int32 LocalUniverseStart = 1;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config")` — Local Start Universe
- L154 _protected member_ `int32 NumUniverses = 10;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config", Meta = (DisplayName = "Amount of Universes"))` — Number of Universes
- L161 _protected member_ `int32 ExternUniverseStart = 1;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config", Meta = (DisplayName = "Protocol Universe Remap"))` — Remaps the range of local Universes (Num Universes from Local Universe Start) to a different set of Universes at the Protocol level. For example, for Art-Net this allows to map local Universe 1 to extern Universe 0.
- L166 _protected member_ `bool bIsExternUnivereStartEditable = false;` — `UPROPERTY(Config, EditDefaultsOnly, Category = "Port Config")` — Edit condition for the ExternUniverseStart property
- L171 _protected member_ `EDMXPortPriorityStrategy PriorityStrategy = EDMXPortPriorityStrategy::Highest;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config")` — How to deal with the priority value
- L175 _protected member_ `int32 Priority = 0;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config")` — Priority value, can act as a filter or a threshold
- L184 _protected member_ `FGuid PortGuid;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config Guid", meta = (IgnoreForMemberInitializationTest))` — Unique identifier, shared with the port instance. Note: This needs be BlueprintReadWrite to be accessible to property type customization, but is hidden by customization.

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/IO/DMXInputPortReference.h` (Public)


#### struct `FDMXInputPortReference`  
`struct FDMXInputPortReference`  
_L15-105_
- reflection: `USTRUCT(BlueprintType)`
- desc: Reference of an input port
- L19 _public function_ `FDMXInputPortReference() : bEnabledFlag(true)`
- L29 _public function_ `FDMXInputPortReference(const FGuid& InPortGuid, bool bIsEnabledFlag) : PortGuid(InPortGuid) , bEnabledFlag(bIsEnabledFlag)`
- L45 _public function_ `FDMXInputPortReference(const FDMXInputPortReference& InInputPortReference, bool bIsEnabledFlag) : PortGuid(InInputPortReference.PortGuid) , bEnabledFlag(bIsEnabledFlag)`
- L62 _public function_ `bool IsEnabledFlagSet() const` — Returns true if the port is enabled. Always true unless constructed with bIsAlwaysEnabled = false
- L71 _public function_ `bool operator==(const FDMXInputPortReference& Other) const`
- L76 _public function_ `bool operator!=(const FDMXInputPortReference& Other) const`
- L86 _public function_ `const FGuid& GetPortGuid() const`
- L89 _public function_ `FGuid& GetMutablePortGuid()` — Returns a non const Guid of the port, required for serialization only
- L91 _public function_ `static FName GetPortGuidPropertyName()`
- L92 _public function_ `static FName GetEnabledFlagPropertyName()`
- L100 _protected member_ `FGuid PortGuid;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DMX")` — Unique identifier shared with port config and port instance. Note: This needs be BlueprintReadWrite to be accessible to property type customization, but is hidden by customization.
- L104 _protected member_ `uint32 bEnabledFlag : 1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DMX")` — Optional flag for port references that can be enabled or disabled

#### Free symbols / members of external scopes

- L37 _function_ `` (scope `FDMXInputPortReference::FDMXInputPortReference`)
- L64 _function_ `friend FArchive& operator<<(FArchive& Ar, FDMXInputPortReference& InputPortReference)`
- L81 _function_ `FORCEINLINE_DEBUGGABLE friend uint32 GetTypeHash(const FDMXInputPortReference& PortReference)`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/IO/DMXOutputPort.h` (Public)


#### struct `FDMXOutputPortCommunicationDeterminator`  
`struct FDMXOutputPortCommunicationDeterminator`  
_L25-63_
- desc: Helper to determine how DMX should be communicated (loopback, send)
- L27 _public function_ `FDMXOutputPortCommunicationDeterminator() : bLoopbackToEngine(false) , bReceiveEnabled(true) , bSendEnabled(true) , bHasValidSender(false)`
- L35 _public function_ `void SetLoopbackToEngine(bool bInLoopbackToEngine)` — Set the variable from the port config in project settings
- L38 _public function_ `void SetReceiveEnabled(bool bInReceiveEnabled)` — Sets if receive is enabled
- L41 _public function_ `void SetSendEnabled(bool bInSendEnabled)` — Sets if send is enabled
- L44 _public function_ `void SetHasValidSender(bool bInHasValidSender)` — Sets if there is a valid sender obj
- L47 _public function_ `bool NeedsLoopbackToEngine() const` — Determinates if loopback to engine is needed (may be true even is loopback to engine is not enabled)
- L50 _public function_ `bool NeedsSendDMX() const` — Determinates if dmx needs to be sent (may be false even if send is enabled)
- L53 _public function_ `bool IsSendDMXEnabled() const` — Determinates if send dmx is enabled
- L56 _public function_ `bool IsLoopbackToEngineEnabled() const` — Returns true if loopback to engine is enabled (only true if loopback to engine is set enabled)
- L59 _private member_ `TAtomic<bool> bLoopbackToEngine;`
- L60 _private member_ `TAtomic<bool> bReceiveEnabled;`
- L61 _private member_ `TAtomic<bool> bSendEnabled;`
- L62 _private member_ `TAtomic<bool> bHasValidSender;`

#### struct `FDMXSignalFragment`  
`struct FDMXSignalFragment : TSharedFromThis<FDMXSignalFragment, ESPMode::ThreadSafe>`  
_L67-86_
- inherits: `TSharedFromThis<FDMXSignalFragment,ESPMode::ThreadSafe>`
- desc: Structs that holds the fragmented values to be sent along with a timestamp when to send it
- L70 _public prototype_ `FDMXSignalFragment() = delete;`
- L72 _public function_ `FDMXSignalFragment(int32 InExternUniverseID, const TMap<int32, uint8>& InChannelToValueMap, double InSendTime) : ExternUniverseID(InExternUniverseID) , ChannelToValueMap(InChannelToValueMap) , SendTime(InSendTime)`
- L79 _public member_ `int32 ExternUniverseID;` — The universe the fragment needs to be written to
- L82 _public member_ `TMap<int32, uint8> ChannelToValueMap;` — The map of channels and values to send
- L85 _public member_ `double SendTime;` — The time when the Fragment needs be sent

#### class `FDMXOutputPort`  
`class FDMXOutputPort : public FDMXPort , public FRunnable , public FSingleThreadRunnable`  
_L96-251_
- inherits: `FDMXPort,FRunnable,FSingleThreadRunnable`
- desc: Higher level abstraction of a DMX input hiding networking specific and protocol specific complexity. Ment to be constructed by DMXPortManger only. Use SendDMX method to send DMX. To loopback outputs, refer to DMXRawListener.
- L109 _protected prototype_ `static FDMXOutputPortSharedRef CreateFromConfig(FDMXOutputPortConfig& OutputPortConfig);` — Creates an output port tied to a specific config. Hidden on purpose, use FDMXPortManager to create instances
- L112 _public prototype_ `virtual ~FDMXOutputPort();`
- L115 _public prototype_ `FDMXOutputPortConfig MakeOutputPortConfig() const;` — Creates a dmx output port config that corresponds to the port
- L123 _public prototype_ `void UpdateFromConfig(FDMXOutputPortConfig& OutputPortConfig, bool bForceUpdateRegistrationWithProtocol = false);` — Updates the Port to use the config of the OutputPortConfig. Makes the config valid if it's invalid. @param InOutInputPortConfig					The config that is applied. May be changed to a valid config. @param bForceUpdateRegistrationWithProtocol	Optional: Forces the port to update its registration with the protocol (useful for runtime changes)
- L126 _public prototype_ `void SendDMX(int32 LocalUniverseID, const TMap<int32, uint8>& ChannelToValueMap);` — Sends DMX over the port
- L130 _public prototype_ `void SendDMXToRemoteUniverse(const TMap<int32, uint8>& ChannelToValueMap, int32 RemoteUniverse);` — `UE_DEPRECATED(4.27, "Use SenDMX instead. SendDMXToRemoteUniverse only exists to support deprecated blueprint nodes.")` — DEPRECATED 4.27. Sends DMX over the port with an extern (remote) Universe ID. Soly here to support legacy functions that would send to an extern universe
- L133 _public prototype_ `void ClearBuffers();` — Clears all buffers
- L143 _public prototype_ `bool GameThreadGetDMXSignal(int32 LocalUniverseID, FDMXSignalSharedPtr& OutDMXSignal, bool bEvenIfNotLoopbackToEngine);` — Game-Thread only: Gets the last signal received in specified local universe. @param LocalUniverseID				The local universe that should be retrieved @param OutDMXSignal					The signal that is set if the opperation succeeds. @param bEvenIfNotLoopbackToEngine	Defaults to false. If true, succeeds even if the signal should not be looped back to engine (useful for monitoring). @return								True if the OutDMXSignal was set.
- L146 _public prototype_ `TArray<FString> GetDestinationAddresses() const;` — Returns the Destination Addresses
- L150 _public prototype_ `bool GameThreadGetDMXSignalFromRemoteUniverse(FDMXSignalSharedPtr& OutDMXSignal, int32 RemoteUniverseID, bool bEvenIfNotLoopbackToEngine);` — `UE_DEPRECATED(4.27, "Use GameThreadGetDMXSignal instead. GameThreadGetDMXSignalFromRemoteUniverse only exists to support deprecated blueprint nodes.")` — DEPRECATED 4.27. Gets the DMX signal from an extern (remote) Universe ID.
- L153 _public function_ `uint8 GetTimeToLive() const` — Returns the multicast Time-to-Live (TTL), only used when the port is set to multicast
- L156 _public function_ `double GetDelaySeconds() const` — Returns the output port's delay in seconds
- L160 _public prototype_ `virtual bool IsRegistered() const override;`
- L161 _public prototype_ `virtual const FGuid& GetPortGuid() const override;`
- L164 _protected prototype_ `virtual void AddRawListener(TSharedRef<FDMXRawListener> InRawListener) override;`
- L165 _protected prototype_ `virtual void RemoveRawListener(TSharedRef<FDMXRawListener> InRawListenerToRemove) override;`
- L166 _protected prototype_ `virtual bool Register() override;`
- L167 _protected prototype_ `virtual void Unregister() override;`
- L171 _protected prototype_ `void OnSendingRefreshRateChanged();` — Called when the DMX send rate changed
- L174 _protected prototype_ `void OnSetSendDMXEnabled(bool bEnabled);` — Called to set if DMX should be enabled
- L177 _protected prototype_ `void OnSetReceiveDMXEnabled(bool bEnabled);` — Called to set if DMX should be enabled
- L180 _protected prototype_ `virtual bool Init() override;`
- L181 _protected prototype_ `virtual uint32 Run() override;`
- L182 _protected prototype_ `virtual void Stop() override;`
- L183 _protected prototype_ `virtual void Exit() override;`
- L187 _protected prototype_ `virtual void Tick() override;`
- L188 _protected prototype_ `virtual class FSingleThreadRunnable* GetSingleThreadInterface() override;`
- L192 _protected prototype_ `void ProcessSendDMX();` — Updates the thread, sending DMX
- L196 _private member_ `TArray<TSharedPtr<IDMXSender>> DMXSenderArray;` — The DMX senders in use
- L199 _private member_ `TQueue<TSharedPtr<FDMXSignalFragment, ESPMode::ThreadSafe>> SignalFragments;` — Buffer of the signals that are to be sent in the next frame
- L202 _private member_ `TMap<int32, FDMXSignalSharedPtr> ExternUniverseToLatestSignalMap_GameThread;` — Map that holds the latest Signal per Universe on the Game Thread
- L205 _private member_ `TMap<int32, FDMXSignalSharedPtr> ExternUniverseToLatestSignalMap_PortThread;` — Map that holds the latest Signal per Universe on the Port Thread
- L208 _private member_ `TArray<FDMXOutputPortDestinationAddress> DestinationAddresses;` — The Destination Address to send to, can be irrelevant, e.g. for art-net broadcast
- L211 _private member_ `FDMXOutputPortCommunicationDeterminator CommunicationDeterminator;` — Helper to determine how dmx should be communicated (loopback, send)
- L214 _private member_ `mutable FCriticalSection SendDMXMutex;` — Mutex access to members required to send DMX
- L217 _private member_ `uint8 TimeToLive = 1;` — Multicast Time-to-Live (TTL), only used when the port is set to multicast
- L220 _private member_ `int32 Priority = 0;` — Priority on which packets are being sent
- L223 _private member_ `TSet<TSharedRef<FDMXRawListener>> RawListeners;` — Map of raw Inputs
- L226 _private member_ `bool bPendingRegistration = false;` — True while registration is pending
- L229 _private member_ `TAtomic<bool> bRegistered = false;` — True if the port is registered with its protocol
- L232 _private member_ `FGuid PortGuid;` — The unique identifier of this port, shared with the port config this was constructed from. Should not be changed after construction.
- L235 _private member_ `TAtomic<uint32> SendRate = 44.f;` — Current send rate, set from project settings (see OnSendingRefreshRateChanged)
- L238 _private member_ `double DelaySeconds = 0.0;` — Delay to apply on packets being sent
- L241 _private member_ `FFrameRate DelayFrameRate;` — The frame rate of the delay
- L244 _private member_ `FEvent* SendDMXEvent = nullptr;` — Send DMX sync event
- L247 _private member_ `FRunnableThread* Thread = nullptr;` — Holds this thread object
- L250 _private member_ `TAtomic<bool> bStopping;` — Flag indicating that the thread is stopping.

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/IO/DMXOutputPortConfig.h` (Public)


#### struct `FDMXOutputPortDestinationAddress`  
`struct FDMXOutputPortDestinationAddress`  
_L21-38_
- reflection: `USTRUCT(BlueprintType)`
- desc: The IP address outbound DMX is sent to
- L25 _public prototype_ `FDMXOutputPortDestinationAddress() = default;`
- L27 _public function_ `FDMXOutputPortDestinationAddress(const FString& DestinationAddress) : DestinationAddressString(DestinationAddress)`
- L33 _public member_ `FString DestinationAddressString;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config", Meta = (DisplayName = "Destination IP Address"))` — The IP address outbound DMX is sent to
- L35 _public function_ `bool operator==(const FDMXOutputPortDestinationAddress& Other) const`
- L36 _public function_ `bool operator!=(const FDMXOutputPortDestinationAddress& Other) const`

#### struct `FDMXOutputPortConfigParams`  
`struct FDMXOutputPortConfigParams`  
_L41-64_
- desc: Data to create a new output port config with related constructor
- L43 _public prototype_ `FDMXOutputPortConfigParams() = default;`
- L44 _public prototype_ `FDMXOutputPortConfigParams(const FDMXOutputPortConfig& OutputPortConfig);`
- L46 _public member_ `FString PortName;`
- L47 _public member_ `FName ProtocolName;`
- L48 _public member_ `EDMXCommunicationType CommunicationType;`
- L49 _public member_ `uint8 TimeToLive;`
- L50 _public member_ `bool bAutoCompleteDeviceAddressEnabled;`
- L51 _public member_ `FString AutoCompleteDeviceAddress;`
- L52 _public member_ `FString DeviceAddress;`
- L53 _public member_ `TArray<FDMXOutputPortDestinationAddress> DestinationAddresses;`
- L54 _public member_ `bool bLoopbackToEngine;`
- L55 _public member_ `int32 LocalUniverseStart;`
- L56 _public member_ `int32 NumUniverses;`
- L57 _public member_ `int32 ExternUniverseStart;`
- L58 _public member_ `int32 Priority;`
- L59 _public member_ `double Delay;`
- L60 _public member_ `FFrameRate DelayFrameRate;`
- L63 _public member_ `FString DestinationAddress_DEPRECATED;` — DEPRECATED 5.0. Instead please use the DestinationAddresses array.

#### struct `FDMXOutputPortConfig`  
`struct FDMXOutputPortConfig`  
_L72-225_
- reflection: `USTRUCT(BlueprintType)`
- desc: Blueprint Configuration of a Port, used in DXM Settings to specify inputs and outputs. Property changes are handled in details customization consistently.
- L78 _public prototype_ `FDMXOutputPortConfig();` — Default constructor, only for Default Objects
- L81 _public prototype_ `explicit FDMXOutputPortConfig(const FGuid & InPortGuid);` — Constructs a config from the guid
- L84 _public prototype_ `FDMXOutputPortConfig(const FGuid & InPortGuid, const FDMXOutputPortConfigParams& InitializationData);` — Constructs a config from the guid and given initialization data
- L87 _public prototype_ `void MakeValid();` — Changes members to result in a valid config
- L90 _public prototype_ `void Upgrade();` — Upgrades this config to the latest engine version
- L92 _public function_ `const FString& GetPortName() const`
- L93 _public function_ `const FName& GetProtocolName() const`
- L94 _public function_ `EDMXCommunicationType GetCommunicationType() const`
- L95 _public function_ `uint8 GetTimeToLive() const`
- L96 _public function_ `bool IsAutoCompleteDeviceAddressEnabled() const`
- L97 _public function_ `FString GetAutoCompleteDeviceAddress() const`
- L98 _public prototype_ `FString GetDeviceAddress() const;`
- L99 _public function_ `const TArray<FDMXOutputPortDestinationAddress>& GetDestinationAddresses() const`
- L100 _public function_ `bool NeedsLoopbackToEngine() const`
- L101 _public function_ `int32 GetLocalUniverseStart() const`
- L102 _public function_ `int32 GetNumUniverses() const`
- L103 _public function_ `int32 GetExternUniverseStart() const`
- L104 _public function_ `int32 GetPriority() const`
- L105 _public function_ `const FGuid& GetPortGuid() const`
- L106 _public function_ `double GetDelay() const`
- L107 _public function_ `const FFrameRate& GetDelayFrameRate() const`
- L110 _public function_ `const FString& GetDestinationAddress() const` — `UE_DEPRECATED(5.0, "Output Ports now support many destination addresses. Use FDMXOutputPortConfig::GetDestinationAddresses instead. ")`
- L113 _public function_ `static FName GetPortNamePropertyNameChecked()`
- L114 _public function_ `static FName GetProtocolNamePropertyNameChecked()`
- L115 _public function_ `static FName GetCommunicationTypePropertyNameChecked()`
- L116 _public function_ `static FName GetAutoCompleteDeviceAddressEnabledPropertyNameChecked()`
- L117 _public function_ `static FName GetAutoCompleteDeviceAddressPropertyNameChecked()`
- L118 _public function_ `static FName GetDeviceAddressPropertyNameChecked()`
- L119 _public function_ `static FName GetDestinationAddressesPropertyNameChecked()`
- L120 _public function_ `static FName GetLocalUniverseStartPropertyNameChecked()`
- L121 _public function_ `static FName GetNumUniversesPropertyNameChecked()`
- L122 _public function_ `static FName GetExternUniverseStartPropertyNameChecked()`
- L123 _public function_ `static FName GetIsExternUnivereStartEditablePropertyNameChecked()`
- L124 _public function_ `static FName GetPriorityPropertyNameChecked()`
- L125 _public function_ `static FName GetDelayPropertyNameChecked()`
- L126 _public function_ `static FName GetDelayFrameRatePropertyNameChecked()`
- L127 _public function_ `static FName GetPortGuidPropertyNameChecked()`
- L130 _public function_ `static FName GetDestinationAddressPropertyNameChecked()` — `UE_DEPRECATED(5.0, "Output Ports now support many destination addresses. Use FDMXOutputPortConfig::GetDestinationAddressesPropertyNameChecked instead. ")`
- L136 _protected member_ `FString PortName;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config")` — The name displayed wherever the port can be displayed
- L140 _protected member_ `FName ProtocolName = FDMXProtocolModule::DefaultProtocolArtNetName;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config", Meta = (DisplayName = "Protocol Type"))` — DMX Protocol
- L144 _protected member_ `EDMXCommunicationType CommunicationType = EDMXCommunicationType::InternalOnly;` — `UPROPERTY(Config, BlueprintReadWrite, EditDefaultsOnly, Category = "Port Config")` — The type of communication used with this port
- L148 _protected member_ `uint8 TimeToLive = 1;` — `UPROPERTY()` — Sets how many hops multicast DMX packets can take before being discarded. In common network setups this should be set to 1.
- L152 _protected member_ `bool bAutoCompleteDeviceAddressEnabled = false;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config")` — Enables 'Auto Complete Device Address', hidden via customization - EditConditionInlineToggle doesn't support Config
- L165 _protected member_ `FString AutoCompleteDeviceAddress = TEXT("192` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config", Meta = (DisplayName = "Auto Complete Network Interface Card IP Address"))` — Searches available Network Interface Card IP Addresses and uses the first match as the 'Network Interface Card IP Address' (both in Editor and Game). Supports wildcards, examples: '192' '192.*' '192.168.?.*'.. If empty or '*' the first best available IP will be selected (not recommended)
- L169 _protected member_ `FString DeviceAddress = TEXT("127` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config", Meta = (DisplayName = "Network Interface Card IP Address"))` — The IP address of the network interface card over which outbound DMX is sent
- L173 _protected member_ `FString DestinationAddress = TEXT("Non` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "DestinationAddress is deprecated. Please use DestinationAddresses instead."))` — For Unicast, the IP address outbound DMX is sent to
- L177 _protected member_ `TArray<FDMXOutputPortDestinationAddress> DestinationAddresses;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config", Meta = (DisplayName = "Destination IP Address"))` — For Unicast, the IP addresses outbound DMX is sent to
- L181 _protected member_ `bool bLoopbackToEngine = true;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config", Meta = (DisplayName = "Input into Engine"))` — If true, the signals output from this port are input into to the engine. Note, signals input into the engine this way will not be visible in Monitors when monitoring Inputs.
- L185 _protected member_ `int32 LocalUniverseStart = 1;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config")` — Local Start Universe
- L189 _protected member_ `int32 NumUniverses = 10;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config", Meta = (DisplayName = "Amount of Universes"))` — Number of Universes
- L196 _protected member_ `int32 ExternUniverseStart = 1;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config", Meta = (DisplayName = "Protocol Universe Remap"))` — Remaps the range of local Universes (Num Universes from Local Universe Start) to a different set of Universes at the Protocol level. For example, for Art-Net this allows to map local Universe 1 to extern Universe 0.
- L201 _protected member_ `bool bIsExternUnivereStartEditable = false;` — `UPROPERTY(Config, EditDefaultsOnly, Category = "Port Config")` — Edit condition for the ExternUniverseStart property
- L206 _protected member_ `int32 Priority = 100;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config")` — Priority on which packets are being sent
- L210 _protected member_ `double Delay = 0.0;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config")` — The amout by which sending of packets is delayed
- L214 _protected member_ `FFrameRate DelayFrameRate;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config")` — Framerate of the delay
- L224 _protected member_ `FGuid PortGuid;` — `UPROPERTY(Config, BlueprintReadOnly, EditDefaultsOnly, Category = "Port Config Guid", meta = (IgnoreForMemberInitializationTest))`

#### Free symbols / members of external scopes

- L37 _function_ `friend uint32 GetTypeHash(const FDMXOutputPortDestinationAddress& Key)`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/IO/DMXOutputPortReference.h` (Public)


#### struct `FDMXOutputPortReference`  
`struct FDMXOutputPortReference`  
_L15-102_
- reflection: `USTRUCT(BlueprintType)`
- desc: Reference of an input port
- L19 _public function_ `FDMXOutputPortReference() : bEnabledFlag(true)`
- L29 _public function_ `FDMXOutputPortReference(const FGuid& InPortGuid, bool bIsEnabledFlag) : PortGuid(InPortGuid) , bEnabledFlag(bIsEnabledFlag)`
- L45 _public function_ `FDMXOutputPortReference(const FDMXOutputPortReference& InOutputPortReference, bool bIsEnabledFlag) : PortGuid(InOutputPortReference.PortGuid) , bEnabledFlag(bIsEnabledFlag)`
- L62 _public function_ `bool IsEnabledFlagSet() const` — Returns true if the port is enabled. Always true unless constructed with bIsAlwaysEnabled = false
- L71 _public function_ `bool operator==(const FDMXOutputPortReference& Other) const`
- L76 _public function_ `bool operator!=(const FDMXOutputPortReference& Other) const`
- L86 _public function_ `const FGuid& GetPortGuid() const`
- L88 _public function_ `static FName GetPortGuidPropertyName()`
- L89 _public function_ `static FName GetEnabledFlagPropertyName()`
- L97 _protected member_ `FGuid PortGuid;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DMX")` — Unique identifier shared with port config and port instance. Note: This needs be BlueprintReadWrite to be accessible to property type customization, but is hidden by customization.
- L101 _protected member_ `bool bEnabledFlag;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DMX")` — Optional flag for port references that can be enabled or disabled

#### Free symbols / members of external scopes

- L37 _function_ `` (scope `FDMXOutputPortReference::FDMXOutputPortReference`)
- L64 _function_ `friend FArchive& operator<<(FArchive& Ar, FDMXOutputPortReference& OutputPortReference)`
- L81 _function_ `FORCEINLINE_DEBUGGABLE friend uint32 GetTypeHash(const FDMXOutputPortReference& PortReference)`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/IO/DMXPort.h` (Public)


#### class `FDMXPort`  
`class FDMXPort : public TSharedFromThis<FDMXPort, ESPMode::ThreadSafe>`  
_L22-140_
- inherits: `TSharedFromThis<FDMXPort,ESPMode::ThreadSafe>`
- desc: Base class for a higher level abstraction of a DMX input or output. Higher level abstraction of a DMX input hiding networking specific and protocol specific complexity.
- L30 _protected function_ `FDMXPort()` — Protected default constructor, child classes need to take care of member initialization
- L37 _public prototype_ `virtual bool IsRegistered() const = 0;` — Returns true if the port is successfully registered with its protocol
- L40 _public prototype_ `virtual const FGuid& GetPortGuid() const = 0;` — Returns the Guid of the Port
- L48 _protected prototype_ `virtual void AddRawListener(TSharedRef<FDMXRawListener> InRawListener) = 0;` — Adds a Raw Listener that receives all raw signals received on this port. Only useful for objects that want to process all data, and not just data on tick (e.g. DMX Take Recorder). Should not be used directly, instead see DMXRawListener constructor.
- L51 _protected prototype_ `virtual void RemoveRawListener(TSharedRef<FDMXRawListener> InRawListener) = 0;` — Removes the Raw Listener from the port. Should not be used directly, instead see DMXRawListener.
- L54 _protected prototype_ `virtual bool Register() = 0;` — Registers the port with its protocol. Returns true if successfully registered
- L57 _protected prototype_ `virtual void Unregister() = 0;` — Unregisteres the port if it was registered with its protocol
- L63 _public function_ `virtual ~FDMXPort()`
- L67 _public prototype_ `bool IsLocalUniverseInPortRange(int32 Universe) const;` — Returns true if the Intern Universe is in this Port's Universe range
- L70 _public prototype_ `bool IsExternUniverseInPortRange(int32 Universe) const;` — Returns true if the Extern Universe is in this Port's Universe range
- L73 _public prototype_ `int32 GetExternUniverseOffset() const;` — Returns the offset of the extern universe. LocalUniverse == ExternUniverse - ExternUniverseOffset
- L76 _public prototype_ `int32 ConvertExternToLocalUniverseID(int32 ExternUniverseID) const;` — Converts an extern Universe ID to a local Universe ID
- L79 _public prototype_ `int32 ConvertLocalToExternUniverseID(int32 LocalUniverseID) const;` — Converts a local Universe ID to an extern Universe ID
- L81 _public function_ `const FString& GetPortName() const`
- L83 _public function_ `const IDMXProtocolPtr& GetProtocol() const`
- L85 _public function_ `bool IsAutoCompleteDeviceAddressEnabled() const`
- L87 _public function_ `const FString& GetAutoCompleteDeviceAddress() const`
- L89 _public function_ `const FString& GetDeviceAddress() const`
- L91 _public function_ `EDMXCommunicationType GetCommunicationType() const`
- L93 _public function_ `int32 GetLocalUniverseStart() const`
- L95 _public function_ `int32 GetLocalUniverseEnd() const`
- L97 _public function_ `int32 GetExternUniverseStart() const`
- L99 _public function_ `int32 GetExternUniverseEnd() const`
- L102 _public member_ `FSimpleMulticastDelegate OnPortUpdated;` — Broadcast when the port is updated
- L106 _protected prototype_ `bool IsValidPortSlow() const;` — Tests whether the port is valid
- L112 _protected member_ `FString PortName;` — The name displayed wherever the port can be displayed
- L115 _protected member_ `IDMXProtocolPtr Protocol;` — The protocol of this port
- L118 _protected member_ `EDMXCommunicationType CommunicationType;` — The communication type of this port
- L121 _protected member_ `bool bAutoCompleteDeviceAddressEnabled = false;` — If true, instead of using the Device Address, the port will auto-complete the IP from the available Network Interface Card Addresses
- L124 _protected member_ `FString AutoCompleteDeviceAddress;` — The auto-complete Device Address, supports wildcards
- L127 _protected member_ `FString DeviceAddress;` — The address of the device that handles communication, e.g. the network interface for art-net
- L130 _protected member_ `int32 LocalUniverseStart;` — The Local Start Universe
- L133 _protected member_ `int32 NumUniverses;` — Number of Universes
- L139 _protected member_ `int32 ExternUniverseStart;` — The start address this being transposed to. E.g. if LocalUniverseStart is 1 and this is 100, Local Universe 1 is sent as Universe 100.

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/IO/DMXPortManager.h` (Public)


#### class `FDMXPortManager`  
`class FDMXPortManager`  
_L64-175_
- desc: Manager for all DMX ports. Exposes available input and output ports anywhere. A) Overview of the IO System 1. Definition of Ports in Project Settings: DMX Protocol Settings (the DMX Project Settings) holds two arrays of DMX Input Port Configs resp. DMX Output Port Configs. This is where ports are defined. Port Manager automatically creates DMXInputPortS and DMXOutputPortS that match these settings. Generally this is self-contained and does not need any user code. Note: Applications that want to offer dynamic ports should specify a fixed number of ports in project settings, e.g. 8, 16 ports and work with these at runtime. (While it is possible to mutate the protocol settings at runtime and create ports from that via FDMXPortManager.Get()::UpdateFromProtocolSettings(), ports created alike are not available in blueprints as port references, hence this approach is disfavored in most situations.) 2. Acquire a DMXInputPort or DMXOutputPort: Get all input ports or all output ports available via the Port Manager's GetInputPorts and GetOutputPorts methods. Alternatively use the Editor-Only SDMXPortSelector widget to select a port from available ports. 3. Receive DMX in an object: a) Latest (frame time relevant) data on the Game-Thread: - Call the port's GameThreadGetDMXSignal method to get a DMX Signal of a local universe. b) All data on any thread: - Create an instance of DMXRawListener. Use its constructor to specify which port it should use. - Use DequeueSignal to receive DMX. Note
- L68 _public member_ `FDMXOnPortsChangedDelegate OnPortsChanged;` — Broadcast when port arrays or data changed
- L70 _public prototype_ `static FDMXPortManager& Get();`
- L73 _public function_ `const TArray<FDMXInputPortSharedRef>& GetInputPorts() const` — Returns the current input ports
- L76 _public function_ `const TArray<FDMXOutputPortSharedRef>& GetOutputPorts() const` — Returns the current output ports
- L79 _public prototype_ `void ClearBuffers();` — Clears all buffered data of Input Ports, Output Ports and Raw Listeners. Note, this clears the data, it does not zero it out.
- L82 _public function_ `FSimpleMulticastDelegate& GetOnBuffersCleared()` — Returns a delegate broadcast when port buffers were cleared
- L85 _public prototype_ `FDMXInputPortSharedRef GetInputPortFromConfigChecked(const FDMXInputPortConfig& InputPortConfig);` — Gets the input port that corresponds to the input port config. Checks the config is in the DMXProtocolSetting's InputPortConfigs array.
- L88 _public prototype_ `FDMXOutputPortSharedRef GetOutputPortFromConfigChecked(const FDMXOutputPortConfig& OutputPortConfig);` — Gets the output port that corresponds to the input port config. Checks the config is in the DMXProtocolSetting's OutputPortConfigs array.
- L91 _public prototype_ `FDMXPortSharedPtr FindPortByGuid(const FGuid& PortGuid) const;` — Returns the port matching the port guid. Returns nullptr if the port doesn't exist.
- L94 _public prototype_ `FDMXPortSharedRef FindPortByGuidChecked(const FGuid& PortGuid) const;` — Returns the port matching the port guid, checked version.
- L97 _public prototype_ `FDMXInputPortSharedPtr FindInputPortByGuid(const FGuid& PortGuid) const;` — Returns the input port matching the port guid. Returns nullptr if the port doesn't exist.
- L100 _public prototype_ `FDMXInputPortSharedRef FindInputPortByGuidChecked(const FGuid& PortGuid) const;` — Returns the input port matching the port guid, checkedversion.
- L103 _public prototype_ `FDMXOutputPortSharedPtr FindOutputPortByGuid(const FGuid& PortGuid) const;` — Returns the output port matching the port guid. Returns nullptr if the port doesn't exist.
- L106 _public prototype_ `FDMXOutputPortSharedRef FindOutputPortByGuidChecked(const FGuid& PortGuid) const;` — Returns the output port matching the port guid, checked version.
- L112 _public prototype_ `void UpdateFromProtocolSettings(bool bForceUpdateRegistrationWithProtocol = false);` — Updates ports from protocol settings. Useful when project settings were modified in some way. If optional bForceUpdateRegistrationWithProtocol is set to true, ports will reregister with the protocol.
- L120 _public prototype_ `void SuspendProtocols();` — Thread-safe: Suspends the protocols irrevocably, and with it all sending and receiving of DMX via the protocols. Useful when UE4 self wants to inject data into ports, rather than communicating with the outside world, e.g. for nDisplay replication. Note: When protocols are suspended, changes to project settings are no longer reflected and UpdateFromProtocolSettings has no effect.
- L123 _public function_ `bool AreProtocolsSuspended()` — Returns true if protocols are suspended
- L127 _private prototype_ `FDMXInputPortSharedRef GetOrCreateInputPortFromConfig(FDMXInputPortConfig& InputPortConfig);` — Gets the input port that corresponds to the input port config or creates a new one. Note, the config needs be in the DMXProtocolSetting input ports array.
- L130 _private prototype_ `void RemoveInputPortChecked(const FGuid& PortGuid);` — Removes the input port. Checks that it exists.
- L133 _private prototype_ `FDMXOutputPortSharedRef GetOrCreateOutputPortFromConfig(FDMXOutputPortConfig& OutputPortConfig);` — Gets the output port that corresponds to the input port config or creates a new one. Note, the config needs be in the DMXProtocolSetting input ports array.
- L136 _private prototype_ `void RemoveOutputPortChecked(const FGuid& PortGuid);` — Removes the output port. Checks that it exists.
- L139 _private member_ `TArray<FDMXInputPortSharedRef> InputPorts;` — Array of input ports
- L142 _private member_ `TArray<FDMXOutputPortSharedRef> OutputPorts;` — Array of output ports
- L145 _private member_ `TArray<FGuid> PortGuidsFromProtocolSettings;` — Array of Port Guids added from protocol settings
- L148 _private member_ `bool bIOsAvailable = false;` — True once Input and Output Ports are available
- L151 _private member_ `bool bProtocolsSuspended = false;` — True when protocols are suspended
- L154 _private member_ `FSimpleMulticastDelegate OnBuffersClearedDelegate;` — Delegate raised when buffers were cleared
- L159 _public prototype_ `FDMXPortManager() = default;`
- L160 _public prototype_ `virtual ~FDMXPortManager();`
- L163 _public prototype_ `FDMXPortManager(FDMXPortManager const&) = delete;` — Non-copyable
- L164 _public prototype_ `void operator=(FDMXPortManager const& x) = delete;`
- L167 _private member_ `static TUniquePtr<FDMXPortManager> CurrentManager;`
- L171 _public prototype_ `static void StartupManager();` — Initializes the manager
- L174 _public prototype_ `static void ShutdownManager();` — Destroys the manager.

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE(FDMXOnPortsChangedDelegate);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE(FDMXOnPortsChangedDelegate);`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/IO/DMXRawListener.h` (Public)


#### class `FDMXRawListener`  
`class FDMXRawListener : public TSharedFromThis<FDMXRawListener>`  
_L27-90_
- inherits: `TSharedFromThis<FDMXRawListener>`
- desc: Listen to all DMX data of a port. Thread-safe single producer single consumer: Single producer always is the DMX port. This is handled by the port internally. Do not use EnqueueSignal somewhere else to retain thread-safety. Single consumer is the user thread. Needs frequent dequeuing. Stop needs to be called before the Input is released.
- L31 _public prototype_ `FDMXRawListener() = delete;`
- L34 _public prototype_ `FDMXRawListener(TSharedRef<FDMXPort, ESPMode::ThreadSafe> InOwnerPort);` — Constructor
- L37 _public prototype_ `virtual ~FDMXRawListener();` — Destructor
- L40 _public prototype_ `void Start();` — Starts receiving the Input
- L43 _public prototype_ `void Stop();` — Stops receiving the Input
- L51 _public prototype_ `virtual void EnqueueSignal(void* Producer, const FDMXSignalSharedRef& Signal);` — Thread safe single producer. Enqueues a signal. Should not be called besides from the owner port. @Param Producer				The producer object, tested in debug builds to be the owner port. @Param Signal				The signal to enqueue
- L62 _public prototype_ `bool DequeueSignal(void* Consumer, FDMXSignalSharedPtr& OutSignal, int32& OutLocalUniverseID);` — Thread safe single consumer. Tries to dequeues a signal from the raw listener. @param Consumer				The consumer object, tested to be the same single consumer in debug builds. @param OutSignal				The dequeued signal. If the function returns true, the outsignal is a valid shared pointer. @param OutLocalUniverseID	The local universe of the signal. @return						True if a signal was dequeued.
- L65 _public prototype_ `void ClearBuffer();` — Thread-safe. Clears the raw buffer
- L69 _private prototype_ `void OnPortUpdated();` — Called when the port changed
- L72 _private member_ `TQueue<FDMXSignalSharedPtr, EQueueMode::Spsc> RawBuffer;` — The actual buffer
- L75 _private member_ `TWeakPtr<FDMXPort, ESPMode::ThreadSafe> OwnerPort;` — The port that owns this Listener
- L78 _private member_ `TAtomic<int32> ExternUniverseOffset;` — The extern universe offset of the port
- L81 _private member_ `bool bStopped;` — True when stopped
- L85 _private member_ `void* ProducerObj;` — The producer object, should always be the owner port
- L88 _private member_ `void* ConsumerObj;` — The consumer of the queue, should never change once set

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/Interfaces/IDMXProtocol.h` (Public)


#### class `IDMXProtocol`  
`class IDMXProtocol : public IDMXProtocolBase`  
_L55-212_
- inherits: `IDMXProtocolBase`
- desc: Serves as a higher level abstraction of a specific protocol such as Art-Net or sACN with the purpose to hide its complexity. By that the commonly expected responsability of the implementation is to: - Provide a way to send and receive protocol specific DMX from and to the system. - Push received DXM as generic DMXSignals to the registered DMXInputPorts. - Pull generic DMXSignals from the registered DMXOutputPorts and send it as Protocol specific DMX. For an overview for DMX and protocol developers, see DMXPortManager (in IO folder) For an exemplary implementation, see DMXProtocolArtNet (in ProtocolArtNetModule) DMX Protocol Life-Cycle Startup: 1. All DMX Modules should be set to load in the Predefault loading phase and bind to FDMXProtocolModule::GetOnRequestProtocolRegistration(). 2. At the end of the Pre-Default loading phase DMXProtocol Broadcasts GetOnRequestProtocolRegistration. Protocol should now provide their Name and DMXProtocolFactory. All protocols registered can be selected in Project Settings -> Plugins -> DMX -> Communication settings 3. When a Input Port of a specific Protocol is created in Project Settings: a) The input Port calls IDMXProtocol::RegisterInputPort. If the Protocol cannot handle the Input Port, e.g. because the network interface is not reachable, the protocol needs to return false. b) The Protocol should pass received DMX by calling DMXInputPort::SingleProducerInputDMXSignal to the Input Ports. Note: The Input Ports do the required filtering for 
- L67 _public prototype_ `virtual bool IsEnabled() const = 0;` — Whether protocol enabled @return Return true if the protocol is enabled
- L73 _public prototype_ `virtual const FName& GetProtocolName() const = 0;` — Get the Protocol Name @return Return FName of the protocol
- L79 _public prototype_ `virtual int32 GetMinUniverseID() const = 0;` — Get minimum supported universe ID for protocol @return		Minimum supported universe ID for protocol
- L85 _public prototype_ `virtual int32 GetMaxUniverseID() const = 0;` — Get maximum supported universe ID for protocol @return		Maximum supported universe ID for protocol
- L88 _public prototype_ `virtual bool IsValidUniverseID(int32 UniverseID) const = 0;` — Returns true if the Universe ID is valid for the protocol
- L91 _public prototype_ `virtual int32 MakeValidUniverseID(int32 DesiredUniverseID) const = 0;` — Returns a valid Universe ID as close as possible to the provided Universe ID
- L100 _public prototype_ `virtual const TArray<EDMXCommunicationType> GetInputPortCommunicationTypes() const = 0;` — Returns the communication types the protocol supports for its input ports. Can be empty if the protocol doesn't want to expose a selection to the user. If an empty array is returned, input ports that use the protocol will set CommunicationType to EDMXCommunicationType::InternalOnly. @return	Array of communication types the user can select from, when defining input ports in editor.
- L109 _public prototype_ `virtual const TArray<EDMXCommunicationType> GetOutputPortCommunicationTypes() const = 0;` — Returns the communication types the protocol supports for its input ports. Can be empty if the protocol doesn't want to expose a selection to the user. If an empty array is returned, output ports that use the protocol will set CommunicationType to EDMXCommunicationType::InternalOnly. @return						Array of communication types the user can select from, when defining output ports in editor.
- L117 _public prototype_ `virtual bool SupportsPrioritySettings() const = 0;` — Returns true if the Protocol supports a priority setting to filter inbound and outbound signals @return						Whether the protocol supports Priority settings.
- L126 _public prototype_ `virtual bool RegisterInputPort(const FDMXInputPortSharedRef& InputPort) = 0;` — Called to register a DMXInputPort with the protocol. This should be implemented so each port can only register once (see Art-Net for an example). @param	InputPort			The input port that needs to be registered @return						True if the port was successfully registered
- L133 _public prototype_ `virtual void UnregisterInputPort(const FDMXInputPortSharedRef& InputPort) = 0;` — Called to unregister a DMXInputPort with the protocol. @param	InputPort			The input port that needs to be unregistered
- L143 _public prototype_ `virtual TArray<TSharedPtr<IDMXSender>> RegisterOutputPort(const FDMXOutputPortSharedRef& OutputPort) = 0;` — Called to register a DMXOutputPort with the protocol. If initially valid, returned sender needs to guarantee to be valid while the port is registered. This should be implemented so each port can only register once (see Art-Net for an example). @param	OutputPort			The Output port that needs to be registered @return						The DMX senders that can be used while the output port is registered.
- L150 _public prototype_ `virtual void UnregisterOutputPort(const FDMXOutputPortSharedRef& OutputPort) = 0;` — Called to unregister a DMXOutputPort with the protocol. @param	OutputPort			The Output port that needs to be unregistered
- L161 _public prototype_ `virtual bool IsCausingLoopback(EDMXCommunicationType InCommunicationType) = 0;` — Called to deduce if the communication type will be heard by corresponding input ports. As an example, this should be true, when the output port broadcasts to network. Broadcast traffic is heard by any input port that receives this protocol on corresponding universes. We forward this info to users, so they can take appropriate messures when specifying their ports. @param	InCommunicationType		The communication type that may cause intrinsic loopback
- L167 _public function_ `static const TMap<FName, IDMXProtocolFactory*>& GetProtocolFactories()`
- L174 _public function_ `static const TMap<FName, IDMXProtocolPtr>& GetProtocols()`
- L181 _public function_ `static const TArray<FName>& GetProtocolNames()`
- L189 _public function_ `static FName GetFirstProtocolName()`
- L206 _public function_ `static IDMXProtocolPtr Get(const FName& ProtocolName = NAME_None)` — If protocol exists return the pointer otherwise it create a new protocol first and then return the pointer. @param  InProtocolName Name of the requested protocol @return Return the pointer to protocol

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/Interfaces/IDMXProtocolBase.h` (Public)


#### class `IDMXProtocolBase`  
`class IDMXProtocolBase : public TSharedFromThis<IDMXProtocolBase, ESPMode::ThreadSafe>`  
_L7-18_
- inherits: `TSharedFromThis<IDMXProtocolBase,ESPMode::ThreadSafe>`
- L11 _public function_ `virtual ~IDMXProtocolBase()`
- L13 _public prototype_ `virtual bool Init() = 0;`
- L15 _public prototype_ `virtual bool Shutdown() = 0;`
- L17 _public prototype_ `virtual bool Tick(float DeltaTime) = 0;`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/Interfaces/IDMXProtocolFactory.h` (Public)


#### class `IDMXProtocolFactory`  
`class IDMXProtocolFactory`  
_L7-17_
- L10 _public function_ `virtual ~IDMXProtocolFactory()`
- L16 _public prototype_ `virtual IDMXProtocolPtr CreateProtocol(const FName& ProtocolName) = 0;` — It creates only one instance of Protocol. There is the condition to check in DMXProtocolModule @return Return the pointer to protocol

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/Interfaces/IDMXProtocolPacket.h` (Public)


#### struct `IDMXProtocolPacket`  
`struct IDMXProtocolPacket`  
_L8-14_
- L11 _public function_ `virtual ~IDMXProtocolPacket()`
- L13 _public function_ `virtual TSharedPtr<FBufferArchive> Pack(const uint16 PropertiesNum)`

### `Plugins/VirtualProduction/DMX/DMXProtocol/Source/DMXProtocol/Public/Interfaces/IDMXSender.h` (Public)


#### class `IDMXSender`  
`class IDMXSender : public TSharedFromThis<IDMXSender>`  
_L12-25_
- inherits: `TSharedFromThis<IDMXSender>`
- L16 _public function_ `virtual ~IDMXSender()`
- L20 _public prototype_ `virtual void SendDMXSignal(const FDMXSignalSharedRef& DMXSignal) = 0;` — Sends the DMX signal. Note, this may called concurrently from various threads
- L24 _public function_ `virtual void ClearBuffer()` — `UE_DEPRECATED(5.0, "Deprecated without replacement. Classes that implement IDMXSender do no longer need to implement this method.")` — DEPRECATED 5.0
