# Plugins / OnlineBase

- module root: `Plugins/Online/OnlineBase/Source`
- headers: 4; symbols: 208
- symbol kinds: class=4, delegate=3, enum=2, enumerator=7, function=54, macro=84, member=26, namespace=2, prototype=21, typedef=3, variable=2
- PrivateDependencyModuleNames: Core, CoreUObject
- PublicDependencyModuleNames: Sockets

### `Plugins/Online/OnlineBase/Source/Public/Online/LANBeacon.h` (Public)


#### enum `ELANBeaconVersionHistory`  
`enum class ELANBeaconVersionHistory : uint8`  
_L34-42_
- desc: This value indicates which packet version the server is sending. Clients with differing versions will ignore these packets. This prevents crashing when changing the packet format and there are existing servers on the network Current format: <Ver byte><Platform byte><Game unique 4 bytes><packet type 2 bytes><nonce 8 bytes><guid 16 bytes><payload>
- L36 _public enumerator_ `HISTORY_INITIAL = 11`
- L37 _public enumerator_ `HISTORY_BEACON_GUID = 12` — Lan response packets now contain an instance guid
- L40 _public enumerator_ `HISTORY_PLUS_ONE` — -----<new versions can be added before this line>-------------------------------------------------
- L41 _public enumerator_ `HISTORY_LATEST = HISTORY_PLUS_ONE - 1`

#### enum `ELanBeaconState::Type`  
`enum Type`  
_L81-89_
- L84 _public enumerator_ `NotUsingLanBeacon` — The lan beacon is disabled
- L86 _public enumerator_ `Hosting` — The lan beacon is responding to client requests for information
- L88 _public enumerator_ `Searching` — The lan beacon is querying servers for information

#### class `FLanBeacon`  
`class FLanBeacon`  
_L118-166_
- desc: Class responsible for sending/receiving UDP broadcasts for LAN match discovery
- L121 _private member_ `TSharedPtr<class FInternetAddr> BroadcastAddr;` — Builds the broadcast address and caches it
- L123 _private member_ `class FSocket* ListenSocket;` — The socket to listen for requests on
- L125 _private member_ `TSharedPtr<class FInternetAddr> ListenAddr;` — The address in bound requests come in on
- L127 _private member_ `TSharedRef<class FInternetAddr> SockAddr;` — Temporary address when receiving packets
- L131 _public prototype_ `FLanBeacon();` — Sets the broadcast address for this object
- L134 _public prototype_ `~FLanBeacon();` — Frees the broadcast socket
- L137 _public prototype_ `bool IsListenSocketValid() const;` — Return true if there is a valid ListenSocket
- L146 _public prototype_ `bool Init(int32 Port);` — Initializes the socket @param Port the port to listen on @return true if both socket was created successfully, false otherwise
- L157 _public prototype_ `int32 ReceivePacket(uint8* PacketData, int32 BufferSize);` — Called to poll the socket for pending data. Any data received is placed in the specified packet buffer @param PacketData the buffer to get the socket's packet data @param BufferSize the size of the packet buffer @return the number of bytes read (0 if none or an error)
- L165 _public prototype_ `bool BroadcastPacket(uint8* Packet, int32 Length);` — Uses the cached broadcast address to send packet to a subnet @param Packet the packet to send @param Length the size of the packet to send

