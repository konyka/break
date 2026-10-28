# Runtime / PortalMessages

- module root: `Source/Runtime/Portal/Messages`
- headers: 4; symbols: 50
- symbol kinds: function=22, member=16, struct=12
- PublicDependencyModuleNames: Core, CoreUObject, MessagingRpc, PortalServices

### `Source/Runtime/Portal/Messages/Public/PortalApplicationWindowMessages.h` (Public)


#### struct `FPortalApplicationWindowNavigateToRequest`  
`struct FPortalApplicationWindowNavigateToRequest : public FRpcMessage`  
_L10-22_
- reflection: `USTRUCT()`
- inherits: `FRpcMessage`
- L16 _public member_ `FString Url;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L18 _public function_ `FPortalApplicationWindowNavigateToRequest()`
- L19 _public function_ `FPortalApplicationWindowNavigateToRequest(const FString& InUrl) : Url(InUrl)`

#### struct `FPortalApplicationWindowNavigateToResponse`  
`struct FPortalApplicationWindowNavigateToResponse : public FRpcMessage`  
_L26-38_
- reflection: `USTRUCT()`
- inherits: `FRpcMessage`
- L32 _public member_ `bool Result = false;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L34 _public function_ `FPortalApplicationWindowNavigateToResponse()`
- L35 _public function_ `FPortalApplicationWindowNavigateToResponse(bool InResult) : Result(InResult)`

### `Source/Runtime/Portal/Messages/Public/PortalPackageInstallerMessages.h` (Public)


#### struct `FPortalPackageInstallerInstallRequest`  
`struct FPortalPackageInstallerInstallRequest : public FRpcMessage`  
_L13-33_
- reflection: `USTRUCT()`
- inherits: `FRpcMessage`
- L19 _public member_ `FString AppName;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L22 _public member_ `FString BuildLabel;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L25 _public member_ `FString DestinationPath;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L27 _public function_ `FPortalPackageInstallerInstallRequest()`
- L28 _public function_ `FPortalPackageInstallerInstallRequest(const FString& InAppName, const FString& InBuildLabel, const FString& InDestinationPath) : AppName(InAppName) , BuildLabel(InBuildLabel) , DestinationPath(InDestinationPath)`

#### struct `FPortalPackageInstallerInstallResponse`  
`struct FPortalPackageInstallerInstallResponse : public FRpcMessage`  
_L37-49_
- reflection: `USTRUCT()`
- inherits: `FRpcMessage`
- L43 _public member_ `bool Result = false;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L45 _public function_ `FPortalPackageInstallerInstallResponse()`
- L46 _public function_ `FPortalPackageInstallerInstallResponse(bool InResult) : Result(InResult)`

#### struct `FPortalPackageInstallerUninstallRequest`  
`struct FPortalPackageInstallerUninstallRequest : public FRpcMessage`  
_L53-77_
- reflection: `USTRUCT()`
- inherits: `FRpcMessage`
- L59 _public member_ `FString AppName;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L62 _public member_ `FString BuildLabel;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L65 _public member_ `FString InstallationPath;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L68 _public member_ `bool RemoveUserFiles = false;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L70 _public function_ `FPortalPackageInstallerUninstallRequest()`
- L71 _public function_ `FPortalPackageInstallerUninstallRequest(const FString& InAppName, const FString& InBuildLabel, const FString& InInstallationPath, bool InRemoveUserFiles) : AppName(InAppName) , BuildLabel(InBuildLabel) , InstallationPath(InInstallationPath) , RemoveUserFiles(InRemoveUserFiles)`

#### struct `FPortalPackageInstallerUninstallResponse`  
`struct FPortalPackageInstallerUninstallResponse : public FRpcMessage`  
_L81-93_
- reflection: `USTRUCT()`
- inherits: `FRpcMessage`
- L87 _public member_ `bool Result = false;` — `UPROPERTY(EditAnywhere, Category="Message")`
- L89 _public function_ `FPortalPackageInstallerUninstallResponse()`
- L90 _public function_ `FPortalPackageInstallerUninstallResponse(bool InResult) : Result(InResult)`

### `Source/Runtime/Portal/Messages/Public/PortalUserLoginMessages.h` (Public)


#### struct `FPortalUserLoginPromptUserForSignInRequest`  
`struct FPortalUserLoginPromptUserForSignInRequest : public FRpcMessage`  
_L10-17_
- reflection: `USTRUCT()`
- inherits: `FRpcMessage`
- L15 _public function_ `FPortalUserLoginPromptUserForSignInRequest()`

#### struct `FPortalUserLoginPromptUserForSignInResponse`  
`struct FPortalUserLoginPromptUserForSignInResponse : public FRpcMessage`  
_L21-36_
- reflection: `USTRUCT()`
- inherits: `FRpcMessage`
- L27 _public member_ `bool Result;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L29 _public function_ `FPortalUserLoginPromptUserForSignInResponse() : Result(false)`
- L33 _public function_ `FPortalUserLoginPromptUserForSignInResponse(bool InResult) : Result(InResult)`

### `Source/Runtime/Portal/Messages/Public/PortalUserMessages.h` (Public)


#### struct `FPortalUserGetUserDetailsRequest`  
`struct FPortalUserGetUserDetailsRequest : public FRpcMessage`  
_L11-18_
- reflection: `USTRUCT()`
- inherits: `FRpcMessage`
- L16 _public function_ `FPortalUserGetUserDetailsRequest()`

#### struct `FPortalUserGetUserDetailsResponse`  
`struct FPortalUserGetUserDetailsResponse : public FRpcMessage`  
_L22-34_
- reflection: `USTRUCT()`
- inherits: `FRpcMessage`
- L28 _public member_ `FPortalUserDetails Result;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L30 _public function_ `FPortalUserGetUserDetailsResponse()`
- L31 _public function_ `FPortalUserGetUserDetailsResponse(const FPortalUserDetails& InResult) : Result(InResult)`

#### struct `FPortalUserIsEntitledToItemRequest`  
`struct FPortalUserIsEntitledToItemRequest : public FRpcMessage`  
_L39-59_
- reflection: `USTRUCT()`
- inherits: `FRpcMessage`
- L45 _public member_ `FString ItemId;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L48 _public member_ `EEntitlementCacheLevelRequest CacheLevel = EEntitlementCacheLevelRequest::Memory;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L50 _public function_ `FPortalUserIsEntitledToItemRequest()`
- L53 _public function_ `FPortalUserIsEntitledToItemRequest( const FString& InItemId, EEntitlementCacheLevelRequest InCacheLevel) : ItemId(InItemId) , CacheLevel(InCacheLevel)`

#### struct `FPortalUserIsEntitledToItemResponse`  
`struct FPortalUserIsEntitledToItemResponse : public FRpcMessage`  
_L62-76_
- reflection: `USTRUCT()`
- inherits: `FRpcMessage`
- L68 _public member_ `FPortalUserIsEntitledToItemResult Result;` — `UPROPERTY(EditAnywhere, Category = "Message")`
- L70 _public function_ `FPortalUserIsEntitledToItemResponse()`
- L73 _public function_ `FPortalUserIsEntitledToItemResponse(const FPortalUserIsEntitledToItemResult& InResult) : Result(InResult)`
