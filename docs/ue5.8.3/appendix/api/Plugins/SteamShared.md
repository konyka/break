# Plugins / SteamShared

- module root: `Plugins/Runtime/Steam/SteamShared/Source/SteamShared`
- headers: 5; symbols: 88
- symbol kinds: class=6, externvar=2, function=32, macro=9, member=11, namespace=1, prototype=27
- PrivateDependencyModuleNames: Core, Sockets

### `Plugins/Runtime/Steam/SteamShared/Source/SteamShared/Public/IPAddressSteam.h` (Public)


#### class `FInternetAddrSteam`  
`class FInternetAddrSteam : public FInternetAddr`  
_L21-217_
- inherits: `FInternetAddr`
- L24 _private member_ `SteamNetworkingIdentity Addr;`
- L25 _private member_ `int32 P2PVirtualPort;`
- L26 _private member_ `FName ProtocolType;`
- L29 _public function_ `FInternetAddrSteam(const FName RequestedProtocol = NAME_None) : P2PVirtualPort(0), ProtocolType(RequestedProtocol)`
- L36 _public function_ `FInternetAddrSteam(const SteamNetworkingIdentity& NewAddress) : Addr(NewAddress), P2PVirtualPort(0), ProtocolType(NewAddress.GetIPAddr() == nullptr ? FNetworkProtocolTypes::SteamSocketsP2P : FNetworkProtocolTypes::SteamSocketsIP)`
- L43 _public function_ `FInternetAddrSteam(const SteamNetworkingIPAddr& IPAddr) : P2PVirtualPort(0), ProtocolType(FNetworkProtocolTypes::SteamSocketsIP)`
- L50 _public function_ `explicit FInternetAddrSteam(uint64& SteamID) : P2PVirtualPort(0), ProtocolType(FNetworkProtocolTypes::SteamSocketsP2P)`
- L57 _public function_ `explicit FInternetAddrSteam(const CSteamID& SteamID) : P2PVirtualPort(0), ProtocolType(FNetworkProtocolTypes::SteamSocketsP2P)`
- L64 _public prototype_ `virtual TArray<uint8> GetRawIp() const override;`
- L66 _public prototype_ `virtual void SetRawIp(const TArray<uint8>& RawAddr) override;`
- L68 _public function_ `virtual void SetIp(uint32 InAddr) override`
- L77 _public function_ `CSteamID GetSteamID() const` — Attempts to return the CSteamID of the target. Will return an invalid CSteamID if using IP address
- L81 _public function_ `uint64 GetSteamID64() const`
- L89 _public function_ `void SetSteamID(CSteamID NewSteamID)` — Shortcut for SetIp because SetIp is expecting the array format from GetIp which has some additional information
- L101 _public prototype_ `virtual void SetIp(const TCHAR* InAddr, bool& bIsValid) override;` — Sets the ip address from a string ("A.B.C.D") or a steam id "steam.STEAMID" or "STEAMID:PORT" @param InAddr the string containing the new ip address to use
- L108 _public function_ `virtual void GetIp(uint32& OutAddr) const override` — Copies the network byte order ip address to a host byte order dword @param OutAddr the out param receiving the ip address
- L118 _public prototype_ `virtual void SetPort(int32 InPort) override;` — Sets the port number from a host byte order int @param InPort the new port to use (must convert to network byte order)
- L123 _public prototype_ `virtual int32 GetPort() const override;` — Returns the port number from this address in host byte order
- L128 _public function_ `virtual void SetPlatformPort(int32 InPort) override` — Set Platform specific port data
- L136 _public function_ `virtual int32 GetPlatformPort() const override` — Get platform specific port data.
- L142 _public prototype_ `virtual void SetAnyAddress() override;` — Sets the address to be any address
- L145 _public function_ `virtual void SetBroadcastAddress() override` — Sets the address to broadcast
- L151 _public function_ `virtual void SetLoopbackAddress() override` — Sets the address to loopback
- L161 _public prototype_ `virtual FString ToString(bool bAppendPort) const override;` — Converts this internet ip address to string form @param bAppendPort whether to append the port information or not
- L168 _public function_ `virtual inline bool operator==(const FInternetAddr& Other) const override` — Compares two internet ip addresses for equality @param Other the address to compare against
- L179 _public function_ `inline bool operator==(const FInternetAddrSteam& Other) const` — Compares two internet ip addresses for equality @param Other the address to compare against
- L184 _public prototype_ `virtual uint32 GetTypeHash() const override;`
- L186 _public prototype_ `virtual FName GetProtocolType() const override;`
- L188 _public function_ `virtual bool IsValid() const override`
- L193 _public function_ `operator const SteamNetworkingIPAddr() const`
- L205 _public function_ `operator const SteamNetworkingIdentity() const`
- L210 _public function_ `virtual TSharedRef<FInternetAddr> Clone() const override`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API STEAMSHARED_API`
- L19 _macro_ `#define STEAM_URL_PREFIX TEXT("steam.")`

