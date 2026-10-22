# Runtime / XMPP

- module root: `Source/Runtime/Online/XMPP`
- headers: 28; symbols: 885
- symbol kinds: class=37, delegate=30, enum=10, enumerator=65, function=76, macro=3, member=184, namespace=5, prototype=397, struct=3, typedef=23, variable=52
- PrivateDependencyModuleNames: Core, Json, WebSockets

### `Source/Runtime/Online/XMPP/Private/XmppLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogXmpp, Warning, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogXmpp, Warning, All);`

### `Source/Runtime/Online/XMPP/Private/XmppNull.h` (Private)


#### class `FXmppNull`  
`class FXmppNull`  
_L8-15_
- desc: Mock for when Xmpp implementation is not available on a platform
- L14 _public prototype_ `static TSharedRef<class IXmppConnection> CreateConnection();`

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/StropheConnection.h` (Private)


#### enum `EStropheConnectionState`  
`enum class EStropheConnectionState : uint8`  
_L17-23_
- L19 _public enumerator_ `Unknown`
- L20 _public enumerator_ `Disconnected`
- L21 _public enumerator_ `Connecting`
- L22 _public enumerator_ `Connected`

#### enum `EStropheConnectionEvent`  
`enum class EStropheConnectionEvent : uint8`  
_L25-31_
- L27 _public enumerator_ `Connect`
- L28 _public enumerator_ `RawConnect`
- L29 _public enumerator_ `Disconnect`
- L30 _public enumerator_ `Fail`

#### class `FStropheConnection`  
`class FStropheConnection`  
_L33-90_
- L36 _public prototype_ `explicit FStropheConnection(FStropheContext& InContext);`
- L37 _public prototype_ `~FStropheConnection();`
- L40 _public prototype_ `FStropheConnection(const FStropheConnection& Other) = delete;` — Do not allow copies/assigns
- L41 _public prototype_ `FStropheConnection(FStropheConnection&& Other) = delete;`
- L42 _public prototype_ `FStropheConnection& operator=(const FStropheConnection& Other) = delete;`
- L43 _public prototype_ `FStropheConnection& operator=(FStropheConnection&& Other) = delete;`
- L46 _public prototype_ `int32 GetTimeout() const;` — Get server timeout in milliseconds
- L48 _public prototype_ `int32 GetPingInterval() const;` — Get ping interval in milliseconds
- L50 _public prototype_ `void SetKeepAlive(int32 Timeout, int32 PingInterval);` — Set KeepAlive information in milliseconds
- L53 _public prototype_ `FString GetUserId() const;` — Get our current user
- L55 _public prototype_ `void SetUserId(const FXmppUserJid& NewUserJid);` — Set our current user
- L56 _public prototype_ `void SetUserId(const FString& NewUserId);`
- L59 _public prototype_ `FString GetPassword() const;` — Get our current password/auth
- L61 _public prototype_ `void SetPassword(const FString& NewPassword);` — Set our current password/auth
- L64 _public prototype_ `bool Connect(const FString& Domain, uint16 Port, FXmppConnectionStrophe& ConnectionManager);` — Connect to specified domain/port; will use previously set user/pass information
- L66 _public prototype_ `void Disconnect();` — Disconnect from the server
- L69 _public prototype_ `bool SendStanza(const FStropheStanza& Stanza);` — Queue a stanza to be sent
- L72 _public prototype_ `void XmppThreadTick();` — Tick to process events
- L75 _public prototype_ `void RegisterStropheHandler(FXmppConnectionStrophe& ConnectionManager);` — Manage Strophe event handlers
- L76 _public prototype_ `void RemoveStropheHandler();`
- L79 _public function_ `xmpp_ctx_t* GetContextPtr() const` — Get our context pointer
- L82 _public prototype_ `EStropheConnectionState GetConnectionState() const;` — Get our current connection state
- L85 _protected member_ `FStropheContext& Context;`
- L87 _protected member_ `xmpp_conn_t* XmppConnectionPtr;`
- L88 _protected member_ `int32 ConnectionTimeoutSeconds;`
- L89 _protected member_ `int32 ConnectionPingIntervalSeconds;`

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef struct _xmpp_conn_t xmpp_conn_t;`
- L15 _typedef_ `typedef struct _xmpp_ctx_t xmpp_ctx_t;`

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/StropheContext.h` (Private)


#### class `FStropheContext`  
`class FStropheContext`  
_L9-25_
- L12 _public prototype_ `explicit FStropheContext();`
- L13 _public prototype_ `~FStropheContext();`
- L16 _public prototype_ `FStropheContext(const FStropheContext& Other) = delete;` — Do not allow copies/assigns
- L17 _public prototype_ `FStropheContext(FStropheContext&& Other) = delete;`
- L18 _public prototype_ `FStropheContext& operator=(const FStropheContext& Other) = delete;`
- L19 _public prototype_ `FStropheContext& operator=(FStropheContext&& Other) = delete;`
- L21 _public function_ `xmpp_ctx_t* GetContextPtr() const`
- L24 _private member_ `xmpp_ctx_t* XmppContextPtr;`

#### Free symbols / members of external scopes

- L7 _typedef_ `typedef struct _xmpp_ctx_t xmpp_ctx_t;`

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/StropheError.h` (Private)


#### enum `EStropheErrorType`  
`enum class EStropheErrorType : uint8`  
_L14-41_
- L16 _public enumerator_ `Unknown`
- L17 _public enumerator_ `BadFormat`
- L18 _public enumerator_ `BadNSPrefix`
- L19 _public enumerator_ `Conflict`
- L20 _public enumerator_ `ConnectionTimeout`
- L21 _public enumerator_ `HostGone`
- L22 _public enumerator_ `HostUnknown`
- L23 _public enumerator_ `ImproperAddr`
- L24 _public enumerator_ `InternalServerError`
- L25 _public enumerator_ `InvalidFrom`
- L26 _public enumerator_ `InvalidId`
- L27 _public enumerator_ `InvalidNS`
- L28 _public enumerator_ `InvalidXML`
- L29 _public enumerator_ `NotAuthorized`
- L30 _public enumerator_ `PolicyViolation`
- L31 _public enumerator_ `RemoteConnectionFailed`
- L32 _public enumerator_ `ResourceConstraint`
- L33 _public enumerator_ `RestrictedXML`
- L34 _public enumerator_ `SeeOtherHost`
- L35 _public enumerator_ `SystemShutdown`
- L36 _public enumerator_ `UndefinedCondition`
- L37 _public enumerator_ `UnsupportedEncoding`
- L38 _public enumerator_ `UnsupportedStanzaType`
- L39 _public enumerator_ `UnsupportedVersion`
- L40 _public enumerator_ `XMLNotWellFormed`

