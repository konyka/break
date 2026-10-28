# Plugins / BackChannel

- module root: `Plugins/Experimental/BackChannel/Source/BackChannel`
- headers: 14; symbols: 262
- symbol kinds: class=12, delegate=2, enum=2, enumerator=5, externvar=2, function=41, macro=7, member=51, prototype=136, struct=2, typedef=2
- PrivateDependencyModuleNames: Core, Networking, Sockets

### `Plugins/Experimental/BackChannel/Source/BackChannel/Private/BackChannelCommon.h` (Private)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBackChannel, Log, All);`
- L9 _externvar_ `extern int32 GBackChannelLogPackets;`
- L10 _externvar_ `extern int32 GBackChannelLogErrors;`

### `Plugins/Experimental/BackChannel/Source/BackChannel/Private/Transport/BackChannelConnection.h` (Private)


#### class `FBackChannelConnection`  
`class FBackChannelConnection : public IBackChannelSocketConnection, public TSharedFromThis<FBackChannelConnection>`  
_L16-82_
- inherits: `IBackChannelSocketConnection,TSharedFromThis<FBackChannelConnection>`
- desc: BackChannelClient implementation.
- L20 _public prototype_ `FBackChannelConnection();`
- L21 _public prototype_ `~FBackChannelConnection();`
- L24 _public prototype_ `virtual bool Connect(const TCHAR* InEndPoint) override;` — Start connecting to the specified port for incoming connections. Use WaitForConnection to check status.
- L27 _public prototype_ `virtual bool Listen(const int16 Port) override;` — Start listening on the specified port for incoming connections. Use WaitForConnection to accept one.
- L30 _public prototype_ `virtual void Close() override;` — Close the connection
- L33 _public prototype_ `virtual bool WaitForConnection(double InTimeout, TFunction<bool(TSharedRef<IBackChannelSocketConnection>)> InDelegate) override;` — Waits for an icoming or outgoing connection to be made
- L36 _public prototype_ `bool Attach(FSocket* InSocket);` — Attach this connection to the provided socket
- L39 _public prototype_ `virtual int32 SendData(const void* InData, const int32 InSize) override;` — Send data over our connection. The number of bytes sent is returned
- L42 _public prototype_ `virtual int32 ReceiveData(void* OutBuffer, const int32 BufferSize) override;` — Read data from our remote connection. The number of bytes received is returned
- L45 _public prototype_ `virtual bool IsConnected() const override;` — Return our current connection state
- L48 _public prototype_ `virtual bool IsListening() const override;` — Returns true if this connection is currently listening for incoming connections
- L51 _public prototype_ `virtual FString GetDescription() const override;` — Return a string describing this connection
- L54 _public function_ `virtual FSocket* GetSocket() override` — Return the underlying socket (if any) for this connection
- L57 _public prototype_ `virtual uint32 GetPacketsReceived() const override;` — Todo - Proper stats
- L60 _public prototype_ `virtual void SetBufferSizes(int32 DesiredSendSize, int32 DesiredReceiveSize) override;` — Set the specified send and receive buffer sizes, if supported
- L62 _public function_ `const FConnectionStats& GetConnectionStats() const override`
- L65 _private member_ `static int32 SendBufferSize;`
- L66 _private member_ `static int32 ReceiveBufferSize;`
- L68 _private prototype_ `void CloseWithError(const TCHAR* Error, FSocket* InSocket=nullptr);`
- L69 _private prototype_ `void ResetStatsIfTime();`
- L72 _private prototype_ `void SetSocketBufferSizes(FSocket* NewSocket, int32 DesiredSendSize, int32 DesiredReceiveSize);` — Attempts to set the specified buffer size on our socket, will drop by 50% each time until success
- L74 _private member_ `FThreadSafeBool IsAttemptingConnection;`
- L75 _private member_ `FCriticalSection SocketMutex;`
- L76 _private member_ `FSocket* Socket;`
- L77 _private member_ `bool IsListener;`
- L79 _private member_ `FConnectionStats ConnectionStats;`
- L80 _private member_ `FConnectionStats LastStats;`
- L81 _private member_ `double TimeSinceStatsSet;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API BACKCHANNEL_API`

