# Plugins / GooglePAD

- module root: `Plugins/Runtime/GooglePAD/Source/GooglePAD`
- headers: 2; symbols: 88
- symbol kinds: class=2, enum=5, enumerator=43, macro=1, member=6, prototype=31
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: Core
- PublicIncludePathModuleNames: Launch

### `Plugins/Runtime/GooglePAD/Source/GooglePAD/Classes/GooglePADFunctionLibrary.h` (Public)


#### enum `EGooglePADErrorCode`  
`enum class EGooglePADErrorCode : uint8`  
_L17-70_
- reflection: `UENUM(BlueprintType)`
- desc: An error code associated with Asset Pack operations.
- L20 _public enumerator_ `AssetPack_NO_ERROR = 0` — There was no error with the request.
- L23 _public enumerator_ `AssetPack_APP_UNAVAILABLE` — The requesting app is unavailable.
- L26 _public enumerator_ `AssetPack_UNAVAILABLE` — The requested Asset Pack isn't available for this app version.
- L29 _public enumerator_ `AssetPack_INVALID_REQUEST` — The request is invalid.
- L32 _public enumerator_ `AssetPack_DOWNLOAD_NOT_FOUND` — The requested download isn't found.
- L35 _public enumerator_ `AssetPack_API_NOT_AVAILABLE` — The Asset Pack API is unavailable.
- L38 _public enumerator_ `AssetPack_NETWORK_ERROR` — Network error. Unable to obtain Asset Pack details.
- L42 _public enumerator_ `AssetPack_ACCESS_DENIED` — Download not permitted under current device circumstances, e.g. app in background or device not signed into a Google account.
- L45 _public enumerator_ `AssetPack_INSUFFICIENT_STORAGE` — Asset Packs download failed due to insufficient storage.
- L48 _public enumerator_ `AssetPack_PLAY_STORE_NOT_FOUND` — The Play Store app is either not installed or not the official version.
- L51 _public enumerator_ `AssetPack_NETWORK_UNRESTRICTED` — Returned if showCellularDataConfirmation is called but no Asset Packs are waiting for Wi-Fi.
- L54 _public enumerator_ `AssetPack_INTERNAL_ERROR` — Unknown error downloading Asset Pack.
- L57 _public enumerator_ `AssetPack_INITIALIZATION_NEEDED` — The requested operation failed: need to call AssetPackManager_init() first.
- L60 _public enumerator_ `AssetPack_INITIALIZATION_FAILED` — There was an error initializing the Asset Pack API.
- L63 _public enumerator_ `AssetPack_APP_NOT_OWNED` — The app isn't owned by any user on this device. An app is "owned" if it has been acquired from the Play Store.
- L66 _public enumerator_ `AssetPack_CONFIRMATION_NOT_REQUIRED` — Returned if showConfirmationDialog is called but no asset packs are waiting for user confirmation.
- L69 _public enumerator_ `AssetPack_UNRECOGNIZED_INSTALLATION` — Returned if the app was not installed by Play.

#### enum `EGooglePADDownloadStatus`  
`enum class EGooglePADDownloadStatus : uint8`  
_L74-117_
- reflection: `UENUM(BlueprintType)`
- desc: The status associated with Asset Pack download operations.
- L77 _public enumerator_ `AssetPack_UNKNOWN = 0` — Nothing is known about the Asset Pack.
- L80 _public enumerator_ `AssetPack_DOWNLOAD_PENDING` — An AssetPackManager_requestDownload() async request is pending.
- L83 _public enumerator_ `AssetPack_DOWNLOADING` — The Asset Pack download is in progress.
- L86 _public enumerator_ `AssetPack_TRANSFERRING` — The Asset Pack is being transferred to the app.
- L89 _public enumerator_ `AssetPack_DOWNLOAD_COMPLETED` — Download and transfer are complete; the assets are available to the app.
- L92 _public enumerator_ `AssetPack_DOWNLOAD_FAILED` — An AssetPackManager_requestDownload() has failed.
- L95 _public enumerator_ `AssetPack_DOWNLOAD_CANCELED` — Asset Pack download has been canceled.
- L98 _public enumerator_ `AssetPack_WAITING_FOR_WIFI` — The Asset Pack download is waiting for Wi-Fi to proceed.
- L101 _public enumerator_ `AssetPack_NOT_INSTALLED` — The Asset Pack isn't installed.
- L104 _public enumerator_ `AssetPack_INFO_PENDING` — An AssetPackManager_requestInfo() async request started, but the result isn't known yet.
- L107 _public enumerator_ `AssetPack_INFO_FAILED` — An AssetPackManager_requestInfo() async request has failed.
- L110 _public enumerator_ `AssetPack_REMOVAL_PENDING` — An AssetPackManager_requestRemoval() async request started.
- L113 _public enumerator_ `AssetPack_REMOVAL_FAILED` — An AssetPackManager_requestRemoval() async request has failed.
- L116 _public enumerator_ `AssetPack_REQUIRES_USER_CONFIRMATION` — The Asset Pack download is waiting for user confirmation to proceed.

