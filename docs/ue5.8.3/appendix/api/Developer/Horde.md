# Developer / Horde

- module root: `Source/Developer/Horde`
- headers: 38; symbols: 779
- symbol kinds: class=38, delegate=1, enum=7, enumerator=42, function=17, macro=30, member=173, namespace=1, prototype=445, struct=22, typedef=3
- PrivateDependencyModuleNames: Core, HTTP, Json
- PrivateIncludePathModuleNames: DesktopPlatform

### `Source/Developer/Horde/Private/Compute/ComputePlatform.h` (Private)


#### class `FComputeEvent`  
`class FComputeEvent`  
_L13-37_
- desc: IPC manually-reset event object
- L16 _public prototype_ `FComputeEvent();`
- L17 _public prototype_ `~FComputeEvent();`
- L20 _public prototype_ `bool Create(const char* Name);` — Creates a new event with the given name
- L23 _public prototype_ `bool OpenExisting(const char* Name);` — Opens an existing event created elsewhere
- L26 _public prototype_ `void Close();` — Close the event and release its resources
- L29 _public prototype_ `void Signal();` — Signal the event, releasing any waiters
- L32 _public prototype_ `bool Wait(int timeoutMs);` — Wait for the event to be signalled or timeout. Pass -1 for timeoutMs to wait infinitely.
- L35 _private member_ `void* Handle;`
- L36 _private member_ `bool Anonymous;`

#### class `FComputeMemoryMappedFile`  
`class FComputeMemoryMappedFile`  
_L42-66_
- desc: IPC memory mapped file
- L45 _public prototype_ `FComputeMemoryMappedFile();`
- L46 _public prototype_ `~FComputeMemoryMappedFile();`
- L49 _public prototype_ `bool Create(const char* Name, long long Capacity);` — Creates a new memory mapped file with the given capacity
- L52 _public prototype_ `bool OpenExisting(const char* Name);` — Opens an existing memory mapped file
- L55 _public prototype_ `void Close();` — Close the memory mapped file handle
- L58 _public prototype_ `void* GetPointer() const;` — Gets a pointer to the mapped memory
- L61 _private member_ `void* Handle;`
- L62 _private member_ `void* Pointer;`
- L63 _private member_ `long long MappedSize;`
- L64 _private member_ `char* OwnerName;`
- L65 _private member_ `bool Anonymous;`

### `Source/Developer/Horde/Private/HordePlatform.h` (Private)