#### class `FStropheError`  
`class FStropheError`  
_L43-61_
- L46 _public prototype_ `explicit FStropheError(const xmpp_stream_error_t& StreamError, int32 InErrorNumber);`
- L48 _public prototype_ `EStropheErrorType GetErrorType() const;`
- L49 _public prototype_ `const FString& GetErrorString() const;`
- L50 _public prototype_ `int32 GetErrorNumber() const;`
- L51 _public prototype_ `const FStropheStanza& GetStanza() const;`
- L54 _protected prototype_ `static EStropheErrorType ConvertStropheError(xmpp_error_type_t InErrorType);`
- L57 _protected member_ `EStropheErrorType ErrorType;`
- L58 _protected member_ `FString ErrorString;`
- L59 _protected member_ `int32 ErrorNumber;`
- L60 _protected member_ `const FStropheStanza ErrorStanza;`

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/StropheStanza.h` (Private)


#### class `FStropheStanza`  
`class FStropheStanza : public IXmppStanza`  
_L17-101_
- inherits: `IXmppStanza`
- L33 _public prototype_ `explicit FStropheStanza(const FXmppConnectionStrophe& Context, const FString& StanzaName = FString());`
- L34 _public prototype_ `FStropheStanza(const FStropheStanza& Other);`
- L35 _public prototype_ `FStropheStanza(FStropheStanza&& Other);`
- L36 _public prototype_ `virtual ~FStropheStanza();`
- L37 _public prototype_ `FStropheStanza& operator=(const FStropheStanza& Other);`
- L38 _public prototype_ `FStropheStanza& operator=(FStropheStanza&& Other);`
- L40 _public prototype_ `FStropheStanza Clone();`
- L42 _public prototype_ `void AddChild(const FStropheStanza& Child);`
- L43 _public prototype_ `virtual TUniquePtr<IXmppStanza> GetChild(const FString& ChildName) const override;`
- L44 _public prototype_ `TOptional<FStropheStanza> GetChildStropheStanza(const FString& ChildName);`
- L45 _public prototype_ `TOptional<const FStropheStanza> GetChildStropheStanza(const FString& ChildName) const;`
- L46 _public prototype_ `TOptional<FStropheStanza> GetChildByNameAndNamespace(const FString& ChildName, const FString& Namespace);`
- L47 _public prototype_ `TOptional<const FStropheStanza> GetChildByNameAndNamespace(const FString& ChildName, const FString& Namespace) const;`
- L48 _public prototype_ `virtual bool HasChild(const FString& ChildName) const override;`
- L49 _public prototype_ `bool HasChildByNameAndNamespace(const FString& ChildName, const FString& Namespace) const;`
- L51 _public prototype_ `TArray<FStropheStanza> GetChildren();`
- L52 _public prototype_ `const TArray<FStropheStanza> GetChildren() const;`
- L54 _public prototype_ `void SetNamespace(const FString& Namespace);`
- L55 _public prototype_ `FString GetNamespace() const;`
- L57 _public prototype_ `void SetAttribute(const FString& Key, const FString& Value);`
- L58 _public prototype_ `virtual FString GetAttribute(const FString& Key) const override;`
- L59 _public prototype_ `virtual bool HasAttribute(const FString& Key) const override;`
- L61 _public prototype_ `void SetName(const FString& Name);`
- L62 _public prototype_ `virtual FString GetName() const override;`
- L64 _public prototype_ `void SetText(const FString& Text);`
- L65 _public prototype_ `virtual FString GetText() const override;`
- L67 _public prototype_ `void SetType(const FString& Type);`
- L68 _public prototype_ `virtual FString GetType() const override;`
- L70 _public prototype_ `void SetId(const FString& Id);`
- L71 _public prototype_ `virtual FString GetId() const override;`
- L73 _public prototype_ `void SetTo(const FXmppUserJid& To);`
- L74 _public prototype_ `void SetTo(const FString& To);`
- L75 _public prototype_ `virtual FXmppUserJid GetTo() const override;`
- L77 _public prototype_ `void SetFrom(const FXmppUserJid& From);`
- L78 _public prototype_ `void SetFrom(const FString& From);`
- L79 _public prototype_ `virtual FXmppUserJid GetFrom() const override;`
- L84 _public prototype_ `bool AddBodyWithText(const FString& Text);` — Add a child stanza of name Body with the requested text.  Fails if we already have a body stanza, or if we are a text stanza.
- L86 _public prototype_ `virtual TOptional<FString> GetBodyText() const override;` — Get the text from a child Body stanza, if one exists
- L90 _protected function_ `xmpp_stanza_t* GetStanzaPtr() const` — Get the current stanza
- L93 _protected prototype_ `explicit FStropheStanza(xmpp_stanza_t* const OtherStanzaPtr);` — Passed in stanzas will be cloned instead of copied here
- L96 _protected prototype_ `explicit FStropheStanza(xmpp_ctx_t* const StropheContextPtr);` — Create a new stanza directly from a context
- L100 _protected member_ `xmpp_stanza_t* XmppStanzaPtr;` — Ref-counted pointer to libstrophe stanza data

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef struct _xmpp_ctx_t xmpp_ctx_t;`
- L14 _typedef_ `typedef struct _xmpp_conn_t xmpp_conn_t;`
- L15 _typedef_ `typedef struct _xmpp_stanza_t xmpp_stanza_t;`

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/StropheStanzaConstants.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace Strophe`
- L11 _variable_ `const TCHAR* const SN_BODY = TEXT("bod` (scope `Strophe`)
- L12 _variable_ `const TCHAR* const SN_MESSAGE = TEXT("mes` (scope `Strophe`)
- L13 _variable_ `const TCHAR* const SN_DELAY = TEXT("del` (scope `Strophe`)
- L14 _variable_ `const TCHAR* const SN_PRESENCE = TEXT("pre` (scope `Strophe`)
- L15 _variable_ `const TCHAR* const SN_SHOW = TEXT("sho` (scope `Strophe`)
- L16 _variable_ `const TCHAR* const SN_STATUS = TEXT("sta` (scope `Strophe`)
- L17 _variable_ `const TCHAR* const SN_X = TEXT("x")` (scope `Strophe`)
- L18 _variable_ `const TCHAR* const SN_ITEM = TEXT("ite` (scope `Strophe`)
- L19 _variable_ `const TCHAR* const SN_PASSWORD = TEXT("pas` (scope `Strophe`)
- L20 _variable_ `const TCHAR* const SN_ERROR = TEXT("err` (scope `Strophe`)
- L21 _variable_ `const TCHAR* const SN_FORBIDDEN = TEXT("for` (scope `Strophe`)
- L22 _variable_ `const TCHAR* const SN_BAD_REQUEST = TEXT("bad` (scope `Strophe`)
- L23 _variable_ `const TCHAR* const SN_NOT_AUTHORIZED = TEXT("not` (scope `Strophe`)
- L24 _variable_ `const TCHAR* const SN_ITEM_NOT_FOUND = TEXT("ite` (scope `Strophe`)
- L25 _variable_ `const TCHAR* const SN_NOT_ALLOWED = TEXT("not` (scope `Strophe`)
- L26 _variable_ `const TCHAR* const SN_NOT_ACCEPTABLE = TEXT("not` (scope `Strophe`)
- L27 _variable_ `const TCHAR* const SN_REGISTRATION_REQUIRED = TEXT("reg` (scope `Strophe`)
- L28 _variable_ `const TCHAR* const SN_CONFLICT = TEXT("con` (scope `Strophe`)
- L29 _variable_ `const TCHAR* const SN_SERVICE_UNAVAILABLE = TEXT("ser` (scope `Strophe`)
- L30 _variable_ `const TCHAR* const SN_HISTORY = TEXT("his` (scope `Strophe`)
- L31 _variable_ `const TCHAR* const SN_SUBJECT = TEXT("sub` (scope `Strophe`)
- L32 _variable_ `const TCHAR* const SN_IQ = TEXT("iq"` (scope `Strophe`)
- L33 _variable_ `const TCHAR* const SN_QUERY = TEXT("que` (scope `Strophe`)
- L34 _variable_ `const TCHAR* const SN_FIELD = TEXT("fie` (scope `Strophe`)
- L35 _variable_ `const TCHAR* const SN_VALUE = TEXT("val` (scope `Strophe`)
- L36 _variable_ `const TCHAR* const SN_RECIPIENT_UNAVAILABLE = TEXT("rec` (scope `Strophe`)
- L37 _variable_ `const TCHAR* const SN_PING = TEXT("pin` (scope `Strophe`)
- L41 _variable_ `const TCHAR* const ST_CHAT = TEXT("cha` (scope `Strophe`)
- L42 _variable_ `const TCHAR* const ST_UNAVAILABLE = TEXT("una` (scope `Strophe`)
- L43 _variable_ `const TCHAR* const ST_GROUPCHAT = TEXT("gro` (scope `Strophe`)
- L44 _variable_ `const TCHAR* const ST_ERROR = TEXT("err` (scope `Strophe`)
- L45 _variable_ `const TCHAR* const ST_SET = TEXT("set` (scope `Strophe`)
- L46 _variable_ `const TCHAR* const ST_GET = TEXT("get` (scope `Strophe`)
- L47 _variable_ `const TCHAR* const ST_SUBMIT = TEXT("sub` (scope `Strophe`)
- L48 _variable_ `const TCHAR* const ST_AUTH = TEXT("aut` (scope `Strophe`)
- L49 _variable_ `const TCHAR* const ST_RESULT = TEXT("res` (scope `Strophe`)
- L53 _variable_ `const TCHAR* const SA_STAMP = TEXT("sta` (scope `Strophe`)
- L54 _variable_ `const TCHAR* const SA_TYPE = TEXT("typ` (scope `Strophe`)
- L55 _variable_ `const TCHAR* const SA_ROLE = TEXT("rol` (scope `Strophe`)
- L56 _variable_ `const TCHAR* const SA_AFFILIATION = TEXT("aff` (scope `Strophe`)
- L57 _variable_ `const TCHAR* const SA_MAXSTANZAS = TEXT("max` (scope `Strophe`)
- L58 _variable_ `const TCHAR* const SA_VAR = TEXT("var` (scope `Strophe`)
- L59 _variable_ `const TCHAR* const SA_CODE = TEXT("cod` (scope `Strophe`)
- L60 _variable_ `const TCHAR* const SA_JID = TEXT("jid` (scope `Strophe`)
- L64 _variable_ `const TCHAR* const SNS_DELAY = TEXT("urn` (scope `Strophe`)
- L65 _variable_ `const TCHAR* const SNS_MUC = TEXT("htt` (scope `Strophe`) — jabber.org/protocol/muc");
- L66 _variable_ `const TCHAR* const SNS_MUC_USER = TEXT("htt` (scope `Strophe`) — jabber.org/protocol/muc#user");
- L67 _variable_ `const TCHAR* const SNS_MUC_OWNER = TEXT("htt` (scope `Strophe`) — jabber.org/protocol/muc#owner");
- L68 _variable_ `const TCHAR* const SNS_X_DATA = TEXT("jab` (scope `Strophe`)
- L69 _variable_ `const TCHAR* const SNS_PING = TEXT("urn` (scope `Strophe`)
- L70 _variable_ `const TCHAR* const SNS_DISCO_INFO = TEXT("htt` (scope `Strophe`) — jabber.org/protocol/disco#info");
- L74 _variable_ `const TCHAR* const SC_104 = TEXT("104` (scope `Strophe`)

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/StropheWebsocketConnection.h` (Private)


#### class `FStropheWebsocketConnection`  
`class FStropheWebsocketConnection`  
_L17-67_
- L20 _public prototype_ `explicit FStropheWebsocketConnection(FStropheContext& InContext, const FString& Url);`
- L21 _public prototype_ `~FStropheWebsocketConnection();`
- L24 _public prototype_ `FStropheWebsocketConnection(const FStropheWebsocketConnection& Other) = delete;` — Do not allow copies/assigns
- L25 _public prototype_ `FStropheWebsocketConnection(FStropheWebsocketConnection&& Other) = delete;`
- L26 _public prototype_ `FStropheWebsocketConnection& operator=(const FStropheWebsocketConnection& Other) = delete;`
- L27 _public prototype_ `FStropheWebsocketConnection& operator=(FStropheWebsocketConnection&& Other) = delete;`
- L36 _public prototype_ `bool Connect(const FXmppUserJid& UserJid, const FString& Password, FXmppConnectionStrophe& ConnectionManager);` — Connect to previously set url @param UserJid username @param Password password @param ConnectionManager connection object that will receive the stanzas/errors @return true if no errors were detected
- L38 _public prototype_ `void Disconnect();` — Disconnect from the server
- L41 _public prototype_ `bool SendStanza(FStropheStanza&& Stanza);` — Send a stanza
- L44 _public prototype_ `void Tick();` — Tick to process events
- L47 _private member_ `FStropheContext& Context;`
- L49 _private member_ `TSharedPtr<IWebSocket> Websocket;`
- L51 _private member_ `xmpp_conn_t* XmppConnectionPtr;`
- L54 _private prototype_ `static void WebsocketConnectHandler(void* const Userdata);` — Handlers for strophe external socket events
- L55 _private prototype_ `static void WebsocketCloseHandler(void* const Userdata);`
- L56 _private prototype_ `static void WebsocketSendHandler(const char* const Data, const size_t Length, void* const Userdata);`
- L58 _private prototype_ `void WebsocketConnect();`
- L59 _private prototype_ `void WebsocketClose();`
- L60 _private prototype_ `void WebsocketSend(const char* const Data, const size_t Length);`
- L63 _private prototype_ `void OnWebsocketConnected();` — Handlers for websocket events
- L64 _private prototype_ `void OnWebsocketConnectionError(const FString& Error);`
- L65 _private prototype_ `void OnWebsocketClosed(int32 StatusCode, const FString& Reason, bool bWasClean);`
- L66 _private prototype_ `void OnRawMessage(const void* Data, SIZE_T Size, SIZE_T BytesRemaining);`

#### Free symbols / members of external scopes

- L15 _typedef_ `typedef struct _xmpp_conn_t xmpp_conn_t;`

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/XmppConnectionStrophe.h` (Private)


#### class `FXmppConnectionStrophe`  
`class FXmppConnectionStrophe : public IXmppConnection , public FTSTickerObjectBase`  
_L25-137_
- inherits: `IXmppConnection,FTSTickerObjectBase`
- L33 _public prototype_ `explicit FXmppConnectionStrophe();` — FXmppConnectionStrophe
- L34 _public prototype_ `virtual ~FXmppConnectionStrophe();`
- L35 _public prototype_ `FXmppConnectionStrophe(const FXmppConnectionStrophe& Other) = delete;`
- L36 _public prototype_ `FXmppConnectionStrophe(FXmppConnectionStrophe&& Other) = delete;`
- L37 _public prototype_ `FXmppConnectionStrophe& operator=(const FXmppConnectionStrophe& Other) = delete;`
- L38 _public prototype_ `FXmppConnectionStrophe& operator=(FXmppConnectionStrophe&& Other) = delete;`
- L43 _public prototype_ `virtual void SetServer(const FXmppServer& NewServerConfiguration) override;` — IXmppConnection
- L44 _public prototype_ `virtual const FXmppServer& GetServer() const override;`
- L46 _public prototype_ `virtual void Login(const FString& UserId, const FString& Auth) override;`
- L47 _public prototype_ `virtual void Logout() override;`
- L49 _public prototype_ `virtual EXmppLoginStatus::Type GetLoginStatus() const override;`
- L51 _public prototype_ `virtual const FXmppUserJid& GetUserJid() const override;`
- L53 _public function_ `virtual FOnXmppLoginComplete& OnLoginComplete() override`
- L54 _public function_ `virtual FOnXmppLoginChanged& OnLoginChanged() override`
- L55 _public function_ `virtual FOnXmppLogoutComplete& OnLogoutComplete() override`
- L56 _public function_ `virtual FOnXmppStanzaSent& OnStanzaSent() override`
- L57 _public function_ `virtual FOnXmppStanzaReceived& OnStanzaReceived() override`
- L59 _public prototype_ `virtual IXmppMessagesPtr Messages() override;`
- L60 _public prototype_ `virtual IXmppMultiUserChatPtr MultiUserChat() override;`
- L61 _public prototype_ `virtual IXmppPresencePtr Presence() override;`
- L62 _public prototype_ `virtual IXmppChatPtr PrivateChat() override;`
- L63 _public prototype_ `virtual IXmppPubSubPtr PubSub() override;`
- L65 _public prototype_ `virtual void DumpState() const override;`
- L68 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L70 _public prototype_ `bool SendStanza(FStropheStanza&& Stanza);`
- L72 _public prototype_ `void StartXmppThread(const FXmppUserJid& ConnectionUser, const FString& ConnectionAuth);`
- L73 _public prototype_ `void StopXmppThread();`
- L77 _public prototype_ `void ReceiveConnectionStateChange(EStropheConnectionEvent Event, bool bQueue = true);`
- L78 _public prototype_ `void ReceiveConnectionError(const FStropheError& Error, EStropheConnectionEvent Event);`
- L79 _public prototype_ `void ReceiveStanza(const FStropheStanza& Stanza);`
- L80 _public prototype_ `void QueueNewLoginStatus(EXmppLoginStatus::Type NewStatus);`
- L81 _public prototype_ `void ProcessLoginStatusChange(EXmppLoginStatus::Type NewLoginStatus);`
- L84 _public function_ `const FStropheContext& GetContext() const` — Get our Context object
- L87 _public function_ `const FString& GetMucDomain() const` — Get the MUC domain that was saved right before we connected
- L91 _private prototype_ `void ReconnectLogin();` — Notify that Login was triggered again while already connected
- L95 _protected member_ `FStropheContext StropheContext;` — XMPP Context to use across this connection
- L98 _protected member_ `TUniquePtr<FXmppStropheThread> StropheThread;` — Our XMPP thread that manages sending/receiving/sending events
- L101 _protected member_ `TUniquePtr<FStropheWebsocketConnection> WebsocketConnection;` — If using websockets, use event driven websocket connection instead
- L104 _protected member_ `TAtomic<EXmppLoginStatus::Type> LoginStatus;` — Current login status
- L107 _protected member_ `TQueue<EXmppLoginStatus::Type> IncomingLoginStatusChanges;` — Queue of login status changes processed on tick so that we do not miss processing any status changes
- L110 _protected member_ `FXmppServer ServerConfiguration;` — XMPP Connection information to be used during Login/Connection
- L113 _protected member_ `FXmppUserJid UserJid;` — The User last logged into
- L116 _protected member_ `FString MucDomain;` — The Multi-User-Chat domain to use in stanzas
- L119 _protected member_ `FThreadSafeBool RequestLogout;` — Thread-Safe way to request we logout+cleanup from the XMPP Thread
- L122 _protected member_ `FOnXmppLoginComplete OnXmppLoginCompleteDelegate;` — Login status delegates
- L123 _protected member_ `FOnXmppLoginChanged OnXmppLoginChangedDelegate;`
- L124 _protected member_ `FOnXmppLogoutComplete OnXmppLogoutCompleteDelegate;`
- L127 _protected member_ `FOnXmppStanzaReceived OnXmppStanzaReceivedDelegate;` — Message Status delegates
- L128 _protected member_ `FOnXmppStanzaSent OnXmppStanzaSentDelegate;`
- L131 _protected member_ `FXmppMessagesStrophePtr MessagesStrophe;` — XMPP Implementation Shared Pointers
- L132 _protected member_ `FXmppMultiUserChatStrophePtr MultiUserChatStrophe;`
- L133 _protected member_ `FXmppPingStrophePtr PingStrophe;`
- L134 _protected member_ `FXmppPresenceStrophePtr PresenceStrophe;`
- L135 _protected member_ `FXmppPrivateChatStrophePtr PrivateChatStrophe;`
- L136 _protected member_ `FXmppPubSubStrophePtr PubSubStrophe;`

#### Free symbols / members of external scopes

- L15 _typedef_ `using FXmppMessagesStrophePtr = TSharedPtr<class FXmppMessagesStrophe, ESPMode::ThreadSafe>;`
- L16 _typedef_ `using FXmppMultiUserChatStrophePtr = TSharedPtr<class FXmppMultiUserChatStrophe, ESPMode::ThreadSafe>;`
- L17 _typedef_ `using FXmppPingStrophePtr = TSharedPtr<class FXmppPingStrophe, ESPMode::ThreadSafe>;`
- L18 _typedef_ `using FXmppPresenceStrophePtr = TSharedPtr<class FXmppPresenceStrophe, ESPMode::ThreadSafe>;`
- L19 _typedef_ `using FXmppPrivateChatStrophePtr = TSharedPtr<class FXmppPrivateChatStrophe, ESPMode::ThreadSafe>;`
- L20 _typedef_ `using FXmppPubSubStrophePtr = TSharedPtr<class FXmppPubSubStrophe, ESPMode::ThreadSafe>;`

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/XmppMessagesStrophe.h` (Private)


#### class `FXmppMessagesStrophe`  
`class FXmppMessagesStrophe : public IXmppMessages , public FTSTickerObjectBase`  
_L16-60_
- inherits: `IXmppMessages,FTSTickerObjectBase`
- L22 _public prototype_ `FXmppMessagesStrophe(FXmppConnectionStrophe& InConnectionManager);` — FXmppMessagesStrophe
- L23 _public prototype_ `~FXmppMessagesStrophe();`
- L26 _public prototype_ `bool ReceiveStanza(const FStropheStanza& IncomingStanza);` — XMPP Thread
- L27 _public prototype_ `bool HandleMessageStanza(const FStropheStanza& IncomingStanza);`
- L28 _public prototype_ `bool HandleMessageErrorStanza(const FStropheStanza& ErrorStanza);`
- L31 _public prototype_ `void OnDisconnect();` — Game Thread
- L32 _public prototype_ `void OnReconnect();`
- L35 _public prototype_ `virtual bool SendMessage(const FXmppUserJid& RecipientId, const FString& Type, const FString& Payload, bool bPayloadIsSerializedJson = false) override;` — IXmppMessages
- L36 _public prototype_ `virtual bool SendMessage(const FXmppUserJid& RecipientId, const FString& Type, const TSharedRef<class FJsonObject>& Payload) override;`
- L37 _public function_ `virtual FOnXmppMessageReceived& OnReceiveMessage() override`
- L40 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L43 _protected prototype_ `void OnMessageReceived(TUniquePtr<FXmppMessage>&& Message);`
- L46 _protected prototype_ `void CleanupMessages();` — Remove pending messages and engine KeepAwake calls
- L50 _protected member_ `FXmppConnectionStrophe& ConnectionManager;` — Connection manager controls sending data to XMPP thread
- L56 _protected member_ `TQueue<TUniquePtr<FXmppMessage>> IncomingMessages;` — Queue of Messages needing to be consumed. These are Queued on the XMPP thread, and Dequeued on the Game thread
- L59 _protected member_ `FOnXmppMessageReceived OnMessageReceivedDelegate;` — Delegate for game to listen to messages

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/XmppMultiUserChatStrophe.h` (Private)


#### enum `ERoomStatusStrophe`  
`enum class ERoomStatusStrophe : uint8`  
_L18-26_
- L20 _public enumerator_ `NotJoined`
- L21 _public enumerator_ `Joined`
- L22 _public enumerator_ `CreatePending`
- L23 _public enumerator_ `JoinPrivatePending`
- L24 _public enumerator_ `JoinPublicPending`
- L25 _public enumerator_ `ExitPending`

#### class `FXmppRoomStrophe`  
`class FXmppRoomStrophe`  
_L53-118_
- desc: Info cached about a joined/created room
- L57 _public function_ `FXmppRoomStrophe() : Status(ERoomStatusStrophe::NotJoined)`
- L62 _public function_ `void AddNewMessage(const TSharedRef<FXmppChatMessage>& ChatMessage)`
- L77 _public function_ `bool HasMember(const FXmppUserJid& RoomMemberJid) const` — Check if a member is in the chat room based on their room JID @param RoomMemberJid the member's JID in the room @return true if the member is in the chat room
- L89 _public function_ `FXmppChatMemberPtr GetMember(const FXmppUserJid& RoomMemberJid) const` — Get a member in the chat room based on their room JID @param RoomMemberJid the member's JID in the room @return pointer to the member, if found in the room
- L102 _public function_ `FXmppRoomId& GetRoomId()`
- L103 _public function_ `const FXmppRoomId& GetRoomId() const`
- L105 _public function_ `FString& GetNickname()`
- L106 _public function_ `const FString& GetNickname() const`
- L108 _public function_ `FXmppUserJid& GetRoomJid()`
- L109 _public function_ `const FXmppUserJid& GetRoomJid() const`
- L112 _public member_ `FXmppUserJid RoomJid;`
- L114 _public member_ `ERoomStatusStrophe Status;`
- L115 _public member_ `FXmppRoomInfo Info;`
- L116 _public member_ `TArray<FXmppChatMemberRef> Members;`
- L117 _public member_ `TArray<TSharedRef<FXmppChatMessage> > LastMessages;`

#### struct `FXmppStropheErrorPair`  
`struct FXmppStropheErrorPair`  
_L121-125_
- desc: Struct to hold Error information about a failed command
- L123 _public member_ `FString ErrorMessage;`
- L124 _public member_ `FXmppRoomId RoomId;`

#### struct `FXmppStropheSubjectUpdate`  
`struct FXmppStropheSubjectUpdate`  
_L128-132_
- desc: Struct to hold Subject information about a joined channel
- L130 _public member_ `FString NewSubject;`
- L131 _public member_ `FXmppRoomId RoomId;`

#### enum `EConfigureRoomTypeStrophe`  
`enum class EConfigureRoomTypeStrophe : uint8`  
_L134-139_
- L136 _public enumerator_ `NoCallback` — Trigger no callbacks.  Currently used for global chat config.
- L137 _public enumerator_ `UseCreateCallback` — New room config, trigger create callback when done
- L138 _public enumerator_ `UseConfigCallback` — Change existing room, trigger config callback when done

#### class `FXmppMultiUserChatStrophe`  
`class FXmppMultiUserChatStrophe : public IXmppMultiUserChat , public FTSTickerObjectBase`  
_L141-261_
- inherits: `IXmppMultiUserChat,FTSTickerObjectBase`
- L147 _public prototype_ `FXmppMultiUserChatStrophe(class FXmppConnectionStrophe& InConnectionManager);` — FXmppMultiUserChatStrophe
- L148 _public prototype_ `virtual ~FXmppMultiUserChatStrophe();`
- L151 _public prototype_ `bool ReceiveStanza(const FStropheStanza& IncomingStanza);` — XMPP Thread
- L152 _public prototype_ `bool HandlePresenceStanza(const FStropheStanza& IncomingStanza);`
- L153 _public prototype_ `bool HandlePresenceErrorStanza(const FStropheStanza& IncomingStanza);`
- L154 _public prototype_ `bool HandleGroupChatStanza(const FStropheStanza& IncomingStanza);`
- L155 _public prototype_ `bool HandleGroupChatErrorStanza(const FStropheStanza& IncomingStanza);`
- L156 _public prototype_ `bool HandleRoomConfigStanza(const FStropheStanza& IncomingStanza);`
- L157 _public prototype_ `bool HandleRoomConfigErrorStanza(const FStropheStanza& IncomingStanza);`
- L160 _public prototype_ `void OnDisconnect();` — Game Thread
- L161 _public prototype_ `void OnReconnect();`
- L164 _public prototype_ `virtual bool CreateRoom(const FXmppRoomId& RoomId, const FString& Nickname, const FXmppRoomConfig& RoomConfig) override;` — IXmppMultiUserChat
- L165 _public prototype_ `virtual bool ConfigureRoom(const FXmppRoomId& RoomId, const FXmppRoomConfig& RoomConfig) override;`
- L166 _public prototype_ `virtual bool RefreshRoomInfo(const FXmppRoomId& RoomId) override;`
- L167 _public prototype_ `virtual bool JoinPublicRoom(const FXmppRoomId& RoomId, const FString& Nickname) override;`
- L168 _public prototype_ `virtual bool JoinPrivateRoom(const FXmppRoomId& RoomId, const FString& Nickname, const FString& Password) override;`
- L169 _public prototype_ `virtual bool RegisterMember(const FXmppRoomId& RoomId, const FString& Nickname) override;`
- L170 _public prototype_ `virtual bool UnregisterMember(const FXmppRoomId& RoomId, const FString& Nickname) override;`
- L171 _public prototype_ `virtual bool ExitRoom(const FXmppRoomId& RoomId) override;`
- L172 _public prototype_ `virtual bool SendChat(const FXmppRoomId& RoomId, const class FString& MsgBody, const FString& ChatInfo) override;`
- L173 _public prototype_ `virtual void GetJoinedRooms(TArray<FXmppRoomId>& OutRooms) override;`
- L174 _public prototype_ `virtual bool GetRoomInfo(const FXmppRoomId& RoomId, FXmppRoomInfo& OutRoomInfo) override;`
- L175 _public prototype_ `virtual bool GetMembers(const FXmppRoomId& RoomId, TArray<FXmppChatMemberRef>& OutMembers) override;`
- L176 _public prototype_ `virtual FXmppChatMemberPtr GetMember(const FXmppRoomId& RoomId, const FXmppUserJid& MemberJid) override;`
- L177 _public prototype_ `virtual bool GetLastMessages(const FXmppRoomId& RoomId, int32 NumMessages, TArray< TSharedRef<FXmppChatMessage> >& OutMessages) override;`
- L178 _public prototype_ `virtual void HandleMucPresence(const FXmppMucPresence& MemberPresence) override;`
- L179 _public prototype_ `virtual void DumpMultiUserChatState() const override;`
- L180 _public function_ `virtual FOnXmppRoomCreateComplete& OnRoomCreated() override`
- L181 _public function_ `virtual FOnXmppRoomConfigureComplete& OnRoomConfigured() override`
- L182 _public function_ `virtual FOnXmppRoomInfoRefreshComplete& OnRoomInfoRefreshed() override`
- L183 _public function_ `virtual FOnXmppRoomJoinPublicComplete& OnJoinPublicRoom() override`
- L184 _public function_ `virtual FOnXmppRoomJoinPrivateComplete& OnJoinPrivateRoom() override`
- L185 _public function_ `virtual FOnXmppRoomExitComplete& OnExitRoom() override`
- L186 _public function_ `virtual FOnXmppRoomMemberJoin& OnRoomMemberJoin() override`
- L187 _public function_ `virtual FOnXmppRoomMemberExit& OnRoomMemberExit() override`
- L188 _public function_ `virtual FOnXmppRoomMemberChanged& OnRoomMemberChanged() override`
- L189 _public function_ `virtual FOnXmppRoomChatReceived& OnRoomChatReceived() override`
- L192 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L195 _protected prototype_ `void OnReceiveMucPresence(FXmppMucPresence&& MemberPresence);`
- L196 _protected prototype_ `void OnReceiveMucPresenceError(FXmppStropheErrorPair&& PresenceError);`
- L197 _protected prototype_ `void OnReceiveGroupChatMessage(TUniquePtr<FXmppChatMessage>&& GroupChatMessage);`
- L198 _protected prototype_ `void OnReceiveGroupChatSubject(FXmppStropheSubjectUpdate&& GroupChatMessage);`
- L199 _protected prototype_ `void OnReceiveRoomConfigError(FXmppStropheErrorPair&& RoomConfigError);`
- L200 _protected prototype_ `void OnReceiveRoomConfigSuccess(FXmppRoomId&& RoomId);`
- L201 _protected prototype_ `void OnReceieveRoomInfoUpdate(FXmppRoomId&& RoomId);`
- L203 _protected prototype_ `bool SendJoinRoomStanza(const FXmppRoomStrophe& Room, const FString& Password = FString());`
- L204 _protected prototype_ `bool SendExitRoomStanza(const FXmppRoomStrophe& Room);`
- L205 _protected prototype_ `bool SendRequestRoomInfoConfigStanza(const FXmppRoomStrophe& Room);`
- L207 _protected prototype_ `bool InternalConfigureRoom(const FXmppRoomStrophe& Room, const FXmppRoomConfig& RoomConfig, EConfigureRoomTypeStrophe CallbackType);`
- L210 _protected prototype_ `void HandleCreateRoomComplete(FXmppRoomStrophe& Room, FXmppMucPresence&& MemberPresence);` — Events that happen to us
- L211 _protected prototype_ `void HandleJoinPrivateRoomComplete(FXmppRoomStrophe& Room, FXmppMucPresence&& MemberPresence);`
- L212 _protected prototype_ `void HandleJoinPublicRoomComplete(FXmppRoomStrophe& Room, FXmppMucPresence&& MemberPresence);`
- L213 _protected prototype_ `void HandleExitRoomComplete(FXmppRoomStrophe& Room, FXmppMucPresence&& MemberPresence);`
- L216 _protected prototype_ `void HandleRoomMemberJoined(FXmppRoomStrophe& Room, FXmppMucPresence&& MemberPresence);` — Events that happen to others in our rooms
- L217 _protected prototype_ `void HandleRoomMemberChanged(FXmppRoomStrophe& Room, FXmppMucPresence&& MemberPresence);`
- L218 _protected prototype_ `void HandleRoomMemberLeft(FXmppRoomStrophe& Room, FXmppMucPresence&& MemberPresence);`
- L221 _protected prototype_ `void CleanupMessages();` — Remove pending messages and engine KeepAwake calls
- L225 _protected member_ `FXmppConnectionStrophe& ConnectionManager;` — Connection manager controls sending data to XMPP thread
- L228 _protected member_ `TMap<FXmppRoomId, FXmppRoomStrophe> Chatrooms;` — Cache of known Rooms we belong to
- L231 _protected member_ `TMap<FXmppRoomId, FXmppRoomConfig> PendingRoomCreateConfigs;` — Cache of Room configs while we wait for the corresponding room to be created
- L233 _protected member_ `TMap<FXmppRoomId, EConfigureRoomTypeStrophe> PendingRoomConfigCallbacks;` — Cache of Room config callbacks while we wait for the corresponding room to be configured
- L236 _protected member_ `TQueue<TUniquePtr<FXmppMucPresence>> IncomingMucPresenceUpdates;` — Queue of presence updates from the server
- L238 _protected member_ `TQueue<FXmppStropheErrorPair> IncomingMucPresenceErrors;` — Queue of presence errors from the server
- L240 _protected member_ `TQueue<TUniquePtr<FXmppChatMessage>> IncomingGroupChatMessages;` — Queue of new chat messages from the server
- L242 _protected member_ `TQueue<FXmppStropheSubjectUpdate> IncomingRoomSubjects;` — Queue of new Subjects for chat rooms
- L244 _protected member_ `TQueue<FXmppStropheErrorPair> IncomingRoomConfigErrors;` — Queue of room configuration errors from the server
- L246 _protected member_ `TQueue<FXmppRoomId> IncomingRoomConfigWriteSuccesses;` — Queue of room configuration writes that came back successful
- L248 _protected member_ `TQueue<FXmppRoomId> IncomingRoomInfoUpdates;` — Queue of room configuration updates to be queried
- L251 _protected member_ `FOnXmppRoomCreateComplete OnXmppRoomCreateCompleteDelegate;` — Delegates for game to listen for MUC events
- L252 _protected member_ `FOnXmppRoomConfigureComplete OnXmppRoomConfiguredDelegate;`
- L253 _protected member_ `FOnXmppRoomInfoRefreshComplete OnXmppRoomInfoRefreshedDelegate;`
- L254 _protected member_ `FOnXmppRoomJoinPublicComplete OnXmppRoomJoinPublicCompleteDelegate;`
- L255 _protected member_ `FOnXmppRoomJoinPrivateComplete OnXmppRoomJoinPrivateCompleteDelegate;`
- L256 _protected member_ `FOnXmppRoomExitComplete OnXmppRoomExitCompleteDelegate;`
- L257 _protected member_ `FOnXmppRoomMemberJoin OnXmppRoomMemberJoinDelegate;`
- L258 _protected member_ `FOnXmppRoomMemberExit OnXmppRoomMemberExitDelegate;`
- L259 _protected member_ `FOnXmppRoomMemberChanged OnXmppRoomMemberChangedDelegate;`
- L260 _protected member_ `FOnXmppRoomChatReceived OnXmppRoomChatReceivedDelegate;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define MAX_MESSAGE_HISTORY 50`
- L28 _function_ `inline const TCHAR* LexToString(ERoomStatusStrophe Value)`

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/XmppPingStrophe.h` (Private)


#### struct `FXmppPingReceivedInfo`  
`struct FXmppPingReceivedInfo`  
_L17-33_
- L20 _public member_ `FXmppUserJid FromJid;`
- L21 _public member_ `FString PingId;`
- L24 _public function_ `FXmppPingReceivedInfo()`
- L28 _public function_ `FXmppPingReceivedInfo(FXmppUserJid&& InFromJid, FString&& InPingId) : FromJid(MoveTemp(InFromJid)) , PingId(MoveTemp(InPingId))`

#### class `FXmppPingStrophe`  
`class FXmppPingStrophe : public FTSTickerObjectBase`  
_L35-96_
- inherits: `FTSTickerObjectBase`
- L40 _public prototype_ `FXmppPingStrophe(FXmppConnectionStrophe& InConnectionManager);` — FXmppPingStrophe
- L41 _public prototype_ `virtual ~FXmppPingStrophe();`
- L44 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L47 _public prototype_ `void OnDisconnect();` — Clear any caches on disconnect
- L48 _public prototype_ `void OnReconnect();`
- L51 _public prototype_ `bool ReceiveStanza(const FStropheStanza& IncomingStanza);` — Determine if an incoming stanza is a ping stanza
- L54 _public prototype_ `void ResetPingTimer();` — Reset the ping timer (usually due to incoming/outgoing traffic)
- L57 _public prototype_ `void ResetPongTimer();` — Reset the pong timer (usually due to incoming traffic)
- L61 _protected prototype_ `bool HandlePingStanza(const FStropheStanza& PingStanza);` — Process parsing a ping we have received and queue it to be replied to
- L64 _protected prototype_ `void ReplyToPing(FXmppPingReceivedInfo&& ReceivedPing);` — Queue a reply to a specific ping we received
- L67 _protected prototype_ `void SendClientPing();` — Send a ping from the client to the server
- L70 _protected prototype_ `void CheckXmppPongTimeout(float DeltaTime);` — Check the current status of our Xmpp ping responses; may lead to disconnection requests
- L73 _protected prototype_ `void CleanupMessages();` — Remove pending messages and engine KeepAwake calls
- L77 _private member_ `FXmppConnectionStrophe& ConnectionManager;` — Connection manager controls sending data to XMPP thread
- L80 _private member_ `TQueue<FXmppPingReceivedInfo> IncomingPings;` — Queued pings we have received but haven't processed
- L83 _private member_ `float TimeSinceLastClientPing;` — The time since we last sent the server a ping
- L86 _private member_ `bool bWaitingForPong;` — Are we waiting for a pong?
- L89 _private member_ `float SecondsSinceLastServerPong;` — The amount of seconds since the server last responded to our ping request
- L92 _private member_ `FThreadSafeBool bHasReceievedServerPong;` — Have we received a pong since the last tick?
- L95 _private member_ `int32 MissedPongs;` — Number of missed pongs

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/XmppPresenceStrophe.h` (Private)


#### class `FXmppPresenceStrophe`  
`class FXmppPresenceStrophe : public IXmppPresence , public FTSTickerObjectBase`  
_L17-65_
- inherits: `IXmppPresence,FTSTickerObjectBase`
- L23 _public prototype_ `FXmppPresenceStrophe(FXmppConnectionStrophe& InConnectionManager);` — FXmppPresenceStrophe
- L24 _public prototype_ `virtual ~FXmppPresenceStrophe();`
- L27 _public prototype_ `bool ReceiveStanza(const FStropheStanza& IncomingStanza);` — XMPP Thread
- L30 _public prototype_ `void OnDisconnect();` — Game Thread
- L31 _public prototype_ `void OnReconnect();`
- L34 _public prototype_ `virtual bool UpdatePresence(const FXmppUserPresence& NewPresence) override;` — IXmppPresence
- L35 _public prototype_ `virtual const FXmppUserPresence& GetPresence() const override;`
- L36 _public prototype_ `virtual bool QueryPresence(const FString& UserId) override;`
- L37 _public prototype_ `virtual TArray<TSharedPtr<FXmppUserPresence>> GetRosterPresence(const FString& UserId) override;`
- L38 _public prototype_ `virtual void GetRosterMembers(TArray<FXmppUserJid>& Members) override;`
- L39 _public function_ `virtual FOnXmppPresenceReceived& OnReceivePresence() override`
- L42 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L45 _protected prototype_ `void OnPresenceUpdate(TUniquePtr<FXmppUserPresence>&& UpdatedPresence);`
- L48 _protected prototype_ `void CleanupMessages();` — Remove pending messages and engine KeepAwake calls
- L52 _protected member_ `FXmppConnectionStrophe& ConnectionManager;` — Connection manager controls sending data to XMPP thread
- L55 _protected member_ `FXmppUserPresence CachedPresence;` — Local user's Presence information
- L58 _protected member_ `TMap<FString, TSharedRef<FXmppUserPresence>> RosterMembers;` — Presence information for players on our roster
- L61 _protected member_ `TQueue<TUniquePtr<FXmppUserPresence>> IncomingPresenceUpdates;` — Queue of stanzas needing to be processed on the game thread
- L64 _protected member_ `FOnXmppPresenceReceived OnXmppPresenceReceivedDelegate;` — Delegate to signal presence information has been received for a user

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/XmppPrivateChatStrophe.h` (Private)


#### class `FXmppPrivateChatStrophe`  
`class FXmppPrivateChatStrophe : public IXmppChat , public FTSTickerObjectBase`  
_L17-60_
- inherits: `IXmppChat,FTSTickerObjectBase`
- L25 _public prototype_ `FXmppPrivateChatStrophe(FXmppConnectionStrophe& InConnectionManager);` — FXmppPrivateChatStrophe
- L26 _public prototype_ `virtual ~FXmppPrivateChatStrophe();`
- L29 _public prototype_ `bool ReceiveStanza(const FStropheStanza& IncomingStanza);` — XMPP Thread
- L32 _public prototype_ `void OnDisconnect();` — Game Thread
- L33 _public prototype_ `void OnReconnect();`
- L36 _public prototype_ `virtual bool SendChat(const FXmppUserJid& RecipientId, const FString& Message) override;` — IXmppChat
- L37 _public function_ `virtual FOnXmppChatReceived& OnReceiveChat() override`
- L40 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L43 _protected prototype_ `void OnChatReceived(TUniquePtr<FXmppChatMessage>&& Chat);`
- L46 _protected prototype_ `void CleanupMessages();` — Remove pending messages and engine KeepAwake calls
- L50 _protected member_ `FXmppConnectionStrophe& ConnectionManager;` — Connection manager controls sending data to XMPP thread
- L56 _protected member_ `TQueue<TUniquePtr<FXmppChatMessage>> IncomingChatMessages;` — Queue of Chat Messages needing to be consumed. These are Queued on the XMPP thread, and Dequeued on the Game thread
- L59 _protected member_ `FOnXmppChatReceived OnChatReceivedDelegate;` — Delegate for game to listen to Chat Messages

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/XmppPubSubStrophe.h` (Private)


#### class `FXmppPubSubStrophe`  
`class FXmppPubSubStrophe : public IXmppPubSub , public FTSTickerObjectBase`  
_L15-69_
- inherits: `IXmppPubSub,FTSTickerObjectBase`
- L21 _public prototype_ `FXmppPubSubStrophe(class FXmppConnectionStrophe& InConnectionManager);` — FXmppPubSubStrophe
- L22 _public prototype_ `virtual ~FXmppPubSubStrophe() = default;`
- L25 _public prototype_ `bool ReceiveStanza(const FStropheStanza& IncomingStanza);` — XMPP Thread
- L28 _public prototype_ `void OnDisconnect();` — Game Thread
- L29 _public prototype_ `void OnReconnect();`
- L32 _public prototype_ `virtual bool CreateNode(const FXmppPubSubId& NodeId, const FXmppPubSubConfig& NodeConfig) override;` — IXmppPubSub
- L33 _public prototype_ `virtual bool ConfigureNode(const FXmppPubSubId& NodeId, const FXmppPubSubConfig& NodeConfig) override;`
- L34 _public prototype_ `virtual bool DestroyNode(const FXmppPubSubId& NodeId) override;`
- L35 _public prototype_ `virtual bool QueryNode(const FXmppPubSubId& NodeId) override;`
- L36 _public prototype_ `virtual bool QuerySubscriptions() override;`
- L37 _public prototype_ `virtual bool Subscribe(const FXmppPubSubId& NodeId) override;`
- L38 _public prototype_ `virtual bool Unsubscribe(const FXmppPubSubId& NodeId) override;`
- L39 _public prototype_ `virtual bool PublishMessage(const FXmppPubSubId& NodeId, const FXmppPubSubMessage& Message) override;`
- L40 _public prototype_ `virtual TArray<FXmppPubSubId> GetOwnedNodes() const override;`
- L41 _public prototype_ `virtual TArray<FXmppPubSubId> GetSubscribedNodes() const override;`
- L42 _public prototype_ `virtual TSharedPtr<FXmppPubSubNode> GetNodeInfo(const FXmppPubSubId& NodeId) const override;`
- L43 _public prototype_ `virtual bool GetLastMessages(const FXmppPubSubId& NodeId, int32 NumMessages, TArray<TSharedRef<FXmppPubSubMessage>>& OutMessages) const override;`
- L45 _public function_ `virtual FOnXmppPubSubCreateNodeComplete& OnCreateNodeComplete() override`
- L46 _public function_ `virtual FOnXmppPubSubConfigureNodeComplete& OnConfigureNodeComplete() override`
- L47 _public function_ `virtual FOnXmppPubSubDestroyNodeComplete& OnDestroyNodeComplete() override`
- L48 _public function_ `virtual FOnXmppPubSubQueryNodeComplete& OnQueryNodeComplete() override`
- L49 _public function_ `virtual FOnXmppPubSubQuerySubscriptionsComplete& OnQuerySubscriptionsComplete() override`
- L50 _public function_ `virtual FOnXmppPubSubSubscribed& OnSubscribed() override`
- L51 _public function_ `virtual FOnXmppPubSubUnsubscribed& OnUnsubscribed() override`
- L52 _public function_ `virtual FOnXmppPubSubMessageReceived& OnMessageReceived() override`
- L55 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L59 _protected member_ `FXmppConnectionStrophe& ConnectionManager;` — Connection manager controls sending data to XMPP thread
- L61 _protected member_ `FOnXmppPubSubCreateNodeComplete OnXmppPubSubCreateNodeCompleteDelegate;`
- L62 _protected member_ `FOnXmppPubSubConfigureNodeComplete OnXmppPubSubConfigureNodeCompleteDelegate;`
- L63 _protected member_ `FOnXmppPubSubDestroyNodeComplete OnXmppPubSubDestroyNodeCompleteDelegate;`
- L64 _protected member_ `FOnXmppPubSubQueryNodeComplete OnXmppPubSubQueryNodeCompleteDelegate;`
- L65 _protected member_ `FOnXmppPubSubQuerySubscriptionsComplete OnXmppPubSubQuerySubscriptionsCompleteDelegate;`
- L66 _protected member_ `FOnXmppPubSubSubscribed OnXmppPubSubSubscribedDelegate;`
- L67 _protected member_ `FOnXmppPubSubUnsubscribed OnXmppPubSubUnsubscribedDelegate;`
- L68 _protected member_ `FOnXmppPubSubMessageReceived OnXmppPubSubMessageReceivedDelegate;`

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/XmppStrophe.h` (Private)


#### class `FXmppStrophe`  
`class FXmppStrophe`  
_L15-27_
- desc: Entry for access to Xmpp connections implemented via libstrophe
- L19 _public prototype_ `static void Init();` — FXmppStrophe
- L20 _public prototype_ `static void Cleanup();`
- L21 _public prototype_ `static TSharedRef<IXmppConnection> CreateConnection();`
- L23 _public prototype_ `static FString JidToString(const FXmppUserJid& UserJid);`
- L25 _public prototype_ `static FXmppUserJid JidFromString(const FString& JidString);`
- L26 _public prototype_ `static FXmppUserJid JidFromStropheString(const char* StropheJidPtr);`

### `Source/Runtime/Online/XMPP/Private/XmppStrophe/XmppStropheThread.h` (Private)


#### class `FXmppStropheThread`  
`class FXmppStropheThread : public FRunnable`  
_L19-60_
- inherits: `FRunnable`
- L24 _public prototype_ `explicit FXmppStropheThread(FXmppConnectionStrophe& InConnectionManager, const FXmppUserJid& InUser, const FString& InAuth, const FXmppServer& InServerConfiguration);` — FXmppStropheThread
- L25 _public prototype_ `virtual ~FXmppStropheThread();`
- L27 _public prototype_ `bool SendStanza(FStropheStanza&& Stanza);`
- L30 _public prototype_ `virtual bool Init() override;` — FRunnable
- L31 _public prototype_ `virtual uint32 Run() override;`
- L32 _public prototype_ `virtual void Stop() override;`
- L33 _public prototype_ `virtual void Exit() override;`
- L36 _protected prototype_ `void SendQueuedStanza();`
- L40 _protected member_ `FXmppConnectionStrophe& ConnectionManager;` — Connection Manager
- L43 _protected member_ `FStropheConnection StropheConnection;` — Strophe Connection
- L46 _protected member_ `const FXmppServer& ServerConfiguration;` — Server Configuration to use for this connection
- L49 _protected member_ `TUniquePtr<FRunnableThread> ThreadPtr;` — Our runnable thread to be cleaned up before we're destroyed
- L52 _protected member_ `TQueue<TUniquePtr<FStropheStanza>> StanzaSendQueue;` — Queue of stanzas needing to be sent
- L55 _protected member_ `FThreadSafeBool bConnectRequest;` — signal request for connection
- L57 _protected member_ `FThreadSafeBool bDisconnectRequest;` — signal request for disconnect
- L59 _protected member_ `FThreadSafeBool bExitRequested;` — Thread-Safe way to trigger a thread exit

### `Source/Runtime/Online/XMPP/Private/XmppTests.h` (Private)


#### class `FXmppTest`  
`class FXmppTest`  
_L16-61_
- desc: Create a new Xmpp connection And run some basic tests for login/presence/pubsub/chat
- L23 _public prototype_ `FXmppTest();` — Constructor
- L28 _public prototype_ `virtual ~FXmppTest() = default;` — Destructor
- L33 _public prototype_ `void Test(const FString& UserId, const FString& Password, const FXmppServer& XmppServer);` — Kicks off all of the testing process
- L40 _private prototype_ `void StartNextTest();` — Step through the various tests that should be run and initiate the next one
- L45 _private prototype_ `void FinishTest();` — Finish/cleanup the tests
- L48 _private member_ `bool bRunBasicPresenceTest;` — tests to run
- L49 _private member_ `bool bRunPubSubTest;`
- L50 _private member_ `bool bRunChatTest;`
- L52 _private member_ `TSharedPtr<IXmppConnection> XmppConnection;`
- L55 _private prototype_ `void OnLoginComplete(const FXmppUserJid& UserJid, bool bWasSuccess, const FString& Error);` — completion delegates
- L56 _private prototype_ `void OnLogoutComplete(const FXmppUserJid& UserJid, bool bWasSuccess, const FString& Error);`
- L59 _private member_ `FDelegateHandle OnLoginCompleteHandle;` — Handles for the registered delegates
- L60 _private member_ `FDelegateHandle OnLogoutCompleteHandle;`

### `Source/Runtime/Online/XMPP/Public/Xmpp.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/Online/XMPP/Public/XmppChat.h` (Public)


#### class `FXmppChatMessage`  
`class FXmppChatMessage`  
_L11-27_
- desc: Chat message received from another Xmpp user
- L15 _public function_ `FXmppChatMessage() : Timestamp(0)` — constructor
- L20 _public member_ `FXmppUserJid FromJid;` — id of message sender
- L22 _public member_ `FXmppUserJid ToJid;` — id of message recipient
- L24 _public member_ `FString Body;` — body of the message
- L26 _public member_ `FDateTime Timestamp;` — server provided timestamp for message

#### class `IXmppChat`  
`class IXmppChat`  
_L32-59_
- desc: Interface for sending/receiving chat messages between users
- L37 _public prototype_ `virtual ~IXmppChat() = default;` — destructor
- L47 _public prototype_ `virtual bool SendChat(const FXmppUserJid& RecipientId, const FString& Message) = 0;` — Send a chat to a user via xmpp service @param RecipientId user to send chat to (must be online) @param Message chat message to send @return true if successfully sent
- L56 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppChatReceived, const TSharedRef<IXmppConnection>& , const FXmppUserJid& , const TSharedRef<FXmppChatMessage>& );` — Delegate callback for when a new chat message is received @param Connection the xmpp connection that received the chat @param FromId id of user that sent the chat @param Chat data that was received
- L58 _public prototype_ `virtual FOnXmppChatReceived& OnReceiveChat() = 0;` — @return chat received delegate

#### Free symbols / members of external scopes

- L56 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppChatReceived, const TSharedRef<IXmppConnection>& , const FXmppUserJid& , const TSharedRef<FXmppChatMessage>& );` — Delegate callback for when a new chat message is received @param Connection the xmpp connection that received the chat @param FromId id of user that sent the chat @param Chat data that was received

### `Source/Runtime/Online/XMPP/Public/XmppConnection.h` (Public)


#### enum `EXmppLoginStatus::Type`  
`enum Type`  
_L20-27_
- L22 _public enumerator_ `NotStarted`
- L23 _public enumerator_ `ProcessingLogin`
- L24 _public enumerator_ `ProcessingLogout`
- L25 _public enumerator_ `LoggedIn`
- L26 _public enumerator_ `LoggedOut`

#### class `FXmppServer`  
`class FXmppServer`  
_L51-93_
- desc: Info needed for connecting to an XMPP server
- L54 _public function_ `FXmppServer() : ServerPort(5222) , bUseSSL(true) , bUsePlainTextAuth(false) , PingInterval(60.0f) , PingTimeout(30.0f) , MaxPingRetries(1) , bPrivateChatFriendsOnly(false) , bResetPingTimeoutOnReceiveStanza(true)`
- L66 _public member_ `FString ServerAddr;` — ip/host to connect to
- L68 _public member_ `int32 ServerPort;` — port number 5222 typically
- L70 _public member_ `FString PlatformUserId;` — Platform user id, if applicable
- L72 _public member_ `FString Domain;` — domain for user jid
- L74 _public member_ `FString ClientResource;` — client id user is logging in from (constructed from other fields)
- L76 _public member_ `FString AppId;` — app id associated with this client
- L78 _public member_ `FString Platform;` — platform the player is using
- L80 _public member_ `bool bUseSSL;` — true to enable SSL handshake for connection
- L82 _public member_ `bool bUsePlainTextAuth;` — true to allow the usage of plain text authentication
- L84 _public member_ `float PingInterval;` — seconds between sending server ping requests
- L86 _public member_ `float PingTimeout;` — seconds before a server ping request is treated as a timeout
- L88 _public member_ `int32 MaxPingRetries;` — max number of retries on ping timeout before connection is abandoned and logged out
- L90 _public member_ `bool bPrivateChatFriendsOnly;` — limit private chat to friends only
- L92 _public member_ `bool bResetPingTimeoutOnReceiveStanza;` — reset ping timeout on received stanzas

#### class `FXmppUserJid`  
`class FXmppUserJid`  
_L98-206_
- desc: Jid for identifying user on the current connection as well as roster members
- L102 _public function_ `explicit FXmppUserJid( FString InId = FString(), FString InDomain = FString(), FString InResource = FString() ) : Id(MoveTemp(InId)) , Domain(MoveTemp(InDomain)) , Resource(MoveTemp(InResource))`
- L120 _public prototype_ `static FXmppUserJid FromFullJid(const FString& JidString);` — Create an FXmppUserJid from a formatted JID e.g., user@domain/resource @param JidString the formatted JID @return FXmppUserJid populated from the formatted JID
- L123 _public member_ `FString Id;` — unique id for the user
- L125 _public member_ `FString Domain;` — domain user has access to
- L127 _public member_ `FString Resource;` — client resource user is logged in from
- L139 _public prototype_ `static bool ParseResource(const FString& InResource, FString& OutAppId, FString& OutPlatform, FString& OutPlatformUserId);` — Get the components that comprise the resource @param InResource The resource to parse @param OutAppId The app id the user is using @param OutPlatform The platform the user is using @param OutPlatformUserId The platform user id (optional) @return Whether the Resource was successfully parsed or not
- L141 _public prototype_ `static FString CreateResource(const FString& AppId, const FString& Platform, const FString& PlatformUserId);`
- L152 _public function_ `bool ParseResource(FString& OutAppId, FString& OutPlatform, FString& OutPlatformUserId) const` — Get the components that comprise the resource @param OutAppId The app id the user is using @param OutPlatform The platform the user is using @param OutPlatformUserId The platform user id (optional) @return Whether the Resource was successfully parsed or not
- L161 _public prototype_ `static FString ParseMucUserResource(const FString& InResource);` — Separate the MUC half of the resource (nickname:userid) from the UserJid resource portion (Vx:AppId:Platform:etc) This is highly dependent on FChatRoomMemberMcp::BuildMemberJidResourceString
- L163 _public function_ `bool operator==(const FXmppUserJid& Other) const`
- L171 _public function_ `bool operator!=(const FXmppUserJid& Other) const`
- L177 _public function_ `FString GetFullPath() const` — full jid path <id@domain/resource>
- L194 _public function_ `FString GetBareId() const` — Return Bare id (id@domain)
- L200 _public function_ `bool IsValid() const` — @return true if jid has all valid elements
- L205 _public prototype_ `FString ToDebugString() const;`

#### class `IXmppConnection`  
`class IXmppConnection : public TSharedFromThis<IXmppConnection>`  
_L217-336_
- inherits: `TSharedFromThis<IXmppConnection>`
- desc: Base interface for connecting to Xmpp
- L223 _public prototype_ `virtual ~IXmppConnection() = default;` — destructor
- L230 _public prototype_ `virtual void SetServer(const FXmppServer& Server) = 0;` — Configure the connection with server details @param Server server details
- L237 _public prototype_ `virtual const FXmppServer& GetServer() const = 0;` — Obtain last server details associated with the connection @return Server server details
- L246 _public prototype_ `virtual void Login(const FString& UserId, const FString& Auth) = 0;` — Login on the connection. No socket connection is created until user attempts to login See OnLoginComplete(), OnLoginChanged() delegates for completion @param UserId just the id portion of the jid (domain is in server config) @param Auth plain text auth credentials for user
- L253 _public prototype_ `virtual void Logout() = 0;` — Logout on the connection with a user that has previously logged in. This will close the socket connection and cleanup. See OnLogoutComplete(), OnLoginChanged() delegates for completion
- L260 _public prototype_ `virtual EXmppLoginStatus::Type GetLoginStatus() const = 0;` — Obtain currently cached login status @return EXmppLoginStatus based on logged in and socket connection state
- L268 _public prototype_ `virtual const FXmppUserJid& GetUserJid() const = 0;` — Get the jid of the last user login attempt Note that they may be logged out @param jid to identify user
- L277 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppLoginComplete, const FXmppUserJid& , bool , const FString& );` — Delegate called when login completes @param UserJid jid of user that attempted to login @param bWasSuccess true if successfully logged in user, false otherwise @param Error string representing error or empty if success
- L286 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppLogoutComplete, const FXmppUserJid& , bool , const FString& );` — Delegate called when logout completes @param UserJid jid of user that logged out @param bWasSuccess true if successfully logged out, false otherwise @param Error string representing error or empty if success
- L294 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnXmppLoginChanged, const FXmppUserJid& , EXmppLoginStatus::Type );` — Delegate called when login completes @param UserJid jid of user that changed login state @param LoginState new login state (see EXmppLoginStatus)
- L297 _public typedef_ `using FOnXmppLogingChanged UE_DEPRECATED(4.23, "Please update usages of '` — Alias for old typo, remove in 4.24
- L303 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnXmppStanzaReceived, const IXmppStanza& );` — Delegate called when a message is received (ONLY STROPHE) @param reference to stanza
- L310 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnXmppStanzaSent, const IXmppStanza& );` — Delegate called when a message is sent (ONLY STROPHE) @param reference to stanza
- L313 _public prototype_ `virtual FOnXmppLoginComplete& OnLoginComplete() = 0;` — @return login complete delegate
- L315 _public prototype_ `virtual FOnXmppLoginChanged& OnLoginChanged() = 0;` — @return login changed delegate
- L317 _public prototype_ `virtual FOnXmppLogoutComplete& OnLogoutComplete() = 0;` — @return logout complete delegate
- L319 _public prototype_ `virtual FOnXmppStanzaSent& OnStanzaSent() = 0;` — @return Stanza sent delegate
- L321 _public prototype_ `virtual FOnXmppStanzaReceived& OnStanzaReceived() = 0;` — @return Stanza received delegate
- L324 _public prototype_ `virtual IXmppPresencePtr Presence() = 0;` — @return Presence interface if available. NULL otherwise
- L326 _public prototype_ `virtual IXmppPubSubPtr PubSub() = 0;` — @return PubSub interface if available. NULL otherwise
- L328 _public prototype_ `virtual IXmppMessagesPtr Messages() = 0;` — @return Messages interface if available. NULL otherwise
- L330 _public prototype_ `virtual IXmppMultiUserChatPtr MultiUserChat() = 0;` — @return MultiUserChat interface if available. NULL otherwise
- L332 _public prototype_ `virtual IXmppChatPtr PrivateChat() = 0;` — @return PrivateChat interface if available. NULL otherwise
- L335 _public prototype_ `virtual void DumpState() const = 0;` — Debug dump of this connection

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace EXmppLoginStatus`
- L29 _function_ `inline const TCHAR* ToString(EXmppLoginStatus::Type EnumVal)` (scope `EXmppLoginStatus`)
- L208 _typedef_ `typedef TSharedPtr<IXmppPresence, ESPMode::ThreadSafe> IXmppPresencePtr;`
- L209 _typedef_ `typedef TSharedPtr<IXmppPubSub, ESPMode::ThreadSafe> IXmppPubSubPtr;`
- L210 _typedef_ `typedef TSharedPtr<IXmppMessages, ESPMode::ThreadSafe> IXmppMessagesPtr;`
- L211 _typedef_ `typedef TSharedPtr<IXmppMultiUserChat, ESPMode::ThreadSafe> IXmppMultiUserChatPtr;`
- L212 _typedef_ `typedef TSharedPtr<IXmppChat, ESPMode::ThreadSafe> IXmppChatPtr;`
- L277 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppLoginComplete, const FXmppUserJid& , bool , const FString& );` — Delegate called when login completes @param UserJid jid of user that attempted to login @param bWasSuccess true if successfully logged in user, false otherwise @param Error string representing error or empty if success
- L286 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppLogoutComplete, const FXmppUserJid& , bool , const FString& );` — Delegate called when logout completes @param UserJid jid of user that logged out @param bWasSuccess true if successfully logged out, false otherwise @param Error string representing error or empty if success
- L294 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnXmppLoginChanged, const FXmppUserJid& , EXmppLoginStatus::Type );` — Delegate called when login completes @param UserJid jid of user that changed login state @param LoginState new login state (see EXmppLoginStatus)
- L303 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnXmppStanzaReceived, const IXmppStanza& );` — Delegate called when a message is received (ONLY STROPHE) @param reference to stanza
- L310 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnXmppStanzaSent, const IXmppStanza& );` — Delegate called when a message is sent (ONLY STROPHE) @param reference to stanza

