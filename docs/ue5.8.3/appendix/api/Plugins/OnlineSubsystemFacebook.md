# Plugins / OnlineSubsystemFacebook

- module root: `Plugins/Online/OnlineSubsystemFacebook/Source`
- headers: 30; symbols: 508
- symbol kinds: class=35, delegate=7, enum=1, enumerator=3, function=51, macro=27, member=85, namespace=2, prototype=248, struct=6, typedef=42, variable=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreOnline, CoreUObject, HTTP, ImageCore, Json, Launch, OnlineSubsystem

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/Android/OnlineExternalUIInterfaceFacebook.h` (Private)


#### class `FOnlineExternalUIFacebook`  
`class FOnlineExternalUIFacebook : public FOnlineExternalUIFacebookCommon`  
_L14-35_
- inherits: `FOnlineExternalUIFacebookCommon`
- desc: Implementation for the Facebook external UIs
- L31 _public prototype_ `virtual ~FOnlineExternalUIFacebook();` — Destructor.
- L34 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;` — IOnlineExternalUI

#### Free symbols / members of external scopes

- L37 _typedef_ `typedef TSharedPtr<FOnlineExternalUIFacebook, ESPMode::ThreadSafe> FOnlineExternalUIFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/Android/OnlineFriendsFacebook.h` (Private)


#### class `FOnlineFriendsFacebook`  
`class FOnlineFriendsFacebook : public FOnlineFriendsFacebookCommon`  
_L13-38_
- inherits: `FOnlineFriendsFacebookCommon`
- desc: Facebook service implementation of the online friends interface (Windows)
- L24 _public prototype_ `FOnlineFriendsFacebook(FOnlineSubsystemFacebook* InSubsystem);` — Constructor @param InSubsystem Facebook subsystem being used
- L29 _public prototype_ `virtual ~FOnlineFriendsFacebook();` — Destructor
- L36 _private prototype_ `FOnlineFriendsFacebook() = delete;` — Should use the initialization constructor instead

#### Free symbols / members of external scopes

- L40 _typedef_ `typedef TSharedPtr<FOnlineFriendsFacebook, ESPMode::ThreadSafe> FOnlineFriendsFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/Android/OnlineIdentityFacebook.h` (Private)


#### enum `EFacebookLoginResponse`  
`enum class EFacebookLoginResponse : uint8`  
_L13-21_
- desc: Tied to FacebookLogin.java
- L16 _public enumerator_ `RESPONSE_OK = 0` — Facebook SDK ok response
- L18 _public enumerator_ `RESPONSE_CANCELED = 1` — Facebook SDK user cancellation
- L20 _public enumerator_ `RESPONSE_ERROR = 2` — Facebook SDK error

#### class `FOnlineIdentityFacebook`  
`class FOnlineIdentityFacebook : public FOnlineIdentityFacebookCommon`  
_L62-127_
- inherits: `FOnlineIdentityFacebookCommon`
- desc: Facebook service implementation of the online identity interface
- L69 _public prototype_ `virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;`
- L70 _public prototype_ `virtual bool Logout(int32 LocalUserNum) override;`
- L74 _public prototype_ `FOnlineIdentityFacebook(FOnlineSubsystemFacebook* InSubsystem);`
- L79 _public function_ `virtual ~FOnlineIdentityFacebook()` — Destructor
- L100 _public prototype_ `DEFINE_ONLINE_DELEGATE_ONE_PARAM(OnFacebookLogoutComplete, EFacebookLoginResponse );` — Delegate fired internally when the Java Facebook SDK has completed, notifying any OSS listeners Not meant for external use @param InResponseCode response from the FacebookSDK
- L106 _private prototype_ `void OnLoginAttemptComplete(int32 LocalUserNum, const FString& ErrorStr);` — Last function called for any single login attempt
- L109 _private prototype_ `void OnLoginComplete(EFacebookLoginResponse InResponseCode, const FString& InAccessToken, const TArray<FString>& GrantedPermissions, const TArray<FString>& DeclinedPermissions);` — Generic handler for the Java SDK login callback
- L111 _private prototype_ `void OnLoginFailed();`
- L113 _private prototype_ `void OnLogoutComplete(EFacebookLoginResponse InResponseCode);` — Generic handler for the Java SDK logout callback
- L116 _private prototype_ `DECLARE_DELEGATE_FourParams(FOnInternalLoginComplete, EFacebookLoginResponse , const FString& , const TArray<FString>& , const TArray<FString>& );` — Delegate holder for all internal related login callbacks
- L117 _private member_ `FOnInternalLoginComplete LoginCompletionDelegate;`
- L119 _private prototype_ `DECLARE_DELEGATE_OneParam(FOnInternalLogoutComplete, EFacebookLoginResponse );` — Delegate holder for all internal related logout callbacks
- L120 _private member_ `FOnInternalLogoutComplete LogoutCompletionDelegate;`
- L123 _private member_ `TArray<FString> ScopeFields;` — Config based list of permission scopes to use when logging in
- L125 _private member_ `FDelegateHandle OnFBLoginCompleteHandle;`
- L126 _private member_ `FDelegateHandle OnFBLogoutCompleteHandle;`

#### Free symbols / members of external scopes

- L23 _function_ `inline const TCHAR* ToString(EFacebookLoginResponse Response)`
- L44 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnFacebookLoginComplete, EFacebookLoginResponse , const FString& , const TArray<FString>& , const TArray<FString>& );` — Delegate fired when the Facebook Android SDK has completed a login request @param InResponseCode response from the Facebook SDK @param InAccessToken access token if the response was RESPONSE_OK
- L44 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnFacebookLoginComplete, EFacebookLoginResponse , const FString& , const TArray<FString>& , const TArray<FString>& );` — Delegate fired when the Facebook Android SDK has completed a login request @param InResponseCode response from the Facebook SDK @param InAccessToken access token if the response was RESPONSE_OK
- L45 _typedef_ `typedef FOnFacebookLoginComplete::FDelegate FOnFacebookLoginCompleteDelegate;`
- L52 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFacebookLogoutComplete, EFacebookLoginResponse );` — Delegate fired when the Facebook Android SDK has completed a logout request @param InResponseCode response from the Facebook SDK
- L52 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFacebookLogoutComplete, EFacebookLoginResponse );` — Delegate fired when the Facebook Android SDK has completed a logout request @param InResponseCode response from the Facebook SDK
- L53 _typedef_ `typedef FOnFacebookLogoutComplete::FDelegate FOnFacebookLogoutCompleteDelegate;`
- L57 _typedef_ `using FUserOnlineAccountFacebook = FUserOnlineAccountFacebookCommon;` — Android implementation of a Facebook user account
- L116 _delegate_ `DECLARE_DELEGATE_FourParams(FOnInternalLoginComplete, EFacebookLoginResponse , const FString& , const TArray<FString>& , const TArray<FString>& );` — Delegate holder for all internal related login callbacks
- L119 _delegate_ `DECLARE_DELEGATE_OneParam(FOnInternalLogoutComplete, EFacebookLoginResponse );` — Delegate holder for all internal related logout callbacks
- L129 _typedef_ `typedef TSharedPtr<FOnlineIdentityFacebook, ESPMode::ThreadSafe> FOnlineIdentityFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/Android/OnlineJniFacebookLogin.h` (Private)


#### struct `UE::Jni::FFacebookLogin`  
`struct FFacebookLogin: Java::Lang::FObject`  
_L11-27_
- inherits: `Java::Lang::FObject`
- L13 _public member_ `static constexpr FAnsiStringView ClassName = "co`
- L15 _public prototype_ `static void JNICALL nativeLoginComplete(JNIEnv* env, jobject thiz, jsize responseCode, jstring accessToken, Java::Lang::TArray<jstring>* grantedPermissions, Java::Lang::TArray<jstring>* declinedPermissions);`
- L16 _public prototype_ `static void JNICALL nativeRequestReadPermissionsComplete(JNIEnv* env, jobject thiz, jsize responseCode, jstring accessToken, Java::Lang::TArray<jstring>* grantedPermissions, Java::Lang::TArray<jstring>* declinedPermissions);`
- L17 _public prototype_ `static void JNICALL nativeRequestPublishPermissionsComplete(JNIEnv* env, jobject thiz, jsize responseCode, jstring accessToken, Java::Lang::TArray<jstring>* grantedPermissions, Java::Lang::TArray<jstring>* declinedPermissions);`
- L18 _public prototype_ `static void JNICALL nativeLogoutComplete(JNIEnv* env, jobject thiz, jsize responseCode);`
- L20 _public member_ `static constexpr FNativeMethod NativeMethods[] { UE_JNI_NATIVE_METHOD(nativeLoginComplete), UE_JNI_NATIVE_METHOD(nativeRequestReadPermissionsComplete), UE_JNI_NATIVE_METHOD(nativeRequestPublishPermissionsComplete), UE_JNI_NATIVE_METHOD(nativeLogoutComplete) };`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Jni` (scope `UE`)
- L29 _variable_ `template struct TInitialize<FFacebookLogin>;` (scope `UE::Jni`)

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/Android/OnlineSharingFacebook.h` (Private)