#### class `FLANSession`  
`class FLANSession`  
_L177-311_
- desc: Encapsulate functionality related to LAN broadcast data
- L188 _protected prototype_ `bool IsValidLanQueryPacket(const uint8* Packet, uint32 Length, uint64& ClientNonce);` — Determines if the packet header is valid or not @param Packet the packet data to check @param Length the size of the packet buffer @return true if the header is valid, false otherwise
- L199 _protected prototype_ `bool IsValidLanResponsePacket(const uint8* Packet, uint32 Length, FGuid& ResponseGuid);` — Determines if the packet header is valid or not @param Packet the packet data to check @param Length the size of the packet buffer @param ResponseGuid the beacon guid from the response packet @return true if the header is valid, false otherwise
- L204 _public member_ `int32 LanAnnouncePort;` — Port to listen on for LAN queries/responses
- L207 _public member_ `int32 LanGameUniqueId;` — Unique id to keep UE games from seeing each others' LAN packets
- L210 _public member_ `int32 LanPacketPlatformMask;` — Mask containing which platforms can cross communicate
- L213 _public member_ `float LanQueryTimeout;` — The amount of time to wait before timing out a LAN query request
- L216 _public member_ `float LanQueryRetryTime;` — The amount of time to wait before resending a LAN query request
- L219 _public member_ `class FLanBeacon* LanBeacon;` — LAN beacon for packet broadcast
- L222 _public member_ `ELanBeaconState::Type LanBeaconState;` — State of the LAN beacon
- L225 _public member_ `uint64 LanNonce;` — Used by a client to uniquely identify itself during LAN match discovery
- L228 _public member_ `float LanQueryTimeLeft;` — The amount of time before the LAN query is considered done
- L231 _public member_ `float LanQueryRetryTimeLeft;` — The amount of time before the LAN query retry
- L234 _public member_ `TArray<uint8> RetryData;` — Cached search packet data for retries
- L237 _public member_ `FGuid LanBeaconGuid;` — Unique identifier for this hosting/searching LAN session
- L239 _public function_ `FLANSession() : LanAnnouncePort(LAN_ANNOUNCE_PORT), LanGameUniqueId(LAN_UNIQUE_ID), LanPacketPlatformMask(LAN_PLATFORMMASK), LanQueryTimeout(LAN_QUERY_TIMEOUT), LanQueryRetryTime(LAN_QUERY_RETRY_TIME), LanBeacon(nullptr), LanBeaconState(ELanBeaconState::NotUsingLanBeacon), LanNonce(0), LanQueryTimeLeft(0.0f), LanQueryRetryTimeLeft(0.0f)`
- L261 _public function_ `virtual ~FLANSession()`
- L271 _public prototype_ `bool Host(FOnValidQueryPacketDelegate& QueryDelegate);` — Creates the LAN beacon for queries/advertising servers @param QueryDelegate delegate to fire when a client query is received
- L282 _public prototype_ `bool Search(class FNboSerializeToBuffer& Packet, FOnValidResponsePacketDelegate& ResponseDelegate, FOnSearchingTimeoutDelegate& TimeoutDelegate);` — Creates the LAN beacon for queries/advertising servers @param Packet packet to be search when broadcasting the search @param ResponseDelegate delegate to fire when a server response is received @param TimeoutDelegate delegate to fire if we exceed maximum search time @return true if search was started successfully, false otherwise
- L287 _public prototype_ `void StopLANSession();` — Stops the LAN beacon from accepting broadcasts
- L289 _public prototype_ `void Tick(float DeltaTime);`
- L292 _public prototype_ `void CreateHostResponsePacket(FNboSerializeToBuffer& Packet, uint64 ClientNonce);` — create packet of MAX size
- L293 _public prototype_ `void CreateClientQueryPacket(FNboSerializeToBuffer& Packet, uint64 ClientNonce);`
- L301 _public prototype_ `bool BroadcastPacket(uint8* Packet, int32 Length);` — Uses the cached broadcast address to send packet to a subnet @param Packet the packet to send @param Length the size of the packet to send
- L303 _public function_ `ELanBeaconState::Type GetBeaconState() const`
- L308 _public member_ `FOnValidQueryPacket OnValidQueryPacketDelegates;`
- L309 _public member_ `FOnValidResponsePacket OnValidResponsePacketDelegates;`
- L310 _public member_ `FOnSearchingTimeout OnSearchTimeoutDelegates;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINEBASE_API`
- L16 _function_ `inline void GenerateNonce(uint8* Nonce, uint32 Length)` — Generates a random nonce (number used once) of the desired length @param Nonce the buffer that will get the randomized data @param Length the number of bytes to generate random values for
- L44 _variable_ `static const uint8 LAN_BEACON_PACKET_VERSION = (uint8)ELANBeaconVersionHistory::HISTORY_LATEST;`
- L47 _macro_ `#define LAN_BEACON_PACKET_HEADER_SIZE 32` — The size of the header for validation
- L50 _macro_ `#define LAN_BEACON_VER_OFFSET 0` — Offsets for various fields
- L51 _macro_ `#define LAN_BEACON_PLATFORM_OFFSET 1`
- L52 _macro_ `#define LAN_BEACON_GAMEID_OFFSET 2`
- L53 _macro_ `#define LAN_BEACON_PACKETTYPE1_OFFSET 6`
- L54 _macro_ `#define LAN_BEACON_PACKETTYPE2_OFFSET 7`
- L55 _macro_ `#define LAN_BEACON_NONCE_OFFSET 8`
- L56 _macro_ `#define LAN_BEACON_GUID_OFFSET 16`
- L59 _macro_ `#define LAN_SERVER_QUERY1 (uint8)'S'` — Packet types in 2 byte readable form
- L60 _macro_ `#define LAN_SERVER_QUERY2 (uint8)'Q'`
- L62 _macro_ `#define LAN_SERVER_RESPONSE1 (uint8)'S'`
- L63 _macro_ `#define LAN_SERVER_RESPONSE2 (uint8)'R'`
- L69 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnValidQueryPacket, uint8*, int32, uint64);` — LAN Session Delegates
- L69 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnValidQueryPacket, uint8*, int32, uint64);` — LAN Session Delegates
- L70 _typedef_ `typedef FOnValidQueryPacket::FDelegate FOnValidQueryPacketDelegate;`
- L72 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnValidResponsePacket, uint8*, int32);`
- L72 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnValidResponsePacket, uint8*, int32);`
- L73 _typedef_ `typedef FOnValidResponsePacket::FDelegate FOnValidResponsePacketDelegate;`
- L75 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSearchingTimeout);`
- L75 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnSearchingTimeout);`
- L76 _typedef_ `typedef FOnSearchingTimeout::FDelegate FOnSearchingTimeoutDelegate;`
- L79 _namespace_ `namespace ELanBeaconState`
- L92 _function_ `inline const TCHAR* ToString(ELanBeaconState::Type EnumVal)` (scope `ELanBeaconState`) — @return the stringified version of the enum passed in
- L168 _macro_ `#define LAN_ANNOUNCE_PORT 14001`
- L169 _macro_ `#define LAN_UNIQUE_ID 9999`
- L170 _macro_ `#define LAN_QUERY_TIMEOUT 5`
- L171 _macro_ `#define LAN_QUERY_RETRY_TIME 1`
- L172 _macro_ `#define LAN_PLATFORMMASK 0xffffffff`