### `Source/Runtime/Online/XMPP/Public/XmppMessages.h` (Public)


#### class `FXmppMessage`  
`class FXmppMessage`  
_L11-28_
- desc: Message received from Xmpp user/admin
- L15 _public function_ `FXmppMessage()` — constructor
- L19 _public member_ `FXmppUserJid FromJid;` — id of message sender
- L21 _public member_ `FXmppUserJid ToJid;` — id of message recipient
- L23 _public member_ `FString Payload;` — body of the message
- L25 _public member_ `FString Type;` — type of the message
- L27 _public member_ `FDateTime Timestamp;` — date sent

#### class `IXmppMessages`  
`class IXmppMessages`  
_L33-62_
- desc: Interface for sending/receiving messages between users (also admin to user notifications)
- L38 _public prototype_ `virtual ~IXmppMessages() = default;` — destructor
- L49 _public prototype_ `virtual bool SendMessage(const FXmppUserJid& RecipientId, const FString& Type, const FString& Payload, bool bPayloadIsSerializedJson = false) = 0;` — Send a message to a user via xmpp service @param RecipientId user to send message to (must be online) @param Type message type @param Payload message data to send @return true if successfully sent
- L50 _public prototype_ `virtual bool SendMessage(const FXmppUserJid& RecipientId, const FString& Type, const TSharedRef<class FJsonObject>& Payload) = 0;`
- L59 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppMessageReceived, const TSharedRef<IXmppConnection>& , const FXmppUserJid& , const TSharedRef<FXmppMessage>& );` — Delegate callback for when a new message is received @param Connection the xmpp connection this message was received on @param FromId id of user that sent the message (might be admin) @param Message data that was received
- L61 _public prototype_ `virtual FOnXmppMessageReceived& OnReceiveMessage() = 0;` — @return message received delegate

#### Free symbols / members of external scopes

- L59 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppMessageReceived, const TSharedRef<IXmppConnection>& , const FXmppUserJid& , const TSharedRef<FXmppMessage>& );` — Delegate callback for when a new message is received @param Connection the xmpp connection this message was received on @param FromId id of user that sent the message (might be admin) @param Message data that was received

