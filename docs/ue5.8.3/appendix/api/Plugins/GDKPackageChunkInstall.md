# Plugins / GDKPackageChunkInstall

- module root: `Plugins/Runtime/Microsoft/GDKPackageChunkInstall/Source/GDKPackageChunkInstall`
- headers: 1; symbols: 90
- symbol kinds: class=2, function=11, macro=3, member=27, prototype=46, struct=1
- PrivateDependencyModuleNames: Core, GDKPackageManifest, GDKRuntime, GRDK

### `Plugins/Runtime/Microsoft/GDKPackageChunkInstall/Source/GDKPackageChunkInstall/Public/GDKPlatformChunkInstall.h` (Public)


#### class `FGDKPlatformChunkInstall`  
`class FGDKPlatformChunkInstall : public FGenericPlatformChunkInstall`  
_L38-167_
- inherits: `FGenericPlatformChunkInstall`
- desc: GDK implementation of FGenericPlatformChunkInstall with support for Recipes & Features
- L41 _public prototype_ `FGDKPlatformChunkInstall();`
- L42 _public prototype_ `virtual ~FGDKPlatformChunkInstall();`
- L46 _public prototype_ `virtual void AsyncInit( TFunction<void(bool )> OnInitComplete ) override;`
- L48 _public prototype_ `virtual bool IsAvailable() const override;`
- L49 _public prototype_ `virtual EChunkLocation::Type GetPakchunkLocation(int32 PakchunkIndex) override;`
- L50 _public function_ `virtual bool GetProgressReportingTypeSupported(EChunkProgressReportingType::Type ReportType) override`
- L51 _public prototype_ `virtual float GetChunkProgress( uint32 PakchunkIndex, EChunkProgressReportingType::Type ReportType ) override;`
- L52 _public function_ `virtual EChunkInstallSpeed::Type GetInstallSpeed() override`
- L53 _public function_ `virtual bool SetInstallSpeed( EChunkInstallSpeed::Type InstallSpeed ) override`
- L54 _public prototype_ `virtual bool PrioritizePakchunk(int32 PakchunkIndex, EChunkPriority::Type Priority) override;`
- L55 _public function_ `virtual bool DebugStartNextChunk()`
- L56 _public prototype_ `virtual void ExternalNotifyChunkAvailable(uint32 PakchunkIndex) override;`
- L58 _public function_ `virtual bool SupportsNamedChunkInstall() const override`
- L59 _public prototype_ `virtual bool IsNamedChunkInProgress(const FName NamedChunk) override;`
- L60 _public prototype_ `virtual bool InstallNamedChunks(const TArrayView<const FName>& NamedChunks) override;`
- L61 _public prototype_ `virtual bool UninstallNamedChunks(const TArrayView<const FName>& NamedChunks) override;`
- L62 _public prototype_ `virtual EChunkLocation::Type GetNamedChunkLocation(const FName NamedChunk) override;`
- L63 _public prototype_ `virtual float GetNamedChunkProgress(const FName NamedChunk, EChunkProgressReportingType::Type ReportType) override;`
- L64 _public prototype_ `virtual bool PrioritizeNamedChunk(const FName NamedChunk, EChunkPriority::Type Priority) override;`
- L65 _public prototype_ `virtual bool CancelNamedChunksInstall(const TArrayView<const FName>& NamedChunks) override;`
- L66 _public prototype_ `virtual ENamedChunkType GetNamedChunkType(const FName NamedChunk) const override;`
- L67 _public prototype_ `virtual TArray<FName> GetNamedChunksByType(ENamedChunkType NamedChunkType) const override;`
- L69 _public function_ `virtual bool SupportsBundleSource() const override`
- L71 _public prototype_ `virtual bool SetAutoPakMountingEnabled( bool bEnabled ) override;`
- L72 _public prototype_ `virtual bool GetPakFilesInNamedChunk( const FName NamedChunk, TArray<FString>& OutFilesInChunk) const override;`
- L73 _public prototype_ `virtual bool GetNamedChunkInstallationStatus( const FName NamedChunk, FChunkInstallationStatusDetail& OutChunkStatusDetail ) const override;`
- L74 _public prototype_ `virtual bool IsNamedChunkForCurrentLocale( const FName NamedChunk ) const override;`
- L77 _public prototype_ `static void DebugDumpChunkState();` — helper functions
- L81 _private member_ `std::atomic<bool> bIsInitialized = false;`
- L85 _private prototype_ `virtual bool PrioritizeChunk(uint32 UnrealChunkID, EChunkPriority::Type Priority) override;` — IPlatformChunkInstall implementation
- L86 _private prototype_ `virtual EChunkLocation::Type GetChunkLocation(uint32 UnrealChunkID) override;`
- L89 _private member_ `bool bAutoMountPaks = true;` — common chunk install functionality
- L90 _private prototype_ `bool MountPaks(uint32 UnrealChunkID);`
- L91 _private prototype_ `bool UnMountPaks(uint32 UnrealChunkID);`
- L94 _private member_ `bool bIsPackaged;` — package data
- L95 _private member_ `bool bPackageHasFeatures;`
- L96 _private member_ `char PackageIdentifier[XPACKAGE_IDENTIFIER_MAX_LENGTH];`
- L123 _private member_ `TArray<FName> OnDemandChunks;` — chunk data
- L124 _private member_ `TArray<FName> LanguageChunks;`
- L125 _private member_ `TMap<uint32,TUniquePtr<FChunkMonitor>> ChunkMonitors;`
- L126 _private member_ `TMap<FName,TUniquePtr<FChunkMonitor>> NamedChunkMonitors;`
- L127 _private member_ `TMultiMap<FName,int32> InitialNamedChunksMap;`
- L128 _private member_ `TSet<FName> SecondaryLanguageNamedChunks;`
- L129 _private member_ `TSet<FName> UnavailableChunks;`
- L130 _private member_ `FCriticalSection ChunkDataLock;`
- L134 _private prototype_ `bool CreateChunkDataFromPackageManifest();`
- L136 _private prototype_ `void CreateChunkDataForPackage(const XPackageDetails& Details);`
- L138 _private prototype_ `void OnNamedChunkInstallationChanged(const FName NamedChunk, bool bIsInstalled);`
- L139 _private prototype_ `void OnChunkInstallationChanged(uint32 UnrealChunkID, bool bIsInstalled);`
- L140 _private prototype_ `FChunkMonitor* FindChunkMonitor(uint32 UnrealChunkID);`
- L141 _private prototype_ `FChunkMonitor* FindChunkMonitor(const FName NamedChunk);`
- L142 _private function_ `const FChunkMonitor* FindChunkMonitor(uint32 UnrealChunkID) const`
- L143 _private function_ `const FChunkMonitor* FindChunkMonitor(const FName NamedChunk) const`
- L146 _private prototype_ `void AddToTicker();` — ticker & deferred operations
- L147 _private prototype_ `void RemoveFromTicker();`
- L148 _private prototype_ `bool Tick( float DeltaSeconds );`
- L149 _private member_ `FTSTicker::FDelegateHandle TickHandle;`
- L150 _private member_ `TSet<FName> PendingInstallChunks;`
- L151 _private member_ `TSet<FName> PendingUninstallChunks;`
- L152 _private member_ `TSet<FName> CurrentUninstallingChunks;`