### `Plugins/Experimental/BackChannel/Source/BackChannel/Public/BackChannel/IBackChannelConnection.h` (Public)


#### class `IBackChannelConnection`  
`class IBackChannelConnection`  
_L10-30_
- desc: Declares the interface for a BackChannel connection
- L14 _public prototype_ `virtual ~IBackChannelConnection() = default;`
- L16 _public prototype_ `virtual FString GetProtocolName() const = 0;`
- L18 _public prototype_ `virtual TBackChannelSharedPtr<IBackChannelPacket> CreatePacket() = 0;`
- L20 _public prototype_ `virtual int SendPacket(const TBackChannelSharedPtr<IBackChannelPacket>& Packet) = 0;`
- L23 _public prototype_ `virtual FDelegateHandle AddRouteDelegate(FStringView Path, FBackChannelRouteDelegate::FDelegate Delegate) = 0;` — Bind a delegate to a message address
- L26 _public prototype_ `virtual void RemoveRouteDelegate(FStringView Path, FDelegateHandle& InHandle) = 0;` — Remove a delegate handle
- L29 _public prototype_ `virtual void SetBufferSizes(int32 DesiredSendSize, int32 DesiredReceiveSize) = 0;` — Set the specified send and receive buffer sizes, if supported

### `Plugins/Experimental/BackChannel/Source/BackChannel/Public/BackChannel/IBackChannelPacket.h` (Public)


#### class `IBackChannelPacket`  
`class IBackChannelPacket`  
_L13-78_
- desc: Declares the interface for a BackChannel packet
- L17 _public prototype_ `virtual ~IBackChannelPacket() = default;`
- L19 _public prototype_ `virtual FBackChannelPacketType GetProtocolID() const = 0;`
- L21 _public prototype_ `virtual FString GetProtocolName() const = 0;`
- L23 _public prototype_ `virtual bool IsWritable() const = 0;`
- L25 _public prototype_ `virtual bool IsReadable() const = 0;`
- L30 _public prototype_ `virtual int SetPath(const TCHAR* InPath) = 0;` — Set the path of this packet (if supported)
- L33 _public prototype_ `virtual int Write(const TCHAR* Name, const int32 Value) = 0;` — Write an int32 into the message
- L36 _public prototype_ `virtual int Write(const TCHAR* Name, const float Value) = 0;` — Write an int32 into message
- L39 _public prototype_ `virtual int Write(const TCHAR* Name, const bool Value) = 0;` — Write a bool into the message
- L42 _public prototype_ `virtual int Write(const TCHAR* Name, const TCHAR* Value) = 0;` — Write a string into the message
- L45 _public prototype_ `virtual int Write(const TCHAR* Name, const FString& Value) = 0;` — Write a string into the message
- L48 _public prototype_ `virtual int Write(const TCHAR* Name, const TArrayView<const uint8> Value) = 0;` — Write a TArray into the message
- L51 _public prototype_ `virtual int Write(const TCHAR* Name, const void* InBlob, int32 BlobSize) = 0;` — Write a block of data into the message
- L56 _public prototype_ `virtual FString GetPath() const = 0;` — Return the path of this packet (if supported)
- L59 _public prototype_ `virtual int Read(const TCHAR* Name, int32& Value) = 0;` — Read an int32 from the message
- L62 _public prototype_ `virtual int Read(const TCHAR* Name, float& Value) = 0;` — Read an int32 from the message
- L65 _public prototype_ `virtual int Read(const TCHAR* Name, bool& Value) = 0;` — Read a bool from the message
- L68 _public prototype_ `virtual int Read(const TCHAR* Name, FString& Value) = 0;` — Read a string from the message
- L71 _public prototype_ `virtual int Read(const TCHAR* Name, TArray<uint8>& Data) = 0;` — Read a TArray from the message
- L74 _public prototype_ `virtual int Read(const TCHAR* InName, void* OutBlob, int32 MaxBlobSize, int32& OutBlobSize) = 0;` — Read a block of data from the message
- L77 _public prototype_ `virtual void ResetReading() = 0;` — Reset the reading position