### `Plugins/Online/OnlineBase/Source/Public/Online/NboSerializer.h` (Public)


#### class `FNboSerializeToBuffer`  
`class FNboSerializeToBuffer`  
_L19-407_
- desc: Serializes data in network byte order form into a buffer
- L22 _private prototype_ `FNboSerializeToBuffer(void);` — Hidden on purpose
- L28 _protected member_ `TArray<uint8> Data;` — Holds the data as it is serialized
- L32 _protected member_ `uint32 NumBytes;` — Tracks how many bytes have been written in the packet
- L35 _protected member_ `bool bHasOverflowed;` — Indicates whether writing to the buffer caused an overflow or not
- L41 _public function_ `FNboSerializeToBuffer(uint32 Size) : NumBytes(0), bHasOverflowed(false)` — Initializes the write tracking
- L52 _public function_ `inline operator uint8*(void) const` — Cast operator to get at the formatted buffer data
- L60 _public function_ `inline const TArray<uint8>& GetBuffer(void) const` — Cast operator to get at the formatted buffer data
- L68 _public function_ `inline uint32 GetByteCount(void) const` — Returns the size of the buffer we've built up
- L76 _public function_ `inline uint32 GetBufferSize(void) const` — Returns the number of bytes preallocated in the array
- L84 _public function_ `inline void TrimBuffer()` — Trim any extra space in the buffer that is not used
- L95 _public function_ `inline void Reset()` — Act as if the buffer is now empty. Useful for buffers that are reused
- L291 _public function_ `inline FNboSerializeToBuffer& AddString(const ANSICHAR* String,const int32 Length)` — Adds a substring to the buffer
- L364 _public function_ `inline void WriteBinary(const uint8* Buffer,uint32 NumToWrite)` — Writes a blob of data to the buffer @param Buffer the source data to append @param NumToWrite the size of the blob to write
- L380 _public function_ `inline uint8* GetRawBuffer(uint32 Offset)` — Gets the buffer at a specific point
- L390 _public function_ `inline void SkipAheadBy(uint32 Amount)` — Skips forward in the buffer by the specified amount @param Amount the number of bytes to skip ahead
- L403 _public function_ `inline bool HasOverflow(void) const` — Returns whether the buffer had an overflow when writing to it

