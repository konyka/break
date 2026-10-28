# Plugins / OnlineSubsystemGoogle

- module root: `Plugins/Online/OnlineSubsystemGoogle/Source`
- headers: 18; symbols: 365
- symbol kinds: class=23, delegate=10, enum=5, enumerator=13, function=49, macro=6, member=89, namespace=2, prototype=142, struct=4, typedef=21, variable=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreOnline, HTTP, Json, Launch, OnlineSubsystem

### `Plugins/Online/OnlineSubsystemGoogle/Source/Private/Android/GoogleLoginWrapper.h` (Private)


#### class `FGoogleLoginWrapper`  
`class FGoogleLoginWrapper`  
_L15-29_
- desc: Google interface class with com.epicgames.unreal.GoogleLogin Java instance
- L18 _public prototype_ `bool Init(const FString& ServerClientId, bool bRequestServerAuthCode);`
- L19 _public prototype_ `void Shutdown();`
- L21 _public prototype_ `bool Login(const TArray<FString>& ScopeFields);`
- L22 _public prototype_ `bool Logout();`
- L25 _private member_ `jobject GoogleLoginInstance = nullptr;`
- L26 _private member_ `jmethodID InitMethod = nullptr;`
- L27 _private member_ `jmethodID LoginMethod = nullptr;`
- L28 _private member_ `jmethodID LogoutMethod = nullptr;`

### `Plugins/Online/OnlineSubsystemGoogle/Source/Private/Android/OnlineExternalUIInterfaceGoogle.h` (Private)


#### class `FOnlineExternalUIGoogle`  
`class FOnlineExternalUIGoogle : public FOnlineExternalUIGoogleCommon`  
_L14-41_
- inherits: `FOnlineExternalUIGoogleCommon`
- desc: Implementation for the Google external UIs
- L33 _public function_ `virtual ~FOnlineExternalUIGoogle()` — Destructor.
- L38 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;` — IOnlineExternalUI

#### Free symbols / members of external scopes

- L43 _typedef_ `typedef TSharedPtr<FOnlineExternalUIGoogle, ESPMode::ThreadSafe> FOnlineExternalUIGooglePtr;`

### `Plugins/Online/OnlineSubsystemGoogle/Source/Private/Android/OnlineIdentityGoogle.h` (Private)


#### enum `EGoogleLoginResponse`  
`enum class EGoogleLoginResponse : uint8`  
_L15-25_
- desc: Tied to GoogleLogin.java
- L18 _public enumerator_ `RESPONSE_OK = 0` — Google Sign In SDK ok response
- L20 _public enumerator_ `RESPONSE_CANCELED = 1` — Google Sign In  SDK user cancellation
- L22 _public enumerator_ `RESPONSE_ERROR = 2` — Google Sign In  SDK error
- L24 _public enumerator_ `RESPONSE_DEVELOPER_ERROR` — Developer setup error

#### class `FUserOnlineAccountGoogle`  
`class FUserOnlineAccountGoogle : public FUserOnlineAccountGoogleCommon`  
_L45-77_
- inherits: `FUserOnlineAccountGoogleCommon`
- desc: Android implementation of a Google user account
- L49 _public function_ `explicit FUserOnlineAccountGoogle()`
- L53 _public function_ `explicit FUserOnlineAccountGoogle(FString&& InUserId, FString&& InGivenName, FString&& InFamilyName, FString&& InDisplayName, FString&& InPicture, const FAuthTokenGoogle& InAuthToken) : FUserOnlineAccountGoogleCommon(InUserId, InAuthToken)`
- L74 _public function_ `virtual ~FUserOnlineAccountGoogle()`

#### class `FOnlineIdentityGoogle`  
`class FOnlineIdentityGoogle : public FOnlineIdentityGoogleCommon`  
_L82-141_
- inherits: `FOnlineIdentityGoogleCommon`
- desc: Google service implementation of the online identity interface
- L89 _public prototype_ `virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;`
- L90 _public prototype_ `virtual bool Logout(int32 LocalUserNum) override;`
- L94 _public prototype_ `FOnlineIdentityGoogle(FOnlineSubsystemGoogle* InSubsystem);`
- L101 _public prototype_ `bool Init();` — Initialize the interface @return true if successful, false if there was an issue
- L107 _public prototype_ `void Shutdown();` — Shuts down the interface
- L112 _public function_ `virtual ~FOnlineIdentityGoogle()` — Destructor
- L122 _public prototype_ `void OnLoginComplete(EGoogleLoginResponse InResponseCode, const TSharedPtr<FUserOnlineAccountGoogle>& User);` — Generic handler for the Java SDK login callback
- L124 _public prototype_ `void OnLogoutComplete(EGoogleLoginResponse InResponseCode);` — Generic handler for the Java SDK logout callback
- L128 _private member_ `FGoogleLoginWrapper GoogleLoginWrapper;`
- L131 _private member_ `TArray<FString> ScopeFields;` — Config based list of permission scopes to use when logging in
- L134 _private prototype_ `DECLARE_DELEGATE_TwoParams(FOnInternalLoginComplete, EGoogleLoginResponse , TSharedPtr<FUserOnlineAccountGoogle> );` — Delegate holder for all internal related login callbacks
- L135 _private member_ `FOnInternalLoginComplete LoginCompletionDelegate;`
- L137 _private prototype_ `DECLARE_DELEGATE_OneParam(FOnInternalLogoutComplete, EGoogleLoginResponse );` — Delegate holder for all internal related logout callbacks
- L138 _private member_ `FOnInternalLogoutComplete LogoutCompletionDelegate;`
- L140 _private prototype_ `FUniqueNetIdPtr RemoveUserId(int LocalUserNum);`

#### Free symbols / members of external scopes

- L27 _function_ `inline const TCHAR* ToString(EGoogleLoginResponse Response)`
- L134 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnInternalLoginComplete, EGoogleLoginResponse , TSharedPtr<FUserOnlineAccountGoogle> );` — Delegate holder for all internal related login callbacks
- L137 _delegate_ `DECLARE_DELEGATE_OneParam(FOnInternalLogoutComplete, EGoogleLoginResponse );` — Delegate holder for all internal related logout callbacks
- L143 _typedef_ `typedef TSharedPtr<FOnlineIdentityGoogle, ESPMode::ThreadSafe> FOnlineIdentityGooglePtr;`

### `Plugins/Online/OnlineSubsystemGoogle/Source/Private/Android/OnlineJniGoogleLogin.h` (Private)


