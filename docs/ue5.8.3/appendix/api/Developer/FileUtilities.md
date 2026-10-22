# Developer / FileUtilities

- module root: `Source/Developer/FileUtilities`
- headers: 4; symbols: 45
- symbol kinds: class=2, delegate=1, enum=1, enumerator=3, function=6, macro=1, member=13, namespace=4, prototype=12, struct=2
- PrivateDependencyModuleNames: libzip
- PublicDependencyModuleNames: Core

### `Source/Developer/FileUtilities/Private/ZipArchivePrivate.h` (Private)


#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogZipArchive, Display, Display);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogZipArchive, Display, Display);`

### `Source/Developer/FileUtilities/Public/FileUtilities/ZipArchiveReader.h` (Public)


#### class `FZipArchiveReader`  
`class FZipArchiveReader`  
_L21-41_
- desc: Helper class for reading an uncompressed zip archive file.
- L24 _private member_ `TUniquePtr<FImpl> Impl;`
- L31 _public prototype_ `FZipArchiveReader(IFileHandle* InFileHandle, FOutputDevice* ErrorHandler = nullptr);` — Constructs the ZipArchive to read from a FileHandle. Takes ownership of the FileHandle (even if it is corrupt); it will be closed by the destructor.
- L32 _public prototype_ `~FZipArchiveReader();`
- L34 _public prototype_ `bool IsValid() const;`
- L36 _public prototype_ `TArray<FString> GetFileNames() const;`
- L37 _public prototype_ `bool TryReadFile(FStringView FileName, TArray<uint8>& OutData, FOutputDevice* ErrorHandler = nullptr, UE::FileUtilities::FZipFileMetaData* OutMetadata = nullptr ) const;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace FileUtilities` (scope `UE`)

### `Source/Developer/FileUtilities/Public/FileUtilities/ZipArchiveWriter.h` (Public)


#### enum `EZipArchiveOptions`  
`enum class EZipArchiveOptions : uint8`  
_L21-26_
- L23 _public enumerator_ `None = 0`
- L24 _public enumerator_ `Deflate = 1 << 0`
- L25 _public enumerator_ `RemoveDuplicate = 1 << 1`

#### class `FZipArchiveWriter`  
`class FZipArchiveWriter`  
_L30-80_
- desc: Helper class for generating an uncompressed zip archive file.
- L54 _private member_ `TArray<FFileEntry> Files;`
- L56 _private member_ `TArray<uint8> Buffer;`
- L57 _private member_ `IFileHandle* File;`
- L58 _private member_ `EZipArchiveOptions ZipOptions;`
- L60 _private function_ `inline void Write(uint16 V)`
- L61 _private function_ `inline void Write(uint32 V)`
- L62 _private function_ `inline void Write(uint64 V)`
- L63 _private function_ `inline void Write(void* Src, uint64 Size)`
- L71 _private function_ `inline uint64 Tell()`
- L72 _private prototype_ `void Flush();`
- L75 _public prototype_ `FZipArchiveWriter(IFileHandle* InFile, EZipArchiveOptions InZipOptions = EZipArchiveOptions::None);`
- L76 _public prototype_ `~FZipArchiveWriter();`
- L78 _public prototype_ `void AddFile(const FString& Filename, TConstArrayView<uint8> Data, const FDateTime& Timestamp);`
- L79 _public prototype_ `void AddFile(const FString& Filename, const TArray<uint8>& Data, const FDateTime& Timestamp);`

#### struct `FZipArchiveWriter::FFileEntry`  
`struct FFileEntry`  
_L32-52_
- L34 _public member_ `FString Filename;`
- L35 _public member_ `uint32 Crc32;`
- L36 _public member_ `uint64 Offset;`
- L37 _public member_ `uint32 Time;`
- L38 _public member_ `uint64 CompressedSize;`
- L39 _public member_ `uint64 UnCompressedSize;`
- L40 _public member_ `bool bIsCompress;`
- L42 _public function_ `FFileEntry(const FString& InFilename, uint32 InCrc32, uint64 InOffset, uint32 InTime) : Filename(InFilename) , Crc32(InCrc32) , Offset(InOffset) , Time(InTime) , CompressedSize(0) , UnCompressedSize(0) , bIsCompress(false)`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API FILEUTILITIES_API`
- L27 _prototype_ `ENUM_CLASS_FLAGS(EZipArchiveOptions);`

### `Source/Developer/FileUtilities/Public/FileUtilities/ZipFileMetaData.h` (Public)


#### struct `UE::FileUtilities::FZipFileMetaData`  
`struct FZipFileMetaData`  
_L10-14_
- L13 _public member_ `TOptional<FDateTime> Timestamp;` — The timestamp of the file, if available.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace FileUtilities` (scope `UE`)