### `Source/Runtime/Online/XMPP/Public/XmppModule.h` (Public)


#### class `FXmppModule`  
`class FXmppModule : public IModuleInterface, public FSelfRegisteringExec, public FTSTickerObjectBase`  
_L28-178_
- inherits: `IModuleInterface,FSelfRegisteringExec,FTSTickerObjectBase`
- desc: Module for Xmpp connections Use CreateConnection to create a new Xmpp connection
- L45 _protected prototype_ `virtual bool Exec_Runtime(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — Handle exec commands starting with "XMPP" @param InWorld	the world context @param Cmd		the exec command being executed @param Ar		the archive to log results to @return true if the handler consumed the input, false to continue searching handlers
- L52 _public prototype_ `bool HandleXmppCommand( const TCHAR* Cmd, FOutputDevice& Ar );` — Exec command handlers
- L62 _public prototype_ `static FXmppModule& Get();` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L69 _public prototype_ `static bool IsAvailable();` — Checks to see if this module is loaded and ready. @return True if the module is loaded and ready to use
- L76 _public prototype_ `TSharedRef<class IXmppConnection> CreateConnection(const FString& UserId);` — Creates a new Xmpp connection for the current platform and associated it with the user @return new Xmpp connection instance
- L83 _public prototype_ `TSharedPtr<class IXmppConnection> GetConnection(const FString& UserId) const;` — Return an existing Xmpp connection associated with a user @return new Xmpp connection instance
- L90 _public prototype_ `void RemoveConnection(const FString& UserId);` — Remove an existing Xmpp connection associated with a user @param UserId user to find connection for
- L95 _public prototype_ `void ProcessPendingRemovals();` — Clean up any pending connection removals
- L102 _public prototype_ `void RemoveConnection(const TSharedRef<class IXmppConnection>& Connection);` — Remove an existing Xmpp connection @param Connection reference to find/remove
- L107 _public function_ `inline bool IsXmppEnabled() const` — @return true if Xmpp requests are globally enabled
- L113 _public prototype_ `virtual bool Tick(float DeltaTime) override;` — FTSTickerObjectBase
- L121 _public prototype_ `DECLARE_EVENT_TwoParams(FXmppModule, FOnXmppConnectionAcquired, const TSharedRef<IXmppConnection>& , const FString& );` — Delegate callback when a system acquires ownership over an XMPP connection @param XmppConnection The connection that is acquired @param SystemName The name of the system initiating this request
- L122 _public member_ `FOnXmppConnectionAcquired OnXmppConnectionAcquired;`
- L130 _public prototype_ `DECLARE_EVENT_TwoParams(FXmppModule, FOnXmppConnectionRelinquished, const TSharedRef<IXmppConnection>& , const FString& );` — Delegate callback when a system relinquishes ownership of an XMPP connection @param XmppConnection The connection that is relinquished @param SystemName The name of the system initiating this request
- L131 _public member_ `FOnXmppConnectionRelinquished OnXmppConnectionRelinquished;`
- L139 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnXmppConnectionCreated, const TSharedRef<IXmppConnection>& );` — Delegate fired when an Xmpp connection is created. @param NewConnection Reference to newly created Xmpp connection
- L140 _public member_ `FOnXmppConnectionCreated OnXmppConnectionCreated;`
- L147 _private prototype_ `void OnXmppRoomCreated(const TSharedRef<IXmppConnection>& Connection, bool bSuccess, const FXmppRoomId& RoomId, const FString& Error);`
- L148 _private prototype_ `void OnXmppRoomConfigured(const TSharedRef<IXmppConnection>& Connection, bool bSuccess, const FXmppRoomId& RoomId, const FString& Error);`
- L154 _private prototype_ `virtual void StartupModule() override;` — Called when Xmpp module is loaded Initialize platform specific parts of Xmpp handling
- L160 _private prototype_ `virtual void ShutdownModule() override;` — Called when Xmpp module is unloaded Shutdown platform specific parts of Xmpp handling
- L165 _private prototype_ `void CleanupConnection(const TSharedRef<class IXmppConnection>& Connection);` — Connection cleanup before removal
- L168 _private member_ `bool bEnabled;` — toggles Xmpp requests
- L170 _private member_ `static FXmppModule* Singleton;` — singleton for the module while loaded and available
- L173 _private member_ `TMap<FString, TSharedRef<class IXmppConnection>> ActiveConnections;` — Active Xmpp server connections mapped by user id
- L175 _private member_ `TSet<TSharedPtr<IXmppConnection>> PendingRemovals;` — Xmpp connections pending removal on next tick
- L177 _private member_ `TArray<TSharedRef<class IXmppConnection>> PendingDeleteConnections;` — Keep track of removed connections pending cleanup

