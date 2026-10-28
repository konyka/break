# Runtime / PortalServices

- module root: `Source/Runtime/Portal/Services`
- headers: 9; symbols: 52
- symbol kinds: class=9, enum=2, enumerator=5, function=5, member=7, prototype=22, struct=2
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/Portal/Services/Private/PortalServiceLocator.h` (Private)


#### class `FPortalServiceLocatorFactory`  
`class FPortalServiceLocatorFactory`  
_L9-13_
- L12 _public prototype_ `static TSharedRef<IPortalServiceLocator> Create(const TSharedRef<FTypeContainer>& ServiceDependencies);`

### `Source/Runtime/Portal/Services/Public/Account/IPortalUser.h` (Public)


#### struct `FPortalUserDetails`  
`struct FPortalUserDetails`  
_L14-40_
- reflection: `USTRUCT()`
- desc: The basic data for the last or currently signed-in user.
- L20 _public member_ `FText DisplayName;` — `UPROPERTY(EditAnywhere, Category = "User")` — The users epic games account display name
- L24 _public member_ `FText Email;` — `UPROPERTY(EditAnywhere, Category = "User")` — The users epic games account email address
- L28 _public member_ `FText RealName;` — `UPROPERTY(EditAnywhere, Category = "User")` — The users real name attached to their epic games account
- L32 _public member_ `bool IsSignedIn;` — `UPROPERTY(EditAnywhere, Category = "User")` — Whether this user is currently signed-in to the portal
- L34 _public function_ `FPortalUserDetails() : DisplayName() , Email() , RealName() , IsSignedIn(false)`

#### enum `EEntitlementCacheLevelRequest`  
`enum class EEntitlementCacheLevelRequest : uint8`  
_L49-63_
- reflection: `UENUM()`
- desc: The available options for the different levels of caches available when requesting information about user entitlements. Disk cache level includes Memory cache level.
- L55 _public enumerator_ `Memory = 1` — Allow reference to entitlements cached in-memory for this session of the portal. These are periodically updated. This is the recommended level for entitlement checking.
- L62 _public enumerator_ `Disk = 2` — Allow reference to entitlements cached on disk between sessions of the portal. This cache is updated regularly while a user is signed-in.  If no user is signed-in then disk cached entitlements are still used from the last signed-in user's session.

#### enum `EEntitlementCacheLevelRetrieved`  
`enum class EEntitlementCacheLevelRetrieved : uint8`  
_L69-85_
- reflection: `UENUM()`
- desc: Used to delineate which cache an entitlement check result was retrieved from.
- L71 _public enumerator_ `None = 0`
- L77 _public enumerator_ `Memory = 1` — Allow reference to entitlements cached in-memory for this session of the portal. These are periodically updated. This is the recommended level for entitlement checking.
- L84 _public enumerator_ `Disk = 2` — Allow reference to entitlements cached on disk between sessions of the portal. This cache is updated regularly while a user is signed-in.  If no user is signed-in then disk cached entitlements are still used from the last signed-in user's session.

#### struct `FPortalUserIsEntitledToItemResult`  
`struct FPortalUserIsEntitledToItemResult`  
_L88-118_
- reflection: `USTRUCT()`
- L94 _public member_ `FString ItemId;` — `UPROPERTY(EditAnywhere, Category = "Entitlement")` — The item id that was checked for an active entitlement
- L98 _public member_ `bool IsEntitled;` — `UPROPERTY(EditAnywhere, Category = "Entitlement")` — Whether this user is entitled to the item id
- L102 _public member_ `EEntitlementCacheLevelRetrieved RetrievedFromCacheLevel;` — `UPROPERTY(EditAnywhere, Category = "Entitlement")` — How fresh this entitlement information is
- L104 _public function_ `FPortalUserIsEntitledToItemResult() : ItemId() , IsEntitled(false) , RetrievedFromCacheLevel(EEntitlementCacheLevelRetrieved::None)`
- L110 _public function_ `FPortalUserIsEntitledToItemResult( const FString& InItemId, const bool InIsEntitled, const EEntitlementCacheLevelRetrieved InRetrievedFromCacheLevel) : ItemId(InItemId) , IsEntitled(InIsEntitled) , RetrievedFromCacheLevel(InRetrievedFromCacheLevel)`

#### class `IPortalUser`  
`class IPortalUser : public IPortalService`  
_L124-153_
- inherits: `IPortalService`
- desc: Interface for the Portal application's user services. Specializes in readonly requests for information about the last or currently signed-in user.
- L132 _public prototype_ `virtual TAsyncResult<FPortalUserDetails> GetUserDetails() = 0;` — Requests the details of the last or currently signed in user
- L148 _public prototype_ `virtual TAsyncResult<FPortalUserIsEntitledToItemResult> IsEntitledToItem(const FString& ItemId, EEntitlementCacheLevelRequest CacheLevel) = 0;` — Returns whether the use is entitled to the specified Item Id. @param ItemId    The guid for the catalog item to check the entitled state for @param CacheLevel    The level at which to allow referencing cached data Behavior will vary based on the entitlement cache level specified and whether the user is signed-in or not, or if the user is signed-in but latest entitlements have yet to be retrieved. See documentation about the entitlement cache levels for details. In the case where there is no cached entitlement data and the latest entitlements have yet to be retrieved, then false will be returned. The Portal will not wait for the entitlements to update before returning a response. This state can be detected when the RetrievedFromCacheLevel is None.
- L152 _public prototype_ `virtual ~IPortalUser() = default;`

#### Free symbols / members of external scopes

- L155 _prototype_ `Expose_TNameOf(IPortalUser);`

### `Source/Runtime/Portal/Services/Public/Account/IPortalUserLogin.h` (Public)


#### class `IPortalUserLogin`  
`class IPortalUserLogin : public IPortalService`  
_L12-34_
- inherits: `IPortalService`
- desc: Interface for the Portal application's user login services. Specializes in actions related to signing a user in and out of the portal.
- L28 _public prototype_ `virtual TAsyncResult<bool> PromptUserForSignIn() = 0;` — Requests that the portal come to the front and ask the user to sign-in. If a user is already signed into the Portal then a prompt may ask the existing user if they want to sign-out, especially if they have on going installations or downloads. The user may opt to not sign-out if this happens. @return whether the portal successfully received and handled your request. Note this doesn't mean that the user signed-in successfully or even that the existing user signed-out. It simply means that the Portal attempted to prompt the user for sign-in.
- L33 _public prototype_ `virtual ~IPortalUserLogin() = default;`

#### Free symbols / members of external scopes

- L36 _prototype_ `Expose_TNameOf(IPortalUserLogin);`

### `Source/Runtime/Portal/Services/Public/Application/IPortalApplicationWindow.h` (Public)


#### class `IPortalApplicationWindow`  
`class IPortalApplicationWindow : public IPortalService`  
_L11-27_
- inherits: `IPortalService`
- desc: Interface for the Portal application's marketplace services.
- L21 _public prototype_ `virtual TAsyncResult<bool> NavigateTo(const FString& Url) = 0;` — Requests that the Portal navigate the user to the specified Url @return true on success, false otherwise.
- L26 _public prototype_ `virtual ~IPortalApplicationWindow() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L28 _prototype_ `Expose_TNameOf(IPortalApplicationWindow);`