### `Plugins/Experimental/BackChannel/Source/BackChannel/Public/BackChannel/Protocol/OSC/BackChannelOSC.h` (Public)
_(no declarations extracted)_

### `Plugins/Experimental/BackChannel/Source/BackChannel/Public/BackChannel/Protocol/OSC/BackChannelOSCBundle.h` (Public)


#### class `FBackChannelOSCBundle`  
`class FBackChannelOSCBundle : public FBackChannelOSCPacket`  
_L8-46_
- inherits: `FBackChannelOSCPacket`
- L12 _public prototype_ `FBackChannelOSCBundle(OSCPacketMode InMode);`
- L13 _public prototype_ `virtual ~FBackChannelOSCBundle();`
- L15 _public prototype_ `FBackChannelOSCBundle(FBackChannelOSCBundle&& RHS);`
- L17 _public prototype_ `FBackChannelOSCBundle& operator=(FBackChannelOSCBundle&& RHS);`
- L19 _public function_ `virtual OSCPacketType GetType() const override`
- L21 _public prototype_ `virtual int32 GetSize() const override;`
- L23 _public prototype_ `void AddElement(const void* InData, const int32 InSize);`
- L25 _public prototype_ `int32 GetElementCount() const;`
- L27 _public prototype_ `const TArray<uint8>& GetElement(const int32 Index) const;`
- L29 _public prototype_ `virtual TArray<uint8> WriteToBuffer() const override;`
- L31 _public prototype_ `virtual void WriteToBuffer(TArray<uint8>& Buffer) const override;`
- L33 _public prototype_ `static TSharedPtr<FBackChannelOSCBundle> CreateFromBuffer(const void* Data, int32 DataLength);`
- L39 _protected typedef_ `typedef TArray<uint8> ElementData;`
- L41 _protected member_ `OSCPacketMode Mode;`
- L42 _protected member_ `int64 TimeTag;`
- L43 _protected member_ `TArray<ElementData> Elements;`
- L45 _protected member_ `static const ANSICHAR* BundleHeader;`

### `Plugins/Experimental/BackChannel/Source/BackChannel/Public/BackChannel/Protocol/OSC/BackChannelOSCConnection.h` (Public)