#### struct `FGDKPlatformChunkInstall::FChunkMonitor`  
`struct FChunkMonitor`  
_L99-120_
- desc: cached information about a chunk
- L101 _public prototype_ `FChunkMonitor( FGDKPlatformChunkInstall& Owner, const XPackageChunkSelector& InSelector, XPackageChunkAvailability InInitialAvailability );`
- L102 _public prototype_ `~FChunkMonitor();`
- L104 _public prototype_ `FString GetDebugString() const;`
- L105 _public prototype_ `FString GetName() const;`
- L106 _public prototype_ `void OnProgressChange();`
- L108 _public prototype_ `bool SetPriority(EChunkPriority::Type Priority);`
- L109 _public prototype_ `float GetProgress(EChunkProgressReportingType::Type ReportType) const;`
- L110 _public prototype_ `EChunkLocation::Type GetLocation() const;`
- L112 _public member_ `bool bInstalled;`
- L113 _public member_ `bool bWasInProgress;`
- L114 _public member_ `uint8 CachedProgress;` — 0-100
- L115 _public member_ `TUniquePtr<char[]> SelectorTag;`
- L116 _public member_ `XPackageChunkSelector Selector;`
- L117 _public member_ `XPackageInstallationMonitorHandle InstallationMonitorHandle;`
- L118 _public member_ `XTaskQueueRegistrationToken InstallationProgressChangedToken;`
- L119 _public member_ `FGDKPlatformChunkInstall* Owner;`

#### class `FGDKPlatformChunkInstall::FGDKCustomChunkSelector`  
`class FGDKCustomChunkSelector`  
_L155-166_
- desc: helper class for creating an GDK XPackageChunkSelector array from an FName array
- L158 _public prototype_ `FGDKCustomChunkSelector( const TSet<FName>& NamedChunks, FGDKPlatformChunkInstall* Owner );`
- L159 _public function_ `inline const FString& ToString() const`
- L160 _public function_ `inline const uint32 Num() const`
- L161 _public function_ `inline XPackageChunkSelector* Get()`
- L164 _private member_ `FString StringTagList;` — comma-separated list of tags, for logging only
- L165 _private member_ `TArray<XPackageChunkSelector> ChunkSelectors;` — chunk selectors for the chunk tag ids

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API GDKPACKAGECHUNKINSTALL_API`
- L24 _macro_ `#define WITH_CHUNKINSTALL_ASYNC_INIT 0`
- L32 _macro_ `#define USE_GDK_PACKAGE_MANIFEST_INIT 0`
- L170 _prototype_ `FString LexToString(const XPackageChunkSelector& ChunkSelector);`
- L171 _prototype_ `FString LexToString(XPackageChunkAvailability Availability);`