#### struct `UE::Jni::FGoogleLogin`  
`struct FGoogleLogin: Java::Lang::FObject`  
_L11-25_
- inherits: `Java::Lang::FObject`
- L13 _public member_ `static constexpr FAnsiStringView ClassName = "co`
- L15 _public prototype_ `static void JNICALL nativeLoginSuccess(JNIEnv* env, jobject thiz, jstring InUserId, jstring InGivenName, jstring InFamilyName, jstring InDisplayName, jstring InPhotoUrl, jstring InIdToken, jstring InServerAuthCode);`
- L16 _public prototype_ `static void JNICALL nativeLoginFailed(JNIEnv* env, jobject thiz, jint ResponseCode);`
- L17 _public prototype_ `static void JNICALL nativeLogoutComplete(JNIEnv* env, jobject thiz, jsize responseCode);`
- L19 _public member_ `static constexpr FNativeMethod NativeMethods[] { UE_JNI_NATIVE_METHOD(nativeLoginSuccess), UE_JNI_NATIVE_METHOD(nativeLoginFailed), UE_JNI_NATIVE_METHOD(nativeLogoutComplete) };`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Jni` (scope `UE`)
- L27 _variable_ `template struct TInitialize<FGoogleLogin>;` (scope `UE::Jni`)

### `Plugins/Online/OnlineSubsystemGoogle/Source/Private/IOS/GoogleHelper.h` (Private)


#### enum `EGoogleLoginResponse`  
`enum class EGoogleLoginResponse : uint8`  
_L12-22_
- L15 _public enumerator_ `RESPONSE_OK = 0` — Google Sign In SDK ok response
- L17 _public enumerator_ `RESPONSE_NOAUTH = 1` — Silent sign in failed
- L19 _public enumerator_ `RESPONSE_CANCELED = 2` — Google Sign In  SDK user cancellation
- L21 _public enumerator_ `RESPONSE_ERROR = 3` — Google Sign In  SDK error

#### struct `FGoogleSignInData`  
`struct FGoogleSignInData`  
_L44-61_
- L47 _public function_ `FString ToDebugString() const` — @return a string that prints useful debug information about this response
- L56 _public member_ `EGoogleLoginResponse Response;` — Result of the sign in
- L58 _public member_ `FString ErrorStr;` — Error response, if any
- L60 _public member_ `FAuthTokenGoogle AuthToken;` — Token data (access/refresh/id), only valid on RESPONSE_OK

#### struct `FGoogleSignOutData`  
`struct FGoogleSignOutData`  
_L63-77_
- L66 _public function_ `FString ToDebugString() const` — @return a string that prints useful debug information about this response
- L74 _public member_ `EGoogleLoginResponse Response;` — Result of the sign in
- L76 _public member_ `FString ErrorStr;` — Error response, if any

#### Free symbols / members of external scopes

- L24 _function_ `inline const TCHAR* ToString(EGoogleLoginResponse Response)`
- L84 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGoogleSignInComplete, const FGoogleSignInData& );` — Delegate fired when Google sign in has completed @param SignInData
- L84 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGoogleSignInComplete, const FGoogleSignInData& );` — Delegate fired when Google sign in has completed @param SignInData
- L85 _typedef_ `typedef FOnGoogleSignInComplete::FDelegate FOnGoogleSignInCompleteDelegate;`
- L92 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGoogleSignOutComplete, const FGoogleSignOutData& );` — Delegate fired when Google sign out has completed @param SignOutData
- L92 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGoogleSignOutComplete, const FGoogleSignOutData& );` — Delegate fired when Google sign out has completed @param SignOutData
- L93 _typedef_ `typedef FOnGoogleSignOutComplete::FDelegate FOnGoogleSignOutCompleteDelegate;`

### `Plugins/Online/OnlineSubsystemGoogle/Source/Private/IOS/OnlineExternalUIInterfaceGoogleIOS.h` (Private)


#### class `FOnlineExternalUIGoogleIOS`  
`class FOnlineExternalUIGoogleIOS : public FOnlineExternalUIGoogleCommon`  
_L14-41_
- inherits: `FOnlineExternalUIGoogleCommon`
- desc: Implementation for the Google external UIs
- L33 _public function_ `virtual ~FOnlineExternalUIGoogleIOS()` — Destructor.
- L38 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;` — IOnlineExternalUI

#### Free symbols / members of external scopes

- L43 _typedef_ `typedef TSharedPtr<FOnlineExternalUIGoogle, ESPMode::ThreadSafe> FOnlineExternalUIGooglePtr;`

### `Plugins/Online/OnlineSubsystemGoogle/Source/Private/IOS/OnlineIdentityGoogle.h` (Private)


#### class `FUserOnlineAccountGoogle`  
`class FUserOnlineAccountGoogle : public FUserOnlineAccountGoogleCommon`  
_L18-30_
- inherits: `FUserOnlineAccountGoogleCommon`
- desc: iOS implementation of a Google user account
- L22 _public function_ `explicit FUserOnlineAccountGoogle(const FString& InUserId = FString(), const FAuthTokenGoogle& InAuthToken = FAuthTokenGoogle()) : FUserOnlineAccountGoogleCommon(InUserId, InAuthToken)`
- L27 _public function_ `virtual ~FUserOnlineAccountGoogle()`

#### class `FOnlineIdentityGoogle`  
`class FOnlineIdentityGoogle : public FOnlineIdentityGoogleCommon`  
_L35-92_
- inherits: `FOnlineIdentityGoogleCommon`
- desc: Google service implementation of the online identity interface
- L42 _public prototype_ `virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;`
- L43 _public prototype_ `virtual bool Logout(int32 LocalUserNum) override;`
- L47 _public prototype_ `FOnlineIdentityGoogle(FOnlineSubsystemGoogle* InSubsystem);`
- L52 _public prototype_ `virtual ~FOnlineIdentityGoogle();` — Destructor
- L54 _public prototype_ `bool Init();`
- L68 _public prototype_ `void Login(int32 LocalUserNum, const FAuthTokenGoogle& InToken, const FOnLoginCompleteDelegate& InCompletionDelegate);` — Login with an existing token @param LocalUserNum id of the local user initiating the request @param InToken exchange or refresh token already received from Google @param InCompletionDelegate delegate to fire when operation completes
- L71 _private prototype_ `void OnSignInComplete(const FGoogleSignInData& InSignInData);`
- L72 _private prototype_ `void OnSignOutComplete(const FGoogleSignOutData& InSignOutData);`
- L74 _private prototype_ `void OnAccessTokenLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UniqueId, const FString& Error);`
- L75 _private prototype_ `void OnLoginAttemptComplete(int32 LocalUserNum, const FString& ErrorStr);`
- L78 _private member_ `FGoogleHelper* GoogleHelper;` — ObjC helper for access to SDK methods and callbacks
- L81 _private member_ `TArray<FString> ScopeFields;` — Config based list of permission scopes to use when logging in
- L84 _private member_ `bool bAllowSilentSignIn;` — Is it allowed to try to refresh the tokens instead of full a login?
- L87 _private prototype_ `DECLARE_DELEGATE_TwoParams(FOnInternalLoginComplete, EGoogleLoginResponse , const FAuthTokenGoogle& );` — Delegate holder for all internal related login callbacks
- L88 _private member_ `FOnInternalLoginComplete LoginCompletionDelegate;`
- L90 _private prototype_ `DECLARE_DELEGATE_OneParam(FOnInternalLogoutComplete, EGoogleLoginResponse );` — Delegate holder for all internal related logout callbacks
- L91 _private member_ `FOnInternalLogoutComplete LogoutCompletionDelegate;`