### `Plugins/Runtime/Steam/SteamShared/Source/SteamShared/Public/ISteamSharedModule.h` (Public)


#### class `ISteamSharedModule`  
`class ISteamSharedModule : public IModuleInterface`  
_L8-13_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual TSharedPtr<class FSteamClientInstanceHandler> ObtainSteamClientInstanceHandle() = 0;` — Retrieve steam client handle if steam is enabled, otherwise return a nullptr

### `Plugins/Runtime/Steam/SteamShared/Source/SteamShared/Public/SteamOnlineDefines.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace FNetworkProtocolTypes`
- L7 _externvar_ `extern const FLazyName SteamSocketsP2P;` (scope `FNetworkProtocolTypes`)
- L8 _externvar_ `extern const FLazyName SteamSocketsIP;` (scope `FNetworkProtocolTypes`)

### `Plugins/Runtime/Steam/SteamShared/Source/SteamShared/Public/SteamSharedModule.h` (Public)


#### class `FSteamSharedModule`  
`class FSteamSharedModule : public ISteamSharedModule`  
_L19-130_
- inherits: `ISteamSharedModule`
- L23 _public function_ `FSteamSharedModule() : SteamDLLHandle(nullptr), SteamServerDLLHandle(nullptr), bForceLoadSteamClientDll(false), SteamClientObserver(nullptr), SteamServerObserver(nullptr)`
- L32 _public prototype_ `virtual ~FSteamSharedModule() = default;`
- L35 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L36 _public prototype_ `virtual void ShutdownModule() override;`
- L39 _public function_ `virtual bool SupportsDynamicReloading() override` — Due to the loading of the DLLs and how the Steamworks API is initialized, we cannot support dynamic reloading.
- L50 _public prototype_ `virtual TSharedPtr<class FSteamClientInstanceHandler> ObtainSteamClientInstanceHandle() override;` — Initializes Steam Client API and provides a handler that will keep the API valid for the lifetime of the the object. Several Handlers can be active at once. @return A handler to the Steam Client API, use IsValid to check if the handle is initialized.
- L58 _public prototype_ `TSharedPtr<class FSteamServerInstanceHandler> ObtainSteamServerInstanceHandle();` — Initializes Steam Server API and provides a handler that will keep the API valid for the lifetime of the the object. Several Handlers can be active at once. @return A handler to the Steam Server API, use IsValid to check if the handle is initialized.
- L65 _public prototype_ `bool AreSteamDllsLoaded() const;` — Are the Steamworks Dlls loaded @return if the steam dlls are currently loaded (if we are loading them dynamically, statically linked are always true)
- L72 _public prototype_ `FString GetSteamModulePath() const;` — The path to where the Steam binaries are stored, for use in debugging. @return The directory path of the location of the steam dlls
- L80 _public function_ `bool IsLoadingServerClientDlls() const` — If the module will be loading the client dlls for the dedicated server instance. Really only useful on Windows. @return If this application is currently loading client dlls on the server
- L87 _public prototype_ `bool CanLoadClientDllsOnServer() const;` — Checks if we can load client dlls on dedicated server instances. @return On dedicated servers on windows, this returns true, for other platforms this returns false (as feature is unnecessary)
- L95 _public function_ `static inline class FSteamSharedModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L105 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L113 _private member_ `void* SteamDLLHandle;` — Handle to the STEAM API dll
- L116 _private member_ `void* SteamServerDLLHandle;` — Handle to the STEAM dedicated server support dlls
- L119 _private member_ `bool bForceLoadSteamClientDll;` — If we force loaded the steamclient dlls due to launch flags
- L122 _private member_ `TWeakPtr<class FSteamClientInstanceHandler> SteamClientObserver;` — Object that holds the refcounted pointer that's given out
- L123 _private member_ `TWeakPtr<class FSteamServerInstanceHandler> SteamServerObserver;`
- L126 _private prototype_ `void LoadSteamModules();` — Load the required modules for Steam
- L129 _private prototype_ `void UnloadSteamModules();` — Unload the required modules for Steam