### `Source/Runtime/Portal/Services/Public/IPortalService.h` (Public)


#### class `IPortalService`  
`class IPortalService`  
_L6-14_
- L11 _public prototype_ `virtual ~IPortalService() = default;` — Virtual destructor.
- L13 _public prototype_ `virtual bool IsAvailable() const = 0;`

### `Source/Runtime/Portal/Services/Public/IPortalServiceLocator.h` (Public)


#### class `IPortalServiceLocator`  
`class IPortalServiceLocator`  
_L10-75_
- L28 _public prototype_ `virtual void Configure(const FString& ServiceName, const FWildcardString& ProductId, const FName& ServiceModule) = 0;` — Configure a service. The format of the ProductId is "ProductName_Major.Minor.Patch-Changelist+Branch". Use the '*` wild card to include multiple versions, i.e. "Fortnite_1.0.*+UE". When looking up services, the first matching configuration entry will be used. If no entry matches, nullptr will be returned. @param ServiceName The name of the service type configure. @param ProductName The product name that this configuration applies to. @param ProductVersion The version string of the product that this configuration applies to. @param ServiceModule The name of the module that implements the service.
- L40 _public function_ `template<typename ServiceType> TSharedPtr<ServiceType> GetService(const FString& ProductId = TEXT(""))` — Get a service of the specified type. @param ServiceType The type of service to get. @return The service instance, or nullptr if unavailable. @see GetServiceRef
- L56 _public function_ `template<typename ServiceType> TSharedRef<ServiceType> GetServiceRef(const FString& ProductId = TEXT(""))` — Get a service of the specified type. Unlike GetService(), this method will assert if a service instance of the specified type does not exist. @param ServiceType The type of service to get. @return The service instance. @see GetService
- L69 _protected prototype_ `virtual TSharedPtr<IPortalService> GetService(const FString& ServiceName, const FString& ProductId) = 0;` — Get a service of the specified type. @param ServiceName The name of the service type to get. @return The service instance, or nullptr if unavailable.
- L74 _public prototype_ `virtual ~IPortalServiceLocator() = default;` — Virtual destructor.

