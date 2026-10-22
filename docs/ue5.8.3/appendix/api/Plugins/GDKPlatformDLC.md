# Plugins / GDKPlatformDLC

- module root: `Plugins/Experimental/Microsoft/GDKPlatformDLC/Source/GDKPlatformDLC`
- headers: 2; symbols: 132
- symbol kinds: class=2, enum=4, enumerator=23, function=1, member=47, prototype=53, struct=2
- PublicIncludePathModuleNames: GDKRuntime

### `Plugins/Experimental/Microsoft/GDKPlatformDLC/Source/GDKPlatformDLC/Private/GDKPlatformDLC.h` (Private)


#### class `FGDKPlatformDLC`  
`class FGDKPlatformDLC : public FGenericPlatformDLC`  
_L24-210_
- inherits: `FGenericPlatformDLC`
- L27 _public prototype_ `FGDKPlatformDLC();`
- L28 _public prototype_ `virtual ~FGDKPlatformDLC();`
- L31 _public prototype_ `virtual void Shutdown() override;` — IPlatformDLC implementation
- L33 _public prototype_ `virtual bool HasEntitlement( FName DLCName ) const override;`
- L34 _public prototype_ `virtual EState GetState( FName DLCName ) const override;`
- L36 _public prototype_ `virtual bool Mount( FName DLCName ) override;`
- L37 _public prototype_ `virtual bool Unmount( FName DLCName ) override;`
- L38 _public prototype_ `virtual bool Download( FName DLCName ) override;`
- L39 _public prototype_ `virtual bool Uninstall( FName DLCName ) override;`
- L41 _public prototype_ `virtual bool GetDownloadSize( FName DLCName, uint64& OutCurrentInstallSize, uint64& OutFullInstallSize ) const override;`
- L42 _public prototype_ `virtual FString GetRootDirectory( FName DLCName ) const override;`
- L43 _public prototype_ `virtual TArray<FName> GetAllDLCNames() const override;`
- L44 _public prototype_ `virtual TArray<FName> GetMountedDLCNames() const override;`
- L45 _public prototype_ `virtual FString GetStoreId( FName DLCName ) const override;`
- L47 _public prototype_ `virtual void SetStoreUser( FPlatformUserId PlatformUserId ) override;`
- L48 _public prototype_ `virtual FPlatformUserId GetStoreUser() const override;`
- L52 _public prototype_ `FString Debug_GetStateDescription() const;`
- L53 _public prototype_ `bool Debug_GetPackageDescription( int PackageIndex, FString& OutDescription, FColor& OutColor ) const;`
- L57 _private prototype_ `void SetStoreUserHandle(const FGDKUserHandle& NewStoreUser);`
- L122 _private member_ `TArray<TSharedPtr<FPackageData>> AllPackages;`
- L123 _private member_ `TArray<const char*> AllStoreIds;` — points to StoreId in AllPackages
- L124 _private member_ `TMap<FName, FString> DLCNameToStoreIdMap;`
- L125 _private member_ `TMap<FName, FString> DLCNameToPluginNameMap;`
- L126 _private member_ `mutable FCriticalSection PackageDataLock;`
- L127 _private member_ `TFuture<void> InitFuture;`
- L128 _private member_ `XTaskQueueRegistrationToken PackageInstalledToken;`
- L129 _private member_ `FDelegateHandle UserLoginChangedDelegateHandle;`
- L131 _private prototype_ `void AsyncInitDLC(const XPackageDetails& Details, bool bMount, bool bNotify);`
- L132 _private prototype_ `TSharedPtr<FPackageData> FindDLC( FName DLCName );`
- L133 _private prototype_ `TSharedPtr<const FPackageData> FindDLC( FName DLCName ) const;`
- L134 _private prototype_ `TSharedPtr<FPackageData> FindDLCByStoreId( const char* StoreId );`
- L156 _private member_ `std::atomic<EProcessingState> ProcessingState = EProcessingState::Idle;`
- L157 _private member_ `bool bPendingProductsRequery = false;`
- L158 _private member_ `TArray<TSharedPtr<FPackageData>> PendingPackages;`
- L159 _private member_ `TArray<TSharedPtr<FPackageData>> LostLicensePackages;`
- L160 _private member_ `TSharedPtr<FPackageData> CurrentProcessingPackage;`
- L161 _private member_ `FGDKAsyncTaskMonitor CurrentProcessingAsyncTask;`
- L163 _private prototype_ `virtual void BeginInitializeInternal() override;`
- L165 _private prototype_ `bool AddToPendingPackages( TSharedPtr<FPackageData> Package );`
- L166 _private prototype_ `void AsyncQueryingProducts_GameThread();`
- L167 _private prototype_ `void BeginProcessingPackage_GameThread( TSharedPtr<FPackageData> Package );`
- L169 _private prototype_ `void Purchase_AsyncShowPurchaseUI_GameThread( TSharedPtr<FPackageData> Package );`
- L170 _private prototype_ `void Purchase_AsyncQueryingProduct_GameThread( TSharedPtr<FPackageData> Package );`
- L171 _private prototype_ `void Purchase_Completed_GameThread( TSharedPtr<FPackageData> Package );`
- L173 _private prototype_ `void Mount_AsyncAcquireLicense_GameThread( TSharedPtr<FPackageData> Package );`
- L174 _private prototype_ `void Mount_AsyncMountPackage_GameThread( TSharedPtr<FPackageData> Package );`
- L175 _private prototype_ `void Mount_CachePackageData_BackgroundThread( TSharedPtr<FPackageData> Package );`
- L176 _private prototype_ `void Mount_MountPlugin_GameThread( TSharedPtr<FPackageData> Package );`
- L177 _private prototype_ `void Mount_Completed_GameThread( TSharedPtr<FPackageData> Package );`
- L178 _private prototype_ `void LicenseLost_GameThread( TSharedPtr<FPackageData> Package );`
- L180 _private prototype_ `bool AsyncDownloadPackage( TSharedPtr<FPackageData> Package );`
- L183 _private member_ `XStoreContextHandle CurrentStoreContext;` — store
- L184 _private member_ `FGDKUserHandle CurrentStoreUser;`
- L185 _private member_ `FPlatformUserId CurrentStoreUserId;`
- L186 _private prototype_ `bool EnsureValidStoreContext();`
- L187 _private prototype_ `bool ProcessQueryProductsResult(XAsyncBlock* Block);`
- L188 _private prototype_ `static void OnPackageLicenseLost(void* Context);`
- L189 _private prototype_ `static void OnInstallationProgressChanged(void* Context, XPackageInstallationMonitorHandle Monitor);`
- L190 _private prototype_ `void OnUserLoginChanged(bool bSignedIn, int32 ChangedUserIndex, int32 ControllerId);`
- L193 _private member_ `bool bAutoMountDLC = true;` — configuration
- L194 _private member_ `bool bAutoMountExistingDLC = true;` — Whether to automatically mount any already-downloaded DLC on system startup.
- L195 _private member_ `bool bAutoMountPakFiles = true;` — Whether to automatically mount pak files
- L196 _private member_ `bool bAutoMountPlugin = true;` — Whether to automatically mount the DLC plugin and asset registry etc. (requires bAutoMountPakFiles)
- L197 _private member_ `bool bAutoMountAgeRestricted = false;` — Whether to attempt to mount age-restricted DLC. This will trigger a parental controls consent prompt.
- L200 _private member_ `FTSTicker::FDelegateHandle TickHandle;` — ticker
- L201 _private prototype_ `void AddToTicker();`
- L202 _private prototype_ `void RemoveFromTicker();`
- L203 _private prototype_ `bool Tick( float DeltaSeconds );`

