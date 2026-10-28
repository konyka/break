# Runtime / CookOnTheFly

- module root: `Source/Runtime/CookOnTheFly`
- headers: 5; symbols: 122
- symbol kinds: class=8, delegate=1, enum=2, enumerator=15, function=19, member=19, namespace=5, prototype=45, struct=7, typedef=1
- PublicDependencyModuleNames: Core, CoreUObject, Networking, Sockets

### `Source/Runtime/CookOnTheFly/Internal/CookOnTheFly.h` (Internal)


#### enum `UE::Cook::ECookOnTheFlyMessage`  
`enum class ECookOnTheFlyMessage : uint32`  
_L26-53_
- desc: Flags and message types to be used with the cook-on-the-fly server. The first 8 bits specifies the message type, i.e request, response or a on-way message.
- L29 _public enumerator_ `None = 0x00` — Represents no message.
- L32 _public enumerator_ `Request = 0x02` — A request message.
- L34 _public enumerator_ `Response = 0x04` — A response message.
- L35 _public enumerator_ `TypeFlags = 0x0F`
- L38 _public enumerator_ `CookPackage = 0x20` — Request to cook a package.
- L40 _public enumerator_ `GetCookedPackages = 0x30` — Get all currenlty cooked packages.
- L42 _public enumerator_ `RecompileShaders = 0x40` — Request to recompile shaders.
- L44 _public enumerator_ `PackagesCooked = 0x50` — One way message indicating that one or more packages has been cooked.
- L46 _public enumerator_ `FilesAdded = 0x60` — One way message indicating that one or more files has been added.
- L48 _public enumerator_ `RecookPackages = 0x70` — Request to recook packages.
- L50 _public enumerator_ `NetworkPlatformFile = 0x80` — Legacy message for NetworkPlatformFile
- L52 _public enumerator_ `GetAllOnDiskPackages = 0x90` — Request for a list of on-disk packages, which may or may not be cooked or cookable for a given platform

#### enum `UE::Cook::ECookOnTheFlyMessageStatus`  
`enum class ECookOnTheFlyMessageStatus : uint32`  
_L89-97_
- desc: Cook-on-the-fly message status.
- L92 _public enumerator_ `None` — No status.
- L94 _public enumerator_ `Ok` — The message is successful.
- L96 _public enumerator_ `Error` — The message failed.

#### struct `UE::Cook::FCookOnTheFlyMessageHeader`  
`struct FCookOnTheFlyMessageHeader`  
_L120-134_
- desc: Cook-on-the-fly message header.
- L123 _public member_ `ECookOnTheFlyMessage MessageType = ECookOnTheFlyMessage::None;` — Type of message
- L125 _public member_ `ECookOnTheFlyMessageStatus MessageStatus = ECookOnTheFlyMessageStatus::Ok;` — The message status.
- L127 _public member_ `uint32 CorrelationId = 0;` — Correlation id, used to match response with request.
- L129 _public member_ `int64 Timestamp = 0;` — When the message was sent.
- L131 _public prototype_ `FString ToString() const;`

#### class `UE::Cook::FCookOnTheFlyMessage`  
`class FCookOnTheFlyMessage`  
_L139-246_
- desc: Cook-on-the-fly message.
- L143 _public prototype_ `FCookOnTheFlyMessage() = default;` — Creates a new instance of a cook-on-the-fly message.
- L146 _public function_ `explicit FCookOnTheFlyMessage(ECookOnTheFlyMessage MessageType)` — Creates a new instance of a cook-on-the-fly message with the specified message type.
- L151 _public function_ `ECookOnTheFlyMessage GetMessageType() const`
- L159 _public function_ `FCookOnTheFlyMessageHeader& GetHeader()` — Returns the message header.
- L165 _public function_ `const FCookOnTheFlyMessageHeader& GetHeader() const` — Returns the message header.
- L171 _public function_ `void SetHeader(const FCookOnTheFlyMessageHeader& InHeader)` — Set a new message header.
- L177 _public function_ `void SetStatus(ECookOnTheFlyMessageStatus InStatus)` — Sets the message status.
- L183 _public function_ `ECookOnTheFlyMessageStatus GetStatus() const` — Returns the message status.
- L189 _public function_ `bool IsOk() const` — Returns whether the message stauts is OK.
- L195 _public prototype_ `void SetBody(TArray<uint8> InBody);` — Set the message body.
- L199 _public function_ `template<typename BodyType> void SetBodyTo(BodyType InBody)` — Set body to serializable type.
- L207 _public function_ `TArray<uint8>& GetBody()` — Returns the message body.
- L213 _public function_ `const TArray<uint8>& GetBody() const` — Returns the message body.
- L220 _public function_ `template<typename BodyType> BodyType GetBodyAs() const` — Serialize the body as the specified type.
- L230 _public function_ `int64 TotalSize() const` — Returns the total size of the message header and message body.
- L236 _public prototype_ `TUniquePtr<FArchive> ReadBody() const;` — Creates an archive for ready the message body.
- L239 _public prototype_ `TUniquePtr<FArchive> WriteBody();` — Creates an archive for writing the message body.
- L244 _protected member_ `FCookOnTheFlyMessageHeader Header;`
- L245 _protected member_ `TArray<uint8> Body;`

