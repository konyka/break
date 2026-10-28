# Plugins / DMXZip

- module root: `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXZip`
- headers: 2; symbols: 24
- symbol kinds: class=1, delegate=1, member=7, prototype=14, struct=1
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXZip/Private/DMXZipLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogDMXZip, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogDMXZip, Log, All);`

### `Plugins/VirtualProduction/DMX/DMXGDTF/Source/DMXZip/Public/DMXZipper.h` (Public)


#### class `FDMXZipper`  
`class FDMXZipper : public TSharedFromThis<FDMXZipper>`  
_L37-110_
- inherits: `TSharedFromThis<FDMXZipper>`
- desc: Zip reader/writer for DMX specific Zip Files such as MVR and GDTF. Example of use: bool DoStuffWithZip(const FString& ZipFileName) { FDMXZipper Zipper; Zipper.LoadFromFile(ZipFileName); Zipper.AddFile("hello/world", { 'A', 'B', 'C' }); Zipper.AddFile("test001", { '0', '1', '2', '3', 'X' }, false); Zipper.AddFile("a/b/c/d/e/test002", { 80, 90, 100, 110, 111, 112, 113 }); TArray64<uint8> BigFile; if (FFileHelper::LoadFileToArray(BigFile, TEXT("D:/SM_MatPreviewMesh_01.stl"))) { Zipper.AddFile("Meshes/Mesh.stl", BigFile); } if (!Zipper.SaveToFile(ZipFileName)) { return false; } return true; }
- L42 _public prototype_ `FDMXZipper();` — Constructor
- L45 _public prototype_ `[[nodiscard]] bool LoadFromFile(const FString& Filename);` — Loads the specified zip file
- L48 _public prototype_ `[[nodiscard]] bool LoadFromData(const TArray64<uint8>& Data);` — Loads the data as zip file
- L51 _public prototype_ `[[nodiscard]] bool SaveToFile(const FString& Filename);` — Saves the zip to specified Filename
- L54 _public prototype_ `[[nodiscard]] bool GetData(TArray64<uint8>& OutData);` — Gets the zip as data. Returns true on success
- L57 _public prototype_ `TArray<FString> GetFiles() const;` — Returns the File Names in the Zip. Note, may contain relative paths
- L68 _public prototype_ `void AddFile(const FString& RelativeFilePathAndName, const TArray64<uint8>& Data, const bool bCompress = false);` — Adds a file to the Zip at its Relative File Path and Name. Note, files added this way need to exist on disk until SaveToFile is called. Examples: AddFile("hello/world.txt", { 'A', 'B', 'C' }); AddFile("test001", { '0', '1', '2', '3', 'X' }, false); AddFile("a/b/c/d/e/test002", { 80, 90, 100, 110, 111, 112, 113 });
- L71 _public prototype_ `[[nodiscard]] bool GetFileContent(const FString& Filename, TArray64<uint8>& OutData);` — Gets the Data of a File in the Zip
- L85 _protected prototype_ `[[nodiscard]] bool AddFileInternal(FArrayWriter& Writer, const FString& Path, const TArray64<uint8>& Data, const bool bCompress = true);` — Writes a zipped File to the array writer
- L88 _protected prototype_ `void AddEndOfCentralDirectory(FArrayWriter& Writer);` — Adds an End of Central Directory entry to the zip
- L91 _protected prototype_ `[[nodiscard]] bool Parse();` — Parses the Zip File
- L94 _protected member_ `uint32 SizeOfCentralDirectory = 0;` — The Size of the Central Directory
- L97 _protected member_ `uint32 OffsetOfCentralDirectory = 0;` — The Offset of the Central Directory
- L100 _protected member_ `uint16 TotalNumberOfCentralDirectoryRecords = 0;` — The total number of Central Directory records
- L103 _protected member_ `FArrayReader Reader;` — Array reader handling the data
- L106 _protected member_ `TMap<FString, uint32> OffsetsMap;` — Map of File Names and their Offset
- L109 _protected member_ `TMap<FString, TPair<TArray64<uint8>, bool>> NewFilesToShouldCompressMap;` — Map of Files added to the Zip

#### struct `FDMXZipper::FDMXScopedUnzipToTempFile`  
`struct FDMXScopedUnzipToTempFile`  
_L74-81_
- desc: Helper to unzip a file within the zip as temp file. Deletes the file when running out of scope.
- L76 _public prototype_ `FDMXScopedUnzipToTempFile(const TSharedRef<FDMXZipper>& DMXZipper, const FString& FilenameInZip);`
- L77 _public prototype_ `~FDMXScopedUnzipToTempFile();`
- L80 _public member_ `FString TempFilePathAndName;` — Absolute File Path and Name of the Temp File