#### enum `FGDKPlatformDLC::EMountState`  
`enum class EMountState : uint8`  
_L60-66_
- L62 _public enumerator_ `NotMounted`
- L63 _public enumerator_ `Mounted`
- L64 _public enumerator_ `Unmounted`
- L65 _public enumerator_ `Ignored_AgeRestricted`

#### enum `FGDKPlatformDLC::ELicenseState`  
`enum class ELicenseState : uint8`  
_L67-72_
- L69 _public enumerator_ `Unlicensed`
- L70 _public enumerator_ `Licensed`
- L71 _public enumerator_ `LicenseLost`

#### enum `FGDKPlatformDLC::EDownloadState`  
`enum class EDownloadState : uint8`  
_L73-78_
- L75 _public enumerator_ `NotDownloaded`
- L76 _public enumerator_ `Downloading`
- L77 _public enumerator_ `Downloaded`

#### struct `FGDKPlatformDLC::FPackageData`  
`struct FPackageData`  
_L80-121_
- L82 _public prototype_ `FPackageData(FGDKPlatformDLC* InOwner, const FName& InDLCName, const FString& InStoreId);`
- L83 _public prototype_ `~FPackageData();`
- L85 _public prototype_ `void OnDownloading(const char* InPackageIdentifier);`
- L86 _public prototype_ `void OnDownloaded(const XPackageDetails& InDetails);`
- L87 _public prototype_ `void OnUninstalled();`
- L89 _public prototype_ `void CreateInstallationMonitor(const char* Identifier);`
- L90 _public prototype_ `void DestroyInstallationMonitor();`
- L92 _public member_ `char PackageIdentifier[XPACKAGE_IDENTIFIER_MAX_LENGTH] = {};`
- L93 _public member_ `char StoreId[STORE_SKU_ID_SIZE] = {};`
- L94 _public member_ `std::atomic<EMountState> MountState = EMountState::NotMounted;`
- L95 _public member_ `std::atomic<ELicenseState> LicenseState = ELicenseState::Unlicensed;`
- L96 _public member_ `std::atomic<EDownloadState> DownloadState = EDownloadState::NotDownloaded;`
- L97 _public member_ `FString PackageName;`
- L98 _public member_ `FString MountPath;`
- L99 _public member_ `FGDKPlatformDLC* Owner = nullptr;`
- L100 _public member_ `bool bAllowPurchasePrompt = false;`
- L101 _public member_ `std::atomic<bool> bIsPurchased = false;`
- L102 _public member_ `bool bIsAgeRestricted = false;`
- L103 _public member_ `FName DLCName;`
- L104 _public member_ `XPackageMountHandle DLCHandle = nullptr;`
- L105 _public member_ `XStoreLicenseHandle DLCLicense = nullptr;`
- L106 _public member_ `XTaskQueueRegistrationToken PackageLicenseLostToken = {};`
- L107 _public member_ `TSharedPtr<class IPlugin> DLCPlugin;`
- L108 _public member_ `FString DLCPluginFilePath;`
- L109 _public member_ `FGDKAsyncTaskMonitor DownloadAsyncTask;`
- L110 _public member_ `XPackageInstallationMonitorHandle InstallationMonitorHandle = nullptr;`
- L111 _public member_ `XTaskQueueRegistrationToken InstallationProgressToken = {};`
- L112 _public member_ `std::atomic<uint64> CachedInstalledBytes = 0;`
- L113 _public member_ `std::atomic<uint64> CachedTotalBytes = 0;`
- L120 _public member_ `FContext Context;`