#### struct `FHordePlatform`  
`struct FHordePlatform`  
_L12-49_
- desc: Platform-specific utility functions
- L19 _public prototype_ `[[noreturn]] static void NotImplemented();` — Indicate that the current codepath is not implemented
- L22 _public prototype_ `[[noreturn]] static void NotSupported(const char* Message);` — Indicate that the current codepath is not supported
- L25 _public prototype_ `static bool GetEnvironmentVariable(const char* Name, char* Buffer, size_t BufferLen);` — Reads an environment variable
- L28 _public prototype_ `static void CreateUniqueIdentifier(char* NameBuffer, size_t NameBufferLen);` — Creates a unique identifier
- L31 _public prototype_ `static void CreateUniqueName(char* NameBuffer, size_t NameBufferLen);` — Creates a unique object name
- L38 _public prototype_ `static unsigned int FloorLog2(unsigned int Value);` — Find the log2 of the given value, returning 0 if the value is zero.
- L41 _public prototype_ `static unsigned int CountLeadingZeros(unsigned int Value);` — Count the number of leading zeros in the given value.
- L48 _public prototype_ `static bool TryParseSizeT(const char* Source, size_t SourceLen, size_t& OutValue, size_t& OutNumBytes);` — Parse an integer from a string, returning the number of bytes read

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHorde, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHorde, Log, All);`

### `Source/Developer/Horde/Public/Compute/AgentMessage.h` (Public)


#### enum `EAgentMessageType`  
`enum class EAgentMessageType : unsigned char`  
_L14-63_
- desc: Type of a compute message
- L17 _public enumerator_ `None = 0x00` — No message was received (end of stream)
- L20 _public enumerator_ `Ping = 0x01` — No-op message sent to keep the connection alive. Remote should reply with the same message.
- L23 _public enumerator_ `Exception = 0x02` — Sent in place of a regular response if an error occurs on the remote
- L26 _public enumerator_ `Fork = 0x03` — Fork the message loop into a new channel
- L29 _public enumerator_ `Attach = 0x04` — Sent as the first message on a channel to notify the remote that the remote end is attached
- L32 _public enumerator_ `WriteFiles = 0x10` — Extract files on the remote machine (Initiator -> Remote)
- L35 _public enumerator_ `WriteFilesResponse = 0x11` — Notification that files have been extracted (Remote -> Initiator)
- L38 _public enumerator_ `DeleteFiles = 0x12` — Deletes files on the remote machine (Initiator -> Remote)
- L41 _public enumerator_ `ExecuteV1 = 0x16` — Execute a process in a sandbox (Initiator -> Remote)
- L44 _public enumerator_ `ExecuteV2 = 0x22` — Execute a process in a sandbox (Initiator -> Remote)
- L47 _public enumerator_ `ExecuteOutput = 0x17` — Returns output from the child process to the caller (Remote -> Initiator)
- L50 _public enumerator_ `ExecuteResult = 0x18` — Returns the process exit code (Remote -> Initiator)
- L53 _public enumerator_ `ReadBlob = 0x20` — Reads a blob from storage
- L56 _public enumerator_ `ReadBlobResponse = 0x21` — Response to a ReadBlob request.
- L59 _public enumerator_ `XorRequest = 0xf0` — Xor a block of data with a value
- L62 _public enumerator_ `XorResponse = 0xf1` — Result from an XorRequest request.

#### enum `EExecuteProcessFlags`  
`enum class EExecuteProcessFlags : unsigned char`  
_L66-73_
- desc: Flags describing how to execute a compute task process on the agent
- L69 _public enumerator_ `None = 0` — No execute flags set
- L72 _public enumerator_ `UseWine = 1` — Request execution to be wrapped under Wine when running on Linux. Agent still reserves the right to refuse it (e.g no Wine executable configured, mismatching OS etc)

#### struct `AgentMessage::FException`  
`struct FException`  
_L78-82_
- L80 _public member_ `FUtf8StringView Message;`
- L81 _public member_ `FUtf8StringView Description;`

#### struct `AgentMessage::FBlobRequest`  
`struct FBlobRequest`  
_L84-89_
- L86 _public member_ `FUtf8StringView Locator;`
- L87 _public member_ `int Offset;`
- L88 _public member_ `int Length;`

#### class `FAgentMessageChannel`  
`class FAgentMessageChannel`  
_L93-183_
- desc: Channel for receiving agent messages
- L96 _public prototype_ `FAgentMessageChannel(TSharedPtr<FComputeChannel> InChannel);`
- L97 _public prototype_ `~FAgentMessageChannel();`
- L102 _public prototype_ `void Close();` — Closes the remote message loop
- L105 _public prototype_ `void Ping();` — Sends a ping message to the remote
- L108 _public prototype_ `void Exception(const char* Description, const char* Trace);` — Sends an exception response to the remote
- L111 _public prototype_ `void Fork(int ChannelId, int BufferSize);` — Requests that the remote message loop be forked
- L114 _public prototype_ `void Attach();` — Notifies the remote that a buffer has been attached
- L117 _public prototype_ `void UploadFiles(const char* Path, const char* Locator);` — Extracts a bundle containing files to a particular path
- L120 _public prototype_ `void DeleteFiles(const char* const * Paths, size_t Count);` — Deletes files matching a set of wildcards
- L123 _public prototype_ `void Execute(const char* Exe, const char* const * Args, size_t NumArgs, const char* WorkingDir, const char* const * EnvVars, size_t NumEnvVars, EExecuteProcessFlags Flags);` — Executes a process on the remote machine
- L126 _public prototype_ `void Blob(const unsigned char* Data, size_t Length);` — Writes a blob requested by the remote
- L129 _public prototype_ `void Xor(const unsigned char* Data, size_t Length, unsigned char Value);` — Send a message to request that a byte string be xor'ed with a particular value
- L134 _public prototype_ `EAgentMessageType ReadResponse(int32 TimeoutMS = -1, bool* bOutTimedOut = nullptr);` — Reads a response from the remote. Other Read methods can be used to access response data.
- L137 _public function_ `const void* GetResponseData() const` — Gets the raw data from a response
- L140 _public function_ `size_t GetResponseSize() const` — Gets the size of the response
- L143 _public prototype_ `void ReadException(AgentMessage::FException& Ex);` — Reads an exception response
- L146 _public prototype_ `int ReadExecuteResult();` — Reads the result from executing a process
- L149 _public prototype_ `void ReadBlobRequest(AgentMessage::FBlobRequest& Ex);` — Reads a blob request message
- L152 _private member_ `const size_t MessageHeaderLength = 5;`
- L154 _private member_ `TSharedPtr<FComputeChannel> ChannelBuffers;`
- L156 _private member_ `unsigned char* RequestData;`
- L157 _private member_ `size_t RequestSize;`
- L158 _private member_ `size_t MaxRequestSize;`
- L160 _private member_ `EAgentMessageType ResponseType;`
- L161 _private member_ `const unsigned char* ResponseData;`
- L162 _private member_ `size_t ResponseLength;`
- L164 _private prototype_ `void CreateMessage(EAgentMessageType Type, size_t MaxLength);`
- L165 _private prototype_ `void FlushMessage();`
- L167 _private prototype_ `void WriteInt32(int Value);`
- L168 _private prototype_ `static int ReadInt32(const unsigned char** Pos);`
- L170 _private prototype_ `void WriteFixedLengthBytes(const unsigned char* Data, size_t Length);`
- L171 _private prototype_ `static const unsigned char* ReadFixedLengthBytes(const unsigned char** Pos, size_t Length);`
- L173 _private prototype_ `static size_t MeasureUnsignedVarInt(size_t Value);`
- L174 _private prototype_ `void WriteUnsignedVarInt(size_t Value);`
- L175 _private prototype_ `static size_t ReadUnsignedVarInt(const unsigned char** Pos);`
- L177 _private prototype_ `size_t MeasureString(const char* Text) const;`
- L178 _private prototype_ `void WriteString(const char* Text);`
- L179 _private prototype_ `void WriteString(const std::string_view& Text);`
- L180 _private prototype_ `static FUtf8StringView ReadString(const unsigned char** Pos);`
- L182 _private prototype_ `void WriteOptionalString(const char* Text);`

#### Free symbols / members of external scopes

- L76 _namespace_ `namespace AgentMessage`

### `Source/Developer/Horde/Public/Compute/ComputeBuffer.h` (Public)


#### class `FComputeBuffer`  
`class FComputeBuffer`  
_L24-78_
- desc: Implements a ring buffer using shared memory, with one writer and multiple readers. Contention between the writer and readers is resolved by splitting the buffer into a number of fixed-size chunks, which can be appended to and read immediately, but only reset once consumed by all readers. If the read position is never advanced and only one chunk is used, the buffer functions as an append-only buffer.
- L28 _public member_ `static const int MaxReaders = 16;` — Maximum allowed number of readers
- L31 _public member_ `static const int MaxChunks = 16;` — Maximum allowed number of chunks
- L34 _public member_ `static const size_t MaxNameLength = 256;` — Maximum length of a compute buffer name
- L46 _public prototype_ `FComputeBuffer();`
- L47 _public prototype_ `FComputeBuffer(const FComputeBuffer& Other);`
- L48 _public prototype_ `FComputeBuffer(FComputeBuffer&& Other) noexcept;`
- L49 _public prototype_ `~FComputeBuffer();`
- L51 _public prototype_ `FComputeBuffer& operator=(const FComputeBuffer& Other);`
- L52 _public prototype_ `FComputeBuffer& operator=(FComputeBuffer&& Other) noexcept;`
- L55 _public prototype_ `bool CreateNew(const FParams& Params);` — Creates a new buffer
- L58 _public prototype_ `bool OpenExisting(const char* Name);` — Opens an existing shared memory buffer (typically from handles created in another process)
- L61 _public prototype_ `void Close();` — Close the current buffer and release all allocated resources
- L64 _public function_ `bool IsValid() const` — Test if the buffer is currently open
- L67 _public prototype_ `FComputeBufferReader CreateReader();` — Creates a new reader for this buffer
- L70 _public prototype_ `FComputeBufferWriter CreateWriter();` — Creates a new writer for this buffer
- L75 _private member_ `FComputeBufferDetail* Detail;`
- L77 _private prototype_ `const char* GetName() const;`

#### struct `FComputeBuffer::FParams`  
`struct FParams`  
_L37-44_
- desc: Parameters for constructing a compute buffer
- L39 _public member_ `const char* Name = nullptr;` — When creating a buffer, we should not normally set the name. We can only *OPEN* buffers with a name. Usually we create buffers and attach them to channels.
- L40 _public member_ `int NumChunks = 2;`
- L41 _public member_ `int ChunkLength = 512 * 1024;`
- L42 _public member_ `int NumReaders = 1;`
- L43 _public member_ `bool Anonymous = false;` — Set this to true to use anonymous buffers. This could be used together with for example socket transports

#### class `FComputeBufferReader`  
`class FComputeBufferReader`  
_L83-130_
- desc: Facilitates reading data from a compute buffer
- L86 _public prototype_ `FComputeBufferReader();`
- L87 _public prototype_ `FComputeBufferReader(const FComputeBufferReader& Other);`
- L88 _public prototype_ `FComputeBufferReader(FComputeBufferReader&& Other) noexcept;`
- L89 _public prototype_ `~FComputeBufferReader();`
- L91 _public prototype_ `FComputeBufferReader& operator=(const FComputeBufferReader& Other);`
- L92 _public prototype_ `FComputeBufferReader& operator=(FComputeBufferReader&& Other) noexcept;`
- L95 _public prototype_ `void Close();` — Closes the handle to the underlying reader instance, resetting this instance back to empty
- L98 _public prototype_ `void Detach();` — Detaches this reader from the buffer, causing all pending and subsequent reads to return immediately.
- L101 _public function_ `bool IsValid() const` — Test if the reader is valid
- L104 _public prototype_ `bool IsComplete() const;` — Test whether the buffer has finished being written to (ie. MarkComplete() has been called by the writer) and all data has been read from it.
- L107 _public prototype_ `void AdvanceReadPosition(size_t Size);` — Move the read cursor forwards by the given number of bytes
- L110 _public prototype_ `size_t GetMaxReadSize() const;` — Gets the amount of data that is ready to be read from a contiguous block of memory.
- L113 _public prototype_ `size_t Read(void* Buffer, size_t MaxSize, int TimeoutMs = -1, bool* bOutTimedOut = nullptr);` — Reads data into the given buffer
- L117 _public prototype_ `const unsigned char* WaitToRead(size_t MinSize, int TimeoutMs = -1, bool* bOutTimedOut = nullptr);` — Waits until the given amount of data has been read, and returns a pointer to it. Returns nullptr if the timeout expires, or if the requested amount of data is not in a contiguous block of memory.
- L125 _private member_ `FComputeBufferDetail* Detail;`
- L126 _private member_ `int ReaderIdx;`
- L128 _private prototype_ `FComputeBufferReader(FComputeBufferDetail* Detail, int ReaderIdx);`
- L129 _private prototype_ `const char* GetName() const;`

#### class `FComputeBufferWriter`  
`class FComputeBufferWriter`  
_L135-179_
- desc: Facilitates writing data to a compute buffer
- L138 _public prototype_ `FComputeBufferWriter();`
- L139 _public prototype_ `FComputeBufferWriter(const FComputeBufferWriter& Other);`
- L140 _public prototype_ `FComputeBufferWriter(FComputeBufferWriter&& Other) noexcept;`
- L141 _public prototype_ `~FComputeBufferWriter();`
- L143 _public prototype_ `FComputeBufferWriter& operator=(const FComputeBufferWriter& Other);`
- L144 _public prototype_ `FComputeBufferWriter& operator=(FComputeBufferWriter&& Other) noexcept;`
- L147 _public prototype_ `void Close();` — Closes the handle to the underlying writer instance, resetting this instance back to empty
- L150 _public function_ `bool IsValid() const` — Test if the writer is valid
- L153 _public prototype_ `void MarkComplete();` — Signal that we've finished writing to this buffer
- L156 _public prototype_ `void AdvanceWritePosition(size_t Size);` — Move the write cursor forward by the given number of bytes
- L159 _public prototype_ `size_t GetMaxWriteSize() const;` — Gets the length of the current write buffer.
- L162 _public prototype_ `size_t GetChunkMaxLength() const;` — Get the max length of a chunk.
- L165 _public prototype_ `size_t Write(const void* Buffer, size_t MaxSize, int TimeoutMs = -1);` — Writes data into the compute buffer
- L169 _public prototype_ `unsigned char* WaitToWrite(size_t MinSize, int TimeoutMs = -1);` — Waits until a write buffer of the requested size is available, and returns a pointer to it. Returns nullptr if the timeout expires before enough data has been flushed to return a buffer of the given length.
- L175 _private member_ `FComputeBufferDetail* Detail;`
- L177 _private prototype_ `FComputeBufferWriter(FComputeBufferDetail* Detail);`
- L178 _private prototype_ `const char* GetName() const;`

### `Source/Developer/Horde/Public/Compute/ComputeChannel.h` (Public)


#### class `FComputeChannel`  
`class FComputeChannel`  
_L13-37_
- desc: Allows bi-directional communication between two nodes using compute buffers
- L17 _public member_ `FComputeBufferReader Reader;` — Reader for the channel
- L20 _public member_ `FComputeBufferWriter Writer;` — Writer for the channel
- L22 _public prototype_ `FComputeChannel();`
- L23 _public prototype_ `FComputeChannel(FComputeBufferReader InReader, FComputeBufferWriter InWriter);`
- L24 _public prototype_ `~FComputeChannel();`
- L27 _public prototype_ `bool IsValid() const;` — Tests whether the channel is valid
- L30 _public prototype_ `size_t Send(const void* Data, size_t Size, int TimeoutMs = -1);` — Sends bytes to the remote.
- L33 _public prototype_ `size_t Recv(void* Data, size_t Size, int TimeoutMs = -1);` — Reads as many bytes as are available from the socket.
- L36 _public prototype_ `void MarkComplete();` — Indicate to the remote that no more data will be sent.

### `Source/Developer/Horde/Public/Compute/ComputeSocket.h` (Public)


#### class `FComputeSocket`  
`class FComputeSocket`  
_L15-38_
- desc: Connection to a remote machine that multiplexes data into and out-of multiple buffers attached to different channel numbers.
- L18 _public prototype_ `FComputeSocket();`
- L19 _public prototype_ `virtual ~FComputeSocket();`
- L21 _public prototype_ `FComputeSocket(const FComputeSocket&) = delete;`
- L22 _public prototype_ `FComputeSocket& operator=(const FComputeSocket&) = delete;`
- L25 _public prototype_ `virtual void StartCommunication() = 0;` — Begins communication with the agent
- L28 _public prototype_ `virtual void AttachRecvBuffer(int ChannelId, FComputeBuffer RecvBuffer) = 0;` — Attaches a new buffer for receiving data
- L31 _public prototype_ `virtual void AttachSendBuffer(int ChannelId, FComputeBuffer SendBuffer) = 0;`
- L34 _public prototype_ `TSharedPtr<FComputeChannel> CreateChannel(int ChannelId, bool Anonymous = false);` — Attaches a channel to this socket
- L37 _public prototype_ `TSharedPtr<FComputeChannel> CreateChannel(int ChannelId, FComputeBuffer RecvBuffer, FComputeBuffer SendBuffer);` — Attaches a channel to this socket

#### class `FWorkerComputeSocket`  
`class FWorkerComputeSocket final : public FComputeSocket`  
_L44-86_
- inherits: `FComputeSocket`
- desc: Socket used by a worker process to communicate with a host running on the same machine using shared memory to attach new buffers.
- L47 _public member_ `static const char* const IpcEnvVar;`
- L49 _public prototype_ `FWorkerComputeSocket();`
- L50 _public prototype_ `~FWorkerComputeSocket();`
- L53 _public prototype_ `bool Open();` — Opens a connection to the agent process using a command buffer read from an environment variable (EnvVarName)
- L56 _public prototype_ `bool Open(const char* CommandBufferName);` — Opens a connection to the agent process using a specific command buffer name
- L59 _public prototype_ `void Close();` — Close the current connection
- L62 _public prototype_ `virtual void StartCommunication() override;`
- L65 _public prototype_ `virtual void AttachRecvBuffer(int ChannelId, FComputeBuffer RecvBuffer) override;` — Attaches a new buffer for receiving data
- L68 _public prototype_ `virtual void AttachSendBuffer(int ChannelId, FComputeBuffer SendBuffer) override;` — Attaches a new buffer for sending data
- L71 _public prototype_ `static void RunServer(FComputeBufferReader& CommandBufferReader, FComputeSocket& Socket);` — Reads and handles a command from the command buffer
- L76 _private member_ `FComputeBufferWriter CommandBufferWriter;`
- L77 _private member_ `std::vector<FComputeBuffer> Buffers;`
- L79 _private prototype_ `void AttachBuffer(int ChannelId, EMessageType Type, const char* Name);`
- L81 _private prototype_ `static size_t ReadVarUInt(const unsigned char* Pos, unsigned int* OutValue);`
- L82 _private prototype_ `static size_t ReadString(const unsigned char* Pos, char* OutText, size_t OutTextMaxLen);`
- L84 _private prototype_ `static size_t WriteVarUInt(unsigned char* Pos, unsigned int Value);`
- L85 _private prototype_ `static size_t WriteString(unsigned char* Pos, const char* Text);`

#### enum `EComputeSocketEndpoint`  
`enum class EComputeSocketEndpoint`  
_L91-98_
- desc: Enum identifying which end of the socket a particular machine is
- L94 _public enumerator_ `Local` — The initiating machine
- L97 _public enumerator_ `Remote` — The remote machine

#### Free symbols / members of external scopes

- L101 _prototype_ `TUniquePtr<FComputeSocket> CreateComputeSocket(TUniquePtr<FComputeTransport> Transport, EComputeSocketEndpoint Endpoint);` — Creates a socket using a custom transport. Also returns the default channel (channel 0)

### `Source/Developer/Horde/Public/Compute/ComputeTransport.h` (Public)


#### class `FComputeTransport`  
`class FComputeTransport`  
_L11-36_
- desc: Interface for a transport mechanism that can be used by a compute socket
- L14 _public prototype_ `virtual ~FComputeTransport();`
- L17 _public prototype_ `virtual bool IsValid() const = 0;` — Returns true if this compute transport channel has been successfully established.
- L20 _public prototype_ `virtual size_t Send(const void* Data, size_t Size) = 0;` — Sends data to the remote
- L23 _public prototype_ `virtual size_t Recv(void* Data, size_t Size) = 0;` — Receives data from the remote
- L26 _public prototype_ `virtual void MarkComplete() = 0;` — Indicates to the remote that no more data will be sent.
- L29 _public prototype_ `virtual void Close() = 0;` — Indicates that no more data will be sent or received, and that any blocking reads/writes should stop.
- L32 _public prototype_ `bool SendMessage(const void* Data, size_t Size);` — Sends data to the remote, blocking until the entire message has been sent.
- L35 _public prototype_ `bool RecvMessage(void* Data, size_t Size);` — Receives a fixed length block of data from the remote, blocking until the entire length has been received.

#### class `FBufferTransport`  
`class FBufferTransport final : public FComputeTransport`  
_L41-56_
- inherits: `FComputeTransport`
- desc: Implementation of FComputeTransport which uses in-memory buffers to transport data
- L44 _public prototype_ `FBufferTransport(FComputeBufferWriter InSendBufferWriter, FComputeBufferReader InRecvBufferReader);`
- L47 _protected prototype_ `virtual bool IsValid() const override final;`
- L48 _protected prototype_ `virtual size_t Send(const void* Data, size_t Size) override final;`
- L49 _protected prototype_ `virtual size_t Recv(void* Data, size_t Size) override final;`
- L50 _protected prototype_ `virtual void MarkComplete() override final;`
- L51 _protected prototype_ `virtual void Close() override final;`
- L54 _private member_ `FComputeBufferWriter SendBufferWriter;`
- L55 _private member_ `FComputeBufferReader RecvBufferReader;`

### `Source/Developer/Horde/Public/Horde.h` (Public)


#### struct `FHorde`  
`struct FHorde`  
_L11-26_
- L14 _public prototype_ `static bool GetServerUrl(FString& OutUrl, FString* OutUrlConfigSource = nullptr);` — Gets the server URL. Equivalent to calling IDesktopPlatform::GetHordeUrl().
- L17 _public prototype_ `static FString GetTemplateName();` — Settings available from the environment when running under a job
- L18 _public prototype_ `static FString GetTemplateId();`
- L19 _public prototype_ `static FString GetServerURL();`
- L20 _public prototype_ `static FString GetJobId();`
- L21 _public prototype_ `static FString GetJobURL();`
- L22 _public prototype_ `static FString GetStepId();`
- L23 _public prototype_ `static FString GetStepURL();`
- L24 _public prototype_ `static FString GetStepName();`
- L25 _public prototype_ `static FString GetBatchId();`

#### Free symbols / members of external scopes

- L6 _macro_ `#define HORDE_API`