#### class `FNboSerializeFromBuffer`  
`class FNboSerializeFromBuffer`  
_L416-741_
- desc: Class used to read data from a NBO data buffer
- L420 _protected member_ `const uint8* Data;` — Pointer to the data this reader is attached to
- L422 _protected member_ `const int32 NumBytes;` — The size of the data in bytes
- L424 _protected member_ `int32 CurrentOffset;` — The current location in the byte stream for reading
- L426 _protected member_ `bool bHasOverflowed;` — Indicates whether reading from the buffer caused an overflow or not
- L429 _protected prototype_ `FNboSerializeFromBuffer(void);` — Hidden on purpose
- L438 _public function_ `FNboSerializeFromBuffer(const uint8* InData,int32 Length) : Data(InData), NumBytes(Length), CurrentOffset(0), bHasOverflowed(false)` — Initializes the buffer, size, and zeros the read offset @param InData the buffer to attach to @param Length the size of the buffer we are attaching to
- L661 _public function_ `void ReadBinaryArray(TArray<uint8>& OutArray, uint32 NumToRead)` — Reads a blob of data from the buffer into an array Prevents the necessity for additional allocation. @param OutArray the destination array @param NumToRead the size of the blob to read
- L684 _public function_ `void ReadBinary(uint8* OutBuffer,uint32 NumToRead)` — Reads a blob of data from the buffer @param OutBuffer the destination buffer @param NumToRead the size of the blob to read
- L702 _public function_ `void Seek(int32 Pos)` — Seek to the desired position in the buffer @param Pos the offset from the start of the buffer
- L717 _public function_ `inline int32 Tell(void) const` — @return Current position of the buffer being to be read
- L723 _public function_ `inline bool HasOverflow(void) const` — Returns whether the buffer had an overflow when reading from it
- L729 _public function_ `inline int32 AvailableToRead(void) const` — @return Number of bytes remaining to read from the current offset to the end of the buffer
- L737 _public function_ `inline int32 GetBufferSize(void) const` — Returns the number of total bytes in the buffer

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINEBASE_API`
- L10 _namespace_ `namespace NboSerializer`
- L13 _variable_ `template <typename T> static constexpr inline bool UnexpectedType = false;` (scope `NboSerializer`)
- L104 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar, const bool B)` — Adds a bool to the buffer (converted to uint8)
- L114 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const char Ch)` — Adds a char to the buffer
- L131 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const uint8& B)` — Adds a byte to the buffer
- L149 _function_ `template<class TEnum> friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const TEnumAsByte<TEnum>& B)` — Adds a byte to the buffer
- L157 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const int32& I)` — Adds an int32 to the buffer
- L165 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const uint32& D)` — Adds a uint32 to the buffer
- L186 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const uint64& Q)` — Adds a uint64 to the buffer
- L211 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const float& F)` — Adds a float to the buffer
- L220 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const double& Dbl)` — Adds a double to the buffer
- L229 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const FString& String)` — Adds a FString to the buffer
- L260 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const TCHAR* String)` — Adds a string to the buffer
- L318 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const FName& Name)` — Adds an FName to the buffer as a string
- L328 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const FInternetAddr& Addr)` — Adds an ip address to the buffer
- L340 _function_ `friend inline FNboSerializeToBuffer& operator<<(FNboSerializeToBuffer& Ar,const FGuid& Guid)` — Adds a FGuid to the buffer
- L351 _function_ `template <typename T> friend inline FNboSerializeToBuffer& operator <<(FNboSerializeToBuffer& Ar, const T& Value)` — This will be chosen in case of any type not specially supported
- L449 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar, bool& B)` — Reads a bool from the buffer (as uint8)
- L461 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,char& Ch)` — Reads a char from the buffer
- L477 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,uint8& B)` — Reads a byte from the buffer
- L493 _function_ `template<class TEnum> friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,TEnumAsByte<TEnum>& B)` — Reads a byte from the buffer
- L501 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,int32& I)` — Reads an int32 from the buffer
- L509 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,uint32& D)` — Reads a uint32 from the buffer
- L530 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,uint64& Q)` — Adds a uint64 to the buffer
- L554 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,float& F)` — Reads a float from the buffer
- L562 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,double& Dbl)` — Reads a double from the buffer
- L570 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,FString& String)` — Reads a FString from the buffer
- L609 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,FName& Name)` — Reads an FName from the buffer
- L620 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,FInternetAddr& Addr)` — Reads an ip address from the buffer
- L636 _function_ `friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar,FGuid& Guid)` — Reads a FGuid from the buffer
- L647 _function_ `template <typename T> friend inline FNboSerializeFromBuffer& operator>>(FNboSerializeFromBuffer& Ar, T& Value)` — This will be chosen in case of any type not specially supported