#### Free symbols / members of external scopes

- L87 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnInternalLoginComplete, EGoogleLoginResponse , const FAuthTokenGoogle& );` — Delegate holder for all internal related login callbacks
- L90 _delegate_ `DECLARE_DELEGATE_OneParam(FOnInternalLogoutComplete, EGoogleLoginResponse );` — Delegate holder for all internal related logout callbacks
- L94 _typedef_ `typedef TSharedPtr<FOnlineIdentityGoogle, ESPMode::ThreadSafe> FOnlineIdentityGooglePtr;`

### `Plugins/Online/OnlineSubsystemGoogle/Source/Private/OnlineAccountGoogleCommon.h` (Private)


#### class `FUserOnlineAccountGoogleCommon`  
`class FUserOnlineAccountGoogleCommon : public FUserOnlineAccount, public FJsonSerializable`  
_L13-130_
- inherits: `FUserOnlineAccount,FJsonSerializable`
- desc: Info associated with an user account generated by this online service
- L21 _public prototype_ `virtual FUniqueNetIdRef GetUserId() const override;`
- L22 _public prototype_ `virtual FString GetRealName() const override;`
- L23 _public prototype_ `virtual FString GetDisplayName(const FString& Platform = FString()) const override;`
- L24 _public prototype_ `virtual bool GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L25 _public prototype_ `virtual bool SetUserAttribute(const FString& AttrName, const FString& AttrValue) override;`
- L29 _public prototype_ `virtual FString GetAccessToken() const override;`
- L30 _public prototype_ `virtual bool GetAuthAttribute(const FString& AttrName, FString& OutAttrValue) const override;`
- L34 _public function_ `explicit FUserOnlineAccountGoogleCommon(const FString& InUserId = FString(), const FAuthTokenGoogle& InAuthToken = FAuthTokenGoogle()) : UserIdPtr(FUniqueNetIdGoogle::Create(InUserId)) , UserId(InUserId) , AuthToken(InAuthToken)`
- L41 _public function_ `virtual ~FUserOnlineAccountGoogleCommon()`
- L51 _public prototype_ `bool Parse(const FAuthTokenGoogle& InAuthToken, const FString& InJsonStr);` — Parse Json profile request data into the user account @param InAuthToken previously associated auth token with this Json response @param InJsonStr a json payload from a /me request
- L59 _public prototype_ `bool Parse(const FAuthTokenGoogle& InAuthToken, TSharedPtr<FJsonObject> InJsonObject);` — Parse Json profile request data into the user account @param InAuthToken previously associated auth token with this Json response @param InJsonObject a json payload from a /me request
- L71 _protected function_ `inline bool GetAccountData(const FString& Key, FString& OutVal) const` — Get account data attribute @param Key account data entry key @param OutVal [out] value that was found @return true if entry was found
- L90 _protected function_ `inline bool SetAccountData(const FString& Key, const FString& Val)` — Set account data attribute @param Key account data entry key @param Val value that we want to set @return true if entry changed
- L102 _protected member_ `FUniqueNetIdRef UserIdPtr;` — User Id represented as a FUniqueNetId
- L104 _protected member_ `FString UserId;` — Id associated with the user account provided by the online service during registration
- L106 _protected member_ `FString RealName;` — Real name
- L108 _protected member_ `FString FirstName;` — First name
- L110 _protected member_ `FString LastName;` — Last name
- L112 _protected member_ `FAuthTokenGoogle AuthToken;` — Token which is provided to user once authenticated by the online service
- L114 _protected member_ `FJsonSerializableKeyValueMap AccountData;` — Any addition account data associated with the user
- L125 _private prototype_ `JSON_SERIALIZE_SIMPLECOPY(AccountData);`

### `Plugins/Online/OnlineSubsystemGoogle/Source/Private/OnlineExternalUIGoogleCommon.h` (Private)