### `Source/Developer/Horde/Public/HordeHttpClient.h` (Public)


#### class `FHordeHttpClient`  
`class FHordeHttpClient`  
_L12-40_
- L15 _public prototype_ `FHordeHttpClient(FString InServerUrl);`
- L16 _public prototype_ `~FHordeHttpClient();`
- L18 _public prototype_ `bool Login(bool bUnattended, FFeedbackContext* Warn = nullptr);`
- L20 _public prototype_ `bool LoginWithOidc(const TCHAR* Profile, bool bUnattended, FFeedbackContext* Warn = nullptr);`
- L22 _public prototype_ `bool LoginWithEnvironmentVariable();`
- L24 _public prototype_ `TSharedRef<IHttpRequest> CreateRequest(const TCHAR* Verb, const TCHAR* Path);`
- L25 _public prototype_ `TSharedRef<IHttpResponse> Get(const TCHAR* Path);`
- L28 _public function_ `template<typename T> T Get(const TCHAR* Path)`
- L35 _public prototype_ `static TSharedRef<IHttpResponse> ExecuteRequest(TSharedRef<IHttpRequest> Request);`
- L38 _private member_ `FString ServerUrl;`
- L39 _private member_ `FString Token;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Server/ServerMessages.h` (Public)


#### struct `FGetServerInfoResponse`  
`struct FGetServerInfoResponse : FJsonSerializable`  
_L9-23_
- inherits: `FJsonSerializable`
- desc: Server Info
- L12 _public member_ `FString ServerVersion;` — Server version info
- L15 _public member_ `FString AgentVersion;` — The current agent version string
- L18 _public member_ `FString OsDescription;` — The operating system server is hosted on
- L20 _public prototype_ `FGetServerInfoResponse();`
- L22 _public prototype_ `virtual void Serialize(FJsonSerializerBase& Serializer, bool bFlatObject) override;`

#### struct `FGetAuthConfigResponse`  
`struct FGetAuthConfigResponse : FJsonSerializable`  
_L26-43_
- inherits: `FJsonSerializable`
- desc: Describes the auth config for this server
- L29 _public member_ `FString Method;` — Issuer for tokens from the auth provider
- L32 _public member_ `FString ServerUrl;` — Issuer for tokens from the auth provider
- L35 _public member_ `FString ClientId;` — Client id for the OIDC authority
- L38 _public member_ `TArray<FString> LocalRedirectUrls;` — Optional redirect url provided to OIDC login for external tools (typically to a local server)
- L40 _public prototype_ `FGetAuthConfigResponse();`
- L42 _public prototype_ `virtual void Serialize(FJsonSerializerBase& Serializer, bool bFlatObject) override;`

### `Source/Developer/Horde/Public/SharedBufferView.h` (Public)


#### class `FSharedBufferView`  
`class FSharedBufferView final`  
_L12-33_
- desc: View into a buffer with shared ownership
- L15 _public prototype_ `FSharedBufferView();`
- L16 _public prototype_ `FSharedBufferView(FSharedBuffer InBuffer);`
- L17 _public prototype_ `FSharedBufferView(FSharedBuffer InBuffer, const FMemoryView& InView);`
- L18 _public prototype_ `FSharedBufferView(FSharedBuffer InBuffer, size_t InOffset, size_t InLength);`
- L19 _public prototype_ `~FSharedBufferView();`
- L21 _public prototype_ `static FSharedBufferView Copy(const FMemoryView& View);`
- L23 _public prototype_ `FSharedBufferView Slice(uint64 Offset) const;`
- L24 _public prototype_ `FSharedBufferView Slice(uint64 Offset, uint64 Length) const;`
- L26 _public prototype_ `const unsigned char* GetPointer() const;`
- L27 _public prototype_ `size_t GetLength() const;`
- L28 _public prototype_ `FMemoryView GetView() const;`
- L31 _private member_ `FSharedBuffer Buffer;`
- L32 _private member_ `FMemoryView View;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Blob.h` (Public)


#### struct `FBlob`  
`struct FBlob`  
_L15-28_
- desc: Describes a blob of data in the storage system
- L18 _public member_ `FBlobType Type;` — Type of the blob.
- L21 _public member_ `FSharedBufferView Data;` — Data for the blob.
- L24 _public member_ `TArray<FBlobHandle> References;` — References to other blobs.
- L26 _public prototype_ `FBlob(const FBlobType& InType, FSharedBufferView InData, TArray<FBlobHandle> InReferences);`
- L27 _public prototype_ `~FBlob();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/BlobHandle.h` (Public)


