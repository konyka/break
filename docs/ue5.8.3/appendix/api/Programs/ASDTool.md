# Programs / ASDTool

- module root: `Source/Programs/Windows/ASDTool`
- headers: 4; symbols: 113
- symbol kinds: class=4, delegate=1, enum=1, enumerator=2, function=2, member=44, namespace=4, prototype=46, struct=5, typedef=1, variable=3
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, D3D12RHI, PakFile, PakFileUtilities, Projects, RHI, RHICore, RenderCore, SQLiteCore, ShaderCompilerCommon
- PrivateIncludePathModuleNames: Launch, TargetPlatform

### `Source/Programs/Windows/ASDTool/Private/ASDToolCommands.h` (Private)


#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogASDTool, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogASDTool, Log, All);`
- L18 _namespace_ `namespace ASDTool`
- L24 _prototype_ `int32 GenerateSODBs();` (scope `ASDTool`) — Generate State Object Database (.sodb) from cooked shader data.
- L27 _prototype_ `int32 CompilePSDBs();` (scope `ASDTool`) — Compile SODBs into Precompiled Shader Databases (.psdb) via IHV compiler plugins.
- L30 _prototype_ `int32 RegisterPSDBs();` (scope `ASDTool`) — Register PSDBs with the D3D12 shader cache runtime.

### `Source/Programs/Windows/ASDTool/Private/ASDToolShaderUtils.h` (Private)


#### struct `ASDTool::FShaderKeyEntry`  
`struct FShaderKeyEntry`  
_L25-28_
- L27 _public member_ `FShaderHash Hash;`