#### class `FSteamInstanceHandlerBase`  
`class FSteamInstanceHandlerBase`  
_L133-149_
- desc: Base instance handler class for the Steam shared classes, this allows for less code redundancy between the shared modules.
- L136 _public prototype_ `virtual ~FSteamInstanceHandlerBase() = default;`
- L137 _public function_ `virtual bool IsInitialized() const`
- L138 _public function_ `int32 GetGamePort() const`
- L141 _protected prototype_ `FSteamInstanceHandlerBase();`
- L143 _protected member_ `bool bInitialized;`
- L144 _protected member_ `int32 GamePort;`
- L146 _protected prototype_ `virtual bool CanCleanUp() const;`
- L147 _protected prototype_ `virtual void Destroy();`
- L148 _protected prototype_ `virtual void InternalShutdown() = 0;`

#### class `FSteamClientInstanceHandler`  
`class FSteamClientInstanceHandler final : public FSteamInstanceHandlerBase`  
_L152-169_
- inherits: `FSteamInstanceHandlerBase`
- desc: A simple instance handler that creates and uninitializes the client SteamAPI automatically.
- L155 _public function_ `virtual ~FSteamClientInstanceHandler()`
- L162 _protected prototype_ `virtual void InternalShutdown() override;`
- L165 _private function_ `FSteamClientInstanceHandler() : FSteamInstanceHandlerBase()`

#### class `FSteamServerInstanceHandler`  
`class FSteamServerInstanceHandler final : public FSteamInstanceHandlerBase`  
_L172-193_
- inherits: `FSteamInstanceHandlerBase`
- desc: A simple instance handler that creates and uninitializes the server SteamAPI automatically.
- L175 _public function_ `virtual ~FSteamServerInstanceHandler()`
- L177 _public function_ `int32 GetQueryPort() const`
- L184 _protected member_ `int32 QueryPort;`
- L185 _protected prototype_ `virtual void InternalShutdown() override;`
- L188 _private function_ `FSteamServerInstanceHandler() : FSteamInstanceHandlerBase(), QueryPort(-1)`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API STEAMSHARED_API`
- L13 _macro_ `#define LOADING_STEAM_CLIENT_LIBRARY_DYNAMICALLY (PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_ANDROID || (PLATFORM_LINUX && !IS_MONOLITHIC))`
- L14 _macro_ `#define LOADING_STEAM_SERVER_LIBRARY_DYNAMICALLY (PLATFORM_WINDOWS || (PLATFORM_LINUX && !IS_MONOLITHIC) || PLATFORM_MAC)`
- L15 _macro_ `#define LOADING_STEAM_LIBRARIES_DYNAMICALLY (LOADING_STEAM_CLIENT_LIBRARY_DYNAMICALLY || LOADING_STEAM_SERVER_LIBRARY_DYNAMICALLY)`
- L17 _macro_ `#define STEAM_UNSUPPORTED_ANDROID_PLATFORMS (PLATFORM_ANDROID_X64 || PLATFORM_ANDROID_X86)`

### `Plugins/Runtime/Steam/SteamShared/Source/SteamShared/Public/SteamSharedPackage.h` (Public)


#### Free symbols / members of external scopes

- L12 _macro_ `#define PACKAGE_SCOPE public`
- L14 _macro_ `#define PACKAGE_SCOPE protected`
