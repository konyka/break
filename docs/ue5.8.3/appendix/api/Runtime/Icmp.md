# Runtime / Icmp

- module root: `Source/Runtime/Online/ICMP`
- headers: 3; symbols: 66
- symbol kinds: class=3, delegate=2, enum=2, enumerator=10, function=13, macro=7, member=10, prototype=13, struct=4, typedef=2
- PrivateDependencyModuleNames: Core, CoreUObject, Sockets

### `Source/Runtime/Online/ICMP/Private/IcmpPrivate.h` (Private)


#### Free symbols / members of external scopes

- L13 _macro_ `#define PLATFORM_SUPPORTS_ICMP 1`
- L14 _macro_ `#define PLATFORM_USES_POSIX_ICMP 0`
- L15 _macro_ `#define PING_ALLOWS_CUSTOM_THREAD_SIZE 1`
- L20 _macro_ `#define PLATFORM_USES_POSIX_ICMP 1`
- L21 _macro_ `#define PING_ALLOWS_CUSTOM_THREAD_SIZE 0`
- L43 _macro_ `#define PLATFORM_SUPPORTS_ICMP 0`
- L60 _prototype_ `int CalculateChecksum(uint8* Address, int Length);` — Calculate the 16-bit one's complement of the one's complement sum of the ICMP message starting at the beginning of the IcmpHeader @param Address byte array to calculate the checksum from @param Length length of the input byte array
- L70 _prototype_ `bool ResolveIp(ISocketSubsystem* SocketSub, const FString& HostName, FString& OutIp);` — Convert a string based hostname (ipv4) to a valid ip address @param HostName the name of the host to look up @param OutIp [out] the string to copy the IP address to @return true if conversion was successful, false otherwise

### `Source/Runtime/Online/ICMP/Public/Icmp.h` (Public)


#### enum `EIcmpResponseStatus`  
`enum class EIcmpResponseStatus`  
_L11-25_
- L14 _public enumerator_ `Success` — We did receive a valid Echo reply back from the target host
- L16 _public enumerator_ `Timeout` — We did not receive any results within the time limit
- L18 _public enumerator_ `Unreachable` — We got an unreachable error from another node on the way
- L20 _public enumerator_ `Unresolvable` — We could not resolve the target address to a valid IP address
- L22 _public enumerator_ `InternalError` — Some internal error happened during setting up or sending the ping packet
- L24 _public enumerator_ `NotImplemented` — not implemented - used to indicate we haven't implemented ICMP ping on this platform

#### struct `FIcmpEchoResult`  
`struct FIcmpEchoResult`  
_L41-58_
- L44 _public member_ `EIcmpResponseStatus Status;` — Status of the final response
- L46 _public member_ `FString ResolvedAddress;` — Addressed resolved by GetHostName
- L48 _public member_ `FString ReplyFrom;` — Reply received from this address
- L50 _public member_ `float Time;` — Total round trip time
- L52 _public function_ `FIcmpEchoResult() : Status(EIcmpResponseStatus::InternalError) , ResolvedAddress() , ReplyFrom() , Time(-1)`

#### struct `FIcmpTarget`  
`struct FIcmpTarget`  
_L63-76_
- L65 _public member_ `FString Address;`
- L66 _public member_ `int32 Port;`
- L68 _public function_ `FIcmpTarget() : Port(0)`
- L72 _public function_ `FIcmpTarget(const FString& InAddress, int32 InPort) : Address(InAddress) , Port(InPort)`

#### struct `FIcmpEchoManyResult`  
`struct FIcmpEchoManyResult`  
_L78-89_
- L80 _public member_ `FIcmpEchoResult EchoResult;`
- L81 _public member_ `FIcmpTarget Target;`
- L83 _public prototype_ `FIcmpEchoManyResult() = default;`
- L84 _public function_ `FIcmpEchoManyResult(const FIcmpEchoResult& InEchoResult, const FIcmpTarget& InTarget) : EchoResult(InEchoResult) , Target(InTarget)`

#### enum `EIcmpEchoManyStatus`  
`enum class EIcmpEchoManyStatus : uint8`  
_L91-97_
- L93 _public enumerator_ `Invalid`
- L94 _public enumerator_ `Success`
- L95 _public enumerator_ `Failure`
- L96 _public enumerator_ `Canceled`

#### struct `FIcmpEchoManyCompleteResult`  
`struct FIcmpEchoManyCompleteResult`  
_L99-108_
- L101 _public member_ `TArray<FIcmpEchoManyResult> AllResults;`
- L102 _public member_ `EIcmpEchoManyStatus Status;`
- L104 _public function_ `FIcmpEchoManyCompleteResult() : Status(EIcmpEchoManyStatus::Invalid)`

#### class `FIcmp`  
`class FIcmp`  
_L115-150_
- desc: Simple ping interface that sends an ICMP packet to the given address and returns timing info for the reply if reachable
- L133 _public prototype_ `static void IcmpEcho(const FString& TargetAddress, float Timeout, FIcmpEchoResultCallback HandleResult);` — Send an ICMP echo packet and wait for a reply. The name resolution and ping send/receive will happen on a separate thread. The third argument is a callback function that will be invoked on the game thread after the a reply has been received from the target address, the timeout has expired, or if there was an error resolving the address or delivering the ICMP message to it. Multiple pings can be issued concurrently and this function will ensure they're executed in turn in order not to mix ping replies from different nodes. @param TargetAddress the target address to ping @param Timeout max time to wait for a reply @param HandleResult a callback function that will be called when the result is ready
- L143 _public function_ `static void IcmpEcho(const FString& TargetAddress, float Timeout, FIcmpEchoResultDelegate ResultDelegate)` — Send an ICMP echo packet and wait for a reply. This is a wrapper around the above function, taking a delegate instead of a function argument. @param TargetAddress the target address to ping @param Timeout max time to wait for a reply @param ResultDelegate a delegate that will be called when the result is ready

