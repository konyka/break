# Plugins / OnlineServicesInterface

- module root: `Plugins/Online/OnlineServices/Source/OnlineServicesInterface`
- headers: 32; symbols: 2202
- symbol kinds: class=40, delegate=2, enum=25, enumerator=110, externvar=31, function=133, macro=23, member=738, namespace=216, prototype=378, struct=444, typedef=59, variable=3
- PrivateDependencyModuleNames: Core
- PublicDependencyModuleNames: CoreOnline, OnlineBase

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/Achievements.h` (Public)


#### struct `UE::Online::FQueryAchievementDefinitions`  
`struct FQueryAchievementDefinitions`  
_L16-29_
- L18 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FQueryAchievementDefinitions::Params`  
`struct Params`  
_L20-24_
- L23 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation

#### struct `UE::Online::FQueryAchievementDefinitions::Result`  
`struct Result`  
_L26-28_

#### struct `UE::Online::FGetAchievementIds`  
`struct FGetAchievementIds`  
_L31-46_
- L33 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetAchievementIds::Params`  
`struct Params`  
_L35-39_
- L38 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation

#### struct `UE::Online::FGetAchievementIds::Result`  
`struct Result`  
_L41-45_
- L44 _public member_ `TArray<FString> AchievementIds;` — Available achievements

#### struct `UE::Online::FAchievementStatDefinition`  
`struct FAchievementStatDefinition`  
_L48-54_
- L51 _public member_ `FString StatId;` — Unique Id of the stat
- L53 _public member_ `uint32 UnlockThreshold = 0;` — Threshold value a user must meet for the achievement to auto unlock

#### struct `UE::Online::FAchievementDefinition`  
`struct FAchievementDefinition`  
_L58-80_
- L61 _public member_ `FString AchievementId;` — Unique Id for this achievement
- L63 _public member_ `FText UnlockedDisplayName;` — Localized display name of this achievement, once unlocked
- L65 _public member_ `FText UnlockedDescription;` — Localized description of this achievement, once unlocked
- L67 _public member_ `FText LockedDisplayName;` — Localized display name of this achievement, while locked
- L69 _public member_ `FText LockedDescription;` — Localized description of this achievement, while locked
- L71 _public member_ `FText FlavorText;` — Localized flavor text
- L73 _public member_ `FString UnlockedIconUrl;` — URL of the icon for this achievement, once unlocked
- L75 _public member_ `FString LockedIconUrl;` — URL of the icon for this achievement, while locked
- L77 _public member_ `bool bIsHidden = false;` — Is this achievement "hidden" until unlocked
- L79 _public member_ `TArray<FAchievementStatDefinition> StatDefinitions;` — The stats that relate to this achievement

#### struct `UE::Online::FGetAchievementDefinition`  
`struct FGetAchievementDefinition`  
_L84-101_
- L86 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetAchievementDefinition::Params`  
`struct Params`  
_L88-94_
- L91 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation
- L93 _public member_ `FString AchievementId;` — Achievement to get definition of

#### struct `UE::Online::FGetAchievementDefinition::Result`  
`struct Result`  
_L96-100_
- L99 _public member_ `FAchievementDefinition AchievementDefinition;` — Definition of the requested achievement

#### struct `UE::Online::FQueryAchievementStates`  
`struct FQueryAchievementStates`  
_L103-116_
- L105 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FQueryAchievementStates::Params`  
`struct Params`  
_L107-111_
- L110 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation

#### struct `UE::Online::FQueryAchievementStates::Result`  
`struct Result`  
_L113-115_

#### struct `UE::Online::FAchievementState`  
`struct FAchievementState`  
_L118-126_
- L121 _public member_ `FString AchievementId;` — Achievement that this state relates to
- L123 _public member_ `float Progress = 0.0f;` — Progress towards unlocking this achievement, as a percentage in the range [0.0, 1.0]. A value of 1.0 means the achievement is unlocked
- L125 _public member_ `FDateTime UnlockTime;` — If unlocked, the time this achievement was unlocked

#### struct `UE::Online::FGetAchievementState`  
`struct FGetAchievementState`  
_L130-147_
- L132 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetAchievementState::Params`  
`struct Params`  
_L134-140_
- L137 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation
- L139 _public member_ `FString AchievementId;` — Achievement to get state of

#### struct `UE::Online::FGetAchievementState::Result`  
`struct Result`  
_L142-146_
- L145 _public member_ `FAchievementState AchievementState;` — The state of the achievement for the local user

#### struct `UE::Online::FUnlockAchievements`  
`struct FUnlockAchievements`  
_L149-164_
- L151 _public member_ `static constexpr TCHAR Name[] = TEXT("Unl`

#### struct `UE::Online::FUnlockAchievements::Params`  
`struct Params`  
_L153-159_
- L156 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation
- L158 _public member_ `TArray<FString> AchievementIds;` — Achievements to unlock

#### struct `UE::Online::FUnlockAchievements::Result`  
`struct Result`  
_L161-163_

#### struct `UE::Online::FDisplayAchievementUI`  
`struct FDisplayAchievementUI`  
_L166-181_
- L168 _public member_ `static constexpr TCHAR Name[] = TEXT("Dis`

#### struct `UE::Online::FDisplayAchievementUI::Params`  
`struct Params`  
_L170-176_
- L173 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation
- L175 _public member_ `FString AchievementId;` — Achievement to display

#### struct `UE::Online::FDisplayAchievementUI::Result`  
`struct Result`  
_L178-180_

#### struct `UE::Online::FAchievementStateUpdated`  
`struct FAchievementStateUpdated`  
_L184-190_
- desc: Struct for AchievementStateUpdated event
- L187 _public member_ `FAccountId LocalAccountId;` — User whose achievement states have updated
- L189 _public member_ `TArray<FString> AchievementIds;` — Achievements which have updated

