# Developer / Localization

- module root: `Source/Developer/Localization`
- headers: 15; symbols: 654
- symbol kinds: class=20, enum=13, enumerator=41, externvar=1, function=38, macro=11, member=185, namespace=7, prototype=307, struct=25, typedef=6
- PrivateDependencyModuleNames: DesktopPlatform, Json, JsonUtilities, Projects, SourceControl
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Developer/Localization/Public/LocTextHelper.h` (Public)


#### enum `ELocTextHelperLoadFlags`  
`enum class ELocTextHelperLoadFlags : uint8`  
_L31-39_
- desc: Flags controlling the behavior used when loading manifests and archives into FLocTextHelper
- L34 _public enumerator_ `Load = 1<<0` — Attempt to load an existing file, or fail is none is present
- L36 _public enumerator_ `Create = 1<<1` — Attempt to create a new file, potentially replacing an existing file
- L38 _public enumerator_ `LoadOrCreate = Load | Create` — Attempt to load an existing file, or create a new file if none is present

#### enum `ELocTextExportSourceMethod`  
`enum class ELocTextExportSourceMethod : uint8`  
_L43-49_
- desc: What kind of "source" should we use when looking up translations for export?
- L46 _public enumerator_ `SourceText` — Use the source text
- L48 _public enumerator_ `NativeText` — Use the native text

#### enum `ELocTextPlatformSplitMode`  
`enum class ELocTextPlatformSplitMode : uint8`  
_L53-61_
- reflection: `UENUM()`
- desc: How should we split platform specific localization data?
- L56 _public enumerator_ `None` — Don't split platform specific localization data
- L58 _public enumerator_ `Confidential` — Split platform specific localization data for confidential platforms only
- L60 _public enumerator_ `All` — Split platform specific localization data for all platforms

#### class `ILocFileNotifies`  
`class ILocFileNotifies`  
_L67-90_
- desc: Interface for the loc file notify API. This can be used to integrate with services like source control.
- L71 _public prototype_ `virtual ~ILocFileNotifies() = default;` — Virtual destructor
- L74 _public prototype_ `virtual void BeginParallelTasks() = 0;` — Start a block of parallel tasks
- L77 _public prototype_ `virtual void EndParallelTasks() = 0;` — Stop a block of parallel tasks
- L80 _public prototype_ `virtual void PreFileRead(const FString& InFilename) = 0;` — Called prior to reading the given file on disk
- L83 _public prototype_ `virtual void PostFileRead(const FString& InFilename) = 0;` — Called after reading the given file from disk
- L86 _public prototype_ `virtual void PreFileWrite(const FString& InFilename) = 0;` — Called prior to writing the given file to disk
- L89 _public prototype_ `virtual void PostFileWrite(const FString& InFilename) = 0;` — Called after writing the given file to disk

#### struct `FLocTextPlatformSplitUtils`  
`struct FLocTextPlatformSplitUtils`  
_L95-102_
- desc: Utilities to get manage platforms to split.
- L98 _public prototype_ `static bool ShouldSplitPlatformData(const ELocTextPlatformSplitMode& InSplitMode);` — True if the given split mode is actually splitting localization data
- L101 _public prototype_ `static const TArray<FString>& GetPlatformsToSplit(const ELocTextPlatformSplitMode& InSplitMode);` — Get the platforms names that should be split, based on the given split mode

#### enum `EConflictReportFormat`  
`enum class EConflictReportFormat : uint8`  
_L104-109_
- desc: An enum representing all the formats the conflict report can be output in.
- L106 _public enumerator_ `None`
- L107 _public enumerator_ `Txt`
- L108 _public enumerator_ `CSV`

#### class `FLocTextConflicts`  
`class FLocTextConflicts`  
_L114-182_
- desc: Class that tracks any conflicts that occur when gathering source text entries.
- L140 _private typedef_ `typedef TMultiMap<FLocKey, TSharedRef<FConflict>> FConflictMap;`
- L143 _public function_ `FLocTextConflicts()`
- L154 _public prototype_ `void AddConflict(const FLocKey& InNamespace, const FLocKey& InKey, const TSharedPtr<FLocMetadataObject>& InKeyMetadata, const FLocItem& InSource, const FString& InSourceLocation);` — Add a new conflict entry. @param InNamespace			The namespace of the entry. @param InKey					The key/identifier of the entry. @param InKeyMetadata			Entry Metadata keys. @param InSource				The source info for the conflict. @param InSourceLocation		The source location of the conflict.
- L159 _public prototype_ `FString GetConflictReport() const;` — Convert the conflicts to a string format that can be easily saved as a .txt report summary.
- L163 _public prototype_ `FString GetConflictReportAsCSV() const;` — Convert the conflicts to a string format that can be easily saved as a .csv report summary.
- L166 _private prototype_ `FLocTextConflicts(const FLocTextConflicts&) = delete;`
- L167 _private prototype_ `FLocTextConflicts& operator=(const FLocTextConflicts&) = delete;`
- L178 _private prototype_ `TSharedPtr<FConflict> FindEntryByKey(const FLocKey& InNamespace, const FLocKey& InKey, const TSharedPtr<FLocMetadataObject> InKeyMetadata) const;` — Find an existing conflict entry. @param InNamespace			The namespace of the entry. @param InKey					The key/identifier of the entry. @param InKeyMetadata			Entry Metadata keys. @return The entry, or null if there is no current entry for the given key.
- L181 _private member_ `FConflictMap EntriesByKey;`

#### struct `FLocTextConflicts::FConflict`  
`struct FConflict`  
_L118-138_
- desc: Internal conflict item. Maps a source identity to all of its conflicts.
- L121 _public function_ `FConflict(FLocKey InNamespace, FLocKey InKey, TSharedPtr<FLocMetadataObject> InKeyMetadataObj) : Namespace(MoveTemp(InNamespace)) , Key(MoveTemp(InKey)) , KeyMetadataObj(MoveTemp(InKeyMetadataObj))`
- L128 _public function_ `void Add(const FLocItem& Source, const FString& SourceLocation)`
- L133 _public member_ `const FLocKey Namespace;`
- L134 _public member_ `const FLocKey Key;`
- L135 _public member_ `TSharedPtr<FLocMetadataObject> KeyMetadataObj;`
- L137 _public member_ `TMultiMap<FString, FLocItem> EntriesBySourceLocation;`

#### class `FLocTextWordCounts`  
`class FLocTextWordCounts`  
_L187-267_
- desc: Class that manages the word count reporting of the various cultures.
- L216 _public prototype_ `FRowData& AddRow(int32* OutIndex = nullptr);` — Add a new row and get its data. @param OutIndex				Optional value to fill with the index of the new row. @return The row data.
- L225 _public prototype_ `FRowData* GetRow(const int32 InIndex);` — Get the data for a row from its index. @param InIndex				Index of the row to find. @return The row data, or null if no row exists with that index.
- L226 _public prototype_ `const FRowData* GetRow(const int32 InIndex) const;`
- L231 _public prototype_ `int32 GetRowCount() const;` — @return The number of rows in this report.
- L236 _public prototype_ `void TrimReport();` — Trim entries from the report for the cases where the word counts haven't changed between consecutive rows (as ordered by date).
- L246 _public prototype_ `bool FromCSV(const FString& InCSVString, FText* OutError = nullptr);` — Populate this word count report from a CSV string (clears any existing data). @param InCSVString			String containing the CSV data to import. @param OutError				Optional text to be filled when an error occurs. @return True if the CSV string was imported, false otherwise.
- L253 _public prototype_ `FString ToCSV();` — Write this word count report to a CSV string. @return A string containing this report in CSV format.
- L259 _private prototype_ `void SortRowsByDate();` — Sort all the rows by descending date.
- L262 _private member_ `static const FString ColHeadingDateTime;` — Constant column headings for the CSV.
- L263 _private member_ `static const FString ColHeadingWordCount;`
- L266 _private member_ `TArray<FRowData> Rows;` — Array of data for each row.

#### struct `FLocTextWordCounts::FRowData`  
`struct FRowData`  
_L191-207_
- desc: Data representing a single word count row
- L193 _public member_ `FDateTime Timestamp;`
- L194 _public member_ `int32 SourceWordCount;`
- L195 _public member_ `TMap<FString, int32> PerCultureWordCounts;`
- L197 _public function_ `FRowData() : Timestamp() , SourceWordCount(0) , PerCultureWordCounts()`
- L204 _public prototype_ `void ResetWordCounts();`
- L206 _public prototype_ `bool IdenticalWordCounts(const FRowData& InOther) const;`

#### class `FLocTextHelper`  
`class FLocTextHelper`  
_L273-1022_
- desc: High-level access to the non-compiled localization resources (manifests and archives) in a way that abstracts some of their quirks. Each instance gives access to a single localization target consisting of a single manifest and several archives (a native archive, and one for each foreign culture).
- L284 _public prototype_ `FLocTextHelper(FString InTargetName, TSharedPtr<ILocFileNotifies> InLocFileNotifies, const ELocTextPlatformSplitMode InPlatformSplitMode = ELocTextPlatformSplitMode::None);` — Construct an empty helper. @note This kind of helper is only suitable for dealing with manifests, *not* archives. @param InLocFileNotifies		Interface for allowing source control integration (may be null). @param InTargetName			The name of the target we're working with (eg, Game). @param InPlatformSplitMode	Should we split localization data per-platform?
- L298 _public prototype_ `FLocTextHelper(FString InTargetPath, FString InManifestName, FString InArchiveName, FString InNativeCulture, TArray<FString> InForeignCultures, TSharedPtr<ILocFileNotifies> InLocFileNotifies, const ELocTextPlatformSplitMode InPlatformSplitMode = ELocTextPlatformSplitMode::None);` — Construct a helper for the given target information. @note Nothing is loaded or created at this point. @param InTargetPath			Path to the localization target (the root of this path should contain the manifest, and the archives should be under culture code directories). @param InManifestName		Name given to the manifest file for this target (eg, Game.manifest). @param InArchiveName			Name given to the archive files for this target (eg, Game.archive). @param InNativeCulture		Culture code of the native culture (eg, en), or an empty string if the native culture is unknown. @param InForeignCultures		Array of culture codes for the foreign cultures (the native culture will be removed from this array if present). @param InLocFileNotifies		Interface for allowing source control integration (may be null). @param InPlatformSplitMode	Should we split localization data per-platform?
- L312 _public prototype_ `FLocTextHelper(TSharedPtr<FInternationalizationManifest> InLoadedManifest, FString InTargetName, FString InTargetPath, FString InNativeCulture, TArray<FString> InForeignCultures, TSharedPtr<ILocFileNotifies> InLocFileNotifies, const ELocTextPlatformSplitMode InPlatformSplitMode = ELocTextPlatformSplitMode::None);` — Initialize helper with already loaded manifest. @note Suitable for dealing with in-memory manifest (but not limited to). @param InLoadedManifest		A pre-loaded manifest for intrusive LocTextHelper initialization. @param InTargetName			The name of the loc target. Used to infer ManifestName and ArchiveName. @param InTargetPath			Path to the localization target the pre-loaded manifest refers or should be saved to. @param InNativeCulture		Culture code of the native culture (eg, en), or an empty string if the native culture is unknown. @param InForeignCultures		Array of culture codes for the foreign cultures (the native culture will be removed from this array if present). @param InLocFileNotifies		Interface for allowing source control integration (may be null). @param InPlatformSplitMode	Should we split localization data per-platform?
- L317 _public prototype_ `bool ShouldSplitPlatformData() const;` — Are we splitting localization data per-platform?
- L322 _public prototype_ `ELocTextPlatformSplitMode GetPlatformSplitMode() const;` — How are we splitting localization data per-platform?
- L327 _public prototype_ `const TArray<FString>& GetPlatformsToSplit() const;` — Get the platforms names that should be split, based on the active split mode.
- L332 _public prototype_ `const FString& GetTargetName() const;` — @return The name of the target we're working with.
- L337 _public prototype_ `const FString& GetTargetPath() const;` — @return The path to the localization target (the root of this path should contain the manifest, and the archives should be under culture code directories).
- L342 _public prototype_ `TSharedPtr<ILocFileNotifies> GetLocFileNotifies() const;` — @return The interface that allows source control integration (may be null).
- L347 _public prototype_ `void SetCopyrightNotice(const FString& InCopyrightNotice);` — Set the optional copyright notice to insert into files that support it.
- L352 _public prototype_ `const FString& GetCopyrightNotice() const;` — @return Get the optional copyright notice to insert into files that support it.
- L357 _public prototype_ `const FString& GetNativeCulture() const;` — @return Get the culture code of the native culture (eg, en), or an empty string if the native culture is unknown.
- L362 _public prototype_ `const TArray<FString>& GetForeignCultures() const;` — @return Get an array of culture codes for the foreign cultures (does not include the native culture).
- L367 _public prototype_ `TArray<FString> GetAllCultures(const bool bSingleCultureMode = false) const;` — @return Get an array of culture codes for all the cultures (native and foreign).
- L372 _public prototype_ `bool HasManifest() const;` — Check to see whether we've loaded the manifest.
- L382 _public prototype_ `bool LoadManifest(const ELocTextHelperLoadFlags InLoadFlags, FText* OutError = nullptr);` — Attempt to load (or create) the manifest file. @param InLoadFlags			Flags controlling whether we should load or create the manifest file. @param OutError				Optional text to be filled when an error occurs. @return True if the file was loaded (or created), false otherwise.
- L393 _public prototype_ `bool LoadManifest(const FString& InManifestFilePath, const ELocTextHelperLoadFlags InLoadFlags, FText* OutError = nullptr);` — Attempt to load (or create) the manifest file from the given file path. @param InManifestFilePath	Full file path to load the manifest from. @param InLoadFlags			Flags controlling whether we should load or create the manifest file. @param OutError				Optional text to be filled when an error occurs. @return True if the file was loaded (or created), false otherwise.
- L402 _public prototype_ `bool SaveManifest(FText* OutError = nullptr) const;` — Attempt to save the manifest file. @param OutError				Optional text to be filled when an error occurs. @return True if the file was saved, false otherwise.
- L412 _public prototype_ `bool SaveManifest(const FString& InManifestFilePath, FText* OutError = nullptr) const;` — Attempt to save the manifest file to the given file path. @param InManifestFilePath	Full file path to save the manifest to. @param OutError				Optional text to be filled when an error occurs. @return True if the file was saved, false otherwise.
- L417 _public prototype_ `void TrimManifest();` — Trim the currently loaded manifest by remove all dependency entries from it.
- L422 _public prototype_ `void SortManifest();` — Sort the currently loaded manifest into a deterministic order (as if it had been serialized and then deserialized from JSON).
- L427 _public prototype_ `bool HasNativeArchive() const;` — Check to see whether we've loaded the native archive.
- L439 _public prototype_ `bool LoadNativeArchive(const ELocTextHelperLoadFlags InLoadFlags, FText* OutError = nullptr);` — Attempt to load (or create) the native archive file. @note This requires that the native culture was set during construction. @note The manifest must have been loaded prior to loading archives. @param InLoadFlags			Flags controlling whether we should load or create the archive file. @param OutError				Optional text to be filled when an error occurs. @return True if the file was loaded (or created), false otherwise.
- L452 _public prototype_ `bool LoadNativeArchive(const FString& InArchiveFilePath, const ELocTextHelperLoadFlags InLoadFlags, FText* OutError = nullptr);` — Attempt to load (or create) the native archive file from the given file path. @note This requires that the native culture was set during construction. @note The manifest must have been loaded prior to loading archives. @param InArchiveFilePath		Full file path to read the archive from. @param InLoadFlags			Flags controlling whether we should load or create the archive file. @param OutError				Optional text to be filled when an error occurs. @return True if the file was loaded (or created), false otherwise.
- L461 _public prototype_ `bool SaveNativeArchive(FText* OutError = nullptr) const;` — Attempt to save the native archive file. @param OutError				Optional text to be filled when an error occurs. @return True if the file was saved, false otherwise.
- L471 _public prototype_ `bool SaveNativeArchive(const FString& InArchiveFilePath, FText* OutError = nullptr) const;` — Attempt to save the native archive file to the given file path. @param InArchiveFilePath		Full file path to write the archive as. @param OutError				Optional text to be filled when an error occurs. @return True if the file was saved, false otherwise.
- L477 _public prototype_ `bool HasForeignArchive(const FString& InCulture) const;` — Check to see whether we've loaded the given foreign archive. @note This requires that the given culture is in the list of foreign cultures set during construction.
- L490 _public prototype_ `bool LoadForeignArchive(const FString& InCulture, const ELocTextHelperLoadFlags InLoadFlags, FText* OutError = nullptr);` — Attempt to load (or create) a foreign archive file. @note This requires that the given culture is in the list of foreign cultures set during construction. @note The manifest and native archive (if set) must have been loaded prior to loading foreign archives. @param InCulture				Culture code of the archive to load. @param InLoadFlags			Flags controlling whether we should load or create the archive file. @param OutError				Optional text to be filled when an error occurs. @return True if the file was loaded (or created), false otherwise.
- L504 _public prototype_ `bool LoadForeignArchive(const FString& InCulture, const FString& InArchiveFilePath, const ELocTextHelperLoadFlags InLoadFlags, FText* OutError = nullptr);` — Attempt to load (or create) a foreign archive file from the given file path. @note This requires that the given culture is in the list of foreign cultures set during construction. @note The manifest and native archive (if set) must have been loaded prior to loading foreign archives. @param InCulture				Culture code of the archive to load. @param InArchiveFilePath		Full file path to load the archive from. @param InLoadFlags			Flags controlling whether we should load or create the archive file. @param OutError				Optional text to be filled when an error occurs. @return True if the file was loaded (or created), false otherwise.
- L515 _public prototype_ `bool SaveForeignArchive(const FString& InCulture, FText* OutError = nullptr) const;` — Attempt to save a foreign archive file. @note This requires that the given culture is in the list of foreign cultures set during construction. @param InCulture				Culture code of the archive to load. @param OutError				Optional text to be filled when an error occurs. @return True if the file was saved, false otherwise.
- L527 _public prototype_ `bool SaveForeignArchive(const FString& InCulture, const FString& InArchiveFilePath, FText* OutError = nullptr) const;` — Attempt to save a foreign archive file to the given file path. @note This requires that the given culture is in the list of foreign cultures set during construction. @param InCulture				Culture code of the archive to load. @param InArchiveFilePath		Full file path to write the archive as. @param OutError				Optional text to be filled when an error occurs. @return True if the file was saved, false otherwise.
- L532 _public prototype_ `bool HasArchive(const FString& InCulture) const;` — Check to see whether we've loaded the given archive (native or foreign).
- L545 _public prototype_ `bool LoadArchive(const FString& InCulture, const ELocTextHelperLoadFlags InLoadFlags, FText* OutError = nullptr);` — Attempt to load (or create) an archive file (native or foreign). @note This requires that the given culture is in the native culture, or in the list of foreign cultures set during construction. @note The manifest and native archive (if set) must have been loaded prior to loading foreign archives. @param InCulture				Culture code of the archive to load. @param InLoadFlags			Flags controlling whether we should load or create the archive file. @param OutError				Optional text to be filled when an error occurs. @return True if the file was loaded (or created), false otherwise.
- L559 _public prototype_ `bool LoadArchive(const FString& InCulture, const FString& InArchiveFilePath, const ELocTextHelperLoadFlags InLoadFlags, FText* OutError = nullptr);` — Attempt to load (or create) an foreign file (native or foreign) from the given file path. @note This requires that the given culture is is in the native culture, or in the list of foreign cultures set during construction. @note The manifest and native archive (if set) must have been loaded prior to loading foreign archives. @param InCulture				Culture code of the archive to load. @param InArchiveFilePath		Full file path to load the archive from. @param InLoadFlags			Flags controlling whether we should load or create the archive file. @param OutError				Optional text to be filled when an error occurs. @return True if the file was loaded (or created), false otherwise.
- L570 _public prototype_ `bool SaveArchive(const FString& InCulture, FText* OutError = nullptr) const;` — Attempt to save an archive file (native or foreign). @note This requires that the given culture is is in the native culture, or in the list of foreign cultures set during construction. @param InCulture				Culture code of the archive to load. @param OutError				Optional text to be filled when an error occurs. @return True if the file was saved, false otherwise.
- L582 _public prototype_ `bool SaveArchive(const FString& InCulture, const FString& InArchiveFilePath, FText* OutError = nullptr) const;` — Attempt to save an archive file (native or foreign) to the given file path. @note This requires that the given culture is is in the native culture, or in the list of foreign cultures set during construction. @param InCulture				Culture code of the archive to load. @param InArchiveFilePath		Full file path to write the archive as. @param OutError				Optional text to be filled when an error occurs. @return True if the file was saved, false otherwise.
- L593 _public prototype_ `bool LoadAllArchives(const ELocTextHelperLoadFlags InLoadFlags, FText* OutError = nullptr);` — Attempt to load (or create) all archive files. @note The manifest must have been loaded prior to loading archives. @param InLoadFlags			Flags controlling whether we should load or create the archive file. @param OutError				Optional text to be filled when an error occurs. @return True if the files were loaded (or created), false otherwise.
- L602 _public prototype_ `bool SaveAllArchives(FText* OutError = nullptr) const;` — Attempt to save all (native and foreign) archive files. @param OutError				Optional text to be filled when an error occurs. @return True if the file was saved, false otherwise.
- L609 _public prototype_ `void TrimArchive(const FString& InCulture);` — Trim the given archive by remove any entries that no longer exist in the manifest. @param InCulture				Culture code of the archive to load.
- L619 _public prototype_ `bool LoadAll(const ELocTextHelperLoadFlags InLoadFlags, FText* OutError = nullptr);` — Attempt to load (or create) the manifest and all archive files specified during construction. @param InLoadFlags			Flags controlling whether we should load or create the files. @param OutError				Optional text to be filled when an error occurs. @return True if all files were loaded (or created), false otherwise.
- L628 _public prototype_ `bool SaveAll(FText* OutError = nullptr) const;` — Attempt to save the manifest and all archive files specified during construction. @param OutError				Optional text to be filled when an error occurs. @return True if all files were saved, false otherwise.
- L638 _public prototype_ `bool AddDependency(const FString& InDependencyFilePath, FText* OutError = nullptr);` — Attempt to add a manifest dependency. @param InManifestFilePath	Full path to the dependency to load. @param OutError				Optional text to be filled when an error occurs. @return True if the file was load, false otherwise.
- L650 _public prototype_ `TSharedPtr<FManifestEntry> FindDependencyEntry(const FLocKey& InNamespace, const FLocKey& InKey, const FString* InSourceText = nullptr, FString* OutDependencyFilePath = nullptr) const;` — Find an dependency entry using its namespace and key. @param InNamespace			Namespace of the text. @param InKey					Key of the text. @param InSourceText			Optional source text pointer to compare against the source text in the entry. @param OutDependencyFilePath Optional string to fill with the path to the manifest file that contained the matching dependency. @return The entry, or null if it couldn't be found.
- L661 _public prototype_ `TSharedPtr<FManifestEntry> FindDependencyEntry(const FLocKey& InNamespace, const FManifestContext& InContext, FString* OutDependencyFilePath = nullptr) const;` — Find an existing dependency entry using its namespace and context. @param InNamespace			Namespace of the text. @param InContext				Context information for the text (including its key). @param OutDependencyFilePath Optional string to fill with the path to the manifest file that contained the matching dependency @return The entry, or null if it couldn't be found.
- L673 _public prototype_ `bool AddSourceText(const FLocKey& InNamespace, const FLocItem& InSource, const FManifestContext& InContext, const FString* InDescription = nullptr);` — Add a new source text entry to the manifest. @param InNamespace			Namespace of the source text. @param InSource				Source text to add. @param InContext				Context information for the source text (including its key). @param InDescription			Optional description of the source text (for logging). @return Returns true if it was added successfully (or if a matching entry already exists), false if a duplicate entry was found with different text (an identity conflict).
- L681 _public prototype_ `void UpdateSourceText(const TSharedRef<FManifestEntry>& InOldEntry, TSharedRef<FManifestEntry>& InNewEntry);` — Update an existing source text entry in the manifest. @param InOldEntry			Old entry to update. @param InNewEntry			New entry to set.
- L692 _public prototype_ `TSharedPtr<FManifestEntry> FindSourceText(const FLocKey& InNamespace, const FLocKey& InKey, const FString* InSourceText = nullptr) const;` — Find an existing source text entry using its namespace and key. @param InNamespace			Namespace of the source text. @param InKey					Key of the source text. @param InSourceText			Optional source text pointer to compare against the source text in the entry. @return The entry, or null if it couldn't be found.
- L702 _public prototype_ `TSharedPtr<FManifestEntry> FindSourceText(const FLocKey& InNamespace, const FManifestContext& InContext) const;` — Find an existing source text entry using its namespace and context. @param InNamespace			Namespace of the source text. @param InContext				Context information for the source text (including its key). @return The entry, or null if it couldn't be found.
- L710 _public typedef_ `typedef TFunctionRef<bool(TSharedRef<FManifestEntry>)> FEnumerateSourceTextsFuncPtr;` — Enumerate all the source texts in the manifest, optionally skipping those entries from a dependent manifest. @param InCallback			Function to call for each source text. Returns true to continue enumeration. @param InCheckDependencies	True to skip entries that can be found in a dependent manifest, false to include them.
- L711 _public prototype_ `void EnumerateSourceTexts(const FEnumerateSourceTextsFuncPtr& InCallback, const bool InCheckDependencies) const;`
- L721 _public prototype_ `void EnumerateSourceTextsParallel(const FEnumerateSourceTextsFuncPtr& InCallback, const bool InCheckDependencies) const;` — Enumerate in parallel all the source texts in the manifest, optionally skipping those entries from a dependent manifest. InCallback shall be called from multiple threads so it is the calllers responsibility to guarantee thread safety inside the callback's scope. @param InCallback			Function to call for each source text. Returns true to continue enumeration. @param InCheckDependencies	True to skip entries that can be found in a dependent manifest, false to include them.
- L736 _public prototype_ `bool AddTranslation(const FString& InCulture, const FLocKey& InNamespace, const FLocKey& InKey, const TSharedPtr<FLocMetadataObject>& InKeyMetadataObj, const FLocItem& InSource, const FLocItem& InTranslation, const bool InOptional);` — Add a new translation to the given archive. @param InCulture				Culture to add the translation for. @param InNamespace			Namespace of the text. @param InKey					Key of the text. @param InKeyMetadataObj		Meta-data associated with the source text key. @param InSource				Source text to key against. @param InTranslation			Translated text to set. @param InOptional			Is this translation optional? @return Returns true if it was added successfully, false otherwise.
- L746 _public prototype_ `bool AddTranslation(const FString& InCulture, const TSharedRef<FArchiveEntry>& InEntry);` — Add a new translation to the given archive. @param InCulture				Culture to add the translation for. @param InEntry				Archive entry to add. @return Returns true if it was added successfully, false otherwise.
- L760 _public prototype_ `bool UpdateTranslation(const FString& InCulture, const FLocKey& InNamespace, const FLocKey& InKey, const TSharedPtr<FLocMetadataObject>& InKeyMetadataObj, const FLocItem& InSource, const FLocItem& InTranslation);` — Update an existing translation in the given archive. @param InCulture				Culture to update the translation for. @param InNamespace			Namespace of the text. @param InKey					Key of the text. @param InKeyMetadataObj		Meta-data associated with the source text key. @param InSource				Source text to key against. @param InTranslation			Translated text to set. @return Returns true if it was updated successfully, false otherwise.
- L769 _public prototype_ `void UpdateTranslation(const FString& InCulture, const TSharedRef<FArchiveEntry>& InOldEntry, const TSharedRef<FArchiveEntry>& InNewEntry);` — Update an existing translation in the given archive. @param InCulture				Culture to update the translation for. @param InOldEntry			Old entry to update. @param InNewEntry			New entry to set.
- L785 _public prototype_ `bool ImportTranslation(const FString& InCulture, const FLocKey& InNamespace, const FLocKey& InKey, const TSharedPtr<FLocMetadataObject> InKeyMetadataObj, const FLocItem& InSource, const FLocItem& InTranslation, const bool InOptional);` — Import a previously exported translation (generated using GetExportText) back into the archive. This will either update an existing translation, or add a new one if it can't be found. @param InCulture				Culture to update the translation for. @param InNamespace			Namespace of the text. @param InKey					Key of the text. @param InKeyMetadataObj		Meta-data associated with the source text key. @param InSource				Source text to key against. @param InTranslation			Translated text to set. @param InOptional			Is this translation optional? @return Returns true if it was imported successfully, false otherwise.
- L797 _public prototype_ `TSharedPtr<FArchiveEntry> FindTranslation(const FString& InCulture, const FLocKey& InNamespace, const FLocKey& InKey, const TSharedPtr<FLocMetadataObject> InKeyMetadataObj) const;` — Find an existing translation entry from its source text. @param InCulture				Culture to find the translation for. @param InNamespace			Namespace of the text. @param InKey					Key of the text. @param InKeyMetadataObj		Meta-data associated with the source text key. @return The entry, or null if it couldn't be found.
- L807 _public typedef_ `typedef TFunctionRef<bool(TSharedRef<FArchiveEntry>)> FEnumerateTranslationsFuncPtr;` — Enumerate all the translations for the given culture. @note This only enumerates translations that have a source in the manifest. @param InCulture				Culture to enumerate the translation for. @param InCallback			Function to call for each translation. Returns true to continue enumeration. @param InCheckDependencies	True to skip entries that can be found in a dependent manifest, false to include them.
- L808 _public prototype_ `void EnumerateTranslations(const FString& InCulture, const FEnumerateTranslationsFuncPtr& InCallback, const bool InCheckDependencies) const;`
- L822 _public prototype_ `void GetExportText(const FString& InCulture, const FLocKey& InNamespace, const FLocKey& InKey, const TSharedPtr<FLocMetadataObject> InKeyMetadataObj, const ELocTextExportSourceMethod InSourceMethod, const FLocItem& InSource, FLocItem& OutSource, FLocItem& OutTranslation) const;` — Given some source text, work out which text should be exported (eg, when exporting to PO). @param InCulture				Culture to find the translation for. @param InNamespace			Namespace of the text. @param InKey					Key of the text. @param InKeyMetadataObj		Meta-data associated with the source text key. @param InSourceMethod		What kind of "source" should we use when looking up translations? @param InSource				The raw source text to use as a fallback. @param OutSource				The source to export. @param OutTranslation		The translation to export.
- L836 _public prototype_ `void GetRuntimeText(const FString& InCulture, const FLocKey& InNamespace, const FLocKey& InKey, const TSharedPtr<FLocMetadataObject> InKeyMetadataObj, const ELocTextExportSourceMethod InSourceMethod, const FLocItem& InSource, FLocItem& OutTranslation, const bool bSkipSourceCheck) const;` — Given some source text, work out which text is our current "best" translation (eg, when compiling to LocRes). @param InCulture				Culture to find the translation for. @param InNamespace			Namespace of the text. @param InKey					Key of the text. @param InKeyMetadataObj		Meta-data associated with the source text key. @param InSourceMethod		What kind of "source" should we use when looking up translations? @param InSource				The raw source text to use as a fallback. @param OutTranslation		The translation to use. @param bSkipSourceCheck		True to skip the source check and just return any matching translation.
- L847 _public prototype_ `void AddConflict(const FLocKey& InNamespace, const FLocKey& InKey, const TSharedPtr<FLocMetadataObject>& InKeyMetadata, const FLocItem& InSource, const FString& InSourceLocation);` — Add a new conflict entry. @param InNamespace			The namespace of the entry. @param InKey					The key/identifier of the entry. @param InKeyMetadata			Entry Metadata keys. @param InSource				The source info for the conflict. @param InSourceLocation		The source location of the conflict.
- L852 _public prototype_ `FString GetConflictReport() const;` — Get a conflict report that can be easily saved as a report summary.
- L864 _public prototype_ `bool SaveConflictReport(const FString& InReportFilePath, EConflictReportFormat InConflictReportFormat, FText* OutError = nullptr) const;` — Save the conflict report summary to disk. @param InReportFilePath		Full file path to write the report to. @param InConflictReportFormat		The format the conflict report should be generated in. @param OutError				Optional text to be filled when an error occurs. @return True if the file was saved, false otherwise.
- L874 _public prototype_ `FLocTextWordCounts GetWordCountReport(const FDateTime& InTimestamp, const TCHAR* InBaseReportFilePath = nullptr) const;` — Get a word count report for the current state of the manifest and archives. @param InTimestamp			Timestamp to use when adding this entry to the report. @param InBaseReportFilePath	Optional string containing the file path to a report we should use as a base for this one (loads that data before adding ours to it). @return The word count report.
- L885 _public prototype_ `bool SaveWordCountReport(const FDateTime& InTimestamp, const FString& InReportFilePath, FText* OutError = nullptr) const;` — Save the word count report for the current state of the manifest and archives to disk. @param InTimestamp			Timestamp to use when adding this entry to the report. @param InReportFilePath		Full file path to write the report to (also loads any existing report data from this path before adding ours to it). @param OutError				Optional text to be filled when an error occurs. @return True if the file was saved, false otherwise.
- L890 _public prototype_ `static FString SanitizeLogOutput(FStringView InString);` — Sanitize any output from the given string that may cause the build machine to generate erroneous errors.
- L891 _public prototype_ `static FString SanitizeLogOutput(FString&& InString);`
- L905 _public prototype_ `bool FindKeysForLegacyTranslation(const FString& InCulture, const FLocKey& InNamespace, const FString& InSource, const TSharedPtr<FLocMetadataObject> InKeyMetadataObj, TArray<FLocKey>& OutKeys) const;` — Given a culture, try and find all the keys that the source string should use by checking the manifest. @note This should only be used to upgrade old non-keyed archive entries when importing legacy data. @param InCulture				Culture to find the key for. @param InNamespace			Namespace of the text. @param InSource				The source text to find the keys for. @param InKeyMetadataObj		Meta-data associated with the source text key. @param OutKeys				Array to fill with the found keys. @return True if keys were found, false otherwise.
- L920 _public prototype_ `static bool FindKeysForLegacyTranslation(const TSharedRef<const FInternationalizationManifest>& InManifest, const TSharedPtr<const FInternationalizationArchive>& InNativeArchive, const FLocKey& InNamespace, const FString& InSource, const TSharedPtr<FLocMetadataObject> InKeyMetadataObj, TArray<FLocKey>& OutKeys);` — Given a manifest and (optional) native archive, try and find all the keys that the source string should use by checking the manifest. @note This should only be used to upgrade old non-keyed archive entries when importing legacy data. @param InManifest			The manifest to find the source string in. @param InNativeArchive		The native archive to test to see if the given source text is really a native translation. @param InNamespace			Namespace of the text. @param InSource				The source text to find the keys for. @param InKeyMetadataObj		Meta-data associated with the source text key. @param OutKeys				Array to fill with the found keys. @return True if keys were found, false otherwise.
- L924 _private prototype_ `FLocTextHelper(const FLocTextHelper&) = delete;` — Non-copyable
- L925 _private prototype_ `FLocTextHelper& operator=(const FLocTextHelper&) = delete;`
- L936 _private prototype_ `TSharedPtr<FInternationalizationManifest> LoadManifestImpl(const FString& InManifestFilePath, const ELocTextHelperLoadFlags InLoadFlags, FText* OutError);` — Internal implementation of loading (or creating) a manifest. @param InManifestFilePath	Full path to the manifest file to load. @param InLoadFlags			Flags controlling whether we should load or create the manifest file. @param OutError				Optional text to be filled when an error occurs. @return The file that was loaded (or created), null otherwise.
- L947 _private prototype_ `bool SaveManifestImpl(const TSharedRef<const FInternationalizationManifest>& InManifest, const FString& InManifestFilePath, FText* OutError) const;` — Internal implementation of saving a manifest. @param InManifest			The manifest file to save. @param InManifestFilePath	Full path to where the manifest file should be saved. @param OutError				Optional text to be filled when an error occurs. @return True if the file was saved, false otherwise.
- L958 _private prototype_ `TSharedPtr<FInternationalizationArchive> LoadArchiveImpl(const FString& InArchiveFilePath, const ELocTextHelperLoadFlags InLoadFlags, FText* OutError);` — Internal implementation of loading (or creating) an archive. @param InArchiveFilePath		Full path to the archive file to load. @param InLoadFlags			Flags controlling whether we should load or create the archive file. @param OutError				Optional text to be filled when an error occurs. @return The file that was loaded (or created), null otherwise.
- L969 _private prototype_ `bool SaveArchiveImpl(const TSharedRef<const FInternationalizationArchive>& InArchive, const FString& InArchiveFilePath, FText* OutError) const;` — Internal implementation of saving an archive. @param InArchive				The archive file to save. @param InArchiveFilePath		Full path to where the archive file should be saved. @param OutError				Optional text to be filled when an error occurs. @return True if the file was saved, false otherwise.
- L981 _private prototype_ `TSharedPtr<FArchiveEntry> FindTranslationImpl(const FString& InCulture, const FLocKey& InNamespace, const FLocKey& InKey, const TSharedPtr<FLocMetadataObject> InKeyMetadataObj) const;` — Find an existing translation entry from its source text. @param InCulture				Culture to find the translation for. @param InNamespace			Namespace of the text. @param InKey					Key of the text. @param InKeyMetadataObj		Meta-data associated with the source text key. @return The entry, or null if it couldn't be found.
- L984 _private member_ `ELocTextPlatformSplitMode PlatformSplitMode;` — How are we splitting localization data per-platform?
- L987 _private member_ `FString TargetName;` — The name of the target we're working with
- L990 _private member_ `FString TargetPath;` — The path to the localization target (the root of this path should contain the manifest, and the archives should be under culture code directories)
- L993 _private member_ `FString ManifestName;` — Name given to the manifest file for this target (eg, Game.manifest)
- L996 _private member_ `FString ArchiveName;` — Name given to the archive files for this target (eg, Game.archive)
- L999 _private member_ `FString NativeCulture;` — Culture code of the native culture (eg, en), or an empty string if the native culture is unknown
- L1002 _private member_ `TArray<FString> ForeignCultures;` — Array of culture codes for the foreign cultures (does not include the native culture)
- L1005 _private member_ `TSharedPtr<ILocFileNotifies> LocFileNotifies;` — Interface for allowing source control integration (may be null)
- L1008 _private member_ `FString CopyrightNotice;` — Optional copyright notice to insert into files that support it
- L1011 _private member_ `TSharedPtr<FInternationalizationManifest> Manifest;` — Loaded manifest
- L1014 _private member_ `TMap<FString, TSharedPtr<FInternationalizationArchive>> Archives;` — Loaded archives
- L1017 _private member_ `TArray<FString> DependencyPaths;` — Loaded dependencies
- L1018 _private member_ `TArray<TSharedPtr<FInternationalizationManifest>> Dependencies;`
- L1021 _private member_ `FLocTextConflicts ConflictTracker;` — Conflict tracker instance

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API LOCALIZATION_API`
- L40 _prototype_ `ENUM_CLASS_FLAGS(ELocTextHelperLoadFlags);`