#### class `FBackChannelOSCConnection`  
`class FBackChannelOSCConnection : FRunnable, public IBackChannelConnection`  
_L20-124_
- inherits: `FRunnable,IBackChannelConnection`
- desc: A class that wraps an existing BackChannel connection and provides an OSC-focused interface and a background thread. Incoming messages are received on a background thread and queued until DispatchMessages() is called. Outgoing messages are sent immediately
- L24 _public prototype_ `FBackChannelOSCConnection(TSharedRef<IBackChannelSocketConnection> InConnection);`
- L26 _public prototype_ `~FBackChannelOSCConnection();`
- L32 _public prototype_ `FString GetProtocolName() const override;`
- L34 _public prototype_ `TBackChannelSharedPtr<IBackChannelPacket> CreatePacket() override;`
- L36 _public prototype_ `int SendPacket(const TBackChannelSharedPtr<IBackChannelPacket>& Packet) override;`
- L39 _public prototype_ `FDelegateHandle AddRouteDelegate(FStringView Path, FBackChannelRouteDelegate::FDelegate Delegate) override;` — Bind a delegate to a message address
- L42 _public prototype_ `void RemoveRouteDelegate(FStringView Path, FDelegateHandle& InHandle) override;` — Remove a delegate handle
- L45 _public prototype_ `void SetBufferSizes(int32 DesiredSendSize, int32 DesiredReceiveSize) override;` — Sets the send and receive buffer sizes
- L49 _public prototype_ `bool StartReceiveThread();`
- L52 _public prototype_ `virtual void Stop() override;`
- L56 _public prototype_ `bool IsConnected() const;` — Returns our connection state as determined by the underlying BackChannel connection
- L59 _public prototype_ `bool IsThreaded() const;` — Returns true if running in the background
- L65 _public prototype_ `void ReceiveAndDispatchMessages(const float MaxTime = 0);` — Checks for and dispatches any incoming messages. MaxTime is how long to wait if no data is ready to be read. This function is thread-safe and be called from a backfround thread manually or by calling StartReceiveThread()
- L68 _public prototype_ `bool SendPacket(FBackChannelOSCPacket& Packet);` — Send the provided OSC packet
- L71 _public prototype_ `void SetMessageOptions(const TCHAR* Path, int32 MaxQueuedMessages);` — Set options for the specified message path
- L73 _public prototype_ `FString GetDescription();`
- L77 _protected prototype_ `virtual uint32 Run() override;`
- L80 _protected prototype_ `bool SendPacketData(const void* Data, const int32 DataLen);`
- L82 _protected prototype_ `int32 GetMessageLimitForPath(const TCHAR* Path);`
- L84 _protected prototype_ `int32 GetMessageCountForPath(const TCHAR* Path);`
- L86 _protected prototype_ `void RemoveMessagesWithPath(const TCHAR* Path, const int32 Num = 0);`
- L88 _protected prototype_ `void ReceiveMessages(const float MaxTime = 0);`
- L91 _protected prototype_ `void DispatchMessages();` — Dispatch all queued messages
- L96 _protected member_ `TSharedPtr<IBackChannelSocketConnection> Connection;`
- L98 _protected member_ `FBackChannelDispatchMap DispatchMap;`
- L100 _protected member_ `TArray<TSharedPtr<FBackChannelOSCPacket>> ReceivedPackets;`
- L102 _protected member_ `TMap<FString, int32> MessageLimits;`
- L104 _protected member_ `FThreadSafeBool ExitRequested;`
- L105 _protected member_ `FThreadSafeBool IsRunning;`
- L107 _protected member_ `FCriticalSection ReceiveMutex;`
- L108 _protected member_ `FCriticalSection SendMutex;`
- L109 _protected member_ `FCriticalSection PacketMutex;`
- L110 _protected member_ `TArray<uint8> ReceiveBuffer;`
- L114 _protected member_ `double PingTime = 2;` — Time where we'll send a ping if no packets arrive to check the connection is alive
- L117 _protected member_ `bool HasErrorState = false;` — Is the connection in an error state
- L120 _protected member_ `int32 ReceivedDataSize = 0;` — How much data has been received this check?
- L123 _protected member_ `int32 ExpectedSizeOfNextPacket = 4;` — How much data do we expect to receive next time? This is for OSC over TCP where the size of a packet is sent, then the packet

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API BACKCHANNEL_API`

### `Plugins/Experimental/BackChannel/Source/BackChannel/Public/BackChannel/Protocol/OSC/BackChannelOSCMessage.h` (Public)


#### class `FBackChannelOSCMessage`  
`class FBackChannelOSCMessage : public FBackChannelOSCPacket, public IBackChannelPacket`  
_L21-366_
- inherits: `FBackChannelOSCPacket,IBackChannelPacket`
- desc: Representation of an OSC message. Data can be read/written using the explicit Read/Write functions, or the Serialize function / << operator where the behaviour is overloaded based on whether the message was created for reading or writing. Any failed Reads() will result in the default value of the type (e.g. 0, 0.0, false, "") being returned.
- L25 _public prototype_ `FBackChannelOSCMessage(OSCPacketMode InMode);`
- L27 _public prototype_ `FBackChannelOSCMessage(const TCHAR* Address);`
- L29 _public prototype_ `virtual ~FBackChannelOSCMessage();`
- L32 _public prototype_ `FBackChannelOSCMessage(FBackChannelOSCMessage&& RHS);` — Move constructor
- L35 _public prototype_ `FBackChannelOSCMessage& operator=(FBackChannelOSCMessage&& RHS);` — Move operator
- L38 _public function_ `virtual OSCPacketType GetType() const override` — Return our type
- L41 _public prototype_ `virtual int32 GetSize() const override;` — Return our size (plus any necessary padding)
- L44 _public prototype_ `virtual TArray<uint8> WriteToBuffer() const override;` — Returns a buffer with the contents of this message. Data is padded per OSC requirements
- L47 _public prototype_ `virtual void WriteToBuffer(TArray<uint8>& Buffer) const override;` — Writes this message into the provided buffer at an offset of Buffer.Num()
- L50 _public function_ `bool IsWriting() const` — Helper to check our read/write status
- L53 _public function_ `bool IsReading() const` — Helper to check our read/write status
- L56 _public function_ `FString GetPath() const` — Returns the address of this packet
- L62 _public function_ `const FString& GetTags() const` — Return our argument tags
- L68 _public function_ `int32 GetArgumentCount() const` — Returns the number of arguments in this message
- L74 _public function_ `TCHAR GetNextArgumentType() const` — Returns the type of our next argument
- L80 _public function_ `const int32 GetArgumentSize() const` — Return the size (plus padding) of all our arguments)
- L86 _public prototype_ `int SetPath(const TCHAR* Address);` — Set our destination address
- L89 _public prototype_ `void ResetRead();` — Reset us for reading. The next argument read will be our first argument
- L91 _public function_ `virtual FBackChannelPacketType GetProtocolID() const`
- L93 _public function_ `virtual FString GetProtocolName() const`
- L95 _public function_ `virtual bool IsWritable() const`
- L97 _public function_ `virtual bool IsReadable() const`
- L102 _public function_ `virtual int Write(const TCHAR* InName, const int32 Value) override` — Write an int32 into our arguments
- L111 _public function_ `virtual int Write(const TCHAR* InName, const float Value) override` — Write a float to our arguments
- L119 _public function_ `virtual int Write(const TCHAR* InName, const bool Value) override` — Write a bool to our arguments
- L134 _public function_ `virtual int Write(const TCHAR* InName, const TCHAR* Value) override` — Write a string to our arguments
- L140 _public function_ `virtual int Write(const TCHAR* InName, const FString& Value) override` — Write a string to our arguments
- L146 _public function_ `virtual int Write(const TCHAR* InName, const void* InBlob, int32 BlobSize) override` — Write a blob of data to our arguments
- L167 _public function_ `virtual int Write(const TCHAR* InName, const TArrayView<const uint8> InValues) override` — Read data from the message into a TArray. It must have been serialized by the Read form for TArray(!). Note - data will be appended to the array.
- L174 _public function_ `template<typename T> int Write(const TCHAR* InName, const TArrayView<const T> InValues)` — Write a TArrayView into the message
- L191 _public function_ `virtual int Read(const TCHAR* InName, int32& Value) override` — Read an int32 from our arguments
- L205 _public function_ `virtual int Read(const TCHAR* InName, float& OutValue) override` — Read a float from our arguments
- L219 _public function_ `virtual int Read(const TCHAR* InName, bool& Value) override` — Read a bool from our arguments
- L242 _public prototype_ `virtual int Read(const TCHAR* InName, FString& OutValue) override;` — Read a string from our arguments.
- L247 _public prototype_ `virtual int Read(const TCHAR* InName, void* InBlob, int32 MaxBlobSize, int32& OutBlobSize) override;` — Read a blob of data from our arguments
- L250 _public function_ `virtual void ResetReading() override` — Reset the reading position
- L259 _public function_ `virtual int Read(const TCHAR* InName, TArray<uint8>& DataArray) override` — Read data from the message into a TArray. It must have been serialized by the Read form for TArray(!). Note - data will be appended to the array.
- L269 _public function_ `template<typename T> int Read(const TCHAR* InName, TArray<T>& DataArray)` — Read a TArray of type T from our arguments. This is a helper that reads an int for the size, then allocated and reads a blob of sizeof(t) * NumItems
- L305 _public function_ `template<typename T> void Serialize(const TCHAR* Name, T& Value)` — Serialize helper that will read/write based on the open mode of this message
- L318 _public function_ `void Serialize(const TCHAR* Name, void* InBlob, int32 BlobSize)` — Serialize helper that will read/write based on the open mode of this message
- L331 _public function_ `static int32 RoundedArgumentSize(int32 ArgSize)`
- L336 _public prototype_ `static TSharedPtr<FBackChannelOSCMessage> CreateFromBuffer(const void* Data, int32 DataLength);`
- L338 _public function_ `static void SetLegacyMode(const bool bEnable)`
- L339 _public function_ `static bool IsLegacyConnection()`
- L344 _protected prototype_ `void GetComponentSizes(int32& OutAddressSize, int32& OutTagSize, int32& OutBufferSize) const;` — Return our sizes for each item (plus any necessary padding)
- L346 _protected prototype_ `int Serialize(const TCHAR Code, void* InData, int32 InSize);`
- L348 _protected prototype_ `TCHAR ReadTag(const TCHAR ExpectedTag, bool SuppressWarning=false);`
- L349 _protected prototype_ `int ReadData(void* InData, int32 InSize);`
- L350 _protected prototype_ `int ReadTagAndData(const TCHAR ExpectedTag, void* InData, int32 InSize);`
- L352 _protected prototype_ `int WriteTag(const TCHAR Code);`
- L353 _protected prototype_ `int WriteTagAndData(const TCHAR Code, const void* InData, int32 InSize);`
- L354 _protected prototype_ `int WriteData(const void* InData, int32 InSize);`
- L358 _protected member_ `OSCPacketMode Mode;`
- L359 _protected member_ `FString Address;`
- L360 _protected member_ `FString TagString;`
- L361 _protected member_ `int TagIndex;`
- L362 _protected member_ `int BufferIndex;`
- L363 _protected member_ `TArray<uint8> Buffer;`
- L365 _protected member_ `static bool bIsLegacyConnection;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API BACKCHANNEL_API`

### `Plugins/Experimental/BackChannel/Source/BackChannel/Public/BackChannel/Protocol/OSC/BackChannelOSCPacket.h` (Public)


#### enum `OSCPacketMode`  
`enum class OSCPacketMode`  
_L9-13_
- L11 _public enumerator_ `Read`
- L12 _public enumerator_ `Write`

#### enum `OSCPacketType`  
`enum class OSCPacketType`  
_L15-20_
- L17 _public enumerator_ `Invalid`
- L18 _public enumerator_ `Message`
- L19 _public enumerator_ `Bundle`

#### class `FBackChannelOSCPacket`  
`class FBackChannelOSCPacket`  
_L25-48_
- desc: Base class for OSC messages
- L29 _public prototype_ `virtual ~FBackChannelOSCPacket() = default;`
- L32 _public prototype_ `virtual int32 GetSize() const = 0;` — Return the total size in bytes of this message
- L35 _public prototype_ `virtual OSCPacketType GetType() const = 0;` — Return the type of this packet
- L38 _public prototype_ `virtual TArray<uint8> WriteToBuffer() const =0;` — Return a buffer with a copy of the contents of this packet
- L41 _public prototype_ `virtual void WriteToBuffer(TArray<uint8>& Buffer) const = 0;` — Write the contents of this packet into the specified buffer starting at an offset of Buffer.Num()
- L44 _public prototype_ `static OSCPacketType GetType(const void* Data, int32 DataLength);` — Static helper to determine the type of packet (if any) at the specified address
- L47 _public prototype_ `static TSharedPtr<FBackChannelOSCPacket> CreateFromBuffer(const void* Data, int32 DataLength);` — Helper to construct a packet (and in the case of a bundle, any sub-packets) from the specified buffer

#### class `FBackChannelOSCNullPacket`  
`class FBackChannelOSCNullPacket : public FBackChannelOSCPacket`  
_L50-56_
- inherits: `FBackChannelOSCPacket`
- L53 _public function_ `virtual int32 GetSize() const override`
- L55 _public function_ `virtual OSCPacketType GetType() const override`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API BACKCHANNEL_API`