#### class `FOnlineSharingFacebook`  
`class FOnlineSharingFacebook : public FOnlineSharingFacebookCommon`  
_L24-68_
- inherits: `FOnlineSharingFacebookCommon`
- desc: Facebook implementation of the Online Sharing Interface
- L30 _public prototype_ `virtual bool RequestNewReadPermissions(int32 LocalUserNum, EOnlineSharingCategory NewPermissions) override;`
- L31 _public prototype_ `virtual bool RequestNewPublishPermissions(int32 LocalUserNum, EOnlineSharingCategory NewPermissions, EOnlineStatusUpdatePrivacy Privacy) override;`
- L37 _public prototype_ `FOnlineSharingFacebook(FOnlineSubsystemFacebook* InSubsystem);` — Constructor used to indicate which OSS we are a part of
- L42 _public prototype_ `virtual ~FOnlineSharingFacebook();` — Default destructor
- L60 _private prototype_ `void OnPermissionsOpFailed();` — Generic handler for both read/publish permissions requests
- L61 _private prototype_ `void OnPermissionsOpComplete(EFacebookLoginResponse InResponseCode, const FString& InAccessToken, const TArray<FString>& GrantedPermissions, const TArray<FString>& DeclinedPermissions);`
- L64 _private prototype_ `DECLARE_DELEGATE_FourParams(FOnPermissionsOpComplete, EFacebookLoginResponse , const FString& , const TArray<FString>& , const TArray<FString>& );` — Delegate holder for all internal related permissions callbacks
- L65 _private member_ `FOnPermissionsOpComplete PermissionsOpCompletionDelegate;`
- L67 _private member_ `FDelegateHandle OnFBRequestPermissionsOpCompleteHandle;`

#### Free symbols / members of external scopes

- L18 _delegate_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnFacebookRequestPermissionsOpComplete, EFacebookLoginResponse , const FString& , const TArray<FString>& , const TArray<FString>& );` — Delegate fired when the Facebook Android SDK has completed a permissions update request @param InResponseCode response from the Facebook SDK @param InAccessToken access token if the response was RESPONSE_OK
- L18 _prototype_ `DECLARE_MULTICAST_DELEGATE_FourParams(FOnFacebookRequestPermissionsOpComplete, EFacebookLoginResponse , const FString& , const TArray<FString>& , const TArray<FString>& );` — Delegate fired when the Facebook Android SDK has completed a permissions update request @param InResponseCode response from the Facebook SDK @param InAccessToken access token if the response was RESPONSE_OK
- L19 _typedef_ `typedef FOnFacebookRequestPermissionsOpComplete::FDelegate FOnFacebookRequestPermissionsOpCompleteDelegate;`
- L64 _delegate_ `DECLARE_DELEGATE_FourParams(FOnPermissionsOpComplete, EFacebookLoginResponse , const FString& , const TArray<FString>& , const TArray<FString>& );` — Delegate holder for all internal related permissions callbacks
- L70 _typedef_ `typedef TSharedPtr<FOnlineSharingFacebook, ESPMode::ThreadSafe> FOnlineSharingFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/Android/OnlineUserFacebook.h` (Private)


#### class `FOnlineUserFacebook`  
`class FOnlineUserFacebook : public FOnlineUserFacebookCommon`  
_L14-31_
- inherits: `FOnlineUserFacebookCommon`
- desc: Facebook implementation of the Online User Interface
- L24 _public prototype_ `FOnlineUserFacebook(FOnlineSubsystemFacebook* InSubsystem);` — Constructor used to indicate which OSS we are a part of
- L29 _public prototype_ `virtual ~FOnlineUserFacebook();` — Default destructor

#### Free symbols / members of external scopes

- L33 _typedef_ `typedef TSharedPtr<FOnlineUserFacebook, ESPMode::ThreadSafe> FOnlineUserFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/IOS/FacebookHelper.h` (Private)


#### class `FIOSFacebookNotificationDelegate`  
`class FIOSFacebookNotificationDelegate`  
_L14-39_
- L23 _public prototype_ `virtual void OnFacebookTokenChange(FBSDKAccessToken* OldToken, FBSDKAccessToken* NewToken) = 0;` — Callback from the SDK that the FBSDKAccessToken has changed @param OldToken previous access token, possibly null @param NewToken current access token, possibly null
- L28 _public prototype_ `virtual void OnFacebookUserIdChange() = 0;` — Callback from the SDK when the UserId has changed
- L36 _public prototype_ `virtual void OnFacebookProfileChange(FBSDKProfile* OldProfile, FBSDKProfile* NewProfile) = 0;` — Callback from the SDK when the FBSDKProfile data has changed @param OldProfile previous profile, possibly null @param NewProfile current profile, possibly null
- L38 _public prototype_ `virtual ~FIOSFacebookNotificationDelegate() = default;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/IOS/OnlineAccountFacebookIOS.h` (Private)


#### class `FUserOnlineAccountFacebookIOS`  
`class FUserOnlineAccountFacebookIOS : public FUserOnlineAccountFacebookCommon`  
_L14-31_
- inherits: `FUserOnlineAccountFacebookCommon`
- desc: IOS specialization to support limited login
- L24 _public prototype_ `FUserOnlineAccountFacebookIOS(FBSDKProfile* FromProfile);` — Create from FBSDKProfile when using limited login
- L29 _public prototype_ `virtual ~FUserOnlineAccountFacebookIOS();` — Default destructor

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/IOS/OnlineExternalUIInterfaceFacebook.h` (Private)