#### class `FOnlineExternalUIGoogleCommon`  
`class FOnlineExternalUIGoogleCommon : public IOnlineExternalUI`  
_L15-55_
- inherits: `IOnlineExternalUI`
- desc: Implementation for the Google external UIs
- L31 _private member_ `FOnlineSubsystemGoogleCommon* GoogleSubsystem;` — Reference to the owning subsystem
- L38 _public function_ `virtual ~FOnlineExternalUIGoogleCommon()` — Destructor.
- L43 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;` — IOnlineExternalUI
- L44 _public function_ `virtual bool ShowAccountCreationUI(const int ControllerIndex, const FOnAccountCreationUIClosedDelegate& Delegate = FOnAccountCreationUIClosedDelegate()) override`
- L45 _public prototype_ `virtual bool ShowFriendsUI(int32 LocalUserNum) override;`
- L46 _public prototype_ `virtual bool ShowInviteUI(int32 LocalUserNum, FName SessionName = NAME_GameSession) override;`
- L47 _public prototype_ `virtual bool ShowAchievementsUI(int32 LocalUserNum) override;`
- L48 _public prototype_ `virtual bool ShowLeaderboardUI(const FString& LeaderboardName) override;`
- L49 _public prototype_ `virtual bool ShowWebURL(const FString& Url, const FShowWebUrlParams& ShowParams, const FOnShowWebUrlClosedDelegate& Delegate = FOnShowWebUrlClosedDelegate()) override;`
- L50 _public prototype_ `virtual bool CloseWebURL() override;`
- L51 _public prototype_ `virtual bool ShowProfileUI(const FUniqueNetId& Requestor, const FUniqueNetId& Requestee, const FOnProfileUIClosedDelegate& Delegate = FOnProfileUIClosedDelegate()) override;`
- L52 _public prototype_ `virtual bool ShowAccountUpgradeUI(const FUniqueNetId& UniqueId) override;`
- L53 _public prototype_ `virtual bool ShowStoreUI(int32 LocalUserNum, const FShowStoreParams& ShowParams, const FOnShowStoreUIClosedDelegate& Delegate = FOnShowStoreUIClosedDelegate()) override;`
- L54 _public prototype_ `virtual bool ShowSendMessageUI(int32 LocalUserNum, const FShowSendMessageParams& ShowParams, const FOnShowSendMessageUIClosedDelegate& Delegate = FOnShowSendMessageUIClosedDelegate()) override;`

#### Free symbols / members of external scopes

- L57 _typedef_ `typedef TSharedPtr<FOnlineExternalUIGoogleCommon, ESPMode::ThreadSafe> FOnlineExternalUIGoogleCommonPtr;`

### `Plugins/Online/OnlineSubsystemGoogle/Source/Private/OnlineIdentityGoogleCommon.h` (Private)


#### class `FOnlineIdentityGoogleCommon`  
`class FOnlineIdentityGoogleCommon : public IOnlineIdentity`  
_L38-121_
- inherits: `IOnlineIdentity`
- desc: Google service implementation of the online identity interface
- L45 _protected member_ `FOnlineSubsystemGoogle* GoogleSubsystem;` — Parent subsystem
- L47 _protected member_ `FGoogleOpenIDConfiguration Endpoints;` — Endpoint configurations retrieved from Google discovery service
- L49 _protected member_ `FUserOnlineAccountGoogleMap UserAccounts;` — Users that have been registered/authenticated
- L51 _protected member_ `TMap<int32, FUniqueNetIdPtr > UserIds;` — Ids mapped to locally registered users
- L53 _protected member_ `bool bAccessTokenAvailableToPlatform = true;` — Platform can know the client access token
- L55 _protected typedef_ `typedef TFunction<void(bool)> PendingLoginRequestCb;`
- L60 _public prototype_ `virtual bool AutoLogin(int32 LocalUserNum) override;` — IOnlineIdentity
- L61 _public prototype_ `virtual TSharedPtr<FUserOnlineAccount> GetUserAccount(const FUniqueNetId& UserId) const override;`
- L62 _public prototype_ `virtual TArray<TSharedPtr<FUserOnlineAccount> > GetAllUserAccounts() const override;`
- L63 _public prototype_ `virtual FUniqueNetIdPtr GetUniquePlayerId(int32 LocalUserNum) const override;`
- L64 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(uint8* Bytes, int32 Size) override;`
- L65 _public prototype_ `virtual FUniqueNetIdPtr CreateUniquePlayerId(const FString& Str) override;`
- L66 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(int32 LocalUserNum) const override;`
- L67 _public prototype_ `virtual ELoginStatus::Type GetLoginStatus(const FUniqueNetId& UserId) const override;`
- L68 _public prototype_ `virtual FString GetPlayerNickname(int32 LocalUserNum) const override;`
- L69 _public prototype_ `virtual FString GetPlayerNickname(const FUniqueNetId& UserId) const override;`
- L70 _public prototype_ `virtual FString GetAuthToken(int32 LocalUserNum) const override;`
- L71 _public prototype_ `virtual void GetUserPrivilege(const FUniqueNetId& UserId, EUserPrivileges::Type Privilege, const FOnGetUserPrivilegeCompleteDelegate& Delegate, EShowPrivilegeResolveUI ShowResolveUI=EShowPrivilegeResolveUI::Default) override;`
- L72 _public prototype_ `virtual FPlatformUserId GetPlatformUserIdFromUniqueNetId(const FUniqueNetId& UniqueNetId) const override;`
- L73 _public prototype_ `virtual FString GetAuthType() const override;`
- L74 _public prototype_ `virtual void RevokeAuthToken(const FUniqueNetId& UserId, const FOnRevokeAuthTokenCompleteDelegate& Delegate) override;`
- L78 _public prototype_ `FOnlineIdentityGoogleCommon(FOnlineSubsystemGoogle* InSubsystem);`
- L83 _public function_ `virtual ~FOnlineIdentityGoogleCommon()` — Destructor
- L99 _public prototype_ `void ProfileRequest(int32 LocalUserNum, const FAuthTokenGoogle& InAuthToken, FOnProfileRequestComplete& InCompletionDelegate);` — Retrieve the profile for a given user and access token @param LocalUserNum the controller number of the associated user @param AccessToken associated access token to make the request @param InCompletionDelegate delegate to fire when request is completed
- L107 _public prototype_ `void RetrieveDiscoveryDocument(PendingLoginRequestCb&& LoginCb);` — Retrieve auth endpoints from Google discovery service @param LoginCb the login function to call after this request completes
- L113 _protected prototype_ `virtual void DiscoveryRequest_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, PendingLoginRequestCb LoginCb);` — Delegate fired when the discover service request has completed
- L120 _private prototype_ `void MeUser_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, int32 InLocalUserNum, FAuthTokenGoogle InAuthToken, FOnProfileRequestComplete InCompletionDelegate);` — Delegate called when a user /me request from Google is complete

#### Free symbols / members of external scopes

- L15 _macro_ `#define GOOGLE_PERM_PUBLIC_PROFILE "https://www.googleapis.com/auth/userinfo.profile"` — Google scope fields: https://developers.google.com/identity/protocols/googlescopes email profile https://www.googleapis.com/auth/userinfo.email https://www.googleapis.com/auth/userinfo.profile
- L20 _macro_ `#define AUTH_TYPE_GOOGLE TEXT("google")`
- L21 _macro_ `#define GOOGLE_AUTH_EXPIRED_CREDS TEXT("com.epicgames.google.oauth.expiredcreds")`
- L30 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnProfileRequestComplete, int32 , bool , const FString& );` — Delegate fired after a Google profile request has been completed @param LocalUserNum the controller number of the associated user @param bWasSuccessful was the request successful @param ErrorStr error associated with the request
- L30 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnProfileRequestComplete, int32 , bool , const FString& );` — Delegate fired after a Google profile request has been completed @param LocalUserNum the controller number of the associated user @param bWasSuccessful was the request successful @param ErrorStr error associated with the request
- L33 _typedef_ `typedef TMap<FString, TSharedRef<FUserOnlineAccountGoogleCommon> > FUserOnlineAccountGoogleMap;` — Mapping from user id to internal online account info (only one per user)
- L123 _typedef_ `typedef TSharedPtr<FOnlineIdentityGoogleCommon, ESPMode::ThreadSafe> FOnlineIdentityGoogleCommonPtr;`

### `Plugins/Online/OnlineSubsystemGoogle/Source/Private/OnlineSubsystemGooglePrivate.h` (Private)


#### Free symbols / members of external scopes

- L15 _macro_ `#define ONLINE_LOG_PREFIX TEXT("Google: ")`

### `Plugins/Online/OnlineSubsystemGoogle/Source/Private/OnlineSubsystemGoogleTypes.h` (Private)


#### enum `EGoogleAuthTokenType`  
`enum class EGoogleAuthTokenType : uint8`  
_L20-28_
- desc: Types of supported auth tokens
- L23 _public enumerator_ `ExchangeToken` — Simple single use token meant to be converted to an access token
- L25 _public enumerator_ `RefreshToken` — Refresh token meant to be fully converted to an access token
- L27 _public enumerator_ `AccessToken` — Allows for access to Google APIs using verified user account credentials

