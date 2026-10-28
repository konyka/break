# Runtime / BackgroundHTTPFileHash

- module root: `Source/Runtime/Online/BackgroundHTTPFileHash`
- headers: 2; symbols: 39
- symbol kinds: class=1, delegate=1, function=4, member=6, prototype=24, struct=1, typedef=2
- PrivateDependencyModuleNames: BuildSettings
- PublicDependencyModuleNames: Core

### `Source/Runtime/Online/BackgroundHTTPFileHash/Private/BackgroundHttpFileHashPrivate.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBackgroundHttpFileHash, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBackgroundHttpFileHash, Log, All);`

### `Source/Runtime/Online/BackgroundHTTPFileHash/Public/BackgroundHttpFileHashHelper.h` (Public)


#### struct `FURLTempFileMapping`  
`struct FURLTempFileMapping`  
_L11-35_
- desc: Simple data wrapper used to hold a mapping of a URL to the temp file holding the finished download of that URL in the BackgroundHTTP Temp folder
- L14 _public member_ `FString URL;`
- L15 _public member_ `FString TempFilename;`
- L17 _public function_ `FURLTempFileMapping() : URL() , TempFilename()`
- L23 _public function_ `FURLTempFileMapping(const FString& URLIn, const FString& TempFilenameIn) : URL(URLIn) , TempFilename(TempFilenameIn)`
- L30 _public prototype_ `FString ToString() const;` — Creates an FString representation of this FURLTempFileMapping
- L34 _public prototype_ `bool InitFromString(const FString& StringIn);` — Sets the values of this FURLTempFileMapping from the string representation Returns if the parse was successful or not

#### class `FBackgroundHttpFileHashHelper`  
`class FBackgroundHttpFileHashHelper`  
_L44-133_
- desc: Helper that handles generating unique hashed file paths to use store to store BackgroundHTTP work once completed. Can be saved and loaded to/from disk to handle persistence across session when background work is compelted without any usefull program state. NOTE: This is in it's own separate module as some platforms (IOS, etc.) need to include this functionality in ApplicationCore and thus fully adding a dependency to those modules on BackgroundHTTP would not work
- L47 _public function_ `FBackgroundHttpFileHashHelper() : bHasLoadedURLData(false) , bIsDirty(false) , URLFileMappings() , URLFileMappingsLock()`
- L56 _public prototype_ `void LoadData();` — Handles loading URL Mapping data from disk. No operation if data has previously been loaded.
- L59 _public prototype_ `void SaveData();` — Handles saving URL Mapping data to disk. No operation if data isn't dirty
- L62 _public prototype_ `FString ToString() const;` — Creates an FString representation of this FBackgroundHttpFileHashHelper's URL mappings. Used for serializing to/from disk
- L66 _public prototype_ `bool InitFromString(const FString& StringIn);` — Sets the values of this FBackgroundHttpFileHashHelper from the string representation Returns if the parse was successful or not
- L69 _public prototype_ `bool FindTempFilenameMappingForURL(const FString& URL, const FString& RequestID, FString& OutTempFilename) const;` — Looks for a temp filename mapping for the given URL. If one isn't found returns false and does NOT generate one.
- L71 _public prototype_ `const FString* FindTempFilenameMappingForURL(const FString& URL) const;` — `UE_DEPRECATED(5.8, "Please use FindTempFilenameMappingForURL with RequestID and reference out arguments instead")`
- L74 _public prototype_ `const FString& FindOrAddTempFilenameMappingForURL(const FString& URL, const FString& RequestID);` — Looks for a temp filename mapping for the given URL. If one isn't found a new one is generated and returned.
- L77 _public prototype_ `void RemoveURLMapping(const FString& URL, const FString& RequestID);` — Removes URL mapping
- L79 _public function_ `void RemoveURLMapping(const FString& URL)` — `UE_DEPRECATED(5.8, "Please use RemoveURLMapping with RequestID argument instead")`
- L82 _public prototype_ `bool FindMappedURLForTempFilename(const FString& TempFilename, FString& OutMappedURL) const;` — Looks for a URL mapped to the supplied TempFilename. Nullptr returned if one isn't found
- L85 _public prototype_ `const FString* FindMappedURLForTempFilename(const FString& TempFilename) const;` — `UE_DEPRECATED(5.7, "Please use FindMappedURLForTempFilename with reference out argument instead")`
- L88 _public prototype_ `void DeleteURLMappingsWithoutTempFiles();` — Deletes any URLMapping that doesn't have a corresponding Temp file actually on disk.
- L91 _public prototype_ `static const FString& GetTemporaryRootPath();` — Get our base directory used to store Temp files
- L94 _public prototype_ `static const FString& GetTemporaryDownloadPath();` — Get temporary download path
- L97 _public prototype_ `static const FString& GetTempFileExtension();` — Helper function that returns the file extension used by our BackgroundHTTP temp files
- L100 _public prototype_ `static FString GetFullPathOfTempFilename(const FString& TempFilename);` — Helper function that returns a full path representation of the given TempFilename
- L104 _private prototype_ `FString ToStringNoLock() const;` — Same as ToString but doesn't take a lock
- L107 _private prototype_ `bool InitFromStringNoLock(const FString& StringIn);` — Same as InitFromString but doesn't take a lock
- L110 _private prototype_ `static const FString& GetURLMappingFilePathNoLock();` — Helper function that just returns the filepath we use to save/load our URL mapping data
- L113 _private prototype_ `const FURLTempFileMapping* FindMappingForURLNoLock(const FString& URL, const FString& RequestID) const;` — Looks for a temp filename mapping for the given URL. If one isn't found returns nullptr an does NOT generate one.
- L117 _private prototype_ `FString FindValidFilenameHashForURLNoLock(const FString& URL, const FString& RequestID) const;` — Finds the hash that should be used to refer to this URL+RequestID. Either finds the hash used in the map to reference the URLFileMappings entry for this URL+RequestID or returns the hash we should use (the next valid hash entry) without inserting it into the map.
- L120 _private prototype_ `static FString GenerateHashedFilenameForURLNoLock(const FString& URL, const FString& RequestID, uint32 CollisionCount);` — Creates a hashed Filename with a modifier for the given collision count.
- L123 _private member_ `std::atomic<bool> bHasLoadedURLData;` — Used to make sure that we have called LoadData before any operations that depend on it
- L126 _private member_ `std::atomic<bool> bIsDirty;` — Tracks if we have changed data since our last call to SaveData()
- L129 _private member_ `TMap<FString, FURLTempFileMapping> URLFileMappings;` — Stores our FURLTempFileMapping mapped to a Hashed filename
- L132 _private member_ `mutable FRWLock URLFileMappingsLock;` — Access lock for URLFileMappings

#### Free symbols / members of external scopes

- L135 _typedef_ `typedef TSharedRef<FBackgroundHttpFileHashHelper, ESPMode::ThreadSafe> BackgroundHttpFileHashHelperRef;`
- L136 _typedef_ `typedef TSharedPtr<FBackgroundHttpFileHashHelper, ESPMode::ThreadSafe> BackgroundHttpFileHashHelperPtr;`