### `Plugins/Experimental/BackChannel/Source/BackChannel/Public/BackChannel/Transport/IBackChannelSocketConnection.h` (Public)


#### class `IBackChannelSocketConnection`  
`class IBackChannelSocketConnection`  
_L16-83_
- desc: Base class that describes a back-channel connection. The underlying behavior will depend on the type of connection that was requested from the factory
- L41 _public prototype_ `virtual bool Connect(const TCHAR* InEndPoint) = 0;` — Start connecting to the specified port for incoming connections. Use WaitForConnection to check status.
- L44 _public prototype_ `virtual bool Listen(const int16 Port) = 0;` — Start listening on the specified port for incoming connections. Use WaitForConnection to accept one.
- L47 _public prototype_ `virtual void Close() = 0;` — Close the connection
- L50 _public prototype_ `virtual bool WaitForConnection(double InTimeout, TFunction<bool(TSharedRef<IBackChannelSocketConnection>)> InDelegate) = 0;` — Waits for an icoming or outgoing connection to be made
- L53 _public prototype_ `virtual bool IsListening() const = 0;` — Returns true if this connection is currently listening for incoming connections
- L56 _public prototype_ `virtual bool IsConnected() const = 0;` — Returns true if this connection is connected to another
- L59 _public prototype_ `virtual int32 SendData(const void* InData, const int32 InSize) = 0;` — Send data via our connection
- L62 _public prototype_ `virtual int32 ReceiveData(void* OutBuffer, const int32 BufferSize) = 0;` — Receive data from our connection. The returned value is the number of bytes read, to a max of BufferSize
- L65 _public prototype_ `virtual FString GetDescription() const = 0;` — Return the underlying socket (if any) for this connection
- L68 _public prototype_ `virtual FSocket* GetSocket() = 0;` — Return the underlying socket (if any) for this connection
- L71 _public prototype_ `virtual uint32 GetPacketsReceived() const = 0;` — Todo - Proper stats
- L74 _public prototype_ `virtual void SetBufferSizes(int32 DesiredSendSize, int32 DesiredReceiveSize) = 0;` — Set the specified send and receive buffer sizes, if supported
- L77 _public prototype_ `virtual const FConnectionStats& GetConnectionStats() const = 0;` — Return stats about this connection
- L81 _protected function_ `IBackChannelSocketConnection()`
- L82 _protected prototype_ `virtual ~IBackChannelSocketConnection() = default;`