#### Free symbols / members of external scopes

- L121 _delegate_ `DECLARE_EVENT_TwoParams(FXmppModule, FOnXmppConnectionAcquired, const TSharedRef<IXmppConnection>& , const FString& );` — Delegate callback when a system acquires ownership over an XMPP connection @param XmppConnection The connection that is acquired @param SystemName The name of the system initiating this request
- L130 _delegate_ `DECLARE_EVENT_TwoParams(FXmppModule, FOnXmppConnectionRelinquished, const TSharedRef<IXmppConnection>& , const FString& );` — Delegate callback when a system relinquishes ownership of an XMPP connection @param XmppConnection The connection that is relinquished @param SystemName The name of the system initiating this request
- L139 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnXmppConnectionCreated, const TSharedRef<IXmppConnection>& );` — Delegate fired when an Xmpp connection is created. @param NewConnection Reference to newly created Xmpp connection

### `Source/Runtime/Online/XMPP/Public/XmppMultiUserChat.h` (Public)


#### enum `EXmppChatMemberAffiliation::Type`  
`enum Type`  
_L22-35_
- L25 _public enumerator_ `Owner` — Owner of the room
- L27 _public enumerator_ `Admin` — An admin or owner enters a room as a moderator
- L30 _public enumerator_ `Member` — As a default, an unaffiliated user enters a moderated room as a visitor, and enters an open room as a participant.
- L32 _public enumerator_ `Outcast` — Banned from the room
- L34 _public enumerator_ `None` — Absence of an affiliation

#### enum `EXmppChatMemberRole::Type`  
`enum Type`  
_L87-96_
- L90 _public enumerator_ `Moderator` — A moderator is the most powerful role within the context of the room, and can to some extent manage other occupants' roles in the room.
- L92 _public enumerator_ `Participant` — A participant has fewer privileges than a moderator, although they always have the right to speak.
- L94 _public enumerator_ `Visitor` — A visitor is a more restricted role within the context of a moderated room
- L95 _public enumerator_ `None`

#### class `FXmppChatMember`  
`class FXmppChatMember`  
_L138-183_
- desc: Member of a chat room
- L141 _public function_ `FXmppChatMember() : Affiliation(EXmppChatMemberAffiliation::None) , Role(EXmppChatMemberRole::None)`
- L146 _public function_ `explicit FXmppChatMember(const FXmppMucPresence& MemberPresence) : Nickname(MemberPresence.GetNickName()) , RoomMemberJid(MemberPresence.UserJid) , UserJid(MemberPresence.MemberJid) , UserPresence(MemberPresence) , Affiliation(EXmppChatMemberAffiliation::ToType(MemberPresence.Affiliation)) , Role(EXmppChatMemberRole::ToType(MemberPresence.Role))`
- L157 _public member_ `FString Nickname;` — Nickname of the user
- L163 _public member_ `FXmppUserJid RoomMemberJid;` — JID of the member for the chat room Use this to identify the user in the chat room (such as iterating the chat room's members) ex: RoomId@MucDomain/MemberMucResource
- L170 _public member_ `FXmppUserJid UserJid;` — JID of the member outside of the chat room, if the room is non-anonymous. May be blank. Use this to identify the user outside of the chat room (such as private messages) ex: AccountId@Domain/Resource @see https://xmpp.org/extensions/xep-0045.html#enter-nonanon
- L172 _public member_ `FXmppUserPresence UserPresence;` — Presence of the member
- L174 _public member_ `EXmppChatMemberAffiliation::Type Affiliation;` — Affiliation of the member in the chat room
- L176 _public member_ `EXmppChatMemberRole::Type Role;` — Role of the member in the chat room
- L179 _public function_ `FString ToDebugString() const` — @return string representation of this object suitable for logging

#### class `FXmppRoomInfo`  
`class FXmppRoomInfo`  
_L191-207_
- desc: Info for a joined/created chat room
- L194 _public function_ `FXmppRoomInfo() : bIsPrivate(false)`
- L198 _public member_ `FXmppRoomId Id;`
- L199 _public member_ `FString OwnerId;`
- L200 _public member_ `FString Subject;`
- L201 _public member_ `bool bIsPrivate;`
- L203 _public function_ `FString ToDebugString() const`

#### class `FXmppRoomConfig`  
`class FXmppRoomConfig`  
_L212-288_
- desc: Info to configure a new room
- L215 _public function_ `FXmppRoomConfig() : RoomName(TEXT("")) , RoomDesc(TEXT("")) , bIsPrivate(true) , Password(TEXT("")) , bIsPersistent(false) , bAllowPublicSearch(false) , bIsModerated(false) , bIsMembersOnly(false) , bAllowChangeSubject(false) , MaxMsgHistory(0) , RoomAnonymity(ERoomAnonymity::Semianonymous)`
- L236 _public function_ `static const FString ConvertRoomAnonymityToString(ERoomAnonymity InRoomAnonymity)`
- L257 _public member_ `FString RoomName;` — <field type = "text-single" label = "Natural-Language Room Name" var = "muc#roomconfig_roomname">
- L259 _public member_ `FString RoomDesc;` — <field type = "text-single" label = "Short Description of Room" var = "muc#roomconfig_roomdesc">
- L261 _public member_ `bool bIsPrivate;` — <field type = "boolean" label = "Password Required to Enter?" var = "muc#roomconfig_passwordprotectedroom">
- L263 _public member_ `FString Password;` — <field type = "text-single" label = "Password" var = "muc#roomconfig_roomsecret">
- L265 _public member_ `bool bIsPersistent;` — <field type = "boolean" label = "Make Room Persistent?" var = "muc#roomconfig_persistentroom">
- L270 _private member_ `bool bAllowPublicSearch;` — These fields are not used yet.  Move to public when hooking up <field type = "boolean" label = "Make Room Publicly Searchable?" var = "muc#roomconfig_publicroom">
- L272 _private member_ `bool bIsModerated;` — <field type = "boolean" label = "Make Room Moderated?" var = "muc#roomconfig_moderatedroom">
- L274 _private member_ `bool bIsMembersOnly;` — <field type = "boolean" label = "Make Room Members Only?" var = "muc#roomconfig_membersonly">
- L276 _private member_ `bool bAllowChangeSubject;` — <field type = "boolean" label = "Allow Occupants to Change Subject?" var = "muc#roomconfig_changesubject">
- L278 _private member_ `int32 MaxMsgHistory;` — <field type = "text-single" label = "Maximum Number of History Messages Returned by Room" var = "muc#maxhistoryfetch">
- L280 _private member_ `ERoomAnonymity RoomAnonymity;` — <field type = "list-single" label = "Room anonymity level:" var = "muc#roomconfig_anonymity">

#### enum `FXmppRoomConfig::ERoomAnonymity`  
`enum class ERoomAnonymity`  
_L229-234_
- L231 _public enumerator_ `Semianonymous`
- L232 _public enumerator_ `Nonanonymous`
- L233 _public enumerator_ `Fullanonymous`

#### class `IXmppMultiUserChat`  
`class IXmppMultiUserChat`  
_L293-361_
- desc: Interface for creating/joining/chatting in a MUC
- L297 _public prototype_ `virtual ~IXmppMultiUserChat() = default;`
- L299 _public prototype_ `virtual bool CreateRoom(const FXmppRoomId& RoomId, const FString& Nickname, const FXmppRoomConfig& RoomConfig = FXmppRoomConfig()) = 0;`
- L300 _public prototype_ `virtual bool ConfigureRoom(const FXmppRoomId& RoomId, const FXmppRoomConfig& RoomConfig) = 0;`
- L301 _public prototype_ `virtual bool JoinPublicRoom(const FXmppRoomId& RoomId, const FString& Nickname) = 0;`
- L302 _public prototype_ `virtual bool JoinPrivateRoom(const FXmppRoomId& RoomId, const FString& Nickname, const FString& Password) = 0;`
- L303 _public prototype_ `virtual bool RegisterMember(const FXmppRoomId& RoomId, const FString& Nickname) = 0;`
- L304 _public prototype_ `virtual bool UnregisterMember(const FXmppRoomId& RoomId, const FString& Nickname) = 0;`
- L305 _public prototype_ `virtual bool ExitRoom(const FXmppRoomId& RoomId) = 0;`
- L306 _public prototype_ `virtual bool SendChat(const FXmppRoomId& RoomId, const FString& MsgBody, const FString& ChatInfo) = 0;`
- L307 _public prototype_ `virtual void GetJoinedRooms(TArray<FXmppRoomId>& OutRooms) = 0;`
- L308 _public prototype_ `virtual bool RefreshRoomInfo(const FXmppRoomId& RoomId) = 0;`
- L309 _public prototype_ `virtual bool GetRoomInfo(const FXmppRoomId& RoomId, FXmppRoomInfo& OutRoomInfo) = 0;`
- L310 _public prototype_ `virtual bool GetMembers(const FXmppRoomId& RoomId, TArray<FXmppChatMemberRef>& OutMembers) = 0;`
- L311 _public prototype_ `virtual FXmppChatMemberPtr GetMember(const FXmppRoomId& RoomId, const FXmppUserJid& MemberJid) = 0;`
- L312 _public prototype_ `virtual bool GetLastMessages(const FXmppRoomId& RoomId, int32 NumMessages, TArray< TSharedRef<FXmppChatMessage> >& OutMessages) = 0;`
- L313 _public prototype_ `virtual void HandleMucPresence(const FXmppMucPresence& MemberPresence) = 0;`
- L314 _public prototype_ `virtual void DumpMultiUserChatState() const = 0;`
- L316 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppRoomCreateComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppRoomId& , const FString& );`
- L318 _public prototype_ `virtual FOnXmppRoomCreateComplete& OnRoomCreated() = 0;` — @return room created delegate
- L320 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppRoomConfigureComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppRoomId& , const FString& );`
- L322 _public prototype_ `virtual FOnXmppRoomConfigureComplete& OnRoomConfigured() = 0;` — @return room configured delegate
- L324 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppRoomInfoRefreshComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppRoomId& , const FString& );`
- L326 _public prototype_ `virtual FOnXmppRoomInfoRefreshComplete& OnRoomInfoRefreshed() = 0;` — @return room refresh delegate
- L328 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppRoomJoinPublicComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppRoomId& , const FString& );`
- L330 _public prototype_ `virtual FOnXmppRoomJoinPublicComplete& OnJoinPublicRoom() = 0;` — @return public room joined delegate
- L332 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppRoomJoinPrivateComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppRoomId& , const FString& );`
- L334 _public prototype_ `virtual FOnXmppRoomJoinPrivateComplete& OnJoinPrivateRoom() = 0;` — @return private room joined delegate
- L336 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppRoomExitComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppRoomId& , const FString& );`
- L338 _public prototype_ `virtual FOnXmppRoomExitComplete& OnExitRoom() = 0;` — @return exit room delegate
- L346 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppRoomMemberJoin, const TSharedRef<IXmppConnection>& , const FXmppRoomId& , const FXmppUserJid& );` — Delegate when a member joins a room @param Connection the XMPP connection @param RoomId the ID of the room that a member joined @param RoomMemberJid the JID the member that joined, used to lookup the member inside of the room
- L348 _public prototype_ `virtual FOnXmppRoomMemberJoin& OnRoomMemberJoin() = 0;` — @return room member joined room delegate
- L350 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppRoomMemberExit, const TSharedRef<IXmppConnection>& , const FXmppRoomId& , const FXmppUserJid& );`
- L352 _public prototype_ `virtual FOnXmppRoomMemberExit& OnRoomMemberExit() = 0;` — @return room member exited room delegate
- L354 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppRoomMemberChanged, const TSharedRef<IXmppConnection>& , const FXmppRoomId& , const FXmppUserJid& );`
- L356 _public prototype_ `virtual FOnXmppRoomMemberChanged& OnRoomMemberChanged() = 0;` — @return room member changed delegate
- L358 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppRoomChatReceived, const TSharedRef<IXmppConnection>& , const FXmppRoomId& , const FXmppUserJid& , const TSharedRef<FXmppChatMessage>& );`
- L360 _public prototype_ `virtual FOnXmppRoomChatReceived& OnRoomChatReceived() = 0;` — @return chat room message received delegate

#### Free symbols / members of external scopes

- L13 _typedef_ `typedef FString FXmppRoomId;` — Id of a chat room
- L20 _namespace_ `namespace EXmppChatMemberAffiliation`
- L37 _function_ `inline const TCHAR* ToString(Type Affiliation)` (scope `EXmppChatMemberAffiliation`)
- L55 _function_ `inline Type ToType(const FString& Affiliation)` (scope `EXmppChatMemberAffiliation`)
- L85 _namespace_ `namespace EXmppChatMemberRole`
- L98 _function_ `inline const TCHAR* ToString(Type Role)` (scope `EXmppChatMemberRole`)
- L114 _function_ `inline Type ToType(const FString& Role)` (scope `EXmppChatMemberRole`)
- L185 _typedef_ `typedef TSharedPtr<FXmppChatMember, ESPMode::ThreadSafe> FXmppChatMemberPtr;`
- L186 _typedef_ `typedef TSharedRef<FXmppChatMember, ESPMode::ThreadSafe> FXmppChatMemberRef;`
- L316 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppRoomCreateComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppRoomId& , const FString& );`
- L320 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppRoomConfigureComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppRoomId& , const FString& );`
- L324 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppRoomInfoRefreshComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppRoomId& , const FString& );`
- L328 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppRoomJoinPublicComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppRoomId& , const FString& );`
- L332 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppRoomJoinPrivateComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppRoomId& , const FString& );`
- L336 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppRoomExitComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppRoomId& , const FString& );`
- L346 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppRoomMemberJoin, const TSharedRef<IXmppConnection>& , const FXmppRoomId& , const FXmppUserJid& );` — Delegate when a member joins a room @param Connection the XMPP connection @param RoomId the ID of the room that a member joined @param RoomMemberJid the JID the member that joined, used to lookup the member inside of the room
- L350 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppRoomMemberExit, const TSharedRef<IXmppConnection>& , const FXmppRoomId& , const FXmppUserJid& );`
- L354 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppRoomMemberChanged, const TSharedRef<IXmppConnection>& , const FXmppRoomId& , const FXmppUserJid& );`
- L358 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppRoomChatReceived, const TSharedRef<IXmppConnection>& , const FXmppRoomId& , const FXmppUserJid& , const TSharedRef<FXmppChatMessage>& );`

### `Source/Runtime/Online/XMPP/Public/XmppPackage.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define PACKAGE_SCOPE public`
- L12 _macro_ `#define PACKAGE_SCOPE private`