#### class `FJsonWebTokenGoogle`  
`class FJsonWebTokenGoogle`  
_L30-114_
- L42 _public prototype_ `bool Parse(const FString& InJWTStr);` — Parse a Google JWT into its constituent parts @param InJWTStr JWT id token representations @return true if parsing was successful, false otherwise
- L111 _private member_ `FHeader Header;` — JWT header
- L113 _private member_ `FPayload Payload;` — JWT payload

#### class `FJsonWebTokenGoogle::FHeader`  
`class FHeader : public FJsonSerializable`  
_L46-58_
- inherits: `FJsonSerializable`
- L51 _public member_ `FString Alg;` — Algorithm used to sign the token
- L53 _public member_ `FString Kid;` — Key Id

#### class `FJsonWebTokenGoogle::FPayload`  
`class FPayload : public FJsonSerializable`  
_L60-108_
- inherits: `FJsonSerializable`
- L66 _public member_ `FString Sub;` — Subscriber
- L68 _public member_ `FString FirstName;` — User first name
- L70 _public member_ `FString LastName;` — User last name
- L72 _public member_ `FString RealName;` — User full name
- L74 _public member_ `FString ISS;` — Issuer
- L76 _public member_ `double IAT;` — Time of token grant
- L78 _public member_ `double EXP;` — Time of token expiration
- L79 _public member_ `FString ATHash;`
- L81 _public member_ `FString Aud;` — Audience
- L83 _public member_ `bool bEmailVerified;` — Is the email address verified
- L84 _public member_ `FString AZP;`
- L86 _public member_ `FString Email;` — User email address
- L88 _public member_ `FString Picture;` — User profile picture
- L90 _public member_ `FString Locale;` — User locale

#### enum `EGoogleExchangeToken`  
`enum EGoogleExchangeToken : uint8`  
_L116-116_
- L116 _public enumerator_ `enum EGoogleExchangeToken : uint8 { GoogleExchangeToken }; enum EGoogleRefreshToken : uint8 { GoogleRefreshToken }; /** * Google auth token representation`

#### enum `EGoogleRefreshToken`  
`enum EGoogleRefreshToken : uint8`  
_L117-117_
- L117 _public enumerator_ `enum EGoogleRefreshToken : uint8 { GoogleRefreshToken }; /** * Google auth token representation`

#### class `FAuthTokenGoogle`  
`class FAuthTokenGoogle : public FJsonSerializable`  
_L122-259_
- inherits: `FJsonSerializable`
- desc: Google auth token representation, both exchange and access tokens
- L127 _public function_ `FAuthTokenGoogle() : AuthType(EGoogleAuthTokenType::ExchangeToken) , ExpiresIn(0) , ExpiresInUTC(0)`
- L134 _public function_ `explicit FAuthTokenGoogle(const FString& InExchangeToken, EGoogleExchangeToken) : AuthType(EGoogleAuthTokenType::ExchangeToken) , AccessToken(InExchangeToken) , ExpiresIn(0) , ExpiresInUTC(0)`
- L142 _public function_ `explicit FAuthTokenGoogle(const FString& InRefreshToken, EGoogleRefreshToken) : AuthType(EGoogleAuthTokenType::RefreshToken) , ExpiresIn(0) , RefreshToken(InRefreshToken) , ExpiresInUTC(0)`
- L150 _public prototype_ `FAuthTokenGoogle(FAuthTokenGoogle&&) = default;`
- L151 _public prototype_ `FAuthTokenGoogle(const FAuthTokenGoogle&) = default;`
- L152 _public prototype_ `FAuthTokenGoogle& operator=(FAuthTokenGoogle&&) = default;`
- L153 _public prototype_ `FAuthTokenGoogle& operator=(const FAuthTokenGoogle&) = default;`
- L162 _public prototype_ `bool Parse(const FString& InJsonStr);` — Parse a Google json auth response into an access/refresh token @param InJsonStr json response containing the token information @return true if parsing was successful, false otherwise
- L171 _public prototype_ `bool Parse(TSharedPtr<FJsonObject> InJsonObject);` — Parse a Google json auth response into an access/refresh token @param InJsonObject json object containing the token information @return true if parsing was successful, false otherwise
- L181 _public prototype_ `bool Parse(const FString& InJsonStr, const FAuthTokenGoogle& InOldAuthToken);` — Parse a Google json auth refresh response into an access/refresh token @param InJsonStr json response containing the token information @param InOldAuthToken previous auth token with refresh token information @return true if parsing was successful, false otherwise
- L184 _public function_ `bool IsValid() const` — @return true if this auth token is valid, false otherwise
- L201 _public function_ `bool IsExpired() const` — @return true if the token is expired
- L212 _public function_ `inline bool GetAuthData(const FString& Key, FString& OutVal) const`
- L223 _public function_ `inline void AddAuthData(FString Key, const FString& Value)`
- L229 _public member_ `EGoogleAuthTokenType AuthType;` — Type of auth this token represents
- L231 _public member_ `FString AccessToken;` — Access or exchange token
- L233 _public member_ `FString TokenType;` — Type of token (valid for AccessToken only)
- L235 _public member_ `double ExpiresIn;` — Number of seconds until this token expires at time of receipt
- L237 _public member_ `FString RefreshToken;` — Refresh token for generating new AccessTokens
- L239 _public member_ `FString IdToken;` — Id token in JWT form
- L241 _public member_ `FJsonWebTokenGoogle IdTokenJWT;` — Parsed IdToken
- L243 _public member_ `FDateTime ExpiresInUTC;` — Absolute time, in UTC, when this token will expire
- L247 _private prototype_ `void AddAuthAttributes(const TSharedPtr<FJsonObject>& JsonUser);`
- L250 _private member_ `FJsonSerializableKeyValueMap AuthData;` — Any addition auth data associated with the token

#### class `FGoogleOpenIDConfiguration`  
`class FGoogleOpenIDConfiguration : public FJsonSerializable`  
_L264-324_
- inherits: `FJsonSerializable`
- desc: Container for configuration info related to all Google API services
- L272 _public function_ `FGoogleOpenIDConfiguration() : bInitialized(false) , AuthEndpoint(TEXT("https:` — Constructor
- L282 _public function_ `bool IsValid() const` — @return true if this data is valid, false otherwise
- L289 _public function_ `bool Parse(const FString& InJsonStr)` — Parse a Json response from Google into a this data structure @return true if parsing was successful, false otherwise
- L300 _public member_ `bool bInitialized;` — Has this data been setup
- L302 _public member_ `FString Issuer;` — Issuer of the configuration information
- L304 _public member_ `FString AuthEndpoint;` — Authentication endpoint for login
- L306 _public member_ `FString TokenEndpoint;` — Token exchange endpoint
- L308 _public member_ `FString UserInfoEndpoint;` — User profile request endpoint
- L310 _public member_ `FString RevocationEndpoint;` — Auth revocation endpoint
- L312 _public member_ `FString JWKSURI;` — JWT Cert endpoint