#### struct `ASDTool::FShaderArchiveEntry`  
`struct FShaderArchiveEntry`  
_L33-51_
- L36 _public member_ `FShaderHash Hash;` — The UE shader output hash
- L39 _public member_ `EShaderFrequency Frequency = SF_NumFrequencies;` — Shader frequency (VS, PS, CS, etc.)
- L44 _public member_ `TArrayView64<const uint8> ShaderCode;` — The raw shader code bytes (after SRT, before optional data). For D3D12 this is the full DXContainer (identified by 'DXBC' magic), which may contain a DXIL part (SM6+) or legacy DXBC bytecode (SM5).
- L47 _public member_ `TArrayView64<const uint8> OptionalData;` — The optional data appended after shader code
- L50 _public member_ `TArray<uint8>* UncompressedBuffer = nullptr;` — Owning buffer for the decompressed data (caller must keep alive during callback)

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace ASDTool`
- L54 _typedef_ `using FShaderVisitor = TFunctionRef<void(FShaderArchiveEntry& Entry)>;` (scope `ASDTool`) — Visitor callback type. Called once per unique matched shader.
- L69 _prototype_ `int32 ProcessArchive( const FString& ArchivePath, const TArray<FShaderKeyEntry>& ShaderKeys, TSet<FShaderHash>& AlreadySeen, FShaderVisitor Visitor, bool bSingleThreaded = false, int32* OutNumNotFound = nullptr, int32* OutNumDuplicates = nullptr );` (scope `ASDTool`) — Open a .ushaderbytecode archive and iterate over all shaders, matching them against the provided sorted SHK key entries. Calls the visitor for each unique, previously-unseen shader. @param ArchivePath       Path to the .ushaderbytecode file @param ShaderKeys        Sorted shader key entries (must be sorted by Hash) @param AlreadySeen       Set of hashes already processed (updated by this function) @param Visitor           Called for each unique shader entry @param bSingleThreaded   If true, process sequentially @param OutNumNotFound    Number of archive shaders not found in SHK data @param OutNumDuplicates  Number of shaders skipped as duplicates @return Number of unique shaders visited
- L90 _prototype_ `const uint8* FindOptionalData( TArrayView64<const uint8> OptionalData, EShaderOptionalDataKey InKey, uint32 ValueSize );` (scope `ASDTool`) — Search the optional data section for a specific key. The OptionalData view must already be trimmed to exactly the optional data bytes, with no trailing size sentinel - as returned by ProcessArchive via DecompressAndExtract. Format: [Key(1 byte), Size(4 bytes), Data(Size bytes), ...] (repeating) @param OptionalData    View into the optional data bytes (trimmed, no trailing size uint32) @param InKey           The key to search for @param ValueSize       Expected size of the value @return Pointer to the value data, or nullptr if not found
- L102 _prototype_ `bool ExtractResourceCounts( TArrayView64<const uint8> OptionalData, FShaderCodePackedResourceCounts& OutCounts );` (scope `ASDTool`) — Extract FShaderCodePackedResourceCounts from shader optional data. @param OptionalData    View into the optional data bytes @param OutCounts       Output resource counts @return true if found and extracted

### `Source/Programs/Windows/ASDTool/Private/ASDToolUtil.h` (Private)


#### struct `ASDTool::FCompressedHeader`  
`struct FCompressedHeader`  
_L47-53_
- desc: Header written at the start of every compressed file.
- L49 _public member_ `uint32 Magic;` — See PSDB_COMPRESSED_MAGIC / SODB_COMPRESSED_MAGIC
- L50 _public member_ `uint32 Version;` — See COMPRESSED_VERSION
- L51 _public member_ `int64 UncompressedSize;`
- L52 _public member_ `int64 CompressedSize;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ASDTool`
- L16 _prototype_ `int32 RunProcess(const FString& ExePath, const FString& Args, FString& OutOutput, bool bLogOutput = false);` (scope `ASDTool`) — Run a process and capture stdout. Returns exit code. If bLogOutput is true, logs lines in real-time with progress-line (\r) handling.
- L34 _prototype_ `FString FindAgilitySDKFile(const FString& Filename);` (scope `ASDTool`) — Returns the absolute path to a named file in the AgilitySDK x64 binaries directory, or empty string if not found. Use for D3D12StateObjectCompiler.exe and .dll.
- L37 _prototype_ `FString FindDefaultCompilerPluginDir();` (scope `ASDTool`) — Returns the absolute path to the default IHV compiler plugin directory, or empty string if not found.
- L55 _variable_ `static constexpr uint32 COMPRESSED_VERSION = 1;` (scope `ASDTool`)
- L59 _variable_ `static constexpr uint32 PSDB_COMPRESSED_MAGIC = (uint32('C') << 24) | (uint32('P') << 16) | (uint32('D') << 8) | uint32('B');` (scope `ASDTool`) — Magic constants use explicit byte shifts rather than multi-character literals to guarantee stable on-disk values regardless of compiler or endianness (multi-char literals are implementation-defined in C++ and should not be used for persisted file format identifiers).
- L60 _variable_ `static constexpr uint32 SODB_COMPRESSED_MAGIC = (uint32('C') << 24) | (uint32('S') << 16) | (uint32('D') << 8) | uint32('B');` (scope `ASDTool`) — Reserved for future SODB compression
- L64 _prototype_ `bool CompressFile(const FString& FilePath, uint32 Magic);` (scope `ASDTool`) — Compress a file with Kraken Optimal2, writing to FilePath + ".oodle". Deletes the original file on success. Returns true on success.
- L68 _prototype_ `bool DecompressFile(const FString& CompressedPath, const FString& OutputPath, uint32 Magic);` (scope `ASDTool`) — Decompress a .oodle file into OutputPath. Creates the output directory if needed. Returns true on success.

### `Source/Programs/Windows/ASDTool/Private/SODBFile.h` (Private)


#### struct `ASDTool::FSODBEntry`  
`struct FSODBEntry`  
_L25-51_
- L27 _public member_ `TArray<uint8> Key;` — Opaque PSO key -- 8 bytes (FShaderHash is FXxHash64, stored big-endian via ToByteArray)
- L28 _public member_ `uint32 Version = 0;`
- L29 _public member_ `TArray<uint8> StreamData;` — Owns the pipeline state stream memory
- L32 _public member_ `bool bIsGraphics = false;` — Whether this is a graphics PSO (vs compute)
- L38 _public member_ `TArray<uint8> StageDXBC[SF_NumStandardFrequencies];` — Per-stage raw DXBC for the direct SQLite read/write path. Both StreamData and StageDXBC can be populated simultaneously (e.g. for compute, StoreComputeShader fills StreamData for the D3D12 API write path and StageDXBC[SF_Compute] for the SQLite write path). Callers should use whichever field is relevant to their write path.
- L40 _public member_ `TArray<uint8> RootSigData;` — Serialized root signature bytes (populated by SQLite read)
- L41 _public member_ `TRefCountPtr<ID3DBlob> RootSigBlob;` — Serialized root signature as ID3DBlob (populated by GenerateSODB)
- L44 _public function_ `D3D12_PIPELINE_STATE_STREAM_DESC GetDesc() const` — Get a D3D12_PIPELINE_STATE_STREAM_DESC pointing into StreamData.

#### struct `ASDTool::FSODBGroup`  
`struct FSODBGroup`  
_L61-91_
- L63 _public member_ `FString Name;`
- L64 _public member_ `TSet<FShaderHash> WantedHashes;`
- L65 _public member_ `TSet<FShaderHash> WrittenHashes;`
- L66 _public member_ `FRWLock WrittenLock;`
- L67 _public member_ `int32 NumFailed = 0;`
- L68 _public member_ `volatile int64 TotalDXILBytes = 0;`
- L71 _public member_ `TArray<FSODBEntry> CollectedEntries;` — Batch-collected entries -- written by WriteSODBFiles.
- L72 _public member_ `FCriticalSection EntriesLock;`
- L75 _public prototype_ `bool Contains(const FShaderHash& Hash) const;` — Check if this group wants the hash. No lock needed -- WantedHashes is immutable after SetupGroups.
- L78 _public prototype_ `bool StoreComputeShader(const FShaderHash& Hash, const uint8* DXBCData, int64 DXBCSize, ID3DBlob* RootSignatureBlob);` — Build an FSODBEntry from compute shader data and add to CollectedEntries. Thread-safe.
- L82 _public prototype_ `bool StoreGraphicsPSO( const FShaderHash& Hash, const TArray<uint8>& DXBC_VS, const TArray<uint8>& DXBC_PS, const TArray<uint8>& DXBC_GS, const TArray<uint8>& DXBC_MS, const TArray<uint8>& DXBC_AS, ID3DBlob* RootSignatureBlob);` — Build an FSODBEntry for a graphics PSO and add to CollectedEntries. Thread-safe. StageDXBC: raw DXBC per stage -- empty arrays for unused stages. VS or MS required (traditional raster or mesh shader pipeline).
- L90 _private prototype_ `bool DeduplicateAndMark(const FShaderHash& Hash);` — Returns true if this is the first time we've seen this hash. Thread-safe.

#### class `ASDTool::FSODBFactory`  
`class FSODBFactory`  
_L98-109_
- L101 _public prototype_ `~FSODBFactory();`
- L103 _public prototype_ `bool Initialize();`
- L104 _public prototype_ `ID3D12StateObjectDatabase* CreateDatabase(const FString& OutputPath);`
- L107 _private member_ `HMODULE D3D12Module = nullptr;`
- L108 _private member_ `ID3D12StateObjectDatabaseFactory* Factory = nullptr;`

#### enum `ASDTool::ESODBOpenMode`  
`enum class ESODBOpenMode : uint8`  
_L115-119_
- L117 _public enumerator_ `Read`
- L118 _public enumerator_ `Write`

#### class `ASDTool::ISODBFile`  
`class ISODBFile`  
_L125-147_
- L128 _public prototype_ `virtual ~ISODBFile() = default;`
- L131 _public prototype_ `virtual bool Open(const FString& Path, ESODBOpenMode Mode) = 0;` — Open an SODB file for reading or writing.
- L134 _public prototype_ `virtual void SetApplicationDesc(const D3D12_APPLICATION_DESC& AppDesc) = 0;` — Set application metadata.
- L137 _public prototype_ `virtual bool WriteEntries(const TArray<FSODBEntry>& Entries) = 0;` — Write all entries to the SODB.
- L140 _public prototype_ `virtual bool ReadEntries(TArray<FSODBEntry>& OutEntries) = 0;` — Read all entries from the SODB.
- L143 _public prototype_ `virtual void Close() = 0;` — Close/finalize the database.
- L146 _public prototype_ `virtual double GetWriteTimeSeconds() const = 0;` — Get timing stats in seconds.

#### class `ASDTool::FD3D12SODBFile`  
`class FD3D12SODBFile : public ISODBFile`  
_L154-174_
- inherits: `ISODBFile`
- L157 _public prototype_ `~FD3D12SODBFile();`
- L160 _public function_ `void SetFactory(FSODBFactory* InFactory)` — Set the factory to use. Must be called before Open().
- L162 _public prototype_ `virtual bool Open(const FString& Path, ESODBOpenMode Mode) override;`
- L163 _public prototype_ `virtual void SetApplicationDesc(const D3D12_APPLICATION_DESC& AppDesc) override;`
- L164 _public prototype_ `virtual bool WriteEntries(const TArray<FSODBEntry>& Entries) override;`
- L165 _public prototype_ `virtual bool ReadEntries(TArray<FSODBEntry>& OutEntries) override;`
- L166 _public prototype_ `virtual void Close() override;`
- L167 _public prototype_ `virtual double GetWriteTimeSeconds() const override;`
- L170 _private member_ `FSODBFactory* Factory = nullptr;`
- L171 _private member_ `ID3D12StateObjectDatabase* Database = nullptr;`
- L172 _private member_ `FString FilePath;`
- L173 _private member_ `volatile int64 WriteCycles = 0;`

#### class `ASDTool::FDirectSODBFile`  
`class FDirectSODBFile : public ISODBFile`  
_L180-211_
- inherits: `ISODBFile`
- L183 _public prototype_ `~FDirectSODBFile();`
- L185 _public prototype_ `virtual bool Open(const FString& Path, ESODBOpenMode Mode) override;`
- L186 _public prototype_ `virtual void SetApplicationDesc(const D3D12_APPLICATION_DESC& AppDesc) override;`
- L187 _public prototype_ `virtual bool WriteEntries(const TArray<FSODBEntry>& Entries) override;`
- L188 _public prototype_ `virtual bool ReadEntries(TArray<FSODBEntry>& OutEntries) override;`
- L189 _public prototype_ `virtual void Close() override;`
- L190 _public prototype_ `virtual double GetWriteTimeSeconds() const override;`
- L193 _private member_ `sqlite3* DB = nullptr;`
- L194 _private member_ `sqlite3_stmt* StmtRootSig = nullptr;`
- L195 _private member_ `sqlite3_stmt* StmtBytecode = nullptr;`
- L196 _private member_ `sqlite3_stmt* StmtPSO = nullptr;`
- L197 _private member_ `sqlite3_stmt* StmtPSO_Graphics = nullptr;`
- L198 _private member_ `sqlite3_stmt* StmtGroup = nullptr;`
- L199 _private member_ `volatile int64 WriteCycles = 0;`
- L200 _private member_ `ESODBOpenMode OpenMode = ESODBOpenMode::Write;`
- L201 _private member_ `FString FilePath;`
- L202 _private member_ `D3D12_APPLICATION_DESC CachedAppDesc = {};`
- L203 _private member_ `FString CachedExeFilename;`
- L204 _private member_ `FString CachedAppName;`
- L205 _private member_ `FString CachedEngineName;`
- L207 _private prototype_ `void Cleanup();`
- L208 _private prototype_ `void ExecSQL(const char* SQL);`
- L209 _private prototype_ `void PrepareSQLite(const char* SQL, sqlite3_stmt** OutStmt);`
- L210 _private prototype_ `void CreateSchema();`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace ASDTool`
- L218 _prototype_ `bool ReadSODBEntries(const FString& SODBPath, TArray<FSODBEntry>& OutEntries);` (scope `ASDTool`) — Read PSO entries from an SODB. Tries D3D12 API path first (.keys manifest), falls back to direct SQLite.
- L222 _prototype_ `bool MergePSDBs(const TArray<FString>& SourcePaths, const FString& DestPath, double& OutMergeSeconds);` (scope `ASDTool`) — Merge N per-thread PSDBs into a single destination PSDB via SQLite ATTACH. All inserts are content-addressed (INSERT OR IGNORE), keyids remapped through key content.