### `Source/Runtime/Online/XMPP/Public/XmppPresence.h` (Public)


#### enum `EXmppPresenceStatus::Type`  
`enum Type`  
_L13-27_
- L16 _public enumerator_ `Online` — online while connected
- L18 _public enumerator_ `Offline` — offline if not connected
- L20 _public enumerator_ `Away` — online but away due to being afk or manually set
- L22 _public enumerator_ `ExtendedAway` — online but away for a long period or manually set
- L24 _public enumerator_ `DoNotDisturb` — manually set to avoid interruptions
- L26 _public enumerator_ `Chat` — currently chatting. implies online

#### class `FXmppUserPresence`  
`class FXmppUserPresence`  
_L54-88_
- desc: User presence info obtained from Xmpp roster
- L58 _public member_ `EXmppPresenceStatus::Type Status = EXmppPresenceStatus::Offline;` — state of basic online status
- L60 _public member_ `bool bIsAvailable = true;` — connected an available to receive messages
- L62 _public member_ `FDateTime SentTime = FDateTime::MinValue();` — time when presence was sent by the user
- L64 _public member_ `FDateTime ReceivedTime = FDateTime::MinValue();` — time when presence was sent by the user
- L66 _public member_ `FString AppId;` — app id user is logged in from
- L68 _public member_ `FString Platform;` — platform associated with this client
- L70 _public member_ `FString StatusStr;` — string that will be parsed for further displayed presence info
- L72 _public member_ `FXmppUserJid UserJid;` — full jid for user that sent this presence update
- L74 _public function_ `inline bool operator==(const FXmppUserPresence& Presence) const`
- L84 _public function_ `inline bool operator!=(const FXmppUserPresence& Presence) const`