#### class `FOnlineExternalUIFacebook`  
`class FOnlineExternalUIFacebook : public FOnlineExternalUIFacebookCommon`  
_L14-35_
- inherits: `FOnlineExternalUIFacebookCommon`
- desc: Implementation for the Facebook external UIs
- L31 _public prototype_ `virtual ~FOnlineExternalUIFacebook();` — Destructor.
- L34 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;` — IOnlineExternalUI

#### Free symbols / members of external scopes

- L37 _typedef_ `typedef TSharedPtr<FOnlineExternalUIFacebook, ESPMode::ThreadSafe> FOnlineExternalUIFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/IOS/OnlineFriendsFacebook.h` (Private)


#### class `FOnlineFriendsFacebook`  
`class FOnlineFriendsFacebook : public FOnlineFriendsFacebookCommon`  
_L13-43_
- inherits: `FOnlineFriendsFacebookCommon`
- desc: Facebook service implementation of the online friends interface (iOS)
- L31 _public prototype_ `virtual ~FOnlineFriendsFacebook();` — Destructor
- L34 _public prototype_ `virtual bool ReadFriendsList(int32 LocalUserNum, const FString& ListName, const FOnReadFriendsListComplete& Delegate = FOnReadFriendsListComplete()) override;` — IOnlineFriends
- L41 _private prototype_ `FOnlineFriendsFacebook();` — Should use the OSS param constructor instead

#### Free symbols / members of external scopes

- L45 _typedef_ `typedef TSharedPtr<FOnlineFriendsFacebook, ESPMode::ThreadSafe> FOnlineFriendsFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/IOS/OnlineIdentityFacebook.h` (Private)


#### class `FOnlineIdentityFacebook`  
`class FOnlineIdentityFacebook : public FOnlineIdentityFacebookCommon, public FIOSFacebookNotificationDelegate, public TSharedFromThis<FOnlineIdentityFacebook>`  
_L25-112_
- inherits: `FOnlineIdentityFacebookCommon,FIOSFacebookNotificationDelegate,TSharedFromThis<FOnlineIdentityFacebook>`
- desc: Facebook service implementation of the online identity interface
- L34 _public prototype_ `virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;`
- L35 _public prototype_ `virtual bool Logout(int32 LocalUserNum) override;`
- L36 _public prototype_ `virtual FString GetAuthToken(int32 LocalUserNum) const override;`
- L44 _public prototype_ `FOnlineIdentityFacebook(FOnlineSubsystemFacebook* InSubsystem);` — Default constructor
- L49 _public function_ `virtual ~FOnlineIdentityFacebook()` — Destructor
- L59 _public prototype_ `void Shutdown();` — Shutdown the interface
- L67 _public prototype_ `void Login(int32 LocalUserNum, const FString& AccessToken);` — Login user to Facebook using classic login, given a valid access token @param LocalUserNum local id of the requesting user @param AccessToken opaque Facebook supplied access token
- L74 _public prototype_ `void LoginLimited(int32 LocalUserNum);` — Gathers login information from limited login token @param LocalUserNum local id of the requesting user
- L81 _public prototype_ `bool IsUsingClassicLogin() const;` — Returns whether we are using classic login or limited login @return true if using classic login. false if using limited login
- L91 _private prototype_ `void OnLoginAttemptComplete(int32 LocalUserNum, bool bSucceeded, const FString& ErrorStr);` — Generic callback for all attempts at login, called to end the attempt @param local id of the requesting user @param bSucceeded was login succesful? @param ErrorStr any error as a result of the login attempt
- L93 _private prototype_ `virtual void OnFacebookTokenChange(FBSDKAccessToken* OldToken, FBSDKAccessToken* NewToken) override;`
- L94 _private prototype_ `virtual void OnFacebookUserIdChange() override;`
- L95 _private prototype_ `virtual void OnFacebookProfileChange(FBSDKProfile* OldProfile, FBSDKProfile* NewProfile) override;`
- L98 _private member_ `FFacebookHelper* FacebookHelper;` — ObjC helper for access to SDK methods and callbacks
- L101 _private member_ `ELoginStatus::Type LoginStatus = ELoginStatus::NotLoggedIn;` — The current state of our login
- L104 _private member_ `TArray<FString> ScopeFields;` — Config based list of permission scopes to use when logging in
- L107 _private member_ `bool bIsUsingClassicLogin = false;` — Did we log in using limited login?
- L110 _private member_ `bool bIsLoginInProgress = false;` — Did we started a login but didn't finished yet?

#### Free symbols / members of external scopes

- L20 _typedef_ `using FUserOnlineAccountFacebook = FUserOnlineAccountFacebookIOS;` — iOS implementation of a Facebook user account
- L114 _typedef_ `typedef TSharedPtr<FOnlineIdentityFacebook, ESPMode::ThreadSafe> FOnlineIdentityFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/IOS/OnlineSharingFacebook.h` (Private)


#### class `FOnlineSharingFacebook`  
`class FOnlineSharingFacebook : public FOnlineSharingFacebookCommon`  
_L14-59_
- inherits: `FOnlineSharingFacebookCommon`
- desc: Facebook implementation of the Online Sharing Interface
- L20 _public prototype_ `virtual bool RequestNewReadPermissions(int32 LocalUserNum, EOnlineSharingCategory NewPermissions) override;`
- L21 _public prototype_ `virtual bool RequestNewPublishPermissions(int32 LocalUserNum, EOnlineSharingCategory NewPermissions, EOnlineStatusUpdatePrivacy Privacy) override;`
- L29 _public prototype_ `FOnlineSharingFacebook(FOnlineSubsystemFacebook* InSubsystem);` — Constructor used to indicate which OSS we are a part of
- L34 _public prototype_ `virtual ~FOnlineSharingFacebook();` — Default destructor
- L37 _public prototype_ `virtual void RequestCurrentPermissions(int32 LocalUserNum, FOnRequestCurrentPermissionsComplete& CompletionDelegate) override;` — IOnlineSharing
- L48 _private prototype_ `void OnRequestCurrentReadPermissionsComplete(int32 LocalUserNum, bool bWasSuccessful, const TArray<FSharingPermission>& Permissions);` — Delegate fired when current permissions have been updated after a read permissions request @param LocalUserNum the controller number of the associated user @param bWasSuccessful true permission query was successful @param Permissions set of all known permissions
- L57 _private prototype_ `void OnRequestCurrentPublishPermissionsComplete(int32 LocalUserNum, bool bWasSuccessful, const TArray<FSharingPermission>& Permissions);` — Delegate fired when current permissions have been updated after a publish permissions request @param LocalUserNum the controller number of the associated user @param bWasSuccessful true permission query was successful @param Permissions set of all known permissions

#### Free symbols / members of external scopes

- L62 _typedef_ `typedef TSharedPtr<FOnlineSharingFacebook, ESPMode::ThreadSafe> FOnlineSharingFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/IOS/OnlineUserFacebook.h` (Private)


#### class `FOnlineUserFacebook`  
`class FOnlineUserFacebook : public FOnlineUserFacebookCommon`  
_L15-31_
- inherits: `FOnlineUserFacebookCommon`
- desc: Facebook implementation of the Online User Interface
- L24 _public prototype_ `FOnlineUserFacebook(FOnlineSubsystemFacebook* InSubsystem);` — Constructor used to indicate which OSS we are a part of
- L29 _public prototype_ `virtual ~FOnlineUserFacebook();` — Default destructor

#### Free symbols / members of external scopes

- L34 _typedef_ `typedef TSharedPtr<FOnlineUserFacebook, ESPMode::ThreadSafe> FOnlineUserFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/OnlineAccountFacebookCommon.h` (Private)


#### class `FUserOnlineAccountFacebookCommon`  
`class FUserOnlineAccountFacebookCommon : public FUserOnlineAccount, public FJsonSerializable`  
_L20-134_
- inherits: `FUserOnlineAccount,FJsonSerializable`
- desc: Info associated with an user account generated by this online service
- L28 _public prototype_ `virtual FUniqueNetIdRef GetUserId() const override;`
- L29 _public prototype_ `virtual FString GetRealName() const override;`
- L30 _public prototype_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override;`
- L31 _public prototype_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L32 _public prototype_ `virtual bool SetUserAttribute(const FString& AttrName, const FString& AttrValue) override;`
- L36 _public prototype_ `virtual FString GetAccessToken() const override;`
- L37 _public prototype_ `virtual bool GetAuthAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L41 _public function_ `explicit FUserOnlineAccountFacebookCommon(const FString& InUserId = FString(), const FString& InAuthTicket = FString()) : UserIdPtr(FUniqueNetIdFacebook::Create(InUserId)) , UserId(InUserId) , AuthTicket(InAuthTicket)`
- L48 _public function_ `virtual ~FUserOnlineAccountFacebookCommon()`
- L58 _public prototype_ `bool Parse(const FString& InAuthTicket, const FString& JsonStr);` — Parse Json profile request data into the user account @param InAuthTicket previously associated auth ticket with this Json response @param JsonStr a json payload from a /me request
- L70 _protected function_ `inline bool GetAccountData(const FString& Key, FString& OutVal) const` — Get account data attribute @param Key account data entry key @param OutVal [out] value that was found @return true if entry was found
- L89 _protected function_ `inline bool SetAccountData(const FString& Key, const FString& Val)` — Set account data attribute @param Key account data entry key @param Val value that we want to set @return true if entry changed
- L101 _protected member_ `FUniqueNetIdRef UserIdPtr;` — User Id represented as a FUniqueNetId
- L103 _protected member_ `FString UserId;` — Id associated with the user account provided by the online service during registration
- L105 _protected member_ `FString RealName;` — Real name
- L107 _protected member_ `FString FirstName;` — First name
- L109 _protected member_ `FString LastName;` — Last name
- L111 _protected member_ `FUserOnlineFacebookPicture Picture;` — Profile pic
- L113 _protected member_ `FString AuthTicket;` — Ticket which is provided to user once authenticated by the online service
- L115 _protected member_ `FString AuthToken;` — Authorization Token received when using limited login
- L117 _protected member_ `FJsonSerializableKeyValueMap AccountData;` — Any addition account data associated with the user
- L124 _private prototype_ `JSON_SERIALIZE(ME_FIELD_ID, UserId);`
- L125 _private prototype_ `JSON_SERIALIZE(ME_FIELD_NAME, RealName);`
- L126 _private prototype_ `JSON_SERIALIZE(ME_FIELD_FIRSTNAME, FirstName);`
- L127 _private prototype_ `JSON_SERIALIZE(ME_FIELD_LASTNAME, LastName);`
- L128 _private prototype_ `JSON_SERIALIZE_OBJECT_SERIALIZABLE(ME_FIELD_PICTURE, Picture);`
- L129 _private prototype_ `JSON_SERIALIZE_SIMPLECOPY(AccountData);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define ME_FIELD_ID "id"` — Details about the logged in user
- L12 _macro_ `#define ME_FIELD_NAME "name"`
- L13 _macro_ `#define ME_FIELD_FIRSTNAME "first_name"`
- L14 _macro_ `#define ME_FIELD_LASTNAME "last_name"`
- L15 _macro_ `#define ME_FIELD_PICTURE "picture"`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/OnlineExternalUIFacebookCommon.h` (Private)


#### class `FOnlineExternalUIFacebookCommon`  
`class FOnlineExternalUIFacebookCommon : public IOnlineExternalUI`  
_L14-54_
- inherits: `IOnlineExternalUI`
- desc: Implementation for the Facebook external UIs
- L30 _private member_ `FOnlineSubsystemFacebookCommon* FacebookSubsystem;` — Reference to the owning subsystem
- L37 _public function_ `virtual ~FOnlineExternalUIFacebookCommon()` — Destructor.
- L42 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;` — IOnlineExternalUI
- L43 _public function_ `virtual bool ShowAccountCreationUI(const int ControllerIndex, const FOnAccountCreationUIClosedDelegate& Delegate = FOnAccountCreationUIClosedDelegate()) override`
- L44 _public prototype_ `virtual bool ShowFriendsUI(int32 LocalUserNum) override;`
- L45 _public prototype_ `virtual bool ShowInviteUI(int32 LocalUserNum, FName SessionName = NAME_GameSession) override;`
- L46 _public prototype_ `virtual bool ShowAchievementsUI(int32 LocalUserNum) override;`
- L47 _public prototype_ `virtual bool ShowLeaderboardUI(const FString& LeaderboardName) override;`
- L48 _public prototype_ `virtual bool ShowWebURL(const FString& Url, const FShowWebUrlParams& ShowParams, const FOnShowWebUrlClosedDelegate& Delegate = FOnShowWebUrlClosedDelegate()) override;`
- L49 _public prototype_ `virtual bool CloseWebURL() override;`
- L50 _public prototype_ `virtual bool ShowProfileUI(const FUniqueNetId& Requestor, const FUniqueNetId& Requestee, const FOnProfileUIClosedDelegate& Delegate = FOnProfileUIClosedDelegate()) override;`
- L51 _public prototype_ `virtual bool ShowAccountUpgradeUI(const FUniqueNetId& UniqueId) override;`
- L52 _public prototype_ `virtual bool ShowStoreUI(int32 LocalUserNum, const FShowStoreParams& ShowParams, const FOnShowStoreUIClosedDelegate& Delegate = FOnShowStoreUIClosedDelegate()) override;`
- L53 _public prototype_ `virtual bool ShowSendMessageUI(int32 LocalUserNum, const FShowSendMessageParams& ShowParams, const FOnShowSendMessageUIClosedDelegate& Delegate = FOnShowSendMessageUIClosedDelegate()) override;`