### `Source/Runtime/Portal/Services/Public/IPortalServiceProvider.h` (Public)


#### class `IPortalServiceProvider`  
`class IPortalServiceProvider : public IModuleInterface`  
_L10-23_
- inherits: `IModuleInterface`
- L22 _public prototype_ `virtual TSharedPtr<IPortalService> GetService(const FString& ServiceName, const TSharedRef<FTypeContainer>& Dependencies) = 0;` — Get a service instance of the specified type. @param ServiceName The name of the service type to get. @param Dependencies Optional service dependencies. @return The service instance, or nullptr if unavailable.

### `Source/Runtime/Portal/Services/Public/IPortalServicesModule.h` (Public)


#### class `IPortalServicesModule`  
`class IPortalServicesModule : public IModuleInterface`  
_L11-28_
- inherits: `IModuleInterface`
- L22 _public prototype_ `virtual TSharedRef<IPortalServiceLocator> CreateLocator(const TSharedRef<FTypeContainer>& ServiceDependencies) = 0;` — Create a locator for Portal services. @param ServiceDependencies Any dependencies that the services may need. @return A service locator.
- L27 _public prototype_ `virtual ~IPortalServicesModule() = default;` — Virtual destructor.

### `Source/Runtime/Portal/Services/Public/Package/IPortalPackageInstaller.h` (Public)


#### class `IPortalPackageInstaller`  
`class IPortalPackageInstaller : public IPortalService`  
_L12-43_
- inherits: `IPortalService`
- desc: Interface for package installer services.
- L25 _public prototype_ `virtual TAsyncResult<bool> Install(const FString& Path, const FString& AppName, const FString& BuildLabel) = 0;` — Install the specified package using the given request object. @param AppName The name of the application to install. @param BuildLabel The application's build label. @return The result of the task. @see UninstallPackage
- L37 _public prototype_ `virtual TAsyncResult<bool> Uninstall(const FString& Path, const FString& AppName, const FString& BuildLabel, bool RemoveUserFiles) = 0;` — Attempts to uninstall the specified package using the given request object. @param Path The path at which the package is installed. @param AppName The name of the application to uninstall. @param BuildLabel The application's build label. @param RemoveUserFiles Whether user created files should be removed as well. @return The result of the task. @see InstallPackage
- L42 _public prototype_ `virtual ~IPortalPackageInstaller() = default;` — Virtual destructor.