#### class `FBlobHandle`  
`class FBlobHandle : public TSharedPtr<FBlobHandleData>`  
_L19-52_
- inherits: `TSharedPtr<FBlobHandleData>`
- desc: Handle to a blob. Can be used to reference blobs that have not been flushed yet. Implemented as a shared pointer to a FBlobHandleData object.
- L22 _public typedef_ `using Super = TSharedPtr<FBlobHandleData>;`
- L27 _public function_ `FBlobHandle()`
- L30 _public function_ `FBlobHandle(TSharedPtr<FBlobHandleData>&& Other) : TSharedPtr<FBlobHandleData>(Other)`
- L34 _public function_ `FBlobHandle(TSharedRef<FBlobHandleData> Value) : TSharedPtr<FBlobHandleData>(MoveTemp(Value))`
- L39 _public function_ `template<typename T> FBlobHandle(TSharedPtr<T> Value) : TSharedPtr<FBlobHandleData>(StaticCastSharedPtr<FBlobHandleData, T>(MoveTemp(Value)))`
- L44 _public function_ `template<typename T> FBlobHandle(TSharedRef<T> Value) : TSharedPtr<FBlobHandleData>(StaticCastSharedPtr<FBlobHandleData, T>(Value.ToSharedPtr()))`
- L48 _public prototype_ `bool operator==(const FBlobHandle& Other) const;`
- L49 _public prototype_ `bool operator!=(const FBlobHandle& Other) const;`

#### class `TBlobHandle`  
`template<typename T> class TBlobHandle : public FBlobHandle`  
_L58-70_
- inherits: `FBlobHandle`
- desc: Handle to a blob with a particular state representation
- L61 _public function_ `TBlobHandle()`
- L64 _public function_ `TBlobHandle(TSharedRef<T> Other) : FBlobHandle(MoveTemp(Other))`
- L68 _public function_ `T* operator->()`
- L69 _public function_ `const T* operator->() const`

#### class `FBlobHandleData`  
`class FBlobHandleData`  
_L75-115_
- desc: Base interface for a blob.
- L78 _public prototype_ `virtual ~FBlobHandleData();`
- L81 _public prototype_ `virtual const char* GetType() const = 0;` — Gets the type name of this derived blob handle instance.
- L84 _public prototype_ `virtual bool Equals(const FBlobHandleData& Other) const = 0;` — Determines if this blob equals the other.
- L87 _public prototype_ `virtual uint32 GetHashCode() const = 0;` — Gets a hash for this blob.
- L90 _public prototype_ `virtual FBlobHandle GetOuter() const = 0;` — For a blob nested within another blob, gets a handle to the containing blob (eg. For a bundle node, will return the packet. For a bundle packet, will return the bundle. For a bundle or other non-nested blob, returns null.)
- L93 _public prototype_ `virtual FBlob Read() const = 0;` — Reads the blob's data.
- L96 _public prototype_ `virtual FBlobType ReadType() const;` — Gets the type of this blob.
- L99 _public prototype_ `virtual void ReadImports(TArray<FBlobHandle>& OutImports) const;` — Gets the outward references from this blob.
- L102 _public prototype_ `virtual FSharedBufferView ReadBody() const;` — Reads part of the blob, and returns a handle that can be used to access the data.
- L105 _public prototype_ `virtual FSharedBufferView ReadBody(size_t Offset, TOptional<size_t> Length = TOptional<size_t>()) const;` — Reads part of the blob, and returns a handle that can be used to access the data.
- L108 _public prototype_ `FBlobLocator GetLocator() const;` — Gets a locator for this blob, by calling TryAppendLocator recursively.
- L111 _public prototype_ `virtual bool TryAppendIdentifier(FUtf8String& OutBuffer) const = 0;` — Gets an identifier for this blob, relative to its outer.
- L114 _public prototype_ `virtual FBlobHandle GetFragmentHandle(const FUtf8StringView& Fragment) const;` — Gets a handle to a nested blob object.

#### struct `FBlobHandleWithHash`  
`struct FBlobHandleWithHash`  
_L120-129_
- desc: Stores a blob handle along with a hash of the target node.
- L122 _public member_ `FBlobHandle Handle;`
- L123 _public member_ `FIoHash Hash;`
- L125 _public function_ `FBlobHandleWithHash(FBlobHandle InHandle, FIoHash InHash) : Handle(MoveTemp(InHandle)) , Hash(InHash)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/BlobLocator.h` (Public)


#### class `FBlobLocator`  
`class FBlobLocator`  
_L13-46_
- desc: Identifies the location of a blob. Meaning of this string is implementation defined.
- L16 _public prototype_ `FBlobLocator();`
- L17 _public prototype_ `FBlobLocator(FUtf8String InPath);`
- L18 _public prototype_ `FBlobLocator(const FBlobLocator& InBaseLocator, const FUtf8StringView& InFragment);`
- L19 _public prototype_ `explicit FBlobLocator(const FUtf8StringView& InPath);`
- L22 _public prototype_ `bool IsValid() const;` — Tests whether this locator is valid.
- L25 _public prototype_ `const FUtf8String& GetPath() const;` — Gets the path for this locator.
- L28 _public prototype_ `FBlobLocator GetBaseLocator() const;` — Gets the base locator for this blob.
- L31 _public prototype_ `FUtf8StringView GetFragment() const;` — Gets the path for this locator.
- L34 _public prototype_ `bool CanUnwrap() const;` — Determines if this locator can be unwrapped into an outer locator/fragment pair.
- L37 _public prototype_ `bool TryUnwrap(FBlobLocator& OutLocator, FUtf8StringView& OutFragment) const;` — Split this locator into a locator and fragment.
- L39 _public prototype_ `bool operator==(const FBlobLocator& Other) const;`
- L40 _public prototype_ `bool operator!=(const FBlobLocator& Other) const;`
- L45 _private member_ `FUtf8String Path;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/BlobReader.h` (Public)


#### class `FBlobReader`  
`class FBlobReader`  
_L18-44_
- desc: Reads data from a blob object
- L21 _public prototype_ `FBlobReader(const FBlob& InBlob);`
- L22 _public prototype_ `FBlobReader(int32 InVersion, const FMemoryView& InBuffer, const TArray<FBlobHandle>& InImports);`
- L25 _public prototype_ `int GetVersion() const;` — Gets a version number for the current blob
- L28 _public prototype_ `const unsigned char* GetBuffer() const;` — Gets a pointer to the remaining memory.
- L31 _public prototype_ `FMemoryView GetView() const;` — Gets the remaining memory to read from.
- L34 _public prototype_ `void Advance(size_t Size);` — Advance the current read position.
- L37 _public prototype_ `FBlobHandle ReadImport();` — Reads the next import.
- L40 _private member_ `int32 Version;`
- L41 _private member_ `FMemoryView Buffer;`
- L42 _private member_ `const TArray<FBlobHandle>& Imports;`
- L43 _private member_ `int32 NextImportIdx;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HORDE_API`
- L48 _prototype_ `FBlobHandle ReadBlobHandle(FBlobReader& Reader);`
- L49 _prototype_ `FBlobHandleWithHash ReadBlobHandleWithHash(FBlobReader& Reader);`
- L50 _prototype_ `int ReadInt32(FBlobReader& Reader);`
- L51 _prototype_ `FIoHash ReadIoHash(FBlobReader& Reader);`
- L52 _prototype_ `FMemoryView ReadFixedLengthBytes(FBlobReader& Reader, size_t Length);`
- L53 _prototype_ `size_t ReadUnsignedVarInt(FBlobReader& Reader);`
- L54 _prototype_ `FUtf8String ReadString(FBlobReader& Reader);`
- L55 _prototype_ `FMemoryView ReadStringSpan(FBlobReader& Reader);`

### `Source/Developer/Horde/Public/Storage/BlobType.h` (Public)


#### struct `FBlobType`  
`struct FBlobType`  
_L12-26_
- desc: Identifies the type of a blob
- L14 _public member_ `static const FBlobType Leaf;`
- L17 _public member_ `FGuid Guid;` — Nominal identifier for the type.
- L20 _public member_ `int Version;` — Version number for the serializer.
- L22 _public prototype_ `FBlobType(const FGuid& InGuid, int InVersion);`
- L24 _public prototype_ `bool operator==(const FBlobType& Other) const;`
- L25 _public prototype_ `bool operator!=(const FBlobType& Other) const;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/BlobWriter.h` (Public)