#### class `FXmppMucPresence`  
`class FXmppMucPresence : public FXmppUserPresence`  
_L93-116_
- inherits: `FXmppUserPresence`
- desc: Muc room presence from an Xmpp muc room member
- L97 _public function_ `FXmppMucPresence() : FXmppUserPresence()` — constructor
- L102 _public member_ `FString Role;` — Role of the member in the room
- L104 _public member_ `FString Affiliation;` — Affiliation of the member in the room
- L112 _public member_ `FXmppUserJid MemberJid;` — JID of the member outside of the chat room, if the room is non-anonymous. May be blank. Different from UserJid, where UserJid is the identifier of this member inside of the chat room. Use this to identify the user outside of the chat room (such as private messages) ex: AccountId@Domain/Resource @see https://xmpp.org/extensions/xep-0045.html#enter-nonanon
- L114 _public function_ `const FString& GetRoomId() const`
- L115 _public function_ `const FString& GetNickName() const`

#### class `IXmppPresence`  
`class IXmppPresence`  
_L121-177_
- desc: Interface for updating presence for current user and for obtaining updates of roster members
- L126 _public prototype_ `virtual ~IXmppPresence() = default;` — destructor
- L135 _public prototype_ `virtual bool UpdatePresence(const FXmppUserPresence& Presence) = 0;` — Send a presence update to Xmpp service for current user logged in with the connection. Also updates cached copy of presence data @param Presence status data to update @return true if successfully sent
- L142 _public prototype_ `virtual const FXmppUserPresence& GetPresence() const = 0;` — Get the last cached presence for the current user @return Presence status data
- L149 _public prototype_ `virtual bool QueryPresence(const FString& UserId) = 0;` — Kick off a query for presence data for a given user @return true if successfully sent
- L156 _public prototype_ `virtual void GetRosterMembers(TArray<FXmppUserJid>& OutMembers) = 0;` — Obtain a list of current roster member id @param OutMembers [out] members to update
- L163 _public prototype_ `virtual TArray<TSharedPtr<FXmppUserPresence>> GetRosterPresence(const FString& UserId) = 0;` — Obtain presence info for a given roster member id @return cached presence or NULL if not found
- L174 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppPresenceReceived, const TSharedRef<IXmppConnection>& , const FXmppUserJid& , const TSharedRef<FXmppUserPresence>& );` — Delegate callback for when new presence data is received for a given user. Can also obtain cached data via GetRosterPresence() @param Connection the xmpp connection this message was received on @param UserId roster member or current user that updated @param Presence presence data that was received
- L176 _public prototype_ `virtual FOnXmppPresenceReceived& OnReceivePresence() = 0;` — @return presence received delegate

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace EXmppPresenceStatus`
- L30 _function_ `inline const TCHAR* ToString(EXmppPresenceStatus::Type EnumVal)` (scope `EXmppPresenceStatus`) — @return string version of enum
- L174 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppPresenceReceived, const TSharedRef<IXmppConnection>& , const FXmppUserJid& , const TSharedRef<FXmppUserPresence>& );` — Delegate callback for when new presence data is received for a given user. Can also obtain cached data via GetRosterPresence() @param Connection the xmpp connection this message was received on @param UserId roster member or current user that updated @param Presence presence data that was received

### `Source/Runtime/Online/XMPP/Public/XmppPubSub.h` (Public)


#### class `FXmppPubSubConfig`  
`class FXmppPubSubConfig`  
_L16-36_
- desc: Info to configure a new PubSub node
- L19 _public function_ `FXmppPubSubConfig() : bPersistItems(false) , bCollection(false) , MaxItems(1) , MaxPayloadSize(4*1024)`
- L27 _public member_ `bool bPersistItems;` — items published to the node are not persisted
- L29 _public member_ `bool bCollection;` — node is a collection of node instead of a leaf node. can only publish to leaf nodes
- L31 _public member_ `int32 MaxItems;` — maximum number of items that the node will persist
- L33 _public member_ `int32 MaxPayloadSize;` — maximum size of item payload in bytes
- L35 _public member_ `FXmppPubSubId CollectionId;` — optional id of collection node to use as container/parent for this node

#### class `FXmppPubSubMessage`  
`class FXmppPubSubMessage`  
_L41-58_
- desc: Message received from PubSub node
- L45 _public function_ `FXmppPubSubMessage()` — constructor
- L49 _public member_ `FXmppUserJid FromJid;` — jid of node that sent the message
- L51 _public member_ `FXmppUserJid ToJid;` — jid of message recipient
- L53 _public member_ `FString Payload;` — body of the message
- L55 _public member_ `FString Type;` — type of the message
- L57 _public member_ `FDateTime Timestamp;` — date sent

#### class `FXmppPubSubNode`  
`class FXmppPubSubNode`  
_L63-73_
- desc: Info cached about a PubSub node
- L66 _public function_ `FXmppPubSubNode()`
- L70 _public member_ `FXmppPubSubId Id;` — id/path of the pubsub node
- L72 _public member_ `FXmppPubSubConfig Config;` — configuration of the node

#### class `IXmppPubSub`  
`class IXmppPubSub`  
_L78-128_
- desc: Interface for publishing/subscribing to events
- L82 _public prototype_ `virtual ~IXmppPubSub() = default;`
- L84 _public prototype_ `virtual bool CreateNode(const FXmppPubSubId& NodeId, const FXmppPubSubConfig& NodeConfig) = 0;`
- L85 _public prototype_ `virtual bool ConfigureNode(const FXmppPubSubId& NodeId, const FXmppPubSubConfig& NodeConfig) = 0;`
- L86 _public prototype_ `virtual bool DestroyNode(const FXmppPubSubId& NodeId) = 0;`
- L87 _public prototype_ `virtual bool QueryNode(const FXmppPubSubId& NodeId) = 0;`
- L88 _public prototype_ `virtual bool QuerySubscriptions() = 0;`
- L89 _public prototype_ `virtual bool Subscribe(const FXmppPubSubId& NodeId) = 0;`
- L90 _public prototype_ `virtual bool Unsubscribe(const FXmppPubSubId& NodeId) = 0;`
- L91 _public prototype_ `virtual bool PublishMessage(const FXmppPubSubId& NodeId, const FXmppPubSubMessage& Message) = 0;`
- L92 _public prototype_ `virtual TArray<FXmppPubSubId> GetOwnedNodes() const = 0;`
- L93 _public prototype_ `virtual TArray<FXmppPubSubId> GetSubscribedNodes() const = 0;`
- L94 _public prototype_ `virtual TSharedPtr<FXmppPubSubNode> GetNodeInfo(const FXmppPubSubId& NodeId) const = 0;`
- L95 _public prototype_ `virtual bool GetLastMessages(const FXmppPubSubId& NodeId, int32 NumMessages, TArray< TSharedRef<FXmppPubSubMessage> >& OutMessages) const = 0;`
- L97 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppPubSubCreateNodeComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppPubSubId& , const FString& );`
- L99 _public prototype_ `virtual FOnXmppPubSubCreateNodeComplete& OnCreateNodeComplete() = 0;` — @return pubsub node created delegate
- L101 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppPubSubConfigureNodeComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppPubSubId& , const FString& );`
- L103 _public prototype_ `virtual FOnXmppPubSubConfigureNodeComplete& OnConfigureNodeComplete() = 0;` — @return pubsub node configured delegate
- L105 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppPubSubDestroyNodeComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppPubSubId& , const FString& );`
- L107 _public prototype_ `virtual FOnXmppPubSubDestroyNodeComplete& OnDestroyNodeComplete() = 0;` — @return pubsub node destroyed delegate
- L109 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppPubSubQueryNodeComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppPubSubId& , const FString& );`
- L111 _public prototype_ `virtual FOnXmppPubSubQueryNodeComplete& OnQueryNodeComplete() = 0;` — @return pubsub node query delegate
- L113 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppPubSubQuerySubscriptionsComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppPubSubId& , const FString& );`
- L115 _public prototype_ `virtual FOnXmppPubSubQuerySubscriptionsComplete& OnQuerySubscriptionsComplete() = 0;` — @return pubsub node created delegate
- L117 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppPubSubSubscribed, const TSharedRef<IXmppConnection>& , FXmppPubSubId& , const FXmppUserJid& );`
- L119 _public prototype_ `virtual FOnXmppPubSubSubscribed& OnSubscribed() = 0;` — @return pubsub node subscription delegate
- L121 _public prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppPubSubUnsubscribed, const TSharedRef<IXmppConnection>& , FXmppPubSubId& , const FXmppUserJid& );`
- L123 _public prototype_ `virtual FOnXmppPubSubUnsubscribed& OnUnsubscribed() = 0;` — @return pubsub node unsubscribe delegate
- L125 _public prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppPubSubMessageReceived, const TSharedRef<IXmppConnection>& , FXmppPubSubId& , const FXmppUserJid& , const TSharedRef<FXmppPubSubMessage>& );`
- L127 _public prototype_ `virtual FOnXmppPubSubMessageReceived& OnMessageReceived() = 0;` — @return pubsub message received delegate

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef FString FXmppPubSubId;` — Id of a PubSub node
- L97 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppPubSubCreateNodeComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppPubSubId& , const FString& );`
- L101 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppPubSubConfigureNodeComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppPubSubId& , const FString& );`
- L105 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppPubSubDestroyNodeComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppPubSubId& , const FString& );`
- L109 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppPubSubQueryNodeComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppPubSubId& , const FString& );`
- L113 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppPubSubQuerySubscriptionsComplete, const TSharedRef<IXmppConnection>& , bool , const FXmppPubSubId& , const FString& );`
- L117 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppPubSubSubscribed, const TSharedRef<IXmppConnection>& , FXmppPubSubId& , const FXmppUserJid& );`
- L121 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnXmppPubSubUnsubscribed, const TSharedRef<IXmppConnection>& , FXmppPubSubId& , const FXmppUserJid& );`
- L125 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnXmppPubSubMessageReceived, const TSharedRef<IXmppConnection>& , FXmppPubSubId& , const FXmppUserJid& , const TSharedRef<FXmppPubSubMessage>& );`