#### class `FErrorGoogle`  
`class FErrorGoogle : public FJsonSerializable`  
_L329-352_
- inherits: `FJsonSerializable`
- desc: Google error from JSON payload
- L337 _public function_ `FErrorGoogle()` — Constructor
- L342 _public member_ `FString Error;` — Error type
- L344 _public member_ `FString Error_Description;` — Description of error
- L346 _public function_ `FString ToDebugString() const`

#### Free symbols / members of external scopes

- L15 _prototype_ `TEMP_UNIQUENETIDSTRING_SUBCLASS(FUniqueNetIdGoogle, GOOGLE_SUBSYSTEM);` — from OnlineSubsystemTypes.h

### `Plugins/Online/OnlineSubsystemGoogle/Source/Private/Rest/OnlineExternalUIInterfaceGoogleRest.h` (Private)


#### class `FOnlineExternalUIGoogle`  
`class FOnlineExternalUIGoogle : public FOnlineExternalUIGoogleCommon`  
_L16-71_
- inherits: `FOnlineExternalUIGoogleCommon`
- desc: Implementation for the Google external UIs
- L35 _public function_ `virtual ~FOnlineExternalUIGoogle()` — Destructor.
- L40 _public prototype_ `virtual bool ShowLoginUI(const int ControllerIndex, bool bShowOnlineOnly, bool bShowSkipButton, const FOnLoginUIClosedDelegate& Delegate = FOnLoginUIClosedDelegate()) override;` — IOnlineExternalUI
- L50 _private prototype_ `FLoginFlowResult OnLoginRedirectURL(const FString& RedirectURL);` — Delegate fired when redirect URLs from the login flow are passed back for parsing We are looking for the success or error completion state from Google to grab the access token or complete the flow @param RedirectURL URL received from the login flow for parsing
- L59 _private prototype_ `void OnExternalLoginFlowComplete(const FLoginFlowResult& Result, int ControllerIndex, const FOnLoginUIClosedDelegate Delegate);` — Delegate fired when the login flow is complete @param Result final result of the login flow action @param ControllerIndex index of the local user initiating the request @param Delegate UI closed delegate to fire, completing the external UIs part in the login process
- L70 _private prototype_ `void OnAccessTokenLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error, FOnLoginUIClosedDelegate Delegate);` — Delegate fired when the Google identity interface has completed login using the token retrieved from the login flow @param LocalUserNum index of the local user initiating the request @param bWasSuccessful was the login call successful @param UserId user id of the logged in user, or null if login failed @param Error error string if applicable @param Delegate UI closed delegate to fire, completing the external UIs part in the login process

#### Free symbols / members of external scopes

- L73 _typedef_ `typedef TSharedPtr<FOnlineExternalUIGoogle, ESPMode::ThreadSafe> FOnlineExternalUIGooglePtr;`

### `Plugins/Online/OnlineSubsystemGoogle/Source/Private/Rest/OnlineIdentityGoogleRest.h` (Private)


#### class `FUserOnlineAccountGoogle`  
`class FUserOnlineAccountGoogle : public FUserOnlineAccountGoogleCommon`  
_L36-48_
- inherits: `FUserOnlineAccountGoogleCommon`
- desc: Windows implementation of a Google user account
- L40 _public function_ `explicit FUserOnlineAccountGoogle(const FString& InUserId = FString(), const FAuthTokenGoogle& InAuthToken = FAuthTokenGoogle()) : FUserOnlineAccountGoogleCommon(InUserId, InAuthToken)`
- L45 _public function_ `virtual ~FUserOnlineAccountGoogle()`

#### struct `FGoogleLoginURL`  
`struct FGoogleLoginURL`  
_L53-104_
- desc: Contains URL details for Windows Google interaction
- L56 _public member_ `FString LoginUrl;` — The Google exchange token auth endpoint
- L58 _public member_ `FString LoginRedirectUrl;` — The redirect url for Google to redirect to upon completion
- L60 _public member_ `int32 RedirectPort = 9000;` — Port to append to the LoginRedirectURL when communicating with Google auth services
- L62 _public member_ `FString ClientId;` — The client id given to us by Google
- L64 _public member_ `TArray<FString> ScopeFields;` — Config based list of permission scopes to use when logging in
- L66 _public member_ `FString State;` — A value used to verify our response came from our server
- L68 _public member_ `bool bRequestOfflineAccess = false;` — Should request Offline Access. Refresh token is only received on first authorization
- L70 _public function_ `bool IsValid() const`
- L76 _public function_ `FString GenerateNonce()`
- L83 _public function_ `FString GetRedirectURL() const`
- L89 _public function_ `FString GetURL() const`