#### class `UE::Online::IAchievements`  
`class IAchievements`  
_L194-243_
- L197 _public prototype_ `virtual ~IAchievements() = default;`
- L202 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryAchievementDefinitions> QueryAchievementDefinitions(FQueryAchievementDefinitions::Params&& Params) = 0;` — Query all achievement definitions.
- L208 _public prototype_ `virtual TOnlineResult<FGetAchievementIds> GetAchievementIds(FGetAchievementIds::Params&& Params) = 0;` — Gets the achievement id's. Requires first calling QueryAchievementDefinitions.
- L214 _public prototype_ `virtual TOnlineResult<FGetAchievementDefinition> GetAchievementDefinition(FGetAchievementDefinition::Params&& Params) = 0;` — Gets an achievement definition by id. Requires first calling QueryAchievementDefinitions.
- L220 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryAchievementStates> QueryAchievementStates(FQueryAchievementStates::Params&& Params) = 0;` — Query the state of all achievements for the given player. Requires first calling QueryAchievementDefinitions.
- L226 _public prototype_ `virtual TOnlineResult<FGetAchievementState> GetAchievementState(FGetAchievementState::Params&& Params) const = 0;` — Gets the state of an achievement by id for the given player. Requires first calling QueryAchievementStates.
- L232 _public prototype_ `virtual TOnlineAsyncOpHandle<FUnlockAchievements> UnlockAchievements(FUnlockAchievements::Params&& Params) = 0;` — Manually unlock achievements Requires first calling QueryAchievementStates.
- L237 _public prototype_ `virtual TOnlineResult<FDisplayAchievementUI> DisplayAchievementUI(FDisplayAchievementUI::Params&& Params) = 0;` — Launch the platform UI for a particular achievement
- L242 _public prototype_ `virtual TOnlineEvent<void(const FAchievementStateUpdated&)> OnAchievementStateUpdated() = 0;` — Event triggered when a player's achievement state changes

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L12 _namespace_ `namespace Meta` (scope `UE::Online`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Online` (scope `UE`)
- L56 _prototype_ `FString ToLogString(const FAchievementStatDefinition&);` (scope `UE::Online`)
- L82 _prototype_ `FString ToLogString(const FAchievementDefinition&);` (scope `UE::Online`)
- L128 _prototype_ `FString ToLogString(const FAchievementState&);` (scope `UE::Online`)
- L192 _prototype_ `bool operator==(const FAchievementStateUpdated&, const FAchievementStateUpdated&);` (scope `UE::Online`)
- L245 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/AchievementsErrors.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define LOCTEXT_NAMESPACE "AchievementsErrors"`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace Errors` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/Auth.h` (Public)


#### enum `UE::Online::ELoginStatus`  
`enum class ELoginStatus : uint8`  
_L62-72_
- L65 _public enumerator_ `NotLoggedIn` — Player has not logged in or chosen a local profile.
- L67 _public enumerator_ `UsingLocalProfile` — Player is using a local profile but is not logged in.
- L69 _public enumerator_ `LoggedInReducedFunctionality` — Player is logged in but may have reduced functionality with online services.
- L71 _public enumerator_ `LoggedIn` — Player has been validated by the platform specific authentication service.

#### enum `UE::Online::ERemoteAuthTicketAudience`  
`enum class ERemoteAuthTicketAudience : uint8`  
_L82-91_
- L85 _public enumerator_ `Peer` — Generate a ticket appropriate for peer validation.
- L90 _public enumerator_ `DedicatedServer` — Generate a ticket appropriate for dedicated server validation. Depending on the platform, dedicated servers may have access to additional APIs used to verify tickets.

#### enum `UE::Online::EExternalAuthTokenMethod`  
`enum class EExternalAuthTokenMethod : uint8`  
_L101-107_
- desc: Some auth interfaces have more than one method for providing credentials when linking to an external account. An example usage is when the auth interface can provide a token for linking the local hardware device as the primary method before falling back to a token linked to the users online account.
- L104 _public enumerator_ `Primary` — Acquire an external auth token using the primary method provided by the auth interface.
- L106 _public enumerator_ `Secondary` — Acquire an external auth token using the secondary method provided by the auth interface.

#### struct `UE::Online::FAccountInfo`  
`struct FAccountInfo`  
_L112-122_
- L115 _public member_ `FAccountId AccountId;` — The account id for the user which represents the user's online platform account.
- L117 _public member_ `FPlatformUserId PlatformUserId = PLATFORMUSERID_NONE;` — The platform user id associated with the online user.
- L119 _public member_ `ELoginStatus LoginStatus = ELoginStatus::NotLoggedIn;` — Login status
- L121 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> Attributes;` — Additional account attributes.

#### struct `UE::Online::FExternalAuthToken`  
`struct FExternalAuthToken`  
_L127-131_
- desc: Token appropriate for allowing a trusted server to verify authentication. In most implementations this token will be an OpenId token.
- L129 _public member_ `FName Type;`
- L130 _public member_ `FString Data;`

#### struct `UE::Online::FExternalServerAuthTicket`  
`struct FExternalServerAuthTicket`  
_L134-138_
- desc: Ticket appropriate for allowing a trusted server to access service APIs on the users behalf.
- L136 _public member_ `FName Type;`
- L137 _public member_ `FString Data;`

#### struct `UE::Online::FVerifiedAuthSession`  
`struct FVerifiedAuthSession`  
_L145-150_
- L147 _public member_ `FVerifiedAuthSessionId SessionId;`
- L148 _public member_ `FAccountId RemoteAccountId;`
- L149 _public member_ `double CreationTime;`

#### struct `UE::Online::FVerifiedAuthTicket`  
`struct FVerifiedAuthTicket`  
_L152-156_
- L154 _public member_ `FName Type;`
- L155 _public member_ `FString Data;`

#### struct `UE::Online::FAuthLogin`  
`struct FAuthLogin`  
_L158-176_
- L160 _public member_ `static constexpr TCHAR Name[] = TEXT("Log`

#### struct `UE::Online::FAuthLogin::Params`  
`struct Params`  
_L162-170_
- L165 _public member_ `FPlatformUserId PlatformUserId = PLATFORMUSERID_NONE;` — The PlatformUserId of the Local User making the request.
- L166 _public member_ `FName CredentialsType;`
- L167 _public member_ `FString CredentialsId;`
- L168 _public member_ `TVariant<FString, FExternalAuthToken> CredentialsToken;`
- L169 _public member_ `TArray<FString> Scopes;`

#### struct `UE::Online::FAuthLogin::Result`  
`struct Result`  
_L172-175_
- L174 _public member_ `TSharedRef<FAccountInfo> AccountInfo;`

#### struct `UE::Online::FAuthLogout`  
`struct FAuthLogout`  
_L178-193_
- L180 _public member_ `static constexpr TCHAR Name[] = TEXT("Log`

#### struct `UE::Online::FAuthLogout::Params`  
`struct Params`  
_L182-188_
- L185 _public member_ `FAccountId LocalAccountId;` — The online account id of the Local User making the request.
- L187 _public member_ `bool bDestroyAuth = false;` — Whether to remove persistent credentials on logout.

#### struct `UE::Online::FAuthLogout::Result`  
`struct Result`  
_L190-192_

#### struct `UE::Online::FAuthCreateAccount`  
`struct FAuthCreateAccount`  
_L195-211_
- L197 _public member_ `static constexpr TCHAR Name[] = TEXT("Cre`

#### struct `UE::Online::FAuthCreateAccount::Params`  
`struct Params`  
_L199-205_
- L202 _public member_ `FPlatformUserId PlatformUserId = PLATFORMUSERID_NONE;` — The PlatformUserId of the Local User making the request.
- L204 _public member_ `FLoginContinuationId ContinuationId;` — The id associated with external auth data used to continue a previous login attempt.

#### struct `UE::Online::FAuthCreateAccount::Result`  
`struct Result`  
_L207-210_
- L209 _public member_ `TSharedRef<const FAccountInfo> AccountInfo;`

#### struct `UE::Online::FAuthLinkAccount`  
`struct FAuthLinkAccount`  
_L213-231_
- L215 _public member_ `static constexpr TCHAR Name[] = TEXT("Lin`

#### struct `UE::Online::FAuthLinkAccount::Params`  
`struct Params`  
_L217-225_
- L220 _public member_ `FPlatformUserId PlatformUserId = PLATFORMUSERID_NONE;` — The PlatformUserId of the Local User making the request.
- L222 _public member_ `FLoginContinuationId ContinuationId;` — The id associated with external auth data used to continue a previous login attempt.
- L224 _public member_ `TArray<FName> Tags;` — Implementation dependent tags which affect how the account is linked.

#### struct `UE::Online::FAuthLinkAccount::Result`  
`struct Result`  
_L227-230_
- L229 _public member_ `TSharedRef<const FAccountInfo> AccountInfo;`

#### struct `UE::Online::FAuthModifyAccountAttributes`  
`struct FAuthModifyAccountAttributes`  
_L233-250_
- L235 _public member_ `static constexpr TCHAR Name[] = TEXT("Mod`

#### struct `UE::Online::FAuthModifyAccountAttributes::Params`  
`struct Params`  
_L237-245_
- L240 _public member_ `FAccountId LocalAccountId;` — The online account id of the Local User making the request.
- L242 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> MutatedAttributes;` — New or changed attributes.
- L244 _public member_ `TSet<FSchemaAttributeId> ClearedAttributes;` — Attributes to be cleared.

#### struct `UE::Online::FAuthModifyAccountAttributes::Result`  
`struct Result`  
_L247-249_

#### struct `UE::Online::FAuthQueryExternalServerAuthTicket`  
`struct FAuthQueryExternalServerAuthTicket`  
_L252-266_
- L254 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FAuthQueryExternalServerAuthTicket::Params`  
`struct Params`  
_L256-260_
- L259 _public member_ `FAccountId LocalAccountId;` — The online account id of the Local User making the request.

#### struct `UE::Online::FAuthQueryExternalServerAuthTicket::Result`  
`struct Result`  
_L262-265_
- L264 _public member_ `FExternalServerAuthTicket ExternalServerAuthTicket;`

#### struct `UE::Online::FAuthQueryExternalAuthToken`  
`struct FAuthQueryExternalAuthToken`  
_L268-286_
- L270 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FAuthQueryExternalAuthToken::Params`  
`struct Params`  
_L272-280_
- L275 _public member_ `FAccountId LocalAccountId;` — The online account id of the Local User making the request.
- L277 _public member_ `EExternalAuthTokenMethod Method = EExternalAuthTokenMethod::Primary;` — The method of external auth to provide.
- L279 _public member_ `FString RelyingParty;` — The Relying Party for the external auth token.

#### struct `UE::Online::FAuthQueryExternalAuthToken::Result`  
`struct Result`  
_L282-285_
- L284 _public member_ `FExternalAuthToken ExternalAuthToken;`

#### struct `UE::Online::FAuthQueryVerifiedAuthTicket`  
`struct FAuthQueryVerifiedAuthTicket`  
_L288-307_
- L290 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FAuthQueryVerifiedAuthTicket::Params`  
`struct Params`  
_L292-298_
- L295 _public member_ `FAccountId LocalAccountId;` — The online account id of the Local User making the request.
- L297 _public member_ `ERemoteAuthTicketAudience Audience = ERemoteAuthTicketAudience::Peer;` — The intended purpose of the auth ticket.

#### struct `UE::Online::FAuthQueryVerifiedAuthTicket::Result`  
`struct Result`  
_L300-306_
- L303 _public member_ `FVerifiedAuthTicketId VerifiedAuthTicketId;` — Local ticket id used to reference the ticket in further operations.
- L305 _public member_ `FVerifiedAuthTicket VerifiedAuthTicket;` — Ticket used to begin a verified auth session with a remote host.

#### struct `UE::Online::FAuthCancelVerifiedAuthTicket`  
`struct FAuthCancelVerifiedAuthTicket`  
_L309-324_
- L311 _public member_ `static constexpr TCHAR Name[] = TEXT("Can`

#### struct `UE::Online::FAuthCancelVerifiedAuthTicket::Params`  
`struct Params`  
_L313-319_
- L316 _public member_ `FAccountId LocalAccountId;` — The online account id of the Local User making the request.
- L318 _public member_ `FVerifiedAuthTicketId VerifiedAuthTicketId;` — Local ticket id used to reference the verified auth ticket.

#### struct `UE::Online::FAuthCancelVerifiedAuthTicket::Result`  
`struct Result`  
_L321-323_

#### struct `UE::Online::FAuthBeginVerifiedAuthSession`  
`struct FAuthBeginVerifiedAuthSession`  
_L326-342_
- L328 _public member_ `static constexpr TCHAR Name[] = TEXT("Beg`

#### struct `UE::Online::FAuthBeginVerifiedAuthSession::Params`  
`struct Params`  
_L330-336_
- L333 _public member_ `FAccountId RemoteAccountId;` — The remote user for which to start the verified auth session.
- L335 _public member_ `FVerifiedAuthTicket Ticket;` — The ticket used to verify the identity of the user.

#### struct `UE::Online::FAuthBeginVerifiedAuthSession::Result`  
`struct Result`  
_L338-341_
- L340 _public member_ `FVerifiedAuthSession Session;`

#### struct `UE::Online::FAuthEndVerifiedAuthSession`  
`struct FAuthEndVerifiedAuthSession`  
_L344-356_
- L346 _public member_ `static constexpr TCHAR Name[] = TEXT("End`

#### struct `UE::Online::FAuthEndVerifiedAuthSession::Params`  
`struct Params`  
_L348-351_
- L350 _public member_ `FVerifiedAuthSessionId SessionId;`

#### struct `UE::Online::FAuthEndVerifiedAuthSession::Result`  
`struct Result`  
_L353-355_

#### struct `UE::Online::FAuthGetLocalOnlineUserByOnlineAccountId`  
`struct FAuthGetLocalOnlineUserByOnlineAccountId`  
_L358-372_
- L360 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FAuthGetLocalOnlineUserByOnlineAccountId::Params`  
`struct Params`  
_L362-366_
- L365 _public member_ `FAccountId LocalAccountId;` — Account Id of the Local User making the request

#### struct `UE::Online::FAuthGetLocalOnlineUserByOnlineAccountId::Result`  
`struct Result`  
_L368-371_
- L370 _public member_ `TSharedRef<FAccountInfo> AccountInfo;`

#### struct `UE::Online::FAuthGetLocalOnlineUserByPlatformUserId`  
`struct FAuthGetLocalOnlineUserByPlatformUserId`  
_L374-388_
- L376 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FAuthGetLocalOnlineUserByPlatformUserId::Params`  
`struct Params`  
_L378-382_
- L381 _public member_ `FPlatformUserId PlatformUserId;` — The PlatformUserId of the Local User making the request.

#### struct `UE::Online::FAuthGetLocalOnlineUserByPlatformUserId::Result`  
`struct Result`  
_L384-387_
- L386 _public member_ `TSharedRef<FAccountInfo> AccountInfo;`

#### struct `UE::Online::FAuthGetAllLocalOnlineUsers`  
`struct FAuthGetAllLocalOnlineUsers`  
_L390-402_
- L392 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FAuthGetAllLocalOnlineUsers::Params`  
`struct Params`  
_L394-396_

#### struct `UE::Online::FAuthGetAllLocalOnlineUsers::Result`  
`struct Result`  
_L398-401_
- L400 _public member_ `TArray<TSharedRef<FAccountInfo>> AccountInfo;`

#### struct `UE::Online::FAuthGetLinkAccountContinuationId`  
`struct FAuthGetLinkAccountContinuationId`  
_L404-419_
- L406 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FAuthGetLinkAccountContinuationId::Params`  
`struct Params`  
_L408-412_
- L411 _public member_ `FPlatformUserId PlatformUserId = PLATFORMUSERID_NONE;` — The PlatformUserId of the Local User making the request.

#### struct `UE::Online::FAuthGetLinkAccountContinuationId::Result`  
`struct Result`  
_L414-418_
- L417 _public member_ `FLoginContinuationId ContinuationId;` — The continuation id which identifies the external auth to be linked.

#### struct `UE::Online::FAuthGetRelyingParty`  
`struct FAuthGetRelyingParty`  
_L421-433_
- L423 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FAuthGetRelyingParty::Params`  
`struct Params`  
_L425-427_

#### struct `UE::Online::FAuthGetRelyingParty::Result`  
`struct Result`  
_L429-432_
- L431 _public member_ `FString RelyingParty;`

#### struct `UE::Online::FAuthLoginStatusChanged`  
`struct FAuthLoginStatusChanged`  
_L436-442_
- desc: Struct for LoginStatusChanged event
- L439 _public member_ `TSharedRef<FAccountInfo> AccountInfo;` — The affected account.
- L441 _public member_ `ELoginStatus LoginStatus = ELoginStatus::NotLoggedIn;` — The new login status.

#### struct `UE::Online::FAuthPendingAuthExpiration`  
`struct FAuthPendingAuthExpiration`  
_L445-449_
- desc: Struct for PendingAuthExpiration event
- L448 _public member_ `TSharedRef<FAccountInfo> AccountInfo;` — The affected account.

#### struct `UE::Online::FAuthAccountAttributesChanged`  
`struct FAuthAccountAttributesChanged`  
_L452-462_
- desc: Struct for AccountAttributesChanged event
- L455 _public member_ `TSharedRef<FAccountInfo> AccountInfo;` — The affected account.
- L457 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> AddedAttributes;` — Added attributes and their values.
- L459 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> RemovedAttributes;` — Removed attributes with their previous values.
- L461 _public member_ `TMap<FSchemaAttributeId, TPair<FSchemaVariant, FSchemaVariant>> ChangedAttributes;` — Changed attributes with their old and new values.

#### class `UE::Online::IAuth`  
`class IAuth`  
_L464-607_
- L467 _public prototype_ `virtual ~IAuth() = default;`
- L477 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthLogin> Login(FAuthLogin::Params&& Params) = 0;` — Authenticate a local user. If necessary, retrieve and maintain an access token for the duration of the auth session. Returns Errors::InvalidUser when no user has been associated with the provided credentials. GetLinkAccountContinuationId can then be used to retrieve a continuance token which can be passed to either CreateAccount or LinkAccount.
- L482 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthLogout> Logout(FAuthLogout::Params&& Params) = 0;` — Concludes the auth session for the local user.
- L487 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthCreateAccount> CreateAccount(FAuthCreateAccount::Params&& Params) = 0;` — Create a new account and link it to an external auth method using a continuation token from a previous login attempt.
- L492 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthLinkAccount> LinkAccount(FAuthLinkAccount::Params&& Params) = 0;` — Link a logged in account to an external auth method using a continuation token from a previous login attempt.
- L497 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthModifyAccountAttributes> ModifyAccountAttributes(FAuthModifyAccountAttributes::Params&& Params) = 0;` — Modify attributes associated with an authenticated account. Signals OnAccountAttributesChanged on completion.
- L504 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthQueryExternalServerAuthTicket> QueryExternalServerAuthTicket(FAuthQueryExternalServerAuthTicket::Params&& Params) = 0;` — Queries a ticket which is appropriate for making server-to-server calls on behalf of the signed in user. Tickets are intended to be single use - users must call the API again to retrieve a new ticket when making repeated calls which use a ticket.
- L511 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthQueryExternalAuthToken> QueryExternalAuthToken(FAuthQueryExternalAuthToken::Params&& Params) = 0;` — Retrieves a token appropriate for linking the service account with a service account of a different service type. On most platforms this will return an OpenId token. May return a cached token, but will handle refreshing if necessary.
- L526 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthQueryVerifiedAuthTicket> QueryVerifiedAuthTicket(FAuthQueryVerifiedAuthTicket::Params&& Params) = 0;` — Retrieves a ticket which is used to create a verified authentication session on a remote client. When establishing a verified authentication session the user must always call QueryVerifiedAuthTicket to retrieve a new ticket. To prevent the transmission of PII to a non-trusted destination an audience enumeration is required which may generate an empty ticket in the case of some peer-to-peer implementations. On those platforms user authentication is handled implicitly through the peer-to-peer networking model. It is the responsibility of the game code to provide an audience enumeration value appropriate for the usage.
- L533 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthCancelVerifiedAuthTicket> CancelVerifiedAuthTicket(FAuthCancelVerifiedAuthTicket::Params&& Params) = 0;` — Cancels the ticket associated with a verified auth session. When the session created using a verified auth ticket is no longer in use, CancelVerifiedAuthTicket must be called to clean up any resources associated with the ticket.
- L549 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthBeginVerifiedAuthSession> BeginVerifiedAuthSession(FAuthBeginVerifiedAuthSession::Params&& Params) = 0;` — Starts a verified auth session for a remote user. Depending on implementation RemoteAuthTicket will be used to verify the identity of RemoteUserId. The intended usage is to start a verified auth session for any client connecting any other client or server. Having a verified auth session handles identity verification in both peer-to-peer and client-server topologies. In peer-to-peer topologies authentication may not occur due to implicit trust established by the peer-to-peer network. Creating a verified auth session will generate a FVerifiedAuthSessionId. This id is a cryptographically secure random id intended to be transmitted between the established peers to refer to the remote auth session. This id is needed when the client changes how they communicate with the server. An example is connecting to a server reservation beacon to reserve a spot before traveling to the server url using a different connection.
- L554 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthEndVerifiedAuthSession> EndVerifiedAuthSession(FAuthEndVerifiedAuthSession::Params&& Params) = 0;` — Clean up the remote verified auth session and handle any required book-keeping.
- L559 _public prototype_ `virtual TOnlineResult<FAuthGetLocalOnlineUserByOnlineAccountId> GetLocalOnlineUserByOnlineAccountId(FAuthGetLocalOnlineUserByOnlineAccountId::Params&& Params) const = 0;` — Retrieve a logged in user account.
- L564 _public prototype_ `virtual TOnlineResult<FAuthGetLocalOnlineUserByPlatformUserId> GetLocalOnlineUserByPlatformUserId(FAuthGetLocalOnlineUserByPlatformUserId::Params&& Params) const = 0;` — Retrieve a logged in user account.
- L569 _public prototype_ `virtual TOnlineResult<FAuthGetAllLocalOnlineUsers> GetAllLocalOnlineUsers(FAuthGetAllLocalOnlineUsers::Params&& Params) const = 0;` — Retrieve all logged in user accounts.
- L574 _public prototype_ `virtual TOnlineResult<FAuthGetLinkAccountContinuationId> GetLinkAccountContinuationId(FAuthGetLinkAccountContinuationId::Params&& Params) const = 0;` — Retrieve the continuation id from a previous login attempt which used an external auth token and failed with Errors::InvalidUser.
- L579 _public prototype_ `virtual TOnlineResult<FAuthGetRelyingParty> GetRelyingParty(FAuthGetRelyingParty::Params&& Params) const = 0;` — Retrieve the relying party to use when fetching an external token to authenticate with this interface.
- L584 _public prototype_ `virtual TOnlineEvent<void(const FAuthLoginStatusChanged&)> OnLoginStatusChanged() = 0;` — Triggered when the login status for a logged in user changes.
- L591 _public prototype_ `virtual TOnlineEvent<void(const FAuthPendingAuthExpiration&)> OnPendingAuthExpiration() = 0;` — Triggered when the auth token will expire soon. Services which allow login using an external auth token may trigger this notification when an updated external auth token is required to maintain the auth session without interruption.
- L596 _public prototype_ `virtual TOnlineEvent<void(const FAuthAccountAttributesChanged&)> OnAccountAttributesChanged() = 0;` — Triggered when the additional attributes associated with an authenticated account are changed.
- L601 _public prototype_ `virtual bool IsLoggedIn(const FAccountId& AccountId) const = 0;` — Helper for querying the login status of a local user.
- L606 _public prototype_ `virtual bool IsLoggedIn(const FPlatformUserId& PlatformUserId) const = 0;` — Helper for querying the login status of a local user by platform user id.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L17 _namespace_ `namespace LoginCredentialsType` (scope `UE::Online`)
- L19 _externvar_ `extern const FName Auto;` (scope `UE::Online::LoginCredentialsType`)
- L20 _externvar_ `extern const FName Password;` (scope `UE::Online::LoginCredentialsType`)
- L21 _externvar_ `extern const FName ExchangeCode;` (scope `UE::Online::LoginCredentialsType`)
- L22 _externvar_ `extern const FName PersistentAuth;` (scope `UE::Online::LoginCredentialsType`)
- L23 _externvar_ `extern const FName Developer;` (scope `UE::Online::LoginCredentialsType`)
- L24 _externvar_ `extern const FName RefreshToken;` (scope `UE::Online::LoginCredentialsType`)
- L25 _externvar_ `extern const FName AccountPortal;` (scope `UE::Online::LoginCredentialsType`)
- L26 _externvar_ `extern const FName ExternalAuth;` (scope `UE::Online::LoginCredentialsType`)
- L29 _namespace_ `namespace ExternalLoginType` (scope `UE::Online`)
- L31 _externvar_ `extern const FName Epic;` (scope `UE::Online::ExternalLoginType`)
- L32 _externvar_ `extern const FName SteamSessionTicket;` (scope `UE::Online::ExternalLoginType`)
- L33 _externvar_ `extern const FName PsnIdToken;` (scope `UE::Online::ExternalLoginType`)
- L34 _externvar_ `extern const FName XblXstsToken;` (scope `UE::Online::ExternalLoginType`)
- L35 _externvar_ `extern const FName DiscordAccessToken;` (scope `UE::Online::ExternalLoginType`)
- L36 _externvar_ `extern const FName GogSessionTicket;` (scope `UE::Online::ExternalLoginType`)
- L37 _externvar_ `extern const FName NintendoIdToken;` (scope `UE::Online::ExternalLoginType`)
- L38 _externvar_ `extern const FName NintendoNsaIdToken;` (scope `UE::Online::ExternalLoginType`)
- L39 _externvar_ `extern const FName UplayAccessToken;` (scope `UE::Online::ExternalLoginType`)
- L40 _externvar_ `extern const FName OpenIdAccessToken;` (scope `UE::Online::ExternalLoginType`)
- L41 _externvar_ `extern const FName DeviceIdAccessToken;` (scope `UE::Online::ExternalLoginType`)
- L42 _externvar_ `extern const FName AppleIdToken;` (scope `UE::Online::ExternalLoginType`)
- L43 _externvar_ `extern const FName GoogleIdToken;` (scope `UE::Online::ExternalLoginType`)
- L44 _externvar_ `extern const FName OculusUserIdNonce;` (scope `UE::Online::ExternalLoginType`)
- L45 _externvar_ `extern const FName ItchioJwt;` (scope `UE::Online::ExternalLoginType`)
- L46 _externvar_ `extern const FName ItchioKey;` (scope `UE::Online::ExternalLoginType`)
- L47 _externvar_ `extern const FName EpicIdToken;` (scope `UE::Online::ExternalLoginType`)
- L48 _externvar_ `extern const FName AmazonAccessToken;` (scope `UE::Online::ExternalLoginType`)
- L51 _namespace_ `namespace ExternalServerAuthTicketType` (scope `UE::Online`)
- L53 _externvar_ `extern const FName PsnAuthCode;` (scope `UE::Online::ExternalServerAuthTicketType`)
- L54 _externvar_ `extern const FName XblXstsToken;` (scope `UE::Online::ExternalServerAuthTicketType`)
- L57 _namespace_ `namespace AccountAttributeData` (scope `UE::Online`)
- L59 _externvar_ `extern const FSchemaAttributeId DisplayName;` (scope `UE::Online::AccountAttributeData`)
- L73 _prototype_ `const TCHAR* LexToString(ELoginStatus Value);` (scope `UE::Online`)
- L74 _prototype_ `bool LexTryParseString(ELoginStatus& OutValue, const TCHAR* InStr);` (scope `UE::Online`)
- L75 _prototype_ `void LexFromString(ELoginStatus& OutValue, const TCHAR* InStr);` (scope `UE::Online`)
- L77 _function_ `inline bool IsOnlineStatus(ELoginStatus LoginStatus)` (scope `UE::Online`)
- L92 _prototype_ `const TCHAR* LexToString(ERemoteAuthTicketAudience Value);` (scope `UE::Online`)
- L93 _prototype_ `bool LexTryParseString(ERemoteAuthTicketAudience& OutValue, const TCHAR* InStr);` (scope `UE::Online`)
- L94 _prototype_ `void LexFromString(ERemoteAuthTicketAudience& OutValue, const TCHAR* InStr);` (scope `UE::Online`)
- L108 _prototype_ `const TCHAR* LexToString(EExternalAuthTokenMethod Value);` (scope `UE::Online`)
- L109 _prototype_ `bool LexTryParseString(EExternalAuthTokenMethod& OutValue, const TCHAR* InStr);` (scope `UE::Online`)
- L110 _prototype_ `void LexFromString(EExternalAuthTokenMethod& OutValue, const TCHAR* InStr);` (scope `UE::Online`)
- L143 _typedef_ `using FCredentialsToken = TVariant<FString, FExternalAuthToken>;` (scope `UE::Online`) — Token used during Login operation. The data provided as the credentials token varies based on the type of login being performed.
- L609 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/AuthErrors.h` (Public)


#### Free symbols / members of external scopes

- L8 _macro_ `#define LOCTEXT_NAMESPACE "AuthErrors"`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace Errors` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/Commerce.h` (Public)


#### enum `UE::Online::EOfferType`  
`enum class EOfferType : uint8`  
_L22-28_
- L24 _public enumerator_ `Nonconsumable`
- L25 _public enumerator_ `Consumable`
- L26 _public enumerator_ `Subscription`
- L27 _public enumerator_ `Unknown`

#### struct `UE::Online::FOffer`  
`struct FOffer`  
_L34-65_
- desc: Contains all the information required to display an offer to a user.
- L37 _public member_ `FOfferId OfferId;` — The Id of this offer
- L39 _public member_ `FText Title;` — Localized title of this offer
- L41 _public member_ `FText Description;` — Localized description of this offer
- L43 _public member_ `FText LongDescription;` — Localized long description of this offer
- L45 _public member_ `int32 PurchaseLimit;` — The maximum number of times the offer can be purchased (-1 for no limit)
- L47 _public member_ `FString CurrencyCode;` — Currency Code for this offer
- L49 _public member_ `FText FormattedRegularPrice;` — Regular non-sale price as text for display
- L51 _public member_ `uint64 RegularPrice;` — Regular non-sale price in numeric form for comparison/sorting
- L53 _public member_ `FText FormattedPrice;` — Final-Pricing (Post-Sales/Discounts) as text for display
- L55 _public member_ `uint64 Price;` — Final-Price (Post-Sales/Discounts) in numeric form for comparison/sorting
- L57 _public member_ `int32 PriceDecimalPoint;` — Number of decimal places in Price/RegularPrice
- L59 _public member_ `TOptional<FDateTime> ReleaseDate;` — Date the offer was first available/will be available
- L61 _public member_ `TOptional<FDateTime> ExpirationDate;` — Date the information is no longer valid (offer no longer available or discount expires)
- L63 _public member_ `TMap<FString, FString> AdditionalData;` — Additional implementation specified fields. See the implementation specific documentation for what this will contain

#### struct `UE::Online::FCommerceQueryOffers`  
`struct FCommerceQueryOffers`  
_L67-83_
- L69 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FCommerceQueryOffers::Params`  
`struct Params`  
_L71-77_
- L74 _public member_ `FAccountId LocalAccountId;` — Local user
- L76 _public member_ `FString OverrideCatalogNamespace;` — Optional catalog namespace to use for this query. Can be left blank to use the "default" namespace

#### struct `UE::Online::FCommerceQueryOffers::Result`  
`struct Result`  
_L79-82_

#### struct `UE::Online::FCommerceQueryOffersById`  
`struct FCommerceQueryOffersById`  
_L86-103_
- desc: Query the offers matching specified offer ids
- L88 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FCommerceQueryOffersById::Params`  
`struct Params`  
_L90-96_
- L93 _public member_ `FAccountId LocalAccountId;` — Local user
- L95 _public member_ `TArray<FOfferId> OfferIds;` — List of offer ids

#### struct `UE::Online::FCommerceQueryOffersById::Result`  
`struct Result`  
_L98-102_
- L101 _public member_ `TArray<FOfferId> OfferIds;` — List of offer ids that were found

#### struct `UE::Online::FCommerceGetOffers`  
`struct FCommerceGetOffers`  
_L106-121_
- desc: Get the complete list of cached offers
- L108 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FCommerceGetOffers::Params`  
`struct Params`  
_L110-114_
- L113 _public member_ `FAccountId LocalAccountId;` — Local user

#### struct `UE::Online::FCommerceGetOffers::Result`  
`struct Result`  
_L116-120_
- L119 _public member_ `TArray<FOffer> Offers;` — List of offers

#### struct `UE::Online::FCommerceGetOffersById`  
`struct FCommerceGetOffersById`  
_L124-141_
- desc: Get the offers for a list of offer ids
- L126 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FCommerceGetOffersById::Params`  
`struct Params`  
_L128-134_
- L131 _public member_ `FAccountId LocalAccountId;` — Local user
- L133 _public member_ `TArray<FOfferId> OfferIds;` — List of offer ids

#### struct `UE::Online::FCommerceGetOffersById::Result`  
`struct Result`  
_L136-140_
- L139 _public member_ `TArray<FOffer> Offers;` — List of offers

#### struct `UE::Online::FCommerceShowStoreUI`  
`struct FCommerceShowStoreUI`  
_L144-159_
- desc: Bring up the platform store ui
- L147 _public member_ `static constexpr TCHAR Name[] = TEXT("Sho`

#### struct `UE::Online::FCommerceShowStoreUI::Params`  
`struct Params`  
_L149-153_
- L152 _public member_ `FAccountId LocalAccountId;` — Local user

#### struct `UE::Online::FCommerceShowStoreUI::Result`  
`struct Result`  
_L155-158_

#### struct `UE::Online::FPurchaseOffer`  
`struct FPurchaseOffer`  
_L161-167_
- L164 _public member_ `FOfferId OfferId;` — The Id of the offer
- L166 _public member_ `int32 Quantity;` — Quantity of the offer to purchase

#### struct `UE::Online::FCommerceCheckout`  
`struct FCommerceCheckout`  
_L170-187_
- desc: Initiate the checkout process for purchasing one or more offers
- L172 _public member_ `static constexpr TCHAR Name[] = TEXT("Che`

#### struct `UE::Online::FCommerceCheckout::Params`  
`struct Params`  
_L174-180_
- L177 _public member_ `FAccountId LocalAccountId;` — Local user
- L179 _public member_ `TArray<FPurchaseOffer> Offers;` — Offers to purchase

#### struct `UE::Online::FCommerceCheckout::Result`  
`struct Result`  
_L182-186_
- L185 _public member_ `TOptional<FString> TransactionId;` — If available, the transaction id for the completed purchase

#### struct `UE::Online::FEntitlement`  
`struct FEntitlement`  
_L189-205_
- L192 _public member_ `FEntitlementId EntitlementId;` — Id of the entitlement
- L194 _public member_ `FName EntitlementType;` — Type of the entitlement
- L196 _public member_ `FString ProductId;` — The Id of the product
- L198 _public member_ `bool bRedeemed;` — True if the entitlement has been marked as redeemed
- L200 _public member_ `int32 Quantity;` — Quantity
- L202 _public member_ `TOptional<FDateTime> AcquiredDate;` — If set, specifies when the entitlement was acquired
- L204 _public member_ `TOptional<FDateTime> ExpiryDate;` — If set, specifies when the entitlement will expire

#### struct `UE::Online::FCommerceQueryTransactionEntitlements`  
`struct FCommerceQueryTransactionEntitlements`  
_L208-226_
- desc: Retrieve the list of entitlements from a transaction id returned from a checkout call
- L211 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FCommerceQueryTransactionEntitlements::Params`  
`struct Params`  
_L213-219_
- L216 _public member_ `FAccountId LocalAccountId;` — Local user
- L218 _public member_ `FString TransactionId;` — Transaction id for a completed purchase

#### struct `UE::Online::FCommerceQueryTransactionEntitlements::Result`  
`struct Result`  
_L221-225_
- L224 _public member_ `TArray<FEntitlement> Entitlements;` — Array of entitlements granted in the transaction

#### struct `UE::Online::FCommerceQueryEntitlements`  
`struct FCommerceQueryEntitlements`  
_L229-245_
- desc: Get the list of all entitlements
- L231 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FCommerceQueryEntitlements::Params`  
`struct Params`  
_L233-239_
- L236 _public member_ `FAccountId LocalAccountId;` — Local user
- L238 _public member_ `bool bIncludeRedeemed;` — Whether or not to fetch redeemed entitlements

#### struct `UE::Online::FCommerceQueryEntitlements::Result`  
`struct Result`  
_L241-244_

#### struct `UE::Online::FCommerceGetEntitlements`  
`struct FCommerceGetEntitlements`  
_L248-263_
- desc: Get the complete list of cached entitlements
- L250 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FCommerceGetEntitlements::Params`  
`struct Params`  
_L252-256_
- L255 _public member_ `FAccountId LocalAccountId;` — Local user

#### struct `UE::Online::FCommerceGetEntitlements::Result`  
`struct Result`  
_L258-262_
- L261 _public member_ `TArray<FEntitlement> Entitlements;` — Array of entitlements owned by the user

#### struct `UE::Online::FCommerceRedeemEntitlement`  
`struct FCommerceRedeemEntitlement`  
_L266-284_
- desc: Mark an entitlement as redeemed.Used when there is no external service managing redemption of entitlements or the redemption must be done on the client side.
- L268 _public member_ `static constexpr TCHAR Name[] = TEXT("Red`

#### struct `UE::Online::FCommerceRedeemEntitlement::Params`  
`struct Params`  
_L270-278_
- L273 _public member_ `FAccountId LocalAccountId;` — Local user
- L275 _public member_ `FEntitlementId EntitlementId;` — Entitlement id to mark as redeemed
- L277 _public member_ `int32 Quantity;` — Quantity to consume

#### struct `UE::Online::FCommerceRedeemEntitlement::Result`  
`struct Result`  
_L280-283_

#### struct `UE::Online::FCommerceRetrieveS2SToken`  
`struct FCommerceRetrieveS2SToken`  
_L287-304_
- desc: Get a token suitable for making service to service Commerce related calls
- L289 _public member_ `static constexpr TCHAR Name[] = TEXT("Ret`

#### struct `UE::Online::FCommerceRetrieveS2SToken::Params`  
`struct Params`  
_L291-297_
- L294 _public member_ `FAccountId LocalAccountId;` — Local user
- L296 _public member_ `FString TokenType;` — Implementation specific, used to specify the type of token to retrieve. See implementation specific documentation for valid values

#### struct `UE::Online::FCommerceRetrieveS2SToken::Result`  
`struct Result`  
_L299-303_
- L302 _public member_ `TArray<uint8> Token;` — Token or code that can be used for service to service calls. See implementation specific documentation for details

#### struct `UE::Online::FCommerceOnPurchaseComplete`  
`struct FCommerceOnPurchaseComplete`  
_L307-317_
- desc: event
- L312 _public member_ `FAccountId LocalAccountId;` — Local user
- L315 _public member_ `TOptional<FString> TransactionId;` — If available, the transaction id for the completed purchase

#### class `UE::Online::ICommerce`  
`class ICommerce`  
_L319-359_
- L322 _public prototype_ `virtual ~ICommerce() = default;`
- L325 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryOffers> QueryOffers(FCommerceQueryOffers::Params&& Params) = 0;` — Query the list of all offers for the target user
- L328 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryOffersById> QueryOffersById(FCommerceQueryOffersById::Params&& Params) = 0;` — Query the offers matching specified offer ids
- L331 _public prototype_ `virtual TOnlineResult<FCommerceGetOffers> GetOffers(FCommerceGetOffers::Params&& Params) = 0;` — Get the complete list of cached offers
- L334 _public prototype_ `virtual TOnlineResult<FCommerceGetOffersById> GetOffersById(FCommerceGetOffersById::Params&& Params) = 0;` — Get the offers for a list of offer ids
- L337 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceShowStoreUI> ShowStoreUI(FCommerceShowStoreUI::Params&& Params) = 0;` — Bring up the platform store ui
- L340 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceCheckout> Checkout(FCommerceCheckout::Params&& Params) = 0;` — Initiate the checkout process for purchasing one or more offers
- L343 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryTransactionEntitlements> QueryTransactionEntitlements(FCommerceQueryTransactionEntitlements::Params&& Params) = 0;` — Retrieve the list of entitlements from a transaction id returned from a checkout call
- L346 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceQueryEntitlements> QueryEntitlements(FCommerceQueryEntitlements::Params&& Params) = 0;` — Get the list of all entitlements
- L349 _public prototype_ `virtual TOnlineResult<FCommerceGetEntitlements> GetEntitlements(FCommerceGetEntitlements::Params&& Params) = 0;` — Get the complete list of cached entitlements
- L352 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceRedeemEntitlement> RedeemEntitlement(FCommerceRedeemEntitlement::Params&& Params) = 0;` — Mark an entitlement as redeemed. Used when there is no external service managing redemption of entitlements or the redemption must be done on the client side
- L355 _public prototype_ `virtual TOnlineAsyncOpHandle<FCommerceRetrieveS2SToken> RetrieveS2SToken(FCommerceRetrieveS2SToken::Params&& Params) = 0;` — Get a token suitable for making service to service Commerce related calls
- L358 _public prototype_ `virtual TOnlineEvent<void(const FCommerceOnPurchaseComplete&)> OnPurchaseCompleted() = 0;` — Fires whenever a purchase is completed

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L12 _namespace_ `namespace Meta` (scope `UE::Online`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Online` (scope `UE`)
- L17 _typedef_ `using FOfferId = FString;` (scope `UE::Online`) — Unique identifier for an offer
- L20 _typedef_ `using FEntitlementId = FString;` (scope `UE::Online`) — Unique identifier for an entitlement
- L30 _prototype_ `const TCHAR* LexToString(EOfferType Status);` (scope `UE::Online`)
- L31 _prototype_ `void LexFromString(EOfferType& OutStatus, const TCHAR* InStr);` (scope `UE::Online`)
- L361 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/Connectivity.h` (Public)


#### enum `UE::Online::EOnlineServicesConnectionStatus`  
`enum class EOnlineServicesConnectionStatus : uint8`  
_L15-21_
- L18 _public enumerator_ `Connected` — Connected to the online servers
- L20 _public enumerator_ `NotConnected` — Successfully disconnected from the online servers

#### struct `UE::Online::FGetConnectionStatus`  
`struct FGetConnectionStatus`  
_L25-42_
- L27 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetConnectionStatus::Params`  
`struct Params`  
_L30-34_
- desc: Input struct for Connectivity::FGetConnectionStatus
- L33 _public member_ `FString ServiceName;` — Optional. If set, the name of the specific service being accessed (service dependent).

#### struct `UE::Online::FGetConnectionStatus::Result`  
`struct Result`  
_L37-41_
- desc: Output struct for Connectivity::FGetConnectionStatus
- L40 _public member_ `EOnlineServicesConnectionStatus Status;` — Connection status

#### struct `UE::Online::FConnectionStatusChanged`  
`struct FConnectionStatusChanged`  
_L45-53_
- desc: Struct for ConnectionStatusChanged event
- L48 _public member_ `FString ServiceName;` — The name of the service that is reporting (service dependent). Can be empty.
- L50 _public member_ `EOnlineServicesConnectionStatus PreviousStatus;` — Previous connection status
- L52 _public member_ `EOnlineServicesConnectionStatus CurrentStatus;` — Current connection status

#### class `UE::Online::IConnectivity`  
`class IConnectivity`  
_L55-69_
- L58 _public prototype_ `virtual ~IConnectivity() = default;`
- L63 _public prototype_ `virtual TOnlineResult<FGetConnectionStatus> GetConnectionStatus(FGetConnectionStatus::Params&& Params) = 0;` — Accessor for the connection status
- L68 _public prototype_ `virtual TOnlineEvent<void(const FConnectionStatusChanged&)> OnConnectionStatusChanged() = 0;` — Event triggered when the connection status changes

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace Meta` (scope `UE::Online`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L22 _prototype_ `const TCHAR* LexToString(EOnlineServicesConnectionStatus Status);` (scope `UE::Online`)
- L23 _prototype_ `void LexFromString(EOnlineServicesConnectionStatus& OutStatus, const TCHAR* InStr);` (scope `UE::Online`)
- L71 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/ExternalUI.h` (Public)


#### struct `UE::Online::FExternalUIShowLoginUI`  
`struct FExternalUIShowLoginUI`  
_L17-34_
- L19 _public member_ `static constexpr TCHAR Name[] = TEXT("Sho`

#### struct `UE::Online::FExternalUIShowLoginUI::Params`  
`struct Params`  
_L21-27_
- L24 _public member_ `FPlatformUserId PlatformUserId = PLATFORMUSERID_NONE;` — Platform user id logging in
- L26 _public member_ `TArray<FString> Scopes;` — Auth scopes to request

#### struct `UE::Online::FExternalUIShowLoginUI::Result`  
`struct Result`  
_L29-33_
- L32 _public member_ `TSharedRef<FAccountInfo> AccountInfo;` — The account info that was logged into

#### struct `UE::Online::FExternalUIShowFriendsUI`  
`struct FExternalUIShowFriendsUI`  
_L36-49_
- L38 _public member_ `static constexpr TCHAR Name[] = TEXT("Sho`

#### struct `UE::Online::FExternalUIShowFriendsUI::Params`  
`struct Params`  
_L40-44_
- L43 _public member_ `FAccountId LocalAccountId;` — Local user id to show the friends UI for

#### struct `UE::Online::FExternalUIShowFriendsUI::Result`  
`struct Result`  
_L46-48_

#### struct `UE::Online::FExternalUIStatusChanged`  
`struct FExternalUIStatusChanged`  
_L52-56_
- desc: Struct for ExternalUIStatusChanged event
- L55 _public member_ `bool bIsOpening = false;` — Whether the external UI is being opened or not

#### class `UE::Online::IExternalUI`  
`class IExternalUI`  
_L58-77_
- L61 _public prototype_ `virtual ~IExternalUI() = default;`
- L66 _public prototype_ `virtual TOnlineAsyncOpHandle<FExternalUIShowLoginUI> ShowLoginUI(FExternalUIShowLoginUI::Params&& Params) = 0;` — Shows the online service's login UI
- L71 _public prototype_ `virtual TOnlineAsyncOpHandle<FExternalUIShowFriendsUI> ShowFriendsUI(FExternalUIShowFriendsUI::Params&& Params) = 0;` — Shows the online service's friends UI
- L76 _public prototype_ `virtual TOnlineEvent<void(const FExternalUIStatusChanged&)> OnExternalUIStatusChanged() = 0;` — Event triggered when an external UI's status changes

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace Meta` (scope `UE::Online`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L79 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/Leaderboards.h` (Public)


#### struct `UE::Online::FLeaderboardEntry`  
`struct FLeaderboardEntry`  
_L15-23_
- L18 _public member_ `FAccountId AccountId;` — The account id of this leaderboard entry
- L20 _public member_ `int32 Rank;` — The rank of this account
- L22 _public member_ `int64 Score;` — The score of this account

#### struct `UE::Online::FReadEntriesForUsers`  
`struct FReadEntriesForUsers`  
_L25-44_
- L27 _public member_ `static constexpr TCHAR Name[] = TEXT("Rea`

#### struct `UE::Online::FReadEntriesForUsers::Params`  
`struct Params`  
_L29-37_
- L32 _public member_ `FAccountId LocalAccountId;` — Local user id
- L34 _public member_ `TArray<FAccountId> AccountIds;` — The account ids of users
- L36 _public member_ `FString BoardName;` — The leaderboard name

#### struct `UE::Online::FReadEntriesForUsers::Result`  
`struct Result`  
_L39-43_
- L42 _public member_ `TArray<FLeaderboardEntry> Entries;` — The result leaderboard entries

#### struct `UE::Online::FReadEntriesAroundRank`  
`struct FReadEntriesAroundRank`  
_L46-67_
- L48 _public member_ `static constexpr TCHAR Name[] = TEXT("Rea`

#### struct `UE::Online::FReadEntriesAroundRank::Params`  
`struct Params`  
_L50-60_
- L53 _public member_ `FAccountId LocalAccountId;` — Local user id
- L55 _public member_ `uint32 Rank;` — The rank index to start read
- L57 _public member_ `uint32 Limit;` — How many entries to fetch
- L59 _public member_ `FString BoardName;` — The leaderboard to read

#### struct `UE::Online::FReadEntriesAroundRank::Result`  
`struct Result`  
_L62-66_
- L65 _public member_ `TArray<FLeaderboardEntry> Entries;` — The result leaderboard entries

#### struct `UE::Online::FReadEntriesAroundUser`  
`struct FReadEntriesAroundUser`  
_L69-92_
- L71 _public member_ `static constexpr TCHAR Name[] = TEXT("Rea`

#### struct `UE::Online::FReadEntriesAroundUser::Params`  
`struct Params`  
_L73-85_
- L76 _public member_ `FAccountId LocalAccountId;` — Local user id
- L78 _public member_ `FAccountId AccountId;` — The account id of specified user
- L80 _public member_ `int32 Offset;` — The offset to the rank of user
- L82 _public member_ `uint32 Limit;` — How many entries to fetch
- L84 _public member_ `FString BoardName;` — The leaderboard to read

#### struct `UE::Online::FReadEntriesAroundUser::Result`  
`struct Result`  
_L87-91_
- L90 _public member_ `TArray<FLeaderboardEntry> Entries;` — The result leaderboard entries

#### class `UE::Online::ILeaderboards`  
`class ILeaderboards`  
_L97-118_
- desc: Interface definition for the leaderboards service
- L100 _public prototype_ `virtual ~ILeaderboards() = default;`
- L105 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesForUsers> ReadEntriesForUsers(FReadEntriesForUsers::Params&& Params) = 0;` — Read leaderboard entries for specific users
- L110 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesAroundRank> ReadEntriesAroundRank(FReadEntriesAroundRank::Params&& Params) = 0;` — Read leaderboard entries around specified rank index
- L117 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesAroundUser> ReadEntriesAroundUser(FReadEntriesAroundUser::Params&& Params) = 0;` — Read leaderboard entries around specified user. If the Offset is bigger than the Limit, the user may not appear in the returned entries. It makes sense in situations like getting prev page of users above my rank

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L9 _namespace_ `namespace Meta` (scope `UE::Online`)
- L11 _macro_ `#define UE_LEADERBOARD_RANK_UNKNOWN -1`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L121 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/Lobbies.h` (Public)


#### enum `UE::Online::ELobbyJoinPolicy`  
`enum class ELobbyJoinPolicy : uint8`  
_L15-28_
- L21 _public enumerator_ `PublicAdvertised` — Lobby can be found through searches based on attribute matching, by knowing the lobby id, or by invitation.
- L24 _public enumerator_ `PublicNotAdvertised` — Lobby may be joined by knowing the lobby id or by invitation.
- L27 _public enumerator_ `InvitationOnly` — Lobby may only be joined by invitation.

#### enum `UE::Online::ELobbyMemberLeaveReason`  
`enum class ELobbyMemberLeaveReason`  
_L32-48_
- L35 _public enumerator_ `Left` — The lobby member explicitly left the lobby.
- L38 _public enumerator_ `Kicked` — The lobby member was kicked from the lobby by the lobby owner.
- L41 _public enumerator_ `Disconnected` — The lobby member unexpectedly left.
- L47 _public enumerator_ `Closed` — The lobby was destroyed by the service. All members have left.

#### struct `UE::Online::FLobbyMember`  
`struct FLobbyMember`  
_L52-57_
- L54 _public member_ `FAccountId AccountId;`
- L55 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> Attributes;`
- L56 _public member_ `bool bIsLocalMember = false;`

#### struct `UE::Online::FLobby`  
`struct FLobby`  
_L59-69_
- L61 _public member_ `FLobbyId LobbyId;`
- L62 _public member_ `FAccountId OwnerAccountId;`
- L63 _public member_ `FName LocalName;`
- L64 _public member_ `FSchemaId SchemaId;`
- L65 _public member_ `int32 MaxMembers;`
- L66 _public member_ `ELobbyJoinPolicy JoinPolicy;`
- L67 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> Attributes;`
- L68 _public member_ `TMap<FAccountId, TSharedRef<const FLobbyMember>> Members;`

#### struct `UE::Online::FFindLobbySearchFilter`  
`struct FFindLobbySearchFilter`  
_L71-81_
- L74 _public member_ `FSchemaAttributeId AttributeName;` — The name of the attribute to be compared.
- L77 _public member_ `ESchemaAttributeComparisonOp ComparisonOp;` — The type of comparison to perform.
- L80 _public member_ `FSchemaVariant ComparisonValue;` — Value to use when comparing the attribute.

#### struct `UE::Online::FCreateLobby`  
`struct FCreateLobby`  
_L85-123_
- L87 _public member_ `static constexpr TCHAR Name[] = TEXT("Cre`

#### struct `UE::Online::FCreateLobby::Params`  
`struct Params`  
_L90-115_
- desc: Input struct for Lobbies::CreateLobby
- L93 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L96 _public member_ `FName LocalName;` — The local name for the lobby.
- L99 _public member_ `FSchemaId SchemaId;` — The schema which will be applied to the lobby.
- L102 _public member_ `bool bPresenceEnabled = false;` — Whether this lobby should be set as the user's new presence lobby. False by default
- L105 _public member_ `int32 MaxMembers = 0;` — The maximum number of members who can fit in the lobby.
- L108 _public member_ `ELobbyJoinPolicy JoinPolicy = ELobbyJoinPolicy::InvitationOnly;` — Initial join policy setting.
- L111 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> Attributes;` — Initial attributes.
- L114 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> UserAttributes;` — Initial user attributes.

#### struct `UE::Online::FCreateLobby::Result`  
`struct Result`  
_L118-122_
- desc: Output struct for Lobbies::CreateLobby
- L121 _public member_ `TSharedPtr<const FLobby> Lobby;` — Todo: investigate returning TSharedRef

#### struct `UE::Online::FFindLobbies`  
`struct FFindLobbies`  
_L125-156_
- L127 _public member_ `static constexpr TCHAR Name[] = TEXT("Fin`

#### struct `UE::Online::FFindLobbies::Params`  
`struct Params`  
_L130-149_
- desc: Input struct for Lobbies::FindLobbies
- L133 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L139 _public member_ `uint32 MaxResults = 20;` — Max results to return in one search. Actual count may be smaller based on implementation.
- L142 _public member_ `TArray<FFindLobbySearchFilter> Filters;` — Filters to apply when searching for lobbies.
- L145 _public member_ `TOptional<FAccountId> TargetUser;` — Find lobbies containing the target user.
- L148 _public member_ `TOptional<FLobbyId> LobbyId;` — Find join info for the target lobby id.

#### struct `UE::Online::FFindLobbies::Result`  
`struct Result`  
_L152-155_
- desc: Output struct for Lobbies::FindLobbies
- L154 _public member_ `TArray<TSharedRef<const FLobby>> Lobbies;`

#### struct `UE::Online::FRestoreLobbies`  
`struct FRestoreLobbies`  
_L158-171_
- L160 _public member_ `static constexpr TCHAR Name[] = TEXT("Res`

#### struct `UE::Online::FRestoreLobbies::Params`  
`struct Params`  
_L163-165_
- desc: Input struct for Lobbies::RestoreLobbies

#### struct `UE::Online::FRestoreLobbies::Result`  
`struct Result`  
_L168-170_
- desc: Output struct for Lobbies::RestoreLobbies

#### struct `UE::Online::FJoinLobby`  
`struct FJoinLobby`  
_L173-202_
- L175 _public member_ `static constexpr TCHAR Name[] = TEXT("Joi`

#### struct `UE::Online::FJoinLobby::Params`  
`struct Params`  
_L178-194_
- desc: Input struct for Lobbies::JoinLobby
- L181 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L184 _public member_ `FName LocalName;` — The local name for the lobby.
- L187 _public member_ `FLobbyId LobbyId;` — The id of the lobby to be joined.
- L190 _public member_ `bool bPresenceEnabled = false;` — Whether this lobby should be set as the user's new presence lobby. False by default
- L193 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> UserAttributes;` — Initial user attributes.

#### struct `UE::Online::FJoinLobby::Result`  
`struct Result`  
_L197-201_
- desc: Output struct for Lobbies::JoinLobby
- L200 _public member_ `TSharedPtr<const FLobby> Lobby;` — Todo: investigate returning TSharedRef

#### struct `UE::Online::FLeaveLobby`  
`struct FLeaveLobby`  
_L204-222_
- L206 _public member_ `static constexpr TCHAR Name[] = TEXT("Lea`

#### struct `UE::Online::FLeaveLobby::Params`  
`struct Params`  
_L209-216_
- desc: Input struct for Lobbies::LeaveLobby
- L212 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L215 _public member_ `FLobbyId LobbyId;` — Id of the lobby to leave.

#### struct `UE::Online::FLeaveLobby::Result`  
`struct Result`  
_L219-221_
- desc: Output struct for Lobbies::LeaveLobby

#### struct `UE::Online::FInviteLobbyMember`  
`struct FInviteLobbyMember`  
_L224-245_
- L226 _public member_ `static constexpr TCHAR Name[] = TEXT("Inv`

#### struct `UE::Online::FInviteLobbyMember::Params`  
`struct Params`  
_L229-239_
- desc: Input struct for Lobbies::InviteLobbyMember
- L232 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L235 _public member_ `FLobbyId LobbyId;` — Id of the lobby for which the invitation will be sent.
- L238 _public member_ `FAccountId TargetAccountId;` — Id of the player who will be sent the invitation.

#### struct `UE::Online::FInviteLobbyMember::Result`  
`struct Result`  
_L242-244_
- desc: Output struct for Lobbies::InviteLobbyMember

#### struct `UE::Online::FDeclineLobbyInvitation`  
`struct FDeclineLobbyInvitation`  
_L247-265_
- L249 _public member_ `static constexpr TCHAR Name[] = TEXT("Dec`

#### struct `UE::Online::FDeclineLobbyInvitation::Params`  
`struct Params`  
_L252-259_
- desc: Input struct for Lobbies::DeclineLobbyInvitation
- L255 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L258 _public member_ `FLobbyId LobbyId;` — Id of the lobby for which the invitations will be declined.

#### struct `UE::Online::FDeclineLobbyInvitation::Result`  
`struct Result`  
_L262-264_
- desc: Output struct for Lobbies::DeclineLobbyInvitation

#### struct `UE::Online::FKickLobbyMember`  
`struct FKickLobbyMember`  
_L267-288_
- L269 _public member_ `static constexpr TCHAR Name[] = TEXT("Kic`

#### struct `UE::Online::FKickLobbyMember::Params`  
`struct Params`  
_L272-282_
- desc: Input struct for Lobbies::KickLobbyMember
- L275 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L278 _public member_ `FLobbyId LobbyId;` — Id of the lobby.
- L281 _public member_ `FAccountId TargetAccountId;` — The target user to be kicked.

#### struct `UE::Online::FKickLobbyMember::Result`  
`struct Result`  
_L285-287_
- desc: Output struct for Lobbies::KickLobbyMember

#### struct `UE::Online::FPromoteLobbyMember`  
`struct FPromoteLobbyMember`  
_L290-311_
- L292 _public member_ `static constexpr TCHAR Name[] = TEXT("Pro`

#### struct `UE::Online::FPromoteLobbyMember::Params`  
`struct Params`  
_L295-305_
- desc: Input struct for Lobbies::PromoteLobbyMember
- L298 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L301 _public member_ `FLobbyId LobbyId;` — Id of the lobby.
- L304 _public member_ `FAccountId TargetAccountId;` — The target user to be promoted to owner.

#### struct `UE::Online::FPromoteLobbyMember::Result`  
`struct Result`  
_L308-310_
- desc: Output struct for Lobbies::PromoteLobbyMember

#### struct `UE::Online::FModifyLobbySchema`  
`struct FModifyLobbySchema`  
_L313-326_
- L315 _public member_ `static constexpr TCHAR Name[] = TEXT("Mod`

#### struct `UE::Online::FModifyLobbySchema::Params`  
`struct Params`  
_L318-320_
- desc: Input struct for Lobbies::ModifyLobbySchema

#### struct `UE::Online::FModifyLobbySchema::Result`  
`struct Result`  
_L323-325_
- desc: Output struct for Lobbies::ModifyLobbySchema

#### struct `UE::Online::FModifyLobbyJoinPolicy`  
`struct FModifyLobbyJoinPolicy`  
_L328-349_
- L330 _public member_ `static constexpr TCHAR Name[] = TEXT("Mod`

#### struct `UE::Online::FModifyLobbyJoinPolicy::Params`  
`struct Params`  
_L333-343_
- desc: Input struct for Lobbies::ModifyLobbyJoinPolicy
- L336 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L339 _public member_ `FLobbyId LobbyId;` — Id of the lobby.
- L342 _public member_ `ELobbyJoinPolicy JoinPolicy = ELobbyJoinPolicy::InvitationOnly;` — The new join policy setting.

#### struct `UE::Online::FModifyLobbyJoinPolicy::Result`  
`struct Result`  
_L346-348_
- desc: Output struct for Lobbies::ModifyLobbyJoinPolicy

#### struct `UE::Online::FModifyLobbyAttributes`  
`struct FModifyLobbyAttributes`  
_L351-375_
- L353 _public member_ `static constexpr TCHAR Name[] = TEXT("Mod`

#### struct `UE::Online::FModifyLobbyAttributes::Params`  
`struct Params`  
_L356-369_
- desc: Input struct for Lobbies::ModifyLobbyAttributes
- L359 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L362 _public member_ `FLobbyId LobbyId;` — Id of the lobby.
- L365 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> UpdatedAttributes;` — New or changed lobby attributes.
- L368 _public member_ `TSet<FSchemaAttributeId> RemovedAttributes;` — Attributes to be cleared.

#### struct `UE::Online::FModifyLobbyAttributes::Result`  
`struct Result`  
_L372-374_
- desc: Output struct for Lobbies::ModifyLobbyAttributes

#### struct `UE::Online::FModifyLobbyMemberAttributes`  
`struct FModifyLobbyMemberAttributes`  
_L377-401_
- L379 _public member_ `static constexpr TCHAR Name[] = TEXT("Mod`

#### struct `UE::Online::FModifyLobbyMemberAttributes::Params`  
`struct Params`  
_L382-395_
- desc: Input struct for Lobbies::ModifyLobbyMemberAttributes
- L385 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L388 _public member_ `FLobbyId LobbyId;` — Id of the lobby.
- L391 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> UpdatedAttributes;` — New or changed lobby attributes.
- L394 _public member_ `TSet<FSchemaAttributeId> RemovedAttributes;` — Attributes to be cleared.

#### struct `UE::Online::FModifyLobbyMemberAttributes::Result`  
`struct Result`  
_L398-400_
- desc: Output struct for Lobbies::ModifyLobbyMemberAttributes

#### struct `UE::Online::FGetPresenceLobby`  
`struct FGetPresenceLobby`  
_L403-418_
- L405 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetPresenceLobby::Params`  
`struct Params`  
_L407-411_
- L410 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action

#### struct `UE::Online::FGetPresenceLobby::Result`  
`struct Result`  
_L413-417_
- L416 _public member_ `TSharedRef<const FLobby> Lobby;` — Reference to the lobby set as presence lobby for the given user

#### struct `UE::Online::FIsPresenceLobby`  
`struct FIsPresenceLobby`  
_L420-438_
- L422 _public member_ `static constexpr TCHAR Name[] = TEXT("IsP`

#### struct `UE::Online::FIsPresenceLobby::Params`  
`struct Params`  
_L424-431_
- L427 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action
- L430 _public member_ `FLobbyId LobbyId;` — Id handle for the lobby to be compared

#### struct `UE::Online::FIsPresenceLobby::Result`  
`struct Result`  
_L433-437_
- L436 _public member_ `bool bIsPresenceLobby;` — Whether the lobby mapped to the given id is set as the presence lobby for the given user

#### struct `UE::Online::FGetJoinedLobbies`  
`struct FGetJoinedLobbies`  
_L440-456_
- L442 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetJoinedLobbies::Params`  
`struct Params`  
_L445-449_
- desc: Input struct for Lobbies::GetJoinedLobbies
- L448 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.

#### struct `UE::Online::FGetJoinedLobbies::Result`  
`struct Result`  
_L452-455_
- desc: Output struct for Lobbies::GetJoinedLobbies
- L454 _public member_ `TArray<TSharedRef<const FLobby>> Lobbies;`

#### struct `UE::Online::FGetReceivedInvitations`  
`struct FGetReceivedInvitations`  
_L458-473_
- L460 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetReceivedInvitations::Params`  
`struct Params`  
_L463-467_
- desc: Input struct for Lobbies::GetReceivedInvitations
- L466 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.

#### struct `UE::Online::FGetReceivedInvitations::Result`  
`struct Result`  
_L470-472_
- desc: Output struct for Lobbies::GetReceivedInvitations

#### struct `UE::Online::FLobbyJoined`  
`struct FLobbyJoined`  
_L476-480_
- desc: Struct for LobbyJoined event
- L479 _public member_ `TSharedRef<const FLobby> Lobby;` — Lobby data access.

#### struct `UE::Online::FLobbyLeft`  
`struct FLobbyLeft`  
_L483-487_
- desc: Struct for LobbyLeft event
- L486 _public member_ `TSharedRef<const FLobby> Lobby;` — Lobby data access.

#### struct `UE::Online::FLobbyMemberJoined`  
`struct FLobbyMemberJoined`  
_L490-497_
- desc: Struct for LobbyMemberJoined event
- L493 _public member_ `TSharedRef<const FLobby> Lobby;` — Lobby data access.
- L496 _public member_ `TSharedRef<const FLobbyMember> Member;` — Member data access.

#### struct `UE::Online::FLobbyMemberLeft`  
`struct FLobbyMemberLeft`  
_L500-510_
- desc: Struct for LobbyMemberLeft event
- L503 _public member_ `TSharedRef<const FLobby> Lobby;` — Lobby data access.
- L506 _public member_ `TSharedRef<const FLobbyMember> Member;` — Member data access.
- L509 _public member_ `ELobbyMemberLeaveReason Reason;` — Context for the member leaving.

#### struct `UE::Online::FLobbyLeaderChanged`  
`struct FLobbyLeaderChanged`  
_L513-520_
- desc: Struct for LobbyLeaderChanged event
- L516 _public member_ `TSharedRef<const FLobby> Lobby;` — Lobby data access.
- L519 _public member_ `TSharedRef<const FLobbyMember> Leader;` — Leader data access.

#### struct `UE::Online::FLobbySchemaChanged`  
`struct FLobbySchemaChanged`  
_L523-531_
- desc: Struct for LobbySchemaChanged event
- L526 _public member_ `TSharedRef<const FLobby> Lobby;` — Lobby data access.
- L528 _public member_ `FSchemaId PreviousSchemaId;` — The previous schema id.
- L530 _public member_ `FSchemaId NewSchemaId;` — The new schema id.

#### struct `UE::Online::FLobbyAttributesChanged`  
`struct FLobbyAttributesChanged`  
_L534-548_
- desc: Struct for LobbyAttributesChanged event
- L537 _public member_ `TSharedRef<const FLobby> Lobby;` — Lobby data access.
- L540 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> AddedAttributes;` — Added attributes.
- L543 _public member_ `TMap<FSchemaAttributeId, TPair<FSchemaVariant, FSchemaVariant>> ChangedAttributes;` — Changed attributes with their old and new values.
- L546 _public member_ `TSet<FSchemaAttributeId> RemovedAttributes;` — Removed attribute ids.

#### struct `UE::Online::FLobbyMemberAttributesChanged`  
`struct FLobbyMemberAttributesChanged`  
_L551-567_
- desc: Struct for LobbyMemberAttributesChanged event
- L554 _public member_ `TSharedRef<const FLobby> Lobby;` — Lobby data access.
- L557 _public member_ `TSharedRef<const FLobbyMember> Member;` — Member data access.
- L560 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> AddedAttributes;` — Added attributes.
- L563 _public member_ `TMap<FSchemaAttributeId, TPair<FSchemaVariant, FSchemaVariant>> ChangedAttributes;` — Changed attributes with their old and new values.
- L566 _public member_ `TSet<FSchemaAttributeId> RemovedAttributes;` — Removed attribute ids.

#### struct `UE::Online::FLobbyInvitationAdded`  
`struct FLobbyInvitationAdded`  
_L570-580_
- desc: Struct for LobbyInvitationAdded event
- L573 _public member_ `FAccountId LocalAccountId;` — The local user associated with the invitation.
- L576 _public member_ `FAccountId SenderId;` — The user who sent the invitation.
- L579 _public member_ `TSharedRef<const FLobby> Lobby;` — The invited lobby.

#### struct `UE::Online::FLobbyInvitationRemoved`  
`struct FLobbyInvitationRemoved`  
_L583-594_
- desc: Struct for LobbyInvitationRemoved event
- L586 _public member_ `FAccountId LocalAccountId;` — The local user associated with the invitation.
- L589 _public member_ `FAccountId SenderId;` — The user who sent the invitation.
- L592 _public member_ `TSharedRef<const FLobby> Lobby;` — The invited lobby.

#### enum `UE::Online::EUILobbyJoinRequestedSource`  
`enum class EUILobbyJoinRequestedSource : uint8`  
_L597-603_
- desc: Lobby join requested source
- L600 _public enumerator_ `Unspecified` — Unspecified by the online service
- L602 _public enumerator_ `FromInvitation` — From an invitation

#### struct `UE::Online::FUILobbyJoinRequested`  
`struct FUILobbyJoinRequested`  
_L608-618_
- desc: Struct for UILobbyJoinedRequested event
- L611 _public member_ `FAccountId LocalAccountId;` — The local user associated with the join request.
- L614 _public member_ `TResult<TSharedRef<const FLobby>, FOnlineError> Result;` — The lobby if the local user requested to join, or the online error if there was a failure
- L617 _public member_ `EUILobbyJoinRequestedSource JoinRequestedSource = EUILobbyJoinRequestedSource::Unspecified;` — Join request source

#### class `UE::Online::ILobbies`  
`class ILobbies`  
_L620-860_
- L623 _public prototype_ `virtual ~ILobbies() = default;`
- L634 _public prototype_ `virtual TOnlineAsyncOpHandle<FCreateLobby> CreateLobby(FCreateLobby::Params&& Params) = 0;` — Create and join a new lobby. @param Params for the CreateLobby call @return
- L642 _public prototype_ `virtual TOnlineAsyncOpHandle<FFindLobbies> FindLobbies(FFindLobbies::Params&& Params) = 0;` — Search for lobbies using filtering parameters. @param Params for the FindLobby call @return
- L650 _public prototype_ `virtual TOnlineAsyncOpHandle<FRestoreLobbies> RestoreLobbies(FRestoreLobbies::Params&& Params) = 0;` — Try to rejoin previously joined lobbies. @param Params for the RestoreLobbies call @return
- L658 _public prototype_ `virtual TOnlineAsyncOpHandle<FJoinLobby> JoinLobby(FJoinLobby::Params&& Params) = 0;` — Join a lobby using its id. @param Params for the JoinLobby call @return
- L666 _public prototype_ `virtual TOnlineAsyncOpHandle<FLeaveLobby> LeaveLobby(FLeaveLobby::Params&& Params) = 0;` — Leave a joined lobby. @param Params for the LeaveLobby call @return
- L674 _public prototype_ `virtual TOnlineAsyncOpHandle<FInviteLobbyMember> InviteLobbyMember(FInviteLobbyMember::Params&& Params) = 0;` — Invite a player to join a lobby. @param Params for the InviteLobbyMember call @return
- L682 _public prototype_ `virtual TOnlineAsyncOpHandle<FDeclineLobbyInvitation> DeclineLobbyInvitation(FDeclineLobbyInvitation::Params&& Params) = 0;` — Decline an invitation to join a lobby. @param Params for the DeclineLobbyInvitation call @return
- L690 _public prototype_ `virtual TOnlineAsyncOpHandle<FKickLobbyMember> KickLobbyMember(FKickLobbyMember::Params&& Params) = 0;` — Kick a member from a the target lobby. @param Params for the KickLobbyMember call @return
- L699 _public prototype_ `virtual TOnlineAsyncOpHandle<FPromoteLobbyMember> PromoteLobbyMember(FPromoteLobbyMember::Params&& Params) = 0;` — Promote another lobby member to leader. The local user must be the current lobby leader to promote another member. @param Params for the PromoteLobbyMember call @return
- L712 _public prototype_ `virtual TOnlineAsyncOpHandle<FModifyLobbySchema> ModifyLobbySchema(FModifyLobbySchema::Params&& Params) = 0;` — Change the schema applied to the lobby and member attributes. Only the lobby leader may change the schema. Existing attributes not present in the new schema will be cleared. @param Params for the ModifyLobbySchema call @return
- L721 _public prototype_ `virtual TOnlineAsyncOpHandle<FModifyLobbyJoinPolicy> ModifyLobbyJoinPolicy(FModifyLobbyJoinPolicy::Params&& Params) = 0;` — Change the join policy applied to the lobby. Only the lobby leader may change the join policy. @param Params for the ModifyLobbyJoinPolicy call @return
- L731 _public prototype_ `virtual TOnlineAsyncOpHandle<FModifyLobbyAttributes> ModifyLobbyAttributes(FModifyLobbyAttributes::Params&& Params) = 0;` — Change the attributes applied to the lobby. Only the lobby leader may change the lobby attributes. Attributes are validated against the lobby schema before an update can succeed. @param Params for the ModifyLobbyAttributes call @return
- L741 _public prototype_ `virtual TOnlineAsyncOpHandle<FModifyLobbyMemberAttributes> ModifyLobbyMemberAttributes(FModifyLobbyMemberAttributes::Params&& Params) = 0;` — Change the attributes applied to a lobby member. Lobby members may only change their own attributes. Attributes are validated against the lobby schema before an update can succeed. @param Params for the ModifyLobbyAttributes call @return
- L752 _public prototype_ `virtual TOnlineResult<FGetPresenceLobby> GetPresenceLobby(FGetPresenceLobby::Params&& Params) = 0;` — Retrieve the presence Lobby for the given user, if any is set @params Params for the GetPresenceLobby call @return
- L760 _public prototype_ `virtual TOnlineResult<FIsPresenceLobby> IsPresenceLobby(FIsPresenceLobby::Params&& Params) = 0;` — Return whether the Lobby with the given id is set as presence lobby for the given user @params Params for the IsPresenceLobby call @return
- L768 _public prototype_ `virtual TOnlineResult<FGetJoinedLobbies> GetJoinedLobbies(FGetJoinedLobbies::Params&& Params) = 0;` — Retrieve the list of joined lobbies for the target local user. @param Params for the GetJoinedLobbies call @return
- L776 _public prototype_ `virtual TOnlineResult<FGetReceivedInvitations> GetReceivedInvitations(FGetReceivedInvitations::Params&& Params) = 0;` — Retrieve the list of received invitations for the target local user. @param Params for the GetJoinedLobbies call @return
- L787 _public prototype_ `virtual TOnlineEvent<void(const FLobbyJoined&)> OnLobbyJoined() = 0;` — Get the event that is triggered when a lobby is joined. This will happen as a result of creating or joining a lobby. @return Event that can be bound to
- L794 _public prototype_ `virtual TOnlineEvent<void(const FLobbyLeft&)> OnLobbyLeft() = 0;` — Get the event that is triggered when a lobby has been left by all local members. @return Event that can be bound to
- L803 _public prototype_ `virtual TOnlineEvent<void(const FLobbyMemberJoined&)> OnLobbyMemberJoined() = 0;` — Get the event that is triggered when a lobby member joins. This will happen as a result of creating or joining a lobby for local users, and will trigger when a remote user joins. @return Event that can be bound to
- L810 _public prototype_ `virtual TOnlineEvent<void(const FLobbyMemberLeft&)> OnLobbyMemberLeft() = 0;` — Get the event that is triggered when a lobby member leaves a joined lobby. @return Event that can be bound to
- L817 _public prototype_ `virtual TOnlineEvent<void(const FLobbyLeaderChanged&)> OnLobbyLeaderChanged() = 0;` — Get the event that is triggered when the leadership of a lobby changes. @return Event that can be bound to
- L824 _public prototype_ `virtual TOnlineEvent<void(const FLobbySchemaChanged&)> OnLobbySchemaChanged() = 0;` — Get the event that is triggered when the attribute schema of a lobby changes. @return Event that can be bound to
- L831 _public prototype_ `virtual TOnlineEvent<void(const FLobbyAttributesChanged&)> OnLobbyAttributesChanged() = 0;` — Get the event that is triggered when lobby attributes have changed. @return Event that can be bound to
- L838 _public prototype_ `virtual TOnlineEvent<void(const FLobbyMemberAttributesChanged&)> OnLobbyMemberAttributesChanged() = 0;` — Get the event that is triggered when lobby member attributes have changed. @return Event that can be bound to
- L845 _public prototype_ `virtual TOnlineEvent<void(const FLobbyInvitationAdded&)> OnLobbyInvitationAdded() = 0;` — Get the event that is triggered when an invitation is received. @return Event that can be bound to
- L852 _public prototype_ `virtual TOnlineEvent<void(const FLobbyInvitationRemoved&)> OnLobbyInvitationRemoved() = 0;` — Get the event that is triggered when an invitation is removed. @return Event that can be bound to
- L859 _public prototype_ `virtual TOnlineEvent<void(const FUILobbyJoinRequested&)> OnUILobbyJoinRequested() = 0;` — Get the event that is triggered when a join is requested through an external mechanism. @return Event that can be bound to

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L29 _prototype_ `const TCHAR* LexToString(ELobbyJoinPolicy Policy);` (scope `UE::Online`)
- L30 _prototype_ `void LexFromString(ELobbyJoinPolicy& OutPolicy, const TCHAR* InStr);` (scope `UE::Online`)
- L49 _prototype_ `const TCHAR* LexToString(ELobbyMemberLeaveReason LeaveReason);` (scope `UE::Online`)
- L50 _prototype_ `void LexFromString(ELobbyMemberLeaveReason& OutLeaveReason, const TCHAR* InStr);` (scope `UE::Online`)
- L83 _prototype_ `void SortLobbies(const TArray<FFindLobbySearchFilter>& Filters, TArray<TSharedRef<const FLobby>>& Lobbies);` (scope `UE::Online`)
- L604 _prototype_ `const TCHAR* LexToString(EUILobbyJoinRequestedSource UILobbyJoinRequestedSource);` (scope `UE::Online`)
- L605 _prototype_ `void LexFromString(EUILobbyJoinRequestedSource& OutUILobbyJoinRequestedSource, const TCHAR* InStr);` (scope `UE::Online`)
- L862 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/OnlineAsyncOpHandle.h` (Public)


#### struct `UE::Online::Private::CAsSharedCallable`  
`struct CAsSharedCallable`  
_L17-21_
- L20 _public prototype_ `template <typename T> auto Requires(T&& Object) -> decltype(Object->AsShared());`

#### struct `UE::Online::Private::TIsSharedPtrOrRef`  
`template <typename T> struct TIsSharedPtrOrRef`  
_L24-27_
- L26 _public member_ `static inline constexpr bool value = false;`
- L32 _public member_ `static inline constexpr bool value = true;`

#### struct `UE::Online::Private::TIsSharedPtrOrRef`  
`template <typename T, ESPMode SPMode> struct TIsSharedPtrOrRef<TSharedPtr<T, SPMode>>`  
_L30-33_
- L26 _public member_ `static inline constexpr bool value = false;`
- L32 _public member_ `static inline constexpr bool value = true;`

#### struct `UE::Online::Private::TIsSharedPtrOrRef`  
`template <typename T, ESPMode SPMode> struct TIsSharedPtrOrRef<TSharedRef<T, SPMode>>`  
_L36-39_
- L26 _public member_ `static inline constexpr bool value = false;`
- L32 _public member_ `static inline constexpr bool value = true;`

#### struct `UE::Online::Private::TSharedPtrHelper`  
`template <typename ObjectType, typename = void> struct TSharedPtrHelper`  
_L42-46_
- L44 _public member_ `static inline constexpr bool bIsThreadSafe = false;`
- L45 _public member_ `static inline constexpr bool bIsSharedPtr = false;`

#### struct `UE::Online::Private::TSharedPtrHelper2`  
`template <typename T> struct TSharedPtrHelper2`  
_L49-56_
- L51 _public typedef_ `using PtrType = decltype(((std::remove_pointer_t<T>*)nullptr)->AsShared());`
- L52 _public member_ `static inline constexpr bool bIsThreadSafe = TSharedPtrHelper<PtrType>::bIsThreadSafe;`
- L53 _public member_ `static inline constexpr bool bIsSharedPtr = true;`
- L54 _public typedef_ `using WeakPtrType = typename TSharedPtrHelper<PtrType>::WeakPtrType;`
- L55 _public function_ `static inline WeakPtrType GetWeak(T Ptr)`
- L61 _public member_ `static inline constexpr bool bIsThreadSafe = SPMode == ESPMode::ThreadSafe;`
- L63 _public typedef_ `using WeakPtrType = TWeakPtr<T, SPMode>;`
- L64 _public function_ `static inline WeakPtrType GetWeak(const TSharedPtr<T, SPMode>& Ptr)`
- L73 _public function_ `static inline WeakPtrType GetWeak(const TSharedRef<T, SPMode>& Ptr)`

#### struct `UE::Online::Private::TSharedPtrHelper2`  
`template <typename T, ESPMode SPMode> struct TSharedPtrHelper2<TSharedPtr<T, SPMode>>`  
_L59-65_
- L51 _public typedef_ `using PtrType = decltype(((std::remove_pointer_t<T>*)nullptr)->AsShared());`
- L52 _public member_ `static inline constexpr bool bIsThreadSafe = TSharedPtrHelper<PtrType>::bIsThreadSafe;`
- L53 _public member_ `static inline constexpr bool bIsSharedPtr = true;`
- L54 _public typedef_ `using WeakPtrType = typename TSharedPtrHelper<PtrType>::WeakPtrType;`
- L55 _public function_ `static inline WeakPtrType GetWeak(T Ptr)`
- L61 _public member_ `static inline constexpr bool bIsThreadSafe = SPMode == ESPMode::ThreadSafe;`
- L63 _public typedef_ `using WeakPtrType = TWeakPtr<T, SPMode>;`
- L64 _public function_ `static inline WeakPtrType GetWeak(const TSharedPtr<T, SPMode>& Ptr)`
- L73 _public function_ `static inline WeakPtrType GetWeak(const TSharedRef<T, SPMode>& Ptr)`

#### struct `UE::Online::Private::TSharedPtrHelper2`  
`template <typename T, ESPMode SPMode> struct TSharedPtrHelper2<TSharedRef<T, SPMode>>`  
_L68-74_
- L51 _public typedef_ `using PtrType = decltype(((std::remove_pointer_t<T>*)nullptr)->AsShared());`
- L52 _public member_ `static inline constexpr bool bIsThreadSafe = TSharedPtrHelper<PtrType>::bIsThreadSafe;`
- L53 _public member_ `static inline constexpr bool bIsSharedPtr = true;`
- L54 _public typedef_ `using WeakPtrType = typename TSharedPtrHelper<PtrType>::WeakPtrType;`
- L55 _public function_ `static inline WeakPtrType GetWeak(T Ptr)`
- L61 _public member_ `static inline constexpr bool bIsThreadSafe = SPMode == ESPMode::ThreadSafe;`
- L63 _public typedef_ `using WeakPtrType = TWeakPtr<T, SPMode>;`
- L64 _public function_ `static inline WeakPtrType GetWeak(const TSharedPtr<T, SPMode>& Ptr)`
- L73 _public function_ `static inline WeakPtrType GetWeak(const TSharedRef<T, SPMode>& Ptr)`

#### struct `UE::Online::Private::TSharedPtrHelper`  
`template <typename T> struct TSharedPtrHelper<T, std::enable_if_t<TModels_V<CAsSharedCallable, T> && !TIsSharedPtrOrRef<T>::value, void>> : public TSharedPtrHelper2<T>`  
_L77-79_
- inherits: `TSharedPtrHelper2<T>`
- L44 _public member_ `static inline constexpr bool bIsThreadSafe = false;`
- L45 _public member_ `static inline constexpr bool bIsSharedPtr = false;`

#### struct `UE::Online::Private::TSharedPtrHelper`  
`template <typename T, ESPMode SPMode> struct TSharedPtrHelper<TSharedPtr<T, SPMode>, void> : public TSharedPtrHelper2<TSharedPtr<T, SPMode>>`  
_L82-84_
- inherits: `TSharedPtrHelper2<TSharedPtr<T,SPMode>>`
- L44 _public member_ `static inline constexpr bool bIsThreadSafe = false;`
- L45 _public member_ `static inline constexpr bool bIsSharedPtr = false;`

#### struct `UE::Online::Private::TSharedPtrHelper`  
`template <typename T, ESPMode SPMode> struct TSharedPtrHelper<TSharedRef<T, SPMode>, void> : public TSharedPtrHelper2<TSharedRef<T, SPMode>>`  
_L87-89_
- inherits: `TSharedPtrHelper2<TSharedRef<T,SPMode>>`
- L44 _public member_ `static inline constexpr bool bIsThreadSafe = false;`
- L45 _public member_ `static inline constexpr bool bIsSharedPtr = false;`

#### class `UE::Online::TOnlineCallback`  
`template<typename DelegateSignature> class TOnlineCallback`  
_L174-178_
- L177 _private member_ `TDelegate<DelegateSignature> Delegate;` — Will hit TDelegate's static_asserts
- L187 _public typedef_ `using DelegateSignature = InRetValType(ParamTypes...);`
- L193 _public function_ `template<typename... ConstructDelegateParamTypes> void Bind(ConstructDelegateParamTypes&&... Params)`
- L201 _public function_ `void Unbind()`
- L209 _public function_ `void ExecuteIfBound(ParamTypes&&... Params)`

#### class `UE::Online::TOnlineCallback`  
`template <typename InRetValType, typename... ParamTypes> class TOnlineCallback<InRetValType(ParamTypes...)>`  
_L184-216_
- L177 _private member_ `TDelegate<DelegateSignature> Delegate;` — Will hit TDelegate's static_asserts
- L187 _public typedef_ `using DelegateSignature = InRetValType(ParamTypes...);`
- L193 _public function_ `template<typename... ConstructDelegateParamTypes> void Bind(ConstructDelegateParamTypes&&... Params)`
- L201 _public function_ `void Unbind()`
- L209 _public function_ `void ExecuteIfBound(ParamTypes&&... Params)`

#### class `UE::Online::FOnlineEventDelegateHandle`  
`class FOnlineEventDelegateHandle`  
_L221-279_
- L224 _public prototype_ `FOnlineEventDelegateHandle() = default;`
- L225 _public function_ `FOnlineEventDelegateHandle(FOnlineEventDelegateHandle&& Other)`
- L230 _public function_ `FOnlineEventDelegateHandle& operator=(FOnlineEventDelegateHandle&& Other)`
- L241 _public function_ `template <typename DelegateSignature> FOnlineEventDelegateHandle(FDelegateHandle Handle, TSharedRef<TMulticastDelegate<DelegateSignature>>& DelegateRef)`
- L257 _public function_ `~FOnlineEventDelegateHandle()`
- L265 _public function_ `void Unbind()`
- L275 _private prototype_ `FOnlineEventDelegateHandle(const FOnlineEventDelegateHandle&) = delete;`
- L276 _private prototype_ `FOnlineEventDelegateHandle& operator=(const FOnlineEventDelegateHandle&) = delete;`
- L278 _private member_ `TUniqueFunction<void()> DelegateUnbinder;`

#### class `UE::Online::TOnlineEventCallable`  
`template<typename DelegateSignature> class TOnlineEventCallable`  
_L282-286_
- L285 _private member_ `TMulticastDelegate<DelegateSignature> Delegate;` — Will hit TMulticastDelegate's static_asserts
- L295 _public typedef_ `using DelegateSignature = void(ParamTypes...);`
- L300 _public function_ `TOnlineEventCallable() : DelegateRef(MakeShared<TMulticastDelegate<DelegateSignature>>())`
- L309 _public function_ `template<typename... ConstructDelegateParamTypes> FOnlineEventDelegateHandle Add(ConstructDelegateParamTypes&&... Params)`
- L315 _public function_ `void Clear()`
- L323 _public function_ `void Broadcast(ParamTypes&&... Params)`
- L329 _private member_ `TSharedRef<TMulticastDelegate<DelegateSignature>> DelegateRef;`

#### class `UE::Online::TOnlineEventCallable`  
`template <typename... ParamTypes> class TOnlineEventCallable<void(ParamTypes...)>`  
_L292-330_
- L285 _private member_ `TMulticastDelegate<DelegateSignature> Delegate;` — Will hit TMulticastDelegate's static_asserts
- L295 _public typedef_ `using DelegateSignature = void(ParamTypes...);`
- L300 _public function_ `TOnlineEventCallable() : DelegateRef(MakeShared<TMulticastDelegate<DelegateSignature>>())`
- L309 _public function_ `template<typename... ConstructDelegateParamTypes> FOnlineEventDelegateHandle Add(ConstructDelegateParamTypes&&... Params)`
- L315 _public function_ `void Clear()`
- L323 _public function_ `void Broadcast(ParamTypes&&... Params)`
- L329 _private member_ `TSharedRef<TMulticastDelegate<DelegateSignature>> DelegateRef;`

#### class `UE::Online::TOnlineEvent`  
`template <typename DelegateSignature> class TOnlineEvent`  
_L336-358_
- L342 _public function_ `TOnlineEvent(TOnlineEventCallable<DelegateSignature>& InEvent) : Event(InEvent)`
- L351 _public function_ `template<typename... ConstructDelegateParamTypes> [[nodiscard]] FOnlineEventDelegateHandle Add(ConstructDelegateParamTypes&&... Params)`
- L357 _private member_ `TOnlineEventCallable<DelegateSignature>& Event;`

#### enum `UE::Online::EAsyncOpState`  
`enum class EAsyncOpState : uint8`  
_L360-368_
- L362 _public enumerator_ `Invalid`
- L363 _public enumerator_ `Queued`
- L364 _public enumerator_ `Running`
- L365 _public enumerator_ `RetryQueued`
- L366 _public enumerator_ `Complete`
- L367 _public enumerator_ `Cancelled`

#### class `UE::Online::IOnlineAsyncOp`  
`class IOnlineAsyncOp`  
_L384-392_
- L387 _public prototype_ `virtual ~IOnlineAsyncOp() = default;`
- L389 _public prototype_ `virtual void Cancel() = 0;`
- L390 _public prototype_ `virtual EAsyncOpState GetState() const = 0;`
- L391 _public prototype_ `virtual void DetachHandle(class IAsyncHandle* Handle) = 0;`

#### struct `UE::Online::FAsyncProgress`  
`struct FAsyncProgress`  
_L394-404_
- L397 _public member_ `const FString Step;` — Step that is running
- L399 _public member_ `double Progress;` — How much has been completed
- L401 _public member_ `double MaxProgress;` — How much total there is to do
- L403 _public member_ `FText ProgressMessage;` — Localized message suitable for showing to end user

#### struct `UE::Online::FWillRetry`  
`struct FWillRetry`  
_L406-412_
- L408 _public member_ `FOnlineError Reason;`
- L409 _public member_ `double RetryInSeconds;`
- L410 _public member_ `int RetryAttempt;`
- L411 _public member_ `int MaxRetryAttempts;`

#### class `UE::Online::Private::IOnlineAsyncOpSharedState`  
`template <typename OpType> class IOnlineAsyncOpSharedState`  
_L420-429_
- desc: State shared between the Op and Handle
- L423 _public prototype_ `virtual ~IOnlineAsyncOpSharedState() = default;`
- L424 _public prototype_ `virtual void Cancel(const FOnlineError& Reason) = 0;`
- L425 _public prototype_ `virtual EAsyncOpState GetState() const = 0;`
- L426 _public prototype_ `virtual void SetOnProgress(TDelegate<void(const FAsyncProgress&)>&& Delegate) = 0;`
- L427 _public prototype_ `virtual void SetOnWillRetry(TDelegate<void(TOnlineAsyncOpHandle<OpType>&, const FWillRetry&)>&& Delegate) = 0;`
- L428 _public prototype_ `virtual void SetOnComplete(TDelegate<void(const TOnlineResult<OpType>&)>&& Delegate) = 0;`

#### class `UE::Online::TOnlineAsyncOpHandle`  
`template <typename OpType> class TOnlineAsyncOpHandle`  
_L436-517_
- L442 _public function_ `TOnlineAsyncOpHandle(TSharedRef<Private::IOnlineAsyncOpSharedState<OpType>>&& InSharedState) : State(MoveTemp(InSharedState))`
- L460 _public function_ `template <typename... ArgTypes> TOnlineAsyncOpHandle& OnProgress(ArgTypes&&... Args)` — @param @return The async op handle
- L474 _public function_ `template <typename... ArgTypes> TOnlineAsyncOpHandle& OnWillRetry(ArgTypes&&... Args)` — @param @return The async op handle
- L488 _public function_ `template <typename... ArgTypes> TOnlineAsyncOpHandle& OnComplete(ArgTypes&&... Args)` — @param @return The async op handle
- L500 _public function_ `void Cancel(const FOnlineError& Reason = Errors::Cancelled())` — Cancel the operation @param Reason Allows a more specific reson why the operation is cancelled to be specified
- L510 _public function_ `EAsyncOpState GetState() const` — Get the state of the operation @return The state of the operation
- L516 _private member_ `TSharedPtr<Private::IOnlineAsyncOpSharedState<OpType>> State;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Online`)
- L92 _function_ `template <typename DelegateSignature, typename CallableType, typename... VarTypes> TDelegate<DelegateSignature> ConstructFunctionDelegate(CallableType&& Callable, VarTypes&&... Vars)` (scope `UE::Online::Private`)
- L105 _function_ `template <typename DelegateSignature, typename ObjectType, typename CallableType, typename... VarTypes> TDelegate<DelegateSignature> ConstructObjectDelegate(ObjectType Object, CallableType&& Callable, VarTypes&&... Vars)` (scope `UE::Online::Private`)
- L147 _function_ `` (scope `UE::Online::Private::ConstructObjectDelegate`)
- L159 _function_ `template <typename DelegateSignature, typename ObjectOrCallableType, typename... VarTypes> [[nodiscard]] inline TDelegate<DelegateSignature> ConstructDelegate(ObjectOrCallableType&& ObjectOrCallable, VarTypes&&... Vars)` (scope `UE::Online::Private`)
- L244 _function_ `` (scope `UE::Online::FOnlineEventDelegateHandle::FOnlineEventDelegateHandle`)
- L370 _function_ `inline const TCHAR* LexToString(EAsyncOpState Value)` (scope `UE::Online`)
- L416 _namespace_ `namespace Private` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/OnlineError.h` (Public)


#### class `UE::Online::IOnlineErrorDetails`  
`class IOnlineErrorDetails`  
_L14-22_
- desc: Implementations of this would contain any contextual information about the error (eg, if an FText or FString exposed some fields to be filled in at run time), and likely the platform specific error representation (eg, NSError on apple that we can use to get a string to display to user and a string to log)
- L17 _public prototype_ `virtual ~IOnlineErrorDetails() = default;`
- L19 _public prototype_ `virtual FString GetFriendlyErrorCode(const FOnlineError&) const = 0;`
- L20 _public prototype_ `virtual FText GetText(const FOnlineError&) const = 0;`
- L21 _public prototype_ `virtual FString GetLogString(const FOnlineError&) const = 0;`

#### class `UE::Online::FOnlineErrorDetails`  
`class FOnlineErrorDetails : public IOnlineErrorDetails`  
_L24-59_
- inherits: `IOnlineErrorDetails`
- L27 _public function_ `FOnlineErrorDetails(FString&& InFriendlyErrorCode, FString&& InLogString, FText&& InText) : FriendlyErrorCode(MoveTemp(InFriendlyErrorCode)) , LogString(MoveTemp(InLogString)) , Text(MoveTemp(InText))`
- L34 _public prototype_ `virtual ~FOnlineErrorDetails() = default;`
- L36 _public function_ `virtual FString GetFriendlyErrorCode(const FOnlineError&) const override`
- L41 _public function_ `virtual FString GetLogString(const FOnlineError&) const override`
- L46 _public function_ `virtual FText GetText(const FOnlineError&) const override`
- L52 _protected function_ `FOnlineErrorDetails()`
- L56 _protected member_ `FString FriendlyErrorCode;`
- L57 _protected member_ `FString LogString;`
- L58 _protected member_ `FText Text;`

#### class `UE::Online::FOnlineError`  
`class FOnlineError`  
_L64-193_
- L67 _public function_ `explicit FOnlineError(ErrorCodeType InErrorCode, TSharedPtr<const IOnlineErrorDetails, ESPMode::ThreadSafe> InDetails = nullptr, TSharedPtr<const FOnlineError, ESPMode::ThreadSafe> InInner = nullptr) : Details(InDetails) , Inner(InInner) , ErrorCode(InErrorCode)`
- L73 _public prototype_ `explicit FOnlineError(bool) = delete;`
- L75 _public function_ `FText GetText() const`
- L87 _public function_ `FString GetLogString(bool bIncludePrefix = true) const`
- L128 _public function_ `FString GetErrorId() const`
- L142 _public function_ `FString GetFriendlyErrorCode() const`
- L154 _public function_ `const FOnlineError* GetInner() const`
- L159 _public function_ `const IOnlineErrorDetails* GetErrorDetails() const`
- L164 _public function_ `ErrorCodeType GetSystem() const`
- L169 _public function_ `ErrorCodeType GetCategory() const`
- L174 _public function_ `ErrorCodeType GetValue() const`
- L179 _public function_ `ErrorCodeType GetErrorCode() const`
- L184 _public prototype_ `bool IsSuccess() const;`
- L188 _private member_ `TSharedPtr<const IOnlineErrorDetails, ESPMode::ThreadSafe> Details;` — TSharedPtr instead of TUniquePtr so that we can copy errors easily
- L189 _private member_ `TSharedPtr<const FOnlineError, ESPMode::ThreadSafe> Inner;`
- L190 _private member_ `ErrorCodeType ErrorCode;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Online` (scope `UE`)
- L9 _typedef_ `using ErrorCodeType = uint64;` (scope `UE::Online`)
- L11 _macro_ `#define LOCTEXT_NAMESPACE "OnlineError"`
- L200 _prototype_ `bool operator==(const FOnlineError& Lhs, const FOnlineError& Rhs);` (scope `UE::Online`) — the comparison with ErrorCodeType is the one I would expect to see in almost every case
- L201 _function_ `inline bool operator!=(const FOnlineError& Lhs, const FOnlineError& Rhs)` (scope `UE::Online`)
- L202 _prototype_ `bool operator==(const FOnlineError& OnlineError, ErrorCodeType OtherErrorCode);` (scope `UE::Online`)
- L203 _function_ `inline bool operator==(ErrorCodeType OtherErrorCode, const FOnlineError& OnlineError)` (scope `UE::Online`)
- L204 _function_ `inline bool operator!=(const FOnlineError& OnlineError, ErrorCodeType OtherErrorCode)` (scope `UE::Online`)
- L205 _function_ `inline bool operator!=(ErrorCodeType OtherErrorCode, const FOnlineError& OnlineError)` (scope `UE::Online`)
- L207 _function_ `inline FString ToLogString(const FOnlineError& Error)` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/OnlineErrorCode.h` (Public)


#### struct `UE::Online::Errors::FOnlineErrorCode`  
`struct FOnlineErrorCode`  
_L15-20_
- desc: error code as struct with bitfields
- L17 _public member_ `uint64 System : 4;` — Engine, Game, Third Party Plugin
- L18 _public member_ `uint64 Category : 28;` — HRESULT, Http, nn::Result, etc
- L19 _public member_ `uint64 Code : 32;` — HRESULT value, Http status code, nn::Result underlying int value, etc

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace Errors` (scope `UE::Online`)
- L11 _typedef_ `using ErrorCodeType = uint64;` (scope `UE::Online::Errors`)
- L22 _namespace_ `namespace ErrorCode` (scope `UE::Online::Errors`)
- L24 _prototype_ `FString ToString(ErrorCodeType ErrorCode);` (scope `UE::Online::Errors::ErrorCode`)
- L25 _prototype_ `TOptional<ErrorCodeType> FromString(FStringView ErrorCode);` (scope `UE::Online::Errors::ErrorCode`)
- L27 _function_ `constexpr ErrorCodeType Create(uint32 System, uint32 Category, uint32 Code)` (scope `UE::Online::Errors::ErrorCode`)
- L32 _namespace_ `namespace System` (scope `UE::Online::Errors::ErrorCode`)
- L34 _variable_ `inline constexpr ErrorCodeType Engine = 1;` (scope `UE::Online::Errors::ErrorCode::System`)
- L35 _variable_ `inline constexpr ErrorCodeType Game = 2;` (scope `UE::Online::Errors::ErrorCode::System`)
- L36 _variable_ `inline constexpr ErrorCodeType ThirdPartyPlugin = 3;` (scope `UE::Online::Errors::ErrorCode::System`)
- L43 _prototype_ `uint64 ErrorCodeSystem(ErrorCodeType ErrorCode);` (scope `UE::Online::Errors`) — These three functions are responsible for reading the parts of the uint64 error representation The uint64 error is formatted as follows (big endian): ssss cccc cccc cccc cccc cccc cccc cccc vvvv vvvv vvvv vvvv vvvv vvvv vvvv vvvv
- L44 _prototype_ `uint64 ErrorCodeCategory(ErrorCodeType ErrorCode);` (scope `UE::Online::Errors`)
- L45 _prototype_ `uint64 ErrorCodeValue(ErrorCodeType ErrorCode);` (scope `UE::Online::Errors`)
- L48 _macro_ `#define UE_ONLINE_ERROR_CATEGORY(Name, InSystem, Value, Description) \` — define an error category
- L54 _macro_ `#define UE_ONLINE_ERROR_CATEGORY_RANGE(Name, System, StartValue, EndValue, Description) \` — reserve an error category range
- L70 _macro_ `#define UE_ONLINE_ERROR_INTERNAL(CategoryName, Name, ErrorCodeValue, ErrorMessage, ErrorText) \` — Defines an individual error. Not intended to be used directly. - Example access: (UE::Online::Errors::)NoConnection(); - Can also specify an inner, e.g. RequestFailure(InvalidCreds()); - Parameters: - CategoryName: The name of a category previously defined by ONLINE_ERROR_CATEGORY - Name: Code-facing name - ErrorCodeValue: Unique identifiable integer that will encode this error string when displaying the condensed version to end user - ErrorMessage: Message displayed in the log when this error is printed - ErrorText: End-User-facing message shown when this error occurs todo: Do we need to add a value in here to have a "System" other than "Engine"? Maybe we can tie this to the category?
- L82 _macro_ `#define UE_ONLINE_ERROR(CategoryName, Name, ErrorCodeValue, ErrorMessage, ErrorText) \` — Macro to define an error within a category. Must be used within the UE::Online::Errors namespace. The error will be accessible as UE::Online::Errors::CategoryName::Name()
- L89 _macro_ `#define UE_ONLINE_ERROR_COMMON(CategoryName, Name, ErrorCodeValue, ErrorMessage, ErrorText) \` — Macro to define a common error in the UE::Online::Errors namespace. Must be used within the UE::Online::Errors namespace. The error will be accessible as UE::Online::Errors::Name()
- L94 _macro_ `#define UE_ONLINE_ERROR_EXTERNAL(CategoryName, Name, ErrorCodeValue, ErrorMessage, ErrorText) \` — Macro to define an error in a user defined namespace. The error will be accessible as CurrentNamespace::Name()

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/OnlineErrorDefinitions.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define LOCTEXT_NAMESPACE "OnlineErrors"`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L9 _namespace_ `namespace Errors` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/OnlineMeta.h` (Public)


#### struct `UE::Online::Meta::CSuperDefined`  
`struct CSuperDefined`  
_L12-16_
- desc: Concept that checks for the existence of a Super typedef/using declaration
- L15 _public prototype_ `template <typename T> auto Requires() -> typename T::Super&;`

#### struct `UE::Online::Meta::Private::TBaseClassHelper`  
`template <typename T, bool THasSuper = TModels_V<CSuperDefined, T>> struct TBaseClassHelper`  
_L21-23_
- L28 _public typedef_ `using Type = T;`
- L34 _public typedef_ `using Type = typename TBaseClassHelper<typename T::Super>::Type;`

#### struct `UE::Online::Meta::Private::TBaseClassHelper`  
`template <typename T> struct TBaseClassHelper<T, false>`  
_L26-29_
- L28 _public typedef_ `using Type = T;`
- L34 _public typedef_ `using Type = typename TBaseClassHelper<typename T::Super>::Type;`

#### struct `UE::Online::Meta::Private::TBaseClassHelper`  
`template <typename T> struct TBaseClassHelper<T, true>`  
_L32-35_
- L28 _public typedef_ `using Type = T;`
- L34 _public typedef_ `using Type = typename TBaseClassHelper<typename T::Super>::Type;`

#### struct `UE::Online::Meta::Private::TField`  
`template <typename StructType, typename FieldType> struct TField`  
_L38-44_
- L40 _public function_ `constexpr TField(FieldType StructType::* InPointer, const TCHAR* InName) : Pointer(InPointer), Name(InName)`
- L41 _public typedef_ `using Type = FieldType;`
- L42 _public member_ `Type StructType::* Pointer;`
- L43 _public member_ `const TCHAR* Name;`

#### struct `UE::Online::Meta::TBaseClass`  
`template <typename T> struct TBaseClass`  
_L58-61_
- desc: If all types in a class hierarchy have a Super typedef or using declaration, Type will be the type of the last Super definition
- L60 _public typedef_ `using Type = typename Private::TBaseClassHelper<T>::Type;`

#### struct `UE::Online::Meta::TStruct`  
`template <typename StructType> struct TStruct : public TStructDetails<std::remove_cv_t<std::remove_reference_t<StructType>>>`  
_L79-81_
- inherits: `TStructDetails<std::remove_cv_t<std::remove_reference_t<StructType>>>`
- desc: Struct field definitions, manually defined via the ONLINE_STRUCT macros below

#### struct `UE::Online::Meta::COnlineMetadataAvailable`  
`struct COnlineMetadataAvailable`  
_L129-133_
- desc: Concept that checks if we have metadata for a struct
- L132 _public prototype_ `template <typename T> auto Requires() -> decltype(TStructDetails<std::remove_cv_t<std::remove_reference_t<T>>>::Fields());`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Online` (scope `UE`)
- L7 _namespace_ `namespace Meta` (scope `UE::Online`)
- L18 _namespace_ `namespace Private` (scope `UE::Online::Meta`)
- L47 _function_ `template <typename StructType, typename FieldType> constexpr TField<StructType, FieldType> MakeTField(FieldType StructType::* Pointer, const TCHAR* Name)` (scope `UE::Online::Meta::Private`)
- L67 _typedef_ `template <typename T> using TBaseClass_T = typename TBaseClass<T>::Type;` (scope `UE::Online::Meta`) — Convenience template alias for TBaseClass<T>::Type
- L89 _function_ `template <typename StructType, typename FuncType> inline void VisitFields(FuncType&& Func)` (scope `UE::Online::Meta`) — Visit the TFields for a struct. TStructDetails must be specialized for the StructType @param Func The functor to apply.
- L101 _function_ `template <typename StructType, typename FuncType> inline void VisitFields(StructType&& Object, FuncType&& Func)` (scope `UE::Online::Meta`) — Visit the fields of a struct. TStructDetails must be specialized for the StructType @param Object The object whose fields will be applied to the functor @param Func The functor to apply.
- L105 _function_ `` (scope `UE::Online::Meta::VisitFields`)
- L117 _function_ `template <typename StructType, typename FuncType> inline void VisitFields(const StructType& Object, FuncType&& Func)` (scope `UE::Online::Meta`) — Visit the TFields of a struct. TStructDetails must be specialized for the StructType @param Object The object whose fields will be applied to the functor @param Func The functor to apply.
- L141 _macro_ `#define BEGIN_ONLINE_STRUCT_META(StructType) template <> struct TStructDetails<StructType> { static const auto& Fields() { static auto Fields = MakeTuple(` — The following macros are used to define the metadata for Online structs Must be inside of the UE::Online::Meta namespace
- L142 _macro_ `#define ONLINE_STRUCT_FIELD(StructType, FieldName) Private::MakeTField(&StructType::FieldName, TEXT(#FieldName))`
- L143 _macro_ `#define ONLINE_STRUCT_FIELD_NAMED(StructType, FieldName, FieldNameString) Private::MakeTField(&StructType::FieldName, FieldNameString)`
- L144 _macro_ `#define END_ONLINE_STRUCT_META() ); return Fields; } };`

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/OnlineResult.h` (Public)


#### class `UE::Online::TResult`  
`template <typename SuccessType, typename ErrorType> class TResult`  
_L21-201_
- desc: A container that holds either a successful result or an erroneous result. @param SuccessType - the type to use for successful results @param ErrorType - the type to use for erroneous results
- L27 _public function_ `explicit TResult(const SuccessType& OkValue) : Storage(TInPlaceType<SuccessType>(), OkValue)` — Construct a result with an Ok value
- L35 _public function_ `explicit TResult(SuccessType&& OkValue) : Storage(TInPlaceType<SuccessType>(), MoveTemp(OkValue))` — Construct a result with an Ok value
- L43 _public function_ `explicit TResult(const ErrorType& ErrValue) : Storage(TInPlaceType<ErrorType>(), ErrValue)` — Construct a result with an error value
- L51 _public function_ `explicit TResult(ErrorType&& ErrValue) : Storage(TInPlaceType<ErrorType>(), MoveTemp(ErrValue))` — Construct a result with an error value
- L59 _public prototype_ `TResult(const TResult& Other) = default;` — Copy construct a result of the same type
- L64 _public prototype_ `TResult(TResult&& Other) = default;` — Move construct a result
- L69 _public function_ `TResult& operator=(const TResult& Other)` — Assign a result from another result
- L81 _public function_ `TResult& operator=(TResult&& Other)` — Move-assign a result
- L90 _public prototype_ `virtual ~TResult() = default;`
- L99 _public function_ `bool IsOk() const` — Check if the value held in the result is a SuccessType. If the held value is a SuccessType, it is permissible to call GetOkValue. Otherwise it is permissible to call GetErrorValue. @return true if the held value is a SuccessType, false otherwise.
- L111 _public function_ `bool IsError() const` — Check if the value held in the result is a ErrorType. If the held value is a ErrorType, it is permissible to call GetErrorValue. Otherwise it is permissible to call GetOkValue. @return true if the held value is a ErrorType, false otherwise.
- L117 _public function_ `const SuccessType& GetOkValue() const` — Get the Ok value stored in the result. This must not be called on a result holding the error type
- L124 _public function_ `SuccessType& GetOkValue()` — Get the Ok value stored in the result. This must not be called on a result holding the error type
- L131 _public function_ `const ErrorType& GetErrorValue() const` — Get the Error value stored in the result. This must not be called on a result holding the success type
- L138 _public function_ `ErrorType& GetErrorValue()` — Get the Error value stored in the result. This must not be called on a result holding the success type
- L149 _public function_ `const SuccessType* TryGetOkValue() const` — Convert from TResult<Success, Error> to Success* if the result is successful. @return A pointer to a value of type SuccessType if the result is successful, otherwise nullptr
- L159 _public function_ `SuccessType* TryGetOkValue()` — Convert from TResult<Success, Error> to Success* if the result is successful. @return A pointer to a value of type SuccessType if the result is successful, otherwise nullptr
- L169 _public function_ `const ErrorType* TryGetErrorValue() const` — Convert from TResult<Success, Error> to Error* if the result is erroneous. @return A pointer to a value of type ErrorType if the result is erroneous, otherwise nullptr
- L179 _public function_ `ErrorType* TryGetErrorValue()` — Convert from TResult<Success, Error> to Error* if the result is erroneous. @return A pointer to a value of type ErrorType if the result is erroneous, otherwise nullptr
- L189 _public function_ `const SuccessType& GetOkOrDefault(const SuccessType& DefaultValue) const` — Unwraps the result, returning the success value if one is held, otherwise returning the default passed. @param DefaultValue - The value to return if the result does not hold a success type.
- L196 _protected prototype_ `TResult() = default;`
- L200 _private member_ `TVariant<SuccessType, ErrorType> Storage;` — Location that the result's value is stored

#### class `UE::Online::TOnlineResult`  
`template <typename OpType> class TOnlineResult : public TResult<typename OpType::Result, FOnlineError>`  
_L204-208_
- inherits: `TResult<typenameOpType::Result,FOnlineError>`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L211 _function_ `template <typename T> FString ToLogString(const TOnlineResult<T>& Result)` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/OnlineServices.h` (Public)


#### enum `UE::Online::EOnlinePlatformType`  
`enum class EOnlinePlatformType : uint8`  
_L16-24_
- L18 _public enumerator_ `Epic`
- L19 _public enumerator_ `Steam`
- L20 _public enumerator_ `PSN`
- L21 _public enumerator_ `Nintendo`
- L22 _public enumerator_ `XBL`
- L23 _public enumerator_ `Unknown`

#### struct `UE::Online::FGetResolvedConnectString`  
`struct FGetResolvedConnectString`  
_L46-62_
- L48 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetResolvedConnectString::Params`  
`struct Params`  
_L50-56_
- L52 _public member_ `FAccountId LocalAccountId;`
- L53 _public member_ `FLobbyId LobbyId;`
- L54 _public member_ `FOnlineSessionId SessionId;`
- L55 _public member_ `FName PortType;`

#### struct `UE::Online::FGetResolvedConnectString::Result`  
`struct Result`  
_L58-61_
- L60 _public member_ `FString ResolvedConnectString;`

#### class `UE::Online::IOnlineServices`  
`class IOnlineServices : public TSharedFromThis<IOnlineServices>`  
_L64-205_
- inherits: `TSharedFromThis<IOnlineServices>`
- L67 _public prototype_ `virtual ~IOnlineServices() = default;`
- L72 _public prototype_ `virtual void Init() = 0;`
- L77 _public prototype_ `virtual void Destroy() = 0;`
- L82 _public prototype_ `virtual IAchievementsPtr GetAchievementsInterface() = 0;`
- L87 _public prototype_ `virtual IAuthPtr GetAuthInterface() = 0;`
- L92 _public prototype_ `virtual ICommercePtr GetCommerceInterface() = 0;`
- L97 _public prototype_ `virtual IUserInfoPtr GetUserInfoInterface() = 0;`
- L104 _public prototype_ `virtual ISocialPtr GetSocialInterface() = 0;` — Get the social interface, used to interact with friends lists, blocked user lists, and any other social relationships @return social interface implementation, may be null if not implemented for this service
- L109 _public prototype_ `virtual IPresencePtr GetPresenceInterface() = 0;`
- L114 _public prototype_ `virtual IExternalUIPtr GetExternalUIInterface() = 0;`
- L120 _public prototype_ `virtual ILeaderboardsPtr GetLeaderboardsInterface() = 0;` — Get the leaderboards implementation @return leaderboards implementation, may be null if not implemented for this service
- L126 _public prototype_ `virtual ILobbiesPtr GetLobbiesInterface() = 0;` — Get the lobbies implementation @return lobbies implementation, may be null if not implemented for this service
- L132 _public prototype_ `virtual ISessionsPtr GetSessionsInterface() = 0;` — Get the sessions implementation @return sessions implementation, may be null if not implemented for this service
- L138 _public prototype_ `virtual IStatsPtr GetStatsInterface() = 0;` — Get the stats implementation @return stats implementation, may be null if not implemented for this service
- L143 _public prototype_ `virtual IConnectivityPtr GetConnectivityInterface() = 0;`
- L148 _public prototype_ `virtual IPrivilegesPtr GetPrivilegesInterface() = 0;`
- L153 _public prototype_ `virtual ITitleFilePtr GetTitleFileInterface() = 0;`
- L158 _public prototype_ `virtual IUserFilePtr GetUserFileInterface() = 0;`
- L163 _public prototype_ `virtual TOnlineResult<FGetResolvedConnectString> GetResolvedConnectString(FGetResolvedConnectString::Params&& Params) = 0;` — Get the connectivity string used for client travel
- L169 _public prototype_ `virtual EOnlineServices GetServicesProvider() const = 0;` — Get the provider type of this instance. @return provider type
- L175 _public prototype_ `virtual FName GetInstanceName() const = 0;` — Get the instance name of this instance. @return instance name
- L181 _public prototype_ `virtual FName GetInstanceConfigName() const = 0;` — Get the instance config name for this instance. @return instance config name
- L187 _public function_ `template <typename InterfaceType> TSharedPtr<InterfaceType> GetInterface()` — Retrieve any of the standard or implementation specific interfaces
- L204 _private prototype_ `virtual void AssignBaseInterfaceSharedPtr(const FOnlineTypeName& TypeName, void* InterfaceSP) = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace Meta` (scope `UE::Online`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Online` (scope `UE`)
- L25 _prototype_ `const TCHAR* LexToString(EOnlinePlatformType EnumVal);` (scope `UE::Online`)
- L26 _prototype_ `void LexFromString(EOnlinePlatformType& OutPlatformType, const TCHAR* InStr);` (scope `UE::Online`)
- L29 _typedef_ `using IOnlineServicesPtr = TSharedPtr<class IOnlineServices>;` (scope `UE::Online`) — Interfaces
- L30 _typedef_ `using IAchievementsPtr = TSharedPtr<class IAchievements>;` (scope `UE::Online`)
- L31 _typedef_ `using IAuthPtr = TSharedPtr<class IAuth>;` (scope `UE::Online`)
- L32 _typedef_ `using ICommercePtr = TSharedPtr<class ICommerce>;` (scope `UE::Online`)
- L33 _typedef_ `using IUserInfoPtr = TSharedPtr<class IUserInfo>;` (scope `UE::Online`)
- L34 _typedef_ `using ISocialPtr = TSharedPtr<class ISocial>;` (scope `UE::Online`)
- L35 _typedef_ `using IPresencePtr = TSharedPtr<class IPresence>;` (scope `UE::Online`)
- L36 _typedef_ `using IExternalUIPtr = TSharedPtr<class IExternalUI>;` (scope `UE::Online`)
- L37 _typedef_ `using ILeaderboardsPtr = TSharedPtr<class ILeaderboards>;` (scope `UE::Online`)
- L38 _typedef_ `using ILobbiesPtr = TSharedPtr<class ILobbies>;` (scope `UE::Online`)
- L39 _typedef_ `using ISessionsPtr = TSharedPtr<class ISessions>;` (scope `UE::Online`)
- L40 _typedef_ `using IStatsPtr = TSharedPtr<class IStats>;` (scope `UE::Online`)
- L41 _typedef_ `using IConnectivityPtr = TSharedPtr<class IConnectivity>;` (scope `UE::Online`)
- L42 _typedef_ `using IPrivilegesPtr = TSharedPtr<class IPrivileges>;` (scope `UE::Online`)
- L43 _typedef_ `using ITitleFilePtr = TSharedPtr<class ITitleFile>;` (scope `UE::Online`)
- L44 _typedef_ `using IUserFilePtr = TSharedPtr<class IUserFile>;` (scope `UE::Online`)
- L190 _typedef_ `using BaseInterfaceType = Meta::TBaseClass_T<InterfaceType>;` (scope `UE::Online::IOnlineServices::GetInterface`)
- L213 _prototype_ `int32 GetBuildUniqueId();` (scope `UE::Online`) — Retrieve the unique id for the executable build. The build id is used for ensuring that client and server builds are compatible. @return The unique id for the executable build.
- L222 _prototype_ `bool IsLoaded(EOnlineServices OnlineServices = EOnlineServices::Default, FName InstanceName = NAME_None, FName InstanceConfigName = NAME_None);` (scope `UE::Online`) — Check if an instance of the online service is loaded @param OnlineServices Type of online services for the IOnlineServices instance @param InstanceName Name of the instance @return true if the instance is loaded
- L232 _prototype_ `TSharedPtr<IOnlineServices> GetServices(EOnlineServices OnlineServices = EOnlineServices::Default, FName InstanceName = NAME_None, FName InstanceConfigName = NAME_None);` (scope `UE::Online`) — Get an instance of the online service @param OnlineServices Type of online services to retrieve @param InstanceName Name of the services instance to retrieve @param InstanceConfigName Name of the implementation specific config to use for this services instance @return The services instance or an invalid pointer if the services is unavailable
- L241 _function_ `template <typename ServicesClass> TSharedPtr<ServicesClass> GetServices(FName InstanceName = NAME_None, FName InstanceConfigName = NAME_None)` (scope `UE::Online`) — Get a specific services type and cast to the specific services type @param InstanceName Name of the services instance to retrieve @return The services instance or an invalid pointer if the services is unavailable
- L252 _prototype_ `void DestroyService(EOnlineServices OnlineServices = EOnlineServices::Default, FName InstanceName = NAME_None, FName InstanceConfigName = NAME_None);` (scope `UE::Online`) — Destroy an instance of the online service @param OnlineServices Type of online services to destroy @param InstanceName Name of the services instance to destroy
- L259 _prototype_ `void DestroyAllNamedServices(EOnlineServices OnlineServices);` (scope `UE::Online`) — Destroy all instances of the online services specified by EOnlineServices type @param OnlineServices Type of online services to destroy all instances from
- L266 _prototype_ `void DestroyAllServicesWithName(FName InstanceName);` (scope `UE::Online`) — Destroy all instances of the online services with specified instance name @param InstanceName Name of online services to destroy all instances from
- L268 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/OnlineServicesDelegates.h` (Public)


#### struct `UE::Online::FOnAsyncOpCompletedParams`  
`struct FOnAsyncOpCompletedParams`  
_L27-39_
- desc: Notification params of OnAsyncOpCompleted delegate
- L30 _public member_ `FString OpName;` — The name of completed operation
- L32 _public member_ `FString InterfaceName;` — The name of interface
- L34 _public member_ `TWeakPtr<IOnlineServices> OnlineServices;` — The OnlineServices instance
- L36 _public member_ `TOptional<UE::Online::FOnlineError> OnlineError;` — The result of completed operation
- L38 _public member_ `double DurationInSeconds = -1.0;` — The duration of the operation from start to complete

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L23 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlineServicesCreated, TSharedRef<class IOnlineServices> );` — Notification that a new online subsystem instance has been created @param NewSubsystem the new instance created
- L23 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlineServicesCreated, TSharedRef<class IOnlineServices> );` (scope `UE::Online`) — Notification that a new online subsystem instance has been created @param NewSubsystem the new instance created
- L24 _externvar_ `extern FOnOnlineServicesCreated OnOnlineServicesCreated;` (scope `UE::Online`)
- L48 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAsyncOpCompleted, const FOnAsyncOpCompletedParams& Params);` — Notification that an online operation has completed !!!NOTE!!! The notification can happen on off-game threads, make sure the callbacks are thread-safe @param Params the struct FOnAsyncOpCompletedParams which contains related info
- L48 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAsyncOpCompleted, const FOnAsyncOpCompletedParams& Params);` (scope `UE::Online`) — Notification that an online operation has completed !!!NOTE!!! The notification can happen on off-game threads, make sure the callbacks are thread-safe @param Params the struct FOnAsyncOpCompletedParams which contains related info
- L49 _externvar_ `extern FOnAsyncOpCompleted OnAsyncOpCompleted;` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/OnlineServicesLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOnlineServices, Log, All);`

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/OnlineServicesRegistry.h` (Public)


#### class `UE::Online::IOnlineServicesFactory`  
`class IOnlineServicesFactory`  
_L16-30_
- L22 _public prototype_ `virtual ~IOnlineServicesFactory() = default;` — Virtual destructor
- L29 _public prototype_ `virtual TSharedPtr<IOnlineServices> Create(FName InstanceName, FName InstanceConfigName) = 0;` — Create an IOnlineServices instance @return Initialized IOnlineServices instance

#### class `UE::Online::FOnlineServicesRegistry`  
`class FOnlineServicesRegistry`  
_L32-167_
- L40 _public prototype_ `static FOnlineServicesRegistry& Get();` — Get the FOnlineServicesRegistry singleton @return The FOnlineServicesRegistry singleton instance
- L45 _public prototype_ `static void TearDown();` — Tear down the singleton instance
- L54 _public prototype_ `void RegisterServicesFactory(EOnlineServices OnlineServices, TUniquePtr<IOnlineServicesFactory>&& Factory, int32 Priority = 0);` — Register a factory for creation of IOnlineServices instances @param OnlineServices Services that the factory is for @param Factory Factory for creation of IOnlineServices instances @param Priority Integer priority, allows an existing OnlineServices implementation to be extended and registered with a higher priority so it is used instead
- L62 _public prototype_ `void UnregisterServicesFactory(EOnlineServices OnlineServices, int32 Priority = 0);` — Unregister a previously registered IOnlineServices factory @param OnlineServices Services that the factory is for @param Priority Integer priority, will be unregistered only if the priority matches the one that is registered
- L73 _public prototype_ `bool IsLoaded(EOnlineServices OnlineServices, FName InstanceName, FName InstanceConfigName = NAME_None) const;` — Check if an online service instance is loaded @param OnlineServices Type of online services for the IOnlineServices instance @param InstanceName Name of the instance @param InstanceConfigName Name of the config @return true if the instance is loaded
- L84 _public prototype_ `TSharedPtr<IOnlineServices> GetNamedServicesInstance(EOnlineServices OnlineServices, FName InstanceName, FName InstanceConfigName);` — Get a named instance of a specific IOnlineServices @param OnlineServices Type of online services for the IOnlineServices instance @param InstanceName Name of the instance @param InstanceConfigName Name of the config to use @return The services instance, or an invalid pointer if the OnlineServices is unavailable
- L93 _public prototype_ `void DestroyNamedServicesInstance(EOnlineServices OnlineServices, FName InstanceName, FName InstanceConfigName);` — Destroy a named instance of a specific OnlineServices @param OnlineServices Type of online services for the IOnlineServices instance @param InstanceName Name of the instance @param InstanceConfigName Name of the config
- L100 _public prototype_ `void DestroyAllNamedServicesInstances(EOnlineServices OnlineServices);` — Destroy all instances of a specific OnlineServices @param OnlineServices  Type of online services for the IOnlineServices instance
- L107 _public prototype_ `void DestroyAllServicesInstancesWithName(FName InstanceName);` — Destroy all instances of a specific InstanceName @param InstanceName  Name of online services for the IOnlineServices instance
- L118 _public prototype_ `TSharedPtr<IOnlineServices> CreateServices(EOnlineServices OnlineServices, FName InstanceName, FName InstanceConfigName);` — Create and initialize a new IOnlineServices instance @param OnlineServices Type of online services for the IOnlineServices instance @param InstanceName Name of the instance @param InstanceConfigName Name of the config @return The initialized IOnlineServices instance, or an invalid pointer if the OnlineServices is unavailable
- L125 _public prototype_ `void GetAllServicesInstances(TArray<TSharedRef<IOnlineServices>>& OutOnlineServices) const;` — Get list of all instantiated OnlineServices @param OutOnlineServices Array of online services to fill
- L133 _public prototype_ `void SetDefaultServiceOverride(EOnlineServices DefaultService);` — Adds a temporary override to the default online service. Used for testing to quickly run tests with different default online services. @param Service the name of the Online Service to force default online service to return
- L138 _public prototype_ `void ClearDefaultServiceOverride();` — Removes an override for the target service.
- L153 _private member_ `TMap<EOnlineServices, FFactoryAndPriority> ServicesFactories;`
- L155 _private typedef_ `using FInstanceNameInstanceConfigNamePair = TPair<FName, FName>;`
- L156 _private member_ `TMap<EOnlineServices, TMap<FInstanceNameInstanceConfigNamePair, TSharedRef<IOnlineServices>>> NamedServiceInstances;`
- L157 _private member_ `EOnlineServices DefaultServiceOverride = EOnlineServices::Default;`
- L159 _private function_ `FOnlineServicesRegistry()`
- L160 _private prototype_ `~FOnlineServicesRegistry();`
- L166 _private prototype_ `EOnlineServices ResolveServiceName(EOnlineServices OnlineServices) const;` — Resolves a generic (like Platform and Default) service enum value into the value of the real corresponding service.

#### struct `UE::Online::FOnlineServicesRegistry::FFactoryAndPriority`  
`struct FFactoryAndPriority`  
_L141-151_
- L143 _public function_ `FFactoryAndPriority(TUniquePtr<IOnlineServicesFactory>&& InFactory, int32 InPriority) : Factory(MoveTemp(InFactory)) , Priority(InPriority)`
- L149 _public member_ `TUniquePtr<IOnlineServicesFactory> Factory;`
- L150 _public member_ `int32 Priority;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/OnlineTypeInfo.h` (Public)


#### struct `UE::Online::FOnlineTypeName`  
`struct FOnlineTypeName`  
_L14-27_
- L16 _public member_ `const TCHAR* Name = nullptr;`
- L18 _public function_ `bool operator==(const FOnlineTypeName& Other) const`
- L23 _public function_ `bool operator!=(const FOnlineTypeName& Other) const`

#### struct `UE::Online::TOnlineTypeInfo`  
`template <typename T> struct TOnlineTypeInfo`  
_L35-58_
- L37 _public function_ `static inline FOnlineTypeName GetTypeName()`
- L42 _public function_ `static inline bool IsA(FOnlineTypeName TypeName)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace Meta` (scope `UE::Online`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L29 _function_ `inline uint32 GetTypeHash(const FOnlineTypeName& TypeName)` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/OnlineUtils.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Online` (scope `UE`)
- L18 _prototype_ `template <typename T> FString ToLogString(const TSet<T>& Set);` (scope `UE::Online`)
- L22 _prototype_ `template <typename T, typename U> FString ToLogString(const TPair<T, U>& Pair);` (scope `UE::Online`)
- L23 _prototype_ `template <typename T, ESPMode Mode> FString ToLogString(const TSharedPtr<T, Mode>& Ptr);` (scope `UE::Online`)
- L24 _prototype_ `template <typename T, ESPMode Mode> FString ToLogString(const TSharedRef<T, Mode>& Ref);` (scope `UE::Online`)
- L25 _prototype_ `template <typename T> FString ToLogString(const TOptional<T> Optional);` (scope `UE::Online`)
- L26 _prototype_ `inline FString ToLogString(const FName& Name);` (scope `UE::Online`)
- L27 _prototype_ `inline FString ToLogString(const FUtf8String& Name);` (scope `UE::Online`)
- L28 _prototype_ `inline FString ToLogString(const FText& Text);` (scope `UE::Online`)
- L29 _prototype_ `inline FString ToLogString(uint8 Value);` (scope `UE::Online`)
- L30 _prototype_ `inline FString ToLogString(int8 Value);` (scope `UE::Online`)
- L31 _prototype_ `inline FString ToLogString(uint16 Value);` (scope `UE::Online`)
- L32 _prototype_ `inline FString ToLogString(int16 Value);` (scope `UE::Online`)
- L33 _prototype_ `inline FString ToLogString(uint32 Value);` (scope `UE::Online`)
- L34 _prototype_ `inline FString ToLogString(int32 Value);` (scope `UE::Online`)
- L35 _prototype_ `inline FString ToLogString(uint64 Value);` (scope `UE::Online`)
- L36 _prototype_ `inline FString ToLogString(int64 Value);` (scope `UE::Online`)
- L37 _prototype_ `inline FString ToLogString(bool Value);` (scope `UE::Online`)
- L38 _prototype_ `inline FString ToLogString(float Value);` (scope `UE::Online`)
- L39 _prototype_ `inline FString ToLogString(double Value);` (scope `UE::Online`)
- L40 _prototype_ `FString ToLogString(const FDateTime& Time);` (scope `UE::Online`)
- L41 _prototype_ `template <typename T> FString ToLogString(const T& Value);` (scope `UE::Online`)
- L44 _function_ `template <typename T> FString ToLogString(const TSet<T>& Set)` (scope `UE::Online`)
- L46 _function_ `return FString::Printf(TEXT("{%s}"), *FString::JoinBy(Set, TEXT(", "), [](const T& Value) { return ToLogString(Value)` (scope `UE::Online::ToLogString`)
- L50 _function_ `template <typename T, typename U> FString ToLogString(const TPair<T, U>& Pair)` (scope `UE::Online`)
- L56 _function_ `template <typename T, ESPMode Mode> FString ToLogString(const TSharedPtr<T, Mode>& Ptr)` (scope `UE::Online`)
- L69 _function_ `template <typename T, ESPMode Mode> FString ToLogString(const TSharedRef<T, Mode>& Ref)` (scope `UE::Online`)
- L75 _function_ `template <typename T> FString ToLogString(const TOptional<T> Optional)` (scope `UE::Online`)
- L88 _function_ `template <typename... Ts> FString ToLogString(const TVariant<Ts...>& Variant)` (scope `UE::Online`)
- L91 _function_ `` (scope `UE::Online::ToLogString`)
- L96 _function_ `inline FString ToLogString(const FString& String)` (scope `UE::Online`)
- L101 _function_ `inline FString ToLogString(const FName& Name)` (scope `UE::Online`)
- L106 _function_ `inline FString ToLogString(const FUtf8String& String)` (scope `UE::Online`)
- L111 _function_ `inline FString ToLogString(const FText& Text)` (scope `UE::Online`)
- L116 _function_ `inline FString ToLogString(uint8 Value)` (scope `UE::Online`)
- L121 _function_ `inline FString ToLogString(int8 Value)` (scope `UE::Online`)
- L126 _function_ `inline FString ToLogString(uint16 Value)` (scope `UE::Online`)
- L131 _function_ `inline FString ToLogString(int16 Value)` (scope `UE::Online`)
- L136 _function_ `inline FString ToLogString(uint32 Value)` (scope `UE::Online`)
- L141 _function_ `inline FString ToLogString(int32 Value)` (scope `UE::Online`)
- L146 _function_ `inline FString ToLogString(uint64 Value)` (scope `UE::Online`)
- L151 _function_ `inline FString ToLogString(int64 Value)` (scope `UE::Online`)
- L156 _function_ `inline FString ToLogString(float Value)` (scope `UE::Online`)
- L161 _function_ `inline FString ToLogString(double Value)` (scope `UE::Online`)
- L166 _function_ `inline FString ToLogString(bool Value)` (scope `UE::Online`)
- L171 _function_ `inline FString ToLogString(FPlatformUserId PlatformUserId)` (scope `UE::Online`)
- L180 _member_ `typename T::ElementType;` (scope `UE::Online::T`)
- L188 _member_ `typename T::KeyType;` (scope `UE::Online::T`)
- L189 _member_ `typename T::ValueType;` (scope `UE::Online::T`)
- L194 _function_ `template <typename T> FString ToLogString(const T& Value)` (scope `UE::Online`)
- L198 _function_ `return FString::Printf(TEXT("[%s]"), *FString::JoinBy(Value, TEXT(", "), [](const typename T::ElementType& Element) { return ToLogString(Element)` (scope `UE::Online::ToLogString`)
- L202 _function_ `return FString::Printf(TEXT("{%s}"), *FString::JoinBy(Value, TEXT(", "), [](const TPair<typename T::KeyType, typename T::ValueType>& Pair) { return ToLogString(Pair)` (scope `UE::Online::ToLogString`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/Presence.h` (Public)


#### enum `UE::Online::EUserPresenceStatus`  
`enum class EUserPresenceStatus : uint8`  
_L41-55_
- L44 _public enumerator_ `Offline` — User is offline
- L46 _public enumerator_ `Online` — User is online
- L48 _public enumerator_ `Away` — User is away
- L50 _public enumerator_ `ExtendedAway` — User is away for >2 hours (can change depending on platform)
- L52 _public enumerator_ `DoNotDisturb` — User is in do not disturb mode
- L54 _public enumerator_ `Unknown` — Default

#### enum `UE::Online::EUserPresenceJoinability`  
`enum class EUserPresenceJoinability : uint8`  
_L60-72_
- L63 _public enumerator_ `Public` — Anyone can matchmake/discover and join this session
- L65 _public enumerator_ `FriendsOnly` — Anyone trying to join must be a friend of a lobby member
- L67 _public enumerator_ `InviteOnly` — Anyone trying to join must have been invited first
- L69 _public enumerator_ `Private` — Not currently accepting invites
- L71 _public enumerator_ `Unknown` — Default

#### enum `UE::Online::EUserPresenceGameStatus`  
`enum class EUserPresenceGameStatus : uint8`  
_L76-84_
- L79 _public enumerator_ `PlayingThisGame` — The user is playing the same game as you
- L81 _public enumerator_ `PlayingOtherGame` — The user is playing a different game than you
- L83 _public enumerator_ `Unknown` — Default

#### struct `UE::Online::FUserPresence`  
`struct FUserPresence`  
_L93-113_
- L96 _public member_ `FAccountId AccountId;` — User whose presence this is
- L98 _public member_ `EUserPresenceStatus Status = EUserPresenceStatus::Unknown;` — Presence state
- L100 _public member_ `EUserPresenceJoinability Joinability = EUserPresenceJoinability::Unknown;` — Session state
- L102 _public member_ `EUserPresenceGameStatus GameStatus = EUserPresenceGameStatus::Unknown;` — Playing this game
- L104 _public member_ `FString StatusString;` — Stringified representation of the user status (online, offline, whatever the platform wants to define)
- L106 _public member_ `FString RichPresenceString;` — Game-defined representation of the current game state (e.g. "Squads- 4 Remaining" or "Level 5 Warrior")
- L108 _public member_ `EOnlinePlatformType PlatformType = EOnlinePlatformType::Unknown;` — Type of the user's current online platform
- L110 _public member_ `FPresenceProperties Properties;` — Session keys, and any platform specific presence properties
- L112 _public prototype_ `bool operator==(const FUserPresence& Other) const = default;`

#### struct `UE::Online::FQueryPresence`  
`struct FQueryPresence`  
_L115-134_
- L117 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FQueryPresence::Params`  
`struct Params`  
_L119-127_
- L122 _public member_ `FAccountId LocalAccountId;` — Local user performing the query
- L124 _public member_ `FAccountId TargetAccountId;` — User to query the presence for
- L126 _public member_ `bool bListenToChanges = true;` — If true, then future presence updates for this user will be propagated via the OnPresenceUpdated event

#### struct `UE::Online::FQueryPresence::Result`  
`struct Result`  
_L129-133_
- L132 _public member_ `TSharedRef<const FUserPresence> Presence;` — The retrieved presence

#### struct `UE::Online::FBatchQueryPresence`  
`struct FBatchQueryPresence`  
_L137-156_
- L139 _public member_ `static constexpr TCHAR Name[] = TEXT("Bat`

#### struct `UE::Online::FBatchQueryPresence::Params`  
`struct Params`  
_L141-149_
- L144 _public member_ `FAccountId LocalAccountId;` — Local user performing the query
- L146 _public member_ `TArray<FAccountId> TargetAccountIds;` — Users to query the presence for
- L148 _public member_ `bool bListenToChanges = true;` — If true, then future presence updates for these users will be propagated via the OnPresenceUpdated event

#### struct `UE::Online::FBatchQueryPresence::Result`  
`struct Result`  
_L151-155_
- L154 _public member_ `TArray<TSharedRef<const FUserPresence>> Presences;` — The retrieved presence

#### struct `UE::Online::FGetCachedPresence`  
`struct FGetCachedPresence`  
_L158-175_
- L160 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetCachedPresence::Params`  
`struct Params`  
_L162-168_
- L165 _public member_ `FAccountId LocalAccountId;` — Local user getting the presence
- L167 _public member_ `FAccountId TargetAccountId;` — User to get the presence for

#### struct `UE::Online::FGetCachedPresence::Result`  
`struct Result`  
_L170-174_
- L173 _public member_ `TSharedRef<const FUserPresence> Presence;` — The presence

#### struct `UE::Online::FUpdatePresence`  
`struct FUpdatePresence`  
_L177-192_
- L179 _public member_ `static constexpr TCHAR Name[] = TEXT("Upd`

#### struct `UE::Online::FUpdatePresence::Params`  
`struct Params`  
_L181-187_
- L184 _public member_ `FAccountId LocalAccountId;` — Local user performing the query
- L186 _public member_ `TSharedRef<FUserPresence> Presence;` — The new presence to send to the server

#### struct `UE::Online::FUpdatePresence::Result`  
`struct Result`  
_L189-191_

#### struct `UE::Online::FPartialUpdatePresence`  
`struct FPartialUpdatePresence`  
_L194-230_
- L196 _public member_ `static constexpr TCHAR Name[] = TEXT("Par`

#### struct `UE::Online::FPartialUpdatePresence::Params`  
`struct Params`  
_L198-225_
- L201 _public member_ `FAccountId LocalAccountId;` — Local user performing the query
- L223 _public member_ `FMutations Mutations;`

#### struct `UE::Online::FPartialUpdatePresence::Params::FMutations`  
`struct FMutations`  
_L204-222_
- L207 _public member_ `TOptional<EUserPresenceStatus> Status;` — Presence state
- L209 _public member_ `TOptional<EUserPresenceJoinability> Joinability;` — Joinability state
- L211 _public member_ `TOptional<EUserPresenceGameStatus> GameStatus;` — Game status (playing/not playing this game)
- L213 _public member_ `TOptional<FString> StatusString;` — Status string
- L215 _public member_ `TOptional<FString> RichPresenceString;` — Rich presence string
- L217 _public member_ `FPresenceProperties UpdatedProperties;` — Presence keys to update
- L219 _public member_ `TArray<FString> RemovedProperties;` — Properties to remove
- L221 _public prototype_ `FMutations& operator+=(FMutations&& NewParams);`
- L232 _function_ `inline FPartialUpdatePresence::Params::FMutations& FPartialUpdatePresence::Params::FMutations::operator+=(FPartialUpdatePresence::Params::FMutations&& NewParams)`

#### struct `UE::Online::FPartialUpdatePresence::Result`  
`struct Result`  
_L227-229_

#### struct `UE::Online::FPresenceUpdated`  
`struct FPresenceUpdated`  
_L322-328_
- desc: Struct for PresenceUpdated event
- L325 _public member_ `FAccountId LocalAccountId;` — Local user receiving the presence update
- L327 _public member_ `TSharedRef<const FUserPresence> UpdatedPresence;` — Presence that has updated

#### class `UE::Online::IPresence`  
`class IPresence`  
_L330-382_
- L333 _public prototype_ `virtual ~IPresence() = default;`
- L341 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryPresence> QueryPresence(FQueryPresence::Params&& Params) = 0;` — Query presence for a user @param Params for the QueryPresence call @return
- L349 _public prototype_ `virtual TOnlineAsyncOpHandle<FBatchQueryPresence> BatchQueryPresence(FBatchQueryPresence::Params&& Params) = 0;` — Queries presences for all users in the array @param Params for the BatchQueryPresence call @return
- L358 _public prototype_ `virtual TOnlineResult<FGetCachedPresence> GetCachedPresence(FGetCachedPresence::Params&& Params) = 0;` — Get the presence of a user Presence typically comes from QueryPresence or push events from the online service @param Params for the GetCachedPresence call @return
- L366 _public prototype_ `virtual TOnlineAsyncOpHandle<FUpdatePresence> UpdatePresence(FUpdatePresence::Params&& Params) = 0;` — Update your presence @param Params for the UpdatePresence call @return
- L374 _public prototype_ `virtual TOnlineAsyncOpHandle<FPartialUpdatePresence> PartialUpdatePresence(FPartialUpdatePresence::Params&& Params) = 0;` — Updates only the parts of the presence that are specified @param Params for the UpdatePresence call @return
- L381 _public prototype_ `virtual TOnlineEvent<void(const FPresenceUpdated&)> OnPresenceUpdated() = 0;` — Get the event that is triggered when presence is updated @return Event that can be bound to

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Online` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Online` (scope `UE`)
- L15 _namespace_ `namespace Meta` (scope `UE::Online`)
- L17 _macro_ `#define LOCTEXT_NAMESPACE "Presence"`
- L19 _macro_ `#define SENT_TIME_ATTRIBUTE_KEY FString(TEXT("SentTimeAttributeKey"))`
- L20 _macro_ `#define SESSION_ID_ATTRIBUTE_KEY FString(TEXT("SessionIdAttributeKey"))`
- L21 _macro_ `#define PLATFORM_ATTRIBUTE_KEY FString(TEXT("PlatformAttributeKey"))`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Online` (scope `UE`)
- L25 _typedef_ `using FPresenceVariant = FNestedVariantJson;` (scope `UE::Online`)
- L27 _namespace_ `namespace Errors` (scope `UE::Online`)
- L56 _prototype_ `const TCHAR* LexToString(EUserPresenceStatus EnumVal);` (scope `UE::Online`)
- L57 _prototype_ `void LexFromString(EUserPresenceStatus& OutStatus, const TCHAR* InStr);` (scope `UE::Online`)
- L58 _prototype_ `FText ToLocText(EUserPresenceStatus EnumVal);` (scope `UE::Online`)
- L73 _prototype_ `const TCHAR* LexToString(EUserPresenceJoinability EnumVal);` (scope `UE::Online`)
- L74 _prototype_ `void LexFromString(EUserPresenceJoinability& OutJoinability, const TCHAR* InStr);` (scope `UE::Online`)
- L85 _prototype_ `const TCHAR* LexToString(EUserPresenceGameStatus EnumVal);` (scope `UE::Online`)
- L86 _prototype_ `void LexFromString(EUserPresenceGameStatus& OutGameStatus, const TCHAR* InStr);` (scope `UE::Online`)
- L88 _typedef_ `using FPresenceProperties = FPresenceVariant::FMap;` (scope `UE::Online`)
- L89 _typedef_ `using FPresencePropertiesRef = FPresenceVariant::FMapRef;` (scope `UE::Online`)
- L90 _typedef_ `using FPresencePropertiesPtr = FPresenceVariant::FMapPtr;` (scope `UE::Online`)
- L91 _typedef_ `using FPresenceProperty = FPresenceProperties::ValueType;` (scope `UE::Online`)
- L276 _function_ `inline TSharedRef<FUserPresence> ApplyPresenceMutations(const FUserPresence& BasePresence, const FPartialUpdatePresence::Params::FMutations& Mutations)` (scope `UE::Online`)
- L384 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/Privileges.h` (Public)


#### enum `UE::Online::EUserPrivileges`  
`enum class EUserPrivileges : uint8`  
_L13-27_
- L16 _public enumerator_ `CanPlay` — Whether the user can play at all, online or offline
- L18 _public enumerator_ `CanPlayOnline` — Whether the user can play in online modes
- L20 _public enumerator_ `CanCommunicateViaTextOnline` — Whether the user can use text chat
- L22 _public enumerator_ `CanCommunicateViaVoiceOnline` — Whether the user can use voice chat
- L24 _public enumerator_ `CanUseUserGeneratedContent` — Whether the user can use content generated by other users
- L26 _public enumerator_ `CanCrossPlay` — Whether the user can ever participate in cross-play

#### enum `UE::Online::EShowPrivilegeResolutionUI`  
`enum class EShowPrivilegeResolutionUI : uint8`  
_L32-40_
- desc: Whether to show UI to resolve the privilege if there is no access when GetUserPrivilege
- L35 _public enumerator_ `Default` — Behavior matching the recommended practices for the platform
- L37 _public enumerator_ `Show` — Show UI to resolve privilege
- L39 _public enumerator_ `NotShow` — Not show UI to resolve privilege

#### enum `UE::Online::EPrivilegeResults`  
`enum class EPrivilegeResults : uint32`  
_L44-70_
- L47 _public enumerator_ `NoFailures = 0` — The user has the requested privilege
- L49 _public enumerator_ `RequiredPatchAvailable = 1 << 0` — Patch required before the user can use the privilege
- L51 _public enumerator_ `RequiredSystemUpdate = 1 << 1` — System update required before the user can use the privilege
- L53 _public enumerator_ `AgeRestrictionFailure = 1 << 2` — Parental control failure usually
- L55 _public enumerator_ `AccountTypeFailure = 1 << 3` — Premium account required
- L57 _public enumerator_ `UserNotFound = 1 << 4` — Invalid user
- L59 _public enumerator_ `UserNotLoggedIn = 1 << 5` — User must be logged in
- L61 _public enumerator_ `ChatRestriction = 1 << 6` — User restricted from chat
- L63 _public enumerator_ `UGCRestriction = 1 << 7` — User restricted from User Generated Content
- L65 _public enumerator_ `GenericFailure = 1 << 8` — Platform failed for unknown reason and handles its own dialogs
- L67 _public enumerator_ `OnlinePlayRestricted = 1 << 9` — Online play is restricted
- L69 _public enumerator_ `NetworkConnectionUnavailable = 1 << 10` — Check failed because network is unavailable

#### struct `UE::Online::FQueryUserPrivilege`  
`struct FQueryUserPrivilege`  
_L75-97_
- L77 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FQueryUserPrivilege::Params`  
`struct Params`  
_L80-89_
- desc: Input struct for Misc::FQueryUserPrivilege
- L83 _public member_ `FAccountId LocalAccountId;` — User id whose privilege we want to query
- L85 _public member_ `EUserPrivileges Privilege;` — Privilege to query
- L87 _public member_ `EShowPrivilegeResolutionUI ShowExternalUI;` — Should external UI be shown when not possessing the queried privilege

#### struct `UE::Online::FQueryUserPrivilege::Result`  
`struct Result`  
_L92-96_
- desc: Output struct for Misc::FQueryUserPrivilege
- L95 _public member_ `EPrivilegeResults PrivilegeResult = EPrivilegeResults::NoFailures;` — Privilege result, bitwise OR of various EPrivilegeResults values

#### class `UE::Online::IPrivileges`  
`class IPrivileges`  
_L99-108_
- L105 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryUserPrivilege> QueryUserPrivilege(FQueryUserPrivilege::Params&& Params) = 0;` — Queries about a given privilege for a user
- L107 _public prototype_ `virtual ~IPrivileges() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L9 _namespace_ `namespace Meta` (scope `UE::Online`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L28 _prototype_ `const TCHAR* LexToString(EUserPrivileges Type);` (scope `UE::Online`)
- L29 _prototype_ `void LexFromString(EUserPrivileges& OutType, const TCHAR* InStr);` (scope `UE::Online`)
- L41 _prototype_ `FString LexToString(EShowPrivilegeResolutionUI Type);` (scope `UE::Online`)
- L42 _prototype_ `void LexFromString(EShowPrivilegeResolutionUI& OutType, const FString& InStr);` (scope `UE::Online`)
- L71 _prototype_ `ENUM_CLASS_FLAGS(EPrivilegeResults);` (scope `UE::Online`)
- L72 _prototype_ `FString LexToString(EPrivilegeResults Type);` (scope `UE::Online`)
- L73 _prototype_ `void LexFromString(EPrivilegeResults& OutType, const FString& InStr);` (scope `UE::Online`)
- L110 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/Schema.h` (Public)


#### class `UE::Online::Private::FSchemaCategoryInstanceBase`  
`class FSchemaCategoryInstanceBase`  
_L18-121_
- L26 _public prototype_ `FSchemaCategoryInstanceBase( const FSchemaId& DerivedSchemaId, const FSchemaId& BaseSchemaId, const FSchemaCategoryId& CategoryId, const TSharedRef<const FSchemaRegistry>& SchemaRegistry);` — DerivedSchemaId may remain unset in two situations: 1. DerivedSchemaId will be populated by attributes from a search result. In this scenario the base schema is required to have an attribute flagged as SchemaCompatibilityId so that the derived schema can be discovered. 2. Schema swapping is not enabled. All attributes are defined in the base schema.
- L32 _public prototype_ `virtual ~FSchemaCategoryInstanceBase() = default;`
- L36 _public prototype_ `TOnlineResult<FSchemaCategoryInstancePrepareClientChanges> PrepareClientChanges(FSchemaCategoryInstancePrepareClientChanges::Params&& Params) const;` — Two phase commit to the service. Prepare data to be written to the service from an client delta of attributes.
- L38 _public prototype_ `FSchemaCategoryInstanceCommitClientChanges::Result CommitClientChanges();` — Commit the client data once the service data has been successfully written.
- L42 _public prototype_ `TOnlineResult<FSchemaCategoryInstancePrepareServiceSnapshot> PrepareServiceSnapshot(FSchemaCategoryInstancePrepareServiceSnapshot::Params&& Params) const;` — Two phase commit from the service. Prepare data to be written to the client from a service snapshot of attributes.
- L44 _public prototype_ `FSchemaCategoryInstanceCommitServiceSnapshot::Result CommitServiceSnapshot();` — Commit a service snapshot containing all known service attributes.
- L48 _public function_ `TSharedPtr<const FSchemaDefinition> GetDerivedDefinition() const`
- L49 _public function_ `TSharedPtr<const FSchemaDefinition> GetBaseDefinition() const`
- L52 _public prototype_ `bool IsValid() const;` — Check whether the schema is valid.
- L56 _public prototype_ `bool VerifyBaseAttributeData( const FSchemaAttributeId& Id, const FSchemaVariant& Data, FSchemaServiceAttributeId& OutSchemaServiceAttributeId, ESchemaServiceAttributeFlags& OutSchemaServiceAttributeFlags);` — Check whether an client attribute is valid in the base schema. Intended to be used when attribute information needs to be verified without translating to the service.
- L63 _protected prototype_ `const TMap<FSchemaAttributeId, FSchemaVariant>& GetClientSnapshot() const;`
- L64 _protected prototype_ `virtual TMap<FSchemaAttributeId, FSchemaVariant>& GetMutableClientSnapshot() = 0;`
- L67 _private prototype_ `bool InitializeSchemaDefinition( int64 SchemaCompatibilityId, const FSchemaDefinition* OptionalBaseDefinition, const FSchemaCategoryId& CategoryId, TSharedPtr<const FSchemaDefinition>* OutSchemaDefinition, const FSchemaCategoryDefinition** OutSchemaCategoryDefinition) const;`
- L74 _private prototype_ `bool InitializeSchemaDefinition( const FSchemaId& SchemaId, const FSchemaDefinition* OptionalBaseDefinition, const FSchemaCategoryId& CategoryId, TSharedPtr<const FSchemaDefinition>* OutSchemaDefinition, const FSchemaCategoryDefinition** OutSchemaCategoryDefinition) const;`
- L81 _private prototype_ `bool InitializeSchemaDefinition( const TSharedRef<const FSchemaDefinition>& NewDefinition, const FSchemaDefinition* OptionalBaseDefinition, const FSchemaCategoryId& CategoryId, TSharedPtr<const FSchemaDefinition>* OutSchemaDefinition, const FSchemaCategoryDefinition** OutSchemaCategoryDefinition) const;`
- L88 _private prototype_ `bool GetSerializationSchema( const FSchemaDefinition** OutSchemaDefinition, const FSchemaCategoryDefinition** OutSchemaCategoryDefinition) const;`
- L92 _private prototype_ `void ResetPreparedChanges() const;`
- L110 _private member_ `TSharedRef<const FSchemaRegistry> SchemaRegistry;`
- L111 _private member_ `TSharedPtr<const FSchemaDefinition> DerivedSchemaDefinition;`
- L112 _private member_ `TSharedPtr<const FSchemaDefinition> BaseSchemaDefinition;`
- L113 _private member_ `const FSchemaCategoryDefinition* DerivedSchemaCategoryDefinition = nullptr;`
- L114 _private member_ `const FSchemaCategoryDefinition* BaseSchemaCategoryDefinition = nullptr;`
- L115 _private member_ `int64 LastSentSchemaCompatibilityId = 0;`
- L119 _private member_ `mutable TOptional<FPreparedClientChanges> PreparedClientChanges;` — Prepared changes are mutable so that the prepare methods can be const. Setting as mutable is done to prevent modifying state outside of the prepared changes.
- L120 _private member_ `mutable TOptional<FPreparedServiceChanges> PreparedServiceChanges;`

#### struct `UE::Online::Private::FSchemaCategoryInstanceBase::FPreparedClientChanges`  
`struct FPreparedClientChanges`  
_L94-100_
- L96 _public member_ `FSchemaServiceClientChanges ClientChanges;`
- L97 _public member_ `int64 SchemaCompatibilityId = 0;`
- L98 _public member_ `TSharedPtr<const FSchemaDefinition> DerivedSchemaDefinition;`
- L99 _public member_ `const FSchemaCategoryDefinition* DerivedSchemaCategoryDefinition = nullptr;`

#### struct `UE::Online::Private::FSchemaCategoryInstanceBase::FPreparedServiceChanges`  
`struct FPreparedServiceChanges`  
_L102-108_
- L104 _public member_ `FSchemaServiceClientChanges ClientChanges;`
- L105 _public member_ `TSharedPtr<const FSchemaDefinition> DerivedSchemaDefinition;`
- L106 _public member_ `const FSchemaCategoryDefinition* DerivedSchemaCategoryDefinition = nullptr;`
- L107 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> ClientDataSnapshot;`

#### class `UE::Online::FSchemaCategoryInstanceInternalSnapshotAccessor`  
`class FSchemaCategoryInstanceInternalSnapshotAccessor`  
_L126-136_
- desc: Schema category instance attribute accessor for providing the client attributes internally.
- L129 _public function_ `TMap<FSchemaAttributeId, FSchemaVariant>& GetMutableClientSnapshot()`
- L135 _private member_ `TMap<FSchemaAttributeId, FSchemaVariant> ClientSnapshot;`

#### class `UE::Online::TSchemaCategoryInstance`  
`template <typename FSnapshotAccessor> class TSchemaCategoryInstance final : public Private::FSchemaCategoryInstanceBase`  
_L144-165_
- inherits: `Private::FSchemaCategoryInstanceBase`
- desc: Schema category instance class templated by access to client attributes. The passed in accessor is an interface which must provide a definition for GetMutableClientSnapshot.
- L147 _public function_ `TSchemaCategoryInstance( const FSchemaId& DerivedSchemaId, const FSchemaId& BaseSchemaId, const FSchemaCategoryId& CategoryId, const TSharedRef<const FSchemaRegistry>& SchemaRegistry, FSnapshotAccessor&& InSnapshotAccessor = FSnapshotAccessor()) : Private::FSchemaCategoryInstanceBase(DerivedSchemaId, BaseSchemaId, CategoryId, SchemaRegistry) , SnapshotAccessor(MoveTemp(InSnapshotAccessor))`
- L159 _private function_ `virtual TMap<FSchemaAttributeId, FSchemaVariant>& GetMutableClientSnapshot() override`
- L164 _private member_ `FSnapshotAccessor SnapshotAccessor;`

#### class `UE::Online::FSchemaRegistry`  
`class FSchemaRegistry`  
_L170-184_
- L174 _public prototype_ `bool ParseConfig(const FSchemaRegistryDescriptorConfig& Config);` — Parse the loaded config structures.
- L176 _public prototype_ `TSharedPtr<const FSchemaDefinition> GetDefinition(const FSchemaId& SchemaId) const;`
- L177 _public prototype_ `TSharedPtr<const FSchemaDefinition> GetDefinition(int64 CompatibilityId) const;`
- L178 _public prototype_ `bool IsSchemaChildOf(const FSchemaId& SchemaId, const FSchemaId& ParentSchemaId) const;`
- L182 _private member_ `TMap<FSchemaId, TSharedRef<const FSchemaDefinition>> SchemaDefinitionsById;`
- L183 _private member_ `TMap<int64, TSharedRef<const FSchemaDefinition>> SchemaDefinitionsByCompatibilityId;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API ONLINESERVICESINTERFACE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Online`)
- L168 _typedef_ `using FSchemaCategoryInstance = TSchemaCategoryInstance<FSchemaCategoryInstanceInternalSnapshotAccessor>;` (scope `UE::Online`) — Default implementation with both translation and client attribute snapshot data contained within the category instance.

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/SchemaTypes.h` (Public)


#### enum `UE::Online::ESchemaAttributeComparisonOp`  
`enum class ESchemaAttributeComparisonOp : uint8`  
_L55-66_
- desc: Flags to indicate comparison types between Schema Attributes. Used in searches
- L57 _public enumerator_ `Equals`
- L58 _public enumerator_ `NotEquals`
- L59 _public enumerator_ `GreaterThan`
- L60 _public enumerator_ `GreaterThanEquals`
- L61 _public enumerator_ `LessThan`
- L62 _public enumerator_ `LessThanEquals`
- L63 _public enumerator_ `Near`
- L64 _public enumerator_ `In`
- L65 _public enumerator_ `NotIn`

#### enum `UE::Online::ESchemaAttributeVisibility`  
`enum class ESchemaAttributeVisibility : uint8`  
_L71-75_
- desc: TODO: This enum fulfills the same function as the attribute flags, and will be removed once full Schema support is added to Sessions/Lobbies/Auth
- L73 _public enumerator_ `Public`
- L74 _public enumerator_ `Private`

#### enum `UE::Online::ESchemaAttributeFlags`  
`enum class ESchemaAttributeFlags : uint8`  
_L82-109_
- desc: Flags to indicate required properties for a schema attribute.
- L87 _public enumerator_ `None = 0` — No special properties needed.
- L94 _public enumerator_ `Searchable = 1 << 0` — Attribute is available for search operations. Searchable attributes are required to exist only in a base schema used as a parent of all schema for a particular interface.
- L98 _public enumerator_ `Public = 1 << 1` — Attribute is publicly visible.
- L102 _public enumerator_ `Private = 1 << 2` — Attribute is visible to members only.
- L108 _public enumerator_ `SchemaCompatibilityId = 1 << 3` — If multiple schema are supported using the same service interface, a base schema must exist with a field marked as schema compatibility id. This field will allow remote clients to determine what schema should be used to handle attributes.

#### enum `UE::Online::ESchemaAttributeType`  
`enum class ESchemaAttributeType : uint8`  
_L117-139_
- desc: Flags to indicate the data types supported by a service attribute.
- L122 _public enumerator_ `None` — Unset.
- L126 _public enumerator_ `Bool` — Boolean values.
- L130 _public enumerator_ `Int64` — Signed 64 bit integers.
- L134 _public enumerator_ `Double` — Double precision floating point.
- L138 _public enumerator_ `String` — Variable length string data.

#### enum `UE::Online::ESchemaServiceAttributeFlags`  
`enum class ESchemaServiceAttributeFlags : uint8`  
_L146-164_
- desc: Flags to indicate the available support for a service attribute.
- L151 _public enumerator_ `None = 0` — No special properties needed.
- L155 _public enumerator_ `Searchable = 1 << 0` — Attribute is available for search operations.
- L159 _public enumerator_ `Public = 1 << 1` — Attribute is publicly visible.
- L163 _public enumerator_ `Private = 1 << 2` — Attribute is visible to members only.

#### enum `UE::Online::ESchemaServiceAttributeSupportedTypeFlags`  
`enum class ESchemaServiceAttributeSupportedTypeFlags : uint8`  
_L172-191_
- desc: Flags to indicate the data types supported by a service attribute.
- L174 _public enumerator_ `None = 0`
- L178 _public enumerator_ `Bool = 1 << 0` — Boolean values.
- L182 _public enumerator_ `Int64 = 1 << 1` — Signed 64 bit integers.
- L186 _public enumerator_ `Double = 1 << 2` — Double precision floating point.
- L190 _public enumerator_ `String = 1 << 3` — Variable length string data.

#### class `UE::Online::FSchemaVariant`  
`class FSchemaVariant final`  
_L196-233_
- L199 _public typedef_ `using FVariantType = TVariant<FString, int64, double, bool>;`
- L200 _public prototype_ `FSchemaVariant() = default;`
- L201 _public prototype_ `FSchemaVariant(const FSchemaVariant& InOther) = default;`
- L202 _public prototype_ `FSchemaVariant(FSchemaVariant&& InOther);`
- L203 _public prototype_ `FSchemaVariant& operator=(FSchemaVariant&&);`
- L204 _public prototype_ `FSchemaVariant& operator=(const FSchemaVariant&) = default;`
- L206 _public function_ `FSchemaVariant(const TCHAR* InData)`
- L207 _public function_ `FSchemaVariant(const FString& InData)`
- L208 _public function_ `FSchemaVariant(FString&& InData)`
- L209 _public function_ `FSchemaVariant(int64 InData)`
- L210 _public function_ `FSchemaVariant(double InData)`
- L211 _public function_ `FSchemaVariant(bool InData)`
- L212 _public prototype_ `void Set(const TCHAR* AsString);`
- L213 _public prototype_ `void Set(const FString& AsString);`
- L214 _public prototype_ `void Set(FString&& AsString);`
- L215 _public prototype_ `void Set(int64 AsInt);`
- L216 _public prototype_ `void Set(double AsDouble);`
- L217 _public prototype_ `void Set(bool bAsBool);`
- L219 _public function_ `ESchemaAttributeType GetType() const`
- L221 _public prototype_ `int64 GetInt64() const;`
- L222 _public prototype_ `double GetDouble() const;`
- L223 _public prototype_ `bool GetBoolean() const;`
- L224 _public prototype_ `const FString& GetString() const;`
- L226 _public prototype_ `FString ToLogString() const;`
- L228 _public prototype_ `bool operator==(const FSchemaVariant& Other) const;`
- L229 _public function_ `bool operator!=(const FSchemaVariant& Other) const`
- L231 _public member_ `FVariantType VariantData;`
- L232 _public member_ `ESchemaAttributeType VariantType = ESchemaAttributeType::None;`

#### class `UE::Online::FLexToStringAdaptor`  
`template <typename T> class FLexToStringAdaptor;`  
_L241-250_
- desc: Adaptor for handling LexToString with a schema variant. The adapter prevents unintentional implicit conversion of types to FSchemaVariant when calling LexToString.
- L244 _public function_ `FLexToStringAdaptor(const FSchemaVariant& SchemaVariant) : SchemaVariant(SchemaVariant)`
- L249 _public member_ `const FSchemaVariant& SchemaVariant;`

#### struct `UE::Online::FSchemaServiceAttributeDescriptor`  
`struct FSchemaServiceAttributeDescriptor`  
_L257-278_
- desc: Describes available options for an attribute made available by the underlying service.
- L262 _public member_ `FSchemaServiceAttributeId Id;` — The id to associate with this attribute.
- L266 _public member_ `TArray<ESchemaServiceAttributeSupportedTypeFlags> SupportedTypes;` — Declares what data types can be handled by the service attribute.
- L271 _public member_ `TArray<ESchemaServiceAttributeFlags> Flags;` — Additional behavior required by the attribute. Examples include making an attribute public or available to search.
- L277 _public member_ `int32 MaxSize = 0;` — Declares the maximum allowed size for the service attribute. Applicable when using a variable sized type such as String.

#### struct `UE::Online::FSchemaServiceDescriptor`  
`struct FSchemaServiceDescriptor`  
_L283-293_
- desc: Service descriptor used for declaring a set of attributes a service provides.
- L288 _public member_ `FSchemaServiceDescriptorId Id;` — The id associated with this service descriptor.
- L292 _public member_ `TArray<FSchemaServiceAttributeId> AttributeIds;` — Service attribute descriptions.

#### struct `UE::Online::FSchemaAttributeDescriptor`  
`struct FSchemaAttributeDescriptor`  
_L298-327_
- desc: Describes the required attribute configuration for a schema attribute.
- L303 _public member_ `FSchemaAttributeId Id;` — The id to associate with this attribute.
- L307 _public member_ `ESchemaAttributeType Type = ESchemaAttributeType::None;` — The type of data contained within the attribute.
- L312 _public member_ `TArray<ESchemaAttributeFlags> Flags;` — Additional behavior required by the attribute. Examples include making an attribute public or available to search.
- L320 _public member_ `int32 UpdateGroupId = 0;` — Whether to group the attribute together with other attributes explicitly. Providing a group id allows the client to explicitly serialize attributes to the same service attribute for increased network efficiency. Id 0 uses automatic grouping.
- L326 _public member_ `int32 MaxSize = 0;` — Declares the maximum allowed serialized size for a variably sized attribute. Applicable when using a variable sized type such as String.

#### struct `UE::Online::FSchemaCategoryDescriptor`  
`struct FSchemaCategoryDescriptor`  
_L332-346_
- desc: Describes a category within a schema.
- L339 _public member_ `FSchemaCategoryId Id;` — Category for which the schema applies. Example: "Lobby" vs "LobbyMember"
- L345 _public member_ `FSchemaServiceDescriptorId ServiceDescriptorId;` — Service descriptor to use for initializing schema. May be empty when a schema only applies to local data. May only be set by base parent schema.

#### struct `UE::Online::FSchemaCategoryAttributesDescriptor`  
`struct FSchemaCategoryAttributesDescriptor`  
_L351-365_
- desc: Adds a set of attributes to a given category in a given schema.
- L356 _public member_ `FSchemaId SchemaId;` — The schema to add attributes to.
- L360 _public member_ `FSchemaCategoryId CategoryId;` — The category to add attributes to.
- L364 _public member_ `TArray<FSchemaAttributeId> AttributeIds;` — The attributes to add.

#### struct `UE::Online::FSchemaDescriptor`  
`struct FSchemaDescriptor`  
_L370-386_
- desc: Describes all properties needed to use a schema.
- L375 _public member_ `FSchemaId Id;` — The id associated with this schema.
- L380 _public member_ `FSchemaId ParentId;` — Parent schema (not required). Attributes used in a parent schema may not be modified by a child schema.
- L385 _public member_ `TArray<FSchemaCategoryId> CategoryIds;` — Categories of data within the schema. Each category is handled differently within the service so will have different configuration of attributes and service attributes.

#### struct `UE::Online::FSchemaRegistryDescriptorConfig`  
`struct FSchemaRegistryDescriptorConfig`  
_L391-418_
- desc: Set of all descriptors used to initialize a SchemaRegistry.
- L396 _public member_ `TArray<FSchemaDescriptor> SchemaDescriptors;` — List of all supported schema.
- L400 _public member_ `TArray<FSchemaCategoryDescriptor> SchemaCategoryDescriptors;` — List of all schema categories
- L404 _public member_ `TArray<FSchemaAttributeDescriptor> SchemaAttributeDescriptors;` — List of all schema attributes
- L408 _public member_ `TArray<FSchemaCategoryAttributesDescriptor> SchemaCategoryAttributeDescriptors;` — List of additional attributes to add to the given category for the given schema.
- L413 _public member_ `TArray<FSchemaServiceDescriptor> ServiceDescriptors;` — List of all service descriptors.
- L417 _public member_ `TArray<FSchemaServiceAttributeDescriptor> ServiceAttributeDescriptors;` — List of all service attributes

#### struct `UE::Online::FSchemaServiceAttributeDefinition`  
`struct FSchemaServiceAttributeDefinition`  
_L423-448_
- desc: The runtime definition of a schema service attribute.
- L428 _public member_ `FSchemaServiceAttributeId Id;` — The id to associate with this attribute.
- L432 _public member_ `ESchemaServiceAttributeSupportedTypeFlags Type;` — The supported type. Only one type is supported in a service attribute definition.
- L437 _public member_ `ESchemaServiceAttributeFlags Flags = ESchemaServiceAttributeFlags::None;` — Additional behavior required by the attribute. Examples include making an attribute public, private or available to search.
- L443 _public member_ `int32 MaxSize = 0;` — Declares the maximum allowed size for the service attribute. Applicable when using a variable sized type such as String.
- L447 _public member_ `TArray<FSchemaAttributeId> SchemaAttributeIds;` — The attribute ids contained within the service attribute.

#### struct `UE::Online::FSchemaAttributeDefinition`  
`struct FSchemaAttributeDefinition`  
_L453-478_
- desc: The runtime definition of a schema attribute.
- L458 _public member_ `FSchemaAttributeId Id;` — The id to associate with this attribute.
- L462 _public member_ `ESchemaAttributeType Type = ESchemaAttributeType::None;` — The type of data contained within the attribute.
- L467 _public member_ `ESchemaAttributeFlags Flags;` — Additional behavior required by the attribute. Examples include making an attribute public, private or available to search.
- L473 _public member_ `int32 MaxSize = 0;` — Declares the maximum allowed serialized size for a variably sized attribute. Applicable when using a variable sized type such as String.
- L477 _public member_ `FSchemaServiceAttributeId ServiceAttributeId;` — The id of the associated service attribute.

#### struct `UE::Online::FSchemaCategoryDefinition`  
`struct FSchemaCategoryDefinition`  
_L484-512_
- desc: The runtime definition of a schema category. The contained data can be used for validation and translation.
- L491 _public member_ `FSchemaCategoryId Id;` — Category for which the schema applies. Example: "Lobby" vs "LobbyMember"
- L497 _public member_ `FSchemaAttributeId SchemaCompatibilityAttributeId;` — The Id of the attribute containing the schema compatibility id. Changes to the schema compatibility attribute are not allowed externally. This id is used to fail attempted external changes.
- L503 _public member_ `FSchemaServiceAttributeId SchemaCompatibilityServiceAttributeId;` — The Id of the service attribute containing the schema compatibility id. This Id is used to detect the schema to use when handling search results and to handle schema changes when the remote owner makes a change.
- L507 _public member_ `TMap<FSchemaAttributeId, FSchemaAttributeDefinition> SchemaAttributeDefinitions;` — Mapping of schema attribute ids to attribute definitions.
- L511 _public member_ `TMap<FSchemaServiceAttributeId, FSchemaServiceAttributeDefinition> ServiceAttributeDefinitions;` — Mapping of service attribute ids to service attribute definitions.

#### struct `UE::Online::FSchemaDefinition`  
`struct FSchemaDefinition`  
_L518-537_
- desc: The runtime definition of a schema. The contained data can be used for validation and translation.
- L523 _public member_ `FSchemaId Id;` — The id associated with this schema.
- L528 _public member_ `int64 CompatibilityId = 0;` — The compatibility id consists of the CRC of the schema name in the top 32 bits and the CRC of all the schema options in the bottom 32 bits.
- L532 _public member_ `TMap<FSchemaCategoryId, FSchemaCategoryDefinition> Categories;` — Supported categories within the schema.
- L536 _public member_ `TSet<FSchemaId> ParentSchemaIds;` — Set of parent schema ids for parent checks.

#### struct `UE::Online::FSchemaServiceAttributeData`  
`struct FSchemaServiceAttributeData`  
_L542-557_
- desc: The set of data used to write a variant to a service.
- L547 _public member_ `FSchemaServiceAttributeId Id;` — The id to associate with this attribute.
- L552 _public member_ `ESchemaServiceAttributeFlags Flags = ESchemaServiceAttributeFlags::None;` — Additional behavior required by the attribute. Examples include making an attribute public or available to search.
- L556 _public member_ `FSchemaVariant Value;` — The attribute value.

#### struct `UE::Online::FSchemaServiceSnapshot`  
`struct FSchemaServiceSnapshot`  
_L560-563_
- desc: Full snapshot of all set service attributes.
- L562 _public member_ `TMap<FSchemaServiceAttributeId, FSchemaVariant> Attributes;`

#### struct `UE::Online::FSchemaClientChanges`  
`struct FSchemaClientChanges`  
_L568-582_
- desc: Changes from the client data to be translated into service changes.
- L573 _public member_ `TOptional<FSchemaId> SchemaId;` — Change to schema id.
- L577 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> UpdatedAttributes;` — Added or changed attributes and their values.
- L581 _public member_ `TSet<FSchemaAttributeId> RemovedAttributes;` — Attributes to be cleared.

#### struct `UE::Online::FSchemaClientServiceChanges`  
`struct FSchemaClientServiceChanges`  
_L587-597_
- desc: Changes to be applied to the service data following client schema attribute changes.
- L592 _public member_ `TMap<FSchemaServiceAttributeId, FSchemaServiceAttributeData> UpdatedAttributes;` — Added or changed attributes and their values.
- L596 _public member_ `TSet<FSchemaServiceAttributeId> RemovedAttributes;` — Removed attribute ids.

#### struct `UE::Online::FSchemaServiceClientChanges`  
`struct FSchemaServiceClientChanges`  
_L602-620_
- desc: Changes to be applied to the client data following service attribute changes.
- L607 _public member_ `TOptional<FSchemaId> SchemaId;` — Change to schema id.
- L611 _public member_ `TMap<FSchemaAttributeId, FSchemaVariant> AddedAttributes;` — Added attributes.
- L615 _public member_ `TMap<FSchemaAttributeId, TPair<FSchemaVariant, FSchemaVariant>> ChangedAttributes;` — Changed attributes with their old and new values.
- L619 _public member_ `TSet<FSchemaAttributeId> RemovedAttributes;` — Removed attribute ids.

#### struct `UE::Online::FSchemaCategoryInstancePrepareClientChanges`  
`struct FSchemaCategoryInstancePrepareClientChanges`  
_L622-635_

#### struct `UE::Online::FSchemaCategoryInstancePrepareClientChanges::Params`  
`struct Params`  
_L624-628_
- L627 _public member_ `FSchemaClientChanges ClientChanges;` — Changes from the client to be applied to the service.

#### struct `UE::Online::FSchemaCategoryInstancePrepareClientChanges::Result`  
`struct Result`  
_L630-634_
- L633 _public member_ `FSchemaClientServiceChanges ServiceChanges;` — Attribute changes to be notified to the service.

#### struct `UE::Online::FSchemaCategoryInstanceCommitClientChanges`  
`struct FSchemaCategoryInstanceCommitClientChanges`  
_L637-644_

#### struct `UE::Online::FSchemaCategoryInstanceCommitClientChanges::Result`  
`struct Result`  
_L639-643_
- L642 _public member_ `FSchemaServiceClientChanges ClientChanges;` — Attribute changes to be notified to the client.

#### struct `UE::Online::FSchemaCategoryInstancePrepareServiceSnapshot`  
`struct FSchemaCategoryInstancePrepareServiceSnapshot`  
_L646-661_

#### struct `UE::Online::FSchemaCategoryInstancePrepareServiceSnapshot::Params`  
`struct Params`  
_L648-654_
- L651 _public member_ `TOptional<FSchemaId> SchemaId;` — Optional schema id for applying a schema change from external state.
- L653 _public member_ `FSchemaServiceSnapshot ServiceSnapshot;` — Full attribute snapshot from the service.

#### struct `UE::Online::FSchemaCategoryInstancePrepareServiceSnapshot::Result`  
`struct Result`  
_L656-660_
- L659 _public member_ `TOptional<FSchemaId> DerivedSchemaId;` — The new derived schema id when set from the service.

#### struct `UE::Online::FSchemaCategoryInstanceCommitServiceSnapshot`  
`struct FSchemaCategoryInstanceCommitServiceSnapshot`  
_L663-670_

#### struct `UE::Online::FSchemaCategoryInstanceCommitServiceSnapshot::Result`  
`struct Result`  
_L665-669_
- L668 _public member_ `FSchemaServiceClientChanges ClientChanges;` — Attribute changes to be notified to the client.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ONLINESERVICESINTERFACE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L13 _namespace_ `namespace Meta` (scope `UE::Online`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Online` (scope `UE`)
- L18 _typedef_ `using FSchemaId = FName;` (scope `UE::Online`) — Schema name - used to lookup and interact with a schema.
- L30 _typedef_ `using FSchemaCategoryId = FName;` (scope `UE::Online`) — Category within a schema. Most schema will have two sets of configuration - one for the singular object and one for member data within that object. The category name is expected to be built into the code which uses a schema and is not expected to change. A schema may not add any categories not already declared in the parent schema. Example: A lobby contains both lobby data and lobby member data, but during lobby creation the client only specifies a single schema Id. The schema id is required to have categories for both Lobby and LobbyMember.
- L35 _typedef_ `using FSchemaAttributeId = FName;` (scope `UE::Online`) — The id used to refer to a schema attribute. These ids are declared in the client config and used in client code to look up an attribute value.
- L40 _typedef_ `using FSchemaServiceAttributeId = FName;` (scope `UE::Online`) — The id used to refer to a schema service attribute. These ids are declared in config and used directly by the platform service when serializing attributes.
- L52 _typedef_ `using FSchemaServiceDescriptorId = FName;` (scope `UE::Online`) — The id used to refer to a schema service descriptor. Similar to a schema, service descriptors declare a set of attributes. Service descriptors are tied directly to how a service serializes data to its backend. Example: In the case of a lobby the backing service is capable of storing attributes for a lobby and a lobby member. There will be separate service descriptors for lobby and lobby member where each will list the attributes available to be set as well as the types of data each attribute can store. The lobby implementation refers to the attributes names in the service descriptor directly when handling the serialization of attributes.
- L67 _prototype_ `const TCHAR* LexToString(ESchemaAttributeComparisonOp EnumVal);` (scope `UE::Online`)
- L68 _prototype_ `void LexFromString(ESchemaAttributeComparisonOp& OutComparison, const TCHAR* InStr);` (scope `UE::Online`)
- L76 _prototype_ `const TCHAR* LexToString(ESchemaAttributeVisibility Visibility);` (scope `UE::Online`)
- L77 _prototype_ `void LexFromString(ESchemaAttributeVisibility& OutVisibility, const TCHAR* InStr);` (scope `UE::Online`)
- L110 _prototype_ `ENUM_CLASS_FLAGS(ESchemaAttributeFlags);` (scope `UE::Online`)
- L111 _prototype_ `const TCHAR* LexToString(ESchemaAttributeFlags SchemaAttributeFlags);` (scope `UE::Online`)
- L112 _prototype_ `void LexFromString(ESchemaAttributeFlags& OutSchemaAttributeFlags, const TCHAR* InStr);` (scope `UE::Online`)
- L140 _prototype_ `const TCHAR* LexToString(ESchemaAttributeType SchemaAttributeType);` (scope `UE::Online`)
- L141 _prototype_ `void LexFromString(ESchemaAttributeType& OutSchemaAttributeType, const TCHAR* InStr);` (scope `UE::Online`)
- L165 _prototype_ `ENUM_CLASS_FLAGS(ESchemaServiceAttributeFlags);` (scope `UE::Online`)
- L166 _prototype_ `const TCHAR* LexToString(ESchemaServiceAttributeFlags SchemaServiceAttributeFlags);` (scope `UE::Online`)
- L167 _prototype_ `void LexFromString(ESchemaServiceAttributeFlags& OutSchemaServiceAttributeFlags, const TCHAR* InStr);` (scope `UE::Online`)
- L192 _prototype_ `ENUM_CLASS_FLAGS(ESchemaServiceAttributeSupportedTypeFlags);` (scope `UE::Online`)
- L193 _prototype_ `const TCHAR* LexToString(ESchemaServiceAttributeSupportedTypeFlags SchemaServiceAttributeSupportedTypeFlags);` (scope `UE::Online`)
- L194 _prototype_ `void LexFromString(ESchemaServiceAttributeSupportedTypeFlags& OutSchemaServiceAttributeSupportedTypeFlags, const TCHAR* InStr);` (scope `UE::Online`)
- L251 _prototype_ `const FString LexToString(const FLexToStringAdaptor<FSchemaVariant>& Adaptor);` (scope `UE::Online`)
- L252 _prototype_ `void LexFromString(FSchemaVariant& OutSchemaVariant, const TCHAR* InStr);` (scope `UE::Online`)
- L672 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/Sessions.h` (Public)


#### struct `UE::Online::FFindSessionsSearchFilter`  
`struct FFindSessionsSearchFilter`  
_L20-30_
- desc: Filter class for a session search, will be compared against the session's CustomSettings
- L23 _public member_ `FSchemaAttributeId Key;` — Name of the custom setting to be used as filter
- L26 _public member_ `ESchemaAttributeComparisonOp ComparisonOp;` — The type of comparison to perform
- L29 _public member_ `FSchemaVariant Value;` — Value to use when comparing the filter

#### struct `UE::Online::FCustomSessionSetting`  
`struct FCustomSessionSetting`  
_L33-43_
- desc: User-defined data to be stored along with the session information. Will be evaluated in session searches
- L36 _public member_ `FSchemaVariant Data;` — Setting data value
- L39 _public member_ `ESchemaAttributeVisibility Visibility;` — Manner in which this session setting is advertised with the backend or searches
- L42 _public member_ `int32 ID;` — Optional ID used in some platforms as the index instead of the setting name

#### struct `UE::Online::FCustomSessionSettingUpdate`  
`struct FCustomSessionSettingUpdate`  
_L48-55_
- desc: Contains both the old and new values for an updated FCustomSessionSetting. Part of the FSessionUpdate event data
- L51 _public member_ `FCustomSessionSetting OldValue;` — Old value for the updated Setting
- L54 _public member_ `FCustomSessionSetting NewValue;` — New value for the updated Setting

#### enum `UE::Online::ESessionJoinPolicy`  
`enum class ESessionJoinPolicy : uint8`  
_L62-72_
- desc: Set of options to reflect how a session may be discovered in searches and joined
- L65 _public enumerator_ `Public` — The session will appear on searches an may be joined by anyone
- L68 _public enumerator_ `FriendsOnly` — The session will not appear on searches and may only be joined via presence (if enabled) or invitation
- L71 _public enumerator_ `InviteOnly` — The session will not appear on searches and may not be joined via presence, only via invitation

#### struct `UE::Online::FSessionSettingsUpdate`  
`struct FSessionSettingsUpdate`  
_L77-94_
- desc: Contains new values for an FSessions modifiable settings. Taken as a parameter by FUpdateSessionSettings method
- L80 _public member_ `TOptional<FSchemaId> SchemaName;` — Set with an updated value if the SchemaName field will be changed in the update operation
- L82 _public member_ `TOptional<uint32> NumMaxConnections;` — Set with an updated value if the NumMaxConnections field will be changed in the update operation
- L84 _public member_ `TOptional<ESessionJoinPolicy> JoinPolicy;` — Set with an updated value if the JoinPolicy field will be changed in the update operation
- L86 _public member_ `TOptional<bool> bAllowNewMembers;` — Set with an updated value if the bAllowNewMembers field will be changed in the update operation
- L89 _public member_ `FCustomSessionSettingsMap UpdatedCustomSettings;` — Updated values for custom settings to change in the update operation
- L91 _public member_ `TArray<FSchemaAttributeId> RemovedCustomSettings;` — Names of custom settings to be removed in the update operation
- L93 _public prototype_ `FSessionSettingsUpdate& operator+=(FSessionSettingsUpdate&& UpdatedValue);`

#### struct `UE::Online::FSessionSettingsChanges`  
`struct FSessionSettingsChanges`  
_L97-116_
- desc: Contains updated data for any modifiable members of FSessionSettings. Part of the FSessionUpdated event data
- L100 _public member_ `TOptional<FName> SchemaName;` — If set, the FSessionSettings's SchemaName member will have been updated to this value
- L102 _public member_ `TOptional<uint32> NumMaxConnections;` — If set, the FSessionSettings's NumMaxConnections member will have been updated to this value
- L104 _public member_ `TOptional<ESessionJoinPolicy> JoinPolicy;` — If set, the FSessionSettings's JoinPolicy member will have been updated to this value
- L106 _public member_ `TOptional<bool> bAllowNewMembers;` — If set, the FSessionSettings's bAllowNewMembers member will have been updated to this value
- L109 _public member_ `FCustomSessionSettingsMap AddedCustomSettings;` — New custom settings added in the update, with their values
- L112 _public member_ `FCustomSessionSettingUpdateMap ChangedCustomSettings;` — Existing custom settings that changed value, including new and old values
- L115 _public member_ `TArray<FName> RemovedCustomSettings;` — Keys for custom settings removed in the update

#### struct `UE::Online::FSessionSettings`  
`struct FSessionSettings`  
_L119-137_
- desc: Set of all of an FSession's defining properties that can be updated by the session owner during its lifetime, using the FUpdateSessionSettings method
- L122 _public member_ `FName SchemaName;` — The name for the schema which will be applied to the session's user-defined attributes
- L125 _public member_ `uint32 NumMaxConnections = 0;` — Maximum number of slots for session members
- L128 _public member_ `ESessionJoinPolicy JoinPolicy = ESessionJoinPolicy::Public;` — Enum value describing the level of restriction to join the session. Public by default
- L131 _public member_ `bool bAllowNewMembers = true;` — Override value to restrict the session from accepting new members, regardless of other factors. True by default
- L134 _public member_ `FCustomSessionSettingsMap CustomSettings;` — Map of user-defined settings to be passed to the platform APIs as additional information for various purposes
- L136 _public prototype_ `FSessionSettings& operator+=(const FSessionSettingsChanges& UpdatedValue);`

#### struct `UE::Online::FSessionInfo`  
`struct FSessionInfo`  
_L140-159_
- desc: Information about an FSession that will be set at creation time and remain constant during its lifetime
- L143 _public member_ `FOnlineSessionId SessionId;` — The id handle for the session, platform dependent
- L146 _public member_ `FString SessionIdOverride;` — In platforms that support this feature, it will set the session id to this value. Might be subject to minimum and maximum length restrictions
- L149 _public member_ `bool bIsLANSession = false;` — Whether the session is only available in the local network and not via internet connection. Only available in some platforms. False by default
- L152 _public member_ `bool bIsDedicatedServerSession = false;` — Whether the session is configured to run as a dedicated server. Only available in some platforms. False by default
- L155 _public member_ `bool bAllowSanctionedPlayers = true;` — Whether this session will allow sanctioned players to join it. True by default
- L158 _public member_ `bool bAntiCheatProtected = false;` — Whether this is a secure session protected by anti-cheat services. False by default

#### class `UE::Online::ISession`  
`class ISession`  
_L162-193_
- desc: Interface to access all information related to Online Sessions. Read only
- L165 _public prototype_ `virtual ~ISession() = default;`
- L168 _public prototype_ `virtual const FAccountId GetOwnerAccountId() const = 0;` — Retrieves the id handle for the user who created or currently owns the session
- L171 _public prototype_ `virtual const FOnlineSessionId GetSessionId() const = 0;` — Retrieves the id handle for the session
- L174 _public prototype_ `virtual const uint32 GetNumOpenConnections() const = 0;` — Retrieves the number of available slots for new session members
- L177 _public prototype_ `virtual const FSessionInfo& GetSessionInfo() const = 0;` — Retrieves the set of constant information about the session
- L180 _public prototype_ `virtual const FSessionSettings& GetSessionSettings() const = 0;` — Retrieves the set of variable information about the session
- L183 _public prototype_ `virtual const FSessionMemberIdsSet& GetSessionMembers() const = 0;` — Retrieves the list of users currently in the session
- L186 _public prototype_ `virtual bool IsJoinable() const = 0;` — Evaluates a series of factors to determine if a session is accepting new members
- L189 _public prototype_ `virtual FString ToLogString() const = 0;` — Returns a string with the minimal information to identify the session
- L192 _public prototype_ `virtual void DumpState() const = 0;` — Returns a string with all the information in the session

#### class `UE::Online::ISessionInvite`  
`class ISessionInvite`  
_L197-209_
- desc: Interface to access all information about an invitation to join an Online Session. Read only
- L201 _public prototype_ `virtual const FAccountId GetRecipientId() const = 0;` — Retrieves the id handle for the user who received the invite
- L204 _public prototype_ `virtual const FAccountId GetSenderId() const = 0;` — Retrieves the id handle for the user who sent the invite
- L205 _public prototype_ `virtual const FSessionInviteId GetInviteId() const = 0;`
- L206 _public prototype_ `virtual const FOnlineSessionId GetSessionId() const = 0;`
- L208 _public prototype_ `virtual FString ToLogString() const = 0;`

#### struct `UE::Online::FGetAllSessions`  
`struct FGetAllSessions`  
_L214-229_
- L216 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetAllSessions::Params`  
`struct Params`  
_L218-222_
- L221 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action

#### struct `UE::Online::FGetAllSessions::Result`  
`struct Result`  
_L224-228_
- L227 _public member_ `TArray<TSharedRef<const ISession>> Sessions;` — Array of sessions that the given user is member of

#### struct `UE::Online::FGetSessionByName`  
`struct FGetSessionByName`  
_L231-246_
- L233 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetSessionByName::Params`  
`struct Params`  
_L235-239_
- L238 _public member_ `FName LocalName;` — Local name for the session

#### struct `UE::Online::FGetSessionByName::Result`  
`struct Result`  
_L241-245_
- L244 _public member_ `TSharedRef<const ISession> Session;` — Reference to the session mapped to the given name

#### struct `UE::Online::FGetSessionName`  
`struct FGetSessionName`  
_L248-263_
- L250 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetSessionName::Params`  
`struct Params`  
_L252-256_
- L255 _public member_ `FOnlineSessionId SessionId;` — Id handle for the session to be retrieved the name from

#### struct `UE::Online::FGetSessionName::Result`  
`struct Result`  
_L258-262_
- L261 _public member_ `FName SessionName;` — Session name

#### struct `UE::Online::FGetSessionById`  
`struct FGetSessionById`  
_L265-280_
- L267 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetSessionById::Params`  
`struct Params`  
_L269-273_
- L272 _public member_ `FOnlineSessionId SessionId;` — Id handle for the session to be retrieved

#### struct `UE::Online::FGetSessionById::Result`  
`struct Result`  
_L275-279_
- L278 _public member_ `TSharedRef<const ISession> Session;` — Reference to the session mapped to the given id

#### struct `UE::Online::FGetPresenceSession`  
`struct FGetPresenceSession`  
_L282-297_
- L284 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetPresenceSession::Params`  
`struct Params`  
_L286-290_
- L289 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action

#### struct `UE::Online::FGetPresenceSession::Result`  
`struct Result`  
_L292-296_
- L295 _public member_ `TSharedRef<const ISession> Session;` — Reference to the session set as presence session for the given user

#### struct `UE::Online::FIsPresenceSession`  
`struct FIsPresenceSession`  
_L299-317_
- L301 _public member_ `static constexpr TCHAR Name[] = TEXT("IsP`

#### struct `UE::Online::FIsPresenceSession::Params`  
`struct Params`  
_L303-310_
- L306 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action
- L309 _public member_ `FOnlineSessionId SessionId;` — Id handle for the session to be compared

#### struct `UE::Online::FIsPresenceSession::Result`  
`struct Result`  
_L312-316_
- L315 _public member_ `bool bIsPresenceSession;` — Whether the session mapped to the given id is set as the presence session for the given user

#### struct `UE::Online::FSetPresenceSession`  
`struct FSetPresenceSession`  
_L319-335_
- L321 _public member_ `static constexpr TCHAR Name[] = TEXT("Set`

#### struct `UE::Online::FSetPresenceSession::Params`  
`struct Params`  
_L323-330_
- L326 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action
- L329 _public member_ `FOnlineSessionId SessionId;` — Id handle for the session

#### struct `UE::Online::FSetPresenceSession::Result`  
`struct Result`  
_L332-334_

#### struct `UE::Online::FClearPresenceSession`  
`struct FClearPresenceSession`  
_L337-350_
- L339 _public member_ `static constexpr TCHAR Name[] = TEXT("Cle`

#### struct `UE::Online::FClearPresenceSession::Params`  
`struct Params`  
_L341-345_
- L344 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action

#### struct `UE::Online::FClearPresenceSession::Result`  
`struct Result`  
_L347-349_

#### struct `UE::Online::FCreateSession`  
`struct FCreateSession`  
_L352-387_
- L354 _public member_ `static constexpr TCHAR Name[] = TEXT("Cre`

#### struct `UE::Online::FCreateSession::Params`  
`struct Params`  
_L356-381_
- L359 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action
- L362 _public member_ `FName SessionName;` — Local name for the session
- L365 _public member_ `FString SessionIdOverride;` — In platforms that support this feature, it will set the session id to this value. Might be subject to minimum and maximum length restrictions
- L368 _public member_ `bool bPresenceEnabled = false;` — Whether this session should be set as the local user's new presence session. False by default
- L371 _public member_ `bool bIsLANSession = false;` — Whether the session is only available via the local network and not via internet connection. Only available in some platforms. False by default
- L374 _public member_ `bool bAllowSanctionedPlayers = true;` — Whether this session will allow sanctioned players to join it. True by default
- L377 _public member_ `bool bAntiCheatProtected = false;` — Whether this is a secure session protected by anti-cheat services. False by default
- L380 _public member_ `FSessionSettings SessionSettings;` — Settings object to define session properties during creation

#### struct `UE::Online::FCreateSession::Result`  
`struct Result`  
_L383-386_

#### struct `UE::Online::FUpdateSessionSettings`  
`struct FUpdateSessionSettings`  
_L389-409_
- L391 _public member_ `static constexpr TCHAR Name[] = TEXT("Upd`

#### struct `UE::Online::FUpdateSessionSettings::Params`  
`struct Params`  
_L393-403_
- L396 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action
- L399 _public member_ `FName SessionName;` — Local name for the session
- L402 _public member_ `FSessionSettingsUpdate Mutations;` — Changes to current session settings

#### struct `UE::Online::FUpdateSessionSettings::Result`  
`struct Result`  
_L405-408_

#### struct `UE::Online::FLeaveSession`  
`struct FLeaveSession`  
_L411-431_
- L413 _public member_ `static constexpr TCHAR Name[] = TEXT("Lea`

#### struct `UE::Online::FLeaveSession::Params`  
`struct Params`  
_L415-425_
- L418 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action
- L421 _public member_ `FName SessionName;` — Local name for the session
- L424 _public member_ `bool bDestroySession;` — Whether the call should attempt to destroy the session instead of just leave it

#### struct `UE::Online::FLeaveSession::Result`  
`struct Result`  
_L427-430_

#### struct `UE::Online::FFindSessions`  
`struct FFindSessions`  
_L433-462_
- L435 _public member_ `static constexpr TCHAR Name[] = TEXT("Fin`

#### struct `UE::Online::FFindSessions::Params`  
`struct Params`  
_L437-456_
- L440 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action
- L443 _public member_ `uint32 MaxResults;` — Maximum number of results to return in the search
- L446 _public member_ `bool bFindLANSessions = false;` — Whether we want to look for LAN sessions (true) or Online sessions (false). False by default
- L449 _public member_ `TArray<FFindSessionsSearchFilter> Filters;` — Filters to apply when searching for sessions.
- L452 _public member_ `TOptional<FAccountId> TargetUser;` — If set, the search will look for sessions containing the set user.
- L455 _public member_ `TOptional<FOnlineSessionId> SessionId;` — If set, the search will look for the session with the set session id.

#### struct `UE::Online::FFindSessions::Result`  
`struct Result`  
_L458-461_
- L460 _public member_ `TArray<FOnlineSessionId> FoundSessionIds;`

#### struct `UE::Online::FStartMatchmaking`  
`struct FStartMatchmaking`  
_L464-481_
- L466 _public member_ `static constexpr TCHAR Name[] = TEXT("Sta`

#### struct `UE::Online::FStartMatchmaking::Params`  
`struct Params`  
_L468-475_
- L471 _public member_ `FCreateSession::Params SessionCreationParameters;` — Session creation parameters
- L474 _public member_ `TArray<FFindSessionsSearchFilter> SessionSearchFilters;` — Filters to apply when searching for sessions

#### struct `UE::Online::FStartMatchmaking::Result`  
`struct Result`  
_L477-480_

#### struct `UE::Online::FJoinSession`  
`struct FJoinSession`  
_L483-509_
- L485 _public member_ `static constexpr TCHAR Name[] = TEXT("Joi`

#### struct `UE::Online::FJoinSession::Params`  
`struct Params`  
_L487-503_
- L490 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action
- L493 _public member_ `FName SessionName;` — Local name for the session
- L496 _public member_ `FOnlineSessionId SessionId;` — Id handle for the session to be joined. To be retrieved via session search, invite or UI operation
- L499 _public member_ `bool bPresenceEnabled = false;` — Whether this session should be set as the user's new presence session. False by default
- L502 _public member_ `bool bJoinAsSpectator = false;` — Whether to join as a spectator instead of player

#### struct `UE::Online::FJoinSession::Result`  
`struct Result`  
_L505-508_

#### struct `UE::Online::FAddSessionMember`  
`struct FAddSessionMember`  
_L511-528_
- L513 _public member_ `static constexpr TCHAR Name[] = TEXT("Add`

#### struct `UE::Online::FAddSessionMember::Params`  
`struct Params`  
_L515-522_
- L518 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action
- L521 _public member_ `FName SessionName;` — Local name for the session

#### struct `UE::Online::FAddSessionMember::Result`  
`struct Result`  
_L524-527_

#### struct `UE::Online::FRemoveSessionMember`  
`struct FRemoveSessionMember`  
_L530-549_
- L532 _public member_ `static constexpr TCHAR Name[] = TEXT("Rem`

#### struct `UE::Online::FRemoveSessionMember::Params`  
`struct Params`  
_L534-543_
- L537 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action
- L540 _public member_ `FAccountId TargetAccountId;` — Id handle for the user to be kicked
- L542 _public member_ `FName SessionName;` — Local name for the session

#### struct `UE::Online::FRemoveSessionMember::Result`  
`struct Result`  
_L545-548_

#### struct `UE::Online::FSendSessionInvite`  
`struct FSendSessionInvite`  
_L551-571_
- L553 _public member_ `static constexpr TCHAR Name[] = TEXT("Sen`

#### struct `UE::Online::FSendSessionInvite::Params`  
`struct Params`  
_L555-565_
- L558 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action
- L561 _public member_ `FName SessionName;` — Local name for the session
- L564 _public member_ `TArray<FAccountId> TargetUsers;` — Array of id handles for users to which the invites will be sent

#### struct `UE::Online::FSendSessionInvite::Result`  
`struct Result`  
_L567-570_

#### struct `UE::Online::FGetSessionInviteById`  
`struct FGetSessionInviteById`  
_L573-591_
- L575 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetSessionInviteById::Params`  
`struct Params`  
_L577-584_
- L580 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action
- L583 _public member_ `FSessionInviteId SessionInviteId;` — Id handle for the invite to be retrieved

#### struct `UE::Online::FGetSessionInviteById::Result`  
`struct Result`  
_L586-590_
- L589 _public member_ `TSharedRef<const ISessionInvite> SessionInvite;` — Reference to the invite mapped to the given id

#### struct `UE::Online::FGetAllSessionInvites`  
`struct FGetAllSessionInvites`  
_L593-608_
- L595 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetAllSessionInvites::Params`  
`struct Params`  
_L597-601_
- L600 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action

#### struct `UE::Online::FGetAllSessionInvites::Result`  
`struct Result`  
_L603-607_
- L606 _public member_ `TArray<TSharedRef<const ISessionInvite>> SessionInvites;` — Array of invites received by the given user

#### struct `UE::Online::FRejectSessionInvite`  
`struct FRejectSessionInvite`  
_L610-626_
- L612 _public member_ `static constexpr TCHAR Name[] = TEXT("Rej`

#### struct `UE::Online::FRejectSessionInvite::Params`  
`struct Params`  
_L614-621_
- L617 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which will perform the action
- L620 _public member_ `FSessionInviteId SessionInviteId;` — Id handle for the session invite to be rejected

#### struct `UE::Online::FRejectSessionInvite::Result`  
`struct Result`  
_L623-625_

#### struct `UE::Online::FSessionCreated`  
`struct FSessionCreated`  
_L630-637_
- L633 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user who created the session
- L636 _public member_ `FOnlineSessionId SessionId;` — Id handle for the session created.

#### struct `UE::Online::FSessionJoined`  
`struct FSessionJoined`  
_L639-646_
- L642 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user who joined the session
- L645 _public member_ `FOnlineSessionId SessionId;` — Id handle for the session joined.

#### struct `UE::Online::FSessionLeft`  
`struct FSessionLeft`  
_L648-652_
- L651 _public member_ `FAccountId LocalAccountId;` — Id handle for the local users which left the session

#### struct `UE::Online::FSessionUpdate`  
`struct FSessionUpdate`  
_L655-670_
- desc: Contains updated data for any modifiable members of ISession
- L658 _public member_ `TOptional<FAccountId> OwnerAccountId;` — If set, the OwnerUserId member will have updated to this value
- L661 _public member_ `TOptional<FSessionSettingsChanges> SessionSettingsChanges;` — If set, the SessionSettings member will have updated using the struct information
- L664 _public member_ `FSessionMemberIdsSet AddedSessionMembers;` — Id handles for members that just joined the session
- L667 _public member_ `FSessionMemberIdsSet RemovedSessionMembers;` — Id handles for members that just left the session
- L669 _public prototype_ `FSessionUpdate& operator+=(const FSessionUpdate& SessionUpdate);`

#### struct `UE::Online::FSessionUpdated`  
`struct FSessionUpdated`  
_L672-679_
- L675 _public member_ `FName SessionName;` — Local name for the updated session
- L678 _public member_ `FSessionUpdate SessionUpdate;` — Updated session information

#### struct `UE::Online::FSessionInviteReceived`  
`struct FSessionInviteReceived`  
_L681-688_
- L684 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user which received the invite
- L687 _public member_ `FSessionInviteId SessionInviteId;` — The session invite id for the invite received

#### enum `UE::Online::EUISessionJoinRequestedSource`  
`enum class EUISessionJoinRequestedSource : uint8`  
_L690-696_
- L693 _public enumerator_ `Unspecified` — Unspecified by the online service
- L695 _public enumerator_ `FromInvitation` — From an invitation

#### struct `UE::Online::FUISessionJoinRequested`  
`struct FUISessionJoinRequested`  
_L700-710_
- L703 _public member_ `FAccountId LocalAccountId;` — Id handle for the local user associated with the join request
- L706 _public member_ `TResult<FOnlineSessionId, FOnlineError> Result;` — Id handle for the session the local user requested to join, or the online error if there was a failure retrieving it
- L709 _public member_ `EUISessionJoinRequestedSource JoinRequestedSource = EUISessionJoinRequestedSource::Unspecified;` — Join request source

#### class `UE::Online::ISessions`  
`class ISessions`  
_L712-921_
- L721 _public prototype_ `virtual TOnlineResult<FGetAllSessions> GetAllSessions(FGetAllSessions::Params&& Params) const = 0;` — Gets an array of references to all the sessions the given user is part of. @params Parameters for the GetAllSessions call return
- L729 _public prototype_ `virtual TOnlineResult<FGetSessionByName> GetSessionByName(FGetSessionByName::Params&& Params) const = 0;` — Gets a reference to the session with the given local name. @params Parameters for the GetSessionByName call return
- L737 _public prototype_ `virtual TOnlineResult<FGetSessionName> GetSessionName(FGetSessionName::Params&& Params) const = 0;` — Gets the name of the session with the given id handle. @params Parameters for the GetSessionName call return
- L745 _public prototype_ `virtual TOnlineResult<FGetSessionById> GetSessionById(FGetSessionById::Params&& Params) const = 0;` — Gets a reference to the session with the given id handle. @params Parameters for the GetSessionById call return
- L753 _public prototype_ `virtual TOnlineResult<FGetPresenceSession> GetPresenceSession(FGetPresenceSession::Params&& Params) const = 0;` — Gets a reference to the session set as presence session for the given user. @params Parameters for the GetPresenceSession call return
- L761 _public prototype_ `virtual TOnlineResult<FIsPresenceSession> IsPresenceSession(FIsPresenceSession::Params&& Params) const = 0;` — Returns whether the session with the given id is set as the presence session for the given user. @params Parameters for the IsPresenceSession call return
- L769 _public prototype_ `virtual TOnlineResult<FSetPresenceSession> SetPresenceSession(FSetPresenceSession::Params&& Params) = 0;` — Sets the session with the given id as the presence session for the given user. @params Parameters for the SetPresenceSession call return
- L777 _public prototype_ `virtual TOnlineResult<FClearPresenceSession> ClearPresenceSession(FClearPresenceSession::Params&& Params) = 0;` — Clears the presence session for the given user. @params Parameters for the ClearPresenceSession call return
- L786 _public prototype_ `virtual TOnlineAsyncOpHandle<FCreateSession> CreateSession(FCreateSession::Params&& Params) = 0;` — Creates a new session with the given parameters, and assigns to it the given local name. Depending on the implementation, the creating user might not be added to the Session Members automatically, so a subsequent call to AddSessionMember is recommended @param Parameters for the CreateSession call @return
- L795 _public prototype_ `virtual TOnlineAsyncOpHandle<FUpdateSessionSettings> UpdateSessionSettings(FUpdateSessionSettings::Params&& Params) = 0;` — Update the settings for the session with the given name. Should only be called by the session owner. @param Parameters for the UpdateSessionSettings call @return
- L803 _public prototype_ `virtual TOnlineAsyncOpHandle<FLeaveSession> LeaveSession(FLeaveSession::Params&& Params) = 0;` — Leaves and optionally destroys the session with the given name. @param Parameters for the LeaveSession call @return
- L811 _public prototype_ `virtual TOnlineAsyncOpHandle<FFindSessions> FindSessions(FFindSessions::Params&& Params) = 0;` — Queries the API session service for sessions matching the given parameters. @param Parameters for the FindSessions call @return
- L819 _public prototype_ `virtual TOnlineAsyncOpHandle<FStartMatchmaking> StartMatchmaking(FStartMatchmaking::Params&& Params) = 0;` — Starts the matchmaking process, which will either create a session with the given parameters, or join one that matches the given search filters. @param Parameters for the StartMatchmaking call @return
- L827 _public prototype_ `virtual TOnlineAsyncOpHandle<FJoinSession> JoinSession(FJoinSession::Params&& Params) = 0;` — Joins  the session with the given session id, and assigns to it the given local name. @param Parameters for the JoinSession call @return
- L836 _public prototype_ `virtual TOnlineAsyncOpHandle<FAddSessionMember> AddSessionMember(FAddSessionMember::Params&& Params) = 0;` — Adds the given user as a new session member to the session with the given name The number of open slots in the session will decrease accordingly @params Parameters for the AddSessionMember call @return
- L845 _public prototype_ `virtual TOnlineAsyncOpHandle<FRemoveSessionMember> RemoveSessionMember(FRemoveSessionMember::Params&& Params) = 0;` — Removes the given user from the session with the given name The number of open slots in the session will increase accordingly @params Parameters for the RemoveSessionMember call @return
- L853 _public prototype_ `virtual TOnlineAsyncOpHandle<FSendSessionInvite> SendSessionInvite(FSendSessionInvite::Params&& Params) = 0;` — Sends an invite to the session with the given name to all given users. @param Parameters for the SendSessionInvite call @return
- L861 _public prototype_ `virtual TOnlineResult<FGetSessionInviteById> GetSessionInviteById(FGetSessionInviteById::Params&& Params) = 0;` — Gets a reference to the session invite with the given invite id. @param Parameters for the GetSessionInviteById call @return
- L869 _public prototype_ `virtual TOnlineResult<FGetAllSessionInvites> GetAllSessionInvites(FGetAllSessionInvites::Params&& Params) = 0;` — Gets an array of references to all the session invites the given user has received. @param Parameters for the SendSessionInvite call @return
- L877 _public prototype_ `virtual TOnlineAsyncOpHandle<FRejectSessionInvite> RejectSessionInvite(FRejectSessionInvite::Params&& Params) = 0;` — Rejects the session invite with the given invite id. @param Parameters for the RejectSessionInvite call @return
- L886 _public prototype_ `virtual TOnlineEvent<void(const FSessionCreated &)> OnSessionCreated() = 0;` — This event will trigger as a result of a session being created. @return
- L892 _public prototype_ `virtual TOnlineEvent<void(const FSessionJoined&)> OnSessionJoined() = 0;` — This event will trigger as a result of joining a session. @return
- L899 _public prototype_ `virtual TOnlineEvent<void(const FSessionLeft&)> OnSessionLeft() = 0;` — This event will trigger as a result of leaving or destroying a session. @return
- L906 _public prototype_ `virtual TOnlineEvent<void(const FSessionUpdated&)> OnSessionUpdated() = 0;` — This event will trigger as a result of updating a session's settings, or whenever a session update event is received by the API. @return
- L913 _public prototype_ `virtual TOnlineEvent<void(const FSessionInviteReceived&)> OnSessionInviteReceived() = 0;` — This event will trigger as a result of receiving a session invite. @return
- L920 _public prototype_ `virtual TOnlineEvent<void(const FUISessionJoinRequested&)> OnUISessionJoinRequested() = 0;` — This event will trigger as a result of accepting a session invite or joining a session via the platform UI. @return

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ONLINESERVICESINTERFACE_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Online` (scope `UE`)
- L45 _typedef_ `using FCustomSessionSettingsMap = TMap<FSchemaAttributeId, FCustomSessionSetting>;` (scope `UE::Online`)
- L57 _typedef_ `using FCustomSessionSettingUpdateMap = TMap<FName, FCustomSessionSettingUpdate>;` (scope `UE::Online`)
- L59 _typedef_ `using FSessionMemberIdsSet = TSet<FAccountId>;` (scope `UE::Online`)
- L73 _prototype_ `const TCHAR* LexToString(ESessionJoinPolicy Value);` (scope `UE::Online`)
- L74 _prototype_ `void LexFromString(ESessionJoinPolicy& Value, const TCHAR* InStr);` (scope `UE::Online`)
- L194 _prototype_ `const FString ToLogString(const ISession& Session);` (scope `UE::Online`)
- L210 _prototype_ `const FString ToLogString(const ISessionInvite& Session);` (scope `UE::Online`)
- L697 _prototype_ `const TCHAR* LexToString(EUISessionJoinRequestedSource UISessionJoinRequestedSource);` (scope `UE::Online`)
- L698 _prototype_ `void LexFromString(EUISessionJoinRequestedSource& OutUISessionJoinRequestedSource, const TCHAR* InStr);` (scope `UE::Online`)
- L923 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/Social.h` (Public)


#### enum `UE::Online::ERelationship`  
`enum class ERelationship : uint8`  
_L18-30_
- desc: Social relationship status
- L21 _public enumerator_ `Friend` — Friend
- L23 _public enumerator_ `NotFriend` — Not friend
- L25 _public enumerator_ `InviteSent` — Invite Sent to User
- L27 _public enumerator_ `InviteReceived` — Invite Received from User
- L29 _public enumerator_ `Blocked` — Local user has Blocked the other user

#### struct `UE::Online::FFriend`  
`struct FFriend`  
_L37-47_
- desc: Information about a friend
- L40 _public member_ `FAccountId FriendId;` — Account Id of the Friend
- L42 _public member_ `FString DisplayName;` — Display Name of the Friend
- L44 _public member_ `FString Nickname;` — Local Nickname for the Friend, Not always available
- L46 _public member_ `ERelationship Relationship;` — Relationship of the friend

#### struct `UE::Online::FQueryFriends`  
`struct FQueryFriends`  
_L49-67_
- L51 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FQueryFriends::Params`  
`struct Params`  
_L54-58_
- desc: Input struct for Social::QueryFriends
- L57 _public member_ `FAccountId LocalAccountId;` — Account Id of the local user making the request

#### struct `UE::Online::FQueryFriends::Result`  
`struct Result`  
_L64-66_
- desc: Output struct for Social::QueryFriends Obtain the friends list via GetFriends

#### struct `UE::Online::FGetFriends`  
`struct FGetFriends`  
_L69-86_
- L71 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetFriends::Params`  
`struct Params`  
_L74-78_
- desc: Input struct for Social::GetFriends
- L77 _public member_ `FAccountId LocalAccountId;` — Account Id of the local user making the request

#### struct `UE::Online::FGetFriends::Result`  
`struct Result`  
_L81-85_
- desc: Output struct for Social::GetFriends
- L84 _public member_ `TArray<TSharedRef<FFriend>> Friends;` — Array of friends

#### struct `UE::Online::FSendFriendInvite`  
`struct FSendFriendInvite`  
_L88-105_
- L90 _public member_ `static constexpr TCHAR Name[] = TEXT("Sen`

#### struct `UE::Online::FSendFriendInvite::Params`  
`struct Params`  
_L93-99_
- desc: Input struct for Social::SendFriendInvite
- L96 _public member_ `FAccountId LocalAccountId;` — Account Id of the local user making the request
- L98 _public member_ `FAccountId TargetAccountId;` — Account Id of user to send a friend request to

#### struct `UE::Online::FSendFriendInvite::Result`  
`struct Result`  
_L102-104_
- desc: Output struct for Social::SendFriendInvite

#### struct `UE::Online::FAcceptFriendInvite`  
`struct FAcceptFriendInvite`  
_L107-124_
- L109 _public member_ `static constexpr TCHAR Name[] = TEXT("Acc`

#### struct `UE::Online::FAcceptFriendInvite::Params`  
`struct Params`  
_L112-118_
- desc: Input struct for Social::AcceptFriendInvite
- L115 _public member_ `FAccountId LocalAccountId;` — Account Id of the local user making the request
- L117 _public member_ `FAccountId TargetAccountId;` — Account Id of user that sent the invite

#### struct `UE::Online::FAcceptFriendInvite::Result`  
`struct Result`  
_L121-123_
- desc: Output struct for Social::AcceptFriendInvite

#### struct `UE::Online::FRejectFriendInvite`  
`struct FRejectFriendInvite`  
_L126-143_
- L128 _public member_ `static constexpr TCHAR Name[] = TEXT("Rej`

#### struct `UE::Online::FRejectFriendInvite::Params`  
`struct Params`  
_L131-137_
- desc: Input struct for Social::RejectFriendInvite
- L134 _public member_ `FAccountId LocalAccountId;` — Account Id of the local user making the request
- L136 _public member_ `FAccountId TargetAccountId;` — Account Id of user that sent the invite

#### struct `UE::Online::FRejectFriendInvite::Result`  
`struct Result`  
_L140-142_
- desc: Output struct for Social::RejectFriendInvite

#### struct `UE::Online::FRelationshipUpdated`  
`struct FRelationshipUpdated`  
_L146-156_
- desc: Struct for RelationshipUpdated event
- L149 _public member_ `FAccountId LocalAccountId;` — Account Id of the Local User whose friends list changed
- L151 _public member_ `FAccountId RemoteAccountId;` — Account Id of the User whose status changed
- L153 _public member_ `ERelationship OldRelationship;` — Previous relationship
- L155 _public member_ `ERelationship NewRelationship;` — New relationship

#### struct `UE::Online::FQueryBlockedUsers`  
`struct FQueryBlockedUsers`  
_L158-176_
- L160 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FQueryBlockedUsers::Params`  
`struct Params`  
_L163-167_
- desc: Input struct for Social::QueryBlockedUsers
- L166 _public member_ `FAccountId LocalAccountId;` — Account Id of the local user making the request

#### struct `UE::Online::FQueryBlockedUsers::Result`  
`struct Result`  
_L173-175_
- desc: Output struct for Social::QueryBlockedUsers Obtain the blocked users list via GetBlockedUsers

#### struct `UE::Online::FGetBlockedUsers`  
`struct FGetBlockedUsers`  
_L178-195_
- L180 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetBlockedUsers::Params`  
`struct Params`  
_L183-187_
- desc: Input struct for Social::GetBlockedUsers
- L186 _public member_ `FAccountId LocalAccountId;` — Account Id of the local user making the request

#### struct `UE::Online::FGetBlockedUsers::Result`  
`struct Result`  
_L190-194_
- desc: Output struct for Social::GetBlockedUsers
- L193 _public member_ `TArray<FAccountId> BlockedUsers;` — Array of blocked users

#### struct `UE::Online::FBlockUser`  
`struct FBlockUser`  
_L197-214_
- L199 _public member_ `static constexpr TCHAR Name[] = TEXT("Blo`

#### struct `UE::Online::FBlockUser::Params`  
`struct Params`  
_L202-208_
- desc: Input struct for Social::BlockUser
- L205 _public member_ `FAccountId LocalAccountId;` — Account Id of the local user making the request
- L207 _public member_ `FAccountId TargetAccountId;` — Account Id of user to block

#### struct `UE::Online::FBlockUser::Result`  
`struct Result`  
_L211-213_
- desc: Output struct for Social::BlockUser

#### class `UE::Online::ISocial`  
`class ISocial`  
_L216-293_
- L219 _public prototype_ `virtual ~ISocial() = default;`
- L227 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryFriends> QueryFriends(FQueryFriends::Params&& Params) = 0;` — Query the friends list @param Params for the QueryFriends call @return AsyncOpHandle
- L235 _public prototype_ `virtual TOnlineResult<FGetFriends> GetFriends(FGetFriends::Params&& Params) = 0;` — Get the contents of a previously queried friends list @param Params for the GetFriends call @return Result
- L243 _public prototype_ `virtual TOnlineAsyncOpHandle<FSendFriendInvite> SendFriendInvite(FSendFriendInvite::Params&& Params) = 0;` — Send a friend invite @param Params for the SendFriendInvite call @return AsyncOpHandle
- L251 _public prototype_ `virtual TOnlineAsyncOpHandle<FAcceptFriendInvite> AcceptFriendInvite(FAcceptFriendInvite::Params&& Params) = 0;` — Accept a friend invite @param Params for the AcceptFriendInvite call @return AsyncOpHandle
- L259 _public prototype_ `virtual TOnlineAsyncOpHandle<FRejectFriendInvite> RejectFriendInvite(FRejectFriendInvite::Params&& Params) = 0;` — Reject a friend invite @param Params for the RejectFriendInvite call @return AsyncOpHandle
- L268 _public prototype_ `virtual TOnlineEvent<void(const FRelationshipUpdated&)> OnRelationshipUpdated() = 0;` — Get the event that is triggered when a friends list is updated This typically happens when QueryFriends is called, a friend or block list modifying function is called, or is called in response to an event coming from a backend service @return Event that can be bound to
- L276 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryBlockedUsers> QueryBlockedUsers(FQueryBlockedUsers::Params&& Params) = 0;` — Query the blocked users list @param Params for the QueryBlockedUsers call @return AsyncOpHandle
- L284 _public prototype_ `virtual TOnlineResult<FGetBlockedUsers> GetBlockedUsers(FGetBlockedUsers::Params&& Params) = 0;` — Get the contents of a previously queried blocked users list @param Params for the GetBlockedUsers call @return Result
- L292 _public prototype_ `virtual TOnlineAsyncOpHandle<FBlockUser> BlockUser(FBlockUser::Params&& Params) = 0;` — Block a user @param Params for the BlockUser call @return AsyncOpHandle

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L11 _namespace_ `namespace Meta` (scope `UE::Online`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L32 _prototype_ `const TCHAR* LexToString(ERelationship Relationship);` (scope `UE::Online`)
- L295 _function_ `inline const TCHAR* LexToString(ERelationship Relationship)` (scope `UE::Online`)
- L313 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/Stats.h` (Public)


#### struct `UE::Online::FUserStats`  
`struct FUserStats`  
_L17-23_
- L20 _public member_ `FAccountId AccountId;` — The user id
- L22 _public member_ `TMap<FString, FStatValue> Stats;` — The stats of one account

#### struct `UE::Online::FUpdateStats`  
`struct FUpdateStats`  
_L25-40_
- L27 _public member_ `static constexpr TCHAR Name[] = TEXT("Upd`

#### struct `UE::Online::FUpdateStats::Params`  
`struct Params`  
_L29-35_
- L32 _public member_ `FAccountId LocalAccountId;` — Local user id
- L34 _public member_ `TArray<FUserStats> UpdateUsersStats;` — The stats of users to update

#### struct `UE::Online::FUpdateStats::Result`  
`struct Result`  
_L37-39_

#### struct `UE::Online::FQueryStats`  
`struct FQueryStats`  
_L42-61_
- L44 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FQueryStats::Params`  
`struct Params`  
_L46-54_
- L49 _public member_ `FAccountId LocalAccountId;` — Local user id
- L51 _public member_ `FAccountId TargetAccountId;` — Target user id to query
- L53 _public member_ `TArray<FString> StatNames;` — The stats to query

#### struct `UE::Online::FQueryStats::Result`  
`struct Result`  
_L56-60_
- L59 _public member_ `TMap<FString, FStatValue> Stats;` — The stats of queried user

#### struct `UE::Online::FBatchQueryStats`  
`struct FBatchQueryStats`  
_L63-82_
- L65 _public member_ `static constexpr TCHAR Name[] = TEXT("Bat`

#### struct `UE::Online::FBatchQueryStats::Params`  
`struct Params`  
_L67-75_
- L70 _public member_ `FAccountId LocalAccountId;` — Local user id
- L72 _public member_ `TArray<FAccountId> TargetAccountIds;` — The user ids to query
- L74 _public member_ `TArray<FString> StatNames;` — The stats to query

#### struct `UE::Online::FBatchQueryStats::Result`  
`struct Result`  
_L77-81_
- L80 _public member_ `TArray<FUserStats> UsersStats;` — The stats of queried users, there should be no much elements so simply use TArray instead of TMap

#### struct `UE::Online::FTriggerEvent`  
`struct FTriggerEvent`  
_L84-101_
- L86 _public member_ `static constexpr TCHAR Name[] = TEXT("Tri`

#### struct `UE::Online::FTriggerEvent::Params`  
`struct Params`  
_L88-96_
- L91 _public member_ `FAccountId LocalAccountId;` — Local user id
- L93 _public member_ `FString EventName;` — The name of the event to fire
- L95 _public member_ `FOnlineEventParams EventParams;` — The events parameters if any

#### struct `UE::Online::FTriggerEvent::Result`  
`struct Result`  
_L98-100_

#### struct `UE::Online::FResetStats`  
`struct FResetStats`  
_L104-117_
- L106 _public member_ `static constexpr TCHAR Name[] = TEXT("Res`

#### struct `UE::Online::FResetStats::Params`  
`struct Params`  
_L108-112_
- L111 _public member_ `FAccountId LocalAccountId;` — Local user id

#### struct `UE::Online::FResetStats::Result`  
`struct Result`  
_L114-116_

#### struct `UE::Online::FGetCachedStats`  
`struct FGetCachedStats`  
_L120-132_
- L122 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetCachedStats::Params`  
`struct Params`  
_L124-126_

#### struct `UE::Online::FGetCachedStats::Result`  
`struct Result`  
_L128-131_
- L130 _public member_ `TArray<FUserStats> UsersStats;`

#### class `UE::Online::IStats`  
`class IStats`  
_L137-192_
- desc: Stats interface is used to upload the stats to EOS or first party platforms, to complete corresponding InGame/Platform features such as Stats Query, Achievements, Leaderboard, etc.
- L140 _public prototype_ `virtual ~IStats() = default;`
- L148 _public prototype_ `virtual TOnlineAsyncOpHandle<FUpdateStats> UpdateStats(FUpdateStats::Params&& Params) = 0;` — Upload/send stats to the backend/platform. @param Params for the UpdateStats call @return
- L155 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryStats> QueryStats(FQueryStats::Params&& Params) = 0;` — Get stats of the specified user. @param Params for the QueryStats call @return
- L162 _public prototype_ `virtual TOnlineAsyncOpHandle<FBatchQueryStats> BatchQueryStats(FBatchQueryStats::Params&& Params) = 0;` — Get stats of the specified users. @param Params for the BatchQueryStats call @return
- L169 _public prototype_ `virtual TOnlineAsyncOpHandle<FTriggerEvent> TriggerEvent(FTriggerEvent::Params&& Params) = 0;` — Trigger a stat modifying event @param Params for the TriggerEvent call @return
- L178 _public prototype_ `virtual TOnlineAsyncOpHandle<FResetStats> ResetStats(FResetStats::Params&& Params) = 0;` — Reset stats of the local user. @param Params for the ResetStats call @return
- L184 _public prototype_ `virtual TOnlineEvent<void(const FStatsUpdated&)> OnStatsUpdated() = 0;` — Event triggered when stats of user(s) changed
- L191 _public prototype_ `virtual TOnlineResult<FGetCachedStats> GetCachedStats(FGetCachedStats::Params&& Params) const = 0;` — Retrieve cached users' stats, which was retrieved when call QueryStats or BatchQueryStats, or after calling UpdateStats. When choose to use StatsNull, make sure to listen to OnStatsUpdated event and use this function to get all latest local stats and put them into SaveGame

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L14 _typedef_ `using FStatValue = FSchemaVariant;` (scope `UE::Online`)
- L15 _typedef_ `using FOnlineEventParams = TMap<FString, FSchemaVariant>;` (scope `UE::Online`)
- L134 _typedef_ `using FStatsUpdated = FUpdateStats::Params;` (scope `UE::Online`)
- L194 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/TitleFile.h` (Public)


#### struct `UE::Online::FTitleFileEnumerateFiles`  
`struct FTitleFileEnumerateFiles`  
_L14-27_
- L16 _public member_ `static constexpr TCHAR Name[] = TEXT("Enu`

#### struct `UE::Online::FTitleFileEnumerateFiles::Params`  
`struct Params`  
_L18-22_
- L21 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation

#### struct `UE::Online::FTitleFileEnumerateFiles::Result`  
`struct Result`  
_L24-26_

#### struct `UE::Online::FTitleFileGetEnumeratedFiles`  
`struct FTitleFileGetEnumeratedFiles`  
_L29-44_
- L31 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FTitleFileGetEnumeratedFiles::Params`  
`struct Params`  
_L33-37_
- L36 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation

#### struct `UE::Online::FTitleFileGetEnumeratedFiles::Result`  
`struct Result`  
_L39-43_
- L42 _public member_ `TArray<FString> Filenames;` — Available files

#### struct `UE::Online::FTitleFileReadFile`  
`struct FTitleFileReadFile`  
_L51-68_
- L53 _public member_ `static constexpr TCHAR Name[] = TEXT("Rea`

#### struct `UE::Online::FTitleFileReadFile::Params`  
`struct Params`  
_L55-61_
- L58 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation
- L60 _public member_ `FString Filename;` — File to be opened

#### struct `UE::Online::FTitleFileReadFile::Result`  
`struct Result`  
_L63-67_
- L66 _public member_ `FTitleFileContentsRef FileContents;` — Contents of the file

#### class `UE::Online::ITitleFile`  
`class ITitleFile`  
_L70-89_
- L73 _public prototype_ `virtual ~ITitleFile() = default;`
- L78 _public prototype_ `virtual TOnlineAsyncOpHandle<FTitleFileEnumerateFiles> EnumerateFiles(FTitleFileEnumerateFiles::Params&& Params) = 0;` — Enumerate all available files
- L83 _public prototype_ `virtual TOnlineResult<FTitleFileGetEnumeratedFiles> GetEnumeratedFiles(FTitleFileGetEnumeratedFiles::Params&& Params) = 0;` — Get the cached list of files enumerated by previous call to EnumerateFiles
- L88 _public prototype_ `virtual TOnlineAsyncOpHandle<FTitleFileReadFile> ReadFile(FTitleFileReadFile::Params&& Params) = 0;` — Read a file and return the file contents

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace Meta` (scope `UE::Online`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L46 _typedef_ `using FTitleFileContents = TArray<uint8>;` (scope `UE::Online`)
- L47 _typedef_ `using FTitleFileContentsRef = TSharedRef<const FTitleFileContents>;` (scope `UE::Online`)
- L48 _typedef_ `using FTitleFileContentsPtr = TSharedPtr<const FTitleFileContents>;` (scope `UE::Online`)
- L49 _typedef_ `using FTitleFileContentsWeakPtr = TWeakPtr<const FTitleFileContents>;` (scope `UE::Online`)
- L92 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/UserFile.h` (Public)


#### struct `UE::Online::FUserFileEnumerateFiles`  
`struct FUserFileEnumerateFiles`  
_L14-27_
- L16 _public member_ `static constexpr TCHAR Name[] = TEXT("Enu`

#### struct `UE::Online::FUserFileEnumerateFiles::Params`  
`struct Params`  
_L18-22_
- L21 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation

#### struct `UE::Online::FUserFileEnumerateFiles::Result`  
`struct Result`  
_L24-26_

#### struct `UE::Online::FUserFileGetEnumeratedFiles`  
`struct FUserFileGetEnumeratedFiles`  
_L29-44_
- L31 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FUserFileGetEnumeratedFiles::Params`  
`struct Params`  
_L33-37_
- L36 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation

#### struct `UE::Online::FUserFileGetEnumeratedFiles::Result`  
`struct Result`  
_L39-43_
- L42 _public member_ `TArray<FString> Filenames;` — Available files for the local user

#### struct `UE::Online::FUserFileReadFile`  
`struct FUserFileReadFile`  
_L51-68_
- L53 _public member_ `static constexpr TCHAR Name[] = TEXT("Rea`

#### struct `UE::Online::FUserFileReadFile::Params`  
`struct Params`  
_L55-61_
- L58 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation
- L60 _public member_ `FString Filename;` — File to be read

#### struct `UE::Online::FUserFileReadFile::Result`  
`struct Result`  
_L63-67_
- L66 _public member_ `FUserFileContentsRef FileContents;` — Contents of the file

#### struct `UE::Online::FUserFileWriteFile`  
`struct FUserFileWriteFile`  
_L70-87_
- L72 _public member_ `static constexpr TCHAR Name[] = TEXT("Wri`

#### struct `UE::Online::FUserFileWriteFile::Params`  
`struct Params`  
_L74-82_
- L77 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation
- L79 _public member_ `FString Filename;` — File to be written
- L81 _public member_ `FUserFileContents FileContents;` — Data to write

#### struct `UE::Online::FUserFileWriteFile::Result`  
`struct Result`  
_L84-86_

#### struct `UE::Online::FUserFileCopyFile`  
`struct FUserFileCopyFile`  
_L89-106_
- L91 _public member_ `static constexpr TCHAR Name[] = TEXT("Cop`

#### struct `UE::Online::FUserFileCopyFile::Params`  
`struct Params`  
_L93-101_
- L96 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation
- L98 _public member_ `FString SourceFilename;` — File to copy contents from
- L100 _public member_ `FString TargetFilename;` — File to copy contents to

#### struct `UE::Online::FUserFileCopyFile::Result`  
`struct Result`  
_L103-105_

#### struct `UE::Online::FUserFileDeleteFile`  
`struct FUserFileDeleteFile`  
_L108-123_
- L110 _public member_ `static constexpr TCHAR Name[] = TEXT("Del`

#### struct `UE::Online::FUserFileDeleteFile::Params`  
`struct Params`  
_L112-118_
- L115 _public member_ `FAccountId LocalAccountId;` — Local user performing the operation
- L117 _public member_ `FString Filename;` — File to delete

#### struct `UE::Online::FUserFileDeleteFile::Result`  
`struct Result`  
_L120-122_

#### class `UE::Online::IUserFile`  
`class IUserFile`  
_L125-159_
- L128 _public prototype_ `virtual ~IUserFile() = default;`
- L133 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileEnumerateFiles> EnumerateFiles(FUserFileEnumerateFiles::Params&& Params) = 0;` — Enumerate all available files
- L138 _public prototype_ `virtual TOnlineResult<FUserFileGetEnumeratedFiles> GetEnumeratedFiles(FUserFileGetEnumeratedFiles::Params&& Params) = 0;` — Get the cached list of files enumerated by previous call to EnumerateFiles
- L143 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileReadFile> ReadFile(FUserFileReadFile::Params&& Params) = 0;` — Read a file and return the file contents
- L148 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileWriteFile> WriteFile(FUserFileWriteFile::Params&& Params) = 0;` — Write file contents to a file.
- L153 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileCopyFile> CopyFile(FUserFileCopyFile::Params&& Params) = 0;` — Copy file contents to another file
- L158 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileDeleteFile> DeleteFile(FUserFileDeleteFile::Params&& Params) = 0;` — Delete a file

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace Meta` (scope `UE::Online`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L46 _typedef_ `using FUserFileContents = TArray<uint8>;` (scope `UE::Online`)
- L47 _typedef_ `using FUserFileContentsRef = TSharedRef<const FUserFileContents>;` (scope `UE::Online`)
- L48 _typedef_ `using FUserFileContentsPtr = TSharedPtr<const FUserFileContents>;` (scope `UE::Online`)
- L49 _typedef_ `using FUserFileContentsWeakPtr = TWeakPtr<const FUserFileContents>;` (scope `UE::Online`)
- L161 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/UserInfo.h` (Public)


#### struct `UE::Online::FUserInfo`  
`struct FUserInfo`  
_L15-21_
- L18 _public member_ `FAccountId AccountId;` — Account Id
- L20 _public member_ `FString DisplayName;` — Display Name of the User

#### struct `UE::Online::FQueryUserInfo`  
`struct FQueryUserInfo`  
_L23-43_
- L25 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FQueryUserInfo::Params`  
`struct Params`  
_L28-34_
- desc: Input struct for UserInfo::QueryUserInfo
- L31 _public member_ `FAccountId LocalAccountId;` — Local user to query users for
- L33 _public member_ `TArray<FAccountId> AccountIds;` — List of User ids to Query

#### struct `UE::Online::FQueryUserInfo::Result`  
`struct Result`  
_L40-42_
- desc: Output struct for UserInfo::QueryUserInfo Obtain the queried user info via GetUserInfo

#### struct `UE::Online::FGetUserInfo`  
`struct FGetUserInfo`  
_L45-68_
- L47 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetUserInfo::Params`  
`struct Params`  
_L50-58_
- desc: Input struct for UserInfo::GetUserInfo
- L53 _public member_ `FAccountId LocalAccountId;` — Local user
- L55 _public member_ `FAccountId AccountId;` — User id to get info for
- L57 _public member_ `TOptional<EOnlinePlatformType> DisplayNamePlatform;` — Preferred platform for DisplayName

#### struct `UE::Online::FGetUserInfo::Result`  
`struct Result`  
_L63-67_
- desc: Output struct for UserInfo::GetUserInfo
- L66 _public member_ `TSharedRef<FUserInfo> UserInfo;` — User info

#### struct `UE::Online::FQueryUserAvatar`  
`struct FQueryUserAvatar`  
_L70-90_
- L72 _public member_ `static constexpr TCHAR Name[] = TEXT("Que`

#### struct `UE::Online::FQueryUserAvatar::Params`  
`struct Params`  
_L75-81_
- desc: Input struct for UserInfo::QueryUserAvatar
- L78 _public member_ `FAccountId LocalAccountId;` — Local user to query users for
- L80 _public member_ `TArray<FAccountId> AccountIds;` — List of User ids to Query

#### struct `UE::Online::FQueryUserAvatar::Result`  
`struct Result`  
_L87-89_
- desc: Output struct for UserInfo::QueryUserAvatar Obtain the queried user info via GetUserAvatar

#### struct `UE::Online::FGetUserAvatar`  
`struct FGetUserAvatar`  
_L92-113_
- L94 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FGetUserAvatar::Params`  
`struct Params`  
_L97-103_
- desc: Input struct for UserInfo::GetUserAvatar
- L100 _public member_ `FAccountId LocalAccountId;` — Local user
- L102 _public member_ `FAccountId AccountId;` — User id to get avatar for

#### struct `UE::Online::FGetUserAvatar::Result`  
`struct Result`  
_L108-112_
- desc: Output struct for UserInfo::GetUserAvatar
- L111 _public member_ `FString AvatarUrl;` — Avatar Url

#### struct `UE::Online::FShowUserProfile`  
`struct FShowUserProfile`  
_L115-134_
- L117 _public member_ `static constexpr TCHAR Name[] = TEXT("Sho`

#### struct `UE::Online::FShowUserProfile::Params`  
`struct Params`  
_L120-126_
- desc: Input struct for UserInfo::ShowUserProfile
- L123 _public member_ `FAccountId LocalAccountId;` — Local user
- L125 _public member_ `FAccountId AccountId;` — User id to display the profile for

#### struct `UE::Online::FShowUserProfile::Result`  
`struct Result`  
_L131-133_
- desc: Output struct for UserInfo::ShowUserProfile

#### class `UE::Online::IUserInfo`  
`class IUserInfo`  
_L136-188_
- L139 _public prototype_ `virtual ~IUserInfo() = default;`
- L150 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryUserInfo> QueryUserInfo(FQueryUserInfo::Params&& Params) = 0;` — Queries the user info for a list of account ids. Upon success, user info can be accessed with GetUserInfo. @see FUserInfo @see GetUserInfo @params Params for the QueryUserInfo call @return AsyncOpHandle
- L160 _public prototype_ `virtual TOnlineResult<FGetUserInfo> GetUserInfo(FGetUserInfo::Params&& Params) = 0;` — Get the user info for a previously queried AccountId @see FUserInfo @see QueryUserInfo @params Params for the GetUserInfo call @return Result
- L170 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryUserAvatar> QueryUserAvatar(FQueryUserAvatar::Params&& Params) = 0;` — Queries the user avatars for a list of account ids Upon success, avatars can be accessed with GetUserAvatar. @see GetUserAvatar @params Params for the QueryUserAvatar call @return AsyncOpHandle
- L179 _public prototype_ `virtual TOnlineResult<FGetUserAvatar> GetUserAvatar(FGetUserAvatar::Params&& Params) = 0;` — Get the user avatar for a previously queried AccountId @see QueryUserAvatar @params Params for the GetUserAvatar call @return Result
- L187 _public prototype_ `virtual TOnlineAsyncOpHandle<FShowUserProfile> ShowUserProfile(FShowUserProfile::Params&& Params) = 0;` — Show the profile UI for a user @params Params for the ShowUserProfile call @return AsyncOpHandle

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Online` (scope `UE`)
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Online` (scope `UE`)
- L11 _namespace_ `namespace Meta` (scope `UE::Online`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L190 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServices/Source/OnlineServicesInterface/Public/Online/Windows/WindowsOnlineErrorDefinitions.h` (Public)


#### Free symbols / members of external scopes

- L11 _macro_ `#define LOCTEXT_NAMESPACE "OnlineErrors"`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L13 _namespace_ `namespace Errors` (scope `UE::Online`)
- L29 _function_ `inline FString Internal_HResultToString(HRESULT Result)` (scope `UE::Online::Errors`)
- L54 _function_ `inline ErrorCodeType ErrorValueFromHRESULT(HRESULT Result)` (scope `UE::Online::Errors`)
- L59 _function_ `inline ErrorCodeType ErrorCodeFromHRESULT(HRESULT Result)` (scope `UE::Online::Errors`)
- L65 _function_ `inline FOnlineError FromHRESULT(HRESULT Result)` (scope `UE::Online::Errors`) — Errors created from this will be equal to the predefined types in ErrorCodes::Windows if they exist.