### `Source/Developer/Localization/Public/LocalizationConfigurationScript.h` (Public)


#### struct `FLocalizationConfigurationScript`  
`struct FLocalizationConfigurationScript : public FConfigFile`  
_L16-29_
- inherits: `FConfigFile`
- L18 _public prototype_ `bool WriteWithSCC(const FString& InConfigFilename);`
- L20 _public function_ `void AddCommonSettings(FConfigSection&& Section)`
- L25 _public function_ `void AddGatherTextStep(const uint32 Index, FConfigSection&& Section)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LOCALIZATION_API`
- L31 _namespace_ `namespace LocalizationConfigurationScript`
- L33 _prototype_ `FString MakePathRelativeForCommandletProcess(const FString& Path, const bool IsUsingProjectFile);` (scope `LocalizationConfigurationScript`)
- L35 _prototype_ `FString GetConfigDirectory(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L36 _prototype_ `FString GetDataDirectory(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L38 _prototype_ `TArray<FString> GetConfigPaths(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L39 _prototype_ `void GenerateAllConfigFiles(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L41 _prototype_ `TArray<FString> GetOutputFilePaths(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L43 _prototype_ `FString GetManifestFileName(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L44 _prototype_ `FString GetManifestPath(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L46 _prototype_ `FString GetArchiveFileName(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L47 _prototype_ `FString GetArchivePath(const ULocalizationTarget* const Target, const FString& CultureName);` (scope `LocalizationConfigurationScript`)
- L49 _prototype_ `FString GetDefaultPOFileName(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L50 _prototype_ `FString GetDefaultPOPath(const ULocalizationTarget* const Target, const FString& CultureName);` (scope `LocalizationConfigurationScript`)
- L52 _prototype_ `FString GetDefaultDialogueScriptFileName(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L53 _prototype_ `FString GetDefaultDialogueScriptPath(const ULocalizationTarget* const Target, const FString& CultureName);` (scope `LocalizationConfigurationScript`)
- L55 _prototype_ `FString GetLocResFileName(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L56 _prototype_ `FString GetLocResPath(const ULocalizationTarget* const Target, const FString& CultureName);` (scope `LocalizationConfigurationScript`)
- L58 _prototype_ `FString GetLocMetaFileName(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L59 _prototype_ `FString GetLocMetaPath(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L61 _prototype_ `FString GetWordCountCSVFileName(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L62 _prototype_ `FString GetWordCountCSVPath(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L64 _prototype_ `FString GetConflictReportFileName(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L65 _prototype_ `FString GetConflictReportPath(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L67 _prototype_ `FLocalizationConfigurationScript GenerateGatherTextConfigFile(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L68 _prototype_ `FString GetGatherTextConfigPath(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L70 _prototype_ `FLocalizationConfigurationScript GenerateImportTextConfigFile(const ULocalizationTarget* const Target, const TOptional<FString> CultureName = TOptional<FString>(), const TOptional<FString> ImportPathOverride = TOptional<FString>());` (scope `LocalizationConfigurationScript`)
- L71 _prototype_ `FString GetImportTextConfigPath(const ULocalizationTarget* const Target, const TOptional<FString> CultureName = TOptional<FString>());` (scope `LocalizationConfigurationScript`)
- L73 _prototype_ `FLocalizationConfigurationScript GenerateExportTextConfigFile(const ULocalizationTarget* const Target, const TOptional<FString> CultureName = TOptional<FString>(), const TOptional<FString> ExportPathOverride = TOptional<FString>());` (scope `LocalizationConfigurationScript`)
- L74 _prototype_ `FString GetExportTextConfigPath(const ULocalizationTarget* const Target, const TOptional<FString> CultureName = TOptional<FString>());` (scope `LocalizationConfigurationScript`)
- L76 _prototype_ `FLocalizationConfigurationScript GenerateImportDialogueScriptConfigFile(const ULocalizationTarget* const Target, const TOptional<FString> CultureName = TOptional<FString>(), const TOptional<FString> ImportPathOverride = TOptional<FString>());` (scope `LocalizationConfigurationScript`)
- L77 _prototype_ `FString GetImportDialogueScriptConfigPath(const ULocalizationTarget* const Target, const TOptional<FString> CultureName = TOptional<FString>());` (scope `LocalizationConfigurationScript`)
- L79 _prototype_ `FLocalizationConfigurationScript GenerateExportDialogueScriptConfigFile(const ULocalizationTarget* const Target, const TOptional<FString> CultureName = TOptional<FString>(), const TOptional<FString> ExportPathOverride = TOptional<FString>());` (scope `LocalizationConfigurationScript`)
- L80 _prototype_ `FString GetExportDialogueScriptConfigPath(const ULocalizationTarget* const Target, const TOptional<FString> CultureName = TOptional<FString>());` (scope `LocalizationConfigurationScript`)
- L82 _prototype_ `FLocalizationConfigurationScript GenerateImportDialogueConfigFile(const ULocalizationTarget* const Target, const TOptional<FString> CultureName = TOptional<FString>());` (scope `LocalizationConfigurationScript`)
- L83 _prototype_ `FString GetImportDialogueConfigPath(const ULocalizationTarget* const Target, const TOptional<FString> CultureName = TOptional<FString>());` (scope `LocalizationConfigurationScript`)
- L85 _prototype_ `FLocalizationConfigurationScript GenerateWordCountReportConfigFile(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L86 _prototype_ `FString GetWordCountReportConfigPath(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L88 _prototype_ `FLocalizationConfigurationScript GenerateCompileTextConfigFile(const ULocalizationTarget* const Target, const TOptional<FString> CultureName = TOptional<FString>());` (scope `LocalizationConfigurationScript`)
- L89 _prototype_ `FString GetCompileTextConfigPath(const ULocalizationTarget* const Target, const TOptional<FString> CultureName = TOptional<FString>());` (scope `LocalizationConfigurationScript`)
- L91 _prototype_ `FLocalizationConfigurationScript GenerateRegenerateResourcesConfigFile(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L92 _prototype_ `FString GetRegenerateResourcesConfigPath(const ULocalizationTarget* const Target);` (scope `LocalizationConfigurationScript`)
- L94 _prototype_ `bool WriteConfigFileWithSCC(const FString& InConfigFilename, FLocalizationConfigurationScript& InConfigScript);` (scope `LocalizationConfigurationScript`)

### `Source/Developer/Localization/Public/LocalizationDelegates.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace LocalizationDelegates`
- L15 _externvar_ `extern TMulticastDelegate<void(const FString& LocalizationTargetPath)> OnLocalizationTargetDataUpdated;` (scope `LocalizationDelegates`) — Delegate called when any on-disk data for the given localization target is updated.

### `Source/Developer/Localization/Public/LocalizationFileUtil.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LOCALIZATION_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Localization` (scope `UE`)
- L15 _namespace_ `namespace FileUtil` (scope `UE::Localization`)
- L21 _prototype_ `uint64 BinaryHash(const FString& Filename);` (scope `UE::Localization::FileUtil`) — Generic file hash, that hashes the binary representation of the file.
- L26 _prototype_ `uint64 TextHash(const FString& Filename);` (scope `UE::Localization::FileUtil`) — Generic file hash, that hashes the textual representation of the file (ignoring line endings and encoding).
- L31 _prototype_ `uint64 PortableObjectHash(const FString& Filename);` (scope `UE::Localization::FileUtil`) — Specialized file hash for PO files, that skips the transient information (like timestamps) from the PO file header.
- L41 _prototype_ `bool WriteFileIfModified(const FString& Filename, TFunctionRef<bool(const FString&)> WriteFunc, TFunctionRef<uint64(const FString&)> HashFunc);` (scope `UE::Localization::FileUtil`) — Utility to write a file to disk, but only if it has changed. This function works by using WriteFunc to generate a .tmp file and then uses HashFunc to compare the contents of the .tmp file against the contents of Filename (if it exists). If the hash is different, then the file is atomically renamed to Filename, which ensures that we don't get a partial file write if the application crashes. @return True if the file was modified or up-to-date, or false if the file failed to write.
- L42 _prototype_ `bool WriteFileIfModified(const FString& Filename, TFunctionRef<bool(const FString&)> WriteFunc, TFunctionRef<uint64(const FString&)> HashFunc, const TSharedPtr<FLocalizationSCC>& SourceControlInfo);` (scope `UE::Localization::FileUtil`)
- L43 _prototype_ `bool WriteFileIfModified(const FString& Filename, TFunctionRef<bool(const FString&)> WriteFunc, TFunctionRef<uint64(const FString&)> HashFunc, const TSharedPtr<ILocFileNotifies>& LocFileNotifies);` (scope `UE::Localization::FileUtil`)

### `Source/Developer/Localization/Public/LocalizationModule.h` (Public)


#### class `ILocalizationModule`  
`class ILocalizationModule : public IModuleInterface`  
_L12-26_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual bool HandleRegenLocCommand(const FString& InConfigFilePath) = 0;` — Given a config file, generate a compiled LocRes file for the active culture and use it to update the live-entries in the localization manager.
- L20 _public prototype_ `virtual ULocalizationTarget* GetLocalizationTargetByName(FString TargetName, bool bIsEngineTarget) = 0;`
- L22 _public function_ `static ILocalizationModule& Get()`

### `Source/Developer/Localization/Public/LocalizationSettings.h` (Public)


#### class `ULocalizationSettings`  
`class ULocalizationSettings : public UObject`  
_L23-51_
- reflection: `UCLASS(MinimalAPI, Config=Editor, defaultconfig)`
- inherits: `UObject`
- desc: Class for loading/saving configuration settings and the details view objects needed for localization dashboard functionality.
- L28 _public prototype_ `ULocalizationSettings(const FObjectInitializer& ObjectInitializer);`
- L32 _private member_ `TObjectPtr<ULocalizationTargetSet> EngineTargetSet;` — `UPROPERTY()`
- L35 _private member_ `TArray<FLocalizationTargetSettings> EngineTargetsSettings;` — `UPROPERTY(config)`
- L38 _private member_ `TObjectPtr<ULocalizationTargetSet> GameTargetSet;` — `UPROPERTY()`
- L41 _private member_ `TArray<FLocalizationTargetSettings> GameTargetsSettings;` — `UPROPERTY(config)`
- L45 _public prototype_ `virtual void PostInitProperties() override;`
- L46 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L49 _public prototype_ `static ULocalizationTargetSet* GetEngineTargetSet();`
- L50 _public prototype_ `static ULocalizationTargetSet* GetGameTargetSet();`

#### struct `FLocalizationSourceControlSettings`  
`struct FLocalizationSourceControlSettings`  
_L54-76_
- desc: Struct containing util functions for getting/setting the SCC settings for the localization dashboard
- L58 _public prototype_ `static bool IsSourceControlAvailable();` — Checks to see whether source control is available based upon the current editor SCC settings.
- L61 _public prototype_ `static bool IsSourceControlEnabled();` — Check to see whether we should use SCC when running the localization commandlets. This should be used to optionally pass "-EnableSCC" to the commandlet.
- L64 _public prototype_ `static bool IsSourceControlAutoSubmitEnabled();` — Check to see whether we should automatically submit changed files after running the commandlet. This should be used to optionally pass "-DisableSCCSubmit" to the commandlet.
- L67 _public prototype_ `static void SetSourceControlEnabled(const bool bIsEnabled);` — Set whether we should use SCC when running the localization commandlets.
- L70 _public prototype_ `static void SetSourceControlAutoSubmitEnabled(const bool bIsEnabled);` — Set whether we should automatically submit changed files after running the commandlet.
- L73 _private member_ `static const FString LocalizationSourceControlSettingsCategoryName;`
- L74 _private member_ `static const FString SourceControlEnabledSettingName;`
- L75 _private member_ `static const FString SourceControlAutoSubmitEnabledSettingName;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API LOCALIZATION_API`

### `Source/Developer/Localization/Public/LocalizationSourceControlUtil.h` (Public)


#### class `FLocalizationSCC`  
`class FLocalizationSCC`  
_L16-59_
- L26 _public prototype_ `explicit FLocalizationSCC(const EInitSCC InitSCC = EInitSCC::Commandlet);`
- L27 _public prototype_ `~FLocalizationSCC();`
- L30 _public prototype_ `static TSharedPtr<FLocalizationSCC> CreateIfSCCEnabled(const EInitSCC InitSCC);` — Create a FLocalizationSCC, but only if a SCC provider is enabled
- L33 _public prototype_ `void BeginParallelTasks();` — Start a block of parallel tasks (may be nested); this will defer check-out requests until the final EndParallelTasks is called
- L35 _public prototype_ `bool EndParallelTasks(FText& OutError);` — Stop a block of parallel tasks; this will attempt to perform any check-outs deferred during the block
- L38 _public prototype_ `bool CheckOutFile(const FString& InFile, FText& OutError);` — Attempt to check-out the given file; if called during a parallel tasks block, the file will be made writable and the check-out request deferred
- L40 _public prototype_ `bool CheckinFiles(const FText& InChangeDescription, FText& OutError);` — Attempt to check-in every file that is currently tracked as checked-out; this cannot be called during a parallel tasks block
- L42 _public prototype_ `bool CleanUp(FText& OutError);` — Attempt to revert every file that is currently tracked as checked-out; this cannot be called during a parallel tasks block
- L44 _public prototype_ `bool RevertFile(const FString& InFile, FText& OutError);` — Attempt to revert the given file; this cannot be called during a parallel tasks block
- L46 _public prototype_ `bool IsReady(FText& OutError) const;` — Check whether SCC is ready to be used; this cannot be called during a parallel tasks block
- L50 _private member_ `TSet<FString> CheckedOutFiles;` — Set of files that were checked-out from SCC via CheckOutFile
- L52 _private member_ `TSet<FString> DeferredCheckedOutFiles;` — Set of files that will be checked-out from SCC via CheckOutFile, but had to be deferred due to running in parallel mode
- L54 _private member_ `mutable UE::FMutex FilesMutex;` — Mutex protecting CheckedOutFiles and DeferredCheckedOutFiles when ParallelTasksCount > 0
- L56 _private member_ `std::atomic<uint16> ParallelTasksCount = 0;` — >0 if this we're being used from a parallel tasks block, and need to defer check-out requests
- L58 _private member_ `bool bDidInitSCC = false;` — True if we called Init on the SCC during construction, and need to call Close during destruction

#### enum `FLocalizationSCC::EInitSCC`  
`enum class EInitSCC`  
_L19-24_
- L21 _public enumerator_ `Never`
- L22 _public enumerator_ `Always`
- L23 _public enumerator_ `Commandlet`

#### class `FLocFileSCCNotifies`  
`class FLocFileSCCNotifies : public ILocFileNotifies`  
_L61-82_
- inherits: `ILocFileNotifies`
- L64 _public function_ `FLocFileSCCNotifies(const TSharedPtr<FLocalizationSCC>& InSourceControlInfo) : SourceControlInfo(InSourceControlInfo)`
- L70 _public prototype_ `virtual ~FLocFileSCCNotifies() = default;` — Virtual destructor
- L73 _public prototype_ `virtual void BeginParallelTasks() override;`
- L74 _public prototype_ `virtual void EndParallelTasks() override;`
- L75 _public function_ `virtual void PreFileRead(const FString& InFilename) override`
- L76 _public function_ `virtual void PostFileRead(const FString& InFilename) override`
- L77 _public prototype_ `virtual void PreFileWrite(const FString& InFilename) override;`
- L78 _public prototype_ `virtual void PostFileWrite(const FString& InFilename) override;`
- L81 _private member_ `TSharedPtr<FLocalizationSCC> SourceControlInfo;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LOCALIZATION_API`

### `Source/Developer/Localization/Public/LocalizationTargetTypes.h` (Public)


#### enum `ELocalizationTargetConflictStatus`  
`enum class ELocalizationTargetConflictStatus : uint8`  
_L28-36_
- reflection: `UENUM()`
- L31 _public enumerator_ `Unknown` — The status of conflicts in this localization target could not be determined.
- L33 _public enumerator_ `ConflictsPresent` — The are outstanding conflicts present in this localization target.
- L35 _public enumerator_ `Clear` — The localization target is clear of conflicts.

#### enum `ELocalizationGatherPathRoot`  
`enum class ELocalizationGatherPathRoot : uint8`  
_L39-47_
- reflection: `UENUM()`
- L42 _public enumerator_ `Auto` — Automatically select Engine or Project based on which set the target belongs to
- L44 _public enumerator_ `Engine` — Path is relative to the Engine directory
- L46 _public enumerator_ `Project` — Path is relative to the Project directory

#### struct `FLocalizationGatherPathRootUtil`  
`struct FLocalizationGatherPathRootUtil`  
_L49-59_
- L52 _public prototype_ `static FString GetResolvedPathRootToken(const ELocalizationGatherPathRoot InPathRoot);` — Get the resolved placeholder token of the path root ("%LOCENGINEROOT%" for Engine or "%LOCPROJECTROOT%" for Project; empty for Auto)
- L55 _public prototype_ `static FString GetResolvedPathRoot(const ELocalizationGatherPathRoot InPathRoot, const bool bIsEngineTarget);` — Get the path name of the resolved path root (either FPaths::EngineDir() or FPaths::ProjectDir() depending on the setting and target type
- L58 _public prototype_ `static FText GetResolvedPathRootDisplayName(const ELocalizationGatherPathRoot InPathRoot, const bool bIsEngineTarget);` — Get the display name of the resolved path root (either "Engine/" or "{ProjectName/" depending on the setting and target type

#### struct `FGatherTextSearchDirectory`  
`struct FGatherTextSearchDirectory`  
_L62-73_
- reflection: `USTRUCT()`
- L67 _public member_ `ELocalizationGatherPathRoot PathRoot = ELocalizationGatherPathRoot::Auto;` — `UPROPERTY(config, EditAnywhere, Category="Path")`
- L70 _public member_ `FString Path;` — `UPROPERTY(config, EditAnywhere, Category="Path")`
- L72 _public prototype_ `bool Validate(const bool bIsEngineTarget, FText& OutError) const;`

#### struct `FGatherTextIncludePath`  
`struct FGatherTextIncludePath`  
_L76-87_
- reflection: `USTRUCT()`
- L81 _public member_ `ELocalizationGatherPathRoot PathRoot = ELocalizationGatherPathRoot::Auto;` — `UPROPERTY(config, EditAnywhere, Category="Path")`
- L84 _public member_ `FString Pattern;` — `UPROPERTY(config, EditAnywhere, Category="Pattern")`
- L86 _public prototype_ `bool Validate(const bool bIsEngineTarget, FText& OutError) const;`

#### struct `FGatherTextExcludePath`  
`struct FGatherTextExcludePath`  
_L90-101_
- reflection: `USTRUCT()`
- L95 _public member_ `ELocalizationGatherPathRoot PathRoot = ELocalizationGatherPathRoot::Auto;` — `UPROPERTY(config, EditAnywhere, Category="Path")`
- L98 _public member_ `FString Pattern;` — `UPROPERTY(config, EditAnywhere, Category="Pattern")`
- L100 _public prototype_ `bool Validate(const bool bIsEngineTarget, FText& OutError) const;`

#### struct `FGatherTextFileExtension`  
`struct FGatherTextFileExtension`  
_L104-112_
- reflection: `USTRUCT()`
- L109 _public member_ `FString Pattern;` — `UPROPERTY(config, EditAnywhere, Category="Pattern")`
- L111 _public prototype_ `bool Validate(const bool bIsEngineTarget, FText& OutError) const;`

#### struct `FMetaDataTextKeyPattern`  
`struct FMetaDataTextKeyPattern`  
_L115-125_
- reflection: `USTRUCT()`
- L120 _public member_ `FString Pattern;` — `UPROPERTY(config, EditAnywhere, Category="Pattern")`
- L122 _public prototype_ `bool Validate(const bool bIsEngineTarget, FText& OutError) const;`
- L124 _public prototype_ `static const TArray<FString>& GetPossiblePlaceHolders();`

#### struct `FMetaDataKeyName`  
`struct FMetaDataKeyName`  
_L128-136_
- reflection: `USTRUCT()`
- L133 _public member_ `FString Name;` — `UPROPERTY(config, EditAnywhere, Category="Name")`
- L135 _public prototype_ `bool Validate(const bool bIsEngineTarget, FText& OutError) const;`

#### struct `FMetaDataKeyGatherSpecification`  
`struct FMetaDataKeyGatherSpecification`  
_L139-159_
- reflection: `USTRUCT()`
- L145 _public member_ `FMetaDataKeyName MetaDataKey;` — `UPROPERTY(config, EditAnywhere, Category = "Input")` — The metadata key for which values will be gathered as text.
- L149 _public member_ `FString TextNamespace;` — `UPROPERTY(config, EditAnywhere, Category = "Output")` — The localization namespace in which the gathered text will be output.
- L156 _public member_ `FMetaDataTextKeyPattern TextKeyPattern;` — `UPROPERTY(config, EditAnywhere, Category = "Output")` — The pattern which will be formatted to form the localization key for the metadata value gathered as text. Placeholder - Description {FieldPath} - The fully qualified name of the object upon which the metadata resides. {MetaDataValue} - The value associated with the metadata key.
- L158 _public prototype_ `bool Validate(const bool bIsEngineTarget, FText& OutError) const;`

#### struct `FGatherTextFromTextFilesConfiguration`  
`struct FGatherTextFromTextFilesConfiguration`  
_L162-196_
- reflection: `USTRUCT()`
- L166 _public prototype_ `static const TArray<FGatherTextFileExtension>& GetDefaultTextFileExtensions();`
- L168 _public function_ `FGatherTextFromTextFilesConfiguration() : IsEnabled(true) , FileExtensions(GetDefaultTextFileExtensions()) , ShouldGatherFromEditorOnlyData(false)`
- L177 _public member_ `bool IsEnabled;` — `UPROPERTY(config, EditAnywhere, Category = "Execution")` — If enabled, text from text files will be gathered according to this configuration.
- L181 _public member_ `TArray<FGatherTextSearchDirectory> SearchDirectories;` — `UPROPERTY(config, EditAnywhere, Category = "Filter")` — The paths of directories to be searched recursively for text files, specified relative to the project's root, which may be parsed for text to gather.
- L185 _public member_ `TArray<FGatherTextExcludePath> ExcludePathWildcards;` — `UPROPERTY(config, EditAnywhere, Category = "Filter")` — Text files whose paths match these wildcard patterns will be excluded from gathering.
- L189 _public member_ `TArray<FGatherTextFileExtension> FileExtensions;` — `UPROPERTY(config, EditAnywhere, Category = "Filter")` — Text files whose names match these wildcard patterns may be parsed for text to gather.
- L193 _public member_ `bool ShouldGatherFromEditorOnlyData;` — `UPROPERTY(config, EditAnywhere, Category = "Filter")` — If enabled, data that is specified as editor-only may be processed for gathering.
- L195 _public prototype_ `bool Validate(const bool bIsEngineTarget, FText& OutError) const;`

#### struct `FGatherTextFromPackagesConfiguration`  
`struct FGatherTextFromPackagesConfiguration`  
_L200-292_
- reflection: `USTRUCT()`
- L204 _public prototype_ `static const TArray<FGatherTextFileExtension>& GetDefaultPackageFileExtensions();`
- L206 _public function_ `FGatherTextFromPackagesConfiguration() : IsEnabled(true) , FileExtensions(GetDefaultPackageFileExtensions()) , ShouldExcludeDerivedClasses(false) , ShouldGatherFromEditorOnlyData(false) , SkipGatherCache(false)`
- L222 _public member_ `bool IsEnabled;` — `UPROPERTY(config, EditAnywhere, Category = "Execution")` — If enabled, text from packages will be gathered according to this configuration.
- L226 _public member_ `TArray<FGatherTextIncludePath> IncludePathWildcards;` — `UPROPERTY(config, EditAnywhere, Category = "Filter")` — Packages whose paths match these wildcard patterns, specified relative to the project's root, may be processed for gathering.
- L230 _public member_ `TArray<FGatherTextExcludePath> ExcludePathWildcards;` — `UPROPERTY(config, EditAnywhere, Category = "Filter")` — Packages whose paths match these wildcard patterns will be excluded from gathering.
- L234 _public member_ `TArray<FGatherTextFileExtension> FileExtensions;` — `UPROPERTY(config, EditAnywhere, Category = "Filter")` — Packages whose names match these wildcard patterns may be processed for text to gather.
- L238 _public member_ `TArray<FName> Collections;` — `UPROPERTY(config, EditAnywhere, Category = "Filter")` — Packages in these collections may be processed for gathering.
- L245 _public member_ `TArray<FName> WorldCollections;` — `UPROPERTY(config, EditAnywhere, Category = "Filter", AdvancedDisplay)` — Worlds (including their associated external actors) in these collections may be processed for gathering. The collections may contain more than just worlds, and will be filtered internally. @note This is typically not needed unless setting up modular localization targets that have to gather external actors separately from their world (eg, when using External Data Layers).
- L249 _public member_ `TArray<FSoftClassPath> ExcludeClasses;` — `UPROPERTY(config, EditAnywhere, Category = "Filter", meta=(MetaClass="/Script/CoreUObject.Object", AllowAbstract="True"))` — Classes that should be excluded from gathering.
- L253 _public member_ `bool ShouldExcludeDerivedClasses;` — `UPROPERTY(config, EditAnywhere, Category = "Filter")` — Should classes derived from those in the exclude classes list also be excluded from gathering?
- L257 _public member_ `TArray<FMetaDataKeyGatherSpecification> MetadataKeySpecifications;` — `UPROPERTY(config, EditAnywhere, Category = "MetaData", AdvancedDisplay)` — Specifications for how to gather text from specific metadata keys from BP/struct/enum assets.
- L261 _public member_ `TArray<FString> MetadataFieldTypesToInclude;` — `UPROPERTY(config, EditAnywhere, Category = "MetaData", AdvancedDisplay)` — List of field types (eg, Property, Function, ScriptStruct, Enum, etc) that should be included in the gather, or empty to include everything.
- L265 _public member_ `TArray<FString> MetadataFieldTypesToExclude;` — `UPROPERTY(config, EditAnywhere, Category = "MetaData", AdvancedDisplay)` — List of field types (eg, Property, Function, ScriptStruct, Enum, etc) the should be excluded from the gather.
- L269 _public member_ `TArray<FString> MetadataFieldOwnerTypesToInclude;` — `UPROPERTY(config, EditAnywhere, Category = "MetaData", AdvancedDisplay)` — List of field owner types (eg, MyClass, MyStruct, etc) that should have fields within them included in the gather, or empty to include everything.
- L273 _public member_ `TArray<FString> MetadataFieldOwnerTypesToExclude;` — `UPROPERTY(config, EditAnywhere, Category = "MetaData", AdvancedDisplay)` — List of field owner types (eg, MyClass, MyStruct, etc) that should have fields within them excluded from the gather.
- L277 _public member_ `TArray<FString> MetadataFieldOuterTypesToInclude;` — `UPROPERTY(config, EditAnywhere, Category = "MetaData", AdvancedDisplay)` — List of outer types (eg, Property, Function, ScriptStruct, etc) of fields that should be included in the gather, or empty to include everything.
- L281 _public member_ `TArray<FString> MetadataFieldOuterTypesToExclude;` — `UPROPERTY(config, EditAnywhere, Category = "MetaData", AdvancedDisplay)` — List of outer types (eg, Property, Function, ScriptStruct, etc) of fields that should be excluded from the gather.
- L285 _public member_ `bool ShouldGatherFromEditorOnlyData;` — `UPROPERTY(config, EditAnywhere, Category = "Gather Text")` — If enabled, data that is specified as editor-only may be processed for gathering.
- L289 _public member_ `bool SkipGatherCache;` — `UPROPERTY(config, EditAnywhere, Category = "Gather Text", AdvancedDisplay)` — Should we ignore the cached text in the package header and perform a full package load instead?
- L291 _public prototype_ `bool Validate(const bool bIsEngineTarget, FText& OutError) const;`

#### struct `FGatherTextFromMetaDataConfiguration`  
`struct FGatherTextFromMetaDataConfiguration`  
_L295-350_
- reflection: `USTRUCT()`
- L299 _public function_ `FGatherTextFromMetaDataConfiguration() : IsEnabled(false) , ShouldGatherFromEditorOnlyData(false)`
- L307 _public member_ `bool IsEnabled;` — `UPROPERTY(config, EditAnywhere, Category = "Execution")` — If enabled, metadata will be gathered according to this configuration.
- L311 _public member_ `TArray<FGatherTextIncludePath> IncludePathWildcards;` — `UPROPERTY(config, EditAnywhere, Category = "Filter")` — Metadata from source files whose paths match these wildcard patterns, specified relative to the project's root, may be processed for gathering.
- L315 _public member_ `TArray<FGatherTextExcludePath> ExcludePathWildcards;` — `UPROPERTY(config, EditAnywhere, Category = "Filter")` — Metadata from source files whose paths match these wildcard patterns will be excluded from gathering.
- L319 _public member_ `TArray<FMetaDataKeyGatherSpecification> KeySpecifications;` — `UPROPERTY(config, EditAnywhere, Category = "MetaData")` — Specifications for how to gather text from specific metadata keys.
- L323 _public member_ `TArray<FString> FieldTypesToInclude;` — `UPROPERTY(config, EditAnywhere, Category = "MetaData")` — List of field types (eg, Property, Function, ScriptStruct, Enum, etc) that should be included in the gather, or empty to include everything.
- L327 _public member_ `TArray<FString> FieldTypesToExclude;` — `UPROPERTY(config, EditAnywhere, Category = "MetaData")` — List of field types (eg, Property, Function, ScriptStruct, Enum, etc) the should be excluded from the gather.
- L331 _public member_ `TArray<FString> FieldOwnerTypesToInclude;` — `UPROPERTY(config, EditAnywhere, Category = "MetaData")` — List of field owner types (eg, MyClass, MyStruct, etc) that should have fields within them included in the gather, or empty to include everything.
- L335 _public member_ `TArray<FString> FieldOwnerTypesToExclude;` — `UPROPERTY(config, EditAnywhere, Category = "MetaData")` — List of field owner types (eg, MyClass, MyStruct, etc) that should have fields within them excluded from the gather.
- L339 _public member_ `TArray<FString> FieldOuterTypesToInclude;` — `UPROPERTY(config, EditAnywhere, Category = "MetaData")` — List of outer types (eg, Property, Function, ScriptStruct, etc) of fields that should be included in the gather, or empty to include everything.
- L343 _public member_ `TArray<FString> FieldOuterTypesToExclude;` — `UPROPERTY(config, EditAnywhere, Category = "MetaData")` — List of outer types (eg, Property, Function, ScriptStruct, etc) of fields that should be excluded from the gather.
- L347 _public member_ `bool ShouldGatherFromEditorOnlyData;` — `UPROPERTY(config, EditAnywhere, Category = "Filter")` — If enabled, data that is specified as editor-only may be processed for gathering.
- L349 _public prototype_ `bool Validate(const bool bIsEngineTarget, FText& OutError) const;`

#### struct `FLocalizationExportingSettings`  
`struct FLocalizationExportingSettings`  
_L353-380_
- reflection: `USTRUCT()`
- L357 _public function_ `FLocalizationExportingSettings() : CollapseMode(ELocalizedTextCollapseMode::IdenticalTextIdAndSource) , POFormat(EPortableObjectFormat::Unreal) , ShouldPersistCommentsOnExport(false) , ShouldAddSourceLocationsAsComments(true)`
- L367 _public member_ `ELocalizedTextCollapseMode CollapseMode;` — `UPROPERTY(config, EditAnywhere, Category = "Collapsing", AdvancedDisplay)` — How should we collapse down text when exporting to PO?
- L371 _public member_ `EPortableObjectFormat POFormat;` — `UPROPERTY(config, EditAnywhere, Category = "Format", AdvancedDisplay)` — Which format of PO file should we use?
- L375 _public member_ `bool ShouldPersistCommentsOnExport;` — `UPROPERTY(config, EditAnywhere, Category = "Comments")` — Should user comments in existing PO files be persisted after export? Useful if using a third party service that stores editor/translator notes in the PO format's comment fields.
- L379 _public member_ `bool ShouldAddSourceLocationsAsComments;` — `UPROPERTY(config, EditAnywhere, Category = "Comments")` — Should source locations be added to PO file entries as comments? Useful if a third party service doesn't expose PO file reference comments, which typically store the source location.

#### struct `FLocalizationCompilationSettings`  
`struct FLocalizationCompilationSettings`  
_L383-410_
- reflection: `USTRUCT()`
- L387 _public function_ `FLocalizationCompilationSettings() : SkipSourceCheck(false) , ValidateFormatPatterns(true) , ValidateSafeWhitespace(false) , ValidateRichTextTags(false)`
- L397 _public member_ `bool SkipSourceCheck;` — `UPROPERTY(config, EditAnywhere, Category="Source")` — Should we skip the source check when compiling translations? This will allow translations whose source no longer matches the active source to still be used by the game at runtime.
- L401 _public member_ `bool ValidateFormatPatterns;` — `UPROPERTY(config, EditAnywhere, Category="Validation")` — Should we validate that format patterns are valid for the language being compiled (eg, detect invalid plural rules or broken syntax).
- L405 _public member_ `bool ValidateSafeWhitespace;` — `UPROPERTY(config, EditAnywhere, Category="Validation")` — Should we validate that text doesn't contain any unsafe whitespace (leading or trailing whitespace) that could get lost during the translation process.
- L409 _public member_ `bool ValidateRichTextTags;` — `UPROPERTY(config, EditAnywhere, Category = "Validation")` — Should we validate translated text containing rich text tags to see if the translated text have broken rich text tags. (i.e. "Example of <b>broken tag</")

#### struct `FLocalizationImportDialogueSettings`  
`struct FLocalizationImportDialogueSettings`  
_L413-434_
- reflection: `USTRUCT()`
- L417 _public function_ `FLocalizationImportDialogueSettings() : ImportedDialogueFolder(TEXT("ImportedDialogue")) , bImportNativeAsSource(false)`
- L425 _public member_ `FDirectoryPath RawAudioPath;` — `UPROPERTY(config, EditAnywhere, Category="Dialogue")` — Path to the folder to import the audio from. This folder is expected to contain language sub-folders, which in turn contain the raw WAV files to import.
- L429 _public member_ `FString ImportedDialogueFolder;` — `UPROPERTY(config, EditAnywhere, Category="Dialogue")` — Folder in which to create the generated sound waves. This is relative to the root of the L10N language folder (or the root content folder if importing native dialogue as source dialogue).
- L433 _public member_ `bool bImportNativeAsSource;` — `UPROPERTY(config, EditAnywhere, Category="Dialogue")` — Should the dialogue for the native language be imported as if it were source audio? If false, the native language dialogue will be imported as localized data for the native language.

#### struct `FCultureStatistics`  
`struct FCultureStatistics`  
_L437-460_
- reflection: `USTRUCT()`
- L441 _public function_ `FCultureStatistics() : WordCount(0)`
- L446 _public function_ `FCultureStatistics(const FString& InCultureName) : CultureName(InCultureName) , WordCount(0)`
- L455 _public member_ `FString CultureName;` — `UPROPERTY(config, EditAnywhere, Category = "Language", DisplayName="Language")` — The ISO name for this language.
- L459 _public member_ `uint32 WordCount;` — `UPROPERTY(Transient, EditAnywhere, Category = "Statistics")` — The estimated number of words that have been localized for this language.

#### enum `ELocalizationTargetLoadingPolicy`  
`enum class ELocalizationTargetLoadingPolicy : uint8`  
_L463-477_
- reflection: `UENUM()`
- L466 _public enumerator_ `Never` — This target's localization data will never be loaded automatically.
- L468 _public enumerator_ `Always` — This target's localization data will always be loaded automatically.
- L470 _public enumerator_ `Editor` — This target's localization data will only be loaded when running the editor. Use if this target localizes the editor.
- L472 _public enumerator_ `Game` — This target's localization data will only be loaded when running the game. Use if this target localizes your game.
- L474 _public enumerator_ `PropertyNames` — This target's localization data will only be loaded if the editor is displaying localized property names.
- L476 _public enumerator_ `ToolTips` — This target's localization data will only be loaded if the editor is displaying localized tool tips.

#### struct `FLocalizationTargetSettings`  
`struct FLocalizationTargetSettings`  
_L480-545_
- reflection: `USTRUCT()`
- L484 _public function_ `FLocalizationTargetSettings() : Guid(FGuid::NewGuid()) , ConflictStatus(ELocalizationTargetConflictStatus::Unknown) , NativeCultureIndex(INDEX_NONE)`
- L493 _public member_ `FString Name;` — `UPROPERTY(config, EditAnywhere, Category = "Target")` — Unique name for the target.
- L496 _public member_ `FGuid Guid;` — `UPROPERTY(config, meta=(IgnoreForMemberInitializationTest))`
- L500 _public member_ `ELocalizationTargetConflictStatus ConflictStatus;` — `UPROPERTY(Transient, EditAnywhere, Category = "Target")` — Whether the target has outstanding conflicts that require resolution.
- L504 _public member_ `TArray<FGuid> TargetDependencies;` — `UPROPERTY(config, EditAnywhere, Category = "Gather Text")` — Text present in these targets will not be duplicated in this target.
- L508 _public member_ `TArray<FFilePath> AdditionalManifestDependencies;` — `UPROPERTY(config, EditAnywhere, Category = "Gather Text", AdvancedDisplay, meta=(FilePathFilter="manifest"))` — Text present in these manifests will not be duplicated in this target.
- L512 _public member_ `TArray<FString> RequiredModuleNames;` — `UPROPERTY(config, EditAnywhere, Category = "Gather Text", AdvancedDisplay)` — The names of modules which must be loaded when gathering text. Use to gather from packages or metadata sourced from a module that isn't the primary game module.
- L516 _public member_ `FGatherTextFromTextFilesConfiguration GatherFromTextFiles;` — `UPROPERTY(config, EditAnywhere, Category = "Gather Text")` — Parameters for defining what text is gathered from text files and how.
- L520 _public member_ `FGatherTextFromPackagesConfiguration GatherFromPackages;` — `UPROPERTY(config, EditAnywhere, Category = "Gather Text")` — Parameters for defining what text is gathered from packages and how.
- L524 _public member_ `FGatherTextFromMetaDataConfiguration GatherFromMetaData;` — `UPROPERTY(config, EditAnywhere, Category = "Gather Text")` — Parameters for defining what text is gathered from metadata and how.
- L528 _public member_ `FLocalizationExportingSettings ExportSettings;` — `UPROPERTY(config, EditAnywhere, Category = "Export Text", meta=(ShowOnlyInnerProperties))` — Settings for exporting translations.
- L532 _public member_ `FLocalizationCompilationSettings CompileSettings;` — `UPROPERTY(config, EditAnywhere, Category = "Compile Text", meta=(ShowOnlyInnerProperties))` — Settings for compiling translations.
- L536 _public member_ `FLocalizationImportDialogueSettings ImportDialogueSettings;` — `UPROPERTY(config, EditAnywhere, Category = "Import Dialogue", meta=(ShowOnlyInnerProperties))` — Settings for importing dialogue from WAV files.
- L540 _public member_ `int32 NativeCultureIndex;` — `UPROPERTY(config, EditAnywhere, Category = "Languages")` — The index of the native language among the supported languages.
- L544 _public member_ `TArray<FCultureStatistics> SupportedCulturesStatistics;` — `UPROPERTY(config, EditAnywhere, Category = "Languages")` — Language for which the source text is being localized for.

#### class `ULocalizationTarget`  
`class ULocalizationTarget : public UObject`  
_L548-568_
- reflection: `UCLASS(MinimalAPI, Within=LocalizationTargetSet)`
- inherits: `UObject`
- L553 _public prototype_ `ULocalizationTarget(const FObjectInitializer& ObjectInitializer);`
- L556 _public member_ `FLocalizationTargetSettings Settings;` — `UPROPERTY(EditAnywhere, Category = "Target", meta=(ShowOnlyInnerProperties))`
- L560 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L563 _public prototype_ `bool IsMemberOfEngineTargetSet() const;`
- L564 _public prototype_ `bool UpdateWordCountsFromCSV();`
- L565 _public prototype_ `void UpdateStatusFromConflictReport();`
- L566 _public prototype_ `bool RenameTargetAndFiles(const FString& NewName);`
- L567 _public prototype_ `bool DeleteFiles(const FString* const Culture = nullptr) const;`

#### class `ULocalizationTargetSet`  
`class ULocalizationTargetSet : public UObject`  
_L571-583_
- reflection: `UCLASS(MinimalAPI, Within=LocalizationSettings)`
- inherits: `UObject`
- L577 _public member_ `TArray<TObjectPtr<ULocalizationTarget>> TargetObjects;` — `UPROPERTY(EditAnywhere, Category = "Targets")`
- L581 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API LOCALIZATION_API`

### `Source/Developer/Localization/Public/PortableObjectFormatDOM.h` (Public)


#### class `FPortableObjectCulture`  
`class FPortableObjectCulture`  
_L22-92_
- desc: Class for handling language codes used in the Portable Object format.
- L25 _public function_ `FPortableObjectCulture()`
- L28 _public prototype_ `FPortableObjectCulture( const FString& LangCode, const FString& PluralForms = TEXT("") );`
- L33 _public function_ `bool IsValid() const` — Checks to see if we have a language code and if we were able to match a culture to that code
- L38 _public prototype_ `void SetLanguageCode( const FString& LangCode );` — Sets the language code
- L43 _public function_ `const FString& GetLanguageCode() const` — Retrieves the language code
- L48 _public function_ `void SetPluralForms( const FString& InPluralForms )` — Sets the language plural forms.  This is only required if we wish to override the default plural forms associated with a language.
- L53 _public prototype_ `FString GetPluralForms() const;` — Retrieves the language plural forms.
- L58 _public prototype_ `FString Language() const;` — Retrieves the two or three letter language code for the culture
- L63 _public prototype_ `FString Country() const;` — Retrieves the country info of the culture
- L68 _public prototype_ `FString Variant() const;` — Retrieves the variant info for the culture
- L73 _public prototype_ `FString DisplayName() const;` — Retrieves the display name for the language.
- L78 _public prototype_ `FString EnglishName() const;` — Retrieves the English name for the language.
- L85 _private prototype_ `FString GetDefaultPluralForms() const;` — Retrieves the language default plural forms.  If no plural forms are provided for this language we use this to pull from a set of defaults if available.
- L88 _private member_ `FString LanguageCode;` — The language code as it appears in the PO file.
- L89 _private member_ `FString LanguagePluralForms;`
- L91 _private member_ `FCulturePtr Culture;`

#### class `FPortableObjectEntryKey`  
`class FPortableObjectEntryKey`  
_L98-136_
- desc: Class for representing the key of an entry in a Portable Object file(.po) or a Portable Object Template file(.pot).
- L101 _public function_ `FPortableObjectEntryKey()`
- L105 _public function_ `FPortableObjectEntryKey(const FString& InMsgId, const FString& InMsgIdPlural, const FString& InMsgCtxt) : MsgId(InMsgId) , MsgIdPlural(InMsgIdPlural) , MsgCtxt(InMsgCtxt)`
- L112 _public function_ `bool operator==(const FPortableObjectEntryKey& Other) const`
- L129 _public member_ `FString MsgId;` — Represents the original source text(also called the id or context).  Stored here are the msgid values from the Portable Object entries.
- L132 _public member_ `FString MsgIdPlural;` — Represents the plural form of the source text.  Stored here are the msgid_plural values from the Portable Object file entries.
- L135 _public member_ `FString MsgCtxt;` — Represents the disambiguating  context for the source text.  If used, will prevent two identical source strings from getting collapsed into one entry.

#### class `FPortableObjectEntry`  
`class FPortableObjectEntry : public FPortableObjectEntryKey`  
_L141-238_
- inherits: `FPortableObjectEntryKey`
- desc: Class for representing entries in a Portable Object file(.po) or a Portable Object Template file(.pot).
- L144 _public function_ `FPortableObjectEntry()`
- L153 _public prototype_ `void AddExtractedComment( const FString& InComment );` — Helper function that adds to the extracted comments. @param InComment		String representing an extracted comment entry.
- L160 _public prototype_ `void AddExtractedComments( const TArray<FString>& InComments );` — Helper function that adds to the extracted comments. @param InComments	String array representing extracted comment entries.
- L167 _public prototype_ `void AddTranslatorComment(const FString& InComment);` — Helper function that adds to the translator comments. @param InComment		String representing a translator comment entry.
- L174 _public prototype_ `void AddTranslatorComments(const TArray<FString>& InComments);` — Helper function that adds to the translator comments. @param InComments	String array representing the translator's notes.
- L181 _public prototype_ `void AddReference( const FString& InReference );` — Helper function that adds to the reference comments. @param InReference	String representing reference comment entries of the following form: "File/path/file.cpp:20 File/path/file.cpp:21 File/path/file2.cpp:5".
- L188 _public prototype_ `void AddReferences( const TArray<FString>& InReferences );` — Helper function that adds to the reference comments. @param InReferences	String array representing reference comment entries of the following form: "File/path/file.cpp:20 File/path/file.cpp:21 File/path/file2.cpp:5".
- L195 _public prototype_ `FString ToString() const;` — Function to convert the entry to a string. @return	String representing the entry that can be written directly to the .po file.
- L199 _public member_ `TArray< FString > MsgStr;` — Represents the translated text.  This stores the msgstr, msgstr[0], msgstr[1], etc values from Portable Object entries.
- L209 _public member_ `TArray<FString> ExtractedComments;` — Stores extracted comments. Lines starting with #. above the msgid. #. TRANSLATORS: A test phrase with all letters of the English alphabet. #. Replace it with a sample text in your language, such that it is #. representative of language's writing system. msgid "The Quick Brown Fox Jumps Over The Lazy Dog" msgstr ""
- L217 _public member_ `TArray<FString> TranslatorComments;` — Stores the translator comments.  Lines starting with # (hash and space), followed by any text whatsoever. # Wikipedia says that 'etrurski' is our name for this script. msgid "Old Italic" msgstr "etrurski"
- L226 _public member_ `TArray<FString> ReferenceComments;` — Stores a reference comments. Lines starting with #: above the msgid. #: /Engine/Source/Runtime/Engine/Private/Actor.cpp:2306 #: /Engine/Source/Runtime/Engine/Private/Actor.cpp:2307 /Engine/Source/Runtime/Engine/Private/Actor.cpp:2308 msgid "The Quick Brown Fox Jumps Over The Lazy Dog" msgstr ""
- L234 _public member_ `TArray<FString> Flags;` — Stores flags.  Lines starting with #, #, fuzzy msgid "The Quick Brown Fox Jumps Over The Lazy Dog" msgstr ""
- L237 _public member_ `TArray< FString > UnknownElements;` — Stores any unknown elements we may encounter when processing a Portable Object file.

#### class `FPortableObjectHeader`  
`class FPortableObjectHeader`  
_L245-307_
- desc: Class that stores and manipulates PO and POT file header info.
- L248 _public typedef_ `typedef TPair<FString, FString> FPOHeaderEntry;`
- L249 _public typedef_ `typedef TArray< FPOHeaderEntry > FPOHeaderData;`
- L251 _public function_ `FPortableObjectHeader()`
- L260 _public prototype_ `FString ToString() const;` — Creates a string representation of the Portable Object header. @return	String representing the header that can be written directly to the .po file.
- L268 _public function_ `bool FromString( const FString& InStr )` — Parses out header key/value pair entries. @param InStr	String representing a .po or .pot file header @return	Returns true if successful, false otherwise.
- L276 _public prototype_ `bool FromLocPOEntry( const TSharedRef<const FPortableObjectEntry> LocEntry );` — Parses out header info from a FPortableObjectEntry with an empty ID. @param LocEntry	The Portable Object entry with an empty ID @return	Returns true if successful, false otherwise.
- L279 _public prototype_ `bool HasEntry ( const FString& EntryKey ) const;` — Checks if a header entry exists with the given key
- L282 _public prototype_ `FString GetEntryValue ( const FString& EntryKey ) const;` — Gets the header entry value for the given key or the empty string if the key does not exist
- L285 _public prototype_ `void SetEntryValue( const FString& EntryKey, const FString& EntryValue );` — Sets a header entry value
- L290 _public prototype_ `void UpdateTimeStamp();` — Puts the current time into POT-Creation-Date and PO-Revision-Date entries
- L295 _public function_ `void Clear()` — Clears the header entries.
- L298 _private prototype_ `FPortableObjectHeader::FPOHeaderEntry* FindEntry( const FString& EntryKey );`
- L299 _private prototype_ `const FPortableObjectHeader::FPOHeaderEntry* FindEntry( const FString& EntryKey ) const;`
- L304 _public member_ `TArray<FString> Comments;` — Stores the header comment block
- L306 _public member_ `FPOHeaderData HeaderEntries;` — Stores all the header key/value pairs

#### class `FPortableObjectFormatDOM`  
`class FPortableObjectFormatDOM`  
_L312-395_
- desc: Contains all the info we need to represent files in the Portable Object format.
- L315 _public function_ `FPortableObjectFormatDOM()`
- L319 _public function_ `FPortableObjectFormatDOM( const FString& LanguageCode ) : Language( LanguageCode )`
- L325 _public prototype_ `FPortableObjectFormatDOM(const FPortableObjectFormatDOM&) = delete;` — Copying is not supported
- L326 _public prototype_ `FPortableObjectFormatDOM& operator=(const FPortableObjectFormatDOM&) = delete;`
- L333 _public prototype_ `FString ToString();` — Creates a string representation of the Portable Object. @return	String representing the Portable Object that can be written directly to a file.
- L334 _public prototype_ `void ToString(FString& OutString);`
- L343 _public prototype_ `bool FromString( const FString& InStr, FText* OutErrorMsg = nullptr );` — Parses Portable Object elements from a string. @param InStr	String representing a Portable Object file(.PO) or Portable Object Template file(.POT). @param OutErrorMsg Optional Text to be filled with error information. @return	Returns true if successful, false otherwise.
- L346 _public prototype_ `void CreateNewHeader( const FString& InCopyrightNotice = FString() );` — Creates a header entry based on the project and language info.
- L352 _public prototype_ `void SetHeaderValue(const FString& EntryKey, const FString& EntryValue);` — Sets a header entry value. @note Must be called after CreateNewHeader.
- L361 _public prototype_ `bool SetLanguage( const FString& LanguageCode, const FString& LangPluralForms = TEXT("") );` — Sets the language. @param LanguageCode	String representing a Portable Object language code. @param LangPluralForms	Optional plural forms for the language.  If not provided, defaults will be used if found. @return	Returns true if the function was able to successfully set the language code and pair it with a known culture, false otherwise.
- L369 _public prototype_ `bool AddEntry( const TSharedRef<FPortableObjectEntry> LocEntry );` — Adds a translation entry to the Portable Object. @param LocEntry	The LocPOEntry to add. @return	Returns true if successful, false otherwise.
- L372 _public prototype_ `TSharedPtr<FPortableObjectEntry> FindEntry( const TSharedRef<const FPortableObjectEntry> LocEntry ) const;` — Returns the Portable Object entry that matches the passed in entry or NULL if not found
- L375 _public prototype_ `TSharedPtr<FPortableObjectEntry> FindEntry( const FString& MsgId, const FString& MsgIdPlural, const FString& MsgCtxt ) const;` — Returns the Portable Object file entry that matches the passed in parameters or NULL if not found
- L378 _public function_ `void SetProjectName( const FString& ProjName )` — Sets the project name that will appear in the Project-Id-Version header entry
- L381 _public function_ `FString GetProjectName() const` — Sets the project name from the Project-Id-Version header entry
- L383 _public function_ `FPortableObjectEntries::TConstIterator GetEntriesIterator() const`
- L388 _public prototype_ `void SortEntries();`
- L391 _private member_ `FPortableObjectCulture Language;`
- L392 _private member_ `FPortableObjectHeader Header;`
- L393 _private member_ `FString ProjectName;`
- L394 _private member_ `FPortableObjectEntries Entries;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API LOCALIZATION_API`
- L119 _function_ `friend inline uint32 GetTypeHash(const FPortableObjectEntryKey& Key)`
- L240 _typedef_ `typedef TMap<FPortableObjectEntryKey, TSharedPtr<FPortableObjectEntry>> FPortableObjectEntries;`

### `Source/Developer/Localization/Public/PortableObjectPipeline.h` (Public)


#### enum `ELocalizedTextCollapseMode`  
`enum class ELocalizedTextCollapseMode : uint8`  
_L19-27_
- reflection: `UENUM()`
- L22 _public enumerator_ `IdenticalTextIdAndSource UMETA(DisplayName = "Identical Text Identity (Namespace + Key) and Source Text")` — Collapse texts with the same text identity (namespace + key) and source text (default 4.15+ behavior).
- L24 _public enumerator_ `IdenticalPackageIdTextIdAndSource UMETA(DisplayName = "Identical Package ID, Text Identity (Namespace + Key) and Source Text", Hidden)` — Collapse texts with the same package ID, text identity (namespace + key), and source text (deprecated 4.14 behavior, removed in 4.17).
- L26 _public enumerator_ `IdenticalNamespaceAndSource UMETA(DisplayName = "Identical Namespace and Source Text")` — Collapse texts with the same namespace and source text (legacy pre-4.14 behavior).

#### enum `EPortableObjectFormat`  
`enum class EPortableObjectFormat : uint8`  
_L30-62_
- reflection: `UENUM()`
- L45 _public enumerator_ `Unreal` — The PO file uses the Unreal format. When using the "Identical Text Identity and Source Text" collapse mode: - msgctxt contains the Unreal identity of the entry. - msgid contains the source string. - msgstr contains the translation. When using the "Identical Namespace and Source Text" collapse mode: - msgctxt contains the Unreal namespace of the entry. - msgid contains the source string. - msgstr contains the translation.
- L61 _public enumerator_ `Crowdin` — The PO file uses the Crowdin format. When using the "Identical Text Identity and Source Text" collapse mode: - msgctxt is unused. - msgid contains the Unreal identity of the entry. - msgstr contains the source string (for the native culture), or the translation (for foreign cultures). - X-Crowdin-SourceKey header attribute specifies that msgstr is used as the source text from the native culture. When using the "Identical Namespace and Source Text" collapse mode: - msgctxt contains the Unreal namespace of the entry. - msgid contains the source string. - msgstr contains the translation.

#### Free symbols / members of external scopes

- L64 _namespace_ `namespace PortableObjectPipeline`
- L67 _prototype_ `bool Import(FLocTextHelper& InLocTextHelper, const FString& InCulture, const FString& InPOFilePath, const ELocalizedTextCollapseMode InTextCollapseMode, const EPortableObjectFormat InPOFormat);` (scope `PortableObjectPipeline`) — Update the given LocTextHelper with the translation data imported from the PO file for the given culture
- L70 _prototype_ `bool ImportAll(FLocTextHelper& InLocTextHelper, const FString& InPOCultureRootPath, const FString& InPOFilename, const ELocalizedTextCollapseMode InTextCollapseMode, const EPortableObjectFormat InPOFormat, const bool bUseCultureDirectory);` (scope `PortableObjectPipeline`) — Update the given LocTextHelper with the translation data imported from the PO file for all cultures
- L73 _prototype_ `bool Export(FLocTextHelper& InLocTextHelper, const FString& InCulture, const FString& InPOFilePath, const ELocalizedTextCollapseMode InTextCollapseMode, const EPortableObjectFormat InPOFormat, const bool bShouldPersistComments);` (scope `PortableObjectPipeline`) — Use the given LocTextHelper to generate a new PO file using the translation data for the given culture
- L76 _prototype_ `bool ExportAll(FLocTextHelper& InLocTextHelper, const FString& InPOCultureRootPath, const FString& InPOFilename, const ELocalizedTextCollapseMode InTextCollapseMode, const EPortableObjectFormat InPOFormat, const bool bShouldPersistComments, const bool bUseCultureDirectory);` (scope `PortableObjectPipeline`) — Use the given LocTextHelper to generate a new PO file using the translation data for all cultures
- L79 _prototype_ `FString ConditionIdentityForPO(const FString& Namespace, const FString& Key, const TSharedPtr<FLocMetadataObject>& KeyMetaData, const ELocalizedTextCollapseMode InTextCollapseMode);` (scope `PortableObjectPipeline`) — Given a namespace and key, condition this information so it can be written to the "msgctxt" or "msgid" field of a PO file
- L82 _prototype_ `void ParseIdentityFromPO(const FString& InIdentity, FString& OutNamespace, FString& OutKey);` (scope `PortableObjectPipeline`) — Given the "msgctxt" or "msgid" field of a PO file, split it into the namespace and key
- L85 _prototype_ `FString ConditionArchiveStrForPO(const FString& InStr);` (scope `PortableObjectPipeline`) — Given a string, condition it so it can be written as a field of a PO file
- L88 _prototype_ `FString ConditionPOStringForArchive(const FString& InStr);` (scope `PortableObjectPipeline`) — Given the field of a PO file, condition it back to a clean string
- L91 _prototype_ `FString GetConditionedKeyForExtractedComment(const FString& Key);` (scope `PortableObjectPipeline`) — Given a key string, condition it so it can be written as the extracted comment field of a PO file
- L94 _prototype_ `FString GetConditionedReferenceForExtractedComment(const FString& PORefString);` (scope `PortableObjectPipeline`) — Given a source location string, condition it so it can be written as the extracted comment field of a PO file
- L97 _prototype_ `FString GetConditionedDevNotesForExtractedComment(const FString& DevNotes);` (scope `PortableObjectPipeline`) — Given developer-entered translator context notes, condition it so it can be written as the extracted comment field of a PO file
- L100 _prototype_ `FString GetConditionedInfoMetaDataForExtractedComment(const FString& KeyName, const FString& ValueString);` (scope `PortableObjectPipeline`) — Given a meta-data value string, condition it so it can be written as the extracted comment field of a PO file
- L103 _prototype_ `void UpdatePOFileHeaderForSettings(FPortableObjectFormatDOM& PortableObject, const ELocalizedTextCollapseMode InTextCollapseMode, const EPortableObjectFormat InPOFormat);` (scope `PortableObjectPipeline`) — Given the collapse mode and PO format, append any extra required meta-data to the PO file header
- L106 _prototype_ `void PopulateBasicPOFileEntry(FPortableObjectEntry& POEntry, const FString& InNamespace, const FString& InKey, const TSharedPtr<FLocMetadataObject>& InKeyMetaData, const FString& InSourceString, const FString& InTranslation, const ELocalizedTextCollapseMode InTextCollapseMode, const EPortableObjectFormat InPOFormat);` (scope `PortableObjectPipeline`) — Populate the basic data (msgctxt, msgid, msgstr) within a PO entry
- L109 _prototype_ `void ParseBasicPOFileEntry(const FPortableObjectEntry& POEntry, FString& OutNamespace, FString& OutKey, FString& OutSourceString, FString& OutTranslation, const ELocalizedTextCollapseMode InTextCollapseMode, const EPortableObjectFormat InPOFormat);` (scope `PortableObjectPipeline`) — Parse the basic data (msgctxt, msgid, msgstr) from a PO entry

### `Source/Developer/Localization/Public/Serialization/JsonInternationalizationArchiveSerializer.h` (Public)


#### class `FJsonInternationalizationArchiveSerializer`  
`class FJsonInternationalizationArchiveSerializer`  
_L23-160_
- desc: Implements a serializer that serializes to and from Json encoded data.
- L37 _public prototype_ `static bool DeserializeArchiveFromString(const FString& InStr, TSharedRef<FInternationalizationArchive> InArchive, TSharedPtr<const FInternationalizationManifest> InManifest, TSharedPtr<const FInternationalizationArchive> InNativeArchive);` — Deserializes an archive from a JSON string. @param InStr				The JSON string to deserialize from. @param InArchive			The archive to populate from the JSON data. @param InManifest		The manifest associated with the archive. May be null, but you won't be able to load archives with a version < FInternationalizationArchive::EFormatVersion::AddedKeys. @param InNativeArchive	The native archive associated with the archive. May be null. @return true if deserialization was successful, false otherwise.
- L49 _public prototype_ `static bool DeserializeArchiveFromFile(const FString& InJsonFile, TSharedRef<FInternationalizationArchive> InArchive, TSharedPtr<const FInternationalizationManifest> InManifest, TSharedPtr<const FInternationalizationArchive> InNativeArchive);` — Deserializes an archive from a JSON file. @param InJsonFile		The path to the JSON file to deserialize from. @param InArchive			The archive to populate from the JSON data. @param InManifest		The manifest associated with the archive. May be null, but you won't be able to load archives with a version < FInternationalizationArchive::EFormatVersion::AddedKeys. @param InNativeArchive	The native archive associated with the archive. May be null. @return true if deserialization was successful, false otherwise.
- L59 _public prototype_ `static bool SerializeArchiveToString(TSharedRef<const FInternationalizationArchive> InArchive, FString& Str);` — Serializes an archive to a JSON string. @param InArchive			The archive data to serialize. @param Str				The string to fill with the JSON data. @return true if serialization was successful, false otherwise.
- L69 _public prototype_ `static bool SerializeArchiveToFile(TSharedRef<const FInternationalizationArchive> InArchive, const FString& InJsonFile);` — Serializes an archive to a JSON string. @param InArchive			The archive data to serialize. @param InJsonFile			The path to the JSON file to serialize to. @return true if serialization was successful, false otherwise.
- L98 _private prototype_ `static bool DeserializeInternal(UE::Json::FConstObject InJsonObj, TSharedRef<FInternationalizationArchive> InArchive, TSharedPtr<const FInternationalizationManifest> InManifest, TSharedPtr<const FInternationalizationArchive> InNativeArchive);` — Deserializes an archive from a JSON object. @param InJsonObj			The JSON object to serialize from. @param InArchive			The archive to populate from the JSON data. @param InManifest		The manifest associated with the archive. May be null, but you won't be able to load archives with a version < FInternationalizationArchive::EFormatVersion::AddedKeys. @param InNativeArchive	The native archive associated with the archive. May be null. @return true if deserialization was successful, false otherwise.
- L107 _private prototype_ `static bool SerializeInternal(TSharedRef<const FInternationalizationArchive> InArchive, UE::Json::FObject JsonObj, UE::Json::FAllocator& Allocator);` — Convert a Internationalization archive to a JSON object. @param InArchive The Internationalization archive object to serialize from. @param JsonObj The Json object that will store the data. @return true if serialization was successful, false otherwise.
- L120 _private prototype_ `static bool JsonObjToArchive(UE::Json::FConstObject InJsonObj, const FString& ParentNamespace, TSharedRef<FInternationalizationArchive> InArchive, TSharedPtr<const FInternationalizationManifest> InManifest, TSharedPtr<const FInternationalizationArchive> InNativeArchive);` — Recursive function that will traverse the JSON object and populate an archive. @param InJsonObj			The JSON object to serialize from. @param ParentNamespace	The namespace of the parent JSON object. @param InArchive			The archive to populate from the JSON data. @param InManifest		The manifest associated with the archive. May be null, but you won't be able to load archives with a version < FInternationalizationArchive::EFormatVersion::AddedKeys. @param InNativeArchive	The native archive associated with the archive. May be null. @return true if successful, false otherwise.
- L128 _private prototype_ `static void GenerateStructuredData( TSharedRef< const FInternationalizationArchive > InArchive, TSharedPtr< FStructuredArchiveEntry > RootElement );` — Takes a Internationalization archive and arranges the data into a hierarchy based on namespace. @param InArchive The Internationalization archive. @param RootElement The root element of the structured data.
- L135 _private prototype_ `static void SortStructuredData( TSharedPtr< FStructuredArchiveEntry > InElement );` — Goes through the structured, hierarchy based, archive data and does a non-culture specific sort on namespaces and default text. @param RootElement The root element of the structured data.
- L143 _private prototype_ `static void StructuredDataToJsonObj(TSharedPtr< const FStructuredArchiveEntry > InElement, UE::Json::FObject JsonObj, UE::Json::FAllocator& Allocator);` — Populates a JSON object from Internationalization archive data that has been structured based on namespace. @param InElement Internationalization archive data structured based on namespace. @param JsonObj JSON object to be populated.
- L145 _private member_ `static const FString TAG_FORMATVERSION;`
- L146 _private member_ `static const FString TAG_NAMESPACE;`
- L147 _private member_ `static const FString TAG_KEY;`
- L148 _private member_ `static const FString TAG_CHILDREN;`
- L149 _private member_ `static const FString TAG_SUBNAMESPACES;`
- L150 _private member_ `static const FString TAG_DEPRECATED_DEFAULTTEXT;`
- L151 _private member_ `static const FString TAG_DEPRECATED_TRANSLATEDTEXT;`
- L152 _private member_ `static const FString TAG_OPTIONAL;`
- L153 _private member_ `static const FString TAG_SOURCE;`
- L154 _private member_ `static const FString TAG_SOURCE_TEXT;`
- L155 _private member_ `static const FString TAG_TRANSLATION;`
- L156 _private member_ `static const FString TAG_TRANSLATION_TEXT;`
- L157 _private member_ `static const FString TAG_METADATA;`
- L158 _private member_ `static const FString TAG_METADATA_KEY;`
- L159 _private member_ `static const FString NAMESPACE_DELIMITER;`

#### struct `FJsonInternationalizationArchiveSerializer::FStructuredArchiveEntry`  
`struct FStructuredArchiveEntry`  
_L76-86_
- desc: Used to arrange Internationalization archive data in a hierarchy based on namespace prior to json serialization.
- L78 _public function_ `explicit FStructuredArchiveEntry(const FString& InNamespace) : Namespace(InNamespace)`
- L83 _public member_ `const FString Namespace;`
- L84 _public member_ `TMap<FString, TSharedPtr<FStructuredArchiveEntry>, FDefaultSetAllocator, FLocKeyMapFuncs<TSharedPtr<FStructuredArchiveEntry>>> SubNamespaces;`
- L85 _public member_ `TArray<TSharedPtr<FArchiveEntry>> ArchiveEntries;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LOCALIZATION_API`

### `Source/Developer/Localization/Public/Serialization/JsonInternationalizationManifestSerializer.h` (Public)


#### class `FJsonInternationalizationManifestSerializer`  
`class FJsonInternationalizationManifestSerializer`  
_L22-161_
- desc: Implements a serializer that serializes to and from Json encoded data.
- L33 _public prototype_ `static bool DeserializeManifestFromString( const FString& InStr, TSharedRef< FInternationalizationManifest > Manifest, const FName PlatformName = FName() );` — Deserializes a Internationalization manifest from a JSON string. @param InStr The JSON string to deserialize from. @param Manifest The populated Internationalization manifest. @return true if deserialization was successful, false otherwise.
- L42 _public prototype_ `static bool DeserializeManifestFromFile( const FString& InJsonFile, TSharedRef< FInternationalizationManifest > Manifest, const FName PlatformName = FName() );` — Deserializes a Internationalization manifest from a JSON file. @param InJsonFile The path to the JSON file to deserialize from. @param Manifest The populated Internationalization manifest. @return true if deserialization was successful, false otherwise.
- L51 _public prototype_ `static bool SerializeManifestToString( TSharedRef< const FInternationalizationManifest > Manifest, FString& Str );` — Serializes a Internationalization manifest to a JSON string. @param Manifest The Internationalization manifest data to serialize. @param Str The string to serialize into. @return true if serialization was successful, false otherwise.
- L60 _public prototype_ `static bool SerializeManifestToFile( TSharedRef< const FInternationalizationManifest > Manifest, const FString& InJsonFile );` — Serializes a Internationalization manifest to a JSON file. @param Manifest The Internationalization manifest data to serialize. @param InJsonFile The path to the JSON file to serialize to. @return true if serialization was successful, false otherwise.
- L65 _public prototype_ `static void SortManifest(const TSharedRef<FInternationalizationManifest>& Manifest);` — Sort an Internationalization manifest as if it had been serialized and then deserialized from JSON.
- L89 _private prototype_ `static bool DeserializeInternal( UE::Json::FConstObject InJsonObj, TSharedRef< FInternationalizationManifest > Manifest, const FName PlatformName );` — Convert a JSON object to a Internationalization manifest. @param InJsonObj The JSON object to serialize from. @param Manifest The Internationalization manifest that will store the data. @return true if deserialization was successful, false otherwise.
- L99 _private prototype_ `static bool SerializeInternal( TSharedRef< const FInternationalizationManifest > InManifest, UE::Json::FObject JsonObj, UE::Json::FAllocator& Allocator );` — Convert a Internationalization manifest to a JSON object. @param InManifest The Internationalization manifest object to serialize from. @param JsonObj The Json object that will store the data. @return true if serialization was successful, false otherwise.
- L110 _private prototype_ `static bool JsonObjToManifest( UE::Json::FConstObject InJsonObj, FString InNamespace, TSharedRef< FInternationalizationManifest > Manifest, const FName PlatformName );` — Recursive function that will traverse the JSON object and populate a Internationalization manifest. @param InJsonObj The JSON object. @param InNamespace The namespace of the parent JSON object. @param Manifest The Internationalization manifest that will store the data. @return true if successful, false otherwise.
- L118 _private prototype_ `static void GenerateStructuredData( TSharedRef< const FInternationalizationManifest > InManifest, TSharedPtr< FStructuredEntry > RootElement );` — Takes a Internationalization manifest and arranges the data into a hierarchy based on namespace. @param InManifest The Internationalization manifest. @param RootElement The root element of the structured data.
- L125 _private prototype_ `static void SortStructuredData( TSharedPtr< FStructuredEntry > InElement );` — Goes through the structured, hierarchy based, manifest data and does a non-culture specific sort on namespaces, default text, and key. @param RootElement The root element of the structured data.
- L133 _private prototype_ `static void StructuredDataToManifest(const TSharedPtr<const FStructuredEntry>& InElement, const TSharedRef<FInternationalizationManifest>& Manifest);` — Populates an Internationalization manifest from data that has been structured based on namespace. @param InElement The structured data. @param Manifest The Internationalization manifest that will store the data.
- L141 _private prototype_ `static void StructuredDataToJsonObj( TSharedPtr< const FStructuredEntry> InElement, UE::Json::FObject JsonObj, UE::Json::FAllocator& Allocator );` — Populates a JSON object from Internationalization manifest data that has been structured based on namespace. @param InElement Internationalization manifest data structured based on namespace. @param JsonObj JSON object to be populated.
- L144 _private member_ `static const FString TAG_FORMATVERSION;`
- L145 _private member_ `static const FString TAG_NAMESPACE;`
- L146 _private member_ `static const FString TAG_CHILDREN;`
- L147 _private member_ `static const FString TAG_SUBNAMESPACES;`
- L148 _private member_ `static const FString TAG_PATH;`
- L149 _private member_ `static const FString TAG_DEVNOTES;`
- L150 _private member_ `static const FString TAG_OPTIONAL;`
- L151 _private member_ `static const FString TAG_KEYCOLLECTION;`
- L152 _private member_ `static const FString TAG_KEY;`
- L153 _private member_ `static const FString TAG_DEPRECATED_DEFAULTTEXT;`
- L154 _private member_ `static const FString TAG_SOURCE;`
- L155 _private member_ `static const FString TAG_SOURCE_TEXT;`
- L156 _private member_ `static const FString TAG_PLATFORM_NAME;`
- L157 _private member_ `static const FString TAG_METADATA;`
- L158 _private member_ `static const FString TAG_METADATA_INFO;`
- L159 _private member_ `static const FString TAG_METADATA_KEY;`
- L160 _private member_ `static const FString NAMESPACE_DELIMITER;`

#### struct `FJsonInternationalizationManifestSerializer::FStructuredEntry`  
`struct FStructuredEntry`  
_L69-79_
- L71 _public function_ `explicit FStructuredEntry(const FString& InNamespace) : Namespace(InNamespace)`
- L76 _public member_ `const FString Namespace;`
- L77 _public member_ `TMap<FString, TSharedPtr<FStructuredEntry>, FDefaultSetAllocator, FLocKeyMapFuncs<TSharedPtr<FStructuredEntry>>> SubNamespaces;`
- L78 _public member_ `TArray<TSharedPtr<FManifestEntry>> ManifestEntries;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LOCALIZATION_API`

### `Source/Developer/Localization/Public/Serialization/JsonInternationalizationMetadataSerializer.h` (Public)


#### class `FJsonInternationalizationMetaDataSerializer`  
`class FJsonInternationalizationMetaDataSerializer`  
_L13-38_
- L22 _public prototype_ `static void DeserializeMetadata( UE::Json::FConstObject JsonObj, TSharedPtr< FLocMetadataObject >& OutMetadataObj );` — Deserializes manifest metadata from a JSON object. @param JsonObj The JSON object to deserialize from. @param OutMetadataObj The resulting metadata object, or an unmodified object if the serialize is not successful.
- L30 _public prototype_ `static void SerializeMetadata( const TSharedRef< FLocMetadataObject > Metadata, UE::Json::FValue& OutJsonObj, UE::Json::FAllocator& Allocator );` — Serializes manifest metadata object to a JSON object. @param Metadata The Internationalization metadata to serialize. @param OutJsonObj The resulting JSON object or an unmodified object if the serialize is not successful.
- L37 _public prototype_ `static FString MetadataToString( const TSharedPtr<FLocMetadataObject> Metadata );` — Utility function that will convert metadata to string using the JSON metadata serializer. @param Metadata The Internationalization metadata to convert to string.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LOCALIZATION_API`

### `Source/Developer/Localization/Public/TextLocalizationResourceGenerator.h` (Public)


#### enum `EGenerateLocResFlags`  
`enum class EGenerateLocResFlags : uint8`  
_L18-30_
- L21 _public enumerator_ `None = 0` — No special behavior
- L23 _public enumerator_ `AllowStaleTranslations = 1<<0` — Should "stale" translations (translations that were made against different source text) still be used?
- L25 _public enumerator_ `ValidateFormatPatterns = 1<<1` — Validate that format patterns are valid for the culture being compiled (eg, detect invalid plural rules or broken syntax)
- L27 _public enumerator_ `ValidateSafeWhitespace = 1<<2` — Validate that text doesn't contain any unsafe whitespace (leading or trailing whitespace) that could get lost during the translation process
- L29 _public enumerator_ `ValidateRichTextTags = 1<<3` — Validate that rich text tags have not been broken during translation

#### class `FTextLocalizationResourceGenerator`  
`class FTextLocalizationResourceGenerator`  
_L34-51_
- desc: Utility functions for generating compiled LocMeta (Localization MetaData Resource) and LocRes (Localization Resource) files from source localization data
- L40 _public prototype_ `static bool GenerateLocMeta(const FLocTextHelper& InLocTextHelper, const FString& InResourceName, FTextLocalizationMetaDataResource& OutLocMeta);` — Given a loc text helper, generate a compiled LocMeta resource.
- L45 _public prototype_ `static bool GenerateLocRes(const FLocTextHelper& InLocTextHelper, const FString& InCultureToGenerate, const EGenerateLocResFlags InGenerateFlags, const FTextKey& InLocResID, FTextLocalizationResource& OutPlatformAgnosticLocRes, TMap<FName, TSharedRef<FTextLocalizationResource>>& OutPerPlatformLocRes, const int32 InPriority = 0);` — Given a loc text helper, generate a compiled LocRes resource for the given culture.
- L50 _public prototype_ `static bool GenerateLocResAndUpdateLiveEntriesFromConfig(const FString& InConfigFilePath, const EGenerateLocResFlags InGenerateFlags);` — Given a config file, generate a compiled LocRes resource for the active culture and use it to update the live-entries in the localization manager.

#### Free symbols / members of external scopes

- L31 _prototype_ `ENUM_CLASS_FLAGS(EGenerateLocResFlags);`

### `Source/Developer/Localization/Public/UserGeneratedContentLocalization.h` (Public)


#### class `UUserGeneratedContentLocalizationSettings`  
`class UUserGeneratedContentLocalizationSettings : public UObject`  
_L29-53_
- reflection: `UCLASS(MinimalAPI, config=Engine, defaultconfig)`
- inherits: `UObject`
- desc: Settings controlling UGC localization.
- L39 _public member_ `TArray<FString> CulturesToDisable;` — `UPROPERTY(config, EditAnywhere, Category=Localization)` — List of cultures that should be disabled for UGC localization. @note You can't disable the native culture for the project.
- L45 _public member_ `bool bCompileDLCLocalizationDuringCook = true;` — `UPROPERTY(config, EditAnywhere, Category=Localization)` — Should we compile UGC localization (if present) for DLC plugins during cook?
- L52 _public member_ `bool bValidateDLCLocalizationDuringCook = true;` — `UPROPERTY(config, EditAnywhere, Category=Localization)` — Should we validate UGC localization (if present) for DLC plugins during cook? @note Validation will happen against a UGC localization descriptor that has had InitializeFromProject called on it.

#### struct `FUserGeneratedContentLocalizationDescriptor`  
`struct FUserGeneratedContentLocalizationDescriptor`  
_L59-113_
- reflection: `USTRUCT()`
- desc: Minimal descriptor needed to generate a localization target for UGC localization.
- L68 _public prototype_ `void InitializeFromProject(const ELocalizedTextSourceCategory LocalizationCategory = ELocalizedTextSourceCategory::Game);` — Initialize the NativeCulture and CulturesToGenerate values based on the settings of the currently loaded Unreal project. @param LocalizationCategory What category is the localization targets being used with this descriptor?
- L77 _public prototype_ `bool Validate(const FUserGeneratedContentLocalizationDescriptor& DefaultDescriptor);` — Validate that this descriptor isn't using cultures that aren't present in the CulturesToGenerate of the given default. - If the NativeCulture is invalid, reset it to the value from the default. - If CulturesToGenerate contains invalid entries then remove those from the array. @return True if this descriptor was valid and no changes were made. False if this descriptor was invalid and had default changes applied.
- L82 _public prototype_ `bool ToJsonObject(TSharedPtr<FJsonObject>& OutJsonObject) const;` — Save the settings to a JSON object/file.
- L83 _public prototype_ `bool ToJsonString(FString& OutJsonString) const;`
- L84 _public prototype_ `bool ToJsonFile(const TCHAR* InFilename) const;`
- L89 _public prototype_ `bool FromJsonObject(TSharedRef<const FJsonObject> InJsonObject);` — Load the settings from a JSON object/file.
- L90 _public prototype_ `bool FromJsonString(const FString& InJsonString);`
- L91 _public prototype_ `bool FromJsonFile(const TCHAR* InFilename);`
- L98 _public member_ `FString NativeCulture;` — `UPROPERTY(EditAnywhere, Category=Localization, DisplayName="Native Language")` — The language that the source text is authored in. @note You shouldn't change this once you start to localize your text.
- L105 _public member_ `TArray<FString> CulturesToGenerate;` — `UPROPERTY(EditAnywhere, Category=Localization, DisplayName="Languages to Generate")` — The languages that we should generate localization data for. @note Will implicitly always contain the native language during export/compile.
- L112 _public member_ `EPortableObjectFormat PoFormat = EPortableObjectFormat::Unreal;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category=Localization, DisplayName="PO Format")` — What format of PO file should we use? @note You can adjust this later and we'll attempt to preserve any existing localization data by importing with the old setting prior to export.

#### struct `UserGeneratedContentLocalization::FExportLocalizationOptions`  
`struct FExportLocalizationOptions`  
_L127-161_
- L130 _public member_ `FUserGeneratedContentLocalizationDescriptor UGCLocDescriptor;` — Common export options for all plugins
- L133 _public member_ `TMap<FString, FString> PluginNameToCollectionNameFilter;` — Optional mapping of plugin names to collection names (to act as a filter for their asset gather step)
- L136 _public member_ `bool bGatherSource = true;` — True to gather localization from source code (if a plugin has a Config or Source folder)
- L139 _public member_ `bool bGatherAssets = true;` — True to gather localization from assets
- L142 _public member_ `bool bGatherVerse = true;` — True to gather localization from Verse
- L145 _public member_ `bool bUpdatePluginDescriptor = true;` — True to update the plugin descriptors (if needed) so that they contain the exported localization target
- L148 _public member_ `bool bAutoCleanup = true;` — True to automatically clean-up any scratch data created during the localization export
- L151 _public member_ `ELocalizedTextSourceCategory LocalizationCategory = ELocalizedTextSourceCategory::Game;` — The category to use for the exported localization target (only used when bUpdatePluginDescriptor is true)
- L154 _public member_ `FString CopyrightNotice;` — An optional copyright notice to insert into the exported files
- L157 _public member_ `FString LocalizationTargetRootDirectoryOverride;` — An optional override for the root directory that we import/export the localization target data to, generating a sub-folder for each target exported (@see GetLocalizationTargetName, @see GetLocalizationTargetDirectory)
- L160 _public member_ `TOptional<EMergeLocalizationMode> MergeProjectDataWithRootDirectoryOverrideData;` — If set, merge any existing plugin localization data with the data copied from LocalizationTargetRootDirectoryOverride (in the export scratch directory) prior to running the export

#### enum `UserGeneratedContentLocalization::ELoadLocalizationResult`  
`enum class ELoadLocalizationResult : uint8`  
_L163-171_
- L166 _public enumerator_ `NoData` — There was no source localization data to load
- L168 _public enumerator_ `Failed` — There was source localization data to load, but we failed to load it
- L170 _public enumerator_ `Success` — There was source localization data to load, and we successfully loaded it

#### enum `UserGeneratedContentLocalization::EMergeLocalizationMode`  
`enum class EMergeLocalizationMode : uint8`  
_L173-185_
- L178 _public enumerator_ `Untranslated` — Only merge untranslated strings
- L184 _public enumerator_ `All` — Merge all strings, even if they have an existing translation @note This will overwrite any existing translation data

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API LOCALIZATION_API`
- L122 _namespace_ `namespace UserGeneratedContentLocalization`
- L190 _prototype_ `FStringView GetLocalizationTargetNameFieldName();` (scope `UserGeneratedContentLocalization`) — Gets the name of the custom plugin field used to store the localization target name.
- L195 _prototype_ `FString GetLocalizationTargetName(const TSharedRef<IPlugin>& Plugin);` (scope `UserGeneratedContentLocalization`) — Utility to get the name of the UGC localization target that would be used by the given plugin.
- L202 _prototype_ `bool SetLocalizationTargetName(const TSharedRef<IPlugin>& Plugin, const FString& LocalizationTargetName, bool bUseSourceControl, FText& OutFailReason);` (scope `UserGeneratedContentLocalization`) — Utility to set the name of the UGC localization target that will be used by the given plugin.
- L209 _prototype_ `FString GetLocalizationTargetDirectory(const TSharedRef<IPlugin>& Plugin);` (scope `UserGeneratedContentLocalization`) — Utility to get the path of the UGC localization target directory that would be used by the given plugin.
- L214 _prototype_ `FString GetLocalizationTargetDirectory(const TSharedRef<IPlugin>& Plugin, const FString& LocalizationTargetRootDirectoryOverride);` (scope `UserGeneratedContentLocalization`) — Utility to get the path of the UGC localization target directory that would be used by the given plugin, based on the given root directory override (@see FExportLocalizationOptions).
- L219 _prototype_ `FString GetLocalizationTargetDirectory(const FString& LocalizationTargetName, const FString& PluginContentDirectory);` (scope `UserGeneratedContentLocalization`) — Utility to get the path of the UGC localization target that would be used by the given target name and directory.
- L224 _prototype_ `FString GetLocalizationTargetDirectory(const FString& LocalizationTargetName, const FString& PluginContentDirectory, const FString& LocalizationTargetRootDirectoryOverride);` (scope `UserGeneratedContentLocalization`) — Utility to get the path of the UGC localization target that would be used by the given target name and directory, based on the given root directory override (@see FExportLocalizationOptions).
- L229 _prototype_ `FString GetLocalizationTargetUGCLocFile(const FString& LocalizationTargetName, const FString& LocalizationTargetDirectory);` (scope `UserGeneratedContentLocalization`) — Utility to get the UGCLoc file for for the given UGC localization target name and directory.
- L234 _prototype_ `FString GetLocalizationTargetPOFile(const FString& LocalizationTargetName, const FString& LocalizationTargetDirectory, const FString& Culture);` (scope `UserGeneratedContentLocalization`) — Utility to get the PO file for for the given UGC localization target name and directory, and the given culture.
- L240 _prototype_ `void PreWriteFileWithSCC(const FString& Filename, const bool bUseSourceControl = true);` (scope `UserGeneratedContentLocalization`) — `UE_DEPRECATED(5.8, "PreWriteFileWithSCC is deprecated in favor of CreateLocFileNotifies, as the latter can batch SCC requests via BeginParallelTasks/EndParallelTasks")` — Utility to prepare a SCC managed file for writing.
- L246 _prototype_ `void PostWriteFileWithSCC(const FString& Filename, const bool bUseSourceControl = true);` (scope `UserGeneratedContentLocalization`) — `UE_DEPRECATED(5.8, "PostWriteFileWithSCC is deprecated in favor of CreateLocFileNotifies, as the latter can batch SCC requests via BeginParallelTasks/EndParallelTasks")` — Utility to update a SCC managed file after writing.
- L251 _prototype_ `FLocFileSCCNotifies CreateLocFileNotifies(const bool bUseSourceControl = true);` (scope `UserGeneratedContentLocalization`) — Create a loc file notifies helper that will use source control if currently enabled.
- L263 _prototype_ `bool ExportLocalization(TArrayView<const TSharedRef<IPlugin>> Plugins, const FExportLocalizationOptions& ExportOptions, TFunctionRef<int32(const FString&, FString&)> CommandletExecutor);` (scope `UserGeneratedContentLocalization`) — Export UGC localization for the given plugins. @param Plugins				The list of plugins to export. @param ExportOptions			Options controlling how to export the localization data. @param CommandletExecutor	Callback used to actually execute the gather commandlet: This should execute an editor with `-run=GatherText -config="..."`, where the config argument is the first argument passed to this callback. The second argument should be filled with the raw log output from running the commandlet process. The return value is the exit code of the commandlet process (where zero means success).
- L271 _prototype_ `bool CompileLocalization(TArrayView<const TSharedRef<IPlugin>> Plugins, const FUserGeneratedContentLocalizationDescriptor* DefaultDescriptor = nullptr);` (scope `UserGeneratedContentLocalization`) — Compile UGC localization (if present) for the given plugins, producing LocMeta and LocRes files for consumption by the engine. @param Plugins				The list of plugins to compile. @param DefaultDescriptor		An optional default UGC localization descriptor to validate any loaded UGC localization descriptors against prior to compiling the localization data.
- L281 _prototype_ `bool CompileLocalization(const FString& LocalizationTargetName, const FString& LocalizationTargetInputDirectory, const FString& LocalizationTargetOutputDirectory, const FUserGeneratedContentLocalizationDescriptor* DefaultDescriptor = nullptr);` (scope `UserGeneratedContentLocalization`) — Compile UGC localization (if present) for the given localization target, producing LocMeta and LocRes files for consumption by the engine. @param LocalizationTargetName			The target name being compiled (@see GetLocalizationTargetName). @param LocalizationTargetInputDirectory	The directory we'll read the source localization data from when compiling the plugin (@see GetLocalizationTargetDirectory). @param LocalizationTargetOutputDirectory	The directory we'll write the LocMeta and LocRes data to when compiling the plugin. @param DefaultDescriptor					An optional default UGC localization descriptor to validate any loaded UGC localization descriptors against prior to compiling the localization data.
- L292 _prototype_ `ELoadLocalizationResult LoadLocalization(const FString& LocalizationTargetName, const FString& LocalizationTargetDirectory, TSharedPtr<FLocTextHelper>& OutLocTextHelper, const FUserGeneratedContentLocalizationDescriptor* DefaultDescriptor = nullptr);` (scope `UserGeneratedContentLocalization`) — Load UGC localization source data for the given localization target. @note This is typically only needed for compilation (which does it internally), but can also be useful if you have other processes that need to read the source data. @param LocalizationTargetName		The target name being loaded (@see GetLocalizationTargetName). @param LocalizationTargetDirectory	The directory we'll read the source localization data from (@see GetLocalizationTargetDirectory). @param OutLocTextHelper				The LocTextHelper to fill with manifest/archive data, re-generated from the source data. @param DefaultDescriptor				An optional default UGC localization descriptor to validate any loaded UGC localization descriptors against prior to loading the localization data.
- L306 _prototype_ `bool MergeLocalization(const FString& SourceLocalizationTargetName, const FString& SourceLocalizationTargetDirectory, const FString& DestLocalizationTargetName, const FString& DestLocalizationTargetDirectory, const EMergeLocalizationMode MergeMode, const bool bOnlyIfSourceFileNewer, const bool bUseSourceControl = true);` (scope `UserGeneratedContentLocalization`) — Merge the PO file data of two UGC localization targets together, so that any PO entries with translations from source are present in dest. Whether the translation from source is actually applied to dest depends on the MergeMode. @note Dest does not have to currently exist prior to the merge. @param SourceLocalizationTargetName		The name of the source localization target (@see GetLocalizationTargetName). @param SourceLocalizationTargetDirectory	The directory of the source localization target (@see GetLocalizationTargetDirectory). @param DestLocalizationTargetName		The name of the dest localization target (@see GetLocalizationTargetName). @param DestLocalizationTargetDirectory	The directory of the dest localization target (@see GetLocalizationTargetDirectory). @param MergeMode							When should an existing translation from source be applied to dest? @param bOnlyIfSourceFileNewer			True if we should only merge from source -> dest if the source file is newer than the dest file. @param bUseSourceControl					Pass false as an optimization if you knew for certain that DestLocalizationTargetDirectory is outside of source control, otherwise pass true.
- L316 _prototype_ `void CleanupLocalization(TArrayView<const TSharedRef<IPlugin>> PluginsToClean, const FUserGeneratedContentLocalizationDescriptor& DefaultDescriptor, const bool bSilent = false);` (scope `UserGeneratedContentLocalization`) — Cleanup UGC localization that is no longer relevant based on the given descriptor. @param PluginsToClean		The list of plugins to cleanup. @param PluginsToRemove		The list of plugins to remove any localization data for, regardless of the UGC localization descriptor. @param DefaultDescriptor		The default UGC localization descriptor to filter existing UGC localization data against (things that don't pass the filter will be cleaned). @param bSilent				True to silently delete localization data that doesn't pass the filter, or false to confirm with the user (via a dialog).
- L317 _prototype_ `void CleanupLocalization(TArrayView<const TSharedRef<IPlugin>> PluginsToClean, TArrayView<const TSharedRef<IPlugin>> PluginsToRemove, const FUserGeneratedContentLocalizationDescriptor& DefaultDescriptor, const bool bSilent = false);` (scope `UserGeneratedContentLocalization`)