#### class `FOnlineIdentityGoogle`  
`class FOnlineIdentityGoogle : public FOnlineIdentityGoogleCommon`  
_L109-208_
- inherits: `FOnlineIdentityGoogleCommon`
- desc: Google service implementation of the online identity interface
- L113 _private member_ `FString ClientSecret;` — Client secret retrieved from Google Dashboard
- L115 _private member_ `FGoogleLoginURL LoginURLDetails;` — Const details about communicating with Google API
- L117 _private member_ `bool bHasLoginOutstanding;` — Whether we have a registration in flight or not
- L120 _private member_ `TArray<FString> LoginDomains;` — Domains used for login, for cookie management
- L125 _public prototype_ `virtual bool Login(int32 LocalUserNum, const FOnlineAccountCredentials& AccountCredentials) override;`
- L126 _public prototype_ `virtual bool Logout(int32 LocalUserNum) override;`
- L130 _public prototype_ `FOnlineIdentityGoogle(FOnlineSubsystemGoogle* InSubsystem);`
- L135 _public function_ `virtual ~FOnlineIdentityGoogle()` — Destructor
- L152 _public prototype_ `void Login(int32 LocalUserNum, const FAuthTokenGoogle& InToken, const FOnLoginCompleteDelegate& InCompletionDelegate);` — Login with an existing token If an exchange token has been given, it will convert to access/refresh before continuing login If an older access token has been given, it will refresh the token before continuing login @param LocalUserNum id of the local user initiating the request @param InToken exchange or refresh token already received from Google @param InCompletionDelegate delegate to fire when operation completes
- L155 _public function_ `const FGoogleLoginURL& GetLoginURLDetails() const` — @return the login configuration details
- L164 _public prototype_ `void ExchangeCode(int32 LocalUserNum, const FAuthTokenGoogle& InExchangeToken, FOnExchangeRequestComplete& InCompletionDelegate);` — Exchange the Google auth token for actual user access/refresh tokens @param LocalUserNum id of the local user initiating the request @param InExchangeToken token received from user consent login flow @param InCompletionDelegate delegate to fire when operation completes
- L173 _public prototype_ `void RefreshAuth(int32 LocalUserNum, const FAuthTokenGoogle& InAuthToken, FOnRefreshAuthRequestComplete& InCompletionDelegate);` — Refresh an existing Google auth token @param LocalUserNum id of the local user initiating the request @param InAuthToken existing valid auth token with refresh token included @param InCompletionDelegate delegate to fire when operation completes
- L178 _private prototype_ `virtual void DiscoveryRequest_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, PendingLoginRequestCb LoginCb) override;` — FOnlineIdentityGoogleCommon
- L181 _private prototype_ `void OnLoginAttemptComplete(int32 LocalUserNum, const FString& ErrorStr);`
- L186 _private prototype_ `void ExchangeRequest_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, int32 InLocalUserNum, FAuthTokenGoogle InExchangeToken, FOnExchangeRequestComplete InCompletionDelegate);` — Delegate called when a token exchange has completed
- L191 _private prototype_ `void RefreshAuthRequest_HttpRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded, int32 InLocalUserNum, FAuthTokenGoogle InOldAuthToken, FOnRefreshAuthRequestComplete InCompletionDelegate);` — Delegate called when a refresh auth request has completed
- L201 _private prototype_ `void OnAccessTokenLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);` — Delegate fired when the internal call to Login() with AccessToken is specified @param LocalUserNum index of the local user initiating the request @param bWasSuccessful was the login call successful @param UserId user id of the logged in user, or null if login failed @param Error error string if applicable
- L206 _private prototype_ `void OnExternalUILoginComplete(FUniqueNetIdPtr UniqueId, const int ControllerIndex, const FOnlineError& Error);` — Delegate fired when the call to ShowLoginUI completes

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_FourParams(FOnExchangeRequestComplete, int32 , bool , const FAuthTokenGoogle& , const FString& );` — Delegate fired after an exchange token to access/refresh token request has been completed @param LocalUserNum the controller number of the associated user @param bWasSuccessful was the request successful @param AuthToken the new auth token returned from the exchange @param ErrorStr error associated with the request
- L23 _prototype_ `DECLARE_DELEGATE_FourParams(FOnExchangeRequestComplete, int32 , bool , const FAuthTokenGoogle& , const FString& );` — Delegate fired after an exchange token to access/refresh token request has been completed @param LocalUserNum the controller number of the associated user @param bWasSuccessful was the request successful @param AuthToken the new auth token returned from the exchange @param ErrorStr error associated with the request
- L33 _delegate_ `DECLARE_DELEGATE_FourParams(FOnRefreshAuthRequestComplete, int32 , bool , const FAuthTokenGoogle& , const FString& );` — Delegate fired after a refresh auth from existing token request has been completed @param LocalUserNum the controller number of the associated user @param bWasSuccessful was the request successful @param AuthToken the new auth token returned from the refresh @param ErrorStr error associated with the request
- L33 _prototype_ `DECLARE_DELEGATE_FourParams(FOnRefreshAuthRequestComplete, int32 , bool , const FAuthTokenGoogle& , const FString& );` — Delegate fired after a refresh auth from existing token request has been completed @param LocalUserNum the controller number of the associated user @param bWasSuccessful was the request successful @param AuthToken the new auth token returned from the refresh @param ErrorStr error associated with the request
- L210 _typedef_ `typedef TSharedPtr<FOnlineIdentityGoogle, ESPMode::ThreadSafe> FOnlineIdentityGooglePtr;`

### `Plugins/Online/OnlineSubsystemGoogle/Source/Public/OnlineSubsystemGoogle.h` (Public)


#### class `FOnlineSubsystemGoogle`  
`class FOnlineSubsystemGoogle : public FOnlineSubsystemGoogleCommon`  
_L18-40_
- inherits: `FOnlineSubsystemGoogleCommon`
- desc: OnlineSubsystemGoogle - Implementation of the online subsystem for Google services
- L24 _public prototype_ `virtual bool Init() override;` — FOnlineSubsystemGoogleCommon Interface
- L25 _public prototype_ `virtual bool Shutdown() override;`
- L32 _public prototype_ `virtual ~FOnlineSubsystemGoogle();` — Destructor
- L38 _public prototype_ `explicit FOnlineSubsystemGoogle(FName InInstanceName);`

#### Free symbols / members of external scopes

- L9 _typedef_ `typedef TSharedPtr<class FOnlineIdentityGoogle, ESPMode::ThreadSafe> FOnlineIdentityGooglePtr;` — Forward declarations of all interface classes
- L10 _typedef_ `typedef TSharedPtr<class FOnlineFriendsGoogle, ESPMode::ThreadSafe> FOnlineFriendsGooglePtr;`
- L11 _typedef_ `typedef TSharedPtr<class FOnlineSharingGoogle, ESPMode::ThreadSafe> FOnlineSharingGooglePtr;`
- L12 _typedef_ `typedef TSharedPtr<class FOnlineUserGoogle, ESPMode::ThreadSafe> FOnlineUserGooglePtr;`
- L13 _typedef_ `typedef TSharedPtr<class FOnlineExternalUIGoogle, ESPMode::ThreadSafe> FOnlineExternalUIGooglePtr;`
- L42 _typedef_ `typedef TSharedPtr<FOnlineSubsystemGoogle, ESPMode::ThreadSafe> FOnlineSubsystemGooglePtr;`

### `Plugins/Online/OnlineSubsystemGoogle/Source/Public/OnlineSubsystemGoogleCommon.h` (Public)


#### class `FGoogleAuthConfig`  
`class FGoogleAuthConfig`  
_L17-28_
- desc: Configuration structure for overriding auth id parameters required by Google
- L20 _public function_ `FGoogleAuthConfig()`
- L27 _public member_ `FString Backend;` — Backend Name Added to [OnlineSubsystemGoogle <Backend>] to search the ini for specific overrides

#### class `FOnlineSubsystemGoogleCommon`  
`class FOnlineSubsystemGoogleCommon : public FOnlineSubsystemImpl`  
_L33-124_
- inherits: `FOnlineSubsystemImpl`
- desc: OnlineSubsystemGoogleCommon - Implementation of the online subsystem for Google services
- L39 _public prototype_ `virtual IOnlineSessionPtr GetSessionInterface() const override;` — IOnlineSubsystem Interface
- L40 _public prototype_ `virtual IOnlineFriendsPtr GetFriendsInterface() const override;`
- L41 _public prototype_ `virtual IOnlinePartyPtr GetPartyInterface() const override;`
- L42 _public prototype_ `virtual IOnlineGroupsPtr GetGroupsInterface() const override;`
- L43 _public prototype_ `virtual IOnlineSharedCloudPtr GetSharedCloudInterface() const override;`
- L44 _public prototype_ `virtual IOnlineUserCloudPtr GetUserCloudInterface() const override;`
- L45 _public prototype_ `virtual IOnlineLeaderboardsPtr GetLeaderboardsInterface() const override;`
- L46 _public prototype_ `virtual IOnlineVoicePtr GetVoiceInterface() const override;`
- L47 _public prototype_ `virtual IOnlineExternalUIPtr GetExternalUIInterface() const override;`
- L48 _public prototype_ `virtual IOnlineTimePtr GetTimeInterface() const override;`
- L49 _public prototype_ `virtual IOnlineIdentityPtr GetIdentityInterface() const override;`
- L50 _public prototype_ `virtual IOnlineTitleFilePtr GetTitleFileInterface() const override;`
- L51 _public prototype_ `virtual IOnlineEntitlementsPtr GetEntitlementsInterface() const override;`
- L52 _public function_ `virtual IOnlineStoreV2Ptr GetStoreV2Interface() const override`
- L53 _public function_ `virtual IOnlinePurchasePtr GetPurchaseInterface() const override`
- L54 _public prototype_ `virtual IOnlineEventsPtr GetEventsInterface() const override;`
- L55 _public prototype_ `virtual IOnlineAchievementsPtr GetAchievementsInterface() const override;`
- L56 _public prototype_ `virtual IOnlineSharingPtr GetSharingInterface() const override;`
- L57 _public prototype_ `virtual IOnlineUserPtr GetUserInterface() const override;`
- L58 _public prototype_ `virtual IOnlineMessagePtr GetMessageInterface() const override;`
- L59 _public prototype_ `virtual IOnlinePresencePtr GetPresenceInterface() const override;`
- L60 _public prototype_ `virtual IOnlineChatPtr GetChatInterface() const override;`
- L61 _public prototype_ `virtual IOnlineStatsPtr GetStatsInterface() const override;`
- L62 _public prototype_ `virtual IOnlineTurnBasedPtr GetTurnBasedInterface() const override;`
- L63 _public prototype_ `virtual IOnlineTournamentPtr GetTournamentInterface() const override;`
- L64 _public prototype_ `virtual FText GetOnlineServiceName() const override;`
- L65 _public prototype_ `virtual bool Init() override;`
- L66 _public prototype_ `virtual bool Shutdown() override;`
- L67 _public prototype_ `virtual FString GetAppId() const override;`
- L68 _public prototype_ `virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L72 _public prototype_ `virtual bool Tick(float DeltaTime) override;`
- L79 _public prototype_ `virtual ~FOnlineSubsystemGoogleCommon();` — Destructor
- L87 _public prototype_ `DECLARE_DELEGATE_TwoParams(FGoogleConfigurationDelegate, const FString& , FGoogleAuthConfig& );` — Delegate fired at initialization allowing the application to override the configuration parameters @param ConfigOverride unused @param OutConfig config parameters needed to be filled in in order to override the default engine ini settings
- L88 _public prototype_ `static FOnlineSubsystemGoogleCommon::FGoogleConfigurationDelegate& GetConfigurationDelegate();`
- L94 _public prototype_ `FOnlineSubsystemGoogleCommon(FName InInstanceName);`
- L97 _public function_ `FString GetClientId() const` — @return the backend server client id
- L100 _public function_ `FString GetServerClientId() const` — @return the backend server client id
- L105 _protected member_ `FString ClientId;` — The client id given to us by Google Dashboard
- L108 _protected member_ `FString ServerClientId;` — Server client id that this client will be engaging with
- L111 _protected member_ `bool bPlatformRequiresClientId;` — Does the implementation need a Client Id configured
- L114 _protected member_ `bool bPlatformAllowsClientIdOverride;` — Does the implementation need a Client Id configured
- L117 _protected member_ `bool bPlatformRequiresServerClientId;` — Does the implementation need a Server Client Id configured
- L120 _protected member_ `FOnlineIdentityGoogleCommonPtr GoogleIdentity;` — Google implementation of identity interface
- L123 _protected member_ `FOnlineExternalUIGoogleCommonPtr GoogleExternalUI;` — Google implementation of the external ui