#### enum `EGooglePADStorageMethod`  
`enum class EGooglePADStorageMethod : uint8`  
_L121-134_
- reflection: `UENUM(BlueprintType)`
- desc: The method used to store an Asset Pack on the device.
- L124 _public enumerator_ `AssetPack_STORAGE_FILES = 0` — The Asset Pack is unpacked into a folder containing individual asset files. Assets can be accessed via standard File APIs.
- L127 _public enumerator_ `AssetPack_STORAGE_APK` — The Asset Pack is installed as an APK containing packed asset files. Assets can be accessed via AAssetManager.
- L130 _public enumerator_ `AssetPack_STORAGE_UNKNOWN` — Nothing is known, perhaps due to an error.
- L133 _public enumerator_ `AssetPack_STORAGE_NOT_INSTALLED` — The Asset Pack is not installed.

#### enum `EGooglePADCellularDataConfirmStatus`  
`enum class EGooglePADCellularDataConfirmStatus : uint8`  
_L138-151_
- reflection: `UENUM(BlueprintType)`
- desc: The status associated with a request to display a cellular data confirmation dialog.
- L141 _public enumerator_ `AssetPack_CONFIRM_UNKNOWN = 0` — AssetPackManager_showCellularDataConfirmation() has not been called.
- L144 _public enumerator_ `AssetPack_CONFIRM_PENDING` — AssetPackManager_showCellularDataConfirmation() has been called, but the user hasn't made a choice.
- L147 _public enumerator_ `AssetPack_CONFIRM_USER_APPROVED` — The user approved of downloading Asset Packs over cellular data.
- L150 _public enumerator_ `AssetPack_CONFIRM_USER_CANCELED` — The user declined to download Asset Packs over cellular data.

#### enum `EGooglePADConfirmationDialogStatus`  
`enum class EGooglePADConfirmationDialogStatus : uint8`  
_L155-168_
- reflection: `UENUM(BlueprintType)`
- desc: The status associated with a request to display a confirmation dialog.
- L158 _public enumerator_ `AssetPack_CONFIRMATION_DIALOG_UNKNOWN = 0` — AssetPackManager_showConfirmationDialog() has not been called.
- L161 _public enumerator_ `AssetPack_CONFIRMATION_DIALOG_PENDING` — AssetPackManager_showConfirmationDialog() has been called, but the user hasn't made a choice.
- L164 _public enumerator_ `AssetPack_CONFIRMATION_DIALOG_APPROVED` — The user approved of downloading asset packs.
- L167 _public enumerator_ `AssetPack_CONFIRMATION_DIALOG_CANCELED` — The user declined to download asset packs.