#### class `FUDPPing`  
`class FUDPPing`  
_L153-224_
- desc: Simple ping interface that sends an ICMP packet over UDP to the given address and returns timing info for the reply if reachable
- L171 _public prototype_ `static void UDPEcho(const FString& TargetAddress, float Timeout, FIcmpEchoResultCallback HandleResult);` — Send an ICMP echo packet and wait for a reply. The name resolution and ping send/receive will happen on a separate thread. The third argument is a callback function that will be invoked on the game thread after the a reply has been received from the target address, the timeout has expired, or if there was an error resolving the address or delivering the ICMP message to it. Multiple pings can be issued concurrently and this function will ensure they're executed in turn in order not to mix ping replies from different nodes. @param TargetAddress the target address to ping @param Timeout max time to wait for a reply @param HandleResult a callback function that will be called when the result is ready
- L181 _public function_ `static void UDPEcho(const FString& TargetAddress, float Timeout, FIcmpEchoResultDelegate ResultDelegate)` — Send an ICMP echo packet and wait for a reply. This is a wrapper around the above function, taking a delegate instead of a function argument. @param TargetAddress the target address to ping @param Timeout max time to wait for a reply @param ResultDelegate a delegate that will be called when the result is ready
- L205 _public prototype_ `static void UDPEchoMany(const TArray<FIcmpTarget>& Targets, float Timeout, FIcmpEchoManyCompleteCallback CompletionCallback);` — Send multiple ICMP echo packets and wait for replies. Creates a new thread in which name resolution and ping send/receive are handled for all supplied target addresses.  These are non-blocking requests, sent and received on a single network socket. The third argument is a callback function that will be invoked on the game thread after all replies are received, timed out, or otherwise terminated (e.g. remote address could not be resolved, host unreachable, send failed, etc.).  It passes a FIcmpEchoManyCompleteResult instance, containing the overall completion status, and the ping results obtained so far for all of the supplied targets. @param Targets the target addresses to ping @param Timeout max time to wait for a replies @param CompletionCallback callback function that is invoked when the final results are ready
- L223 _public prototype_ `static void UDPEchoMany(const TArray<FIcmpTarget>& Targets, float Timeout, FIcmpEchoManyCompleteDelegate CompletionDelegate);` — Send multiple ICMP echo packets and wait for replies. Creates a new thread in which name resolution and ping send/receive are handled for all supplied target addresses.  These are non-blocking requests, sent and received on a single network socket. The third argument is a callback function that will be invoked on the game thread after all replies are received, timed out, or otherwise terminated (e.g. remote address could not be resolved, host unreachable, send failed, etc.).  It passes a FIcmpEchoManyCompleteResult instance, containing the overall completion status, and the ping results obtained so far for all of the supplied targets. @param Targets the target addresses to ping @param Timeout max time to wait for a replies @param CompletionDelegate delegate that is invoked when the final results are ready

#### Free symbols / members of external scopes

- L27 _function_ `inline const TCHAR* LexToString(EIcmpResponseStatus ResponseStatus)`
- L60 _typedef_ `typedef TFunction<void(FIcmpEchoResult)> FIcmpEchoResultCallback;`
- L61 _delegate_ `DECLARE_DELEGATE_OneParam(FIcmpEchoResultDelegate, FIcmpEchoResult);`
- L61 _prototype_ `DECLARE_DELEGATE_OneParam(FIcmpEchoResultDelegate, FIcmpEchoResult);`
- L110 _typedef_ `typedef TFunction<void(FIcmpEchoManyCompleteResult)> FIcmpEchoManyCompleteCallback;`
- L111 _delegate_ `DECLARE_DELEGATE_OneParam(FIcmpEchoManyCompleteDelegate, FIcmpEchoManyCompleteResult);`
- L111 _prototype_ `DECLARE_DELEGATE_OneParam(FIcmpEchoManyCompleteDelegate, FIcmpEchoManyCompleteResult);`
- L146 _function_ `` (scope `FIcmp::IcmpEcho`)
- L184 _function_ `` (scope `FUDPPing::UDPEcho`)
- L227 _macro_ `#define EnumCase(Name) case EIcmpResponseStatus::Name : return TEXT(#Name)`
- L228 _function_ `static const TCHAR* ToString(EIcmpResponseStatus Status)`

### `Source/Runtime/Online/ICMP/Public/IcmpModule.h` (Public)


#### class `FIcmpModule`  
`class FIcmpModule : public IModuleInterface, public FSelfRegisteringExec`  
_L20-74_
- inherits: `IModuleInterface,FSelfRegisteringExec`
- desc: Module for Icmp service utilities
- L31 _public function_ `static inline FIcmpModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L41 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L59 _private prototype_ `virtual bool Exec_Dev(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — Handle exec commands starting with "Icmp" @param InWorld	the world context @param Cmd		the exec command being executed @param Ar		the archive to log results to @return true if the handler consumed the input, false to continue searching handlers
- L67 _private prototype_ `virtual void StartupModule() override;` — Called when icmp module is loaded Initialize platform specific parts of template handling
- L73 _private prototype_ `virtual void ShutdownModule() override;` — Called when icmp module is unloaded Shutdown platform specific parts of template handling

#### Free symbols / members of external scopes

- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIcmp, Display, All);` — Logging related to parties