#### Free symbols / members of external scopes

- L11 _typedef_ `typedef TSharedPtr<class FOnlineIdentityGoogleCommon, ESPMode::ThreadSafe> FOnlineIdentityGoogleCommonPtr;` — Forward declarations of all interface classes
- L12 _typedef_ `typedef TSharedPtr<class FOnlineExternalUIGoogleCommon, ESPMode::ThreadSafe> FOnlineExternalUIGoogleCommonPtr;`
- L87 _delegate_ `DECLARE_DELEGATE_TwoParams(FGoogleConfigurationDelegate, const FString& , FGoogleAuthConfig& );` — Delegate fired at initialization allowing the application to override the configuration parameters @param ConfigOverride unused @param OutConfig config parameters needed to be filled in in order to override the default engine ini settings
- L126 _typedef_ `typedef TSharedPtr<FOnlineSubsystemGoogleCommon, ESPMode::ThreadSafe> FOnlineSubsystemGoogleCommonPtr;`

### `Plugins/Online/OnlineSubsystemGoogle/Source/Public/OnlineSubsystemGoogleModule.h` (Public)


#### class `FOnlineSubsystemGoogleModule`  
`class FOnlineSubsystemGoogleModule : public IModuleInterface`  
_L13-49_
- inherits: `IModuleInterface`
- desc: Online subsystem module class (Google Implementation) Code related to the loading and handling of the Google module.
- L18 _private member_ `class FOnlineFactoryGoogle* GoogleFactory;` — Class responsible for creating instance(s) of the subsystem
- L24 _public prototype_ `virtual void StartupModule() override;`
- L25 _public prototype_ `virtual void ShutdownModule() override;`
- L26 _public function_ `virtual bool SupportsDynamicReloading() override`
- L30 _public function_ `virtual bool SupportsAutomaticShutdown() override`
- L40 _public function_ `FOnlineSubsystemGoogleModule() : GoogleFactory(nullptr)` — Constructor
- L47 _public function_ `virtual ~FOnlineSubsystemGoogleModule()` — Destructor

### `Plugins/Online/OnlineSubsystemGoogle/Source/Public/OnlineSubsystemGooglePackage.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define PACKAGE_SCOPE public`
- L12 _macro_ `#define PACKAGE_SCOPE protected`