#### class `UE::Cook::FCookOnTheFlyRequest`  
`class FCookOnTheFlyRequest : public FCookOnTheFlyMessage`  
_L251-263_
- inherits: `FCookOnTheFlyMessage`
- desc: Cook-on-the-fly request.
- L256 _public prototype_ `FCookOnTheFlyRequest() = default;` — Creates a new instance of a cook-on-the-fly request.
- L259 _public function_ `explicit FCookOnTheFlyRequest(ECookOnTheFlyMessage MessageType) : FCookOnTheFlyMessage(MessageType | ECookOnTheFlyMessage::Request)` — Creates a new instance of a cook-on-the-fly request with the specified request type.

#### class `UE::Cook::FCookOnTheFlyResponse`  
`class FCookOnTheFlyResponse : public FCookOnTheFlyMessage`  
_L268-288_
- inherits: `FCookOnTheFlyMessage`
- desc: Cook-on-the-fly response.
- L273 _public prototype_ `FCookOnTheFlyResponse() = default;` — Creates a new instance of a cook-on-the-fly response.
- L276 _public function_ `explicit FCookOnTheFlyResponse(ECookOnTheFlyMessage MessageType) : FCookOnTheFlyMessage(MessageType | ECookOnTheFlyMessage::Response)` — Creates a new instance of a cook-on-the-fly response with the specified response type.
- L282 _public function_ `explicit FCookOnTheFlyResponse(const FCookOnTheFlyRequest& Request) : FCookOnTheFlyMessage(Request.GetMessageType())` — Creates a new instance of a cook-on-the-fly response for the specified request.

#### struct `UE::Cook::FCookOnTheFlyHostOptions`  
`struct FCookOnTheFlyHostOptions`  
_L293-299_
- desc: Cook-on-the-fly host address.
- L296 _public member_ `TArray<FString> Hosts;` — Host address.
- L298 _public member_ `FTimespan ServerStartupWaitTime;` — How long to wait for the server to start.

#### class `UE::Cook::ICookOnTheFlyServerConnection`  
`class ICookOnTheFlyServerConnection`  
_L301-335_
- L304 _public prototype_ `virtual ~ICookOnTheFlyServerConnection() = default;`
- L306 _public prototype_ `virtual const FString& GetHost() const = 0;`
- L308 _public prototype_ `virtual const FString& GetZenProjectName() const = 0;`
- L310 _public prototype_ `virtual const FString& GetPlatformName() const = 0;`
- L312 _public prototype_ `virtual const TArray<FString> GetZenHostNames() const = 0;`
- L314 _public prototype_ `virtual const uint16 GetZenHostPort() const = 0;`
- L319 _public prototype_ `virtual bool IsConnected() const = 0;` — Returns whether connected to the cook-on-the-fly server.
- L321 _public prototype_ `virtual bool IsSingleThreaded() const = 0;`
- L328 _public prototype_ `virtual TFuture<FCookOnTheFlyResponse> SendRequest(FCookOnTheFlyRequest& Request) = 0;` — Sends a request to the server. @param Request The request message to send.
- L333 _public prototype_ `DECLARE_EVENT_OneParam(ICookOnTheFlyServerConnection, FMessageEvent, const FCookOnTheFlyMessage&);` — Event triggered when a new message has been sent from the server.
- L334 _public prototype_ `virtual FMessageEvent& OnMessage() = 0;`

#### class `UE::Cook::ICookOnTheFlyModule`  
`class ICookOnTheFlyModule : public IModuleInterface`  
_L340-354_
- inherits: `IModuleInterface`
- desc: Cook-on-the-fly module
- L344 _public prototype_ `virtual ~ICookOnTheFlyModule() = default;`
- L346 _public prototype_ `virtual TSharedPtr<ICookOnTheFlyServerConnection> GetDefaultServerConnection() = 0;`
- L353 _public prototype_ `virtual TUniquePtr<ICookOnTheFlyServerConnection> ConnectToServer(const FCookOnTheFlyHostOptions& HostOptions) = 0;` — Connect to the cook-on-the-fly server. @param HostOptions Cook-on-the-fly host options.

#### Free symbols / members of external scopes

- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCookOnTheFly, Log, All);`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Cook` (scope `UE`)
- L54 _prototype_ `ENUM_CLASS_FLAGS(ECookOnTheFlyMessage);` (scope `UE::Cook`)
- L59 _function_ `inline const TCHAR* LexToString(ECookOnTheFlyMessage Message)` (scope `UE::Cook`) — Returns a string from the specified message.
- L102 _function_ `inline const TCHAR* LexToString(ECookOnTheFlyMessageStatus Status)` (scope `UE::Cook`) — Returns a string from the specified message status.
- L333 _delegate_ `DECLARE_EVENT_OneParam(ICookOnTheFlyServerConnection, FMessageEvent, const FCookOnTheFlyMessage&);` — Event triggered when a new message has been sent from the server.