#### Free symbols / members of external scopes

- L56 _typedef_ `typedef TSharedPtr<FOnlineExternalUIFacebookCommon, ESPMode::ThreadSafe> FOnlineExternalUIFacebookCommonPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/OnlineFriendsFacebookCommon.h` (Private)


#### class `FOnlineFriendFacebook`  
`class FOnlineFriendFacebook : public FOnlineFriend, public FJsonSerializable`  
_L25-108_
- inherits: `FOnlineFriend,FJsonSerializable`
- desc: Info associated with an online friend on the Facebook service
- L33 _public prototype_ `virtual FUniqueNetIdRef GetUserId() const override;`
- L34 _public prototype_ `virtual FString GetRealName() const override;`
- L35 _public prototype_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override;`
- L36 _public prototype_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L40 _public prototype_ `virtual EInviteStatus::Type GetInviteStatus() const override;`
- L41 _public prototype_ `virtual const FOnlineUserPresence& GetPresence() const override;`
- L48 _public function_ `FOnlineFriendFacebook(const FString& InUserId=TEXT("")) : UserIdPtr(FUniqueNetIdFacebook::Create(InUserId))` — Init/default constructor
- L56 _public function_ `virtual ~FOnlineFriendFacebook()` — Destructor
- L65 _public prototype_ `bool Parse(const TSharedPtr<FJsonObject>& JsonObject);` — Parse Json friend request data @param JsonObject a json payload from a friend request
- L77 _private function_ `inline bool GetAccountData(const FString& Key, FString& OutVal) const` — Get account data attribute @param Key account data entry key @param OutVal [out] value that was found @return true if entry was found
- L89 _private member_ `FString UserIdStr;` — User Id
- L91 _private member_ `FUniqueNetIdRef UserIdPtr;` — User Id represented as a FUniqueNetId
- L93 _private member_ `FUserOnlineFacebookPicture Picture;` — Profile picture
- L95 _private member_ `FJsonSerializableKeyValueMap AccountData;` — Any addition account data associated with the friend
- L97 _private member_ `FOnlineUserPresence Presence;` — @temp presence info
- L101 _private prototype_ `JSON_SERIALIZE(FRIEND_FIELD_ID, UserIdStr);`
- L102 _private prototype_ `JSON_SERIALIZE_OBJECT_SERIALIZABLE(FRIEND_FIELD_PICTURE, Picture);`
- L103 _private prototype_ `JSON_SERIALIZE_SIMPLECOPY(AccountData);`

#### class `FOnlineFriendsFacebookCommon`  
`class FOnlineFriendsFacebookCommon : public IOnlineFriends`  
_L113-196_
- inherits: `IOnlineFriends`
- desc: Facebook service implementation of the online friends interface
- L121 _public prototype_ `virtual bool ReadFriendsList(int32 LocalUserNum, const FString& ListName, const FOnReadFriendsListComplete& Delegate = FOnReadFriendsListComplete()) override;`
- L122 _public prototype_ `virtual bool DeleteFriendsList(int32 LocalUserNum, const FString& ListName, const FOnDeleteFriendsListComplete& Delegate = FOnDeleteFriendsListComplete()) override;`
- L123 _public prototype_ `virtual bool SendInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnSendInviteComplete& Delegate = FOnSendInviteComplete()) override;`
- L124 _public prototype_ `virtual bool AcceptInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnAcceptInviteComplete& Delegate = FOnAcceptInviteComplete()) override;`
- L125 _public prototype_ `virtual bool RejectInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L126 _public prototype_ `virtual void SetFriendAlias(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FString& Alias, const FOnSetFriendAliasComplete& Delegate = FOnSetFriendAliasComplete()) override;`
- L127 _public prototype_ `virtual void DeleteFriendAlias(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnDeleteFriendAliasComplete& Delegate = FOnDeleteFriendAliasComplete()) override;`
- L128 _public prototype_ `virtual bool DeleteFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L129 _public prototype_ `virtual bool GetFriendsList(int32 LocalUserNum, const FString& ListName, TArray< TSharedRef<FOnlineFriend> >& OutFriends) override;`
- L130 _public prototype_ `virtual TSharedPtr<FOnlineFriend> GetFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L131 _public prototype_ `virtual bool IsFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName) override;`
- L132 _public prototype_ `virtual bool QueryRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace) override;`
- L133 _public prototype_ `virtual bool GetRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace, TArray< TSharedRef<FOnlineRecentPlayer> >& OutRecentPlayers) override;`
- L134 _public prototype_ `virtual void DumpRecentPlayers() const override;`
- L135 _public prototype_ `virtual bool BlockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId) override;`
- L136 _public prototype_ `virtual bool UnblockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId) override;`
- L137 _public prototype_ `virtual bool QueryBlockedPlayers(const FUniqueNetId& UserId) override;`
- L138 _public prototype_ `virtual bool GetBlockedPlayers(const FUniqueNetId& UserId, TArray< TSharedRef<FOnlineBlockedPlayer> >& OutBlockedPlayers) override;`
- L139 _public prototype_ `virtual void DumpBlockedPlayers() const override;`
- L148 _public prototype_ `FOnlineFriendsFacebookCommon(FOnlineSubsystemFacebook* InSubsystem);` — Constructor @param InSubsystem Facebook subsystem being used
- L153 _public prototype_ `virtual ~FOnlineFriendsFacebookCommon();` — Destructor
- L164 _public member_ `TMap<int, FOnlineFriendsList> FriendsMap;` — Cached friends list from last call to ReadFriendsList for each local user
- L171 _private prototype_ `FOnlineFriendsFacebookCommon() = delete;` — Should use the initialization constructor instead
- L176 _private prototype_ `void QueryFriendsList_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnReadFriendsListComplete Delegate);` — Delegate called when a user /me request from Facebook is complete
- L179 _private member_ `FString FriendsUrl;` — Config based url for querying friends list
- L182 _private member_ `TArray<FString> FriendsFields;` — Config based list of fields to use when querying friends list
- L195 _private member_ `TMap<class IHttpRequest*, FPendingFriendsQuery> FriendsQueryRequests;` — List of pending Http requests for user registration

#### struct `FOnlineFriendsFacebookCommon::FOnlineFriendsList`  
`struct FOnlineFriendsList`  
_L159-162_
- desc: List of online friends
- L161 _public member_ `TArray< TSharedRef<FOnlineFriendFacebook> > Friends;`

#### struct `FOnlineFriendsFacebookCommon::FPendingFriendsQuery`  
`struct FPendingFriendsQuery`  
_L185-193_
- desc: Info used to send request to register a user
- L187 _public function_ `FPendingFriendsQuery(int32 InLocalUserNum=0) : LocalUserNum(InLocalUserNum)`
- L192 _public member_ `int32 LocalUserNum;` — local index of user making the request

#### Free symbols / members of external scopes

- L16 _macro_ `#define FRIEND_FIELD_ID "id"` — Details about a friend
- L17 _macro_ `#define FRIEND_FIELD_NAME "name"`
- L18 _macro_ `#define FRIEND_FIELD_FIRSTNAME "first_name"`
- L19 _macro_ `#define FRIEND_FIELD_LASTNAME "last_name"`
- L20 _macro_ `#define FRIEND_FIELD_PICTURE "picture"`
- L198 _typedef_ `typedef TSharedPtr<FOnlineFriendsFacebookCommon, ESPMode::ThreadSafe> FOnlineFriendsFacebookCommonPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/OnlineIdentityFacebookCommon.h` (Private)


#### class `FOnlineIdentityFacebookCommon`  
`class FOnlineIdentityFacebookCommon : public IOnlineIdentity`  
_L31-127_
- inherits: `IOnlineIdentity`
- desc: Facebook service implementation of the online identity interface
- L38 _protected member_ `FOnlineSubsystemFacebook* FacebookSubsystem;` — Parent subsystem
- L40 _protected member_ `FString MeURL;` — URL for Facebook API to retrieve personal details
- L42 _protected member_ `FUserOnlineAccountFacebookMap UserAccounts;` — Users that have been registered/authenticated
- L44 _protected member_ `TMap<int32, FUniqueNetIdPtr > UserIds;` — Ids mapped to locally registered users
- L49 _public prototype_ `virtual bool AutoLogin(int32 LocalUserNum) override;` — IOnlineIdentity
- L50 _public prototype_ `virtual TSharedPtr<FUserOnlineAccount> GetUserAccount(const FUniqueNetId& UserId) const override;`
- L51 _public prototype_ `virtual TArray<TSharedPtr<FUserOnlineAccount> > GetAllUserAccounts() const override;`
- L52 _public prototype_ `virtual FUniqueNetIdPtr GetUniquePlayerId(int32 LocalUserNum) const override;`
- L53 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(uint8* Bytes, int32 Size) override;`
- L54 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(const FString& Str) override;`
- L55 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(int32 LocalUserNum) const override;`
- L56 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(const FUniqueNetId& UserId) const override;`
- L57 _public prototype_ `virtual FString GetPlayerNickname(int32 LocalUserNum) const override;`
- L58 _public prototype_ `virtual FString GetPlayerNickname(const FUniqueNetId& UserId) const override;`
- L59 _public prototype_ `virtual FString GetAuthToken(int32 LocalUserNum) const override;`
- L60 _public prototype_ `virtual void RevokeAuthToken(const FUniqueNetId& UserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate) override;`
- L61 _public prototype_ `virtual void GetUserPrivilege(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate, EShowPrivilegeResolveUI ShowResolveUI=EShowPrivilegeResolveUI::Default) override;`
- L62 _public prototype_ `virtual FPlatformUserId GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& UniqueNetId) const override;`
- L63 _public prototype_ `virtual FString GetAuthType() const override;`
- L67 _public prototype_ `FOnlineIdentityFacebookCommon(FOnlineSubsystemFacebook* InSubsystem);`
- L72 _public function_ `virtual ~FOnlineIdentityFacebookCommon()` — Destructor
- L94 _public prototype_ `void RequestCurrentPermissions(int32 LocalUserNum, FOnRequestCurrentPermissionsComplete& InCompletionDelegate);` — Retrieve the permissions for a given user and access token @param LocalUserNum the controller number of the associated user @param InCompletionDelegate delegate to fire when request is completed
- L99 _protected member_ `TArray<FString> ProfileFields;` — Profile fields
- L106 _private prototype_ `void MeUser_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, FOnProfileRequestComplete InCompletionDelegate);` — Delegate called when a user /me request from Facebook is complete
- L126 _private member_ `TMap<IHttpRequest*, FPendingLoginUser> LoginUserRequests;` — List of pending Http requests for user registration