#### class `FBlobWriter`  
`class FBlobWriter`  
_L20-52_
- desc: Interface for writing data to the storage system.
- L23 _public prototype_ `virtual ~FBlobWriter();`
- L26 _public prototype_ `virtual TUniquePtr<FBlobWriter> Fork() = 0;` — Create another writer instance, allowing multiple threads to write in parallel.
- L29 _public prototype_ `virtual void AddAlias(const FAliasInfo& AliasInfo) = 0;` — Adds an alias for the current blob.
- L32 _public prototype_ `virtual void AddImport(FBlobHandle Target) = 0;` — Adds a reference to another blob.
- L35 _public prototype_ `void AddRef(const FRefName& RefName);` — Adds a named reference to the blob being built.
- L36 _public prototype_ `virtual void AddRef(const FRefName& RefName, const FRefOptions& Options) = 0;`
- L39 _public prototype_ `void* GetOutputBuffer(size_t Size);` — Gets a block of memory of the given size.
- L42 _public prototype_ `virtual FMutableMemoryView GetOutputBufferAsSpan(size_t UsedSize, size_t DesiredSize) = 0;` — Gets a block of memory, at least the given size.
- L45 _public prototype_ `virtual void Advance(size_t Size) = 0;` — Advance the current write position.
- L48 _public prototype_ `virtual FBlobHandle CompleteBlob(const FBlobType& InType) = 0;` — Finish writing a blob that has been written into the output buffer.
- L51 _public prototype_ `virtual void Flush() = 0;` — Flush any pending nodes to storage.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HORDE_API`
- L56 _prototype_ `void WriteBlobHandle(FBlobWriter& Writer, FBlobHandle Handle);`
- L57 _prototype_ `void WriteBlobHandleWithHash(FBlobWriter& Writer, FBlobHandleWithHash Target);`
- L59 _prototype_ `void WriteIoHash(FBlobWriter& Writer, const struct FIoHash& Hash);`
- L61 _prototype_ `void WriteFixedLengthBytes(FBlobWriter& Writer, const void* Data, size_t Length);`
- L62 _prototype_ `void WriteFixedLengthBytes(FBlobWriter& Writer, const FMemoryView& View);`
- L64 _prototype_ `size_t MeasureUnsignedVarInt(size_t Value);`
- L65 _prototype_ `size_t WriteUnsignedVarInt(void* Buffer, size_t Value);`
- L66 _prototype_ `void WriteUnsignedVarIntWithKnownLength(void* Buffer, size_t Value, size_t NumBytes);`
- L67 _prototype_ `void WriteUnsignedVarInt(FBlobWriter& Writer, size_t Value);`
- L69 _prototype_ `size_t MeasureString(const char* Text);`
- L70 _prototype_ `size_t MeasureString(const FUtf8StringView& Text);`
- L71 _prototype_ `void WriteString(FBlobWriter& Writer, const char* Text);`
- L72 _prototype_ `void WriteString(FBlobWriter& Writer, const FUtf8StringView& Text);`
- L73 _prototype_ `void WriteString(FBlobWriter& Writer, const FUtf8String& Text);`

### `Source/Developer/Horde/Public/Storage/Bundles/Bundle.h` (Public)


#### enum `EBundleVersion`  
`enum class EBundleVersion : unsigned char`  
_L10-41_
- desc: Bundle version number
- L13 _public enumerator_ `Initial = 0` — Initial version number.
- L16 _public enumerator_ `ExportAliases = 1` — Added the BundleExport.Alias property.
- L19 _public enumerator_ `RemoveAliases = 2` — Back out change to include aliases. Will likely do this through an API rather than baked into the data.
- L22 _public enumerator_ `InPlace = 3` — Use data structures which support in-place reading and writing.
- L25 _public enumerator_ `ImportHashes = 4` — Add import hashes to imported nodes.
- L28 _public enumerator_ `PacketSequence = 5` — Structure bundles as a sequence of self-contained packets (uses V2 code).
- L31 _public enumerator_ `LatestPlusOne` — Last item in the enum. Used for Latest.
- L34 _public enumerator_ `Latest = (int)LatestPlusOne - 1` — The current version number.
- L37 _public enumerator_ `LatestV1 = ImportHashes` — Last version using the V1 pipeline.
- L40 _public enumerator_ `LatestV2 = Latest` — Last version using the V2 pipeline.

#### struct `FBundle`  
`struct FBundle`  
_L46-49_
- desc: General bundle properties
- L48 _public member_ `static const FBlobType BlobType;`

#### struct `FBundleSignature`  
`struct FBundleSignature`  
_L54-68_
- desc: Signature for a bundle
- L57 _public member_ `static const int NumBytes = 8;` — Number of bytes in a serialized signature.
- L60 _public member_ `EBundleVersion Version;` — Version number for the following file data.
- L63 _public member_ `size_t Length;` — Length of the packet, including the length of the signature itself.
- L65 _public prototype_ `FBundleSignature(EBundleVersion InVersion, size_t InLength);`
- L66 _public prototype_ `static FBundleSignature Read(const void* Data);`
- L67 _public prototype_ `void Write(void* Data);`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Bundles/BundleCompression.h` (Public)


#### enum `EBundleCompressionFormat`  
`enum EBundleCompressionFormat : unsigned char`  
_L11-27_
- desc: Indicates the compression format in a bundle
- L14 _public enumerator_ `None = 0` — Packets are uncompressed.
- L17 _public enumerator_ `LZ4 = 1` — LZ4 compression.
- L20 _public enumerator_ `Gzip = 2` — Gzip compression.
- L23 _public enumerator_ `Oodle = 3` — Oodle compression (Kraken).
- L26 _public enumerator_ `Brotli = 4` — Brotli compression.

#### struct `FBundleCompression`  
`struct FBundleCompression`  
_L32-42_
- desc: Utility methods for compressing bundles
- L35 _public prototype_ `static size_t GetMaxSize(EBundleCompressionFormat Format, const FMemoryView& Input);` — Gets the maximum size of the buffer required to compress the given data.
- L38 _public prototype_ `static size_t Compress(EBundleCompressionFormat Format, const FMemoryView& Input, const FMutableMemoryView& Output);` — Compress a data packet.
- L41 _public prototype_ `static void Decompress(EBundleCompressionFormat Format, const FMemoryView& Input, const FMutableMemoryView& Output);` — Decompress a packet of data.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Bundles/BundleOptions.h` (Public)


#### struct `FBundleOptions`  
`struct FBundleOptions`  
_L13-31_
- desc: Options for configuring a bundle serializer
- L16 _public member_ `static const FBundleOptions Default;` — Default options value.
- L19 _public member_ `EBundleVersion MaxVersion = EBundleVersion::LatestV2;` — Maximum version number of bundles to write.
- L22 _public member_ `int MaxBlobSize = 10 * 1024 * 1024;` — Maximum payload size fo a blob.
- L25 _public member_ `EBundleCompressionFormat CompressionFormat = EBundleCompressionFormat::LZ4;` — Compression format to use.
- L28 _public member_ `int MinCompressionPacketSize = 16 * 1024;` — Minimum size of a block to be compressed.
- L30 _public prototype_ `FBundleOptions();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Bundles/V2/BundleWriter.h` (Public)


#### class `FBundleWriter`  
`class FBundleWriter final : public FBlobWriter`  
_L20-58_
- inherits: `FBlobWriter`
- desc: Writes blobs into bundles
- L23 _public prototype_ `FBundleWriter(TSharedRef<FKeyValueStorageClient> InStorageClient, FUtf8String InBasePath, const FBundleOptions& InOptions);`
- L24 _public prototype_ `~FBundleWriter();`
- L27 _public prototype_ `void Flush() override;` — Inherited from FBlobWriter
- L28 _public prototype_ `TUniquePtr<FBlobWriter> Fork() override;`
- L29 _public prototype_ `virtual void AddAlias(const FAliasInfo& AliasInfo) override;`
- L30 _public prototype_ `virtual void AddImport(FBlobHandle Target) override;`
- L31 _public prototype_ `virtual void AddRef(const FRefName& RefName, const FRefOptions& Options) override;`
- L32 _public prototype_ `virtual FBlobHandle CompleteBlob(const FBlobType& InType) override;`
- L33 _public prototype_ `virtual FMutableMemoryView GetOutputBufferAsSpan(size_t UsedSize, size_t DesiredSize) override;`
- L34 _public prototype_ `virtual void Advance(size_t Size) override;`
- L41 _private member_ `TSharedRef<FKeyValueStorageClient> StorageClient;`
- L42 _private member_ `FUtf8String BasePath;`
- L43 _private member_ `FBundleOptions Options;`
- L45 _private member_ `TBlobHandle<FPendingPacketHandleData> CurrentPacketHandle;`
- L46 _private member_ `TUniquePtr<FPacketWriter> PacketWriter;`
- L48 _private member_ `TBlobHandle<FPendingBundleHandleData> CurrentBundleHandle;`
- L49 _private member_ `FChunkedBufferWriter CompressedPacketWriter;`
- L50 _private member_ `TArray<FBlobHandle> CurrentBundleImports;`
- L52 _private member_ `TArray<FBlobHandle> BundleReferences;`
- L56 _private prototype_ `void StartPacket();`
- L57 _private prototype_ `void FinishPacket();`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Bundles/V2/ExportHandle.h` (Public)


#### class `FExportHandleData`  
`class FExportHandleData final : public FBlobHandleData, public TSharedFromThis<FExportHandleData, ESPMode::ThreadSafe>`  
_L19-45_
- inherits: `FBlobHandleData,TSharedFromThis<FExportHandleData,ESPMode::ThreadSafe>`
- desc: Implementation of export handle data.
- L22 _public member_ `static const char Type[];`
- L24 _public prototype_ `FExportHandleData(FPacketHandle InPacket, int32 InExportIdx);`
- L25 _public prototype_ `FExportHandleData(FPacketHandle InPacket, const FUtf8StringView& InFragment);`
- L26 _public prototype_ `~FExportHandleData();`
- L28 _public prototype_ `static void AppendIdentifier(FUtf8String& OutBuffer, int32 ExportIdx);`
- L31 _public prototype_ `virtual bool Equals(const FBlobHandleData& Other) const override;` — Implementation of FBlobHandle
- L32 _public prototype_ `virtual uint32 GetHashCode() const override;`
- L33 _public prototype_ `virtual FBlobHandle GetOuter() const override;`
- L34 _public prototype_ `virtual const char* GetType() const override;`
- L35 _public prototype_ `virtual FBlob Read() const override;`
- L36 _public prototype_ `virtual bool TryAppendIdentifier(FUtf8String& OutBuffer) const override;`
- L39 _private member_ `static const FUtf8StringView FragmentPrefix;`
- L41 _private member_ `FPacketHandle Packet;`
- L42 _private member_ `int32 ExportIdx;`
- L44 _private prototype_ `static bool TryParse(const FUtf8StringView& Fragment, int32& OutExportIdx);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HORDE_API`
- L14 _typedef_ `typedef TBlobHandle<FExportHandleData> FExportHandle;` — Handle to an export within a packet.

### `Source/Developer/Horde/Public/Storage/Bundles/V2/Packet.h` (Public)


#### class `FPacket`  
`class FPacket`  
_L20-62_
- desc: Accessor for data structures stored into a serialized bundle packet.
- L23 _public member_ `static const FBlobType BlobType;`
- L25 _public prototype_ `FPacket(FSharedBufferView InBuffer);`
- L26 _public prototype_ `virtual ~FPacket();`
- L29 _public prototype_ `FSharedBufferView GetBuffer() const;` — Gets the underlying buffer for this packet.
- L32 _public prototype_ `size_t GetLength() const;` — Length of this packet.
- L35 _public prototype_ `size_t GetTypeCount() const;` — Gets the number of types in this packet.
- L38 _public prototype_ `const FBlobType& GetType(size_t TypeIdx) const;` — Gets a type from the packet.
- L41 _public prototype_ `size_t GetImportCount() const;` — Gets the number of imports in this packet.
- L44 _public prototype_ `FPacketImport GetImport(size_t ImportIdx) const;` — Gets the locator for a particular import.
- L47 _public prototype_ `size_t GetExportCount() const;` — Gets the number of exports in this packet.
- L50 _public prototype_ `FPacketExport GetExport(size_t ExportIdx) const;` — Gets the bulk data for a particular export.
- L53 _public prototype_ `void Encode(EBundleCompressionFormat Format, FChunkedBufferWriter& Writer);` — Encodes a packet.
- L56 _public prototype_ `static FPacket Decode(const FMemoryView& View);` — Decodes a packet from the given data.
- L61 _private member_ `FSharedBufferView Buffer;`