### `Source/Runtime/CookOnTheFly/Internal/CookOnTheFlyMessages.h` (Internal)


#### struct `UE::ZenCookOnTheFly::Messaging::FCompletedPackages`  
`struct FCompletedPackages`  
_L11-17_
- L13 _public member_ `TArray<FPackageStoreEntryResource> CookedPackages;`
- L14 _public member_ `TArray<FPackageId> FailedPackages;`

#### struct `UE::ZenCookOnTheFly::Messaging::FCookPackageRequest`  
`struct FCookPackageRequest`  
_L19-24_
- L21 _public member_ `TArray<FPackageId> PackageIds;`

#### struct `UE::ZenCookOnTheFly::Messaging::FRecookPackagesRequest`  
`struct FRecookPackagesRequest`  
_L28-33_
- L30 _public member_ `TArray<FPackageId> PackageIds;`

#### struct `UE::ZenCookOnTheFly::Messaging::FRecookPackagesResponse`  
`struct FRecookPackagesResponse`  
_L35-38_

#### struct `UE::ZenCookOnTheFly::Messaging::FGetAllOnDiskPackagesRequest`  
`struct FGetAllOnDiskPackagesRequest`  
_L40-45_
- L42 _public member_ `TArray<FPackageId> PackageIds;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ZenCookOnTheFly` (scope `UE`)
- L8 _namespace_ `namespace Messaging` (scope `UE::ZenCookOnTheFly`)
- L26 _typedef_ `using FCookPackageResponse = FCompletedPackages;` (scope `UE::ZenCookOnTheFly::Messaging`)

### `Source/Runtime/CookOnTheFly/Private/CookOnTheFlyServerConnection.h` (Private)


#### class `ICookOnTheFlyServerTransport`  
`class ICookOnTheFlyServerTransport`  
_L9-20_
- L12 _public function_ `ICookOnTheFlyServerTransport()`
- L13 _public prototype_ `virtual ~ICookOnTheFlyServerTransport() = default;`
- L15 _public prototype_ `virtual bool Initialize(const TCHAR*) = 0;`
- L16 _public prototype_ `virtual void Disconnect() = 0;`
- L17 _public prototype_ `virtual bool SendPayload(const TArray<uint8>& Payload) = 0;`
- L18 _public prototype_ `virtual bool HasPendingPayload() = 0;`
- L19 _public prototype_ `virtual bool ReceivePayload(FArrayReader& Payload) = 0;`

#### Free symbols / members of external scopes

- L22 _prototype_ `UE::Cook::ICookOnTheFlyServerConnection* MakeCookOnTheFlyServerConnection(TUniquePtr<ICookOnTheFlyServerTransport> InTransport, const FString& InHost);`

### `Source/Runtime/CookOnTheFly/Private/PlatformTransport.h` (Private)


#### class `FPlatformTransport`  
`class FPlatformTransport : public ICookOnTheFlyServerTransport`  
_L12-40_
- inherits: `ICookOnTheFlyServerTransport`
- desc: Implementation of ITransport using IPlatformHostCommunication/IPlatformHostSocket interfaces (custom target and host pc communication).
- L17 _public prototype_ `FPlatformTransport(int32 InProtocolIndex, const FString& InProtocolName);`
- L18 _public prototype_ `~FPlatformTransport();`
- L21 _public prototype_ `virtual bool Initialize(const TCHAR* HostIp) override;`
- L22 _public prototype_ `virtual bool SendPayload(const TArray<uint8>& Payload) override;`
- L23 _public prototype_ `virtual bool ReceivePayload(FArrayReader& Payload) override;`
- L24 _public prototype_ `virtual bool HasPendingPayload() override;`
- L25 _public prototype_ `virtual void Disconnect() override;`
- L34 _private prototype_ `bool WaitUntilConnected();` — Wait until HostSocket is in a non-default state (preferably Connected). @return True is the socket is Connected, false otherwise (an error or if the host pc immediately disconnects).
- L36 _private member_ `int32 ProtocolIndex;`
- L37 _private member_ `FString ProtocolName;`
- L38 _private member_ `IPlatformHostSocketPtr HostSocket;`

### `Source/Runtime/CookOnTheFly/Private/TCPTransport.h` (Private)


#### class `FTCPTransport`  
`class FTCPTransport : public ICookOnTheFlyServerTransport`  
_L7-28_
- inherits: `ICookOnTheFlyServerTransport`
- L13 _public prototype_ `FTCPTransport();`
- L14 _public prototype_ `~FTCPTransport();`
- L17 _public prototype_ `virtual bool Initialize(const TCHAR* HostIp) override;` — ITransport Interface.
- L18 _public prototype_ `virtual bool SendPayload(const TArray<uint8>& Payload) override;`
- L19 _public prototype_ `virtual bool ReceivePayload(FArrayReader& Payload) override;`
- L20 _public prototype_ `virtual bool HasPendingPayload() override;`
- L21 _public prototype_ `virtual void Disconnect() override;`
- L25 _private member_ `class FSocket* FileSocket;`
- L26 _private member_ `class FMultichannelTcpSocket* MCSocket;`
- L27 _private member_ `FString HostName;`