#### struct `IBackChannelSocketConnection::FConnectionStats`  
`struct FConnectionStats`  
_L20-34_
- L23 _public member_ `int PacketsSent = 0;` — lifetime stats
- L24 _public member_ `int PacketsReceived = 0;`
- L25 _public member_ `int BytesSent = 0;`
- L26 _public member_ `int BytesReceived = 0;`
- L27 _public member_ `int Errors = 0;`
- L30 _public member_ `double LastSendTime = 0;` — time these events occurred
- L31 _public member_ `double LastReceiveTime = 0;`
- L32 _public member_ `double LastErrorTime = FPlatformTime::Seconds();`
- L33 _public member_ `double LastSuccessTime = FPlatformTime::Seconds();`

### `Plugins/Experimental/BackChannel/Source/BackChannel/Public/BackChannel/Transport/IBackChannelTransport.h` (Public)


#### class `IBackChannelTransport`  
`class IBackChannelTransport : public IModuleInterface`  
_L14-38_
- inherits: `IModuleInterface`
- desc: Main module and factory interface for Backchannel connections
- L18 _public function_ `static inline bool IsAvailable(void)`
- L23 _public function_ `static inline IBackChannelTransport* Get(void)`
- L28 _public prototype_ `virtual TSharedPtr<IBackChannelSocketConnection> CreateConnection(const int32 Type) = 0;`
- L32 _public member_ `static const int TCP;`
- L36 _protected function_ `IBackChannelTransport()`
- L37 _protected prototype_ `virtual ~IBackChannelTransport() = default;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API BACKCHANNEL_API`