#### struct `FPacketImport`  
`struct FPacketImport`  
_L67-86_
- desc: Specifies the path to an imported node
- L69 _public member_ `static constexpr int32 Bias = 3;`
- L70 _public member_ `static constexpr int32 InvalidBaseIdx = -1;`
- L71 _public member_ `static constexpr int32 CurrentPacketBaseIdx = -2;`
- L72 _public member_ `static constexpr int32 CurrentBundleBaseIdx = -3;`
- L74 _public prototype_ `FPacketImport(const FMemoryView& InView);`
- L75 _public prototype_ `FPacketImport(int32 InBaseIdx, const FUtf8StringView& InFragment);`
- L78 _public prototype_ `int GetBaseIdx() const;` — Gets the index of the base packet import.
- L81 _public prototype_ `FUtf8StringView GetFragment() const;` — Gets the fragment for this import.
- L84 _private member_ `int32 BaseIdx;`
- L85 _private member_ `FUtf8StringView Fragment;`

#### struct `FPacketExport`  
`struct FPacketExport`  
_L91-109_
- desc: Data for an exported node in a packet
- L93 _public prototype_ `FPacketExport(FSharedBufferView InBuffer);`
- L94 _public prototype_ `~FPacketExport();`
- L97 _public prototype_ `size_t GetTypeIndex() const;` — Gets the index of this export's type.
- L100 _public prototype_ `void GetImportIndices(TArray<size_t>& OutIndices) const;` — Gets the import indexes for this export.
- L103 _public prototype_ `FSharedBufferView GetPayload() const;` — Gets the payload for this export.
- L106 _private member_ `FSharedBufferView Buffer;`
- L107 _private member_ `int32 TypeIdx;`
- L108 _private member_ `FMemoryView Imports;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Bundles/V2/PacketHandle.h` (Public)


#### class `FPacketHandleData`  
`class FPacketHandleData final : public FBlobHandleData, public TSharedFromThis<FPacketHandleData, ESPMode::ThreadSafe>`  
_L21-59_
- inherits: `FBlobHandleData,TSharedFromThis<FPacketHandleData,ESPMode::ThreadSafe>`
- desc: Data for FPacketHandle
- L24 _public member_ `static const char Type[];`
- L26 _public prototype_ `FPacketHandleData(TSharedRef<FStorageClient> InStorageClient, FBlobHandle InBundle, size_t InPacketOffset, size_t InPacketLength);`
- L27 _public prototype_ `FPacketHandleData(TSharedRef<FStorageClient> InStorageClient, FBlobHandle InBundle, const FUtf8StringView& InFragment);`
- L28 _public prototype_ `~FPacketHandleData();`
- L31 _public prototype_ `FBlob ReadExport(size_t ExportIdx) const;` — Reads an export from this packet.
- L34 _public prototype_ `FSharedBufferView ReadExportBody(size_t ExportIdx) const;` — Reads an export body from this packet.
- L37 _public prototype_ `virtual bool Equals(const FBlobHandleData& Other) const override;` — Implementation of FBlobHandle
- L38 _public prototype_ `virtual uint32 GetHashCode() const override;`
- L39 _public prototype_ `virtual FBlobHandle GetOuter() const override;`
- L40 _public prototype_ `virtual const char* GetType() const override;`
- L41 _public prototype_ `virtual FBlob Read() const override;`
- L42 _public prototype_ `virtual bool TryAppendIdentifier(FUtf8String& OutBuffer) const override;`
- L43 _public prototype_ `virtual FBlobHandle GetFragmentHandle(const FUtf8StringView& Fragment) const override;`
- L46 _private member_ `static const char FragmentPrefix[];`
- L47 _private member_ `static const size_t FragmentPrefixLength;`
- L49 _private member_ `TSharedRef<FStorageClient> StorageClient;`
- L51 _private member_ `FBlobHandle Bundle;`
- L52 _private member_ `size_t PacketOffset;`
- L53 _private member_ `size_t PacketLength;`
- L55 _private member_ `mutable TSharedPtr<FPacketReader> PacketReader;`
- L57 _private prototype_ `const FPacketReader& GetPacketReader() const;`
- L58 _private prototype_ `static bool TryParse(const FUtf8StringView& Fragment, size_t& OutPacketOffset, size_t& OutPacketLength);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HORDE_API`
- L18 _typedef_ `typedef TBlobHandle<FPacketHandleData> FPacketHandle;` — Handle to an packet within a bundle.

### `Source/Developer/Horde/Public/Storage/Bundles/V2/PacketReader.h` (Public)


#### class `FPacketReader`  
`class FPacketReader`  
_L15-38_
- desc: Utility class for constructing BlobData objects from a packet, caching any computed handles to other blobs.
- L18 _public prototype_ `FPacketReader(TSharedRef<FStorageClient> InStorageClient, FBlobHandle InBundleHandle, FPacketHandle InPacketHandle, FPacket InPacket);`
- L19 _public prototype_ `~FPacketReader();`
- L22 _public prototype_ `FBlob ReadPacket() const;` — Read a blob object for the entire packet.
- L25 _public prototype_ `FBlob ReadExport(size_t ExportIdx) const;` — Reads an export from this packet.
- L28 _public prototype_ `FSharedBufferView ReadExportBody(size_t ExportIdx) const;` — Reads an export body from this packet.
- L31 _private member_ `TSharedRef<FStorageClient> StorageClient;`
- L32 _private member_ `FBlobHandle BundleHandle;`
- L33 _private member_ `FPacketHandle PacketHandle;`
- L34 _private member_ `FPacket Packet;`
- L35 _private member_ `mutable TArray<FBlobHandle> CachedImportHandles;`
- L37 _private prototype_ `FBlobHandle GetImportHandle(size_t Index) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Bundles/V2/PacketWriter.h` (Public)


#### class `FPacketWriter`  
`class FPacketWriter`  
_L16-84_
- desc: Writes exports into a new bundle packet
- L19 _public prototype_ `FPacketWriter(FBlobHandle InBundleHandle, FBlobHandle InPacketHandle);`
- L20 _public prototype_ `FPacketWriter(const FPacketWriter&) = delete;`
- L21 _public prototype_ `~FPacketWriter();`
- L24 _public prototype_ `size_t GetLength() const;` — Current length of the packet
- L27 _public prototype_ `void AddImport(FBlobHandle Import);` — Adds an import to the current blob
- L30 _public prototype_ `int GetImportCount() const;` — Gets the number of unique imports current added to this packet
- L33 _public prototype_ `FBlobHandle GetImport(int ImportIdx) const;` — Gets a packet import by index
- L36 _public prototype_ `FMutableMemoryView GetOutputBuffer(size_t UsedSize, size_t DesiredSize);` — Gets data to write new export
- L39 _public prototype_ `void Advance(size_t Size);` — Increase the length of the current blob
- L42 _public prototype_ `int CompleteBlob(const FBlobType& Type);` — Writes a new blob to this packet
- L45 _public prototype_ `int GetExportCount() const;` — Gets the number of exports currently in this packet
- L48 _public prototype_ `FBlob GetExport(int ExportIdx) const;` — Reads data for a blob written to storage
- L51 _public prototype_ `FPacket CompletePacket();` — Mark the current packet as complete
- L53 _public prototype_ `FPacketWriter& operator=(const FPacketWriter&) = delete;`
- L56 _private member_ `FBlobHandle BundleHandle;`
- L57 _private member_ `FBlobHandle PacketHandle;`
- L59 _private member_ `FSharedBuffer Buffer;`
- L60 _private member_ `uint8* BufferBasePtr;`
- L61 _private member_ `size_t Length;`
- L63 _private member_ `size_t NextBlobLength;`
- L64 _private member_ `TArray<int32> NextBlobImports;`
- L66 _private member_ `TArray<FBlobType> Types;`
- L67 _private member_ `TArray<uint32> ImportOffsets;`
- L68 _private member_ `FChunkedBufferWriter ImportWriter;`
- L69 _private member_ `TArray<FBlobHandle> ImportHandles;`
- L70 _private member_ `TMap<FBlobHandle, int> ImportMap;`
- L71 _private member_ `TArray<uint32> ExportOffsets;`
- L73 _private prototype_ `FMutableMemoryView GetOutputBufferInternal(size_t UsedSize, size_t DesiredSize);`
- L74 _private prototype_ `uint8* GetOutputSpanAndAdvance(size_t Length);`
- L76 _private prototype_ `int32 FindOrAddType(FBlobType Type);`
- L77 _private prototype_ `int32 FindOrAddImport(const FBlobHandle& Handle);`
- L79 _private prototype_ `void WriteTypeTable();`
- L80 _private prototype_ `void WriteImportTable();`
- L81 _private prototype_ `void WriteExportTable();`
- L83 _private prototype_ `static size_t Align(size_t Offset);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/ChunkedBufferWriter.h` (Public)


