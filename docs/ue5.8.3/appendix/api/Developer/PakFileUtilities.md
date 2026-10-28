# Developer / PakFileUtilities

- module root: `Source/Developer/PakFileUtilities`
- headers: 2; symbols: 54
- symbol kinds: class=2, function=12, member=23, prototype=16, struct=1
- DynamicallyLoadedModuleNames: DerivedDataCache, Virtualization
- PrivateDependencyModuleNames: Core, IoStoreUtilities, Json, PakFile, Projects, RSA
- PrivateIncludePathModuleNames: DerivedDataCache

### `Source/Developer/PakFileUtilities/Private/SignedArchiveWriter.h` (Private)


#### class `FSignedArchiveWriter`  
`class FSignedArchiveWriter : public FArchive`  
_L13-55_
- inherits: `FArchive`
- desc: Wrapper for writing and signing an archive
- L16 _private member_ `TArray<uint8> Buffer;` — Buffer to sign
- L18 _private member_ `FMemoryWriter BufferArchive;` — Buffer writer
- L20 _private member_ `FArchive& PakWriter;` — The actual pak archive
- L22 _private member_ `FString PakSignaturesFilename;` — The filename of the signature file that accompanies the pak
- L24 _private member_ `int64 SizeOnDisk;` — Size of the archive on disk (including signatures)
- L26 _private member_ `int64 PakSize;` — Data size (excluding signatures)
- L28 _private member_ `const FRSAKeyHandle SigningKey;` — Signing key
- L30 _private member_ `TArray<TPakChunkHash> ChunkHashes;` — Hashes
- L32 _private member_ `TArray<uint8> SignatureData;` — Signature data
- L37 _private prototype_ `void SerializeBufferAndSign();` — Serializes and signs a buffer
- L41 _public prototype_ `FSignedArchiveWriter(FArchive& InPak, const FString& InPakFilename, const FRSAKeyHandle InSigningKey);`
- L42 _public prototype_ `virtual ~FSignedArchiveWriter();`
- L45 _public prototype_ `virtual bool Close() override;` — FArchive interface
- L46 _public prototype_ `virtual void Serialize(void* Data, int64 Length) override;`
- L47 _public prototype_ `virtual int64 Tell() override;`
- L48 _public prototype_ `virtual int64 TotalSize() override;`
- L49 _public prototype_ `virtual void Seek(int64 InPos) override;`
- L51 _public function_ `void SetSignatureData(TArray<uint8>& InSignatureData)`

### `Source/Developer/PakFileUtilities/Public/PakFileUtilities.h` (Public)


#### class `FPakOrderMap`  
`class FPakOrderMap`  
_L28-103_
- desc: Defines the order mapping for files within a pak. When read from the files present in the pak, Indexes will be [0,NumFiles).  This is important for detecting gaps in the order between adjacent files in a patch .pak. For new files being added into the pak, the values can be arbitrary, and will be usable only for relative order in an output list. Due to the arbitrary values for new files, the FPakOrderMap can contain files with duplicate Order values.
- L31 _public function_ `FPakOrderMap() : MaxPrimaryOrderIndex(MAX_uint64) , MaxIndex(0)`
- L36 _public function_ `void Empty()`
- L43 _public function_ `int32 Num() const`
- L49 _public function_ `void Add(const FString& Filename, uint64 Index)` — Add the given filename with the given Sorting Index
- L59 _public function_ `void AddOffset(const FString& Filename, uint64 Offset)` — Add the given filename with the given Offset interpreted as Offset in bytes in the Pak File.  This version of Add is only useful when all Adds are done by offset, and are converted into Sorting Indexes at the end by a call to ConvertOffsetsToOrder
- L66 _public function_ `void ConvertOffsetsToOrder()` — Remaps all the current values in the OrderMap onto [0, NumEntries).  Useful to convert from Offset in Pak file bytes into an Index sorted by Offset
- L86 _public prototype_ `bool ProcessOrderFile(const TCHAR* ResponseFile, bool bSecondaryOrderFile = false, bool bMergeOrder = false, TOptional<uint64> InOffset = {});`
- L89 _public prototype_ `void MergeOrderMap(FPakOrderMap&& Other);` — Merge another order map into this one where the files are not already ordered by this map. Steals the strings and empties the other order map.
- L91 _public prototype_ `uint64 GetFileOrder(const FString& Path, bool bAllowUexpUBulkFallback, bool* OutIsPrimary=nullptr) const;`
- L93 _public prototype_ `void WriteOpenOrder(FArchive* Ar);`
- L95 _public function_ `uint64 GetMaxIndex()`
- L98 _private prototype_ `FString RemapLocalizationPathIfNeeded(const FString& PathLower, FString& OutRegion) const;`
- L100 _private member_ `TMap<FString, uint64> OrderMap;`
- L101 _private member_ `uint64 MaxPrimaryOrderIndex;`
- L102 _private member_ `uint64 MaxIndex;`

#### struct `FPakFooterInfo`  
`struct FPakFooterInfo`  
_L109-142_
- desc: Input and output data for WritePakFooter
- L111 _public function_ `FPakFooterInfo(const TCHAR* InFilename, const FString& InMountPoint, FPakInfo& InInfo, TArray<FPakEntryPair>& InIndex) : Filename(InFilename) , MountPoint(InMountPoint) , Info(InInfo) , Index(InIndex)`
- L118 _public function_ `void SetEncryptionInfo(const FKeyChain& InKeyChain, uint64* InTotalEncryptedDataSize)`
- L123 _public function_ `void SetFileRegionInfo(bool bInFileRegions, TArray<FFileRegion>& InAllFileRegions)`
- L129 _public member_ `const TCHAR* Filename;`
- L130 _public member_ `const FString& MountPoint;`
- L131 _public member_ `FPakInfo& Info;`
- L132 _public member_ `TArray<FPakEntryPair>& Index;`
- L134 _public member_ `const FKeyChain* KeyChain = nullptr;`
- L135 _public member_ `uint64* TotalEncryptedDataSize = nullptr;`
- L136 _public member_ `bool bFileRegions = false;`
- L137 _public member_ `TArray<FFileRegion>* AllFileRegions = nullptr;`
- L139 _public member_ `int64 PrimaryIndexSize = 0;`
- L140 _public member_ `int64 PathHashIndexSize = 0;`
- L141 _public member_ `int64 FullDirectoryIndexSize = 0;`

#### Free symbols / members of external scopes

- L74 _function_ `` (scope `FPakOrderMap::ConvertOffsetsToOrder`)
- L106 _prototype_ `bool ExecuteUnrealPak(const TCHAR* CmdLine);`
- L145 _prototype_ `void WritePakFooter(FArchive& PakHandle, FPakFooterInfo& FooterInfo);` — Write the index and other data at the end of a pak file after all the entries
- L148 _prototype_ `bool SignPakFile(const FString& InPakFilename, const FRSAKeyHandle InSigningKey);` — Take an existing pak file and regenerate the signature file
