# Plugins / MobilePatchingUtils

- module root: `Plugins/Runtime/MobilePatchingUtils/Source/MobilePatchingUtils`
- headers: 1; symbols: 42
- symbol kinds: class=3, delegate=4, enum=1, enumerator=7, macro=1, member=6, prototype=20
- PrivateDependencyModuleNames: BuildPatchServices, HTTP, PakFile
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Runtime/MobilePatchingUtils/Source/MobilePatchingUtils/Private/MobilePatchingLibrary.h` (Private)


#### class `UMobileInstalledContent`  
`class UMobileInstalledContent : public UObject`  
_L16-42_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject`
- L23 _public prototype_ `float GetDiskFreeSpace();` — `UFUNCTION(BlueprintPure, Category="Mobile Patching")` — Get the disk free space in megabytes where content is installed
- L27 _public prototype_ `float GetInstalledContentSize();` — `UFUNCTION(BlueprintPure, Category="Mobile Patching")` — Get the installed content size in megabytes
- L35 _public prototype_ `bool Mount(int32 PakOrder, const FString& MountPoint);` — `UFUNCTION(BlueprintCallable, Category="Mobile Patching", meta=(AdvancedDisplay="PakOrder,MountPoint", PakOrder="1"))` — Mount installed content @param	PakOrder : Content pak priority @param	MountPoint : Path to mount the pak at
- L39 _public member_ `FString InstallDir;` — User specified directory where content should be/already installed
- L41 _public member_ `IBuildManifestPtr InstalledManifest;` — Currently installed manifest

#### class `UMobilePendingContent`  
`class UMobilePendingContent : public UMobileInstalledContent`  
_L45-97_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UMobileInstalledContent`
- L52 _public prototype_ `float GetDownloadSize();` — `UFUNCTION(BlueprintPure, Category="Mobile Patching")` — Get the total download size for this content installation
- L56 _public prototype_ `float GetRequiredDiskSpace();` — `UFUNCTION(BlueprintPure, Category="Mobile Patching")` — Get the required disk space in megabytes for this content installation
- L60 _public prototype_ `float GetTotalDownloadedSize();` — `UFUNCTION(BlueprintPure, Category="Mobile Patching|Progress")` — Get the total downloaded size in megabytes. Valid during installation
- L64 _public prototype_ `float GetDownloadSpeed();` — `UFUNCTION(BlueprintPure, Category="Mobile Patching|Progress")` — Get the current download speed in megabytes per second. Valid during installation
- L69 _public prototype_ `FText GetDownloadStatusText();` — `UE_DEPRECATED(4.21, "GetDownloadStatusText has been deprecated. It will no longer be supported in the future.")` — `UFUNCTION(BlueprintPure, Category="Mobile Patching|Progress")` — DEPRECATED. GetDownloadStatusText has been deprecated. It will no longer be supported in the future
- L73 _public prototype_ `float GetInstallProgress();` — `UFUNCTION(BlueprintPure, Category="Mobile Patching|Progress")` — Get the current installation progress. Between 0 and 1 for known progress, or less than 0 for unknown progress
- L82 _public prototype_ `void StartInstall(FOnContentInstallSucceeded OnSucceeded, FOnContentInstallFailed OnFailed);` — `UFUNCTION(BlueprintCallable, Category="Mobile Patching")` — Attempt to download and install remote content. User can choose to mount installed content into the game. @param	OnSucceeded: Callback on installation success. @param	OnFailed: Callback on installation fail. Will return error message text and error integer code
- L85 _public prototype_ `virtual void BeginDestroy() override;`
- L90 _public member_ `FString RemoteManifestURL;` — User specified URL from where manifest can be downloaded
- L92 _public member_ `FString CloudURL;` — User specified cloud URL from where content chunks can be downloaded
- L94 _public member_ `IBuildInstallerPtr Installer;` — Content installer, only valid during installation
- L96 _public member_ `IBuildManifestPtr RemoteManifest;` — Manifest downloaded from a cloud

#### enum `ERequestContentError`  
`enum class ERequestContentError`  
_L99-108_
- L101 _public enumerator_ `NoError`
- L102 _public enumerator_ `InvalidInstallationDirectory`
- L103 _public enumerator_ `InvalidCloudURL`
- L104 _public enumerator_ `InvalidManifestURL`
- L105 _public enumerator_ `FailedToDownloadManifestNoResponse`
- L106 _public enumerator_ `FailedToDownloadManifest`
- L107 _public enumerator_ `FailedToReadManifest`

#### class `UMobilePatchingLibrary`  
`class UMobilePatchingLibrary : public UBlueprintFunctionLibrary`  
_L114-150_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L124 _public prototype_ `static UMobileInstalledContent* GetInstalledContent(const FString& InstallDirectory);` — `UFUNCTION(BlueprintPure, Category="Mobile Patching")` — Get the installed content. Will return non-null object if there is an installed content at specified directory User can choose to mount installed content into the game
- L137 _public prototype_ `static void RequestContent(const FString& RemoteManifestURL, const FString& CloudURL, const FString& InstallDirectory, FOnRequestContentSucceeded OnSucceeded, FOnRequestContentFailed OnFailed);` — `UFUNCTION(BlueprintCallable, Category="Mobile Patching")` — Attempt to download manifest file using specified manifest URL. On success it will return an object that represents remote content. This object can be queried for additional information, like total content size, download size, etc. User can choose to download and install remote content. @param	RemoteManifestURL : URL from where manifest file can be downloaded. (http://my-server.com/awesomecontent.manifest) @param	CloudURL :  URL from where content chunk data can be downloaded. (http://my-server.com/awesomecontent/clouddir) @param	InstallDirectory: Relative directory to where downloaded content should be installed (MyContent/AwesomeContent) @param	OnSucceeded: Callback on manifest download success. Will return object that represents remote content @param	OnFailed: Callback on manifest download fail. Will return error message text and error integer code
- L141 _public prototype_ `static bool HasActiveWiFiConnection();` — `UFUNCTION(BlueprintPure, Category="Mobile Patching")` — Whether WiFi connection is currently available
- L145 _public prototype_ `static FString GetActiveDeviceProfileName();` — `UFUNCTION(BlueprintPure, Category="Mobile Patching")` — Get the name of currently selected device profile name
- L149 _public prototype_ `static TArray<FString> GetSupportedPlatformNames();` — `UFUNCTION(BlueprintPure, Category="Mobile Patching")` — Get the list of supported platform names on this device. Example: Android_ETC2, Android_ASTC

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOBILEPATCHINGUTILS_API`
- L12 _delegate_ `DECLARE_DYNAMIC_DELEGATE(FOnContentInstallSucceeded);`
- L12 _prototype_ `DECLARE_DYNAMIC_DELEGATE(FOnContentInstallSucceeded);`
- L13 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnContentInstallFailed, FText, ErrorText, int32, ErrorCode);`
- L13 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnContentInstallFailed, FText, ErrorText, int32, ErrorCode);`
- L110 _delegate_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnRequestContentSucceeded, UMobilePendingContent*, MobilePendingContent);`
- L110 _prototype_ `DECLARE_DYNAMIC_DELEGATE_OneParam(FOnRequestContentSucceeded, UMobilePendingContent*, MobilePendingContent);`
- L111 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnRequestContentFailed, FText, ErrorText, int32, ErrorCode);`
- L111 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnRequestContentFailed, FText, ErrorText, int32, ErrorCode);`