#### class `FChunkedBufferWriter`  
`class FChunkedBufferWriter`  
_L13-47_
- desc: Writes data to a series of memory blocks
- L16 _public prototype_ `FChunkedBufferWriter(size_t InitialSize = 1024);`
- L17 _public prototype_ `FChunkedBufferWriter(const FChunkedBufferWriter&) = delete;`
- L18 _public prototype_ `FChunkedBufferWriter& operator = (const FChunkedBufferWriter&) = delete;`
- L19 _public prototype_ `virtual ~FChunkedBufferWriter();`
- L22 _public prototype_ `void Reset();` — Reset the contents of this writer.
- L25 _public prototype_ `size_t GetLength() const;` — Gets the current written length of this buffer.
- L28 _public prototype_ `FSharedBufferView Slice(size_t Offset, size_t Length) const;` — Get a handle to part of the written buffer
- L31 _public prototype_ `TArray<FMemoryView> GetView() const;` — Gets a view over the underlying buffer.
- L34 _public prototype_ `void CopyTo(void* Buffer) const;` — Copies the entire contents of this writer to another buffer.
- L37 _public prototype_ `FMutableMemoryView GetOutputBuffer(size_t UsedSize, size_t DesiredSize);` — Gets an output buffer for writing.
- L40 _public prototype_ `void Advance(size_t Size);` — Increase the length of the written data.
- L45 _private member_ `TArray<FChunk> Chunks;`
- L46 _private member_ `size_t WrittenLength;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Clients/BundleStorageClient.h` (Public)


#### class `FBundleStorageClient`  
`class FBundleStorageClient final : public FKeyValueStorageClient`  
_L16-47_
- inherits: `FKeyValueStorageClient`
- desc: Base class for an implementation of <see cref="IStorageClient"/>, providing implementations for some common functionality using bundles.
- L19 _public prototype_ `FBundleStorageClient(TSharedRef<FKeyValueStorageClient> InInner);`
- L23 _public prototype_ `virtual FBlob ReadBlob(const FBlobLocator& Locator) const override;` — FKeyValueStorageClient implementation
- L24 _public prototype_ `virtual FBlobHandle WriteBlob(const FUtf8StringView& BasePath, const FBlobType& Type, const TArrayView<FMemoryView>& Data, const TArrayView<FBlobHandle>& Imports) override;`
- L27 _public prototype_ `virtual FBlobHandle CreateHandle(const FBlobLocator& Locator) const override;` — FBundleStorageClient implementation
- L28 _public prototype_ `virtual TUniquePtr<FBlobWriter> CreateWriter(FUtf8String BasePath) override;`
- L29 _public prototype_ `TUniquePtr<FBlobWriter> CreateWriter(FUtf8String BasePath, const FBundleOptions& Options);`
- L31 _public prototype_ `virtual void AddAlias(const char* Name, FBlobAlias Alias) override;`
- L32 _public prototype_ `virtual void RemoveAlias(const char* Name, FBlobHandle Handle) override;`
- L33 _public prototype_ `virtual void FindAliases(const char* Name, int MaxResults, TArray<FBlobAlias>& OutAliases) override;`
- L35 _public prototype_ `virtual bool DeleteRef(const FRefName& Name) override;`
- L36 _public prototype_ `virtual FBlobHandle ReadRef(const FRefName& Name, const FRefCacheTime& CacheTime) const override;`
- L37 _public prototype_ `virtual void WriteRef(const FRefName& Name, const FBlobHandle& Handle, const FRefOptions& Options) override;`
- L43 _private member_ `TSharedRef<FKeyValueStorageClient> Inner;`
- L45 _private prototype_ `TBlobHandle<FBundleHandleData> CreateBundleHandle(const FBlobLocator& Locator) const;`
- L46 _private prototype_ `FBlobHandle GetFragmentHandle(const FBlobHandle& BundleHandle, const FUtf8StringView& Fragment) const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Clients/FileStorageClient.h` (Public)


#### class `FFileStorageClient`  
`class FFileStorageClient : public FKeyValueStorageClient`  
_L14-40_
- inherits: `FKeyValueStorageClient`
- desc: Implementation of FStorageClient which writes data to files on disk.
- L17 _public prototype_ `FFileStorageClient(std::filesystem::path InRootDir);`
- L18 _public prototype_ `~FFileStorageClient();`
- L20 _public prototype_ `static FBlobLocator ReadRefFromFile(const std::filesystem::path &File);`
- L21 _public prototype_ `static void WriteRefToFile(const std::filesystem::path& File, const FBlobLocator& Locator);`
- L23 _public prototype_ `std::filesystem::path GetBlobFile(const FBlobLocator& Locator) const;`
- L24 _public prototype_ `std::filesystem::path GetRefFile(const FRefName& Name) const;`
- L26 _public prototype_ `virtual void AddAlias(const char* Name, FBlobAlias Alias) override;`
- L27 _public prototype_ `virtual void RemoveAlias(const char* Name, FBlobHandle Handle) override;`
- L28 _public prototype_ `virtual void FindAliases(const char* Name, int MaxResults, TArray<FBlobAlias>& OutAliases) override;`
- L30 _public prototype_ `virtual bool DeleteRef(const FRefName& Name) override;`
- L31 _public prototype_ `virtual FBlobHandle ReadRef(const FRefName& Name, const FRefCacheTime& CacheTime) const override;`
- L32 _public prototype_ `virtual void WriteRef(const FRefName& Name, const FBlobHandle& Handle, const FRefOptions& Options) override;`
- L35 _protected prototype_ `virtual FBlob ReadBlob(const FBlobLocator& Locator) const override;`
- L36 _protected prototype_ `virtual FBlobHandle WriteBlob(const FUtf8StringView& BasePath, const FBlobType& Type, const TArrayView<FMemoryView>& Data, const TArrayView<FBlobHandle>& Imports) override;`
- L39 _private member_ `std::filesystem::path RootDir;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Clients/KeyValueStorageClient.h` (Public)


#### class `FKeyValueStorageClient`  
`class FKeyValueStorageClient : public FStorageClient`  
_L14-29_
- inherits: `FStorageClient`
- desc: Base class for storage clients that wrap a diirect key/value type store without any merging/splitting.
- L18 _public prototype_ `virtual FBlob ReadBlob(const FBlobLocator& Locator) const = 0;` — Read a single blob from the underlying store.
- L21 _public prototype_ `virtual FBlobHandle WriteBlob(const FUtf8StringView& BasePath, const FBlobType& Type, const TArrayView<FMemoryView>& Data, const TArrayView<FBlobHandle>& Imports) = 0;` — Write a single blob to the underlying store.
- L24 _public prototype_ `virtual FBlobHandle CreateHandle(const FBlobLocator& Locator) const override;` — Implementation of FStorageClient
- L25 _public prototype_ `virtual TUniquePtr<FBlobWriter> CreateWriter(FUtf8String BasePath = FUtf8String()) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Clients/MemoryStorageClient.h` (Public)


#### class `FMemoryStorageClient`  
`class FMemoryStorageClient final : public FKeyValueStorageClient`  
_L13-37_
- inherits: `FKeyValueStorageClient`
- desc: Implementation of FStorageClient which stores data in memory.
- L16 _public prototype_ `FMemoryStorageClient();`
- L17 _public prototype_ `~FMemoryStorageClient();`
- L19 _public prototype_ `virtual void AddAlias(const char* Name, FBlobAlias Alias) override;`
- L20 _public prototype_ `virtual void RemoveAlias(const char* Name, FBlobHandle Handle) override;`
- L21 _public prototype_ `virtual void FindAliases(const char* Name, int MaxResults, TArray<FBlobAlias>& OutAliases) override;`
- L23 _public prototype_ `virtual bool DeleteRef(const FRefName& Name) override;`
- L24 _public prototype_ `virtual FBlobHandle ReadRef(const FRefName& Name, const FRefCacheTime& CacheTime) const override;`
- L25 _public prototype_ `virtual void WriteRef(const FRefName& Name, const FBlobHandle& Target, const FRefOptions& Options) override;`
- L28 _protected prototype_ `virtual FBlob ReadBlob(const FBlobLocator& Locator) const override;`
- L29 _protected prototype_ `virtual FBlobHandle WriteBlob(const FUtf8StringView& BasePath, const FBlobType& Type, const TArrayView<FMemoryView>& Data, const TArrayView<FBlobHandle>& Imports) override;`
- L32 _private member_ `mutable FCriticalSection CriticalSection;`
- L34 _private member_ `TMap<FBlobLocator, FBlob> Blobs;`
- L35 _private member_ `TMap<FRefName, FBlobLocator> Refs;`
- L36 _private member_ `TMap<FUtf8String, TArray<FBlobAlias>> Aliases;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Nodes/ChunkNode.h` (Public)


#### struct `FChunkingOptions`  
`struct FChunkingOptions`  
_L20-27_
- L22 _public member_ `static const FChunkingOptions Default;`
- L24 _public member_ `int32 MinChunkSize = 4 * 1024;`
- L25 _public member_ `int32 TargetChunkSize = 64 * 1024;`
- L26 _public member_ `int32 MaxChunkSize = 128 * 1024;`

#### class `FChunkNode`  
`class FChunkNode`  
_L32-49_
- desc: Node containing a chunk of data
- L35 _public member_ `static const FBlobType LeafBlobType;`
- L36 _public member_ `static const FBlobType InteriorBlobType;`
- L38 _public member_ `TArray<FBlobHandleWithHash> Children;`
- L39 _public member_ `FSharedBufferView Data;`
- L41 _public prototype_ `FChunkNode();`
- L42 _public prototype_ `FChunkNode(TArray<FBlobHandleWithHash> InChildren, FSharedBufferView InData);`
- L43 _public prototype_ `~FChunkNode();`
- L45 _public prototype_ `static FChunkNode Read(FBlob Blob);`
- L46 _public prototype_ `FBlobHandleWithHash Write(FBlobWriter& Writer) const;`
- L48 _public prototype_ `static FBlobHandleWithHash Write(FBlobWriter& Writer, const TArrayView<const FBlobHandleWithHash>& Children, FMemoryView Data);`

#### class `FChunkNodeReader`  
`class FChunkNodeReader`  
_L54-79_
- desc: Utility class for reading data a data stream from a tree of chunk nodes
- L57 _public prototype_ `FChunkNodeReader(FBlob Blob);`
- L58 _public prototype_ `FChunkNodeReader(const FBlobHandle& Handle);`
- L59 _public prototype_ `~FChunkNodeReader();`
- L61 _public prototype_ `bool IsComplete() const;`
- L62 _public prototype_ `FMemoryView GetBuffer() const;`
- L63 _public prototype_ `void Advance(int32 Length);`
- L65 _public prototype_ `operator bool() const;`
- L78 _private member_ `TArray<FStackEntry> Stack;`