#### struct `FOnlineIdentityFacebookCommon::FPendingLoginUser`  
`struct FPendingLoginUser`  
_L109-124_
- desc: Info used to send request to register a user
- L111 _public function_ `FPendingLoginUser( int32 InLocalUserNum=0, const FString& InAccessToken=FString() ) : LocalUserNum(InLocalUserNum) , AccessToken(InAccessToken)`
- L121 _public member_ `int32 LocalUserNum;` — local index of user being registered
- L123 _public member_ `FString AccessToken;` — Access token being used to login to Facebook

#### Free symbols / members of external scopes

- L13 _macro_ `#define AUTH_TYPE_FACEBOOK TEXT("facebook")`
- L14 _macro_ `#define FB_AUTH_EXPIRED_CREDS TEXT("com.epicgames.fb.oauth.expiredcreds");`
- L23 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnProfileRequestComplete, int32 , bool , const FString& );` — Delegate fired after a Facebook profile request has been completed @param LocalUserNum the controller number of the associated user @param bWasSuccessful was the request successful @param ErrorStr error associated with the request
- L23 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnProfileRequestComplete, int32 , bool , const FString& );` — Delegate fired after a Facebook profile request has been completed @param LocalUserNum the controller number of the associated user @param bWasSuccessful was the request successful @param ErrorStr error associated with the request
- L26 _typedef_ `typedef TMap<FString, TSharedRef<FUserOnlineAccountFacebookCommon> > FUserOnlineAccountFacebookMap;` — Mapping from user id to internal online account info (only one per user)
- L129 _typedef_ `typedef TSharedPtr<FOnlineIdentityFacebookCommon, ESPMode::ThreadSafe> FOnlineIdentityFacebookCommonPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/OnlineSharingFacebookCommon.h` (Private)


#### class `FFacebookPermissions`  
`class FFacebookPermissions`  
_L35-128_
- desc: Registry of known permissions associated with a logged in user
- L41 _private typedef_ `typedef TMap<EOnlineSharingCategory, TArray<FString>> FSharingPermissionsMap;` — The read permissions map which sets up the Facebook permissions in their correct category
- L42 _private member_ `FSharingPermissionsMap SharingPermissionsMap;`
- L75 _private prototype_ `EOnlineSharingCategory GetCategoryFromFacebookPermission(const FString& FacebookPermission) const;`
- L78 _private member_ `TArray<FSharingPermission> GrantedPerms;` — List of known permissions to have been accepted by the user
- L80 _private member_ `TArray<FSharingPermission> DeclinedPerms;` — List of known permissions intentionally declined by the user
- L84 _public function_ `FFacebookPermissions()`
- L85 _public function_ `~FFacebookPermissions()`
- L92 _public prototype_ `void GetPermissions(TArray<FSharingPermission>& OutPermissions);` — Get the current list of permissions, granted and denied @param OutPermission store the current permissions
- L97 _public prototype_ `void Setup();` — Setup the permission categories with the relevant Facebook entries
- L102 _public prototype_ `void Reset();` — Clear out all permissions
- L109 _public prototype_ `bool RefreshPermissions(const FString& NewJsonStr);` — Reset the current permissions, filling them in from a json string @param NewJsonStr valid json response from Facebook permissions request
- L117 _public prototype_ `void RefreshPermissions(const TArray<FString>& GrantedPermissions, const TArray<FString>& DeclinedPermissions);` — Reset the current permissions, filling them from string arrays @param GrantedPermissions array of accepted Facebook permissions @param DeclinedPermissions array of declined Facebook permissions
- L127 _public prototype_ `bool HasPermission(EOnlineSharingCategory RequestedPermission, TArray<FSharingPermission>& OutMissingPermissions) const;` — Has this user granted the proper permissions for a given category @param RequestedPermission type of permission to check for @param OutMissingPermissions if the function returns false, this is the list of permissions still needed to proceed @return true if the user has granted all permissions related to the category, false if there are missing permissions

#### class `FFacebookPermissions::FFacebookPermissionsJson`  
`class FFacebookPermissionsJson : public FJsonSerializable`  
_L44-73_
- inherits: `FJsonSerializable`
- L68 _public member_ `TArray<FFacebookPermissionJson> Permissions;` — Main error body
- L71 _public prototype_ `JSON_SERIALIZE_ARRAY_SERIALIZABLE(PERM_JSON_PERMISSIONS, Permissions, FFacebookPermissionJson);`

#### class `FFacebookPermissions::FFacebookPermissionsJson::FFacebookPermissionJson`  
`class FFacebookPermissionJson : public FJsonSerializable`  
_L47-64_
- inherits: `FJsonSerializable`
- L53 _public member_ `FString Name;` — Name of the permission
- L55 _public member_ `FString Status;` — Status of the permission (granted/declined)
- L57 _public function_ `FFacebookPermissionJson()`
- L61 _public prototype_ `JSON_SERIALIZE(PERM_JSON_PERMISSION_NAME, Name);`
- L62 _public prototype_ `JSON_SERIALIZE(PERM_JSON_PERMISSION_STATUS, Status);`

#### class `FOnlineSharingFacebookCommon`  
`class FOnlineSharingFacebookCommon : public IOnlineSharing`  
_L134-203_
- inherits: `IOnlineSharing`
- desc: Facebook implementation of the Online Sharing Interface
- L140 _public prototype_ `virtual void RequestCurrentPermissions(int32 LocalUserNum, FOnRequestCurrentPermissionsComplete& CompletionDelegate) override;`
- L141 _public prototype_ `virtual void GetCurrentPermissions(int32 LocalUserNum, TArray<FSharingPermission>& OutPermissions) override;`
- L142 _public prototype_ `virtual bool ReadNewsFeed(int32 LocalUserNum, int32 NumPostsToRead) override;`
- L143 _public prototype_ `virtual bool RequestNewReadPermissions(int32 LocalUserNum, EOnlineSharingCategory NewPermissions) override;`
- L144 _public prototype_ `virtual bool ShareStatusUpdate(int32 LocalUserNum, const FOnlineStatusUpdate& StatusUpdate) override;`
- L145 _public prototype_ `virtual bool RequestNewPublishPermissions(int32 LocalUserNum, EOnlineSharingCategory NewPermissions, EOnlineStatusUpdatePrivacy Privacy) override;`
- L146 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedNewsFeed(int32 LocalUserNum, int32 NewsFeedIdx, FOnlineStatusUpdate& OutNewsFeed) override;`
- L147 _public prototype_ `virtual EOnlineCachedResult::Type GetCachedNewsFeeds(int32 LocalUserNum, TArray<FOnlineStatusUpdate>& OutNewsFeeds) override;`
- L155 _public prototype_ `FOnlineSharingFacebookCommon(FOnlineSubsystemFacebook* InSubsystem);` — Constructor used to indicate which OSS we are a part of
- L160 _public prototype_ `virtual ~FOnlineSharingFacebookCommon();` — Default destructor
- L168 _public prototype_ `void SetCurrentPermissions(const TArray<FString>& GrantedPermissions, const TArray<FString>& DeclinedPermissions);` — Reset the current permissions, filling them from string arrays @param GrantedPermissions array of accepted Facebook permissions @param DeclinedPermissions array of declined Facebook permissions
- L173 _protected member_ `FOnlineSubsystemFacebook* Subsystem;` — Parent subsystem
- L175 _protected member_ `FString PermissionsURL;` — Permissions request URL
- L177 _protected member_ `FFacebookPermissions CurrentPermissions;` — Current state of granted/declined permissions
- L190 _private prototype_ `void Permissions_HttpComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, int32 LocalUserNum, FOnRequestCurrentPermissionsComplete CompletionDelegate);` — Delegate fired when the current permissions request completes @param HttpRequest the permission request @param HttpResposne the permission response @param bSucceeded did the request succeed @param LocalUserNum local user that made the request @param CompletionDelegate follow up delegate to fire now that this request is complete
- L201 _private prototype_ `void OnLoginStatusChanged(int32 LocalUserNum, ELoginStatus::Type OldStatus, ELoginStatus::Type NewStatus, const FUniqueNetId& UserId);` — Delegate fired when login status changes need to reset permissions on logout @param LocalUserNum local user of interest @param OldStatus previous login status @param NewStatus current login status @param UserId user id of interest
- L202 _private member_ `FDelegateHandle LoginStatusChangedDelegates[MAX_LOCAL_PLAYERS];`

#### Free symbols / members of external scopes

- L16 _macro_ `#define PERM_PUBLIC_PROFILE "public_profile"` — Permissions to request at login
- L17 _macro_ `#define PERM_PUBLIC_GAMING_PROFILE "gaming_profile" // Same as public_profile for facebook apps with Gaming Services type`
- L18 _macro_ `#define PERM_READ_EMAIL "email"`
- L21 _macro_ `#define PERM_READ_FRIENDS "user_friends"` — Elevated read permissions
- L24 _macro_ `#define PERM_JSON_PERMISSIONS "data"` — Facebook Permission Json
- L25 _macro_ `#define PERM_JSON_PERMISSION_NAME "permission"`
- L26 _macro_ `#define PERM_JSON_PERMISSION_STATUS "status"`
- L29 _macro_ `#define PERM_GRANTED "granted"` — Facebook Permission status
- L30 _macro_ `#define PERM_DECLINED "declined"`
- L206 _typedef_ `typedef TSharedPtr<FOnlineSharingFacebookCommon, ESPMode::ThreadSafe> FOnlineSharingFacebookCommonPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/OnlineSubsystemFacebookCommon.h` (Private)