#### class `UGooglePADFunctionLibrary`  
`class UGooglePADFunctionLibrary : public UBlueprintFunctionLibrary`  
_L171-285_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L177 _public prototype_ `static EGooglePADErrorCode RequestInfo(const TArray<FString> AssetPacks);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Request Info"), Category = "GooglePAD")` — Request information about a set of asset packs
- L181 _public prototype_ `static EGooglePADErrorCode RequestDownload(const TArray<FString> AssetPacks);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Request Download"), Category = "GooglePAD")` — Request download of a set of asset packs
- L185 _public prototype_ `static EGooglePADErrorCode CancelDownload(const TArray<FString> AssetPacks);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Cancel Download"), Category = "GooglePAD")` — Cancel download of a set of asset packs
- L189 _public prototype_ `static EGooglePADErrorCode GetDownloadState(const FString& Name, int32& State);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Download State"), Category = "GooglePAD")` — Get download state handle of an asset pack (release when done)
- L193 _public prototype_ `static void ReleaseDownloadState(const int32 State);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Release Download State"), Category = "GooglePAD")` — Release download state resources
- L197 _public prototype_ `static EGooglePADDownloadStatus GetDownloadStatus(const int32 State);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Download Status"), Category = "GooglePAD")` — Get download status from a download state
- L201 _public prototype_ `static int32 GetBytesDownloaded(const int32 State);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Bytes Downloaded"), Category = "GooglePAD")` — Get the number of bytes downloaded from a download state
- L205 _public prototype_ `static int32 GetTotalBytesToDownload(const int32 State);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Total Bytes To Download"), Category = "GooglePAD")` — Get the total number of bytes to download from a download state
- L209 _public prototype_ `static EGooglePADErrorCode RequestRemoval(const FString& Name);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Request Removal"), Category = "GooglePAD")` — Request removal of an asset pack
- L213 _public prototype_ `static EGooglePADErrorCode ShowCellularDataConfirmation();` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Show Cellular Data Confirmation"), Category = "GooglePAD")` — Show confirmation dialog requesting data download over cellular network (DEPRECIATED)
- L217 _public prototype_ `static EGooglePADErrorCode GetShowCellularDataConfirmationStatus(EGooglePADCellularDataConfirmStatus& Status);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Cellular Data Confirmation Status"), Category = "GooglePAD")` — Get status of cellular confirmation dialog (DEPRECIATED)
- L221 _public prototype_ `static EGooglePADErrorCode ShowConfirmationDialog();` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Show Confirmation dialog"), Category = "GooglePAD")` — Show confirmation dialog to start all asset pack downloads in either REQUIRES_USER_CONFIRMATION or WAITING_FOR_WIFI state.
- L225 _public prototype_ `static EGooglePADErrorCode GetShowConfirmationDialogStatus(EGooglePADConfirmationDialogStatus& Status);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Cellular Data Confirmation Status"), Category = "GooglePAD")` — Gets the status of confirmation dialog requests
- L229 _public prototype_ `static EGooglePADErrorCode GetAssetPackLocation(const FString& Name, int32& Location);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get AssetPack Location"), Category = "GooglePAD")` — Get location handle of requested asset pack (release when done)
- L233 _public prototype_ `static void ReleaseAssetPackLocation(const int32 Location);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Release AssetPack Location"), Category = "GooglePAD")` — Release location resources
- L237 _public prototype_ `static EGooglePADStorageMethod GetStorageMethod(const int32 Location);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Storage Method"), Category = "GooglePAD")` — Get storage method from location
- L241 _public prototype_ `static FString GetAssetsPath(const int32 Location);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Assets Path"), Category = "GooglePAD")` — Get asset path from from location
- L245 _public prototype_ `static void Initialize();` — initialize java objects and cache them for further usage. called when the module is loaded
- L248 _public prototype_ `static void Shutdown();` — releases resources. called when the module is shut down
- L253 _private prototype_ `static EGooglePADErrorCode ConvertErrorCode(AssetPackErrorCode Code);` — Conversion functions between enum types
- L254 _private prototype_ `static EGooglePADDownloadStatus ConvertDownloadStatus(AssetPackDownloadStatus Status);`
- L255 _private prototype_ `static EGooglePADCellularDataConfirmStatus ConvertCellarDataConfirmStatus(ShowCellularDataConfirmationStatus Status);`
- L256 _private prototype_ `static EGooglePADConfirmationDialogStatus ConvertConfirmationDialogStatus(ShowConfirmationDialogStatus Status);`
- L257 _private prototype_ `static EGooglePADStorageMethod ConvertStorageMethod(AssetPackStorageMethod Code);`
- L261 _private prototype_ `static char **ConvertAssetPackNames(TArray<FString> AssetPacks);` — Helper functions for dealing with asset name arrays
- L262 _private prototype_ `static void ReleaseAssetPackNames(const char **AssetPackNames, int32 NumAssetPacks);`
- L266 _private prototype_ `static void HandleApplicationHasEnteredForeground();` — Callback for when the application resumed in the foreground.
- L269 _private prototype_ `static void HandleApplicationWillEnterBackground();` — Callback for when the application is being paused in the background.
- L273 _private member_ `static FDelegateHandle PauseHandle;` — Foreground/background delegate for pause.
- L276 _private member_ `static FDelegateHandle ResumeHandle;` — Foreground/background delegate for resume.
- L279 _private member_ `static TMap<int32, void*> DownloadStateMap;` — Handles for DownloadState
- L280 _private member_ `static int32 DownloadStateMapIndex;`
- L283 _private member_ `static TMap<int32, void*> LocationMap;` — Handles for AssetPackLocation
- L284 _private member_ `static int32 LocationMapIndex;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define SUPPORTED_PLATFORM (PLATFORM_ANDROID && USE_ANDROID_JNI)`

### `Plugins/Runtime/GooglePAD/Source/GooglePAD/Public/GooglePAD.h` (Public)


#### class `FGooglePADModule`  
`class FGooglePADModule : public IModuleInterface`  
_L9-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGooglePAD, Log, All);`