### `Plugins/Online/OnlineBase/Source/Public/Online/OnlineBase.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define ONLINE_SUCCESS 0`
- L13 _macro_ `#define ONLINE_FAIL (uint32)-1`
- L17 _macro_ `#define ONLINE_IO_PENDING 997`
- L20 _prototype_ `TAutoConsoleVariable<int32>& GetBuildIdOverrideCVar();`

### `Plugins/Online/OnlineBase/Source/Public/Online/OnlineSessionNames.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define DEFAULT_BEACON_PORT 15000` — default beacon port, if not specified by other means
- L16 _macro_ `#define SETTING_MAPNAME FName(TEXT("MAPNAME"))` — Setting describing the name of the current map (value is FString)
- L18 _macro_ `#define SETTING_NUMBOTS FName(TEXT("NUMBOTS"))` — Setting describing the number of bots in the session (value is int32)
- L20 _macro_ `#define SETTING_GAMEMODE FName(TEXT("GAMEMODE"))` — Setting describing the game mode of the session (value is FString)
- L22 _macro_ `#define SETTING_BEACONPORT FName(TEXT("BEACONPORT"))` — Setting describing the beacon host port (value is int32)
- L24 _macro_ `#define SETTING_QOS FName(TEXT("QOS"))` — Server responds to Qos beacon requests (value is int32)
- L26 _macro_ `#define SETTING_REGION FName(TEXT("REGION"))` — Setting describing the region of the world you are in (value is FString)
- L28 _macro_ `#define SETTING_SUBREGION FName(TEXT("SUBREGION"))` — Setting describing the a specific subregion preference within a region (value is FString)
- L30 _macro_ `#define SETTING_DCID FName(TEXT("DCID"))` — Setting describing the unique id of a datacenter (value is FString)
- L32 _macro_ `#define SETTING_NEEDS FName(TEXT("NEEDS"))` — Number of players needed to fill out this session (value is int32)
- L34 _macro_ `#define SETTING_NEEDSSORT FName(TEXT("NEEDSSORT"))` — Second key for "needs" because can't set same value with two criteria (value is int32)
- L36 _macro_ `#define SETTING_SESSIONKEY FName(TEXT("SESSIONKEY"))` — Setting describing the session key (value is FString)
- L38 _macro_ `#define SETTING_ALLOWBROADCASTING FName(TEXT("ALLOWBROADCASTING"))` — Setting describing the session key (value is FString)
- L40 _macro_ `#define SETTING_BROADCASTER FName(TEXT("BROADCASTER"))` — Setting defining broadcaster (value is bool)
- L42 _macro_ `#define SETTING_PARTYMEMBERSPECTATOR FName(TEXT("PARTYMEMBERSPECTATOR"))` — Setting defining if we are a party member spectator (value is bool)
- L44 _macro_ `#define SETTING_MAXSPECTATORS FName(TEXT("MAXSPECTATORS"))` — Setting describing the number of spectator slots in the session (value is int32)
- L47 _macro_ `#define SETTING_CUSTOMSEARCHINT1 FName(TEXT("CUSTOMSEARCHINT1"))` — 8 user defined integer params to be used when filtering searches for sessions
- L48 _macro_ `#define SETTING_CUSTOMSEARCHINT2 FName(TEXT("CUSTOMSEARCHINT2"))`
- L49 _macro_ `#define SETTING_CUSTOMSEARCHINT3 FName(TEXT("CUSTOMSEARCHINT3"))`
- L50 _macro_ `#define SETTING_CUSTOMSEARCHINT4 FName(TEXT("CUSTOMSEARCHINT4"))`
- L51 _macro_ `#define SETTING_CUSTOMSEARCHINT5 FName(TEXT("CUSTOMSEARCHINT5"))`
- L52 _macro_ `#define SETTING_CUSTOMSEARCHINT6 FName(TEXT("CUSTOMSEARCHINT6"))`
- L53 _macro_ `#define SETTING_CUSTOMSEARCHINT7 FName(TEXT("CUSTOMSEARCHINT7"))`
- L54 _macro_ `#define SETTING_CUSTOMSEARCHINT8 FName(TEXT("CUSTOMSEARCHINT8"))`
- L57 _macro_ `#define SETTING_ALLOWEXTERNALMEMBERSINSESSION FName("ALLOWEXTERNALMEMBERSINSESSION")` — Setting to allow non-primary platform members in a session
- L63 _macro_ `#define SETTING_HOST_MIGRATION FName(TEXT("HOSTMIGRATION"))` — Setting describing whether host migration is enabled for the session.  This typically means when the host leaves, the online service picks a new host instead of destroying the session.  Not supported by all online services.
- L77 _macro_ `#define SETTING_CUSTOM FName(TEXT("CUSTOM"))` — Custom settings to be associated with Session (value is FString)
- L79 _macro_ `#define SETTING_PARTY_ENABLED_SESSION FName(TEXT("PARTYENABLEDSESSION"))` — Session is marked as using party enabled session flag (value is bool)
- L81 _macro_ `#define SETTING_MATCHING_HOPPER FName(TEXT("MATCHHOPPER"))` — Hopper name to search within (value is FString)
- L83 _macro_ `#define SETTING_MATCHING_TIMEOUT FName(TEXT("MATCHTIMEOUT"))` — Timeout for search (value is float seconds)
- L85 _macro_ `#define SETTING_MATCHING_ATTRIBUTES FName(TEXT("MATCHATTRIBUTES"))` — Match attributes (value is FString)
- L87 _macro_ `#define SETTING_MATCH_MEMBERS_JSON FName(TEXT("MATCHMEMBERS"))` — Match attributes (value is FString)
- L89 _macro_ `#define SETTING_SESSION_MEMBER_CONSTANT_CUSTOM_JSON_XUID_PREFIX TEXT("SESSIONMEMBERCONSTANTCUSTOMJSON")` — Session member constant custom json (value is FString) - This is to be used with FString::Printf, populated with user xuid
- L91 _macro_ `#define SETTING_MAX_RESULT FName(TEXT("MAXRESULT"))` — Set self as host (value is int32)
- L93 _macro_ `#define SETTING_CONTRACT_VERSION_FILTER FName(TEXT("CONTRACTVERSIONFILTER"))` — Set self as host (value is int32)
- L95 _macro_ `#define SETTING_FIND_PRIVATE_SESSIONS FName(TEXT("FINDPRIVATESESSIONS"))` — Set self as host (value is int32)
- L97 _macro_ `#define SETTING_FIND_RESERVED_SESSIONS FName(TEXT("FINDRESERVEDSESSIONS"))` — Set self as host (value is int32)
- L99 _macro_ `#define SETTING_FIND_INACTIVE_SESSIONS FName(TEXT("FINDINACTIVESESSIONS"))` — Set self as host (value is int32)
- L101 _macro_ `#define SETTING_MULTIPLAYER_VISIBILITY FName(TEXT("MULTIPLAYERVISIBILITY"))` — Set self as host (value is int32)
- L103 _macro_ `#define SETTING_SESSION_TEMPLATE_NAME FName(TEXT("SESSIONTEMPLATENAME"))` — Session template name, must match a session template name from the service config.
- L105 _macro_ `#define SETTING_CHANGE_NUMBER FName(TEXT("CHANGENUMBER"))` — Session change number from shoulder tapped version
- L107 _macro_ `#define SETTING_ALLOW_ARBITER_MIGRATION FName(TEXT("ALLOWARBITERMIGRATION"))` — Session can attempt arbiter migration
- L109 _macro_ `#define SETTING_MATCHING_PRESERVE_SESSION FName(TEXT("PRESERVESESSIONALWAYS"))` — Session preservation type for matchmaking
- L111 _macro_ `#define SETTING_GAME_SESSION_URI FName(TEXT("GAMESESSIONURI"))` — Matchmade game session URI for join in progress/invites
- L113 _macro_ `#define SETTING_GROUP_NAME_PREFIX TEXT("USERGROUPNAME")` — Session member group identifier (value is FString) - This is to be used with FString::Printf, populated with user xuid - Field required with Team Based matchmaking
- L115 _macro_ `#define SETTING_CUSTOM_JOIN_INFO FName(TEXT("CUSTOMJOININFO"))` — Information to join a third-party auxiliary session (value is FString)
- L117 _macro_ `#define SETTING_SESSION_SUBSCRIPTION_TYPES FName(TEXT("SESSIONSUBSCRIPTIONTYPE"))` — What verbosity of session updates to subscribe to (value is FString, comma-separated if multiple values needed)
- L119 _macro_ `#define SETTING_ACTIVITY_SESSION FName(TEXT("ACTIVITYSESSION"))` — Whether the session should be considered as the player's activity session or otherwise (value is bool)
- L126 _macro_ `#define SEARCH_DEDICATED_ONLY FName(TEXT("DEDICATEDONLY"))` — Search only for dedicated servers (value is true/false)
- L128 _macro_ `#define SEARCH_EMPTY_SERVERS_ONLY FName(TEXT("EMPTYONLY"))` — Search for empty servers only (value is true/false)
- L130 _macro_ `#define SEARCH_NONEMPTY_SERVERS_ONLY FName(TEXT("NONEMPTYONLY"))` — Search for non empty servers only (value is true/false)
- L132 _macro_ `#define SEARCH_SECURE_SERVERS_ONLY FName(TEXT("SECUREONLY"))` — Search for secure servers only (value is true/false)
- L135 _macro_ `#define SEARCH_MINSLOTSAVAILABLE FName(TEXT("MINSLOTSAVAILABLE"))` — Search for a match with min player availability (value is int)
- L137 _macro_ `#define SEARCH_EXCLUDE_UNIQUEIDS FName(TEXT("EXCLUDEUNIQUEIDS"))` — Exclude all matches where any unique ids in a given array are present (value is string of the form "uniqueid1;uniqueid2;uniqueid3")
- L139 _macro_ `#define SEARCH_USER FName(TEXT("SEARCHUSER"))` — User ID to search for session of
- L141 _macro_ `#define SEARCH_KEYWORDS FName(TEXT("SEARCHKEYWORDS"))` — Keywords to match in session search
- L143 _macro_ `#define SEARCH_MATCHMAKING_QUEUE FName(TEXT("MATCHMAKINGQUEUE"))` — The matchmaking queue name to matchmake in, e.g. "TeamDeathmatch" (value is string)
- L145 _macro_ `#define SEARCH_XBOX_LIVE_HOPPER_NAME UE_DEPRECATED_MACRO(5.4, "SEARCH_XBOX_LIVE_HOPPER_NAME has been deprecated. Use SETTING_MATCHING_HOPPER instead.") SETTING_MATCHING_HOPPER` — If set, use the named Xbox Live hopper to find a session via matchmaking (value is a string)
- L147 _macro_ `#define SEARCH_XBOX_LIVE_SESSION_TEMPLATE_NAME UE_DEPRECATED_MACRO(5.4, "SEARCH_XBOX_LIVE_SESSION_TEMPLATE_NAME has been deprecated. Use SETTING_SESSION_TEMPLATE_NAME instead.") SETTING_SESSION_TEMPLATE_NAME` — Which session template from the service configuration to use.
- L149 _macro_ `#define SEARCH_SWITCH_SELECTION_METHOD FName(TEXT("SWITCHSELECTIONMETHOD"))` — Selection method used to determine which match to join when multiple are returned (valid only on Switch)
- L151 _macro_ `#define SEARCH_LOBBIES FName(TEXT("LOBBYSEARCH"))` — Whether to search for lobbies instead of sessions
- L155 _macro_ `#define SEARCH_USER_ATTRIBUTE_TEAM TEXT("TEAM")` — Team a user is searching for