#### class `FOnlineSubsystemFacebookCommon`  
`class FOnlineSubsystemFacebookCommon : public FOnlineSubsystemImpl`  
_L20-115_
- inherits: `FOnlineSubsystemImpl`
- desc: OnlineSubsystemFacebookCommon - Implementation of the online subsystem for Facebook services
- L28 _private prototype_ `bool HandleFacebookExecCommands(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar);` — Exec function handling for Exec() call
- L31 _private prototype_ `void HandleFacebookLoginCommand(int32 LocalNum);` — Handle facebook login console command
- L33 _private prototype_ `void HandleFacebookLogoutCommand(int32 LocalNum);` — Handle facebook logout console command
- L35 _private prototype_ `void HandleFacebookFriendsCommand(int32 LocalNum);` — Handle facebook friends console command
- L37 _private prototype_ `void HandleFacebookRequestReadScopesCommand(EOnlineSharingCategory Scopes, int32 LocalNum);` — Handle facebook request additional scopes console command
- L38 _private prototype_ `void HandleFacebookRequestPublishScopesCommand(EOnlineSharingCategory Scopes, int32 LocalNum);`
- L43 _public prototype_ `virtual IOnlineSessionPtr GetSessionInterface() const override;` — IOnlineSubsystem Interface
- L44 _public prototype_ `virtual IOnlineFriendsPtr GetFriendsInterface() const override;`
- L45 _public prototype_ `virtual IOnlinePartyPtr GetPartyInterface() const override;`
- L46 _public prototype_ `virtual IOnlineGroupsPtr GetGroupsInterface() const override;`
- L47 _public prototype_ `virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override;`
- L48 _public prototype_ `virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;`
- L49 _public prototype_ `virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;`
- L50 _public prototype_ `virtual IOnlineVoicePtr GetVoiceInterface() const override;`
- L51 _public prototype_ `virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;`
- L52 _public prototype_ `virtual IOnlineTimePtr GetTimeInterface() const override;`
- L53 _public prototype_ `virtual IOnlineIdentityPtr GetIdentityInterface() const override;`
- L54 _public prototype_ `virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;`
- L55 _public prototype_ `virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;`
- L56 _public function_ `virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override`
- L57 _public function_ `virtual IOnlinePurchasePtr GetPurchaseInterface() const override`
- L58 _public prototype_ `virtual IOnlineEventsPtr GetEventsInterface() const override;`
- L59 _public prototype_ `virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;`
- L60 _public prototype_ `virtual IOnlineSharingPtr GetSharingInterface() const override;`
- L61 _public prototype_ `virtual IOnlineUserPtr GetUserInterface() const override;`
- L62 _public prototype_ `virtual IOnlineMessagePtr GetMessageInterface() const override;`
- L63 _public prototype_ `virtual IOnlinePresencePtr GetPresenceInterface() const override;`
- L64 _public prototype_ `virtual IOnlineChatPtr GetChatInterface() const override;`
- L65 _public prototype_ `virtual IOnlineStatsPtr GetStatsInterface() const override;`
- L66 _public prototype_ `virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override;`
- L67 _public prototype_ `virtual IOnlineTournamentPtr GetTournamentInterface() const override;`
- L68 _public prototype_ `virtual bool Init() override;`
- L69 _public prototype_ `virtual bool Shutdown() override;`
- L70 _public prototype_ `virtual FString GetAppId() const override;`
- L71 _public prototype_ `virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L72 _public prototype_ `virtual FText GetOnlineServiceName() const override;`
- L76 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L81 _public function_ `const FString& GetAPIVer() const` — @return the API version in use (depends on the Facebook app settings)
- L86 _public prototype_ `virtual ~FOnlineSubsystemFacebookCommon();` — Destructor
- L92 _public prototype_ `explicit FOnlineSubsystemFacebookCommon(FName InInstanceName);`
- L97 _protected member_ `FString ClientId;` — The client id given to us by Facebook
- L99 _protected member_ `FString APIVer;` — Version of the API in use (depends on the Facebook app settings)
- L102 _protected member_ `FOnlineIdentityFacebookCommonPtr FacebookIdentity;` — Facebook implementation of identity interface
- L105 _protected member_ `FOnlineFriendsFacebookCommonPtr FacebookFriends;` — Facebook implementation of friends interface
- L108 _protected member_ `FOnlineSharingFacebookCommonPtr FacebookSharing;` — Facebook implementation of sharing interface
- L111 _protected member_ `FOnlineUserFacebookCommonPtr FacebookUser;` — Facebook implementation of user interface
- L114 _protected member_ `FOnlineExternalUIFacebookCommonPtr FacebookExternalUI;` — Facebook implementation of the external ui

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TSharedPtr<class FOnlineIdentityFacebookCommon, ESPMode::ThreadSafe> FOnlineIdentityFacebookCommonPtr;` — Forward declarations of all interface classes
- L12 _typedef_ `typedef TSharedPtr<class FOnlineFriendsFacebookCommon, ESPMode::ThreadSafe> FOnlineFriendsFacebookCommonPtr;`
- L13 _typedef_ `typedef TSharedPtr<class FOnlineSharingFacebookCommon, ESPMode::ThreadSafe> FOnlineSharingFacebookCommonPtr;`
- L14 _typedef_ `typedef TSharedPtr<class FOnlineUserFacebookCommon, ESPMode::ThreadSafe> FOnlineUserFacebookCommonPtr;`
- L15 _typedef_ `typedef TSharedPtr<class FOnlineExternalUIFacebookCommon, ESPMode::ThreadSafe> FOnlineExternalUIFacebookCommonPtr;`
- L117 _typedef_ `typedef TSharedPtr<FOnlineSubsystemFacebookCommon, ESPMode::ThreadSafe> FOnlineSubsystemFacebookCommonPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/OnlineSubsystemFacebookPrivate.h` (Private)


#### Free symbols / members of external scopes