### `Source/Runtime/Online/XMPP/Public/XmppStanza.h` (Public)


#### class `IXmppStanza`  
`class IXmppStanza`  
_L13-88_
- desc: Xmpp stanza abstract interface Exposes getters for various attributes and fields of an Xmpp stanza
- L17 _public prototype_ `virtual ~IXmppStanza() = default;`
- L23 _public prototype_ `virtual FString GetName() const = 0;` — Get Stanza type (presence, query, message) @return stanza type
- L29 _public prototype_ `virtual FString GetText() const = 0;` — Get Stanza text (concatenates all child text nodes) @return stanza text
- L35 _public prototype_ `virtual FString GetType() const = 0;` — Get Stanza type @return stanza type
- L41 _public prototype_ `virtual FString GetId() const = 0;` — Get Stanza Id @return Stanza Id
- L47 _public prototype_ `virtual FXmppUserJid GetTo() const = 0;` — Get Stanza to (destination) user Jid @return Stanza to Jid
- L53 _public prototype_ `virtual FXmppUserJid GetFrom() const = 0;` — Get Stanza from (source) user Jid @return Stanza from Jid
- L60 _public prototype_ `virtual FString GetAttribute(const FString& Key) const = 0;` — Get Stanza attribute @param Key attribute name @return attribute text
- L67 _public prototype_ `virtual bool HasAttribute(const FString& Key) const = 0;` — Returns whether or not stanza has a given attribute @param Key attribute name @return whether or not stanza has attribute named Key
- L73 _public prototype_ `virtual TOptional<FString> GetBodyText() const = 0;` — Get stanza body text (if any) @return Stanza body text
- L80 _public prototype_ `virtual TUniquePtr<IXmppStanza> GetChild(const FString& ChildName) const = 0;` — Get given Stanza child, if existing @param ChildName name of child to return @return Stanza ChildName, if it exists
- L87 _public prototype_ `virtual bool HasChild(const FString& ChildName) const = 0;` — Whether or not Stanza has a given child @param ChildName name of child to check for @return Whether or not Stanza has child ChildName