#### struct `FGDKPlatformDLC::FPackageData::FContext`  
`struct FContext`  
_L116-119_
- desc: context used for GDK callbacks that only accept void*
- L118 _public member_ `TWeakPtr<FPackageData> Package;`

#### enum `FGDKPlatformDLC::EProcessingState`  
`enum class EProcessingState : uint8`  
_L137-155_
- desc: DLC processing
- L139 _public enumerator_ `Initializing`
- L140 _public enumerator_ `Idle`
- L141 _public enumerator_ `QueryingProducts`
- L143 _public enumerator_ `Purchase_ShowingPurchaseUI`
- L144 _public enumerator_ `Purchase_QueryingProduct`
- L145 _public enumerator_ `Purchase_DownloadRequested`
- L146 _public enumerator_ `Purchase_Completed`
- L148 _public enumerator_ `Mount_AcquiringLicense`
- L149 _public enumerator_ `Mount_MountingPackage`
- L150 _public enumerator_ `Mount_CachingData`
- L151 _public enumerator_ `Mount_MountingPlugin`
- L152 _public enumerator_ `Mount_Completed`
- L154 _public enumerator_ `Destroying`

### `Plugins/Experimental/Microsoft/GDKPlatformDLC/Source/GDKPlatformDLC/Public/GDKPlatformDLCModule.h` (Public)


#### class `IGDKPlatformDLCModule`  
`class IGDKPlatformDLCModule : public IPlatformDLCFactoryModule`  
_L10-24_
- inherits: `IPlatformDLCFactoryModule`
- L17 _public function_ `static inline IGDKPlatformDLCModule& Get()` — Singleton-like access to the MS Gaming Runtime module instance @return Returns IGDKPlatformDLCModule singleton instance, loading the module on demand if needed
- L23 _public prototype_ `virtual TSharedPtr<IPlatformDLC> GetPlatformDLC() = 0;` — get the platform DLC for this factory