- L15 _macro_ `#define ONLINE_LOG_PREFIX TEXT("Facebook: ")`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/OnlineSubsystemFacebookTypes.h` (Private)


#### class `FUniqueNetIdFacebook`  
`class FUniqueNetIdFacebook : public FUniqueNetId`  
_L19-112_
- inherits: `FUniqueNetId`
- desc: Facebook specific implementation of the unique net id
- L28 _public function_ `template<typename... TArgs> static FUniqueNetIdFacebookRef Create(TArgs&&... Args)`
- L34 _public function_ `virtual FName GetType() const override`
- L39 _public function_ `virtual const uint8* GetBytes() const override`
- L45 _public function_ `virtual int32 GetSize() const override`
- L50 _public function_ `virtual bool IsValid() const override`
- L56 _public function_ `virtual FString ToString() const override`
- L62 _public function_ `virtual FString ToDebugString() const override`
- L68 _public function_ `virtual uint32 GetTypeHash() const override`
- L75 _public function_ `static const FUniqueNetIdRef& EmptyId()` — global static instance of invalid (zero) id
- L83 _private function_ `FUniqueNetIdFacebook() : UniqueNetId(0)` — Hidden on purpose
- L93 _private function_ `explicit FUniqueNetIdFacebook(const FUniqueNetIdFacebook& Src) : UniqueNetId(Src.UniqueNetId)` — Copy Constructor @param Src the id to copy
- L103 _private function_ `explicit FUniqueNetIdFacebook(uint64 InUniqueNetId) : UniqueNetId(InUniqueNetId)` — Constructs this object with the specified net id @param InUniqueNetId the id to set ours to
- L108 _private function_ `explicit FUniqueNetIdFacebook(const FString& Str) : UniqueNetId(FCString::Strtoui64(*Str, nullptr, 10))`

#### class `FErrorFacebook`  
`class FErrorFacebook : public FJsonSerializable`  
_L117-166_
- inherits: `FJsonSerializable`
- desc: Facebook error from JSON payload
- L125 _public function_ `FErrorFacebook()` — Constructor
- L158 _public member_ `FErrorBody Error;` — Main error body
- L161 _public function_ `FString ToDebugString() const` — @return debug output for logs

#### class `FErrorFacebook::FErrorBody`  
`class FErrorBody : public FJsonSerializable`  
_L129-155_
- inherits: `FJsonSerializable`
- L135 _public member_ `FString Message;` — Facebook error message
- L137 _public member_ `FString Type;` — Type of error reported by Facebook
- L139 _public member_ `int32 Code;` — Facebook error code
- L141 _public member_ `int32 ErrorSubCode;` — Facebook error sub code
- L143 _public member_ `FString FBTraceId;` — Facebook trace id
- L145 _public function_ `FErrorBody()`

#### class `FUserOnlineFacebookPicture`  
`class FUserOnlineFacebookPicture : public FJsonSerializable`  
_L169-195_
- inherits: `FJsonSerializable`
- desc: Facebook profile picture
- L189 _public member_ `FPictureData PictureData;` — User picture
- L193 _public prototype_ `JSON_SERIALIZE_OBJECT_SERIALIZABLE(PICTURE_DATA, PictureData);`

#### struct `FUserOnlineFacebookPicture::FPictureData`  
`struct FPictureData : public FJsonSerializable`  
_L174-186_
- inherits: `FJsonSerializable`
- L178 _public member_ `bool bIsSilhouette;` — Is this picture the default silhouette
- L180 _public member_ `FString PictureURL;` — URL to picture content
- L183 _public prototype_ `JSON_SERIALIZE(PICTURE_DATA_SILHOUETTE, bIsSilhouette);`
- L184 _public prototype_ `JSON_SERIALIZE(PICTURE_DATA_URL, PictureURL);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define PICTURE_DATA "data"`
- L10 _macro_ `#define PICTURE_DATA_SILHOUETTE "is_silhouette"`
- L11 _macro_ `#define PICTURE_DATA_URL "url"`
- L13 _typedef_ `using FUniqueNetIdFacebookPtr = TSharedPtr<const class FUniqueNetIdFacebook>;`
- L14 _typedef_ `using FUniqueNetIdFacebookRef = TSharedRef<const class FUniqueNetIdFacebook>;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/OnlineUserFacebookCommon.h` (Private)


#### class `FOnlineUserInfoFacebook`  
`class FOnlineUserInfoFacebook : public FOnlineUser`  
_L16-68_
- inherits: `FOnlineUser`
- desc: Info associated with an online user on the facebook service
- L23 _public prototype_ `virtual FUniqueNetIdRef GetUserId() const override;`
- L24 _public prototype_ `virtual FString GetRealName() const override;`
- L25 _public prototype_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override;`
- L26 _public prototype_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L33 _public function_ `FOnlineUserInfoFacebook(const FString& InUserId=TEXT("")) : UserId(FUniqueNetIdFacebook::Create(InUserId))` — Init/default constructor
- L41 _public function_ `virtual ~FOnlineUserInfoFacebook()` — Destructor
- L53 _public function_ `inline bool GetAccountData(const FString& Key, FString& OutVal) const` — Get account data attribute @param Key account data entry key @param OutVal [out] value that was found @return true if entry was found
- L65 _public member_ `FUniqueNetIdRef UserId;` — User Id represented as a FUniqueNetId
- L67 _public member_ `TMap<FString, FString> AccountData;` — Any addition account data associated with the friend

#### class `FOnlineUserFacebookCommon`  
`class FOnlineUserFacebookCommon : public IOnlineUser`  
_L74-108_
- inherits: `IOnlineUser`
- desc: Facebook implementation of the Online User Interface
- L81 _public prototype_ `virtual bool QueryUserInfo(int32 LocalUserNum, const TArray<FUniqueNetIdRef >& UserIds) override;`
- L82 _public prototype_ `virtual bool GetAllUserInfo(int32 LocalUserNum, TArray< TSharedRef<class FOnlineUser> >& OutUsers) override;`
- L83 _public prototype_ `virtual TSharedPtr<FOnlineUser> GetUserInfo(int32 LocalUserNum, const class FUniqueNetId& UserId) override;`
- L84 _public prototype_ `virtual bool QueryUserIdMapping(const FUniqueNetId& UserId, const FString& DisplayNameOrEmail, const FOnQueryUserMappingComplete& Delegate = FOnQueryUserMappingComplete()) override;`
- L85 _public prototype_ `virtual bool QueryExternalIdMappings(const FUniqueNetId& LocalUserId, const FExternalIdQueryOptions& QueryOptions, const TArray<FString>& ExternalIds, const FOnQueryExternalIdMappingsComplete& Delegate = FOnQueryExternalIdMappingsComplete()) override;`
- L86 _public prototype_ `virtual void GetExternalIdMappings(const FExternalIdQueryOptions& QueryOptions, const TArray<FString>& ExternalIds, TArray<FUniqueNetIdPtr>& OutIds) override;`
- L87 _public prototype_ `virtual FUniqueNetIdPtr GetExternalIdMapping(const FExternalIdQueryOptions& QueryOptions, const FString& ExternalId) override;`
- L94 _public prototype_ `FOnlineUserFacebookCommon(FOnlineSubsystemFacebookCommon* InSubsystem);` — Constructor used to indicate which OSS we are a part of
- L99 _public prototype_ `virtual ~FOnlineUserFacebookCommon();` — Default destructor
- L104 _protected member_ `FOnlineSubsystemFacebookCommon* Subsystem;`
- L107 _protected member_ `TArray< TSharedRef<FOnlineUserInfoFacebook> > CachedUsers;` — The collection of Facebook users received through the callbacks in QueryUserInfo

#### Free symbols / members of external scopes

- L110 _typedef_ `typedef TSharedPtr<FOnlineUserFacebookCommon, ESPMode::ThreadSafe> FOnlineUserFacebookCommonPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/Rest/OnlineExternalUIInterfaceFacebookRest.h` (Private)


#### class `FOnlineExternalUIFacebook`  
`class FOnlineExternalUIFacebook : public FOnlineExternalUIFacebookCommon`  
_L18-82_
- inherits: `FOnlineExternalUIFacebookCommon`
- desc: Implementation for the Facebook external UIs
- L38 _public function_ `virtual ~FOnlineExternalUIFacebook()` — Destructor.
- L43 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;` — IOnlineExternalUI
- L53 _private prototype_ `FLoginFlowResult ParseRedirectResult(const FFacebookLoginURL& URLDetails, const FString& RedirectURL);` — Parse a successful URL redirect from Facebook @param URLDetails URL config settings @param RedirectURL an URL knowns to start with the redirect URI
- L61 _private prototype_ `FLoginFlowResult OnLoginRedirectURL(const FString& RedirectURL);` — Delegate fired when redirect URLs from the login flow are passed back for parsing We are looking for the success or error completion state from Facebook to grab the access token or complete the flow @param RedirectURL URL received from the login flow for parsing
- L70 _private prototype_ `void OnExternalLoginFlowComplete(const FLoginFlowResult& Result, int ControllerIndex, const FOnLoginUIClosedDelegate Delegate);` — Delegate fired when the login flow is complete @param Result final result of the login flow action @param ControllerIndex index of the local user initiating the request @param Delegate UI closed delegate to fire, completing the external UIs part in the login process
- L81 _private prototype_ `void OnAccessTokenLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error, FOnLoginUIClosedDelegate Delegate);` — Delegate fired when the Facebook identity interface has completed login using the token retrieved from the login flow @param LocalUserNum index of the local user initiating the request @param bWasSuccessful was the login call successful @param UserId user id of the logged in user, or null if login failed @param Error error string if applicable @param Delegate UI closed delegate to fire, completing the external UIs part in the login process

#### Free symbols / members of external scopes

- L84 _typedef_ `typedef TSharedPtr<FOnlineExternalUIFacebook, ESPMode::ThreadSafe> FOnlineExternalUIFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/Rest/OnlineFriendsFacebookRest.h` (Private)


#### class `FOnlineFriendsFacebook`  
`class FOnlineFriendsFacebook : public FOnlineFriendsFacebookCommon`  
_L15-40_
- inherits: `FOnlineFriendsFacebookCommon`
- desc: Facebook service implementation of the online friends interface (Windows)
- L26 _public prototype_ `FOnlineFriendsFacebook(FOnlineSubsystemFacebook* InSubsystem);` — Constructor @param InSubsystem Facebook subsystem being used
- L31 _public prototype_ `virtual ~FOnlineFriendsFacebook();` — Destructor
- L38 _private prototype_ `FOnlineFriendsFacebook() = delete;` — Should use the initialization constructor instead

#### Free symbols / members of external scopes

- L42 _typedef_ `typedef TSharedPtr<FOnlineFriendsFacebook, ESPMode::ThreadSafe> FOnlineFriendsFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/Rest/OnlineIdentityFacebookRest.h` (Private)