### `Plugins/Experimental/BackChannel/Source/BackChannel/Public/BackChannel/Types.h` (Public)


#### struct `FBackChannelPacketType`  
`struct FBackChannelPacketType`  
_L10-18_
- L12 _public function_ `FBackChannelPacketType(char A, char B, char C, char D) : ID`
- L17 _public member_ `char ID[4];`

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FBackChannelRouteDelegate, IBackChannelPacket&) template <class ObjectType> using TBackChannelSharedPtr = TSharedPtr<ObjectType, ESPMode::ThreadSafe>;`
- L24 _typedef_ `template <class ObjectType> using TBackChannelSharedPtr = TSharedPtr<ObjectType, ESPMode::ThreadSafe>;`

### `Plugins/Experimental/BackChannel/Source/BackChannel/Public/BackChannel/Utils/BackChannelThreadedConnection.h` (Public)


#### class `FBackChannelThreadedListener`  
`class FBackChannelThreadedListener : public FRunnable, public TSharedFromThis<FBackChannelThreadedListener>`  
_L20-45_
- inherits: `FRunnable,TSharedFromThis<FBackChannelThreadedListener>`
- desc: BackChannelClient implementation.
- L24 _public prototype_ `FBackChannelThreadedListener();`
- L25 _public prototype_ `~FBackChannelThreadedListener();`
- L27 _public prototype_ `void Start(TSharedRef<IBackChannelSocketConnection> InConnection, FBackChannelListenerDelegate InDelegate);`
- L29 _public prototype_ `virtual void Stop() override;`
- L31 _public prototype_ `bool IsRunning() const;`
- L35 _protected prototype_ `virtual uint32 Run() override;`
- L39 _private member_ `TSharedPtr<IBackChannelSocketConnection> Connection;`
- L40 _private member_ `FBackChannelListenerDelegate Delegate;`
- L42 _private member_ `FThreadSafeBool bExitRequested;`
- L43 _private member_ `FThreadSafeBool bIsRunning;`
- L44 _private member_ `FCriticalSection RunningCS;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API BACKCHANNEL_API`
- L15 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FBackChannelListenerDelegate, TSharedRef<IBackChannelSocketConnection>);`
- L15 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FBackChannelListenerDelegate, TSharedRef<IBackChannelSocketConnection>);`

### `Plugins/Experimental/BackChannel/Source/BackChannel/Public/BackChannel/Utils/DispatchMap.h` (Public)


#### class `FBackChannelDispatchMap`  
`class FBackChannelDispatchMap`  
_L11-30_
- L16 _public prototype_ `FBackChannelDispatchMap();`
- L18 _public prototype_ `virtual ~FBackChannelDispatchMap() = default;`
- L20 _public prototype_ `FDelegateHandle AddRoute(FStringView Path, FBackChannelRouteDelegate::FDelegate Delegate);`
- L22 _public prototype_ `void RemoveRoute(FStringView Path, FDelegateHandle DelegateHandle);`
- L24 _public prototype_ `bool DispatchMessage(IBackChannelPacket& Message);`
- L28 _protected member_ `TMap<FString, FBackChannelRouteDelegate> DispatchMap;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API BACKCHANNEL_API`