#### struct `FChunkNodeReader::FStackEntry`  
`struct FStackEntry`  
_L68-77_
- L70 _public member_ `FBlob Blob;`
- L71 _public member_ `size_t Position;`
- L73 _public function_ `FStackEntry(FBlob InBlob) : Blob(MoveTemp(InBlob)) , Position(0)`

#### class `FChunkNodeWriter`  
`class FChunkNodeWriter`  
_L84-107_
- desc: Utility class for writing new data to a tree of chunk nodes
- L87 _public prototype_ `FChunkNodeWriter(FBlobWriter& InWriter, const FChunkingOptions& InOptions = FChunkingOptions::Default);`
- L88 _public prototype_ `~FChunkNodeWriter();`
- L90 _public prototype_ `void Write(FMemoryView Data);`
- L92 _public prototype_ `FBlobHandleWithHash Flush(FIoHash& OutStreamHash);`
- L95 _private member_ `FBlobWriter& Writer;`
- L96 _private member_ `const FChunkingOptions& Options;`
- L98 _private member_ `FBuzHash RollingHash;`
- L99 _private member_ `uint32 Threshold;`
- L100 _private member_ `int32 NodeLength;`
- L102 _private member_ `FBlake3 StreamHasher;`
- L104 _private member_ `TArray<FBlobHandleWithHash> Nodes;`
- L106 _private prototype_ `void WriteNode();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Nodes/DirectoryEntry.h` (Public)


#### class `FDirectoryEntry`  
`class FDirectoryEntry`  
_L18-35_
- desc: Entry for a directory within a directory node
- L21 _public member_ `FBlobHandle Target;`
- L22 _public member_ `FIoHash TargetHash;`
- L25 _public member_ `int64 Length;` — Total size of this directory's contents.
- L28 _public member_ `const FUtf8String Name;` — Name of this directory.
- L30 _public prototype_ `FDirectoryEntry(FBlobHandle InTarget, const FIoHash& InTargetHash, FUtf8String InName, int64 InLength);`
- L31 _public prototype_ `~FDirectoryEntry();`
- L33 _public prototype_ `static FDirectoryEntry Read(FBlobReader& Reader);`
- L34 _public prototype_ `void Write(FBlobWriter& Writer) const;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Nodes/DirectoryNode.h` (Public)


#### enum `EDirectoryFlags`  
`enum class EDirectoryFlags`  
_L16-20_
- desc: Flags for a directory node
- L19 _public enumerator_ `None = 0` — No flags specified.

#### class `FDirectoryNode`  
`class FDirectoryNode`  
_L25-39_
- desc: Stores the contents of a directory in a blob
- L28 _public member_ `static const FBlobType BlobType;`
- L30 _public member_ `EDirectoryFlags Flags;`
- L31 _public member_ `TMap<FUtf8String, FFileEntry> NameToFile;`
- L32 _public member_ `TMap<FUtf8String, FDirectoryEntry> NameToDirectory;`
- L34 _public prototype_ `FDirectoryNode(EDirectoryFlags InFlags = EDirectoryFlags::None);`
- L35 _public prototype_ `~FDirectoryNode();`
- L37 _public prototype_ `static FDirectoryNode Read(const FBlob& Blob);`
- L38 _public prototype_ `FBlobHandle Write(FBlobWriter& Writer) const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/Nodes/FileEntry.h` (Public)


#### enum `EFileEntryFlags`  
`enum class EFileEntryFlags`  
_L20-39_
- desc: Flags for a file entry
- L23 _public enumerator_ `None = 0` — No other flags set.
- L26 _public enumerator_ `Executable = 4` — Indicates that the referenced file is executable.
- L29 _public enumerator_ `ReadOnly = 8` — File should be stored as read-only.
- L32 _public enumerator_ `Text = 16` — File contents are utf-8 encoded text. Client may want to replace line-endings with OS-specific format.
- L35 _public enumerator_ `HasCustomData = 32` — Used to indicate that custom data is included in the output. Used internally for serialization; not exposed to users.
- L38 _public enumerator_ `Utf16 = 64` — File should be materialized as UTF-16 (but is stored as a UTF-8 source).

#### class `FFileEntry`  
`class FFileEntry`  
_L46-72_
- desc: Entry for a file within a directory node
- L50 _public member_ `FBlobHandleWithHash Target;` — Handle to the root chunked data node.
- L53 _public member_ `const FUtf8String Name;` — Name of this file.
- L56 _public member_ `EFileEntryFlags Flags;` — Flags for this file.
- L59 _public member_ `int64 Length;` — Length of this file.
- L62 _public member_ `FIoHash Hash;` — Hash of the file.
- L65 _public member_ `FSharedBufferView CustomData;` — Custom user data for this file entry.
- L67 _public prototype_ `FFileEntry(FBlobHandleWithHash InTarget, FUtf8String InName, EFileEntryFlags InFlags, int64 InLength, const FIoHash& InHash, FSharedBufferView InCustomData);`
- L68 _public prototype_ `~FFileEntry();`
- L70 _public prototype_ `static FFileEntry Read(FBlobReader& Reader);`
- L71 _public prototype_ `void Write(FBlobWriter& Writer) const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/RefName.h` (Public)


#### struct `FRefName`  
`struct FRefName`  
_L11-26_
- desc: Identifier for a ref in the storage system. Refs serve as GC roots, and are persistent entry points to expanding data structures within the store.
- L14 _public prototype_ `FRefName(FUtf8String Text);`
- L15 _public prototype_ `~FRefName();`
- L18 _public prototype_ `const FUtf8String& GetText() const;` — Accessor for the underlying string.
- L20 _public prototype_ `bool operator==(const FRefName& Other) const;`
- L21 _public prototype_ `bool operator!=(const FRefName& Other) const;`
- L25 _private member_ `FUtf8String Text;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/RefOptions.h` (Public)


#### struct `FRefOptions`  
`struct FRefOptions`  
_L12-23_
- desc: Options for adding a new ref
- L14 _public member_ `static const FRefOptions Default;`
- L17 _public member_ `FTimespan Lifetime;` — Time until a ref is expired. If zero, the ref does not expire.
- L20 _public member_ `bool bExtend = true;` — Whether to extend the remaining lifetime of a ref whenever it is fetched. Defaults to true.
- L22 _public prototype_ `FRefOptions();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API HORDE_API`

### `Source/Developer/Horde/Public/Storage/StorageClient.h` (Public)


#### struct `FRefCacheTime`  
`struct FRefCacheTime`  
_L22-29_
- desc: Specifies a relative or absolute time value for returning cached ref values
- L24 _public member_ `FDateTime Time;`
- L26 _public prototype_ `FRefCacheTime();`
- L27 _public prototype_ `FRefCacheTime(FTimespan InMaxAge);`
- L28 _public prototype_ `FRefCacheTime(FDateTime InTime);`

#### class `FStorageClient`  
`class FStorageClient : public TSharedFromThis<FStorageClient, ESPMode::ThreadSafe>`  
_L34-80_
- inherits: `TSharedFromThis<FStorageClient,ESPMode::ThreadSafe>`
- desc: Interface for the storage system.
- L37 _public prototype_ `virtual ~FStorageClient();`
- L44 _public prototype_ `virtual FBlobHandle CreateHandle(const FBlobLocator& Locator) const = 0;` — Creates a new blob handle from a blob locator.
- L47 _public prototype_ `virtual TUniquePtr<FBlobWriter> CreateWriter(FUtf8String BasePath = FUtf8String()) = 0;` — Creates a new writer for storage blobs.
- L54 _public prototype_ `virtual void AddAlias(const char* Name, FBlobAlias Alias) = 0;` — Adds an alias to a given blob.
- L57 _public prototype_ `virtual void RemoveAlias(const char* Name, FBlobHandle Handle) = 0;` — Removes an alias from a blob.
- L60 _public prototype_ `virtual void FindAliases(const char* Name, int MaxResults, TArray<FBlobAlias>& OutAliases) = 0;` — Finds blobs with the given alias. Unlike refs, aliases do not serve as GC roots.
- L67 _public prototype_ `virtual bool DeleteRef(const FRefName& Name) = 0;` — Deletes a ref.
- L70 _public prototype_ `virtual FBlobHandle ReadRef(const FRefName& Name, const FRefCacheTime& CacheTime) const = 0;` — Reads data for a ref from the store.
- L73 _public prototype_ `void WriteRef(const FRefName& Name, const FBlobHandle& Handle);` — Writes a new ref to the store.
- L74 _public prototype_ `virtual void WriteRef(const FRefName& Name, const FBlobHandle& Handle, const FRefOptions& Options) = 0;`
- L79 _protected prototype_ `static FBlobLocator CreateLocator(const FUtf8StringView& BasePath);` — Creates a new locator with a particular base path.

#### class `FBlobAlias`  
`class FBlobAlias`  
_L85-99_
- desc: Target for an aliased blob name
- L89 _public member_ `FBlobHandle Target;` — Handle to the target blob for the alias.
- L92 _public member_ `int Rank;` — Rank for the alias.
- L95 _public member_ `FSharedBufferView Data;` — Data stored inline with the alias.
- L97 _public prototype_ `FBlobAlias(FBlobHandle InTarget, int InRank, FSharedBufferView InData);`
- L98 _public prototype_ `~FBlobAlias();`

#### struct `FAliasInfo`  
`struct FAliasInfo`  
_L104-118_
- desc: Alias for newly added blobs
- L107 _public member_ `FUtf8String Name;` — Name of the alias.
- L110 _public member_ `int Rank;` — Rank for ordering aliases (lower values are preferred).
- L113 _public member_ `FSharedBufferView Data;` — Inline data to be stored with the alias.
- L115 _public prototype_ `FAliasInfo(FUtf8String InName, int InRank = 0);`
- L116 _public prototype_ `FAliasInfo(FUtf8String InName, int InRank, FSharedBufferView InData);`
- L117 _public prototype_ `~FAliasInfo();`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API HORDE_API`