#### struct `FFacebookLoginURL`  
`struct FFacebookLoginURL`  
_L20-74_
- desc: Contains URL details for Windows Facebook interaction
- L23 _public member_ `FString LoginUrl;` — The endpoint at Facebook we are supposed to hit for auth
- L25 _public member_ `FString LoginRedirectUrl;` — The redirect url for Facebook to redirect to upon completion. Note: this is configured at Facebook too
- L27 _public member_ `FString ClientId;` — The client id given to us by Facebook
- L29 _public member_ `TArray<FString> ScopeFields;` — Config based list of permission scopes to use when logging in
- L31 _public member_ `TArray<FString> NewScopeFields;` — Requested list of permission scopes when elevating permissions (merge into ScopeFields on success)
- L33 _public member_ `TArray<FString> RerequestScopeFields;` — Requested list of permission scopes when elevating permissions (merge into ScopeFields on success)
- L35 _public member_ `FString State;` — A value used to verify our response came from our server
- L37 _public member_ `bool bUsePopup;` — Should the URL include the popup display size
- L39 _public function_ `FFacebookLoginURL() : bUsePopup(false)`
- L43 _public function_ `bool IsValid() const`
- L48 _public function_ `FString GenerateNonce()`
- L55 _public function_ `FString GetURL() const`

#### class `FOnlineIdentityFacebook`  
`class FOnlineIdentityFacebook : public FOnlineIdentityFacebookCommon`  
_L79-162_
- inherits: `FOnlineIdentityFacebookCommon`
- desc: Facebook service implementation of the online identity interface
- L83 _private member_ `FFacebookLoginURL LoginURLDetails;` — Const details about communicating with Facebook API
- L85 _private member_ `bool bHasLoginOutstanding;` — Whether we have a registration in flight or not
- L88 _private member_ `TArray<FString> LoginDomains;` — Domains used for login, for cookie management
- L93 _public prototype_ `virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;`
- L94 _public prototype_ `virtual bool Logout(int32 LocalUserNum) override;`
- L98 _public prototype_ `FOnlineIdentityFacebook(FOnlineSubsystemFacebook* InSubsystem);`
- L103 _public function_ `virtual ~FOnlineIdentityFacebook()` — Destructor
- L125 _public prototype_ `void RequestElevatedPermissions(int32 LocalUserNum, const TArray<FSharingPermission>& AddlPermissions, const FOnLoginCompleteDelegate& InCompletionDelegate);` — Request additional permissions for an already logged in user.  Activates the external UI for user interaction @param LocalUserNum id of the local user initiating the request @param AddlPermissions list of additional permissions that are been requested @param InCompletionDelegate delegate to fire when request has completed
- L128 _public function_ `const FFacebookLoginURL& GetLoginURLDetails() const` — @return the login configuration details
- L140 _private prototype_ `void OnAccessTokenLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);` — Delegate fired when the internal call to Login() with AccessToken is specified @param LocalUserNum index of the local user initiating the request @param bWasSuccessful was the login call successful @param UserId user id of the logged in user, or null if login failed @param Error error string if applicable
- L145 _private prototype_ `void OnExternalUILoginComplete(FUniqueNetIdPtr UniqueId, const int ControllerIndex, const FOnlineError& Error);` — Delegate fired when the call to ShowLoginUI completes
- L150 _private prototype_ `void OnExternalUIElevatedPermissionsComplete(FUniqueNetIdPtr UniqueId, const int ControllerIndex, const FOnlineError& Error, FOnLoginCompleteDelegate InCompletionDelegate);` — Delegate fired when the call to ShowLoginUI completes for requesting elevated permissions
- L160 _private prototype_ `void OnRequestCurrentPermissionsComplete(int32 LocalUserNum, bool bWasSuccessful, const TArray<FSharingPermission>& NewPermissions, FOnLoginCompleteDelegate CompletionDelegate);` — Delegate called when current permission request completes @param LocalUserNum user that made the request @param bWasSuccessful was the request successful @param NewPermissions array of all known permissions @param CompletionDelegate follow up delegate after this request is complete

#### Free symbols / members of external scopes

- L15 _typedef_ `using FUserOnlineAccountFacebook = FUserOnlineAccountFacebookCommon;` — Windows implementation of a Facebook user account
- L164 _typedef_ `typedef TSharedPtr<FOnlineIdentityFacebook, ESPMode::ThreadSafe> FOnlineIdentityFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/Rest/OnlineSharingFacebookRest.h` (Private)


#### class `FOnlineSharingFacebook`  
`class FOnlineSharingFacebook : public FOnlineSharingFacebookCommon`  
_L16-43_
- inherits: `FOnlineSharingFacebookCommon`
- desc: Facebook implementation of the Online Sharing Interface
- L22 _public prototype_ `virtual bool ReadNewsFeed(int32 LocalUserNum, int32 NumPostsToRead) override;`
- L23 _public prototype_ `virtual bool RequestNewReadPermissions(int32 LocalUserNum, EOnlineSharingCategory NewPermissions) override;`
- L24 _public prototype_ `virtual bool ShareStatusUpdate(int32 LocalUserNum, const FOnlineStatusUpdate& StatusUpdate) override;`
- L25 _public prototype_ `virtual bool RequestNewPublishPermissions(int32 LocalUserNum, EOnlineSharingCategory NewPermissions, EOnlineStatusUpdatePrivacy Privacy) override;`
- L33 _public prototype_ `FOnlineSharingFacebook(FOnlineSubsystemFacebook* InSubsystem);` — Constructor used to indicate which OSS we are a part of
- L38 _public prototype_ `virtual ~FOnlineSharingFacebook();` — Default destructor
- L42 _private prototype_ `void OnPermissionsLevelRequest(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);`

#### Free symbols / members of external scopes

- L45 _typedef_ `typedef TSharedPtr<FOnlineSharingFacebook, ESPMode::ThreadSafe> FOnlineSharingFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Private/Rest/OnlineUserFacebookRest.h` (Private)


#### class `FOnlineUserFacebook`  
`class FOnlineUserFacebook : public FOnlineUserFacebookCommon`  
_L16-33_
- inherits: `FOnlineUserFacebookCommon`
- desc: Facebook implementation of the Online User Interface
- L26 _public prototype_ `FOnlineUserFacebook(FOnlineSubsystemFacebook* InSubsystem);` — Constructor used to indicate which OSS we are a part of
- L31 _public prototype_ `virtual ~FOnlineUserFacebook();` — Default destructor

#### Free symbols / members of external scopes

- L35 _typedef_ `typedef TSharedPtr<FOnlineUserFacebook, ESPMode::ThreadSafe> FOnlineUserFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Public/OnlineSubsystemFacebook.h` (Public)


#### class `FOnlineSubsystemFacebook`  
`class FOnlineSubsystemFacebook : public FOnlineSubsystemFacebookCommon`  
_L18-40_
- inherits: `FOnlineSubsystemFacebookCommon`
- desc: OnlineSubsystemFacebook - Implementation of the online subsystem for Facebook services
- L24 _public prototype_ `virtual bool Init() override;` — FOnlineSubsystemFacebookCommon Interface
- L25 _public prototype_ `virtual bool Shutdown() override;`
- L26 _public prototype_ `virtual bool IsEnabled() const override;`
- L33 _public prototype_ `virtual ~FOnlineSubsystemFacebook();` — Destructor
- L39 _public prototype_ `explicit FOnlineSubsystemFacebook(FName InInstanceName);`

#### Free symbols / members of external scopes

- L9 _typedef_ `typedef TSharedPtr<class FOnlineIdentityFacebook, ESPMode::ThreadSafe> FOnlineIdentityFacebookPtr;` — Forward declarations of all interface classes
- L10 _typedef_ `typedef TSharedPtr<class FOnlineFriendsFacebook, ESPMode::ThreadSafe> FOnlineFriendsFacebookPtr;`
- L11 _typedef_ `typedef TSharedPtr<class FOnlineSharingFacebook, ESPMode::ThreadSafe> FOnlineSharingFacebookPtr;`
- L12 _typedef_ `typedef TSharedPtr<class FOnlineUserFacebook, ESPMode::ThreadSafe> FOnlineUserFacebookPtr;`
- L13 _typedef_ `typedef TSharedPtr<class FOnlineExternalUIFacebook, ESPMode::ThreadSafe> FOnlineExternalUIFacebookPtr;`
- L42 _typedef_ `typedef TSharedPtr<FOnlineSubsystemFacebook, ESPMode::ThreadSafe> FOnlineSubsystemFacebookPtr;`

### `Plugins/Online/OnlineSubsystemFacebook/Source/Public/OnlineSubsystemFacebookModule.h` (Public)


#### class `FOnlineSubsystemFacebookModule`  
`class FOnlineSubsystemFacebookModule : public IModuleInterface`  
_L13-49_
- inherits: `IModuleInterface`
- desc: Online subsystem module class (Facebook Implementation) Code related to the loading and handling of the Facebook module.
- L18 _private member_ `class FOnlineFactoryFacebook* FacebookFactory;` — Class responsible for creating instance(s) of the subsystem
- L24 _public prototype_ `virtual void StartupModule() override;`
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _public function_ `virtual bool SupportsDynamicReloading() override`
- L30 _public function_ `virtual bool SupportsAutomaticShutdown() override`
- L40 _public function_ `FOnlineSubsystemFacebookModule() : FacebookFactory(NULL)` — Constructor
- L47 _public function_ `virtual ~FOnlineSubsystemFacebookModule()` — Destructor

### `Plugins/Online/OnlineSubsystemFacebook/Source/Public/OnlineSubsystemFacebookPackage.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define PACKAGE_SCOPE public`
- L12 _macro_ `#define PACKAGE_SCOPE protected`
